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

#include "mtip_mac.h"
#include "mtip.h"
#include "mtip_device.h"
#include "mtip_platform.h"
#include "mtip_dut.h"
#include "mtip_logging.h"
#include "mtip_ptp.h"
#include "mtip_workq.h"

static irqreturn_t mtip_mac_interrupt_handler(int irq, void *devptr) 
{
   struct mtip_port_device_info * portptr;
   u32 summary;
   u32 int_status;
   int i;
   u32 link_index;
   u64 timestamp;
   bool found = false;
   bool handled = false;

   CSMLOGINFO("Got an interrupt!\n");

   // check if this an interrupt that needs to be handled
   for (i = 0; i < platform_driver_priv->devices.num_port_phandles; ++i) 
   {
       if (devptr == (void *)&platform_driver_priv->devices.port_devices[i]) 
       {
           found = true;
           break;
       }
   }

   if (found == false) 
   {
       // no need to handle interrupt
       return IRQ_NONE;
   }

   // set the portptr
   portptr = (struct mtip_port_device_info *)devptr;

   CSMLOGINFO("Got an interrupt! on port type %d\n", portptr->port_type);

   // read the interrupt summary
   summary = mtip_mac_get_interrupt_summary(portptr);

   for (i = 0; i < MTIP_MAX_LINKS_PER_PORT; ++i)
   {
       if ((summary & 0x01) == 0x1)
       {
           CSMLOGINFO("Got an interrupt! on port type %d, link: %d\n", portptr->port_type, i);

           // the bit for link i is set
           // there is an interrupt pending
           mtip_lookup_link_index_by_real_port_and_link(&link_index, portptr->port_type, i);

           int_status = mtip_mac_get_interrupt_status(link_index);

           CSMLOGINFO("Interrupt status 0x%x for link: %d with link_index: %d\n", int_status, i, link_index);

           if ((int_status & MTIP_MAC_INTERRUPT_PTP_TX_INTR) != 0)
           {
               // there is a PTP interrupt pending
               timestamp = mtip_mac_read_timestamp(link_index);

               CSMLOGINFO("Tx Timestamp %d read for link: %d with link_index: %d\n", timestamp, i, link_index);

               // post a job to workqueue to process this timestamp
               post_mtip_process_timestamp(link_index, timestamp);

               // clear the interrupt
               mtip_mac_clear_interrupts(link_index, MTIP_MAC_INTERRUPT_PTP_TX_INTR);

               handled = true;
           }
           if ((int_status & MTIP_MAC_INTERRUPT_LINK_DOWN_INTR) != 0)
           {
               // got a link down interrupt for link index
               post_mtip_process_link_state(link_index, false);

               // clear the interrupt
               mtip_mac_clear_interrupts(link_index, MTIP_MAC_INTERRUPT_LINK_DOWN_INTR);

               handled = true;
           }
           if ((int_status & MTIP_MAC_INTERRUPT_LINK_UP_INTR) != 0) 
           {
               // got a link up interrupt for link index
               post_mtip_process_link_state(link_index, true);

               // clear the interrupt
               mtip_mac_clear_interrupts(link_index, MTIP_MAC_INTERRUPT_LINK_UP_INTR);

               handled = true;
           }

       }

       summary = summary >> 1;
   }

   if (handled == true) 
   {
       // set as handled
       return IRQ_HANDLED;
   }
   else
   {
       // set as not handled
       return IRQ_NONE;
   }
}

static int mtip_mac_read_version(struct mtip_netdev_priv *priv) {
   u32 read_val;
   u32 link_index = priv->link_index;

   CSMLOGINFO("Reading REVISION register for link index: %d\n", link_index);

   // read the value
   read_val = ioread32(priv->mac_ioaddr + MTIP_MAC_REVISION);

   CSMLOGINFO("MAC REVISION: 0x%x for link index: %d\n", read_val, link_index);
   return 0;
}

static int mtip_mac_test_scratch(struct mtip_netdev_priv *priv) {
    u32 read_val;
    u32 write_val = 0xAAAAAAAA;
    u32 link_index = priv->link_index;

    // read the current value of scratch
    read_val = ioread32(priv->mac_ioaddr + MTIP_MAC_SCRATCH);

    // write the value
    iowrite32(write_val, priv->mac_ioaddr + MTIP_MAC_SCRATCH);

    // read the value again
    read_val = ioread32(priv->mac_ioaddr + MTIP_MAC_SCRATCH);

    // check that the read and write values are the same
    if (read_val != write_val) {
       CSMLOGERR("link index: %d, Read val: %d, write val: %d mismatch\n", link_index, read_val, write_val);
       return -1;
    }

    CSMLOGINFO("scratch register test passed for link index: %d\n", link_index);
   return 0;
}

static void mtip_mac_reset_mac(struct mtip_netdev_priv *priv) {
   u32 read_val;
   u32 write_val = MTIP_MAC_RESET;
   int flag = 0;
   u32 link_index = priv->link_index;

   CSMLOGINFO("Reseting MAC for link index: %d\n", link_index);

   // reset the MAC
   iowrite32(write_val, priv->mac_ioaddr + MTIP_MAC_COMMAND_CONFIG);

   while (flag == 0) {
      // wait for reset to complete
      mdelay(MTIP_MAC_RESET_DELAY_MSECS);

      // read the value again
      read_val = ioread32(priv->mac_ioaddr + MTIP_MAC_COMMAND_CONFIG);

      // check that the reset bit has cleared
      if (read_val & 0x00001000) {
         flag = 0;
      } else {
         flag = 1;
      }
   }

   CSMLOGINFO("MAC Reset complete for link index: %d\n", link_index);
   return;
}

void mtip_mac_set_frame_length(struct mtip_netdev_priv *priv, u32 frame_length)
{
   u32 link_index = priv->link_index;

   iowrite32(frame_length, priv->mac_ioaddr + MTIP_MAC_FRM_LENGTH);
   CSMLOGINFO("Setting frame length to %d for link index: %d\n", frame_length, link_index);
}

u32 mtip_mac_get_frame_length(u32 port_number, u32 link_number)
{
    u32 frame_length;
    void __iomem *mac_ioaddr;

    // lookup the mac_ioadr for the port and link
    mac_ioaddr = platform_driver_priv->devices.port_devices[port_number].link_devices[link_number].mac_ioaddr;

    frame_length = ioread32(mac_ioaddr + MTIP_MAC_FRM_LENGTH);
    return frame_length;
}

void mtip_mac_set_mac_address(struct mtip_netdev_priv *priv,
                              struct sockaddr *saddr) {
   u32 lower = 0;
   u32 upper = 0;
   u32 link_index = priv->link_index;

   lower = (saddr->sa_data[0]) | (saddr->sa_data[1] << 8) | (saddr->sa_data[2] << 16) | (saddr->sa_data[3] << 24);

   upper = (saddr->sa_data[4]) | (saddr->sa_data[5] << 8);

   // write the lower bits
   iowrite32(lower, priv->mac_ioaddr + MTIP_MAC_MAC_ADDR_0);

   // write the upper bits
   iowrite32(upper, priv->mac_ioaddr + MTIP_MAC_MAC_ADDR_1);

   CSMLOGINFO("Set the MAC address for link index: %d to upper: 0x%x, lower: 0x%x\n", link_index, upper, lower);
}

void mtip_mac_get_mac_address_by_device(u32 port_device_index, u32 link_device_index, uint8_t sa_data[]) {
   u32 lower = 0;
   u32 upper = 0;
   void __iomem *mac_ioaddr;
   u32 link_index;

   mtip_lookup_link_index_by_device(&link_index, port_device_index, link_device_index);

   // lookup the mac_ioadr for the port and link
   mac_ioaddr = platform_driver_priv->devices.port_devices[port_device_index].link_devices[link_device_index].mac_ioaddr;

   // read the lower bits
   lower = ioread32(mac_ioaddr + MTIP_MAC_MAC_ADDR_0);

   // read the lower bits
   upper = ioread32(mac_ioaddr + MTIP_MAC_MAC_ADDR_1);

   // update the sa_addr->sa_data
   sa_data[0] = (lower) & 0xFF;
   sa_data[1] = (lower >> 8) & 0xFF;
   sa_data[2] = (lower >> 16) & 0xFF;
   sa_data[3] = (lower >> 24) & 0xFF;

   sa_data[4] = (upper) & 0xFF;
   sa_data[5] = (upper >> 8) & 0xFF;

   CSMLOGINFO("Retrieved the MAC address of link index: %d, upper: 0x%x, lower: 0x%x\n", link_index, upper, lower);
}

void mtip_mac_set_mac_address_by_device(u32 port_device_index, u32 link_device_index, uint8_t sa_data[]) 
{
    u32 lower = 0;
    u32 upper = 0;
    void __iomem *mac_ioaddr;
    u32 link_index;

    mtip_lookup_link_index_by_device(&link_index, port_device_index, link_device_index);

    // lookup the mac_ioadr for the port and link
    mac_ioaddr = platform_driver_priv->devices.port_devices[port_device_index].link_devices[link_device_index].mac_ioaddr;

    lower = (sa_data[0]) | (sa_data[1] << 8) | (sa_data[2] << 16) | (sa_data[3] << 24);

    upper = (sa_data[4]) | (sa_data[5] << 8);

    // write the lower bits
    iowrite32(lower, platform_driver_priv->devices.port_devices[port_device_index].link_devices[link_device_index].mac_ioaddr + MTIP_MAC_MAC_ADDR_0);

    // write the upper bits
    iowrite32(upper, platform_driver_priv->devices.port_devices[port_device_index].link_devices[link_device_index].mac_ioaddr + MTIP_MAC_MAC_ADDR_1);

    CSMLOGINFO("Set the MAC address for link index: %d to upper: 0x%x, lower: 0x%x\n", link_index, upper, lower);
}

int mtip_mac_set_promisc_mode(struct mtip_netdev_priv *priv, bool mode)
{
    u32 read_val;
    u32 write_val;
    u32 link_index = priv->link_index;
    int ret = 0;

    // read the current value of the command config register
    read_val = ioread32(priv->mac_ioaddr + MTIP_MAC_COMMAND_CONFIG);

    if (mode)
    {
        // we need to set promisc mode bit
        // first check if the bit is already set
        if ((read_val & MTIP_MAC_COMMAND_CONFIG_SET_PROMISC) == 0)
        {
            write_val = read_val | MTIP_MAC_COMMAND_CONFIG_SET_PROMISC;

            // write the value back to the CONFIG register
            iowrite32(write_val, priv->mac_ioaddr + MTIP_MAC_COMMAND_CONFIG);

            CSMLOGINFO("Set the promisc mode for link index: %d\n", link_index);
        }
        else
        {
            CSMLOGINFO("Promisc mode already set for link index: %d\n", link_index);

            ret = 1;
        }
    }
    else
    {
        // we need to reset promisc mode bit
        // first check if the bit is already reset
        if ((read_val & MTIP_MAC_COMMAND_CONFIG_SET_PROMISC) != 0)
        {
            write_val = read_val & ~(MTIP_MAC_COMMAND_CONFIG_SET_PROMISC);

            // write the value back to the CONFIG register
            iowrite32(write_val, priv->mac_ioaddr + MTIP_MAC_COMMAND_CONFIG);
            CSMLOGINFO("Reset the promisc mode for link index: %d\n", link_index);
        }
        else
        {
            CSMLOGINFO("Promisc mode already reset for link index: %d\n", link_index);

            ret = 1;
        }
    }
    return ret;
}

void mtip_mac_set_hashtable_entry(struct mtip_netdev_priv *priv, u8 entry_address, u8 val)
{
   u32 write_val = 0;
   u32 link_index = priv->link_index;

   // first set the bottom 6 bits for the address
   write_val = (u32)entry_address & 0x0000003F;

   if (val != 0)
   {
      // set the bit 8
      write_val |= 0x00000100;
   }

   // write the value back to the CONFIG register
   iowrite32(write_val, priv->mac_ioaddr + MTIP_MAC_HASHTABLE_LOAD);
   CSMLOGINFO("Setting hashtable of link index: %d, address: %d to %d\n", link_index, entry_address, write_val);
}

void mtip_mac_enable_tx_rx(u32 link_index)
{
    void __iomem *mac_ioaddr;
    struct net_device* dev = platform_driver_priv->mtip_links[link_index]->dev;
    struct mtip_netdev_priv* priv = netdev_priv(dev);
    u32 command_config;
     
    CSMLOGINFO("Enabling Tx and Rx on link_index: %d\n", link_index);

    // set the link state as up
    platform_driver_priv->mtip_links[link_index]->state = MTIP_LINK_STATE_UP;

    mac_ioaddr = priv->mac_ioaddr;

    command_config = (u32)ioread32(mac_ioaddr + MTIP_MAC_COMMAND_CONFIG);

    command_config |= (MTIP_MAC_COMMAND_CONFIG_ENABLE_TX | MTIP_MAC_COMMAND_CONFIG_ENABLE_RX);

   // configure the mac for operation
   iowrite32(command_config, mac_ioaddr + MTIP_MAC_COMMAND_CONFIG);
}

void mtip_mac_disable_tx_rx(u32 link_index)
{
    void __iomem *mac_ioaddr;
    struct net_device* dev = platform_driver_priv->mtip_links[link_index]->dev;
    struct mtip_netdev_priv* priv = netdev_priv(dev);
    u32 command_config;
     
    CSMLOGINFO("Disabling Tx and Rx on link_index: %d\n", link_index);

    // set link state as down
    platform_driver_priv->mtip_links[link_index]->state = MTIP_LINK_STATE_DOWN;

    mac_ioaddr = priv->mac_ioaddr;

    command_config = (u32)ioread32(mac_ioaddr + MTIP_MAC_COMMAND_CONFIG);

    command_config &= (~(MTIP_MAC_COMMAND_CONFIG_ENABLE_TX | MTIP_MAC_COMMAND_CONFIG_ENABLE_RX));

   // configure the mac for operation
   iowrite32(command_config, mac_ioaddr + MTIP_MAC_COMMAND_CONFIG);
}

/*
1.	Provide a soft reset to the MAC core by doing the following steps.
a.	Write to the register MAC0_COMMAND_CONFIG with vaue 0x1800.
After the soft reset we need to initialize the  MAC by following steps 2 to 10.
2.	Program the MAC0_COMMAND_CONFIG with value 0x2813.
3.	Program MAC0_FRM_LENGTH register with the required frame length.
4.	Program MAC0_RX_FIFO_SECTIONS with 0x0001
5.	Program MAC0_TX_FIFO_SECTIONS with value 0x0004
6.	Program MAC0_HASHTABLE_LOAD with 0x0
7.	Program MAC0_TX_IPG_LENGTH with value 0xC.
8.	Program MAC0_CRC_MODE register with value 0x0.
9.	Program MAC0_CRC_INV_MASK with value 0xFFFFFFFF.
10.	Program MAC0_XIF_MODE register.
*/
void mtip_mac_initialize(struct mtip_netdev_priv *priv)
{
    u32 link_index = priv->link_index;

   CSMLOGINFO("Initializing the MAC for link index: %d\n", link_index);

   // read the version info and print it
   mtip_mac_read_version(priv);

   // check the scratch memory write and read
   mtip_mac_test_scratch(priv);

   // reset the MAC
   mtip_mac_reset_mac(priv);

   // configure the mac for operation
   iowrite32(MTIP_MAC_INIT_COMMAND_CONFIG, priv->mac_ioaddr + MTIP_MAC_COMMAND_CONFIG);

   if (mtip_loopback_mode != MTIP_MODE_DEFAULT)
   {
       post_mtip_process_link_state(link_index, true);
   }

   // set the initial frame length
   mtip_mac_set_frame_length(priv, MTIP_MAC_INIT_FRAME_LENGTH);

   // configure the RX and TX FIFO sections
   iowrite32(MTIP_MAC_INIT_RX_FIFO_SECTIONS, priv->mac_ioaddr + MTIP_MAC_RX_FIFO_SECTIONS);

   iowrite32(MTIP_MAC_INIT_TX_FIFO_SECTIONS, priv->mac_ioaddr + MTIP_MAC_TX_FIFO_SECTIONS);

   // set the HASH TABLE LOAD
   iowrite32(MTIP_MAC_INIT_HASHTABLE_LOAD, priv->mac_ioaddr + MTIP_MAC_HASHTABLE_LOAD);

   // set the IPG
   iowrite32(MTIP_MAC_INIT_TX_IPG_LENGTH, priv->mac_ioaddr + MTIP_MAC_TX_IPG_LENGTH);

   // set the CRC mode
   iowrite32(MTIP_MAC_INIT_CRC_MODE, priv->mac_ioaddr + MTIP_MAC_CRC_MODE);

   // set the CRC INV MASK
   iowrite32(MTIP_MAC_INIT_CRC_INV_MASK, priv->mac_ioaddr + MTIP_MAC_CRC_INV_MASK);

   // set the XIF mode: TBD
   iowrite32(MTIP_MAC_INIT_XIF_MODE, priv->mac_ioaddr + MTIP_MAC_XIF_MODE);

   CSMLOGINFO("MAC Init complete\n");
}

void mtip_mac_finalize(void __iomem *mac_base_addr, unsigned int irq, const char *name, void *devptr) {
   // reset the MTIP hardware

    // disable the irq wake
    disable_irq_wake(irq);
    free_irq(irq, devptr);
}

void mtip_mac_phy_validate(struct phylink_config *config,
                           unsigned long *supported,
                           struct phylink_link_state *state) {
   __ETHTOOL_DECLARE_LINK_MODE_MASK(mac_supported) = { 0, };
   __ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = { 0, };

   phylink_set(mac_supported, 10baseT_Full);
   phylink_set(mac_supported, 100baseT_Full);
   phylink_set(mac_supported, 1000baseT_Full);
   phylink_set(mac_supported, 1000baseKX_Full);

   phylink_set(mac_supported, Autoneg);
   phylink_set(mac_supported, Pause);
   phylink_set(mac_supported, Asym_Pause);
   phylink_set_port_modes(mac_supported);

   bitmap_and(supported, supported, mac_supported,
              __ETHTOOL_LINK_MODE_MASK_NBITS);
   bitmap_andnot(supported, supported, mask,
                 __ETHTOOL_LINK_MODE_MASK_NBITS);
   bitmap_and(state->advertising, state->advertising, mac_supported,
              __ETHTOOL_LINK_MODE_MASK_NBITS);
   bitmap_andnot(state->advertising, state->advertising, mask,
                 __ETHTOOL_LINK_MODE_MASK_NBITS);

   return;
}

static u32 mtip_mac_wrapper_calendar_cfg_val(struct mtip_port_device_info* port_device)
{
    u32 cfg_val = 0;
    int j;
    u32 link_index;
    u32 real_link_number;
    u32 pattern = 0x00000001;

// for now only symmetric configurations are supported
// the weights are set to 000
    for (j = 0; j < port_device->num_link_phandles; ++j)
    {
        link_index = port_device->link_devices[j].link_index;

        mtip_lookup_real_link_number_by_link_index(link_index, &real_link_number);

        cfg_val |= (pattern << (4*real_link_number));
    }

    CSMLOGINFO("Setting calendar config of port %d to 0x%x\n", port_device->port_type, cfg_val);

    return cfg_val;
}

void mtip_mac_wrapper_pcs_mode_control(struct mtip_port_device_info* port_device)
{
    int i;
    u32 num_lanes;
    int j;
    enum eth_phy_iface_phy_lane_speed_enum lane_speed;
    u32 lane;
    u32 csr_cfg = 0;
    u32 pcs_mode_set = 0;
    u32 serdes_mux_cfg = 0;
    void __iomem* wrapper_base_addr = port_device->wrapper_base_addr;

    for (i = 0; i < port_device->num_link_phandles; ++i) 
    {
        num_lanes = port_device->link_devices[i].num_lanes;
        lane_speed = port_device->link_devices[i].lane_speed;
        
        for (j = 0; j < num_lanes; ++j)
        {
            lane = port_device->link_devices[j].lanes[j];

            // configure the lane based on the speed
            switch (lane_speed)
            {
            case PHY_LANE_SPEED_25G:
                {
                    // this needs a proper fix
                    pcs_mode_set = 0x0000;
                    csr_cfg = 0x3C00;
                    serdes_mux_cfg = 0x400;
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
        }
    }

    CSMLOGINFO("Setting CSR: 0%x, PCS Mode: 0x%x, MUX CFG: 0x%x\n", csr_cfg, pcs_mode_set, serdes_mux_cfg);

    // set the mac wrapper csr cfg
    iowrite32(csr_cfg,
              wrapper_base_addr + MTIP_MAC_WRAPPER_CSR_CONFIG_OFFSET);

    // set the mac wrapper pcs mode set
    iowrite32(pcs_mode_set,
              wrapper_base_addr + MTIP_MAC_WRAPPER_PCS_MODE_SET_OFFSET);

    // set the serdes mux cfg register
    iowrite32(serdes_mux_cfg,
              wrapper_base_addr + MTIP_MAC_WRAPPER_SERDES_MUX_CFG_OFFSET);

    return;
}

/*
 * MAC Wrapper Init
 */
void mtip_mac_wrapper_init(struct mtip_port_device_info* port_device)
{
    void __iomem *wrapper_base_addr;
    u32 calendar_cfg_val;

    wrapper_base_addr = port_device->wrapper_base_addr;

   CSMLOGINFO("MAC Wrapper Init\n");

   calendar_cfg_val = mtip_mac_wrapper_calendar_cfg_val(port_device);

   // Enable MAC instances with calendar config register
   iowrite32(calendar_cfg_val,
             wrapper_base_addr + MTIP_MAC_WRAPPER_CALENDAR_CFG_REG_OFFSET);

   // Configure TX AMF value
   iowrite32(MTIP_MAC_WRAPPER_TX_AMF_CFG_REG_VAL,
             wrapper_base_addr + MTIP_MAC_WRAPPER_TX_AMF_CFG_REG_OFFSET);

   // set the TSC_OFFSET REG
   iowrite32(MTIP_MAC_WRAPPER_TSC_OFFSET_REG_VAL,
             wrapper_base_addr + MTIP_MAC_WRAPPER_TSC_OFFSET_REG_OFFSET);

   // enable the Global timer
   iowrite32(MTIP_MAC_WRAPPER_GLOBAL_TIMER_EN_REG_VAL,
             wrapper_base_addr + MTIP_MAC_WRAPPER_GLOBAL_TIMER_EN_REG_OFFSET);

   return;
}

void mtip_mac_wrapper_register_irq(struct device *dev, unsigned int irq,
                              const char* dev_name, void* devptr)
{
   int irqret;

   CSMLOGINFO("Registering IRQ %d, %s for MAC Wrapper\n", irq, dev_name);

   irqret = devm_request_irq(dev, irq, (irq_handler_t)mtip_mac_interrupt_handler, IRQF_SHARED | IRQF_TRIGGER_RISING, dev_name, devptr);
   if (irqret) {
       CSMLOGERR("failed to register IRQ handler irq=%d\n", irq);
       return;
   }
   CSMLOGINFO("IRQ handler irq=%d registered\n", irq);

   irqret = enable_irq_wake(irq);
   if (irqret)
       CSMLOGERR("fail to enable IRQ wakeup irq=%d res=%d\n", irq, irqret);
   else
       CSMLOGINFO("IRQ wakeup enabled irq=%d\n", irq);

   CSMLOGINFO("MAC Wrapper IRQ register done\n");
}

void mtip_mac_set_interrupt_mask(u32 link_index)
{
    u32 write_val = 0;
    void __iomem *wrapper_base_addr;
    u32 port_device_index;
    u32 link_device_index;
    u32 real_link_number;

    mtip_lookup_device_by_link_index(link_index, &port_device_index, &link_device_index);

    mtip_lookup_real_link_number_by_link_index(link_index, &real_link_number);

    wrapper_base_addr = platform_driver_priv->devices.port_devices[port_device_index].wrapper_base_addr;

    // set the interrupts we are interested in
    write_val |= (MTIP_MAC_INTERRUPT_PTP_TX_INTR | MTIP_MAC_INTERRUPT_LINK_DOWN_INTR | MTIP_MAC_INTERRUPT_LINK_UP_INTR);

    CSMLOGINFO("Setting mask: 0x%x to register 0x%x with real_link_number %d link_index %d\n", write_val, 
               real_link_number*MTIP_MAC_WRAPPER_INTERRUPT_OFFSET + MTIP_MAC_WRAPPER_INTERRUPT_MASK_REG_OFFSET, real_link_number, link_index);

    // Enable MAC interrupt
    iowrite32(write_val,
              wrapper_base_addr + real_link_number*MTIP_MAC_WRAPPER_INTERRUPT_OFFSET + MTIP_MAC_WRAPPER_INTERRUPT_MASK_REG_OFFSET);
    return;
}

u64 mtip_mac_read_timestamp(u32 link_index)
{
    u32 read_val1 = 0;
    u32 read_val0 = 0;
    void __iomem *wrapper_base_addr;
    u32 port_device_index;
    u32 link_device_index;
    u32 real_link_number;
    u64 timestamp;

    mtip_lookup_device_by_link_index(link_index, &port_device_index, &link_device_index);

    mtip_lookup_real_link_number_by_link_index(link_index, &real_link_number);

    wrapper_base_addr = platform_driver_priv->devices.port_devices[port_device_index].wrapper_base_addr;

    // read the upper 32 bits
    read_val1 = (u32)ioread32(wrapper_base_addr + real_link_number*MTIP_MAC_WRAPPER_TX_TS_REG_OFFSET + MTIP_MAC_WRAPPER_TX_TS1_REG_BASE_OFFSET);

    // read the lower 32 bits
    read_val0 = (u32)ioread32(wrapper_base_addr + real_link_number*MTIP_MAC_WRAPPER_TX_TS_REG_OFFSET + MTIP_MAC_WRAPPER_TX_TS0_REG_BASE_OFFSET);

    // check this. Is read_val1 the significant bits?
    timestamp = ((u64)read_val0 | ((u64)read_val1 << 32));

    return timestamp;
}

u32 mtip_mac_get_interrupt_mask(u32 link_index)
{
    u32 read_val = 0;
    void __iomem *wrapper_base_addr;
    u32 port_device_index;
    u32 link_device_index;
    u32 real_link_number;

    mtip_lookup_device_by_link_index(link_index, &port_device_index, &link_device_index);

    mtip_lookup_real_link_number_by_link_index(link_index, &real_link_number);

    wrapper_base_addr = platform_driver_priv->devices.port_devices[port_device_index].wrapper_base_addr;

    read_val = (u32)ioread32(wrapper_base_addr + real_link_number*MTIP_MAC_WRAPPER_INTERRUPT_OFFSET + MTIP_MAC_WRAPPER_INTERRUPT_MASK_REG_OFFSET);
    return read_val;
}

u32 mtip_mac_get_interrupt_summary(struct mtip_port_device_info* port_device)
{
    u32 read_val = 0;
    void __iomem *wrapper_base_addr;

    wrapper_base_addr = port_device->wrapper_base_addr;

    read_val = (u32)ioread32(wrapper_base_addr + MTIP_MAC_WRAPPER_INTERRUPT_SUMMARY_REG_OFFSET);
    return read_val;
}

u32 mtip_mac_get_interrupt_status(u32 link_index)
{
    u32 read_val = 0;
    void __iomem *wrapper_base_addr;
    u32 port_device_index;
    u32 link_device_index;
    u32 real_link_number;

    mtip_lookup_device_by_link_index(link_index, &port_device_index, &link_device_index);

    mtip_lookup_real_link_number_by_link_index(link_index, &real_link_number);

    wrapper_base_addr = platform_driver_priv->devices.port_devices[port_device_index].wrapper_base_addr;

    read_val = (u32)ioread32(wrapper_base_addr + real_link_number*MTIP_MAC_WRAPPER_INTERRUPT_OFFSET + MTIP_MAC_WRAPPER_INTERRUPT_STAT_REG_OFFSET);
    return read_val;
}

void mtip_mac_clear_interrupts(u32 link_index, u32 int_to_clear)
{
    u32 write_val = int_to_clear;
    void __iomem *wrapper_base_addr;
    u32 port_device_index;
    u32 link_device_index;
    u32 real_link_number;

    mtip_lookup_device_by_link_index(link_index, &port_device_index, &link_device_index);

    mtip_lookup_real_link_number_by_link_index(link_index, &real_link_number);

    wrapper_base_addr = platform_driver_priv->devices.port_devices[port_device_index].wrapper_base_addr;

    // clear all interrupts
    iowrite32(write_val,
              wrapper_base_addr + real_link_number*MTIP_MAC_WRAPPER_INTERRUPT_OFFSET + MTIP_MAC_WRAPPER_INTERRUPT_CLR_REG_OFFSET);
    return;
}

