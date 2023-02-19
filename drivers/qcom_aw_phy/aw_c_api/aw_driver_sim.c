// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) Alphawave IP Inc. All rights reserved.
 */

#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/delay.h>
#include "aw_driver_sim.h"
#include "aw_alphacore_csr_defines.h"
#include "qcom_aw_phy_main.h"
#include "qcom_aw_phy_utils.h"
#include "interface.h"

#if defined(DO_NOT_PRINT)
#define printf(...)                                                            \
  do {                                                                         \
  } while (0)
#endif

int serdes_init(mss_access_t *mss, uint32_t lane_offset,
                void __iomem *phy_offset) {
  mss->lane_offset = lane_offset;
  mss->phy_offset = phy_offset;
  return 0;
}

void write_csr(void __iomem *addr, uint32_t wdata) {
  sv_write_csr(addr, wdata);
}

void read_csr(void __iomem *addr, uint32_t *rdata) { sv_read_csr(addr, rdata); }

int delay_us(int x) {
  sv_delay_us(x);
  return 0;
}

int c_test_api_write(void) {
  uint32_t wval = 0x7FF;
  write_csr(0x00000000, wval);
  QCOM_AW_PHY_LOG_DBG("[aw_driver_sim.c] Wrote value: %d\n", wval);
  return 0;
}

int c_test_api_read(void) {
  uint32_t rddata;
  read_csr(0x00000000, &rddata);
  QCOM_AW_PHY_LOG_DBG("[aw_driver_sim.c] Read Value:  %d\n", rddata);
  return 0;
}

static uint32_t addr_translate(uint32_t addr){
	uint32_t translated_addr = 0;

	translated_addr = addr & 0xFFFF;
	translated_addr |= ((addr & 0xFE000000) >> 9);

	return translated_addr;
}

int pmd_set_lane(mss_access_t *mss, uint32_t lane) {

  if (lane == 99) {
    mss->lane_offset = addr_translate(LANE_BROADCAST);
    return 0;
  } else if (lane > LANE_MAX) {
    QCOM_AW_PHY_LOG_DBG(
        "[pmd_set_lane]: Lane number %d does not exist in the design\n", lane);
    return 1;
  } else {
    mss->lane_offset = addr_translate((lane) * LANE0_OFFSET);
    return 0;
  }
}

int pmd_get_lane(mss_access_t *mss, uint32_t *lane) {
  uint32_t lane_temp;

  if (mss->lane_offset == addr_translate(LANE_BROADCAST)) {
    *lane = 99;
  } else {
    lane_temp = mss->lane_offset / addr_translate(LANE0_OFFSET);
    if (lane_temp > LANE_MAX) {
      QCOM_AW_PHY_LOG_DBG("[pmd_get_lane]: Lane number %d does not exist \n",
             lane_temp);
      return 1;
    } else {
      *lane = lane_temp;
    }
  }
  return 0;
}

int pmd_write_addr(mss_access_t *mss, uint32_t addr, uint32_t value) {
  void __iomem *final_addr;
  uint32_t trans_addr, addr_offset;

  if (addr < LANE0_OFFSET || addr >= LANE_BROADCAST) {
    trans_addr = addr_translate(addr);
    addr_offset = trans_addr;
    final_addr = trans_addr + mss->phy_offset;
  } else {
    trans_addr = addr_translate(addr);
    addr_offset = trans_addr  + mss->lane_offset;
    final_addr = trans_addr + mss->lane_offset + mss->phy_offset;
  }

  if(addr < LANE_BROADCAST){
    QCOM_AW_PHY_LOG_DBG("[pmd_write_addr]: Writing addr offset: 0x%x, value: %d\n",
                        addr_offset, value);
  }

  write_csr(final_addr, value);

  return 0;
}

int pmd_read_addr(mss_access_t *mss, uint32_t addr, uint32_t *rdval) {
  void __iomem *final_addr;
  uint32_t trans_addr, addr_offset;

  if (addr < LANE0_OFFSET || addr >= LANE_BROADCAST) {
    trans_addr = addr_translate(addr);
    addr_offset = trans_addr;
    final_addr = trans_addr + mss->phy_offset;
  } else {
    trans_addr = addr_translate(addr);
    addr_offset = trans_addr + mss->lane_offset;
    final_addr = trans_addr + mss->lane_offset + mss->phy_offset;
  }

  if (addr >= LANE_BROADCAST && addr < SRAM_OFFSET) {
    QCOM_AW_PHY_LOG_DBG("[pmd_read_addr]: Cannot read register while mss.lane_offset has "
           "lane broadcast set.\n");
    return 1;
  }

  read_csr(final_addr, rdval);
  QCOM_AW_PHY_LOG_DBG("[pmd_read_addr]: Reading addr offset: 0x%x, val = %d\n",
                      addr_offset, *rdval);

  return 0;
}

int pmd_write_field(mss_access_t *mss, uint32_t addr, uint32_t fld_mask,
                    uint32_t fld_offset, uint32_t wval) {
  void __iomem *final_addr;
  uint32_t reg_read;
  uint32_t trans_addr, addr_offset;

  if (addr < LANE0_OFFSET) {
    trans_addr = addr_translate(addr);
    addr_offset = trans_addr;
    final_addr = trans_addr + mss->phy_offset;
  } else if (mss->lane_offset == LANE_BROADCAST) {
    trans_addr = addr_translate(addr);
    addr_offset = trans_addr + mss->lane_offset - addr_translate(LANE0_OFFSET);
    final_addr = trans_addr + mss->lane_offset - addr_translate(LANE0_OFFSET) + mss->phy_offset;
  } else {
    trans_addr = addr_translate(addr);
    addr_offset = trans_addr + mss->lane_offset;
    final_addr = trans_addr + mss->lane_offset + mss->phy_offset;
  }

  QCOM_AW_PHY_LOG_DBG("[pmd_write_field]: Writing addr offset: 0x%x, value: %d\n",
                      addr_offset, wval);
  wval = wval << fld_offset;
  read_csr(final_addr, &reg_read);
  wval = (wval & fld_mask) | (reg_read & ~fld_mask);
  write_csr(final_addr, wval);

  return 0;
}

int pmd_read_field(mss_access_t *mss, uint32_t addr, uint32_t fld_mask,
                   uint32_t fld_offset, uint32_t *rdval) {
  void __iomem *final_addr;
  uint32_t rddata;
  uint32_t fld_val;
  uint32_t trans_addr, addr_offset;

  if (addr < LANE0_OFFSET) {
    trans_addr = addr_translate(addr);
    addr_offset = trans_addr;
    final_addr = trans_addr + mss->phy_offset;
  } else {
    trans_addr = addr_translate(addr);
    addr_offset = trans_addr + mss->lane_offset;
    final_addr = trans_addr + mss->lane_offset + mss->phy_offset;
  }

  if (addr >= LANE_BROADCAST) {
    QCOM_AW_PHY_LOG_ERR(
        "[pmd_read_field]: Cannot read register while mss.lane_offset "
        "has lane broadcast set.\n");
    return 1;
  }

  QCOM_AW_PHY_LOG_DBG("[pmd_read_field]: Reading addr offset: 0x%08X\n", addr_offset);
  read_csr(final_addr, &rddata);
  QCOM_AW_PHY_LOG_DBG("[pmd_read_field]: Read value: 0x%08X\n", rddata);
  fld_val = ((rddata & fld_mask) >> fld_offset);
  *rdval = fld_val;

  return 0;
}

int pmd_read_check_field(mss_access_t *mss, uint32_t addr, uint32_t fld_mask,
                         uint32_t fld_offset, aw_rd_opcode_t rd_opcode,
                         uint32_t *rdval, uint32_t rdcheck_val1,
                         uint32_t rdcheck_val2) {
  void __iomem *final_addr;
  uint32_t rddata;
  uint32_t fld_val;
  uint32_t trans_addr, addr_offset;

  if (addr < LANE0_OFFSET) {
    trans_addr = addr_translate(addr);
    addr_offset = trans_addr;
    final_addr = trans_addr + mss->phy_offset;
  } else {
    trans_addr = addr_translate(addr);
    addr_offset = trans_addr + mss->lane_offset;
    final_addr = trans_addr + mss->lane_offset + mss->phy_offset;
  }

  if (addr >= LANE_BROADCAST) {
    QCOM_AW_PHY_LOG_DBG("[pmd_read_check_field]: Cannot read register while mss."
                   "lane_offset has lane broadcast set.\n");
    return 1;
  }

  QCOM_AW_PHY_LOG_DBG("[pmd_read_check_field]: Reading addr offset: 0x%08X\n", addr_offset);
  read_csr(final_addr, &rddata);
  QCOM_AW_PHY_LOG_DBG("[pmd_read_check_field]: Read value: 0x%08X\n", rddata);
  fld_val = ((rddata & fld_mask) >> fld_offset);
  *rdval = fld_val;

  if (rd_opcode == RD_EQ) {
    if (fld_val == rdcheck_val1) {
      QCOM_AW_PHY_LOG_DBG("[pmd_read_check_field]: Register check passed. "
                     "Expected value = 0x%X. Field value = 0x%X\n",
             rdcheck_val1, fld_val);
      return 0;
    } else {
      QCOM_AW_PHY_LOG_ERR("[pmd_read_check_field]: ERROR. Register check failed. "
                     "Expected value = 0x%X. Field value = 0x%X\n",
             rdcheck_val1, fld_val);
      return -1;
    }
  } else if (rd_opcode == RD_GT) {
    if (fld_val > rdcheck_val1) {
      QCOM_AW_PHY_LOG_DBG("[pmd_read_check_field]: Register check passed. "
                     "Expected value > 0x%X. Field value = 0x%X\n",
             rdcheck_val1, fld_val);
      return 0;
    } else {
      QCOM_AW_PHY_LOG_ERR("[pmd_read_check_field]: ERROR. Register check failed. "
                     "Expected > 0x%X. Field value = 0x%X\n",
             rdcheck_val1, fld_val);
      return -1;
    }
  } else if (rd_opcode == RD_GTE) {
    if (fld_val >= rdcheck_val1) {
      QCOM_AW_PHY_LOG_DBG("[pmd_read_check_field]: Register check passed. "
                     "Expected value >= 0x%X. Field value = 0x%X\n",
             rdcheck_val1, fld_val);
      return 0;
    } else {
      QCOM_AW_PHY_LOG_ERR("[pmd_read_check_field]: ERROR. Register check failed. "
                     "Expected value >= 0x%X. Field value = 0x%X\n",
             rdcheck_val1, fld_val);
      return -1;
    }
  } else if (rd_opcode == RD_LT) {
    if (fld_val < rdcheck_val1) {
      QCOM_AW_PHY_LOG_DBG("[pmd_read_check_field]: Register check passed. Expected "
                     "value < 0x%X. Field value = 0x%X\n",
             rdcheck_val1, fld_val);
      return 0;
    } else {
      QCOM_AW_PHY_LOG_ERR("[pmd_read_check_field]: ERROR. Register check failed. "
                     "Expected < 0x%X. Field value = 0x%X\n",
             rdcheck_val1, fld_val);
      return -1;
    }
  } else if (rd_opcode == RD_LTE) {
    if (fld_val <= rdcheck_val1) {
      QCOM_AW_PHY_LOG_DBG("[pmd_read_check_field]: Register check passed. Expected "
                     "value <= 0x%X. Field value = 0x%X\n",
             rdcheck_val1, fld_val);
      return 0;
    } else {
      QCOM_AW_PHY_LOG_ERR("[pmd_read_check_field]: ERROR. Register check failed. "
                     "Expected <= 0x%X. Field value = 0x%X\n",
             rdcheck_val1, fld_val);
      return -1;
    }
  } else if (rd_opcode == RD_RANGE) {
    if (fld_val >= rdcheck_val1 && fld_val <= rdcheck_val2) {
      QCOM_AW_PHY_LOG_DBG("[pmd_read_check_field]: Register check passed. Expected "
                     "range = 0x%X -> 0x%X. Field value = 0x%X\n",
             rdcheck_val1, rdcheck_val2, fld_val);
      return 0;
    } else {
      QCOM_AW_PHY_LOG_ERR("[pmd_read_check_field]: ERROR. Register check failed. "
                     "Expected range = 0x%X -> 0x%X. Field value = 0x%X\n",
             rdcheck_val1, rdcheck_val2, fld_val);
      return -1;
    }

  } else {
    QCOM_AW_PHY_LOG_ERR("[pmd_read_check_field]: ERROR. Invalid read opcode");
    return -1;
  }
}

int pmd_poll_field(mss_access_t *mss, uint32_t addr, uint32_t fld_mask,
                   uint32_t fld_offset, uint32_t poll_val,
                   uint32_t timeout_us) {
  void __iomem *final_addr;
  uint32_t rddata = 0;
  uint32_t fld_val = 0;
  uint32_t i = 0;
  uint32_t trans_addr, addr_offset;

  if (addr < LANE0_OFFSET) {
    trans_addr = addr_translate(addr);
    addr_offset = trans_addr;
    final_addr = trans_addr + mss->phy_offset;
  } else {
    trans_addr = addr_translate(addr);
    addr_offset = trans_addr + mss->lane_offset;
    final_addr = trans_addr + mss->lane_offset + mss->phy_offset;
  }

  if (addr >= LANE_BROADCAST) {
    QCOM_AW_PHY_LOG_ERR("[pmd_poll_field]: Cannot read register while "
                   "mss.lane_offset has lane broadcast set.\n");
    return 1;
  }

  QCOM_AW_PHY_LOG_DBG("[pmd_poll_field]: Using SIM version\n");
  QCOM_AW_PHY_LOG_DBG("[pmd_poll_field]: Polling addr offset: 0x%08X\n", addr_offset);

#ifdef FEATURE_QCOM_AW_RUMI_SW
  return 0;
#endif

  while (i < timeout_us) {
    i++;
    udelay(1);
    read_csr(final_addr, &rddata);
    fld_val = ((rddata & fld_mask) >> fld_offset);
    if (fld_val == poll_val) {
      break;
    }
  }
  if (fld_val == poll_val) {
    QCOM_AW_PHY_LOG_DBG("[pmd_poll_field]: Polling successful after %d us\n", i);
    return 0;
  } else {
    QCOM_AW_PHY_LOG_DBG("[pmd_poll_field]: Polling timed out after %d us\n",
                   timeout_us);
    return -1;
  }
}

int pmd_ate_vec_comment(char comment[]) {
  QCOM_AW_PHY_LOG_DBG("[pmd_ate_vec_comment]: %s\n", comment);
  return 0;
}
