/* SPDX-License-Identifier: GPL-2.0-only
 *  Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef __ECPRI_QUDP_HWIO_V2_H__
#define __ECPRI_QUDP_HWIO_V2_H__
/*
===========================================================================
*/
/**
  @file ecpri_qudp_hwio.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
    ECPRI_UDP.*

  'Include' filters applied: <none>
  'Exclude' filters applied: RESERVED DUMMY 

  Attribute definitions for the HWIO_*_ATTR_V2 macros are as follows:
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
 * MODULE: ECPRI_UDP_FH_UDP_FH_REGS
 *--------------------------------------------------------------------------*/

#define ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2                                                                            (ECPRI_WRAPPER_BASE      + 0x00380000)
#define ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2_V2                                                                       (ECPRI_WRAPPER_BASE_PHYS + 0x00380000)
#define ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2_V2                                                                       0x00380000

#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ADDR_V2(p)                                                                   (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2      + 0x00000000 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_PHYS_V2(p)                                                                   (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2_V2 + 0x00000000 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_OFFS_V2(p)                                                                   (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2_V2 + 0x00000000 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_RMSK_V2                                                                      0x3fffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_MAXp_V2                                                                               2
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ATTR_V2                                                                             0x3
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ADDR_V2(p), HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_INI_V2(p))
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_ETH_PADDING_REMOVAL_BMSK_V2                                           0x20000000
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_ETH_PADDING_REMOVAL_SHFT_V2                                                 0x1d
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_SHARED_FILTERING_4_LINKS_BMSK_V2                                      0x10000000
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_SHARED_FILTERING_4_LINKS_SHFT_V2                                            0x1c
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_SHARED_FILTERING_2_LINKS_BMSK_V2                                       0x8000000
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_SHARED_FILTERING_2_LINKS_SHFT_V2                                            0x1b
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_NON_LOCAL_DST_ACTION_BMSK_V2                                                  0x7000000
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_NON_LOCAL_DST_ACTION_SHFT_V2                                                       0x18
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_LAST_IN_CHAIN_BMSK_V2                                                          0x800000
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_LAST_IN_CHAIN_SHFT_V2                                                              0x17
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_BROADCAST_CHECK_BMSK_V2                                                 0x400000
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_BROADCAST_CHECK_SHFT_V2                                                     0x16
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_USE_EXTERNAL_NOT_LOCAL_MAC_DST_BMSK_V2                                         0x200000
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_USE_EXTERNAL_NOT_LOCAL_MAC_DST_SHFT_V2                                             0x15
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_MAC_DST_CHECK_BMSK_V2                                                   0x100000
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_MAC_DST_CHECK_SHFT_V2                                                       0x14
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_IP_FILT_MISS_ACTION_BMSK_V2                                                     0xc0000
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_IP_FILT_MISS_ACTION_SHFT_V2                                                        0x12
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_VLAN_FILT_MISS_ACTION_BMSK_V2                                                   0x30000
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_VLAN_FILT_MISS_ACTION_SHFT_V2                                                      0x10
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_DISABLE_ST_AND_FW_BMSK_V2                                                        0x8000
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_DISABLE_ST_AND_FW_SHFT_V2                                                           0xf
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_IP_LEN_ERR_ACTION_BMSK_V2                                                        0x6000
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_IP_LEN_ERR_ACTION_SHFT_V2                                                           0xd
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_PKT_ERR_ACTION_BMSK_V2                                                           0x1800
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_PKT_ERR_ACTION_SHFT_V2                                                              0xb
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_FCS_ERR_ACTION_BMSK_V2                                                            0x600
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_FCS_ERR_ACTION_SHFT_V2                                                              0x9
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_UDP_CS_ERR_ACTION_BMSK_V2                                                         0x180
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_UDP_CS_ERR_ACTION_SHFT_V2                                                           0x7
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_IPV4_CS_ERR_ACTION_BMSK_V2                                                         0x60
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_IPV4_CS_ERR_ACTION_SHFT_V2                                                          0x5
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_IP_LEN_CHECK_BMSK_V2                                                        0x10
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_IP_LEN_CHECK_SHFT_V2                                                         0x4
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_UDP_CS_CHECK_BMSK_V2                                                         0x8
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_UDP_CS_CHECK_SHFT_V2                                                         0x3
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_VLAN_FILT_BMSK_V2                                                            0x4
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_VLAN_FILT_SHFT_V2                                                            0x2
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_UDP_DST_CLASS_BMSK_V2                                                        0x2
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_UDP_DST_CLASS_SHFT_V2                                                        0x1
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_IP_DST_FILT_BMSK_V2                                                          0x1
#define HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_IP_DST_FILT_SHFT_V2                                                          0x0

#define HWIO_ECPRI_UDP_FH_WORDS_BEFORE_TRANSMITTING_p_ADDR_V2(p)                                                        (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x0000000c + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_WORDS_BEFORE_TRANSMITTING_p_PHYS_V2(p)                                                        (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x0000000c + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_WORDS_BEFORE_TRANSMITTING_p_OFFS_V2(p)                                                        (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x0000000c + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_WORDS_BEFORE_TRANSMITTING_p_RMSK_V2                                                                 0xff
#define HWIO_ECPRI_UDP_FH_WORDS_BEFORE_TRANSMITTING_p_MAXp_V2                                                                    2
#define HWIO_ECPRI_UDP_FH_WORDS_BEFORE_TRANSMITTING_p_ATTR_V2                                                                  0x3
#define HWIO_ECPRI_UDP_FH_WORDS_BEFORE_TRANSMITTING_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_WORDS_BEFORE_TRANSMITTING_p_ADDR_V2(p), HWIO_ECPRI_UDP_FH_WORDS_BEFORE_TRANSMITTING_p_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_WORDS_BEFORE_TRANSMITTING_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_WORDS_BEFORE_TRANSMITTING_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_FH_WORDS_BEFORE_TRANSMITTING_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_WORDS_BEFORE_TRANSMITTING_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_FH_WORDS_BEFORE_TRANSMITTING_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_WORDS_BEFORE_TRANSMITTING_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_FH_WORDS_BEFORE_TRANSMITTING_p_INI_V2(p))
#define HWIO_ECPRI_UDP_FH_WORDS_BEFORE_TRANSMITTING_p_VALUE_BMSK_V2                                                           0xff
#define HWIO_ECPRI_UDP_FH_WORDS_BEFORE_TRANSMITTING_p_VALUE_SHFT_V2                                                            0x0

#define HWIO_ECPRI_UDP_FH_UDP_PTP_PORT_NUM_p_ADDR_V2(p)                                                                 (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x00000018 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_UDP_PTP_PORT_NUM_p_PHYS_V2(p)                                                                 (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x00000018 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_UDP_PTP_PORT_NUM_p_OFFS_V2(p)                                                                 (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x00000018 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_UDP_PTP_PORT_NUM_p_RMSK_V2                                                                        0xffff
#define HWIO_ECPRI_UDP_FH_UDP_PTP_PORT_NUM_p_MAXp_V2                                                                             2
#define HWIO_ECPRI_UDP_FH_UDP_PTP_PORT_NUM_p_ATTR_V2                                                                           0x3
#define HWIO_ECPRI_UDP_FH_UDP_PTP_PORT_NUM_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_UDP_PTP_PORT_NUM_p_ADDR_V2(p), HWIO_ECPRI_UDP_FH_UDP_PTP_PORT_NUM_p_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_UDP_PTP_PORT_NUM_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_UDP_PTP_PORT_NUM_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_FH_UDP_PTP_PORT_NUM_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_UDP_PTP_PORT_NUM_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_FH_UDP_PTP_PORT_NUM_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_UDP_PTP_PORT_NUM_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_FH_UDP_PTP_PORT_NUM_p_INI_V2(p))
#define HWIO_ECPRI_UDP_FH_UDP_PTP_PORT_NUM_p_VALUE_BMSK_V2                                                                  0xffff
#define HWIO_ECPRI_UDP_FH_UDP_PTP_PORT_NUM_p_VALUE_SHFT_V2                                                                     0x0

#define HWIO_ECPRI_UDP_FH_ECPRI_ETHERTYPE_p_ADDR_V2(p)                                                                  (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x0000002c + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_ECPRI_ETHERTYPE_p_PHYS_V2(p)                                                                  (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x0000002c + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_ECPRI_ETHERTYPE_p_OFFS_V2(p)                                                                  (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x0000002c + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_ECPRI_ETHERTYPE_p_RMSK_V2                                                                         0xffff
#define HWIO_ECPRI_UDP_FH_ECPRI_ETHERTYPE_p_MAXp_V2                                                                              2
#define HWIO_ECPRI_UDP_FH_ECPRI_ETHERTYPE_p_ATTR_V2                                                                            0x3
#define HWIO_ECPRI_UDP_FH_ECPRI_ETHERTYPE_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_ECPRI_ETHERTYPE_p_ADDR_V2(p), HWIO_ECPRI_UDP_FH_ECPRI_ETHERTYPE_p_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_ECPRI_ETHERTYPE_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_ECPRI_ETHERTYPE_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_FH_ECPRI_ETHERTYPE_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_ECPRI_ETHERTYPE_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_FH_ECPRI_ETHERTYPE_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_ECPRI_ETHERTYPE_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_FH_ECPRI_ETHERTYPE_p_INI_V2(p))
#define HWIO_ECPRI_UDP_FH_ECPRI_ETHERTYPE_p_VALUE_BMSK_V2                                                                   0xffff
#define HWIO_ECPRI_UDP_FH_ECPRI_ETHERTYPE_p_VALUE_SHFT_V2                                                                      0x0

#define HWIO_ECPRI_UDP_FH_PTP_ETHERTYPE_p_ADDR_V2(p)                                                                    (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x00000038 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_PTP_ETHERTYPE_p_PHYS_V2(p)                                                                    (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x00000038 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_PTP_ETHERTYPE_p_OFFS_V2(p)                                                                    (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x00000038 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_PTP_ETHERTYPE_p_RMSK_V2                                                                           0xffff
#define HWIO_ECPRI_UDP_FH_PTP_ETHERTYPE_p_MAXp_V2                                                                                2
#define HWIO_ECPRI_UDP_FH_PTP_ETHERTYPE_p_ATTR_V2                                                                              0x3
#define HWIO_ECPRI_UDP_FH_PTP_ETHERTYPE_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_PTP_ETHERTYPE_p_ADDR_V2(p), HWIO_ECPRI_UDP_FH_PTP_ETHERTYPE_p_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_PTP_ETHERTYPE_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_PTP_ETHERTYPE_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_FH_PTP_ETHERTYPE_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_PTP_ETHERTYPE_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_FH_PTP_ETHERTYPE_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_PTP_ETHERTYPE_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_FH_PTP_ETHERTYPE_p_INI_V2(p))
#define HWIO_ECPRI_UDP_FH_PTP_ETHERTYPE_p_VALUE_BMSK_V2                                                                     0xffff
#define HWIO_ECPRI_UDP_FH_PTP_ETHERTYPE_p_VALUE_SHFT_V2                                                                        0x0

#define HWIO_ECPRI_UDP_FH_FILT_ERROR_CHANNEL_CFG_p_ADDR_V2(p)                                                           (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x00000044 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_ERROR_CHANNEL_CFG_p_PHYS_V2(p)                                                           (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x00000044 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_ERROR_CHANNEL_CFG_p_OFFS_V2(p)                                                           (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x00000044 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_ERROR_CHANNEL_CFG_p_RMSK_V2                                                                     0x3
#define HWIO_ECPRI_UDP_FH_FILT_ERROR_CHANNEL_CFG_p_MAXp_V2                                                                       2
#define HWIO_ECPRI_UDP_FH_FILT_ERROR_CHANNEL_CFG_p_ATTR_V2                                                                     0x3
#define HWIO_ECPRI_UDP_FH_FILT_ERROR_CHANNEL_CFG_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_FILT_ERROR_CHANNEL_CFG_p_ADDR_V2(p), HWIO_ECPRI_UDP_FH_FILT_ERROR_CHANNEL_CFG_p_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_FILT_ERROR_CHANNEL_CFG_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_FILT_ERROR_CHANNEL_CFG_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_FH_FILT_ERROR_CHANNEL_CFG_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_FILT_ERROR_CHANNEL_CFG_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_FH_FILT_ERROR_CHANNEL_CFG_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_FILT_ERROR_CHANNEL_CFG_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_FH_FILT_ERROR_CHANNEL_CFG_p_INI_V2(p))
#define HWIO_ECPRI_UDP_FH_FILT_ERROR_CHANNEL_CFG_p_SEND_IP_FILT_MISS_TO_ERROR_CHANNEL_BMSK_V2                                  0x2
#define HWIO_ECPRI_UDP_FH_FILT_ERROR_CHANNEL_CFG_p_SEND_IP_FILT_MISS_TO_ERROR_CHANNEL_SHFT_V2                                  0x1
#define HWIO_ECPRI_UDP_FH_FILT_ERROR_CHANNEL_CFG_p_SEND_VLAN_FILT_MISS_TO_ERROR_CHANNEL_BMSK_V2                                0x1
#define HWIO_ECPRI_UDP_FH_FILT_ERROR_CHANNEL_CFG_p_SEND_VLAN_FILT_MISS_TO_ERROR_CHANNEL_SHFT_V2                                0x0

#define HWIO_ECPRI_UDP_FH_TRAP_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n)                                                         (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x00000060 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_MISC_PORT_p_ENTRY_n_PHYS_V2(p,n)                                                         (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x00000060 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_MISC_PORT_p_ENTRY_n_OFFS_V2(p,n)                                                         (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x00000060 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_MISC_PORT_p_ENTRY_n_RMSK_V2                                                                 0xfffff
#define HWIO_ECPRI_UDP_FH_TRAP_MISC_PORT_p_ENTRY_n_MAXp_V2                                                                       2
#define HWIO_ECPRI_UDP_FH_TRAP_MISC_PORT_p_ENTRY_n_MAXn_V2                                                                       3
#define HWIO_ECPRI_UDP_FH_TRAP_MISC_PORT_p_ENTRY_n_ATTR_V2                                                                     0x3
#define HWIO_ECPRI_UDP_FH_TRAP_MISC_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_TRAP_MISC_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_TRAP_MISC_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_TRAP_MISC_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_TRAP_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_TRAP_MISC_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_TRAP_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_TRAP_MISC_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_TRAP_MISC_PORT_p_ENTRY_n_ENABLE_BMSK_V2                                                          0x80000
#define HWIO_ECPRI_UDP_FH_TRAP_MISC_PORT_p_ENTRY_n_ENABLE_SHFT_V2                                                             0x13
#define HWIO_ECPRI_UDP_FH_TRAP_MISC_PORT_p_ENTRY_n_ACTION_BMSK_V2                                                          0x70000
#define HWIO_ECPRI_UDP_FH_TRAP_MISC_PORT_p_ENTRY_n_ACTION_SHFT_V2                                                             0x10
#define HWIO_ECPRI_UDP_FH_TRAP_MISC_PORT_p_ENTRY_n_RULE32_OFFSET_BMSK_V2                                                    0xff00
#define HWIO_ECPRI_UDP_FH_TRAP_MISC_PORT_p_ENTRY_n_RULE32_OFFSET_SHFT_V2                                                       0x8
#define HWIO_ECPRI_UDP_FH_TRAP_MISC_PORT_p_ENTRY_n_RULE64_OFFSET_BMSK_V2                                                      0xff
#define HWIO_ECPRI_UDP_FH_TRAP_MISC_PORT_p_ENTRY_n_RULE64_OFFSET_SHFT_V2                                                       0x0

#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n)                                               (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x00000090 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_PHYS_V2(p,n)                                               (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x00000090 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_OFFS_V2(p,n)                                               (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x00000090 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_RMSK_V2                                                    0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_MAXp_V2                                                             2
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_MAXn_V2                                                             3
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_ATTR_V2                                                           0x3
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_VALUE_BMSK_V2                                              0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_VALUE_SHFT_V2                                                     0x0

#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n)                                               (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x000000c0 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_PHYS_V2(p,n)                                               (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x000000c0 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_OFFS_V2(p,n)                                               (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x000000c0 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_RMSK_V2                                                    0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_MAXp_V2                                                             2
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_MAXn_V2                                                             3
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_ATTR_V2                                                           0x3
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_VALUE_BMSK_V2                                              0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_VALUE_SHFT_V2                                                     0x0

#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n)                                              (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x000000f0 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_PHYS_V2(p,n)                                              (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x000000f0 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_OFFS_V2(p,n)                                              (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x000000f0 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_RMSK_V2                                                   0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_MAXp_V2                                                            2
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_MAXn_V2                                                            3
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_ATTR_V2                                                          0x3
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_VALUE_BMSK_V2                                             0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_VALUE_SHFT_V2                                                    0x0

#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n)                                              (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x00000120 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_PHYS_V2(p,n)                                              (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x00000120 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_OFFS_V2(p,n)                                              (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x00000120 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_RMSK_V2                                                   0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_MAXp_V2                                                            2
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_MAXn_V2                                                            3
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_ATTR_V2                                                          0x3
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_VALUE_BMSK_V2                                             0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_VALUE_SHFT_V2                                                    0x0

#define HWIO_ECPRI_UDP_FH_TRAP_RULE32_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n)                                                   (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x00000150 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_RULE32_VAL_PORT_p_ENTRY_n_PHYS_V2(p,n)                                                   (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x00000150 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_RULE32_VAL_PORT_p_ENTRY_n_OFFS_V2(p,n)                                                   (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x00000150 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_RULE32_VAL_PORT_p_ENTRY_n_RMSK_V2                                                        0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_RULE32_VAL_PORT_p_ENTRY_n_MAXp_V2                                                                 2
#define HWIO_ECPRI_UDP_FH_TRAP_RULE32_VAL_PORT_p_ENTRY_n_MAXn_V2                                                                 3
#define HWIO_ECPRI_UDP_FH_TRAP_RULE32_VAL_PORT_p_ENTRY_n_ATTR_V2                                                               0x3
#define HWIO_ECPRI_UDP_FH_TRAP_RULE32_VAL_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_RULE32_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_TRAP_RULE32_VAL_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_TRAP_RULE32_VAL_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_RULE32_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_TRAP_RULE32_VAL_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_TRAP_RULE32_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_TRAP_RULE32_VAL_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_TRAP_RULE32_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_TRAP_RULE32_VAL_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_TRAP_RULE32_VAL_PORT_p_ENTRY_n_VALUE_BMSK_V2                                                  0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_RULE32_VAL_PORT_p_ENTRY_n_VALUE_SHFT_V2                                                         0x0

#define HWIO_ECPRI_UDP_FH_TRAP_RULE32_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n)                                                  (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x00000180 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_RULE32_MASK_PORT_p_ENTRY_n_PHYS_V2(p,n)                                                  (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x00000180 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_RULE32_MASK_PORT_p_ENTRY_n_OFFS_V2(p,n)                                                  (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x00000180 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_RULE32_MASK_PORT_p_ENTRY_n_RMSK_V2                                                       0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_RULE32_MASK_PORT_p_ENTRY_n_MAXp_V2                                                                2
#define HWIO_ECPRI_UDP_FH_TRAP_RULE32_MASK_PORT_p_ENTRY_n_MAXn_V2                                                                3
#define HWIO_ECPRI_UDP_FH_TRAP_RULE32_MASK_PORT_p_ENTRY_n_ATTR_V2                                                              0x3
#define HWIO_ECPRI_UDP_FH_TRAP_RULE32_MASK_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_RULE32_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_TRAP_RULE32_MASK_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_TRAP_RULE32_MASK_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_RULE32_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_TRAP_RULE32_MASK_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_TRAP_RULE32_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_TRAP_RULE32_MASK_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_TRAP_RULE32_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_TRAP_RULE32_MASK_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_TRAP_RULE32_MASK_PORT_p_ENTRY_n_VALUE_BMSK_V2                                                 0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_RULE32_MASK_PORT_p_ENTRY_n_VALUE_SHFT_V2                                                        0x0

#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_ADDR_V2(p,n)                                            (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x000001b0 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_PHYS_V2(p,n)                                            (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x000001b0 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_OFFS_V2(p,n)                                            (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x000001b0 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_RMSK_V2                                                     0xffff
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_MAXp_V2                                                          2
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_MAXn_V2                                                          1
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_ATTR_V2                                                        0x3
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_LARGE_SET_RULE32_OFFSET_BMSK_V2                             0xff00
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_LARGE_SET_RULE32_OFFSET_SHFT_V2                                0x8
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_LARGE_SET_RULE128_OFFSET_BMSK_V2                              0xff
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_LARGE_SET_RULE128_OFFSET_SHFT_V2                               0x0

#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n)                                         (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x000001c8 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_PHYS_V2(p,n)                                         (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x000001c8 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_OFFS_V2(p,n)                                         (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x000001c8 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_RMSK_V2                                              0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_MAXp_V2                                                       2
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_MAXn_V2                                                       1
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_ATTR_V2                                                     0x3
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_VALUE_BMSK_V2                                        0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_VALUE_SHFT_V2                                               0x0

#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n)                                        (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x000001e0 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_PHYS_V2(p,n)                                        (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x000001e0 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_OFFS_V2(p,n)                                        (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x000001e0 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_RMSK_V2                                             0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_MAXp_V2                                                      2
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_MAXn_V2                                                      1
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_ATTR_V2                                                    0x3
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_VALUE_BMSK_V2                                       0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_VALUE_SHFT_V2                                              0x0

#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n)                                      (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x000001f8 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_PHYS_V2(p,n)                                      (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x000001f8 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_OFFS_V2(p,n)                                      (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x000001f8 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_RMSK_V2                                           0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_MAXp_V2                                                    2
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_MAXn_V2                                                    1
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_ATTR_V2                                                  0x3
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_VALUE_BMSK_V2                                     0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_VALUE_SHFT_V2                                            0x0

#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n)                                     (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x00000210 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_PHYS_V2(p,n)                                     (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x00000210 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_OFFS_V2(p,n)                                     (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x00000210 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_RMSK_V2                                          0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_MAXp_V2                                                   2
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_MAXn_V2                                                   1
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_ATTR_V2                                                 0x3
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_VALUE_BMSK_V2                                    0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_VALUE_SHFT_V2                                           0x0

#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n)                                      (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x00000228 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_PHYS_V2(p,n)                                      (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x00000228 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_OFFS_V2(p,n)                                      (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x00000228 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_RMSK_V2                                           0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_MAXp_V2                                                    2
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_MAXn_V2                                                    1
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_ATTR_V2                                                  0x3
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_VALUE_BMSK_V2                                     0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_VALUE_SHFT_V2                                            0x0

#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n)                                     (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x00000240 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_PHYS_V2(p,n)                                     (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x00000240 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_OFFS_V2(p,n)                                     (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x00000240 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_RMSK_V2                                          0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_MAXp_V2                                                   2
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_MAXn_V2                                                   1
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_ATTR_V2                                                 0x3
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_VALUE_BMSK_V2                                    0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_VALUE_SHFT_V2                                           0x0

#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n)                                      (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x00000258 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_PHYS_V2(p,n)                                      (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x00000258 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_OFFS_V2(p,n)                                      (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x00000258 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_RMSK_V2                                           0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_MAXp_V2                                                    2
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_MAXn_V2                                                    1
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_ATTR_V2                                                  0x3
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_VALUE_BMSK_V2                                     0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_VALUE_SHFT_V2                                            0x0

#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n)                                     (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x00000270 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_PHYS_V2(p,n)                                     (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x00000270 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_OFFS_V2(p,n)                                     (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x00000270 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_RMSK_V2                                          0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_MAXp_V2                                                   2
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_MAXn_V2                                                   1
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_ATTR_V2                                                 0x3
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_VALUE_BMSK_V2                                    0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_VALUE_SHFT_V2                                           0x0

#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n)                                      (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x00000288 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_PHYS_V2(p,n)                                      (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x00000288 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_OFFS_V2(p,n)                                      (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x00000288 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_RMSK_V2                                           0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_MAXp_V2                                                    2
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_MAXn_V2                                                    1
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_ATTR_V2                                                  0x3
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_VALUE_BMSK_V2                                     0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_VALUE_SHFT_V2                                            0x0

#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n)                                     (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x000002a0 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_PHYS_V2(p,n)                                     (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x000002a0 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_OFFS_V2(p,n)                                     (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x000002a0 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_RMSK_V2                                          0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_MAXp_V2                                                   2
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_MAXn_V2                                                   1
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_ATTR_V2                                                 0x3
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_VALUE_BMSK_V2                                    0xffffffff
#define HWIO_ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_VALUE_SHFT_V2                                           0x0

#define HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_ADDR_V2(p)                                                                (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x000002b8 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_PHYS_V2(p)                                                                (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x000002b8 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_OFFS_V2(p)                                                                (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x000002b8 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_RMSK_V2                                                                         0x3f
#define HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_MAXp_V2                                                                            2
#define HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_ATTR_V2                                                                          0x3
#define HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_ADDR_V2(p), HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_INI_V2(p))
#define HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_TRAP_PTP_OVER_IPV6_WITH_VLAN_EN_BMSK_V2                                         0x20
#define HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_TRAP_PTP_OVER_IPV6_WITH_VLAN_EN_SHFT_V2                                          0x5
#define HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_TRAP_PTP_OVER_IPV6_WITHOUT_VLAN_EN_BMSK_V2                                      0x10
#define HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_TRAP_PTP_OVER_IPV6_WITHOUT_VLAN_EN_SHFT_V2                                       0x4
#define HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_TRAP_PTP_OVER_IPV4_WITH_VLAN_EN_BMSK_V2                                          0x8
#define HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_TRAP_PTP_OVER_IPV4_WITH_VLAN_EN_SHFT_V2                                          0x3
#define HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_TRAP_PTP_OVER_IPV4_WITHOUT_VLAN_EN_BMSK_V2                                       0x4
#define HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_TRAP_PTP_OVER_IPV4_WITHOUT_VLAN_EN_SHFT_V2                                       0x2
#define HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_TRAP_PTP_OVER_ETH_WITH_VLAN_EN_BMSK_V2                                           0x2
#define HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_TRAP_PTP_OVER_ETH_WITH_VLAN_EN_SHFT_V2                                           0x1
#define HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_TRAP_PTP_OVER_ETH_WITHOUT_VLAN_EN_BMSK_V2                                        0x1
#define HWIO_ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p_TRAP_PTP_OVER_ETH_WITHOUT_VLAN_EN_SHFT_V2                                        0x0

#define HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p)                                           (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x000003c0 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_PHYS_V2(p)                                           (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x000003c0 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_OFFS_V2(p)                                           (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x000003c0 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_RMSK_V2                                                  0xffff
#define HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_MAXp_V2                                                       2
#define HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_ATTR_V2                                                     0x3
#define HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p), HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_INI_V2(p))
#define HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_BMSK_V2                                       0xffff
#define HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_SHFT_V2                                          0x0

#define HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p)                                  (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x000003cc + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_PHYS_V2(p)                                  (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x000003cc + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_OFFS_V2(p)                                  (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x000003cc + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_RMSK_V2                                         0xffff
#define HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_MAXp_V2                                              2
#define HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_ATTR_V2                                            0x3
#define HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p), HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_INI_V2(p))
#define HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_BMSK_V2                              0xffff
#define HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_SHFT_V2                                 0x0

#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p)                                         (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x000003e4 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_PHYS_V2(p)                                         (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x000003e4 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_OFFS_V2(p)                                         (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x000003e4 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_RMSK_V2                                                0xffff
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_MAXp_V2                                                     2
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_ATTR_V2                                                   0x3
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p), HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_INI_V2(p))
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_BMSK_V2                                     0xffff
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_SHFT_V2                                        0x0

#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p)                                         (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x000003f0 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_PHYS_V2(p)                                         (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x000003f0 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_OFFS_V2(p)                                         (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x000003f0 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_RMSK_V2                                               0xfffff
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_MAXp_V2                                                     2
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_ATTR_V2                                                   0x3
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p), HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_INI_V2(p))
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_BMSK_V2                                    0xfffff
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_SHFT_V2                                        0x0

#define HWIO_ECPRI_UDP_FH_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_ADDR_V2(p,n)                                            (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x000003fc + 0x4 * (n) + 0x10 * (p))
#define HWIO_ECPRI_UDP_FH_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_PHYS_V2(p,n)                                            (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x000003fc + 0x4 * (n) + 0x10 * (p))
#define HWIO_ECPRI_UDP_FH_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_OFFS_V2(p,n)                                            (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x000003fc + 0x4 * (n) + 0x10 * (p))
#define HWIO_ECPRI_UDP_FH_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_RMSK_V2                                                      0x3ff
#define HWIO_ECPRI_UDP_FH_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_MAXp_V2                                                          2
#define HWIO_ECPRI_UDP_FH_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_MAXn_V2                                                          3
#define HWIO_ECPRI_UDP_FH_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_ATTR_V2                                                        0x3
#define HWIO_ECPRI_UDP_FH_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_RING_ID_BMSK_V2                                              0x3fc
#define HWIO_ECPRI_UDP_FH_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_RING_ID_SHFT_V2                                                0x2
#define HWIO_ECPRI_UDP_FH_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_GSI_ID_BMSK_V2                                                 0x3
#define HWIO_ECPRI_UDP_FH_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_GSI_ID_SHFT_V2                                                 0x0

#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_ADDR_V2(p)                                                                 (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x00000500 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_PHYS_V2(p)                                                                 (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x00000500 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_OFFS_V2(p)                                                                 (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x00000500 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_RMSK_V2                                                                       0x3ffff
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_MAXp_V2                                                                             2
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_ATTR_V2                                                                           0x1
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_ADDR_V2(p), HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_INGRESS_CMD_FIFO_EMPTY_LINK_3_BMSK_V2                                         0x20000
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_INGRESS_CMD_FIFO_EMPTY_LINK_3_SHFT_V2                                            0x11
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_INGRESS_CMD_FIFO_EMPTY_LINK_2_BMSK_V2                                         0x10000
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_INGRESS_CMD_FIFO_EMPTY_LINK_2_SHFT_V2                                            0x10
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_INGRESS_CMD_FIFO_EMPTY_LINK_1_BMSK_V2                                          0x8000
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_INGRESS_CMD_FIFO_EMPTY_LINK_1_SHFT_V2                                             0xf
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_INGRESS_PKT_FIFO_EMPTY_LINK_3_BMSK_V2                                          0x4000
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_INGRESS_PKT_FIFO_EMPTY_LINK_3_SHFT_V2                                             0xe
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_INGRESS_PKT_FIFO_EMPTY_LINK_2_BMSK_V2                                          0x2000
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_INGRESS_PKT_FIFO_EMPTY_LINK_2_SHFT_V2                                             0xd
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_INGRESS_PKT_FIFO_EMPTY_LINK_1_BMSK_V2                                          0x1000
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_INGRESS_PKT_FIFO_EMPTY_LINK_1_SHFT_V2                                             0xc
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_INGRESS_ARBITER_IDLE_BMSK_V2                                                    0x800
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_INGRESS_ARBITER_IDLE_SHFT_V2                                                      0xb
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_EGRESS_CS_FIFO_EMPTY_BMSK_V2                                                    0x400
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_EGRESS_CS_FIFO_EMPTY_SHFT_V2                                                      0xa
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_EGRESS_OUTPUT_FIFO_EMPTY_BMSK_V2                                                0x200
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_EGRESS_OUTPUT_FIFO_EMPTY_SHFT_V2                                                  0x9
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_EGRESS_ALIGNER_IDLE_BMSK_V2                                                     0x100
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_EGRESS_ALIGNER_IDLE_SHFT_V2                                                       0x8
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_EGRESS_PKT_FIFO_EMPTY_BMSK_V2                                                    0x80
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_EGRESS_PKT_FIFO_EMPTY_SHFT_V2                                                     0x7
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_EGRESS_HDRI_IDLE_BMSK_V2                                                         0x40
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_EGRESS_HDRI_IDLE_SHFT_V2                                                          0x6
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_EGRESS_IDLE_BMSK_V2                                                              0x20
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_EGRESS_IDLE_SHFT_V2                                                               0x5
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_INGRESS_CMD_FIFO_EMPTY_LINK_0_BMSK_V2                                            0x10
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_INGRESS_CMD_FIFO_EMPTY_LINK_0_SHFT_V2                                             0x4
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_INGRESS_PKT_FIFO_EMPTY_LINK_0_BMSK_V2                                             0x8
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_INGRESS_PKT_FIFO_EMPTY_LINK_0_SHFT_V2                                             0x3
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_INGRESS_ALIGNER_IDLE_BMSK_V2                                                      0x4
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_INGRESS_ALIGNER_IDLE_SHFT_V2                                                      0x2
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_INGRESS_IDLE_BMSK_V2                                                              0x2
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_INGRESS_IDLE_SHFT_V2                                                              0x1
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_PORT_IS_IDLE_BMSK_V2                                                              0x1
#define HWIO_ECPRI_UDP_FH_IDLE_STATUS_PORT_p_PORT_IS_IDLE_SHFT_V2                                                              0x0

#define HWIO_ECPRI_UDP_FH_CGC_CFG_ADDR_V2                                                                               (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x00000510)
#define HWIO_ECPRI_UDP_FH_CGC_CFG_PHYS_V2                                                                               (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x00000510)
#define HWIO_ECPRI_UDP_FH_CGC_CFG_OFFS_V2                                                                               (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x00000510)
#define HWIO_ECPRI_UDP_FH_CGC_CFG_RMSK_V2                                                                                      0x3
#define HWIO_ECPRI_UDP_FH_CGC_CFG_ATTR_V2                                                                                      0x3
#define HWIO_ECPRI_UDP_FH_CGC_CFG_IN_V2          \
        in_dword_masked(HWIO_ECPRI_UDP_FH_CGC_CFG_ADDR_V2, HWIO_ECPRI_UDP_FH_CGC_CFG_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_CGC_CFG_IN_V2M(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_FH_CGC_CFG_ADDR_V2, m)
#define HWIO_ECPRI_UDP_FH_CGC_CFG_OUT_V2(v)      \
        out_dword(HWIO_ECPRI_UDP_FH_CGC_CFG_ADDR_V2,v)
#define HWIO_ECPRI_UDP_FH_CGC_CFG_OUTM_V2(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_CGC_CFG_ADDR_V2,m,v,HWIO_ECPRI_UDP_FH_CGC_CFG_IN_V2)
#define HWIO_ECPRI_UDP_FH_CGC_CFG_EGRESS_CGC_OPEN_BMSK_V2                                                                      0x2
#define HWIO_ECPRI_UDP_FH_CGC_CFG_EGRESS_CGC_OPEN_SHFT_V2                                                                      0x1
#define HWIO_ECPRI_UDP_FH_CGC_CFG_IN_V2GRESS_CGC_OPEN_BMSK_V2                                                                     0x1
#define HWIO_ECPRI_UDP_FH_CGC_CFG_IN_V2GRESS_CGC_OPEN_SHFT_V2                                                                     0x0

#define HWIO_ECPRI_UDP_FH_HW_PARAMS_0_ADDR_V2                                                                           (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x00000514)
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_0_PHYS_V2                                                                           (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x00000514)
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_0_OFFS_V2                                                                           (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x00000514)
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_0_RMSK_V2                                                                           0xffffffff
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_0_ATTR_V2                                                                                  0x1
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_0_IN_V2          \
        in_dword_masked(HWIO_ECPRI_UDP_FH_HW_PARAMS_0_ADDR, HWIO_ECPRI_UDP_FH_HW_PARAMS_0_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_0_INM_V2(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_FH_HW_PARAMS_0_ADDR, m)
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_0_L3_SUPPORT_BMSK_V2                                                                0x80000000
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_0_L3_SUPPORT_SHFT_V2                                                                      0x1f
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_0_UDP_CLASSIFICATION_ENTRIES_N_BMSK_V2                                              0x7e000000
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_0_UDP_CLASSIFICATION_ENTRIES_N_SHFT_V2                                                    0x19
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_0_IP_TABLE_ENTRIES_N_BMSK_V2                                                         0x1ff0000
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_0_IP_TABLE_ENTRIES_N_SHFT_V2                                                              0x10
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_0_ETH_TABLE_ENTRIES_N_BMSK_V2                                                           0xff80
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_0_ETH_TABLE_ENTRIES_N_SHFT_V2                                                              0x7
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_0_LINKS_N_BMSK_V2                                                                         0x70
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_0_LINKS_N_SHFT_V2                                                                          0x4
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_0_PORTS_N_BMSK_V2                                                                          0xc
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_0_PORTS_N_SHFT_V2                                                                          0x2
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_0_INSTANCE_TYPE_BMSK_V2                                                                    0x3
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_0_INSTANCE_TYPE_SHFT_V2                                                                    0x0
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_0_INSTANCE_TYPE_FH_FVAL                                                                 0x0
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_0_INSTANCE_TYPE_C2C_FVAL                                                                0x1
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_0_INSTANCE_TYPE_L2_FVAL                                                                 0x2

#define HWIO_ECPRI_UDP_FH_HW_PARAMS_1_ADDR_V2                                                                           (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2      + 0x00000518)
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_1_PHYS_V2                                                                           (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2_V2 + 0x00000518)
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_1_OFFS_V2                                                                           (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2_V2 + 0x00000518)
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_1_RMSK_V2                                                                               0x7fff
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_1_ATTR_V2                                                                                  0x1
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_1_IN_V2          \
        in_dword_masked(HWIO_ECPRI_UDP_FH_HW_PARAMS_1_ADDR_V2, HWIO_ECPRI_UDP_FH_HW_PARAMS_1_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_1_INM_V2(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_FH_HW_PARAMS_1_ADDR_V2, m)
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_1_ETH_DST_FILT_ENTRIES_N_BMSK_V2                                                        0x7c00
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_1_ETH_DST_FILT_ENTRIES_N_SHFT_V2                                                           0xa
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_1_IP_FILT_ENTRIES_N_BMSK_V2                                                              0x3e0
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_1_IP_FILT_ENTRIES_N_SHFT_V2                                                                0x5
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_1_VLAN_FILT_ENTRIES_N_BMSK_V2                                                             0x1f
#define HWIO_ECPRI_UDP_FH_HW_PARAMS_1_VLAN_FILT_ENTRIES_N_SHFT_V2                                                              0x0

#define HWIO_ECPRI_UDP_FH_QUDP_STAT_COUNTERS_CTL_ADDR_V2                                                                (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2      + 0x0000051c)
#define HWIO_ECPRI_UDP_FH_QUDP_STAT_COUNTERS_CTL_PHYS_V2                                                                (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2_V2 + 0x0000051c)
#define HWIO_ECPRI_UDP_FH_QUDP_STAT_COUNTERS_CTL_OFFS_V2                                                                (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2_V2 + 0x0000051c)
#define HWIO_ECPRI_UDP_FH_QUDP_STAT_COUNTERS_CTL_RMSK_V2                                                                       0x3
#define HWIO_ECPRI_UDP_FH_QUDP_STAT_COUNTERS_CTL_ATTR_V2                                                                       0x3
#define HWIO_ECPRI_UDP_FH_QUDP_STAT_COUNTERS_CTL_IN_V2          \
        in_dword_masked(HWIO_ECPRI_UDP_FH_QUDP_STAT_COUNTERS_CTL_ADDR_V2, HWIO_ECPRI_UDP_FH_QUDP_STAT_COUNTERS_CTL_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_QUDP_STAT_COUNTERS_CTL_INM_V2(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_FH_QUDP_STAT_COUNTERS_CTL_ADDR_V2, m)
#define HWIO_ECPRI_UDP_FH_QUDP_STAT_COUNTERS_CTL_OUT_V2(v)      \
        out_dword(HWIO_ECPRI_UDP_FH_QUDP_STAT_COUNTERS_CTL_ADDR_V2,v)
#define HWIO_ECPRI_UDP_FH_QUDP_STAT_COUNTERS_CTL_OUTM_V2(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_QUDP_STAT_COUNTERS_CTL_ADDR_V2,m,v,HWIO_ECPRI_UDP_FH_QUDP_STAT_COUNTERS_CTL_IN_V2)
#define HWIO_ECPRI_UDP_FH_QUDP_STAT_COUNTERS_CTL_CNT_CLR_EN_BMSK_V2                                                            0x2
#define HWIO_ECPRI_UDP_FH_QUDP_STAT_COUNTERS_CTL_CNT_CLR_EN_SHFT_V2                                                            0x1
#define HWIO_ECPRI_UDP_FH_QUDP_STAT_COUNTERS_CTL_CNT_EN_BMSK_V2                                                                0x1
#define HWIO_ECPRI_UDP_FH_QUDP_STAT_COUNTERS_CTL_CNT_EN_SHFT_V2                                                                0x0

#define HWIO_ECPRI_UDP_FH_QUDP_CTL_PORT_p_ADDR_V2(p)                                                                    (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2      + 0x00000520 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_QUDP_CTL_PORT_p_PHYS_V2(p)                                                                    (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2_V2 + 0x00000520 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_QUDP_CTL_PORT_p_OFFS_V2(p)                                                                    (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2_V2 + 0x00000520 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_QUDP_CTL_PORT_p_RMSK_V2                                                                              0x7
#define HWIO_ECPRI_UDP_FH_QUDP_CTL_PORT_p_MAXp_V2                                                                                2
#define HWIO_ECPRI_UDP_FH_QUDP_CTL_PORT_p_ATTR_V2                                                                              0x3
#define HWIO_ECPRI_UDP_FH_QUDP_CTL_PORT_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_QUDP_CTL_PORT_p_ADDR_V2(p), HWIO_ECPRI_UDP_FH_QUDP_CTL_PORT_p_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_QUDP_CTL_PORT_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_QUDP_CTL_PORT_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_FH_QUDP_CTL_PORT_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_QUDP_CTL_PORT_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_FH_QUDP_CTL_PORT_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_QUDP_CTL_PORT_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_FH_QUDP_CTL_PORT_p_INI_V2(p))
#define HWIO_ECPRI_UDP_FH_QUDP_CTL_PORT_p_DISABLE_IRQ_DELAY_BMSK_V2                                                            0x4
#define HWIO_ECPRI_UDP_FH_QUDP_CTL_PORT_p_DISABLE_IRQ_DELAY_SHFT_V2                                                            0x2
#define HWIO_ECPRI_UDP_FH_QUDP_CTL_PORT_p_SLEEP_MODE_BMSK_V2                                                                   0x2
#define HWIO_ECPRI_UDP_FH_QUDP_CTL_PORT_p_SLEEP_MODE_SHFT_V2                                                                   0x1
#define HWIO_ECPRI_UDP_FH_QUDP_CTL_PORT_p_SRES_BMSK_V2                                                                         0x1
#define HWIO_ECPRI_UDP_FH_QUDP_CTL_PORT_p_SRES_SHFT_V2                                                                         0x0

#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_ADDR_V2(p,n)                                              (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x0000052c + 0x4 * (n) + 0x10 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_PHYS_V2(p,n)                                              (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x0000052c + 0x4 * (n) + 0x10 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_OFFS_V2(p,n)                                              (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x0000052c + 0x4 * (n) + 0x10 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_RMSK_V2                                                    0x3ffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_MAXp_V2                                                            2
#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_MAXn_V2                                                            3
#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_ATTR_V2                                                          0x1
#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_CMD_FIFO_BMSK_V2                                           0x3ff0000
#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_CMD_FIFO_SHFT_V2                                                0x10
#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_PTP_TIMESTAMP_FIFO_BMSK_V2                                    0xe000
#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_PTP_TIMESTAMP_FIFO_SHFT_V2                                       0xd
#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_PKT_HANDLER_SYNC_FIFOS_BMSK_V2                                0x1c00
#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_PKT_HANDLER_SYNC_FIFOS_SHFT_V2                                   0xa
#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_PKT_FIFO_BMSK_V2                                               0x3ff
#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_PKT_FIFO_SHFT_V2                                                 0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_0_PORT_p_ADDR_V2(p)                                                      (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x0000055c + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_0_PORT_p_PHYS_V2(p)                                                      (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x0000055c + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_0_PORT_p_OFFS_V2(p)                                                      (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x0000055c + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_0_PORT_p_RMSK_V2                                                          0x1ffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_0_PORT_p_MAXp_V2                                                                  2
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_0_PORT_p_ATTR_V2                                                                0x1
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_0_PORT_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_0_PORT_p_ADDR_V2(p), HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_0_PORT_p_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_0_PORT_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_0_PORT_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_0_PORT_p_ALIGNER_OUTPUT_FIFO_BMSK_V2                                      0x1c00000
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_0_PORT_p_ALIGNER_OUTPUT_FIFO_SHFT_V2                                           0x16
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_0_PORT_p_HDRI_OUTPUT_FIFO_BMSK_V2                                          0x380000
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_0_PORT_p_HDRI_OUTPUT_FIFO_SHFT_V2                                              0x13
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_0_PORT_p_HDRI_CFG_IN_V2DEX_FIFO_BMSK_V2                                        0x7fc00
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_0_PORT_p_HDRI_CFG_IN_V2DEX_FIFO_SHFT_V2                                            0xa
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_0_PORT_p_PKT_FIFO_BMSK_V2                                                     0x3ff
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_0_PORT_p_PKT_FIFO_SHFT_V2                                                       0x0

#define HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_ADDR_V2                                                                    (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x00000568)
#define HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_PHYS_V2                                                                    (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x00000568)
#define HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_OFFS_V2                                                                    (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x00000568)
#define HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_RMSK_V2                                                                          0x3f
#define HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_ATTR_V2                                                                           0x3
#define HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_IN_V2          \
        in_dword_masked(HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_ADDR_V2, HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_IN_V2M(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_ADDR_V2, m)
#define HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_OUT_V2(v)      \
        out_dword(HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_ADDR_V2,v)
#define HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_OUTM_V2(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_ADDR_V2,m,v,HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_IN_V2)
#define HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_HW_EVENTS_EN_BMSK_V2                                                             0x20
#define HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_HW_EVENTS_EN_SHFT_V2                                                              0x5
#define HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_TESTBUS_EN_BMSK_V2                                                               0x10
#define HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_TESTBUS_EN_SHFT_V2                                                                0x4
#define HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_EN_CLEAR_WATERMARK_ON_READ_BMSK_V2                                                0x8
#define HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_EN_CLEAR_WATERMARK_ON_READ_SHFT_V2                                                0x3
#define HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_WATERMARK_EN_BMSK_V2                                                              0x4
#define HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_WATERMARK_EN_SHFT_V2                                                              0x2
#define HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_TPDM_OPERATION_MODE_BMSK_V2                                                       0x2
#define HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_TPDM_OPERATION_MODE_SHFT_V2                                                       0x1
#define HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_TPDM_OPERATION_MODE_DATA_MODE_FVAL                                             0x0
#define HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_TPDM_OPERATION_MODE_CONTROL_MODE_FVAL                                          0x1
#define HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_TPDM_EN_BMSK_V2                                                                   0x1
#define HWIO_ECPRI_UDP_FH_DEBUG_FEATURES_CFG_TPDM_EN_SHFT_V2                                                                   0x0

#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_ADDR_V2                                                                         (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x0000056c)
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_PHYS_V2                                                                         (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x0000056c)
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_OFFS_V2                                                                         (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x0000056c)
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_RMSK_V2                                                                          0x7fe7fff
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_ATTR_V2                                                                                0x3
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_IN_V2          \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_ADDR_V2, HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_IN_V2M(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_ADDR_V2, m)
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_OUT_V2(v)      \
        out_dword(HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_ADDR_V2,v)
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_OUTM_V2(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_ADDR_V2,m,v,HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_IN_V2)
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_SAMPLE_ONLY_TRAPPED_PACKETS_BMSK_V2                                              0x4000000
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_SAMPLE_ONLY_TRAPPED_PACKETS_SHFT_V2                                                   0x1a
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_MAX_WORDS_TO_SEND_PER_PACKET_BMSK_V2                                             0x3fe0000
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_MAX_WORDS_TO_SEND_PER_PACKET_SHFT_V2                                                  0x11
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_SAMPLING_MODE_BMSK_V2                                                               0x6000
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_SAMPLING_MODE_SHFT_V2                                                                  0xd
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_SAMPLING_MODE_NUM_WORDS_FROM_SOP_FVAL                                               0x0
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_SAMPLING_MODE_SOP_ONLY_FVAL                                                         0x1
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_SAMPLING_MODE_EOP_ONLY_FVAL                                                         0x2
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_SAMPLING_MODE_SOP_AND_EOP_ONLY_FVAL                                                 0x3
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_SIDEBAND_INSERTION_OFFSET_BMSK_V2                                                   0x1c00
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_SIDEBAND_INSERTION_OFFSET_SHFT_V2                                                      0xa
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_SIDEBAND_INSERTION_MODE_BMSK_V2                                                      0x300
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_SIDEBAND_INSERTION_MODE_SHFT_V2                                                        0x8
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_SIDEBAND_INSERTION_MODE_INSERT_ALWAYS_FVAL                                          0x0
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_SIDEBAND_INSERTION_MODE_INSERT_ONLY_AT_SOP_FVAL                                     0x1
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_SIDEBAND_INSERTION_MODE_INSERT_ONLY_AT_EOP_FVAL                                     0x2
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_SIDEBAND_INSERTION_MODE_INSERT_AT_EOP_AND_SOP_FVAL                                  0x3
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_SIDEBAND_INSERTION_EN_BMSK_V2                                                         0x80
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_SIDEBAND_INSERTION_EN_SHFT_V2                                                          0x7
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_BUS_SEL_BMSK_V2                                                                       0x70
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_BUS_SEL_SHFT_V2                                                                        0x4
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_BUS_SEL_INGRESS_SEC2UDP_FVAL                                                        0x0
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_BUS_SEL_INGRESS_UDP2XBAR_FVAL                                                       0x1
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_BUS_SEL_EGRESS_XBAR2UDP_FVAL                                                        0x2
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_BUS_SEL_EGRESS_UDP2SEC_FVAL                                                         0x3
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_BUS_SEL_EGRESS_HDRI_OUTPUT_FVAL                                                     0x4
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_BUS_SEL_EGRESS_CS_UPDATE_OUTPUT_FVAL                                                0x5
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_LINK_INDEX_SEL_BMSK_V2                                                                 0xc
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_LINK_INDEX_SEL_SHFT_V2                                                                 0x2
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_PORT_INDEX_SEL_BMSK_V2                                                                 0x3
#define HWIO_ECPRI_UDP_FH_TPDM_DATA_CFG_PORT_INDEX_SEL_SHFT_V2                                                                 0x0

#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_ADDR                                                                    (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x00000570)
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_PHYS                                                                    (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x00000570)
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_OFFS                                                                    (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x00000570)
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_RMSK_V2                                                                     0xfffffff
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_ATTR_V2                                                                           0x3
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_IN          \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_ADDR, HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_INM(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_ADDR, m)
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_OUT_V2(v)      \
        out_dword(HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_ADDR,v)
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_OUTM_V2(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_ADDR,m,v,HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_IN)
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_ARBITRARY_TESTBUS_2_SEL_BMSK_V2                                             0xfe00000
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_ARBITRARY_TESTBUS_2_SEL_SHFT_V2                                                  0x15
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_ARBITRARY_TESTBUS_1_SEL_BMSK_V2                                              0x1fc000
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_ARBITRARY_TESTBUS_1_SEL_SHFT_V2                                                   0xe
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_ARBITRARY_TESTBUS_0_SEL_BMSK_V2                                                0x3f80
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_ARBITRARY_TESTBUS_0_SEL_SHFT_V2                                                   0x7
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_BUS_SEL_BMSK_V2                                                                  0x70
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_BUS_SEL_SHFT_V2                                                                   0x4
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_BUS_SEL_INGRESS_PKT_HANDLER_FVAL                                               0x0
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_BUS_SEL_INGRESS_PKT_HANDLER_WHITELISTS_FVAL                                    0x1
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_BUS_SEL_INGRESS_PORT_TOP_FVAL                                                  0x2
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_BUS_SEL_EGRESS_HDRI_FVAL                                                       0x3
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_BUS_SEL_EGRESS_PORT_TOP_FVAL                                                   0x4
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_BUS_SEL_ARBITRARY_TESTBUSES_FVAL                                               0x5
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_LINK_INDEX_SEL_BMSK_V2                                                            0xc
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_LINK_INDEX_SEL_SHFT_V2                                                            0x2
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_PORT_INDEX_SEL_BMSK_V2                                                            0x3
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_0_PORT_INDEX_SEL_SHFT_V2                                                            0x0

#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_1_ADDR                                                                    (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2      + 0x00000574)
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_1_PHYS                                                                    (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2_V2 + 0x00000574)
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_1_OFFS                                                                    (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2_V2 + 0x00000574)
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_1_RMSK_V2                                                                     0xfffffff
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_1_ATTR_V2                                                                           0x3
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_1_IN          \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_1_ADDR, HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_1_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_1_INM(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_1_ADDR, m)
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_1_OUT_V2(v)      \
        out_dword(HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_1_ADDR,v)
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_1_OUTM_V2(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_1_ADDR,m,v,HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_1_IN)
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_1_ARBITRARY_TESTBUS_6_SEL_BMSK_V2                                             0xfe00000
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_1_ARBITRARY_TESTBUS_6_SEL_SHFT_V2                                                  0x15
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_1_ARBITRARY_TESTBUS_5_SEL_BMSK_V2                                              0x1fc000
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_1_ARBITRARY_TESTBUS_5_SEL_SHFT_V2                                                   0xe
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_1_ARBITRARY_TESTBUS_4_SEL_BMSK_V2                                                0x3f80
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_1_ARBITRARY_TESTBUS_4_SEL_SHFT_V2                                                   0x7
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_1_ARBITRARY_TESTBUS_3_SEL_BMSK_V2                                                  0x7f
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_CFG_1_ARBITRARY_TESTBUS_3_SEL_SHFT_V2                                                   0x0

#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_MASK_n_ADDR_V2(n)                                                                (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2      + 0x00000578 + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_MASK_n_PHYS_V2(n)                                                                (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2_V2 + 0x00000578 + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_MASK_n_OFFS_V2(n)                                                                (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2_V2 + 0x00000578 + 0x4 * (n))
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_MASK_n_RMSK_V2                                                                   0xffffffff
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_MASK_n_MAXn_V2                                                                            6
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_MASK_n_ATTR_V2                                                                          0x3
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_MASK_n_INI_V2(n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TPDM_CONTROL_MASK_n_ADDR_V2(n), HWIO_ECPRI_UDP_FH_TPDM_CONTROL_MASK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_MASK_n_INMI_V2(n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TPDM_CONTROL_MASK_n_ADDR_V2(n), mask)
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_MASK_n_OUTI_V2(n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_TPDM_CONTROL_MASK_n_ADDR_V2(n),val)
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_MASK_n_OUTMI_V2(n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_TPDM_CONTROL_MASK_n_ADDR_V2(n),mask,val,HWIO_ECPRI_UDP_FH_TPDM_CONTROL_MASK_n_INI_V2(n))
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_MASK_n_MASK_BITS_BMSK_V2                                                         0xffffffff
#define HWIO_ECPRI_UDP_FH_TPDM_CONTROL_MASK_n_MASK_BITS_SHFT_V2                                                                0x0

#define HWIO_ECPRI_UDP_FH_TESTBUS_SEL_CFG_ADDR_V2                                                                       (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2      + 0x00000594)
#define HWIO_ECPRI_UDP_FH_TESTBUS_SEL_CFG_PHYS_V2                                                                       (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2_V2 + 0x00000594)
#define HWIO_ECPRI_UDP_FH_TESTBUS_SEL_CFG_OFFS_V2                                                                       (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2_V2 + 0x00000594)
#define HWIO_ECPRI_UDP_FH_TESTBUS_SEL_CFG_RMSK_V2                                                                            0x7ff
#define HWIO_ECPRI_UDP_FH_TESTBUS_SEL_CFG_ATTR_V2                                                                              0x3
#define HWIO_ECPRI_UDP_FH_TESTBUS_SEL_CFG_IN_V2          \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TESTBUS_SEL_CFG_ADDR_V2, HWIO_ECPRI_UDP_FH_TESTBUS_SEL_CFG_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_TESTBUS_SEL_CFG_IN_V2M(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TESTBUS_SEL_CFG_ADDR_V2, m)
#define HWIO_ECPRI_UDP_FH_TESTBUS_SEL_CFG_OUT_V2(v)      \
        out_dword(HWIO_ECPRI_UDP_FH_TESTBUS_SEL_CFG_ADDR_V2,v)
#define HWIO_ECPRI_UDP_FH_TESTBUS_SEL_CFG_OUTM_V2(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_TESTBUS_SEL_CFG_ADDR_V2,m,v,HWIO_ECPRI_UDP_FH_TESTBUS_SEL_CFG_IN_V2)
#define HWIO_ECPRI_UDP_FH_TESTBUS_SEL_CFG_TESTBUS_SEL_BMSK_V2                                                                0x7f0
#define HWIO_ECPRI_UDP_FH_TESTBUS_SEL_CFG_TESTBUS_SEL_SHFT_V2                                                                  0x4
#define HWIO_ECPRI_UDP_FH_TESTBUS_SEL_CFG_LINK_INDEX_SEL_BMSK_V2                                                               0xc
#define HWIO_ECPRI_UDP_FH_TESTBUS_SEL_CFG_LINK_INDEX_SEL_SHFT_V2                                                               0x2
#define HWIO_ECPRI_UDP_FH_TESTBUS_SEL_CFG_PORT_INDEX_SEL_BMSK_V2                                                               0x3
#define HWIO_ECPRI_UDP_FH_TESTBUS_SEL_CFG_PORT_INDEX_SEL_SHFT_V2                                                               0x0

#define HWIO_ECPRI_UDP_FH_TESTBUS_ADDR_V2                                                                               (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2      + 0x00000598)
#define HWIO_ECPRI_UDP_FH_TESTBUS_PHYS_V2                                                                               (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2_V2 + 0x00000598)
#define HWIO_ECPRI_UDP_FH_TESTBUS_OFFS_V2                                                                               (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2_V2 + 0x00000598)
#define HWIO_ECPRI_UDP_FH_TESTBUS_RMSK_V2                                                                               0xffffffff
#define HWIO_ECPRI_UDP_FH_TESTBUS_ATTR_V2                                                                                      0x1
#define HWIO_ECPRI_UDP_FH_TESTBUS_IN_V2          \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TESTBUS_ADDR_V2, HWIO_ECPRI_UDP_FH_TESTBUS_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_TESTBUS_INM_V2(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_FH_TESTBUS_ADDR_V2, m)
#define HWIO_ECPRI_UDP_FH_TESTBUS_DATA_BMSK_V2                                                                          0xffffffff
#define HWIO_ECPRI_UDP_FH_TESTBUS_DATA_SHFT_V2                                                                                 0x0

#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_MISC_p_ADDR_V2(p)                                                              (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2      + 0x0000059c + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_MISC_p_PHYS_V2(p)                                                              (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2_V2 + 0x0000059c + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_MISC_p_OFFS_V2(p)                                                              (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2_V2 + 0x0000059c + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_MISC_p_RMSK_V2                                                                    0x7ffff
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_MISC_p_MAXp_V2                                                                          2
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_MISC_p_ATTR_V2                                                                        0x3
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_MISC_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_MISC_p_ADDR_V2(p), HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_MISC_p_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_MISC_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_MISC_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_MISC_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_MISC_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_MISC_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_MISC_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_MISC_p_INI_V2(p))
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_MISC_p_ERRO_INFO_BMSK_V2                                                          0x7f800
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_MISC_p_ERRO_INFO_SHFT_V2                                                              0xb
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_MISC_p_LINK_ID_BMSK_V2                                                              0x600
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_MISC_p_LINK_ID_SHFT_V2                                                                0x9
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_MISC_p_NUM_VALID_BYTES_BMSK_V2                                                      0x1fc
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_MISC_p_NUM_VALID_BYTES_SHFT_V2                                                        0x2
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_MISC_p_EN_BMSK_V2                                                                     0x2
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_MISC_p_EN_SHFT_V2                                                                     0x1
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_MISC_p_CLR_BMSK_V2                                                                    0x1
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_MISC_p_CLR_SHFT_V2                                                                    0x0

#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_ADDR_V2(p,n)                                                (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x000005a8 + 0x4 * (n) + 0x54 * (p))
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_PHYS_V2(p,n)                                                (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x000005a8 + 0x4 * (n) + 0x54 * (p))
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_OFFS_V2(p,n)                                                (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x000005a8 + 0x4 * (n) + 0x54 * (p))
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_RMSK_V2                                                     0xffffffff
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_MAXp_V2                                                              2
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_MAXn_V2                                                             20
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_ATTR_V2                                                            0x1
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_VALUE_BMSK_V2                                               0xffffffff
#define HWIO_ECPRI_UDP_FH_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_VALUE_SHFT_V2                                                      0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_1_PORT_p_ADDR_V2(p)                                                      (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x000006a4 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_1_PORT_p_PHYS_V2(p)                                                      (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x000006a4 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_1_PORT_p_OFFS_V2(p)                                                      (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x000006a4 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_1_PORT_p_RMSK_V2                                                              0x7ff
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_1_PORT_p_MAXp_V2                                                                  2
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_1_PORT_p_ATTR_V2                                                                0x1
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_1_PORT_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_1_PORT_p_ADDR_V2(p), HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_1_PORT_p_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_1_PORT_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_1_PORT_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_1_PORT_p_CS_UPDATE_FIFO_BMSK_V2                                               0x600
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_1_PORT_p_CS_UPDATE_FIFO_SHFT_V2                                                 0x9
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_1_PORT_p_CS_CALC_FIFO_BMSK_V2                                                 0x1ff
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_1_PORT_p_CS_CALC_FIFO_SHFT_V2                                                   0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_IPV4_FIELDS_p_ADDR_V2(p)                                                               (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x00000800 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IPV4_FIELDS_p_PHYS_V2(p)                                                               (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x00000800 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IPV4_FIELDS_p_OFFS_V2(p)                                                               (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x00000800 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IPV4_FIELDS_p_RMSK_V2                                                                    0xffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_IPV4_FIELDS_p_MAXp_V2                                                                           2
#define HWIO_ECPRI_UDP_FH_EGRESS_IPV4_FIELDS_p_ATTR_V2                                                                         0x3
#define HWIO_ECPRI_UDP_FH_EGRESS_IPV4_FIELDS_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_IPV4_FIELDS_p_ADDR_V2(p), HWIO_ECPRI_UDP_FH_EGRESS_IPV4_FIELDS_p_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_IPV4_FIELDS_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_IPV4_FIELDS_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_IPV4_FIELDS_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_EGRESS_IPV4_FIELDS_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_FH_EGRESS_IPV4_FIELDS_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_EGRESS_IPV4_FIELDS_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_FH_EGRESS_IPV4_FIELDS_p_INI_V2(p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IPV4_FIELDS_p_TTL_BMSK_V2                                                                0xff0000
#define HWIO_ECPRI_UDP_FH_EGRESS_IPV4_FIELDS_p_TTL_SHFT_V2                                                                    0x10
#define HWIO_ECPRI_UDP_FH_EGRESS_IPV4_FIELDS_p_ID_BMSK_V2                                                                   0xffff
#define HWIO_ECPRI_UDP_FH_EGRESS_IPV4_FIELDS_p_ID_SHFT_V2                                                                      0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_IPV6_FIELDS_p_ADDR_V2(p)                                                               (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x0000080c + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IPV6_FIELDS_p_PHYS_V2(p)                                                               (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x0000080c + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IPV6_FIELDS_p_OFFS_V2(p)                                                               (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x0000080c + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IPV6_FIELDS_p_RMSK_V2                                                                   0xfffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_IPV6_FIELDS_p_MAXp_V2                                                                           2
#define HWIO_ECPRI_UDP_FH_EGRESS_IPV6_FIELDS_p_ATTR_V2                                                                         0x3
#define HWIO_ECPRI_UDP_FH_EGRESS_IPV6_FIELDS_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_IPV6_FIELDS_p_ADDR_V2(p), HWIO_ECPRI_UDP_FH_EGRESS_IPV6_FIELDS_p_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_IPV6_FIELDS_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_IPV6_FIELDS_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_IPV6_FIELDS_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_EGRESS_IPV6_FIELDS_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_FH_EGRESS_IPV6_FIELDS_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_EGRESS_IPV6_FIELDS_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_FH_EGRESS_IPV6_FIELDS_p_INI_V2(p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IPV6_FIELDS_p_FLOW_LABEL_BMSK_V2                                                        0xfffff00
#define HWIO_ECPRI_UDP_FH_EGRESS_IPV6_FIELDS_p_FLOW_LABEL_SHFT_V2                                                              0x8
#define HWIO_ECPRI_UDP_FH_EGRESS_IPV6_FIELDS_p_HOP_LIMIT_BMSK_V2                                                              0xff
#define HWIO_ECPRI_UDP_FH_EGRESS_IPV6_FIELDS_p_HOP_LIMIT_SHFT_V2                                                               0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_ETHERTYPE_p_ADDR_V2(p)                                                          (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x00000818 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_ETHERTYPE_p_PHYS_V2(p)                                                          (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x00000818 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_ETHERTYPE_p_OFFS_V2(p)                                                          (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x00000818 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_ETHERTYPE_p_RMSK_V2                                                                 0xffff
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_ETHERTYPE_p_MAXp_V2                                                                      2
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_ETHERTYPE_p_ATTR_V2                                                                    0x3
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_ETHERTYPE_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_ETHERTYPE_p_ADDR_V2(p), HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_ETHERTYPE_p_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_ETHERTYPE_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_ETHERTYPE_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_ETHERTYPE_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_ETHERTYPE_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_ETHERTYPE_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_ETHERTYPE_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_ETHERTYPE_p_INI_V2(p))
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_ETHERTYPE_p_VALUE_BMSK_V2                                                           0xffff
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_ETHERTYPE_p_VALUE_SHFT_V2                                                              0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_ADDR_V2(p)                                                   (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x00000824 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_PHYS_V2(p)                                                   (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x00000824 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_OFFS_V2(p)                                                   (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x00000824 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_RMSK_V2                                                          0xffff
#define HWIO_ECPRI_UDP_FH_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_MAXp_V2                                                               2
#define HWIO_ECPRI_UDP_FH_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_ATTR_V2                                                             0x3
#define HWIO_ECPRI_UDP_FH_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_ADDR_V2(p), HWIO_ECPRI_UDP_FH_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_FH_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_FH_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_INI_V2(p))
#define HWIO_ECPRI_UDP_FH_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_REDIRECT_TO_BMSK_V2                                              0xff00
#define HWIO_ECPRI_UDP_FH_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_REDIRECT_TO_SHFT_V2                                                 0x8
#define HWIO_ECPRI_UDP_FH_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_REDIRECT_FROM_BMSK_V2                                              0xff
#define HWIO_ECPRI_UDP_FH_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_REDIRECT_FROM_SHFT_V2                                               0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_ADDR_V2(p)                                                   (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x00000830 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_PHYS_V2(p)                                                   (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x00000830 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_OFFS_V2(p)                                                   (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x00000830 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_RMSK_V2                                                          0xffff
#define HWIO_ECPRI_UDP_FH_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_MAXp_V2                                                               2
#define HWIO_ECPRI_UDP_FH_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_ATTR_V2                                                             0x3
#define HWIO_ECPRI_UDP_FH_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_ADDR_V2(p), HWIO_ECPRI_UDP_FH_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_FH_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_FH_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_INI_V2(p))
#define HWIO_ECPRI_UDP_FH_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_REDIRECT_TO_BMSK_V2                                              0xff00
#define HWIO_ECPRI_UDP_FH_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_REDIRECT_TO_SHFT_V2                                                 0x8
#define HWIO_ECPRI_UDP_FH_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_REDIRECT_FROM_BMSK_V2                                              0xff
#define HWIO_ECPRI_UDP_FH_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_REDIRECT_FROM_SHFT_V2                                               0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_MTU_p_ADDR_V2(p)                                                                   (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x0000083c + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_MTU_p_PHYS_V2(p)                                                                   (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x0000083c + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_MTU_p_OFFS_V2(p)                                                                   (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x0000083c + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_MTU_p_RMSK_V2                                                                          0x3fff
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_MTU_p_MAXp_V2                                                                               2
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_MTU_p_ATTR_V2                                                                             0x3
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_MTU_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_ETH_MTU_p_ADDR_V2(p), HWIO_ECPRI_UDP_FH_EGRESS_ETH_MTU_p_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_MTU_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_ETH_MTU_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_MTU_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_EGRESS_ETH_MTU_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_MTU_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_EGRESS_ETH_MTU_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_FH_EGRESS_ETH_MTU_p_INI_V2(p))
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_MTU_p_VALUE_BMSK_V2                                                                    0x3fff
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_MTU_p_VALUE_SHFT_V2                                                                       0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_ADDR_V2(p)                                                                    (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x00000860 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_PHYS_V2(p)                                                                    (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x00000860 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_OFFS_V2(p)                                                                    (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x00000860 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_RMSK_V2                                                                           0x7fff
#define HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_MAXp_V2                                                                                2
#define HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_ATTR_V2                                                                              0x3
#define HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_ADDR_V2(p), HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_INI_V2(p))
#define HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_DISABLE_PTP_DETECTION_BMSK_V2                                                     0x4000
#define HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_DISABLE_PTP_DETECTION_SHFT_V2                                                        0xe
#define HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_L3_ENCAP_INDEX_OVERRIDE_EN_BMSK_V2                                                0x2000
#define HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_L3_ENCAP_INDEX_OVERRIDE_EN_SHFT_V2                                                   0xd
#define HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_L2_ENCAP_INDEX_OVERRIDE_EN_BMSK_V2                                                0x1000
#define HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_L2_ENCAP_INDEX_OVERRIDE_EN_SHFT_V2                                                   0xc
#define HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_DISABLE_PADDING_REMOVAL_BMSK_V2                                                    0x800
#define HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_DISABLE_PADDING_REMOVAL_SHFT_V2                                                      0xb
#define HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_BYPASSED_PACKETS_VPORT_BMSK_V2                                                     0x7f8
#define HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_BYPASSED_PACKETS_VPORT_SHFT_V2                                                       0x3
#define HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_BYPASSED_PACKETS_VPORT_ACTION_BMSK_V2                                                0x6
#define HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_BYPASSED_PACKETS_VPORT_ACTION_SHFT_V2                                                0x1
#define HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_CALC_IP_UDP_LEN_FROM_BYTE_COUNT_BMSK_V2                                              0x1
#define HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_CALC_IP_UDP_LEN_FROM_BYTE_COUNT_SHFT_V2                                              0x0

#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_ADDR_V2(p)                                                         (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x00000900 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_PHYS_V2(p)                                                         (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x00000900 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_OFFS_V2(p)                                                         (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x00000900 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_RMSK_V2                                                            0x7fff7fff
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_MAXp_V2                                                                     2
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_ATTR_V2                                                                   0x1
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_ADDR_V2(p), HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_1_BMSK_V2             0x40000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_1_SHFT_V2                   0x1e
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_1_BMSK_V2          0x20000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_1_SHFT_V2                0x1d
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_1_BMSK_V2                                 0x10000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_1_SHFT_V2                                       0x1c
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_1_BMSK_V2                                  0x8000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_1_SHFT_V2                                       0x1b
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_1_BMSK_V2                                  0x4000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_1_SHFT_V2                                       0x1a
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_1_BMSK_V2                                  0x2000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_1_SHFT_V2                                       0x19
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_1_BMSK_V2                            0x1000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_1_SHFT_V2                                 0x18
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_1_BMSK_V2                                0x800000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_1_SHFT_V2                                    0x17
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_1_BMSK_V2                          0x400000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_1_SHFT_V2                              0x16
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_1_BMSK_V2                            0x200000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_1_SHFT_V2                                0x15
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_1_BMSK_V2                                  0x100000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_1_SHFT_V2                                      0x14
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_1_BMSK_V2                                  0x80000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_1_SHFT_V2                                     0x13
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_1_BMSK_V2                      0x40000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_1_SHFT_V2                         0x12
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_1_BMSK_V2                                 0x20000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_1_SHFT_V2                                    0x11
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_1_BMSK_V2                                  0x10000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_1_SHFT_V2                                     0x10
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_0_BMSK_V2                 0x4000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_0_SHFT_V2                    0xe
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_0_BMSK_V2              0x2000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_0_SHFT_V2                 0xd
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_0_BMSK_V2                                     0x1000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_0_SHFT_V2                                        0xc
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_0_BMSK_V2                                      0x800
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_0_SHFT_V2                                        0xb
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_0_BMSK_V2                                      0x400
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_0_SHFT_V2                                        0xa
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_0_BMSK_V2                                      0x200
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_0_SHFT_V2                                        0x9
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_0_BMSK_V2                                0x100
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_0_SHFT_V2                                  0x8
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_0_BMSK_V2                                    0x80
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_0_SHFT_V2                                     0x7
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_0_BMSK_V2                              0x40
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_0_SHFT_V2                               0x6
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_0_BMSK_V2                                0x20
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_0_SHFT_V2                                 0x5
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_0_BMSK_V2                                      0x10
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_0_SHFT_V2                                       0x4
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_0_BMSK_V2                                      0x8
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_0_SHFT_V2                                      0x3
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_0_BMSK_V2                          0x4
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_0_SHFT_V2                          0x2
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_0_BMSK_V2                                     0x2
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_0_SHFT_V2                                     0x1
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_0_BMSK_V2                                      0x1
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_0_SHFT_V2                                      0x0

#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_ADDR_V2(p)                                                         (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x0000090c + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_PHYS_V2(p)                                                         (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x0000090c + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_OFFS_V2(p)                                                         (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x0000090c + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_RMSK_V2                                                            0x7fff7fff
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_MAXp_V2                                                                     2
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_ATTR_V2                                                                   0x1
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_ADDR_V2(p), HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_3_BMSK_V2             0x40000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_3_SHFT_V2                   0x1e
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_3_BMSK_V2          0x20000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_3_SHFT_V2                0x1d
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_3_LINK_3_BMSK_V2                                 0x10000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_3_LINK_3_SHFT_V2                                       0x1c
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_2_LINK_3_BMSK_V2                                  0x8000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_2_LINK_3_SHFT_V2                                       0x1b
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_1_LINK_3_BMSK_V2                                  0x4000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_1_LINK_3_SHFT_V2                                       0x1a
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_0_LINK_3_BMSK_V2                                  0x2000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_0_LINK_3_SHFT_V2                                       0x19
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_3_BMSK_V2                            0x1000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_3_SHFT_V2                                 0x18
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_3_BMSK_V2                                0x800000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_3_SHFT_V2                                    0x17
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_3_BMSK_V2                          0x400000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_3_SHFT_V2                              0x16
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_3_BMSK_V2                            0x200000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_3_SHFT_V2                                0x15
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_UDP_CS_ERROR_LINK_3_BMSK_V2                                  0x100000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_UDP_CS_ERROR_LINK_3_SHFT_V2                                      0x14
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_3_BMSK_V2                                  0x80000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_3_SHFT_V2                                     0x13
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_3_BMSK_V2                      0x40000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_3_SHFT_V2                         0x12
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_3_BMSK_V2                                 0x20000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_3_SHFT_V2                                    0x11
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_3_BMSK_V2                                  0x10000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_3_SHFT_V2                                     0x10
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_2_BMSK_V2                 0x4000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_2_SHFT_V2                    0xe
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_2_BMSK_V2              0x2000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_2_SHFT_V2                 0xd
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_3_LINK_2_BMSK_V2                                     0x1000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_3_LINK_2_SHFT_V2                                        0xc
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_2_LINK_2_BMSK_V2                                      0x800
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_2_LINK_2_SHFT_V2                                        0xb
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_1_LINK_2_BMSK_V2                                      0x400
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_1_LINK_2_SHFT_V2                                        0xa
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_0_LINK_2_BMSK_V2                                      0x200
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_0_LINK_2_SHFT_V2                                        0x9
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_2_BMSK_V2                                0x100
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_2_SHFT_V2                                  0x8
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_2_BMSK_V2                                    0x80
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_2_SHFT_V2                                     0x7
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_2_BMSK_V2                              0x40
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_2_SHFT_V2                               0x6
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_2_BMSK_V2                                0x20
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_2_SHFT_V2                                 0x5
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_UDP_CS_ERROR_LINK_2_BMSK_V2                                      0x10
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_UDP_CS_ERROR_LINK_2_SHFT_V2                                       0x4
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_2_BMSK_V2                                      0x8
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_2_SHFT_V2                                      0x3
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_2_BMSK_V2                          0x4
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_2_SHFT_V2                          0x2
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_2_BMSK_V2                                     0x2
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_2_SHFT_V2                                     0x1
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_2_BMSK_V2                                      0x1
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_2_SHFT_V2                                      0x0

#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_ADDR_V2(p)                                                           (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x00000920 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_PHYS_V2(p)                                                           (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x00000920 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_OFFS_V2(p)                                                           (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x00000920 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_RMSK_V2                                                              0x7fff7fff
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_MAXp_V2                                                                       2
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_ATTR_V2                                                                     0x3
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_ADDR_V2(p), HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INI_V2(p))
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_1_BMSK_V2               0x40000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_1_SHFT_V2                     0x1e
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_1_BMSK_V2            0x20000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_1_SHFT_V2                  0x1d
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_1_BMSK_V2                                   0x10000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_1_SHFT_V2                                         0x1c
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_1_BMSK_V2                                    0x8000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_1_SHFT_V2                                         0x1b
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_1_BMSK_V2                                    0x4000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_1_SHFT_V2                                         0x1a
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_1_BMSK_V2                                    0x2000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_1_SHFT_V2                                         0x19
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_1_BMSK_V2                              0x1000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_1_SHFT_V2                                   0x18
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_1_BMSK_V2                                  0x800000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_1_SHFT_V2                                      0x17
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_1_BMSK_V2                            0x400000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_1_SHFT_V2                                0x16
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_1_BMSK_V2                              0x200000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_1_SHFT_V2                                  0x15
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_1_BMSK_V2                                    0x100000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_1_SHFT_V2                                        0x14
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_1_BMSK_V2                                    0x80000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_1_SHFT_V2                                       0x13
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_1_BMSK_V2                        0x40000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_1_SHFT_V2                           0x12
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_1_BMSK_V2                                   0x20000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_1_SHFT_V2                                      0x11
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_1_BMSK_V2                                    0x10000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_1_SHFT_V2                                       0x10
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_0_BMSK_V2                   0x4000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_0_SHFT_V2                      0xe
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_0_BMSK_V2                0x2000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_0_SHFT_V2                   0xd
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_0_BMSK_V2                                       0x1000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_0_SHFT_V2                                          0xc
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_0_BMSK_V2                                        0x800
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_0_SHFT_V2                                          0xb
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_0_BMSK_V2                                        0x400
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_0_SHFT_V2                                          0xa
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_0_BMSK_V2                                        0x200
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_0_SHFT_V2                                          0x9
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_0_BMSK_V2                                  0x100
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_0_SHFT_V2                                    0x8
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_0_BMSK_V2                                      0x80
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_0_SHFT_V2                                       0x7
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_0_BMSK_V2                                0x40
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_0_SHFT_V2                                 0x6
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_0_BMSK_V2                                  0x20
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_0_SHFT_V2                                   0x5
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_0_BMSK_V2                                        0x10
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_0_SHFT_V2                                         0x4
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_0_BMSK_V2                                        0x8
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_0_SHFT_V2                                        0x3
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_0_BMSK_V2                            0x4
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_0_SHFT_V2                            0x2
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_0_BMSK_V2                                       0x2
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_0_SHFT_V2                                       0x1
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_0_BMSK_V2                                        0x1
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_0_SHFT_V2                                        0x0

#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_ADDR_V2(p)                                                           (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x0000092c + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_PHYS_V2(p)                                                           (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x0000092c + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_OFFS_V2(p)                                                           (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x0000092c + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_RMSK_V2                                                              0x7fff7fff
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_MAXp_V2                                                                       2
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_ATTR_V2                                                                     0x3
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_ADDR_V2(p), HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INI_V2(p))
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_3_BMSK_V2               0x40000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_3_SHFT_V2                     0x1e
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_3_BMSK_V2            0x20000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_3_SHFT_V2                  0x1d
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_3_LINK_3_BMSK_V2                                   0x10000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_3_LINK_3_SHFT_V2                                         0x1c
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_2_LINK_3_BMSK_V2                                    0x8000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_2_LINK_3_SHFT_V2                                         0x1b
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_1_LINK_3_BMSK_V2                                    0x4000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_1_LINK_3_SHFT_V2                                         0x1a
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_0_LINK_3_BMSK_V2                                    0x2000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_0_LINK_3_SHFT_V2                                         0x19
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_3_BMSK_V2                              0x1000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_3_SHFT_V2                                   0x18
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_3_BMSK_V2                                  0x800000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_3_SHFT_V2                                      0x17
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_3_BMSK_V2                            0x400000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_3_SHFT_V2                                0x16
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_3_BMSK_V2                              0x200000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_3_SHFT_V2                                  0x15
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_UDP_CS_ERROR_LINK_3_BMSK_V2                                    0x100000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_UDP_CS_ERROR_LINK_3_SHFT_V2                                        0x14
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_3_BMSK_V2                                    0x80000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_3_SHFT_V2                                       0x13
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_3_BMSK_V2                        0x40000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_3_SHFT_V2                           0x12
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_3_BMSK_V2                                   0x20000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_3_SHFT_V2                                      0x11
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_3_BMSK_V2                                    0x10000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_3_SHFT_V2                                       0x10
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_2_BMSK_V2                   0x4000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_2_SHFT_V2                      0xe
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_2_BMSK_V2                0x2000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_2_SHFT_V2                   0xd
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_3_LINK_2_BMSK_V2                                       0x1000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_3_LINK_2_SHFT_V2                                          0xc
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_2_LINK_2_BMSK_V2                                        0x800
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_2_LINK_2_SHFT_V2                                          0xb
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_1_LINK_2_BMSK_V2                                        0x400
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_1_LINK_2_SHFT_V2                                          0xa
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_0_LINK_2_BMSK_V2                                        0x200
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_0_LINK_2_SHFT_V2                                          0x9
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_2_BMSK_V2                                  0x100
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_2_SHFT_V2                                    0x8
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_2_BMSK_V2                                      0x80
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_2_SHFT_V2                                       0x7
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_2_BMSK_V2                                0x40
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_2_SHFT_V2                                 0x6
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_2_BMSK_V2                                  0x20
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_2_SHFT_V2                                   0x5
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_UDP_CS_ERROR_LINK_2_BMSK_V2                                        0x10
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_UDP_CS_ERROR_LINK_2_SHFT_V2                                         0x4
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_2_BMSK_V2                                        0x8
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_2_SHFT_V2                                        0x3
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_2_BMSK_V2                            0x4
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_2_SHFT_V2                            0x2
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_2_BMSK_V2                                       0x2
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_2_SHFT_V2                                       0x1
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_2_BMSK_V2                                        0x1
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_2_SHFT_V2                                        0x0

#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_ADDR_V2(p)                                                            (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x00000940 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_PHYS_V2(p)                                                            (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x00000940 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_OFFS_V2(p)                                                            (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x00000940 + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_RMSK_V2                                                               0x7fff7fff
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_MAXp_V2                                                                        2
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_ATTR_V2                                                                      0x2
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_1_BMSK_V2                0x40000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_1_SHFT_V2                      0x1e
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_1_BMSK_V2             0x20000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_1_SHFT_V2                   0x1d
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_1_BMSK_V2                                    0x10000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_1_SHFT_V2                                          0x1c
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_1_BMSK_V2                                     0x8000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_1_SHFT_V2                                          0x1b
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_1_BMSK_V2                                     0x4000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_1_SHFT_V2                                          0x1a
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_1_BMSK_V2                                     0x2000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_1_SHFT_V2                                          0x19
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_1_BMSK_V2                               0x1000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_1_SHFT_V2                                    0x18
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_1_BMSK_V2                                   0x800000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_1_SHFT_V2                                       0x17
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_1_BMSK_V2                             0x400000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_1_SHFT_V2                                 0x16
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_1_BMSK_V2                               0x200000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_1_SHFT_V2                                   0x15
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_1_BMSK_V2                                     0x100000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_1_SHFT_V2                                         0x14
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_1_BMSK_V2                                     0x80000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_1_SHFT_V2                                        0x13
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_1_BMSK_V2                         0x40000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_1_SHFT_V2                            0x12
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_1_BMSK_V2                                    0x20000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_1_SHFT_V2                                       0x11
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_1_BMSK_V2                                     0x10000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_1_SHFT_V2                                        0x10
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_0_BMSK_V2                    0x4000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_0_SHFT_V2                       0xe
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_0_BMSK_V2                 0x2000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_0_SHFT_V2                    0xd
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_0_BMSK_V2                                        0x1000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_0_SHFT_V2                                           0xc
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_0_BMSK_V2                                         0x800
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_0_SHFT_V2                                           0xb
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_0_BMSK_V2                                         0x400
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_0_SHFT_V2                                           0xa
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_0_BMSK_V2                                         0x200
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_0_SHFT_V2                                           0x9
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_0_BMSK_V2                                   0x100
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_0_SHFT_V2                                     0x8
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_0_BMSK_V2                                       0x80
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_0_SHFT_V2                                        0x7
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_0_BMSK_V2                                 0x40
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_0_SHFT_V2                                  0x6
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_0_BMSK_V2                                   0x20
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_0_SHFT_V2                                    0x5
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_0_BMSK_V2                                         0x10
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_0_SHFT_V2                                          0x4
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_0_BMSK_V2                                         0x8
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_0_SHFT_V2                                         0x3
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_0_BMSK_V2                             0x4
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_0_SHFT_V2                             0x2
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_0_BMSK_V2                                        0x2
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_0_SHFT_V2                                        0x1
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_0_BMSK_V2                                         0x1
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_0_SHFT_V2                                         0x0

#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_ADDR_V2(p)                                                            (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_V2     + 0x0000094c + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_PHYS_V2(p)                                                            (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_PHYS_V2 + 0x0000094c + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_OFFS_V2(p)                                                            (ECPRI_UDP_FH_UDP_FH_REGS_REG_BASE_OFFS_V2 + 0x0000094c + 0x4 * (p))
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_RMSK_V2                                                               0x7fff7fff
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_MAXp_V2                                                                        2
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_ATTR_V2                                                                      0x2
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_3_BMSK_V2                0x40000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_3_SHFT_V2                      0x1e
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_3_BMSK_V2             0x20000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_3_SHFT_V2                   0x1d
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_3_LINK_3_BMSK_V2                                    0x10000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_3_LINK_3_SHFT_V2                                          0x1c
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_2_LINK_3_BMSK_V2                                     0x8000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_2_LINK_3_SHFT_V2                                          0x1b
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_1_LINK_3_BMSK_V2                                     0x4000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_1_LINK_3_SHFT_V2                                          0x1a
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_0_LINK_3_BMSK_V2                                     0x2000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_0_LINK_3_SHFT_V2                                          0x19
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_3_BMSK_V2                               0x1000000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_3_SHFT_V2                                    0x18
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_3_BMSK_V2                                   0x800000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_3_SHFT_V2                                       0x17
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_3_BMSK_V2                             0x400000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_3_SHFT_V2                                 0x16
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_3_BMSK_V2                               0x200000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_3_SHFT_V2                                   0x15
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_UDP_CS_ERROR_LINK_3_BMSK_V2                                     0x100000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_UDP_CS_ERROR_LINK_3_SHFT_V2                                         0x14
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_3_BMSK_V2                                     0x80000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_3_SHFT_V2                                        0x13
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_3_BMSK_V2                         0x40000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_3_SHFT_V2                            0x12
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_3_BMSK_V2                                    0x20000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_3_SHFT_V2                                       0x11
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_3_BMSK_V2                                     0x10000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_3_SHFT_V2                                        0x10
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_2_BMSK_V2                    0x4000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_2_SHFT_V2                       0xe
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_2_BMSK_V2                 0x2000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_2_SHFT_V2                    0xd
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_3_LINK_2_BMSK_V2                                        0x1000
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_3_LINK_2_SHFT_V2                                           0xc
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_2_LINK_2_BMSK_V2                                         0x800
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_2_LINK_2_SHFT_V2                                           0xb
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_1_LINK_2_BMSK_V2                                         0x400
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_1_LINK_2_SHFT_V2                                           0xa
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_0_LINK_2_BMSK_V2                                         0x200
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_0_LINK_2_SHFT_V2                                           0x9
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_2_BMSK_V2                                   0x100
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_2_SHFT_V2                                     0x8
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_2_BMSK_V2                                       0x80
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_2_SHFT_V2                                        0x7
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_2_BMSK_V2                                 0x40
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_2_SHFT_V2                                  0x6
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_2_BMSK_V2                                   0x20
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_2_SHFT_V2                                    0x5
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_UDP_CS_ERROR_LINK_2_BMSK_V2                                         0x10
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_UDP_CS_ERROR_LINK_2_SHFT_V2                                          0x4
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_2_BMSK_V2                                         0x8
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_2_SHFT_V2                                         0x3
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_2_BMSK_V2                             0x4
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_2_SHFT_V2                             0x2
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_2_BMSK_V2                                        0x2
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_2_SHFT_V2                                        0x1
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_2_BMSK_V2                                         0x1
#define HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_2_SHFT_V2                                         0x0

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_UDP_FH_UDP_FH_FILTER
 *--------------------------------------------------------------------------*/

#define ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_V2                                         (ECPRI_WRAPPER_BASE      + 0x00381000)
#define ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_PHYS_V2                                     (ECPRI_WRAPPER_BASE_PHYS + 0x00381000)
#define ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_OFFS_V2                                     0x00381000

#define HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n_ADDR_V2(p,n)                    (ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_V2     + 0x00000000 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n_PHYS_V2(p,n)                    (ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_PHYS_V2 + 0x00000000 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n_OFFS_V2(p,n)                    (ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_OFFS_V2 + 0x00000000 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n_RMSK_V2                             0xffff
#define HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n_MAXp_V2                                  2
#define HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n_MAXn_V2                                 15
#define HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n_ATTR_V2                                0x3
#define HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n_VALUE_BMSK_V2                       0xffff
#define HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n_VALUE_SHFT_V2                          0x0

#define HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_ADDR_V2(p,n)           (ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_V2     + 0x00000300 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_PHYS_V2(p,n)           (ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_PHYS_V2 + 0x00000300 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_OFFS_V2(p,n)           (ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_OFFS_V2 + 0x00000300 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_RMSK_V2                    0xffff
#define HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_MAXp_V2                         2
#define HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_MAXn_V2                        15
#define HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_ATTR_V2                       0x3
#define HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_VALUE_BMSK_V2              0xffff
#define HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_VALUE_SHFT_V2                 0x0

#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n)                 (ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_V2     + 0x00000700 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_PHYS_V2(p,n)                 (ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_PHYS_V2 + 0x00000700 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_OFFS_V2(p,n)                 (ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_OFFS_V2 + 0x00000700 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_RMSK_V2                      0xffffffff
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_MAXp_V2                               2
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_MAXn_V2                              15
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_ATTR_V2                             0x3
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_VALUE_BMSK_V2                0xffffffff
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_VALUE_SHFT_V2                       0x0

#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n)                 (ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_V2     + 0x00000a00 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_PHYS_V2(p,n)                 (ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_PHYS_V2 + 0x00000a00 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_OFFS_V2(p,n)                 (ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_OFFS_V2 + 0x00000a00 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_RMSK_V2                      0xffffffff
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_MAXp_V2                               2
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_MAXn_V2                              15
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_ATTR_V2                             0x3
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_VALUE_BMSK_V2                0xffffffff
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_VALUE_SHFT_V2                       0x0

#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n)                 (ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_V2     + 0x00000d00 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_PHYS_V2(p,n)                 (ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_PHYS_V2 + 0x00000d00 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_OFFS_V2(p,n)                 (ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_OFFS_V2 + 0x00000d00 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_RMSK_V2                      0xffffffff
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_MAXp_V2                               2
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_MAXn_V2                              15
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_ATTR_V2                             0x3
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_VALUE_BMSK_V2                0xffffffff
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_VALUE_SHFT_V2                       0x0

#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n)                 (ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_V2     + 0x00001000 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_PHYS_V2(p,n)                 (ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_PHYS_V2 + 0x00001000 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_OFFS_V2(p,n)                 (ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_OFFS_V2 + 0x00001000 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_RMSK_V2                      0xffffffff
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_MAXp_V2                               2
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_MAXn_V2                              15
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_ATTR_V2                             0x3
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_VALUE_BMSK_V2                0xffffffff
#define HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_VALUE_SHFT_V2                       0x0

#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n)              (ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_V2     + 0x00001300 + 0x4 * (n) + 0x50 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_PHYS_V2(p,n)              (ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_PHYS_V2 + 0x00001300 + 0x4 * (n) + 0x50 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_OFFS_V2(p,n)              (ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_OFFS_V2 + 0x00001300 + 0x4 * (n) + 0x50 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_RMSK_V2                   0xffffffff
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_MAXp_V2                            2
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_MAXn_V2                           19
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_ATTR_V2                          0x3
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_VALUE_BMSK_V2             0xffffffff
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_VALUE_SHFT_V2                    0x0

#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n)              (ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_V2     + 0x00001400 + 0x4 * (n) + 0x50 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_PHYS_V2(p,n)              (ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_PHYS_V2 + 0x00001400 + 0x4 * (n) + 0x50 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_OFFS_V2(p,n)              (ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_OFFS_V2 + 0x00001400 + 0x4 * (n) + 0x50 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_RMSK_V2                       0xffff
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_MAXp_V2                            2
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_MAXn_V2                           19
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_ATTR_V2                          0x3
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_VALUE_BMSK_V2                 0xffff
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_VALUE_SHFT_V2                    0x0

#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_ADDR_V2(p,n)             (ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_V2     + 0x00001500 + 0x4 * (n) + 0x50 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_PHYS_V2(p,n)             (ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_PHYS_V2 + 0x00001500 + 0x4 * (n) + 0x50 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_OFFS_V2(p,n)             (ECPRI_UDP_FH_UDP_FH_FILTER_REG_BASE_OFFS_V2 + 0x00001500 + 0x4 * (n) + 0x50 * (p))
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_RMSK_V2                      0x1fff
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_MAXp_V2                           2
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_MAXn_V2                          19
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_ATTR_V2                         0x3
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_RING_ID_BMSK_V2              0x1fe0
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_RING_ID_SHFT_V2                 0x5
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_GSI_ID_BMSK_V2                 0x18
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_GSI_ID_SHFT_V2                  0x3
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_ACTION_BMSK_V2                  0x7
#define HWIO_ECPRI_UDP_FH_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_ACTION_SHFT_V2                  0x0

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_UDP_FH_UDP_FH_RAMS
 *--------------------------------------------------------------------------*/

#define ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2                                                         (ECPRI_WRAPPER_BASE      + 0x00384000)
#define ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2                                                     (ECPRI_WRAPPER_BASE_PHYS + 0x00384000)
#define ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2                                                     0x00384000

#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                      (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x00000000 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                      (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x00000000 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                      (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x00000000 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_RMSK_V2                           0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_MAXp_V2                                    2
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_MAXn_V2                                    3
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_ATTR_V2                                  0x1
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                     0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                            0x0

#define HWIO_ECPRI_UDP_FH_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                          (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x00000004 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                          (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x00000004 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                          (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x00000004 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_RMSK_V2                               0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_MAXp_V2                                        2
#define HWIO_ECPRI_UDP_FH_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_MAXn_V2                                        3
#define HWIO_ECPRI_UDP_FH_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_ATTR_V2                                      0x1
#define HWIO_ECPRI_UDP_FH_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                         0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                                0x0

#define HWIO_ECPRI_UDP_FH_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                    (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x00000008 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                    (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x00000008 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                    (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x00000008 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_RMSK_V2                         0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_MAXp_V2                                  2
#define HWIO_ECPRI_UDP_FH_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_MAXn_V2                                  3
#define HWIO_ECPRI_UDP_FH_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_ATTR_V2                                0x1
#define HWIO_ECPRI_UDP_FH_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                   0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                          0x0

#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                     (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x0000000c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                     (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x0000000c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                     (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x0000000c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_RMSK_V2                          0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_MAXp_V2                                   2
#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_MAXn_V2                                   3
#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_ATTR_V2                                 0x1
#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                    0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                           0x0

#define HWIO_ECPRI_UDP_FH_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                      (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x00000010 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                      (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x00000010 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                      (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x00000010 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_RMSK_V2                           0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_MAXp_V2                                    2
#define HWIO_ECPRI_UDP_FH_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_MAXn_V2                                    3
#define HWIO_ECPRI_UDP_FH_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_ATTR_V2                                  0x1
#define HWIO_ECPRI_UDP_FH_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                     0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                            0x0

#define HWIO_ECPRI_UDP_FH_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                    (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x00000014 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                    (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x00000014 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                    (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x00000014 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_RMSK_V2                         0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_MAXp_V2                                  2
#define HWIO_ECPRI_UDP_FH_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_MAXn_V2                                  3
#define HWIO_ECPRI_UDP_FH_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_ATTR_V2                                0x1
#define HWIO_ECPRI_UDP_FH_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                   0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                          0x0

#define HWIO_ECPRI_UDP_FH_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                          (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x00000018 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                          (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x00000018 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                          (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x00000018 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_RMSK_V2                               0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_MAXp_V2                                        2
#define HWIO_ECPRI_UDP_FH_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_MAXn_V2                                        3
#define HWIO_ECPRI_UDP_FH_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_ATTR_V2                                      0x1
#define HWIO_ECPRI_UDP_FH_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                         0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                                0x0

#define HWIO_ECPRI_UDP_FH_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                       (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x0000001c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                       (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x0000001c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                       (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x0000001c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_RMSK_V2                            0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_MAXp_V2                                     2
#define HWIO_ECPRI_UDP_FH_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_MAXn_V2                                     3
#define HWIO_ECPRI_UDP_FH_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_ATTR_V2                                   0x1
#define HWIO_ECPRI_UDP_FH_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                      0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                             0x0

#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                    (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x00000020 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                    (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x00000020 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                    (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x00000020 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_RMSK_V2                         0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_MAXp_V2                                  2
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_MAXn_V2                                  3
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_ATTR_V2                                0x1
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                   0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                          0x0

#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                      (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x00000024 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                      (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x00000024 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                      (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x00000024 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_RMSK_V2                           0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_MAXp_V2                                    2
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_MAXn_V2                                    3
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_ATTR_V2                                  0x1
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                     0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                            0x0

#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                    (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x00000028 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                    (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x00000028 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                    (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x00000028 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_RMSK_V2                         0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_MAXp_V2                                  2
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_MAXn_V2                                  3
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_ATTR_V2                                0x1
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                   0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                          0x0

#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)           (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x0000002c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)           (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x0000002c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)           (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x0000002c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_RMSK_V2                0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_MAXp_V2                         2
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_MAXn_V2                         3
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_ATTR_V2                       0x1
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2          0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                 0x0

#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                      (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x00000030 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                      (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x00000030 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                      (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x00000030 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_RMSK_V2                           0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_MAXp_V2                                    2
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_MAXn_V2                                    3
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_ATTR_V2                                  0x1
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                     0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                            0x0

#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                    (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x00000034 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                    (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x00000034 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                    (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x00000034 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_RMSK_V2                         0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_MAXp_V2                                  2
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_MAXn_V2                                  3
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_ATTR_V2                                0x1
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                   0xffffffff
#define HWIO_ECPRI_UDP_FH_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                          0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                           (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x00000038 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                           (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x00000038 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                           (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x00000038 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_RMSK_V2                                0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_MAXp_V2                                         2
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_MAXn_V2                                         3
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_ATTR_V2                                       0x1
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                          0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                                 0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                      (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x0000003c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                      (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x0000003c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                      (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x0000003c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_RMSK_V2                           0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_MAXp_V2                                    2
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_MAXn_V2                                    3
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_ATTR_V2                                  0x1
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                     0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                            0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                      (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x00000040 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                      (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x00000040 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                      (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x00000040 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_RMSK_V2                           0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_MAXp_V2                                    2
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_MAXn_V2                                    3
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_ATTR_V2                                  0x1
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                     0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                            0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                           (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x00000044 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                           (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x00000044 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                           (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x00000044 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_RMSK_V2                                0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_MAXp_V2                                         2
#define HWIO_ECPRI_UDP_FH_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_MAXn_V2                                         3
#define HWIO_ECPRI_UDP_FH_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_ATTR_V2                                       0x1
#define HWIO_ECPRI_UDP_FH_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                          0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                                 0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n_ADDR_V2(p,n)                                 (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x00001000 + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n_PHYS_V2(p,n)                                 (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x00001000 + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n_OFFS_V2(p,n)                                 (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x00001000 + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n_RMSK_V2                                      0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n_MAXp_V2                                               2
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n_MAXn_V2                                             255
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n_ATTR_V2                                             0x3
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n_VALUE_BMSK_V2                                0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n_VALUE_SHFT_V2                                       0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_ADDR_V2(p,n)                            (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x00001004 + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_PHYS_V2(p,n)                            (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x00001004 + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_OFFS_V2(p,n)                            (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x00001004 + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_RMSK_V2                                 0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_MAXp_V2                                          2
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_MAXn_V2                                        255
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_ATTR_V2                                        0x3
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_SRC_MSB_BMSK_V2                         0xffff0000
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_SRC_MSB_SHFT_V2                               0x10
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_DST_MSB_BMSK_V2                             0xffff
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_DST_MSB_SHFT_V2                                0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_ADDR_V2(p,n)                                 (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x00001008 + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_PHYS_V2(p,n)                                 (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x00001008 + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_OFFS_V2(p,n)                                 (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x00001008 + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_RMSK_V2                                      0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_MAXp_V2                                               2
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_MAXn_V2                                             255
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_ATTR_V2                                             0x3
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_VALUE_BMSK_V2                                0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_VALUE_SHFT_V2                                       0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_ADDR_V2(p,n)                           (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x0000100c + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_PHYS_V2(p,n)                           (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x0000100c + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_OFFS_V2(p,n)                           (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x0000100c + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_RMSK_V2                                0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_MAXp_V2                                         2
#define HWIO_ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_MAXn_V2                                       255
#define HWIO_ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_ATTR_V2                                       0x3
#define HWIO_ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_VLAN_DATA_BMSK_V2                      0xffff0000
#define HWIO_ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_VLAN_DATA_SHFT_V2                            0x10
#define HWIO_ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_ETHERTYPE_BMSK_V2                          0xffff
#define HWIO_ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_ETHERTYPE_SHFT_V2                             0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n)                               (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x00001010 + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_PHYS_V2(p,n)                               (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x00001010 + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_OFFS_V2(p,n)                               (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x00001010 + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_RMSK_V2                                        0x7fff
#define HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_MAXp_V2                                             2
#define HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_MAXn_V2                                           255
#define HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_ATTR_V2                                           0x3
#define HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_RSVD_BMSK_V2                                   0x7800
#define HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_RSVD_SHFT_V2                                      0xb
#define HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_VPORT_ACTION_BMSK_V2                            0x600
#define HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_VPORT_ACTION_SHFT_V2                              0x9
#define HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_HAS_VLAN_BMSK_V2                                0x100
#define HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_HAS_VLAN_SHFT_V2                                  0x8
#define HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_VPORT_BMSK_V2                                    0xff
#define HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_VPORT_SHFT_V2                                     0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n)                             (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x00010000 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_PHYS_V2(p,n)                             (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x00010000 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_OFFS_V2(p,n)                             (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x00010000 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_RMSK_V2                                  0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_MAXp_V2                                           2
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_MAXn_V2                                         255
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_ATTR_V2                                         0x3
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_VALUE_BMSK_V2                            0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_VALUE_SHFT_V2                                   0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n)                             (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x00010004 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_PHYS_V2(p,n)                             (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x00010004 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_OFFS_V2(p,n)                             (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x00010004 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_RMSK_V2                                  0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_MAXp_V2                                           2
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_MAXn_V2                                         255
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_ATTR_V2                                         0x3
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_VALUE_BMSK_V2                            0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_VALUE_SHFT_V2                                   0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n)                             (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x00010008 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_PHYS_V2(p,n)                             (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x00010008 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_OFFS_V2(p,n)                             (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x00010008 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_RMSK_V2                                  0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_MAXp_V2                                           2
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_MAXn_V2                                         255
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_ATTR_V2                                         0x3
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_VALUE_BMSK_V2                            0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_VALUE_SHFT_V2                                   0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n)                             (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x0001000c + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_PHYS_V2(p,n)                             (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x0001000c + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_OFFS_V2(p,n)                             (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x0001000c + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_RMSK_V2                                  0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_MAXp_V2                                           2
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_MAXn_V2                                         255
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_ATTR_V2                                         0x3
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_VALUE_BMSK_V2                            0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_VALUE_SHFT_V2                                   0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n)                             (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x00010010 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_PHYS_V2(p,n)                             (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x00010010 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_OFFS_V2(p,n)                             (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x00010010 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_RMSK_V2                                  0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_MAXp_V2                                           2
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_MAXn_V2                                         255
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_ATTR_V2                                         0x3
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_VALUE_BMSK_V2                            0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_VALUE_SHFT_V2                                   0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n)                             (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x00010014 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_PHYS_V2(p,n)                             (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x00010014 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_OFFS_V2(p,n)                             (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x00010014 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_RMSK_V2                                  0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_MAXp_V2                                           2
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_MAXn_V2                                         255
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_ATTR_V2                                         0x3
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_VALUE_BMSK_V2                            0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_VALUE_SHFT_V2                                   0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n)                             (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x00010018 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_PHYS_V2(p,n)                             (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x00010018 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_OFFS_V2(p,n)                             (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x00010018 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_RMSK_V2                                  0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_MAXp_V2                                           2
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_MAXn_V2                                         255
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_ATTR_V2                                         0x3
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_VALUE_BMSK_V2                            0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_VALUE_SHFT_V2                                   0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n)                             (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x0001001c + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_PHYS_V2(p,n)                             (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x0001001c + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_OFFS_V2(p,n)                             (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x0001001c + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_RMSK_V2                                  0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_MAXp_V2                                           2
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_MAXn_V2                                         255
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_ATTR_V2                                         0x3
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_VALUE_BMSK_V2                            0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_VALUE_SHFT_V2                                   0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_ADDR_V2(p,n)                                (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x00010020 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_PHYS_V2(p,n)                                (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x00010020 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_OFFS_V2(p,n)                                (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x00010020 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_RMSK_V2                                     0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_MAXp_V2                                              2
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_MAXn_V2                                            255
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_ATTR_V2                                            0x3
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_DST_BMSK_V2                                 0xffff0000
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_DST_SHFT_V2                                       0x10
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_SRC_BMSK_V2                                     0xffff
#define HWIO_ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_SRC_SHFT_V2                                        0x0

#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n)                       (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_V2     + 0x00010024 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_PHYS_V2(p,n)                       (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_PHYS_V2 + 0x00010024 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_OFFS_V2(p,n)                       (ECPRI_UDP_FH_UDP_FH_RAMS_REG_BASE_OFFS_V2 + 0x00010024 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_RMSK_V2                            0xffffffff
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_MAXp_V2                                     2
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_MAXn_V2                                   255
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_ATTR_V2                                   0x3
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_RSVD_BMSK_V2                       0xf0000000
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_RSVD_SHFT_V2                             0x1c
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_CALC_UDP_CS_BMSK_V2                 0x8000000
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_CALC_UDP_CS_SHFT_V2                      0x1b
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_DF_BIT_BMSK_V2                      0x4000000
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_DF_BIT_SHFT_V2                           0x1a
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_IS_IPSEC_BMSK_V2                    0x2000000
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_IS_IPSEC_SHFT_V2                         0x19
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_IP_TYPE_BMSK_V2                     0x1000000
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_IP_TYPE_SHFT_V2                          0x18
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_TOS_BMSK_V2                          0xff0000
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_TOS_SHFT_V2                              0x10
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_SA_TAG_DATA_BMSK_V2                    0xffff
#define HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_SA_TAG_DATA_SHFT_V2                       0x0

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_UDP_C2C_UDP_C2C_REGS
 *--------------------------------------------------------------------------*/

#define ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_V2                                                                 (ECPRI_WRAPPER_BASE      + 0x003b0000)
#define ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_PHYS_V2                                                             (ECPRI_WRAPPER_BASE_PHYS + 0x003b0000)
#define ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_OFFS_V2                                                             0x003b0000

#define HWIO_ECPRI_UDP_C2C_WORDS_BEFORE_TRANSMITTING_p_ADDR_V2(p)                                               (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_V2     + 0x0000000c + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_WORDS_BEFORE_TRANSMITTING_p_PHYS_V2(p)                                               (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_PHYS_V2 + 0x0000000c + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_WORDS_BEFORE_TRANSMITTING_p_OFFS_V2(p)                                               (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_OFFS_V2 + 0x0000000c + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_WORDS_BEFORE_TRANSMITTING_p_RMSK_V2                                                        0xff
#define HWIO_ECPRI_UDP_C2C_WORDS_BEFORE_TRANSMITTING_p_MAXp_V2                                                           1
#define HWIO_ECPRI_UDP_C2C_WORDS_BEFORE_TRANSMITTING_p_ATTR_V2                                                         0x3
#define HWIO_ECPRI_UDP_C2C_WORDS_BEFORE_TRANSMITTING_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_WORDS_BEFORE_TRANSMITTING_p_ADDR_V2(p), HWIO_ECPRI_UDP_C2C_WORDS_BEFORE_TRANSMITTING_p_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_WORDS_BEFORE_TRANSMITTING_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_WORDS_BEFORE_TRANSMITTING_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_C2C_WORDS_BEFORE_TRANSMITTING_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_C2C_WORDS_BEFORE_TRANSMITTING_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_C2C_WORDS_BEFORE_TRANSMITTING_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_C2C_WORDS_BEFORE_TRANSMITTING_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_C2C_WORDS_BEFORE_TRANSMITTING_p_INI_V2(p))
#define HWIO_ECPRI_UDP_C2C_WORDS_BEFORE_TRANSMITTING_p_VALUE_BMSK_V2                                                  0xff
#define HWIO_ECPRI_UDP_C2C_WORDS_BEFORE_TRANSMITTING_p_VALUE_SHFT_V2                                                   0x0

#define HWIO_ECPRI_UDP_C2C_ECPRI_ETHERTYPE_p_ADDR_V2(p)                                                         (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_V2     + 0x0000002c + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_ECPRI_ETHERTYPE_p_PHYS_V2(p)                                                         (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_PHYS_V2 + 0x0000002c + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_ECPRI_ETHERTYPE_p_OFFS_V2(p)                                                         (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_OFFS_V2 + 0x0000002c + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_ECPRI_ETHERTYPE_p_RMSK_V2                                                                0xffff
#define HWIO_ECPRI_UDP_C2C_ECPRI_ETHERTYPE_p_MAXp_V2                                                                     1
#define HWIO_ECPRI_UDP_C2C_ECPRI_ETHERTYPE_p_ATTR_V2                                                                   0x3
#define HWIO_ECPRI_UDP_C2C_ECPRI_ETHERTYPE_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_ECPRI_ETHERTYPE_p_ADDR_V2(p), HWIO_ECPRI_UDP_C2C_ECPRI_ETHERTYPE_p_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_ECPRI_ETHERTYPE_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_ECPRI_ETHERTYPE_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_C2C_ECPRI_ETHERTYPE_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_C2C_ECPRI_ETHERTYPE_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_C2C_ECPRI_ETHERTYPE_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_C2C_ECPRI_ETHERTYPE_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_C2C_ECPRI_ETHERTYPE_p_INI_V2(p))
#define HWIO_ECPRI_UDP_C2C_ECPRI_ETHERTYPE_p_VALUE_BMSK_V2                                                          0xffff
#define HWIO_ECPRI_UDP_C2C_ECPRI_ETHERTYPE_p_VALUE_SHFT_V2                                                             0x0

#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_ADDR_V2(p)                                                        (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_V2     + 0x00000500 + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_PHYS_V2(p)                                                        (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_PHYS_V2 + 0x00000500 + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_OFFS_V2(p)                                                        (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_OFFS_V2 + 0x00000500 + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_RMSK_V2                                                                0x3ff
#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_MAXp_V2                                                                    1
#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_ATTR_V2                                                                  0x1
#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_ADDR_V2(p), HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_EGRESS_OUTPUT_FIFO_EMPTY_BMSK_V2                                       0x200
#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_EGRESS_OUTPUT_FIFO_EMPTY_SHFT_V2                                         0x9
#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_EGRESS_ALIGNER_IDLE_BMSK_V2                                            0x100
#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_EGRESS_ALIGNER_IDLE_SHFT_V2                                              0x8
#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_EGRESS_PKT_FIFO_EMPTY_BMSK_V2                                           0x80
#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_EGRESS_PKT_FIFO_EMPTY_SHFT_V2                                            0x7
#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_EGRESS_HDRI_IDLE_BMSK_V2                                                0x40
#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_EGRESS_HDRI_IDLE_SHFT_V2                                                 0x6
#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_EGRESS_IDLE_BMSK_V2                                                     0x20
#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_EGRESS_IDLE_SHFT_V2                                                      0x5
#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_INGRESS_CMD_FIFO_EMPTY_LINK_0_BMSK_V2                                   0x10
#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_INGRESS_CMD_FIFO_EMPTY_LINK_0_SHFT_V2                                    0x4
#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_INGRESS_PKT_FIFO_EMPTY_LINK_0_BMSK_V2                                    0x8
#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_INGRESS_PKT_FIFO_EMPTY_LINK_0_SHFT_V2                                    0x3
#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_INGRESS_ALIGNER_IDLE_BMSK_V2                                             0x4
#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_INGRESS_ALIGNER_IDLE_SHFT_V2                                             0x2
#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_INGRESS_IDLE_BMSK_V2                                                     0x2
#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_INGRESS_IDLE_SHFT_V2                                                     0x1
#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_PORT_IS_IDLE_BMSK_V2                                                     0x1
#define HWIO_ECPRI_UDP_C2C_IDLE_STATUS_PORT_p_PORT_IS_IDLE_SHFT_V2                                                     0x0

#define HWIO_ECPRI_UDP_C2C_CGC_CFG_ADDR_V2                                                                      (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_V2     + 0x00000510)
#define HWIO_ECPRI_UDP_C2C_CGC_CFG_PHYS_V2                                                                      (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_PHYS_V2 + 0x00000510)
#define HWIO_ECPRI_UDP_C2C_CGC_CFG_OFFS_V2                                                                      (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_OFFS_V2 + 0x00000510)
#define HWIO_ECPRI_UDP_C2C_CGC_CFG_RMSK_V2                                                                             0x3
#define HWIO_ECPRI_UDP_C2C_CGC_CFG_ATTR_V2                                                                             0x3
#define HWIO_ECPRI_UDP_C2C_CGC_CFG_IN_V2          \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_CGC_CFG_ADDR_V2, HWIO_ECPRI_UDP_C2C_CGC_CFG_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_CGC_CFG_IN_V2M(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_CGC_CFG_ADDR_V2, m)
#define HWIO_ECPRI_UDP_C2C_CGC_CFG_OUT_V2(v)      \
        out_dword(HWIO_ECPRI_UDP_C2C_CGC_CFG_ADDR_V2,v)
#define HWIO_ECPRI_UDP_C2C_CGC_CFG_OUTM_V2(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_C2C_CGC_CFG_ADDR_V2,m,v,HWIO_ECPRI_UDP_C2C_CGC_CFG_IN_V2)
#define HWIO_ECPRI_UDP_C2C_CGC_CFG_EGRESS_CGC_OPEN_BMSK_V2                                                             0x2
#define HWIO_ECPRI_UDP_C2C_CGC_CFG_EGRESS_CGC_OPEN_SHFT_V2                                                             0x1
#define HWIO_ECPRI_UDP_C2C_CGC_CFG_IN_V2GRESS_CGC_OPEN_BMSK_V2                                                            0x1
#define HWIO_ECPRI_UDP_C2C_CGC_CFG_IN_V2GRESS_CGC_OPEN_SHFT_V2                                                            0x0

#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_0_ADDR_V2                                                                  (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_V2     + 0x00000514)
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_0_PHYS_V2                                                                  (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_PHYS_V2 + 0x00000514)
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_0_OFFS_V2                                                                  (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_OFFS_V2 + 0x00000514)
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_0_RMSK_V2                                                                  0xffffffff
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_0_ATTR_V2                                                                         0x1
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_0_IN_V2          \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_HW_PARAMS_0_ADDR_V2, HWIO_ECPRI_UDP_C2C_HW_PARAMS_0_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_0_INM_V2(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_HW_PARAMS_0_ADDR_V2, m)
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_0_L3_SUPPORT_BMSK_V2                                                       0x80000000
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_0_L3_SUPPORT_SHFT_V2                                                             0x1f
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_0_UDP_CLASSIFICATION_ENTRIES_N_BMSK_V2                                     0x7e000000
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_0_UDP_CLASSIFICATION_ENTRIES_N_SHFT_V2                                           0x19
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_0_IP_TABLE_ENTRIES_N_BMSK_V2                                                0x1ff0000
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_0_IP_TABLE_ENTRIES_N_SHFT_V2                                                     0x10
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_0_ETH_TABLE_ENTRIES_N_BMSK_V2                                                  0xff80
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_0_ETH_TABLE_ENTRIES_N_SHFT_V2                                                     0x7
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_0_LINKS_N_BMSK_V2                                                                0x70
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_0_LINKS_N_SHFT_V2                                                                 0x4
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_0_PORTS_N_BMSK_V2                                                                 0xc
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_0_PORTS_N_SHFT_V2                                                                 0x2
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_0_INSTANCE_TYPE_BMSK_V2                                                           0x3
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_0_INSTANCE_TYPE_SHFT_V2                                                           0x0
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_0_INSTANCE_TYPE_FH_FVAL                                                        0x0
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_0_INSTANCE_TYPE_C2C_FVAL                                                       0x1
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_0_INSTANCE_TYPE_L2_FVAL                                                        0x2

#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_1_ADDR_V2                                                                  (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_V2     + 0x00000518)
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_1_PHYS_V2                                                                  (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_PHYS_V2 + 0x00000518)
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_1_OFFS_V2                                                                  (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_OFFS_V2 + 0x00000518)
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_1_RMSK_V2                                                                      0x7fff
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_1_ATTR_V2                                                                         0x1
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_1_IN_V2          \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_HW_PARAMS_1_ADDR_V2, HWIO_ECPRI_UDP_C2C_HW_PARAMS_1_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_1_INM_V2(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_HW_PARAMS_1_ADDR_V2, m)
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_1_ETH_DST_FILT_ENTRIES_N_BMSK_V2                                               0x7c00
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_1_ETH_DST_FILT_ENTRIES_N_SHFT_V2                                                  0xa
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_1_IP_FILT_ENTRIES_N_BMSK_V2                                                     0x3e0
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_1_IP_FILT_ENTRIES_N_SHFT_V2                                                       0x5
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_1_VLAN_FILT_ENTRIES_N_BMSK_V2                                                    0x1f
#define HWIO_ECPRI_UDP_C2C_HW_PARAMS_1_VLAN_FILT_ENTRIES_N_SHFT_V2                                                     0x0

#define HWIO_ECPRI_UDP_C2C_QUDP_STAT_COUNTERS_CTL_ADDR_V2                                                       (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_V2     + 0x0000051c)
#define HWIO_ECPRI_UDP_C2C_QUDP_STAT_COUNTERS_CTL_PHYS_V2                                                       (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_PHYS_V2 + 0x0000051c)
#define HWIO_ECPRI_UDP_C2C_QUDP_STAT_COUNTERS_CTL_OFFS_V2                                                       (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_OFFS_V2 + 0x0000051c)
#define HWIO_ECPRI_UDP_C2C_QUDP_STAT_COUNTERS_CTL_RMSK_V2                                                              0x3
#define HWIO_ECPRI_UDP_C2C_QUDP_STAT_COUNTERS_CTL_ATTR_V2                                                              0x3
#define HWIO_ECPRI_UDP_C2C_QUDP_STAT_COUNTERS_CTL_IN_V2          \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_QUDP_STAT_COUNTERS_CTL_ADDR_V2, HWIO_ECPRI_UDP_C2C_QUDP_STAT_COUNTERS_CTL_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_QUDP_STAT_COUNTERS_CTL_INM_V2(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_QUDP_STAT_COUNTERS_CTL_ADDR_V2, m)
#define HWIO_ECPRI_UDP_C2C_QUDP_STAT_COUNTERS_CTL_OUT_V2(v)      \
        out_dword(HWIO_ECPRI_UDP_C2C_QUDP_STAT_COUNTERS_CTL_ADDR_V2,v)
#define HWIO_ECPRI_UDP_C2C_QUDP_STAT_COUNTERS_CTL_OUTM_V2(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_C2C_QUDP_STAT_COUNTERS_CTL_ADDR_V2,m,v,HWIO_ECPRI_UDP_C2C_QUDP_STAT_COUNTERS_CTL_IN_V2)
#define HWIO_ECPRI_UDP_C2C_QUDP_STAT_COUNTERS_CTL_CNT_CLR_EN_BMSK_V2                                                   0x2
#define HWIO_ECPRI_UDP_C2C_QUDP_STAT_COUNTERS_CTL_CNT_CLR_EN_SHFT_V2                                                   0x1
#define HWIO_ECPRI_UDP_C2C_QUDP_STAT_COUNTERS_CTL_CNT_EN_BMSK_V2                                                       0x1
#define HWIO_ECPRI_UDP_C2C_QUDP_STAT_COUNTERS_CTL_CNT_EN_SHFT_V2                                                       0x0

#define HWIO_ECPRI_UDP_C2C_QUDP_CTL_PORT_p_ADDR_V2(p)                                                           (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_V2     + 0x00000520 + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_QUDP_CTL_PORT_p_PHYS_V2(p)                                                           (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_PHYS_V2 + 0x00000520 + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_QUDP_CTL_PORT_p_OFFS_V2(p)                                                           (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_OFFS_V2 + 0x00000520 + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_QUDP_CTL_PORT_p_RMSK_V2                                                                     0x5
#define HWIO_ECPRI_UDP_C2C_QUDP_CTL_PORT_p_MAXp_V2                                                                       1
#define HWIO_ECPRI_UDP_C2C_QUDP_CTL_PORT_p_ATTR_V2                                                                     0x3
#define HWIO_ECPRI_UDP_C2C_QUDP_CTL_PORT_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_QUDP_CTL_PORT_p_ADDR_V2(p), HWIO_ECPRI_UDP_C2C_QUDP_CTL_PORT_p_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_QUDP_CTL_PORT_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_QUDP_CTL_PORT_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_C2C_QUDP_CTL_PORT_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_C2C_QUDP_CTL_PORT_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_C2C_QUDP_CTL_PORT_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_C2C_QUDP_CTL_PORT_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_C2C_QUDP_CTL_PORT_p_INI_V2(p))
#define HWIO_ECPRI_UDP_C2C_QUDP_CTL_PORT_p_DISABLE_IRQ_DELAY_BMSK_V2                                                   0x4
#define HWIO_ECPRI_UDP_C2C_QUDP_CTL_PORT_p_DISABLE_IRQ_DELAY_SHFT_V2                                                   0x2
#define HWIO_ECPRI_UDP_C2C_QUDP_CTL_PORT_p_SRES_BMSK_V2                                                                0x1
#define HWIO_ECPRI_UDP_C2C_QUDP_CTL_PORT_p_SRES_SHFT_V2                                                                0x0

#define HWIO_ECPRI_UDP_C2C_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_ADDR_V2(p,n)                                     (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_V2     + 0x0000052c + 0x4 * (n) + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_PHYS_V2(p,n)                                     (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_PHYS_V2 + 0x0000052c + 0x4 * (n) + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_OFFS_V2(p,n)                                     (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_OFFS_V2 + 0x0000052c + 0x4 * (n) + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_RMSK_V2                                           0x3ff1fff
#define HWIO_ECPRI_UDP_C2C_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_MAXp_V2                                                   1
#define HWIO_ECPRI_UDP_C2C_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_MAXn_V2                                                   0
#define HWIO_ECPRI_UDP_C2C_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_ATTR_V2                                                 0x1
#define HWIO_ECPRI_UDP_C2C_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_C2C_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_C2C_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_CMD_FIFO_BMSK_V2                                  0x3ff0000
#define HWIO_ECPRI_UDP_C2C_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_CMD_FIFO_SHFT_V2                                       0x10
#define HWIO_ECPRI_UDP_C2C_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_PKT_HANDLER_SYNC_FIFOS_BMSK_V2                       0x1c00
#define HWIO_ECPRI_UDP_C2C_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_PKT_HANDLER_SYNC_FIFOS_SHFT_V2                          0xa
#define HWIO_ECPRI_UDP_C2C_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_PKT_FIFO_BMSK_V2                                      0x3ff
#define HWIO_ECPRI_UDP_C2C_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_PKT_FIFO_SHFT_V2                                        0x0

#define HWIO_ECPRI_UDP_C2C_EGRESS_UDP_WATERMARK_0_PORT_p_ADDR_V2(p)                                             (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_V2     + 0x0000055c + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_UDP_WATERMARK_0_PORT_p_PHYS_V2(p)                                             (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_PHYS_V2 + 0x0000055c + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_UDP_WATERMARK_0_PORT_p_OFFS_V2(p)                                             (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_OFFS_V2 + 0x0000055c + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_UDP_WATERMARK_0_PORT_p_RMSK_V2                                                 0x1ffffff
#define HWIO_ECPRI_UDP_C2C_EGRESS_UDP_WATERMARK_0_PORT_p_MAXp_V2                                                         1
#define HWIO_ECPRI_UDP_C2C_EGRESS_UDP_WATERMARK_0_PORT_p_ATTR_V2                                                       0x1
#define HWIO_ECPRI_UDP_C2C_EGRESS_UDP_WATERMARK_0_PORT_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_EGRESS_UDP_WATERMARK_0_PORT_p_ADDR_V2(p), HWIO_ECPRI_UDP_C2C_EGRESS_UDP_WATERMARK_0_PORT_p_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_EGRESS_UDP_WATERMARK_0_PORT_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_EGRESS_UDP_WATERMARK_0_PORT_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_C2C_EGRESS_UDP_WATERMARK_0_PORT_p_ALIGNER_OUTPUT_FIFO_BMSK_V2                             0x1c00000
#define HWIO_ECPRI_UDP_C2C_EGRESS_UDP_WATERMARK_0_PORT_p_ALIGNER_OUTPUT_FIFO_SHFT_V2                                  0x16
#define HWIO_ECPRI_UDP_C2C_EGRESS_UDP_WATERMARK_0_PORT_p_HDRI_OUTPUT_FIFO_BMSK_V2                                 0x380000
#define HWIO_ECPRI_UDP_C2C_EGRESS_UDP_WATERMARK_0_PORT_p_HDRI_OUTPUT_FIFO_SHFT_V2                                     0x13
#define HWIO_ECPRI_UDP_C2C_EGRESS_UDP_WATERMARK_0_PORT_p_HDRI_CFG_IN_V2DEX_FIFO_BMSK_V2                               0x7fc00
#define HWIO_ECPRI_UDP_C2C_EGRESS_UDP_WATERMARK_0_PORT_p_HDRI_CFG_IN_V2DEX_FIFO_SHFT_V2                                   0xa
#define HWIO_ECPRI_UDP_C2C_EGRESS_UDP_WATERMARK_0_PORT_p_PKT_FIFO_BMSK_V2                                            0x3ff
#define HWIO_ECPRI_UDP_C2C_EGRESS_UDP_WATERMARK_0_PORT_p_PKT_FIFO_SHFT_V2                                              0x0

#define HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_ADDR_V2                                                           (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_V2     + 0x00000568)
#define HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_PHYS_V2                                                           (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_PHYS_V2 + 0x00000568)
#define HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_OFFS_V2                                                           (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_OFFS_V2 + 0x00000568)
#define HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_RMSK_V2                                                                 0x3f
#define HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_ATTR_V2                                                                  0x3
#define HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_IN_V2          \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_ADDR_V2, HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_IN_V2M(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_ADDR_V2, m)
#define HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_OUT_V2(v)      \
        out_dword(HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_ADDR_V2,v)
#define HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_OUTM_V2(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_ADDR_V2,m,v,HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_IN_V2)
#define HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_HW_EVENTS_EN_BMSK_V2                                                    0x20
#define HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_HW_EVENTS_EN_SHFT_V2                                                     0x5
#define HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_TESTBUS_EN_BMSK_V2                                                      0x10
#define HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_TESTBUS_EN_SHFT_V2                                                       0x4
#define HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_EN_CLEAR_WATERMARK_ON_READ_BMSK_V2                                       0x8
#define HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_EN_CLEAR_WATERMARK_ON_READ_SHFT_V2                                       0x3
#define HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_WATERMARK_EN_BMSK_V2                                                     0x4
#define HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_WATERMARK_EN_SHFT_V2                                                     0x2
#define HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_TPDM_OPERATION_MODE_BMSK_V2                                              0x2
#define HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_TPDM_OPERATION_MODE_SHFT_V2                                              0x1
#define HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_TPDM_OPERATION_MODE_DATA_MODE_FVAL                                    0x0
#define HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_TPDM_OPERATION_MODE_CONTROL_MODE_FVAL                                 0x1
#define HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_TPDM_EN_BMSK_V2                                                          0x1
#define HWIO_ECPRI_UDP_C2C_DEBUG_FEATURES_CFG_TPDM_EN_SHFT_V2                                                          0x0

#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_ADDR_V2                                                                (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_V2     + 0x0000056c)
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_PHYS_V2                                                                (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_PHYS_V2 + 0x0000056c)
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_OFFS_V2                                                                (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_OFFS_V2 + 0x0000056c)
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_RMSK_V2                                                                 0x3fe7ff3
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_ATTR_V2                                                                       0x3
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_IN_V2          \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_ADDR_V2, HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_IN_V2M(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_ADDR_V2, m)
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_OUT_V2(v)      \
        out_dword(HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_ADDR_V2,v)
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_OUTM_V2(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_ADDR_V2,m,v,HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_IN_V2)
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_MAX_WORDS_TO_SEND_PER_PACKET_BMSK_V2                                    0x3fe0000
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_MAX_WORDS_TO_SEND_PER_PACKET_SHFT_V2                                         0x11
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_SAMPLING_MODE_BMSK_V2                                                      0x6000
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_SAMPLING_MODE_SHFT_V2                                                         0xd
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_SAMPLING_MODE_NUM_WORDS_FROM_SOP_FVAL                                      0x0
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_SAMPLING_MODE_SOP_ONLY_FVAL                                                0x1
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_SAMPLING_MODE_EOP_ONLY_FVAL                                                0x2
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_SAMPLING_MODE_SOP_AND_EOP_ONLY_FVAL                                        0x3
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_SIDEBAND_INSERTION_OFFSET_BMSK_V2                                          0x1c00
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_SIDEBAND_INSERTION_OFFSET_SHFT_V2                                             0xa
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_SIDEBAND_INSERTION_MODE_BMSK_V2                                             0x300
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_SIDEBAND_INSERTION_MODE_SHFT_V2                                               0x8
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_SIDEBAND_INSERTION_MODE_INSERT_ALWAYS_FVAL                                 0x0
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_SIDEBAND_INSERTION_MODE_INSERT_ONLY_AT_SOP_FVAL                            0x1
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_SIDEBAND_INSERTION_MODE_INSERT_ONLY_AT_EOP_FVAL                            0x2
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_SIDEBAND_INSERTION_MODE_INSERT_AT_EOP_AND_SOP_FVAL                         0x3
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_SIDEBAND_INSERTION_EN_BMSK_V2                                                0x80
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_SIDEBAND_INSERTION_EN_SHFT_V2                                                 0x7
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_BUS_SEL_BMSK_V2                                                              0x70
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_BUS_SEL_SHFT_V2                                                               0x4
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_BUS_SEL_INGRESS_SEC2UDP_FVAL                                               0x0
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_BUS_SEL_INGRESS_UDP2XBAR_FVAL                                              0x1
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_BUS_SEL_EGRESS_XBAR2UDP_FVAL                                               0x2
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_BUS_SEL_EGRESS_UDP2SEC_FVAL                                                0x3
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_BUS_SEL_EGRESS_HDRI_OUTPUT_FVAL                                            0x4
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_BUS_SEL_EGRESS_CS_UPDATE_OUTPUT_FVAL                                       0x5
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_PORT_INDEX_SEL_BMSK_V2                                                        0x3
#define HWIO_ECPRI_UDP_C2C_TPDM_DATA_CFG_PORT_INDEX_SEL_SHFT_V2                                                        0x0

#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_ADDR_V2                                                           (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_V2     + 0x00000570)
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_PHYS_V2                                                           (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_PHYS_V2 + 0x00000570)
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_OFFS_V2                                                           (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_OFFS_V2 + 0x00000570)
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_RMSK_V2                                                            0xffffff3
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_ATTR_V2                                                                  0x3
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_IN_V2          \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_ADDR_V2, HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_INM_V2(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_ADDR_V2, m)
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_OUT_V2(v)      \
        out_dword(HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_ADDR_V2,v)
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_OUTM_V2(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_ADDR_V2,m,v,HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_IN_V2)
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_ARBITRARY_TESTBUS_2_SEL_BMSK_V2                                    0xfe00000
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_ARBITRARY_TESTBUS_2_SEL_SHFT_V2                                         0x15
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_ARBITRARY_TESTBUS_1_SEL_BMSK_V2                                     0x1fc000
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_ARBITRARY_TESTBUS_1_SEL_SHFT_V2                                          0xe
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_ARBITRARY_TESTBUS_0_SEL_BMSK_V2                                       0x3f80
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_ARBITRARY_TESTBUS_0_SEL_SHFT_V2                                          0x7
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_BUS_SEL_BMSK_V2                                                         0x70
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_BUS_SEL_SHFT_V2                                                          0x4
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_BUS_SEL_INGRESS_PKT_HANDLER_FVAL                                      0x0
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_BUS_SEL_INGRESS_PKT_HANDLER_WHITELISTS_FVAL                           0x1
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_BUS_SEL_INGRESS_PORT_TOP_FVAL                                         0x2
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_BUS_SEL_EGRESS_HDRI_FVAL                                              0x3
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_BUS_SEL_EGRESS_PORT_TOP_FVAL                                          0x4
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_BUS_SEL_ARBITRARY_TESTBUSES_FVAL                                      0x5
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_PORT_INDEX_SEL_BMSK_V2                                                   0x3
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0_PORT_INDEX_SEL_SHFT_V2                                                   0x0

#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_1_ADDR_V2                                                           (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_V2     + 0x00000574)
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_1_PHYS_V2                                                           (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_PHYS_V2 + 0x00000574)
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_1_OFFS_V2                                                           (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_OFFS_V2 + 0x00000574)
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_1_RMSK_V2                                                            0xfffffff
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_1_ATTR_V2                                                                  0x3
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_1_IN_V2          \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_1_ADDR_V2, HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_1_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_1_INM_V2(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_1_ADDR_V2, m)
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_1_OUT_V2(v)      \
        out_dword(HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_1_ADDR_V2,v)
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_1_OUTM_V2(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_1_ADDR_V2,m,v,HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_1_IN_V2)
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_1_ARBITRARY_TESTBUS_6_SEL_BMSK_V2                                    0xfe00000
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_1_ARBITRARY_TESTBUS_6_SEL_SHFT_V2                                         0x15
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_1_ARBITRARY_TESTBUS_5_SEL_BMSK_V2                                     0x1fc000
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_1_ARBITRARY_TESTBUS_5_SEL_SHFT_V2                                          0xe
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_1_ARBITRARY_TESTBUS_4_SEL_BMSK_V2                                       0x3f80
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_1_ARBITRARY_TESTBUS_4_SEL_SHFT_V2                                          0x7
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_1_ARBITRARY_TESTBUS_3_SEL_BMSK_V2                                         0x7f
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_CFG_1_ARBITRARY_TESTBUS_3_SEL_SHFT_V2                                          0x0

#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_MASK_n_ADDR_V2(n)                                                       (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_V2     + 0x00000578 + 0x4 * (n))
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_MASK_n_PHYS_V2(n)                                                       (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_PHYS_V2 + 0x00000578 + 0x4 * (n))
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_MASK_n_OFFS_V2(n)                                                       (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_OFFS_V2 + 0x00000578 + 0x4 * (n))
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_MASK_n_RMSK_V2                                                          0xffffffff
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_MASK_n_MAXn_V2                                                                   6
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_MASK_n_ATTR_V2                                                                 0x3
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_MASK_n_INI_V2(n)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_MASK_n_ADDR_V2(n), HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_MASK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_MASK_n_INMI_V2(n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_MASK_n_ADDR_V2(n), mask)
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_MASK_n_OUTI_V2(n,val)    \
        out_dword(HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_MASK_n_ADDR_V2(n),val)
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_MASK_n_OUTMI_V2(n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_MASK_n_ADDR_V2(n),mask,val,HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_MASK_n_INI_V2(n))
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_MASK_n_MASK_BITS_BMSK_V2                                                0xffffffff
#define HWIO_ECPRI_UDP_C2C_TPDM_CONTROL_MASK_n_MASK_BITS_SHFT_V2                                                       0x0

#define HWIO_ECPRI_UDP_C2C_TESTBUS_SEL_CFG_ADDR_V2                                                              (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_V2     + 0x00000594)
#define HWIO_ECPRI_UDP_C2C_TESTBUS_SEL_CFG_PHYS_V2                                                              (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_PHYS_V2 + 0x00000594)
#define HWIO_ECPRI_UDP_C2C_TESTBUS_SEL_CFG_OFFS_V2                                                              (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_OFFS_V2 + 0x00000594)
#define HWIO_ECPRI_UDP_C2C_TESTBUS_SEL_CFG_RMSK_V2                                                                   0x7f3
#define HWIO_ECPRI_UDP_C2C_TESTBUS_SEL_CFG_ATTR_V2                                                                     0x3
#define HWIO_ECPRI_UDP_C2C_TESTBUS_SEL_CFG_IN_V2          \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_TESTBUS_SEL_CFG_ADDR_V2, HWIO_ECPRI_UDP_C2C_TESTBUS_SEL_CFG_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_TESTBUS_SEL_CFG_IN_V2M(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_TESTBUS_SEL_CFG_ADDR_V2, m)
#define HWIO_ECPRI_UDP_C2C_TESTBUS_SEL_CFG_OUT_V2(v)      \
        out_dword(HWIO_ECPRI_UDP_C2C_TESTBUS_SEL_CFG_ADDR_V2,v)
#define HWIO_ECPRI_UDP_C2C_TESTBUS_SEL_CFG_OUTM_V2(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_C2C_TESTBUS_SEL_CFG_ADDR_V2,m,v,HWIO_ECPRI_UDP_C2C_TESTBUS_SEL_CFG_IN_V2)
#define HWIO_ECPRI_UDP_C2C_TESTBUS_SEL_CFG_TESTBUS_SEL_BMSK_V2                                                       0x7f0
#define HWIO_ECPRI_UDP_C2C_TESTBUS_SEL_CFG_TESTBUS_SEL_SHFT_V2                                                         0x4
#define HWIO_ECPRI_UDP_C2C_TESTBUS_SEL_CFG_PORT_INDEX_SEL_BMSK_V2                                                      0x3
#define HWIO_ECPRI_UDP_C2C_TESTBUS_SEL_CFG_PORT_INDEX_SEL_SHFT_V2                                                      0x0

#define HWIO_ECPRI_UDP_C2C_TESTBUS_ADDR_V2                                                                      (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_V2     + 0x00000598)
#define HWIO_ECPRI_UDP_C2C_TESTBUS_PHYS_V2                                                                      (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_PHYS_V2 + 0x00000598)
#define HWIO_ECPRI_UDP_C2C_TESTBUS_OFFS_V2                                                                      (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_OFFS_V2 + 0x00000598)
#define HWIO_ECPRI_UDP_C2C_TESTBUS_RMSK_V2                                                                      0xffffffff
#define HWIO_ECPRI_UDP_C2C_TESTBUS_ATTR_V2                                                                             0x1
#define HWIO_ECPRI_UDP_C2C_TESTBUS_IN_V2          \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_TESTBUS_ADDR_V2, HWIO_ECPRI_UDP_C2C_TESTBUS_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_TESTBUS_INM_V2(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_TESTBUS_ADDR_V2, m)
#define HWIO_ECPRI_UDP_C2C_TESTBUS_DATA_BMSK_V2                                                                 0xffffffff
#define HWIO_ECPRI_UDP_C2C_TESTBUS_DATA_SHFT_V2                                                                        0x0

#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_MTU_p_ADDR_V2(p)                                                          (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_V2     + 0x0000083c + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_MTU_p_PHYS_V2(p)                                                          (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_PHYS_V2 + 0x0000083c + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_MTU_p_OFFS_V2(p)                                                          (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_OFFS_V2 + 0x0000083c + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_MTU_p_RMSK_V2                                                                 0x3fff
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_MTU_p_MAXp_V2                                                                      1
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_MTU_p_ATTR_V2                                                                    0x3
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_MTU_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_EGRESS_ETH_MTU_p_ADDR_V2(p), HWIO_ECPRI_UDP_C2C_EGRESS_ETH_MTU_p_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_MTU_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_EGRESS_ETH_MTU_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_MTU_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_C2C_EGRESS_ETH_MTU_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_MTU_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_C2C_EGRESS_ETH_MTU_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_C2C_EGRESS_ETH_MTU_p_INI_V2(p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_MTU_p_VALUE_BMSK_V2                                                           0x3fff
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_MTU_p_VALUE_SHFT_V2                                                              0x0

#define HWIO_ECPRI_UDP_C2C_EGRESS_CONFIG_p_ADDR_V2(p)                                                           (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_V2     + 0x00000860 + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_CONFIG_p_PHYS_V2(p)                                                           (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_PHYS_V2 + 0x00000860 + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_CONFIG_p_OFFS_V2(p)                                                           (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_OFFS_V2 + 0x00000860 + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_CONFIG_p_RMSK_V2                                                                   0xffe
#define HWIO_ECPRI_UDP_C2C_EGRESS_CONFIG_p_MAXp_V2                                                                       1
#define HWIO_ECPRI_UDP_C2C_EGRESS_CONFIG_p_ATTR_V2                                                                     0x3
#define HWIO_ECPRI_UDP_C2C_EGRESS_CONFIG_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_EGRESS_CONFIG_p_ADDR_V2(p), HWIO_ECPRI_UDP_C2C_EGRESS_CONFIG_p_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_EGRESS_CONFIG_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_EGRESS_CONFIG_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_C2C_EGRESS_CONFIG_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_C2C_EGRESS_CONFIG_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_C2C_EGRESS_CONFIG_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_C2C_EGRESS_CONFIG_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_C2C_EGRESS_CONFIG_p_INI_V2(p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_CONFIG_p_DISABLE_PADDING_REMOVAL_BMSK_V2                                           0x800
#define HWIO_ECPRI_UDP_C2C_EGRESS_CONFIG_p_DISABLE_PADDING_REMOVAL_SHFT_V2                                             0xb
#define HWIO_ECPRI_UDP_C2C_EGRESS_CONFIG_p_BYPASSED_PACKETS_VPORT_BMSK_V2                                            0x7f8
#define HWIO_ECPRI_UDP_C2C_EGRESS_CONFIG_p_BYPASSED_PACKETS_VPORT_SHFT_V2                                              0x3
#define HWIO_ECPRI_UDP_C2C_EGRESS_CONFIG_p_BYPASSED_PACKETS_VPORT_ACTION_BMSK_V2                                       0x6
#define HWIO_ECPRI_UDP_C2C_EGRESS_CONFIG_p_BYPASSED_PACKETS_VPORT_ACTION_SHFT_V2                                       0x1

#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_STATUS_0_PORT_p_ADDR_V2(p)                                                (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_V2     + 0x00000900 + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_STATUS_0_PORT_p_PHYS_V2(p)                                                (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_PHYS_V2 + 0x00000900 + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_STATUS_0_PORT_p_OFFS_V2(p)                                                (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_OFFS_V2 + 0x00000900 + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_STATUS_0_PORT_p_RMSK_V2                                                          0x7
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_STATUS_0_PORT_p_MAXp_V2                                                            1
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_STATUS_0_PORT_p_ATTR_V2                                                          0x1
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_STATUS_0_PORT_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_STATUS_0_PORT_p_ADDR_V2(p), HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_STATUS_0_PORT_p_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_STATUS_0_PORT_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_STATUS_0_PORT_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_0_BMSK_V2                 0x4
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_0_SHFT_V2                 0x2
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_0_BMSK_V2                            0x2
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_0_SHFT_V2                            0x1
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_STATUS_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_0_BMSK_V2                             0x1
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_STATUS_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_0_SHFT_V2                             0x0

#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_MASK_0_PORT_p_ADDR_V2(p)                                                  (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_V2     + 0x00000920 + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_MASK_0_PORT_p_PHYS_V2(p)                                                  (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_PHYS_V2 + 0x00000920 + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_MASK_0_PORT_p_OFFS_V2(p)                                                  (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_OFFS_V2 + 0x00000920 + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_MASK_0_PORT_p_RMSK_V2                                                            0x7
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_MASK_0_PORT_p_MAXp_V2                                                              1
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_MASK_0_PORT_p_ATTR_V2                                                            0x3
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_MASK_0_PORT_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_MASK_0_PORT_p_ADDR_V2(p), HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_MASK_0_PORT_p_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_MASK_0_PORT_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_MASK_0_PORT_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_MASK_0_PORT_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_MASK_0_PORT_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_MASK_0_PORT_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_MASK_0_PORT_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_MASK_0_PORT_p_INI_V2(p))
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_0_BMSK_V2                   0x4
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_0_SHFT_V2                   0x2
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_0_BMSK_V2                              0x2
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_0_SHFT_V2                              0x1
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_MASK_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_0_BMSK_V2                               0x1
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_MASK_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_0_SHFT_V2                               0x0

#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_CLR_0_PORT_p_ADDR_V2(p)                                                   (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_V2     + 0x00000940 + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_CLR_0_PORT_p_PHYS_V2(p)                                                   (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_PHYS_V2 + 0x00000940 + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_CLR_0_PORT_p_OFFS_V2(p)                                                   (ECPRI_UDP_C2C_UDP_C2C_REGS_REG_BASE_OFFS_V2 + 0x00000940 + 0x4 * (p))
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_CLR_0_PORT_p_RMSK_V2                                                             0x7
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_CLR_0_PORT_p_MAXp_V2                                                               1
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_CLR_0_PORT_p_ATTR_V2                                                             0x2
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_CLR_0_PORT_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_CLR_0_PORT_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_0_BMSK_V2                    0x4
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_0_SHFT_V2                    0x2
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_0_BMSK_V2                               0x2
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_0_SHFT_V2                               0x1
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_CLR_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_0_BMSK_V2                                0x1
#define HWIO_ECPRI_UDP_C2C_UDP_SW_IRQ_CLR_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_0_SHFT_V2                                0x0

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_UDP_C2C_UDP_C2C_RAMS
 *--------------------------------------------------------------------------*/

#define ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_V2                                                        (ECPRI_WRAPPER_BASE      + 0x003b4000)
#define ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_PHYS_V2                                                    (ECPRI_WRAPPER_BASE_PHYS + 0x003b4000)
#define ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_OFFS_V2                                                    0x003b4000

#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                      (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_V2     + 0x00000000 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                      (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_PHYS_V2 + 0x00000000 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                      (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_OFFS_V2 + 0x00000000 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_RMSK_V2                           0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_MAXp_V2                                    1
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_MAXn_V2                                    0
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_ATTR_V2                                  0x1
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                     0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                            0x0

#define HWIO_ECPRI_UDP_C2C_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                          (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_V2     + 0x00000004 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                          (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_PHYS_V2 + 0x00000004 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                          (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_OFFS_V2 + 0x00000004 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_RMSK_V2                               0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_MAXp_V2                                        1
#define HWIO_ECPRI_UDP_C2C_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_MAXn_V2                                        0
#define HWIO_ECPRI_UDP_C2C_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_ATTR_V2                                      0x1
#define HWIO_ECPRI_UDP_C2C_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_C2C_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_C2C_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                         0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                                0x0

#define HWIO_ECPRI_UDP_C2C_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                    (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_V2     + 0x00000008 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                    (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_PHYS_V2 + 0x00000008 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                    (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_OFFS_V2 + 0x00000008 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_RMSK_V2                         0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_MAXp_V2                                  1
#define HWIO_ECPRI_UDP_C2C_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_MAXn_V2                                  0
#define HWIO_ECPRI_UDP_C2C_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_ATTR_V2                                0x1
#define HWIO_ECPRI_UDP_C2C_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_C2C_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_C2C_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                   0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                          0x0

#define HWIO_ECPRI_UDP_C2C_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                     (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_V2     + 0x0000000c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                     (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_PHYS_V2 + 0x0000000c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                     (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_OFFS_V2 + 0x0000000c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_RMSK_V2                          0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_MAXp_V2                                   1
#define HWIO_ECPRI_UDP_C2C_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_MAXn_V2                                   0
#define HWIO_ECPRI_UDP_C2C_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_ATTR_V2                                 0x1
#define HWIO_ECPRI_UDP_C2C_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_C2C_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_C2C_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                    0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                           0x0

#define HWIO_ECPRI_UDP_C2C_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                      (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_V2     + 0x00000010 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                      (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_PHYS_V2 + 0x00000010 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                      (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_OFFS_V2 + 0x00000010 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_RMSK_V2                           0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_MAXp_V2                                    1
#define HWIO_ECPRI_UDP_C2C_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_MAXn_V2                                    0
#define HWIO_ECPRI_UDP_C2C_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_ATTR_V2                                  0x1
#define HWIO_ECPRI_UDP_C2C_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_C2C_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_C2C_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                     0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                            0x0

#define HWIO_ECPRI_UDP_C2C_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                    (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_V2     + 0x00000014 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                    (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_PHYS_V2 + 0x00000014 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                    (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_OFFS_V2 + 0x00000014 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_RMSK_V2                         0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_MAXp_V2                                  1
#define HWIO_ECPRI_UDP_C2C_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_MAXn_V2                                  0
#define HWIO_ECPRI_UDP_C2C_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_ATTR_V2                                0x1
#define HWIO_ECPRI_UDP_C2C_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_C2C_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_C2C_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                   0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                          0x0

#define HWIO_ECPRI_UDP_C2C_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                          (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_V2     + 0x00000018 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                          (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_PHYS_V2 + 0x00000018 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                          (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_OFFS_V2 + 0x00000018 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_RMSK_V2                               0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_MAXp_V2                                        1
#define HWIO_ECPRI_UDP_C2C_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_MAXn_V2                                        0
#define HWIO_ECPRI_UDP_C2C_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_ATTR_V2                                      0x1
#define HWIO_ECPRI_UDP_C2C_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_C2C_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_C2C_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                         0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                                0x0

#define HWIO_ECPRI_UDP_C2C_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                       (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_V2     + 0x0000001c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                       (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_PHYS_V2 + 0x0000001c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                       (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_OFFS_V2 + 0x0000001c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_RMSK_V2                            0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_MAXp_V2                                     1
#define HWIO_ECPRI_UDP_C2C_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_MAXn_V2                                     0
#define HWIO_ECPRI_UDP_C2C_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_ATTR_V2                                   0x1
#define HWIO_ECPRI_UDP_C2C_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_C2C_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_C2C_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                      0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                             0x0

#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                    (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_V2     + 0x00000020 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                    (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_PHYS_V2 + 0x00000020 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                    (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_OFFS_V2 + 0x00000020 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_RMSK_V2                         0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_MAXp_V2                                  1
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_MAXn_V2                                  0
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_ATTR_V2                                0x1
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                   0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                          0x0

#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                      (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_V2     + 0x00000024 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                      (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_PHYS_V2 + 0x00000024 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                      (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_OFFS_V2 + 0x00000024 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_RMSK_V2                           0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_MAXp_V2                                    1
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_MAXn_V2                                    0
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_ATTR_V2                                  0x1
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                     0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                            0x0

#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                    (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_V2     + 0x00000028 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                    (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_PHYS_V2 + 0x00000028 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                    (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_OFFS_V2 + 0x00000028 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_RMSK_V2                         0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_MAXp_V2                                  1
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_MAXn_V2                                  0
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_ATTR_V2                                0x1
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                   0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                          0x0

#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)           (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_V2     + 0x0000002c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)           (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_PHYS_V2 + 0x0000002c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)           (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_OFFS_V2 + 0x0000002c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_RMSK_V2                0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_MAXp_V2                         1
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_MAXn_V2                         0
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_ATTR_V2                       0x1
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2          0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                 0x0

#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                      (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_V2     + 0x00000030 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                      (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_PHYS_V2 + 0x00000030 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                      (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_OFFS_V2 + 0x00000030 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_RMSK_V2                           0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_MAXp_V2                                    1
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_MAXn_V2                                    0
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_ATTR_V2                                  0x1
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                     0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                            0x0

#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                    (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_V2     + 0x00000034 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                    (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_PHYS_V2 + 0x00000034 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                    (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_OFFS_V2 + 0x00000034 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_RMSK_V2                         0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_MAXp_V2                                  1
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_MAXn_V2                                  0
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_ATTR_V2                                0x1
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                   0xffffffff
#define HWIO_ECPRI_UDP_C2C_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                          0x0

#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                           (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_V2     + 0x00000038 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                           (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_PHYS_V2 + 0x00000038 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                           (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_OFFS_V2 + 0x00000038 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_RMSK_V2                                0xffffffff
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_MAXp_V2                                         1
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_MAXn_V2                                         0
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_ATTR_V2                                       0x1
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_C2C_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                          0xffffffff
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                                 0x0

#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                      (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_V2     + 0x0000003c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                      (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_PHYS_V2 + 0x0000003c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                      (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_OFFS_V2 + 0x0000003c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_RMSK_V2                           0xffffffff
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_MAXp_V2                                    1
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_MAXn_V2                                    0
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_ATTR_V2                                  0x1
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_C2C_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                     0xffffffff
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                            0x0

#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                      (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_V2     + 0x00000040 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                      (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_PHYS_V2 + 0x00000040 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                      (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_OFFS_V2 + 0x00000040 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_RMSK_V2                           0xffffffff
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_MAXp_V2                                    1
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_MAXn_V2                                    0
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_ATTR_V2                                  0x1
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_C2C_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                     0xffffffff
#define HWIO_ECPRI_UDP_C2C_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                            0x0

#define HWIO_ECPRI_UDP_C2C_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                           (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_V2     + 0x00000044 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                           (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_PHYS_V2 + 0x00000044 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                           (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_OFFS_V2 + 0x00000044 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_RMSK_V2                                0xffffffff
#define HWIO_ECPRI_UDP_C2C_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_MAXp_V2                                         1
#define HWIO_ECPRI_UDP_C2C_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_MAXn_V2                                         0
#define HWIO_ECPRI_UDP_C2C_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_ATTR_V2                                       0x1
#define HWIO_ECPRI_UDP_C2C_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_C2C_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_C2C_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                          0xffffffff
#define HWIO_ECPRI_UDP_C2C_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                                 0x0

#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_DST0_PORT_p_ENTRY_n_ADDR_V2(p,n)                                 (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_V2     + 0x00001000 + 0x20 * (n) + 0x20 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_DST0_PORT_p_ENTRY_n_PHYS_V2(p,n)                                 (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_PHYS_V2 + 0x00001000 + 0x20 * (n) + 0x20 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_DST0_PORT_p_ENTRY_n_OFFS_V2(p,n)                                 (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_OFFS_V2 + 0x00001000 + 0x20 * (n) + 0x20 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_DST0_PORT_p_ENTRY_n_RMSK_V2                                      0xffffffff
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_DST0_PORT_p_ENTRY_n_MAXp_V2                                               1
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_DST0_PORT_p_ENTRY_n_MAXn_V2                                               0
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_DST0_PORT_p_ENTRY_n_ATTR_V2                                             0x3
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_DST0_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_EGRESS_ETH_DST0_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_C2C_EGRESS_ETH_DST0_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_DST0_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_EGRESS_ETH_DST0_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_DST0_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_C2C_EGRESS_ETH_DST0_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_DST0_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_C2C_EGRESS_ETH_DST0_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_C2C_EGRESS_ETH_DST0_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_DST0_PORT_p_ENTRY_n_VALUE_BMSK_V2                                0xffffffff
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_DST0_PORT_p_ENTRY_n_VALUE_SHFT_V2                                       0x0

#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_ADDR_V2(p,n)                            (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_V2     + 0x00001004 + 0x20 * (n) + 0x20 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_PHYS_V2(p,n)                            (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_PHYS_V2 + 0x00001004 + 0x20 * (n) + 0x20 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_OFFS_V2(p,n)                            (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_OFFS_V2 + 0x00001004 + 0x20 * (n) + 0x20 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_RMSK_V2                                 0xffffffff
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_MAXp_V2                                          1
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_MAXn_V2                                          0
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_ATTR_V2                                        0x3
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_SRC_MSB_BMSK_V2                         0xffff0000
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_SRC_MSB_SHFT_V2                               0x10
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_DST_MSB_BMSK_V2                             0xffff
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_DST_MSB_SHFT_V2                                0x0

#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_ADDR_V2(p,n)                                 (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_V2     + 0x00001008 + 0x20 * (n) + 0x20 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_PHYS_V2(p,n)                                 (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_PHYS_V2 + 0x00001008 + 0x20 * (n) + 0x20 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_OFFS_V2(p,n)                                 (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_OFFS_V2 + 0x00001008 + 0x20 * (n) + 0x20 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_RMSK_V2                                      0xffffffff
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_MAXp_V2                                               1
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_MAXn_V2                                               0
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_ATTR_V2                                             0x3
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_VALUE_BMSK_V2                                0xffffffff
#define HWIO_ECPRI_UDP_C2C_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_VALUE_SHFT_V2                                       0x0

#define HWIO_ECPRI_UDP_C2C_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_ADDR_V2(p,n)                           (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_V2     + 0x0000100c + 0x20 * (n) + 0x20 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_PHYS_V2(p,n)                           (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_PHYS_V2 + 0x0000100c + 0x20 * (n) + 0x20 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_OFFS_V2(p,n)                           (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_OFFS_V2 + 0x0000100c + 0x20 * (n) + 0x20 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_RMSK_V2                                0xffffffff
#define HWIO_ECPRI_UDP_C2C_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_MAXp_V2                                         1
#define HWIO_ECPRI_UDP_C2C_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_MAXn_V2                                         0
#define HWIO_ECPRI_UDP_C2C_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_ATTR_V2                                       0x3
#define HWIO_ECPRI_UDP_C2C_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_C2C_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_C2C_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_C2C_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_C2C_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_C2C_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_C2C_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_C2C_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_VLAN_DATA_BMSK_V2                      0xffff0000
#define HWIO_ECPRI_UDP_C2C_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_VLAN_DATA_SHFT_V2                            0x10
#define HWIO_ECPRI_UDP_C2C_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_ETHERTYPE_BMSK_V2                          0xffff
#define HWIO_ECPRI_UDP_C2C_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_ETHERTYPE_SHFT_V2                             0x0

#define HWIO_ECPRI_UDP_C2C_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n)                               (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_V2     + 0x00001010 + 0x20 * (n) + 0x20 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_PHYS_V2(p,n)                               (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_PHYS_V2 + 0x00001010 + 0x20 * (n) + 0x20 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_OFFS_V2(p,n)                               (ECPRI_UDP_C2C_UDP_C2C_RAMS_REG_BASE_OFFS_V2 + 0x00001010 + 0x20 * (n) + 0x20 * (p))
#define HWIO_ECPRI_UDP_C2C_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_RMSK_V2                                        0x7fff
#define HWIO_ECPRI_UDP_C2C_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_MAXp_V2                                             1
#define HWIO_ECPRI_UDP_C2C_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_MAXn_V2                                             0
#define HWIO_ECPRI_UDP_C2C_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_ATTR_V2                                           0x3
#define HWIO_ECPRI_UDP_C2C_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_C2C_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_C2C_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_C2C_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_C2C_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_C2C_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_C2C_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_C2C_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_C2C_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_C2C_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_RSVD_BMSK_V2                                   0x7800
#define HWIO_ECPRI_UDP_C2C_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_RSVD_SHFT_V2                                      0xb
#define HWIO_ECPRI_UDP_C2C_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_VPORT_ACTION_BMSK_V2                            0x600
#define HWIO_ECPRI_UDP_C2C_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_VPORT_ACTION_SHFT_V2                              0x9
#define HWIO_ECPRI_UDP_C2C_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_HAS_VLAN_BMSK_V2                                0x100
#define HWIO_ECPRI_UDP_C2C_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_HAS_VLAN_SHFT_V2                                  0x8
#define HWIO_ECPRI_UDP_C2C_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_VPORT_BMSK_V2                                    0xff
#define HWIO_ECPRI_UDP_C2C_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_VPORT_SHFT_V2                                     0x0

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_UDP_L2_UDP_L2_REGS
 *--------------------------------------------------------------------------*/

#define ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2                                                                           (ECPRI_WRAPPER_BASE      + 0x003e0000)
#define ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2                                                                       (ECPRI_WRAPPER_BASE_PHYS + 0x003e0000)
#define ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2                                                                       0x003e0000

#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_ADDR_V2(p)                                                                   (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000000 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_PHYS_V2(p)                                                                   (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000000 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_OFFS_V2(p)                                                                   (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000000 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_RMSK_V2                                                                      0x27ffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_MAXp_V2                                                                               0
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_ATTR_V2                                                                             0x3
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_ADDR_V2(p), HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_INI_V2(p))
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_ENABLE_ETH_PADDING_REMOVAL_BMSK_V2                                           0x20000000
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_ENABLE_ETH_PADDING_REMOVAL_SHFT_V2                                                 0x1d
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_NON_LOCAL_DST_ACTION_BMSK_V2                                                  0x7000000
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_NON_LOCAL_DST_ACTION_SHFT_V2                                                       0x18
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_LAST_IN_CHAIN_BMSK_V2                                                          0x800000
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_LAST_IN_CHAIN_SHFT_V2                                                              0x17
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_ENABLE_BROADCAST_CHECK_BMSK_V2                                                 0x400000
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_ENABLE_BROADCAST_CHECK_SHFT_V2                                                     0x16
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_USE_EXTERNAL_NOT_LOCAL_MAC_DST_BMSK_V2                                         0x200000
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_USE_EXTERNAL_NOT_LOCAL_MAC_DST_SHFT_V2                                             0x15
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_ENABLE_MAC_DST_CHECK_BMSK_V2                                                   0x100000
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_ENABLE_MAC_DST_CHECK_SHFT_V2                                                       0x14
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_IP_FILT_MISS_ACTION_BMSK_V2                                                     0xc0000
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_IP_FILT_MISS_ACTION_SHFT_V2                                                        0x12
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_VLAN_FILT_MISS_ACTION_BMSK_V2                                                   0x30000
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_VLAN_FILT_MISS_ACTION_SHFT_V2                                                      0x10
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_DISABLE_ST_AND_FW_BMSK_V2                                                        0x8000
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_DISABLE_ST_AND_FW_SHFT_V2                                                           0xf
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_IP_LEN_ERR_ACTION_BMSK_V2                                                        0x6000
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_IP_LEN_ERR_ACTION_SHFT_V2                                                           0xd
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_PKT_ERR_ACTION_BMSK_V2                                                           0x1800
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_PKT_ERR_ACTION_SHFT_V2                                                              0xb
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_FCS_ERR_ACTION_BMSK_V2                                                            0x600
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_FCS_ERR_ACTION_SHFT_V2                                                              0x9
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_UDP_CS_ERR_ACTION_BMSK_V2                                                         0x180
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_UDP_CS_ERR_ACTION_SHFT_V2                                                           0x7
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_IPV4_CS_ERR_ACTION_BMSK_V2                                                         0x60
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_IPV4_CS_ERR_ACTION_SHFT_V2                                                          0x5
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_ENABLE_IP_LEN_CHECK_BMSK_V2                                                        0x10
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_ENABLE_IP_LEN_CHECK_SHFT_V2                                                         0x4
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_ENABLE_UDP_CS_CHECK_BMSK_V2                                                         0x8
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_ENABLE_UDP_CS_CHECK_SHFT_V2                                                         0x3
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_ENABLE_VLAN_FILT_BMSK_V2                                                            0x4
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_ENABLE_VLAN_FILT_SHFT_V2                                                            0x2
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_ENABLE_UDP_DST_CLASS_BMSK_V2                                                        0x2
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_ENABLE_UDP_DST_CLASS_SHFT_V2                                                        0x1
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_ENABLE_IP_DST_FILT_BMSK_V2                                                          0x1
#define HWIO_ECPRI_UDP_L2_INGRESS_CONFIG_p_ENABLE_IP_DST_FILT_SHFT_V2                                                          0x0

#define HWIO_ECPRI_UDP_L2_WORDS_BEFORE_TRANSMITTING_p_ADDR_V2(p)                                                        (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x0000000c + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_WORDS_BEFORE_TRANSMITTING_p_PHYS_V2(p)                                                        (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x0000000c + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_WORDS_BEFORE_TRANSMITTING_p_OFFS_V2(p)                                                        (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x0000000c + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_WORDS_BEFORE_TRANSMITTING_p_RMSK_V2                                                                 0xff
#define HWIO_ECPRI_UDP_L2_WORDS_BEFORE_TRANSMITTING_p_MAXp_V2                                                                    0
#define HWIO_ECPRI_UDP_L2_WORDS_BEFORE_TRANSMITTING_p_ATTR_V2                                                                  0x3
#define HWIO_ECPRI_UDP_L2_WORDS_BEFORE_TRANSMITTING_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_WORDS_BEFORE_TRANSMITTING_p_ADDR_V2(p), HWIO_ECPRI_UDP_L2_WORDS_BEFORE_TRANSMITTING_p_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_WORDS_BEFORE_TRANSMITTING_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_WORDS_BEFORE_TRANSMITTING_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_L2_WORDS_BEFORE_TRANSMITTING_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_WORDS_BEFORE_TRANSMITTING_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_L2_WORDS_BEFORE_TRANSMITTING_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_WORDS_BEFORE_TRANSMITTING_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_L2_WORDS_BEFORE_TRANSMITTING_p_INI_V2(p))
#define HWIO_ECPRI_UDP_L2_WORDS_BEFORE_TRANSMITTING_p_VALUE_BMSK_V2                                                           0xff
#define HWIO_ECPRI_UDP_L2_WORDS_BEFORE_TRANSMITTING_p_VALUE_SHFT_V2                                                            0x0

#define HWIO_ECPRI_UDP_L2_UDP_PTP_PORT_NUM_p_ADDR_V2(p)                                                                 (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000018 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_UDP_PTP_PORT_NUM_p_PHYS_V2(p)                                                                 (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000018 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_UDP_PTP_PORT_NUM_p_OFFS_V2(p)                                                                 (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000018 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_UDP_PTP_PORT_NUM_p_RMSK_V2                                                                        0xffff
#define HWIO_ECPRI_UDP_L2_UDP_PTP_PORT_NUM_p_MAXp_V2                                                                             0
#define HWIO_ECPRI_UDP_L2_UDP_PTP_PORT_NUM_p_ATTR_V2                                                                           0x3
#define HWIO_ECPRI_UDP_L2_UDP_PTP_PORT_NUM_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_UDP_PTP_PORT_NUM_p_ADDR_V2(p), HWIO_ECPRI_UDP_L2_UDP_PTP_PORT_NUM_p_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_UDP_PTP_PORT_NUM_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_UDP_PTP_PORT_NUM_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_L2_UDP_PTP_PORT_NUM_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_UDP_PTP_PORT_NUM_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_L2_UDP_PTP_PORT_NUM_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_UDP_PTP_PORT_NUM_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_L2_UDP_PTP_PORT_NUM_p_INI_V2(p))
#define HWIO_ECPRI_UDP_L2_UDP_PTP_PORT_NUM_p_VALUE_BMSK_V2                                                                  0xffff
#define HWIO_ECPRI_UDP_L2_UDP_PTP_PORT_NUM_p_VALUE_SHFT_V2                                                                     0x0

#define HWIO_ECPRI_UDP_L2_ECPRI_ETHERTYPE_p_ADDR_V2(p)                                                                  (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x0000002c + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_ECPRI_ETHERTYPE_p_PHYS_V2(p)                                                                  (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x0000002c + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_ECPRI_ETHERTYPE_p_OFFS_V2(p)                                                                  (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x0000002c + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_ECPRI_ETHERTYPE_p_RMSK_V2                                                                         0xffff
#define HWIO_ECPRI_UDP_L2_ECPRI_ETHERTYPE_p_MAXp_V2                                                                              0
#define HWIO_ECPRI_UDP_L2_ECPRI_ETHERTYPE_p_ATTR_V2                                                                            0x3
#define HWIO_ECPRI_UDP_L2_ECPRI_ETHERTYPE_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_ECPRI_ETHERTYPE_p_ADDR_V2(p), HWIO_ECPRI_UDP_L2_ECPRI_ETHERTYPE_p_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_ECPRI_ETHERTYPE_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_ECPRI_ETHERTYPE_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_L2_ECPRI_ETHERTYPE_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_ECPRI_ETHERTYPE_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_L2_ECPRI_ETHERTYPE_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_ECPRI_ETHERTYPE_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_L2_ECPRI_ETHERTYPE_p_INI_V2(p))
#define HWIO_ECPRI_UDP_L2_ECPRI_ETHERTYPE_p_VALUE_BMSK_V2                                                                   0xffff
#define HWIO_ECPRI_UDP_L2_ECPRI_ETHERTYPE_p_VALUE_SHFT_V2                                                                      0x0

#define HWIO_ECPRI_UDP_L2_PTP_ETHERTYPE_p_ADDR_V2(p)                                                                    (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000038 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_PTP_ETHERTYPE_p_PHYS_V2(p)                                                                    (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000038 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_PTP_ETHERTYPE_p_OFFS_V2(p)                                                                    (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000038 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_PTP_ETHERTYPE_p_RMSK_V2                                                                           0xffff
#define HWIO_ECPRI_UDP_L2_PTP_ETHERTYPE_p_MAXp_V2                                                                                0
#define HWIO_ECPRI_UDP_L2_PTP_ETHERTYPE_p_ATTR_V2                                                                              0x3
#define HWIO_ECPRI_UDP_L2_PTP_ETHERTYPE_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_PTP_ETHERTYPE_p_ADDR_V2(p), HWIO_ECPRI_UDP_L2_PTP_ETHERTYPE_p_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_PTP_ETHERTYPE_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_PTP_ETHERTYPE_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_L2_PTP_ETHERTYPE_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_PTP_ETHERTYPE_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_L2_PTP_ETHERTYPE_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_PTP_ETHERTYPE_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_L2_PTP_ETHERTYPE_p_INI_V2(p))
#define HWIO_ECPRI_UDP_L2_PTP_ETHERTYPE_p_VALUE_BMSK_V2                                                                     0xffff
#define HWIO_ECPRI_UDP_L2_PTP_ETHERTYPE_p_VALUE_SHFT_V2                                                                        0x0

#define HWIO_ECPRI_UDP_L2_FILT_ERROR_CHANNEL_CFG_p_ADDR_V2(p)                                                           (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000044 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_ERROR_CHANNEL_CFG_p_PHYS_V2(p)                                                           (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000044 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_ERROR_CHANNEL_CFG_p_OFFS_V2(p)                                                           (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000044 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_ERROR_CHANNEL_CFG_p_RMSK_V2                                                                     0x3
#define HWIO_ECPRI_UDP_L2_FILT_ERROR_CHANNEL_CFG_p_MAXp_V2                                                                       0
#define HWIO_ECPRI_UDP_L2_FILT_ERROR_CHANNEL_CFG_p_ATTR_V2                                                                     0x3
#define HWIO_ECPRI_UDP_L2_FILT_ERROR_CHANNEL_CFG_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_FILT_ERROR_CHANNEL_CFG_p_ADDR_V2(p), HWIO_ECPRI_UDP_L2_FILT_ERROR_CHANNEL_CFG_p_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_FILT_ERROR_CHANNEL_CFG_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_FILT_ERROR_CHANNEL_CFG_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_L2_FILT_ERROR_CHANNEL_CFG_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_FILT_ERROR_CHANNEL_CFG_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_L2_FILT_ERROR_CHANNEL_CFG_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_FILT_ERROR_CHANNEL_CFG_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_L2_FILT_ERROR_CHANNEL_CFG_p_INI_V2(p))
#define HWIO_ECPRI_UDP_L2_FILT_ERROR_CHANNEL_CFG_p_SEND_IP_FILT_MISS_TO_ERROR_CHANNEL_BMSK_V2                                  0x2
#define HWIO_ECPRI_UDP_L2_FILT_ERROR_CHANNEL_CFG_p_SEND_IP_FILT_MISS_TO_ERROR_CHANNEL_SHFT_V2                                  0x1
#define HWIO_ECPRI_UDP_L2_FILT_ERROR_CHANNEL_CFG_p_SEND_VLAN_FILT_MISS_TO_ERROR_CHANNEL_BMSK_V2                                0x1
#define HWIO_ECPRI_UDP_L2_FILT_ERROR_CHANNEL_CFG_p_SEND_VLAN_FILT_MISS_TO_ERROR_CHANNEL_SHFT_V2                                0x0

#define HWIO_ECPRI_UDP_L2_TRAP_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n)                                                         (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000060 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_MISC_PORT_p_ENTRY_n_PHYS_V2(p,n)                                                         (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000060 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_MISC_PORT_p_ENTRY_n_OFFS_V2(p,n)                                                         (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000060 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_MISC_PORT_p_ENTRY_n_RMSK_V2                                                                 0xfffff
#define HWIO_ECPRI_UDP_L2_TRAP_MISC_PORT_p_ENTRY_n_MAXp_V2                                                                       0
#define HWIO_ECPRI_UDP_L2_TRAP_MISC_PORT_p_ENTRY_n_MAXn_V2                                                                       3
#define HWIO_ECPRI_UDP_L2_TRAP_MISC_PORT_p_ENTRY_n_ATTR_V2                                                                     0x3
#define HWIO_ECPRI_UDP_L2_TRAP_MISC_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_TRAP_MISC_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_TRAP_MISC_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_TRAP_MISC_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_TRAP_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_TRAP_MISC_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_TRAP_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_TRAP_MISC_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_TRAP_MISC_PORT_p_ENTRY_n_ENABLE_BMSK_V2                                                          0x80000
#define HWIO_ECPRI_UDP_L2_TRAP_MISC_PORT_p_ENTRY_n_ENABLE_SHFT_V2                                                             0x13
#define HWIO_ECPRI_UDP_L2_TRAP_MISC_PORT_p_ENTRY_n_ACTION_BMSK_V2                                                          0x70000
#define HWIO_ECPRI_UDP_L2_TRAP_MISC_PORT_p_ENTRY_n_ACTION_SHFT_V2                                                             0x10
#define HWIO_ECPRI_UDP_L2_TRAP_MISC_PORT_p_ENTRY_n_RULE32_OFFSET_BMSK_V2                                                    0xff00
#define HWIO_ECPRI_UDP_L2_TRAP_MISC_PORT_p_ENTRY_n_RULE32_OFFSET_SHFT_V2                                                       0x8
#define HWIO_ECPRI_UDP_L2_TRAP_MISC_PORT_p_ENTRY_n_RULE64_OFFSET_BMSK_V2                                                      0xff
#define HWIO_ECPRI_UDP_L2_TRAP_MISC_PORT_p_ENTRY_n_RULE64_OFFSET_SHFT_V2                                                       0x0

#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n)                                               (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000090 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_PHYS_V2(p,n)                                               (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000090 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_OFFS_V2(p,n)                                               (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000090 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_RMSK_V2                                                    0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_MAXp_V2                                                             0
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_MAXn_V2                                                             3
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_ATTR_V2                                                           0x3
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_VALUE_BMSK_V2                                              0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n_VALUE_SHFT_V2                                                     0x0

#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n)                                               (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x000000c0 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_PHYS_V2(p,n)                                               (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x000000c0 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_OFFS_V2(p,n)                                               (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x000000c0 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_RMSK_V2                                                    0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_MAXp_V2                                                             0
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_MAXn_V2                                                             3
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_ATTR_V2                                                           0x3
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_VALUE_BMSK_V2                                              0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n_VALUE_SHFT_V2                                                     0x0

#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n)                                              (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x000000f0 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_PHYS_V2(p,n)                                              (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x000000f0 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_OFFS_V2(p,n)                                              (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x000000f0 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_RMSK_V2                                                   0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_MAXp_V2                                                            0
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_MAXn_V2                                                            3
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_ATTR_V2                                                          0x3
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_VALUE_BMSK_V2                                             0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n_VALUE_SHFT_V2                                                    0x0

#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n)                                              (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000120 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_PHYS_V2(p,n)                                              (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000120 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_OFFS_V2(p,n)                                              (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000120 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_RMSK_V2                                                   0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_MAXp_V2                                                            0
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_MAXn_V2                                                            3
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_ATTR_V2                                                          0x3
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_VALUE_BMSK_V2                                             0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n_VALUE_SHFT_V2                                                    0x0

#define HWIO_ECPRI_UDP_L2_TRAP_RULE32_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n)                                                   (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000150 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_RULE32_VAL_PORT_p_ENTRY_n_PHYS_V2(p,n)                                                   (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000150 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_RULE32_VAL_PORT_p_ENTRY_n_OFFS_V2(p,n)                                                   (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000150 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_RULE32_VAL_PORT_p_ENTRY_n_RMSK_V2                                                        0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_RULE32_VAL_PORT_p_ENTRY_n_MAXp_V2                                                                 0
#define HWIO_ECPRI_UDP_L2_TRAP_RULE32_VAL_PORT_p_ENTRY_n_MAXn_V2                                                                 3
#define HWIO_ECPRI_UDP_L2_TRAP_RULE32_VAL_PORT_p_ENTRY_n_ATTR_V2                                                               0x3
#define HWIO_ECPRI_UDP_L2_TRAP_RULE32_VAL_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_RULE32_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_TRAP_RULE32_VAL_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_TRAP_RULE32_VAL_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_RULE32_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_TRAP_RULE32_VAL_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_TRAP_RULE32_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_TRAP_RULE32_VAL_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_TRAP_RULE32_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_TRAP_RULE32_VAL_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_TRAP_RULE32_VAL_PORT_p_ENTRY_n_VALUE_BMSK_V2                                                  0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_RULE32_VAL_PORT_p_ENTRY_n_VALUE_SHFT_V2                                                         0x0

#define HWIO_ECPRI_UDP_L2_TRAP_RULE32_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n)                                                  (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000180 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_RULE32_MASK_PORT_p_ENTRY_n_PHYS_V2(p,n)                                                  (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000180 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_RULE32_MASK_PORT_p_ENTRY_n_OFFS_V2(p,n)                                                  (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000180 + 0x10 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_RULE32_MASK_PORT_p_ENTRY_n_RMSK_V2                                                       0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_RULE32_MASK_PORT_p_ENTRY_n_MAXp_V2                                                                0
#define HWIO_ECPRI_UDP_L2_TRAP_RULE32_MASK_PORT_p_ENTRY_n_MAXn_V2                                                                3
#define HWIO_ECPRI_UDP_L2_TRAP_RULE32_MASK_PORT_p_ENTRY_n_ATTR_V2                                                              0x3
#define HWIO_ECPRI_UDP_L2_TRAP_RULE32_MASK_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_RULE32_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_TRAP_RULE32_MASK_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_TRAP_RULE32_MASK_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_RULE32_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_TRAP_RULE32_MASK_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_TRAP_RULE32_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_TRAP_RULE32_MASK_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_TRAP_RULE32_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_TRAP_RULE32_MASK_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_TRAP_RULE32_MASK_PORT_p_ENTRY_n_VALUE_BMSK_V2                                                 0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_RULE32_MASK_PORT_p_ENTRY_n_VALUE_SHFT_V2                                                        0x0

#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_ADDR_V2(p,n)                                            (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x000001b0 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_PHYS_V2(p,n)                                            (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x000001b0 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_OFFS_V2(p,n)                                            (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x000001b0 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_RMSK_V2                                                     0xffff
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_MAXp_V2                                                          0
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_MAXn_V2                                                          1
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_ATTR_V2                                                        0x3
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_LARGE_SET_RULE32_OFFSET_BMSK_V2                             0xff00
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_LARGE_SET_RULE32_OFFSET_SHFT_V2                                0x8
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_LARGE_SET_RULE128_OFFSET_BMSK_V2                              0xff
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n_LARGE_SET_RULE128_OFFSET_SHFT_V2                               0x0

#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n)                                         (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x000001c8 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_PHYS_V2(p,n)                                         (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x000001c8 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_OFFS_V2(p,n)                                         (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x000001c8 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_RMSK_V2                                              0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_MAXp_V2                                                       0
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_MAXn_V2                                                       1
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_ATTR_V2                                                     0x3
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_VALUE_BMSK_V2                                        0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n_VALUE_SHFT_V2                                               0x0

#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n)                                        (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x000001e0 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_PHYS_V2(p,n)                                        (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x000001e0 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_OFFS_V2(p,n)                                        (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x000001e0 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_RMSK_V2                                             0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_MAXp_V2                                                      0
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_MAXn_V2                                                      1
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_ATTR_V2                                                    0x3
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_VALUE_BMSK_V2                                       0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n_VALUE_SHFT_V2                                              0x0

#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n)                                      (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x000001f8 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_PHYS_V2(p,n)                                      (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x000001f8 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_OFFS_V2(p,n)                                      (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x000001f8 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_RMSK_V2                                           0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_MAXp_V2                                                    0
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_MAXn_V2                                                    1
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_ATTR_V2                                                  0x3
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_VALUE_BMSK_V2                                     0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n_VALUE_SHFT_V2                                            0x0

#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n)                                     (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000210 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_PHYS_V2(p,n)                                     (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000210 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_OFFS_V2(p,n)                                     (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000210 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_RMSK_V2                                          0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_MAXp_V2                                                   0
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_MAXn_V2                                                   1
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_ATTR_V2                                                 0x3
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_VALUE_BMSK_V2                                    0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n_VALUE_SHFT_V2                                           0x0

#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n)                                      (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000228 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_PHYS_V2(p,n)                                      (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000228 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_OFFS_V2(p,n)                                      (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000228 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_RMSK_V2                                           0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_MAXp_V2                                                    0
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_MAXn_V2                                                    1
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_ATTR_V2                                                  0x3
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_VALUE_BMSK_V2                                     0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n_VALUE_SHFT_V2                                            0x0

#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n)                                     (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000240 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_PHYS_V2(p,n)                                     (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000240 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_OFFS_V2(p,n)                                     (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000240 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_RMSK_V2                                          0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_MAXp_V2                                                   0
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_MAXn_V2                                                   1
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_ATTR_V2                                                 0x3
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_VALUE_BMSK_V2                                    0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n_VALUE_SHFT_V2                                           0x0

#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n)                                      (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000258 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_PHYS_V2(p,n)                                      (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000258 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_OFFS_V2(p,n)                                      (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000258 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_RMSK_V2                                           0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_MAXp_V2                                                    0
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_MAXn_V2                                                    1
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_ATTR_V2                                                  0x3
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_VALUE_BMSK_V2                                     0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n_VALUE_SHFT_V2                                            0x0

#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n)                                     (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000270 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_PHYS_V2(p,n)                                     (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000270 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_OFFS_V2(p,n)                                     (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000270 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_RMSK_V2                                          0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_MAXp_V2                                                   0
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_MAXn_V2                                                   1
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_ATTR_V2                                                 0x3
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_VALUE_BMSK_V2                                    0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n_VALUE_SHFT_V2                                           0x0

#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n)                                      (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000288 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_PHYS_V2(p,n)                                      (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000288 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_OFFS_V2(p,n)                                      (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000288 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_RMSK_V2                                           0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_MAXp_V2                                                    0
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_MAXn_V2                                                    1
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_ATTR_V2                                                  0x3
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_VALUE_BMSK_V2                                     0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n_VALUE_SHFT_V2                                            0x0

#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n)                                     (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x000002a0 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_PHYS_V2(p,n)                                     (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x000002a0 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_OFFS_V2(p,n)                                     (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x000002a0 + 0x8 * (p) + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_RMSK_V2                                          0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_MAXp_V2                                                   0
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_MAXn_V2                                                   1
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_ATTR_V2                                                 0x3
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_VALUE_BMSK_V2                                    0xffffffff
#define HWIO_ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n_VALUE_SHFT_V2                                           0x0

#define HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_ADDR_V2(p)                                                                (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x000002b8 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_PHYS_V2(p)                                                                (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x000002b8 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_OFFS_V2(p)                                                                (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x000002b8 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_RMSK_V2                                                                         0x3f
#define HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_MAXp_V2                                                                            0
#define HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_ATTR_V2                                                                          0x3
#define HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_ADDR_V2(p), HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_INI_V2(p))
#define HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_TRAP_PTP_OVER_IPV6_WITH_VLAN_EN_BMSK_V2                                         0x20
#define HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_TRAP_PTP_OVER_IPV6_WITH_VLAN_EN_SHFT_V2                                          0x5
#define HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_TRAP_PTP_OVER_IPV6_WITHOUT_VLAN_EN_BMSK_V2                                      0x10
#define HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_TRAP_PTP_OVER_IPV6_WITHOUT_VLAN_EN_SHFT_V2                                       0x4
#define HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_TRAP_PTP_OVER_IPV4_WITH_VLAN_EN_BMSK_V2                                          0x8
#define HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_TRAP_PTP_OVER_IPV4_WITH_VLAN_EN_SHFT_V2                                          0x3
#define HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_TRAP_PTP_OVER_IPV4_WITHOUT_VLAN_EN_BMSK_V2                                       0x4
#define HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_TRAP_PTP_OVER_IPV4_WITHOUT_VLAN_EN_SHFT_V2                                       0x2
#define HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_TRAP_PTP_OVER_ETH_WITH_VLAN_EN_BMSK_V2                                           0x2
#define HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_TRAP_PTP_OVER_ETH_WITH_VLAN_EN_SHFT_V2                                           0x1
#define HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_TRAP_PTP_OVER_ETH_WITHOUT_VLAN_EN_BMSK_V2                                        0x1
#define HWIO_ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p_TRAP_PTP_OVER_ETH_WITHOUT_VLAN_EN_SHFT_V2                                        0x0

#define HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p)                                           (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x000003c0 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_PHYS_V2(p)                                           (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x000003c0 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_OFFS_V2(p)                                           (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x000003c0 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_RMSK_V2                                                  0xffff
#define HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_MAXp_V2                                                       0
#define HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_ATTR_V2                                                     0x3
#define HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p), HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_INI_V2(p))
#define HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_BMSK_V2                                       0xffff
#define HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_SHFT_V2                                          0x0

#define HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p)                                  (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x000003cc + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_PHYS_V2(p)                                  (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x000003cc + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_OFFS_V2(p)                                  (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x000003cc + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_RMSK_V2                                     0xffffffff
#define HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_MAXp_V2                                              0
#define HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_ATTR_V2                                            0x3
#define HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p), HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_INI_V2(p))
#define HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_BMSK_V2                          0xffffffff
#define HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_SHFT_V2                                 0x0

#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p)                                         (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x000003e4 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_PHYS_V2(p)                                         (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x000003e4 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_OFFS_V2(p)                                         (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x000003e4 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_RMSK_V2                                                0xffff
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_MAXp_V2                                                     0
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_ATTR_V2                                                   0x3
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p), HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_INI_V2(p))
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_BMSK_V2                                     0xffff
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_SHFT_V2                                        0x0

#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p)                                         (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x000003f0 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_PHYS_V2(p)                                         (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x000003f0 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_OFFS_V2(p)                                         (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x000003f0 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_RMSK_V2                                                   0xf
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_MAXp_V2                                                     0
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_ATTR_V2                                                   0x3
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p), HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_INI_V2(p))
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_BMSK_V2                                        0xf
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_SHFT_V2                                        0x0

#define HWIO_ECPRI_UDP_L2_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_ADDR_V2(p,n)                                            (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x000003fc + 0x4 * (n) + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_PHYS_V2(p,n)                                            (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x000003fc + 0x4 * (n) + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_OFFS_V2(p,n)                                            (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x000003fc + 0x4 * (n) + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_RMSK_V2                                                      0x3ff
#define HWIO_ECPRI_UDP_L2_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_MAXp_V2                                                          0
#define HWIO_ECPRI_UDP_L2_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_MAXn_V2                                                          0
#define HWIO_ECPRI_UDP_L2_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_ATTR_V2                                                        0x3
#define HWIO_ECPRI_UDP_L2_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_RING_ID_BMSK_V2                                              0x3fc
#define HWIO_ECPRI_UDP_L2_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_RING_ID_SHFT_V2                                                0x2
#define HWIO_ECPRI_UDP_L2_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_GSI_ID_BMSK_V2                                                 0x3
#define HWIO_ECPRI_UDP_L2_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_GSI_ID_SHFT_V2                                                 0x0

#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_ADDR_V2(p)                                                                 (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000500 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_PHYS_V2(p)                                                                 (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000500 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_OFFS_V2(p)                                                                 (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000500 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_RMSK_V2                                                                         0x7ff
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_MAXp_V2                                                                             0
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_ATTR_V2                                                                           0x1
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_ADDR_V2(p), HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_EGRESS_CS_FIFO_EMPTY_BMSK_V2                                                    0x400
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_EGRESS_CS_FIFO_EMPTY_SHFT_V2                                                      0xa
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_EGRESS_OUTPUT_FIFO_EMPTY_BMSK_V2                                                0x200
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_EGRESS_OUTPUT_FIFO_EMPTY_SHFT_V2                                                  0x9
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_EGRESS_ALIGNER_IDLE_BMSK_V2                                                     0x100
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_EGRESS_ALIGNER_IDLE_SHFT_V2                                                       0x8
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_EGRESS_PKT_FIFO_EMPTY_BMSK_V2                                                    0x80
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_EGRESS_PKT_FIFO_EMPTY_SHFT_V2                                                     0x7
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_EGRESS_HDRI_IDLE_BMSK_V2                                                         0x40
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_EGRESS_HDRI_IDLE_SHFT_V2                                                          0x6
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_EGRESS_IDLE_BMSK_V2                                                              0x20
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_EGRESS_IDLE_SHFT_V2                                                               0x5
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_INGRESS_CMD_FIFO_EMPTY_LINK_0_BMSK_V2                                            0x10
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_INGRESS_CMD_FIFO_EMPTY_LINK_0_SHFT_V2                                             0x4
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_INGRESS_PKT_FIFO_EMPTY_LINK_0_BMSK_V2                                             0x8
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_INGRESS_PKT_FIFO_EMPTY_LINK_0_SHFT_V2                                             0x3
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_INGRESS_ALIGNER_IDLE_BMSK_V2                                                      0x4
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_INGRESS_ALIGNER_IDLE_SHFT_V2                                                      0x2
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_INGRESS_IDLE_BMSK_V2                                                              0x2
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_INGRESS_IDLE_SHFT_V2                                                              0x1
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_PORT_IS_IDLE_BMSK_V2                                                              0x1
#define HWIO_ECPRI_UDP_L2_IDLE_STATUS_PORT_p_PORT_IS_IDLE_SHFT_V2                                                              0x0

#define HWIO_ECPRI_UDP_L2_CGC_CFG_ADDR_V2                                                                               (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000510)
#define HWIO_ECPRI_UDP_L2_CGC_CFG_PHYS_V2                                                                               (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000510)
#define HWIO_ECPRI_UDP_L2_CGC_CFG_OFFS_V2                                                                               (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000510)
#define HWIO_ECPRI_UDP_L2_CGC_CFG_RMSK_V2                                                                                      0x3
#define HWIO_ECPRI_UDP_L2_CGC_CFG_ATTR_V2                                                                                      0x3
#define HWIO_ECPRI_UDP_L2_CGC_CFG_IN_V2          \
        in_dword_masked(HWIO_ECPRI_UDP_L2_CGC_CFG_ADDR_V2, HWIO_ECPRI_UDP_L2_CGC_CFG_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_CGC_CFG_IN_V2M(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_L2_CGC_CFG_ADDR_V2, m)
#define HWIO_ECPRI_UDP_L2_CGC_CFG_OUT_V2(v)      \
        out_dword(HWIO_ECPRI_UDP_L2_CGC_CFG_ADDR_V2,v)
#define HWIO_ECPRI_UDP_L2_CGC_CFG_OUTM_V2(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_CGC_CFG_ADDR_V2,m,v,HWIO_ECPRI_UDP_L2_CGC_CFG_IN_V2)
#define HWIO_ECPRI_UDP_L2_CGC_CFG_EGRESS_CGC_OPEN_BMSK_V2                                                                      0x2
#define HWIO_ECPRI_UDP_L2_CGC_CFG_EGRESS_CGC_OPEN_SHFT_V2                                                                      0x1
#define HWIO_ECPRI_UDP_L2_CGC_CFG_IN_V2GRESS_CGC_OPEN_BMSK_V2                                                                     0x1
#define HWIO_ECPRI_UDP_L2_CGC_CFG_IN_V2GRESS_CGC_OPEN_SHFT_V2                                                                     0x0

#define HWIO_ECPRI_UDP_L2_HW_PARAMS_0_ADDR_V2                                                                           (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000514)
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_0_PHYS_V2                                                                           (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000514)
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_0_OFFS_V2                                                                           (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000514)
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_0_RMSK_V2                                                                           0xffffffff
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_0_ATTR_V2                                                                                  0x1
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_0_IN_V2          \
        in_dword_masked(HWIO_ECPRI_UDP_L2_HW_PARAMS_0_ADDR_V2, HWIO_ECPRI_UDP_L2_HW_PARAMS_0_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_0_INM_V2(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_L2_HW_PARAMS_0_ADDR_V2, m)
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_0_L3_SUPPORT_BMSK_V2                                                                0x80000000
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_0_L3_SUPPORT_SHFT_V2                                                                      0x1f
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_0_UDP_CLASSIFICATION_ENTRIES_N_BMSK_V2                                              0x7e000000
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_0_UDP_CLASSIFICATION_ENTRIES_N_SHFT_V2                                                    0x19
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_0_IP_TABLE_ENTRIES_N_BMSK_V2                                                         0x1ff0000
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_0_IP_TABLE_ENTRIES_N_SHFT_V2                                                              0x10
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_0_ETH_TABLE_ENTRIES_N_BMSK_V2                                                           0xff80
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_0_ETH_TABLE_ENTRIES_N_SHFT_V2                                                              0x7
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_0_LINKS_N_BMSK_V2                                                                         0x70
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_0_LINKS_N_SHFT_V2                                                                          0x4
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_0_PORTS_N_BMSK_V2                                                                          0xc
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_0_PORTS_N_SHFT_V2                                                                          0x2
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_0_INSTANCE_TYPE_BMSK_V2                                                                    0x3
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_0_INSTANCE_TYPE_SHFT_V2                                                                    0x0
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_0_INSTANCE_TYPE_FH_FVAL                                                                 0x0
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_0_INSTANCE_TYPE_C2C_FVAL                                                                0x1
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_0_INSTANCE_TYPE_L2_FVAL                                                                 0x2

#define HWIO_ECPRI_UDP_L2_HW_PARAMS_1_ADDR_V2                                                                           (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000518)
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_1_PHYS_V2                                                                           (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000518)
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_1_OFFS_V2                                                                           (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000518)
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_1_RMSK_V2                                                                               0x7fff
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_1_ATTR_V2                                                                                  0x1
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_1_IN_V2          \
        in_dword_masked(HWIO_ECPRI_UDP_L2_HW_PARAMS_1_ADDR_V2, HWIO_ECPRI_UDP_L2_HW_PARAMS_1_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_1_INM_V2(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_L2_HW_PARAMS_1_ADDR_V2, m)
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_1_ETH_DST_FILT_ENTRIES_N_BMSK_V2                                                        0x7c00
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_1_ETH_DST_FILT_ENTRIES_N_SHFT_V2                                                           0xa
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_1_IP_FILT_ENTRIES_N_BMSK_V2                                                              0x3e0
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_1_IP_FILT_ENTRIES_N_SHFT_V2                                                                0x5
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_1_VLAN_FILT_ENTRIES_N_BMSK_V2                                                             0x1f
#define HWIO_ECPRI_UDP_L2_HW_PARAMS_1_VLAN_FILT_ENTRIES_N_SHFT_V2                                                              0x0

#define HWIO_ECPRI_UDP_L2_QUDP_STAT_COUNTERS_CTL_ADDR_V2                                                                (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x0000051c)
#define HWIO_ECPRI_UDP_L2_QUDP_STAT_COUNTERS_CTL_PHYS_V2                                                                (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x0000051c)
#define HWIO_ECPRI_UDP_L2_QUDP_STAT_COUNTERS_CTL_OFFS_V2                                                                (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x0000051c)
#define HWIO_ECPRI_UDP_L2_QUDP_STAT_COUNTERS_CTL_RMSK_V2                                                                       0x3
#define HWIO_ECPRI_UDP_L2_QUDP_STAT_COUNTERS_CTL_ATTR_V2                                                                       0x3
#define HWIO_ECPRI_UDP_L2_QUDP_STAT_COUNTERS_CTL_IN_V2          \
        in_dword_masked(HWIO_ECPRI_UDP_L2_QUDP_STAT_COUNTERS_CTL_ADDR_V2, HWIO_ECPRI_UDP_L2_QUDP_STAT_COUNTERS_CTL_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_QUDP_STAT_COUNTERS_CTL_INM_V2(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_L2_QUDP_STAT_COUNTERS_CTL_ADDR_V2, m)
#define HWIO_ECPRI_UDP_L2_QUDP_STAT_COUNTERS_CTL_OUT_V2(v)      \
        out_dword(HWIO_ECPRI_UDP_L2_QUDP_STAT_COUNTERS_CTL_ADDR_V2,v)
#define HWIO_ECPRI_UDP_L2_QUDP_STAT_COUNTERS_CTL_OUTM_V2(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_QUDP_STAT_COUNTERS_CTL_ADDR_V2,m,v,HWIO_ECPRI_UDP_L2_QUDP_STAT_COUNTERS_CTL_IN_V2)
#define HWIO_ECPRI_UDP_L2_QUDP_STAT_COUNTERS_CTL_CNT_CLR_EN_BMSK_V2                                                            0x2
#define HWIO_ECPRI_UDP_L2_QUDP_STAT_COUNTERS_CTL_CNT_CLR_EN_SHFT_V2                                                            0x1
#define HWIO_ECPRI_UDP_L2_QUDP_STAT_COUNTERS_CTL_CNT_EN_BMSK_V2                                                                0x1
#define HWIO_ECPRI_UDP_L2_QUDP_STAT_COUNTERS_CTL_CNT_EN_SHFT_V2                                                                0x0

#define HWIO_ECPRI_UDP_L2_QUDP_CTL_PORT_p_ADDR_V2(p)                                                                    (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000520 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_QUDP_CTL_PORT_p_PHYS_V2(p)                                                                    (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000520 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_QUDP_CTL_PORT_p_OFFS_V2(p)                                                                    (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000520 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_QUDP_CTL_PORT_p_RMSK_V2                                                                              0x7
#define HWIO_ECPRI_UDP_L2_QUDP_CTL_PORT_p_MAXp_V2                                                                                0
#define HWIO_ECPRI_UDP_L2_QUDP_CTL_PORT_p_ATTR_V2                                                                              0x3
#define HWIO_ECPRI_UDP_L2_QUDP_CTL_PORT_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_QUDP_CTL_PORT_p_ADDR_V2(p), HWIO_ECPRI_UDP_L2_QUDP_CTL_PORT_p_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_QUDP_CTL_PORT_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_QUDP_CTL_PORT_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_L2_QUDP_CTL_PORT_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_QUDP_CTL_PORT_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_L2_QUDP_CTL_PORT_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_QUDP_CTL_PORT_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_L2_QUDP_CTL_PORT_p_INI_V2(p))
#define HWIO_ECPRI_UDP_L2_QUDP_CTL_PORT_p_DISABLE_IRQ_DELAY_BMSK_V2                                                            0x4
#define HWIO_ECPRI_UDP_L2_QUDP_CTL_PORT_p_DISABLE_IRQ_DELAY_SHFT_V2                                                            0x2
#define HWIO_ECPRI_UDP_L2_QUDP_CTL_PORT_p_SLEEP_MODE_BMSK_V2                                                                   0x2
#define HWIO_ECPRI_UDP_L2_QUDP_CTL_PORT_p_SLEEP_MODE_SHFT_V2                                                                   0x1
#define HWIO_ECPRI_UDP_L2_QUDP_CTL_PORT_p_SRES_BMSK_V2                                                                         0x1
#define HWIO_ECPRI_UDP_L2_QUDP_CTL_PORT_p_SRES_SHFT_V2                                                                         0x0

#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_ADDR_V2(p,n)                                              (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x0000052c + 0x4 * (n) + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_PHYS_V2(p,n)                                              (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x0000052c + 0x4 * (n) + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_OFFS_V2(p,n)                                              (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x0000052c + 0x4 * (n) + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_RMSK_V2                                                   0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_MAXp_V2                                                            0
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_MAXn_V2                                                            0
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_ATTR_V2                                                          0x1
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_L2_SB_FIFO_BMSK_V2                                        0xff000000
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_L2_SB_FIFO_SHFT_V2                                              0x18
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_CMD_FIFO_BMSK_V2                                            0xff0000
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_CMD_FIFO_SHFT_V2                                                0x10
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_PTP_TIMESTAMP_FIFO_BMSK_V2                                    0xe000
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_PTP_TIMESTAMP_FIFO_SHFT_V2                                       0xd
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_PKT_HANDLER_SYNC_FIFOS_BMSK_V2                                0x1c00
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_PKT_HANDLER_SYNC_FIFOS_SHFT_V2                                   0xa
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_PKT_FIFO_BMSK_V2                                               0x3ff
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_WATERMARK_PORT_p_LINK_n_PKT_FIFO_SHFT_V2                                                 0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_0_PORT_p_ADDR_V2(p)                                                      (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x0000055c + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_0_PORT_p_PHYS_V2(p)                                                      (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x0000055c + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_0_PORT_p_OFFS_V2(p)                                                      (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x0000055c + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_0_PORT_p_RMSK_V2                                                          0x1ffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_0_PORT_p_MAXp_V2                                                                  0
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_0_PORT_p_ATTR_V2                                                                0x1
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_0_PORT_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_0_PORT_p_ADDR_V2(p), HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_0_PORT_p_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_0_PORT_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_0_PORT_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_0_PORT_p_ALIGNER_OUTPUT_FIFO_BMSK_V2                                      0x1c00000
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_0_PORT_p_ALIGNER_OUTPUT_FIFO_SHFT_V2                                           0x16
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_0_PORT_p_HDRI_OUTPUT_FIFO_BMSK_V2                                          0x380000
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_0_PORT_p_HDRI_OUTPUT_FIFO_SHFT_V2                                              0x13
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_0_PORT_p_HDRI_CFG_IN_V2DEX_FIFO_BMSK_V2                                        0x7fc00
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_0_PORT_p_HDRI_CFG_IN_V2DEX_FIFO_SHFT_V2                                            0xa
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_0_PORT_p_PKT_FIFO_BMSK_V2                                                     0x3ff
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_0_PORT_p_PKT_FIFO_SHFT_V2                                                       0x0

#define HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_ADDR_V2                                                                    (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000568)
#define HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_PHYS_V2                                                                    (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000568)
#define HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_OFFS_V2                                                                    (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000568)
#define HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_RMSK_V2                                                                          0x3f
#define HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_ATTR_V2                                                                           0x3
#define HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_IN_V2          \
        in_dword_masked(HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_ADDR_V2, HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_IN_V2M(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_ADDR_V2, m)
#define HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_OUT_V2(v)      \
        out_dword(HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_ADDR_V2,v)
#define HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_OUTM_V2(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_ADDR_V2,m,v,HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_IN_V2)
#define HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_HW_EVENTS_EN_BMSK_V2                                                             0x20
#define HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_HW_EVENTS_EN_SHFT_V2                                                              0x5
#define HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_TESTBUS_EN_BMSK_V2                                                               0x10
#define HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_TESTBUS_EN_SHFT_V2                                                                0x4
#define HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_EN_CLEAR_WATERMARK_ON_READ_BMSK_V2                                                0x8
#define HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_EN_CLEAR_WATERMARK_ON_READ_SHFT_V2                                                0x3
#define HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_WATERMARK_EN_BMSK_V2                                                              0x4
#define HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_WATERMARK_EN_SHFT_V2                                                              0x2
#define HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_TPDM_OPERATION_MODE_BMSK_V2                                                       0x2
#define HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_TPDM_OPERATION_MODE_SHFT_V2                                                       0x1
#define HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_TPDM_OPERATION_MODE_DATA_MODE_FVAL                                             0x0
#define HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_TPDM_OPERATION_MODE_CONTROL_MODE_FVAL                                          0x1
#define HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_TPDM_EN_BMSK_V2                                                                   0x1
#define HWIO_ECPRI_UDP_L2_DEBUG_FEATURES_CFG_TPDM_EN_SHFT_V2                                                                   0x0

#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_ADDR_V2                                                                         (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x0000056c)
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_PHYS_V2                                                                         (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x0000056c)
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_OFFS_V2                                                                         (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x0000056c)
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_RMSK_V2                                                                          0x7fe7ff0
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_ATTR_V2                                                                                0x3
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_IN_V2          \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_ADDR_V2, HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_IN_V2M(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_ADDR_V2, m)
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_OUT_V2(v)      \
        out_dword(HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_ADDR_V2,v)
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_OUTM_V2(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_ADDR_V2,m,v,HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_IN_V2)
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_SAMPLE_ONLY_TRAPPED_PACKETS_BMSK_V2                                              0x4000000
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_SAMPLE_ONLY_TRAPPED_PACKETS_SHFT_V2                                                   0x1a
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_MAX_WORDS_TO_SEND_PER_PACKET_BMSK_V2                                             0x3fe0000
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_MAX_WORDS_TO_SEND_PER_PACKET_SHFT_V2                                                  0x11
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_SAMPLING_MODE_BMSK_V2                                                               0x6000
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_SAMPLING_MODE_SHFT_V2                                                                  0xd
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_SAMPLING_MODE_NUM_WORDS_FROM_SOP_FVAL                                               0x0
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_SAMPLING_MODE_SOP_ONLY_FVAL                                                         0x1
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_SAMPLING_MODE_EOP_ONLY_FVAL                                                         0x2
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_SAMPLING_MODE_SOP_AND_EOP_ONLY_FVAL                                                 0x3
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_SIDEBAND_INSERTION_OFFSET_BMSK_V2                                                   0x1c00
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_SIDEBAND_INSERTION_OFFSET_SHFT_V2                                                      0xa
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_SIDEBAND_INSERTION_MODE_BMSK_V2                                                      0x300
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_SIDEBAND_INSERTION_MODE_SHFT_V2                                                        0x8
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_SIDEBAND_INSERTION_MODE_INSERT_ALWAYS_FVAL                                          0x0
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_SIDEBAND_INSERTION_MODE_INSERT_ONLY_AT_SOP_FVAL                                     0x1
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_SIDEBAND_INSERTION_MODE_INSERT_ONLY_AT_EOP_FVAL                                     0x2
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_SIDEBAND_INSERTION_MODE_INSERT_AT_EOP_AND_SOP_FVAL                                  0x3
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_SIDEBAND_INSERTION_EN_BMSK_V2                                                         0x80
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_SIDEBAND_INSERTION_EN_SHFT_V2                                                          0x7
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_BUS_SEL_BMSK_V2                                                                       0x70
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_BUS_SEL_SHFT_V2                                                                        0x4
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_BUS_SEL_INGRESS_SEC2UDP_FVAL                                                        0x0
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_BUS_SEL_INGRESS_UDP2XBAR_FVAL                                                       0x1
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_BUS_SEL_EGRESS_XBAR2UDP_FVAL                                                        0x2
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_BUS_SEL_EGRESS_UDP2SEC_FVAL                                                         0x3
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_BUS_SEL_EGRESS_HDRI_OUTPUT_FVAL                                                     0x4
#define HWIO_ECPRI_UDP_L2_TPDM_DATA_CFG_BUS_SEL_EGRESS_CS_UPDATE_OUTPUT_FVAL                                                0x5

#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_ADDR                                                                    (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000570)
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_PHYS                                                                    (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000570)
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_OFFS                                                                    (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000570)
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_RMSK_V2                                                                     0xffffff0
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_ATTR_V2                                                                           0x3
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_IN          \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_ADDR, HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_INM(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_ADDR, m)
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_OUT_V2(v)      \
        out_dword(HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_ADDR,v)
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_OUTM_V2(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_ADDR,m,v,HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_IN)
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_ARBITRARY_TESTBUS_2_SEL_BMSK_V2                                             0xfe00000
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_ARBITRARY_TESTBUS_2_SEL_SHFT_V2                                                  0x15
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_ARBITRARY_TESTBUS_1_SEL_BMSK_V2                                              0x1fc000
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_ARBITRARY_TESTBUS_1_SEL_SHFT_V2                                                   0xe
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_ARBITRARY_TESTBUS_0_SEL_BMSK_V2                                                0x3f80
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_ARBITRARY_TESTBUS_0_SEL_SHFT_V2                                                   0x7
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_BUS_SEL_BMSK_V2                                                                  0x70
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_BUS_SEL_SHFT_V2                                                                   0x4
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_BUS_SEL_INGRESS_PKT_HANDLER_FVAL                                               0x0
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_BUS_SEL_INGRESS_PKT_HANDLER_WHITELISTS_FVAL                                    0x1
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_BUS_SEL_INGRESS_PORT_TOP_FVAL                                                  0x2
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_BUS_SEL_EGRESS_HDRI_FVAL                                                       0x3
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_BUS_SEL_EGRESS_PORT_TOP_FVAL                                                   0x4
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_0_BUS_SEL_ARBITRARY_TESTBUSES_FVAL                                               0x5

#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_1_ADDR                                                                    (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000574)
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_1_PHYS                                                                    (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000574)
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_1_OFFS                                                                    (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000574)
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_1_RMSK_V2                                                                     0xfffffff
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_1_ATTR_V2                                                                           0x3
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_1_IN          \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_1_ADDR, HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_1_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_1_INM(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_1_ADDR, m)
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_1_OUT_V2(v)      \
        out_dword(HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_1_ADDR,v)
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_1_OUTM_V2(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_1_ADDR,m,v,HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_1_IN)
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_1_ARBITRARY_TESTBUS_6_SEL_BMSK_V2                                             0xfe00000
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_1_ARBITRARY_TESTBUS_6_SEL_SHFT_V2                                                  0x15
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_1_ARBITRARY_TESTBUS_5_SEL_BMSK_V2                                              0x1fc000
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_1_ARBITRARY_TESTBUS_5_SEL_SHFT_V2                                                   0xe
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_1_ARBITRARY_TESTBUS_4_SEL_BMSK_V2                                                0x3f80
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_1_ARBITRARY_TESTBUS_4_SEL_SHFT_V2                                                   0x7
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_1_ARBITRARY_TESTBUS_3_SEL_BMSK_V2                                                  0x7f
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_CFG_1_ARBITRARY_TESTBUS_3_SEL_SHFT_V2                                                   0x0

#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_MASK_n_ADDR_V2(n)                                                                (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000578 + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_MASK_n_PHYS_V2(n)                                                                (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000578 + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_MASK_n_OFFS_V2(n)                                                                (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000578 + 0x4 * (n))
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_MASK_n_RMSK_V2                                                                   0xffffffff
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_MASK_n_MAXn_V2                                                                            6
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_MASK_n_ATTR_V2                                                                          0x3
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_MASK_n_INI_V2(n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TPDM_CONTROL_MASK_n_ADDR_V2(n), HWIO_ECPRI_UDP_L2_TPDM_CONTROL_MASK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_MASK_n_INMI_V2(n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TPDM_CONTROL_MASK_n_ADDR_V2(n), mask)
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_MASK_n_OUTI_V2(n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_TPDM_CONTROL_MASK_n_ADDR_V2(n),val)
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_MASK_n_OUTMI_V2(n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_TPDM_CONTROL_MASK_n_ADDR_V2(n),mask,val,HWIO_ECPRI_UDP_L2_TPDM_CONTROL_MASK_n_INI_V2(n))
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_MASK_n_MASK_BITS_BMSK_V2                                                         0xffffffff
#define HWIO_ECPRI_UDP_L2_TPDM_CONTROL_MASK_n_MASK_BITS_SHFT_V2                                                                0x0

#define HWIO_ECPRI_UDP_L2_TESTBUS_SEL_CFG_ADDR_V2                                                                       (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000594)
#define HWIO_ECPRI_UDP_L2_TESTBUS_SEL_CFG_PHYS_V2                                                                       (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000594)
#define HWIO_ECPRI_UDP_L2_TESTBUS_SEL_CFG_OFFS_V2                                                                       (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000594)
#define HWIO_ECPRI_UDP_L2_TESTBUS_SEL_CFG_RMSK_V2                                                                            0x7f0
#define HWIO_ECPRI_UDP_L2_TESTBUS_SEL_CFG_ATTR_V2                                                                              0x3
#define HWIO_ECPRI_UDP_L2_TESTBUS_SEL_CFG_IN_V2          \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TESTBUS_SEL_CFG_ADDR_V2, HWIO_ECPRI_UDP_L2_TESTBUS_SEL_CFG_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_TESTBUS_SEL_CFG_IN_V2M(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TESTBUS_SEL_CFG_ADDR_V2, m)
#define HWIO_ECPRI_UDP_L2_TESTBUS_SEL_CFG_OUT_V2(v)      \
        out_dword(HWIO_ECPRI_UDP_L2_TESTBUS_SEL_CFG_ADDR_V2,v)
#define HWIO_ECPRI_UDP_L2_TESTBUS_SEL_CFG_OUTM_V2(m,v) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_TESTBUS_SEL_CFG_ADDR_V2,m,v,HWIO_ECPRI_UDP_L2_TESTBUS_SEL_CFG_IN_V2)
#define HWIO_ECPRI_UDP_L2_TESTBUS_SEL_CFG_TESTBUS_SEL_BMSK_V2                                                                0x7f0
#define HWIO_ECPRI_UDP_L2_TESTBUS_SEL_CFG_TESTBUS_SEL_SHFT_V2                                                                  0x4

#define HWIO_ECPRI_UDP_L2_TESTBUS_ADDR_V2                                                                               (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000598)
#define HWIO_ECPRI_UDP_L2_TESTBUS_PHYS_V2                                                                               (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000598)
#define HWIO_ECPRI_UDP_L2_TESTBUS_OFFS_V2                                                                               (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000598)
#define HWIO_ECPRI_UDP_L2_TESTBUS_RMSK_V2                                                                               0xffffffff
#define HWIO_ECPRI_UDP_L2_TESTBUS_ATTR_V2                                                                                      0x1
#define HWIO_ECPRI_UDP_L2_TESTBUS_IN_V2          \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TESTBUS_ADDR_V2, HWIO_ECPRI_UDP_L2_TESTBUS_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_TESTBUS_INM_V2(m)      \
        in_dword_masked(HWIO_ECPRI_UDP_L2_TESTBUS_ADDR_V2, m)
#define HWIO_ECPRI_UDP_L2_TESTBUS_DATA_BMSK_V2                                                                          0xffffffff
#define HWIO_ECPRI_UDP_L2_TESTBUS_DATA_SHFT_V2                                                                                 0x0

#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_MISC_p_ADDR_V2(p)                                                              (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x0000059c + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_MISC_p_PHYS_V2(p)                                                              (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x0000059c + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_MISC_p_OFFS_V2(p)                                                              (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x0000059c + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_MISC_p_RMSK_V2                                                                    0x7ffff
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_MISC_p_MAXp_V2                                                                          0
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_MISC_p_ATTR_V2                                                                        0x3
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_MISC_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_MISC_p_ADDR_V2(p), HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_MISC_p_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_MISC_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_MISC_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_MISC_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_MISC_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_MISC_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_MISC_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_MISC_p_INI_V2(p))
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_MISC_p_ERRO_INFO_BMSK_V2                                                          0x7f800
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_MISC_p_ERRO_INFO_SHFT_V2                                                              0xb
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_MISC_p_LINK_ID_BMSK_V2                                                              0x600
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_MISC_p_LINK_ID_SHFT_V2                                                                0x9
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_MISC_p_NUM_VALID_BYTES_BMSK_V2                                                      0x1fc
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_MISC_p_NUM_VALID_BYTES_SHFT_V2                                                        0x2
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_MISC_p_EN_BMSK_V2                                                                     0x2
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_MISC_p_EN_SHFT_V2                                                                     0x1
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_MISC_p_CLR_BMSK_V2                                                                    0x1
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_MISC_p_CLR_SHFT_V2                                                                    0x0

#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_ADDR_V2(p,n)                                                (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x000005a8 + 0x4 * (n) + 0x54 * (p))
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_PHYS_V2(p,n)                                                (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x000005a8 + 0x4 * (n) + 0x54 * (p))
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_OFFS_V2(p,n)                                                (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x000005a8 + 0x4 * (n) + 0x54 * (p))
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_RMSK_V2                                                     0xffffffff
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_MAXp_V2                                                              0
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_MAXn_V2                                                             20
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_ATTR_V2                                                            0x1
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_VALUE_BMSK_V2                                               0xffffffff
#define HWIO_ECPRI_UDP_L2_ERROR_SYNDROME_REG_PORT_p_ENRTY_n_VALUE_SHFT_V2                                                      0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_1_PORT_p_ADDR_V2(p)                                                      (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x000006a4 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_1_PORT_p_PHYS_V2(p)                                                      (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x000006a4 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_1_PORT_p_OFFS_V2(p)                                                      (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x000006a4 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_1_PORT_p_RMSK_V2                                                              0x7ff
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_1_PORT_p_MAXp_V2                                                                  0
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_1_PORT_p_ATTR_V2                                                                0x1
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_1_PORT_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_1_PORT_p_ADDR_V2(p), HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_1_PORT_p_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_1_PORT_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_1_PORT_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_1_PORT_p_CS_UPDATE_FIFO_BMSK_V2                                               0x600
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_1_PORT_p_CS_UPDATE_FIFO_SHFT_V2                                                 0x9
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_1_PORT_p_CS_CALC_FIFO_BMSK_V2                                                 0x1ff
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_1_PORT_p_CS_CALC_FIFO_SHFT_V2                                                   0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_IPV4_FIELDS_p_ADDR_V2(p)                                                               (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000800 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IPV4_FIELDS_p_PHYS_V2(p)                                                               (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000800 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IPV4_FIELDS_p_OFFS_V2(p)                                                               (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000800 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IPV4_FIELDS_p_RMSK_V2                                                                    0xffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_IPV4_FIELDS_p_MAXp_V2                                                                           0
#define HWIO_ECPRI_UDP_L2_EGRESS_IPV4_FIELDS_p_ATTR_V2                                                                         0x3
#define HWIO_ECPRI_UDP_L2_EGRESS_IPV4_FIELDS_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_IPV4_FIELDS_p_ADDR_V2(p), HWIO_ECPRI_UDP_L2_EGRESS_IPV4_FIELDS_p_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_IPV4_FIELDS_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_IPV4_FIELDS_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_IPV4_FIELDS_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_EGRESS_IPV4_FIELDS_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_L2_EGRESS_IPV4_FIELDS_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_EGRESS_IPV4_FIELDS_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_L2_EGRESS_IPV4_FIELDS_p_INI_V2(p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IPV4_FIELDS_p_TTL_BMSK_V2                                                                0xff0000
#define HWIO_ECPRI_UDP_L2_EGRESS_IPV4_FIELDS_p_TTL_SHFT_V2                                                                    0x10
#define HWIO_ECPRI_UDP_L2_EGRESS_IPV4_FIELDS_p_ID_BMSK_V2                                                                   0xffff
#define HWIO_ECPRI_UDP_L2_EGRESS_IPV4_FIELDS_p_ID_SHFT_V2                                                                      0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_IPV6_FIELDS_p_ADDR_V2(p)                                                               (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x0000080c + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IPV6_FIELDS_p_PHYS_V2(p)                                                               (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x0000080c + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IPV6_FIELDS_p_OFFS_V2(p)                                                               (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x0000080c + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IPV6_FIELDS_p_RMSK_V2                                                                   0xfffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_IPV6_FIELDS_p_MAXp_V2                                                                           0
#define HWIO_ECPRI_UDP_L2_EGRESS_IPV6_FIELDS_p_ATTR_V2                                                                         0x3
#define HWIO_ECPRI_UDP_L2_EGRESS_IPV6_FIELDS_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_IPV6_FIELDS_p_ADDR_V2(p), HWIO_ECPRI_UDP_L2_EGRESS_IPV6_FIELDS_p_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_IPV6_FIELDS_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_IPV6_FIELDS_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_IPV6_FIELDS_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_EGRESS_IPV6_FIELDS_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_L2_EGRESS_IPV6_FIELDS_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_EGRESS_IPV6_FIELDS_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_L2_EGRESS_IPV6_FIELDS_p_INI_V2(p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IPV6_FIELDS_p_FLOW_LABEL_BMSK_V2                                                        0xfffff00
#define HWIO_ECPRI_UDP_L2_EGRESS_IPV6_FIELDS_p_FLOW_LABEL_SHFT_V2                                                              0x8
#define HWIO_ECPRI_UDP_L2_EGRESS_IPV6_FIELDS_p_HOP_LIMIT_BMSK_V2                                                              0xff
#define HWIO_ECPRI_UDP_L2_EGRESS_IPV6_FIELDS_p_HOP_LIMIT_SHFT_V2                                                               0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_ETHERTYPE_p_ADDR_V2(p)                                                          (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000818 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_ETHERTYPE_p_PHYS_V2(p)                                                          (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000818 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_ETHERTYPE_p_OFFS_V2(p)                                                          (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000818 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_ETHERTYPE_p_RMSK_V2                                                                 0xffff
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_ETHERTYPE_p_MAXp_V2                                                                      0
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_ETHERTYPE_p_ATTR_V2                                                                    0x3
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_ETHERTYPE_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_ETHERTYPE_p_ADDR_V2(p), HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_ETHERTYPE_p_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_ETHERTYPE_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_ETHERTYPE_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_ETHERTYPE_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_ETHERTYPE_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_ETHERTYPE_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_ETHERTYPE_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_ETHERTYPE_p_INI_V2(p))
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_ETHERTYPE_p_VALUE_BMSK_V2                                                           0xffff
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_ETHERTYPE_p_VALUE_SHFT_V2                                                              0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_ADDR_V2(p)                                                   (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000824 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_PHYS_V2(p)                                                   (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000824 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_OFFS_V2(p)                                                   (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000824 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_RMSK_V2                                                          0xffff
#define HWIO_ECPRI_UDP_L2_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_MAXp_V2                                                               0
#define HWIO_ECPRI_UDP_L2_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_ATTR_V2                                                             0x3
#define HWIO_ECPRI_UDP_L2_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_ADDR_V2(p), HWIO_ECPRI_UDP_L2_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_L2_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_L2_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_INI_V2(p))
#define HWIO_ECPRI_UDP_L2_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_REDIRECT_TO_BMSK_V2                                              0xff00
#define HWIO_ECPRI_UDP_L2_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_REDIRECT_TO_SHFT_V2                                                 0x8
#define HWIO_ECPRI_UDP_L2_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_REDIRECT_FROM_BMSK_V2                                              0xff
#define HWIO_ECPRI_UDP_L2_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p_REDIRECT_FROM_SHFT_V2                                               0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_ADDR_V2(p)                                                   (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000830 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_PHYS_V2(p)                                                   (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000830 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_OFFS_V2(p)                                                   (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000830 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_RMSK_V2                                                          0xffff
#define HWIO_ECPRI_UDP_L2_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_MAXp_V2                                                               0
#define HWIO_ECPRI_UDP_L2_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_ATTR_V2                                                             0x3
#define HWIO_ECPRI_UDP_L2_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_ADDR_V2(p), HWIO_ECPRI_UDP_L2_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_L2_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_L2_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_INI_V2(p))
#define HWIO_ECPRI_UDP_L2_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_REDIRECT_TO_BMSK_V2                                              0xff00
#define HWIO_ECPRI_UDP_L2_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_REDIRECT_TO_SHFT_V2                                                 0x8
#define HWIO_ECPRI_UDP_L2_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_REDIRECT_FROM_BMSK_V2                                              0xff
#define HWIO_ECPRI_UDP_L2_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p_REDIRECT_FROM_SHFT_V2                                               0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_MTU_p_ADDR_V2(p)                                                                   (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x0000083c + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_MTU_p_PHYS_V2(p)                                                                   (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x0000083c + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_MTU_p_OFFS_V2(p)                                                                   (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x0000083c + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_MTU_p_RMSK_V2                                                                          0x3fff
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_MTU_p_MAXp_V2                                                                               0
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_MTU_p_ATTR_V2                                                                             0x3
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_MTU_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_ETH_MTU_p_ADDR_V2(p), HWIO_ECPRI_UDP_L2_EGRESS_ETH_MTU_p_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_MTU_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_ETH_MTU_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_MTU_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_EGRESS_ETH_MTU_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_MTU_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_EGRESS_ETH_MTU_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_L2_EGRESS_ETH_MTU_p_INI_V2(p))
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_MTU_p_VALUE_BMSK_V2                                                                    0x3fff
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_MTU_p_VALUE_SHFT_V2                                                                       0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_ADDR_V2(p)                                                                    (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000860 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_PHYS_V2(p)                                                                    (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000860 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_OFFS_V2(p)                                                                    (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000860 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_RMSK_V2                                                                           0x7fff
#define HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_MAXp_V2                                                                                0
#define HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_ATTR_V2                                                                              0x3
#define HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_ADDR_V2(p), HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_INI_V2(p))
#define HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_DISABLE_PTP_DETECTION_BMSK_V2                                                     0x4000
#define HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_DISABLE_PTP_DETECTION_SHFT_V2                                                        0xe
#define HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_L3_ENCAP_INDEX_OVERRIDE_EN_BMSK_V2                                                0x2000
#define HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_L3_ENCAP_INDEX_OVERRIDE_EN_SHFT_V2                                                   0xd
#define HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_L2_ENCAP_INDEX_OVERRIDE_EN_BMSK_V2                                                0x1000
#define HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_L2_ENCAP_INDEX_OVERRIDE_EN_SHFT_V2                                                   0xc
#define HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_DISABLE_PADDING_REMOVAL_BMSK_V2                                                    0x800
#define HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_DISABLE_PADDING_REMOVAL_SHFT_V2                                                      0xb
#define HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_BYPASSED_PACKETS_VPORT_BMSK_V2                                                     0x7f8
#define HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_BYPASSED_PACKETS_VPORT_SHFT_V2                                                       0x3
#define HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_BYPASSED_PACKETS_VPORT_ACTION_BMSK_V2                                                0x6
#define HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_BYPASSED_PACKETS_VPORT_ACTION_SHFT_V2                                                0x1
#define HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_CALC_IP_UDP_LEN_FROM_BYTE_COUNT_BMSK_V2                                              0x1
#define HWIO_ECPRI_UDP_L2_EGRESS_CONFIG_p_CALC_IP_UDP_LEN_FROM_BYTE_COUNT_SHFT_V2                                              0x0

#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_ADDR_V2(p)                                                         (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000900 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_PHYS_V2(p)                                                         (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000900 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_OFFS_V2(p)                                                         (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000900 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_RMSK_V2                                                                0x7fff
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_MAXp_V2                                                                     0
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_ATTR_V2                                                                   0x1
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_ADDR_V2(p), HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_0_BMSK_V2                 0x4000
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_0_SHFT_V2                    0xe
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_0_BMSK_V2              0x2000
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_0_SHFT_V2                 0xd
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_0_BMSK_V2                                     0x1000
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_0_SHFT_V2                                        0xc
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_0_BMSK_V2                                      0x800
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_0_SHFT_V2                                        0xb
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_0_BMSK_V2                                      0x400
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_0_SHFT_V2                                        0xa
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_0_BMSK_V2                                      0x200
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_0_SHFT_V2                                        0x9
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_0_BMSK_V2                                0x100
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_0_SHFT_V2                                  0x8
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_0_BMSK_V2                                    0x80
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_0_SHFT_V2                                     0x7
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_0_BMSK_V2                              0x40
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_0_SHFT_V2                               0x6
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_0_BMSK_V2                                0x20
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_0_SHFT_V2                                 0x5
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_0_BMSK_V2                                      0x10
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_0_SHFT_V2                                       0x4
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_0_BMSK_V2                                      0x8
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_0_SHFT_V2                                      0x3
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_0_BMSK_V2                          0x4
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_0_SHFT_V2                          0x2
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_0_BMSK_V2                                     0x2
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_0_SHFT_V2                                     0x1
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_0_BMSK_V2                                      0x1
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_0_SHFT_V2                                      0x0

#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_ADDR_V2(p)                                                           (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000920 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_PHYS_V2(p)                                                           (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000920 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_OFFS_V2(p)                                                           (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000920 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_RMSK_V2                                                                  0x7fff
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_MAXp_V2                                                                       0
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_ATTR_V2                                                                     0x3
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INI_V2(p)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_ADDR_V2(p), HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INMI_V2(p,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_ADDR_V2(p), mask)
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_OUTMI_V2(p,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_ADDR_V2(p),mask,val,HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INI_V2(p))
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_0_BMSK_V2                   0x4000
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_0_SHFT_V2                      0xe
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_0_BMSK_V2                0x2000
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_0_SHFT_V2                   0xd
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_0_BMSK_V2                                       0x1000
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_0_SHFT_V2                                          0xc
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_0_BMSK_V2                                        0x800
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_0_SHFT_V2                                          0xb
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_0_BMSK_V2                                        0x400
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_0_SHFT_V2                                          0xa
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_0_BMSK_V2                                        0x200
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_0_SHFT_V2                                          0x9
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_0_BMSK_V2                                  0x100
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_0_SHFT_V2                                    0x8
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_0_BMSK_V2                                      0x80
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_0_SHFT_V2                                       0x7
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_0_BMSK_V2                                0x40
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_0_SHFT_V2                                 0x6
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_0_BMSK_V2                                  0x20
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_0_SHFT_V2                                   0x5
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_0_BMSK_V2                                        0x10
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_0_SHFT_V2                                         0x4
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_0_BMSK_V2                                        0x8
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_0_SHFT_V2                                        0x3
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_0_BMSK_V2                            0x4
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_0_SHFT_V2                            0x2
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_0_BMSK_V2                                       0x2
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_0_SHFT_V2                                       0x1
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_0_BMSK_V2                                        0x1
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_0_SHFT_V2                                        0x0

#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_ADDR_V2(p)                                                            (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_V2     + 0x00000940 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_PHYS_V2(p)                                                            (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_PHYS_V2 + 0x00000940 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_OFFS_V2(p)                                                            (ECPRI_UDP_L2_UDP_L2_REGS_REG_BASE_OFFS_V2 + 0x00000940 + 0x4 * (p))
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_RMSK_V2                                                                   0x7fff
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_MAXp_V2                                                                        0
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_ATTR_V2                                                                      0x2
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_OUTI_V2(p,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_ADDR_V2(p),val)
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_0_BMSK_V2                    0x4000
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TIMESTAMPED_PACKETS_BW_TOO_HIGH_LINK_0_SHFT_V2                       0xe
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_0_BMSK_V2                 0x2000
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_0_SHFT_V2                    0xd
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_0_BMSK_V2                                        0x1000
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_0_SHFT_V2                                           0xc
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_0_BMSK_V2                                         0x800
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_0_SHFT_V2                                           0xb
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_0_BMSK_V2                                         0x400
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_0_SHFT_V2                                           0xa
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_0_BMSK_V2                                         0x200
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_0_SHFT_V2                                           0x9
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_0_BMSK_V2                                   0x100
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_0_SHFT_V2                                     0x8
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_0_BMSK_V2                                       0x80
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_0_SHFT_V2                                        0x7
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_0_BMSK_V2                                 0x40
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_VLAN_FILTERED_PACKET_LINK_0_SHFT_V2                                  0x6
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_0_BMSK_V2                                   0x20
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_IP_FILTERED_PACKET_LINK_0_SHFT_V2                                    0x5
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_0_BMSK_V2                                         0x10
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_0_SHFT_V2                                          0x4
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_0_BMSK_V2                                         0x8
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_0_SHFT_V2                                         0x3
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_0_BMSK_V2                             0x4
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_0_SHFT_V2                             0x2
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_0_BMSK_V2                                        0x2
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_0_SHFT_V2                                        0x1
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_0_BMSK_V2                                         0x1
#define HWIO_ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_0_SHFT_V2                                         0x0

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_UDP_L2_UDP_L2_FILTER
 *--------------------------------------------------------------------------*/

#define ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_V2                                         (ECPRI_WRAPPER_BASE      + 0x003e1000)
#define ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_PHYS_V2                                     (ECPRI_WRAPPER_BASE_PHYS + 0x003e1000)
#define ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_OFFS_V2                                     0x003e1000

#define HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRY_n_ADDR_V2(p,n)                    (ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_V2     + 0x00000000 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRY_n_PHYS_V2(p,n)                    (ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_PHYS_V2 + 0x00000000 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRY_n_OFFS_V2(p,n)                    (ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_OFFS_V2 + 0x00000000 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRY_n_RMSK_V2                             0xffff
#define HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRY_n_MAXp_V2                                  0
#define HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRY_n_MAXn_V2                                 15
#define HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRY_n_ATTR_V2                                0x3
#define HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRY_n_VALUE_BMSK_V2                       0xffff
#define HWIO_ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRY_n_VALUE_SHFT_V2                          0x0

#define HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_ADDR_V2(p,n)           (ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_V2     + 0x00000300 + 0x4 * (n) + 0x80 * (p))
#define HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_PHYS_V2(p,n)           (ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_PHYS_V2 + 0x00000300 + 0x4 * (n) + 0x80 * (p))
#define HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_OFFS_V2(p,n)           (ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_OFFS_V2 + 0x00000300 + 0x4 * (n) + 0x80 * (p))
#define HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_RMSK_V2                    0xffff
#define HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_MAXp_V2                         0
#define HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_MAXn_V2                        31
#define HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_ATTR_V2                       0x3
#define HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_VALUE_BMSK_V2              0xffff
#define HWIO_ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_VALUE_SHFT_V2                 0x0

#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n)                 (ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_V2     + 0x00000700 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_PHYS_V2(p,n)                 (ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_PHYS_V2 + 0x00000700 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_OFFS_V2(p,n)                 (ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_OFFS_V2 + 0x00000700 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_RMSK_V2                      0xffffffff
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_MAXp_V2                               0
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_MAXn_V2                              15
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_ATTR_V2                             0x3
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_VALUE_BMSK_V2                0xffffffff
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_VALUE_SHFT_V2                       0x0

#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n)                 (ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_V2     + 0x00000a00 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_PHYS_V2(p,n)                 (ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_PHYS_V2 + 0x00000a00 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_OFFS_V2(p,n)                 (ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_OFFS_V2 + 0x00000a00 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_RMSK_V2                      0xffffffff
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_MAXp_V2                               0
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_MAXn_V2                              15
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_ATTR_V2                             0x3
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_VALUE_BMSK_V2                0xffffffff
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_VALUE_SHFT_V2                       0x0

#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n)                 (ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_V2     + 0x00000d00 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_PHYS_V2(p,n)                 (ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_PHYS_V2 + 0x00000d00 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_OFFS_V2(p,n)                 (ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_OFFS_V2 + 0x00000d00 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_RMSK_V2                      0xffffffff
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_MAXp_V2                               0
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_MAXn_V2                              15
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_ATTR_V2                             0x3
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_VALUE_BMSK_V2                0xffffffff
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_VALUE_SHFT_V2                       0x0

#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n)                 (ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_V2     + 0x00001000 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_PHYS_V2(p,n)                 (ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_PHYS_V2 + 0x00001000 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_OFFS_V2(p,n)                 (ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_OFFS_V2 + 0x00001000 + 0x4 * (n) + 0x40 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_RMSK_V2                      0xffffffff
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_MAXp_V2                               0
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_MAXn_V2                              15
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_ATTR_V2                             0x3
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_VALUE_BMSK_V2                0xffffffff
#define HWIO_ECPRI_UDP_L2_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_VALUE_SHFT_V2                       0x0

#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n)              (ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_V2     + 0x00001300 + 0x4 * (n) + 0x10 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_PHYS_V2(p,n)              (ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_PHYS_V2 + 0x00001300 + 0x4 * (n) + 0x10 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_OFFS_V2(p,n)              (ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_OFFS_V2 + 0x00001300 + 0x4 * (n) + 0x10 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_RMSK_V2                   0xffffffff
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_MAXp_V2                            0
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_MAXn_V2                            3
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_ATTR_V2                          0x3
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_VALUE_BMSK_V2             0xffffffff
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_VALUE_SHFT_V2                    0x0

#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n)              (ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_V2     + 0x00001400 + 0x4 * (n) + 0x10 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_PHYS_V2(p,n)              (ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_PHYS_V2 + 0x00001400 + 0x4 * (n) + 0x10 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_OFFS_V2(p,n)              (ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_OFFS_V2 + 0x00001400 + 0x4 * (n) + 0x10 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_RMSK_V2                       0xffff
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_MAXp_V2                            0
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_MAXn_V2                            3
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_ATTR_V2                          0x3
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_VALUE_BMSK_V2                 0xffff
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_VALUE_SHFT_V2                    0x0

#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_ADDR_V2(p,n)             (ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_V2     + 0x00001500 + 0x4 * (n) + 0x10 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_PHYS_V2(p,n)             (ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_PHYS_V2 + 0x00001500 + 0x4 * (n) + 0x10 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_OFFS_V2(p,n)             (ECPRI_UDP_L2_UDP_L2_FILTER_REG_BASE_OFFS_V2 + 0x00001500 + 0x4 * (n) + 0x10 * (p))
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_RMSK_V2                      0x1fff
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_MAXp_V2                           0
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_MAXn_V2                           3
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_ATTR_V2                         0x3
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_RING_ID_BMSK_V2              0x1fe0
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_RING_ID_SHFT_V2                 0x5
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_GSI_ID_BMSK_V2                 0x18
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_GSI_ID_SHFT_V2                  0x3
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_ACTION_BMSK_V2                  0x7
#define HWIO_ECPRI_UDP_L2_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n_ACTION_SHFT_V2                  0x0

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_UDP_L2_UDP_L2_RAMS
 *--------------------------------------------------------------------------*/

#define ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_V2                                                          (ECPRI_WRAPPER_BASE      + 0x003e4000)
#define ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS_V2                                                     (ECPRI_WRAPPER_BASE_PHYS + 0x003e4000)
#define ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS_V2                                                     0x003e4000

#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                      (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x00000000 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                      (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x00000000 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                      (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x00000000 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_RMSK_V2                           0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_MAXp_V2                                    0
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_MAXn_V2                                    0
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_ATTR_V2                                  0x1
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                     0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                            0x0

#define HWIO_ECPRI_UDP_L2_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                          (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x00000004 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                          (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x00000004 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                          (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x00000004 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_RMSK_V2                               0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_MAXp_V2                                        0
#define HWIO_ECPRI_UDP_L2_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_MAXn_V2                                        0
#define HWIO_ECPRI_UDP_L2_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_ATTR_V2                                      0x1
#define HWIO_ECPRI_UDP_L2_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                         0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                                0x0

#define HWIO_ECPRI_UDP_L2_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                    (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x00000008 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                    (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x00000008 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                    (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x00000008 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_RMSK_V2                         0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_MAXp_V2                                  0
#define HWIO_ECPRI_UDP_L2_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_MAXn_V2                                  0
#define HWIO_ECPRI_UDP_L2_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_ATTR_V2                                0x1
#define HWIO_ECPRI_UDP_L2_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                   0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                          0x0

#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                     (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x0000000c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                     (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x0000000c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                     (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x0000000c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_RMSK_V2                          0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_MAXp_V2                                   0
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_MAXn_V2                                   0
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_ATTR_V2                                 0x1
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                    0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                           0x0

#define HWIO_ECPRI_UDP_L2_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                      (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x00000010 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                      (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x00000010 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                      (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x00000010 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_RMSK_V2                           0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_MAXp_V2                                    0
#define HWIO_ECPRI_UDP_L2_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_MAXn_V2                                    0
#define HWIO_ECPRI_UDP_L2_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_ATTR_V2                                  0x1
#define HWIO_ECPRI_UDP_L2_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                     0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                            0x0

#define HWIO_ECPRI_UDP_L2_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                    (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x00000014 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                    (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x00000014 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                    (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x00000014 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_RMSK_V2                         0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_MAXp_V2                                  0
#define HWIO_ECPRI_UDP_L2_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_MAXn_V2                                  0
#define HWIO_ECPRI_UDP_L2_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_ATTR_V2                                0x1
#define HWIO_ECPRI_UDP_L2_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                   0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                          0x0

#define HWIO_ECPRI_UDP_L2_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                          (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x00000018 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                          (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x00000018 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                          (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x00000018 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_RMSK_V2                               0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_MAXp_V2                                        0
#define HWIO_ECPRI_UDP_L2_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_MAXn_V2                                        0
#define HWIO_ECPRI_UDP_L2_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_ATTR_V2                                      0x1
#define HWIO_ECPRI_UDP_L2_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                         0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                                0x0

#define HWIO_ECPRI_UDP_L2_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                       (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x0000001c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                       (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x0000001c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                       (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x0000001c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_RMSK_V2                            0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_MAXp_V2                                     0
#define HWIO_ECPRI_UDP_L2_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_MAXn_V2                                     0
#define HWIO_ECPRI_UDP_L2_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_ATTR_V2                                   0x1
#define HWIO_ECPRI_UDP_L2_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                      0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                             0x0

#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                    (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x00000020 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                    (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x00000020 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                    (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x00000020 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_RMSK_V2                         0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_MAXp_V2                                  0
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_MAXn_V2                                  0
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_ATTR_V2                                0x1
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                   0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                          0x0

#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                      (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x00000024 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                      (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x00000024 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                      (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x00000024 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_RMSK_V2                           0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_MAXp_V2                                    0
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_MAXn_V2                                    0
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_ATTR_V2                                  0x1
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                     0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                            0x0

#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                    (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x00000028 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                    (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x00000028 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                    (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x00000028 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_RMSK_V2                         0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_MAXp_V2                                  0
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_MAXn_V2                                  0
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_ATTR_V2                                0x1
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                   0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                          0x0

#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)           (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x0000002c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)           (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x0000002c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)           (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x0000002c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_RMSK_V2                0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_MAXp_V2                         0
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_MAXn_V2                         0
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_ATTR_V2                       0x1
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2          0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                 0x0

#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                      (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x00000030 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                      (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x00000030 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                      (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x00000030 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_RMSK_V2                           0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_MAXp_V2                                    0
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_MAXn_V2                                    0
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_ATTR_V2                                  0x1
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                     0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                            0x0

#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                    (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x00000034 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                    (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x00000034 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                    (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x00000034 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_RMSK_V2                         0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_MAXp_V2                                  0
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_MAXn_V2                                  0
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_ATTR_V2                                0x1
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                   0xffffffff
#define HWIO_ECPRI_UDP_L2_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                          0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                           (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x00000038 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                           (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x00000038 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                           (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x00000038 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_RMSK_V2                                0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_MAXp_V2                                         0
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_MAXn_V2                                         0
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_ATTR_V2                                       0x1
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                          0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                                 0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                      (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x0000003c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                      (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x0000003c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                      (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x0000003c + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_RMSK_V2                           0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_MAXp_V2                                    0
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_MAXn_V2                                    0
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_ATTR_V2                                  0x1
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                     0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                            0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                      (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x00000040 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                      (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x00000040 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                      (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x00000040 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_RMSK_V2                           0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_MAXp_V2                                    0
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_MAXn_V2                                    0
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_ATTR_V2                                  0x1
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                     0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                            0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n)                           (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x00000044 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_PHYS_V2(p,n)                           (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x00000044 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_OFFS_V2(p,n)                           (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x00000044 + 0x48 * (n) + 0x120 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_RMSK_V2                                0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_MAXp_V2                                         0
#define HWIO_ECPRI_UDP_L2_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_MAXn_V2                                         0
#define HWIO_ECPRI_UDP_L2_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_ATTR_V2                                       0x1
#define HWIO_ECPRI_UDP_L2_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_VALUE_BMSK_V2                          0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_VALUE_SHFT_V2                                 0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_DST0_PORT_p_ENTRY_n_ADDR_V2(p,n)                                 (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x00001000 + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_DST0_PORT_p_ENTRY_n_PHYS_V2(p,n)                                 (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x00001000 + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_DST0_PORT_p_ENTRY_n_OFFS_V2(p,n)                                 (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x00001000 + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_DST0_PORT_p_ENTRY_n_RMSK_V2                                      0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_DST0_PORT_p_ENTRY_n_MAXp_V2                                               0
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_DST0_PORT_p_ENTRY_n_MAXn_V2                                             255
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_DST0_PORT_p_ENTRY_n_ATTR_V2                                             0x3
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_DST0_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_ETH_DST0_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_EGRESS_ETH_DST0_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_DST0_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_ETH_DST0_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_DST0_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_EGRESS_ETH_DST0_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_DST0_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_EGRESS_ETH_DST0_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_EGRESS_ETH_DST0_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_DST0_PORT_p_ENTRY_n_VALUE_BMSK_V2                                0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_DST0_PORT_p_ENTRY_n_VALUE_SHFT_V2                                       0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_ADDR_V2(p,n)                            (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x00001004 + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_PHYS_V2(p,n)                            (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x00001004 + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_OFFS_V2(p,n)                            (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x00001004 + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_RMSK_V2                                 0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_MAXp_V2                                          0
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_MAXn_V2                                        255
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_ATTR_V2                                        0x3
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_SRC_MSB_BMSK_V2                         0xffff0000
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_SRC_MSB_SHFT_V2                               0x10
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_DST_MSB_BMSK_V2                             0xffff
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_DST_MSB_SHFT_V2                                0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_ADDR_V2(p,n)                                 (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x00001008 + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_PHYS_V2(p,n)                                 (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x00001008 + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_OFFS_V2(p,n)                                 (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x00001008 + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_RMSK_V2                                      0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_MAXp_V2                                               0
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_MAXn_V2                                             255
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_ATTR_V2                                             0x3
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_VALUE_BMSK_V2                                0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_VALUE_SHFT_V2                                       0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_ADDR_V2(p,n)                           (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x0000100c + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_PHYS_V2(p,n)                           (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x0000100c + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_OFFS_V2(p,n)                           (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x0000100c + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_RMSK_V2                                0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_MAXp_V2                                         0
#define HWIO_ECPRI_UDP_L2_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_MAXn_V2                                       255
#define HWIO_ECPRI_UDP_L2_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_ATTR_V2                                       0x3
#define HWIO_ECPRI_UDP_L2_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_VLAN_DATA_BMSK_V2                      0xffff0000
#define HWIO_ECPRI_UDP_L2_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_VLAN_DATA_SHFT_V2                            0x10
#define HWIO_ECPRI_UDP_L2_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_ETHERTYPE_BMSK_V2                          0xffff
#define HWIO_ECPRI_UDP_L2_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_ETHERTYPE_SHFT_V2                             0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n)                               (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x00001010 + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_PHYS_V2(p,n)                               (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x00001010 + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_OFFS_V2(p,n)                               (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x00001010 + 0x20 * (n) + 0x2000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_RMSK_V2                                        0x7fff
#define HWIO_ECPRI_UDP_L2_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_MAXp_V2                                             0
#define HWIO_ECPRI_UDP_L2_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_MAXn_V2                                           255
#define HWIO_ECPRI_UDP_L2_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_ATTR_V2                                           0x3
#define HWIO_ECPRI_UDP_L2_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_RSVD_BMSK_V2                                   0x7800
#define HWIO_ECPRI_UDP_L2_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_RSVD_SHFT_V2                                      0xb
#define HWIO_ECPRI_UDP_L2_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_VPORT_ACTION_BMSK_V2                            0x600
#define HWIO_ECPRI_UDP_L2_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_VPORT_ACTION_SHFT_V2                              0x9
#define HWIO_ECPRI_UDP_L2_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_HAS_VLAN_BMSK_V2                                0x100
#define HWIO_ECPRI_UDP_L2_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_HAS_VLAN_SHFT_V2                                  0x8
#define HWIO_ECPRI_UDP_L2_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_VPORT_BMSK_V2                                    0xff
#define HWIO_ECPRI_UDP_L2_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_VPORT_SHFT_V2                                     0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n)                             (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x00010000 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_PHYS_V2(p,n)                             (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x00010000 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_OFFS_V2(p,n)                             (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x00010000 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_RMSK_V2                                  0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_MAXp_V2                                           0
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_MAXn_V2                                         255
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_ATTR_V2                                         0x3
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_VALUE_BMSK_V2                            0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_VALUE_SHFT_V2                                   0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n)                             (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x00010004 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_PHYS_V2(p,n)                             (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x00010004 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_OFFS_V2(p,n)                             (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x00010004 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_RMSK_V2                                  0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_MAXp_V2                                           0
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_MAXn_V2                                         255
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_ATTR_V2                                         0x3
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_VALUE_BMSK_V2                            0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_VALUE_SHFT_V2                                   0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n)                             (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x00010008 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_PHYS_V2(p,n)                             (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x00010008 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_OFFS_V2(p,n)                             (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x00010008 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_RMSK_V2                                  0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_MAXp_V2                                           0
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_MAXn_V2                                         255
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_ATTR_V2                                         0x3
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_VALUE_BMSK_V2                            0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_VALUE_SHFT_V2                                   0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n)                             (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x0001000c + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_PHYS_V2(p,n)                             (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x0001000c + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_OFFS_V2(p,n)                             (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x0001000c + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_RMSK_V2                                  0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_MAXp_V2                                           0
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_MAXn_V2                                         255
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_ATTR_V2                                         0x3
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_VALUE_BMSK_V2                            0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_VALUE_SHFT_V2                                   0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n)                             (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x00010010 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_PHYS_V2(p,n)                             (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x00010010 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_OFFS_V2(p,n)                             (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x00010010 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_RMSK_V2                                  0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_MAXp_V2                                           0
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_MAXn_V2                                         255
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_ATTR_V2                                         0x3
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_VALUE_BMSK_V2                            0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_VALUE_SHFT_V2                                   0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n)                             (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x00010014 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_PHYS_V2(p,n)                             (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x00010014 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_OFFS_V2(p,n)                             (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x00010014 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_RMSK_V2                                  0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_MAXp_V2                                           0
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_MAXn_V2                                         255
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_ATTR_V2                                         0x3
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_VALUE_BMSK_V2                            0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_VALUE_SHFT_V2                                   0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n)                             (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x00010018 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_PHYS_V2(p,n)                             (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x00010018 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_OFFS_V2(p,n)                             (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x00010018 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_RMSK_V2                                  0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_MAXp_V2                                           0
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_MAXn_V2                                         255
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_ATTR_V2                                         0x3
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_VALUE_BMSK_V2                            0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_VALUE_SHFT_V2                                   0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n)                             (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x0001001c + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_PHYS_V2(p,n)                             (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x0001001c + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_OFFS_V2(p,n)                             (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x0001001c + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_RMSK_V2                                  0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_MAXp_V2                                           0
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_MAXn_V2                                         255
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_ATTR_V2                                         0x3
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_VALUE_BMSK_V2                            0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_VALUE_SHFT_V2                                   0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_ADDR_V2(p,n)                                (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x00010020 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_PHYS_V2(p,n)                                (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x00010020 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_OFFS_V2(p,n)                                (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x00010020 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_RMSK_V2                                     0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_MAXp_V2                                              0
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_MAXn_V2                                            255
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_ATTR_V2                                            0x3
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_DST_BMSK_V2                                 0xffff0000
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_DST_SHFT_V2                                       0x10
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_SRC_BMSK_V2                                     0xffff
#define HWIO_ECPRI_UDP_L2_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_SRC_SHFT_V2                                        0x0

#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n)                       (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE      + 0x00010024 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_PHYS_V2(p,n)                       (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_PHYS + 0x00010024 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_OFFS_V2(p,n)                       (ECPRI_UDP_L2_UDP_L2_RAMS_REG_BASE_OFFS + 0x00010024 + 0x40 * (n) + 0x4000 * (p))
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_RMSK_V2                            0xffffffff
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_MAXp_V2                                     0
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_MAXn_V2                                   255
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_ATTR_V2                                   0x3
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_INI2_V2(p,n)        \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n), HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_RMSK_V2)
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_INMI2_V2(p,n,mask)    \
        in_dword_masked(HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n), mask)
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_OUTI2_V2(p,n,val)    \
        out_dword(HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n),val)
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_OUTMI2_V2(p,n,mask,val) \
        out_dword_masked_ns(HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_ADDR_V2(p,n),mask,val,HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_INI2_V2(p,n))
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_RSVD_BMSK_V2                       0xf0000000
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_RSVD_SHFT_V2                             0x1c
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_CALC_UDP_CS_BMSK_V2                 0x8000000
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_CALC_UDP_CS_SHFT_V2                      0x1b
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_DF_BIT_BMSK_V2                      0x4000000
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_DF_BIT_SHFT_V2                           0x1a
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_IS_IPSEC_BMSK_V2                    0x2000000
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_IS_IPSEC_SHFT_V2                         0x19
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_IP_TYPE_BMSK_V2                     0x1000000
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_IP_TYPE_SHFT_V2                          0x18
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_TOS_BMSK_V2                          0xff0000
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_TOS_SHFT_V2                              0x10
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_SA_TAG_DATA_BMSK_V2                    0xffff
#define HWIO_ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_SA_TAG_DATA_SHFT_V2                       0x0


#endif /* __ECPRI_QUDP_HWIO_V2_H__ */
