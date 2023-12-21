//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
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

#include "mtip_pcs.h"
#include "eth_phy_iface.h"
#include "mtip_debug_eth.h"

void mtip_pcs_reset_pcs(struct mtip_link_device_info* link_device)
{
    void __iomem *pcs_ioaddr = link_device->pcs_ioaddr;
    u32 write_val = MTIP_PCS_RESET_CONTROL_BIT;
    u32 link_index = link_device->link_index;

    CSMLOGDBG("Reseting PCS for link index: %d\n", link_index);

    // reset the PCS
    iowrite32(write_val, pcs_ioaddr + MTIP_PCS_CONTROL_REG_OFFSET);

    // wait for reset to complete
    mdelay(MTIP_PCS_RESET_DELAY_MSECS);

    CSMLOGDBG("PCS Reset done for link index: %d\n", link_index);
    return;
}

static void mtip_pcs_set_vendor_pcs_mode(enum mtip_port_config_enum port_config, struct mtip_link_device_info *link_device) {
    void __iomem *pcs_ioaddr = link_device->pcs_ioaddr;
    u32 vendor_pcs_mode = 0; // the default value sets ENA_CLAUSE49 = 0, DISABLE_MLD = 0, HI_BER25 = 0
    u32 link_index = link_device->link_index;

    switch (port_config) 
    {
    case MTIP_PORT_CONFIG_1x25GBASE_R:
    case MTIP_PORT_CONFIG_4x25GBASE_R:
    case MTIP_PORT_CONFIG_1x25GBASE_R_FEC:
    case MTIP_PORT_CONFIG_4x25GBASE_R_FEC:
        {
            vendor_pcs_mode = MTIP_PCS_VENDOR_PCS_ENA_CLAUSE49_BIT | MTIP_PCS_VENDOR_PCS_DISABLE_MLD_BIT | MTIP_PCS_VENDOR_PCS_HI_BER25_BIT;
        }
        break;

    case MTIP_PORT_CONFIG_4x25GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_1x25GBASE_R_RSFEC:
        {
            vendor_pcs_mode = MTIP_PCS_VENDOR_PCS_ENA_CLAUSE49_BIT | MTIP_PCS_VENDOR_PCS_HI_BER25_BIT; // DISABLE_MLD is not set
        }
        break;

    case MTIP_PORT_CONFIG_1x10GBASE_R:
    case MTIP_PORT_CONFIG_4x10GBASE_R:
    case MTIP_PORT_CONFIG_1x10GBASE_R_FEC:
    case MTIP_PORT_CONFIG_4x10GBASE_R_FEC:
        {
            vendor_pcs_mode = MTIP_PCS_VENDOR_PCS_ENA_CLAUSE49_BIT | MTIP_PCS_VENDOR_PCS_DISABLE_MLD_BIT; // HI_BER25 is not set
        }
        break;

    case MTIP_PORT_CONFIG_1x100GBASE_R:
    case MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC_LL:
    case MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_1x100GBASE_R2:
    case MTIP_PORT_CONFIG_1x100GBASE_R2_RSFEC:
    case MTIP_PORT_CONFIG_1x100GBASE_R4:
    case MTIP_PORT_CONFIG_1x100GBASE_R4_RSFEC:
    case MTIP_PORT_CONFIG_1x50GBASE_R:
    case MTIP_PORT_CONFIG_1x50GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_2x50GBASE_R:
    case MTIP_PORT_CONFIG_2x50GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_1x50GBASE_R2:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_RSFEC:
    case MTIP_PORT_CONFIG_1x40GBASE_R4:
    case MTIP_PORT_CONFIG_1x40GBASE_R4_FEC:
    default:
        {
            vendor_pcs_mode = 0; // ENA_CLAUSE49 = 0, DISABLE_MLD = 0, HI_BER25 = 0
        }
        break;
    }

    CSMLOGDBG("Setting VENDOR_PCS_MODE to: 0x%x for link_index: %d\n", vendor_pcs_mode, link_index);

    // set the vendor pcs mode register
    iowrite32(vendor_pcs_mode,
              pcs_ioaddr + MTIP_PCS_VENDOR_PCS_MODE_OFFSET);

    // read the value
    vendor_pcs_mode = (u32)ioread32(pcs_ioaddr + MTIP_PCS_VENDOR_PCS_MODE_OFFSET);

    CSMLOGDBG("Read VENDOR_PCS_MODE: 0x%x\n", vendor_pcs_mode);

    return;
}

static void mtip_pcs_set_vendor_vl_intvl(enum mtip_port_config_enum port_config, struct mtip_link_device_info *link_device) {
    void __iomem *pcs_ioaddr = link_device->pcs_ioaddr;
    u32 marker_counter = 0; // the default value is 0
    u32 link_index = link_device->link_index;

    switch (port_config) {
    case MTIP_PORT_CONFIG_1x50GBASE_R:
    case MTIP_PORT_CONFIG_1x50GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_2x50GBASE_R:
    case MTIP_PORT_CONFIG_2x50GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_1x25GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_4x25GBASE_R_RSFEC:
        {
            marker_counter = 0x4FFF;
        }
        break;

    case MTIP_PORT_CONFIG_1x100GBASE_R:
    case MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC_LL:
    case MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_1x100GBASE_R2:
    case MTIP_PORT_CONFIG_1x100GBASE_R2_RSFEC:
    case MTIP_PORT_CONFIG_1x100GBASE_R4:
    case MTIP_PORT_CONFIG_1x100GBASE_R4_RSFEC:
    case MTIP_PORT_CONFIG_1x50GBASE_R2:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_RSFEC:
    case MTIP_PORT_CONFIG_2x50GBASE_R2:
    case MTIP_PORT_CONFIG_2x50GBASE_R2_FEC:
    case MTIP_PORT_CONFIG_2x50GBASE_R2_LUAI:
    case MTIP_PORT_CONFIG_2x50GBASE_R2_LUAI_FEC:
    case MTIP_PORT_CONFIG_1x40GBASE_R4:
    case MTIP_PORT_CONFIG_1x40GBASE_R4_FEC:
        {
            marker_counter = 0x3FFF;
        }
        break;

    case MTIP_PORT_CONFIG_1x50GBASE_R2_LUAI:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_LUAI_FEC:
    case MTIP_PORT_CONFIG_1x25GBASE_R_FEC:
    case MTIP_PORT_CONFIG_4x25GBASE_R_FEC:
    case MTIP_PORT_CONFIG_1x25GBASE_R:
    case MTIP_PORT_CONFIG_4x25GBASE_R:
    case MTIP_PORT_CONFIG_1x10GBASE_R:
    case MTIP_PORT_CONFIG_1x10GBASE_R_FEC:
    case MTIP_PORT_CONFIG_4x10GBASE_R:
    case MTIP_PORT_CONFIG_4x10GBASE_R_FEC:
    default:
        {
            marker_counter = 0x0;
        }
        break;
    }

    CSMLOGDBG("Setting marker_counter to 0x%x for link_index: %d", marker_counter, link_index);

    // set the vendor vl intvl register
    iowrite32(marker_counter,
              pcs_ioaddr + MTIP_PCS_VENDOR_VL_INTVL_OFFSET);
    return;
}

static void mtip_pcs_set_v1_register_value0(struct mtip_link_device_info* link_device, u32* index, u32 val)
{
    void __iomem *pcs_ioaddr = link_device->pcs_ioaddr;
    u32 loc_index = *index;

    iowrite32(val, pcs_ioaddr + MTIP_PCS_VL0_0_OFFSET + loc_index*MTIP_PCS_VLn_OFFSET);
}

static void mtip_pcs_set_v1_register_value1(struct mtip_link_device_info* link_device, u32* index, u32 val)
{
    void __iomem *pcs_ioaddr = link_device->pcs_ioaddr;
    u32 loc_index = *index;

    iowrite32(val, pcs_ioaddr + MTIP_PCS_VL0_1_OFFSET + loc_index*MTIP_PCS_VLn_OFFSET);

    *index = loc_index + 1;
}

static void mtip_pcs_set_vl_registers_for_1x100gbase_R(struct mtip_link_device_info* link_device)
{
    u32 index = 0;

    mtip_pcs_set_v1_register_value0(link_device, &index, 0x68c1);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x21);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x719d);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x8e);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x4b59);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xe8);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x954d);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x7b);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x7f5);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x9);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x14dd);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xc2);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x4a9a);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x26);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x457b);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x66);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x24a0);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x76);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xc968);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xfb);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x6cfd);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x99);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x91b9);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x55);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xb95c);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xb2);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xf81a);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xbd);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xc783);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xca);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x3635);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xcd);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x31c4);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x4c);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xd6ad);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xb7);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x665f);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x2a);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xf0c0);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xe5);
}

static void mtip_pcs_set_vl_registers_for_1x100gbase_R_RSFEC(struct mtip_link_device_info* link_device)
{
    u32 index = 0;

    mtip_pcs_set_v1_register_value0(link_device, &index, 0x68c1);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x21);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x719d);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x8e);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x4b59);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xe8);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x954d);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x7b);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x7f5);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x9);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x14dd);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xc2);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x4a9a);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x26);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x457b);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x66);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x24a0);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x76);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xc968);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xfb);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x6cfd);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x99);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x91b9);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x55);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xb95c);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xb2);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xf81a);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xbd);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xc783);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xca);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x3635);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xcd);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x31c4);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x4c);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xd6ad);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xb7);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x665f);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x2a);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xf0c0);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xe5);
}

static void mtip_pcs_set_vl_registers_for_1x100gbase_R2(struct mtip_link_device_info* link_device)
{
    u32 index = 0;

    mtip_pcs_set_v1_register_value0(link_device, &index, 0x68c1);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x21);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x719d);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x8e);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x4b59);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xe8);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x954d);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x7b);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x7f5);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x9);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x14dd);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xc2);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x4a9a);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x26);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x457b);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x66);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x24a0);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x76);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xc968);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xfb);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x6cfd);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x99);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x91b9);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x55);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xb95c);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xb2);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xf81a);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xbd);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xc783);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xca);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x3635);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xcd);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x31c4);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x4c);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xd6ad);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xb7);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x665f);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x2a);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xf0c0);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xe5);
}

static void mtip_pcs_set_vl_registers_for_1x100gbase_R4(struct mtip_link_device_info* link_device)
{
    u32 index = 0;

    mtip_pcs_set_v1_register_value0(link_device, &index, 0x68c1);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x21);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x719d);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x8e);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x4b59);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xe8);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x954d);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x7b);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x7f5);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x9);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x14dd);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xc2);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x4a9a);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x26);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x457b);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x66);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x24a0);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x76);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xc968);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xfb);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x6cfd);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x99);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x91b9);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x55);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xb95c);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xb2);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xf81a);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xbd);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xc783);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xca);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x3635);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xcd);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x31c4);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x4c);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xd6ad);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xb7);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x665f);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x2a);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xf0c0);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xe5);
}

static void mtip_pcs_set_vl_registers_for_1x50gbase_R(struct mtip_link_device_info* link_device)
{
    u32 index = 0;

    mtip_pcs_set_v1_register_value0(link_device, &index, 0x7690);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x47);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xc4f0);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xe6);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x65c5);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x9b);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x79a2);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x3d);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x7F5);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x9);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x14DD);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x0C2);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x4A9A);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x26);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x457B);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x66);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x24A0);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x76);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x0C968);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x0FB);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x6CFD);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x99);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x91B9);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x55);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x0B95C);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x0B2);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x0F81A);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x0BD);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x0C783);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x0CA);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x3635);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x0CD);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x31C4);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x4C);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x0D6AD);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x0B7);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x665F);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x2A);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x0F0C0);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x0E5);
}

static void mtip_pcs_set_vl_registers_for_1x50gbase_R2(struct mtip_link_device_info* link_device)
{
    u32 index = 0;

    mtip_pcs_set_v1_register_value0(link_device, &index, 0x7690);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x47);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xc4f0);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xe6);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x65c5);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x9b);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x79a2);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x3d);
}

static void mtip_pcs_set_vl_registers_for_1x40gbase_R4(struct mtip_link_device_info* link_device)
{
    u32 index = 0;

    mtip_pcs_set_v1_register_value0(link_device, &index, 0x7690);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x47);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xc4f0);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xe6);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x65c5);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x9b);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x79a2);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x3d);
}

static void mtip_pcs_set_vl_registers_for_1x25gbase_R(struct mtip_link_device_info* link_device)
{
    u32 index = 0;

    mtip_pcs_set_v1_register_value0(link_device, &index, 0x68c1);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x21);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xc4f0);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xe6);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x65c5);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x9b);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x79a2);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x3d);
}

static void mtip_pcs_set_vl_registers_for_1x25gbase_R_RSFEC(struct mtip_link_device_info* link_device)
{
    u32 index = 0;

    mtip_pcs_set_v1_register_value0(link_device, &index, 0x68c1);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x21);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0xc4f0);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0xe6);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x65c5);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x9b);
    mtip_pcs_set_v1_register_value0(link_device, &index, 0x79a2);
    mtip_pcs_set_v1_register_value1(link_device, &index, 0x3d);
}

static void mtip_pcs_set_vl_registers(enum mtip_port_config_enum port_config, struct mtip_link_device_info* link_device)
{
    u32 link_index = link_device->link_index;

    switch (port_config) 
    {
    case MTIP_PORT_CONFIG_1x100GBASE_R:
        {
            mtip_pcs_set_vl_registers_for_1x100gbase_R(link_device);
        }
        break;

    case MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC_LL:
    case MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC:
        {
            mtip_pcs_set_vl_registers_for_1x100gbase_R_RSFEC(link_device);
        }
        break;

    case MTIP_PORT_CONFIG_1x100GBASE_R2:
    case MTIP_PORT_CONFIG_1x100GBASE_R2_RSFEC:
        {
            mtip_pcs_set_vl_registers_for_1x100gbase_R2(link_device);
        }
        break;

    case MTIP_PORT_CONFIG_1x100GBASE_R4:
    case MTIP_PORT_CONFIG_1x100GBASE_R4_RSFEC:
        {
            mtip_pcs_set_vl_registers_for_1x100gbase_R4(link_device);
        }
        break;

    case MTIP_PORT_CONFIG_1x50GBASE_R:
    case MTIP_PORT_CONFIG_1x50GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_2x50GBASE_R:
    case MTIP_PORT_CONFIG_2x50GBASE_R_RSFEC:
        {
            mtip_pcs_set_vl_registers_for_1x50gbase_R(link_device);
        }
        break;

    case MTIP_PORT_CONFIG_2x50GBASE_R2_FEC:
    case MTIP_PORT_CONFIG_2x50GBASE_R2_LUAI:
    case MTIP_PORT_CONFIG_2x50GBASE_R2_LUAI_FEC:
    case MTIP_PORT_CONFIG_1x50GBASE_R2:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_RSFEC:
    case MTIP_PORT_CONFIG_2x50GBASE_R2:
        {
            mtip_pcs_set_vl_registers_for_1x50gbase_R2(link_device);
        }
        break;

    case MTIP_PORT_CONFIG_1x40GBASE_R4:
    case MTIP_PORT_CONFIG_1x40GBASE_R4_FEC:
        {
            mtip_pcs_set_vl_registers_for_1x40gbase_R4(link_device);
        }
        break;

    case MTIP_PORT_CONFIG_1x25GBASE_R:
    case MTIP_PORT_CONFIG_4x25GBASE_R:
        {
            mtip_pcs_set_vl_registers_for_1x25gbase_R(link_device);
        }
        break;

    case MTIP_PORT_CONFIG_1x25GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_4x25GBASE_R_RSFEC:
        {
            mtip_pcs_set_vl_registers_for_1x25gbase_R_RSFEC(link_device);
        }
        break;

    case MTIP_PORT_CONFIG_1x10GBASE_R:
    case MTIP_PORT_CONFIG_1x10GBASE_R_FEC:
    case MTIP_PORT_CONFIG_4x10GBASE_R:
    case MTIP_PORT_CONFIG_4x10GBASE_R_FEC:
    default:
        break;
    }

    CSMLOGDBG("Set vl registers for link_index: %d port_config: %d", link_index, port_config);
    return;
}

void mtip_pcs_reset_all_vl_registers(struct mtip_link_device_info* link_device)
{
    int index = 0;
    void __iomem *pcs_ioaddr = link_device->pcs_ioaddr;

    CSMLOGDBG("Resetting all PCS VL registers\n");

    for (index = 0; index < 20; ++index) 
    {
        // reset the VL register
        iowrite32(0x0,
                  pcs_ioaddr + MTIP_PCS_VL0_0_OFFSET + index*MTIP_PCS_VLn_OFFSET);

        iowrite32(0x0,
                  pcs_ioaddr + MTIP_PCS_VL0_1_OFFSET + index*MTIP_PCS_VLn_OFFSET);

        CSMLOGDBG("done with index: %d\n", index);
    }
    return;
}

static void mtip_set_fec_control_registers(enum mtip_port_config_enum port_config, struct mtip_port_device_info *port_device)
{
    void __iomem *rsfec_base_addr = port_device->rsfec_base_addr;
    u32 fec_control_val = 0;
    u32 fec_control_val1 = 0;
    u32 fec_control_val2 = 0;
    u32 fec_control_val3 = 0;
    CSMLOGDBG("Setting all FEC control registers\n");

    switch (port_config)
    {
        case MTIP_PORT_CONFIG_1x10GBASE_R_FEC:
        case MTIP_PORT_CONFIG_1x25GBASE_R_FEC:
        case MTIP_PORT_CONFIG_1x40GBASE_R4_FEC:
        {
             fec_control_val = 0x3;
        }
        break;

        case MTIP_PORT_CONFIG_4x10GBASE_R_FEC:
        case MTIP_PORT_CONFIG_4x25GBASE_R_FEC:
        {
             fec_control_val = 0x3;
             fec_control_val1 = 0x3;
             fec_control_val2 = 0x3;
             fec_control_val3 = 0x3;
        }
        break;

        default:
        break;
    }

    iowrite32(fec_control_val,
              rsfec_base_addr + MTIP_FEC_CONTROL_OFFSET);
    iowrite32(fec_control_val1,
              rsfec_base_addr + MTIP_FEC_CONTROL1_OFFSET);
    iowrite32(fec_control_val2,
              rsfec_base_addr + MTIP_FEC_CONTROL2_OFFSET);
    iowrite32(fec_control_val3,
              rsfec_base_addr + MTIP_FEC_CONTROL3_OFFSET);
    return;
}

int mtip_pcs_config_pcs(u32 link_index)
{
    enum mtip_port_config_enum port_config;
    u32 port_type;

    if (mtip_lookup_port_type_by_link_index(link_index, &port_type) < 0)
    {
        CSMLOGERR("invalid port_type for link_index %d", link_index);
        return -1;
    }

    // configure the PCS of the link
    CSMLOGDBG("Configuring the PCS for link_index: %d, port_type: %d", link_index, port_type);

    // reset the PCS
    mtip_pcs_reset_pcs(&platform_driver_priv->devices.link_devices[link_index]);

    // this is the port configuration
    port_config = platform_driver_priv->mtip_ports[port_type]->port_config;

    // program the vendor pcs mode register
    mtip_pcs_set_vendor_pcs_mode(port_config, &platform_driver_priv->devices.link_devices[link_index]);

    // program the vendor vl intvl register
    mtip_pcs_set_vendor_vl_intvl(port_config, &platform_driver_priv->devices.link_devices[link_index]);

    // program the vendor vl registers
    mtip_pcs_set_vl_registers(port_config, &platform_driver_priv->devices.link_devices[link_index]);

    mtip_set_fec_control_registers(port_config, &platform_driver_priv->devices.port_devices[port_type]);

    return 0;
}

int mtip_pcs_enable_loopback(u32 link_index)
{
    u32 port_type;
    void __iomem *pcs_ioaddr;
    u32 pcs_control;

    if (mtip_lookup_port_type_by_link_index(link_index, &port_type) < 0)
    {
        CSMLOGERR("invalid port_type for link_index %d", link_index);
        return -1;
    }

    // set the loopback bit in the PCS corresponding to the link
    pcs_ioaddr = platform_driver_priv->devices.link_devices[link_index].pcs_ioaddr;

    // read the control register
    pcs_control = (u32)ioread32(pcs_ioaddr + MTIP_PCS_CONTROL_REG_OFFSET);

    // set the loopback bit in the PCS CONTROL register
    pcs_control |= MTIP_PCS_LOOPBACK_CONTROL_BIT;

    CSMLOGERR("Setting PCS loopback on link index %d, pcs_control: 0x%x\n", link_index, pcs_control);

    // write to the register
    iowrite32(pcs_control,
              pcs_ioaddr + MTIP_PCS_CONTROL_REG_OFFSET);
    return 0;
}

int mtip_rsfec_initialize(struct mtip_port_device_info *port_device) {
    int i;
    void __iomem *rsfec_base_addr = port_device->rsfec_base_addr;
    u32 rsfec_control_val = 0;
    u32 rsfec_dec_thresh = MTIP_RSFEC_DEC_THRESH_POR_VAL;
    enum mtip_port_config_enum port_config;
    u32 port_type = port_device->port_type;
    struct mtip_port_info* port_info = NULL;

    CSMLOGDBG("Initializing RSFEC for port %d\n", port_type);

    // this is the port configuration
    port_config = platform_driver_priv->mtip_ports[port_type]->port_config;

    port_info = platform_driver_priv->mtip_ports[port_type];

    if(port_type == MTIP_PORT_TYPE_DEBUG && !check_if_valid_port_config_for_debug_eth(port_config))
    {
        CSMLOGERR("config %d not supported on port_type %d", port_config, port_type);
        return 0;
    }

    for (i = 0; i < PHY_LANE_MAX; ++i) 
    {
        rsfec_control_val = 0;
        if (port_info->lane_config[i].lane_enabled) 
        {
            // lane is enabled
            switch (port_config) {
            case MTIP_PORT_CONFIG_1x100GBASE_R:
            case MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC_LL:
            case MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC:
            case MTIP_PORT_CONFIG_1x100GBASE_R2:
            case MTIP_PORT_CONFIG_1x100GBASE_R2_RSFEC:
                {
                    if ((port_type != MTIP_PORT_TYPE_DEBUG && i == 0) || (port_type == MTIP_PORT_TYPE_DEBUG && i == 2))
                    {
                        rsfec_control_val = MTIP_RSFEC_CONTROL_AM16_COPY_DIS_BIT;
                    }
                    else
                    {
                        rsfec_control_val = 0;
                    }
                }
                break;

            case MTIP_PORT_CONFIG_1x50GBASE_R:
            case MTIP_PORT_CONFIG_1x50GBASE_R_RSFEC:
            case MTIP_PORT_CONFIG_1x50GBASE_R2:
            case MTIP_PORT_CONFIG_1x50GBASE_R2_RSFEC:
                {
                    if ((port_type != MTIP_PORT_TYPE_DEBUG && i == 0) || (port_type == MTIP_PORT_TYPE_DEBUG && i == 2))
                    {
                        rsfec_control_val = MTIP_RSFEC_CONTROL_KP_ENABLE_BIT | MTIP_RSFEC_CONTROL_TC_PAD_VALUE_BIT;
                    }
                    else
                    {
                        rsfec_control_val = 0;
                    }
                }
                break;

            case MTIP_PORT_CONFIG_2x50GBASE_R:
            case MTIP_PORT_CONFIG_2x50GBASE_R_RSFEC:
                {
                    if ((i == 0) || (i == 1))
                    {
                        rsfec_control_val = MTIP_RSFEC_CONTROL_KP_ENABLE_BIT | MTIP_RSFEC_CONTROL_TC_PAD_VALUE_BIT;
                    }
                    else
                    {
                        rsfec_control_val = 0;
                    }
                }
                break;

            case MTIP_PORT_CONFIG_1x25GBASE_R:
            case MTIP_PORT_CONFIG_4x25GBASE_R:
            case MTIP_PORT_CONFIG_1x25GBASE_R_RSFEC:
            case MTIP_PORT_CONFIG_4x25GBASE_R_RSFEC:
                {
                    rsfec_control_val = 0;
                    rsfec_dec_thresh = MTIP_RSFEC_DEC_THRESH_4X25G_VAL;
                } break;

            case MTIP_PORT_CONFIG_1x50GBASE_R2_LUAI:
            case MTIP_PORT_CONFIG_1x50GBASE_R2_LUAI_FEC:
                {
                    if ((port_type != MTIP_PORT_TYPE_DEBUG && i == 0) || (port_type == MTIP_PORT_TYPE_DEBUG && i == 2))
                    {
                        rsfec_control_val = MTIP_RSFEC_CONTROL_KP_ENABLE_BIT | MTIP_RSFEC_CONTROL_TC_PAD_VALUE_BIT;
                    }
                    else
                    {
                        rsfec_control_val = 0;
                    }
                }
                break;

            case MTIP_PORT_CONFIG_2x50GBASE_R2:
            case MTIP_PORT_CONFIG_2x50GBASE_R2_FEC:
            case MTIP_PORT_CONFIG_2x50GBASE_R2_LUAI:
            case MTIP_PORT_CONFIG_2x50GBASE_R2_LUAI_FEC:
                {
                    if ((i == 0) || (i == 1))
                    {
                        rsfec_control_val = MTIP_RSFEC_CONTROL_KP_ENABLE_BIT | MTIP_RSFEC_CONTROL_TC_PAD_VALUE_BIT;
                    }
                    else
                    {
                        rsfec_control_val = 0;
                    }
                }
                break;

            case MTIP_PORT_CONFIG_1x25GBASE_R_FEC:
            case MTIP_PORT_CONFIG_4x25GBASE_R_FEC:
            case MTIP_PORT_CONFIG_1x100GBASE_R4:
            case MTIP_PORT_CONFIG_1x100GBASE_R4_RSFEC:
            case MTIP_PORT_CONFIG_1x40GBASE_R4:
            case MTIP_PORT_CONFIG_1x40GBASE_R4_FEC:
            case MTIP_PORT_CONFIG_1x10GBASE_R:
            case MTIP_PORT_CONFIG_1x10GBASE_R_FEC:
            case MTIP_PORT_CONFIG_4x10GBASE_R:
            case MTIP_PORT_CONFIG_4x10GBASE_R_FEC:
            default:
                {
                    rsfec_control_val = 0; // TC PAD VALUE is 0
                }
                break;
            }

            CSMLOGDBG("Setting RSFEC addr 0x%x to 0x%x\n", MTIP_RSFEC_CONTROL_OFFSET + i * MTIP_RSFEC_LINK_OFFSET, rsfec_control_val);
            CSMLOGDBG("Setting RSFEC dec thresh addr 0x%x to 0x%x\n",
                       MTIP_RSFEC_DEC_THRESH_OFFSET + i * MTIP_RSFEC_LINK_OFFSET,
                       rsfec_dec_thresh);

            // set the RSFEC control register
           iowrite32(rsfec_control_val,
                     rsfec_base_addr + MTIP_RSFEC_CONTROL_OFFSET + i * MTIP_RSFEC_LINK_OFFSET);

           // set the RSFEC decoder threshold register
           iowrite32(rsfec_dec_thresh,
                     rsfec_base_addr + MTIP_RSFEC_DEC_THRESH_OFFSET +
                     i * MTIP_RSFEC_LINK_OFFSET);

	}
    }
    return 0;
}

// enable RSFEC for 25G mode
// set the VENDOR PCS MODE to DISABLE MLD
void mtip_pcs_enable_rsfec_for_25g_mode(struct mtip_link_device_info* link_device)
{
    void __iomem *pcs_ioaddr = link_device->pcs_ioaddr;
    u32 vendor_pcs_mode = 0;
    u32 marker_counter = 0;
    u32 link_index = link_device->link_index;

    // set the active fec
    platform_driver_priv->mtip_links[link_index]->active_fec = ETHTOOL_FEC_RS;

    // set PCS_VENDOR_PCS_MODE [DISABLE_MLD] = 0
    vendor_pcs_mode = MTIP_PCS_VENDOR_PCS_ENA_CLAUSE49_BIT | MTIP_PCS_VENDOR_PCS_HI_BER25_BIT; 

    CSMLOGDBG("Setting VENDOR_PCS_MODE to: 0x%x\n", vendor_pcs_mode);

    // set the vendor pcs mode register
    iowrite32(vendor_pcs_mode,
              pcs_ioaddr + MTIP_PCS_VENDOR_PCS_MODE_OFFSET);

    // set PCS_VENDOR_VL_INTLVL marker_counter = 0x4FFF
    marker_counter = 0x4FFF;

    // set the vendor vl intvl register
    iowrite32(marker_counter,
              pcs_ioaddr + MTIP_PCS_VENDOR_VL_INTVL_OFFSET);
    return;
}

// disable RSFEC for 25G mode
// reset the VENDOR PCS MODE
void mtip_pcs_disable_rsfec_for_25g_mode(struct mtip_link_device_info* link_device)
{
    void __iomem *pcs_ioaddr = link_device->pcs_ioaddr;
    u32 vendor_pcs_mode = 0;
    u32 marker_counter = 0;
    u32 link_index = link_device->link_index;

    // set the active fec
    platform_driver_priv->mtip_links[link_index]->active_fec = ETHTOOL_FEC_OFF;

    // set PCS_VENDOR_PCS_MODE [DISABLE_MLD] = 1
    vendor_pcs_mode = MTIP_PCS_VENDOR_PCS_ENA_CLAUSE49_BIT | MTIP_PCS_VENDOR_PCS_DISABLE_MLD_BIT | MTIP_PCS_VENDOR_PCS_HI_BER25_BIT; 

    CSMLOGDBG("Setting VENDOR_PCS_MODE to: 0x%x\n", vendor_pcs_mode);

    // set the vendor pcs mode register
    iowrite32(vendor_pcs_mode,
              pcs_ioaddr + MTIP_PCS_VENDOR_PCS_MODE_OFFSET);

    // set PCS_VENDOR_VL_INTLVL marker_counter = 0
    marker_counter = 0x0;

    // set the vendor vl intvl register
    iowrite32(marker_counter,
              pcs_ioaddr + MTIP_PCS_VENDOR_VL_INTVL_OFFSET);
    return;
}

void mtip_pcs_update_active_fec(u32 link_index,
                                       enum mtip_port_config_enum port_config,
                                       u32  sfp_port_type) {

    u32 active_fec;
    u32 port_type;

    if(mtip_lookup_port_type_by_link_index(link_index, &port_type) < 0)
        return;

    switch (port_config) {
    case MTIP_PORT_CONFIG_1x100GBASE_R:
    case MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC_LL:
    case MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_1x100GBASE_R2:
    case MTIP_PORT_CONFIG_1x100GBASE_R2_RSFEC:
    case MTIP_PORT_CONFIG_1x100GBASE_R4_RSFEC:
    case MTIP_PORT_CONFIG_2x50GBASE_R:
    case MTIP_PORT_CONFIG_2x50GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_1x50GBASE_R:
    case MTIP_PORT_CONFIG_1x50GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_RSFEC:
    case MTIP_PORT_CONFIG_1x25GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_4x25GBASE_R_RSFEC:
        {
            active_fec = ETHTOOL_FEC_RS;
        }
        break;

    case MTIP_PORT_CONFIG_1x100GBASE_R4:
    case MTIP_PORT_CONFIG_1x50GBASE_R2:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_LUAI:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_LUAI_FEC:
    case MTIP_PORT_CONFIG_2x50GBASE_R2:
    case MTIP_PORT_CONFIG_2x50GBASE_R2_FEC:
    case MTIP_PORT_CONFIG_2x50GBASE_R2_LUAI:
    case MTIP_PORT_CONFIG_2x50GBASE_R2_LUAI_FEC:
    case MTIP_PORT_CONFIG_1x25GBASE_R:
    case MTIP_PORT_CONFIG_4x25GBASE_R:
    case MTIP_PORT_CONFIG_1x40GBASE_R4:
    case MTIP_PORT_CONFIG_4x10GBASE_R:
    case MTIP_PORT_CONFIG_1x10GBASE_R:
        {
            active_fec = ETHTOOL_FEC_OFF;
        }
        break;

    case MTIP_PORT_CONFIG_1x40GBASE_R4_FEC:
    case MTIP_PORT_CONFIG_4x25GBASE_R_FEC:
    case MTIP_PORT_CONFIG_1x25GBASE_R_FEC:
    case MTIP_PORT_CONFIG_4x10GBASE_R_FEC:
    case MTIP_PORT_CONFIG_1x10GBASE_R_FEC:
    default:
        {
            active_fec = ETHTOOL_FEC_BASER;
        }
        break;
    }

    CSMLOGINFO("Setting active FEC(4=OFF, 8=RS) to %d for link_index: %d",
               active_fec, link_index);

    platform_driver_priv->mtip_links[link_index]->active_fec = active_fec;

    return;
}

