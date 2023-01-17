//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#include <linux/init.h>

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/gfp.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/in.h>
#include <linux/string.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/skbuff.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/bitrev.h>
#include <linux/slab.h>
#include <linux/moduleparam.h>

#include <linux/sched.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/errno.h>  /* error codes */
#include <linux/types.h>  /* size_t */
#include <linux/interrupt.h> /* mark_bh */

#include <linux/in.h>
#include <linux/netdevice.h>   /* struct device, and other headers */
#include <linux/etherdevice.h> /* eth_type_trans */
#include <linux/ip.h>          /* struct iphdr */
#include <linux/tcp.h>         /* struct tcphdr */
#include <linux/skbuff.h>

#include "mtip_ethtool.h"
#include "mtip.h"
#include "mtip_platform.h"
#include "mtip_device.h"
#include "mtip_phy.h"
#include "mtip_macstats.h"
#include "mtip_mac.h"
#include "mtip_pcs.h"
#include "mtip_debug_eth.h"

static const char * const mtip_ethtool_stat_strings[] = {
    "EtherStatsOctets",
    "OctetsReceivedOK",
	"VLANReceivedOK",
    "InErrors",
    "InUCastPkts",
    "InMCastPkts",
    "InBCastPkts",
    "EtherStatsDrops",
    "EtherStatsPkts",
    "OctetsTransmittedOK",
    "VLANTransmittedOK",
    "OutErrors",
    "OutUCastPkts",
    "OutMCastPkts",
    "OutBCastPkts",
};

#define MTIP_ETHTOOL_STATS_LEN	ARRAY_SIZE(mtip_ethtool_stat_strings)

static const char* const mtip_ethtool_priv_flags_str_arr[] = {
    "1x100GBASE_R",
    "1x100GBASE_R_RSFEC_LL",
    "1x100GBASE_R_RSFEC",
    "1x100GBASE_R2",
    "1x100GBASE_R2_RSFEC",
    "1x100GBASE_R4",
    "1x100GBASE_R4_RSFEC",
    "1x50GBASE_R",
    "1x50GBASE_R_RSFEC",
    "2x50GBASE_R",
    "2x50GBASE_R_RSFEC",
    "1x50GBASE_R2",
    "1x50GBASE_R2_RSFEC",
    "1x50GBASE_R2_LUAI",
    "1x50GBASE_R2_LUAI_FEC",
    "2x50GBASE_R2",
    "2x50GBASE_R2_FEC",
    "2x50GBASE_R2_LUAI",
    "2x50GBASE_R2_LUAI_FEC",
    "1x40GBASE_R4",
    "1x40GBASE_R4_FEC",
    "1x25GBASE_R",
    "1x25GBASE_R_FEC",
    "4x25GBASE_R",
    "4x25GBASE_R_FEC",
    "1x25GBASE_R_RSFEC",
    "4x25GBASE_R_RSFEC",
    "1x10GBASE_R",
    "1x10GBASE_R_FEC",
    "4x10GBASE_R",
    "4x10GBASE_R_FEC",
};

#define MTIP_ETHTOOL_PRIV_FLAGS_LEN ARRAY_SIZE(mtip_ethtool_priv_flags_str_arr)

static int mtip_get_sset_count(struct net_device *netdev, int sset)
{
    CSMLOGINFO("ethtool: get_sset_count %d, %d\n", sset, MTIP_ETHTOOL_STATS_LEN);

	switch (sset) {
	case ETH_SS_STATS:
		return MTIP_ETHTOOL_STATS_LEN;
    case ETH_SS_PRIV_FLAGS:
        return MTIP_ETHTOOL_PRIV_FLAGS_LEN;
	default:
		return -EOPNOTSUPP;
	}
}

static void mtip_get_strings(struct net_device *netdev, u32 stringset, u8 *data)
{
    int i;
    CSMLOGINFO("ethtool: get_strings stringset %d, %d\n", stringset, MTIP_ETHTOOL_STATS_LEN);

    if (stringset == ETH_SS_STATS) 
    {
		for (i = 0; i < MTIP_ETHTOOL_STATS_LEN; i++) {
			strlcpy(data, mtip_ethtool_stat_strings[i],
				ETH_GSTRING_LEN);
			data += ETH_GSTRING_LEN;
		}
    }
    else if (stringset == ETH_SS_PRIV_FLAGS) 
    {
        for (i = 0; i < MTIP_ETHTOOL_PRIV_FLAGS_LEN; i++) {
            strlcpy(data, mtip_ethtool_priv_flags_str_arr[i],
                ETH_GSTRING_LEN);
            data += ETH_GSTRING_LEN;
        }
    }
}

static void mtip_ethtool_get_stats(struct net_device *netdev, struct ethtool_stats *stats, u64 *data) 
{
    CSMLOGINFO("ethtool: get_stats\n");

    memset(data, 0, MTIP_ETHTOOL_STATS_LEN*sizeof(u64));

    // read the stats from the HW
    mtip_macstats_get_stats(netdev, data);
}

int mtip_check_if_running(struct net_device *dev)
{
    CSMLOGINFO("ethtool: check_if_running\n");

	if (!netif_running(dev))
		return -EBUSY;
	return 0;
}

void mtip_getdrvinfo(struct net_device *dev, struct ethtool_drvinfo *info)
{
    CSMLOGINFO("ethtool: getdrvinfo\n");

    strlcpy(info->driver, MTIP_MAC_DRIVER, sizeof(info->driver));
	strlcpy(info->version, MTIP_MAC_DRIVER_VERSION, sizeof(info->version));
}

int mtip_get_link_ksettings(struct net_device *dev, struct ethtool_link_ksettings *cmd)
{
    struct mtip_netdev_priv *priv;
    u32 link_index;
    u32 port_device_index;
    u32 link_device_index;
    struct mtip_link_device_info* link_device;

    priv = netdev_priv(dev);
    link_index = priv->link_index;

    CSMLOGINFO("ethtool: get_link_ksettings for link_index: %d\n", link_index);

	if (!netif_running(dev)) {
		CSMLOGERR("%s: interface is disabled: we cannot track "
		"link speed / duplex setting\n", dev->name);
		return -EBUSY;
	}

    if (mtip_lookup_device_by_link_index(link_index, &port_device_index, &link_device_index) < 0)
    {
       CSMLOGERR("unable to find device for link %d", link_index);
       return -ENODEV;
    }

    link_device = &platform_driver_priv->devices.port_devices[port_device_index].link_devices[link_device_index];

    cmd->base.speed = mtip_platform_convert_lane_speed_to_gbps(link_device->lane_speed) * link_device->num_lanes;

    return 0;
}

static int mtip_get_ts_info(struct net_device *ndev, struct ethtool_ts_info *info)
{
    CSMLOGINFO("ethtool: getting ts info\n");

	ethtool_op_get_ts_info(ndev, info);

	info->so_timestamping |=
            SOF_TIMESTAMPING_TX_HARDWARE |
			SOF_TIMESTAMPING_RX_HARDWARE |
			SOF_TIMESTAMPING_RAW_HARDWARE |
            SOF_TIMESTAMPING_SYS_HARDWARE;

	info->tx_types = BIT(HWTSTAMP_TX_OFF) |
			 BIT(HWTSTAMP_TX_ON);

	info->rx_filters = BIT(HWTSTAMP_FILTER_NONE);

	info->rx_filters |= BIT(HWTSTAMP_FILTER_PTP_V2_L4_EVENT) |
			    BIT(HWTSTAMP_FILTER_PTP_V2_L2_EVENT) |
			    BIT(HWTSTAMP_FILTER_PTP_V2_EVENT);

    info->phc_index = 0;
	return 0;
}

int	mtip_ethtool_get_fecparam(struct net_device* netdev, struct ethtool_fecparam* pfec)
{
    u32 cmd = pfec->cmd;
    struct mtip_netdev_priv *priv;
    u32 link_index;

    priv = netdev_priv(netdev);
    link_index = priv->link_index;

    // set the capable set of FECs
    pfec->fec = ETHTOOL_FEC_OFF | ETHTOOL_FEC_RS;

    // set the active fec
    pfec->active_fec = platform_driver_priv->mtip_links[link_index]->active_fec;

    CSMLOGINFO("Getting FEC parameter for link index: %d, cmd: %d", link_index, cmd);

    return 0;
}

int	mtip_ethtool_set_fecparam(struct net_device* netdev, struct ethtool_fecparam* pfec)
{
    u32 cmd = pfec->cmd;
    u32 active_fec = pfec->active_fec;
    u32 fec = pfec->fec;
    struct mtip_netdev_priv *priv;
    u32 link_index;
    u32 port_device_index;
    u32 link_device_index;
    struct mtip_port_device_info* port_device = NULL;
    struct mtip_link_device_info* link_device = NULL;
    int i;

    priv = netdev_priv(netdev);
    link_index = priv->link_index;

    CSMLOGINFO("Setting FEC parameter for link index: %d, cmd: %d, active: %d, fec: %d", link_index, cmd, active_fec, fec);

    mtip_lookup_device_by_link_index(link_index, &port_device_index, &link_device_index);

    CSMLOGINFO("link index: %d, port_device: %d, link_device: %d", link_index, port_device_index, link_device_index);

    // set the port_device
    port_device = &platform_driver_priv->devices.port_devices[port_device_index];

    // check the value of the active_fec
    if (fec == ETHTOOL_FEC_OFF) 
    {
        // find the port corresponding to the link
        CSMLOGINFO("Going to set FEC OFF for link_index: %d", link_index);

        // turn FEC to OFF
        mtip_mac_wrapper_disable_rsfec_for_25g_mode(port_device);

        // disable rsfec in pcs
        for (i = 0; i < port_device->num_link_phandles; ++i)
        {
            link_device = &port_device->link_devices[i];
            mtip_pcs_disable_rsfec_for_25g_mode(link_device);
        }
    }
    else if (fec == ETHTOOL_FEC_RS) 
    {
        // find the port corresponding to the link
        CSMLOGINFO("Going to set FEC RS for link_index: %d", link_index);

        // turn on RS FEC
        mtip_mac_wrapper_enable_rsfec_for_25g_mode(port_device);

        // enable rsfec in the pcs
        for (i = 0; i < port_device->num_link_phandles; ++i)
        {
            link_device = &port_device->link_devices[i];
            mtip_pcs_enable_rsfec_for_25g_mode(link_device);
        }
    }
    else
    {
        CSMLOGERR("Unsupported FEC %d parameter for link index: %d", active_fec, link_index);
        return -EINVAL;
    }

    return 0;
}

static u32 mtip_ethtool_get_priv_flags(struct net_device *netdev)
{
    struct mtip_netdev_priv *priv;
    u32 link_index;

    priv = netdev_priv(netdev);
    link_index = priv->link_index;

    CSMLOGINFO("Get priv called for link index: %d", link_index);

    // return flags currently enabled
    return priv->priv_flags;
}

#define MTIP_ETHTOOL_SET_PFLAG(params, pflag, enable)			\
 	do {							\
 		if (enable)					\
 			(params)->priv_flags |= BIT(pflag);		\
 		else						\
 			(params)->priv_flags &= ~(BIT(pflag));	\
	} while (0)

static int mtip_ethtool_handle_pflag(struct net_device *netdev,
			      u32 wanted_flags,
			      u32 flag)
{
    struct mtip_netdev_priv *priv = netdev_priv(netdev);
	bool enable = !!(wanted_flags & BIT(flag));
    u32 changes = wanted_flags ^ priv->priv_flags;

	if (!(changes & BIT(flag)))
		return 0;

	MTIP_ETHTOOL_SET_PFLAG(priv, flag, enable);
	return 0;
}

static int mtip_ethtool_set_priv_flags(struct net_device *netdev, u32 flags)
{
    struct mtip_netdev_priv *priv;
    u32 link_index;
    u32 pflag;
    int err;

    priv = netdev_priv(netdev);
    link_index = priv->link_index;

    CSMLOGINFO("Set priv called for link index: %d with flags: 0x%x", link_index, flags);

    if (mtip_check_if_running(netdev) == true) 
    {
        CSMLOGERR("Set priv called when running for link_index: %d", link_index);
        return -EINVAL;
    }

    for (pflag = 0; pflag < MTIP_ETHTOOL_PRIV_FLAGS_LEN; pflag++) {
        err = mtip_ethtool_handle_pflag(netdev, flags, pflag);
        if (err)
            break;
    }

    mtip_netdev_set_port_config(netdev);
    return err;
}

static void mtip_ethtool_set_msglevel(struct net_device *netdev, u32 level)
{
    u32 link_index;
    u32 real_port_number;
    struct mtip_netdev_priv *priv;

    priv = netdev_priv(netdev);
    link_index = priv->link_index;

    // check if the corresponding port is in LINK_UP state
    mtip_lookup_real_port_number_by_link_index(link_index, &real_port_number);

    switch (level)
    {
    case 0:
        {
            CSMLOGERR("Using set msglevel %d to toggle PHYLINK state to NOT CONNECTED for link index %d", level, link_index);
            platform_driver_priv->mtip_ports[real_port_number]->port_state = MTIP_PORT_STATE_DISCONNECTED;
        }
        break;

    case 1:
        {
            CSMLOGERR("Using set msglevel %d to set PHYLINK state to CONNECTED for DAC link index %d", level, link_index);
            platform_driver_priv->mtip_ports[real_port_number]->port_state = MTIP_PORT_STATE_CONNECTED;

            platform_driver_priv->mtip_ports[real_port_number]->sfp_port_type = PORT_DA;
        }
        break;

    case 2:
        {
            CSMLOGERR("Using set msglevel %d to set PHYLINK state to CONNECTED for FIBRE link index %d", level, link_index);
            platform_driver_priv->mtip_ports[real_port_number]->port_state = MTIP_PORT_STATE_CONNECTED;

            platform_driver_priv->mtip_ports[real_port_number]->sfp_port_type = PORT_FIBRE;
        }
        break;

    default:
        {
            CSMLOGERR("Ignoring msglevel %d for link index: %d", level, link_index);
        }
        break;
    }
}

static u32 mtip_ethtool_get_msglevel(struct net_device *netdev)
{
    u32 link_index;
    u32 real_port_number;
    struct mtip_netdev_priv *priv;

    priv = netdev_priv(netdev);
    link_index = priv->link_index;

    // check if the corresponding port is in LINK_UP state
    mtip_lookup_real_port_number_by_link_index(link_index, &real_port_number);

    return platform_driver_priv->mtip_ports[real_port_number]->port_state;
}

static const struct ethtool_ops mtip_ethtool_ops = {
   .get_drvinfo = mtip_getdrvinfo,
   .get_sset_count  = mtip_get_sset_count,
   .get_strings = mtip_get_strings,
   .get_ethtool_stats = mtip_ethtool_get_stats,
   .get_ts_info = mtip_get_ts_info,
   .get_link_ksettings = mtip_get_link_ksettings,
   .get_priv_flags = mtip_ethtool_get_priv_flags,
   .set_priv_flags = mtip_ethtool_set_priv_flags,
   .get_fecparam = mtip_ethtool_get_fecparam,
   .set_fecparam = mtip_ethtool_set_fecparam,
   .set_msglevel = mtip_ethtool_set_msglevel,
   .get_msglevel = mtip_ethtool_get_msglevel,
};

void mtip_ethtool_set_ops(struct net_device *netdev)
{
  struct mtip_netdev_priv* priv;
  u32 link_index;

   CSMLOGINFO("Setting ethtool ops for netdev 0x%lx\n", (unsigned long)netdev);

   priv = netdev_priv(netdev);
   link_index = priv->link_index;
   CSMLOGERR("Link index : %d\n",link_index);


   if(link_index == MTIP_DEBUG_ETH_LINK_INDEX)
      netdev->ethtool_ops = mtip_debug_eth_get_ethtool_ops();
   else
      netdev->ethtool_ops = &mtip_ethtool_ops;
}
