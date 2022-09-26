/* test_vector_transform.h
 *
 * Test Tool for CfyE and SecY API's
 * Test vector for the test case transform data
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

#ifndef TEST_VECTOR_TRANSFORM_H_
#define TEST_VECTOR_TRANSFORM_H_

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

#define SA_Param_Egress_Common(fSAInUse, ConfOffset,                           \
                               fProtectFrames, fUseES, fUseSCB, fConfProtect,  \
                               fAllowDataPackets, PreSecTAGStart, PreSecTAGLen)\
  {                                                                           \
    /* Size of the transform record (TransformRecord_p), in 32-bit words */   \
    0, /* To be filled in later*/                                             \
                                                                              \
    /* Transform record block */                                              \
    NULL, /* To be filled in later*/                                          \
                                                                              \
   {                                                                          \
     .Egress =                                                                \
     {                                                                        \
        /* fSAInUse, true - SA is in use */                                   \
        fSAInUse,                                                             \
                                                                              \
        /* ConfidentialityOffset - Confidentiality offset */                  \
        ConfOffset,                                                           \
                                                                              \
        /* fProtectFrames - Protect frames */                                 \
        fProtectFrames,                                                       \
                                                                              \
        /* fIncludeSCI - Include SCI */                                       \
        !fUseES,                                                              \
                                                                              \
        /* fUseES - Use ES */                                                 \
        fUseES,                                                               \
                                                                              \
        /* fUseSCB - true - is use SCB */                                     \
        fUseSCB,                                                              \
                                                                              \
        /* fConfProtect - Confidentiality protect */                          \
        fConfProtect,                                                         \
                                                                              \
        /* fAllowDataPkts - allow data packets */                             \
        fAllowDataPackets,                                                    \
                                                                              \
        /* Pre-SecTAG Authentication Start */                                 \
        PreSecTAGStart,                                                       \
                                                                              \
        /* Pre-SecTAG Authentication Length */                                \
        PreSecTAGLen                                                          \
      }                                                                       \
    },                                                                        \
                                                                              \
    /* Action type */                                                         \
    SECY_SA_ACTION_EGRESS,                                                    \
                                                                              \
    /* Drop action */                                                         \
    SECY_SA_DROP_CRC_ERROR,                                                   \
                                                                              \
    /* Destination port */                                                    \
    SECY_PORT_COMMON                                                          \
}

#if defined(TEST_IPSEC_ENABLE)
#define SA_Param_IPsec_Egress_Common(fSAInUse,   fRollOverMode, fEncrAuth,        \
                                     CryptoAlg,  fReplayCheck, fIgHdrInsert,      \
                                     fUpdateUDP, fUpdateIP, fNAT_UDP, fOuterIPHdr,\
                                     fConfProtect, fProtectFrames)                \
{                                                                              \
    /* Size of the transform record (TransformRecord_p), in 32-bit words */    \
    0, /* To be filled in later*/                                              \
                                                                               \
    /* Transform record block */                                               \
    NULL, /* To be filled in later*/                                           \
                                                                               \
    {                                                                          \
        .IPsecEgress =                                                         \
        {                                                                      \
            /* fSAInUse, true - SA is in use */                                \
            fSAInUse,                                                          \
                                                                               \
            /* Roll Over Mode */                                               \
            fRollOverMode,                                                     \
                                                                               \
            /** true - Encrypt the GHASH output.*/                             \
            fEncrAuth,                                                         \
                                                                               \
            /** Algorithm for data encryption */                               \
            CryptoAlg,                                                         \
                                                                               \
            /** Enabling IPsec replay check with the mask */                   \
            fReplayCheck,                                                      \
                                                                               \
            fIgHdrInsert,                                                      \
                                                                               \
            /** true - If UDP header is present, update length */              \
            fUpdateUDP,                                                        \
                                                                               \
            /** true - Update outer IP header */                               \
            fUpdateIP,                                                         \
                                                                               \
            /** true - The NAT-T UDP is present after outer IP header */       \
            fNAT_UDP,                                                          \
                                                                               \
            /* Outer IP header, IPv6 or IPV4 */                                \
            fOuterIPHdr,                                                       \
                                                                               \
            /** confidentiality protection */                                  \
            fConfProtect,                                                      \
                                                                               \
            /** enable frame protection */                                     \
            fProtectFrames                                                     \
        }                                                                      \
    },                                                                         \
                                                                               \
    /* Action type */                                                          \
    SECY_SA_ACTION_IPSEC_EGRESS,                                               \
                                                                               \
    /* Drop action */                                                          \
    SECY_SA_DROP_CRC_ERROR,                                                    \
                                                                               \
    /* Destination port */                                                     \
    SECY_PORT_COMMON                                                           \
}


#define SA_Param_IPsec_Ingress_Common(fSAInUse, fRetainPad, fPadCheck,         \
                                      fReplayCheck, fIgHdrInsert,              \
                                      fReplayProtect, fConfProtect,            \
                                      fPadNotValidDrop, fPadLenFailDrop,       \
                                      fUpdateIP,fUpdateTTL)                    \
{                                                                              \
    /* Size of the transform record (TransformRecord_p), in 32-bit words */    \
    0, /* To be filled in later*/                                              \
                                                                               \
    /* Transform record block */                                               \
    NULL, /* To be filled in later*/                                           \
                                                                               \
    {                                                                          \
        .IPsecIngress =                                                        \
        {                                                                      \
            /* fSAInUse, true - SA is in use */                                \
            fSAInUse,                                                          \
                                                                               \
            /** IPsec padding is not removed */                                \
            fRetainPad,                                                        \
                                                                               \
            /** IPsec pad check is enabled */                                  \
            fPadCheck,                                                         \
                                                                               \
            /** Enabling IPsec replay check with the mask */                   \
            fReplayCheck,                                                      \
                                                                               \
            /* true - enable inserting 4-byte SA-Tag */                        \
            fIgHdrInsert,                                                      \
                                                                               \
            /** true - enable replay protection */                             \
            fReplayProtect,                                                    \
                                                                               \
            /** true - enable confidentiality protection */                    \
            fConfProtect,                                                      \
                                                                               \
            /** true - Drop policy for packets with not valid padding */       \
            fPadNotValidDrop,                                                  \
                                                                               \
            /** true - Drop policy for packets */                              \
            fPadLenFailDrop,                                                   \
                                                                               \
            /** true - update outer IP header */                               \
            fUpdateIP,                                                         \
                                                                               \
            /** true - for MPLS-IPsec */                                       \
            fUpdateTTL,                                                        \
        }                                                                      \
    },                                                                         \
                                                                               \
    /* Action type */                                                          \
    SECY_SA_ACTION_IPSEC_INGRESS,                                              \
                                                                               \
    /* Drop action */                                                          \
    SECY_SA_DROP_CRC_ERROR,                                                    \
                                                                               \
    /* Destination port */                                                     \
    SECY_PORT_COMMON                                                           \
}
#endif


#define SA_Param_Ingress_Common(fSAInUse, ConfOffset,                         \
                                fReplayProtect, ValidateFramesTagged, SCI_p,  \
                                AN, fAllowTagged, fAllowUntagged,             \
                                fValidateUntagged, fDummy1, fDummy2,          \
                                PreSecTAGStart, PreSecTAGLen)                 \
  {                                                                           \
    /* Size of the transform record (TransformRecord_p), in 32-bit words */   \
    0, /* To be filled in later*/                                             \
                                                                              \
    /* Transform record block */                                              \
    NULL, /* To be filled in later*/                                          \
                                                                              \
    {                                                                         \
      .Ingress =                                                              \
      {                                                                       \
        /* fSAInUse, true - SA is in use, false - SA not in use */            \
        fSAInUse,                                                             \
                                                                              \
        /* Confidentiality offset */                                          \
        ConfOffset,                                                           \
                                                                              \
        /* fReplayProtect - Replay protection */                              \
        fReplayProtect,                                                       \
                                                                              \
        /* ValidateFramesTagged - Validate frames level */                    \
        ValidateFramesTagged,                                                 \
                                                                              \
        /* SCI to which ingress SA applies, note needs to be filled in */     \
        SCI_p,                                                                \
                                                                              \
        /* Association number to which ingress SA applies */                  \
        AN,                                                                   \
                                                                              \
        /* fAllowTagged - allow tagged packets */                             \
        fAllowTagged,                                                         \
                                                                              \
        /* fAllowUntagged - drop untagged packets */                          \
        fAllowUntagged,                                                       \
                                                                              \
        /* fValidateUntagged - disabled validate untagged packets */          \
        fValidateUntagged,                                                    \
                                                                              \
                                                                              \
        /* Pre-SecTAG Authentication Start */                                 \
        PreSecTAGStart,                                                       \
                                                                              \
        /* Pre-SecTAG Authentication Length */                                \
        PreSecTAGLen,                                                         \
                                                                              \
        /* Retain SecTAG */                                                   \
        false,                                                                \
                                                                              \
        /* Retain ICV */                                                      \
        false,                                                                \
                                                                              \
        /* Retire */                                                          \
        true                                                                  \
      }                                                                       \
    },                                                                        \
                                                                              \
    /* Action type */                                                         \
    SECY_SA_ACTION_INGRESS,                                                   \
                                                                              \
    /* Drop action */                                                         \
    SECY_SA_DROP_CRC_ERROR,                                                   \
                                                                              \
    /* Destination port */                                                    \
    SECY_PORT_CONTROLLED                                                      \
  }


#define SA_Param_Egress_Drop_Bypass(Action_Type)                              \
  {                                                                           \
    /* Size of the transform record (TransformRecord_p), in 32-bit words */   \
    0,                                                                        \
                                                                              \
    /* Transform record block */                                              \
    NULL,                                                                     \
                                                                              \
    {                                                                         \
      .BypassDrop =                                                           \
      {                                                                       \
        /* fSAInUse - SA not in use */                                        \
        false                                                                 \
      }                                                                       \
    },                                                                        \
                                                                              \
    /* Action type */                                                         \
    Action_Type,                                                              \
                                                                              \
    /* Drop action */                                                         \
    SECY_SA_DROP_CRC_ERROR,                                                   \
                                                                              \
    /* Destination port */                                                    \
    SECY_PORT_COMMON,                                                         \
  }

#define SA_Param_Ingress_Drop_Bypass(Action_Type)                             \
  {                                                                           \
    /* Size of the transform record (TransformRecord_p), in 32-bit words */   \
    0,                                                                        \
                                                                              \
    /* Transform record block */                                              \
    NULL,                                                                     \
                                                                              \
    {                                                                         \
      .BypassDrop =                                                           \
      {                                                                       \
        /* fSAInUse - SA not in use */                                        \
        false                                                                 \
      }                                                                       \
    },                                                                        \
                                                                              \
    /* Action type */                                                         \
    Action_Type,                                                              \
                                                                              \
    /* Drop action */                                                         \
    SECY_SA_DROP_CRC_ERROR,                                                   \
                                                                              \
    /* Destination port */                                                    \
    SECY_PORT_CONTROLLED                                                      \
  }

#define SA_Param_Crypt_Authenticate_Encode(ConfOffset, fGCM, fEncrypt)        \
  {                                                                           \
    /* Size of the transform record (TransformRecord_p), in 32-bit words */   \
    0, /* To be filled in later*/                                             \
                                                                              \
    /* Transform record block */                                              \
    NULL, /* To be filled in later*/                                          \
                                                                              \
   {                                                                          \
     .CryptAuth =                                                             \
     {                                                                        \
        /* Zero length message */                                             \
        false,                                                                \
                                                                              \
        /* Confidentiality offset */                                          \
        ConfOffset,                                                           \
                                                                              \
        /* IV loading mode */                                                 \
        2,                                                                    \
                                                                              \
        /* Append ICV */                                                      \
        fGCM,                                                                 \
                                                                              \
        /* Verify ICV */                                                      \
        false,                                                                \
                                                                              \
        /* Confidentiality protect */                                         \
        fEncrypt,                                                             \
      }                                                                       \
    },                                                                        \
                                                                              \
    /* Action type */                                                         \
    SECY_SA_ACTION_CRYPT_AUTH,                                                \
                                                                              \
    /* Drop action */                                                         \
    SECY_SA_DROP_PKT_ERROR,                                                   \
                                                                              \
    /* Destination port */                                                    \
    SECY_PORT_COMMON                                                          \
  }

#define SA_Param_Crypt_Authenticate_Decode(ConfOffset, fGCM, fEncrypt)        \
  {                                                                           \
    /* Size of the transform record (TransformRecord_p), in 32-bit words */   \
    0, /* To be filled in later*/                                             \
                                                                              \
    /* Transform record block */                                              \
    NULL, /* To be filled in later*/                                          \
                                                                              \
   {                                                                          \
     .CryptAuth =                                                             \
     {                                                                        \
        /* Zero length message */                                             \
        false,                                                                \
                                                                              \
        /* Confidentiality offset */                                          \
        ConfOffset,                                                           \
                                                                              \
        /* IV loading mode */                                                 \
        2,                                                                    \
                                                                              \
        /* Append ICV */                                                      \
        false,                                                                \
                                                                              \
        /* Verify ICV */                                                      \
        fGCM,                                                                 \
                                                                              \
        /* Confidentiality protect */                                         \
        fEncrypt                                                              \
      }                                                                       \
    },                                                                        \
                                                                              \
    /* Action type */                                                         \
    SECY_SA_ACTION_CRYPT_AUTH,                                                \
                                                                              \
    /* Drop action */                                                         \
    SECY_SA_DROP_PKT_ERROR,                                                   \
                                                                              \
    /* Destination port */                                                    \
    SECY_PORT_COMMON                                                          \
  }

/* Transform data structure for basic Egress transform */
extern Test_Case_Transform_t Transform_Basic_Transform_Egress;

/* Transform data structure for basic Egress transform, expire SA. */
extern Test_Case_Transform_t Transform_Expire_Egress;

/* Transform data structure for basic Egress transform with tag bypass. */
extern Test_Case_Transform_t Transform_Basic_Transform_Egress_TagBypass;

/* Transform data structure for egress untagged packet. */
extern Test_Case_Transform_t Transform_Untagged_Egress;

/* Transform data structure for egress MTU check. */
extern Test_Case_Transform_t Transform_Egress_MTU_CheckDrop;
extern Test_Case_Transform_t Transform_Egress_MTU_CheckBypass;

/* Transform data structure for basic Ingress transform */
extern Test_Case_Transform_t Transform_Basic_Transform_Ingress;

/* Transform data structure, wrong SCI. */
extern Test_Case_Transform_t Transform_Basic_Transform_WrongSCI_Ingress;

/* Transform data structure for Egress transform with Extended PN */
extern Test_Case_Transform_t Transform_ExtPN_Egress;

/* Transform data structure for Ingress transform with Extended PN */
extern Test_Case_Transform_t Transform_ExtPN_Ingress;

/* Transform data structure for SA Bypass Egress */
extern Test_Case_Transform_t Transform_SA_Bypass_Egress;

/* Transform data structure for SA Bypass Ingress */
extern Test_Case_Transform_t Transform_SA_Bypass_Ingress;

/* Transform data structure for SA Drop Egress */
extern Test_Case_Transform_t Transform_SA_Drop_Egress;

/* Transform data structure for SA Drop Ingress */
extern Test_Case_Transform_t Transform_SA_Drop_Ingress;

/* Transform data structure for Crypt-authenticate Decode */
extern Test_Case_Transform_t Transform_Crypt_Authenticate_Decode_GMAC;

/* Transform data structure for Crypt-authenticate Decode */
extern Test_Case_Transform_t Transform_Crypt_Authenticate_Decode_GCM;

/* Transform data structure for Crypt-authenticate Decode */
extern Test_Case_Transform_t Transform_Crypt_Authenticate_Decode_GCM2;

/* Transform data structure for Crypt-authenticate Encode */
extern Test_Case_Transform_t Transform_Crypt_Authenticate_Encode_ECB;

/* Transform data structure for Crypt-authenticate Encode */
extern Test_Case_Transform_t Transform_Crypt_Authenticate_Encode_CTR;

/* Transform data structure for Crypt-authenticate Encode */
extern Test_Case_Transform_t Transform_Crypt_Authenticate_Encode_GMAC;

/* Transform data structure for Crypt-authenticate Encode */
extern Test_Case_Transform_t Transform_Crypt_Authenticate_Encode_GCM;

/* Transform data structure for Crypt-authenticate Encode */
extern Test_Case_Transform_t Transform_Crypt_Authenticate_Encode_GCM2;

/* Transform data structure for multiple SA Egress transform */
extern Test_Case_Transform_t Transform_Multi_SA_Transform_Egress[];

/* Transform data structure for multiple SA Ingress transform */
extern Test_Case_Transform_t Transform_Multi_SA_Transform_Ingress[];

/* Transform data structure for multiple SCI and AN Ingress transform */
extern Test_Case_Transform_t Transform_Multi_SCI_AN_Transform_Ingress[];

/* Transform data structure for Rekey Egress */
extern Test_Case_Transform_t Transform_Rekey_Egress[];
extern Test_Case_Transform_t Transform_Rekey_Egress_Chain[];

/* Transform data structure for Rekey Ingress */
extern Test_Case_Transform_t Transform_Rekey_Ingress[];
extern Test_Case_Transform_t Transform_Rekey_Ingress_NoSCI[];

/* Transform data structures for Allow Egress Data Packets */
extern Test_Case_Transform_t Transform_AllowEgressDataPackets[];

/* Transform data structures for the Allow Ingress Untagged Packets */
extern Test_Case_Transform_t Transform_AllowIngressUntaggedPackets[];

extern Test_Case_Transform_t Transform_Ingress_BadTag;
extern Test_Case_Transform_t Transform_Ingress_KaY_Packet;

extern Test_Case_Transform_t Transform_MultipleChannel_Egress[];
extern Test_Case_Transform_t Transform_MultipleChannel_Ingress[];

extern Test_Case_Transform_t Transform_Untagged_Egress_MACsec_bn;
extern Test_Case_Transform_t Transform_Untagged_Ingress_MACsec_bn;
extern Test_Case_Transform_t Transform_VLAN_1Q_Egress_MACsec_O1;
extern Test_Case_Transform_t Transform_VLAN_1Q_Egress_MACsec_O2;
extern Test_Case_Transform_t Transform_VLAN_QinQ_Egress_MACsec_O3;
extern Test_Case_Transform_t Transform_VLAN_QinQinQ_Egress_MACsec_O4;
extern Test_Case_Transform_t Transform_VLAN_1Q_Ingress_MACsec_O1;
extern Test_Case_Transform_t Transform_VLAN_1Q_Ingress_MACsec_O2;
extern Test_Case_Transform_t Transform_VLAN_QinQ_Ingress_MACsec_O3;
extern Test_Case_Transform_t Transform_VLAN_QinQinQ_Ingress_MACsec_O4;
extern Test_Case_Transform_t Transform_Egress_Bypass_MACsec[];
extern Test_Case_Transform_t Transform_Ingress_Bypass_MACsec[];

#if defined(TEST_MACSEC_VXLAN_ENABLE)
extern Test_Case_Transform_t Transform_VxLAN_IPv6_Egress_MACsec;
extern Test_Case_Transform_t Transform_VxLAN_IPv4_Egress_MACsec;
extern Test_Case_Transform_t Transform_VxLAN_IPv6_Ingress_MACsec;
extern Test_Case_Transform_t Transform_VxLAN_IPv4_Ingress_MACsec;
#endif

#if defined(TEST_IPSEC_ENABLE)
extern Test_Case_Transform_t Transform_Egress_IPsec_O1;
extern Test_Case_Transform_t Transform_Egress_IPsec_UDP;
extern Test_Case_Transform_t Transform_Egress_IPsecMPLS;
extern Test_Case_Transform_t Transform_Egress_IPsecVLAN;
extern Test_Case_Transform_t Transform_Ingress_IPsec_O1;
extern Test_Case_Transform_t Transform_Ingress_IPsec_UDP;
extern Test_Case_Transform_t Transform_Ingress_IPsec_VLAN;
extern Test_Case_Transform_t Transform_Ingress_IPsec_MPLS;
extern Test_Case_Transform_t Transform_Ingress_IPsec_MPLS_Bypass;
extern Test_Case_Transform_t Transform_Egress_IPsec_SA_Tag_Bypass;
extern Test_Case_Transform_t Transform_Ingress_IPsec_LateCheck;
extern Test_Case_Transform_t Transform_MultipleChannel_Ipsec_MACsec_Egress[];
extern Test_Case_Transform_t Transform_MultiCh_Ipsec_MACsec_Ingress[];
extern Test_Case_Transform_t Transform_IPsec_Multi_SA_Transform_Egress[];
extern Test_Case_Transform_t Transform_IPsec_Multi_SA_Transform_Ingress[];
extern Test_Case_Transform_t Transform_IPsec_Multi_SA_Transform_Egress_Test[];
extern Test_Case_Transform_t Transform_IPsec_ReplayFail_Transform_Ingress[];
#endif

#endif /* TEST_VECTOR_TRANSFORM_H_ */


/* end of file test_vector_transform.h */
