/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef __ECPRISS_XBAR_H__
#define __ECPRISS_XBAR_H__

/**
  @file ecpriss_xbar.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
  QDRUxxx (Lassen) [lassen_v1.0_p3q1r15.7]

  This file contains HWIO register definitions for the following modules:
  ECPRI_XBAR


  Generation parameters:
  { 'explicit-addressing': True,
  'filename': 'ecpriss_xbar.h',
  'modules': ['ECPRI_XBAR'],
  'output-fvals': True,
  'output-offsets': True}
  */

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_XBAR
 *--------------------------------------------------------------------------*/

#define ECPRI_XBAR_REG_BASE                                                           (ECPRI_WRAPPER_BASE      + 0x00220000)
#define ECPRI_XBAR_REG_BASE_SIZE                                                      0x8000
#define ECPRI_XBAR_REG_BASE_USED                                                      0x4010
#define ECPRI_XBAR_REG_BASE_OFFS                                                      0x00220000

#define HWIO_ECPRI_XBAR_XBAR_CFG_ADDR(x)                                              ((x) + 0x0)
#define HWIO_ECPRI_XBAR_XBAR_CFG_OFFS                                                 (0x0)
#define HWIO_ECPRI_XBAR_XBAR_CFG_RMSK                                                      0x1ff
#define HWIO_ECPRI_XBAR_XBAR_CFG_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_CFG_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_CFG_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_CFG_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_CFG_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_CFG_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_CFG_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_CFG_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_CFG_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_CFG_AXIS_ARB_FIX_EN_BMSK                                      0x200
#define HWIO_ECPRI_XBAR_XBAR_CFG_AXIS_ARB_FIX_EN_SHFT                                          9
#define HWIO_ECPRI_XBAR_XBAR_CFG_TPDM_EN_BMSK                                              0x100
#define HWIO_ECPRI_XBAR_XBAR_CFG_TPDM_EN_SHFT                                                  8
#define HWIO_ECPRI_XBAR_XBAR_CFG_XBAR_CNT_CLR_EN_BMSK                                       0x80
#define HWIO_ECPRI_XBAR_XBAR_CFG_XBAR_CNT_CLR_EN_SHFT                                          7
#define HWIO_ECPRI_XBAR_XBAR_CFG_XBAR_CNT_EN_BMSK                                           0x40
#define HWIO_ECPRI_XBAR_XBAR_CFG_XBAR_CNT_EN_SHFT                                              6
#define HWIO_ECPRI_XBAR_XBAR_CFG_C2CTX_CNT_EN_BMSK                                          0x20
#define HWIO_ECPRI_XBAR_XBAR_CFG_C2CTX_CNT_EN_SHFT                                             5
#define HWIO_ECPRI_XBAR_XBAR_CFG_C2CRX_CNT_EN_BMSK                                          0x10
#define HWIO_ECPRI_XBAR_XBAR_CFG_C2CRX_CNT_EN_SHFT                                             4
#define HWIO_ECPRI_XBAR_XBAR_CFG_OCTX_CNT_EN_BMSK                                            0x8
#define HWIO_ECPRI_XBAR_XBAR_CFG_OCTX_CNT_EN_SHFT                                              3
#define HWIO_ECPRI_XBAR_XBAR_CFG_OCRX_CNT_EN_BMSK                                            0x4
#define HWIO_ECPRI_XBAR_XBAR_CFG_OCRX_CNT_EN_SHFT                                              2
#define HWIO_ECPRI_XBAR_XBAR_CFG_FHTX_CNT_EN_BMSK                                            0x2
#define HWIO_ECPRI_XBAR_XBAR_CFG_FHTX_CNT_EN_SHFT                                              1
#define HWIO_ECPRI_XBAR_XBAR_CFG_FHRX_CNT_EN_BMSK                                            0x1
#define HWIO_ECPRI_XBAR_XBAR_CFG_FHRX_CNT_EN_SHFT                                              0

#define HWIO_ECPRI_XBAR_XBAR_C2C_IPG_CFG_ADDR(x)                                      ((x) + 0x4)
#define HWIO_ECPRI_XBAR_XBAR_C2C_IPG_CFG_OFFS                                         (0x4)
#define HWIO_ECPRI_XBAR_XBAR_C2C_IPG_CFG_RMSK                                         0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_IPG_CFG_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_C2C_IPG_CFG_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_IPG_CFG_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_IPG_CFG_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_C2C_IPG_CFG_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_IPG_CFG_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_C2C_IPG_CFG_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_IPG_CFG_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_C2C_IPG_CFG_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_IPG_CFG_DMA_EOP_IPG_BMSK                             0xff000000
#define HWIO_ECPRI_XBAR_XBAR_C2C_IPG_CFG_DMA_EOP_IPG_SHFT                                     24
#define HWIO_ECPRI_XBAR_XBAR_C2C_IPG_CFG_OC_EOP_IPG_BMSK                                0xff0000
#define HWIO_ECPRI_XBAR_XBAR_C2C_IPG_CFG_OC_EOP_IPG_SHFT                                      16
#define HWIO_ECPRI_XBAR_XBAR_C2C_IPG_CFG_DMA_SOP_IPG_BMSK                                 0xff00
#define HWIO_ECPRI_XBAR_XBAR_C2C_IPG_CFG_DMA_SOP_IPG_SHFT                                      8
#define HWIO_ECPRI_XBAR_XBAR_C2C_IPG_CFG_OC_SOP_IPG_BMSK                                    0xff
#define HWIO_ECPRI_XBAR_XBAR_C2C_IPG_CFG_OC_SOP_IPG_SHFT                                       0

#define HWIO_ECPRI_XBAR_XBAR_FH_IPG_CFG_ADDR(x)                                       ((x) + 0x8)
#define HWIO_ECPRI_XBAR_XBAR_FH_IPG_CFG_OFFS                                          (0x8)
#define HWIO_ECPRI_XBAR_XBAR_FH_IPG_CFG_RMSK                                          0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_IPG_CFG_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_FH_IPG_CFG_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_IPG_CFG_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_IPG_CFG_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_FH_IPG_CFG_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_IPG_CFG_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_FH_IPG_CFG_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_IPG_CFG_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_FH_IPG_CFG_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_IPG_CFG_DMA_EOP_IPG_BMSK                              0xff000000
#define HWIO_ECPRI_XBAR_XBAR_FH_IPG_CFG_DMA_EOP_IPG_SHFT                                      24
#define HWIO_ECPRI_XBAR_XBAR_FH_IPG_CFG_OC_EOP_IPG_BMSK                                 0xff0000
#define HWIO_ECPRI_XBAR_XBAR_FH_IPG_CFG_OC_EOP_IPG_SHFT                                       16
#define HWIO_ECPRI_XBAR_XBAR_FH_IPG_CFG_DMA_SOP_IPG_BMSK                                  0xff00
#define HWIO_ECPRI_XBAR_XBAR_FH_IPG_CFG_DMA_SOP_IPG_SHFT                                       8
#define HWIO_ECPRI_XBAR_XBAR_FH_IPG_CFG_OC_SOP_IPG_BMSK                                     0xff
#define HWIO_ECPRI_XBAR_XBAR_FH_IPG_CFG_OC_SOP_IPG_SHFT                                        0

#define HWIO_ECPRI_XBAR_XBAR_C2C_CFG_ADDR(x)                                          ((x) + 0xc)
#define HWIO_ECPRI_XBAR_XBAR_C2C_CFG_OFFS                                             (0xc)
#define HWIO_ECPRI_XBAR_XBAR_C2C_CFG_RMSK                                                   0xff
#define HWIO_ECPRI_XBAR_XBAR_C2C_CFG_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_C2C_CFG_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_CFG_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_CFG_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_C2C_CFG_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_CFG_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_C2C_CFG_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_CFG_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_C2C_CFG_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_CFG_DMA_DST_PORT_BMSK                                      0xc0
#define HWIO_ECPRI_XBAR_XBAR_C2C_CFG_DMA_DST_PORT_SHFT                                         6
#define HWIO_ECPRI_XBAR_XBAR_C2C_CFG_DMA_PRIO_BMSK                                          0x30
#define HWIO_ECPRI_XBAR_XBAR_C2C_CFG_DMA_PRIO_SHFT                                             4
#define HWIO_ECPRI_XBAR_XBAR_C2C_CFG_ORAN_PRIO_BMSK                                          0xc
#define HWIO_ECPRI_XBAR_XBAR_C2C_CFG_ORAN_PRIO_SHFT                                            2
#define HWIO_ECPRI_XBAR_XBAR_C2C_CFG_FH_PRIO_BMSK                                            0x3
#define HWIO_ECPRI_XBAR_XBAR_C2C_CFG_FH_PRIO_SHFT                                              0

#define HWIO_ECPRI_XBAR_XBAR_FH_CFG_ADDR(x)                                           ((x) + 0x10)
#define HWIO_ECPRI_XBAR_XBAR_FH_CFG_OFFS                                              (0x10)
#define HWIO_ECPRI_XBAR_XBAR_FH_CFG_RMSK                                                    0xff
#define HWIO_ECPRI_XBAR_XBAR_FH_CFG_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_FH_CFG_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_CFG_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_CFG_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_FH_CFG_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_CFG_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_FH_CFG_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_CFG_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_FH_CFG_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_CFG_DMA_PRIO_BMSK                                           0xc0
#define HWIO_ECPRI_XBAR_XBAR_FH_CFG_DMA_PRIO_SHFT                                              6
#define HWIO_ECPRI_XBAR_XBAR_FH_CFG_UC_PRIO_BMSK                                            0x30
#define HWIO_ECPRI_XBAR_XBAR_FH_CFG_UC_PRIO_SHFT                                               4
#define HWIO_ECPRI_XBAR_XBAR_FH_CFG_ORAN_PRIO_BMSK                                           0xc
#define HWIO_ECPRI_XBAR_XBAR_FH_CFG_ORAN_PRIO_SHFT                                             2
#define HWIO_ECPRI_XBAR_XBAR_FH_CFG_C2C_PRIO_BMSK                                            0x3
#define HWIO_ECPRI_XBAR_XBAR_FH_CFG_C2C_PRIO_SHFT                                              0

#define HWIO_ECPRI_XBAR_XBAR_OC_CFG_ADDR(x)                                           ((x) + 0x14)
#define HWIO_ECPRI_XBAR_XBAR_OC_CFG_OFFS                                              (0x14)
#define HWIO_ECPRI_XBAR_XBAR_OC_CFG_RMSK                                                  0x39ff
#define HWIO_ECPRI_XBAR_XBAR_OC_CFG_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_OC_CFG_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_OC_CFG_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_OC_CFG_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_OC_CFG_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_OC_CFG_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_OC_CFG_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_OC_CFG_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_OC_CFG_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_OC_CFG_OCRX_ASYNC_THRESHOLD_BMSK                             0x3800
#define HWIO_ECPRI_XBAR_XBAR_OC_CFG_OCRX_ASYNC_THRESHOLD_SHFT                                 11
#define HWIO_ECPRI_XBAR_XBAR_OC_CFG_OCRX_OUTPUT_THRESHOLD_BMSK                             0x1f8
#define HWIO_ECPRI_XBAR_XBAR_OC_CFG_OCRX_OUTPUT_THRESHOLD_SHFT                                 3
#define HWIO_ECPRI_XBAR_XBAR_OC_CFG_OCTX_DYNAMIC_PRIO_EN_BMSK                                0x4
#define HWIO_ECPRI_XBAR_XBAR_OC_CFG_OCTX_DYNAMIC_PRIO_EN_SHFT                                  2
#define HWIO_ECPRI_XBAR_XBAR_OC_CFG_OCTX_LEN_CHK_DROP_BMSK                                   0x2
#define HWIO_ECPRI_XBAR_XBAR_OC_CFG_OCTX_LEN_CHK_DROP_SHFT                                     1
#define HWIO_ECPRI_XBAR_XBAR_OC_CFG_OCTX_LEN_CHK_ENABLE_BMSK                                 0x1
#define HWIO_ECPRI_XBAR_XBAR_OC_CFG_OCTX_LEN_CHK_ENABLE_SHFT                                   0

#define HWIO_ECPRI_XBAR_XBAR_OC_LOOPBACK_CFG_ADDR(x)                                  ((x) + 0x18)
#define HWIO_ECPRI_XBAR_XBAR_OC_LOOPBACK_CFG_OFFS                                     (0x18)
#define HWIO_ECPRI_XBAR_XBAR_OC_LOOPBACK_CFG_RMSK                                           0xff
#define HWIO_ECPRI_XBAR_XBAR_OC_LOOPBACK_CFG_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_OC_LOOPBACK_CFG_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_OC_LOOPBACK_CFG_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_OC_LOOPBACK_CFG_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_OC_LOOPBACK_CFG_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_OC_LOOPBACK_CFG_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_OC_LOOPBACK_CFG_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_OC_LOOPBACK_CFG_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_OC_LOOPBACK_CFG_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_OC_LOOPBACK_CFG_OCTX_3_SRC_BMSK                                0xc0
#define HWIO_ECPRI_XBAR_XBAR_OC_LOOPBACK_CFG_OCTX_3_SRC_SHFT                                   6
#define HWIO_ECPRI_XBAR_XBAR_OC_LOOPBACK_CFG_OCTX_2_SRC_BMSK                                0x30
#define HWIO_ECPRI_XBAR_XBAR_OC_LOOPBACK_CFG_OCTX_2_SRC_SHFT                                   4
#define HWIO_ECPRI_XBAR_XBAR_OC_LOOPBACK_CFG_OCTX_1_SRC_BMSK                                 0xc
#define HWIO_ECPRI_XBAR_XBAR_OC_LOOPBACK_CFG_OCTX_1_SRC_SHFT                                   2
#define HWIO_ECPRI_XBAR_XBAR_OC_LOOPBACK_CFG_OCTX_0_SRC_BMSK                                 0x3
#define HWIO_ECPRI_XBAR_XBAR_OC_LOOPBACK_CFG_OCTX_0_SRC_SHFT                                   0

#define HWIO_ECPRI_XBAR_XBAR_FLUSH_ADDR(x)                                            ((x) + 0x1c)
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_OFFS                                               (0x1c)
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_RMSK                                                 0xff1fbf
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_FLUSH_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FLUSH_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FLUSH_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FLUSH_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_FLUSH_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_3_RX_BMSK                                   0x800000
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_3_RX_SHFT                                         23
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_3_TX_BMSK                                   0x400000
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_3_TX_SHFT                                         22
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_2_RX_BMSK                                   0x200000
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_2_RX_SHFT                                         21
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_2_TX_BMSK                                   0x100000
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_2_TX_SHFT                                         20
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_1_RX_BMSK                                    0x80000
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_1_RX_SHFT                                         19
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_1_TX_BMSK                                    0x40000
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_1_TX_SHFT                                         18
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_0_RX_BMSK                                    0x20000
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_0_RX_SHFT                                         17
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_0_TX_BMSK                                    0x10000
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_0_TX_SHFT                                         16
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_2_RX_BMSK                                    0x1000
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_2_RX_SHFT                                        12
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_2_TX_BMSK                                     0x800
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_2_TX_SHFT                                        11
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_1_RX_BMSK                                     0x400
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_1_RX_SHFT                                        10
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_1_TX_BMSK                                     0x200
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_1_TX_SHFT                                         9
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_0_RX_BMSK                                     0x100
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_0_RX_SHFT                                         8
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_0_TX_BMSK                                      0x80
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_0_TX_SHFT                                         7
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_2_RX_BMSK                                       0x20
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_2_RX_SHFT                                          5
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_2_TX_BMSK                                       0x10
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_2_TX_SHFT                                          4
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_1_RX_BMSK                                        0x8
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_1_RX_SHFT                                          3
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_1_TX_BMSK                                        0x4
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_1_TX_SHFT                                          2
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_0_RX_BMSK                                        0x2
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_0_RX_SHFT                                          1
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_0_TX_BMSK                                        0x1
#define HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_0_TX_SHFT                                          0

#define HWIO_ECPRI_XBAR_XBAR_FH_STATUS_ADDR(x)                                        ((x) + 0x20)
#define HWIO_ECPRI_XBAR_XBAR_FH_STATUS_OFFS                                           (0x20)
#define HWIO_ECPRI_XBAR_XBAR_FH_STATUS_RMSK                                                  0x7
#define HWIO_ECPRI_XBAR_XBAR_FH_STATUS_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_FH_STATUS_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_STATUS_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_STATUS_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_FH_STATUS_TX_C2C_OVERFLOW_BMSK                                  0x7
#define HWIO_ECPRI_XBAR_XBAR_FH_STATUS_TX_C2C_OVERFLOW_SHFT                                    0

#define HWIO_ECPRI_XBAR_XBAR_C2C_STATUS_ADDR(x)                                       ((x) + 0x24)
#define HWIO_ECPRI_XBAR_XBAR_C2C_STATUS_OFFS                                          (0x24)
#define HWIO_ECPRI_XBAR_XBAR_C2C_STATUS_RMSK                                                 0x7
#define HWIO_ECPRI_XBAR_XBAR_C2C_STATUS_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_C2C_STATUS_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_STATUS_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_STATUS_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_C2C_STATUS_TX_FH_OVERFLOW_BMSK                                  0x7
#define HWIO_ECPRI_XBAR_XBAR_C2C_STATUS_TX_FH_OVERFLOW_SHFT                                    0

#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_ADDR(x)                                      ((x) + 0x2c)
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_OFFS                                         (0x2c)
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_RMSK                                            0x3ffff
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_TX_C2C_LEN_ERR_BMSK                             0x38000
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_TX_C2C_LEN_ERR_SHFT                                  15
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_TX_FH_LEN_ERR_BMSK                               0x7000
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_TX_FH_LEN_ERR_SHFT                                   12
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_TX_C2C_OVERFLOW_BMSK                              0xe00
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_TX_C2C_OVERFLOW_SHFT                                  9
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_TX_FH_OVERFLOW_BMSK                               0x1c0
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_TX_FH_OVERFLOW_SHFT                                   6
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_TX_C2C_DROP_BMSK                                   0x38
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_TX_C2C_DROP_SHFT                                      3
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_TX_FH_DROP_BMSK                                     0x7
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_TX_FH_DROP_SHFT                                       0

#define HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_ADDR(x)                                       ((x) + 0x30)
#define HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_OFFS                                          (0x30)
#define HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_RMSK                                               0xfff
#define HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_OCRX_LUT_INIT_DONE_BMSK                            0xe00
#define HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_OCRX_LUT_INIT_DONE_SHFT                                9
#define HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_C2CRX_UL_LUT_INIT_DONE_BMSK                        0x1c0
#define HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_C2CRX_UL_LUT_INIT_DONE_SHFT                            6
#define HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_C2CRX_DL_LUT_INIT_DONE_BMSK                         0x38
#define HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_C2CRX_DL_LUT_INIT_DONE_SHFT                            3
#define HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_FHRX_LUT_INIT_DONE_BMSK                              0x7
#define HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_FHRX_LUT_INIT_DONE_SHFT                                0

#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_ADDR(x)                                    ((x) + 0x40)
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_OFFS                                       (0x40)
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_RMSK                                           0x3ffb
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_C2CRX_UNKNOWN_PCID_BMSK                        0x2000
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_C2CRX_UNKNOWN_PCID_SHFT                            13
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_FHRX_UNKNOWN_PCID_BMSK                         0x1000
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_FHRX_UNKNOWN_PCID_SHFT                             12
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_OCRX_UNKNOWN_PCID_BMSK                          0x800
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_OCRX_UNKNOWN_PCID_SHFT                             11
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_FHRX_UC_PKT_DROP_BMSK                           0x400
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_FHRX_UC_PKT_DROP_SHFT                              10
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_FHRX_UC_PKT_ERR_BMSK                            0x200
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_FHRX_UC_PKT_ERR_SHFT                                9
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_FHRX_UC_OVERFLOW_BMSK                           0x100
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_FHRX_UC_OVERFLOW_SHFT                               8
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_FHRX_UC_PKT_PENDING_BMSK                         0x80
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_FHRX_UC_PKT_PENDING_SHFT                            7
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_OCTX_C2C_OVERFLOW_BMSK                           0x40
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_OCTX_C2C_OVERFLOW_SHFT                              6
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_OCTX_FH_OVERFLOW_BMSK                            0x20
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_OCTX_FH_OVERFLOW_SHFT                               5
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_C2CTX_FH_OVERFLOW_BMSK                           0x10
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_C2CTX_FH_OVERFLOW_SHFT                              4
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_FHTX_C2C_OVERFLOW_BMSK                            0x8
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_FHTX_C2C_OVERFLOW_SHFT                              3
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_OCTX_C2C_LEN_ERR_BMSK                             0x2
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_OCTX_C2C_LEN_ERR_SHFT                               1
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_OCTX_FH_LEN_ERR_BMSK                              0x1
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_STATUS_OCTX_FH_LEN_ERR_SHFT                                0

#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_ADDR(x)                                      ((x) + 0x44)
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_OFFS                                         (0x44)
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_RMSK                                             0x3ffb
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_C2CRX_UNKNOWN_PCID_BMSK                          0x2000
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_C2CRX_UNKNOWN_PCID_SHFT                              13
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_FHRX_UNKNOWN_PCID_BMSK                           0x1000
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_FHRX_UNKNOWN_PCID_SHFT                               12
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_OCRX_UNKNOWN_PCID_BMSK                            0x800
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_OCRX_UNKNOWN_PCID_SHFT                               11
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_FHRX_UC_PKT_DROP_BMSK                             0x400
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_FHRX_UC_PKT_DROP_SHFT                                10
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_FHRX_UC_PKT_ERR_BMSK                              0x200
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_FHRX_UC_PKT_ERR_SHFT                                  9
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_FHRX_UC_OVERFLOW_BMSK                             0x100
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_FHRX_UC_OVERFLOW_SHFT                                 8
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_FHRX_UC_PKT_PENDING_BMSK                           0x80
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_FHRX_UC_PKT_PENDING_SHFT                              7
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_OCTX_C2C_OVERFLOW_BMSK                             0x40
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_OCTX_C2C_OVERFLOW_SHFT                                6
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_OCTX_FH_OVERFLOW_BMSK                              0x20
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_OCTX_FH_OVERFLOW_SHFT                                 5
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_C2CTX_FH_OVERFLOW_BMSK                             0x10
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_C2CTX_FH_OVERFLOW_SHFT                                4
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_FHTX_C2C_OVERFLOW_BMSK                              0x8
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_FHTX_C2C_OVERFLOW_SHFT                                3
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_OCTX_C2C_LEN_ERR_BMSK                               0x2
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_OCTX_C2C_LEN_ERR_SHFT                                 1
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_OCTX_FH_LEN_ERR_BMSK                                0x1
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_MASK_OCTX_FH_LEN_ERR_SHFT                                  0

#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_ADDR(x)                                       ((x) + 0x48)
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_OFFS                                          (0x48)
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_RMSK                                              0x3ffb
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_C2CRX_UNKNOWN_PCID_BMSK                           0x2000
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_C2CRX_UNKNOWN_PCID_SHFT                               13
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_FHRX_UNKNOWN_PCID_BMSK                            0x1000
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_FHRX_UNKNOWN_PCID_SHFT                                12
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_OCRX_UNKNOWN_PCID_BMSK                             0x800
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_OCRX_UNKNOWN_PCID_SHFT                                11
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_FHRX_UC_PKT_DROP_BMSK                              0x400
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_FHRX_UC_PKT_DROP_SHFT                                 10
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_FHRX_UC_PKT_ERR_BMSK                               0x200
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_FHRX_UC_PKT_ERR_SHFT                                   9
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_FHRX_UC_OVERFLOW_BMSK                              0x100
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_FHRX_UC_OVERFLOW_SHFT                                  8
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_FHRX_UC_PKT_PENDING_BMSK                            0x80
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_FHRX_UC_PKT_PENDING_SHFT                               7
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_OCTX_C2C_OVERFLOW_BMSK                              0x40
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_OCTX_C2C_OVERFLOW_SHFT                                 6
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_OCTX_FH_OVERFLOW_BMSK                               0x20
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_OCTX_FH_OVERFLOW_SHFT                                  5
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_C2CTX_FH_OVERFLOW_BMSK                              0x10
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_C2CTX_FH_OVERFLOW_SHFT                                 4
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_FHTX_C2C_OVERFLOW_BMSK                               0x8
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_FHTX_C2C_OVERFLOW_SHFT                                 3
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_OCTX_C2C_LEN_ERR_BMSK                                0x2
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_OCTX_C2C_LEN_ERR_SHFT                                  1
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_OCTX_FH_LEN_ERR_BMSK                                 0x1
#define HWIO_ECPRI_XBAR_XBAR_FW_IRQ_CLR_OCTX_FH_LEN_ERR_SHFT                                   0

#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_ADDR(x)                                    ((x) + 0x50)
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_OFFS                                       (0x50)
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_RMSK                                           0x3ffb
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_C2CRX_UNKNOWN_PCID_BMSK                        0x2000
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_C2CRX_UNKNOWN_PCID_SHFT                            13
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_FHRX_UNKNOWN_PCID_BMSK                         0x1000
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_FHRX_UNKNOWN_PCID_SHFT                             12
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_OCRX_UNKNOWN_PCID_BMSK                          0x800
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_OCRX_UNKNOWN_PCID_SHFT                             11
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_FHRX_UC_PKT_DROP_BMSK                           0x400
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_FHRX_UC_PKT_DROP_SHFT                              10
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_FHRX_UC_PKT_ERR_BMSK                            0x200
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_FHRX_UC_PKT_ERR_SHFT                                9
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_FHRX_UC_OVERFLOW_BMSK                           0x100
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_FHRX_UC_OVERFLOW_SHFT                               8
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_FHRX_UC_PKT_PENDING_BMSK                         0x80
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_FHRX_UC_PKT_PENDING_SHFT                            7
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_OCTX_C2C_OVERFLOW_BMSK                           0x40
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_OCTX_C2C_OVERFLOW_SHFT                              6
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_OCTX_FH_OVERFLOW_BMSK                            0x20
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_OCTX_FH_OVERFLOW_SHFT                               5
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_C2CTX_FH_OVERFLOW_BMSK                           0x10
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_C2CTX_FH_OVERFLOW_SHFT                              4
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_FHTX_C2C_OVERFLOW_BMSK                            0x8
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_FHTX_C2C_OVERFLOW_SHFT                              3
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_OCTX_C2C_LEN_ERR_BMSK                             0x2
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_OCTX_C2C_LEN_ERR_SHFT                               1
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_OCTX_FH_LEN_ERR_BMSK                              0x1
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_STATUS_OCTX_FH_LEN_ERR_SHFT                                0

#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_ADDR(x)                                      ((x) + 0x54)
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_OFFS                                         (0x54)
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_RMSK                                             0x3ffb
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_C2CRX_UNKNOWN_PCID_BMSK                          0x2000
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_C2CRX_UNKNOWN_PCID_SHFT                              13
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_FHRX_UNKNOWN_PCID_BMSK                           0x1000
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_FHRX_UNKNOWN_PCID_SHFT                               12
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_OCRX_UNKNOWN_PCID_BMSK                            0x800
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_OCRX_UNKNOWN_PCID_SHFT                               11
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_FHRX_UC_PKT_DROP_BMSK                             0x400
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_FHRX_UC_PKT_DROP_SHFT                                10
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_FHRX_UC_PKT_ERR_BMSK                              0x200
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_FHRX_UC_PKT_ERR_SHFT                                  9
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_FHRX_UC_OVERFLOW_BMSK                             0x100
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_FHRX_UC_OVERFLOW_SHFT                                 8
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_FHRX_UC_PKT_PENDING_BMSK                           0x80
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_FHRX_UC_PKT_PENDING_SHFT                              7
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_OCTX_C2C_OVERFLOW_BMSK                             0x40
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_OCTX_C2C_OVERFLOW_SHFT                                6
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_OCTX_FH_OVERFLOW_BMSK                              0x20
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_OCTX_FH_OVERFLOW_SHFT                                 5
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_C2CTX_FH_OVERFLOW_BMSK                             0x10
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_C2CTX_FH_OVERFLOW_SHFT                                4
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_FHTX_C2C_OVERFLOW_BMSK                              0x8
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_FHTX_C2C_OVERFLOW_SHFT                                3
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_OCTX_C2C_LEN_ERR_BMSK                               0x2
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_OCTX_C2C_LEN_ERR_SHFT                                 1
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_OCTX_FH_LEN_ERR_BMSK                                0x1
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_MASK_OCTX_FH_LEN_ERR_SHFT                                  0

#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_ADDR(x)                                       ((x) + 0x58)
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_OFFS                                          (0x58)
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_RMSK                                              0x3ffb
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_C2CRX_UNKNOWN_PCID_BMSK                           0x2000
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_C2CRX_UNKNOWN_PCID_SHFT                               13
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_FHRX_UNKNOWN_PCID_BMSK                            0x1000
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_FHRX_UNKNOWN_PCID_SHFT                                12
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_OCRX_UNKNOWN_PCID_BMSK                             0x800
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_OCRX_UNKNOWN_PCID_SHFT                                11
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_FHRX_UC_PKT_DROP_BMSK                              0x400
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_FHRX_UC_PKT_DROP_SHFT                                 10
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_FHRX_UC_PKT_ERR_BMSK                               0x200
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_FHRX_UC_PKT_ERR_SHFT                                   9
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_FHRX_UC_OVERFLOW_BMSK                              0x100
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_FHRX_UC_OVERFLOW_SHFT                                  8
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_FHRX_UC_PKT_PENDING_BMSK                            0x80
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_FHRX_UC_PKT_PENDING_SHFT                               7
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_OCTX_C2C_OVERFLOW_BMSK                              0x40
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_OCTX_C2C_OVERFLOW_SHFT                                 6
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_OCTX_FH_OVERFLOW_BMSK                               0x20
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_OCTX_FH_OVERFLOW_SHFT                                  5
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_C2CTX_FH_OVERFLOW_BMSK                              0x10
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_C2CTX_FH_OVERFLOW_SHFT                                 4
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_FHTX_C2C_OVERFLOW_BMSK                               0x8
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_FHTX_C2C_OVERFLOW_SHFT                                 3
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_OCTX_C2C_LEN_ERR_BMSK                                0x2
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_OCTX_C2C_LEN_ERR_SHFT                                  1
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_OCTX_FH_LEN_ERR_BMSK                                 0x1
#define HWIO_ECPRI_XBAR_XBAR_SW_IRQ_CLR_OCTX_FH_LEN_ERR_SHFT                                   0

#define HWIO_ECPRI_XBAR_XBAR_IDLE_1_ADDR(x)                                           ((x) + 0x70)
#define HWIO_ECPRI_XBAR_XBAR_IDLE_1_OFFS                                              (0x70)
#define HWIO_ECPRI_XBAR_XBAR_IDLE_1_RMSK                                                     0xf
#define HWIO_ECPRI_XBAR_XBAR_IDLE_1_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_IDLE_1_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_IDLE_1_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_IDLE_1_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_IDLE_1_ORAN_IS_IDLE_BMSK                                        0x8
#define HWIO_ECPRI_XBAR_XBAR_IDLE_1_ORAN_IS_IDLE_SHFT                                          3
#define HWIO_ECPRI_XBAR_XBAR_IDLE_1_C2C_IS_IDLE_BMSK                                         0x4
#define HWIO_ECPRI_XBAR_XBAR_IDLE_1_C2C_IS_IDLE_SHFT                                           2
#define HWIO_ECPRI_XBAR_XBAR_IDLE_1_FH_IS_IDLE_BMSK                                          0x2
#define HWIO_ECPRI_XBAR_XBAR_IDLE_1_FH_IS_IDLE_SHFT                                            1
#define HWIO_ECPRI_XBAR_XBAR_IDLE_1_XBAR_IS_IDLE_BMSK                                        0x1
#define HWIO_ECPRI_XBAR_XBAR_IDLE_1_XBAR_IS_IDLE_SHFT                                          0

#define HWIO_ECPRI_XBAR_XBAR_IDLE_2_ADDR(x)                                           ((x) + 0x74)
#define HWIO_ECPRI_XBAR_XBAR_IDLE_2_OFFS                                              (0x74)
#define HWIO_ECPRI_XBAR_XBAR_IDLE_2_RMSK                                              0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_IDLE_2_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_IDLE_2_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_IDLE_2_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_IDLE_2_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_IDLE_2_C2CTX_IS_IDLE_BMSK                                0xe0000000
#define HWIO_ECPRI_XBAR_XBAR_IDLE_2_C2CTX_IS_IDLE_SHFT                                        29
#define HWIO_ECPRI_XBAR_XBAR_IDLE_2_C2CRX_IS_IDLE_BMSK                                0x1c000000
#define HWIO_ECPRI_XBAR_XBAR_IDLE_2_C2CRX_IS_IDLE_SHFT                                        26
#define HWIO_ECPRI_XBAR_XBAR_IDLE_2_FHTX_IS_IDLE_BMSK                                  0x3800000
#define HWIO_ECPRI_XBAR_XBAR_IDLE_2_FHTX_IS_IDLE_SHFT                                         23
#define HWIO_ECPRI_XBAR_XBAR_IDLE_2_FHRX_IS_IDLE_BMSK                                   0x700000
#define HWIO_ECPRI_XBAR_XBAR_IDLE_2_FHRX_IS_IDLE_SHFT                                         20
#define HWIO_ECPRI_XBAR_XBAR_IDLE_2_OCTX_C2C_IS_IDLE_BMSK                                0xe0000
#define HWIO_ECPRI_XBAR_XBAR_IDLE_2_OCTX_C2C_IS_IDLE_SHFT                                     17
#define HWIO_ECPRI_XBAR_XBAR_IDLE_2_OCTX_FH_IS_IDLE_BMSK                                 0x1c000
#define HWIO_ECPRI_XBAR_XBAR_IDLE_2_OCTX_FH_IS_IDLE_SHFT                                      14
#define HWIO_ECPRI_XBAR_XBAR_IDLE_2_OCTX_ORAN_IS_IDLE_BMSK                                0x3c00
#define HWIO_ECPRI_XBAR_XBAR_IDLE_2_OCTX_ORAN_IS_IDLE_SHFT                                    10
#define HWIO_ECPRI_XBAR_XBAR_IDLE_2_OCRX_C2C_IS_IDLE_BMSK                                  0x380
#define HWIO_ECPRI_XBAR_XBAR_IDLE_2_OCRX_C2C_IS_IDLE_SHFT                                      7
#define HWIO_ECPRI_XBAR_XBAR_IDLE_2_OCRX_FH_IS_IDLE_BMSK                                    0x70
#define HWIO_ECPRI_XBAR_XBAR_IDLE_2_OCRX_FH_IS_IDLE_SHFT                                       4
#define HWIO_ECPRI_XBAR_XBAR_IDLE_2_OCRX_ORAN_IS_IDLE_BMSK                                   0xf
#define HWIO_ECPRI_XBAR_XBAR_IDLE_2_OCRX_ORAN_IS_IDLE_SHFT                                     0

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_ADDR(x)                                    ((x) + 0x100)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_OFFS                                       (0x100)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_RMSK                                          0x1ff0f
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_VALID_BMSK                      0x10000
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_VALID_SHFT                           16
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_BMSK                      0xff00
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_SHFT                           8
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_FHRX_FVAL               0x0
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_C2CRX_FVAL              0x1
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_OCRX_FVAL               0x2
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_DMA_FVAL                0x3
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_UC_FVAL                 0x4
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_BEFORE_LUT_FVAL             0x10
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_AFTER_LUT_FVAL              0x11
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_ALL_FVAL               0xff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_ID_BMSK                             0xf
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_ID_SHFT                               0
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_ID_FHTX_0_FVAL                      0x0
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_ID_FHTX_1_FVAL                      0x1
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_ID_FHTX_2_FVAL                      0x2
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_ID_FHRX_0_FVAL                      0x3
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_ID_FHRX_1_FVAL                      0x4
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_ID_FHRX_2_FVAL                      0x5
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_ID_DMA_TO_FH_FVAL                   0x6
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_ID_FH0_TO_DMA_FVAL                  0x7
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_ID_FH1_TO_DMA_FVAL                  0x8
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_CFG_CAPTURE_POINT_ID_FH2_TO_DMA_FVAL                  0x9

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_MASK_m_ADDR(base,m)                       ((base) + 0X104 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_MASK_m_OFFS(m)                            (0X104 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_MASK_m_RMSK                               0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_MASK_m_MAXm                                        3
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_MASK_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_MASK_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_MASK_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_MASK_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_MASK_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_MASK_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_MASK_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_MASK_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_MASK_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_MASK_m_MASK_BMSK                          0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_MASK_m_MASK_SHFT                                   0

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_VALUE_m_ADDR(base,m)                      ((base) + 0X114 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_VALUE_m_OFFS(m)                           (0X114 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_VALUE_m_RMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_VALUE_m_MAXm                                       3
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_VALUE_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_VALUE_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_VALUE_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_VALUE_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_VALUE_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_VALUE_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_VALUE_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_VALUE_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_VALUE_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_VALUE_m_VALUE_BMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_VALUE_m_VALUE_SHFT                                 0

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_MASK_m_ADDR(base,m)                      ((base) + 0X124 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_MASK_m_OFFS(m)                           (0X124 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_MASK_m_RMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_MASK_m_MAXm                                       1
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_MASK_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_MASK_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_MASK_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_MASK_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_MASK_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_MASK_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_MASK_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_MASK_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_MASK_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_MASK_m_MASK_BMSK                         0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_MASK_m_MASK_SHFT                                  0

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_VALUE_m_ADDR(base,m)                     ((base) + 0X12C + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_VALUE_m_OFFS(m)                          (0X12C + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_VALUE_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_VALUE_m_MAXm                                      1
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_VALUE_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_VALUE_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_VALUE_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_VALUE_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_VALUE_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_VALUE_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_VALUE_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_VALUE_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_VALUE_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_VALUE_m_VALUE_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_VALUE_m_VALUE_SHFT                                0

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TID_MASK_VALUE_ADDR(x)                         ((x) + 0x134)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TID_MASK_VALUE_OFFS                            (0x134)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TID_MASK_VALUE_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TID_MASK_VALUE_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TID_MASK_VALUE_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TID_MASK_VALUE_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TID_MASK_VALUE_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TID_MASK_VALUE_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TID_MASK_VALUE_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TID_MASK_VALUE_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TID_MASK_VALUE_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TID_MASK_VALUE_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TID_MASK_VALUE_VALUE_BMSK                      0xffff0000
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TID_MASK_VALUE_VALUE_SHFT                              16
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TID_MASK_VALUE_MASK_BMSK                           0xffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_TID_MASK_VALUE_MASK_SHFT                                0

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_MISC_MASK_VALUE_ADDR(x)                        ((x) + 0x138)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_MISC_MASK_VALUE_OFFS                           (0x138)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_MISC_MASK_VALUE_RMSK                              0x3ffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_MISC_MASK_VALUE_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_MISC_MASK_VALUE_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_MISC_MASK_VALUE_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_MISC_MASK_VALUE_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_MISC_MASK_VALUE_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_MISC_MASK_VALUE_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_MISC_MASK_VALUE_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_MISC_MASK_VALUE_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_MISC_MASK_VALUE_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_MISC_MASK_VALUE_TERROR_VALUE_BMSK                 0x20000
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_MISC_MASK_VALUE_TERROR_VALUE_SHFT                      17
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_MISC_MASK_VALUE_TERROR_MASK_BMSK                  0x10000
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_MISC_MASK_VALUE_TERROR_MASK_SHFT                       16
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_MISC_MASK_VALUE_TDEST_VALUE_BMSK                   0xff00
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_MISC_MASK_VALUE_TDEST_VALUE_SHFT                        8
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_MISC_MASK_VALUE_TDEST_MASK_BMSK                      0xff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_0_MISC_MASK_VALUE_TDEST_MASK_SHFT                         0

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_ADDR(x)                                    ((x) + 0x140)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_OFFS                                       (0x140)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_RMSK                                          0x1ff0f
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_VALID_BMSK                      0x10000
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_VALID_SHFT                           16
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_BMSK                      0xff00
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_SHFT                           8
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_FHRX_FVAL               0x0
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_C2CRX_FVAL              0x1
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_OCRX_FVAL               0x2
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_DMA_FVAL                0x3
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_UC_FVAL                 0x4
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_BEFORE_LUT_FVAL             0x10
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_AFTER_LUT_FVAL              0x11
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_ALL_FVAL               0xff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_ID_BMSK                             0xf
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_ID_SHFT                               0
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_ID_FHTX_0_FVAL                      0x0
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_ID_FHTX_1_FVAL                      0x1
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_ID_FHTX_2_FVAL                      0x2
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_ID_FHRX_0_FVAL                      0x3
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_ID_FHRX_1_FVAL                      0x4
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_ID_FHRX_2_FVAL                      0x5
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_ID_DMA_TO_FH_FVAL                   0x6
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_ID_FH0_TO_DMA_FVAL                  0x7
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_ID_FH1_TO_DMA_FVAL                  0x8
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_CFG_CAPTURE_POINT_ID_FH2_TO_DMA_FVAL                  0x9

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_MASK_m_ADDR(base,m)                       ((base) + 0X144 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_MASK_m_OFFS(m)                            (0X144 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_MASK_m_RMSK                               0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_MASK_m_MAXm                                        3
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_MASK_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_MASK_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_MASK_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_MASK_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_MASK_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_MASK_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_MASK_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_MASK_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_MASK_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_MASK_m_MASK_BMSK                          0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_MASK_m_MASK_SHFT                                   0

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_VALUE_m_ADDR(base,m)                      ((base) + 0X154 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_VALUE_m_OFFS(m)                           (0X154 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_VALUE_m_RMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_VALUE_m_MAXm                                       3
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_VALUE_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_VALUE_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_VALUE_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_VALUE_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_VALUE_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_VALUE_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_VALUE_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_VALUE_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_VALUE_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_VALUE_m_VALUE_BMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_VALUE_m_VALUE_SHFT                                 0

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_MASK_m_ADDR(base,m)                      ((base) + 0X164 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_MASK_m_OFFS(m)                           (0X164 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_MASK_m_RMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_MASK_m_MAXm                                       1
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_MASK_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_MASK_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_MASK_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_MASK_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_MASK_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_MASK_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_MASK_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_MASK_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_MASK_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_MASK_m_MASK_BMSK                         0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_MASK_m_MASK_SHFT                                  0

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_VALUE_m_ADDR(base,m)                     ((base) + 0X16C + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_VALUE_m_OFFS(m)                          (0X16C + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_VALUE_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_VALUE_m_MAXm                                      1
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_VALUE_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_VALUE_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_VALUE_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_VALUE_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_VALUE_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_VALUE_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_VALUE_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_VALUE_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_VALUE_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_VALUE_m_VALUE_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_VALUE_m_VALUE_SHFT                                0

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TID_MASK_VALUE_ADDR(x)                         ((x) + 0x174)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TID_MASK_VALUE_OFFS                            (0x174)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TID_MASK_VALUE_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TID_MASK_VALUE_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TID_MASK_VALUE_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TID_MASK_VALUE_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TID_MASK_VALUE_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TID_MASK_VALUE_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TID_MASK_VALUE_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TID_MASK_VALUE_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TID_MASK_VALUE_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TID_MASK_VALUE_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TID_MASK_VALUE_VALUE_BMSK                      0xffff0000
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TID_MASK_VALUE_VALUE_SHFT                              16
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TID_MASK_VALUE_MASK_BMSK                           0xffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_TID_MASK_VALUE_MASK_SHFT                                0

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_MISC_MASK_VALUE_ADDR(x)                        ((x) + 0x178)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_MISC_MASK_VALUE_OFFS                           (0x178)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_MISC_MASK_VALUE_RMSK                              0x3ffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_MISC_MASK_VALUE_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_MISC_MASK_VALUE_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_MISC_MASK_VALUE_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_MISC_MASK_VALUE_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_MISC_MASK_VALUE_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_MISC_MASK_VALUE_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_MISC_MASK_VALUE_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_MISC_MASK_VALUE_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_MISC_MASK_VALUE_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_MISC_MASK_VALUE_TERROR_VALUE_BMSK                 0x20000
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_MISC_MASK_VALUE_TERROR_VALUE_SHFT                      17
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_MISC_MASK_VALUE_TERROR_MASK_BMSK                  0x10000
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_MISC_MASK_VALUE_TERROR_MASK_SHFT                       16
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_MISC_MASK_VALUE_TDEST_VALUE_BMSK                   0xff00
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_MISC_MASK_VALUE_TDEST_VALUE_SHFT                        8
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_MISC_MASK_VALUE_TDEST_MASK_BMSK                      0xff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_1_MISC_MASK_VALUE_TDEST_MASK_SHFT                         0

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_ADDR(x)                                    ((x) + 0x180)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_OFFS                                       (0x180)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_RMSK                                          0x1ff0f
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_VALID_BMSK                      0x10000
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_VALID_SHFT                           16
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_BMSK                      0xff00
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_SHFT                           8
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_FHRX_FVAL               0x0
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_C2CRX_FVAL              0x1
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_OCRX_FVAL               0x2
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_DMA_FVAL                0x3
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_UC_FVAL                 0x4
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_BEFORE_LUT_FVAL             0x10
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_AFTER_LUT_FVAL              0x11
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_ALL_FVAL               0xff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_ID_BMSK                             0xf
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_ID_SHFT                               0
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_ID_FHTX_0_FVAL                      0x0
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_ID_FHTX_1_FVAL                      0x1
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_ID_FHTX_2_FVAL                      0x2
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_ID_FHRX_0_FVAL                      0x3
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_ID_FHRX_1_FVAL                      0x4
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_ID_FHRX_2_FVAL                      0x5
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_ID_DMA_TO_FH_FVAL                   0x6
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_ID_FH0_TO_DMA_FVAL                  0x7
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_ID_FH1_TO_DMA_FVAL                  0x8
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_CFG_CAPTURE_POINT_ID_FH2_TO_DMA_FVAL                  0x9

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_MASK_m_ADDR(base,m)                       ((base) + 0X184 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_MASK_m_OFFS(m)                            (0X184 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_MASK_m_RMSK                               0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_MASK_m_MAXm                                        3
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_MASK_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_MASK_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_MASK_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_MASK_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_MASK_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_MASK_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_MASK_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_MASK_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_MASK_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_MASK_m_MASK_BMSK                          0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_MASK_m_MASK_SHFT                                   0

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_VALUE_m_ADDR(base,m)                      ((base) + 0X194 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_VALUE_m_OFFS(m)                           (0X194 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_VALUE_m_RMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_VALUE_m_MAXm                                       3
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_VALUE_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_VALUE_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_VALUE_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_VALUE_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_VALUE_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_VALUE_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_VALUE_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_VALUE_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_VALUE_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_VALUE_m_VALUE_BMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_VALUE_m_VALUE_SHFT                                 0

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_MASK_m_ADDR(base,m)                      ((base) + 0X1A4 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_MASK_m_OFFS(m)                           (0X1A4 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_MASK_m_RMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_MASK_m_MAXm                                       1
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_MASK_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_MASK_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_MASK_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_MASK_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_MASK_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_MASK_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_MASK_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_MASK_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_MASK_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_MASK_m_MASK_BMSK                         0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_MASK_m_MASK_SHFT                                  0

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_VALUE_m_ADDR(base,m)                     ((base) + 0X1AC + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_VALUE_m_OFFS(m)                          (0X1AC + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_VALUE_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_VALUE_m_MAXm                                      1
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_VALUE_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_VALUE_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_VALUE_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_VALUE_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_VALUE_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_VALUE_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_VALUE_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_VALUE_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_VALUE_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_VALUE_m_VALUE_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_VALUE_m_VALUE_SHFT                                0

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TID_MASK_VALUE_ADDR(x)                         ((x) + 0x1b4)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TID_MASK_VALUE_OFFS                            (0x1b4)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TID_MASK_VALUE_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TID_MASK_VALUE_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TID_MASK_VALUE_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TID_MASK_VALUE_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TID_MASK_VALUE_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TID_MASK_VALUE_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TID_MASK_VALUE_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TID_MASK_VALUE_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TID_MASK_VALUE_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TID_MASK_VALUE_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TID_MASK_VALUE_VALUE_BMSK                      0xffff0000
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TID_MASK_VALUE_VALUE_SHFT                              16
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TID_MASK_VALUE_MASK_BMSK                           0xffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_TID_MASK_VALUE_MASK_SHFT                                0

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_MISC_MASK_VALUE_ADDR(x)                        ((x) + 0x1b8)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_MISC_MASK_VALUE_OFFS                           (0x1b8)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_MISC_MASK_VALUE_RMSK                              0x3ffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_MISC_MASK_VALUE_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_MISC_MASK_VALUE_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_MISC_MASK_VALUE_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_MISC_MASK_VALUE_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_MISC_MASK_VALUE_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_MISC_MASK_VALUE_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_MISC_MASK_VALUE_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_MISC_MASK_VALUE_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_MISC_MASK_VALUE_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_MISC_MASK_VALUE_TERROR_VALUE_BMSK                 0x20000
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_MISC_MASK_VALUE_TERROR_VALUE_SHFT                      17
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_MISC_MASK_VALUE_TERROR_MASK_BMSK                  0x10000
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_MISC_MASK_VALUE_TERROR_MASK_SHFT                       16
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_MISC_MASK_VALUE_TDEST_VALUE_BMSK                   0xff00
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_MISC_MASK_VALUE_TDEST_VALUE_SHFT                        8
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_MISC_MASK_VALUE_TDEST_MASK_BMSK                      0xff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_2_MISC_MASK_VALUE_TDEST_MASK_SHFT                         0

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_ADDR(x)                                    ((x) + 0x1c0)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_OFFS                                       (0x1c0)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_RMSK                                          0x1ff0f
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_VALID_BMSK                      0x10000
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_VALID_SHFT                           16
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_BMSK                      0xff00
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_SHFT                           8
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_FHRX_FVAL               0x0
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_C2CRX_FVAL              0x1
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_OCRX_FVAL               0x2
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_DMA_FVAL                0x3
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_UC_FVAL                 0x4
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_BEFORE_LUT_FVAL             0x10
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_AFTER_LUT_FVAL              0x11
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_ALL_FVAL               0xff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_ID_BMSK                             0xf
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_ID_SHFT                               0
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_ID_FHTX_0_FVAL                      0x0
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_ID_FHTX_1_FVAL                      0x1
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_ID_FHTX_2_FVAL                      0x2
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_ID_FHRX_0_FVAL                      0x3
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_ID_FHRX_1_FVAL                      0x4
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_ID_FHRX_2_FVAL                      0x5
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_ID_DMA_TO_FH_FVAL                   0x6
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_ID_FH0_TO_DMA_FVAL                  0x7
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_ID_FH1_TO_DMA_FVAL                  0x8
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_CFG_CAPTURE_POINT_ID_FH2_TO_DMA_FVAL                  0x9

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_MASK_m_ADDR(base,m)                       ((base) + 0X1C4 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_MASK_m_OFFS(m)                            (0X1C4 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_MASK_m_RMSK                               0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_MASK_m_MAXm                                        3
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_MASK_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_MASK_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_MASK_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_MASK_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_MASK_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_MASK_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_MASK_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_MASK_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_MASK_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_MASK_m_MASK_BMSK                          0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_MASK_m_MASK_SHFT                                   0

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_VALUE_m_ADDR(base,m)                      ((base) + 0X1D4 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_VALUE_m_OFFS(m)                           (0X1D4 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_VALUE_m_RMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_VALUE_m_MAXm                                       3
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_VALUE_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_VALUE_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_VALUE_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_VALUE_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_VALUE_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_VALUE_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_VALUE_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_VALUE_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_VALUE_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_VALUE_m_VALUE_BMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_VALUE_m_VALUE_SHFT                                 0

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_MASK_m_ADDR(base,m)                      ((base) + 0X1E4 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_MASK_m_OFFS(m)                           (0X1E4 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_MASK_m_RMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_MASK_m_MAXm                                       1
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_MASK_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_MASK_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_MASK_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_MASK_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_MASK_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_MASK_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_MASK_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_MASK_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_MASK_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_MASK_m_MASK_BMSK                         0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_MASK_m_MASK_SHFT                                  0

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_VALUE_m_ADDR(base,m)                     ((base) + 0X1EC + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_VALUE_m_OFFS(m)                          (0X1EC + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_VALUE_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_VALUE_m_MAXm                                      1
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_VALUE_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_VALUE_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_VALUE_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_VALUE_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_VALUE_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_VALUE_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_VALUE_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_VALUE_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_VALUE_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_VALUE_m_VALUE_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_VALUE_m_VALUE_SHFT                                0

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TID_MASK_VALUE_ADDR(x)                         ((x) + 0x1f4)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TID_MASK_VALUE_OFFS                            (0x1f4)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TID_MASK_VALUE_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TID_MASK_VALUE_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TID_MASK_VALUE_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TID_MASK_VALUE_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TID_MASK_VALUE_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TID_MASK_VALUE_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TID_MASK_VALUE_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TID_MASK_VALUE_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TID_MASK_VALUE_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TID_MASK_VALUE_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TID_MASK_VALUE_VALUE_BMSK                      0xffff0000
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TID_MASK_VALUE_VALUE_SHFT                              16
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TID_MASK_VALUE_MASK_BMSK                           0xffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_TID_MASK_VALUE_MASK_SHFT                                0

#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_MISC_MASK_VALUE_ADDR(x)                        ((x) + 0x1f8)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_MISC_MASK_VALUE_OFFS                           (0x1f8)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_MISC_MASK_VALUE_RMSK                              0x3ffff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_MISC_MASK_VALUE_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_MISC_MASK_VALUE_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_MISC_MASK_VALUE_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_MISC_MASK_VALUE_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_MISC_MASK_VALUE_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_MISC_MASK_VALUE_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_MISC_MASK_VALUE_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_MISC_MASK_VALUE_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_MISC_MASK_VALUE_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_MISC_MASK_VALUE_TERROR_VALUE_BMSK                 0x20000
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_MISC_MASK_VALUE_TERROR_VALUE_SHFT                      17
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_MISC_MASK_VALUE_TERROR_MASK_BMSK                  0x10000
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_MISC_MASK_VALUE_TERROR_MASK_SHFT                       16
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_MISC_MASK_VALUE_TDEST_VALUE_BMSK                   0xff00
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_MISC_MASK_VALUE_TDEST_VALUE_SHFT                        8
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_MISC_MASK_VALUE_TDEST_MASK_BMSK                      0xff
#define HWIO_ECPRI_XBAR_XBAR_FH_TPDM_3_MISC_MASK_VALUE_TDEST_MASK_SHFT                         0

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_ADDR(x)                                   ((x) + 0x200)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_OFFS                                      (0x200)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_RMSK                                         0x1ff0f
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_VALID_BMSK                     0x10000
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_VALID_SHFT                          16
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_BMSK                     0xff00
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_SHFT                          8
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_FHRX_FVAL              0x0
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_C2CRX_FVAL             0x1
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_OCRX_FVAL              0x2
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_DMA_FVAL               0x3
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_UC_FVAL                0x4
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_BEFORE_LUT_FVAL            0x10
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_AFTER_LUT_FVAL             0x11
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_ALL_FVAL              0xff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_ID_BMSK                            0xf
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_ID_SHFT                              0
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_ID_C2CTX_0_FVAL                    0x0
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_ID_C2CTX_1_FVAL                    0x1
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_ID_C2CTX_2_FVAL                    0x2
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_ID_C2CRX_0_FVAL                    0x3
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_ID_C2CRX_1_FVAL                    0x4
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_ID_C2CRX_2_FVAL                    0x5
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_ID_DMA_TO_C2C_FVAL                 0x6
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_ID_C2C0_TO_DMA_FVAL                0x7
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_ID_C2C1_TO_DMA_FVAL                0x8
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG_CAPTURE_POINT_ID_C2C2_TO_DMA_FVAL                0x9

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_MASK_m_ADDR(base,m)                      ((base) + 0X204 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_MASK_m_OFFS(m)                           (0X204 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_MASK_m_RMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_MASK_m_MAXm                                       3
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_MASK_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_MASK_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_MASK_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_MASK_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_MASK_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_MASK_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_MASK_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_MASK_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_MASK_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_MASK_m_MASK_BMSK                         0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_MASK_m_MASK_SHFT                                  0

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_VALUE_m_ADDR(base,m)                     ((base) + 0X214 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_VALUE_m_OFFS(m)                          (0X214 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_VALUE_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_VALUE_m_MAXm                                      3
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_VALUE_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_VALUE_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_VALUE_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_VALUE_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_VALUE_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_VALUE_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_VALUE_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_VALUE_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_VALUE_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_VALUE_m_VALUE_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_VALUE_m_VALUE_SHFT                                0

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_MASK_m_ADDR(base,m)                     ((base) + 0X224 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_MASK_m_OFFS(m)                          (0X224 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_MASK_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_MASK_m_MAXm                                      1
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_MASK_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_MASK_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_MASK_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_MASK_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_MASK_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_MASK_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_MASK_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_MASK_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_MASK_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_MASK_m_MASK_BMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_MASK_m_MASK_SHFT                                 0

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_VALUE_m_ADDR(base,m)                    ((base) + 0X22C + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_VALUE_m_OFFS(m)                         (0X22C + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_VALUE_m_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_VALUE_m_MAXm                                     1
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_VALUE_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_VALUE_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_VALUE_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_VALUE_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_VALUE_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_VALUE_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_VALUE_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_VALUE_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_VALUE_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_VALUE_m_VALUE_BMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_VALUE_m_VALUE_SHFT                               0

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TID_MASK_VALUE_ADDR(x)                        ((x) + 0x234)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TID_MASK_VALUE_OFFS                           (0x234)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TID_MASK_VALUE_RMSK                           0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TID_MASK_VALUE_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TID_MASK_VALUE_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TID_MASK_VALUE_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TID_MASK_VALUE_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TID_MASK_VALUE_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TID_MASK_VALUE_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TID_MASK_VALUE_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TID_MASK_VALUE_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TID_MASK_VALUE_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TID_MASK_VALUE_VALUE_BMSK                     0xffff0000
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TID_MASK_VALUE_VALUE_SHFT                             16
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TID_MASK_VALUE_MASK_BMSK                          0xffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_TID_MASK_VALUE_MASK_SHFT                               0

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_ADDR(x)                       ((x) + 0x238)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_OFFS                          (0x238)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_RMSK                             0x3ffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_TERROR_VALUE_BMSK                0x20000
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_TERROR_VALUE_SHFT                     17
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_TERROR_MASK_BMSK                 0x10000
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_TERROR_MASK_SHFT                      16
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_TDEST_VALUE_BMSK                  0xff00
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_TDEST_VALUE_SHFT                       8
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_TDEST_MASK_BMSK                     0xff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_0_MISC_MASK_VALUE_TDEST_MASK_SHFT                        0

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_ADDR(x)                                   ((x) + 0x240)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_OFFS                                      (0x240)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_RMSK                                         0x1ff0f
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_VALID_BMSK                     0x10000
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_VALID_SHFT                          16
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_BMSK                     0xff00
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_SHFT                          8
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_FHRX_FVAL              0x0
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_C2CRX_FVAL             0x1
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_OCRX_FVAL              0x2
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_DMA_FVAL               0x3
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_UC_FVAL                0x4
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_BEFORE_LUT_FVAL            0x10
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_AFTER_LUT_FVAL             0x11
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_ALL_FVAL              0xff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_ID_BMSK                            0xf
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_ID_SHFT                              0
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_ID_C2CTX_0_FVAL                    0x0
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_ID_C2CTX_1_FVAL                    0x1
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_ID_C2CTX_2_FVAL                    0x2
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_ID_C2CRX_0_FVAL                    0x3
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_ID_C2CRX_1_FVAL                    0x4
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_ID_C2CRX_2_FVAL                    0x5
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_ID_DMA_TO_C2C_FVAL                 0x6
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_ID_C2C0_TO_DMA_FVAL                0x7
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_ID_C2C1_TO_DMA_FVAL                0x8
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG_CAPTURE_POINT_ID_C2C2_TO_DMA_FVAL                0x9

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_MASK_m_ADDR(base,m)                      ((base) + 0X244 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_MASK_m_OFFS(m)                           (0X244 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_MASK_m_RMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_MASK_m_MAXm                                       3
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_MASK_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_MASK_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_MASK_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_MASK_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_MASK_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_MASK_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_MASK_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_MASK_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_MASK_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_MASK_m_MASK_BMSK                         0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_MASK_m_MASK_SHFT                                  0

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_VALUE_m_ADDR(base,m)                     ((base) + 0X254 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_VALUE_m_OFFS(m)                          (0X254 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_VALUE_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_VALUE_m_MAXm                                      3
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_VALUE_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_VALUE_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_VALUE_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_VALUE_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_VALUE_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_VALUE_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_VALUE_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_VALUE_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_VALUE_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_VALUE_m_VALUE_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_VALUE_m_VALUE_SHFT                                0

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_MASK_m_ADDR(base,m)                     ((base) + 0X264 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_MASK_m_OFFS(m)                          (0X264 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_MASK_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_MASK_m_MAXm                                      1
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_MASK_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_MASK_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_MASK_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_MASK_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_MASK_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_MASK_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_MASK_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_MASK_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_MASK_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_MASK_m_MASK_BMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_MASK_m_MASK_SHFT                                 0

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_VALUE_m_ADDR(base,m)                    ((base) + 0X26C + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_VALUE_m_OFFS(m)                         (0X26C + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_VALUE_m_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_VALUE_m_MAXm                                     1
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_VALUE_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_VALUE_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_VALUE_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_VALUE_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_VALUE_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_VALUE_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_VALUE_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_VALUE_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_VALUE_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_VALUE_m_VALUE_BMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_VALUE_m_VALUE_SHFT                               0

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TID_MASK_VALUE_ADDR(x)                        ((x) + 0x274)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TID_MASK_VALUE_OFFS                           (0x274)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TID_MASK_VALUE_RMSK                           0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TID_MASK_VALUE_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TID_MASK_VALUE_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TID_MASK_VALUE_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TID_MASK_VALUE_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TID_MASK_VALUE_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TID_MASK_VALUE_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TID_MASK_VALUE_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TID_MASK_VALUE_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TID_MASK_VALUE_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TID_MASK_VALUE_VALUE_BMSK                     0xffff0000
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TID_MASK_VALUE_VALUE_SHFT                             16
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TID_MASK_VALUE_MASK_BMSK                          0xffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_TID_MASK_VALUE_MASK_SHFT                               0

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_ADDR(x)                       ((x) + 0x278)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_OFFS                          (0x278)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_RMSK                             0x3ffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_TERROR_VALUE_BMSK                0x20000
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_TERROR_VALUE_SHFT                     17
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_TERROR_MASK_BMSK                 0x10000
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_TERROR_MASK_SHFT                      16
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_TDEST_VALUE_BMSK                  0xff00
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_TDEST_VALUE_SHFT                       8
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_TDEST_MASK_BMSK                     0xff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_1_MISC_MASK_VALUE_TDEST_MASK_SHFT                        0

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_ADDR(x)                                   ((x) + 0x280)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_OFFS                                      (0x280)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_RMSK                                         0x1ff0f
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_VALID_BMSK                     0x10000
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_VALID_SHFT                          16
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_BMSK                     0xff00
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_SHFT                          8
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_FHRX_FVAL              0x0
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_C2CRX_FVAL             0x1
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_OCRX_FVAL              0x2
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_DMA_FVAL               0x3
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_UC_FVAL                0x4
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_BEFORE_LUT_FVAL            0x10
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_AFTER_LUT_FVAL             0x11
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_ALL_FVAL              0xff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_ID_BMSK                            0xf
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_ID_SHFT                              0
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_ID_C2CTX_0_FVAL                    0x0
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_ID_C2CTX_1_FVAL                    0x1
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_ID_C2CTX_2_FVAL                    0x2
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_ID_C2CRX_0_FVAL                    0x3
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_ID_C2CRX_1_FVAL                    0x4
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_ID_C2CRX_2_FVAL                    0x5
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_ID_DMA_TO_C2C_FVAL                 0x6
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_ID_C2C0_TO_DMA_FVAL                0x7
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_ID_C2C1_TO_DMA_FVAL                0x8
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG_CAPTURE_POINT_ID_C2C2_TO_DMA_FVAL                0x9

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_MASK_m_ADDR(base,m)                      ((base) + 0X284 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_MASK_m_OFFS(m)                           (0X284 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_MASK_m_RMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_MASK_m_MAXm                                       3
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_MASK_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_MASK_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_MASK_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_MASK_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_MASK_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_MASK_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_MASK_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_MASK_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_MASK_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_MASK_m_MASK_BMSK                         0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_MASK_m_MASK_SHFT                                  0

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_VALUE_m_ADDR(base,m)                     ((base) + 0X294 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_VALUE_m_OFFS(m)                          (0X294 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_VALUE_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_VALUE_m_MAXm                                      3
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_VALUE_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_VALUE_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_VALUE_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_VALUE_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_VALUE_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_VALUE_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_VALUE_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_VALUE_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_VALUE_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_VALUE_m_VALUE_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_VALUE_m_VALUE_SHFT                                0

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_MASK_m_ADDR(base,m)                     ((base) + 0X2A4 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_MASK_m_OFFS(m)                          (0X2A4 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_MASK_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_MASK_m_MAXm                                      1
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_MASK_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_MASK_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_MASK_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_MASK_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_MASK_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_MASK_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_MASK_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_MASK_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_MASK_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_MASK_m_MASK_BMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_MASK_m_MASK_SHFT                                 0

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_VALUE_m_ADDR(base,m)                    ((base) + 0X2AC + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_VALUE_m_OFFS(m)                         (0X2AC + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_VALUE_m_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_VALUE_m_MAXm                                     1
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_VALUE_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_VALUE_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_VALUE_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_VALUE_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_VALUE_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_VALUE_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_VALUE_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_VALUE_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_VALUE_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_VALUE_m_VALUE_BMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_VALUE_m_VALUE_SHFT                               0

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TID_MASK_VALUE_ADDR(x)                        ((x) + 0x2b4)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TID_MASK_VALUE_OFFS                           (0x2b4)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TID_MASK_VALUE_RMSK                           0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TID_MASK_VALUE_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TID_MASK_VALUE_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TID_MASK_VALUE_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TID_MASK_VALUE_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TID_MASK_VALUE_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TID_MASK_VALUE_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TID_MASK_VALUE_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TID_MASK_VALUE_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TID_MASK_VALUE_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TID_MASK_VALUE_VALUE_BMSK                     0xffff0000
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TID_MASK_VALUE_VALUE_SHFT                             16
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TID_MASK_VALUE_MASK_BMSK                          0xffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_TID_MASK_VALUE_MASK_SHFT                               0

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_ADDR(x)                       ((x) + 0x2b8)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_OFFS                          (0x2b8)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_RMSK                             0x3ffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_TERROR_VALUE_BMSK                0x20000
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_TERROR_VALUE_SHFT                     17
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_TERROR_MASK_BMSK                 0x10000
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_TERROR_MASK_SHFT                      16
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_TDEST_VALUE_BMSK                  0xff00
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_TDEST_VALUE_SHFT                       8
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_TDEST_MASK_BMSK                     0xff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_2_MISC_MASK_VALUE_TDEST_MASK_SHFT                        0

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_ADDR(x)                                   ((x) + 0x2c0)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_OFFS                                      (0x2c0)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_RMSK                                         0x1ff0f
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_VALID_BMSK                     0x10000
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_VALID_SHFT                          16
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_BMSK                     0xff00
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_SHFT                          8
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_FHRX_FVAL              0x0
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_C2CRX_FVAL             0x1
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_OCRX_FVAL              0x2
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_DMA_FVAL               0x3
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_UC_FVAL                0x4
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_BEFORE_LUT_FVAL            0x10
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_AFTER_LUT_FVAL             0x11
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_ALL_FVAL              0xff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_ID_BMSK                            0xf
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_ID_SHFT                              0
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_ID_C2CTX_0_FVAL                    0x0
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_ID_C2CTX_1_FVAL                    0x1
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_ID_C2CTX_2_FVAL                    0x2
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_ID_C2CRX_0_FVAL                    0x3
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_ID_C2CRX_1_FVAL                    0x4
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_ID_C2CRX_2_FVAL                    0x5
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_ID_DMA_TO_C2C_FVAL                 0x6
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_ID_C2C0_TO_DMA_FVAL                0x7
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_ID_C2C1_TO_DMA_FVAL                0x8
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG_CAPTURE_POINT_ID_C2C2_TO_DMA_FVAL                0x9

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_MASK_m_ADDR(base,m)                      ((base) + 0X2C4 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_MASK_m_OFFS(m)                           (0X2C4 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_MASK_m_RMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_MASK_m_MAXm                                       3
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_MASK_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_MASK_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_MASK_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_MASK_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_MASK_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_MASK_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_MASK_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_MASK_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_MASK_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_MASK_m_MASK_BMSK                         0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_MASK_m_MASK_SHFT                                  0

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_VALUE_m_ADDR(base,m)                     ((base) + 0X2D4 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_VALUE_m_OFFS(m)                          (0X2D4 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_VALUE_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_VALUE_m_MAXm                                      3
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_VALUE_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_VALUE_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_VALUE_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_VALUE_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_VALUE_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_VALUE_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_VALUE_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_VALUE_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_VALUE_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_VALUE_m_VALUE_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_VALUE_m_VALUE_SHFT                                0

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_MASK_m_ADDR(base,m)                     ((base) + 0X2E4 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_MASK_m_OFFS(m)                          (0X2E4 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_MASK_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_MASK_m_MAXm                                      1
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_MASK_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_MASK_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_MASK_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_MASK_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_MASK_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_MASK_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_MASK_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_MASK_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_MASK_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_MASK_m_MASK_BMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_MASK_m_MASK_SHFT                                 0

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_VALUE_m_ADDR(base,m)                    ((base) + 0X2EC + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_VALUE_m_OFFS(m)                         (0X2EC + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_VALUE_m_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_VALUE_m_MAXm                                     1
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_VALUE_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_VALUE_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_VALUE_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_VALUE_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_VALUE_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_VALUE_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_VALUE_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_VALUE_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_VALUE_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_VALUE_m_VALUE_BMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_VALUE_m_VALUE_SHFT                               0

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TID_MASK_VALUE_ADDR(x)                        ((x) + 0x2f4)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TID_MASK_VALUE_OFFS                           (0x2f4)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TID_MASK_VALUE_RMSK                           0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TID_MASK_VALUE_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TID_MASK_VALUE_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TID_MASK_VALUE_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TID_MASK_VALUE_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TID_MASK_VALUE_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TID_MASK_VALUE_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TID_MASK_VALUE_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TID_MASK_VALUE_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TID_MASK_VALUE_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TID_MASK_VALUE_VALUE_BMSK                     0xffff0000
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TID_MASK_VALUE_VALUE_SHFT                             16
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TID_MASK_VALUE_MASK_BMSK                          0xffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_TID_MASK_VALUE_MASK_SHFT                               0

#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_ADDR(x)                       ((x) + 0x2f8)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_OFFS                          (0x2f8)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_RMSK                             0x3ffff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_TERROR_VALUE_BMSK                0x20000
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_TERROR_VALUE_SHFT                     17
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_TERROR_MASK_BMSK                 0x10000
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_TERROR_MASK_SHFT                      16
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_TDEST_VALUE_BMSK                  0xff00
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_TDEST_VALUE_SHFT                       8
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_TDEST_MASK_BMSK                     0xff
#define HWIO_ECPRI_XBAR_XBAR_C2C_TPDM_3_MISC_MASK_VALUE_TDEST_MASK_SHFT                        0

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_ADDR(x)                                  ((x) + 0x300)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_OFFS                                     (0x300)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_RMSK                                        0x1ff0f
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_VALID_BMSK                    0x10000
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_VALID_SHFT                         16
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_BMSK                    0xff00
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_SHFT                         8
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_FHRX_FVAL             0x0
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_C2CRX_FVAL            0x1
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_OCRX_FVAL             0x2
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_DMA_FVAL              0x3
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_UC_FVAL               0x4
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_BEFORE_LUT_FVAL           0x10
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_AFTER_LUT_FVAL            0x11
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_SUB_ID_FROM_ALL_FVAL             0xff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_ID_BMSK                           0xf
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_ID_SHFT                             0
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_ID_OCTX_0_FVAL                    0x0
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_ID_OCTX_1_FVAL                    0x1
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_ID_OCTX_2_FVAL                    0x2
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_ID_OCTX_3_FVAL                    0x3
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_ID_OCRX_0_FVAL                    0x4
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_ID_OCRX_1_FVAL                    0x5
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_ID_OCRX_2_FVAL                    0x6
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG_CAPTURE_POINT_ID_OCRX_3_FVAL                    0x7

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_MASK_m_ADDR(base,m)                     ((base) + 0X304 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_MASK_m_OFFS(m)                          (0X304 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_MASK_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_MASK_m_MAXm                                      3
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_MASK_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_MASK_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_MASK_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_MASK_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_MASK_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_MASK_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_MASK_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_MASK_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_MASK_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_MASK_m_MASK_BMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_MASK_m_MASK_SHFT                                 0

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_VALUE_m_ADDR(base,m)                    ((base) + 0X314 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_VALUE_m_OFFS(m)                         (0X314 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_VALUE_m_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_VALUE_m_MAXm                                     3
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_VALUE_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_VALUE_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_VALUE_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_VALUE_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_VALUE_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_VALUE_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_VALUE_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_VALUE_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_VALUE_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_VALUE_m_VALUE_BMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_VALUE_m_VALUE_SHFT                               0

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_MASK_m_ADDR(base,m)                    ((base) + 0X324 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_MASK_m_OFFS(m)                         (0X324 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_MASK_m_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_MASK_m_MAXm                                     1
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_MASK_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_MASK_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_MASK_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_MASK_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_MASK_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_MASK_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_MASK_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_MASK_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_MASK_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_MASK_m_MASK_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_MASK_m_MASK_SHFT                                0

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_ADDR(base,m)                   ((base) + 0X32C + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_OFFS(m)                        (0X32C + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_RMSK                           0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_MAXm                                    1
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_VALUE_BMSK                     0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_VALUE_m_VALUE_SHFT                              0

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_ADDR(x)                       ((x) + 0x334)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_OFFS                          (0x334)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_RMSK                          0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_VALUE_BMSK                    0xffff0000
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_VALUE_SHFT                            16
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_MASK_BMSK                         0xffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_TID_MASK_VALUE_MASK_SHFT                              0

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_ADDR(x)                      ((x) + 0x338)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_OFFS                         (0x338)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_RMSK                            0x3ffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_TERROR_VALUE_BMSK               0x20000
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_TERROR_VALUE_SHFT                    17
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_TERROR_MASK_BMSK                0x10000
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_TERROR_MASK_SHFT                     16
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_TDEST_VALUE_BMSK                 0xff00
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_TDEST_VALUE_SHFT                      8
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_TDEST_MASK_BMSK                    0xff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE_TDEST_MASK_SHFT                       0

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_ADDR(x)                                  ((x) + 0x340)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_OFFS                                     (0x340)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_RMSK                                        0x1ff0f
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_VALID_BMSK                    0x10000
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_VALID_SHFT                         16
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_BMSK                    0xff00
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_SHFT                         8
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_FHRX_FVAL             0x0
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_C2CRX_FVAL            0x1
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_OCRX_FVAL             0x2
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_DMA_FVAL              0x3
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_UC_FVAL               0x4
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_BEFORE_LUT_FVAL           0x10
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_AFTER_LUT_FVAL            0x11
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_SUB_ID_FROM_ALL_FVAL             0xff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_ID_BMSK                           0xf
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_ID_SHFT                             0
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_ID_OCTX_0_FVAL                    0x0
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_ID_OCTX_1_FVAL                    0x1
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_ID_OCTX_2_FVAL                    0x2
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_ID_OCTX_3_FVAL                    0x3
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_ID_OCRX_0_FVAL                    0x4
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_ID_OCRX_1_FVAL                    0x5
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_ID_OCRX_2_FVAL                    0x6
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG_CAPTURE_POINT_ID_OCRX_3_FVAL                    0x7

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_MASK_m_ADDR(base,m)                     ((base) + 0X344 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_MASK_m_OFFS(m)                          (0X344 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_MASK_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_MASK_m_MAXm                                      3
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_MASK_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_MASK_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_MASK_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_MASK_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_MASK_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_MASK_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_MASK_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_MASK_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_MASK_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_MASK_m_MASK_BMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_MASK_m_MASK_SHFT                                 0

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_VALUE_m_ADDR(base,m)                    ((base) + 0X354 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_VALUE_m_OFFS(m)                         (0X354 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_VALUE_m_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_VALUE_m_MAXm                                     3
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_VALUE_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_VALUE_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_VALUE_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_VALUE_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_VALUE_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_VALUE_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_VALUE_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_VALUE_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_VALUE_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_VALUE_m_VALUE_BMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_VALUE_m_VALUE_SHFT                               0

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_MASK_m_ADDR(base,m)                    ((base) + 0X364 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_MASK_m_OFFS(m)                         (0X364 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_MASK_m_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_MASK_m_MAXm                                     1
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_MASK_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_MASK_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_MASK_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_MASK_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_MASK_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_MASK_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_MASK_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_MASK_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_MASK_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_MASK_m_MASK_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_MASK_m_MASK_SHFT                                0

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_ADDR(base,m)                   ((base) + 0X36C + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_OFFS(m)                        (0X36C + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_RMSK                           0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_MAXm                                    1
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_VALUE_BMSK                     0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_VALUE_m_VALUE_SHFT                              0

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_ADDR(x)                       ((x) + 0x374)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_OFFS                          (0x374)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_RMSK                          0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_VALUE_BMSK                    0xffff0000
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_VALUE_SHFT                            16
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_MASK_BMSK                         0xffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_TID_MASK_VALUE_MASK_SHFT                              0

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_ADDR(x)                      ((x) + 0x378)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_OFFS                         (0x378)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_RMSK                            0x3ffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_TERROR_VALUE_BMSK               0x20000
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_TERROR_VALUE_SHFT                    17
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_TERROR_MASK_BMSK                0x10000
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_TERROR_MASK_SHFT                     16
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_TDEST_VALUE_BMSK                 0xff00
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_TDEST_VALUE_SHFT                      8
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_TDEST_MASK_BMSK                    0xff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE_TDEST_MASK_SHFT                       0

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_ADDR(x)                                  ((x) + 0x380)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_OFFS                                     (0x380)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_RMSK                                        0x1ff0f
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_VALID_BMSK                    0x10000
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_VALID_SHFT                         16
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_BMSK                    0xff00
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_SHFT                         8
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_FHRX_FVAL             0x0
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_C2CRX_FVAL            0x1
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_OCRX_FVAL             0x2
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_DMA_FVAL              0x3
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_UC_FVAL               0x4
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_BEFORE_LUT_FVAL           0x10
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_AFTER_LUT_FVAL            0x11
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_SUB_ID_FROM_ALL_FVAL             0xff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_ID_BMSK                           0xf
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_ID_SHFT                             0
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_ID_OCTX_0_FVAL                    0x0
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_ID_OCTX_1_FVAL                    0x1
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_ID_OCTX_2_FVAL                    0x2
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_ID_OCTX_3_FVAL                    0x3
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_ID_OCRX_0_FVAL                    0x4
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_ID_OCRX_1_FVAL                    0x5
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_ID_OCRX_2_FVAL                    0x6
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG_CAPTURE_POINT_ID_OCRX_3_FVAL                    0x7

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_MASK_m_ADDR(base,m)                     ((base) + 0X384 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_MASK_m_OFFS(m)                          (0X384 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_MASK_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_MASK_m_MAXm                                      3
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_MASK_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_MASK_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_MASK_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_MASK_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_MASK_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_MASK_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_MASK_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_MASK_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_MASK_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_MASK_m_MASK_BMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_MASK_m_MASK_SHFT                                 0

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_VALUE_m_ADDR(base,m)                    ((base) + 0X394 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_VALUE_m_OFFS(m)                         (0X394 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_VALUE_m_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_VALUE_m_MAXm                                     3
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_VALUE_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_VALUE_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_VALUE_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_VALUE_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_VALUE_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_VALUE_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_VALUE_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_VALUE_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_VALUE_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_VALUE_m_VALUE_BMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_VALUE_m_VALUE_SHFT                               0

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_MASK_m_ADDR(base,m)                    ((base) + 0X3A4 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_MASK_m_OFFS(m)                         (0X3A4 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_MASK_m_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_MASK_m_MAXm                                     1
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_MASK_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_MASK_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_MASK_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_MASK_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_MASK_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_MASK_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_MASK_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_MASK_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_MASK_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_MASK_m_MASK_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_MASK_m_MASK_SHFT                                0

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_ADDR(base,m)                   ((base) + 0X3AC + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_OFFS(m)                        (0X3AC + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_RMSK                           0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_MAXm                                    1
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_VALUE_BMSK                     0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_VALUE_m_VALUE_SHFT                              0

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_ADDR(x)                       ((x) + 0x3b4)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_OFFS                          (0x3b4)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_RMSK                          0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_VALUE_BMSK                    0xffff0000
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_VALUE_SHFT                            16
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_MASK_BMSK                         0xffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_TID_MASK_VALUE_MASK_SHFT                              0

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_ADDR(x)                      ((x) + 0x3b8)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_OFFS                         (0x3b8)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_RMSK                            0x3ffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_TERROR_VALUE_BMSK               0x20000
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_TERROR_VALUE_SHFT                    17
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_TERROR_MASK_BMSK                0x10000
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_TERROR_MASK_SHFT                     16
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_TDEST_VALUE_BMSK                 0xff00
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_TDEST_VALUE_SHFT                      8
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_TDEST_MASK_BMSK                    0xff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE_TDEST_MASK_SHFT                       0

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_ADDR(x)                                  ((x) + 0x3c0)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_OFFS                                     (0x3c0)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_RMSK                                        0x1ff0f
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_VALID_BMSK                    0x10000
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_VALID_SHFT                         16
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_BMSK                    0xff00
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_SHFT                         8
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_FHRX_FVAL             0x0
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_C2CRX_FVAL            0x1
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_OCRX_FVAL             0x2
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_DMA_FVAL              0x3
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_UC_FVAL               0x4
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_BEFORE_LUT_FVAL           0x10
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_AFTER_LUT_FVAL            0x11
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_SUB_ID_FROM_ALL_FVAL             0xff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_ID_BMSK                           0xf
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_ID_SHFT                             0
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_ID_OCTX_0_FVAL                    0x0
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_ID_OCTX_1_FVAL                    0x1
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_ID_OCTX_2_FVAL                    0x2
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_ID_OCTX_3_FVAL                    0x3
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_ID_OCRX_0_FVAL                    0x4
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_ID_OCRX_1_FVAL                    0x5
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_ID_OCRX_2_FVAL                    0x6
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG_CAPTURE_POINT_ID_OCRX_3_FVAL                    0x7

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_MASK_m_ADDR(base,m)                     ((base) + 0X3C4 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_MASK_m_OFFS(m)                          (0X3C4 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_MASK_m_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_MASK_m_MAXm                                      3
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_MASK_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_MASK_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_MASK_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_MASK_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_MASK_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_MASK_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_MASK_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_MASK_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_MASK_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_MASK_m_MASK_BMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_MASK_m_MASK_SHFT                                 0

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_VALUE_m_ADDR(base,m)                    ((base) + 0X3D4 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_VALUE_m_OFFS(m)                         (0X3D4 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_VALUE_m_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_VALUE_m_MAXm                                     3
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_VALUE_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_VALUE_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_VALUE_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_VALUE_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_VALUE_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_VALUE_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_VALUE_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_VALUE_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_VALUE_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_VALUE_m_VALUE_BMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_VALUE_m_VALUE_SHFT                               0

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_MASK_m_ADDR(base,m)                    ((base) + 0X3E4 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_MASK_m_OFFS(m)                         (0X3E4 + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_MASK_m_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_MASK_m_MAXm                                     1
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_MASK_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_MASK_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_MASK_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_MASK_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_MASK_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_MASK_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_MASK_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_MASK_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_MASK_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_MASK_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_MASK_m_MASK_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_MASK_m_MASK_SHFT                                0

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_ADDR(base,m)                   ((base) + 0X3EC + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_OFFS(m)                        (0X3EC + (0x4*(m)))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_RMSK                           0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_MAXm                                    1
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_INI(base,m)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_ADDR(base,m), HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_INMI(base,m,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_ADDR(base,m), mask)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_OUTI(base,m,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_ADDR(base,m),val)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_OUTMI(base,m,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_ADDR(base,m),mask,val,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_INI(base,m))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_VALUE_BMSK                     0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_VALUE_m_VALUE_SHFT                              0

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_ADDR(x)                       ((x) + 0x3f4)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_OFFS                          (0x3f4)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_RMSK                          0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_VALUE_BMSK                    0xffff0000
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_VALUE_SHFT                            16
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_MASK_BMSK                         0xffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_TID_MASK_VALUE_MASK_SHFT                              0

#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_ADDR(x)                      ((x) + 0x3f8)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_OFFS                         (0x3f8)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_RMSK                            0x3ffff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_TERROR_VALUE_BMSK               0x20000
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_TERROR_VALUE_SHFT                    17
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_TERROR_MASK_BMSK                0x10000
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_TERROR_MASK_SHFT                     16
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_TDEST_VALUE_BMSK                 0xff00
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_TDEST_VALUE_SHFT                      8
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_TDEST_MASK_BMSK                    0xff
#define HWIO_ECPRI_XBAR_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE_TDEST_MASK_SHFT                       0

#define HWIO_ECPRI_XBAR_XBAR_TPDM_GLOBAL_CFG_ADDR(x)                                  ((x) + 0x400)
#define HWIO_ECPRI_XBAR_XBAR_TPDM_GLOBAL_CFG_OFFS                                     (0x400)
#define HWIO_ECPRI_XBAR_XBAR_TPDM_GLOBAL_CFG_RMSK                                            0x1
#define HWIO_ECPRI_XBAR_XBAR_TPDM_GLOBAL_CFG_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_TPDM_GLOBAL_CFG_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_TPDM_GLOBAL_CFG_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_TPDM_GLOBAL_CFG_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_TPDM_GLOBAL_CFG_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_TPDM_GLOBAL_CFG_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_TPDM_GLOBAL_CFG_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_TPDM_GLOBAL_CFG_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_TPDM_GLOBAL_CFG_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_TPDM_GLOBAL_CFG_SHARED_DATA_MODE_BMSK                           0x1
#define HWIO_ECPRI_XBAR_XBAR_TPDM_GLOBAL_CFG_SHARED_DATA_MODE_SHFT                             0

#define HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_ADDR(x)                             ((x) + 0x800)
#define HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_OFFS                                (0x800)
#define HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RMSK                                0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_3_BMSK                      0xff000000
#define HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_3_SHFT                              24
#define HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_2_BMSK                        0xff0000
#define HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_2_SHFT                              16
#define HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_1_BMSK                          0xff00
#define HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_1_SHFT                               8
#define HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_0_BMSK                            0xff
#define HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_0_SHFT                               0

#define HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_ADDR(x)                             ((x) + 0x804)
#define HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_OFFS                                (0x804)
#define HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_RMSK                                0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_RING_ID_3_BMSK                      0xff000000
#define HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_RING_ID_3_SHFT                              24
#define HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_RING_ID_2_BMSK                        0xff0000
#define HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_RING_ID_2_SHFT                              16
#define HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_RING_ID_1_BMSK                          0xff00
#define HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_RING_ID_1_SHFT                               8
#define HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_RING_ID_0_BMSK                            0xff
#define HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_RING_ID_0_SHFT                               0

#define HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_ADDR(x)                             ((x) + 0x808)
#define HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_OFFS                                (0x808)
#define HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_RMSK                                0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_RING_ID_3_BMSK                      0xff000000
#define HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_RING_ID_3_SHFT                              24
#define HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_RING_ID_2_BMSK                        0xff0000
#define HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_RING_ID_2_SHFT                              16
#define HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_RING_ID_1_BMSK                          0xff00
#define HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_RING_ID_1_SHFT                               8
#define HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_RING_ID_0_BMSK                            0xff
#define HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_RING_ID_0_SHFT                               0

#define HWIO_ECPRI_XBAR_XBAR_FHRX_n_DEFAULT_LUT_ADDR(base,n)                          ((base) + 0X80C + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_FHRX_n_DEFAULT_LUT_OFFS(n)                               (0X80C + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_FHRX_n_DEFAULT_LUT_RMSK                                       0xfff
#define HWIO_ECPRI_XBAR_XBAR_FHRX_n_DEFAULT_LUT_MAXn                                           2
#define HWIO_ECPRI_XBAR_XBAR_FHRX_n_DEFAULT_LUT_INI(base,n)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FHRX_n_DEFAULT_LUT_ADDR(base,n), HWIO_ECPRI_XBAR_XBAR_FHRX_n_DEFAULT_LUT_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_FHRX_n_DEFAULT_LUT_INMI(base,n,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FHRX_n_DEFAULT_LUT_ADDR(base,n), mask)
#define HWIO_ECPRI_XBAR_XBAR_FHRX_n_DEFAULT_LUT_OUTI(base,n,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FHRX_n_DEFAULT_LUT_ADDR(base,n),val)
#define HWIO_ECPRI_XBAR_XBAR_FHRX_n_DEFAULT_LUT_OUTMI(base,n,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FHRX_n_DEFAULT_LUT_ADDR(base,n),mask,val,HWIO_ECPRI_XBAR_XBAR_FHRX_n_DEFAULT_LUT_INI(base,n))
#define HWIO_ECPRI_XBAR_XBAR_FHRX_n_DEFAULT_LUT_ROUTE_TO_DMA_BMSK                          0x800
#define HWIO_ECPRI_XBAR_XBAR_FHRX_n_DEFAULT_LUT_ROUTE_TO_DMA_SHFT                             11
#define HWIO_ECPRI_XBAR_XBAR_FHRX_n_DEFAULT_LUT_ROUTE_TO_C2C_BMSK                          0x400
#define HWIO_ECPRI_XBAR_XBAR_FHRX_n_DEFAULT_LUT_ROUTE_TO_C2C_SHFT                             10
#define HWIO_ECPRI_XBAR_XBAR_FHRX_n_DEFAULT_LUT_ROUTE_TO_ORAN_BMSK                         0x200
#define HWIO_ECPRI_XBAR_XBAR_FHRX_n_DEFAULT_LUT_ROUTE_TO_ORAN_SHFT                             9
#define HWIO_ECPRI_XBAR_XBAR_FHRX_n_DEFAULT_LUT_OC_LINK_ID_BMSK                            0x180
#define HWIO_ECPRI_XBAR_XBAR_FHRX_n_DEFAULT_LUT_OC_LINK_ID_SHFT                                7
#define HWIO_ECPRI_XBAR_XBAR_FHRX_n_DEFAULT_LUT_DMA_RING_ID_BMSK                            0x7f
#define HWIO_ECPRI_XBAR_XBAR_FHRX_n_DEFAULT_LUT_DMA_RING_ID_SHFT                               0

#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_0_ADDR(x)                              ((x) + 0x820)
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_0_OFFS                                 (0x820)
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_0_RMSK                                 0x1ff7fdff
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_0_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_0_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_0_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_0_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_0_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_0_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_0_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_0_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_0_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_0_VALID_2_BMSK                         0x10000000
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_0_VALID_2_SHFT                                 28
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_0_MSG_TYPE_2_BMSK                       0xff00000
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_0_MSG_TYPE_2_SHFT                              20
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_0_VALID_1_BMSK                            0x40000
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_0_VALID_1_SHFT                                 18
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_0_MSG_TYPE_1_BMSK                         0x3fc00
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_0_MSG_TYPE_1_SHFT                              10
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_0_VALID_0_BMSK                              0x100
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_0_VALID_0_SHFT                                  8
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_0_MSG_TYPE_0_BMSK                            0xff
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_0_MSG_TYPE_0_SHFT                               0

#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_1_ADDR(x)                              ((x) + 0x824)
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_1_OFFS                                 (0x824)
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_1_RMSK                                 0x1ff7fdff
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_1_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_1_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_1_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_1_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_1_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_1_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_1_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_1_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_1_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_1_VALID_5_BMSK                         0x10000000
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_1_VALID_5_SHFT                                 28
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_1_MSG_TYPE_5_BMSK                       0xff00000
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_1_MSG_TYPE_5_SHFT                              20
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_1_VALID_4_BMSK                            0x40000
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_1_VALID_4_SHFT                                 18
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_1_MSG_TYPE_4_BMSK                         0x3fc00
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_1_MSG_TYPE_4_SHFT                              10
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_1_VALID_3_BMSK                              0x100
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_1_VALID_3_SHFT                                  8
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_1_MSG_TYPE_3_BMSK                            0xff
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_1_MSG_TYPE_3_SHFT                               0

#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_ADDR(base,n)                  ((base) + 0X828 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_OFFS(n)                       (0X828 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_RMSK                               0xfff
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_MAXn                                   5
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_INI(base,n)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_ADDR(base,n), HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_INMI(base,n,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_ADDR(base,n), mask)
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_OUTI(base,n,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_ADDR(base,n),val)
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_OUTMI(base,n,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_ADDR(base,n),mask,val,HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_INI(base,n))
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_ROUTE_TO_DMA_BMSK                  0x800
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_ROUTE_TO_DMA_SHFT                     11
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_ROUTE_TO_C2C_BMSK                  0x400
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_ROUTE_TO_C2C_SHFT                     10
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_ROUTE_TO_ORAN_BMSK                 0x200
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_ROUTE_TO_ORAN_SHFT                     9
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_OC_LINK_ID_BMSK                    0x180
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_OC_LINK_ID_SHFT                        7
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_DMA_RING_ID_BMSK                    0x7f
#define HWIO_ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT_DMA_RING_ID_SHFT                       0

#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_ADDR(x)                             ((x) + 0x850)
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_OFFS                                (0x850)
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_RMSK                                0x1ff7fdff
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_VALID_2_BMSK                        0x10000000
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_VALID_2_SHFT                                28
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_MSG_TYPE_2_BMSK                      0xff00000
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_MSG_TYPE_2_SHFT                             20
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_VALID_1_BMSK                           0x40000
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_VALID_1_SHFT                                18
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_MSG_TYPE_1_BMSK                        0x3fc00
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_MSG_TYPE_1_SHFT                             10
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_VALID_0_BMSK                             0x100
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_VALID_0_SHFT                                 8
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_MSG_TYPE_0_BMSK                           0xff
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_MSG_TYPE_0_SHFT                              0

#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_1_ADDR(x)                             ((x) + 0x854)
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_1_OFFS                                (0x854)
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_1_RMSK                                0x1ff7fdff
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_1_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_1_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_1_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_1_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_1_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_1_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_1_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_1_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_1_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_1_VALID_5_BMSK                        0x10000000
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_1_VALID_5_SHFT                                28
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_1_MSG_TYPE_5_BMSK                      0xff00000
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_1_MSG_TYPE_5_SHFT                             20
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_1_VALID_4_BMSK                           0x40000
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_1_VALID_4_SHFT                                18
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_1_MSG_TYPE_4_BMSK                        0x3fc00
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_1_MSG_TYPE_4_SHFT                             10
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_1_VALID_3_BMSK                             0x100
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_1_VALID_3_SHFT                                 8
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_1_MSG_TYPE_3_BMSK                           0xff
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_1_MSG_TYPE_3_SHFT                              0

#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_ADDR(base,n)                 ((base) + 0X858 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_OFFS(n)                      (0X858 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_RMSK                         0x1fffffff
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_MAXn                                  5
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_INI(base,n)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_ADDR(base,n), HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_INMI(base,n,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_ADDR(base,n), mask)
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_OUTI(base,n,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_ADDR(base,n),val)
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_OUTMI(base,n,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_ADDR(base,n),mask,val,HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_INI(base,n))
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_ROUTE_TO_DMA_BMSK            0x10000000
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_ROUTE_TO_DMA_SHFT                    28
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_ROUTE_TO_FH_BMSK              0x8000000
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_ROUTE_TO_FH_SHFT                     27
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_ROUTE_TO_ORAN_BMSK            0x4000000
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_ROUTE_TO_ORAN_SHFT                   26
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_L3_ENCAP_VALID_BMSK           0x2000000
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_L3_ENCAP_VALID_SHFT                  25
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_L3_ENCAP_INFO_BMSK            0x1fe0000
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_L3_ENCAP_INFO_SHFT                   17
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_L2_ENCAP_INFO_BMSK              0x1fe00
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_L2_ENCAP_INFO_SHFT                    9
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_OC_LINK_ID_BMSK                   0x180
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_OC_LINK_ID_SHFT                       7
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_DMA_RING_ID_BMSK                   0x7f
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT_DMA_RING_ID_SHFT                      0

#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_ADDR(base,n)                      ((base) + 0X870 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_OFFS(n)                           (0X870 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_RMSK                              0x1fffffff
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_MAXn                                       2
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_INI(base,n)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_ADDR(base,n), HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_INMI(base,n,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_ADDR(base,n), mask)
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_OUTI(base,n,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_ADDR(base,n),val)
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_OUTMI(base,n,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_ADDR(base,n),mask,val,HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_INI(base,n))
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_ROUTE_TO_DMA_BMSK                 0x10000000
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_ROUTE_TO_DMA_SHFT                         28
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_ROUTE_TO_FH_BMSK                   0x8000000
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_ROUTE_TO_FH_SHFT                          27
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_ROUTE_TO_ORAN_BMSK                 0x4000000
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_ROUTE_TO_ORAN_SHFT                        26
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_L3_ENCAP_VALID_BMSK                0x2000000
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_L3_ENCAP_VALID_SHFT                       25
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_L3_ENCAP_INFO_BMSK                 0x1fe0000
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_L3_ENCAP_INFO_SHFT                        17
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_L2_ENCAP_INFO_BMSK                   0x1fe00
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_L2_ENCAP_INFO_SHFT                         9
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_OC_LINK_ID_BMSK                        0x180
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_OC_LINK_ID_SHFT                            7
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_DMA_RING_ID_BMSK                        0x7f
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT_DMA_RING_ID_SHFT                           0

#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_ADDR(base,n)                      ((base) + 0X880 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_OFFS(n)                           (0X880 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_RMSK                              0x1fffffff
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_MAXn                                       2
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_INI(base,n)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_ADDR(base,n), HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_INMI(base,n,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_ADDR(base,n), mask)
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_OUTI(base,n,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_ADDR(base,n),val)
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_OUTMI(base,n,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_ADDR(base,n),mask,val,HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_INI(base,n))
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_ROUTE_TO_DMA_BMSK                 0x10000000
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_ROUTE_TO_DMA_SHFT                         28
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_ROUTE_TO_FH_BMSK                   0x8000000
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_ROUTE_TO_FH_SHFT                          27
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_ROUTE_TO_ORAN_BMSK                 0x4000000
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_ROUTE_TO_ORAN_SHFT                        26
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_L3_ENCAP_VALID_BMSK                0x2000000
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_L3_ENCAP_VALID_SHFT                       25
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_L3_ENCAP_INFO_BMSK                 0x1fe0000
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_L3_ENCAP_INFO_SHFT                        17
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_L2_ENCAP_INFO_BMSK                   0x1fe00
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_L2_ENCAP_INFO_SHFT                         9
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_OC_LINK_ID_BMSK                        0x180
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_OC_LINK_ID_SHFT                            7
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_DMA_RING_ID_BMSK                        0x7f
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT_DMA_RING_ID_SHFT                           0

#define HWIO_ECPRI_XBAR_XBAR_C2CRX_NON_ECPRI_LUT_ADDR(x)                              ((x) + 0x890)
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_NON_ECPRI_LUT_OFFS                                 (0x890)
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_NON_ECPRI_LUT_RMSK                                   0xffffff
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_NON_ECPRI_LUT_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_C2CRX_NON_ECPRI_LUT_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_NON_ECPRI_LUT_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2CRX_NON_ECPRI_LUT_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_NON_ECPRI_LUT_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_C2CRX_NON_ECPRI_LUT_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_NON_ECPRI_LUT_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_C2CRX_NON_ECPRI_LUT_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_C2CRX_NON_ECPRI_LUT_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_NON_ECPRI_LUT_RING_ID_2_BMSK                         0xff0000
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_NON_ECPRI_LUT_RING_ID_2_SHFT                               16
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_NON_ECPRI_LUT_RING_ID_1_BMSK                           0xff00
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_NON_ECPRI_LUT_RING_ID_1_SHFT                                8
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_NON_ECPRI_LUT_RING_ID_0_BMSK                             0xff
#define HWIO_ECPRI_XBAR_XBAR_C2CRX_NON_ECPRI_LUT_RING_ID_0_SHFT                                0

#define HWIO_ECPRI_XBAR_XBAR_OCRX_FH_n_DEFAULT_LUT_ADDR(base,n)                       ((base) + 0X8A0 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_OCRX_FH_n_DEFAULT_LUT_OFFS(n)                            (0X8A0 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_OCRX_FH_n_DEFAULT_LUT_RMSK                                  0x3ffff
#define HWIO_ECPRI_XBAR_XBAR_OCRX_FH_n_DEFAULT_LUT_MAXn                                        2
#define HWIO_ECPRI_XBAR_XBAR_OCRX_FH_n_DEFAULT_LUT_INI(base,n)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_OCRX_FH_n_DEFAULT_LUT_ADDR(base,n), HWIO_ECPRI_XBAR_XBAR_OCRX_FH_n_DEFAULT_LUT_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_OCRX_FH_n_DEFAULT_LUT_INMI(base,n,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_OCRX_FH_n_DEFAULT_LUT_ADDR(base,n), mask)
#define HWIO_ECPRI_XBAR_XBAR_OCRX_FH_n_DEFAULT_LUT_OUTI(base,n,val)        \
	out_dword(HWIO_ECPRI_XBAR_XBAR_OCRX_FH_n_DEFAULT_LUT_ADDR(base,n),val)
#define HWIO_ECPRI_XBAR_XBAR_OCRX_FH_n_DEFAULT_LUT_OUTMI(base,n,mask,val) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_OCRX_FH_n_DEFAULT_LUT_ADDR(base,n),mask,val,HWIO_ECPRI_XBAR_XBAR_OCRX_FH_n_DEFAULT_LUT_INI(base,n))
#define HWIO_ECPRI_XBAR_XBAR_OCRX_FH_n_DEFAULT_LUT_DROP_BMSK                             0x20000
#define HWIO_ECPRI_XBAR_XBAR_OCRX_FH_n_DEFAULT_LUT_DROP_SHFT                                  17
#define HWIO_ECPRI_XBAR_XBAR_OCRX_FH_n_DEFAULT_LUT_L3_ENCAP_VALID_BMSK                   0x10000
#define HWIO_ECPRI_XBAR_XBAR_OCRX_FH_n_DEFAULT_LUT_L3_ENCAP_VALID_SHFT                        16
#define HWIO_ECPRI_XBAR_XBAR_OCRX_FH_n_DEFAULT_LUT_L3_ENCAP_INFO_BMSK                     0xff00
#define HWIO_ECPRI_XBAR_XBAR_OCRX_FH_n_DEFAULT_LUT_L3_ENCAP_INFO_SHFT                          8
#define HWIO_ECPRI_XBAR_XBAR_OCRX_FH_n_DEFAULT_LUT_L2_ENCAP_INFO_BMSK                       0xff
#define HWIO_ECPRI_XBAR_XBAR_OCRX_FH_n_DEFAULT_LUT_L2_ENCAP_INFO_SHFT                          0

#define HWIO_ECPRI_XBAR_XBAR_OCRX_C2C_DEFAULT_LUT_ADDR(x)                             ((x) + 0x8b0)
#define HWIO_ECPRI_XBAR_XBAR_OCRX_C2C_DEFAULT_LUT_OFFS                                (0x8b0)
#define HWIO_ECPRI_XBAR_XBAR_OCRX_C2C_DEFAULT_LUT_RMSK                                 0x301ffff
#define HWIO_ECPRI_XBAR_XBAR_OCRX_C2C_DEFAULT_LUT_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_OCRX_C2C_DEFAULT_LUT_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_OCRX_C2C_DEFAULT_LUT_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_OCRX_C2C_DEFAULT_LUT_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_OCRX_C2C_DEFAULT_LUT_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_OCRX_C2C_DEFAULT_LUT_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_OCRX_C2C_DEFAULT_LUT_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_OCRX_C2C_DEFAULT_LUT_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_OCRX_C2C_DEFAULT_LUT_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_OCRX_C2C_DEFAULT_LUT_C2C_PORT_NUM_BMSK                    0x3000000
#define HWIO_ECPRI_XBAR_XBAR_OCRX_C2C_DEFAULT_LUT_C2C_PORT_NUM_SHFT                           24
#define HWIO_ECPRI_XBAR_XBAR_OCRX_C2C_DEFAULT_LUT_L3_ENCAP_VALID_BMSK                    0x10000
#define HWIO_ECPRI_XBAR_XBAR_OCRX_C2C_DEFAULT_LUT_L3_ENCAP_VALID_SHFT                         16
#define HWIO_ECPRI_XBAR_XBAR_OCRX_C2C_DEFAULT_LUT_L3_ENCAP_INFO_BMSK                      0xff00
#define HWIO_ECPRI_XBAR_XBAR_OCRX_C2C_DEFAULT_LUT_L3_ENCAP_INFO_SHFT                           8
#define HWIO_ECPRI_XBAR_XBAR_OCRX_C2C_DEFAULT_LUT_L2_ENCAP_INFO_BMSK                        0xff
#define HWIO_ECPRI_XBAR_XBAR_OCRX_C2C_DEFAULT_LUT_L2_ENCAP_INFO_SHFT                           0

#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_ADDR_ADDR(x)                                ((x) + 0x1000)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_ADDR_OFFS                                   (0x1000)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_ADDR_RMSK                                       0xffff
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_ADDR_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_ADDR_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_ADDR_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_ADDR_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_ADDR_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_ADDR_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_ADDR_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_ADDR_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_ADDR_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_ADDR_ADDR_BMSK                                  0xffff
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_ADDR_ADDR_SHFT                                       0

#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_SIZE_ADDR(x)                                ((x) + 0x1004)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_SIZE_OFFS                                   (0x1004)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_SIZE_RMSK                                       0x7fff
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_SIZE_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_SIZE_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_SIZE_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_SIZE_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_SIZE_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_SIZE_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_SIZE_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_SIZE_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_SIZE_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_SIZE_SIZE_BMSK                                  0x7fff
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_SIZE_SIZE_SHFT                                       0

#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_RD_ADDR(x)                                  ((x) + 0x1008)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_RD_OFFS                                     (0x1008)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_RD_RMSK                                         0xffff
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_RD_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_RD_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_RD_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_RD_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_RD_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_RD_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_RD_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_RD_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_RD_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_RD_ADDR_BMSK                                    0xffff
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_BUFF_RD_ADDR_SHFT                                         0

#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_POP_ADDR(x)                             ((x) + 0x100c)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_POP_OFFS                                (0x100c)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_POP_RMSK                                 0x10f3fff
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_POP_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_POP_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_POP_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_POP_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_POP_ERR_BMSK                             0x1000000
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_POP_ERR_SHFT                                    24
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_POP_PORT_BMSK                              0xc0000
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_POP_PORT_SHFT                                   18
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_POP_LINK_BMSK                              0x30000
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_POP_LINK_SHFT                                   16
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_POP_LENGTH_BMSK                             0x3fff
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_POP_LENGTH_SHFT                                  0

#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_NO_POP_ADDR(x)                          ((x) + 0x1010)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_NO_POP_OFFS                             (0x1010)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_NO_POP_RMSK                              0x10f3fff
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_NO_POP_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_NO_POP_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_NO_POP_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_NO_POP_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_NO_POP_ERR_BMSK                          0x1000000
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_NO_POP_ERR_SHFT                                 24
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_NO_POP_PORT_BMSK                           0xc0000
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_NO_POP_PORT_SHFT                                18
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_NO_POP_LINK_BMSK                           0x30000
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_NO_POP_LINK_SHFT                                16
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_NO_POP_LENGTH_BMSK                          0x3fff
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_NO_POP_LENGTH_SHFT                               0

#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_ADDR(x)                                   ((x) + 0x1014)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_OFFS                                      (0x1014)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_RMSK                                           0x3ff
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_UC_PKT_DROP_BMSK                               0x380
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_UC_PKT_DROP_SHFT                                   7
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_UC_PKT_ERR_BMSK                                 0x70
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_UC_PKT_ERR_SHFT                                    4
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_UC_PKT_OVERFLOW_BMSK                             0xe
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_UC_PKT_OVERFLOW_SHFT                               1
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_UC_PKT_PENDING_BMSK                              0x1
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_UC_PKT_PENDING_SHFT                                0

#define HWIO_ECPRI_XBAR_XBAR_UC_FH_CTRL_ADDR(x)                                       ((x) + 0x1018)
#define HWIO_ECPRI_XBAR_XBAR_UC_FH_CTRL_OFFS                                          (0x1018)
#define HWIO_ECPRI_XBAR_XBAR_UC_FH_CTRL_RMSK                                                 0x3
#define HWIO_ECPRI_XBAR_XBAR_UC_FH_CTRL_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_UC_FH_CTRL_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_UC_FH_CTRL_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_UC_FH_CTRL_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_UC_FH_CTRL_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_UC_FH_CTRL_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_UC_FH_CTRL_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_UC_FH_CTRL_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_UC_FH_CTRL_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_UC_FH_CTRL_FHRX_UC_PKT_ERR_DROP_BMSK                            0x2
#define HWIO_ECPRI_XBAR_XBAR_UC_FH_CTRL_FHRX_UC_PKT_ERR_DROP_SHFT                              1
#define HWIO_ECPRI_XBAR_XBAR_UC_FH_CTRL_FHRX_UC_ENABLE_BMSK                                  0x1
#define HWIO_ECPRI_XBAR_XBAR_UC_FH_CTRL_FHRX_UC_ENABLE_SHFT                                    0

#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ADDR_ADDR(x)                                 ((x) + 0x101c)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ADDR_OFFS                                    (0x101c)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ADDR_RMSK                                    0x3fffffff
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ADDR_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ADDR_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ADDR_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ADDR_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ADDR_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ADDR_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ADDR_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ADDR_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ADDR_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ADDR_LENGTH_BMSK                             0x3fff0000
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ADDR_LENGTH_SHFT                                     16
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ADDR_ADDR_BMSK                                   0xffff
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ADDR_ADDR_SHFT                                        0

#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR_ADDR(x)                                 ((x) + 0x1020)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR_OFFS                                    (0x1020)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR_RMSK                                    0x8f0fffff
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR_PKT_AVAIL_BMSK                          0x80000000
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR_PKT_AVAIL_SHFT                                  31
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR_PORT_BMSK                                0xc000000
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR_PORT_SHFT                                       26
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR_LINK_BMSK                                0x3000000
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR_LINK_SHFT                                       24
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR_L3_ENCAP_VALID_BMSK                        0x80000
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR_L3_ENCAP_VALID_SHFT                             19
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR_L2_ENCAP_VALID_BMSK                        0x40000
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR_L2_ENCAP_VALID_SHFT                             18
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR_L3_ENCAP_BMSK                              0x3fe00
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR_L3_ENCAP_SHFT                                    9
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR_L2_ENCAP_BMSK                                0x1ff
#define HWIO_ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR_L2_ENCAP_SHFT                                    0

#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_PKT_CNT_n_ADDR(base,n)                          ((base) + 0X2000 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_PKT_CNT_n_OFFS(n)                               (0X2000 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_PKT_CNT_n_RMSK                                  0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_PKT_CNT_n_MAXn                                          11
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_PKT_CNT_n_INI(base,n)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_PKT_CNT_n_ADDR(base,n), HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_PKT_CNT_n_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_PKT_CNT_n_INMI(base,n,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_PKT_CNT_n_ADDR(base,n), mask)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_PKT_CNT_n_CNT_BMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_PKT_CNT_n_CNT_SHFT                                       0

#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_DMA_PKT_CNT_ADDR(x)                             ((x) + 0x2060)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_DMA_PKT_CNT_OFFS                                (0x2060)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_DMA_PKT_CNT_RMSK                                0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_DMA_PKT_CNT_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_DMA_PKT_CNT_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_DMA_PKT_CNT_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_DMA_PKT_CNT_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_DMA_PKT_CNT_CNT_BMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_DMA_PKT_CNT_CNT_SHFT                                     0

#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UC_PKT_CNT_ADDR(x)                              ((x) + 0x2090)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UC_PKT_CNT_OFFS                                 (0x2090)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UC_PKT_CNT_RMSK                                 0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UC_PKT_CNT_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UC_PKT_CNT_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UC_PKT_CNT_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UC_PKT_CNT_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UC_PKT_CNT_CNT_BMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UC_PKT_CNT_CNT_SHFT                                      0

#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UC_ERR_PKT_CNT_ADDR(x)                          ((x) + 0x2098)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UC_ERR_PKT_CNT_OFFS                             (0x2098)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UC_ERR_PKT_CNT_RMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UC_ERR_PKT_CNT_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UC_ERR_PKT_CNT_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UC_ERR_PKT_CNT_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UC_ERR_PKT_CNT_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UC_ERR_PKT_CNT_CNT_BMSK                         0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UC_ERR_PKT_CNT_CNT_SHFT                                  0

#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_ERR_PKT_CNT_ADDR(x)                             ((x) + 0x20a0)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_ERR_PKT_CNT_OFFS                                (0x20a0)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_ERR_PKT_CNT_RMSK                                0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_ERR_PKT_CNT_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_ERR_PKT_CNT_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_ERR_PKT_CNT_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_ERR_PKT_CNT_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_ERR_PKT_CNT_CNT_BMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_ERR_PKT_CNT_CNT_SHFT                                     0

#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_PKT_CNT_n_ADDR(base,n)                          ((base) + 0X2100 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_PKT_CNT_n_OFFS(n)                               (0X2100 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_PKT_CNT_n_RMSK                                  0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_PKT_CNT_n_MAXn                                          11
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_PKT_CNT_n_INI(base,n)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_PKT_CNT_n_ADDR(base,n), HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_PKT_CNT_n_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_PKT_CNT_n_INMI(base,n,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_PKT_CNT_n_ADDR(base,n), mask)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_PKT_CNT_n_CNT_BMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_PKT_CNT_n_CNT_SHFT                                       0

#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_C2C_PKT_OVF_CNT_ADDR(x)                         ((x) + 0x2190)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_C2C_PKT_OVF_CNT_OFFS                            (0x2190)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_C2C_PKT_OVF_CNT_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_C2C_PKT_OVF_CNT_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_C2C_PKT_OVF_CNT_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_C2C_PKT_OVF_CNT_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_C2C_PKT_OVF_CNT_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_C2C_PKT_OVF_CNT_CNT_BMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_C2C_PKT_OVF_CNT_CNT_SHFT                                 0

#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_DMA_PKT_CNT_ADDR(x)                             ((x) + 0x2194)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_DMA_PKT_CNT_OFFS                                (0x2194)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_DMA_PKT_CNT_RMSK                                0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_DMA_PKT_CNT_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_DMA_PKT_CNT_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_DMA_PKT_CNT_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_DMA_PKT_CNT_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_DMA_PKT_CNT_CNT_BMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_DMA_PKT_CNT_CNT_SHFT                                     0

#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_UC_PKT_CNT_ADDR(x)                              ((x) + 0x2198)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_UC_PKT_CNT_OFFS                                 (0x2198)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_UC_PKT_CNT_RMSK                                 0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_UC_PKT_CNT_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_UC_PKT_CNT_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_UC_PKT_CNT_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_UC_PKT_CNT_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_UC_PKT_CNT_CNT_BMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_UC_PKT_CNT_CNT_SHFT                                      0

#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_PKT_CNT_n_ADDR(base,n)                         ((base) + 0X2200 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_PKT_CNT_n_OFFS(n)                              (0X2200 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_PKT_CNT_n_RMSK                                 0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_PKT_CNT_n_MAXn                                          2
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_PKT_CNT_n_INI(base,n)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_PKT_CNT_n_ADDR(base,n), HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_PKT_CNT_n_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_PKT_CNT_n_INMI(base,n,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_PKT_CNT_n_ADDR(base,n), mask)
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_PKT_CNT_n_CNT_BMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_PKT_CNT_n_CNT_SHFT                                      0

#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_DMA_PKT_CNT_ADDR(x)                            ((x) + 0x2230)
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_DMA_PKT_CNT_OFFS                               (0x2230)
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_DMA_PKT_CNT_RMSK                               0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_DMA_PKT_CNT_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_DMA_PKT_CNT_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_DMA_PKT_CNT_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_DMA_PKT_CNT_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_DMA_PKT_CNT_CNT_BMSK                           0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_DMA_PKT_CNT_CNT_SHFT                                    0

#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_ERR_PKT_CNT_ADDR(x)                            ((x) + 0x2234)
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_ERR_PKT_CNT_OFFS                               (0x2234)
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_ERR_PKT_CNT_RMSK                               0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_ERR_PKT_CNT_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_ERR_PKT_CNT_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_ERR_PKT_CNT_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_ERR_PKT_CNT_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_ERR_PKT_CNT_CNT_BMSK                           0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_ERR_PKT_CNT_CNT_SHFT                                    0

#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_PKT_CNT_n_ADDR(base,n)                         ((base) + 0X2260 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_PKT_CNT_n_OFFS(n)                              (0X2260 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_PKT_CNT_n_RMSK                                 0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_PKT_CNT_n_MAXn                                          2
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_PKT_CNT_n_INI(base,n)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_PKT_CNT_n_ADDR(base,n), HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_PKT_CNT_n_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_PKT_CNT_n_INMI(base,n,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_PKT_CNT_n_ADDR(base,n), mask)
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_PKT_CNT_n_CNT_BMSK                             0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_PKT_CNT_n_CNT_SHFT                                      0

#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_FH_PKT_OVF_CNT_ADDR(x)                         ((x) + 0x2290)
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_FH_PKT_OVF_CNT_OFFS                            (0x2290)
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_FH_PKT_OVF_CNT_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_FH_PKT_OVF_CNT_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_FH_PKT_OVF_CNT_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_FH_PKT_OVF_CNT_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_FH_PKT_OVF_CNT_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_FH_PKT_OVF_CNT_CNT_BMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_FH_PKT_OVF_CNT_CNT_SHFT                                 0

#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_DMA_PKT_CNT_ADDR(x)                            ((x) + 0x2294)
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_DMA_PKT_CNT_OFFS                               (0x2294)
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_DMA_PKT_CNT_RMSK                               0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_DMA_PKT_CNT_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_DMA_PKT_CNT_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_DMA_PKT_CNT_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_DMA_PKT_CNT_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_DMA_PKT_CNT_CNT_BMSK                           0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_DMA_PKT_CNT_CNT_SHFT                                    0

#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_C2C_PKT_DROP_CNT_ADDR(x)                        ((x) + 0x2300)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_C2C_PKT_DROP_CNT_OFFS                           (0x2300)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_C2C_PKT_DROP_CNT_RMSK                           0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_C2C_PKT_DROP_CNT_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_C2C_PKT_DROP_CNT_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_C2C_PKT_DROP_CNT_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_C2C_PKT_DROP_CNT_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_C2C_PKT_DROP_CNT_CNT_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_C2C_PKT_DROP_CNT_CNT_SHFT                                0

#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_FH_PKT_DROP_CNT_ADDR(x)                         ((x) + 0x2304)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_FH_PKT_DROP_CNT_OFFS                            (0x2304)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_FH_PKT_DROP_CNT_RMSK                            0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_FH_PKT_DROP_CNT_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_FH_PKT_DROP_CNT_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_FH_PKT_DROP_CNT_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_FH_PKT_DROP_CNT_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_FH_PKT_DROP_CNT_CNT_BMSK                        0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_FH_PKT_DROP_CNT_CNT_SHFT                                 0

#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_PKT_CNT_n_ADDR(base,n)                          ((base) + 0X2310 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_PKT_CNT_n_OFFS(n)                               (0X2310 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_PKT_CNT_n_RMSK                                  0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_PKT_CNT_n_MAXn                                           3
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_PKT_CNT_n_INI(base,n)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_PKT_CNT_n_ADDR(base,n), HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_PKT_CNT_n_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_PKT_CNT_n_INMI(base,n,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_PKT_CNT_n_ADDR(base,n), mask)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_PKT_CNT_n_CNT_BMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_PKT_CNT_n_CNT_SHFT                                       0

#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_PKT_CNT_n_ADDR(base,n)                          ((base) + 0X2320 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_PKT_CNT_n_OFFS(n)                               (0X2320 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_PKT_CNT_n_RMSK                                  0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_PKT_CNT_n_MAXn                                           3
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_PKT_CNT_n_INI(base,n)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_PKT_CNT_n_ADDR(base,n), HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_PKT_CNT_n_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_PKT_CNT_n_INMI(base,n,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_PKT_CNT_n_ADDR(base,n), mask)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_PKT_CNT_n_CNT_BMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_PKT_CNT_n_CNT_SHFT                                       0

#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_FH_PKT_CNT_n_ADDR(base,n)                       ((base) + 0X2330 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_FH_PKT_CNT_n_OFFS(n)                            (0X2330 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_FH_PKT_CNT_n_RMSK                               0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_FH_PKT_CNT_n_MAXn                                       11
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_FH_PKT_CNT_n_INI(base,n)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_FH_PKT_CNT_n_ADDR(base,n), HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_FH_PKT_CNT_n_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_FH_PKT_CNT_n_INMI(base,n,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_FH_PKT_CNT_n_ADDR(base,n), mask)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_FH_PKT_CNT_n_CNT_BMSK                           0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_FH_PKT_CNT_n_CNT_SHFT                                    0

#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_C2C_PKT_CNT_n_ADDR(base,n)                      ((base) + 0X2360 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_C2C_PKT_CNT_n_OFFS(n)                           (0X2360 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_C2C_PKT_CNT_n_RMSK                              0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_C2C_PKT_CNT_n_MAXn                                       2
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_C2C_PKT_CNT_n_INI(base,n)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_C2C_PKT_CNT_n_ADDR(base,n), HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_C2C_PKT_CNT_n_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_C2C_PKT_CNT_n_INMI(base,n,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_C2C_PKT_CNT_n_ADDR(base,n), mask)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_C2C_PKT_CNT_n_CNT_BMSK                          0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_C2C_PKT_CNT_n_CNT_SHFT                                   0

#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_ADDR(x)                        ((x) + 0x2370)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_OFFS                           (0x2370)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_RMSK                           0x3fffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_OCRX_FH_2_CNT_BMSK             0x3ff00000
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_OCRX_FH_2_CNT_SHFT                     20
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_OCRX_FH_1_CNT_BMSK                0xffc00
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_OCRX_FH_1_CNT_SHFT                     10
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_OCRX_FH_0_CNT_BMSK                  0x3ff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT_OCRX_FH_0_CNT_SHFT                      0

#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n_ADDR(base,n)              ((base) + 0X2374 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n_OFFS(n)                   (0X2374 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n_RMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n_MAXn                               2
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n_INI(base,n)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n_ADDR(base,n), HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n_INMI(base,n,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n_ADDR(base,n), mask)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n_INFO_BMSK                 0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n_INFO_SHFT                          0

#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n_ADDR(base,n)              ((base) + 0X2384 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n_OFFS(n)                   (0X2384 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n_RMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n_MAXn                               2
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n_INI(base,n)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n_ADDR(base,n), HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n_INMI(base,n,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n_ADDR(base,n), mask)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n_INFO_BMSK                 0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n_INFO_SHFT                          0

#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_ADDR(x)                        ((x) + 0x23a0)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_OFFS                           (0x23a0)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_RMSK                           0x3fffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_FHRX_2_CNT_BMSK                0x3ff00000
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_FHRX_2_CNT_SHFT                        20
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_FHRX_1_CNT_BMSK                   0xffc00
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_FHRX_1_CNT_SHFT                        10
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_FHRX_0_CNT_BMSK                     0x3ff
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT_FHRX_0_CNT_SHFT                         0

#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n_ADDR(base,n)              ((base) + 0X23A4 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n_OFFS(n)                   (0X23A4 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n_RMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n_MAXn                               2
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n_INI(base,n)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n_ADDR(base,n), HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n_INMI(base,n,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n_ADDR(base,n), mask)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n_INFO_BMSK                 0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n_INFO_SHFT                          0

#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n_ADDR(base,n)              ((base) + 0X23B4 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n_OFFS(n)                   (0X23B4 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n_RMSK                      0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n_MAXn                               2
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n_INI(base,n)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n_ADDR(base,n), HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n_INMI(base,n,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n_ADDR(base,n), mask)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n_INFO_BMSK                 0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n_INFO_SHFT                          0

#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_ADDR(x)                       ((x) + 0x23d0)
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_OFFS                          (0x23d0)
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_RMSK                          0x3fffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_C2CRX_2_CNT_BMSK              0x3ff00000
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_C2CRX_2_CNT_SHFT                      20
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_C2CRX_1_CNT_BMSK                 0xffc00
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_C2CRX_1_CNT_SHFT                      10
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_C2CRX_0_CNT_BMSK                   0x3ff
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT_C2CRX_0_CNT_SHFT                       0

#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_1_n_ADDR(base,n)             ((base) + 0X23D4 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_1_n_OFFS(n)                  (0X23D4 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_1_n_RMSK                     0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_1_n_MAXn                              2
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_1_n_INI(base,n)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_1_n_ADDR(base,n), HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_1_n_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_1_n_INMI(base,n,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_1_n_ADDR(base,n), mask)
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_1_n_INFO_BMSK                0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_1_n_INFO_SHFT                         0

#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_2_n_ADDR(base,n)             ((base) + 0X23E4 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_2_n_OFFS(n)                  (0X23E4 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_2_n_RMSK                     0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_2_n_MAXn                              2
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_2_n_INI(base,n)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_2_n_ADDR(base,n), HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_2_n_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_2_n_INMI(base,n,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_2_n_ADDR(base,n), mask)
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_2_n_INFO_BMSK                0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_2_n_INFO_SHFT                         0

#define HWIO_ECPRI_XBAR_XBAR_DBG_TESTBUS_SELECT_ADDR(x)                               ((x) + 0x2400)
#define HWIO_ECPRI_XBAR_XBAR_DBG_TESTBUS_SELECT_OFFS                                  (0x2400)
#define HWIO_ECPRI_XBAR_XBAR_DBG_TESTBUS_SELECT_RMSK                                      0xffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_TESTBUS_SELECT_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_DBG_TESTBUS_SELECT_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_TESTBUS_SELECT_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_TESTBUS_SELECT_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_DBG_TESTBUS_SELECT_OUT(x, v)            \
	out_dword(HWIO_ECPRI_XBAR_XBAR_DBG_TESTBUS_SELECT_ADDR(x),v)
#define HWIO_ECPRI_XBAR_XBAR_DBG_TESTBUS_SELECT_OUTM(x,m,v) \
	out_dword_masked_ns(HWIO_ECPRI_XBAR_XBAR_DBG_TESTBUS_SELECT_ADDR(x),m,v,HWIO_ECPRI_XBAR_XBAR_DBG_TESTBUS_SELECT_IN(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_TESTBUS_SELECT_ORAN_TESTBUS_SEL_BMSK                     0xff00
#define HWIO_ECPRI_XBAR_XBAR_DBG_TESTBUS_SELECT_ORAN_TESTBUS_SEL_SHFT                          8
#define HWIO_ECPRI_XBAR_XBAR_DBG_TESTBUS_SELECT_XBAR_TESTBUS_SEL_BMSK                       0xff
#define HWIO_ECPRI_XBAR_XBAR_DBG_TESTBUS_SELECT_XBAR_TESTBUS_SEL_SHFT                          0

#define HWIO_ECPRI_XBAR_XBAR_DBG_XBAR_TESTBUS_ADDR(x)                                 ((x) + 0x2404)
#define HWIO_ECPRI_XBAR_XBAR_DBG_XBAR_TESTBUS_OFFS                                    (0x2404)
#define HWIO_ECPRI_XBAR_XBAR_DBG_XBAR_TESTBUS_RMSK                                    0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_XBAR_TESTBUS_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_DBG_XBAR_TESTBUS_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_XBAR_TESTBUS_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_XBAR_TESTBUS_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_DBG_XBAR_TESTBUS_XBAR_TESTBUS_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_XBAR_TESTBUS_XBAR_TESTBUS_SHFT                                0

#define HWIO_ECPRI_XBAR_XBAR_DBG_ORAN_TESTBUS_ADDR(x)                                 ((x) + 0x2408)
#define HWIO_ECPRI_XBAR_XBAR_DBG_ORAN_TESTBUS_OFFS                                    (0x2408)
#define HWIO_ECPRI_XBAR_XBAR_DBG_ORAN_TESTBUS_RMSK                                    0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_ORAN_TESTBUS_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_DBG_ORAN_TESTBUS_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_ORAN_TESTBUS_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_ORAN_TESTBUS_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_DBG_ORAN_TESTBUS_ORAN_TESTBUS_BMSK                       0xffffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_ORAN_TESTBUS_ORAN_TESTBUS_SHFT                                0

#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_ADDR(base,n)                ((base) + 0X2800 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_OFFS(n)                     (0X2800 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_RMSK                        0x3fffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_MAXn                                 3
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_INI(base,n)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_ADDR(base,n), HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_INMI(base,n,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_ADDR(base,n), mask)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_FH2_BMSK                    0x3ff00000
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_FH2_SHFT                            20
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_FH1_BMSK                       0xffc00
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_FH1_SHFT                            10
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_FH0_BMSK                         0x3ff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n_FH0_SHFT                             0

#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_ADDR(base,n)               ((base) + 0X2810 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_OFFS(n)                    (0X2810 + (0x4*(n)))
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_RMSK                       0x3fffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_MAXn                                3
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_INI(base,n)                \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_ADDR(base,n), HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_RMSK)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_INMI(base,n,mask)        \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_ADDR(base,n), mask)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_C2C2_BMSK                  0x3ff00000
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_C2C2_SHFT                          20
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_C2C1_BMSK                     0xffc00
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_C2C1_SHFT                          10
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_C2C0_BMSK                       0x3ff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n_C2C0_SHFT                           0

#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK_ADDR(x)                      ((x) + 0x2820)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK_OFFS                         (0x2820)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK_RMSK                            0xfffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK_CC1_BMSK                        0xffc00
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK_CC1_SHFT                             10
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK_CC0_BMSK                          0x3ff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK_CC0_SHFT                              0

#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK_ADDR(x)                      ((x) + 0x2824)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK_OFFS                         (0x2824)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK_RMSK                            0xfffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK_CC3_BMSK                        0xffc00
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK_CC3_SHFT                             10
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK_CC2_BMSK                          0x3ff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK_CC2_SHFT                              0

#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_ADDR(x)                      ((x) + 0x2834)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_OFFS                         (0x2834)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_RMSK                         0x3fffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_C2C2_BMSK                    0x3ff00000
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_C2C2_SHFT                            20
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_C2C1_BMSK                       0xffc00
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_C2C1_SHFT                            10
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_C2C0_BMSK                         0x3ff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK_C2C0_SHFT                             0

#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_ADDR(x)                       ((x) + 0x2838)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_OFFS                          (0x2838)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_RMSK                          0x3fffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_FH2_BMSK                      0x3ff00000
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_FH2_SHFT                              20
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_FH1_BMSK                         0xffc00
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_FH1_SHFT                              10
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_FH0_BMSK                           0x3ff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCRX_FH_BUFF_WATERMARK_FH0_SHFT                               0

#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_ADDR(x)                      ((x) + 0x283c)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_OFFS                         (0x283c)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_RMSK                         0x3fffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_FH2_BMSK                     0x3ff00000
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_FH2_SHFT                             20
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_FH1_BMSK                        0xffc00
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_FH1_SHFT                             10
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_FH0_BMSK                          0x3ff
#define HWIO_ECPRI_XBAR_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK_FH0_SHFT                              0

#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_ADDR(x)                      ((x) + 0x2840)
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_OFFS                         (0x2840)
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_RMSK                         0x3fffffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_C2C2_BMSK                    0x3ff00000
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_C2C2_SHFT                            20
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_C2C1_BMSK                       0xffc00
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_C2C1_SHFT                            10
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_C2C0_BMSK                         0x3ff
#define HWIO_ECPRI_XBAR_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK_C2C0_SHFT                             0

#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK_ADDR(x)                   ((x) + 0x2850)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK_OFFS                      (0x2850)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK_RMSK                         0xfffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK_CC1_BMSK                     0xffc00
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK_CC1_SHFT                          10
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK_CC0_BMSK                       0x3ff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK_CC0_SHFT                           0

#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK_ADDR(x)                   ((x) + 0x2854)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK_OFFS                      (0x2854)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK_RMSK                         0xfffff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK_CC3_BMSK                     0xffc00
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK_CC3_SHFT                          10
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK_CC2_BMSK                       0x3ff
#define HWIO_ECPRI_XBAR_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK_CC2_SHFT                           0

#define HWIO_ECPRI_XBAR_XBAR_FH_STATUS_SHADOW_ADDR(x)                                 ((x) + 0x4000)
#define HWIO_ECPRI_XBAR_XBAR_FH_STATUS_SHADOW_OFFS                                    (0x4000)
#define HWIO_ECPRI_XBAR_XBAR_FH_STATUS_SHADOW_RMSK                                           0x7
#define HWIO_ECPRI_XBAR_XBAR_FH_STATUS_SHADOW_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_FH_STATUS_SHADOW_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_FH_STATUS_SHADOW_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_FH_STATUS_SHADOW_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_FH_STATUS_SHADOW_TX_C2C_OVERFLOW_BMSK                           0x7
#define HWIO_ECPRI_XBAR_XBAR_FH_STATUS_SHADOW_TX_C2C_OVERFLOW_SHFT                             0

#define HWIO_ECPRI_XBAR_XBAR_C2C_STATUS_SHADOW_ADDR(x)                                ((x) + 0x4004)
#define HWIO_ECPRI_XBAR_XBAR_C2C_STATUS_SHADOW_OFFS                                   (0x4004)
#define HWIO_ECPRI_XBAR_XBAR_C2C_STATUS_SHADOW_RMSK                                          0x7
#define HWIO_ECPRI_XBAR_XBAR_C2C_STATUS_SHADOW_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_C2C_STATUS_SHADOW_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_C2C_STATUS_SHADOW_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_C2C_STATUS_SHADOW_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_C2C_STATUS_SHADOW_TX_FH_OVERFLOW_BMSK                           0x7
#define HWIO_ECPRI_XBAR_XBAR_C2C_STATUS_SHADOW_TX_FH_OVERFLOW_SHFT                             0

#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_SHADOW_ADDR(x)                               ((x) + 0x400c)
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_SHADOW_OFFS                                  (0x400c)
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_SHADOW_RMSK                                       0xfff
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_SHADOW_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_SHADOW_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_SHADOW_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_SHADOW_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_SHADOW_TX_C2C_OVERFLOW_BMSK                       0xe00
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_SHADOW_TX_C2C_OVERFLOW_SHFT                           9
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_SHADOW_TX_FH_OVERFLOW_BMSK                        0x1c0
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_SHADOW_TX_FH_OVERFLOW_SHFT                            6
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_SHADOW_TX_C2C_DROP_BMSK                            0x38
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_SHADOW_TX_C2C_DROP_SHFT                               3
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_SHADOW_TX_FH_DROP_BMSK                              0x7
#define HWIO_ECPRI_XBAR_XBAR_OCTX_STATUS_SHADOW_TX_FH_DROP_SHFT                                0

#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_SHADOW_ADDR(x)                            ((x) + 0x4010)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_SHADOW_OFFS                               (0x4010)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_SHADOW_RMSK                                    0x3ff
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_SHADOW_IN(x)            \
	in_dword(HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_SHADOW_ADDR(x))
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_SHADOW_INM(x, m)            \
	in_dword_masked(HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_SHADOW_ADDR(x), m)
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_SHADOW_UC_PKT_DROP_BMSK                        0x380
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_SHADOW_UC_PKT_DROP_SHFT                            7
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_SHADOW_UC_PKT_ERR_BMSK                          0x70
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_SHADOW_UC_PKT_ERR_SHFT                             4
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_SHADOW_UC_PKT_OVERFLOW_BMSK                      0xe
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_SHADOW_UC_PKT_OVERFLOW_SHFT                        1
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_SHADOW_UC_PKT_PENDING_BMSK                       0x1
#define HWIO_ECPRI_XBAR_XBAR_UC_FHRX_STATUS_SHADOW_UC_PKT_PENDING_SHFT                         0


#endif /* __ECPRISS_XBAR_H__ */
