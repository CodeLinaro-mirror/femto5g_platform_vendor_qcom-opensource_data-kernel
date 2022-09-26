/* test_vector_kat1.h
 *
 * Test Tool for CfyE and SecY API's
 * Test vectors for the KAT1 test
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

#ifndef TEST_VECTOR_KAT_1_H_
#define TEST_VECTOR_KAT_1_H_

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Test Case KAT 1 test vectors */
#include "test_vector_kat1_no_transform.h"
#include "test_vector_kat1_basic_transform.h"
#include "test_vector_kat1_sa_bypass.h"
#include "test_vector_kat1_sa_drop.h"
#include "test_vector_kat1_multi_sa_transform.h"
#include "test_vector_kat1_crypt_authenticate.h"
#include "test_vector_kat1_tag_bypass.h"
#include "test_vector_kat1_extpn.h"
#include "test_vector_kat1_cfye.h"

/*----------------------------------------------------------------------------
 * Local variables
 */

static Test_Case_Record_t TCV_KAT_1[] =
{
#ifdef TEST_MACSEC_MODE_EGRESS
#ifdef TEST_MACSEC_INCLUDE_REDUNDANT_TESTS
    TEST_MACSEC_REC_PKT_STATIC_BYPASS_EGRESS,
#endif /* TEST_MACSEC_INCLUDE_REDUNDANT_TESTS */
    TEST_MACSEC_REC_PKT_BASIC_TRANSFORM_EGRESS,
    TEST_MACSEC_REC_PKT_SA_BYPASS_EGRESS,
    TEST_MACSEC_REC_PKT_SA_DROP_EGRESS,
    TEST_MACSEC_REC_PKT_MULTI_SA_TRANSFORM_EGRESS,
    TEST_MACSEC_REC_PKT_EXTPN_EGRESS,
    TEST_MACSEC_REC_PKT_EXPIRE_EGRESS,
    TEST_MACSEC_REC_PKT_ALLOW_EGRESS_DATA_PACKETS,
    TEST_MACSEC_REC_PKT_EGRESS_UNTAGGED_PACKET,
    TEST_MACSEC_REC_PKT_EGRESS_MTU_CHECK_DROP_PACKET,
    TEST_MACSEC_REC_PKT_EGRESS_MTU_CHECK_PASS_PACKET,
#ifdef TEST_MACSEC_SECY_CRYPT_AUTH_ENABLE
    TEST_MACSEC_REC_PKT_CRYPT_AUTHENTICATE_ENCODE_ECB,
    TEST_MACSEC_REC_PKT_CRYPT_AUTHENTICATE_ENCODE_CTR,
    TEST_MACSEC_REC_PKT_CRYPT_AUTHENTICATE_ENCODE_GMAC,
    TEST_MACSEC_REC_PKT_CRYPT_AUTHENTICATE_ENCODE_GCM,
    TEST_MACSEC_REC_PKT_CRYPT_AUTHENTICATE_ENCODE_GCM2,
#endif /* TEST_MACSEC_SECY_CRYPT_AUTH_ENABLE */

#ifdef TEST_MACSEC_USE_CFYE
    TEST_MACSEC_REC_CFYE_EGRESS_LOW_LATENCY_BYPASS,
    TEST_MACSEC_REC_CFYE_UNTAGGED_EGRESS_NOENC,
    TEST_MACSEC_REC_CFYE_UNTAGGED_EGRESS_MACSEC_BN,
    TEST_MACSEC_REC_CFYE_VLAN_1Q_EGRESS_MACSEC_O1,
    TEST_MACSEC_REC_CFYE_VLAN_1Q_EGRESS_MACSEC_O2,
    TEST_MACSEC_REC_CFYE_VLAN_QINQ_EGRESS_MACSEC_O3,
    TEST_MACSEC_REC_CFYE_VLAN_QINQINQ_EGRESS_MACSEC_O4,
    TEST_MACSEC_REC_CFYE_CTRLPKT_PRIDETECTOR_EGRESS,
#ifdef TEST_MACSEC_VXLAN_ENABLE
    TEST_MACSEC_REC_CFYE_VXLAN_IPV6_EGRESS,
    TEST_MACSEC_REC_CFYE_VXLAN_IPV4_EGRESS,
#endif
#ifdef TEST_IPSEC_ENABLE
    TEST_IPSEC_REC_CFYE_BASIC_EGRESS,
    TEST_IPSEC_REC_CFYE_VLAN_EGRESS,
    TEST_IPSEC_REC_CFYE_MPLS_EGRESS,
    TEST_IPSEC_REC_CFYE_SA_BYPASS_EGRESS,
    TEST_IPSEC_REC_CFYE_IPSEC_MACSEC_MULTI_CH_EGRESS,
    TEST_IPSEC_REC_CFYE_TRANSFORM_EGRESS,
    TEST_IPSEC_REC_CFYE_MULTI_SA_TRANSFORM_EGRESS,
    TEST_IPSEC_REC_CFYE_UDP_EGRESS,
#endif /* TEST_IPSEC_ENABLE */
#endif /* TEST_MACSEC_USE_CFYE */
#endif /* TEST_MACSEC_MODE_EGRESS */

#ifdef TEST_MACSEC_MODE_INGRESS
#ifdef TEST_MACSEC_INCLUDE_REDUNDANT_TESTS
    TEST_MACSEC_REC_PKT_STATIC_BYPASS_INGRESS,
#endif /* TEST_MACSEC_INCLUDE_REDUNDANT_TESTS */
    TEST_MACSEC_REC_PKT_BASIC_TRANSFORM_INGRESS,
    TEST_MACSEC_REC_PKT_SA_BYPASS_INGRESS,
    TEST_MACSEC_REC_PKT_SA_DROP_INGRESS,
    TEST_MACSEC_REC_PKT_MULTI_SA_TRANSFORM_INGRESS,
    TEST_MACSEC_REC_PKT_MULTI_SCI_AN_INGRESS,
    TEST_MACSEC_REC_PKT_EXTPN_INGRESS,
    TEST_MACSEC_REC_PKT_ALLOW_INGRESS_UNTAGGED_PACKETS,
    TEST_MACSEC_REC_PKT_INGRESS_BADTAG,
    TEST_MACSEC_REC_PKT_INGRESS_KAY_PACKET,
    TEST_MACSEC_REC_PKT_INGRESS_NOSCI,
#ifdef TEST_MACSEC_SECY_CRYPT_AUTH_ENABLE
    TEST_MACSEC_REC_PKT_CRYPT_AUTHENTICATE_DECODE_ECB,
    TEST_MACSEC_REC_PKT_CRYPT_AUTHENTICATE_DECODE_CTR,
    TEST_MACSEC_REC_PKT_CRYPT_AUTHENTICATE_DECODE_GMAC,
    TEST_MACSEC_REC_PKT_CRYPT_AUTHENTICATE_DECODE_GCM,
    TEST_MACSEC_REC_PKT_CRYPT_AUTHENTICATE_DECODE_GCM2,
#endif /* TEST_MACSEC_SECY_CRYPT_AUTH_ENABLE */

#ifdef TEST_MACSEC_USE_CFYE
    TEST_MACSEC_REC_CFYE_INGRESS_LOW_LATENCY_BYPASS,
    TEST_MACSEC_REC_CFYE_UNTAGGED_INGRESS_NOENC,
    TEST_MACSEC_REC_CFYE_UNTAGGED_INGRESS_MACSEC_BN,
    TEST_MACSEC_REC_CFYE_VLAN_1Q_INGRESS_MACSEC_O1,
    TEST_MACSEC_REC_CFYE_VLAN_1Q_INGRESS_MACSEC_O2,
    TEST_MACSEC_REC_CFYE_VLAN_QINQ_INGRESS_MACSEC_O3,
    TEST_MACSEC_REC_CFYE_VLAN_QINQINQ_INGRESS_MACSEC_O4,
    TEST_MACSEC_REC_CFYE_CTRLPKT_PRIDETECTOR_INGRESS,
#ifdef TEST_MACSEC_VXLAN_ENABLE
    TEST_MACSEC_REC_CFYE_VXLAN_IPV6_INGRESS,
    TEST_MACSEC_REC_CFYE_VXLAN_IPV4_INGRESS,
#endif
#ifdef TEST_IPSEC_ENABLE
    TEST_IPSEC_REC_CFYE_BASIC_INGRESS,
    TEST_IPSEC_REC_CFYE_VLAN_INGRESS,
    TEST_IPSEC_REC_CFYE_MPLS_INGRESS,
    TEST_IPSEC_REC_CFYE_MPLS_BYPASS_INGRESS,
    TEST_IPSEC_REC_CFYE_LATE_CHECK_INGRESS,
    TEST_IPSEC_REC_CFYE_IPSEC_MACSEC_MULTI_CH_INGRESS,
    TEST_IPSEC_REC_CFYE_MULTI_SA_TRANSFORM_INGRESS,
    TEST_IPSEC_REC_CFYE_REPLAY_FAIL_INGRESS,
    TEST_IPSEC_REC_CFYE_UDP_INGRESS,
#endif /* TEST_IPSEC_ENABLE */
#endif /* TEST_MACSEC_USE_CFYE */
#endif /* TEST_MACSEC_MODE_INGRESS */
};

#endif /* TEST_VECTOR_KAT_1_H_ */


/* end of file test_vector_kat1.h */
