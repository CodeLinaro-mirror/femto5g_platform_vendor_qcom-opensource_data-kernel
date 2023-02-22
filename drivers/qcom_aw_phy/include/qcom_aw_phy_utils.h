/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/**
  @file aw_phy_utils.h
  @brief Utility header file for AW PHY driver.

  This file is a header for utility API/structure/macros for AW PHY driver.
*/

#ifndef QCOM_AW_PHY_UTILS_H
#define QCOM_AW_PHY_UTILS_H

#include <linux/types.h>
#include <linux/ipc_logging.h>
#include "eth_phy_iface.h"
#include "qcom_aw_phy_main.h"
#include "aw_c_api/aw_driver_sim.h"

#define PHY_IPC_LOG_PAGES 50

#define QCOM_AW_PHY_LOG_DBG(fmt, args...) \
do {\
  struct qcom_aw_phy_config* phy_config = qcom_aw_phy_get_config_info();\
  if(phy_config && phy_config->phy_ipc_log_buf_low)\
    ipc_log_string(phy_config->phy_ipc_log_buf_low, " %s:%d " fmt, __func__, __LINE__, ## args);\
  pr_debug(" %s:%d " fmt, __func__, __LINE__, ## args);\
} while (0)

#define QCOM_AW_PHY_LOG_ERR(fmt, args...) \
do {\
  struct qcom_aw_phy_config* phy_config = qcom_aw_phy_get_config_info();\
  if(phy_config && phy_config->phy_ipc_log_buf)\
    ipc_log_string(phy_config->phy_ipc_log_buf, " %s:%d " fmt, __func__, __LINE__, ## args);\
  pr_debug(" %s:%d " fmt, __func__, __LINE__, ## args);\
} while (0)

#define QCOM_AW_PHY_LOG_INFO(fmt, args...) \
do {\
  struct qcom_aw_phy_config* phy_config = qcom_aw_phy_get_config_info();\
  if(phy_config && phy_config->phy_ipc_log_buf)\
    ipc_log_string(phy_config->phy_ipc_log_buf, " %s:%d " fmt, __func__, __LINE__, ## args);\
  pr_debug(" %s:%d " fmt, __func__, __LINE__, ## args);\
} while (0)

/*-------------------------------------------------------------------
* Function Declarations
------------------------------------------------------------------- */
enum qcom_aw_phy_instance_enum qcom_aw_phy_mac_port_to_phy_inst(
                                           enum mtip_port_type_enum port_type);

enum mtip_port_type_enum qcom_aw_phy_inst_to_mac_port(
                                      enum  qcom_aw_phy_instance_enum phy_inst);

void qcom_aw_phy_get_lane_speed_config(
                         enum eth_phy_iface_phy_lane_speed_enum     lane_speed,
                         struct qcom_aw_phy_lane_speed_config      *config);

char *qcom_aw_phy_strtok(char *in_string, const char ch, char **out_string);

int qcom_aw_phy_load_hexfile(mss_access_t *mss, char * fileName);

void qcom_aw_phy_dump_registers(void);

#endif /* QCOM_AW_PHY_UTILS_H */
