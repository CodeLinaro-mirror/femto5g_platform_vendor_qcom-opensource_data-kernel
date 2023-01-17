
/* test_vector_transform.c
 *
 * Test Tool for CfyE and SecY API's
 * Implementation of the test vector for the test case transform data
 */


/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
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

#include "test_vector_transform.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Driver Framework Basic Defs API */
#include "basic_defs.h"

/* Test Case KAT 1 record format */
#include "test_record.h"

/* General test vectors and configuration data */
#include "test_vector_conf.h"
#include "test_vector_packet.h"

/* constants for SA Builder. */
#include "sa_builder_macsec.h"

/*----------------------------------------------------------------------------
 * Definitions and macros
 */

/*----------------------------------------------------------------------------
 * Local variables
 */
static SecY_SA_Stat_I_t SAStatTest_Ingress_AllZero =
{
    /* Packet counters */
    /*InPktsUnchecked {Lo, Hi} */
    {0, 0},
    /*InPktsDelayed {Lo, Hi} */
    {0, 0},
    /*InPktsLate {Lo, Hi} */
    {0, 0},
    /*InPktsOK {Lo, Hi} */
    {0, 0},
    /*InPktsInvalid {Lo, Hi} */
    {0, 0},
    /*InPktsNotValid {Lo, Hi} */
    {0, 0},
    /*InPktsNotUsingSA {Lo, Hi} */
    {0, 0},
    /*InPktsUnusedSA {Lo, Hi} */
    {0, 0},

    /* Octet counters */
    /*InOctetsDecrypted {Lo, Hi} */
    {0, 0},
    /*InOctetsValidated {Lo, Hi} */
    {0, 0}
};

static SecY_SA_Stat_E_t SAStatTest_Egress_AllZero =
{
    /* Packet counters */
    /*OutPktsEncryptedProtected {Lo, Hi} */
    {0, 0},
    /*OutPktsTooLong {Lo, Hi} */
    {0, 0},
    /*OutPktsSANotInUse */
    {0, 0},

    /* Octet counter */
    /*OutOctetsEncryptedProtected {Lo, Hi} */
    {0, 0}
};

/* Transform data for basic transform related tests */
static uint8_t Transform_Record_Basic_Transform_SCI[] =
{
    0xb9, 0xaa, 0x08, 0xfd, 0x98, 0x8a, 0xbd, 0xc2
};

static uint8_t Transform_Record_Basic_Transform_Key[] =
{
    0x3a, 0x65, 0xbb, 0x5d, 0xcd, 0x99, 0xf9, 0x42,
    0x67, 0xd3, 0x0b, 0x45, 0xc7, 0x8e, 0x7d, 0xfa,
};


static SecY_SA_Stat_E_t SAStatTest_Basic_Transform_Egress =
{
    /* Packet counters */
    /*OutPktsEncryptedProtected {Lo, Hi} */
    {1, 0},
    /*OutPktsTooLong {Lo, Hi} */
    {0, 0},
    /*OutPktsSANotInUse */
    {0, 0},

    /* Octet counter */
    /*OutOctetsEncryptedProtected {Lo, Hi} */
    {60, 0}
};

Test_Case_Transform_t Transform_Basic_Transform_Egress =
{
    .vPort = 0,

    .SCI_p = Transform_Record_Basic_Transform_SCI,

    .AN = 1,

    .Key_p = Transform_Record_Basic_Transform_Key,

    /* Key length */
    .KeyByteCount = sizeof(Transform_Record_Basic_Transform_Key),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0x13,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0, /* SPI value */

    /** SA Builder Operation type */
    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Egress_Common(true, 0, true, false, false, true, true, 0, 12),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_Basic_Transform_Egress,
};

Test_Case_Transform_t Transform_Expire_Egress =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = Transform_Record_Basic_Transform_SCI,

    /* Association number to use */
    .AN = 1,

    /* MACsec key */
    .Key_p = Transform_Record_Basic_Transform_Key,

    /* Key length */
    .KeyByteCount = sizeof(Transform_Record_Basic_Transform_Key),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0xfffffffc,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Egress_Common(true, 0, true, false, false, true, true, 0, 12),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_Basic_Transform_Egress,
};

/* Transform data structure basic transform egress */
Test_Case_Transform_t Transform_Basic_Transform_Egress_TagBypass =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = Transform_Record_Basic_Transform_SCI,

    /* Association number to use */
    .AN = 1,

    /* MACsec key */
    .Key_p = Transform_Record_Basic_Transform_Key,

    /* Key length */
    .KeyByteCount = sizeof(Transform_Record_Basic_Transform_Key),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0x13,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Egress_Common(true, 0, true, false, false, true, true, 0, 12),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_Basic_Transform_Egress,
};

Test_Case_Transform_t Transform_Untagged_Egress =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = Transform_Record_Basic_Transform_SCI,

    /* Association number to use */
    .AN = 1,

    /* MACsec key */
    .Key_p = Transform_Record_Basic_Transform_Key,

    /* Key length */
    .KeyByteCount = sizeof(Transform_Record_Basic_Transform_Key),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0x13,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Egress_Common(true, 0, false, false, false, true, true, 0, 12),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_Egress_AllZero,
};


static SecY_SA_Stat_E_t SAStatTest_Egress_MTU_CheckBypass =
{
    /* Packet counters */
    /*OutPktsEncryptedProtected {Lo, Hi} */
    {1, 0},
    /*OutPktsTooLong {Lo, Hi} */
    {1, 0},
    /*OutPktsSANotInUse */
    {0, 0},

    /* Octet counter */
    /*OutOctetsEncryptedProtected {Lo, Hi} */
    {288, 0}
};

Test_Case_Transform_t Transform_Egress_MTU_CheckBypass =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = Transform_Record_Basic_Transform_SCI,

    /* Association number to use */
    .AN = 1,

    /* MACsec key */
    .Key_p = Transform_Record_Basic_Transform_Key,

    /* Key length */
    .KeyByteCount = sizeof(Transform_Record_Basic_Transform_Key),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0x13,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Egress_Common(true, 0, true, false, false, true, true, 0, 12),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_Egress_MTU_CheckBypass,
};

static SecY_SA_Stat_E_t SAStatTest_Egress_MTU_CheckDrop =
{
    /* Packet counters */
    /*OutPktsEncryptedProtected {Lo, Hi} */
    {0, 0},
    /*OutPktsTooLong {Lo, Hi} */
    {1, 0},
    /*OutPktsSANotInUse */
    {0, 0},

    /* Octet counter */
    /*OutOctetsEncryptedProtected {Lo, Hi} */
    {288, 0}
};

Test_Case_Transform_t Transform_Egress_MTU_CheckDrop =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = Transform_Record_Basic_Transform_SCI,

    /* Association number to use */
    .AN = 1,

    /* MACsec key */
    .Key_p = Transform_Record_Basic_Transform_Key,

    /* Key length */
    .KeyByteCount = sizeof(Transform_Record_Basic_Transform_Key),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0x13,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Egress_Common(true, 0, true, false, false, true, true, 0, 12),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_Egress_MTU_CheckDrop,
};

static SecY_SA_Stat_I_t SAStatTest_Basic_Transform_Ingress =
{
    /* Packet counters */
    /*InPktsUnchecked {Lo, Hi} */
    {0, 0},
    /*InPktsDelayed {Lo, Hi} */
    {0, 0},
    /*InPktsLate {Lo, Hi} */
    {0, 0},
    /*InPktsOK {Lo, Hi} */
    {1, 0},
    /*InPktsInvalid {Lo, Hi} */
    {0, 0},
    /*InPktsNotValid {Lo, Hi} */
    {0, 0},
    /*InPktsNotUsingSA {Lo, Hi} */
    {0, 0},
    /*InPktsUnusedSA {Lo, Hi} */
    {0, 0},

    /* Octet counters */
    /*InOctetsDecrypted {Lo, Hi} */
    {60, 0},
    /*InOctetsValidated {Lo, Hi} */
    {0, 0}
};

Test_Case_Transform_t Transform_Basic_Transform_Ingress =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = Transform_Record_Basic_Transform_SCI,

    /* Association number to use */
    .AN = 1,

    /* MACsec key */
    .Key_p = Transform_Record_Basic_Transform_Key,

    /* Key length */
    .KeyByteCount = sizeof(Transform_Record_Basic_Transform_Key),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0x1,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0x80,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,
                            Transform_Record_Basic_Transform_SCI, 1,
                            true, false, false, false, false, 0, 12),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_Basic_Transform_Ingress,
};


/* Transform data for ExtPN tests */
static uint8_t Transform_Record_ExtPN_SCI[] =
{
    0x12, 0x15, 0x35, 0x24, 0xc0, 0x89, 0x5e, 0x81
};


Test_Case_Transform_t Transform_Basic_Transform_WrongSCI_Ingress =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = Transform_Record_ExtPN_SCI,

    /* Association number to use */
    .AN = 1,

    /* MACsec key */
    .Key_p = Transform_Record_Basic_Transform_Key,

    /* Key length */
    .KeyByteCount = sizeof(Transform_Record_Basic_Transform_Key),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0x13,
    .SeqNumHi = 0x80,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,
                            Transform_Record_Basic_Transform_SCI, 1,
                            true, false, false, false, false, 0, 12),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_Ingress_AllZero,
};

uint8_t Transform_Record_ExtPN_Key[] =
{
    0xad, 0x7a, 0x2b, 0xd0, 0x3e, 0xac, 0x83, 0x5a,
    0x6f, 0x62, 0x0f, 0xdc, 0xb5, 0x06, 0xb3, 0x45,
};

uint8_t Transform_Record_ExtPN_SSCI[] =
{
    0x01, 0x00, 0x00, 0x00,
};

uint8_t Transform_Record_ExtPN_Salt[] =
{
    0x9d, 0x00, 0x29, 0x02, 0x48, 0xde, 0x86, 0xa2,
    0x1c, 0x66, 0xfa, 0x6d,
};


static SecY_SA_Stat_E_t SAStatTest_ExtPN_Egress =
{
    /* Packet counters */
    /*OutPktsEncryptedProtected {Lo, Hi} */
    {1, 0},
    /*OutPktsTooLong {Lo, Hi} */
    {0, 0},
    /*OutPktsSANotInUse */
    {0, 0},

    /* Octet counter */
    /*OutOctetsEncryptedProtected {Lo, Hi} */
    {48, 0},
};

SecY_SA_Stat_I_t SAStatTest_ExtPN_Ingress =
{
    /* Packet counters */
    /*InPktsUnchecked {Lo, Hi} */
    {0, 0},
    /*InPktsDelayed {Lo, Hi} */
    {0, 0},
    /*InPktsLate {Lo, Hi} */
    {0, 0},
    /*InPktsOK {Lo, Hi} */
    {1, 0},
    /*InPktsInvalid {Lo, Hi} */
    {0, 0},
    /*InPktsNotValid {Lo, Hi} */
    {0, 0},
    /*InPktsNotUsingSA {Lo, Hi} */
    {0, 0},
    /*InPktsUnusedSA {Lo, Hi} */
    {0, 0},

    /* Octet counters */
    /*InOctetsDecrypted {Lo, Hi} */
    {48, 0},
    /*InOctetsValidated {Lo, Hi} */
    {0, 0},
};

Test_Case_Transform_t Transform_ExtPN_Egress =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = Transform_Record_ExtPN_SCI,

    /* Association number to use */
    .AN = 2,

    /* MACsec key */
    .Key_p = Transform_Record_ExtPN_Key,

    /* Key length */
    .KeyByteCount = sizeof(Transform_Record_ExtPN_Key),

    /* SSCI */
    .SSCI_p = Transform_Record_ExtPN_SSCI,

    /* Salt */
    .Salt_p = Transform_Record_ExtPN_Salt,

    /* Sequence Number, */
    .SeqNumLo = 0xb2c28464, /* Seq0 */
    .SeqNumHi = 0xb0df459c, /* Seq1 */

    /* Mask */
    .SeqMask = 0,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Egress_Common(true, 0, true, false, false, true, true, 0, 12),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_ExtPN_Egress,
};


/* Transform data structure ExtPN ingress transform */
Test_Case_Transform_t Transform_ExtPN_Ingress =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = Transform_Record_ExtPN_SCI,

    /* Association number to use */
    .AN = 2,

    /* MACsec key */
    .Key_p = Transform_Record_ExtPN_Key,

    /* Key length */
    .KeyByteCount = sizeof(Transform_Record_ExtPN_Key),

    /* SSCI */
    .SSCI_p = Transform_Record_ExtPN_SSCI,

    /* Salt */
    .Salt_p = Transform_Record_ExtPN_Salt,

    /* Sequence Number, */
    .SeqNumLo = 0xb2c28465, /* Seq0 */
    .SeqNumHi = 0xb0df459c, /* Seq1 */

    /* Mask */
    .SeqMask = 0x80,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,
                            NULL, 2,
                            true, false, false, false, false, 0, 12),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_ExtPN_Ingress,
};

Test_Case_Transform_t Transform_SA_Bypass_Egress =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = NULL,

    /* Association number to use */
    .AN = 0,

    /* MACsec key */
    .Key_p = NULL,

    /* Key length */
    .KeyByteCount = 0,

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Egress_Drop_Bypass(SECY_SA_ACTION_BYPASS),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_Egress_AllZero,
};



Test_Case_Transform_t Transform_SA_Bypass_Ingress =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = NULL,

    /* Association number to use */
    .AN = 0,

    /* MACsec key */
    .Key_p = NULL,

    /* Key length */
    .KeyByteCount = 0,

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Ingress_Drop_Bypass(SECY_SA_ACTION_BYPASS),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_Ingress_AllZero,
};

Test_Case_Transform_t Transform_SA_Drop_Egress =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = NULL,

    /* Association number to use */
    .AN = 0,

    /* MACsec key */
    .Key_p = NULL,

    /* Key length */
    .KeyByteCount = 0,

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Egress_Drop_Bypass(SECY_SA_ACTION_DROP),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_Egress_AllZero,
};


Test_Case_Transform_t Transform_SA_Drop_Ingress =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = NULL,

    /* Association number to use */
    .AN = 0,

    /* MACsec key */
    .Key_p = NULL,

    /* Key length */
    .KeyByteCount = 0,

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Ingress_Drop_Bypass(SECY_SA_ACTION_DROP),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_Ingress_AllZero,
};

/* First vector from FIPS ECBMMT128 set. */
static uint8_t Transform_Record_Crypt_Authenticate_Encode_ECB_Key[] =
{
    0x1f, 0x87, 0x33, 0xf4, 0x18, 0x65, 0x81, 0x98,
    0xbd, 0x02, 0x4c, 0x8f, 0x0f, 0xa6, 0xce, 0xfc,
};


Test_Case_Transform_t Transform_Crypt_Authenticate_Encode_ECB =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = NULL,

    /* Association number to use */
    .AN = 0,

    /* MACsec key */
    .Key_p = Transform_Record_Crypt_Authenticate_Encode_ECB_Key,

    /* Key length */
    .KeyByteCount = sizeof(Transform_Record_Crypt_Authenticate_Encode_ECB_Key),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = AUTHENC_OP_AES_CTR,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_ENC_AES_CTR,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Crypt_Authenticate_Encode(0, false, true),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_Egress_AllZero,
};

/* AES-CTR test vector, first from NIST sp800-38a */
static uint8_t Transform_Record_Crypt_Authenticate_Encode_CTR_Key[] =
{
    0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
    0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c,
};


Test_Case_Transform_t Transform_Crypt_Authenticate_Encode_CTR =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = NULL,

    /* Association number to use */
    .AN = 0,

    /* MACsec key */
    .Key_p = Transform_Record_Crypt_Authenticate_Encode_CTR_Key,

    /* Key length */
    .KeyByteCount = sizeof(Transform_Record_Crypt_Authenticate_Encode_CTR_Key),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = AUTHENC_OP_AES_CTR,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_ENC_AES_CTR,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Crypt_Authenticate_Encode(0, false, true),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_Egress_AllZero,
};

/* FIPS AES-GCM vector: gcmEncryptExtIV256: Keylen=256, IVlen=96, PTlen=0, */
/* AADlen=1024, Taglen=128, Count 0 */
static uint8_t Transform_Record_Crypt_Authenticate_Encode_GMAC_Key[] =
{
    0xde, 0x84, 0x84, 0x51, 0x87, 0x0b, 0xbd, 0xe3,
    0x5e, 0x40, 0xb1, 0x59, 0x5d, 0x03, 0xab, 0x0b,
    0xef, 0x91, 0x92, 0xd5, 0xca, 0x7b, 0xef, 0x59,
    0x64, 0x65, 0x9a, 0xac, 0xf4, 0x13, 0x28, 0x51,
};

/* Transform data for the crypt-authenticate encode test */

Test_Case_Transform_t Transform_Crypt_Authenticate_Encode_GMAC =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = NULL,

    /* Association number to use */
    .AN = 0,

    /* MACsec key */
    .Key_p = Transform_Record_Crypt_Authenticate_Encode_GMAC_Key,

    /* Key length */
    .KeyByteCount = sizeof(Transform_Record_Crypt_Authenticate_Encode_GMAC_Key),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = AUTHENC_OP_AES_GCM_ENC,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_ENCAUTH_AES_GCM,

    /* flags */
    .flags = 0,

    /* SA record data Note: encryption must be turned off for GMAC */
    .SA_Data = SA_Param_Crypt_Authenticate_Encode(0, true, false),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_Egress_AllZero,
};

/* FIPS vector: gcmEncryptExtIV256: Keylen=256, IVlen=96, PTlen=1024, */
/* AADlen=0, Taglen=128, Count 0 */
static uint8_t Transform_Record_Crypt_Authenticate_Encode_GCM_Key[] =
{
    0xfb, 0x21, 0x0c, 0xe6, 0x35, 0x5b, 0x96, 0xa0,
    0xba, 0x3d, 0xa2, 0x0e, 0x43, 0xb3, 0x58, 0xec,
    0xc2, 0x42, 0xd3, 0x78, 0x7a, 0x46, 0xa3, 0x4e,
    0x0c, 0x7e, 0xf9, 0x80, 0x35, 0x97, 0x49, 0xfc,
};

/* Transform data for the crypt-authenticate encode test */

Test_Case_Transform_t Transform_Crypt_Authenticate_Encode_GCM =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = NULL,

    /* Association number to use */
    .AN = 0,

    /* MACsec key */
    .Key_p = Transform_Record_Crypt_Authenticate_Encode_GCM_Key,

    /* Key length */
    .KeyByteCount = sizeof(Transform_Record_Crypt_Authenticate_Encode_GCM_Key),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = AUTHENC_OP_AES_GCM_ENC,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_ENCAUTH_AES_GCM,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Crypt_Authenticate_Encode(0, true, true),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_Egress_AllZero,
};

/* AES test vector from NIST test set. GCM Test Case #16. */
static uint8_t Transform_Record_Crypt_Authenticate_Encode_GCM2_Key[] =
{
    0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c,
    0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08,
    0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c,
    0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08,
};

/* Transform data for the crypt-authenticate encode test */

Test_Case_Transform_t Transform_Crypt_Authenticate_Encode_GCM2 =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = NULL,

    /* Association number to use */
    .AN = 0,

    /* MACsec key */
    .Key_p = Transform_Record_Crypt_Authenticate_Encode_GCM2_Key,

    /* Key length */
    .KeyByteCount = sizeof(Transform_Record_Crypt_Authenticate_Encode_GCM2_Key),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = AUTHENC_OP_AES_GCM_ENC,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_ENCAUTH_AES_GCM,

    /* flags */
    .flags = 0,

    /* SA record data, AAD length=20 (from NIST AES-GCM vector #16) */
    /* is filled in here. */
    .SA_Data = SA_Param_Crypt_Authenticate_Encode(20, true, true),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_Egress_AllZero,
};

/* FIPS AES-GCM vector: gcmEncryptExtIV256: Keylen=256, IVlen=96, PTlen=0, */
/* AADlen=1024, Taglen=128, Count 0 */
static uint8_t Transform_Record_Crypt_Authenticate_Decode_GMAC_Key[] =
{
    0xde, 0x84, 0x84, 0x51, 0x87, 0x0b, 0xbd, 0xe3,
    0x5e, 0x40, 0xb1, 0x59, 0x5d, 0x03, 0xab, 0x0b,
    0xef, 0x91, 0x92, 0xd5, 0xca, 0x7b, 0xef, 0x59,
    0x64, 0x65, 0x9a, 0xac, 0xf4, 0x13, 0x28, 0x51,
};

/* Transform data for the crypt-authenticate decode test */

Test_Case_Transform_t Transform_Crypt_Authenticate_Decode_GMAC =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = NULL,

    /* Association number to use */
    .AN = 0,

    /* MACsec key */
    .Key_p = Transform_Record_Crypt_Authenticate_Decode_GMAC_Key,

    /* Key length */
    .KeyByteCount = sizeof(Transform_Record_Crypt_Authenticate_Decode_GMAC_Key),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = AUTHENC_OP_AES_GCM_DEC,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_ENCAUTH_AES_GCM,

    /* flags */
    .flags = 0,

    /* SA record data Note: encryption must be turned off for GMAC */
    .SA_Data = SA_Param_Crypt_Authenticate_Decode(0, true, false),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_Ingress_AllZero,
};


/* FIPS vector: gcmEncryptExtIV256: Keylen=256, IVlen=96, PTlen=1024, */
/* AADlen=0, Taglen=128, Count 0 */
static uint8_t Transform_Record_Crypt_Authenticate_Decode_GCM_Key[] =
{
    0xfb, 0x21, 0x0c, 0xe6, 0x35, 0x5b, 0x96, 0xa0,
    0xba, 0x3d, 0xa2, 0x0e, 0x43, 0xb3, 0x58, 0xec,
    0xc2, 0x42, 0xd3, 0x78, 0x7a, 0x46, 0xa3, 0x4e,
    0x0c, 0x7e, 0xf9, 0x80, 0x35, 0x97, 0x49, 0xfc,
};

/* Transform data for the crypt-authenticate decode test */

Test_Case_Transform_t Transform_Crypt_Authenticate_Decode_GCM =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = NULL,

    /* Association number to use */
    .AN = 0,

    /* MACsec key */
    .Key_p = Transform_Record_Crypt_Authenticate_Decode_GCM_Key,

    /* Key length */
    .KeyByteCount = sizeof(Transform_Record_Crypt_Authenticate_Decode_GCM_Key),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = AUTHENC_OP_AES_GCM_DEC,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_ENCAUTH_AES_GCM,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Crypt_Authenticate_Decode(0, true, true),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_Ingress_AllZero,
};


/* AES test vector from NIST test set. GCM Test Case #16. */
static uint8_t Transform_Record_Crypt_Authenticate_Decode_GCM2_Key[] =
{
    0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c,
    0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08,
    0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c,
    0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08,
};

/* Transform data for the crypt-authenticate decode test */

Test_Case_Transform_t Transform_Crypt_Authenticate_Decode_GCM2 =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = NULL,

    /* Association number to use */
    .AN = 0,

    /* MACsec key */
    .Key_p = Transform_Record_Crypt_Authenticate_Decode_GCM2_Key,

    /* Key length */
    .KeyByteCount = sizeof(Transform_Record_Crypt_Authenticate_Decode_GCM2_Key),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = AUTHENC_OP_AES_GCM_DEC,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_ENCAUTH_AES_GCM,

    /* flags */
    .flags = 0,

    /* SA record data, AAD length=20 (from NIST AES-GCM vector #16) */
    /* is filled in here. */
    .SA_Data = SA_Param_Crypt_Authenticate_Decode(20, true, true),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_Ingress_AllZero,
};


/* Transform data for the multiple SA transform tests */
static uint8_t Transform_Record_Multi_SA_Transform_1_SCI[] =
{
    0xf0, 0x76, 0x1e, 0x8d, 0xcd, 0x3d, 0x00, 0x01
};
static uint8_t Transform_Record_Multi_SA_Transform_2_SCI[] =
{
    0x12, 0x15, 0x35, 0x24, 0xc0, 0x89, 0x5e, 0x81
};
static uint8_t Transform_Record_Multi_SA_Transform_3_SCI[] =
{
    0x7c, 0xfd, 0xe9, 0xf9, 0xe3, 0x37, 0x24, 0xc6
};

static uint8_t Transform_Record_Multi_SA_Transform_1_Key[] =
{
    0x07, 0x1b, 0x11, 0x3b, 0x0c, 0xa7, 0x43, 0xfe,
    0xcc, 0xcf, 0x3d, 0x05, 0x1f, 0x73, 0x73, 0x82,
};

static uint8_t Transform_Record_Multi_SA_Transform_2_Key[] =
{
    0xad, 0x7a, 0x2b, 0xd0, 0x3e, 0xac, 0x83, 0x5a,
    0x6f, 0x62, 0x0f, 0xdc, 0xb5, 0x06, 0xb3, 0x45,
};

static uint8_t Transform_Record_Multi_SA_Transform_3_Key[] =
{
    0x01, 0x3f, 0xe0, 0x0b, 0x5f, 0x11, 0xbe, 0x7f,
    0x86, 0x6d, 0x0c, 0xbb, 0xc5, 0x5a, 0x7a, 0x90,
};



static SecY_SA_Stat_E_t SAStatTest_Multi_SA_Transform_Egress_1 =
{
    /* Packet counters */
    /*OutPktsEncryptedProtected {Lo, Hi} */
    {1, 0},
    /*OutPktsTooLong {Lo, Hi} */
    {0, 0},
    /*OutPktsSANotInUse */
    {0, 0},

    /* Octet counter */
    /*OutOctetsEncryptedProtected {Lo, Hi} */
    {60, 0}
};

static SecY_SA_Stat_E_t SAStatTest_Multi_SA_Transform_Egress_2 =
{
    /* Packet counters */
    /*OutPktsEncryptedProtected {Lo, Hi} */
    {1, 0},
    /*OutPktsTooLong {Lo, Hi} */
    {0, 0},
    /*OutPktsSANotInUse */
    {0, 0},

    /* Octet counter */
    /*OutOctetsEncryptedProtected {Lo, Hi} */
    {48, 0}
};

static SecY_SA_Stat_E_t SAStatTest_Multi_SA_Transform_Egress_3 =
{
    /* Packet counters */
    /*OutPktsEncryptedProtected {Lo, Hi} */
    {1, 0},
    /*OutPktsTooLong {Lo, Hi} */
    {0, 0},
    /*OutPktsSANotInUse */
    {0, 0},

    /* Octet counter */
    /*OutOctetsEncryptedProtected {Lo, Hi} */
    {49, 0}
};

static SecY_SA_Stat_I_t SAStatTest_Multi_SA_Transform_Ingress_1 =
{
    /* Packet counters */
    /*InPktsUnchecked {Lo, Hi} */
    {0, 0},
    /*InPktsDelayed {Lo, Hi} */
    {0, 0},
    /*InPktsLate {Lo, Hi} */
    {0, 0},
    /*InPktsOK {Lo, Hi} */
    {1, 0},
    /*InPktsInvalid {Lo, Hi} */
    {0, 0},
    /*InPktsNotValid {Lo, Hi} */
    {0, 0},
    /*InPktsNotUsingSA {Lo, Hi} */
    {0, 0},
    /*InPktsUnusedSA {Lo, Hi} */
    {0, 0},

    /* Octet counters */
    /*InOctetsDecrypted {Lo, Hi} */
    {60, 0},
    /*InOctetsValidated {Lo, Hi} */
    {0, 0}
};

static SecY_SA_Stat_I_t SAStatTest_Multi_SA_Transform_Ingress_2 =
{
    /* Packet counters */
    /*InPktsUnchecked {Lo, Hi} */
    {0, 0},
    /*InPktsDelayed {Lo, Hi} */
    {0, 0},
    /*InPktsLate {Lo, Hi} */
    {0, 0},
    /*InPktsOK {Lo, Hi} */
    {1, 0},
    /*InPktsInvalid {Lo, Hi} */
    {0, 0},
    /*InPktsNotValid {Lo, Hi} */
    {0, 0},
    /*InPktsNotUsingSA {Lo, Hi} */
    {0, 0},
    /*InPktsUnusedSA {Lo, Hi} */
    {0, 0},

    /* Octet counters */
    /*InOctetsDecrypted {Lo, Hi} */
    {48, 0},
    /*InOctetsValidated {Lo, Hi} */
    {0, 0}
};

static SecY_SA_Stat_I_t SAStatTest_Multi_SA_Transform_Ingress_3 =
{
    /* Packet counters */
    /*InPktsUnchecked {Lo, Hi} */
    {0, 0},
    /*InPktsDelayed {Lo, Hi} */
    {0, 0},
    /*InPktsLate {Lo, Hi} */
    {0, 0},
    /*InPktsOK {Lo, Hi} */
    {1, 0},
    /*InPktsInvalid {Lo, Hi} */
    {0, 0},
    /*InPktsNotValid {Lo, Hi} */
    {0, 0},
    /*InPktsNotUsingSA {Lo, Hi} */
    {0, 0},
    /*InPktsUnusedSA {Lo, Hi} */
    {0, 0},

    /* Octet counters */
    /*InOctetsDecrypted {Lo, Hi} */
    {49, 0},
    /*InOctetsValidated {Lo, Hi} */
    {0, 0}
};

#define TRANSFORM_MULTI_SA_TRANSFORM_EGRESS_1                                  \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 0,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_Multi_SA_Transform_1_SCI,                          \
                                                                               \
  /* AN to use */                                                              \
  .AN = 0,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_Multi_SA_Transform_1_Key,                          \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_Multi_SA_Transform_1_Key),           \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0x76d457ec,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0,                                                                \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Egress_Common(true, 0, true, true, false, true, true, 0, 12), \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = &SAStatTest_Multi_SA_Transform_Egress_1,                  \
}

#define TRANSFORM_MULTI_SA_TRANSFORM_EGRESS_2                                  \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 1,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_Multi_SA_Transform_2_SCI,                          \
                                                                               \
  /* AN to use */                                                              \
  .AN = 2,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_Multi_SA_Transform_2_Key,                          \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_Multi_SA_Transform_2_Key),           \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0xb2c28464,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0,                                                                \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Egress_Common(true, 0, true, false, false, true, true, 0, 12), \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = &SAStatTest_Multi_SA_Transform_Egress_2,                  \
}

#define TRANSFORM_MULTI_SA_TRANSFORM_EGRESS_3                                  \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 2,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_Multi_SA_Transform_3_SCI,                          \
                                                                               \
  /* AN to use */                                                              \
  .AN = 3,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_Multi_SA_Transform_3_Key,                          \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_Multi_SA_Transform_3_Key),           \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0x8932d611,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0,                                                                \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Egress_Common(true, 0, true, false, false, true, true, 0, 12), \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = &SAStatTest_Multi_SA_Transform_Egress_3,                  \
}

Test_Case_Transform_t Transform_Multi_SA_Transform_Egress[] =
{
    TRANSFORM_MULTI_SA_TRANSFORM_EGRESS_1,
    TRANSFORM_MULTI_SA_TRANSFORM_EGRESS_2,
    TRANSFORM_MULTI_SA_TRANSFORM_EGRESS_3
};

#define TRANSFORM_MULTI_SA_TRANSFORM_INGRESS_1                                 \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 0,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_Multi_SA_Transform_1_SCI,                          \
                                                                               \
  /* AN to use */                                                              \
  .AN = 0,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_Multi_SA_Transform_1_Key,                          \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_Multi_SA_Transform_1_Key),           \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0x76d457ed,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0x80,                                                             \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,\
                          NULL, 2,                                             \
                          true, false, false, false, false, 0, 12),            \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = &SAStatTest_Multi_SA_Transform_Ingress_1,                 \
}

#define TRANSFORM_MULTI_SA_TRANSFORM_INGRESS_2                                 \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 0,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_Multi_SA_Transform_2_SCI,                          \
                                                                               \
  /* AN to use */                                                              \
  .AN = 2,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_Multi_SA_Transform_2_Key,                          \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_Multi_SA_Transform_2_Key),           \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0xb2c28465,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0x80,                                                             \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,\
                          NULL, 2,                                             \
                          true, false, false, false, false, 0, 12),            \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = &SAStatTest_Multi_SA_Transform_Ingress_2,                 \
}

#define TRANSFORM_MULTI_SA_TRANSFORM_INGRESS_3                                 \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 0,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_Multi_SA_Transform_3_SCI,                          \
                                                                               \
  /* AN to use */                                                              \
  .AN = 3,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_Multi_SA_Transform_3_Key,                          \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_Multi_SA_Transform_3_Key),           \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0x8932d612,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0x80,                                                             \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,\
                          NULL, 3,                                             \
                          true, false, false, false, false, 0, 12),            \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = &SAStatTest_Multi_SA_Transform_Ingress_3,                 \
}

Test_Case_Transform_t Transform_Multi_SA_Transform_Ingress[] =
{
    TRANSFORM_MULTI_SA_TRANSFORM_INGRESS_1,
    TRANSFORM_MULTI_SA_TRANSFORM_INGRESS_2,
    TRANSFORM_MULTI_SA_TRANSFORM_INGRESS_3
};

/* Transform data for the multiple SCI and AN Ingress test */
static uint8_t Transform_Record_Multi_SCI_AN_Transform_1_SCI[] =
{
    0x12, 0x15, 0x35, 0x24, 0xc0, 0x89, 0x5e, 0x81
};
static uint8_t Transform_Record_Multi_SCI_AN_Transform_2_SCI[] =
{
    0x7c, 0xfd, 0xe9, 0xf9, 0xe3, 0x37, 0x24, 0xc6
};

static uint8_t Transform_Record_Multi_SCI_AN_Transform_1_0_Key[] =
{
    0xad, 0x7a, 0x2b, 0xd0, 0x3e, 0xac, 0x83, 0x5a,
    0x6f, 0x62, 0x0f, 0xdc, 0xb5, 0x06, 0xb3, 0x45,
};

static uint8_t Transform_Record_Multi_SCI_AN_Transform_1_1_Key[] =
{
    0x3a, 0x65, 0xbb, 0x5d, 0xcd, 0x99, 0xf9, 0x42,
    0x67, 0xd3, 0x0b, 0x45, 0xc7, 0x8e, 0x7d, 0xfa,
};

static uint8_t Transform_Record_Multi_SCI_AN_Transform_1_2_Key[] =
{
    0xdd, 0x42, 0xce, 0x8c, 0x03, 0xb8, 0x66, 0xd3,
    0xab, 0x00, 0x7e, 0xde, 0x3e, 0x53, 0xde, 0x30,
};

static uint8_t Transform_Record_Multi_SCI_AN_Transform_2_2_Key[] =
{
    0x01, 0x3f, 0xe0, 0x0b, 0x5f, 0x11, 0xbe, 0x7f,
    0x86, 0x6d, 0x0c, 0xbb, 0xc5, 0x5a, 0x7a, 0x90,
};

static uint8_t Transform_Record_Multi_SCI_AN_Transform_2_3_Key[] =
{
    0x07, 0x1b, 0x11, 0x3b, 0x0c, 0xa7, 0x43, 0xfe,
    0xcc, 0xcf, 0x3d, 0x05, 0x1f, 0x73, 0x73, 0x82,
};



#define TRANSFORM_MULTI_SCI_AN_TRANSFORM_INGRESS_1_0                           \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 0,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_Multi_SCI_AN_Transform_1_SCI,                      \
                                                                               \
  /* AN to use */                                                              \
  .AN = 0,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_Multi_SCI_AN_Transform_1_0_Key,                    \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_Multi_SCI_AN_Transform_1_0_Key),     \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0xb2c28465,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0x80,                                                             \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,\
                          Transform_Record_Multi_SCI_AN_Transform_1_SCI, 0,    \
                          true, false, false, false, false, 0, 12),            \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = NULL,                                                     \
}

#define TRANSFORM_MULTI_SCI_AN_TRANSFORM_INGRESS_1_1                           \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 0,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_Multi_SCI_AN_Transform_1_SCI,                      \
                                                                               \
  /* AN to use */                                                              \
  .AN = 1,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_Multi_SCI_AN_Transform_1_1_Key,                    \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_Multi_SCI_AN_Transform_1_1_Key),     \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0x84b2c265,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0x80,                                                             \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,\
                          Transform_Record_Multi_SCI_AN_Transform_1_SCI, 1,    \
                          true, false, false, false, false, 0, 12),            \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = NULL,                                                     \
}

#define TRANSFORM_MULTI_SCI_AN_TRANSFORM_INGRESS_1_2                           \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 0,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_Multi_SCI_AN_Transform_1_SCI,                      \
                                                                               \
  /* AN to use */                                                              \
  .AN = 2,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_Multi_SCI_AN_Transform_1_2_Key,                    \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_Multi_SCI_AN_Transform_1_2_Key),     \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0xc26484b3,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0x80,                                                             \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,\
                          Transform_Record_Multi_SCI_AN_Transform_1_SCI, 2,    \
                          true, false, false, false, false, 0, 12),            \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = NULL,                                                     \
}

#define TRANSFORM_MULTI_SCI_AN_TRANSFORM_INGRESS_2_2                           \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 0,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_Multi_SCI_AN_Transform_2_SCI,                      \
                                                                               \
  /* AN to use */                                                              \
  .AN = 2,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_Multi_SCI_AN_Transform_2_2_Key,                    \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_Multi_SCI_AN_Transform_2_2_Key),     \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0x8932d612,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0x80,                                                             \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,\
                          Transform_Record_Multi_SCI_AN_Transform_2_SCI, 2,    \
                          true, false, false, false, false, 0, 12),            \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = NULL,                                                     \
}

#define TRANSFORM_MULTI_SCI_AN_TRANSFORM_INGRESS_2_3                           \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 0,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_Multi_SCI_AN_Transform_2_SCI,                      \
                                                                               \
  /* AN to use */                                                              \
  .AN = 3,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_Multi_SCI_AN_Transform_2_3_Key,                    \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_Multi_SCI_AN_Transform_2_3_Key),     \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0xd6891235,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0x80,                                                             \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,\
                          Transform_Record_Multi_SCI_AN_Transform_2_SCI, 3,    \
                          true, false, false, false, false, 0, 12),            \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = NULL,                                                     \
}

Test_Case_Transform_t Transform_Multi_SCI_AN_Transform_Ingress[] =
{
    TRANSFORM_MULTI_SCI_AN_TRANSFORM_INGRESS_1_0,
    TRANSFORM_MULTI_SCI_AN_TRANSFORM_INGRESS_1_1,
    TRANSFORM_MULTI_SCI_AN_TRANSFORM_INGRESS_1_2,
    TRANSFORM_MULTI_SCI_AN_TRANSFORM_INGRESS_2_2,
    TRANSFORM_MULTI_SCI_AN_TRANSFORM_INGRESS_2_3
};

uint8_t Transform_Record_Rekey_1_SCI[] =
{
    0x12, 0x15, 0x35, 0x24, 0xc0, 0x89, 0x5e, 0x81,
};

uint8_t Transform_Record_Rekey_2_SCI[] =
{
    0x7c, 0xfd, 0xe9, 0xf9, 0xe3, 0x37, 0x24, 0xc6,
};

uint8_t Transform_Record_Rekey_1_Key[] =
{
    0xad, 0x7a, 0x2b, 0xd0, 0x3e, 0xac, 0x83, 0x5a,
    0x6f, 0x62, 0x0f, 0xdc, 0xb5, 0x06, 0xb3, 0x45,
};

uint8_t Transform_Record_Rekey_2_Key[] =
{
    0x01, 0x3f, 0xe0, 0x0b, 0x5f, 0x11, 0xbe, 0x7f,
    0x86, 0x6d, 0x0c, 0xbb, 0xc5, 0x5a, 0x7a, 0x90,
};



static SecY_SA_Stat_E_t SAStatTest_Rekey_Egress_1 =
{
    /* Packet counters */
    /*OutPktsEncryptedProtected {Lo, Hi} */
    {1, 0},
    /*OutPktsTooLong {Lo, Hi} */
    {0, 0},
    /*OutPktsSANotInUse */
    {0, 0},

    /* Octet counter */
    /*OutOctetsEncryptedProtected {Lo, Hi} */
    {48, 0}
};

static SecY_SA_Stat_E_t SAStatTest_Rekey_Egress_2 =
{
    /* Packet counters */
    /*OutPktsEncryptedProtected {Lo, Hi} */
    {1, 0},
    /*OutPktsTooLong {Lo, Hi} */
    {0, 0},
    /*OutPktsSANotInUse */
    {0, 0},

    /* Octet counter */
    /*OutOctetsEncryptedProtected {Lo, Hi} */
    {49, 0}
};

#define TRANSFORM_REKEY_EGRESS_1                                               \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 0,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_Rekey_1_SCI,                                       \
                                                                               \
  /* AN to use */                                                              \
  .AN = 2,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_Rekey_1_Key,                                       \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_Rekey_1_Key),                        \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0xb2c28464,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0,                                                                \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Egress_Common(true, 0, true, false, false, true, true, 0, 12), \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = &SAStatTest_Rekey_Egress_1,                               \
}

#define TRANSFORM_REKEY_EGRESS_2                                               \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 0,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_Rekey_2_SCI,                                       \
                                                                               \
  /* AN to use */                                                              \
  .AN = 3,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_Rekey_2_Key,                                       \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_Rekey_2_Key),                        \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0x8932d611,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0,                                                                \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Egress_Common(true, 0, true, false, false, true, true, 0, 12), \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = &SAStatTest_Rekey_Egress_2,                               \
}

Test_Case_Transform_t Transform_Rekey_Egress[] =
{
    TRANSFORM_REKEY_EGRESS_1,
    TRANSFORM_REKEY_EGRESS_2
};


static SecY_SA_Stat_I_t SAStatTest_Rekey_Ingress_1 =
{
    /* Packet counters */
    /*InPktsUnchecked {Lo, Hi} */
    {0, 0},
    /*InPktsDelayed {Lo, Hi} */
    {0, 0},
    /*InPktsLate {Lo, Hi} */
    {0, 0},
    /*InPktsOK {Lo, Hi} */
    {1, 0},
    /*InPktsInvalid {Lo, Hi} */
    {0, 0},
    /*InPktsNotValid {Lo, Hi} */
    {0, 0},
    /*InPktsNotUsingSA {Lo, Hi} */
    {0, 0},
    /*InPktsUnusedSA {Lo, Hi} */
    {0, 0},

    /* Octet counters */
    /*InOctetsDecrypted {Lo, Hi} */
    {48, 0},
    /*InOctetsValidated {Lo, Hi} */
    {0, 0}
};

static SecY_SA_Stat_I_t SAStatTest_Rekey_Ingress_2 =
{
    /* Packet counters */
    /*InPktsUnchecked {Lo, Hi} */
    {0, 0},
    /*InPktsDelayed {Lo, Hi} */
    {0, 0},
    /*InPktsLate {Lo, Hi} */
    {0, 0},
    /*InPktsOK {Lo, Hi} */
    {1, 0},
    /*InPktsInvalid {Lo, Hi} */
    {0, 0},
    /*InPktsNotValid {Lo, Hi} */
    {0, 0},
    /*InPktsNotUsingSA {Lo, Hi} */
    {0, 0},
    /*InPktsUnusedSA {Lo, Hi} */
    {0, 0},

    /* Octet counters */
    /*InOctetsDecrypted {Lo, Hi} */
    {49, 0},
    /*InOctetsValidated {Lo, Hi} */
    {0, 0}
};

#define TRANSFORM_REKEY_INGRESS_1                                              \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 0,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_Rekey_1_SCI,                                       \
                                                                               \
  /* AN to use */                                                              \
  .AN = 2,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_Rekey_1_Key,                                       \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_Rekey_1_Key),                        \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0xb2c28465,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0x80,                                                             \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = SAB_MACSEC_FLAG_NO_LATE_CHECK,                                      \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,\
                          Transform_Record_Rekey_1_SCI, 2,                     \
                          true, false, false, false, false, 0, 12),            \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = &SAStatTest_Rekey_Ingress_1,                              \
}

#define TRANSFORM_REKEY_INGRESS_2                                              \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 0,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_Rekey_1_SCI,                                       \
                                                                               \
  /* AN to use */                                                              \
  .AN = 3,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_Rekey_2_Key,                                       \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_Rekey_2_Key),                        \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0x8932d612,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0x80,                                                             \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,\
                          Transform_Record_Rekey_1_SCI, 3,                     \
                          true, false, false, false, false, 0, 12),            \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = &SAStatTest_Rekey_Ingress_2,                              \
}

Test_Case_Transform_t Transform_Rekey_Ingress[] =
{
    TRANSFORM_REKEY_INGRESS_1,
    TRANSFORM_REKEY_INGRESS_2
};

static uint8_t Transform_Record_Rekey_Ingress_NoSCI_SCI[] =
{
    0xf0, 0x76, 0x1e, 0x8d, 0xcd, 0x3d, 0x00, 0x01,
};


static uint8_t Transform_Record_Rekey_Ingress_NoSCI_Key1[] =
{
    0x07, 0x1b, 0x11, 0x3b, 0x0c, 0xa7, 0x43, 0xfe,
    0xcc, 0xcf, 0x3d, 0x05, 0x1f, 0x73, 0x73, 0x82,
};


static uint8_t Transform_Record_Rekey_Ingress_NoSCI_Key2[] =
{
    0xf8, 0xe4, 0xee, 0xc4, 0xf3, 0x58, 0xbc, 0x01,
    0x33, 0x30, 0xc2, 0xfa, 0xe0, 0x8c, 0x8c, 0x7d,
};



static SecY_SA_Stat_I_t SAStatTest_Rekey_Ingress_NoSCI_1 =
{
    /* Packet counters */
    /*InPktsUnchecked {Lo, Hi} */
    {0, 0},
    /*InPktsDelayed {Lo, Hi} */
    {0, 0},
    /*InPktsLate {Lo, Hi} */
    {0, 0},
    /*InPktsOK {Lo, Hi} */
    {1, 0},
    /*InPktsInvalid {Lo, Hi} */
    {0, 0},
    /*InPktsNotValid {Lo, Hi} */
    {0, 0},
    /*InPktsNotUsingSA {Lo, Hi} */
    {0, 0},
    /*InPktsUnusedSA {Lo, Hi} */
    {0, 0},

    /* Octet counters */
    /*InOctetsDecrypted {Lo, Hi} */
    {48, 0},
    /*InOctetsValidated {Lo, Hi} */
    {0, 0}
};

static SecY_SA_Stat_I_t SAStatTest_Rekey_Ingress_NoSCI_2 =
{
    /* Packet counters */
    /*InPktsUnchecked {Lo, Hi} */
    {0, 0},
    /*InPktsDelayed {Lo, Hi} */
    {0, 0},
    /*InPktsLate {Lo, Hi} */
    {0, 0},
    /*InPktsOK {Lo, Hi} */
    {1, 0},
    /*InPktsInvalid {Lo, Hi} */
    {0, 0},
    /*InPktsNotValid {Lo, Hi} */
    {0, 0},
    /*InPktsNotUsingSA {Lo, Hi} */
    {0, 0},
    /*InPktsUnusedSA {Lo, Hi} */
    {0, 0},

    /* Octet counters */
    /*InOctetsDecrypted {Lo, Hi} */
    {49, 0},
    /*InOctetsValidated {Lo, Hi} */
    {0, 0}
};

#define TRANSFORM_REKEY_INGRESS_NOSCI_1                                        \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 0,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_Rekey_Ingress_NoSCI_SCI,                           \
                                                                               \
  /* AN to use */                                                              \
  .AN = 0,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_Rekey_Ingress_NoSCI_Key1,                          \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_Rekey_Ingress_NoSCI_Key1),           \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0x7865de17,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0,                                                                \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_CHECK, \
                          Transform_Record_Rekey_Ingress_NoSCI_SCI, 0,         \
                          true, false, false, false, false, 0, 12),            \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = &SAStatTest_Rekey_Ingress_NoSCI_1,                        \
}

#define TRANSFORM_REKEY_INGRESS_NOSCI_2                                        \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 0,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_Rekey_Ingress_NoSCI_SCI,                           \
                                                                               \
  /* AN to use */                                                              \
  .AN = 1,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_Rekey_Ingress_NoSCI_Key2,                          \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_Rekey_Ingress_NoSCI_Key2),           \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0x99f91566,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0,                                                                \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_CHECK, \
                                   Transform_Record_Rekey_Ingress_NoSCI_SCI,   \
                                   1, true, false, false, false, false, 0, 12),\
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = &SAStatTest_Rekey_Ingress_NoSCI_2,                        \
}

Test_Case_Transform_t Transform_Rekey_Ingress_NoSCI[] =
{
    TRANSFORM_REKEY_INGRESS_NOSCI_1,
    TRANSFORM_REKEY_INGRESS_NOSCI_2
};


static uint8_t Transform_Record_Rekey_Egress_Chain_SCI[] =
{
    0xf0, 0x76, 0x1e, 0x8d, 0xcd, 0x3d, 0x00, 0x01,
};


static uint8_t Transform_Record_Rekey_Egress_Chain_Key1[] =
{
    0x07, 0x1b, 0x11, 0x3b, 0x0c, 0xa7, 0x43, 0xfe,
    0xcc, 0xcf, 0x3d, 0x05, 0x1f, 0x73, 0x73, 0x82,
};


static uint8_t Transform_Record_Rekey_Egress_Chain_Key2[] =
{
    0xf8, 0xe4, 0xee, 0xc4, 0xf3, 0x58, 0xbc, 0x01,
    0x33, 0x30, 0xc2, 0xfa, 0xe0, 0x8c, 0x8c, 0x7d,
};


static SecY_SA_Stat_E_t SAStatTest_Rekey_Egress_Chain_1 =
{
    /* Packet counters */
    /*OutPktsEncryptedProtected {Lo, Hi} */
    {1, 0},
    /*OutPktsTooLong {Lo, Hi} */
    {0, 0},
    /*OutPktsSANotInUse */
    {0, 0},

    /* Octet counter */
    /*OutOctetsEncryptedProtected {Lo, Hi} */
    {50, 0}
};

static SecY_SA_Stat_E_t SAStatTest_Rekey_Egress_Chain_2 =
{
    /* Packet counters */
    /*OutPktsEncryptedProtected {Lo, Hi} */
    {1, 0},
    /*OutPktsTooLong {Lo, Hi} */
    {0, 0},
    /*OutPktsSANotInUse */
    {0, 0},

    /* Octet counter */
    /*OutOctetsEncryptedProtected {Lo, Hi} */
    {50, 0}
};

#define TRANSFORM_REKEY_EGRESS_CHAIN_1                                         \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 0,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_Rekey_Egress_Chain_SCI,                            \
                                                                               \
  /* AN to use */                                                              \
  .AN = 0,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_Rekey_Egress_Chain_Key1,                           \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_Rekey_Egress_Chain_Key1),            \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0xfffffffc,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0,                                                                \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Egress_Common(true, 0, true, true, false, true, true, 0, 12), \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = &SAStatTest_Rekey_Egress_Chain_1,                         \
}

#define TRANSFORM_REKEY_EGRESS_CHAIN_2                                         \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 0,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_Rekey_Egress_Chain_SCI,                            \
                                                                               \
  /* AN to use */                                                              \
  .AN = 1,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_Rekey_Egress_Chain_Key2,                           \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_Rekey_Egress_Chain_Key2),            \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0x76d457ec,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0,                                                                \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Egress_Common(true, 0, true, true, false, true, true, 0, 12), \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = &SAStatTest_Rekey_Egress_Chain_2,                         \
}

Test_Case_Transform_t Transform_Rekey_Egress_Chain[] =
{
    TRANSFORM_REKEY_EGRESS_CHAIN_1,
    TRANSFORM_REKEY_EGRESS_CHAIN_2
};

static uint8_t Transform_Record_AllowEgressDataPackets_SCI1[] =
{
    0x12, 0x15, 0x35, 0x24, 0xc0, 0x89, 0x5e, 0x81,
};

static uint8_t Transform_Record_AllowEgressDataPackets_SCI2[] =
{
    0x7c, 0xfd, 0xe9, 0xf9, 0xe3, 0x37, 0x24, 0xc6,
};

static uint8_t Transform_Record_AllowEgressDataPackets_Key1[] =
{
    0xad, 0x7a, 0x2b, 0xd0, 0x3e, 0xac, 0x83, 0x5a,
    0x6f, 0x62, 0x0f, 0xdc, 0xb5, 0x06, 0xb3, 0x45,
};

static uint8_t Transform_Record_AllowEgressDataPackets_Key2[] =
{
    0x01, 0x3f, 0xe0, 0x0b, 0x5f, 0x11, 0xbe, 0x7f,
    0x86, 0x6d, 0x0c, 0xbb, 0xc5, 0x5a, 0x7a, 0x90,
};


/* Transform data for the allow egress data packets test */

static SecY_SA_Stat_E_t SAStatTest_AllowEgressDataPackets_1 =
{
    /* Packet counters */
    /*OutPktsEncryptedProtected {Lo, Hi} */
    {1, 0},
    /*OutPktsTooLong {Lo, Hi} */
    {0, 0},
    /*OutPktsSANotInUse */
    {0, 0},

    /* Octet counter */
    /*OutOctetsEncryptedProtected {Lo, Hi} */
    {48, 0}
};

#define TRANSFORM_ALLOW_EGRESS_DATA_PACKETS_1                                  \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 0,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_AllowEgressDataPackets_SCI1,                       \
                                                                               \
  /* AN to use */                                                              \
  .AN = 2,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_AllowEgressDataPackets_Key1,                       \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_AllowEgressDataPackets_Key1),        \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0xb2c28464,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0,                                                                \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Egress_Common(true, 0, true, false, false, true, true, 0, 12), \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = &SAStatTest_AllowEgressDataPackets_1,                     \
}

#define TRANSFORM_ALLOW_EGRESS_DATA_PACKETS_2                                  \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 1,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_AllowEgressDataPackets_SCI2,                       \
                                                                               \
  /* AN to use */                                                              \
  .AN = 3,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_AllowEgressDataPackets_Key2,                       \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_AllowEgressDataPackets_Key2),        \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0x8932d611,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0,                                                                \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Egress_Common(true, 0, true, false, false, true, false, 0, 12), \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = &SAStatTest_Egress_AllZero,                               \
}

Test_Case_Transform_t Transform_AllowEgressDataPackets[] =
{
    TRANSFORM_ALLOW_EGRESS_DATA_PACKETS_1,
    TRANSFORM_ALLOW_EGRESS_DATA_PACKETS_2
};


/* Transform data structures for the allow ingress untagged packets test */
/* Note: Statistics is performed at SecY level */
static uint8_t Transform_Record_AllowIngressUntaggedPackets_1_SCI[] =
{
    0x12, 0x15, 0x35, 0x24, 0xc0, 0x89, 0x5e, 0x81
};

static uint8_t Transform_Record_AllowIngressUntaggedPackets_2_SCI[] =
{
    0x7c, 0xfd, 0xe9, 0xf9, 0xe3, 0x37, 0x24, 0xc6
};

static uint8_t Transform_Record_AllowIngressUntaggedPackets_1_Key[] =
{
    0xad, 0x7a, 0x2b, 0xd0, 0x3e, 0xac, 0x83, 0x5a,
    0x6f, 0x62, 0x0f, 0xdc, 0xb5, 0x06, 0xb3, 0x45,
};

static uint8_t Transform_Record_AllowIngressUntaggedPackets_2_Key[] =
{
    0x01, 0x3f, 0xe0, 0x0b, 0x5f, 0x11, 0xbe, 0x7f,
    0x86, 0x6d, 0x0c, 0xbb, 0xc5, 0x5a, 0x7a, 0x90,
};

#define TRANSFORM_ALLOW_INGRESS_UNTAGGED_PACKETS_1                             \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 0,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_AllowIngressUntaggedPackets_1_SCI,                 \
                                                                               \
  /* AN to use */                                                              \
  .AN = 2,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_AllowIngressUntaggedPackets_1_Key,                 \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_AllowIngressUntaggedPackets_1_Key),  \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0xb2c28465,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0,                                                                \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,\
                          NULL, 2,                                             \
                          true, true, false, false, false, 0, 12),             \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = &SAStatTest_Ingress_AllZero,                              \
}

#define TRANSFORM_ALLOW_INGRESS_UNTAGGED_PACKETS_2                             \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 1,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_AllowIngressUntaggedPackets_2_SCI,                 \
                                                                               \
  /* AN to use */                                                              \
  .AN = 3,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_AllowIngressUntaggedPackets_2_Key,                 \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_AllowIngressUntaggedPackets_2_Key),  \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0x8932d612,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0,                                                                \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,\
                          NULL, 3,                                             \
                          true, true, true, false, false, 0, 12),              \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = &SAStatTest_Ingress_AllZero,                              \
}

Test_Case_Transform_t Transform_AllowIngressUntaggedPackets[] =
{
    TRANSFORM_ALLOW_INGRESS_UNTAGGED_PACKETS_1,
    TRANSFORM_ALLOW_INGRESS_UNTAGGED_PACKETS_2
};


Test_Case_Transform_t Transform_Ingress_BadTag =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = Transform_Record_Basic_Transform_SCI,

    /* Association number to use */
    .AN = 1,

    /* MACsec key */
    .Key_p = Transform_Record_Basic_Transform_Key,

    /* Key length */
    .KeyByteCount = sizeof(Transform_Record_Basic_Transform_Key),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0x1,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0x80,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,
                            NULL, 1,
                            true, false, false, false, false, 0, 12),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_Ingress_AllZero,
};

Test_Case_Transform_t Transform_Ingress_KaY_Packet =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = Transform_Record_Basic_Transform_SCI,

    /* Association number to use */
    .AN = 1,

    /* MACsec key */
    .Key_p = Transform_Record_Basic_Transform_Key,

    /* Key length */
    .KeyByteCount = sizeof(Transform_Record_Basic_Transform_Key),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0x1,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0x80,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,
                            NULL, 1,
                            true, false, false, false, false, 0, 12),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_Ingress_AllZero,
};

/* Transform data structures for multiple channels ingress tests */
static uint8_t Transform_Record_MultipleChannel_0_SCI[] =
{
    0x12, 0x15, 0x35, 0x24, 0xc0, 0x89, 0x5e, 0x81
};

static uint8_t Transform_Record_MultipleChannel_1_SCI[] =
{
    0x7c, 0xfd, 0xe9, 0xf9, 0xe3, 0x37, 0x24, 0xc6
};

static uint8_t Transform_Record_MultipleChannel_2_SCI[] =
{
    0x81, 0x12, 0xab, 0x28, 0x53, 0x35, 0x27, 0xa9
};

static uint8_t Transform_Record_MultipleChannel_3_SCI[] =
{
    0xb9, 0xaa, 0x08, 0xfd, 0x98, 0x8a, 0xbd, 0xc2
};

static uint8_t Transform_Record_MultipleChannel_0_Key[] =
{
    0x3a, 0x65, 0xbb, 0x5d, 0xcd, 0x99, 0xf9, 0x42,
    0x67, 0xd3, 0x0b, 0x45, 0xc7, 0x8e, 0x7d, 0xfa,
};

static uint8_t Transform_Record_MultipleChannel_1_Key[] =
{
    0xad, 0x7a, 0x2b, 0xd0, 0x3e, 0xac, 0x83, 0x5a,
    0x6f, 0x62, 0x0f, 0xdc, 0xb5, 0x06, 0xb3, 0x45,
};

static uint8_t Transform_Record_MultipleChannel_2_Key[] =
{
    0x07, 0x1b, 0x11, 0x3b, 0x0c, 0xa7, 0x43, 0xfe,
    0xcc, 0xcf, 0x3d, 0x05, 0x1f, 0x73, 0x73, 0x82,
};

static uint8_t Transform_Record_MultipleChannel_3_Key[] =
{
    0x01, 0x3f, 0xe0, 0x0b, 0x5f, 0x11, 0xbe, 0x7f,
    0x86, 0x6d, 0x0c, 0xbb, 0xc5, 0x5a, 0x7a, 0x90,
};


/* Transform data structures for multiple channels egress tests */

#define TRANSFORM_MULTIPLE_CHANNEL_EGRESS_0                                    \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 0,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_MultipleChannel_0_SCI,                             \
                                                                               \
  /* AN to use */                                                              \
  .AN = 0,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_MultipleChannel_0_Key,                             \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_MultipleChannel_0_Key),              \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0x00078013,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0,                                                                \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Egress_Common(true, 0, true, false, false, true, true, 0, 12),\
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = NULL,                                                     \
}

#define TRANSFORM_MULTIPLE_CHANNEL_EGRESS_1                                    \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 1,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_MultipleChannel_1_SCI,                             \
                                                                               \
  /* AN to use */                                                              \
  .AN = 0,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_MultipleChannel_1_Key,                             \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_MultipleChannel_1_Key),              \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0xb2c28464,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0,                                                                \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Egress_Common(true, 0, true, false, false, true, true, 0, 12),     \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = NULL,                                                     \
}

#define TRANSFORM_MULTIPLE_CHANNEL_EGRESS_2                                    \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 2,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_MultipleChannel_2_SCI,                             \
                                                                               \
  /* AN to use */                                                              \
  .AN = 0,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_MultipleChannel_2_Key,                             \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_MultipleChannel_2_Key),              \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0x8911d633,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0,                                                                \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Egress_Common(true, 0, true, false, false, true, true, 0, 12), \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = NULL,                                                     \
}

#define TRANSFORM_MULTIPLE_CHANNEL_EGRESS_3                                    \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 3,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_MultipleChannel_3_SCI,                             \
                                                                               \
  /* AN to use */                                                              \
  .AN = 0,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_MultipleChannel_3_Key,                             \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_MultipleChannel_3_Key),              \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0x8932d611,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
   /* Mask */                                                                  \
  .SeqMask = 0,                                                                \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Egress_Common(true, 0, true, false, false, true, true, 0, 12),\
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = NULL,                                                     \
}

Test_Case_Transform_t Transform_MultipleChannel_Egress[] =
{
    TRANSFORM_MULTIPLE_CHANNEL_EGRESS_0,
    TRANSFORM_MULTIPLE_CHANNEL_EGRESS_1,
    TRANSFORM_MULTIPLE_CHANNEL_EGRESS_2,
    TRANSFORM_MULTIPLE_CHANNEL_EGRESS_3
};


#define TRANSFORM_MULTIPLE_CHANNEL_INGRESS_0                                   \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 0,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_MultipleChannel_0_SCI,                             \
                                                                               \
  /* AN to use */                                                              \
  .AN = 0,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_MultipleChannel_0_Key,                             \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_MultipleChannel_0_Key),              \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0x00078014,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0x80,                                                             \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,\
                          NULL, 0,                                             \
                          true, false, false, false, false, 0, 12),            \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = NULL,                                                     \
}

#define TRANSFORM_MULTIPLE_CHANNEL_INGRESS_1                                   \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 1,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_MultipleChannel_1_SCI,                             \
                                                                               \
  /* AN to use */                                                              \
  .AN = 0,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_MultipleChannel_1_Key,                             \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_MultipleChannel_1_Key),              \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0xb2c28465,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0x80,                                                             \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,\
                          NULL, 0,                                             \
                          true, false, false, false, false, 0, 12),            \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = NULL,                                                     \
}

#define TRANSFORM_MULTIPLE_CHANNEL_INGRESS_2                                   \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 2,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_MultipleChannel_2_SCI,                             \
                                                                               \
  /* AN to use */                                                              \
  .AN = 0,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_MultipleChannel_2_Key,                             \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_MultipleChannel_2_Key),              \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0x8911d634,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0,                                                                \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,\
                          NULL, 0,                                             \
                          true, false, false, false, false, 0, 12),            \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = NULL,                                                     \
}

#define TRANSFORM_MULTIPLE_CHANNEL_INGRESS_3                                   \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 3,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_MultipleChannel_3_SCI,                             \
                                                                               \
  /* AN to use */                                                              \
  .AN = 0,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_MultipleChannel_3_Key,                             \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_MultipleChannel_3_Key),              \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0x8932d612,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0,                                                                \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,\
                          NULL, 0,                                             \
                          true, false, false, false, false, 0, 12),            \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = NULL,                                                     \
}

Test_Case_Transform_t Transform_MultipleChannel_Ingress[] =
{
    TRANSFORM_MULTIPLE_CHANNEL_INGRESS_0,
    TRANSFORM_MULTIPLE_CHANNEL_INGRESS_1,
    TRANSFORM_MULTIPLE_CHANNEL_INGRESS_2,
    TRANSFORM_MULTIPLE_CHANNEL_INGRESS_3
};

/* Transform for MACSec */
/* GCM-AES-256 (61-octet frame confidentiality protection) */
static uint8_t SCI_MACsec_bn[] =
{
    0x7c, 0xfd, 0xe9, 0xf9, 0xe3, 0x37, 0x24, 0xc6
};


static uint8_t Key_MACsec_bn[] =
{
    0x83, 0xc0, 0x93, 0xb5, 0x8d, 0xe7, 0xff, 0xe1,
    0xc0, 0xda, 0x92, 0x6a, 0xc4, 0x3f, 0xb3, 0x60,
    0x9a, 0xc1, 0xc8, 0x0f, 0xee, 0x1b, 0x62, 0x44,
    0x97, 0xef, 0x94, 0x2e, 0x2f, 0x79, 0xa8, 0x23,
};

/* Transform for MACsec (egress) */
/* GCM-AES-256 (61-octet frame confidentiality protection) */

static SecY_SA_Stat_E_t SAStatTest_Egress_MACsec_bn =
{
    /* Packet counters */
    /*OutPktsEncryptedProtected {Lo, Hi} */
    {1, 0},
    /*OutPktsTooLong {Lo, Hi} */
    {0, 0},
    /*OutPktsSANotInUse */
    {0, 0},

    /* Octet counter */
    /*OutOctetsEncryptedProtected {Lo, Hi} */
    {49, 0}
};

Test_Case_Transform_t Transform_Untagged_Egress_MACsec_bn =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = SCI_MACsec_bn,

    /* Association number to use */
    .AN = 3,

    /* MACsec key */
    .Key_p = Key_MACsec_bn,

    /* Key length */
    .KeyByteCount = sizeof(Key_MACsec_bn),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0x8932d611,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = SAB_MACSEC_FLAG_ROLLOVER,

    /* SA record data */
    .SA_Data = SA_Param_Egress_Common(true, 0, true, false, false, true, true, 0, 12),

    /* Transform statistics */
   .TransformStat_p = &SAStatTest_Egress_MACsec_bn,
};

static SecY_SA_Stat_I_t SAStatTest_Ingress_MACsec_bn =
{
    /* Packet counters */
    /*InPktsUnchecked {Lo, Hi} */
    {0, 0},
    /*InPktsDelayed {Lo, Hi} */
    {0, 0},
    /*InPktsLate {Lo, Hi} */
    {0, 0},
    /*InPktsOK {Lo, Hi} */
    {1, 0},
    /*InPktsInvalid {Lo, Hi} */
    {0, 0},
    /*InPktsNotValid {Lo, Hi} */
    {0, 0},
    /*InPktsNotUsingSA {Lo, Hi} */
    {0, 0},
    /*InPktsUnusedSA {Lo, Hi} */
    {0, 0},

    /* Octet counters */
    /*InOctetsDecrypted {Lo, Hi} */
    {49, 0},
    /*InOctetsValidated {Lo, Hi} */
    {0, 0}
};

Test_Case_Transform_t Transform_Untagged_Ingress_MACsec_bn =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = SCI_MACsec_bn,

    /* Association number to use */
    .AN = 3,

    /* MACsec key */
    .Key_p = Key_MACsec_bn,

    /* Key length */
    .KeyByteCount = sizeof(Key_MACsec_bn),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0x8932d612,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0x80,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = SAB_MACSEC_FLAG_ROLLOVER,

    /* SA record data */
    .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,
                            SCI_MACsec_bn, 2,
                            true, false, false, false, false, 0, 12),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_Ingress_MACsec_bn,
};

/* GCM-AES-128 (75-octet frame confidentiality protection) */
static uint8_t SCI_VLAN_MACsec[] =
{
    0x7A, 0xE8, 0xE2, 0xCA, 0x4E, 0xC5, 0x00, 0x01
};

static uint8_t Key_VLAN_MACsec[] =
{
    0x88, 0xee, 0x08, 0x7f, 0xd9, 0x5d, 0xa9, 0xfb,
    0xf6, 0x72, 0x5a, 0xa9, 0xd7, 0x57, 0xb0, 0xcd,
};

/* Transform for MACSEC VLAN encapsulation (egress) */
/* GCM-AES-128 (75-octet frame confidentiality protection) */

static SecY_SA_Stat_E_t SAStatTest_VLAN_1Q_Egress_MACsec_O1 =
{
    /* Packet counters */
    /*OutPktsEncryptedProtected {Lo, Hi} */
    {1, 0},
    /*OutPktsTooLong {Lo, Hi} */
    {0, 0},
    /*OutPktsSANotInUse */
    {0, 0},

    /* Octet counter */
    /*OutOctetsEncryptedProtected {Lo, Hi} */
    {48, 0}
};

Test_Case_Transform_t Transform_VLAN_1Q_Egress_MACsec_O1 =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = SCI_VLAN_MACsec,

    /* Association number to use */
    .AN = 1,

    /* MACsec key */
    .Key_p = Key_VLAN_MACsec,

    /* Key length */
    .KeyByteCount = sizeof(Key_VLAN_MACsec),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0x2e58495b,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Egress_Common(true, 0, true, false, false, true, true, 0, 12),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_VLAN_1Q_Egress_MACsec_O1,
};

#if defined(TEST_MACSEC_VXLAN_ENABLE)


static uint8_t SCI_VxLAN_IPv6_MACsec[] =
{
    0xda, 0x20, 0x1f, 0xc5, 0x06, 0x9f, 0x00, 0x00,
};

static uint8_t Key_VxLAN_IPv6_MACsec[] =
{
    0xe1, 0x6c, 0x39, 0xe9, 0x9f, 0x5b, 0xa8, 0x7f,
    0x77, 0x7a, 0x54, 0x3d, 0x68, 0xb2, 0xf1, 0x86,
    0x69, 0x20, 0xc1, 0x9d, 0xb6, 0x9b, 0xe0, 0x3e,
    0x5b, 0x12, 0x66, 0x64, 0x00, 0x91, 0xec, 0x9a,
};

static SecY_SA_Stat_E_t SAStatTest_VxLAN_IPv6_Egress_MACsec =
{
    /* Packet counters */
    /*OutPktsEncryptedProtected {Lo, Hi} */
    {1, 0},
    /*OutPktsTooLong {Lo, Hi} */
    {0, 0},
    /*OutPktsSANotInUse */
    {0, 0},

    /* Octet counter */
    /*OutOctetsEncryptedProtected {Lo, Hi} */
    {300, 0}
};

Test_Case_Transform_t Transform_VxLAN_IPv6_Egress_MACsec =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = SCI_VxLAN_IPv6_MACsec,

    /* Association number to use */
    .AN = 0,

    /* MACsec key */
    .Key_p = Key_VxLAN_IPv6_MACsec,

    /* Key length */
    .KeyByteCount = sizeof(Key_VxLAN_IPv6_MACsec),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Egress_Common(true, 0, true, true, true, true, true, 0, 12),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_VxLAN_IPv6_Egress_MACsec,
};

static uint8_t SCI_VxLAN_IPv4_MACsec[] =
{
    0xf0, 0xe8, 0x83, 0x9a, 0x3c, 0x24, 0x46, 0x1c,
};

static uint8_t Key_VxLAN_IPv4_MACsec[] =
{
    0x11, 0x5c, 0xe9, 0xe3, 0xab, 0x92, 0x74, 0x55,
    0xf6, 0x24, 0xe2, 0x41, 0x3d, 0x12, 0xdb, 0x90,
};

static SecY_SA_Stat_E_t SAStatTest_VxLAN_IPv4_Egress_MACsec =
{
    /* Packet counters */
    /*OutPktsEncryptedProtected {Lo, Hi} */
    {1, 0},
    /*OutPktsTooLong {Lo, Hi} */
    {0, 0},
    /*OutPktsSANotInUse */
    {0, 0},

    /* Octet counter */
    /*OutOctetsEncryptedProtected {Lo, Hi} */
    {289, 0}
};

Test_Case_Transform_t Transform_VxLAN_IPv4_Egress_MACsec =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = SCI_VxLAN_IPv4_MACsec,

    /* Association number to use */
    .AN = 0,

    /* MACsec key */
    .Key_p = Key_VxLAN_IPv4_MACsec,

    /* Key length */
    .KeyByteCount = sizeof(Key_VxLAN_IPv4_MACsec),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Egress_Common(true, 0, true, false, false, true, true, 0, 12),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_VxLAN_IPv4_Egress_MACsec,
};


static SecY_SA_Stat_I_t SAStatTest_VxLAN_IPv6_Ingress_MACsec =
{
    /* Packet counters */
    /*InPktsUnchecked {Lo, Hi} */
    {0, 0},
    /*InPktsDelayed {Lo, Hi} */
    {0, 0},
    /*InPktsLate {Lo, Hi} */
    {0, 0},
    /*InPktsOK {Lo, Hi} */
    {1, 0},
    /*InPktsInvalid {Lo, Hi} */
    {0, 0},
    /*InPktsNotValid {Lo, Hi} */
    {0, 0},
    /*InPktsNotUsingSA {Lo, Hi} */
    {0, 0},
    /*InPktsUnusedSA {Lo, Hi} */
    {0, 0},

    /* Octet counters */
    /*InOctetsDecrypted {Lo, Hi} */
    {300, 0},
    /*InOctetsValidated {Lo, Hi} */
    {0, 0}
};


Test_Case_Transform_t Transform_VxLAN_IPv6_Ingress_MACsec =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = SCI_VxLAN_IPv6_MACsec,

    /* Association number to use */
    .AN = 0,

    /* MACsec key */
    .Key_p = Key_VxLAN_IPv6_MACsec,

    /* Key length */
    .KeyByteCount = sizeof(Key_VxLAN_IPv6_MACsec),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0x1,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0x80,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,
                                       SCI_VxLAN_IPv6_MACsec, 0,
                                       true, false, false, false, false, 0, 12),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_VxLAN_IPv6_Ingress_MACsec,
};

static SecY_SA_Stat_I_t SAStatTest_VxLAN_IPv4_Ingress_MACsec =
{
    /* Packet counters */
    /*InPktsUnchecked {Lo, Hi} */
    {0, 0},
    /*InPktsDelayed {Lo, Hi} */
    {0, 0},
    /*InPktsLate {Lo, Hi} */
    {0, 0},
    /*InPktsOK {Lo, Hi} */
    {1, 0},
    /*InPktsInvalid {Lo, Hi} */
    {0, 0},
    /*InPktsNotValid {Lo, Hi} */
    {0, 0},
    /*InPktsNotUsingSA {Lo, Hi} */
    {0, 0},
    /*InPktsUnusedSA {Lo, Hi} */
    {0, 0},

    /* Octet counters */
    /*InOctetsDecrypted {Lo, Hi} */
    {289, 0},
    /*InOctetsValidated {Lo, Hi} */
    {0, 0}
};


Test_Case_Transform_t Transform_VxLAN_IPv4_Ingress_MACsec =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = SCI_VxLAN_IPv4_MACsec,

    /* Association number to use */
    .AN = 0,

    /* MACsec key */
    .Key_p = Key_VxLAN_IPv4_MACsec,

    /* Key length */
    .KeyByteCount = sizeof(Key_VxLAN_IPv4_MACsec),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0x1,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0x80,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,
                                       SCI_VxLAN_IPv4_MACsec, 0,
                                       true, false, false, false, false, 0, 12),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_VxLAN_IPv4_Ingress_MACsec,
};

#endif

#if defined(TEST_IPSEC_ENABLE)
static uint8_t Key_IPsec_Egress[] =
{
    0x20, 0x93, 0xef, 0xfa, 0xf0, 0x84, 0x7a, 0x84,
    0xaa, 0x74, 0xd5, 0x08, 0xfa, 0x07, 0xcb, 0x9e,
    0x91, 0x7d, 0x48, 0xbe, 0x21, 0xe9, 0xad, 0xbd,
    0x81, 0x03, 0x45, 0x4f, 0x9c, 0x6e, 0xbc, 0xb2,
};

static uint8_t Key_IPsec_EgressMPLS[] =
{
    0x79, 0x88, 0x83, 0x3d, 0x27, 0x31, 0x2f, 0x2e,
    0x1f, 0x18, 0xb8, 0x07, 0x19, 0x1c, 0xd3, 0x71,
    0xbf, 0xca, 0xf3, 0x8b, 0x4b, 0x09, 0x03, 0x3d,
    0xc3, 0xe3, 0x00, 0xd5, 0x72, 0xfd, 0x0b, 0x6a,
};

static uint8_t Key_IPsec_EgressVLAN[] =
{
    0x4e, 0x21, 0x16, 0x1c, 0xc0, 0xec, 0x8b, 0x42,
    0x42, 0x66, 0xa2, 0x21, 0x45, 0x4c, 0x1b, 0xa8,
    0x94, 0x41, 0x07, 0x5b, 0xbd, 0x01, 0xc4, 0xb2,
    0x3e, 0x32, 0x3b, 0xab, 0x79, 0x7b, 0x0a, 0x38,
};

static uint8_t Key_IPsec_Ingress[] =
{
    0xc9, 0xdf, 0xdf, 0x40, 0x9f, 0x58, 0xf9, 0x2c,
    0x28, 0x92, 0xd6, 0xa5, 0x21, 0x9a, 0x22, 0x08,
    0xc1, 0x84, 0x27, 0xee, 0xc4, 0xd7, 0x1f, 0x6e,
    0x98, 0x9c, 0x06, 0xbd, 0xf5, 0x9e, 0xc9, 0x00,
};

static uint8_t IPsecEgressSCI[] = {
    0xfa, 0xd4, 0xd3, 0x40, 0x00, 0x00, 0x00, 0x0,
};

static uint8_t IPsecEgressSalt[] = {0xdc, 0x53, 0x54, 0x69};

Test_Case_Transform_t Transform_Egress_IPsec_O1 =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = IPsecEgressSCI,

    /* Association number to use */
    .AN = 0,

    /* MACsec key */
    .Key_p = Key_IPsec_Egress,

    /* Key length */
    .KeyByteCount = sizeof(Key_IPsec_Egress),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = IPsecEgressSalt,

    /* Sequence Number, */
    .SeqNumLo = 0,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0x40d3d4fa,

    .operation = SAB_OP_IPSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_IPsec_Egress_Common(true, true, true, 7, false,
                                            false, true, true, false,
                                            true, true, true),

    /* Transform statistics */
    .TransformStat_p = NULL,
};


static uint8_t Key_IPsec_EgressUDP[] =
{
    0x0f, 0xd1, 0x5c, 0xe3, 0xd4, 0x9b, 0x2b, 0x21,
    0x07, 0x10, 0xfb, 0x1f, 0x27, 0xbc, 0xec, 0x96,
    0xad, 0xd7, 0xe1, 0x7b, 0xef, 0x48, 0x6d, 0x6c,
    0x3d, 0x68, 0x99, 0xd9, 0x99, 0x60, 0x51, 0x67,
};

static uint8_t IPsecEgressUDPSCI[] = {
    0xfa, 0xd4, 0xd3, 0x40, 0x00, 0x00, 0x00, 0x0,
};

static uint8_t IPsecEgressUDPSalt[] = {0xbf, 0x73, 0x02, 0xbc};

Test_Case_Transform_t Transform_Egress_IPsec_UDP =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = IPsecEgressUDPSCI,

    /* Association number to use */
    .AN = 0,

    /* MACsec key */
    .Key_p = Key_IPsec_EgressUDP,

    /* Key length */
    .KeyByteCount = sizeof(Key_IPsec_EgressUDP),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = IPsecEgressUDPSalt,

    /* Sequence Number, */
    .SeqNumLo = 0,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0x40b6be0e,

    .operation = SAB_OP_IPSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_IPsec_Egress_Common(true, true, true, 7, false,
                                            false, true, true, true,
                                            false, true, true),

    /* Transform statistics */
    .TransformStat_p = NULL,
};


static uint8_t IPsecEgressSATagBypass[] = {
    0xa0, 0x63, 0x66, 0x52, 0x00, 0x00, 0x00, 0x00,
};

static uint8_t Key_IPsec_Egress_SATag_Bypass[] =
{
    0xea, 0xde, 0xfb, 0x9e, 0xb5, 0xd7, 0xaa, 0x22,
    0xfa, 0x50, 0x2b, 0xbe, 0xdb, 0x72, 0x6e, 0x91,
    0xd6, 0xd7, 0xc3, 0x79, 0x9b, 0xf3, 0x6a, 0xa3,
    0xfa, 0xfc, 0x9b, 0xba, 0x47, 0x63, 0xa5, 0x4b,
};

static uint8_t IPsecEgressSaltSATagBypass[] = {0xe2, 0xcf, 0x50, 0xd7};

Test_Case_Transform_t Transform_Egress_IPsec_SA_Tag_Bypass =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = IPsecEgressSATagBypass,

    /* Association number to use */
    .AN = 0,

    /* MACsec key */
    .Key_p = Key_IPsec_Egress_SATag_Bypass,

    /* Key length */
    .KeyByteCount = sizeof(Key_IPsec_Egress_SATag_Bypass),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = IPsecEgressSaltSATagBypass,

    /* Sequence Number, */
    .SeqNumLo = 0,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0x526663a0,

    .operation = SAB_OP_IPSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_IPsec_Egress_Common(true, true, true, 7, false,
                                            false, true, true, false,
                                            true, true, true),

    /* Transform statistics */
    .TransformStat_p = NULL,
};

static uint8_t IPsecEgressMPLSSCI[] = {
    0x94, 0x01, 0x26, 0x7e, 0x00, 0x00, 0x00, 0x00,
};

static uint8_t IPsecEgressMPLSSalt[] = {0xc5, 0xf8, 0x45, 0x1f};

Test_Case_Transform_t Transform_Egress_IPsecMPLS =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = IPsecEgressMPLSSCI,

    /* Association number to use */
    .AN = 0,

    /* MACsec key */
    .Key_p = Key_IPsec_EgressMPLS,

    /* Key length */
    .KeyByteCount = sizeof(Key_IPsec_EgressMPLS),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = IPsecEgressMPLSSalt,

    /* Sequence Number, */
    .SeqNumLo = 0,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0x7e260194,

    .operation = SAB_OP_IPSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_IPsec_Egress_Common(true, true, true, 7, false,
                                            false, true, true, false,
                                            false, true, true),

    /* Transform statistics */
    .TransformStat_p = NULL,
};

static uint8_t IPsecEgressVLAN_SCI[] = {
    0x5f, 0x0b, 0x41, 0x16, 0x00, 0x00, 0x00, 0x00,
};

static uint8_t IPsecEgressVLANSalt[] = {0xf4, 0x72, 0xc7, 0xda};

Test_Case_Transform_t Transform_Egress_IPsecVLAN =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = IPsecEgressVLAN_SCI,

    /* Association number to use */
    .AN = 0,

    /* MACsec key */
    .Key_p = Key_IPsec_EgressVLAN,

    /* Key length */
    .KeyByteCount = sizeof(Key_IPsec_EgressVLAN),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = IPsecEgressVLANSalt,

    /* Sequence Number, */
    .SeqNumLo = 0,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0x16410b5f,

    .operation = SAB_OP_IPSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_IPsec_Egress_Common(true, true, true, 7, false,
                                            false, true, true, false,
                                            false, true, true),

    /* Transform statistics */
    .TransformStat_p = NULL,
};

static uint8_t IPsecIngressSalt[] = {0x9f, 0x9c, 0xa4, 0x0f};

Test_Case_Transform_t Transform_Ingress_IPsec_O1 =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = NULL,

    /* Association number to use */
    .AN = 0,

    /* MACsec key */
    .Key_p = Key_IPsec_Ingress,

    /* Key length */
    .KeyByteCount = sizeof(Key_IPsec_Ingress),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = IPsecIngressSalt,

    /* Sequence Number, */
    .SeqNumLo = 0,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 128,

    .SPI = 0,

    .operation = SAB_OP_IPSEC,

    /* flags */
    .flags = SAB_IPSEC_FLAG_PAD_CHECK,

    /* SA record data */
    .SA_Data = SA_Param_IPsec_Ingress_Common(true, false, true, true,
                                             true, true, true, true,
                                             true, true, false),

    /* Transform statistics */
    .TransformStat_p = NULL,
};

static uint8_t Key_IPsec_IngressUDP[] =
{
    0xbd, 0xe1, 0xbf, 0xce, 0x83, 0xf9, 0xdb, 0xf0,
    0x56, 0xec, 0xf8, 0x44, 0x46, 0xa2, 0xe2, 0x52,
    0x26, 0x15, 0x37, 0x06, 0xaf, 0xf3, 0xde, 0x97,
    0xff, 0x07, 0x7e, 0xed, 0x5b, 0x97, 0x8c, 0x04,
};

static uint8_t IPsecIngressUDPSalt[] = {0xc6, 0xcf, 0x2f, 0xdb};

Test_Case_Transform_t Transform_Ingress_IPsec_UDP =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = NULL,

    /* Association number to use */
    .AN = 0,

    /* MACsec key */
    .Key_p = Key_IPsec_IngressUDP,

    /* Key length */
    .KeyByteCount = sizeof(Key_IPsec_IngressUDP),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = IPsecIngressUDPSalt,

    /* Sequence Number, */
    .SeqNumLo = 0,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 128,

    .SPI = 0,

    .operation = SAB_OP_IPSEC,

    /* flags */
    .flags = SAB_IPSEC_FLAG_PAD_CHECK,

    /* SA record data */
    .SA_Data = SA_Param_IPsec_Ingress_Common(true, false, true, true,
                                             true, true, true, true,
                                             true, true, false),

    /* Transform statistics */
    .TransformStat_p = NULL,
};

static uint8_t Key_IPsec_IngressVLAN[] =
{
    0x7b, 0xa2, 0x95, 0x49, 0xa6, 0x47, 0x85, 0xa8,
    0xcc, 0x82, 0x3b, 0xde, 0xa9, 0x46, 0x4c, 0x76,
    0x80, 0x2c, 0x6f, 0x34, 0x60, 0x6a, 0xce, 0xdd,
    0x1d, 0x47, 0xe6, 0xdd, 0xb8, 0x07, 0xa9, 0xe6,
};

static uint8_t IPsecIngressVLANSalt[] = {0x9e, 0x33, 0xae, 0x1f};

Test_Case_Transform_t Transform_Ingress_IPsec_VLAN =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = NULL,

    /* Association number to use */
    .AN = 0,

    /* MACsec key */
    .Key_p = Key_IPsec_IngressVLAN,

    /* Key length */
    .KeyByteCount = sizeof(Key_IPsec_Ingress),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = IPsecIngressVLANSalt,

    /* Sequence Number, */
    .SeqNumLo = 0,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 128,

    .SPI = 0,

    .operation = SAB_OP_IPSEC,

    /* flags */
    .flags = SAB_IPSEC_FLAG_PAD_CHECK,

    /* SA record data */

    /* SA record data */
    .SA_Data = SA_Param_IPsec_Ingress_Common(true, false, true, true,
                                             true, true, true, true,
                                             true, true, false),

    /* Transform statistics */
    .TransformStat_p = NULL,
};

static uint8_t Key_IPsec_IngressMPLS[] =
{
    0x50, 0xf2, 0x26, 0x82, 0x1b, 0x44, 0xcb, 0xcd,
    0xa0, 0xc5, 0xa2, 0x4a, 0xf7, 0x86, 0x57, 0x11,
    0x59, 0xab, 0x0e, 0x89, 0x4f, 0x06, 0xc8, 0x5d,
    0xac, 0x46, 0xf9, 0x87, 0x4c, 0x6a, 0x34, 0xf2,
};

static uint8_t IPsecIngressMPLSSalt[] = {0x67, 0x2d, 0x36, 0xcd};

static SecY_SA_Stat_I_t SAStatTest_Ingress_IPsec_MPLS =
{
    /* Packet counters */
    /*InPktsUnchecked {Lo, Hi} */
    {0, 0},
    /*InPktsDelayed {Lo, Hi} */
    {0, 0},
    /*InPktsLate {Lo, Hi} */
    {0, 0},
    /*InPktsOK {Lo, Hi} */
    {1, 0},
    /*InPktsInvalid {Lo, Hi} */
    {0, 0},
    /*InPktsNotValid {Lo, Hi} */
    {0, 0},
    /*InPktsNotUsingSA {Lo, Hi} */
    {0, 0},
    /*InPktsUnusedSA {Lo, Hi} */
    {0, 0},

    /* Octet counters */
    /*InOctetsDecrypted {Lo, Hi} */
    {350, 0},
    /*InOctetsValidated {Lo, Hi} */
    {0, 0}
};

Test_Case_Transform_t Transform_Ingress_IPsec_MPLS =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = NULL,

    /* Association number to use */
    .AN = 0,

    /* MACsec key */
    .Key_p = Key_IPsec_IngressMPLS,

    /* Key length */
    .KeyByteCount = sizeof(Key_IPsec_IngressMPLS),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = IPsecIngressMPLSSalt,

    /* Sequence Number, */
    .SeqNumLo = 0,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 128,

    .SPI = 0,

    .operation = SAB_OP_IPSEC,

    /* flags */
    .flags = SAB_IPSEC_FLAG_PAD_CHECK,

    /* SA record data */

    /* SA record data */
    .SA_Data = SA_Param_IPsec_Ingress_Common(true, false, true, true,
                                             true, true, true, true,
                                             true, true, false),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_Ingress_IPsec_MPLS,
};

static uint8_t Key_IPsec_IngressMPLSBypass[] =
{
    0x3e, 0xf7, 0x23, 0x3a, 0x19, 0xa9, 0x2e, 0xb2,
    0x61, 0x3a, 0x61, 0x52, 0xb5, 0xf3, 0x0e, 0xad,
    0xf9, 0xde, 0xc9, 0xfd, 0x49, 0xac, 0xf7, 0x7e,
    0x2c, 0x48, 0x8b, 0x16, 0x0a, 0x58, 0x35, 0xba,
};

static uint8_t IPsecIngressMPLSSaltBypass[] = {0xea, 0x93, 0x51, 0x11};

Test_Case_Transform_t Transform_Ingress_IPsec_MPLS_Bypass =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = NULL,

    /* Association number to use */
    .AN = 0,

    /* MACsec key */
    .Key_p = Key_IPsec_IngressMPLSBypass,

    /* Key length */
    .KeyByteCount = sizeof(Key_IPsec_IngressMPLSBypass),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = IPsecIngressMPLSSaltBypass,

    /* Sequence Number, */
    .SeqNumLo = 0,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 128,

    .SPI = 0,

    .operation = SAB_OP_IPSEC,

    /* flags */
    .flags = SAB_IPSEC_FLAG_PAD_CHECK,

    /* SA record data */
    .SA_Data = SA_Param_IPsec_Ingress_Common(true, false, true, true,
                                             true, true, true, true,
                                             true, true, false),

    /* Transform statistics */
    .TransformStat_p = NULL,
};

static uint8_t Key_IPsec_Ingress_LateCheck[] =
{
    0x4c, 0x9a, 0x7f, 0x2e, 0x9a, 0x82, 0xb2, 0x2d,
    0xcf, 0xef, 0x23, 0x5c, 0xd3, 0x9e, 0x21, 0xc2,
    0xb7, 0xbd, 0x1e, 0x2b, 0x49, 0x2d, 0x1c, 0x12,
    0xd9, 0x7c, 0x82, 0xae, 0x23, 0xb6, 0xb5, 0xd5,
};

static uint8_t IPsecIngressSalt_LateCheck[] = {0xf0, 0xf7, 0xbd, 0xa9};

Test_Case_Transform_t Transform_Ingress_IPsec_LateCheck =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = NULL,

    /* Association number to use */
    .AN = 0,

    /* MACsec key */
    .Key_p = Key_IPsec_Ingress_LateCheck,

    /* Key length */
    .KeyByteCount = sizeof(Key_IPsec_Ingress_LateCheck),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = IPsecIngressSalt_LateCheck,

    /* Sequence Number */
    .SeqNumLo = 0x384,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 128,

    .SPI = 0,

    .operation = SAB_OP_IPSEC,

    /* flags */
    .flags = (SAB_IPSEC_FLAG_PAD_CHECK | SAB_MACSEC_FLAG_LATE_HDR_DROP | SAB_MACSEC_FLAG_LATE_HDR_CHECK),

    /* SA record data */
    .SA_Data = SA_Param_IPsec_Ingress_Common(true, false, true, true,
                                             true, true, true, true,
                                             true, true, false),

    /* Transform statistics */
    .TransformStat_p = NULL,
};

#define TRANSFORM_MULTIPLE_CHANNEL_IPSEC_EGRESS_0                              \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 0,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = IPsecEgressSCI,                                                     \
                                                                               \
  /* AN to use */                                                              \
  .AN = 0,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Key_IPsec_Egress,                                                   \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Key_IPsec_Egress),                                    \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = IPsecEgressSalt,                                                   \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0,                                                               \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0,                                                                \
                                                                               \
  .SPI = 0x40d3d4fa, /* SPI value */                                           \
                                                                               \
  .operation = SAB_OP_IPSEC,                                                   \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_IPsec_Egress_Common(true, true, true, 7, false,          \
                                            false, true, true, false,          \
                                            true, true, true),                 \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = NULL,                                                     \
}

#define TRANSFORM_MULTIPLE_CHANNEL_MACSEC_EGRESS_1                             \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 1,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = Transform_Record_MultipleChannel_1_SCI,                             \
                                                                               \
  /* AN to use */                                                              \
  .AN = 0,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Transform_Record_MultipleChannel_1_Key,                             \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Transform_Record_MultipleChannel_1_Key),              \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = NULL,                                                              \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0xb2c28464,                                                      \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0,                                                                \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
  .operation = SAB_OP_MACSEC,                                                  \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_Egress_Common(true, 0, true, false, false, true, true, 0, 12), \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = NULL,                                                     \
}

Test_Case_Transform_t Transform_MultipleChannel_Ipsec_MACsec_Egress[] =
{
    TRANSFORM_MULTIPLE_CHANNEL_IPSEC_EGRESS_0,
    TRANSFORM_MULTIPLE_CHANNEL_MACSEC_EGRESS_1,
};

#define TRANSFORM_MULTIPLE_CHANNEL_IPSEC_INGRESS_0                             \
{                                                                              \
  /* vPort to use */                                                           \
    .vPort = 0,                                                                \
                                                                               \
    /* SCI to use */                                                           \
    .SCI_p = NULL,                                                             \
                                                                               \
    /* Association number to use */                                            \
    .AN = 0,                                                                   \
                                                                               \
    /* MACsec key */                                                           \
    .Key_p = Key_IPsec_Ingress,                                                \
                                                                               \
    /* Key length */                                                           \
    .KeyByteCount = sizeof(Key_IPsec_Ingress),                                 \
                                                                               \
    /* SSCI */                                                                 \
    .SSCI_p = NULL,                                                            \
                                                                               \
    /* Salt */                                                                 \
    .Salt_p = IPsecIngressSalt,                                                \
                                                                               \
    /* Sequence Number, */                                                     \
    .SeqNumLo = 0,                                                             \
    .SeqNumHi = 0,                                                             \
                                                                               \
    /* Mask */                                                                 \
    .SeqMask = 128,                                                            \
                                                                               \
    .SPI = 0,                                                                  \
                                                                               \
    .operation = SAB_OP_IPSEC,                                                 \
                                                                               \
    /* flags */                                                                \
    .flags = SAB_IPSEC_FLAG_PAD_CHECK,                                         \
                                                                               \
    /* SA record data */                                                       \
    .SA_Data = SA_Param_IPsec_Ingress_Common(true, false, true, true,          \
                                             true, true, true, true,           \
                                             true, true, false),               \
                                                                               \
    /* Transform statistics */                                                 \
    .TransformStat_p = NULL,                                                   \
}

Test_Case_Transform_t Transform_MultiCh_Ipsec_MACsec_Ingress[] =
{
    TRANSFORM_MULTIPLE_CHANNEL_IPSEC_INGRESS_0,
    TRANSFORM_MULTIPLE_CHANNEL_INGRESS_1,
};

static uint8_t IPsecMultiSAEgressSCI_1[] = {
    0x20, 0xb9, 0x2d, 0x03, 0x00, 0x00, 0x00, 0x00,
};

static uint8_t Key_Multi_SA_IPsec_Egress_1[] =
{
    0x9b, 0x90, 0xbc, 0x37, 0x71, 0x86, 0x3b, 0x74,
    0xaf, 0xe9, 0x15, 0x3a, 0xf5, 0x6c, 0x1b, 0x13,
    0x18, 0x19, 0x74, 0x04, 0xc1, 0x0b, 0xda, 0x52,
    0x50, 0x7c, 0x5a, 0x9a, 0x4a, 0x9f, 0x18, 0x52,
};

static uint8_t IPsecMultiSAEgressSalt_1[] = {0x9a, 0x77, 0xe7, 0x1a};

#define TRANSFORM_MULTI_SA_TRANSFORM_IPSEC_EGRESS_TEST                         \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 0,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = IPsecMultiSAEgressSCI_1,                                            \
                                                                               \
  /* AN to use */                                                              \
  .AN = 0,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Key_Multi_SA_IPsec_Egress_1,                                        \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Key_Multi_SA_IPsec_Egress_1),                         \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = IPsecMultiSAEgressSalt_1,                                          \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0,                                                               \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0,                                                                \
                                                                               \
  .SPI = 0x032db920, /* SPI value */                                           \
                                                                               \
  .operation = SAB_OP_IPSEC,                                                   \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_IPsec_Egress_Common(true, true, true, 7, false,          \
                                          false, true, true, false,            \
                                          false, true, true),                  \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = NULL,                                                     \
}


#define TRANSFORM_MULTI_SA_TRANSFORM_IPSEC_EGRESS_1                            \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 1,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = IPsecMultiSAEgressSCI_1,                                            \
                                                                               \
  /* AN to use */                                                              \
  .AN = 0,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Key_Multi_SA_IPsec_Egress_1,                                        \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Key_Multi_SA_IPsec_Egress_1),                         \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = IPsecMultiSAEgressSalt_1,                                          \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0,                                                               \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0,                                                                \
                                                                               \
  .SPI = 0x032db920, /* SPI value */                                           \
                                                                               \
  .operation = SAB_OP_IPSEC,                                                   \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_IPsec_Egress_Common(true, true, true, 7, false,          \
                                          false, true, true, false,            \
                                          false, true, true),                  \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = NULL,                                                     \
}

#define TRANSFORM_MULTI_SA_TRANSFORM_IPSEC_EGRESS_0                            \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 0,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = IPsecEgressSCI,                                                     \
                                                                               \
  /* AN to use */                                                              \
  .AN = 0,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Key_IPsec_Egress,                                                   \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Key_IPsec_Egress),                                    \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = IPsecEgressSalt,                                                   \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0,                                                               \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0,                                                                \
                                                                               \
  .SPI = 0x40d3d4fa, /* SPI value */                                           \
                                                                               \
  .operation = SAB_OP_IPSEC,                                                   \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_IPsec_Egress_Common(true, true, true, 7, false,          \
                                          false, true, true, false,            \
                                          true, true, true),                   \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = NULL,                                                     \
}

static uint8_t Key_Multi_SA_IPsec_Egress_2[] =
{
    0xf5, 0xde, 0x60, 0x7e, 0xab, 0x9d, 0xd9, 0x7a,
    0xae, 0x61, 0xa6, 0xc5, 0x5a, 0x73, 0xa3, 0x13,
    0x0a, 0x0f, 0x93, 0xfc, 0xcb, 0x28, 0x42, 0x7a,
    0x9f, 0xc5, 0x88, 0x48, 0xa6, 0x99, 0xe1, 0x38,
};

static uint8_t IPsecMultiSAEgressSCI_2[] = {
    0x99, 0x8c, 0x0e, 0x5e, 0x00, 0x00, 0x00, 0x00,
};

static uint8_t IPsecMultiSAEgressSalt_2[] = {0xe7, 0x98, 0x86, 0x2b};

#define TRANSFORM_MULTI_SA_TRANSFORM_IPSEC_EGRESS_2                            \
{                                                                              \
  /* vPort to use */                                                           \
  .vPort = 1,                                                                  \
                                                                               \
  /* SCI to use */                                                             \
  .SCI_p = IPsecMultiSAEgressSCI_2,                                            \
                                                                               \
  /* AN to use */                                                              \
  .AN = 0,                                                                     \
                                                                               \
  /* MACsec key */                                                             \
  .Key_p = Key_Multi_SA_IPsec_Egress_2,                                        \
                                                                               \
  /* Key length */                                                             \
  .KeyByteCount = sizeof(Key_Multi_SA_IPsec_Egress_2),                         \
                                                                               \
  /* SSCI */                                                                   \
  .SSCI_p = NULL,                                                              \
                                                                               \
  /* Salt */                                                                   \
  .Salt_p = IPsecMultiSAEgressSalt_2,                                          \
                                                                               \
  /* Sequence Number */                                                        \
  .SeqNumLo = 0,                                                               \
  .SeqNumHi = 0,                                                               \
                                                                               \
  /* Mask */                                                                   \
  .SeqMask = 0,                                                                \
                                                                               \
  .SPI = 0x5e0e8c99, /* SPI value */                                           \
                                                                               \
  .operation = SAB_OP_IPSEC,                                                   \
                                                                               \
  /* flags */                                                                  \
  .flags = 0,                                                                  \
                                                                               \
  /* SA record data */                                                         \
  .SA_Data = SA_Param_IPsec_Egress_Common(true, true, true, 7, false,          \
                                          false, true, true, false,            \
                                          false, true, true),                  \
                                                                               \
  /* Transform statistics */                                                   \
  .TransformStat_p = NULL,                                                     \
}

Test_Case_Transform_t Transform_IPsec_Multi_SA_Transform_Egress_Test[] =
{
    TRANSFORM_MULTI_SA_TRANSFORM_IPSEC_EGRESS_TEST,
};

Test_Case_Transform_t Transform_IPsec_Multi_SA_Transform_Egress[] =
{
    TRANSFORM_MULTI_SA_TRANSFORM_IPSEC_EGRESS_0,
    TRANSFORM_MULTI_SA_TRANSFORM_IPSEC_EGRESS_2,
};

static uint8_t Key_IPsec_MultiSA_Ingress_0[] =
{
    0x7c, 0x1a, 0x20, 0x7f, 0x9e, 0x0e, 0xf6, 0x61,
    0xba, 0x15, 0x33, 0xd4, 0xef, 0x3f, 0x2b, 0x43,
    0x78, 0x76, 0xa8, 0xd5, 0x51, 0x81, 0x49, 0x7f,
    0x8c, 0xf2, 0x6b, 0xa4, 0x27, 0x1a, 0xbc, 0x5d,
};

static uint8_t Salt_IPsec_MultiSA_Ingress_0[] = {0x40, 0xe8, 0xc5, 0x30};


#define TRANSFORM_MULTI_SA_TRANSFORM_IPSEC_INGRESS_0                           \
{                                                                              \
  /* vPort to use */                                                           \
    .vPort = 0,                                                                \
                                                                               \
    /* SCI to use */                                                           \
    .SCI_p = NULL,                                                             \
                                                                               \
    /* Association number to use */                                            \
    .AN = 0,                                                                   \
                                                                               \
    /* MACsec key */                                                           \
    .Key_p = Key_IPsec_MultiSA_Ingress_0,                                      \
                                                                               \
    /* Key length */                                                           \
    .KeyByteCount = sizeof(Key_IPsec_MultiSA_Ingress_0),                       \
                                                                               \
    /* SSCI */                                                                 \
    .SSCI_p = NULL,                                                            \
                                                                               \
    /* Salt */                                                                 \
    .Salt_p = Salt_IPsec_MultiSA_Ingress_0,                                    \
                                                                               \
    /* Sequence Number, */                                                     \
    .SeqNumLo = 0,                                                             \
    .SeqNumHi = 0,                                                             \
                                                                               \
    /* Mask */                                                                 \
    .SeqMask = 128,                                                            \
                                                                               \
    .SPI = 0,                                                                  \
                                                                               \
    .operation = SAB_OP_IPSEC,                                                 \
                                                                               \
    /* flags */                                                                \
    .flags = SAB_IPSEC_FLAG_PAD_CHECK,                                         \
                                                                               \
    /* SA record data */                                                       \
    .SA_Data = SA_Param_IPsec_Ingress_Common(true, false, true, true,          \
                                             true, true, true, true,           \
                                             true, true, false),               \
                                                                               \
    /* Transform statistics */                                                 \
    .TransformStat_p = NULL,                                                   \
}

static uint8_t Key_IPsec_MultiSA_Ingress_1[] =
{
    0x78, 0x6e, 0xf3, 0xc3, 0xa1, 0x0e, 0x8a, 0x6a,
    0x5e, 0x64, 0x8a, 0x24, 0x38, 0x0b, 0xef, 0x76,
    0x8f, 0x67, 0x1f, 0xab, 0x9f, 0x3e, 0x71, 0x5f,
    0x8e, 0xb6, 0xde, 0x3a, 0x7d, 0x96, 0xbf, 0xe9,
};

static uint8_t Salt_IPsec_MultiSA_Ingress_1[] = {0xc5, 0xc7, 0x52, 0x89};

#define TRANSFORM_MULTI_SA_TRANSFORM_IPSEC_INGRESS_1                           \
{                                                                              \
  /* vPort to use */                                                           \
    .vPort = 1,                                                                \
                                                                               \
    /* SCI to use */                                                           \
    .SCI_p = NULL,                                                             \
                                                                               \
    /* Association number to use */                                            \
    .AN = 0,                                                                   \
                                                                               \
    /* MACsec key */                                                           \
    .Key_p = Key_IPsec_MultiSA_Ingress_1,                                      \
                                                                               \
    /* Key length */                                                           \
    .KeyByteCount = sizeof(Key_IPsec_MultiSA_Ingress_1),                       \
                                                                               \
    /* SSCI */                                                                 \
    .SSCI_p = NULL,                                                            \
                                                                               \
    /* Salt */                                                                 \
    .Salt_p = Salt_IPsec_MultiSA_Ingress_1,                                    \
                                                                               \
    /* Sequence Number, */                                                     \
    .SeqNumLo = 0,                                                             \
    .SeqNumHi = 0,                                                             \
                                                                               \
    /* Mask */                                                                 \
    .SeqMask = 128,                                                            \
                                                                               \
    .SPI = 0,                                                                  \
                                                                               \
    .operation = SAB_OP_IPSEC,                                                 \
                                                                               \
    /* flags */                                                                \
    .flags = SAB_IPSEC_FLAG_PAD_CHECK,                                         \
                                                                               \
    /* SA record data */                                                       \
    .SA_Data = SA_Param_IPsec_Ingress_Common(true, false, true, true,          \
                                             true, true, true, true,           \
                                             true, true, false),               \
                                                                               \
    /* Transform statistics */                                                 \
    .TransformStat_p = NULL,                                                   \
}

static uint8_t Key_IPsec_MultiSA_Ingress_2[] =
{
    0x48, 0xaa, 0xb9, 0xca, 0x6d, 0x10, 0x3c, 0x16,
    0x25, 0x80, 0xee, 0xc3, 0xc3, 0xb7, 0x87, 0x52,
    0x05, 0xad, 0x10, 0x42, 0x28, 0x4d, 0x3d, 0x65,
    0xca, 0x0e, 0x7a, 0x92, 0x34, 0x99, 0x59, 0x20,
};

static uint8_t Salt_IPsec_MultiSA_Ingress_2[] = {0x1d, 0xb8, 0xd5, 0x06};

#define TRANSFORM_MULTI_SA_TRANSFORM_IPSEC_INGRESS_2                           \
{                                                                              \
  /* vPort to use */                                                           \
    .vPort = 2,                                                                \
                                                                               \
    /* SCI to use */                                                           \
    .SCI_p = NULL,                                                             \
                                                                               \
    /* Association number to use */                                            \
    .AN = 0,                                                                   \
                                                                               \
    /* MACsec key */                                                           \
    .Key_p = Key_IPsec_MultiSA_Ingress_2,                                      \
                                                                               \
    /* Key length */                                                           \
    .KeyByteCount = sizeof(Key_IPsec_MultiSA_Ingress_2),                       \
                                                                               \
    /* SSCI */                                                                 \
    .SSCI_p = NULL,                                                            \
                                                                               \
    /* Salt */                                                                 \
    .Salt_p = Salt_IPsec_MultiSA_Ingress_2,                                    \
                                                                               \
    /* Sequence Number, */                                                     \
    .SeqNumLo = 0,                                                             \
    .SeqNumHi = 0,                                                             \
                                                                               \
    /* Mask */                                                                 \
    .SeqMask = 128,                                                            \
                                                                               \
    .SPI = 0,                                                                  \
                                                                               \
    .operation = SAB_OP_IPSEC,                                                 \
                                                                               \
    /* flags */                                                                \
    .flags = SAB_IPSEC_FLAG_PAD_CHECK,                                         \
                                                                               \
    /* SA record data */                                                       \
    .SA_Data = SA_Param_IPsec_Ingress_Common(true, false, true, true,          \
                                             true, true, true, true,           \
                                             true, true, false),               \
                                                                               \
    /* Transform statistics */                                                 \
    .TransformStat_p = NULL,                                                   \
}

Test_Case_Transform_t Transform_IPsec_Multi_SA_Transform_Ingress[] =
{
    TRANSFORM_MULTI_SA_TRANSFORM_IPSEC_INGRESS_0,
    TRANSFORM_MULTI_SA_TRANSFORM_IPSEC_INGRESS_1,
    TRANSFORM_MULTI_SA_TRANSFORM_IPSEC_INGRESS_2,
};

static uint8_t Key_IPsec_ReplayFail_Ingress_0[] =
{
    0x33, 0x47, 0x44, 0xf1, 0x64, 0x5d, 0x97, 0x7a,
    0x1e, 0xa5, 0x20, 0x0d, 0x2c, 0x68, 0x23, 0xa0,
    0xd4, 0xb1, 0x27, 0xe4, 0xce, 0x26, 0xbd, 0xdb,
    0x95, 0x8f, 0xb1, 0xc3, 0xb9, 0xc4, 0x32, 0x01,
};

static uint8_t Salt_IPsec_ReplayFail_Ingress_0[] = {0x11, 0x0d, 0x3a, 0xd6};

static SecY_SA_Stat_IPsec_I_t SAStatTest_ReplayFail_Ingress_0 =
{
    /* InPktsPadNotValid */
    {0, 0},

    /* InPktsReplayed */
    {0, 0},

    /* InPktsLate */
    {0, 0},

    /* InPktsOK */
    {2, 0},

    /* InPktsPadLenFail */
    {0, 0},

    /* InPktsNotValid */
    {0, 0},

    /* InPktsNotUsingSA */
    {0, 0},

    /* InPktsPadDummy */
    {0, 0},

    /* InOctetsDecrypted */
    {1772, 0},

    /* InOctetsValidated */
    {0, 0},
};


#define TRANSFORM_REPLAY_FAIL_IPSEC_INGRESS_0                                  \
{                                                                              \
  /* vPort to use */                                                           \
    .vPort = 0,                                                                \
                                                                               \
    /* SCI to use */                                                           \
    .SCI_p = NULL,                                                             \
                                                                               \
    /* Association number to use */                                            \
    .AN = 0,                                                                   \
                                                                               \
    /* MACsec key */                                                           \
    .Key_p = Key_IPsec_ReplayFail_Ingress_0,                                   \
                                                                               \
    /* Key length */                                                           \
    .KeyByteCount = sizeof(Key_IPsec_ReplayFail_Ingress_0),                    \
                                                                               \
    /* SSCI */                                                                 \
    .SSCI_p = NULL,                                                            \
                                                                               \
    /* Salt */                                                                 \
    .Salt_p = Salt_IPsec_ReplayFail_Ingress_0,                                 \
                                                                               \
    /* Sequence Number, */                                                     \
    .SeqNumLo = 0,                                                             \
    .SeqNumHi = 0,                                                             \
                                                                               \
    /* Mask */                                                                 \
    .SeqMask = 128,                                                            \
                                                                               \
    .SPI = 0,                                                                  \
                                                                               \
    .operation = SAB_OP_IPSEC,                                                 \
                                                                               \
    /* flags */                                                                \
    .flags = (SAB_IPSEC_FLAG_PAD_CHECK | SAB_MACSEC_FLAG_LATE_HDR_DROP | \
              SAB_MACSEC_FLAG_LATE_HDR_CHECK | SAB_IPSEC_DISABLE_REPLAY_CHECK),\
                                                                               \
    /* SA record data */                                                       \
    .SA_Data = SA_Param_IPsec_Ingress_Common(true, false, true, false,         \
                                             true, true, true, true,           \
                                             true, true, false),               \
                                                                               \
    /* Transform statistics */                                                 \
    .TransformStat_p = &SAStatTest_ReplayFail_Ingress_0,                       \
}

static uint8_t Key_IPsec_ReplayFail_Ingress_1[] =
{
    0x6a, 0xfa, 0xe1, 0xa9, 0xd5, 0x1e, 0x97, 0x35,
    0x7c, 0xf6, 0x1c, 0x56, 0x94, 0x5f, 0x37, 0x95,
    0x3b, 0xc6, 0xef, 0xbe, 0xdc, 0xf8, 0x79, 0x4e,
    0xfc, 0xa4, 0x47, 0xe6, 0xe3, 0xdd, 0x56, 0xc8,
};


static uint8_t Salt_IPsec_ReplayFail_Ingress_1[] = {0x84, 0x87, 0xd6, 0x5d};

static SecY_SA_Stat_IPsec_I_t SAStatTest_ReplayFail_Ingress_1 =
{
    /* InPktsPadNotValid */
    {0, 0},

    /* InPktsReplayed */
    {1, 0},

    /* InPktsLate */
    {0, 0},

    /* InPktsOK */
    {1, 0},

    /* InPktsPadLenFail */
    {0, 0},

    /* InPktsNotValid */
    {0, 0},

    /* InPktsNotUsingSA */
    {0, 0},

    /* InPktsPadDummy */
    {0, 0},

    /* InOctetsDecrypted */
    {1539, 0},

    /* InOctetsValidated */
    {0, 0},
};

#define TRANSFORM_REPLAY_FAIL_IPSEC_INGRESS_1                                  \
{                                                                              \
  /* vPort to use */                                                           \
    .vPort = 1,                                                                \
                                                                               \
    /* SCI to use */                                                           \
    .SCI_p = NULL,                                                             \
                                                                               \
    /* Association number to use */                                            \
    .AN = 0,                                                                   \
                                                                               \
    /* MACsec key */                                                           \
    .Key_p = Key_IPsec_ReplayFail_Ingress_1,                                   \
                                                                               \
    /* Key length */                                                           \
    .KeyByteCount = sizeof(Key_IPsec_ReplayFail_Ingress_1),                    \
                                                                               \
    /* SSCI */                                                                 \
    .SSCI_p = NULL,                                                            \
                                                                               \
    /* Salt */                                                                 \
    .Salt_p = Salt_IPsec_ReplayFail_Ingress_1,                                 \
                                                                               \
    /* Sequence Number, */                                                     \
    .SeqNumLo = 0,                                                             \
    .SeqNumHi = 0,                                                             \
                                                                               \
    /* Mask */                                                                 \
    .SeqMask = 128,                                                            \
                                                                               \
    .SPI = 0,                                                                  \
                                                                               \
    .operation = SAB_OP_IPSEC,                                                 \
                                                                               \
    /* flags */                                                                \
    .flags = SAB_IPSEC_FLAG_PAD_CHECK,                                         \
                                                                               \
    /* SA record data */                                                       \
    .SA_Data = SA_Param_IPsec_Ingress_Common(true, false, true, true,          \
                                             true, true, true, true,           \
                                             true, true, false),               \
                                                                               \
    /* Transform statistics */                                                 \
    .TransformStat_p = &SAStatTest_ReplayFail_Ingress_1,                       \
}

Test_Case_Transform_t Transform_IPsec_ReplayFail_Transform_Ingress[] =
{
    TRANSFORM_REPLAY_FAIL_IPSEC_INGRESS_0,
    TRANSFORM_REPLAY_FAIL_IPSEC_INGRESS_1,
};
#endif

static SecY_SA_Stat_E_t SAStatTest_VLAN_1Q_Egress_MACsec_O2 =
{
    /* Packet counters */
    /*OutPktsEncryptedProtected {Lo, Hi} */
    {1, 0},
    /*OutPktsTooLong {Lo, Hi} */
    {0, 0},
    /*OutPktsSANotInUse */
    {0, 0},

    /* Octet counter */
    /*OutOctetsEncryptedProtected {Lo, Hi} */
    {44, 0}
};

Test_Case_Transform_t Transform_VLAN_1Q_Egress_MACsec_O2 =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = SCI_VLAN_MACsec,

    /* Association number to use */
    .AN = 1,

    /* MACsec key */
    .Key_p = Key_VLAN_MACsec,

    /* Key length */
    .KeyByteCount = sizeof(Key_VLAN_MACsec),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0x2e58495b,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Egress_Common(true, 0, true, false, false, true, true, 0, 12),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_VLAN_1Q_Egress_MACsec_O2,
};

static SecY_SA_Stat_E_t SAStatTest_VLAN_QinQ_Egress_MACsec_O3 =
{
    /* Packet counters */
    /*OutPktsEncryptedProtected {Lo, Hi} */
    {1, 0},
    /*OutPktsTooLong {Lo, Hi} */
    {0, 0},
    /*OutPktsSANotInUse */
    {0, 0},

    /* Octet counter */
    /*OutOctetsEncryptedProtected {Lo, Hi} */
    {42, 0}
};

Test_Case_Transform_t Transform_VLAN_QinQ_Egress_MACsec_O3 =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = SCI_VLAN_MACsec,

    /* Association number to use */
    .AN = 1,

    /* MACsec key */
    .Key_p = Key_VLAN_MACsec,

    /* Key length */
    .KeyByteCount = sizeof(Key_VLAN_MACsec),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0x2e58495b,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Egress_Common(true, 0, true, false, false, true, true, 0, 12),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_VLAN_QinQ_Egress_MACsec_O3,
};

static SecY_SA_Stat_E_t SAStatTest_VLAN_QinQinQ_Egress_MACsec_O4 =
{
    /* Packet counters */
    /*OutPktsEncryptedProtected {Lo, Hi} */
    {1, 0},
    /*OutPktsTooLong {Lo, Hi} */
    {0, 0},
    /*OutPktsSANotInUse */
    {0, 0},

    /* Octet counter */
    /*OutOctetsEncryptedProtected {Lo, Hi} */
    {42, 0}
};

Test_Case_Transform_t Transform_VLAN_QinQinQ_Egress_MACsec_O4 =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = SCI_VLAN_MACsec,

    /* Association number to use */
    .AN = 1,

    /* MACsec key */
    .Key_p = Key_VLAN_MACsec,

    /* Key length */
    .KeyByteCount = sizeof(Key_VLAN_MACsec),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0x2e58495b,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Egress_Common(true, 0, true, false, false, true, true, 0, 12),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_VLAN_QinQinQ_Egress_MACsec_O4,
};

/* Transform for MACSEC VLAN encapsulation (ingress) */


static SecY_SA_Stat_I_t SAStatTest_VLAN_1Q_Ingress_MACsec_O1 =
{
    /* Packet counters */
    /*InPktsUnchecked {Lo, Hi} */
    {0, 0},
    /*InPktsDelayed {Lo, Hi} */
    {0, 0},
    /*InPktsLate {Lo, Hi} */
    {0, 0},
    /*InPktsOK {Lo, Hi} */
    {1, 0},
    /*InPktsInvalid {Lo, Hi} */
    {0, 0},
    /*InPktsNotValid {Lo, Hi} */
    {0, 0},
    /*InPktsNotUsingSA {Lo, Hi} */
    {0, 0},
    /*InPktsUnusedSA {Lo, Hi} */
    {0, 0},

    /* Octet counters */
    /*InOctetsDecrypted {Lo, Hi} */
    {48, 0},
    /*InOctetsValidated {Lo, Hi} */
    {0, 0}
};

Test_Case_Transform_t Transform_VLAN_1Q_Ingress_MACsec_O1 =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = SCI_VLAN_MACsec,

    /* Association number to use */
    .AN = 1,

    /* MACsec key */
    .Key_p = Key_VLAN_MACsec,

    /* Key length */
    .KeyByteCount = sizeof(Key_VLAN_MACsec),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0x2e58495c,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0x80,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,
                                       SCI_VLAN_MACsec, 2,
                                       true, false, false, false, false, 0, 12),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_VLAN_1Q_Ingress_MACsec_O1,
};

static SecY_SA_Stat_I_t SAStatTest_VLAN_1Q_Ingress_MACsec_O2 =
{
    /* Packet counters */
    /*InPktsUnchecked {Lo, Hi} */
    {0, 0},
    /*InPktsDelayed {Lo, Hi} */
    {0, 0},
    /*InPktsLate {Lo, Hi} */
    {0, 0},
    /*InPktsOK {Lo, Hi} */
    {1, 0},
    /*InPktsInvalid {Lo, Hi} */
    {0, 0},
    /*InPktsNotValid {Lo, Hi} */
    {0, 0},
    /*InPktsNotUsingSA {Lo, Hi} */
    {0, 0},
    /*InPktsUnusedSA {Lo, Hi} */
    {0, 0},

    /* Octet counters */
    /*InOctetsDecrypted {Lo, Hi} */
    {44, 0},
    /*InOctetsValidated {Lo, Hi} */
    {0, 0}
};

Test_Case_Transform_t Transform_VLAN_1Q_Ingress_MACsec_O2 =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = SCI_VLAN_MACsec,

    /* Association number to use */
    .AN = 1,

    /* MACsec key */
    .Key_p = Key_VLAN_MACsec,

    /* Key length */
    .KeyByteCount = sizeof(Key_VLAN_MACsec),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0x2e58495c,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0x80,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,
                            SCI_VLAN_MACsec, 2,
                            true, false, false, false, false, 0, 12),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_VLAN_1Q_Ingress_MACsec_O2,
};

static SecY_SA_Stat_I_t SAStatTest_VLAN_QinQ_Ingress_MACsec_O3 =
{
    /* Packet counters */
    /*InPktsUnchecked {Lo, Hi} */
    {0, 0},
    /*InPktsDelayed {Lo, Hi} */
    {0, 0},
    /*InPktsLate {Lo, Hi} */
    {0, 0},
    /*InPktsOK {Lo, Hi} */
    {1, 0},
    /*InPktsInvalid {Lo, Hi} */
    {0, 0},
    /*InPktsNotValid {Lo, Hi} */
    {0, 0},
    /*InPktsNotUsingSA {Lo, Hi} */
    {0, 0},
    /*InPktsUnusedSA {Lo, Hi} */
    {0, 0},

    /* Octet counters */
    /*InOctetsDecrypted {Lo, Hi} */
    {42, 0},
    /*InOctetsValidated {Lo, Hi} */
    {0, 0}
};

Test_Case_Transform_t Transform_VLAN_QinQ_Ingress_MACsec_O3 =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = SCI_VLAN_MACsec,

    /* Association number to use */
    .AN = 1,

    /* MACsec key */
    .Key_p = Key_VLAN_MACsec,

    /* Key length */
    .KeyByteCount = sizeof(Key_VLAN_MACsec),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0x2e58495c,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0x80,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,
                            SCI_VLAN_MACsec, 2,
                            true, false, false, false, false, 0, 12),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_VLAN_QinQ_Ingress_MACsec_O3,
};

static SecY_SA_Stat_I_t SAStatTest_VLAN_QinQinQ_Ingress_MACsec_O4 =
{
    /* Packet counters */
    /*InPktsUnchecked {Lo, Hi} */
    {0, 0},
    /*InPktsDelayed {Lo, Hi} */
    {0, 0},
    /*InPktsLate {Lo, Hi} */
    {0, 0},
    /*InPktsOK {Lo, Hi} */
    {1, 0},
    /*InPktsInvalid {Lo, Hi} */
    {0, 0},
    /*InPktsNotValid {Lo, Hi} */
    {0, 0},
    /*InPktsNotUsingSA {Lo, Hi} */
    {0, 0},
    /*InPktsUnusedSA {Lo, Hi} */
    {0, 0},

    /* Octet counters */
    /*InOctetsDecrypted {Lo, Hi} */
    {42, 0},
    /*InOctetsValidated {Lo, Hi} */
    {0, 0}
};

Test_Case_Transform_t Transform_VLAN_QinQinQ_Ingress_MACsec_O4 =
{
    /* vPort to use */
    .vPort = 0,

    /* SCI to use */
    .SCI_p = SCI_VLAN_MACsec,

    /* Association number to use */
    .AN = 1,

    /* MACsec key */
    .Key_p = Key_VLAN_MACsec,

    /* Key length */
    .KeyByteCount = sizeof(Key_VLAN_MACsec),

    /* SSCI */
    .SSCI_p = NULL,

    /* Salt */
    .Salt_p = NULL,

    /* Sequence Number, */
    .SeqNumLo = 0x2e58495c,
    .SeqNumHi = 0,

    /* Mask */
    .SeqMask = 0x80,

    .SPI = 0, /* SPI value */

    .operation = SAB_OP_MACSEC,

    /* flags */
    .flags = 0,

    /* SA record data */
    .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT,
                            SCI_VLAN_MACsec, 2,
                            true, false, false, false, false, 0, 12),

    /* Transform statistics */
    .TransformStat_p = &SAStatTest_VLAN_QinQinQ_Ingress_MACsec_O4,
};


#define  TRANSFORM_EGRESS_BYPASS_MACSEC_1                                   \
  {                                                                         \
      /* vPort to use */                                                    \
      .vPort = 0,                                                           \
                                                                            \
     /* SCI to use */                                                       \
     .SCI_p = NULL,                                                         \
                                                                            \
     /* Association number to use */                                        \
     .AN = 0,                                                               \
                                                                            \
    /* MACsec key */                                                        \
    .Key_p = NULL,                                                          \
                                                                            \
    /* Key length */                                                        \
    .KeyByteCount = 0,                                                      \
                                                                            \
    /* SSCI */                                                              \
    .SSCI_p = NULL,                                                         \
                                                                            \
    /* Salt */                                                              \
    .Salt_p = NULL,                                                         \
                                                                            \
    /* Sequence Number, */                                                  \
    .SeqNumLo = 0,                                                          \
    .SeqNumHi = 0,                                                          \
                                                                            \
    /* Mask */                                                              \
    .SeqMask = 0,                                                           \
                                                                            \
  .SPI = 0, /* SPI value */                                                    \
                                                                            \
    .operation = SAB_OP_MACSEC,                                             \
                                                                            \
    /* flags */                                                             \
    .flags = 0,                                                             \
                                                                            \
    /* SA record data */                                                    \
    .SA_Data = SA_Param_Egress_Drop_Bypass(SECY_SA_ACTION_BYPASS),          \
                                                                            \
    /* Transform statistics */                                              \
    .TransformStat_p = &SAStatTest_Egress_AllZero,                          \
  }

#define  TRANSFORM_EGRESS_BYPASS_MACSEC_2                                   \
  {                                                                         \
    /* vPort to use */                                                      \
    .vPort = 0,                                                             \
                                                                            \
    /* SCI to use */                                                        \
    .SCI_p = Transform_Record_Basic_Transform_SCI,                          \
                                                                            \
    /* Association number to use */                                         \
    .AN = 1,                                                                \
                                                                            \
    /* MACsec key */                                                        \
    .Key_p = Transform_Record_Basic_Transform_Key,                          \
                                                                            \
    /* Key length */                                                        \
    .KeyByteCount = sizeof(Transform_Record_Basic_Transform_Key),           \
                                                                            \
    /* SSCI */                                                              \
    .SSCI_p = NULL,                                                         \
                                                                            \
    /* Salt */                                                              \
    .Salt_p = NULL,                                                         \
                                                                            \
    /* Sequence Number, */                                                  \
    .SeqNumLo = 0x13,                                                       \
    .SeqNumHi = 0,                                                          \
                                                                            \
    /* Mask */                                                              \
    .SeqMask = 0,                                                           \
                                                                            \
  .SPI = 0, /* SPI value */                                                    \
                                                                            \
    .operation = SAB_OP_MACSEC,                                             \
                                                                            \
    /* flags */                                                             \
    .flags = 0,                                                             \
                                                                            \
    /* SA record data */                                                    \
    .SA_Data = SA_Param_Egress_Common(true, 0, true, false, false, true, true, 0, 12),\
                                                                            \
    /* Transform statistics */                                              \
    .TransformStat_p = &SAStatTest_Basic_Transform_Egress,                  \
  }


Test_Case_Transform_t Transform_Egress_Bypass_MACsec[] =
{
    TRANSFORM_EGRESS_BYPASS_MACSEC_1,
    TRANSFORM_EGRESS_BYPASS_MACSEC_2,
};


#define  TRANSFORM_INGRESS_BYPASS_MACSEC_1                                   \
  {                                                                          \
     /* vPort to use */                                                      \
     .vPort = 0,                                                             \
                                                                             \
     /* SCI to use */                                                        \
     .SCI_p = NULL,                                                          \
                                                                             \
     /* Association number to use */                                         \
     .AN = 0,                                                                \
                                                                             \
    /* MACsec key */                                                         \
    .Key_p = NULL,                                                           \
                                                                             \
    /* Key length */                                                         \
    .KeyByteCount = 0,                                                       \
                                                                             \
    /* SSCI */                                                               \
    .SSCI_p = NULL,                                                          \
                                                                             \
    /* Salt */                                                               \
    .Salt_p = NULL,                                                          \
                                                                             \
    /* Sequence Number, */                                                   \
    .SeqNumLo = 0,                                                           \
    .SeqNumHi = 0,                                                           \
                                                                             \
    /* Mask */                                                               \
    .SeqMask = 0,                                                            \
                                                                             \
  .SPI = 0, /* SPI value */                                                    \
                                                                             \
    .operation = SAB_OP_MACSEC,                                              \
                                                                             \
    /* flags */                                                              \
    .flags = 0,                                                              \
                                                                             \
    /* SA record data */                                                     \
    .SA_Data = SA_Param_Ingress_Drop_Bypass(SECY_SA_ACTION_BYPASS),          \
                                                                             \
    /* Transform statistics */                                               \
    .TransformStat_p = &SAStatTest_Ingress_AllZero,                          \
  }

#define  TRANSFORM_INGRESS_BYPASS_MACSEC_2                                     \
  {                                                                            \
    /* vPort to use */                                                         \
    .vPort = 0,                                                                \
                                                                               \
    /* SCI to use */                                                           \
    .SCI_p = Transform_Record_Basic_Transform_SCI,                             \
                                                                               \
    /* Association number to use */                                            \
    .AN = 1,                                                                   \
                                                                               \
    /* MACsec key */                                                           \
    .Key_p = Transform_Record_Basic_Transform_Key,                             \
                                                                               \
    /* Key length */                                                           \
    .KeyByteCount = sizeof(Transform_Record_Basic_Transform_Key),              \
                                                                               \
    /* SSCI */                                                                 \
    .SSCI_p = NULL,                                                            \
                                                                               \
    /* Salt */                                                                 \
    .Salt_p = NULL,                                                            \
                                                                               \
    /* Sequence Number, */                                                     \
    .SeqNumLo = 0x1,                                                           \
    .SeqNumHi = 0,                                                             \
                                                                               \
    /* Mask */                                                                 \
    .SeqMask = 0x80,                                                           \
                                                                               \
  .SPI = 0, /* SPI value */                                                    \
                                                                               \
    .operation = SAB_OP_MACSEC,                                                \
                                                                               \
    /* flags */                                                                \
    .flags = 0,                                                                \
                                                                               \
    /* SA record data */                                                       \
    .SA_Data = SA_Param_Ingress_Common(true, 0, true, SECY_FRAME_VALIDATE_STRICT, \
                            Transform_Record_Basic_Transform_SCI, 1,           \
                            true, false, false, false, false, 0, 12),          \
                                                                               \
    /* Transform statistics */                                                 \
    .TransformStat_p = &SAStatTest_Basic_Transform_Ingress,                    \
 }

Test_Case_Transform_t Transform_Ingress_Bypass_MACsec[] =
{
    TRANSFORM_INGRESS_BYPASS_MACSEC_1,
    TRANSFORM_INGRESS_BYPASS_MACSEC_2,
};


/* end of file test_vector_transform.c */
