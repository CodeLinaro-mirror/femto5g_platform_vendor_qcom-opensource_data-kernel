/* SPDX-License-Identifier: GPL-2.0-only WITH Linux-syscall-note
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/**
  @file qcom_aw_phy_gnl_uapi.h
  @brief Interface UAPI header file for generic netlink interface with the
  user space.

  This file defines header interface for netlink messages from PHY driver.
*/

#ifndef QCOM_AW_PHY_GNL_UAPI_H
#define QCOM_AW_PHY_GNL_UAPI_H

#define FAMILY_NAME "QCOM_AW_PHY_GNL"

enum qcom_aw_phy_gnl_cmd_enum{
	QCOM_AW_PHY_GNL_CMD_UNSPEC,
	QCOM_AW_PHY_GNL_CMD_INIT_LIB,
	QCOM_AW_PHY_GNL_CMD_ETH_STATUS_CHANGE,
	QCOM_AW_PHY_GNL_CMD_SNR_VALID_CHANGE,
	QCOM_AW_PHY_GNL_CMD_SET_SNR_THRESHOLD,
	QCOM_AW_PHY_GNL_CMD_GET_SNR_VALUE_REQ,
	QCOM_AW_PHY_GNL_CMD_GET_SNR_VALUE_RESP,
	QCOM_AW_PHY_GNL_CMD_SET_SYNCE_MUX,
	QCOM_AW_PHY_GNL_CMD_MAX
};

#define QCOM_AW_PHY_GNL_CMD_COUNT (QCOM_AW_PHY_GNL_CMD_MAX-1)

enum qcom_aw_phy_gnl_attr_enum{
	QCOM_AW_PHY_GNL_ATTR_UNSPEC,
	QCOM_AW_PHY_GNL_ATTR_INIT_LIB,
	QCOM_AW_PHY_GNL_ATTR_ETH_STATUS_CHANGE,
	QCOM_AW_PHY_GNL_ATTR_SNR_VALID_CHANGE,
	QCOM_AW_PHY_GNL_ATTR_SET_SNR_THRESHOLD,
	QCOM_AW_PHY_GNL_ATTR_GET_SNR_VALUE_REQ,
	QCOM_AW_PHY_GNL_ATTR_GET_SNR_VALUE_RESP,
	QCOM_AW_PHY_GNL_ATTR_SET_SYNCE_MUX,
	QCOM_AW_PHY_GNL_ATTR_MAX
};

#define QCOM_AW_PHY_GNL_ATTR_COUNT (QCOM_AW_PHY_GNL_ATTR_MAX-1)

#endif /* QCOM_AW_PHY_GNL_UAPI_H */
