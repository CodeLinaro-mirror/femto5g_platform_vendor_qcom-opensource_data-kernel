/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef __ECPRI_ORAN_XTOR_HWIO_H__
#define __ECPRI_ORAN_XTOR_HWIO_H__
/**
  @file ecpri_oran_xtor_hwio.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
    ECPRI_ORAN_XTOR.*

  'Include' filters applied: <none>
  'Exclude' filters applied: RESERVED DUMMY

  Attribute definitions for the HWIO_*_ATTR macros are as follows:
    0x0: Command register
    0x1: Read-Only
    0x2: Write-Only
    0x3: Read/Write
*/
/*----------------------------------------------------------------------------
 * MODULE: ECPRI_ORAN_XTOR
 *--------------------------------------------------------------------------*/

#define ECPRI_ORAN_XTOR_REG_BASE                                                               (ECPRI_WRAPPER_BASE      + 0x00228000)
#define ECPRI_ORAN_XTOR_REG_BASE_PHYS                                                          (ECPRI_WRAPPER_BASE_PHYS + 0x00228000)
#define ECPRI_ORAN_XTOR_REG_BASE_OFFS                                                          0x00228000

#define HWIO_ECPRI_ORAN_XTOR_TX_n_CTL_REG_ADDR(n)                                              (ECPRI_ORAN_XTOR_REG_BASE      + 0x00000000 + 0x300 * (n))
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CTL_REG_PHYS(n)                                              (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00000000 + 0x300 * (n))
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CTL_REG_OFFS(n)                                              (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00000000 + 0x300 * (n))
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CTL_REG_RMSK                                                        0x3
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CTL_REG_MAXn                                                          3
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CTL_REG_ATTR                                                        0x3
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CTL_REG_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_TX_n_CTL_REG_ADDR(n), HWIO_ECPRI_ORAN_XTOR_TX_n_CTL_REG_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CTL_REG_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_TX_n_CTL_REG_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CTL_REG_OUTI(n,val)    \
        out_dword(HWIO_ECPRI_ORAN_XTOR_TX_n_CTL_REG_ADDR(n),val)
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CTL_REG_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_ORAN_XTOR_TX_n_CTL_REG_ADDR(n),mask,val,HWIO_ECPRI_ORAN_XTOR_TX_n_CTL_REG_INI(n))
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CTL_REG_RD_IDX_WRAP_CNT_SATURATE_EN_BMSK                            0x2
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CTL_REG_RD_IDX_WRAP_CNT_SATURATE_EN_SHFT                            0x1
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CTL_REG_WRAP_EN_BMSK                                                0x1
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CTL_REG_WRAP_EN_SHFT                                                0x0

#define HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_ADDR(n)                                        (ECPRI_ORAN_XTOR_REG_BASE      + 0x00000004 + 0x300 * (n))
#define HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_PHYS(n)                                        (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00000004 + 0x300 * (n))
#define HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_OFFS(n)                                        (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00000004 + 0x300 * (n))
#define HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_RMSK                                               0x1f1f
#define HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_MAXn                                                    3
#define HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_ATTR                                                  0x3
#define HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_ADDR(n), HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_OUTI(n,val)    \
        out_dword(HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_ADDR(n),val)
#define HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_ADDR(n),mask,val,HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_INI(n))
#define HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_RD_IDX_BMSK                                        0x1f00
#define HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_RD_IDX_SHFT                                           0x8
#define HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_WR_IDX_BMSK                                          0x1f
#define HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_WR_IDX_SHFT                                           0x0

#define HWIO_ECPRI_ORAN_XTOR_TX_n_PKT_CNT_REG_ADDR(n)                                          (ECPRI_ORAN_XTOR_REG_BASE      + 0x00000008 + 0x300 * (n))
#define HWIO_ECPRI_ORAN_XTOR_TX_n_PKT_CNT_REG_PHYS(n)                                          (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00000008 + 0x300 * (n))
#define HWIO_ECPRI_ORAN_XTOR_TX_n_PKT_CNT_REG_OFFS(n)                                          (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00000008 + 0x300 * (n))
#define HWIO_ECPRI_ORAN_XTOR_TX_n_PKT_CNT_REG_RMSK                                             0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_TX_n_PKT_CNT_REG_MAXn                                                      3
#define HWIO_ECPRI_ORAN_XTOR_TX_n_PKT_CNT_REG_ATTR                                                    0x1
#define HWIO_ECPRI_ORAN_XTOR_TX_n_PKT_CNT_REG_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_TX_n_PKT_CNT_REG_ADDR(n), HWIO_ECPRI_ORAN_XTOR_TX_n_PKT_CNT_REG_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_TX_n_PKT_CNT_REG_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_TX_n_PKT_CNT_REG_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_TX_n_PKT_CNT_REG_PKT_CNT_BMSK                                     0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_TX_n_PKT_CNT_REG_PKT_CNT_SHFT                                            0x0

#define HWIO_ECPRI_ORAN_XTOR_TX_n_BACKPRESSURE_CNT_REG_ADDR(n)                                 (ECPRI_ORAN_XTOR_REG_BASE      + 0x0000000c + 0x300 * (n))
#define HWIO_ECPRI_ORAN_XTOR_TX_n_BACKPRESSURE_CNT_REG_PHYS(n)                                 (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x0000000c + 0x300 * (n))
#define HWIO_ECPRI_ORAN_XTOR_TX_n_BACKPRESSURE_CNT_REG_OFFS(n)                                 (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x0000000c + 0x300 * (n))
#define HWIO_ECPRI_ORAN_XTOR_TX_n_BACKPRESSURE_CNT_REG_RMSK                                    0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_TX_n_BACKPRESSURE_CNT_REG_MAXn                                             3
#define HWIO_ECPRI_ORAN_XTOR_TX_n_BACKPRESSURE_CNT_REG_ATTR                                           0x1
#define HWIO_ECPRI_ORAN_XTOR_TX_n_BACKPRESSURE_CNT_REG_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_TX_n_BACKPRESSURE_CNT_REG_ADDR(n), HWIO_ECPRI_ORAN_XTOR_TX_n_BACKPRESSURE_CNT_REG_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_TX_n_BACKPRESSURE_CNT_REG_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_TX_n_BACKPRESSURE_CNT_REG_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_TX_n_BACKPRESSURE_CNT_REG_BACKPRESSURE_CNT_BMSK                   0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_TX_n_BACKPRESSURE_CNT_REG_BACKPRESSURE_CNT_SHFT                          0x0

#define HWIO_ECPRI_ORAN_XTOR_TX_n_RD_IDX_WRAP_CNT_ADDR(n)                                      (ECPRI_ORAN_XTOR_REG_BASE      + 0x00000290 + 0x300 * (n))
#define HWIO_ECPRI_ORAN_XTOR_TX_n_RD_IDX_WRAP_CNT_PHYS(n)                                      (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00000290 + 0x300 * (n))
#define HWIO_ECPRI_ORAN_XTOR_TX_n_RD_IDX_WRAP_CNT_OFFS(n)                                      (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00000290 + 0x300 * (n))
#define HWIO_ECPRI_ORAN_XTOR_TX_n_RD_IDX_WRAP_CNT_RMSK                                           0xffffff
#define HWIO_ECPRI_ORAN_XTOR_TX_n_RD_IDX_WRAP_CNT_MAXn                                                  3
#define HWIO_ECPRI_ORAN_XTOR_TX_n_RD_IDX_WRAP_CNT_ATTR                                                0x1
#define HWIO_ECPRI_ORAN_XTOR_TX_n_RD_IDX_WRAP_CNT_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_TX_n_RD_IDX_WRAP_CNT_ADDR(n), HWIO_ECPRI_ORAN_XTOR_TX_n_RD_IDX_WRAP_CNT_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_TX_n_RD_IDX_WRAP_CNT_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_TX_n_RD_IDX_WRAP_CNT_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_TX_n_RD_IDX_WRAP_CNT_RD_IDX_WRAP_CNT_BMSK                           0xffffff
#define HWIO_ECPRI_ORAN_XTOR_TX_n_RD_IDX_WRAP_CNT_RD_IDX_WRAP_CNT_SHFT                                0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_ADDR(n)                                              (ECPRI_ORAN_XTOR_REG_BASE      + 0x00001000 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_PHYS(n)                                              (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00001000 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_OFFS(n)                                              (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00001000 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_RMSK                                                 0xff111111
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_MAXn                                                          3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_ATTR                                                        0x3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_ADDR(n), HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_OUTI(n,val)    \
        out_dword(HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_ADDR(n),val)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_ADDR(n),mask,val,HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_INI(n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_MAX_BW_EN_BMSK                                       0x80000000
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_MAX_BW_EN_SHFT                                             0x1f
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_MIN_BW_EN_BMSK                                       0x40000000
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_MIN_BW_EN_SHFT                                             0x1e
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_MAX_BW_CLEAR_BMSK                                    0x20000000
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_MAX_BW_CLEAR_SHFT                                          0x1d
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_MIN_BW_CLEAR_BMSK                                    0x10000000
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_MIN_BW_CLEAR_SHFT                                          0x1c
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_MAX_LATENCY_CLEAR_BMSK                                0x8000000
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_MAX_LATENCY_CLEAR_SHFT                                     0x1b
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_MIN_LATENCY_CLEAR_BMSK                                0x4000000
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_MIN_LATENCY_CLEAR_SHFT                                     0x1a
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_AVG_LATENCY_CLEAR_BMSK                                0x2000000
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_AVG_LATENCY_CLEAR_SHFT                                     0x19
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_SEQNUM_ERR_EN_BMSK                                    0x1000000
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_SEQNUM_ERR_EN_SHFT                                         0x18
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_LATENCY_ERR_EN_BMSK                                    0x100000
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_LATENCY_ERR_EN_SHFT                                        0x14
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_CRC_ERR_EN_BMSK                                         0x10000
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_CRC_ERR_EN_SHFT                                            0x10
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_LEN_ERR_EN_BMSK                                          0x1000
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_LEN_ERR_EN_SHFT                                             0xc
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_TIME_ERR_EN_BMSK                                          0x100
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_TIME_ERR_EN_SHFT                                            0x8
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_DATA_ERR_EN_BMSK                                           0x10
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_DATA_ERR_EN_SHFT                                            0x4
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_TGT_RX_ERR_EN_BMSK                                          0x1
#define HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_TGT_RX_ERR_EN_SHFT                                          0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_ADDR(n)                                            (ECPRI_ORAN_XTOR_REG_BASE      + 0x00001004 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_PHYS(n)                                            (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00001004 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_OFFS(n)                                            (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00001004 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_RMSK                                               0xf1111111
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_MAXn                                                        3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_ATTR                                                      0x3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_ADDR(n), HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_OUTI(n,val)    \
        out_dword(HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_ADDR(n),val)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_ADDR(n),mask,val,HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_INI(n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_SEQNUM_ERR_BMSK                                    0xf0000000
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_SEQNUM_ERR_SHFT                                          0x1c
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_LATENCY_ERR_BMSK                                    0x1000000
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_LATENCY_ERR_SHFT                                         0x18
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_CRC_ERR_BMSK                                         0x100000
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_CRC_ERR_SHFT                                             0x14
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_LEN_ERR_BMSK                                          0x10000
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_LEN_ERR_SHFT                                             0x10
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_TIME_ERR_BMSK                                          0x1000
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_TIME_ERR_SHFT                                             0xc
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_DATA_ERR_BMSK                                           0x100
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_DATA_ERR_SHFT                                             0x8
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_TGT_RX_ERR_BMSK                                          0x10
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_TGT_RX_ERR_SHFT                                           0x4
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_RESET_ERR_STATUS_BMSK                                     0x1
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_RESET_ERR_STATUS_SHFT                                     0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_n_PKT_CNT_REG_ADDR(n)                                          (ECPRI_ORAN_XTOR_REG_BASE      + 0x00001008 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PKT_CNT_REG_PHYS(n)                                          (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00001008 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PKT_CNT_REG_OFFS(n)                                          (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00001008 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PKT_CNT_REG_RMSK                                             0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PKT_CNT_REG_MAXn                                                      3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PKT_CNT_REG_ATTR                                                    0x1
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PKT_CNT_REG_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_PKT_CNT_REG_ADDR(n), HWIO_ECPRI_ORAN_XTOR_RX_n_PKT_CNT_REG_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PKT_CNT_REG_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_PKT_CNT_REG_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PKT_CNT_REG_PKT_CNT_BMSK                                     0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PKT_CNT_REG_PKT_CNT_SHFT                                            0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_ADDR(n)                                     (ECPRI_ORAN_XTOR_REG_BASE      + 0x00001010 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_PHYS(n)                                     (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00001010 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_OFFS(n)                                     (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00001010 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_RMSK                                        0x1f1f33ff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_MAXn                                                 3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_ATTR                                               0x1
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_ADDR(n), HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_XU_NUM_BMSK                                 0x1f000000
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_XU_NUM_SHFT                                       0x18
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_SEQNUM_BMSK                                   0x1f0000
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_SEQNUM_SHFT                                       0x10
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_TGT_RX_BMSK                                     0x3000
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_TGT_RX_SHFT                                        0xc
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_SRC_TX_BMSK                                      0x300
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_SRC_TX_SHFT                                        0x8
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_ECPRI_MSG_TYPE_BMSK                               0xff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_ECPRI_MSG_TYPE_SHFT                                0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_1_REG_ADDR(n)                                     (ECPRI_ORAN_XTOR_REG_BASE      + 0x00001014 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_1_REG_PHYS(n)                                     (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00001014 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_1_REG_OFFS(n)                                     (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00001014 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_1_REG_RMSK                                        0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_1_REG_MAXn                                                 3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_1_REG_ATTR                                               0x1
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_1_REG_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_1_REG_ADDR(n), HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_1_REG_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_1_REG_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_1_REG_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_1_REG_ECPRI_PCID_BMSK                             0xffff0000
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_1_REG_ECPRI_PCID_SHFT                                   0x10
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_1_REG_ECPRI_PAYLOAD_SIZE_BMSK                         0xffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_1_REG_ECPRI_PAYLOAD_SIZE_SHFT                            0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_2_REG_ADDR(n)                                     (ECPRI_ORAN_XTOR_REG_BASE      + 0x00001018 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_2_REG_PHYS(n)                                     (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00001018 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_2_REG_OFFS(n)                                     (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00001018 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_2_REG_RMSK                                        0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_2_REG_MAXn                                                 3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_2_REG_ATTR                                               0x1
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_2_REG_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_2_REG_ADDR(n), HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_2_REG_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_2_REG_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_2_REG_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_2_REG_TIMESTAMP_BMSK                              0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_2_REG_TIMESTAMP_SHFT                                     0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_3_REG_ADDR(n)                                     (ECPRI_ORAN_XTOR_REG_BASE      + 0x0000101c + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_3_REG_PHYS(n)                                     (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x0000101c + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_3_REG_OFFS(n)                                     (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x0000101c + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_3_REG_RMSK                                        0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_3_REG_MAXn                                                 3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_3_REG_ATTR                                               0x1
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_3_REG_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_3_REG_ADDR(n), HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_3_REG_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_3_REG_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_3_REG_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_3_REG_INIT_DATA_BMSK                              0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_3_REG_INIT_DATA_SHFT                                     0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_ADDR(n)                                (ECPRI_ORAN_XTOR_REG_BASE      + 0x00001020 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_PHYS(n)                                (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00001020 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_OFFS(n)                                (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00001020 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_RMSK                                       0xffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_MAXn                                            3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_ATTR                                          0x3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_ADDR(n), HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_OUTI(n,val)    \
        out_dword(HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_ADDR(n),val)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_ADDR(n),mask,val,HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_INI(n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_XU_NUM_BMSK                                0xf800
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_XU_NUM_SHFT                                   0xb
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_SEQNUM_ERR_BMSK                             0x780
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_SEQNUM_ERR_SHFT                               0x7
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_LATENCY_ERR_BMSK                             0x40
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_LATENCY_ERR_SHFT                              0x6
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_CRC_ERR_BMSK                                 0x20
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_CRC_ERR_SHFT                                  0x5
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_LEN_ERR_BMSK                                 0x10
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_LEN_ERR_SHFT                                  0x4
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_TIME_ERR_BMSK                                 0x8
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_TIME_ERR_SHFT                                 0x3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_DATA_ERR_BMSK                                 0x4
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_DATA_ERR_SHFT                                 0x2
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_TGT_RX_ERR_BMSK                               0x2
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_TGT_RX_ERR_SHFT                               0x1
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_RESET_ERROR_DUMP_BMSK                         0x1
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_RESET_ERROR_DUMP_SHFT                         0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_PACKET_LATENCY_ADDR(n)                        (ECPRI_ORAN_XTOR_REG_BASE      + 0x00001024 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_PACKET_LATENCY_PHYS(n)                        (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00001024 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_PACKET_LATENCY_OFFS(n)                        (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00001024 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_PACKET_LATENCY_RMSK                           0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_PACKET_LATENCY_MAXn                                    3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_PACKET_LATENCY_ATTR                                  0x1
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_PACKET_LATENCY_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_PACKET_LATENCY_ADDR(n), HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_PACKET_LATENCY_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_PACKET_LATENCY_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_PACKET_LATENCY_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_PACKET_LATENCY_ACTUAL_LATENCY_BMSK            0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_PACKET_LATENCY_ACTUAL_LATENCY_SHFT                   0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_EXPECTED_VALUES_ADDR(n)                       (ECPRI_ORAN_XTOR_REG_BASE      + 0x00001028 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_EXPECTED_VALUES_PHYS(n)                       (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00001028 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_EXPECTED_VALUES_OFFS(n)                       (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00001028 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_EXPECTED_VALUES_RMSK                          0xffff001f
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_EXPECTED_VALUES_MAXn                                   3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_EXPECTED_VALUES_ATTR                                 0x1
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_EXPECTED_VALUES_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_EXPECTED_VALUES_ADDR(n), HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_EXPECTED_VALUES_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_EXPECTED_VALUES_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_EXPECTED_VALUES_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_EXPECTED_VALUES_ACTUAL_LENGTH_BMSK            0xffff0000
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_EXPECTED_VALUES_ACTUAL_LENGTH_SHFT                  0x10
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_EXPECTED_VALUES_EXPECTED_SEQNUM_BMSK                0x1f
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_EXPECTED_VALUES_EXPECTED_SEQNUM_SHFT                 0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_n_KBYTE_CNT_REG_ADDR(n)                                        (ECPRI_ORAN_XTOR_REG_BASE      + 0x0000102c + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_KBYTE_CNT_REG_PHYS(n)                                        (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x0000102c + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_KBYTE_CNT_REG_OFFS(n)                                        (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x0000102c + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_KBYTE_CNT_REG_RMSK                                           0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_KBYTE_CNT_REG_MAXn                                                    3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_KBYTE_CNT_REG_ATTR                                                  0x1
#define HWIO_ECPRI_ORAN_XTOR_RX_n_KBYTE_CNT_REG_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_KBYTE_CNT_REG_ADDR(n), HWIO_ECPRI_ORAN_XTOR_RX_n_KBYTE_CNT_REG_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_KBYTE_CNT_REG_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_KBYTE_CNT_REG_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_KBYTE_CNT_REG_KBYTE_CNT_BMSK                                 0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_KBYTE_CNT_REG_KBYTE_CNT_SHFT                                        0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL_ADDR                                             (ECPRI_ORAN_XTOR_REG_BASE      + 0x00001030)
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL_PHYS                                             (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00001030)
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL_OFFS                                             (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00001030)
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL_RMSK                                                    0x3
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL_ATTR                                                    0x3
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL_IN          \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL_ADDR, HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL_INM(m)      \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL_ADDR, m)
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL_OUT(v)      \
        out_dword(HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL_ADDR,v)
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL_ADDR,m,v,HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL_IN)
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL_CLR_BMSK                                                0x2
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL_CLR_SHFT                                                0x1
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL_EN_BMSK                                                 0x1
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL_EN_SHFT                                                 0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_0_ADDR                                  (ECPRI_ORAN_XTOR_REG_BASE      + 0x00001034)
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_0_PHYS                                  (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00001034)
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_0_OFFS                                  (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00001034)
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_0_RMSK                                  0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_0_ATTR                                         0x1
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_0_IN          \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_0_ADDR, HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_0_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_0_INM(m)      \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_0_ADDR, m)
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_0_QTIMER_LSB_BMSK                       0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_0_QTIMER_LSB_SHFT                              0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_1_ADDR                                  (ECPRI_ORAN_XTOR_REG_BASE      + 0x00001038)
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_1_PHYS                                  (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00001038)
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_1_OFFS                                  (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00001038)
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_1_RMSK                                    0xffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_1_ATTR                                         0x1
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_1_IN          \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_1_ADDR, HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_1_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_1_INM(m)      \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_1_ADDR, m)
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_1_QTIMER_MSB_BMSK                         0xffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_1_QTIMER_MSB_SHFT                              0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_n_MSRMNT_PER_REG_ADDR(n)                                       (ECPRI_ORAN_XTOR_REG_BASE      + 0x00001128 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MSRMNT_PER_REG_PHYS(n)                                       (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00001128 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MSRMNT_PER_REG_OFFS(n)                                       (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00001128 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MSRMNT_PER_REG_RMSK                                          0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MSRMNT_PER_REG_MAXn                                                   3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MSRMNT_PER_REG_ATTR                                                 0x3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MSRMNT_PER_REG_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_MSRMNT_PER_REG_ADDR(n), HWIO_ECPRI_ORAN_XTOR_RX_n_MSRMNT_PER_REG_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MSRMNT_PER_REG_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_MSRMNT_PER_REG_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MSRMNT_PER_REG_OUTI(n,val)    \
        out_dword(HWIO_ECPRI_ORAN_XTOR_RX_n_MSRMNT_PER_REG_ADDR(n),val)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MSRMNT_PER_REG_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_ORAN_XTOR_RX_n_MSRMNT_PER_REG_ADDR(n),mask,val,HWIO_ECPRI_ORAN_XTOR_RX_n_MSRMNT_PER_REG_INI(n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MSRMNT_PER_REG_MSRMNT_PER_BMSK                               0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MSRMNT_PER_REG_MSRMNT_PER_SHFT                                      0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_BW_REG_ADDR(n)                               (ECPRI_ORAN_XTOR_REG_BASE      + 0x00001130 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_BW_REG_PHYS(n)                               (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00001130 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_BW_REG_OFFS(n)                               (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00001130 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_BW_REG_RMSK                                  0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_BW_REG_MAXn                                           3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_BW_REG_ATTR                                         0x1
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_BW_REG_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_BW_REG_ADDR(n), HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_BW_REG_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_BW_REG_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_BW_REG_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_BW_REG_PER_CNT_ABV_TGT_BW_BMSK               0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_BW_REG_PER_CNT_ABV_TGT_BW_SHFT                      0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_BW_REG_ADDR(n)                               (ECPRI_ORAN_XTOR_REG_BASE      + 0x00001134 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_BW_REG_PHYS(n)                               (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00001134 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_BW_REG_OFFS(n)                               (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00001134 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_BW_REG_RMSK                                  0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_BW_REG_MAXn                                           3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_BW_REG_ATTR                                         0x1
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_BW_REG_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_BW_REG_ADDR(n), HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_BW_REG_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_BW_REG_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_BW_REG_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_BW_REG_PER_CNT_BLW_TGT_BW_BMSK               0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_BW_REG_PER_CNT_BLW_TGT_BW_SHFT                      0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_LAT_REG_ADDR(n)                              (ECPRI_ORAN_XTOR_REG_BASE      + 0x00001138 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_LAT_REG_PHYS(n)                              (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00001138 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_LAT_REG_OFFS(n)                              (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00001138 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_LAT_REG_RMSK                                 0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_LAT_REG_MAXn                                          3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_LAT_REG_ATTR                                        0x1
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_LAT_REG_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_LAT_REG_ADDR(n), HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_LAT_REG_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_LAT_REG_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_LAT_REG_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_LAT_REG_PER_CNT_ABV_TGT_LAT_BMSK             0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_LAT_REG_PER_CNT_ABV_TGT_LAT_SHFT                    0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_LAT_REG_ADDR(n)                              (ECPRI_ORAN_XTOR_REG_BASE      + 0x0000113c + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_LAT_REG_PHYS(n)                              (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x0000113c + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_LAT_REG_OFFS(n)                              (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x0000113c + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_LAT_REG_RMSK                                 0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_LAT_REG_MAXn                                          3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_LAT_REG_ATTR                                        0x1
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_LAT_REG_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_LAT_REG_ADDR(n), HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_LAT_REG_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_LAT_REG_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_LAT_REG_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_LAT_REG_PER_CNT_BLW_TGT_LAT_BMSK             0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_LAT_REG_PER_CNT_BLW_TGT_LAT_SHFT                    0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_BW_VAL_REG_ADDR(n)                                       (ECPRI_ORAN_XTOR_REG_BASE      + 0x00001140 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_BW_VAL_REG_PHYS(n)                                       (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00001140 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_BW_VAL_REG_OFFS(n)                                       (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00001140 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_BW_VAL_REG_RMSK                                          0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_BW_VAL_REG_MAXn                                                   3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_BW_VAL_REG_ATTR                                                 0x3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_BW_VAL_REG_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_BW_VAL_REG_ADDR(n), HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_BW_VAL_REG_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_BW_VAL_REG_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_BW_VAL_REG_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_BW_VAL_REG_OUTI(n,val)    \
        out_dword(HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_BW_VAL_REG_ADDR(n),val)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_BW_VAL_REG_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_BW_VAL_REG_ADDR(n),mask,val,HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_BW_VAL_REG_INI(n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_BW_VAL_REG_TGT_BW_BMSK                                   0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_BW_VAL_REG_TGT_BW_SHFT                                          0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_BW_VAL_REG_ADDR(n)                                       (ECPRI_ORAN_XTOR_REG_BASE      + 0x00001144 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_BW_VAL_REG_PHYS(n)                                       (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00001144 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_BW_VAL_REG_OFFS(n)                                       (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00001144 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_BW_VAL_REG_RMSK                                          0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_BW_VAL_REG_MAXn                                                   3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_BW_VAL_REG_ATTR                                                 0x1
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_BW_VAL_REG_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_BW_VAL_REG_ADDR(n), HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_BW_VAL_REG_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_BW_VAL_REG_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_BW_VAL_REG_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_BW_VAL_REG_MAX_BW_BMSK                                   0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_BW_VAL_REG_MAX_BW_SHFT                                          0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_n_MIN_BW_VAL_REG_ADDR(n)                                       (ECPRI_ORAN_XTOR_REG_BASE      + 0x00001148 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MIN_BW_VAL_REG_PHYS(n)                                       (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00001148 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MIN_BW_VAL_REG_OFFS(n)                                       (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00001148 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MIN_BW_VAL_REG_RMSK                                          0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MIN_BW_VAL_REG_MAXn                                                   3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MIN_BW_VAL_REG_ATTR                                                 0x1
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MIN_BW_VAL_REG_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_MIN_BW_VAL_REG_ADDR(n), HWIO_ECPRI_ORAN_XTOR_RX_n_MIN_BW_VAL_REG_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MIN_BW_VAL_REG_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_MIN_BW_VAL_REG_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MIN_BW_VAL_REG_MIN_BW_BMSK                                   0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MIN_BW_VAL_REG_MIN_BW_SHFT                                          0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_LAT_VAL_REG_ADDR(n)                                      (ECPRI_ORAN_XTOR_REG_BASE      + 0x00001150 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_LAT_VAL_REG_PHYS(n)                                      (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00001150 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_LAT_VAL_REG_OFFS(n)                                      (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00001150 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_LAT_VAL_REG_RMSK                                         0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_LAT_VAL_REG_MAXn                                                  3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_LAT_VAL_REG_ATTR                                                0x3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_LAT_VAL_REG_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_LAT_VAL_REG_ADDR(n), HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_LAT_VAL_REG_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_LAT_VAL_REG_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_LAT_VAL_REG_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_LAT_VAL_REG_OUTI(n,val)    \
        out_dword(HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_LAT_VAL_REG_ADDR(n),val)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_LAT_VAL_REG_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_LAT_VAL_REG_ADDR(n),mask,val,HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_LAT_VAL_REG_INI(n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_LAT_VAL_REG_TGT_LATENCY_BMSK                             0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_TGT_LAT_VAL_REG_TGT_LATENCY_SHFT                                    0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LAT_VAL_REG_ADDR(n)                                      (ECPRI_ORAN_XTOR_REG_BASE      + 0x00001154 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LAT_VAL_REG_PHYS(n)                                      (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00001154 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LAT_VAL_REG_OFFS(n)                                      (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00001154 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LAT_VAL_REG_RMSK                                         0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LAT_VAL_REG_MAXn                                                  3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LAT_VAL_REG_ATTR                                                0x1
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LAT_VAL_REG_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LAT_VAL_REG_ADDR(n), HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LAT_VAL_REG_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LAT_VAL_REG_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LAT_VAL_REG_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LAT_VAL_REG_MAX_LATENCY_BMSK                             0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LAT_VAL_REG_MAX_LATENCY_SHFT                                    0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_n_MIN_LAT_VAL_REG_ADDR(n)                                      (ECPRI_ORAN_XTOR_REG_BASE      + 0x00001158 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MIN_LAT_VAL_REG_PHYS(n)                                      (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00001158 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MIN_LAT_VAL_REG_OFFS(n)                                      (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00001158 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MIN_LAT_VAL_REG_RMSK                                         0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MIN_LAT_VAL_REG_MAXn                                                  3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MIN_LAT_VAL_REG_ATTR                                                0x1
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MIN_LAT_VAL_REG_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_MIN_LAT_VAL_REG_ADDR(n), HWIO_ECPRI_ORAN_XTOR_RX_n_MIN_LAT_VAL_REG_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MIN_LAT_VAL_REG_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_MIN_LAT_VAL_REG_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MIN_LAT_VAL_REG_MIN_LATENCY_BMSK                             0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MIN_LAT_VAL_REG_MIN_LATENCY_SHFT                                    0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0_ADDR(n)                                       (ECPRI_ORAN_XTOR_REG_BASE      + 0x0000115c + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0_PHYS(n)                                       (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x0000115c + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0_OFFS(n)                                       (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x0000115c + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0_RMSK                                          0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0_MAXn                                                   3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0_ATTR                                                 0x1
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0_ADDR(n), HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0_TGT_RX_ERR_COUNT_BMSK                         0xff000000
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0_TGT_RX_ERR_COUNT_SHFT                               0x18
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0_TIME_ERR_COUNT_BMSK                             0xff0000
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0_TIME_ERR_COUNT_SHFT                                 0x10
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0_LEN_ERR_COUNT_BMSK                                0xff00
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0_LEN_ERR_COUNT_SHFT                                   0x8
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0_SEQNUM_ERR_COUNT_BMSK                               0xff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0_SEQNUM_ERR_COUNT_SHFT                                0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1_ADDR(n)                                       (ECPRI_ORAN_XTOR_REG_BASE      + 0x00001160 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1_PHYS(n)                                       (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00001160 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1_OFFS(n)                                       (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00001160 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1_RMSK                                          0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1_MAXn                                                   3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1_ATTR                                                 0x1
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1_ADDR(n), HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1_OVERALL_ERR_COUNT_BMSK                        0xff000000
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1_OVERALL_ERR_COUNT_SHFT                              0x18
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1_LATENCY_ERR_COUNT_BMSK                          0xff0000
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1_LATENCY_ERR_COUNT_SHFT                              0x10
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1_DATA_ERR_COUNT_BMSK                               0xff00
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1_DATA_ERR_COUNT_SHFT                                  0x8
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1_CRC_ERR_COUNT_BMSK                                  0xff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1_CRC_ERR_COUNT_SHFT                                   0x0

#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LATENCY_EXPECTED_ADDR(n)                                 (ECPRI_ORAN_XTOR_REG_BASE      + 0x00001164 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LATENCY_EXPECTED_PHYS(n)                                 (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00001164 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LATENCY_EXPECTED_OFFS(n)                                 (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00001164 + 0x200 * (n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LATENCY_EXPECTED_RMSK                                    0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LATENCY_EXPECTED_MAXn                                             3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LATENCY_EXPECTED_ATTR                                           0x3
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LATENCY_EXPECTED_INI(n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LATENCY_EXPECTED_ADDR(n), HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LATENCY_EXPECTED_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LATENCY_EXPECTED_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LATENCY_EXPECTED_ADDR(n), mask)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LATENCY_EXPECTED_OUTI(n,val)    \
        out_dword(HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LATENCY_EXPECTED_ADDR(n),val)
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LATENCY_EXPECTED_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LATENCY_EXPECTED_ADDR(n),mask,val,HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LATENCY_EXPECTED_INI(n))
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LATENCY_EXPECTED_MAX_LATENCY_BMSK                        0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LATENCY_EXPECTED_MAX_LATENCY_SHFT                               0x0

#define HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_LSB_ADDR                                            (ECPRI_ORAN_XTOR_REG_BASE      + 0x00001fd0)
#define HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_LSB_PHYS                                            (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00001fd0)
#define HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_LSB_OFFS                                            (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00001fd0)
#define HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_LSB_RMSK                                            0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_LSB_ATTR                                                   0x3
#define HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_LSB_IN          \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_LSB_ADDR, HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_LSB_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_LSB_INM(m)      \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_LSB_ADDR, m)
#define HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_LSB_OUT(v)      \
        out_dword(HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_LSB_ADDR,v)
#define HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_LSB_ADDR,m,v,HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_LSB_IN)
#define HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_LSB_OFFSET_LSBS_BMSK                                0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_LSB_OFFSET_LSBS_SHFT                                       0x0

#define HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB_ADDR                                            (ECPRI_ORAN_XTOR_REG_BASE      + 0x00001fd4)
#define HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB_PHYS                                            (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00001fd4)
#define HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB_OFFS                                            (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00001fd4)
#define HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB_RMSK                                             0x1ffffff
#define HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB_ATTR                                                   0x3
#define HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB_IN          \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB_ADDR, HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB_INM(m)      \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB_ADDR, m)
#define HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB_OUT(v)      \
        out_dword(HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB_ADDR,v)
#define HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB_ADDR,m,v,HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB_IN)
#define HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB_OFFSET_SIGN_BIT_BMSK                             0x1000000
#define HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB_OFFSET_SIGN_BIT_SHFT                                  0x18
#define HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB_OFFSET_MSBS_BMSK                                  0xffffff
#define HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB_OFFSET_MSBS_SHFT                                       0x0

#define HWIO_ECPRI_ORAN_XTOR_HW_PARAMS_ADDR                                                    (ECPRI_ORAN_XTOR_REG_BASE      + 0x00001fe0)
#define HWIO_ECPRI_ORAN_XTOR_HW_PARAMS_PHYS                                                    (ECPRI_ORAN_XTOR_REG_BASE_PHYS + 0x00001fe0)
#define HWIO_ECPRI_ORAN_XTOR_HW_PARAMS_OFFS                                                    (ECPRI_ORAN_XTOR_REG_BASE_OFFS + 0x00001fe0)
#define HWIO_ECPRI_ORAN_XTOR_HW_PARAMS_RMSK                                                        0xff1f
#define HWIO_ECPRI_ORAN_XTOR_HW_PARAMS_ATTR                                                           0x1
#define HWIO_ECPRI_ORAN_XTOR_HW_PARAMS_IN          \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_HW_PARAMS_ADDR, HWIO_ECPRI_ORAN_XTOR_HW_PARAMS_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_HW_PARAMS_INM(m)      \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_HW_PARAMS_ADDR, m)
#define HWIO_ECPRI_ORAN_XTOR_HW_PARAMS_NUM_RX_PORTS_BMSK                                           0xf000
#define HWIO_ECPRI_ORAN_XTOR_HW_PARAMS_NUM_RX_PORTS_SHFT                                              0xc
#define HWIO_ECPRI_ORAN_XTOR_HW_PARAMS_NUM_TX_PORTS_BMSK                                            0xf00
#define HWIO_ECPRI_ORAN_XTOR_HW_PARAMS_NUM_TX_PORTS_SHFT                                              0x8
#define HWIO_ECPRI_ORAN_XTOR_HW_PARAMS_RING_SIZE_BMSK                                                0x1f
#define HWIO_ECPRI_ORAN_XTOR_HW_PARAMS_RING_SIZE_SHFT                                                 0x0

#if 0
/* ECPRI_GLOBAL_XTOR_CFG */
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_RX_RESET_3_BMSK                                    0x100
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_RX_RESET_3_SHFT                                        8
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_RX_RESET_2_BMSK                                     0x80
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_RX_RESET_2_SHFT                                        7
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_RX_RESET_1_BMSK                                     0x40
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_RX_RESET_1_SHFT                                        6
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_RX_RESET_0_BMSK                                     0x20
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_RX_RESET_0_SHFT                                        5
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_TX_RESET_3_BMSK                                     0x10
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_TX_RESET_3_SHFT                                        4
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_TX_RESET_2_BMSK                                      0x8
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_TX_RESET_2_SHFT                                        3
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_TX_RESET_1_BMSK                                      0x4
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_TX_RESET_1_SHFT                                        2
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_TX_RESET_0_BMSK                                      0x2
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_TX_RESET_0_SHFT                                        1
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_EN_BMSK                                              0x1
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_EN_SHFT                                                0
#endif

/* TODO, need to check how to retain these as its not part of SWI : Mayank */
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CMD_m_k_ADDR(base,k,m,n)     ((base) + 0x00000010 + 0x4 * (k) + 0x10 * (m) + 0x300 * (n))
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CMD_m_k_PHYS(base,k,m,n)     ((base) + 0x00000010 + 0x4 * (k) + 0x10 * (m) + 0x300 * (n))
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CMD_m_k_OFFS(base,k,m,n)     (0x00000010 + 0x4 * (k) + 0x10 * (m) + 0x300 * (n))
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CMD_m_k_RMSK               0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CMD_m_k_MAXk                        4 /* 4 dword per entry */
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CMD_m_k_MAXm                       30 /* 30 entries */
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CMD_m_k_MAXn                        3 /* 4 rings */
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CMD_m_k_POR                0x00000000
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CMD_m_k_POR_RMSK           0x00000000
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CMD_m_k_ATTR                      0x3
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CMD_m_k_INI3(base,k,m,n)        \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_TX_n_CMD_m_k_ADDR(base,k,m,n), HWIO_ECPRI_ORAN_XTOR_TX_n_CMD_m_k_RMSK)
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CMD_m_k_INMI3(base,k,m,n,mask)    \
        in_dword_masked(HWIO_ECPRI_ORAN_XTOR_TX_n_CMD_m_k_ADDR(base,k,m,n), mask)
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CMD_m_k_OUTI3(base,k,m,n,val)    \
        out_dword(HWIO_ECPRI_ORAN_XTOR_TX_n_CMD_m_k_ADDR(base,k,m,n),val)
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CMD_m_k_OUTMI3(base,k,m,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_ORAN_XTOR_TX_n_CMD_m_k_ADDR(base,k,m,n),mask,val,HWIO_ECPRI_ORAN_XTOR_TX_n_CMD_m_k_INI3(base,k,m,n))
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CMD_m_k_DATA_BMSK          0xffffffff
#define HWIO_ECPRI_ORAN_XTOR_TX_n_CMD_m_k_DATA_SHFT                 0x0


#endif /* __ECPRI_ORAN_XTOR_HWIO_H__ */
