/* test_vector_kat1_multi_sa_transform.h
 *
 * Test Tool for CfyE and SecY API's
 * Test vector for the multiple SA transform test case
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

#ifndef TEST_VECTOR_KAT_1_MULTI_SA_TRANSFORM_H_
#define TEST_VECTOR_KAT_1_MULTI_SA_TRANSFORM_H_

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
/* Multiple SA MACsec Egress Test Case */
#define TEST_MACSEC_REC_PKT_MULTI_SA_TRANSFORM_EGRESS                   \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressMultiTransform,                                    \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0110 Multiple SA Transform Egress Test Case",                    \
                                                                        \
    /* CfyE data */                                                     \
    NULL,                                                               \
                                                                        \
    /* Number of transforms */                                          \
    3,                                                                  \
                                                                        \
    /* Transform data */                                                \
    Transform_Multi_SA_Transform_Egress,                                \
                                                                        \
    /* Number of packets to process */                                  \
    3,                                                                  \
                                                                        \
    /* Packet data */                                                   \
    Packet_Multi_SA_Transform_Egress,                                   \
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
    3,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    vPortStat_Multi_SA_Transform_Egress,                                \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}

/* Multiplw SA MACsec Ingress Test Case */
#define TEST_MACSEC_REC_PKT_MULTI_SA_TRANSFORM_INGRESS                  \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressMultiTransform,                                   \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0111 Multiple SA Transform Ingress Test Case",                   \
                                                                        \
    /* CfyE data */                                                     \
    NULL,                                                               \
                                                                        \
    /* Number of transforms */                                          \
    3,                                                                  \
                                                                        \
    /* Transform data */                                                \
    Transform_Multi_SA_Transform_Ingress,                               \
                                                                        \
    /* Number of packets to process */                                  \
    3,                                                                  \
                                                                        \
    /* Packet data*/                                                    \
    Packet_Multi_SA_Transform_Ingress,                                  \
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
    &vPortStat_Multi_SA_Transform_Ingress,                              \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}

/* Multiple Ingress SCIs and ANs (Multiple SAs) on a single flow Test Case */
#define TEST_MACSEC_REC_PKT_MULTI_SCI_AN_INGRESS                        \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressMultiTransform,                                   \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0112 Multiple Ingress SCIs and ANs on single flow Test Case",    \
                                                                        \
    /* CfyE data */                                                     \
    NULL,                                                               \
                                                                        \
    /* Number of transforms */                                          \
    5,                                                                  \
                                                                        \
    /* Transform data */                                                \
    Transform_Multi_SCI_AN_Transform_Ingress,                           \
                                                                        \
    /* Number of packets to process */                                  \
    5,                                                                  \
                                                                        \
    /* Packet data*/                                                    \
    Packet_Multi_SCI_AN_Transform_Ingress,                              \
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
    &vPortStat_Multi_SCI_AN_Transform,                                  \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}
#endif /* TEST_VECTOR_KAT_1_MULTI_SA_TRANSFORM_H_ */


/* end of file test_vector_kat1_multi_sa_transform.h */
