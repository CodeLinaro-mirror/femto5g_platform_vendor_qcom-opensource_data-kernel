/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/**
  @file eth_phy_iface.h
  @brief Interface file between MAC and PHY drivers of Ethernet SS.

  This file contains interface APIs, structures and enums to be
  used between MAC and PHY drivers.
*/

#ifndef _ETH_PHY_IFACE_H
#define _ETH_PHY_IFACE_H

/* The Device Mode */
enum mtip_device_mode_enum
{
   MTIP_DEVICE_RU = 0,
   MTIP_DEVICE_DU
};

/* The Port type */
enum mtip_port_type_enum
{
   MTIP_PORT_TYPE_FH_0 = 0,
   MTIP_PORT_TYPE_FH_1,
   MTIP_PORT_TYPE_FH_2,
   MTIP_PORT_TYPE_L2,
   MTIP_PORT_TYPE_DEBUG,
   MTIP_PORT_TYPE_MAX
};

/* Enum to identify the lane number within a PHY instance */
enum eth_phy_iface_phy_lane_num_enum
{
	PHY_LANE_0 = 0,
	PHY_LANE_1,
	PHY_LANE_2,
	PHY_LANE_3,
	PHY_LANE_MAX
};

/* Enum to identify the lane speed */
enum eth_phy_iface_phy_lane_speed_enum
{
	PHY_LANE_SPEED_10G = 0,
	PHY_LANE_SPEED_25G,
	PHY_LANE_SPEED_50G,
	PHY_LANE_SPEED_100G,
	PHY_LANE_SPEED_MAX
};

/* Lane Config - Enabled flag and speed info */
struct eth_phy_iface_phy_lane_config
{
	bool                                       lane_enabled;
	enum eth_phy_iface_phy_lane_speed_enum     lane_speed;
	u32                                        link_index;
};

typedef void (*eth_phy_iface_phy_ready_cb)(void *user_data);

typedef void (*eth_phy_iface_an_complete_cb)(
	                            enum mtip_port_type_enum port_type,
	                            enum eth_phy_iface_phy_lane_num_enum lane_num);

typedef void (*eth_phy_iface_cdr_lock_cb)(u32 link_index, bool status);

/* struct eth_phy_iface_eth_register_params - PHY readiness parameters
 * @notify_ready:   PHY ready callback
 * @userdata_ready: userdata for PHY ready callback
 * @notify_an_complete:   AN complete callback(link fully up,
                          including LT and PCS)
 * @cdr_lock_cb: Callback to indicate CDR lock success/failure across PHY lanes
                 mapped to a particular MAC link
 */
struct eth_phy_iface_eth_register_params {
	eth_phy_iface_phy_ready_cb    notify_ready;
	void                         *userdata_ready;
	eth_phy_iface_an_complete_cb  notify_an_complete;
	eth_phy_iface_cdr_lock_cb     cdr_lock_cb;
};

/* struct eth_phy_iface_ops - Structure for interface ops between MAC and
                              PHY drivers
 * @eth_phy_iface_eth_register: MAC registers for PHY callback functions
                                like PHY ready and AN complete
 * @eth_phy_iface_eth_deregister: MAC deregisters from PHY callbacks
 * @eth_phy_iface_phy_setup:   Sets up PHY lanes associated with the given port
 * @eth_phy_iface_phy_bringup:   Brings up PHY lanes associated with the given
                                 MAC instance
 * @eth_phy_iface_phy_teardown:  Tears down PHY lanes associated with the given
                                 MAC instance
 * @eth_phy_iface_notify_mac_link_status: Indicates MAC link status(up/down)
 */
struct eth_phy_iface_ops {
	int (*eth_phy_iface_eth_register)(
	                       struct eth_phy_iface_eth_register_params *ready_info,
	                       bool *is_phy_ready);
	void (*eth_phy_iface_eth_deregister)(void);
	int (*eth_phy_iface_phy_setup)(enum mtip_port_type_enum port_type,
	            struct eth_phy_iface_phy_lane_config lane_config[PHY_LANE_MAX]);
	int (*eth_phy_iface_phy_bringup)(enum mtip_port_type_enum port_type,
	                                 bool lanes_enabled[PHY_LANE_MAX],
	                                 int sfp_port_type);
	int (*eth_phy_iface_phy_teardown)(enum mtip_port_type_enum port_type,
	                                  bool lanes_enabled[PHY_LANE_MAX]);
	int (*eth_phy_iface_notify_mac_link_status)(
	                                     enum mtip_port_type_enum port_type,
	                                     bool lanes_enabled[PHY_LANE_MAX],
	                                     bool status);
};

#endif // _ETH_PHY_IFACE_H
