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
#include "mtip_phy.h"
#include "eth_phy_iface.h"
#include "mtip_mac.h"
#include "mtip_pcs.h"
#include "mtip_workq.h"
#include "mtip_sysfs.h"

struct eth_phy_iface_eth_register_params mtip_phy_eth_params;

extern struct eth_phy_iface_ops qcom_aw_phy_driver_iface_ops;

/* 
 * qsfp_eth_get_link_type: returns sfp port type
 * based on values defined in ethtool.h
#define PORT_TP            0x00
#define PORT_AUI           0x01
#define PORT_MII           0x02
#define PORT_FIBRE         0x03
#define PORT_BNC           0x04
#define PORT_DA            0x05
#define PORT_NONE          0xef
#define PORT_OTHER         0xff
 */ 
extern int qsfp_eth_get_link_type(u32 qsfp_phandle, u8* link_info);

// PCS level retry delay to bring up PHY lane
#define MTIP_PHY_RETRY_TIMER     10000
#define MTIP_PHY_RETRY_MIN_TIMER     100

static void mtip_phy_ready_cb(void *user_data)
{
    CSMLOGINFO("Got the PHY ready cb\n");

    if (platform_driver_priv->phy_is_ready == false) 
    {
        // TBD: do we wait for both DMA and PHY?
    }

    // set the phy_is_ready flag
    platform_driver_priv->phy_is_ready = true;
    return;
}

static void mtip_phy_an_complete_cb(enum mtip_port_type_enum port_type, enum eth_phy_iface_phy_lane_num_enum lane_num)
{
    CSMLOGINFO("Got AN complete CB for port: %d\n", port_type);

    // TBD: we need AN complete for all lanes of a link

    return;
}

static int mtip_phy_get_link_index_for_phy_lane(
    enum mtip_port_type_enum port_type, enum eth_phy_iface_phy_lane_num_enum lane_num)
{
    int i,j,k;
    u32 num_lanes;

    for(i = 0; i < MTIP_MAX_PORTS; i++){
      if(platform_driver_priv->devices.port_devices[i].port_type == port_type){
        for(j = 0; j < MTIP_MAX_LINKS_PER_PORT; j++){
          num_lanes = platform_driver_priv->devices.port_devices[i].link_devices[j].num_lanes;
          for (k = 0; k < num_lanes; k++){
            if(platform_driver_priv->devices.port_devices[i].link_devices[j].lanes[k] == lane_num)
              return platform_driver_priv->devices.port_devices[i].link_devices[j].link_index;
          }
        }
      }
    }

    return -1;
}

static void mtip_phy_cdr_lock_cb(enum mtip_port_type_enum port_type, enum eth_phy_iface_phy_lane_num_enum lane_num, bool status)
{
    int link_index = -1;
    struct mtip_delayed_work_q_params *wq_params;
    int delay_ms = MTIP_PHY_RETRY_MIN_TIMER;

    CSMLOGERR("CDR lock callback for port: %d, lane %d, status %d\n", port_type, lane_num, status);

    link_index = mtip_phy_get_link_index_for_phy_lane(port_type, lane_num);
    if(link_index == -1){
      CSMLOGERR("Index not found\n");
      return;
    }

    if(status == true)
      delay_ms = MTIP_PHY_RETRY_TIMER;

    if(mtip_mac_wrapper_get_link_status(link_index) == false){
      wq_params = kmalloc(sizeof(struct mtip_delayed_work_q_params),
                          GFP_ATOMIC);
      if(!wq_params)
        CSMLOGERR("Malloc failed!");
      else{
        INIT_DELAYED_WORK(&wq_params->wq_item,
                          mtip_phy_retry_phy_bringup);
        wq_params->port_type = port_type;
        wq_params->link_index = link_index;
        mtip_workq_queue_delayed_work(wq_params, delay_ms);
      }
    }
    else{
      post_mtip_process_link_state(link_index, true);
    }
    return;
}


int mtip_phy_register_eth(void)
{
    int res = 0;
    bool is_ready = false;
    mtip_phy_eth_params.notify_an_complete = mtip_phy_an_complete_cb;
    mtip_phy_eth_params.userdata_ready = NULL;
    mtip_phy_eth_params.notify_ready = mtip_phy_ready_cb;
    mtip_phy_eth_params.cdr_lock_cb = mtip_phy_cdr_lock_cb;

    // register with the PHY
    res = (qcom_aw_phy_driver_iface_ops.eth_phy_iface_eth_register)(&mtip_phy_eth_params, &is_ready);

    if (res < 0) 
    {
        CSMLOGERR("Failed to register with PHY: %d\n", res);
        return res;
    }

    // check if PHY is ready
    if (is_ready)
    {
        platform_driver_priv->phy_is_ready = true;
    }
    return 0;
}

int mtip_phy_deregister_eth(void)
{
    CSMLOGINFO("Deregistering with the phy driver\n");

    // deregister with the PHY driver
    (qcom_aw_phy_driver_iface_ops.eth_phy_iface_eth_deregister)();

    return 0;
}

int mtip_phy_setup_phy(struct mtip_port_device_info* port_device)
{
    // setup the phy for the port
    // pass the consolidated lane config of the port to phy
    return (qcom_aw_phy_driver_iface_ops.eth_phy_iface_phy_setup)(port_device->port_type, port_device->lane_config);
}

static void mtip_phy_get_lanes_of_link(u32 link_index, bool lanes_enabled[PHY_LANE_MAX])
{
    u32 port_device_index;
    u32 link_device_index;
    u32 num_lanes;
    int i;
    u32 lane;
    int lane_count = 0;

    if (mtip_lookup_device_by_link_index(link_index, &port_device_index, &link_device_index) < 0)
    {
        CSMLOGERR("Unable to find device for link index: %d\n", link_index);
        return;
    }

    num_lanes = platform_driver_priv->devices.port_devices[port_device_index].link_devices[link_device_index].num_lanes;

    for (i = 0; i < PHY_LANE_MAX; ++i)
    {
        lanes_enabled[i] = false;
    }

    for (i = 0; i < num_lanes; ++i)
    {
        lane = platform_driver_priv->devices.port_devices[port_device_index].link_devices[link_device_index].lanes[i];
        lanes_enabled[lane] = true;
        ++lane_count;
    }
    CSMLOGINFO("lane count of link_index: %d is %d\n", link_index, lane_count);
    return;
}

void mtip_phy_retry_phy_bringup(struct work_struct *work)
{
    struct delayed_work *delayed_work_item = to_delayed_work(work);
    struct mtip_delayed_work_q_params *wq_params =
        container_of(delayed_work_item, struct mtip_delayed_work_q_params, wq_item);

    if(platform_driver_priv->mtip_links[wq_params->link_index]->state == MTIP_LINK_STATE_CLOSE)
    {
      goto func_exit;
    }

    if(mtip_mac_wrapper_get_link_status(wq_params->link_index) == true)
    {
      post_mtip_process_link_state(wq_params->link_index, true);
      goto func_exit;
    }

    CSMLOGINFO("mtip_phy_retry_phy_bringup with link: %d, port_type: %d\n",
               wq_params->link_index, wq_params->port_type);

    mtip_phy_teardown_phy(wq_params->link_index);
    mtip_phy_bringup_phy(wq_params->link_index,
         platform_driver_priv->mtip_ports[wq_params->port_type]->sfp_port_type);

func_exit:
    kfree(wq_params);
    return;
}

int mtip_phy_bringup_phy(u32 link_index, int sfp_port_type)
{
    enum mtip_port_type_enum port_type;
    bool lanes_enabled[PHY_LANE_MAX];
    u32 port_device_index;
    u32 link_device_index;

    CSMLOGINFO("calling phy_bringup with link: %d, port_type: %d\n", link_index, sfp_port_type);

    if (mtip_lookup_device_by_link_index(link_index, &port_device_index, &link_device_index) < 0)
    {
        CSMLOGERR("Unable to find device for link index: %d\n", link_index);
        return -1;
    }

    port_type = platform_driver_priv->devices.port_devices[port_device_index].port_type;

    mtip_phy_get_lanes_of_link(link_index, lanes_enabled);

    // bringup the phy for the specified lanes
    return (qcom_aw_phy_driver_iface_ops.eth_phy_iface_phy_bringup)(port_type, lanes_enabled, sfp_port_type);
}

int mtip_phy_teardown_phy(u32 link_index)
{
    enum mtip_port_type_enum port_type;
    bool lanes_enabled[PHY_LANE_MAX];
    u32 port_device_index;
    u32 link_device_index;
    int ret_val = 0;

    if (mtip_lookup_device_by_link_index(link_index, &port_device_index, &link_device_index) < 0)
    {
        CSMLOGERR("Unable to find device for link index: %d\n", link_index);
        return -1;
    }

    port_type = platform_driver_priv->devices.port_devices[port_device_index].port_type;

    mtip_phy_get_lanes_of_link(link_index, lanes_enabled);

    // teardown the phy for the specified lanes
    ret_val = (qcom_aw_phy_driver_iface_ops.eth_phy_iface_phy_teardown)(port_type, lanes_enabled);

    // disable tx_rx on the link
    post_mtip_process_link_state(link_index, false);
    return ret_val;
}

int mtip_phy_notify_link_status(u32 link_index, bool status)
{
    enum mtip_port_type_enum port_type;
    bool lanes_enabled[PHY_LANE_MAX];
    u32 port_device_index;
    u32 link_device_index;

    if (mtip_lookup_device_by_link_index(link_index, &port_device_index, &link_device_index) < 0)
    {
        CSMLOGERR("Unable to find device for link index: %d\n", link_index);
        return -1;
    }

    port_type = platform_driver_priv->devices.port_devices[port_device_index].port_type;

    mtip_phy_get_lanes_of_link(link_index, lanes_enabled);

    // notify PHY of the link status
    return (qcom_aw_phy_driver_iface_ops.eth_phy_iface_notify_mac_link_status)(port_type, lanes_enabled, status);
}

static int mtip_phy_find_matching_port(struct phylink_config *config, u32* real_port_number)
{
    struct mtip_portdev_priv* priv;
    struct net_device* dev = to_net_dev(config->dev);

    priv = netdev_priv(dev);

    *real_port_number = priv->port_type;
    return 0;
}

static void mtip_phy_phy_validate(struct phylink_config *config,
                           unsigned long *supported,
                           struct phylink_link_state *state) 
{
    u32 real_port_number;
    int ret;

    ret = mtip_phy_find_matching_port(config, &real_port_number);

    if (ret < 0) 
    {
        CSMLOGERR("failed to find matching port for config: 0x%lx\n", (unsigned long)config);
    }
    else
    {
        CSMLOGINFO("phy_validate found matching port: %d\n", real_port_number);
    }

    CSMLOGINFO("phy validate ops received\n");

    return;
}

static void mtip_phy_get_link_state(struct phylink_config *config,
				 struct phylink_link_state *state)
{
    u32 real_port_number;
    int ret;

    ret = mtip_phy_find_matching_port(config, &real_port_number);

    if (ret < 0) 
    {
        CSMLOGERR("failed to find matching port for config: 0x%lx\n", (unsigned long)config);
        return;
    }
    else
    {
        CSMLOGINFO("get_link_state found matching port: %d\n", real_port_number);
    }

    // indicate that the mac pcs state is up
    state->link = 1;

    CSMLOGINFO("mtip_mac_link_state %d\n", state->link);

	return;
}

static void mtip_phy_config(struct phylink_config *config,
                     unsigned int mode,
                     const struct phylink_link_state *state) 
{
    u32 real_port_number;
    int ret;
    unsigned int an_enabled;

    ret = mtip_phy_find_matching_port(config, &real_port_number);

    if (ret < 0) 
    {
        CSMLOGERR("failed to find matching port for config: 0x%lx\n", (unsigned long)config);
        return;
    }
    else
    {
        CSMLOGINFO("config found matching port: %d\n", real_port_number);
    }

    an_enabled = state->an_enabled;

    CSMLOGINFO("phy config ops received with an_enabled: %d\n", an_enabled);

   return;
}

static void mtip_phy_link_up(struct phylink_config *config,
                      struct phy_device *phy, unsigned int mode,
                      phy_interface_t interface, int speed,
                      int duplex, bool tx_pause, bool rx_pause) 
{
    u32 real_port_number;
    u32 i;
    int ret;
    u32 current_state;
    u32 link_index;
    u32 port_device_index;
    u32 link_device_index;
    enum mtip_link_state_enum link_state;
    u8  sfp_port_type = 0;
    int sfp_phandle;
    struct mtip_port_device_info* port_device = NULL;
    struct mtip_link_device_info* link_device = NULL;

    ret = mtip_phy_find_matching_port(config, &real_port_number);

    if (ret < 0) 
    {
        CSMLOGERR("failed to find matching port for config: 0x%lx\n", (unsigned long)config);
        return;
    }
    else
    {
        CSMLOGINFO("link_up found matching port: %d\n", real_port_number);
    }

    CSMLOGINFO("phy link up ops received\n");

    // print the data passed
    CSMLOGERR("mode: %d, interface: %d, speed: %d, duplex: %d, tx_pause: %d, rx_pause: %d\n", mode, (unsigned int)interface, speed, duplex, tx_pause, rx_pause);

    // /lookup the sfp_port_type of the port
    sfp_phandle = platform_driver_priv->mtip_ports[real_port_number]->sfp_phandle;

    if (sfp_phandle < 0) 
    {
        CSMLOGERR("Got an unexpected link event! port: %d\n", real_port_number);
        return;
    }

    current_state = platform_driver_priv->mtip_ports[real_port_number]->port_state;

    // ask the qsfp driver for the port type
    qsfp_eth_get_link_type(sfp_phandle, &sfp_port_type);

    CSMLOGINFO("sfp_port_type %d, associated with port %d", sfp_port_type, real_port_number);

    // update the sfp port type
    platform_driver_priv->mtip_ports[real_port_number]->sfp_port_type = sfp_port_type;

    // set the port_device
    port_device = &platform_driver_priv->devices.port_devices[real_port_number];

    // deal with the phy_port_type as appropriate
    if (sfp_port_type == PORT_FIBRE)
    {
        // handle the case where FIBRE is connected
        mtip_mac_wrapper_enable_rsfec_for_25g_mode(port_device);

        // enable rsfec in the pcs
        for (i = 0; i < port_device->num_link_phandles; ++i)
        {
            link_device = &port_device->link_devices[i];
            mtip_pcs_enable_rsfec_for_25g_mode(link_device);
        }
    }
    else
    {
        // handle the case where DAC or OTHER is connected
        mtip_mac_wrapper_disable_rsfec_for_25g_mode(port_device);

        // disable rsfec in pcs
        for (i = 0; i < port_device->num_link_phandles; ++i)
        {
            link_device = &port_device->link_devices[i];
            mtip_pcs_disable_rsfec_for_25g_mode(link_device);
        }
    }

    switch (current_state) 
    {
    case MTIP_PORT_STATE_INIT:
        {
            CSMLOGINFO("Handling transition from INIT to CONNECTED for port: %d", real_port_number);

            // new state is CONNECTED
            platform_driver_priv->mtip_ports[real_port_number]->port_state = MTIP_PORT_STATE_CONNECTED;

            // go through all the links of the port that are in OPEN state
            for (i = 0; i < MTIP_MAX_LINKS_PER_PORT; ++i) 
            {
                if (mtip_lookup_link_index_by_real_port_and_link(&link_index, real_port_number, i) == 0)
                {
                    if (mtip_lookup_device_by_link_index(link_index, &port_device_index, &link_device_index) == 0)
                    {
                        link_state = mtip_get_link_state_by_device(port_device_index, link_device_index);

                        if (link_state == MTIP_LINK_STATE_OPEN) 
                        {
                            CSMLOGINFO("Port: %d with link_index: %d in OPEN state\n", real_port_number, link_index);

                            // bring up the phy
                           mtip_phy_bringup_phy(link_index, sfp_port_type);

                           CSMLOGINFO("phy bringup done for link: %d\n", link_index);
                        }
                    }
                }
            }
        }
        break;

    case MTIP_PORT_STATE_CONNECTED:
        {
            CSMLOGINFO("Handling transition from CONNECTED to CONNECTED for port: %d", real_port_number);
            platform_driver_priv->mtip_ports[real_port_number]->port_state = MTIP_PORT_STATE_CONNECTED;
        }
        break;

    case MTIP_PORT_STATE_DISCONNECTED:
        {
            CSMLOGINFO("Handling transition from DISCONNECTED to CONNECTED for port: %d", real_port_number);

            // new state is CONNECTED
            platform_driver_priv->mtip_ports[real_port_number]->port_state = MTIP_PORT_STATE_CONNECTED;

            // go through all the links of the port that are in OPEN or DOWN state
            for (i = 0; i < MTIP_MAX_LINKS_PER_PORT; ++i) 
            {
                if (mtip_lookup_link_index_by_real_port_and_link(&link_index, real_port_number, i) == 0)
                {
                    if (mtip_lookup_device_by_link_index(link_index, &port_device_index, &link_device_index) == 0)
                    {
                        link_state = mtip_get_link_state_by_device(port_device_index, link_device_index);

                        if ((link_state == MTIP_LINK_STATE_OPEN) || (link_state == MTIP_LINK_STATE_DOWN))
                        {
                            CSMLOGINFO("Port: %d with link_index: %d in %d state\n", real_port_number, link_index, link_state);

                            // bring up the phy
                           mtip_phy_bringup_phy(link_index, sfp_port_type);

                           CSMLOGINFO("phy bringup done for link: %d\n", link_index);
                        }
                    }
                }
            }
        }
        break;

    default:
        {
            CSMLOGINFO("Handling transition from unknown to CONNECTED for port: %d", real_port_number);
            platform_driver_priv->mtip_ports[real_port_number]->port_state = MTIP_PORT_STATE_CONNECTED;
        }
        break;
    }

   return;
}

static void mtip_phy_link_down(struct phylink_config *config, unsigned int mode,
                                phy_interface_t interface) 
{
    u32 real_port_number;
    int ret;
    u32 current_state;
    int i;
    u32 link_index;
    u32 port_device_index;
    u32 link_device_index;
    enum mtip_link_state_enum link_state;
    int sfp_phandle;

    ret = mtip_phy_find_matching_port(config, &real_port_number);

    if (ret < 0) 
    {
        CSMLOGERR("failed to find matching port for config: 0x%lx\n", (unsigned long)config);
        return;
    }
    else
    {
        CSMLOGINFO("link_down found matching port: %d\n", real_port_number);
    }

    CSMLOGINFO("phy link down ops received\n");

    // /lookup the sfp_port_type of the port
    sfp_phandle = platform_driver_priv->mtip_ports[real_port_number]->sfp_phandle;

    if (sfp_phandle < 0) 
    {
        CSMLOGERR("Got an unexpected link event! port: %d\n", real_port_number);
        return;
    }

    current_state = platform_driver_priv->mtip_ports[real_port_number]->port_state;

    switch (current_state) 
    {
    case MTIP_PORT_STATE_INIT:
        {
            CSMLOGINFO("Handling transition from INIT to    DISCONNECTED for port: %d", real_port_number);
            platform_driver_priv->mtip_ports[real_port_number]->port_state = MTIP_PORT_STATE_DISCONNECTED;
        }
        break;

    case MTIP_PORT_STATE_CONNECTED:
        {
            CSMLOGINFO("Handling transition from CONNECTED to DISCONNECTED for port: %d", real_port_number);
            platform_driver_priv->mtip_ports[real_port_number]->port_state = MTIP_PORT_STATE_DISCONNECTED;

            // go through all the links of the port that are in UP or DOWN state
            for (i = 0; i < MTIP_MAX_LINKS_PER_PORT; ++i) 
            {
                if (mtip_lookup_link_index_by_real_port_and_link(&link_index, real_port_number, i) == 0)
                {
                    if (mtip_lookup_device_by_link_index(link_index, &port_device_index, &link_device_index) == 0)
                    {
                        link_state = mtip_get_link_state_by_device(port_device_index, link_device_index);

                        if ((link_state == MTIP_LINK_STATE_UP) || (link_state == MTIP_LINK_STATE_DOWN))
                        {
                            CSMLOGINFO("Port: %d with link_index: %d in %d state\n", real_port_number, link_index, link_state);

                            // teardown the phy
                            mtip_phy_teardown_phy(link_index);

                            CSMLOGINFO("phy teardown done for link: %d\n", link_index);
                        }
                    }
                }
            }
        }
        break;

    case MTIP_PORT_STATE_DISCONNECTED:
        {
            CSMLOGINFO("Handling transition from DISCONNECTED to DISCONNECTED for port: %d", real_port_number);
            platform_driver_priv->mtip_ports[real_port_number]->port_state = MTIP_PORT_STATE_DISCONNECTED;
        }
        break;

    default:
        {
            CSMLOGINFO("Handling transition from unknown to CONNECTED for port: %d", real_port_number);
            platform_driver_priv->mtip_ports[real_port_number]->port_state = MTIP_PORT_STATE_DISCONNECTED;
        }
        break;
    }
   return;
}

static const struct phylink_mac_ops mtip_phylink_mac_ops = {
	.validate = mtip_phy_phy_validate,
	.mac_pcs_get_state = mtip_phy_get_link_state,
	.mac_config = mtip_phy_config,
	.mac_link_up = mtip_phy_link_up,
	.mac_link_down = mtip_phy_link_down,
};

static void mtip_phy_port_netdevice_init(struct net_device *dev) 
{
   CSMLOGINFO("dummy netdev init for 0x%lx\n", (unsigned long)dev);
}

int mtip_phy_create_phylink(struct mtip_port_device_info* port_device)
{
    phy_interface_t mode;
    u32 port_type = port_device->port_type;
    struct platform_device* port_pdev = port_device->port_pdev;
    struct mtip_port_info* port_info;
    struct mtip_portdev_priv* priv;

    // allocate the mtip_port_info for the port_type
    port_info = (struct mtip_port_info*)kmalloc(sizeof(struct mtip_port_info), GFP_KERNEL);

    // initialize the lock
    spin_lock_init(&port_info->lock);

    // set the sfp_phandle from port_device
    port_info->sfp_phandle = port_device->sfp_phandle;

    // set the port info
    platform_driver_priv->mtip_ports[port_type] = port_info;

    // check if there is a valid sfp_handle associated with the port
    if (port_device->sfp_phandle < 0) 
    {
        CSMLOGINFO("port sfp_handle is not present\n");

        // set port state as CONNECTED and return
        port_info->port_state = MTIP_PORT_STATE_CONNECTED;
        return 0;
    }

    if (mtip_loopback_mode != MTIP_MODE_DEFAULT)
    {
        // we are not using phylink for PCS loopback or
        // near end loopback
        // set port state as CONNECTED and return
        port_info->port_state = MTIP_PORT_STATE_CONNECTED;
        return 0;
    }

    // for E2E set the port state as INIT
    // this will be set to CONNECTED on receiving a link up
    port_info->port_state = MTIP_PORT_STATE_INIT;

    port_info->port_dummy_ndev = alloc_netdev(sizeof(struct mtip_portdev_priv), "port%d", NET_NAME_ENUM, mtip_phy_port_netdevice_init);

    SET_NETDEV_DEV(port_info->port_dummy_ndev, &port_pdev->dev);

    priv = netdev_priv(port_info->port_dummy_ndev);
    priv->port_type = port_type;

    /* PHYLINK setup */
	port_info->phylink_config.dev = &port_info->port_dummy_ndev->dev;
	port_info->phylink_config.type = PHYLINK_NETDEV;
	of_get_phy_mode(port_pdev->dev.of_node, &mode);

	port_info->phylink = phylink_create(&port_info->phylink_config, of_fwnode_handle(port_pdev->dev.of_node),
	                         mode, &mtip_phylink_mac_ops);

    CSMLOGINFO("got phylink 0x%lx\n", port_info->phylink);

	if (IS_ERR(port_info->phylink))
	{
		CSMLOGERR("PHYLINK creation failed with err = %d", PTR_ERR(port_info->phylink));
		return IS_ERR(port_info->phylink);
	}

    CSMLOGINFO("phylink create done\n");

    // start has to be done in rtnl context
    rtnl_lock();

    // start the phylink
    phylink_start(port_info->phylink);

    // start has to be done in rtnl context
    rtnl_unlock();

    CSMLOGINFO("phylink start done\n");

    return 0;
}


