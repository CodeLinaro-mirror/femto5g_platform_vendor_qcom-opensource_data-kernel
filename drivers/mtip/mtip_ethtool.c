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
#include "mtip_client.h"

int mtip_ethtool_debug_logging_enable = 0;

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

#define MTIP_ETHTOOL_REG_OFFSET_ARRAY_SIZE 14
int mtip_ethtool_reg_buffer_size;

enum mtip_ethtool_regs_e
{
    MTIP_ETHTOOL_MAC,
    MTIP_ETHTOOL_PCS,
    MTIP_ETHTOOL_MAC_WRAPPER,
    MTIP_ETHTOOL_MAC_STATS,
    MTIP_ETHTOOL_RSFEC,
    MTIP_ETHTOOL_REG_MAX
};

struct mtip_ethtool_reg_offset
{
    u32 start_offset;
    u32 end_offset;
    enum mtip_ethtool_regs_e mtip_ethtool_regs;
};

struct mtip_ethtool_reg_offset mtip_ethtool_reg_offset_val[MTIP_ETHTOOL_REG_OFFSET_ARRAY_SIZE] =
{   {0,             0x000000A0,     MTIP_ETHTOOL_MAC},
    {0,             0x000000D4,     MTIP_ETHTOOL_PCS},
    {0x00000320,    0x0000036C,     MTIP_ETHTOOL_PCS},
    {0x00000640,    0x0000068C,     MTIP_ETHTOOL_PCS},
    {0x00020000,    0x00020040,     MTIP_ETHTOOL_PCS},
    {0x00020100,    0x0002019C,     MTIP_ETHTOOL_PCS},
    {0,             0x00000384,     MTIP_ETHTOOL_MAC_WRAPPER},
    {0,             0x0000001C,     MTIP_ETHTOOL_MAC_STATS},
    {0x00000100,    0x000004CC,     MTIP_ETHTOOL_MAC_STATS},
    {0,             0x0000007c,     MTIP_ETHTOOL_RSFEC},
    {0x00000100,    0x0000012c,     MTIP_ETHTOOL_RSFEC},
    {0x00000200,    0x0000023c,     MTIP_ETHTOOL_RSFEC},
    {0x00000284,    0x00000290,     MTIP_ETHTOOL_RSFEC},
    {0x000002C0,    0x000002D8,     MTIP_ETHTOOL_RSFEC}
};

#define MTIP_ETHTOOL_PRIV_FLAGS_LEN ARRAY_SIZE(mtip_ethtool_priv_flags_str_arr)

const char* mtip_ethtool_get_priv_flags_str(u32 index)
{
    return mtip_ethtool_priv_flags_str_arr[index];
}

static int mtip_get_sset_count(struct net_device *netdev, int sset)
{
    CSMLOGDBG("ethtool: get_sset_count %d, %d\n", sset, MTIP_ETHTOOL_STATS_LEN);

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
    CSMLOGDBG("ethtool: get_strings stringset %d, %d\n", stringset, MTIP_ETHTOOL_STATS_LEN);

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
    CSMLOGDBG("ethtool: get_stats\n");

    memset(data, 0, MTIP_ETHTOOL_STATS_LEN*sizeof(u64));

    // read the stats from the HW
    mtip_macstats_get_stats(netdev, data);
}

int mtip_check_if_running(struct net_device *dev)
{
    CSMLOGDBG("ethtool: check_if_running\n");

	if (!netif_running(dev))
		return -EBUSY;
	return 0;
}

void mtip_ethtool_get_dev_regs
(
    struct platform_device* port_pdev,
    void __iomem *dev_base_addr,
    void *buf,
    u32 *wr_ptr,
    struct resource *dev_resource,
    struct mtip_ethtool_reg_offset *reg_offset_array,
    u32 reg_offset_array_idx
)
{
    u32 *rbuf = (u32 *)buf;
    u32 *reg_addr = 0x0;
    u32 reg_offset = 0;
    
    CSMLOGINFO("mtip_ethtool: mtip_get_dev_regs port base = 0x%x, port end 0x%x port size = 0x%x "
               "Dev wr_ptr: %d addr 0x%x arry_idx %d \n",dev_resource->start, dev_resource->end,
               resource_size(dev_resource), *wr_ptr, dev_base_addr, reg_offset_array_idx);

    for (reg_offset = reg_offset_array[reg_offset_array_idx].start_offset; 
         (reg_offset <= reg_offset_array[reg_offset_array_idx].end_offset) &&
         (*wr_ptr < mtip_ethtool_reg_buffer_size);)
    {
        reg_addr = (u32*)(dev_base_addr + reg_offset);
        rbuf[(*wr_ptr)++] = (u32)(dev_resource->start + reg_offset);    // Reg Address
        rbuf[(*wr_ptr)++] = (u32)ioread32(reg_addr);                    // Reg Value
        reg_offset+=4;
    }
}

static void mtip_ethtool_dump_regs(u32 link_index, void *buf)
{
    u32 wr_idx = 0;
    u32 port_device_index;
    u32 link_device_index;
    struct mtip_link_device_info* link_device;
    struct resource *dev_resource;
    u32 mtip_reg_idx = 0;

    struct platform_device* pdev;
    void __iomem *dev_ioaddr;

    CSMLOGINFO("mtip_ethtool: Entering mtip_ethtool_dump_regs with link_idx %d \n", link_index);

    if (mtip_lookup_device_by_link_index(link_index, &port_device_index, &link_device_index) < 0)
    {
       CSMLOGERR("mtip_ethtool: unable to find device for link %d", link_index);
       return;
    }

    link_device = &platform_driver_priv->devices.port_devices[port_device_index].link_devices[link_device_index];
    
    for (mtip_reg_idx = 0; mtip_reg_idx < MTIP_ETHTOOL_REG_OFFSET_ARRAY_SIZE; mtip_reg_idx++)
    {
        switch (mtip_ethtool_reg_offset_val[mtip_reg_idx].mtip_ethtool_regs)
        {
            case MTIP_ETHTOOL_MAC:
                dev_ioaddr = link_device->mac_ioaddr;
                pdev = platform_driver_priv->devices.port_devices[port_device_index].link_devices[link_device_index].link_pdev;
                dev_resource = platform_get_resource_byname(pdev, IORESOURCE_MEM, "mac");
            break;

            case MTIP_ETHTOOL_PCS:
                dev_ioaddr = link_device->pcs_ioaddr;
                pdev = platform_driver_priv->devices.port_devices[port_device_index].link_devices[link_device_index].link_pdev;
                dev_resource = platform_get_resource_byname(pdev, IORESOURCE_MEM, "pcs");
            break;

            case MTIP_ETHTOOL_MAC_WRAPPER:
                dev_ioaddr = platform_driver_priv->devices.port_devices[port_device_index].wrapper_base_addr;
                pdev = platform_driver_priv->devices.port_devices[port_device_index].port_pdev;
                dev_resource = platform_get_resource_byname(pdev, IORESOURCE_MEM, "mac-wrapper");
            break;

            case MTIP_ETHTOOL_MAC_STATS:
                dev_ioaddr = platform_driver_priv->devices.port_devices[port_device_index].macstats_base_addr;
                pdev = platform_driver_priv->devices.port_devices[port_device_index].port_pdev;
                dev_resource = platform_get_resource_byname(pdev, IORESOURCE_MEM, "macstats");
            break;

            case MTIP_ETHTOOL_RSFEC:
                dev_ioaddr = platform_driver_priv->devices.port_devices[port_device_index].rsfec_base_addr;
                pdev = platform_driver_priv->devices.port_devices[port_device_index].port_pdev;
                dev_resource = platform_get_resource_byname(pdev, IORESOURCE_MEM, "rsfec");
            break;

            default:
            break;
        }
        
        mtip_ethtool_get_dev_regs(pdev, dev_ioaddr, buf, &wr_idx, dev_resource, mtip_ethtool_reg_offset_val, mtip_reg_idx);
    }
}

static void mtip_ethtool_get_regs(struct net_device *dev, struct ethtool_regs *regs, void *buf)
{
    struct mtip_netdev_priv *priv;
    u32 link_index;

    priv = netdev_priv(dev);
    link_index = priv->link_index;

    CSMLOGINFO("mtip_ethtool: Entering mtip_get_regs with Dev %s link_idx %d \n", dev->name, link_index);

    mtip_ethtool_dump_regs(link_index, buf);
}

static int mtip_ethtool_dump_regs_len()
{
    u32 reg_buf_size = 0;
    u32 mtip_reg_idx = 0;

    for (mtip_reg_idx = 0; mtip_reg_idx < MTIP_ETHTOOL_REG_OFFSET_ARRAY_SIZE; mtip_reg_idx++)
    {
        // add 1 at the end to inlcude the reg at the current index as well
        reg_buf_size += (mtip_ethtool_reg_offset_val[mtip_reg_idx].end_offset - mtip_ethtool_reg_offset_val[mtip_reg_idx].start_offset)/4 + 1;
    }

    // Multiply by 2 to add addresses of registers in buffer
    mtip_ethtool_reg_buffer_size = reg_buf_size * 2;

    CSMLOGDBG("mtip_ethtool: reg buffer size %d  total buff size %d \n", 
               reg_buf_size, mtip_ethtool_reg_buffer_size);
   
    // return size in bytes
    return (mtip_ethtool_reg_buffer_size * sizeof(u32));
}

static int mtip_ethtool_get_regs_len(struct net_device *dev)
{
    u32 reg_buf_size = 0;

    reg_buf_size = mtip_ethtool_dump_regs_len();
    
    return reg_buf_size;
}

void mtip_getdrvinfo(struct net_device *dev, struct ethtool_drvinfo *info)
{
    CSMLOGDBG("ethtool: getdrvinfo\n");

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

    CSMLOGDBG("ethtool: get_link_ksettings for link_index: %d\n", link_index);

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
    CSMLOGDBG("ethtool: getting ts info\n");

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

    CSMLOGDBG("Getting FEC parameter for link index: %d, cmd: %d", link_index, cmd);

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

    CSMLOGDBG("Setting FEC parameter for link index: %d, cmd: %d, active: %d, fec: %d", link_index, cmd, active_fec, fec);

    mtip_lookup_device_by_link_index(link_index, &port_device_index, &link_device_index);

    CSMLOGDBG("link index: %d, port_device: %d, link_device: %d", link_index, port_device_index, link_device_index);

    // set the port_device
    port_device = &platform_driver_priv->devices.port_devices[port_device_index];

    // check the value of the active_fec
    if (fec == ETHTOOL_FEC_OFF) 
    {
        // find the port corresponding to the link
        CSMLOGDBG("Going to set FEC OFF for link_index: %d", link_index);

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
        CSMLOGDBG("Going to set FEC RS for link_index: %d", link_index);

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

    CSMLOGDBG("Get priv called for link index: %d", link_index);

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

    CSMLOGDBG("Set priv called for link index: %d with flags: 0x%x", link_index, flags);

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
            CSMLOGINFO("Using set msglevel %d to toggle PHYLINK state to NOT CONNECTED for link index %d", level, link_index);
            platform_driver_priv->mtip_ports[real_port_number]->port_state = MTIP_PORT_STATE_DISCONNECTED;
        }
        break;

    case 1:
        {
            CSMLOGINFO("Using set msglevel %d to set PHYLINK state to CONNECTED for DAC link index %d", level, link_index);
            platform_driver_priv->mtip_ports[real_port_number]->port_state = MTIP_PORT_STATE_CONNECTED;

            platform_driver_priv->mtip_ports[real_port_number]->sfp_port_type = PORT_DA;
        }
        break;

    case 2:
        {
            CSMLOGINFO("Using set msglevel %d to set PHYLINK state to CONNECTED for FIBRE link index %d", level, link_index);
            platform_driver_priv->mtip_ports[real_port_number]->port_state = MTIP_PORT_STATE_CONNECTED;

            platform_driver_priv->mtip_ports[real_port_number]->sfp_port_type = PORT_FIBRE;
        }
        break;

    case 3:
        {
            mtip_platform_print_platform();
        }
        break;

    case 4:
        {
            mtip_print_topology(platform_driver_priv->topology);
        }
        break;

    case 5:
        {
            mtip_ethtool_debug_logging_enable = 1;
        }
        break;
    default:
        {
            CSMLOGINFO("Ignoring msglevel %d for link index: %d", level, link_index);
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
   .get_regs = mtip_ethtool_get_regs,
   .get_regs_len = mtip_ethtool_get_regs_len,
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

   CSMLOGDBG("Setting ethtool ops for netdev 0x%lx\n", (unsigned long)netdev);

   priv = netdev_priv(netdev);
   link_index = priv->link_index;

   // TBD: here link_index is not yet valid
   if(link_index == MTIP_DEBUG_ETH_LINK_INDEX)
      netdev->ethtool_ops = mtip_debug_eth_get_ethtool_ops();
   else
      netdev->ethtool_ops = &mtip_ethtool_ops;
}
