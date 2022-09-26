/* test_vector_kat3_basic_transform.h
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

#ifndef TEST_VECTOR_KAT_3_BASIC_TRANSFORM_H_
#define TEST_VECTOR_KAT_3_BASIC_TRANSFORM_H_

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

/* Basic MACsec Egress Test for Max number of SA test Case */
#define TEST_MACSEC_REC_PKT_BASIC_TRANSFORM_EGRESS_MAX_SA               \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressDefaultDropCRC,                                    \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0300 Max number of SA supported Egress Test Case",               \
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

/* Basic MACsec Ingress Test for Max number of SA test Case */
#define TEST_MACSEC_REC_PKT_BASIC_TRANSFORM_INGRESS_MAX_SA              \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressDefaultDropCRC,                                   \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0301 Max number of SA supported Ingress Test Case",              \
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


/* Basic MACsec Egress Test for Max number of SA test Case */
#define TEST_MACSEC_REC_PKT_BASIC_TRANSFORM_EGRESS_REDUCED_SA           \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressReducedDropCRC,                                    \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0302 Reduced number of SA supported Egress Test Case",           \
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

/* Basic MACsec Ingress Test for Max number of SA test Case */
#define TEST_MACSEC_REC_PKT_BASIC_TRANSFORM_INGRESS_REDUCED_SA          \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressReducedDropCRC,                                   \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0303 Reduced number of SA supported Ingress Test Case",          \
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


#endif /* TEST_VECTOR_KAT_3_BASIC_TRANSFORM_H_ */


/* end of file test_vector_kat3_basic_transform.h */
