/* test_vector_kat1_basic_transform.h
 *
 * Test Tool for CfyE and SecY API's
 * Test vector for the basic transform test case
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

#ifndef TEST_VECTOR_KAT_1_BASIC_TRANSFORM_H_
#define TEST_VECTOR_KAT_1_BASIC_TRANSFORM_H_

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Default configuration */
#include "c_test_macsec.h"

/* Driver Framework Basic Defs API */
#include "basic_defs.h"

/* Test Case KAT 1 record format */
#include "test_record_kat1.h"

#include "test_vector_conf.h"
#include "test_vector_packet.h"
#include "test_vector_transform.h"
#include "test_vector_vport.h"
#include "test_vector_cfye.h"
#include "test_vector_rule.h"


/*----------------------------------------------------------------------------
 * Local variables
 */


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

/* Basic MACsec Egress Test Case */
#define TEST_MACSEC_REC_PKT_BASIC_TRANSFORM_EGRESS                      \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressBasicTransform,                                    \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0102 Basic Transform Egress Test Case",                          \
                                                                        \
    /* CfyE data */                                                     \
    NULL,                                                               \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_Basic_Transform_Egress,                                  \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* Packet data */                                                   \
    &Packet_Basic_Transform_Egress,                                     \
                                                                        \
    /* Number of Channel rules to install */                            \
    0,                                                                  \
                                                                        \
    /* Channel rules to install */                                      \
    NULL,                                                               \
                                                                        \
    /* Number of Secure Channel rules to install */                     \
    0,                                                                  \
                                                                        \
    /* Secure Channel rules to install */                               \
    NULL,                                                               \
                                                                        \
    /* Number of vPort statistics entries */                            \
    1,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    &vPortStat_Basic_Transform_Egress,                                    \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                              \
}


/* Basic MACsec Ingress Test Case */
#define TEST_MACSEC_REC_PKT_BASIC_TRANSFORM_INGRESS                     \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressBasicTransform,                                   \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0103 Basic Transform Ingress Test Case",                         \
                                                                        \
    /* CfyE data */                                                     \
    NULL,                                                               \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_Basic_Transform_Ingress,                                 \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* Packet data*/                                                    \
    &Packet_Basic_Transform_Ingress,                                    \
                                                                        \
    /* Number of Channel rules to install */                            \
    4,                                                                  \
                                                                        \
    /* Channel rules to install */                                      \
    ChannelRules_Ingress_Default,                                       \
                                                                        \
    /* Number of Secure Channel rules to install */                     \
    0,                                                                  \
                                                                        \
    /* Secure Channel rules to install */                               \
    NULL,                                                               \
                                                                        \
    /* Number of vPort statistics entries */                            \
    1,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    &vPortStat_Basic_Transform_Ingress,                                 \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}


/* Basic MACsec Egress Test Case with SA Expire. */
#define TEST_MACSEC_REC_PKT_EXPIRE_EGRESS                               \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressBasicTransform,                                    \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0122 Basic Transform Egress SA Expire Test Case",                \
                                                                        \
    /* CfyE data */                                                     \
    NULL,                                                               \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_Expire_Egress,                                           \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* Packet data */                                                   \
    &Packet_Expire_Egress,                                              \
                                                                        \
    /* Number of Channel rules to install */                            \
    0,                                                                  \
                                                                        \
    /* Channel rules to install */                                      \
    NULL,                                                               \
                                                                        \
    /* Number of Secure Channel rules to install */                     \
    0,                                                                  \
                                                                        \
    /* Secure Channel rules to install */                               \
    NULL,                                                               \
                                                                        \
    /* Number of vPort statistics entries */                            \
    1,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    &vPortStat_Basic_Transform_Egress,                                  \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}


/* Allow Egress Data Packets Test Case */
#define TEST_MACSEC_REC_PKT_ALLOW_EGRESS_DATA_PACKETS                   \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressMultiTransform,                                    \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0130 Allow Egress Data Packets Test Case",                       \
                                                                        \
    /* CfyE data */                                                     \
    NULL,                                                               \
                                                                        \
    /* Number of transforms */                                          \
    2,                                                                  \
                                                                        \
    /* Transform data */                                                \
    Transform_AllowEgressDataPackets,                                   \
                                                                        \
    /* Number of packets to process */                                  \
    2,                                                                  \
                                                                        \
    /* Packet data */                                                   \
    Packet_AllowEgressDataPackets,                                      \
                                                                        \
    /* Number of Channel rules to install */                            \
    0,                                                                  \
                                                                        \
    /* Channel rules to install */                                      \
    NULL,                                                               \
                                                                        \
    /* Number of Secure Channel rules to install */                     \
    0,                                                                  \
                                                                        \
    /* Secure Channel rules to install */                               \
    NULL,                                                               \
                                                                        \
    /* Number of vPort statistics entries */                            \
    2,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    vPortStat_AllowEgressDataPackets,                                   \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}


/* Allow Ingress Untagged Packets Test Case */
#define TEST_MACSEC_REC_PKT_ALLOW_INGRESS_UNTAGGED_PACKETS              \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressMultiTransform,                                   \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0131 Allow Ingress Untagged Packets Test Case",                  \
                                                                        \
    /* CfyE data */                                                     \
    NULL,                                                               \
                                                                        \
    /* Number of transforms */                                          \
    2,                                                                  \
                                                                        \
    /* Transform data */                                                \
    Transform_AllowIngressUntaggedPackets,                              \
                                                                        \
    /* Number of packets to process */                                  \
    2,                                                                  \
                                                                        \
    /* Packet data */                                                   \
    Packet_AllowIngressUntaggedPackets,                                 \
                                                                        \
    /* Number of Channel rules to install */                            \
    0,                                                                  \
                                                                        \
    /* Channel rules to install */                                      \
    NULL,                                                               \
                                                                        \
    /* Number of Secure Channel rules to install */                     \
    0,                                                                  \
                                                                        \
    /* Secure Channel rules to install */                               \
    NULL,                                                               \
                                                                        \
    /* Number of vPort statistics entries */                            \
    2,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    vPortStat_AllowIngressUntaggedPackets,                              \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}

/* Egress Untagged Packet Test Case */
#define TEST_MACSEC_REC_PKT_EGRESS_UNTAGGED_PACKET                      \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressDefaultBypass,                                     \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0132 Egress Untagged Packet Test Case",                          \
                                                                        \
    /* CfyE data */                                                     \
    NULL,                                                               \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_Untagged_Egress,                                         \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* Packet data */                                                   \
    &Packet_Untagged_Egress,                                            \
                                                                        \
    /* Number of Channel rules to install */                            \
    0,                                                                  \
                                                                        \
    /* Channel rules to install */                                      \
    NULL,                                                               \
                                                                        \
    /* Number of Secure Channel rules to install */                     \
    0,                                                                  \
                                                                        \
    /* Secure Channel rules to install */                               \
    NULL,                                                               \
                                                                        \
    /* Number of vPort statistics entries */                            \
    1,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    &vPortStat_EgressUntaggedPacket,                                    \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}

/* Egress MTU check drop Packet Test Case */
#define TEST_MACSEC_REC_PKT_EGRESS_MTU_CHECK_DROP_PACKET                \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressDefaultBypass,                                     \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0133 Egress MTU Check Drop Packet Test Case",                    \
                                                                        \
    /* CfyE data */                                                     \
    NULL,                                                               \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_Egress_MTU_CheckDrop,                                    \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* Packet data */                                                   \
    &Packet_Egress_MTU_Check,                                           \
                                                                        \
    /* Number of Channel rules to install */                            \
    4,                                                                  \
                                                                        \
    /* Channel rules to install */                                      \
    ChannelRules_Egress_Default,                                        \
                                                                        \
    /* Number of Secure Channel rules to install */                     \
    1,                                                                  \
                                                                        \
    /* Secure Channel rules to install */                               \
    SCRules_Egress_MTU_Check_Drop,                                      \
                                                                        \
    /* Number of vPort statistics entries */                            \
    1,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    &vPortStat_EgressMTUCheck,                                          \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}


/* Egress MTU check pass Packet Test Case */
#define TEST_MACSEC_REC_PKT_EGRESS_MTU_CHECK_PASS_PACKET                \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressDefaultBypass,                                     \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0134 Egress MTU Check Pass Packet Test Case",                    \
                                                                        \
    /* CfyE data */                                                     \
    NULL,                                                               \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_Egress_MTU_CheckBypass,                                  \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* Packet data */                                                   \
    &Packet_Egress_MTU_Check,                                           \
                                                                        \
    /* Number of Channel rules to install */                            \
    4,                                                                  \
                                                                        \
    /* Channel rules to install */                                      \
    ChannelRules_Egress_Default,                                        \
                                                                        \
    /* Number of Secure Channel rules to install */                     \
    1,                                                                  \
                                                                        \
    /* Secure Channel rules to install */                               \
    SCRules_Egress_MTU_Check_Pass,                                      \
                                                                        \
    /* Number of vPort statistics entries */                            \
    1,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    &vPortStat_EgressMTUCheck,                                          \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}


/* Ingress BadTag Test Case */
#define TEST_MACSEC_REC_PKT_INGRESS_BADTAG                              \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressBasicTransform,                                   \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0135 Ingress BadTag Test Case",                                  \
                                                                        \
    /* CfyE data */                                                     \
    NULL,                                                               \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_Ingress_BadTag,                                          \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* Packet data*/                                                    \
    &Packet_Ingress_BadTag,                                             \
                                                                        \
    /* Number of Channel rules to install */                            \
    4,                                                                  \
                                                                        \
    /* Channel rules to install */                                      \
    ChannelRules_Ingress_Default,                                       \
                                                                        \
    /* Number of Secure Channel rules to install */                     \
    0,                                                                  \
                                                                        \
    /* Secure Channel rules to install */                               \
    NULL,                                                               \
                                                                        \
    /* Number of vPort statistics entries */                            \
    1,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    &vPortStat_Ingress_BadTag,                                          \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}


/* Ingress KaY packet (!cbit && ebit) Test Case */
#define TEST_MACSEC_REC_PKT_INGRESS_KAY_PACKET                          \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressBasicTransform,                                   \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0136 Ingress KaY packet (!cbit && ebit) Test Case",              \
                                                                        \
    /* CfyE data */                                                     \
    NULL,                                                               \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_Ingress_KaY_Packet,                                      \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* Packet data*/                                                    \
    &Packet_Ingress_KaY_Packet,                                         \
                                                                        \
    /* Number of Channel rules to install */                            \
    4,                                                                  \
                                                                        \
    /* Channel rules to install */                                      \
    ChannelRules_Ingress_Default,                                       \
                                                                        \
    /* Number of Secure Channel rules to install */                     \
    0,                                                                  \
                                                                        \
    /* Secure Channel rules to install */                               \
    NULL,                                                               \
                                                                        \
    /* Number of vPort statistics entries */                            \
    1,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    &vPortStat_Ingress_KaY_Packet,                                      \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}


/* Basic MACsec Ingress packet, SCI not found */
#define TEST_MACSEC_REC_PKT_INGRESS_NOSCI                               \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressBasicTransform,                                   \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0137 Ingress SCI not found Test Case",                           \
                                                                        \
    /* CfyE data */                                                     \
    NULL,                                                               \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_Basic_Transform_WrongSCI_Ingress,                        \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* Packet data*/                                                    \
    &Packet_Ingress_NoSCI,                                              \
                                                                        \
    /* Number of Channel rules to install */                            \
    4,                                                                  \
                                                                        \
    /* Channel rules to install */                                      \
    ChannelRules_Ingress_Default,                                       \
                                                                        \
    /* Number of Secure Channel rules to install */                     \
    0,                                                                  \
                                                                        \
    /* Secure Channel rules to install */                               \
    NULL,                                                               \
                                                                        \
    /* Number of vPort statistics entries */                            \
    1,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    &vPortStat_Ingress_NoSCI,                                           \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}


#endif /* TEST_VECTOR_KAT_1_BASIC_TRANSFORM_H_ */


/* end of file test_vector_kat1_basic_transform.h */
