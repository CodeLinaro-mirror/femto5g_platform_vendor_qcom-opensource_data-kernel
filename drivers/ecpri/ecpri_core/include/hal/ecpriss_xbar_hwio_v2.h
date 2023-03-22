 /* SPDX-License-Identifier: GPL-2.0-only
  * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
  */

#ifndef __ECPRI_XBAR_HWIO_V2_H__
#define __ECPRI_XBAR_HWIO_V2_H__
/*
===========================================================================
*/
/**
  @file ecpri_xbar_hwio.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
    ECPRI_XBAR.*

  'Include' filters applied: <none>
  'Exclude' filters applied: RESERVED DUMMY 

  Attribute definitions for the HWIO_*_ATTR macros are as follows:
    0x0: Command register
    0x1: Read-Only
    0x2: Write-Only
    0x3: Read/Write
*/
/*
  ===========================================================================

  $Header: $
  $DateTime: $
  $Author: $

  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_XBAR
 *--------------------------------------------------------------------------*/

#define ECPRI_XBAR_REG_BASE_V2  (ECPRI_WRAPPER_BASE      + 0x00420000)
#define ECPRI_XBAR_REG_BASE_PHYS_V2 (ECPRI_WRAPPER_BASE_PHYS + 0x00420000)
#define ECPRI_XBAR_REG_BASE_OFFS_V2 0x00420000

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_XBAR_REGS
 *--------------------------------------------------------------------------*/

#define ECPRI_XBAR_REGS_REG_BASE                                                 (ECPRI_WRAPPER_BASE      + 0x00420000)
#define ECPRI_XBAR_REGS_REG_BASE_PHYS                                            (ECPRI_WRAPPER_BASE_PHYS + 0x00420000)
#define ECPRI_XBAR_REGS_REG_BASE_OFFS                                            0x00420000

#define HWIO_ECPRI_XBAR_CFG_ADDR                                                 (ECPRI_XBAR_REGS_REG_BASE      + 0x00000000)
#define HWIO_ECPRI_XBAR_CFG_PHYS                                                 (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000000)
#define HWIO_ECPRI_XBAR_CFG_OFFS                                                 (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000000)
#define HWIO_ECPRI_XBAR_CFG_RMSK                                                      0x3ff
#define HWIO_ECPRI_XBAR_CFG_ATTR                                                        0x3
#define HWIO_ECPRI_XBAR_CFG_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_CFG_ADDR, HWIO_ECPRI_XBAR_CFG_RMSK)
#define HWIO_ECPRI_XBAR_CFG_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_CFG_ADDR, m)
#define HWIO_ECPRI_XBAR_CFG_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_CFG_ADDR,v)
#define HWIO_ECPRI_XBAR_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_CFG_ADDR,m,v,HWIO_ECPRI_XBAR_CFG_IN)
#define HWIO_ECPRI_XBAR_CFG_AXIS_ARB_FIX_EN_BMSK                                      0x200
#define HWIO_ECPRI_XBAR_CFG_AXIS_ARB_FIX_EN_SHFT                                        0x9
#define HWIO_ECPRI_XBAR_CFG_TPDM_EN_BMSK                                              0x100
#define HWIO_ECPRI_XBAR_CFG_TPDM_EN_SHFT                                                0x8
#define HWIO_ECPRI_XBAR_CFG_XBAR_CNT_CLR_EN_BMSK                                       0x80
#define HWIO_ECPRI_XBAR_CFG_XBAR_CNT_CLR_EN_SHFT                                        0x7
#define HWIO_ECPRI_XBAR_CFG_XBAR_CNT_EN_BMSK                                           0x40
#define HWIO_ECPRI_XBAR_CFG_XBAR_CNT_EN_SHFT                                            0x6
#define HWIO_ECPRI_XBAR_CFG_C2CTX_CNT_EN_BMSK                                          0x20
#define HWIO_ECPRI_XBAR_CFG_C2CTX_CNT_EN_SHFT                                           0x5
#define HWIO_ECPRI_XBAR_CFG_C2CRX_CNT_EN_BMSK                                          0x10
#define HWIO_ECPRI_XBAR_CFG_C2CRX_CNT_EN_SHFT                                           0x4
#define HWIO_ECPRI_XBAR_CFG_OCTX_CNT_EN_BMSK                                            0x8
#define HWIO_ECPRI_XBAR_CFG_OCTX_CNT_EN_SHFT                                            0x3
#define HWIO_ECPRI_XBAR_CFG_OCRX_CNT_EN_BMSK                                            0x4
#define HWIO_ECPRI_XBAR_CFG_OCRX_CNT_EN_SHFT                                            0x2
#define HWIO_ECPRI_XBAR_CFG_FHTX_CNT_EN_BMSK                                            0x2
#define HWIO_ECPRI_XBAR_CFG_FHTX_CNT_EN_SHFT                                            0x1
#define HWIO_ECPRI_XBAR_CFG_FHRX_CNT_EN_BMSK                                            0x1
#define HWIO_ECPRI_XBAR_CFG_FHRX_CNT_EN_SHFT                                            0x0

#define HWIO_ECPRI_XBAR_C2C_IPG_CFG_ADDR                                         (ECPRI_XBAR_REGS_REG_BASE      + 0x00000004)
#define HWIO_ECPRI_XBAR_C2C_IPG_CFG_PHYS                                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000004)
#define HWIO_ECPRI_XBAR_C2C_IPG_CFG_OFFS                                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000004)
#define HWIO_ECPRI_XBAR_C2C_IPG_CFG_RMSK                                         0xffffffff
#define HWIO_ECPRI_XBAR_C2C_IPG_CFG_ATTR                                                0x3
#define HWIO_ECPRI_XBAR_C2C_IPG_CFG_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_IPG_CFG_ADDR, HWIO_ECPRI_XBAR_C2C_IPG_CFG_RMSK)
#define HWIO_ECPRI_XBAR_C2C_IPG_CFG_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_IPG_CFG_ADDR, m)
#define HWIO_ECPRI_XBAR_C2C_IPG_CFG_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_C2C_IPG_CFG_ADDR,v)
#define HWIO_ECPRI_XBAR_C2C_IPG_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_IPG_CFG_ADDR,m,v,HWIO_ECPRI_XBAR_C2C_IPG_CFG_IN)
#define HWIO_ECPRI_XBAR_C2C_IPG_CFG_DMA_EOP_IPG_BMSK                             0xff000000
#define HWIO_ECPRI_XBAR_C2C_IPG_CFG_DMA_EOP_IPG_SHFT                                   0x18
#define HWIO_ECPRI_XBAR_C2C_IPG_CFG_OC_EOP_IPG_BMSK                                0xff0000
#define HWIO_ECPRI_XBAR_C2C_IPG_CFG_OC_EOP_IPG_SHFT                                    0x10
#define HWIO_ECPRI_XBAR_C2C_IPG_CFG_DMA_SOP_IPG_BMSK                                 0xff00
#define HWIO_ECPRI_XBAR_C2C_IPG_CFG_DMA_SOP_IPG_SHFT                                    0x8
#define HWIO_ECPRI_XBAR_C2C_IPG_CFG_OC_SOP_IPG_BMSK                                    0xff
#define HWIO_ECPRI_XBAR_C2C_IPG_CFG_OC_SOP_IPG_SHFT                                     0x0

#define HWIO_ECPRI_XBAR_FH_IPG_CFG_ADDR                                          (ECPRI_XBAR_REGS_REG_BASE      + 0x00000008)
#define HWIO_ECPRI_XBAR_FH_IPG_CFG_PHYS                                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000008)
#define HWIO_ECPRI_XBAR_FH_IPG_CFG_OFFS                                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000008)
#define HWIO_ECPRI_XBAR_FH_IPG_CFG_RMSK                                          0xffffffff
#define HWIO_ECPRI_XBAR_FH_IPG_CFG_ATTR                                                 0x3
#define HWIO_ECPRI_XBAR_FH_IPG_CFG_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_IPG_CFG_ADDR, HWIO_ECPRI_XBAR_FH_IPG_CFG_RMSK)
#define HWIO_ECPRI_XBAR_FH_IPG_CFG_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_IPG_CFG_ADDR, m)
#define HWIO_ECPRI_XBAR_FH_IPG_CFG_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_FH_IPG_CFG_ADDR,v)
#define HWIO_ECPRI_XBAR_FH_IPG_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_IPG_CFG_ADDR,m,v,HWIO_ECPRI_XBAR_FH_IPG_CFG_IN)
#define HWIO_ECPRI_XBAR_FH_IPG_CFG_DMA_EOP_IPG_BMSK                              0xff000000
#define HWIO_ECPRI_XBAR_FH_IPG_CFG_DMA_EOP_IPG_SHFT                                    0x18
#define HWIO_ECPRI_XBAR_FH_IPG_CFG_OC_EOP_IPG_BMSK                                 0xff0000
#define HWIO_ECPRI_XBAR_FH_IPG_CFG_OC_EOP_IPG_SHFT                                     0x10
#define HWIO_ECPRI_XBAR_FH_IPG_CFG_DMA_SOP_IPG_BMSK                                  0xff00
#define HWIO_ECPRI_XBAR_FH_IPG_CFG_DMA_SOP_IPG_SHFT                                     0x8
#define HWIO_ECPRI_XBAR_FH_IPG_CFG_OC_SOP_IPG_BMSK                                     0xff
#define HWIO_ECPRI_XBAR_FH_IPG_CFG_OC_SOP_IPG_SHFT                                      0x0

#define HWIO_ECPRI_XBAR_C2C_CFG_ADDR                                             (ECPRI_XBAR_REGS_REG_BASE      + 0x0000000c)
#define HWIO_ECPRI_XBAR_C2C_CFG_PHYS                                             (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x0000000c)
#define HWIO_ECPRI_XBAR_C2C_CFG_OFFS                                             (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x0000000c)
#define HWIO_ECPRI_XBAR_C2C_CFG_RMSK                                                   0x3f
#define HWIO_ECPRI_XBAR_C2C_CFG_ATTR                                                    0x3
#define HWIO_ECPRI_XBAR_C2C_CFG_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_CFG_ADDR, HWIO_ECPRI_XBAR_C2C_CFG_RMSK)
#define HWIO_ECPRI_XBAR_C2C_CFG_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_CFG_ADDR, m)
#define HWIO_ECPRI_XBAR_C2C_CFG_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_C2C_CFG_ADDR,v)
#define HWIO_ECPRI_XBAR_C2C_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_CFG_ADDR,m,v,HWIO_ECPRI_XBAR_C2C_CFG_IN)
#define HWIO_ECPRI_XBAR_C2C_CFG_DMA_PRIO_BMSK                                          0x30
#define HWIO_ECPRI_XBAR_C2C_CFG_DMA_PRIO_SHFT                                           0x4
#define HWIO_ECPRI_XBAR_C2C_CFG_ORAN_PRIO_BMSK                                          0xc
#define HWIO_ECPRI_XBAR_C2C_CFG_ORAN_PRIO_SHFT                                          0x2
#define HWIO_ECPRI_XBAR_C2C_CFG_FH_PRIO_BMSK                                            0x3
#define HWIO_ECPRI_XBAR_C2C_CFG_FH_PRIO_SHFT                                            0x0

#define HWIO_ECPRI_XBAR_FH_CFG_ADDR                                              (ECPRI_XBAR_REGS_REG_BASE      + 0x00000010)
#define HWIO_ECPRI_XBAR_FH_CFG_PHYS                                              (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000010)
#define HWIO_ECPRI_XBAR_FH_CFG_OFFS                                              (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000010)
#define HWIO_ECPRI_XBAR_FH_CFG_RMSK                                                    0xff
#define HWIO_ECPRI_XBAR_FH_CFG_ATTR                                                     0x3
#define HWIO_ECPRI_XBAR_FH_CFG_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_CFG_ADDR, HWIO_ECPRI_XBAR_FH_CFG_RMSK)
#define HWIO_ECPRI_XBAR_FH_CFG_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_CFG_ADDR, m)
#define HWIO_ECPRI_XBAR_FH_CFG_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_FH_CFG_ADDR,v)
#define HWIO_ECPRI_XBAR_FH_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_CFG_ADDR,m,v,HWIO_ECPRI_XBAR_FH_CFG_IN)
#define HWIO_ECPRI_XBAR_FH_CFG_DMA_PRIO_BMSK                                           0xc0
#define HWIO_ECPRI_XBAR_FH_CFG_DMA_PRIO_SHFT                                            0x6
#define HWIO_ECPRI_XBAR_FH_CFG_UC_PRIO_BMSK                                            0x30
#define HWIO_ECPRI_XBAR_FH_CFG_UC_PRIO_SHFT                                             0x4
#define HWIO_ECPRI_XBAR_FH_CFG_ORAN_PRIO_BMSK                                           0xc
#define HWIO_ECPRI_XBAR_FH_CFG_ORAN_PRIO_SHFT                                           0x2
#define HWIO_ECPRI_XBAR_FH_CFG_C2C_PRIO_BMSK                                            0x3
#define HWIO_ECPRI_XBAR_FH_CFG_C2C_PRIO_SHFT                                            0x0

#define HWIO_ECPRI_XBAR_OC_CFG_ADDR                                              (ECPRI_XBAR_REGS_REG_BASE      + 0x00000014)
#define HWIO_ECPRI_XBAR_OC_CFG_PHYS                                              (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000014)
#define HWIO_ECPRI_XBAR_OC_CFG_OFFS                                              (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000014)
#define HWIO_ECPRI_XBAR_OC_CFG_RMSK                                                 0x3ff7f
#define HWIO_ECPRI_XBAR_OC_CFG_ATTR                                                     0x3
#define HWIO_ECPRI_XBAR_OC_CFG_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_OC_CFG_ADDR, HWIO_ECPRI_XBAR_OC_CFG_RMSK)
#define HWIO_ECPRI_XBAR_OC_CFG_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_OC_CFG_ADDR, m)
#define HWIO_ECPRI_XBAR_OC_CFG_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_OC_CFG_ADDR,v)
#define HWIO_ECPRI_XBAR_OC_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_OC_CFG_ADDR,m,v,HWIO_ECPRI_XBAR_OC_CFG_IN)
#define HWIO_ECPRI_XBAR_OC_CFG_OCRX_EOP_TIMEOUT_BMSK                                0x3ff00
#define HWIO_ECPRI_XBAR_OC_CFG_OCRX_EOP_TIMEOUT_SHFT                                    0x8
#define HWIO_ECPRI_XBAR_OC_CFG_OCRX_ASYNC_THRESHOLD_BMSK                               0x70
#define HWIO_ECPRI_XBAR_OC_CFG_OCRX_ASYNC_THRESHOLD_SHFT                                0x4
#define HWIO_ECPRI_XBAR_OC_CFG_OCTX_OVERFLOW_MODE_BMSK                                  0x8
#define HWIO_ECPRI_XBAR_OC_CFG_OCTX_OVERFLOW_MODE_SHFT                                  0x3
#define HWIO_ECPRI_XBAR_OC_CFG_OCTX_DYNAMIC_PRIO_EN_BMSK                                0x4
#define HWIO_ECPRI_XBAR_OC_CFG_OCTX_DYNAMIC_PRIO_EN_SHFT                                0x2
#define HWIO_ECPRI_XBAR_OC_CFG_OCTX_LEN_CHK_DROP_BMSK                                   0x2
#define HWIO_ECPRI_XBAR_OC_CFG_OCTX_LEN_CHK_DROP_SHFT                                   0x1
#define HWIO_ECPRI_XBAR_OC_CFG_OCTX_LEN_CHK_ENABLE_BMSK                                 0x1
#define HWIO_ECPRI_XBAR_OC_CFG_OCTX_LEN_CHK_ENABLE_SHFT                                 0x0

#define HWIO_ECPRI_XBAR_OC_LOOPBACK_CFG_ADDR                                     (ECPRI_XBAR_REGS_REG_BASE      + 0x00000018)
#define HWIO_ECPRI_XBAR_OC_LOOPBACK_CFG_PHYS                                     (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000018)
#define HWIO_ECPRI_XBAR_OC_LOOPBACK_CFG_OFFS                                     (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000018)
#define HWIO_ECPRI_XBAR_OC_LOOPBACK_CFG_RMSK                                           0xff
#define HWIO_ECPRI_XBAR_OC_LOOPBACK_CFG_ATTR                                            0x3
#define HWIO_ECPRI_XBAR_OC_LOOPBACK_CFG_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_OC_LOOPBACK_CFG_ADDR, HWIO_ECPRI_XBAR_OC_LOOPBACK_CFG_RMSK)
#define HWIO_ECPRI_XBAR_OC_LOOPBACK_CFG_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_OC_LOOPBACK_CFG_ADDR, m)
#define HWIO_ECPRI_XBAR_OC_LOOPBACK_CFG_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_OC_LOOPBACK_CFG_ADDR,v)
#define HWIO_ECPRI_XBAR_OC_LOOPBACK_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_OC_LOOPBACK_CFG_ADDR,m,v,HWIO_ECPRI_XBAR_OC_LOOPBACK_CFG_IN)
#define HWIO_ECPRI_XBAR_OC_LOOPBACK_CFG_OCTX_3_SRC_BMSK                                0xc0
#define HWIO_ECPRI_XBAR_OC_LOOPBACK_CFG_OCTX_3_SRC_SHFT                                 0x6
#define HWIO_ECPRI_XBAR_OC_LOOPBACK_CFG_OCTX_2_SRC_BMSK                                0x30
#define HWIO_ECPRI_XBAR_OC_LOOPBACK_CFG_OCTX_2_SRC_SHFT                                 0x4
#define HWIO_ECPRI_XBAR_OC_LOOPBACK_CFG_OCTX_1_SRC_BMSK                                 0xc
#define HWIO_ECPRI_XBAR_OC_LOOPBACK_CFG_OCTX_1_SRC_SHFT                                 0x2
#define HWIO_ECPRI_XBAR_OC_LOOPBACK_CFG_OCTX_0_SRC_BMSK                                 0x3
#define HWIO_ECPRI_XBAR_OC_LOOPBACK_CFG_OCTX_0_SRC_SHFT                                 0x0

#define HWIO_ECPRI_XBAR_FLUSH_ADDR                                               (ECPRI_XBAR_REGS_REG_BASE      + 0x0000001c)
#define HWIO_ECPRI_XBAR_FLUSH_PHYS                                               (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x0000001c)
#define HWIO_ECPRI_XBAR_FLUSH_OFFS                                               (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x0000001c)
#define HWIO_ECPRI_XBAR_FLUSH_RMSK                                                 0xff3f3f
#define HWIO_ECPRI_XBAR_FLUSH_ATTR                                                      0x3
#define HWIO_ECPRI_XBAR_FLUSH_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_FLUSH_ADDR, HWIO_ECPRI_XBAR_FLUSH_RMSK)
#define HWIO_ECPRI_XBAR_FLUSH_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_FLUSH_ADDR, m)
#define HWIO_ECPRI_XBAR_FLUSH_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_FLUSH_ADDR,v)
#define HWIO_ECPRI_XBAR_FLUSH_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FLUSH_ADDR,m,v,HWIO_ECPRI_XBAR_FLUSH_IN)
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_OC_3_RX_BMSK                                   0x800000
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_OC_3_RX_SHFT                                       0x17
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_OC_3_TX_BMSK                                   0x400000
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_OC_3_TX_SHFT                                       0x16
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_OC_2_RX_BMSK                                   0x200000
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_OC_2_RX_SHFT                                       0x15
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_OC_2_TX_BMSK                                   0x100000
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_OC_2_TX_SHFT                                       0x14
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_OC_1_RX_BMSK                                    0x80000
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_OC_1_RX_SHFT                                       0x13
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_OC_1_TX_BMSK                                    0x40000
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_OC_1_TX_SHFT                                       0x12
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_OC_0_RX_BMSK                                    0x20000
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_OC_0_RX_SHFT                                       0x11
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_OC_0_TX_BMSK                                    0x10000
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_OC_0_TX_SHFT                                       0x10
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_C2C_2_RX_BMSK                                    0x2000
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_C2C_2_RX_SHFT                                       0xd
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_C2C_2_TX_BMSK                                    0x1000
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_C2C_2_TX_SHFT                                       0xc
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_C2C_1_RX_BMSK                                     0x800
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_C2C_1_RX_SHFT                                       0xb
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_C2C_1_TX_BMSK                                     0x400
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_C2C_1_TX_SHFT                                       0xa
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_C2C_0_RX_BMSK                                     0x200
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_C2C_0_RX_SHFT                                       0x9
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_C2C_0_TX_BMSK                                     0x100
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_C2C_0_TX_SHFT                                       0x8
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_FH_2_RX_BMSK                                       0x20
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_FH_2_RX_SHFT                                        0x5
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_FH_2_TX_BMSK                                       0x10
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_FH_2_TX_SHFT                                        0x4
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_FH_1_RX_BMSK                                        0x8
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_FH_1_RX_SHFT                                        0x3
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_FH_1_TX_BMSK                                        0x4
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_FH_1_TX_SHFT                                        0x2
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_FH_0_RX_BMSK                                        0x2
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_FH_0_RX_SHFT                                        0x1
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_FH_0_TX_BMSK                                        0x1
#define HWIO_ECPRI_XBAR_FLUSH_FLUSH_FH_0_TX_SHFT                                        0x0

#define HWIO_ECPRI_XBAR_FH_STATUS_ADDR                                           (ECPRI_XBAR_REGS_REG_BASE      + 0x00000020)
#define HWIO_ECPRI_XBAR_FH_STATUS_PHYS                                           (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000020)
#define HWIO_ECPRI_XBAR_FH_STATUS_OFFS                                           (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000020)
#define HWIO_ECPRI_XBAR_FH_STATUS_RMSK                                                  0x7
#define HWIO_ECPRI_XBAR_FH_STATUS_ATTR                                                  0x1
#define HWIO_ECPRI_XBAR_FH_STATUS_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_STATUS_ADDR, HWIO_ECPRI_XBAR_FH_STATUS_RMSK)
#define HWIO_ECPRI_XBAR_FH_STATUS_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_STATUS_ADDR, m)
#define HWIO_ECPRI_XBAR_FH_STATUS_TX_C2C_OVERFLOW_BMSK                                  0x7
#define HWIO_ECPRI_XBAR_FH_STATUS_TX_C2C_OVERFLOW_SHFT                                  0x0

#define HWIO_ECPRI_XBAR_C2C_STATUS_ADDR                                          (ECPRI_XBAR_REGS_REG_BASE      + 0x00000024)
#define HWIO_ECPRI_XBAR_C2C_STATUS_PHYS                                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000024)
#define HWIO_ECPRI_XBAR_C2C_STATUS_OFFS                                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000024)
#define HWIO_ECPRI_XBAR_C2C_STATUS_RMSK                                                 0x7
#define HWIO_ECPRI_XBAR_C2C_STATUS_ATTR                                                 0x1
#define HWIO_ECPRI_XBAR_C2C_STATUS_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_STATUS_ADDR, HWIO_ECPRI_XBAR_C2C_STATUS_RMSK)
#define HWIO_ECPRI_XBAR_C2C_STATUS_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_STATUS_ADDR, m)
#define HWIO_ECPRI_XBAR_C2C_STATUS_TX_FH_OVERFLOW_BMSK                                  0x7
#define HWIO_ECPRI_XBAR_C2C_STATUS_TX_FH_OVERFLOW_SHFT                                  0x0

#define HWIO_ECPRI_XBAR_OCTX_STATUS_ADDR                                         (ECPRI_XBAR_REGS_REG_BASE      + 0x0000002c)
#define HWIO_ECPRI_XBAR_OCTX_STATUS_PHYS                                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x0000002c)
#define HWIO_ECPRI_XBAR_OCTX_STATUS_OFFS                                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x0000002c)
#define HWIO_ECPRI_XBAR_OCTX_STATUS_RMSK                                            0x3ffff
#define HWIO_ECPRI_XBAR_OCTX_STATUS_ATTR                                                0x1
#define HWIO_ECPRI_XBAR_OCTX_STATUS_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_OCTX_STATUS_ADDR, HWIO_ECPRI_XBAR_OCTX_STATUS_RMSK)
#define HWIO_ECPRI_XBAR_OCTX_STATUS_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_OCTX_STATUS_ADDR, m)
#define HWIO_ECPRI_XBAR_OCTX_STATUS_TX_C2C_LEN_ERR_BMSK                             0x38000
#define HWIO_ECPRI_XBAR_OCTX_STATUS_TX_C2C_LEN_ERR_SHFT                                 0xf
#define HWIO_ECPRI_XBAR_OCTX_STATUS_TX_FH_LEN_ERR_BMSK                               0x7000
#define HWIO_ECPRI_XBAR_OCTX_STATUS_TX_FH_LEN_ERR_SHFT                                  0xc
#define HWIO_ECPRI_XBAR_OCTX_STATUS_TX_C2C_OVERFLOW_BMSK                              0xe00
#define HWIO_ECPRI_XBAR_OCTX_STATUS_TX_C2C_OVERFLOW_SHFT                                0x9
#define HWIO_ECPRI_XBAR_OCTX_STATUS_TX_FH_OVERFLOW_BMSK                               0x1c0
#define HWIO_ECPRI_XBAR_OCTX_STATUS_TX_FH_OVERFLOW_SHFT                                 0x6
#define HWIO_ECPRI_XBAR_OCTX_STATUS_TX_C2C_DROP_BMSK                                   0x38
#define HWIO_ECPRI_XBAR_OCTX_STATUS_TX_C2C_DROP_SHFT                                    0x3
#define HWIO_ECPRI_XBAR_OCTX_STATUS_TX_FH_DROP_BMSK                                     0x7
#define HWIO_ECPRI_XBAR_OCTX_STATUS_TX_FH_DROP_SHFT                                     0x0

#define HWIO_ECPRI_XBAR_LUT_STATUS_ADDR                                          (ECPRI_XBAR_REGS_REG_BASE      + 0x00000030)
#define HWIO_ECPRI_XBAR_LUT_STATUS_PHYS                                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000030)
#define HWIO_ECPRI_XBAR_LUT_STATUS_OFFS                                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000030)
#define HWIO_ECPRI_XBAR_LUT_STATUS_RMSK                                               0x1ff
#define HWIO_ECPRI_XBAR_LUT_STATUS_ATTR                                                 0x1
#define HWIO_ECPRI_XBAR_LUT_STATUS_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_LUT_STATUS_ADDR, HWIO_ECPRI_XBAR_LUT_STATUS_RMSK)
#define HWIO_ECPRI_XBAR_LUT_STATUS_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_LUT_STATUS_ADDR, m)
#define HWIO_ECPRI_XBAR_LUT_STATUS_OCRX_LUT_INIT_DONE_BMSK                            0x1c0
#define HWIO_ECPRI_XBAR_LUT_STATUS_OCRX_LUT_INIT_DONE_SHFT                              0x6
#define HWIO_ECPRI_XBAR_LUT_STATUS_C2CRX_LUT_INIT_DONE_BMSK                            0x38
#define HWIO_ECPRI_XBAR_LUT_STATUS_C2CRX_LUT_INIT_DONE_SHFT                             0x3
#define HWIO_ECPRI_XBAR_LUT_STATUS_FHRX_LUT_INIT_DONE_BMSK                              0x7
#define HWIO_ECPRI_XBAR_LUT_STATUS_FHRX_LUT_INIT_DONE_SHFT                              0x0

#define HWIO_ECPRI_XBAR_OCRX_STATUS_ADDR                                         (ECPRI_XBAR_REGS_REG_BASE      + 0x00000034)
#define HWIO_ECPRI_XBAR_OCRX_STATUS_PHYS                                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000034)
#define HWIO_ECPRI_XBAR_OCRX_STATUS_OFFS                                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000034)
#define HWIO_ECPRI_XBAR_OCRX_STATUS_RMSK                                                0xf
#define HWIO_ECPRI_XBAR_OCRX_STATUS_ATTR                                                0x1
#define HWIO_ECPRI_XBAR_OCRX_STATUS_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_OCRX_STATUS_ADDR, HWIO_ECPRI_XBAR_OCRX_STATUS_RMSK)
#define HWIO_ECPRI_XBAR_OCRX_STATUS_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_OCRX_STATUS_ADDR, m)
#define HWIO_ECPRI_XBAR_OCRX_STATUS_OCRX_EOP_TIMEOUT_BMSK                               0xf
#define HWIO_ECPRI_XBAR_OCRX_STATUS_OCRX_EOP_TIMEOUT_SHFT                               0x0

#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_ADDR                                       (ECPRI_XBAR_REGS_REG_BASE      + 0x00000040)
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_PHYS                                       (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000040)
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_OFFS                                       (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000040)
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_RMSK                                           0x7ffb
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_ATTR                                              0x1
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_FW_IRQ_STATUS_ADDR, HWIO_ECPRI_XBAR_FW_IRQ_STATUS_RMSK)
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_FW_IRQ_STATUS_ADDR, m)
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_OCRX_EOP_TIMEOUT_BMSK                          0x4000
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_OCRX_EOP_TIMEOUT_SHFT                             0xe
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_C2CRX_UNKNOWN_PCID_BMSK                        0x2000
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_C2CRX_UNKNOWN_PCID_SHFT                           0xd
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_FHRX_UNKNOWN_PCID_BMSK                         0x1000
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_FHRX_UNKNOWN_PCID_SHFT                            0xc
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_OCRX_UNKNOWN_PCID_BMSK                          0x800
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_OCRX_UNKNOWN_PCID_SHFT                            0xb
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_FHRX_UC_PKT_DROP_BMSK                           0x400
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_FHRX_UC_PKT_DROP_SHFT                             0xa
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_FHRX_UC_PKT_ERR_BMSK                            0x200
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_FHRX_UC_PKT_ERR_SHFT                              0x9
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_FHRX_UC_OVERFLOW_BMSK                           0x100
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_FHRX_UC_OVERFLOW_SHFT                             0x8
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_FHRX_UC_PKT_PENDING_BMSK                         0x80
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_FHRX_UC_PKT_PENDING_SHFT                          0x7
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_OCTX_C2C_OVERFLOW_BMSK                           0x40
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_OCTX_C2C_OVERFLOW_SHFT                            0x6
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_OCTX_FH_OVERFLOW_BMSK                            0x20
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_OCTX_FH_OVERFLOW_SHFT                             0x5
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_C2CTX_FH_OVERFLOW_BMSK                           0x10
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_C2CTX_FH_OVERFLOW_SHFT                            0x4
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_FHTX_C2C_OVERFLOW_BMSK                            0x8
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_FHTX_C2C_OVERFLOW_SHFT                            0x3
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_OCTX_C2C_LEN_ERR_BMSK                             0x2
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_OCTX_C2C_LEN_ERR_SHFT                             0x1
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_OCTX_FH_LEN_ERR_BMSK                              0x1
#define HWIO_ECPRI_XBAR_FW_IRQ_STATUS_OCTX_FH_LEN_ERR_SHFT                              0x0

#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_ADDR                                         (ECPRI_XBAR_REGS_REG_BASE      + 0x00000044)
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_PHYS                                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000044)
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_OFFS                                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000044)
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_RMSK                                             0x7ffb
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_ATTR                                                0x3
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_FW_IRQ_MASK_ADDR, HWIO_ECPRI_XBAR_FW_IRQ_MASK_RMSK)
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_FW_IRQ_MASK_ADDR, m)
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_FW_IRQ_MASK_ADDR,v)
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FW_IRQ_MASK_ADDR,m,v,HWIO_ECPRI_XBAR_FW_IRQ_MASK_IN)
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_OCRX_EOP_TIMEOUT_BMSK                            0x4000
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_OCRX_EOP_TIMEOUT_SHFT                               0xe
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_C2CRX_UNKNOWN_PCID_BMSK                          0x2000
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_C2CRX_UNKNOWN_PCID_SHFT                             0xd
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_FHRX_UNKNOWN_PCID_BMSK                           0x1000
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_FHRX_UNKNOWN_PCID_SHFT                              0xc
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_OCRX_UNKNOWN_PCID_BMSK                            0x800
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_OCRX_UNKNOWN_PCID_SHFT                              0xb
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_FHRX_UC_PKT_DROP_BMSK                             0x400
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_FHRX_UC_PKT_DROP_SHFT                               0xa
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_FHRX_UC_PKT_ERR_BMSK                              0x200
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_FHRX_UC_PKT_ERR_SHFT                                0x9
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_FHRX_UC_OVERFLOW_BMSK                             0x100
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_FHRX_UC_OVERFLOW_SHFT                               0x8
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_FHRX_UC_PKT_PENDING_BMSK                           0x80
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_FHRX_UC_PKT_PENDING_SHFT                            0x7
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_OCTX_C2C_OVERFLOW_BMSK                             0x40
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_OCTX_C2C_OVERFLOW_SHFT                              0x6
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_OCTX_FH_OVERFLOW_BMSK                              0x20
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_OCTX_FH_OVERFLOW_SHFT                               0x5
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_C2CTX_FH_OVERFLOW_BMSK                             0x10
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_C2CTX_FH_OVERFLOW_SHFT                              0x4
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_FHTX_C2C_OVERFLOW_BMSK                              0x8
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_FHTX_C2C_OVERFLOW_SHFT                              0x3
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_OCTX_C2C_LEN_ERR_BMSK                               0x2
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_OCTX_C2C_LEN_ERR_SHFT                               0x1
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_OCTX_FH_LEN_ERR_BMSK                                0x1
#define HWIO_ECPRI_XBAR_FW_IRQ_MASK_OCTX_FH_LEN_ERR_SHFT                                0x0

#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_ADDR                                          (ECPRI_XBAR_REGS_REG_BASE      + 0x00000048)
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_PHYS                                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000048)
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_OFFS                                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000048)
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_RMSK                                              0x7ffb
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_ATTR                                                 0x2
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_FW_IRQ_CLR_ADDR,v)
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_OCRX_EOP_TIMEOUT_BMSK                             0x4000
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_OCRX_EOP_TIMEOUT_SHFT                                0xe
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_C2CRX_UNKNOWN_PCID_BMSK                           0x2000
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_C2CRX_UNKNOWN_PCID_SHFT                              0xd
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_FHRX_UNKNOWN_PCID_BMSK                            0x1000
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_FHRX_UNKNOWN_PCID_SHFT                               0xc
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_OCRX_UNKNOWN_PCID_BMSK                             0x800
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_OCRX_UNKNOWN_PCID_SHFT                               0xb
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_FHRX_UC_PKT_DROP_BMSK                              0x400
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_FHRX_UC_PKT_DROP_SHFT                                0xa
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_FHRX_UC_PKT_ERR_BMSK                               0x200
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_FHRX_UC_PKT_ERR_SHFT                                 0x9
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_FHRX_UC_OVERFLOW_BMSK                              0x100
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_FHRX_UC_OVERFLOW_SHFT                                0x8
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_FHRX_UC_PKT_PENDING_BMSK                            0x80
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_FHRX_UC_PKT_PENDING_SHFT                             0x7
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_OCTX_C2C_OVERFLOW_BMSK                              0x40
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_OCTX_C2C_OVERFLOW_SHFT                               0x6
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_OCTX_FH_OVERFLOW_BMSK                               0x20
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_OCTX_FH_OVERFLOW_SHFT                                0x5
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_C2CTX_FH_OVERFLOW_BMSK                              0x10
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_C2CTX_FH_OVERFLOW_SHFT                               0x4
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_FHTX_C2C_OVERFLOW_BMSK                               0x8
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_FHTX_C2C_OVERFLOW_SHFT                               0x3
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_OCTX_C2C_LEN_ERR_BMSK                                0x2
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_OCTX_C2C_LEN_ERR_SHFT                                0x1
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_OCTX_FH_LEN_ERR_BMSK                                 0x1
#define HWIO_ECPRI_XBAR_FW_IRQ_CLR_OCTX_FH_LEN_ERR_SHFT                                 0x0

#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_ADDR                                       (ECPRI_XBAR_REGS_REG_BASE      + 0x00000050)
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_PHYS                                       (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000050)
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_OFFS                                       (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000050)
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_RMSK                                           0x7ffb
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_ATTR                                              0x1
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_SW_IRQ_STATUS_ADDR, HWIO_ECPRI_XBAR_SW_IRQ_STATUS_RMSK)
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_SW_IRQ_STATUS_ADDR, m)
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_OCRX_EOP_TIMEOUT_BMSK                          0x4000
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_OCRX_EOP_TIMEOUT_SHFT                             0xe
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_C2CRX_UNKNOWN_PCID_BMSK                        0x2000
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_C2CRX_UNKNOWN_PCID_SHFT                           0xd
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_FHRX_UNKNOWN_PCID_BMSK                         0x1000
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_FHRX_UNKNOWN_PCID_SHFT                            0xc
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_OCRX_UNKNOWN_PCID_BMSK                          0x800
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_OCRX_UNKNOWN_PCID_SHFT                            0xb
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_FHRX_UC_PKT_DROP_BMSK                           0x400
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_FHRX_UC_PKT_DROP_SHFT                             0xa
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_FHRX_UC_PKT_ERR_BMSK                            0x200
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_FHRX_UC_PKT_ERR_SHFT                              0x9
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_FHRX_UC_OVERFLOW_BMSK                           0x100
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_FHRX_UC_OVERFLOW_SHFT                             0x8
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_FHRX_UC_PKT_PENDING_BMSK                         0x80
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_FHRX_UC_PKT_PENDING_SHFT                          0x7
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_OCTX_C2C_OVERFLOW_BMSK                           0x40
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_OCTX_C2C_OVERFLOW_SHFT                            0x6
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_OCTX_FH_OVERFLOW_BMSK                            0x20
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_OCTX_FH_OVERFLOW_SHFT                             0x5
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_C2CTX_FH_OVERFLOW_BMSK                           0x10
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_C2CTX_FH_OVERFLOW_SHFT                            0x4
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_FHTX_C2C_OVERFLOW_BMSK                            0x8
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_FHTX_C2C_OVERFLOW_SHFT                            0x3
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_OCTX_C2C_LEN_ERR_BMSK                             0x2
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_OCTX_C2C_LEN_ERR_SHFT                             0x1
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_OCTX_FH_LEN_ERR_BMSK                              0x1
#define HWIO_ECPRI_XBAR_SW_IRQ_STATUS_OCTX_FH_LEN_ERR_SHFT                              0x0

#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_ADDR                                         (ECPRI_XBAR_REGS_REG_BASE      + 0x00000054)
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_PHYS                                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000054)
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_OFFS                                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000054)
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_RMSK                                             0x7ffb
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_ATTR                                                0x3
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_SW_IRQ_MASK_ADDR, HWIO_ECPRI_XBAR_SW_IRQ_MASK_RMSK)
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_SW_IRQ_MASK_ADDR, m)
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_SW_IRQ_MASK_ADDR,v)
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_SW_IRQ_MASK_ADDR,m,v,HWIO_ECPRI_XBAR_SW_IRQ_MASK_IN)
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_OCRX_EOP_TIMEOUT_BMSK                            0x4000
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_OCRX_EOP_TIMEOUT_SHFT                               0xe
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_C2CRX_UNKNOWN_PCID_BMSK                          0x2000
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_C2CRX_UNKNOWN_PCID_SHFT                             0xd
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_FHRX_UNKNOWN_PCID_BMSK                           0x1000
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_FHRX_UNKNOWN_PCID_SHFT                              0xc
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_OCRX_UNKNOWN_PCID_BMSK                            0x800
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_OCRX_UNKNOWN_PCID_SHFT                              0xb
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_FHRX_UC_PKT_DROP_BMSK                             0x400
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_FHRX_UC_PKT_DROP_SHFT                               0xa
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_FHRX_UC_PKT_ERR_BMSK                              0x200
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_FHRX_UC_PKT_ERR_SHFT                                0x9
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_FHRX_UC_OVERFLOW_BMSK                             0x100
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_FHRX_UC_OVERFLOW_SHFT                               0x8
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_FHRX_UC_PKT_PENDING_BMSK                           0x80
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_FHRX_UC_PKT_PENDING_SHFT                            0x7
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_OCTX_C2C_OVERFLOW_BMSK                             0x40
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_OCTX_C2C_OVERFLOW_SHFT                              0x6
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_OCTX_FH_OVERFLOW_BMSK                              0x20
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_OCTX_FH_OVERFLOW_SHFT                               0x5
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_C2CTX_FH_OVERFLOW_BMSK                             0x10
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_C2CTX_FH_OVERFLOW_SHFT                              0x4
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_FHTX_C2C_OVERFLOW_BMSK                              0x8
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_FHTX_C2C_OVERFLOW_SHFT                              0x3
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_OCTX_C2C_LEN_ERR_BMSK                               0x2
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_OCTX_C2C_LEN_ERR_SHFT                               0x1
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_OCTX_FH_LEN_ERR_BMSK                                0x1
#define HWIO_ECPRI_XBAR_SW_IRQ_MASK_OCTX_FH_LEN_ERR_SHFT                                0x0

#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_ADDR                                          (ECPRI_XBAR_REGS_REG_BASE      + 0x00000058)
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_PHYS                                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000058)
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_OFFS                                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000058)
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_RMSK                                              0x7ffb
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_ATTR                                                 0x2
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_SW_IRQ_CLR_ADDR,v)
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_OCRX_EOP_TIMEOUT_BMSK                             0x4000
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_OCRX_EOP_TIMEOUT_SHFT                                0xe
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_C2CRX_UNKNOWN_PCID_BMSK                           0x2000
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_C2CRX_UNKNOWN_PCID_SHFT                              0xd
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_FHRX_UNKNOWN_PCID_BMSK                            0x1000
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_FHRX_UNKNOWN_PCID_SHFT                               0xc
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_OCRX_UNKNOWN_PCID_BMSK                             0x800
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_OCRX_UNKNOWN_PCID_SHFT                               0xb
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_FHRX_UC_PKT_DROP_BMSK                              0x400
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_FHRX_UC_PKT_DROP_SHFT                                0xa
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_FHRX_UC_PKT_ERR_BMSK                               0x200
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_FHRX_UC_PKT_ERR_SHFT                                 0x9
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_FHRX_UC_OVERFLOW_BMSK                              0x100
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_FHRX_UC_OVERFLOW_SHFT                                0x8
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_FHRX_UC_PKT_PENDING_BMSK                            0x80
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_FHRX_UC_PKT_PENDING_SHFT                             0x7
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_OCTX_C2C_OVERFLOW_BMSK                              0x40
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_OCTX_C2C_OVERFLOW_SHFT                               0x6
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_OCTX_FH_OVERFLOW_BMSK                               0x20
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_OCTX_FH_OVERFLOW_SHFT                                0x5
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_C2CTX_FH_OVERFLOW_BMSK                              0x10
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_C2CTX_FH_OVERFLOW_SHFT                               0x4
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_FHTX_C2C_OVERFLOW_BMSK                               0x8
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_FHTX_C2C_OVERFLOW_SHFT                               0x3
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_OCTX_C2C_LEN_ERR_BMSK                                0x2
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_OCTX_C2C_LEN_ERR_SHFT                                0x1
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_OCTX_FH_LEN_ERR_BMSK                                 0x1
#define HWIO_ECPRI_XBAR_SW_IRQ_CLR_OCTX_FH_LEN_ERR_SHFT                                 0x0

#define HWIO_ECPRI_XBAR_IDLE_1_ADDR                                              (ECPRI_XBAR_REGS_REG_BASE      + 0x00000070)
#define HWIO_ECPRI_XBAR_IDLE_1_PHYS                                              (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000070)
#define HWIO_ECPRI_XBAR_IDLE_1_OFFS                                              (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000070)
#define HWIO_ECPRI_XBAR_IDLE_1_RMSK                                                    0x1f
#define HWIO_ECPRI_XBAR_IDLE_1_ATTR                                                     0x1
#define HWIO_ECPRI_XBAR_IDLE_1_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_IDLE_1_ADDR, HWIO_ECPRI_XBAR_IDLE_1_RMSK)
#define HWIO_ECPRI_XBAR_IDLE_1_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_IDLE_1_ADDR, m)
#define HWIO_ECPRI_XBAR_IDLE_1_CSR_IS_IDLE_BMSK                                        0x10
#define HWIO_ECPRI_XBAR_IDLE_1_CSR_IS_IDLE_SHFT                                         0x4
#define HWIO_ECPRI_XBAR_IDLE_1_ORAN_IS_IDLE_BMSK                                        0x8
#define HWIO_ECPRI_XBAR_IDLE_1_ORAN_IS_IDLE_SHFT                                        0x3
#define HWIO_ECPRI_XBAR_IDLE_1_C2C_IS_IDLE_BMSK                                         0x4
#define HWIO_ECPRI_XBAR_IDLE_1_C2C_IS_IDLE_SHFT                                         0x2
#define HWIO_ECPRI_XBAR_IDLE_1_FH_IS_IDLE_BMSK                                          0x2
#define HWIO_ECPRI_XBAR_IDLE_1_FH_IS_IDLE_SHFT                                          0x1
#define HWIO_ECPRI_XBAR_IDLE_1_XBAR_IS_IDLE_BMSK                                        0x1
#define HWIO_ECPRI_XBAR_IDLE_1_XBAR_IS_IDLE_SHFT                                        0x0

#define HWIO_ECPRI_XBAR_IDLE_2_ADDR                                              (ECPRI_XBAR_REGS_REG_BASE      + 0x00000074)
#define HWIO_ECPRI_XBAR_IDLE_2_PHYS                                              (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000074)
#define HWIO_ECPRI_XBAR_IDLE_2_OFFS                                              (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000074)
#define HWIO_ECPRI_XBAR_IDLE_2_RMSK                                              0xffffffff
#define HWIO_ECPRI_XBAR_IDLE_2_ATTR                                                     0x1
#define HWIO_ECPRI_XBAR_IDLE_2_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_IDLE_2_ADDR, HWIO_ECPRI_XBAR_IDLE_2_RMSK)
#define HWIO_ECPRI_XBAR_IDLE_2_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_IDLE_2_ADDR, m)
#define HWIO_ECPRI_XBAR_IDLE_2_C2CTX_IS_IDLE_BMSK                                0xe0000000
#define HWIO_ECPRI_XBAR_IDLE_2_C2CTX_IS_IDLE_SHFT                                      0x1d
#define HWIO_ECPRI_XBAR_IDLE_2_C2CRX_IS_IDLE_BMSK                                0x1c000000
#define HWIO_ECPRI_XBAR_IDLE_2_C2CRX_IS_IDLE_SHFT                                      0x1a
#define HWIO_ECPRI_XBAR_IDLE_2_FHTX_IS_IDLE_BMSK                                  0x3800000
#define HWIO_ECPRI_XBAR_IDLE_2_FHTX_IS_IDLE_SHFT                                       0x17
#define HWIO_ECPRI_XBAR_IDLE_2_FHRX_IS_IDLE_BMSK                                   0x700000
#define HWIO_ECPRI_XBAR_IDLE_2_FHRX_IS_IDLE_SHFT                                       0x14
#define HWIO_ECPRI_XBAR_IDLE_2_OCTX_C2C_IS_IDLE_BMSK                                0xe0000
#define HWIO_ECPRI_XBAR_IDLE_2_OCTX_C2C_IS_IDLE_SHFT                                   0x11
#define HWIO_ECPRI_XBAR_IDLE_2_OCTX_FH_IS_IDLE_BMSK                                 0x1c000
#define HWIO_ECPRI_XBAR_IDLE_2_OCTX_FH_IS_IDLE_SHFT                                     0xe
#define HWIO_ECPRI_XBAR_IDLE_2_OCTX_ORAN_IS_IDLE_BMSK                                0x3c00
#define HWIO_ECPRI_XBAR_IDLE_2_OCTX_ORAN_IS_IDLE_SHFT                                   0xa
#define HWIO_ECPRI_XBAR_IDLE_2_OCRX_C2C_IS_IDLE_BMSK                                  0x380
#define HWIO_ECPRI_XBAR_IDLE_2_OCRX_C2C_IS_IDLE_SHFT                                    0x7
#define HWIO_ECPRI_XBAR_IDLE_2_OCRX_FH_IS_IDLE_BMSK                                    0x70
#define HWIO_ECPRI_XBAR_IDLE_2_OCRX_FH_IS_IDLE_SHFT                                     0x4
#define HWIO_ECPRI_XBAR_IDLE_2_OCRX_ORAN_IS_IDLE_BMSK                                   0xf
#define HWIO_ECPRI_XBAR_IDLE_2_OCRX_ORAN_IS_IDLE_SHFT                                   0x0

#define HWIO_ECPRI_XBAR_CLKON_CFG_ADDR                                           (ECPRI_XBAR_REGS_REG_BASE      + 0x00000078)
#define HWIO_ECPRI_XBAR_CLKON_CFG_PHYS                                           (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000078)
#define HWIO_ECPRI_XBAR_CLKON_CFG_OFFS                                           (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000078)
#define HWIO_ECPRI_XBAR_CLKON_CFG_RMSK                                               0x7777
#define HWIO_ECPRI_XBAR_CLKON_CFG_ATTR                                                  0x3
#define HWIO_ECPRI_XBAR_CLKON_CFG_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_CLKON_CFG_ADDR, HWIO_ECPRI_XBAR_CLKON_CFG_RMSK)
#define HWIO_ECPRI_XBAR_CLKON_CFG_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_CLKON_CFG_ADDR, m)
#define HWIO_ECPRI_XBAR_CLKON_CFG_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_CLKON_CFG_ADDR,v)
#define HWIO_ECPRI_XBAR_CLKON_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_CLKON_CFG_ADDR,m,v,HWIO_ECPRI_XBAR_CLKON_CFG_IN)
#define HWIO_ECPRI_XBAR_CLKON_CFG_C2CTX_2_CGC_OPEN_BMSK                              0x4000
#define HWIO_ECPRI_XBAR_CLKON_CFG_C2CTX_2_CGC_OPEN_SHFT                                 0xe
#define HWIO_ECPRI_XBAR_CLKON_CFG_C2CTX_1_CGC_OPEN_BMSK                              0x2000
#define HWIO_ECPRI_XBAR_CLKON_CFG_C2CTX_1_CGC_OPEN_SHFT                                 0xd
#define HWIO_ECPRI_XBAR_CLKON_CFG_C2CTX_0_CGC_OPEN_BMSK                              0x1000
#define HWIO_ECPRI_XBAR_CLKON_CFG_C2CTX_0_CGC_OPEN_SHFT                                 0xc
#define HWIO_ECPRI_XBAR_CLKON_CFG_C2CRX_2_CGC_OPEN_BMSK                               0x400
#define HWIO_ECPRI_XBAR_CLKON_CFG_C2CRX_2_CGC_OPEN_SHFT                                 0xa
#define HWIO_ECPRI_XBAR_CLKON_CFG_C2CRX_1_CGC_OPEN_BMSK                               0x200
#define HWIO_ECPRI_XBAR_CLKON_CFG_C2CRX_1_CGC_OPEN_SHFT                                 0x9
#define HWIO_ECPRI_XBAR_CLKON_CFG_C2CRX_0_CGC_OPEN_BMSK                               0x100
#define HWIO_ECPRI_XBAR_CLKON_CFG_C2CRX_0_CGC_OPEN_SHFT                                 0x8
#define HWIO_ECPRI_XBAR_CLKON_CFG_FHTX_2_CGC_OPEN_BMSK                                 0x40
#define HWIO_ECPRI_XBAR_CLKON_CFG_FHTX_2_CGC_OPEN_SHFT                                  0x6
#define HWIO_ECPRI_XBAR_CLKON_CFG_FHTX_1_CGC_OPEN_BMSK                                 0x20
#define HWIO_ECPRI_XBAR_CLKON_CFG_FHTX_1_CGC_OPEN_SHFT                                  0x5
#define HWIO_ECPRI_XBAR_CLKON_CFG_FHTX_0_CGC_OPEN_BMSK                                 0x10
#define HWIO_ECPRI_XBAR_CLKON_CFG_FHTX_0_CGC_OPEN_SHFT                                  0x4
#define HWIO_ECPRI_XBAR_CLKON_CFG_FHRX_2_CGC_OPEN_BMSK                                  0x4
#define HWIO_ECPRI_XBAR_CLKON_CFG_FHRX_2_CGC_OPEN_SHFT                                  0x2
#define HWIO_ECPRI_XBAR_CLKON_CFG_FHRX_1_CGC_OPEN_BMSK                                  0x2
#define HWIO_ECPRI_XBAR_CLKON_CFG_FHRX_1_CGC_OPEN_SHFT                                  0x1
#define HWIO_ECPRI_XBAR_CLKON_CFG_FHRX_0_CGC_OPEN_BMSK                                  0x1
#define HWIO_ECPRI_XBAR_CLKON_CFG_FHRX_0_CGC_OPEN_SHFT                                  0x0

#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_ADDR                                      (ECPRI_XBAR_REGS_REG_BASE      + 0x0000007c)
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_PHYS                                      (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x0000007c)
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OFFS                                      (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x0000007c)
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_RMSK                                         0x77f77
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_ATTR                                             0x3
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_ADDR, HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_ADDR, m)
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_ADDR,v)
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_ADDR,m,v,HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_IN)
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCRX_C2C_2_CGC_OPEN_BMSK                     0x40000
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCRX_C2C_2_CGC_OPEN_SHFT                        0x12
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCRX_C2C_1_CGC_OPEN_BMSK                     0x20000
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCRX_C2C_1_CGC_OPEN_SHFT                        0x11
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCRX_C2C_0_CGC_OPEN_BMSK                     0x10000
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCRX_C2C_0_CGC_OPEN_SHFT                        0x10
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCRX_FH_2_CGC_OPEN_BMSK                       0x4000
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCRX_FH_2_CGC_OPEN_SHFT                          0xe
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCRX_FH_1_CGC_OPEN_BMSK                       0x2000
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCRX_FH_1_CGC_OPEN_SHFT                          0xd
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCRX_FH_0_CGC_OPEN_BMSK                       0x1000
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCRX_FH_0_CGC_OPEN_SHFT                          0xc
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCRX_OC_3_CGC_OPEN_BMSK                        0x800
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCRX_OC_3_CGC_OPEN_SHFT                          0xb
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCRX_OC_2_CGC_OPEN_BMSK                        0x400
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCRX_OC_2_CGC_OPEN_SHFT                          0xa
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCRX_OC_1_CGC_OPEN_BMSK                        0x200
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCRX_OC_1_CGC_OPEN_SHFT                          0x9
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCRX_OC_0_CGC_OPEN_BMSK                        0x100
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCRX_OC_0_CGC_OPEN_SHFT                          0x8
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCTX_C2C_2_CGC_OPEN_BMSK                        0x40
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCTX_C2C_2_CGC_OPEN_SHFT                         0x6
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCTX_C2C_1_CGC_OPEN_BMSK                        0x20
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCTX_C2C_1_CGC_OPEN_SHFT                         0x5
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCTX_C2C_0_CGC_OPEN_BMSK                        0x10
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCTX_C2C_0_CGC_OPEN_SHFT                         0x4
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCTX_FH_2_CGC_OPEN_BMSK                          0x4
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCTX_FH_2_CGC_OPEN_SHFT                          0x2
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCTX_FH_1_CGC_OPEN_BMSK                          0x2
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCTX_FH_1_CGC_OPEN_SHFT                          0x1
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCTX_FH_0_CGC_OPEN_BMSK                          0x1
#define HWIO_ECPRI_XBAR_ORAN_CLKON_CFG_OCTX_FH_0_CGC_OPEN_SHFT                          0x0

#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_ADDR                                      (ECPRI_XBAR_REGS_REG_BASE      + 0x00000080)
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_PHYS                                      (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000080)
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_OFFS                                      (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000080)
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_RMSK                                         0x77f77
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_ATTR                                             0x3
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_ADDR, HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_RMSK)
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_ADDR, m)
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_ADDR,v)
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_ADDR,m,v,HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_IN)
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_OC_C2C_2_ORAN_CLOCK_OFF_BMSK                 0x40000
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_OC_C2C_2_ORAN_CLOCK_OFF_SHFT                    0x12
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_OC_C2C_1_ORAN_CLOCK_OFF_BMSK                 0x20000
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_OC_C2C_1_ORAN_CLOCK_OFF_SHFT                    0x11
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_OC_C2C_0_ORAN_CLOCK_OFF_BMSK                 0x10000
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_OC_C2C_0_ORAN_CLOCK_OFF_SHFT                    0x10
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_OC_FH_2_ORAN_CLOCK_OFF_BMSK                   0x4000
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_OC_FH_2_ORAN_CLOCK_OFF_SHFT                      0xe
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_OC_FH_1_ORAN_CLOCK_OFF_BMSK                   0x2000
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_OC_FH_1_ORAN_CLOCK_OFF_SHFT                      0xd
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_OC_FH_0_ORAN_CLOCK_OFF_BMSK                   0x1000
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_OC_FH_0_ORAN_CLOCK_OFF_SHFT                      0xc
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_OCRX_3_ORAN_CLOCK_OFF_BMSK                     0x800
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_OCRX_3_ORAN_CLOCK_OFF_SHFT                       0xb
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_OCRX_2_ORAN_CLOCK_OFF_BMSK                     0x400
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_OCRX_2_ORAN_CLOCK_OFF_SHFT                       0xa
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_OCRX_1_ORAN_CLOCK_OFF_BMSK                     0x200
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_OCRX_1_ORAN_CLOCK_OFF_SHFT                       0x9
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_OCRX_0_ORAN_CLOCK_OFF_BMSK                     0x100
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_OCRX_0_ORAN_CLOCK_OFF_SHFT                       0x8
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_C2C_2_CLOCK_OFF_BMSK                            0x40
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_C2C_2_CLOCK_OFF_SHFT                             0x6
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_C2C_1_CLOCK_OFF_BMSK                            0x20
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_C2C_1_CLOCK_OFF_SHFT                             0x5
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_C2C_0_CLOCK_OFF_BMSK                            0x10
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_C2C_0_CLOCK_OFF_SHFT                             0x4
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_FH_2_CLOCK_OFF_BMSK                              0x4
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_FH_2_CLOCK_OFF_SHFT                              0x2
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_FH_1_CLOCK_OFF_BMSK                              0x2
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_FH_1_CLOCK_OFF_SHFT                              0x1
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_FH_0_CLOCK_OFF_BMSK                              0x1
#define HWIO_ECPRI_XBAR_GLOBAL_CLK_CTL_FH_0_CLOCK_OFF_SHFT                              0x0

#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_ADDR                                       (ECPRI_XBAR_REGS_REG_BASE      + 0x00000100)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_PHYS                                       (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000100)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_OFFS                                       (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000100)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_RMSK                                          0x1ff0f
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_ATTR                                              0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_ADDR, HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_ADDR, m)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_ADDR,v)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_ADDR,m,v,HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_IN)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_VALID_BMSK                      0x10000
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_VALID_SHFT                         0x10
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_BMSK                      0xff00
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_SHFT                         0x8
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_FHRX_FVAL               0x0
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_C2CRX_FVAL              0x1
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_OCRX_FVAL               0x2
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_DMA_FVAL                0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_UC_FVAL                 0x4
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_BEFORE_LUT_FVAL             0x10
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_AFTER_LUT_FVAL              0x11
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_ALL_FVAL               0xff
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_ID_BMSK                             0xf
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_ID_SHFT                             0x0
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_ID_FHTX_0_FVAL                      0x0
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_ID_FHTX_1_FVAL                      0x1
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_ID_FHTX_2_FVAL                      0x2
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_ID_FHRX_0_FVAL                      0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_ID_FHRX_1_FVAL                      0x4
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_ID_FHRX_2_FVAL                      0x5
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_ID_DMA_TO_FH_FVAL                   0x6
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_ID_FH0_TO_DMA_FVAL                  0x7
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_ID_FH1_TO_DMA_FVAL                  0x8
#define HWIO_ECPRI_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_ID_FH2_TO_DMA_FVAL                  0x9

#define HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_MASK_m_ADDR(m)                            (ECPRI_XBAR_REGS_REG_BASE      + 0x00000104 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_MASK_m_PHYS(m)                            (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000104 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_MASK_m_OFFS(m)                            (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000104 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_MASK_m_RMSK                               0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_MASK_m_MAXm                                        3
#define HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_MASK_m_ATTR                                      0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_MASK_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_MASK_m_ADDR(m), HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_MASK_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_MASK_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_MASK_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_MASK_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_MASK_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_MASK_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_MASK_m_INI(m))
#define HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_MASK_m_MASK_BMSK                          0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_MASK_m_MASK_SHFT                                 0x0

#define HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_VALUE_m_ADDR(m)                           (ECPRI_XBAR_REGS_REG_BASE      + 0x00000114 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_VALUE_m_PHYS(m)                           (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000114 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_VALUE_m_OFFS(m)                           (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000114 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_VALUE_m_RMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_VALUE_m_MAXm                                       3
#define HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_VALUE_m_ATTR                                     0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_VALUE_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_VALUE_m_ADDR(m), HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_VALUE_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_VALUE_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_VALUE_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_VALUE_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_VALUE_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_VALUE_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_VALUE_m_INI(m))
#define HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_VALUE_m_VALUE_BMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_0_DATA_VALUE_m_VALUE_SHFT                               0x0

#define HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_MASK_m_ADDR(m)                           (ECPRI_XBAR_REGS_REG_BASE      + 0x00000124 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_MASK_m_PHYS(m)                           (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000124 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_MASK_m_OFFS(m)                           (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000124 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_MASK_m_RMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_MASK_m_MAXm                                       1
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_MASK_m_ATTR                                     0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_MASK_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_MASK_m_ADDR(m), HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_MASK_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_MASK_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_MASK_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_MASK_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_MASK_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_MASK_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_MASK_m_INI(m))
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_MASK_m_MASK_BMSK                         0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_MASK_m_MASK_SHFT                                0x0

#define HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_VALUE_m_ADDR(m)                          (ECPRI_XBAR_REGS_REG_BASE      + 0x0000012c + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_VALUE_m_PHYS(m)                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x0000012c + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_VALUE_m_OFFS(m)                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x0000012c + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_VALUE_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_VALUE_m_MAXm                                      1
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_VALUE_m_ATTR                                    0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_VALUE_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_VALUE_m_ADDR(m), HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_VALUE_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_VALUE_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_VALUE_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_VALUE_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_VALUE_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_VALUE_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_VALUE_m_INI(m))
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_VALUE_m_VALUE_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TUSER_VALUE_m_VALUE_SHFT                              0x0

#define HWIO_ECPRI_XBAR_FH_TPDM_0_TID_MASK_VALUE_ADDR                            (ECPRI_XBAR_REGS_REG_BASE      + 0x00000134)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TID_MASK_VALUE_PHYS                            (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000134)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TID_MASK_VALUE_OFFS                            (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000134)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TID_MASK_VALUE_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TID_MASK_VALUE_ATTR                                   0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TID_MASK_VALUE_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_0_TID_MASK_VALUE_ADDR, HWIO_ECPRI_XBAR_FH_TPDM_0_TID_MASK_VALUE_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TID_MASK_VALUE_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_0_TID_MASK_VALUE_ADDR, m)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TID_MASK_VALUE_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_0_TID_MASK_VALUE_ADDR,v)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TID_MASK_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_0_TID_MASK_VALUE_ADDR,m,v,HWIO_ECPRI_XBAR_FH_TPDM_0_TID_MASK_VALUE_IN)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TID_MASK_VALUE_VALUE_BMSK                      0xffff0000
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TID_MASK_VALUE_VALUE_SHFT                            0x10
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TID_MASK_VALUE_MASK_BMSK                           0xffff
#define HWIO_ECPRI_XBAR_FH_TPDM_0_TID_MASK_VALUE_MASK_SHFT                              0x0

#define HWIO_ECPRI_XBAR_FH_TPDM_0_MISC_MASK_VALUE_ADDR                           (ECPRI_XBAR_REGS_REG_BASE      + 0x00000138)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_MISC_MASK_VALUE_PHYS                           (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000138)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_MISC_MASK_VALUE_OFFS                           (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000138)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_MISC_MASK_VALUE_RMSK                              0x3ffff
#define HWIO_ECPRI_XBAR_FH_TPDM_0_MISC_MASK_VALUE_ATTR                                  0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_0_MISC_MASK_VALUE_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_0_MISC_MASK_VALUE_ADDR, HWIO_ECPRI_XBAR_FH_TPDM_0_MISC_MASK_VALUE_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_MISC_MASK_VALUE_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_0_MISC_MASK_VALUE_ADDR, m)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_MISC_MASK_VALUE_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_0_MISC_MASK_VALUE_ADDR,v)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_MISC_MASK_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_0_MISC_MASK_VALUE_ADDR,m,v,HWIO_ECPRI_XBAR_FH_TPDM_0_MISC_MASK_VALUE_IN)
#define HWIO_ECPRI_XBAR_FH_TPDM_0_MISC_MASK_VALUE_TERROR_VALUE_BMSK                 0x20000
#define HWIO_ECPRI_XBAR_FH_TPDM_0_MISC_MASK_VALUE_TERROR_VALUE_SHFT                    0x11
#define HWIO_ECPRI_XBAR_FH_TPDM_0_MISC_MASK_VALUE_TERROR_MASK_BMSK                  0x10000
#define HWIO_ECPRI_XBAR_FH_TPDM_0_MISC_MASK_VALUE_TERROR_MASK_SHFT                     0x10
#define HWIO_ECPRI_XBAR_FH_TPDM_0_MISC_MASK_VALUE_TDEST_VALUE_BMSK                   0xff00
#define HWIO_ECPRI_XBAR_FH_TPDM_0_MISC_MASK_VALUE_TDEST_VALUE_SHFT                      0x8
#define HWIO_ECPRI_XBAR_FH_TPDM_0_MISC_MASK_VALUE_TDEST_MASK_BMSK                      0xff
#define HWIO_ECPRI_XBAR_FH_TPDM_0_MISC_MASK_VALUE_TDEST_MASK_SHFT                       0x0

#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_ADDR                                       (ECPRI_XBAR_REGS_REG_BASE      + 0x00000140)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_PHYS                                       (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000140)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_OFFS                                       (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000140)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_RMSK                                          0x1ff0f
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_ATTR                                              0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_ADDR, HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_ADDR, m)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_ADDR,v)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_ADDR,m,v,HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_IN)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_VALID_BMSK                      0x10000
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_VALID_SHFT                         0x10
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_BMSK                      0xff00
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_SHFT                         0x8
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_FHRX_FVAL               0x0
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_C2CRX_FVAL              0x1
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_OCRX_FVAL               0x2
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_DMA_FVAL                0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_UC_FVAL                 0x4
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_BEFORE_LUT_FVAL             0x10
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_AFTER_LUT_FVAL              0x11
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_ALL_FVAL               0xff
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_ID_BMSK                             0xf
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_ID_SHFT                             0x0
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_ID_FHTX_0_FVAL                      0x0
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_ID_FHTX_1_FVAL                      0x1
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_ID_FHTX_2_FVAL                      0x2
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_ID_FHRX_0_FVAL                      0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_ID_FHRX_1_FVAL                      0x4
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_ID_FHRX_2_FVAL                      0x5
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_ID_DMA_TO_FH_FVAL                   0x6
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_ID_FH0_TO_DMA_FVAL                  0x7
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_ID_FH1_TO_DMA_FVAL                  0x8
#define HWIO_ECPRI_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_ID_FH2_TO_DMA_FVAL                  0x9

#define HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_MASK_m_ADDR(m)                            (ECPRI_XBAR_REGS_REG_BASE      + 0x00000144 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_MASK_m_PHYS(m)                            (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000144 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_MASK_m_OFFS(m)                            (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000144 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_MASK_m_RMSK                               0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_MASK_m_MAXm                                        3
#define HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_MASK_m_ATTR                                      0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_MASK_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_MASK_m_ADDR(m), HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_MASK_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_MASK_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_MASK_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_MASK_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_MASK_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_MASK_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_MASK_m_INI(m))
#define HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_MASK_m_MASK_BMSK                          0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_MASK_m_MASK_SHFT                                 0x0

#define HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_VALUE_m_ADDR(m)                           (ECPRI_XBAR_REGS_REG_BASE      + 0x00000154 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_VALUE_m_PHYS(m)                           (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000154 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_VALUE_m_OFFS(m)                           (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000154 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_VALUE_m_RMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_VALUE_m_MAXm                                       3
#define HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_VALUE_m_ATTR                                     0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_VALUE_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_VALUE_m_ADDR(m), HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_VALUE_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_VALUE_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_VALUE_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_VALUE_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_VALUE_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_VALUE_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_VALUE_m_INI(m))
#define HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_VALUE_m_VALUE_BMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_1_DATA_VALUE_m_VALUE_SHFT                               0x0

#define HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_MASK_m_ADDR(m)                           (ECPRI_XBAR_REGS_REG_BASE      + 0x00000164 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_MASK_m_PHYS(m)                           (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000164 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_MASK_m_OFFS(m)                           (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000164 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_MASK_m_RMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_MASK_m_MAXm                                       1
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_MASK_m_ATTR                                     0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_MASK_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_MASK_m_ADDR(m), HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_MASK_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_MASK_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_MASK_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_MASK_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_MASK_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_MASK_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_MASK_m_INI(m))
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_MASK_m_MASK_BMSK                         0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_MASK_m_MASK_SHFT                                0x0

#define HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_VALUE_m_ADDR(m)                          (ECPRI_XBAR_REGS_REG_BASE      + 0x0000016c + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_VALUE_m_PHYS(m)                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x0000016c + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_VALUE_m_OFFS(m)                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x0000016c + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_VALUE_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_VALUE_m_MAXm                                      1
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_VALUE_m_ATTR                                    0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_VALUE_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_VALUE_m_ADDR(m), HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_VALUE_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_VALUE_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_VALUE_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_VALUE_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_VALUE_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_VALUE_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_VALUE_m_INI(m))
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_VALUE_m_VALUE_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TUSER_VALUE_m_VALUE_SHFT                              0x0

#define HWIO_ECPRI_XBAR_FH_TPDM_1_TID_MASK_VALUE_ADDR                            (ECPRI_XBAR_REGS_REG_BASE      + 0x00000174)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TID_MASK_VALUE_PHYS                            (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000174)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TID_MASK_VALUE_OFFS                            (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000174)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TID_MASK_VALUE_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TID_MASK_VALUE_ATTR                                   0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TID_MASK_VALUE_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_1_TID_MASK_VALUE_ADDR, HWIO_ECPRI_XBAR_FH_TPDM_1_TID_MASK_VALUE_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TID_MASK_VALUE_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_1_TID_MASK_VALUE_ADDR, m)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TID_MASK_VALUE_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_1_TID_MASK_VALUE_ADDR,v)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TID_MASK_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_1_TID_MASK_VALUE_ADDR,m,v,HWIO_ECPRI_XBAR_FH_TPDM_1_TID_MASK_VALUE_IN)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TID_MASK_VALUE_VALUE_BMSK                      0xffff0000
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TID_MASK_VALUE_VALUE_SHFT                            0x10
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TID_MASK_VALUE_MASK_BMSK                           0xffff
#define HWIO_ECPRI_XBAR_FH_TPDM_1_TID_MASK_VALUE_MASK_SHFT                              0x0

#define HWIO_ECPRI_XBAR_FH_TPDM_1_MISC_MASK_VALUE_ADDR                           (ECPRI_XBAR_REGS_REG_BASE      + 0x00000178)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_MISC_MASK_VALUE_PHYS                           (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000178)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_MISC_MASK_VALUE_OFFS                           (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000178)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_MISC_MASK_VALUE_RMSK                              0x3ffff
#define HWIO_ECPRI_XBAR_FH_TPDM_1_MISC_MASK_VALUE_ATTR                                  0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_1_MISC_MASK_VALUE_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_1_MISC_MASK_VALUE_ADDR, HWIO_ECPRI_XBAR_FH_TPDM_1_MISC_MASK_VALUE_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_MISC_MASK_VALUE_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_1_MISC_MASK_VALUE_ADDR, m)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_MISC_MASK_VALUE_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_1_MISC_MASK_VALUE_ADDR,v)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_MISC_MASK_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_1_MISC_MASK_VALUE_ADDR,m,v,HWIO_ECPRI_XBAR_FH_TPDM_1_MISC_MASK_VALUE_IN)
#define HWIO_ECPRI_XBAR_FH_TPDM_1_MISC_MASK_VALUE_TERROR_VALUE_BMSK                 0x20000
#define HWIO_ECPRI_XBAR_FH_TPDM_1_MISC_MASK_VALUE_TERROR_VALUE_SHFT                    0x11
#define HWIO_ECPRI_XBAR_FH_TPDM_1_MISC_MASK_VALUE_TERROR_MASK_BMSK                  0x10000
#define HWIO_ECPRI_XBAR_FH_TPDM_1_MISC_MASK_VALUE_TERROR_MASK_SHFT                     0x10
#define HWIO_ECPRI_XBAR_FH_TPDM_1_MISC_MASK_VALUE_TDEST_VALUE_BMSK                   0xff00
#define HWIO_ECPRI_XBAR_FH_TPDM_1_MISC_MASK_VALUE_TDEST_VALUE_SHFT                      0x8
#define HWIO_ECPRI_XBAR_FH_TPDM_1_MISC_MASK_VALUE_TDEST_MASK_BMSK                      0xff
#define HWIO_ECPRI_XBAR_FH_TPDM_1_MISC_MASK_VALUE_TDEST_MASK_SHFT                       0x0

#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_ADDR                                       (ECPRI_XBAR_REGS_REG_BASE      + 0x00000180)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_PHYS                                       (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000180)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_OFFS                                       (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000180)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_RMSK                                          0x1ff0f
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_ATTR                                              0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_ADDR, HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_ADDR, m)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_ADDR,v)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_ADDR,m,v,HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_IN)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_VALID_BMSK                      0x10000
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_VALID_SHFT                         0x10
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_BMSK                      0xff00
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_SHFT                         0x8
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_FHRX_FVAL               0x0
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_C2CRX_FVAL              0x1
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_OCRX_FVAL               0x2
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_DMA_FVAL                0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_UC_FVAL                 0x4
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_BEFORE_LUT_FVAL             0x10
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_AFTER_LUT_FVAL              0x11
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_ALL_FVAL               0xff
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_ID_BMSK                             0xf
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_ID_SHFT                             0x0
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_ID_FHTX_0_FVAL                      0x0
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_ID_FHTX_1_FVAL                      0x1
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_ID_FHTX_2_FVAL                      0x2
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_ID_FHRX_0_FVAL                      0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_ID_FHRX_1_FVAL                      0x4
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_ID_FHRX_2_FVAL                      0x5
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_ID_DMA_TO_FH_FVAL                   0x6
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_ID_FH0_TO_DMA_FVAL                  0x7
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_ID_FH1_TO_DMA_FVAL                  0x8
#define HWIO_ECPRI_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_ID_FH2_TO_DMA_FVAL                  0x9

#define HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_MASK_m_ADDR(m)                            (ECPRI_XBAR_REGS_REG_BASE      + 0x00000184 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_MASK_m_PHYS(m)                            (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000184 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_MASK_m_OFFS(m)                            (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000184 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_MASK_m_RMSK                               0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_MASK_m_MAXm                                        3
#define HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_MASK_m_ATTR                                      0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_MASK_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_MASK_m_ADDR(m), HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_MASK_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_MASK_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_MASK_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_MASK_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_MASK_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_MASK_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_MASK_m_INI(m))
#define HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_MASK_m_MASK_BMSK                          0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_MASK_m_MASK_SHFT                                 0x0

#define HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_VALUE_m_ADDR(m)                           (ECPRI_XBAR_REGS_REG_BASE      + 0x00000194 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_VALUE_m_PHYS(m)                           (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000194 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_VALUE_m_OFFS(m)                           (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000194 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_VALUE_m_RMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_VALUE_m_MAXm                                       3
#define HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_VALUE_m_ATTR                                     0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_VALUE_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_VALUE_m_ADDR(m), HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_VALUE_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_VALUE_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_VALUE_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_VALUE_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_VALUE_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_VALUE_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_VALUE_m_INI(m))
#define HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_VALUE_m_VALUE_BMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_2_DATA_VALUE_m_VALUE_SHFT                               0x0

#define HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_MASK_m_ADDR(m)                           (ECPRI_XBAR_REGS_REG_BASE      + 0x000001a4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_MASK_m_PHYS(m)                           (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000001a4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_MASK_m_OFFS(m)                           (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000001a4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_MASK_m_RMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_MASK_m_MAXm                                       1
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_MASK_m_ATTR                                     0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_MASK_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_MASK_m_ADDR(m), HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_MASK_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_MASK_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_MASK_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_MASK_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_MASK_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_MASK_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_MASK_m_INI(m))
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_MASK_m_MASK_BMSK                         0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_MASK_m_MASK_SHFT                                0x0

#define HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_VALUE_m_ADDR(m)                          (ECPRI_XBAR_REGS_REG_BASE      + 0x000001ac + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_VALUE_m_PHYS(m)                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000001ac + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_VALUE_m_OFFS(m)                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000001ac + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_VALUE_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_VALUE_m_MAXm                                      1
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_VALUE_m_ATTR                                    0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_VALUE_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_VALUE_m_ADDR(m), HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_VALUE_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_VALUE_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_VALUE_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_VALUE_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_VALUE_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_VALUE_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_VALUE_m_INI(m))
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_VALUE_m_VALUE_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TUSER_VALUE_m_VALUE_SHFT                              0x0

#define HWIO_ECPRI_XBAR_FH_TPDM_2_TID_MASK_VALUE_ADDR                            (ECPRI_XBAR_REGS_REG_BASE      + 0x000001b4)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TID_MASK_VALUE_PHYS                            (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000001b4)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TID_MASK_VALUE_OFFS                            (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000001b4)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TID_MASK_VALUE_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TID_MASK_VALUE_ATTR                                   0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TID_MASK_VALUE_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_2_TID_MASK_VALUE_ADDR, HWIO_ECPRI_XBAR_FH_TPDM_2_TID_MASK_VALUE_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TID_MASK_VALUE_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_2_TID_MASK_VALUE_ADDR, m)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TID_MASK_VALUE_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_2_TID_MASK_VALUE_ADDR,v)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TID_MASK_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_2_TID_MASK_VALUE_ADDR,m,v,HWIO_ECPRI_XBAR_FH_TPDM_2_TID_MASK_VALUE_IN)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TID_MASK_VALUE_VALUE_BMSK                      0xffff0000
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TID_MASK_VALUE_VALUE_SHFT                            0x10
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TID_MASK_VALUE_MASK_BMSK                           0xffff
#define HWIO_ECPRI_XBAR_FH_TPDM_2_TID_MASK_VALUE_MASK_SHFT                              0x0

#define HWIO_ECPRI_XBAR_FH_TPDM_2_MISC_MASK_VALUE_ADDR                           (ECPRI_XBAR_REGS_REG_BASE      + 0x000001b8)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_MISC_MASK_VALUE_PHYS                           (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000001b8)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_MISC_MASK_VALUE_OFFS                           (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000001b8)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_MISC_MASK_VALUE_RMSK                              0x3ffff
#define HWIO_ECPRI_XBAR_FH_TPDM_2_MISC_MASK_VALUE_ATTR                                  0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_2_MISC_MASK_VALUE_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_2_MISC_MASK_VALUE_ADDR, HWIO_ECPRI_XBAR_FH_TPDM_2_MISC_MASK_VALUE_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_MISC_MASK_VALUE_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_2_MISC_MASK_VALUE_ADDR, m)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_MISC_MASK_VALUE_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_2_MISC_MASK_VALUE_ADDR,v)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_MISC_MASK_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_2_MISC_MASK_VALUE_ADDR,m,v,HWIO_ECPRI_XBAR_FH_TPDM_2_MISC_MASK_VALUE_IN)
#define HWIO_ECPRI_XBAR_FH_TPDM_2_MISC_MASK_VALUE_TERROR_VALUE_BMSK                 0x20000
#define HWIO_ECPRI_XBAR_FH_TPDM_2_MISC_MASK_VALUE_TERROR_VALUE_SHFT                    0x11
#define HWIO_ECPRI_XBAR_FH_TPDM_2_MISC_MASK_VALUE_TERROR_MASK_BMSK                  0x10000
#define HWIO_ECPRI_XBAR_FH_TPDM_2_MISC_MASK_VALUE_TERROR_MASK_SHFT                     0x10
#define HWIO_ECPRI_XBAR_FH_TPDM_2_MISC_MASK_VALUE_TDEST_VALUE_BMSK                   0xff00
#define HWIO_ECPRI_XBAR_FH_TPDM_2_MISC_MASK_VALUE_TDEST_VALUE_SHFT                      0x8
#define HWIO_ECPRI_XBAR_FH_TPDM_2_MISC_MASK_VALUE_TDEST_MASK_BMSK                      0xff
#define HWIO_ECPRI_XBAR_FH_TPDM_2_MISC_MASK_VALUE_TDEST_MASK_SHFT                       0x0

#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_ADDR                                       (ECPRI_XBAR_REGS_REG_BASE      + 0x000001c0)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_PHYS                                       (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000001c0)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_OFFS                                       (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000001c0)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_RMSK                                          0x1ff0f
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_ATTR                                              0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_ADDR, HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_ADDR, m)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_ADDR,v)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_ADDR,m,v,HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_IN)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_VALID_BMSK                      0x10000
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_VALID_SHFT                         0x10
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_BMSK                      0xff00
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_SHFT                         0x8
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_FHRX_FVAL               0x0
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_C2CRX_FVAL              0x1
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_OCRX_FVAL               0x2
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_DMA_FVAL                0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_UC_FVAL                 0x4
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_BEFORE_LUT_FVAL             0x10
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_AFTER_LUT_FVAL              0x11
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_ALL_FVAL               0xff
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_ID_BMSK                             0xf
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_ID_SHFT                             0x0
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_ID_FHTX_0_FVAL                      0x0
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_ID_FHTX_1_FVAL                      0x1
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_ID_FHTX_2_FVAL                      0x2
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_ID_FHRX_0_FVAL                      0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_ID_FHRX_1_FVAL                      0x4
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_ID_FHRX_2_FVAL                      0x5
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_ID_DMA_TO_FH_FVAL                   0x6
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_ID_FH0_TO_DMA_FVAL                  0x7
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_ID_FH1_TO_DMA_FVAL                  0x8
#define HWIO_ECPRI_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_ID_FH2_TO_DMA_FVAL                  0x9

#define HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_MASK_m_ADDR(m)                            (ECPRI_XBAR_REGS_REG_BASE      + 0x000001c4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_MASK_m_PHYS(m)                            (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000001c4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_MASK_m_OFFS(m)                            (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000001c4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_MASK_m_RMSK                               0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_MASK_m_MAXm                                        3
#define HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_MASK_m_ATTR                                      0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_MASK_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_MASK_m_ADDR(m), HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_MASK_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_MASK_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_MASK_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_MASK_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_MASK_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_MASK_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_MASK_m_INI(m))
#define HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_MASK_m_MASK_BMSK                          0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_MASK_m_MASK_SHFT                                 0x0

#define HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_VALUE_m_ADDR(m)                           (ECPRI_XBAR_REGS_REG_BASE      + 0x000001d4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_VALUE_m_PHYS(m)                           (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000001d4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_VALUE_m_OFFS(m)                           (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000001d4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_VALUE_m_RMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_VALUE_m_MAXm                                       3
#define HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_VALUE_m_ATTR                                     0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_VALUE_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_VALUE_m_ADDR(m), HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_VALUE_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_VALUE_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_VALUE_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_VALUE_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_VALUE_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_VALUE_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_VALUE_m_INI(m))
#define HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_VALUE_m_VALUE_BMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_3_DATA_VALUE_m_VALUE_SHFT                               0x0

#define HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_MASK_m_ADDR(m)                           (ECPRI_XBAR_REGS_REG_BASE      + 0x000001e4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_MASK_m_PHYS(m)                           (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000001e4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_MASK_m_OFFS(m)                           (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000001e4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_MASK_m_RMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_MASK_m_MAXm                                       1
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_MASK_m_ATTR                                     0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_MASK_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_MASK_m_ADDR(m), HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_MASK_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_MASK_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_MASK_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_MASK_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_MASK_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_MASK_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_MASK_m_INI(m))
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_MASK_m_MASK_BMSK                         0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_MASK_m_MASK_SHFT                                0x0

#define HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_VALUE_m_ADDR(m)                          (ECPRI_XBAR_REGS_REG_BASE      + 0x000001ec + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_VALUE_m_PHYS(m)                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000001ec + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_VALUE_m_OFFS(m)                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000001ec + 0x4 * (m))
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_VALUE_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_VALUE_m_MAXm                                      1
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_VALUE_m_ATTR                                    0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_VALUE_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_VALUE_m_ADDR(m), HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_VALUE_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_VALUE_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_VALUE_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_VALUE_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_VALUE_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_VALUE_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_VALUE_m_INI(m))
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_VALUE_m_VALUE_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TUSER_VALUE_m_VALUE_SHFT                              0x0

#define HWIO_ECPRI_XBAR_FH_TPDM_3_TID_MASK_VALUE_ADDR                            (ECPRI_XBAR_REGS_REG_BASE      + 0x000001f4)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TID_MASK_VALUE_PHYS                            (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000001f4)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TID_MASK_VALUE_OFFS                            (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000001f4)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TID_MASK_VALUE_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TID_MASK_VALUE_ATTR                                   0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TID_MASK_VALUE_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_3_TID_MASK_VALUE_ADDR, HWIO_ECPRI_XBAR_FH_TPDM_3_TID_MASK_VALUE_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TID_MASK_VALUE_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_3_TID_MASK_VALUE_ADDR, m)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TID_MASK_VALUE_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_3_TID_MASK_VALUE_ADDR,v)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TID_MASK_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_3_TID_MASK_VALUE_ADDR,m,v,HWIO_ECPRI_XBAR_FH_TPDM_3_TID_MASK_VALUE_IN)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TID_MASK_VALUE_VALUE_BMSK                      0xffff0000
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TID_MASK_VALUE_VALUE_SHFT                            0x10
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TID_MASK_VALUE_MASK_BMSK                           0xffff
#define HWIO_ECPRI_XBAR_FH_TPDM_3_TID_MASK_VALUE_MASK_SHFT                              0x0

#define HWIO_ECPRI_XBAR_FH_TPDM_3_MISC_MASK_VALUE_ADDR                           (ECPRI_XBAR_REGS_REG_BASE      + 0x000001f8)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_MISC_MASK_VALUE_PHYS                           (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000001f8)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_MISC_MASK_VALUE_OFFS                           (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000001f8)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_MISC_MASK_VALUE_RMSK                              0x3ffff
#define HWIO_ECPRI_XBAR_FH_TPDM_3_MISC_MASK_VALUE_ATTR                                  0x3
#define HWIO_ECPRI_XBAR_FH_TPDM_3_MISC_MASK_VALUE_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_3_MISC_MASK_VALUE_ADDR, HWIO_ECPRI_XBAR_FH_TPDM_3_MISC_MASK_VALUE_RMSK)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_MISC_MASK_VALUE_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_TPDM_3_MISC_MASK_VALUE_ADDR, m)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_MISC_MASK_VALUE_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_FH_TPDM_3_MISC_MASK_VALUE_ADDR,v)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_MISC_MASK_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FH_TPDM_3_MISC_MASK_VALUE_ADDR,m,v,HWIO_ECPRI_XBAR_FH_TPDM_3_MISC_MASK_VALUE_IN)
#define HWIO_ECPRI_XBAR_FH_TPDM_3_MISC_MASK_VALUE_TERROR_VALUE_BMSK                 0x20000
#define HWIO_ECPRI_XBAR_FH_TPDM_3_MISC_MASK_VALUE_TERROR_VALUE_SHFT                    0x11
#define HWIO_ECPRI_XBAR_FH_TPDM_3_MISC_MASK_VALUE_TERROR_MASK_BMSK                  0x10000
#define HWIO_ECPRI_XBAR_FH_TPDM_3_MISC_MASK_VALUE_TERROR_MASK_SHFT                     0x10
#define HWIO_ECPRI_XBAR_FH_TPDM_3_MISC_MASK_VALUE_TDEST_VALUE_BMSK                   0xff00
#define HWIO_ECPRI_XBAR_FH_TPDM_3_MISC_MASK_VALUE_TDEST_VALUE_SHFT                      0x8
#define HWIO_ECPRI_XBAR_FH_TPDM_3_MISC_MASK_VALUE_TDEST_MASK_BMSK                      0xff
#define HWIO_ECPRI_XBAR_FH_TPDM_3_MISC_MASK_VALUE_TDEST_MASK_SHFT                       0x0

#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_ADDR                                      (ECPRI_XBAR_REGS_REG_BASE      + 0x00000200)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_PHYS                                      (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000200)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_OFFS                                      (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000200)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_RMSK                                         0x1ff0f
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_ATTR                                             0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_ADDR, HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_ADDR, m)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_ADDR,v)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_ADDR,m,v,HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_IN)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_VALID_BMSK                     0x10000
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_VALID_SHFT                        0x10
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_BMSK                     0xff00
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_SHFT                        0x8
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_FHRX_FVAL              0x0
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_C2CRX_FVAL             0x1
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_OCRX_FVAL              0x2
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_DMA_FVAL               0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_UC_FVAL                0x4
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_BEFORE_LUT_FVAL            0x10
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_AFTER_LUT_FVAL             0x11
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_ALL_FVAL              0xff
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_ID_BMSK                            0xf
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_ID_SHFT                            0x0
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_ID_C2CTX_0_FVAL                    0x0
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_ID_C2CTX_1_FVAL                    0x1
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_ID_C2CTX_2_FVAL                    0x2
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_ID_C2CRX_0_FVAL                    0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_ID_C2CRX_1_FVAL                    0x4
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_ID_C2CRX_2_FVAL                    0x5
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_ID_DMA_TO_C2C_FVAL                 0x6
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_ID_C2C0_TO_DMA_FVAL                0x7
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_ID_C2C1_TO_DMA_FVAL                0x8
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_ID_C2C2_TO_DMA_FVAL                0x9

#define HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_MASK_m_ADDR(m)                           (ECPRI_XBAR_REGS_REG_BASE      + 0x00000204 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_MASK_m_PHYS(m)                           (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000204 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_MASK_m_OFFS(m)                           (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000204 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_MASK_m_RMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_MASK_m_MAXm                                       3
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_MASK_m_ATTR                                     0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_MASK_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_MASK_m_ADDR(m), HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_MASK_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_MASK_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_MASK_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_MASK_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_MASK_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_MASK_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_MASK_m_INI(m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_MASK_m_MASK_BMSK                         0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_MASK_m_MASK_SHFT                                0x0

#define HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_VALUE_m_ADDR(m)                          (ECPRI_XBAR_REGS_REG_BASE      + 0x00000214 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_VALUE_m_PHYS(m)                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000214 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_VALUE_m_OFFS(m)                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000214 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_VALUE_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_VALUE_m_MAXm                                      3
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_VALUE_m_ATTR                                    0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_VALUE_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_VALUE_m_ADDR(m), HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_VALUE_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_VALUE_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_VALUE_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_VALUE_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_VALUE_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_VALUE_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_VALUE_m_INI(m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_VALUE_m_VALUE_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_DATA_VALUE_m_VALUE_SHFT                              0x0

#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_MASK_m_ADDR(m)                          (ECPRI_XBAR_REGS_REG_BASE      + 0x00000224 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_MASK_m_PHYS(m)                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000224 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_MASK_m_OFFS(m)                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000224 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_MASK_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_MASK_m_MAXm                                      1
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_MASK_m_ATTR                                    0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_MASK_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_MASK_m_ADDR(m), HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_MASK_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_MASK_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_MASK_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_MASK_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_MASK_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_MASK_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_MASK_m_INI(m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_MASK_m_MASK_BMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_MASK_m_MASK_SHFT                               0x0

#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_VALUE_m_ADDR(m)                         (ECPRI_XBAR_REGS_REG_BASE      + 0x0000022c + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_VALUE_m_PHYS(m)                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x0000022c + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_VALUE_m_OFFS(m)                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x0000022c + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_VALUE_m_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_VALUE_m_MAXm                                     1
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_VALUE_m_ATTR                                   0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_VALUE_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_VALUE_m_ADDR(m), HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_VALUE_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_VALUE_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_VALUE_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_VALUE_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_VALUE_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_VALUE_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_VALUE_m_INI(m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_VALUE_m_VALUE_BMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TUSER_VALUE_m_VALUE_SHFT                             0x0

#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TID_MASK_VALUE_ADDR                           (ECPRI_XBAR_REGS_REG_BASE      + 0x00000234)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TID_MASK_VALUE_PHYS                           (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000234)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TID_MASK_VALUE_OFFS                           (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000234)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TID_MASK_VALUE_RMSK                           0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TID_MASK_VALUE_ATTR                                  0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TID_MASK_VALUE_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_0_TID_MASK_VALUE_ADDR, HWIO_ECPRI_XBAR_C2C_TPDM_0_TID_MASK_VALUE_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TID_MASK_VALUE_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_0_TID_MASK_VALUE_ADDR, m)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TID_MASK_VALUE_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_0_TID_MASK_VALUE_ADDR,v)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TID_MASK_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_0_TID_MASK_VALUE_ADDR,m,v,HWIO_ECPRI_XBAR_C2C_TPDM_0_TID_MASK_VALUE_IN)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TID_MASK_VALUE_VALUE_BMSK                     0xffff0000
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TID_MASK_VALUE_VALUE_SHFT                           0x10
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TID_MASK_VALUE_MASK_BMSK                          0xffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_TID_MASK_VALUE_MASK_SHFT                             0x0

#define HWIO_ECPRI_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_ADDR                          (ECPRI_XBAR_REGS_REG_BASE      + 0x00000238)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_PHYS                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000238)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_OFFS                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000238)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_RMSK                             0x3ffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_ATTR                                 0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_ADDR, HWIO_ECPRI_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_ADDR, m)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_ADDR,v)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_ADDR,m,v,HWIO_ECPRI_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_IN)
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_TERROR_VALUE_BMSK                0x20000
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_TERROR_VALUE_SHFT                   0x11
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_TERROR_MASK_BMSK                 0x10000
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_TERROR_MASK_SHFT                    0x10
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_TDEST_VALUE_BMSK                  0xff00
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_TDEST_VALUE_SHFT                     0x8
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_TDEST_MASK_BMSK                     0xff
#define HWIO_ECPRI_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_TDEST_MASK_SHFT                      0x0

#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_ADDR                                      (ECPRI_XBAR_REGS_REG_BASE      + 0x00000240)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_PHYS                                      (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000240)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_OFFS                                      (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000240)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_RMSK                                         0x1ff0f
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_ATTR                                             0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_ADDR, HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_ADDR, m)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_ADDR,v)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_ADDR,m,v,HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_IN)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_VALID_BMSK                     0x10000
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_VALID_SHFT                        0x10
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_BMSK                     0xff00
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_SHFT                        0x8
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_FHRX_FVAL              0x0
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_C2CRX_FVAL             0x1
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_OCRX_FVAL              0x2
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_DMA_FVAL               0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_UC_FVAL                0x4
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_BEFORE_LUT_FVAL            0x10
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_AFTER_LUT_FVAL             0x11
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_ALL_FVAL              0xff
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_ID_BMSK                            0xf
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_ID_SHFT                            0x0
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_ID_C2CTX_0_FVAL                    0x0
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_ID_C2CTX_1_FVAL                    0x1
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_ID_C2CTX_2_FVAL                    0x2
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_ID_C2CRX_0_FVAL                    0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_ID_C2CRX_1_FVAL                    0x4
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_ID_C2CRX_2_FVAL                    0x5
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_ID_DMA_TO_C2C_FVAL                 0x6
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_ID_C2C0_TO_DMA_FVAL                0x7
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_ID_C2C1_TO_DMA_FVAL                0x8
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_ID_C2C2_TO_DMA_FVAL                0x9

#define HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_MASK_m_ADDR(m)                           (ECPRI_XBAR_REGS_REG_BASE      + 0x00000244 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_MASK_m_PHYS(m)                           (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000244 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_MASK_m_OFFS(m)                           (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000244 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_MASK_m_RMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_MASK_m_MAXm                                       3
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_MASK_m_ATTR                                     0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_MASK_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_MASK_m_ADDR(m), HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_MASK_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_MASK_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_MASK_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_MASK_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_MASK_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_MASK_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_MASK_m_INI(m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_MASK_m_MASK_BMSK                         0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_MASK_m_MASK_SHFT                                0x0

#define HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_VALUE_m_ADDR(m)                          (ECPRI_XBAR_REGS_REG_BASE      + 0x00000254 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_VALUE_m_PHYS(m)                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000254 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_VALUE_m_OFFS(m)                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000254 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_VALUE_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_VALUE_m_MAXm                                      3
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_VALUE_m_ATTR                                    0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_VALUE_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_VALUE_m_ADDR(m), HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_VALUE_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_VALUE_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_VALUE_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_VALUE_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_VALUE_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_VALUE_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_VALUE_m_INI(m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_VALUE_m_VALUE_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_DATA_VALUE_m_VALUE_SHFT                              0x0

#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_MASK_m_ADDR(m)                          (ECPRI_XBAR_REGS_REG_BASE      + 0x00000264 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_MASK_m_PHYS(m)                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000264 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_MASK_m_OFFS(m)                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000264 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_MASK_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_MASK_m_MAXm                                      1
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_MASK_m_ATTR                                    0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_MASK_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_MASK_m_ADDR(m), HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_MASK_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_MASK_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_MASK_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_MASK_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_MASK_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_MASK_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_MASK_m_INI(m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_MASK_m_MASK_BMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_MASK_m_MASK_SHFT                               0x0

#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_VALUE_m_ADDR(m)                         (ECPRI_XBAR_REGS_REG_BASE      + 0x0000026c + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_VALUE_m_PHYS(m)                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x0000026c + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_VALUE_m_OFFS(m)                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x0000026c + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_VALUE_m_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_VALUE_m_MAXm                                     1
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_VALUE_m_ATTR                                   0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_VALUE_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_VALUE_m_ADDR(m), HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_VALUE_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_VALUE_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_VALUE_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_VALUE_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_VALUE_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_VALUE_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_VALUE_m_INI(m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_VALUE_m_VALUE_BMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TUSER_VALUE_m_VALUE_SHFT                             0x0

#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TID_MASK_VALUE_ADDR                           (ECPRI_XBAR_REGS_REG_BASE      + 0x00000274)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TID_MASK_VALUE_PHYS                           (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000274)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TID_MASK_VALUE_OFFS                           (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000274)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TID_MASK_VALUE_RMSK                           0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TID_MASK_VALUE_ATTR                                  0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TID_MASK_VALUE_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_1_TID_MASK_VALUE_ADDR, HWIO_ECPRI_XBAR_C2C_TPDM_1_TID_MASK_VALUE_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TID_MASK_VALUE_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_1_TID_MASK_VALUE_ADDR, m)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TID_MASK_VALUE_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_1_TID_MASK_VALUE_ADDR,v)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TID_MASK_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_1_TID_MASK_VALUE_ADDR,m,v,HWIO_ECPRI_XBAR_C2C_TPDM_1_TID_MASK_VALUE_IN)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TID_MASK_VALUE_VALUE_BMSK                     0xffff0000
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TID_MASK_VALUE_VALUE_SHFT                           0x10
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TID_MASK_VALUE_MASK_BMSK                          0xffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_TID_MASK_VALUE_MASK_SHFT                             0x0

#define HWIO_ECPRI_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_ADDR                          (ECPRI_XBAR_REGS_REG_BASE      + 0x00000278)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_PHYS                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000278)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_OFFS                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000278)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_RMSK                             0x3ffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_ATTR                                 0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_ADDR, HWIO_ECPRI_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_ADDR, m)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_ADDR,v)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_ADDR,m,v,HWIO_ECPRI_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_IN)
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_TERROR_VALUE_BMSK                0x20000
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_TERROR_VALUE_SHFT                   0x11
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_TERROR_MASK_BMSK                 0x10000
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_TERROR_MASK_SHFT                    0x10
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_TDEST_VALUE_BMSK                  0xff00
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_TDEST_VALUE_SHFT                     0x8
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_TDEST_MASK_BMSK                     0xff
#define HWIO_ECPRI_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_TDEST_MASK_SHFT                      0x0

#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_ADDR                                      (ECPRI_XBAR_REGS_REG_BASE      + 0x00000280)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_PHYS                                      (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000280)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_OFFS                                      (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000280)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_RMSK                                         0x1ff0f
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_ATTR                                             0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_ADDR, HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_ADDR, m)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_ADDR,v)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_ADDR,m,v,HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_IN)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_VALID_BMSK                     0x10000
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_VALID_SHFT                        0x10
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_BMSK                     0xff00
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_SHFT                        0x8
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_FHRX_FVAL              0x0
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_C2CRX_FVAL             0x1
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_OCRX_FVAL              0x2
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_DMA_FVAL               0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_UC_FVAL                0x4
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_BEFORE_LUT_FVAL            0x10
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_AFTER_LUT_FVAL             0x11
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_ALL_FVAL              0xff
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_ID_BMSK                            0xf
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_ID_SHFT                            0x0
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_ID_C2CTX_0_FVAL                    0x0
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_ID_C2CTX_1_FVAL                    0x1
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_ID_C2CTX_2_FVAL                    0x2
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_ID_C2CRX_0_FVAL                    0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_ID_C2CRX_1_FVAL                    0x4
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_ID_C2CRX_2_FVAL                    0x5
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_ID_DMA_TO_C2C_FVAL                 0x6
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_ID_C2C0_TO_DMA_FVAL                0x7
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_ID_C2C1_TO_DMA_FVAL                0x8
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_ID_C2C2_TO_DMA_FVAL                0x9

#define HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_MASK_m_ADDR(m)                           (ECPRI_XBAR_REGS_REG_BASE      + 0x00000284 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_MASK_m_PHYS(m)                           (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000284 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_MASK_m_OFFS(m)                           (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000284 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_MASK_m_RMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_MASK_m_MAXm                                       3
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_MASK_m_ATTR                                     0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_MASK_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_MASK_m_ADDR(m), HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_MASK_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_MASK_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_MASK_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_MASK_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_MASK_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_MASK_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_MASK_m_INI(m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_MASK_m_MASK_BMSK                         0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_MASK_m_MASK_SHFT                                0x0

#define HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_VALUE_m_ADDR(m)                          (ECPRI_XBAR_REGS_REG_BASE      + 0x00000294 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_VALUE_m_PHYS(m)                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000294 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_VALUE_m_OFFS(m)                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000294 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_VALUE_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_VALUE_m_MAXm                                      3
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_VALUE_m_ATTR                                    0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_VALUE_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_VALUE_m_ADDR(m), HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_VALUE_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_VALUE_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_VALUE_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_VALUE_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_VALUE_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_VALUE_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_VALUE_m_INI(m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_VALUE_m_VALUE_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_DATA_VALUE_m_VALUE_SHFT                              0x0

#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_MASK_m_ADDR(m)                          (ECPRI_XBAR_REGS_REG_BASE      + 0x000002a4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_MASK_m_PHYS(m)                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000002a4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_MASK_m_OFFS(m)                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000002a4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_MASK_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_MASK_m_MAXm                                      1
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_MASK_m_ATTR                                    0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_MASK_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_MASK_m_ADDR(m), HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_MASK_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_MASK_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_MASK_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_MASK_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_MASK_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_MASK_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_MASK_m_INI(m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_MASK_m_MASK_BMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_MASK_m_MASK_SHFT                               0x0

#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_VALUE_m_ADDR(m)                         (ECPRI_XBAR_REGS_REG_BASE      + 0x000002ac + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_VALUE_m_PHYS(m)                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000002ac + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_VALUE_m_OFFS(m)                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000002ac + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_VALUE_m_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_VALUE_m_MAXm                                     1
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_VALUE_m_ATTR                                   0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_VALUE_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_VALUE_m_ADDR(m), HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_VALUE_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_VALUE_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_VALUE_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_VALUE_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_VALUE_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_VALUE_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_VALUE_m_INI(m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_VALUE_m_VALUE_BMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TUSER_VALUE_m_VALUE_SHFT                             0x0

#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TID_MASK_VALUE_ADDR                           (ECPRI_XBAR_REGS_REG_BASE      + 0x000002b4)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TID_MASK_VALUE_PHYS                           (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000002b4)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TID_MASK_VALUE_OFFS                           (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000002b4)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TID_MASK_VALUE_RMSK                           0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TID_MASK_VALUE_ATTR                                  0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TID_MASK_VALUE_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_2_TID_MASK_VALUE_ADDR, HWIO_ECPRI_XBAR_C2C_TPDM_2_TID_MASK_VALUE_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TID_MASK_VALUE_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_2_TID_MASK_VALUE_ADDR, m)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TID_MASK_VALUE_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_2_TID_MASK_VALUE_ADDR,v)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TID_MASK_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_2_TID_MASK_VALUE_ADDR,m,v,HWIO_ECPRI_XBAR_C2C_TPDM_2_TID_MASK_VALUE_IN)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TID_MASK_VALUE_VALUE_BMSK                     0xffff0000
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TID_MASK_VALUE_VALUE_SHFT                           0x10
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TID_MASK_VALUE_MASK_BMSK                          0xffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_TID_MASK_VALUE_MASK_SHFT                             0x0

#define HWIO_ECPRI_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_ADDR                          (ECPRI_XBAR_REGS_REG_BASE      + 0x000002b8)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_PHYS                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000002b8)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_OFFS                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000002b8)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_RMSK                             0x3ffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_ATTR                                 0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_ADDR, HWIO_ECPRI_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_ADDR, m)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_ADDR,v)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_ADDR,m,v,HWIO_ECPRI_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_IN)
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_TERROR_VALUE_BMSK                0x20000
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_TERROR_VALUE_SHFT                   0x11
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_TERROR_MASK_BMSK                 0x10000
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_TERROR_MASK_SHFT                    0x10
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_TDEST_VALUE_BMSK                  0xff00
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_TDEST_VALUE_SHFT                     0x8
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_TDEST_MASK_BMSK                     0xff
#define HWIO_ECPRI_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_TDEST_MASK_SHFT                      0x0

#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_ADDR                                      (ECPRI_XBAR_REGS_REG_BASE      + 0x000002c0)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_PHYS                                      (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000002c0)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_OFFS                                      (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000002c0)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_RMSK                                         0x1ff0f
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_ATTR                                             0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_ADDR, HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_ADDR, m)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_ADDR,v)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_ADDR,m,v,HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_IN)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_VALID_BMSK                     0x10000
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_VALID_SHFT                        0x10
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_BMSK                     0xff00
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_SHFT                        0x8
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_FHRX_FVAL              0x0
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_C2CRX_FVAL             0x1
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_OCRX_FVAL              0x2
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_DMA_FVAL               0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_UC_FVAL                0x4
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_BEFORE_LUT_FVAL            0x10
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_AFTER_LUT_FVAL             0x11
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_ALL_FVAL              0xff
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_ID_BMSK                            0xf
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_ID_SHFT                            0x0
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_ID_C2CTX_0_FVAL                    0x0
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_ID_C2CTX_1_FVAL                    0x1
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_ID_C2CTX_2_FVAL                    0x2
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_ID_C2CRX_0_FVAL                    0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_ID_C2CRX_1_FVAL                    0x4
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_ID_C2CRX_2_FVAL                    0x5
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_ID_DMA_TO_C2C_FVAL                 0x6
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_ID_C2C0_TO_DMA_FVAL                0x7
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_ID_C2C1_TO_DMA_FVAL                0x8
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_ID_C2C2_TO_DMA_FVAL                0x9

#define HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_MASK_m_ADDR(m)                           (ECPRI_XBAR_REGS_REG_BASE      + 0x000002c4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_MASK_m_PHYS(m)                           (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000002c4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_MASK_m_OFFS(m)                           (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000002c4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_MASK_m_RMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_MASK_m_MAXm                                       3
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_MASK_m_ATTR                                     0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_MASK_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_MASK_m_ADDR(m), HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_MASK_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_MASK_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_MASK_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_MASK_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_MASK_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_MASK_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_MASK_m_INI(m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_MASK_m_MASK_BMSK                         0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_MASK_m_MASK_SHFT                                0x0

#define HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_VALUE_m_ADDR(m)                          (ECPRI_XBAR_REGS_REG_BASE      + 0x000002d4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_VALUE_m_PHYS(m)                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000002d4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_VALUE_m_OFFS(m)                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000002d4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_VALUE_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_VALUE_m_MAXm                                      3
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_VALUE_m_ATTR                                    0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_VALUE_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_VALUE_m_ADDR(m), HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_VALUE_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_VALUE_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_VALUE_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_VALUE_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_VALUE_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_VALUE_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_VALUE_m_INI(m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_VALUE_m_VALUE_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_DATA_VALUE_m_VALUE_SHFT                              0x0

#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_MASK_m_ADDR(m)                          (ECPRI_XBAR_REGS_REG_BASE      + 0x000002e4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_MASK_m_PHYS(m)                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000002e4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_MASK_m_OFFS(m)                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000002e4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_MASK_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_MASK_m_MAXm                                      1
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_MASK_m_ATTR                                    0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_MASK_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_MASK_m_ADDR(m), HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_MASK_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_MASK_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_MASK_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_MASK_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_MASK_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_MASK_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_MASK_m_INI(m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_MASK_m_MASK_BMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_MASK_m_MASK_SHFT                               0x0

#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_VALUE_m_ADDR(m)                         (ECPRI_XBAR_REGS_REG_BASE      + 0x000002ec + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_VALUE_m_PHYS(m)                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000002ec + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_VALUE_m_OFFS(m)                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000002ec + 0x4 * (m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_VALUE_m_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_VALUE_m_MAXm                                     1
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_VALUE_m_ATTR                                   0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_VALUE_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_VALUE_m_ADDR(m), HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_VALUE_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_VALUE_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_VALUE_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_VALUE_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_VALUE_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_VALUE_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_VALUE_m_INI(m))
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_VALUE_m_VALUE_BMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TUSER_VALUE_m_VALUE_SHFT                             0x0

#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TID_MASK_VALUE_ADDR                           (ECPRI_XBAR_REGS_REG_BASE      + 0x000002f4)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TID_MASK_VALUE_PHYS                           (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000002f4)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TID_MASK_VALUE_OFFS                           (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000002f4)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TID_MASK_VALUE_RMSK                           0xffffffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TID_MASK_VALUE_ATTR                                  0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TID_MASK_VALUE_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_3_TID_MASK_VALUE_ADDR, HWIO_ECPRI_XBAR_C2C_TPDM_3_TID_MASK_VALUE_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TID_MASK_VALUE_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_3_TID_MASK_VALUE_ADDR, m)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TID_MASK_VALUE_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_3_TID_MASK_VALUE_ADDR,v)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TID_MASK_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_3_TID_MASK_VALUE_ADDR,m,v,HWIO_ECPRI_XBAR_C2C_TPDM_3_TID_MASK_VALUE_IN)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TID_MASK_VALUE_VALUE_BMSK                     0xffff0000
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TID_MASK_VALUE_VALUE_SHFT                           0x10
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TID_MASK_VALUE_MASK_BMSK                          0xffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_TID_MASK_VALUE_MASK_SHFT                             0x0

#define HWIO_ECPRI_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_ADDR                          (ECPRI_XBAR_REGS_REG_BASE      + 0x000002f8)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_PHYS                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000002f8)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_OFFS                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000002f8)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_RMSK                             0x3ffff
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_ATTR                                 0x3
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_ADDR, HWIO_ECPRI_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_RMSK)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_ADDR, m)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_ADDR,v)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_ADDR,m,v,HWIO_ECPRI_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_IN)
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_TERROR_VALUE_BMSK                0x20000
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_TERROR_VALUE_SHFT                   0x11
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_TERROR_MASK_BMSK                 0x10000
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_TERROR_MASK_SHFT                    0x10
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_TDEST_VALUE_BMSK                  0xff00
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_TDEST_VALUE_SHFT                     0x8
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_TDEST_MASK_BMSK                     0xff
#define HWIO_ECPRI_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_TDEST_MASK_SHFT                      0x0

#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_ADDR                                     (ECPRI_XBAR_REGS_REG_BASE      + 0x00000300)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_PHYS                                     (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000300)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_OFFS                                     (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000300)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_RMSK                                        0x1ff0f
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_ATTR                                            0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_ADDR, HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_ADDR, m)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_ADDR,v)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_ADDR,m,v,HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_IN)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_VALID_BMSK                    0x10000
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_VALID_SHFT                       0x10
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_BMSK                    0xff00
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_SHFT                       0x8
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_FHRX_FVAL             0x0
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_C2CRX_FVAL            0x1
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_OCRX_FVAL             0x2
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_DMA_FVAL              0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_UC_FVAL               0x4
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_BEFORE_LUT_FVAL           0x10
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_AFTER_LUT_FVAL            0x11
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_ALL_FVAL             0xff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_ID_BMSK                           0xf
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_ID_SHFT                           0x0
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_ID_OCTX_0_FVAL                    0x0
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_ID_OCTX_1_FVAL                    0x1
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_ID_OCTX_2_FVAL                    0x2
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_ID_OCTX_3_FVAL                    0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_ID_OCRX_0_FVAL                    0x4
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_ID_OCRX_1_FVAL                    0x5
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_ID_OCRX_2_FVAL                    0x6
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_ID_OCRX_3_FVAL                    0x7

#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_MASK_m_ADDR(m)                          (ECPRI_XBAR_REGS_REG_BASE      + 0x00000304 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_MASK_m_PHYS(m)                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000304 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_MASK_m_OFFS(m)                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000304 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_MASK_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_MASK_m_MAXm                                      3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_MASK_m_ATTR                                    0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_MASK_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_MASK_m_ADDR(m), HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_MASK_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_MASK_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_MASK_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_MASK_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_MASK_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_MASK_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_MASK_m_INI(m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_MASK_m_MASK_BMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_MASK_m_MASK_SHFT                               0x0

#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_VALUE_m_ADDR(m)                         (ECPRI_XBAR_REGS_REG_BASE      + 0x00000314 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_VALUE_m_PHYS(m)                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000314 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_VALUE_m_OFFS(m)                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000314 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_VALUE_m_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_VALUE_m_MAXm                                     3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_VALUE_m_ATTR                                   0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_VALUE_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_VALUE_m_ADDR(m), HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_VALUE_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_VALUE_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_VALUE_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_VALUE_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_VALUE_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_VALUE_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_VALUE_m_INI(m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_VALUE_m_VALUE_BMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_DATA_VALUE_m_VALUE_SHFT                             0x0

#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_MASK_m_ADDR(m)                         (ECPRI_XBAR_REGS_REG_BASE      + 0x00000324 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_MASK_m_PHYS(m)                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000324 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_MASK_m_OFFS(m)                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000324 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_MASK_m_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_MASK_m_MAXm                                     1
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_MASK_m_ATTR                                   0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_MASK_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_MASK_m_ADDR(m), HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_MASK_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_MASK_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_MASK_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_MASK_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_MASK_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_MASK_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_MASK_m_INI(m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_MASK_m_MASK_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_MASK_m_MASK_SHFT                              0x0

#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_ADDR(m)                        (ECPRI_XBAR_REGS_REG_BASE      + 0x0000032c + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_PHYS(m)                        (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x0000032c + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_OFFS(m)                        (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x0000032c + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_RMSK                           0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_MAXm                                    1
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_ATTR                                  0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_ADDR(m), HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_INI(m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_VALUE_BMSK                     0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_VALUE_SHFT                            0x0

#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_ADDR                          (ECPRI_XBAR_REGS_REG_BASE      + 0x00000334)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_PHYS                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000334)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_OFFS                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000334)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_RMSK                          0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_ATTR                                 0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_ADDR, HWIO_ECPRI_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_ADDR, m)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_ADDR,v)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_ADDR,m,v,HWIO_ECPRI_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_IN)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_VALUE_BMSK                    0xffff0000
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_VALUE_SHFT                          0x10
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_MASK_BMSK                         0xffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_MASK_SHFT                            0x0

#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_ADDR                         (ECPRI_XBAR_REGS_REG_BASE      + 0x00000338)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_PHYS                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000338)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_OFFS                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000338)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_RMSK                            0x3ffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_ATTR                                0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_ADDR, HWIO_ECPRI_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_ADDR, m)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_ADDR,v)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_ADDR,m,v,HWIO_ECPRI_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_IN)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_TERROR_VALUE_BMSK               0x20000
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_TERROR_VALUE_SHFT                  0x11
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_TERROR_MASK_BMSK                0x10000
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_TERROR_MASK_SHFT                   0x10
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_TDEST_VALUE_BMSK                 0xff00
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_TDEST_VALUE_SHFT                    0x8
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_TDEST_MASK_BMSK                    0xff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_TDEST_MASK_SHFT                     0x0

#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_ADDR                                     (ECPRI_XBAR_REGS_REG_BASE      + 0x00000340)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_PHYS                                     (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000340)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_OFFS                                     (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000340)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_RMSK                                        0x1ff0f
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_ATTR                                            0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_ADDR, HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_ADDR, m)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_ADDR,v)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_ADDR,m,v,HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_IN)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_VALID_BMSK                    0x10000
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_VALID_SHFT                       0x10
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_BMSK                    0xff00
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_SHFT                       0x8
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_FHRX_FVAL             0x0
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_C2CRX_FVAL            0x1
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_OCRX_FVAL             0x2
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_DMA_FVAL              0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_UC_FVAL               0x4
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_BEFORE_LUT_FVAL           0x10
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_AFTER_LUT_FVAL            0x11
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_ALL_FVAL             0xff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_ID_BMSK                           0xf
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_ID_SHFT                           0x0
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_ID_OCTX_0_FVAL                    0x0
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_ID_OCTX_1_FVAL                    0x1
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_ID_OCTX_2_FVAL                    0x2
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_ID_OCTX_3_FVAL                    0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_ID_OCRX_0_FVAL                    0x4
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_ID_OCRX_1_FVAL                    0x5
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_ID_OCRX_2_FVAL                    0x6
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_ID_OCRX_3_FVAL                    0x7

#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_MASK_m_ADDR(m)                          (ECPRI_XBAR_REGS_REG_BASE      + 0x00000344 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_MASK_m_PHYS(m)                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000344 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_MASK_m_OFFS(m)                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000344 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_MASK_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_MASK_m_MAXm                                      3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_MASK_m_ATTR                                    0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_MASK_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_MASK_m_ADDR(m), HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_MASK_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_MASK_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_MASK_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_MASK_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_MASK_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_MASK_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_MASK_m_INI(m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_MASK_m_MASK_BMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_MASK_m_MASK_SHFT                               0x0

#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_VALUE_m_ADDR(m)                         (ECPRI_XBAR_REGS_REG_BASE      + 0x00000354 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_VALUE_m_PHYS(m)                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000354 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_VALUE_m_OFFS(m)                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000354 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_VALUE_m_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_VALUE_m_MAXm                                     3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_VALUE_m_ATTR                                   0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_VALUE_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_VALUE_m_ADDR(m), HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_VALUE_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_VALUE_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_VALUE_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_VALUE_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_VALUE_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_VALUE_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_VALUE_m_INI(m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_VALUE_m_VALUE_BMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_DATA_VALUE_m_VALUE_SHFT                             0x0

#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_MASK_m_ADDR(m)                         (ECPRI_XBAR_REGS_REG_BASE      + 0x00000364 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_MASK_m_PHYS(m)                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000364 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_MASK_m_OFFS(m)                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000364 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_MASK_m_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_MASK_m_MAXm                                     1
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_MASK_m_ATTR                                   0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_MASK_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_MASK_m_ADDR(m), HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_MASK_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_MASK_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_MASK_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_MASK_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_MASK_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_MASK_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_MASK_m_INI(m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_MASK_m_MASK_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_MASK_m_MASK_SHFT                              0x0

#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_ADDR(m)                        (ECPRI_XBAR_REGS_REG_BASE      + 0x0000036c + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_PHYS(m)                        (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x0000036c + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_OFFS(m)                        (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x0000036c + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_RMSK                           0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_MAXm                                    1
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_ATTR                                  0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_ADDR(m), HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_INI(m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_VALUE_BMSK                     0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_VALUE_SHFT                            0x0

#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_ADDR                          (ECPRI_XBAR_REGS_REG_BASE      + 0x00000374)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_PHYS                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000374)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_OFFS                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000374)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_RMSK                          0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_ATTR                                 0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_ADDR, HWIO_ECPRI_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_ADDR, m)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_ADDR,v)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_ADDR,m,v,HWIO_ECPRI_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_IN)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_VALUE_BMSK                    0xffff0000
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_VALUE_SHFT                          0x10
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_MASK_BMSK                         0xffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_MASK_SHFT                            0x0

#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_ADDR                         (ECPRI_XBAR_REGS_REG_BASE      + 0x00000378)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_PHYS                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000378)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_OFFS                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000378)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_RMSK                            0x3ffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_ATTR                                0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_ADDR, HWIO_ECPRI_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_ADDR, m)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_ADDR,v)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_ADDR,m,v,HWIO_ECPRI_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_IN)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_TERROR_VALUE_BMSK               0x20000
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_TERROR_VALUE_SHFT                  0x11
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_TERROR_MASK_BMSK                0x10000
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_TERROR_MASK_SHFT                   0x10
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_TDEST_VALUE_BMSK                 0xff00
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_TDEST_VALUE_SHFT                    0x8
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_TDEST_MASK_BMSK                    0xff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_TDEST_MASK_SHFT                     0x0

#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_ADDR                                     (ECPRI_XBAR_REGS_REG_BASE      + 0x00000380)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_PHYS                                     (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000380)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_OFFS                                     (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000380)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_RMSK                                        0x1ff0f
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_ATTR                                            0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_ADDR, HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_ADDR, m)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_ADDR,v)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_ADDR,m,v,HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_IN)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_VALID_BMSK                    0x10000
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_VALID_SHFT                       0x10
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_BMSK                    0xff00
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_SHFT                       0x8
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_FHRX_FVAL             0x0
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_C2CRX_FVAL            0x1
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_OCRX_FVAL             0x2
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_DMA_FVAL              0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_UC_FVAL               0x4
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_BEFORE_LUT_FVAL           0x10
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_AFTER_LUT_FVAL            0x11
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_ALL_FVAL             0xff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_ID_BMSK                           0xf
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_ID_SHFT                           0x0
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_ID_OCTX_0_FVAL                    0x0
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_ID_OCTX_1_FVAL                    0x1
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_ID_OCTX_2_FVAL                    0x2
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_ID_OCTX_3_FVAL                    0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_ID_OCRX_0_FVAL                    0x4
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_ID_OCRX_1_FVAL                    0x5
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_ID_OCRX_2_FVAL                    0x6
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_ID_OCRX_3_FVAL                    0x7

#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_MASK_m_ADDR(m)                          (ECPRI_XBAR_REGS_REG_BASE      + 0x00000384 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_MASK_m_PHYS(m)                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000384 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_MASK_m_OFFS(m)                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000384 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_MASK_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_MASK_m_MAXm                                      3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_MASK_m_ATTR                                    0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_MASK_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_MASK_m_ADDR(m), HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_MASK_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_MASK_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_MASK_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_MASK_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_MASK_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_MASK_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_MASK_m_INI(m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_MASK_m_MASK_BMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_MASK_m_MASK_SHFT                               0x0

#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_VALUE_m_ADDR(m)                         (ECPRI_XBAR_REGS_REG_BASE      + 0x00000394 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_VALUE_m_PHYS(m)                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000394 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_VALUE_m_OFFS(m)                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000394 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_VALUE_m_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_VALUE_m_MAXm                                     3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_VALUE_m_ATTR                                   0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_VALUE_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_VALUE_m_ADDR(m), HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_VALUE_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_VALUE_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_VALUE_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_VALUE_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_VALUE_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_VALUE_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_VALUE_m_INI(m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_VALUE_m_VALUE_BMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_DATA_VALUE_m_VALUE_SHFT                             0x0

#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_MASK_m_ADDR(m)                         (ECPRI_XBAR_REGS_REG_BASE      + 0x000003a4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_MASK_m_PHYS(m)                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000003a4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_MASK_m_OFFS(m)                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000003a4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_MASK_m_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_MASK_m_MAXm                                     1
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_MASK_m_ATTR                                   0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_MASK_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_MASK_m_ADDR(m), HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_MASK_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_MASK_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_MASK_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_MASK_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_MASK_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_MASK_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_MASK_m_INI(m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_MASK_m_MASK_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_MASK_m_MASK_SHFT                              0x0

#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_ADDR(m)                        (ECPRI_XBAR_REGS_REG_BASE      + 0x000003ac + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_PHYS(m)                        (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000003ac + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_OFFS(m)                        (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000003ac + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_RMSK                           0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_MAXm                                    1
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_ATTR                                  0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_ADDR(m), HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_INI(m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_VALUE_BMSK                     0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_VALUE_SHFT                            0x0

#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_ADDR                          (ECPRI_XBAR_REGS_REG_BASE      + 0x000003b4)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_PHYS                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000003b4)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_OFFS                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000003b4)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_RMSK                          0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_ATTR                                 0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_ADDR, HWIO_ECPRI_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_ADDR, m)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_ADDR,v)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_ADDR,m,v,HWIO_ECPRI_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_IN)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_VALUE_BMSK                    0xffff0000
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_VALUE_SHFT                          0x10
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_MASK_BMSK                         0xffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_MASK_SHFT                            0x0

#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_ADDR                         (ECPRI_XBAR_REGS_REG_BASE      + 0x000003b8)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_PHYS                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000003b8)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_OFFS                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000003b8)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_RMSK                            0x3ffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_ATTR                                0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_ADDR, HWIO_ECPRI_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_ADDR, m)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_ADDR,v)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_ADDR,m,v,HWIO_ECPRI_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_IN)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_TERROR_VALUE_BMSK               0x20000
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_TERROR_VALUE_SHFT                  0x11
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_TERROR_MASK_BMSK                0x10000
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_TERROR_MASK_SHFT                   0x10
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_TDEST_VALUE_BMSK                 0xff00
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_TDEST_VALUE_SHFT                    0x8
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_TDEST_MASK_BMSK                    0xff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_TDEST_MASK_SHFT                     0x0

#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_ADDR                                     (ECPRI_XBAR_REGS_REG_BASE      + 0x000003c0)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_PHYS                                     (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000003c0)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_OFFS                                     (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000003c0)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_RMSK                                        0x1ff0f
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_ATTR                                            0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_ADDR, HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_ADDR, m)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_ADDR,v)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_ADDR,m,v,HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_IN)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_VALID_BMSK                    0x10000
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_VALID_SHFT                       0x10
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_BMSK                    0xff00
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_SHFT                       0x8
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_FHRX_FVAL             0x0
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_C2CRX_FVAL            0x1
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_OCRX_FVAL             0x2
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_DMA_FVAL              0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_UC_FVAL               0x4
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_BEFORE_LUT_FVAL           0x10
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_AFTER_LUT_FVAL            0x11
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_ALL_FVAL             0xff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_ID_BMSK                           0xf
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_ID_SHFT                           0x0
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_ID_OCTX_0_FVAL                    0x0
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_ID_OCTX_1_FVAL                    0x1
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_ID_OCTX_2_FVAL                    0x2
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_ID_OCTX_3_FVAL                    0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_ID_OCRX_0_FVAL                    0x4
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_ID_OCRX_1_FVAL                    0x5
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_ID_OCRX_2_FVAL                    0x6
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_ID_OCRX_3_FVAL                    0x7

#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_MASK_m_ADDR(m)                          (ECPRI_XBAR_REGS_REG_BASE      + 0x000003c4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_MASK_m_PHYS(m)                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000003c4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_MASK_m_OFFS(m)                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000003c4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_MASK_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_MASK_m_MAXm                                      3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_MASK_m_ATTR                                    0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_MASK_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_MASK_m_ADDR(m), HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_MASK_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_MASK_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_MASK_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_MASK_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_MASK_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_MASK_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_MASK_m_INI(m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_MASK_m_MASK_BMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_MASK_m_MASK_SHFT                               0x0

#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_VALUE_m_ADDR(m)                         (ECPRI_XBAR_REGS_REG_BASE      + 0x000003d4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_VALUE_m_PHYS(m)                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000003d4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_VALUE_m_OFFS(m)                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000003d4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_VALUE_m_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_VALUE_m_MAXm                                     3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_VALUE_m_ATTR                                   0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_VALUE_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_VALUE_m_ADDR(m), HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_VALUE_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_VALUE_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_VALUE_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_VALUE_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_VALUE_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_VALUE_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_VALUE_m_INI(m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_VALUE_m_VALUE_BMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_DATA_VALUE_m_VALUE_SHFT                             0x0

#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_MASK_m_ADDR(m)                         (ECPRI_XBAR_REGS_REG_BASE      + 0x000003e4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_MASK_m_PHYS(m)                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000003e4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_MASK_m_OFFS(m)                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000003e4 + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_MASK_m_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_MASK_m_MAXm                                     1
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_MASK_m_ATTR                                   0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_MASK_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_MASK_m_ADDR(m), HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_MASK_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_MASK_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_MASK_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_MASK_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_MASK_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_MASK_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_MASK_m_INI(m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_MASK_m_MASK_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_MASK_m_MASK_SHFT                              0x0

#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_ADDR(m)                        (ECPRI_XBAR_REGS_REG_BASE      + 0x000003ec + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_PHYS(m)                        (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000003ec + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_OFFS(m)                        (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000003ec + 0x4 * (m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_RMSK                           0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_MAXm                                    1
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_ATTR                                  0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_INI(m)        \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_ADDR(m), HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_INMI(m,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_ADDR(m), mask)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_OUTI(m,val)    \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_ADDR(m),val)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_ADDR(m),mask,val,HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_INI(m))
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_VALUE_BMSK                     0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_VALUE_SHFT                            0x0

#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_ADDR                          (ECPRI_XBAR_REGS_REG_BASE      + 0x000003f4)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_PHYS                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000003f4)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_OFFS                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000003f4)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_RMSK                          0xffffffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_ATTR                                 0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_ADDR, HWIO_ECPRI_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_ADDR, m)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_ADDR,v)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_ADDR,m,v,HWIO_ECPRI_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_IN)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_VALUE_BMSK                    0xffff0000
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_VALUE_SHFT                          0x10
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_MASK_BMSK                         0xffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_MASK_SHFT                            0x0

#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_ADDR                         (ECPRI_XBAR_REGS_REG_BASE      + 0x000003f8)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_PHYS                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000003f8)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_OFFS                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000003f8)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_RMSK                            0x3ffff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_ATTR                                0x3
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_ADDR, HWIO_ECPRI_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_RMSK)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_ADDR, m)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_ADDR,v)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_ADDR,m,v,HWIO_ECPRI_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_IN)
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_TERROR_VALUE_BMSK               0x20000
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_TERROR_VALUE_SHFT                  0x11
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_TERROR_MASK_BMSK                0x10000
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_TERROR_MASK_SHFT                   0x10
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_TDEST_VALUE_BMSK                 0xff00
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_TDEST_VALUE_SHFT                    0x8
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_TDEST_MASK_BMSK                    0xff
#define HWIO_ECPRI_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_TDEST_MASK_SHFT                     0x0

#define HWIO_ECPRI_XBAR_TPDM_GLOBAL_CFG_ADDR                                     (ECPRI_XBAR_REGS_REG_BASE      + 0x00000400)
#define HWIO_ECPRI_XBAR_TPDM_GLOBAL_CFG_PHYS                                     (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000400)
#define HWIO_ECPRI_XBAR_TPDM_GLOBAL_CFG_OFFS                                     (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000400)
#define HWIO_ECPRI_XBAR_TPDM_GLOBAL_CFG_RMSK                                            0x1
#define HWIO_ECPRI_XBAR_TPDM_GLOBAL_CFG_ATTR                                            0x3
#define HWIO_ECPRI_XBAR_TPDM_GLOBAL_CFG_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_TPDM_GLOBAL_CFG_ADDR, HWIO_ECPRI_XBAR_TPDM_GLOBAL_CFG_RMSK)
#define HWIO_ECPRI_XBAR_TPDM_GLOBAL_CFG_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_TPDM_GLOBAL_CFG_ADDR, m)
#define HWIO_ECPRI_XBAR_TPDM_GLOBAL_CFG_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_TPDM_GLOBAL_CFG_ADDR,v)
#define HWIO_ECPRI_XBAR_TPDM_GLOBAL_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_TPDM_GLOBAL_CFG_ADDR,m,v,HWIO_ECPRI_XBAR_TPDM_GLOBAL_CFG_IN)
#define HWIO_ECPRI_XBAR_TPDM_GLOBAL_CFG_SHARED_DATA_MODE_BMSK                           0x1
#define HWIO_ECPRI_XBAR_TPDM_GLOBAL_CFG_SHARED_DATA_MODE_SHFT                           0x0

#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_CFG_ADDR                            (ECPRI_XBAR_REGS_REG_BASE      + 0x00000800)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_CFG_PHYS                            (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000800)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_CFG_OFFS                            (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000800)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_CFG_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_CFG_ATTR                                   0x3
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_CFG_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_CFG_ADDR, HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_CFG_RMSK)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_CFG_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_CFG_ADDR, m)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_CFG_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_CFG_ADDR,v)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_CFG_ADDR,m,v,HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_CFG_IN)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_CFG_VALUE_3_BMSK                    0xff000000
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_CFG_VALUE_3_SHFT                          0x18
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_CFG_VALUE_2_BMSK                      0xff0000
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_CFG_VALUE_2_SHFT                          0x10
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_CFG_VALUE_1_BMSK                        0xff00
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_CFG_VALUE_1_SHFT                           0x8
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_CFG_VALUE_0_BMSK                          0xff
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_CFG_VALUE_0_SHFT                           0x0

#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_VALID_ADDR                          (ECPRI_XBAR_REGS_REG_BASE      + 0x00000804)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_VALID_PHYS                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000804)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_VALID_OFFS                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000804)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_VALID_RMSK                                 0xf
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_VALID_ATTR                                 0x3
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_VALID_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_VALID_ADDR, HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_VALID_RMSK)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_VALID_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_VALID_ADDR, m)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_VALID_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_VALID_ADDR,v)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_VALID_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_VALID_ADDR,m,v,HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_VALID_IN)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_VALID_VALID_3_BMSK                         0x8
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_VALID_VALID_3_SHFT                         0x3
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_VALID_VALID_2_BMSK                         0x4
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_VALID_VALID_2_SHFT                         0x2
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_VALID_VALID_1_BMSK                         0x2
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_VALID_VALID_1_SHFT                         0x1
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_VALID_VALID_0_BMSK                         0x1
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_UPLANE_VALID_VALID_0_SHFT                         0x0

#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_CFG_ADDR                            (ECPRI_XBAR_REGS_REG_BASE      + 0x00000808)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_CFG_PHYS                            (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000808)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_CFG_OFFS                            (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000808)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_CFG_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_CFG_ATTR                                   0x3
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_CFG_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_CFG_ADDR, HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_CFG_RMSK)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_CFG_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_CFG_ADDR, m)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_CFG_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_CFG_ADDR,v)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_CFG_ADDR,m,v,HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_CFG_IN)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_CFG_VALUE_3_BMSK                    0xff000000
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_CFG_VALUE_3_SHFT                          0x18
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_CFG_VALUE_2_BMSK                      0xff0000
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_CFG_VALUE_2_SHFT                          0x10
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_CFG_VALUE_1_BMSK                        0xff00
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_CFG_VALUE_1_SHFT                           0x8
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_CFG_VALUE_0_BMSK                          0xff
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_CFG_VALUE_0_SHFT                           0x0

#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_VALID_ADDR                          (ECPRI_XBAR_REGS_REG_BASE      + 0x0000080c)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_VALID_PHYS                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x0000080c)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_VALID_OFFS                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x0000080c)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_VALID_RMSK                                 0xf
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_VALID_ATTR                                 0x3
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_VALID_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_VALID_ADDR, HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_VALID_RMSK)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_VALID_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_VALID_ADDR, m)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_VALID_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_VALID_ADDR,v)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_VALID_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_VALID_ADDR,m,v,HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_VALID_IN)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_VALID_VALID_3_BMSK                         0x8
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_VALID_VALID_3_SHFT                         0x3
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_VALID_VALID_2_BMSK                         0x4
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_VALID_VALID_2_SHFT                         0x2
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_VALID_VALID_1_BMSK                         0x2
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_VALID_VALID_1_SHFT                         0x1
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_VALID_VALID_0_BMSK                         0x1
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_CPLANE_VALID_VALID_0_SHFT                         0x0

#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_ADDR(n)                               (ECPRI_XBAR_REGS_REG_BASE      + 0x00000810 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_PHYS(n)                               (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000810 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_OFFS(n)                               (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000810 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_RMSK                                      0x7fff
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_MAXn                                           2
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_ATTR                                         0x3
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_ADDR(n), HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_RMSK)
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_OUTI(n,val)    \
        out_dword(HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_ADDR(n),val)
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_ADDR(n),mask,val,HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_INI(n))
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_OTHER_ROUTE_TO_DMA_BMSK                   0x4000
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_OTHER_ROUTE_TO_DMA_SHFT                      0xe
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_OTHER_ROUTE_TO_C2C_BMSK                   0x2000
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_OTHER_ROUTE_TO_C2C_SHFT                      0xd
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_OTHER_ROUTE_TO_ORAN_BMSK                  0x1000
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_OTHER_ROUTE_TO_ORAN_SHFT                     0xc
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_OTHER_OC_LINK_ID_BMSK                      0xc00
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_OTHER_OC_LINK_ID_SHFT                        0xa
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_DL_ROUTE_TO_DMA_BMSK                       0x200
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_DL_ROUTE_TO_DMA_SHFT                         0x9
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_DL_ROUTE_TO_C2C_BMSK                       0x100
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_DL_ROUTE_TO_C2C_SHFT                         0x8
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_DL_ROUTE_TO_ORAN_BMSK                       0x80
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_DL_ROUTE_TO_ORAN_SHFT                        0x7
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_DL_OC_LINK_ID_BMSK                          0x60
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_DL_OC_LINK_ID_SHFT                           0x5
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_UL_ROUTE_TO_DMA_BMSK                        0x10
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_UL_ROUTE_TO_DMA_SHFT                         0x4
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_UL_ROUTE_TO_C2C_BMSK                         0x8
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_UL_ROUTE_TO_C2C_SHFT                         0x3
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_UL_ROUTE_TO_ORAN_BMSK                        0x4
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_UL_ROUTE_TO_ORAN_SHFT                        0x2
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_UL_OC_LINK_ID_BMSK                           0x3
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_LUT_UL_OC_LINK_ID_SHFT                           0x0

#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_DMA_CHANNEL_ADDR(n)                       (ECPRI_XBAR_REGS_REG_BASE      + 0x00000820 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_DMA_CHANNEL_PHYS(n)                       (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000820 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_DMA_CHANNEL_OFFS(n)                       (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000820 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_DMA_CHANNEL_RMSK                               0x37f
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_DMA_CHANNEL_MAXn                                   2
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_DMA_CHANNEL_ATTR                                 0x3
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_DMA_CHANNEL_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_DMA_CHANNEL_ADDR(n), HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_DMA_CHANNEL_RMSK)
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_DMA_CHANNEL_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_DMA_CHANNEL_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_DMA_CHANNEL_OUTI(n,val)    \
        out_dword(HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_DMA_CHANNEL_ADDR(n),val)
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_DMA_CHANNEL_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_DMA_CHANNEL_ADDR(n),mask,val,HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_DMA_CHANNEL_INI(n))
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_DMA_CHANNEL_GSI_ID_BMSK                        0x300
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_DMA_CHANNEL_GSI_ID_SHFT                          0x8
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_DMA_CHANNEL_DMA_RING_ID_BMSK                    0x7f
#define HWIO_ECPRI_XBAR_FHRX_n_DEFAULT_DMA_CHANNEL_DMA_RING_ID_SHFT                     0x0

#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_0_ADDR                                 (ECPRI_XBAR_REGS_REG_BASE      + 0x00000830)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_0_PHYS                                 (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000830)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_0_OFFS                                 (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000830)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_0_RMSK                                 0x1ff7fdff
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_0_ATTR                                        0x3
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_0_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_0_ADDR, HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_0_RMSK)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_0_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_0_ADDR, m)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_0_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_0_ADDR,v)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_0_ADDR,m,v,HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_0_IN)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_0_VALID_2_BMSK                         0x10000000
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_0_VALID_2_SHFT                               0x1c
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_0_MSG_TYPE_2_BMSK                       0xff00000
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_0_MSG_TYPE_2_SHFT                            0x14
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_0_VALID_1_BMSK                            0x40000
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_0_VALID_1_SHFT                               0x12
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_0_MSG_TYPE_1_BMSK                         0x3fc00
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_0_MSG_TYPE_1_SHFT                             0xa
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_0_VALID_0_BMSK                              0x100
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_0_VALID_0_SHFT                                0x8
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_0_MSG_TYPE_0_BMSK                            0xff
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_0_MSG_TYPE_0_SHFT                             0x0

#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_1_ADDR                                 (ECPRI_XBAR_REGS_REG_BASE      + 0x00000834)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_1_PHYS                                 (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000834)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_1_OFFS                                 (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000834)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_1_RMSK                                 0x1ff7fdff
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_1_ATTR                                        0x3
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_1_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_1_ADDR, HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_1_RMSK)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_1_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_1_ADDR, m)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_1_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_1_ADDR,v)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_1_ADDR,m,v,HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_1_IN)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_1_VALID_5_BMSK                         0x10000000
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_1_VALID_5_SHFT                               0x1c
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_1_MSG_TYPE_5_BMSK                       0xff00000
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_1_MSG_TYPE_5_SHFT                            0x14
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_1_VALID_4_BMSK                            0x40000
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_1_VALID_4_SHFT                               0x12
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_1_MSG_TYPE_4_BMSK                         0x3fc00
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_1_MSG_TYPE_4_SHFT                             0xa
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_1_VALID_3_BMSK                              0x100
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_1_VALID_3_SHFT                                0x8
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_1_MSG_TYPE_3_BMSK                            0xff
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_LUT_1_MSG_TYPE_3_SHFT                             0x0

#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_ADDR(n)                       (ECPRI_XBAR_REGS_REG_BASE      + 0x00000838 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_PHYS(n)                       (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000838 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_OFFS(n)                       (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000838 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_RMSK                              0x7fdf
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_MAXn                                   5
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_ATTR                                 0x3
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_ADDR(n), HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_RMSK)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_OUTI(n,val)    \
        out_dword(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_ADDR(n),val)
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_ADDR(n),mask,val,HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_INI(n))
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_DMA_RING_ID_BMSK                  0x7f00
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_DMA_RING_ID_SHFT                     0x8
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_GSI_ID_BMSK                         0xc0
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_GSI_ID_SHFT                          0x6
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_ROUTE_TO_DMA_BMSK                   0x10
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_ROUTE_TO_DMA_SHFT                    0x4
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_ROUTE_TO_C2C_BMSK                    0x8
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_ROUTE_TO_C2C_SHFT                    0x3
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_ROUTE_TO_ORAN_BMSK                   0x4
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_ROUTE_TO_ORAN_SHFT                   0x2
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_OC_LINK_ID_BMSK                      0x3
#define HWIO_ECPRI_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_OC_LINK_ID_SHFT                      0x0

#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_CFG_ADDR                           (ECPRI_XBAR_REGS_REG_BASE      + 0x00000860)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_CFG_PHYS                           (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000860)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_CFG_OFFS                           (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000860)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_CFG_RMSK                           0xffffffff
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_CFG_ATTR                                  0x3
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_CFG_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_CFG_ADDR, HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_CFG_RMSK)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_CFG_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_CFG_ADDR, m)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_CFG_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_CFG_ADDR,v)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_CFG_ADDR,m,v,HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_CFG_IN)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_CFG_VALUE_3_BMSK                   0xff000000
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_CFG_VALUE_3_SHFT                         0x18
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_CFG_VALUE_2_BMSK                     0xff0000
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_CFG_VALUE_2_SHFT                         0x10
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_CFG_VALUE_1_BMSK                       0xff00
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_CFG_VALUE_1_SHFT                          0x8
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_CFG_VALUE_0_BMSK                         0xff
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_CFG_VALUE_0_SHFT                          0x0

#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_VALID_ADDR                         (ECPRI_XBAR_REGS_REG_BASE      + 0x00000864)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_VALID_PHYS                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000864)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_VALID_OFFS                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000864)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_VALID_RMSK                                0xf
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_VALID_ATTR                                0x3
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_VALID_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_VALID_ADDR, HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_VALID_RMSK)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_VALID_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_VALID_ADDR, m)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_VALID_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_VALID_ADDR,v)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_VALID_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_VALID_ADDR,m,v,HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_VALID_IN)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_VALID_VALID_3_BMSK                        0x8
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_VALID_VALID_3_SHFT                        0x3
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_VALID_VALID_2_BMSK                        0x4
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_VALID_VALID_2_SHFT                        0x2
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_VALID_VALID_1_BMSK                        0x2
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_VALID_VALID_1_SHFT                        0x1
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_VALID_VALID_0_BMSK                        0x1
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_UPLANE_VALID_VALID_0_SHFT                        0x0

#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_CFG_ADDR                           (ECPRI_XBAR_REGS_REG_BASE      + 0x00000868)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_CFG_PHYS                           (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000868)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_CFG_OFFS                           (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000868)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_CFG_RMSK                           0xffffffff
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_CFG_ATTR                                  0x3
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_CFG_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_CFG_ADDR, HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_CFG_RMSK)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_CFG_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_CFG_ADDR, m)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_CFG_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_CFG_ADDR,v)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_CFG_ADDR,m,v,HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_CFG_IN)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_CFG_VALUE_3_BMSK                   0xff000000
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_CFG_VALUE_3_SHFT                         0x18
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_CFG_VALUE_2_BMSK                     0xff0000
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_CFG_VALUE_2_SHFT                         0x10
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_CFG_VALUE_1_BMSK                       0xff00
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_CFG_VALUE_1_SHFT                          0x8
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_CFG_VALUE_0_BMSK                         0xff
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_CFG_VALUE_0_SHFT                          0x0

#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_VALID_ADDR                         (ECPRI_XBAR_REGS_REG_BASE      + 0x0000086c)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_VALID_PHYS                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x0000086c)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_VALID_OFFS                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x0000086c)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_VALID_RMSK                                0xf
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_VALID_ATTR                                0x3
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_VALID_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_VALID_ADDR, HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_VALID_RMSK)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_VALID_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_VALID_ADDR, m)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_VALID_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_VALID_ADDR,v)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_VALID_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_VALID_ADDR,m,v,HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_VALID_IN)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_VALID_VALID_3_BMSK                        0x8
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_VALID_VALID_3_SHFT                        0x3
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_VALID_VALID_2_BMSK                        0x4
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_VALID_VALID_2_SHFT                        0x2
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_VALID_VALID_1_BMSK                        0x2
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_VALID_VALID_1_SHFT                        0x1
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_VALID_VALID_0_BMSK                        0x1
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_CPLANE_VALID_VALID_0_SHFT                        0x0

#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_ADDR(n)                              (ECPRI_XBAR_REGS_REG_BASE      + 0x00000870 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_PHYS(n)                              (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000870 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_OFFS(n)                              (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000870 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_RMSK                                 0xffffffff
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_MAXn                                          2
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_ATTR                                        0x3
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_ADDR(n), HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_RMSK)
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_OUTI(n,val)    \
        out_dword(HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_ADDR(n),val)
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_ADDR(n),mask,val,HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_INI(n))
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_L2_ENCAP_INFO_BMSK                   0xff000000
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_L2_ENCAP_INFO_SHFT                         0x18
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_L3_ENCAP_INFO_BMSK                     0xff0000
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_L3_ENCAP_INFO_SHFT                         0x10
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_L3_ENCAP_VALID_BMSK                      0x8000
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_L3_ENCAP_VALID_SHFT                         0xf
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_OTHER_ROUTE_BMSK                         0x7000
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_OTHER_ROUTE_SHFT                            0xc
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_OTHER_ROUTE_INVALID_FVAL                    0x0
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_OTHER_ROUTE_ROUTE_TO_FH_FVAL                0x1
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_OTHER_ROUTE_ROUTE_TO_DMA_FVAL               0x2
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_OTHER_ROUTE_RESERVED_FVAL                   0x3
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_OTHER_ROUTE_ROUTE_TO_OC0_FVAL               0x4
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_OTHER_ROUTE_ROUTE_TO_OC1_FVAL               0x5
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_OTHER_ROUTE_ROUTE_TO_OC2_FVAL               0x6
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_OTHER_ROUTE_ROUTE_TO_OC3_FVAL               0x7
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_CP_DL_ROUTE_BMSK                          0xe00
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_CP_DL_ROUTE_SHFT                            0x9
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_CP_DL_ROUTE_INVALID_FVAL                    0x0
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_CP_DL_ROUTE_ROUTE_TO_FH_FVAL                0x1
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_CP_DL_ROUTE_ROUTE_TO_DMA_FVAL               0x2
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_CP_DL_ROUTE_RESERVED_FVAL                   0x3
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_CP_DL_ROUTE_ROUTE_TO_OC0_FVAL               0x4
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_CP_DL_ROUTE_ROUTE_TO_OC1_FVAL               0x5
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_CP_DL_ROUTE_ROUTE_TO_OC2_FVAL               0x6
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_CP_DL_ROUTE_ROUTE_TO_OC3_FVAL               0x7
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_CP_UL_ROUTE_BMSK                          0x1c0
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_CP_UL_ROUTE_SHFT                            0x6
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_CP_UL_ROUTE_INVALID_FVAL                    0x0
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_CP_UL_ROUTE_ROUTE_TO_FH_FVAL                0x1
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_CP_UL_ROUTE_ROUTE_TO_DMA_FVAL               0x2
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_CP_UL_ROUTE_RESERVED_FVAL                   0x3
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_CP_UL_ROUTE_ROUTE_TO_OC0_FVAL               0x4
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_CP_UL_ROUTE_ROUTE_TO_OC1_FVAL               0x5
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_CP_UL_ROUTE_ROUTE_TO_OC2_FVAL               0x6
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_CP_UL_ROUTE_ROUTE_TO_OC3_FVAL               0x7
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_UP_DL_ROUTE_BMSK                           0x38
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_UP_DL_ROUTE_SHFT                            0x3
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_UP_DL_ROUTE_INVALID_FVAL                    0x0
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_UP_DL_ROUTE_ROUTE_TO_FH_FVAL                0x1
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_UP_DL_ROUTE_ROUTE_TO_DMA_FVAL               0x2
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_UP_DL_ROUTE_RESERVED_FVAL                   0x3
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_UP_DL_ROUTE_ROUTE_TO_OC0_FVAL               0x4
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_UP_DL_ROUTE_ROUTE_TO_OC1_FVAL               0x5
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_UP_DL_ROUTE_ROUTE_TO_OC2_FVAL               0x6
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_UP_DL_ROUTE_ROUTE_TO_OC3_FVAL               0x7
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_UP_UL_ROUTE_BMSK                            0x7
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_UP_UL_ROUTE_SHFT                            0x0
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_UP_UL_ROUTE_INVALID_FVAL                    0x0
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_UP_UL_ROUTE_ROUTE_TO_FH_FVAL                0x1
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_UP_UL_ROUTE_ROUTE_TO_DMA_FVAL               0x2
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_UP_UL_ROUTE_RESERVED_FVAL                   0x3
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_UP_UL_ROUTE_ROUTE_TO_OC0_FVAL               0x4
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_UP_UL_ROUTE_ROUTE_TO_OC1_FVAL               0x5
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_UP_UL_ROUTE_ROUTE_TO_OC2_FVAL               0x6
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_LUT_UP_UL_ROUTE_ROUTE_TO_OC3_FVAL               0x7

#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_DMA_CHANNEL_ADDR(n)                      (ECPRI_XBAR_REGS_REG_BASE      + 0x00000880 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_DMA_CHANNEL_PHYS(n)                      (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000880 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_DMA_CHANNEL_OFFS(n)                      (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000880 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_DMA_CHANNEL_RMSK                              0x37f
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_DMA_CHANNEL_MAXn                                  2
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_DMA_CHANNEL_ATTR                                0x3
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_DMA_CHANNEL_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_DMA_CHANNEL_ADDR(n), HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_DMA_CHANNEL_RMSK)
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_DMA_CHANNEL_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_DMA_CHANNEL_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_DMA_CHANNEL_OUTI(n,val)    \
        out_dword(HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_DMA_CHANNEL_ADDR(n),val)
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_DMA_CHANNEL_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_DMA_CHANNEL_ADDR(n),mask,val,HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_DMA_CHANNEL_INI(n))
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_DMA_CHANNEL_GSI_ID_BMSK                       0x300
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_DMA_CHANNEL_GSI_ID_SHFT                         0x8
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_DMA_CHANNEL_DMA_RING_ID_BMSK                   0x7f
#define HWIO_ECPRI_XBAR_C2CRX_n_DEFAULT_DMA_CHANNEL_DMA_RING_ID_SHFT                    0x0

#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_0_ADDR                                (ECPRI_XBAR_REGS_REG_BASE      + 0x00000890)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_0_PHYS                                (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000890)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_0_OFFS                                (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000890)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_0_RMSK                                0x1ff7fdff
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_0_ATTR                                       0x3
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_0_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_0_ADDR, HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_0_RMSK)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_0_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_0_ADDR, m)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_0_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_0_ADDR,v)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_0_ADDR,m,v,HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_0_IN)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_0_VALID_2_BMSK                        0x10000000
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_0_VALID_2_SHFT                              0x1c
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_0_MSG_TYPE_2_BMSK                      0xff00000
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_0_MSG_TYPE_2_SHFT                           0x14
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_0_VALID_1_BMSK                           0x40000
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_0_VALID_1_SHFT                              0x12
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_0_MSG_TYPE_1_BMSK                        0x3fc00
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_0_MSG_TYPE_1_SHFT                            0xa
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_0_VALID_0_BMSK                             0x100
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_0_VALID_0_SHFT                               0x8
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_0_MSG_TYPE_0_BMSK                           0xff
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_0_MSG_TYPE_0_SHFT                            0x0

#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_1_ADDR                                (ECPRI_XBAR_REGS_REG_BASE      + 0x00000894)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_1_PHYS                                (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000894)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_1_OFFS                                (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000894)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_1_RMSK                                0x1ff7fdff
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_1_ATTR                                       0x3
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_1_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_1_ADDR, HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_1_RMSK)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_1_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_1_ADDR, m)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_1_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_1_ADDR,v)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_1_ADDR,m,v,HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_1_IN)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_1_VALID_5_BMSK                        0x10000000
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_1_VALID_5_SHFT                              0x1c
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_1_MSG_TYPE_5_BMSK                      0xff00000
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_1_MSG_TYPE_5_SHFT                           0x14
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_1_VALID_4_BMSK                           0x40000
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_1_VALID_4_SHFT                              0x12
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_1_MSG_TYPE_4_BMSK                        0x3fc00
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_1_MSG_TYPE_4_SHFT                            0xa
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_1_VALID_3_BMSK                             0x100
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_1_VALID_3_SHFT                               0x8
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_1_MSG_TYPE_3_BMSK                           0xff
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_LUT_1_MSG_TYPE_3_SHFT                            0x0

#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_ADDR(n)                      (ECPRI_XBAR_REGS_REG_BASE      + 0x00000898 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_PHYS(n)                      (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00000898 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_OFFS(n)                      (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00000898 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_RMSK                         0x7fffffff
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_MAXn                                  5
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_ATTR                                0x3
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_ADDR(n), HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_RMSK)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_OUTI(n,val)    \
        out_dword(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_ADDR(n),val)
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_ADDR(n),mask,val,HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_INI(n))
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_DMA_RING_ID_BMSK             0x7f000000
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_DMA_RING_ID_SHFT                   0x18
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_GSI_ID_BMSK                    0xc00000
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_GSI_ID_SHFT                        0x16
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_ROUTE_TO_DMA_BMSK              0x200000
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_ROUTE_TO_DMA_SHFT                  0x15
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_ROUTE_TO_FH_BMSK               0x100000
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_ROUTE_TO_FH_SHFT                   0x14
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_ROUTE_TO_ORAN_BMSK              0x80000
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_ROUTE_TO_ORAN_SHFT                 0x13
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_L3_ENCAP_VALID_BMSK             0x40000
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_L3_ENCAP_VALID_SHFT                0x12
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_L3_ENCAP_INFO_BMSK              0x3fc00
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_L3_ENCAP_INFO_SHFT                  0xa
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_L2_ENCAP_INFO_BMSK                0x3fc
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_L2_ENCAP_INFO_SHFT                  0x2
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_OC_LINK_ID_BMSK                     0x3
#define HWIO_ECPRI_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_OC_LINK_ID_SHFT                     0x0

#define HWIO_ECPRI_XBAR_OCRX_FH_n_DEFAULT_LUT_ADDR(n)                            (ECPRI_XBAR_REGS_REG_BASE      + 0x000008c0 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_OCRX_FH_n_DEFAULT_LUT_PHYS(n)                            (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000008c0 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_OCRX_FH_n_DEFAULT_LUT_OFFS(n)                            (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000008c0 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_OCRX_FH_n_DEFAULT_LUT_RMSK                                  0x3ffff
#define HWIO_ECPRI_XBAR_OCRX_FH_n_DEFAULT_LUT_MAXn                                        2
#define HWIO_ECPRI_XBAR_OCRX_FH_n_DEFAULT_LUT_ATTR                                      0x3
#define HWIO_ECPRI_XBAR_OCRX_FH_n_DEFAULT_LUT_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_OCRX_FH_n_DEFAULT_LUT_ADDR(n), HWIO_ECPRI_XBAR_OCRX_FH_n_DEFAULT_LUT_RMSK)
#define HWIO_ECPRI_XBAR_OCRX_FH_n_DEFAULT_LUT_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_OCRX_FH_n_DEFAULT_LUT_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_OCRX_FH_n_DEFAULT_LUT_OUTI(n,val)    \
        out_dword(HWIO_ECPRI_XBAR_OCRX_FH_n_DEFAULT_LUT_ADDR(n),val)
#define HWIO_ECPRI_XBAR_OCRX_FH_n_DEFAULT_LUT_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_OCRX_FH_n_DEFAULT_LUT_ADDR(n),mask,val,HWIO_ECPRI_XBAR_OCRX_FH_n_DEFAULT_LUT_INI(n))
#define HWIO_ECPRI_XBAR_OCRX_FH_n_DEFAULT_LUT_DROP_BMSK                             0x20000
#define HWIO_ECPRI_XBAR_OCRX_FH_n_DEFAULT_LUT_DROP_SHFT                                0x11
#define HWIO_ECPRI_XBAR_OCRX_FH_n_DEFAULT_LUT_L3_ENCAP_VALID_BMSK                   0x10000
#define HWIO_ECPRI_XBAR_OCRX_FH_n_DEFAULT_LUT_L3_ENCAP_VALID_SHFT                      0x10
#define HWIO_ECPRI_XBAR_OCRX_FH_n_DEFAULT_LUT_L3_ENCAP_INFO_BMSK                     0xff00
#define HWIO_ECPRI_XBAR_OCRX_FH_n_DEFAULT_LUT_L3_ENCAP_INFO_SHFT                        0x8
#define HWIO_ECPRI_XBAR_OCRX_FH_n_DEFAULT_LUT_L2_ENCAP_INFO_BMSK                       0xff
#define HWIO_ECPRI_XBAR_OCRX_FH_n_DEFAULT_LUT_L2_ENCAP_INFO_SHFT                        0x0

#define HWIO_ECPRI_XBAR_OCRX_C2C_DEFAULT_LUT_ADDR                                (ECPRI_XBAR_REGS_REG_BASE      + 0x000008d0)
#define HWIO_ECPRI_XBAR_OCRX_C2C_DEFAULT_LUT_PHYS                                (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000008d0)
#define HWIO_ECPRI_XBAR_OCRX_C2C_DEFAULT_LUT_OFFS                                (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000008d0)
#define HWIO_ECPRI_XBAR_OCRX_C2C_DEFAULT_LUT_RMSK                                 0x301ffff
#define HWIO_ECPRI_XBAR_OCRX_C2C_DEFAULT_LUT_ATTR                                       0x3
#define HWIO_ECPRI_XBAR_OCRX_C2C_DEFAULT_LUT_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_OCRX_C2C_DEFAULT_LUT_ADDR, HWIO_ECPRI_XBAR_OCRX_C2C_DEFAULT_LUT_RMSK)
#define HWIO_ECPRI_XBAR_OCRX_C2C_DEFAULT_LUT_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_OCRX_C2C_DEFAULT_LUT_ADDR, m)
#define HWIO_ECPRI_XBAR_OCRX_C2C_DEFAULT_LUT_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_OCRX_C2C_DEFAULT_LUT_ADDR,v)
#define HWIO_ECPRI_XBAR_OCRX_C2C_DEFAULT_LUT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_OCRX_C2C_DEFAULT_LUT_ADDR,m,v,HWIO_ECPRI_XBAR_OCRX_C2C_DEFAULT_LUT_IN)
#define HWIO_ECPRI_XBAR_OCRX_C2C_DEFAULT_LUT_C2C_PORT_NUM_BMSK                    0x3000000
#define HWIO_ECPRI_XBAR_OCRX_C2C_DEFAULT_LUT_C2C_PORT_NUM_SHFT                         0x18
#define HWIO_ECPRI_XBAR_OCRX_C2C_DEFAULT_LUT_L3_ENCAP_VALID_BMSK                    0x10000
#define HWIO_ECPRI_XBAR_OCRX_C2C_DEFAULT_LUT_L3_ENCAP_VALID_SHFT                       0x10
#define HWIO_ECPRI_XBAR_OCRX_C2C_DEFAULT_LUT_L3_ENCAP_INFO_BMSK                      0xff00
#define HWIO_ECPRI_XBAR_OCRX_C2C_DEFAULT_LUT_L3_ENCAP_INFO_SHFT                         0x8
#define HWIO_ECPRI_XBAR_OCRX_C2C_DEFAULT_LUT_L2_ENCAP_INFO_BMSK                        0xff
#define HWIO_ECPRI_XBAR_OCRX_C2C_DEFAULT_LUT_L2_ENCAP_INFO_SHFT                         0x0

#define HWIO_ECPRI_XBAR_NFAPI_DEFAULT_LUT_ADDR                                   (ECPRI_XBAR_REGS_REG_BASE      + 0x000008e0)
#define HWIO_ECPRI_XBAR_NFAPI_DEFAULT_LUT_PHYS                                   (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x000008e0)
#define HWIO_ECPRI_XBAR_NFAPI_DEFAULT_LUT_OFFS                                   (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x000008e0)
#define HWIO_ECPRI_XBAR_NFAPI_DEFAULT_LUT_RMSK                                        0x3ff
#define HWIO_ECPRI_XBAR_NFAPI_DEFAULT_LUT_ATTR                                          0x3
#define HWIO_ECPRI_XBAR_NFAPI_DEFAULT_LUT_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_NFAPI_DEFAULT_LUT_ADDR, HWIO_ECPRI_XBAR_NFAPI_DEFAULT_LUT_RMSK)
#define HWIO_ECPRI_XBAR_NFAPI_DEFAULT_LUT_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_NFAPI_DEFAULT_LUT_ADDR, m)
#define HWIO_ECPRI_XBAR_NFAPI_DEFAULT_LUT_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_NFAPI_DEFAULT_LUT_ADDR,v)
#define HWIO_ECPRI_XBAR_NFAPI_DEFAULT_LUT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_NFAPI_DEFAULT_LUT_ADDR,m,v,HWIO_ECPRI_XBAR_NFAPI_DEFAULT_LUT_IN)
#define HWIO_ECPRI_XBAR_NFAPI_DEFAULT_LUT_GSI_ID_BMSK                                 0x300
#define HWIO_ECPRI_XBAR_NFAPI_DEFAULT_LUT_GSI_ID_SHFT                                   0x8
#define HWIO_ECPRI_XBAR_NFAPI_DEFAULT_LUT_DMA_RING_ID_BMSK                             0xfe
#define HWIO_ECPRI_XBAR_NFAPI_DEFAULT_LUT_DMA_RING_ID_SHFT                              0x1
#define HWIO_ECPRI_XBAR_NFAPI_DEFAULT_LUT_ROUTE_TO_DMA_BMSK                             0x1
#define HWIO_ECPRI_XBAR_NFAPI_DEFAULT_LUT_ROUTE_TO_DMA_SHFT                             0x0

#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_ADDR_ADDR                                   (ECPRI_XBAR_REGS_REG_BASE      + 0x00003000)
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_ADDR_PHYS                                   (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00003000)
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_ADDR_OFFS                                   (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00003000)
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_ADDR_RMSK                                       0xffff
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_ADDR_ATTR                                          0x3
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_ADDR_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_UC_FHRX_BUFF_ADDR_ADDR, HWIO_ECPRI_XBAR_UC_FHRX_BUFF_ADDR_RMSK)
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_ADDR_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_UC_FHRX_BUFF_ADDR_ADDR, m)
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_ADDR_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_UC_FHRX_BUFF_ADDR_ADDR,v)
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_ADDR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_UC_FHRX_BUFF_ADDR_ADDR,m,v,HWIO_ECPRI_XBAR_UC_FHRX_BUFF_ADDR_IN)
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_ADDR_ADDR_BMSK                                  0xffff
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_ADDR_ADDR_SHFT                                     0x0

#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_SIZE_ADDR                                   (ECPRI_XBAR_REGS_REG_BASE      + 0x00003004)
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_SIZE_PHYS                                   (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00003004)
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_SIZE_OFFS                                   (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00003004)
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_SIZE_RMSK                                       0x7fff
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_SIZE_ATTR                                          0x3
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_SIZE_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_UC_FHRX_BUFF_SIZE_ADDR, HWIO_ECPRI_XBAR_UC_FHRX_BUFF_SIZE_RMSK)
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_SIZE_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_UC_FHRX_BUFF_SIZE_ADDR, m)
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_SIZE_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_UC_FHRX_BUFF_SIZE_ADDR,v)
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_SIZE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_UC_FHRX_BUFF_SIZE_ADDR,m,v,HWIO_ECPRI_XBAR_UC_FHRX_BUFF_SIZE_IN)
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_SIZE_SIZE_BMSK                                  0x7fff
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_SIZE_SIZE_SHFT                                     0x0

#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_RD_ADDR                                     (ECPRI_XBAR_REGS_REG_BASE      + 0x00003008)
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_RD_PHYS                                     (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00003008)
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_RD_OFFS                                     (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00003008)
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_RD_RMSK                                         0xffff
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_RD_ATTR                                            0x3
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_RD_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_UC_FHRX_BUFF_RD_ADDR, HWIO_ECPRI_XBAR_UC_FHRX_BUFF_RD_RMSK)
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_RD_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_UC_FHRX_BUFF_RD_ADDR, m)
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_RD_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_UC_FHRX_BUFF_RD_ADDR,v)
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_RD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_UC_FHRX_BUFF_RD_ADDR,m,v,HWIO_ECPRI_XBAR_UC_FHRX_BUFF_RD_IN)
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_RD_ADDR_BMSK                                    0xffff
#define HWIO_ECPRI_XBAR_UC_FHRX_BUFF_RD_ADDR_SHFT                                       0x0

#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_POP_ADDR                                (ECPRI_XBAR_REGS_REG_BASE      + 0x0000300c)
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_POP_PHYS                                (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x0000300c)
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_POP_OFFS                                (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x0000300c)
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_POP_RMSK                                 0x10f3fff
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_POP_ATTR                                       0x1
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_POP_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_POP_ADDR, HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_POP_RMSK)
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_POP_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_POP_ADDR, m)
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_POP_ERR_BMSK                             0x1000000
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_POP_ERR_SHFT                                  0x18
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_POP_PORT_BMSK                              0xc0000
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_POP_PORT_SHFT                                 0x12
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_POP_LINK_BMSK                              0x30000
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_POP_LINK_SHFT                                 0x10
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_POP_LENGTH_BMSK                             0x3fff
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_POP_LENGTH_SHFT                                0x0

#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_NO_POP_ADDR                             (ECPRI_XBAR_REGS_REG_BASE      + 0x00003010)
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_NO_POP_PHYS                             (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00003010)
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_NO_POP_OFFS                             (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00003010)
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_NO_POP_RMSK                              0x10f3fff
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_NO_POP_ATTR                                    0x1
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_NO_POP_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_NO_POP_ADDR, HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_NO_POP_RMSK)
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_NO_POP_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_NO_POP_ADDR, m)
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_NO_POP_ERR_BMSK                          0x1000000
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_NO_POP_ERR_SHFT                               0x18
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_NO_POP_PORT_BMSK                           0xc0000
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_NO_POP_PORT_SHFT                              0x12
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_NO_POP_LINK_BMSK                           0x30000
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_NO_POP_LINK_SHFT                              0x10
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_NO_POP_LENGTH_BMSK                          0x3fff
#define HWIO_ECPRI_XBAR_UC_FHRX_PKT_ATTR_NO_POP_LENGTH_SHFT                             0x0

#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_ADDR                                      (ECPRI_XBAR_REGS_REG_BASE      + 0x00003014)
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_PHYS                                      (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00003014)
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_OFFS                                      (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00003014)
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_RMSK                                           0x3ff
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_ATTR                                             0x1
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_UC_FHRX_STATUS_ADDR, HWIO_ECPRI_XBAR_UC_FHRX_STATUS_RMSK)
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_UC_FHRX_STATUS_ADDR, m)
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_UC_PKT_DROP_BMSK                               0x380
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_UC_PKT_DROP_SHFT                                 0x7
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_UC_PKT_ERR_BMSK                                 0x70
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_UC_PKT_ERR_SHFT                                  0x4
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_UC_PKT_OVERFLOW_BMSK                             0xe
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_UC_PKT_OVERFLOW_SHFT                             0x1
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_UC_PKT_PENDING_BMSK                              0x1
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_UC_PKT_PENDING_SHFT                              0x0

#define HWIO_ECPRI_XBAR_UC_FH_CTRL_ADDR                                          (ECPRI_XBAR_REGS_REG_BASE      + 0x00003018)
#define HWIO_ECPRI_XBAR_UC_FH_CTRL_PHYS                                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00003018)
#define HWIO_ECPRI_XBAR_UC_FH_CTRL_OFFS                                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00003018)
#define HWIO_ECPRI_XBAR_UC_FH_CTRL_RMSK                                                 0x3
#define HWIO_ECPRI_XBAR_UC_FH_CTRL_ATTR                                                 0x3
#define HWIO_ECPRI_XBAR_UC_FH_CTRL_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_UC_FH_CTRL_ADDR, HWIO_ECPRI_XBAR_UC_FH_CTRL_RMSK)
#define HWIO_ECPRI_XBAR_UC_FH_CTRL_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_UC_FH_CTRL_ADDR, m)
#define HWIO_ECPRI_XBAR_UC_FH_CTRL_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_UC_FH_CTRL_ADDR,v)
#define HWIO_ECPRI_XBAR_UC_FH_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_UC_FH_CTRL_ADDR,m,v,HWIO_ECPRI_XBAR_UC_FH_CTRL_IN)
#define HWIO_ECPRI_XBAR_UC_FH_CTRL_FHRX_UC_PKT_ERR_DROP_BMSK                            0x2
#define HWIO_ECPRI_XBAR_UC_FH_CTRL_FHRX_UC_PKT_ERR_DROP_SHFT                            0x1
#define HWIO_ECPRI_XBAR_UC_FH_CTRL_FHRX_UC_ENABLE_BMSK                                  0x1
#define HWIO_ECPRI_XBAR_UC_FH_CTRL_FHRX_UC_ENABLE_SHFT                                  0x0

#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ADDR_ADDR                                    (ECPRI_XBAR_REGS_REG_BASE      + 0x0000301c)
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ADDR_PHYS                                    (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x0000301c)
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ADDR_OFFS                                    (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x0000301c)
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ADDR_RMSK                                    0x3fffffff
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ADDR_ATTR                                           0x3
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ADDR_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_UC_FHTX_PKT_ADDR_ADDR, HWIO_ECPRI_XBAR_UC_FHTX_PKT_ADDR_RMSK)
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ADDR_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_UC_FHTX_PKT_ADDR_ADDR, m)
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ADDR_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_UC_FHTX_PKT_ADDR_ADDR,v)
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ADDR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_UC_FHTX_PKT_ADDR_ADDR,m,v,HWIO_ECPRI_XBAR_UC_FHTX_PKT_ADDR_IN)
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ADDR_LENGTH_BMSK                             0x3fff0000
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ADDR_LENGTH_SHFT                                   0x10
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ADDR_ADDR_BMSK                                   0xffff
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ADDR_ADDR_SHFT                                      0x0

#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_ADDR                                    (ECPRI_XBAR_REGS_REG_BASE      + 0x00003020)
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_PHYS                                    (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00003020)
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_OFFS                                    (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00003020)
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_RMSK                                    0x8f0fffff
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_ATTR                                           0x3
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_ADDR, HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_RMSK)
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_ADDR, m)
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_ADDR,v)
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_ADDR,m,v,HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_IN)
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_PKT_AVAIL_BMSK                          0x80000000
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_PKT_AVAIL_SHFT                                0x1f
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_PORT_BMSK                                0xc000000
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_PORT_SHFT                                     0x1a
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_LINK_BMSK                                0x3000000
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_LINK_SHFT                                     0x18
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_L3_ENCAP_VALID_BMSK                        0x80000
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_L3_ENCAP_VALID_SHFT                           0x13
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_L2_ENCAP_VALID_BMSK                        0x40000
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_L2_ENCAP_VALID_SHFT                           0x12
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_L3_ENCAP_BMSK                              0x3fe00
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_L3_ENCAP_SHFT                                  0x9
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_L2_ENCAP_BMSK                                0x1ff
#define HWIO_ECPRI_XBAR_UC_FHTX_PKT_ATTR_L2_ENCAP_SHFT                                  0x0

#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_ADDR                           (ECPRI_XBAR_REGS_REG_BASE      + 0x00002000)
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_PHYS                           (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00002000)
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_OFFS                           (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00002000)
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_RMSK                           0x3fffffff
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_ATTR                                  0x1
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_ADDR, HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_RMSK)
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_OCRX_FH_2_CNT_BMSK             0x3ff00000
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_OCRX_FH_2_CNT_SHFT                   0x14
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_OCRX_FH_1_CNT_BMSK                0xffc00
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_OCRX_FH_1_CNT_SHFT                    0xa
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_OCRX_FH_0_CNT_BMSK                  0x3ff
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_OCRX_FH_0_CNT_SHFT                    0x0

#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n_ADDR(n)                   (ECPRI_XBAR_REGS_REG_BASE      + 0x00002010 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n_PHYS(n)                   (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00002010 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n_OFFS(n)                   (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00002010 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n_RMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n_MAXn                               2
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n_ATTR                             0x1
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n_ADDR(n), HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n_RMSK)
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n_INFO_BMSK                 0xffffffff
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n_INFO_SHFT                        0x0

#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n_ADDR(n)                   (ECPRI_XBAR_REGS_REG_BASE      + 0x00002020 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n_PHYS(n)                   (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00002020 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n_OFFS(n)                   (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00002020 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n_RMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n_MAXn                               2
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n_ATTR                             0x1
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n_ADDR(n), HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n_RMSK)
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n_INFO_BMSK                 0xffffffff
#define HWIO_ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n_INFO_SHFT                        0x0

#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_ADDR                           (ECPRI_XBAR_REGS_REG_BASE      + 0x00002030)
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_PHYS                           (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00002030)
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_OFFS                           (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00002030)
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_RMSK                           0x3fffffff
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_ATTR                                  0x1
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_ADDR, HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_RMSK)
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_FHRX_2_CNT_BMSK                0x3ff00000
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_FHRX_2_CNT_SHFT                      0x14
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_FHRX_1_CNT_BMSK                   0xffc00
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_FHRX_1_CNT_SHFT                       0xa
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_FHRX_0_CNT_BMSK                     0x3ff
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_FHRX_0_CNT_SHFT                       0x0

#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n_ADDR(n)                   (ECPRI_XBAR_REGS_REG_BASE      + 0x00002040 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n_PHYS(n)                   (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00002040 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n_OFFS(n)                   (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00002040 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n_RMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n_MAXn                               2
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n_ATTR                             0x1
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n_ADDR(n), HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n_RMSK)
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n_INFO_BMSK                 0xffffffff
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n_INFO_SHFT                        0x0

#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n_ADDR(n)                   (ECPRI_XBAR_REGS_REG_BASE      + 0x00002050 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n_PHYS(n)                   (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00002050 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n_OFFS(n)                   (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00002050 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n_RMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n_MAXn                               2
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n_ATTR                             0x1
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n_ADDR(n), HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n_RMSK)
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n_INFO_BMSK                 0xffffffff
#define HWIO_ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n_INFO_SHFT                        0x0

#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_ADDR                          (ECPRI_XBAR_REGS_REG_BASE      + 0x00002060)
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_PHYS                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00002060)
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_OFFS                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00002060)
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_RMSK                          0x3fffffff
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_ATTR                                 0x1
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_ADDR, HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_RMSK)
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_C2CRX_2_CNT_BMSK              0x3ff00000
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_C2CRX_2_CNT_SHFT                    0x14
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_C2CRX_1_CNT_BMSK                 0xffc00
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_C2CRX_1_CNT_SHFT                     0xa
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_C2CRX_0_CNT_BMSK                   0x3ff
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_C2CRX_0_CNT_SHFT                     0x0

#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_1_n_ADDR(n)                  (ECPRI_XBAR_REGS_REG_BASE      + 0x00002070 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_1_n_PHYS(n)                  (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00002070 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_1_n_OFFS(n)                  (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00002070 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_1_n_RMSK                     0xffffffff
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_1_n_MAXn                              2
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_1_n_ATTR                            0x1
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_1_n_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_1_n_ADDR(n), HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_1_n_RMSK)
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_1_n_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_1_n_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_1_n_INFO_BMSK                0xffffffff
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_1_n_INFO_SHFT                       0x0

#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_2_n_ADDR(n)                  (ECPRI_XBAR_REGS_REG_BASE      + 0x00002080 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_2_n_PHYS(n)                  (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00002080 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_2_n_OFFS(n)                  (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00002080 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_2_n_RMSK                     0xffffffff
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_2_n_MAXn                              2
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_2_n_ATTR                            0x1
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_2_n_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_2_n_ADDR(n), HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_2_n_RMSK)
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_2_n_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_2_n_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_2_n_INFO_BMSK                0xffffffff
#define HWIO_ECPRI_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_2_n_INFO_SHFT                       0x0

#define HWIO_ECPRI_XBAR_DBG_TESTBUS_SELECT_ADDR                                  (ECPRI_XBAR_REGS_REG_BASE      + 0x00002200)
#define HWIO_ECPRI_XBAR_DBG_TESTBUS_SELECT_PHYS                                  (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00002200)
#define HWIO_ECPRI_XBAR_DBG_TESTBUS_SELECT_OFFS                                  (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00002200)
#define HWIO_ECPRI_XBAR_DBG_TESTBUS_SELECT_RMSK                                  0x8000ffff
#define HWIO_ECPRI_XBAR_DBG_TESTBUS_SELECT_ATTR                                         0x3
#define HWIO_ECPRI_XBAR_DBG_TESTBUS_SELECT_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_TESTBUS_SELECT_ADDR, HWIO_ECPRI_XBAR_DBG_TESTBUS_SELECT_RMSK)
#define HWIO_ECPRI_XBAR_DBG_TESTBUS_SELECT_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_TESTBUS_SELECT_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_TESTBUS_SELECT_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_DBG_TESTBUS_SELECT_ADDR,v)
#define HWIO_ECPRI_XBAR_DBG_TESTBUS_SELECT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_DBG_TESTBUS_SELECT_ADDR,m,v,HWIO_ECPRI_XBAR_DBG_TESTBUS_SELECT_IN)
#define HWIO_ECPRI_XBAR_DBG_TESTBUS_SELECT_TESTBUS_ENABLE_BMSK                   0x80000000
#define HWIO_ECPRI_XBAR_DBG_TESTBUS_SELECT_TESTBUS_ENABLE_SHFT                         0x1f
#define HWIO_ECPRI_XBAR_DBG_TESTBUS_SELECT_ORAN_TESTBUS_SEL_BMSK                     0xff00
#define HWIO_ECPRI_XBAR_DBG_TESTBUS_SELECT_ORAN_TESTBUS_SEL_SHFT                        0x8
#define HWIO_ECPRI_XBAR_DBG_TESTBUS_SELECT_XBAR_TESTBUS_SEL_BMSK                       0xff
#define HWIO_ECPRI_XBAR_DBG_TESTBUS_SELECT_XBAR_TESTBUS_SEL_SHFT                        0x0

#define HWIO_ECPRI_XBAR_DBG_XBAR_TESTBUS_ADDR                                    (ECPRI_XBAR_REGS_REG_BASE      + 0x00002204)
#define HWIO_ECPRI_XBAR_DBG_XBAR_TESTBUS_PHYS                                    (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00002204)
#define HWIO_ECPRI_XBAR_DBG_XBAR_TESTBUS_OFFS                                    (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00002204)
#define HWIO_ECPRI_XBAR_DBG_XBAR_TESTBUS_RMSK                                    0xffffffff
#define HWIO_ECPRI_XBAR_DBG_XBAR_TESTBUS_ATTR                                           0x1
#define HWIO_ECPRI_XBAR_DBG_XBAR_TESTBUS_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_XBAR_TESTBUS_ADDR, HWIO_ECPRI_XBAR_DBG_XBAR_TESTBUS_RMSK)
#define HWIO_ECPRI_XBAR_DBG_XBAR_TESTBUS_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_XBAR_TESTBUS_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_XBAR_TESTBUS_XBAR_TESTBUS_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_DBG_XBAR_TESTBUS_XBAR_TESTBUS_SHFT                              0x0

#define HWIO_ECPRI_XBAR_DBG_ORAN_TESTBUS_ADDR                                    (ECPRI_XBAR_REGS_REG_BASE      + 0x00002208)
#define HWIO_ECPRI_XBAR_DBG_ORAN_TESTBUS_PHYS                                    (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00002208)
#define HWIO_ECPRI_XBAR_DBG_ORAN_TESTBUS_OFFS                                    (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00002208)
#define HWIO_ECPRI_XBAR_DBG_ORAN_TESTBUS_RMSK                                    0xffffffff
#define HWIO_ECPRI_XBAR_DBG_ORAN_TESTBUS_ATTR                                           0x1
#define HWIO_ECPRI_XBAR_DBG_ORAN_TESTBUS_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_ORAN_TESTBUS_ADDR, HWIO_ECPRI_XBAR_DBG_ORAN_TESTBUS_RMSK)
#define HWIO_ECPRI_XBAR_DBG_ORAN_TESTBUS_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_ORAN_TESTBUS_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_ORAN_TESTBUS_ORAN_TESTBUS_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_DBG_ORAN_TESTBUS_ORAN_TESTBUS_SHFT                              0x0

#define HWIO_ECPRI_XBAR_DBG_CHICKEN_SWITCH_1_ADDR                                (ECPRI_XBAR_REGS_REG_BASE      + 0x00002300)
#define HWIO_ECPRI_XBAR_DBG_CHICKEN_SWITCH_1_PHYS                                (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00002300)
#define HWIO_ECPRI_XBAR_DBG_CHICKEN_SWITCH_1_OFFS                                (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00002300)
#define HWIO_ECPRI_XBAR_DBG_CHICKEN_SWITCH_1_RMSK                                      0xff
#define HWIO_ECPRI_XBAR_DBG_CHICKEN_SWITCH_1_ATTR                                       0x3
#define HWIO_ECPRI_XBAR_DBG_CHICKEN_SWITCH_1_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_CHICKEN_SWITCH_1_ADDR, HWIO_ECPRI_XBAR_DBG_CHICKEN_SWITCH_1_RMSK)
#define HWIO_ECPRI_XBAR_DBG_CHICKEN_SWITCH_1_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_CHICKEN_SWITCH_1_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_CHICKEN_SWITCH_1_OUT(v)      \
        out_dword(HWIO_ECPRI_XBAR_DBG_CHICKEN_SWITCH_1_ADDR,v)
#define HWIO_ECPRI_XBAR_DBG_CHICKEN_SWITCH_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_DBG_CHICKEN_SWITCH_1_ADDR,m,v,HWIO_ECPRI_XBAR_DBG_CHICKEN_SWITCH_1_IN)
#define HWIO_ECPRI_XBAR_DBG_CHICKEN_SWITCH_1_CHKN_1_BMSK                               0xff
#define HWIO_ECPRI_XBAR_DBG_CHICKEN_SWITCH_1_CHKN_1_SHFT                                0x0

#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_ADDR(n)                     (ECPRI_XBAR_REGS_REG_BASE      + 0x00002400 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_PHYS(n)                     (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00002400 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_OFFS(n)                     (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00002400 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_RMSK                        0x3fffffff
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_MAXn                                 3
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_ATTR                               0x1
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_ADDR(n), HWIO_ECPRI_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_RMSK)
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_FH2_BMSK                    0x3ff00000
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_FH2_SHFT                          0x14
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_FH1_BMSK                       0xffc00
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_FH1_SHFT                           0xa
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_FH0_BMSK                         0x3ff
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_FH0_SHFT                           0x0

#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_ADDR(n)                    (ECPRI_XBAR_REGS_REG_BASE      + 0x00002410 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_PHYS(n)                    (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00002410 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_OFFS(n)                    (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00002410 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_RMSK                       0x3fffffff
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_MAXn                                3
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_ATTR                              0x1
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_ADDR(n), HWIO_ECPRI_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_RMSK)
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_C2C2_BMSK                  0x3ff00000
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_C2C2_SHFT                        0x14
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_C2C1_BMSK                     0xffc00
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_C2C1_SHFT                         0xa
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_C2C0_BMSK                       0x3ff
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_C2C0_SHFT                         0x0

#define HWIO_ECPRI_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK_ADDR                         (ECPRI_XBAR_REGS_REG_BASE      + 0x00002420)
#define HWIO_ECPRI_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK_PHYS                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00002420)
#define HWIO_ECPRI_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK_OFFS                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00002420)
#define HWIO_ECPRI_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK_RMSK                            0xfffff
#define HWIO_ECPRI_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK_ATTR                                0x1
#define HWIO_ECPRI_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK_ADDR, HWIO_ECPRI_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK_RMSK)
#define HWIO_ECPRI_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK_CC1_BMSK                        0xffc00
#define HWIO_ECPRI_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK_CC1_SHFT                            0xa
#define HWIO_ECPRI_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK_CC0_BMSK                          0x3ff
#define HWIO_ECPRI_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK_CC0_SHFT                            0x0

#define HWIO_ECPRI_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK_ADDR                         (ECPRI_XBAR_REGS_REG_BASE      + 0x00002424)
#define HWIO_ECPRI_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK_PHYS                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00002424)
#define HWIO_ECPRI_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK_OFFS                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00002424)
#define HWIO_ECPRI_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK_RMSK                            0xfffff
#define HWIO_ECPRI_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK_ATTR                                0x1
#define HWIO_ECPRI_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK_ADDR, HWIO_ECPRI_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK_RMSK)
#define HWIO_ECPRI_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK_CC3_BMSK                        0xffc00
#define HWIO_ECPRI_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK_CC3_SHFT                            0xa
#define HWIO_ECPRI_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK_CC2_BMSK                          0x3ff
#define HWIO_ECPRI_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK_CC2_SHFT                            0x0

#define HWIO_ECPRI_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_ADDR                         (ECPRI_XBAR_REGS_REG_BASE      + 0x00002434)
#define HWIO_ECPRI_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_PHYS                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00002434)
#define HWIO_ECPRI_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_OFFS                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00002434)
#define HWIO_ECPRI_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_RMSK                         0x3fffffff
#define HWIO_ECPRI_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_ATTR                                0x1
#define HWIO_ECPRI_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_ADDR, HWIO_ECPRI_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_RMSK)
#define HWIO_ECPRI_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_C2C2_BMSK                    0x3ff00000
#define HWIO_ECPRI_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_C2C2_SHFT                          0x14
#define HWIO_ECPRI_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_C2C1_BMSK                       0xffc00
#define HWIO_ECPRI_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_C2C1_SHFT                           0xa
#define HWIO_ECPRI_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_C2C0_BMSK                         0x3ff
#define HWIO_ECPRI_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_C2C0_SHFT                           0x0

#define HWIO_ECPRI_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_ADDR                          (ECPRI_XBAR_REGS_REG_BASE      + 0x00002438)
#define HWIO_ECPRI_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_PHYS                          (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00002438)
#define HWIO_ECPRI_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_OFFS                          (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00002438)
#define HWIO_ECPRI_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_RMSK                          0x3fffffff
#define HWIO_ECPRI_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_ATTR                                 0x1
#define HWIO_ECPRI_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_ADDR, HWIO_ECPRI_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_RMSK)
#define HWIO_ECPRI_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_FH2_BMSK                      0x3ff00000
#define HWIO_ECPRI_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_FH2_SHFT                            0x14
#define HWIO_ECPRI_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_FH1_BMSK                         0xffc00
#define HWIO_ECPRI_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_FH1_SHFT                             0xa
#define HWIO_ECPRI_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_FH0_BMSK                           0x3ff
#define HWIO_ECPRI_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_FH0_SHFT                             0x0

#define HWIO_ECPRI_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_ADDR                         (ECPRI_XBAR_REGS_REG_BASE      + 0x0000243c)
#define HWIO_ECPRI_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_PHYS                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x0000243c)
#define HWIO_ECPRI_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_OFFS                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x0000243c)
#define HWIO_ECPRI_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_RMSK                         0x3fffffff
#define HWIO_ECPRI_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_ATTR                                0x1
#define HWIO_ECPRI_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_ADDR, HWIO_ECPRI_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_RMSK)
#define HWIO_ECPRI_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_FH2_BMSK                     0x3ff00000
#define HWIO_ECPRI_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_FH2_SHFT                           0x14
#define HWIO_ECPRI_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_FH1_BMSK                        0xffc00
#define HWIO_ECPRI_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_FH1_SHFT                            0xa
#define HWIO_ECPRI_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_FH0_BMSK                          0x3ff
#define HWIO_ECPRI_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_FH0_SHFT                            0x0

#define HWIO_ECPRI_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_ADDR                         (ECPRI_XBAR_REGS_REG_BASE      + 0x00002440)
#define HWIO_ECPRI_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_PHYS                         (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00002440)
#define HWIO_ECPRI_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_OFFS                         (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00002440)
#define HWIO_ECPRI_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_RMSK                         0x3fffffff
#define HWIO_ECPRI_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_ATTR                                0x1
#define HWIO_ECPRI_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_ADDR, HWIO_ECPRI_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_RMSK)
#define HWIO_ECPRI_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_C2C2_BMSK                    0x3ff00000
#define HWIO_ECPRI_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_C2C2_SHFT                          0x14
#define HWIO_ECPRI_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_C2C1_BMSK                       0xffc00
#define HWIO_ECPRI_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_C2C1_SHFT                           0xa
#define HWIO_ECPRI_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_C2C0_BMSK                         0x3ff
#define HWIO_ECPRI_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_C2C0_SHFT                           0x0

#define HWIO_ECPRI_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK_ADDR                      (ECPRI_XBAR_REGS_REG_BASE      + 0x00002450)
#define HWIO_ECPRI_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK_PHYS                      (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00002450)
#define HWIO_ECPRI_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK_OFFS                      (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00002450)
#define HWIO_ECPRI_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK_RMSK                         0xfffff
#define HWIO_ECPRI_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK_ATTR                             0x1
#define HWIO_ECPRI_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK_ADDR, HWIO_ECPRI_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK_RMSK)
#define HWIO_ECPRI_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK_CC1_BMSK                     0xffc00
#define HWIO_ECPRI_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK_CC1_SHFT                         0xa
#define HWIO_ECPRI_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK_CC0_BMSK                       0x3ff
#define HWIO_ECPRI_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK_CC0_SHFT                         0x0

#define HWIO_ECPRI_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK_ADDR                      (ECPRI_XBAR_REGS_REG_BASE      + 0x00002454)
#define HWIO_ECPRI_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK_PHYS                      (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00002454)
#define HWIO_ECPRI_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK_OFFS                      (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00002454)
#define HWIO_ECPRI_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK_RMSK                         0xfffff
#define HWIO_ECPRI_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK_ATTR                             0x1
#define HWIO_ECPRI_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK_ADDR, HWIO_ECPRI_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK_RMSK)
#define HWIO_ECPRI_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK_CC3_BMSK                     0xffc00
#define HWIO_ECPRI_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK_CC3_SHFT                         0xa
#define HWIO_ECPRI_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK_CC2_BMSK                       0x3ff
#define HWIO_ECPRI_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK_CC2_SHFT                         0x0

#define HWIO_ECPRI_XBAR_FH_STATUS_SHADOW_ADDR                                    (ECPRI_XBAR_REGS_REG_BASE      + 0x00002800)
#define HWIO_ECPRI_XBAR_FH_STATUS_SHADOW_PHYS                                    (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00002800)
#define HWIO_ECPRI_XBAR_FH_STATUS_SHADOW_OFFS                                    (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00002800)
#define HWIO_ECPRI_XBAR_FH_STATUS_SHADOW_RMSK                                           0x7
#define HWIO_ECPRI_XBAR_FH_STATUS_SHADOW_ATTR                                           0x1
#define HWIO_ECPRI_XBAR_FH_STATUS_SHADOW_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_STATUS_SHADOW_ADDR, HWIO_ECPRI_XBAR_FH_STATUS_SHADOW_RMSK)
#define HWIO_ECPRI_XBAR_FH_STATUS_SHADOW_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_FH_STATUS_SHADOW_ADDR, m)
#define HWIO_ECPRI_XBAR_FH_STATUS_SHADOW_TX_C2C_OVERFLOW_BMSK                           0x7
#define HWIO_ECPRI_XBAR_FH_STATUS_SHADOW_TX_C2C_OVERFLOW_SHFT                           0x0

#define HWIO_ECPRI_XBAR_C2C_STATUS_SHADOW_ADDR                                   (ECPRI_XBAR_REGS_REG_BASE      + 0x00002804)
#define HWIO_ECPRI_XBAR_C2C_STATUS_SHADOW_PHYS                                   (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00002804)
#define HWIO_ECPRI_XBAR_C2C_STATUS_SHADOW_OFFS                                   (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00002804)
#define HWIO_ECPRI_XBAR_C2C_STATUS_SHADOW_RMSK                                          0x7
#define HWIO_ECPRI_XBAR_C2C_STATUS_SHADOW_ATTR                                          0x1
#define HWIO_ECPRI_XBAR_C2C_STATUS_SHADOW_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_STATUS_SHADOW_ADDR, HWIO_ECPRI_XBAR_C2C_STATUS_SHADOW_RMSK)
#define HWIO_ECPRI_XBAR_C2C_STATUS_SHADOW_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_C2C_STATUS_SHADOW_ADDR, m)
#define HWIO_ECPRI_XBAR_C2C_STATUS_SHADOW_TX_FH_OVERFLOW_BMSK                           0x7
#define HWIO_ECPRI_XBAR_C2C_STATUS_SHADOW_TX_FH_OVERFLOW_SHFT                           0x0

#define HWIO_ECPRI_XBAR_OCTX_STATUS_SHADOW_ADDR                                  (ECPRI_XBAR_REGS_REG_BASE      + 0x0000280c)
#define HWIO_ECPRI_XBAR_OCTX_STATUS_SHADOW_PHYS                                  (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x0000280c)
#define HWIO_ECPRI_XBAR_OCTX_STATUS_SHADOW_OFFS                                  (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x0000280c)
#define HWIO_ECPRI_XBAR_OCTX_STATUS_SHADOW_RMSK                                       0xfff
#define HWIO_ECPRI_XBAR_OCTX_STATUS_SHADOW_ATTR                                         0x1
#define HWIO_ECPRI_XBAR_OCTX_STATUS_SHADOW_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_OCTX_STATUS_SHADOW_ADDR, HWIO_ECPRI_XBAR_OCTX_STATUS_SHADOW_RMSK)
#define HWIO_ECPRI_XBAR_OCTX_STATUS_SHADOW_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_OCTX_STATUS_SHADOW_ADDR, m)
#define HWIO_ECPRI_XBAR_OCTX_STATUS_SHADOW_TX_C2C_OVERFLOW_BMSK                       0xe00
#define HWIO_ECPRI_XBAR_OCTX_STATUS_SHADOW_TX_C2C_OVERFLOW_SHFT                         0x9
#define HWIO_ECPRI_XBAR_OCTX_STATUS_SHADOW_TX_FH_OVERFLOW_BMSK                        0x1c0
#define HWIO_ECPRI_XBAR_OCTX_STATUS_SHADOW_TX_FH_OVERFLOW_SHFT                          0x6
#define HWIO_ECPRI_XBAR_OCTX_STATUS_SHADOW_TX_C2C_DROP_BMSK                            0x38
#define HWIO_ECPRI_XBAR_OCTX_STATUS_SHADOW_TX_C2C_DROP_SHFT                             0x3
#define HWIO_ECPRI_XBAR_OCTX_STATUS_SHADOW_TX_FH_DROP_BMSK                              0x7
#define HWIO_ECPRI_XBAR_OCTX_STATUS_SHADOW_TX_FH_DROP_SHFT                              0x0

#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_SHADOW_ADDR                               (ECPRI_XBAR_REGS_REG_BASE      + 0x00002810)
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_SHADOW_PHYS                               (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00002810)
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_SHADOW_OFFS                               (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00002810)
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_SHADOW_RMSK                                    0x3ff
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_SHADOW_ATTR                                      0x1
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_SHADOW_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_UC_FHRX_STATUS_SHADOW_ADDR, HWIO_ECPRI_XBAR_UC_FHRX_STATUS_SHADOW_RMSK)
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_SHADOW_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_UC_FHRX_STATUS_SHADOW_ADDR, m)
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_SHADOW_UC_PKT_DROP_BMSK                        0x380
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_SHADOW_UC_PKT_DROP_SHFT                          0x7
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_SHADOW_UC_PKT_ERR_BMSK                          0x70
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_SHADOW_UC_PKT_ERR_SHFT                           0x4
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_SHADOW_UC_PKT_OVERFLOW_BMSK                      0xe
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_SHADOW_UC_PKT_OVERFLOW_SHFT                      0x1
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_SHADOW_UC_PKT_PENDING_BMSK                       0x1
#define HWIO_ECPRI_XBAR_UC_FHRX_STATUS_SHADOW_UC_PKT_PENDING_SHFT                       0x0

#define HWIO_ECPRI_XBAR_OCRX_STATUS_SHADOW_ADDR                                  (ECPRI_XBAR_REGS_REG_BASE      + 0x00002814)
#define HWIO_ECPRI_XBAR_OCRX_STATUS_SHADOW_PHYS                                  (ECPRI_XBAR_REGS_REG_BASE_PHYS + 0x00002814)
#define HWIO_ECPRI_XBAR_OCRX_STATUS_SHADOW_OFFS                                  (ECPRI_XBAR_REGS_REG_BASE_OFFS + 0x00002814)
#define HWIO_ECPRI_XBAR_OCRX_STATUS_SHADOW_RMSK                                         0xf
#define HWIO_ECPRI_XBAR_OCRX_STATUS_SHADOW_ATTR                                         0x1
#define HWIO_ECPRI_XBAR_OCRX_STATUS_SHADOW_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_OCRX_STATUS_SHADOW_ADDR, HWIO_ECPRI_XBAR_OCRX_STATUS_SHADOW_RMSK)
#define HWIO_ECPRI_XBAR_OCRX_STATUS_SHADOW_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_OCRX_STATUS_SHADOW_ADDR, m)
#define HWIO_ECPRI_XBAR_OCRX_STATUS_SHADOW_OCRX_EOP_TIMEOUT_BMSK                        0xf
#define HWIO_ECPRI_XBAR_OCRX_STATUS_SHADOW_OCRX_EOP_TIMEOUT_SHFT                        0x0

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_XBAR_RAM_FH
 *--------------------------------------------------------------------------*/

#define ECPRI_XBAR_RAM_FH_REG_BASE                                      (ECPRI_WRAPPER_BASE      + 0x00424000)
#define ECPRI_XBAR_RAM_FH_REG_BASE_PHYS                                 (ECPRI_WRAPPER_BASE_PHYS + 0x00424000)
#define ECPRI_XBAR_RAM_FH_REG_BASE_OFFS                                 0x00424000

#define HWIO_ECPRI_XBAR_DBG_FHRX_PKT_CNT_n_ADDR(n)                      (ECPRI_XBAR_RAM_FH_REG_BASE      + 0x00000000 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_FHRX_PKT_CNT_n_PHYS(n)                      (ECPRI_XBAR_RAM_FH_REG_BASE_PHYS + 0x00000000 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_FHRX_PKT_CNT_n_OFFS(n)                      (ECPRI_XBAR_RAM_FH_REG_BASE_OFFS + 0x00000000 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_FHRX_PKT_CNT_n_RMSK                         0xffffffff
#define HWIO_ECPRI_XBAR_DBG_FHRX_PKT_CNT_n_MAXn                                 11
#define HWIO_ECPRI_XBAR_DBG_FHRX_PKT_CNT_n_ATTR                                0x1
#define HWIO_ECPRI_XBAR_DBG_FHRX_PKT_CNT_n_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHRX_PKT_CNT_n_ADDR(n), HWIO_ECPRI_XBAR_DBG_FHRX_PKT_CNT_n_RMSK)
#define HWIO_ECPRI_XBAR_DBG_FHRX_PKT_CNT_n_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHRX_PKT_CNT_n_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_DBG_FHRX_PKT_CNT_n_CNT_BMSK                     0xffffffff
#define HWIO_ECPRI_XBAR_DBG_FHRX_PKT_CNT_n_CNT_SHFT                            0x0

#define HWIO_ECPRI_XBAR_DBG_FHRX_DMA_PKT_CNT_ADDR                       (ECPRI_XBAR_RAM_FH_REG_BASE      + 0x00000030)
#define HWIO_ECPRI_XBAR_DBG_FHRX_DMA_PKT_CNT_PHYS                       (ECPRI_XBAR_RAM_FH_REG_BASE_PHYS + 0x00000030)
#define HWIO_ECPRI_XBAR_DBG_FHRX_DMA_PKT_CNT_OFFS                       (ECPRI_XBAR_RAM_FH_REG_BASE_OFFS + 0x00000030)
#define HWIO_ECPRI_XBAR_DBG_FHRX_DMA_PKT_CNT_RMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_DBG_FHRX_DMA_PKT_CNT_ATTR                              0x1
#define HWIO_ECPRI_XBAR_DBG_FHRX_DMA_PKT_CNT_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHRX_DMA_PKT_CNT_ADDR, HWIO_ECPRI_XBAR_DBG_FHRX_DMA_PKT_CNT_RMSK)
#define HWIO_ECPRI_XBAR_DBG_FHRX_DMA_PKT_CNT_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHRX_DMA_PKT_CNT_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_FHRX_DMA_PKT_CNT_CNT_BMSK                   0xffffffff
#define HWIO_ECPRI_XBAR_DBG_FHRX_DMA_PKT_CNT_CNT_SHFT                          0x0

#define HWIO_ECPRI_XBAR_DBG_FHRX_UC_PKT_CNT_ADDR                        (ECPRI_XBAR_RAM_FH_REG_BASE      + 0x00000034)
#define HWIO_ECPRI_XBAR_DBG_FHRX_UC_PKT_CNT_PHYS                        (ECPRI_XBAR_RAM_FH_REG_BASE_PHYS + 0x00000034)
#define HWIO_ECPRI_XBAR_DBG_FHRX_UC_PKT_CNT_OFFS                        (ECPRI_XBAR_RAM_FH_REG_BASE_OFFS + 0x00000034)
#define HWIO_ECPRI_XBAR_DBG_FHRX_UC_PKT_CNT_RMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_DBG_FHRX_UC_PKT_CNT_ATTR                               0x1
#define HWIO_ECPRI_XBAR_DBG_FHRX_UC_PKT_CNT_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHRX_UC_PKT_CNT_ADDR, HWIO_ECPRI_XBAR_DBG_FHRX_UC_PKT_CNT_RMSK)
#define HWIO_ECPRI_XBAR_DBG_FHRX_UC_PKT_CNT_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHRX_UC_PKT_CNT_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_FHRX_UC_PKT_CNT_CNT_BMSK                    0xffffffff
#define HWIO_ECPRI_XBAR_DBG_FHRX_UC_PKT_CNT_CNT_SHFT                           0x0

#define HWIO_ECPRI_XBAR_DBG_FHRX_UC_ERR_PKT_CNT_ADDR                    (ECPRI_XBAR_RAM_FH_REG_BASE      + 0x00000038)
#define HWIO_ECPRI_XBAR_DBG_FHRX_UC_ERR_PKT_CNT_PHYS                    (ECPRI_XBAR_RAM_FH_REG_BASE_PHYS + 0x00000038)
#define HWIO_ECPRI_XBAR_DBG_FHRX_UC_ERR_PKT_CNT_OFFS                    (ECPRI_XBAR_RAM_FH_REG_BASE_OFFS + 0x00000038)
#define HWIO_ECPRI_XBAR_DBG_FHRX_UC_ERR_PKT_CNT_RMSK                    0xffffffff
#define HWIO_ECPRI_XBAR_DBG_FHRX_UC_ERR_PKT_CNT_ATTR                           0x1
#define HWIO_ECPRI_XBAR_DBG_FHRX_UC_ERR_PKT_CNT_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHRX_UC_ERR_PKT_CNT_ADDR, HWIO_ECPRI_XBAR_DBG_FHRX_UC_ERR_PKT_CNT_RMSK)
#define HWIO_ECPRI_XBAR_DBG_FHRX_UC_ERR_PKT_CNT_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHRX_UC_ERR_PKT_CNT_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_FHRX_UC_ERR_PKT_CNT_CNT_BMSK                0xffffffff
#define HWIO_ECPRI_XBAR_DBG_FHRX_UC_ERR_PKT_CNT_CNT_SHFT                       0x0

#define HWIO_ECPRI_XBAR_DBG_FHRX_ERR_PKT_CNT_ADDR                       (ECPRI_XBAR_RAM_FH_REG_BASE      + 0x0000003c)
#define HWIO_ECPRI_XBAR_DBG_FHRX_ERR_PKT_CNT_PHYS                       (ECPRI_XBAR_RAM_FH_REG_BASE_PHYS + 0x0000003c)
#define HWIO_ECPRI_XBAR_DBG_FHRX_ERR_PKT_CNT_OFFS                       (ECPRI_XBAR_RAM_FH_REG_BASE_OFFS + 0x0000003c)
#define HWIO_ECPRI_XBAR_DBG_FHRX_ERR_PKT_CNT_RMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_DBG_FHRX_ERR_PKT_CNT_ATTR                              0x1
#define HWIO_ECPRI_XBAR_DBG_FHRX_ERR_PKT_CNT_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHRX_ERR_PKT_CNT_ADDR, HWIO_ECPRI_XBAR_DBG_FHRX_ERR_PKT_CNT_RMSK)
#define HWIO_ECPRI_XBAR_DBG_FHRX_ERR_PKT_CNT_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHRX_ERR_PKT_CNT_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_FHRX_ERR_PKT_CNT_CNT_BMSK                   0xffffffff
#define HWIO_ECPRI_XBAR_DBG_FHRX_ERR_PKT_CNT_CNT_SHFT                          0x0

#define HWIO_ECPRI_XBAR_DBG_FHTX_PKT_CNT_n_ADDR(n)                      (ECPRI_XBAR_RAM_FH_REG_BASE      + 0x00000040 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_FHTX_PKT_CNT_n_PHYS(n)                      (ECPRI_XBAR_RAM_FH_REG_BASE_PHYS + 0x00000040 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_FHTX_PKT_CNT_n_OFFS(n)                      (ECPRI_XBAR_RAM_FH_REG_BASE_OFFS + 0x00000040 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_FHTX_PKT_CNT_n_RMSK                         0xffffffff
#define HWIO_ECPRI_XBAR_DBG_FHTX_PKT_CNT_n_MAXn                                 11
#define HWIO_ECPRI_XBAR_DBG_FHTX_PKT_CNT_n_ATTR                                0x1
#define HWIO_ECPRI_XBAR_DBG_FHTX_PKT_CNT_n_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHTX_PKT_CNT_n_ADDR(n), HWIO_ECPRI_XBAR_DBG_FHTX_PKT_CNT_n_RMSK)
#define HWIO_ECPRI_XBAR_DBG_FHTX_PKT_CNT_n_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHTX_PKT_CNT_n_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_DBG_FHTX_PKT_CNT_n_CNT_BMSK                     0xffffffff
#define HWIO_ECPRI_XBAR_DBG_FHTX_PKT_CNT_n_CNT_SHFT                            0x0

#define HWIO_ECPRI_XBAR_DBG_FHTX_C2C_PKT_OVF_DROP_CNT_ADDR              (ECPRI_XBAR_RAM_FH_REG_BASE      + 0x00000070)
#define HWIO_ECPRI_XBAR_DBG_FHTX_C2C_PKT_OVF_DROP_CNT_PHYS              (ECPRI_XBAR_RAM_FH_REG_BASE_PHYS + 0x00000070)
#define HWIO_ECPRI_XBAR_DBG_FHTX_C2C_PKT_OVF_DROP_CNT_OFFS              (ECPRI_XBAR_RAM_FH_REG_BASE_OFFS + 0x00000070)
#define HWIO_ECPRI_XBAR_DBG_FHTX_C2C_PKT_OVF_DROP_CNT_RMSK              0xffffffff
#define HWIO_ECPRI_XBAR_DBG_FHTX_C2C_PKT_OVF_DROP_CNT_ATTR                     0x1
#define HWIO_ECPRI_XBAR_DBG_FHTX_C2C_PKT_OVF_DROP_CNT_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHTX_C2C_PKT_OVF_DROP_CNT_ADDR, HWIO_ECPRI_XBAR_DBG_FHTX_C2C_PKT_OVF_DROP_CNT_RMSK)
#define HWIO_ECPRI_XBAR_DBG_FHTX_C2C_PKT_OVF_DROP_CNT_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHTX_C2C_PKT_OVF_DROP_CNT_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_FHTX_C2C_PKT_OVF_DROP_CNT_CNT_BMSK          0xffffffff
#define HWIO_ECPRI_XBAR_DBG_FHTX_C2C_PKT_OVF_DROP_CNT_CNT_SHFT                 0x0

#define HWIO_ECPRI_XBAR_DBG_FHTX_DMA_PKT_CNT_ADDR                       (ECPRI_XBAR_RAM_FH_REG_BASE      + 0x00000074)
#define HWIO_ECPRI_XBAR_DBG_FHTX_DMA_PKT_CNT_PHYS                       (ECPRI_XBAR_RAM_FH_REG_BASE_PHYS + 0x00000074)
#define HWIO_ECPRI_XBAR_DBG_FHTX_DMA_PKT_CNT_OFFS                       (ECPRI_XBAR_RAM_FH_REG_BASE_OFFS + 0x00000074)
#define HWIO_ECPRI_XBAR_DBG_FHTX_DMA_PKT_CNT_RMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_DBG_FHTX_DMA_PKT_CNT_ATTR                              0x1
#define HWIO_ECPRI_XBAR_DBG_FHTX_DMA_PKT_CNT_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHTX_DMA_PKT_CNT_ADDR, HWIO_ECPRI_XBAR_DBG_FHTX_DMA_PKT_CNT_RMSK)
#define HWIO_ECPRI_XBAR_DBG_FHTX_DMA_PKT_CNT_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHTX_DMA_PKT_CNT_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_FHTX_DMA_PKT_CNT_CNT_BMSK                   0xffffffff
#define HWIO_ECPRI_XBAR_DBG_FHTX_DMA_PKT_CNT_CNT_SHFT                          0x0

#define HWIO_ECPRI_XBAR_DBG_FHTX_UC_PKT_CNT_ADDR                        (ECPRI_XBAR_RAM_FH_REG_BASE      + 0x00000078)
#define HWIO_ECPRI_XBAR_DBG_FHTX_UC_PKT_CNT_PHYS                        (ECPRI_XBAR_RAM_FH_REG_BASE_PHYS + 0x00000078)
#define HWIO_ECPRI_XBAR_DBG_FHTX_UC_PKT_CNT_OFFS                        (ECPRI_XBAR_RAM_FH_REG_BASE_OFFS + 0x00000078)
#define HWIO_ECPRI_XBAR_DBG_FHTX_UC_PKT_CNT_RMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_DBG_FHTX_UC_PKT_CNT_ATTR                               0x1
#define HWIO_ECPRI_XBAR_DBG_FHTX_UC_PKT_CNT_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHTX_UC_PKT_CNT_ADDR, HWIO_ECPRI_XBAR_DBG_FHTX_UC_PKT_CNT_RMSK)
#define HWIO_ECPRI_XBAR_DBG_FHTX_UC_PKT_CNT_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHTX_UC_PKT_CNT_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_FHTX_UC_PKT_CNT_CNT_BMSK                    0xffffffff
#define HWIO_ECPRI_XBAR_DBG_FHTX_UC_PKT_CNT_CNT_SHFT                           0x0

#define HWIO_ECPRI_XBAR_DBG_FHRX_C2C_PKT_CNT_n_ADDR(n)                  (ECPRI_XBAR_RAM_FH_REG_BASE      + 0x0000007c + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_FHRX_C2C_PKT_CNT_n_PHYS(n)                  (ECPRI_XBAR_RAM_FH_REG_BASE_PHYS + 0x0000007c + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_FHRX_C2C_PKT_CNT_n_OFFS(n)                  (ECPRI_XBAR_RAM_FH_REG_BASE_OFFS + 0x0000007c + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_FHRX_C2C_PKT_CNT_n_RMSK                     0xffffffff
#define HWIO_ECPRI_XBAR_DBG_FHRX_C2C_PKT_CNT_n_MAXn                              2
#define HWIO_ECPRI_XBAR_DBG_FHRX_C2C_PKT_CNT_n_ATTR                            0x1
#define HWIO_ECPRI_XBAR_DBG_FHRX_C2C_PKT_CNT_n_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHRX_C2C_PKT_CNT_n_ADDR(n), HWIO_ECPRI_XBAR_DBG_FHRX_C2C_PKT_CNT_n_RMSK)
#define HWIO_ECPRI_XBAR_DBG_FHRX_C2C_PKT_CNT_n_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHRX_C2C_PKT_CNT_n_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_DBG_FHRX_C2C_PKT_CNT_n_CNT_BMSK                 0xffffffff
#define HWIO_ECPRI_XBAR_DBG_FHRX_C2C_PKT_CNT_n_CNT_SHFT                        0x0

#define HWIO_ECPRI_XBAR_DBG_FHRX_OC_PKT_CNT_n_ADDR(n)                   (ECPRI_XBAR_RAM_FH_REG_BASE      + 0x00000088 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_FHRX_OC_PKT_CNT_n_PHYS(n)                   (ECPRI_XBAR_RAM_FH_REG_BASE_PHYS + 0x00000088 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_FHRX_OC_PKT_CNT_n_OFFS(n)                   (ECPRI_XBAR_RAM_FH_REG_BASE_OFFS + 0x00000088 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_FHRX_OC_PKT_CNT_n_RMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_DBG_FHRX_OC_PKT_CNT_n_MAXn                               2
#define HWIO_ECPRI_XBAR_DBG_FHRX_OC_PKT_CNT_n_ATTR                             0x1
#define HWIO_ECPRI_XBAR_DBG_FHRX_OC_PKT_CNT_n_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHRX_OC_PKT_CNT_n_ADDR(n), HWIO_ECPRI_XBAR_DBG_FHRX_OC_PKT_CNT_n_RMSK)
#define HWIO_ECPRI_XBAR_DBG_FHRX_OC_PKT_CNT_n_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_FHRX_OC_PKT_CNT_n_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_DBG_FHRX_OC_PKT_CNT_n_CNT_BMSK                  0xffffffff
#define HWIO_ECPRI_XBAR_DBG_FHRX_OC_PKT_CNT_n_CNT_SHFT                         0x0

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_XBAR_RAM_OC
 *--------------------------------------------------------------------------*/

#define ECPRI_XBAR_RAM_OC_REG_BASE                                  (ECPRI_WRAPPER_BASE      + 0x00426000)
#define ECPRI_XBAR_RAM_OC_REG_BASE_PHYS                             (ECPRI_WRAPPER_BASE_PHYS + 0x00426000)
#define ECPRI_XBAR_RAM_OC_REG_BASE_OFFS                             0x00426000

#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_PKT_DROP_CNT_ADDR              (ECPRI_XBAR_RAM_OC_REG_BASE      + 0x00000000)
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_PKT_DROP_CNT_PHYS              (ECPRI_XBAR_RAM_OC_REG_BASE_PHYS + 0x00000000)
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_PKT_DROP_CNT_OFFS              (ECPRI_XBAR_RAM_OC_REG_BASE_OFFS + 0x00000000)
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_PKT_DROP_CNT_RMSK              0xffffffff
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_PKT_DROP_CNT_ATTR                     0x1
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_PKT_DROP_CNT_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCTX_C2C_PKT_DROP_CNT_ADDR, HWIO_ECPRI_XBAR_DBG_OCTX_C2C_PKT_DROP_CNT_RMSK)
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_PKT_DROP_CNT_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCTX_C2C_PKT_DROP_CNT_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_PKT_DROP_CNT_CNT_BMSK          0xffffffff
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_PKT_DROP_CNT_CNT_SHFT                 0x0

#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_PKT_DROP_CNT_ADDR               (ECPRI_XBAR_RAM_OC_REG_BASE      + 0x00000004)
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_PKT_DROP_CNT_PHYS               (ECPRI_XBAR_RAM_OC_REG_BASE_PHYS + 0x00000004)
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_PKT_DROP_CNT_OFFS               (ECPRI_XBAR_RAM_OC_REG_BASE_OFFS + 0x00000004)
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_PKT_DROP_CNT_RMSK               0xffffffff
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_PKT_DROP_CNT_ATTR                      0x1
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_PKT_DROP_CNT_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCTX_FH_PKT_DROP_CNT_ADDR, HWIO_ECPRI_XBAR_DBG_OCTX_FH_PKT_DROP_CNT_RMSK)
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_PKT_DROP_CNT_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCTX_FH_PKT_DROP_CNT_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_PKT_DROP_CNT_CNT_BMSK           0xffffffff
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_PKT_DROP_CNT_CNT_SHFT                  0x0

#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_LEN_ERR_CNT_ADDR               (ECPRI_XBAR_RAM_OC_REG_BASE      + 0x00000008)
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_LEN_ERR_CNT_PHYS               (ECPRI_XBAR_RAM_OC_REG_BASE_PHYS + 0x00000008)
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_LEN_ERR_CNT_OFFS               (ECPRI_XBAR_RAM_OC_REG_BASE_OFFS + 0x00000008)
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_LEN_ERR_CNT_RMSK               0xffffffff
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_LEN_ERR_CNT_ATTR                      0x1
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_LEN_ERR_CNT_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCTX_C2C_LEN_ERR_CNT_ADDR, HWIO_ECPRI_XBAR_DBG_OCTX_C2C_LEN_ERR_CNT_RMSK)
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_LEN_ERR_CNT_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCTX_C2C_LEN_ERR_CNT_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_LEN_ERR_CNT_CNT_BMSK           0xffffffff
#define HWIO_ECPRI_XBAR_DBG_OCTX_C2C_LEN_ERR_CNT_CNT_SHFT                  0x0

#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_LEN_ERR_CNT_ADDR                (ECPRI_XBAR_RAM_OC_REG_BASE      + 0x0000000c)
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_LEN_ERR_CNT_PHYS                (ECPRI_XBAR_RAM_OC_REG_BASE_PHYS + 0x0000000c)
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_LEN_ERR_CNT_OFFS                (ECPRI_XBAR_RAM_OC_REG_BASE_OFFS + 0x0000000c)
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_LEN_ERR_CNT_RMSK                0xffffffff
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_LEN_ERR_CNT_ATTR                       0x1
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_LEN_ERR_CNT_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCTX_FH_LEN_ERR_CNT_ADDR, HWIO_ECPRI_XBAR_DBG_OCTX_FH_LEN_ERR_CNT_RMSK)
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_LEN_ERR_CNT_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCTX_FH_LEN_ERR_CNT_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_LEN_ERR_CNT_CNT_BMSK            0xffffffff
#define HWIO_ECPRI_XBAR_DBG_OCTX_FH_LEN_ERR_CNT_CNT_SHFT                   0x0

#define HWIO_ECPRI_XBAR_DBG_OCTX_PKT_CNT_n_ADDR(n)                  (ECPRI_XBAR_RAM_OC_REG_BASE      + 0x00000010 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_OCTX_PKT_CNT_n_PHYS(n)                  (ECPRI_XBAR_RAM_OC_REG_BASE_PHYS + 0x00000010 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_OCTX_PKT_CNT_n_OFFS(n)                  (ECPRI_XBAR_RAM_OC_REG_BASE_OFFS + 0x00000010 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_OCTX_PKT_CNT_n_RMSK                     0xffffffff
#define HWIO_ECPRI_XBAR_DBG_OCTX_PKT_CNT_n_MAXn                              3
#define HWIO_ECPRI_XBAR_DBG_OCTX_PKT_CNT_n_ATTR                            0x1
#define HWIO_ECPRI_XBAR_DBG_OCTX_PKT_CNT_n_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCTX_PKT_CNT_n_ADDR(n), HWIO_ECPRI_XBAR_DBG_OCTX_PKT_CNT_n_RMSK)
#define HWIO_ECPRI_XBAR_DBG_OCTX_PKT_CNT_n_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCTX_PKT_CNT_n_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_DBG_OCTX_PKT_CNT_n_CNT_BMSK                 0xffffffff
#define HWIO_ECPRI_XBAR_DBG_OCTX_PKT_CNT_n_CNT_SHFT                        0x0

#define HWIO_ECPRI_XBAR_DBG_OCRX_PKT_CNT_n_ADDR(n)                  (ECPRI_XBAR_RAM_OC_REG_BASE      + 0x00000020 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_OCRX_PKT_CNT_n_PHYS(n)                  (ECPRI_XBAR_RAM_OC_REG_BASE_PHYS + 0x00000020 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_OCRX_PKT_CNT_n_OFFS(n)                  (ECPRI_XBAR_RAM_OC_REG_BASE_OFFS + 0x00000020 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_OCRX_PKT_CNT_n_RMSK                     0xffffffff
#define HWIO_ECPRI_XBAR_DBG_OCRX_PKT_CNT_n_MAXn                              3
#define HWIO_ECPRI_XBAR_DBG_OCRX_PKT_CNT_n_ATTR                            0x1
#define HWIO_ECPRI_XBAR_DBG_OCRX_PKT_CNT_n_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCRX_PKT_CNT_n_ADDR(n), HWIO_ECPRI_XBAR_DBG_OCRX_PKT_CNT_n_RMSK)
#define HWIO_ECPRI_XBAR_DBG_OCRX_PKT_CNT_n_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCRX_PKT_CNT_n_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_DBG_OCRX_PKT_CNT_n_CNT_BMSK                 0xffffffff
#define HWIO_ECPRI_XBAR_DBG_OCRX_PKT_CNT_n_CNT_SHFT                        0x0

#define HWIO_ECPRI_XBAR_DBG_OCRX_FH_PKT_CNT_n_ADDR(n)               (ECPRI_XBAR_RAM_OC_REG_BASE      + 0x00000030 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_OCRX_FH_PKT_CNT_n_PHYS(n)               (ECPRI_XBAR_RAM_OC_REG_BASE_PHYS + 0x00000030 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_OCRX_FH_PKT_CNT_n_OFFS(n)               (ECPRI_XBAR_RAM_OC_REG_BASE_OFFS + 0x00000030 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_OCRX_FH_PKT_CNT_n_RMSK                  0xffffffff
#define HWIO_ECPRI_XBAR_DBG_OCRX_FH_PKT_CNT_n_MAXn                          11
#define HWIO_ECPRI_XBAR_DBG_OCRX_FH_PKT_CNT_n_ATTR                         0x1
#define HWIO_ECPRI_XBAR_DBG_OCRX_FH_PKT_CNT_n_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCRX_FH_PKT_CNT_n_ADDR(n), HWIO_ECPRI_XBAR_DBG_OCRX_FH_PKT_CNT_n_RMSK)
#define HWIO_ECPRI_XBAR_DBG_OCRX_FH_PKT_CNT_n_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCRX_FH_PKT_CNT_n_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_DBG_OCRX_FH_PKT_CNT_n_CNT_BMSK              0xffffffff
#define HWIO_ECPRI_XBAR_DBG_OCRX_FH_PKT_CNT_n_CNT_SHFT                     0x0

#define HWIO_ECPRI_XBAR_DBG_OCRX_C2C_PKT_CNT_n_ADDR(n)              (ECPRI_XBAR_RAM_OC_REG_BASE      + 0x00000060 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_OCRX_C2C_PKT_CNT_n_PHYS(n)              (ECPRI_XBAR_RAM_OC_REG_BASE_PHYS + 0x00000060 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_OCRX_C2C_PKT_CNT_n_OFFS(n)              (ECPRI_XBAR_RAM_OC_REG_BASE_OFFS + 0x00000060 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_OCRX_C2C_PKT_CNT_n_RMSK                 0xffffffff
#define HWIO_ECPRI_XBAR_DBG_OCRX_C2C_PKT_CNT_n_MAXn                          2
#define HWIO_ECPRI_XBAR_DBG_OCRX_C2C_PKT_CNT_n_ATTR                        0x1
#define HWIO_ECPRI_XBAR_DBG_OCRX_C2C_PKT_CNT_n_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCRX_C2C_PKT_CNT_n_ADDR(n), HWIO_ECPRI_XBAR_DBG_OCRX_C2C_PKT_CNT_n_RMSK)
#define HWIO_ECPRI_XBAR_DBG_OCRX_C2C_PKT_CNT_n_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_OCRX_C2C_PKT_CNT_n_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_DBG_OCRX_C2C_PKT_CNT_n_CNT_BMSK             0xffffffff
#define HWIO_ECPRI_XBAR_DBG_OCRX_C2C_PKT_CNT_n_CNT_SHFT                    0x0

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_XBAR_RAM_C2C
 *--------------------------------------------------------------------------*/

#define ECPRI_XBAR_RAM_C2C_REG_BASE                                     (ECPRI_WRAPPER_BASE      + 0x00425000)
#define ECPRI_XBAR_RAM_C2C_REG_BASE_PHYS                                (ECPRI_WRAPPER_BASE_PHYS + 0x00425000)
#define ECPRI_XBAR_RAM_C2C_REG_BASE_OFFS                                0x00425000

#define HWIO_ECPRI_XBAR_DBG_C2CRX_PKT_CNT_n_ADDR(n)                     (ECPRI_XBAR_RAM_C2C_REG_BASE      + 0x00000000 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_C2CRX_PKT_CNT_n_PHYS(n)                     (ECPRI_XBAR_RAM_C2C_REG_BASE_PHYS + 0x00000000 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_C2CRX_PKT_CNT_n_OFFS(n)                     (ECPRI_XBAR_RAM_C2C_REG_BASE_OFFS + 0x00000000 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_C2CRX_PKT_CNT_n_RMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_DBG_C2CRX_PKT_CNT_n_MAXn                                 2
#define HWIO_ECPRI_XBAR_DBG_C2CRX_PKT_CNT_n_ATTR                               0x1
#define HWIO_ECPRI_XBAR_DBG_C2CRX_PKT_CNT_n_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_C2CRX_PKT_CNT_n_ADDR(n), HWIO_ECPRI_XBAR_DBG_C2CRX_PKT_CNT_n_RMSK)
#define HWIO_ECPRI_XBAR_DBG_C2CRX_PKT_CNT_n_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_C2CRX_PKT_CNT_n_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_DBG_C2CRX_PKT_CNT_n_CNT_BMSK                    0xffffffff
#define HWIO_ECPRI_XBAR_DBG_C2CRX_PKT_CNT_n_CNT_SHFT                           0x0

#define HWIO_ECPRI_XBAR_DBG_C2CRX_DMA_PKT_CNT_ADDR                      (ECPRI_XBAR_RAM_C2C_REG_BASE      + 0x0000000c)
#define HWIO_ECPRI_XBAR_DBG_C2CRX_DMA_PKT_CNT_PHYS                      (ECPRI_XBAR_RAM_C2C_REG_BASE_PHYS + 0x0000000c)
#define HWIO_ECPRI_XBAR_DBG_C2CRX_DMA_PKT_CNT_OFFS                      (ECPRI_XBAR_RAM_C2C_REG_BASE_OFFS + 0x0000000c)
#define HWIO_ECPRI_XBAR_DBG_C2CRX_DMA_PKT_CNT_RMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_DBG_C2CRX_DMA_PKT_CNT_ATTR                             0x1
#define HWIO_ECPRI_XBAR_DBG_C2CRX_DMA_PKT_CNT_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_C2CRX_DMA_PKT_CNT_ADDR, HWIO_ECPRI_XBAR_DBG_C2CRX_DMA_PKT_CNT_RMSK)
#define HWIO_ECPRI_XBAR_DBG_C2CRX_DMA_PKT_CNT_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_C2CRX_DMA_PKT_CNT_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_C2CRX_DMA_PKT_CNT_CNT_BMSK                  0xffffffff
#define HWIO_ECPRI_XBAR_DBG_C2CRX_DMA_PKT_CNT_CNT_SHFT                         0x0

#define HWIO_ECPRI_XBAR_DBG_C2CRX_ERR_PKT_CNT_ADDR                      (ECPRI_XBAR_RAM_C2C_REG_BASE      + 0x00000010)
#define HWIO_ECPRI_XBAR_DBG_C2CRX_ERR_PKT_CNT_PHYS                      (ECPRI_XBAR_RAM_C2C_REG_BASE_PHYS + 0x00000010)
#define HWIO_ECPRI_XBAR_DBG_C2CRX_ERR_PKT_CNT_OFFS                      (ECPRI_XBAR_RAM_C2C_REG_BASE_OFFS + 0x00000010)
#define HWIO_ECPRI_XBAR_DBG_C2CRX_ERR_PKT_CNT_RMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_DBG_C2CRX_ERR_PKT_CNT_ATTR                             0x1
#define HWIO_ECPRI_XBAR_DBG_C2CRX_ERR_PKT_CNT_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_C2CRX_ERR_PKT_CNT_ADDR, HWIO_ECPRI_XBAR_DBG_C2CRX_ERR_PKT_CNT_RMSK)
#define HWIO_ECPRI_XBAR_DBG_C2CRX_ERR_PKT_CNT_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_C2CRX_ERR_PKT_CNT_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_C2CRX_ERR_PKT_CNT_CNT_BMSK                  0xffffffff
#define HWIO_ECPRI_XBAR_DBG_C2CRX_ERR_PKT_CNT_CNT_SHFT                         0x0

#define HWIO_ECPRI_XBAR_DBG_C2CTX_PKT_CNT_n_ADDR(n)                     (ECPRI_XBAR_RAM_C2C_REG_BASE      + 0x00000014 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_C2CTX_PKT_CNT_n_PHYS(n)                     (ECPRI_XBAR_RAM_C2C_REG_BASE_PHYS + 0x00000014 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_C2CTX_PKT_CNT_n_OFFS(n)                     (ECPRI_XBAR_RAM_C2C_REG_BASE_OFFS + 0x00000014 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_C2CTX_PKT_CNT_n_RMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_DBG_C2CTX_PKT_CNT_n_MAXn                                 2
#define HWIO_ECPRI_XBAR_DBG_C2CTX_PKT_CNT_n_ATTR                               0x1
#define HWIO_ECPRI_XBAR_DBG_C2CTX_PKT_CNT_n_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_C2CTX_PKT_CNT_n_ADDR(n), HWIO_ECPRI_XBAR_DBG_C2CTX_PKT_CNT_n_RMSK)
#define HWIO_ECPRI_XBAR_DBG_C2CTX_PKT_CNT_n_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_C2CTX_PKT_CNT_n_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_DBG_C2CTX_PKT_CNT_n_CNT_BMSK                    0xffffffff
#define HWIO_ECPRI_XBAR_DBG_C2CTX_PKT_CNT_n_CNT_SHFT                           0x0

#define HWIO_ECPRI_XBAR_DBG_C2CTX_FH_PKT_OVF_DROP_CNT_ADDR              (ECPRI_XBAR_RAM_C2C_REG_BASE      + 0x00000020)
#define HWIO_ECPRI_XBAR_DBG_C2CTX_FH_PKT_OVF_DROP_CNT_PHYS              (ECPRI_XBAR_RAM_C2C_REG_BASE_PHYS + 0x00000020)
#define HWIO_ECPRI_XBAR_DBG_C2CTX_FH_PKT_OVF_DROP_CNT_OFFS              (ECPRI_XBAR_RAM_C2C_REG_BASE_OFFS + 0x00000020)
#define HWIO_ECPRI_XBAR_DBG_C2CTX_FH_PKT_OVF_DROP_CNT_RMSK              0xffffffff
#define HWIO_ECPRI_XBAR_DBG_C2CTX_FH_PKT_OVF_DROP_CNT_ATTR                     0x1
#define HWIO_ECPRI_XBAR_DBG_C2CTX_FH_PKT_OVF_DROP_CNT_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_C2CTX_FH_PKT_OVF_DROP_CNT_ADDR, HWIO_ECPRI_XBAR_DBG_C2CTX_FH_PKT_OVF_DROP_CNT_RMSK)
#define HWIO_ECPRI_XBAR_DBG_C2CTX_FH_PKT_OVF_DROP_CNT_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_C2CTX_FH_PKT_OVF_DROP_CNT_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_C2CTX_FH_PKT_OVF_DROP_CNT_CNT_BMSK          0xffffffff
#define HWIO_ECPRI_XBAR_DBG_C2CTX_FH_PKT_OVF_DROP_CNT_CNT_SHFT                 0x0

#define HWIO_ECPRI_XBAR_DBG_C2CTX_DMA_PKT_CNT_ADDR                      (ECPRI_XBAR_RAM_C2C_REG_BASE      + 0x00000024)
#define HWIO_ECPRI_XBAR_DBG_C2CTX_DMA_PKT_CNT_PHYS                      (ECPRI_XBAR_RAM_C2C_REG_BASE_PHYS + 0x00000024)
#define HWIO_ECPRI_XBAR_DBG_C2CTX_DMA_PKT_CNT_OFFS                      (ECPRI_XBAR_RAM_C2C_REG_BASE_OFFS + 0x00000024)
#define HWIO_ECPRI_XBAR_DBG_C2CTX_DMA_PKT_CNT_RMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_DBG_C2CTX_DMA_PKT_CNT_ATTR                             0x1
#define HWIO_ECPRI_XBAR_DBG_C2CTX_DMA_PKT_CNT_IN          \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_C2CTX_DMA_PKT_CNT_ADDR, HWIO_ECPRI_XBAR_DBG_C2CTX_DMA_PKT_CNT_RMSK)
#define HWIO_ECPRI_XBAR_DBG_C2CTX_DMA_PKT_CNT_INM(m)      \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_C2CTX_DMA_PKT_CNT_ADDR, m)
#define HWIO_ECPRI_XBAR_DBG_C2CTX_DMA_PKT_CNT_CNT_BMSK                  0xffffffff
#define HWIO_ECPRI_XBAR_DBG_C2CTX_DMA_PKT_CNT_CNT_SHFT                         0x0

#define HWIO_ECPRI_XBAR_DBG_C2CRX_FH_PKT_CNT_n_ADDR(n)                  (ECPRI_XBAR_RAM_C2C_REG_BASE      + 0x00000028 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_C2CRX_FH_PKT_CNT_n_PHYS(n)                  (ECPRI_XBAR_RAM_C2C_REG_BASE_PHYS + 0x00000028 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_C2CRX_FH_PKT_CNT_n_OFFS(n)                  (ECPRI_XBAR_RAM_C2C_REG_BASE_OFFS + 0x00000028 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_C2CRX_FH_PKT_CNT_n_RMSK                     0xffffffff
#define HWIO_ECPRI_XBAR_DBG_C2CRX_FH_PKT_CNT_n_MAXn                              2
#define HWIO_ECPRI_XBAR_DBG_C2CRX_FH_PKT_CNT_n_ATTR                            0x1
#define HWIO_ECPRI_XBAR_DBG_C2CRX_FH_PKT_CNT_n_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_C2CRX_FH_PKT_CNT_n_ADDR(n), HWIO_ECPRI_XBAR_DBG_C2CRX_FH_PKT_CNT_n_RMSK)
#define HWIO_ECPRI_XBAR_DBG_C2CRX_FH_PKT_CNT_n_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_C2CRX_FH_PKT_CNT_n_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_DBG_C2CRX_FH_PKT_CNT_n_CNT_BMSK                 0xffffffff
#define HWIO_ECPRI_XBAR_DBG_C2CRX_FH_PKT_CNT_n_CNT_SHFT                        0x0

#define HWIO_ECPRI_XBAR_DBG_C2CRX_OC_PKT_CNT_n_ADDR(n)                  (ECPRI_XBAR_RAM_C2C_REG_BASE      + 0x00000034 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_C2CRX_OC_PKT_CNT_n_PHYS(n)                  (ECPRI_XBAR_RAM_C2C_REG_BASE_PHYS + 0x00000034 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_C2CRX_OC_PKT_CNT_n_OFFS(n)                  (ECPRI_XBAR_RAM_C2C_REG_BASE_OFFS + 0x00000034 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_DBG_C2CRX_OC_PKT_CNT_n_RMSK                     0xffffffff
#define HWIO_ECPRI_XBAR_DBG_C2CRX_OC_PKT_CNT_n_MAXn                              2
#define HWIO_ECPRI_XBAR_DBG_C2CRX_OC_PKT_CNT_n_ATTR                            0x1
#define HWIO_ECPRI_XBAR_DBG_C2CRX_OC_PKT_CNT_n_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_C2CRX_OC_PKT_CNT_n_ADDR(n), HWIO_ECPRI_XBAR_DBG_C2CRX_OC_PKT_CNT_n_RMSK)
#define HWIO_ECPRI_XBAR_DBG_C2CRX_OC_PKT_CNT_n_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_DBG_C2CRX_OC_PKT_CNT_n_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_DBG_C2CRX_OC_PKT_CNT_n_CNT_BMSK                 0xffffffff
#define HWIO_ECPRI_XBAR_DBG_C2CRX_OC_PKT_CNT_n_CNT_SHFT                        0x0

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_XBAR_LUT
 *--------------------------------------------------------------------------*/

#define ECPRI_XBAR_LUT_REG_BASE                                        (ECPRI_WRAPPER_BASE      + 0x00500000)
#define ECPRI_XBAR_LUT_REG_BASE_PHYS                                   (ECPRI_WRAPPER_BASE_PHYS + 0x00500000)
#define ECPRI_XBAR_LUT_REG_BASE_OFFS                                   0x00500000

#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_ADDR(m,n)                         (ECPRI_XBAR_LUT_REG_BASE      + 0x00000000 + 0x40000 * (m) + 0x4 * (n))
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_PHYS(m,n)                         (ECPRI_XBAR_LUT_REG_BASE_PHYS + 0x00000000 + 0x40000 * (m) + 0x4 * (n))
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_OFFS(m,n)                         (ECPRI_XBAR_LUT_REG_BASE_OFFS + 0x00000000 + 0x40000 * (m) + 0x4 * (n))
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_RMSK                                  0x7fff
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_MAXm                                       2
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_MAXn                                       1
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_ATTR                                     0x3
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_INI2(m,n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_FHRX_m_LUT_n_ADDR(m,n), HWIO_ECPRI_XBAR_FHRX_m_LUT_n_RMSK)
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_INMI2(m,n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_FHRX_m_LUT_n_ADDR(m,n), mask)
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_OUTI2(m,n,val)    \
        out_dword(HWIO_ECPRI_XBAR_FHRX_m_LUT_n_ADDR(m,n),val)
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_OUTMI2(m,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_FHRX_m_LUT_n_ADDR(m,n),mask,val,HWIO_ECPRI_XBAR_FHRX_m_LUT_n_INI2(m,n))
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_OTHER_ROUTE_TO_DMA_BMSK               0x4000
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_OTHER_ROUTE_TO_DMA_SHFT                  0xe
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_OTHER_ROUTE_TO_C2C_BMSK               0x2000
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_OTHER_ROUTE_TO_C2C_SHFT                  0xd
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_OTHER_ROUTE_TO_ORAN_BMSK              0x1000
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_OTHER_ROUTE_TO_ORAN_SHFT                 0xc
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_OTHER_OC_LINK_ID_BMSK                  0xc00
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_OTHER_OC_LINK_ID_SHFT                    0xa
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_DL_ROUTE_TO_DMA_BMSK                   0x200
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_DL_ROUTE_TO_DMA_SHFT                     0x9
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_DL_ROUTE_TO_C2C_BMSK                   0x100
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_DL_ROUTE_TO_C2C_SHFT                     0x8
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_DL_ROUTE_TO_ORAN_BMSK                   0x80
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_DL_ROUTE_TO_ORAN_SHFT                    0x7
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_DL_OC_LINK_ID_BMSK                      0x60
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_DL_OC_LINK_ID_SHFT                       0x5
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_UL_ROUTE_TO_DMA_BMSK                    0x10
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_UL_ROUTE_TO_DMA_SHFT                     0x4
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_UL_ROUTE_TO_C2C_BMSK                     0x8
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_UL_ROUTE_TO_C2C_SHFT                     0x3
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_UL_ROUTE_TO_ORAN_BMSK                    0x4
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_UL_ROUTE_TO_ORAN_SHFT                    0x2
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_UL_OC_LINK_ID_BMSK                       0x3
#define HWIO_ECPRI_XBAR_FHRX_m_LUT_n_UL_OC_LINK_ID_SHFT                       0x0

#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_ADDR(m,n)                        (ECPRI_XBAR_LUT_REG_BASE      + 0x000c0000 + 0x40000 * (m) + 0x4 * (n))
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_PHYS(m,n)                        (ECPRI_XBAR_LUT_REG_BASE_PHYS + 0x000c0000 + 0x40000 * (m) + 0x4 * (n))
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_OFFS(m,n)                        (ECPRI_XBAR_LUT_REG_BASE_OFFS + 0x000c0000 + 0x40000 * (m) + 0x4 * (n))
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_MAXm                                      2
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_MAXn                                      1
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_ATTR                                    0x3
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_INI2(m,n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_ADDR(m,n), HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_RMSK)
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_INMI2(m,n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_ADDR(m,n), mask)
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_OUTI2(m,n,val)    \
        out_dword(HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_ADDR(m,n),val)
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_OUTMI2(m,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_ADDR(m,n),mask,val,HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_INI2(m,n))
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_L2_ENCAP_INFO_BMSK               0xff000000
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_L2_ENCAP_INFO_SHFT                     0x18
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_L3_ENCAP_INFO_BMSK                 0xff0000
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_L3_ENCAP_INFO_SHFT                     0x10
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_L3_ENCAP_VALID_BMSK                  0x8000
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_L3_ENCAP_VALID_SHFT                     0xf
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_OTHER_ROUTE_BMSK                     0x7000
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_OTHER_ROUTE_SHFT                        0xc
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_OTHER_ROUTE_INVALID_FVAL                0x0
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_OTHER_ROUTE_ROUTE_TO_FH_FVAL            0x1
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_OTHER_ROUTE_ROUTE_TO_DMA_FVAL           0x2
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_OTHER_ROUTE_RESERVED_FVAL               0x3
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_OTHER_ROUTE_ROUTE_TO_OC0_FVAL           0x4
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_OTHER_ROUTE_ROUTE_TO_OC1_FVAL           0x5
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_OTHER_ROUTE_ROUTE_TO_OC2_FVAL           0x6
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_OTHER_ROUTE_ROUTE_TO_OC3_FVAL           0x7
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_CP_DL_ROUTE_BMSK                      0xe00
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_CP_DL_ROUTE_SHFT                        0x9
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_CP_DL_ROUTE_INVALID_FVAL                0x0
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_CP_DL_ROUTE_ROUTE_TO_FH_FVAL            0x1
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_CP_DL_ROUTE_ROUTE_TO_DMA_FVAL           0x2
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_CP_DL_ROUTE_RESERVED_FVAL               0x3
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_CP_DL_ROUTE_ROUTE_TO_OC0_FVAL           0x4
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_CP_DL_ROUTE_ROUTE_TO_OC1_FVAL           0x5
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_CP_DL_ROUTE_ROUTE_TO_OC2_FVAL           0x6
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_CP_DL_ROUTE_ROUTE_TO_OC3_FVAL           0x7
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_CP_UL_ROUTE_BMSK                      0x1c0
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_CP_UL_ROUTE_SHFT                        0x6
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_CP_UL_ROUTE_INVALID_FVAL                0x0
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_CP_UL_ROUTE_ROUTE_TO_FH_FVAL            0x1
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_CP_UL_ROUTE_ROUTE_TO_DMA_FVAL           0x2
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_CP_UL_ROUTE_RESERVED_FVAL               0x3
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_CP_UL_ROUTE_ROUTE_TO_OC0_FVAL           0x4
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_CP_UL_ROUTE_ROUTE_TO_OC1_FVAL           0x5
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_CP_UL_ROUTE_ROUTE_TO_OC2_FVAL           0x6
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_CP_UL_ROUTE_ROUTE_TO_OC3_FVAL           0x7
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_UP_DL_ROUTE_BMSK                       0x38
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_UP_DL_ROUTE_SHFT                        0x3
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_UP_DL_ROUTE_INVALID_FVAL                0x0
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_UP_DL_ROUTE_ROUTE_TO_FH_FVAL            0x1
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_UP_DL_ROUTE_ROUTE_TO_DMA_FVAL           0x2
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_UP_DL_ROUTE_RESERVED_FVAL               0x3
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_UP_DL_ROUTE_ROUTE_TO_OC0_FVAL           0x4
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_UP_DL_ROUTE_ROUTE_TO_OC1_FVAL           0x5
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_UP_DL_ROUTE_ROUTE_TO_OC2_FVAL           0x6
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_UP_DL_ROUTE_ROUTE_TO_OC3_FVAL           0x7
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_UP_UL_ROUTE_BMSK                        0x7
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_UP_UL_ROUTE_SHFT                        0x0
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_UP_UL_ROUTE_INVALID_FVAL                0x0
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_UP_UL_ROUTE_ROUTE_TO_FH_FVAL            0x1
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_UP_UL_ROUTE_ROUTE_TO_DMA_FVAL           0x2
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_UP_UL_ROUTE_RESERVED_FVAL               0x3
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_UP_UL_ROUTE_ROUTE_TO_OC0_FVAL           0x4
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_UP_UL_ROUTE_ROUTE_TO_OC1_FVAL           0x5
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_UP_UL_ROUTE_ROUTE_TO_OC2_FVAL           0x6
#define HWIO_ECPRI_XBAR_C2CRX_m_LUT_n_UP_UL_ROUTE_ROUTE_TO_OC3_FVAL           0x7

#define HWIO_ECPRI_XBAR_OCRX_m_LUT_n_ADDR(m,n)                         (ECPRI_XBAR_LUT_REG_BASE      + 0x00180000 + 0x40000 * (m) + 0x4 * (n))
#define HWIO_ECPRI_XBAR_OCRX_m_LUT_n_PHYS(m,n)                         (ECPRI_XBAR_LUT_REG_BASE_PHYS + 0x00180000 + 0x40000 * (m) + 0x4 * (n))
#define HWIO_ECPRI_XBAR_OCRX_m_LUT_n_OFFS(m,n)                         (ECPRI_XBAR_LUT_REG_BASE_OFFS + 0x00180000 + 0x40000 * (m) + 0x4 * (n))
#define HWIO_ECPRI_XBAR_OCRX_m_LUT_n_RMSK                                 0x3ffff
#define HWIO_ECPRI_XBAR_OCRX_m_LUT_n_MAXm                                       2
#define HWIO_ECPRI_XBAR_OCRX_m_LUT_n_MAXn                                       1
#define HWIO_ECPRI_XBAR_OCRX_m_LUT_n_ATTR                                     0x3
#define HWIO_ECPRI_XBAR_OCRX_m_LUT_n_INI2(m,n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_OCRX_m_LUT_n_ADDR(m,n), HWIO_ECPRI_XBAR_OCRX_m_LUT_n_RMSK)
#define HWIO_ECPRI_XBAR_OCRX_m_LUT_n_INMI2(m,n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_OCRX_m_LUT_n_ADDR(m,n), mask)
#define HWIO_ECPRI_XBAR_OCRX_m_LUT_n_OUTI2(m,n,val)    \
        out_dword(HWIO_ECPRI_XBAR_OCRX_m_LUT_n_ADDR(m,n),val)
#define HWIO_ECPRI_XBAR_OCRX_m_LUT_n_OUTMI2(m,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_OCRX_m_LUT_n_ADDR(m,n),mask,val,HWIO_ECPRI_XBAR_OCRX_m_LUT_n_INI2(m,n))
#define HWIO_ECPRI_XBAR_OCRX_m_LUT_n_VALID_BMSK                           0x20000
#define HWIO_ECPRI_XBAR_OCRX_m_LUT_n_VALID_SHFT                              0x11
#define HWIO_ECPRI_XBAR_OCRX_m_LUT_n_L3_ENCAP_VALID_BMSK                  0x10000
#define HWIO_ECPRI_XBAR_OCRX_m_LUT_n_L3_ENCAP_VALID_SHFT                     0x10
#define HWIO_ECPRI_XBAR_OCRX_m_LUT_n_L3_ENCAP_INFO_BMSK                    0xff00
#define HWIO_ECPRI_XBAR_OCRX_m_LUT_n_L3_ENCAP_INFO_SHFT                       0x8
#define HWIO_ECPRI_XBAR_OCRX_m_LUT_n_L2_ENCAP_INFO_BMSK                      0xff
#define HWIO_ECPRI_XBAR_OCRX_m_LUT_n_L2_ENCAP_INFO_SHFT                       0x0

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_XBAR_NFAPI_LUT
 *--------------------------------------------------------------------------*/

#define ECPRI_XBAR_NFAPI_LUT_REG_BASE                          (ECPRI_WRAPPER_BASE      + 0x00427000)
#define ECPRI_XBAR_NFAPI_LUT_REG_BASE_PHYS                     (ECPRI_WRAPPER_BASE_PHYS + 0x00427000)
#define ECPRI_XBAR_NFAPI_LUT_REG_BASE_OFFS                     0x00427000

#define HWIO_ECPRI_XBAR_NFAPI_LUT_n_ADDR(n)                    (ECPRI_XBAR_NFAPI_LUT_REG_BASE      + 0x00000000 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_NFAPI_LUT_n_PHYS(n)                    (ECPRI_XBAR_NFAPI_LUT_REG_BASE_PHYS + 0x00000000 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_NFAPI_LUT_n_OFFS(n)                    (ECPRI_XBAR_NFAPI_LUT_REG_BASE_OFFS + 0x00000000 + 0x4 * (n))
#define HWIO_ECPRI_XBAR_NFAPI_LUT_n_RMSK                            0x7ff
#define HWIO_ECPRI_XBAR_NFAPI_LUT_n_MAXn                              255
#define HWIO_ECPRI_XBAR_NFAPI_LUT_n_ATTR                              0x3
#define HWIO_ECPRI_XBAR_NFAPI_LUT_n_INI(n)        \
        in_dword_masked(HWIO_ECPRI_XBAR_NFAPI_LUT_n_ADDR(n), HWIO_ECPRI_XBAR_NFAPI_LUT_n_RMSK)
#define HWIO_ECPRI_XBAR_NFAPI_LUT_n_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_XBAR_NFAPI_LUT_n_ADDR(n), mask)
#define HWIO_ECPRI_XBAR_NFAPI_LUT_n_OUTI(n,val)    \
        out_dword(HWIO_ECPRI_XBAR_NFAPI_LUT_n_ADDR(n),val)
#define HWIO_ECPRI_XBAR_NFAPI_LUT_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_XBAR_NFAPI_LUT_n_ADDR(n),mask,val,HWIO_ECPRI_XBAR_NFAPI_LUT_n_INI(n))
#define HWIO_ECPRI_XBAR_NFAPI_LUT_n_VALID_BMSK                      0x400
#define HWIO_ECPRI_XBAR_NFAPI_LUT_n_VALID_SHFT                        0xa
#define HWIO_ECPRI_XBAR_NFAPI_LUT_n_GSI_ID_BMSK                     0x300
#define HWIO_ECPRI_XBAR_NFAPI_LUT_n_GSI_ID_SHFT                       0x8
#define HWIO_ECPRI_XBAR_NFAPI_LUT_n_DMA_RING_ID_BMSK                 0xfe
#define HWIO_ECPRI_XBAR_NFAPI_LUT_n_DMA_RING_ID_SHFT                  0x1
#define HWIO_ECPRI_XBAR_NFAPI_LUT_n_ROUTE_TO_DMA_BMSK                 0x1
#define HWIO_ECPRI_XBAR_NFAPI_LUT_n_ROUTE_TO_DMA_SHFT                 0x0


#endif /* __ECPRI_XBAR_HWIO_H__ */
