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
#include <linux/of_net.h>

#include "mtip.h"
#include "mtip_device.h"
#include "mtip_phy.h"
#include "eth_phy_iface.h"
#include "mtip_mac.h"
#include "mtip_pcs.h"
#include "mtip_workq.h"
#include "mtip_sysfs.h"
#include "mtip_ethtool.h"
#include "mtip_notifr.h"

extern struct mtip_delayed_work_q_params *delayed_wq_notifr_param;

struct eth_phy_iface_eth_register_params mtip_phy_eth_params;

extern struct eth_phy_iface_ops qcom_aw_phy_driver_iface_ops;

struct mtip_delayed_work_q_params *delayed_wq_params[MTIP_MAX_LINKS] = {NULL};

u8 mtip_phy_retry_num[MTIP_MAX_LINKS] = {0};

u8 mtip_phy_an_seq_num[MTIP_MAX_PORTS] = {0};

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
#define MTIP_PHY_RETRY_TIMER       2000
#define MTIP_PHY_RETRIES_MAX_NUM   5

static void mtip_phy_ready_cb(void *user_data)
{
    CSMLOGDBG("Got the PHY ready cb\n");

    if (platform_driver_priv->phy_is_ready == false) 
    {
        // TBD: do we wait for both DMA and PHY?
    }

    // set the phy_is_ready flag
    platform_driver_priv->phy_is_ready = true;
    return;
}

static void mtip_phy_an_result_cb(enum mtip_port_type_enum port_type, bool an_result, enum mtip_port_config_enum port_config, u8 seq_num)
{
    CSMLOGINFO("Got AN complete CB for port: %d seq %d result %d port_config %d %s\n", port_type, seq_num, an_result, port_config, mtip_ethtool_get_priv_flags_str(port_config));

    if(seq_num != mtip_phy_an_seq_num[port_type])
    {
        CSMLOGINFO("Ignore the older AN result");
        return;
    }

    post_mtip_process_an_result(port_type, an_result, port_config, seq_num);
    return;
}

void mtip_phy_lane_bring_up_progress_ind(u32 link_index, bool in_progress)
{
    CSMLOGDBG("Lane bring up progress: %d for link index %d", in_progress, link_index);

    if(in_progress)
        mtip_mac_clear_link_status_interrupt_mask(link_index);
    else
        mtip_mac_set_link_status_interrupt_mask(link_index);

    return;
}

static void mtip_phy_cdr_lock_ind(u32 link_index, bool status, u8 an_seq_num)
{
    struct mtip_process_cdr_lock_ind* taskstruct;
    u32 port_type;

    if(status == false)
        return;

    if(link_index >= MTIP_MAX_LINKS)
    {
        CSMLOGINFO("Invalid link index %d", link_index);
        return;
    }

    if(mtip_lookup_port_type_by_link_index(link_index, &port_type) != 0)
    {
        CSMLOGINFO("Invalid link/port!");
        return;
    }

    if(an_seq_num != 0 &&
       an_seq_num != mtip_phy_an_seq_num[port_type])
    {
        CSMLOGINFO("Ignore the older CDR lock status");
        return;
    }

    taskstruct = kmalloc(sizeof(struct mtip_process_cdr_lock_ind), GFP_ATOMIC);
    if(taskstruct == NULL)
    {
      CSMLOGERR("memory alloc failed\n");
      return;
    }

    taskstruct->link_index= link_index;
    taskstruct->status = status;
    taskstruct->an_seq_num = an_seq_num;
    mtip_queue_work(MTIP_WORKQ_TASK_PROCESS_CDR_LOCK_IND, taskstruct);
    return;
}

void run_mtip_process_cdr_lock_ind(void* workptr)
{
    struct mtip_process_cdr_lock_ind *taskstruct = (struct mtip_process_cdr_lock_ind *)workptr;
    u32 link_index = taskstruct->link_index;
    bool status = taskstruct->status;
    u8 an_seq_num = taskstruct->an_seq_num;
    u32 port_type;

    CSMLOGINFO("CDR lock indication for link_index %d, status %d, an_seq_num %d\n",
               link_index, status, an_seq_num);

    if(mtip_lookup_port_type_by_link_index(link_index, &port_type) != 0)
    {
        CSMLOGINFO("Invalid link/port!");
        goto out;
    }

    if(an_seq_num != 0 &&
       an_seq_num != mtip_phy_an_seq_num[port_type])
    {
        CSMLOGINFO("Ignore the older CDR lock status");
        goto out;
    }

    if (mtip_mac_wrapper_get_link_status(link_index) == true) 
    {
        mtip_process_link_state(link_index, true);
        mtip_phy_lane_bring_up_progress_ind(link_index, false);
        mtip_phy_retry_num[link_index] = 0;
    }
    else if(status == true)
    {
        delayed_wq_params[link_index] =
                              kmalloc(sizeof(struct mtip_delayed_work_q_params),
                                      GFP_ATOMIC);
        if(!delayed_wq_params[link_index])
            CSMLOGERR("Malloc failed!");
        else{
            INIT_DELAYED_WORK(&delayed_wq_params[link_index]->wq_item,
                              mtip_phy_retry_phy_bringup);
            delayed_wq_params[link_index]->link_index = link_index;
            mtip_workq_queue_delayed_work(delayed_wq_params[link_index],
                                          MTIP_PHY_RETRY_TIMER);
        }
    }

out:
    kfree(taskstruct);
    return;
}

int mtip_phy_register_eth(void)
{
    int res = 0;
    bool is_ready = false;
    mtip_phy_eth_params.notify_an_result = mtip_phy_an_result_cb;
    mtip_phy_eth_params.userdata_ready = NULL;
    mtip_phy_eth_params.notify_ready = mtip_phy_ready_cb;
    mtip_phy_eth_params.cdr_lock_ind = mtip_phy_cdr_lock_ind;
    mtip_phy_eth_params.lane_bring_up_progress_ind = mtip_phy_lane_bring_up_progress_ind;

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
    CSMLOGDBG("Deregistering with the phy driver\n");

    // deregister with the PHY driver
    (qcom_aw_phy_driver_iface_ops.eth_phy_iface_eth_deregister)();

    return 0;
}

int mtip_phy_setup_phy(struct mtip_port_device_info* port_device)
{
    int i;
    int rv;
    u32 port_type = port_device->port_type;
    struct mtip_port_info* port_info = NULL;

    // setup the phy for the port
    // pass the consolidated lane config of the port to phy
    CSMLOGDBG("setting up phy for port %d", port_device->port_type);

    port_info = platform_driver_priv->mtip_ports[port_type];

    for (i = 0; i < PHY_LANE_MAX; ++i)
    {
        CSMLOGDBG("lane config[%d] enabled %d speed %d link_index %d", i, 
                  port_info->lane_config[i].lane_enabled, 
                  port_info->lane_config[i].lane_speed,
                  port_info->lane_config[i].link_index);
    }

    rv = (qcom_aw_phy_driver_iface_ops.eth_phy_iface_phy_setup)(port_type, port_info->lane_config);

    CSMLOGDBG("phy_setup returned rv %d", rv);
    return rv;
}

void mtip_phy_get_lanes_of_link(u32 link_index, bool lanes_enabled[PHY_LANE_MAX])
{
    u32 num_lanes;
    int i;
    u32 lane;
    u32 lane_index;
    int lane_count = 0;

    // set lanes enabled to false
    for (i = 0; i < PHY_LANE_MAX; ++i)
    {
        lanes_enabled[i] = false;
    }

    // number of lanes assigned to the link
    num_lanes = platform_driver_priv->mtip_links[link_index]->num_assigned_lanes;

    if (num_lanes == 0) 
    {
        CSMLOGDBG("no lanes assigned to link_index %d", link_index);
        return;
    }

    // enable the assigned lanes
    for (i = 0; i < num_lanes; ++i)
    {
        lane_index = platform_driver_priv->mtip_links[link_index]->assigned_lane_indices[i];

        mtip_lookup_real_lane_number_by_lane_index(lane_index, &lane);

        lanes_enabled[lane] = true;

        CSMLOGDBG("using lane %d for link_index: %d", lane, link_index);
        ++lane_count;
    }

    CSMLOGDBG("lane count of link_index: %d is %d\n", link_index, lane_count);
    return;
}

void mtip_phy_retry_phy_bringup(struct work_struct *work)
{
    struct delayed_work *delayed_work_item = to_delayed_work(work);
    struct mtip_delayed_work_q_params *wq_params =
        container_of(delayed_work_item, struct mtip_delayed_work_q_params, wq_item);
    u32 port_type;
    u32 link_index = wq_params->link_index;

    if(link_index >= MTIP_MAX_LINKS)
    {
      CSMLOGERR("invalid link_index %d\n", link_index);
      goto func_exit;
    }

    if(!platform_driver_priv){
        CSMLOGERR("platform_driver_priv NULL \n");
        goto func_exit;
    }

    if(platform_driver_priv->mtip_links[link_index]->state == MTIP_LINK_STATE_CLOSE)
    {
        goto func_exit;
    }

    if(delayed_wq_params[link_index] != wq_params){
        CSMLOGINFO("Work mismatch, dropping");
        goto func_exit;
    }

    if(mtip_mac_wrapper_get_link_status(link_index) == true)
    {
        mtip_phy_retry_num[link_index] = 0;
        mtip_process_link_state(link_index, true);
        mtip_phy_lane_bring_up_progress_ind(link_index, false);
        goto func_exit;
    }

    if (mtip_lookup_port_type_by_link_index(link_index, &port_type) < 0)
    {
        CSMLOGERR("invalid port_type for link_index %d", link_index);
        goto func_exit;
    }

    mtip_phy_retry_num[link_index]++;
    if(mtip_phy_retry_num[link_index] >= MTIP_PHY_RETRIES_MAX_NUM){

        CSMLOGINFO("Max retries done for link_index %d", link_index);
        mtip_phy_retry_num[link_index] = 0;

        // notify phy that PCS link is down after max retries
        mtip_phy_notify_link_status(link_index, false);

        goto func_exit;
    }

    CSMLOGDBG("mtip_phy_retry_phy_bringup with link: %d, port: %d\n",
               link_index, port_type);

    mtip_phy_teardown_phy(link_index);
    mtip_phy_bringup_phy(link_index,
                    platform_driver_priv->mtip_ports[port_type]->sfp_port_type);

func_exit:
    kfree(wq_params);
    return;
}
extern uint32_t ber_sim_status[12];
void mtip_fault_notifr_status(struct work_struct *work)
{
    u32 link_index = 0;
    u32 port_type = 0;
    void __iomem *wrapper_base_addr;
    u32 port_link_id = 0;
    u32 read_val;

    if(!platform_driver_priv){
        CSMLOGERR("platform_driver_priv NULL \n");
        return;
    }
    for(port_type = MTIP_PORT_TYPE_FH_0;  port_type <= MTIP_PORT_TYPE_FH_2; port_type++){

        if(!platform_driver_priv->mtip_links[port_link_id]){
                continue;
        }
        wrapper_base_addr = platform_driver_priv->devices.port_devices[port_type].wrapper_base_addr;

        read_val = (u32)ioread32(wrapper_base_addr + MTIP_MAC_WRAPPER_CORE_STATUS_REG_OFFSET);

        for(link_index=0 ; link_index < MTIP_MAX_LINKS_PER_PORT; link_index++){

            mtip_lookup_link_index_by_port_type_and_real_link(&port_link_id, port_type, link_index);

            if(platform_driver_priv->mtip_links[port_link_id]->state == MTIP_LINK_STATE_CLOSE){
                continue;
            }

            if ( (((read_val & GENMASK(5,2)) >> 2) & (1 << link_index)) || ber_sim_status[port_link_id]){

                mtip_snd_event_notification(port_link_id, HIGH_BER_SET);
            }else{
                mtip_snd_event_notification(port_link_id, HIGH_BER_CLR);
            }
        }
    }
    mtip_workq_queue_delayed_work(delayed_wq_notifr_param , MTIP_NOTIFY_TIMER);

    return;
}

int mtip_phy_bringup_phy(u32 link_index, int sfp_port_type)
{
    enum mtip_port_type_enum port_type;
    bool lanes_enabled[PHY_LANE_MAX];
    int i;
    int rv;
    enum mtip_port_config_enum port_config;

    CSMLOGINFO("calling phy_bringup with link: %d, sfp_port_type: %d\n", link_index, sfp_port_type);

    if (mtip_lookup_port_type_by_link_index(link_index, &port_type) < 0)
    {
        CSMLOGERR("invalid port_type for link_index %d", link_index);
        return -1;
    }

    port_config = platform_driver_priv->mtip_ports[port_type]->port_config;

    CSMLOGINFO("phy bringup of port_type %d with config %d, %s", port_type, port_config, mtip_ethtool_get_priv_flags_str(port_config));

    mtip_phy_get_lanes_of_link(link_index, lanes_enabled);

    for (i = 0; i < PHY_LANE_MAX; ++i) 
    {
        CSMLOGDBG("phy_bringup_phy lane enabled[%d] is %d", i, lanes_enabled[i]);
    }

    // bringup the phy for the specified lanes
    rv = (qcom_aw_phy_driver_iface_ops.eth_phy_iface_phy_bringup)(port_type, lanes_enabled, sfp_port_type);

    CSMLOGDBG("phy bringup returned rv %d", rv);
    return rv;
}

int mtip_phy_teardown_phy(u32 link_index)
{
    enum mtip_port_type_enum port_type;
    bool lanes_enabled[PHY_LANE_MAX];
    int ret_val = 0;
    int i;

    if (mtip_lookup_port_type_by_link_index(link_index, &port_type) < 0)
    {
        CSMLOGERR("invalid port_type for link_index %d", link_index);
        return -1;
    }

    // stop listening to link status interrupts
    mtip_phy_lane_bring_up_progress_ind(link_index, true);

    mtip_phy_get_lanes_of_link(link_index, lanes_enabled);

    for (i = 0; i < PHY_LANE_MAX; ++i) 
    {
        CSMLOGDBG("phy teardown of link_index %d lanes_enabled[%d] = %d", link_index, i, lanes_enabled[i]);
    }

    // teardown the phy for the specified lanes
    ret_val = (qcom_aw_phy_driver_iface_ops.eth_phy_iface_phy_teardown)(port_type, lanes_enabled);

    CSMLOGINFO("phy teardown done for link_index %d rv %d", link_index, ret_val);

    // disable tx_rx on the link
    if (mtip_loopback_mode == MTIP_MODE_DEFAULT)
    {
        mtip_process_link_state(link_index, false);
    }

    // Clear the retry count if interface has been torn down
    if(platform_driver_priv->mtip_links[link_index]->state == MTIP_LINK_STATE_CLOSE)
    {
        mtip_phy_retry_num[link_index] = 0;
    }

    return ret_val;
}

int mtip_phy_notify_link_status(u32 link_index, bool status)
{
    enum mtip_port_type_enum port_type;
    bool lanes_enabled[PHY_LANE_MAX];
    int i;

    if (mtip_lookup_port_type_by_link_index(link_index, &port_type) < 0)
    {
        CSMLOGERR("invalid port_type for link_index %d", link_index);
        return -1;
    }

    mtip_phy_get_lanes_of_link(link_index, lanes_enabled);

    CSMLOGDBG("phy_notify_link for port: %d link: %d", port_type, link_index);

    for (i = 0; i < PHY_LANE_MAX; ++i) 
    {
        CSMLOGDBG("phy_notify_link lane enabled[%d] is %d", i, lanes_enabled[i]);
    }

    // notify PHY of the link status
    return (qcom_aw_phy_driver_iface_ops.eth_phy_iface_notify_mac_link_status)(port_type, lanes_enabled, status);
}

int mtip_phy_initiate_an(u32 port_type, int num_lanes, u32 port_config_mask)
{
    mtip_phy_an_seq_num[port_type]++;
    if(mtip_phy_an_seq_num[port_type] == 255)
        mtip_phy_an_seq_num[port_type] = 1;

    CSMLOGINFO("Initiating AN on port %d with seq %d, num_lanes %d and mask %d",
               port_type, mtip_phy_an_seq_num[port_type], num_lanes, port_config_mask);
    return (qcom_aw_phy_driver_iface_ops.eth_phy_iface_initiate_an)(
              port_type, mtip_phy_an_seq_num[port_type], num_lanes, port_config_mask);
}

int mtip_phy_reset_phy_sm(u32 port_type)
{
    CSMLOGDBG("Resetting PHY state machine on port %d", port_type);
    return (qcom_aw_phy_driver_iface_ops.eth_phy_iface_reset_phy_sm)(port_type);
}

void mtip_phy_set_tx_compliance(bool flag)
{
    CSMLOGDBG("Compliance setting for PHY configured as: %d", flag);
    qcom_aw_phy_driver_iface_ops.eth_phy_iface_set_tx_compliance(flag);
    return;
}

static int mtip_phy_find_matching_lane(struct phylink_config *config, u32* lane_index)
{
    struct mtip_lanedev_priv* priv;
    struct net_device* dev = to_net_dev(config->dev);

    priv = netdev_priv(dev);

    *lane_index = priv->lane_index;
    return 0;
}

static void mtip_phy_get_link_state(struct phylink_config *config,
				 struct phylink_link_state *state)
{
    u32 lane_index;
    int ret;

    ret = mtip_phy_find_matching_lane(config, &lane_index);

    if (ret < 0) 
    {
        CSMLOGERR("failed to find matching lane for config: 0x%lx\n", (unsigned long)config);
        return;
    }
    else
    {
        CSMLOGDBG("get_link_state found matching lane: %d\n", lane_index);
    }

    // indicate that the mac pcs state is up
    state->link = 1;

    CSMLOGDBG("mtip_mac_link_state %d\n", state->link);

	return;
}

static void mtip_phy_config(struct phylink_config *config,
                     unsigned int mode,
                     const struct phylink_link_state *state) 
{
    u32 lane_index;
    int ret;
    unsigned int an_enabled;

    ret = mtip_phy_find_matching_lane(config, &lane_index);

    if (ret < 0) 
    {
        CSMLOGERR("failed to find matching lane for config: 0x%lx\n", (unsigned long)config);
        return;
    }
    else
    {
        CSMLOGDBG("config found matching lane: %d\n", lane_index);
    }

    an_enabled = state->an_enabled;

    CSMLOGDBG("phy config ops received with an_enabled: %d\n", an_enabled);

   return;
}

static void mtip_phy_handle_lane_up(u32 lane_index, u8 sfp_port_type, enum eth_phy_iface_phy_lane_speed_enum lane_speed)
{
    u32 port_type;
    enum mtip_lane_state_enum current_state;

    current_state = platform_driver_priv->mtip_lanes[lane_index]->lane_state;

    switch (current_state)
    {
    case MTIP_LANE_STATE_DISCONNECTED:
    case MTIP_LANE_STATE_INIT:
       {
          CSMLOGINFO("Handling transition from lane state %d to CONNECTED for lane: %d", current_state, lane_index);

          // trigger an update for the port
          if (mtip_lookup_port_type_by_lane_index(lane_index, &port_type) < 0)
          {
              CSMLOGERR("invalid port_type for lane_index %d", lane_index);
              return;
          }

          CSMLOGINFO("Updating state of Port: %d with lane_index: %d in state %d\n", port_type, lane_index, MTIP_LANE_STATE_CONNECTED);

          // set the lane state of the lane to CONNECTED
          platform_driver_priv->mtip_lanes[lane_index]->lane_state = MTIP_LANE_STATE_CONNECTED;

          // set the sfp_port_type
          platform_driver_priv->mtip_lanes[lane_index]->sfp_port_type = sfp_port_type;

          // set the lane speed
          platform_driver_priv->mtip_lanes[lane_index]->lane_speed = lane_speed;

          // set the sfp port type of the port
          platform_driver_priv->mtip_ports[port_type]->sfp_port_type = sfp_port_type;

          // update the port configuration
          post_mtip_process_configure_port_using_lane(port_type, lane_index);
       }
       break;

    case MTIP_LANE_STATE_CONNECTED:
       {
          CSMLOGINFO("Handling transition from CONNECTED to CONNECTED for lane: %d ignoring", lane_index);
       }
       break;

    default:
       {
          CSMLOGINFO("Handling transition from unknown to CONNECTED for lane: %d", lane_index);
       }
       break;
    }
    return;
}

static void mtip_phy_handle_lane_down(u32 lane_index)
{
   int i;
   u32 link_index;
   enum mtip_link_state_enum link_state;
   u32 port_type;
   enum mtip_lane_state_enum current_state = MTIP_LANE_STATE_INIT;
   u32 tmp_lane_index;
   bool any_lane_connected = false;

   if(platform_driver_priv->mtip_lanes[lane_index])
   {
      current_state = platform_driver_priv->mtip_lanes[lane_index]->lane_state;
   }

   switch (current_state)
   {
   case MTIP_LANE_STATE_DISCONNECTED:
   case MTIP_LANE_STATE_INIT:
      {
         CSMLOGINFO("Handling transition from lane state %d to DISCONNECTED for lane: %d", current_state, lane_index);
         if(platform_driver_priv->mtip_lanes[lane_index])
         {
           platform_driver_priv->mtip_lanes[lane_index]->lane_state = MTIP_LANE_STATE_DISCONNECTED; 
         }
      }
      break;

   case MTIP_LANE_STATE_CONNECTED:
      {
         CSMLOGINFO("Handling transition from CONNECTED to DISCONNECTED for lane: %d", lane_index);

         // set the lane state as DISCONNECTED
         if(platform_driver_priv->mtip_lanes[lane_index])
         {
           platform_driver_priv->mtip_lanes[lane_index]->lane_state = MTIP_LANE_STATE_DISCONNECTED;
         }

         // determine the port using lane
         mtip_lookup_port_type_by_lane_index(lane_index, &port_type);

         // Bring down only the link which is mapped to this lane
         if(mtip_lookup_link_index_by_lane_index(&link_index, lane_index) == 0)
         {
            if (platform_driver_priv->mtip_links[link_index] != NULL)
            {
               link_state = mtip_get_link_state_by_link_index(link_index);
               if ((link_state == MTIP_LINK_STATE_OPEN_DONE) ||
                   (link_state == MTIP_LINK_STATE_UP) ||
                   (link_state == MTIP_LINK_STATE_DOWN))
               {
                  CSMLOGDBG("Port: %d with link_index: %d in %d state\n", port_type, link_index, link_state);
                  // teardown the phy
                  mtip_phy_teardown_phy(link_index);
               }
            }
         }

         // Keep the port as connected if any other lane is still connected
         for (i = 0; i < platform_driver_priv->devices.port_devices[port_type].num_lane_phandles; ++i)
         {
            tmp_lane_index = platform_driver_priv->devices.port_devices[port_type].lane_devices[i]->lane_index;
            if (platform_driver_priv->mtip_lanes[tmp_lane_index]->lane_state == MTIP_LANE_STATE_CONNECTED)
            {
               any_lane_connected = true;
               break;
            }
         }

         if(any_lane_connected == false)
         {
            // Reset PHY state machine if links were torn down
            mtip_phy_reset_phy_sm(port_type);

            // set the port state back to INIT
            platform_driver_priv->mtip_ports[port_type]->port_state = MTIP_PORT_STATE_INIT;
         }
      }
      break;

   default:
      {
       CSMLOGINFO("Handling transition from unknown to CONNECTED for lane: %d", lane_index);
       if(platform_driver_priv->mtip_lanes[lane_index])  
       { 
         platform_driver_priv->mtip_lanes[lane_index]->lane_state = MTIP_LANE_STATE_DISCONNECTED; 
       }
      }
      break;
   }

   return;
}

void post_mtip_phy_handle_lane_up(u32 lane_index, u8 sfp_port_type, enum eth_phy_iface_phy_lane_speed_enum lane_speed)
{
    struct mtip_process_lane_up* taskstruct = kmalloc(sizeof(struct mtip_process_lane_up), GFP_ATOMIC);
    if(taskstruct == NULL)
    {
      CSMLOGERR("memory alloc failed\n");
      return;
    }
    taskstruct->lane_index = lane_index;
    taskstruct->sfp_port_type = sfp_port_type;
    taskstruct->lane_speed = lane_speed;
    mtip_queue_work(MTIP_WORKQ_TASK_PROCESS_LANE_UP, taskstruct);
}

void run_mtip_process_lane_up(void* workptr)
{
    struct mtip_process_lane_up *taskstruct = (struct mtip_process_lane_up *)workptr;
    u32 lane_index = taskstruct->lane_index;
    u8 sfp_port_type = taskstruct->sfp_port_type;
    enum eth_phy_iface_phy_lane_speed_enum lane_speed = taskstruct->lane_speed;

    mtip_phy_handle_lane_up(lane_index,sfp_port_type,lane_speed);

    // free the taskstruct
    kfree(taskstruct);
}

void post_mtip_phy_handle_lane_down(u32 lane_index)
{
    struct mtip_process_lane_down* taskstruct = kmalloc(sizeof(struct mtip_process_lane_down), GFP_ATOMIC);
    if(taskstruct == NULL)
    {
      CSMLOGERR("memory alloc failed\n");
      return;
   }
    taskstruct->lane_index = lane_index;
    mtip_queue_work(MTIP_WORKQ_TASK_PROCESS_LANE_DOWN, taskstruct);
}

void run_mtip_process_lane_down(void* workptr)
{
    struct mtip_process_lane_down *taskstruct = (struct mtip_process_lane_down *)workptr;
    u32 lane_index = taskstruct->lane_index;

    mtip_phy_handle_lane_down(lane_index);

    // free the taskstruct
    kfree(taskstruct);
}

static void mtip_phy_phy_validate(struct phylink_config *config,
                           unsigned long *supported,
                           struct phylink_link_state *state) 
{
    u32 lane_index;
    int ret;
    u8  sfp_port_type = PORT_DA;
    int sfp_phandle;
    struct qsfp_info trx_info;

    // set the lane speed for now to 25G
    enum eth_phy_iface_phy_lane_speed_enum lane_speed = PHY_LANE_SPEED_25G;

    ret = mtip_phy_find_matching_lane(config, &lane_index);
    if (ret < 0) 
    {
        CSMLOGERR("failed to find matching lane for config: 0x%lx\n", (unsigned long)config);
        return;
    }

    CSMLOGDBG("phy validate ops received for lane: %d config: 0x%lx", lane_index, (unsigned long)config);

    // ignore this if there is no associated lane device
    if (platform_driver_priv->mtip_lanes[lane_index] == NULL)
    {
       CSMLOGINFO("Got phy validate on unused lane_index: %d ignoring", lane_index);
       return;
    }

    // /lookup the sfp_port_type of the port
    sfp_phandle = platform_driver_priv->devices.lane_devices[lane_index].sfp_phandle;
    if (sfp_phandle < 0)
    {
       CSMLOGERR("Got an unexpected link event! lane: %d\n", lane_index);
       return;
    }

    // ask the qsfp driver about the sfp port type
    if (qsfp_trx_get_lane_type(sfp_phandle, &sfp_port_type) < 0)
    {
       CSMLOGDBG("TRX not initialized yet, ignoring event for lane: %d\n", lane_index);
       return;
    }

    CSMLOGINFO("phy validate read sfp_port_type %d for sfp_phandle %d", sfp_port_type, sfp_phandle);

    // if sfp port type is OTHER, force it to be PORT_DA
    if (sfp_port_type == PORT_OTHER)
    {
        sfp_port_type = PORT_DA;
    }

    // set the sfp port_type of the lane
    platform_driver_priv->mtip_lanes[lane_index]->sfp_port_type = sfp_port_type;

    ret = qsfp_trx_get_info(sfp_phandle, &trx_info);
    if (ret == 0) 
    {
        // copy the trx info to the lane
        memcpy(&platform_driver_priv->mtip_lanes[lane_index]->lane_qsfp_info, &trx_info, sizeof(struct qsfp_info));

        // convert the trx_speed to eth_phy format
        switch (trx_info.trx_speed)
        {
        case TRX_LANE_SPEED_10G:
           lane_speed = PHY_LANE_SPEED_10G;
           break;

        case TRX_LANE_SPEED_25G:
           lane_speed = PHY_LANE_SPEED_25G;
           break;

        case TRX_LANE_SPEED_50G:
           lane_speed = PHY_LANE_SPEED_50G;
           break;

        case TRX_LANE_SPEED_100G:
           lane_speed = PHY_LANE_SPEED_100G;
           break;

        case TRX_LANE_SPEED_UNKNOWN:
        case TRX_LANE_SPEED_2_5G:
        default:
           lane_speed = PHY_LANE_SPEED_MAX;
           break;
        }

        CSMLOGINFO("mod_type %d , trx_speed %d, lane_info 0x%x, breakout_cfg 0x%x, link length range %d, associated with lane_index %d",
                   trx_info.trx_module_type, trx_info.trx_speed, trx_info.trx_laneinfo, trx_info.trx_bout_cfg , trx_info.trx_link_length_range, lane_index);

        if(lane_speed == PHY_LANE_SPEED_MAX)
           return;

        post_mtip_phy_handle_lane_up(lane_index, sfp_port_type, lane_speed);
    }

    return;
}

static void mtip_phy_phylink_lane_up(struct phylink_config *config,
                                     struct phy_device *phy, unsigned int mode,
                                     phy_interface_t interface, int speed,
                                     int duplex, bool tx_pause, bool rx_pause)
{
    u32 lane_index;
    int ret;
    u8  sfp_port_type = PORT_DA;
    int sfp_phandle;
    struct qsfp_info trx_info;
    // set the lane speed for now to 25G
    enum eth_phy_iface_phy_lane_speed_enum lane_speed = PHY_LANE_SPEED_25G;

    ret = mtip_phy_find_matching_lane(config, &lane_index);

    if (ret < 0)
    {
       CSMLOGERR("failed to find matching lane for config: 0x%lx\n", (unsigned long)config);
       return;
    }
    else
    {
       CSMLOGDBG("link_up found matching lane_index: %d\n", lane_index);
    }

    CSMLOGINFO("phy link up ops received for lane_index %d\n", lane_index);

    // print the data passed
    CSMLOGINFO("mode: %d, interface: %d, speed: %d, duplex: %d, tx_pause: %d, rx_pause: %d\n", mode, (unsigned int)interface, speed, duplex, tx_pause, rx_pause);

    // ignore this if there is no associated lane device
    if (platform_driver_priv->mtip_lanes[lane_index] == NULL)
    {
       CSMLOGINFO("Got lane up on unused lane_index: %d ignoring", lane_index);
       return;
    }

    // /lookup the sfp_port_type of the port
    sfp_phandle = platform_driver_priv->devices.lane_devices[lane_index].sfp_phandle;
    if (sfp_phandle < 0)
    {
       CSMLOGERR("Got an unexpected link event! lane: %d\n", lane_index);
       return;
    }

    // ask the qsfp driver about the sfp port type
    qsfp_trx_get_lane_type(sfp_phandle, &sfp_port_type);

    CSMLOGINFO("read sfp_port_type %d for sfp_phandle %d", sfp_port_type, sfp_phandle);

    // if sfp port type is OTHER, force it to be PORT_DA
    if (sfp_port_type == PORT_OTHER)
    {
       sfp_port_type = PORT_DA;
    }

    // set the sfp port_type
    platform_driver_priv->mtip_lanes[lane_index]->sfp_port_type = sfp_port_type;

    ret = qsfp_trx_get_info(sfp_phandle, &trx_info);
    if (ret == 0) 
    {
        // copy the trx info to the lane
        memcpy(&platform_driver_priv->mtip_lanes[lane_index]->lane_qsfp_info, &trx_info, sizeof(struct qsfp_info));

        // convert the trx_speed to eth_phy format
        switch (trx_info.trx_speed)
        {
        case TRX_LANE_SPEED_10G:
           lane_speed = PHY_LANE_SPEED_10G;
           break;

        case TRX_LANE_SPEED_25G:
           lane_speed = PHY_LANE_SPEED_25G;
           break;

        case TRX_LANE_SPEED_50G:
           lane_speed = PHY_LANE_SPEED_50G;
           break;

        case TRX_LANE_SPEED_100G:
           lane_speed = PHY_LANE_SPEED_100G;
           break;

        case TRX_LANE_SPEED_UNKNOWN:
        case TRX_LANE_SPEED_2_5G:
        default:
           lane_speed = PHY_LANE_SPEED_MAX;
           break;
        }

        CSMLOGINFO("mod_type %d , trx_speed %d, lane_info 0x%x, breakout_cfg 0x%x, link length range %d, associated with lane_index %d",
                   trx_info.trx_module_type, trx_info.trx_speed, trx_info.trx_laneinfo, trx_info.trx_bout_cfg , trx_info.trx_link_length_range, lane_index);

        if(lane_speed == PHY_LANE_SPEED_MAX)
           return;

        post_mtip_phy_handle_lane_up(lane_index, sfp_port_type, lane_speed);
    }   

   return;
}

static void mtip_phy_phylink_lane_down(struct phylink_config *config, unsigned int mode,
                                phy_interface_t interface) 
{
    u32 lane_index;
    int ret;
    int sfp_phandle;
    trx_lane_down_reason_code_type reason_code;

    ret = mtip_phy_find_matching_lane(config, &lane_index);

    if (ret < 0) 
    {
        CSMLOGERR("failed to find matching lane for config: 0x%lx\n", (unsigned long)config);
        return;
    }
    else
    {
        CSMLOGDBG("link_down found matching lane: %d\n", lane_index);
    }

    CSMLOGDBG("phy link down ops received\n");

    // /lookup the sfp_port_type of the port
    sfp_phandle = platform_driver_priv->devices.lane_devices[lane_index].sfp_phandle;

    if (sfp_phandle < 0) 
    {
        CSMLOGERR("Got an unexpected link event! lane: %d\n", lane_index);
        return;
    }

    // get the lane down reason code from the transceiver
    if (qsfp_trx_get_lane_down_reason_code(sfp_phandle, &reason_code) < 0) 
    {
        CSMLOGERR("got an invalid lane_down indication %d", lane_index);
        return;
    }

    CSMLOGINFO("Phylink lane down on lane_index %d reason_code: %d", lane_index, reason_code);

    platform_driver_priv->devices.lane_devices[lane_index].reason_code = reason_code;

    switch (reason_code) 
    {
    case TRX_LOCAL_PLUGOUT:
        {
            // handle this local cable plugout
            post_mtip_phy_handle_lane_down(lane_index);
        }
        break;

    case TRX_TX_FAULT:
    case TRX_RX_LOS:
        {
            CSMLOGINFO("Ignore lane down for lane_index %d", lane_index);
        }
        break;

    default:
        {
            CSMLOGERR("unknown reason code received for lane_index %d", lane_index);
        }
        break;
    }
   return;
}

static const struct phylink_mac_ops mtip_phylink_mac_ops = {
	.validate = mtip_phy_phy_validate,
	.mac_pcs_get_state = mtip_phy_get_link_state,
	.mac_config = mtip_phy_config,
	.mac_link_up = mtip_phy_phylink_lane_up,
	.mac_link_down = mtip_phy_phylink_lane_down,
};

static void mtip_phy_lane_netdevice_init(struct net_device *dev) 
{
   CSMLOGDBG("dummy netdev init for 0x%lx\n", (unsigned long)dev);
}

int mtip_phy_create_phylink(struct mtip_lane_device_info* lane_device)
{
    phy_interface_t mode;
    u32 lane_index = lane_device->lane_index;
    struct platform_device* lane_pdev = lane_device->lane_pdev;
    struct mtip_lane_info* lane_info;
    struct mtip_lanedev_priv* priv;

    // allocate the mtip_lane_info for the lane_index
    lane_info = platform_driver_priv->mtip_lanes[lane_index];

    // check if there is a valid sfp_handle associated with the port
    if (platform_driver_priv->devices.lane_devices[lane_index].sfp_phandle < 0) 
    {
        CSMLOGINFO("lane sfp_handle is not present\n");

        // set lane state as CONNECTED and return
        lane_info->lane_state = MTIP_LANE_STATE_CONNECTED;
        return 0;
    }

    if (mtip_loopback_mode != MTIP_MODE_DEFAULT)
    {
        // we are not using phylink for PCS loopback or
        // near end loopback
        // set port state as CONNECTED and return
        lane_info->lane_state = MTIP_LANE_STATE_CONNECTED;
        return 0;
    }

    // for E2E set the port state as INIT
    // this will be set to CONNECTED on receiving a link up
    lane_info->lane_state = MTIP_LANE_STATE_INIT;

    lane_info->lane_dummy_ndev = alloc_netdev(sizeof(struct mtip_lanedev_priv), "lane%d", NET_NAME_ENUM, mtip_phy_lane_netdevice_init);

    SET_NETDEV_DEV(lane_info->lane_dummy_ndev, &lane_pdev->dev);

    priv = netdev_priv(lane_info->lane_dummy_ndev);
    priv->lane_index = lane_index;

    /* PHYLINK setup */
	lane_info->phylink_config.dev = &lane_info->lane_dummy_ndev->dev;
	lane_info->phylink_config.type = PHYLINK_NETDEV;
	of_get_phy_mode(lane_pdev->dev.of_node, &mode);

	lane_info->phylink = phylink_create(&lane_info->phylink_config, of_fwnode_handle(lane_pdev->dev.of_node),
	                         mode, &mtip_phylink_mac_ops);

    CSMLOGDBG("got phylink 0x%lx\n", lane_info->phylink);

	if (IS_ERR(lane_info->phylink))
	{
		CSMLOGERR("PHYLINK creation failed with err = %d", PTR_ERR(lane_info->phylink));
		return IS_ERR(lane_info->phylink);
	}

    CSMLOGINFO("phylink create done for lane %d\n", lane_index);

    // start has to be done in rtnl context
    rtnl_lock();

    // start the phylink
    phylink_start(lane_info->phylink);

    // start has to be done in rtnl context
    rtnl_unlock();

    CSMLOGDBG("phylink start done\n");

    return 0;
}

int mtip_phy_destroy_phylink(u32 lane_index)
{
    if (platform_driver_priv->devices.lane_devices[lane_index].sfp_phandle != -1)
    {
       // stop the phylink
       phylink_stop(platform_driver_priv->mtip_lanes[lane_index]->phylink);

       // destory the phylink
       phylink_destroy(platform_driver_priv->mtip_lanes[lane_index]->phylink);

       // free the netdev
       if(platform_driver_priv->mtip_lanes[lane_index]->lane_dummy_ndev)
          free_netdev(platform_driver_priv->mtip_lanes[lane_index]->lane_dummy_ndev);
    }

    return 0;
}

trx_link_length_range mtip_phy_get_trx_link_length_range(struct mtip_port_device_info* port_device)
{
    int i;
    u32 port_type = port_device->port_type;
    u32 lane_index;

    // find a lane that is connected
    for (i = 0; i < port_device->num_lane_phandles; ++i) 
    {
        lane_index = port_device->lane_devices[i]->lane_index;

        if (platform_driver_priv->mtip_lanes[lane_index]->lane_state == MTIP_LANE_STATE_CONNECTED) 
        {
            CSMLOGINFO("mtip_phy_get_trx_link_length_range %d for port %d",
                      platform_driver_priv->mtip_lanes[lane_index]->lane_qsfp_info.trx_link_length_range, port_type);
            return platform_driver_priv->mtip_lanes[lane_index]->lane_qsfp_info.trx_link_length_range;
        }
    }

    return TRX_LINK_UNKNOWN;
}

void mtip_phy_notify_eth_event_to_trx(u32 link_index, bool enable)
{
    enum mtip_port_type_enum port_type;
    bool lanes_enabled[PHY_LANE_MAX];
    int i;
    u32 lane_index;
    u32 sfp_phandle[MAX_ETH_LANES] = {0};
    u8 sfp_lane_count = 0;

    if (mtip_lookup_port_type_by_link_index(link_index, &port_type) < 0)
    {
        CSMLOGERR("invalid port_type for link_index %d", link_index);
        return;
    }

    mtip_phy_get_lanes_of_link(link_index, lanes_enabled);

    for (i = 0; i < PHY_LANE_MAX; ++i)
    {
        if(lanes_enabled[i] == true){
            mtip_lookup_lane_index_by_port_type_and_real_lane(&lane_index, port_type, i);
            sfp_phandle[sfp_lane_count++] = platform_driver_priv->devices.lane_devices[lane_index].sfp_phandle;
            CSMLOGINFO("eth_event %d for link_index %d = lane %d = sfp_phandle=%d",
                       enable, link_index, lane_index, sfp_phandle[sfp_lane_count-1]);
        }
    }

    // Indicate transceiver driver about interface bring up
    rtnl_lock();
    qsfp_trx_ifconfig_notifier(enable, sfp_phandle);
    rtnl_unlock();

    return;
}

bool mtip_phy_is_breakout_config(u32 port_type)
{
    struct qsfp_info lane_qsfp_info;

    if (mtip_device_lookup_lane_qsfp_cfg(port_type, &lane_qsfp_info) < 0)
    {
        CSMLOGERR("unable to lookup lane cfg of port_type %d", port_type);
        return false;
    }

    if(lane_qsfp_info.trx_module_type == TRX_QSFP_PLS_QSFP28_QSFP56)
    {
        if(lane_qsfp_info.trx_bout_cfg != 0 && lane_qsfp_info.trx_bout_cfg != 0xFF)
        {
            return true;
        }
        else if(lane_qsfp_info.trx_laneinfo != 0xF)
        {
            return true;
        }
    }
    else if(lane_qsfp_info.trx_module_type == TRX_QSFPDD)
    {
        if(lane_qsfp_info.trx_bout_cfg != 0)
        {
            return true;
        }
        else if(lane_qsfp_info.trx_laneinfo != 0xFF)
        {
            return true;
        }
    }

    return false;
}

