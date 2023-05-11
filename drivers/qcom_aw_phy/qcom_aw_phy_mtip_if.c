/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
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

  /* Register CDR lock success callback */
  qcom_aw_phy_mtip_if_info_s.cdr_lock_ind = ready_info->cdr_lock_ind;

  qcom_aw_phy_mtip_if_info_s.lane_bring_up_progress_ind =
                                         ready_info->lane_bring_up_progress_ind;

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

  mutex_lock(&phy_inst_info->phy_inst_lock);

  if (phy_inst_info->valid == false) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_2;
    goto func_exit;
  }

  /* Ignore the call if PHY has been already brought up */
  if (phy_inst_info->bring_up_status == true) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_3;
    goto func_exit;
  }

  // Reset the number of lanes to 0
  phy_inst_info->num_lanes = 0;

  for (i = 0; i < PHY_LANE_MAX; i++) {

    mutex_lock(&phy_inst_info->lane_lock[i]);

    phy_lane_params = &phy_inst_info->lane_params[i];

    if (lane_config[i].lane_enabled) {

      // Increment the number of lanes
      phy_inst_info->num_lanes++;

      // Set the lane as enabled and lane speed config.
      phy_lane_params->lane_config = lane_config[i];

      phy_inst_info->cdr_lock_status_flag[i] = CDR_LOCK_NONE;

      QCOM_AW_PHY_LOG_INFO("Port %d has lane %d enabled with speed %d",
                           port_type, i, lane_config[i].lane_speed);
    }
    else{
      /* Clear the old lane configuration */
      memset(&phy_lane_params->lane_config, 0,
             sizeof(struct eth_phy_iface_phy_lane_config));
    }

    mutex_unlock(&phy_inst_info->lane_lock[i]);

  }

func_exit:
  if(local_err_val != LOCAL_ERROR_INVALID){
    QCOM_AW_PHY_LOG_ERR("%s: returns %d with local error %d", __func__, ret_val,
                        local_err_val);
  }

  mutex_unlock(&phy_inst_info->phy_inst_lock);

  return ret_val;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_handle_cdr_lock_status

* @phy_inst_info: PHY instance info pointer
* @lane: PHY lane number

* Description: This function check CDR locks status for multiple
  PHY lanes mapped to the ethernet interface, and initiates calback
  with appropriate status.
------------------------------------------------------------------- */
void qcom_aw_phy_handle_cdr_lock_status(
    struct qcom_aw_phy_inst_config *phy_inst_info,
    enum eth_phy_iface_phy_lane_num_enum lane,
    enum qcom_aw_phy_cdr_lock_lane_status lane_level_status) {

  u32 eth_link_index;
  bool eth_level_status = false;
  u32 i;

  QCOM_AW_PHY_LOG_INFO("CDR lock status %d for PHY %d, lane %d",
                       lane_level_status, phy_inst_info->phy_inst, lane);

  phy_inst_info->cdr_lock_status_flag[lane] = lane_level_status;
  eth_link_index = phy_inst_info->lane_params[lane].lane_config.link_index;

  for(i=PHY_LANE_0; i<PHY_LANE_MAX; i++){

    if(phy_inst_info->lane_params[i].lane_config.lane_enabled == false){
      continue;
    }

    /* Skip processing for PHY lane mapped to a different ETH link */
    if(eth_link_index != phy_inst_info->lane_params[i].lane_config.link_index){
      continue;
    }

    /* Don't initiate callback if CDR is not yet locked for either of the lanes*/
    if(phy_inst_info->cdr_lock_status_flag[i] == CDR_LOCK_NONE){
      return;
    }
    /* Initiate failure callback if CDR lock failed for any of the lanes*/
    else if(phy_inst_info->cdr_lock_status_flag[i] == CDR_LOCK_FAILURE){
      eth_level_status = false;
      break;
    }
    /* Initiate success callback if CDR is locked for all the lanes*/
    else
      eth_level_status = true;

  }

  qcom_aw_phy_mtip_if_info_s.cdr_lock_ind(eth_link_index, eth_level_status);

  if(eth_level_status == true){
    /* Notify MAC to start listening to PCS link interrupts */
    qcom_aw_phy_notify_lane_bring_up_progress_to_mac(phy_inst_info, lane, false);

    /* Start listening to SNR valid/error interrupts */
    for(i=PHY_LANE_0; i<PHY_LANE_MAX; i++){
      if(phy_inst_info->lane_params[i].lane_config.lane_enabled == true &&
        eth_link_index == phy_inst_info->lane_params[i].lane_config.link_index){
        qcom_aw_phy_enable_snr_interrupt(phy_inst_info, i);
      }
    }
  }

  return;
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
* @phy_inst_info: PHY instance info pointer
* @lane: PHY lane number
* @config: Phy lane config

* Description: This function brings up the lanes in LT mode
------------------------------------------------------------------- */
int qcom_aw_phy_bringup_lt_mode(mss_access_t *mss,
                                struct qcom_aw_phy_inst_config *phy_inst_info,
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

  aw_pmd_anlt_ms_per_ck_set(mss, 99999);
  aw_pmd_rx_background_adapt_enable_set(mss, 1);

  if ((config.rate == 2) || (config.rate == 3)) {
    aw_pmd_enable_pam4_mode(mss, 1);
  }

  aw_pmd_anlt_link_training_timeout_enable_set(mss, 0);
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

  mdelay(3000); // an_good_link_training_eval_timeout_us

  aw_pmd_anlt_link_training_status_get(mss, &lt_running, &lt_done,
                                       &lt_training_failure, &lt_rx_ready);
  if (lt_training_failure == 1) {
    QCOM_AW_PHY_LOG_ERR("LT failed, need to debug");
  }

  if (lt_done == 0) {
    QCOM_AW_PHY_LOG_ERR("LT did not finish, try increasing iterations");
  }
  else {
    QCOM_AW_PHY_LOG_INFO("LT successful");
    mdelay(500);
    if(AW_ERR_CODE_NONE == aw_pmd_rx_check_cdr_lock(mss, RX_CDR_TIMEOUT_US)){
      qcom_aw_phy_handle_cdr_lock_status(phy_inst_info, lane, CDR_LOCK_SUCCESS);
    }
    else{
      qcom_aw_phy_handle_cdr_lock_status(phy_inst_info, lane, CDR_LOCK_FAILURE);
    }
  }

func_exit:
  if(local_err_val != LOCAL_ERROR_INVALID){
    QCOM_AW_PHY_LOG_ERR("%s: returns %d with local error %d and aw_error %d",
                        __func__, ret_val, local_err_val, aw_err_val);
  }

  return ret_val;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_bringup_manual_eq_mode

* @mss: PHY address and offset
* @phy_inst_info: PHY instance info pointer
* @lane: PHY lane number
* @config: Phy lane config

* Description: This function brings up the lanes in LT mode
------------------------------------------------------------------- */
int qcom_aw_phy_bringup_manual_eq_mode(
    mss_access_t *mss, 
    struct qcom_aw_phy_inst_config *phy_inst_info,
    enum eth_phy_iface_phy_lane_num_enum lane,
    struct qcom_aw_phy_lane_speed_config config) {
  aw_txfir_config_t txfir_cfg = {0};
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

  aw_pmd_anlt_ms_per_ck_set(mss, 99999);

  if ((config.rate == 2) || (config.rate == 3)) {
    aw_pmd_enable_pam4_mode(mss, 1);
  }

  /* Configuration for Near End Parallel Loopback mode */
  if (qcom_aw_phy_get_loopback_mode() == QCOM_AW_PHY_NEAR_END_PARALLEL_LB) {
    QCOM_AW_PHY_LOG_INFO("Configuring PHY for near end parallel LB");
    aw_pmd_nep_loopback_set(mss, 1);
    return ret_val;
  }

  // TX FIR Config
  txfir_cfg.CM3 = 0;
  txfir_cfg.CM2 = 0;
  txfir_cfg.CM1 = 0;
  txfir_cfg.C0 = 60;
  txfir_cfg.C1 = 0;
  txfir_cfg.main_or_max = 1;
  aw_pmd_txfir_config_set(mss, &txfir_cfg, 1);

  aw_pmd_rx_background_adapt_enable_set(mss, 1);

  /* Configuration for Near End Serial Loopback mode */
  if (qcom_aw_phy_get_loopback_mode() == QCOM_AW_PHY_NEAR_END_SERIAL_LB) {
    QCOM_AW_PHY_LOG_INFO("Configuring PHY for near end serial LB");
    aw_pmd_analog_loopback_set(mss, 1);
  }

  /* Delay before triggering RX equalization */
  mdelay(500);

  // RX Equalization - Check aw_eq_type_e enum
  aw_pmd_rx_equalize(mss, AW_EQ_FULL_DIR, RX_LINKEVAL_FULL_TIMEOUT_US);

  /* Delay before checking RX CDR lock post equalization */
  mdelay(500);

  // Check CDR Lock
  if(AW_ERR_CODE_NONE == aw_pmd_rx_check_cdr_lock(mss, RX_CDR_TIMEOUT_US)){
    qcom_aw_phy_handle_cdr_lock_status(phy_inst_info, lane, CDR_LOCK_SUCCESS);
  }
  else{
    qcom_aw_phy_handle_cdr_lock_status(phy_inst_info, lane, CDR_LOCK_FAILURE);
  }

func_exit:
  if(local_err_val != LOCAL_ERROR_INVALID){
    QCOM_AW_PHY_LOG_ERR("%s: returns %d with local error %d and aw_error %d",
                        __func__, ret_val, local_err_val, aw_err_val);
  }

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

  mutex_lock(&phy_inst_info->phy_inst_lock);

  QCOM_AW_PHY_LOG_INFO("MAC Port %d has sfp port %d", port_type, sfp_port_type);
  phy_inst_info->sfp_port_type = sfp_port_type;
  phy_inst_info->bring_up_status = true;

  /* Setup PHY offset */
  mss.phy_offset = phy_inst_info->base_addr;

  /* Common isolation - Not required if PHY input pins are used for
     REF clock propagation - From HPG */
  aw_err_val = aw_pmd_isolate_cmn_set(&mss, 1);
  if (aw_err_val != AW_ERR_CODE_NONE) {
    ret_val = EIO;
    local_err_val = LOCAL_ERROR_3;
    mutex_unlock(&phy_inst_info->phy_inst_lock);
    goto func_exit;
  }

  /* Common Lane Bring up */
  aw_err_val =
      aw_pmd_iso_request_cmn_state_change(&mss, AW_CMN_P0, CMN_ACK_TIMEOUT_US);
  if (aw_err_val != AW_ERR_CODE_NONE) {
    ret_val = EIO;
    local_err_val = LOCAL_ERROR_4;
    mutex_unlock(&phy_inst_info->phy_inst_lock);
    goto func_exit;
  }

  for (lane = PHY_LANE_0; lane < PHY_LANE_MAX; lane++) {
    /* Check if lane is valid for this MAC instance */
    if (lanes_enabled[lane] == false)
      continue;

  /* Get the lane specific info for the provided lane */
    phy_lane_params = &phy_inst_info->lane_params[lane];
    if (phy_lane_params->lane_config.lane_enabled == false) {
      ret_val = EINVAL;
      local_err_val = LOCAL_ERROR_5;
      mutex_unlock(&phy_inst_info->phy_inst_lock);
      goto func_exit;
    }

    QCOM_AW_PHY_LOG_INFO("Bringing up lane %d on port %d!", lane, port_type);

    mutex_lock(&phy_inst_info->lane_lock[lane]);

    /* Notify MAC to stop listening to PCS link interrupts */
    qcom_aw_phy_notify_lane_bring_up_progress_to_mac(phy_inst_info, lane, true);

    /* Stop listening to SNR valid/error interrupts */
    qcom_aw_phy_disable_snr_interrupt(phy_inst_info, lane);

    /* Set the lane offset */
    pmd_set_lane(&mss, lane);

    if(qcom_aw_phy_get_polarity_flag()){
      QCOM_AW_PHY_LOG_INFO("Setting TX/RX polarity !");
      aw_pmd_tx_polarity_set(&mss, 1);
      aw_pmd_rx_polarity_set(&mss, 1);
    }

    /* Lane Isolation */
    aw_err_val = aw_pmd_isolate_lane_set(&mss, 1);
    if (aw_err_val != AW_ERR_CODE_NONE) {
      ret_val = EIO;
      local_err_val = LOCAL_ERROR_7;
      mutex_unlock(&phy_inst_info->lane_lock[lane]);
      mutex_unlock(&phy_inst_info->phy_inst_lock);
      goto func_exit;
    }

    aw_pmd_gen_tx_en_set(&mss, 0);

    /* Get lane rate and width based on the speed. */
    qcom_aw_phy_get_lane_speed_config(phy_lane_params->lane_config.lane_speed,
                                      &config);

    if (phy_inst_info->phy_eq_mode == QCOM_AW_PHY_ANLT_MODE) {
      qcom_aw_phy_bringup_anlt_mode(&mss, lane, config);
    } else if (phy_inst_info->phy_eq_mode == QCOM_AW_PHY_LT_MODE) {
      qcom_aw_phy_bringup_lt_mode(&mss, phy_inst_info, lane, config);
    } else if (phy_inst_info->phy_eq_mode == QCOM_AW_PHY_MANUAL_EQ_MODE) {
      qcom_aw_phy_bringup_manual_eq_mode(&mss, phy_inst_info, lane, config);
    }

    mutex_unlock(&phy_inst_info->lane_lock[lane]);
  }

  mutex_unlock(&phy_inst_info->phy_inst_lock);

func_exit:
  if(local_err_val != LOCAL_ERROR_INVALID){
    QCOM_AW_PHY_LOG_ERR("%s: returns %d with local error %d and aw_error %d",
                        __func__, ret_val, local_err_val, aw_err_val);
  }

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
  int poll_result;
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

  mutex_lock(&phy_inst_info->phy_inst_lock);

  /* Setup PHY offset */
  mss.phy_offset = phy_inst_info->base_addr;

  for (lane = PHY_LANE_0; lane < PHY_LANE_MAX; lane++) {
    /* Check if lane is valid for this MAC instance */
    if (lanes_enabled[lane] == false)
      continue;

 /* Get the lane specific info for the provided lane */
    phy_lane_params = &phy_inst_info->lane_params[lane];
    if (phy_lane_params->lane_config.lane_enabled == false) {
      ret_val = EINVAL;
      local_err_val = LOCAL_ERROR_3;
      mutex_unlock(&phy_inst_info->phy_inst_lock);
      goto func_exit;
    }

    QCOM_AW_PHY_LOG_INFO("Tearing down lane %d on port %d!", lane, port_type);

    mutex_lock(&phy_inst_info->lane_lock[lane]);

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
      local_err_val = LOCAL_ERROR_4;
      mutex_unlock(&phy_inst_info->lane_lock[lane]);
      mutex_unlock(&phy_inst_info->phy_inst_lock);
      goto func_exit;
    }

    /* RX power down */
    aw_err_val = aw_pmd_iso_request_rx_state_change(
        &mss, AW_PD, config.rate, config.width, RX_ACK_TIMEOUT_US);
    if (aw_err_val != AW_ERR_CODE_NONE) {
      ret_val = EIO;
      local_err_val = LOCAL_ERROR_5;
      mutex_unlock(&phy_inst_info->lane_lock[lane]);
      mutex_unlock(&phy_inst_info->phy_inst_lock);
      goto func_exit;
    }

    /* Check for CDR lock de-assertion */
    poll_result = pmd_poll_field(&mss, DIG_SOC_LANE_STAT_REG1_ADDR,
                                 DIG_SOC_LANE_STAT_REG1_OCTL_RX_DATA_VLD_MASK,
                                 DIG_SOC_LANE_STAT_REG1_OCTL_RX_DATA_VLD_OFFSET,
                                 0, RX_CDR_TIMEOUT_US);
    if (poll_result == -1) {
      QCOM_AW_PHY_LOG_ERR("ERROR: RX CDR timed out waiting to deassert");
    } else {
      QCOM_AW_PHY_LOG_DBG("RX CDR deasserted\n");
    }

    phy_inst_info->cdr_lock_status_flag[lane] = CDR_LOCK_NONE;

    mutex_unlock(&phy_inst_info->lane_lock[lane]);
  }

  phy_inst_info->bring_up_status = false;

  mutex_unlock(&phy_inst_info->phy_inst_lock);

func_exit:
  if(local_err_val != LOCAL_ERROR_INVALID){
    QCOM_AW_PHY_LOG_ERR("%s: returns %d with local error %d and aw_error %d",
                        __func__, ret_val, local_err_val, aw_err_val);
  }

  return ret_val;
}

int qcom_aw_phy_mac_link_status(enum mtip_port_type_enum port_type,
                                bool lanes_enabled[PHY_LANE_MAX], bool status) {
  struct qcom_aw_phy_config *phy_config_info = NULL;
  enum qcom_aw_phy_instance_enum phy_inst_type = QCOM_AW_PHY_INST_MAX;
  struct qcom_aw_phy_inst_config *phy_inst_info = NULL;
  enum eth_phy_iface_phy_lane_num_enum lane_num;
  bool notify_flag = false;
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

  mutex_lock(&phy_inst_info->phy_inst_lock);

  for (lane_num = PHY_LANE_0; lane_num < PHY_LANE_MAX; lane_num++) {
    if(lanes_enabled[lane_num]){

      mutex_lock(&phy_inst_info->lane_lock[lane_num]);
      if(phy_inst_info->lane_params[lane_num].link_status != status){
        phy_inst_info->lane_params[lane_num].link_status = status;
        QCOM_AW_PHY_LOG_ERR("PHY instance %d, lane %d, status %d, ",
                            phy_inst_type, lane_num, status);
        notify_flag = true;
      }
      mutex_unlock(&phy_inst_info->lane_lock[lane_num]);
    }
  }

  mutex_unlock(&phy_inst_info->phy_inst_lock);

  if(notify_flag)
    qcom_aw_phy_synce_notify_phy_lane_state_change();

func_exit:
  if(local_err_val != LOCAL_ERROR_INVALID){
    QCOM_AW_PHY_LOG_ERR("%s: PHY instance %d, status %d, "
                        "returns %d with local error %d",
                        __func__, phy_inst_type, status,
                        ret_val, local_err_val);
  }

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

void qcom_aw_phy_handle_an_complete(struct work_struct *work){
  struct delayed_work *delayed_work_item = to_delayed_work(work);
  struct qcom_aw_phy_work_q_params *wq_params =
     container_of(delayed_work_item, struct qcom_aw_phy_work_q_params, wq_item);

  if(!wq_params){
    QCOM_AW_PHY_LOG_ERR("Invalid work queue structure!");
    return;
  }

  QCOM_AW_PHY_LOG_ERR("AN done rcvd for PHY %d lane %d",
                      wq_params->phy_inst, wq_params->lane_num);

  qcom_aw_phy_notify_an_complete(wq_params->phy_inst, wq_params->lane_num);

  kfree(wq_params);
  return;
}

void qcom_aw_phy_handle_rx_sig_detect(struct work_struct *work){
  struct delayed_work *delayed_work_item = to_delayed_work(work);
  struct qcom_aw_phy_work_q_params *wq_params =
     container_of(delayed_work_item, struct qcom_aw_phy_work_q_params, wq_item);
  struct qcom_aw_phy_config *phy_config_info = NULL;
  struct qcom_aw_phy_inst_config *phy_inst_info = NULL;
  enum eth_phy_iface_phy_lane_num_enum lane = PHY_LANE_0;
  mss_access_t mss = {.phy_offset = 0, .lane_offset = 0};
  aw_txfir_config_t txfir_cfg = {0};
  int cdr_lock_status = 0;
  struct qcom_aw_phy_lane_speed_config config;
  aw_err_code_t aw_err_val = AW_ERR_CODE_NONE;
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;
  int ret_val = 0;

  /* Ignore for loopback mode */
  if (qcom_aw_phy_get_loopback_mode() != QCOM_AW_PHY_NO_LB){
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_0;
    goto func_exit;
  }

  if(!wq_params){
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_1;
    goto func_exit;
  }

  phy_config_info = qcom_aw_phy_get_config_info();
  if (!phy_config_info) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_2;
    goto func_exit;
  }

  /* Get the PHY instance info for the passed instance type */
  phy_inst_info = &phy_config_info->phy_inst_config_info[wq_params->phy_inst];
  if (phy_inst_info->valid == false) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_3;
    goto func_exit;
  }

  mutex_lock(&phy_inst_info->phy_inst_lock);

  if(phy_inst_info->bring_up_status == false) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_4;
    mutex_unlock(&phy_inst_info->phy_inst_lock);
    goto func_exit;
  }

  lane = wq_params->lane_num;

  mutex_lock(&phy_inst_info->lane_lock[lane]);

  /* Setup PHY offset */
  mss.phy_offset = phy_inst_info->base_addr;
  /* Set the lane offset */
  pmd_set_lane(&mss, lane);

  /* Reset the CDR lock status flag if error interrupt is received */
  if(false == (bool)wq_params->user_data){
    QCOM_AW_PHY_LOG_ERR("RX signal detect error received for PHY %d lane %d",
                        phy_inst_info->phy_inst, lane);
    phy_inst_info->cdr_lock_status_flag[lane] = CDR_LOCK_NONE;
  }
  /* Retry lane bring up if detect interrupt is received and PCS link is down */
  else if((phy_inst_info->lane_params[lane].link_status == false) &&
          (phy_inst_info->cdr_lock_status_flag[lane] != CDR_LOCK_SUCCESS)){

    QCOM_AW_PHY_LOG_INFO("Retry for PHY %d, lane %d",
                         wq_params->phy_inst, wq_params->lane_num);

    /* Get lane rate and width based on the speed. */
    qcom_aw_phy_get_lane_speed_config(
                        phy_inst_info->lane_params[lane].lane_config.lane_speed,
                        &config);

    // Notify MAC to stop listening to link status interrupts
    qcom_aw_phy_notify_lane_bring_up_progress_to_mac(phy_inst_info, lane, true);

    /* Stop listening to SNR valid/error interrupts */
    qcom_aw_phy_disable_snr_interrupt(phy_inst_info, lane);

    if (phy_inst_info->phy_eq_mode == QCOM_AW_PHY_ANLT_MODE) {
      //TODO
    }
    else if (phy_inst_info->phy_eq_mode == QCOM_AW_PHY_LT_MODE) {
      pmd_write_field(&mss, ETH_LT_CTRL_ADDR,
                      ETH_LT_CTRL_LT_MR_RESTART_TRAINING_MASK,
                      ETH_LT_CTRL_LT_MR_RESTART_TRAINING_OFFSET, 1);
      pmd_write_field(&mss, ETH_LT_CTRL_ADDR,
                      ETH_LT_CTRL_LT_MR_RESTART_TRAINING_MASK,
                      ETH_LT_CTRL_LT_MR_RESTART_TRAINING_OFFSET, 0);
    }
    else if (phy_inst_info->phy_eq_mode == QCOM_AW_PHY_MANUAL_EQ_MODE) {
      /* TX power down */
      aw_err_val = aw_pmd_iso_request_tx_state_change(
          &mss, AW_PD, config.rate, config.width, TX_ACK_TIMEOUT_US);
      if (aw_err_val != AW_ERR_CODE_NONE) {
        ret_val = EIO;
        local_err_val = LOCAL_ERROR_5;
        mutex_unlock(&phy_inst_info->lane_lock[lane]);
        mutex_unlock(&phy_inst_info->phy_inst_lock);
        goto func_exit;
      }

      /* RX power down */
      aw_err_val = aw_pmd_iso_request_rx_state_change(
          &mss, AW_PD, config.rate, config.width, RX_ACK_TIMEOUT_US);
      if (aw_err_val != AW_ERR_CODE_NONE) {
        ret_val = EIO;
        local_err_val = LOCAL_ERROR_6;
        mutex_unlock(&phy_inst_info->lane_lock[lane]);
        mutex_unlock(&phy_inst_info->phy_inst_lock);
        goto func_exit;
      }

      /* TX power up */
      aw_err_val = aw_pmd_iso_request_tx_state_change(
          &mss, AW_P0, config.rate, config.width, TX_ACK_TIMEOUT_US);
      if (aw_err_val != AW_ERR_CODE_NONE) {
        ret_val = EIO;
        local_err_val = LOCAL_ERROR_7;
        goto func_exit;
      }

      /* RX power up */
      aw_err_val = aw_pmd_iso_request_rx_state_change(
          &mss, AW_P0, config.rate, config.width, RX_ACK_TIMEOUT_US);
      if (aw_err_val != AW_ERR_CODE_NONE) {
        ret_val = EIO;
        local_err_val = LOCAL_ERROR_8;
        goto func_exit;
      }

      // TX FIR Config
      txfir_cfg.CM3 = 0;
      txfir_cfg.CM2 = 0;
      txfir_cfg.CM1 = 0;
      txfir_cfg.C0 = 60;
      txfir_cfg.C1 = 0;
      txfir_cfg.main_or_max = 1;
      aw_pmd_txfir_config_set(&mss, &txfir_cfg, 1);

      aw_pmd_rx_background_adapt_enable_set(&mss, 1);

      /* Delay before triggering RX equalization */
      mdelay(500);

      // RX Equalization - Check aw_eq_type_e enum
      aw_pmd_rx_equalize(&mss, AW_EQ_FULL_DIR, RX_LINKEVAL_FULL_TIMEOUT_US);

      /* Delay before checking RX CDR lock post equalization */
      mdelay(500);
    }

    cdr_lock_status = aw_pmd_rx_check_cdr_lock(&mss, RX_CDR_TIMEOUT_US);

    if(cdr_lock_status == AW_ERR_CODE_NONE){
      qcom_aw_phy_handle_cdr_lock_status(phy_inst_info, lane, CDR_LOCK_SUCCESS);
    }
    else{
      qcom_aw_phy_handle_cdr_lock_status(phy_inst_info, lane,
                                         CDR_LOCK_FAILURE);
    }
  }

  mutex_unlock(&phy_inst_info->lane_lock[lane]);
  mutex_unlock(&phy_inst_info->phy_inst_lock);

func_exit:
  if(local_err_val != LOCAL_ERROR_INVALID){
    QCOM_AW_PHY_LOG_DBG("%s: returns %d with local error %d",
                        __func__, ret_val, local_err_val);
  }

  kfree(wq_params);

  return;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_notify_lane_bring_up_progress_to_mac

* @phy_inst: PHY instance type(FH/C2C/Debug)
* @lane_num: Lane number

* Description: This function notifies MAC that lane bring up is in progress and
               it should stop listening to link status interrupts.
------------------------------------------------------------------- */
void qcom_aw_phy_notify_lane_bring_up_progress_to_mac(
  struct qcom_aw_phy_inst_config *phy_inst_info,
  enum eth_phy_iface_phy_lane_num_enum lane,
  bool in_progress) {

  u32 eth_link_index;

  QCOM_AW_PHY_LOG_DBG("Lane bring up status %d for PHY %d, lane %d",
                      in_progress, phy_inst_info->phy_inst, lane);

  eth_link_index = phy_inst_info->lane_params[lane].lane_config.link_index;

  qcom_aw_phy_mtip_if_info_s.lane_bring_up_progress_ind(
                                                   eth_link_index, in_progress);

  return;
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
