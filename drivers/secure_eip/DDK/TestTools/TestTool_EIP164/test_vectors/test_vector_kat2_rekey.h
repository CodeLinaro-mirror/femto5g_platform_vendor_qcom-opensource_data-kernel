/* test_vector_kat2_rekey.h
 *
 * Test Tool for CfyE and SecY API's
 * Test vector for the re-key test case
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

#ifndef TEST_VECTOR_KAT_2_REKEY_H_
#define TEST_VECTOR_KAT_2_REKEY_H_

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

/* Test Case KAT 2 record format */
#include "test_record_kat2.h"

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
/* Rekey Egress Test Case */
#define TEST_MACSEC_REC_PKT_REKEY_EGRESS                                \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressDefaultBypass,                                     \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0200 Rekey Egress (Non-Chained) Test Case",                      \
                                                                        \
    /* CfyE data */                                                     \
    NULL,                                                               \
                                                                        \
    /* Number of transforms */                                          \
    2,                                                                  \
                                                                        \
    /* Transform data */                                                \
    Transform_Rekey_Egress,                                             \
                                                                        \
    /* Number of packets to process */                                  \
    2,                                                                  \
                                                                        \
    /* Packet data */                                                   \
    Packet_Rekey_Egress,                                                \
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
    &vPortStat_Rekey_Egress,                                            \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_REKEY,                                               \
}

/* Rekey Ingress Test Case */
#define TEST_MACSEC_REC_PKT_REKEY_INGRESS                               \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressDefaultBypass,                                    \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0210 Rekey Ingress Test Case",                                   \
                                                                        \
    /* CfyE data */                                                     \
    NULL,                                                               \
                                                                        \
    /* Number of transforms */                                          \
    2,                                                                  \
                                                                        \
    /* Transform data */                                                \
    Transform_Rekey_Ingress,                                            \
                                                                        \
    /* Number of packets to process */                                  \
    2,                                                                  \
                                                                        \
    /* Packet data*/                                                    \
    Packet_Rekey_Ingress,                                               \
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
    &vPortStat_Rekey_Ingress,                                           \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_REKEY,                                               \
}

#define TEST_MACSEC_REC_PKT_REKEY_INGRESS_NOSCI                         \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressDefaultBypass,                                    \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0211 Rekey Ingress Test Case (non-strict/end-station)",          \
                                                                        \
    /* CfyE data */                                                     \
    NULL,                                                               \
                                                                        \
    /* Number of transforms */                                          \
    2,                                                                  \
                                                                        \
    /* Transform data */                                                \
    Transform_Rekey_Ingress_NoSCI,                                      \
                                                                        \
    /* Number of packets to process */                                  \
    2,                                                                  \
                                                                        \
    /* Packet data*/                                                    \
    Packet_Rekey_Ingress_NoSCI,                                         \
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
    &vPortStat_Rekey_Ingress_NoSCI,                                     \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_REKEY,                                               \
}

#endif /* TEST_VECTOR_KAT_2_REKEY_H_ */


/* end of file test_vector_kat2_rekey.h */
