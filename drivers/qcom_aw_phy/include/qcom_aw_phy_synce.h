/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/**
  @file qcom_aw_phy_synce.h
  @brief Interface header file between AW PHY and SyncE application.

  This file defines interface betwen AW PHY driver and SyncE application.
*/

#ifndef QCOM_AW_PHY_SYNCE_H
#define QCOM_AW_PHY_SYNCE_H

#define MAX_MAC_LINKS_PER_PORT 4

void qcom_aw_phy_synce_notify_phy_lane_state_change(void);
void qcom_aw_phy_synce_notify_snr_valid_change(
                                 enum qcom_aw_phy_instance_enum phy_inst,
                                 enum eth_phy_iface_phy_lane_num_enum lane_num,
                                 bool valid);
void qcom_aw_phy_synce_handle_snr_valid_change(
                                 struct work_struct *work);
int qcom_aw_phy_synce_set_snr_threshold(
                                 enum qcom_aw_phy_instance_enum phy_inst,
                                 enum eth_phy_iface_phy_lane_num_enum lane_num,
                                 int snr_low_val, int snr_high_val);
int qcom_aw_phy_synce_get_current_snr_val(
                                 enum qcom_aw_phy_instance_enum phy_inst,
                                 enum eth_phy_iface_phy_lane_num_enum lane_num,
                                 int *snr_val);
int qcom_aw_phy_synce_set_synce_mux(
                                 enum qcom_aw_phy_synce_lane_id lane_id);
enum qcom_aw_phy_synce_lane_id qcom_aw_phy_synce_eth_inst_to_phy_lane_id(
                                     enum qcom_aw_phy_synce_eth_inst eth_inst);
enum qcom_aw_phy_synce_eth_inst qcom_aw_phy_synce_phy_lane_to_eth_inst(
                                enum qcom_aw_phy_instance_enum phy_inst_type,
                                enum eth_phy_iface_phy_lane_num_enum lane_num);

#endif /* QCOM_AW_PHY_SYNCE_H */
