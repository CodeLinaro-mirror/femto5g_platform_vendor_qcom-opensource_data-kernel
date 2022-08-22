/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
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


int qcom_aw_phy_gnl_lane_status_change(
                             struct qcom_aw_phy_synce_lane_status *lane_status);
int qcom_aw_phy_gnl_snr_valid_change(
                      struct qcom_aw_phy_synce_snr_valid_change snr_valid_info);
int qcom_aw_phy_gnl_no_action(struct sk_buff *sender_skb,
                                         struct genl_info *info);
int qcom_aw_phy_gnl_init_lib(struct sk_buff *sender_skb,
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
