/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/**
  @file qcom_aw_phy_main.c
  @brief Main file for the AW PHY driver.

  This file contains AW PHY driver probe handling.
*/

#include <linux/clk.h>
#include <linux/interrupt.h>
#include <linux/of.h>
#include <linux/phylink.h>
#include <linux/string.h>
#include <linux/reset.h>

#include "qcom_aw_phy_main.h"
#include "qcom_aw_phy_mtip_if.h"
#include "qcom_aw_phy_synce.h"
#include "qcom_aw_phy_utils.h"
#include "qcom_aw_phy_gnl.h"
#include "qcom_aw_phy_prbs.h"
#include "aw_c_api/aw_alphacore.h"
#include "aw_c_api/aw_alphacore_ip_defines.h"
#include "aw_c_api/aw_driver_sim.h"
#include "aw_c_api/interface.h"

/* PHY Driver Name */
#define QCOM_AW_PHY_DRV_MAIN_NAME "qcom-aw-phy-main"
#define QCOM_AW_PHY_DRV_INST_NAME "qcom-aw-phy-inst"

#define REF_CLK_MODE_SILABS       0
#define REF_CLK_MODE_OSCILLATOR   1

/* Module parameters */
static enum qcom_aw_phy_loopback_mode_enum qcom_aw_phy_loopback_mode;

/* Global to store the device level PHY information */
static struct qcom_aw_phy_config qcom_aw_phy_config_info;

/* Global to cache CXO clock reference */
struct clk *cxo_clk = NULL;

int qcom_aw_phy_ref_clk_mode = 0;
module_param(qcom_aw_phy_ref_clk_mode, int,
                  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(qcom_aw_phy_ref_clk_mode, "PHY REF clock mode");

int qcom_aw_phy_toggle_polarity = 0;
module_param(qcom_aw_phy_toggle_polarity, int,
             S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(qcom_aw_phy_toggle_polarity,
                 "Toggle PHY TX/RX polarity");

/*-------------------------------------------------------------------
* Function Definitions
------------------------------------------------------------------- */

/*-------------------------------------------------------------------
* qcom_aw_phy_get_config_info

* Description: This function returns the cache for PHY config information.
------------------------------------------------------------------- */
struct qcom_aw_phy_config *qcom_aw_phy_get_config_info(void) {
  return &qcom_aw_phy_config_info;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_get_loopback_mode

* Description: This function returns the loopback config for AW PHY.
------------------------------------------------------------------- */
enum qcom_aw_phy_loopback_mode_enum qcom_aw_phy_get_loopback_mode(void) {
  return qcom_aw_phy_loopback_mode;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_set_loopback_mode

* Description: This function sets the loopback config for AW PHY.
------------------------------------------------------------------- */
void qcom_aw_phy_set_loopback_mode(enum qcom_aw_phy_loopback_mode_enum mode) {
  qcom_aw_phy_loopback_mode = mode;
}

/*------------------------------------------------------------------------
* qcom_aw_phy_get_polarity_flag

* Description: This function returns the polarity toggle flag for AW PHY.
----------------------------------------------------------------------- */
int qcom_aw_phy_get_polarity_flag(void) {
  return qcom_aw_phy_toggle_polarity;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_interrupt_handler

* @irq: Interrupt number
* @devptr : User data(struct aw_phy_inst_config)

* Description: This function does the formware loading, DT parsing and
   PHY structure initializations.
------------------------------------------------------------------- */
static irqreturn_t qcom_aw_phy_interrupt_handler(int irq, void *devptr) {
  struct qcom_aw_phy_inst_config *phy_inst_info = NULL;
  u32 intr_status = 0;
  u32 intr_error = 0;
  u32 temp_bmask = 0;
  u32 i = 0;
  u32 clear = 0;
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;
  int ret_val = IRQ_HANDLED;
  struct qcom_aw_phy_work_q_params *wq_params = NULL;

  // check if this an interrupt that needs to be handled
  for (i = QCOM_AW_PHY_INST_FH0; i < QCOM_AW_PHY_INST_MAX; i++)
  {
    if (devptr == (void *)&qcom_aw_phy_config_info.phy_inst_config_info[i])
    {
      phy_inst_info = (struct qcom_aw_phy_inst_config *)devptr;
      break;
    }
  }

  if (!phy_inst_info) {
    ret_val = IRQ_NONE;
    local_err_val = LOCAL_ERROR_0;
    goto func_exit;
  }

  // Read interrupt status register
  intr_status = ioread32(phy_inst_info->wrapper_base_addr +
                         QCOM_AW_PHY_WRAPPER_INT_STATUS_REG_OFFSET);

  // Read interrupt error register
  intr_error = ioread32(phy_inst_info->wrapper_base_addr +
                        QCOM_AW_PHY_WRAPPER_INT_ERROR_REG_OFFSET);

  QCOM_AW_PHY_LOG_INFO(
      "Interrupt received for PHY instance %d, status %x, error %x",
      phy_inst_info->phy_inst, intr_status, intr_error);

  // Handle status interrupt
  for (i = QCOM_AW_PHY_INT_STATUS_BIT_MIN; i < QCOM_AW_PHY_INT_STATUS_BIT_MAX;
       i++) {
    temp_bmask = intr_status & (1 << i);
    if (temp_bmask) {
      switch (i) {

      case QCOM_AW_PHY_RX_SIGNAL_DETECT_LANE_0:
      case QCOM_AW_PHY_RX_SIGNAL_DETECT_LANE_1:
      case QCOM_AW_PHY_RX_SIGNAL_DETECT_LANE_2:
      case QCOM_AW_PHY_RX_SIGNAL_DETECT_LANE_3:
        QCOM_AW_PHY_LOG_ERR("RX signal detect interrupt received for lane %d",
                            i - QCOM_AW_PHY_RX_SIGNAL_DETECT_LANE_0);
        wq_params = kmalloc(sizeof(struct qcom_aw_phy_work_q_params),
                            GFP_ATOMIC);
        if(!wq_params)
          QCOM_AW_PHY_LOG_ERR("Malloc failed!");
        else{
          INIT_DELAYED_WORK(&wq_params->wq_item,
                            qcom_aw_phy_retry_lane_bring_up);
          wq_params->phy_inst = phy_inst_info->phy_inst;
          wq_params->lane_num = i;
          wq_params->user_data = (void*)true;
          queue_delayed_work(qcom_aw_phy_config_info.wq, &wq_params->wq_item, 0);
        }
        clear |= (1<<i);
        break;

      case QCOM_AW_PHY_AN_DONE_LANE_0:
      case QCOM_AW_PHY_AN_DONE_LANE_1:
      case QCOM_AW_PHY_AN_DONE_LANE_2:
      case QCOM_AW_PHY_AN_DONE_LANE_3:
        wq_params = kmalloc(sizeof(struct qcom_aw_phy_work_q_params),
                            GFP_ATOMIC);
        if(!wq_params)
          QCOM_AW_PHY_LOG_ERR("Malloc failed!");
        else{
          INIT_DELAYED_WORK(&wq_params->wq_item,
                            qcom_aw_phy_handle_an_complete);
          wq_params->phy_inst = phy_inst_info->phy_inst;
          wq_params->lane_num = i - QCOM_AW_PHY_AN_DONE_LANE_0;
          queue_delayed_work(qcom_aw_phy_config_info.wq, &wq_params->wq_item, 0);
        }
        clear |= (1<<i);
        break;

      case QCOM_AW_PHY_AN_LINK_GOOD_LANE_0:
      case QCOM_AW_PHY_AN_LINK_GOOD_LANE_1:
      case QCOM_AW_PHY_AN_LINK_GOOD_LANE_2:
      case QCOM_AW_PHY_AN_LINK_GOOD_LANE_3:
        // NO-OP, just to monitor the link state transition
        clear |= (1<<i);
        break;

      case QCOM_AW_PHY_SNR_VALID_LANE_0:
      case QCOM_AW_PHY_SNR_VALID_LANE_1:
      case QCOM_AW_PHY_SNR_VALID_LANE_2:
      case QCOM_AW_PHY_SNR_VALID_LANE_3:
        wq_params = kmalloc(sizeof(struct qcom_aw_phy_work_q_params),
                            GFP_ATOMIC);
        if(!wq_params)
          QCOM_AW_PHY_LOG_ERR("Malloc failed!");
        else{
          INIT_DELAYED_WORK(&wq_params->wq_item,
                            qcom_aw_phy_synce_handle_snr_valid_change);
          wq_params->phy_inst = phy_inst_info->phy_inst;
          wq_params->lane_num = i - QCOM_AW_PHY_SNR_VALID_LANE_0;
          wq_params->user_data = (void*)true;
          queue_delayed_work(qcom_aw_phy_config_info.wq, &wq_params->wq_item, 0);
        }
        clear |= (1<<i);
        break;

      default:
        break;
      }
    }
  }

  // clear status interrupt
  iowrite32(clear, phy_inst_info->wrapper_base_addr +
                             QCOM_AW_PHY_WRAPPER_INT_STATUS_CLR_REG_OFFSET);

  clear = 0;

  // Handle error interrupt
  for (i = QCOM_AW_PHY_INT_ERROR_BIT_MIN; i < QCOM_AW_PHY_INT_ERROR_BIT_MAX;
       i++) {
    temp_bmask = intr_error & (1 << i);
    if (temp_bmask) {
      switch (i) {
      case QCOM_AW_PHY_SNR_VALID_ERR_LANE_0:
      case QCOM_AW_PHY_SNR_VALID_ERR_LANE_1:
      case QCOM_AW_PHY_SNR_VALID_ERR_LANE_2:
      case QCOM_AW_PHY_SNR_VALID_ERR_LANE_3:
        wq_params = kmalloc(sizeof(struct qcom_aw_phy_work_q_params),
                            GFP_ATOMIC);
        if(!wq_params)
          QCOM_AW_PHY_LOG_ERR("Malloc failed!");
        else{
          INIT_DELAYED_WORK(&wq_params->wq_item,
                            qcom_aw_phy_synce_handle_snr_valid_change);
          wq_params->phy_inst = phy_inst_info->phy_inst;
          wq_params->lane_num = i - QCOM_AW_PHY_SNR_VALID_ERR_LANE_0;
          wq_params->user_data = (void*)false;
          queue_delayed_work(qcom_aw_phy_config_info.wq, &wq_params->wq_item, 0);
        }
        clear |= (1<<i);
        break;

      default:
        break;
      }
    }
  }

  // clear error interrupt
  iowrite32(clear, phy_inst_info->wrapper_base_addr +
                            QCOM_AW_PHY_WRAPPER_INT_ERROR_CLR_REG_OFFSET);

func_exit:
  QCOM_AW_PHY_LOG_INFO(
      "QCOM_aw_phy_interrupt_handler returns %d, local_err = %d", ret_val,
      local_err_val);

  return ret_val;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_enable_interrupt

* @phy_inst_info: PHY instance pointer

* Description: This function enables the interrupts PHY driver is
               interested in.
------------------------------------------------------------------- */
void qcom_aw_phy_enable_interrupt(
    struct qcom_aw_phy_inst_config *phy_inst_info) {
  u32 temp_bmask = 0;
  u32 i = 0;
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;

  if (!phy_inst_info) {
    local_err_val = LOCAL_ERROR_0;
    goto func_exit;
  }

  // Enable status interrupt
  for (i = QCOM_AW_PHY_INT_STATUS_BIT_MIN; i < QCOM_AW_PHY_INT_STATUS_BIT_MAX;
       i++) {
    switch (i) {
    case QCOM_AW_PHY_RX_SIGNAL_DETECT_LANE_0:
    case QCOM_AW_PHY_RX_SIGNAL_DETECT_LANE_1:
    case QCOM_AW_PHY_RX_SIGNAL_DETECT_LANE_2:
    case QCOM_AW_PHY_RX_SIGNAL_DETECT_LANE_3:
    case QCOM_AW_PHY_AN_DONE_LANE_0:
    case QCOM_AW_PHY_AN_DONE_LANE_1:
    case QCOM_AW_PHY_AN_DONE_LANE_2:
    case QCOM_AW_PHY_AN_DONE_LANE_3:
    case QCOM_AW_PHY_AN_LINK_GOOD_LANE_0:
    case QCOM_AW_PHY_AN_LINK_GOOD_LANE_1:
    case QCOM_AW_PHY_AN_LINK_GOOD_LANE_2:
    case QCOM_AW_PHY_AN_LINK_GOOD_LANE_3:
    case QCOM_AW_PHY_SNR_VALID_LANE_0:
    case QCOM_AW_PHY_SNR_VALID_LANE_1:
    case QCOM_AW_PHY_SNR_VALID_LANE_2:
    case QCOM_AW_PHY_SNR_VALID_LANE_3:
      temp_bmask |= (1 << i);
      break;

    default:
      break;
    }
  }

#ifndef FEATURE_QCOM_AW_RUMI_SW
  iowrite32(temp_bmask, phy_inst_info->wrapper_base_addr +
                            QCOM_AW_PHY_WRAPPER_INT_STATUS_EN_REG_OFFSET);
#endif

  QCOM_AW_PHY_LOG_INFO(
      "Status interrupt enabled for PHY instance %d, bitmask %x",
      phy_inst_info->phy_inst, temp_bmask);

  // Enable error interrupt
  temp_bmask = 0;
  for (i = QCOM_AW_PHY_INT_ERROR_BIT_MIN; i < QCOM_AW_PHY_INT_ERROR_BIT_MAX;
       i++) {
    switch (i) {
    case QCOM_AW_PHY_SNR_VALID_ERR_LANE_0:
    case QCOM_AW_PHY_SNR_VALID_ERR_LANE_1:
    case QCOM_AW_PHY_SNR_VALID_ERR_LANE_2:
    case QCOM_AW_PHY_SNR_VALID_ERR_LANE_3:
      temp_bmask |= (1 << i);
      break;

    default:
      break;
    }
  }

#ifndef FEATURE_QCOM_AW_RUMI_SW
  iowrite32(temp_bmask, phy_inst_info->wrapper_base_addr +
                            QCOM_AW_PHY_WRAPPER_INT_ERROR_EN_REG_OFFSET);
#endif

  QCOM_AW_PHY_LOG_INFO(
      "Error interrupt enabled for PHY instance %d, bitmask %x",
      phy_inst_info->phy_inst, temp_bmask);

func_exit:
  QCOM_AW_PHY_LOG_INFO("qcom_aw_phy_enable_interrupt local_err = %d",
                       local_err_val);

  return;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_get_clock

* @dev: platform device's dev pointer
  @id: Clock name

* Description: This function gets the PHY clocks.
------------------------------------------------------------------- */
static struct clk* qcom_aw_phy_get_clock(struct device *dev, const char *id) {
  struct clk *clk = NULL;

  /* Fetch the clock */
  clk = devm_clk_get(dev, id);
  if (IS_ERR_OR_NULL(clk)) {
    QCOM_AW_PHY_LOG_ERR("Failed to get %s, error %d", id, PTR_ERR(clk));
    return NULL;
  }

  return clk;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_enable_clock

* @dev: platform device's dev pointer
  @id: Clock name

* Description: This function fetches and enables PHY clocks..
------------------------------------------------------------------- */
static void qcom_aw_phy_enable_clock(struct device *dev, const char *id) {
  struct clk *clk = NULL;

  /* Fetch the clock */
  clk = devm_clk_get(dev, id);
  if (IS_ERR_OR_NULL(clk)) {
    QCOM_AW_PHY_LOG_ERR("Failed to get %s, error %d", id, PTR_ERR(clk));
    return;
  }

  /* Prepare/enable the clock */
  if (clk_prepare_enable(clk)) {
    QCOM_AW_PHY_LOG_ERR("Failed to prepare/enable %s", id);
    return;
  }

  return;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_setup_clocks

* @dev: platform device's dev pointer

* Description: This function sets up PHY clocks.
------------------------------------------------------------------- */
static void qcom_aw_phy_setup_clocks(struct device *dev) {

#ifdef FEATURE_QCOM_AW_RUMI_SW
  return;
#endif /* FEATURE_QCOM_AW_RUMI_SW */

  QCOM_AW_PHY_LOG_INFO("qcom_aw_phy_setup_clocks");

  // GCC Clocks
  qcom_aw_phy_enable_clock(dev, "GCC_ETH_100G_C2C_HM_APB_CLK");
  qcom_aw_phy_enable_clock(dev, "GCC_ETH_100G_FH_HM_APB_0_CLK");
  qcom_aw_phy_enable_clock(dev, "GCC_ETH_100G_FH_HM_APB_1_CLK");
  qcom_aw_phy_enable_clock(dev, "GCC_ETH_100G_FH_HM_APB_2_CLK");
  qcom_aw_phy_enable_clock(dev, "GCC_ETH_DBG_C2C_HM_APB_CLK");
  qcom_aw_phy_enable_clock(dev, "GCC_ETH_DBG_SNOC_AXI_CLK");

  // FH0 PHY Clocks
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY0_LANE0_RX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY0_LANE0_TX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY0_LANE1_RX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY0_LANE1_TX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY0_LANE2_RX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY0_LANE2_TX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY0_LANE3_RX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY0_LANE3_TX_CLK");

  // FH1 PHY Clocks
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY1_LANE0_RX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY1_LANE0_TX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY1_LANE1_RX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY1_LANE1_TX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY1_LANE2_RX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY1_LANE2_TX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY1_LANE3_RX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY1_LANE3_TX_CLK");

  // FH2 PHY Clocks
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY2_LANE0_RX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY2_LANE0_TX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY2_LANE1_RX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY2_LANE1_TX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY2_LANE2_RX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY2_LANE2_TX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY2_LANE3_RX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY2_LANE3_TX_CLK");

  // L2 PHY Clocks
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY3_LANE0_RX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY3_LANE0_TX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY3_LANE1_RX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY3_LANE1_TX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY3_LANE2_RX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY3_LANE2_TX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY3_LANE3_RX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY3_LANE3_TX_CLK");

  // Debug PHY Clocks
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY4_LANE0_RX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY4_LANE0_TX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY4_LANE1_RX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY4_LANE1_TX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY4_LANE2_RX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY4_LANE2_TX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY4_LANE3_RX_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_PHY4_LANE3_TX_CLK");

  // SRAM clocks
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_ETH_PHY_0_OCK_SRAM_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_ETH_PHY_1_OCK_SRAM_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_ETH_PHY_2_OCK_SRAM_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_ETH_PHY_3_OCK_SRAM_CLK");
  qcom_aw_phy_enable_clock(dev, "ECPRI_CC_ETH_PHY_4_OCK_SRAM_CLK");

  return;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_setup_synce_clocks

* @dev: platform device's dev pointer

* Description: This function sets up PHY SyncE clocks.
------------------------------------------------------------------- */
static void qcom_aw_phy_setup_synce_clocks(struct device *dev) {

  QCOM_AW_PHY_LOG_INFO("qcom_aw_phy_setup_synce_clocks");

  qcom_aw_phy_config_info.synce_cmux_clk_src =
         qcom_aw_phy_get_clock(dev, "ECPRI_CC_EMAC_SYNCE_CMUX_CLK_SRC");

  qcom_aw_phy_config_info.synce_cmux_clk =
             qcom_aw_phy_get_clock(dev, "ECPRI_CC_EMAC_SYNCE_CMUX_CLK");

  qcom_aw_phy_config_info.synce_div_clk =
          qcom_aw_phy_get_clock(dev, "ECPRI_CC_EMAC_SYNCE_DIV_CLK_SRC");

  qcom_aw_phy_config_info.synce_phy_lane_clk[FH0_LANE_0] =
         qcom_aw_phy_get_clock(dev, "ECPRI_CC_EMAC_SYNCE_PHY0_CLK_SRC");
  qcom_aw_phy_config_info.synce_phy_lane_clk[FH0_LANE_1] =
         qcom_aw_phy_get_clock(dev, "ECPRI_CC_EMAC_SYNCE_PHY1_CLK_SRC");
  qcom_aw_phy_config_info.synce_phy_lane_clk[FH0_LANE_2] =
         qcom_aw_phy_get_clock(dev, "ECPRI_CC_EMAC_SYNCE_PHY2_CLK_SRC");
  qcom_aw_phy_config_info.synce_phy_lane_clk[FH0_LANE_3] =
         qcom_aw_phy_get_clock(dev, "ECPRI_CC_EMAC_SYNCE_PHY3_CLK_SRC");
  qcom_aw_phy_config_info.synce_phy_lane_clk[FH1_LANE_0] =
         qcom_aw_phy_get_clock(dev, "ECPRI_CC_EMAC_SYNCE_PHY4_CLK_SRC");
  qcom_aw_phy_config_info.synce_phy_lane_clk[FH1_LANE_1] =
         qcom_aw_phy_get_clock(dev, "ECPRI_CC_EMAC_SYNCE_PHY5_CLK_SRC");
  qcom_aw_phy_config_info.synce_phy_lane_clk[FH1_LANE_2] =
         qcom_aw_phy_get_clock(dev, "ECPRI_CC_EMAC_SYNCE_PHY6_CLK_SRC");
  qcom_aw_phy_config_info.synce_phy_lane_clk[FH1_LANE_3] =
         qcom_aw_phy_get_clock(dev, "ECPRI_CC_EMAC_SYNCE_PHY7_CLK_SRC");
  qcom_aw_phy_config_info.synce_phy_lane_clk[FH2_LANE_0] =
         qcom_aw_phy_get_clock(dev, "ECPRI_CC_EMAC_SYNCE_PHY8_CLK_SRC");
  qcom_aw_phy_config_info.synce_phy_lane_clk[FH2_LANE_1] =
         qcom_aw_phy_get_clock(dev, "ECPRI_CC_EMAC_SYNCE_PHY9_CLK_SRC");
  qcom_aw_phy_config_info.synce_phy_lane_clk[FH2_LANE_2] =
         qcom_aw_phy_get_clock(dev, "ECPRI_CC_EMAC_SYNCE_PHY10_CLK_SRC");
  qcom_aw_phy_config_info.synce_phy_lane_clk[FH2_LANE_3] =
         qcom_aw_phy_get_clock(dev, "ECPRI_CC_EMAC_SYNCE_PHY11_CLK_SRC");
  qcom_aw_phy_config_info.synce_phy_lane_clk[L2_LANE_0] =
         qcom_aw_phy_get_clock(dev, "ECPRI_CC_EMAC_SYNCE_PHY12_CLK_SRC");
  qcom_aw_phy_config_info.synce_phy_lane_clk[L2_LANE_1] =
         qcom_aw_phy_get_clock(dev, "ECPRI_CC_EMAC_SYNCE_PHY13_CLK_SRC");
  qcom_aw_phy_config_info.synce_phy_lane_clk[L2_LANE_2] =
         qcom_aw_phy_get_clock(dev, "ECPRI_CC_EMAC_SYNCE_PHY14_CLK_SRC");
  qcom_aw_phy_config_info.synce_phy_lane_clk[L2_LANE_3] =
         qcom_aw_phy_get_clock(dev, "ECPRI_CC_EMAC_SYNCE_PHY15_CLK_SRC");

  return;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_enable_ref_clk_propagation

* @phy_inst_info: PHY instance pointer

* Description: This function enables the oscillator REF clock
               propgation from Debug PHY(botton) to FH0 PHY (top).
------------------------------------------------------------------- */
static void qcom_aw_phy_enable_ref_clk_propagation(
    struct qcom_aw_phy_inst_config *phy_inst_info) {
  mss_access_t mss = {.phy_offset = 0, .lane_offset = 0};
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;
  int reg_val = 0;

  if (!phy_inst_info) {
    local_err_val = LOCAL_ERROR_0;
    goto func_exit;
  }

  // Setup PHY offset
  mss.phy_offset = phy_inst_info->base_addr;

  pmd_write_field(&mss, DIG_SOC_CMN_OVRD_ADDR,
                  DIG_SOC_CMN_OVRD_REF_SEL_OVRD_EN_A_MASK,
                  DIG_SOC_CMN_OVRD_REF_SEL_OVRD_EN_A_OFFSET, 1);

  pmd_write_field(&mss, DIG_SOC_CMN_OVRD_ADDR,
                  DIG_SOC_CMN_OVRD_CMN_OVRD_EN_A_MASK,
                  DIG_SOC_CMN_OVRD_CMN_OVRD_EN_A_OFFSET, 1);

  pmd_write_field(&mss, DIG_SOC_CMN_OVRD_ADDR,
                  DIG_SOC_CMN_OVRD_ICTL_REF_LS_ENA_A_MASK,
                  DIG_SOC_CMN_OVRD_ICTL_REF_LS_ENA_A_OFFSET, 1);

  if(qcom_aw_phy_ref_clk_mode == REF_CLK_MODE_OSCILLATOR){
    if (phy_inst_info->phy_inst == QCOM_AW_PHY_INST_DEBUG)
      reg_val = 0x4;
    else
      reg_val = 0x1;
  }
  else{
    if (phy_inst_info->phy_inst == QCOM_AW_PHY_INST_FH0)
      reg_val = 0x4;
    else
      reg_val = 0x3;
  }

  pmd_write_field(&mss, DIG_SOC_CMN_OVRD_ADDR,
                  DIG_SOC_CMN_OVRD_ICTL_LSREF_SELECT_NT_MASK,
                  DIG_SOC_CMN_OVRD_ICTL_LSREF_SELECT_NT_OFFSET, reg_val);

  if(qcom_aw_phy_ref_clk_mode == REF_CLK_MODE_OSCILLATOR){
    if (phy_inst_info->phy_inst == QCOM_AW_PHY_INST_FH0)
      reg_val = 0x0;
    else if (phy_inst_info->phy_inst == QCOM_AW_PHY_INST_DEBUG)
      reg_val = 0x3;
    else
      reg_val = 0x1;

    pmd_write_field(&mss, DIG_SOC_CMN_OVRD_ADDR,
                    DIG_SOC_CMN_OVRD_ICTL_L2R0_LSREF_SELECT_NT_MASK,
                    DIG_SOC_CMN_OVRD_ICTL_L2R0_LSREF_SELECT_NT_OFFSET, reg_val);
  }
  else{
    if (phy_inst_info->phy_inst == QCOM_AW_PHY_INST_FH0)
      reg_val = 0x3;
    else if (phy_inst_info->phy_inst == QCOM_AW_PHY_INST_DEBUG)
      reg_val = 0x0;
    else
      reg_val = 0x1;

    pmd_write_field(&mss, DIG_SOC_CMN_OVRD_ADDR,
                    DIG_SOC_CMN_OVRD_ICTL_R2L0_LSREF_SELECT_NT_MASK,
                    DIG_SOC_CMN_OVRD_ICTL_R2L0_LSREF_SELECT_NT_OFFSET, reg_val);
  }

func_exit:
  QCOM_AW_PHY_LOG_ERR("%s: local error %d", __func__, local_err_val);

  return;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_hw_init

* @pdev: platform device pointer

* Description: This function does the clock setting, firmware
  loading.
------------------------------------------------------------------- */
static void qcom_aw_phy_hw_init() {
  struct qcom_aw_phy_config *phy_config_info = NULL;
  enum qcom_aw_phy_instance_enum phy_inst_type = QCOM_AW_PHY_INST_FH0;
  struct qcom_aw_phy_inst_config *phy_inst_info = NULL;
  mss_access_t mss = {.phy_offset = 0, .lane_offset = 0};
  u32 sram_cfg_val = 2;
  bool phy_input_config = false;
  uint32_t version_raw;
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;
  int ret_val = 0;

  QCOM_AW_PHY_LOG_INFO("qcom_aw_phy_hw_init!");

  /* PHY Inititalization sequence
     First two steps are not handled by PHY driver.
       Power-on-Reset (Pin name - irst_por_ba)
       APB reset (Pin name - irst_apb4_presetn) */

  phy_config_info = qcom_aw_phy_get_config_info();
  if (!phy_config_info) {
    local_err_val = LOCAL_ERROR_0;
    goto func_exit;
  }

  // Reference clock propagation using PHY inputs
  if (phy_input_config) {

    for (phy_inst_type = QCOM_AW_PHY_INST_DEBUG;
         QCOM_AW_PHY_INST_VALID(phy_inst_type); phy_inst_type--) {
      phy_inst_info = &phy_config_info->phy_inst_config_info[phy_inst_type];
      if (phy_inst_info && phy_inst_info->valid) {

        sv_write_field(phy_inst_info->wrapper_base_addr +
                           QCOM_AW_PHY_WRAPPER_PHY_ICTL_CMN_CFG_OFFSET,
                       0x1, ICTL_CMN_CFG_REF_LS_ENA_A_OFFSET,
                       ICTL_CMN_CFG_REF_LS_ENA_A_MASK);
      }
    }

    sv_write_field(phy_config_info->tcsr_base_addr +
                       TCSR_FH0_ICTL_REF_CML_LS_REG_OFFSET,
                   0x0, B2T_0_MUX_SEL_NT_OFFSET, B2T_0_MUX_SEL_NT_MASK);
    sv_write_field(phy_config_info->tcsr_base_addr +
                       TCSR_FH1_ICTL_REF_CML_LS_REG_OFFSET,
                   0x1, B2T_0_MUX_SEL_NT_OFFSET, B2T_0_MUX_SEL_NT_MASK);
    sv_write_field(phy_config_info->tcsr_base_addr +
                       TCSR_FH2_ICTL_REF_CML_LS_REG_OFFSET,
                   0x1, B2T_0_MUX_SEL_NT_OFFSET, B2T_0_MUX_SEL_NT_MASK);
    sv_write_field(phy_config_info->tcsr_base_addr +
                       TCSR_C2C_L2_ICTL_REF_CML_LS_REG_OFFSET,
                   0x1, B2T_0_MUX_SEL_NT_OFFSET, B2T_0_MUX_SEL_NT_MASK);
    sv_write_field(phy_config_info->tcsr_base_addr +
                       TCSR_C2C_DBG_ICTL_REF_CML_LS_REG_OFFSET,
                   0x3, B2T_0_MUX_SEL_NT_OFFSET, B2T_0_MUX_SEL_NT_MASK);

    sv_write_field(phy_config_info->tcsr_base_addr +
                       TCSR_FH0_ICTL_REF_LS_MUX_SEL_REG_OFFSET,
                   0x1, LS_MUX_SEL_NT_OFFSET, LS_MUX_SEL_NT_MASK);
    sv_write_field(phy_config_info->tcsr_base_addr +
                       TCSR_FH1_ICTL_REF_LS_MUX_SEL_REG_OFFSET,
                   0x1, LS_MUX_SEL_NT_OFFSET, LS_MUX_SEL_NT_MASK);
    sv_write_field(phy_config_info->tcsr_base_addr +
                       TCSR_FH2_ICTL_REF_LS_MUX_SEL_REG_OFFSET,
                   0x1, LS_MUX_SEL_NT_OFFSET, LS_MUX_SEL_NT_MASK);
    sv_write_field(phy_config_info->tcsr_base_addr +
                       TCSR_C2C_L2_ICTL_REF_LS_MUX_SEL_REG_OFFSET,
                   0x1, LS_MUX_SEL_NT_OFFSET, LS_MUX_SEL_NT_MASK);
    sv_write_field(phy_config_info->tcsr_base_addr +
                       TCSR_C2C_DBG_ICTL_REF_LS_MUX_SEL_REG_OFFSET,
                   0x4, LS_MUX_SEL_NT_OFFSET, LS_MUX_SEL_NT_MASK);
  }
  // Reference clock propagation using PHY internal registers
  else {

    QCOM_AW_PHY_LOG_INFO("REF clock in mode %d (0-silabs, 1- osc)",
                         qcom_aw_phy_ref_clk_mode);

    for (phy_inst_type = QCOM_AW_PHY_INST_FH0;
         phy_inst_type < QCOM_AW_PHY_INST_MAX; phy_inst_type++) {
      phy_inst_info = &phy_config_info->phy_inst_config_info[phy_inst_type];
      if (phy_inst_info && phy_inst_info->valid) {
        mss.phy_offset = phy_inst_info->base_addr;
        qcom_aw_phy_enable_ref_clk_propagation(phy_inst_info);
      }
    }
  }

  mdelay(500);

  // Disable SyncE ACGC output by setting SyncE MUX to no lane.
  qcom_aw_phy_synce_set_synce_mux(LANE_NONE);

  /* Allocate workqueue */
  phy_config_info->wq = create_singlethread_workqueue("qcom_aw_phy_wq");
  if (!phy_config_info->wq) {
    local_err_val = LOCAL_ERROR_1;
    goto func_exit;
  }

  for (phy_inst_type = QCOM_AW_PHY_INST_FH0;
       phy_inst_type < QCOM_AW_PHY_INST_MAX; phy_inst_type++) {
    phy_inst_info = &phy_config_info->phy_inst_config_info[phy_inst_type];
    if (phy_inst_info && phy_inst_info->valid) {

      mss.phy_offset = phy_inst_info->base_addr;

      pmd_write_field(&mss, RXMFSM_SCRATCH_REG7_ADDR,
                      RXMFSM_SCRATCH_REG7_RXMFSM_SCRATCH7_MASK,
                      RXMFSM_SCRATCH_REG7_RXMFSM_SCRATCH7_OFFSET, 0xFF);

      /* PHY SRAM Configuration */
      aw_pmd_rd_data_pipeline_stages_set(&mss, sram_cfg_val);

      /* Load firmware/hex file*/
      qcom_aw_phy_load_hexfile(
          &mss, "/lib/firmware/qcom_aw_phy/eth_custom_rates_1.hex");

      pmd_read_addr(&mss,0x80000000, &version_raw);
      QCOM_AW_PHY_LOG_INFO("FW loaded : Version MAJOR = %d "
                           "Version MINOR = %d Version PATCH = %d\n",
                           (version_raw >> 16) & 0xFF,
                           (version_raw >> 8) & 0xFF, version_raw & 0xFF);

      // Set digital signal detect
      pmd_write_field(&mss, RX_SIGNAL_DETECT_REG3_ADDR,
                      RX_SIGNAL_DETECT_REG3_VALID_PCS_SEL_NT_MASK,
                      RX_SIGNAL_DETECT_REG3_VALID_PCS_SEL_NT_OFFSET, 1);

#ifndef FEATURE_QCOM_AW_RUMI_SW
      /* Register for PHY status IRQ */
      ret_val = devm_request_irq(
          &phy_inst_info->pdev->dev, phy_inst_info->phy_status_irq,
          (irq_handler_t)qcom_aw_phy_interrupt_handler,
          IRQF_SHARED | IRQF_TRIGGER_RISING, NULL, phy_inst_info);
      if (ret_val) {
        local_err_val = LOCAL_ERROR_2;
        goto func_exit;
      }

      ret_val = enable_irq_wake(phy_inst_info->phy_status_irq);
      if (ret_val) {
        local_err_val = LOCAL_ERROR_3;
        goto func_exit;
      }

      /* Enable the interrupts which PHY driver is interested in */
      qcom_aw_phy_enable_interrupt(phy_inst_info);
#endif
    }
  }

  QCOM_AW_PHY_LOG_INFO("PHY IRQ register done\n");

func_exit:
  QCOM_AW_PHY_LOG_ERR("%s: local error %d", __func__, local_err_val);

  return;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_inst_probe

* @pdev: platform device pointer

* Description: This function does the instance level probe handling.
------------------------------------------------------------------- */
static int qcom_aw_phy_inst_probe(struct platform_device *pdev) {
  struct device_node *np;
  u32 phy_inst_type;
  struct qcom_aw_phy_inst_config *phy_inst_info = NULL;
  struct resource *phy_resource;
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;
  int ret_val = 0;
  struct resource *tcsr_resource;
  struct pinctrl *pinctrl;

  QCOM_AW_PHY_LOG_INFO("QCOM AW PHY driver instance probed for device %s!",
                       pdev->name);

  /* Incrment the PHY instance count */
  qcom_aw_phy_config_info.num_phy_instances++;

  /* DT read */
  np = pdev->dev.of_node;

  /* Get the PHY instance type */
  ret_val =
      of_property_read_u32(pdev->dev.of_node, "phy-inst-type", &phy_inst_type);
  if (!ret_val) {
    QCOM_AW_PHY_LOG_INFO("phy_inst_type = %d, ret: %d", phy_inst_type, ret_val);

    if (phy_inst_type < QCOM_AW_PHY_INST_MAX) {
      phy_inst_info =
          &qcom_aw_phy_config_info.phy_inst_config_info[phy_inst_type];
      phy_inst_info->valid = true;
      phy_inst_info->phy_inst = phy_inst_type;
    } else {
      local_err_val = LOCAL_ERROR_0;
      ret_val = EINVAL;
      goto func_exit;
    }
  } else {
    local_err_val = LOCAL_ERROR_1;
    ret_val = EINVAL;
    goto func_exit;
  }

  if (phy_inst_type == QCOM_AW_PHY_INST_FH0) {

    // Enable regulator
    if(qcom_aw_phy_ref_clk_mode == REF_CLK_MODE_OSCILLATOR){
      if (of_property_read_bool(pdev->dev.of_node, "vdd-supply")) {
        qcom_aw_phy_config_info.ldo16_supply =
                                            devm_regulator_get(&pdev->dev, "vdd");
        if (IS_ERR(qcom_aw_phy_config_info.ldo16_supply)) {
          QCOM_AW_PHY_LOG_ERR("Cannot get <%s>\n", "ld016");
          return PTR_ERR(qcom_aw_phy_config_info.ldo16_supply);
        }

        ret_val = regulator_set_load(qcom_aw_phy_config_info.ldo16_supply, 10000);
        if (ret_val) {
          QCOM_AW_PHY_LOG_ERR("Can not set Regulator Load <%s>\n", "ldo16");
        }

        ret_val = regulator_set_voltage(qcom_aw_phy_config_info.ldo16_supply,
                                        1800000, 1800000);
        if (ret_val) {
          QCOM_AW_PHY_LOG_ERR("Can not set Regulator Voltage enable <%s>\n",
                              "ldo16");
        }

        ret_val = regulator_enable(qcom_aw_phy_config_info.ldo16_supply);
        if (ret_val) {
          QCOM_AW_PHY_LOG_ERR("Can not enable <%s>\n", "ldo16");
          goto func_exit;
        }

        QCOM_AW_PHY_LOG_INFO("Enabled <%s>\n", "ldo16");
      }

      pinctrl = devm_pinctrl_get_select_default(&pdev->dev);
      if (IS_ERR(pinctrl))
        QCOM_AW_PHY_LOG_ERR("No default pinctrl found\n");
    }

    // Read TCSR base address and apply clamp register setting
    tcsr_resource = platform_get_resource_byname(pdev, IORESOURCE_MEM, "tcsr");
    if (!tcsr_resource) {
      local_err_val = LOCAL_ERROR_2;
      goto func_exit;
    }

    qcom_aw_phy_config_info.tcsr_base_addr =
        devm_ioremap_resource(&pdev->dev, tcsr_resource);

    write_csr(qcom_aw_phy_config_info.tcsr_base_addr +
                  TCSR_ETH_CLAMP_EN_REG_OFFSET,
              0x0);

    // Fetch the ACGC reset control handle
    qcom_aw_phy_config_info.acgc_reset_ctrl =
                        devm_reset_control_get(&pdev->dev, "synce_acgc_reset");
    if (IS_ERR(qcom_aw_phy_config_info.acgc_reset_ctrl)) {
      local_err_val = LOCAL_ERROR_3;
      goto func_exit;
    }

    /* Fetch the SyncE clocks */
    qcom_aw_phy_setup_synce_clocks(&pdev->dev);

    /* Enable PHY clocks */
    qcom_aw_phy_setup_clocks(&pdev->dev);
  }

  /* Read the PHY TOP address */
  phy_resource = platform_get_resource_byname(pdev, IORESOURCE_MEM, "phy-top");
  if (!phy_resource) {
    local_err_val = LOCAL_ERROR_4;
    goto func_exit;
  }

  QCOM_AW_PHY_LOG_INFO("phy-top base: %x, phy-top size = %x",
                       phy_resource->start, resource_size(phy_resource));

#ifndef FEATURE_QCOM_AW_RUMI_SW
  phy_inst_info->base_addr = devm_ioremap_resource(&pdev->dev, phy_resource);
#endif

  /* Read the PHY wrapper address */
  phy_resource =
      platform_get_resource_byname(pdev, IORESOURCE_MEM, "phy-wrapper");
  if (!phy_resource) {
    local_err_val = LOCAL_ERROR_5;
    goto func_exit;
  }

  QCOM_AW_PHY_LOG_INFO("phy-wrapper base: %x, phy-wrapper size = %x",
                       phy_resource->start, resource_size(phy_resource));

#ifndef FEATURE_QCOM_AW_RUMI_SW
  phy_inst_info->wrapper_base_addr =
      devm_ioremap_resource(&pdev->dev, phy_resource);
#endif

  /* Get the PHY equalization mode */
  phy_inst_info->phy_eq_mode =
      QCOM_AW_PHY_MANUAL_EQ_MODE; // Default value for now

  /* Get the IRQ info */
  phy_inst_info->phy_status_irq = platform_get_irq_byname(pdev, "phy-irq");
  if (phy_inst_info->phy_status_irq < 0) {
    local_err_val = LOCAL_ERROR_6;
    ret_val = ENODEV;
#ifndef FEATURE_QCOM_AW_RUMI_SW
    goto func_exit;
#endif
  }

  QCOM_AW_PHY_LOG_INFO("PHY IRQ = %d", phy_inst_info->phy_status_irq);

  /* Store the platform device */
  phy_inst_info->pdev = pdev;

  if (QCOM_AW_PHY_INST_MAX == qcom_aw_phy_config_info.num_phy_instances) {
    QCOM_AW_PHY_LOG_INFO("Max PHY instance probe reached !");

    /* Initialize PHY HW */
    qcom_aw_phy_hw_init();

    /* Indicate PHY driver readiness to MAC */
    qcom_aw_phy_set_drv_ready();
  }

func_exit:
  QCOM_AW_PHY_LOG_ERR("%s: returns %d with local error %d", __func__, ret_val,
                      local_err_val);

  return ret_val;
}

/*-------------------------------------------------------------------
* aw_phy_remove

* @pdev: platform device pointer

* Description: This function resets PHY driver module parameters.
------------------------------------------------------------------- */
static int qcom_aw_phy_inst_remove(struct platform_device *pdev) {

  QCOM_AW_PHY_LOG_INFO("qcom_aw_phy_inst_remove");

  return 0;

}

/* PHY Driver Instance Compatible string */
static const struct of_device_id qcom_aw_phy_inst_match[] = {
    {.compatible = "qcom-aw-phy-inst"}, {}};

MODULE_DEVICE_TABLE(of, qcom_aw_phy_inst_match);

/* Platform Driver Structure - Instance*/
static struct platform_driver qcom_aw_phy_inst_driver = {
    .probe = qcom_aw_phy_inst_probe,
    .remove = qcom_aw_phy_inst_remove,
    .driver =
        {
            .name = QCOM_AW_PHY_DRV_INST_NAME,
            .of_match_table = of_match_ptr(qcom_aw_phy_inst_match),
        },
};

/* Module Init Function */
static int __init qcom_aw_phy_init(void) {
  int ret_val;

  memset(&qcom_aw_phy_config_info, 0, sizeof(struct qcom_aw_phy_config));
  qcom_aw_phy_loopback_mode = QCOM_AW_PHY_NO_LB;

  qcom_aw_phy_mtip_if_init();

  qcom_aw_phy_gnl_init();
  qcom_aw_phy_prbs_gnl_init();

#ifdef FEATURE_QCOM_AW_TEST_SYS_FS
  qcom_aw_phy_setup_sysfs();
#endif

  ret_val = platform_driver_register(&qcom_aw_phy_inst_driver);
  if (ret_val < 0) {
    QCOM_AW_PHY_LOG_INFO(
        "Platform registration failed for PHY instance driver !");
  }

  return 0;
}

/* Module Exit Function */
static void __exit qcom_aw_phy_exit(void) {

  QCOM_AW_PHY_LOG_INFO("qcom_aw_phy_exit");

  if(qcom_aw_phy_config_info.ldo16_supply){
    regulator_disable(qcom_aw_phy_config_info.ldo16_supply);
    qcom_aw_phy_config_info.ldo16_supply = NULL;
  }

  destroy_workqueue(qcom_aw_phy_config_info.wq);

  qcom_aw_phy_gnl_exit();
  qcom_aw_phy_prbs_gnl_exit();

#ifdef FEATURE_QCOM_AW_TEST_SYS_FS
  qcom_aw_phy_del_sysfs();
#endif

  platform_driver_unregister(&qcom_aw_phy_inst_driver);

  return;
}

module_init(qcom_aw_phy_init);
module_exit(qcom_aw_phy_exit);
MODULE_DESCRIPTION("QCOM AW PHY Device Driver");
MODULE_LICENSE("GPL v2");
MODULE_IMPORT_NS(VFS_internal_I_am_really_a_filesystem_and_am_NOT_a_driver);
