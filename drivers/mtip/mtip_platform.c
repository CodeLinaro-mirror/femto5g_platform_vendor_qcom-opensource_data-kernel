//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
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
#include <linux/clk.h>

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
#include <linux/of.h>

#include "mtip_platform.h"
#include "mtip_dma.h"
#include "mtip.h"
#include "mtip_device.h"
#include "mtip_mac.h"
#include "mtip_mdio.h"
#include "mtip_hashmap.h"
#include "mtip_client.h"
#include "mtip_ptp.h"
#include "mtip_sysfs.h"
#include "mtip_pcs.h"
#include "mtip_phy.h"
#include "mtip_dut.h"
#include "mtip_clocks.h"
#include "mtip_ethtool.h"

static int mtip_platform_setup(void);

/*
 * mtip_platform_setup_link: allocate memory for the link and connect to the dma
 */
static int mtip_platform_setup_link(unsigned int port_device_index, unsigned int link_device_index)
{
   ecpri_dma_eth_conn_hdl_t hdl;
   int rv = 0;
   u32 link_index;

   // get the link index using port number and link number
   link_index = platform_driver_priv->devices.port_devices[port_device_index].link_devices[link_device_index].link_index;

   if (platform_driver_priv->mtip_links[link_index] != NULL)
   {
       CSMLOGERR("Link index %d is already in use!\n", link_index);
       return -1;
   }

   platform_driver_priv->mtip_links[link_index] = (struct mtip_link_info*)kmalloc(sizeof(struct mtip_link_info), GFP_KERNEL);

   // HANDLE THE ERROR
   if (platform_driver_priv->mtip_links[link_index] == NULL)
   {
      CSMLOGERR("failed to allocated memory for mtip_links[%d]\n", link_index);
      rv = -ENOMEM;
      goto out;
   }

   memset(platform_driver_priv->mtip_links[link_index], 0, sizeof(struct mtip_link_info));

   // set the port and link number to access the link device
   platform_driver_priv->mtip_links[link_index]->port_device_index = port_device_index;
   platform_driver_priv->mtip_links[link_index]->link_device_index = link_device_index;

   platform_driver_priv->mtip_links[link_index]->ptp_ts_enabled = false;

   // initialize the PTP lists for the link index
   mtip_ptp_initialize(link_index);
   mtip_dma_tx_comp_list_initialize(link_index);

   // set the link state to INIT
   platform_driver_priv->mtip_links[link_index]->state = MTIP_LINK_STATE_INIT;

   if(link_index != MTIP_DEBUG_ETH_LINK_INDEX){
      // connect to the dma pipe
      rv = mtip_connect_dma_pipe(link_index, &hdl);

      // HANDLE THE ERROR
      if (rv < 0)
      {
         CSMLOGERR("dma connect pipe failed for link_index: %d\n", link_index);
         goto cleanup;
      }

      // set the hdl of the link
      platform_driver_priv->mtip_links[link_index]->dma_hdl = hdl;

      // add to hashmap
      mtip_hashmap_insert(hdl, link_index);

      CSMLOGDBG("connect_dma_pipe is complete with hdl: %d for link_index: %d\n", hdl, link_index);
   }

   goto out;

cleanup:
   kfree(platform_driver_priv->mtip_links[link_index]);
   platform_driver_priv->mtip_links[link_index] = NULL;

out:
   return rv;
}

static int mtip_platform_cleanup_link(unsigned int link_index)
{
   if (platform_driver_priv->mtip_links[link_index] != NULL) 
   {
      if(platform_driver_priv->mtip_links[link_index]->dma_hdl != 0)
      {
         // disconnect the pipes
         mtip_disconnect_dma_pipe(platform_driver_priv->mtip_links[link_index]->dma_hdl);

         // remove from hashmap
         mtip_hashmap_remove(platform_driver_priv->mtip_links[link_index]->dma_hdl);

         // reset the hdl of the link
         platform_driver_priv->mtip_links[link_index]->dma_hdl = 0;
      }

      kfree(platform_driver_priv->mtip_links[link_index]);

      platform_driver_priv->mtip_links[link_index] = NULL;
   }
   return 0;
}

static void mtip_platform_cleanup_ports(void) {
   int i;

   CSMLOGINFO("cleaning up %d ports\n", MTIP_MAX_PORTS);

   for (i = 0; i < MTIP_MAX_PORTS; ++i) 
   {
       if (platform_driver_priv->mtip_ports[i] != NULL) 
       {
           mtip_phy_destroy_phylink(i);
       }
   }
}

int mtip_link_probe(struct platform_device *pdev) 
{
    int ret = 0;
    int 			result = 0;
    int i, j;
    struct mtip_link_device_info link_device;
    struct resource *resource;
    unsigned long flags;
    spinlock_t *lock = &platform_driver_priv->driver_lock;
    bool link_found = false;
    u32 port_index;
    u32 link_index;
    bool all_probes_complete = false;
    const char* linkname;
    u32 lane_entries;
    u32 lane;
    u32 lane_speed;

    CSMLOGDBG("mtip_link_probe called of device \"%s\"\n", pdev->name);

    link_device.link_pdev = pdev;
    link_device.link_phandle = pdev->dev.of_node->phandle;

    CSMLOGDBG("phandle of the link device: %d\n", link_device.link_phandle);

    /* Get the link index */
    result	= of_property_read_u32(pdev->dev.of_node, "qcom,mac-link-index", &link_device.link_index);

    if (result < 0) {
        CSMLOGERR(":get resource failed for qcom,mac-link-index\n");
        return ret;
    }

    CSMLOGDBG("qcom,mac-link-index is %d\n", link_device.link_index);

    /* Get the name */
    result = of_property_read_string(pdev->dev.of_node,"qcom,mac-link-name", &linkname);

    if (result < 0) {
        CSMLOGERR(":get resource failed for reg-names\n");
        return ret;
    }

    link_device.link_name = linkname;
    CSMLOGDBG("link name is %s\n", link_device.link_name);

    // get the mac link base address
   resource = platform_get_resource_byname(pdev, IORESOURCE_MEM, "mac");
   if (!resource) {
       CSMLOGERR(":get resource failed for mac\n");
       return -ENODEV;
   }
   CSMLOGDBG("index: %d, link base = 0x%x, link size = 0x%x\n", link_device.link_index, resource->start, resource_size(resource));

   // set the MAC base address
   link_device.mac_ioaddr = devm_ioremap_resource(&pdev->dev, resource);

   if (mtip_rumi_platform == 0) 
   {
       // get the pcs link base address
       resource = platform_get_resource_byname(pdev, IORESOURCE_MEM, "pcs");
       if (!resource) {
           CSMLOGERR(":get resource failed for pcs\n");
           return -ENODEV;
       }
       CSMLOGDBG("index: %d, link base = 0x%x, link size = 0x%x\n", link_device.link_index, resource->start, resource_size(resource));

       // set the base address
       link_device.pcs_ioaddr = devm_ioremap_resource(&pdev->dev, resource);
   }

   // read the lane-speed to use
   result	= of_property_read_u32(pdev->dev.of_node, "qcom,lane-speed", &lane_speed);

   if (result < 0) {
       CSMLOGERR(":get resource failed for qcom,lane-speed\n");
       return ret;
   }

   if (lane_speed >= PHY_LANE_SPEED_MAX) {
       CSMLOGERR("lane_speed = %d is invalid\n", lane_speed);
       return -ENODEV;
   }

   link_device.lane_speed = lane_speed;

   CSMLOGDBG("qcom,lane-speed is %d\n", link_device.lane_speed);

   // get the number of lanes
   if (!of_get_property(pdev->dev.of_node, "qcom,lane-numbers", &lane_entries))
   {
       CSMLOGERR("Unable to read lane assignment\n");
       return -ENODEV;
   }

   link_device.num_lanes = lane_entries / (sizeof(u32));

   CSMLOGDBG("Number of lanes assigned is: %d\n", link_device.num_lanes);

   if ((link_device.num_lanes == 0) || (link_device.num_lanes > PHY_LANE_MAX))
   {
       CSMLOGERR("Error in the number of lanes: %d\n", link_device.num_lanes);
       return -ENODEV;
   }

   for (i = 0; i < link_device.num_lanes; ++i) 
   {
       if (of_property_read_u32_index(pdev->dev.of_node, "qcom,lane-numbers", i, &lane) >= 0)
       {
           CSMLOGDBG("Lane: %d assigned to link\n", lane);
           link_device.lanes[i] = lane;
       }
       else
       {
           CSMLOGERR("Failed to find lane for index: %d", i);
           return -ENODEV;
       }
   }

   // the DT entries have been processed
   spin_lock_irqsave(lock, flags);

   link_found = false;

   // loop thru all ports and look for phandle in its links
   for (i = 0; i < platform_driver_priv->devices.num_port_phandles; ++i)
   {
       for (j = 0; j < platform_driver_priv->devices.port_devices[i].num_link_phandles; ++j)
       {
           if (link_device.link_phandle == platform_driver_priv->devices.port_devices[i].link_phandles[j])
           {
               port_index = i;
               link_index = j;
               link_found = true;
               CSMLOGDBG("Found link_phandle %d in port device %d at index: %d\n", link_device.link_phandle, i, j);
               break;
           }
       }
   }

   if (link_found)
   {
       CSMLOGDBG("Updating index: %d, %d with link information\n", port_index, link_index);

       // set the link device at the found indices
       memcpy(&platform_driver_priv->devices.port_devices[port_index].link_devices[link_index], &link_device, sizeof(struct mtip_link_device_info));

       ++platform_driver_priv->devices.port_devices[port_index].num_link_phandles_probed;

       all_probes_complete = true;

       // go through all ports and check if all ports probed
       for (i = 0; i < platform_driver_priv->devices.num_port_phandles; ++i)
       {
           if (platform_driver_priv->devices.port_devices[i].num_link_phandles_probed < 
                   platform_driver_priv->devices.port_devices[i].num_link_phandles)
           {
               all_probes_complete = false;
               break;
           }
       }
   }
   else
   {
       CSMLOGERR("Did not find %d handle in any port device: ignoring\n", link_device.link_phandle);
       ret = -ENODEV;
   }

   spin_unlock_irqrestore(lock, flags);

   if (all_probes_complete)
   {
       CSMLOGINFO("All device probes have been received\n");

       // setup the netdevs now
       ret = mtip_platform_setup();
   }
   else
   {
       CSMLOGDBG("Still waiting for all probes to complete\n");
       ret = 0;
   }
    CSMLOGDBG("done with processing link device: %lx", (unsigned long) pdev);
    return ret;
}

int mtip_port_probe(struct platform_device *pdev) 
{
    int ret = 0;
    int i;
    int 			result = 0;
    u32             phandle;
    struct mtip_port_device_info port_device;
    struct resource *wrapper_resource;
    struct resource *irq_resource;
    int             link_entries;
    unsigned long flags;
    spinlock_t *lock = &platform_driver_priv->driver_lock;
    bool index_found = false;
    bool all_ports_probed = false;
    struct resource dev_resource;
    u32             dut_base_regs[2];
    u32             sfp_phandle;

    CSMLOGDBG("mtip_port_probe called of device \"%s\"\n", pdev->name);

    port_device.port_pdev = pdev;
    
    port_device.port_phandle = pdev->dev.of_node->phandle;
    CSMLOGDBG("phandle of the port device: %d\n", port_device.port_phandle);

    /* Get the port type */
    result = of_property_read_u32(pdev->dev.of_node, "qcom,port-type", &port_device.port_type);

    if (result < 0) {
        CSMLOGERR(":get resource failed for port-type\n");
        return -ENODEV;
    }

   CSMLOGDBG("port type is %d\n", port_device.port_type);

   // mac wrapper base address
   wrapper_resource = platform_get_resource_byname(pdev, IORESOURCE_MEM, "mac-wrapper");
   if (!wrapper_resource) {
       CSMLOGERR(":get resource failed for mac-wrapper\n");
       return -ENODEV;
   }
   CSMLOGDBG("port type: %d, port base = 0x%x, port size = 0x%x\n", port_device.port_type, wrapper_resource->start, resource_size(wrapper_resource));

   // set the base address
   port_device.wrapper_base_addr = devm_ioremap_resource(&pdev->dev, wrapper_resource);
   
   // macstats base address
   wrapper_resource = platform_get_resource_byname(pdev, IORESOURCE_MEM, "macstats");
   if (!wrapper_resource) {
       CSMLOGERR(":get resource failed for macstats\n");
       return -ENODEV;
   }
   CSMLOGDBG("port type: %d, port base = 0x%x, port size = 0x%x\n", port_device.port_type, wrapper_resource->start, resource_size(wrapper_resource));

   // set the base address
   port_device.macstats_base_addr = devm_ioremap_resource(&pdev->dev, wrapper_resource);
   
   if (mtip_rumi_platform == 0) 
   {
       // rsfec base address
       wrapper_resource = platform_get_resource_byname(pdev, IORESOURCE_MEM, "rsfec");
       if (!wrapper_resource) {
           CSMLOGERR(":get resource failed for rsfec\n");
           return -ENODEV;
       }
       CSMLOGDBG("port type: %d, port base = 0x%x, port size = 0x%x\n", port_device.port_type, wrapper_resource->start, resource_size(wrapper_resource));

       // set the base address
       port_device.rsfec_base_addr = devm_ioremap_resource(&pdev->dev, wrapper_resource);
   }

   // get the irq resource
   irq_resource = platform_get_resource_byname(pdev, IORESOURCE_IRQ, "pcs-mac-irq");
   if (!irq_resource) {
       CSMLOGERR(":get resource failed for irq 0\n");
       return -ENODEV;
   }
   CSMLOGDBG("port type: %d, :irq = %d\n", port_device.port_type, irq_resource->start);

   // set the irq
   port_device.wrapper_irq = irq_resource->start;

   if (mtip_rumi_platform != 0) 
   {
       // read the dut_base_regs
       ret = of_property_read_u32_array(pdev->dev.of_node, "qcom,dut-base-reg", dut_base_regs, 2);
       if (ret < 0) {
           CSMLOGERR("dut_base_regs[0] : %x, dut_base_regs[1] = %x, ret: %d\n", dut_base_regs[0], dut_base_regs[1], ret );
           return -ENODEV;
       }

       dev_resource.start = dut_base_regs[0];
       dev_resource.end = dut_base_regs[0] + dut_base_regs[1];
       dev_resource.flags = IORESOURCE_MEM;
       dev_resource.parent = dev_resource.child = dev_resource.sibling = NULL;

       // set the dut base address
       port_device.dut_base_addr = devm_ioremap_resource(&pdev->dev, &dev_resource);

       CSMLOGDBG("ioremap of resource done: 0x%lx\n", port_device.dut_base_addr);
   }

   // read the sfp phandle
   if (of_property_read_u32_index(pdev->dev.of_node, "sfp", 0, &sfp_phandle) >= 0)
   {
       CSMLOGDBG("Port found sfp_phandle: %d\n", sfp_phandle);
       port_device.sfp_phandle = sfp_phandle;
   }
   else
   {
       CSMLOGDBG("Port failed to find sfp_phandle\n");
       port_device.sfp_phandle = -1;
   }

   // get the number of links
   if (!of_get_property(pdev->dev.of_node, "qcom,mac-port-link-references", &link_entries))
   {
       CSMLOGERR("Port no references to links");
       return -ENODEV;
   }

   port_device.num_link_phandles = link_entries/(sizeof(u32));

   if (port_device.num_link_phandles > MTIP_MAX_LINKS_PER_PORT)
   {
       CSMLOGERR("Num phandle references %d exceeds MAX\n", port_device.num_link_phandles);
       return -ENODEV;
   }

   if (port_device.num_link_phandles == 0)
   {
       CSMLOGERR("Num phandle references %d is 0!\n", port_device.num_link_phandles);
       return -ENODEV;
   }

   CSMLOGDBG("Port link entries: %d, num_phandles: %d\n", link_entries, port_device.num_link_phandles);

   for (i = 0; i < port_device.num_link_phandles; ++i) 
   {
       if (of_property_read_u32_index(pdev->dev.of_node, "qcom,mac-port-link-references", i, &phandle) >= 0)
       {
           CSMLOGDBG("Port found phandle: %d for index: %d\n", phandle, i);
           port_device.link_phandles[i] = phandle;
       }
       else
       {
           CSMLOGERR("Port failed to find phandle for index: %d", i);
           return -ENODEV;
       }
   }

   // the DT entries have been processed
   spin_lock_irqsave(lock, flags);

   index_found = false;

   // search for the port_phandle
   for (i = 0; i < platform_driver_priv->devices.num_port_phandles; ++i)
   {
       if (port_device.port_phandle == platform_driver_priv->devices.port_phandles[i])
       {
           CSMLOGDBG("Found port_phandle %d in root device at index: %d\n", port_device.port_phandle, i);
           index_found = true;
           break;
       }
   }

   if (index_found)
   {
       CSMLOGDBG("Updating index: %d with port information\n", i);

       // set the port device at the found index
       memcpy(&platform_driver_priv->devices.port_devices[i], &port_device, sizeof(struct mtip_port_device_info));

       ++platform_driver_priv->devices.num_port_phandles_probed;

       if (platform_driver_priv->devices.num_port_phandles_probed >= platform_driver_priv->devices.num_port_phandles)
       {
           all_ports_probed = true;
       }
   }
   else
   {
       CSMLOGERR("Did not find %d handle in root device: ignoring\n", port_device.port_phandle);
       ret = -ENODEV;
   }

   spin_unlock_irqrestore(lock, flags);

   if (all_ports_probed)
   {
       CSMLOGERR("All ports received probe!");
   }

    CSMLOGDBG("done with processing port device: %lx", (unsigned long) pdev);
    return ret;
}

int mtip_platform_probe(struct platform_device *pdev) 
{
    int ret = 0;
    int i;
    int result = 0;
    int mode;
    int port_entries;
    int port_count;
    u32 phandle;
    u32 fuse_addr[2];          
    u32 fuse_bit_offset;
    struct resource dev_resource;

    CSMLOGDBG("mtip_platform_probe called for device: \"%s\"\n", pdev->name);

    /* Get the device mode */
    result	= of_property_read_u32(pdev->dev.of_node, "qcom,device-mode", &mode);

    if (result < 0) {
        CSMLOGERR(":get resource failed for device-mode\n");
        return -ENODEV;
    }

    if (mode == MTIP_DEVICE_RU) {
       CSMLOGERR("device-mode is RU");
    }
    else {
       CSMLOGERR("device-mode is DU");
    }
    platform_driver_priv->devices.mode = mode;

    if (mtip_rumi_platform == 0) 
    {
        // read the MAC address fuse addresses
        result = of_property_read_u32_array(pdev->dev.of_node, "qcom,mac-address-fuse", fuse_addr, 2);

        if (result < 0) {
            CSMLOGERR("Unable to read mac-address-fuse, result: %d\n", result);
            return -ENODEV;
        }
        CSMLOGDBG("fuse_addr[0] : %x, fuse_addr[1] = %x, ret: %d\n", fuse_addr[0], fuse_addr[1], result);

        dev_resource.start = fuse_addr[0];
        dev_resource.end = fuse_addr[0] + fuse_addr[1];
        dev_resource.flags = IORESOURCE_MEM;
        dev_resource.parent = dev_resource.child = dev_resource.sibling = NULL;

        // set the fuse base address
        platform_driver_priv->devices.fuse_base_addr = devm_ioremap_resource(&pdev->dev, &dev_resource);

        // read the MAC address fuse bit offset
        result = of_property_read_u32(pdev->dev.of_node, "qcom,mac-address-bit-offset", &fuse_bit_offset);

        if (result < 0) {
            CSMLOGERR("Unable to read mac-address-bit-offset, result: %d\n", result);
            return -ENODEV;
        }
        CSMLOGDBG("fuse_bit_offset = %d, ret: %d\n", fuse_bit_offset, result);

        // set the fuse bit offset
        platform_driver_priv->devices.fuse_bit_offset = fuse_bit_offset;
    }

    // copy the platform device pointer
    platform_driver_priv->devices.root_pdev = pdev;

    // set the number of phandles probed
    platform_driver_priv->devices.num_port_phandles_probed = 0;

    // get the number of ports
    if (!of_get_property(pdev->dev.of_node, "qcom,mac-port-references", &port_entries))
    {
        CSMLOGERR("Platform no references to ports");
        return -ENODEV;
    }

    port_count = port_entries/(sizeof(u32));

    CSMLOGDBG("Platform port entries: %d, port count: %d\n", port_entries, port_count);

    platform_driver_priv->devices.num_port_phandles = port_count;

    if (port_count > MTIP_MAX_PORTS)
    {
        CSMLOGERR("Number of port phandles exceeds MAX");
        return -ENODEV;
    }

    for (i = 0; i < port_count; ++i) 
    {
        if (of_property_read_u32_index(pdev->dev.of_node, "qcom,mac-port-references", i, &phandle) >= 0)
        {
            CSMLOGDBG("Platform found phandle: %d for index: %d\n", phandle, i);
            platform_driver_priv->devices.port_phandles[i] = phandle;
        }
        else
        {
            CSMLOGERR("Platform failed to find phandle for index: %d", i);
            return -ENODEV;
        }
    }

    CSMLOGDBG("done with processing platform device: %lx", (unsigned long) pdev);
    return ret;
}

/*
 * Validate that the lane configurations of all the links of a port 
 * are correct 
 */
static int mtip_platform_validate_dt_lane_config(struct mtip_port_device_info* port_device)
{
    u32 i;
    u32 j;
    bool lanes_used[PHY_LANE_MAX];
    u8 lane_number;
    int lane_speed_gbps;
    u32 link_index;
    struct mtip_link_device_info *link;
    u32 port_speed = 0;

    // no common lanes across links
    for (i = 0; i < PHY_LANE_MAX; ++i) {
        lanes_used[i] = false;
    }

    for (j = 0; j < port_device->num_link_phandles; ++j)
    {
        link = &port_device->link_devices[j];
        link_index = link->link_index;

        for (i = 0; i < link->num_lanes; ++i)
        {
            lane_number = link->lanes[i];

            if (lanes_used[lane_number] == true)
            {
                CSMLOGERR("Error in link_index %d lane_number %d already in use\n", link_index, lane_number);
                return -1;
            }
            else
            {
                lanes_used[lane_number] = true;
            }
        }
    }

    CSMLOGDBG("No lane conflicts present for port type %d\n", port_device->port_type);

    for (j = 0; j < port_device->num_link_phandles; ++j)
    {
        link = &port_device->link_devices[j];
        link_index = link->link_index;

        switch (link->lane_speed)
        {
        case PHY_LANE_SPEED_100G:
            {
                if (link->num_lanes != 1)
                {
                    CSMLOGERR("100G speed only supported over 1 lane: %d set\n", link->num_lanes);
                    return -1;
                }

                // only lane3 in v1 supports 100G
                if (link->lanes[0] != 3)
                {
                    CSMLOGERR("In V1 HW, only lane 3 supports 100G: set %d\n", link->lanes[0]);
                    return -1;
                }
            }
            break;

        case PHY_LANE_SPEED_50G:
            {
                // 50G can only be supported on 2 lanes: 0 and 1
                if (link->num_lanes > 2)
                {
                    CSMLOGERR("50G speed supported over MAX 2 lanes: %d set\n", link->num_lanes);
                    return -1;
                }

                for (i = 0; i < link->num_lanes; ++i)
                {
                    lane_number = link->lanes[i];

                    if (lane_number >= 2)
                    {
                        CSMLOGERR("50G supported only on lane 0 or 1: set %d for link index: %d\n", lane_number, link_index);
                        return -1;
                    }
                }
            }
            break;

        case PHY_LANE_SPEED_10G:
        case PHY_LANE_SPEED_25G:
            {
                // all four lanes can be used for these speeds
            }
            break;
        default:
            {
                CSMLOGERR("Unknown lane_speed %d set for link_index %d\n", link->lane_speed, link_index);
                return -1;
            }
            break;
        }
    }

    CSMLOGDBG("Lane speed assignment to lanes is valid");

    for (j = 0; j < port_device->num_link_phandles; ++j)
    {
        link = &port_device->link_devices[j];
        link_index = link->link_index;
        lane_speed_gbps = mtip_platform_convert_lane_speed_to_gbps(link->lane_speed);

        if (lane_speed_gbps < 0)
        {
            CSMLOGERR("Invalid lane speed %d for link index: %d\n", link->lane_speed, link_index);
            return -1;
        }

        port_speed +=  lane_speed_gbps * link->num_lanes;
    }

    if (port_speed > 100000)
    {
        CSMLOGERR("Total port_speed %d exceeds 100Gbps\n", port_speed);
        return -1;
    }

    CSMLOGDBG("Total port_speed is %d\n", port_speed);

    return 0;
}

static int mtip_platform_validate_dt_config()
{
    int i, j;
    int ret = 0;
    u32 real_link_number;
    u32 first_link_index;
    u32 tmp_link_number;
    u32 link_index;
    u32 port_type;

    // check if num ports is zero
    if (platform_driver_priv->devices.num_port_phandles == 0)
    {
        CSMLOGERR("There are no ports specified!\n");
        return -1;
    }

    for (i = 0; i < platform_driver_priv->devices.num_port_phandles; ++i) 
    {
        CSMLOGDBG("validating port %d dt config\n", i);

        if (platform_driver_priv->devices.port_devices[i].num_link_phandles == 0)
        {
            CSMLOGDBG("Port %d has no links: ignoring\n", j);
        }
        else
        {
            port_type = platform_driver_priv->devices.port_devices[i].port_type;

            CSMLOGDBG("Port %d has %d links\n", i, platform_driver_priv->devices.port_devices[i].num_link_phandles);

            // use the real port and link of the first link
            first_link_index = platform_driver_priv->devices.port_devices[i].link_devices[0].link_index;

            if (mtip_lookup_real_link_number_by_link_index(first_link_index, &real_link_number) < 0)
            {
                CSMLOGERR("Link index %d is out of range\n", first_link_index);
                return -1;
            }

            for (j = 0; j < platform_driver_priv->devices.port_devices[i].num_link_phandles; ++j)
            {
                link_index = platform_driver_priv->devices.port_devices[i].link_devices[j].link_index;

                if (mtip_lookup_real_link_number_by_link_index(link_index, &tmp_link_number) < 0)
                {
                    CSMLOGERR("Link index %d of %d, %d is out of range\n", link_index, i, j);
                    return -1;
                }
            }

            if (mtip_platform_validate_dt_lane_config(&platform_driver_priv->devices.port_devices[i]) < 0)
            {
                CSMLOGERR("Port %d lane config error\n", i);
                return -1;
            }
        }
    }

    return ret;
}

static int mtip_platform_set_mac_addresses_for_rumi(void)
{
    uint8_t saddr[6];
    u32 port_device_index;
    u32 link_device_index;
    int i;
    u32 oui;
    u32 nic;
    
    CSMLOGDBG("Setting default MAC addresses on RUMI\n");

    // set the oui and nic values in little endian order
    oui = 0x00534E; 
    nic = 0x554C30; 

    for (i = 0; i < MTIP_MAX_LINKS; ++i) 
    {
        // for each valid link
        if (platform_driver_priv->mtip_links[i] != NULL) 
        {
            // find the port and link numbers
            mtip_lookup_device_by_link_index(i, &port_device_index, &link_device_index);

            saddr[0] = (oui >> 16) & 0xFF;
            saddr[1] = (oui >> 8) & 0xFF;
            saddr[2] = (oui) & 0xFF;

            saddr[3] = (nic >> 16) & 0xFF;
            saddr[4] = (nic >> 8) & 0xFF;
            saddr[5] = (nic) & 0xFF;

            mtip_mac_set_mac_address_by_device(port_device_index, link_device_index, saddr);

            // increment the lower bits
            ++nic;
        }
    }
    return 0;
}

static u8 mtip_platform_read_fuse_mac_info_version(void)
{
    void __iomem *fuse_base_addr;
    u8 fuse_bit_offset;
    u64 first_fuse_word;
    u8 version;

    // the start address is
    fuse_base_addr = platform_driver_priv->devices.fuse_base_addr;
    fuse_bit_offset = platform_driver_priv->devices.fuse_bit_offset;

    CSMLOGDBG("Going to read version info from fuse: 0x%lx\n", (unsigned long)fuse_base_addr);

    // read the first 64 bits
    first_fuse_word = ioread64(fuse_base_addr);

    // shift the fuse word by fuse_bit_offset
    first_fuse_word = (first_fuse_word >> fuse_bit_offset);

    // the version will be the first three bits
    version = (u8)((first_fuse_word) & 0x7);

    CSMLOGDBG("FUSE version: %d\n", version);

    return version;
}

static int mtip_platform_read_fuse_version1_info(u32* oui,
                                                  u32* start_nic,
                                                  u8* num_macs,
                                                  u32* start_secondary_nic,
                                                  u8* num_secondary_macs)
{
    void __iomem *fuse_base_addr;
    u8 fuse_bit_offset;
    u64 first_fuse_word;
    u64 second_fuse_word;

    // set as default
    *num_macs = 0;
    *num_secondary_macs = 0;

    // the start address is
    fuse_base_addr = platform_driver_priv->devices.fuse_base_addr;
    fuse_bit_offset = platform_driver_priv->devices.fuse_bit_offset;

    // version 1 will always start at fuse_bit_offset = 0
    if (fuse_bit_offset != 0) 
    {
        CSMLOGERR("Version 1 fuse bit offset has to be 0 not %d\n", fuse_bit_offset);
        return -1;
    }

    // read the first 64 bits
    first_fuse_word = ioread64(fuse_base_addr);

    // shift by 3 bits for version
    first_fuse_word = (first_fuse_word >> 3);

    // set the oui
    *oui = (u32)(first_fuse_word & 0xFFFFFF);

    CSMLOGDBG("VENDOR OUI is 0x%x\n", *oui);

    // shift by 24 bits
    first_fuse_word = (first_fuse_word >> 24);

    // set the start_nic
    *start_nic = (u32)(first_fuse_word & 0xFFFFFF);

    CSMLOGDBG("MAC Address Start Offset is 0x%x\n", *start_nic);

    // shift by 24 bits
    first_fuse_word = (first_fuse_word >> 24);

    // set the num_macs
    *num_macs = (u8)(first_fuse_word & 0x1F);

    CSMLOGDBG("Number of MAC addresses is %d\n", *num_macs);

    // read the second 64 bits
    second_fuse_word = ioread64(fuse_base_addr + sizeof(u64));

    // set the secondary nic
    *start_secondary_nic = (u32)(second_fuse_word & 0xFFFFFF);

    CSMLOGDBG("Secondary MAC address offset: 0x%x\n", *start_secondary_nic);

    // shift by 24 bits
    second_fuse_word = (second_fuse_word >> 24);

    // set the num secondary macs
    *num_secondary_macs = (u8)(second_fuse_word & 0x1F);

    CSMLOGDBG("Num secondary MAC Addresses: %d\n", *num_secondary_macs);

    return 0;
}

static int mtip_platform_set_mac_addresses(void)
{
    uint8_t saddr[6];
    u32 port_device_index;
    u32 link_device_index;
    int i;
    u32 oui;
    u32 start_nic;
    u8 no_of_macs = 0;
    u32 start_secondary_nic;
    u8 num_secondary_macs = 0;
    u8 version;

    version = mtip_platform_read_fuse_mac_info_version();

    // for now we only support version = 0x1
    if (version != 0x1) 
    {
        CSMLOGERR("Unsupported FUSE MAC INFO version number: %d\n", version);

        CSMLOGDBG("Setting default MAC addresses\n");

        // the oui and nic are in little endian order
        oui = 0x00534E; // EXAMPLE
        start_nic = 0x554C30; // EXAMPLE

        // set the MAC address for the other interfaces
        for (i = 0; i < MTIP_MAX_LINKS; ++i) 
        {
            // for each valid link
            if (platform_driver_priv->mtip_links[i] != NULL) 
            {
                // find the port and link numbers
                mtip_lookup_device_by_link_index(i, &port_device_index, &link_device_index);

                saddr[0] = (oui >> 16) & 0xFF;
                saddr[1] = (oui >> 8) & 0xFF;
                saddr[2] = (oui) & 0xFF;

                saddr[3] = (start_nic >> 16) & 0xFF;
                saddr[4] = (start_nic >> 8) & 0xFF;
                saddr[5] = (start_nic) & 0xFF;

                mtip_mac_set_mac_address_by_device(port_device_index, link_device_index, saddr);
            }

            // increment the lower bits
            ++start_nic;
        }
    }
    else
    {
        // read the remaining fields of fuse
        // read the fuse and update the oui, nic and no of macs
        mtip_platform_read_fuse_version1_info(&oui, &start_nic, &no_of_macs, &start_secondary_nic, &num_secondary_macs);

        // check that we have sufficient addresses
        if (no_of_macs < 16)
        {
            CSMLOGERR("Number of MAC addresses in fuse: %d is less than required: %d\n", no_of_macs, 16);
        }

        // first set the MAC address of Debug Ethernet if presennt
        i = MTIP_MAX_LINKS - 1;

        if (platform_driver_priv->mtip_links[i] != NULL) 
        {
            // find the port and link numbers
            mtip_lookup_device_by_link_index(i, &port_device_index, &link_device_index);

            saddr[0] = (oui >> 16) & 0xFF;
            saddr[1] = (oui >> 8) & 0xFF;
            saddr[2] = (oui) & 0xFF;

            saddr[3] = (start_nic >> 16) & 0xFF;
            saddr[4] = (start_nic >> 8) & 0xFF;
            saddr[5] = (start_nic) & 0xFF;

            mtip_mac_set_mac_address_by_device(port_device_index, link_device_index, saddr);
        }

        // increment the MAC OFFSET
        ++start_nic;

        // set the MAC address for the other interfaces
        for (i = 0; i < MTIP_MAX_LINKS - 1; ++i) 
        {
            // for each valid link
            if (platform_driver_priv->mtip_links[i] != NULL) 
            {
                // find the port and link numbers
                mtip_lookup_device_by_link_index(i, &port_device_index, &link_device_index);

                saddr[0] = (oui >> 16) & 0xFF;
                saddr[1] = (oui >> 8) & 0xFF;
                saddr[2] = (oui) & 0xFF;

                saddr[3] = (start_nic >> 16) & 0xFF;
                saddr[4] = (start_nic >> 8) & 0xFF;
                saddr[5] = (start_nic) & 0xFF;

                mtip_mac_set_mac_address_by_device(port_device_index, link_device_index, saddr);
            }

            // increment the lower bits
            ++start_nic;
        }
    }

    return 0;
}

static bool mtip_platform_consolidate_port_lane_config(struct mtip_port_device_info* port_device)
{
    int i, j;
    enum eth_phy_iface_phy_lane_speed_enum  lane_speed;
    u32 num_lanes;
    u32 lane;
    enum mtip_port_config_enum port_config = MTIP_PORT_CONFIG_4x25GBASE_R;
    bool rv = true;
    u32 link_index;

    CSMLOGDBG("Consolidating lane config of port: %d\n", port_device->port_type);

    // set all the lanes as disabled
    for (i = 0; i < PHY_LANE_MAX; ++i) 
    {
        port_device->lane_config[i].lane_enabled = false;
    }

    // go through all the links and set the lanes to be enabled
    // the lanes and speeds have all been validated to be correct by this time
    for (i = 0; i < port_device->num_link_phandles; ++i)
    {
        lane_speed = port_device->link_devices[i].lane_speed;
        num_lanes = port_device->link_devices[i].num_lanes;
        link_index = port_device->link_devices[i].link_index;

        for (j = 0; j < num_lanes; ++j)
        {
            lane = port_device->link_devices[i].lanes[j];
            port_device->lane_config[lane].lane_enabled = true;
            port_device->lane_config[lane].lane_speed = lane_speed;

            port_device->lane_config[lane].link_index = link_index;

            CSMLOGDBG("Setting port: %d lane_config[%d] to lane_speed: %d, link_index: %d\n", port_device->port_type, lane, lane_speed, link_index);
        }
    }

    // set the PORT CONFIG
    // for now only symmetric configurations are supported
    // link 0 configuration will be used to set the port config
    lane_speed = port_device->link_devices[0].lane_speed;
    num_lanes = port_device->link_devices[0].num_lanes;

    switch (lane_speed) 
    {
    case PHY_LANE_SPEED_25G:
        {
            if (num_lanes == 4)
            {
                port_config = MTIP_PORT_CONFIG_1x100GBASE_R4;
            }
            else if (num_lanes == 2) 
            {
                port_config = MTIP_PORT_CONFIG_2x50GBASE_R2;
            }
            else
            {
                port_config = MTIP_PORT_CONFIG_4x25GBASE_R;
            }
        }
        break;

    case PHY_LANE_SPEED_10G:
        {
            if (num_lanes == 4)
            {
                port_config = MTIP_PORT_CONFIG_1x40GBASE_R4;
            }
            else
            {
                port_config = MTIP_PORT_CONFIG_4x10GBASE_R;
            }
        }
        break;

    case PHY_LANE_SPEED_50G:
    case PHY_LANE_SPEED_100G:
    default:
        {
            CSMLOGERR("Unsupported lane_speed: %d", lane_speed);
            rv = false;
        }
        break;
    }

    CSMLOGERR("Setting port: %d port config to %d str %s", port_device->port_type, port_config, mtip_ethtool_get_priv_flags_str(port_config));

    // set the config of the port
    port_device->port_config = port_config;
    return rv;
}

int mtip_platform_setup_ethernet(unsigned int port_device)
{
    int i;
    int result;
    int ret = 0;
    struct mtip_netdev_priv *priv;
    u32 port_device_index;
    u32 link_device_index;

    CSMLOGDBG("Setting up ethernet for port_device %d", port_device);

    if (mtip_rumi_platform != 0) 
    {
        // Reset the EMULATION DUT ONLY FOR RUMI
        CSMLOGDBG("Reseting the FH emulation at index: %d\n", port_device);

        // reset the FH emulation
        mtip_dut_reset(platform_driver_priv->devices.port_devices[port_device].dut_base_addr);
    } 
    else 
    {
        // initialize the RSFEC, SETUP PHY and PHYLINK of the ports
        CSMLOGDBG("Initializing RSFEC and PHY for port: %d\n", port_device);

        // initialize the RSFEC of the port
        mtip_rsfec_initialize(&platform_driver_priv->devices.port_devices[port_device]);

        // setup the phy of the port
        mtip_phy_setup_phy(&platform_driver_priv->devices.port_devices[port_device]);
    }

    // Initialize the MAC WRAPPER
    CSMLOGDBG("Initializing MAC port at index: %d\n", port_device);

    // MAC wrapper Init
    mtip_mac_wrapper_init(&platform_driver_priv->devices.port_devices[port_device]);

    if (mtip_rumi_platform == 0) 
    {
        // set the mac wrapper pcs mode control
        mtip_mac_wrapper_pcs_mode_control(&platform_driver_priv->devices.port_devices[port_device]);
    }

    // allocate the net device structures
    for (i = 0; i < MTIP_MAX_LINKS; ++i) 
    {
        // for each valid link
        if (mtip_lookup_device_by_link_index(i, &port_device_index, &link_device_index) >= 0)
        {
            // make sure there is at least one lane assigned to the link
            if (platform_driver_priv->devices.port_devices[port_device_index].link_devices[link_device_index].num_lanes != 0)
            {
                // check for the link object
                if (platform_driver_priv->mtip_links[i] != NULL)
                {
                    if (port_device == port_device_index) 
                    {
                        priv = netdev_priv(platform_driver_priv->mtip_links[i]->dev);

                        // Initialize the MAC block
                        mtip_mac_initialize(priv);

                        if (mtip_rumi_platform != 0) 
                        {
                            // setup loopback if needed
                            if (mtip_loopback_mode != MTIP_MODE_DEFAULT) 
                            {
                                // enable IOMACRO loopback
                                mtip_dut_enable_rgmii_loopback(i);
                            } 
                            else 
                            {
                                // MDIO registration
                                result = mtip_mdio_register(platform_driver_priv->mtip_links[i]->dev,
                                                            platform_driver_priv->devices.port_devices[port_device_index].link_devices[link_device_index].link_pdev->dev.of_node);
                                if (result) 
                                {
                                    CSMLOGERR("MDIO registration failed with err %d", result);
                                }

                                CSMLOGDBG("TX delay = %d, RX delay = %d", mtip_dut_get_tx_delay(i), mtip_dut_get_rx_delay(i));
                            }
                        } 
                        else 
                        {
                            // this is the default for the target
                            // initialize the PCS for the link
                            mtip_pcs_config_pcs(i);

                            if (mtip_loopback_mode == MTIP_MODE_LOOPBACK) 
                            {
                                // enable pcs loopback on the link
                                mtip_pcs_enable_loopback(i);
                            }

                            if (mtip_rumi_platform == 0) 
                            {
                                // set the MAC interrupt mask
                                mtip_mac_set_interrupt_mask(i);
                            }
                        }
                    }
                }
            }
            else
            {
                // check for the link object
                if (platform_driver_priv->mtip_links[i] != NULL)
                {
                    if (port_device == port_device_index) 
                    {
                        if (mtip_rumi_platform == 0) 
                        {
                            // clear the MAC interrupt mask
                            mtip_mac_clear_interrupt_mask(i);
                        }
                    }
                }
            }
        }
    }

    return ret;
}

/**
 * mtip_platform_setup
 */
static int mtip_platform_setup(void)
{
   int i, j = 0;
   int result;
   int ret = 0;
   struct net_device *netdev = NULL;
   struct mtip_netdev_priv *priv;
   u32 total_num_links = 0;
   u32 port_device_index;
   u32 link_device_index;

   // validate device tree config
   if (mtip_platform_validate_dt_config() < 0)
   {
       CSMLOGERR("platform validate failed!\n");
       return -ENODEV;
   }

   // consolidate the lane configuration of all ports
   for (i = 0; i < platform_driver_priv->devices.num_port_phandles; ++i)
   {
       // consolidate the lane config
       mtip_platform_consolidate_port_lane_config(&platform_driver_priv->devices.port_devices[i]);
   }

   // enable all the necessary clocks
   mtip_clocks_setup_clocks();

   // calculate the total number of active links across all ports
   total_num_links = 0;

   for (i = 0; i < platform_driver_priv->devices.num_port_phandles; ++i) 
   {
       total_num_links += platform_driver_priv->devices.port_devices[i].num_link_phandles;
   }

   CSMLOGDBG("Setting up %d links\n", total_num_links);

   for (i = 0; i < platform_driver_priv->devices.num_port_phandles; ++i) 
   {
        // allocate the mtip_links and connect to dma
       for (j = 0; j < platform_driver_priv->devices.port_devices[i].num_link_phandles; ++j)
        {
           // check if this is a valid link
           if (platform_driver_priv->devices.port_devices[i].link_devices[j].mac_ioaddr != NULL) {

                // setup the link for port: i and link number: j
                ret = mtip_platform_setup_link(i, j);

               // HANDLE THE ERROR
               if (ret < 0) {
                  CSMLOGERR("link setup failed for port number: %d and link number: %d\n", i, j);
                  goto cleanup;
               }
            }
        }
   }

   // allocate the net device structures
   for (i = 0; i < MTIP_MAX_LINKS; ++i) 
   {
       // for each valid link
       if (platform_driver_priv->mtip_links[i] != NULL) 
       {
           // find the port and link numbers
           mtip_lookup_device_by_link_index(i, &port_device_index, &link_device_index);

           platform_driver_priv->mtip_links[i]->dev = alloc_netdev(sizeof(struct mtip_netdev_priv), 
                                                                   platform_driver_priv->devices.port_devices[port_device_index].link_devices[link_device_index].link_name, 
                                                                   NET_NAME_ENUM,
                                                                   mtip_netdevice_init);

          priv = netdev_priv(platform_driver_priv->mtip_links[i]->dev);

          netdev = platform_driver_priv->mtip_links[i]->dev;

          if (mtip_loopback_mode == MTIP_MODE_DEFAULT) 
          {
              // the supported features and hw features
              netdev->hw_features = 0;
              netdev->features = netdev->hw_features | NETIF_F_HIGHDMA;
              netdev->vlan_features = 0;
          }
          else
          {
              // for loopback set the features
              netdev->features = NETIF_F_HW_CSUM | NETIF_F_RXCSUM;
              netdev->hw_features = netdev->features;
              netdev->vlan_features |= NETIF_F_HW_CSUM;
          }
          
          /* MTU range: 46 - 9194 */
          netdev->min_mtu = MTIP_MAC_MIN_ETH_FRAME_SIZE -
             (ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN);
          netdev->max_mtu = MTIP_MAC_MAX_ETH_FRAME_SIZE -
             (ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN);

          priv->link_index = i;

          priv->hashtablebits = 0;

          // set the priv flags
          priv->priv_flags = (0x1 << (platform_driver_priv->devices.port_devices[port_device_index].port_config));

          // Set up link between ndev and pdev
          SET_NETDEV_DEV(platform_driver_priv->mtip_links[i]->dev, &platform_driver_priv->devices.port_devices[port_device_index].link_devices[link_device_index].link_pdev->dev);

          priv->mac_ioaddr = platform_driver_priv->devices.port_devices[port_device_index].link_devices[link_device_index].mac_ioaddr;

          CSMLOGDBG("dev = 0x%lx with link_index = %d",
                     (unsigned long)platform_driver_priv->mtip_links[i]->dev,
                     priv->link_index);

          // add the mtip_napi_rx
          // this needs to be done before register netdev
          netif_napi_add(platform_driver_priv->mtip_links[i]->dev, &(platform_driver_priv->mtip_links[i]->napi), mtip_napi_poll, MTIP_NAPI_WEIGHT);
          netif_napi_add(platform_driver_priv->mtip_links[i]->dev, &(platform_driver_priv->mtip_links[i]->napi_tx), mtip_napi_poll_tx, MTIP_NAPI_WEIGHT);

          CSMLOGDBG("mtip_devs[%d] = 0x%lx with link_index = %d\n", i, (unsigned long)platform_driver_priv->mtip_links[i]->dev, priv->link_index);
       }
   }

   if (mtip_rumi_platform == 0)
   {
       // program the MAC address of all the links by reading the fuse registers
       mtip_platform_set_mac_addresses();

       for (i = 0; i < platform_driver_priv->devices.num_port_phandles; ++i) {
           // setup phylink for the port
           mtip_phy_create_phylink(&platform_driver_priv->devices.port_devices[i]);
       }
   }
   else
   {
       // set default mac addresses
       mtip_platform_set_mac_addresses_for_rumi();
   }

   // register the net devices
   for (i = 0; i < MTIP_MAX_LINKS; ++i) {

       if (platform_driver_priv->mtip_links[i] != NULL) {

           // register the netdev
           result = register_netdev(platform_driver_priv->mtip_links[i]->dev);

           if (result) {
              CSMLOGERR("mtip: error %i for device \"%s\"\n", result, platform_driver_priv->mtip_links[i]->dev->name);
           } else {
              ret = 0;

              CSMLOGDBG("mtip: register netdev complete for \"%s\"\n", platform_driver_priv->mtip_links[i]->dev->name);

              // set the netdev MAC address from the HW
              mtip_set_netdev_hw_mac_addr(platform_driver_priv->mtip_links[i]->dev, i);
           }
       }
   }

   // setup the ethernet
   for (i = 0; i < platform_driver_priv->devices.num_port_phandles; ++i)
   {
       mtip_platform_setup_ethernet(i);

       // register for MAC wrapper IRQ
       mtip_mac_wrapper_register_irq(&platform_driver_priv->devices.port_devices[i].port_pdev->dev, 
                                      platform_driver_priv->devices.port_devices[i].wrapper_irq, 
                                      DRV_NAME, 
                                      (void *)&platform_driver_priv->devices.port_devices[i]);

       // set the clock rates based on updated port config
       mtip_clocks_set_clock_rates(platform_driver_priv->devices.port_devices[i].port_type, platform_driver_priv->devices.port_devices[i].port_config);
   }

   // the system topology is now setup using the device tree
   mtip_setup_topology();

   // indicate readiness to any registered clients */
   post_mtip_client_send_ready();

   goto out;

cleanup:
   for (i = 0; i < MTIP_MAX_LINKS; ++i) {
      mtip_platform_cleanup_link(i);
   }

out:
   return ret;
}

int mtip_port_remove(struct platform_device *pdev)
{
   CSMLOGINFO("mtip_port_remove called\n");
   // free the ports
   mtip_platform_cleanup_ports();
   return 0;
}

int mtip_link_remove(struct platform_device *pdev)
{
   int i;
   CSMLOGINFO("mtip_link_remove called\n");
   // free the net devices
   for (i = 0; i < MTIP_MAX_LINKS; ++i) 
   {
       if (platform_driver_priv->mtip_links[i]!=NULL)
       {
	  if(platform_driver_priv->mtip_links[i]->dev != NULL)
       {
           // unregister the netdevs
          unregister_netdev(platform_driver_priv->mtip_links[i]->dev);

          // free the netdevs
          free_netdev(platform_driver_priv->mtip_links[i]->dev);
             platform_driver_priv->mtip_links[i]->dev=NULL;
       }
           // cleanup the link
           mtip_platform_cleanup_link(i);
       }
   }

   return 0;
}

int mtip_platform_convert_lane_speed_to_gbps(enum eth_phy_iface_phy_lane_speed_enum lane_speed)
{
    switch (lane_speed)
    {
    case PHY_LANE_SPEED_100G:
        {
            return 100000;
        }
        break;

    case PHY_LANE_SPEED_50G:
        {
            return 50000;
        }
        break;

    case PHY_LANE_SPEED_10G:
        {
            return 10000;
        }
        break;
    case PHY_LANE_SPEED_25G:
        {
            return 25000;
        }
        break;
    default:
        {
            CSMLOGERR("Unknown lane_speed %d\n", lane_speed);
            return -1;
        }
        break;
    }
    return -1;
}

void mtip_platform_print_link_device(struct mtip_link_device_info* link_device)
{
    int i;
    CSMLOGINFO("link phandle: %d, link_index: %d, link name: %s", 
               link_device->link_phandle, 
               link_device->link_index,
               link_device->link_name);

    CSMLOGINFO("lane speed: %d, num_lanes: %d", link_device->lane_speed, link_device->num_lanes);

    for (i = 0; i < link_device->num_lanes; ++i) 
    {
        CSMLOGINFO("lanes[%d] = %d", i, link_device->lanes[i]);
    }
}

void mtip_platform_print_port_device(struct mtip_port_device_info* port_device)
{
    int i;

    CSMLOGINFO("printing port phandle: %d, port_type: %d, sfp_handle: %d", 
               port_device->port_phandle,
               port_device->port_type,
               port_device->sfp_phandle);

    CSMLOGINFO("port config: %d str %s", port_device->port_config, mtip_ethtool_get_priv_flags_str(port_device->port_config));

    for (i = 0; i < PHY_LANE_MAX; ++i) 
    {
        CSMLOGINFO("lane config[%d] enabled: %d speed: %d link_index: %d", 
                   i, 
                   port_device->lane_config[i].lane_enabled,
                   port_device->lane_config[i].lane_speed,
                   port_device->lane_config[i].link_index);
    }

    CSMLOGINFO("num links: %d, links probed: %d", port_device->num_link_phandles, port_device->num_link_phandles_probed);

    for (i = 0; i < port_device->num_link_phandles; ++i) 
    {
        CSMLOGINFO("link device[%d] link phandle: %d start", i, port_device->link_phandles[i]);
        mtip_platform_print_link_device(&port_device->link_devices[i]);
        CSMLOGINFO("link device[%d] end", i);
    }
}

/**
 * print the contents of devices
 */
void mtip_platform_print_devices(void)
{
    int i;

    CSMLOGINFO("devices enum_mode: %d, num ports: %d, probed: %d", 
               platform_driver_priv->devices.mode,
               platform_driver_priv->devices.num_port_phandles,
               platform_driver_priv->devices.num_port_phandles_probed);

    for (i = 0; i < platform_driver_priv->devices.num_port_phandles; ++i) 
    {
        CSMLOGINFO("port device: %d port phandle: %d start", i, platform_driver_priv->devices.port_phandles[i]);
        mtip_platform_print_port_device(&platform_driver_priv->devices.port_devices[i]);
        CSMLOGINFO("port device: %d end", i);
    }
}

/**
 * print the contents of links
 */
void mtip_platform_print_links(void)
{
    int i;
    struct mtip_link_info* link;

    for (i = 0; i < MTIP_MAX_LINKS; ++i) 
    {
        if (platform_driver_priv->mtip_links[i] != NULL) 
        {
            link = platform_driver_priv->mtip_links[i];

            CSMLOGINFO("mtip_link[%d] state: %d, dma_hdl: %d, pdi: %d, ldi: %d, ts_enable: %d, peak_rx_available: %d, active fec: %d", i, 
                       link->state,
                       link->dma_hdl,
                       link->port_device_index,
                       link->link_device_index,
                       link->ptp_ts_enabled,
                       link->peak_rx_available,
                       link->active_fec);
        }
        else
        {
            CSMLOGINFO("mtip_link[%d] is NULL", i);
        }
    }
}

/**
 * print the contents of ports
 */
void mtip_platform_print_ports(void)
{
    int i;
    struct mtip_port_info* port;

    for (i = 0; i < MTIP_MAX_PORTS; ++i) 
    {
        if (platform_driver_priv->mtip_ports[i] != NULL) 
        {
            port = platform_driver_priv->mtip_ports[i];

            CSMLOGINFO("mtip_ports[%d] port_state: %d, sfp_port_type: %d", i, port->port_state, port->sfp_port_type);
        }
        else
        {
            CSMLOGINFO("mtip_ports[%d] is NULL", i);
        }
    }
}

void mtip_platform_print_platform(void)
{
    CSMLOGINFO("Printing platform start");
    CSMLOGINFO("perr: %d dma_is_ready: %d, phy_is_ready: %d", platform_driver_priv->perr, platform_driver_priv->dma_is_ready, platform_driver_priv->phy_is_ready);
    mtip_platform_print_devices();
    mtip_platform_print_links();
    mtip_platform_print_ports();
    CSMLOGINFO("Printing platform end");
}
