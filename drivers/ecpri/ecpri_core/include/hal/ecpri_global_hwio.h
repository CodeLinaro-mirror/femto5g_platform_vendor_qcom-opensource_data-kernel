/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/**
  @file ecpri_global_hwio.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
  GLOBAL.*

  'Include' filters applied: <none>
  'Exclude' filters applied: RESERVED DUMMY

  Attribute definitions for the HWIO_*_ATTR macros are as follows:
0x0: Command register
0x1: Read-Only
0x2: Write-Only
0x3: Read/Write
*/

#ifndef __ECPRI_GLOBAL_HWIO_H__
#define __ECPRI_GLOBAL_HWIO_H__

/*----------------------------------------------------------------------------
 * MODULE: GLOBAL
 *--------------------------------------------------------------------------*/

#define GLOBAL_REG_BASE                                               (ECPRI_WRAPPER_BASE      + 0x00210000)
#define GLOBAL_REG_BASE_PHYS                                          (ECPRI_WRAPPER_BASE_PHYS + 0x00210000)
#define GLOBAL_REG_BASE_OFFS                                          0x00210000

#define HWIO_ECPRI_GLOBAL_CFG_ADDR                                    (GLOBAL_REG_BASE      + 0x00000000)
#define HWIO_ECPRI_GLOBAL_CFG_PHYS                                    (GLOBAL_REG_BASE_PHYS + 0x00000000)
#define HWIO_ECPRI_GLOBAL_CFG_OFFS                                    (GLOBAL_REG_BASE_OFFS + 0x00000000)
#define HWIO_ECPRI_GLOBAL_CFG_RMSK                                          0x1f
#define HWIO_ECPRI_GLOBAL_CFG_ATTR                                           0x3
#define HWIO_ECPRI_GLOBAL_CFG_IN          \
	in_dword_masked(HWIO_ECPRI_GLOBAL_CFG_ADDR, HWIO_ECPRI_GLOBAL_CFG_RMSK)
#define HWIO_ECPRI_GLOBAL_CFG_INM(m)      \
	in_dword_masked(HWIO_ECPRI_GLOBAL_CFG_ADDR, m)
#define HWIO_ECPRI_GLOBAL_CFG_OUT(v)      \
	out_dword(HWIO_ECPRI_GLOBAL_CFG_ADDR,v)
#define HWIO_ECPRI_GLOBAL_CFG_OUTM(m,v) \
	out_dword_masked_ns(HWIO_ECPRI_GLOBAL_CFG_ADDR,m,v,HWIO_ECPRI_GLOBAL_CFG_IN)
#define HWIO_ECPRI_GLOBAL_CFG_XBAR_SRES_BMSK                                0x10
#define HWIO_ECPRI_GLOBAL_CFG_XBAR_SRES_SHFT                                 0x4
#define HWIO_ECPRI_GLOBAL_CFG_AHB_RESP_ERR_EN_BMSK                           0x8
#define HWIO_ECPRI_GLOBAL_CFG_AHB_RESP_ERR_EN_SHFT                           0x3
#define HWIO_ECPRI_GLOBAL_CFG_OPERATION_MODE_BMSK                            0x7
#define HWIO_ECPRI_GLOBAL_CFG_OPERATION_MODE_SHFT                            0x0
#define HWIO_ECPRI_GLOBAL_CFG_OPERATION_MODE_DU_WITHOUT_L2_FVAL              0x0
#define HWIO_ECPRI_GLOBAL_CFG_OPERATION_MODE_RU_FVAL                         0x1
#define HWIO_ECPRI_GLOBAL_CFG_OPERATION_MODE_DRU_FVAL                        0x2
#define HWIO_ECPRI_GLOBAL_CFG_OPERATION_MODE_DU_WITH_L2_FVAL                 0x3
#define HWIO_ECPRI_GLOBAL_CFG_OPERATION_MODE_RU_CASCADE_FVAL                 0x4

#define HWIO_ECPRI_DEFAULT_HRESP_ADDR                                 (GLOBAL_REG_BASE      + 0x00000004)
#define HWIO_ECPRI_DEFAULT_HRESP_PHYS                                 (GLOBAL_REG_BASE_PHYS + 0x00000004)
#define HWIO_ECPRI_DEFAULT_HRESP_OFFS                                 (GLOBAL_REG_BASE_OFFS + 0x00000004)
#define HWIO_ECPRI_DEFAULT_HRESP_RMSK                                 0xffffffff
#define HWIO_ECPRI_DEFAULT_HRESP_ATTR                                        0x3
#define HWIO_ECPRI_DEFAULT_HRESP_IN          \
	in_dword_masked(HWIO_ECPRI_DEFAULT_HRESP_ADDR, HWIO_ECPRI_DEFAULT_HRESP_RMSK)
#define HWIO_ECPRI_DEFAULT_HRESP_INM(m)      \
	in_dword_masked(HWIO_ECPRI_DEFAULT_HRESP_ADDR, m)
#define HWIO_ECPRI_DEFAULT_HRESP_OUT(v)      \
	out_dword(HWIO_ECPRI_DEFAULT_HRESP_ADDR,v)
#define HWIO_ECPRI_DEFAULT_HRESP_OUTM(m,v) \
	out_dword_masked_ns(HWIO_ECPRI_DEFAULT_HRESP_ADDR,m,v,HWIO_ECPRI_DEFAULT_HRESP_IN)
#define HWIO_ECPRI_DEFAULT_HRESP_DATA_BMSK                            0xffffffff
#define HWIO_ECPRI_DEFAULT_HRESP_DATA_SHFT                                   0x0

#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ADDR                               (GLOBAL_REG_BASE      + 0x00000010)
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_PHYS                               (GLOBAL_REG_BASE_PHYS + 0x00000010)
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_OFFS                               (GLOBAL_REG_BASE_OFFS + 0x00000010)
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_RMSK                                    0x1ff
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ATTR                                      0x3
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_IN          \
	in_dword_masked(HWIO_ECPRI_GLOBAL_XTOR_CFG_ADDR, HWIO_ECPRI_GLOBAL_XTOR_CFG_RMSK)
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_INM(m)      \
	in_dword_masked(HWIO_ECPRI_GLOBAL_XTOR_CFG_ADDR, m)
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_OUT(v)      \
	out_dword(HWIO_ECPRI_GLOBAL_XTOR_CFG_ADDR,v)
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_OUTM(m,v) \
	out_dword_masked_ns(HWIO_ECPRI_GLOBAL_XTOR_CFG_ADDR,m,v,HWIO_ECPRI_GLOBAL_XTOR_CFG_IN)
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_RX_RESET_3_BMSK               0x100
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_RX_RESET_3_SHFT                 0x8
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_RX_RESET_2_BMSK                0x80
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_RX_RESET_2_SHFT                 0x7
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_RX_RESET_1_BMSK                0x40
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_RX_RESET_1_SHFT                 0x6
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_RX_RESET_0_BMSK                0x20
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_RX_RESET_0_SHFT                 0x5
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_TX_RESET_3_BMSK                0x10
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_TX_RESET_3_SHFT                 0x4
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_TX_RESET_2_BMSK                 0x8
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_TX_RESET_2_SHFT                 0x3
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_TX_RESET_1_BMSK                 0x4
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_TX_RESET_1_SHFT                 0x2
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_TX_RESET_0_BMSK                 0x2
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_TX_RESET_0_SHFT                 0x1
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_EN_BMSK                         0x1
#define HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_EN_SHFT                         0x0

#define HWIO_ECPRI_IPCAT_VERSION_ADDR                                 (GLOBAL_REG_BASE      + 0x00000014)
#define HWIO_ECPRI_IPCAT_VERSION_PHYS                                 (GLOBAL_REG_BASE_PHYS + 0x00000014)
#define HWIO_ECPRI_IPCAT_VERSION_OFFS                                 (GLOBAL_REG_BASE_OFFS + 0x00000014)
#define HWIO_ECPRI_IPCAT_VERSION_RMSK                                 0xffffffff
#define HWIO_ECPRI_IPCAT_VERSION_ATTR                                        0x1
#define HWIO_ECPRI_IPCAT_VERSION_IN          \
	in_dword_masked(HWIO_ECPRI_IPCAT_VERSION_ADDR, HWIO_ECPRI_IPCAT_VERSION_RMSK)
#define HWIO_ECPRI_IPCAT_VERSION_INM(m)      \
	in_dword_masked(HWIO_ECPRI_IPCAT_VERSION_ADDR, m)
#define HWIO_ECPRI_IPCAT_VERSION_MAJOR_BMSK                           0xf0000000
#define HWIO_ECPRI_IPCAT_VERSION_MAJOR_SHFT                                 0x1c
#define HWIO_ECPRI_IPCAT_VERSION_MINOR_BMSK                            0xfff0000
#define HWIO_ECPRI_IPCAT_VERSION_MINOR_SHFT                                 0x10
#define HWIO_ECPRI_IPCAT_VERSION_STEP_BMSK                                0xffff
#define HWIO_ECPRI_IPCAT_VERSION_STEP_SHFT                                   0x0

#define HWIO_ECPRI_HW_VERSION_ADDR                                    (GLOBAL_REG_BASE      + 0x00000018)
#define HWIO_ECPRI_HW_VERSION_PHYS                                    (GLOBAL_REG_BASE_PHYS + 0x00000018)
#define HWIO_ECPRI_HW_VERSION_OFFS                                    (GLOBAL_REG_BASE_OFFS + 0x00000018)
#define HWIO_ECPRI_HW_VERSION_RMSK                                          0xff
#define HWIO_ECPRI_HW_VERSION_ATTR                                           0x1
#define HWIO_ECPRI_HW_VERSION_IN          \
	in_dword_masked(HWIO_ECPRI_HW_VERSION_ADDR, HWIO_ECPRI_HW_VERSION_RMSK)
#define HWIO_ECPRI_HW_VERSION_INM(m)      \
	in_dword_masked(HWIO_ECPRI_HW_VERSION_ADDR, m)
#define HWIO_ECPRI_HW_VERSION_R_REV_BMSK                                    0xff
#define HWIO_ECPRI_HW_VERSION_R_REV_SHFT                                     0x0

#define HWIO_ECPRI_GLOBAL_QUDP_CFG_ADDR                               (GLOBAL_REG_BASE      + 0x0000001c)
#define HWIO_ECPRI_GLOBAL_QUDP_CFG_PHYS                               (GLOBAL_REG_BASE_PHYS + 0x0000001c)
#define HWIO_ECPRI_GLOBAL_QUDP_CFG_OFFS                               (GLOBAL_REG_BASE_OFFS + 0x0000001c)
#define HWIO_ECPRI_GLOBAL_QUDP_CFG_RMSK                                      0x3
#define HWIO_ECPRI_GLOBAL_QUDP_CFG_ATTR                                      0x3
#define HWIO_ECPRI_GLOBAL_QUDP_CFG_IN          \
	in_dword_masked(HWIO_ECPRI_GLOBAL_QUDP_CFG_ADDR, HWIO_ECPRI_GLOBAL_QUDP_CFG_RMSK)
#define HWIO_ECPRI_GLOBAL_QUDP_CFG_INM(m)      \
	in_dword_masked(HWIO_ECPRI_GLOBAL_QUDP_CFG_ADDR, m)
#define HWIO_ECPRI_GLOBAL_QUDP_CFG_OUT(v)      \
	out_dword(HWIO_ECPRI_GLOBAL_QUDP_CFG_ADDR,v)
#define HWIO_ECPRI_GLOBAL_QUDP_CFG_OUTM(m,v) \
	out_dword_masked_ns(HWIO_ECPRI_GLOBAL_QUDP_CFG_ADDR,m,v,HWIO_ECPRI_GLOBAL_QUDP_CFG_IN)
#define HWIO_ECPRI_GLOBAL_QUDP_CFG_L2_CFG_AHB_CGC_OPEN_BMSK                  0x2
#define HWIO_ECPRI_GLOBAL_QUDP_CFG_L2_CFG_AHB_CGC_OPEN_SHFT                  0x1
#define HWIO_ECPRI_GLOBAL_QUDP_CFG_FH_CFG_AHB_CGC_OPEN_BMSK                  0x1
#define HWIO_ECPRI_GLOBAL_QUDP_CFG_FH_CFG_AHB_CGC_OPEN_SHFT                  0x0

#define HWIO_ECPRI_GLOBAL_TPDM_SELECT_ADDR                            (GLOBAL_REG_BASE      + 0x00000020)
#define HWIO_ECPRI_GLOBAL_TPDM_SELECT_PHYS                            (GLOBAL_REG_BASE_PHYS + 0x00000020)
#define HWIO_ECPRI_GLOBAL_TPDM_SELECT_OFFS                            (GLOBAL_REG_BASE_OFFS + 0x00000020)
#define HWIO_ECPRI_GLOBAL_TPDM_SELECT_RMSK                            0xffffffff
#define HWIO_ECPRI_GLOBAL_TPDM_SELECT_ATTR                                   0x3
#define HWIO_ECPRI_GLOBAL_TPDM_SELECT_IN          \
	in_dword_masked(HWIO_ECPRI_GLOBAL_TPDM_SELECT_ADDR, HWIO_ECPRI_GLOBAL_TPDM_SELECT_RMSK)
#define HWIO_ECPRI_GLOBAL_TPDM_SELECT_INM(m)      \
	in_dword_masked(HWIO_ECPRI_GLOBAL_TPDM_SELECT_ADDR, m)
#define HWIO_ECPRI_GLOBAL_TPDM_SELECT_OUT(v)      \
	out_dword(HWIO_ECPRI_GLOBAL_TPDM_SELECT_ADDR,v)
#define HWIO_ECPRI_GLOBAL_TPDM_SELECT_OUTM(m,v) \
	out_dword_masked_ns(HWIO_ECPRI_GLOBAL_TPDM_SELECT_ADDR,m,v,HWIO_ECPRI_GLOBAL_TPDM_SELECT_IN)
#define HWIO_ECPRI_GLOBAL_TPDM_SELECT_SELECT_BMSK                     0xffffffff
#define HWIO_ECPRI_GLOBAL_TPDM_SELECT_SELECT_SHFT                            0x0

#define HWIO_ECPRI_GLOBAL_TPDM_CFG_ADDR                               (GLOBAL_REG_BASE      + 0x00000024)
#define HWIO_ECPRI_GLOBAL_TPDM_CFG_PHYS                               (GLOBAL_REG_BASE_PHYS + 0x00000024)
#define HWIO_ECPRI_GLOBAL_TPDM_CFG_OFFS                               (GLOBAL_REG_BASE_OFFS + 0x00000024)
#define HWIO_ECPRI_GLOBAL_TPDM_CFG_RMSK                                      0x7
#define HWIO_ECPRI_GLOBAL_TPDM_CFG_ATTR                                      0x3
#define HWIO_ECPRI_GLOBAL_TPDM_CFG_IN          \
	in_dword_masked(HWIO_ECPRI_GLOBAL_TPDM_CFG_ADDR, HWIO_ECPRI_GLOBAL_TPDM_CFG_RMSK)
#define HWIO_ECPRI_GLOBAL_TPDM_CFG_INM(m)      \
	in_dword_masked(HWIO_ECPRI_GLOBAL_TPDM_CFG_ADDR, m)
#define HWIO_ECPRI_GLOBAL_TPDM_CFG_OUT(v)      \
	out_dword(HWIO_ECPRI_GLOBAL_TPDM_CFG_ADDR,v)
#define HWIO_ECPRI_GLOBAL_TPDM_CFG_OUTM(m,v) \
	out_dword_masked_ns(HWIO_ECPRI_GLOBAL_TPDM_CFG_ADDR,m,v,HWIO_ECPRI_GLOBAL_TPDM_CFG_IN)
#define HWIO_ECPRI_GLOBAL_TPDM_CFG_TPDM_CMB_I_BMSK                           0x7
#define HWIO_ECPRI_GLOBAL_TPDM_CFG_TPDM_CMB_I_SHFT                           0x0


#endif /* __ECPRI_GLOBAL_HWIO_H__ */
