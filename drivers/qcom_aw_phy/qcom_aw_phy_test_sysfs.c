
/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/**
  @file qcom_aw_phy_test_sysfs.c
  @brief Test SYS FS for AW PHY driver.

  This file contains SYS FS definitions for AW PHY driver.
*/

#include <linux/sysfs.h>
#include <linux/debugfs.h>

#include "qcom_aw_phy_main.h"
#include "qcom_aw_phy_mtip_if.h"
#include "qcom_aw_phy_gnl.h"
#include "qcom_aw_phy_utils.h"
#include "eth_phy_iface.h"


#ifdef FEATURE_QCOM_AW_TEST_SYS_FS

struct dentry *dobj;

static const struct file_operations qcom_aw_phy_debug_fs_ops = {
  .write = qcom_aw_phy_set_attr,
};

int                                        qcom_aw_phy_attr_val;
enum mtip_port_type_enum                   port_type = MTIP_PORT_TYPE_FH_0;
int                                        num_lanes = 4;
enum eth_phy_iface_phy_lane_speed_enum     lane_speed = PHY_LANE_SPEED_25G;

extern struct eth_phy_iface_ops qcom_aw_phy_driver_iface_ops;

#define MIN(a,b) ((a < b) ? a : b)

void qcom_aw_phy_setup_sysfs() {

  /* creating the directory structure in /sys/kernel/debug */
  dobj = debugfs_create_dir("qcom_aw_phy_test", NULL);

  debugfs_create_file("qcom_aw_phy", 0644, dobj, 0, &qcom_aw_phy_debug_fs_ops);

  return;
}

void qcom_aw_phy_del_sysfs() {

  /* deleting the directory structure in /sys/kernel/debug */
  debugfs_remove_recursive(dobj);

  return;
}

void qcom_aw_phy_ready_cb(void *udata) {
  QCOM_AW_PHY_LOG_ERR("qcom_aw_phy_ready_cb");
}

void qcom_aw_phy_an_complete_cb(enum mtip_port_type_enum port_type,
                                enum eth_phy_iface_phy_lane_num_enum lane_num) {

  QCOM_AW_PHY_LOG_ERR("qcom_aw_phy_an_complete_cb port %d, lane %d", port_type,
                      lane_num);
}

ssize_t qcom_aw_phy_set_attr(struct file *file, const char __user *buf,
                                      size_t count, loff_t *ppos) {
  struct eth_phy_iface_eth_register_params ready_info;
  bool is_phy_ready;
  struct eth_phy_iface_phy_lane_config lane_config[PHY_LANE_MAX];
  int i = 0;
  bool lanes_enabled[PHY_LANE_MAX] = {true, true, true, true};
  struct qcom_aw_phy_synce_snr_valid_change snr_valid_info;
  char *token;
  char token_string[100];
  char *save_ptr = NULL;

  memset(token_string, 0, sizeof(token_string));
  if (copy_from_user(&token_string, buf, MIN(sizeof(token_string), count))){
    QCOM_AW_PHY_LOG_ERR("Copy from user failed");
    return -EFAULT;
  }

  token = qcom_aw_phy_strtok(token_string, ',', &save_ptr);
  sscanf(token, "%d", &qcom_aw_phy_attr_val);

  QCOM_AW_PHY_LOG_ERR("qcom_aw_phy_set_attr val %d", qcom_aw_phy_attr_val);

  switch (qcom_aw_phy_attr_val) {
    case 1:
      QCOM_AW_PHY_LOG_ERR("Register");
      ready_info.notify_ready = qcom_aw_phy_ready_cb;
      ready_info.userdata_ready = NULL;
      ready_info.notify_an_complete = qcom_aw_phy_an_complete_cb;
      qcom_aw_phy_driver_iface_ops.eth_phy_iface_eth_register(&ready_info,
                                                              &is_phy_ready);
      QCOM_AW_PHY_LOG_ERR("is_phy_ready %d", is_phy_ready);
      break;

    case 2:
      QCOM_AW_PHY_LOG_ERR("Setup");
      memset(lane_config, 0, 
             PHY_LANE_MAX * sizeof(struct eth_phy_iface_phy_lane_config));
      for (i = PHY_LANE_0; i < num_lanes; i++) {
        lane_config[i].lane_enabled = true;
        lane_config[i].lane_speed = lane_speed;
      }
      qcom_aw_phy_driver_iface_ops.eth_phy_iface_phy_setup(port_type,
                                                           lane_config);
      break;

    case 3:
      QCOM_AW_PHY_LOG_ERR("Bringup");
      memset(lanes_enabled, 0, PHY_LANE_MAX * sizeof(bool));
      for (i = PHY_LANE_0; i < num_lanes; i++) {
        lanes_enabled[i] = true;
      }
      qcom_aw_phy_driver_iface_ops.eth_phy_iface_phy_bringup(port_type,
                                                             lanes_enabled, 0);
      break;

    case 4:
      QCOM_AW_PHY_LOG_ERR("Tear Down");
      memset(lanes_enabled, 0, PHY_LANE_MAX * sizeof(bool));
      for (i = PHY_LANE_0; i < num_lanes; i++) {
        lanes_enabled[i] = true;
      }
      qcom_aw_phy_driver_iface_ops.eth_phy_iface_phy_teardown(port_type,
                                                              lanes_enabled);
      QCOM_AW_PHY_LOG_ERR("Resetting loopback mode !");
      qcom_aw_phy_set_loopback_mode(QCOM_AW_PHY_NO_LB);
      break;

    case 5:
      QCOM_AW_PHY_LOG_ERR("MAC link status up");
      memset(lanes_enabled, 0, PHY_LANE_MAX * sizeof(bool));
      for (i = PHY_LANE_0; i < num_lanes; i++) {
        lanes_enabled[i] = true;
      }
      qcom_aw_phy_driver_iface_ops.eth_phy_iface_notify_mac_link_status(
          port_type, lanes_enabled, true);
      break;

    case 6:
      QCOM_AW_PHY_LOG_ERR("MAC link status down");
      memset(lanes_enabled, 0, PHY_LANE_MAX * sizeof(bool));
      for (i = PHY_LANE_0; i < num_lanes; i++) {
        lanes_enabled[i] = true;
      }
      qcom_aw_phy_driver_iface_ops.eth_phy_iface_notify_mac_link_status(
          port_type, lanes_enabled, false);
      break;

    case 7:
      QCOM_AW_PHY_LOG_ERR("Deregister");
      qcom_aw_phy_driver_iface_ops.eth_phy_iface_eth_deregister();
      break;

    case 8:
      QCOM_AW_PHY_LOG_ERR("SNR valid status change");
      snr_valid_info.lane_id = FH0_LANE_0;
      snr_valid_info.snr_valid_status = true;
      qcom_aw_phy_gnl_snr_valid_change(snr_valid_info);
      break;

    case 9:
      QCOM_AW_PHY_LOG_ERR("AN done callback simulation");
      for (i = PHY_LANE_0; i < num_lanes; i++) {
        qcom_aw_phy_notify_an_complete(
                               qcom_aw_phy_mac_port_to_phy_inst(port_type), i);
      }
      break;

    case 10:
      QCOM_AW_PHY_LOG_ERR("Set near end serial loopback mode !");
      qcom_aw_phy_set_loopback_mode(QCOM_AW_PHY_NEAR_END_SERIAL_LB);
      break;

    case 11:
      QCOM_AW_PHY_LOG_ERR("Set near end parallel loopback mode !");
      qcom_aw_phy_set_loopback_mode(QCOM_AW_PHY_NEAR_END_PARALLEL_LB);
      break;

    case 12:
      QCOM_AW_PHY_LOG_ERR("Dumping PHY registers !");
      qcom_aw_phy_dump_registers();
      break;

    case 13:
      token = qcom_aw_phy_strtok(NULL, ',', &save_ptr);
      sscanf(token, "%d", &port_type);
      QCOM_AW_PHY_LOG_ERR("Configuring port %d", port_type);
      break;

    case 14:
      token = qcom_aw_phy_strtok(NULL, ',', &save_ptr);
      sscanf(token, "%d", &num_lanes);
      QCOM_AW_PHY_LOG_ERR("Configuring num_lanes %d", num_lanes);
      break;

    case 15:
      token = qcom_aw_phy_strtok(NULL, ',', &save_ptr);
      sscanf(token, "%d", &lane_speed);
      QCOM_AW_PHY_LOG_ERR("Configuring lane_speed %d", lane_speed);
      break;

    default:
      break;
  }

  return count;
}

#endif /* FEATURE_QCOM_AW_TEST_SYS_FS */
