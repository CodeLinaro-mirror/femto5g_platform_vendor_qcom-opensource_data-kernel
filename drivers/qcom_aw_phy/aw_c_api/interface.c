/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/**
  @file interface.c
  @brief Interface between AW C API and QCOM AW PHY driver.
*/

#include <linux/io.h>
#include <linux/delay.h>
#include "qcom_aw_phy_main.h"
#include "interface.h"

void sv_print(char *str) { return; }

void sv_write_csr(void __iomem *addr, uint32_t wdata) {
#ifdef FEATURE_QCOM_AW_RUMI_SW
  return;
#endif

  iowrite32(wdata, addr);
  return;
}

void sv_read_csr(void __iomem *addr, uint32_t *rdata) {
#ifdef FEATURE_QCOM_AW_RUMI_SW
  return;
#endif

  *rdata = ioread32(addr);
  return;
}

void sv_write_field(void __iomem *addr, uint32_t wdata,
                          uint32_t offset, uint32_t mask) {
  uint32_t read_val;

#ifdef FEATURE_QCOM_AW_RUMI_SW
  return;
#endif

  read_val = ioread32(addr);

  wdata = wdata << offset;
  wdata = (wdata & mask) | (read_val & ~mask);

  iowrite32(wdata, addr);

  return;
}

void sv_delay_us(int x) {
#ifdef FEATURE_QCOM_AW_RUMI_SW
  return;
#endif

  udelay(x);
  return;
}
