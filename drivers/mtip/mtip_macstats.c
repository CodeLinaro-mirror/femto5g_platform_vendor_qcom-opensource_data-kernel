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

u64 mtip_macstats_read_stat(void __iomem *macstats_base_addr, unsigned int offset)
{
    u64 stat = 0;
    u32 lower;
    u32 upper;

    // read the lower 32 bits of the stat
    lower = ioread32(macstats_base_addr + offset);

    // read the upper 32 bits of the stat from DATA_HI
    upper = ioread32(macstats_base_addr + MTIP_MACSTATS_DATA_HI_OFFSET);

    stat = ((u64)upper << 32) | ((u64)lower);
    return stat;
}

void mtip_macstats_get_stats(struct net_device *netdev, u64 *data)
{
    struct mtip_netdev_priv* priv;
    u32 link_index;
    int i = 0;
    void __iomem *macstats_base_addr;
    u32 real_link_number;
    u32 port_type;

    priv = netdev_priv(netdev);
    link_index = priv->link_index;

    if (mtip_lookup_port_type_by_link_index(link_index, &port_type) < 0)
    {
        CSMLOGERR("invalid port_type for link_index %d", link_index);
        return;
    }

    if (port_type > 3) 
    {
        CSMLOGERR("Access to MACSTATS for C2C/DBG ports not supported\n");
        return;
    }

    macstats_base_addr = platform_driver_priv->devices.port_devices[port_type].macstats_base_addr;

    mtip_lookup_real_link_number_by_link_index(link_index, &real_link_number);

    if ( port_type <=2 )
    {
    // the Rx stats
    data[i] = mtip_macstats_read_stat(macstats_base_addr, real_link_number*MTIP_MACSTATS_RX_BLOCKSIZE + MTIP_MACSTATS_ETHERSTATSOCTETS_REG_OFFET);
    data[++i] = mtip_macstats_read_stat(macstats_base_addr, real_link_number*MTIP_MACSTATS_RX_BLOCKSIZE + MTIP_MACSTATS_OCTETSRECEIVEDOK_REG_OFFET);
    data[++i] = mtip_macstats_read_stat(macstats_base_addr, real_link_number*MTIP_MACSTATS_RX_BLOCKSIZE + MTIP_MACSTATS_VLANRECEIVEDOK_REG_OFFSET);
    data[++i] = mtip_macstats_read_stat(macstats_base_addr, real_link_number*MTIP_MACSTATS_RX_BLOCKSIZE + MTIP_MACSTATS_INERRORS_REG_OFFET);
    data[++i] = mtip_macstats_read_stat(macstats_base_addr, real_link_number*MTIP_MACSTATS_RX_BLOCKSIZE + MTIP_MACSTATS_INUCASTPKTS_REG_OFFET);
    data[++i] = mtip_macstats_read_stat(macstats_base_addr, real_link_number*MTIP_MACSTATS_RX_BLOCKSIZE + MTIP_MACSTATS_INMCASTPKTS_REG_OFFET);
    data[++i] = mtip_macstats_read_stat(macstats_base_addr, real_link_number*MTIP_MACSTATS_RX_BLOCKSIZE + MTIP_MACSTATS_INBCASTPKTS_REG_OFFET);
    data[++i] = mtip_macstats_read_stat(macstats_base_addr, real_link_number*MTIP_MACSTATS_RX_BLOCKSIZE + MTIP_MACSTATS_ETHERSTATSDROPS_REG_OFFET);
    data[++i] = mtip_macstats_read_stat(macstats_base_addr, real_link_number*MTIP_MACSTATS_RX_BLOCKSIZE + MTIP_MACSTATS_ETHERSTATSPKTS_REG_OFFET);

    // the Tx stats
    data[++i] = mtip_macstats_read_stat(macstats_base_addr, real_link_number*MTIP_MACSTATS_TX_BLOCKSIZE + MTIP_MACSTATS_OCTETSTRANSMITTEDOK_REG_OFFET);
    data[++i] = mtip_macstats_read_stat(macstats_base_addr, real_link_number*MTIP_MACSTATS_TX_BLOCKSIZE + MTIP_MACSTATS_VLANTRANSMITTEDOK_OFFET);
    data[++i] = mtip_macstats_read_stat(macstats_base_addr, real_link_number*MTIP_MACSTATS_TX_BLOCKSIZE + MTIP_MACSTATS_OUTERRORS_REG_OFFET);
    data[++i] = mtip_macstats_read_stat(macstats_base_addr, real_link_number*MTIP_MACSTATS_TX_BLOCKSIZE + MTIP_MACSTATS_OUTUCASTPKTS_REG_OFFET);
    data[++i] = mtip_macstats_read_stat(macstats_base_addr, real_link_number*MTIP_MACSTATS_TX_BLOCKSIZE + MTIP_MACSTATS_OUTMCASTPKTS_REG_OFFET);
    data[++i] = mtip_macstats_read_stat(macstats_base_addr, real_link_number*MTIP_MACSTATS_TX_BLOCKSIZE + MTIP_MACSTATS_OUTBCASTPKTS_REG_OFFET);
    }
    else if (port_type == 3)
    {
      if (real_link_number == 0 )
      {
          // the Rx stats
        data[i] = mtip_macstats_read_stat(macstats_base_addr,   MTIP_C2C_MACSTATS_ETHERSTATSOCTETS_REG_OFFET);
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_OCTETSRECEIVEDOK_REG_OFFET);
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_VLANRECEIVEDOK_REG_OFFSET);
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_INERRORS_REG_OFFET);
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_INUCASTPKTS_REG_OFFET);
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_INMCASTPKTS_REG_OFFET);
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_INBCASTPKTS_REG_OFFET);
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_ETHERSTATSDROPS_REG_OFFET);
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_ETHERSTATSPKTS_REG_OFFET);
    
        // the Tx stats
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_OCTETSTRANSMITTEDOK_REG_OFFET);
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_VLANTRANSMITTEDOK_OFFET);
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_OUTERRORS_REG_OFFET);
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_OUTUCASTPKTS_REG_OFFET);
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_OUTMCASTPKTS_REG_OFFET);
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_OUTBCASTPKTS_REG_OFFET);
      }
      else if ( real_link_number == 1 )
      {
        // the Rx stats
        data[i]   =  mtip_macstats_read_stat(macstats_base_addr,MTIP_C2C_MACSTATS_ETHERSTATSOCTETS_2_REG_OFFET);
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_OCTETSRECEIVEDOK_2_REG_OFFET);
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_VLANRECEIVEDOK_2_REG_OFFSET);
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_INERRORS_2_REG_OFFET);
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_INUCASTPKTS_2_REG_OFFET);
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_INMCASTPKTS_2_REG_OFFET);
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_INBCASTPKTS_2_REG_OFFET);
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_ETHERSTATSDROPS_2_REG_OFFET);
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_ETHERSTATSPKTS_2_REG_OFFET);
    
        // the Tx stats
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_OCTETSTRANSMITTEDOK_2_REG_OFFET);
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_VLANTRANSMITTEDOK_2_OFFET);
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_OUTERRORS_2_REG_OFFET);
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_OUTUCASTPKTS_2_REG_OFFET);
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_OUTMCASTPKTS_2_REG_OFFET);
        data[++i] = mtip_macstats_read_stat(macstats_base_addr, MTIP_C2C_MACSTATS_OUTBCASTPKTS_2_REG_OFFET);
      }
    }
}

