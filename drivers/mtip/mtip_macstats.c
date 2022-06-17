//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#include <linux/init.h>
#include <linux/module.h>

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
#include <linux/delay.h>
#include <linux/interrupt.h>

#include "mtip_macstats.h"

void mtip_macstats_get_stats(struct net_device *netdev, u64 *data)
{
    struct mtip_netdev_priv* priv;
    u32 link_index;
    int i = 0;
    void __iomem *macstats_base_addr;
    u32 port_device_index;
    u32 link_device_index;
    u32 real_link_number;

    priv = netdev_priv(netdev);
    link_index = priv->link_index;

    mtip_lookup_device_by_link_index(link_index, &port_device_index, &link_device_index);

    mtip_lookup_real_link_number_by_link_index(link_index, &real_link_number);

    macstats_base_addr = platform_driver_priv->devices.port_devices[port_device_index].macstats_base_addr;

    // the Rx stats
    data[i] = (u64)ioread32(macstats_base_addr + real_link_number*MTIP_MACSTATS_RX_BLOCKSIZE + MTIP_MACSTATS_ETHERSTATSOCTETS_REG_OFFET);
    data[++i] = (u64)ioread32(macstats_base_addr + real_link_number*MTIP_MACSTATS_RX_BLOCKSIZE + MTIP_MACSTATS_OCTETSRECEIVEDOK_REG_OFFET);
    data[++i] = (u64)ioread32(macstats_base_addr + real_link_number*MTIP_MACSTATS_RX_BLOCKSIZE + MTIP_MACSTATS_VLANRECEIVEDOK_REG_OFFSET);
    data[++i] = (u64)ioread32(macstats_base_addr + real_link_number*MTIP_MACSTATS_RX_BLOCKSIZE + MTIP_MACSTATS_INERRORS_REG_OFFET);
    data[++i] = (u64)ioread32(macstats_base_addr + real_link_number*MTIP_MACSTATS_RX_BLOCKSIZE + MTIP_MACSTATS_INUCASTPKTS_REG_OFFET);
    data[++i] = (u64)ioread32(macstats_base_addr + real_link_number*MTIP_MACSTATS_RX_BLOCKSIZE + MTIP_MACSTATS_INMCASTPKTS_REG_OFFET);
    data[++i] = (u64)ioread32(macstats_base_addr + real_link_number*MTIP_MACSTATS_RX_BLOCKSIZE + MTIP_MACSTATS_INBCASTPKTS_REG_OFFET);
    data[++i] = (u64)ioread32(macstats_base_addr + real_link_number*MTIP_MACSTATS_RX_BLOCKSIZE + MTIP_MACSTATS_ETHERSTATSDROPS_REG_OFFET);
    data[++i] = (u64)ioread32(macstats_base_addr + real_link_number*MTIP_MACSTATS_RX_BLOCKSIZE + MTIP_MACSTATS_ETHERSTATSPKTS_REG_OFFET);

    // the Tx stats
    data[++i] = (u64)ioread32(macstats_base_addr + real_link_number*MTIP_MACSTATS_TX_BLOCKSIZE + MTIP_MACSTATS_OCTETSTRANSMITTEDOK_REG_OFFET);
    data[++i] = (u64)ioread32(macstats_base_addr + real_link_number*MTIP_MACSTATS_TX_BLOCKSIZE + MTIP_MACSTATS_VLANTRANSMITTEDOK_OFFET);
    data[++i] = (u64)ioread32(macstats_base_addr + real_link_number*MTIP_MACSTATS_TX_BLOCKSIZE + MTIP_MACSTATS_OUTERRORS_REG_OFFET);
    data[++i] = (u64)ioread32(macstats_base_addr + real_link_number*MTIP_MACSTATS_TX_BLOCKSIZE + MTIP_MACSTATS_OUTUCASTPKTS_REG_OFFET);
    data[++i] = (u64)ioread32(macstats_base_addr + real_link_number*MTIP_MACSTATS_TX_BLOCKSIZE + MTIP_MACSTATS_OUTMCASTPKTS_REG_OFFET);
    data[++i] = (u64)ioread32(macstats_base_addr + real_link_number*MTIP_MACSTATS_TX_BLOCKSIZE + MTIP_MACSTATS_OUTBCASTPKTS_REG_OFFET);
}

