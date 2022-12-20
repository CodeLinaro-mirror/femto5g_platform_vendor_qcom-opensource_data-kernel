
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
#include "aw_c_api/aw_alphacore.h"


#ifdef FEATURE_QCOM_AW_TEST_SYS_FS

struct dentry *dobj;

static const struct file_operations qcom_aw_phy_debug_fs_ops = {
  .write = qcom_aw_phy_set_attr,
  .read = qcom_aw_phy_get_attr,
};

static const struct file_operations qcom_aw_phy_debug_fs_prbs_result_ops = {
  .read = qcom_aw_phy_get_prbs_result,
};

enum qcom_aw_phy_debug_fs_cmd{
  PHY_REG = 1,
  PHY_SETUP,
  PHY_BRINGUP,
  PHY_TEAR_DOWN,
  MAC_LINK_UP,
  MAC_LINK_DOWN,
  PHY_DEREG,
  SNR_VALID_CB,
  AN_DONE_CB,
  NES_LB,
  NEP_LB,
  DUMP_PHY_REG,
  SET_PORT,
  SET_NUM_LANES,
  SET_LANE_SPEED,
  TX_BIST_PHY_NUM,
  TX_BIST_LANE_NUM,
  RX_BIST_PHY_NUM,
  RX_BIST_LANE_NUM,
  PRBS_PATTERN,
  UDP_DATA,
  BIST_DURATION,
  BIST_ERROR_COUNT,
  ENABLE_TX_BIST,
  RX_CDR_CHECKER,
  ENABLE_RX_BIST,
  CHECK_PRBS_ALL_LANES
};

int                                        qcom_aw_phy_attr_val;
enum mtip_port_type_enum                   port_type = MTIP_PORT_TYPE_FH_0;
int                                        num_lanes = 4;
enum eth_phy_iface_phy_lane_speed_enum     lane_speed = PHY_LANE_SPEED_25G;

// PRBS parameters
enum qcom_aw_phy_instance_enum         tx_bist_phy_inst = QCOM_AW_PHY_INST_FH0;
enum eth_phy_iface_phy_lane_num_enum   tx_bist_lane_num = PHY_LANE_0;
enum qcom_aw_phy_instance_enum         rx_bist_phy_inst = QCOM_AW_PHY_INST_FH0;
enum eth_phy_iface_phy_lane_num_enum   rx_bist_lane_num = PHY_LANE_0;
aw_bist_pattern_t                      bist_pattern = AW_PRBS31;
int                                    measure_time = 1;
int                                    inject_error_count = 0;
uint64_t                               user_data = 0;
uint32_t                               err_count_overflow[12] = {0};
uint64_t                               err_count[12] = {0};
uint64_t                               ber[12] = {0};
bool                                   check_prbs_all_lanes = false;

extern struct eth_phy_iface_ops qcom_aw_phy_driver_iface_ops;

#define MIN(a,b) ((a < b) ? a : b)

char help_menu[] = {
"1		ETH PHY drivers interface registration(dummy MAC/PHY registration)\n\
2		PHY setup from MAC\n\
3		PHY bring up from MAC\n\
4		PHY tear down from MAC\n\
5		MAC link up status to PHY\n\
6		MAC link down status to PHY\n\
7		ETH PHY drivers interface deregistration\n\
8		SNR valid status change from PHY to SyncE\n\
9		AN done callback from PHY to MAC\n\
10		Sets near end serial loopback mode on PHY\n\
11		Sets near end parallel loopback mode on PHY\n\
12		Dumps PHY registers to /tmp/phy_registers.txt on target\n\
13,x	Sets the port type for set up/bring up/tear down operations\n\
		(Value 'x' can be 0-FH0, 1-FH1, 2-FH2, 3-L2, 4-Debug)\n\
		For example, echo 13,0 > /sys/kernel/debug/qcom_aw_phy_test/qcom_aw_phy\n\
		This will configure port as FH0, and all further operations will correspond to the last configured port.\n\
14,x	Sets the number of lanes for set up/bring up/tear down operations\n\
		(Value 'x' can be 1/2/3/4 based on the number of lanes to be configured)\n\
		For example, echo 14,4 > /sys/kernel/debug/qcom_aw_phy_test/qcom_aw_phy\n\
		This will configure number of lanes as 4, and all further operations will correspond to the last configured number of lanes.\n\
15,x	Sets the lane speed for set up/bring up/tear down operations\n\
		(Value 'x' can be 0-10G, 1-25G, 2-50G, 3-100G)\n\
		For example, echo 15,1 > /sys/kernel/debug/qcom_aw_phy_test/qcom_aw_phy\n\
		This will configure lane speed as 25G, and all further operations will correspond to this lane speed for all the lanes specified above.\n\
16,x	Sets the PHY instance type for TX BIST generator\n\
		(Value 'x' can be 0-FH0, 1-FH1, 2-FH2, 3-L2, 4-Debug)\n\
17,x	Sets the PHY lane number 'x' for TX BIST generator\n\
18,x	Sets the PHY instance type for RX BIST checker\n\
		(Value 'x' can be 0-FH0, 1-FH1, 2-FH2, 3-L2, 4-Debug)\n\
19,x	Sets the PHY lane number 'x' for RX BIST checker\n\
20,x	Sets the PRBS BIST pattern. Value 'x' can be set from one of the below patterns\n\
		AW_PRBS7 = 0,\n\
		AW_PRBS9 = 1,\n\
		AW_PRBS11 = 2,\n\
		AW_PRBS13 = 3,\n\
		AW_PRBS15 = 4,\n\
		AW_PRBS23 = 5,\n\
		AW_PRBS31 = 6,\n\
		AW_QPRBS13 = 7,\n\
		AW_JP03A = 8,\n\
		AW_JP03B = 9,\n\
		AW_LINEARITY_PATTERN = 10,\n\
		AW_USER_DEFINED_PATTERN = 11,\n\
		AW_FULL_RATE_CLOCK = 12,\n\
		AW_HALF_RATE_CLOCK = 13,\n\
		AW_QUARTER_RATE_CLOCK = 14,\n\
		AW_PATT_32_1S_32_0S = 15\n\
21,x	Sets the user data pattern in hex if BIST pattern is selected as AW_USER_DEFINED_PATTERN = 11 in the above option\n\
22,x	Sets the duration in 'x' seconds to monitor pattern on RX checker side.\n\
23,x	Sets the number of errors 'x' to be injected from TX BIST generator. Default is 0.\n\
24,x	Enables/disables TX BIST generator based on value 'x' (0-disable/1-enable)\n\
25		Checks RX CDR lock on RX PHY and lane set with options 18 and 19 respectively.\n\
26,x	Enables/disables RX BIST checker based on value 'x' (0-disable/1-enable)\n\
27,x	Flag to configure if PRBS needs to be validated for all lanes\n"};

void qcom_aw_phy_setup_sysfs() {

  /* creating the directory structure in /sys/kernel/debug */
  dobj = debugfs_create_dir("qcom_aw_phy_test", NULL);

  debugfs_create_file("qcom_aw_phy", 0644, dobj, 0, &qcom_aw_phy_debug_fs_ops);

  debugfs_create_file("prbs_result", 0644, dobj, 0,
                      &qcom_aw_phy_debug_fs_prbs_result_ops);

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

void qcom_aw_phy_cdr_lock_cb(enum mtip_port_type_enum port_type,
                                enum eth_phy_iface_phy_lane_num_enum lane_num,
                                bool status) {
  QCOM_AW_PHY_LOG_ERR("CDR lock for port %d, lane %d, status", port_type,
                      lane_num, status);
}
ssize_t qcom_aw_phy_get_prbs_result(struct file *file, char __user *buf,
                                    size_t count, loff_t *ppos){
  char dbg_buf[1500] = {0};
  int nbytes = 0, i, j, min, max, min_port, max_port, lane_index;

  if(rx_bist_lane_num != PHY_LANE_MAX){
    min = rx_bist_lane_num;
    max = rx_bist_lane_num;
  }
  else{
    min = PHY_LANE_0;
    max = PHY_LANE_3;
  }

  if(check_prbs_all_lanes == false){
    min_port = rx_bist_phy_inst;
    max_port = rx_bist_phy_inst;
  }
  else{
    min_port = QCOM_AW_PHY_INST_FH0;
    max_port = QCOM_AW_PHY_INST_FH2;
  }

  for (j = min_port; j <= max_port; j++) {
    for (i = min; i <= max; i++) {
      lane_index = (j*PHY_LANE_MAX) + i;
      nbytes += scnprintf(dbg_buf + strlen(dbg_buf), 120,
                          "Port %d, Lane %d, error count = %lu, "
                          "error overflow count = %d, ber = %lu\n",
                          j, i, err_count[lane_index],
                          err_count_overflow[lane_index], ber[lane_index]);
    }
  }

  return simple_read_from_buffer(buf, count, ppos, dbg_buf, nbytes);
}

ssize_t qcom_aw_phy_get_attr(struct file *file, char __user *buf,
                             size_t count, loff_t *ppos) {
  return simple_read_from_buffer(buf, count, ppos, help_menu, sizeof(help_menu));
}

ssize_t qcom_aw_phy_set_attr(struct file *file, const char __user *buf,
                             size_t count, loff_t *ppos) {
  struct eth_phy_iface_eth_register_params ready_info;
  bool is_phy_ready;
  struct eth_phy_iface_phy_lane_config lane_config[PHY_LANE_MAX];
  int i = 0, j = 0, k = 0;
  int min = 0, max = 0, min_port = 0, max_port = 0, lane_index = 0;
  bool lanes_enabled[PHY_LANE_MAX] = {true, true, true, true};
  struct qcom_aw_phy_synce_snr_valid_change snr_valid_info;
  char *token;
  char token_string[100];
  char *save_ptr = NULL;
  struct qcom_aw_phy_config *phy_config_info = NULL;
  struct qcom_aw_phy_inst_config *phy_inst_info = NULL;
  mss_access_t mss = {.phy_offset = 0, .lane_offset = 0};
  struct qcom_aw_phy_inst_config *tx_phy_inst_info = NULL;
  mss_access_t tx_mss = {.phy_offset = 0, .lane_offset = 0};
  int enable_flag = 0;
  uint32_t err_cnt_55_32, err_cnt_31_0;
  bool error = false;

  memset(token_string, 0, sizeof(token_string));
  if (copy_from_user(&token_string, buf, MIN(sizeof(token_string), count))){
    QCOM_AW_PHY_LOG_ERR("Copy from user failed");
    return -EFAULT;
  }

  token = qcom_aw_phy_strtok(token_string, ',', &save_ptr);
  sscanf(token, "%d", &qcom_aw_phy_attr_val);

  QCOM_AW_PHY_LOG_ERR("qcom_aw_phy_set_attr val %d", qcom_aw_phy_attr_val);

  switch (qcom_aw_phy_attr_val) {

    case PHY_REG:
      QCOM_AW_PHY_LOG_ERR("Register");
      ready_info.notify_ready = qcom_aw_phy_ready_cb;
      ready_info.userdata_ready = NULL;
      ready_info.notify_an_complete = qcom_aw_phy_an_complete_cb;
      ready_info.cdr_lock_cb = qcom_aw_phy_cdr_lock_cb;
      qcom_aw_phy_driver_iface_ops.eth_phy_iface_eth_register(&ready_info,
                                                              &is_phy_ready);
      QCOM_AW_PHY_LOG_ERR("is_phy_ready %d", is_phy_ready);
      break;

    case PHY_SETUP:
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

    case PHY_BRINGUP:
      QCOM_AW_PHY_LOG_ERR("Bringup");
      memset(lanes_enabled, 0, PHY_LANE_MAX * sizeof(bool));
      for (i = PHY_LANE_0; i < num_lanes; i++) {
        lanes_enabled[i] = true;
      }
      qcom_aw_phy_driver_iface_ops.eth_phy_iface_phy_bringup(port_type,
                                                             lanes_enabled, 0);
      break;

    case PHY_TEAR_DOWN:
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

    case MAC_LINK_UP:
      QCOM_AW_PHY_LOG_ERR("MAC link status up");
      memset(lanes_enabled, 0, PHY_LANE_MAX * sizeof(bool));
      for (i = PHY_LANE_0; i < num_lanes; i++) {
        lanes_enabled[i] = true;
      }
      qcom_aw_phy_driver_iface_ops.eth_phy_iface_notify_mac_link_status(
          port_type, lanes_enabled, true);
      break;

    case MAC_LINK_DOWN:
      QCOM_AW_PHY_LOG_ERR("MAC link status down");
      memset(lanes_enabled, 0, PHY_LANE_MAX * sizeof(bool));
      for (i = PHY_LANE_0; i < num_lanes; i++) {
        lanes_enabled[i] = true;
      }
      qcom_aw_phy_driver_iface_ops.eth_phy_iface_notify_mac_link_status(
          port_type, lanes_enabled, false);
      break;

    case PHY_DEREG:
      QCOM_AW_PHY_LOG_ERR("Deregister");
      qcom_aw_phy_driver_iface_ops.eth_phy_iface_eth_deregister();
      break;

    case SNR_VALID_CB:
      QCOM_AW_PHY_LOG_ERR("SNR valid status change");
      snr_valid_info.lane_id = FH0_LANE_0;
      snr_valid_info.snr_valid_status = true;
      qcom_aw_phy_gnl_snr_valid_change(snr_valid_info);
      break;

    case AN_DONE_CB:
      QCOM_AW_PHY_LOG_ERR("AN done callback simulation");
      for (i = PHY_LANE_0; i < num_lanes; i++) {
        qcom_aw_phy_notify_an_complete(
                               qcom_aw_phy_mac_port_to_phy_inst(port_type), i);
      }
      break;

    case NES_LB:
      QCOM_AW_PHY_LOG_ERR("Set near end serial loopback mode !");
      qcom_aw_phy_set_loopback_mode(QCOM_AW_PHY_NEAR_END_SERIAL_LB);
      break;

    case NEP_LB:
      QCOM_AW_PHY_LOG_ERR("Set near end parallel loopback mode !");
      qcom_aw_phy_set_loopback_mode(QCOM_AW_PHY_NEAR_END_PARALLEL_LB);
      break;

    case DUMP_PHY_REG:
      QCOM_AW_PHY_LOG_ERR("Dumping PHY registers !");
      qcom_aw_phy_dump_registers();
      break;

    case SET_PORT:
      token = qcom_aw_phy_strtok(NULL, ',', &save_ptr);
      sscanf(token, "%d", &port_type);

      if(port_type < MTIP_PORT_TYPE_FH_0 || port_type >= MTIP_PORT_TYPE_MAX){
        port_type = MTIP_PORT_TYPE_FH_0;
        error = true;
      }

      QCOM_AW_PHY_LOG_ERR("Configuring port %d", port_type);
      break;

    case SET_NUM_LANES:
      token = qcom_aw_phy_strtok(NULL, ',', &save_ptr);
      sscanf(token, "%d", &num_lanes);

      if(num_lanes < 1 || num_lanes > PHY_LANE_MAX){
        num_lanes = 1;
        error = true;
      }

      QCOM_AW_PHY_LOG_ERR("Configuring num_lanes %d", num_lanes);
      break;

    case SET_LANE_SPEED:
      token = qcom_aw_phy_strtok(NULL, ',', &save_ptr);
      sscanf(token, "%d", &lane_speed);

      if(lane_speed < PHY_LANE_SPEED_10G || lane_speed >= PHY_LANE_SPEED_MAX){
        lane_speed = PHY_LANE_SPEED_25G;
        error = true;
      }

      QCOM_AW_PHY_LOG_ERR("Configuring lane_speed %d", lane_speed);
      break;

    case TX_BIST_PHY_NUM:
      token = qcom_aw_phy_strtok(NULL, ',', &save_ptr);
      sscanf(token, "%d", &tx_bist_phy_inst);

      if(!QCOM_AW_PHY_INST_VALID(tx_bist_phy_inst)){
        tx_bist_phy_inst = QCOM_AW_PHY_INST_FH0;
        error = true;
      }

      QCOM_AW_PHY_LOG_ERR("Configuring TX BIST PHY instance %d",
                          tx_bist_phy_inst);
      break;

    case TX_BIST_LANE_NUM:
      token = qcom_aw_phy_strtok(NULL, ',', &save_ptr);
      sscanf(token, "%d", &tx_bist_lane_num);

      if(tx_bist_lane_num > PHY_LANE_MAX){
        tx_bist_lane_num = PHY_LANE_0;
        error = true;
      }

      QCOM_AW_PHY_LOG_ERR("Configuring TX BIST PHY lane %d",
                          tx_bist_lane_num);
      break;

    case RX_BIST_PHY_NUM:
      token = qcom_aw_phy_strtok(NULL, ',', &save_ptr);
      sscanf(token, "%d", &rx_bist_phy_inst);

      if(!QCOM_AW_PHY_INST_VALID(rx_bist_phy_inst)){
        rx_bist_phy_inst = QCOM_AW_PHY_INST_FH0;
        error = true;
      }

      QCOM_AW_PHY_LOG_ERR("Configuring RX BIST PHY instance %d",
                          rx_bist_phy_inst);
      break;

    case RX_BIST_LANE_NUM:
      token = qcom_aw_phy_strtok(NULL, ',', &save_ptr);
      sscanf(token, "%d", &rx_bist_lane_num);

      if(rx_bist_lane_num > PHY_LANE_MAX){
        rx_bist_lane_num = PHY_LANE_0;
        error = true;
      }

      QCOM_AW_PHY_LOG_ERR("Configuring RX BIST PHY lane %d",
                          rx_bist_lane_num);
      break;

    case PRBS_PATTERN:
      token = qcom_aw_phy_strtok(NULL, ',', &save_ptr);
      sscanf(token, "%d", &bist_pattern);

      if(bist_pattern >= AW_BIST_PATTERN_MAX){
        bist_pattern = AW_PRBS31;
        error = true;
      }

      QCOM_AW_PHY_LOG_ERR("Configuring BIST pattern %d", bist_pattern);
      break;

    case UDP_DATA:
      token = qcom_aw_phy_strtok(NULL, ',', &save_ptr);
      sscanf(token, "%llx", &user_data);
      QCOM_AW_PHY_LOG_ERR("Configuring user data %llx", user_data);
      break;

    case BIST_DURATION:
      token = qcom_aw_phy_strtok(NULL, ',', &save_ptr);
      sscanf(token, "%d", &measure_time);
      QCOM_AW_PHY_LOG_ERR("Configuring measurement time %d", measure_time);
      break;

    case BIST_ERROR_COUNT:
      token = qcom_aw_phy_strtok(NULL, ',', &save_ptr);
      sscanf(token, "%d", &inject_error_count);
      QCOM_AW_PHY_LOG_ERR("Configuring inject error count %d",
                          inject_error_count);
      break;

    case ENABLE_TX_BIST:
      token = qcom_aw_phy_strtok(NULL, ',', &save_ptr);
      sscanf(token, "%d", &enable_flag);
      QCOM_AW_PHY_LOG_ERR("Configuring TX BIST, enabled = %d", enable_flag);

      phy_config_info = qcom_aw_phy_get_config_info();

      if(tx_bist_lane_num != PHY_LANE_MAX){
        min = tx_bist_lane_num;
        max = tx_bist_lane_num;
      }
      else{
        min = PHY_LANE_0;
        max = PHY_LANE_3;
      }

      if(check_prbs_all_lanes == false){
        min_port = tx_bist_phy_inst;
        max_port = tx_bist_phy_inst;
      }
      else{
        min_port = QCOM_AW_PHY_INST_FH0;
        max_port = QCOM_AW_PHY_INST_FH2;
      }

      for (j = min_port; j <= max_port; j++) {

        phy_inst_info = &phy_config_info->phy_inst_config_info[j];
        mss.phy_offset = phy_inst_info->base_addr;
        QCOM_AW_PHY_LOG_ERR("TX BIST for port %d", j);

        for (i = min; i <= max; i++) {
          QCOM_AW_PHY_LOG_ERR("TX BIST for lane %d", i);
          pmd_set_lane(&mss, i);
          if(enable_flag){
            aw_pmd_tx_gen_config_set(&mss, bist_pattern, user_data, user_data);
            aw_pmd_gen_tx_en_set(&mss, 1);
          }
          else{
            aw_pmd_gen_tx_en_set(&mss, 0);
          }
        }
      }
      break;

    case RX_CDR_CHECKER:
      QCOM_AW_PHY_LOG_ERR("Checking RX CDR lock for PHY %d, lane %d", 
                          rx_bist_phy_inst, rx_bist_lane_num);
      phy_config_info = qcom_aw_phy_get_config_info();
      phy_inst_info = &phy_config_info->phy_inst_config_info[rx_bist_phy_inst];
      mss.phy_offset = phy_inst_info->base_addr;
      pmd_set_lane(&mss, rx_bist_lane_num);
      aw_pmd_rx_check_cdr_lock(&mss, RX_CDR_TIMEOUT_US);
      break;

    case ENABLE_RX_BIST:
      token = qcom_aw_phy_strtok(NULL, ',', &save_ptr);
      sscanf(token, "%d", &enable_flag);
      QCOM_AW_PHY_LOG_ERR("Configuring RX BIST, enabled = %d", enable_flag);

      phy_config_info = qcom_aw_phy_get_config_info();

      if(rx_bist_lane_num != PHY_LANE_MAX){
        min = rx_bist_lane_num;
        max = rx_bist_lane_num;
      }
      else{
        min = PHY_LANE_0;
        max = PHY_LANE_3;
      }

      if(check_prbs_all_lanes == false){
        min_port = rx_bist_phy_inst;
        max_port = rx_bist_phy_inst;
      }
      else{
        min_port = QCOM_AW_PHY_INST_FH0;
        max_port = QCOM_AW_PHY_INST_FH2;
      }

      if(enable_flag){

        for (j = min_port; j <= max_port; j++) {
          phy_inst_info = &phy_config_info->phy_inst_config_info[j];
          mss.phy_offset = phy_inst_info->base_addr;
          QCOM_AW_PHY_LOG_ERR("RX BIST for port %d", j);

          for (i = min; i <= max; i++) {
            QCOM_AW_PHY_LOG_ERR("RX BIST checker for lane %d", i);
            pmd_set_lane(&mss, i);

            aw_pmd_rx_chk_config_set(&mss, bist_pattern, AW_DWELL,
                                     user_data, user_data, 2, 2000);
            aw_pmd_rx_chk_en_set(&mss, 1);
            CHECK(pmd_write_field(&mss, RX_DATABIST_TOP_REG1_ADDR,
                                  RX_DATABIST_TOP_REG1_BIST_ENABLE_A_MASK,
                                  RX_DATABIST_TOP_REG1_BIST_ENABLE_A_OFFSET, 0));
            CHECK(pmd_write_field(&mss, RX_DATABIST_TOP_REG1_ADDR,
                                  RX_DATABIST_TOP_REG1_BIST_ENABLE_A_MASK,
                                  RX_DATABIST_TOP_REG1_BIST_ENABLE_A_OFFSET, 1));
            CHECK(pmd_write_field(&mss, RX_DATABIST_TOP_REG1_ADDR,
                                  RX_DATABIST_TOP_REG1_ERROR_CNT_CLR_A_MASK,
                                  RX_DATABIST_TOP_REG1_ERROR_CNT_CLR_A_OFFSET, 0));
            CHECK(pmd_write_field(&mss, RX_DATABIST_TOP_REG1_ADDR,
                                  RX_DATABIST_TOP_REG1_ERROR_CNT_CLR_A_MASK,
                                  RX_DATABIST_TOP_REG1_ERROR_CNT_CLR_A_OFFSET, 1));
            CHECK(pmd_write_field(&mss, RX_DATABIST_TOP_REG1_ADDR,
                                  RX_DATABIST_TOP_REG1_ERROR_CNT_CLR_A_MASK,
                                  RX_DATABIST_TOP_REG1_ERROR_CNT_CLR_A_OFFSET, 0));
          }
        }

        USR_SLEEP(1000000 * measure_time);

        for (j = min_port; j <= max_port; j++) {
          phy_inst_info = &phy_config_info->phy_inst_config_info[j];
          mss.phy_offset = phy_inst_info->base_addr;
          QCOM_AW_PHY_LOG_ERR("RX BIST for port %d", j);
          if(check_prbs_all_lanes == false)
            tx_phy_inst_info = &phy_config_info->phy_inst_config_info[tx_bist_phy_inst];
          else
            tx_phy_inst_info = &phy_config_info->phy_inst_config_info[j];
          tx_mss.phy_offset = tx_phy_inst_info->base_addr;

          for (i = min; i <= max; i++) {
            QCOM_AW_PHY_LOG_ERR("RX BIST checker for lane %d", i);
            pmd_set_lane(&mss, i);
            if(tx_bist_lane_num != PHY_LANE_MAX)
              pmd_set_lane(&tx_mss, tx_bist_lane_num);
            else
              pmd_set_lane(&tx_mss, i);

            if(inject_error_count > 0){
              for (k = 0; k < inject_error_count; k++) {
                udelay(1);
                aw_pmd_tx_gen_err_inject_en_set(&tx_mss,1);
                udelay(1);
                aw_pmd_tx_gen_err_inject_en_set(&tx_mss,0);
              }
            }

            lane_index = (j*PHY_LANE_MAX) + i;
            err_count[lane_index] = 0;
            err_count_overflow[lane_index] = 0;
            ber[lane_index] = 0;

            CHECK(pmd_read_field(&mss, RX_DATABIST_TOP_RDREG3_ADDR,
                  RX_DATABIST_TOP_RDREG3_ERROR_CNT_55T32_NT_MASK,
                  RX_DATABIST_TOP_RDREG3_ERROR_CNT_55T32_NT_OFFSET,
                  &err_cnt_55_32));
            CHECK(pmd_read_field(&mss, RX_DATABIST_TOP_RDREG2_ADDR,
                  RX_DATABIST_TOP_RDREG2_ERROR_CNT_NT_MASK,
                  RX_DATABIST_TOP_RDREG2_ERROR_CNT_NT_OFFSET,
                  &err_cnt_31_0));
            err_count[lane_index] += (uint64_t)err_cnt_55_32 << 32 | (uint64_t)err_cnt_31_0;
            CHECK(pmd_read_check_field(
                  &mss, RX_DATABIST_TOP_RDREG1_ADDR,
                  RX_DATABIST_TOP_RDREG1_ERROR_CNT_OVERFLOW_NT_MASK,
                  RX_DATABIST_TOP_RDREG1_ERROR_CNT_OVERFLOW_NT_OFFSET, RD_EQ,
                  &err_count_overflow[lane_index], 0, 0));
            ber[lane_index] += (uint64_t)err_count[lane_index] / (measure_time * 25);
            QCOM_AW_PHY_LOG_ERR("err_count = %lu\n", err_count[lane_index]);
            QCOM_AW_PHY_LOG_ERR("err_count_overflow = %d\n", err_count_overflow[lane_index]);
            QCOM_AW_PHY_LOG_ERR("ber = %lu\n", ber[lane_index]);
          }
        }
      }
      else{
        for (j = min_port; j <= max_port; j++) {
          phy_inst_info = &phy_config_info->phy_inst_config_info[j];
          mss.phy_offset = phy_inst_info->base_addr;
          QCOM_AW_PHY_LOG_ERR("RX BIST for port %d", j);

          for (i = min; i <= max; i++) {
            QCOM_AW_PHY_LOG_ERR("Disabling RX BIST for lane %d", i);
            pmd_set_lane(&mss, i);
            aw_pmd_rx_chk_en_set(&mss, 0);
          }
        }
      }

      break;

    case CHECK_PRBS_ALL_LANES:
      token = qcom_aw_phy_strtok(NULL, ',', &save_ptr);
      sscanf(token, "%d", &enable_flag);
      QCOM_AW_PHY_LOG_ERR("Checking PRBS for all lanes = %d", enable_flag);
      check_prbs_all_lanes = enable_flag;
      break;

    default:
      error = true;
      break;
  }

  if(error)
    QCOM_AW_PHY_LOG_ERR("Invalid input, \"cat /sys/kernel/debug/qcom_aw_phy_test/qcom_aw_phy\" for help menu");

  return count;
}

#endif /* FEATURE_QCOM_AW_TEST_SYS_FS */
