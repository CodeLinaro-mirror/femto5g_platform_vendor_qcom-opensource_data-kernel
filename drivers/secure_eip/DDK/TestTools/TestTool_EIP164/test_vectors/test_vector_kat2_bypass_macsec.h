/* test_vector_kat2_bypass_macsec.h
 *
 * Test Tool for CfyE and SecY API's
 * Test vector for a use case where a bypass SA is replaced with a MACsec SA.
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

#ifndef TEST_VECTOR_KAT_2_BYPASS_MACSEC_H_
#define TEST_VECTOR_KAT_2_BYPASS_MACSEC_H_

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

/* Test Case KAT 2 record format * */
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
#define  TEST_MACSEC_REC_EGRESS_BYPASS_MACSEC                           \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressDefaultBypass,                                     \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0204 Replace bypass SA with egress MACsec",                      \
                                                                        \
    /* CfyE data */                                                     \
    NULL,                                                               \
                                                                        \
    /* Number of transforms */                                          \
    2,                                                                  \
                                                                        \
    /* Transform data */                                                \
    Transform_Egress_Bypass_MACsec,                                     \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* Packet data */                                                   \
    &Packet_Basic_Transform_Egress_NoEvents,                             \
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
    TEST_MACSEC_OP_BYPASS_SA_MACSEC,                                    \
}

#define  TEST_MACSEC_REC_INGRESS_BYPASS_MACSEC                          \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressDefaultBypass,                                    \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0205 Replace bypass SA with ingress MACsec",                     \
                                                                        \
    /* CfyE data */                                                     \
    NULL,                                                               \
                                                                        \
    /* Number of transforms */                                          \
    2,                                                                  \
                                                                        \
    /* Transform data */                                                \
    Transform_Ingress_Bypass_MACsec,                                    \
                                                                        \
    /* Number of packets to process */                                  \
    1,                                                                  \
                                                                        \
    /* Packet data */                                                   \
    &Packet_Basic_Transform_Ingress,                                    \
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
    TEST_MACSEC_OP_BYPASS_SA_MACSEC,                                    \
}


#endif /* TEST_VECTOR_KAT_2_BYPASS_MACSEC_H_ */


/* end of file test_vector_kat2_bypass_macsec.h */
