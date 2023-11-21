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
   MTIP_DEVICE_DU,
   MTIP_DEVICE_RUv2,
   MTIP_DEVICE_DUv2
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

/*
 * mtip_port_config enum 
 *    These are the set of support PORT configurations 
 */
enum mtip_port_config_enum
{
   MTIP_PORT_CONFIG_1x100GBASE_R,
   MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC_LL,
   MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC,
   MTIP_PORT_CONFIG_1x100GBASE_R2,
   MTIP_PORT_CONFIG_1x100GBASE_R2_RSFEC,
   MTIP_PORT_CONFIG_1x100GBASE_R4,
   MTIP_PORT_CONFIG_1x100GBASE_R4_RSFEC,
   MTIP_PORT_CONFIG_2x50GBASE_R,
   MTIP_PORT_CONFIG_2x50GBASE_R_RSFEC,
   MTIP_PORT_CONFIG_2x50GBASE_R2,
   MTIP_PORT_CONFIG_2x50GBASE_R2_FEC,
   MTIP_PORT_CONFIG_2x50GBASE_R2_LUAI,
   MTIP_PORT_CONFIG_2x50GBASE_R2_LUAI_FEC,
   MTIP_PORT_CONFIG_1x50GBASE_R,
   MTIP_PORT_CONFIG_1x50GBASE_R_RSFEC,
   MTIP_PORT_CONFIG_1x50GBASE_R2,
   MTIP_PORT_CONFIG_1x50GBASE_R2_RSFEC,
   MTIP_PORT_CONFIG_1x50GBASE_R2_LUAI,
   MTIP_PORT_CONFIG_1x50GBASE_R2_LUAI_FEC,
   MTIP_PORT_CONFIG_1x40GBASE_R4,
   MTIP_PORT_CONFIG_1x40GBASE_R4_FEC,
   MTIP_PORT_CONFIG_4x25GBASE_R,
   MTIP_PORT_CONFIG_4x25GBASE_R_FEC,
   MTIP_PORT_CONFIG_4x25GBASE_R_RSFEC,
   MTIP_PORT_CONFIG_1x25GBASE_R,
   MTIP_PORT_CONFIG_1x25GBASE_R_FEC,
   MTIP_PORT_CONFIG_1x25GBASE_R_RSFEC,
   MTIP_PORT_CONFIG_4x10GBASE_R,
   MTIP_PORT_CONFIG_4x10GBASE_R_FEC,
   MTIP_PORT_CONFIG_1x10GBASE_R,
   MTIP_PORT_CONFIG_1x10GBASE_R_FEC,
   MTIP_PORT_CONFIG_MAX
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

/* Enum to identify the link speed */
enum eth_phy_iface_mtip_link_speed_enum
{
	MTIP_LINK_SPEED_10G = 0,
	MTIP_LINK_SPEED_25G,
	MTIP_LINK_SPEED_40G,
	MTIP_LINK_SPEED_50G,
	MTIP_LINK_SPEED_100G,
	MTIP_LINK_SPEED_MAX
};

/* Enum to identify the PHY eq mode */
enum qcom_aw_phy_eq_mode_enum {
	QCOM_AW_PHY_EQ_MODE_MIN = 0,
	QCOM_AW_PHY_MANUAL_EQ_MODE,
	QCOM_AW_PHY_ANLT_MODE,
	QCOM_AW_PHY_LT_MODE,
	QCOM_AW_PHY_EQ_MODE_MAX
};

/* Lane Config - Enabled flag and speed info */
struct eth_phy_iface_phy_lane_config
{
	bool                                       lane_enabled;
	enum eth_phy_iface_phy_lane_speed_enum     lane_speed;
	u32                                        link_index;
};

typedef void (*eth_phy_iface_phy_ready_cb)(void *user_data);

typedef void (*eth_phy_iface_an_result_cb)(
	                            enum mtip_port_type_enum port_type,
	                            bool an_result,
	                            enum mtip_port_config_enum port_config,
	                            u8 seq_num);

typedef void (*eth_phy_iface_cdr_lock_ind)(u32 link_index, bool status, u8 an_seq_num);

typedef void (*eth_phy_iface_lane_bring_up_progress_ind)(
                                              u32 link_index, bool in_progress);

/* struct eth_phy_iface_eth_register_params - PHY readiness parameters
 * @notify_ready:   PHY ready callback
 * @userdata_ready: userdata for PHY ready callback
 * @notify_an_result:   AN result callback
 * @cdr_lock_ind: CDR lock success/failure indication across PHY lanes
                  mapped to a particular MAC link
 * @lane_bring_up_progress_ind: Indication that at least one of the lanes 
                  mapped to the passed MAC link is being brought up.
 */
struct eth_phy_iface_eth_register_params {
	eth_phy_iface_phy_ready_cb                notify_ready;
	void                                     *userdata_ready;
	eth_phy_iface_an_result_cb                notify_an_result;
	eth_phy_iface_cdr_lock_ind                cdr_lock_ind;
	eth_phy_iface_lane_bring_up_progress_ind  lane_bring_up_progress_ind;
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
 * @eth_phy_iface_initiate_an: Initiate AN at port level with the speed modes
                               to be advertised for the number of lanes
                               passed as argument.
 * @eth_phy_iface_reset_phy_sm: Resets PHY state machine at port level.
 * @eth_phy_iface_set_tx_compliance: Indicates PHY to operate in TX only
                                     compliance mode.
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
	int (*eth_phy_iface_initiate_an)(enum mtip_port_type_enum port_type,
	                                 u8 seq_num,
	                                 int num_lanes,
	                                 uint32_t port_config_mask);
	int (*eth_phy_iface_reset_phy_sm)(enum mtip_port_type_enum port_type);
	void (*eth_phy_iface_set_tx_compliance)(bool flag);
	int (*eth_phy_iface_get_phy_phy_eq_mode)(
                                    enum mtip_port_type_enum port_type);
};

#endif // _ETH_PHY_IFACE_H
