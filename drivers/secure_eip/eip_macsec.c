//SPDX-License-Identifier: GPL-2.0-only

/*
* Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
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
#define CONTROL_ETYPE 0x888e	/* Ether type for control packets */
#define MACSEC_GET_LINK_ID(device_id, channel)\
                 4*device_id  + channel%4
#define MAX_CHANNELS_PER_PORT 4
#define STATS_2x32_TO_64(stat_field_Lo,stat_field_Hi )   \
            (((u64)stat_field_Hi << 32) | stat_field_Lo)

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
	CfyE_vPortHandle_t CfyE_vPortHandle[MACSEC_MAX_SA];
	uint32_t rx_sc_ptr_val[MACSEC_MAX_SA];
	sci_t secy_sci;
	unsigned int device_id;
	unsigned int channel;
	SecY_SA_t SA_Params[MACSEC_MAX_SA];
	bool associated[MACSEC_MAX_SA];
	uint8_t link_index;
	uint8_t SCI_p[8];
	bool valid;
};

struct macsec_per_channel_info_an {
	struct {
		unsigned int vPort;
		CfyE_RuleHandle_t CfyE_RuleHandle;
		SecY_SAHandle_t SecY_SAHandle;
		CfyE_vPortHandle_t CfyE_vPortHandle;
		sci_t secy_sci;
		unsigned int device_id;
		unsigned int channel;
		SecY_SA_t SA_Params;
		bool associated;
		uint8_t link_index;
		uint8_t SCI_p[8];
	} sa[MACSEC_MAX_SA];
	bool associated;
};

struct macsec_priv_data_info {
	struct macsec_device_info device_info[EIP_MAX_PORT];
	struct macsec_per_channel_info channel_info[MACSEC_MAX_LINK_IDS];

};

static inline void get_device_params_from_link_id(u32 link_index,
						  u32 * port_id,
						  u32 * ingress_device,
						  u32 * egress_device,
						  u32 * channel_id)
{
	*port_id = GET_PORT_ID_FROM_LINK_IDX(link_index);
	*ingress_device = GET_INGRESS_ID_FROM_DEVICE_ID(*port_id);
	*egress_device = GET_EGRESS_ID_FROM_DEVICE_ID(*port_id);
	*channel_id = GET_CHANNEL_ID_FROM_LINK_IDX(link_index);
}

static inline void get_ingress_params_from_link_id(u32 link_index,
						   u32 * port_id,
						   u32 * ingress_device,
						   u32 * channel_id)
{
	*port_id = GET_PORT_ID_FROM_LINK_IDX(link_index);
	*ingress_device = GET_INGRESS_ID_FROM_DEVICE_ID(*port_id);
	*channel_id = GET_CHANNEL_ID_FROM_LINK_IDX(link_index);
}

static inline void get_egress_params_from_link_id(u32 link_index,
						  u32 * port_id,
						  u32 * egress_device,
						  u32 * channel_id)
{
	*port_id = GET_PORT_ID_FROM_LINK_IDX(link_index);
	*egress_device = GET_EGRESS_ID_FROM_DEVICE_ID(*port_id);
	*channel_id = GET_CHANNEL_ID_FROM_LINK_IDX(link_index);
}

static SecY_SAHandle_t SecY_SAHandle;
static CfyE_vPortHandle_t CfyE_vPortHandle;
static unsigned int vPortIndex;
static CfyE_RuleHandle_t CfyE_RuleHandle;

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

#define MAX_CHANNELS_PER_PORT 4

#ifdef SECURE_MACSEC_DEBUG

static void dump_txsc(struct macsec_context *ctx)
{

	LOG_CRIT("****************** %s********************\n", __func__);
	if (ctx->secy == NULL) {
		LOG_CRIT("ctx->secy NULL, return;");
		return;
	}
	LOG_CRIT
	    ("active %d \n encoding sa %d\n encrypt %d \n send_sci %d\n endstation %d \n scb %d \n",
	     ctx->secy->tx_sc.active, ctx->secy->tx_sc.encoding_sa,
	     ctx->secy->tx_sc.encrypt, ctx->secy->tx_sc.send_sci,
	     ctx->secy->tx_sc.end_station, ctx->secy->tx_sc.scb);
	LOG_CRIT("sa[0] 0x%x\n sa[1] 0x%x\n sa[2] 0x%x\n",
		 ctx->secy->tx_sc.sa[0], ctx->secy->tx_sc.sa[1],
		 ctx->secy->tx_sc.sa[2]);

}

static void dump_rxsc(struct macsec_context *ctx)
{

	LOG_CRIT("****************** %s********************\n", __func__);

	if (ctx->rx_sc == NULL) {
		LOG_CRIT("ctx->rx_sc is NULL; return;");
		return;
	}
	LOG_CRIT
	    (" next ptr 0x%x\n sci 0x%x \n active %d \n sa[0] 0x%x\n, sa[1] 0x%x\n sa[2] 0x%x\n",
	     ctx->rx_sc->next, ctx->rx_sc->sci, ctx->rx_sc->active,
	     ctx->rx_sc->sa[0], ctx->rx_sc->sa[1], ctx->rx_sc->sa[2]);
}

static void dump_secy(struct macsec_context *ctx)
{

	LOG_CRIT("****************** %s********************\n", __func__);
	LOG_CRIT("AN = %d\n", ctx->sa.assoc_num);
	LOG_CRIT(" n_rx_sc = %d\n sci = 0x%x\n validate frames = %d\n",
		 ctx->secy->n_rx_sc, ctx->secy->sci,
		 ctx->secy->validate_frames);
	LOG_CRIT
	    (" xpn %d \n operational = %d\n protect_frames = %d \n replay_protect = %d\n replay_window = %d\n",
	     ctx->secy->xpn, ctx->secy->operational, ctx->secy->protect_frames,
	     ctx->secy->replay_protect, ctx->secy->replay_window);
	dump_txsc(ctx);
	dump_rxsc(ctx);
}

static void dump_rxsa(struct macsec_context *ctx)
{

	/* Dump the received RX SA details */
	LOG_CRIT("****************** %s********************\n", __func__);

	LOG_CRIT("AN = %d\n", ctx->sa.assoc_num);
	if (ctx->sa.rx_sa == NULL) {
		LOG_CRIT("ctx->sa.rx_sa is NULL; return ");
		return;
	}
	LOG_CRIT
	    ("ssci = %d\n next_pn = %d\n sc ptr 0x%x\n active = %d \n refcnt %d\n",
	     ctx->sa.rx_sa->ssci, ctx->sa.rx_sa->next_pn, ctx->sa.rx_sa->sc,
	     ctx->sa.rx_sa->active, ctx->sa.rx_sa->refcnt);

}

static void dump_txsa(struct macsec_context *ctx)
{
	LOG_CRIT("****************** %s********************\n", __func__);
	LOG_CRIT("AN = %d\n", ctx->sa.assoc_num);
	if (ctx->sa.tx_sa == NULL) {
		LOG_CRIT("ctx->sa.tx_sa is NULL; return ");
		return;
	}
	LOG_CRIT("ssci = %d\n next_pn = %d\n active = %d \n refcnt %d\n",
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

	LOG_CRIT
	    ("%s: n_rx_sc = %d \n sci = %lu \n key_len = %d \n icv_len = %d\n",
	     __func__, ctx->secy->n_rx_sc, ctx->secy->sci, ctx->secy->key_len,
	     ctx->secy->icv_len);
	LOG_CRIT
	    ("validate_frames = %d\n xpn=%d \n operational = %d \nprotect_frames=%d\n replay_protect = %d\n",
	     ctx->secy->validate_frames, ctx->secy->xpn, ctx->secy->operational,
	     ctx->secy->protect_frames, ctx->secy->replay_protect);
	LOG_CRIT
	    ("replay_window = %d\n tx_sc->active = %d\n tx_sc->encoding_sa = %d\n tx_sc->encrypt = %d\n tx_sc->send_sci=%d",
	     ctx->secy->replay_window, ctx->secy->tx_sc.active,
	     ctx->secy->tx_sc.encoding_sa, ctx->secy->tx_sc.encrypt,
	     ctx->secy->tx_sc.send_sci);
	LOG_CRIT("tx_sc->end_station = %d\n", ctx->secy->tx_sc.end_station);

	LOG_CRIT("ctx->rx_sc =0x%x\n ctx->sa.rx_sa 0x%x\n ctx->sa.tx_sa 0x%x\n",
		 ctx->rx_sc, ctx->sa.rx_sa, ctx->sa.tx_sa);
	{
		uint32_t i = 0;

		for (i = 0; i < 4; ++i)	//MAX SA of 4
		{
			LOG_CRIT("tx_sc->sa[0]= 0x%x\n ",
				 ctx->secy->tx_sc.sa[i]);

			if (ctx->secy->tx_sc.sa[i] != NULL) {
				uint8_t j = 0;
				for (j = 0; j < MACSEC_KEYID_LEN; ++j)
					LOG_CRIT("Key [j]=%d",
						 ctx->secy->tx_sc.sa[i]->key.
						 id[j]);
			}
		}
		if (NULL == ctx->secy->rx_sc) {
			LOG_CRIT("WPA NULL NULL return rx_Sc ");
		} else {
			LOG_CRIT
			    ("WPA rx_Sc = 0x%x rx_sc->sci =0x%x rx_sc->sa[0]=0x%x rx_sc->sa[1]=0x%x rx_sc->sa[2]=0x%x\n",
			     ctx->secy->rx_sc, ctx->secy->rx_sc->sci,
			     ctx->secy->rx_sc->sa[0], ctx->secy->rx_sc->sa[1],
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

static uint32_t *eip_macsec_build_sa(const da_sa_params_t * const params,
				     uint32_t * const SAWordCount_p)
{
	SABuilder_Params_t SAParams;
	SABuilder_Status_t rc;
	unsigned int SAWordCount;
	uint32_t *SABuffer_p;

	memset(&SAParams, 0, sizeof(SAParams));

	rc = SABuilder_InitParams(&SAParams,
				  params->AN,
				  params->direction, params->operation);
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

	uint32_t link_id, sa;
	struct macsec_per_channel_info *ch_info_p = NULL;

	/* Initialize channel info params to NULL */
	for (sa = 0; sa < MACSEC_MAX_SA; ++sa) {
		link_id = MACSEC_GET_LINK_ID(device_id, sa);
		LOG_CRIT("%d Device's Link id %d", device_id, link_id);
		ch_info_p = &macsec_priv_data.channel_info[link_id];
		ch_info_p->CfyE_RuleHandle[sa] = CfyE_RuleHandle_NULL;
		ch_info_p->SecY_SAHandle[sa] = SecY_SAHandle_NULL;
		ch_info_p->CfyE_vPortHandle[sa] = CfyE_vPortHandle_NULL;
	}
}

static int
eip_macsec_config_default_vport(bool fVerbose,
				bool fIngress,
				unsigned int device_id,
				unsigned int channel,
				struct macsec_context *ctx)
{
	struct macsec_device_info *dev_info_p;
	u32 port_id;
	CfyE_vPort_t vPortParams;
	SecY_SA_t SA_Params;
  int rc;

	port_id = GET_PORT_ID_FROM_DEVICE_ID(device_id);
	if (port_id >= EIP_MAX_PORT) {
		LOG_CRIT("%s: Invalid device ID %d", __func__, port_id);
		return -EINVAL;
	} else {
		dev_info_p = &macsec_priv_data.device_info[port_id];
	}

	Log_FormattedMessage("%s Starting test for %sgress\n",
			     __func__, fIngress ? "in" : "e");

	/* Initialize resource variables to NULL */
	SecY_SAHandle = SecY_SAHandle_NULL;
	CfyE_vPortHandle = CfyE_vPortHandle_NULL;
	CfyE_RuleHandle = CfyE_RuleHandle_NULL;

	/* Create default vPorts */
	ZEROINIT(vPortParams);
	vPortParams.SecTagOffset = EIP_MACSEC_SECTAG_OFFSET;
	vPortParams.PktExtension = EIP_MACSEC_EXPANSION_EXPLICIT_SCI;

	rc = CfyE_vPort_Add(device_id,
				 &CfyE_vPortHandle,
				 &vPortParams, CYFE_MODE_MACSEC);
	if (rc != CFYE_STATUS_OK) {
		LOG_CRIT("%s: Failed, CfyE_vPort_Add()=%d\n", __func__,
			 rc);
		goto error_exit;
	}

	/* Now get vPort index to use when installing SA: */
	CfyE_vPortIndex_Get(CfyE_vPortHandle, &vPortIndex);

	if (fVerbose) {
		Log_FormattedMessage
		    ("%s: D e f a u l t vPort added\n", __func__);
	}

	/* Install default SAs. */
	ZEROINIT(SA_Params);
	if (fIngress) {
		SA_Params.SA_WordCount = 0;
		SA_Params.TransformRecord_p = NULL;
		SA_Params.DropType = SECY_SA_DROP_CRC_ERROR;
		SA_Params.DestPort = SECY_PORT_CONTROLLED;
		SA_Params.ActionType = SECY_SA_ACTION_INGRESS;
		SA_Params.Params.Ingress.fSAInUse = false;
		SA_Params.Params.Ingress.ValidateFramesTagged =
		    SECY_FRAME_VALIDATE_DISABLE;
		SA_Params.Params.Ingress.fReplayProtect =
		    ctx->secy->replay_protect;
		memcpy(&dev_info_p->SCI_p[0], &ctx->secy->sci, 8);
		SA_Params.Params.Ingress.SCI_p = &dev_info_p->SCI_p[0];
		SA_Params.Params.Ingress.AN = 0;
		SA_Params.Params.Ingress.fAllowTagged = false;
		SA_Params.Params.Ingress.fAllowUntagged = false;
		SA_Params.Params.Ingress.PreSecTagAuthLength = 12;
	}

	if (!fIngress) {
		SA_Params.DropType = SECY_SA_DROP_INTERNAL;
		SA_Params.DestPort = SECY_PORT_COMMON;
		SA_Params.SA_WordCount = 0;
		SA_Params.TransformRecord_p = NULL;
		SA_Params.ActionType = SECY_SA_ACTION_EGRESS;
		SA_Params.Params.Egress.fSAInUse = false;
		SA_Params.Params.Egress.fProtectFrames = false;
		SA_Params.Params.Egress.fIncludeSCI = false;
		SA_Params.Params.Egress.fConfProtect = false;
		SA_Params.Params.Egress.fAllowDataPkts = false;
		SA_Params.Params.Egress.PreSecTagAuthLength = 12;
	}

	rc = SecY_SA_Add(device_id, vPortIndex,
			      &SecY_SAHandle, &SA_Params);
	if (rc != SECY_STATUS_OK) {
		LOG_CRIT("%s: Failed, SecY_SA_Add()=%d\n", __func__, rc);
		goto error_exit;
	}
	dev_info_p->SecY_SAHandleDefault = SecY_SAHandle;
	dev_info_p->vPortDefault = vPortIndex;

	/* SecY_SA_Add() creates SA that is always enabled, disable it
	   by calling SecY_SA_Update(). This does not apply to the
	   bypass SA in should-secure */
	rc = SecY_SA_Update(device_id, SecY_SAHandle, &SA_Params);

	if (rc != SECY_STATUS_OK) {
		LOG_CRIT
		    ("%s: Failed, SecY_SA_Update()=%d\n", __func__, rc);
		goto error_exit;
	}

	if (SA_Params.TransformRecord_p) {
		kfree_sensitive(SA_Params.TransformRecord_p);
	}

	if (fVerbose) {
		Log_FormattedMessage
		    ("%s: D e f a u l t  SA for vPort added\n", __func__);
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
		CP.CPMatchEnableMask = BIT_8;	/* Enable Etype[0] matching */
		CP.CPMatchModeMask = BIT_0;	/* Etype[0] matching after VLAN tag */
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
		VLANTagParams.QTag =  ETH_P_8021Q;
		VLANTagParams.STag1 =  ETH_P_QINQ2; 

		HeaderParams.VLAN_Parser_p = &VLANTagParams;
		DeviceParams.HeaderParser_p = &HeaderParams;
		DeviceExceptions.DefaultVPort = vPortIndex;
		rc =
				CfyE_Device_Update(device_id, channel, &DeviceParams);
		if (rc != CFYE_STATUS_OK) {
			LOG_CRIT
					("DA_MACSEC: CfyE device could not be updated, error=%d\n",
					 rc);
			goto error_exit;
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
 error_exit:

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

static int
eip_macsec_delete_sa(bool fVerbose,
		     bool fIngress,
		     unsigned int device_id,
		     unsigned int Channel, struct macsec_context *ctx)
{
  int rc = 0;
	u32 sa;
	u32 link_id;
	struct macsec_per_channel_info *ch_info_p;

	link_id = MACSEC_GET_LINK_ID(device_id, Channel);
	ch_info_p = &macsec_priv_data.channel_info[link_id];

	sa = ctx->sa.assoc_num;
	if (sa >= MACSEC_MAX_SA) {
		LOG_CRIT("%s: Invalid SA/AN received ", __func__, sa);
		return false;
	}

	if (!CfyE_RuleHandle_IsSame
	    (ch_info_p->CfyE_RuleHandle[sa], CfyE_RuleHandle_NULL)) {
		CfyE_Rule_Disable(device_id,
				  ch_info_p->CfyE_RuleHandle[sa], true);
		CfyE_Rule_Remove(device_id, ch_info_p->CfyE_RuleHandle[sa]);
		ch_info_p->CfyE_RuleHandle[sa] = CfyE_RuleHandle_NULL;
		LOG_INFO("%s: Deleted CfyE_Rule %d SA", __func__, sa);
	} else {
		rc = -EINVAL;
	}
	if (!CfyE_vPortHandle_IsSame
	    (ch_info_p->CfyE_vPortHandle[sa], CfyE_vPortHandle_NULL)) {
		CfyE_vPort_Remove(device_id, ch_info_p->CfyE_vPortHandle[sa]);
		ch_info_p->CfyE_vPortHandle[sa] = CfyE_vPortHandle_NULL;
		LOG_INFO("%s: Deleted CfyE_vPort %d SA", __func__, sa);
	} else {
		rc = -EINVAL;
	}
	if (!SecY_SAHandle_IsSame
	    (&ch_info_p->SecY_SAHandle[sa], &SecY_SAHandle_NULL)) {
		SecY_SA_Remove(device_id, ch_info_p->SecY_SAHandle[sa]);
		ch_info_p->SecY_SAHandle[sa] = SecY_SAHandle_NULL;
		LOG_INFO("%s: Deleted SecY_SA %d SA", __func__, sa);
	} else {
		rc = -EINVAL;
	}

	if (!rc) {
		ch_info_p->associated[sa] = false;
	}
	return rc;
}

static int
eip_macsec_add_secy(bool fVerbose,
		    bool fIngress,
		    unsigned int device_id,
		    unsigned int Channel, struct macsec_context *ctx)
{

	unsigned int link_id;
	struct macsec_per_channel_info *ch_info_p;  

	link_id = MACSEC_GET_LINK_ID(device_id, Channel);
	ch_info_p =
				&macsec_priv_data.channel_info[link_id];


	LOG_INFO("%s: Link ID = %d Device %d Channel %d\n", __func__, link_id,
		 device_id, Channel);

	Log_FormattedMessage("%s Config for %sgress device id %d Channel %d ",
			     __func__, fIngress ? "in" : "e", device_id,
			     Channel);

	memcpy(&ch_info_p->secy_sci, &ctx->secy->sci, sizeof(sci_t));

	/* Add default cfye port and secy port */
	if (eip_macsec_config_default_vport
	    (fVerbose, fIngress, device_id, Channel, ctx) <0) {
		LOG_CRIT("%s: Ingress mode Device_ID %d FAILED\n", __func__,
			 device_id);
		return -EINVAL;
	}

	dump_ctx_values(ctx, false);

	return 0;
}

static int
eip_macsec_upd_secy(bool fVerbose,
		    bool fIngress,
		    unsigned int device_id,
		    unsigned int Channel, struct macsec_context *ctx)
{

	u32 link_id;
	SecY_Status_t SecY_Rc;
	SecY_SA_t *SA_Params;

	link_id = MACSEC_GET_LINK_ID(device_id, Channel);

	LOG_INFO("%s: Link ID = %d Device %d Channel %d\n", __func__, link_id,
		 device_id, Channel);

	Log_FormattedMessage("%s Config for %sgress device id %d Channel %d ",
			     __func__, fIngress ? "in" : "e", device_id,
			     Channel);
	if (ctx->sa.assoc_num >= MACSEC_NUM_AN) {
		LOG_CRIT("Invalid AN %d\n", ctx->sa.assoc_num);
		return false;
	}

	SA_Params =
	    &macsec_priv_data.channel_info[link_id].SA_Params[ctx->
							      sa.assoc_num];
	ZEROINIT(*SA_Params);

	if (fIngress) {
		SA_Params->SA_WordCount = 0;
		SA_Params->TransformRecord_p = NULL;
		SA_Params->ActionType = SECY_SA_ACTION_INGRESS;
		SA_Params->DropType = SECY_SA_DROP_CRC_ERROR;
		SA_Params->DestPort = SECY_PORT_CONTROLLED;
		SA_Params->Params.Ingress.ValidateFramesTagged =
		    (SecY_ValidateFrames_t) ctx->secy->validate_frames;
		SA_Params->Params.Ingress.fReplayProtect =
		    ctx->secy->replay_protect;
		SA_Params->Params.Ingress.AN = ctx->sa.assoc_num;
		LOG_INFO("%s: AN = %d\n", __func__, ctx->sa.assoc_num);
		SA_Params->Params.Ingress.fAllowTagged = true;
		SA_Params->Params.Ingress.PreSecTagAuthLength = 12;
		SA_Params->SA_WordCount = 0;
	}

	if (!fIngress) {
		SA_Params->ActionType = SECY_SA_ACTION_EGRESS;
		SA_Params->DropType = SECY_SA_DROP_INTERNAL;
		SA_Params->DestPort = SECY_PORT_COMMON;

		SA_Params->Params.Egress.fProtectFrames =
		    ctx->secy->tx_sc.encrypt;
		SA_Params->Params.Egress.fIncludeSCI =
		    ctx->secy->tx_sc.send_sci;
		SA_Params->Params.Egress.fConfProtect = true;
		SA_Params->Params.Egress.fAllowDataPkts = true;
		SA_Params->Params.Egress.PreSecTagAuthLength = 12;
		SA_Params->SA_WordCount = 0;
	}
	/* find secy_index and fetch SAHandle */
	SecY_Rc =
	    SecY_SA_Update(device_id,
			   macsec_priv_data.device_info
			   [device_id].SecY_SAHandleDefault, SA_Params);

	if (SecY_Rc != SECY_STATUS_OK) {
		LOG_CRIT("%s: Failed, SecY_SA_Update()=%d\n", __func__,
			 SecY_Rc);
		goto error_exit;
	}

	LOG_INFO("%s: Sucessfully Exiting update secy ", __func__);
	dump_ctx_values(ctx, false);

	return SecY_Rc;

 error_exit:

	LOG_CRIT("%s: Failed, exiting ", __func__);
	ZEROINIT(*SA_Params);
	return SecY_Rc;
}

static int
eip_macsec_config_sa(bool fVerbose,
		     bool fIngress,
		     unsigned int device_id,
		     unsigned int Channel, struct macsec_context *ctx)
{
	u32 SAWordCount = 0;
	u32 link_id;
	SecY_SA_t *SA_Params;
	struct macsec_per_channel_info *ch_info_p;

	link_id = MACSEC_GET_LINK_ID(device_id, Channel);
	ch_info_p = &macsec_priv_data.channel_info[link_id];

	Log_FormattedMessage("%s config %sgress\n Device ID = %d Channel = %d",
			     __func__, fIngress ? "in" : "e", device_id,
			     Channel);
	LOG_INFO("%s: Link ID = %d Device %d Channel %d\n", __func__, link_id,
		 device_id, Channel);

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
		SA_Params->Params.Ingress.ValidateFramesTagged =
		    SECY_FRAME_VALIDATE_STRICT;
		SA_Params->Params.Ingress.fReplayProtect = true;
		SA_Params->Params.Ingress.SCI_p =
		    (uint8_t *) & ch_info_p->SCI_p[0];
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
		params.SCI_p = (uint8_t *) & ch_info_p->SCI_p[0];
		params.SeqMask = 0;
		params.SeqNumHi = 0;
		params.SeqNumLo = 0;
		params.SSCI_p = NULL;
		SA_Params->TransformRecord_p =
		    eip_macsec_build_sa(&params, &SAWordCount);
		SA_Params->SA_WordCount = SAWordCount;

	}

	if (!fIngress) {
		da_sa_params_t params;

		SA_Params->ActionType = SECY_SA_ACTION_EGRESS;
		SA_Params->DropType = SECY_SA_DROP_INTERNAL;
		SA_Params->DestPort = SECY_PORT_COMMON;

		SA_Params->Params.Egress.fProtectFrames = true;
		SA_Params->Params.Egress.fIncludeSCI = true;
		SA_Params->Params.Egress.fConfProtect = true;
		SA_Params->Params.Egress.fAllowDataPkts = true;
		SA_Params->Params.Egress.PreSecTagAuthLength = 12;
		SA_Params->Params.Egress.fSAInUse = true;
		params.direction = SAB_DIRECTION_EGRESS;
		params.flags = 0;
		params.KeyByteCount = ctx->secy->key_len;
		params.Key_p = &ctx->sa.key[0];
		params.operation = SAB_OP_MACSEC;
		params.Salt_p = NULL;
		params.SCI_p = (uint8_t *) & ctx->secy->sci;
		params.SeqMask = 0;
		params.SeqNumHi = 0;
		params.SeqNumLo = 0;
		params.SSCI_p = NULL;
		SA_Params->TransformRecord_p =
		    eip_macsec_build_sa(&params, &SAWordCount);
		SA_Params->SA_WordCount = SAWordCount;
	}

	dump_ctx_values(ctx, false);
	return 0;

}

static int
eip_macsec_add_sa(bool fVerbose,
		  bool fIngress,
		  unsigned int device_id,
		  unsigned int Channel, struct macsec_context *ctx)
{
	int rc;
	CfyE_vPort_t vPortParams;
	SecY_SA_t *SA_Params;
	CfyE_Rule_t RuleParams;
	unsigned int link_id = MACSEC_GET_LINK_ID(device_id, Channel);
	struct macsec_per_channel_info *ch_info_p =
	    &macsec_priv_data.channel_info[link_id];

	Log_FormattedMessage("%s DA_MACSEC: Starting test for %sgress\n",
			     __func__, fIngress ? "in" : "e");
	LOG_INFO("%s: link id %d device %d channel %d", __func__, link_id,
		 device_id, Channel);

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

	if (!ch_info_p->associated[ctx->sa.assoc_num]) {
		LOG_CRIT
		    ("%s: Channel is being setup for the first time", __func__);
		    
		vPortParams.SecTagOffset = EIP_MACSEC_SECTAG_OFFSET;	/* vPort 2 has no VLAN tag */
		vPortParams.PktExtension = EIP_MACSEC_EXPANSION_EXPLICIT_SCI;

		rc = CfyE_vPort_Add(device_id,
					 &CfyE_vPortHandle,
					 &vPortParams, CYFE_MODE_MACSEC);
		if (rc != CFYE_STATUS_OK) {
			LOG_CRIT
			    ("%s: Failed, CfyE_vPort_Add()=%d\n",
			     __func__, rc);
			goto error_exit;
		}

		/* Now get vPort index to use when installing SA: */
		CfyE_vPortIndex_Get(CfyE_vPortHandle, &vPortIndex);

		rc =
		    SecY_SA_Add(device_id, vPortIndex,
				&SecY_SAHandle, SA_Params);
		if (rc != SECY_STATUS_OK) {
			LOG_CRIT
			    ("%s: Failed, SecY_SA_Add()=%d\n", __func__,
			     rc);
			goto error_exit;
		}

	} else {
		SecY_SAHandle_t active_SA_Handle[4];
		uint16_t index = 0;

		rc =
		    SecY_SA_Chain(device_id, active_SA_Handle[index],
				  &ch_info_p->SecY_SAHandle[0], SA_Params);
		LOG_CRIT
		    ("Setting up SA Chain, with old handle 0x%x, new handle 0x%x",
		     active_SA_Handle[index],
		     ch_info_p->SecY_SAHandle[ctx->sa.assoc_num]);
		LOG_CRIT("Actual valid SA handle = 0x%x",
			 ch_info_p->SecY_SAHandle[0]);
		rc = SecY_SA_Remove(device_id, active_SA_Handle[index]);
	}
	if (fVerbose) {
		Log_FormattedMessage
		    ("%s: Transform 32-bit word count %d\n", __func__,
		     SA_Params->SA_WordCount);
		Log_HexDump32("DA_MACSEC: Transform data", 0,
			      SA_Params->TransformRecord_p,
			      SA_Params->SA_WordCount);
	}

	if (SA_Params->TransformRecord_p) {
		kfree_sensitive(SA_Params->TransformRecord_p);
	}

	if (fVerbose) {
		Log_FormattedMessage
		    ("%s: MACsec SA for vPort added\n", __func__);
	}
	if (!ch_info_p->associated[ctx->sa.assoc_num]) {
		ch_info_p->SecY_SAHandle[ctx->sa.assoc_num] = SecY_SAHandle;
		ch_info_p->vPort[ctx->sa.assoc_num] = vPortIndex;

		LOG_CRIT
		    ("%s: Secy Add handle 0x%xpk vport index %d at link %d secy_index %d\n",
		     __func__,
		     ch_info_p->SecY_SAHandle[ctx->sa.assoc_num],
		     ch_info_p->vPort[ctx->sa.assoc_num], link_id,
		     ctx->sa.assoc_num);

		RuleParams.Policy.vPortHandle = CfyE_vPortHandle;
		/* Exact match on channel, no other fields to match on. */
		RuleParams.Mask.ChannelID = 0x3f;
		RuleParams.Key.ChannelID = Channel;

		rc = CfyE_Rule_Add(device_id, CfyE_vPortHandle,
					&CfyE_RuleHandle, &RuleParams);
		if (rc != CFYE_STATUS_OK) {
			LOG_CRIT
			    ("%s: Failed, CfyE_Rule_Add()=%d\n",
			     __func__, rc);
			goto error_exit;
		}

		rc = CfyE_Rule_Enable(device_id, CfyE_RuleHandle, true);
		if (rc != CFYE_STATUS_OK) {
			LOG_CRIT
			    ("%s: Failed, CfyE_Rule_Enable()=%d\n",
			     __func__, rc);
			goto error_exit;
		}

		ch_info_p->CfyE_RuleHandle[ctx->sa.assoc_num] = CfyE_RuleHandle;
		ch_info_p->CfyE_vPortHandle[ctx->sa.assoc_num] =
		    CfyE_vPortHandle;

		if (fVerbose) {
			Log_FormattedMessage
			    ("%s: Rule enabled for vPort \n", __func__);
		}
		ch_info_p->valid = true;

	}

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

int eip_device_deinit(bool fVerbose, bool fIngress,
			      unsigned int device_id)
{
	unsigned int link_id;
	uint32_t sa;
	struct macsec_per_channel_info *ch_info_p;

	for (sa = 0; sa < MACSEC_MAX_SA; sa++) {

		link_id = MACSEC_GET_LINK_ID(device_id, sa);
		LOG_CRIT("%d Port id's Link id %d", device_id, link_id);
		ch_info_p = &macsec_priv_data.channel_info[link_id];
		if (!CfyE_RuleHandle_IsSame
		    (ch_info_p->CfyE_RuleHandle[sa], CfyE_RuleHandle_NULL)) {
			LOG_CRIT("device id %d CfyE_RuleHandle[%d] = 0x%x",
				 device_id, sa, ch_info_p->CfyE_RuleHandle[sa]);
			CfyE_Rule_Disable(device_id,
					  ch_info_p->CfyE_RuleHandle[sa], true);
			CfyE_Rule_Remove(device_id,
					 ch_info_p->CfyE_RuleHandle[sa]);
			ch_info_p->CfyE_RuleHandle[sa] = CfyE_RuleHandle_NULL;
		}
		if (!CfyE_vPortHandle_IsSame
		    (ch_info_p->CfyE_vPortHandle[sa], CfyE_vPortHandle_NULL)) {
			LOG_CRIT("device id %d CfyE_vPortHandle[%d] = 0x%x",
				 device_id, sa, ch_info_p->CfyE_vPortHandle[sa]);
			CfyE_vPort_Remove(device_id,
					  ch_info_p->CfyE_vPortHandle[sa]);
			ch_info_p->CfyE_vPortHandle[sa] = CfyE_vPortHandle_NULL;
		}
		if (!SecY_SAHandle_IsSame
		    (&ch_info_p->SecY_SAHandle[sa], &SecY_SAHandle_NULL)) {
			LOG_CRIT("device id %d SecY_SAHandle[%d] = 0x%x",
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

static int
eip_macsec_config_sc(bool fVerbose,
		     bool fIngress,
		     unsigned int device_id,
		     unsigned int Channel, struct macsec_context *ctx)
{
	unsigned int link_id;
	struct macsec_per_channel_info *ch_info_p;

	link_id = MACSEC_GET_LINK_ID(device_id, Channel);
	ch_info_p =
				&macsec_priv_data.channel_info[link_id];

	LOG_INFO("%s for %cxsc config", __func__,
		 (fIngress == true) ? 'r' : 't');

	if (fIngress) {
		memcpy(&ch_info_p->SCI_p[0], &ctx->rx_sc->sci, 8);
	}
	dump_ctx_values(ctx, false);
	return 0;

}

static int
eip_macsec_channel_stop(bool fVerbose,
			bool fIngress,
			unsigned int device_id, unsigned int channel)
{
	unsigned int link_id;
	struct macsec_per_channel_info *ch_info_p;
	
	link_id = MACSEC_GET_LINK_ID(device_id, channel);
	ch_info_p =
				&macsec_priv_data.channel_info[link_id];

	LOG_INFO("%s: Link ID = %d Device %d Channel %d\n", __func__, link_id,
		 device_id, channel);

	/* Remove any and all resources of a channel */
	if (!CfyE_RuleHandle_IsSame
	    (ch_info_p->CfyE_RuleHandle[channel], CfyE_RuleHandle_NULL)) {
		CfyE_Rule_Disable(device_id,
				  ch_info_p->CfyE_RuleHandle[channel], true);
		CfyE_Rule_Remove(device_id,
				 ch_info_p->CfyE_RuleHandle[channel]);
		ch_info_p->CfyE_RuleHandle[channel] = CfyE_RuleHandle_NULL;
	}
	if (!CfyE_vPortHandle_IsSame
	    (ch_info_p->CfyE_vPortHandle[channel], CfyE_vPortHandle_NULL)) {
		CfyE_vPort_Remove(device_id,
				  ch_info_p->CfyE_vPortHandle[channel]);
		ch_info_p->CfyE_vPortHandle[channel] = CfyE_vPortHandle_NULL;
	}
	if (!SecY_SAHandle_IsSame
	    (&ch_info_p->SecY_SAHandle[channel], &SecY_SAHandle_NULL)) {
		SecY_SA_Remove(device_id, ch_info_p->SecY_SAHandle[channel]);
		ch_info_p->SecY_SAHandle[channel] = SecY_SAHandle_NULL;
	}
	ch_info_p->associated[channel] = false;

	return 0;
}

static int
eip_macsec_egress_stats(bool fVerbose,
			unsigned int port_id,
			unsigned int channel,
			struct eip_macsec_stats *stats,
			enum stats_type stats_type)
{
	SecY_Status_t SecY_Rc;
	uint32_t link_id;
	unsigned int vPort;
	unsigned int egress_device_id;
	unsigned int i = 0;
	bool valid = false;
	struct macsec_per_channel_info *ch_info_p = NULL;

	egress_device_id = GET_EGRESS_ID_FROM_DEVICE_ID(port_id);
	link_id = MACSEC_GET_LINK_ID(egress_device_id, channel);
	ch_info_p = &macsec_priv_data.channel_info[link_id];

	do {

		valid =
		    !SecY_SAHandle_IsSame(&ch_info_p->SecY_SAHandle[i],
					  &SecY_SAHandle_NULL);

		if (valid) {
			LOG_INFO("%s: SA = %d , Link %d channel %d",__func__, i, link_id, channel);
			vPort = ch_info_p->vPort[i];
			if ((stats_type == MACSEC_STATS_DEV)
			    || (stats_type == MACSEC_STATS_TXSC)
			    || (stats_type == MACSEC_STATS_TXSA)) {
				SecY_SA_Stat_E_t SAStats;

				ZEROINIT(SAStats);

				/* Read out egress SA statistics, */
				/* request device synchronization before reading out statistics */
				SecY_Rc =
				    SecY_SA_Statistics_E_Get
				    (egress_device_id,
				     ch_info_p->SecY_SAHandle[i],
				     &SAStats, true);
				if (SecY_Rc != SECY_STATUS_OK) {
					LOG_CRIT
					    ("%s: Failed, SecY_SA_Statistics_E_Get()=%d\n",
					     __func__, SecY_Rc);
					//goto error_exit;
				} else if (fVerbose)

					/* Assume that any counters are less than 2^32, so we can just display */
					/* the low halves of the 64-bit counters */
					Log_FormattedMessage
					    ("DA_MACSEC: WPA Egress SA Statistics:\n"
					     "\tOutOctetsEncryptedProtected: %u\n"
					     "\tOutPktsEncryptedProtected:	 %u\n"
					     "\tOutPktsTooLong: 						 %u\n"
					     "\tOutPktsSANotInUse:					 %u\n",
					     SAStats.
					     OutOctetsEncryptedProtected.
					     Lo,
					     SAStats.
					     OutPktsEncryptedProtected.
					     Lo,
					     SAStats.
					     OutPktsTooLong.
					     Lo, SAStats.OutPktsSANotInUse.Lo);

				stats->dev_stats.OutPktsTooLong +=
				    STATS_2x32_TO_64
				    (SAStats.OutPktsTooLong.Lo,
				     SAStats.OutPktsTooLong.Hi);

				stats->tx_sc_stats.OutPktsProtected +=
				    STATS_2x32_TO_64
				    (SAStats.OutPktsEncryptedProtected.Lo,
				     SAStats.OutPktsEncryptedProtected.Hi);
				stats->tx_sc_stats.OutPktsEncrypted +=
				    STATS_2x32_TO_64
				    (SAStats.OutPktsEncryptedProtected.Lo,
				     SAStats.OutPktsEncryptedProtected.Hi);
				stats->tx_sc_stats.OutOctetsProtected +=
				    STATS_2x32_TO_64
				    (SAStats.OutOctetsEncryptedProtected.Lo,
				     SAStats.OutOctetsEncryptedProtected.Hi);
				stats->tx_sc_stats.OutOctetsEncrypted +=
				    STATS_2x32_TO_64
				    (SAStats.OutOctetsEncryptedProtected.Lo,
				     SAStats.OutOctetsEncryptedProtected.Hi);

			}
			if (stats_type == MACSEC_STATS_DEV) {
				SecY_SecY_Stat_E_t SecYStats;

				ZEROINIT(SecYStats);

				/* Read the SecY ingress statistics counters. */
				/* Sync with the SecY device to get the exact counters values */
				SecY_Rc =
				    SecY_SecY_Statistics_E_Get
				    (egress_device_id, vPort, &SecYStats, true);
				if (SecY_Rc != SECY_STATUS_OK) {
					LOG_CRIT
					    ("%s: Failed, SecY_SecY_Statistics_E_Get()=%d\n",
					     __func__, SecY_Rc);
					//goto error_exit;
				} else if (fVerbose)

					/* Assume that any counters are less than 2^32, so we can just display */
					/* the low halves of the 64-bit counters */
					Log_FormattedMessage
					    ("DA_MACSEC: Egress SecY(%d) Statistics:\n"
					     "\tTransform E r r o r Packets Counter: %u\n"
					     "\tEgress Controlled Packets Counter:	 %u\n"
					     "\tEgress Untagged Packets Counter:		 %u\n",
					     vPort,
					     SecYStats.
					     OutPktsTransformError.Lo,
					     SecYStats.OutPktsControl.
					     Lo, SecYStats.OutPktsUntagged.Lo);

				stats->dev_stats.OutPktsUntagged +=
				    STATS_2x32_TO_64
				    (SecYStats.OutPktsUntagged.Lo,
				     SecYStats.OutPktsUntagged.Hi);
			}
		}
		++i;
	} while (i < MACSEC_MAX_SA);

	return 0;

}

static int
eip_macsec_ingress_stats(bool fVerbose,
			 unsigned int port_id,
			 unsigned int channel,
			 struct eip_macsec_stats *stats,
			 enum stats_type stats_type)
{
	SecY_Status_t SecY_Rc;
	uint32_t link_id;
	unsigned int vPort;
	unsigned int ingress_device_id;
	unsigned int i = 0;
	bool valid = false;
	struct macsec_per_channel_info *ch_info_p = NULL;

	ingress_device_id = GET_INGRESS_ID_FROM_DEVICE_ID(port_id);

	link_id = MACSEC_GET_LINK_ID(ingress_device_id, channel);

	ch_info_p = &macsec_priv_data.channel_info[link_id];

	do {

		valid =
		    !SecY_SAHandle_IsSame(&ch_info_p->SecY_SAHandle[i],
					  &SecY_SAHandle_NULL);

		if (valid) {
			LOG_INFO("%s: SA = %d , Link %d channel %d",__func__, i, link_id, channel);
			vPort = ch_info_p->vPort[i];

			if ((stats_type == MACSEC_STATS_RXSC)
			    || (stats_type == MACSEC_STATS_RXSA)) {
				SecY_SA_Stat_I_t SAStats;

				ZEROINIT(SAStats);

				/* Read the SA ingress statistics counters, */
				/* request device synchronization before reading out the statistics */
				SecY_Rc =
				    SecY_SA_Statistics_I_Get
				    (ingress_device_id,
				     ch_info_p->SecY_SAHandle[i],
				     &SAStats, true);
				if (SecY_Rc != SECY_STATUS_OK) {
					LOG_CRIT
					    ("%s: Failed, SecY_SA_Statistics_I_Get()=%d\n",
					     __func__, SecY_Rc);
					//goto error_exit;
				} else if (fVerbose)
					/* Assume that any counters are less than 2^32, so we can just display */
					/* the low halves of the 64-bit counters */
					Log_FormattedMessage
					    ("DA_MACSEC:WPA Ingress SA Statistics:\n"
					     "\tInOctetsDecrypted: %u\n"
					     "\tInOctetsValidated: %u\n"
					     "\tInPktsDelayed:     %u\n"
					     "\tInPktsInvalid:     %u\n"
					     "\tInPktsLate:        %u\n"
					     "\tInPktsNotUsingSA:  %u\n"
					     "\tInPktsNotValid:    %u\n"
					     "\tInPktsOK:          %u\n"
					     "\tInPktsUnchecked:   %u\n"
					     "\tInPktsUnusedSA:    %u\n",
					     SAStats.InOctetsDecrypted.Lo,
					     SAStats.InOctetsValidated.Lo,
					     SAStats.InPktsDelayed.Lo,
					     SAStats.InPktsInvalid.Lo,
					     SAStats.InPktsLate.Lo,
					     SAStats.InPktsNotUsingSA.Lo,
					     SAStats.InPktsNotValid.Lo,
					     SAStats.InPktsOK.Lo,
					     SAStats.InPktsUnchecked.Lo,
					     SAStats.InPktsUnusedSA.Lo);

				stats->rx_sc_stats.InOctetsValidated +=
				    STATS_2x32_TO_64
				    (SAStats.InOctetsValidated.Lo,
				     SAStats.InOctetsValidated.Hi);
				stats->rx_sc_stats.InOctetsDecrypted +=
				    STATS_2x32_TO_64
				    (SAStats.InOctetsDecrypted.Lo,
				     SAStats.InOctetsDecrypted.Hi);
				stats->rx_sc_stats.InPktsUnchecked +=
				    STATS_2x32_TO_64
				    (SAStats.InPktsUnchecked.Lo,
				     SAStats.InPktsUnchecked.Hi);
				stats->rx_sc_stats.InPktsDelayed +=
				    STATS_2x32_TO_64
				    (SAStats.InPktsDelayed.Lo,
				     SAStats.InPktsDelayed.Hi);
				stats->rx_sc_stats.InPktsOK +=
				    STATS_2x32_TO_64(SAStats.InPktsOK.Lo,
						     SAStats.InPktsOK.Hi);
				stats->rx_sc_stats.InPktsInvalid +=
				    STATS_2x32_TO_64
				    (SAStats.InPktsInvalid.Lo,
				     SAStats.InPktsInvalid.Hi);
				stats->rx_sc_stats.InPktsLate +=
				    STATS_2x32_TO_64(SAStats.InPktsLate.Lo,
						     SAStats.InPktsLate.Hi);
				stats->rx_sc_stats.InPktsNotValid +=
				    STATS_2x32_TO_64
				    (SAStats.InPktsNotValid.Lo,
				     SAStats.InPktsNotValid.Hi);
				stats->rx_sc_stats.InPktsNotUsingSA +=
				    STATS_2x32_TO_64
				    (SAStats.InPktsNotUsingSA.Lo,
				     SAStats.InPktsNotUsingSA.Hi);
				stats->rx_sc_stats.InPktsUnusedSA +=
				    STATS_2x32_TO_64
				    (SAStats.InPktsUnusedSA.Lo,
				     SAStats.InPktsUnusedSA.Hi);

				stats->rx_sa_stats.InPktsOK +=
				    STATS_2x32_TO_64(SAStats.InPktsOK.Lo,
						     SAStats.InPktsOK.Hi);;
				stats->rx_sa_stats.InPktsInvalid +=
				    STATS_2x32_TO_64
				    (SAStats.InPktsInvalid.Lo,
				     SAStats.InPktsInvalid.Hi);;
				stats->rx_sa_stats.InPktsNotValid +=
				    STATS_2x32_TO_64
				    (SAStats.InPktsNotValid.Lo,
				     SAStats.InPktsNotValid.Hi);;
				stats->rx_sa_stats.InPktsNotUsingSA +=
				    STATS_2x32_TO_64
				    (SAStats.InPktsNotUsingSA.Lo,
				     SAStats.InPktsNotUsingSA.Hi);;
				stats->rx_sa_stats.InPktsUnusedSA +=
				    STATS_2x32_TO_64
				    (SAStats.InPktsUnusedSA.Lo,
				     SAStats.InPktsUnusedSA.Hi);;

			}
			if (stats_type == MACSEC_STATS_DEV) {
				SecY_SecY_Stat_I_t SecYStats;

				ZEROINIT(SecYStats);

				/* Read the SecY ingress statistics counters. */
				/* Sync with the SecY device to get the exact counters values */
				SecY_Rc =
				    SecY_SecY_Statistics_I_Get
				    (ingress_device_id, vPort,
				     &SecYStats, true);
				if (SecY_Rc != SECY_STATUS_OK) {
					LOG_CRIT
					    ("%s: Failed, SecY_SecY_Statistics_I_Get()=%d\n",
					     __func__, SecY_Rc);
					//goto error_exit;
				} else if (fVerbose)

					/* Assume that any counters are less than 2^32, so we can just display */
					/* the low halves of the 64-bit counters */
					Log_FormattedMessage
					    ("DA_MACSEC: Ingress SecY(%d) Statistics:\n"
					     "\tTransform E r r o r Packets Counter:    %u\n"
					     "\tIngress Controlled Packets Counter:     %u\n"
					     "\tIngress Untagged Packets Counter:       %u\n"
					     "\tIngress No Tag Packets Counter:         %u\n"
					     "\tIngress Bad Tag Packets Counter:        %u\n"
					     "\tIngress No SCI Packets Counter:         %u\n"
					     "\tIngress Unknown SCI Packets Counter:    %u\n"
					     "\tIngress Tagged Control Packets Counter: %u\n",
					     vPort,
					     SecYStats.InPktsTransformError.Lo,
					     SecYStats.InPktsControl.Lo,
					     SecYStats.InPktsUntagged.Lo,
					     SecYStats.InPktsNoTag.Lo,
					     SecYStats.InPktsBadTag.Lo,
					     SecYStats.InPktsNoSCI.Lo,
					     SecYStats.InPktsUnknownSCI.Lo,
					     SecYStats.InPktsTaggedCtrl.Lo);

				stats->dev_stats.InPktsUntagged +=
				    STATS_2x32_TO_64
				    (SecYStats.InPktsUntagged.Lo,
				     SecYStats.InPktsUntagged.Lo);
				stats->dev_stats.InPktsNoTag +=
				    STATS_2x32_TO_64
				    (SecYStats.InPktsNoTag.Lo,
				     SecYStats.InPktsNoTag.Hi);
				stats->dev_stats.InPktsBadTag +=
				    STATS_2x32_TO_64
				    (SecYStats.InPktsBadTag.Lo,
				     SecYStats.InPktsBadTag.Hi);
				stats->dev_stats.InPktsUnknownSCI +=
				    STATS_2x32_TO_64
				    (SecYStats.InPktsUnknownSCI.Lo,
				     SecYStats.InPktsUnknownSCI.Hi);
				stats->dev_stats.InPktsNoSCI +=
				    STATS_2x32_TO_64
				    (SecYStats.InPktsNoSCI.Lo,
				     SecYStats.InPktsNoSCI.Hi);
				stats->dev_stats.InPktsOverrun +=
				    STATS_2x32_TO_64
				    (SecYStats.InPktsTransformError.Lo,
				     SecYStats.InPktsTransformError.Hi);
			}
		}
		++i;
	} while (i < MACSEC_MAX_SA);

	return 0;

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

	LOG_INFO("%s: Link %d Device %d Channel %d \n", __func__, link_index,
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

	LOG_INFO("%s: Link %d Device %d Channel %d \n", __func__, link_index,
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

	LOG_INFO("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		 port_id, channel_id);

	if (eip_macsec_add_secy(false, true, ingress_device, channel_id, ctx) <0) {
		LOG_CRIT("%s: Ingress mode Device_ID %d Channel %d FAILED\n",
			 __func__, ingress_device, channel_id);
		return -EINVAL;

	}

	if (eip_macsec_add_secy(false, false, egress_device, channel_id, ctx) <0) {
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

	if (ctx->prepare) {
		return 0;
	}
	dump_secy(ctx);

	/* Configure  Ingress and Egress device Initalizations and set them in bypass mode */

	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);

	get_device_params_from_link_id(link_index, &port_id, &ingress_device,
				       &egress_device, &channel_id);

	LOG_INFO("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		 port_id, channel_id);

	/* TODO : Need to figure out how to configure the change in update secy to 163/164 */
	return 0;
	//return -ENOTSUPP;
}

static int eip_mdo_del_secy(struct macsec_context *ctx)
{

	unsigned int port_id, ingress_device, egress_device, channel_id;
	uint32_t link_index;
	u32 index;

	if (ctx->prepare) {
		return 0;
	}
	dump_secy(ctx);

	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);

	get_device_params_from_link_id(link_index, &port_id, &ingress_device,
				       &egress_device, &channel_id);

	LOG_INFO("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		 port_id, channel_id);

	for (index = 0; index < MACSEC_MAX_SA; ++index) {
		if (eip_macsec_channel_stop
		    (false, true, ingress_device, index) <0) {
			LOG_CRIT("%s: Ingress device %d channel %d failed",
				 __func__, ingress_device, channel_id);
			return -EINVAL;
		}

		if (eip_macsec_channel_stop(false, true, egress_device, index) <0) {
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

	if (ctx->prepare) {
		return 0;
	}
	dump_rxsc(ctx);

	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);
	get_ingress_params_from_link_id(link_index, &port_id, &ingress_device,
					&channel_id);

	LOG_INFO("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		 port_id, channel_id);

	/*  Configure Ingress Device and Channels */
	if (eip_macsec_config_sc(false, true, ingress_device, channel_id, ctx) <0) {
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
	LOG_INFO("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		 port_id, channel_id);

	if (eip_macsec_config_sc(false, true, ingress_device, channel_id, ctx) <0) {
		LOG_CRIT("%s: Ingress config for rxsc failed", __func__);
		return -EINVAL;

	}

	return 0;
}

static int eip_mdo_del_rxsc(struct macsec_context *ctx)
{

	if (ctx->prepare) {
		return 0;
	}

	LOG_INFO("%s: called \n", __func__);

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
	LOG_INFO("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		 port_id, channel_id);

	if (eip_macsec_config_sa(false, true, ingress_device, channel_id, ctx) <0) {
		LOG_CRIT("%s: Ingress mode Device_ID %d Channel %d FAILED\n",
			 __func__, ingress_device, channel_id);
		return -EINVAL;
	}
	if (eip_macsec_add_sa(false, true, ingress_device, channel_id, ctx) <0) {
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

	if (ctx->prepare) {
		return 0;
	}
	/* TBD: To support the advanced use case early return for now */
	LOG_CRIT("%s: Not supported, early return", __func__);
	return 0;
	//return -ENOTSUPP;

	dump_rxsa(ctx);

	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);
	get_ingress_params_from_link_id(link_index, &port_id, &ingress_device,
					&channel_id);

	LOG_INFO("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		 port_id, channel_id);

	if (eip_macsec_config_sa(false, true, ingress_device, channel_id, ctx) <0) {
		LOG_CRIT("%s: Ingress mode Device_ID %d Channel %d FAILED\n",
			 __func__, ingress_device, channel_id);
		return -EINVAL;
	}
	if (eip_macsec_add_sa(false, true, ingress_device, channel_id, ctx) <0) {
		LOG_CRIT("%s: Egress mode Device_ID %d Channel %d FAILED\n",
			 __func__, ingress_device, channel_id);
		return -EINVAL;
	}

	return 0;
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

	LOG_INFO("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		 port_id, channel_id);

	if (eip_macsec_delete_sa(false, true, ingress_device, channel_id, ctx) <0) {
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

	LOG_INFO("%s: called \n", __func__);
	dump_txsa(ctx);

	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);
	/* Configure Egress device and Channels */
	get_egress_params_from_link_id(link_index, &port_id, &egress_device,
				       &channel_id);

	LOG_INFO("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		 port_id, channel_id);

	if (eip_macsec_config_sa(false, false, egress_device, channel_id, ctx)< 0) {
		LOG_CRIT("%s: Ingress mode Device_ID %d Channel %d FAILED\n",
			 __func__, egress_device, channel_id);
		return -EINVAL;
	}
	if (eip_macsec_add_sa(false, false, egress_device, channel_id, ctx) <0) {
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

	if (ctx->prepare) {
		return 0;
	}
	/* TBD: To support the advanced use case early return for now */
	LOG_CRIT("%s: Not supported, early return", __func__);
	return 0;
	//return -ENOTSUPP;

	LOG_INFO("%s: called \n", __func__);

	dump_txsa(ctx);

	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);
	get_egress_params_from_link_id(link_index, &port_id, &egress_device,
				       &channel_id);

	LOG_INFO("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		 port_id, channel_id);

	if (eip_macsec_config_sa(false, false, egress_device, channel_id, ctx) <0) {
		LOG_CRIT("%s: Ingress mode Device_ID %d Channel %d FAILED\n",
			 __func__, egress_device, channel_id);
		return -EINVAL;
	}
	if (eip_macsec_add_sa(false, false, egress_device, channel_id, ctx)<0) {
		LOG_CRIT("%s: Egress mode Device_ID %d Channel %d FAILED\n",
			 __func__, egress_device, channel_id);
		return -EINVAL;
	}

	return 0;
}

static int eip_mdo_del_txsa(struct macsec_context *ctx)
{

	unsigned int egress_device, port_id, channel_id;
	uint32_t link_index;

	if (ctx->prepare) {
		return 0;
	}
	dump_txsa(ctx);

	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);
	get_egress_params_from_link_id(link_index, &port_id, &egress_device,
				       &channel_id);

	LOG_INFO("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		 port_id, channel_id);

	if (eip_macsec_delete_sa(false, false, egress_device, channel_id, ctx) <0) {
		LOG_INFO("%s: Egress mode Device_ID %d Channel %d FAILED\n",
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

	if (ctx->prepare) {
		return 0;
	}

	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);
	memset((void *)&ingress_stats, 0, sizeof(ingress_stats));
	memset((void *)&egress_stats, 0, sizeof(egress_stats));

	get_device_params_from_link_id(link_index, &port_id, &ingress_device,
				       &egress_device, &channel_id);

	LOG_INFO("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		 port_id, channel_id);

	eip_macsec_ingress_stats(false, port_id, channel_id,
				 &ingress_stats, MACSEC_STATS_DEV);

	ctx->stats.dev_stats->OutPktsUntagged +=
	    ingress_stats.dev_stats.OutPktsUntagged;
	ctx->stats.dev_stats->InPktsUntagged +=
	    ingress_stats.dev_stats.InPktsUntagged;
	ctx->stats.dev_stats->OutPktsTooLong +=
	    ingress_stats.dev_stats.OutPktsTooLong;
	ctx->stats.dev_stats->InPktsNoTag += ingress_stats.dev_stats.InPktsNoTag;
	ctx->stats.dev_stats->InPktsBadTag +=
	    ingress_stats.dev_stats.InPktsBadTag;
	ctx->stats.dev_stats->InPktsUnknownSCI +=
	    ingress_stats.dev_stats.InPktsUnknownSCI;
	ctx->stats.dev_stats->InPktsNoSCI += ingress_stats.dev_stats.InPktsNoSCI;
	ctx->stats.dev_stats->InPktsOverrun +=
	    ingress_stats.dev_stats.InPktsOverrun;

	eip_macsec_egress_stats(false, port_id, channel_id,
				&egress_stats, MACSEC_STATS_DEV);

	ctx->stats.dev_stats->OutPktsUntagged +=
	    egress_stats.dev_stats.OutPktsUntagged;
	ctx->stats.dev_stats->InPktsUntagged +=
	    egress_stats.dev_stats.InPktsUntagged;
	ctx->stats.dev_stats->OutPktsTooLong +=
	    egress_stats.dev_stats.OutPktsTooLong;
	ctx->stats.dev_stats->InPktsNoTag += egress_stats.dev_stats.InPktsNoTag;
	ctx->stats.dev_stats->InPktsBadTag +=
	    egress_stats.dev_stats.InPktsBadTag;
	ctx->stats.dev_stats->InPktsUnknownSCI +=
	    egress_stats.dev_stats.InPktsUnknownSCI;
	ctx->stats.dev_stats->InPktsNoSCI += egress_stats.dev_stats.InPktsNoSCI;
	ctx->stats.dev_stats->InPktsOverrun +=
	    egress_stats.dev_stats.InPktsOverrun;

	return 0;
}

static int eip_mdo_get_tx_sc_stats(struct macsec_context *ctx)
{

	unsigned int egress_device, port_id, channel_id;
	uint32_t link_index;
	struct eip_macsec_stats egress_stats;

	if (ctx->prepare) {
		return 0;
	}
	memset((void *)&egress_stats, 0, sizeof(egress_stats));
	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);
	get_egress_params_from_link_id(link_index, &port_id, &egress_device,
				       &channel_id);

	LOG_INFO("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		 port_id, channel_id);

	eip_macsec_egress_stats(false, port_id, channel_id,
				&egress_stats, MACSEC_STATS_TXSC);

	ctx->stats.tx_sc_stats->OutPktsProtected +=
	    egress_stats.tx_sc_stats.OutPktsProtected;
	ctx->stats.tx_sc_stats->OutPktsEncrypted +=
	    egress_stats.tx_sc_stats.OutPktsEncrypted;
	ctx->stats.tx_sc_stats->OutOctetsProtected +=
	    egress_stats.tx_sc_stats.OutOctetsProtected;
	ctx->stats.tx_sc_stats->OutOctetsEncrypted +=
	    egress_stats.tx_sc_stats.OutOctetsEncrypted;

	return 0;
}

static int eip_mdo_get_tx_sa_stats(struct macsec_context *ctx)
{

	unsigned int egress_device, port_id, channel_id;
	uint32_t link_index;
	struct eip_macsec_stats egress_stats;

	if (ctx->prepare) {
		return 0;
	}
	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);
	memset((void *)&egress_stats, 0, sizeof(egress_stats));
	get_egress_params_from_link_id(link_index, &port_id,
				       &egress_device, &channel_id);

	LOG_INFO("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		 port_id, channel_id);

	eip_macsec_egress_stats(false, port_id, channel_id,
				&egress_stats, MACSEC_STATS_TXSA);

	ctx->stats.tx_sa_stats->OutPktsProtected +=
	    egress_stats.tx_sa_stats.OutPktsProtected;
	ctx->stats.tx_sa_stats->OutPktsEncrypted +=
	    egress_stats.tx_sa_stats.OutPktsEncrypted;

	return 0;
}

static int eip_mdo_get_rx_sc_stats(struct macsec_context *ctx)
{

	unsigned int ingress_device, port_id, channel_id;
	uint32_t link_index;
	struct eip_macsec_stats ingress_stats;

	if (ctx->prepare) {
		return 0;
	}
	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);

	memset((void *)&ingress_stats, 0, sizeof(ingress_stats));
	get_ingress_params_from_link_id(link_index, &port_id, &ingress_device,
					&channel_id);

	LOG_INFO("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		 port_id, channel_id);

	eip_macsec_ingress_stats(false, port_id, channel_id,
				 &ingress_stats, MACSEC_STATS_RXSC);

	ctx->stats.rx_sc_stats->InOctetsValidated +=
	    ingress_stats.rx_sc_stats.InOctetsValidated;
	ctx->stats.rx_sc_stats->InOctetsDecrypted +=
	    ingress_stats.rx_sc_stats.InOctetsDecrypted;
	ctx->stats.rx_sc_stats->InPktsUnchecked +=
	    ingress_stats.rx_sc_stats.InPktsUnchecked;
	ctx->stats.rx_sc_stats->InPktsDelayed +=
	    ingress_stats.rx_sc_stats.InPktsDelayed;
	ctx->stats.rx_sc_stats->InPktsOK += ingress_stats.rx_sc_stats.InPktsOK;
	ctx->stats.rx_sc_stats->InPktsInvalid +=
	    ingress_stats.rx_sc_stats.InPktsInvalid;
	ctx->stats.rx_sc_stats->InPktsLate +=
	    ingress_stats.rx_sc_stats.InPktsLate;
	ctx->stats.rx_sc_stats->InPktsNotValid +=
	    ingress_stats.rx_sc_stats.InPktsNotValid;
	ctx->stats.rx_sc_stats->InPktsNotUsingSA +=
	    ingress_stats.rx_sc_stats.InPktsNotUsingSA;
	ctx->stats.rx_sc_stats->InPktsUnusedSA +=
	    ingress_stats.rx_sc_stats.InPktsUnusedSA;

	return 0;
}

static int eip_mdo_get_rx_sa_stats(struct macsec_context *ctx)
{

	unsigned int ingress_device, port_id, channel_id;
	uint32_t link_index;
	struct eip_macsec_stats ingress_stats;

	if (ctx->prepare) {
		return 0;
	}
	macsec_eth_lookup_eth_link_by_netdev(ctx->netdev, &link_index);

	memset((void *)&ingress_stats, 0, sizeof(ingress_stats));
	get_ingress_params_from_link_id(link_index, &port_id, &ingress_device,
					&channel_id);

	LOG_INFO("%s: Link %d Device %d Channel %d \n", __func__, link_index,
		 port_id, channel_id);

	eip_macsec_ingress_stats(false, port_id, channel_id,
				 &ingress_stats, MACSEC_STATS_RXSA);

	ctx->stats.rx_sa_stats->InPktsOK += ingress_stats.rx_sa_stats.InPktsOK;
	ctx->stats.rx_sa_stats->InPktsInvalid +=
	    ingress_stats.rx_sa_stats.InPktsInvalid;
	ctx->stats.rx_sa_stats->InPktsNotValid +=
	    ingress_stats.rx_sa_stats.InPktsNotValid;
	ctx->stats.rx_sa_stats->InPktsNotUsingSA +=
	    ingress_stats.rx_sa_stats.InPktsNotUsingSA;
	ctx->stats.rx_sa_stats->InPktsUnusedSA +=
	    ingress_stats.rx_sa_stats.InPktsUnusedSA;

	return 0;
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
