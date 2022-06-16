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

static int mtip_get_sset_count(struct net_device *netdev, int sset)
{
    CSMLOGINFO("ethtool: get_sset_count %d, %d\n", sset, MTIP_ETHTOOL_STATS_LEN);

	switch (sset) {
	case ETH_SS_STATS:
		return MTIP_ETHTOOL_STATS_LEN;
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
}

static void mtip_ethtool_get_stats(struct net_device *netdev, struct ethtool_stats *stats, u64 *data) 
{
    CSMLOGINFO("ethtool: get_stats\n");

    memset(data, 0, MTIP_ETHTOOL_STATS_LEN*sizeof(u64));

    // read the stats from the HW
    mtip_macstats_get_stats(netdev, data);
}

static int mtip_check_if_running(struct net_device *dev)
{
    CSMLOGINFO("ethtool: check_if_running\n");

	if (!netif_running(dev))
		return -EBUSY;
	return 0;
}

static void mtip_getdrvinfo(struct net_device *dev, struct ethtool_drvinfo *info)
{
    CSMLOGINFO("ethtool: getdrvinfo\n");

    strlcpy(info->driver, MTIP_MAC_DRIVER, sizeof(info->driver));
	strlcpy(info->version, MTIP_MAC_DRIVER_VERSION, sizeof(info->version));
}

static int mtip_get_link_ksettings(struct net_device *dev, struct ethtool_link_ksettings *cmd)
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

static const struct ethtool_ops mtip_ethtool_ops = {
   .begin = mtip_check_if_running,
   .get_drvinfo = mtip_getdrvinfo,
   .get_sset_count  = mtip_get_sset_count,
   .get_strings = mtip_get_strings,
   .get_ethtool_stats = mtip_ethtool_get_stats,
   .get_ts_info = mtip_get_ts_info,
   .get_link_ksettings = mtip_get_link_ksettings,
};

void mtip_ethtool_set_ops(struct net_device *netdev)
{
   CSMLOGINFO("Setting ethtool ops for netdev 0x%lx\n", (unsigned long)netdev);
   netdev->ethtool_ops = &mtip_ethtool_ops;
}
