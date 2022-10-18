/* SPDX-License-Identifier: GPL-2.0-only WITH Linux-syscall-note
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/**
  @file qcom_aw_phy_prbs_gnl_uapi.h
  @brief Interface UAPI header file for generic netlink interface with the
  user space.

  This file defines header interface for netlink messages from PHY driver.
*/

#ifndef QCOM_AW_PHY_PRBS_GNL_UAPI_H
#define QCOM_AW_PHY_PRBS_GNL_UAPI_H

#define PRBS_GNL_FAMILY_NAME "QCOM_PRBS_GNL"
#define MAX_LANES 12
/**
 * struct qti_diag_aw_phy_prbs_params - PRBS parameters
 * tx_bist_phy_inst		-	PHY instance type for TX BIST generator
 * tx_bist_phy_lane		-	PHY lane number for TX BIST generator
 * rx_bist_phy_inst		-	PHY instance type for RX BIST generator
 * rx_bist_phy_lane		-	PHY lane number for RX BIST generator
 * check_all_lanes		-	Check for all lanes if it is set ie 01
 * prbs_bist_pattern		-	PRBS BIST pattern. Value can be set from one of the below patterns
  					AW_PRBS7 = 0, AW_PRBS9 = 1, AW_PRBS11 = 2, AW_PRBS13 = 3,
                                        AW_PRBS15 = 4, AW_PRBS23 = 5, AW_PRBS31 = 6, AW_QPRBS13 = 7,
					AW_JP03A = 8, AW_JP03B = 9, AW_LINEARITY_PATTERN = 10,
					AW_USER_DEFINED_PATTERN = 11, AW_FULL_RATE_CLOCK = 12,
					AW_HALF_RATE_CLOCK = 13, AW_QUARTER_RATE_CLOCK = 14,
                                        AW_PATT_32_1S_32_0S = 15
 * user_data_pattern		-	user data pattern if BIST pattern is selected as
 					AW_USER_DEFINED_PATTERN = 11 in the above option
 * monitor_duration		-	Duration in seconds to monitor pattern on RX checker side
 * num_of_errors		-	Number of errors to be injected from TX BIST generator. Default is 0
 */

typedef struct {
  u_int8_t tx_bist_phy_inst;
  u_int8_t tx_bist_phy_lane;
  u_int8_t rx_bist_phy_inst;
  u_int8_t rx_bist_phy_lane;
  u_int8_t check_all_lanes;
  u_int8_t prbs_bist_pattern;
  u_int32_t user_data_pattern;
  u_int8_t monitor_duration;
  u_int8_t num_of_errors;
} data_csm_diag_prbs_params;

/**
 * struct qti_diag_aw_phy_prbs_result - Store the Result for each lane of each
 * port min_lane	-	Staring PHY lane for which result is required
 * max_lane		-	Ending PHY lane for which result is required
 * min_port		-	Staring PHY instance for which result is required
 * max_port		-	Ending PHY instance for which result is required
 * err_count_overflow	-	Store if there is overflow in error for each lane of each port
 * err_count		-	Store error count for each lane of each port
 * ber			-	Store bit error ratio for each lane of each port
 */

typedef struct {

  int min_lane;
  int max_lane;
  int min_port;
  int max_port;
  u_int32_t err_count_overflow[MAX_LANES];
  u_int64_t err_count[MAX_LANES];
  u_int64_t ber[MAX_LANES];
} data_csm_diag_prbs_result;

enum data_csm_diag_gnl_cmd_enum {
  DATA_CSM_DIAG_GNL_CMD_MIN,
  DATA_CSM_DIAG_GNL_CMD_SET_PRBS_PARAMS,
  DATA_CSM_DIAG_GNL_CMD_ENABLE_DISABLE_PRBS,
  DATA_CSM_DIAG_GNL_CMD_GET_PRBS_RESULT,
  DATA_CSM_DIAG_GNL_CMD_MAX
};

#define DATA_CSM_DIAG_GNL_CMD_COUNT (DATA_CSM_DIAG_GNL_CMD_MAX - 1)

enum data_csm_diag_gnl_attr_enum {
  DATA_CSM_DIAG_GNL_ATTR_MIN,
  DATA_CSM_DIAG_GNL_ATTR_SET_PRBS_PARAMS,
  DATA_CSM_DIAG_GNL_ATTR_ENABLE_DISABLE_PRBS,
  DATA_CSM_DIAG_GNL_ATTR_GET_PRBS_RESULT,
  DATA_CSM_DIAG_GNL_ATTR_MAX
};

#define DATA_CSM_DIAG_GNL_ATTR_COUNT (DATA_CSM_DIAG_GNL_ATTR_MAX - 1)

#endif /* QCOM_AW_PHY_PRBS_GNL_UAPI_H */
