/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/**
  @file qcom_aw_phy_mtip_if.h
  @brief Interface header file between AW PHY and MTIP MAC drivers.

  This file contains definitions for AW PHY and MTIP MAC interface APIs and
  structures.
*/

#ifndef QCOM_AW_PHY_MTIP_IF_H
#define QCOM_AW_PHY_MTIP_IF_H

#include "eth_phy_iface.h"

//Default timeouts (slow sim)
#define CMN_ACK_TIMEOUT_US           2000
#define TX_ACK_TIMEOUT_US            1200
#define TX_ACK_P1_TIMEOUT_US         1100
#define TX_ACK_P2_TIMEOUT_US         900
#define RX_ACK_TIMEOUT_US            900
#define RX_ACK_P2_TIMEOUT_US         100
#define RX_CDR_TIMEOUT_US            150
#define RX_BIST_TIMEOUT_US           400
#define RX_LINKEVAL_FULL_TIMEOUT_US  4200
#define RX_DATABIST_TIMER_THRESH     20000
#define TX_RXDET_TIMEOUT_US          550

struct qcom_aw_phy_mtip_if_info {
	struct mutex                  lock;
	bool                          is_phy_drv_ready;
	bool                          is_mac_drv_ready;
	bool                          is_ready_notified;
	eth_phy_iface_phy_ready_cb    ready_cb;
	void                         *ready_cb_user_data;
	eth_phy_iface_an_complete_cb  an_complete_cb;
	eth_phy_iface_cdr_lock_cb     cdr_lock_cb;
};

/*-------------------------------------------------------------------
* Function Declarations
------------------------------------------------------------------- */
int qcom_aw_phy_mtip_register(
                          struct eth_phy_iface_eth_register_params *ready_info,
                          bool *is_phy_ready);

void qcom_aw_phy_mtip_deregister(void);

int qcom_aw_phy_setup(enum mtip_port_type_enum port_type,
                struct eth_phy_iface_phy_lane_config lane_config[PHY_LANE_MAX]);

int qcom_aw_phy_bringup(enum mtip_port_type_enum port_type,
                                 bool lanes_enabled[PHY_LANE_MAX],
                                 int sfp_port_type);

int qcom_aw_phy_teardown(enum mtip_port_type_enum port_type,
                                  bool lanes_enabled[PHY_LANE_MAX]);

int qcom_aw_phy_mac_link_status(enum mtip_port_type_enum port_type,
                                            bool lanes_enabled[PHY_LANE_MAX],
                                            bool status);

void qcom_aw_phy_set_drv_ready(void);

void qcom_aw_phy_mtip_if_init(void);

void qcom_aw_phy_notify_an_complete(
                                enum qcom_aw_phy_instance_enum phy_inst,
                                enum eth_phy_iface_phy_lane_num_enum lane_num);

void qcom_aw_phy_handle_an_complete(struct work_struct *work);

void qcom_aw_phy_retry_lane_bring_up(struct work_struct *work);

#endif /* QCOM_AW_PHY_MTIP_IF_H */
