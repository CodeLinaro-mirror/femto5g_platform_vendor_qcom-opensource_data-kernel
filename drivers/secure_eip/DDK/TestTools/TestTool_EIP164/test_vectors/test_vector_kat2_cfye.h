/* test_vector_kat2_cfye.h
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

#ifndef TEST_VECTOR_KAT_2_CFYE_H_
#define TEST_VECTOR_KAT_2_CFYE_H_

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


#define TEST_MACSEC_REC_PKT_EGRESS_REUSE_SA_VPORT                       \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressDefaultDropInternal,                               \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1200 Egress Reuse SA/vPort Test Case",                           \
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
    0,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    NULL,                                                               \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_REUSE_SA_VPORT,                                      \
}

#define TEST_MACSEC_REC_PKT_INGRESS_REUSE_SA_VPORT                      \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressDefaultDropInternal,                              \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC1201 Ingress Reuse SA/vPort Test Case",                          \
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
    0,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    NULL,                                                               \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_REUSE_SA_VPORT,                                      \
}


#endif /* TEST_VECTOR_KAT_2_CFYE_H_ */


/* end of file test_vector_kat2_cfye.h */
