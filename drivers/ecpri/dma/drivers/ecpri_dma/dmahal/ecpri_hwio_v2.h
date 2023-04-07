/*
 * SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */
#ifndef __ECPRI_HWIO_V2_H__
#define __ECPRI_HWIO_V2_H__
/*
===========================================================================
*/
/**
    @file ecpri_hwio.h
    @brief Auto-generated HWIO interface include file.

    This file contains HWIO register definitions for the following modules:
        ECPRI_DMA.*
'Include' filters applied: <none>
'Exclude' filters applied: RESERVED DUMMY

    Attribute definitions for the HWIO_*_ATTR macros are as follows:
        0x0: Command register
        0x1: Read-Only
        0x2: Write-Only
        0x3: Read/Write
*/

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_DMA Bases
 *--------------------------------------------------------------------------*/
 /*	ECPRI_DMA_REG_BASE_OFFS is 0x00300000 but DMA driver already maps memory
     directly to this offset, therefor HAL shouldn't add it again */
#define ECPRI_DMA_REG_BASE   (ECPRI_WRAPPER_BASE)
#define ECPRI_DMA_REG_BASE_SIZE 0x40000
#define ECPRI_DMA_REG_BASE_USED 0x0
#define ECPRI_DMA_REG_BASE_PHYS (ECPRI_WRAPPER_BASE_PHYS)
#define ECPRI_DMA_REG_BASE_OFFS (0x0)

#define ECPRI_DMA_NON_SECURED_REG_BASE                                                                                   (ECPRI_WRAPPER_BASE      + 0x0)
#define ECPRI_DMA_NON_SECURED_REG_BASE_SIZE                                                                              0x20000
#define ECPRI_DMA_NON_SECURED_REG_BASE_USED                                                                              0x13008
#define ECPRI_DMA_NON_SECURED_REG_BASE_PHYS                                                                              (ECPRI_WRAPPER_BASE_PHYS + 0x0)
#define ECPRI_DMA_NON_SECURED_REG_BASE_OFFS                                                                              (0x0)

#define ECPRI_DMA_EES_REG_BASE                                                               (ECPRI_WRAPPER_BASE      + 0x00020000)
#define ECPRI_DMA_EES_REG_BASE_SIZE                                                          0x2000
#define ECPRI_DMA_EES_REG_BASE_USED                                                          0x1020
#define ECPRI_DMA_EES_REG_BASE_PHYS                                                          (ECPRI_WRAPPER_BASE_PHYS + 0x00020000)
#define ECPRI_DMA_EES_REG_BASE_OFFS                                                          (0x00020000)

#define ECPRI_DMA_DEBUG_REG_BASE                                       (ECPRI_WRAPPER_BASE      + 0x003c000)
#define ECPRI_DMA_DEBUG_REG_BASE_PHYS                                  (ECPRI_WRAPPER_BASE_PHYS + 0x003c000)
#define ECPRI_DMA_DEBUG_REG_BASE_OFFS                                  (0x0003c000)

#define ECPRI_DMA_NS_RESTRICTED_REG_BASE                                            (ECPRI_WRAPPER_BASE      + 0x00038000)
#define ECPRI_DMA_NS_RESTRICTED_REG_BASE_SIZE                                       0x4000
#define ECPRI_DMA_NS_RESTRICTED_REG_BASE_USED                                       0x2928
#define ECPRI_DMA_NS_RESTRICTED_REG_BASE_PHYS                                       (ECPRI_WRAPPER_BASE_PHYS + 0x00038000)
#define ECPRI_DMA_NS_RESTRICTED_REG_BASE_OFFS                                       0x00038000

#define ECPRI_DMA_SECURED_REG_BASE                                               (ECPRI_WRAPPER_BASE      + 0x00030000)
#define ECPRI_DMA_SECURED_REG_BASE_SIZE                                          0x8000
#define ECPRI_DMA_SECURED_REG_BASE_USED                                          0x4098
#define ECPRI_DMA_SECURED_REG_BASE_PHYS                                          (ECPRI_WRAPPER_BASE_PHYS + 0x00030000)
#define ECPRI_DMA_SECURED_REG_BASE_OFFS                                          0x00330000

#define ECPRI_DMA_RAM_REG_BASE                                            (ECPRI_WRAPPER_BASE      + 0x00040000)
#define ECPRI_DMA_RAM_REG_BASE_SIZE                                       0x10000
#define ECPRI_DMA_RAM_REG_BASE_USED                                       0xdffc
#define ECPRI_DMA_RAM_REG_BASE_PHYS                                       (ECPRI_WRAPPER_BASE_PHYS + 0x00040000)
#define ECPRI_DMA_RAM_REG_BASE_OFFS                                       (0x00040000)

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_DMA
 *--------------------------------------------------------------------------*/

#define HWIO_ECPRI_HW_PARAMS_0_V2_ADDR                                                                                  (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x0)
#define HWIO_ECPRI_HW_PARAMS_0_V2_PHYS                                                                                  (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x0)
#define HWIO_ECPRI_HW_PARAMS_0_V2_OFFS                                                                                  (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x0)
#define HWIO_ECPRI_HW_PARAMS_0_V2_RMSK                                                                                   0x1ffffff
#define HWIO_ECPRI_HW_PARAMS_0_V2_ATTR                                                                                               0x1
#define HWIO_ECPRI_HW_PARAMS_0_V2_IN                    \
                in_dword(HWIO_ECPRI_HW_PARAMS_0_V2_ADDR)
#define HWIO_ECPRI_HW_PARAMS_0_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_HW_PARAMS_0_V2_ADDR, m)
#define HWIO_ECPRI_HW_PARAMS_0_V2_UC_ENABLE_BMSK                                                                         0x1000000
#define HWIO_ECPRI_HW_PARAMS_0_V2_UC_ENABLE_SHFT                                                                                24
#define HWIO_ECPRI_HW_PARAMS_0_V2_DST_CHANNEL_N_BMSK                                                                      0xff0000
#define HWIO_ECPRI_HW_PARAMS_0_V2_DST_CHANNEL_N_SHFT                                                                            16
#define HWIO_ECPRI_HW_PARAMS_0_V2_SRC_CHANNEL_N_BMSK                                                                        0xff00
#define HWIO_ECPRI_HW_PARAMS_0_V2_SRC_CHANNEL_N_SHFT                                                                             8
#define HWIO_ECPRI_HW_PARAMS_0_V2_TOTAL_CHANNELS_N_BMSK                                                                       0xff
#define HWIO_ECPRI_HW_PARAMS_0_V2_TOTAL_CHANNELS_N_SHFT                                                                          0

#define HWIO_ECPRI_HW_PARAMS_1_ADDR                                                                                  (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x4)
#define HWIO_ECPRI_HW_PARAMS_1_PHYS                                                                                  (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x4)
#define HWIO_ECPRI_HW_PARAMS_1_OFFS                                                                                  (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x4)
#define HWIO_ECPRI_HW_PARAMS_1_RMSK                                                                                   0xfff7f7f
#define HWIO_ECPRI_HW_PARAMS_1_ATTR                                                                                               0x1
#define HWIO_ECPRI_HW_PARAMS_1_IN                    \
                in_dword(HWIO_ECPRI_HW_PARAMS_1_ADDR)
#define HWIO_ECPRI_HW_PARAMS_1_INM(m)            \
                in_dword_masked(HWIO_ECPRI_HW_PARAMS_1_ADDR, m)
#define HWIO_ECPRI_HW_PARAMS_1_NFAPI_REASSEMBLY_CTX_NUM_BMSK                                                          0xff00000
#define HWIO_ECPRI_HW_PARAMS_1_NFAPI_REASSEMBLY_CTX_NUM_SHFT                                                                 20
#define HWIO_ECPRI_HW_PARAMS_1_GSI_EES_N_BMSK                                                                           0xf0000
#define HWIO_ECPRI_HW_PARAMS_1_GSI_EES_N_SHFT                                                                                16
#define HWIO_ECPRI_HW_PARAMS_1_QMB_MAX_OUTST_RD_BMSK                                                                     0x7f00
#define HWIO_ECPRI_HW_PARAMS_1_QMB_MAX_OUTST_RD_SHFT                                                                          8
#define HWIO_ECPRI_HW_PARAMS_1_QMB_MAX_OUTST_WR_BMSK                                                                       0x7f
#define HWIO_ECPRI_HW_PARAMS_1_QMB_MAX_OUTST_WR_SHFT                                                                          0

#define HWIO_ECPRI_HW_PARAMS_2_V2_ADDR                                                                                  (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x8)
#define HWIO_ECPRI_HW_PARAMS_2_V2_PHYS                                                                                  (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x8)
#define HWIO_ECPRI_HW_PARAMS_2_V2_OFFS                                                                                  (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x8)
#define HWIO_ECPRI_HW_PARAMS_2_V2_RMSK                                                                                       0xfff
#define HWIO_ECPRI_HW_PARAMS_2_V2_ATTR                                                                                               0x1
#define HWIO_ECPRI_HW_PARAMS_2_V2_IN                    \
                in_dword(HWIO_ECPRI_HW_PARAMS_2_V2_ADDR)
#define HWIO_ECPRI_HW_PARAMS_2_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_HW_PARAMS_2_V2_ADDR, m)
#define HWIO_ECPRI_HW_PARAMS_2_V2_TLV_FIFO_SIZE_BMSK                                                                         0xfff
#define HWIO_ECPRI_HW_PARAMS_2_V2_TLV_FIFO_SIZE_SHFT                                                                             0


/*----------------------------------------------------------------------------
 * MODULE: ECPRI_DMA_RAM
 *--------------------------------------------------------------------------*/

#define HWIO_ECPRI_RAM_FIFO_CONTENT_LINE_l_WORD_n_ADDR(l,n)           (ECPRI_DMA_RAM_REG_BASE      + 0X0 + (0x10*(l)) + (0x4*(n)))
#define HWIO_ECPRI_RAM_FIFO_CONTENT_LINE_l_WORD_n_PHYS(l,n)           (ECPRI_DMA_RAM_REG_BASE_PHYS + 0X0 + (0x10*(l)) + (0x4*(n)))
#define HWIO_ECPRI_RAM_FIFO_CONTENT_LINE_l_WORD_n_OFFS(l,n)           (ECPRI_DMA_RAM_REG_BASE_OFFS + 0X0 + (0x10*(l)) + (0x4*(n)))
#define HWIO_ECPRI_RAM_FIFO_CONTENT_LINE_l_WORD_n_RMSK                0xffffffff
#define HWIO_ECPRI_RAM_FIFO_CONTENT_LINE_l_WORD_n_MAXl                      3583
#define HWIO_ECPRI_RAM_FIFO_CONTENT_LINE_l_WORD_n_MAXn                         3
#define HWIO_ECPRI_RAM_FIFO_CONTENT_LINE_l_WORD_n_ATTR                             0x1
#define HWIO_ECPRI_RAM_FIFO_CONTENT_LINE_l_WORD_n_INI2(l,n)                \
                in_dword_masked(HWIO_ECPRI_RAM_FIFO_CONTENT_LINE_l_WORD_n_ADDR(l,n), HWIO_ECPRI_RAM_FIFO_CONTENT_LINE_l_WORD_n_RMSK)
#define HWIO_ECPRI_RAM_FIFO_CONTENT_LINE_l_WORD_n_INMI2(l,n,mask)        \
                in_dword_masked(HWIO_ECPRI_RAM_FIFO_CONTENT_LINE_l_WORD_n_ADDR(l,n), mask)
#define HWIO_ECPRI_RAM_FIFO_CONTENT_LINE_l_WORD_n_VALUE_BMSK          0xffffffff
#define HWIO_ECPRI_RAM_FIFO_CONTENT_LINE_l_WORD_n_VALUE_SHFT                   0


#define HWIO_ECPRI_GEN_CFG_V2_ADDR                                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x1c)
#define HWIO_ECPRI_GEN_CFG_V2_PHYS                                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x1c)
#define HWIO_ECPRI_GEN_CFG_V2_OFFS                                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x1c)
#define HWIO_ECPRI_GEN_CFG_V2_RMSK                                                                                             0x7
#define HWIO_ECPRI_GEN_CFG_V2_ATTR                                                                                                   0x3
#define HWIO_ECPRI_GEN_CFG_V2_IN                    \
                in_dword(HWIO_ECPRI_GEN_CFG_V2_ADDR)
#define HWIO_ECPRI_GEN_CFG_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_GEN_CFG_V2_ADDR, m)
#define HWIO_ECPRI_GEN_CFG_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_GEN_CFG_V2_ADDR,v)
#define HWIO_ECPRI_GEN_CFG_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_GEN_CFG_V2_ADDR,m,v,HWIO_ECPRI_GEN_CFG_V2_IN)
#define HWIO_ECPRI_GEN_CFG_V2_ACK_MNGR_ACK_ON_0_LEN_BMSK                                                                       0x4
#define HWIO_ECPRI_GEN_CFG_V2_ACK_MNGR_ACK_ON_0_LEN_SHFT                                                                         2
#define HWIO_ECPRI_GEN_CFG_V2_GEN_QMB_DYNAMIC_ASIZE_BMSK                                                                       0x2
#define HWIO_ECPRI_GEN_CFG_V2_GEN_QMB_DYNAMIC_ASIZE_SHFT                                                                         1
#define HWIO_ECPRI_GEN_CFG_V2_OUT_OF_BUF_STOP_RESET_MASK_ENABLE_BMSK                                                           0x1
#define HWIO_ECPRI_GEN_CFG_V2_OUT_OF_BUF_STOP_RESET_MASK_ENABLE_SHFT                                                             0

#define HWIO_ECPRI_CLKON_CFG_V2_ADDR                                                                                    (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x20)
#define HWIO_ECPRI_CLKON_CFG_V2_PHYS                                                                                    (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x20)
#define HWIO_ECPRI_CLKON_CFG_V2_OFFS                                                                                    (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x20)
#define HWIO_ECPRI_CLKON_CFG_V2_RMSK                                                                                          0x37
#define HWIO_ECPRI_CLKON_CFG_V2_ATTR                                                                                                 0x3
#define HWIO_ECPRI_CLKON_CFG_V2_IN                    \
                in_dword(HWIO_ECPRI_CLKON_CFG_V2_ADDR)
#define HWIO_ECPRI_CLKON_CFG_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_CLKON_CFG_V2_ADDR, m)
#define HWIO_ECPRI_CLKON_CFG_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_CLKON_CFG_V2_ADDR,v)
#define HWIO_ECPRI_CLKON_CFG_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_CLKON_CFG_V2_ADDR,m,v,HWIO_ECPRI_CLKON_CFG_V2_IN)
#define HWIO_ECPRI_CLKON_CFG_V2_CGC_OPEN_DMA_V2_BMSK                                                                             0x20
#define HWIO_ECPRI_CLKON_CFG_V2_CGC_OPEN_DMA_V2_SHFT                                                                                5
#define HWIO_ECPRI_CLKON_CFG_V2_CGC_OPEN_NSO_BMSK                                                                             0x10
#define HWIO_ECPRI_CLKON_CFG_V2_CGC_OPEN_NSO_SHFT                                                                                4
#define HWIO_ECPRI_CLKON_CFG_V2_CGC_OPEN_NRO_BMSK                                                                              0x4
#define HWIO_ECPRI_CLKON_CFG_V2_CGC_OPEN_NRO_SHFT                                                                                2
#define HWIO_ECPRI_CLKON_CFG_V2_CGC_OPEN_ACK_MANAGER_BMSK                                                                      0x2
#define HWIO_ECPRI_CLKON_CFG_V2_CGC_OPEN_ACK_MANAGER_SHFT                                                                        1
#define HWIO_ECPRI_CLKON_CFG_V2_CGC_OPEN_GSI_IF_BMSK                                                                           0x1
#define HWIO_ECPRI_CLKON_CFG_V2_CGC_OPEN_GSI_IF_SHFT                                                                             0

#define HWIO_ECPRI_QMB_CFG_V2_ADDR                                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x24)
#define HWIO_ECPRI_QMB_CFG_V2_PHYS                                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x24)
#define HWIO_ECPRI_QMB_CFG_V2_OFFS                                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x24)
#define HWIO_ECPRI_QMB_CFG_V2_RMSK                                                                                       0xfffffff
#define HWIO_ECPRI_QMB_CFG_V2_ATTR                                                                                                   0x3
#define HWIO_ECPRI_QMB_CFG_V2_IN                    \
                in_dword(HWIO_ECPRI_QMB_CFG_V2_ADDR)
#define HWIO_ECPRI_QMB_CFG_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_QMB_CFG_V2_ADDR, m)
#define HWIO_ECPRI_QMB_CFG_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_QMB_CFG_V2_ADDR,v)
#define HWIO_ECPRI_QMB_CFG_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_QMB_CFG_V2_ADDR,m,v,HWIO_ECPRI_QMB_CFG_V2_IN)
#define HWIO_ECPRI_QMB_CFG_V2_READ_BEATS_LIMIT_BMSK                                                                      0xfff0000
#define HWIO_ECPRI_QMB_CFG_V2_READ_BEATS_LIMIT_SHFT                                                                             16
#define HWIO_ECPRI_QMB_CFG_V2_READ_OT_LIMIT_BMSK                                                                            0xff00
#define HWIO_ECPRI_QMB_CFG_V2_READ_OT_LIMIT_SHFT                                                                                 8
#define HWIO_ECPRI_QMB_CFG_V2_WRITE_OT_LIMIT_BMSK                                                                             0xff
#define HWIO_ECPRI_QMB_CFG_V2_WRITE_OT_LIMIT_SHFT                                                                                0

#define HWIO_ECPRI_QMB_0_STATUS_V2_ADDR                                                                                 (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x28)
#define HWIO_ECPRI_QMB_0_STATUS_V2_PHYS                                                                                 (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x28)
#define HWIO_ECPRI_QMB_0_STATUS_V2_OFFS                                                                                 (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x28)
#define HWIO_ECPRI_QMB_0_STATUS_V2_RMSK                                                                                 0x1fffffff
#define HWIO_ECPRI_QMB_0_STATUS_V2_ATTR                                                                                              0x1
#define HWIO_ECPRI_QMB_0_STATUS_V2_IN                    \
                in_dword(HWIO_ECPRI_QMB_0_STATUS_V2_ADDR)
#define HWIO_ECPRI_QMB_0_STATUS_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_QMB_0_STATUS_V2_ADDR, m)
#define HWIO_ECPRI_QMB_0_STATUS_V2_BUSY_BMSK                                                                            0x10000000
#define HWIO_ECPRI_QMB_0_STATUS_V2_BUSY_SHFT                                                                                    28
#define HWIO_ECPRI_QMB_0_STATUS_V2_READ_BEATS_BMSK                                                                       0xfff0000
#define HWIO_ECPRI_QMB_0_STATUS_V2_READ_BEATS_SHFT                                                                              16
#define HWIO_ECPRI_QMB_0_STATUS_V2_READ_OUTS_BMSK                                                                           0xff00
#define HWIO_ECPRI_QMB_0_STATUS_V2_READ_OUTS_SHFT                                                                                8
#define HWIO_ECPRI_QMB_0_STATUS_V2_WRITE_OUTS_BMSK                                                                            0xff
#define HWIO_ECPRI_QMB_0_STATUS_V2_WRITE_OUTS_SHFT                                                                               0

#define HWIO_ECPRI_QMB_1_STATUS_V2_ADDR                                                                                 (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x2c)
#define HWIO_ECPRI_QMB_1_STATUS_V2_PHYS                                                                                 (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x2c)
#define HWIO_ECPRI_QMB_1_STATUS_V2_OFFS                                                                                 (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x2c)
#define HWIO_ECPRI_QMB_1_STATUS_V2_RMSK                                                                                 0x1fffffff
#define HWIO_ECPRI_QMB_1_STATUS_V2_ATTR                                                                                              0x1
#define HWIO_ECPRI_QMB_1_STATUS_V2_IN                    \
                in_dword(HWIO_ECPRI_QMB_1_STATUS_V2_ADDR)
#define HWIO_ECPRI_QMB_1_STATUS_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_QMB_1_STATUS_V2_ADDR, m)
#define HWIO_ECPRI_QMB_1_STATUS_V2_BUSY_BMSK                                                                            0x10000000
#define HWIO_ECPRI_QMB_1_STATUS_V2_BUSY_SHFT                                                                                    28
#define HWIO_ECPRI_QMB_1_STATUS_V2_READ_BEATS_BMSK                                                                       0xfff0000
#define HWIO_ECPRI_QMB_1_STATUS_V2_READ_BEATS_SHFT                                                                              16
#define HWIO_ECPRI_QMB_1_STATUS_V2_READ_OUTS_BMSK                                                                           0xff00
#define HWIO_ECPRI_QMB_1_STATUS_V2_READ_OUTS_SHFT                                                                                8
#define HWIO_ECPRI_QMB_1_STATUS_V2_WRITE_OUTS_BMSK                                                                            0xff
#define HWIO_ECPRI_QMB_1_STATUS_V2_WRITE_OUTS_SHFT                                                                               0

#define HWIO_ECPRI_AOS_CFG_V2_ADDR                                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x30)
#define HWIO_ECPRI_AOS_CFG_V2_PHYS                                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x30)
#define HWIO_ECPRI_AOS_CFG_V2_OFFS                                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x30)
#define HWIO_ECPRI_AOS_CFG_V2_RMSK                                                                                             0x1
#define HWIO_ECPRI_AOS_CFG_V2_ATTR                                                                                                   0x3
#define HWIO_ECPRI_AOS_CFG_V2_IN                    \
                in_dword(HWIO_ECPRI_AOS_CFG_V2_ADDR)
#define HWIO_ECPRI_AOS_CFG_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_AOS_CFG_V2_ADDR, m)
#define HWIO_ECPRI_AOS_CFG_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_AOS_CFG_V2_ADDR,v)
#define HWIO_ECPRI_AOS_CFG_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_AOS_CFG_V2_ADDR,m,v,HWIO_ECPRI_AOS_CFG_V2_IN)
#define HWIO_ECPRI_AOS_CFG_V2_TX_RX_PRIORITY_BMSK                                                                              0x1
#define HWIO_ECPRI_AOS_CFG_V2_TX_RX_PRIORITY_SHFT                                                                                0

#define HWIO_ECPRI_TIMERS_XO_CLK_DIV_CFG_V2_ADDR                                                                        (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x34)
#define HWIO_ECPRI_TIMERS_XO_CLK_DIV_CFG_V2_PHYS                                                                        (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x34)
#define HWIO_ECPRI_TIMERS_XO_CLK_DIV_CFG_V2_OFFS                                                                        (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x34)
#define HWIO_ECPRI_TIMERS_XO_CLK_DIV_CFG_V2_RMSK                                                                        0x800001ff
#define HWIO_ECPRI_TIMERS_XO_CLK_DIV_CFG_V2_ATTR                                                                                     0x3
#define HWIO_ECPRI_TIMERS_XO_CLK_DIV_CFG_V2_IN                    \
                in_dword(HWIO_ECPRI_TIMERS_XO_CLK_DIV_CFG_V2_ADDR)
#define HWIO_ECPRI_TIMERS_XO_CLK_DIV_CFG_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_TIMERS_XO_CLK_DIV_CFG_V2_ADDR, m)
#define HWIO_ECPRI_TIMERS_XO_CLK_DIV_CFG_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_TIMERS_XO_CLK_DIV_CFG_V2_ADDR,v)
#define HWIO_ECPRI_TIMERS_XO_CLK_DIV_CFG_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_TIMERS_XO_CLK_DIV_CFG_V2_ADDR,m,v,HWIO_ECPRI_TIMERS_XO_CLK_DIV_CFG_V2_IN)
#define HWIO_ECPRI_TIMERS_XO_CLK_DIV_CFG_V2_ENABLE_BMSK                                                                 0x80000000
#define HWIO_ECPRI_TIMERS_XO_CLK_DIV_CFG_V2_ENABLE_SHFT                                                                         31
#define HWIO_ECPRI_TIMERS_XO_CLK_DIV_CFG_V2_VALUE_BMSK                                                                       0x1ff
#define HWIO_ECPRI_TIMERS_XO_CLK_DIV_CFG_V2_VALUE_SHFT                                                                           0

#define HWIO_ECPRI_TIMERS_PULSE_GRAN_CFG_V2_ADDR                                                                        (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x38)
#define HWIO_ECPRI_TIMERS_PULSE_GRAN_CFG_V2_PHYS                                                                        (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x38)
#define HWIO_ECPRI_TIMERS_PULSE_GRAN_CFG_V2_OFFS                                                                        (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x38)
#define HWIO_ECPRI_TIMERS_PULSE_GRAN_CFG_V2_RMSK                                                                             0xfff
#define HWIO_ECPRI_TIMERS_PULSE_GRAN_CFG_V2_ATTR                                                                                     0x3
#define HWIO_ECPRI_TIMERS_PULSE_GRAN_CFG_V2_IN                    \
                in_dword(HWIO_ECPRI_TIMERS_PULSE_GRAN_CFG_V2_ADDR)
#define HWIO_ECPRI_TIMERS_PULSE_GRAN_CFG_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_TIMERS_PULSE_GRAN_CFG_V2_ADDR, m)
#define HWIO_ECPRI_TIMERS_PULSE_GRAN_CFG_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_TIMERS_PULSE_GRAN_CFG_V2_ADDR,v)
#define HWIO_ECPRI_TIMERS_PULSE_GRAN_CFG_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_TIMERS_PULSE_GRAN_CFG_V2_ADDR,m,v,HWIO_ECPRI_TIMERS_PULSE_GRAN_CFG_V2_IN)
#define HWIO_ECPRI_TIMERS_PULSE_GRAN_CFG_V2_GRAN_3_BMSK                                                                      0xe00
#define HWIO_ECPRI_TIMERS_PULSE_GRAN_CFG_V2_GRAN_3_SHFT                                                                          9
#define HWIO_ECPRI_TIMERS_PULSE_GRAN_CFG_V2_GRAN_2_BMSK                                                                      0x1c0
#define HWIO_ECPRI_TIMERS_PULSE_GRAN_CFG_V2_GRAN_2_SHFT                                                                          6
#define HWIO_ECPRI_TIMERS_PULSE_GRAN_CFG_V2_GRAN_1_BMSK                                                                       0x38
#define HWIO_ECPRI_TIMERS_PULSE_GRAN_CFG_V2_GRAN_1_SHFT                                                                          3
#define HWIO_ECPRI_TIMERS_PULSE_GRAN_CFG_V2_GRAN_0_BMSK                                                                        0x7
#define HWIO_ECPRI_TIMERS_PULSE_GRAN_CFG_V2_GRAN_0_SHFT                                                                          0

#define HWIO_ECPRI_QTIME_SMP_V2_ADDR                                                                                    (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x3c)
#define HWIO_ECPRI_QTIME_SMP_V2_PHYS                                                                                    (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x3c)
#define HWIO_ECPRI_QTIME_SMP_V2_OFFS                                                                                    (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x3c)
#define HWIO_ECPRI_QTIME_SMP_V2_RMSK                                                                                           0x1
#define HWIO_ECPRI_QTIME_SMP_V2_ATTR                                                                                                 0x2
#define HWIO_ECPRI_QTIME_SMP_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_QTIME_SMP_V2_ADDR,v)
#define HWIO_ECPRI_QTIME_SMP_V2_PULSE_BMSK                                                                                     0x1
#define HWIO_ECPRI_QTIME_SMP_V2_PULSE_SHFT                                                                                       0

#define HWIO_ECPRI_QTIME_LSB_V2_ADDR                                                                                    (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x40)
#define HWIO_ECPRI_QTIME_LSB_V2_PHYS                                                                                    (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x40)
#define HWIO_ECPRI_QTIME_LSB_V2_OFFS                                                                                    (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x40)
#define HWIO_ECPRI_QTIME_LSB_V2_RMSK                                                                                    0xffffffff
#define HWIO_ECPRI_QTIME_LSB_V2_ATTR                                                                                                 0x1
#define HWIO_ECPRI_QTIME_LSB_V2_IN                    \
                in_dword(HWIO_ECPRI_QTIME_LSB_V2_ADDR)
#define HWIO_ECPRI_QTIME_LSB_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_QTIME_LSB_V2_ADDR, m)
#define HWIO_ECPRI_QTIME_LSB_V2_VALUE_BMSK                                                                              0xffffffff
#define HWIO_ECPRI_QTIME_LSB_V2_VALUE_SHFT                                                                                       0

#define HWIO_ECPRI_QTIME_MSB_V2_ADDR                                                                                    (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x44)
#define HWIO_ECPRI_QTIME_MSB_V2_PHYS                                                                                    (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x44)
#define HWIO_ECPRI_QTIME_MSB_V2_OFFS                                                                                    (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x44)
#define HWIO_ECPRI_QTIME_MSB_V2_RMSK                                                                                    0xffffffff
#define HWIO_ECPRI_QTIME_MSB_V2_ATTR                                                                                                 0x1
#define HWIO_ECPRI_QTIME_MSB_V2_IN                    \
                in_dword(HWIO_ECPRI_QTIME_MSB_V2_ADDR)
#define HWIO_ECPRI_QTIME_MSB_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_QTIME_MSB_V2_ADDR, m)
#define HWIO_ECPRI_QTIME_MSB_V2_VALUE_BMSK                                                                              0xffffffff
#define HWIO_ECPRI_QTIME_MSB_V2_VALUE_SHFT                                                                                       0

#define HWIO_ECPRI_SNOC_FEC_V2_ADDR                                                                                     (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x48)
#define HWIO_ECPRI_SNOC_FEC_V2_PHYS                                                                                     (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x48)
#define HWIO_ECPRI_SNOC_FEC_V2_OFFS                                                                                     (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x48)
#define HWIO_ECPRI_SNOC_FEC_V2_RMSK                                                                                         0xc7ff
#define HWIO_ECPRI_SNOC_FEC_V2_ATTR                                                                                                  0x3
#define HWIO_ECPRI_SNOC_FEC_V2_IN                    \
                in_dword(HWIO_ECPRI_SNOC_FEC_V2_ADDR)
#define HWIO_ECPRI_SNOC_FEC_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_SNOC_FEC_V2_ADDR, m)
#define HWIO_ECPRI_SNOC_FEC_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_SNOC_FEC_V2_ADDR,v)
#define HWIO_ECPRI_SNOC_FEC_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_SNOC_FEC_V2_ADDR,m,v,HWIO_ECPRI_SNOC_FEC_V2_IN)
#define HWIO_ECPRI_SNOC_FEC_V2_VALID_BMSK                                                                                   0x8000
#define HWIO_ECPRI_SNOC_FEC_V2_VALID_SHFT                                                                                       15
#define HWIO_ECPRI_SNOC_FEC_V2_CLEAR_BMSK                                                                                   0x4000
#define HWIO_ECPRI_SNOC_FEC_V2_CLEAR_SHFT                                                                                       14
#define HWIO_ECPRI_SNOC_FEC_V2_DIRECTION_BMSK                                                                                0x400
#define HWIO_ECPRI_SNOC_FEC_V2_DIRECTION_SHFT                                                                                   10
#define HWIO_ECPRI_SNOC_FEC_V2_NOC_PORT_BMSK                                                                                 0x300
#define HWIO_ECPRI_SNOC_FEC_V2_NOC_PORT_SHFT                                                                                     8
#define HWIO_ECPRI_SNOC_FEC_V2_AXI_ID_BMSK                                                                                    0xff
#define HWIO_ECPRI_SNOC_FEC_V2_AXI_ID_SHFT                                                                                       0

#define HWIO_ECPRI_QMB_CFG_V2_PARAM_ADDR                                                                                (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x4c)
#define HWIO_ECPRI_QMB_CFG_PARAM_V2_PHYS                                                                                (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x4c)
#define HWIO_ECPRI_QMB_CFG_PARAM_V2_OFFS                                                                                (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x4c)
#define HWIO_ECPRI_QMB_CFG_PARAM_V2_RMSK                                                                                      0xff
#define HWIO_ECPRI_QMB_CFG_PARAM_V2_ATTR                                                                                             0x3
#define HWIO_ECPRI_QMB_CFG_PARAM_V2_IN                    \
                in_dword(HWIO_ECPRI_QMB_CFG_V2_PARAM_ADDR)
#define HWIO_ECPRI_QMB_CFG_PARAM_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_QMB_CFG_V2_PARAM_ADDR, m)
#define HWIO_ECPRI_QMB_CFG_PARAM_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_QMB_CFG_V2_PARAM_ADDR,v)
#define HWIO_ECPRI_QMB_CFG_PARAM_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_QMB_CFG_PARAM_ADDR,m,v,HWIO_ECPRI_QMB_CFG_PARAM_V2_IN)
#define HWIO_ECPRI_QMB_CFG_PARAM_V2_REQ_AMEMTYPE_BMSK                                                                         0xe0
#define HWIO_ECPRI_QMB_CFG_PARAM_V2_REQ_AMEMTYPE_SHFT                                                                            5
#define HWIO_ECPRI_QMB_CFG_PARAM_V2_REQ_AINNERSHARED_BMSK                                                                     0x10
#define HWIO_ECPRI_QMB_CFG_PARAM_V2_REQ_AINNERSHARED_SHFT                                                                        4
#define HWIO_ECPRI_QMB_CFG_PARAM_V2_REQ_ANOALLOCATE_BMSK                                                                       0x8
#define HWIO_ECPRI_QMB_CFG_PARAM_V2_REQ_ANOALLOCATE_SHFT                                                                         3
#define HWIO_ECPRI_QMB_CFG_PARAM_V2_REQ_AOOORD_BMSK                                                                            0x4
#define HWIO_ECPRI_QMB_CFG_PARAM_V2_REQ_AOOORD_SHFT                                                                              2
#define HWIO_ECPRI_QMB_CFG_PARAM_V2_REQ_AOOOWR_BMSK                                                                            0x2
#define HWIO_ECPRI_QMB_CFG_PARAM_V2_REQ_AOOOWR_SHFT                                                                              1
#define HWIO_ECPRI_QMB_CFG_PARAM_V2_REQ_ASHARED_BMSK                                                                           0x1
#define HWIO_ECPRI_QMB_CFG_PARAM_V2_REQ_ASHARED_SHFT                                                                             0

#define HWIO_ECPRI_NFAPI_CFG_0_V2_ADDR                                                                                  (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x50)
#define HWIO_ECPRI_NFAPI_CFG_0_V2_PHYS                                                                                  (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x50)
#define HWIO_ECPRI_NFAPI_CFG_0_V2_OFFS                                                                                  (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x50)
#define HWIO_ECPRI_NFAPI_CFG_0_V2_RMSK                                                                                        0xff
#define HWIO_ECPRI_NFAPI_CFG_0_V2_ATTR                                                                                               0x3
#define HWIO_ECPRI_NFAPI_CFG_0_V2_IN                    \
                in_dword(HWIO_ECPRI_NFAPI_CFG_0_V2_ADDR)
#define HWIO_ECPRI_NFAPI_CFG_0_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NFAPI_CFG_0_V2_ADDR, m)
#define HWIO_ECPRI_NFAPI_CFG_0_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_NFAPI_CFG_0_V2_ADDR,v)
#define HWIO_ECPRI_NFAPI_CFG_0_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_NFAPI_CFG_0_V2_ADDR,m,v,HWIO_ECPRI_NFAPI_CFG_0_V2_IN)
#define HWIO_ECPRI_NFAPI_CFG_0_V2_HEADER_LENGTH_BMSK                                                                          0xff
#define HWIO_ECPRI_NFAPI_CFG_0_V2_HEADER_LENGTH_SHFT                                                                             0

#define HWIO_ECPRI_NFAPI_CFG_1_V2_ADDR                                                                                  (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x54)
#define HWIO_ECPRI_NFAPI_CFG_1_V2_PHYS                                                                                  (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x54)
#define HWIO_ECPRI_NFAPI_CFG_1_V2_OFFS                                                                                  (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x54)
#define HWIO_ECPRI_NFAPI_CFG_1_V2_RMSK                                                                                  0xffffffff
#define HWIO_ECPRI_NFAPI_CFG_1_V2_ATTR                                                                                               0x3
#define HWIO_ECPRI_NFAPI_CFG_1_V2_IN                    \
                in_dword(HWIO_ECPRI_NFAPI_CFG_1_V2_ADDR)
#define HWIO_ECPRI_NFAPI_CFG_1_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NFAPI_CFG_1_V2_ADDR, m)
#define HWIO_ECPRI_NFAPI_CFG_1_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_NFAPI_CFG_1_V2_ADDR,v)
#define HWIO_ECPRI_NFAPI_CFG_1_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_NFAPI_CFG_1_V2_ADDR,m,v,HWIO_ECPRI_NFAPI_CFG_1_V2_IN)
#define HWIO_ECPRI_NFAPI_CFG_1_V2_TIME_STAMP_OFFSET_BMSK                                                                0xff000000
#define HWIO_ECPRI_NFAPI_CFG_1_V2_TIME_STAMP_OFFSET_SHFT                                                                        24
#define HWIO_ECPRI_NFAPI_CFG_1_V2_SEQUENCE_NUMBER_OFFSET_BMSK                                                             0xff0000
#define HWIO_ECPRI_NFAPI_CFG_1_V2_SEQUENCE_NUMBER_OFFSET_SHFT                                                                   16
#define HWIO_ECPRI_NFAPI_CFG_1_V2_TOTAL_SDU_LENGTH_OFFSET_BMSK                                                              0xff00
#define HWIO_ECPRI_NFAPI_CFG_1_V2_TOTAL_SDU_LENGTH_OFFSET_SHFT                                                                   8
#define HWIO_ECPRI_NFAPI_CFG_1_V2_BYTE_OFFSET_OFFSET_BMSK                                                                     0xff
#define HWIO_ECPRI_NFAPI_CFG_1_V2_BYTE_OFFSET_OFFSET_SHFT                                                                        0

#define HWIO_ECPRI_NFAPI_CFG_2_V2_ADDR                                                                                  (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x58)
#define HWIO_ECPRI_NFAPI_CFG_2_V2_PHYS                                                                                  (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x58)
#define HWIO_ECPRI_NFAPI_CFG_2_V2_OFFS                                                                                  (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x58)
#define HWIO_ECPRI_NFAPI_CFG_2_V2_RMSK                                                                                  0xffffffff
#define HWIO_ECPRI_NFAPI_CFG_2_V2_ATTR                                                                                               0x3
#define HWIO_ECPRI_NFAPI_CFG_2_V2_IN                    \
                in_dword(HWIO_ECPRI_NFAPI_CFG_2_V2_ADDR)
#define HWIO_ECPRI_NFAPI_CFG_2_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NFAPI_CFG_2_V2_ADDR, m)
#define HWIO_ECPRI_NFAPI_CFG_2_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_NFAPI_CFG_2_V2_ADDR,v)
#define HWIO_ECPRI_NFAPI_CFG_2_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_NFAPI_CFG_2_V2_ADDR,m,v,HWIO_ECPRI_NFAPI_CFG_2_V2_IN)
#define HWIO_ECPRI_NFAPI_CFG_2_V2_TIME_STAMP_SIZE_BMSK                                                                  0xff000000
#define HWIO_ECPRI_NFAPI_CFG_2_V2_TIME_STAMP_SIZE_SHFT                                                                          24
#define HWIO_ECPRI_NFAPI_CFG_2_V2_SEQUENCE_NUMBER_SIZE_BMSK                                                               0xff0000
#define HWIO_ECPRI_NFAPI_CFG_2_V2_SEQUENCE_NUMBER_SIZE_SHFT                                                                     16
#define HWIO_ECPRI_NFAPI_CFG_2_V2_TOTAL_SDU_LENGTH_SIZE_BMSK                                                                0xff00
#define HWIO_ECPRI_NFAPI_CFG_2_V2_TOTAL_SDU_LENGTH_SIZE_SHFT                                                                     8
#define HWIO_ECPRI_NFAPI_CFG_2_V2_BYTE_OFFSET_SIZE_BMSK                                                                       0xff
#define HWIO_ECPRI_NFAPI_CFG_2_V2_BYTE_OFFSET_SIZE_SHFT                                                                          0

#define HWIO_ECPRI_NFAPI_REASSEMBLY_CFG_0_V2_ADDR                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x5c)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_CFG_0_V2_PHYS                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x5c)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_CFG_0_V2_OFFS                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x5c)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_CFG_0_V2_RMSK                                                                              0x7
#define HWIO_ECPRI_NFAPI_REASSEMBLY_CFG_0_V2_ATTR                                                                                    0x3
#define HWIO_ECPRI_NFAPI_REASSEMBLY_CFG_0_V2_IN                    \
                in_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_CFG_0_V2_ADDR)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_CFG_0_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NFAPI_REASSEMBLY_CFG_0_V2_ADDR, m)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_CFG_0_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_CFG_0_V2_ADDR,v)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_CFG_0_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_NFAPI_REASSEMBLY_CFG_0_V2_ADDR,m,v,HWIO_ECPRI_NFAPI_REASSEMBLY_CFG_0_V2_IN)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_CFG_0_V2_BAD_TOTAL_SDU_LENGTH_PKT_EN_BMSK                                                  0x4
#define HWIO_ECPRI_NFAPI_REASSEMBLY_CFG_0_V2_BAD_TOTAL_SDU_LENGTH_PKT_EN_SHFT                                                    2
#define HWIO_ECPRI_NFAPI_REASSEMBLY_CFG_0_V2_BAD_TIMESTAMP_EN_BMSK                                                             0x2
#define HWIO_ECPRI_NFAPI_REASSEMBLY_CFG_0_V2_BAD_TIMESTAMP_EN_SHFT                                                               1
#define HWIO_ECPRI_NFAPI_REASSEMBLY_CFG_0_V2_STALL_MODE_BMSK                                                                   0x1
#define HWIO_ECPRI_NFAPI_REASSEMBLY_CFG_0_V2_STALL_MODE_SHFT                                                                     0

#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_V2_ADDR                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x60)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_V2_PHYS                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x60)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_V2_OFFS                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x60)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_V2_RMSK                                                                             0xff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_V2_ATTR                                                                                    0x1
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_V2_IN                    \
                in_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_V2_ADDR)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_V2_ADDR, m)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_V2_MESSAGE_TOO_BIG_BMSK                                                             0x80
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_V2_MESSAGE_TOO_BIG_SHFT                                                                7
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_V2_NOT_ENOUGH_BYTES_BMSK                                                            0x40
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_V2_NOT_ENOUGH_BYTES_SHFT                                                               6
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_V2_NOT_ENOUGH_CONTEXTS_BMSK                                                         0x20
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_V2_NOT_ENOUGH_CONTEXTS_SHFT                                                            5
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_V2_TIMEOUT_BMSK                                                                     0x10
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_V2_TIMEOUT_SHFT                                                                        4
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_V2_BAD_TOTAL_SDU_LENGTH_BMSK                                                         0x8
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_V2_BAD_TOTAL_SDU_LENGTH_SHFT                                                           3
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_V2_BAD_TIMESTAMP_BMSK                                                                0x4
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_V2_BAD_TIMESTAMP_SHFT                                                                  2
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_V2_PACKET_BIGGER_THAN_SDU_LENGTH_BMSK                                                0x2
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_V2_PACKET_BIGGER_THAN_SDU_LENGTH_SHFT                                                  1
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_V2_MESSAGE_BIGGER_THAN_SDU_LENGTH_BMSK                                               0x1
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_V2_MESSAGE_BIGGER_THAN_SDU_LENGTH_SHFT                                                 0

#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_1_V2_ADDR                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x64)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_1_V2_PHYS                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x64)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_1_V2_OFFS                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x64)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_1_V2_RMSK                                                                       0xffffffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_1_V2_ATTR                                                                                    0x1
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_1_V2_IN                    \
                in_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_1_V2_ADDR)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_1_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_1_V2_ADDR, m)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_1_V2_OFFSET_BMSK                                                                0xffffffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_1_V2_OFFSET_SHFT                                                                         0

#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_2_V2_ADDR                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x68)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_2_V2_PHYS                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x68)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_2_V2_OFFS                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x68)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_2_V2_RMSK                                                                       0xffffffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_2_V2_ATTR                                                                                    0x1
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_2_V2_IN                    \
                in_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_2_V2_ADDR)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_2_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_2_V2_ADDR, m)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_2_V2_SDU_LENGTH_BMSK                                                            0xffffffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_2_V2_SDU_LENGTH_SHFT                                                                     0

#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_3_V2_ADDR                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x6c)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_3_V2_PHYS                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x6c)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_3_V2_OFFS                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x6c)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_3_V2_RMSK                                                                       0xffffffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_3_V2_ATTR                                                                                    0x1
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_3_V2_IN                    \
                in_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_3_V2_ADDR)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_3_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_3_V2_ADDR, m)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_3_V2_TIMESTAMP_BMSK                                                             0xffffffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_3_V2_TIMESTAMP_SHFT                                                                      0

#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_4_V2_ADDR                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x70)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_4_V2_PHYS                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x70)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_4_V2_OFFS                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x70)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_4_V2_RMSK                                                                       0xffff00ff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_4_V2_ATTR                                                                                    0x1
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_4_V2_IN                    \
                in_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_4_V2_ADDR)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_4_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_4_V2_ADDR, m)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_4_V2_GSI_ID_BMSK                                                                0xff000000
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_4_V2_GSI_ID_SHFT                                                                        24
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_4_V2_CONTEXT_ID_BMSK                                                              0xff0000
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_4_V2_CONTEXT_ID_SHFT                                                                    16
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_4_V2_CHANNEL_ID_BMSK                                                                  0xff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_4_V2_CHANNEL_ID_SHFT                                                                     0

#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_5_V2_ADDR                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x74)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_5_V2_PHYS                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x74)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_5_V2_OFFS                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x74)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_5_V2_RMSK                                                                       0xffffffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_5_V2_ATTR                                                                                    0x1
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_5_V2_IN                    \
                in_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_5_V2_ADDR)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_5_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_5_V2_ADDR, m)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_5_V2_SEQUENCE_NUMBER_BMSK                                                       0xffffffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_5_V2_SEQUENCE_NUMBER_SHFT                                                                0

#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_PKT_CNT_V2_ADDR                                          (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x78)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_PKT_CNT_V2_PHYS                                          (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x78)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_PKT_CNT_V2_OFFS                                          (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x78)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_PKT_CNT_V2_RMSK                                            0xffffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_PKT_CNT_V2_ATTR                                                       0x3
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_PKT_CNT_V2_IN                    \
                in_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_PKT_CNT_V2_ADDR)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_PKT_CNT_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_PKT_CNT_V2_ADDR, m)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_PKT_CNT_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_PKT_CNT_V2_ADDR,v)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_PKT_CNT_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_PKT_CNT_V2_ADDR,m,v,HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_PKT_CNT_V2_IN)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_PKT_CNT_V2_PACKET_COUNT_BMSK                               0xffffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_PKT_CNT_V2_PACKET_COUNT_SHFT                                      0

#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_LSB_V2_ADDR                                     (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x7c)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_LSB_V2_PHYS                                     (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x7c)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_LSB_V2_OFFS                                     (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x7c)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_LSB_V2_RMSK                                     0xffffffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_LSB_V2_ATTR                                                  0x3
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_LSB_V2_IN                    \
                in_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_LSB_V2_ADDR)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_LSB_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_LSB_V2_ADDR, m)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_LSB_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_LSB_V2_ADDR,v)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_LSB_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_LSB_V2_ADDR,m,v,HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_LSB_V2_IN)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_LSB_V2_BYTE_COUNT_BMSK                          0xffffffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_LSB_V2_BYTE_COUNT_SHFT                                   0

#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_MSB_V2_ADDR                                     (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x80)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_MSB_V2_PHYS                                     (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x80)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_MSB_V2_OFFS                                     (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x80)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_MSB_V2_RMSK                                           0xff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_MSB_V2_ATTR                                                  0x3
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_MSB_V2_IN                    \
                in_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_MSB_V2_ADDR)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_MSB_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_MSB_V2_ADDR, m)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_MSB_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_MSB_V2_ADDR,v)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_MSB_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_MSB_V2_ADDR,m,v,HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_MSB_V2_IN)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_MSB_V2_BYTE_COUNT_BMSK                                0xff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_MSB_V2_BYTE_COUNT_SHFT                                   0

#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_PKT_CNT_V2_ADDR                                                 (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x84)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_PKT_CNT_V2_PHYS                                                 (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x84)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_PKT_CNT_V2_OFFS                                                 (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x84)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_PKT_CNT_V2_RMSK                                                   0xffffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_PKT_CNT_V2_ATTR                                                              0x3
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_PKT_CNT_V2_IN                    \
                in_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_PKT_CNT_V2_ADDR)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_PKT_CNT_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_PKT_CNT_V2_ADDR, m)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_PKT_CNT_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_PKT_CNT_V2_ADDR,v)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_PKT_CNT_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_PKT_CNT_V2_ADDR,m,v,HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_PKT_CNT_V2_IN)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_PKT_CNT_V2_PACKET_COUNT_BMSK                                      0xffffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_PKT_CNT_V2_PACKET_COUNT_SHFT                                             0

#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_LSB_V2_ADDR                                            (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x88)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_LSB_V2_PHYS                                            (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x88)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_LSB_V2_OFFS                                            (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x88)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_LSB_V2_RMSK                                            0xffffffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_LSB_V2_ATTR                                                         0x3
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_LSB_V2_IN                    \
                in_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_LSB_V2_ADDR)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_LSB_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_LSB_V2_ADDR, m)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_LSB_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_LSB_V2_ADDR,v)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_LSB_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_LSB_V2_ADDR,m,v,HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_LSB_V2_IN)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_LSB_V2_BYTE_COUNT_BMSK                                 0xffffffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_LSB_V2_BYTE_COUNT_SHFT                                          0

#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_MSB_V2_ADDR                                            (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x8c)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_MSB_V2_PHYS                                            (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x8c)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_MSB_V2_OFFS                                            (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x8c)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_MSB_V2_RMSK                                                  0xff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_MSB_V2_ATTR                                                         0x3
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_MSB_V2_IN                    \
                in_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_MSB_V2_ADDR)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_MSB_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_MSB_V2_ADDR, m)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_MSB_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_MSB_V2_ADDR,v)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_MSB_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_MSB_V2_ADDR,m,v,HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_MSB_V2_IN)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_MSB_V2_BYTE_COUNT_BMSK                                       0xff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_MSB_V2_BYTE_COUNT_SHFT                                          0

#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_ADDR                                 (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x90)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_PHYS                                 (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x90)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_OFFS                                 (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x90)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_RMSK                                   0xffffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_ATTR                                              0x3
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_IN                    \
                in_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_ADDR)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_ADDR, m)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_ADDR,v)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_ADDR,m,v,HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_IN)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_PACKET_COUNT_BMSK                      0xffffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_PACKET_COUNT_SHFT                             0

#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_ADDR                            (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x94)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_PHYS                            (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x94)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_OFFS                            (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x94)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_RMSK                            0xffffffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_ATTR                                         0x3
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_IN                    \
                in_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_ADDR)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_ADDR, m)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_ADDR,v)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_ADDR,m,v,HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_IN)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_BYTE_COUNT_BMSK                 0xffffffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_BYTE_COUNT_SHFT                          0

#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_ADDR                            (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x98)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_PHYS                            (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x98)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_OFFS                            (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x98)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_RMSK                                  0xff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_ATTR                                         0x3
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_IN                    \
                in_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_ADDR)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_ADDR, m)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_ADDR,v)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_ADDR,m,v,HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_IN)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_BYTE_COUNT_BMSK                       0xff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_BYTE_COUNT_SHFT                          0

#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_ADDR                          (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x9c)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_PHYS                          (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x9c)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_OFFS                          (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x9c)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_RMSK                            0xffffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_ATTR                                       0x3
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_IN                    \
                in_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_ADDR)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_ADDR, m)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_ADDR,v)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_ADDR,m,v,HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_IN)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_PACKET_COUNT_BMSK               0xffffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_PACKET_COUNT_SHFT                      0

#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_ADDR                     (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xa0)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_PHYS                     (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xa0)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_OFFS                     (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xa0)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_RMSK                     0xffffffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_ATTR                                  0x3
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_IN                    \
                in_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_ADDR)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_ADDR, m)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_ADDR,v)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_ADDR,m,v,HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_IN)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_BYTE_COUNT_BMSK          0xffffffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_BYTE_COUNT_SHFT                   0

#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_ADDR                     (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xa4)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_PHYS                     (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xa4)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_OFFS                     (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xa4)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_RMSK                           0xff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_ATTR                                  0x3
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_IN                    \
                in_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_ADDR)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_ADDR, m)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_ADDR,v)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_ADDR,m,v,HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_IN)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_BYTE_COUNT_BMSK                0xff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_BYTE_COUNT_SHFT                   0

#define HWIO_ECPRI_NFAPI_REASSEMBLY_STATE_V2_ADDR                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xa8)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_STATE_V2_PHYS                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xa8)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_STATE_V2_OFFS                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xa8)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_STATE_V2_RMSK                                                                             0x3f
#define HWIO_ECPRI_NFAPI_REASSEMBLY_STATE_V2_ATTR                                                                                    0x1
#define HWIO_ECPRI_NFAPI_REASSEMBLY_STATE_V2_IN                    \
                in_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_STATE_V2_ADDR)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_STATE_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NFAPI_REASSEMBLY_STATE_V2_ADDR, m)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_STATE_V2_SEQUENCE_HANDLER_IDLE_BMSK                                                       0x20
#define HWIO_ECPRI_NFAPI_REASSEMBLY_STATE_V2_SEQUENCE_HANDLER_IDLE_SHFT                                                          5
#define HWIO_ECPRI_NFAPI_REASSEMBLY_STATE_V2_TIMER_IDLE_BMSK                                                                  0x10
#define HWIO_ECPRI_NFAPI_REASSEMBLY_STATE_V2_TIMER_IDLE_SHFT                                                                     4
#define HWIO_ECPRI_NFAPI_REASSEMBLY_STATE_V2_PACKET_HANDLER_IDLE_BMSK                                                          0x8
#define HWIO_ECPRI_NFAPI_REASSEMBLY_STATE_V2_PACKET_HANDLER_IDLE_SHFT                                                            3
#define HWIO_ECPRI_NFAPI_REASSEMBLY_STATE_V2_PIPELINE_BUFFER_IDLE_BMSK                                                         0x4
#define HWIO_ECPRI_NFAPI_REASSEMBLY_STATE_V2_PIPELINE_BUFFER_IDLE_SHFT                                                           2
#define HWIO_ECPRI_NFAPI_REASSEMBLY_STATE_V2_ADDRESS_RESOLUTION_IDLE_BMSK                                                      0x2
#define HWIO_ECPRI_NFAPI_REASSEMBLY_STATE_V2_ADDRESS_RESOLUTION_IDLE_SHFT                                                        1
#define HWIO_ECPRI_NFAPI_REASSEMBLY_STATE_V2_CONTEXT_BRESP_IDLE_BMSK                                                           0x1
#define HWIO_ECPRI_NFAPI_REASSEMBLY_STATE_V2_CONTEXT_BRESP_IDLE_SHFT                                                             0

#define HWIO_ECPRI_STATE_GSI_IF_V2_ADDR                                                                                 (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x100)
#define HWIO_ECPRI_STATE_GSI_IF_V2_PHYS                                                                                 (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x100)
#define HWIO_ECPRI_STATE_GSI_IF_V2_OFFS                                                                                 (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x100)
#define HWIO_ECPRI_STATE_GSI_IF_V2_RMSK                                                                                    0x70707
#define HWIO_ECPRI_STATE_GSI_IF_V2_ATTR                                                                                              0x1
#define HWIO_ECPRI_STATE_GSI_IF_V2_IN                    \
                in_dword(HWIO_ECPRI_STATE_GSI_IF_V2_ADDR)
#define HWIO_ECPRI_STATE_GSI_IF_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_STATE_GSI_IF_V2_ADDR, m)
#define HWIO_ECPRI_STATE_GSI_IF_V2_ECPRI_GSI_2_IDLE_BMSK                                                                   0x40000
#define HWIO_ECPRI_STATE_GSI_IF_V2_ECPRI_GSI_2_IDLE_SHFT                                                                        18
#define HWIO_ECPRI_STATE_GSI_IF_V2_ECPRI_GSI_2_IF_IDLE_BMSK                                                                0x20000
#define HWIO_ECPRI_STATE_GSI_IF_V2_ECPRI_GSI_2_IF_IDLE_SHFT                                                                     17
#define HWIO_ECPRI_STATE_GSI_IF_V2_ECPRI_GSI_2_AOS_FSM_IDLE_BMSK                                                           0x10000
#define HWIO_ECPRI_STATE_GSI_IF_V2_ECPRI_GSI_2_AOS_FSM_IDLE_SHFT                                                                16
#define HWIO_ECPRI_STATE_GSI_IF_V2_ECPRI_GSI_1_IDLE_BMSK                                                                     0x400
#define HWIO_ECPRI_STATE_GSI_IF_V2_ECPRI_GSI_1_IDLE_SHFT                                                                        10
#define HWIO_ECPRI_STATE_GSI_IF_V2_ECPRI_GSI_1_IF_IDLE_BMSK                                                                  0x200
#define HWIO_ECPRI_STATE_GSI_IF_V2_ECPRI_GSI_1_IF_IDLE_SHFT                                                                      9
#define HWIO_ECPRI_STATE_GSI_IF_V2_ECPRI_GSI_1_AOS_FSM_IDLE_BMSK                                                             0x100
#define HWIO_ECPRI_STATE_GSI_IF_V2_ECPRI_GSI_1_AOS_FSM_IDLE_SHFT                                                                 8
#define HWIO_ECPRI_STATE_GSI_IF_V2_ECPRI_GSI_0_IDLE_BMSK                                                                       0x4
#define HWIO_ECPRI_STATE_GSI_IF_V2_ECPRI_GSI_0_IDLE_SHFT                                                                         2
#define HWIO_ECPRI_STATE_GSI_IF_V2_ECPRI_GSI_0_IF_IDLE_BMSK                                                                    0x2
#define HWIO_ECPRI_STATE_GSI_IF_V2_ECPRI_GSI_0_IF_IDLE_SHFT                                                                      1
#define HWIO_ECPRI_STATE_GSI_IF_V2_ECPRI_GSI_0_AOS_FSM_IDLE_BMSK                                                               0x1
#define HWIO_ECPRI_STATE_GSI_IF_V2_ECPRI_GSI_0_AOS_FSM_IDLE_SHFT                                                                 0

#define HWIO_ECPRI_STATE_GSI_TLV_FIFO_EMPTY_V2_GSI_m_REG_n_ADDR(m,n)                                                    (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X400 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_STATE_GSI_TLV_FIFO_EMPTY_V2_GSI_m_REG_n_PHYS(m,n)                                                    (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X400 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_STATE_GSI_TLV_FIFO_EMPTY_V2_GSI_m_REG_n_OFFS(m,n)                                                    (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X400 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_STATE_GSI_TLV_FIFO_EMPTY_V2_GSI_m_REG_n_RMSK                                                         0xffffffff
#define HWIO_ECPRI_STATE_GSI_TLV_FIFO_EMPTY_V2_GSI_m_REG_n_MAXm                                                                  2
#define HWIO_ECPRI_STATE_GSI_TLV_FIFO_EMPTY_V2_GSI_m_REG_n_MAXn                                                                  2
#define HWIO_ECPRI_STATE_GSI_TLV_FIFO_EMPTY_V2_GSI_m_REG_n_ATTR                                                                      0x1
#define HWIO_ECPRI_STATE_GSI_TLV_FIFO_EMPTY_V2_GSI_m_REG_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_STATE_GSI_TLV_FIFO_EMPTY_V2_GSI_m_REG_n_ADDR(m,n), HWIO_ECPRI_STATE_GSI_TLV_FIFO_EMPTY_V2_GSI_m_REG_n_RMSK)
#define HWIO_ECPRI_STATE_GSI_TLV_FIFO_EMPTY_V2_GSI_m_REG_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_STATE_GSI_TLV_FIFO_EMPTY_V2_GSI_m_REG_n_ADDR(m,n), mask)
#define HWIO_ECPRI_STATE_GSI_TLV_FIFO_EMPTY_V2_GSI_m_REG_n_CHANNEL_FIFO_EMPTY_BMSK                                      0xffffffff
#define HWIO_ECPRI_STATE_GSI_TLV_FIFO_EMPTY_V2_GSI_m_REG_n_CHANNEL_FIFO_EMPTY_SHFT                                               0

#define HWIO_ECPRI_STATE_GSI_AOS_FIFO_EMPTY_V2_GSI_m_REG_n_ADDR(m,n)                                                    (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X440 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_STATE_GSI_AOS_FIFO_EMPTY_V2_GSI_m_REG_n_PHYS(m,n)                                                    (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X440 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_STATE_GSI_AOS_FIFO_EMPTY_V2_GSI_m_REG_n_OFFS(m,n)                                                    (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X440 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_STATE_GSI_AOS_FIFO_EMPTY_V2_GSI_m_REG_n_RMSK                                                         0xffffffff
#define HWIO_ECPRI_STATE_GSI_AOS_FIFO_EMPTY_V2_GSI_m_REG_n_MAXm                                                                  2
#define HWIO_ECPRI_STATE_GSI_AOS_FIFO_EMPTY_V2_GSI_m_REG_n_MAXn                                                                  2
#define HWIO_ECPRI_STATE_GSI_AOS_FIFO_EMPTY_V2_GSI_m_REG_n_ATTR                                                                      0x1
#define HWIO_ECPRI_STATE_GSI_AOS_FIFO_EMPTY_V2_GSI_m_REG_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_STATE_GSI_AOS_FIFO_EMPTY_V2_GSI_m_REG_n_ADDR(m,n), HWIO_ECPRI_STATE_GSI_AOS_FIFO_EMPTY_V2_GSI_m_REG_n_RMSK)
#define HWIO_ECPRI_STATE_GSI_AOS_FIFO_EMPTY_V2_GSI_m_REG_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_STATE_GSI_AOS_FIFO_EMPTY_V2_GSI_m_REG_n_ADDR(m,n), mask)
#define HWIO_ECPRI_STATE_GSI_AOS_FIFO_EMPTY_V2_GSI_m_REG_n_CHANNEL_FIFO_EMPTY_BMSK                                      0xffffffff
#define HWIO_ECPRI_STATE_GSI_AOS_FIFO_EMPTY_V2_GSI_m_REG_n_CHANNEL_FIFO_EMPTY_SHFT                                               0


#define HWIO_ECPRI_YELLOW_MARKER_BELOW_V2_GSI_m_REG_n_ADDR(m,n)                                                         (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X480 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_V2_GSI_m_REG_n_PHYS(m,n)                                                         (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X480 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_V2_GSI_m_REG_n_OFFS(m,n)                                                         (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X480 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_V2_GSI_m_REG_n_RMSK                                                              0xffffffff
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_V2_GSI_m_REG_n_MAXm                                                                       2
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_V2_GSI_m_REG_n_MAXn                                                                       2
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_V2_GSI_m_REG_n_ATTR                                                                           0x1
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_V2_GSI_m_REG_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_YELLOW_MARKER_BELOW_V2_GSI_m_REG_n_ADDR(m,n), HWIO_ECPRI_YELLOW_MARKER_BELOW_V2_GSI_m_REG_n_RMSK)
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_V2_GSI_m_REG_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_YELLOW_MARKER_BELOW_V2_GSI_m_REG_n_ADDR(m,n), mask)
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_V2_GSI_m_REG_n_ENDPOINTS_BMSK                                                    0xffffffff
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_V2_GSI_m_REG_n_ENDPOINTS_SHFT                                                             0

#define HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_V2_GSI_m_REG_n_ADDR(m,n)                                                      (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X4C0 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_V2_GSI_m_REG_n_PHYS(m,n)                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X4C0 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_V2_GSI_m_REG_n_OFFS(m,n)                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X4C0 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_V2_GSI_m_REG_n_RMSK                                                           0xffffffff
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_V2_GSI_m_REG_n_MAXm                                                                    2
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_V2_GSI_m_REG_n_MAXn                                                                    2
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_V2_GSI_m_REG_n_ATTR                                                                        0x3
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_V2_GSI_m_REG_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_V2_GSI_m_REG_n_ADDR(m,n), HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_V2_GSI_m_REG_n_RMSK)
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_V2_GSI_m_REG_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_V2_GSI_m_REG_n_ADDR(m,n), mask)
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_V2_GSI_m_REG_n_OUTI2(m,n,val)        \
                out_dword(HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_V2_GSI_m_REG_n_ADDR(m,n),val)
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_V2_GSI_m_REG_n_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_V2_GSI_m_REG_n_ADDR(m,n),mask,val,HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_V2_GSI_m_REG_n_INI2(m,n))
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_V2_GSI_m_REG_n_ENDPOINTS_BMSK                                                 0xffffffff
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_V2_GSI_m_REG_n_ENDPOINTS_SHFT                                                          0

#define HWIO_ECPRI_YELLOW_MARKER_BELOW_CLR_V2_GSI_m_REG_n_ADDR(m,n)                                                     (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X500 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_CLR_V2_GSI_m_REG_n_PHYS(m,n)                                                     (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X500 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_CLR_V2_GSI_m_REG_n_OFFS(m,n)                                                     (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X500 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_CLR_V2_GSI_m_REG_n_RMSK                                                          0xffffffff
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_CLR_V2_GSI_m_REG_n_MAXm                                                                   2
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_CLR_V2_GSI_m_REG_n_MAXn                                                                   2
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_CLR_V2_GSI_m_REG_n_ATTR                                                                       0x2
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_CLR_V2_GSI_m_REG_n_OUTI2(m,n,val)        \
                out_dword(HWIO_ECPRI_YELLOW_MARKER_BELOW_CLR_V2_GSI_m_REG_n_ADDR(m,n),val)
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_CLR_V2_GSI_m_REG_n_ENDPOINTS_BMSK                                                0xffffffff
#define HWIO_ECPRI_YELLOW_MARKER_BELOW_CLR_V2_GSI_m_REG_n_ENDPOINTS_SHFT                                                         0

#define HWIO_ECPRI_RED_MARKER_BELOW_V2_GSI_m_REG_n_ADDR(m,n)                                                            (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X540 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_RED_MARKER_BELOW_V2_GSI_m_REG_n_PHYS(m,n)                                                            (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X540 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_RED_MARKER_BELOW_V2_GSI_m_REG_n_OFFS(m,n)                                                            (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X540 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_RED_MARKER_BELOW_V2_GSI_m_REG_n_RMSK                                                                 0xffffffff
#define HWIO_ECPRI_RED_MARKER_BELOW_V2_GSI_m_REG_n_MAXm                                                                          2
#define HWIO_ECPRI_RED_MARKER_BELOW_V2_GSI_m_REG_n_MAXn                                                                          2
#define HWIO_ECPRI_RED_MARKER_BELOW_V2_GSI_m_REG_n_ATTR                                                                              0x1
#define HWIO_ECPRI_RED_MARKER_BELOW_V2_GSI_m_REG_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_RED_MARKER_BELOW_V2_GSI_m_REG_n_ADDR(m,n), HWIO_ECPRI_RED_MARKER_BELOW_V2_GSI_m_REG_n_RMSK)
#define HWIO_ECPRI_RED_MARKER_BELOW_V2_GSI_m_REG_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_RED_MARKER_BELOW_V2_GSI_m_REG_n_ADDR(m,n), mask)
#define HWIO_ECPRI_RED_MARKER_BELOW_V2_GSI_m_REG_n_ENDPOINTS_BMSK                                                       0xffffffff
#define HWIO_ECPRI_RED_MARKER_BELOW_V2_GSI_m_REG_n_ENDPOINTS_SHFT                                                                0

#define HWIO_ECPRI_RED_MARKER_BELOW_EN_V2_GSI_m_REG_n_ADDR(m,n)                                                         (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X580 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_RED_MARKER_BELOW_EN_V2_GSI_m_REG_n_PHYS(m,n)                                                         (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X580 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_RED_MARKER_BELOW_EN_V2_GSI_m_REG_n_OFFS(m,n)                                                         (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X580 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_RED_MARKER_BELOW_EN_V2_GSI_m_REG_n_RMSK                                                              0xffffffff
#define HWIO_ECPRI_RED_MARKER_BELOW_EN_V2_GSI_m_REG_n_MAXm                                                                       2
#define HWIO_ECPRI_RED_MARKER_BELOW_EN_V2_GSI_m_REG_n_MAXn                                                                       2
#define HWIO_ECPRI_RED_MARKER_BELOW_EN_V2_GSI_m_REG_n_ATTR                                                                           0x3
#define HWIO_ECPRI_RED_MARKER_BELOW_EN_V2_GSI_m_REG_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_RED_MARKER_BELOW_EN_V2_GSI_m_REG_n_ADDR(m,n), HWIO_ECPRI_RED_MARKER_BELOW_EN_V2_GSI_m_REG_n_RMSK)
#define HWIO_ECPRI_RED_MARKER_BELOW_EN_V2_GSI_m_REG_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_RED_MARKER_BELOW_EN_V2_GSI_m_REG_n_ADDR(m,n), mask)
#define HWIO_ECPRI_RED_MARKER_BELOW_EN_V2_GSI_m_REG_n_OUTI2(m,n,val)        \
                out_dword(HWIO_ECPRI_RED_MARKER_BELOW_EN_V2_GSI_m_REG_n_ADDR(m,n),val)
#define HWIO_ECPRI_RED_MARKER_BELOW_EN_V2_GSI_m_REG_n_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_ECPRI_RED_MARKER_BELOW_EN_V2_GSI_m_REG_n_ADDR(m,n),mask,val,HWIO_ECPRI_RED_MARKER_BELOW_EN_V2_GSI_m_REG_n_INI2(m,n))
#define HWIO_ECPRI_RED_MARKER_BELOW_EN_V2_GSI_m_REG_n_ENDPOINTS_BMSK                                                    0xffffffff
#define HWIO_ECPRI_RED_MARKER_BELOW_EN_V2_GSI_m_REG_n_ENDPOINTS_SHFT                                                             0

#define HWIO_ECPRI_RED_MARKER_BELOW_CLR_V2_GSI_m_REG_n_ADDR(m,n)                                                        (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X5C0 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_RED_MARKER_BELOW_CLR_V2_GSI_m_REG_n_PHYS(m,n)                                                        (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X5C0 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_RED_MARKER_BELOW_CLR_V2_GSI_m_REG_n_OFFS(m,n)                                                        (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X5C0 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_RED_MARKER_BELOW_CLR_V2_GSI_m_REG_n_RMSK                                                             0xffffffff
#define HWIO_ECPRI_RED_MARKER_BELOW_CLR_V2_GSI_m_REG_n_MAXm                                                                      2
#define HWIO_ECPRI_RED_MARKER_BELOW_CLR_V2_GSI_m_REG_n_MAXn                                                                      2
#define HWIO_ECPRI_RED_MARKER_BELOW_CLR_V2_GSI_m_REG_n_ATTR                                                                          0x2
#define HWIO_ECPRI_RED_MARKER_BELOW_CLR_V2_GSI_m_REG_n_OUTI2(m,n,val)        \
                out_dword(HWIO_ECPRI_RED_MARKER_BELOW_CLR_V2_GSI_m_REG_n_ADDR(m,n),val)
#define HWIO_ECPRI_RED_MARKER_BELOW_CLR_V2_GSI_m_REG_n_ENDPOINTS_BMSK                                                   0xffffffff
#define HWIO_ECPRI_RED_MARKER_BELOW_CLR_V2_GSI_m_REG_n_ENDPOINTS_SHFT                                                            0



#define HWIO_ECPRI_YELLOW_MARKER_SHADOW_V2_GSI_m_REG_n_ADDR(m,n)                                                        (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X600 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_YELLOW_MARKER_SHADOW_V2_GSI_m_REG_n_PHYS(m,n)                                                        (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X600 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_YELLOW_MARKER_SHADOW_V2_GSI_m_REG_n_OFFS(m,n)                                                        (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X600 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_YELLOW_MARKER_SHADOW_V2_GSI_m_REG_n_RMSK                                                             0xffffffff
#define HWIO_ECPRI_YELLOW_MARKER_SHADOW_V2_GSI_m_REG_n_MAXm                                                                      2
#define HWIO_ECPRI_YELLOW_MARKER_SHADOW_V2_GSI_m_REG_n_MAXn                                                                      2
#define HWIO_ECPRI_YELLOW_MARKER_SHADOW_V2_GSI_m_REG_n_ATTR                                                                          0x1
#define HWIO_ECPRI_YELLOW_MARKER_SHADOW_V2_GSI_m_REG_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_YELLOW_MARKER_SHADOW_V2_GSI_m_REG_n_ADDR(m,n), HWIO_ECPRI_YELLOW_MARKER_SHADOW_V2_GSI_m_REG_n_RMSK)
#define HWIO_ECPRI_YELLOW_MARKER_SHADOW_V2_GSI_m_REG_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_YELLOW_MARKER_SHADOW_V2_GSI_m_REG_n_ADDR(m,n), mask)
#define HWIO_ECPRI_YELLOW_MARKER_SHADOW_V2_GSI_m_REG_n_ENDPOINTS_BMSK                                                   0xffffffff
#define HWIO_ECPRI_YELLOW_MARKER_SHADOW_V2_GSI_m_REG_n_ENDPOINTS_SHFT                                                            0

#define HWIO_ECPRI_RED_MARKER_SHADOW_V2_GSI_m_REG_n_ADDR(m,n)                                                           (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X640 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_RED_MARKER_SHADOW_V2_GSI_m_REG_n_PHYS(m,n)                                                           (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X640 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_RED_MARKER_SHADOW_V2_GSI_m_REG_n_OFFS(m,n)                                                           (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X640 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_RED_MARKER_SHADOW_V2_GSI_m_REG_n_RMSK                                                                0xffffffff
#define HWIO_ECPRI_RED_MARKER_SHADOW_V2_GSI_m_REG_n_MAXm                                                                         2
#define HWIO_ECPRI_RED_MARKER_SHADOW_V2_GSI_m_REG_n_MAXn                                                                         2
#define HWIO_ECPRI_RED_MARKER_SHADOW_V2_GSI_m_REG_n_ATTR                                                                             0x1
#define HWIO_ECPRI_RED_MARKER_SHADOW_V2_GSI_m_REG_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_RED_MARKER_SHADOW_V2_GSI_m_REG_n_ADDR(m,n), HWIO_ECPRI_RED_MARKER_SHADOW_V2_GSI_m_REG_n_RMSK)
#define HWIO_ECPRI_RED_MARKER_SHADOW_V2_GSI_m_REG_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_RED_MARKER_SHADOW_V2_GSI_m_REG_n_ADDR(m,n), mask)
#define HWIO_ECPRI_RED_MARKER_SHADOW_V2_GSI_m_REG_n_ENDPOINTS_BMSK                                                      0xffffffff
#define HWIO_ECPRI_RED_MARKER_SHADOW_V2_GSI_m_REG_n_ENDPOINTS_SHFT                                                               0

#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_V2_GSI_m_REG_n_ADDR(m,n)                                                         (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X680 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_V2_GSI_m_REG_n_PHYS(m,n)                                                         (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X680 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_V2_GSI_m_REG_n_OFFS(m,n)                                                         (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X680 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_V2_GSI_m_REG_n_RMSK                                                              0xffffffff
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_V2_GSI_m_REG_n_MAXm                                                                       2
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_V2_GSI_m_REG_n_MAXn                                                                       2
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_V2_GSI_m_REG_n_ATTR                                                                           0x1
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_V2_GSI_m_REG_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_YELLOW_MARKER_ABOVE_V2_GSI_m_REG_n_ADDR(m,n), HWIO_ECPRI_YELLOW_MARKER_ABOVE_V2_GSI_m_REG_n_RMSK)
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_V2_GSI_m_REG_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_YELLOW_MARKER_ABOVE_V2_GSI_m_REG_n_ADDR(m,n), mask)
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_V2_GSI_m_REG_n_ENDPOINTS_BMSK                                                    0xffffffff
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_V2_GSI_m_REG_n_ENDPOINTS_SHFT                                                             0

#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_V2_GSI_m_REG_n_ADDR(m,n)                                                      (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X6C0 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_V2_GSI_m_REG_n_PHYS(m,n)                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X6C0 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_V2_GSI_m_REG_n_OFFS(m,n)                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X6C0 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_V2_GSI_m_REG_n_RMSK                                                           0xffffffff
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_V2_GSI_m_REG_n_MAXm                                                                    2
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_V2_GSI_m_REG_n_MAXn                                                                    2
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_V2_GSI_m_REG_n_ATTR                                                                        0x3
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_V2_GSI_m_REG_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_V2_GSI_m_REG_n_ADDR(m,n), HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_V2_GSI_m_REG_n_RMSK)
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_V2_GSI_m_REG_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_V2_GSI_m_REG_n_ADDR(m,n), mask)
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_V2_GSI_m_REG_n_OUTI2(m,n,val)        \
                out_dword(HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_V2_GSI_m_REG_n_ADDR(m,n),val)
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_V2_GSI_m_REG_n_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_V2_GSI_m_REG_n_ADDR(m,n),mask,val,HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_V2_GSI_m_REG_n_INI2(m,n))
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_V2_GSI_m_REG_n_ENDPOINTS_BMSK                                                 0xffffffff
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_V2_GSI_m_REG_n_ENDPOINTS_SHFT                                                          0

#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_CLR_V2_GSI_m_REG_n_ADDR(m,n)                                                     (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X700 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_CLR_V2_GSI_m_REG_n_PHYS(m,n)                                                     (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X700 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_CLR_V2_GSI_m_REG_n_OFFS(m,n)                                                     (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X700 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_CLR_V2_GSI_m_REG_n_RMSK                                                          0xffffffff
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_CLR_V2_GSI_m_REG_n_MAXm                                                                   2
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_CLR_V2_GSI_m_REG_n_MAXn                                                                   2
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_CLR_V2_GSI_m_REG_n_ATTR                                                                       0x2
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_CLR_V2_GSI_m_REG_n_OUTI2(m,n,val)        \
                out_dword(HWIO_ECPRI_YELLOW_MARKER_ABOVE_CLR_V2_GSI_m_REG_n_ADDR(m,n),val)
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_CLR_V2_GSI_m_REG_n_ENDPOINTS_BMSK                                                0xffffffff
#define HWIO_ECPRI_YELLOW_MARKER_ABOVE_CLR_V2_GSI_m_REG_n_ENDPOINTS_SHFT                                                         0

#define HWIO_ECPRI_RED_MARKER_ABOVE_V2_GSI_m_REG_n_ADDR(m,n)                                                            (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X740 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_RED_MARKER_ABOVE_V2_GSI_m_REG_n_PHYS(m,n)                                                            (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X740 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_RED_MARKER_ABOVE_V2_GSI_m_REG_n_OFFS(m,n)                                                            (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X740 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_RED_MARKER_ABOVE_V2_GSI_m_REG_n_RMSK                                                                 0xffffffff
#define HWIO_ECPRI_RED_MARKER_ABOVE_V2_GSI_m_REG_n_MAXm                                                                          2
#define HWIO_ECPRI_RED_MARKER_ABOVE_V2_GSI_m_REG_n_MAXn                                                                          2
#define HWIO_ECPRI_RED_MARKER_ABOVE_V2_GSI_m_REG_n_ATTR                                                                              0x1
#define HWIO_ECPRI_RED_MARKER_ABOVE_V2_GSI_m_REG_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_RED_MARKER_ABOVE_V2_GSI_m_REG_n_ADDR(m,n), HWIO_ECPRI_RED_MARKER_ABOVE_V2_GSI_m_REG_n_RMSK)
#define HWIO_ECPRI_RED_MARKER_ABOVE_V2_GSI_m_REG_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_RED_MARKER_ABOVE_V2_GSI_m_REG_n_ADDR(m,n), mask)
#define HWIO_ECPRI_RED_MARKER_ABOVE_V2_GSI_m_REG_n_ENDPOINTS_BMSK                                                       0xffffffff
#define HWIO_ECPRI_RED_MARKER_ABOVE_V2_GSI_m_REG_n_ENDPOINTS_SHFT                                                                0

#define HWIO_ECPRI_RED_MARKER_ABOVE_EN_V2_GSI_m_REG_n_ADDR(m,n)                                                         (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X780 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_RED_MARKER_ABOVE_EN_V2_GSI_m_REG_n_PHYS(m,n)                                                         (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X780 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_RED_MARKER_ABOVE_EN_V2_GSI_m_REG_n_OFFS(m,n)                                                         (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X780 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_RED_MARKER_ABOVE_EN_V2_GSI_m_REG_n_RMSK                                                              0xffffffff
#define HWIO_ECPRI_RED_MARKER_ABOVE_EN_V2_GSI_m_REG_n_MAXm                                                                       2
#define HWIO_ECPRI_RED_MARKER_ABOVE_EN_V2_GSI_m_REG_n_MAXn                                                                       2
#define HWIO_ECPRI_RED_MARKER_ABOVE_EN_V2_GSI_m_REG_n_ATTR                                                                           0x3
#define HWIO_ECPRI_RED_MARKER_ABOVE_EN_V2_GSI_m_REG_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_RED_MARKER_ABOVE_EN_V2_GSI_m_REG_n_ADDR(m,n), HWIO_ECPRI_RED_MARKER_ABOVE_EN_V2_GSI_m_REG_n_RMSK)
#define HWIO_ECPRI_RED_MARKER_ABOVE_EN_V2_GSI_m_REG_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_RED_MARKER_ABOVE_EN_V2_GSI_m_REG_n_ADDR(m,n), mask)
#define HWIO_ECPRI_RED_MARKER_ABOVE_EN_V2_GSI_m_REG_n_OUTI2(m,n,val)        \
                out_dword(HWIO_ECPRI_RED_MARKER_ABOVE_EN_V2_GSI_m_REG_n_ADDR(m,n),val)
#define HWIO_ECPRI_RED_MARKER_ABOVE_EN_V2_GSI_m_REG_n_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_ECPRI_RED_MARKER_ABOVE_EN_V2_GSI_m_REG_n_ADDR(m,n),mask,val,HWIO_ECPRI_RED_MARKER_ABOVE_EN_V2_GSI_m_REG_n_INI2(m,n))
#define HWIO_ECPRI_RED_MARKER_ABOVE_EN_V2_GSI_m_REG_n_ENDPOINTS_BMSK                                                    0xffffffff
#define HWIO_ECPRI_RED_MARKER_ABOVE_EN_V2_GSI_m_REG_n_ENDPOINTS_SHFT                                                             0

#define HWIO_ECPRI_RED_MARKER_ABOVE_CLR_V2_GSI_m_REG_n_ADDR(m,n)                                                        (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X7C0 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_RED_MARKER_ABOVE_CLR_V2_GSI_m_REG_n_PHYS(m,n)                                                        (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X7C0 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_RED_MARKER_ABOVE_CLR_V2_GSI_m_REG_n_OFFS(m,n)                                                        (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X7C0 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_RED_MARKER_ABOVE_CLR_V2_GSI_m_REG_n_RMSK                                                             0xffffffff
#define HWIO_ECPRI_RED_MARKER_ABOVE_CLR_V2_GSI_m_REG_n_MAXm                                                                      2
#define HWIO_ECPRI_RED_MARKER_ABOVE_CLR_V2_GSI_m_REG_n_MAXn                                                                      2
#define HWIO_ECPRI_RED_MARKER_ABOVE_CLR_V2_GSI_m_REG_n_ATTR                                                                          0x2
#define HWIO_ECPRI_RED_MARKER_ABOVE_CLR_V2_GSI_m_REG_n_OUTI2(m,n,val)        \
                out_dword(HWIO_ECPRI_RED_MARKER_ABOVE_CLR_V2_GSI_m_REG_n_ADDR(m,n),val)
#define HWIO_ECPRI_RED_MARKER_ABOVE_CLR_V2_GSI_m_REG_n_ENDPOINTS_BMSK                                                   0xffffffff
#define HWIO_ECPRI_RED_MARKER_ABOVE_CLR_V2_GSI_m_REG_n_ENDPOINTS_SHFT                                                            0

#define HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_ADDR(m,n)                           (ECPRI_DMA_NS_RESTRICTED_REG_BASE      + 0X0 + (0x1000*(m)) + (0x20*(n)))
#define HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_PHYS(m,n)                           (ECPRI_DMA_NS_RESTRICTED_REG_BASE_PHYS + 0X0 + (0x1000*(m)) + (0x20*(n)))
#define HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_OFFS(m,n)                           (ECPRI_DMA_NS_RESTRICTED_REG_BASE_OFFS + 0X0 + (0x1000*(m)) + (0x20*(n)))
#define HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_RMSK                                0x80003fff
#define HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_MAXm                                         2
#define HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_MAXn                                        36
#define HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_ATTR                                             0x3
#define HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_ADDR(m,n), HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_RMSK)
#define HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_ADDR(m,n), mask)
#define HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_OUTI2(m,n,val)        \
                out_dword(HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_ADDR(m,n),val)
#define HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_ADDR(m,n),mask,val,HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_INI2(m,n))
#define HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_USE_DEST_CFG_BMSK                   0x80000000
#define HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_USE_DEST_CFG_SHFT                           31
#define HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_LOOPBACK_GID_BMSK                       0x3000
#define HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_LOOPBACK_GID_SHFT                           12
#define HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_ARB_WEIGHT_BMSK                          0xf00
#define HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_ARB_WEIGHT_SHFT                              8
#define HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_DEST_MEM_CHANNEL_BMSK                     0xff
#define HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_DEST_MEM_CHANNEL_SHFT                        0

#define HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_ADDR(m,n)                           (ECPRI_DMA_NS_RESTRICTED_REG_BASE      + 0X4 + (0x1000*(m)) + (0x20*(n)))
#define HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_PHYS(m,n)                           (ECPRI_DMA_NS_RESTRICTED_REG_BASE_PHYS + 0X4 + (0x1000*(m)) + (0x20*(n)))
#define HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_OFFS(m,n)                           (ECPRI_DMA_NS_RESTRICTED_REG_BASE_OFFS + 0X4 + (0x1000*(m)) + (0x20*(n)))
#define HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_RMSK                                0xeffffff3
#define HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_MAXm                                         2
#define HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_MAXn                                        36
#define HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_ATTR                                             0x3
#define HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_ADDR(m,n), HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_RMSK)
#define HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_ADDR(m,n), mask)
#define HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_OUTI2(m,n,val)        \
                out_dword(HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_ADDR(m,n),val)
#define HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_ADDR(m,n),mask,val,HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_INI2(m,n))
#define HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_NFAPI_WITHOUT_OFFLOAD_BMSK          0x80000000
#define HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_NFAPI_WITHOUT_OFFLOAD_SHFT                  31
#define HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_PRE_HDR_EN_BMSK                     0x40000000
#define HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_PRE_HDR_EN_SHFT                             30
#define HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_LOOPBACK_EN_BMSK                    0x20000000
#define HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_LOOPBACK_EN_SHFT                            29
#define HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_XBAR_TUSER_BMSK                      0xfffff00
#define HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_XBAR_TUSER_SHFT                              8
#define HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_XBAR_TID_BMSK                             0xf0
#define HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_XBAR_TID_SHFT                                4
#define HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_DEST_STREAM_BMSK                           0x3
#define HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_DEST_STREAM_SHFT                             0


#define HWIO_ECPRI_ENDP_CFG_AGGR_V2_GSI_m_CH_n_ADDR(m,n)                                                                (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X1000 + (0x2000*(m)) + (0x40*(n)))
#define HWIO_ECPRI_ENDP_CFG_AGGR_V2_GSI_m_CH_n_PHYS(m,n)                                                                (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X1000 + (0x2000*(m)) + (0x40*(n)))
#define HWIO_ECPRI_ENDP_CFG_AGGR_V2_GSI_m_CH_n_OFFS(m,n)                                                                (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X1000 + (0x2000*(m)) + (0x40*(n)))
#define HWIO_ECPRI_ENDP_CFG_AGGR_V2_GSI_m_CH_n_RMSK                                                                            0x1
#define HWIO_ECPRI_ENDP_CFG_AGGR_V2_GSI_m_CH_n_MAXm                                                                              2
#define HWIO_ECPRI_ENDP_CFG_AGGR_V2_GSI_m_CH_n_MAXn                                                                             73
#define HWIO_ECPRI_ENDP_CFG_AGGR_V2_GSI_m_CH_n_ATTR                                                                                  0x3
#define HWIO_ECPRI_ENDP_CFG_AGGR_V2_GSI_m_CH_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_ENDP_CFG_AGGR_V2_GSI_m_CH_n_ADDR(m,n), HWIO_ECPRI_ENDP_CFG_AGGR_V2_GSI_m_CH_n_RMSK)
#define HWIO_ECPRI_ENDP_CFG_AGGR_V2_GSI_m_CH_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_ENDP_CFG_AGGR_V2_GSI_m_CH_n_ADDR(m,n), mask)
#define HWIO_ECPRI_ENDP_CFG_AGGR_V2_GSI_m_CH_n_OUTI2(m,n,val)        \
                out_dword(HWIO_ECPRI_ENDP_CFG_AGGR_V2_GSI_m_CH_n_ADDR(m,n),val)
#define HWIO_ECPRI_ENDP_CFG_AGGR_V2_GSI_m_CH_n_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_ECPRI_ENDP_CFG_AGGR_V2_GSI_m_CH_n_ADDR(m,n),mask,val,HWIO_ECPRI_ENDP_CFG_AGGR_V2_GSI_m_CH_n_INI2(m,n))
#define HWIO_ECPRI_ENDP_CFG_AGGR_V2_GSI_m_CH_n_AGGR_TYPE_BMSK                                                                  0x1
#define HWIO_ECPRI_ENDP_CFG_AGGR_V2_GSI_m_CH_n_AGGR_TYPE_SHFT                                                                    0

#define HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_ADDR(m,n)                                                                 (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x00001004 + 0x2000 * (m) + 0x40 * (n))
#define HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_PHYS(m,n)                                                                 (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x00001004 + 0x2000 * (m) + 0x40 * (n))
#define HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_OFFS(m,n)                                                                 (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x00001004 + 0x2000 * (m) + 0x40 * (n))
#define HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_RMSK                                                                          0x1101
#define HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_MAXm                                                                               2
#define HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_MAXn                                                                              73
#define HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_ATTR                                                                             0x3
#define HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_INI2(m,n)        \
        in_dword_masked(HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_ADDR(m,n), HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_RMSK)
#define HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_INMI2(m,n,mask)    \
        in_dword_masked(HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_ADDR(m,n), mask)
#define HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_OUTI2(m,n,val)    \
        out_dword(HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_ADDR(m,n),val)
#define HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_OUTMI2(m,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_ADDR(m,n),mask,val,HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_INI2(m,n))
#define HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_LOW_LATENCY_EN_BMSK                                                           0x1000
#define HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_LOW_LATENCY_EN_SHFT                                                              0xc
#define HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_ENDP_FLUSH_BMSK                                                                0x100
#define HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_ENDP_FLUSH_SHFT                                                                  0x8
#define HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_ENDP_EN_BMSK                                                                     0x1
#define HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_ENDP_EN_SHFT                                                                     0x0

#define HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_ADDR(m,n)                                                   (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X1008 + (0x2000*(m)) + (0x40*(n)))
#define HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_PHYS(m,n)                                                   (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X1008 + (0x2000*(m)) + (0x40*(n)))
#define HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_OFFS(m,n)                                                   (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X1008 + (0x2000*(m)) + (0x40*(n)))
#define HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_RMSK                                                        0xfc00fc00
#define HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_MAXm                                                                 2
#define HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_MAXn                                                                73
#define HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_ATTR                                                                     0x3
#define HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_ADDR(m,n), HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_RMSK)
#define HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_ADDR(m,n), mask)
#define HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_OUTI2(m,n,val)        \
                out_dword(HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_ADDR(m,n),val)
#define HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_ADDR(m,n),mask,val,HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_INI2(m,n))
#define HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_ECPRI_RED_MARKER_CFG_BMSK                                   0xfc000000
#define HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_ECPRI_RED_MARKER_CFG_SHFT                                           26
#define HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_ECPRI_YELLOW_MARKER_CFG_BMSK                                    0xfc00
#define HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_ECPRI_YELLOW_MARKER_CFG_SHFT                                        10


#define HWIO_ECPRI_ENDP_INIT_CTRL_STATUS_V2_GSI_m_CH_n_ADDR(m,n)                                                        (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X100C + (0x2000*(m)) + (0x40*(n)))
#define HWIO_ECPRI_ENDP_INIT_CTRL_STATUS_V2_GSI_m_CH_n_PHYS(m,n)                                                        (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X100C + (0x2000*(m)) + (0x40*(n)))
#define HWIO_ECPRI_ENDP_INIT_CTRL_STATUS_V2_GSI_m_CH_n_OFFS(m,n)                                                        (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X100C + (0x2000*(m)) + (0x40*(n)))
#define HWIO_ECPRI_ENDP_INIT_CTRL_STATUS_V2_GSI_m_CH_n_RMSK                                                                    0x3
#define HWIO_ECPRI_ENDP_INIT_CTRL_STATUS_V2_GSI_m_CH_n_MAXm                                                                      2
#define HWIO_ECPRI_ENDP_INIT_CTRL_STATUS_V2_GSI_m_CH_n_MAXn                                                                     73
#define HWIO_ECPRI_ENDP_INIT_CTRL_STATUS_V2_GSI_m_CH_n_ATTR                                                                          0x1
#define HWIO_ECPRI_ENDP_INIT_CTRL_STATUS_V2_GSI_m_CH_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_ENDP_INIT_CTRL_STATUS_V2_GSI_m_CH_n_ADDR(m,n), HWIO_ECPRI_ENDP_INIT_CTRL_STATUS_V2_GSI_m_CH_n_RMSK)
#define HWIO_ECPRI_ENDP_INIT_CTRL_STATUS_V2_GSI_m_CH_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_ENDP_INIT_CTRL_STATUS_V2_GSI_m_CH_n_ADDR(m,n), mask)
#define HWIO_ECPRI_ENDP_INIT_CTRL_STATUS_V2_GSI_m_CH_n_CHANNEL_STATE_BMSK                                                      0x3
#define HWIO_ECPRI_ENDP_INIT_CTRL_STATUS_V2_GSI_m_CH_n_CHANNEL_STATE_SHFT                                                        0

#define HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_ADDR(m,n)                                                                (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X1010 + (0x2000*(m)) + (0x40*(n)))
#define HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_PHYS(m,n)                                                                (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X1010 + (0x2000*(m)) + (0x40*(n)))
#define HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_OFFS(m,n)                                                                (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X1010 + (0x2000*(m)) + (0x40*(n)))
#define HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_RMSK                                                                            0xf
#define HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_MAXm                                                                              2
#define HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_MAXn                                                                             73
#define HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_ATTR                                                                                  0x3
#define HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_ADDR(m,n), HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_RMSK)
#define HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_ADDR(m,n), mask)
#define HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_OUTI2(m,n,val)        \
                out_dword(HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_ADDR(m,n),val)
#define HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_ADDR(m,n),mask,val,HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_INI2(m,n))
#define HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_TPH_BMSK                                                                        0xc
#define HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_TPH_SHFT                                                                          2
#define HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_NOSNOOP_BMSK                                                                    0x2
#define HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_NOSNOOP_SHFT                                                                      1
#define HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_RELAX_ORDER_BMSK                                                                0x1
#define HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_RELAX_ORDER_SHFT                                                                  0

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_DMA_NS_RESTRICTED
 *--------------------------------------------------------------------------*/


#define HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_V2_GSI_m_CH_n_ADDR(m,n)               (ECPRI_DMA_NS_RESTRICTED_REG_BASE      + 0X8 + (0x1000*(m)) + (0x20*(n)))
#define HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_V2_GSI_m_CH_n_PHYS(m,n)               (ECPRI_DMA_NS_RESTRICTED_REG_BASE_PHYS + 0X8 + (0x1000*(m)) + (0x20*(n)))
#define HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_V2_GSI_m_CH_n_OFFS(m,n)               (ECPRI_DMA_NS_RESTRICTED_REG_BASE_OFFS + 0X8 + (0x1000*(m)) + (0x20*(n)))
#define HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_V2_GSI_m_CH_n_RMSK                           0x3
#define HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_V2_GSI_m_CH_n_MAXm                             2
#define HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_V2_GSI_m_CH_n_MAXn                            73
#define HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_V2_GSI_m_CH_n_ATTR                                 0x3
#define HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_V2_GSI_m_CH_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_V2_GSI_m_CH_n_ADDR(m,n), HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_V2_GSI_m_CH_n_RMSK)
#define HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_V2_GSI_m_CH_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_V2_GSI_m_CH_n_ADDR(m,n), mask)
#define HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_V2_GSI_m_CH_n_OUTI2(m,n,val)        \
                out_dword(HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_V2_GSI_m_CH_n_ADDR(m,n),val)
#define HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_V2_GSI_m_CH_n_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_V2_GSI_m_CH_n_ADDR(m,n),mask,val,HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_V2_GSI_m_CH_n_INI2(m,n))
#define HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_V2_GSI_m_CH_n_VM_ID_BMSK                     0x3
#define HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_V2_GSI_m_CH_n_VM_ID_SHFT                       0


#define HWIO_ECPRI_SNOC_MONITORING_CFG_V2_ADDR                                                                          (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x7008)
#define HWIO_ECPRI_SNOC_MONITORING_CFG_V2_PHYS                                                                          (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x7008)
#define HWIO_ECPRI_SNOC_MONITORING_CFG_V2_OFFS                                                                          (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x7008)
#define HWIO_ECPRI_SNOC_MONITORING_CFG_V2_RMSK                                                                                 0x1
#define HWIO_ECPRI_SNOC_MONITORING_CFG_V2_ATTR                                                                                       0x3
#define HWIO_ECPRI_SNOC_MONITORING_CFG_V2_IN                    \
                in_dword(HWIO_ECPRI_SNOC_MONITORING_CFG_V2_ADDR)
#define HWIO_ECPRI_SNOC_MONITORING_CFG_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_SNOC_MONITORING_CFG_V2_ADDR, m)
#define HWIO_ECPRI_SNOC_MONITORING_CFG_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_SNOC_MONITORING_CFG_V2_ADDR,v)
#define HWIO_ECPRI_SNOC_MONITORING_CFG_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_SNOC_MONITORING_CFG_V2_ADDR,m,v,HWIO_ECPRI_SNOC_MONITORING_CFG_V2_IN)
#define HWIO_ECPRI_SNOC_MONITORING_CFG_V2_ENABLE_BMSK                                                                          0x1
#define HWIO_ECPRI_SNOC_MONITORING_CFG_V2_ENABLE_SHFT                                                                            0


#define HWIO_ECPRI_QMB0_SNOC_MONITOR_CNT_V2_ADDR                                                                        (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x700c)
#define HWIO_ECPRI_QMB0_SNOC_MONITOR_CNT_V2_PHYS                                                                        (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x700c)
#define HWIO_ECPRI_QMB0_SNOC_MONITOR_CNT_V2_OFFS                                                                        (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x700c)
#define HWIO_ECPRI_QMB0_SNOC_MONITOR_CNT_V2_RMSK                                                                        0x1f7df7df
#define HWIO_ECPRI_QMB0_SNOC_MONITOR_CNT_V2_ATTR                                                                                     0x1
#define HWIO_ECPRI_QMB0_SNOC_MONITOR_CNT_V2_IN                    \
                in_dword(HWIO_ECPRI_QMB0_SNOC_MONITOR_CNT_V2_ADDR)
#define HWIO_ECPRI_QMB0_SNOC_MONITOR_CNT_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_QMB0_SNOC_MONITOR_CNT_V2_ADDR, m)
#define HWIO_ECPRI_QMB0_SNOC_MONITOR_CNT_V2_B_VALUE_BMSK                                                                0x1f000000
#define HWIO_ECPRI_QMB0_SNOC_MONITOR_CNT_V2_B_VALUE_SHFT                                                                        24
#define HWIO_ECPRI_QMB0_SNOC_MONITOR_CNT_V2_W_VALUE_BMSK                                                                  0x7c0000
#define HWIO_ECPRI_QMB0_SNOC_MONITOR_CNT_V2_W_VALUE_SHFT                                                                        18
#define HWIO_ECPRI_QMB0_SNOC_MONITOR_CNT_V2_R_VALUE_BMSK                                                                   0x1f000
#define HWIO_ECPRI_QMB0_SNOC_MONITOR_CNT_V2_R_VALUE_SHFT                                                                        12
#define HWIO_ECPRI_QMB0_SNOC_MONITOR_CNT_V2_AW_VALUE_BMSK                                                                    0x7c0
#define HWIO_ECPRI_QMB0_SNOC_MONITOR_CNT_V2_AW_VALUE_SHFT                                                                        6
#define HWIO_ECPRI_QMB0_SNOC_MONITOR_CNT_V2_AR_VALUE_BMSK                                                                     0x1f
#define HWIO_ECPRI_QMB0_SNOC_MONITOR_CNT_V2_AR_VALUE_SHFT                                                                        0

#define HWIO_ECPRI_QMB1_SNOC_MONITOR_CNT_V2_ADDR                                                                        (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x7010)
#define HWIO_ECPRI_QMB1_SNOC_MONITOR_CNT_V2_PHYS                                                                        (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x7010)
#define HWIO_ECPRI_QMB1_SNOC_MONITOR_CNT_V2_OFFS                                                                        (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x7010)
#define HWIO_ECPRI_QMB1_SNOC_MONITOR_CNT_V2_RMSK                                                                        0x1f7df7df
#define HWIO_ECPRI_QMB1_SNOC_MONITOR_CNT_V2_ATTR                                                                                     0x1
#define HWIO_ECPRI_QMB1_SNOC_MONITOR_CNT_V2_IN                    \
                in_dword(HWIO_ECPRI_QMB1_SNOC_MONITOR_CNT_V2_ADDR)
#define HWIO_ECPRI_QMB1_SNOC_MONITOR_CNT_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_QMB1_SNOC_MONITOR_CNT_V2_ADDR, m)
#define HWIO_ECPRI_QMB1_SNOC_MONITOR_CNT_V2_B_VALUE_BMSK                                                                0x1f000000
#define HWIO_ECPRI_QMB1_SNOC_MONITOR_CNT_V2_B_VALUE_SHFT                                                                        24
#define HWIO_ECPRI_QMB1_SNOC_MONITOR_CNT_V2_W_VALUE_BMSK                                                                  0x7c0000
#define HWIO_ECPRI_QMB1_SNOC_MONITOR_CNT_V2_W_VALUE_SHFT                                                                        18
#define HWIO_ECPRI_QMB1_SNOC_MONITOR_CNT_V2_R_VALUE_BMSK                                                                   0x1f000
#define HWIO_ECPRI_QMB1_SNOC_MONITOR_CNT_V2_R_VALUE_SHFT                                                                        12
#define HWIO_ECPRI_QMB1_SNOC_MONITOR_CNT_V2_AW_VALUE_BMSK                                                                    0x7c0
#define HWIO_ECPRI_QMB1_SNOC_MONITOR_CNT_V2_AW_VALUE_SHFT                                                                        6
#define HWIO_ECPRI_QMB1_SNOC_MONITOR_CNT_V2_AR_VALUE_BMSK                                                                     0x1f
#define HWIO_ECPRI_QMB1_SNOC_MONITOR_CNT_V2_AR_VALUE_SHFT                                                                        0

#define HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_ADDR                                                                         (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x7014)
#define HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_PHYS                                                                         (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x7014)
#define HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_OFFS                                                                         (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x7014)
#define HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_RMSK                                                                         0x3f7df7df
#define HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_ATTR                                                                                      0x3
#define HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_IN                    \
                in_dword(HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_ADDR)
#define HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_ADDR, m)
#define HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_ADDR,v)
#define HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_ADDR,m,v,HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_IN)
#define HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_SYNC_PULSE_BMSK                                                              0x20000000
#define HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_SYNC_PULSE_SHFT                                                                      29
#define HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_B_VALUE_BMSK                                                                 0x1f000000
#define HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_B_VALUE_SHFT                                                                         24
#define HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_W_VALUE_BMSK                                                                   0x7c0000
#define HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_W_VALUE_SHFT                                                                         18
#define HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_R_VALUE_BMSK                                                                    0x1f000
#define HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_R_VALUE_SHFT                                                                         12
#define HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_AW_VALUE_BMSK                                                                     0x7c0
#define HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_AW_VALUE_SHFT                                                                         6
#define HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_AR_VALUE_BMSK                                                                      0x1f
#define HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_AR_VALUE_SHFT                                                                         0


#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_V2_GSI_m_ADDR(m)                                                             (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X7018 + (0x4*(m)))
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_V2_GSI_m_PHYS(m)                                                             (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X7018 + (0x4*(m)))
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_V2_GSI_m_OFFS(m)                                                             (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X7018 + (0x4*(m)))
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_V2_GSI_m_RMSK                                                                     0x1ff
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_V2_GSI_m_MAXm                                                                         2
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_V2_GSI_m_ATTR                                                                             0x1
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_V2_GSI_m_INI(m)                \
                in_dword_masked(HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_V2_GSI_m_ADDR(m), HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_V2_GSI_m_RMSK)
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_V2_GSI_m_INMI(m,mask)        \
                in_dword_masked(HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_V2_GSI_m_ADDR(m), mask)
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_V2_GSI_m_CMDQ_DEPTH_BMSK                                                          0x1fe
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_V2_GSI_m_CMDQ_DEPTH_SHFT                                                              1
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_V2_GSI_m_CMDQ_FULL_BMSK                                                             0x1
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_V2_GSI_m_CMDQ_FULL_SHFT                                                               0

#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_GSI_m_ADDR(m)                                                             (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X7028 + (0x4*(m)))
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_GSI_m_PHYS(m)                                                             (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X7028 + (0x4*(m)))
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_GSI_m_OFFS(m)                                                             (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X7028 + (0x4*(m)))
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_GSI_m_RMSK                                                                      0xff
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_GSI_m_MAXm                                                                         2
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_GSI_m_ATTR                                                                             0x1
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_GSI_m_INI(m)                \
                in_dword_masked(HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_GSI_m_ADDR(m), HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_GSI_m_RMSK)
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_GSI_m_INMI(m,mask)        \
                in_dword_masked(HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_GSI_m_ADDR(m), mask)
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_GSI_m_CMDQ_DEPTH_BMSK                                                           0xfe
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_GSI_m_CMDQ_DEPTH_SHFT                                                              1
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_GSI_m_CMDQ_FULL_BMSK                                                             0x1
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_GSI_m_CMDQ_FULL_SHFT                                                               0

#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_ADDR(m,n)                                               (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X7040 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_PHYS(m,n)                                               (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X7040 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_OFFS(m,n)                                               (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X7040 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_RMSK                                                    0xffffffff
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_MAXm                                                             2
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_MAXn                                                             2
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_ATTR                                                                 0x1
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_ADDR(m,n), HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_RMSK)
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_ADDR(m,n), mask)
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_CMDQ_EMPTY_BMSK                                         0xffffffff
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_CMDQ_EMPTY_SHFT                                                  0

#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_ADDR(m,n)                                                       (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X7080 + (0x200*(m)) + (0x4*(n)))
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_PHYS(m,n)                                                       (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X7080 + (0x200*(m)) + (0x4*(n)))
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_OFFS(m,n)                                                       (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X7080 + (0x200*(m)) + (0x4*(n)))
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_RMSK                                                                  0xff
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_MAXm                                                                     2
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_MAXn                                                                    73
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_ATTR                                                                         0x1
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_DST_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_ADDR(m,n), HWIO_ECPRI_DST_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_RMSK)
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_DST_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_ADDR(m,n), mask)
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_FIFO_COUNT_BMSK                                                       0xff
#define HWIO_ECPRI_DST_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_FIFO_COUNT_SHFT                                                          0

#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_ADDR(m,n)                                               (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X7600 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_PHYS(m,n)                                               (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X7600 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_OFFS(m,n)                                               (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X7600 + (0x10*(m)) + (0x4*(n)))
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_RMSK                                                    0xffffffff
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_MAXm                                                             2
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_MAXn                                                             1
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_ATTR                                                                 0x1
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_ADDR(m,n), HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_RMSK)
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_ADDR(m,n), mask)
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_CMDQ_EMPTY_BMSK                                         0xffffffff
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_CMDQ_EMPTY_SHFT                                                  0

#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_ADDR(m,n)                                                       (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X7640 + (0x200*(m)) + (0x4*(n)))
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_PHYS(m,n)                                                       (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X7640 + (0x200*(m)) + (0x4*(n)))
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_OFFS(m,n)                                                       (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X7640 + (0x200*(m)) + (0x4*(n)))
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_RMSK                                                                  0xff
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_MAXm                                                                     2
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_MAXn                                                                    36
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_ATTR                                                                         0x1
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_SRC_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_ADDR(m,n), HWIO_ECPRI_SRC_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_RMSK)
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_SRC_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_ADDR(m,n), mask)
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_FIFO_COUNT_BMSK                                                       0xff
#define HWIO_ECPRI_SRC_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_FIFO_COUNT_SHFT                                                          0

#define HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_ADDR(m,n)                                                          (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X8000 + (0x200*(m)) + (0x4*(n)))
#define HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_PHYS(m,n)                                                          (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X8000 + (0x200*(m)) + (0x4*(n)))
#define HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_OFFS(m,n)                                                          (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X8000 + (0x200*(m)) + (0x4*(n)))
#define HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_RMSK                                                                  0xfffff
#define HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_MAXm                                                                        2
#define HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_MAXn                                                                       73
#define HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_ATTR                                                                            0x1
#define HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_ADDR(m,n), HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_RMSK)
#define HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_ADDR(m,n), mask)
#define HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_FIFO_HEAD_IS_BUBBLE_BMSK                                              0x80000
#define HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_FIFO_HEAD_IS_BUBBLE_SHFT                                                   19
#define HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_FIFO_FULL_BMSK                                                        0x40000
#define HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_FIFO_FULL_SHFT                                                             18
#define HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_FIFO_ALMOST_FULL_BMSK                                                 0x20000
#define HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_FIFO_ALMOST_FULL_SHFT                                                      17
#define HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_FIFO_EMPTY_BMSK                                                       0x10000
#define HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_FIFO_EMPTY_SHFT                                                            16
#define HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_FIFO_RD_PTR_BMSK                                                       0xff00
#define HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_FIFO_RD_PTR_SHFT                                                            8
#define HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_FIFO_WR_PTR_BMSK                                                         0xff
#define HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_FIFO_WR_PTR_SHFT                                                            0

#define HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_ADDR(m,n)                                                          (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X8800 + (0x200*(m)) + (0x4*(n)))
#define HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_PHYS(m,n)                                                          (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X8800 + (0x200*(m)) + (0x4*(n)))
#define HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_OFFS(m,n)                                                          (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X8800 + (0x200*(m)) + (0x4*(n)))
#define HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_RMSK                                                                  0xfffff
#define HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_MAXm                                                                        2
#define HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_MAXn                                                                       73
#define HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_ATTR                                                                            0x1
#define HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_ADDR(m,n), HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_RMSK)
#define HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_ADDR(m,n), mask)
#define HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_FIFO_HEAD_IS_BUBBLE_BMSK                                              0x80000
#define HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_FIFO_HEAD_IS_BUBBLE_SHFT                                                   19
#define HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_FIFO_FULL_BMSK                                                        0x40000
#define HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_FIFO_FULL_SHFT                                                             18
#define HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_FIFO_ALMOST_FULL_BMSK                                                 0x20000
#define HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_FIFO_ALMOST_FULL_SHFT                                                      17
#define HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_FIFO_EMPTY_BMSK                                                       0x10000
#define HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_FIFO_EMPTY_SHFT                                                            16
#define HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_FIFO_RD_PTR_BMSK                                                       0xff00
#define HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_FIFO_RD_PTR_SHFT                                                            8
#define HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_FIFO_WR_PTR_BMSK                                                         0xff
#define HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_FIFO_WR_PTR_SHFT                                                            0

#define HWIO_ECPRI_ENDP_GSI_CONS_BYTES_TLV_V2_GSI_m_CH_n_ADDR(m,n)                                                      (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X9000 + (0x200*(m)) + (0x4*(n)))
#define HWIO_ECPRI_ENDP_GSI_CONS_BYTES_TLV_V2_GSI_m_CH_n_PHYS(m,n)                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X9000 + (0x200*(m)) + (0x4*(n)))
#define HWIO_ECPRI_ENDP_GSI_CONS_BYTES_TLV_V2_GSI_m_CH_n_OFFS(m,n)                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X9000 + (0x200*(m)) + (0x4*(n)))
#define HWIO_ECPRI_ENDP_GSI_CONS_BYTES_TLV_V2_GSI_m_CH_n_RMSK                                                             0x1fffff
#define HWIO_ECPRI_ENDP_GSI_CONS_BYTES_TLV_V2_GSI_m_CH_n_MAXm                                                                    2
#define HWIO_ECPRI_ENDP_GSI_CONS_BYTES_TLV_V2_GSI_m_CH_n_MAXn                                                                   73
#define HWIO_ECPRI_ENDP_GSI_CONS_BYTES_TLV_V2_GSI_m_CH_n_ATTR                                                                        0x1
#define HWIO_ECPRI_ENDP_GSI_CONS_BYTES_TLV_V2_GSI_m_CH_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_ENDP_GSI_CONS_BYTES_TLV_V2_GSI_m_CH_n_ADDR(m,n), HWIO_ECPRI_ENDP_GSI_CONS_BYTES_TLV_V2_GSI_m_CH_n_RMSK)
#define HWIO_ECPRI_ENDP_GSI_CONS_BYTES_TLV_V2_GSI_m_CH_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_ENDP_GSI_CONS_BYTES_TLV_V2_GSI_m_CH_n_ADDR(m,n), mask)
#define HWIO_ECPRI_ENDP_GSI_CONS_BYTES_TLV_V2_GSI_m_CH_n_CONS_BYTES_BMSK                                                  0x1fffff
#define HWIO_ECPRI_ENDP_GSI_CONS_BYTES_TLV_V2_GSI_m_CH_n_CONS_BYTES_SHFT                                                         0

#define HWIO_ECPRI_ENDP_GSI_CONS_BYTES_AOS_V2_GSI_m_CH_n_ADDR(m,n)                                                      (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X9800 + (0x200*(m)) + (0x4*(n)))
#define HWIO_ECPRI_ENDP_GSI_CONS_BYTES_AOS_V2_GSI_m_CH_n_PHYS(m,n)                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X9800 + (0x200*(m)) + (0x4*(n)))
#define HWIO_ECPRI_ENDP_GSI_CONS_BYTES_AOS_V2_GSI_m_CH_n_OFFS(m,n)                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X9800 + (0x200*(m)) + (0x4*(n)))
#define HWIO_ECPRI_ENDP_GSI_CONS_BYTES_AOS_V2_GSI_m_CH_n_RMSK                                                             0x1fffff
#define HWIO_ECPRI_ENDP_GSI_CONS_BYTES_AOS_V2_GSI_m_CH_n_MAXm                                                                    2
#define HWIO_ECPRI_ENDP_GSI_CONS_BYTES_AOS_V2_GSI_m_CH_n_MAXn                                                                   73
#define HWIO_ECPRI_ENDP_GSI_CONS_BYTES_AOS_V2_GSI_m_CH_n_ATTR                                                                        0x1
#define HWIO_ECPRI_ENDP_GSI_CONS_BYTES_AOS_V2_GSI_m_CH_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_ENDP_GSI_CONS_BYTES_AOS_V2_GSI_m_CH_n_ADDR(m,n), HWIO_ECPRI_ENDP_GSI_CONS_BYTES_AOS_V2_GSI_m_CH_n_RMSK)
#define HWIO_ECPRI_ENDP_GSI_CONS_BYTES_AOS_V2_GSI_m_CH_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_ENDP_GSI_CONS_BYTES_AOS_V2_GSI_m_CH_n_ADDR(m,n), mask)
#define HWIO_ECPRI_ENDP_GSI_CONS_BYTES_AOS_V2_GSI_m_CH_n_CONS_BYTES_BMSK                                                  0x1fffff
#define HWIO_ECPRI_ENDP_GSI_CONS_BYTES_AOS_V2_GSI_m_CH_n_CONS_BYTES_SHFT                                                         0

#define HWIO_ECPRI_DMA_FL_PACKET_ID_CTRL_V2_ADDR                                                                            (ECPRI_DMA_NON_SECURED_REG_BASE + 0xe000)
#define HWIO_ECPRI_DMA_FL_PACKET_ID_CTRL_V2_PHYS                                                                            (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe000)
#define HWIO_ECPRI_DMA_FL_PACKET_ID_CTRL_V2_OFFS                                                                            (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe000)
#define HWIO_ECPRI_DMA_FL_PACKET_ID_CTRL_V2_RMSK                                                                                  0xff
#define HWIO_ECPRI_DMA_FL_PACKET_ID_CTRL_V2_ATTR                                                                                         0x3
#define HWIO_ECPRI_DMA_FL_PACKET_ID_CTRL_V2_IN                    \
                in_dword(HWIO_ECPRI_DMA_FL_PACKET_ID_CTRL_V2_ADDR)
#define HWIO_ECPRI_DMA_FL_PACKET_ID_CTRL_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA_FL_PACKET_ID_CTRL_V2_ADDR, m)
#define HWIO_ECPRI_DMA_FL_PACKET_ID_CTRL_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA_FL_PACKET_ID_CTRL_V2_ADDR,v)
#define HWIO_ECPRI_DMA_FL_PACKET_ID_CTRL_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA_FL_PACKET_ID_CTRL_V2_ADDR,m,v,HWIO_ECPRI_DMA_FL_PACKET_ID_CTRL_V2_IN)
#define HWIO_ECPRI_DMA_FL_PACKET_ID_CTRL_V2_LIMIT_BMSK                                                                            0xff
#define HWIO_ECPRI_DMA_FL_PACKET_ID_CTRL_V2_LIMIT_SHFT                                                                               0

#define HWIO_ECPRI_DMA_FL_PACKET_ID_STATUS_V2_ADDR                                                                          (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe004)
#define HWIO_ECPRI_DMA_FL_PACKET_ID_STATUS_V2_PHYS                                                                          (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe004)
#define HWIO_ECPRI_DMA_FL_PACKET_ID_STATUS_V2_OFFS                                                                          (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe004)
#define HWIO_ECPRI_DMA_FL_PACKET_ID_STATUS_V2_RMSK                                                                              0xffff
#define HWIO_ECPRI_DMA_FL_PACKET_ID_STATUS_V2_ATTR                                                                                       0x1
#define HWIO_ECPRI_DMA_FL_PACKET_ID_STATUS_V2_IN                    \
                in_dword(HWIO_ECPRI_DMA_FL_PACKET_ID_STATUS_V2_ADDR)
#define HWIO_ECPRI_DMA_FL_PACKET_ID_STATUS_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA_FL_PACKET_ID_STATUS_V2_ADDR, m)
#define HWIO_ECPRI_DMA_FL_PACKET_ID_STATUS_V2_MAX_HW_VALUE_BMSK                                                                 0xff00
#define HWIO_ECPRI_DMA_FL_PACKET_ID_STATUS_V2_MAX_HW_VALUE_SHFT                                                                      8
#define HWIO_ECPRI_DMA_FL_PACKET_ID_STATUS_V2_CURR_VALUE_BMSK                                                                     0xff
#define HWIO_ECPRI_DMA_FL_PACKET_ID_STATUS_V2_CURR_VALUE_SHFT                                                                        0

#define HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_CTRL_V2_ADDR                                                                        (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe008)
#define HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_CTRL_V2_PHYS                                                                        (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe008)
#define HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_CTRL_V2_OFFS                                                                        (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe008)
#define HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_CTRL_V2_RMSK                                                                              0xff
#define HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_CTRL_V2_ATTR                                                                                     0x3
#define HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_CTRL_V2_IN                    \
                in_dword(HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_CTRL_V2_ADDR)
#define HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_CTRL_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_CTRL_V2_ADDR, m)
#define HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_CTRL_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_CTRL_V2_ADDR,v)
#define HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_CTRL_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_CTRL_V2_ADDR,m,v,HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_CTRL_V2_IN)
#define HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_CTRL_V2_LIMIT_BMSK                                                                        0xff
#define HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_CTRL_V2_LIMIT_SHFT                                                                           0

#define HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_STATUS_V2_ADDR                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe00c)
#define HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_STATUS_V2_PHYS                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe00c)
#define HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_STATUS_V2_OFFS                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe00c)
#define HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_STATUS_V2_RMSK                                                                          0xffff
#define HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_STATUS_V2_ATTR                                                                                   0x1
#define HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_STATUS_V2_IN                    \
                in_dword(HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_STATUS_V2_ADDR)
#define HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_STATUS_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_STATUS_V2_ADDR, m)
#define HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_STATUS_V2_MAX_HW_VALUE_BMSK                                                             0xff00
#define HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_STATUS_V2_MAX_HW_VALUE_SHFT                                                                  8
#define HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_STATUS_V2_CURR_VALUE_BMSK                                                                 0xff
#define HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_STATUS_V2_CURR_VALUE_SHFT                                                                    0

#define HWIO_ECPRI_DMA_STREAM_CTRL_V2_ADDR                                                                                  (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe010)
#define HWIO_ECPRI_DMA_STREAM_CTRL_V2_PHYS                                                                                  (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe010)
#define HWIO_ECPRI_DMA_STREAM_CTRL_V2_OFFS                                                                                  (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe010)
#define HWIO_ECPRI_DMA_STREAM_CTRL_V2_RMSK                                                                                  0xffffffff
#define HWIO_ECPRI_DMA_STREAM_CTRL_V2_ATTR                                                                                               0x3
#define HWIO_ECPRI_DMA_STREAM_CTRL_V2_IN                    \
                in_dword(HWIO_ECPRI_DMA_STREAM_CTRL_V2_ADDR)
#define HWIO_ECPRI_DMA_STREAM_CTRL_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA_STREAM_CTRL_V2_ADDR, m)
#define HWIO_ECPRI_DMA_STREAM_CTRL_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA_STREAM_CTRL_V2_ADDR,v)
#define HWIO_ECPRI_DMA_STREAM_CTRL_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA_STREAM_CTRL_V2_ADDR,m,v,HWIO_ECPRI_DMA_STREAM_CTRL_V2_IN)
#define HWIO_ECPRI_DMA_STREAM_CTRL_V2_FH_LIMIT_BMSK                                                                         0xff000000
#define HWIO_ECPRI_DMA_STREAM_CTRL_V2_FH_LIMIT_SHFT                                                                                 24
#define HWIO_ECPRI_DMA_STREAM_CTRL_V2_L2_LIMIT_BMSK                                                                           0xff0000
#define HWIO_ECPRI_DMA_STREAM_CTRL_V2_L2_LIMIT_SHFT                                                                                 16
#define HWIO_ECPRI_DMA_STREAM_CTRL_V2_C2C_LIMIT_BMSK                                                                            0xff00
#define HWIO_ECPRI_DMA_STREAM_CTRL_V2_C2C_LIMIT_SHFT                                                                                 8
#define HWIO_ECPRI_DMA_STREAM_CTRL_V2_MEM_LIMIT_BMSK                                                                              0xff
#define HWIO_ECPRI_DMA_STREAM_CTRL_V2_MEM_LIMIT_SHFT                                                                                 0

#define HWIO_ECPRI_DMA_STREAM_STATUS_V2_ADDR                                                                                (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe014)
#define HWIO_ECPRI_DMA_STREAM_STATUS_V2_PHYS                                                                                (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe014)
#define HWIO_ECPRI_DMA_STREAM_STATUS_V2_OFFS                                                                                (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe014)
#define HWIO_ECPRI_DMA_STREAM_STATUS_V2_RMSK                                                                                0xffffffff
#define HWIO_ECPRI_DMA_STREAM_STATUS_V2_ATTR                                                                                             0x1
#define HWIO_ECPRI_DMA_STREAM_STATUS_V2_IN                    \
                in_dword(HWIO_ECPRI_DMA_STREAM_STATUS_V2_ADDR)
#define HWIO_ECPRI_DMA_STREAM_STATUS_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA_STREAM_STATUS_V2_ADDR, m)
#define HWIO_ECPRI_DMA_STREAM_STATUS_V2_FH_CURR_VALUE_BMSK                                                                  0xff000000
#define HWIO_ECPRI_DMA_STREAM_STATUS_V2_FH_CURR_VALUE_SHFT                                                                          24
#define HWIO_ECPRI_DMA_STREAM_STATUS_V2_L2_CURR_VALUE_BMSK                                                                    0xff0000
#define HWIO_ECPRI_DMA_STREAM_STATUS_V2_L2_CURR_VALUE_SHFT                                                                          16
#define HWIO_ECPRI_DMA_STREAM_STATUS_V2_C2C_CURR_VALUE_BMSK                                                                     0xff00
#define HWIO_ECPRI_DMA_STREAM_STATUS_V2_C2C_CURR_VALUE_SHFT                                                                          8
#define HWIO_ECPRI_DMA_STREAM_STATUS_V2_MEM_CURR_VALUE_BMSK                                                                       0xff
#define HWIO_ECPRI_DMA_STREAM_STATUS_V2_MEM_CURR_VALUE_SHFT                                                                          0

#define HWIO_ECPRI_DMA_STREAM_ARB_V2_ADDR                                                                                   (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe018)
#define HWIO_ECPRI_DMA_STREAM_ARB_V2_PHYS                                                                                   (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe018)
#define HWIO_ECPRI_DMA_STREAM_ARB_V2_OFFS                                                                                   (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe018)
#define HWIO_ECPRI_DMA_STREAM_ARB_V2_RMSK                                                                                       0xffff
#define HWIO_ECPRI_DMA_STREAM_ARB_V2_ATTR                                                                                                0x3
#define HWIO_ECPRI_DMA_STREAM_ARB_V2_IN                    \
                in_dword(HWIO_ECPRI_DMA_STREAM_ARB_V2_ADDR)
#define HWIO_ECPRI_DMA_STREAM_ARB_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA_STREAM_ARB_V2_ADDR, m)
#define HWIO_ECPRI_DMA_STREAM_ARB_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA_STREAM_ARB_V2_ADDR,v)
#define HWIO_ECPRI_DMA_STREAM_ARB_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA_STREAM_ARB_V2_ADDR,m,v,HWIO_ECPRI_DMA_STREAM_ARB_V2_IN)
#define HWIO_ECPRI_DMA_STREAM_ARB_V2_FH_WEIGHT_BMSK                                                                             0xf000
#define HWIO_ECPRI_DMA_STREAM_ARB_V2_FH_WEIGHT_SHFT                                                                                 12
#define HWIO_ECPRI_DMA_STREAM_ARB_V2_L2_WEIGHT_BMSK                                                                              0xf00
#define HWIO_ECPRI_DMA_STREAM_ARB_V2_L2_WEIGHT_SHFT                                                                                  8
#define HWIO_ECPRI_DMA_STREAM_ARB_V2_C2C_WEIGHT_BMSK                                                                              0xf0
#define HWIO_ECPRI_DMA_STREAM_ARB_V2_C2C_WEIGHT_SHFT                                                                                 4
#define HWIO_ECPRI_DMA_STREAM_ARB_V2_MEM_WEIGHT_BMSK                                                                               0xf
#define HWIO_ECPRI_DMA_STREAM_ARB_V2_MEM_WEIGHT_SHFT                                                                                 0

#define HWIO_ECPRI_DMA_XBAR_V2_ADDR                                                                                         (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe01c)
#define HWIO_ECPRI_DMA_XBAR_V2_PHYS                                                                                         (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe01c)
#define HWIO_ECPRI_DMA_XBAR_V2_OFFS                                                                                         (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe01c)
#define HWIO_ECPRI_DMA_XBAR_V2_RMSK                                                                                           0xffff00
#define HWIO_ECPRI_DMA_XBAR_V2_ATTR                                                                                                      0x3
#define HWIO_ECPRI_DMA_XBAR_V2_IN                    \
                in_dword(HWIO_ECPRI_DMA_XBAR_V2_ADDR)
#define HWIO_ECPRI_DMA_XBAR_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA_XBAR_V2_ADDR, m)
#define HWIO_ECPRI_DMA_XBAR_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA_XBAR_V2_ADDR,v)
#define HWIO_ECPRI_DMA_XBAR_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA_XBAR_V2_ADDR,m,v,HWIO_ECPRI_DMA_XBAR_V2_IN)
#define HWIO_ECPRI_DMA_XBAR_V2_TX_FIFO_WATERMARK_C2C_BMSK                                                                     0xff0000
#define HWIO_ECPRI_DMA_XBAR_V2_TX_FIFO_WATERMARK_C2C_SHFT                                                                           16
#define HWIO_ECPRI_DMA_XBAR_V2_TX_FIFO_WATERMARK_FH_BMSK                                                                        0xff00
#define HWIO_ECPRI_DMA_XBAR_V2_TX_FIFO_WATERMARK_FH_SHFT                                                                             8

#define HWIO_ECPRI_DMA_DBG_CTRL_V2_ADDR                                                                                     (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe020)
#define HWIO_ECPRI_DMA_DBG_CTRL_V2_PHYS                                                                                     (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe020)
#define HWIO_ECPRI_DMA_DBG_CTRL_V2_OFFS                                                                                     (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe020)
#define HWIO_ECPRI_DMA_DBG_CTRL_V2_RMSK                                                                                        0xfffff
#define HWIO_ECPRI_DMA_DBG_CTRL_V2_ATTR                                                                                                  0x3
#define HWIO_ECPRI_DMA_DBG_CTRL_V2_IN                    \
                in_dword(HWIO_ECPRI_DMA_DBG_CTRL_V2_ADDR)
#define HWIO_ECPRI_DMA_DBG_CTRL_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA_DBG_CTRL_V2_ADDR, m)
#define HWIO_ECPRI_DMA_DBG_CTRL_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA_DBG_CTRL_V2_ADDR,v)
#define HWIO_ECPRI_DMA_DBG_CTRL_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA_DBG_CTRL_V2_ADDR,m,v,HWIO_ECPRI_DMA_DBG_CTRL_V2_IN)
#define HWIO_ECPRI_DMA_DBG_CTRL_V2_DMA_IRQ_BMSK                                                                                0xc0000
#define HWIO_ECPRI_DMA_DBG_CTRL_V2_DMA_IRQ_SHFT                                                                                     18
#define HWIO_ECPRI_DMA_DBG_CTRL_V2_DMA_LOOPBACK_BMSK                                                                           0x30000
#define HWIO_ECPRI_DMA_DBG_CTRL_V2_DMA_LOOPBACK_SHFT                                                                                16
#define HWIO_ECPRI_DMA_DBG_CTRL_V2_FORCE_EMPTY_BMSK                                                                             0xffff
#define HWIO_ECPRI_DMA_DBG_CTRL_V2_FORCE_EMPTY_SHFT                                                                                  0

#define HWIO_ECPRI_DMA_GBL_CFG_V2_ADDR                                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe024)
#define HWIO_ECPRI_DMA_GBL_CFG_V2_PHYS                                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe024)
#define HWIO_ECPRI_DMA_GBL_CFG_V2_OFFS                                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe024)
#define HWIO_ECPRI_DMA_GBL_CFG_V2_RMSK                                                                                      0xffff003f
#define HWIO_ECPRI_DMA_GBL_CFG_V2_ATTR                                                                                                   0x3
#define HWIO_ECPRI_DMA_GBL_CFG_V2_IN                    \
                in_dword(HWIO_ECPRI_DMA_GBL_CFG_V2_ADDR)
#define HWIO_ECPRI_DMA_GBL_CFG_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA_GBL_CFG_V2_ADDR, m)
#define HWIO_ECPRI_DMA_GBL_CFG_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA_GBL_CFG_V2_ADDR,v)
#define HWIO_ECPRI_DMA_GBL_CFG_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA_GBL_CFG_V2_ADDR,m,v,HWIO_ECPRI_DMA_GBL_CFG_V2_IN)
#define HWIO_ECPRI_DMA_GBL_CFG_V2_FRAG_SIZE_BMSK                                                                            0xffff0000
#define HWIO_ECPRI_DMA_GBL_CFG_V2_FRAG_SIZE_SHFT                                                                                    16
#define HWIO_ECPRI_DMA_GBL_CFG_V2_L2_AR_WEIGTH_BMSK                                                                               0x3c
#define HWIO_ECPRI_DMA_GBL_CFG_V2_L2_AR_WEIGTH_SHFT                                                                                  2
#define HWIO_ECPRI_DMA_GBL_CFG_V2_QMB_512_WR_EN_BMSK                                                                               0x2
#define HWIO_ECPRI_DMA_GBL_CFG_V2_QMB_512_WR_EN_SHFT                                                                                 1
#define HWIO_ECPRI_DMA_GBL_CFG_V2_QMB_512_RD_EN_BMSK                                                                               0x1
#define HWIO_ECPRI_DMA_GBL_CFG_V2_QMB_512_RD_EN_SHFT                                                                                 0

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_DMA_DEBUG
 *--------------------------------------------------------------------------*/



#define HWIO_ECPRI_DMA_TESTBUS_CTRL_V2_ADDR                              (ECPRI_DMA_DEBUG_REG_BASE      + 0x0)
#define HWIO_ECPRI_DMA_TESTBUS_CTRL_V2_PHYS                               (ECPRI_DMA_DEBUG_REG_BASE_PHYS + 0x0)
#define HWIO_ECPRI_DMA_TESTBUS_CTRL_V2_OFFS                               (ECPRI_DMA_DEBUG_REG_BASE_OFFS + 0x0)
#define HWIO_ECPRI_DMA_TESTBUS_CTRL_V2_RMSK                                 0xff01ff
#define HWIO_ECPRI_DMA_TESTBUS_CTRL_V2_ATTR                                            0x3
#define HWIO_ECPRI_DMA_TESTBUS_CTRL_V2_IN                    \
                in_dword(HWIO_ECPRI_DMA_TESTBUS_CTRL_V2_ADDR)
#define HWIO_ECPRI_DMA_TESTBUS_CTRL_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA_TESTBUS_CTRL_V2_ADDR, m)
#define HWIO_ECPRI_DMA_TESTBUS_CTRL_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA_TESTBUS_CTRL_V2_ADDR,v)
#define HWIO_ECPRI_DMA_TESTBUS_CTRL_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA_TESTBUS_CTRL_V2_ADDR,m,v,HWIO_ECPRI_DMA_TESTBUS_CTRL_V2_IN)
#define HWIO_ECPRI_DMA_TESTBUS_CTRL_V2_SEL_INTERNAL_BMSK                    0xff0000
#define HWIO_ECPRI_DMA_TESTBUS_CTRL_V2_SEL_INTERNAL_SHFT                          16
#define HWIO_ECPRI_DMA_TESTBUS_CTRL_V2_SEL_BMSK                                0x1ff
#define HWIO_ECPRI_DMA_TESTBUS_CTRL_V2_SEL_SHFT                                    0


#define HWIO_ECPRI_
#define HWIO_ECPRI_DMA_GP_REG3_V2_ADDR                                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe02c)
#define HWIO_ECPRI_DMA_GP_REG3_V2_PHYS                                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe02c)
#define HWIO_ECPRI_DMA_GP_REG3_V2_OFFS                                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe02c)
#define HWIO_ECPRI_DMA_GP_REG3_V2_RMSK                                                                                      0xffffffff
#define HWIO_ECPRI_DMA_GP_REG3_V2_ATTR                                                                                                   0x3
#define HWIO_ECPRI_DMA_GP_REG3_V2_IN                    \
                in_dword(HWIO_ECPRI_DMA_GP_REG3_V2_ADDR)
#define HWIO_ECPRI_DMA_GP_REG3_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA_GP_REG3_V2_ADDR, m)
#define HWIO_ECPRI_DMA_GP_REG3_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA_GP_REG3_V2_ADDR,v)
#define HWIO_ECPRI_DMA_GP_REG3_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA_GP_REG3_V2_ADDR,m,v,HWIO_ECPRI_DMA_GP_REG3_V2_IN)
#define HWIO_ECPRI_DMA_GP_REG3_V2_DATA_BMSK                                                                                 0xffff0000
#define HWIO_ECPRI_DMA_GP_REG3_V2_DATA_SHFT                                                                                         16
#define HWIO_ECPRI_DMA_GP_REG3_V2_XBAR_RX_MODE_BMSK                                                                             0xff00
#define HWIO_ECPRI_DMA_GP_REG3_V2_XBAR_RX_MODE_SHFT                                                                                  8
#define HWIO_ECPRI_DMA_GP_REG3_V2_XBAR_TX_MODE_BMSK                                                                               0xff
#define HWIO_ECPRI_DMA_GP_REG3_V2_XBAR_TX_MODE_SHFT                                                                                  0

#define HWIO_ECPRI_DMA_AOS_FIFO_STAT_V2_ADDR                                                                                (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe030)
#define HWIO_ECPRI_DMA_AOS_FIFO_STAT_V2_PHYS                                                                                (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe030)
#define HWIO_ECPRI_DMA_AOS_FIFO_STAT_V2_OFFS                                                                                (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe030)
#define HWIO_ECPRI_DMA_AOS_FIFO_STAT_V2_RMSK                                                                                0xffffffff
#define HWIO_ECPRI_DMA_AOS_FIFO_STAT_V2_ATTR                                                                                             0x1
#define HWIO_ECPRI_DMA_AOS_FIFO_STAT_V2_IN                    \
                in_dword(HWIO_ECPRI_DMA_AOS_FIFO_STAT_V2_ADDR)
#define HWIO_ECPRI_DMA_AOS_FIFO_STAT_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA_AOS_FIFO_STAT_V2_ADDR, m)
#define HWIO_ECPRI_DMA_AOS_FIFO_STAT_V2_SRC_BMSK                                                                            0xffff0000
#define HWIO_ECPRI_DMA_AOS_FIFO_STAT_V2_SRC_SHFT                                                                                    16
#define HWIO_ECPRI_DMA_AOS_FIFO_STAT_V2_DST_BMSK                                                                                0xffff
#define HWIO_ECPRI_DMA_AOS_FIFO_STAT_V2_DST_SHFT                                                                                     0

#define HWIO_ECPRI_DMA_GP_STAT1_V2_ADDR                                                                                     (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe034)
#define HWIO_ECPRI_DMA_GP_STAT1_V2_PHYS                                                                                     (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe034)
#define HWIO_ECPRI_DMA_GP_STAT1_V2_OFFS                                                                                     (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe034)
#define HWIO_ECPRI_DMA_GP_STAT1_V2_RMSK                                                                                     0xffffffff
#define HWIO_ECPRI_DMA_GP_STAT1_V2_ATTR                                                                                                  0x1
#define HWIO_ECPRI_DMA_GP_STAT1_V2_IN                    \
                in_dword(HWIO_ECPRI_DMA_GP_STAT1_V2_ADDR)
#define HWIO_ECPRI_DMA_GP_STAT1_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA_GP_STAT1_V2_ADDR, m)
#define HWIO_ECPRI_DMA_GP_STAT1_V2_DATA_BMSK                                                                                0xffffffff
#define HWIO_ECPRI_DMA_GP_STAT1_V2_DATA_SHFT                                                                                         0
 /*----------------------------------------------------------------------------
  * MODULE: ECPRI_DMA_DEBUG
  *--------------------------------------------------------------------------*/


#define HWIO_ECPRI_DMA_TESTBUS_V2_ADDR                                    (ECPRI_DMA_DEBUG_REG_BASE      + 0x4)
#define HWIO_ECPRI_DMA_TESTBUS_V2_PHYS                                    (ECPRI_DMA_DEBUG_REG_BASE_PHYS + 0x4)
#define HWIO_ECPRI_DMA_TESTBUS_V2_OFFS                                    (ECPRI_DMA_DEBUG_REG_BASE_OFFS + 0x4)
#define HWIO_ECPRI_DMA_TESTBUS_V2_RMSK                                    0xffffffff
#define HWIO_ECPRI_DMA_TESTBUS_V2_ATTR                                                 0x1
#define HWIO_ECPRI_DMA_TESTBUS_V2_IN                    \
                in_dword(HWIO_ECPRI_DMA_TESTBUS_V2_ADDR)
#define HWIO_ECPRI_DMA_TESTBUS_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA_TESTBUS_V2_ADDR, m)
#define HWIO_ECPRI_DMA_TESTBUS_V2_DATA_BMSK                               0xffffffff
#define HWIO_ECPRI_DMA_TESTBUS_V2_DATA_SHFT                                        0


#define HWIO_ECPRI_DMA_GP_STAT3_V2_ADDR                                                                                     (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe03c)
#define HWIO_ECPRI_DMA_GP_STAT3_V2_PHYS                                                                                     (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe03c)
#define HWIO_ECPRI_DMA_GP_STAT3_V2_OFFS                                                                                     (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe03c)
#define HWIO_ECPRI_DMA_GP_STAT3_V2_RMSK                                                                                     0xffffffff
#define HWIO_ECPRI_DMA_GP_STAT3_V2_ATTR                                                                                                  0x1
#define HWIO_ECPRI_DMA_GP_STAT3_V2_IN                    \
                in_dword(HWIO_ECPRI_DMA_GP_STAT3_V2_ADDR)
#define HWIO_ECPRI_DMA_GP_STAT3_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA_GP_STAT3_V2_ADDR, m)
#define HWIO_ECPRI_DMA_GP_STAT3_V2_DATA_BMSK                                                                                0xffffffff
#define HWIO_ECPRI_DMA_GP_STAT3_V2_DATA_SHFT                                                                                         0

#define HWIO_ECPRI_DMA_IDLE_REG_V2_ADDR                                                                                     (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe040)
#define HWIO_ECPRI_DMA_IDLE_REG_V2_PHYS                                                                                     (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe040)
#define HWIO_ECPRI_DMA_IDLE_REG_V2_OFFS                                                                                     (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe040)
#define HWIO_ECPRI_DMA_IDLE_REG_V2_RMSK                                                                                     0xffffffff
#define HWIO_ECPRI_DMA_IDLE_REG_V2_ATTR                                                                                                  0x1
#define HWIO_ECPRI_DMA_IDLE_REG_V2_IN                    \
                in_dword(HWIO_ECPRI_DMA_IDLE_REG_V2_ADDR)
#define HWIO_ECPRI_DMA_IDLE_REG_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA_IDLE_REG_V2_ADDR, m)
#define HWIO_ECPRI_DMA_IDLE_REG_V2_DATA_BMSK                                                                                0xffffffff
#define HWIO_ECPRI_DMA_IDLE_REG_V2_DATA_SHFT                                                                                         0

#define HWIO_ECPRI_DMA_EXCEPTION_CHANNEL_V2_ADDR                                                                            (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe044)
#define HWIO_ECPRI_DMA_EXCEPTION_CHANNEL_V2_PHYS                                                                            (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe044)
#define HWIO_ECPRI_DMA_EXCEPTION_CHANNEL_V2_OFFS                                                                            (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe044)
#define HWIO_ECPRI_DMA_EXCEPTION_CHANNEL_V2_RMSK                                                                               0x103ff
#define HWIO_ECPRI_DMA_EXCEPTION_CHANNEL_V2_ATTR                                                                                         0x3
#define HWIO_ECPRI_DMA_EXCEPTION_CHANNEL_V2_IN                    \
                in_dword(HWIO_ECPRI_DMA_EXCEPTION_CHANNEL_V2_ADDR)
#define HWIO_ECPRI_DMA_EXCEPTION_CHANNEL_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA_EXCEPTION_CHANNEL_V2_ADDR, m)
#define HWIO_ECPRI_DMA_EXCEPTION_CHANNEL_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA_EXCEPTION_CHANNEL_V2_ADDR,v)
#define HWIO_ECPRI_DMA_EXCEPTION_CHANNEL_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA_EXCEPTION_CHANNEL_V2_ADDR,m,v,HWIO_ECPRI_DMA_EXCEPTION_CHANNEL_V2_IN)
#define HWIO_ECPRI_DMA_EXCEPTION_CHANNEL_V2_ENABLE_BMSK                                                                        0x10000
#define HWIO_ECPRI_DMA_EXCEPTION_CHANNEL_V2_ENABLE_SHFT                                                                             16
#define HWIO_ECPRI_DMA_EXCEPTION_CHANNEL_V2_GID_BMSK                                                                             0x300
#define HWIO_ECPRI_DMA_EXCEPTION_CHANNEL_V2_GID_SHFT                                                                                 8
#define HWIO_ECPRI_DMA_EXCEPTION_CHANNEL_V2_CHANNEL_BMSK                                                                          0xff
#define HWIO_ECPRI_DMA_EXCEPTION_CHANNEL_V2_CHANNEL_SHFT                                                                             0

#define HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_ADDR(n)                                                                           (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x0000e048 + 0x4 * (n))
#define HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_PHYS(n)                                                                           (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x0000e048 + 0x4 * (n))
#define HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_OFFS(n)                                                                           (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x0000e048 + 0x4 * (n))
#define HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_RMSK                                                                              0xffffffff
#define HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_MAXn                                                                                       3
#define HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_ATTR                                                                                     0x3
#define HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_INI(n)        \
        in_dword_masked(HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_ADDR(n), HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_RMSK)
#define HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_ADDR(n), mask)
#define HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_OUTI(n,val)    \
        out_dword(HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_ADDR(n),val)
#define HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_ADDR(n),mask,val,HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_INI(n))
#define HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_DST_GID_BMSK                                                                      0xc0000000
#define HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_DST_GID_SHFT                                                                            0x1e
#define HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_DST_CHANNEL_BMSK                                                                  0x3fc00000
#define HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_DST_CHANNEL_SHFT                                                                        0x16
#define HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_A_LOCATION_BMSK                                                                     0x3e0000
#define HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_A_LOCATION_SHFT                                                                         0x11
#define HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_A_WIDTH_BMSK                                                                         0x1f000
#define HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_A_WIDTH_SHFT                                                                             0xc
#define HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_A_ENABLE_BMSK                                                                          0x800
#define HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_A_ENABLE_SHFT                                                                            0xb
#define HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_B_LOCATION_BMSK                                                                        0x7c0
#define HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_B_LOCATION_SHFT                                                                          0x6
#define HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_B_WIDTH_BMSK                                                                            0x3e
#define HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_B_WIDTH_SHFT                                                                             0x1
#define HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_B_ENABLE_BMSK                                                                            0x1
#define HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_B_ENABLE_SHFT                                                                            0x0

#define HWIO_ECPRI_DPL_TRIG_A_n_V2_ADDR(n)                                                                              (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x0000e058 + 0x4 * (n))
#define HWIO_ECPRI_DPL_TRIG_A_n_V2_PHYS(n)                                                                              (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x0000e058 + 0x4 * (n))
#define HWIO_ECPRI_DPL_TRIG_A_n_V2_OFFS(n)                                                                              (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x0000e058 + 0x4 * (n))
#define HWIO_ECPRI_DPL_TRIG_A_n_V2_RMSK                                                                                 0xffffffff
#define HWIO_ECPRI_DPL_TRIG_A_n_V2_MAXn                                                                                          3
#define HWIO_ECPRI_DPL_TRIG_A_n_V2_ATTR                                                                                        0x3
#define HWIO_ECPRI_DPL_TRIG_A_n_V2_INI(n)        \
        in_dword_masked(HWIO_ECPRI_DPL_TRIG_A_n_V2_ADDR(n), HWIO_ECPRI_DPL_TRIG_A_n_V2_RMSK)
#define HWIO_ECPRI_DPL_TRIG_A_n_V2_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_DPL_TRIG_A_n_V2_ADDR(n), mask)
#define HWIO_ECPRI_DPL_TRIG_A_n_V2_OUTI(n,val)    \
        out_dword(HWIO_ECPRI_DPL_TRIG_A_n_V2_ADDR(n),val)
#define HWIO_ECPRI_DPL_TRIG_A_n_V2_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_DPL_TRIG_A_n_V2_ADDR(n),mask,val,HWIO_ECPRI_DPL_TRIG_A_n_V2_INI(n))
#define HWIO_ECPRI_DPL_TRIG_A_n_V2_VALUE_BMSK                                                                           0xffffffff
#define HWIO_ECPRI_DPL_TRIG_A_n_V2_VALUE_SHFT                                                                                  0x0

#define HWIO_ECPRI_DPL_TRIG_B_n_V2_ADDR(n)                                                                              (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x0000e068 + 0x4 * (n))
#define HWIO_ECPRI_DPL_TRIG_B_n_V2_PHYS(n)                                                                              (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x0000e068 + 0x4 * (n))
#define HWIO_ECPRI_DPL_TRIG_B_n_V2_OFFS(n)                                                                              (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x0000e068 + 0x4 * (n))
#define HWIO_ECPRI_DPL_TRIG_B_n_V2_RMSK                                                                                 0xffffffff
#define HWIO_ECPRI_DPL_TRIG_B_n_V2_MAXn                                                                                          3
#define HWIO_ECPRI_DPL_TRIG_B_n_V2_ATTR                                                                                        0x3
#define HWIO_ECPRI_DPL_TRIG_B_n_V2_INI(n)        \
        in_dword_masked(HWIO_ECPRI_DPL_TRIG_B_n_V2_ADDR(n), HWIO_ECPRI_DPL_TRIG_B_n_V2_RMSK)
#define HWIO_ECPRI_DPL_TRIG_B_n_V2_INMI(n,mask)    \
        in_dword_masked(HWIO_ECPRI_DPL_TRIG_B_n_V2_ADDR(n), mask)
#define HWIO_ECPRI_DPL_TRIG_B_n_V2_OUTI(n,val)    \
        out_dword(HWIO_ECPRI_DPL_TRIG_B_n_V2_ADDR(n),val)
#define HWIO_ECPRI_DPL_TRIG_B_n_V2_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_DPL_TRIG_B_n_V2_ADDR(n),mask,val,HWIO_ECPRI_DPL_TRIG_B_n_V2_INI(n))
#define HWIO_ECPRI_DPL_TRIG_B_n_V2_VALUE_BMSK                                                                           0xffffffff
#define HWIO_ECPRI_DPL_TRIG_B_n_V2_VALUE_SHFT                                                                                  0x0

#define HWIO_ECPRI_STATUS_PKT_DROP_FULL_V2_ADDR                                                                         (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe090)
#define HWIO_ECPRI_STATUS_PKT_DROP_FULL_V2_PHYS                                                                         (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe090)
#define HWIO_ECPRI_STATUS_PKT_DROP_FULL_V2_OFFS                                                                         (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe090)
#define HWIO_ECPRI_STATUS_PKT_DROP_FULL_V2_RMSK                                                                           0xffffff
#define HWIO_ECPRI_STATUS_PKT_DROP_FULL_V2_ATTR                                                                                      0x1
#define HWIO_ECPRI_STATUS_PKT_DROP_FULL_V2_IN                    \
                in_dword(HWIO_ECPRI_STATUS_PKT_DROP_FULL_V2_ADDR)
#define HWIO_ECPRI_STATUS_PKT_DROP_FULL_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_STATUS_PKT_DROP_FULL_V2_ADDR, m)
#define HWIO_ECPRI_STATUS_PKT_DROP_FULL_V2_CNT_BMSK                                                                       0xffffff
#define HWIO_ECPRI_STATUS_PKT_DROP_FULL_V2_CNT_SHFT                                                                              0

#define HWIO_ECPRI_STATUS_PKT_DROP_TLV_FIFO_EMPTY_V2_ADDR                                                               (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe094)
#define HWIO_ECPRI_STATUS_PKT_DROP_TLV_FIFO_EMPTY_V2_PHYS                                                               (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe094)
#define HWIO_ECPRI_STATUS_PKT_DROP_TLV_FIFO_EMPTY_V2_OFFS                                                               (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe094)
#define HWIO_ECPRI_STATUS_PKT_DROP_TLV_FIFO_EMPTY_V2_RMSK                                                                 0xffffff
#define HWIO_ECPRI_STATUS_PKT_DROP_TLV_FIFO_EMPTY_V2_ATTR                                                                            0x1
#define HWIO_ECPRI_STATUS_PKT_DROP_TLV_FIFO_EMPTY_V2_IN                    \
                in_dword(HWIO_ECPRI_STATUS_PKT_DROP_TLV_FIFO_EMPTY_V2_ADDR)
#define HWIO_ECPRI_STATUS_PKT_DROP_TLV_FIFO_EMPTY_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_STATUS_PKT_DROP_TLV_FIFO_EMPTY_V2_ADDR, m)
#define HWIO_ECPRI_STATUS_PKT_DROP_TLV_FIFO_EMPTY_V2_CNT_BMSK                                                             0xffffff
#define HWIO_ECPRI_STATUS_PKT_DROP_TLV_FIFO_EMPTY_V2_CNT_SHFT                                                                    0

#define HWIO_ECPRI_DMA_DPL_CFG_V2_ADDR                                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe098)
#define HWIO_ECPRI_DMA_DPL_CFG_V2_PHYS                                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe098)
#define HWIO_ECPRI_DMA_DPL_CFG_V2_OFFS                                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe098)
#define HWIO_ECPRI_DMA_DPL_CFG_V2_RMSK                                                                                      0xe0100fff
#define HWIO_ECPRI_DMA_DPL_CFG_V2_ATTR                                                                                                   0x3
#define HWIO_ECPRI_DMA_DPL_CFG_V2_IN                    \
                in_dword(HWIO_ECPRI_DMA_DPL_CFG_V2_ADDR)
#define HWIO_ECPRI_DMA_DPL_CFG_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA_DPL_CFG_V2_ADDR, m)
#define HWIO_ECPRI_DMA_DPL_CFG_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA_DPL_CFG_V2_ADDR,v)
#define HWIO_ECPRI_DMA_DPL_CFG_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA_DPL_CFG_V2_ADDR,m,v,HWIO_ECPRI_DMA_DPL_CFG_V2_IN)
#define HWIO_ECPRI_DMA_DPL_CFG_V2_DPL_FLUSH_PKT_BMSK                                                                        0xc0000000
#define HWIO_ECPRI_DMA_DPL_CFG_V2_DPL_FLUSH_PKT_SHFT                                                                                30
#define HWIO_ECPRI_DMA_DPL_CFG_V2_DPL_FLUSH_CLR_BMSK                                                                        0x20000000
#define HWIO_ECPRI_DMA_DPL_CFG_V2_DPL_FLUSH_CLR_SHFT                                                                                29
#define HWIO_ECPRI_DMA_DPL_CFG_V2_DPL_TRE_MIRROR_EN_BMSK                                                                      0x100000
#define HWIO_ECPRI_DMA_DPL_CFG_V2_DPL_TRE_MIRROR_EN_SHFT                                                                            20
#define HWIO_ECPRI_DMA_DPL_CFG_V2_DPL_SELECT_BMSK                                                                                0xf00
#define HWIO_ECPRI_DMA_DPL_CFG_V2_DPL_SELECT_SHFT                                                                                    8
#define HWIO_ECPRI_DMA_DPL_CFG_V2_DPL_MTU_BMSK                                                                                    0xff
#define HWIO_ECPRI_DMA_DPL_CFG_V2_DPL_MTU_SHFT                                                                                       0

#define HWIO_ECPRI_DMA_TPDM_CFG_V2_ADDR                                   (ECPRI_DMA_DEBUG_REG_BASE      + 0x100)
#define HWIO_ECPRI_DMA_TPDM_CFG_V2_PHYS                                   (ECPRI_DMA_DEBUG_REG_BASE_PHYS + 0x100)
#define HWIO_ECPRI_DMA_TPDM_CFG_V2_OFFS                                   (ECPRI_DMA_DEBUG_REG_BASE_OFFS + 0x100)
#define HWIO_ECPRI_DMA_TPDM_CFG_V2_RMSK                                   0xfff7fff0
#define HWIO_ECPRI_DMA_TPDM_CFG_V2_ATTR                                                0x3
#define HWIO_ECPRI_DMA_TPDM_CFG_V2_IN                    \
                in_dword(HWIO_ECPRI_DMA_TPDM_CFG_V2_ADDR)
#define HWIO_ECPRI_DMA_TPDM_CFG_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA_TPDM_CFG_V2_ADDR, m)
#define HWIO_ECPRI_DMA_TPDM_CFG_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA_TPDM_CFG_V2_ADDR,v)
#define HWIO_ECPRI_DMA_TPDM_CFG_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA_TPDM_CFG_V2_ADDR,m,v,HWIO_ECPRI_DMA_TPDM_CFG_V2_IN)
#define HWIO_ECPRI_DMA_TPDM_CFG_V2_UNIT_EN_BMSK                           0xfff00000
#define HWIO_ECPRI_DMA_TPDM_CFG_V2_UNIT_EN_SHFT                                   20
#define HWIO_ECPRI_DMA_TPDM_CFG_V2_RECORD_EN_BMSK                            0x40000
#define HWIO_ECPRI_DMA_TPDM_CFG_V2_RECORD_EN_SHFT                                 18
#define HWIO_ECPRI_DMA_TPDM_CFG_V2_RECORD_GID_BMSK                           0x30000
#define HWIO_ECPRI_DMA_TPDM_CFG_V2_RECORD_GID_SHFT                                16
#define HWIO_ECPRI_DMA_TPDM_CFG_V2_RECORD_CHANNEL_BMSK                        0xff00
#define HWIO_ECPRI_DMA_TPDM_CFG_V2_RECORD_CHANNEL_SHFT                             8
#define HWIO_ECPRI_DMA_TPDM_CFG_V2_RECORD_RATE_BMSK                             0xf0
#define HWIO_ECPRI_DMA_TPDM_CFG_V2_RECORD_RATE_SHFT                                4


#define HWIO_ECPRI_NSO_CFG_V2_ADDR                                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe100)
#define HWIO_ECPRI_NSO_CFG_V2_PHYS                                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe100)
#define HWIO_ECPRI_NSO_CFG_V2_OFFS                                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe100)
#define HWIO_ECPRI_NSO_CFG_V2_RMSK                                                                                         0xf01ff
#define HWIO_ECPRI_NSO_CFG_V2_ATTR                                                                                                   0x3
#define HWIO_ECPRI_NSO_CFG_V2_IN                    \
                in_dword(HWIO_ECPRI_NSO_CFG_V2_ADDR)
#define HWIO_ECPRI_NSO_CFG_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NSO_CFG_V2_ADDR, m)
#define HWIO_ECPRI_NSO_CFG_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_NSO_CFG_V2_ADDR,v)
#define HWIO_ECPRI_NSO_CFG_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_NSO_CFG_V2_ADDR,m,v,HWIO_ECPRI_NSO_CFG_V2_IN)
#define HWIO_ECPRI_NSO_CFG_V2_MAX_DF_SECTORS_BMSK                                                                          0xf0000
#define HWIO_ECPRI_NSO_CFG_V2_MAX_DF_SECTORS_SHFT                                                                               16
#define HWIO_ECPRI_NSO_CFG_V2_MAX_NUM_OF_SECTORS_BMSK                                                                        0x1fc
#define HWIO_ECPRI_NSO_CFG_V2_MAX_NUM_OF_SECTORS_SHFT                                                                            2
#define HWIO_ECPRI_NSO_CFG_V2_MIN_PKT_ENABLE_BMSK                                                                              0x2
#define HWIO_ECPRI_NSO_CFG_V2_MIN_PKT_ENABLE_SHFT                                                                                1
#define HWIO_ECPRI_NSO_CFG_V2_NFAPI_HDR_BYTE_SWAP_BMSK                                                                         0x1
#define HWIO_ECPRI_NSO_CFG_V2_NFAPI_HDR_BYTE_SWAP_SHFT                                                                           0


#define HWIO_ECPRI_NSO_JUMBO_PKT_CFG_V2_ADDR                                                                            (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe104)
#define HWIO_ECPRI_NSO_JUMBO_PKT_CFG_V2_PHYS                                                                            (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe104)
#define HWIO_ECPRI_NSO_JUMBO_PKT_CFG_V2_OFFS                                                                            (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe104)
#define HWIO_ECPRI_NSO_JUMBO_PKT_CFG_V2_RMSK                                                                            0xffffffff
#define HWIO_ECPRI_NSO_JUMBO_PKT_CFG_V2_ATTR                                                                                         0x3
#define HWIO_ECPRI_NSO_JUMBO_PKT_CFG_V2_IN                    \
                in_dword(HWIO_ECPRI_NSO_JUMBO_PKT_CFG_V2_ADDR)
#define HWIO_ECPRI_NSO_JUMBO_PKT_CFG_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NSO_JUMBO_PKT_CFG_V2_ADDR, m)
#define HWIO_ECPRI_NSO_JUMBO_PKT_CFG_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_NSO_JUMBO_PKT_CFG_V2_ADDR,v)
#define HWIO_ECPRI_NSO_JUMBO_PKT_CFG_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_NSO_JUMBO_PKT_CFG_V2_ADDR,m,v,HWIO_ECPRI_NSO_JUMBO_PKT_CFG_V2_IN)
#define HWIO_ECPRI_NSO_JUMBO_PKT_CFG_V2_JUMBO_MIN_PKT_LEN_BMSK                                                          0xffff0000
#define HWIO_ECPRI_NSO_JUMBO_PKT_CFG_V2_JUMBO_MIN_PKT_LEN_SHFT                                                                  16
#define HWIO_ECPRI_NSO_JUMBO_PKT_CFG_V2_JUMBO_MAX_PKT_LEN_BMSK                                                              0xffff
#define HWIO_ECPRI_NSO_JUMBO_PKT_CFG_V2_JUMBO_MAX_PKT_LEN_SHFT                                                                   0


#define HWIO_ECPRI_NSO_SHORT_PKT_CFG_V2_ADDR                                                                            (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe108)
#define HWIO_ECPRI_NSO_SHORT_PKT_CFG_V2_PHYS                                                                            (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe108)
#define HWIO_ECPRI_NSO_SHORT_PKT_CFG_V2_OFFS                                                                            (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe108)
#define HWIO_ECPRI_NSO_SHORT_PKT_CFG_V2_RMSK                                                                            0xffffffff
#define HWIO_ECPRI_NSO_SHORT_PKT_CFG_V2_ATTR                                                                                         0x3
#define HWIO_ECPRI_NSO_SHORT_PKT_CFG_V2_IN                    \
                in_dword(HWIO_ECPRI_NSO_SHORT_PKT_CFG_V2_ADDR)
#define HWIO_ECPRI_NSO_SHORT_PKT_CFG_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NSO_SHORT_PKT_CFG_V2_ADDR, m)
#define HWIO_ECPRI_NSO_SHORT_PKT_CFG_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_NSO_SHORT_PKT_CFG_V2_ADDR,v)
#define HWIO_ECPRI_NSO_SHORT_PKT_CFG_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_NSO_SHORT_PKT_CFG_V2_ADDR,m,v,HWIO_ECPRI_NSO_SHORT_PKT_CFG_V2_IN)
#define HWIO_ECPRI_NSO_SHORT_PKT_CFG_V2_SHORT_MIN_PKT_LEN_BMSK                                                          0xffff0000
#define HWIO_ECPRI_NSO_SHORT_PKT_CFG_V2_SHORT_MIN_PKT_LEN_SHFT                                                                  16
#define HWIO_ECPRI_NSO_SHORT_PKT_CFG_V2_SHORT_MAX_PKT_LEN_BMSK                                                              0xffff
#define HWIO_ECPRI_NSO_SHORT_PKT_CFG_V2_SHORT_MAX_PKT_LEN_SHFT                                                                   0

#define HWIO_ECPRI_NSO_JUMBO_PKT_EN_V2_GSI_m_REG_n_ADDR(m,n)                                                            (ECPRI_DMA_NON_SECURED_REG_BASE      + 0XE110 + (0x8*(m)) + (0x4*(n)))
#define HWIO_ECPRI_NSO_JUMBO_PKT_EN_V2_GSI_m_REG_n_PHYS(m,n)                                                            (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0XE110 + (0x8*(m)) + (0x4*(n)))
#define HWIO_ECPRI_NSO_JUMBO_PKT_EN_V2_GSI_m_REG_n_OFFS(m,n)                                                            (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0XE110 + (0x8*(m)) + (0x4*(n)))
#define HWIO_ECPRI_NSO_JUMBO_PKT_EN_V2_GSI_m_REG_n_RMSK                                                                 0xffffffff
#define HWIO_ECPRI_NSO_JUMBO_PKT_EN_V2_GSI_m_REG_n_MAXm                                                                          2
#define HWIO_ECPRI_NSO_JUMBO_PKT_EN_V2_GSI_m_REG_n_MAXn                                                                          1
#define HWIO_ECPRI_NSO_JUMBO_PKT_EN_V2_GSI_m_REG_n_ATTR                                                                              0x3
#define HWIO_ECPRI_NSO_JUMBO_PKT_EN_V2_GSI_m_REG_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_NSO_JUMBO_PKT_EN_V2_GSI_m_REG_n_ADDR(m,n), HWIO_ECPRI_NSO_JUMBO_PKT_EN_V2_GSI_m_REG_n_RMSK)
#define HWIO_ECPRI_NSO_JUMBO_PKT_EN_V2_GSI_m_REG_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_NSO_JUMBO_PKT_EN_V2_GSI_m_REG_n_ADDR(m,n), mask)
#define HWIO_ECPRI_NSO_JUMBO_PKT_EN_V2_GSI_m_REG_n_OUTI2(m,n,val)        \
                out_dword(HWIO_ECPRI_NSO_JUMBO_PKT_EN_V2_GSI_m_REG_n_ADDR(m,n),val)
#define HWIO_ECPRI_NSO_JUMBO_PKT_EN_V2_GSI_m_REG_n_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_ECPRI_NSO_JUMBO_PKT_EN_V2_GSI_m_REG_n_ADDR(m,n),mask,val,HWIO_ECPRI_NSO_JUMBO_PKT_EN_V2_GSI_m_REG_n_INI2(m,n))
#define HWIO_ECPRI_NSO_JUMBO_PKT_EN_V2_GSI_m_REG_n_JUMBO_PKT_EN_BMSK                                                    0xffffffff
#define HWIO_ECPRI_NSO_JUMBO_PKT_EN_V2_GSI_m_REG_n_JUMBO_PKT_EN_SHFT                                                             0

#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_ADDR                                                                         (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe140)
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_PHYS                                                                         (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe140)
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_OFFS                                                                         (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe140)
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_RMSK                                                                         0x1fffffff
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_ATTR                                                                                      0x1
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_IN                    \
                in_dword(HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_ADDR)
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_ADDR, m)
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_GSI_ID_BMSK                                                                  0x18000000
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_GSI_ID_SHFT                                                                          27
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_PKT_ID_BMSK                                                                   0x7f80000
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_PKT_ID_SHFT                                                                          19
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_DST_ID_BMSK                                                                     0x7f000
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_DST_ID_SHFT                                                                          12
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_DST_ID_TYPE_BMSK                                                                  0x800
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_DST_ID_TYPE_SHFT                                                                     11
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_SRC_ID_BMSK                                                                       0x7f0
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_SRC_ID_SHFT                                                                           4
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_SRC_ID_TYPE_BMSK                                                                    0x8
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_SRC_ID_TYPE_SHFT                                                                      3
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_NFAPI_MSG_TOO_LONG_BMSK                                                             0x4
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_NFAPI_MSG_TOO_LONG_SHFT                                                               2
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_NFAPI_MSG_TOO_SHORT_BMSK                                                            0x2
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_NFAPI_MSG_TOO_SHORT_SHFT                                                              1
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_NFAPI_MSG_LEN_ERR_BMSK                                                              0x1
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_NFAPI_MSG_LEN_ERR_SHFT                                                                0

#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_2_V2_ADDR                                                                         (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe144)
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_2_V2_PHYS                                                                         (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe144)
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_2_V2_OFFS                                                                         (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe144)
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_2_V2_RMSK                                                                           0xffffff
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_2_V2_ATTR                                                                                      0x1
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_2_V2_IN                    \
                in_dword(HWIO_ECPRI_NSO_LEN_ERR_STATUS_2_V2_ADDR)
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_2_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NSO_LEN_ERR_STATUS_2_V2_ADDR, m)
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_2_V2_NFAPI_REMAINING_LEN_BMSK                                                       0xffffff
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_2_V2_NFAPI_REMAINING_LEN_SHFT                                                              0

#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_3_V2_ADDR                                                                         (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe148)
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_3_V2_PHYS                                                                         (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe148)
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_3_V2_OFFS                                                                         (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe148)
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_3_V2_RMSK                                                                         0xffffffff
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_3_V2_ATTR                                                                                      0x1
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_3_V2_IN                    \
                in_dword(HWIO_ECPRI_NSO_LEN_ERR_STATUS_3_V2_ADDR)
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_3_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NSO_LEN_ERR_STATUS_3_V2_ADDR, m)
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_3_V2_TUSER_TID_BMSK                                                               0xffffffff
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_3_V2_TUSER_TID_SHFT                                                                        0

#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_HDR_n_V2_ADDR(n)                                                                  (ECPRI_DMA_NON_SECURED_REG_BASE      + 0XE150 + (0x4*(n)))
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_HDR_n_V2_PHYS(n)                                                                  (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0XE150 + (0x4*(n)))
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_HDR_n_V2_OFFS(n)                                                                  (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0XE150 + (0x4*(n)))
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_HDR_n_V2_RMSK                                                                     0xffffffff
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_HDR_n_V2_MAXn                                                                              6
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_HDR_n_V2_ATTR                                                                                  0x1
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_HDR_n_V2_INI(n)                \
                in_dword_masked(HWIO_ECPRI_NSO_LEN_ERR_STATUS_HDR_n_V2_ADDR(n), HWIO_ECPRI_NSO_LEN_ERR_STATUS_HDR_n_V2_RMSK)
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_HDR_n_V2_INMI(n,mask)        \
                in_dword_masked(HWIO_ECPRI_NSO_LEN_ERR_STATUS_HDR_n_V2_ADDR(n), mask)
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_HDR_n_V2_NFAPI_MSG_HDR_BMSK                                                       0xffffffff
#define HWIO_ECPRI_NSO_LEN_ERR_STATUS_HDR_n_V2_NFAPI_MSG_HDR_SHFT                                                                0

#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_V2_ADDR(n)                                                                    (ECPRI_DMA_NON_SECURED_REG_BASE      + 0XE170 + (0x4*(n)))
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_V2_PHYS(n)                                                                    (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0XE170 + (0x4*(n)))
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_V2_OFFS(n)                                                                    (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0XE170 + (0x4*(n)))
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_V2_RMSK                                                                       0xffffffff
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_V2_MAXn                                                                                7
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_V2_ATTR                                                                                    0x1
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_V2_INI(n)                \
                in_dword_masked(HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_V2_ADDR(n), HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_V2_RMSK)
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_V2_INMI(n,mask)        \
                in_dword_masked(HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_V2_ADDR(n), mask)
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_V2_GSI_ID_BMSK                                                                0xc0000000
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_V2_GSI_ID_SHFT                                                                        30
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_V2_MSG_TOO_LONG_BMSK                                                          0x20000000
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_V2_MSG_TOO_LONG_SHFT                                                                  29
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_V2_LAST_BMSK                                                                  0x10000000
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_V2_LAST_SHFT                                                                          28
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_V2_NUM_OF_SECTORS_BMSK                                                         0xf000000
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_V2_NUM_OF_SECTORS_SHFT                                                                24
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_V2_SIZE_BMSK                                                                    0xfffc00
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_V2_SIZE_SHFT                                                                          10
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_V2_SRC_ID_BMSK                                                                     0x3f8
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_V2_SRC_ID_SHFT                                                                         3
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_V2_ENG_STATE_BMSK                                                                    0x7
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_V2_ENG_STATE_SHFT                                                                      0

#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_V2_ADDR(n)                                                                    (ECPRI_DMA_NON_SECURED_REG_BASE      + 0XE190 + (0x4*(n)))
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_V2_PHYS(n)                                                                    (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0XE190 + (0x4*(n)))
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_V2_OFFS(n)                                                                    (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0XE190 + (0x4*(n)))
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_V2_RMSK                                                                       0x1fffffff
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_V2_MAXn                                                                                7
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_V2_ATTR                                                                                    0x1
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_V2_INI(n)                \
                in_dword_masked(HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_V2_ADDR(n), HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_V2_RMSK)
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_V2_INMI(n,mask)        \
                in_dword_masked(HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_V2_ADDR(n), mask)
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_V2_JUMBO_PKT_EN_BMSK                                                          0x10000000
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_V2_JUMBO_PKT_EN_SHFT                                                                  28
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_V2_NFAPI_HDR_VALID_BMSK                                                        0x8000000
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_V2_NFAPI_HDR_VALID_SHFT                                                               27
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_V2_ENG_STATE_BMSK                                                              0x7000000
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_V2_ENG_STATE_SHFT                                                                     24
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_V2_NFAPI_REMAINING_LEN_BMSK                                                     0xffffff
#define HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_V2_NFAPI_REMAINING_LEN_SHFT                                                            0

#define HWIO_ECPRI_NSO_DBG_MISC_INFO_V2_ADDR                                                                            (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe1b0)
#define HWIO_ECPRI_NSO_DBG_MISC_INFO_V2_PHYS                                                                            (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe1b0)
#define HWIO_ECPRI_NSO_DBG_MISC_INFO_V2_OFFS                                                                            (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe1b0)
#define HWIO_ECPRI_NSO_DBG_MISC_INFO_V2_RMSK                                                                            0x7fffffff
#define HWIO_ECPRI_NSO_DBG_MISC_INFO_V2_ATTR                                                                                         0x1
#define HWIO_ECPRI_NSO_DBG_MISC_INFO_V2_IN                    \
                in_dword(HWIO_ECPRI_NSO_DBG_MISC_INFO_V2_ADDR)
#define HWIO_ECPRI_NSO_DBG_MISC_INFO_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_NSO_DBG_MISC_INFO_V2_ADDR, m)
#define HWIO_ECPRI_NSO_DBG_MISC_INFO_V2_TOTAL_NUM_OF_SECTORS_BMSK                                                       0x7f000000
#define HWIO_ECPRI_NSO_DBG_MISC_INFO_V2_TOTAL_NUM_OF_SECTORS_SHFT                                                               24
#define HWIO_ECPRI_NSO_DBG_MISC_INFO_V2_ENG_STATE_BMSK                                                                    0xffffff
#define HWIO_ECPRI_NSO_DBG_MISC_INFO_V2_ENG_STATE_SHFT                                                                           0

#define HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_ADDR(m,n)                                                                 (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X1014 + (0x2000*(m)) + (0x40*(n)))
#define HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_PHYS(m,n)                                                                 (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X1014 + (0x2000*(m)) + (0x40*(n)))
#define HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_OFFS(m,n)                                                                 (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X1014 + (0x2000*(m)) + (0x40*(n)))
#define HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_RMSK                                                                           0x3ff
#define HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_MAXm                                                                               2
#define HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_MAXn                                                                              73
#define HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_ATTR                                                                                   0x3
#define HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_ADDR(m,n), HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_RMSK)
#define HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_ADDR(m,n), mask)
#define HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_OUTI2(m,n,val)        \
                out_dword(HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_ADDR(m,n),val)
#define HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_ADDR(m,n),mask,val,HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_INI2(m,n))
#define HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_RECORD_ENABLE_BMSK                                                             0x200
#define HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_RECORD_ENABLE_SHFT                                                                 9
#define HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_RECORD_SIZE_BMSK                                                               0x1ff
#define HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_RECORD_SIZE_SHFT                                                                   0

#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_V2_ADDR(n)                                                               (ECPRI_DMA_NON_SECURED_REG_BASE + 0X10000 + (0x1000 * (n)))
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_V2_PHYS(n)                                                               (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X10000 + (0x1000*(n)))
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_V2_OFFS(n)                                                               (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X10000 + (0x1000*(n)))
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_V2_RMSK                                                                  0xff0300ff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_V2_MAXn                                                                           3
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_V2_ATTR                                                                               0x3
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_V2_INI(n)                \
                in_dword_masked(HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_V2_ADDR(n), HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_V2_RMSK)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_V2_INMI(n,mask)        \
                in_dword_masked(HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_V2_ADDR(n), mask)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_V2_OUTI(n,val)        \
                out_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_V2_ADDR(n),val)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_V2_OUTMI(n,mask,val) \
                out_dword_masked_ns(HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_V2_ADDR(n),mask,val,HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_V2_INI(n))
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_V2_TIMER_VALUE_BMSK                                                      0xff000000
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_V2_TIMER_VALUE_SHFT                                                              24
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_V2_TIMER_GRAN_SEL_BMSK                                                      0x30000
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_V2_TIMER_GRAN_SEL_SHFT                                                           16
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_V2_MAX_MESSAGES_BMSK                                                           0xff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_V2_MAX_MESSAGES_SHFT                                                              0

#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_V2_ADDR(n)                                                               (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X10004 + (0x1000*(n)))
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_V2_PHYS(n)                                                               (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X10004 + (0x1000*(n)))
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_V2_OFFS(n)                                                               (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X10004 + (0x1000*(n)))
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_V2_RMSK                                                                  0xffffffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_V2_MAXn                                                                           3
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_V2_ATTR                                                                               0x3
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_V2_INI(n)                \
                in_dword_masked(HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_V2_ADDR(n), HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_V2_RMSK)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_V2_INMI(n,mask)        \
                in_dword_masked(HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_V2_ADDR(n), mask)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_V2_OUTI(n,val)        \
                out_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_V2_ADDR(n),val)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_V2_OUTMI(n,mask,val) \
                out_dword_masked_ns(HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_V2_ADDR(n),mask,val,HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_V2_INI(n))
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_V2_LARGE_MESSAGE_BYTE_THRESHOLD_BMSK                                     0xffffffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_V2_LARGE_MESSAGE_BYTE_THRESHOLD_SHFT                                              0

#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_V2_ADDR(n)                                                               (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X10008 + (0x1000*(n)))
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_V2_PHYS(n)                                                               (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X10008 + (0x1000*(n)))
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_V2_OFFS(n)                                                               (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X10008 + (0x1000*(n)))
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_V2_RMSK                                                                    0x1fffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_V2_MAXn                                                                           3
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_V2_ATTR                                                                               0x3
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_V2_INI(n)                \
                in_dword_masked(HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_V2_ADDR(n), HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_V2_RMSK)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_V2_INMI(n,mask)        \
                in_dword_masked(HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_V2_ADDR(n), mask)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_V2_OUTI(n,val)        \
                out_dword(HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_V2_ADDR(n),val)
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_V2_OUTMI(n,mask,val) \
                out_dword_masked_ns(HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_V2_ADDR(n),mask,val,HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_V2_INI(n))
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_V2_MAXIMUM_MESSAGE_LENGTH_BMSK                                             0x1fffff
#define HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_V2_MAXIMUM_MESSAGE_LENGTH_SHFT                                                    0


#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_ADDR(n)                                                 (ECPRI_DMA_EES_REG_BASE      + 0X0 + (0x1000*(n)))
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_PHYS(n)                                                 (ECPRI_DMA_EES_REG_BASE_PHYS + 0X0 + (0x1000*(n)))
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_OFFS(n)                                                 (ECPRI_DMA_EES_REG_BASE_OFFS + 0X0 + (0x1000*(n)))
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_RMSK                                                       0xfffff
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_MAXn                                                             1
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_ATTR                                                                 0x1
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_INI(n)                \
                in_dword_masked(HWIO_ECPRI_IRQ_STTS_EE_n_V2_ADDR(n), HWIO_ECPRI_IRQ_STTS_EE_n_V2_RMSK)
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_INMI(n,mask)        \
                in_dword_masked(HWIO_ECPRI_IRQ_STTS_EE_n_V2_ADDR(n), mask)
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_LTE_PKT_DROP_TYPE_2_IRQ_BMSK                               0x80000
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_LTE_PKT_DROP_TYPE_2_IRQ_SHFT                                    19
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_LTE_PKT_DROP_TYPE_1_IRQ_BMSK                               0x40000
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_LTE_PKT_DROP_TYPE_1_IRQ_SHFT                                    18
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_XBAR_RX_PKT_DROP_TYPE_4_IRQ_BMSK                           0x20000
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_XBAR_RX_PKT_DROP_TYPE_4_IRQ_SHFT                                17
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_XBAR_RX_PKT_DROP_TYPE_3_IRQ_BMSK                           0x10000
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_XBAR_RX_PKT_DROP_TYPE_3_IRQ_SHFT                                16
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_XBAR_RX_PKT_DROP_TYPE_2_IRQ_BMSK                            0x8000
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_XBAR_RX_PKT_DROP_TYPE_2_IRQ_SHFT                                15
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_XBAR_RX_PKT_DROP_TYPE_1_IRQ_BMSK                            0x4000
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_XBAR_RX_PKT_DROP_TYPE_1_IRQ_SHFT                                14
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_NRO_MESSAGE_BIGGER_THAN_SDU_LENGTH_IRQ_BMSK                 0x2000
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_NRO_MESSAGE_BIGGER_THAN_SDU_LENGTH_IRQ_SHFT                     13
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_NRO_MESSAGE_TOO_BIG_IRQ_BMSK                                0x1000
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_NRO_MESSAGE_TOO_BIG_IRQ_SHFT                                    12
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_PIPE_RED_MARKER_ABOVE_IRQ_BMSK                               0x800
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_PIPE_RED_MARKER_ABOVE_IRQ_SHFT                                  11
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_PIPE_RED_MARKER_BELOW_IRQ_BMSK                               0x400
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_PIPE_RED_MARKER_BELOW_IRQ_SHFT                                  10
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_PIPE_YELLOW_MARKER_ABOVE_IRQ_BMSK                            0x200
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_PIPE_YELLOW_MARKER_ABOVE_IRQ_SHFT                                9
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_PIPE_YELLOW_MARKER_BELOW_IRQ_BMSK                            0x100
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_PIPE_YELLOW_MARKER_BELOW_IRQ_SHFT                                8
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_NFAPI_SEGMENTATION_IRQ_BMSK                                   0x80
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_NFAPI_SEGMENTATION_IRQ_SHFT                                      7
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_NRO_BAD_TIMESTAMP_IRQ_BMSK                                    0x40
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_NRO_BAD_TIMESTAMP_IRQ_SHFT                                       6
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_NRO_BAD_TOTAL_SDU_LENGTH_IRQ_BMSK                             0x20
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_NRO_BAD_TOTAL_SDU_LENGTH_IRQ_SHFT                                5
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_NRO_TIMEOUT_IRQ_BMSK                                          0x10
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_NRO_TIMEOUT_IRQ_SHFT                                             4
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_NRO_NOT_ENOUGH_BYTES_IRQ_BMSK                                  0x8
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_NRO_NOT_ENOUGH_BYTES_IRQ_SHFT                                    3
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_NRO_NOT_ENOUGH_CONTEXTS_IRQ_BMSK                               0x4
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_NRO_NOT_ENOUGH_CONTEXTS_IRQ_SHFT                                 2
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_NRO_PACKET_BIGGER_THAN_SDU_LENGTH_IRQ_BMSK                     0x2
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_NRO_PACKET_BIGGER_THAN_SDU_LENGTH_IRQ_SHFT                       1
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_BAD_SNOC_ACCESS_IRQ_BMSK                                       0x1
#define HWIO_ECPRI_IRQ_STTS_EE_n_V2_BAD_SNOC_ACCESS_IRQ_SHFT                                         0

#define HWIO_ECPRI_IRQ_EN_EE_n_V2_ADDR(n)                                                   (ECPRI_DMA_EES_REG_BASE      + 0X10 + (0x1000*(n)))
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_PHYS(n)                                                   (ECPRI_DMA_EES_REG_BASE_PHYS + 0X10 + (0x1000*(n)))
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_OFFS(n)                                                   (ECPRI_DMA_EES_REG_BASE_OFFS + 0X10 + (0x1000*(n)))
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_RMSK                                                         0xfffff
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_MAXn                                                               1
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_ATTR                                                                   0x3
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_INI(n)                \
                in_dword_masked(HWIO_ECPRI_IRQ_EN_EE_n_V2_ADDR(n), HWIO_ECPRI_IRQ_EN_EE_n_V2_RMSK)
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_INMI(n,mask)        \
                in_dword_masked(HWIO_ECPRI_IRQ_EN_EE_n_V2_ADDR(n), mask)
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_OUTI(n,val)        \
                out_dword(HWIO_ECPRI_IRQ_EN_EE_n_V2_ADDR(n),val)
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_OUTMI(n,mask,val) \
                out_dword_masked_ns(HWIO_ECPRI_IRQ_EN_EE_n_V2_ADDR(n),mask,val,HWIO_ECPRI_IRQ_EN_EE_n_V2_INI(n))
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_LTE_PKT_DROP_TYPE_2_IRQ_EN_BMSK                              0x80000
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_LTE_PKT_DROP_TYPE_2_IRQ_EN_SHFT                                   19
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_LTE_PKT_DROP_TYPE_1_IRQ_EN_BMSK                              0x40000
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_LTE_PKT_DROP_TYPE_1_IRQ_EN_SHFT                                   18
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_XBAR_RX_PKT_DROP_TYPE_4_IRQ_EN_BMSK                          0x20000
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_XBAR_RX_PKT_DROP_TYPE_4_IRQ_EN_SHFT                               17
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_XBAR_RX_PKT_DROP_TYPE_3_IRQ_EN_BMSK                          0x10000
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_XBAR_RX_PKT_DROP_TYPE_3_IRQ_EN_SHFT                               16
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_XBAR_RX_PKT_DROP_TYPE_2_IRQ_EN_BMSK                           0x8000
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_XBAR_RX_PKT_DROP_TYPE_2_IRQ_EN_SHFT                               15
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_XBAR_RX_PKT_DROP_TYPE_1_IRQ_EN_BMSK                           0x4000
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_XBAR_RX_PKT_DROP_TYPE_1_IRQ_EN_SHFT                               14
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_NRO_MESSAGE_BIGGER_THAN_SDU_LENGTH_IRQ_EN_BMSK                0x2000
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_NRO_MESSAGE_BIGGER_THAN_SDU_LENGTH_IRQ_EN_SHFT                    13
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_NRO_MESSAGE_TOO_BIG_IRQ_EN_BMSK                               0x1000
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_NRO_MESSAGE_TOO_BIG_IRQ_EN_SHFT                                   12
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_PIPE_RED_MARKER_ABOVE_IRQ_EN_BMSK                              0x800
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_PIPE_RED_MARKER_ABOVE_IRQ_EN_SHFT                                 11
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_PIPE_RED_MARKER_BELOW_IRQ_EN_BMSK                              0x400
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_PIPE_RED_MARKER_BELOW_IRQ_EN_SHFT                                 10
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_PIPE_YELLOW_MARKER_ABOVE_IRQ_EN_BMSK                           0x200
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_PIPE_YELLOW_MARKER_ABOVE_IRQ_EN_SHFT                               9
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_PIPE_YELLOW_MARKER_BELOW_IRQ_EN_BMSK                           0x100
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_PIPE_YELLOW_MARKER_BELOW_IRQ_EN_SHFT                               8
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_NFAPI_SEGMENTATION_IRQ_EN_BMSK                                  0x80
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_NFAPI_SEGMENTATION_IRQ_EN_SHFT                                     7
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_NRO_BAD_TIMESTAMP_IRQ_EN_BMSK                                   0x40
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_NRO_BAD_TIMESTAMP_IRQ_EN_SHFT                                      6
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_NRO_BAD_TOTAL_SDU_LENGTH_IRQ_EN_BMSK                            0x20
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_NRO_BAD_TOTAL_SDU_LENGTH_IRQ_EN_SHFT                               5
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_NRO_TIMEOUT_IRQ_EN_BMSK                                         0x10
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_NRO_TIMEOUT_IRQ_EN_SHFT                                            4
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_NRO_NOT_ENOUGH_BYTES_IRQ_EN_BMSK                                 0x8
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_NRO_NOT_ENOUGH_BYTES_IRQ_EN_SHFT                                   3
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_NRO_NOT_ENOUGH_CONTEXTS_IRQ_EN_BMSK                              0x4
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_NRO_NOT_ENOUGH_CONTEXTS_IRQ_EN_SHFT                                2
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_NRO_PACKET_BIGGER_THAN_SDU_LENGTH_IRQ_EN_BMSK                    0x2
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_NRO_PACKET_BIGGER_THAN_SDU_LENGTH_IRQ_EN_SHFT                      1
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_BAD_SNOC_ACCESS_IRQ_EN_BMSK                                      0x1
#define HWIO_ECPRI_IRQ_EN_EE_n_V2_BAD_SNOC_ACCESS_IRQ_EN_SHFT                                        0

#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_ADDR(n)                                                  (ECPRI_DMA_EES_REG_BASE      + 0X20 + (0x1000*(n)))
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_PHYS(n)                                                  (ECPRI_DMA_EES_REG_BASE_PHYS + 0X20 + (0x1000*(n)))
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_OFFS(n)                                                  (ECPRI_DMA_EES_REG_BASE_OFFS + 0X20 + (0x1000*(n)))
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_RMSK                                                        0xfffff
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_MAXn                                                              1
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_ATTR                                                                  0x2
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_OUTI(n,val)        \
                out_dword(HWIO_ECPRI_IRQ_CLR_EE_n_V2_ADDR(n),val)
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_LTE_PKT_DROP_TYPE_2_IRQ_CLR_BMSK                            0x80000
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_LTE_PKT_DROP_TYPE_2_IRQ_CLR_SHFT                                 19
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_LTE_PKT_DROP_TYPE_1_IRQ_CLR_BMSK                            0x40000
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_LTE_PKT_DROP_TYPE_1_IRQ_CLR_SHFT                                 18
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_XBAR_RX_PKT_DROP_TYPE_4_IRQ_CLR_BMSK                        0x20000
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_XBAR_RX_PKT_DROP_TYPE_4_IRQ_CLR_SHFT                             17
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_XBAR_RX_PKT_DROP_TYPE_3_IRQ_CLR_BMSK                        0x10000
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_XBAR_RX_PKT_DROP_TYPE_3_IRQ_CLR_SHFT                             16
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_XBAR_RX_PKT_DROP_TYPE_2_IRQ_CLR_BMSK                         0x8000
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_XBAR_RX_PKT_DROP_TYPE_2_IRQ_CLR_SHFT                             15
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_XBAR_RX_PKT_DROP_TYPE_1_IRQ_CLR_BMSK                         0x4000
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_XBAR_RX_PKT_DROP_TYPE_1_IRQ_CLR_SHFT                             14
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_NRO_MESSAGE_BIGGER_THAN_SDU_LENGTH_IRQ_CLR_BMSK              0x2000
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_NRO_MESSAGE_BIGGER_THAN_SDU_LENGTH_IRQ_CLR_SHFT                  13
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_NRO_MESSAGE_TOO_BIG_IRQ_CLR_BMSK                             0x1000
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_NRO_MESSAGE_TOO_BIG_IRQ_CLR_SHFT                                 12
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_PIPE_RED_MARKER_ABOVE_IRQ_CLR_BMSK                            0x800
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_PIPE_RED_MARKER_ABOVE_IRQ_CLR_SHFT                               11
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_PIPE_RED_MARKER_BELOW_IRQ_CLR_BMSK                            0x400
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_PIPE_RED_MARKER_BELOW_IRQ_CLR_SHFT                               10
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_PIPE_YELLOW_MARKER_ABOVE_IRQ_CLR_BMSK                         0x200
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_PIPE_YELLOW_MARKER_ABOVE_IRQ_CLR_SHFT                             9
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_PIPE_YELLOW_MARKER_BELOW_IRQ_CLR_BMSK                         0x100
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_PIPE_YELLOW_MARKER_BELOW_IRQ_CLR_SHFT                             8
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_NFAPI_SEGMENTATION_IRQ_CLR_BMSK                                0x80
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_NFAPI_SEGMENTATION_IRQ_CLR_SHFT                                   7
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_NRO_BAD_TIMESTAMP_IRQ_CLR_BMSK                                 0x40
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_NRO_BAD_TIMESTAMP_IRQ_CLR_SHFT                                    6
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_NRO_BAD_TOTAL_SDU_LENGTH_IRQ_CLR_BMSK                          0x20
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_NRO_BAD_TOTAL_SDU_LENGTH_IRQ_CLR_SHFT                             5
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_NRO_TIMEOUT_IRQ_CLR_BMSK                                       0x10
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_NRO_TIMEOUT_IRQ_CLR_SHFT                                          4
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_NRO_NOT_ENOUGH_BYTES_IRQ_CLR_BMSK                               0x8
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_NRO_NOT_ENOUGH_BYTES_IRQ_CLR_SHFT                                 3
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_NRO_NOT_ENOUGH_CONTEXTS_IRQ_CLR_BMSK                            0x4
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_NRO_NOT_ENOUGH_CONTEXTS_IRQ_CLR_SHFT                              2
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_NRO_PACKET_BIGGER_THAN_SDU_LENGTH_IRQ_CLR_BMSK                  0x2
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_NRO_PACKET_BIGGER_THAN_SDU_LENGTH_IRQ_CLR_SHFT                    1
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_BAD_SNOC_ACCESS_IRQ_CLR_BMSK                                    0x1
#define HWIO_ECPRI_IRQ_CLR_EE_n_V2_BAD_SNOC_ACCESS_IRQ_CLR_SHFT                                      0


/*----------------------------------------------------------------------------
 * MODULE: ECPRI_DMA_SECURED
 *--------------------------------------------------------------------------*/

#define HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_ADDR(m,n)                    (ECPRI_DMA_SECURED_REG_BASE      + 0X0 + (0x1000*(m)) + (0x20*(n)))
#define HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_PHYS(m,n)                    (ECPRI_DMA_SECURED_REG_BASE_PHYS + 0X0 + (0x1000*(m)) + (0x20*(n)))
#define HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_OFFS(m,n)                    (ECPRI_DMA_SECURED_REG_BASE_OFFS + 0X0 + (0x1000*(m)) + (0x20*(n)))
#define HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_RMSK                           0xff0fff
#define HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_MAXm                                  2
#define HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_MAXn                                 73
#define HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_ATTR                                      0x3
#define HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_ADDR(m,n), HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_RMSK)
#define HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_ADDR(m,n), mask)
#define HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_OUTI2(m,n,val)        \
                out_dword(HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_ADDR(m,n),val)
#define HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_ADDR(m,n),mask,val,HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_INI2(m,n))
#define HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_FIFO_SIZE_BMSK                 0xff0000
#define HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_FIFO_SIZE_SHFT                       16
#define HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_FIFO_BASE_ADDR_BMSK               0xfff
#define HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_FIFO_BASE_ADDR_SHFT                   0

#define HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_ADDR(m,n)                    (ECPRI_DMA_SECURED_REG_BASE      + 0X4 + (0x1000*(m)) + (0x20*(n)))
#define HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_PHYS(m,n)                    (ECPRI_DMA_SECURED_REG_BASE_PHYS + 0X4 + (0x1000*(m)) + (0x20*(n)))
#define HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_OFFS(m,n)                    (ECPRI_DMA_SECURED_REG_BASE_OFFS + 0X4 + (0x1000*(m)) + (0x20*(n)))
#define HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_RMSK                           0xff0fff
#define HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_MAXm                                  2
#define HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_MAXn                                 73
#define HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_ATTR                                      0x3
#define HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_ADDR(m,n), HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_RMSK)
#define HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_ADDR(m,n), mask)
#define HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_OUTI2(m,n,val)        \
                out_dword(HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_ADDR(m,n),val)
#define HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_ADDR(m,n),mask,val,HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_INI2(m,n))
#define HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_FIFO_SIZE_BMSK                 0xff0000
#define HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_FIFO_SIZE_SHFT                       16
#define HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_FIFO_BASE_ADDR_BMSK               0xfff
#define HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_FIFO_BASE_ADDR_SHFT                   0

#define HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_ADDR(m,n)                        (ECPRI_DMA_SECURED_REG_BASE      + 0X8 + (0x1000*(m)) + (0x20*(n)))
#define HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_PHYS(m,n)                        (ECPRI_DMA_SECURED_REG_BASE_PHYS + 0X8 + (0x1000*(m)) + (0x20*(n)))
#define HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_OFFS(m,n)                        (ECPRI_DMA_SECURED_REG_BASE_OFFS + 0X8 + (0x1000*(m)) + (0x20*(n)))
#define HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_RMSK                                   0x3f
#define HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_MAXm                                      2
#define HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_MAXn                                     77
#define HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_ATTR                                          0x3
#define HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_ADDR(m,n), HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_RMSK)
#define HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_ADDR(m,n), mask)
#define HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_OUTI2(m,n,val)        \
                out_dword(HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_ADDR(m,n),val)
#define HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_ADDR(m,n),mask,val,HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_INI2(m,n))
#define HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_VF_ACTIVE_BMSK                         0x20
#define HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_VF_ACTIVE_SHFT                            5
#define HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_VFID_BMSK                              0x1f
#define HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_VFID_SHFT                                 0

#define HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_ADDR(m,n)                          (ECPRI_DMA_SECURED_REG_BASE      + 0X4000 + (0x40*(m)) + (0x4*(n)))
#define HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_PHYS(m,n)                          (ECPRI_DMA_SECURED_REG_BASE_PHYS + 0X4000 + (0x40*(m)) + (0x4*(n)))
#define HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_OFFS(m,n)                          (ECPRI_DMA_SECURED_REG_BASE_OFFS + 0X4000 + (0x40*(m)) + (0x4*(n)))
#define HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_RMSK                                     0x3f
#define HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_MAXm                                        2
#define HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_MAXn                                        6
#define HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_ATTR                                            0x3
#define HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_ADDR(m,n), HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_RMSK)
#define HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_ADDR(m,n), mask)
#define HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_OUTI2(m,n,val)        \
                out_dword(HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_ADDR(m,n),val)
#define HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_ADDR(m,n),mask,val,HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_INI2(m,n))
#define HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_VF_ACTIVE_BMSK                           0x20
#define HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_VF_ACTIVE_SHFT                              5
#define HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_VFID_BMSK                                0x1f
#define HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_VFID_SHFT                                   0

#define HWIO_ECPRI_AHB2RAM_FIFOS_CFG_ADDR                          (ECPRI_DMA_DEBUG_REG_BASE      + 0x8)
#define HWIO_ECPRI_AHB2RAM_FIFOS_CFG_PHYS                          (ECPRI_DMA_DEBUG_REG_BASE_PHYS + 0x8)
#define HWIO_ECPRI_AHB2RAM_FIFOS_CFG_OFFS                          (ECPRI_DMA_DEBUG_REG_BASE_OFFS + 0x8)
#define HWIO_ECPRI_AHB2RAM_FIFOS_CFG_RMSK                                 0xf
#define HWIO_ECPRI_AHB2RAM_FIFOS_CFG_ATTR                                       0x3
#define HWIO_ECPRI_AHB2RAM_FIFOS_CFG_IN                    \
                in_dword(HWIO_ECPRI_AHB2RAM_FIFOS_CFG_ADDR)
#define HWIO_ECPRI_AHB2RAM_FIFOS_CFG_INM(m)            \
                in_dword_masked(HWIO_ECPRI_AHB2RAM_FIFOS_CFG_ADDR, m)
#define HWIO_ECPRI_AHB2RAM_FIFOS_CFG_OUT(v)            \
                out_dword(HWIO_ECPRI_AHB2RAM_FIFOS_CFG_ADDR,v)
#define HWIO_ECPRI_AHB2RAM_FIFOS_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_AHB2RAM_FIFOS_CFG_ADDR,m,v,HWIO_ECPRI_AHB2RAM_FIFOS_CFG_IN)
#define HWIO_ECPRI_AHB2RAM_FIFOS_CFG_EN_BMSK                              0x8
#define HWIO_ECPRI_AHB2RAM_FIFOS_CFG_EN_SHFT                                3
#define HWIO_ECPRI_AHB2RAM_FIFOS_CFG_GSI_SEL_BMSK                         0x6
#define HWIO_ECPRI_AHB2RAM_FIFOS_CFG_GSI_SEL_SHFT                           1
#define HWIO_ECPRI_AHB2RAM_FIFOS_CFG_FIFO_SEL_BMSK                        0x1
#define HWIO_ECPRI_AHB2RAM_FIFOS_CFG_FIFO_SEL_SHFT                          0

#define HWIO_ECPRI_SNIFFER_CTRL1_ADDR                              (ECPRI_DMA_DEBUG_REG_BASE      + 0x200)
#define HWIO_ECPRI_SNIFFER_CTRL1_PHYS                              (ECPRI_DMA_DEBUG_REG_BASE_PHYS + 0x200)
#define HWIO_ECPRI_SNIFFER_CTRL1_OFFS                              (ECPRI_DMA_DEBUG_REG_BASE_OFFS + 0x200)
#define HWIO_ECPRI_SNIFFER_CTRL1_RMSK                              0x7fffffff
#define HWIO_ECPRI_SNIFFER_CTRL1_ATTR                                           0x3
#define HWIO_ECPRI_SNIFFER_CTRL1_IN                    \
                in_dword(HWIO_ECPRI_SNIFFER_CTRL1_ADDR)
#define HWIO_ECPRI_SNIFFER_CTRL1_INM(m)            \
                in_dword_masked(HWIO_ECPRI_SNIFFER_CTRL1_ADDR, m)
#define HWIO_ECPRI_SNIFFER_CTRL1_OUT(v)            \
                out_dword(HWIO_ECPRI_SNIFFER_CTRL1_ADDR,v)
#define HWIO_ECPRI_SNIFFER_CTRL1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_SNIFFER_CTRL1_ADDR,m,v,HWIO_ECPRI_SNIFFER_CTRL1_IN)
#define HWIO_ECPRI_SNIFFER_CTRL1_MEM_BASE_ADDR_BMSK                0x7fffffff
#define HWIO_ECPRI_SNIFFER_CTRL1_MEM_BASE_ADDR_SHFT                         0

#define HWIO_ECPRI_SNIFFER_CTRL2_ADDR                              (ECPRI_DMA_DEBUG_REG_BASE      + 0x204)
#define HWIO_ECPRI_SNIFFER_CTRL2_PHYS                              (ECPRI_DMA_DEBUG_REG_BASE_PHYS + 0x204)
#define HWIO_ECPRI_SNIFFER_CTRL2_OFFS                              (ECPRI_DMA_DEBUG_REG_BASE_OFFS + 0x204)
#define HWIO_ECPRI_SNIFFER_CTRL2_RMSK                              0x87ffffff
#define HWIO_ECPRI_SNIFFER_CTRL2_ATTR                                           0x3
#define HWIO_ECPRI_SNIFFER_CTRL2_IN                    \
                in_dword(HWIO_ECPRI_SNIFFER_CTRL2_ADDR)
#define HWIO_ECPRI_SNIFFER_CTRL2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_SNIFFER_CTRL2_ADDR, m)
#define HWIO_ECPRI_SNIFFER_CTRL2_OUT(v)            \
                out_dword(HWIO_ECPRI_SNIFFER_CTRL2_ADDR,v)
#define HWIO_ECPRI_SNIFFER_CTRL2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_SNIFFER_CTRL2_ADDR,m,v,HWIO_ECPRI_SNIFFER_CTRL2_IN)
#define HWIO_ECPRI_SNIFFER_CTRL2_ENABLE_BMSK                       0x80000000
#define HWIO_ECPRI_SNIFFER_CTRL2_ENABLE_SHFT                               31
#define HWIO_ECPRI_SNIFFER_CTRL2_MEM_SIZE_BMSK                      0x7ff0000
#define HWIO_ECPRI_SNIFFER_CTRL2_MEM_SIZE_SHFT                             16
#define HWIO_ECPRI_SNIFFER_CTRL2_NUM_OT_BMSK                           0xfc00
#define HWIO_ECPRI_SNIFFER_CTRL2_NUM_OT_SHFT                               10
#define HWIO_ECPRI_SNIFFER_CTRL2_GID_BMSK                               0x300
#define HWIO_ECPRI_SNIFFER_CTRL2_GID_SHFT                                   8
#define HWIO_ECPRI_SNIFFER_CTRL2_CHANNEL_BMSK                            0xff
#define HWIO_ECPRI_SNIFFER_CTRL2_CHANNEL_SHFT                               0

#define HWIO_ECPRI_SNIFFER_STAT_ADDR                               (ECPRI_DMA_DEBUG_REG_BASE      + 0x208)
#define HWIO_ECPRI_SNIFFER_STAT_PHYS                               (ECPRI_DMA_DEBUG_REG_BASE_PHYS + 0x208)
#define HWIO_ECPRI_SNIFFER_STAT_OFFS                               (ECPRI_DMA_DEBUG_REG_BASE_OFFS + 0x208)
#define HWIO_ECPRI_SNIFFER_STAT_RMSK                               0xe7ffffff
#define HWIO_ECPRI_SNIFFER_STAT_ATTR                                            0x1
#define HWIO_ECPRI_SNIFFER_STAT_IN                    \
                in_dword(HWIO_ECPRI_SNIFFER_STAT_ADDR)
#define HWIO_ECPRI_SNIFFER_STAT_INM(m)            \
                in_dword_masked(HWIO_ECPRI_SNIFFER_STAT_ADDR, m)
#define HWIO_ECPRI_SNIFFER_STAT_STATE_BMSK                         0xc0000000
#define HWIO_ECPRI_SNIFFER_STAT_STATE_SHFT                                 30
#define HWIO_ECPRI_SNIFFER_STAT_WRAPP_BIT_BMSK                     0x20000000
#define HWIO_ECPRI_SNIFFER_STAT_WRAPP_BIT_SHFT                             29
#define HWIO_ECPRI_SNIFFER_STAT_NUM_OT_BMSK                         0x7e00000
#define HWIO_ECPRI_SNIFFER_STAT_NUM_OT_SHFT                                21
#define HWIO_ECPRI_SNIFFER_STAT_WRITE_PTR_BMSK                       0x1fffff
#define HWIO_ECPRI_SNIFFER_STAT_WRITE_PTR_SHFT                              0

#define HWIO_ECPRI_LTE_DEBUG_CFG_ADDR                              (ECPRI_DMA_DEBUG_REG_BASE      + 0x300)
#define HWIO_ECPRI_LTE_DEBUG_CFG_PHYS                              (ECPRI_DMA_DEBUG_REG_BASE_PHYS + 0x300)
#define HWIO_ECPRI_LTE_DEBUG_CFG_OFFS                              (ECPRI_DMA_DEBUG_REG_BASE_OFFS + 0x300)
#define HWIO_ECPRI_LTE_DEBUG_CFG_RMSK                                     0x3
#define HWIO_ECPRI_LTE_DEBUG_CFG_ATTR                                           0x3
#define HWIO_ECPRI_LTE_DEBUG_CFG_IN                    \
                in_dword(HWIO_ECPRI_LTE_DEBUG_CFG_ADDR)
#define HWIO_ECPRI_LTE_DEBUG_CFG_INM(m)            \
                in_dword_masked(HWIO_ECPRI_LTE_DEBUG_CFG_ADDR, m)
#define HWIO_ECPRI_LTE_DEBUG_CFG_OUT(v)            \
                out_dword(HWIO_ECPRI_LTE_DEBUG_CFG_ADDR,v)
#define HWIO_ECPRI_LTE_DEBUG_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_LTE_DEBUG_CFG_ADDR,m,v,HWIO_ECPRI_LTE_DEBUG_CFG_IN)
#define HWIO_ECPRI_LTE_DEBUG_CFG_WATERMARK_CLR_EN_BMSK                    0x2
#define HWIO_ECPRI_LTE_DEBUG_CFG_WATERMARK_CLR_EN_SHFT                      1
#define HWIO_ECPRI_LTE_DEBUG_CFG_WATERMARK_EN_BMSK                        0x1
#define HWIO_ECPRI_LTE_DEBUG_CFG_WATERMARK_EN_SHFT                          0

#define HWIO_ECPRI_LTE_WATERMARKS_ADDR                             (ECPRI_DMA_DEBUG_REG_BASE      + 0x304)
#define HWIO_ECPRI_LTE_WATERMARKS_PHYS                             (ECPRI_DMA_DEBUG_REG_BASE_PHYS + 0x304)
#define HWIO_ECPRI_LTE_WATERMARKS_OFFS                             (ECPRI_DMA_DEBUG_REG_BASE_OFFS + 0x304)
#define HWIO_ECPRI_LTE_WATERMARKS_RMSK                              0x7ffffff
#define HWIO_ECPRI_LTE_WATERMARKS_ATTR                                          0x1
#define HWIO_ECPRI_LTE_WATERMARKS_IN                    \
                in_dword(HWIO_ECPRI_LTE_WATERMARKS_ADDR)
#define HWIO_ECPRI_LTE_WATERMARKS_INM(m)            \
                in_dword_masked(HWIO_ECPRI_LTE_WATERMARKS_ADDR, m)
#define HWIO_ECPRI_LTE_WATERMARKS_LTE_TXM_CMD_FIFO_BMSK             0x7800000
#define HWIO_ECPRI_LTE_WATERMARKS_LTE_TXM_CMD_FIFO_SHFT                    23
#define HWIO_ECPRI_LTE_WATERMARKS_LTE_DDH_CMD_BUFFER_BMSK            0x7fe000
#define HWIO_ECPRI_LTE_WATERMARKS_LTE_DDH_CMD_BUFFER_SHFT                  13
#define HWIO_ECPRI_LTE_WATERMARKS_LTE_LATENCY_BUFFER_BMSK              0x1fff
#define HWIO_ECPRI_LTE_WATERMARKS_LTE_LATENCY_BUFFER_SHFT                   0

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_DMA_NON_SECURED
 *--------------------------------------------------------------------------*/

#define HWIO_ECPRI_STATUS_XBAR_FH_PORT_RX_ADDR                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x104)
#define HWIO_ECPRI_STATUS_XBAR_FH_PORT_RX_PHYS                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x104)
#define HWIO_ECPRI_STATUS_XBAR_FH_PORT_RX_OFFS                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x104)
#define HWIO_ECPRI_STATUS_XBAR_FH_PORT_RX_RMSK                                                                       0x3fffffff
#define HWIO_ECPRI_STATUS_XBAR_FH_PORT_RX_ATTR                                                                                    0x1
#define HWIO_ECPRI_STATUS_XBAR_FH_PORT_RX_IN                    \
                in_dword(HWIO_ECPRI_STATUS_XBAR_FH_PORT_RX_ADDR)
#define HWIO_ECPRI_STATUS_XBAR_FH_PORT_RX_INM(m)            \
                in_dword_masked(HWIO_ECPRI_STATUS_XBAR_FH_PORT_RX_ADDR, m)
#define HWIO_ECPRI_STATUS_XBAR_FH_PORT_RX_PKT_RX_CNT_RX2_BMSK                                                        0x3ff00000
#define HWIO_ECPRI_STATUS_XBAR_FH_PORT_RX_PKT_RX_CNT_RX2_SHFT                                                                20
#define HWIO_ECPRI_STATUS_XBAR_FH_PORT_RX_PKT_RX_CNT_RX1_BMSK                                                           0xffc00
#define HWIO_ECPRI_STATUS_XBAR_FH_PORT_RX_PKT_RX_CNT_RX1_SHFT                                                                10
#define HWIO_ECPRI_STATUS_XBAR_FH_PORT_RX_PKT_RX_CNT_RX0_BMSK                                                             0x3ff
#define HWIO_ECPRI_STATUS_XBAR_FH_PORT_RX_PKT_RX_CNT_RX0_SHFT                                                                 0

#define HWIO_ECPRI_STATUS_XBAR_FH_PORT_TX_ADDR                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x108)
#define HWIO_ECPRI_STATUS_XBAR_FH_PORT_TX_PHYS                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x108)
#define HWIO_ECPRI_STATUS_XBAR_FH_PORT_TX_OFFS                                                                       (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x108)
#define HWIO_ECPRI_STATUS_XBAR_FH_PORT_TX_RMSK                                                                            0x3ff
#define HWIO_ECPRI_STATUS_XBAR_FH_PORT_TX_ATTR                                                                                    0x1
#define HWIO_ECPRI_STATUS_XBAR_FH_PORT_TX_IN                    \
                in_dword(HWIO_ECPRI_STATUS_XBAR_FH_PORT_TX_ADDR)
#define HWIO_ECPRI_STATUS_XBAR_FH_PORT_TX_INM(m)            \
                in_dword_masked(HWIO_ECPRI_STATUS_XBAR_FH_PORT_TX_ADDR, m)
#define HWIO_ECPRI_STATUS_XBAR_FH_PORT_TX_PKT_TX_CNT_BMSK                                                                 0x3ff
#define HWIO_ECPRI_STATUS_XBAR_FH_PORT_TX_PKT_TX_CNT_SHFT                                                                     0

#define HWIO_ECPRI_STATUS_XBAR_C2C_PORT_RX_ADDR                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x10c)
#define HWIO_ECPRI_STATUS_XBAR_C2C_PORT_RX_PHYS                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x10c)
#define HWIO_ECPRI_STATUS_XBAR_C2C_PORT_RX_OFFS                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x10c)
#define HWIO_ECPRI_STATUS_XBAR_C2C_PORT_RX_RMSK                                                                      0x3fffffff
#define HWIO_ECPRI_STATUS_XBAR_C2C_PORT_RX_ATTR                                                                                   0x1
#define HWIO_ECPRI_STATUS_XBAR_C2C_PORT_RX_IN                    \
                in_dword(HWIO_ECPRI_STATUS_XBAR_C2C_PORT_RX_ADDR)
#define HWIO_ECPRI_STATUS_XBAR_C2C_PORT_RX_INM(m)            \
                in_dword_masked(HWIO_ECPRI_STATUS_XBAR_C2C_PORT_RX_ADDR, m)
#define HWIO_ECPRI_STATUS_XBAR_C2C_PORT_RX_PKT_RX_CNT_RX2_BMSK                                                       0x3ff00000
#define HWIO_ECPRI_STATUS_XBAR_C2C_PORT_RX_PKT_RX_CNT_RX2_SHFT                                                               20
#define HWIO_ECPRI_STATUS_XBAR_C2C_PORT_RX_PKT_RX_CNT_RX1_BMSK                                                          0xffc00
#define HWIO_ECPRI_STATUS_XBAR_C2C_PORT_RX_PKT_RX_CNT_RX1_SHFT                                                               10
#define HWIO_ECPRI_STATUS_XBAR_C2C_PORT_RX_PKT_RX_CNT_RX0_BMSK                                                            0x3ff
#define HWIO_ECPRI_STATUS_XBAR_C2C_PORT_RX_PKT_RX_CNT_RX0_SHFT                                                                0

#define HWIO_ECPRI_STATUS_XBAR_C2C_PORT_TX_ADDR                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x120)
#define HWIO_ECPRI_STATUS_XBAR_C2C_PORT_TX_PHYS                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x120)
#define HWIO_ECPRI_STATUS_XBAR_C2C_PORT_TX_OFFS                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x120)
#define HWIO_ECPRI_STATUS_XBAR_C2C_PORT_TX_RMSK                                                                           0x3ff
#define HWIO_ECPRI_STATUS_XBAR_C2C_PORT_TX_ATTR                                                                                   0x1
#define HWIO_ECPRI_STATUS_XBAR_C2C_PORT_TX_IN                    \
                in_dword(HWIO_ECPRI_STATUS_XBAR_C2C_PORT_TX_ADDR)
#define HWIO_ECPRI_STATUS_XBAR_C2C_PORT_TX_INM(m)            \
                in_dword_masked(HWIO_ECPRI_STATUS_XBAR_C2C_PORT_TX_ADDR, m)
#define HWIO_ECPRI_STATUS_XBAR_C2C_PORT_TX_PKT_TX_CNT_BMSK                                                                0x3ff
#define HWIO_ECPRI_STATUS_XBAR_C2C_PORT_TX_PKT_TX_CNT_SHFT                                                                    0

#define HWIO_ECPRI_INTERFACE_DDH_DF_ADDR                                                                             (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x130)
#define HWIO_ECPRI_INTERFACE_DDH_DF_PHYS                                                                             (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x130)
#define HWIO_ECPRI_INTERFACE_DDH_DF_OFFS                                                                             (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x130)
#define HWIO_ECPRI_INTERFACE_DDH_DF_RMSK                                                                             0x117fffff
#define HWIO_ECPRI_INTERFACE_DDH_DF_ATTR                                                                                          0x1
#define HWIO_ECPRI_INTERFACE_DDH_DF_IN                    \
                in_dword(HWIO_ECPRI_INTERFACE_DDH_DF_ADDR)
#define HWIO_ECPRI_INTERFACE_DDH_DF_INM(m)            \
                in_dword_masked(HWIO_ECPRI_INTERFACE_DDH_DF_ADDR, m)
#define HWIO_ECPRI_INTERFACE_DDH_DF_EMPTY_BMSK                                                                       0x10000000
#define HWIO_ECPRI_INTERFACE_DDH_DF_EMPTY_SHFT                                                                               28
#define HWIO_ECPRI_INTERFACE_DDH_DF_DST_TYPE_BMSK                                                                     0x1000000
#define HWIO_ECPRI_INTERFACE_DDH_DF_DST_TYPE_SHFT                                                                            24
#define HWIO_ECPRI_INTERFACE_DDH_DF_CHANNEL_BMSK                                                                       0x7f0000
#define HWIO_ECPRI_INTERFACE_DDH_DF_CHANNEL_SHFT                                                                             16
#define HWIO_ECPRI_INTERFACE_DDH_DF_GSI_BMSK                                                                             0xc000
#define HWIO_ECPRI_INTERFACE_DDH_DF_GSI_SHFT                                                                                 14
#define HWIO_ECPRI_INTERFACE_DDH_DF_SIZE_BMSK                                                                            0x3fff
#define HWIO_ECPRI_INTERFACE_DDH_DF_SIZE_SHFT                                                                                 0

#define HWIO_ECPRI_INTERFACE_DF_C2C_ADDR                                                                             (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x134)
#define HWIO_ECPRI_INTERFACE_DF_C2C_PHYS                                                                             (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x134)
#define HWIO_ECPRI_INTERFACE_DF_C2C_OFFS                                                                             (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x134)
#define HWIO_ECPRI_INTERFACE_DF_C2C_RMSK                                                                             0x117fffff
#define HWIO_ECPRI_INTERFACE_DF_C2C_ATTR                                                                                          0x1
#define HWIO_ECPRI_INTERFACE_DF_C2C_IN                    \
                in_dword(HWIO_ECPRI_INTERFACE_DF_C2C_ADDR)
#define HWIO_ECPRI_INTERFACE_DF_C2C_INM(m)            \
                in_dword_masked(HWIO_ECPRI_INTERFACE_DF_C2C_ADDR, m)
#define HWIO_ECPRI_INTERFACE_DF_C2C_EMPTY_BMSK                                                                       0x10000000
#define HWIO_ECPRI_INTERFACE_DF_C2C_EMPTY_SHFT                                                                               28
#define HWIO_ECPRI_INTERFACE_DF_C2C_DST_TYPE_BMSK                                                                     0x1000000
#define HWIO_ECPRI_INTERFACE_DF_C2C_DST_TYPE_SHFT                                                                            24
#define HWIO_ECPRI_INTERFACE_DF_C2C_CHANNEL_BMSK                                                                       0x7f0000
#define HWIO_ECPRI_INTERFACE_DF_C2C_CHANNEL_SHFT                                                                             16
#define HWIO_ECPRI_INTERFACE_DF_C2C_GSI_BMSK                                                                             0xc000
#define HWIO_ECPRI_INTERFACE_DF_C2C_GSI_SHFT                                                                                 14
#define HWIO_ECPRI_INTERFACE_DF_C2C_SIZE_BMSK                                                                            0x3fff
#define HWIO_ECPRI_INTERFACE_DF_C2C_SIZE_SHFT                                                                                 0

#define HWIO_ECPRI_INTERFACE_DF_NSO_ADDR                                                                             (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x138)
#define HWIO_ECPRI_INTERFACE_DF_NSO_PHYS                                                                             (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x138)
#define HWIO_ECPRI_INTERFACE_DF_NSO_OFFS                                                                             (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x138)
#define HWIO_ECPRI_INTERFACE_DF_NSO_RMSK                                                                             0x117fffff
#define HWIO_ECPRI_INTERFACE_DF_NSO_ATTR                                                                                          0x1
#define HWIO_ECPRI_INTERFACE_DF_NSO_IN                    \
                in_dword(HWIO_ECPRI_INTERFACE_DF_NSO_ADDR)
#define HWIO_ECPRI_INTERFACE_DF_NSO_INM(m)            \
                in_dword_masked(HWIO_ECPRI_INTERFACE_DF_NSO_ADDR, m)
#define HWIO_ECPRI_INTERFACE_DF_NSO_EMPTY_BMSK                                                                       0x10000000
#define HWIO_ECPRI_INTERFACE_DF_NSO_EMPTY_SHFT                                                                               28
#define HWIO_ECPRI_INTERFACE_DF_NSO_DST_TYPE_BMSK                                                                     0x1000000
#define HWIO_ECPRI_INTERFACE_DF_NSO_DST_TYPE_SHFT                                                                            24
#define HWIO_ECPRI_INTERFACE_DF_NSO_CHANNEL_BMSK                                                                       0x7f0000
#define HWIO_ECPRI_INTERFACE_DF_NSO_CHANNEL_SHFT                                                                             16
#define HWIO_ECPRI_INTERFACE_DF_NSO_GSI_BMSK                                                                             0xc000
#define HWIO_ECPRI_INTERFACE_DF_NSO_GSI_SHFT                                                                                 14
#define HWIO_ECPRI_INTERFACE_DF_NSO_SIZE_BMSK                                                                            0x3fff
#define HWIO_ECPRI_INTERFACE_DF_NSO_SIZE_SHFT                                                                                 0

#define HWIO_ECPRI_INTERFACE_DF_FH_ADDR                                                                              (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x13c)
#define HWIO_ECPRI_INTERFACE_DF_FH_PHYS                                                                              (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x13c)
#define HWIO_ECPRI_INTERFACE_DF_FH_OFFS                                                                              (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x13c)
#define HWIO_ECPRI_INTERFACE_DF_FH_RMSK                                                                              0x117fffff
#define HWIO_ECPRI_INTERFACE_DF_FH_ATTR                                                                                           0x1
#define HWIO_ECPRI_INTERFACE_DF_FH_IN                    \
                in_dword(HWIO_ECPRI_INTERFACE_DF_FH_ADDR)
#define HWIO_ECPRI_INTERFACE_DF_FH_INM(m)            \
                in_dword_masked(HWIO_ECPRI_INTERFACE_DF_FH_ADDR, m)
#define HWIO_ECPRI_INTERFACE_DF_FH_EMPTY_BMSK                                                                        0x10000000
#define HWIO_ECPRI_INTERFACE_DF_FH_EMPTY_SHFT                                                                                28
#define HWIO_ECPRI_INTERFACE_DF_FH_DST_TYPE_BMSK                                                                      0x1000000
#define HWIO_ECPRI_INTERFACE_DF_FH_DST_TYPE_SHFT                                                                             24
#define HWIO_ECPRI_INTERFACE_DF_FH_CHANNEL_BMSK                                                                        0x7f0000
#define HWIO_ECPRI_INTERFACE_DF_FH_CHANNEL_SHFT                                                                              16
#define HWIO_ECPRI_INTERFACE_DF_FH_GSI_BMSK                                                                              0xc000
#define HWIO_ECPRI_INTERFACE_DF_FH_GSI_SHFT                                                                                  14
#define HWIO_ECPRI_INTERFACE_DF_FH_SIZE_BMSK                                                                             0x3fff
#define HWIO_ECPRI_INTERFACE_DF_FH_SIZE_SHFT                                                                                  0

#define HWIO_ECPRI_INTERFACE_DF_TXM_ADDR                                                                             (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x140)
#define HWIO_ECPRI_INTERFACE_DF_TXM_PHYS                                                                             (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x140)
#define HWIO_ECPRI_INTERFACE_DF_TXM_OFFS                                                                             (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x140)
#define HWIO_ECPRI_INTERFACE_DF_TXM_RMSK                                                                             0x117fffff
#define HWIO_ECPRI_INTERFACE_DF_TXM_ATTR                                                                                          0x1
#define HWIO_ECPRI_INTERFACE_DF_TXM_IN                    \
                in_dword(HWIO_ECPRI_INTERFACE_DF_TXM_ADDR)
#define HWIO_ECPRI_INTERFACE_DF_TXM_INM(m)            \
                in_dword_masked(HWIO_ECPRI_INTERFACE_DF_TXM_ADDR, m)
#define HWIO_ECPRI_INTERFACE_DF_TXM_EMPTY_BMSK                                                                       0x10000000
#define HWIO_ECPRI_INTERFACE_DF_TXM_EMPTY_SHFT                                                                               28
#define HWIO_ECPRI_INTERFACE_DF_TXM_DST_TYPE_BMSK                                                                     0x1000000
#define HWIO_ECPRI_INTERFACE_DF_TXM_DST_TYPE_SHFT                                                                            24
#define HWIO_ECPRI_INTERFACE_DF_TXM_CHANNEL_BMSK                                                                       0x7f0000
#define HWIO_ECPRI_INTERFACE_DF_TXM_CHANNEL_SHFT                                                                             16
#define HWIO_ECPRI_INTERFACE_DF_TXM_GSI_BMSK                                                                             0xc000
#define HWIO_ECPRI_INTERFACE_DF_TXM_GSI_SHFT                                                                                 14
#define HWIO_ECPRI_INTERFACE_DF_TXM_SIZE_BMSK                                                                            0x3fff
#define HWIO_ECPRI_INTERFACE_DF_TXM_SIZE_SHFT                                                                                 0

#define HWIO_ECPRI_INTERFACE_DDH_TXM_ADDR                                                                            (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x144)
#define HWIO_ECPRI_INTERFACE_DDH_TXM_PHYS                                                                            (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x144)
#define HWIO_ECPRI_INTERFACE_DDH_TXM_OFFS                                                                            (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x144)
#define HWIO_ECPRI_INTERFACE_DDH_TXM_RMSK                                                                            0x117fffff
#define HWIO_ECPRI_INTERFACE_DDH_TXM_ATTR                                                                                         0x1
#define HWIO_ECPRI_INTERFACE_DDH_TXM_IN                    \
                in_dword(HWIO_ECPRI_INTERFACE_DDH_TXM_ADDR)
#define HWIO_ECPRI_INTERFACE_DDH_TXM_INM(m)            \
                in_dword_masked(HWIO_ECPRI_INTERFACE_DDH_TXM_ADDR, m)
#define HWIO_ECPRI_INTERFACE_DDH_TXM_EMPTY_BMSK                                                                      0x10000000
#define HWIO_ECPRI_INTERFACE_DDH_TXM_EMPTY_SHFT                                                                              28
#define HWIO_ECPRI_INTERFACE_DDH_TXM_DST_TYPE_BMSK                                                                    0x1000000
#define HWIO_ECPRI_INTERFACE_DDH_TXM_DST_TYPE_SHFT                                                                           24
#define HWIO_ECPRI_INTERFACE_DDH_TXM_CHANNEL_BMSK                                                                      0x7f0000
#define HWIO_ECPRI_INTERFACE_DDH_TXM_CHANNEL_SHFT                                                                            16
#define HWIO_ECPRI_INTERFACE_DDH_TXM_GSI_BMSK                                                                            0xc000
#define HWIO_ECPRI_INTERFACE_DDH_TXM_GSI_SHFT                                                                                14
#define HWIO_ECPRI_INTERFACE_DDH_TXM_SIZE_BMSK                                                                           0x3fff
#define HWIO_ECPRI_INTERFACE_DDH_TXM_SIZE_SHFT                                                                                0

#define HWIO_ECPRI_STATUS_GSI0_A_ADDR                                                                                (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x150)
#define HWIO_ECPRI_STATUS_GSI0_A_PHYS                                                                                (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x150)
#define HWIO_ECPRI_STATUS_GSI0_A_OFFS                                                                                (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x150)
#define HWIO_ECPRI_STATUS_GSI0_A_RMSK                                                                                0x3fffffff
#define HWIO_ECPRI_STATUS_GSI0_A_ATTR                                                                                             0x1
#define HWIO_ECPRI_STATUS_GSI0_A_IN                    \
                in_dword(HWIO_ECPRI_STATUS_GSI0_A_ADDR)
#define HWIO_ECPRI_STATUS_GSI0_A_INM(m)            \
                in_dword_masked(HWIO_ECPRI_STATUS_GSI0_A_ADDR, m)
#define HWIO_ECPRI_STATUS_GSI0_A_FRAG_CNT_BMSK                                                                       0x3ff00000
#define HWIO_ECPRI_STATUS_GSI0_A_FRAG_CNT_SHFT                                                                               20
#define HWIO_ECPRI_STATUS_GSI0_A_PKT_CNT_BMSK                                                                           0xffc00
#define HWIO_ECPRI_STATUS_GSI0_A_PKT_CNT_SHFT                                                                                10
#define HWIO_ECPRI_STATUS_GSI0_A_TRE_CNT_BMSK                                                                             0x3ff
#define HWIO_ECPRI_STATUS_GSI0_A_TRE_CNT_SHFT                                                                                 0

#define HWIO_ECPRI_STATUS_GSI0_B_ADDR                                                                                (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x154)
#define HWIO_ECPRI_STATUS_GSI0_B_PHYS                                                                                (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x154)
#define HWIO_ECPRI_STATUS_GSI0_B_OFFS                                                                                (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x154)
#define HWIO_ECPRI_STATUS_GSI0_B_RMSK                                                                                   0xfffff
#define HWIO_ECPRI_STATUS_GSI0_B_ATTR                                                                                             0x1
#define HWIO_ECPRI_STATUS_GSI0_B_IN                    \
                in_dword(HWIO_ECPRI_STATUS_GSI0_B_ADDR)
#define HWIO_ECPRI_STATUS_GSI0_B_INM(m)            \
                in_dword_masked(HWIO_ECPRI_STATUS_GSI0_B_ADDR, m)
#define HWIO_ECPRI_STATUS_GSI0_B_DST_AOS_CNT_BMSK                                                                       0xffc00
#define HWIO_ECPRI_STATUS_GSI0_B_DST_AOS_CNT_SHFT                                                                            10
#define HWIO_ECPRI_STATUS_GSI0_B_SRC_AOS_CNT_BMSK                                                                         0x3ff
#define HWIO_ECPRI_STATUS_GSI0_B_SRC_AOS_CNT_SHFT                                                                             0

#define HWIO_ECPRI_STATUS_GSI1_A_ADDR                                                                                (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x158)
#define HWIO_ECPRI_STATUS_GSI1_A_PHYS                                                                                (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x158)
#define HWIO_ECPRI_STATUS_GSI1_A_OFFS                                                                                (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x158)
#define HWIO_ECPRI_STATUS_GSI1_A_RMSK                                                                                0x3fffffff
#define HWIO_ECPRI_STATUS_GSI1_A_ATTR                                                                                             0x1
#define HWIO_ECPRI_STATUS_GSI1_A_IN                    \
                in_dword(HWIO_ECPRI_STATUS_GSI1_A_ADDR)
#define HWIO_ECPRI_STATUS_GSI1_A_INM(m)            \
                in_dword_masked(HWIO_ECPRI_STATUS_GSI1_A_ADDR, m)
#define HWIO_ECPRI_STATUS_GSI1_A_FRAG_CNT_BMSK                                                                       0x3ff00000
#define HWIO_ECPRI_STATUS_GSI1_A_FRAG_CNT_SHFT                                                                               20
#define HWIO_ECPRI_STATUS_GSI1_A_PKT_CNT_BMSK                                                                           0xffc00
#define HWIO_ECPRI_STATUS_GSI1_A_PKT_CNT_SHFT                                                                                10
#define HWIO_ECPRI_STATUS_GSI1_A_TRE_CNT_BMSK                                                                             0x3ff
#define HWIO_ECPRI_STATUS_GSI1_A_TRE_CNT_SHFT                                                                                 0

#define HWIO_ECPRI_STATUS_GSI1_B_ADDR                                                                                (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x15c)
#define HWIO_ECPRI_STATUS_GSI1_B_PHYS                                                                                (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x15c)
#define HWIO_ECPRI_STATUS_GSI1_B_OFFS                                                                                (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x15c)
#define HWIO_ECPRI_STATUS_GSI1_B_RMSK                                                                                   0xfffff
#define HWIO_ECPRI_STATUS_GSI1_B_ATTR                                                                                             0x1
#define HWIO_ECPRI_STATUS_GSI1_B_IN                    \
                in_dword(HWIO_ECPRI_STATUS_GSI1_B_ADDR)
#define HWIO_ECPRI_STATUS_GSI1_B_INM(m)            \
                in_dword_masked(HWIO_ECPRI_STATUS_GSI1_B_ADDR, m)
#define HWIO_ECPRI_STATUS_GSI1_B_DST_AOS_CNT_BMSK                                                                       0xffc00
#define HWIO_ECPRI_STATUS_GSI1_B_DST_AOS_CNT_SHFT                                                                            10
#define HWIO_ECPRI_STATUS_GSI1_B_SRC_AOS_CNT_BMSK                                                                         0x3ff
#define HWIO_ECPRI_STATUS_GSI1_B_SRC_AOS_CNT_SHFT                                                                             0

#define HWIO_ECPRI_STATUS_GSI2_A_ADDR                                                                                (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x160)
#define HWIO_ECPRI_STATUS_GSI2_A_PHYS                                                                                (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x160)
#define HWIO_ECPRI_STATUS_GSI2_A_OFFS                                                                                (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x160)
#define HWIO_ECPRI_STATUS_GSI2_A_RMSK                                                                                0x3fffffff
#define HWIO_ECPRI_STATUS_GSI2_A_ATTR                                                                                             0x1
#define HWIO_ECPRI_STATUS_GSI2_A_IN                    \
                in_dword(HWIO_ECPRI_STATUS_GSI2_A_ADDR)
#define HWIO_ECPRI_STATUS_GSI2_A_INM(m)            \
                in_dword_masked(HWIO_ECPRI_STATUS_GSI2_A_ADDR, m)
#define HWIO_ECPRI_STATUS_GSI2_A_FRAG_CNT_BMSK                                                                       0x3ff00000
#define HWIO_ECPRI_STATUS_GSI2_A_FRAG_CNT_SHFT                                                                               20
#define HWIO_ECPRI_STATUS_GSI2_A_PKT_CNT_BMSK                                                                           0xffc00
#define HWIO_ECPRI_STATUS_GSI2_A_PKT_CNT_SHFT                                                                                10
#define HWIO_ECPRI_STATUS_GSI2_A_TRE_CNT_BMSK                                                                             0x3ff
#define HWIO_ECPRI_STATUS_GSI2_A_TRE_CNT_SHFT                                                                                 0

#define HWIO_ECPRI_STATUS_GSI2_B_ADDR                                                                                (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x164)
#define HWIO_ECPRI_STATUS_GSI2_B_PHYS                                                                                (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x164)
#define HWIO_ECPRI_STATUS_GSI2_B_OFFS                                                                                (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x164)
#define HWIO_ECPRI_STATUS_GSI2_B_RMSK                                                                                   0xfffff
#define HWIO_ECPRI_STATUS_GSI2_B_ATTR                                                                                             0x1
#define HWIO_ECPRI_STATUS_GSI2_B_IN                    \
                in_dword(HWIO_ECPRI_STATUS_GSI2_B_ADDR)
#define HWIO_ECPRI_STATUS_GSI2_B_INM(m)            \
                in_dword_masked(HWIO_ECPRI_STATUS_GSI2_B_ADDR, m)
#define HWIO_ECPRI_STATUS_GSI2_B_DST_AOS_CNT_BMSK                                                                       0xffc00
#define HWIO_ECPRI_STATUS_GSI2_B_DST_AOS_CNT_SHFT                                                                            10
#define HWIO_ECPRI_STATUS_GSI2_B_SRC_AOS_CNT_BMSK                                                                         0x3ff
#define HWIO_ECPRI_STATUS_GSI2_B_SRC_AOS_CNT_SHFT                                                                             0

#define HWIO_ECPRI_DMA_XBAR_RX_PORT_DPL_STATUS_V2_ADDR                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x200)
#define HWIO_ECPRI_DMA_XBAR_RX_PORT_DPL_STATUS_V2_PHYS                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x200)
#define HWIO_ECPRI_DMA_XBAR_RX_PORT_DPL_STATUS_V2_OFFS                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x200)
#define HWIO_ECPRI_DMA_XBAR_RX_PORT_DPL_STATUS_V2_RMSK                                                                       0x7ff03ff
#define HWIO_ECPRI_DMA_XBAR_RX_PORT_DPL_STATUS_V2_ATTR                                                                                   0x1
#define HWIO_ECPRI_DMA_XBAR_RX_PORT_DPL_STATUS_V2_IN                    \
                in_dword(HWIO_ECPRI_DMA_XBAR_RX_PORT_DPL_STATUS_V2_ADDR)
#define HWIO_ECPRI_DMA_XBAR_RX_PORT_DPL_STATUS_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA_XBAR_RX_PORT_DPL_STATUS_V2_ADDR, m)
#define HWIO_ECPRI_DMA_XBAR_RX_PORT_DPL_STATUS_V2_PORT_SEL_ACT_BMSK                                                          0x7000000
#define HWIO_ECPRI_DMA_XBAR_RX_PORT_DPL_STATUS_V2_PORT_SEL_ACT_SHFT                                                                 24
#define HWIO_ECPRI_DMA_XBAR_RX_PORT_DPL_STATUS_V2_DROP_COUNT_BMSK                                                             0xff0000
#define HWIO_ECPRI_DMA_XBAR_RX_PORT_DPL_STATUS_V2_DROP_COUNT_SHFT                                                                   16
#define HWIO_ECPRI_DMA_XBAR_RX_PORT_DPL_STATUS_V2_DROP_GSI_BMSK                                                                  0x300
#define HWIO_ECPRI_DMA_XBAR_RX_PORT_DPL_STATUS_V2_DROP_GSI_SHFT                                                                      8
#define HWIO_ECPRI_DMA_XBAR_RX_PORT_DPL_STATUS_V2_DROP_CHANNEL_BMSK                                                               0xff
#define HWIO_ECPRI_DMA_XBAR_RX_PORT_DPL_STATUS_V2_DROP_CHANNEL_SHFT                                                                  0

#define HWIO_ECPRI_STATUS_XBAR_RX_PORT_m_ADDR(m)                                                                     (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X204 + (0x4*(m)))
#define HWIO_ECPRI_STATUS_XBAR_RX_PORT_m_PHYS(m)                                                                     (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X204 + (0x4*(m)))
#define HWIO_ECPRI_STATUS_XBAR_RX_PORT_m_OFFS(m)                                                                     (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X204 + (0x4*(m)))
#define HWIO_ECPRI_STATUS_XBAR_RX_PORT_m_RMSK                                                                          0xff03ff
#define HWIO_ECPRI_STATUS_XBAR_RX_PORT_m_MAXm                                                                                 5
#define HWIO_ECPRI_STATUS_XBAR_RX_PORT_m_ATTR                                                                                     0x1
#define HWIO_ECPRI_STATUS_XBAR_RX_PORT_m_INI(m)                \
                in_dword_masked(HWIO_ECPRI_STATUS_XBAR_RX_PORT_m_ADDR(m), HWIO_ECPRI_STATUS_XBAR_RX_PORT_m_RMSK)
#define HWIO_ECPRI_STATUS_XBAR_RX_PORT_m_INMI(m,mask)        \
                in_dword_masked(HWIO_ECPRI_STATUS_XBAR_RX_PORT_m_ADDR(m), mask)
#define HWIO_ECPRI_STATUS_XBAR_RX_PORT_m_DROP_COUNT_BMSK                                                               0xff0000
#define HWIO_ECPRI_STATUS_XBAR_RX_PORT_m_DROP_COUNT_SHFT                                                                     16
#define HWIO_ECPRI_STATUS_XBAR_RX_PORT_m_DROP_GSI_BMSK                                                                    0x300
#define HWIO_ECPRI_STATUS_XBAR_RX_PORT_m_DROP_GSI_SHFT                                                                        8
#define HWIO_ECPRI_STATUS_XBAR_RX_PORT_m_DROP_CHANNEL_BMSK                                                                 0xff
#define HWIO_ECPRI_STATUS_XBAR_RX_PORT_m_DROP_CHANNEL_SHFT                                                                    0

#define HWIO_ECPRI_STATUS_XBAR_RX_DROP_ADDR                                                                          (ECPRI_DMA_NON_SECURED_REG_BASE      + 0x220)
#define HWIO_ECPRI_STATUS_XBAR_RX_DROP_PHYS                                                                          (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0x220)
#define HWIO_ECPRI_STATUS_XBAR_RX_DROP_OFFS                                                                          (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0x220)
#define HWIO_ECPRI_STATUS_XBAR_RX_DROP_RMSK                                                                                0xbf
#define HWIO_ECPRI_STATUS_XBAR_RX_DROP_ATTR                                                                                       0x3
#define HWIO_ECPRI_STATUS_XBAR_RX_DROP_IN                    \
                in_dword(HWIO_ECPRI_STATUS_XBAR_RX_DROP_ADDR)
#define HWIO_ECPRI_STATUS_XBAR_RX_DROP_INM(m)            \
                in_dword_masked(HWIO_ECPRI_STATUS_XBAR_RX_DROP_ADDR, m)
#define HWIO_ECPRI_STATUS_XBAR_RX_DROP_OUT(v)            \
                out_dword(HWIO_ECPRI_STATUS_XBAR_RX_DROP_ADDR,v)
#define HWIO_ECPRI_STATUS_XBAR_RX_DROP_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_STATUS_XBAR_RX_DROP_ADDR,m,v,HWIO_ECPRI_STATUS_XBAR_RX_DROP_IN)
#define HWIO_ECPRI_STATUS_XBAR_RX_DROP_CLR_BMSK                                                                            0x80
#define HWIO_ECPRI_STATUS_XBAR_RX_DROP_CLR_SHFT                                                                               7
#define HWIO_ECPRI_STATUS_XBAR_RX_DROP_PORT_BMSK                                                                           0x3f
#define HWIO_ECPRI_STATUS_XBAR_RX_DROP_PORT_SHFT                                                                              0

#define HWIO_ECPRI_SPARE_REG_V2_ADDR                                                                                    (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xffc)
#define HWIO_ECPRI_SPARE_REG_V2_PHYS                                                                                    (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xffc)
#define HWIO_ECPRI_SPARE_REG_V2_OFFS                                                                                    (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xffc)
#define HWIO_ECPRI_SPARE_REG_V2_RMSK                                                                                        0xffff
#define HWIO_ECPRI_SPARE_REG_V2_ATTR                                                                                                 0x3
#define HWIO_ECPRI_SPARE_REG_V2_IN                    \
                in_dword(HWIO_ECPRI_SPARE_REG_V2_ADDR)
#define HWIO_ECPRI_SPARE_REG_V2_INM(m)            \
                in_dword_masked(HWIO_ECPRI_SPARE_REG_V2_ADDR, m)
#define HWIO_ECPRI_SPARE_REG_V2_OUT(v)            \
                out_dword(HWIO_ECPRI_SPARE_REG_V2_ADDR,v)
#define HWIO_ECPRI_SPARE_REG_V2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_SPARE_REG_V2_ADDR,m,v,HWIO_ECPRI_SPARE_REG_V2_IN)
#define HWIO_ECPRI_SPARE_REG_V2_SPARE_BITS_BMSK                                                                             0xffff
#define HWIO_ECPRI_SPARE_REG_V2_SPARE_BITS_SHFT
#define HWIO_ECPRI_ENDP_LTE_CFG_GSI_m_CH_n_ADDR(m,n)                                                                 (ECPRI_DMA_NON_SECURED_REG_BASE      + 0X1018 + (0x2000*(m)) + (0x40*(n)))
#define HWIO_ECPRI_ENDP_LTE_CFG_GSI_m_CH_n_PHYS(m,n)                                                                 (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0X1018 + (0x2000*(m)) + (0x40*(n)))
#define HWIO_ECPRI_ENDP_LTE_CFG_GSI_m_CH_n_OFFS(m,n)                                                                 (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0X1018 + (0x2000*(m)) + (0x40*(n)))
#define HWIO_ECPRI_ENDP_LTE_CFG_GSI_m_CH_n_RMSK                                                                             0x1
#define HWIO_ECPRI_ENDP_LTE_CFG_GSI_m_CH_n_MAXm                                                                               2
#define HWIO_ECPRI_ENDP_LTE_CFG_GSI_m_CH_n_MAXn                                                                              73
#define HWIO_ECPRI_ENDP_LTE_CFG_GSI_m_CH_n_ATTR                                                                                   0x3
#define HWIO_ECPRI_ENDP_LTE_CFG_GSI_m_CH_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_ENDP_LTE_CFG_GSI_m_CH_n_ADDR(m,n), HWIO_ECPRI_ENDP_LTE_CFG_GSI_m_CH_n_RMSK)
#define HWIO_ECPRI_ENDP_LTE_CFG_GSI_m_CH_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_ENDP_LTE_CFG_GSI_m_CH_n_ADDR(m,n), mask)
#define HWIO_ECPRI_ENDP_LTE_CFG_GSI_m_CH_n_OUTI2(m,n,val)        \
                out_dword(HWIO_ECPRI_ENDP_LTE_CFG_GSI_m_CH_n_ADDR(m,n),val)
#define HWIO_ECPRI_ENDP_LTE_CFG_GSI_m_CH_n_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_ECPRI_ENDP_LTE_CFG_GSI_m_CH_n_ADDR(m,n),mask,val,HWIO_ECPRI_ENDP_LTE_CFG_GSI_m_CH_n_INI2(m,n))
#define HWIO_ECPRI_ENDP_LTE_CFG_GSI_m_CH_n_IS_LTE_BMSK                                                                      0x1
#define HWIO_ECPRI_ENDP_LTE_CFG_GSI_m_CH_n_IS_LTE_SHFT                                                                        0

#define HWIO_ECPRI_SDH_PREFETCH_LSB_GSI_m_CH_n_ADDR(m,n)                                                             (ECPRI_DMA_NON_SECURED_REG_BASE      + 0XA000 + (0x200*(m)) + (0x4*(n)))
#define HWIO_ECPRI_SDH_PREFETCH_LSB_GSI_m_CH_n_PHYS(m,n)                                                             (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0XA000 + (0x200*(m)) + (0x4*(n)))
#define HWIO_ECPRI_SDH_PREFETCH_LSB_GSI_m_CH_n_OFFS(m,n)                                                             (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0XA000 + (0x200*(m)) + (0x4*(n)))
#define HWIO_ECPRI_SDH_PREFETCH_LSB_GSI_m_CH_n_RMSK                                                                  0xffffffff
#define HWIO_ECPRI_SDH_PREFETCH_LSB_GSI_m_CH_n_MAXm                                                                           2
#define HWIO_ECPRI_SDH_PREFETCH_LSB_GSI_m_CH_n_MAXn                                                                          36
#define HWIO_ECPRI_SDH_PREFETCH_LSB_GSI_m_CH_n_ATTR                                                                               0x1
#define HWIO_ECPRI_SDH_PREFETCH_LSB_GSI_m_CH_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_SDH_PREFETCH_LSB_GSI_m_CH_n_ADDR(m,n), HWIO_ECPRI_SDH_PREFETCH_LSB_GSI_m_CH_n_RMSK)
#define HWIO_ECPRI_SDH_PREFETCH_LSB_GSI_m_CH_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_SDH_PREFETCH_LSB_GSI_m_CH_n_ADDR(m,n), mask)
#define HWIO_ECPRI_SDH_PREFETCH_LSB_GSI_m_CH_n_ADDR_31_0_BMSK                                                        0xffffffff
#define HWIO_ECPRI_SDH_PREFETCH_LSB_GSI_m_CH_n_ADDR_31_0_SHFT                                                                 0

#define HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_ADDR(m,n)                                                             (ECPRI_DMA_NON_SECURED_REG_BASE      + 0XA800 + (0x200*(m)) + (0x4*(n)))
#define HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_PHYS(m,n)                                                             (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0XA800 + (0x200*(m)) + (0x4*(n)))
#define HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_OFFS(m,n)                                                             (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0XA800 + (0x200*(m)) + (0x4*(n)))
#define HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_RMSK                                                                  0xffffffff
#define HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_MAXm                                                                           2
#define HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_MAXn                                                                          36
#define HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_ATTR                                                                               0x1
#define HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_ADDR(m,n), HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_RMSK)
#define HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_ADDR(m,n), mask)
#define HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_ADDR_40_BMSK                                                          0x80000000
#define HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_ADDR_40_SHFT                                                                  31
#define HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_ADDR_38_32_BMSK                                                       0x7f000000
#define HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_ADDR_38_32_SHFT                                                               24
#define HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_CHAIN_BMSK                                                              0x800000
#define HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_CHAIN_SHFT                                                                    23
#define HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_MIRROR_BMSK                                                             0x400000
#define HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_MIRROR_SHFT                                                                   22
#define HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_REDIRECT_BMSK                                                           0x200000
#define HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_REDIRECT_SHFT                                                                 21
#define HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_LENGTH_BMSK                                                             0x1fffff
#define HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_LENGTH_SHFT                                                                    0

#define HWIO_ECPRI_STATUS_LTE_PKT_DROP_FULL_ADDR                                                                     (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xb004)
#define HWIO_ECPRI_STATUS_LTE_PKT_DROP_FULL_PHYS                                                                     (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xb004)
#define HWIO_ECPRI_STATUS_LTE_PKT_DROP_FULL_OFFS                                                                     (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xb004)
#define HWIO_ECPRI_STATUS_LTE_PKT_DROP_FULL_RMSK                                                                       0xffffff
#define HWIO_ECPRI_STATUS_LTE_PKT_DROP_FULL_ATTR                                                                                  0x1
#define HWIO_ECPRI_STATUS_LTE_PKT_DROP_FULL_IN                    \
                in_dword(HWIO_ECPRI_STATUS_LTE_PKT_DROP_FULL_ADDR)
#define HWIO_ECPRI_STATUS_LTE_PKT_DROP_FULL_INM(m)            \
                in_dword_masked(HWIO_ECPRI_STATUS_LTE_PKT_DROP_FULL_ADDR, m)
#define HWIO_ECPRI_STATUS_LTE_PKT_DROP_FULL_CNT_BMSK                                                                   0xffffff
#define HWIO_ECPRI_STATUS_LTE_PKT_DROP_FULL_CNT_SHFT                                                                          0

#define HWIO_ECPRI_RATE_LIMITER_ADDR                                                                                 (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe038)
#define HWIO_ECPRI_RATE_LIMITER_PHYS                                                                                 (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe038)
#define HWIO_ECPRI_RATE_LIMITER_OFFS                                                                                 (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe038)
#define HWIO_ECPRI_RATE_LIMITER_RMSK                                                                                   0xffffff
#define HWIO_ECPRI_RATE_LIMITER_ATTR                                                                                              0x3
#define HWIO_ECPRI_RATE_LIMITER_IN                    \
                in_dword(HWIO_ECPRI_RATE_LIMITER_ADDR)
#define HWIO_ECPRI_RATE_LIMITER_INM(m)            \
                in_dword_masked(HWIO_ECPRI_RATE_LIMITER_ADDR, m)
#define HWIO_ECPRI_RATE_LIMITER_OUT(v)            \
                out_dword(HWIO_ECPRI_RATE_LIMITER_ADDR,v)
#define HWIO_ECPRI_RATE_LIMITER_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_RATE_LIMITER_ADDR,m,v,HWIO_ECPRI_RATE_LIMITER_IN)
#define HWIO_ECPRI_RATE_LIMITER_C2C_BMSK                                                                               0xff0000
#define HWIO_ECPRI_RATE_LIMITER_C2C_SHFT                                                                                     16
#define HWIO_ECPRI_RATE_LIMITER_L2_BMSK                                                                                  0xff00
#define HWIO_ECPRI_RATE_LIMITER_L2_SHFT                                                                                       8
#define HWIO_ECPRI_RATE_LIMITER_FH_BMSK                                                                                    0xff
#define HWIO_ECPRI_RATE_LIMITER_FH_SHFT                                                                                       0

#define HWIO_ECPRI_DPL_MONITOR_CFG_ADDR                                                                              (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe09c)
#define HWIO_ECPRI_DPL_MONITOR_CFG_PHYS                                                                              (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe09c)
#define HWIO_ECPRI_DPL_MONITOR_CFG_OFFS                                                                              (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe09c)
#define HWIO_ECPRI_DPL_MONITOR_CFG_RMSK                                                                                     0x1
#define HWIO_ECPRI_DPL_MONITOR_CFG_ATTR                                                                                           0x3
#define HWIO_ECPRI_DPL_MONITOR_CFG_IN                    \
                in_dword(HWIO_ECPRI_DPL_MONITOR_CFG_ADDR)
#define HWIO_ECPRI_DPL_MONITOR_CFG_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DPL_MONITOR_CFG_ADDR, m)
#define HWIO_ECPRI_DPL_MONITOR_CFG_OUT(v)            \
                out_dword(HWIO_ECPRI_DPL_MONITOR_CFG_ADDR,v)
#define HWIO_ECPRI_DPL_MONITOR_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DPL_MONITOR_CFG_ADDR,m,v,HWIO_ECPRI_DPL_MONITOR_CFG_IN)
#define HWIO_ECPRI_DPL_MONITOR_CFG_ENABLE_BMSK                                                                              0x1
#define HWIO_ECPRI_DPL_MONITOR_CFG_ENABLE_SHFT                                                                                0

#define HWIO_ECPRI_DPL_MONITOR_CNT_0_ADDR                                                                            (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe0a0)
#define HWIO_ECPRI_DPL_MONITOR_CNT_0_PHYS                                                                            (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe0a0)
#define HWIO_ECPRI_DPL_MONITOR_CNT_0_OFFS                                                                            (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe0a0)
#define HWIO_ECPRI_DPL_MONITOR_CNT_0_RMSK                                                                                  0xff
#define HWIO_ECPRI_DPL_MONITOR_CNT_0_ATTR                                                                                         0x1
#define HWIO_ECPRI_DPL_MONITOR_CNT_0_IN                    \
                in_dword(HWIO_ECPRI_DPL_MONITOR_CNT_0_ADDR)
#define HWIO_ECPRI_DPL_MONITOR_CNT_0_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DPL_MONITOR_CNT_0_ADDR, m)
#define HWIO_ECPRI_DPL_MONITOR_CNT_0_CNT_BMSK                                                                              0xff
#define HWIO_ECPRI_DPL_MONITOR_CNT_0_CNT_SHFT                                                                                 0

#define HWIO_ECPRI_DPL_MONITOR_CNT_1_ADDR                                                                            (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe0a4)
#define HWIO_ECPRI_DPL_MONITOR_CNT_1_PHYS                                                                            (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe0a4)
#define HWIO_ECPRI_DPL_MONITOR_CNT_1_OFFS                                                                            (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe0a4)
#define HWIO_ECPRI_DPL_MONITOR_CNT_1_RMSK                                                                                  0xff
#define HWIO_ECPRI_DPL_MONITOR_CNT_1_ATTR                                                                                         0x1
#define HWIO_ECPRI_DPL_MONITOR_CNT_1_IN                    \
                in_dword(HWIO_ECPRI_DPL_MONITOR_CNT_1_ADDR)
#define HWIO_ECPRI_DPL_MONITOR_CNT_1_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DPL_MONITOR_CNT_1_ADDR, m)
#define HWIO_ECPRI_DPL_MONITOR_CNT_1_CNT_BMSK                                                                              0xff
#define HWIO_ECPRI_DPL_MONITOR_CNT_1_CNT_SHFT                                                                                 0

#define HWIO_ECPRI_REDIRECT_CHANNEL_ADDR                                                                             (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe0a8)
#define HWIO_ECPRI_REDIRECT_CHANNEL_PHYS                                                                             (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe0a8)
#define HWIO_ECPRI_REDIRECT_CHANNEL_OFFS                                                                             (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe0a8)
#define HWIO_ECPRI_REDIRECT_CHANNEL_RMSK                                                                                  0xfff
#define HWIO_ECPRI_REDIRECT_CHANNEL_ATTR                                                                                          0x3
#define HWIO_ECPRI_REDIRECT_CHANNEL_IN                    \
                in_dword(HWIO_ECPRI_REDIRECT_CHANNEL_ADDR)
#define HWIO_ECPRI_REDIRECT_CHANNEL_INM(m)            \
                in_dword_masked(HWIO_ECPRI_REDIRECT_CHANNEL_ADDR, m)
#define HWIO_ECPRI_REDIRECT_CHANNEL_OUT(v)            \
                out_dword(HWIO_ECPRI_REDIRECT_CHANNEL_ADDR,v)
#define HWIO_ECPRI_REDIRECT_CHANNEL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_REDIRECT_CHANNEL_ADDR,m,v,HWIO_ECPRI_REDIRECT_CHANNEL_IN)
#define HWIO_ECPRI_REDIRECT_CHANNEL_XBAR_RX_PORT_BMSK                                                                     0xc00
#define HWIO_ECPRI_REDIRECT_CHANNEL_XBAR_RX_PORT_SHFT                                                                        10
#define HWIO_ECPRI_REDIRECT_CHANNEL_GID_BMSK                                                                              0x300
#define HWIO_ECPRI_REDIRECT_CHANNEL_GID_SHFT                                                                                  8
#define HWIO_ECPRI_REDIRECT_CHANNEL_CHANNEL_BMSK                                                                           0xff
#define HWIO_ECPRI_REDIRECT_CHANNEL_CHANNEL_SHFT                                                                              0

#define HWIO_ECPRI_STATUS_DST_DROP_PKT_GSI_m_REG_n_ADDR(m,n)                                                         (ECPRI_DMA_NON_SECURED_REG_BASE      + 0XE0B0 + (0x8*(m)) + (0x4*(n)))
#define HWIO_ECPRI_STATUS_DST_DROP_PKT_GSI_m_REG_n_PHYS(m,n)                                                         (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0XE0B0 + (0x8*(m)) + (0x4*(n)))
#define HWIO_ECPRI_STATUS_DST_DROP_PKT_GSI_m_REG_n_OFFS(m,n)                                                         (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0XE0B0 + (0x8*(m)) + (0x4*(n)))
#define HWIO_ECPRI_STATUS_DST_DROP_PKT_GSI_m_REG_n_RMSK                                                              0xffffffff
#define HWIO_ECPRI_STATUS_DST_DROP_PKT_GSI_m_REG_n_MAXm                                                                       2
#define HWIO_ECPRI_STATUS_DST_DROP_PKT_GSI_m_REG_n_MAXn                                                                       1
#define HWIO_ECPRI_STATUS_DST_DROP_PKT_GSI_m_REG_n_ATTR                                                                           0x1
#define HWIO_ECPRI_STATUS_DST_DROP_PKT_GSI_m_REG_n_INI2(m,n)                \
                in_dword_masked(HWIO_ECPRI_STATUS_DST_DROP_PKT_GSI_m_REG_n_ADDR(m,n), HWIO_ECPRI_STATUS_DST_DROP_PKT_GSI_m_REG_n_RMSK)
#define HWIO_ECPRI_STATUS_DST_DROP_PKT_GSI_m_REG_n_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_ECPRI_STATUS_DST_DROP_PKT_GSI_m_REG_n_ADDR(m,n), mask)
#define HWIO_ECPRI_STATUS_DST_DROP_PKT_GSI_m_REG_n_DROP_BMSK                                                         0xffffffff
#define HWIO_ECPRI_STATUS_DST_DROP_PKT_GSI_m_REG_n_DROP_SHFT                                                                  0

#define HWIO_ECPRI_STATUS_DST_DROP_PKT_CLEAR_ADDR                                                                    (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe0d0)
#define HWIO_ECPRI_STATUS_DST_DROP_PKT_CLEAR_PHYS                                                                    (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe0d0)
#define HWIO_ECPRI_STATUS_DST_DROP_PKT_CLEAR_OFFS                                                                    (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe0d0)
#define HWIO_ECPRI_STATUS_DST_DROP_PKT_CLEAR_RMSK                                                                          0x7f
#define HWIO_ECPRI_STATUS_DST_DROP_PKT_CLEAR_ATTR                                                                                 0x3
#define HWIO_ECPRI_STATUS_DST_DROP_PKT_CLEAR_IN                    \
                in_dword(HWIO_ECPRI_STATUS_DST_DROP_PKT_CLEAR_ADDR)
#define HWIO_ECPRI_STATUS_DST_DROP_PKT_CLEAR_INM(m)            \
                in_dword_masked(HWIO_ECPRI_STATUS_DST_DROP_PKT_CLEAR_ADDR, m)
#define HWIO_ECPRI_STATUS_DST_DROP_PKT_CLEAR_OUT(v)            \
                out_dword(HWIO_ECPRI_STATUS_DST_DROP_PKT_CLEAR_ADDR,v)
#define HWIO_ECPRI_STATUS_DST_DROP_PKT_CLEAR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_STATUS_DST_DROP_PKT_CLEAR_ADDR,m,v,HWIO_ECPRI_STATUS_DST_DROP_PKT_CLEAR_IN)
#define HWIO_ECPRI_STATUS_DST_DROP_PKT_CLEAR_CLR_ALL_BMSK                                                                  0x40
#define HWIO_ECPRI_STATUS_DST_DROP_PKT_CLEAR_CLR_ALL_SHFT                                                                     6
#define HWIO_ECPRI_STATUS_DST_DROP_PKT_CLEAR_CLR_REG_BMSK                                                                  0x3f
#define HWIO_ECPRI_STATUS_DST_DROP_PKT_CLEAR_CLR_REG_SHFT                                                                     0

#define HWIO_ECPRI_UNIT_CLK_ENABLE_ADDR                                                                              (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xe0d4)
#define HWIO_ECPRI_UNIT_CLK_ENABLE_PHYS                                                                              (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xe0d4)
#define HWIO_ECPRI_UNIT_CLK_ENABLE_OFFS                                                                              (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xe0d4)
#define HWIO_ECPRI_UNIT_CLK_ENABLE_RMSK                                                                                     0xf
#define HWIO_ECPRI_UNIT_CLK_ENABLE_ATTR                                                                                           0x3
#define HWIO_ECPRI_UNIT_CLK_ENABLE_IN                    \
                in_dword(HWIO_ECPRI_UNIT_CLK_ENABLE_ADDR)
#define HWIO_ECPRI_UNIT_CLK_ENABLE_INM(m)            \
                in_dword_masked(HWIO_ECPRI_UNIT_CLK_ENABLE_ADDR, m)
#define HWIO_ECPRI_UNIT_CLK_ENABLE_OUT(v)            \
                out_dword(HWIO_ECPRI_UNIT_CLK_ENABLE_ADDR,v)
#define HWIO_ECPRI_UNIT_CLK_ENABLE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_UNIT_CLK_ENABLE_ADDR,m,v,HWIO_ECPRI_UNIT_CLK_ENABLE_IN)
#define HWIO_ECPRI_UNIT_CLK_ENABLE_NFAPI_EN_BMSK                                                                            0x8
#define HWIO_ECPRI_UNIT_CLK_ENABLE_NFAPI_EN_SHFT                                                                              3
#define HWIO_ECPRI_UNIT_CLK_ENABLE_LTE_EN_BMSK                                                                              0x4
#define HWIO_ECPRI_UNIT_CLK_ENABLE_LTE_EN_SHFT                                                                                2
#define HWIO_ECPRI_UNIT_CLK_ENABLE_GSI_2_EN_BMSK                                                                            0x2
#define HWIO_ECPRI_UNIT_CLK_ENABLE_GSI_2_EN_SHFT                                                                              1
#define HWIO_ECPRI_UNIT_CLK_ENABLE_GSI_1_EN_BMSK                                                                            0x1
#define HWIO_ECPRI_UNIT_CLK_ENABLE_GSI_1_EN_SHFT                                                                              0

#define HWIO_ECPRI_LTE_CFG_ADDR                                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xf000)
#define HWIO_ECPRI_LTE_CFG_PHYS                                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xf000)
#define HWIO_ECPRI_LTE_CFG_OFFS                                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xf000)
#define HWIO_ECPRI_LTE_CFG_RMSK                                                                                       0x1ffffff
#define HWIO_ECPRI_LTE_CFG_ATTR                                                                                                   0x3
#define HWIO_ECPRI_LTE_CFG_IN                    \
                in_dword(HWIO_ECPRI_LTE_CFG_ADDR)
#define HWIO_ECPRI_LTE_CFG_INM(m)            \
                in_dword_masked(HWIO_ECPRI_LTE_CFG_ADDR, m)
#define HWIO_ECPRI_LTE_CFG_OUT(v)            \
                out_dword(HWIO_ECPRI_LTE_CFG_ADDR,v)
#define HWIO_ECPRI_LTE_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_LTE_CFG_ADDR,m,v,HWIO_ECPRI_LTE_CFG_IN)
#define HWIO_ECPRI_LTE_CFG_LTE_FIFO_THRESHOLD_BMSK                                                                    0x1fff000
#define HWIO_ECPRI_LTE_CFG_LTE_FIFO_THRESHOLD_SHFT                                                                           12
#define HWIO_ECPRI_LTE_CFG_LTE_AR_WEIGTH_BMSK                                                                             0xf00
#define HWIO_ECPRI_LTE_CFG_LTE_AR_WEIGTH_SHFT                                                                                 8
#define HWIO_ECPRI_LTE_CFG_LTE_MAX_QMB_OUTSTANDINGS_BMSK                                                                   0xff
#define HWIO_ECPRI_LTE_CFG_LTE_MAX_QMB_OUTSTANDINGS_SHFT                                                                      0

#define HWIO_ECPRI_STATUS_LTE_PKT_DROP_TLV_FIFO_EMPTY_ADDR                                                           (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xf008)
#define HWIO_ECPRI_STATUS_LTE_PKT_DROP_TLV_FIFO_EMPTY_PHYS                                                           (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xf008)
#define HWIO_ECPRI_STATUS_LTE_PKT_DROP_TLV_FIFO_EMPTY_OFFS                                                           (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xf008)
#define HWIO_ECPRI_STATUS_LTE_PKT_DROP_TLV_FIFO_EMPTY_RMSK                                                             0xffffff
#define HWIO_ECPRI_STATUS_LTE_PKT_DROP_TLV_FIFO_EMPTY_ATTR                                                                        0x1
#define HWIO_ECPRI_STATUS_LTE_PKT_DROP_TLV_FIFO_EMPTY_IN                    \
                in_dword(HWIO_ECPRI_STATUS_LTE_PKT_DROP_TLV_FIFO_EMPTY_ADDR)
#define HWIO_ECPRI_STATUS_LTE_PKT_DROP_TLV_FIFO_EMPTY_INM(m)            \
                in_dword_masked(HWIO_ECPRI_STATUS_LTE_PKT_DROP_TLV_FIFO_EMPTY_ADDR, m)
#define HWIO_ECPRI_STATUS_LTE_PKT_DROP_TLV_FIFO_EMPTY_CNT_BMSK                                                         0xffffff
#define HWIO_ECPRI_STATUS_LTE_PKT_DROP_TLV_FIFO_EMPTY_CNT_SHFT                                                                0

#define HWIO_ECPRI_LTE_LATENCY_BUFFER_WORD_ADDR                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE      + 0xf00c)
#define HWIO_ECPRI_LTE_LATENCY_BUFFER_WORD_PHYS                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_PHYS + 0xf00c)
#define HWIO_ECPRI_LTE_LATENCY_BUFFER_WORD_OFFS                                                                      (ECPRI_DMA_NON_SECURED_REG_BASE_OFFS + 0xf00c)
#define HWIO_ECPRI_LTE_LATENCY_BUFFER_WORD_RMSK                                                                          0x1fff
#define HWIO_ECPRI_LTE_LATENCY_BUFFER_WORD_ATTR                                                                                   0x1
#define HWIO_ECPRI_LTE_LATENCY_BUFFER_WORD_IN                    \
                in_dword(HWIO_ECPRI_LTE_LATENCY_BUFFER_WORD_ADDR)
#define HWIO_ECPRI_LTE_LATENCY_BUFFER_WORD_INM(m)            \
                in_dword_masked(HWIO_ECPRI_LTE_LATENCY_BUFFER_WORD_ADDR, m)
#define HWIO_ECPRI_LTE_LATENCY_BUFFER_WORD_CNT_BMSK                                                                      0x1fff
#define HWIO_ECPRI_LTE_LATENCY_BUFFER_WORD_CNT_SHFT                                                                           0

#define HWIO_ECPRI_NFAPI_
/*----------------------------------------------------------------------------
 * MODULE: ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE
 *--------------------------------------------------------------------------*/

#define ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE                                               (ECPRI_DMA1_THROTTLE_THROTTLE_BWMON_WRAPPER_1_BASE      + 0x00000000)
#define ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_SIZE                                          0x100
#define ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_USED                                          0x40
#define ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS                                          (ECPRI_DMA1_THROTTLE_THROTTLE_BWMON_WRAPPER_1_BASE_PHYS + 0x00000000)
#define ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS                                          0x00000000

#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_ADDR                                                            (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x0)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_PHYS                                                            (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x0)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_OFFS                                                            (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x0)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_RMSK                                                                0xff01
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_ATTR                                                                         0x3
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_7_EN_BMSK                                           0x8000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_7_EN_SHFT                                               15
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_6_EN_BMSK                                           0x4000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_6_EN_SHFT                                               14
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_5_EN_BMSK                                           0x2000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_5_EN_SHFT                                               13
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_4_EN_BMSK                                           0x1000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_4_EN_SHFT                                               12
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_3_EN_BMSK                                            0x800
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_3_EN_SHFT                                               11
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_2_EN_BMSK                                            0x400
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_2_EN_SHFT                                               10
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_1_EN_BMSK                                            0x200
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_1_EN_SHFT                                                9
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_0_EN_BMSK                                            0x100
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_0_EN_SHFT                                                8
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_THROTTLE_EN_BMSK                                                       0x1
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_THROTTLE_EN_SHFT                                                         0

#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CGC_CNTRL_ADDR                                                        (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x4)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CGC_CNTRL_PHYS                                                        (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x4)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CGC_CNTRL_OFFS                                                        (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x4)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CGC_CNTRL_RMSK                                                               0x1
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CGC_CNTRL_ATTR                                                                     0x3
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CGC_CNTRL_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CGC_CNTRL_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CGC_CNTRL_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CGC_CNTRL_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CGC_CNTRL_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CGC_CNTRL_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CGC_CNTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CGC_CNTRL_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CGC_CNTRL_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CGC_CNTRL_THROTTLE_CGC_EN_BMSK                                               0x1
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CGC_CNTRL_THROTTLE_CGC_EN_SHFT                                                 0

#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_RESET_CNTRL_ADDR                                                      (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x8)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_RESET_CNTRL_PHYS                                                      (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x8)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_RESET_CNTRL_OFFS                                                      (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x8)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_RESET_CNTRL_RMSK                                                             0x1
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_RESET_CNTRL_ATTR                                                                   0x3
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_RESET_CNTRL_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_RESET_CNTRL_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_RESET_CNTRL_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_RESET_CNTRL_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_RESET_CNTRL_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_RESET_CNTRL_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_RESET_CNTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_RESET_CNTRL_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_RESET_CNTRL_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_RESET_CNTRL_CORE_SW_RESET_BMSK                                               0x1
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_RESET_CNTRL_CORE_SW_RESET_SHFT                                                 0

#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_ADDR                                                           (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0xc)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_PHYS                                                           (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0xc)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_OFFS                                                           (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0xc)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_RMSK                                                                  0x7
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_ATTR                                                                        0x3
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_THROTTLE_CNTRL_MAX_SKEW_BMSK                                          0x7
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_THROTTLE_CNTRL_MAX_SKEW_SHFT                                            0

#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_PERIOD_ADDR                                                     (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x10)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_PERIOD_PHYS                                                     (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x10)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_PERIOD_OFFS                                                     (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x10)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_PERIOD_RMSK                                                         0x3fff
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_PERIOD_ATTR                                                                  0x3
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_PERIOD_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_PERIOD_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_PERIOD_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_PERIOD_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_PERIOD_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_PERIOD_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_PERIOD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_PERIOD_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_PERIOD_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_PERIOD_GRANT_PERIOD_BMSK                                            0x3fff
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_PERIOD_GRANT_PERIOD_SHFT                                                 0

#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_COUNT_ADDR                                                      (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x14)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_COUNT_PHYS                                                      (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x14)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_COUNT_OFFS                                                      (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x14)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_COUNT_RMSK                                                          0xffff
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_COUNT_ATTR                                                                   0x3
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_COUNT_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_COUNT_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_COUNT_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_COUNT_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_COUNT_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_COUNT_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_COUNT_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_COUNT_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_COUNT_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_COUNT_GRANT_COUNT_BMSK                                              0xffff
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_COUNT_GRANT_COUNT_SHFT                                                   0

#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_00_ADDR                                                     (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x18)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_00_PHYS                                                     (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x18)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_00_OFFS                                                     (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x18)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_00_RMSK                                                     0xffffffff
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_00_ATTR                                                                  0x3
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_00_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_00_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_00_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_00_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_00_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_00_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_00_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_00_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_00_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_00_THRESHOLD_LEVEL_6_BMSK                                   0xffff0000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_00_THRESHOLD_LEVEL_6_SHFT                                           16
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_00_THRESHOLD_LEVEL_7_BMSK                                       0xffff
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_00_THRESHOLD_LEVEL_7_SHFT                                            0

#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_01_ADDR                                                     (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x1c)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_01_PHYS                                                     (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x1c)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_01_OFFS                                                     (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x1c)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_01_RMSK                                                     0xffffffff
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_01_ATTR                                                                  0x3
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_01_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_01_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_01_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_01_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_01_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_01_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_01_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_01_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_01_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_01_THRESHOLD_LEVEL_4_BMSK                                   0xffff0000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_01_THRESHOLD_LEVEL_4_SHFT                                           16
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_01_THRESHOLD_LEVEL_5_BMSK                                       0xffff
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_01_THRESHOLD_LEVEL_5_SHFT                                            0

#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_02_ADDR                                                     (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x20)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_02_PHYS                                                     (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x20)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_02_OFFS                                                     (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x20)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_02_RMSK                                                     0xffffffff
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_02_ATTR                                                                  0x3
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_02_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_02_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_02_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_02_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_02_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_02_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_02_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_02_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_02_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_02_THRESHOLD_LEVEL_2_BMSK                                   0xffff0000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_02_THRESHOLD_LEVEL_2_SHFT                                           16
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_02_THRESHOLD_LEVEL_3_BMSK                                       0xffff
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_02_THRESHOLD_LEVEL_3_SHFT                                            0

#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_03_ADDR                                                     (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x24)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_03_PHYS                                                     (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x24)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_03_OFFS                                                     (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x24)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_03_RMSK                                                     0xffffffff
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_03_ATTR                                                                  0x3
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_03_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_03_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_03_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_03_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_03_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_03_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_03_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_03_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_03_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_03_THRESHOLD_LEVEL_0_BMSK                                   0xffff0000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_03_THRESHOLD_LEVEL_0_SHFT                                           16
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_03_THRESHOLD_LEVEL_1_BMSK                                       0xffff
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_03_THRESHOLD_LEVEL_1_SHFT                                            0

#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_ADDR                                                (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x28)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_PHYS                                                (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x28)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_OFFS                                                (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x28)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_RMSK                                                   0xfffff
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_ATTR                                                             0x3
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_PEAK_ACCUM_CREDIT_BMSK                                 0xfffff
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_PEAK_ACCUM_CREDIT_SHFT                                       0

#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_CNTL_ADDR                                                       (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x30)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_CNTL_PHYS                                                       (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x30)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_CNTL_OFFS                                                       (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x30)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_CNTL_RMSK                                                            0xf01
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_CNTL_ATTR                                                                    0x3
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_CNTL_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_CNTL_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_CNTL_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_CNTL_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_CNTL_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_CNTL_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_CNTL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_CNTL_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_CNTL_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_CNTL_DEBUG_SEL_BMSK                                                  0xf00
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_CNTL_DEBUG_SEL_SHFT                                                      8
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_CNTL_DEBUG_EN_BMSK                                                     0x1
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_CNTL_DEBUG_EN_SHFT                                                       0

#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_READBACK_ADDR                                                   (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x34)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_READBACK_PHYS                                                   (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x34)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_READBACK_OFFS                                                   (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x34)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_READBACK_RMSK                                                   0xffffffff
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_READBACK_ATTR                                                                0x1
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_READBACK_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_READBACK_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_READBACK_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_READBACK_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_READBACK_DEBUG_BUS_READBACK_BMSK                                0xffffffff
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_READBACK_DEBUG_BUS_READBACK_SHFT                                         0

#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_ADDR                                               (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x38)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_PHYS                                               (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x38)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_OFFS                                               (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x38)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_RMSK                                                     0xff
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_ATTR                                                            0x3
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_THROTTLE_BWMON_CFG_ACCESS_CLKON_CNTR_BMSK                0xff
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_THROTTLE_BWMON_CFG_ACCESS_CLKON_CNTR_SHFT                   0

#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_ADDR                                                       (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x40)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_PHYS                                                       (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x40)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_OFFS                                                       (ECPRI_DMA1_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x40)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_RMSK                                                       0xffffffff
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_ATTR                                                                    0x3
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_31_BMSK                                      0x80000000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_31_SHFT                                              31
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_30_BMSK                                      0x40000000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_30_SHFT                                              30
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_29_BMSK                                      0x20000000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_29_SHFT                                              29
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_28_BMSK                                      0x10000000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_28_SHFT                                              28
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_27_BMSK                                       0x8000000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_27_SHFT                                              27
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_26_BMSK                                       0x4000000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_26_SHFT                                              26
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_25_BMSK                                       0x2000000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_25_SHFT                                              25
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_24_BMSK                                       0x1000000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_24_SHFT                                              24
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_23_BMSK                                        0x800000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_23_SHFT                                              23
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_22_BMSK                                        0x400000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_22_SHFT                                              22
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_21_BMSK                                        0x200000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_21_SHFT                                              21
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_20_BMSK                                        0x100000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_20_SHFT                                              20
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_19_BMSK                                         0x80000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_19_SHFT                                              19
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_18_BMSK                                         0x40000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_18_SHFT                                              18
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_17_BMSK                                         0x20000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_17_SHFT                                              17
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_16_BMSK                                         0x10000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_16_SHFT                                              16
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_15_BMSK                                          0x8000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_15_SHFT                                              15
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_14_BMSK                                          0x4000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_14_SHFT                                              14
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_13_BMSK                                          0x2000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_13_SHFT                                              13
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_12_BMSK                                          0x1000
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_12_SHFT                                              12
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_11_BMSK                                           0x800
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_11_SHFT                                              11
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_10_BMSK                                           0x400
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_10_SHFT                                              10
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_9_BMSK                                            0x200
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_9_SHFT                                                9
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_8_BMSK                                            0x100
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_8_SHFT                                                8
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_7_BMSK                                             0x80
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_7_SHFT                                                7
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_6_BMSK                                             0x40
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_6_SHFT                                                6
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_5_BMSK                                             0x20
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_5_SHFT                                                5
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_4_BMSK                                             0x10
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_4_SHFT                                                4
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_3_BMSK                                              0x8
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_3_SHFT                                                3
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_2_BMSK                                              0x4
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_2_SHFT                                                2
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_1_BMSK                                              0x2
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_1_SHFT                                                1
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_0_BMSK                                              0x1
#define HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_0_SHFT                                                0

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2
 *--------------------------------------------------------------------------*/

#define ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE                                                      (ECPRI_DMA1_THROTTLE_THROTTLE_BWMON_WRAPPER_1_BASE      + 0x00000200)
#define ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_SIZE                                                 0x600
#define ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_USED                                                 0x438
#define ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS                                                 (ECPRI_DMA1_THROTTLE_THROTTLE_BWMON_WRAPPER_1_BASE_PHYS + 0x00000200)
#define ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS                                                 0x00000200

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS_ADDR                                             (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x100)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS_PHYS                                             (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x100)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS_OFFS                                             (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x100)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS_RMSK                                                    0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS_ATTR                                                          0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS_GLOBAL_INTR_STATUS_BMSK                                 0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS_GLOBAL_INTR_STATUS_SHFT                                   0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR_ADDR                                              (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x108)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR_PHYS                                              (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x108)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR_OFFS                                              (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x108)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR_RMSK                                                     0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR_ATTR                                                           0x2
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR_GLOBAL_INTR_CLEAR_BMSK                                   0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR_GLOBAL_INTR_CLEAR_SHFT                                     0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_ADDR                                             (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x10c)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_PHYS                                             (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x10c)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_OFFS                                             (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x10c)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_RMSK                                                    0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_ATTR                                                          0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_GLOBAL_INTR_ENABLE_BMSK                                 0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_GLOBAL_INTR_ENABLE_SHFT                                   0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_STATUS_ADDR                                                    (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x200)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_STATUS_PHYS                                                    (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x200)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_STATUS_OFFS                                                    (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x200)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_STATUS_RMSK                                                          0xf3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_STATUS_ATTR                                                                 0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_STATUS_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_STATUS_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_STATUS_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_STATUS_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_STATUS_BWMON2_ZONE3_THRESHOLD_CROSSED_BMSK                           0x80
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_STATUS_BWMON2_ZONE3_THRESHOLD_CROSSED_SHFT                              7
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_STATUS_BWMON2_ZONE2_THRESHOLD_CROSSED_BMSK                           0x40
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_STATUS_BWMON2_ZONE2_THRESHOLD_CROSSED_SHFT                              6
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_STATUS_BWMON2_ZONE1_THRESHOLD_CROSSED_BMSK                           0x20
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_STATUS_BWMON2_ZONE1_THRESHOLD_CROSSED_SHFT                              5
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_STATUS_BWMON2_ZONE0_THRESHOLD_CROSSED_BMSK                           0x10
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_STATUS_BWMON2_ZONE0_THRESHOLD_CROSSED_SHFT                              4
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_STATUS_BWMON_OVERFLOW_BMSK                                            0x2
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_STATUS_BWMON_OVERFLOW_SHFT                                              1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_STATUS_BWMON_THRESHOLD_CROSSED_BMSK                                   0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_STATUS_BWMON_THRESHOLD_CROSSED_SHFT                                     0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_CLEAR_ADDR                                                     (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x208)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_CLEAR_PHYS                                                     (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x208)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_CLEAR_OFFS                                                     (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x208)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_CLEAR_RMSK                                                           0xf3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_CLEAR_ATTR                                                                  0x2
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_CLEAR_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_CLEAR_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_CLEAR_BWMON2_ZONE3_THRESHOLD_CROSSED_BMSK                            0x80
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_CLEAR_BWMON2_ZONE3_THRESHOLD_CROSSED_SHFT                               7
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_CLEAR_BWMON2_ZONE2_THRESHOLD_CROSSED_BMSK                            0x40
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_CLEAR_BWMON2_ZONE2_THRESHOLD_CROSSED_SHFT                               6
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_CLEAR_BWMON2_ZONE1_THRESHOLD_CROSSED_BMSK                            0x20
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_CLEAR_BWMON2_ZONE1_THRESHOLD_CROSSED_SHFT                               5
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_CLEAR_BWMON2_ZONE0_THRESHOLD_CROSSED_BMSK                            0x10
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_CLEAR_BWMON2_ZONE0_THRESHOLD_CROSSED_SHFT                               4
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_CLEAR_BWMON_OVERFLOW_BMSK                                             0x2
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_CLEAR_BWMON_OVERFLOW_SHFT                                               1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_CLEAR_BWMON_THRESHOLD_CROSSED_BMSK                                    0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_CLEAR_BWMON_THRESHOLD_CROSSED_SHFT                                      0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_ADDR                                                    (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x20c)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_PHYS                                                    (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x20c)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_OFFS                                                    (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x20c)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_RMSK                                                          0xf3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_ATTR                                                                 0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_BWMON2_ZONE3_THRESHOLD_CROSSED_BMSK                           0x80
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_BWMON2_ZONE3_THRESHOLD_CROSSED_SHFT                              7
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_BWMON2_ZONE2_THRESHOLD_CROSSED_BMSK                           0x40
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_BWMON2_ZONE2_THRESHOLD_CROSSED_SHFT                              6
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_BWMON2_ZONE1_THRESHOLD_CROSSED_BMSK                           0x20
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_BWMON2_ZONE1_THRESHOLD_CROSSED_SHFT                              5
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_BWMON2_ZONE0_THRESHOLD_CROSSED_BMSK                           0x10
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_BWMON2_ZONE0_THRESHOLD_CROSSED_SHFT                              4
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_BWMON_OVERFLOW_BMSK                                            0x2
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_BWMON_OVERFLOW_SHFT                                              1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_BWMON_THRESHOLD_CROSSED_BMSK                                   0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_BWMON_THRESHOLD_CROSSED_SHFT                                     0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_ADDR                                                (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x210)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_PHYS                                                (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x210)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_OFFS                                                (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x210)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_RMSK                                                    0x1fff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_ATTR                                                             0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_BWMON_CFG_ACCESS_CLKON_CNTR_BMSK                        0x1fe0
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_BWMON_CFG_ACCESS_CLKON_CNTR_SHFT                             5
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_BWMON2_CORE_CLKON_HYSTERESIS_BMSK                         0x1e
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_BWMON2_CORE_CLKON_HYSTERESIS_SHFT                            1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_BWMON2_CORE_CLKON_DISABLE_BMSK                             0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_BWMON2_CORE_CLKON_DISABLE_SHFT                               0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_SW_RESET_ADDR                                                      (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x308)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_SW_RESET_PHYS                                                      (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x308)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_SW_RESET_OFFS                                                      (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x308)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_SW_RESET_RMSK                                                             0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_SW_RESET_ATTR                                                                   0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_SW_RESET_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_SW_RESET_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_SW_RESET_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_SW_RESET_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_SW_RESET_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_SW_RESET_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_SW_RESET_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_SW_RESET_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_SW_RESET_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_SW_RESET_BWMON2_SW_RESET_BMSK                                             0x2
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_SW_RESET_BWMON2_SW_RESET_SHFT                                               1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_SW_RESET_BWMON_SW_RESET_BMSK                                              0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_SW_RESET_BWMON_SW_RESET_SHFT                                                0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CGC_CNTRL_ADDR                                                     (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x30c)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CGC_CNTRL_PHYS                                                     (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x30c)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CGC_CNTRL_OFFS                                                     (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x30c)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CGC_CNTRL_RMSK                                                            0x7
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CGC_CNTRL_ATTR                                                                  0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CGC_CNTRL_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CGC_CNTRL_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CGC_CNTRL_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CGC_CNTRL_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CGC_CNTRL_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CGC_CNTRL_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CGC_CNTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CGC_CNTRL_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CGC_CNTRL_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CGC_CNTRL_BWMON2_CLOCK_EN_CNTRL_BMSK                                      0x4
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CGC_CNTRL_BWMON2_CLOCK_EN_CNTRL_SHFT                                        2
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CGC_CNTRL_BWMON2_HW_CGC_MODE_BMSK                                         0x2
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CGC_CNTRL_BWMON2_HW_CGC_MODE_SHFT                                           1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CGC_CNTRL_BWMON_CLOCK_EN_CNTRL_BMSK                                       0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CGC_CNTRL_BWMON_CLOCK_EN_CNTRL_SHFT                                         0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_ADDR                                                        (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x380)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_PHYS                                                        (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x380)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_OFFS                                                        (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x380)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_RMSK                                                        0x83ff0111
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_ATTR                                                                     0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_CLEAR_ON_INTR_BMSK                                          0x80000000
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_CLEAR_ON_INTR_SHFT                                                  31
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_THROTTLE_OFFSET_BACK_PRESSURE_BMSK                           0x3e00000
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_THROTTLE_OFFSET_BACK_PRESSURE_SHFT                                  21
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_THROTTLE_OFFSET_BMSK                                          0x1f0000
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_THROTTLE_OFFSET_SHFT                                                16
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_MATCH_FILTER_BMSK                                                0x100
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_MATCH_FILTER_SHFT                                                    8
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_SCALING_FACTOR_BMSK                                               0x10
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_SCALING_FACTOR_SHFT                                                  4
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_ENABLE_BMSK                                                        0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_ENABLE_SHFT                                                          0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CLEAR_ADDR                                                         (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x384)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CLEAR_PHYS                                                         (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x384)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CLEAR_OFFS                                                         (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x384)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CLEAR_RMSK                                                                0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CLEAR_ATTR                                                                      0x2
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CLEAR_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CLEAR_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CLEAR_CLEAR_BMSK                                                          0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CLEAR_CLEAR_SHFT                                                            0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BYTE_COUNT_ADDR                                                    (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x388)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BYTE_COUNT_PHYS                                                    (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x388)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BYTE_COUNT_OFFS                                                    (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x388)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BYTE_COUNT_RMSK                                                    0xffffffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BYTE_COUNT_ATTR                                                                 0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BYTE_COUNT_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BYTE_COUNT_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BYTE_COUNT_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BYTE_COUNT_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BYTE_COUNT_BYTE_COUNT_BMSK                                         0xffffffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BYTE_COUNT_BYTE_COUNT_SHFT                                                  0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_THRESHOLD_ADDR                                                     (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x390)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_THRESHOLD_PHYS                                                     (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x390)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_THRESHOLD_OFFS                                                     (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x390)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_THRESHOLD_RMSK                                                     0xffffffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_THRESHOLD_ATTR                                                                  0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_THRESHOLD_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_THRESHOLD_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_THRESHOLD_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_THRESHOLD_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_THRESHOLD_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_THRESHOLD_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_THRESHOLD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_THRESHOLD_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_THRESHOLD_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_THRESHOLD_THRESHOLD_BMSK                                           0xffffffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_THRESHOLD_THRESHOLD_SHFT                                                    0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MASK_ADDR                                                      (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x398)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MASK_PHYS                                                      (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x398)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MASK_OFFS                                                      (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x398)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MASK_RMSK                                                          0xffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MASK_ATTR                                                                   0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MASK_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MASK_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MASK_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MASK_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MASK_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MASK_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MASK_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MASK_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MASK_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MASK_MASK_BMSK                                                     0xffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MASK_MASK_SHFT                                                          0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MATCH_ADDR                                                     (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x39c)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MATCH_PHYS                                                     (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x39c)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MATCH_OFFS                                                     (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x39c)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MATCH_RMSK                                                         0xffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MATCH_ATTR                                                                  0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MATCH_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MATCH_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MATCH_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MATCH_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MATCH_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MATCH_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MATCH_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MATCH_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MATCH_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MATCH_MATCH_BMSK                                                   0xffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MATCH_MATCH_SHFT                                                        0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ENABLE_ADDR                                                       (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x3a0)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ENABLE_PHYS                                                       (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x3a0)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ENABLE_OFFS                                                       (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x3a0)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ENABLE_RMSK                                                       0x801f0001
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ENABLE_ATTR                                                                    0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ENABLE_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ENABLE_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ENABLE_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ENABLE_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ENABLE_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ENABLE_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ENABLE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ENABLE_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ENABLE_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ENABLE_EARLY_INTR_EN_BMSK                                         0x80000000
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ENABLE_EARLY_INTR_EN_SHFT                                                 31
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ENABLE_THROTTLE_OFFSET_BMSK                                         0x1f0000
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ENABLE_THROTTLE_OFFSET_SHFT                                               16
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ENABLE_ENABLE_BMSK                                                       0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ENABLE_ENABLE_SHFT                                                         0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_CLEAR_ADDR                                                        (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x3a4)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_CLEAR_PHYS                                                        (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x3a4)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_CLEAR_OFFS                                                        (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x3a4)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_CLEAR_RMSK                                                               0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_CLEAR_ATTR                                                                     0x2
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_CLEAR_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_CLEAR_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_CLEAR_CLEAR_ALL_BMSK                                                     0x2
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_CLEAR_CLEAR_ALL_SHFT                                                       1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_CLEAR_CLEAR_BMSK                                                         0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_CLEAR_CLEAR_SHFT                                                           0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_ADDR                                              (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x3a8)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_PHYS                                              (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x3a8)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_OFFS                                              (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x3a8)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_RMSK                                                0xffffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_ATTR                                                           0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_REG_BMSK                                            0xffffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_REG_SHFT                                                   0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_ADDR                                    (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x3ac)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_PHYS                                    (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x3ac)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_OFFS                                    (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x3ac)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_RMSK                                        0xffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_ATTR                                                 0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_REG_BMSK                                    0xffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_REG_SHFT                                         0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_ADDR                                  (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x3b0)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_PHYS                                  (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x3b0)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_OFFS                                  (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x3b0)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_RMSK                                      0xffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_ATTR                                               0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_REG_BMSK                                  0xffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_REG_SHFT                                       0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_ADDR                                     (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x3b4)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_PHYS                                     (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x3b4)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_OFFS                                     (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x3b4)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_RMSK                                         0xffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_ATTR                                                  0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_REG_BMSK                                     0xffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_REG_SHFT                                          0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ADDR                                                 (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x3b8)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_PHYS                                                 (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x3b8)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_OFFS                                                 (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x3b8)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_RMSK                                                 0xffffffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ATTR                                                              0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ZONE3_BMSK                                           0xff000000
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ZONE3_SHFT                                                   24
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ZONE2_BMSK                                             0xff0000
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ZONE2_SHFT                                                   16
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ZONE1_BMSK                                               0xff00
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ZONE1_SHFT                                                    8
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ZONE0_BMSK                                                 0xff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ZONE0_SHFT                                                    0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ADDR                                         (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x3bc)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_PHYS                                         (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x3bc)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_OFFS                                         (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x3bc)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_RMSK                                         0xffffffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ATTR                                                      0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ZONE3_BMSK                                   0xff000000
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ZONE3_SHFT                                           24
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ZONE2_BMSK                                     0xff0000
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ZONE2_SHFT                                           16
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ZONE1_BMSK                                       0xff00
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ZONE1_SHFT                                            8
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ZONE0_BMSK                                         0xff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ZONE0_SHFT                                            0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_ADDR                                                   (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x3d0)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_PHYS                                                   (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x3d0)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_OFFS                                                   (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x3d0)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_RMSK                                                   0x3000ffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_ATTR                                                                0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_CURRENT_ZONE_BMSK                                      0x30000000
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_CURRENT_ZONE_SHFT                                              28
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_CURRENT_BYTE_COUNT_BMSK                                    0xffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_CURRENT_BYTE_COUNT_SHFT                                         0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_WINDOW_TIMER_ADDR                                                 (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x3d4)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_WINDOW_TIMER_PHYS                                                 (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x3d4)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_WINDOW_TIMER_OFFS                                                 (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x3d4)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_WINDOW_TIMER_RMSK                                                   0xffffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_WINDOW_TIMER_ATTR                                                              0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_WINDOW_TIMER_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_WINDOW_TIMER_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_WINDOW_TIMER_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_WINDOW_TIMER_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_WINDOW_TIMER_CURRENT_WINDOW_TIMER_BMSK                              0xffffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_WINDOW_TIMER_CURRENT_WINDOW_TIMER_SHFT                                     0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_ADDR                                                   (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x3d8)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_PHYS                                                   (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x3d8)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_OFFS                                                   (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x3d8)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_RMSK                                                   0xffffffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_ATTR                                                                0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_ZONE3_BMSK                                             0xff000000
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_ZONE3_SHFT                                                     24
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_ZONE2_BMSK                                               0xff0000
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_ZONE2_SHFT                                                     16
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_ZONE1_BMSK                                                 0xff00
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_ZONE1_SHFT                                                      8
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_ZONE0_BMSK                                                   0xff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_ZONE0_SHFT                                                      0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_ADDR(n)                                      (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0X3E0 + (0x4*(n)))
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_PHYS(n)                                      (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0X3E0 + (0x4*(n)))
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_OFFS(n)                                      (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0X3E0 + (0x4*(n)))
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_RMSK                                             0xffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_MAXn                                                  3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_ATTR                                                      0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_INI(n)                \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_ADDR(n), HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_RMSK)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_INMI(n,mask)        \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_ADDR(n), mask)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_REG_BMSK                                         0xffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_REG_SHFT                                              0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MASK_ADDR                                                      (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x400)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MASK_PHYS                                                      (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x400)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MASK_OFFS                                                      (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x400)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MASK_RMSK                                                            0x1f
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MASK_ATTR                                                                   0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MASK_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MASK_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MASK_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MASK_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MASK_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MASK_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MASK_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MASK_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MASK_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MASK_MASK_BMSK                                                       0x1f
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MASK_MASK_SHFT                                                          0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MATCH_ADDR                                                     (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x404)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MATCH_PHYS                                                     (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x404)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MATCH_OFFS                                                     (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x404)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MATCH_RMSK                                                           0x1f
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MATCH_ATTR                                                                  0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MATCH_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MATCH_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MATCH_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MATCH_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MATCH_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MATCH_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MATCH_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MATCH_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MATCH_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MATCH_MATCH_BMSK                                                     0x1f
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MATCH_MATCH_SHFT                                                        0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MASK_ADDR                                                      (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x408)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MASK_PHYS                                                      (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x408)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MASK_OFFS                                                      (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x408)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MASK_RMSK                                                             0x7
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MASK_ATTR                                                                   0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MASK_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MASK_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MASK_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MASK_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MASK_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MASK_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MASK_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MASK_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MASK_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MASK_MASK_BMSK                                                        0x7
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MASK_MASK_SHFT                                                          0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MATCH_ADDR                                                     (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x40c)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MATCH_PHYS                                                     (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x40c)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MATCH_OFFS                                                     (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x40c)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MATCH_RMSK                                                            0x7
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MATCH_ATTR                                                                  0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MATCH_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MATCH_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MATCH_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MATCH_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MATCH_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MATCH_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MATCH_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MATCH_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MATCH_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MATCH_MATCH_BMSK                                                      0x7
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MATCH_MATCH_SHFT                                                        0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_ADDR                                      (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x410)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_PHYS                                      (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x410)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_OFFS                                      (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x410)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_RMSK                                             0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_ATTR                                                   0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_BWMON_STATS_CNTR_SATURATED_BMSK                  0x2
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_BWMON_STATS_CNTR_SATURATED_SHFT                    1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_BWMON_REJECT_PERIOD_EXPIRED_BMSK                 0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_BWMON_REJECT_PERIOD_EXPIRED_SHFT                   0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR_ADDR                                       (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x414)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR_PHYS                                       (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x414)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR_OFFS                                       (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x414)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR_RMSK                                              0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR_ATTR                                                    0x2
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR_BWMON_STATS_CNTR_SATURATED_BMSK                   0x2
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR_BWMON_STATS_CNTR_SATURATED_SHFT                     1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR_BWMON_REJECT_PERIOD_EXPIRED_BMSK                  0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR_BWMON_REJECT_PERIOD_EXPIRED_SHFT                    0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_ADDR                                      (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x418)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_PHYS                                      (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x418)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_OFFS                                      (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x418)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_RMSK                                             0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_ATTR                                                   0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_BWMON_STATS_CNTR_SATURATED_BMSK                  0x2
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_BWMON_STATS_CNTR_SATURATED_SHFT                    1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_BWMON_REJECT_PERIOD_EXPIRED_BMSK                 0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_BWMON_REJECT_PERIOD_EXPIRED_SHFT                   0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_ADDR                                        (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x41c)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_PHYS                                        (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x41c)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_OFFS                                        (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x41c)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_RMSK                                               0x7
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_ATTR                                                     0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_CAPTURE_BMSK                                       0x4
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_CAPTURE_SHFT                                         2
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_ALEN_EN_BMSK                                       0x2
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_ALEN_EN_SHFT                                         1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_COUNTERS_EN_BMSK                                   0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_COUNTERS_EN_SHFT                                     0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_PERIOD_ADDR                                                 (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x420)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_PERIOD_PHYS                                                 (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x420)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_PERIOD_OFFS                                                 (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x420)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_PERIOD_RMSK                                                     0x3fff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_PERIOD_ATTR                                                              0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_PERIOD_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_PERIOD_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_PERIOD_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_PERIOD_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_PERIOD_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_PERIOD_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_PERIOD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_PERIOD_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_PERIOD_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_PERIOD_PERIOD_BMSK                                              0x3fff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_PERIOD_PERIOD_SHFT                                                   0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ACCEPT_COUNT_ADDR                                                  (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x424)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ACCEPT_COUNT_PHYS                                                  (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x424)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ACCEPT_COUNT_OFFS                                                  (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x424)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ACCEPT_COUNT_RMSK                                                  0xffffffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ACCEPT_COUNT_ATTR                                                               0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ACCEPT_COUNT_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ACCEPT_COUNT_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ACCEPT_COUNT_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ACCEPT_COUNT_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ACCEPT_COUNT_ACCEPT_COUNT_BMSK                                     0xffffffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ACCEPT_COUNT_ACCEPT_COUNT_SHFT                                              0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNT_ADDR                                                  (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x428)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNT_PHYS                                                  (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x428)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNT_OFFS                                                  (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x428)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNT_RMSK                                                  0xffffffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNT_ATTR                                                               0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNT_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNT_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNT_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNT_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNT_REJECT_COUNT_BMSK                                     0xffffffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNT_REJECT_COUNT_SHFT                                              0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_IDLE_COUNT_ADDR                                                    (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x42c)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_IDLE_COUNT_PHYS                                                    (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x42c)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_IDLE_COUNT_OFFS                                                    (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x42c)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_IDLE_COUNT_RMSK                                                    0xffffffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_IDLE_COUNT_ATTR                                                                 0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_IDLE_COUNT_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_IDLE_COUNT_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_IDLE_COUNT_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_IDLE_COUNT_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_IDLE_COUNT_IDLE_COUNT_BMSK                                         0xffffffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_IDLE_COUNT_IDLE_COUNT_SHFT                                                  0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_INTR_TARGET_ADDR                                                   (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x430)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_INTR_TARGET_PHYS                                                   (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x430)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_INTR_TARGET_OFFS                                                   (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x430)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_INTR_TARGET_RMSK                                                          0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_INTR_TARGET_ATTR                                                                0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_INTR_TARGET_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_INTR_TARGET_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_INTR_TARGET_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_INTR_TARGET_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_INTR_TARGET_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_INTR_TARGET_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_INTR_TARGET_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_INTR_TARGET_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_INTR_TARGET_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_INTR_TARGET_SECONDARY_TARGET_SELECT_BMSK                                  0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_INTR_TARGET_SECONDARY_TARGET_SELECT_SHFT                                    0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_CNTL_ADDR                                                    (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x434)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_CNTL_PHYS                                                    (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x434)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_CNTL_OFFS                                                    (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x434)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_CNTL_RMSK                                                         0xf01
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_CNTL_ATTR                                                                 0x3
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_CNTL_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_CNTL_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_CNTL_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_CNTL_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_CNTL_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_CNTL_ADDR,v)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_CNTL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_CNTL_ADDR,m,v,HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_CNTL_IN)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_CNTL_DEBUG_SEL_BMSK                                               0xf00
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_CNTL_DEBUG_SEL_SHFT                                                   8
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_CNTL_DEBUG_EN_BMSK                                                  0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_CNTL_DEBUG_EN_SHFT                                                    0

#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_READBACK_ADDR                                                (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x438)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_READBACK_PHYS                                                (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x438)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_READBACK_OFFS                                                (ECPRI_DMA1_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x438)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_READBACK_RMSK                                                0xffffffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_READBACK_ATTR                                                             0x1
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_READBACK_IN                    \
                in_dword(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_READBACK_ADDR)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_READBACK_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_READBACK_ADDR, m)
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_READBACK_DEBUG_BUS_READBACK_BMSK                             0xffffffff
#define HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_READBACK_DEBUG_BUS_READBACK_SHFT                                      0

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE
 *--------------------------------------------------------------------------*/

#define ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE                                               (ECPRI_DMA0_THROTTLE_THROTTLE_BWMON_WRAPPER_1_BASE      + 0x00000000)
#define ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_SIZE                                          0x100
#define ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_USED                                          0x40
#define ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS                                          (ECPRI_DMA0_THROTTLE_THROTTLE_BWMON_WRAPPER_1_BASE_PHYS + 0x00000000)
#define ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS                                          0x00000000

#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_ADDR                                                            (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x0)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_PHYS                                                            (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x0)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_OFFS                                                            (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x0)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_RMSK                                                                0xff01
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_ATTR                                                                         0x3
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_7_EN_BMSK                                           0x8000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_7_EN_SHFT                                               15
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_6_EN_BMSK                                           0x4000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_6_EN_SHFT                                               14
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_5_EN_BMSK                                           0x2000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_5_EN_SHFT                                               13
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_4_EN_BMSK                                           0x1000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_4_EN_SHFT                                               12
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_3_EN_BMSK                                            0x800
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_3_EN_SHFT                                               11
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_2_EN_BMSK                                            0x400
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_2_EN_SHFT                                               10
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_1_EN_BMSK                                            0x200
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_1_EN_SHFT                                                9
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_0_EN_BMSK                                            0x100
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_THRESHOLD_LEVEL_0_EN_SHFT                                                8
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_THROTTLE_EN_BMSK                                                       0x1
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_THROTTLE_EN_SHFT                                                         0

#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CGC_CNTRL_ADDR                                                        (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x4)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CGC_CNTRL_PHYS                                                        (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x4)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CGC_CNTRL_OFFS                                                        (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x4)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CGC_CNTRL_RMSK                                                               0x1
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CGC_CNTRL_ATTR                                                                     0x3
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CGC_CNTRL_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CGC_CNTRL_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CGC_CNTRL_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CGC_CNTRL_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CGC_CNTRL_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CGC_CNTRL_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CGC_CNTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CGC_CNTRL_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CGC_CNTRL_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CGC_CNTRL_THROTTLE_CGC_EN_BMSK                                               0x1
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CGC_CNTRL_THROTTLE_CGC_EN_SHFT                                                 0

#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_RESET_CNTRL_ADDR                                                      (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x8)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_RESET_CNTRL_PHYS                                                      (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x8)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_RESET_CNTRL_OFFS                                                      (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x8)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_RESET_CNTRL_RMSK                                                             0x1
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_RESET_CNTRL_ATTR                                                                   0x3
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_RESET_CNTRL_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_RESET_CNTRL_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_RESET_CNTRL_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_RESET_CNTRL_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_RESET_CNTRL_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_RESET_CNTRL_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_RESET_CNTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_RESET_CNTRL_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_RESET_CNTRL_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_RESET_CNTRL_CORE_SW_RESET_BMSK                                               0x1
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_RESET_CNTRL_CORE_SW_RESET_SHFT                                                 0

#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_ADDR                                                           (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0xc)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_PHYS                                                           (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0xc)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_OFFS                                                           (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0xc)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_RMSK                                                                  0x7
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_ATTR                                                                        0x3
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_THROTTLE_CNTRL_MAX_SKEW_BMSK                                          0x7
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_THROTTLE_CNTRL_MAX_SKEW_SHFT                                            0

#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_PERIOD_ADDR                                                     (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x10)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_PERIOD_PHYS                                                     (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x10)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_PERIOD_OFFS                                                     (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x10)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_PERIOD_RMSK                                                         0x3fff
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_PERIOD_ATTR                                                                  0x3
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_PERIOD_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_PERIOD_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_PERIOD_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_PERIOD_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_PERIOD_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_PERIOD_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_PERIOD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_PERIOD_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_PERIOD_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_PERIOD_GRANT_PERIOD_BMSK                                            0x3fff
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_PERIOD_GRANT_PERIOD_SHFT                                                 0

#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_COUNT_ADDR                                                      (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x14)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_COUNT_PHYS                                                      (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x14)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_COUNT_OFFS                                                      (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x14)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_COUNT_RMSK                                                          0xffff
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_COUNT_ATTR                                                                   0x3
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_COUNT_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_COUNT_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_COUNT_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_COUNT_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_COUNT_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_COUNT_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_COUNT_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_COUNT_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_COUNT_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_COUNT_GRANT_COUNT_BMSK                                              0xffff
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_COUNT_GRANT_COUNT_SHFT                                                   0

#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_00_ADDR                                                     (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x18)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_00_PHYS                                                     (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x18)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_00_OFFS                                                     (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x18)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_00_RMSK                                                     0xffffffff
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_00_ATTR                                                                  0x3
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_00_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_00_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_00_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_00_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_00_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_00_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_00_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_00_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_00_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_00_THRESHOLD_LEVEL_6_BMSK                                   0xffff0000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_00_THRESHOLD_LEVEL_6_SHFT                                           16
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_00_THRESHOLD_LEVEL_7_BMSK                                       0xffff
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_00_THRESHOLD_LEVEL_7_SHFT                                            0

#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_01_ADDR                                                     (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x1c)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_01_PHYS                                                     (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x1c)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_01_OFFS                                                     (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x1c)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_01_RMSK                                                     0xffffffff
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_01_ATTR                                                                  0x3
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_01_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_01_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_01_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_01_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_01_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_01_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_01_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_01_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_01_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_01_THRESHOLD_LEVEL_4_BMSK                                   0xffff0000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_01_THRESHOLD_LEVEL_4_SHFT                                           16
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_01_THRESHOLD_LEVEL_5_BMSK                                       0xffff
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_01_THRESHOLD_LEVEL_5_SHFT                                            0

#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_02_ADDR                                                     (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x20)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_02_PHYS                                                     (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x20)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_02_OFFS                                                     (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x20)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_02_RMSK                                                     0xffffffff
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_02_ATTR                                                                  0x3
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_02_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_02_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_02_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_02_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_02_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_02_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_02_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_02_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_02_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_02_THRESHOLD_LEVEL_2_BMSK                                   0xffff0000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_02_THRESHOLD_LEVEL_2_SHFT                                           16
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_02_THRESHOLD_LEVEL_3_BMSK                                       0xffff
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_02_THRESHOLD_LEVEL_3_SHFT                                            0

#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_03_ADDR                                                     (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x24)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_03_PHYS                                                     (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x24)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_03_OFFS                                                     (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x24)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_03_RMSK                                                     0xffffffff
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_03_ATTR                                                                  0x3
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_03_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_03_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_03_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_03_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_03_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_03_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_03_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_03_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_03_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_03_THRESHOLD_LEVEL_0_BMSK                                   0xffff0000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_03_THRESHOLD_LEVEL_0_SHFT                                           16
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_03_THRESHOLD_LEVEL_1_BMSK                                       0xffff
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_03_THRESHOLD_LEVEL_1_SHFT                                            0

#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_ADDR                                                (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x28)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_PHYS                                                (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x28)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_OFFS                                                (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x28)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_RMSK                                                   0xfffff
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_ATTR                                                             0x3
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_PEAK_ACCUM_CREDIT_BMSK                                 0xfffff
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_PEAK_ACCUM_CREDIT_SHFT                                       0

#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_CNTL_ADDR                                                       (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x30)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_CNTL_PHYS                                                       (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x30)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_CNTL_OFFS                                                       (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x30)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_CNTL_RMSK                                                            0xf01
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_CNTL_ATTR                                                                    0x3
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_CNTL_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_CNTL_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_CNTL_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_CNTL_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_CNTL_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_CNTL_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_CNTL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_CNTL_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_CNTL_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_CNTL_DEBUG_SEL_BMSK                                                  0xf00
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_CNTL_DEBUG_SEL_SHFT                                                      8
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_CNTL_DEBUG_EN_BMSK                                                     0x1
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_CNTL_DEBUG_EN_SHFT                                                       0

#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_READBACK_ADDR                                                   (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x34)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_READBACK_PHYS                                                   (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x34)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_READBACK_OFFS                                                   (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x34)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_READBACK_RMSK                                                   0xffffffff
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_READBACK_ATTR                                                                0x1
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_READBACK_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_READBACK_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_READBACK_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_READBACK_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_READBACK_DEBUG_BUS_READBACK_BMSK                                0xffffffff
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_READBACK_DEBUG_BUS_READBACK_SHFT                                         0

#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_ADDR                                               (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x38)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_PHYS                                               (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x38)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_OFFS                                               (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x38)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_RMSK                                                     0xff
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_ATTR                                                            0x3
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_THROTTLE_BWMON_CFG_ACCESS_CLKON_CNTR_BMSK                0xff
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_THROTTLE_BWMON_CFG_ACCESS_CLKON_CNTR_SHFT                   0

#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_ADDR                                                       (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE      + 0x40)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_PHYS                                                       (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_PHYS + 0x40)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_OFFS                                                       (ECPRI_DMA0_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE_REG_BASE_OFFS + 0x40)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_RMSK                                                       0xffffffff
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_ATTR                                                                    0x3
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_31_BMSK                                      0x80000000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_31_SHFT                                              31
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_30_BMSK                                      0x40000000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_30_SHFT                                              30
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_29_BMSK                                      0x20000000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_29_SHFT                                              29
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_28_BMSK                                      0x10000000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_28_SHFT                                              28
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_27_BMSK                                       0x8000000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_27_SHFT                                              27
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_26_BMSK                                       0x4000000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_26_SHFT                                              26
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_25_BMSK                                       0x2000000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_25_SHFT                                              25
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_24_BMSK                                       0x1000000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_24_SHFT                                              24
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_23_BMSK                                        0x800000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_23_SHFT                                              23
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_22_BMSK                                        0x400000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_22_SHFT                                              22
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_21_BMSK                                        0x200000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_21_SHFT                                              21
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_20_BMSK                                        0x100000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_20_SHFT                                              20
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_19_BMSK                                         0x80000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_19_SHFT                                              19
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_18_BMSK                                         0x40000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_18_SHFT                                              18
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_17_BMSK                                         0x20000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_17_SHFT                                              17
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_16_BMSK                                         0x10000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_16_SHFT                                              16
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_15_BMSK                                          0x8000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_15_SHFT                                              15
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_14_BMSK                                          0x4000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_14_SHFT                                              14
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_13_BMSK                                          0x2000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_13_SHFT                                              13
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_12_BMSK                                          0x1000
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_12_SHFT                                              12
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_11_BMSK                                           0x800
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_11_SHFT                                              11
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_10_BMSK                                           0x400
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_10_SHFT                                              10
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_9_BMSK                                            0x200
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_9_SHFT                                                9
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_8_BMSK                                            0x100
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_8_SHFT                                                8
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_7_BMSK                                             0x80
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_7_SHFT                                                7
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_6_BMSK                                             0x40
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_6_SHFT                                                6
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_5_BMSK                                             0x20
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_5_SHFT                                                5
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_4_BMSK                                             0x10
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_4_SHFT                                                4
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_3_BMSK                                              0x8
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_3_SHFT                                                3
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_2_BMSK                                              0x4
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_2_SHFT                                                2
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_1_BMSK                                              0x2
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_1_SHFT                                                1
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_0_BMSK                                              0x1
#define HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_SPARE_REG_BIT_0_SHFT                                                0

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2
 *--------------------------------------------------------------------------*/

#define ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE                                                      (ECPRI_DMA0_THROTTLE_THROTTLE_BWMON_WRAPPER_1_BASE      + 0x00000200)
#define ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_SIZE                                                 0x600
#define ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_USED                                                 0x438
#define ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS                                                 (ECPRI_DMA0_THROTTLE_THROTTLE_BWMON_WRAPPER_1_BASE_PHYS + 0x00000200)
#define ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS                                                 0x00000200

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS_ADDR                                             (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x100)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS_PHYS                                             (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x100)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS_OFFS                                             (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x100)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS_RMSK                                                    0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS_ATTR                                                          0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS_GLOBAL_INTR_STATUS_BMSK                                 0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS_GLOBAL_INTR_STATUS_SHFT                                   0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR_ADDR                                              (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x108)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR_PHYS                                              (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x108)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR_OFFS                                              (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x108)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR_RMSK                                                     0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR_ATTR                                                           0x2
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR_GLOBAL_INTR_CLEAR_BMSK                                   0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR_GLOBAL_INTR_CLEAR_SHFT                                     0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_ADDR                                             (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x10c)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_PHYS                                             (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x10c)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_OFFS                                             (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x10c)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_RMSK                                                    0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_ATTR                                                          0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_GLOBAL_INTR_ENABLE_BMSK                                 0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_GLOBAL_INTR_ENABLE_SHFT                                   0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_STATUS_ADDR                                                    (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x200)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_STATUS_PHYS                                                    (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x200)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_STATUS_OFFS                                                    (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x200)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_STATUS_RMSK                                                          0xf3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_STATUS_ATTR                                                                 0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_STATUS_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_STATUS_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_STATUS_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_STATUS_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_STATUS_BWMON2_ZONE3_THRESHOLD_CROSSED_BMSK                           0x80
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_STATUS_BWMON2_ZONE3_THRESHOLD_CROSSED_SHFT                              7
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_STATUS_BWMON2_ZONE2_THRESHOLD_CROSSED_BMSK                           0x40
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_STATUS_BWMON2_ZONE2_THRESHOLD_CROSSED_SHFT                              6
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_STATUS_BWMON2_ZONE1_THRESHOLD_CROSSED_BMSK                           0x20
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_STATUS_BWMON2_ZONE1_THRESHOLD_CROSSED_SHFT                              5
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_STATUS_BWMON2_ZONE0_THRESHOLD_CROSSED_BMSK                           0x10
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_STATUS_BWMON2_ZONE0_THRESHOLD_CROSSED_SHFT                              4
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_STATUS_BWMON_OVERFLOW_BMSK                                            0x2
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_STATUS_BWMON_OVERFLOW_SHFT                                              1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_STATUS_BWMON_THRESHOLD_CROSSED_BMSK                                   0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_STATUS_BWMON_THRESHOLD_CROSSED_SHFT                                     0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_CLEAR_ADDR                                                     (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x208)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_CLEAR_PHYS                                                     (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x208)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_CLEAR_OFFS                                                     (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x208)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_CLEAR_RMSK                                                           0xf3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_CLEAR_ATTR                                                                  0x2
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_CLEAR_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_CLEAR_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_CLEAR_BWMON2_ZONE3_THRESHOLD_CROSSED_BMSK                            0x80
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_CLEAR_BWMON2_ZONE3_THRESHOLD_CROSSED_SHFT                               7
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_CLEAR_BWMON2_ZONE2_THRESHOLD_CROSSED_BMSK                            0x40
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_CLEAR_BWMON2_ZONE2_THRESHOLD_CROSSED_SHFT                               6
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_CLEAR_BWMON2_ZONE1_THRESHOLD_CROSSED_BMSK                            0x20
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_CLEAR_BWMON2_ZONE1_THRESHOLD_CROSSED_SHFT                               5
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_CLEAR_BWMON2_ZONE0_THRESHOLD_CROSSED_BMSK                            0x10
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_CLEAR_BWMON2_ZONE0_THRESHOLD_CROSSED_SHFT                               4
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_CLEAR_BWMON_OVERFLOW_BMSK                                             0x2
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_CLEAR_BWMON_OVERFLOW_SHFT                                               1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_CLEAR_BWMON_THRESHOLD_CROSSED_BMSK                                    0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_CLEAR_BWMON_THRESHOLD_CROSSED_SHFT                                      0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_ADDR                                                    (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x20c)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_PHYS                                                    (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x20c)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_OFFS                                                    (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x20c)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_RMSK                                                          0xf3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_ATTR                                                                 0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_BWMON2_ZONE3_THRESHOLD_CROSSED_BMSK                           0x80
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_BWMON2_ZONE3_THRESHOLD_CROSSED_SHFT                              7
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_BWMON2_ZONE2_THRESHOLD_CROSSED_BMSK                           0x40
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_BWMON2_ZONE2_THRESHOLD_CROSSED_SHFT                              6
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_BWMON2_ZONE1_THRESHOLD_CROSSED_BMSK                           0x20
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_BWMON2_ZONE1_THRESHOLD_CROSSED_SHFT                              5
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_BWMON2_ZONE0_THRESHOLD_CROSSED_BMSK                           0x10
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_BWMON2_ZONE0_THRESHOLD_CROSSED_SHFT                              4
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_BWMON_OVERFLOW_BMSK                                            0x2
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_BWMON_OVERFLOW_SHFT                                              1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_BWMON_THRESHOLD_CROSSED_BMSK                                   0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_BWMON_THRESHOLD_CROSSED_SHFT                                     0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_ADDR                                                (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x210)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_PHYS                                                (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x210)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_OFFS                                                (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x210)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_RMSK                                                    0x1fff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_ATTR                                                             0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_BWMON_CFG_ACCESS_CLKON_CNTR_BMSK                        0x1fe0
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_BWMON_CFG_ACCESS_CLKON_CNTR_SHFT                             5
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_BWMON2_CORE_CLKON_HYSTERESIS_BMSK                         0x1e
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_BWMON2_CORE_CLKON_HYSTERESIS_SHFT                            1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_BWMON2_CORE_CLKON_DISABLE_BMSK                             0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_BWMON2_CORE_CLKON_DISABLE_SHFT                               0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_SW_RESET_ADDR                                                      (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x308)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_SW_RESET_PHYS                                                      (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x308)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_SW_RESET_OFFS                                                      (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x308)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_SW_RESET_RMSK                                                             0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_SW_RESET_ATTR                                                                   0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_SW_RESET_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_SW_RESET_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_SW_RESET_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_SW_RESET_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_SW_RESET_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_SW_RESET_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_SW_RESET_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_SW_RESET_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_SW_RESET_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_SW_RESET_BWMON2_SW_RESET_BMSK                                             0x2
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_SW_RESET_BWMON2_SW_RESET_SHFT                                               1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_SW_RESET_BWMON_SW_RESET_BMSK                                              0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_SW_RESET_BWMON_SW_RESET_SHFT                                                0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CGC_CNTRL_ADDR                                                     (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x30c)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CGC_CNTRL_PHYS                                                     (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x30c)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CGC_CNTRL_OFFS                                                     (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x30c)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CGC_CNTRL_RMSK                                                            0x7
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CGC_CNTRL_ATTR                                                                  0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CGC_CNTRL_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CGC_CNTRL_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CGC_CNTRL_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CGC_CNTRL_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CGC_CNTRL_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CGC_CNTRL_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CGC_CNTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CGC_CNTRL_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CGC_CNTRL_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CGC_CNTRL_BWMON2_CLOCK_EN_CNTRL_BMSK                                      0x4
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CGC_CNTRL_BWMON2_CLOCK_EN_CNTRL_SHFT                                        2
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CGC_CNTRL_BWMON2_HW_CGC_MODE_BMSK                                         0x2
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CGC_CNTRL_BWMON2_HW_CGC_MODE_SHFT                                           1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CGC_CNTRL_BWMON_CLOCK_EN_CNTRL_BMSK                                       0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CGC_CNTRL_BWMON_CLOCK_EN_CNTRL_SHFT                                         0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_ADDR                                                        (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x380)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_PHYS                                                        (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x380)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_OFFS                                                        (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x380)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_RMSK                                                        0x83ff0111
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_ATTR                                                                     0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_CLEAR_ON_INTR_BMSK                                          0x80000000
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_CLEAR_ON_INTR_SHFT                                                  31
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_THROTTLE_OFFSET_BACK_PRESSURE_BMSK                           0x3e00000
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_THROTTLE_OFFSET_BACK_PRESSURE_SHFT                                  21
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_THROTTLE_OFFSET_BMSK                                          0x1f0000
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_THROTTLE_OFFSET_SHFT                                                16
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_MATCH_FILTER_BMSK                                                0x100
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_MATCH_FILTER_SHFT                                                    8
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_SCALING_FACTOR_BMSK                                               0x10
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_SCALING_FACTOR_SHFT                                                  4
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_ENABLE_BMSK                                                        0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_ENABLE_SHFT                                                          0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CLEAR_ADDR                                                         (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x384)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CLEAR_PHYS                                                         (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x384)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CLEAR_OFFS                                                         (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x384)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CLEAR_RMSK                                                                0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CLEAR_ATTR                                                                      0x2
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CLEAR_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CLEAR_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CLEAR_CLEAR_BMSK                                                          0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CLEAR_CLEAR_SHFT                                                            0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BYTE_COUNT_ADDR                                                    (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x388)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BYTE_COUNT_PHYS                                                    (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x388)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BYTE_COUNT_OFFS                                                    (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x388)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BYTE_COUNT_RMSK                                                    0xffffffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BYTE_COUNT_ATTR                                                                 0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BYTE_COUNT_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BYTE_COUNT_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BYTE_COUNT_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BYTE_COUNT_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BYTE_COUNT_BYTE_COUNT_BMSK                                         0xffffffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BYTE_COUNT_BYTE_COUNT_SHFT                                                  0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_THRESHOLD_ADDR                                                     (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x390)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_THRESHOLD_PHYS                                                     (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x390)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_THRESHOLD_OFFS                                                     (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x390)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_THRESHOLD_RMSK                                                     0xffffffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_THRESHOLD_ATTR                                                                  0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_THRESHOLD_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_THRESHOLD_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_THRESHOLD_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_THRESHOLD_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_THRESHOLD_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_THRESHOLD_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_THRESHOLD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_THRESHOLD_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_THRESHOLD_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_THRESHOLD_THRESHOLD_BMSK                                           0xffffffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_THRESHOLD_THRESHOLD_SHFT                                                    0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MASK_ADDR                                                      (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x398)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MASK_PHYS                                                      (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x398)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MASK_OFFS                                                      (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x398)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MASK_RMSK                                                          0xffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MASK_ATTR                                                                   0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MASK_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MASK_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MASK_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MASK_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MASK_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MASK_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MASK_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MASK_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MASK_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MASK_MASK_BMSK                                                     0xffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MASK_MASK_SHFT                                                          0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MATCH_ADDR                                                     (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x39c)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MATCH_PHYS                                                     (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x39c)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MATCH_OFFS                                                     (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x39c)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MATCH_RMSK                                                         0xffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MATCH_ATTR                                                                  0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MATCH_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MATCH_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MATCH_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MATCH_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MATCH_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MATCH_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MATCH_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MATCH_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MATCH_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MATCH_MATCH_BMSK                                                   0xffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MATCH_MATCH_SHFT                                                        0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ENABLE_ADDR                                                       (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x3a0)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ENABLE_PHYS                                                       (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x3a0)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ENABLE_OFFS                                                       (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x3a0)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ENABLE_RMSK                                                       0x801f0001
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ENABLE_ATTR                                                                    0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ENABLE_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ENABLE_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ENABLE_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ENABLE_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ENABLE_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ENABLE_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ENABLE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ENABLE_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ENABLE_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ENABLE_EARLY_INTR_EN_BMSK                                         0x80000000
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ENABLE_EARLY_INTR_EN_SHFT                                                 31
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ENABLE_THROTTLE_OFFSET_BMSK                                         0x1f0000
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ENABLE_THROTTLE_OFFSET_SHFT                                               16
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ENABLE_ENABLE_BMSK                                                       0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ENABLE_ENABLE_SHFT                                                         0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_CLEAR_ADDR                                                        (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x3a4)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_CLEAR_PHYS                                                        (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x3a4)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_CLEAR_OFFS                                                        (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x3a4)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_CLEAR_RMSK                                                               0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_CLEAR_ATTR                                                                     0x2
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_CLEAR_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_CLEAR_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_CLEAR_CLEAR_ALL_BMSK                                                     0x2
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_CLEAR_CLEAR_ALL_SHFT                                                       1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_CLEAR_CLEAR_BMSK                                                         0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_CLEAR_CLEAR_SHFT                                                           0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_ADDR                                              (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x3a8)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_PHYS                                              (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x3a8)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_OFFS                                              (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x3a8)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_RMSK                                                0xffffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_ATTR                                                           0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_REG_BMSK                                            0xffffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_REG_SHFT                                                   0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_ADDR                                    (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x3ac)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_PHYS                                    (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x3ac)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_OFFS                                    (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x3ac)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_RMSK                                        0xffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_ATTR                                                 0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_REG_BMSK                                    0xffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_REG_SHFT                                         0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_ADDR                                  (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x3b0)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_PHYS                                  (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x3b0)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_OFFS                                  (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x3b0)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_RMSK                                      0xffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_ATTR                                               0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_REG_BMSK                                  0xffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_REG_SHFT                                       0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_ADDR                                     (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x3b4)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_PHYS                                     (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x3b4)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_OFFS                                     (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x3b4)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_RMSK                                         0xffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_ATTR                                                  0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_REG_BMSK                                     0xffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_REG_SHFT                                          0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ADDR                                                 (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x3b8)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_PHYS                                                 (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x3b8)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_OFFS                                                 (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x3b8)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_RMSK                                                 0xffffffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ATTR                                                              0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ZONE3_BMSK                                           0xff000000
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ZONE3_SHFT                                                   24
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ZONE2_BMSK                                             0xff0000
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ZONE2_SHFT                                                   16
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ZONE1_BMSK                                               0xff00
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ZONE1_SHFT                                                    8
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ZONE0_BMSK                                                 0xff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ZONE0_SHFT                                                    0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ADDR                                         (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x3bc)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_PHYS                                         (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x3bc)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_OFFS                                         (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x3bc)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_RMSK                                         0xffffffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ATTR                                                      0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ZONE3_BMSK                                   0xff000000
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ZONE3_SHFT                                           24
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ZONE2_BMSK                                     0xff0000
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ZONE2_SHFT                                           16
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ZONE1_BMSK                                       0xff00
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ZONE1_SHFT                                            8
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ZONE0_BMSK                                         0xff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ZONE0_SHFT                                            0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_ADDR                                                   (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x3d0)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_PHYS                                                   (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x3d0)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_OFFS                                                   (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x3d0)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_RMSK                                                   0x3000ffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_ATTR                                                                0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_CURRENT_ZONE_BMSK                                      0x30000000
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_CURRENT_ZONE_SHFT                                              28
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_CURRENT_BYTE_COUNT_BMSK                                    0xffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_CURRENT_BYTE_COUNT_SHFT                                         0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_WINDOW_TIMER_ADDR                                                 (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x3d4)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_WINDOW_TIMER_PHYS                                                 (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x3d4)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_WINDOW_TIMER_OFFS                                                 (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x3d4)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_WINDOW_TIMER_RMSK                                                   0xffffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_WINDOW_TIMER_ATTR                                                              0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_WINDOW_TIMER_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_WINDOW_TIMER_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_WINDOW_TIMER_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_WINDOW_TIMER_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_WINDOW_TIMER_CURRENT_WINDOW_TIMER_BMSK                              0xffffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_WINDOW_TIMER_CURRENT_WINDOW_TIMER_SHFT                                     0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_ADDR                                                   (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x3d8)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_PHYS                                                   (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x3d8)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_OFFS                                                   (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x3d8)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_RMSK                                                   0xffffffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_ATTR                                                                0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_ZONE3_BMSK                                             0xff000000
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_ZONE3_SHFT                                                     24
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_ZONE2_BMSK                                               0xff0000
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_ZONE2_SHFT                                                     16
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_ZONE1_BMSK                                                 0xff00
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_ZONE1_SHFT                                                      8
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_ZONE0_BMSK                                                   0xff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_ZONE0_SHFT                                                      0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_ADDR(n)                                      (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0X3E0 + (0x4*(n)))
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_PHYS(n)                                      (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0X3E0 + (0x4*(n)))
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_OFFS(n)                                      (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0X3E0 + (0x4*(n)))
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_RMSK                                             0xffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_MAXn                                                  3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_ATTR                                                      0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_INI(n)                \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_ADDR(n), HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_RMSK)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_INMI(n,mask)        \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_ADDR(n), mask)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_REG_BMSK                                         0xffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_REG_SHFT                                              0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MASK_ADDR                                                      (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x400)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MASK_PHYS                                                      (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x400)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MASK_OFFS                                                      (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x400)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MASK_RMSK                                                            0x1f
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MASK_ATTR                                                                   0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MASK_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MASK_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MASK_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MASK_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MASK_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MASK_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MASK_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MASK_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MASK_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MASK_MASK_BMSK                                                       0x1f
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MASK_MASK_SHFT                                                          0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MATCH_ADDR                                                     (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x404)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MATCH_PHYS                                                     (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x404)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MATCH_OFFS                                                     (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x404)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MATCH_RMSK                                                           0x1f
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MATCH_ATTR                                                                  0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MATCH_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MATCH_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MATCH_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MATCH_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MATCH_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MATCH_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MATCH_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MATCH_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MATCH_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MATCH_MATCH_BMSK                                                     0x1f
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MATCH_MATCH_SHFT                                                        0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MASK_ADDR                                                      (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x408)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MASK_PHYS                                                      (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x408)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MASK_OFFS                                                      (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x408)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MASK_RMSK                                                             0x7
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MASK_ATTR                                                                   0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MASK_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MASK_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MASK_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MASK_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MASK_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MASK_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MASK_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MASK_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MASK_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MASK_MASK_BMSK                                                        0x7
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MASK_MASK_SHFT                                                          0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MATCH_ADDR                                                     (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x40c)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MATCH_PHYS                                                     (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x40c)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MATCH_OFFS                                                     (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x40c)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MATCH_RMSK                                                            0x7
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MATCH_ATTR                                                                  0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MATCH_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MATCH_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MATCH_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MATCH_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MATCH_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MATCH_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MATCH_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MATCH_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MATCH_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MATCH_MATCH_BMSK                                                      0x7
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MATCH_MATCH_SHFT                                                        0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_ADDR                                      (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x410)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_PHYS                                      (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x410)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_OFFS                                      (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x410)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_RMSK                                             0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_ATTR                                                   0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_BWMON_STATS_CNTR_SATURATED_BMSK                  0x2
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_BWMON_STATS_CNTR_SATURATED_SHFT                    1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_BWMON_REJECT_PERIOD_EXPIRED_BMSK                 0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_BWMON_REJECT_PERIOD_EXPIRED_SHFT                   0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR_ADDR                                       (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x414)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR_PHYS                                       (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x414)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR_OFFS                                       (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x414)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR_RMSK                                              0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR_ATTR                                                    0x2
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR_BWMON_STATS_CNTR_SATURATED_BMSK                   0x2
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR_BWMON_STATS_CNTR_SATURATED_SHFT                     1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR_BWMON_REJECT_PERIOD_EXPIRED_BMSK                  0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR_BWMON_REJECT_PERIOD_EXPIRED_SHFT                    0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_ADDR                                      (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x418)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_PHYS                                      (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x418)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_OFFS                                      (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x418)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_RMSK                                             0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_ATTR                                                   0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_BWMON_STATS_CNTR_SATURATED_BMSK                  0x2
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_BWMON_STATS_CNTR_SATURATED_SHFT                    1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_BWMON_REJECT_PERIOD_EXPIRED_BMSK                 0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_BWMON_REJECT_PERIOD_EXPIRED_SHFT                   0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_ADDR                                        (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x41c)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_PHYS                                        (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x41c)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_OFFS                                        (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x41c)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_RMSK                                               0x7
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_ATTR                                                     0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_CAPTURE_BMSK                                       0x4
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_CAPTURE_SHFT                                         2
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_ALEN_EN_BMSK                                       0x2
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_ALEN_EN_SHFT                                         1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_COUNTERS_EN_BMSK                                   0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_COUNTERS_EN_SHFT                                     0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_PERIOD_ADDR                                                 (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x420)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_PERIOD_PHYS                                                 (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x420)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_PERIOD_OFFS                                                 (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x420)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_PERIOD_RMSK                                                     0x3fff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_PERIOD_ATTR                                                              0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_PERIOD_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_PERIOD_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_PERIOD_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_PERIOD_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_PERIOD_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_PERIOD_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_PERIOD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_PERIOD_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_PERIOD_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_PERIOD_PERIOD_BMSK                                              0x3fff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_PERIOD_PERIOD_SHFT                                                   0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ACCEPT_COUNT_ADDR                                                  (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x424)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ACCEPT_COUNT_PHYS                                                  (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x424)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ACCEPT_COUNT_OFFS                                                  (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x424)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ACCEPT_COUNT_RMSK                                                  0xffffffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ACCEPT_COUNT_ATTR                                                               0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ACCEPT_COUNT_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ACCEPT_COUNT_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ACCEPT_COUNT_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ACCEPT_COUNT_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ACCEPT_COUNT_ACCEPT_COUNT_BMSK                                     0xffffffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ACCEPT_COUNT_ACCEPT_COUNT_SHFT                                              0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNT_ADDR                                                  (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x428)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNT_PHYS                                                  (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x428)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNT_OFFS                                                  (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x428)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNT_RMSK                                                  0xffffffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNT_ATTR                                                               0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNT_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNT_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNT_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNT_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNT_REJECT_COUNT_BMSK                                     0xffffffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNT_REJECT_COUNT_SHFT                                              0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_IDLE_COUNT_ADDR                                                    (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x42c)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_IDLE_COUNT_PHYS                                                    (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x42c)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_IDLE_COUNT_OFFS                                                    (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x42c)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_IDLE_COUNT_RMSK                                                    0xffffffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_IDLE_COUNT_ATTR                                                                 0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_IDLE_COUNT_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_IDLE_COUNT_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_IDLE_COUNT_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_IDLE_COUNT_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_IDLE_COUNT_IDLE_COUNT_BMSK                                         0xffffffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_IDLE_COUNT_IDLE_COUNT_SHFT                                                  0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_INTR_TARGET_ADDR                                                   (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x430)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_INTR_TARGET_PHYS                                                   (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x430)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_INTR_TARGET_OFFS                                                   (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x430)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_INTR_TARGET_RMSK                                                          0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_INTR_TARGET_ATTR                                                                0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_INTR_TARGET_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_INTR_TARGET_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_INTR_TARGET_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_INTR_TARGET_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_INTR_TARGET_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_INTR_TARGET_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_INTR_TARGET_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_INTR_TARGET_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_INTR_TARGET_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_INTR_TARGET_SECONDARY_TARGET_SELECT_BMSK                                  0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_INTR_TARGET_SECONDARY_TARGET_SELECT_SHFT                                    0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_CNTL_ADDR                                                    (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x434)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_CNTL_PHYS                                                    (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x434)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_CNTL_OFFS                                                    (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x434)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_CNTL_RMSK                                                         0xf01
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_CNTL_ATTR                                                                 0x3
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_CNTL_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_CNTL_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_CNTL_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_CNTL_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_CNTL_OUT(v)            \
                out_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_CNTL_ADDR,v)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_CNTL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_CNTL_ADDR,m,v,HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_CNTL_IN)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_CNTL_DEBUG_SEL_BMSK                                               0xf00
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_CNTL_DEBUG_SEL_SHFT                                                   8
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_CNTL_DEBUG_EN_BMSK                                                  0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_CNTL_DEBUG_EN_SHFT                                                    0

#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_READBACK_ADDR                                                (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE      + 0x438)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_READBACK_PHYS                                                (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_PHYS + 0x438)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_READBACK_OFFS                                                (ECPRI_DMA0_THROTTLE_BWMON_BWMON_BWMON_1_2_REG_BASE_OFFS + 0x438)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_READBACK_RMSK                                                0xffffffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_READBACK_ATTR                                                             0x1
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_READBACK_IN                    \
                in_dword(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_READBACK_ADDR)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_READBACK_INM(m)            \
                in_dword_masked(HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_READBACK_ADDR, m)
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_READBACK_DEBUG_BUS_READBACK_BMSK                             0xffffffff
#define HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_READBACK_DEBUG_BUS_READBACK_SHFT                                      0


#endif /* __ECPRI_HWIO_V2_H__ */
