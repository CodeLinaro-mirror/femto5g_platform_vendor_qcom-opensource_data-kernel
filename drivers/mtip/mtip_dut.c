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
#include <linux/of_net.h>

#include "mtip.h"
#include "mtip_device.h"
#include "mtip_dut.h"

extern int mtip_tx_delay[MTIP_MAX_LINKS];
extern int mtip_rx_delay[MTIP_MAX_LINKS];

int mtip_dut_get_tx_delay(int index)
{
    if (mtip_loopback_mode == MTIP_MODE_DEFAULT) 
    {
        if(index<0 || index>=MTIP_MAX_LINKS)
           return 0;

        if(mtip_tx_delay[index] != TX_DELAY_DEFAULT_VAL)
        {
           return mtip_tx_delay[index];
        }
        else
        {
           switch(index)
           {
              case 0:
                 return 0x14;
              case 1:
                 return 0x14;
              case 2:
                 return 0x10;
              case 3:
                 return 0x10;
               case 15:
                  return 0x10;
              default:
                 return 0;
           }
        }
    }
    else
    {
        return 0x10;
    }
}

int mtip_dut_get_rx_delay(int index)
{
   if(index<0 || index>=MTIP_MAX_LINKS)
      return 0;

   if(mtip_rx_delay[index] != RX_DELAY_DEFAULT_VAL)
   {
      return mtip_rx_delay[index];
   }
   else
   {
      switch(index)
      {
         case 0:
            return 0x01D0;
         case 1:
            return 0x01DE;
         case 2:
            return 0x00AC;
         case 3:
            return 0x0094;
         default:
            return 0;
      }
   }
}

void __iomem * mtip_dut_get_base_addr(u32 port_device_id)
{
    return platform_driver_priv->devices.port_devices[port_device_id].dut_base_addr;
}

/*
 * Reset the FH0 Emulation
 */
void mtip_dut_reset(void __iomem *addr) {
   CSMLOGINFO("DUT Reset\n");

   // Set emulation reset register value
   iowrite32(MTIP_MAC_FH0_EMULATION_RESET_VAL, addr + MTIP_MAC_FH0_EMULATION_RESET_REG);

   // Reset emulation reset register
   iowrite32(0, addr + MTIP_MAC_FH0_EMULATION_RESET_REG);

   CSMLOGINFO("DUT Reset complete\n");
}

void mtip_dut_rx_tx_delay_tuning(u32 link_index) {
   u32 port_device_index;
   u32 link_device_index;
   void __iomem            *dut_base_addr;
   int                      value = 0;
   bool                     flag = false;
   u32 real_link_number;

   // first look up the port and link device index
   if (mtip_lookup_device_by_link_index(link_index, &port_device_index, &link_device_index) < 0)
   {
      CSMLOGERR("unable to find device for link %d", link_index);
      return;
   }

   // get the base address of dut
   dut_base_addr = mtip_dut_get_base_addr(port_device_index);

   CSMLOGINFO("mtip_mac_rx_tx_delay_tuning for link %d", link_index);

   // get the real port and link number for the link index
   if (mtip_lookup_real_link_number_by_link_index(link_index, &real_link_number) < 0)
   {
       CSMLOGERR("unable to find real link numbers for link %d", link_index);
       return;
   }

   /* TX delay tuning*/
   //Write GE_DUT_EMACn_TX_ODDR_DELAY_CTL_REG[TXC_DELAYCNTVALIN] with Tx delay value
   value |= ((mtip_dut_get_tx_delay(link_index) << 
                                       MTIP_TXC_DELAY_CNT_VAL_IN_ADDR_SHIFT) & 
                                          MTIP_TXC_DELAY_CNT_VAL_IN_ADDR_MASK);
   iowrite32(value,
             (dut_base_addr +
              (real_link_number * MTIP_RGMII_IO_MACRO_CFG_REG_MAC_OFFSET) +
              MTIP_TX_DELAY_CTL_REG_OFFSET));

   CSMLOGINFO("mtip_mac_rx_tx_delay_tuning value %x", value);

   // Write GE_DUT_EMACn_TX_ODDR_DELAY_CTL_REG[TXC_DELAY_LD] as '1'
   value |= (1<<MTIP_TXC_DELAY_LD_ADDR_SHIFT);
   iowrite32(value,
             (dut_base_addr +
              (real_link_number * MTIP_RGMII_IO_MACRO_CFG_REG_MAC_OFFSET) +
              MTIP_TX_DELAY_CTL_REG_OFFSET));

   CSMLOGINFO("mtip_mac_rx_tx_delay_tuning value %x", value);

   // Write GE_DUT_EMACn_TX_ODDR_DELAY_CTL_REG[TXC_DELAY_LD] as '0'
   value &= (~(1<<MTIP_TXC_DELAY_LD_ADDR_SHIFT));
   iowrite32(value,
             (dut_base_addr +
              (real_link_number * MTIP_RGMII_IO_MACRO_CFG_REG_MAC_OFFSET) +
              MTIP_TX_DELAY_CTL_REG_OFFSET));

   CSMLOGINFO("mtip_mac_rx_tx_delay_tuning value %x", value);

   // Read GE_DUT_EMACn_TX_ODDR_DELAY_CTL_REG[TXC_DELAYCNTVALOUT] and wait until read as configured value
   while (flag == false) {
      mdelay(10);

      value = ioread32((dut_base_addr +
                        (real_link_number * MTIP_RGMII_IO_MACRO_CFG_REG_MAC_OFFSET) +
                       MTIP_TX_DELAY_CTL_REG_OFFSET));

      CSMLOGINFO("mtip_mac_rx_tx_delay_tuning value %x", value);

      if (((value & MTIP_TXC_DELAY_CNT_VAL_OUT_ADDR_MASK)  >>
                MTIP_TXC_DELAY_CNT_VAL_OUT_ADDR_SHIFT) == 
           mtip_dut_get_tx_delay(link_index)) {
         flag = true;
      }
   }

   CSMLOGINFO("mtip_mac_rx_tx_delay_tuning value %x", value);

   //Write GE_DUT_EMACn_TX_ODDR_DELAY_CTL_REG[TXD_DELAYCNTVALIN] as '0'
   value &= (~(MTIP_TXD_DELAY_CNT_VAL_IN_ADDR_MASK));
   iowrite32(value,
             (dut_base_addr +
              (real_link_number * MTIP_RGMII_IO_MACRO_CFG_REG_MAC_OFFSET) +
              MTIP_TX_DELAY_CTL_REG_OFFSET));

   CSMLOGINFO("mtip_mac_rx_tx_delay_tuning value %x", value);

   // Write GE_DUT_EMACn_TX_ODDR_DELAY_CTL_REG[TXD_DELAY_LD] as '1'
   value |= 1<<MTIP_TXD_DELAY_LD_ADDR_SHIFT;
   iowrite32(value,
             (dut_base_addr +
              (real_link_number * MTIP_RGMII_IO_MACRO_CFG_REG_MAC_OFFSET) +
              MTIP_TX_DELAY_CTL_REG_OFFSET));

   CSMLOGINFO("mtip_mac_rx_tx_delay_tuning value %x", value);

   // Write GE_DUT_EMACn_TX_ODDR_DELAY_CTL_REG[TXD_DELAY_LD] as '0'
   value &= (~(1<<MTIP_TXD_DELAY_LD_ADDR_SHIFT));
   iowrite32(value,
             (dut_base_addr +
              (real_link_number * MTIP_RGMII_IO_MACRO_CFG_REG_MAC_OFFSET) +
              MTIP_TX_DELAY_CTL_REG_OFFSET));

   CSMLOGINFO("mtip_mac_rx_tx_delay_tuning value %x", value);

   // Read GE_DUT_EMACn_TX_ODDR_DELAY_CTL_REG[TXD_DELAYCNTVALOUT] and wait until read as configured value
   flag = false;
   while (flag == false) {
      mdelay(10);

      value = ioread32((dut_base_addr +
                        (real_link_number * MTIP_RGMII_IO_MACRO_CFG_REG_MAC_OFFSET) +
                       MTIP_TX_DELAY_CTL_REG_OFFSET));

      CSMLOGINFO("mtip_mac_rx_tx_delay_tuning value %x", value);

      if (((value & MTIP_TXD_DELAY_CNT_VAL_OUT_ADDR_MASK)  >>
                MTIP_TXD_DELAY_CNT_VAL_OUT_ADDR_SHIFT) == 0) {
         flag = true;
      }
   }

   if (mtip_loopback_mode == MTIP_MODE_DEFAULT) 
   {
       CSMLOGINFO("mtip_mac_rx_tx_delay_tuning value %x", value);

       /* RX delay tuning */

       // Write GE_DUT_RXn_CLK_PS_MMCM_CONFIG[RESET] as '1'
       value = 1<<MTIP_RX_CLK_PS_MMCM_CFG_RESET_ADDR_SHIFT;
       iowrite32(value,
                 (dut_base_addr +
                  (real_link_number * MTIP_RX_CLK_PS_MMCM_MAC_OFFSET) +
                  MTIP_RX_CLK_PS_MMCM_CFG_REG_OFFSET));

       // sleep 100ms
       mdelay(100);

       CSMLOGINFO("mtip_mac_rx_tx_delay_tuning value %x", value);

       // Write GE_DUT_RXn_CLK_PS_MMCM_CONFIG[RESET] as '0'
       value = 0;
       iowrite32(value,
                 (dut_base_addr +
                  (real_link_number * MTIP_RX_CLK_PS_MMCM_MAC_OFFSET) +
                  MTIP_RX_CLK_PS_MMCM_CFG_REG_OFFSET));

       // sleep 5s
       mdelay(5000);

       CSMLOGINFO("mtip_mac_rx_tx_delay_tuning value %x", value);

       // Write GE_DUT_RXn_CLK_PS_MMCM_CONFIG[TAP] with Rx delay value
       value = 0;
       value |= (mtip_dut_get_rx_delay(link_index) & 
                                             MTIP_RX_CLK_PS_MMCM_CFG_TAP_ADDR_MASK);
       iowrite32(value,
                 (dut_base_addr +
                  (real_link_number * MTIP_RX_CLK_PS_MMCM_MAC_OFFSET) +
                  MTIP_RX_CLK_PS_MMCM_CFG_REG_OFFSET));

       CSMLOGINFO("mtip_mac_rx_tx_delay_tuning value %x", value);

       // sleep 7s
       mdelay(7000);
   }
   return;
}

void mtip_dut_enable_rgmii_loopback(u32 link_index) 
{
    u32 port_device_index;
    u32 link_device_index;
    void __iomem            *dut_base_addr;
    u32 real_link_number;

    if (mtip_loopback_mode != MTIP_MODE_DEFAULT) 
    {
       if (mtip_lookup_device_by_link_index(link_index, &port_device_index, &link_device_index) < 0)
       {
          CSMLOGERR("unable to find device for link %d", link_index);
          return;
       }

       dut_base_addr =  mtip_dut_get_base_addr(port_device_index);

       // look up the real port and link numbers
       if (mtip_lookup_real_link_number_by_link_index(link_index, &real_link_number) < 0)
       {
           CSMLOGERR("unable to find real port and link numbers for link %d", link_index);
           return;
       }

       CSMLOGINFO("mtip_mac_enable_rgmii_loopback for link %d", link_index);

       /* RGMII IO Macro Programming */
       iowrite32(MTIP_RGMII_IO_MACRO_CFG_VAL,
                 (dut_base_addr +
                  (real_link_number * MTIP_RGMII_IO_MACRO_CFG_REG_MAC_OFFSET) +
                  MTIP_RGMII_IO_MACRO_CFG_REG_OFFSET));

       /* setup IOMacro for loopback*/
       iowrite32(MTIP_RGMII_IO_MACRO_LOOPBACK_VAL,
                 (dut_base_addr +
                  (real_link_number * MTIP_RGMII_IO_MACRO_CFG_REG_MAC_OFFSET) +
                  MTIP_RGMII_IO_MACRO_CFG_REG_OFFSET));

       // set the Tx and Rx delay values for loopback
       mtip_dut_rx_tx_delay_tuning(link_index);
    }
}

void mtip_dut_iomacro_config(struct phylink_config *config,
                     unsigned int mode,
                     const struct phylink_link_state *state) {
   u32 port_device_index;
   u32 link_device_index;
   void __iomem            *dut_base_addr;
   u32 real_link_number;
   struct mtip_netdev_priv *priv = netdev_priv(to_net_dev(config->dev));
   u32 link_index = priv->link_index;

   if (mtip_lookup_device_by_link_index(link_index, &port_device_index, &link_device_index) < 0)
   {
      CSMLOGERR("unable to find device for link %d", link_index);
      return;
   }

   dut_base_addr =  mtip_dut_get_base_addr(port_device_index);

   // look up the real port and link numbers
   if (mtip_lookup_real_link_number_by_link_index(link_index, &real_link_number) < 0)
   {
       CSMLOGERR("unable to find real port and link numbers for link %d", link_index);
       return;
   }

   CSMLOGINFO("mtip_mac_config for MAC index %d", link_index);

   /* RGMII IO Macro Programming */
   iowrite32(MTIP_RGMII_IO_MACRO_CFG_VAL,
             (dut_base_addr +
              (real_link_number * MTIP_RGMII_IO_MACRO_CFG_REG_MAC_OFFSET) +
              MTIP_RGMII_IO_MACRO_CFG_REG_OFFSET));
   return;
}



