/* test_vector_kat5.h
 *
 * Test Tool for Driver164 Init API, CfyE and SecY API's
 * Test vectors for the KAT5 test
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

#ifndef TEST_VECTOR_KAT_5_H_
#define TEST_VECTOR_KAT_5_H_

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Default configuration */
#include "c_test_macsec.h"

/* KAT5 Test Record Format */
#include "test_record_kat5.h"

/* Test Case KAT 5 test vectors */
#include "test_vector_conf.h"
#include "test_vector_transform.h"
#include "test_vector_packet.h"
#include "test_vector_vport.h"

#ifdef TEST_MACSEC_USE_CFYE
#include "test_vector_cfye.h"
#include "test_vector_rule.h"
#endif


/*----------------------------------------------------------------------------
 * External variables
 *
 */

extern Test_Device_t Test_Devices_KAT5[];
extern Test_DataPath_t Test_DataPaths_KAT5[];

/*----------------------------------------------------------------------------
 * Definitions and macros
 */

#ifdef TEST_MACSEC_MODE_EGRESS
/* Basic MACsec Egress Test Case */
#define TEST_MACSEC_REC_KAT5_PKT_BASIC_TRANSFORM_EGRESS                 \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressBasicTransformKAT5,                                \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0500 Basic Transform Egress Device Add/Remove  Test Case",       \
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
    &vPortStat_Basic_Transform_Egress,                                  \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}

#ifdef TEST_MACSEC_USE_CFYE
/* Basic MACsec Egress Test Case */
#define TEST_MACSEC_REC_KAT5_CFYE_UNTAGGED_EGRESS_MACSEC_BN             \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressDefaultDropInternalKAT5,                           \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1500 Untagged Egress MACsec Device Add/Remove Test Case",        \
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
#endif /* TEST_MACSEC_USE_CFYE */
#endif /* TEST_MACSEC_MODE_EGRESS */

#ifdef TEST_MACSEC_MODE_INGRESS
/* Basic MACsec Ingress Test Case */
#define TEST_MACSEC_REC_KAT5_PKT_BASIC_TRANSFORM_INGRESS                \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressBasicTransformKAT5,                               \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0501 Basic Transform Ingress Device Add/Remove Test Case",       \
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

#ifdef TEST_MACSEC_USE_CFYE
#define TEST_MACSEC_REC_KAT5_CFYE_UNTAGGED_INGRESS_MACSEC_BN            \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressDefaultDropInternalKAT5,                          \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1501 Untagged Ingress MACsec Device Add/Remove Test Case",       \
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
#endif /* TEST_MACSEC_USE_CFYE */
#endif /* TEST_MACSEC_MODE_INGRESS */

Test_Case_Record_KAT5_t TCV_KAT_5[] =
{
#ifdef TEST_MACSEC_MODE_EGRESS
    {
        0,
        Test_Devices_KAT5,
        0,
        NULL,
        TEST_MACSEC_REC_KAT5_PKT_BASIC_TRANSFORM_EGRESS
    },

#ifdef TEST_MACSEC_USE_CFYE
    {
        0,
        NULL,
        0,
        Test_DataPaths_KAT5,
        TEST_MACSEC_REC_KAT5_CFYE_UNTAGGED_EGRESS_MACSEC_BN
    },
#endif /* TEST_MACSEC_USE_CFYE */

#endif /* TEST_MACSEC_MODE_EGRESS */

#ifdef TEST_MACSEC_MODE_INGRESS
    {
        0,
        Test_Devices_KAT5,
        0,
        NULL,
        TEST_MACSEC_REC_KAT5_PKT_BASIC_TRANSFORM_INGRESS
    },

#ifdef TEST_MACSEC_USE_CFYE
    {
        0,
        NULL,
        0,
        Test_DataPaths_KAT5,
        TEST_MACSEC_REC_KAT5_CFYE_UNTAGGED_INGRESS_MACSEC_BN
    },
#endif /* TEST_MACSEC_USE_CFYE */

#endif /* TEST_MACSEC_MODE_INGRESS */
};


#endif /* TEST_VECTOR_KAT_5_H_ */


/* end of file test_vector_kat5.h */
