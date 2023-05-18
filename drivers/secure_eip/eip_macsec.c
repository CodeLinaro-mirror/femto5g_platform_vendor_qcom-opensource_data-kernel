// SPDX-License-Identifier: GPL-2.0-only

/*
* Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include <net/macsec.h>

#include "eip_macsec.h"
#include "device_internal.h"
#include "api_secy_ext.h"
#include "api_cfye_ext.h"
#include "macsec_eth.h"

#include "aes.h"

/*-----------------------------------------------------------------------*/
#define EIP_MACSEC_SECTAG_OFFSET 12;
#define EIP_MACSEC_EXPANSION_EXPLICIT_SCI 3
#define CONTROL_ETYPE 0x888e /* Ether type for control packets */
#define MACSEC_GET_LINK_ID(device_id, channel) 4 * device_id + channel % 4
#define MAX_CHANNELS_PER_PORT 4
#define STATS_2x32_TO_64(stat_field_Lo, stat_field_Hi)                         \
	(((u64)stat_field_Hi << 32) | stat_field_Lo)
#define SECY_FRAME_VALIDATE_DEFAULT SECY_FRAME_VALIDATE_STRICT
#define vPORT_INDEX_NOT_INITIALIZE 0xFFFFFFFF
#define SA_PN_SEQ_OFFSET 14
#define SA_WORD_COUNT 2
#define MAX_CHANNELS_PER_PORT 4

/* Parameters that specify SA creation. */
typedef struct {
	SABuilder_Direction_t direction;
	SABuilder_Operation_t operation;
	uint32_t flags;
	uint8_t AN;
	uint8_t *Key_p;
	unsigned int KeyByteCount;
	uint8_t *SCI_p;
	uint8_t *SSCI_p;
	uint8_t *Salt_p;
	uint32_t SeqNumLo;
	uint32_t SeqNumHi;
	uint32_t SeqMask;
} da_sa_params_t;

struct macsec_device_info {
	SecY_SAHandle_t SecY_SAHandleDefault;
	CfyE_vPortHandle_t CfyE_vPortHandleDefault;
	unsigned int vPortDefault;
	unsigned int device_id;
	uint8_t SCI_p[8];
	bool init;
};

struct macsec_per_channel_info {
	unsigned int vPort[MACSEC_MAX_SA];
	CfyE_RuleHandle_t CfyE_RuleHandle[MACSEC_MAX_SA];
	SecY_SAHandle_t SecY_SAHandle[MACSEC_MAX_SA];
	uint8_t active[MACSEC_MAX_SA];
	CfyE_vPortHandle_t CfyE_vPortHandle[MACSEC_MAX_SA];
	sci_t secy_sci;
	unsigned int device_id;
	unsigned int channel;
	SecY_SA_t SA_Params[MACSEC_MAX_SA];
	bool associated[MACSEC_MAX_SA];
	uint8_t link_index;
	uint8_t SCI_p[8];
	bool valid;
	uint8_t sa_active_idx;
	uint8_t egress_init_flag;
	unsigned int vPortIndex;
};

struct macsec_priv_data_info {
	struct macsec_device_info device_info[EIP_MAX_PORT];
	struct macsec_per_channel_info channel_info[MACSEC_MAX_LINK_IDS];
};

enum stats_type {
	MACSEC_STATS_DEV,
	MACSEC_STATS_TXSC,
	MACSEC_STATS_TXSA,
	MACSEC_STATS_RXSC,
	MACSEC_STATS_RXSA
};

struct eip_macsec_stats {
	struct macsec_tx_sc_stats tx_sc_stats;
	struct macsec_tx_sa_stats tx_sa_stats;
	struct macsec_rx_sc_stats rx_sc_stats;
	struct macsec_rx_sa_stats rx_sa_stats;
	struct macsec_dev_stats dev_stats;
};

struct macsec_priv_data_info macsec_priv_data;

static inline void get_device_params_from_link_id(u32 link_index, u32 *port_id,
						  u32 *ingress_device,
						  u32 *egress_device,
						  u32 *channel_id)
{
	*port_id = GET_PORT_ID_FROM_LINK_IDX(link_index);
	*ingress_device = GET_INGRESS_ID_FROM_DEVICE_ID(*port_id);
	*egress_device = GET_EGRESS_ID_FROM_DEVICE_ID(*port_id);
	*channel_id = GET_CHANNEL_ID_FROM_LINK_IDX(link_index);
}

static inline void get_ingress_params_from_link_id(u32 link_index, u32 *port_id,
						   u32 *ingress_device,
						   u32 *channel_id)
{
	*port_id = GET_PORT_ID_FROM_LINK_IDX(link_index);
	*ingress_device = GET_INGRESS_ID_FROM_DEVICE_ID(*port_id);
	*channel_id = GET_CHANNEL_ID_FROM_LINK_IDX(link_index);
}

static inline void get_egress_params_from_link_id(u32 link_index, u32 *port_id,
						  u32 *egress_device,
						  u32 *channel_id)
{
	*port_id = GET_PORT_ID_FROM_LINK_IDX(link_index);
	*egress_device = GET_EGRESS_ID_FROM_DEVICE_ID(*port_id);
	*channel_id = GET_CHANNEL_ID_FROM_LINK_IDX(link_index);
}

static inline struct macsec_per_channel_info *
get_eip_channel_info(unsigned int device_id, unsigned int channel_id)
{
	unsigned int temp_eip_link_id =
		MACSEC_GET_LINK_ID(device_id, channel_id);
	return &macsec_priv_data.channel_info[temp_eip_link_id];
}

static SecY_SAHandle_t SecY_SAHandle;
static CfyE_vPortHandle_t CfyE_vPortHandle;
static unsigned int vPortIndex;
static CfyE_RuleHandle_t CfyE_RuleHandle;

#ifdef SECURE_MACSEC_DEBUG

static void dump_txsc(struct macsec_context *ctx)
{
	LOG_INFO("****************** %s********************\n", __func__);
	if (ctx->secy == NULL) {
		LOG_CRIT("ctx->secy NULL, return;");
		return;
	}
	LOG_INFO(
		"active %d \n encoding sa %d\n encrypt %d \n send_sci %d\n endstation %d \n scb %d \n",
		ctx->secy->tx_sc.active, ctx->secy->tx_sc.encoding_sa,
		ctx->secy->tx_sc.encrypt, ctx->secy->tx_sc.send_sci,
		ctx->secy->tx_sc.end_station, ctx->secy->tx_sc.scb);
	LOG_INFO("sa[0] 0x%x\n sa[1] 0x%x\n sa[2] 0x%x\n",
		 ctx->secy->tx_sc.sa[0], ctx->secy->tx_sc.sa[1],
		 ctx->secy->tx_sc.sa[2]);
}

static void dump_rxsc(struct macsec_context *ctx)
{
	LOG_INFO("****************** %s********************\n", __func__);

	if (ctx->rx_sc == NULL) {
		LOG_CRIT("ctx->rx_sc is NULL; return;");
		return;
	}
	LOG_INFO(
		" next ptr 0x%x\n sci 0x%x \n active %d \n sa[0] 0x%x\n, sa[1] 0x%x\n sa[2] 0x%x\n",
		ctx->rx_sc->next, ctx->rx_sc->sci, ctx->rx_sc->active,
		ctx->rx_sc->sa[0], ctx->rx_sc->sa[1], ctx->rx_sc->sa[2]);
}

static void dump_secy(struct macsec_context *ctx)
{
	LOG_INFO("****************** %s********************\n", __func__);
	LOG_INFO("AN = %d\n", ctx->sa.assoc_num);
	LOG_INFO(" n_rx_sc = %d\n sci = 0x%x\n validate frames = %d\n",
		 ctx->secy->n_rx_sc, ctx->secy->sci,
		 ctx->secy->validate_frames);
	LOG_INFO(
		" xpn %d \n operational = %d\n protect_frames = %d \n replay_protect = %d\n replay_window = %d\n",
		ctx->secy->xpn, ctx->secy->operational,
		ctx->secy->protect_frames, ctx->secy->replay_protect,
		ctx->secy->replay_window);
	dump_txsc(ctx);
	dump_rxsc(ctx);
}

static void dump_rxsa(struct macsec_context *ctx)
{
	/* Dump the received RX SA details */
	LOG_INFO("****************** %s********************\n", __func__);

	LOG_INFO("AN = %d\n", ctx->sa.assoc_num);
	if (ctx->sa.rx_sa == NULL) {
		LOG_CRIT("ctx->sa.rx_sa is NULL; return ");
		return;
	}
	LOG_INFO(
		"ssci = %d\n next_pn = %d\n sc ptr 0x%x\n active = %d \n refcnt %d\n",
		ctx->sa.rx_sa->ssci, ctx->sa.rx_sa->next_pn, ctx->sa.rx_sa->sc,
		ctx->sa.rx_sa->active, ctx->sa.rx_sa->refcnt);
}

static void dump_txsa(struct macsec_context *ctx)
{
	LOG_INFO("****************** %s********************\n", __func__);
	LOG_INFO("AN = %d\n", ctx->sa.assoc_num);
	if (ctx->sa.tx_sa == NULL) {
		LOG_CRIT("ctx->sa.tx_sa is NULL; return ");
		return;
	}
	LOG_INFO("ssci = %d\n next_pn = %d\n active = %d \n refcnt %d\n",
		 ctx->sa.tx_sa->ssci, ctx->sa.tx_sa->next_pn,
		 ctx->sa.tx_sa->active, ctx->sa.tx_sa->refcnt);
}

static void dump_ctx_values(struct macsec_context *ctx, bool dump)
{
	/* For debug purpose only, dump all the values of the context related to macsec */
	if (dump == false)
		return;

	if (NULL == ctx->secy) {
		LOG_CRIT("WPA NULL ctx->secy\n");
		return;
	}

	LOG_INFO(
		"%s: n_rx_sc = %d \n sci = %lu \n key_len = %d \n icv_len = %d\n",
		__func__, ctx->secy->n_rx_sc, ctx->secy->sci,
		ctx->secy->key_len, ctx->secy->icv_len);
	LOG_INFO(
		"validate_frames = %d\n xpn=%d \n operational = %d \nprotect_frames=%d\n replay_protect = %d\n",
		ctx->secy->validate_frames, ctx->secy->xpn,
		ctx->secy->operational, ctx->secy->protect_frames,
		ctx->secy->replay_protect);
	LOG_INFO(
		"replay_window = %d\n tx_sc->active = %d\n tx_sc->encoding_sa = %d\n tx_sc->encrypt = %d\n tx_sc->send_sci=%d",
		ctx->secy->replay_window, ctx->secy->tx_sc.active,
		ctx->secy->tx_sc.encoding_sa, ctx->secy->tx_sc.encrypt,
		ctx->secy->tx_sc.send_sci);
	LOG_INFO("tx_sc->end_station = %d\n", ctx->secy->tx_sc.end_station);

	LOG_INFO("ctx->rx_sc =0x%x\n ctx->sa.rx_sa 0x%x\n ctx->sa.tx_sa 0x%x\n",
		 ctx->rx_sc, ctx->sa.rx_sa, ctx->sa.tx_sa);
	{
		uint32_t i = 0;

		for (i = 0; i < 4; ++i) // MAX SA of 4
		{
			LOG_INFO("tx_sc->sa[0]= 0x%x\n ",
				 ctx->secy->tx_sc.sa[i]);

			if (ctx->secy->tx_sc.sa[i] != NULL) {
				uint8_t j = 0;
				for (j = 0; j < MACSEC_KEYID_LEN; ++j)
					LOG_INFO("Key [j]=%d",
						 ctx->secy->tx_sc.sa[i]
							 ->key.id[j]);
			}
		}
		if (NULL == ctx->secy->rx_sc) {
			LOG_INFO("WPA NULL NULL return rx_Sc ");
		} else {
			LOG_INFO(
				"WPA rx_Sc = 0x%x rx_sc->sci =0x%x rx_sc->sa[0]=0x%x rx_sc->sa[1]=0x%x rx_sc->sa[2]=0x%x\n",
				ctx->secy->rx_sc, ctx->secy->rx_sc->sci,
				ctx->secy->rx_sc->sa[0],
				ctx->secy->rx_sc->sa[1],
				ctx->secy->rx_sc->sa[2]);
		}
	}
}

#else
static void dump_txsc(struct macsec_context *ctx)
{
}

static void dump_rxsc(struct macsec_context *ctx)
{
}

static void dump_secy(struct macsec_context *ctx)
{
}

static void dump_txsa(struct macsec_context *ctx)
{
}

static void dump_ctx_values(struct macsec_context *ctx, bool dump)
{
}

#endif

static uint32_t *eip_macsec_build_sa(const da_sa_params_t *const params,
				     uint32_t *const SAWordCount_p)
{
	SABuilder_Params_t SAParams;
	SABuilder_Status_t rc;
	unsigned int SAWordCount;
	uint32_t *SABuffer_p;

	memset(&SAParams, 0, sizeof(SAParams));

	rc = SABuilder_InitParams(&SAParams, params->AN, params->direction,
				  params->operation);
	if (rc != SAB_STATUS_OK) {
		LOG_CRIT("eip_macsec_build_sa: SABuilder_InitParams error\n");
		return NULL;
	}

	SAParams.operation = params->operation;
	SAParams.Key_p = params->Key_p;
	SAParams.KeyByteCount = params->KeyByteCount;
	SAParams.SCI_p = params->SCI_p;
	SAParams.SeqNumLo = params->SeqNumLo;
	SAParams.WindowSize = params->SeqMask;

	if (params->flags & SAB_MACSEC_FLAG_SM4) {
		/* The DDK does not contain a software implementation of the SM4
		   block cipher (one for the AES block cipher is included).

		   Therefore the SA Builder cannot perform the HKEY computation
		   internally for SM4. If the application provides an implementation of
		   the SM4 block cipher, it can call the SA Builder with a pointer to
		   such function instead of AES_Encrypt and then the SA Builder could
		   perform the HKEY computation internally.

		   Instead this demo application provides the pre-compute HKEY just
		   after the cipher key.
		 */
		SAParams.HKey_p = params->Key_p + 16;
	}

	SAParams.flags |= params->flags;

	if (params->Salt_p) {
		if (SAB_OP_MACSEC == params->operation)
			SAParams.flags |= SAB_MACSEC_FLAG_LONGSEQ;

		SAParams.Salt_p = params->Salt_p;
		SAParams.SSCI_p = params->SSCI_p;
		SAParams.SeqNumLo = params->SeqNumLo;
		SAParams.SeqNumHi = params->SeqNumHi;
	}

	rc = SABuilder_GetSize(&SAParams, &SAWordCount);
	if (rc != SAB_STATUS_OK) {
		LOG_CRIT("eip_macsec_build_sa: SABuilder_GetSize error\n");
		return NULL;
	}

	SABuffer_p = kmalloc(SAWordCount * sizeof(uint32_t), GFP_KERNEL);
	if (SABuffer_p == NULL) {
		LOG_CRIT("eip_macsec_build_sa: memory allocation failure\n");
		return NULL;
	}

	*SAWordCount_p = SAWordCount;

	rc = SABuilder_BuildSA(&SAParams, SABuffer_p, AES_Encrypt);
	if (rc != SAB_STATUS_OK) {
		kfree(SABuffer_p);
		LOG_CRIT("eip_macsec_build_sa: error building SA\n");
		return NULL;
	}

	return SABuffer_p;
}

void eip_macsec_initalize_priv_data(uint32_t device_id)
{
	uint32_t eip_link_id, sa;
	struct macsec_per_channel_info *ch_info_p = NULL;

	/* Initialize channel info params to NULL */
	for (sa = 0; sa < MACSEC_MAX_SA; ++sa) {
		eip_link_id = MACSEC_GET_LINK_ID(device_id, sa);
		LOG_INFO("%d Device's Link id %d", device_id, eip_link_id);
		ch_info_p = &macsec_priv_data.channel_info[eip_link_id];
		ch_info_p->CfyE_RuleHandle[sa] = CfyE_RuleHandle_NULL;
		ch_info_p->SecY_SAHandle[sa] = SecY_SAHandle_NULL;
		ch_info_p->CfyE_vPortHandle[sa] = CfyE_vPortHandle_NULL;
		ch_info_p->active[sa] = 0;
		ch_info_p->sa_active_idx = 0xFF;
		ch_info_p->egress_init_flag = 0;
		ch_info_p->vPortIndex = vPORT_INDEX_NOT_INITIALIZE;
	}
}

static int eip_macsec_config_default_vport(unsigned int device_id,
					   unsigned int channel,
					   struct macsec_context *ctx)
{
	struct macsec_device_info *dev_info_p;
	u32 port_id;
	int rc = 0;

	port_id = GET_PORT_ID_FROM_DEVICE_ID(device_id);
	if (port_id >= EIP_MAX_PORT) {
		LOG_CRIT("%s: Invalid device ID %d", __func__, port_id);
		return -EINVAL;
	} else {
		dev_info_p = &macsec_priv_data.device_info[port_id];
	}

	/* Configure control packet and VLAN parsers, as well as default vPorts
	   for each channel. Channel 0 will be must-secure all others
	   should-secure */
	{
		CfyE_Device_t DeviceParams;
		CfyE_Device_Exceptions_t DeviceExceptions;
		CfyE_Device_Control_t DeviceControl;
		CfyE_ControlPacket_t CP;
		CfyE_HeaderParser_t HeaderParams;
		CfyE_VLAN_Parser_t VLANTagParams;

		ZEROINIT(DeviceParams);
		ZEROINIT(HeaderParams);
		ZEROINIT(VLANTagParams);
		ZEROINIT(CP);
		ZEROINIT(DeviceControl);
		ZEROINIT(DeviceExceptions);

		CP.MAC_DA_ET_Rules[0].EtherType = CONTROL_ETYPE;
		CP.CPMatchEnableMask = BIT_8; /* Enable Etype[0] matching */
		CP.CPMatchModeMask =
			BIT_0; /* Etype[0] matching after VLAN tag */
		DeviceParams.CP_p = &CP;

		DeviceExceptions.DropAction = CFYE_DO_NOT_DROP;
		DeviceExceptions.fForceDrop = false;
		DeviceExceptions.fDefaultVPortValid = true;
		DeviceControl.fLowLatencyBypass = false;
		DeviceControl.Exceptions_p = &DeviceExceptions;
		DeviceParams.Control_p = &DeviceControl;

		VLANTagParams.CP.fParseQinQ = true;
		VLANTagParams.CP.fParseQTag = true;
		VLANTagParams.CP.fParseStag1 = true;
		VLANTagParams.fSTagUpEnable = true;
		VLANTagParams.fQTagUpEnable = true;
		VLANTagParams.DefaultUp = 0;
		VLANTagParams.UpTable1[0] = VLANTagParams.UpTable2[0] = 0;
		VLANTagParams.UpTable1[1] = VLANTagParams.UpTable2[1] = 1;
		VLANTagParams.UpTable1[2] = VLANTagParams.UpTable2[2] = 2;
		VLANTagParams.UpTable1[3] = VLANTagParams.UpTable2[3] = 3;
		VLANTagParams.UpTable1[4] = VLANTagParams.UpTable2[4] = 4;
		VLANTagParams.UpTable1[5] = VLANTagParams.UpTable2[5] = 5;
		VLANTagParams.UpTable1[6] = VLANTagParams.UpTable2[6] = 6;
		VLANTagParams.UpTable1[7] = VLANTagParams.UpTable2[7] = 7;
		VLANTagParams.QTag = ETH_P_8021Q;
		VLANTagParams.STag1 = ETH_P_QINQ2;

		HeaderParams.VLAN_Parser_p = &VLANTagParams;
		DeviceParams.HeaderParser_p = &HeaderParams;
		DeviceExceptions.DefaultVPort = vPortIndex;
		rc = CfyE_Device_Update(device_id, channel, &DeviceParams);
		if (rc != CFYE_STATUS_OK) {
			LOG_CRIT(
				"DA_MACSEC: CfyE device could not be updated, error=%d\n",
				rc);
			rc = -EINVAL;
		}
	}
	dev_info_p->init = true;
	/* At this point the Engine is ready to pass control packets on all channels
	   and pass data packets on channels with should-secure policy using the
	   per-channel default vPorts.

	   The actual MACsec SAs, vPorts and rules  have not been installed yet.
	 */

	/* If we made it to here, consider this run a success. Any jump */
	/* to the error label below will skip "success = true" */

	return rc;
}

static int eip_macsec_delete_sa(bool fIngress, unsigned int device_id,
				unsigned int Channel,
				struct macsec_context *ctx)
{
	int rc = 0;
	u8 sa;
	SecY_Status_t SecY_Rc;
	struct macsec_per_channel_info *ch_info_p;
	SecY_SA_Stat_E_t Egress_SAStats;
	SecY_SA_Stat_I_t Ingress_SAStats;

	ZEROINIT(Egress_SAStats);
	ZEROINIT(Ingress_SAStats);

	ch_info_p = get_eip_channel_info(device_id, Channel);

	sa = ctx->sa.assoc_num;
	if (sa >= MACSEC_MAX_SA) {
		LOG_CRIT("%s: Invalid SA/AN received ", __func__, sa);
		return false;
	}
	if (ch_info_p->active[sa]) {
		eip_logerr("Current SA %d is active sa, Can't remove it", sa);
		return false;
	}

	if (!SecY_SAHandle_IsSame(&ch_info_p->SecY_SAHandle[sa],
				  &SecY_SAHandle_NULL)) {
		SecY_Rc =
			SecY_SA_Remove(device_id, ch_info_p->SecY_SAHandle[sa]);
		if (SecY_Rc != SECY_STATUS_OK) {
			eip_logerr("Failed, SecY_SA_Remove()=%d\n", SecY_Rc);
		}
		ch_info_p->SecY_SAHandle[sa] = SecY_SAHandle_NULL;
		ch_info_p->active[sa] = 0;
		eip_loginfo("Deleted SecY_SA %d SA device_id = %d", sa,
			    device_id);
	} else {
		rc = -EINVAL;
	}

	if (!rc) {
		ch_info_p->associated[sa] = false;
	}
	return rc;
}

static int eip_macsec_add_secy(bool fIngress, unsigned int device_id,
			       unsigned int Channel, struct macsec_context *ctx)
{
	struct macsec_per_channel_info *ch_info_p;
	ch_info_p = get_eip_channel_info(device_id, Channel);

	eip_loginfo("%s:Device %d Channel %d\n", __func__, device_id, Channel);

	Log_FormattedMessage("%s Config for %sgress device id %d Channel %d ",
			     __func__, fIngress ? "in" : "e", device_id,
			     Channel);

	memcpy(&ch_info_p->secy_sci, &ctx->secy->sci, sizeof(sci_t));

	/* Add default cfye port and secy port */
	if (eip_macsec_config_default_vport(device_id, Channel, ctx) < 0) {
		LOG_CRIT("%s: Ingress mode Device_ID %d FAILED\n", __func__,
			 device_id);
		return -EINVAL;
	}

	dump_ctx_values(ctx, false);

	return 0;
}

static int eip_macsec_upd_secy(unsigned int egress_device_id,
			       unsigned int ingress_device_id,
			       unsigned int channel_id,
			       struct macsec_context *ctx)
{
	SecY_Status_t SecY_Rc = SECY_STATUS_OK;
	struct macsec_per_channel_info *ch_info_p = NULL;
	SecY_SA_t *SA_Params;

	// Egress
	ch_info_p = get_eip_channel_info(egress_device_id, channel_id);
	SA_Params = &ch_info_p->SA_Params[ctx->sa.assoc_num];

	if (!SecY_SAHandle_IsSame(&ch_info_p->SecY_SAHandle[ctx->sa.assoc_num],
				  &SecY_SAHandle_NULL)) {
		SA_Params->Params.Egress.fProtectFrames =
			ctx->secy->protect_frames;
		SA_Params->Params.Egress.fIncludeSCI =
			ctx->secy->tx_sc.send_sci;
		SA_Params->Params.Egress.fConfProtect =
			ctx->secy->tx_sc.encrypt;
		SA_Params->Params.Egress.fUseSCB = ctx->secy->tx_sc.scb;
		SA_Params->Params.Egress.fUseES = ctx->secy->tx_sc.end_station;

		SecY_Rc = SecY_SA_Update(
			egress_device_id,
			ch_info_p->SecY_SAHandle[ctx->sa.assoc_num], SA_Params);
		if (SecY_Rc != SECY_STATUS_OK) {
			eip_logerr("Engress Failed, SecY_SA_Update()=%d\n",
				   SecY_Rc);
			return SecY_Rc;
		}
	}

	// Ingress
	ch_info_p = get_eip_channel_info(ingress_device_id, channel_id);
	SA_Params = &ch_info_p->SA_Params[ctx->sa.assoc_num];
	if (!SecY_SAHandle_IsSame(&ch_info_p->SecY_SAHandle[ctx->sa.assoc_num],
				  &SecY_SAHandle_NULL)) {
		eip_loginfo("Ingress settings: device %d vport %d SCI_P = 0x%x",
			    ingress_device_id, ch_info_p->vPortIndex,
			    &ch_info_p->SCI_p[0]);

		switch (ctx->secy->validate_frames) {
		case MACSEC_VALIDATE_DISABLED:
			SA_Params->Params.Ingress.ValidateFramesTagged =
				SECY_FRAME_VALIDATE_DISABLE;
			break;
		case MACSEC_VALIDATE_CHECK:
			SA_Params->Params.Ingress.ValidateFramesTagged =
				SECY_FRAME_VALIDATE_CHECK;
			break;
		case MACSEC_VALIDATE_STRICT:
		default:
			SA_Params->Params.Ingress.ValidateFramesTagged =
				SECY_FRAME_VALIDATE_DEFAULT;
			eip_loginfo("Setting it to Default!");
			break;
		}
		SA_Params->Params.Ingress.fReplayProtect =
			ctx->secy->replay_protect;
		SA_Params->Params.Ingress.SCI_p = (uint8_t *)&ctx->secy->sci;
		SA_Params->Params.Ingress.AN = ctx->sa.assoc_num;
		SecY_Rc = SecY_SA_Update(
			ingress_device_id,
			ch_info_p->SecY_SAHandle[ctx->sa.assoc_num], SA_Params);
		if (SecY_Rc != SECY_STATUS_OK) {
			eip_logerr("Ingress Failed, SecY_SA_Update()=%d\n",
				   SecY_Rc);
			return SecY_Rc;
		}
	}
	return SecY_Rc;
}

static int eip_macsec_config_sa(bool fIngress, unsigned int device_id,
				unsigned int Channel,
				struct macsec_context *ctx)
{
	u32 SAWordCount = 0;
	SecY_SA_t *SA_Params;
	struct macsec_per_channel_info *ch_info_p;

	ch_info_p = get_eip_channel_info(device_id, Channel);

	Log_FormattedMessage("%s config %sgress\n Device ID = %d Channel = %d",
			     __func__, fIngress ? "in" : "e", device_id,
			     Channel);
	eip_loginfo("%s: Device %d Channel %d\n", __func__, device_id, Channel);

	if (ctx->sa.assoc_num >= MACSEC_NUM_AN) {
		LOG_CRIT("Invalid AN %d\n", ctx->sa.assoc_num);
		return false;
	}

	/* Install SA with transform record */

	SA_Params = &ch_info_p->SA_Params[ctx->sa.assoc_num];
	ZEROINIT(*SA_Params);

	if (fIngress) {
		da_sa_params_t params;

		SA_Params->ActionType = SECY_SA_ACTION_INGRESS;
		SA_Params->DropType = SECY_SA_DROP_CRC_ERROR;
		SA_Params->DestPort = SECY_PORT_CONTROLLED;
		switch (ctx->secy->validate_frames) {
		case MACSEC_VALIDATE_DISABLED:
			SA_Params->Params.Ingress.ValidateFramesTagged =
				SECY_FRAME_VALIDATE_DISABLE;
			break;
		case MACSEC_VALIDATE_CHECK:
			SA_Params->Params.Ingress.ValidateFramesTagged =
				SECY_FRAME_VALIDATE_CHECK;
			break;
		case MACSEC_VALIDATE_STRICT:
		default:
			SA_Params->Params.Ingress.ValidateFramesTagged =
				SECY_FRAME_VALIDATE_DEFAULT;
			eip_loginfo("Setting it to Default!");
			break;
		}
		SA_Params->Params.Ingress.fReplayProtect =
			ctx->secy->replay_protect;
		SA_Params->Params.Ingress.SCI_p =
			(uint8_t *)&ch_info_p->SCI_p[0];
		SA_Params->Params.Ingress.AN = ctx->sa.assoc_num;
		SA_Params->Params.Ingress.fAllowTagged = true;
		SA_Params->Params.Ingress.PreSecTagAuthLength = 12;
		SA_Params->Params.Ingress.fSAInUse = true;

		params.direction = SAB_DIRECTION_INGRESS;
		params.flags = 0;
		params.KeyByteCount = ctx->secy->key_len;
		params.Key_p = &ctx->sa.key[0];
		params.operation = SAB_OP_MACSEC;
		params.Salt_p = NULL;
		params.SCI_p = (uint8_t *)&ch_info_p->SCI_p[0];
		params.SeqMask = ctx->secy->replay_window;
		params.SeqNumHi = 0;
		params.SeqNumLo = ctx->sa.rx_sa->next_pn;
		params.SSCI_p = NULL;
		params.AN = ctx->sa.assoc_num;
		SA_Params->TransformRecord_p =
			eip_macsec_build_sa(&params, &SAWordCount);
		SA_Params->SA_WordCount = SAWordCount;
	}

	if (!fIngress) {
		da_sa_params_t params;

		SA_Params->ActionType = SECY_SA_ACTION_EGRESS;
		SA_Params->DropType = SECY_SA_DROP_INTERNAL;
		SA_Params->DestPort = SECY_PORT_COMMON;

		SA_Params->Params.Egress.fProtectFrames =
			ctx->secy->protect_frames;
		SA_Params->Params.Egress.fIncludeSCI =
			ctx->secy->tx_sc.send_sci;
		SA_Params->Params.Egress.fConfProtect =
			ctx->secy->tx_sc.encrypt;
		SA_Params->Params.Egress.fUseSCB = ctx->secy->tx_sc.scb;
		SA_Params->Params.Egress.fUseES = ctx->secy->tx_sc.end_station;
		SA_Params->Params.Egress.fAllowDataPkts = true;
		SA_Params->Params.Egress.PreSecTagAuthLength = 12;
		SA_Params->Params.Egress.fSAInUse = true;
		params.direction = SAB_DIRECTION_EGRESS;
		params.flags = 0;
		params.KeyByteCount = ctx->secy->key_len;
		params.Key_p = &ctx->sa.key[0];
		params.operation = SAB_OP_MACSEC;
		params.Salt_p = NULL;
		params.SCI_p = (uint8_t *)&ctx->secy->sci;
		params.SeqMask = 0;
		params.SeqNumHi = 0;
		params.SeqNumLo = ctx->sa.tx_sa->next_pn;
		params.SSCI_p = NULL;
		params.AN = ctx->sa.assoc_num;
		SA_Params->TransformRecord_p =
			eip_macsec_build_sa(&params, &SAWordCount);
		SA_Params->SA_WordCount = SAWordCount;
	}

	dump_ctx_values(ctx, false);
	return 0;
}

static int eip_macsec_add_sa(bool fIngress, unsigned int device_id,
			     unsigned int Channel, struct macsec_context *ctx)
{
	int rc = 0;
	CfyE_vPort_t vPortParams;
	SecY_SA_t *SA_Params;
	CfyE_Rule_t RuleParams;

	uint8_t sa_idx = ctx->sa.assoc_num;
	struct macsec_per_channel_info *ch_info_p =
		get_eip_channel_info(device_id, Channel);

	Log_FormattedMessage("%s DA_MACSEC: Starting test for %sgress\n",
			     __func__, fIngress ? "in" : "e");
	eip_loginfo("device %d channel %d", device_id, Channel);

	if (ctx->sa.assoc_num >= MACSEC_NUM_AN) {
		LOG_CRIT("Invalid AN %d\n", ctx->sa.assoc_num);
		return false;
	}

	/* Initialize resource variables to NULL */
	SecY_SAHandle = SecY_SAHandle_NULL;
	CfyE_vPortHandle = CfyE_vPortHandle_NULL;
	CfyE_RuleHandle = CfyE_RuleHandle_NULL;

	/* Create vPorts */
	SA_Params = &ch_info_p->SA_Params[ctx->sa.assoc_num];
	ZEROINIT(vPortParams);
	ZEROINIT(RuleParams);

	vPortParams.SecTagOffset =
		EIP_MACSEC_SECTAG_OFFSET; /* vPort 2 has no VLAN tag */
	vPortParams.PktExtension = EIP_MACSEC_EXPANSION_EXPLICIT_SCI;

	if (ch_info_p->vPortIndex == vPORT_INDEX_NOT_INITIALIZE) {
		rc = CfyE_vPort_Add(device_id, &CfyE_vPortHandle, &vPortParams,
				    CYFE_MODE_MACSEC);
		if (rc != CFYE_STATUS_OK) {
			LOG_CRIT("%s: Failed, CfyE_vPort_Add()=%d\n", __func__,
				 rc);
			goto error_exit;
		}

		/* Now get vPort index to use when installing SA: */
		CfyE_vPortIndex_Get(CfyE_vPortHandle, &vPortIndex);
		ch_info_p->vPortIndex = vPortIndex;

		LOG_INFO(
			"%s: Secy Add handle 0x%xpk vport index %d secy_index %d\n",
			__func__, ch_info_p->SecY_SAHandle[ctx->sa.assoc_num],
			ch_info_p->vPort[ctx->sa.assoc_num], ctx->sa.assoc_num);

		RuleParams.Policy.vPortHandle = CfyE_vPortHandle;
		/* Exact match on channel, no other fields to match on. */
		RuleParams.Mask.ChannelID = 0x3f;
		RuleParams.Key.ChannelID = Channel;

		rc = CfyE_Rule_Add(device_id, CfyE_vPortHandle,
				   &CfyE_RuleHandle, &RuleParams);
		if (rc != CFYE_STATUS_OK) {
			LOG_CRIT("%s: Failed, CfyE_Rule_Add()=%d\n", __func__,
				 rc);
			goto error_exit;
		}

		rc = CfyE_Rule_Enable(device_id, CfyE_RuleHandle, true);
		if (rc != CFYE_STATUS_OK) {
			LOG_CRIT("%s: Failed, CfyE_Rule_Enable()=%d\n",
				 __func__, rc);
			goto error_exit;
		}

		ch_info_p->CfyE_RuleHandle[ctx->sa.assoc_num] = CfyE_RuleHandle;
		ch_info_p->CfyE_vPortHandle[ctx->sa.assoc_num] =
			CfyE_vPortHandle;
		eip_loginfo("Rule enabled for vPort \n");
		ch_info_p->valid = true;
	}
	eip_loginfo("ch_info_p->vPortIndex = %d, vPortIndex = %d\n",
		    ch_info_p->vPortIndex, vPortIndex);
	/*SA Creation*/
	if (fIngress) // Ingress
	{
		rc = SecY_SA_Add(device_id, ch_info_p->vPortIndex,
				 &SecY_SAHandle, SA_Params);
		if (rc != SECY_STATUS_OK) {
			eip_logerr("Failed, SecY_SA_Add()=%d\n", rc);
			goto error_exit;
		}
		eip_loginfo(" Ingress SA_ADDED device id = %d", device_id);
		ch_info_p->active[sa_idx] = ctx->sa.rx_sa->active;
	} else {
		if (!ch_info_p->egress_init_flag) {
			rc = SecY_SA_Add(device_id, ch_info_p->vPortIndex,
					 &SecY_SAHandle, SA_Params);
			if (rc != SECY_STATUS_OK) {
				eip_logerr("Failed, SecY_SA_Add()=%d\n", rc);
				goto error_exit;
			}
			ch_info_p->egress_init_flag = 1;
			eip_loginfo("Egress SA_ADDED:  1st Time device id = %d",
				    device_id);
			ch_info_p->active[sa_idx] = ctx->sa.tx_sa->active;
			ch_info_p->sa_active_idx = sa_idx;
		} else {
			// Get the active SA information
			SecY_SAHandle_t Active_SecY_SAHandle =
				SecY_SAHandle_NULL;
			eip_loginfo("ch_info_p->sa_active_idx = %d",
				    ch_info_p->sa_active_idx);

			rc = SecY_SA_Active_E_Get(device_id,
						  ch_info_p->vPortIndex,
						  &Active_SecY_SAHandle);
			if (rc != SECY_STATUS_OK) {
				eip_logerr("SecY_SA_Active_E_Get()=%d\n", rc);
				goto error_exit;
			}

			rc = SecY_SA_Chain(device_id, Active_SecY_SAHandle,
					   &SecY_SAHandle, SA_Params);
			if (rc != SECY_STATUS_OK) {
				LOG_CRIT(
					"DA_MACSEC: Failed, SecY_SA_Chain()=%d\n",
					rc);
				goto error_exit;
			}
			eip_loginfo("Egress SA_Chained device id = %d\n",
				    device_id);
		}
	}

	ch_info_p->SecY_SAHandle[sa_idx] = SecY_SAHandle;
	ch_info_p->vPort[sa_idx] = vPortIndex;

	if (SA_Params->TransformRecord_p) {
		kfree_sensitive(SA_Params->TransformRecord_p);
	}

	eip_loginfo("MACsec SA for vPort added\n");

	ch_info_p->associated[ctx->sa.assoc_num] = true;

	/* At this point, the MACsec SAs and associated rules have been installed.
	   For egress, all (non-control) data packets will be encrypted regardless
	   of must-secure/should-secure status.
	   For ingress, MACsec packets will be decrypted. Non-MAcsec data packets
	   will be passed in should-secure, dropped in must-secure.

	   Data packets on a channel that do not match a TCAM rule will be handled
	   by the default vPort of that channel (should-secure or must-secure).

	   Control packets are passed unchanged in all cases. If they match a rule
	   they will be passed by the actual MACsec SAs, if they do not match a
	   rule, they will be passed by the dummy SAs on the default vPorts.
	 */

	return rc;
error_exit:

	LOG_CRIT("Error condition, cleaning up");
	/* Remove any and all resources */
	if (!CfyE_RuleHandle_IsSame(CfyE_RuleHandle, CfyE_RuleHandle_NULL)) {
		CfyE_Rule_Disable(device_id, CfyE_RuleHandle, true);
		CfyE_Rule_Remove(device_id, CfyE_RuleHandle);
		CfyE_RuleHandle = CfyE_RuleHandle_NULL;
	}
	if (!CfyE_vPortHandle_IsSame(CfyE_vPortHandle, CfyE_vPortHandle_NULL)) {
		CfyE_vPort_Remove(device_id, CfyE_vPortHandle);
		CfyE_vPortHandle = CfyE_vPortHandle_NULL;
	}
	if (!SecY_SAHandle_IsSame(&SecY_SAHandle, &SecY_SAHandle_NULL)) {
		SecY_SA_Remove(device_id, SecY_SAHandle);
		SecY_SAHandle = SecY_SAHandle_NULL;
	}

	return rc;
}

int eip_device_deinit(bool fIngress, unsigned int device_id)
{
	unsigned int eip_link_id;
	uint32_t sa;
	struct macsec_per_channel_info *ch_info_p;

	for (sa = 0; sa < MACSEC_MAX_SA; sa++) {
		eip_link_id = MACSEC_GET_LINK_ID(device_id, sa);
		LOG_INFO("%d Port id's Link id %d", device_id, eip_link_id);
		ch_info_p = &macsec_priv_data.channel_info[eip_link_id];
		if (!CfyE_RuleHandle_IsSame(ch_info_p->CfyE_RuleHandle[sa],
					    CfyE_RuleHandle_NULL)) {
			LOG_INFO("device id %d CfyE_RuleHandle[%d] = 0x%x",
				 device_id, sa, ch_info_p->CfyE_RuleHandle[sa]);
			CfyE_Rule_Disable(device_id,
					  ch_info_p->CfyE_RuleHandle[sa], true);
			CfyE_Rule_Remove(device_id,
					 ch_info_p->CfyE_RuleHandle[sa]);
			ch_info_p->CfyE_RuleHandle[sa] = CfyE_RuleHandle_NULL;
		}
		if (!CfyE_vPortHandle_IsSame(ch_info_p->CfyE_vPortHandle[sa],
					     CfyE_vPortHandle_NULL)) {
			LOG_INFO("device id %d CfyE_vPortHandle[%d] = 0x%x",
				 device_id, sa,
				 ch_info_p->CfyE_vPortHandle[sa]);
			CfyE_vPort_Remove(device_id,
					  ch_info_p->CfyE_vPortHandle[sa]);
			ch_info_p->CfyE_vPortHandle[sa] = CfyE_vPortHandle_NULL;
		}
		if (!SecY_SAHandle_IsSame(&ch_info_p->SecY_SAHandle[sa],
					  &SecY_SAHandle_NULL)) {
			LOG_INFO("device id %d SecY_SAHandle[%d] = 0x%x",
				 device_id, sa, ch_info_p->SecY_SAHandle[sa]);
			SecY_SA_Remove(device_id, ch_info_p->SecY_SAHandle[sa]);
			ch_info_p->SecY_SAHandle[sa] = SecY_SAHandle_NULL;
		}
		ch_info_p->vPort[sa] = 0xFF;
	}

	SecY_Device_Uninit(device_id);
	CfyE_Device_Uninit(device_id);

	return 0;
}

static int eip_macsec_config_sc(bool fIngress, unsigned int device_id,
				unsigned int Channel,
				struct macsec_context *ctx)
{
	struct macsec_per_channel_info *ch_info_p;

	ch_info_p = get_eip_channel_info(device_id, Channel);

	eip_loginfo("%s for %cxsc config", __func__,
		    (fIngress == true) ? 'r' : 't');

	if (fIngress) {
		memcpy(&ch_info_p->SCI_p[0], &ctx->rx_sc->sci, 8);
	}
	dump_ctx_values(ctx, false);
	return 0;
}

static int eip_macsec_channel_stop(unsigned int device_id, unsigned int channel)
{
	struct macsec_per_channel_info *ch_info_p;
	SecY_Status_t SecY_Rc;
	CfyE_Status_t CfyE_Rc;

	ch_info_p = get_eip_channel_info(device_id, channel);

	eip_loginfo("%s: %d Device %d Channel %d\n", __func__, device_id,
		    channel);

	/* Remove any and all resources of a channel */
	if (!CfyE_RuleHandle_IsSame(ch_info_p->CfyE_RuleHandle[channel],
				    CfyE_RuleHandle_NULL)) {
		CfyE_Rc = CfyE_Rule_Disable(
			device_id, ch_info_p->CfyE_RuleHandle[channel], true);
		if (CfyE_Rc != CFYE_STATUS_OK) {
			LOG_CRIT("CfyE_Rule_Disable returned error %d\n",
				 CfyE_Rc);
			return CfyE_Rc;
		}
		CfyE_Rc = CfyE_Rule_Remove(device_id,
					   ch_info_p->CfyE_RuleHandle[channel]);
		if (CfyE_Rc != CFYE_STATUS_OK) {
			LOG_CRIT("CfyE_Rule_Remove returned error %d\n",
				 CfyE_Rc);
			return CfyE_Rc;
		}
		ch_info_p->CfyE_RuleHandle[channel] = CfyE_RuleHandle_NULL;
	}
	if (!CfyE_vPortHandle_IsSame(ch_info_p->CfyE_vPortHandle[channel],
				     CfyE_vPortHandle_NULL)) {
		CfyE_Rc = CfyE_vPort_Remove(
			device_id, ch_info_p->CfyE_vPortHandle[channel]);
		if (CfyE_Rc != CFYE_STATUS_OK) {
			LOG_CRIT("CfyE_vPort_Remove returned error %d\n",
				 CfyE_Rc);
			return CfyE_Rc;
		}
		ch_info_p->CfyE_vPortHandle[channel] = CfyE_vPortHandle_NULL;
	}
	if (!SecY_SAHandle_IsSame(&ch_info_p->SecY_SAHandle[channel],
				  &SecY_SAHandle_NULL)) {
		SecY_Rc = SecY_SA_Remove(device_id,
					 ch_info_p->SecY_SAHandle[channel]);
		if (SecY_Rc != SECY_STATUS_OK) {
			LOG_CRIT("SecY_SA_Remove returned error %d\n", SecY_Rc);
			return SecY_Rc;
		}
		ch_info_p->SecY_SAHandle[channel] = SecY_SAHandle_NULL;
	}
	ch_info_p->associated[channel] = false;

	return 0;
}

static int eip_macsec_egress_stats(unsigned int port_id, unsigned int channel,
				   struct eip_macsec_stats *stats,
				   enum stats_type stats_type,
				   struct macsec_context *ctx)
{
	SecY_Status_t SecY_Rc;
	unsigned int egress_device_id;
	struct macsec_per_channel_info *ch_info_p = NULL;
	SecY_SA_Stat_E_t SAStats;
	SecY_SecY_Stat_E_t SecYStats;
	uint32_t SA_Words[2] = { 0 };

	ZEROINIT(SecYStats);
	ZEROINIT(SAStats);

	egress_device_id = GET_EGRESS_ID_FROM_DEVICE_ID(port_id);
	ch_info_p = get_eip_channel_info(egress_device_id, channel);

	if (!SecY_SAHandle_IsSame(&ch_info_p->SecY_SAHandle[ctx->sa.assoc_num],
				  &SecY_SAHandle_NULL)) {
		SecY_Rc = SecY_SA_Read(
			egress_device_id,
			ch_info_p->SecY_SAHandle[ctx->sa.assoc_num], 0, 1,
			SA_Words);
		if (SecY_Rc != SECY_STATUS_OK) {
			LOG_CRIT("SecY_SA_Read returned error %d\n", SecY_Rc);
			return SecY_Rc;
		}
		ctx->secy->tx_sc.encoding_sa = (SA_Words[0] >> 26) & 0x3;

		SecY_Rc = SecY_SA_Statistics_E_Get(
			egress_device_id,
			ch_info_p->SecY_SAHandle[ctx->sa.assoc_num], &SAStats,
			true);
		if (SecY_Rc != SECY_STATUS_OK) {
			eip_logerr("Failed, SecY_SA_Statistics_E_Get()=%d\n",
				   SecY_Rc);
			return SecY_Rc;
		}
		switch (stats_type) {
		case MACSEC_STATS_TXSC:
		case MACSEC_STATS_TXSA: {
			if (ctx->secy->tx_sc.encrypt) {
				stats->tx_sc_stats
					.OutPktsEncrypted = STATS_2x32_TO_64(
					SAStats.OutPktsEncryptedProtected.Lo,
					SAStats.OutPktsEncryptedProtected.Hi);
				stats->tx_sc_stats
					.OutOctetsEncrypted = STATS_2x32_TO_64(
					SAStats.OutOctetsEncryptedProtected.Lo,
					SAStats.OutOctetsEncryptedProtected.Hi);
				stats->tx_sa_stats
					.OutPktsEncrypted = STATS_2x32_TO_64(
					SAStats.OutPktsEncryptedProtected.Lo,
					SAStats.OutPktsEncryptedProtected.Hi);
			} else {
				stats->tx_sc_stats
					.OutPktsProtected = STATS_2x32_TO_64(
					SAStats.OutPktsEncryptedProtected.Lo,
					SAStats.OutPktsEncryptedProtected.Hi);
				stats->tx_sc_stats
					.OutOctetsProtected = STATS_2x32_TO_64(
					SAStats.OutOctetsEncryptedProtected.Lo,
					SAStats.OutOctetsEncryptedProtected.Hi);
				stats->tx_sa_stats
					.OutPktsProtected = STATS_2x32_TO_64(
					SAStats.OutPktsEncryptedProtected.Lo,
					SAStats.OutPktsEncryptedProtected.Hi);
			}
		} break;
		case MACSEC_STATS_DEV: {
			/* Read the SecY ingress statistics counters. */
			/* Sync with the SecY device to get the exact counters values */
			SecY_Rc = SecY_SecY_Statistics_E_Get(
				egress_device_id, ch_info_p->vPortIndex,
				&SecYStats, true);
			if (SecY_Rc != SECY_STATUS_OK) {
				eip_logerr(
					"Failed, SecY_SecY_Statistics_E_Get()=%d\n",
					SecY_Rc);
				return SecY_Rc;
			}
			stats->dev_stats.OutPktsUntagged =
				STATS_2x32_TO_64(SecYStats.OutPktsUntagged.Lo,
						 SecYStats.OutPktsUntagged.Hi);
			stats->dev_stats.OutPktsTooLong =
				STATS_2x32_TO_64(SAStats.OutPktsTooLong.Lo,
						 SAStats.OutPktsTooLong.Hi);
		} break;
		default:
			eip_logerr("Invalid option %d", stats_type);
			break;
		}
	}

	return 0;
}

static int eip_macsec_ingress_stats(unsigned int port_id, unsigned int channel,
				    struct eip_macsec_stats *stats,
				    enum stats_type stats_type)
{
	unsigned int ingress_device_id;
	struct macsec_per_channel_info *ch_info_p = NULL;
	SecY_SAHandle_t SAHandles_Ingress[MACSEC_MAX_SA] = {
		SecY_SAHandle_NULL,
	};
	SecY_Status_t SecY_Rc = SECY_STATUS_OK;
	uint8_t active_sa_idx = 0;
	SecY_SA_Stat_I_t SAStats;
	SecY_SecY_Stat_I_t SecYStats;

	ZEROINIT(SecYStats);
	ZEROINIT(SAStats);

	ingress_device_id = GET_INGRESS_ID_FROM_DEVICE_ID(port_id);
	ch_info_p = get_eip_channel_info(ingress_device_id, channel);

	switch (stats_type) {
	case MACSEC_STATS_RXSC:
	case MACSEC_STATS_RXSA: {
		SecY_Rc = SecY_SA_Active_I_Get(ingress_device_id,
					       ch_info_p->vPortIndex,
					       (uint8_t *)&ch_info_p->SCI_p[0],
					       SAHandles_Ingress);
		if (SecY_Rc != SECY_STATUS_OK) {
			eip_logerr("SecY_SA_Active_I_Get()=%d\n", SecY_Rc);
			return SecY_Rc;
		}

		for (active_sa_idx = 0; active_sa_idx < MACSEC_MAX_SA;
		     active_sa_idx++) {
			if (!SecY_SAHandle_IsSame(
				    &SAHandles_Ingress[active_sa_idx],
				    &SecY_SAHandle_NULL)) {
				/* Found current active Ingress SA */
				/* Read the SA ingress statistics counters, */
				/* request device synchronization before reading out the statistics */
				// eip_logerr("active_sa_idx = %d", active_sa_idx);
				SecY_Rc = SecY_SA_Statistics_I_Get(
					ingress_device_id,
					ch_info_p->SecY_SAHandle[active_sa_idx],
					&SAStats, true);
				if (SecY_Rc != SECY_STATUS_OK) {
					eip_logerr(
						"Failed, SecY_SA_Statistics_I_Get()=%d\n",
						SecY_Rc);
					return SecY_Rc;
				}

				stats->rx_sc_stats.InOctetsValidated +=
					STATS_2x32_TO_64(
						SAStats.InOctetsValidated.Lo,
						SAStats.InOctetsValidated.Hi);
				stats->rx_sc_stats.InOctetsDecrypted +=
					STATS_2x32_TO_64(
						SAStats.InOctetsDecrypted.Lo,
						SAStats.InOctetsDecrypted.Hi);
				stats->rx_sc_stats.InPktsUnchecked +=
					STATS_2x32_TO_64(
						SAStats.InPktsUnchecked.Lo,
						SAStats.InPktsUnchecked.Hi);
				stats->rx_sc_stats.InPktsDelayed +=
					STATS_2x32_TO_64(
						SAStats.InPktsDelayed.Lo,
						SAStats.InPktsDelayed.Hi);
				stats->rx_sc_stats.InPktsOK +=
					STATS_2x32_TO_64(SAStats.InPktsOK.Lo,
							 SAStats.InPktsOK.Hi);
				stats->rx_sc_stats.InPktsInvalid +=
					STATS_2x32_TO_64(
						SAStats.InPktsInvalid.Lo,
						SAStats.InPktsInvalid.Hi);
				stats->rx_sc_stats.InPktsLate +=
					STATS_2x32_TO_64(SAStats.InPktsLate.Lo,
							 SAStats.InPktsLate.Hi);
				stats->rx_sc_stats.InPktsNotValid +=
					STATS_2x32_TO_64(
						SAStats.InPktsNotValid.Lo,
						SAStats.InPktsNotValid.Hi);
				stats->rx_sc_stats.InPktsNotUsingSA +=
					STATS_2x32_TO_64(
						SAStats.InPktsNotUsingSA.Lo,
						SAStats.InPktsNotUsingSA.Hi);
				stats->rx_sc_stats.InPktsUnusedSA +=
					STATS_2x32_TO_64(
						SAStats.InPktsUnusedSA.Lo,
						SAStats.InPktsUnusedSA.Hi);

				stats->rx_sa_stats.InPktsOK +=
					STATS_2x32_TO_64(SAStats.InPktsOK.Lo,
							 SAStats.InPktsOK.Hi);
				stats->rx_sa_stats.InPktsInvalid +=
					STATS_2x32_TO_64(
						SAStats.InPktsInvalid.Lo,
						SAStats.InPktsInvalid.Hi);
				stats->rx_sa_stats.InPktsNotValid +=
					STATS_2x32_TO_64(
						SAStats.InPktsNotValid.Lo,
						SAStats.InPktsNotValid.Hi);
				stats->rx_sa_stats.InPktsNotUsingSA +=
					STATS_2x32_TO_64(
						SAStats.InPktsNotUsingSA.Lo,
						SAStats.InPktsNotUsingSA.Hi);
				stats->rx_sa_stats.InPktsUnusedSA +=
					STATS_2x32_TO_64(
						SAStats.InPktsUnusedSA.Lo,
						SAStats.InPktsUnusedSA.Hi);
			}
		}
	} break;
	case MACSEC_STATS_DEV: {
		/* Read the SecY ingress statistics counters. */
		/* Sync with the SecY device to get the exact counters values */
		if (ch_info_p->vPortIndex != vPORT_INDEX_NOT_INITIALIZE) {
			SecY_Rc = SecY_SecY_Statistics_I_Get(
				ingress_device_id, ch_info_p->vPortIndex,
				&SecYStats, true);
			if (SecY_Rc != SECY_STATUS_OK) {
				eip_logerr(
					"Failed, SecY_SecY_Statistics_I_Get()=%d\n",
					SecY_Rc);
				return SecY_Rc;
			}
			stats->dev_stats.InPktsUntagged =
				STATS_2x32_TO_64(SecYStats.InPktsUntagged.Lo,
						 SecYStats.InPktsUntagged.Lo);
			stats->dev_stats.InPktsNoTag =
				STATS_2x32_TO_64(SecYStats.InPktsNoTag.Lo,
						 SecYStats.InPktsNoTag.Hi);
			stats->dev_stats.InPktsBadTag =
				STATS_2x32_TO_64(SecYStats.InPktsBadTag.Lo,
						 SecYStats.InPktsBadTag.Hi);
			stats->dev_stats.InPktsUnknownSCI =
				STATS_2x32_TO_64(SecYStats.InPktsUnknownSCI.Lo,
						 SecYStats.InPktsUnknownSCI.Hi);
			stats->dev_stats.InPktsNoSCI =
				STATS_2x32_TO_64(SecYStats.InPktsNoSCI.Lo,
						 SecYStats.InPktsNoSCI.Hi);
			stats->dev_stats.InPktsOverrun = STATS_2x32_TO_64(
				SecYStats.InPktsTransformError.Lo,
				SecYStats.InPktsTransformError.Hi);
		}
	} break;
	default:
		eip_logerr("Invalid option %d", stats_type);
		break;
	}

	return SecY_Rc;
}

static int eip_mdo_dev_open(struct macsec_context *ctx)
{
	unsigned int ingress_device, egress_device, port_id, channel_id;
	uint32_t link_index;

	if (ctx->prepare) {
		return 0;
	}
	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);

	get_device_params_from_link_id(link_index, &port_id, &ingress_device,
				       &egress_device, &channel_id);

	eip_loginfo("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		    port_id, channel_id);
	/* Clear bypass setting  */

	CfyE_Channel_Bypass_Set(ingress_device, channel_id, false);
	SecY_Channel_Bypass_Set(ingress_device, channel_id, false);

	CfyE_Channel_Bypass_Set(egress_device, channel_id, false);
	SecY_Channel_Bypass_Set(egress_device, channel_id, false);

	return 0;
}

static int eip_mdo_dev_stop(struct macsec_context *ctx)
{
	unsigned int ingress_device, egress_device, port_id, channel_id;
	uint32_t link_index;

	if (ctx->prepare) {
		return 0;
	}
	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);
	get_device_params_from_link_id(link_index, &port_id, &ingress_device,
				       &egress_device, &channel_id);

	eip_loginfo("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		    port_id, channel_id);

	/* The default bootup behavior :
	   1. Setup  the  channel  set them in bypass mode       */
	{
		CfyE_Channel_Bypass_Set(ingress_device, channel_id, true);
		SecY_Channel_Bypass_Set(ingress_device, channel_id, true);

		CfyE_Channel_Bypass_Set(egress_device, channel_id, true);
		SecY_Channel_Bypass_Set(egress_device, channel_id, true);
	}
	return 0;
}

static int eip_mdo_add_secy(struct macsec_context *ctx)
{
	unsigned int ingress_device, egress_device, port_id, channel_id;
	uint32_t link_index;

	if (ctx->prepare) {
		return 0;
	}
	dump_secy(ctx);

	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);
	get_device_params_from_link_id(link_index, &port_id, &ingress_device,
				       &egress_device, &channel_id);

	eip_loginfo("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		    port_id, channel_id);

	if (eip_macsec_add_secy(true, ingress_device, channel_id, ctx) < 0) {
		LOG_CRIT("%s: Ingress mode Device_ID %d Channel %d FAILED\n",
			 __func__, ingress_device, channel_id);
		return -EINVAL;
	}

	if (eip_macsec_add_secy(false, egress_device, channel_id, ctx) < 0) {
		LOG_CRIT("%s: Egress mode Device_ID %d Channel %d FAILED\n",
			 __func__, egress_device, channel_id);
		return -EINVAL;
	}

	return 0;
}

static int eip_mdo_upd_secy(struct macsec_context *ctx)
{
	unsigned int ingress_device, egress_device, port_id, channel_id;
	uint32_t link_index;

	dump_secy(ctx);

	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);

	get_device_params_from_link_id(link_index, &port_id, &ingress_device,
				       &egress_device, &channel_id);

	eip_loginfo("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		    port_id, channel_id);
	if (ctx->prepare) {
		return 0;
	}

	return eip_macsec_upd_secy(egress_device, ingress_device, channel_id,
				   ctx);
}

static int eip_mdo_del_secy(struct macsec_context *ctx)
{
	unsigned int port_id, ingress_device, egress_device, channel_id;
	uint32_t link_index;
	u32 index;
	struct macsec_per_channel_info *ch_info_p = NULL;

	eip_loginfo("Called!!!");
	dump_secy(ctx);

	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);

	get_device_params_from_link_id(link_index, &port_id, &ingress_device,
				       &egress_device, &channel_id);
	ch_info_p = get_eip_channel_info(egress_device, channel_id);

	ch_info_p->egress_init_flag = 0;

	eip_loginfo("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		    port_id, channel_id);

	for (index = 0; index < MACSEC_MAX_SA; ++index) {
		if (eip_macsec_channel_stop(ingress_device, index) < 0) {
			LOG_CRIT("%s: Ingress device %d channel %d failed",
				 __func__, ingress_device, channel_id);
			return -EINVAL;
		}

		if (eip_macsec_channel_stop(egress_device, index) < 0) {
			LOG_CRIT("%s: Egress device %d channel %d failed",
				 __func__, egress_device, channel_id);
			return -EINVAL;
		}
	}
	/* The default bootup behavior :
	   1. Setup  the  channel  set them in bypass mode       */
	{
		CfyE_Channel_Bypass_Set(ingress_device, channel_id, true);
		SecY_Channel_Bypass_Set(ingress_device, channel_id, true);

		CfyE_Channel_Bypass_Set(egress_device, channel_id, true);
		SecY_Channel_Bypass_Set(egress_device, channel_id, true);
	}

	return 0;
}

static int eip_mdo_add_rxsc(struct macsec_context *ctx)
{
	unsigned int ingress_device, port_id, channel_id;
	uint32_t link_index;

	dump_rxsc(ctx);

	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);
	get_ingress_params_from_link_id(link_index, &port_id, &ingress_device,
					&channel_id);

	eip_loginfo("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		    port_id, channel_id);

	/*  Configure Ingress Device and Channels */
	if (eip_macsec_config_sc(true, ingress_device, channel_id, ctx) < 0) {
		/* capture error */
		LOG_CRIT("%s: failed config sc params", __func__);
		return -EINVAL;
	}
	return 0;
}

static int eip_mdo_upd_rxsc(struct macsec_context *ctx)
{
	unsigned int ingress_device, port_id, channel_id;
	uint32_t link_index;

	if (ctx->prepare) {
		return 0;
	}
	dump_rxsc(ctx);

	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);
	get_ingress_params_from_link_id(link_index, &port_id, &ingress_device,
					&channel_id);
	eip_loginfo("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		    port_id, channel_id);

	if (eip_macsec_config_sc(true, ingress_device, channel_id, ctx) < 0) {
		LOG_CRIT("%s: Ingress config for rxsc failed", __func__);
		return -EINVAL;
	}

	return 0;
}

static int eip_mdo_del_rxsc(struct macsec_context *ctx)
{
	struct macsec_per_channel_info *ch_info_p = NULL;
	unsigned int ingress_device, port_id, channel_id;
	uint32_t link_index;

	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);
	get_ingress_params_from_link_id(link_index, &port_id, &ingress_device,
					&channel_id);
	ch_info_p = get_eip_channel_info(ingress_device, channel_id);

	memset(&ch_info_p->SCI_p[0], 0, 8);

	dump_rxsc(ctx);

	return 0;
}

static int eip_mdo_add_rxsa(struct macsec_context *ctx)
{
	unsigned int ingress_device, port_id, channel_id;
	uint32_t link_index;

	if (ctx->prepare) {
		return 0;
	}
	dump_rxsa(ctx);

	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);
	get_ingress_params_from_link_id(link_index, &port_id, &ingress_device,
					&channel_id);
	eip_loginfo("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		    port_id, channel_id);

	if (eip_macsec_config_sa(true, ingress_device, channel_id, ctx) < 0) {
		LOG_CRIT("%s: Ingress mode Device_ID %d Channel %d FAILED\n",
			 __func__, ingress_device, channel_id);
		return -EINVAL;
	}
	if (eip_macsec_add_sa(true, ingress_device, channel_id, ctx) < 0) {
		LOG_CRIT("%s: Egress mode Device_ID %d Channel %d FAILED\n",
			 __func__, ingress_device, channel_id);
		return -EINVAL;
	}

	return 0;
}

static int eip_mdo_upd_rxsa(struct macsec_context *ctx)
{
	unsigned int ingress_device, port_id, channel_id;
	uint32_t link_index;
	uint8_t sa_idx = ctx->sa.assoc_num;
	struct macsec_per_channel_info *ch_info_p = NULL;
	SecY_SAHandle_t SAHandles_Ingress[4] = { SecY_SAHandle_NULL };
	SecY_Status_t SecY_Rc = SECY_STATUS_OK;
	uint32_t SA_Words[2] = { 0 };
	uint8_t i;

	dump_rxsa(ctx);

	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);
	get_ingress_params_from_link_id(link_index, &port_id, &ingress_device,
					&channel_id);

	ch_info_p = get_eip_channel_info(ingress_device, channel_id);

	eip_loginfo("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		    port_id, channel_id);

	ch_info_p->active[sa_idx] = ctx->sa.rx_sa->active;
	SecY_Rc = SecY_SA_Active_I_Get(ingress_device, ch_info_p->vPortIndex,
				       (uint8_t *)&ch_info_p->SCI_p[0],
				       SAHandles_Ingress);
	if (SecY_Rc != SECY_STATUS_OK) {
		eip_logerr("SecY_SA_Active_I_Get()=%d\n", SecY_Rc);
		return SecY_Rc;
	}
	for (i = 0; i < MACSEC_MAX_SA; i++) {
		if (!SecY_SAHandle_IsSame(&SAHandles_Ingress[i],
					  &SecY_SAHandle_NULL)) {
			SecY_Rc = SecY_SA_Read(ingress_device,
					       SAHandles_Ingress[i],
					       SA_PN_SEQ_OFFSET, SA_WORD_COUNT,
					       SA_Words);
			if (SecY_Rc != SECY_STATUS_OK) {
				eip_logerr("SecY_SA_Read returned error %d\n",
					   SecY_Rc);
				return SecY_Rc;
			}
			break;
		}
	}
	ctx->sa.rx_sa->next_pn = STATS_2x32_TO_64(SA_Words[0], SA_Words[1]);
	eip_loginfo("Next_PN Seq0 = %d : Seq1 = %d", SA_Words[0], SA_Words[1]);

	return SecY_Rc;
}

static int eip_mdo_del_rxsa(struct macsec_context *ctx)
{
	unsigned int ingress_device, port_id, channel_id;
	uint32_t link_index;

	if (ctx->prepare) {
		return 0;
	}
	dump_rxsa(ctx);

	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);
	get_ingress_params_from_link_id(link_index, &port_id, &ingress_device,
					&channel_id);

	eip_loginfo("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		    port_id, channel_id);

	if (eip_macsec_delete_sa(true, ingress_device, channel_id, ctx) < 0) {
		LOG_CRIT("%s: Ingress mode Device_ID %d Channel %d FAILED\n",
			 __func__, ingress_device, channel_id);
		return -EINVAL;
	}

	return 0;
}

static int eip_mdo_add_txsa(struct macsec_context *ctx)
{
	unsigned int egress_device, port_id, channel_id;
	uint32_t link_index;

	if (ctx->prepare) {
		return 0;
	}

	eip_loginfo("CALLED!!!");
	dump_txsa(ctx);

	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);
	/* Configure Egress device and Channels */
	get_egress_params_from_link_id(link_index, &port_id, &egress_device,
				       &channel_id);

	eip_loginfo(
		"Link Index %d Device %d Channel %d , egress_device id = %d\n",
		link_index, port_id, channel_id, egress_device);

	if (eip_macsec_config_sa(false, egress_device, channel_id, ctx) < 0) {
		LOG_CRIT("%s: Ingress mode Device_ID %d Channel %d FAILED\n",
			 __func__, egress_device, channel_id);
		return -EINVAL;
	}
	if (eip_macsec_add_sa(false, egress_device, channel_id, ctx) < 0) {
		LOG_CRIT("%s: Egress mode Device_ID %d Channel %d FAILED\n",
			 __func__, egress_device, channel_id);
		return -EINVAL;
	}

	return 0;
}

static int eip_mdo_upd_txsa(struct macsec_context *ctx)
{
	unsigned int egress_device, port_id, channel_id;
	uint32_t link_index;
	SecY_Status_t SecY_Rc = SECY_STATUS_OK;
	struct macsec_per_channel_info *ch_info_p = NULL;
	uint8_t sa_idx = ctx->sa.assoc_num;
	SecY_SA_t *new_SA_Params;
	SecY_SAHandle_t Active_SecY_SAHandle;
	uint32_t SA_Words[24];

	eip_loginfo("%s: called \n", __func__);

	dump_txsa(ctx);

	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);
	get_egress_params_from_link_id(link_index, &port_id, &egress_device,
				       &channel_id);
	ch_info_p = get_eip_channel_info(egress_device, channel_id);
	new_SA_Params = &ch_info_p->SA_Params[sa_idx];
	eip_loginfo(
		"ch_info_p->sa_active_idx = %d, ch_info_p->active[sa_idx] = %s, ctx->sa.tx_sa->active = %s \n",
		ch_info_p->sa_active_idx,
		ch_info_p->active[sa_idx] ? "true" : "false",
		ctx->sa.tx_sa->active ? "true" : "false");
	/*
	Switch SA when, Current SA is not in active state and next incomping SA said to be active
	Else Case, Update Kernel PN value, by read the current active SA
	*/
	if (!ch_info_p->active[sa_idx] && ctx->sa.tx_sa->active) {
		Active_SecY_SAHandle = SecY_SAHandle_NULL;
		SecY_Rc = SecY_SA_Active_E_Get(
			egress_device,
			ch_info_p->vPort[ch_info_p->sa_active_idx],
			&Active_SecY_SAHandle);
		if (SecY_Rc != SECY_STATUS_OK) {
			eip_logerr("SecY_SA_Active_E_Get()=%d\n", SecY_Rc);
			return SecY_Rc;
		}
		SecY_Rc = SecY_SA_Switch(egress_device, Active_SecY_SAHandle,
					 SecY_SAHandle, new_SA_Params);

		if (SecY_Rc != SECY_STATUS_OK) {
			eip_logerr("SecY_SA_Switch()=%d\n", SecY_Rc);
			return SecY_Rc;
		}
		ch_info_p->SecY_SAHandle[sa_idx] = SecY_SAHandle;
		ch_info_p->sa_active_idx = sa_idx;
		eip_loginfo(
			"SA_Switched! egress_device id = %d, active_sa idx = %d\n",
			egress_device, ch_info_p->sa_active_idx);
	} else {
		Active_SecY_SAHandle = SecY_SAHandle_NULL;
		SecY_Rc = SecY_SA_Active_E_Get(egress_device,
					       ch_info_p->vPortIndex,
					       &Active_SecY_SAHandle);
		if (SecY_Rc != SECY_STATUS_OK) {
			eip_logerr("SecY_SA_Active_E_Get()=%d\n", SecY_Rc);
			return SecY_Rc;
		}
		SecY_Rc =
			SecY_SA_Read(egress_device, Active_SecY_SAHandle,
				     SA_PN_SEQ_OFFSET, SA_WORD_COUNT, SA_Words);
		if (SecY_Rc != SECY_STATUS_OK) {
			eip_logerr("SecY_SA_Read returned error %d\n", SecY_Rc);
			return SecY_Rc;
		}
		ctx->sa.tx_sa->next_pn =
			STATS_2x32_TO_64(SA_Words[0], SA_Words[1]);
		eip_loginfo("Next PN Seq0 = %d : Seq1 = %d", SA_Words[0],
			    SA_Words[1]);
	}

	return SecY_Rc;
}

static int eip_mdo_del_txsa(struct macsec_context *ctx)
{
	unsigned int egress_device, port_id, channel_id;
	uint32_t link_index;

	if (ctx->prepare) {
		return 0;
	}
	eip_loginfo("Called!!!");
	dump_txsa(ctx);

	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);
	get_egress_params_from_link_id(link_index, &port_id, &egress_device,
				       &channel_id);

	eip_loginfo("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		    port_id, channel_id);

	if (eip_macsec_delete_sa(false, egress_device, channel_id, ctx) < 0) {
		eip_loginfo("%s: Egress mode Device_ID %d Channel %d FAILED\n",
			    __func__, egress_device, channel_id);
		return -EINVAL;
	}
	return 0;
}

static int eip_mdo_get_dev_stats(struct macsec_context *ctx)
{
	unsigned int ingress_device, egress_device, port_id, channel_id;
	uint32_t link_index;
	struct eip_macsec_stats egress_stats, ingress_stats;
	int ret = 0;
	if (ctx->prepare) {
		return 0;
	}

	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);
	memset((void *)&ingress_stats, 0, sizeof(ingress_stats));
	memset((void *)&egress_stats, 0, sizeof(egress_stats));

	get_device_params_from_link_id(link_index, &port_id, &ingress_device,
				       &egress_device, &channel_id);

	eip_loginfo("Link %d Device %d Channel %d \n", link_index, port_id,
		    channel_id);

	ret = eip_macsec_ingress_stats(port_id, channel_id, &ingress_stats,
				       MACSEC_STATS_DEV);
	if (ret) {
		eip_logerr("Failed, eip_macsec_ingress_stats() = %d", ret);
		return ret;
	}
	ctx->stats.dev_stats->OutPktsUntagged =
		ingress_stats.dev_stats.OutPktsUntagged;
	ctx->stats.dev_stats->InPktsUntagged =
		ingress_stats.dev_stats.InPktsUntagged;
	ctx->stats.dev_stats->OutPktsTooLong =
		ingress_stats.dev_stats.OutPktsTooLong;
	ctx->stats.dev_stats->InPktsNoTag = ingress_stats.dev_stats.InPktsNoTag;
	ctx->stats.dev_stats->InPktsBadTag =
		ingress_stats.dev_stats.InPktsBadTag;
	ctx->stats.dev_stats->InPktsUnknownSCI =
		ingress_stats.dev_stats.InPktsUnknownSCI;
	ctx->stats.dev_stats->InPktsNoSCI = ingress_stats.dev_stats.InPktsNoSCI;
	ctx->stats.dev_stats->InPktsOverrun =
		ingress_stats.dev_stats.InPktsOverrun;

	ret = eip_macsec_egress_stats(port_id, channel_id, &egress_stats,
				      MACSEC_STATS_DEV, ctx);
	if (ret) {
		eip_logerr("Failed, eip_macsec_ingress_stats() = %d", ret);
		return ret;
	}

	ctx->stats.dev_stats->OutPktsUntagged =
		egress_stats.dev_stats.OutPktsUntagged;
	ctx->stats.dev_stats->InPktsUntagged =
		egress_stats.dev_stats.InPktsUntagged;
	ctx->stats.dev_stats->OutPktsTooLong =
		egress_stats.dev_stats.OutPktsTooLong;
	ctx->stats.dev_stats->InPktsNoTag = egress_stats.dev_stats.InPktsNoTag;
	ctx->stats.dev_stats->InPktsBadTag =
		egress_stats.dev_stats.InPktsBadTag;
	ctx->stats.dev_stats->InPktsUnknownSCI =
		egress_stats.dev_stats.InPktsUnknownSCI;
	ctx->stats.dev_stats->InPktsNoSCI = egress_stats.dev_stats.InPktsNoSCI;
	ctx->stats.dev_stats->InPktsOverrun =
		egress_stats.dev_stats.InPktsOverrun;

	return ret;
}

static int eip_mdo_get_tx_sc_stats(struct macsec_context *ctx)
{
	unsigned int egress_device, port_id, channel_id;
	uint32_t link_index;
	struct eip_macsec_stats egress_stats;
	struct macsec_per_channel_info *ch_info_p = NULL;
	SecY_Status_t SecY_Rc = SECY_STATUS_OK;

	if (ctx->prepare) {
		return 0;
	}
	memset((void *)&egress_stats, 0, sizeof(egress_stats));
	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);
	get_egress_params_from_link_id(link_index, &port_id, &egress_device,
				       &channel_id);

	eip_loginfo("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		    port_id, channel_id);

	ch_info_p = get_eip_channel_info(egress_device, channel_id);

	SecY_Rc = eip_macsec_egress_stats(port_id, channel_id, &egress_stats,
					  MACSEC_STATS_TXSC, ctx);
	if (SecY_Rc != SECY_STATUS_OK) {
		eip_logerr("eip_macsec_egress_stats()=%d\n", SecY_Rc);
		return SecY_Rc;
	}

	ctx->stats.tx_sc_stats->OutPktsProtected =
		egress_stats.tx_sc_stats.OutPktsProtected;
	ctx->stats.tx_sc_stats->OutPktsEncrypted =
		egress_stats.tx_sc_stats.OutPktsEncrypted;
	ctx->stats.tx_sc_stats->OutOctetsProtected =
		egress_stats.tx_sc_stats.OutOctetsProtected;
	ctx->stats.tx_sc_stats->OutOctetsEncrypted =
		egress_stats.tx_sc_stats.OutOctetsEncrypted;

	return SecY_Rc;
}

static int eip_mdo_get_tx_sa_stats(struct macsec_context *ctx)
{
	unsigned int egress_device, port_id, channel_id;
	uint32_t link_index;
	SecY_Status_t SecY_Rc = SECY_STATUS_OK;
	struct macsec_per_channel_info *ch_info_p = NULL;
	struct eip_macsec_stats egress_stats;
	uint32_t SA_Words[2] = { 0 };

	if (ctx->prepare) {
		return 0;
	}
	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);
	memset((void *)&egress_stats, 0, sizeof(egress_stats));
	get_egress_params_from_link_id(link_index, &port_id, &egress_device,
				       &channel_id);

	eip_loginfo("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		    port_id, channel_id);

	SecY_Rc = eip_macsec_egress_stats(port_id, channel_id, &egress_stats,
					  MACSEC_STATS_TXSA, ctx);
	if (SecY_Rc != SECY_STATUS_OK) {
		eip_logerr("eip_macsec_egress_stats()=%d\n", SecY_Rc);
		return SecY_Rc;
	}

	ctx->stats.tx_sa_stats->OutPktsProtected =
		egress_stats.tx_sa_stats.OutPktsProtected;
	ctx->stats.tx_sa_stats->OutPktsEncrypted =
		egress_stats.tx_sa_stats.OutPktsEncrypted;

	ch_info_p = get_eip_channel_info(egress_device, channel_id);

	if (!SecY_SAHandle_IsSame(&ch_info_p->SecY_SAHandle[ctx->sa.assoc_num],
				  &SecY_SAHandle_NULL)) {
		SecY_Rc = SecY_SA_Read(
			egress_device,
			ch_info_p->SecY_SAHandle[ctx->sa.assoc_num],
			SA_PN_SEQ_OFFSET, SA_WORD_COUNT, SA_Words);
		if (SecY_Rc != SECY_STATUS_OK) {
			eip_logerr("SecY_SA_Read returned error %d\n", SecY_Rc);
			return SecY_Rc;
		}
		ctx->sa.tx_sa->next_pn =
			STATS_2x32_TO_64(SA_Words[0], SA_Words[1]);
		eip_loginfo("Next PN Seq0 = %d : Seq1 = %d", SA_Words[0],
			    SA_Words[1]);
	}
	return SecY_Rc;
}

static int eip_mdo_get_rx_sc_stats(struct macsec_context *ctx)
{
	unsigned int ingress_device, port_id, channel_id;
	uint32_t link_index;
	struct eip_macsec_stats ingress_stats;
	int ret = 0;

	if (ctx->prepare) {
		return 0;
	}
	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);

	memset((void *)&ingress_stats, 0, sizeof(ingress_stats));
	get_ingress_params_from_link_id(link_index, &port_id, &ingress_device,
					&channel_id);

	eip_loginfo("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		    port_id, channel_id);

	ret = eip_macsec_ingress_stats(port_id, channel_id, &ingress_stats,
				       MACSEC_STATS_RXSC);
	if (ret) {
		return ret;
	}

	ctx->stats.rx_sc_stats->InOctetsValidated =
		ingress_stats.rx_sc_stats.InOctetsValidated;
	ctx->stats.rx_sc_stats->InOctetsDecrypted =
		ingress_stats.rx_sc_stats.InOctetsDecrypted;
	ctx->stats.rx_sc_stats->InPktsUnchecked =
		ingress_stats.rx_sc_stats.InPktsUnchecked;
	ctx->stats.rx_sc_stats->InPktsDelayed =
		ingress_stats.rx_sc_stats.InPktsDelayed;
	ctx->stats.rx_sc_stats->InPktsOK = ingress_stats.rx_sc_stats.InPktsOK;
	ctx->stats.rx_sc_stats->InPktsInvalid =
		ingress_stats.rx_sc_stats.InPktsInvalid;
	ctx->stats.rx_sc_stats->InPktsLate =
		ingress_stats.rx_sc_stats.InPktsLate;
	ctx->stats.rx_sc_stats->InPktsNotValid =
		ingress_stats.rx_sc_stats.InPktsNotValid;
	ctx->stats.rx_sc_stats->InPktsNotUsingSA =
		ingress_stats.rx_sc_stats.InPktsNotUsingSA;
	ctx->stats.rx_sc_stats->InPktsUnusedSA =
		ingress_stats.rx_sc_stats.InPktsUnusedSA;

	return ret;
}

static int eip_mdo_get_rx_sa_stats(struct macsec_context *ctx)
{
	unsigned int ingress_device, port_id, channel_id;
	uint32_t link_index;
	struct eip_macsec_stats ingress_stats;
	struct macsec_per_channel_info *ch_info_p = NULL;
	SecY_SAHandle_t SAHandles_Ingress[4] = { SecY_SAHandle_NULL };
	SecY_Status_t SecY_Rc = SECY_STATUS_OK;
	uint32_t SA_Words[24];
	uint8_t i;

	if (ctx->prepare) {
		return 0;
	}
	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);

	memset((void *)&ingress_stats, 0, sizeof(ingress_stats));
	get_ingress_params_from_link_id(link_index, &port_id, &ingress_device,
					&channel_id);
	ch_info_p = get_eip_channel_info(ingress_device, channel_id);

	eip_loginfo("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		    port_id, channel_id);

	SecY_Rc = eip_macsec_ingress_stats(port_id, channel_id, &ingress_stats,
					   MACSEC_STATS_RXSA);
	if (SecY_Rc != SECY_STATUS_OK) {
		eip_logerr("eip_macsec_ingress_stats()=%d\n", SecY_Rc);
		return SecY_Rc;
	}

	ctx->stats.rx_sa_stats->InPktsOK = ingress_stats.rx_sa_stats.InPktsOK;
	ctx->stats.rx_sa_stats->InPktsInvalid =
		ingress_stats.rx_sa_stats.InPktsInvalid;
	ctx->stats.rx_sa_stats->InPktsNotValid =
		ingress_stats.rx_sa_stats.InPktsNotValid;
	ctx->stats.rx_sa_stats->InPktsNotUsingSA =
		ingress_stats.rx_sa_stats.InPktsNotUsingSA;
	ctx->stats.rx_sa_stats->InPktsUnusedSA =
		ingress_stats.rx_sa_stats.InPktsUnusedSA;

	SecY_Rc = SecY_SA_Active_I_Get(ingress_device, ch_info_p->vPortIndex,
				       (uint8_t *)&ch_info_p->SCI_p[0],
				       SAHandles_Ingress);
	if (SecY_Rc != SECY_STATUS_OK) {
		eip_logerr("SecY_SA_Active_I_Get()=%d\n", SecY_Rc);
		return SecY_Rc;
	}

	for (i = 0; i < MACSEC_MAX_SA; i++) {
		if (!SecY_SAHandle_IsSame(&SAHandles_Ingress[i],
					  &SecY_SAHandle_NULL)) {
			SecY_Rc = SecY_SA_Read(ingress_device,
					       SAHandles_Ingress[i],
					       SA_PN_SEQ_OFFSET, SA_WORD_COUNT,
					       SA_Words);
			if (SecY_Rc != SECY_STATUS_OK) {
				eip_logerr("SecY_SA_Read returned error %d\n",
					   SecY_Rc);
				return SecY_Rc;
			}
			break;
		}
	}

	ctx->sa.rx_sa->next_pn = STATS_2x32_TO_64(SA_Words[0], SA_Words[1]);
	eip_loginfo("Next_PN Seq0 = %d : Seq1 = %d", SA_Words[0], SA_Words[1]);
	return SecY_Rc;
}

const struct macsec_ops eip_macsec_ops = {
	.mdo_dev_open = eip_mdo_dev_open,
	.mdo_dev_stop = eip_mdo_dev_stop,
	.mdo_add_secy = eip_mdo_add_secy,
	.mdo_upd_secy = eip_mdo_upd_secy,
	.mdo_del_secy = eip_mdo_del_secy,
	.mdo_add_rxsc = eip_mdo_add_rxsc,
	.mdo_upd_rxsc = eip_mdo_upd_rxsc,
	.mdo_del_rxsc = eip_mdo_del_rxsc,
	.mdo_add_rxsa = eip_mdo_add_rxsa,
	.mdo_upd_rxsa = eip_mdo_upd_rxsa,
	.mdo_del_rxsa = eip_mdo_del_rxsa,
	.mdo_add_txsa = eip_mdo_add_txsa,
	.mdo_upd_txsa = eip_mdo_upd_txsa,
	.mdo_del_txsa = eip_mdo_del_txsa,
	.mdo_get_dev_stats = eip_mdo_get_dev_stats,
	.mdo_get_tx_sc_stats = eip_mdo_get_tx_sc_stats,
	.mdo_get_tx_sa_stats = eip_mdo_get_tx_sa_stats,
	.mdo_get_rx_sc_stats = eip_mdo_get_rx_sc_stats,
	.mdo_get_rx_sa_stats = eip_mdo_get_rx_sa_stats
};
