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

int mtip_loopback_mode = 0;
module_param(mtip_loopback_mode, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(mtip_loopback_mode, "Loopback mode of the driver");

int mtip_rumi_platform = 0;
module_param(mtip_rumi_platform, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(mtip_rumi_platform, "Platform mode to RUMI");

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

#ifdef COMPILE_THIS
             if (strncmp(name, dev->name, IFNAMSIZ) == 0) {
                *link_index = i;
                ret = 0;
                break;
             }
#endif
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

int mtip_lookup_link_index_by_device(u32* link_index, u32 port_device_index, u32 link_device_index)
{
    *link_index = platform_driver_priv->devices.port_devices[port_device_index].link_devices[link_device_index].link_index;
    return 0;
}

int mtip_lookup_device_by_link_index(u32 link_index, u32* port_device_index, u32* link_device_index)
{
    if (platform_driver_priv->mtip_links[link_index] != NULL)
    {
        *port_device_index = platform_driver_priv->mtip_links[link_index]->port_device_index;
        *link_device_index = platform_driver_priv->mtip_links[link_index]->link_device_index;
        return 0;
    }
    return -1;
}

/*
 * lookup the link index by the real port and link number 
 * This may not be the same as the order of ports/links in the devicetree 
 */
int mtip_lookup_link_index_by_real_port_and_link(u32* link_index, u32 real_port_number, u32 real_link_number)
{
	int ret = 0;
	if (real_port_number <= MTIP_PORT_TYPE_FH_2)
	{
		// front haul port
		if (real_link_number >= 4)
		{
            CSMLOGERR("invalid link number: %d for port %d:\n", real_link_number, real_port_number);
			ret = -1;
		}
        else
        {
            *link_index = 4*real_port_number + real_link_number;
        }
	}
	else if (real_port_number < MTIP_PORT_TYPE_MAX)
	{
        if (real_link_number >= 2)
        {
            CSMLOGERR("invalid link number: %d for port %d:\n", real_link_number, real_port_number);
            ret = -1;
        }
        else
        {
            *link_index = 12 + 2*(real_port_number - MTIP_PORT_TYPE_L2) + real_link_number;
        }
	}
	else
	{
        CSMLOGERR("invalid port_number: %d\n", real_port_number);
		ret = -1;
	}
	return ret;
}

/*
 * lookup the real link number from the link index 
 * This may not be the same as the order in the device tree 
 */
int mtip_lookup_real_link_number_by_link_index(u32 link_index, u32* link_number)
{
	int ret = 0;
	switch(link_index)
	{
	case 0:
		*link_number = 0;
		break;
	case 1:
		*link_number = 1;
		break;
	case 2:
		*link_number = 2;
		break;
	case 3:
		*link_number = 3;
		break;
	case 4:
		*link_number = 0;
		break;
	case 5:
		*link_number = 1;
		break;
	case 6:
		*link_number = 2;
		break;
	case 7:
		*link_number = 3;
		break;
	case 8:
		*link_number = 0;
		break;
	case 9:
		*link_number = 1;
		break;
	case 10:
		*link_number = 2;
		break;
	case 11:
		*link_number = 3;
		break;
	case 12:
		*link_number = 0;
		break;
	case 13:
		*link_number = 1;
		break;
	case 14:
		*link_number = 0;
		break;
	case 15:
		*link_number = 2;
		break;
	default:
        CSMLOGERR("invalid link_index: %d\n", link_index);
	    ret = -1;
		break;
	}
	return ret;
}

static const struct of_device_id mtip_mac_link_match[] = {
    { .compatible = "mtip-mac-link", },
    { }
};

MODULE_DEVICE_TABLE(of, mtip_mac_link_match);

static struct platform_driver ethernet_mac_link_driver = { 
	.probe  = mtip_link_probe,
	.remove = mtip_platform_remove,
	.driver = {
		.name = "MTIP_MAC_LINK",
		.of_match_table = of_match_ptr(mtip_mac_link_match),
	},
};

static const struct of_device_id mtip_mac_port_match[] = {
    { .compatible = "mtip-mac-port", },
    { }
};

MODULE_DEVICE_TABLE(of, mtip_mac_port_match);

static struct platform_driver ethernet_mac_port_driver = { 
	.probe  = mtip_port_probe,
	.remove = mtip_platform_remove,
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

   CSMLOGINFO("mtip_register_platform_driver called\n");

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

   mtip_debug_eth_register_platform_driver();

   return ret;
}

static int mtip_module_init(void)
{
   int i;
   bool is_dma_ready = false;
   int ret = 0;

   CSMLOGINFO("mtip_module_init called\n");

   // process the module parameters
   // tx_delay parameter
	for (i = 0; i < (sizeof mtip_tx_delay / sizeof (int)); i++)
	{
        if (mtip_tx_delay[i] != 0) 
        {
            CSMLOGINFO("mtip_tx_delay[%d] = %d\n", i, mtip_tx_delay[i]);
        }
	}
	CSMLOGINFO("mtip_tx_delay module params set for %d\n", mtip_tx_delay_argc);

    for (i = mtip_tx_delay_argc; i < MTIP_MAX_LINKS; ++i) {
        mtip_tx_delay[i] = TX_DELAY_DEFAULT_VAL;
    }

    // rx_delay parameter
    for (i = 0; i < (sizeof mtip_rx_delay / sizeof (int)); i++)
    {
        if (mtip_rx_delay[i] != 0) 
        {
            CSMLOGINFO("mtip_rx_delay[%d] = %d\n", i, mtip_rx_delay[i]);
        }
    }
    CSMLOGINFO("mtip_rx_delay module params set for %d\n", mtip_rx_delay_argc);

    for (i = mtip_rx_delay_argc; i < MTIP_MAX_LINKS; ++i) {
        mtip_rx_delay[i] = RX_DELAY_DEFAULT_VAL;
    }

    CSMLOGINFO("Loopback mode is %d\n", mtip_loopback_mode);

    if (mtip_rumi_platform != 0) 
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

   if (mtip_rumi_platform == 0) 
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
      goto cleanup;
   }

   // set the dma_is_ready flag
   platform_driver_priv->dma_is_ready = is_dma_ready;

   if (is_dma_ready) 
   {
      CSMLOGINFO("DMA is ready: going to register platform driver\n");

      ret = mtip_register_platform_driver();

      // HANDLE THE ERROR
      if (ret < 0)
      {
         goto cleanup;
      }
   }
   goto out;

cleanup:
   kfree(platform_driver_priv);
   platform_driver_priv = NULL;

out:
   return ret;
}

static void mtip_module_exit(void)
{
   CSMLOGINFO("mtip_module_exit called\n");

   // finalize the workq
   mtip_destroy_workq();

   // destroy the hashmap
   mtip_hashmap_destroy();

   if (!platform_driver_priv->perr)
           platform_driver_unregister(&ethernet_mac_platform_driver);

   // deregister with the dma driver
   (ecpri_dma_eth_driver_ops.ecpri_dma_eth_deregister)();

   if (mtip_rumi_platform == 0) 
   {
       // dergister with the phy driver
       mtip_phy_deregister_eth();
   }

   kfree(platform_driver_priv);
   platform_driver_priv = NULL;
   return;
}

module_init(mtip_module_init);
module_exit(mtip_module_exit);


