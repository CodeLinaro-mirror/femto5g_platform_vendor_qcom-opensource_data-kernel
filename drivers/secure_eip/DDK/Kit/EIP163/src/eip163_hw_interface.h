/* eip163_hw_interface.h
 *
 * EIP-163 Classification Engine Register Internal interface
 *
 */

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Module        : ddk164                                                   */
/*   Version       : 3.2                                                      */
/*   Configuration : DDK-164-IPSEC-GPL                                        */
/*                                                                            */
/*   Date          : 2022-Jan-10                                              */
/*                                                                            */
/* Copyright (c) 2008-2021 by Rambus, Inc. and/or its subsidiaries.           */
/*                                                                            */
/* This program is free software: you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation, either version 2 of the License, or          */
/* any later version.                                                         */
/*                                                                            */
/* This program is distributed in the hope that it will be useful,            */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of             */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               */
/* GNU General Public License for more details.                               */
/*                                                                            */
/* You should have received a copy of the GNU General Public License          */
/* along with this program. If not, see <http://www.gnu.org/licenses/>.       */
/* -------------------------------------------------------------------------- */

#ifndef EIP163_HW_INTERFACE_H_
#define EIP163_HW_INTERFACE_H_


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Default configuration */
#include "c_eip163.h"

/* Driver Framework Basic Definitions API */
#include "basic_defs.h"         /* BIT definitions, bool, uint32_t */

/* Driver Framework Device API */
#include "device_types.h"       /* Device_Handle_t */
#include "device_rw.h"          /* Read32, Write32 */


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

/* Read/Write register constants */

/*****************************************************************************
 * Byte offsets of the EIP-163 Packet Engine registers
 *****************************************************************************/
/* EIP-163 EIP number (0xA3) and complement (0x5C) */
#define EIP163_SIGNATURE                    ((uint16_t)0x5CA3)

#define EIP163_REG_OFFS                     4

/* Input TCAM entries (n), */
/* each entry has (m) 32-bit words, for control word m=0 */
#define EIP163_REG_TCAM_ENTRY_OFFS          0x40 /* TCAM entry size in bytes */
#define EIP163_REG_TCAM_KEY_WORD_COUNT      8
#define EIP163_REG_TCAM_MASK_WORD_COUNT     EIP163_REG_TCAM_KEY_WORD_COUNT
#define EIP163_REG_TCAM_KEY(n,m)            (EIP163_CONF_BASE + \
                                             (0x10000 * (n>>9)) + \
                                             EIP163_REG_TCAM_ENTRY_OFFS * ((n)& 0x1ff) + \
                                             EIP163_REG_OFFS * m)
#define EIP163_REG_TCAM_CTRL_KEY(n)         EIP163_REG_TCAM_KEY((n), 0)
#define EIP163_REG_TCAM_MASK(n,m)           (EIP163_CONF_BASE + 0x0020 + \
                                             (0x10000 * ((n) >> 9)) + \
                                             EIP163_REG_TCAM_ENTRY_OFFS * ((n) & 0x1ff)+ \
                                             EIP163_REG_OFFS * (m))
#define EIP163_REG_TCAM_CTRL_MASK(n)        EIP163_REG_TCAM_MASK((n), 0)

/* TCAM match enable control */
#define EIP163_REG_TCAM_ENTRY_ENABLE(n)     (EIP163_CONF_BASE + 0x8000 + \
                                             (0x10000 * ((n) >> 4)) + \
                                             EIP163_REG_OFFS * ((n) & 0xf))
#define EIP163_REG_TCAM_ENTRY_SET(n)        (EIP163_CONF_BASE + 0x8080 + \
                                             (0x10000 * ((n) >> 4)) + \
                                             EIP163_REG_OFFS * ((n) & 0xf))
#define EIP163_REG_TCAM_ENTRY_CLEAR(n)      (EIP163_CONF_BASE + 0x80C0 + \
                                             (0x10000 * ((n) >> 4)) + \
                                             EIP163_REG_OFFS * ((n) & 0xf))
#define EIP163_REG_TCAM_ENTRY_ENABLE_CTRL   (EIP163_CONF_BASE + 0x8100)
#define EIP163_REG_TCAM_STATUS              (EIP163_CONF_BASE + 0x8120)
#define EIP163_REG_SAM_IN_FLIGHT            (EIP163_CONF_BASE + 0x8104)

#define EIP163_REG_TCAM_COUNT_SUMMARY_CHAN1_CNT_MASK    MASK_4_BITS

/* MTT rules */
/** MTT enable control */
#define EIP163_REG_MTT_ENABLE_CTRL         (EIP163_CONF_BASE + 0x8108)

/** MTT enable/status */
#define EIP163_REG_MTT_ENABLE              (EIP163_CONF_BASE + 0x8110)


#define EIP163_REG_MTT_KEY(n)               (EIP163_CONF_BASE + 0x8400 + \
                                             (n) * 0x40)

#define EIP163_REG_MTT_MASK(n)              (EIP163_CONF_BASE + 0x8420 + \
                                             (n)* 0x40)

/* TCAM policy */
#define EIP163_REG_TCAM_POLICY_OFFS         (EIP163_CONF_BASE + 0x8800)
#define EIP163_REG_TCAM_POLICY(n)           (EIP163_REG_TCAM_POLICY_OFFS + \
                                             (0x10000 * ((n) >> 9)) + \
                                             EIP163_REG_OFFS * ((n) & 0x1ff))

/* vPort policy */
#define EIP163_REG_VPORT_POLICY_OFFS        (EIP163_CONF_BASE + 0x9000)
#define EIP163_REG_VPORT_POLICY(n)          (EIP163_REG_VPORT_POLICY_OFFS + \
                                             (0x10000 * ((n) >> 10)) + \
                                             EIP163_REG_OFFS * ((n) & 0x3ff))

/* Per-channel classifier settings, n - channel identifier */
#define EIP163_REG_CH_CFY_CTRL_OFFS         (EIP163_CONF_BASE + 0xA000)
#define EIP163_REG_CH_CFY_CTRL_ENTRY_OFFS   0x40
#define EIP163_REG_CP_MATCH_MODE_MASK       MASK_10_BITS
#define EIP163_REG_CP_MATCH_ENABLE_MASK     (BIT_31 | MASK_21_BITS)
#define EIP163_REG_CP_MAC_DA_MATCH_MASK     MASK_8_BITS
#define EIP163_REG_CP_MAC_DA_ET_MATCH_MASK  MASK_16_BITS
#define EIP163_REG_CP_MAC_DA_ET_RANGE_MASK  (BIT_17 | BIT_16)
#define EIP163_REG_CP_MAC_DA_RANGE_MASK     BIT_18
#define EIP163_REG_CP_MAC_DA_44BIT_MASK     BIT_19
#define EIP163_REG_CP_MAC_DA_48BIT_MASK     BIT_20

#define EIP163_REG_CP_MATCH_MODE(n)         (EIP163_REG_CH_CFY_CTRL_OFFS + \
                                             0x00 + \
                                             (0x10000 * ((n)>> 5)) + \
                                             EIP163_REG_CH_CFY_CTRL_ENTRY_OFFS * ((n)& 0x1F))
#define EIP163_REG_CP_MATCH_ENABLE(n)       (EIP163_REG_CH_CFY_CTRL_OFFS + \
                                             0x04 + \
                                             (0x10000 * ((n)>> 5)) + \
                                             EIP163_REG_CH_CFY_CTRL_ENTRY_OFFS * ((n)& 0x1F))
#define EIP163_REG_SAM_NM_PARAMS(n)         (EIP163_REG_CH_CFY_CTRL_OFFS + \
                                             0x08 + \
                                             (0x10000 * ((n)>> 5)) + \
                                             EIP163_REG_CH_CFY_CTRL_ENTRY_OFFS * ((n)& 0x1F))
#define EIP163_REG_SAM_POLICY(n)            (EIP163_REG_CH_CFY_CTRL_OFFS + \
                                             0x0C + \
                                             (0x10000 * ((n)>> 5)) + \
                                             EIP163_REG_CH_CFY_CTRL_ENTRY_OFFS * ((n)& 0x1F))
#define EIP163_REG_MPLS_ENB_SELECT(n)       (EIP163_REG_CH_CFY_CTRL_OFFS + \
                                             0x14 + \
                                             (0x10000 * (n) >> 5) + \
                                             EIP163_REG_CH_CFY_CTRL_ENTRY_OFFS * ((n)& 0x1F))
#define EIP163_REG_EGRESS_HDR_ETYPE(n)      (EIP163_REG_CH_CFY_CTRL_OFFS + \
                                             0x18 + \
                                             (0x10000 * ((n)>> 5)) + \
                                             EIP163_REG_CH_CFY_CTRL_ENTRY_OFFS * ((n)& 0x1F))
#define EIP163_REG_SAM_CP_TAG_ENB(n)        (EIP163_REG_CH_CFY_CTRL_OFFS + \
                                             0x1C + \
                                             (0x10000 * ((n)>> 5)) + \
                                             EIP163_REG_CH_CFY_CTRL_ENTRY_OFFS * ((n)& 0x1F))
#define EIP163_REG_NATIVE_VLAN_ID(n)        (EIP163_REG_CH_CFY_CTRL_OFFS + \
                                             0x34 + \
                                             (0x10000 * ((n)>> 5)) + \
                                             EIP163_REG_CH_CFY_CTRL_ENTRY_OFFS * ((n)& 0x1F))
#define EIP163_REG_IPSEC_ENABLE(n)          (EIP163_REG_CH_CFY_CTRL_OFFS + \
                                             0x38 + \
                                             (0x10000 * ((n)>> 5)) + \
                                             EIP163_REG_CH_CFY_CTRL_ENTRY_OFFS * ((n)& 0x1F))
#define EIP163_REG_SCP_MATCH_MODE(n)        (EIP163_REG_CH_CFY_CTRL_OFFS + \
                                             0x20 + \
                                             (0x10000 * ((n)>> 5)) + \
                                             EIP163_REG_CH_CFY_CTRL_ENTRY_OFFS * ((n)& 0x1F))
#define EIP163_REG_SCP_MATCH_ENABLE(n)      (EIP163_REG_CH_CFY_CTRL_OFFS + \
                                             0x24 + \
                                             (0x10000 * ((n)>> 5)) + \
                                             EIP163_REG_CH_CFY_CTRL_ENTRY_OFFS * ((n)& 0x1F))
#define EIP163_REG_SAM_SCP_TAG_ENB(n)       (EIP163_REG_CH_CFY_CTRL_OFFS + \
                                             0x3C + \
                                             (0x10000 * ((n)>> 5)) + \
                                             EIP163_REG_CH_CFY_CTRL_ENTRY_OFFS * ((n)& 0x1F))
#define EIP163_REG_L3L4_ENABLE(n)           (EIP163_CONF_BASE + 0xa038 + \
                                             (0x10000 * ((n)>> 5)) + \
                                              (0x40 *((n)& 0x1F)))


/* Global Control Packet Detector (CPD) control registers */
#define EIP163_REG_CPD_OFFS                     (EIP163_CONF_BASE  + 0xA800)
#define EIP163_REG_CP_MAC_DA_MATCH_0            (EIP163_REG_CPD_OFFS + 0x00)
#define EIP163_REG_CP_MAC_DA_ET_MATCH_0         (EIP163_REG_CPD_OFFS + 0x04)
#define EIP163_REG_CP_MAC_DA_MATCH_1            (EIP163_REG_CPD_OFFS + 0x08)
#define EIP163_REG_CP_MAC_DA_ET_MATCH_1         (EIP163_REG_CPD_OFFS + 0x0C)
#define EIP163_REG_CP_MAC_DA_MATCH_2            (EIP163_REG_CPD_OFFS + 0x10)
#define EIP163_REG_CP_MAC_DA_ET_MATCH_2         (EIP163_REG_CPD_OFFS + 0x14)
#define EIP163_REG_CP_MAC_DA_MATCH_3            (EIP163_REG_CPD_OFFS + 0x18)
#define EIP163_REG_CP_MAC_DA_ET_MATCH_3         (EIP163_REG_CPD_OFFS + 0x1C)
#define EIP163_REG_CP_MAC_DA_MATCH_4            (EIP163_REG_CPD_OFFS + 0x20)
#define EIP163_REG_CP_MAC_DA_ET_MATCH_4         (EIP163_REG_CPD_OFFS + 0x24)
#define EIP163_REG_CP_MAC_DA_MATCH_5            (EIP163_REG_CPD_OFFS + 0x28)
#define EIP163_REG_CP_MAC_DA_ET_MATCH_5         (EIP163_REG_CPD_OFFS + 0x2C)
#define EIP163_REG_CP_MAC_DA_MATCH_6            (EIP163_REG_CPD_OFFS + 0x30)
#define EIP163_REG_CP_MAC_DA_ET_MATCH_6         (EIP163_REG_CPD_OFFS + 0x34)
#define EIP163_REG_CP_MAC_DA_MATCH_7            (EIP163_REG_CPD_OFFS + 0x38)
#define EIP163_REG_CP_MAC_DA_ET_MATCH_7         (EIP163_REG_CPD_OFFS + 0x3C)
#define EIP163_REG_CP_MAC_DA_MATCH(n)           (EIP163_REG_CP_MAC_DA_MATCH_0 + \
                                                 (n) * 0x08)
#define EIP163_REG_CP_MAC_DA_ET_MATCH(n)        (EIP163_REG_CP_MAC_DA_ET_MATCH_0 + \
                                                 (n)* 0x08)

#define EIP163_REG_CP_MAC_DA_START0_LO          (EIP163_REG_CPD_OFFS + 0x60)
#define EIP163_REG_CP_MAC_DA_START0_HI          (EIP163_REG_CPD_OFFS + 0x64)
#define EIP163_REG_CP_MAC_DA_END0_LO            (EIP163_REG_CPD_OFFS + 0x68)
#define EIP163_REG_CP_MAC_DA_END0_HI            (EIP163_REG_CPD_OFFS + 0x6C)
#define EIP163_REG_CP_MAC_DA_START1_LO          (EIP163_REG_CPD_OFFS + 0x70)
#define EIP163_REG_CP_MAC_DA_START1_HI          (EIP163_REG_CPD_OFFS + 0x74)
#define EIP163_REG_CP_MAC_DA_END1_LO            (EIP163_REG_CPD_OFFS + 0x78)
#define EIP163_REG_CP_MAC_DA_END1_HI            (EIP163_REG_CPD_OFFS + 0x7C)
#define EIP163_REG_CP_MAC_DA_START_LO(n)        (EIP163_REG_CP_MAC_DA_START0_LO + \
                                                 (n)* 0x08)
#define EIP163_REG_CP_MAC_DA_START_HI(n)        (EIP163_REG_CP_MAC_DA_START0_HI + \
                                                 (n)* 0x08)
#define EIP163_REG_CP_MAC_DA_END_LO(n)          (EIP163_REG_CP_MAC_DA_END0_LO + \
                                                 (n)* 0x08)
#define EIP163_REG_CP_MAC_DA_END_HI(n)          (EIP163_REG_CP_MAC_DA_END0_HI + \
                                                 (n)* 0x08)

/* Range only (RO) */
#define EIP163_REG_CP_MAC_DA_START_RO_LO        (EIP163_REG_CPD_OFFS + 0x80)
#define EIP163_REG_CP_MAC_DA_START_RO_HI        (EIP163_REG_CPD_OFFS + 0x84)
#define EIP163_REG_CP_MAC_DA_END_RO_LO          (EIP163_REG_CPD_OFFS + 0x88)
#define EIP163_REG_CP_MAC_DA_END_RO_HI          (EIP163_REG_CPD_OFFS + 0x8C)

#define EIP163_REG_CP_MAC_DA_44_BITS_LO         (EIP163_REG_CPD_OFFS + 0x90)
#define EIP163_REG_CP_MAC_DA_44_BITS_HI         (EIP163_REG_CPD_OFFS + 0x94)
#define EIP163_REG_CP_MAC_DA_48_BITS_LO         (EIP163_REG_CPD_OFFS + 0x98)
#define EIP163_REG_CP_MAC_DA_48_BITS_HI         (EIP163_REG_CPD_OFFS + 0x9C)

#define EIP163_REG_CP_MAC_DA_IPSEC_LO           (EIP163_CONF_BASE + 0xA8E0)
#define EIP163_REG_CP_MAC_DA_IPSEC_HI           (EIP163_CONF_BASE + 0xA8E4)

/* Global Header Parser (GHP) control registers */
#define EIP163_REG_GHP_OFFS                     (EIP163_CONF_BASE  + 0xA900)
#define EIP163_REG_SAM_CP_TAG                   (EIP163_REG_GHP_OFFS + 0x00)
#define EIP163_REG_SAM_PP_TAGS                  (EIP163_REG_GHP_OFFS + 0x04)
#define EIP163_REG_SAM_PP_TAGS2                 (EIP163_REG_GHP_OFFS + 0x08)
#define EIP163_REG_MPLS_ETYPE1                  (EIP163_REG_GHP_OFFS + 0x20)
#define EIP163_REG_MPLS_ETYPE2                  (EIP163_REG_GHP_OFFS + 0x24)
#define EIP163_REG_SAM_CP_TAG2                  (EIP163_REG_GHP_OFFS + 0x0C)

#define EIP163_REG_UDP_PORT1                    (EIP163_CONF_BASE + 0xA930)
#define EIP163_REG_UDP_PORT2                    (EIP163_CONF_BASE + 0xA934)
/* Packet processing debug registers */
#define EIP163_REG_CP_MATCH_DEBUG               (EIP163_CONF_BASE + 0xAC00)
#define EIP163_REG_TCAM_DEBUG                   (EIP163_CONF_BASE + 0xAC24)
#define EIP163_REG_SECTAG_DEBUG                 (EIP163_CONF_BASE + 0xAC28)
#define EIP163_REG_SAMPP_DEBUG1                 (EIP163_CONF_BASE + 0xAC80)
#define EIP163_REG_SAMPP_DEBUG2                 (EIP163_CONF_BASE + 0xAC84)
#define EIP163_REG_SAMPP_DEBUG3                 (EIP163_CONF_BASE + 0xAC88)
#define EIP163_REG_EHDR_DEBUG                   (EIP163_CONF_BASE + 0xAC90)
#define EIP163_REG_MPLS_DEBUG1                  (EIP163_CONF_BASE + 0xAC94)
#define EIP163_REG_MPLS_DEBUG2                  (EIP163_CONF_BASE + 0xAC98)
#define EIP163_REG_DBG_PARSED_INNER_SA_LO       (EIP163_CONF_BASE + 0xACA0)
#define EIP163_REG_DBG_PARSED_INNER_SA_HI       (EIP163_CONF_BASE + 0xACA4)

#define EIP163_REG_DBG_PARSED_SCI_LO            (EIP163_CONF_BASE + 0xAD18)

#define EIP163_REG_DBG_PARSED_SCI_HI            (EIP163_CONF_BASE + 0xAD1C)
#define EIP163_REG_IP_DEBUG1                    (EIP163_CONF_BASE + 0xAD70)
#define EIP163_REG_IP_DEBUG2                    (EIP163_CONF_BASE + 0xAD74)
#define EIP163_REG_IP_DEBUG_DA0                 (EIP163_CONF_BASE + 0xAD80)
#define EIP163_REG_IP_DEBUG_DA1                 (EIP163_CONF_BASE + 0xAD84)
#define EIP163_REG_IP_DEBUG_DA2                 (EIP163_CONF_BASE + 0xAD88)
#define EIP163_REG_IP_DEBUG_DA3                 (EIP163_CONF_BASE + 0xAD8C)
#define EIP163_REG_UDP_DEBUG1                   (EIP163_CONF_BASE + 0xAD90)
#define EIP163_REG_UDP_DEBUG2                   (EIP163_CONF_BASE + 0xAD94)
#define EIP163_REG_IPSEC_DEBUG1                 (EIP163_CONF_BASE + 0xAD98)
#define EIP163_REG_IPSEC_SPI                    (EIP163_CONF_BASE + 0xAD9C)
#define EIP163_REG_MTT_DEBUG1                   (EIP163_CONF_BASE + 0xADA0)
#define EIP163_REG_MTT_RAW_MATCH1               (EIP163_CONF_BASE + 0xADC0)

#define EIP163_REG_DBG_PARSED_DA_LO             (EIP163_CONF_BASE + 0xAD00)
#define EIP163_REG_DBG_PARSED_DA_HI             (EIP163_CONF_BASE + 0xAD04)
#define EIP163_REG_DBG_PARSED_SA_LO             (EIP163_CONF_BASE + 0xAD08)
#define EIP163_REG_DBG_PARSED_SA_HI             (EIP163_CONF_BASE + 0xAD0C)
#define EIP163_REG_DBG_PARSED_SECTAG_LO         (EIP163_CONF_BASE + 0xAD10)
#define EIP163_REG_DBG_PARSED_SECTAG_HI         (EIP163_CONF_BASE + 0xAD14)
#define EIP163_REG_DEBUG_FLOW_LOOKUP            (EIP163_CONF_BASE + 0xAD20)

/* TCAM registers bank offsets */
/* EIP-217 register bank: statistics counters */
#define EIP163_REG_TCAM_STAT_COUNT_OFFS(n)      (EIP163_CONF_BASE + 0xC000 + \
                                                 (0x10000 *((n) >> 9)) + 8 * ((n) & 0x1ff))

#define EIP163_REG_TCAM_STAT_POSTED_RES         (EIP163_CONF_BASE + 0xDC00)
/* EIP-217 register bank: statistics controls */
#define EIP163_REG_TCAM_STAT_CTRL_OFFS          (EIP163_CONF_BASE + 0xD800)
#define EIP163_REG_TCAM_SUMMARY_P_OFFS          (EIP163_CONF_BASE + 0xD000)

/* CHAN registers bank offsets */
/* EIP-217 register bank: statistics counters */
#define EIP163_CHAN_STAT_TCAM_HIT_MULTIPLE          0
#define EIP163_CHAN_STAT_HDRPARSER_DROPPED_PKTS     1
#define EIP163_CHAN_STAT_TCAM_MISS                  2
#define EIP163_CHAN_STAT_PKTS_CTRL                  3
#define EIP163_CHAN_STAT_PKTS_DATA                  4
#define EIP163_CHAN_STAT_PKTS_DROP                  5
#define EIP163_CHAN_STAT_PKTS_ERR_IN                6
#define EIP163_CHAN_STAT_PKTS_MTT_MISS              7

#define EIP164_REG_CHn_STAT_BASE_OFFS               0x40
#define EIP163_REG_CHAN_STAT_COUNT_OFFS(n)          (EIP163_CONF_BASE + 0xE000 + \
                                                     (0x10000 * ((n)>> 5)) + \
                                                     (EIP164_REG_CHn_STAT_BASE_OFFS * ((n)& 0x1F)))
#define EIP163_REG_CHAN_STAT_POSTED_RES             (EIP163_CONF_BASE + 0xEE00)

/* EIP-217 register bank: statistics controls */
#define EIP163_REG_CHAN_STAT_CTRL_OFFS              (EIP163_CONF_BASE + 0xEC00)
#define EIP163_REG_CHAN_SUMMARY_P_OFFS              (EIP163_CONF_BASE + 0xE800)

/* MTT statistics counters */
#define EIP163_REG_MTT_STAT_COUNT_OFFS(n)           (EIP163_CONF_BASE + 0xF000 + 8 *(n))
#define EIP163_REG_MTT_STAT_POSTED_RES              (EIP163_CONF_BASE + 0xF300)

/* EIP-217 register bank: statistics controls */
#define EIP163_REG_MTT_STAT_CTRL_OFFS               (EIP163_CONF_BASE + 0xF200)
#define EIP163_REG_MTT_SUMMARY_P_OFFS               (EIP163_CONF_BASE + 0xF100)
/* Ingress MTT hit counters */
#define EIP163_REG_MTTCAM_COUNT_DEBUG1              (EIP163_CONF_BASE + 0xF200)
#define EIP163_REG_MTTCAM_COUNT_DEBUG4              (EIP163_CONF_BASE + 0xF20c)
#define EIP163_REG_MTTCAM_COUNT_CONTROL             (EIP163_CONF_BASE + 0xF210)
#define EIP163_REG_MTTCAM_COUNT_INCEN1              (EIP163_CONF_BASE + 0xF214)
#define EIP163_REG_MTTCAM_COUNT_PACK_TIMING         (EIP163_CONF_BASE + 0xF21C)

#define EIP163_REG_MTTCAM_COUNT_FRAME_THR_1         (EIP163_CONF_BASE + 0xF220)
#define EIP163_REG_MTTCAM_COUNT_FRAME_THR_2         (EIP163_CONF_BASE + 0xF224)

#define EIP163_REG_MTTCAM_COUNT_POSTED_CTRL         (EIP163_CONF_BASE + 0xF238)
#define EIP163_REG_MTTCAM_COUNT_OPTIONS2            (EIP163_CONF_BASE + 0xFA74)
#define EIP163_REG_MTTCAM_COUNT_OPTIONS             (EIP163_CONF_BASE + 0xFA78)
#define EIP163_REG_MTTCAM_COUNT_VERSION             (EIP163_CONF_BASE + 0xFA7C)
#define EIP163_REG_MTTCAM_COUNT_POSTED_RES_LO_0     (EIP163_CONF_BASE + 0xF300)
#define EIP163_REG_MTTCAM_COUNT_POSTED_RES_HI_0     (EIP163_CONF_BASE + 0xF304)

/* Input adapter */
#define EIP163_REG_RX_INSERT_SOP(n)         (EIP163_CONF_BASE + 0xFC80 + \
                                             (0x10000 * (n)))
#define EIP163_REG_RX_INSERT_EOP(n)         (EIP163_CONF_BASE + 0xFC84 + \
                                             (0x10000 * (n)))
#define EIP163_REG_RX_TIMEOUT_CTRL(n)       (EIP163_CONF_BASE + 0xFC88 + \
                                             (0x10000 * (n)))
#define EIP163_REG_RX_TIMEOUT_VAL           (EIP163_CONF_BASE + 0xFC8C)
#define EIP163_REG_RX_TIMEOUT_STATE(n)      (EIP163_CONF_BASE + 0xFC90 + \
                                             (0x10000 * (n)))
#define EIP163_REG_RX_FILTER_STATE(n)       (EIP163_CONF_BASE + 0xFC94 + \
                                             (0x10000 * (n)))

/* Channel controls */
#define EIP163_REG_CHANNEL_CTRL(n)          (EIP163_CONF_BASE + 0xFE00 + \
                                             (0x10000 * ((n)>> 5)) + \
                                             (EIP163_REG_OFFS * ((n)& 0x1f)))

#define EIP163_REG_LOW_LAT_CONFIG           (EIP163_CONF_BASE + 0xFE80)

/* ECC status */
#define EIP163_REG_ECC_COUNTER_RAM(n)       (EIP163_CONF_BASE + 0xFF00 + \
                                             (EIP163_REG_OFFS * (n)))
#define EIP163_REG_ECC_CORR_ENABLE          (EIP163_CONF_BASE + 0xFF60)
#define EIP163_REG_ECC_DERR_ENABLE          (EIP163_CONF_BASE + 0xFF64)
#define EIP163_REG_ECC_THR_CORR_STAT        (EIP163_CONF_BASE + 0xFF68)
#define EIP163_REG_ECC_THR_DERR_STAT        (EIP163_CONF_BASE + 0xFF6C)
#define EIP163_REG_ECC_THRESHOLDS           (EIP163_CONF_BASE + 0xFF78)

/* Global Control Register */
#define EIP163_REG_GLBL_CTRL                (EIP163_CONF_BASE + 0xFFE4)


/* System control */
/* Debug clocks related */
#define EIP163_REG_CLOCK_STATE              (EIP163_CONF_BASE + 0xFFE8)
#define EIP163_REG_FORCE_CLOCK_ON           (EIP163_CONF_BASE + 0xFFEC)
#define EIP163_REG_FORCE_CLOCK_OFF          (EIP163_CONF_BASE + 0xFFF0)

/* EIP-163 configuration and version information registers */
#define EIP163_REG_CONFIG2                  (EIP163_CONF_BASE + 0xFFF4)
#define EIP163_REG_CONFIG                   (EIP163_CONF_BASE + 0xFFF8)
#define EIP163_REG_VERSION                  (EIP163_CONF_BASE + 0xFFFC)

/* Default (reset) register values */
/* Note: when updating the default register values from 0 to something else */
/*       check how this value is used in the corresponding level0 macro, */
/*       it may need to be updated too for the boolean operations! */
#define EIP163_REG_VPORT_POLICY_DEFAULT             0x00000000
#define EIP163_REG_CHANNEL_CTRL_DEFAULT             0x00000000
#define EIP163_REG_TCAM_CTRL_KEY_DEFAULT            0x00000000
#define EIP163_REG_TCAM_CTRL_MASK_DEFAULT           0x00000000
#define EIP163_REG_TCAM_ENTRY_ENABLE_CTRL_DEFAULT   0x00000000
#define EIP163_REG_EGRESS_HDR_ETYPE_DEFAULT         0x00000000
#define EIP163_REG_SAM_IN_FLIGHT_DEFAULT            0x00000000
#define EIP163_REG_TCAM_POLICY_DEFAULT              0x00000000
#define EIP163_REG_CP_MATCH_MODE_DEFAULT            0x00000000
#define EIP163_REG_CP_MATCH_ENABLE_DEFAULT          0x00000000
#define EIP163_REG_SAM_NM_PARAMS_DEFAULT            0xE5880007
#define EIP163_REG_SAM_POLICY_DEFAULT               0x00000000
#define EIP163_REG_SAM_CP_TAG_ENB_DEFAULT           0x00000000
#define EIP163_REG_SCP_MATCH_MODE_DEFAULT           0x00000000
#define EIP163_REG_SCP_MATCH_ENABLE_DEFAULT         0x00000000
#define EIP163_REG_SAM_SCP_TAG_ENB_DEFAULT          0x00000000
#define EIP163_REG_CP_MAC_DA_MATCH_DEFAULT          0x00000000
#define EIP163_REG_CP_MAC_DA_ET_MATCH_DEFAULT       0x00000000
#define EIP163_REG_CP_MAC_DA_44_BITS_LO_DEFAULT     0x00C28001
#define EIP163_REG_CP_MAC_DA_44_BITS_HI_DEFAULT     0x00000000
#define EIP163_REG_CP_MAC_DA_48_BITS_LO_DEFAULT     0xCC0C0001
#define EIP163_REG_CP_MAC_DA_48_BITS_HI_DEFAULT     0x0000CCCC
#define EIP163_REG_SAM_CP_TAG_DEFAULT               0x00000000
#define EIP163_REG_SAM_CP_TAG2_DEFAULT              0x00000000
#define EIP163_REG_SAM_PP_TAGS_DEFAULT              0xA8880081
#define EIP163_REG_SAM_PP_TAGS2_DEFAULT             0x00920091
#define EIP163_REG_MPLS_ENB_SELECT_DEFAULT          0x00000000
#define EIP163_REG_MPLS_ETYPE1_DEFAULT              0x48884788
#define EIP163_REG_MPLS_ETYPE2_DEFAULT              0x00000000
#define EIP163_REG_IPSEC_ENABLE_DEFAULT             0x00000000

#endif /* EIP163_HW_INTERFACE_H_ */


/* end of file eip163_hw_interface.h */
