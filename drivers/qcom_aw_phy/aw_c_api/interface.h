/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/**
  @file interface.h
  @brief Interface header between AW C API and QCOM AW PHY driver.
*/

#include <linux/types.h>
#ifndef __interface
#define __interface

void sv_print(char *str);
void sv_write_csr(void __iomem *addr, uint32_t wdata);
void sv_read_csr(void __iomem *addr, uint32_t *rdata);
void sv_write_field(void __iomem *addr, uint32_t wdata,
                          uint32_t offset, uint32_t mask);
void sv_delay_us(int x);

#endif // __interface
