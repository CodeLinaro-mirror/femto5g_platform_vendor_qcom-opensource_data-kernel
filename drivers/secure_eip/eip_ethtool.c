// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */
#include <linux/module.h>

#include <net/xfrm.h>
#include <linux/ethtool.h>
#include <linux/errno.h>

#include "aes.h"
#include "clib.h"
#include "sa_builder_macsec.h"

#include "eip_ipsec.h"
#include "eip_macsec.h"
#include "eip_log.h"
#include "eip_ethtool.h"

#include "api_cfye.h"
#include "api_secy.h"

#define READ_STATS_2x32_TO_64(param) (((u64)param.Hi << 32) | param.Lo)

static const char *const eip_ethtool_tx_sa_strings[] = {
	"EIP Tx# ",
	/*Tx SA*/
	"OutOctetsEncryptedProtected[%d]",
	"OutPktsEncryptedProtected[%d]",
	"OutPktsTooLong[%d]",
	"OutPktSANotInUse[%d]",
	/*Tx vPort*/
	"OutTransformErrPkts[%d]",
	"OutPktsCtrl[%d]",
	"OutPktsUntagged[%d]",
	"OutPktsSANotInUse[%d]",
	/*Tx vPort ifc0*/
	"ifOutOctetsUncontrolled[%d]",
	"ifOutOctetsControlled[%d]",
	"ifOutUcastPktsUncontrolled[%d]",
	"ifOutMcastPktsUncontrolled[%d]",
	"ifOutBcastPktsUncontrolled[%d]",
	/*Tx vPort ifc1*/
	"ifOutOctetsCommon[%d]",
	"ifOutUcastPktsControlled[%d]",
	"ifOutMCastPktsControlled[%d]",
	"ifOutBCastPktsControlled[%d]",
};

static const char *const eip_ethtool_rx_sa_strings[] = {
	"EIP Rx# ",
	/*Rx SA*/
	"InOctetsDecrypted[%d]",
	"InOctetsValidated[%d]",
	"InPktsPadNotValid[%d]",
	"InPktsReplayed[%d]",
	"InPktsLate[%d]",
	"InPktsOk[%d]",
	"InPktsPadLenFail[%d]",
	"InPktsNotValid[%d]",
	"InPktsNotUsingSA[%d]",
	"InPktsPadDummy[%d]",
	/*Rx vPort*/
	"InTransformErrPkts[%d]",
	"InPktsLateHdr[%d]",
	"InPktsIPMismatch[%d]",
	"InPktsNoTag[%d]",
	"InPktsBadTag[%d]",
	"InPktsNoSCl[%d]",
	"InPktsUnknownSCl[%d]",
	"InPktsTaggedCtrl[%d]",
	"InPktsSANotInUse[%d]",
	/*Rx vPort ifc0*/
	"ifInOctetsUncontrolled[%d]",
	"ifInUcastPktsUncontrolled[%d]",
	"ifInMCastPktsUncontrolled[%d]",
	"ifInBCastPktsUncontrolled[%d]",
	/*Rx vPort ifc1*/
	"ifInOctetsControlled[%d]",
	"ifInUcastPktsControlled[%d]",
	"ifInMCastPktsControlled[%d]",
	"ifInBCastPktsControlled[%d]",
};

static const char *const eip_ethtool_tx_ch_strings[] = {
	/*Tx Cfye Stats*/
	"Tx_TCAMHitMultiple", "Tx_HeaderParserDroppedPkts",
	"Tx_TCAMMiss",	      "Tx_PktsCtrl",
	"Tx_PktsData",	      "Tx_PktsDropped",
	"Tx_PktsErrln",	      "Tx_MTTMiss",
	"Tx_SPI Hit",	      "Tx_MTTHit",
};

static const char *const eip_ethtool_rx_ch_strings[] = {
	/*Rx Cfye Stats*/
	"Rx_TCAMHitMultiple", "Rx_HeaderParserDroppedPkts",
	"Rx_TCAMMiss",	      "Rx_PktsCtrl",
	"Rx_PktsData",	      "Rx_PktsDropped",
	"Rx_PktsErrln",	      "Rx_MTTMiss",
	"Rx_SPI Hit",	      "Rx_MTTHit",
};

#define EIP_ETHTOOL_TX_SAS_STATS_LEN ARRAY_SIZE(eip_ethtool_tx_sa_strings)
#define EIP_ETHTOOL_RX_SAS_STATS_LEN ARRAY_SIZE(eip_ethtool_rx_sa_strings)
#define EIP_ETHTOOL_TX_CHNL_STATS_LEN ARRAY_SIZE(eip_ethtool_tx_ch_strings)
#define EIP_ETHTOOL_RX_CHNL_STATS_LEN ARRAY_SIZE(eip_ethtool_rx_ch_strings)

#define __wr_sset_strings(start, end, strings, buff, sa)                       \
	for ((start) = 0; (start) < (end); (start)++) {                        \
		snprintf((buff), ETH_GSTRING_LEN, strings[(start)], (sa));     \
		(buff) += ETH_GSTRING_LEN;                                     \
	}

static bool __get_device_role(unsigned int devid, unsigned int chid)
{
	SecY_Channel_t ChannelParams;
	SecY_Status_t SecY_Rc;

	SecY_Rc = SecY_Channel_Config_Get(devid, chid, &ChannelParams);
	if (SecY_Rc != SECY_STATUS_OK) {
		eip_logerr("IPSEC:SecY_Channel_Config_Get, error=%d", SecY_Rc);
	}
	return ChannelParams.fIPsec;
}

static u32 __count_ipsec_sa_per_link(struct eip_ipsec_link *ilink, bool inbound)
{
	struct eip_xfrm_state *eip_xs;
	u32 cnt = 0;

	read_lock(&ilink->lock);
	list_for_each_entry (eip_xs, &ilink->eip_xs_l, eip_xs_l) {
		if (eip_xs->inbound == inbound)
			cnt++;
	}
	read_unlock(&ilink->lock);

	return cnt;
}

int eip_ethtool_get_sset_count(struct net_device *netdev)
{
	struct eip_ipsec_link *ilink = ndev_to_ipsec(netdev);
	struct eip_link *link =
		(struct eip_link *)mtip_security_get_priv(netdev);
	unsigned int devid, chid;
	unsigned int e_sa_cnt, in_sa_cnt;
	bool is_ipsec;

	//Get device role for ingress device
	devid = eip_devid(&link->rx);
	chid = eip_chid(&link->rx);
	is_ipsec = __get_device_role(devid, chid);
	if (is_ipsec) { //IPSEC
		in_sa_cnt = __count_ipsec_sa_per_link(ilink, true);
	} else {
		//MACSec: Multiple SA is not possible at a given time
		in_sa_cnt = 1;
	}

	//Get device role for egress device
	devid = eip_devid(&link->tx);
	chid = eip_chid(&link->tx);
	is_ipsec = __get_device_role(devid, chid);
	if (is_ipsec) { //IPSEC
		e_sa_cnt = __count_ipsec_sa_per_link(ilink, false);
	} else {
		//MACSec: Multiple SA is not possible at a given time
		e_sa_cnt = 1;
	}

	return ((in_sa_cnt * EIP_ETHTOOL_RX_SAS_STATS_LEN) +
		(e_sa_cnt * EIP_ETHTOOL_TX_SAS_STATS_LEN) +
		EIP_ETHTOOL_RX_CHNL_STATS_LEN + EIP_ETHTOOL_TX_CHNL_STATS_LEN);
}

int eip_ethtool_get_sset_strings(struct net_device *netdev, u8 *stats_strings)
{
	int i;
	struct eip_ipsec_link *ilink = ndev_to_ipsec(netdev);
	struct eip_link *link =
		(struct eip_link *)mtip_security_get_priv(netdev);
	struct eip_xfrm_state *eip_xs;
	unsigned int devid, chid;
	bool is_ipsec;
	SecY_Status_t SecY_Rc;
	SecY_SAHandle_t sa_handle;
	unsigned int sa_index = 0;

	for (i = 0; i < EIP_ETHTOOL_RX_CHNL_STATS_LEN; i++) {
		strlcpy(stats_strings, eip_ethtool_rx_ch_strings[i],
			ETH_GSTRING_LEN);
		stats_strings += ETH_GSTRING_LEN;
	}

	for (i = 0; i < EIP_ETHTOOL_TX_CHNL_STATS_LEN; i++) {
		strlcpy(stats_strings, eip_ethtool_tx_ch_strings[i],
			ETH_GSTRING_LEN);
		stats_strings += ETH_GSTRING_LEN;
	}

	//Get device role for ingress device
	devid = eip_devid(&link->rx);
	chid = eip_chid(&link->rx);
	is_ipsec = __get_device_role(devid, chid);
	if (is_ipsec) { //IPSEC
		read_lock(&ilink->lock);
		list_for_each_entry (eip_xs, &ilink->eip_xs_l, eip_xs_l) {
			if (eip_xs->inbound) {
				__wr_sset_strings(i,
						  EIP_ETHTOOL_RX_SAS_STATS_LEN,
						  eip_ethtool_rx_sa_strings,
						  stats_strings,
						  eip_xs->sa_index);
			}
		}
		read_unlock(&ilink->lock);
	} else {
		SecY_Rc = eip_macsec_get_sa_handle(netdev, &sa_handle, true);
		if (SecY_Rc) {
			eip_logerr("MACSEC: eip_macsec_get_sa_handle()=%d",
				   SecY_Rc);
			return -EINVAL;
		}
		SecY_SAIndex_Get(sa_handle, &sa_index, NULL);
		__wr_sset_strings(i, EIP_ETHTOOL_RX_SAS_STATS_LEN,
				  eip_ethtool_rx_sa_strings, stats_strings,
				  sa_index);
	}

	//Get device role for egress device
	devid = eip_devid(&link->tx);
	chid = eip_chid(&link->tx);
	is_ipsec = __get_device_role(devid, chid);
	if (is_ipsec) { //IPSEC
		for (i = 0; i < EIP_ETHTOOL_TX_SAS_STATS_LEN; i++) {
			read_lock(&ilink->lock);
			list_for_each_entry (eip_xs, &ilink->eip_xs_l,
					     eip_xs_l) {
				if (!eip_xs->inbound) {
					__wr_sset_strings(
						i, EIP_ETHTOOL_TX_SAS_STATS_LEN,
						eip_ethtool_tx_sa_strings,
						stats_strings,
						eip_xs->sa_index);
				}
			}
			read_unlock(&ilink->lock);
		}
	} else {
		SecY_Rc = eip_macsec_get_sa_handle(netdev, &sa_handle, false);
		if (SecY_Rc) {
			eip_logerr("MACSEC: eip_macsec_get_sa_handle()=%d",
				   SecY_Rc);
			return -EINVAL;
		}
		SecY_SAIndex_Get(sa_handle, &sa_index, NULL);
		__wr_sset_strings(i, EIP_ETHTOOL_TX_SAS_STATS_LEN,
				  eip_ethtool_tx_sa_strings, stats_strings,
				  sa_index);
	}

	return 0;
}

static int eip_ethtool_wr_ipsec_ingress_stats(unsigned int devid,
					      struct eip_xfrm_state *eip_xs,
					      u64 *data)
{
	SecY_SA_Stat_IPsec_I_t sa;
	SecY_SecY_Stat_IPsec_I_t vport_secy;
	SecY_Ifc_Stat_I_t ifc;
	SecY_Status_t SecY_Rc;
	int i = 0;

	SecY_Rc =
		SecY_SA_Statistics_IPsec_I_Get(devid, eip_xs->sa_h, &sa, true);
	if (SecY_Rc != SECY_STATUS_OK) {
		eip_logerr(
			"IPSEC: SecY_SA_Statistics_IPsec_I_Get()=%d dev_id=%d",
			SecY_Rc, devid);
		return SecY_Rc;
	}
	data[i] = eip_xs->sa_index;
	data[++i] = READ_STATS_2x32_TO_64(sa.InOctetsDecrypted);
	data[++i] = READ_STATS_2x32_TO_64(sa.InOctetsValidated);
	data[++i] = READ_STATS_2x32_TO_64(sa.InPktsPadNotValid);
	data[++i] = READ_STATS_2x32_TO_64(sa.InPktsReplayed);
	data[++i] = READ_STATS_2x32_TO_64(sa.InPktsLate);
	data[++i] = READ_STATS_2x32_TO_64(sa.InPktsOK);
	data[++i] = READ_STATS_2x32_TO_64(sa.InPktsPadLenFail);
	data[++i] = READ_STATS_2x32_TO_64(sa.InPktsNotValid);
	data[++i] = READ_STATS_2x32_TO_64(sa.InPktsNotUsingSA);
	data[++i] = READ_STATS_2x32_TO_64(sa.InPktsPadDummy);

	SecY_Rc = SecY_SecY_Statistics_IPsec_I_Get(devid, eip_xs->vport,
						   &vport_secy, true);
	if (SecY_Rc != SECY_STATUS_OK) {
		eip_logerr(
			"IPSEC: SecY_SecY_Statistics_IPsec_I_Get()=%d dev_id=%d",
			SecY_Rc, devid);
		return SecY_Rc;
	}
	data[++i] = READ_STATS_2x32_TO_64(vport_secy.InPktsTransformError);
	data[++i] = READ_STATS_2x32_TO_64(vport_secy.InPktsLateHdr);
	data[++i] = READ_STATS_2x32_TO_64(vport_secy.InPktsIPMismatch);
	data[++i] = 0; //"InPktsNoTag" Not counted in IPSec mode
	data[++i] = 0; //"InPktsBadTag" Not counted in IPSec mode
	data[++i] = 0; //"InPktsNoSCl" Not counted in IPSec mode
	data[++i] = 0; //"InPktsUnknownSCl" Not counted in IPSec mode
	data[++i] = 0; //"InPktsTaggedCtrl" Not counted in IPSec mode
	data[++i] = READ_STATS_2x32_TO_64(vport_secy.InPktsSANotInUse);

	SecY_Rc = SecY_Ifc_Statistics_I_Get(devid, eip_xs->vport, &ifc, true);
	if (SecY_Rc != SECY_STATUS_OK) {
		eip_logerr("IPSEC: SecY_Ifc_Statistics_I_Get()=%d dev_id=%d",
			   SecY_Rc, devid);
		return SecY_Rc;
	}
	data[++i] = READ_STATS_2x32_TO_64(ifc.InOctetsUncontrolled);
	data[++i] = READ_STATS_2x32_TO_64(ifc.InPktsUnicastUncontrolled);
	data[++i] = READ_STATS_2x32_TO_64(ifc.InPktsMulticastUncontrolled);
	data[++i] = READ_STATS_2x32_TO_64(ifc.InPktsBroadcastUncontrolled);
	data[++i] = READ_STATS_2x32_TO_64(ifc.InOctetsControlled);
	data[++i] = READ_STATS_2x32_TO_64(ifc.InPktsUnicastControlled);
	data[++i] = READ_STATS_2x32_TO_64(ifc.InPktsMulticastControlled);
	data[++i] = READ_STATS_2x32_TO_64(ifc.InPktsBroadcastControlled);

	return SECY_STATUS_OK;
}

static int eip_ethtool_wr_macsec_ingress_stats(struct net_device *netdev,
					       unsigned int devid, u64 *data)
{
	SecY_SAHandle_t sa_handle;
	unsigned int vport_idx;
	SecY_SA_Stat_I_t sa;
	SecY_SecY_Stat_I_t vport_secy;
	SecY_Ifc_Stat_I_t ifc;
	SecY_Status_t SecY_Rc;
	int i = 0;
	unsigned int sa_index;

	SecY_Rc = eip_macsec_get_sa_handle(netdev, &sa_handle, true);
	if (SecY_Rc) {
		eip_logerr("MACSEC: eip_macsec_get_sa_handle()=%d", SecY_Rc);
		return SecY_Rc;
	}
	SecY_SAIndex_Get(sa_handle, &sa_index, NULL);

	SecY_Rc = eip_macsec_get_vport_index(netdev, &vport_idx, true);
	if (SecY_Rc) {
		eip_logerr("MACSEC: eip_macsec_get_vport_index()=%d", SecY_Rc);
		return SecY_Rc;
	}
	SecY_Rc = SecY_SA_Statistics_I_Get(devid, sa_handle, &sa, true);
	if (SecY_Rc != SECY_STATUS_OK) {
		eip_logerr(
			"IPSEC: SecY_SA_Statistics_IPsec_I_Get()=%d dev_id=%d",
			SecY_Rc, devid);
		return SecY_Rc;
	}
	data[i] = sa_index;
	data[++i] = READ_STATS_2x32_TO_64(sa.InOctetsDecrypted);
	data[++i] = READ_STATS_2x32_TO_64(sa.InOctetsValidated);
	data[++i] = READ_STATS_2x32_TO_64(sa.InPktsNotValid);
	data[++i] = 0; //"InPktsReplayed" Not counted in MACSec mode
	data[++i] = READ_STATS_2x32_TO_64(sa.InPktsLate);
	data[++i] = READ_STATS_2x32_TO_64(sa.InPktsOK);
	data[++i] = 0; //"InPktsPadLenFail" Not counted in MACSec mode
	data[++i] = READ_STATS_2x32_TO_64(sa.InPktsNotValid);
	data[++i] = READ_STATS_2x32_TO_64(sa.InPktsNotUsingSA);
	data[++i] = 0; //"InPktsPadDummy" Not counted in MACSec mode

	SecY_Rc =
		SecY_SecY_Statistics_I_Get(devid, vport_idx, &vport_secy, true);
	if (SecY_Rc != SECY_STATUS_OK) {
		eip_logerr("MACSEC, SecY_SecY_Statistics_I_Get()=%d\n",
			   SecY_Rc);
		return SecY_Rc;
	}
	data[++i] = READ_STATS_2x32_TO_64(vport_secy.InPktsTransformError);
	data[++i] = 0; //"InPktsLateHdr" Not counted in MACSec mode
	data[++i] = 0; //"InPktsIPMismatch"Not counted in MACSec mode
	data[++i] = READ_STATS_2x32_TO_64(vport_secy.InPktsNoTag);
	data[++i] = READ_STATS_2x32_TO_64(vport_secy.InPktsBadTag);
	data[++i] = READ_STATS_2x32_TO_64(vport_secy.InPktsNoSCI);
	data[++i] = READ_STATS_2x32_TO_64(vport_secy.InPktsUnknownSCI);
	data[++i] = READ_STATS_2x32_TO_64(vport_secy.InPktsTaggedCtrl);
	data[++i] = READ_STATS_2x32_TO_64(vport_secy.InPktsSANotInUse);

	SecY_Rc = SecY_Ifc_Statistics_I_Get(devid, vport_idx, &ifc, true);
	if (SecY_Rc != SECY_STATUS_OK) {
		eip_logerr("MACSEC: SecY_Ifc_Statistics_I_Get()=%d dev_id=%d",
			   SecY_Rc, devid);
		return SecY_Rc;
	}
	data[++i] = READ_STATS_2x32_TO_64(ifc.InOctetsUncontrolled);
	data[++i] = READ_STATS_2x32_TO_64(ifc.InPktsUnicastUncontrolled);
	data[++i] = READ_STATS_2x32_TO_64(ifc.InPktsMulticastUncontrolled);
	data[++i] = READ_STATS_2x32_TO_64(ifc.InPktsBroadcastUncontrolled);
	data[++i] = READ_STATS_2x32_TO_64(ifc.InOctetsControlled);
	data[++i] = READ_STATS_2x32_TO_64(ifc.InPktsUnicastControlled);
	data[++i] = READ_STATS_2x32_TO_64(ifc.InPktsMulticastControlled);
	data[++i] = READ_STATS_2x32_TO_64(ifc.InPktsBroadcastControlled);

	return SECY_STATUS_OK;
}

static int eip_ethtool_wr_ipsec_egress_stats(unsigned int devid,
					     struct eip_xfrm_state *eip_xs,
					     u64 *data)
{
	SecY_SA_Stat_E_t sa;
	SecY_SecY_Stat_IPsec_E_t vport_secy;
	SecY_Ifc_Stat_E_t ifc;
	SecY_Status_t SecY_Rc;
	int i = 0;

	SecY_Rc = SecY_SA_Statistics_E_Get(devid, eip_xs->sa_h, &sa, true);
	if (SecY_Rc != SECY_STATUS_OK) {
		eip_logerr("IPSEC: SecY_SA_Statistics_E_Get()=%d dev_id=%d",
			   SecY_Rc, devid);
		return SecY_Rc;
	}
	data[i] = eip_xs->sa_index;
	data[++i] = READ_STATS_2x32_TO_64(sa.OutOctetsEncryptedProtected);
	data[++i] = READ_STATS_2x32_TO_64(sa.OutPktsEncryptedProtected);
	data[++i] = READ_STATS_2x32_TO_64(sa.OutPktsTooLong);
	data[++i] = READ_STATS_2x32_TO_64(sa.OutPktsSANotInUse);

	SecY_Rc = SecY_SecY_Statistics_IPsec_E_Get(devid, eip_xs->vport,
						   &vport_secy, true);
	if (SecY_Rc != SECY_STATUS_OK) {
		eip_logerr(
			"IPSEC: SecY_SecY_Statistics_IPsec_E_Get()=%d dev_id=%d",
			SecY_Rc, devid);
		return SecY_Rc;
	}
	data[++i] = READ_STATS_2x32_TO_64(vport_secy.OutPktsTransformError);
	data[++i] = 0; //"OutPktsCtrl" Not counted in IPSec mode
	data[++i] = READ_STATS_2x32_TO_64(vport_secy.OutPktsUntagged);
	data[++i] = READ_STATS_2x32_TO_64(vport_secy.OutPktsSANotInUse);

	SecY_Rc = SecY_Ifc_Statistics_E_Get(devid, eip_xs->vport, &ifc, true);
	if (SecY_Rc != SECY_STATUS_OK) {
		eip_logerr("IPSEC: SecY_Ifc_Statistics_I_Get()=%d dev_id=%d",
			   SecY_Rc, devid);
		return SecY_Rc;
	}
	data[++i] = 0; //"ifOutOctetsUncontrolled" Not counted in IPSec mode
	data[++i] = READ_STATS_2x32_TO_64(ifc.OutOctetsControlled);
	data[++i] = 0; //"ifOutUcastPktsUncontrolled" Not counted in IPSec mode
	data[++i] = 0; //"ifOutMcastPktsUncontrolled" Not counted in IPSec mode
	data[++i] = 0; //"ifOutBcastPktsUncontrolled" Not counted in IPSec mode
	data[++i] = READ_STATS_2x32_TO_64(ifc.OutOctetsCommon);
	data[++i] = READ_STATS_2x32_TO_64(ifc.OutPktsUnicastControlled);
	data[++i] = READ_STATS_2x32_TO_64(ifc.OutPktsMulticastControlled);
	data[++i] = READ_STATS_2x32_TO_64(ifc.OutPktsBroadcastControlled);

	return SECY_STATUS_OK;
}

static int eip_ethtool_wr_macsec_egress_stats(struct net_device *netdev,
					      unsigned int devid, u64 *data)
{
	SecY_SAHandle_t sa_handle;
	unsigned int vport_idx;
	SecY_SA_Stat_E_t sa;
	SecY_SecY_Stat_E_t vport_secy;
	SecY_Ifc_Stat_E_t ifc;
	SecY_Status_t SecY_Rc;
	int i = 0;
	unsigned int sa_index;

	SecY_Rc = eip_macsec_get_sa_handle(netdev, &sa_handle, false);
	if (SecY_Rc) {
		eip_logerr("MACSEC: eip_macsec_get_sa_handle()=%d", SecY_Rc);
		return SecY_Rc;
	}
	SecY_SAIndex_Get(sa_handle, &sa_index, NULL);

	SecY_Rc = eip_macsec_get_vport_index(netdev, &vport_idx, false);
	if (SecY_Rc) {
		eip_logerr("MACSEC: eip_macsec_get_vport_index()=%d", SecY_Rc);
		return SecY_Rc;
	}

	SecY_Rc = SecY_SA_Statistics_E_Get(devid, sa_handle, &sa, true);
	if (SecY_Rc != SECY_STATUS_OK) {
		eip_logerr("MACSEC: SecY_SA_Statistics_E_Get()=%d dev_id=%d",
			   SecY_Rc, devid);
		return SecY_Rc;
	}
	data[i] = sa_index;
	data[++i] = READ_STATS_2x32_TO_64(sa.OutOctetsEncryptedProtected);
	data[++i] = READ_STATS_2x32_TO_64(sa.OutPktsEncryptedProtected);
	data[++i] = READ_STATS_2x32_TO_64(sa.OutPktsTooLong);
	data[++i] = READ_STATS_2x32_TO_64(sa.OutPktsSANotInUse);

	SecY_Rc =
		SecY_SecY_Statistics_E_Get(devid, vport_idx, &vport_secy, true);
	if (SecY_Rc != SECY_STATUS_OK) {
		eip_logerr("MACSEC: SecY_SecY_Statistics_E_Get()=%d dev_id=%d",
			   SecY_Rc, devid);
		return SecY_Rc;
	}
	data[++i] = READ_STATS_2x32_TO_64(vport_secy.OutPktsTransformError);
	data[++i] = READ_STATS_2x32_TO_64(vport_secy.OutPktsControl);
	data[++i] = READ_STATS_2x32_TO_64(vport_secy.OutPktsUntagged);
	data[++i] = READ_STATS_2x32_TO_64(vport_secy.OutPktsSANotInUse);

	SecY_Rc = SecY_Ifc_Statistics_E_Get(devid, vport_idx, &ifc, true);
	if (SecY_Rc != SECY_STATUS_OK) {
		eip_logerr("MACSEC: SecY_Ifc_Statistics_E_Get()=%d dev_id=%d",
			   SecY_Rc, devid);
		return SecY_Rc;
	}
	data[++i] = READ_STATS_2x32_TO_64(ifc.OutOctetsUncontrolled);
	data[++i] = READ_STATS_2x32_TO_64(ifc.OutOctetsControlled);
	data[++i] = READ_STATS_2x32_TO_64(ifc.OutPktsUnicastUncontrolled);
	data[++i] = READ_STATS_2x32_TO_64(ifc.OutPktsMulticastUncontrolled);
	data[++i] = READ_STATS_2x32_TO_64(ifc.OutPktsBroadcastUncontrolled);
	data[++i] = READ_STATS_2x32_TO_64(ifc.OutOctetsCommon);
	data[++i] = READ_STATS_2x32_TO_64(ifc.OutPktsUnicastControlled);
	data[++i] = READ_STATS_2x32_TO_64(ifc.OutPktsMulticastControlled);
	data[++i] = READ_STATS_2x32_TO_64(ifc.OutPktsBroadcastControlled);

	return SECY_STATUS_OK;
}

static int eip_ethtool_wr_ingress_chnl_stats(struct eip_link *link,
					     struct eip_ipsec_link *ilink,
					     u64 *data)
{
	unsigned int devid = eip_devid(&link->rx);
	unsigned int chid = eip_chid(&link->rx);
	CfyE_Statistics_Channel_t ch_stats;
	CfyE_Statistics_MTT_t ch_mtt_stats;
	CfyE_Status_t CfyE_Rc;
	int i = 0;

	CfyE_Rc = CfyE_Statistics_Channel_Get(devid, chid, &ch_stats, false);
	if (CfyE_Rc != CFYE_STATUS_OK) {
		eip_logerr(
			"CfyE_Statistics_Channel_Get()=%d dev_id=%d, ch_id=%d",
			CfyE_Rc, devid, chid);
		return CfyE_Rc;
	}

	CfyE_Rc = CfyE_Statistics_MTT_Get(devid, ilink->mtt_index,
					  &ch_mtt_stats, false);
	if (CfyE_Rc != CFYE_STATUS_OK) {
		eip_logerr(
			"IPSEC: CfyE_Statistics_MTT_Get()=%d dev_id=%d, ch_id=%d",
			CfyE_Rc, devid, chid);
		return CfyE_Rc;
	}

	data[i] = READ_STATS_2x32_TO_64(ch_stats.TCAMHitMultiple);
	data[++i] = READ_STATS_2x32_TO_64(ch_stats.HeaderParserDroppedPkts);
	data[++i] = READ_STATS_2x32_TO_64(ch_stats.TCAMMiss);
	data[++i] = READ_STATS_2x32_TO_64(ch_stats.PktsCtrl);
	data[++i] = READ_STATS_2x32_TO_64(ch_stats.PktsData);
	data[++i] = READ_STATS_2x32_TO_64(ch_stats.PktsDropped);
	data[++i] = READ_STATS_2x32_TO_64(ch_stats.PktsErrIn);
	data[++i] = READ_STATS_2x32_TO_64(ch_stats.MTTMiss);
	data[++i] = READ_STATS_2x32_TO_64(ch_stats.TCAMHitMultiple);
	data[++i] = READ_STATS_2x32_TO_64(ch_mtt_stats.Counter);

	return CFYE_STATUS_OK;
}

static int eip_ethtool_wr_egress_chnl_stats(struct eip_link *link,
					    struct eip_ipsec_link *ilink,
					    u64 *data)
{
	unsigned int devid = eip_devid(&link->tx);
	unsigned int chid = eip_chid(&link->tx);
	CfyE_Statistics_Channel_t ch_stats;
	CfyE_Statistics_MTT_t ch_mtt_stats;
	CfyE_Status_t CfyE_Rc;
	int i = 0;

	CfyE_Rc = CfyE_Statistics_Channel_Get(devid, chid, &ch_stats, false);
	if (CfyE_Rc != CFYE_STATUS_OK) {
		eip_logerr(
			"CfyE_Statistics_Channel_Get()=%d dev_id=%d, ch_id=%d",
			CfyE_Rc, devid, chid);
		return CfyE_Rc;
	}
	CfyE_Rc = CfyE_Statistics_MTT_Get(devid, ilink->mtt_index,
					  &ch_mtt_stats, false);
	if (CfyE_Rc != CFYE_STATUS_OK) {
		eip_logerr(
			"IPSEC: CfyE_Statistics_MTT_Get()=%d dev_id=%d, ch_id=%d",
			CfyE_Rc, devid, chid);
		return CfyE_Rc;
	}

	data[i] = READ_STATS_2x32_TO_64(ch_stats.TCAMHitMultiple);
	data[++i] = READ_STATS_2x32_TO_64(ch_stats.HeaderParserDroppedPkts);
	data[++i] = READ_STATS_2x32_TO_64(ch_stats.TCAMMiss);
	data[++i] = READ_STATS_2x32_TO_64(ch_stats.PktsCtrl);
	data[++i] = READ_STATS_2x32_TO_64(ch_stats.PktsData);
	data[++i] = READ_STATS_2x32_TO_64(ch_stats.PktsDropped);
	data[++i] = READ_STATS_2x32_TO_64(ch_stats.PktsErrIn);
	data[++i] = READ_STATS_2x32_TO_64(ch_stats.MTTMiss);
	data[++i] = READ_STATS_2x32_TO_64(ch_stats.TCAMHitMultiple);
	data[++i] = READ_STATS_2x32_TO_64(ch_mtt_stats.Counter);

	return CFYE_STATUS_OK;
}

int eip_ethtool_get_stats(struct net_device *netdev, u64 *data)
{
	int i = 0;
	struct eip_ipsec_link *ilink = ndev_to_ipsec(netdev);
	struct eip_link *link =
		(struct eip_link *)mtip_security_get_priv(netdev);
	unsigned int devid, chid;
	int ret = 0;

	bool is_ipsec = false;
	struct eip_xfrm_state *eip_xs;

	memset(data, 0, link->sset * sizeof(u64));

	ret = eip_ethtool_wr_ingress_chnl_stats(link, ilink, &data[i]);
	if (ret)
		return -EINVAL;
	i += EIP_ETHTOOL_RX_CHNL_STATS_LEN;

	ret = eip_ethtool_wr_egress_chnl_stats(link, ilink, &data[i]);
	if (ret)
		return -EINVAL;
	i += EIP_ETHTOOL_TX_CHNL_STATS_LEN;

	//Get device role for ingress device
	devid = eip_devid(&link->rx);
	chid = eip_chid(&link->rx);

	is_ipsec = __get_device_role(devid, chid);
	if (is_ipsec) { //IPSEC
		read_lock(&ilink->lock);
		list_for_each_entry (eip_xs, &ilink->eip_xs_l, eip_xs_l) {
			if (eip_xs->inbound) {
				ret = eip_ethtool_wr_ipsec_ingress_stats(
					devid, eip_xs, &data[i]);
				if (ret) {
					read_unlock(&ilink->lock);
					return -EINVAL;
				}
				i += EIP_ETHTOOL_RX_SAS_STATS_LEN;
			}
		}
		read_unlock(&ilink->lock);
	} else {
		ret = eip_ethtool_wr_macsec_ingress_stats(netdev, devid,
							  &data[i]);
		if (ret)
			return -EINVAL;
		i += EIP_ETHTOOL_RX_SAS_STATS_LEN;
	}

	//Get device role for egress device
	devid = eip_devid(&link->tx);
	chid = eip_chid(&link->tx);

	is_ipsec = __get_device_role(devid, chid);
	if (is_ipsec) { //IPSEC

		read_lock(&ilink->lock);
		list_for_each_entry (eip_xs, &ilink->eip_xs_l, eip_xs_l) {
			if (!eip_xs->inbound) {
				ret = eip_ethtool_wr_ipsec_egress_stats(
					devid, eip_xs, &data[i]);
				if (ret) {
					read_unlock(&ilink->lock);
					return -EINVAL;
				}
				i += EIP_ETHTOOL_TX_SAS_STATS_LEN;
			}
		}
		read_unlock(&ilink->lock);
	} else { //	MACSEC
		ret = eip_ethtool_wr_macsec_egress_stats(netdev, devid,
							 &data[i]);
		if (ret)
			return -EINVAL;
		i += EIP_ETHTOOL_TX_SAS_STATS_LEN;
	}

	return ret;
}