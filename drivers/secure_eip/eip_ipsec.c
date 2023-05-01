// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include <linux/module.h>
#include <linux/rwlock.h>

#include <net/xfrm.h>

#include "aes.h"
#include "clib.h"
#include "sa_builder_macsec.h"

#include "eip_ipsec.h"

#define EIP_IPSEC_SALT_SIZE 32

#ifndef EIP_SATAG_ETYPE_DEFAULT
#define EIP_SATAG_ETYPE_DEFAULT 0x9999
#endif

u16 eip_satag_etype = EIP_SATAG_ETYPE_DEFAULT;
module_param(eip_satag_etype, ushort, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(eip_satag_etype,
		 "Ether Type used for EIP SA Tag insertion/detection");

#ifndef EIP_IKE_PORT_DEFAULT
#define EIP_IKE_PORT_DEFAULT 500
#endif

u16 eip_ike_port = EIP_IKE_PORT_DEFAULT;
module_param(eip_ike_port, ushort, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(eip_ike_port,
		 "UDP port number that EIP uses for bypassing IKE packets");

#ifndef EIP_NAT_PORT_DEFAULT
#define EIP_NAT_PORT_DEFAULT 4500
#endif

u16 eip_nat_port = EIP_NAT_PORT_DEFAULT;
module_param(eip_nat_port, ushort, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(eip_nat_port,
		 "UDP port number that EIP uses for detecting NAT-T packets");

static bool dump_xs = false;
module_param(dump_xs, bool, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(dump_xs, "Dump xfrm state info (Only use for debugging)");

static void eip_dump_xs(const struct xfrm_state *xs)
{
	if (!dump_xs)
		return;

	pr_info("EIP IPSEC: props.aalgo %x\n", xs->props.aalgo);
	pr_info("EIP IPSEC: props.ealgo %x\n", xs->props.ealgo);
	pr_info("EIP IPSEC: props.calgo %x\n", xs->props.calgo);

	pr_info("EIP IPSEC: props.flags %x\n", xs->props.flags);
	pr_info("EIP IPSEC: props.family %x\n", xs->props.family);
	pr_info("EIP IPSEC: props.mode %x\n", xs->props.mode);

	pr_info("EIP IPSEC: id.proto %x\n", xs->id.proto);

	pr_info("EIP IPSEC: encap %px\n", xs->encap);
	pr_info("EIP IPSEC: aead %px\n", xs->aead);

	pr_info("EIP IPSEC: aead->alg_icv_len %u\n", xs->aead->alg_icv_len);
	pr_info("EIP IPSEC: aead->alg_key_len %u\n", xs->aead->alg_key_len);

	pr_info("EIP IPSEC: tfcpad %u\n", xs->tfcpad);
	pr_info("EIP IPSEC: geniv '%s'\n", xs->geniv);
}

static void print_words(const char *heading, const u32 *words, u32 word_count)
{
	u32 i;

	pr_info("%s:", heading);
	for (i = 0; i < word_count; i++) {
		if ((i % 4) == 0)
			pr_cont("\n%i:");

		pr_cont(" %08x", words[i]);
	}
	pr_cont("\n");
}

static bool eip_ipsec_supported(unsigned int devid)
{
	CfyE_Status_t CfyE_Rc;
	CfyE_Device_Limits_t Device_Limits;

	CfyE_Rc = CfyE_Device_Limits_Get(devid, &Device_Limits);
	if (CfyE_Rc != CFYE_STATUS_OK) {
		pr_err("EIP IPSEC: CfyE_Device_Limits returned error %d\n",
		       CfyE_Rc);
		return false;
	}

	if (Device_Limits.fIPsec)
		pr_info("EIP IPSEC: IPsec is supported on DevID %u\n", devid);
	else
		pr_info("EIP IPSEC: IPsec is not supported on DevID %u\n",
			devid);

	return Device_Limits.fIPsec;
}

static int __cfye_set_mode(unsigned int devid, unsigned int channel,
			   bool inbound, bool ipsec)
{
	CfyE_Status_t CfyE_Rc;
	CfyE_Device_t DeviceParams;
	CfyE_HeaderParser_t HeaderParams;
	CfyE_Device_Control_t DeviceCtrl;
	CfyE_IPSEC_Parser_t IPsecParserParams;
	CfyE_EgressHeader_t EgressHdrParams;
	CfyE_Device_Exceptions_t DevExceptions;

	ZEROINIT(DeviceParams);
	ZEROINIT(HeaderParams);
	ZEROINIT(DeviceCtrl);
	ZEROINIT(IPsecParserParams);
	ZEROINIT(EgressHdrParams);
	ZEROINIT(DevExceptions);

	DevExceptions.fShouldSecure = false;
	DevExceptions.DropAction = CFYE_DO_NOT_DROP;
	DevExceptions.ECCDropAction = CFYE_DROP_CRC_ERROR;

	DeviceCtrl.fIPsec = ipsec; /* IPsec Mode */
	DeviceCtrl.Exceptions_p = &DevExceptions;

	IPsecParserParams.fParseIP = true;
	IPsecParserParams.fParseUDP = false;
	IPsecParserParams.fParseNAT = false;

	IPsecParserParams.fParseESP = true;

	IPsecParserParams.fParseIKE = true;
	IPsecParserParams.fParseNATIKE = true;
	IPsecParserParams.fParseNATKeepAlive = true;
	IPsecParserParams.IKE_Port = eip_ike_port;
	IPsecParserParams.NAT_Port = eip_nat_port;
	IPsecParserParams.fVerifyUDPChkSum = false;
	IPsecParserParams.fMACDACheck = false;

	if (!inbound) {
		EgressHdrParams.EgressHeaderEtype = eip_satag_etype;
		EgressHdrParams.fEnable = true;

		HeaderParams.EgressHeader_p = &EgressHdrParams;
	}

	HeaderParams.IPsec_Parser_p = &IPsecParserParams;

	DeviceParams.HeaderParser_p = &HeaderParams;
	DeviceParams.Control_p = &DeviceCtrl;

	CfyE_Rc = CfyE_Device_Update(devid, channel, &DeviceParams);
	if (CfyE_Rc != CFYE_STATUS_OK) {
		pr_err("EIP IPSEC: Failed, CfyE_Device_Update()=%d\n", CfyE_Rc);
		return -EFAULT;
	}

	return 0;
}

static int __secy_set_mode(unsigned int devid, unsigned int channel, bool ipsec)
{
	SecY_Status_t rc;
	SecY_Device_Params_t DeviceConf;
	SecY_ChannelConf_t ChannelConf;
	SecY_Channel_t ChannelParams;

	ZEROINIT(ChannelConf);
	ZEROINIT(DeviceConf);
	ZEROINIT(ChannelParams);

	rc = SecY_Channel_Config_Get(devid, channel, &ChannelParams);
	if (rc != SECY_STATUS_OK) {
		pr_err("EIP IPSEC: SecY Device config not read, error=%d\n",
		       rc);
		return -EFAULT;
	}

	ChannelParams.ChannelId = channel;
	ChannelParams.fIPsec = ipsec; /* IPsec Mode */
	ChannelParams.fLowLatencyBypass = !ipsec;
	ChannelParams.fShouldSecure = false;

	ChannelConf.Params.ChannelCount = 1;
	ChannelConf.Params.Channel_p = &ChannelParams;

	DeviceConf.ChConf_p = &ChannelConf;

	rc = SecY_Device_Update(devid, &DeviceConf);
	if (rc != SECY_STATUS_OK) {
		pr_err("EIP IPSEC: SecYDevice could not be configured, error=%d\n",
		       rc);
		return -EFAULT;
	}

	pr_info("EIP IPSEC: SecY Device configured successfully\n");

	return 0;
}

static int eip_ipsec_set_mode(struct eip_xfrm_state *eip_xs, bool ipsec)
{
	unsigned int devid = eip_devid(eip_xs->channel);
	unsigned int channel = eip_chid(eip_xs->channel);

	return __secy_set_mode(devid, channel, ipsec) |
	       __cfye_set_mode(devid, channel, eip_xs->inbound, ipsec);
}

static int eip_ipsec_alloc_vport(unsigned int devid, bool inbound,
				 CfyE_vPortHandle_t *vport_h,
				 unsigned int *vport)
{
	CfyE_Status_t rc;
	CfyE_vPort_t vport_params;

	ZEROINIT(vport_params);

	if (!inbound)
		vport_params.PktExtension = 1;

	rc = CfyE_vPort_Add(devid, vport_h, &vport_params, CYFE_MODE_IPSEC);
	if (rc != CFYE_STATUS_OK) {
		pr_err("EIP IPSEC: Failed, CfyE_vPort_Add()=%d\n", rc);
		return -EFAULT;
	}

	rc = CfyE_vPortIndex_Get(*vport_h, vport);
	if (rc) {
		pr_err("EIP IPSEC: Failed to get vport index\n");
		CfyE_vPort_Remove(devid, vport_h);
		return -EFAULT;
	}

	pr_info("EIP IPSEC:  vPort %u added\n", *vport);

	return 0;
}

#define EIP_CRYPTO_AES_GCM_128 0x5
#define EIP_CRYPTO_AES_GCM_256 0x7

static void eip_ipsec_destroy_tr(u32 *tr, unsigned int wc)
{
	kfree_sensitive(tr);
}

static u32 *eip_ipsec_build_tr(bool inbound, u8 *key, unsigned int key_len,
			       u8 *salt, u32 spi, bool insert_satag,
			       unsigned int *wc)
{
	u32 *tr = NULL;
	unsigned int word_count;
	SABuilder_Status_t rc;
	SABuilder_Direction_t sab_dir;
	SABuilder_Params_t sab_params;

	ZEROINIT(sab_params);

	sab_dir = inbound ? SAB_DIRECTION_INGRESS : SAB_DIRECTION_EGRESS;

	rc = SABuilder_InitParams(&sab_params, 0, sab_dir, SAB_OP_IPSEC);
	if (rc != SAB_STATUS_OK) {
		pr_err("EIP IPSEC: SAB InitParams Failed %d\n", rc);
		return NULL;
	}

	if (inbound) {
		sab_params.WindowSize = 128;
		sab_params.flags = SAB_IPSEC_FLAG_PAD_CHECK;

		if (!insert_satag)
			sab_params.flags |= SAB_IPSEC_DISABLE_SA_TAG_INSERT;
	}

	sab_params.Key_p = key;
	sab_params.KeyByteCount = key_len;
	sab_params.Salt_p = salt;
	sab_params.SPI = spi;

	rc = SABuilder_GetSize(&sab_params, &word_count);
	if (rc != SAB_STATUS_OK) {
		pr_err("EIP IPSEC: SAB GetSize Failed %d\n", rc);
		return NULL;
	}

	pr_info("EIP IPSEC: Transform 32-bit word count %d\n", word_count);

	tr = kzalloc(word_count * sizeof(u32), GFP_KERNEL);
	if (!tr)
		return NULL;

	rc = SABuilder_BuildSA(&sab_params, tr, AES_Encrypt);
	if (rc != SAB_STATUS_OK) {
		pr_err("EIP IPSEC: SAB BuildSA Failed %d\n", rc);
		eip_ipsec_destroy_tr(tr, word_count);
		return NULL;
	}

	print_words("EIP IPSEC: Transform Record", tr, word_count);

	*wc = word_count;

	return tr;
}

static int eip_ipsec_add_sa(unsigned int devid, unsigned int vport,
			    bool inbound, const struct xfrm_state *xs,
			    SecY_SAHandle_t *sa_h, unsigned int *sa_index)
{
	SecY_Status_t rc = 0;
	SecY_SA_t sa_params;
	u32 *tr = NULL;
	unsigned int word_count;
	u8 *key = &xs->aead->alg_key[0];
	unsigned int key_len =
		(xs->aead->alg_key_len - EIP_IPSEC_SALT_SIZE) / BITS_PER_BYTE;
	u8 *salt = &xs->aead->alg_key[key_len];
	u32 spi = be32_to_cpu(xs->id.spi);

	ZEROINIT(sa_params);

	/* Note: DDK presently does not use the following egress/ingress SA param fields
	 * in the data structure.
	 *
	 * SecY_SA_IPsec_E_t:
	 *  - fRollOverMode
	 *  - fEncrAuth
	 *  - CryptoAlg
	 *  - fReplayCheck
	 *  - fIgHdrInsert
	 *
	 * SecY_SA_IPsec_I_t:
	 *  - fRetainPad
	 *  - fPadCheck
	 *  - fReplayCheck
	 *  - fIgHdrInsert
	 *
	 * To enable such features, we may need to set relevant SABuilder_Params_t.flags
	 * bits, if the feature flag is not automatically set by SABuilder_BuildSA() API.
	 * Refer sa_builder_internal.h to see all available SAB_CW0_* bits and look into
	 * SABuilder_BuildSA() implementation on how to set relevant CW (control word)
	 * bits in the TR (transform record).
	 */

	tr = eip_ipsec_build_tr(inbound, key, key_len, salt, spi, true,
				&word_count);
	if (tr == NULL) {
		pr_err("EIP IPSEC: Failed to create transformation record\n");
		return -EFAULT;
	}

	sa_params.TransformRecord_p = tr;
	sa_params.SA_WordCount = word_count;

	if (!inbound) {
		SecY_SA_IPsec_E_t *egress_params =
			&sa_params.Params.IPsecEgress;

		sa_params.ActionType = SECY_SA_ACTION_IPSEC_EGRESS;
		sa_params.DropType = SECY_SA_DROP_INTERNAL;
		sa_params.DestPort = SECY_PORT_COMMON;

		egress_params->fRollOverMode = true;
		egress_params->fEncrAuth = true;

		egress_params->fUpdateUDP = true;
		egress_params->fUpdateIP = true;
		egress_params->fNAT_UDP = false;
		egress_params->fOuterIPHdr = (xs->props.family == AF_INET6);
		egress_params->fConfProtect = true;
		egress_params->fProtectFrames = true;
	} else {
		SecY_SA_IPsec_I_t *ingress_params =
			&sa_params.Params.IPsecIngress;

		sa_params.ActionType = SECY_SA_ACTION_IPSEC_INGRESS;
		sa_params.DropType = SECY_SA_DROP_CRC_ERROR;
		sa_params.DestPort = SECY_PORT_CONTROLLED;

		ingress_params->fReplayProtect = true;
		ingress_params->fConfProtect = true;
		ingress_params->fPadNotValidDrop = true;
		ingress_params->fPadLenFailDrop = true;
		ingress_params->fUpdateIP = true;
		ingress_params->fUpdateTTL = false;
	}

	rc = SecY_SA_Add(devid, vport, sa_h, &sa_params);
	if (rc != SECY_STATUS_OK) {
		pr_err("EIP IPSEC: Failed, SecY_SA_Add()=%d\n", rc);
		goto out;
	}

	rc = SecY_SAIndex_Get(*sa_h, sa_index, NULL);
	if (rc != SECY_STATUS_OK) {
		pr_err("EIP IPSEC: Failed to get SA Index=%d\n", rc);
		(void)SecY_SA_Remove(devid, *sa_h);
		goto out;
	}

	pr_info("EIP IPSEC: SA with Transform Record added\n");

out:
	eip_ipsec_destroy_tr(tr, word_count);

	return rc;
}

static int eip_install_cfye_rule(struct eip_xfrm_state *eip_xs)
{
	CfyE_Status_t rc;
	CfyE_Rule_t rule_params;
	const struct xfrm_state *xs = eip_xs->xs;
	unsigned int devid = eip_devid(eip_xs->channel);
	unsigned int channel = eip_chid(eip_xs->channel);

	if (!eip_xs->inbound)
		return -EINVAL;

	ZEROINIT(rule_params);

	rule_params.Policy.vPortHandle = eip_xs->vport_h;

	rule_params.Key.PacketType = CFYE_RULE_PKT_TYPE_IPSEC;
	rule_params.Key.NumTags = 0;
	rule_params.Key.ChannelID = channel;

	rule_params.Mask.PacketType = CFYE_RULE_PKT_TYPE_MASK;
	rule_params.Mask.NumTags = CFYE_RULE_NUMTAGS_MASK;
	rule_params.Mask.ChannelID = CFYE_RULE_CHANNEL_ID_MASK;

	/* Let's not match against ethernet DA in order to accept broadcast/multicast
	 * ethernet frames.
	 */
	rule_params.Data[0] = *(u32 *)eip_xs->ndev->dev_addr;
	rule_params.Data[1] = *(u16 *)(eip_xs->ndev->dev_addr + 4);
	rule_params.DataMask[0] = 0x0;
	rule_params.DataMask[1] = 0x0;

	rule_params.Data[2] = be32_to_cpu(xs->id.spi);
	rule_params.DataMask[2] = 0xffffffff;

	/* Disable MTT match as we do not need to support virtualization, and therefore
	 * not expect more than one SPI namespace.
	 */
	rule_params.Data[3] = 0;
	rule_params.DataMask[3] = 0x0;

	rc = CfyE_Rule_Add(devid, eip_xs->vport_h, &eip_xs->rule_h,
			   &rule_params);
	if (rc != CFYE_STATUS_OK) {
		pr_err("EIP IPSEC: Failed, CfyE_Rule_Add()=%d\n", rc);
		return -EFAULT;
	}

	rc = CfyE_Rule_Enable(devid, eip_xs->rule_h, true);
	if (rc != CFYE_STATUS_OK) {
		pr_err("EIP IPSEC: Failed, CfyE_Rule_Enable()=%d\n", rc);
		return -EFAULT;
	}

	return 0;
}

static int __eip_xdo_dev_state_add(struct eip_xfrm_state *eip_xs)
{
	int rc;
	unsigned int devid = eip_devid(eip_xs->channel);
	unsigned int channel = eip_chid(eip_xs->channel);

	/* TODO: set mode need to be done only once per channel */
	rc = eip_ipsec_set_mode(eip_xs, true);
	if (rc) {
		pr_err("EIP IPSEC: Failed to setup ipsec mode\n");
		return -EFAULT;
	}

	rc = eip_ipsec_alloc_vport(devid, eip_xs->inbound, &eip_xs->vport_h,
				   &eip_xs->vport);
	if (rc) {
		pr_err("EIP IPSEC: Failed to setup ipsec vport\n");
		return -EFAULT;
	}

	/* Generate Egress SA Tag for insertion in skb xmit */
	if (!eip_xs->inbound) {
		union eip_sa_tag_info tag_info;

		ZEROINIT(tag_info);

		tag_info.egress.bypass = false;
		tag_info.egress.vport = eip_xs->vport;

		eip_xs->sa_tag.info = cpu_to_be16(tag_info.info);
	}

	rc = eip_ipsec_add_sa(devid, eip_xs->vport, eip_xs->inbound, eip_xs->xs,
			      &eip_xs->sa_h, &eip_xs->sa_index);
	if (rc) {
		pr_err("EIP IPSEC: Failed to install SA\n");
		return -EFAULT;
	}

	if (eip_xs->inbound && eip_install_cfye_rule(eip_xs)) {
		pr_err("EIP IPSEC: Failed to install cfye rules\n");
		return -EFAULT;
	}

	return 0;
}

static int eip_ipsec_validate_sa(const struct xfrm_state *xs)
{
	if (xs->props.mode != XFRM_MODE_TUNNEL) {
		pr_err("EIP IPSEC: EIP supports only tunnel mode");
		return -EINVAL;
	}

	if (xs->id.proto != IPPROTO_ESP) {
		pr_err("EIP IPSEC: EIP supports only ESP offload");
		return -EINVAL;
	}

	if (xs->props.aalgo != SADB_AALG_NONE ||
	    xs->props.ealgo != SADB_X_EALG_AES_GCM_ICV16 ||
	    xs->props.calgo != SADB_X_CALG_NONE) {
		pr_err("EIP IPSEC: EIP supports only AES GCM algo with 128-bit ICV");
		return -EINVAL;
	}

	if (xs->aalg || xs->ealg || xs->calg || !xs->aead) {
		pr_err("EIP IPSEC: EIP supports only AEAD algo");
		return -EINVAL;
	}

	if (xs->aead->alg_icv_len != 128) {
		pr_err("EIP IPSEC: EIP supports only 128-bit ICV len");
		return -EINVAL;
	}

	if ((xs->aead->alg_key_len - EIP_IPSEC_SALT_SIZE) != 128 &&
	    (xs->aead->alg_key_len - EIP_IPSEC_SALT_SIZE) != 256) {
		pr_err("EIP IPSEC: EIP supports only 128/256-bit keys");
		return -EINVAL;
	}

	if (xs->tfcpad) {
		pr_err("EIP IPSEC: EIP does not support TFC padding");
		return -EINVAL;
	}

	return 0;
}

static int eip_xdo_dev_state_add(struct xfrm_state *xs)
{
	int rc;
	struct eip_xfrm_state *eip_xs;
	struct net_device *ndev = xs->xso.real_dev;
	struct eip_ipsec_link *ilink = ndev_to_ipsec(ndev);

	pr_debug("EIP IPSEC: %s\n", __func__);

	eip_dump_xs(xs);

	rc = eip_ipsec_validate_sa(xs);
	if (rc)
		return rc;

	eip_xs = kzalloc(sizeof(*eip_xs), GFP_KERNEL);
	if (!eip_xs)
		return -ENOMEM;

	eip_xs->ndev = ndev;
	eip_xs->ilink = ilink;

	eip_xs->xs = xs;
	eip_xs->inbound = (xs->xso.dir == XFRM_DEV_OFFLOAD_IN);
	eip_xs->sa_tag.etype = cpu_to_be16(eip_satag_etype);
	eip_xs->channel = eip_xs->inbound ? &ilink->link->rx : &ilink->link->tx;

	rc = __eip_xdo_dev_state_add(eip_xs);
	if (rc) {
		kfree(eip_xs);
	} else {
		xs->xso.offload_handle = (unsigned long)eip_xs;

		write_lock_bh(&ilink->lock);
		list_add(&eip_xs->eip_xs_l, &ilink->eip_xs_l);
		write_unlock_bh(&ilink->lock);
	}

	return rc;
}

static void eip_xdo_dev_state_delete(struct xfrm_state *xs)
{
	SecY_Status_t secy_rc;
	CfyE_Status_t cfye_rc;
	struct eip_xfrm_state *eip_xs =
		(struct eip_xfrm_state *)xs->xso.offload_handle;
	struct eip_ipsec_link *ilink = eip_xs->ilink;
	unsigned int devid;

	pr_debug("EIP IPSEC: %s\n", __func__);

	if (!eip_xs)
		return;

	write_lock_bh(&ilink->lock);
	list_del(&eip_xs->eip_xs_l);
	write_unlock_bh(&ilink->lock);

	devid = eip_devid(eip_xs->channel);

	if (eip_xs->inbound) {
		cfye_rc = CfyE_Rule_Disable(devid, eip_xs->rule_h, true);
		if (cfye_rc != CFYE_STATUS_OK)
			pr_err("EIP IPSEC: Unable to disable CfyE rule\n");

		cfye_rc = CfyE_Rule_Remove(devid, eip_xs->rule_h);
		if (cfye_rc != CFYE_STATUS_OK)
			pr_err("EIP IPSEC: Unable to remove CfyE rule\n");
	}

	secy_rc = SecY_SA_Remove(devid, eip_xs->sa_h);
	if (secy_rc != SECY_STATUS_OK)
		pr_err("EIP IPSEC: Unable to remove SecY SA\n");

	cfye_rc = CfyE_vPort_Remove(devid, eip_xs->vport_h);
	if (cfye_rc != CFYE_STATUS_OK)
		pr_err("EIP IPSEC: Unable to remove CfyE port\n");

	eip_xs->xs = NULL;
}

static void eip_xdo_dev_state_free(struct xfrm_state *xs)
{
	struct eip_xfrm_state *eip_xs =
		(struct eip_xfrm_state *)xs->xso.offload_handle;

	pr_debug("EIP IPSEC: %s\n", __func__);

	xs->xso.offload_handle = 0;
	kfree_sensitive(eip_xs);
}

static bool eip_xdo_dev_offload_ok(struct sk_buff *skb, struct xfrm_state *xs)
{
	pr_debug("EIP IPSEC: %s\n", __func__);

	return true;
}

static void eip_xdo_dev_state_advance_esn(struct xfrm_state *x)
{
	pr_debug("EIP IPSEC: %s\n", __func__);
}

const struct xfrmdev_ops eip_xfrm_ops = {
	.xdo_dev_state_add = eip_xdo_dev_state_add,
	.xdo_dev_state_delete = eip_xdo_dev_state_delete,
	.xdo_dev_state_free = eip_xdo_dev_state_free,
	.xdo_dev_offload_ok = eip_xdo_dev_offload_ok,
	.xdo_dev_state_advance_esn = eip_xdo_dev_state_advance_esn,
};

/* Initialized IPsec private data for a single link */
int eip_ipsec_init_link(struct eip_link *link)
{
	struct net_device *net_dev = link->ndev;
	unsigned int rx_devid = eip_devid(&link->rx);
	unsigned int tx_devid = eip_devid(&link->tx);
	struct eip_ipsec_link *ilink;

	if (!eip_ipsec_supported(rx_devid) || !eip_ipsec_supported(tx_devid)) {
		pr_err("EIP IPSEC: %s does not support ipsec\n", net_dev->name);
		return -EINVAL;
	}

	ilink = kzalloc(sizeof(*ilink), GFP_KERNEL);
	if (!ilink)
		return -ENOMEM;

	INIT_LIST_HEAD(&ilink->eip_xs_l);
	rwlock_init(&ilink->lock);
	ilink->link = link;

	link->ipsec_priv = ilink;

	net_dev->xfrmdev_ops = &eip_xfrm_ops;
	net_dev->features |= NETIF_F_HW_ESP;
	net_dev->hw_enc_features |= NETIF_F_HW_ESP;

	return 0;
}

void eip_ipsec_deinit_link(struct eip_link *link)
{
	struct net_device *net_dev = link->ndev;

	net_dev->xfrmdev_ops = NULL;
	net_dev->features &= ~NETIF_F_HW_ESP;
	net_dev->hw_enc_features &= ~NETIF_F_HW_ESP;

	kfree(link->ipsec_priv);
}
