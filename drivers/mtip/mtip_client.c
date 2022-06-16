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

#include "mtip.h"
#include "mtip_client.h"
#include "mtip_workq.h"
#include "mtip_mac.h"

static void mtip_update_topology()
{
    int i, j;
    u32 port_number = 0;
    u32 link_number = 0;
    eth_ecpriss_topology_root_s* topology;
    unsigned long flags;
    spinlock_t *lock = &platform_driver_priv->driver_lock;
    u32 port = 0;

    CSMLOGINFO("Updating topology\n");

    spin_lock_irqsave(lock, flags);

    // get the topology pointer
    topology = platform_driver_priv->topology;

    // add check here for null pointer
    if (topology == NULL) {
        CSMLOGINFO("Unable to update topology\n");
        spin_unlock_irqrestore(lock, flags);
        return;
    }

    // go through the ports
    for (i = 0; i < platform_driver_priv->devices.num_port_phandles; ++i)
    {
        topology->topology_params[port_number].port_type = platform_driver_priv->devices.port_devices[i].port_type;
        topology->topology_params[port_number].num_ports = 1; // only one port of each type for now

        // set the port params of the first and only port
        port = 0;

        topology->topology_params[port_number].port_params[port].port_index = platform_driver_priv->devices.port_devices[i].port_type;

        link_number = 0;

        for (j = 0; j < platform_driver_priv->devices.port_devices[i].num_link_phandles; ++j)
        {
            if (platform_driver_priv->devices.port_devices[i].link_devices[j].mac_ioaddr != NULL)
            {
                // set the link index
                topology->topology_params[port_number].port_params[port].link_params[link_number].link_index 
                    = platform_driver_priv->devices.port_devices[i].link_devices[j].link_index;

                // get the MTU that has been set in the HW register for this port, link
                topology->topology_params[port_number].port_params[port].link_params[link_number].link_mtu = mtip_mac_get_frame_length(i, j);

                // get the eth_addr
                mtip_mac_get_mac_address_by_device(i, j, topology->topology_params[port_number].port_params[port].link_params[link_number].eth_mac_addr);

                // set the link state
                topology->topology_params[port_number].port_params[port].link_params[link_number].link_state = mtip_get_link_state_by_device(i, j);

                // set the link rate
                topology->topology_params[port_number].port_params[port].link_params[link_number].link_rate = ETH_ECPRISS_LINK_RATE_25;

                // increment the link number
                ++link_number;
            }
        }

        // set the num links
        topology->topology_params[port_number].port_params[port].num_links = platform_driver_priv->devices.port_devices[i].num_link_phandles;
    }

    // set the number of ports
    topology->num_unique_port_types = platform_driver_priv->devices.num_port_phandles;

    spin_unlock_irqrestore(lock, flags);
}

void post_mtip_client_send_ready(void)
{
   struct mtip_send_ready_task* taskstruct = kmalloc(sizeof(struct mtip_send_ready_task), GFP_ATOMIC);
   mtip_queue_work(MTIP_WORKQ_TASK_INDICATE_READY, taskstruct);
}

void run_mtip_client_send_ready(void* work_ptr)
{
   int i;
   struct mtip_send_ready_task* taskstruct = (struct mtip_send_ready_task*)work_ptr;
   unsigned long flags;
   spinlock_t *lock = &platform_driver_priv->driver_lock;
   eth_ecpriss_topology_ready_cb ready_cb = NULL;

   // update the topology since something might have changed
   mtip_update_topology();

   CSMLOGINFO("Sending Ready to all registered clients\n");

   for (i = 0; i < MTIP_MAX_CLIENTS; ++i)
   {
       spin_lock_irqsave(lock, flags);

       ready_cb = platform_driver_priv->clients[i].ready_cb;

       spin_unlock_irqrestore(lock, flags);

       if (ready_cb != NULL)
       {
           // invoke the client cb
           (*ready_cb)();
       }
   }

   // free the taskstruct
   kfree(taskstruct);
}

void post_mtip_client_send_event(eth_ecpriss_event_e event, u32 link_index)
{
   struct mtip_send_event_task* taskstruct = kmalloc(sizeof(struct mtip_send_event_task), GFP_ATOMIC);
   taskstruct->event = event;
   taskstruct->link_index = link_index;

   mtip_queue_work(MTIP_WORKQ_TASK_INDICATE_EVENT, taskstruct);
}

void run_mtip_client_send_event(void* work_ptr)
{
   int i;
   struct mtip_send_event_task* taskstruct = (struct mtip_send_event_task*)work_ptr;
   unsigned long flags;
   spinlock_t *lock = &platform_driver_priv->driver_lock;
   eth_ecpriss_interface_events_cb events_cb = NULL;

   // update the topology since something might have changed
   mtip_update_topology();

   CSMLOGINFO("Sending Event to all registered clients\n");

   for (i = 0; i < MTIP_MAX_CLIENTS; ++i)
   {
       spin_lock_irqsave(lock, flags);

       events_cb = platform_driver_priv->clients[i].events_cb;

       spin_unlock_irqrestore(lock, flags);

       if (events_cb != NULL)
       {
           // invoke the client cb
           (*events_cb)(taskstruct->event, NULL);
       }
   }

   // free the taskstruct
   kfree(taskstruct);
}


/*
    Use the available port information to update the topology
 */
int mtip_setup_topology(void)
{
    eth_ecpriss_topology_root_s* topology;

    CSMLOGINFO("setting up initial topology\n");

    // allocate the memory for the topology structure
    topology = (eth_ecpriss_topology_root_s*)kmalloc(sizeof(eth_ecpriss_topology_root_s), GFP_KERNEL);

    // set the platform topology
    platform_driver_priv->topology = topology;

    // set the initial topology
    mtip_update_topology();

    return 0;
}

/*
    The exported function to get the current topology
 */
eth_ecpriss_status_e mtip_eth_get_topology(eth_ecpriss_dev_mode_e *device_mode, eth_ecpriss_topology_root_s *topology_params)
{
    eth_ecpriss_status_e ret = ETH_ECPRISS_STATUS_FAILURE;
    unsigned long flags;
    spinlock_t *lock = &platform_driver_priv->driver_lock;
    eth_ecpriss_topology_root_s* topology = NULL;

    spin_lock_irqsave(lock, flags);

    topology = platform_driver_priv->topology;

    spin_unlock_irqrestore(lock, flags);

    if (topology != NULL)
    {
        *device_mode = (eth_ecpriss_dev_mode_e)platform_driver_priv->devices.mode;

        memcpy(topology_params, platform_driver_priv->topology, sizeof(eth_ecpriss_topology_params_s));

        ret = ETH_ECPRISS_STATUS_SUCCESS;
    }

    return ret;
}

eth_ecpriss_status_e mtip_eth_register_events_cb(eth_ecpriss_interface_events_cb events_cb)
{
    eth_ecpriss_status_e ret = ETH_ECPRISS_STATUS_FAILURE;
    int i;
    unsigned long flags;
    spinlock_t *lock = &platform_driver_priv->driver_lock;

    spin_lock_irqsave(lock, flags);

    // find the next open spot
    for (i = 0; i < MTIP_MAX_CLIENTS; ++i) {

        if (platform_driver_priv->clients[i].events_cb == NULL) {
            platform_driver_priv->clients[i].events_cb = events_cb;
            ret = ETH_ECPRISS_STATUS_SUCCESS;
        }
    }

    spin_unlock_irqrestore(lock, flags);
    return ret;
}

eth_ecpriss_status_e mtip_eth_register_ready_cb(eth_ecpriss_topology_ready_cb ready_cb, bool *is_ready)
{
    eth_ecpriss_status_e ret = ETH_ECPRISS_STATUS_FAILURE;
    int i;
    unsigned long flags;
    spinlock_t *lock = &platform_driver_priv->driver_lock;

    spin_lock_irqsave(lock, flags);

    // find the next open spot
    for (i = 0; i < MTIP_MAX_CLIENTS; ++i) {

        if (platform_driver_priv->clients[i].ready_cb == NULL) {
            platform_driver_priv->clients[i].ready_cb = ready_cb;

            // check if we are ready to handle get requests
            if (platform_driver_priv->topology != NULL) {
                *is_ready = true;
            }
            else
            {
                *is_ready = false;
            }
            ret = ETH_ECPRISS_STATUS_SUCCESS;
        }
    }

    spin_unlock_irqrestore(lock, flags);
    return ret;
}

struct eth_ecpriss_ops mtip_ecpri_ops = {
    .eth_ecpriss_register_ready_cb = mtip_eth_register_ready_cb,
    .eth_ecpriss_register_events_cb = mtip_eth_register_events_cb,
    .eth_ecpriss_get_topology = mtip_eth_get_topology,
};

EXPORT_SYMBOL(mtip_ecpri_ops);

