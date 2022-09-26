/* test_vector_kat1_extpn.h
 *
 * Test Tool for CfyE and SecY API's
 * Test vector for the extended packet number test case.
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

#ifndef TEST_VECTOR_KAT_1_EXTPN_H_
#define TEST_VECTOR_KAT_1_EXTPN_H_

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
/* MACsec Egress Test Case with Extended Packet Numbers. */
#define TEST_MACSEC_REC_PKT_EXTPN_EGRESS                                \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressExtPN,                                             \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0120 Egress Transform with Extended PN Test Case",               \
                                                                        \
    /* CfyE data */                                                     \
    NULL,                                                               \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_ExtPN_Egress,                                            \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* Packet data */                                                   \
    &Packet_ExtPN_Egress,                                               \
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
    &vPortStat_ExtPN_Egress,                                            \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}

/* MACsec Ingress Test Case with Extended Packet Numbers */
#define TEST_MACSEC_REC_PKT_EXTPN_INGRESS                               \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressBasicTransform,                                   \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0121 Ingress Transform with Extended PN Test Case",              \
                                                                        \
    /* CfyE data */                                                     \
    NULL,                                                               \
                                                                        \
    /* Number of transforms */                                          \
    1,                                                                  \
                                                                        \
    /* Transform data */                                                \
    &Transform_ExtPN_Ingress,                                           \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* Packet data*/                                                    \
    &Packet_ExtPN_Ingress,                                              \
                                                                        \
    /* Number of Channel rules to install */                            \
    4,                                                                  \
                                                                        \
    /* Channel rules to install */                                      \
    ChannelRules_Ingress_ExtPN,                                         \
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
    &vPortStat_ExtPN_Ingress,                                           \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_NONE,                                                \
}

#endif /* TEST_VECTOR_KAT_1_EXTPN_H_ */


/* end of file test_vector_kat1_extpn.h */
