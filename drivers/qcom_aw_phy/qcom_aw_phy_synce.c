/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/**
  @file qcom_aw_phy_synce.c
  @brief Interface file between AW PHY and SyncE application.

  This file contains interface handling betwen AW PHY driver and
  SyncE application.
*/

#include <linux/clk.h>
#include <linux/reset.h>

#include "qcom_aw_phy_main.h"
#include "qcom_aw_phy_mtip_if.h"
#include "qcom_aw_phy_synce.h"
#include "qcom_aw_phy_utils.h"
#include "qcom_aw_phy_gnl.h"
#include "eth_phy_iface.h"
#include "aw_c_api/aw_alphacore.h"
#include "aw_c_api/aw_driver_sim.h"
#include "aw_c_api/interface.h"


/*-------------------------------------------------------------------
* qcom_aw_phy_synce_notify_phy_lane_state_change

* @phy_inst: PHY Instance type(FH/C2C/Debug)
* @lane_num: PHY Lane number.

* Description: This function notifies lane state change to .SyncE application.
------------------------------------------------------------------- */
void qcom_aw_phy_synce_notify_phy_lane_state_change() {

  struct qcom_aw_phy_config *phy_config_info = NULL;
  enum qcom_aw_phy_instance_enum phy_inst_type = QCOM_AW_PHY_INST_FH0;
  struct qcom_aw_phy_inst_config *phy_inst_info = NULL;
  enum eth_phy_iface_phy_lane_num_enum lane_num;
  enum qcom_aw_phy_synce_eth_inst synce_eth_num;
  struct qcom_aw_phy_gnl_eth_status eth_status[MAX_ETH_NUM];
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;

  phy_config_info = qcom_aw_phy_get_config_info();
  if (!phy_config_info) {
    local_err_val = LOCAL_ERROR_0;
    goto func_exit;
  }

  memset(eth_status, 0,
         sizeof(struct qcom_aw_phy_gnl_eth_status) * MAX_ETH_NUM);

  for (phy_inst_type = QCOM_AW_PHY_INST_FH0;
       phy_inst_type <= QCOM_AW_PHY_INST_L2; phy_inst_type++) {

    phy_inst_info = &phy_config_info->phy_inst_config_info[phy_inst_type];
    if (phy_inst_info->valid) {
      for (lane_num = PHY_LANE_0; lane_num < PHY_LANE_MAX; lane_num++) {
        if (phy_inst_info->lane_params[lane_num].link_status) {
          synce_eth_num = qcom_aw_phy_synce_phy_lane_to_eth_inst(phy_inst_type,
                                                                 lane_num);
          eth_status[synce_eth_num].eth_status = true;
          eth_status[synce_eth_num].lane_speed =
              phy_inst_info->lane_params[lane_num].lane_config.lane_speed;
        }
      }
    }
  }

  // Send netlink message with lane_status for all lanes
  qcom_aw_phy_gnl_eth_status_change(eth_status);

func_exit:
  QCOM_AW_PHY_LOG_ERR("qcom_aw_phy_synce_notify_phy_lane_state_change, "
                      "local error %d",
                      local_err_val);

  return;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_synce_notify_snr_valid_change

* @phy_inst: PHY Instance type(FH/C2C/Debug)
* @lane_num: PHY Lane number.

* Description: This function notifies SNR valid change to .SyncE application.
------------------------------------------------------------------- */
void qcom_aw_phy_synce_notify_snr_valid_change(
    enum qcom_aw_phy_instance_enum phy_inst,
    enum eth_phy_iface_phy_lane_num_enum lane_num, bool valid) {

  struct qcom_aw_phy_gnl_snr_valid_change snr_valid_info = {0};
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;

  if (!QCOM_AW_PHY_INST_VALID(phy_inst) || !QCOM_AW_PHY_LANE_VALID(lane_num)) {
    local_err_val = LOCAL_ERROR_0;
    goto func_exit;
  }

  snr_valid_info.eth_inst = qcom_aw_phy_synce_phy_lane_to_eth_inst(phy_inst,
                                                                   lane_num);
  snr_valid_info.snr_valid_status = valid;

  // Send netlink message with SNR valid status for this lane
  qcom_aw_phy_gnl_snr_valid_change(snr_valid_info);

func_exit:
  QCOM_AW_PHY_LOG_ERR(
      "qcom_aw_phy_synce_notify_snr_valid_change, local error %d",
      local_err_val);
  return;
}

void qcom_aw_phy_synce_handle_snr_valid_change(
  struct work_struct *work){
  struct delayed_work *delayed_work_item = to_delayed_work(work);
  struct qcom_aw_phy_work_q_params *wq_params =
     container_of(delayed_work_item, struct qcom_aw_phy_work_q_params, wq_item);

  if(!wq_params)
    QCOM_AW_PHY_LOG_ERR("Invalid work queue structure!");

  QCOM_AW_PHY_LOG_ERR("SNR valid %d rcvd for PHY %d lane %d",
                      (bool)wq_params->user_data, wq_params->phy_inst,
                      wq_params->lane_num);

  qcom_aw_phy_synce_notify_snr_valid_change(wq_params->phy_inst,
                                            wq_params->lane_num,
                                            (bool)wq_params->user_data);

  kfree(wq_params);
  return;
}


/*-------------------------------------------------------------------
* aw_phy_synce_set_snr_threshold

* @phy_inst: PHY Instance type(FH/C2C/Debug)
* @lane_num: PHY Lane number.

* Description: This function sets the valid SNR threshold.
------------------------------------------------------------------- */
int qcom_aw_phy_synce_set_snr_threshold(
    enum qcom_aw_phy_instance_enum phy_inst,
    enum eth_phy_iface_phy_lane_num_enum lane_num, int snr_low_val,
    int snr_high_val) {
  struct qcom_aw_phy_config *phy_config_info = NULL;
  struct qcom_aw_phy_inst_config *phy_inst_info = NULL;
  struct qcom_aw_phy_lane_speed_config config;
  mss_access_t mss = {.phy_offset = 0, .lane_offset = 0};
  u32 nrz_mode = 0;
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;
  int ret_val = 0;

  if (!QCOM_AW_PHY_INST_VALID(phy_inst) || !QCOM_AW_PHY_LANE_VALID(lane_num)) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_0;
    goto func_exit;
  }

  phy_config_info = qcom_aw_phy_get_config_info();
  if (!phy_config_info) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_1;
    goto func_exit;
  }

  phy_inst_info = &phy_config_info->phy_inst_config_info[phy_inst];
  if (phy_inst_info->valid == false) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_2;
    goto func_exit;
  }

  /* Setup PHY and lane offsets */
  mss.phy_offset = phy_inst_info->base_addr;
  pmd_set_lane(&mss, lane_num);

  qcom_aw_phy_get_lane_speed_config(
      phy_inst_info->lane_params[lane_num].lane_config.lane_speed, &config);
  if (config.mod_tech == QCOM_AW_PHY_MOD_TECH_NRZ) {
    nrz_mode = 1;
  }

  pmd_write_field(&mss, RX_SNR_REG4_ADDR,
                  RX_SNR_REG4_VLD_HYS_THRESH_LOW_NT_MASK,
                  RX_SNR_REG4_VLD_HYS_THRESH_LOW_NT_OFFSET, snr_low_val);
  pmd_write_field(&mss, RX_SNR_REG5_ADDR,
                  RX_SNR_REG5_VLD_HYS_THRESH_HIGH_NT_MASK,
                  RX_SNR_REG5_VLD_HYS_THRESH_HIGH_NT_OFFSET, snr_high_val);

  aw_pmd_snr_mon_enable_set(&mss, nrz_mode, 1);
  aw_pmd_snr_vld_enable_set(&mss, 1);

func_exit:
  QCOM_AW_PHY_LOG_INFO("snr_low_val = %d, snr_high_val = %d, "
                       "ret_val %d, local error %d",
                       snr_low_val, snr_high_val, ret_val, local_err_val);

  return ret_val;
}

/*-------------------------------------------------------------------
* aw_phy_synce_get_current_snr_val

* @phy_inst: PHY Instance type(FH/C2C/Debug)
* @lane_num: PHY Lane number.

* Description: This function gets the current SNR value of the passed lane.
------------------------------------------------------------------- */
int qcom_aw_phy_synce_get_current_snr_val(
    enum qcom_aw_phy_instance_enum phy_inst,
    enum eth_phy_iface_phy_lane_num_enum lane_num, int *snr_val) {
  struct qcom_aw_phy_config *phy_config_info = NULL;
  struct qcom_aw_phy_inst_config *phy_inst_info = NULL;
  struct qcom_aw_phy_lane_speed_config config;
  mss_access_t mss = {.phy_offset = 0, .lane_offset = 0};
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;
  int ret_val = 0;

  if (!QCOM_AW_PHY_INST_VALID(phy_inst) || !QCOM_AW_PHY_LANE_VALID(lane_num)) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_0;
    goto func_exit;
  }

  phy_config_info = qcom_aw_phy_get_config_info();
  if (!phy_config_info) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_1;
    goto func_exit;
  }

  phy_inst_info = &phy_config_info->phy_inst_config_info[phy_inst];
  if (phy_inst_info->valid == false) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_2;
    goto func_exit;
  }

  /* Setup PHY and lane offsets */
  mss.phy_offset = phy_inst_info->base_addr;
  pmd_set_lane(&mss, lane_num);

  qcom_aw_phy_get_lane_speed_config(
      phy_inst_info->lane_params[lane_num].lane_config.lane_speed, &config);

  memset(snr_val, 0, sizeof(int) * 3);

  pmd_write_field(&mss, RX_SNR_REG7_ADDR,
                  RX_SNR_REG7_RO_CSR_CAPTURE_A_MASK,
                  RX_SNR_REG7_RO_CSR_CAPTURE_A_OFFSET, 1);
  pmd_write_field(&mss, RX_SNR_REG7_ADDR,
                  RX_SNR_REG7_RO_CSR_CAPTURE_A_MASK,
                  RX_SNR_REG7_RO_CSR_CAPTURE_A_OFFSET, 0);

  if (config.mod_tech == QCOM_AW_PHY_MOD_TECH_NRZ) {
    pmd_read_field(&mss, RX_SNR_RDREG13_ADDR,
                   RX_SNR_RDREG13_MON_NRZ_EYE_NT_MASK,
                   RX_SNR_RDREG13_MON_NRZ_EYE_NT_OFFSET, &snr_val[0]);
  } else if (config.mod_tech == QCOM_AW_PHY_MOD_TECH_PAM4) {

    pmd_read_field(&mss, RX_SNR_RDREG10_ADDR, RX_SNR_RDREG10_MON_EYE0_NT_MASK,
                   RX_SNR_RDREG10_MON_EYE0_NT_OFFSET, &snr_val[0]);

    pmd_read_field(&mss, RX_SNR_RDREG11_ADDR, RX_SNR_RDREG11_MON_EYE1_NT_MASK,
                   RX_SNR_RDREG11_MON_EYE1_NT_OFFSET, &snr_val[1]);

    pmd_read_field(&mss, RX_SNR_RDREG12_ADDR, RX_SNR_RDREG12_MON_EYE2_NT_MASK,
                   RX_SNR_RDREG12_MON_EYE2_NT_OFFSET, &snr_val[2]);
  }

func_exit:
  QCOM_AW_PHY_LOG_INFO("mod_tech %d, snr0 = %d, snr1 = %d, snr2 = %d"
                       "ret_val %d, local error %d",
                       config.mod_tech, snr_val[0], snr_val[1], snr_val[2],
                       ret_val, local_err_val);

  return ret_val;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_synce_set_synce_mux

* @lane_num: Lane number for the selected RX lane clock.

* Description: This function sets the SyncE MUX for the desired RX
               lane clock.
------------------------------------------------------------------- */
int qcom_aw_phy_synce_set_synce_mux(
    enum qcom_aw_phy_synce_lane_id synce_lane_num) {

  struct qcom_aw_phy_config *phy_config_info = NULL;
  enum qcom_aw_phy_instance_enum phy_inst_type = QCOM_AW_PHY_INST_MAX;
  struct qcom_aw_phy_inst_config *phy_inst_info = NULL;
  enum eth_phy_iface_phy_lane_num_enum phy_inst_lane_num = PHY_LANE_MAX;
  struct qcom_aw_phy_lane_speed_config config = {0};
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;
  int ret_val = 0;

  phy_config_info = qcom_aw_phy_get_config_info();
  if (!phy_config_info) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_0;
    goto func_exit;
  }

  if(synce_lane_num == LANE_NONE){
    QCOM_AW_PHY_LOG_INFO("Disable ACGC output for LANE_NONE");
    reset_control_deassert(phy_config_info->acgc_reset_ctrl);
    return ret_val;
  }

  phy_inst_type = synce_lane_num / PHY_LANE_MAX;
  phy_inst_lane_num = synce_lane_num % PHY_LANE_MAX;
  if (!QCOM_AW_PHY_INST_VALID(phy_inst_type) ||
      !QCOM_AW_PHY_LANE_VALID(phy_inst_lane_num)) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_1;
    goto func_exit;
  }

  phy_inst_info = &phy_config_info->phy_inst_config_info[phy_inst_type];
  if (phy_inst_info->valid == false) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_2;
    goto func_exit;
  }

  // Disable SyncE ACGC output
  QCOM_AW_PHY_LOG_ERR("Disable ACGC output");
  reset_control_deassert(phy_config_info->acgc_reset_ctrl);

  // Select division ratio
  QCOM_AW_PHY_LOG_ERR("Select division ratio");
  qcom_aw_phy_get_lane_speed_config(
      phy_inst_info->lane_params[phy_inst_lane_num].lane_config.lane_speed,
      &config);
  clk_set_rate(phy_config_info->synce_cmux_clk,config.synce_cmux_clk_rate);
  clk_set_rate(phy_config_info->synce_div_clk,config.synce_div_clk_src_rate);

  // Select desired RX lane clock
  QCOM_AW_PHY_LOG_ERR("Select desired RX lane clock");
  ret_val = clk_set_parent(phy_config_info->synce_cmux_clk_src,
                        phy_config_info->synce_phy_lane_clk[synce_lane_num]);
  if (ret_val)
    QCOM_AW_PHY_LOG_ERR("clk_set_parent failed ret: %d", ret_val);

  // Enable SyncE ACGC output
  QCOM_AW_PHY_LOG_ERR("Enable ACGC output");
  reset_control_assert(phy_config_info->acgc_reset_ctrl);

func_exit:
  QCOM_AW_PHY_LOG_INFO("qcom_aw_phy_synce_set_synce_mux for lane %d"
                       "ret_val %d, local error %d",
                       synce_lane_num, ret_val, local_err_val);

  return ret_val;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_synce_eth_inst_to_phy_lane_id

* @eth_inst: ETH instance

* Return value : @lane_num: PHY lane number

* Description: This function takes ETH instance as an input
               and translates it into PHY lane id.
------------------------------------------------------------------- */
enum qcom_aw_phy_synce_lane_id qcom_aw_phy_synce_eth_inst_to_phy_lane_id(
      enum qcom_aw_phy_synce_eth_inst eth_inst){
  u32 i = 0;
  u32 eth_link_index;
  struct qcom_aw_phy_config *phy_config_info = NULL;
  enum qcom_aw_phy_instance_enum phy_inst_type = QCOM_AW_PHY_INST_MAX;
  struct qcom_aw_phy_inst_config *phy_inst_info = NULL;
  struct eth_phy_iface_phy_lane_config lane_config;
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;
  enum qcom_aw_phy_synce_lane_id ret_val = LANE_NONE;

  if (eth_inst <= ETH_NONE || eth_inst >= MAX_ETH_NUM) {
    local_err_val = LOCAL_ERROR_0;
    goto func_exit;
  }

  phy_inst_type = (enum qcom_aw_phy_instance_enum)(eth_inst/MAX_MAC_LINKS_PER_PORT);
  eth_link_index = eth_inst%4;

  phy_config_info = qcom_aw_phy_get_config_info();
  if (!phy_config_info) {
    local_err_val = LOCAL_ERROR_1;
    goto func_exit;
  }

  phy_inst_info = &phy_config_info->phy_inst_config_info[phy_inst_type];
  if (phy_inst_info->valid == false) {
    local_err_val = LOCAL_ERROR_2;
    goto func_exit;
  }

  for (i = 0; i < PHY_LANE_MAX; i++) {
    lane_config = phy_inst_info->lane_params[i].lane_config;
    if (lane_config.lane_enabled &&
        lane_config.link_index == eth_link_index){
        ret_val = (phy_inst_type*PHY_LANE_MAX)+i;
        break;
    }
  }

func_exit:
  QCOM_AW_PHY_LOG_ERR("%s: returns %d with local error %d", __func__, ret_val,
                      local_err_val);
  return ret_val;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_synce_phy_lane_to_eth_inst

* @PHY instance
* @PHY lane number

* Return value: @eth_inst: ETH instance

* Description: This function takes PHY lane id as an input
               and translates it into ETH instance 
------------------------------------------------------------------- */
enum qcom_aw_phy_synce_eth_inst qcom_aw_phy_synce_phy_lane_to_eth_inst(
      enum qcom_aw_phy_instance_enum phy_inst_type,
      enum eth_phy_iface_phy_lane_num_enum lane_num){
  u32 eth_link_index;
  struct qcom_aw_phy_config *phy_config_info = NULL;
  struct qcom_aw_phy_inst_config *phy_inst_info = NULL;
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;
  enum qcom_aw_phy_synce_eth_inst ret_val = ETH_NONE;

  phy_config_info = qcom_aw_phy_get_config_info();
  if (!phy_config_info) {
    local_err_val = LOCAL_ERROR_0;
    goto func_exit;
  }

  phy_inst_info = &phy_config_info->phy_inst_config_info[phy_inst_type];
  if (phy_inst_info->valid == false) {
    local_err_val = LOCAL_ERROR_1;
    goto func_exit;
  }

  eth_link_index = phy_inst_info->lane_params[lane_num].lane_config.link_index;

  ret_val = (phy_inst_type*MAX_MAC_LINKS_PER_PORT) + eth_link_index;

func_exit:
  QCOM_AW_PHY_LOG_ERR("%s: returns %d with local error %d", __func__, ret_val,
                      local_err_val);
  return ret_val;
}
