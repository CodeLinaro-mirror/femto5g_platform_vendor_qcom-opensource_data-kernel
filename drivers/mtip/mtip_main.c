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

MODULE_LICENSE("GPL v2");

#include <linux/module.h>
#include <linux/init.h>
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
#include <linux/of.h>

#include "ecpri_dma_eth.h"
#include "mtip.h"
#include "mtip_device.h"
#include "mtip_dma.h"
#include "mtip_platform.h"
#include "mtip_workq.h"
#include "mtip_hashmap.h"
#include "mtip_client.h"
#include "mtip_phy.h"
#include "mtip_dut.h"
#include "mtip_debug_eth.h"

/* Global variables of the driver */
struct mtip_platform_driver_priv* platform_driver_priv = NULL;

/* Module parameters */
int mtip_tx_delay[MTIP_MAX_LINKS];
int mtip_tx_delay_argc = 0;
module_param_array(mtip_tx_delay, int, &mtip_tx_delay_argc, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(mtip_tx_delay, "Transmit delay array for RGMII IO Macro");

int mtip_rx_delay[MTIP_MAX_LINKS];
int mtip_rx_delay_argc = 0;
module_param_array(mtip_rx_delay, int, &mtip_rx_delay_argc, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(mtip_rx_delay, "Receive delay array for RGMII IO Macro");

int mtip_loopback_mode = MTIP_MODE_DEFAULT;
module_param(mtip_loopback_mode, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(mtip_loopback_mode, "Loopback mode of the driver");

bool mtip_loopback_swap_addr = true;
module_param(mtip_loopback_swap_addr, bool, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(mtip_loopback_swap_addr, "Swap SA/DA in loopback mode operation");

bool mtip_loopback_enable_arp = false;
module_param(mtip_loopback_enable_arp, bool, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(mtip_loopback_enable_arp, "Enable ARP in loopback mode");

int mtip_rumi_platform = MTIP_PLATFORM_SOC;
module_param(mtip_rumi_platform, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(mtip_rumi_platform, "Platform mode to RUMI");

int mtip_dma_max_rx_buff_size = MTIP_DMA_RX_BUFF_SIZE;
module_param(mtip_dma_max_rx_buff_size, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(mtip_dma_max_rx_buff_size, "SET mtip_dma_rx buff size");

int mtip_lookup_link_index_by_name(char *name, u32 *link_index) {
   int i;
   struct net_device *dev;
   int ret = -1;
   unsigned long flags;
   spinlock_t *lock = &(platform_driver_priv->driver_lock);

   CSMLOGDBG("mtip_lookup_link_index_by_name called for %s\n", name);

   spin_lock_irqsave(lock, flags);

   // go through all the allocated netdevs and find link_index
   for (i = 0; i < MTIP_MAX_LINKS; ++i) 
   {
       if (platform_driver_priv->mtip_links[i] != NULL)
       {
           if (platform_driver_priv->mtip_links[i]->dev != NULL) {

             dev = (platform_driver_priv->mtip_links[i]->dev);
             if (strncmp(name, dev->name, IFNAMSIZ) == 0) {
                *link_index = i;
                ret = 0;
                break;
             }
       }
      }
   }

   spin_unlock_irqrestore(lock, flags);
   return ret;
}

int mtip_lookup_link_index_by_handle(ecpri_dma_eth_conn_hdl_t hdl, u32 *link_index) {

   CSMLOGDBG("mtip_lookup_link_index_by_handle called for %d\n", hdl);

   // use the hashmap to lookup index
   return mtip_hashmap_find(hdl, link_index);
}

/*
 * lookup the link index by the port_type and link number 
 * For example link_index 10 maps to port_type 2 and real_link_number 2 
 */
int mtip_lookup_link_index_by_port_type_and_real_link(u32* link_index, u32 port_type, u32 real_link_number)
{
	int ret = 0;
    u32 tmp_port_type;

	if (port_type <= MTIP_PORT_TYPE_FH_2)
	{
		// front haul port
		if (real_link_number >= 4)
		{
            CSMLOGERR("invalid link number: %d for port %d:\n", real_link_number, port_type);
			ret = -1;
            goto out;
		}
        else
        {
            *link_index = 4*port_type + real_link_number;
        }
	}
	else if (port_type < MTIP_PORT_TYPE_MAX)
	{
        if (real_link_number >= 2)
        {
            CSMLOGDBG("invalid link number: %d for port %d:\n", real_link_number, port_type);
            ret = -1;
            goto out;
        }
        else
        {
            *link_index = 12 + 2*(port_type - MTIP_PORT_TYPE_L2) + real_link_number;
        }
	}
	else
	{
        CSMLOGERR("invalid port_number: %d\n", port_type);
		ret = -1;
        goto out;
	}

    // cross check that link_index maps to the port
    if (mtip_lookup_port_type_by_link_index(*link_index, &tmp_port_type) < 0)
    {
        ret = -1;
        goto out;
    }
    else if (tmp_port_type != port_type) 
    {
        ret = -1;
        goto out;
    }

out:
	return ret;
}

/*
 * lookup the port_type from the link index 
 */
int mtip_lookup_port_type_by_link_index(u32 link_index, u32* port_type)
{
    int ret = 0;

    switch (link_index) 
    {
    case 0:
    case 1:
    case 2:
    case 3:
        *port_type = MTIP_PORT_TYPE_FH_0;
        break;
    case 4:
    case 5:
    case 6:
    case 7:
        *port_type = MTIP_PORT_TYPE_FH_1;
        break;
    case 8:
    case 9:
    case 10:
    case 11:
        *port_type = MTIP_PORT_TYPE_FH_2;
        break;
    case 12:
        *port_type = MTIP_PORT_TYPE_L2;
        break;
    case 15:
        *port_type = MTIP_PORT_TYPE_DEBUG;
        break;
    case 14:
    case 13:
    default:
        CSMLOGDBG("invalid link_index: %d\n", link_index);
        ret = -1;
        break;
    }
    return ret;
}

/*
 * lookup the real link number from the link index 
 * for example, link_index 7 will have the real link number 3 
 */
int mtip_lookup_real_link_number_by_link_index(u32 link_index, u32* real_link_number)
{
	int ret = 0;
	switch(link_index)
	{
	case 0:
		*real_link_number = 0;
		break;
	case 1:
		*real_link_number = 1;
		break;
	case 2:
		*real_link_number = 2;
		break;
	case 3:
		*real_link_number = 3;
		break;
	case 4:
		*real_link_number = 0;
		break;
	case 5:
		*real_link_number = 1;
		break;
	case 6:
		*real_link_number = 2;
		break;
	case 7:
		*real_link_number = 3;
		break;
	case 8:
		*real_link_number = 0;
		break;
	case 9:
		*real_link_number = 1;
		break;
	case 10:
		*real_link_number = 2;
		break;
	case 11:
		*real_link_number = 3;
		break;
	case 12:
		*real_link_number = 0;
		break;
	case 15:
		*real_link_number = 1;
		break;
    case 13:
    case 14:
	default:
        CSMLOGERR("invalid link_index: %d\n", link_index);
	    ret = -1;
		break;
	}
	return ret;
}

/*
 * mtip_lookup_link_index_by_device 
 *  find the link index within a port and the link_device_index (0 thru num_link_phandles - 1) 
 */
int mtip_lookup_link_index_by_device(u32* link_index, u32 port_type, u32 link_device_index)
{
    if (port_type >= MTIP_MAX_PORTS) 
    {
        CSMLOGERR("port_type %d out of bounds %d", port_type, MTIP_MAX_PORTS);
        return -1;
    }

    if (link_device_index >= platform_driver_priv->devices.port_devices[port_type].num_link_phandles)
    {
        CSMLOGERR("link_device_index %d out of bounds %d", link_device_index, platform_driver_priv->devices.port_devices[port_type].num_link_phandles);
        return -1;
    }

    *link_index = platform_driver_priv->devices.port_devices[port_type].link_devices[link_device_index]->link_index;
    return 0;
}

/*
 * mtip_lookup_device_by_link_index 
 *  find the port_type and the link_device_index (between 0 and num_phandles - 1) 
 */
int mtip_lookup_device_by_link_index(u32 link_index, u32* port_type, u32* link_device_index)
{
    int i;
    u32 link_phandle;

    if (mtip_lookup_port_type_by_link_index(link_index, port_type) < 0) 
    {
        CSMLOGDBG("Could not find port_type of link_index: %d", link_index);
        return -1;
    }

    link_phandle = platform_driver_priv->devices.link_devices[link_index].link_phandle;

    for (i = 0; i < platform_driver_priv->devices.port_devices[*port_type].num_link_phandles; ++i) 
    {
        if (link_phandle == platform_driver_priv->devices.port_devices[*port_type].link_phandles[i]) 
        {
            *link_device_index = i;
        return 0;
    }
    }
    return -1;
}

/*
 * lookup the lane index by the port_type and lane number 
 * For example lane_index 10 maps to port_type 2 and real_lane_number 2 
 */
int mtip_lookup_lane_index_by_port_type_and_real_lane(u32 *lane_index, u32 port_type, u32 real_lane_number)
{
	int ret = 0;
	if (port_type <= MTIP_PORT_TYPE_FH_2)
	{
		// front haul port
		if (real_lane_number >= 4)
		{
            CSMLOGERR("invalid lane number: %d for port %d:\n", real_lane_number, port_type);
			ret = -1;
		}
        else
        {
         *lane_index = 4 * port_type + real_lane_number;
        }
	}
	else if (port_type == MTIP_PORT_TYPE_L2)
	{
        if (real_lane_number >= 4)
        {
            CSMLOGERR("invalid lane number: %d for port %d:\n", real_lane_number, port_type);
            ret = -1;
        }
        else
        {
            *lane_index = 12 + real_lane_number;
        }
	}
    else if (port_type == MTIP_PORT_TYPE_DEBUG)
    {
        // only real_lane_number 2 and 3 are valid for DEBUGETH
        if ((real_lane_number == 2) || (real_lane_number == 3))
        {
            *lane_index = 16 + real_lane_number;
        }
	else
	{
         CSMLOGDBG("invalid lane number: %d for port %d:\n", real_lane_number, port_type);
            ret = -1;
        }
    }
	else
	{
        CSMLOGERR("invalid port_number: %d\n", port_type);
		ret = -1;
	}
	return ret;
}

/*
 * lookup the port_type from the lane index 
 */
int mtip_lookup_port_type_by_lane_index(u32 lane_index, u32* port_type)
{
	int ret = 0;

    switch (lane_index) 
	{
	case 0:
	case 1:
	case 2:
	case 3:
        *port_type = MTIP_PORT_TYPE_FH_0;
		break;
	case 4:
	case 5:
	case 6:
	case 7:
        *port_type = MTIP_PORT_TYPE_FH_1;
		break;
	case 8:
	case 9:
	case 10:
	case 11:
        *port_type = MTIP_PORT_TYPE_FH_2;
		break;
	case 12:
	case 13:
	case 14:
    case 15:
        *port_type = MTIP_PORT_TYPE_L2;
		break;
    case 18:
    case 19:
        *port_type = MTIP_PORT_TYPE_DEBUG;
		break;
    case 16:
    case 17:
	default:
        CSMLOGERR("invalid lane_index: %d\n", lane_index);
	    ret = -1;
		break;
	}
	return ret;
}

/*
 * lookup the real lane number from the lane index 
 * for example, lane_index 7 will have the real lane number 3 
 */
int mtip_lookup_real_lane_number_by_lane_index(u32 lane_index, u32* real_lane_number)
{
    int ret = 0;

    if (lane_index >= MTIP_MAX_LANES) 
    {
        CSMLOGERR("invalid lane_index %d", lane_index);
        ret = -1;
    }
    else 
    {
        *real_lane_number = lane_index%4;
    }
    return ret;
}

/*
 * mtip_lookup_lane_index_by_device 
 *  find the lane index within a port and the lane_device_index (0 thru num_lane_phandles - 1) 
 */
int mtip_lookup_lane_index_by_device(u32* lane_index, u32 port_type, u32 lane_device_index)
{
    if (port_type >= MTIP_MAX_PORTS) 
    {
        CSMLOGERR("port_type %d out of bounds %d", port_type, MTIP_MAX_PORTS);
        return -1;
    }

    if (lane_device_index >= platform_driver_priv->devices.port_devices[port_type].num_lane_phandles)
    {
        CSMLOGERR("lane_device_index %d out of bounds %d", lane_device_index, platform_driver_priv->devices.port_devices[port_type].num_lane_phandles);
        return -1;
    }

    *lane_index = platform_driver_priv->devices.port_devices[port_type].lane_devices[lane_device_index]->lane_index;
    return 0;
}

/*
 * mtip_lookup_device_by_lane_index 
 *  find the port_type and the lane_device_index (between 0 and num_phandles - 1) 
 */
int mtip_lookup_device_by_lane_index(u32 lane_index, u32* port_type, u32* lane_device_index)
{
    int i;
    u32 lane_phandle;

    CSMLOGERR("lookup_device by lane_index called");

    if (mtip_lookup_port_type_by_lane_index(lane_index, port_type) < 0) 
    {
        CSMLOGERR("Could not find port_type of lane_index: %d", lane_index);
        return -1;
    }

    lane_phandle = platform_driver_priv->devices.lane_devices[lane_index].lane_phandle;

    for (i = 0; i < platform_driver_priv->devices.port_devices[*port_type].num_lane_phandles; ++i) 
    {
        if (lane_phandle == platform_driver_priv->devices.port_devices[*port_type].lane_phandles[i]) 
        {
            *lane_device_index = i;
            return 0;
        }
    }
    return -1;
}

static const struct of_device_id mtip_mac_link_match[] = {
    { .compatible = "mtip-mac-link", },
    { }
};

MODULE_DEVICE_TABLE(of, mtip_mac_link_match);

static struct platform_driver ethernet_mac_link_driver = { 
	.probe  = mtip_link_probe,
	.remove = mtip_link_remove,
	.driver = {
		.name = "MTIP_MAC_LINK",
		.of_match_table = of_match_ptr(mtip_mac_link_match),
	},
};

static const struct of_device_id mtip_mac_lane_match[] = {
    { .compatible = "mtip-mac-lane", },
    { }
};

MODULE_DEVICE_TABLE(of, mtip_mac_lane_match);

static struct platform_driver ethernet_mac_lane_driver = { 
	.probe  = mtip_lane_probe,
	.remove = mtip_lane_remove,
	.driver = {
		.name = "MTIP_MAC_LANE",
		.of_match_table = of_match_ptr(mtip_mac_lane_match),
	},
};

static const struct of_device_id mtip_mac_port_match[] = {
    { .compatible = "mtip-mac-port", },
    { }
};

MODULE_DEVICE_TABLE(of, mtip_mac_port_match);

static struct platform_driver ethernet_mac_port_driver = { 
	.probe  = mtip_port_probe,
	.remove = mtip_port_remove,
	.driver = {
		.name = "MTIP_MAC_PORT",
		.of_match_table = of_match_ptr(mtip_mac_port_match),
	},
};

static const struct of_device_id mtip_mac_match[] = {
    { .compatible = "mtip-mac", },
    { }
};

MODULE_DEVICE_TABLE(of, mtip_mac_match);

static struct platform_driver ethernet_mac_platform_driver = { 
	.probe  = mtip_platform_probe,
    .remove = mtip_platform_remove,
	.driver = {
		.name = "MTIP_MAC",
		.of_match_table = of_match_ptr(mtip_mac_match),
	},
};

static struct ecpri_dma_eth_register_params mtip_dma_register_params;

/** 
 * mtip_register_platform_driver 
 *  - register as a platform driver
*/ 
int mtip_register_platform_driver(void)
{
   int ret = 0;

   CSMLOGDBG("mtip_register_platform_driver called\n");

   // register for the platform driver
   platform_driver_priv->perr = platform_driver_register(&ethernet_mac_platform_driver);

   // HANDLE THE ERROR
   if (platform_driver_priv->perr < 0)
   {
      ret = platform_driver_priv->perr;

      CSMLOGERR("platform_driver_register with error: %d\n", ret);
      return ret;
   }

   // register for port devices
   // register for the port driver
   platform_driver_priv->perr = platform_driver_register(&ethernet_mac_port_driver);

   // HANDLE THE ERROR
   if (platform_driver_priv->perr < 0)
   {
      ret = platform_driver_priv->perr;

      CSMLOGERR("platform_driver_register for port with error: %d\n", ret);
      return -ENODEV;
   }

   // register for link devices
   // register for the link driver
   platform_driver_priv->perr = platform_driver_register(&ethernet_mac_link_driver);

   // HANDLE THE ERROR
   if (platform_driver_priv->perr < 0)
   {
      ret = platform_driver_priv->perr;

      CSMLOGERR("platform_driver_register for link with error: %d\n", ret);
      return ret;
   }

   // register for lane devices
   // register for the lane driver
   platform_driver_priv->perr = platform_driver_register(&ethernet_mac_lane_driver);

   // HANDLE THE ERROR
   if (platform_driver_priv->perr < 0)
   {
      ret = platform_driver_priv->perr;

      CSMLOGERR("platform_driver_register for lane with error: %d\n", ret);
      return ret;
   }
   return ret;
}

static int mtip_module_init(void)
{
   int i;
   bool is_dma_ready = false;
   int ret = 0;

   CSMLOGERR("mtip_module_init called\n");

   // process the module parameters
   // tx_delay parameter
	for (i = 0; i < (sizeof mtip_tx_delay / sizeof (int)); i++)
	{
        if (mtip_tx_delay[i] != 0) 
        {
            CSMLOGDBG("mtip_tx_delay[%d] = %d\n", i, mtip_tx_delay[i]);
        }
	}
	CSMLOGDBG("mtip_tx_delay module params set for %d\n", mtip_tx_delay_argc);

    for (i = mtip_tx_delay_argc; i < MTIP_MAX_LINKS; ++i) {
        mtip_tx_delay[i] = TX_DELAY_DEFAULT_VAL;
    }

    // rx_delay parameter
    for (i = 0; i < (sizeof mtip_rx_delay / sizeof (int)); i++)
    {
        if (mtip_rx_delay[i] != 0) 
        {
            CSMLOGDBG("mtip_rx_delay[%d] = %d\n", i, mtip_rx_delay[i]);
        }
    }
    CSMLOGDBG("mtip_rx_delay module params set for %d\n", mtip_rx_delay_argc);

    for (i = mtip_rx_delay_argc; i < MTIP_MAX_LINKS; ++i) {
        mtip_rx_delay[i] = RX_DELAY_DEFAULT_VAL;
    }

    CSMLOGDBG("Loopback mode is %d\n", mtip_loopback_mode);

    if (mtip_rumi_platform != MTIP_PLATFORM_SOC) 
    {
        if (mtip_loopback_mode != MTIP_MODE_DEFAULT)
        {
            CSMLOGINFO("Mode: RUMI with LOOPBACK\n");
        }
        else
        {
            CSMLOGINFO("Mode: RUMI NO LOOPBACK\n");
        }
    }
    else
    {
        if (mtip_loopback_mode == MTIP_MODE_DEFAULT)
        {
            CSMLOGINFO("Mode: SOC NO LOOPBACK\n");
        }
        else if (mtip_loopback_mode == MTIP_MODE_PHY_LOOPBACK) 
        {
            CSMLOGINFO("Mode: SOC PHY LOOPBACK\n");
        }
        else
        {
            CSMLOGINFO("Mode: SOC with PCS LOOPBACK\n");
        }
    }

   // initialize the workq
   ret = mtip_initialize_workq();

   // HANDLE THE ERROR
   if (ret < 0)
   {
      goto out;
   }

   // initialize the hashmap
   ret = mtip_hashmap_initialize();

   // HANDLE THE ERROR
   if (ret < 0)
   {
      goto out;
   }

   // allocate the memory for the platform device private struct
   platform_driver_priv = (struct mtip_platform_driver_priv *)kmalloc(sizeof(struct mtip_platform_driver_priv), GFP_KERNEL);

   // HANDLE THE ERROR
   if (platform_driver_priv == NULL)
   {
      CSMLOGERR("Unable to allocate platform_driv_priv memory!");
      ret = -ENOMEM;
      goto out;
   }

   memset(platform_driver_priv, 0,sizeof(struct mtip_platform_driver_priv));

   // initialize the platform driver error status
   platform_driver_priv->perr = 0;

   // initialize the remaining platform_driver fields to default
   platform_driver_priv->dma_is_ready = false;

   // initialize the topology
   platform_driver_priv->topology = NULL;

   // Init IPC log buffers
   platform_driver_priv->ipc_log_buf = ipc_log_context_create(CSM_IPC_LOG_PAGES,
		"csm_mtip", 0);
	if (platform_driver_priv->ipc_log_buf == NULL)
    {
		CSMLOGERR("mtip_init(): failed to create IPC log context, continue...\n");
    }
    else
    {
        CSMLOGDBG("mtip_init(): IPC log context created successfully, continue...\n");
    }
   platform_driver_priv->ipc_ptp_log_buf = ipc_log_context_create(CSM_IPC_LOG_PAGES,
		"csm_ptp_mtip", 0);
	if (platform_driver_priv->ipc_ptp_log_buf == NULL)
    {
		CSMLOGERR("mtip_init(): failed to create IPC log context, continue...\n");
    }
    else
    {
        CSMLOGDBG("mtip_init(): IPC log context created successfully, continue...\n");
    }

    platform_driver_priv->ipc_log_buf_low = ipc_log_context_create(CSM_IPC_LOG_PAGES,
		"csm_mtip_low", 0);
    if (platform_driver_priv->ipc_log_buf_low == NULL)
    {
		CSMLOGERR("mtip_init(): failed to create IPC log LOW context, continue...\n");
    }
    else
    {
        CSMLOGDBG("mtip_init(): IPC log context LOW created successfully, continue...\n");
    }

    // initialize the dma array of allocs
    for (i = 0; i < MTIP_DMA_ALLOC_LIST_MAX; ++i) 
    {
        mtip_dma_alloc_initialize(i);
    }

   if (mtip_rumi_platform == MTIP_PLATFORM_SOC) 
   {
       // register with the PHY
       mtip_phy_register_eth();
   }

   for (i = 0; i < MTIP_MAX_CLIENTS; ++i) {
       platform_driver_priv->clients[i].events_cb = NULL;
       platform_driver_priv->clients[i].ready_cb = NULL;
   }

   mtip_dma_register_params.notify_ready = mtip_dma_ready_cb;
   mtip_dma_register_params.userdata_ready = NULL;
   mtip_dma_register_params.notify_rx_comp = mtip_dma_rx_comp_cb;
   mtip_dma_register_params.userdata_rx = NULL;
   mtip_dma_register_params.notify_tx_comp = mtip_dma_tx_comp_cb;
   mtip_dma_register_params.userdata_tx = NULL;

   // initialize the spinlock
   spin_lock_init(&platform_driver_priv->driver_lock);

   // register with the dma driver
   ret = (ecpri_dma_eth_driver_ops.ecpri_dma_eth_register)(&mtip_dma_register_params, &is_dma_ready);

   // HANDLE THE ERROR
   if (ret < 0)
   {
      CSMLOGERR("Failed to register with DMA");
      goto cleanup;
   }

   // set the dma_is_ready flag
   platform_driver_priv->dma_is_ready = is_dma_ready;

   if (is_dma_ready) 
   {
      CSMLOGDBG("DMA is ready: going to register platform driver\n");

      ret = mtip_register_platform_driver();

      // HANDLE THE ERROR
      if (ret < 0)
      {
         CSMLOGERR("Failed to register platform driver");
         goto cleanup;
      }
   }

   // register the debug eth platform driver
   mtip_debug_eth_register_platform_driver();

   goto out;

cleanup:
   if (platform_driver_priv->ipc_log_buf)
		ipc_log_context_destroy(platform_driver_priv->ipc_log_buf);
   if (platform_driver_priv->ipc_log_buf_low)
        ipc_log_context_destroy(platform_driver_priv->ipc_log_buf_low);
   kfree(platform_driver_priv);
   platform_driver_priv = NULL;

out:
   return ret;
}

static void mtip_module_exit(void)
{
   //int i;
   CSMLOGERR("mtip_module_exit called\n");

   // destroy the hashmap
   mtip_hashmap_destroy();
   mtip_eth_deregister_events_cb();

   mtip_debug_eth_unregister_platform_driver();
   if (!platform_driver_priv->perr)
   {
       platform_driver_unregister(&ethernet_mac_lane_driver);
       platform_driver_unregister(&ethernet_mac_link_driver);
       platform_driver_unregister(&ethernet_mac_port_driver);
       platform_driver_unregister(&ethernet_mac_platform_driver);
   }
   // deregister with the dma driver
   (ecpri_dma_eth_driver_ops.ecpri_dma_eth_deregister)();

   if (mtip_rumi_platform == MTIP_PLATFORM_SOC) 
   {
       // dergister with the phy driver
       mtip_phy_deregister_eth();
   }
   /* memory leak needs to be fixed later */
   // finalize the dma array of allocs
   /*for (i = 0; i < MTIP_DMA_ALLOC_LIST_MAX; ++i) 
   {
       mtip_dma_alloc_finalize(i);
   }
*/
   // finalize the workq
   mtip_destroy_workq();
   
   if (platform_driver_priv->ipc_log_buf)
		ipc_log_context_destroy(platform_driver_priv->ipc_log_buf);
   if (platform_driver_priv->ipc_log_buf_low)
        ipc_log_context_destroy(platform_driver_priv->ipc_log_buf_low);

   // free the platform driver priv
   kfree(platform_driver_priv);
   platform_driver_priv = NULL;

   return;
}

module_init(mtip_module_init);
module_exit(mtip_module_exit);


