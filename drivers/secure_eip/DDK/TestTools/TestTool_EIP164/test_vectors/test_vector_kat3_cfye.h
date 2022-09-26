/* test_vector_kat3_cfye.h
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

#ifndef TEST_VECTOR_KAT_3_CFYE_H_
#define TEST_VECTOR_KAT_3_CFYE_H_

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

/* Test Case KAT 3 record format */
#include "test_record_kat3.h"

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

#define TEST_MACSEC_REC_CFYE_LIMITS_EGRESS                              \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressDefaultDropInternal,                               \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1300 Max number of SA/vPorts/Rules supported Egress Test Case",  \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_LimitsEgress,                                            \
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
    &Packet_CfyELimitsEgress,                                           \
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
    &vPortStat_CfyELimitsEgress,                                        \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}

#define TEST_MACSEC_REC_CFYE_LIMITS_INGRESS                             \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressDefaultDropInternal,                              \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1301 Max number of SA/vPorts/Rules supported Ingress Test Case", \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_LimitsIngress,                                           \
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
    &Packet_CfyELimitsIngress,                                          \
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
    &vPortStat_CfyELimitsIngress,                                       \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}


#define TEST_MACSEC_REC_CFYE_REDUCED_LIMITS_EGRESS                      \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressReducedDropInternal,                               \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1302 Reduced number of SA/vPorts/Rules supported Egress Test Case",  \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_LimitsEgress,                                            \
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
    &Packet_CfyELimitsEgress,                                           \
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
    &vPortStat_CfyELimitsEgress,                                        \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}

#define TEST_MACSEC_REC_CFYE_REDUCED_LIMITS_INGRESS                     \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressReducedDropInternal,                              \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1303 Reduced number of SA/vPorts/Rules supported Ingress Test Case", \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_LimitsIngress,                                           \
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
    &Packet_CfyELimitsIngress,                                          \
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
    &vPortStat_CfyELimitsIngress,                                       \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}


#define TEST_MACSEC_REC_CFYE_REDUCED_LIMITS_INDEX_EGRESS                \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressReducedDropInternalIndex,                          \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1304 Reduced number of SA/vPorts/Rules supported Egress Test Case",  \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_LimitsEgress,                                            \
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
    &Packet_CfyELimitsEgress,                                           \
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
    &vPortStat_CfyELimitsEgress,                                        \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}

#define TEST_MACSEC_REC_CFYE_REDUCED_LIMITS_INDEX_INGRESS                     \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressReducedDropInternalIndex,                              \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1305 Reduced number of SA/vPorts/Rules supported Ingress Test Case", \
                                                                        \
    /* CfyE data */                                                     \
    &CfyE_Data_LimitsIngress,                                           \
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
    &Packet_CfyELimitsIngress,                                          \
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
    &vPortStat_CfyELimitsIngress,                                       \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}


#endif /* TEST_VECTOR_KAT_3_CFYE_H_ */


/* end of file test_vector_kat3_cfye.h */
