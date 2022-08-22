/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/**
  @file qcom_aw_phy_mtip_if.c
  @brief Interface file between AW PHY and MTIP MAC drivers.

  This file contains interface handling betwen AW PHY and MTIP MAC drivers.
*/

#include "qcom_aw_phy_main.h"
#include "qcom_aw_phy_mtip_if.h"
#include "eth_phy_iface.h"
#include "qcom_aw_phy_synce.h"
#include "qcom_aw_phy_utils.h"
#include "aw_c_api/aw_alphacore.h"
#include "aw_c_api/aw_driver_sim.h"

#include <linux/mutex.h>

struct qcom_aw_phy_mtip_if_info qcom_aw_phy_mtip_if_info_s = {0};

/*-------------------------------------------------------------------
* Function Definitions
------------------------------------------------------------------- */
void qcom_aw_phy_set_drv_ready(void) {
  QCOM_AW_PHY_LOG_INFO("qcom_aw_phy_set_drv_ready !");

  // Acquire mutex
  mutex_lock(&qcom_aw_phy_mtip_if_info_s.lock);

  // Set PHY driver as ready
  qcom_aw_phy_mtip_if_info_s.is_phy_drv_ready = true;

  // Inform if MAC driver is ready and not notified yet
  if ((qcom_aw_phy_mtip_if_info_s.is_mac_drv_ready == true) &&
      (qcom_aw_phy_mtip_if_info_s.is_ready_notified == false)) {

    if (qcom_aw_phy_mtip_if_info_s.ready_cb) {
      qcom_aw_phy_mtip_if_info_s.ready_cb(
          qcom_aw_phy_mtip_if_info_s.ready_cb_user_data);
    }
  }

  // Release Mutex
  mutex_unlock(&qcom_aw_phy_mtip_if_info_s.lock);

  return;
}

void qcom_aw_phy_mtip_if_init(void) {
  QCOM_AW_PHY_LOG_INFO("aw_phy_mtip_if_init !");

  memset(&qcom_aw_phy_mtip_if_info_s, 0,
         sizeof(struct qcom_aw_phy_mtip_if_info));

  mutex_init(&qcom_aw_phy_mtip_if_info_s.lock);

  return;
}

int qcom_aw_phy_mtip_register(
    struct eth_phy_iface_eth_register_params *ready_info, bool *is_phy_ready) {
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;
  int ret_val = 0;

  QCOM_AW_PHY_LOG_INFO("qcom_aw_phy_mtip_register !");

  if (!ready_info || !ready_info->notify_ready ||
      !ready_info->notify_an_complete || !is_phy_ready) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_0;
    goto func_exit;
  }

  mutex_lock(&qcom_aw_phy_mtip_if_info_s.lock);

  if (qcom_aw_phy_mtip_if_info_s.is_ready_notified) {
    ret_val = 0;
    local_err_val = LOCAL_ERROR_1;
    mutex_unlock(&qcom_aw_phy_mtip_if_info_s.lock);
    goto func_exit;
  }

  qcom_aw_phy_mtip_if_info_s.is_mac_drv_ready = true;

  *is_phy_ready = qcom_aw_phy_mtip_if_info_s.is_phy_drv_ready;

  /* If PHY is ready, notify in the reurn value.
     Register ready callback otherwise */
  if (*is_phy_ready) {
    qcom_aw_phy_mtip_if_info_s.is_ready_notified = true;
  } else {
    qcom_aw_phy_mtip_if_info_s.ready_cb = ready_info->notify_ready;
    qcom_aw_phy_mtip_if_info_s.ready_cb_user_data = ready_info->userdata_ready;
  }

  /* Register AN complete callback */
  qcom_aw_phy_mtip_if_info_s.an_complete_cb = ready_info->notify_an_complete;

  mutex_unlock(&qcom_aw_phy_mtip_if_info_s.lock);

func_exit:
  QCOM_AW_PHY_LOG_INFO("qcom_aw_eth_register returns %d, local error %d",
                       ret_val, local_err_val);

  return ret_val;
}

void qcom_aw_phy_mtip_deregister(void) { return; }

/*-------------------------------------------------------------------
* qcom_aw_phy_setup

* @port_type: Port Info(FH/C2C/Debug)
* @lane_config: Lanes for this MAC instance that are enabled and
   corresponding speed config.

* Description: This function fetches the lane configuration for the specified
   port read by MAC in its DT, and caches it at PHY driver.
------------------------------------------------------------------- */
int qcom_aw_phy_setup(
    enum mtip_port_type_enum port_type,
    struct eth_phy_iface_phy_lane_config lane_config[PHY_LANE_MAX]) {
  struct qcom_aw_phy_config *phy_config_info = NULL;
  enum qcom_aw_phy_instance_enum phy_inst_type = QCOM_AW_PHY_INST_MAX;
  struct qcom_aw_phy_inst_config *phy_inst_info = NULL;
  struct qcom_aw_lane_params *phy_lane_params = NULL;
  uint8_t i = 0;
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;
  int ret_val = 0;

  QCOM_AW_PHY_LOG_INFO("qcom_aw_phy_setup !");

  phy_inst_type = qcom_aw_phy_mac_port_to_phy_inst(port_type);
  if (phy_inst_type == QCOM_AW_PHY_INST_MAX) {
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

  phy_inst_info = &phy_config_info->phy_inst_config_info[phy_inst_type];
  if (phy_inst_info->valid == false) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_2;
    goto func_exit;
  }

  for (i = 0; i < PHY_LANE_MAX; i++) {
    if (lane_config[i].lane_enabled) {

      // Increment the number of lanes
      phy_inst_info->num_lanes++;

      // Set the lane as enabled and lane speed config.
      phy_lane_params = &phy_inst_info->lane_params[i];
      phy_lane_params->lane_config = lane_config[i];

      QCOM_AW_PHY_LOG_INFO("%s: Port %d has lane %d enabled with speed %d",
                           __func__, port_type, i, lane_config[i].lane_speed);
    }
  }

func_exit:
  QCOM_AW_PHY_LOG_ERR("%s: returns %d with local error %d", __func__, ret_val,
                      local_err_val);

  return ret_val;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_bringup_anlt_mode

* @mss: PHY address and offset
* @lane: PHY lane number
* @config: Phy lane config

* Description: This function brings up the lanes in ANLT mode
------------------------------------------------------------------- */
int qcom_aw_phy_bringup_anlt_mode(mss_access_t *mss,
                                  enum eth_phy_iface_phy_lane_num_enum lane,
                                  struct qcom_aw_phy_lane_speed_config config) {
  uint32_t lt_running;
  uint32_t lt_done;
  uint32_t lt_training_failure;
  uint32_t lt_rx_ready;
  uint32_t an_complete;
  uint32_t mod = 0;
  uint32_t adv_ability[19];
  uint32_t fec_ability[5];
  uint8_t cntr;
  int ret_val = 0;

  aw_pmd_rxeq_prbs_set(mss, 0);
  aw_pmd_anlt_link_training_en_set(mss, 1);
  aw_pmd_anlt_logical_lane_num_set(
      mss, lane, 0); // 3rd param set to 0 for multi lane, set to 1 for 1 lane

  aw_pmd_anlt_auto_neg_config_set(
      mss, 0, 1, 1); // 3rd param set to 1 for multi lane, set to 0 for 1 lane,
                     // 2nd param 0 for mission mode
  aw_pmd_anlt_link_training_prbs_seed_set(mss, config.clause, 0);

  if (config.mod_tech == QCOM_AW_PHY_MOD_TECH_PAM4)
    mod = 1;
  aw_pmd_anlt_link_training_config_set(mss, config.width, config.clause, mod);

  /* Pass in 1 to the appropriate technology in the below array
  Ex : For tech5 pass 19bit array [0,0,0,0,1,0...0] */
  for (cntr = 0; cntr < 19; cntr++) {
    if (cntr == 18) {
      adv_ability[cntr] = 1;
    } else {
      adv_ability[cntr] = 0;
    }
  }

  /*5bit FEC Array to advertize FEC abiliy*/
  for (cntr = 0; cntr < 5; cntr++) {
    fec_ability[cntr] = 1;
  }

  aw_pmd_anlt_auto_neg_adv_ability_set(mss, adv_ability, fec_ability,
                                       0); // Check 2nd and 3rd params
  aw_pmd_iso_tx_reset_set(mss, 1);
  aw_pmd_iso_rx_reset_set(mss, 1);
  aw_pmd_anlt_auto_neg_start_set(mss, 1);

  mdelay(1000);

  aw_pmd_anlt_auto_neg_status_complete_get(mss, &an_complete);

  if (an_complete == 0) {
    QCOM_AW_PHY_LOG_ERR("AN failed, need to debug!");
  } else {
    QCOM_AW_PHY_LOG_INFO("AN complete link is up");
  }

  mdelay(1000);

  aw_pmd_anlt_link_training_status_get(mss, &lt_running, &lt_done,
                                       &lt_training_failure, &lt_rx_ready);
  if (lt_training_failure == 1) {
    QCOM_AW_PHY_LOG_ERR("LT failed, need to debug!");
  }

  if (lt_done == 0) {
    QCOM_AW_PHY_LOG_ERR("LT did not finish, try increasing delay");
  } else {
    QCOM_AW_PHY_LOG_INFO("LT completed\n");
  }

  return ret_val;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_bringup_lt_mode

* @mss: PHY address and offset
* @lane: PHY lane number
* @config: Phy lane config

* Description: This function brings up the lanes in LT mode
------------------------------------------------------------------- */
int qcom_aw_phy_bringup_lt_mode(mss_access_t *mss,
                                enum eth_phy_iface_phy_lane_num_enum lane,
                                struct qcom_aw_phy_lane_speed_config config) {
  uint32_t lt_running;
  uint32_t lt_done;
  uint32_t lt_training_failure;
  uint32_t lt_rx_ready;
  uint32_t mod = 0;
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;
  aw_err_code_t aw_err_val = AW_ERR_CODE_NONE;
  int ret_val = 0;

  aw_pmd_rxeq_prbs_set(mss, 0);

  /* TX power up */
  aw_err_val = aw_pmd_iso_request_tx_state_change(
      mss, AW_P0, config.rate, config.width, TX_ACK_TIMEOUT_US);
  if (aw_err_val != AW_ERR_CODE_NONE) {
    ret_val = EIO;
    local_err_val = LOCAL_ERROR_0;
    goto func_exit;
  }

  /* RX power up */
  aw_err_val = aw_pmd_iso_request_rx_state_change(
      mss, AW_P0, config.rate, config.width, RX_ACK_TIMEOUT_US);
  if (aw_err_val != AW_ERR_CODE_NONE) {
    ret_val = EIO;
    local_err_val = LOCAL_ERROR_1;
    goto func_exit;
  }

  aw_pmd_gen_tx_en_set(mss, 0);
  aw_pmd_rx_chk_en_set(mss, 0);
  aw_pmd_anlt_link_training_en_set(mss, 1);
  aw_pmd_anlt_logical_lane_num_set(mss, lane, 1);

  aw_pmd_anlt_link_training_prbs_seed_set(mss, config.clause, 0);
  aw_pmd_link_training_without_an_config_set(mss, config.width, config.clause);

  if (config.mod_tech == QCOM_AW_PHY_MOD_TECH_PAM4)
    mod = 1;

  aw_pmd_anlt_link_training_config_set(mss, config.width, config.clause, mod);
  aw_pmd_anlt_link_training_start_set(mss, 1);

  mdelay(1000); // an_good_link_training_eval_timeout_us

  aw_pmd_anlt_link_training_status_get(mss, &lt_running, &lt_done,
                                       &lt_training_failure, &lt_rx_ready);
  if (lt_training_failure == 1) {
    QCOM_AW_PHY_LOG_ERR("Failure, need to debug\n");
  }

  if (lt_done == 0) {
    QCOM_AW_PHY_LOG_ERR("LT did not finish, try increasing iterations");
  } else {
    QCOM_AW_PHY_LOG_INFO("LT successful\n");
  }

func_exit:
  QCOM_AW_PHY_LOG_ERR("%s: returns %d with local error %d and aw_error %d",
                      __func__, ret_val, local_err_val, aw_err_val);

  return ret_val;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_bringup_manual_eq_mode

* @mss: PHY address and offset
* @lane: PHY lane number
* @config: Phy lane config

* Description: This function brings up the lanes in LT mode
------------------------------------------------------------------- */
int qcom_aw_phy_bringup_manual_eq_mode(
    mss_access_t *mss, enum eth_phy_iface_phy_lane_num_enum lane,
    struct qcom_aw_phy_lane_speed_config config) {
  aw_txfir_config_t txfir_cfg;
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;
  aw_err_code_t aw_err_val = AW_ERR_CODE_NONE;
  int ret_val = 0;

  //aw_pmd_rxeq_prbs_set(mss, 0);

  /* TX power up */
  aw_err_val = aw_pmd_iso_request_tx_state_change(
      mss, AW_P0, config.rate, config.width, TX_ACK_TIMEOUT_US);
  if (aw_err_val != AW_ERR_CODE_NONE) {
    ret_val = EIO;
    local_err_val = LOCAL_ERROR_0;
    goto func_exit;
  }

  /* RX power up */
  aw_err_val = aw_pmd_iso_request_rx_state_change(
      mss, AW_P0, config.rate, config.width, RX_ACK_TIMEOUT_US);
  if (aw_err_val != AW_ERR_CODE_NONE) {
    ret_val = EIO;
    local_err_val = LOCAL_ERROR_1;
    goto func_exit;
  }

  /* Configuration for Near End Parallel Loopback mode */
  if (qcom_aw_phy_get_loopback_mode() == QCOM_AW_PHY_NEAR_END_PARALLEL_LB) {
    QCOM_AW_PHY_LOG_INFO("Configuring PHY for near end parallel LB");
    aw_pmd_nep_loopback_set(mss, 1);
    return ret_val;
  }

  // TX FIR Config
  txfir_cfg.CM2 = 0;
  txfir_cfg.C0 = 60;
  txfir_cfg.C1 = 0;
  txfir_cfg.main_or_max = 1;
  aw_pmd_txfir_config_set(mss, &txfir_cfg);

  /* Disabling DFE Adaptations EXT loopback */
  aw_pmd_rx_dfe_adapt_set(mss, 0);

  /* Configuration for Near End Serial Loopback mode */
  if (qcom_aw_phy_get_loopback_mode() == QCOM_AW_PHY_NEAR_END_SERIAL_LB) {
    QCOM_AW_PHY_LOG_INFO("Configuring PHY for near end serial LB");
    aw_pmd_analog_loopback_set(mss, 1);
  }

  mdelay(5000);

  // RX Equalization - Check aw_eq_type_e enum
  aw_pmd_rx_equalize(mss, AW_EQ_FULL_DIR, RX_LINKEVAL_FULL_TIMEOUT_US);

func_exit:
  QCOM_AW_PHY_LOG_ERR("%s: returns %d with local error %d and aw_error %d",
                      __func__, ret_val, local_err_val, aw_err_val);

  return ret_val;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_bringup

* @port_type: Port Info(FH/C2C/Debug)
* @lanes_enabled: Lanes for this MAC instance that need to be brought up
* @pl: Phylink pointer

* Description: This function brings up the lanes corresponding to a MAC instance
   for the specified port
------------------------------------------------------------------- */
int qcom_aw_phy_bringup(enum mtip_port_type_enum port_type,
                        bool lanes_enabled[PHY_LANE_MAX], int sfp_port_type) {
  struct qcom_aw_phy_config *phy_config_info = NULL;
  enum qcom_aw_phy_instance_enum phy_inst_type = QCOM_AW_PHY_INST_MAX;
  struct qcom_aw_phy_inst_config *phy_inst_info = NULL;
  struct qcom_aw_lane_params *phy_lane_params = NULL;
  enum eth_phy_iface_phy_lane_num_enum lane = PHY_LANE_0;
  mss_access_t mss = {.phy_offset = 0, .lane_offset = 0};
  struct qcom_aw_phy_lane_speed_config config;
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;
  aw_err_code_t aw_err_val = AW_ERR_CODE_NONE;
  int ret_val = 0;

  /* Get the PHY instance type for the provided port */
  phy_inst_type = qcom_aw_phy_mac_port_to_phy_inst(port_type);
  if (phy_inst_type == QCOM_AW_PHY_INST_MAX) {
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

  /* Get the PHY instance info for the passed instance type */
  phy_inst_info = &phy_config_info->phy_inst_config_info[phy_inst_type];
  if (phy_inst_info->valid == false) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_2;
    goto func_exit;
  }

  QCOM_AW_PHY_LOG_INFO("%s: MAC Port %d has sfp port %d", __func__, port_type,
                       sfp_port_type);
  phy_inst_info->sfp_port_type = sfp_port_type;

  /* Get the lane specific info for the provided lane */
  if (QCOM_AW_PHY_LANE_VALID(lane)) {
    phy_lane_params = &phy_inst_info->lane_params[lane];
    if (phy_lane_params->lane_config.lane_enabled == false) {
      ret_val = EINVAL;
      local_err_val = LOCAL_ERROR_3;
      goto func_exit;
    }
  } else {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_4;
    goto func_exit;
  }

  /* Setup PHY offset */
  mss.phy_offset = phy_inst_info->base_addr;

  /* Common isolation - Not required if PHY input pins are used for
     REF clock propagation - From HPG */
  aw_err_val = aw_pmd_isolate_cmn_set(&mss, 1);
  if (aw_err_val != AW_ERR_CODE_NONE) {
    ret_val = EIO;
    local_err_val = LOCAL_ERROR_5;
    goto func_exit;
  }

  /* Common Lane Bring up */
  aw_err_val =
      aw_pmd_iso_request_cmn_state_change(&mss, AW_CMN_P0, CMN_ACK_TIMEOUT_US);
  if (aw_err_val != AW_ERR_CODE_NONE) {
    ret_val = EIO;
    local_err_val = LOCAL_ERROR_6;
    goto func_exit;
  }

  for (lane = PHY_LANE_0; lane < PHY_LANE_MAX; lane++) {
    /* Check if lane is valid for this MAC instance */
    if (lanes_enabled[lane] == false)
      continue;

    QCOM_AW_PHY_LOG_INFO("%s: Bringing up lane %d on port %d!", __func__, lane,
                         port_type);

    /* Set the lane offset */
    pmd_set_lane(&mss, lane);

    if(qcom_aw_phy_get_polarity_flag()){
      aw_pmd_tx_polarity_set(&mss, 1);
      aw_pmd_rx_polarity_set(&mss, 1);
    }

    /* Lane Isolation */
    aw_err_val = aw_pmd_isolate_lane_set(&mss, 1);
    if (aw_err_val != AW_ERR_CODE_NONE) {
      ret_val = EIO;
      local_err_val = LOCAL_ERROR_7;
      goto func_exit;
    }

    aw_pmd_gen_tx_en_set(&mss, 0);

    /* Get lane rate and width based on the speed. */
    qcom_aw_phy_get_lane_speed_config(phy_lane_params->lane_config.lane_speed,
                                      &config);

    if (phy_inst_info->phy_eq_mode == QCOM_AW_PHY_ANLT_MODE) {
      qcom_aw_phy_bringup_anlt_mode(&mss, lane, config);
    } else if (phy_inst_info->phy_eq_mode == QCOM_AW_PHY_LT_MODE) {
      qcom_aw_phy_bringup_lt_mode(&mss, lane, config);
    } else if (phy_inst_info->phy_eq_mode == QCOM_AW_PHY_MANUAL_EQ_MODE) {
      qcom_aw_phy_bringup_manual_eq_mode(&mss, lane, config);
    }

    // TX BIST

    // Check CDR Lock
    aw_pmd_rx_check_cdr_lock(&mss, RX_CDR_TIMEOUT_US);

    // RX BIST
  }

func_exit:
  QCOM_AW_PHY_LOG_ERR("%s: returns %d with local error %d and aw_error %d",
                      __func__, ret_val, local_err_val, aw_err_val);

  return ret_val;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_teardown

* @port_type: Port Info(FH/C2C/Debug)
* @lanes_enabled: Lanes for this MAC instance that need to be brought down
* @pl: Phylink pointer

* Description: This function brings down the lanes corresponding to a MAC
instance for the specified port
------------------------------------------------------------------- */
int qcom_aw_phy_teardown(enum mtip_port_type_enum port_type,
                         bool lanes_enabled[PHY_LANE_MAX]) {
  struct qcom_aw_phy_config *phy_config_info = NULL;
  enum qcom_aw_phy_instance_enum phy_inst_type = QCOM_AW_PHY_INST_MAX;
  struct qcom_aw_phy_inst_config *phy_inst_info = NULL;
  struct qcom_aw_lane_params *phy_lane_params = NULL;
  enum eth_phy_iface_phy_lane_num_enum lane = PHY_LANE_0;
  mss_access_t mss = {.phy_offset = 0, .lane_offset = 0};
  struct qcom_aw_phy_lane_speed_config config;
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;
  aw_err_code_t aw_err_val = AW_ERR_CODE_NONE;
  int ret_val = 0;

  /* Get the PHY instance type for the provided port */
  phy_inst_type = qcom_aw_phy_mac_port_to_phy_inst(port_type);
  if (phy_inst_type == QCOM_AW_PHY_INST_MAX) {
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

  /* Get the PHY instance info for the passed instance type */
  phy_inst_info = &phy_config_info->phy_inst_config_info[phy_inst_type];
  if (phy_inst_info->valid == false) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_2;
    goto func_exit;
  }

  /* Get the lane specific info for the provided lane */
  if (QCOM_AW_PHY_LANE_VALID(lane)) {
    phy_lane_params = &phy_inst_info->lane_params[lane];
    if (phy_lane_params->lane_config.lane_enabled == false) {
      ret_val = EINVAL;
      local_err_val = LOCAL_ERROR_3;
      goto func_exit;
    }
  } else {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_4;
    goto func_exit;
  }

  /* Setup PHY offset */
  mss.phy_offset = phy_inst_info->base_addr;

  for (lane = PHY_LANE_0; lane < PHY_LANE_MAX; lane++) {
    /* Check if lane is valid for this MAC instance */
    if (lanes_enabled[lane] == false)
      continue;

    QCOM_AW_PHY_LOG_INFO("%s: Tearing down lane %d on port %d!", __func__, lane,
                         port_type);

    /* Set the lane offset */
    pmd_set_lane(&mss, lane);

    /* Get lane rate and width based on the speed. */
    qcom_aw_phy_get_lane_speed_config(phy_lane_params->lane_config.lane_speed,
                                      &config);

    /* TX power down */
    aw_err_val = aw_pmd_iso_request_tx_state_change(
        &mss, AW_PD, config.rate, config.width, TX_ACK_TIMEOUT_US);
    if (aw_err_val != AW_ERR_CODE_NONE) {
      ret_val = EIO;
      local_err_val = LOCAL_ERROR_5;
      goto func_exit;
    }

    /* RX power down */
    aw_err_val = aw_pmd_iso_request_rx_state_change(
        &mss, AW_PD, config.rate, config.width, TX_ACK_TIMEOUT_US);
    if (aw_err_val != AW_ERR_CODE_NONE) {
      ret_val = EIO;
      local_err_val = LOCAL_ERROR_6;
      goto func_exit;
    }
  }

func_exit:
  QCOM_AW_PHY_LOG_ERR("%s: returns %d with local error %d and aw_error %d",
                      __func__, ret_val, local_err_val, aw_err_val);

  return ret_val;
}

int qcom_aw_phy_mac_link_status(enum mtip_port_type_enum port_type,
                                bool lanes_enabled[PHY_LANE_MAX], bool status) {
  struct qcom_aw_phy_config *phy_config_info = NULL;
  enum qcom_aw_phy_instance_enum phy_inst_type = QCOM_AW_PHY_INST_MAX;
  struct qcom_aw_phy_inst_config *phy_inst_info = NULL;
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;
  int ret_val = 0;

  /* Get the PHY instance type for the provided port */
  phy_inst_type = qcom_aw_phy_mac_port_to_phy_inst(port_type);
  if (phy_inst_type == QCOM_AW_PHY_INST_MAX) {
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

  /* Get the PHY instance info for the passed instance type */
  phy_inst_info = &phy_config_info->phy_inst_config_info[phy_inst_type];
  if (phy_inst_info->valid == false) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_2;
    goto func_exit;
  }

  phy_inst_info->link_status = status;

  qcom_aw_phy_synce_notify_phy_lane_state_change();

func_exit:
  QCOM_AW_PHY_LOG_ERR("%s: returns %d with local error %d", __func__, ret_val,
                      local_err_val);

  return ret_val;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_notify_an_complete

* @phy_inst: PHY instance type(FH/C2C/Debug)
  * @lane_num: Lane number

* Description: This function notifies AN complete to MAC.
------------------------------------------------------------------- */
void qcom_aw_phy_notify_an_complete(
    enum qcom_aw_phy_instance_enum phy_inst,
    enum eth_phy_iface_phy_lane_num_enum lane_num) {
  enum mtip_port_type_enum mac_port_type;

  if (!QCOM_AW_PHY_INST_VALID(phy_inst) || !QCOM_AW_PHY_LANE_VALID(lane_num))
    QCOM_AW_PHY_LOG_ERR("Invalid PHY instance/lane. AN Notification failed.");

  mac_port_type = qcom_aw_phy_inst_to_mac_port(phy_inst);

  qcom_aw_phy_mtip_if_info_s.an_complete_cb(mac_port_type, lane_num);
}

/* API exposed structure */
const struct eth_phy_iface_ops qcom_aw_phy_driver_iface_ops = {
    .eth_phy_iface_eth_register = qcom_aw_phy_mtip_register,
    .eth_phy_iface_eth_deregister = qcom_aw_phy_mtip_deregister,
    .eth_phy_iface_phy_setup = qcom_aw_phy_setup,
    .eth_phy_iface_phy_bringup = qcom_aw_phy_bringup,
    .eth_phy_iface_phy_teardown = qcom_aw_phy_teardown,
    .eth_phy_iface_notify_mac_link_status = qcom_aw_phy_mac_link_status,
};

EXPORT_SYMBOL(qcom_aw_phy_driver_iface_ops);
