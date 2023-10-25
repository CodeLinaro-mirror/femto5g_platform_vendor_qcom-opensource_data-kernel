/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _EIP_IPSEC_H_
#define _EIP_IPSEC_H_

#include <linux/list.h>

#include "eip_device.h"

#include "api_cfye.h"
#include "api_secy.h"

#define EIP_SATAG_ETYPE_DEFAULT 0x9999

/* Use this struct for accessing data on wire */
struct eip_sa_tag {
	__be16 etype;
	__be16 info;
} __packed;

/* Ethernet header after SA Tag inserted */
struct eip_ethhdr {
	u8 dest[ETH_ALEN];
	u8 source[ETH_ALEN];
	struct eip_sa_tag sa_tag;
	__be16 proto;
} __packed;

/* use this structure for local processing but use cpu_to_be*() to convert etype and info
 * to wire format.
 */
union eip_sa_tag_info {
	u16 info;
	struct {
		u16 vport : 9;
		u16 rsvd : 8;
		u16 bypass : 1;
	} egress;
	struct {
		u16 sa : 10;
		u16 rsvd : 1;
		u16 mtt : 4;
		u16 late_hdr : 1;
	} ingress;
} __packed;

struct eip_ipsec_link;

struct eip_xfrm_state {
	struct list_head eip_xs_l;

	struct net_device *ndev;
	struct eip_channel *channel;
	struct eip_ipsec_link *ilink;

	bool inbound;
	bool enable_esn;
	struct xfrm_state *xs;
	struct eip_sa_tag sa_tag; /* prepared for fast egress processing */

	unsigned int vport;
	CfyE_vPortHandle_t vport_h;

	CfyE_RuleHandle_t rule_h;
	SecY_SAHandle_t sa_h;
	unsigned int sa_index;
};

#define MAX_MTT_ENTRIES 14

struct eip_ipsec_link {
	struct list_head eip_xs_l;

	rwlock_t lock;
	struct eip_link *link;

	unsigned int mtt_index;
};

extern u16 eip_satag_etype;

static inline struct eip_ipsec_link *ndev_to_ipsec(struct net_device *ndev)
{
	struct eip_link *link = (struct eip_link *)mtip_security_get_priv(ndev);
	struct eip_ipsec_link *ilink =
		(struct eip_ipsec_link *)link->ipsec_priv;
	return ilink;
}

#ifdef CONFIG_XFRM_OFFLOAD
int eip_ipsec_init_link(struct eip_link *link);
void eip_ipsec_deinit_link(struct eip_link *link);
int eip_ipsec_fixup_rx_skb(struct sk_buff *skb);
int eip_ipsec_fixup_tx_skb(struct sk_buff *skb);
#else
static inline int eip_ipsec_init_link(struct eip_link *link)
{
	return 0;
}
static inline void eip_ipsec_deinit_link(struct eip_link *link)
{
}
static inline int eip_ipsec_fixup_rx_skb(struct sk_buff *skb)
{
	return 0;
}
static inline int eip_ipsec_fixup_tx_skb(struct sk_buff *skb)
{
	return 0;
}
#endif // CONFIG_XFRM_OFFLOAD

#endif // _EIP_IPSEC_H_
