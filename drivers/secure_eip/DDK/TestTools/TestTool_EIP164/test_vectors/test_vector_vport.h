/* test_vector_vport.h
 *
 * Test Tool for CfyE and SecY API's
 * Test vector for the test case vport data
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

#ifndef TEST_VECTOR_VPORT_H_
#define TEST_VECTOR_VPORT_H_

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Driver Framework Basic Defs API */
#include "basic_defs.h"

/* Test Case KAT 1 record format */
#include "test_record.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */
extern Test_Case_vPortStat_t vPortStat_Static_Bypass_Egress;
extern Test_Case_vPortStat_t vPortStat_Static_Bypass_Ingress;
extern Test_Case_vPortStat_t vPortStat_SA_Drop_Egress;
extern Test_Case_vPortStat_t vPortStat_SA_Drop_Ingress;
extern Test_Case_vPortStat_t vPortStat_SA_Bypass_Egress;
extern Test_Case_vPortStat_t vPortStat_SA_Bypass_Ingress;
extern Test_Case_vPortStat_t vPortStat_Tag_Bypass_Egress;
extern Test_Case_vPortStat_t vPortStat_Tag_Bypass_Ingress;
extern Test_Case_vPortStat_t vPortStat_Basic_Transform_Egress;
extern Test_Case_vPortStat_t vPortStat_Basic_Transform_Ingress;
extern Test_Case_vPortStat_t vPortStat_Multi_SA_Transform_Ingress;
extern Test_Case_vPortStat_t vPortStat_Multi_SCI_AN_Transform;
extern Test_Case_vPortStat_t vPortStat_Multi_SA_Transform_Egress[];
extern Test_Case_vPortStat_t vPortStat_CryptAuthenticateEncode_ECB;
extern Test_Case_vPortStat_t vPortStat_CryptAuthenticateEncode_CTR;
extern Test_Case_vPortStat_t vPortStat_CryptAuthenticateEncode_GMAC;
extern Test_Case_vPortStat_t vPortStat_CryptAuthenticateEncode_GCM;
extern Test_Case_vPortStat_t vPortStat_CryptAuthenticateEncode_GCM2;
extern Test_Case_vPortStat_t vPortStat_CryptAuthenticateDecode_ECB;
extern Test_Case_vPortStat_t vPortStat_CryptAuthenticateDecode_CTR;
extern Test_Case_vPortStat_t vPortStat_CryptAuthenticateDecode_GMAC;
extern Test_Case_vPortStat_t vPortStat_CryptAuthenticateDecode_GCM;
extern Test_Case_vPortStat_t vPortStat_CryptAuthenticateDecode_GCM2;
extern Test_Case_vPortStat_t vPortStat_ExtPN_Egress;
extern Test_Case_vPortStat_t vPortStat_ExtPN_Ingress;
extern Test_Case_vPortStat_t vPortStat_Rekey_Egress;
extern Test_Case_vPortStat_t vPortStat_Rekey_EgressChained;
extern Test_Case_vPortStat_t vPortStat_Rekey_EgressNonChained;
extern Test_Case_vPortStat_t vPortStat_Rekey_Ingress;
extern Test_Case_vPortStat_t vPortStat_Rekey_Ingress_NoSCI;
extern Test_Case_vPortStat_t vPortStat_AllowEgressDataPackets[];
extern Test_Case_vPortStat_t vPortStat_EgressUntaggedPacket;
extern Test_Case_vPortStat_t vPortStat_EgressMTUCheck;
extern Test_Case_vPortStat_t vPortStat_AllowIngressUntaggedPackets[];
extern Test_Case_vPortStat_t vPortStat_Ingress_BadTag;
extern Test_Case_vPortStat_t vPortStat_Ingress_KaY_Packet;
extern Test_Case_vPortStat_t vPortStat_Ingress_NoSCI;
extern Test_Case_vPortStat_t vPortStat_EgressChannelReconfiguration[];
extern Test_Case_vPortStat_t vPortStat_IngressChannelReconfiguration[];
extern Test_Case_vPortStat_t vPortStat_Untagged_Egress_MACsec_bn;
extern Test_Case_vPortStat_t vPortStat_Untagged_Egress_NoEnc;
extern Test_Case_vPortStat_t vPortStat_Untagged_Ingress_MACsec_bn;
extern Test_Case_vPortStat_t vPortStat_Untagged_Ingress_NoEnc;
extern Test_Case_vPortStat_t vPortStat_VLAN_1Q_Egress_MACsec_O1;
extern Test_Case_vPortStat_t vPortStat_VLAN_1Q_Egress_MACsec_O2;
extern Test_Case_vPortStat_t vPortStat_VLAN_1Q_Ingress_MACsec_O1;
extern Test_Case_vPortStat_t vPortStat_VLAN_1Q_Ingress_MACsec_O2;
extern Test_Case_vPortStat_t vPortStat_VLAN_QinQ_Egress_MACsec_O3;
extern Test_Case_vPortStat_t vPortStat_VLAN_QinQ_Ingress_MACsec_O3;
extern Test_Case_vPortStat_t vPortStat_VLAN_QinQinQ_Egress_MACsec_O4;
extern Test_Case_vPortStat_t vPortStat_VLAN_QinQinQ_Ingress_MACsec_O4;
extern Test_Case_vPortStat_t vPortStat_CtrlPacket_PriEgress;
extern Test_Case_vPortStat_t vPortStat_CtrlPacket_PriIngress;
extern Test_Case_vPortStat_t vPortStat_VxLAN_IPv6_Egress_MACsec;
extern Test_Case_vPortStat_t vPortStat_VxLAN_IPv4_Egress_MACsec;
extern Test_Case_vPortStat_t vPortStat_VxLAN_IPv6_Ingress_MACsec;
extern Test_Case_vPortStat_t vPortStat_VxLAN_IPv4_Ingress_MACsec;
extern Test_Case_vPortStat_t vPortStat_CfyELimitsEgress;
extern Test_Case_vPortStat_t vPortStat_CfyELimitsIngress;
extern Test_Case_vPortStat_t vPortStat_CfyELimitsIPsecIngressMPLS;
#endif /* TEST_VECTOR_VPORT_H_ */

/* end of file test_vector_vport.h */
