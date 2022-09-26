/* test_vector_kat4_basic_transform.h
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

#ifndef TEST_VECTOR_KAT_4_BASIC_TRANSFORM_H_
#define TEST_VECTOR_KAT_4_BASIC_TRANSFORM_H_

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
#include "test_record_kat4.h"

#include "test_vector_conf.h"
#include "test_vector_packet.h"
#include "test_vector_transform.h"
#include "test_vector_vport.h"
#include "test_vector_rule.h"


/*----------------------------------------------------------------------------
 * Local variables
 */

/*----------------------------------------------------------------------------
 * Definitions and macros
 */

/* Basic MACsec Egress Test for the channel disable test Case */
#define TEST_MACSEC_REC_PKT_MULTIPLE_CHANNEL_EGRESS                     \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsEgressMultiTransform,                                    \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0400 Multi-Channel Egress Test Case",                            \
                                                                        \
    /* CfyE data */                                                     \
    NULL,                                                               \
                                                                        \
    /* Number of transforms */                                          \
    4,                                                                  \
                                                                        \
    /* Transform data */                                                \
    Transform_MultipleChannel_Egress,                                   \
                                                                        \
    /* Number of packets to process */                                  \
    11,                                                                 \
                                                                        \
    /* Packet data */                                                   \
    Packet_ChannelReconfigure_Egress,                                   \
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
    4,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    vPortStat_EgressChannelReconfiguration,                             \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_MULTI_CHANNEL,                                       \
}

/* Basic MACsec Ingress Test for the channel disable test Case */
#define TEST_MACSEC_REC_PKT_MULTIPLE_CHANNEL_INGRESS                    \
{                                                                       \
    /* Test case configuration data */                                  \
    &ConfParamsIngressMultiTransform,                                   \
                                                                        \
    /* Test case configuration data and test vectors record */          \
                                                                        \
    /* Zero-terminated test case name */                                \
    "TC0401 Multi-Channel Ingress Test Case",                           \
                                                                        \
    /* CfyE data */                                                     \
    NULL,                                                               \
                                                                        \
    /* Number of transforms */                                          \
    4,                                                                  \
                                                                        \
    /* Transform data */                                                \
    Transform_MultipleChannel_Ingress,                                  \
                                                                        \
    /* Number of packets to process */                                  \
    11,                                                                 \
                                                                        \
    /* Packet data*/                                                    \
    Packet_ChannelReconfigure_Ingress,                                  \
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
    4,                                                                  \
                                                                        \
    /* vPort statistics test */                                         \
    vPortStat_IngressChannelReconfiguration,                            \
                                                                        \
    /* Special operation */                                             \
    TEST_MACSEC_OP_MULTI_CHANNEL,                                       \
}


#endif /* TEST_VECTOR_KAT_4_BASIC_TRANSFORM_H_ */


/* end of file test_vector_kat4_basic_transform.h */
