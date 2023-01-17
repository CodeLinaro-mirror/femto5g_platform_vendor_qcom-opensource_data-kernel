/* test_vector_packet.h
 *
 * Test Tool for CfyE and SecY API's
 * Test vectors for the Packet data
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

#ifndef TEST_VECTOR_PACKET_H_
#define TEST_VECTOR_PACKET_H_

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Test Case KAT record format */
#include "test_record.h"

extern Test_Case_Packet_t Packet_Static_Bypass;

extern Test_Case_Packet_t Packet_Basic_Transform_Egress;
extern Test_Case_Packet_t Packet_Basic_Transform_Egress_NoEvents;
extern Test_Case_Packet_t Packet_Basic_Transform_Ingress;

extern Test_Case_Packet_t Packet_Expire_Egress;

extern Test_Case_Packet_t Packet_Basic_Transform_Egress_TagBypass;
extern Test_Case_Packet_t Packet_Basic_Transform_Ingress_TagBypass;

extern Test_Case_Packet_t Packet_SA_Bypass_Egress;
extern Test_Case_Packet_t Packet_SA_Bypass_Ingress;

extern Test_Case_Packet_t Packet_SA_Drop_Egress;
extern Test_Case_Packet_t Packet_SA_Drop_Ingress;

extern Test_Case_Packet_t Packet_Untagged_Egress;
extern Test_Case_Packet_t Packet_Egress_MTU_Check;

extern Test_Case_Packet_t Packet_Crypt_Authenticate_Decode_ECB;
extern Test_Case_Packet_t Packet_Crypt_Authenticate_Decode_CTR;
extern Test_Case_Packet_t Packet_Crypt_Authenticate_Decode_GMAC;
extern Test_Case_Packet_t Packet_Crypt_Authenticate_Decode_GCM;
extern Test_Case_Packet_t Packet_Crypt_Authenticate_Decode_GCM2;
extern Test_Case_Packet_t Packet_Crypt_Authenticate_Encode_ECB;
extern Test_Case_Packet_t Packet_Crypt_Authenticate_Encode_CTR;
extern Test_Case_Packet_t Packet_Crypt_Authenticate_Encode_GMAC;
extern Test_Case_Packet_t Packet_Crypt_Authenticate_Encode_GCM;
extern Test_Case_Packet_t Packet_Crypt_Authenticate_Encode_GCM2;

extern Test_Case_Packet_t Packet_Multi_SA_Transform_Egress[];
extern Test_Case_Packet_t Packet_Multi_SA_Transform_Ingress[];
extern Test_Case_Packet_t Packet_Multi_SCI_AN_Transform_Ingress[];

extern Test_Case_Packet_t Packet_Rekey_Egress[];
extern Test_Case_Packet_t Packet_Rekey_Egress_Chain[];

extern Test_Case_Packet_t Packet_Rekey_Ingress[];
extern Test_Case_Packet_t Packet_Rekey_Ingress_NoSCI[];

extern Test_Case_Packet_t Packet_ExtPN_Egress;
extern Test_Case_Packet_t Packet_ExtPN_Ingress;

extern Test_Case_Packet_t Packet_AllowEgressDataPackets[];

extern Test_Case_Packet_t Packet_AllowIngressUntaggedPackets[];

extern Test_Case_Packet_t Packet_ChannelReconfigure_Egress[];
extern Test_Case_Packet_t Packet_ChannelReconfigure_Ingress[];

extern Test_Case_Packet_t Packet_Ingress_BadTag;
extern Test_Case_Packet_t Packet_Ingress_KaY_Packet;
extern Test_Case_Packet_t Packet_Ingress_NoSCI;

extern Test_Case_Packet_t Packet_Untagged_Egress_NoEnc;
extern Test_Case_Packet_t Packet_Untagged_Egress_MACsec_bn;
extern Test_Case_Packet_t Packet_Untagged_Ingress_NoEnc;
extern Test_Case_Packet_t Packet_Untagged_Ingress_MACsec_bn;
extern Test_Case_Packet_t Packet_VLAN_1Q_Egress_MACsec_O1;
extern Test_Case_Packet_t Packet_VLAN_1Q_Egress_MACsec_O2;
extern Test_Case_Packet_t Packet_VLAN_1Q_Ingress_MACsec_O1;
extern Test_Case_Packet_t Packet_VLAN_1Q_Ingress_MACsec_O2;
extern Test_Case_Packet_t Packet_VLAN_QinQ_Egress_MACsec_O3;
extern Test_Case_Packet_t Packet_VLAN_QinQ_Ingress_MACsec_O3;
extern Test_Case_Packet_t Packet_VLAN_QinQinQ_Egress_MACsec_O4;
extern Test_Case_Packet_t Packet_VLAN_QinQinQ_Ingress_MACsec_O4;

extern Test_Case_Packet_t Packet_CtrlPacket_PriEgress[];
extern Test_Case_Packet_t Packet_CtrlPacket_PriIngress[];

#if defined(TEST_MACSEC_VXLAN_ENABLE)
extern Test_Case_Packet_t Packet_VxLAN_IPv6_Egress_MACsec;
extern Test_Case_Packet_t Packet_VxLAN_IPv4_Egress_MACsec;
extern Test_Case_Packet_t Packet_VxLAN_IPv6_Ingress_MACsec;
extern Test_Case_Packet_t Packet_VxLAN_IPv4_Ingress_MACsec;
#endif

extern Test_Case_Packet_t Packet_CfyELimitsEgress;
extern Test_Case_Packet_t Packet_CfyELimitsIngress;

#if defined(TEST_IPSEC_ENABLE)
extern Test_Case_Packet_t Packet_EgressIPsec_O1;
extern Test_Case_Packet_t Packet_EgressIPsec_UDP;
extern Test_Case_Packet_t Packet_EgressIPsecMPLS;
extern Test_Case_Packet_t Packet_EgressIPsecVLAN;
extern Test_Case_Packet_t Packet_EgressIPsec_SATag_Bypass;
extern Test_Case_Packet_t Packet_IngressIPsec_O1;
extern Test_Case_Packet_t Packet_IngressIPsec_UDP;
extern Test_Case_Packet_t Packet_IngressIPsec_VLAN;
extern Test_Case_Packet_t Packet_IngressIPsec_MPLS;
extern Test_Case_Packet_t Packet_IngressIPsec_MPLS_Bypass;
extern Test_Case_Packet_t Packet_IngressIPsec_LateCheck;
extern Test_Case_Packet_t Packet_MultiChannel_IPsec_MACsec_Egress[];
extern Test_Case_Packet_t Packet_MultiChannel_IPsec_MACsec_Ingress[];
extern Test_Case_Packet_t Packet_Multi_SA_Transform_IPsec_Egress[];
extern Test_Case_Packet_t Packet_Multi_SA_Transform_IPsec_Ingress[];
extern Test_Case_Packet_t Packet_Multi_SA_Transform_IPsec_Egress_Test[];
extern Test_Case_Packet_t Packet_ReplayFail_IPsec_Ingress[];
#endif
#endif /* TEST_VECTOR_PACKET_H_ */


/* end of file test_vector_packet.h */
