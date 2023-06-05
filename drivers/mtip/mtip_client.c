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

static eth_ecpriss_link_rate_e mtip_client_get_link_rate(u32 port_type)
{
    enum mtip_port_config_enum port_config = platform_driver_priv->mtip_ports[port_type]->port_config;
    eth_ecpriss_link_rate_e link_rate = ETH_ECPRISS_LINK_RATE_25;

    switch (port_config) 
    {
    case MTIP_PORT_CONFIG_1x100GBASE_R:
    case MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC_LL:
    case MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_1x100GBASE_R2:
    case MTIP_PORT_CONFIG_1x100GBASE_R2_RSFEC:
    case MTIP_PORT_CONFIG_1x100GBASE_R4:
    case MTIP_PORT_CONFIG_1x100GBASE_R4_RSFEC:
        {
            link_rate = ETH_ECPRISS_LINK_RATE_100;
        }
        break;
    case MTIP_PORT_CONFIG_1x50GBASE_R:
    case MTIP_PORT_CONFIG_1x50GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_2x50GBASE_R:
    case MTIP_PORT_CONFIG_2x50GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_1x50GBASE_R2:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_RSFEC:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_LUAI:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_LUAI_FEC:
    case MTIP_PORT_CONFIG_2x50GBASE_R2:
    case MTIP_PORT_CONFIG_2x50GBASE_R2_FEC:
    case MTIP_PORT_CONFIG_2x50GBASE_R2_LUAI:
    case MTIP_PORT_CONFIG_2x50GBASE_R2_LUAI_FEC:
        {
            link_rate = ETH_ECPRISS_LINK_RATE_50;
        }
        break;
    case MTIP_PORT_CONFIG_1x40GBASE_R4:
    case MTIP_PORT_CONFIG_1x40GBASE_R4_FEC:
        {
            link_rate = ETH_ECPRISS_LINK_RATE_40;
        }
        break;
    case MTIP_PORT_CONFIG_1x25GBASE_R:
    case MTIP_PORT_CONFIG_1x25GBASE_R_FEC:
    case MTIP_PORT_CONFIG_1x25GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_4x25GBASE_R:
    case MTIP_PORT_CONFIG_4x25GBASE_R_FEC:
    case MTIP_PORT_CONFIG_4x25GBASE_R_RSFEC:
        {
            link_rate = ETH_ECPRISS_LINK_RATE_25;
        }
        break;
    case MTIP_PORT_CONFIG_1x10GBASE_R:
    case MTIP_PORT_CONFIG_1x10GBASE_R_FEC:
    case MTIP_PORT_CONFIG_4x10GBASE_R:
    case MTIP_PORT_CONFIG_4x10GBASE_R_FEC:
        {
            link_rate = ETH_ECPRISS_LINK_RATE_10;
        }
        break;
    default:
        {
            CSMLOGERR("Unknown port config %d", port_config);
        }
        break;
    }
    
    return link_rate;
}

static eth_ecpriss_link_state_e mtip_client_get_link_state_by_link_index(u32 link_index)
{
    enum mtip_link_state_enum link_state;
    eth_ecpriss_link_state_e retval;

    link_state = mtip_get_link_state_by_link_index(link_index);

    switch (link_state) 
    {
    case MTIP_LINK_STATE_INIT:
        {
            retval = ETH_ECPRISS_LINK_STATE_INIT;
        }
        break;
    case MTIP_LINK_STATE_CLOSE:
        {
            retval = ETH_ECPRISS_LINK_STATE_CLOSE;
        }
        break;
    case MTIP_LINK_STATE_UP:
        {
            retval = ETH_ECPRISS_LINK_STATE_UP;
        }
        break;
    case MTIP_LINK_STATE_DOWN:
        {
            retval = ETH_ECPRISS_LINK_STATE_DOWN;
        }
        break;
    case MTIP_LINK_STATE_OPEN_WAITING_FOR_LANES:
    case MTIP_LINK_STATE_OPEN_DONE:
        {
            retval = ETH_ECPRISS_LINK_STATE_OPEN;
        }
        break;
    case MTIP_LINK_STATE_OPEN_FAILED:
        {
            retval = ETH_ECPRISS_LINK_STATE_DOWN;
        }
        break;
    default:
        {
            retval = ETH_ECPRISS_LINK_STATE_DOWN;
        }
        break;
    }

    CSMLOGDBG("setting link index %d link state %d to ecpri %d", link_index, link_state, retval);
    return retval;
}

static void mtip_update_topology()
{
    int i, j;
    u32 port_number = 0;
    u32 link_number = 0;
    eth_ecpriss_topology_root_s* topology;
    unsigned long flags;
    spinlock_t *lock = &platform_driver_priv->driver_lock;
    u32 port = 0;
    u32 link_index;

    CSMLOGDBG("Updating topology\n");

    spin_lock_irqsave(lock, flags);

    // get the topology pointer
    topology = platform_driver_priv->topology;

    // add check here for null pointer
    if (topology == NULL) {
        CSMLOGERR("Unable to update topology\n");
        spin_unlock_irqrestore(lock, flags);
        return;
    }

    // clear the contents of topology
    memset(topology, 0, sizeof(eth_ecpriss_topology_root_s));

    // set the init as complete
    topology->eth_topology_init_done = true;

    // set the number of unique ports to 3
    topology->num_unique_port_types = ECPRISS_MAX_UNIQUE_PORT;

    // set the three port types
    topology->topology_params[ETH_ECPRISS_PORT_TYPE_FH].port_type = ETH_ECPRISS_PORT_TYPE_FH;
    topology->topology_params[ETH_ECPRISS_PORT_TYPE_C2C].port_type = ETH_ECPRISS_PORT_TYPE_C2C;
    topology->topology_params[ETH_ECPRISS_PORT_TYPE_L2].port_type = ETH_ECPRISS_PORT_TYPE_L2;

    // go through the ports
    for (i = 0; i < MTIP_MAX_PORTS; ++i)
    {
        if (platform_driver_priv->devices.port_devices[i].port_device_valid)
        {
            switch (platform_driver_priv->devices.port_devices[i].port_type)
            {
            case MTIP_PORT_TYPE_FH_0:
            case MTIP_PORT_TYPE_FH_1:
            case MTIP_PORT_TYPE_FH_2:
                {
                    port_number = ETH_ECPRISS_PORT_TYPE_FH;
                    port = topology->topology_params[port_number].num_ports;

                    topology->topology_params[port_number].port_params[port].port_index = platform_driver_priv->devices.port_devices[i].port_type;

                    link_number = 0;

                    for (j = 0; (j < platform_driver_priv->devices.port_devices[i].num_link_phandles) && (j < MTIP_MAX_LINKS_PER_PORT) ; ++j)
                    {
                        if (platform_driver_priv->devices.port_devices[i].link_devices[j]->mac_ioaddr != NULL)
                        {
                            link_index = platform_driver_priv->devices.port_devices[i].link_devices[j]->link_index;

                            // set the link index
                            topology->topology_params[port_number].port_params[port].link_params[link_number].link_index 
                                = link_index;

                            // get the MTU that has been set in the HW register for this port, link
                            topology->topology_params[port_number].port_params[port].link_params[link_number].link_mtu = mtip_mac_get_frame_length(i, j);

                            // get the eth_addr
                            mtip_mac_get_mac_address_by_link_index(link_index, topology->topology_params[port_number].port_params[port].link_params[link_number].eth_mac_addr);

                            // set the link state
                            topology->topology_params[port_number].port_params[port].link_params[link_number].link_state = mtip_client_get_link_state_by_link_index(link_index);

                            // set the link rate
                            topology->topology_params[port_number].port_params[port].link_params[link_number].link_rate = mtip_client_get_link_rate(platform_driver_priv->devices.port_devices[i].port_type);

                            // increment the link number
                            ++link_number;
                        }

                        // set the num links
                        topology->topology_params[port_number].port_params[port].num_links = platform_driver_priv->devices.port_devices[i].num_link_phandles;
                    }

                    // increment the FH port type
                    ++topology->topology_params[port_number].num_ports;
                }
                break;
            case MTIP_PORT_TYPE_L2:
                {
                    port_number = ETH_ECPRISS_PORT_TYPE_L2;
                    port = topology->topology_params[port_number].num_ports;

                    topology->topology_params[port_number].port_params[port].port_index = platform_driver_priv->devices.port_devices[i].port_type;

                    link_number = 0;

                    for (j = 0; (j < platform_driver_priv->devices.port_devices[i].num_link_phandles) && (j < MTIP_MAX_LINKS_PER_PORT); ++j)
                    {
                        if (platform_driver_priv->devices.port_devices[i].link_devices[j]->mac_ioaddr != NULL)
                        {
                            link_index = platform_driver_priv->devices.port_devices[i].link_devices[j]->link_index;

                            // set the link index
                            topology->topology_params[port_number].port_params[port].link_params[link_number].link_index 
                                = link_index;

                            // get the MTU that has been set in the HW register for this port, link
                            topology->topology_params[port_number].port_params[port].link_params[link_number].link_mtu = mtip_mac_get_frame_length(i, j);

                            // get the eth_addr
                            mtip_mac_get_mac_address_by_link_index(link_index, topology->topology_params[port_number].port_params[port].link_params[link_number].eth_mac_addr);

                            // set the link state
                            topology->topology_params[port_number].port_params[port].link_params[link_number].link_state = mtip_client_get_link_state_by_link_index(link_index);

                            // set the link rate
                            topology->topology_params[port_number].port_params[port].link_params[link_number].link_rate = ETH_ECPRISS_LINK_RATE_25;

                            // increment the link number
                            ++link_number;
                        }

                        // set the num links
                        topology->topology_params[port_number].port_params[port].num_links = platform_driver_priv->devices.port_devices[i].num_link_phandles;
                    }

                    // increment the FH port type
                    ++topology->topology_params[port_number].num_ports;
                }
                break;
            case MTIP_PORT_TYPE_DEBUG:
            default:
                {
                    CSMLOGDBG("Ignoring port of type: %d", platform_driver_priv->devices.port_devices[i].port_type);
                }
                break;
            }
        }
    }

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

   CSMLOGDBG("Sending Ready to all registered clients\n");

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
   if(taskstruct == NULL)
   {
	CSMLOGERR("memory alloc failed\n");
	return;
   }
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

   CSMLOGDBG("Sending Event to all registered clients\n");

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

void mtip_print_topology(eth_ecpriss_topology_root_s *topology)
{
    uint8_t i, j, k;
    uint8_t                        num_unique_port_types;
    eth_ecpriss_port_type_e        port_type;
    uint8_t                        num_ports;
    uint8_t                        port_index;
    uint8_t                        num_links;
    uint8_t                        link_index;
    uint16_t                       link_mtu;
    uint16_t                       link_state;
    eth_ecpriss_link_rate_e        link_rate;

    num_unique_port_types = topology->num_unique_port_types;

    // log the information here
    CSMLOGINFO("eth_topology_init_done %d", topology->eth_topology_init_done);
    CSMLOGINFO("num_unique_port_types %d", num_unique_port_types);

    for (i = 0; i < num_unique_port_types; ++i)
    {
        port_type = topology->topology_params[i].port_type;
        num_ports = topology->topology_params[i].num_ports;

        // print the topology->topology_params[i]
        CSMLOGINFO("index: %d, port_type: %d, num_ports: %d", i, port_type, num_ports);

        for (j = 0; j < num_ports; ++j) 
        {
            port_index = topology->topology_params[i].port_params[j].port_index;
            num_links = topology->topology_params[i].port_params[j].num_links;

            // print the topology->topology_params[i].port_params[j]
            CSMLOGINFO("index: (%d, %d) port_index: %d, num_links: %d", i, j, port_index, num_links);

            for (k = 0; k < num_links; ++k) 
            {
                link_index = topology->topology_params[i].port_params[j].link_params[k].link_index;
                link_mtu = topology->topology_params[i].port_params[j].link_params[k].link_mtu;
                link_state = topology->topology_params[i].port_params[j].link_params[k].link_state;
                link_rate = topology->topology_params[i].port_params[j].link_params[k].link_rate;

                // print the topology->topology_params[i].port_params[j].link_params[k]
                CSMLOGINFO("index: (%d, %d, %d) link_index: %d, link_mtu: %d, link_state: %d, link_rate: %d ", i, j, k, link_index, link_mtu, link_state, link_rate);
            }
        }
    }
}

/*
    Use the available port information to update the topology
 */
int mtip_setup_topology(void)
{
    eth_ecpriss_topology_root_s* topology;

    CSMLOGDBG("setting up initial topology\n");

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

        memcpy(topology_params, platform_driver_priv->topology, sizeof(eth_ecpriss_topology_root_s));

        ret = ETH_ECPRISS_STATUS_SUCCESS;

        CSMLOGDBG("Device mode is %d, ret is %d", *device_mode, ret);
    }
    else
    {
        CSMLOGINFO("topology is NULL ret: %d", ret);
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

