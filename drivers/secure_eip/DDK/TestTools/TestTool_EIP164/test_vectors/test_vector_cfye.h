/* test_vector_cfye.h
 *
 * Test vectors for the test case CfyE vPort and device data
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

#ifndef TEST_VECTOR_CFYE_H_
#define TEST_VECTOR_CFYE_H_

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Test Case record format */
#include "test_record.h"

/*----------------------------------------------------------------------------
 * Definitions and macros
 */

#define CfyE_Rule_KeyMask_MACsec(ChannelID, TCI)                            \
{                                                                           \
    /* Packet type */                                                       \
    CFYE_RULE_PKT_TYPE_MACSEC,                                              \
                                                                            \
    /* numTags - Tags info */                                               \
    TCI,                                                                    \
                                                                            \
    /* ChannelID */                                                         \
    ChannelID,                                                              \
}


#if defined(TEST_IPSEC_ENABLE)
#define CfyE_Rule_KeyMask_MPLS_IPSEC(ChannelID, Labels, NumTagsExtn)        \
{                                                                           \
    /* Packet type */                                                       \
    CFYE_RULE_PKT_TYPE_OTHER,                                               \
                                                                            \
    /* numTags - Tags info */                                               \
    3,                                                                      \
                                                                            \
    /* ChannelID */                                                         \
    ChannelID,                                                              \
}

#define CfyE_Rule_KeyMask_VLAN_IPSEC(ChannelID, Labels, NumTagsExtn)        \
{                                                                           \
    /* Packet type */                                                       \
    CFYE_RULE_PKT_TYPE_OTHER,                                               \
                                                                            \
    /* numTags - Tags info */                                               \
    3,                                                                      \
                                                                            \
    /* ChannelID */                                                         \
    ChannelID,                                                              \
}

#define CfyE_Rule_KeyMask_IPSEC_INGRESS(ChannelID, Labels, NumTagsExtn)     \
{                                                                           \
    /* Packet type */                                                       \
    CFYE_RULE_PKT_TYPE_IPSEC,                                              \
                                                                            \
    /* numTags - Tags info */                                               \
    Labels,                                                                 \
                                                                            \
    /* ChannelID */                                                         \
    ChannelID,                                                              \
}

#define CfyE_Rule_KeyMask_IPsec_Ingress_Common(Pkt_Type, Labels, ChannelID )\
{                                                                           \
    /* Packet type */                                                       \
    Pkt_Type,                                                               \
                                                                            \
    /* numTags - Tags info */                                               \
    Labels,                                                                 \
                                                                            \
    /* ChannelID */                                                         \
    ChannelID,                                                              \
}
#endif

#define CfyE_Rule_KeyMask_VLAN(ChannelID, Labels, NumTagsExtn)              \
{                                                                           \
    /* Packet type */                                                       \
    CFYE_RULE_PKT_TYPE_OTHER,                                               \
                                                                            \
    /* numTags - Tags info */                                               \
    (Labels > 4) ? (1 << 6) : (1 << Labels),                                \
                                                                            \
    /* ChannelID */                                                         \
    ChannelID,                                                              \
}

#define CfyE_Rule_KeyMask_VXLAN(ChannelID, Labels)                          \
{                                                                           \
    /* Packet type */                                                       \
    CFYE_RULE_PKT_TYPE_OTHER,                                               \
                                                                            \
    /* numTags - Tags info */                                               \
    0x20 | ((Labels > 4) ? (1 << 6) : (1 << Labels)),                       \
                                                                            \
    /* ChannelID */                                                         \
    ChannelID,                                                              \
}


#define CfyE_Rule_KeyMask_Other(ChannelID, numTags, NumTagsExtn)            \
{                                                                           \
    /* Packet type */                                                       \
    CFYE_RULE_PKT_TYPE_OTHER,                                               \
                                                                            \
    /* numTags - Tags info */                                               \
    numTags,                                                                \
                                                                            \
    /* ChannelID */                                                         \
    ChannelID,                                                              \
}

#define CfyE_Rule_KeyMask_Raw(Type, numTags, ChannelID, Extra, NumTagsExtn) \
{                                                                           \
    /* Packet type */                                                       \
    Type,                                                                   \
                                                                            \
    /* numTags - Tags info */                                               \
    numTags,                                                                \
                                                                            \
    /* ChannelID */                                                         \
    ChannelID,                                                              \
}

#if defined(TEST_IPSEC_ENABLE)

#define CfyE_Rule_KeyMask_IPSEC_Other(Type, numTags, ChannelID, Extra, NumTagsExtn) \
{                                                                           \
    /* Packet type */                                                       \
    CFYE_RULE_PKT_TYPE_IPSEC,                                              \
                                                                            \
    /* numTags - Tags info */                                               \
    numTags,                                                                \
                                                                            \
    /* ChannelID */                                                         \
    ChannelID,                                                              \
}


#define CfyE_Rule_KeyMask_IPSEC_Ingress_Common(Type, numTags, ChannelID)    \
{                                                                           \
    /* Packet type */                                                       \
    Type,                                                                   \
                                                                            \
    /* numTags - Tags info */                                               \
    numTags,                                                                \
                                                                            \
    /* ChannelID */                                                         \
    ChannelID,                                                              \
}
#endif

#define Common_CfyE_Rule_Policy(vPortId, Priority, AN, fDrop, fControl)     \
{                                                                           \
    /* vPort number */                                                      \
    (CfyE_vPortHandle_t)vPortId,                                            \
                                                                            \
    /* Priority */                                                          \
    Priority,                                                               \
                                                                            \
    /** vPort to SA association number */                                   \
    AN,                                                                     \
                                                                            \
    /* Drop packet if true */                                               \
    fDrop,                                                                  \
                                                                            \
    /* Control packet if true */                                            \
    fControl,                                                               \
                                                                            \
    /* Sub control packet */                                                \
    false                                                                   \
}

#define Common_CfyE_vPort_Policy(SecTagOffset, MPLS_Hdr, fDummy1, fDummy2, Expansion) \
{                                                                           \
    /* SecTag offset */                                                     \
    SecTagOffset,                                                           \
                                                                            \
    /* MPLS header options (ingress-only) */                                \
    MPLS_Hdr,                                                               \
                                                                            \
                                                                            \
    /* Packet expansion */                                                  \
    Expansion                                                               \
}

extern Test_Case_CfyE_Data_t CfyE_Data_LowLatencyBypass;

extern Test_Case_CfyE_Data_t CfyE_Data_Untagged_Egress_NoEnc;
extern Test_Case_CfyE_Data_t CfyE_Data_Untagged_Egress_MACsec_bn;
extern Test_Case_CfyE_Data_t CfyE_Data_Untagged_Ingress_NoEnc;
extern Test_Case_CfyE_Data_t CfyE_Data_Untagged_Ingress_MACsec_bn;
extern Test_Case_CfyE_Data_t CfyE_Data_VLAN_1Q_Egress_MACsec_O1;
extern Test_Case_CfyE_Data_t CfyE_Data_VLAN_1Q_Egress_MACsec_O2;
extern Test_Case_CfyE_Data_t CfyE_Data_VLAN_1Q_Ingress_MACsec_O1;
extern Test_Case_CfyE_Data_t CfyE_Data_VLAN_1Q_Ingress_MACsec_O2;
extern Test_Case_CfyE_Data_t CfyE_Data_VLAN_QinQ_Egress_MACsec_O3;
extern Test_Case_CfyE_Data_t CfyE_Data_VLAN_QinQ_Ingress_MACsec_O3;
extern Test_Case_CfyE_Data_t CfyE_Data_VLAN_QinQinQ_Egress_MACsec_O4;
extern Test_Case_CfyE_Data_t CfyE_Data_VLAN_QinQinQ_Ingress_MACsec_O4;
extern Test_Case_CfyE_Data_t CfyE_Data_CtrlPacket_PriEgress;
extern Test_Case_CfyE_Data_t CfyE_Data_CtrlPacket_PriIngress;
extern Test_Case_CfyE_Data_t CfyE_Data_VxLAN_IPv6_Egress_MACsec;
extern Test_Case_CfyE_Data_t CfyE_Data_VxLAN_IPv4_Egress_MACsec;
extern Test_Case_CfyE_Data_t CfyE_Data_VxLAN_IPv6_Ingress_MACsec;
extern Test_Case_CfyE_Data_t CfyE_Data_VxLAN_IPv4_Ingress_MACsec;
extern Test_Case_CfyE_Data_t CfyE_Data_LimitsEgress;
extern Test_Case_CfyE_Data_t CfyE_Data_LimitsIngress;

extern Test_Case_CfyE_Data_t CfyE_Data_MultipleChannelReconfig_Egress_UntaggedMACsec;
extern Test_Case_CfyE_Data_t CfyE_Data_MultipleChannelReconfig_Ingress_UntaggedMACsec;

#if defined(TEST_IPSEC_ENABLE)
extern Test_Case_CfyE_Data_t CfyE_Data_Egress_IPsec_O1;
extern Test_Case_CfyE_Data_t CfyE_Data_Egress_IPsec_UDP;
extern Test_Case_CfyE_Data_t CfyE_Data_Egress_IPsecMPLS;
extern Test_Case_CfyE_Data_t CfyE_Data_Egress_IPsecVLAN;
extern Test_Case_CfyE_Data_t CfyE_Data_Ingress_IPsec_O1;
extern Test_Case_CfyE_Data_t CfyE_Data_Ingress_IPsec_UDP;
extern Test_Case_CfyE_Data_t CfyE_Data_IPsecIngressVLAN;
extern Test_Case_CfyE_Data_t CfyE_Data_IPsecIngressMPLS;
extern Test_Case_CfyE_Data_t CfyE_Data_IPsecIngressMPLS_Bypass;
extern Test_Case_CfyE_Data_t CfyE_Data_Ingress_IPsec_LateCheck;
extern Test_Case_CfyE_Data_t CfyE_Data_Egress_IPsec_MACsec;
extern Test_Case_CfyE_Data_t CfyE_Data_IPsec_MACsec_Ingress;
extern Test_Case_CfyE_Data_t CfyE_Data_ReplayFail_IPsec_Ingress;
extern Test_Case_CfyE_Data_t CfyE_Data_MultiSA_IPsec_Egress;
extern Test_Case_CfyE_Data_t CfyE_Data_MultiSA_IPsec_Ingress;
extern Test_Case_CfyE_Data_t CfyE_Data_MultiSA_IPsec_Egress_Test;
#endif

#endif /* TEST_VECTOR_CFYE_H_ */


/* end of file test_vector_cfye.h */
