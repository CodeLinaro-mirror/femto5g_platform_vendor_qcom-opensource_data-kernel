// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include <net/esp.h>
#include <net/xfrm.h>
#include <crypto/aead.h>

#include "eip_ipsec.h"

static bool dump_skb = false;
module_param(dump_skb, bool, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(dump_skb,
		 "Ether Type used for EIP SA Tag insertion/detection");

static void __eip_dump_skb(struct sk_buff *skb)
{
	int i;

	for (i = 0; i < skb->len; i++) {
		if ((i % 16) == 0)
			pr_info("%u:", i);
		if ((i % 8) == 0)
			pr_cont("\t");
		pr_cont(" %02x", skb->data[i]);
	}
	pr_info("\n");
}

#define eip_dump_skb(skb, fmt, args...)                                        \
	({                                                                     \
		if (dump_skb) {                                                \
			pr_info("DUMP SKB (%u) at %s:%d: " fmt, skb->len,      \
				__func__, __LINE__, ##args);                   \
			__eip_dump_skb(skb);                                   \
		}                                                              \
	})

static inline void __update_outer_v4(struct sk_buff *skb, u8 **outer,
				     u8 **inner, u16 *outer_hdr_len,
				     u16 *esp_len)
{
	struct iphdr *outer_iph = ip_hdr(skb);
	struct iphdr *inner_iph = inner_ip_hdr(skb);
	u16 _outer_hdr_len = skb_network_header_len(skb);

	u16 outer_len = ntohs(outer_iph->tot_len);
	u16 inner_len = ntohs(inner_iph->tot_len);

	u16 new_outer_len = _outer_hdr_len + inner_len;

	outer_iph->protocol = IPPROTO_IPIP;
	outer_iph->tot_len = htons(new_outer_len);
	ip_send_check(outer_iph);

	*outer = (u8 *)outer_iph;
	*inner = (u8 *)inner_iph;
	*outer_hdr_len = _outer_hdr_len;
	*esp_len = outer_len - new_outer_len;
}

static inline void __update_outer_v6(struct sk_buff *skb, u8 **outer,
				     u8 **inner, u16 *outer_hdr_len,
				     u16 *esp_len)
{
	struct ipv6hdr *outer_iph = ipv6_hdr(skb);
	struct ipv6hdr *inner_iph = inner_ipv6_hdr(skb);
	u16 _outer_hdr_len = skb_network_header_len(skb);

	u16 outer_plen = ntohs(outer_iph->payload_len);
	u16 inner_plen = ntohs(inner_iph->payload_len);
	u16 inner_len = inner_plen + sizeof(struct ipv6hdr);

	u16 new_outer_plen =
		_outer_hdr_len - sizeof(struct ipv6hdr) + inner_len;

	outer_iph->nexthdr = IPPROTO_IPV6;
	outer_iph->payload_len = htons(new_outer_plen);

	*outer = (u8 *)outer_iph;
	*inner = (u8 *)inner_iph;
	*outer_hdr_len = _outer_hdr_len;
	*esp_len = outer_plen - new_outer_plen;
}

/**
 * __fixup_tx_ip - Overwrites ESP header with updated IP header
 *
 * @skb: Tx packet to be updated
 * @proto: IP protocol number of the outer/inner packet
 * @trim_header: [out] Returns the number of esp header bytes being trimmed
 * @trim_trailer: [out] Returns the number of esp trailer bytes being trimmed
 *
 * This function locates IP (outer and inner) headers and ESP header/trailer and
 * removes the ESP header by moving outer IP header over it. Any update required
 * in the outer IP header for the removal of ESP header/trailer is also performed.
 *
 * Note: This function does not reduce the length of skb data - caller is expected
 *       to perform this action based on @trim_header and @trim_trailer values.
 *
 * Returns the location to the newly relocated outer IP header.
 */
static u8 *__fixup_tx_ip(struct sk_buff *skb, u8 proto, u16 *trim_header,
			 u16 *trim_trailer)
{
	u8 *outer, *inner, *new_outer;
	u16 outer_hdr_len, esp_len;
	u16 esp_header_len, esp_trailer_len;

	if (proto == IPPROTO_IPIP)
		__update_outer_v4(skb, &outer, &inner, &outer_hdr_len,
				  &esp_len);
	else if (proto == IPPROTO_IPV6)
		__update_outer_v6(skb, &outer, &inner, &outer_hdr_len,
				  &esp_len);
	else
		return NULL;

	esp_header_len = (inner - outer) - outer_hdr_len;
	esp_trailer_len = esp_len - esp_header_len;

	/* Overwrite ESP header with outer IP */
	new_outer = outer + esp_header_len;
	memmove(new_outer, outer, outer_hdr_len);

	skb_set_network_header(skb, skb_network_offset(skb) + esp_header_len);

	*trim_header = esp_header_len;
	*trim_trailer = esp_trailer_len;

	return new_outer;
}

static int __eip_ipsec_fixup_tx_skb(struct sk_buff *skb, u8 proto,
				    const struct eip_sa_tag *sa_tag)
{
	struct ethhdr *ethhdr = eth_hdr(skb);
	struct eip_ethhdr *new_ethhdr;
	u8 *new_outer, *old_outer, *new_eth_proto;
	u16 trim_header, trim_trailer, eth_proto_len;

	eip_dump_skb(skb, "Fixup Tx Begin");

	/* Remove ESP header and move outer IP header next to the inner IP packet after
	 * fixing up the outer IP header for accomodating esp header/trailer removal.
	 */
	new_outer = __fixup_tx_ip(skb, proto, &trim_header, &trim_trailer);
	if (!new_outer)
		return -EINVAL;

	/* We expect the trimmed esp header space to be big enough to accomodate EIP
	 * SA Tag.
	 */
	if (trim_header < sizeof(*sa_tag))
		return -EFAULT;

	/* Move ethernet headers and insert SA tag with the space created by the removed
	 * esp header.
	 */
	old_outer = new_outer - trim_header;
	eth_proto_len = old_outer - (u8 *)(&ethhdr->h_proto);
	new_eth_proto = new_outer - eth_proto_len;
	new_ethhdr =
		container_of((__be16 *)new_eth_proto, struct eip_ethhdr, proto);

	memmove(&new_ethhdr->proto, &ethhdr->h_proto, eth_proto_len);
	new_ethhdr->sa_tag = *sa_tag;
	memmove(new_ethhdr, ethhdr, ETH_ALEN * 2);

	skb_pull(skb, trim_header - sizeof(*sa_tag));
	skb_reset_mac_header(skb);

	/* Remove esp trailer bytes */
	pskb_trim(skb, skb->len - trim_trailer);

	eip_dump_skb(skb, "Fixup Tx Complete");

	return 0;
}

/**
 * eip_ipsec_fixup_tx_skb - Fix up egress skb for IPsec offload in EIP
 * @skb: Skbuff containing the egress ethernet frame
 *
 * IPsec offload in Linux already inserts ESP header with all necessary padding and expansion required
 * for a given SA. For EIP, such expansion is incompatible for its offload logic, and instead expects
 * the packets to be simlpy using ipip or ip6ip6 tunnel with 4-byte EIP SATag inserted between Ethernet
 * SA and EtherType fields.
 *
 * Input Packet:
 *           |---------------------------------------|
 *           | Ethernet DA (6B)                      |
 *           | Ethernet SA (6B)                      |
 *           | Ether Type (2B)                       |
 *           | Outer IP v4/v6 Header                 | <--> will be updated
 *           | ESP: Header                           |  --> will be removed
 *           | ESP: IV (8B as per rfc4106(gcm(aes))) |  --> will be removed
 *           | ESP: (Unencrypted) Inner IP packet    |
 *           | ESP: Padding                          |  --> will be removed
 *           | ESP: Pad Length (1B)                  |  --> will be removed
 *           | ESP: Next Header (1B)                 |  --> will be removed
 *           | ESP: ICV (16B)                        |  --> will be removed
 *           |---------------------------------------|
 *
 * Output Packet:
 *           |-----------------------------------|
 *           | Ethernet DA (6B)                  |
 *           | Ethernet SA (6B)                  |
 *           [ Added EIP SA Tag (4B)             ] <--  is inserted
 *           | Ether Type (2B)                   |
 *           [ Updated Outer IP v4/v6 Header     ] <--> is updated
 *           | (Unencrypted) Inner IP packet     |
 *           |-----------------------------------|
 *
 * Outer IP header will have the following updates:
 *   1. Next Header / Protocol will be changed from ESP (50) to represent the type of Inner IP
 *      packet (v4 - 4, v6 - 41). The actual value is taken from ESP: Next Header field
 *   2. Total Length / Payload Length field will be updated to account for removal for ESP fields
 *   3. Header Checksum (IPv4) is updated to account for changes in Protocol and Total Length
 *      fields
 *
 * Note: This function ignores any packet that kernel xfrm stack does not mark for
 *       IPsec offload.
 */
int eip_ipsec_fixup_tx_skb(struct sk_buff *skb)
{
	const struct xfrm_offload *xo = xfrm_offload(skb);
	const struct xfrm_state *xs = xfrm_input_state(skb);
	struct eip_xfrm_state *eip_xs;

	if (!xo)
		return 0;

	if (!xs)
		return -EFAULT;

	eip_xs = (struct eip_xfrm_state *)xs->xso.offload_handle;
	if (!eip_xs)
		return -EFAULT;

	return __eip_ipsec_fixup_tx_skb(skb, xo->proto, &eip_xs->sa_tag);
}

static unsigned int sa_tag_to_index(struct eip_sa_tag *sa_tag)
{
	union eip_sa_tag_info tag_info;

	tag_info.info = be16_to_cpu(sa_tag->info);

	return tag_info.ingress.sa;
}

static struct xfrm_state *__raw_eip_find_rx_xs(struct eip_ipsec_link *ilink,
					       unsigned int sa_index)
{
	struct eip_xfrm_state *eip_xs;

	/* Linear search should be good enough since we do not expect many SAs within
	 * a single link.
	 */
	list_for_each_entry (eip_xs, &ilink->eip_xs_l, eip_xs_l) {
		if (eip_xs->inbound && eip_xs->sa_index == sa_index)
			return eip_xs->xs;
	}

	return NULL;
}

static struct xfrm_state *eip_rx_xs_get(struct eip_ipsec_link *ilink,
					unsigned int sa_index)
{
	struct xfrm_state *xs;

	read_lock(&ilink->lock);
	xs = __raw_eip_find_rx_xs(ilink, sa_index);
	if (xs)
		xfrm_state_hold(xs);
	read_unlock(&ilink->lock);

	return xs;
}

/* Sets the skb sec path to mark the skb as already authenticated */
static int eip_ipsec_set_secpath(struct sk_buff *skb)
{
	struct ethhdr *ethhdr = eth_hdr(skb);
	struct eip_sa_tag *sa_tag;
	struct xfrm_offload *xo;
	struct xfrm_state *xs;
	struct sec_path *sp;

	sa_tag = container_of(&ethhdr->h_proto, struct eip_sa_tag, etype);

	xs = eip_rx_xs_get(ndev_to_ipsec(skb->dev), sa_tag_to_index(sa_tag));
	if (!xs)
		return -EINVAL;

	sp = secpath_set(skb);
	if (!sp) {
		pr_err("EIP IPSEC: Failed to set secpath\n");
		xfrm_state_put(xs);
		return -EFAULT;
	}

	sp->xvec[sp->len++] = xs;
	sp->olen++;

	xo = xfrm_offload(skb);
	xo->status = CRYPTO_SUCCESS;
	xo->flags = CRYPTO_DONE;

	return 0;
}

/**
 * __locate_ip_hdr - Parses ethernet headers recursively in order to locate the
 *                   start of an IP v4/v6 packet.
 *
 * @outer_proto: Location of outer ether type
 * @inner_proto: [out] Returns the location of inner ether type that identifies either
 *               IPv4 or IPv6 packet
 *
 * Returns pointer to the start of IP packet/header.
 */
static u8 *__locate_ip_hdr(u8 *outer_proto, u8 **inner_proto)
{
	u8 next_off = 0;

	switch (ntohs(*(__be16 *)outer_proto)) {
	case ETH_P_IP:
	case ETH_P_IPV6:
		*inner_proto = outer_proto;
		break;

	case ETH_P_8021Q:
	case ETH_P_QINQ1:
		next_off = VLAN_HLEN;
		break;

	default:
		return NULL;
	}

	if (!next_off)
		return outer_proto + ETH_TLEN;

	return __locate_ip_hdr(outer_proto + next_off, inner_proto);
}

/**
 * eip_ipsec_fixup_rx_skb - Fix up ingress IPsec ethernet frame
 *
 * @skb: Skbuff containing the ethernet frame to be passed in for fixup just before
 *       forwarding to the network stack
 *
 * Ingress IPsec (ESP) packet that is successfully processed by EIP will have an EIP
 * SA Tag header inserted inside the ethernet header. See: struct eip_ethhdr. This
 * function detects the presence of such a tag, removes the tag along with outer IP
 * header. In addition, skb is marked as authenticated by explicitly setting the
 * skb sec path so that kernel xfrm can be bypassed.
 *
 * Input Packet:
 *           |-----------------------------------|
 *           | Ethernet DA (6B)                  |
 *           | Ethernet SA (6B)                  |
 *           [ EIP SA Tag (4B)                   ] --> will be removed
 *           | Ether Type (2B)                   |
 *           [ Outer IP v4/v6 Header             ] --> will be removed
 *           | (Unencrypted) Inner IP packet     |
 *           |-----------------------------------|
 *
 * Output Packet:
 *           |-----------------------------------|
 *           | Ethernet DA (6B)                  |
 *           | Ethernet SA (6B)                  |
 *           | Ether Type (2B)                   |
 *           | (Unencrypted) Inner IP packet     |
 *           |-----------------------------------|
 *
 */
int eip_ipsec_fixup_rx_skb(struct sk_buff *skb)
{
	int rc;
	struct eip_ethhdr *ethhdr = (struct eip_ethhdr *)eth_hdr(skb);
	u8 *outer_proto, *inner_proto, *outer_ip, *inner_ip;
	u16 eth_proto_len, outer_ip_len;
	u8 *new_eth_hdr, *new_outer_proto;

	/* If the frame does not contain SA Tag, we forward to network stack without any
	 * modification or sec path assigned to the skb, and let the stack perform any
	 * required authentication of the packet.
	 */
	if (htons(ethhdr->sa_tag.etype) != eip_satag_etype)
		return 0;

	rc = eip_ipsec_set_secpath(skb);
	if (rc)
		return rc;

	skb_push(skb, ETH_HLEN);

	eip_dump_skb(skb, "Fixup Rx Begin");

	outer_proto = (u8 *)&ethhdr->proto;

	outer_ip = __locate_ip_hdr(outer_proto, &inner_proto);
	if (!outer_ip)
		return -ENOENT;

	eth_proto_len = outer_ip - outer_proto;

	/* EIP does not support outer IP with options/extension headers, so we are safe
	 * to assume the length of outer IP to just include their main header sizes.
	 */
	switch (ntohs(*(__be16 *)inner_proto)) {
	case ETH_P_IP:
		outer_ip_len = sizeof(struct iphdr);
		break;
	case ETH_P_IPV6:
		outer_ip_len = sizeof(struct ipv6hdr);
		break;
	default:
		return -EFAULT;
	}

	inner_ip = outer_ip + outer_ip_len;

	/* Overwrite outer IP header with ethernet header */
	new_outer_proto = inner_ip - eth_proto_len;
	memmove(new_outer_proto, outer_proto, eth_proto_len);

	new_eth_hdr = new_outer_proto - ETH_ALEN * 2;
	memmove(new_eth_hdr, ethhdr, ETH_ALEN * 2);

	/* We removed SA tag and outer IP header */
	skb_pull(skb, sizeof(ethhdr->sa_tag) + outer_ip_len);

	eip_dump_skb(skb, "Fixup Rx End");

	skb->protocol = eth_type_trans(skb, skb->dev);

	return 0;
}
