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

#include "mtip_pcs.h"
#include "eth_phy_iface.h"

static void mtip_pcs_set_vendor_pcs_mode(struct mtip_link_device_info* link_device)
{
    enum eth_phy_iface_phy_lane_speed_enum  lane_speed = link_device->lane_speed;
    void __iomem *pcs_ioaddr = link_device->pcs_ioaddr;
    u32 vendor_pcs_mode = 0;

    switch (lane_speed) 
    {
    case PHY_LANE_SPEED_25G:
        {
            vendor_pcs_mode = MTIP_PCS_VENDOR_PCS_ENA_CLAUSE49_BIT | MTIP_PCS_VENDOR_PCS_DISABLE_MLD_BIT | MTIP_PCS_VENDOR_PCS_HI_BER25_BIT; 
        }
        break;
    case PHY_LANE_SPEED_10G:
    case PHY_LANE_SPEED_50G:
    case PHY_LANE_SPEED_100G:
    default:
        {
            CSMLOGINFO("Need settings for speed: %d\n", lane_speed);
        }
        break;
    }

    CSMLOGINFO("Setting VENDOR_PCS_MODE to: 0x%x\n", vendor_pcs_mode);

    // set the vendor pcs mode register
    iowrite32(vendor_pcs_mode,
              pcs_ioaddr + MTIP_PCS_VENDOR_PCS_MODE_OFFSET);

    // read the value
    vendor_pcs_mode = (u32)ioread32(pcs_ioaddr + MTIP_PCS_VENDOR_PCS_MODE_OFFSET);

    CSMLOGINFO("Read VENDOR_PCS_MODE: 0x%x\n", vendor_pcs_mode);

    return;
}

static void mtip_pcs_set_vendor_vl_intvl(struct mtip_link_device_info* link_device)
{
    enum eth_phy_iface_phy_lane_speed_enum  lane_speed = link_device->lane_speed;
    void __iomem *pcs_ioaddr = link_device->pcs_ioaddr;
    u32 marker_counter = 0;

    switch (lane_speed) 
    {
    case PHY_LANE_SPEED_25G:
        {
            marker_counter = 0x0; 
        }
        break;
    case PHY_LANE_SPEED_10G:
    case PHY_LANE_SPEED_50G:
    case PHY_LANE_SPEED_100G:
    default:
        {
            CSMLOGINFO("Need settings for speed: %d\n", lane_speed);
        }
        break;
    }

    // set the vendor vl intvl register
    iowrite32(marker_counter,
              pcs_ioaddr + MTIP_PCS_VENDOR_VL_INTVL_OFFSET);
    return;
}

static void mtip_pcs_set_vl_registers(struct mtip_link_device_info* link_device)
{
    int index = 0;
    enum eth_phy_iface_phy_lane_speed_enum  lane_speed = link_device->lane_speed;
    void __iomem *pcs_ioaddr = link_device->pcs_ioaddr;

    switch (lane_speed) 
    {
    case PHY_LANE_SPEED_25G:
        {
            // set the VL register
            iowrite32(MTIP_PCS_25GBPS_VL_0_0,
                      pcs_ioaddr + MTIP_PCS_VENDOR_VL0_0_OFFSET + index*MTIP_PCS_VENDOR_VLn_OFFSET);

            iowrite32(MTIP_PCS_25GBPS_VL_0_1,
                      pcs_ioaddr + MTIP_PCS_VENDOR_VL0_1_OFFSET + index*MTIP_PCS_VENDOR_VLn_OFFSET);

            ++index;

            iowrite32(MTIP_PCS_25GBPS_VL_1_0,
                      pcs_ioaddr + MTIP_PCS_VENDOR_VL0_0_OFFSET + index*MTIP_PCS_VENDOR_VLn_OFFSET);

            iowrite32(MTIP_PCS_25GBPS_VL_1_1,
                      pcs_ioaddr + MTIP_PCS_VENDOR_VL0_1_OFFSET + index*MTIP_PCS_VENDOR_VLn_OFFSET);

            ++index;

            iowrite32(MTIP_PCS_25GBPS_VL_2_0,
                      pcs_ioaddr + MTIP_PCS_VENDOR_VL0_0_OFFSET + index*MTIP_PCS_VENDOR_VLn_OFFSET);

            iowrite32(MTIP_PCS_25GBPS_VL_2_1,
                      pcs_ioaddr + MTIP_PCS_VENDOR_VL0_1_OFFSET + index*MTIP_PCS_VENDOR_VLn_OFFSET);

            ++index;

            iowrite32(MTIP_PCS_25GBPS_VL_3_0,
                      pcs_ioaddr + MTIP_PCS_VENDOR_VL0_0_OFFSET + index*MTIP_PCS_VENDOR_VLn_OFFSET);

            iowrite32(MTIP_PCS_25GBPS_VL_3_1,
                      pcs_ioaddr + MTIP_PCS_VENDOR_VL0_1_OFFSET + index*MTIP_PCS_VENDOR_VLn_OFFSET);

            ++index;
        }
        break;
    case PHY_LANE_SPEED_10G:
    case PHY_LANE_SPEED_50G:
    case PHY_LANE_SPEED_100G:
    default:
        {
            CSMLOGINFO("Need settings for speed: %d\n", lane_speed);
        }
        break;
    }
    return;
}

static void mtip_pcs_reset_all_vl_registers(struct mtip_link_device_info* link_device)
{
    int index = 0;
    void __iomem *pcs_ioaddr = link_device->pcs_ioaddr;

    CSMLOGINFO("Resetting all PCS VL registers\n");

    for (index = 0; index < 20; ++index) 
    {
        // reset the VL register
        iowrite32(0x0,
                  pcs_ioaddr + MTIP_PCS_VENDOR_VL0_0_OFFSET + index*MTIP_PCS_VENDOR_VLn_OFFSET);

        iowrite32(0x0,
                  pcs_ioaddr + MTIP_PCS_VENDOR_VL0_1_OFFSET + index*MTIP_PCS_VENDOR_VLn_OFFSET);

        CSMLOGINFO("done with index: %d\n", index);
    }
    return;
}


int mtip_pcs_config_pcs(u32 link_index)
{
    u32 port_device_index;
    u32 link_device_index;

    if (mtip_lookup_device_by_link_index(link_index, &port_device_index, &link_device_index) < 0)
    {
       CSMLOGERR("unable to find device for link %d", link_index);
       return -ENODEV;
    }

    // configure the PCS of the link
    CSMLOGINFO("Configuring the PCS for link_index: %d, port_device_index: %d, link_device_index: %d\n", link_index, port_device_index, link_device_index);

    // reset the vl registers
    mtip_pcs_reset_all_vl_registers(&platform_driver_priv->devices.port_devices[port_device_index].link_devices[link_device_index]);

    // program the vendor pcs mode register
    mtip_pcs_set_vendor_pcs_mode(&platform_driver_priv->devices.port_devices[port_device_index].link_devices[link_device_index]);

    // program the vendor vl intvl register
    mtip_pcs_set_vendor_vl_intvl(&platform_driver_priv->devices.port_devices[port_device_index].link_devices[link_device_index]);

    // program the vendor vl registers
    mtip_pcs_set_vl_registers(&platform_driver_priv->devices.port_devices[port_device_index].link_devices[link_device_index]);

    return 0;
}

int mtip_pcs_enable_loopback(u32 link_index)
{
    u32 port_device_index;
    u32 link_device_index;
    void __iomem *pcs_ioaddr;
    u32 pcs_control;

    if (mtip_lookup_device_by_link_index(link_index, &port_device_index, &link_device_index) < 0)
    {
        CSMLOGERR("Unable to find device for link index: %d\n", link_index);
        return -1;
    }

    // set the loopback bit in the PCS corresponding to the link
    pcs_ioaddr = platform_driver_priv->devices.port_devices[port_device_index].link_devices[link_device_index].pcs_ioaddr;

    // read the control register
    pcs_control = (u32)ioread32(pcs_ioaddr + MTIP_PCS_CONTROL_REG_OFFSET);

    // set the loopback bit in the PCS CONTROL register
    pcs_control |= MTIP_PCS_LOOPBACK_CONTROL_BIT;

    CSMLOGINFO("Setting PCS loopback on link index %d, pcs_control: 0x%x\n", link_index, pcs_control);

    // write to the register
    iowrite32(pcs_control,
              pcs_ioaddr + MTIP_PCS_CONTROL_REG_OFFSET);
    return 0;
}

int mtip_rsfec_initialize(struct mtip_port_device_info* port_device)
{
    int i;
    void __iomem* rsfec_base_addr = port_device->rsfec_base_addr;
    u32 rsfec_control_val = 0;

    CSMLOGINFO("Initializing RSFEC for port %d\n", port_device->port_type);

    for (i = 0; i < PHY_LANE_MAX; ++i) 
    {
        if (port_device->lane_config[i].lane_enabled)
        {
            // lane is enabled
            // program the RSFEC based on lane speed
            switch (port_device->lane_config[i].lane_speed) 
            {
            case PHY_LANE_SPEED_25G:
                {
                    rsfec_control_val = MTIP_RSFEC_CONTROL_TC_PAD_VALUE_BIT; 
                }
                break;
            case PHY_LANE_SPEED_10G:
            case PHY_LANE_SPEED_50G:
            case PHY_LANE_SPEED_100G:
            default:
                {
                    CSMLOGINFO("Need settings for speed: %d\n", port_device->lane_config[i].lane_speed);
                }
                break;
            }

            CSMLOGINFO("Setting RSFEC addr 0x%x to 0x%x\n", MTIP_RSFEC_CONTROL_OFFSET + i*MTIP_RSFEC_LINK_OFFSET, rsfec_control_val);

            // set the RSFEC control register
            iowrite32(rsfec_control_val,
                      rsfec_base_addr + MTIP_RSFEC_CONTROL_OFFSET + i*MTIP_RSFEC_LINK_OFFSET);

        }
    }

    return 0;
}


