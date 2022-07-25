/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/**
  @file qcom_aw_phy_synce.h
  @brief Interface header file between AW PHY and SyncE application.

  This file defines interface betwen AW PHY driver and SyncE application.
*/

#ifndef QCOM_AW_PHY_SYNCE_H
#define QCOM_AW_PHY_SYNCE_H

enum qcom_aw_phy_synce_lane_id{
	LANE_NONE  = -1,
	FH0_LANE_0 =  0,
	FH0_LANE_1,
	FH0_LANE_2,
	FH0_LANE_3,
	FH1_LANE_0,
	FH1_LANE_1,
	FH1_LANE_2,
	FH1_LANE_3,
	FH2_LANE_0,
	FH2_LANE_1,
	FH2_LANE_2,
	FH2_LANE_3,
	L2_LANE_0,
	L2_LANE_1,
	L2_LANE_2,
	L2_LANE_3,
	MAX_PHY_SYNCE_LANES
};

struct qcom_aw_phy_synce_lane_status{
	bool                                       lane_status;
	enum eth_phy_iface_phy_lane_speed_enum     lane_speed;
};

struct qcom_aw_phy_synce_snr_valid_change{
	enum qcom_aw_phy_synce_lane_id             lane_id;
	bool                                       snr_valid_status;
};

struct qcom_aw_phy_snr_threshold_info {
	enum qcom_aw_phy_synce_lane_id             lane_id;
	int                                        low_val;
	int                                        high_val;
};


void qcom_aw_phy_synce_notify_phy_lane_state_change(void);
void qcom_aw_phy_synce_notify_snr_valid_change(
                                 enum qcom_aw_phy_instance_enum phy_inst,
                                 enum eth_phy_iface_phy_lane_num_enum lane_num,
                                 bool valid);
int qcom_aw_phy_synce_set_snr_threshold(
                                 enum qcom_aw_phy_instance_enum phy_inst,
                                 enum eth_phy_iface_phy_lane_num_enum lane_num,
                                 int snr_low_val, int snr_high_val);
int qcom_aw_phy_synce_get_current_snr_val(
                                 enum qcom_aw_phy_instance_enum phy_inst,
                                 enum eth_phy_iface_phy_lane_num_enum lane_num,
                                 int *snr_val);

#endif /* QCOM_AW_PHY_SYNCE_H */
