/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/**
  @file qcom_aw_phy_utils.c
  @brief Utility  file for AW PHY driver.

  This file contains definitions for utility API/structure/macros
  for AW PHY driver.
*/

#include <linux/types.h>

#include "qcom_aw_phy_utils.h"
#include "aw_c_api/aw_alphacore.h"
#include "aw_c_api/aw_driver_sim.h"
#include "aw_c_api/interface.h"


/*-------------------------------------------------------------------
* Function Definitions
------------------------------------------------------------------- */

/*-------------------------------------------------------------------
* qcom_aw_phy_mac_port_to_phy_inst

* @port_type: Port Info(FH/C2C/Debug)

* Description: This function takes MAC port type as an input and translates it
               into PHY instance type for the same port.
------------------------------------------------------------------- */
enum qcom_aw_phy_instance_enum
qcom_aw_phy_mac_port_to_phy_inst(enum mtip_port_type_enum port_type) {
  switch (port_type) {
  case MTIP_PORT_TYPE_FH_0:
    return QCOM_AW_PHY_INST_FH0;

  case MTIP_PORT_TYPE_FH_1:
    return QCOM_AW_PHY_INST_FH1;

  case MTIP_PORT_TYPE_FH_2:
    return QCOM_AW_PHY_INST_FH2;

  case MTIP_PORT_TYPE_L2:
    return QCOM_AW_PHY_INST_L2;

  case MTIP_PORT_TYPE_DEBUG:
    return QCOM_AW_PHY_INST_DEBUG;

  default:
    break;
  }

  return QCOM_AW_PHY_INST_MAX;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_inst_to_mac_port

* @port_type: PHY instance(FH/C2C/Debug)
* @lane_num: PHY lane number

* Description: This function takes PHY instance type and lane number as an input
               and translates it into MAC port type.
------------------------------------------------------------------- */
enum mtip_port_type_enum
qcom_aw_phy_inst_to_mac_port(enum qcom_aw_phy_instance_enum phy_inst) {
  switch (phy_inst) {
  case QCOM_AW_PHY_INST_FH0:
    return MTIP_PORT_TYPE_FH_0;

  case QCOM_AW_PHY_INST_FH1:
    return MTIP_PORT_TYPE_FH_1;

  case QCOM_AW_PHY_INST_FH2:
    return MTIP_PORT_TYPE_FH_2;

  case QCOM_AW_PHY_INST_L2:
    return MTIP_PORT_TYPE_L2;

  case QCOM_AW_PHY_INST_DEBUG:
    return MTIP_PORT_TYPE_DEBUG;

  default:
    break;
  }

  return MTIP_PORT_TYPE_MAX;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_get_lane_speed_config

* @lane_speed: Lane speed(10/25/50/100G)

* Description: This function takes the lane speed as an input and returns the
   corresponding rate, width, LTCS clause and modulation technique that needs
   to be applied on the lane.
------------------------------------------------------------------- */
void qcom_aw_phy_get_lane_speed_config(
    enum eth_phy_iface_phy_lane_speed_enum lane_speed,
    struct qcom_aw_phy_lane_speed_config *config) {
  memset(config, 0, sizeof(struct qcom_aw_phy_lane_speed_config));

  switch (lane_speed) {
  case PHY_LANE_SPEED_10G:
    config->rate = 0;
    config->width = 4;
    config->clause = 1;
    config->synce_cmux_clk_rate = 322265625;
    config->synce_div_clk_src_rate = 40283203;
    config->mod_tech = QCOM_AW_PHY_MOD_TECH_NRZ;
    break;

  case PHY_LANE_SPEED_25G:
    config->rate = 1;
    config->width = 4;
    config->clause = 2;
    config->synce_cmux_clk_rate = 805664064;
    config->synce_div_clk_src_rate = 50354004;
    config->mod_tech = QCOM_AW_PHY_MOD_TECH_NRZ;
    break;

  case PHY_LANE_SPEED_50G:
    config->rate = 2;
    config->width = 6;
    config->clause = 3;
    config->synce_cmux_clk_rate = 830078125;
    config->synce_div_clk_src_rate = 51879883;
    config->mod_tech = QCOM_AW_PHY_MOD_TECH_PAM4;
    break;

  case PHY_LANE_SPEED_100G:
    config->rate = 3;
    config->width = 7;
    config->clause = 4;
    config->synce_cmux_clk_rate = 830078125;
    config->synce_div_clk_src_rate = 51879883;
    config->mod_tech = QCOM_AW_PHY_MOD_TECH_PAM4;
    break;

  default:
    break;
  }

  return;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_strtok

* Description: This function takes a string as input, splits it based
  on delimiter character and returns the next position post split.
------------------------------------------------------------------- */
char *qcom_aw_phy_strtok(char *in_string, const char ch, char **out_string){

  char *temp;

  if (in_string == NULL)
    in_string = *out_string;

  if (*in_string == '\0'){
    return NULL;
  }

  temp  = in_string;
  while(*temp != ch){
    if(*temp == '\n' || *temp == '\0'){
      *temp = '\0';
      return in_string;
    }

    temp++;
  }

  *temp = '\0';
  *out_string = temp + 1;

  return in_string;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_load_hexfile

* @mss: PHY offset
* @fileName: File location to be read

* Description: This function does the firmware loading from hex file
------------------------------------------------------------------- */
int qcom_aw_phy_load_hexfile(mss_access_t *mss, char *fileName) {
  uint32_t value = 0; 
  uint32_t addr = 0;
  struct file *file;
  char line[18], *token;
  loff_t pos = 0;
  int len = 0;
  char *save_ptr = NULL;

  file = filp_open(fileName, O_RDONLY, 0);
  if (IS_ERR(file)) {
    QCOM_AW_PHY_LOG_ERR("File open failed !");
    return -1;
  }

  do {
    len = kernel_read(file, line, sizeof(line), &pos);
    if (len <= 0) {
      QCOM_AW_PHY_LOG_ERR("Nothing to read, bailing out !");
      break;
    }

    token = qcom_aw_phy_strtok(line, ',', &save_ptr);
    if(token != NULL) {
      sscanf(token, "%x", &addr); 
    }
    token = qcom_aw_phy_strtok(NULL, ',', &save_ptr);
    if(token != NULL) {
      sscanf(token, "%x", &value); 
    }

    pmd_write_addr(mss, addr, value);
  } while (len >= 0);

  filp_close(file, NULL);

  return 0;
}

/*-------------------------------------------------------------------
* qcom_aw_phy_dump_registers

* Description: This function dumps the PHY registers
------------------------------------------------------------------- */
void qcom_aw_phy_dump_registers(void) {
  struct file *file;
  char *filePath = "/tmp/phy_registers.txt";
  char line[25];
  loff_t pos = 0;
  uint32_t value, addr, len;
  struct qcom_aw_phy_config *phy_config_info = NULL;
  enum qcom_aw_phy_instance_enum phy_inst_type = QCOM_AW_PHY_INST_FH0;
  struct qcom_aw_phy_inst_config *phy_inst_info = NULL;
  mss_access_t mss = {.phy_offset = 0, .lane_offset = 0};
  enum eth_phy_iface_phy_lane_num_enum lane = PHY_LANE_0;
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;
  void __iomem *temp_addr;

  QCOM_AW_PHY_LOG_INFO("qcom_aw_phy_dump_registers!");

  phy_config_info = qcom_aw_phy_get_config_info();
  if (!phy_config_info) {
    local_err_val = LOCAL_ERROR_0;
    goto func_exit;
  }

  file = filp_open(filePath, O_CREAT | O_WRONLY | O_APPEND | O_LARGEFILE, 0666);
  if (IS_ERR(file)) {
    local_err_val = LOCAL_ERROR_1;
    goto func_exit;
  }

  kernel_write(file, "Offset,Value\n", sizeof("Offset,Value"), &pos);

  for (phy_inst_type = QCOM_AW_PHY_INST_FH0;
       phy_inst_type < QCOM_AW_PHY_INST_MAX; phy_inst_type++) {
    phy_inst_info = &phy_config_info->phy_inst_config_info[phy_inst_type];

    if (phy_inst_info && phy_inst_info->valid) {

      QCOM_AW_PHY_LOG_ERR("Capturing PHY wrapper for %d", phy_inst_type);

      memset(line, 0, sizeof(line));
      len = snprintf(line, sizeof(line), "\nPHY wrapper %d\n", phy_inst_type);
      kernel_write(file, line, len, &pos);

      temp_addr = phy_inst_info->wrapper_base_addr +
                  QCOM_AW_PHY_WRAPPER_PHY_ICTL_CMN_CFG_OFFSET;
      sv_read_csr(temp_addr, &value);
      memset(line, 0, sizeof(line));
      len = snprintf(line, sizeof(line), "0x%x,0x%x\n",
                     QCOM_AW_PHY_WRAPPER_PHY_ICTL_CMN_CFG_OFFSET, value);
      kernel_write(file, line, len, &pos);
    }
  }

  for (phy_inst_type = QCOM_AW_PHY_INST_FH0;
       phy_inst_type < QCOM_AW_PHY_INST_FH1;
       phy_inst_type++) { // change it for all PHYs later
    phy_inst_info = &phy_config_info->phy_inst_config_info[phy_inst_type];

    QCOM_AW_PHY_LOG_INFO("Capturing PHY %d", phy_inst_type);

    memset(line, 0, sizeof(line));
    len = snprintf(line, sizeof(line), "\nPHY %d\n", phy_inst_type);
    kernel_write(file, line, len, &pos);

    if (phy_inst_info && phy_inst_info->valid) {

      mss.phy_offset = phy_inst_info->base_addr;
      mss.lane_offset = 0;
      lane = PHY_LANE_0;

      QCOM_AW_PHY_LOG_INFO("Capturing common registers");

      // Common Registers
      addr = AFE_CMN_ATEST_ADDR;
      while (addr < SWITCHCLK_DBE_CMN_ADDR) {

        pmd_read_addr(&mss, addr, &value);

        memset(line, 0, sizeof(line));
        len = snprintf(line, sizeof(line), "0x%x,0x%x\n", addr, value);
        kernel_write(file, line, len, &pos);

        addr += 0x4;
      }

      while (lane < PHY_LANE_MAX) {

        memset(line, 0, sizeof(line));
        len = snprintf(line, sizeof(line), "\nLane %d\n", lane);
        kernel_write(file, line, len, &pos);

        pmd_set_lane(&mss, lane);

        QCOM_AW_PHY_LOG_INFO("Capturing lane %d", lane);

        // Lane RX registers
        addr = AFE_OCTERM_RX_ADDR;
        while (addr < SWITCHCLK_DBE_RX_ADDR) {

          pmd_read_addr(&mss, addr, &value);

          memset(line, 0, sizeof(line));
          len = snprintf(line, sizeof(line), "0x%x,0x%x\n", addr, value);
          kernel_write(file, line, len, &pos);

          addr += 0x4;
        }

        // Lane TX registers
        addr = AFE_OCTERM_TX_ADDR;
        while (addr < TXMFSM_STATE_ADDR) {

          pmd_read_addr(&mss, addr, &value);

          memset(line, 0, sizeof(line));
          len = snprintf(line, sizeof(line), "0x%x,0x%x\n", addr, value);
          kernel_write(file, line, len, &pos);

          addr += 0x4;
        }

        // Lane AN/LT registers
        addr = ETH_AN_ADV_ABILITY_REG1_ADDR;
        while (addr < ETH_LT_TXFRAME_EXTRA_ADDR) {

          pmd_read_addr(&mss, addr, &value);

          memset(line, 0, sizeof(line));
          len = snprintf(line, sizeof(line), "0x%x,0x%x\n", addr, value);
          kernel_write(file, line, len, &pos);

          addr += 0x4;
        }

        // Lane DBE registers
        addr = CTL_DBE_PLLCHARZ_ADDR;
        while (addr < LOOPBACK_CNTRL_ADDR) {

          pmd_read_addr(&mss, addr, &value);

          memset(line, 0, sizeof(line));
          len = snprintf(line, sizeof(line), "0x%x,0x%x\n", addr, value);
          kernel_write(file, line, len, &pos);

          addr += 0x4;
        }

        lane++;
      }

#if 0
			QCOM_AW_PHY_LOG_ERR("Capturing Braodcast register set 1 ");
			mss.lane_offset = 0;

			// Broadcast registers -set 1
			addr = 0x40000000;
			while(addr <= 0x4000212C){

				pmd_read_addr(&mss, addr, &value);

				memset(line, 0, sizeof(line));
				len = snprintf(line, sizeof(line),
				               "0x%x,0x%x\n", addr, value);
				kernel_write(file, line, len, &pos);

				addr += 0x4;
			}

			QCOM_AW_PHY_LOG_ERR("Capturing Braodcast register set 1 ");

			// Broadcast registers -set 2
			addr = 0x80000000;
			while(addr <= 0x800042A0){

				pmd_read_addr(&mss, addr, &value);

				memset(line, 0, sizeof(line));
				len = snprintf(line, sizeof(line),
				               "0x%x,0x%x\n", addr, value);
				kernel_write(file, line, len, &pos);

				addr += 0x4;
			}
#endif
    }
  }

  filp_close(file, NULL);

func_exit:
  QCOM_AW_PHY_LOG_ERR("%s: local error %d", __func__, local_err_val);

  return;
}
