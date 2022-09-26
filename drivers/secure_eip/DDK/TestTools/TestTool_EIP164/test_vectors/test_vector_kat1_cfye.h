/* test_vector_kat1_cfye.h
 *
 * Test Tool for CfyE API's
 * Test vector(s) for the CfyE related test cases
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

#ifndef TEST_VECTOR_KAT_1_CFYE_H_
#define TEST_VECTOR_KAT_1_CFYE_H_

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

/* Low-latency bypass Egress Test Case */
#define TEST_MACSEC_REC_CFYE_EGRESS_LOW_LATENCY_BYPASS                  \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressLowLatencyBypass,                                  \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1100 Low-latency Bypass Egress Test Case",                       \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_LowLatencyBypass,                                        \
                                                                        \
    /* Number of transforms */                                          \
    0,                                                                  \
                                                                        \
    /* Transform data */                                                \
    NULL,                                                               \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_Static_Bypass,                                              \
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
    &vPortStat_Static_Bypass_Egress,                                    \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}

/* Low-latency bypass Ingress Test Case */
#define TEST_MACSEC_REC_CFYE_INGRESS_LOW_LATENCY_BYPASS                 \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressLowLatencyBypass,                                 \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1101 Low-latency Bypass Ingress Test Case",                      \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_LowLatencyBypass,                                        \
                                                                        \
    /* Number of transforms */                                          \
    0,                                                                  \
                                                                        \
    /* Transform data */                                                \
    NULL,                                                               \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_Static_Bypass,                                              \
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
    &vPortStat_Static_Bypass_Ingress,                                   \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}

#define TEST_MACSEC_REC_CFYE_UNTAGGED_EGRESS_NOENC                      \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressDefaultDropInternal,                               \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1110 Untagged egress no encryption Test Case",                   \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_Untagged_Egress_NoEnc,                                   \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_SA_Bypass_Egress,                                        \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_Untagged_Egress_NoEnc,                                      \
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
    &vPortStat_Untagged_Egress_NoEnc,                                   \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}

#define TEST_MACSEC_REC_CFYE_UNTAGGED_EGRESS_MACSEC_BN                  \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressDefaultDropInternal,                               \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1111 Untagged egress MACsec Test Case",                          \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_Untagged_Egress_MACsec_bn,                               \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_Untagged_Egress_MACsec_bn,                               \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_Untagged_Egress_MACsec_bn,                                  \
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
    &vPortStat_Untagged_Egress_MACsec_bn,                               \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}

#define TEST_MACSEC_REC_CFYE_UNTAGGED_INGRESS_NOENC                     \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressDefaultDropInternal,                              \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1114 Untagged Ingress no encryption Test Case",                  \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_Untagged_Ingress_NoEnc,                                  \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_SA_Bypass_Ingress,                                       \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_Untagged_Ingress_NoEnc,                                     \
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
    &vPortStat_Untagged_Ingress_NoEnc,                                  \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}

#define TEST_MACSEC_REC_CFYE_UNTAGGED_INGRESS_MACSEC_BN                 \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressDefaultDropInternal,                              \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1115 Untagged ingress MACsec Test Case",                         \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_Untagged_Ingress_MACsec_bn,                              \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_Untagged_Ingress_MACsec_bn,                              \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_Untagged_Ingress_MACsec_bn,                                 \
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
    &vPortStat_Untagged_Ingress_MACsec_bn,                              \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}

#define TEST_MACSEC_REC_CFYE_VLAN_1Q_EGRESS_MACSEC_O1                   \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressDefaultDropInternal,                               \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1121 MACsec one VLAN tag (Option 1) Egress Test Case",           \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_VLAN_1Q_Egress_MACsec_O1,                                \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_VLAN_1Q_Egress_MACsec_O1,                                \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_VLAN_1Q_Egress_MACsec_O1,                                   \
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
    &vPortStat_VLAN_1Q_Egress_MACsec_O1,                                \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}

#define TEST_MACSEC_REC_CFYE_VLAN_1Q_EGRESS_MACSEC_O2                   \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressDefaultDropInternal,                               \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1122 MACsec one VLAN tag (Option 2) Egress Test Case",           \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_VLAN_1Q_Egress_MACsec_O2,                                \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_VLAN_1Q_Egress_MACsec_O2,                                \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_VLAN_1Q_Egress_MACsec_O2,                                   \
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
    &vPortStat_VLAN_1Q_Egress_MACsec_O2,                                \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}

#define TEST_MACSEC_REC_CFYE_VLAN_1Q_INGRESS_MACSEC_O1                  \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressDefaultDropInternal,                              \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1123 MACsec one VLAN tag (Option 1) Ingress Test Case",          \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_VLAN_1Q_Ingress_MACsec_O1,                               \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_VLAN_1Q_Ingress_MACsec_O1,                               \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_VLAN_1Q_Ingress_MACsec_O1,                                  \
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
    &vPortStat_VLAN_1Q_Ingress_MACsec_O1,                               \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}

#define TEST_MACSEC_REC_CFYE_VLAN_1Q_INGRESS_MACSEC_O2                  \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressDefaultDropInternal,                              \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1124 MACsec one VLAN tag (option 2) Ingress Test Case",          \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_VLAN_1Q_Ingress_MACsec_O2,                               \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_VLAN_1Q_Ingress_MACsec_O2,                               \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_VLAN_1Q_Ingress_MACsec_O2,                                  \
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
    &vPortStat_VLAN_1Q_Ingress_MACsec_O2,                               \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}

#define TEST_MACSEC_REC_CFYE_VLAN_QINQ_EGRESS_MACSEC_O3                 \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressDefaultDropInternal,                               \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1126 MACsec two VLAN tags (Option 3) Egress Test Case",          \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_VLAN_QinQ_Egress_MACsec_O3,                              \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_VLAN_QinQ_Egress_MACsec_O3,                              \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_VLAN_QinQ_Egress_MACsec_O3,                                 \
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
    &vPortStat_VLAN_QinQ_Egress_MACsec_O3,                              \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}

#define TEST_MACSEC_REC_CFYE_VLAN_QINQ_INGRESS_MACSEC_O3                \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressDefaultDropInternal,                              \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1127 MACsec two VLAN tags (Option 3) Ingress Test Case",         \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_VLAN_QinQ_Ingress_MACsec_O3,                             \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_VLAN_QinQ_Ingress_MACsec_O3,                             \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_VLAN_QinQ_Ingress_MACsec_O3,                                \
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
    &vPortStat_VLAN_QinQ_Ingress_MACsec_O3,                             \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}

#define TEST_MACSEC_REC_CFYE_VLAN_QINQINQ_EGRESS_MACSEC_O4              \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressDefaultDropInternal,                               \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1128 MACsec three VLAN tags (Option 4) Egress Test Case",        \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_VLAN_QinQinQ_Egress_MACsec_O4,                           \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_VLAN_QinQinQ_Egress_MACsec_O4,                           \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_VLAN_QinQinQ_Egress_MACsec_O4,                              \
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
    &vPortStat_VLAN_QinQinQ_Egress_MACsec_O4,                           \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}

#define TEST_MACSEC_REC_CFYE_VLAN_QINQINQ_INGRESS_MACSEC_O4             \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressDefaultDropInternal,                              \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1129 MACsec three VLAN tags (Option 4) Ingress Test Case",       \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_VLAN_QinQinQ_Ingress_MACsec_O4,                          \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_VLAN_QinQinQ_Ingress_MACsec_O4,                          \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_VLAN_QinQinQ_Ingress_MACsec_O4,                             \
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
    &vPortStat_VLAN_QinQinQ_Ingress_MACsec_O4,                          \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}

#define TEST_MACSEC_REC_CFYE_CTRLPKT_PRIDETECTOR_EGRESS                 \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressDefaultDropInternal,                               \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1170 Primary Control Packet Detection Egress Test Case",         \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_CtrlPacket_PriEgress,                                    \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_Untagged_Egress_MACsec_bn,                               \
                                                                        \
    /* Number of packets to process */                                  \
    8,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    Packet_CtrlPacket_PriEgress,                                        \
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
    &vPortStat_CtrlPacket_PriEgress,                                    \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}

#define TEST_MACSEC_REC_CFYE_CTRLPKT_PRIDETECTOR_INGRESS                \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressDefaultDropInternal,                              \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1171 Primary Control Packet Detection Ingress Test Case",        \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_CtrlPacket_PriIngress,                                   \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_Untagged_Ingress_MACsec_bn,                              \
                                                                        \
    /* Number of packets to process */                                  \
    8,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    Packet_CtrlPacket_PriIngress,                                       \
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
    &vPortStat_CtrlPacket_PriIngress,                                   \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}

#if defined(TEST_MACSEC_VXLAN_ENABLE)
#define TEST_MACSEC_REC_CFYE_VXLAN_IPV6_EGRESS                          \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressDefaultDropInternal,                               \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1174 MACsec VxLAN IPv6 outer VLAN tag Egress Test Case",         \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_VxLAN_IPv6_Egress_MACsec,                                \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_VxLAN_IPv6_Egress_MACsec,                                \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_VxLAN_IPv6_Egress_MACsec,                                   \
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
    &vPortStat_VxLAN_IPv6_Egress_MACsec,                                \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_VXLAN,                                               \
}

#define TEST_MACSEC_REC_CFYE_VXLAN_IPV4_EGRESS                          \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressDefaultDropInternal,                               \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1176 MACsec VxLAN IPv4 inner VLAN tag Egress Test Case",         \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_VxLAN_IPv4_Egress_MACsec,                                \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_VxLAN_IPv4_Egress_MACsec,                                \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_VxLAN_IPv4_Egress_MACsec,                                   \
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
    &vPortStat_VxLAN_IPv4_Egress_MACsec,                                \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_VXLAN,                                               \
}

#define TEST_MACSEC_REC_CFYE_VXLAN_IPV6_INGRESS                         \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressDefaultDropInternal,                              \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1175 MACsec VxLAN IPv6 outer VLAN tag Ingress Test Case",        \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_VxLAN_IPv6_Ingress_MACsec,                               \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_VxLAN_IPv6_Ingress_MACsec,                               \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_VxLAN_IPv6_Ingress_MACsec,                                   \
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
    &vPortStat_VxLAN_IPv6_Ingress_MACsec,                               \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_VXLAN,                                               \
}

#define TEST_MACSEC_REC_CFYE_VXLAN_IPV4_INGRESS                         \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressDefaultDropInternal,                              \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1177 MACsec VxLAN IPv4 inner VLAN tag Ingress Test Case",        \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_VxLAN_IPv4_Ingress_MACsec,                               \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_VxLAN_IPv4_Ingress_MACsec,                               \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_VxLAN_IPv4_Ingress_MACsec,                                  \
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
    &vPortStat_VxLAN_IPv4_Ingress_MACsec,                               \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_VXLAN,                                               \
}


#endif

#if defined(TEST_IPSEC_ENABLE)
#define TEST_IPSEC_REC_CFYE_BASIC_EGRESS                                \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIPsecEgressBasicTransform,                               \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1180 IPsec Basic Egress Test Case",                              \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_Egress_IPsec_O1,                                         \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_Egress_IPsec_O1,                                         \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_EgressIPsec_O1,                                             \
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
    0,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    NULL,                                                               \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_IPSEC,                                               \
}


#define TEST_IPSEC_REC_CFYE_BASIC_INGRESS                               \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIPsecIngressBasicTransform,                              \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1181 Untagged IPSEC Ingress Test Case",                          \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_Ingress_IPsec_O1,                                        \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_Ingress_IPsec_O1,                                        \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_IngressIPsec_O1,                                            \
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
    0,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    NULL,                                                               \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_IPSEC,                                               \
}


#define TEST_IPSEC_REC_CFYE_UDP_EGRESS                                  \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIPsecEgressBasicTransform,                               \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1196 IPsec UDP Egress Test Case",                                \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_Egress_IPsec_UDP,                                        \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_Egress_IPsec_UDP,                                        \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_EgressIPsec_UDP,                                            \
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
    0,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    NULL,                                                               \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_IPSEC,                                               \
}

#define TEST_IPSEC_REC_CFYE_UDP_INGRESS                                 \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIPsecIngressBasicTransform,                              \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1195 IPSEC UDP Ingress Test Case",                               \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_Ingress_IPsec_UDP,                                       \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_Ingress_IPsec_UDP,                                       \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_IngressIPsec_UDP,                                           \
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
    0,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    NULL,                                                               \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_IPSEC,                                               \
}

#define TEST_IPSEC_REC_CFYE_MPLS_EGRESS                                 \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIPsecEgressMPLS,                                         \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1182 IPsec Egress MPLS Test Case",                               \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_Egress_IPsecMPLS,                                        \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_Egress_IPsecMPLS,                                        \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_EgressIPsecMPLS,                                            \
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
    0,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    NULL,                                                               \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_IPSEC,                                               \
}

#define TEST_IPSEC_REC_CFYE_MPLS_INGRESS                                \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIPsecIngressBasicTransform,                              \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1183 IPSEC Ingress Test Case for 1 MPLS label",                  \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_IPsecIngressMPLS,                                        \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_Ingress_IPsec_MPLS,                                      \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_IngressIPsec_MPLS,                                          \
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
   /* vPort statistics test */                                          \
   &vPortStat_CfyELimitsIPsecIngressMPLS,                               \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_IPSEC,                                               \
}


#define TEST_IPSEC_REC_CFYE_VLAN_EGRESS                                 \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIPsecEgressVLAN,                                         \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1184 IPsec Egress VLAN Test Case",                               \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_Egress_IPsecVLAN,                                        \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_Egress_IPsecVLAN,                                        \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_EgressIPsecVLAN,                                            \
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
    0,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    NULL,                                                               \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_IPSEC,                                               \
}

#define TEST_IPSEC_REC_CFYE_VLAN_INGRESS                                \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIPsecIngressVLANTransform,                               \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1185 IPSEC Ingress Test Case for 1 VLAN tag",                    \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_IPsecIngressVLAN,                                        \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_Ingress_IPsec_VLAN,                                      \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_IngressIPsec_VLAN,                                          \
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
    0,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    NULL,                                                               \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_IPSEC,                                               \
}

#define TEST_IPSEC_REC_CFYE_SA_BYPASS_EGRESS                            \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIPsecEgressBasicTransform,                               \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1186 IPsec Egress SA Tag Bypass Test Case",                      \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_Egress_IPsec_O1,                                         \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_Egress_IPsec_SA_Tag_Bypass,                              \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_EgressIPsec_SATag_Bypass,                                   \
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
    0,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    NULL,                                                               \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_IPSEC,                                               \
}

#define TEST_IPSEC_REC_CFYE_MPLS_BYPASS_INGRESS                         \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIPsecIngressBasicTransform,                              \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1187 IPSEC Ingress Test Case for MPLS label Bypass",             \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_IPsecIngressMPLS_Bypass,                                 \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_Ingress_IPsec_MPLS_Bypass,                               \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_IngressIPsec_MPLS_Bypass,                                   \
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
    0,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    NULL,                                                               \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_IPSEC,                                               \
}

#define TEST_IPSEC_REC_CFYE_LATE_CHECK_INGRESS                          \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIPsecIngressBasicTransform,                              \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1188 IPSEC Ingress Test Case to test Late Check functionality",  \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_Ingress_IPsec_LateCheck,                                 \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_Ingress_IPsec_LateCheck,                                 \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    &Packet_IngressIPsec_LateCheck,                                     \
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
    0,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    NULL,                                                               \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_IPSEC,                                               \
}

#define TEST_IPSEC_REC_CFYE_IPSEC_MACSEC_MULTI_CH_EGRESS                \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIPsecEgressMultiTransform,                               \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1189 Egress Test case - IPsec and MACsec on different channels", \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_Egress_IPsec_MACsec,                                     \
                                                                        \
    /* Number of transforms */                                          \
    2,                                                                  \
                                                                        \
    /* Transform data */                                                \
    Transform_MultipleChannel_Ipsec_MACsec_Egress,                      \
                                                                        \
    /* Number of packets to process */                                  \
    2,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    Packet_MultiChannel_IPsec_MACsec_Egress,                            \
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
    0,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    NULL,                                                               \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_IPSEC,                                               \
}

#define TEST_IPSEC_REC_CFYE_IPSEC_MACSEC_MULTI_CH_INGRESS               \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIPsecIngressMultiTransform,                              \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1190 Ingress Test case - IPsec and MACsec on different channels",\
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_IPsec_MACsec_Ingress,                                    \
                                                                        \
    /* Number of transforms */                                          \
    2,                                                                  \
                                                                        \
    /* Transform data */                                                \
    Transform_MultiCh_Ipsec_MACsec_Ingress,                             \
                                                                        \
    /* Number of packets to process */                                  \
    2,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    Packet_MultiChannel_IPsec_MACsec_Ingress,                           \
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
    0,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    NULL,                                                               \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_IPSEC,                                               \
}

#define TEST_IPSEC_REC_CFYE_TRANSFORM_EGRESS                            \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIPsecEgressBasicTransform,                               \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1191 Multiple SA Transform Egress Test Case Test",               \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_MultiSA_IPsec_Egress_Test,                               \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    Transform_IPsec_Multi_SA_Transform_Egress_Test,                     \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* Packet data */                                                   \
    Packet_Multi_SA_Transform_IPsec_Egress_Test,                        \
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
    0,                                                                  \
                                                                        \
    /* vPort statistics test   */                                       \
    NULL,                                                               \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_IPSEC,                                               \
}


#define TEST_IPSEC_REC_CFYE_MULTI_SA_TRANSFORM_EGRESS                   \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIPsecEgressBasicTransform,                               \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1192 Multiple SA Transform Egress Test Case",                    \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_MultiSA_IPsec_Egress,                                    \
                                                                        \
    /* Number of transforms */                                          \
    2,                                                                  \
                                                                        \
    /* Transform data */                                                \
    Transform_IPsec_Multi_SA_Transform_Egress,                          \
                                                                        \
    /* Number of packets to process */                                  \
    2,                                                                  \
                                                                        \
    /* Packet data */                                                   \
    Packet_Multi_SA_Transform_IPsec_Egress,                             \
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
    0,                                                                  \
                                                                        \
    /* vPort statistics test   */                                       \
    NULL,                                                               \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_IPSEC,                                               \
}


#define TEST_IPSEC_REC_CFYE_MULTI_SA_TRANSFORM_INGRESS                  \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIPsecIngressBasicTransform,                              \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1193 Multiple SA Transform Ingress Test Case",                   \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_MultiSA_IPsec_Ingress,                                   \
                                                                        \
    /* Number of transforms */                                          \
    3,                                                                  \
                                                                        \
    /* Transform data */                                                \
    Transform_IPsec_Multi_SA_Transform_Ingress,                         \
                                                                        \
    /* Number of packets to process */                                  \
    3,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    Packet_Multi_SA_Transform_IPsec_Ingress,                            \
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
    0,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    NULL,                                                               \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_IPSEC,                                                \
}

#define TEST_IPSEC_REC_CFYE_REPLAY_FAIL_INGRESS                         \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIPsecIngressBasicTransform,                              \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1194 Ingress Replay F a i l feature Test Case",                  \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_ReplayFail_IPsec_Ingress,                                \
                                                                        \
    /* Number of transforms */                                          \
    2,                                                                  \
                                                                        \
    /* Transform data */                                                \
    Transform_IPsec_ReplayFail_Transform_Ingress,                       \
                                                                        \
    /* Number of packets to process */                                  \
    4,                                                                  \
                                                                        \
    /* No packet data provided, test tool will generate a packet*/      \
    Packet_ReplayFail_IPsec_Ingress,                                    \
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
    0,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    NULL,                                                               \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_IPSEC,                                                \
}
#endif /* TEST_IPSEC_ENABLE */
#endif /* TEST_VECTOR_KAT_1_CFYE_H_ */


/* end of file test_vector_kat1_cfye.h */
