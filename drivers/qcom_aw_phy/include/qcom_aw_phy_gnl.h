/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/**
  @file qcom_aw_phy_gnl.h
  @brief Interface header file for generic netlink interface with the
  user space.

  This file defines header interface for netlink messages from PHY driver.
*/

#ifndef QCOM_AW_PHY_GNL_H
#define QCOM_AW_PHY_GNL_H

#include "qcom_aw_phy_main.h"
#include "qcom_aw_phy_synce.h"
#include <net/genetlink.h>

struct qcom_aw_phy_gnl_eth_status{
	bool                                       eth_status;
	enum eth_phy_iface_phy_lane_speed_enum     lane_speed;
};

struct qcom_aw_phy_gnl_snr_valid_change{
	enum qcom_aw_phy_synce_eth_inst            eth_inst;
	bool                                       snr_valid_status;
};

struct qcom_aw_phy_gnl_snr_threshold_info {
	enum qcom_aw_phy_synce_eth_inst            eth_inst;
	int                                        low_val;
	int                                        high_val;
};

int qcom_aw_phy_gnl_eth_status_change(
                             struct qcom_aw_phy_gnl_eth_status *eth_status);
int qcom_aw_phy_gnl_snr_valid_change(
                      struct qcom_aw_phy_gnl_snr_valid_change snr_valid_info);
int qcom_aw_phy_gnl_no_action(struct sk_buff *sender_skb,
                                         struct genl_info *info);
int qcom_aw_phy_gnl_init_lib(struct sk_buff *sender_skb,
                                        struct genl_info *info);
int qcom_aw_phy_gnl_close_lib(struct sk_buff *sender_skb,
                                         struct genl_info *info);
int qcom_aw_phy_gnl_set_snr_threshold(struct sk_buff *sender_skb,
                                                     struct genl_info *info);
int qcom_aw_phy_gnl_get_snr_value(struct sk_buff *sender_skb,
                                               struct genl_info *info);
int qcom_aw_phy_gnl_set_synce_mux(struct sk_buff *sender_skb,
                                               struct genl_info *info);
int qcom_aw_phy_gnl_init(void);
void qcom_aw_phy_gnl_exit(void);

#endif /* QCOM_AW_PHY_GNL_H */
