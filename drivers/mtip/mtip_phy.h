//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
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
void mtip_phy_retry_phy_bringup(struct work_struct *work);
int mtip_phy_teardown_phy(u32 link_index);
int mtip_phy_notify_link_status(u32 link_index, bool status);
int mtip_phy_initiate_an(u32 port_type, int num_lanes, u32 port_config_mask);
int mtip_phy_reset_phy_sm(u32 port_type);
void mtip_phy_set_tx_compliance(bool flag);

void post_mtip_phy_handle_lane_up(u32 lane_index, u8 sfp_port_type, enum eth_phy_iface_phy_lane_speed_enum lane_speed);
void run_mtip_process_lane_up(void* workptr);

struct mtip_process_lane_up
{
    u32 lane_index;
    u8 sfp_port_type;
    enum eth_phy_iface_phy_lane_speed_enum lane_speed;
};

void run_mtip_process_cdr_lock_ind(void* workptr);

struct mtip_process_cdr_lock_ind
{
    u32 link_index;
    bool status;
    u8 an_seq_num;
};

void post_mtip_phy_handle_lane_down(u32 lane_index);
void run_mtip_process_lane_down(void* workptr);

struct mtip_process_lane_down
{
    u32 lane_index;
};

trx_link_length_range mtip_phy_get_trx_link_length_range(struct mtip_port_device_info* port_device);

void mtip_phy_notify_eth_event_to_trx(u32 link_index, bool enable);
bool mtip_phy_is_breakout_config(u32 port_type);

#endif // _MTIP_PHY_H
