//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022-2024 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#ifndef _MTIP_PHY_H
#define _MTIP_PHY_H

#include <linux/slab.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/phylink.h>

#include "mtip.h"

extern u8 mtip_phy_an_seq_num[MTIP_MAX_PORTS];

// PHY driver related functions
int mtip_phy_register_eth(void);
int mtip_phy_deregister_eth(void);

// PHYLINK related functions and structs
struct mtip_lanedev_priv 
{
    u32 lane_index;
};

int mtip_phy_create_phylink(struct mtip_lane_device_info* lane_device);
int mtip_phy_destroy_phylink(struct phylink *phylink,struct net_device* lane_dummy_ndev);

int mtip_phy_setup_phy(struct mtip_port_device_info* port_device);
int mtip_phy_bringup_phy(u32 link_index, int sfp_port_type);
int mtip_phy_teardown_phy(u32 link_index);
int mtip_phy_notify_link_status(u32 link_index, bool status);
int mtip_phy_initiate_an(u32 port_type, int num_lanes, u32 port_config_mask);
int mtip_phy_reset_phy_sm(u32 port_type);
void mtip_phy_set_tx_compliance(bool flag);
void mtip_phy_set_c2c_phy_loopback_mode(enum qcom_aw_phy_loopback_mode_enum loopback_mode);

// Lane up handling structure and function declarations
struct mtip_process_lane_up
{
    u32 lane_index;
    u8 sfp_port_type;
    u8 speed_mask;;
    bool lane_connected;
};
void post_mtip_phy_handle_lane_up(struct mtip_process_lane_up lane_up_info);
void run_mtip_process_lane_up(void* workptr);

void mtip_phy_get_lanes_of_link(u32 link_index, bool lanes_enabled[]);

// CDR lock indication handling structure and function declarations
struct mtip_process_cdr_lock_ind
{
    u32 link_index;
    bool status;
    u8 an_seq_num;
};
void run_mtip_process_cdr_lock_ind(void* workptr);

// Lane down handling structure and function declarations
struct mtip_process_lane_down
{
    u32 lane_index;
    trx_lane_down_reason_code_type reason_code;
};
void post_mtip_phy_handle_lane_down(struct mtip_process_lane_down lane_down_info);
void run_mtip_process_lane_down(void* workptr);

// PHY bring up retry handling structure and function declarations
struct mtip_process_phy_retry_bringup
{
    u32 link_index;
};
void run_mtip_phy_retry_bringup(void* workptr);
void mtip_phy_retry_timer_cb(struct timer_list *list);

trx_link_length_range mtip_phy_get_trx_link_length_range(struct mtip_port_device_info* port_device);

void mtip_phy_notify_eth_event_to_trx(u32 link_index, trx_phy_event event);
bool mtip_phy_is_breakout_config(u32 port_type);
trx_lane_speed mtip_phy_port_config_to_trx_lane_speed(enum mtip_port_config_enum port_config);
void mtip_phy_lane_bring_up_progress_ind(u32 link_index, bool in_progress);

#endif // _MTIP_PHY_H
