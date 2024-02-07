/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2024 Qualcomm Innovation Center, Inc. All rights reserved.
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

extern int qcom_aw_phy_tx_compliance_flag;
extern int qcom_aw_phy_an_restart_delay_timer;

#define MAX_PHY_LANE_STR_LEN 12

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
      !ready_info->notify_an_result || !is_phy_ready) {
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
  qcom_aw_phy_mtip_if_info_s.notify_an_result = ready_info->notify_an_result;

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
  char temp_buf[MAX_PHY_LANE_STR_LEN] = {0};
  char buf[MAX_PHY_LANE_STR_LEN] = {0};
  enum eth_phy_iface_phy_lane_speed_enum lane_speed = PHY_LANE_SPEED_10G;
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;
  int ret_val = 0;

  QCOM_AW_PHY_LOG_DBG("qcom_aw_phy_setup !");

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

  for (i = 0; i < PHY_LANE_MAX; i++) {
    phy_lane_params = &phy_inst_info->lane_params[i];
    if (lane_config[i].lane_enabled) {
        snprintf(temp_buf, sizeof(temp_buf), "%d ", i);
        strlcat(buf, temp_buf, sizeof(buf));
        lane_speed = lane_config[i].lane_speed;
    }
  }

  QCOM_AW_PHY_LOG_INFO("Setting up PHY %d for lanes %s with speed %d",
                       port_type, buf, lane_speed);

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

  if(lane_level_status == CDR_LOCK_FAILURE){
    QCOM_AW_PHY_LOG_ERR("CDR lock status %d for PHY %d, lane %d",
                        lane_level_status, phy_inst_info->phy_inst, lane);
  }

  if(lane >= PHY_LANE_MAX)
  {
    QCOM_AW_PHY_LOG_ERR("Operation on an Invalid lane %d",lane);
    return;
  }
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

  qcom_aw_phy_mtip_if_info_s.cdr_lock_ind(eth_link_index, eth_level_status,
                                          phy_inst_info->an_params.seq_num);

  if(eth_level_status == true){
    /* Notify MAC to start listening to PCS link interrupts */
    //qcom_aw_phy_notify_lane_bring_up_progress_to_mac(phy_inst_info, lane, false);

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

void qcom_aw_phy_reset_anlt(mss_access_t *mss) {
  aw_pmd_anlt_link_training_reset(mss);
  aw_pmd_anlt_auto_neg_start_set(mss, 0);
  aw_pmd_iso_tx_reset_set(mss, 0);
  aw_pmd_iso_tx_reset_set(mss, 1);
  aw_pmd_iso_rx_reset_set(mss, 0);
  aw_pmd_iso_rx_reset_set(mss, 1);
  return;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_reset_phy_sm

* @port_type: MAC port type

* Description: This function resets AN state machine and common lane
  for this PHY instance.
------------------------------------------------------------------- */
int qcom_aw_phy_reset_phy_sm(enum mtip_port_type_enum port_type) {
  struct qcom_aw_phy_config *phy_config_info = NULL;
  enum qcom_aw_phy_instance_enum phy_inst_type = QCOM_AW_PHY_INST_MAX;
  struct qcom_aw_phy_inst_config *phy_inst_info = NULL;
  mss_access_t mss = {.phy_offset = 0, .lane_offset = 0};
  enum eth_phy_iface_phy_lane_num_enum start_lane = PHY_LANE_0;
  struct qcom_aw_phy_lane_speed_config config;
  int i = 0;
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

  QCOM_AW_PHY_LOG_INFO("Resetting state machine for PHY %d", phy_inst_type);

  /* Hard code the master lane number as 2 for Debug port */
  if(port_type == MTIP_PORT_TYPE_DEBUG)
    start_lane = PHY_LANE_2;

  /* Reset the AN result and FEC modes for fresh AN */
  for(i=start_lane; i<PHY_LANE_MAX; i++){

    mutex_lock(&phy_inst_info->lane_lock[i]);

    pmd_set_lane(&mss, i);

    qcom_aw_phy_reset_anlt(&mss);
    phy_inst_info->an_params.an_state[i] = PHY_AN_STATE_NONE;

    qcom_aw_phy_get_lane_speed_config(
                phy_inst_info->lane_params[i].lane_config.lane_speed, &config);

    /* TX power down */
    aw_pmd_iso_request_tx_state_change(
                     &mss, AW_PD, config.rate, config.width, TX_ACK_TIMEOUT_US);

    /* RX power down */
    aw_pmd_iso_request_rx_state_change(
                     &mss, AW_PD, config.rate, config.width, RX_ACK_TIMEOUT_US);

    mutex_unlock(&phy_inst_info->lane_lock[i]);
  }

  phy_inst_info->bring_up_status = false;

  /* Reset the equalization mode to default */
  phy_inst_info->phy_eq_mode = QCOM_AW_PHY_MANUAL_EQ_MODE;
  phy_inst_info->an_params.seq_num = 0;

  /* Common Lane Tear down */
  aw_err_val = aw_pmd_iso_request_cmn_state_change(&mss, AW_CMN_PD,
                                                   CMN_ACK_TIMEOUT_US);
  if (aw_err_val != AW_ERR_CODE_NONE) {
    ret_val = EIO;
    local_err_val = LOCAL_ERROR_3;
    mutex_unlock(&phy_inst_info->phy_inst_lock);
    goto func_exit;
  }

  mutex_unlock(&phy_inst_info->phy_inst_lock);

func_exit:
  if(local_err_val != LOCAL_ERROR_INVALID){
    QCOM_AW_PHY_LOG_ERR("returns %d with local error %d and aw_error %d",
                        ret_val, local_err_val, aw_err_val);
  }

  return ret_val;
}

void qcom_aw_phy_set_tx_compliance(bool flag){
  qcom_aw_phy_tx_compliance_flag = flag;
}

int qcom_aw_phy_configure_speed_mode(
                                  struct qcom_aw_phy_inst_config *phy_inst_info,
                                  uint32_t port_config_mask){
  enum mtip_port_config_enum i = MTIP_PORT_CONFIG_1x100GBASE_R;
  int ret_val = 0;

  QCOM_AW_PHY_LOG_ERR("PHY %d, port_config = 0x%x",
                      phy_inst_info->phy_inst, port_config_mask);

  memset(phy_inst_info->an_params.adv_ability, 0 ,
         sizeof(uint32_t)*PHY_SPEED_SPEC_MAX);
  memset(phy_inst_info->an_params.fec_ability, 0 ,
         sizeof(uint32_t)*PHY_FEC_SPEC_MAX);

  for(i=MTIP_PORT_CONFIG_1x100GBASE_R; i<MTIP_PORT_CONFIG_MAX; i++){
    if(port_config_mask & (1<<i)){
      switch(i){
        case MTIP_PORT_CONFIG_1x100GBASE_R:
        case MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC_LL:
        case MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC:
          phy_inst_info->an_params.adv_ability[PHY_SPEED_SPEC_100G_BASE_K_CR] = 1;
          break;


        case MTIP_PORT_CONFIG_1x100GBASE_R2:
        case MTIP_PORT_CONFIG_1x100GBASE_R2_RSFEC:
          phy_inst_info->an_params.adv_ability[PHY_SPEED_SPEC_100G_BASE_K_CR2] = 1;
          break;

        case MTIP_PORT_CONFIG_1x100GBASE_R4:
        case MTIP_PORT_CONFIG_1x100GBASE_R4_RSFEC:
          phy_inst_info->an_params.adv_ability[PHY_SPEED_SPEC_100G_BASE_KR4] = 1;
          phy_inst_info->an_params.adv_ability[PHY_SPEED_SPEC_100G_BASE_CR4] = 1;
          break;

        case MTIP_PORT_CONFIG_1x50GBASE_R:
        case MTIP_PORT_CONFIG_1x50GBASE_R_RSFEC:
        case MTIP_PORT_CONFIG_2x50GBASE_R:
        case MTIP_PORT_CONFIG_2x50GBASE_R_RSFEC:
          phy_inst_info->an_params.adv_ability[PHY_SPEED_SPEC_50G_BASE_K_CR] = 1;
          break;

        case MTIP_PORT_CONFIG_1x50GBASE_R2:
        case MTIP_PORT_CONFIG_1x50GBASE_R2_RSFEC:
        case MTIP_PORT_CONFIG_1x50GBASE_R2_LUAI:
        case MTIP_PORT_CONFIG_1x50GBASE_R2_LUAI_FEC:
        case MTIP_PORT_CONFIG_2x50GBASE_R2:
        case MTIP_PORT_CONFIG_2x50GBASE_R2_FEC:
        case MTIP_PORT_CONFIG_2x50GBASE_R2_LUAI:
        case MTIP_PORT_CONFIG_2x50GBASE_R2_LUAI_FEC:
          //TBD - Consortium mode
          break;

        case MTIP_PORT_CONFIG_1x40GBASE_R4:
        case MTIP_PORT_CONFIG_1x40GBASE_R4_FEC:
          phy_inst_info->an_params.adv_ability[PHY_SPEED_SPEC_40G_BASE_KR4] = 1;
          phy_inst_info->an_params.adv_ability[PHY_SPEED_SPEC_40G_BASE_CR4] = 1;
          break;

        case MTIP_PORT_CONFIG_1x25GBASE_R:
        case MTIP_PORT_CONFIG_4x25GBASE_R:
          phy_inst_info->an_params.adv_ability[PHY_SPEED_SPEC_25G_BASE_K_CR] = 1;
          phy_inst_info->an_params.adv_ability[PHY_SPEED_SPEC_25G_BASE_K_CR_S] = 1;
          break;

        case MTIP_PORT_CONFIG_1x25GBASE_R_FEC:
        case MTIP_PORT_CONFIG_4x25GBASE_R_FEC:
          phy_inst_info->an_params.adv_ability[PHY_SPEED_SPEC_25G_BASE_K_CR] = 1;
          phy_inst_info->an_params.adv_ability[PHY_SPEED_SPEC_25G_BASE_K_CR_S] = 1;
          phy_inst_info->an_params.fec_ability[PHY_25G_BASE_R_FEC] = 1;
          break;

        case MTIP_PORT_CONFIG_1x25GBASE_R_RSFEC:
        case MTIP_PORT_CONFIG_4x25GBASE_R_RSFEC:
          phy_inst_info->an_params.adv_ability[PHY_SPEED_SPEC_25G_BASE_K_CR] = 1;
          phy_inst_info->an_params.adv_ability[PHY_SPEED_SPEC_25G_BASE_K_CR_S] = 1;
          phy_inst_info->an_params.fec_ability[PHY_25G_RS_FEC] = 1;
          break;

        case MTIP_PORT_CONFIG_1x10GBASE_R:
        case MTIP_PORT_CONFIG_4x10GBASE_R:
          phy_inst_info->an_params.adv_ability[PHY_SPEED_SPEC_10G_BASE_KR] = 1;
          break;

        case MTIP_PORT_CONFIG_1x10GBASE_R_FEC:
        case MTIP_PORT_CONFIG_4x10GBASE_R_FEC:
          phy_inst_info->an_params.adv_ability[PHY_SPEED_SPEC_10G_BASE_KR] = 1;
          phy_inst_info->an_params.fec_ability[PHY_10G_BASE_R_FEC] = 1;
          break;

        default:
          break;
      }
    }
  }

  return ret_val;
}

enum mtip_port_config_enum qcom_aw_phy_an_result_to_debug_port_config(
                                struct qcom_aw_phy_inst_config *phy_inst_info){

  switch(phy_inst_info->an_params.an_result[PHY_LANE_2]){

  // TBD - to add FEC modes

    case PHY_SPEED_SPEC_10G_BASE_KR:
      return MTIP_PORT_CONFIG_1x10GBASE_R;

    case PHY_SPEED_SPEC_25G_BASE_K_CR_S:
    case PHY_SPEED_SPEC_25G_BASE_K_CR:
      return MTIP_PORT_CONFIG_1x25GBASE_R;

    case PHY_SPEED_SPEC_50G_BASE_K_CR:
      if(phy_inst_info->an_params.an_result[PHY_LANE_3] ==
                                                 PHY_SPEED_SPEC_50G_BASE_K_CR){
         return MTIP_PORT_CONFIG_2x50GBASE_R;
      }
      else{
        return MTIP_PORT_CONFIG_1x50GBASE_R;
      }

    case PHY_SPEED_SPEC_100G_BASE_K_CR2:
      return MTIP_PORT_CONFIG_1x100GBASE_R2;

    case PHY_SPEED_SPEC_100G_BASE_K_CR:
      return MTIP_PORT_CONFIG_1x100GBASE_R;

    default:
      return MTIP_PORT_CONFIG_MAX;
  }

  return MTIP_PORT_CONFIG_MAX;
}

enum mtip_port_config_enum qcom_aw_phy_an_result_to_port_config(
                                struct qcom_aw_phy_inst_config *phy_inst_info){

  if(phy_inst_info->phy_inst == QCOM_AW_PHY_INST_DEBUG)
    return qcom_aw_phy_an_result_to_debug_port_config(phy_inst_info);

  switch(phy_inst_info->an_params.an_result[PHY_LANE_0]){

    case PHY_SPEED_SPEC_10G_BASE_KR:
      if((phy_inst_info->an_params.mac_port_config_mask & (1<<MTIP_PORT_CONFIG_4x10GBASE_R)) ||
         (phy_inst_info->an_params.mac_port_config_mask & (1<<MTIP_PORT_CONFIG_4x10GBASE_R_FEC))){

         if(phy_inst_info->an_params.fec_ability[PHY_10G_BASE_R_FEC] == 1 &&
            phy_inst_info->an_params.lp_fec_ability[PHY_LANE_0][PHY_10G_BASE_R_FEC] == 1){
           phy_inst_info->an_params.an_fec_result[PHY_LANE_0] = PHY_10G_BASE_R_FEC;
           phy_inst_info->an_params.an_fec_result[PHY_LANE_1] = PHY_10G_BASE_R_FEC;
           phy_inst_info->an_params.an_fec_result[PHY_LANE_2] = PHY_10G_BASE_R_FEC;
           phy_inst_info->an_params.an_fec_result[PHY_LANE_3] = PHY_10G_BASE_R_FEC;
           return MTIP_PORT_CONFIG_4x10GBASE_R_FEC;
         }
         else
           return MTIP_PORT_CONFIG_4x10GBASE_R;
      }
      else{
        if(phy_inst_info->an_params.fec_ability[PHY_10G_BASE_R_FEC] == 1 &&
           phy_inst_info->an_params.lp_fec_ability[PHY_LANE_0][PHY_10G_BASE_R_FEC] == 1){
          phy_inst_info->an_params.an_fec_result[PHY_LANE_0] = PHY_10G_BASE_R_FEC;
          return MTIP_PORT_CONFIG_1x10GBASE_R_FEC;
        }
        else
          return MTIP_PORT_CONFIG_1x10GBASE_R;
      }

    case PHY_SPEED_SPEC_25G_BASE_K_CR_S:
    case PHY_SPEED_SPEC_25G_BASE_K_CR:
      if((phy_inst_info->an_params.mac_port_config_mask & (1<<MTIP_PORT_CONFIG_4x25GBASE_R)) ||
         (phy_inst_info->an_params.mac_port_config_mask & (1<<MTIP_PORT_CONFIG_4x25GBASE_R_RSFEC)) ||
         (phy_inst_info->an_params.mac_port_config_mask & (1<<MTIP_PORT_CONFIG_4x25GBASE_R_FEC))){

        if(phy_inst_info->an_params.fec_ability[PHY_25G_RS_FEC] == 1 &&
           phy_inst_info->an_params.lp_fec_ability[PHY_LANE_0][PHY_25G_RS_FEC] == 1){
          phy_inst_info->an_params.an_fec_result[PHY_LANE_0] = PHY_25G_RS_FEC;
          phy_inst_info->an_params.an_fec_result[PHY_LANE_1] = PHY_25G_RS_FEC;
          phy_inst_info->an_params.an_fec_result[PHY_LANE_2] = PHY_25G_RS_FEC;
          phy_inst_info->an_params.an_fec_result[PHY_LANE_3] = PHY_25G_RS_FEC;
          return MTIP_PORT_CONFIG_4x25GBASE_R_RSFEC;
        }
        else if(phy_inst_info->an_params.fec_ability[PHY_25G_BASE_R_FEC] == 1 &&
           phy_inst_info->an_params.lp_fec_ability[PHY_LANE_0][PHY_25G_BASE_R_FEC] == 1){
          phy_inst_info->an_params.an_fec_result[PHY_LANE_0] = PHY_25G_BASE_R_FEC;
          phy_inst_info->an_params.an_fec_result[PHY_LANE_1] = PHY_25G_BASE_R_FEC;
          phy_inst_info->an_params.an_fec_result[PHY_LANE_2] = PHY_25G_BASE_R_FEC;
          phy_inst_info->an_params.an_fec_result[PHY_LANE_3] = PHY_25G_BASE_R_FEC;
          return MTIP_PORT_CONFIG_4x25GBASE_R_FEC;
        }
        else
          return MTIP_PORT_CONFIG_4x25GBASE_R;
      }
      else{
        if(phy_inst_info->an_params.fec_ability[PHY_25G_RS_FEC] == 1 &&
           phy_inst_info->an_params.lp_fec_ability[PHY_LANE_0][PHY_25G_RS_FEC] == 1){
          phy_inst_info->an_params.an_fec_result[PHY_LANE_0] = PHY_25G_RS_FEC;
          return MTIP_PORT_CONFIG_1x25GBASE_R_RSFEC;
        }
        else if(phy_inst_info->an_params.fec_ability[PHY_25G_BASE_R_FEC] == 1 &&
                phy_inst_info->an_params.lp_fec_ability[PHY_LANE_0][PHY_25G_BASE_R_FEC] == 1){
          phy_inst_info->an_params.an_fec_result[PHY_LANE_0] = PHY_25G_BASE_R_FEC;
          return MTIP_PORT_CONFIG_1x25GBASE_R_FEC;
        }
        else
          return MTIP_PORT_CONFIG_1x25GBASE_R;
        }

    case PHY_SPEED_SPEC_40G_BASE_KR4:
    case PHY_SPEED_SPEC_40G_BASE_CR4:
      if(phy_inst_info->an_params.mac_port_config_mask & (1<<MTIP_PORT_CONFIG_1x40GBASE_R4_FEC))
        return MTIP_PORT_CONFIG_1x40GBASE_R4_FEC;
      else
        return MTIP_PORT_CONFIG_1x40GBASE_R4;

    case PHY_SPEED_SPEC_50G_BASE_K_CR:
      if(phy_inst_info->an_params.mac_port_config_mask & (1<<MTIP_PORT_CONFIG_2x50GBASE_R_RSFEC))
        return MTIP_PORT_CONFIG_2x50GBASE_R_RSFEC;
      else if(phy_inst_info->an_params.mac_port_config_mask & (1<<MTIP_PORT_CONFIG_2x50GBASE_R))
       return MTIP_PORT_CONFIG_2x50GBASE_R;
      else if(phy_inst_info->an_params.mac_port_config_mask & (1<<MTIP_PORT_CONFIG_1x50GBASE_R_RSFEC))
        return MTIP_PORT_CONFIG_1x50GBASE_R_RSFEC;
      else
        return MTIP_PORT_CONFIG_1x50GBASE_R;

    case PHY_SPEED_SPEC_100G_BASE_KR4:
    case PHY_SPEED_SPEC_100G_BASE_CR4:
      if(phy_inst_info->an_params.mac_port_config_mask & (1<<MTIP_PORT_CONFIG_1x100GBASE_R4_RSFEC))
        return MTIP_PORT_CONFIG_1x100GBASE_R4_RSFEC;
      else
        return MTIP_PORT_CONFIG_1x100GBASE_R4;

    case PHY_SPEED_SPEC_100G_BASE_K_CR2:
      if(phy_inst_info->an_params.mac_port_config_mask & (1<<MTIP_PORT_CONFIG_1x100GBASE_R2_RSFEC))
        return MTIP_PORT_CONFIG_1x100GBASE_R2_RSFEC;
      else
       return MTIP_PORT_CONFIG_1x100GBASE_R2;

    case PHY_SPEED_SPEC_100G_BASE_K_CR:
      if(phy_inst_info->an_params.mac_port_config_mask & (1<<MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC))
        return MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC;
      else if(phy_inst_info->an_params.mac_port_config_mask & (1<<MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC_LL))
        return MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC_LL;
      else
       return MTIP_PORT_CONFIG_1x100GBASE_R;

    default:
      return MTIP_PORT_CONFIG_MAX;
  }

  return MTIP_PORT_CONFIG_MAX;
}

int qcom_aw_phy_get_num_lanes_for_speed_mode(int speed_mode){

  switch(speed_mode){
    case PHY_SPEED_SPEC_10G_BASE_KR:
    case PHY_SPEED_SPEC_25G_BASE_K_CR_S:
    case PHY_SPEED_SPEC_25G_BASE_K_CR:
    case PHY_SPEED_SPEC_50G_BASE_K_CR:
    case PHY_SPEED_SPEC_100G_BASE_K_CR:
      return 1;

    case PHY_SPEED_SPEC_100G_BASE_K_CR2:
      return 2;

    case PHY_SPEED_SPEC_40G_BASE_KR4:
    case PHY_SPEED_SPEC_40G_BASE_CR4:
    case PHY_SPEED_SPEC_100G_BASE_KR4:
    case PHY_SPEED_SPEC_100G_BASE_CR4:
      return 4;

    default:
      return 0;
  }

  return 0;
}


bool qcom_aw_phy_is_an_adv_multi_lane_enabled(
                                uint32_t adv_ability[PHY_SPEED_SPEC_MAX]){
  if((adv_ability[PHY_SPEED_SPEC_100G_BASE_KR4] == 1) ||
     (adv_ability[PHY_SPEED_SPEC_100G_BASE_CR4] == 1) ||
     (adv_ability[PHY_SPEED_SPEC_40G_BASE_KR4] == 1) ||
     (adv_ability[PHY_SPEED_SPEC_40G_BASE_CR4] == 1) ||
     (adv_ability[PHY_SPEED_SPEC_100G_BASE_K_CR2] == 1)){
    return true;
  }

  return false;
}

bool qcom_aw_phy_is_an_adv_single_lane_enabled(
                                uint32_t adv_ability[PHY_SPEED_SPEC_MAX]){
  if((adv_ability[PHY_SPEED_SPEC_10G_BASE_KR] == 1) ||
     (adv_ability[PHY_SPEED_SPEC_25G_BASE_K_CR_S] == 1) ||
     (adv_ability[PHY_SPEED_SPEC_25G_BASE_K_CR] == 1) ||
     (adv_ability[PHY_SPEED_SPEC_50G_BASE_K_CR] == 1) ||
     (adv_ability[PHY_SPEED_SPEC_100G_BASE_K_CR] == 1)){
    return true;
  }

  return false;
}

int qcom_aw_phy_get_an_adv_ability_mask(int* an_adv_ability) {

  int i=0;
  int an_adv_ability_mask=0;

  for(i=0; i<PHY_SPEED_SPEC_MAX; i++){
    if(an_adv_ability[i]){
      an_adv_ability_mask |= (1<<i);
    }
  }

  return an_adv_ability_mask;
}

int qcom_aw_phy_get_an_fec_ability_mask(int* an_fec_ability) {

  int i=0;
  int an_fec_ability_mask=0;

  for(i=0; i<PHY_FEC_SPEC_MAX; i++){
    if(an_fec_ability[i]){
      an_fec_ability_mask |= (1<<i);
    }
  }

  return an_fec_ability_mask;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_perform_an

* Description: This function brings up the lanes in ANLT mode
------------------------------------------------------------------- */
int qcom_aw_phy_perform_an(
                                struct qcom_aw_phy_inst_config *phy_inst_info,
                                uint32_t adv_ability[PHY_SPEED_SPEC_MAX],
                                uint32_t fec_ability[PHY_FEC_SPEC_MAX]) {
  mss_access_t mss = {.phy_offset = 0, .lane_offset = 0};
  enum eth_phy_iface_phy_lane_num_enum lane = PHY_LANE_0;
  uint32_t an_no_attached = 1;
  uint32_t status_check_disable = 2;
  uint32_t next_page_en = 0;
  mss_access_t temp_mss = {0};
  int i=0, start_lane=PHY_LANE_0, end_lane=PHY_LANE_MAX;
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;
  aw_err_code_t aw_err_val = AW_ERR_CODE_NONE;
  int ret_val = 0;

  QCOM_AW_PHY_LOG_INFO(
      "Performing AN for PHY %d, lane %d, AN adv ability 0x%x, "
      "FEC ability 0x%x, AN state %d",
      phy_inst_info->phy_inst,
      phy_inst_info->an_params.current_lane,
      qcom_aw_phy_get_an_adv_ability_mask(adv_ability),
      qcom_aw_phy_get_an_fec_ability_mask(fec_ability),
      phy_inst_info->an_params.an_state[phy_inst_info->an_params.current_lane]);

  /* Current lane on which AN needs to be performed - To be set by the caller */
  lane = phy_inst_info->an_params.current_lane;

  /* Setup PHY offset */
  mss.phy_offset = temp_mss.phy_offset = phy_inst_info->base_addr;
  pmd_set_lane(&mss, lane);

  /* Multi lane config check */
  if(qcom_aw_phy_is_an_adv_multi_lane_enabled(adv_ability)){

    an_no_attached = 0;

    /* TBD, based on the BaseR config, start and end lane needs to be revised
       Currently, end lane is hard coded to PHY_LANE_MAX */
    start_lane = lane;

    for(i=start_lane; i < end_lane; i++){

      pmd_set_lane(&temp_mss, i);

      /* Lane Isolation */
      aw_err_val = aw_pmd_isolate_lane_set(&temp_mss, 1);
      if (aw_err_val != AW_ERR_CODE_NONE) {
        ret_val = EIO;
        local_err_val = LOCAL_ERROR_0;
      }

      /* Notify MAC to stop listening to PCS link interrupts */
      qcom_aw_phy_notify_lane_bring_up_progress_to_mac(phy_inst_info, i, true);

      /* Stop listening to SNR valid/error interrupts */
      qcom_aw_phy_disable_snr_interrupt(phy_inst_info, i);

      /* Reset TX and RX lanes */
      aw_pmd_iso_tx_reset_set(&temp_mss, 1);
      aw_pmd_iso_rx_reset_set(&temp_mss, 1);

      /* For multi lane, set the logical lane starting from 0 for start(master)
         lane and keep on incrementing for the next(slave) lanes */
      aw_pmd_anlt_logical_lane_num_set(&temp_mss, i-start_lane, an_no_attached);

      aw_pmd_rx_background_adapt_enable_set(&temp_mss, 1);

      aw_pmd_anlt_auto_neg_start_set(&temp_mss, 0);

      /* Clock needs to be set as 156MHz */
      aw_pmd_anlt_ms_per_ck_set(&temp_mss, 156249);
    }
  }
  /* Single lane */
  else if(qcom_aw_phy_is_an_adv_single_lane_enabled(adv_ability)){

    pmd_set_lane(&temp_mss, lane);

    /* Lane Isolation */
    aw_err_val = aw_pmd_isolate_lane_set(&temp_mss, 1);
    if (aw_err_val != AW_ERR_CODE_NONE) {
      ret_val = EIO;
      local_err_val = LOCAL_ERROR_1;
    }

    /* Notify MAC to stop listening to PCS link interrupts */
    qcom_aw_phy_notify_lane_bring_up_progress_to_mac(phy_inst_info, lane, true);

    /* Stop listening to SNR valid/error interrupts */
    qcom_aw_phy_disable_snr_interrupt(phy_inst_info, lane);

    /* Reset TX and RX lanes */
    aw_pmd_iso_tx_reset_set(&temp_mss, 1);
    aw_pmd_iso_rx_reset_set(&temp_mss, 1);

    /* For single lane, set the logical lane to 0 always as it will be the
       master lane */
    aw_pmd_anlt_logical_lane_num_set(&temp_mss, i, an_no_attached);

    aw_pmd_rx_background_adapt_enable_set(&temp_mss, 1);

    aw_pmd_anlt_auto_neg_start_set(&temp_mss, 0);

    /* Clock needs to be set as 156MHz */
    aw_pmd_anlt_ms_per_ck_set(&temp_mss, 156249);
  }
  else{
    ret_val = EIO;
    local_err_val = LOCAL_ERROR_2;
    goto func_exit;
  }

  /* Status check disable flag should be 0, can be modified for debugging if
     needed. Next page enabled needs to be set for some 3ed party servers and
     consortium speed modes */
  aw_pmd_anlt_auto_neg_config_set(&mss, status_check_disable, next_page_en, 1);

  QCOM_AW_PHY_LOG_DBG("Starting AN with adv ability 0x%x and FEC 0x%x",
                      qcom_aw_phy_get_an_adv_ability_mask(adv_ability),
                      qcom_aw_phy_get_an_fec_ability_mask(fec_ability));

  aw_pmd_anlt_auto_neg_adv_ability_set(&mss, adv_ability, fec_ability, 0);

  /* If multi lane is enabled, need to start LT and AN for all lanes, but
     master lane needs to be brought up only at the end */
  if(qcom_aw_phy_is_an_adv_multi_lane_enabled(adv_ability)){
    for(i=start_lane+1; i < end_lane; i++){
      pmd_set_lane(&temp_mss, i);
      aw_pmd_anlt_link_training_en_set(&temp_mss, 1);
      aw_pmd_anlt_auto_neg_start_set(&temp_mss, 1);
    }
  }

  /* Enable LT and AN for master lane */
  aw_pmd_anlt_link_training_en_set(&mss, 1);
  aw_pmd_anlt_auto_neg_start_set(&mss, 1);

  func_exit:
  if(local_err_val != LOCAL_ERROR_INVALID){
    QCOM_AW_PHY_LOG_ERR("returns %d with local error %d and aw_error %d",
                        ret_val, local_err_val, aw_err_val);
  }

  return ret_val;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_initiate_an

* @port_type: MAC port type
* @num_lanes: Number of lanes active/supported on this port
* @port_config_mask: Port configuration to be advertised

* Description: This function initiates AN procedure to negotiate the
speed with peer and decide the port configuration.
------------------------------------------------------------------- */
int qcom_aw_phy_initiate_an(enum mtip_port_type_enum port_type,
                                      u8 seq_num,
                                      int num_lanes,
                                      uint32_t port_config_mask) {
  struct qcom_aw_phy_config *phy_config_info = NULL;
  enum qcom_aw_phy_instance_enum phy_inst_type = QCOM_AW_PHY_INST_MAX;
  struct qcom_aw_phy_inst_config *phy_inst_info = NULL;
  mss_access_t mss = {.phy_offset = 0, .lane_offset = 0};
  int i = 0;
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

  /* Common isolate */
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

  /* Convert the MAC level port config to PHY lane speed mode */
  if (qcom_aw_phy_configure_speed_mode(phy_inst_info, port_config_mask) != 0) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_5;
    goto func_exit;
  }

  QCOM_AW_PHY_LOG_INFO(
     "Initiating AN on MAC Port %d, AN adv ability 0x%x, FEC ability 0x%x",
     port_type,
     qcom_aw_phy_get_an_adv_ability_mask(phy_inst_info->an_params.adv_ability),
     qcom_aw_phy_get_an_fec_ability_mask(phy_inst_info->an_params.fec_ability));

  /* Hard code the master lane number as 2 for Debug port */
  if(port_type == MTIP_PORT_TYPE_DEBUG)
    phy_inst_info->an_params.current_lane = PHY_LANE_2;
  else
    phy_inst_info->an_params.current_lane = PHY_LANE_0;

  phy_inst_info->an_params.num_lanes = num_lanes;
  phy_inst_info->an_params.mac_port_config_mask = port_config_mask;

  /* Reset the AN result and FEC modes for fresh AN */
  for(i=PHY_LANE_0; i<PHY_LANE_MAX; i++){
    phy_inst_info->an_params.an_result[i] = -1;
    phy_inst_info->an_params.an_fec_result[i] = -1;
    memset(phy_inst_info->an_params.lp_fec_ability[i], 0,
           sizeof(uint32_t) * PHY_FEC_SPEC_MAX);
  }

  /* Move the AN state to START and proceed with AN */
  phy_inst_info->an_params.an_state[phy_inst_info->an_params.current_lane] =
                                                             PHY_AN_STATE_START;
  phy_inst_info->phy_eq_mode = QCOM_AW_PHY_ANLT_MODE;
  phy_inst_info->an_params.seq_num = seq_num;
  qcom_aw_phy_perform_an(phy_inst_info, phy_inst_info->an_params.adv_ability,
                         phy_inst_info->an_params.fec_ability);

  mutex_unlock(&phy_inst_info->phy_inst_lock);

func_exit:
  if(local_err_val != LOCAL_ERROR_INVALID){
    QCOM_AW_PHY_LOG_ERR("returns %d with local error %d and aw_error %d",
                        ret_val, local_err_val, aw_err_val);
  }

  return ret_val;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_bringup_anlt_mode

* Description: This function brings up the PHY lanes in ANLT mode
               To be called after AN is done for master lane and
               port config is calculated.
------------------------------------------------------------------- */
int qcom_aw_phy_bringup_anlt_mode(mss_access_t *mss,
                                struct qcom_aw_phy_inst_config *phy_inst_info,
                                bool lanes_enabled[PHY_LANE_MAX]){
  enum eth_phy_iface_phy_lane_num_enum i = PHY_LANE_0;
  enum eth_phy_iface_phy_lane_num_enum j = PHY_LANE_0;
  enum eth_phy_iface_phy_lane_num_enum ref_lane;
  enum eth_phy_iface_phy_lane_num_enum temp_lane = PHY_LANE_0;
  int ret_val = 0;
  uint32_t temp_adv_ability[PHY_SPEED_SPEC_MAX];
  uint32_t temp_fec_ability[PHY_FEC_SPEC_MAX];
  int num_an_lanes = 0;

  memset(temp_adv_ability, 0, PHY_SPEED_SPEC_MAX*sizeof(uint32_t));
  memset(temp_fec_ability, 0, PHY_FEC_SPEC_MAX*sizeof(uint32_t));

  for (temp_lane = PHY_LANE_0; temp_lane < PHY_LANE_MAX; temp_lane++)
  {
    if (lanes_enabled[temp_lane] == true)
      phy_inst_info->lane_params[temp_lane].lane_bring_up_status = true;
  }

  /* For Debug port, hard code the master lane as lane 2 */
  if(phy_inst_info->phy_inst == QCOM_AW_PHY_INST_DEBUG)
    ref_lane = PHY_LANE_2;
  else
    ref_lane = PHY_LANE_0;

  while(i<PHY_LANE_MAX){

    /* Skip bring up if lane is not enabled from MAC side,
       or if AN result for master lane is not valid */
    if(lanes_enabled[i] == false ||
       phy_inst_info->an_params.an_result[ref_lane] == -1){
       i++;
      continue;
    }

    num_an_lanes = qcom_aw_phy_get_num_lanes_for_speed_mode(
                                  phy_inst_info->an_params.an_result[ref_lane]);

    /* Just trigger CDR lock successful callback if reference lane was already
       negotiated but was not brought up by MAC earlier post initiate AN */
    if(i == ref_lane){

      if(phy_inst_info->an_params.an_state[ref_lane] == PHY_AN_STATE_DONE){
        for(j=ref_lane; (j < ref_lane+num_an_lanes) && (j < PHY_LANE_MAX); j++){
          qcom_aw_phy_handle_cdr_lock_status(phy_inst_info, j, CDR_LOCK_SUCCESS);
        }
      }

      /* No need to perform AN again if initiate AN was already done for the
         reference lane, and bring up was triggered for the same */
      if(phy_inst_info->bring_up_status == false)
        return ret_val;
    }

    QCOM_AW_PHY_LOG_DBG("ANLT for PHY %d lane %d with speed mode %d FEC %d",
                        phy_inst_info->phy_inst, i,
                        phy_inst_info->an_params.an_result[ref_lane],
                        phy_inst_info->an_params.an_fec_result[ref_lane]);

    /* Use the result from master lane to advertise for the remaining lanes
       of this port */
    temp_adv_ability[phy_inst_info->an_params.an_result[ref_lane]] = 1;
    temp_fec_ability[phy_inst_info->an_params.an_fec_result[ref_lane]] = 1;
    phy_inst_info->an_params.current_lane = i;

    qcom_aw_phy_perform_an(phy_inst_info, temp_adv_ability, temp_fec_ability);

    /* If multi lane is enabled, multiple lanes will be brought up as part of
       the previous AN. So, based on the negotiated speed mode, need to jump to
       the next master lane of this config. */
    i += num_an_lanes;
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
    aw_pmd_rx_pam4_precoder_enable_set(mss, 1, 0);
    aw_pmd_tx_pam4_precoder_enable_set(mss, 1, 0);
    aw_pmd_tx_pam4_precoder_override_set(mss, 1);
  }

  /* Configuration for Near End Parallel Loopback mode */
  if (qcom_aw_phy_get_loopback_mode() == QCOM_AW_PHY_NEAR_END_PARALLEL_LB) {
    QCOM_AW_PHY_LOG_INFO("Configuring PHY for near end parallel LB");
    aw_pmd_nep_loopback_set(mss, 1);
    qcom_aw_phy_handle_cdr_lock_status(phy_inst_info, lane, CDR_LOCK_SUCCESS);
    return ret_val;
  }

  // TX FIR Config
#ifdef FEATURE_QCOM_AW_TEST_SYS_FS
  if(qcom_aw_phy_get_tx_fir_val(phy_inst_info->phy_inst, (void*)&txfir_cfg) == false)
#endif
  {
    txfir_cfg.CM3 = 0;
    txfir_cfg.CM2 = 0;
    txfir_cfg.CM1 = 0;
    txfir_cfg.C0 = 63;
    txfir_cfg.C1 = 0;
    txfir_cfg.main_or_max = 1;
  }

  aw_pmd_txfir_config_set(mss, &txfir_cfg, 1);

  /* Configuration for Near End Serial Loopback mode */
  if (qcom_aw_phy_get_loopback_mode() == QCOM_AW_PHY_NEAR_END_SERIAL_LB) {
    QCOM_AW_PHY_LOG_INFO("Configuring PHY for near end serial LB");
    aw_pmd_analog_loopback_set(mss, 1);
  }

  // RX Equalization - Check aw_eq_type_e enum
  aw_pmd_rx_equalize(mss, AW_EQ_FULL_DIR, RX_LINKEVAL_FULL_TIMEOUT_US);

  aw_pmd_rx_background_adapt_enable_set(mss, 1);

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
  char temp_buf[MAX_PHY_LANE_STR_LEN] = {0};
  char buf[MAX_PHY_LANE_STR_LEN] = {0};
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

  QCOM_AW_PHY_LOG_DBG("MAC Port %d has sfp port %d", port_type, sfp_port_type);
  phy_inst_info->sfp_port_type = sfp_port_type;

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

  if (phy_inst_info->phy_eq_mode == QCOM_AW_PHY_ANLT_MODE) {
    qcom_aw_phy_bringup_anlt_mode(&mss, phy_inst_info, lanes_enabled);
    phy_inst_info->bring_up_status = true;
    mutex_unlock(&phy_inst_info->phy_inst_lock);
    return ret_val;
  }

  for (lane = 0; lane < PHY_LANE_MAX; lane++) {
    if (lanes_enabled[lane]) {
        snprintf(temp_buf, sizeof(temp_buf), "%d ", lane);
        strlcat(buf, temp_buf, sizeof(buf));
    }
  }

  QCOM_AW_PHY_LOG_INFO("Bringing up PHY %d for lanes %s", port_type, buf);

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

    if (phy_inst_info->phy_eq_mode == QCOM_AW_PHY_LT_MODE) {
      qcom_aw_phy_bringup_lt_mode(&mss, phy_inst_info, lane, config);
    } else if (phy_inst_info->phy_eq_mode == QCOM_AW_PHY_MANUAL_EQ_MODE) {
      qcom_aw_phy_bringup_manual_eq_mode(&mss, phy_inst_info, lane, config);
    }

    phy_inst_info->lane_params[lane].lane_bring_up_status = true;

    mutex_unlock(&phy_inst_info->lane_lock[lane]);
  }

  /* First lane bring up for this PHY instance */
  if(phy_inst_info->bring_up_status == false){
    phy_inst_info->bring_up_status = true;
  }

  for (lane = PHY_LANE_0; lane < PHY_LANE_MAX; lane++) {
    /* Check if lane is valid for this MAC instance */
    if (lanes_enabled[lane] == false)
      continue;

    mutex_lock(&phy_inst_info->lane_lock[lane]);

    /* RX CDR lock check not needed if lane bring up is disabled for
       TX compliance test */
    if(qcom_aw_phy_tx_compliance_flag){
      mutex_unlock(&phy_inst_info->lane_lock[lane]);
      break;
    }

    // Check CDR Lock
    if(AW_ERR_CODE_NONE == aw_pmd_rx_check_cdr_lock(&mss, RX_CDR_TIMEOUT_US)){
      qcom_aw_phy_handle_cdr_lock_status(phy_inst_info, lane, CDR_LOCK_SUCCESS);
    }
    else{
      qcom_aw_phy_handle_cdr_lock_status(phy_inst_info, lane, CDR_LOCK_FAILURE);
      mutex_unlock(&phy_inst_info->lane_lock[lane]);
      break;
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
  char temp_buf[MAX_PHY_LANE_STR_LEN] = {0};
  char buf[MAX_PHY_LANE_STR_LEN] = {0};
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

  for (lane = 0; lane < PHY_LANE_MAX; lane++) {
    if (lanes_enabled[lane]) {
        snprintf(temp_buf, sizeof(temp_buf), "%d ", lane);
        strlcat(buf, temp_buf, sizeof(buf));
    }
  }

  QCOM_AW_PHY_LOG_INFO("Tearing down PHY %d for lanes %s", port_type, buf);

  for (lane = PHY_LANE_0; lane < PHY_LANE_MAX; lane++) {
    /* Check if lane is valid for this MAC instance */
    if (lanes_enabled[lane] == false)
      continue;

   /* Get the lane specific info for the provided lane */
    phy_lane_params = &phy_inst_info->lane_params[lane];
    if(phy_lane_params->lane_bring_up_status == false)
      continue;

    if (phy_lane_params->lane_config.lane_enabled == false) {
      ret_val = EINVAL;
      local_err_val = LOCAL_ERROR_3;
      mutex_unlock(&phy_inst_info->phy_inst_lock);
      goto func_exit;
    }

    mutex_lock(&phy_inst_info->lane_lock[lane]);

    /* Set the lane offset */
    pmd_set_lane(&mss, lane);

    /* Get lane rate and width based on the speed. */
    qcom_aw_phy_get_lane_speed_config(phy_lane_params->lane_config.lane_speed,
                                      &config);

    /* Reset AN and LT */
    qcom_aw_phy_reset_anlt(&mss);
    phy_inst_info->an_params.an_state[lane] = PHY_AN_STATE_NONE;

    /* TX power down */
    aw_err_val = aw_pmd_iso_request_tx_state_change(
        &mss, AW_PD, config.rate, config.width, TX_ACK_TIMEOUT_US);
    if (aw_err_val != AW_ERR_CODE_NONE) {
      ret_val = EIO;
      local_err_val = LOCAL_ERROR_4;
      phy_inst_info->cdr_lock_status_flag[lane] = CDR_LOCK_NONE;
      mutex_unlock(&phy_inst_info->lane_lock[lane]);
      continue;
    }

    /* RX power down */
    aw_err_val = aw_pmd_iso_request_rx_state_change(
        &mss, AW_PD, config.rate, config.width, RX_ACK_TIMEOUT_US);
    if (aw_err_val != AW_ERR_CODE_NONE) {
      ret_val = EIO;
      local_err_val = LOCAL_ERROR_5;
      phy_inst_info->cdr_lock_status_flag[lane] = CDR_LOCK_NONE;
      mutex_unlock(&phy_inst_info->lane_lock[lane]);
      continue;
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
    phy_inst_info->lane_params[lane].lane_bring_up_status = false;
    phy_inst_info->lane_params[lane].rx_sig_detect_status = false;

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

int qcom_aw_phy_mac_link_status(enum mtip_port_type_enum port_type,
                                bool lanes_enabled[PHY_LANE_MAX], bool status) {
  struct qcom_aw_phy_config *phy_config_info = NULL;
  enum qcom_aw_phy_instance_enum phy_inst_type = QCOM_AW_PHY_INST_MAX;
  struct qcom_aw_phy_inst_config *phy_inst_info = NULL;
  enum eth_phy_iface_phy_lane_num_enum lane_num;
  bool notify_flag = false;
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;
  int ret_val = 0;
  struct qcom_aw_phy_work_q_params *wq_params = NULL;
  char temp_buf[MAX_PHY_LANE_STR_LEN] = {0};
  char buf[MAX_PHY_LANE_STR_LEN] = {0};
  bool needs_logging = false;

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

  for (lane_num = 0; lane_num < PHY_LANE_MAX; lane_num++) {
    if (lanes_enabled[lane_num]) {
      mutex_lock(&phy_inst_info->lane_lock[lane_num]);
      if(phy_inst_info->lane_params[lane_num].link_status != status){
        snprintf(temp_buf, sizeof(temp_buf), "%d ", lane_num);
        strlcat(buf, temp_buf, sizeof(buf));
        needs_logging = true;
      }
      mutex_unlock(&phy_inst_info->lane_lock[lane_num]);
    }
  }

  if(needs_logging){
    QCOM_AW_PHY_LOG_INFO("MAC link status %d for PHY %d lanes %s",
                         status, port_type, buf);
  }

  for (lane_num = PHY_LANE_0; lane_num < PHY_LANE_MAX; lane_num++) {
    if(lanes_enabled[lane_num]){

      mutex_lock(&phy_inst_info->lane_lock[lane_num]);
      if(phy_inst_info->lane_params[lane_num].link_status != status){
        phy_inst_info->lane_params[lane_num].link_status = status;
        notify_flag = true;
      }

      if(!status)
        phy_inst_info->cdr_lock_status_flag[lane_num] = CDR_LOCK_NONE;
      else
        phy_inst_info->cdr_lock_status_flag[lane_num] = CDR_LOCK_SUCCESS;

      if (status == false &&
          phy_inst_info->phy_eq_mode == QCOM_AW_PHY_ANLT_MODE) {

        wq_params = kmalloc(sizeof(struct qcom_aw_phy_work_q_params),
                            GFP_ATOMIC);
        if(!wq_params)
          QCOM_AW_PHY_LOG_ERR("Malloc failed!");
        else{
          INIT_DELAYED_WORK(&wq_params->wq_item, qcom_aw_phy_handle_an_restart);
          wq_params->phy_inst = phy_inst_info->phy_inst;
          wq_params->lane_num = lane_num;
          queue_delayed_work(phy_config_info->wq, &wq_params->wq_item,
                          msecs_to_jiffies(qcom_aw_phy_an_restart_delay_timer));
        }
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
* qcom_aw_phy_handle_an_done

* Description: Generated upon interrupt trigger indicating AN has
               finished along with link training.
------------------------------------------------------------------- */
void qcom_aw_phy_handle_an_done(struct work_struct *work){
  struct delayed_work *delayed_work_item = to_delayed_work(work);
  struct qcom_aw_phy_work_q_params *wq_params =
     container_of(delayed_work_item, struct qcom_aw_phy_work_q_params, wq_item);
  enum qcom_aw_phy_instance_enum phy_inst;
  enum eth_phy_iface_phy_lane_num_enum lane_num;
  struct qcom_aw_phy_config *phy_config_info = NULL;
  struct qcom_aw_phy_inst_config *phy_inst_info = NULL;
  mss_access_t mss = {.phy_offset = 0, .lane_offset = 0};
  mss_access_t temp_mss = {.phy_offset = 0, .lane_offset = 0};
  uint32_t lt_running;
  uint32_t lt_done;
  uint32_t lt_training_failure;
  uint32_t lt_rx_ready;
  int num_lanes=0, i=0;

  if(!wq_params){
    QCOM_AW_PHY_LOG_ERR("Invalid work queue structure!");
    return;
  }

  QCOM_AW_PHY_LOG_DBG("AN done rcvd for PHY %d lane %d",
                      wq_params->phy_inst, wq_params->lane_num);

  phy_inst = wq_params->phy_inst;
  lane_num = wq_params->lane_num;

  if (!QCOM_AW_PHY_INST_VALID(phy_inst) || !QCOM_AW_PHY_LANE_VALID(lane_num)){
    QCOM_AW_PHY_LOG_ERR("Invalid PHY instance/lane. AN Done failed.");
    goto func_exit;
  }

  phy_config_info = qcom_aw_phy_get_config_info();
  if (!phy_config_info) {
    goto func_exit;
  }

  /* Get the PHY instance info for the passed instance type */
  phy_inst_info = &phy_config_info->phy_inst_config_info[phy_inst];
  if (phy_inst_info->valid == false) {
    goto func_exit;
  }

  mutex_lock(&phy_inst_info->phy_inst_lock);

  /* Setup PHY offset */
  mss.phy_offset = temp_mss.phy_offset = phy_inst_info->base_addr;

  mutex_lock(&phy_inst_info->lane_lock[lane_num]);

  if(phy_inst_info->phy_eq_mode != QCOM_AW_PHY_ANLT_MODE){
    mutex_unlock(&phy_inst_info->lane_lock[lane_num]);
    mutex_unlock(&phy_inst_info->phy_inst_lock);
    goto func_exit;
  }

  /* Set the lane offset */
  pmd_set_lane(&mss, lane_num);

  /* Check the LT status */
  aw_pmd_anlt_link_training_status_get(&mss, &lt_running, &lt_done,
                                       &lt_training_failure, &lt_rx_ready);
  if (lt_training_failure == 1)
    QCOM_AW_PHY_LOG_ERR("LT failed, need to debug!");

  if (lt_done == 0)
    QCOM_AW_PHY_LOG_ERR("LT did not finish, try increasing delay");
  else{
    QCOM_AW_PHY_LOG_DBG("LT completed");
    phy_inst_info->an_params.an_state[lane_num] = PHY_AN_STATE_DONE;
    if(AW_ERR_CODE_NONE == aw_pmd_rx_check_cdr_lock(&mss, RX_CDR_TIMEOUT_US)){
      qcom_aw_phy_handle_cdr_lock_status(phy_inst_info, lane_num,
                                         CDR_LOCK_SUCCESS);
    }
    else{
      qcom_aw_phy_handle_cdr_lock_status(phy_inst_info, lane_num,
                                         CDR_LOCK_FAILURE);
    }

    /* Fetch the CDR lock for slave lanes also */
    num_lanes = qcom_aw_phy_get_num_lanes_for_speed_mode(
                                  phy_inst_info->an_params.an_result[lane_num]);
    if(num_lanes > 1){
      for(i=lane_num+1; (i< lane_num+num_lanes) && (i < PHY_LANE_MAX);i++){

        /* Set the lane offset */
        pmd_set_lane(&temp_mss, i);

        phy_inst_info->an_params.an_state[i] = PHY_AN_STATE_DONE;

        if(AW_ERR_CODE_NONE ==
                        aw_pmd_rx_check_cdr_lock(&temp_mss, RX_CDR_TIMEOUT_US)){
          qcom_aw_phy_handle_cdr_lock_status(phy_inst_info, i,
                                             CDR_LOCK_SUCCESS);
        }
        else{
          qcom_aw_phy_handle_cdr_lock_status(phy_inst_info, i,
                                             CDR_LOCK_FAILURE);
        }
      }
    }
  }

  mutex_unlock(&phy_inst_info->lane_lock[lane_num]);
  mutex_unlock(&phy_inst_info->phy_inst_lock);

func_exit:
  kfree(wq_params);
  return;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_handle_an_link_good

* Description: Generated upon interrupt trigger indicating speed
has been negotiated via AN.
------------------------------------------------------------------- */
void qcom_aw_phy_handle_an_link_good(struct work_struct *work){
  struct delayed_work *delayed_work_item = to_delayed_work(work);
  struct qcom_aw_phy_work_q_params *wq_params =
     container_of(delayed_work_item, struct qcom_aw_phy_work_q_params, wq_item);
  struct qcom_aw_phy_config *phy_config_info = NULL;
  struct qcom_aw_phy_inst_config *phy_inst_info = NULL;
  mss_access_t mss = {.phy_offset = 0, .lane_offset = 0};
  mss_access_t temp_mss = {.phy_offset = 0, .lane_offset = 0};
  uint32_t an_complete;
  enum mtip_port_config_enum port_config_result = MTIP_PORT_CONFIG_MAX;
  bool an_result = false;
  int i = 0;

  if(!wq_params){
    QCOM_AW_PHY_LOG_ERR("Invalid work queue structure!");
    return;
  }

  QCOM_AW_PHY_LOG_DBG("AN link good rcvd for PHY %d lane %d",
                      wq_params->phy_inst, wq_params->lane_num);

  if (!QCOM_AW_PHY_INST_VALID(wq_params->phy_inst) ||
      !QCOM_AW_PHY_LANE_VALID(wq_params->lane_num)){
    QCOM_AW_PHY_LOG_ERR("Invalid PHY instance/lane. AN Notification failed.");
  }

  phy_config_info = qcom_aw_phy_get_config_info();
  if (!phy_config_info) {
    return;
  }

  /* Get the PHY instance info for the passed instance type */
  phy_inst_info = &phy_config_info->phy_inst_config_info[wq_params->phy_inst];
  if (phy_inst_info->valid == false) {
    return;
  }

  mutex_lock(&phy_inst_info->phy_inst_lock);
  mutex_lock(&phy_inst_info->lane_lock[wq_params->lane_num]);

  if(phy_inst_info->phy_eq_mode != QCOM_AW_PHY_ANLT_MODE)
    goto func_exit;

  /* Setup PHY offset */
  mss.phy_offset = temp_mss.phy_offset = phy_inst_info->base_addr;
  pmd_set_lane(&mss, wq_params->lane_num);

  /* Fecth the AN status */
  aw_pmd_anlt_auto_neg_status_get(&mss, &an_complete);
  if (an_complete == 0)
    QCOM_AW_PHY_LOG_ERR("AN failed, need to debug!");
  else
    QCOM_AW_PHY_LOG_DBG("AN link good");

  /* TBD - Handle the no_consortium flag(2nd parameter) */
  aw_pmd_anlt_auto_neg_result_get(&mss, 1,
                      &phy_inst_info->an_params.an_result[wq_params->lane_num]);

  /* Read the link partner ability */
  aw_pmd_anlt_lp_auto_neg_adv_ability_get(&mss,
                  phy_inst_info->an_params.lp_adv_ability[wq_params->lane_num],
                  phy_inst_info->an_params.lp_fec_ability[wq_params->lane_num]);

  /* AN failure handling */
  if(phy_inst_info->an_params.an_result[wq_params->lane_num] == -1){

    QCOM_AW_PHY_LOG_ERR("AN failed!");
    for(i=wq_params->lane_num; i<PHY_LANE_MAX; i++){
      pmd_set_lane(&temp_mss, i);
      qcom_aw_phy_reset_anlt(&temp_mss);
      phy_inst_info->an_params.an_state[i] = PHY_AN_STATE_NONE;
    }

    phy_inst_info->an_params.an_state[wq_params->lane_num] =
                                                           PHY_AN_STATE_FAILURE;
    goto func_exit;
  }
  // AN success after PCS reconfiguration, or AN retry
  else if(phy_inst_info->an_params.an_state[wq_params->lane_num] ==
                                                      PHY_AN_STATE_PCS_CONFIG ||
          phy_inst_info->an_params.an_state[wq_params->lane_num] ==
                                                      PHY_AN_STATE_LINK_GOOD){
    phy_inst_info->an_params.an_state[wq_params->lane_num] =
                                                         PHY_AN_STATE_LINK_GOOD;
    goto func_exit;
  }
  // AN success for the first try
  else{
    if(phy_inst_info->an_params.an_state[wq_params->lane_num] ==
                                                            PHY_AN_STATE_START){
      QCOM_AW_PHY_LOG_INFO(
              "AN result successful for PHY %d lane %d, "
              "configured speed = %d, FEC = 0x%x",
              wq_params->phy_inst, wq_params->lane_num,
              phy_inst_info->an_params.an_result[wq_params->lane_num],
              qcom_aw_phy_get_an_fec_ability_mask(
                 phy_inst_info->an_params.lp_fec_ability[wq_params->lane_num]));
      phy_inst_info->an_params.an_state[wq_params->lane_num] =
                                                        PHY_AN_STATE_PCS_CONFIG;
    }
  }

  /* Convert the AN result to MAC port config type */
  port_config_result = qcom_aw_phy_an_result_to_port_config(phy_inst_info);

  QCOM_AW_PHY_LOG_INFO("PHY %d lane %d, Port_config_result = %d, "
                       "Port config mask =0x%x",
                       wq_params->phy_inst, wq_params->lane_num,
                       port_config_result,
                       phy_inst_info->an_params.mac_port_config_mask);

  /* AN result callback if calculated port config is valid and is configured */
  if(port_config_result != MTIP_PORT_CONFIG_MAX ){
    an_result = true;
    /* Notify AN result to MAC */
    qcom_aw_phy_mtip_if_info_s.notify_an_result(
                        qcom_aw_phy_inst_to_mac_port(phy_inst_info->phy_inst),
                        an_result, port_config_result,
                        phy_inst_info->an_params.seq_num);
  }
  else{
    /* Wait for remote end to come up, or change the config and bring up
       ethernet interface again to re-initiate AN */
  }

func_exit:
  mutex_unlock(&phy_inst_info->lane_lock[wq_params->lane_num]);
  mutex_unlock(&phy_inst_info->phy_inst_lock);

  kfree(wq_params);
  return;
}

void qcom_aw_phy_handle_rx_sig_detect(struct work_struct *work){
  struct delayed_work *delayed_work_item = to_delayed_work(work);
  struct qcom_aw_phy_work_q_params *wq_params =
     container_of(delayed_work_item, struct qcom_aw_phy_work_q_params, wq_item);
  struct qcom_aw_phy_config *phy_config_info = NULL;
  struct qcom_aw_phy_inst_config *phy_inst_info = NULL;
  enum qcom_aw_phy_instance_enum phy_inst_type = QCOM_AW_PHY_INST_FH0;
  enum eth_phy_iface_phy_lane_num_enum lane = PHY_LANE_0;
  mss_access_t mss = {.phy_offset = 0, .lane_offset = 0};
  aw_txfir_config_t txfir_cfg = {0};
  int cdr_lock_status = 0;
  struct qcom_aw_phy_lane_speed_config config;
  int temp_rd_val = 0;
  aw_err_code_t aw_err_val = AW_ERR_CODE_NONE;
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;
  int ret_val = 0;

  /* PHY lane retry based on RX signal detect not needed for TX
     compliance test */
  if(qcom_aw_phy_tx_compliance_flag)
    goto func_exit;

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

  for (phy_inst_type = QCOM_AW_PHY_INST_FH0;
       phy_inst_type < QCOM_AW_PHY_INST_MAX; phy_inst_type++){

    /* Get the PHY instance info for the passed instance type */
    phy_inst_info = &phy_config_info->phy_inst_config_info[phy_inst_type];
    if (!phy_inst_info || phy_inst_info->valid == false) {
      continue;
    }

    mutex_lock(&phy_inst_info->phy_inst_lock);

    if (phy_inst_info->bring_up_status == false) {
      mutex_unlock(&phy_inst_info->phy_inst_lock);
      continue;
    }

    for(lane = PHY_LANE_0; lane < PHY_LANE_MAX; lane++){

      mutex_lock(&phy_inst_info->lane_lock[lane]);

      if(phy_inst_info->lane_params[lane].lane_bring_up_status == false) {
        mutex_unlock(&phy_inst_info->lane_lock[lane]);
        continue;
      }

      /* Setup PHY offset */
      mss.phy_offset = phy_inst_info->base_addr;
      /* Set the lane offset */
      pmd_set_lane(&mss, lane);

      pmd_read_field(&mss, DIG_SOC_LANE_STAT_REG3_ADDR,
                     DIG_SOC_LANE_STAT_REG3_ODAT_RX_SIGNAL_DETECT_A_MASK,
                     DIG_SOC_LANE_STAT_REG3_ODAT_RX_SIGNAL_DETECT_A_OFFSET,
                     &temp_rd_val);

      if(temp_rd_val == 0) {
        phy_inst_info->lane_params[lane].rx_sig_detect_status = false;
        mutex_unlock(&phy_inst_info->lane_lock[lane]);
        continue;
      }

      if(phy_inst_info->lane_params[lane].rx_sig_detect_status == true) {
        mutex_unlock(&phy_inst_info->lane_lock[lane]);
        continue;
      }

      /* Retry lane bring up if detect interrupt is received and PCS link is down */
      if((phy_inst_info->lane_params[lane].link_status == false) &&
         (phy_inst_info->cdr_lock_status_flag[lane] != CDR_LOCK_SUCCESS)){

        /*QCOM_AW_PHY_LOG_INFO("Retry for PHY %d, lane %d",
                             wq_params->phy_inst, lane);*/

        /* Get lane rate and width based on the speed. */
        qcom_aw_phy_get_lane_speed_config(
                          phy_inst_info->lane_params[lane].lane_config.lane_speed,
                          &config);

        // Notify MAC to stop listening to link status interrupts
        qcom_aw_phy_notify_lane_bring_up_progress_to_mac(phy_inst_info, lane, true);

        /* Stop listening to SNR valid/error interrupts */
        qcom_aw_phy_disable_snr_interrupt(phy_inst_info, lane);

        if (phy_inst_info->phy_eq_mode == QCOM_AW_PHY_ANLT_MODE) {
          //qcom_aw_phy_reset_anlt(&mss);
          pmd_write_field(&mss, ETH_AN_CTRL_REG1_ADDR,
                          ETH_AN_CTRL_REG1_AN_MR_RESTART_NEGOTIATION_MASK,
                          ETH_AN_CTRL_REG1_AN_MR_RESTART_NEGOTIATION_OFFSET, 1);
          pmd_write_field(&mss, ETH_AN_CTRL_REG1_ADDR,
                          ETH_AN_CTRL_REG1_AN_MR_RESTART_NEGOTIATION_MASK,
                          ETH_AN_CTRL_REG1_AN_MR_RESTART_NEGOTIATION_OFFSET, 0);
        }
        else if (phy_inst_info->phy_eq_mode == QCOM_AW_PHY_LT_MODE) {
          //qcom_aw_phy_reset_anlt(&mss);
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
            mutex_unlock(&phy_inst_info->lane_lock[lane]);
            continue;
          }

          /* RX power down */
          aw_err_val = aw_pmd_iso_request_rx_state_change(
              &mss, AW_PD, config.rate, config.width, RX_ACK_TIMEOUT_US);
          if (aw_err_val != AW_ERR_CODE_NONE) {
            mutex_unlock(&phy_inst_info->lane_lock[lane]);
            continue;
          }

          /* TX power up */
          aw_err_val = aw_pmd_iso_request_tx_state_change(
              &mss, AW_P0, config.rate, config.width, TX_ACK_TIMEOUT_US);
          if (aw_err_val != AW_ERR_CODE_NONE) {
            mutex_unlock(&phy_inst_info->lane_lock[lane]);
            continue;
          }

          /* RX power up */
          aw_err_val = aw_pmd_iso_request_rx_state_change(
              &mss, AW_P0, config.rate, config.width, RX_ACK_TIMEOUT_US);
          if (aw_err_val != AW_ERR_CODE_NONE) {
            mutex_unlock(&phy_inst_info->lane_lock[lane]);
            continue;
          }

          // TX FIR Config
    #ifdef FEATURE_QCOM_AW_TEST_SYS_FS
          if(qcom_aw_phy_get_tx_fir_val(phy_inst_info->phy_inst,
                                        (void*)&txfir_cfg) == false)
    #endif
          {
            txfir_cfg.CM3 = 0;
            txfir_cfg.CM2 = 0;
            txfir_cfg.CM1 = 0;
            txfir_cfg.C0 = 63;
            txfir_cfg.C1 = 0;
            txfir_cfg.main_or_max = 1;
          }

          aw_pmd_txfir_config_set(&mss, &txfir_cfg, 1);

          if ((config.rate == 2) || (config.rate == 3)) {
             aw_pmd_enable_pam4_mode(&mss, 1);
             aw_pmd_rx_pam4_precoder_enable_set(&mss, 1, 0);
             aw_pmd_tx_pam4_precoder_enable_set(&mss, 1, 0);
             aw_pmd_tx_pam4_precoder_override_set(&mss, 1);
          }

          // RX Equalization - Check aw_eq_type_e enum
          aw_pmd_rx_equalize(&mss, AW_EQ_FULL_DIR, RX_LINKEVAL_FULL_TIMEOUT_US);

          aw_pmd_rx_background_adapt_enable_set(&mss, 1);
        }

        cdr_lock_status = aw_pmd_rx_check_cdr_lock(&mss, RX_CDR_TIMEOUT_US);
        if(cdr_lock_status == AW_ERR_CODE_NONE){
          qcom_aw_phy_handle_cdr_lock_status(phy_inst_info, lane,
                                             CDR_LOCK_SUCCESS);
          phy_inst_info->lane_params[lane].rx_sig_detect_status = true;
        }
        else{
          qcom_aw_phy_handle_cdr_lock_status(phy_inst_info, lane,
                                             CDR_LOCK_FAILURE);
        }
      }

      mutex_unlock(&phy_inst_info->lane_lock[lane]);
    }

    mutex_unlock(&phy_inst_info->phy_inst_lock);
  }

func_exit:
  if(phy_config_info && wq_params){
    queue_delayed_work(phy_config_info->rx_sig_detect_wq,
                       &wq_params->wq_item, msecs_to_jiffies(1000));
  }

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

int qcom_aw_phy_get_phy_eq_mode(enum mtip_port_type_enum port_type) {
  struct qcom_aw_phy_inst_config *phy_inst_info = NULL;
  enum qcom_aw_phy_instance_enum phy_inst_type = QCOM_AW_PHY_INST_MAX;
  
  /* Get the PHY instance type for the provided port */
  phy_inst_type = qcom_aw_phy_mac_port_to_phy_inst(port_type);

  phy_inst_info = qcom_aw_phy_get_inst_config(phy_inst_type);
  if(phy_inst_info == NULL)
  {
    return -1;
  }
  return phy_inst_info->phy_eq_mode;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_handle_an_restart

* Description: Restarts AN state machine after induced delay timer.
------------------------------------------------------------------- */
void qcom_aw_phy_handle_an_restart(struct work_struct *work){
  struct delayed_work *delayed_work_item = to_delayed_work(work);
  struct qcom_aw_phy_work_q_params *wq_params =
     container_of(delayed_work_item, struct qcom_aw_phy_work_q_params, wq_item);
  enum qcom_aw_phy_instance_enum phy_inst;
  enum eth_phy_iface_phy_lane_num_enum lane_num;
  struct qcom_aw_phy_config *phy_config_info = NULL;
  struct qcom_aw_phy_inst_config *phy_inst_info = NULL;
  mss_access_t mss = {.phy_offset = 0, .lane_offset = 0};

  if(!wq_params){
    QCOM_AW_PHY_LOG_ERR("Invalid work queue structure!");
    return;
  }

  QCOM_AW_PHY_LOG_DBG("AN restart for PHY %d lane %d",
                      wq_params->phy_inst, wq_params->lane_num);

  phy_inst = wq_params->phy_inst;
  lane_num = wq_params->lane_num;

  if (!QCOM_AW_PHY_INST_VALID(phy_inst) || !QCOM_AW_PHY_LANE_VALID(lane_num)){
    QCOM_AW_PHY_LOG_ERR("Invalid PHY instance/lane. AN restart failed.");
    goto func_exit;
  }

  phy_config_info = qcom_aw_phy_get_config_info();
  if (!phy_config_info) {
    goto func_exit;
  }

  /* Get the PHY instance info for the passed instance type */
  phy_inst_info = &phy_config_info->phy_inst_config_info[phy_inst];
  if (phy_inst_info->valid == false) {
    goto func_exit;
  }

  mutex_lock(&phy_inst_info->phy_inst_lock);

  /* Setup PHY offset */
  mss.phy_offset = phy_inst_info->base_addr;

  mutex_lock(&phy_inst_info->lane_lock[lane_num]);

  // Skip AN restart if PHY lane was brought down before this processing
  if(phy_inst_info->lane_params[lane_num].lane_bring_up_status == false){
    mutex_unlock(&phy_inst_info->lane_lock[lane_num]);
    mutex_unlock(&phy_inst_info->phy_inst_lock);
    goto func_exit;
  }

  // Skip AN restart if PCS link is already up
  if(phy_inst_info->lane_params[lane_num].link_status == true){
    mutex_unlock(&phy_inst_info->lane_lock[lane_num]);
    mutex_unlock(&phy_inst_info->phy_inst_lock);
    goto func_exit;
  }

  /* Set the lane offset */
  pmd_set_lane(&mss, lane_num);

  pmd_write_field(&mss, ETH_AN_CTRL_REG1_ADDR,
                  ETH_AN_CTRL_REG1_AN_MR_RESTART_NEGOTIATION_MASK,
                  ETH_AN_CTRL_REG1_AN_MR_RESTART_NEGOTIATION_OFFSET, 1);
  pmd_write_field(&mss, ETH_AN_CTRL_REG1_ADDR,
                  ETH_AN_CTRL_REG1_AN_MR_RESTART_NEGOTIATION_MASK,
                  ETH_AN_CTRL_REG1_AN_MR_RESTART_NEGOTIATION_OFFSET, 0);

  mutex_unlock(&phy_inst_info->lane_lock[lane_num]);
  mutex_unlock(&phy_inst_info->phy_inst_lock);

func_exit:
  kfree(wq_params);
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
    .eth_phy_iface_initiate_an = qcom_aw_phy_initiate_an,
    .eth_phy_iface_reset_phy_sm = qcom_aw_phy_reset_phy_sm,
    .eth_phy_iface_set_tx_compliance = qcom_aw_phy_set_tx_compliance,
    .eth_phy_iface_get_phy_phy_eq_mode = qcom_aw_phy_get_phy_eq_mode,
};

EXPORT_SYMBOL(qcom_aw_phy_driver_iface_ops);
