/* test_record.h
 *
 * Test Tool for CfyE and SecY API's
 * Test Case Record format definition
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

#ifndef TEST_MACSEC_RECORD_H
#define TEST_MACSEC_RECORD_H

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Driver Framework Basic Defs API */
#include "basic_defs.h"

#include "api_secy.h"
#include "api_cfye.h"

/* SA Builder API */
#include "sa_builder_macsec.h"

/*----------------------------------------------------------------------------
 * Definitions and macros
 */

/* List of all the test cases ID's */
typedef enum
{
    TEST_MACSEC_TC_ID_KAT_1 = 1,
    TEST_MACSEC_TC_ID_KAT_2,
    TEST_MACSEC_TC_ID_KAT_3,
    TEST_MACSEC_TC_ID_KAT_4,
    TEST_MACSEC_TC_ID_KAT_5,
    TEST_MACSEC_TC_ID_LAST
} Test_Case_ID_t;

/* List of special operations to be performed during test, such as rekeying. */
typedef enum
{
    TEST_MACSEC_OP_NONE = 0,
    TEST_MACSEC_OP_REKEY,
    TEST_MACSEC_OP_REKEY_CHAINED,
    TEST_MACSEC_OP_REKEY_ADDSA,
    TEST_MACSEC_OP_UPDATE_PN,
    TEST_MACSEC_OP_REUSE_SA_VPORT,
    TEST_MACSEC_OP_MULTI_CHANNEL,
    TEST_MACSEC_OP_BYPASS_SA_MACSEC,
    TEST_MACSEC_OP_SA_RETIRE,
    TEST_MACSEC_OP_IPSEC,
    TEST_MACSEC_OP_VXLAN,
} Test_Case_Op_t;


typedef enum
{
    TEST_PKT_PROCESS_RULE_BYPASS = 0,     /* Bypass */
    TEST_PKT_PROCESS_RULE_DROP_CRC_ERROR, /* Drop, but bypass with CRC corruption signaling */
    TEST_PKT_PROCESS_RULE_DROP_PKT_ERROR, /* Drop, but bypass with bad packet indicator */
    TEST_PKT_PROCESS_RULE_DROP_INTERNAL   /* Drop internal by crypto-core (packet is not seen outside) */
} Test_Case_Packet_Process_Rule_t;


/* Test case configuration data */
typedef struct
{
    /* Device ID for which packet must be submitted */
    unsigned int DeviceId;

    /* Unique test case identifier */
    Test_Case_ID_t TestID;

    /* Wait timeout for one iteration, in milliseconds */
    unsigned int TimeoutMS;

    /* Maximum number of iterations (retries) */
    unsigned int RetryCount;

    /* Test duration time, in seconds */
    unsigned int TestDurationS;

    /* True when verbose trace information must be used */
    bool fVerbose;

    /* Test mode, true = ingress, false = egress */
    bool fIngress;

#if defined(TEST_IPSEC_ENABLE)
    /** Ingress Header EType - Global for device - Applicable only for IPsec Ingress */
    uint16_t IngressHdrEtype;
#endif

    /* --- SecY specifics --- */
    /* Default packet processing rule */
    Test_Case_Packet_Process_Rule_t DefaultProcessRule;

    /* The length of the bypass data during crypt-authenticate operation */
    unsigned int CryptAuthBypassLen;

    /* --- CfyE specifics --- */
    /* True when low-latency bypass on all channels must be used */
    bool fLowLatencyBypass;

    /* True when rule must be allocated by index (instead of just a free one). */
    bool fAllocateIndex;

    /* Number of channels, set to zero for hardware default. */
    unsigned int MaxChannelCount;

    /* Number of classification rules, set to zero for hardware default. */
    unsigned int MaxRuleCount;

    /* Number of vPorts, set to zero for hardware default. */
    unsigned int MaxvPortCount;

    /* Number of SCs, set to zero for hardware default. */
    unsigned int MaxSCCount;

    /* Number of SAs, set to zero for hardware default. */
    unsigned int MaxSACount;
} Test_Case_ConfParams_t;

/* Values to put in SeqNumLo field for Auth-enc transforms. */
#define AUTHENC_OP_AES_CTR 0
#define AUTHENC_OP_AES_GCM_ENC 1
#define AUTHENC_OP_AES_GCM_DEC 2

/* Transform data structure */
typedef struct
{
    /* vPort number to use */
    unsigned int vPort;

    /* SCI to use (8 bytes). */
    uint8_t *SCI_p;

    /* Association number to use */
    uint8_t AN;

    /* MACsec key */
    uint8_t *Key_p;

    /* Size of MACsec key in bytes. */
    unsigned int KeyByteCount;

    /* SSCI (ExtPN only) */
    uint8_t *SSCI_p;

    /* Salt (ExtPN only) */
    uint8_t *Salt_p;

    /* Sequence number */
    uint32_t SeqNumLo; /* Operation type for basic auth-enc */
    uint32_t SeqNumHi; /* ICVByteCount for basic auth-enc */

    /* Replay window size */
    uint32_t SeqMask;

    /** Security Parameter Index */
    uint32_t SPI;

    SABuilder_Operation_t operation;

    /* SA Builder flags */
    uint32_t flags;

    /* SA record data */
    SecY_SA_t SA_Data;

    /* Expected transform statistics data at the end of one test case, */
    /* when 0 the test tool will not do the transform statistics test */
    /* This must be either a pointer to SecY_SA_Stat_E_t */
    /* or to SecY_SA_Stat_I_t */
    void * TransformStat_p;
} Test_Case_Transform_t;

/* CfyE channel related data structure */
typedef struct
{
    /* Channel number */
    unsigned int ChannelID;

    /* General vPort Policy */
    CfyE_Device_t Settings;
} Test_Case_CfyE_Channel_t;

/* CfyE vPort related data structure */
typedef struct
{
    /* When true, the rule is used to update the rule specified with vPortId */
    /* otherwise (false) the vPort is installed. */
    bool fUpdate;

    /* vPort number (Id) used as a local vPort administration reference */
    /* When fUpdate is false, vPortId must be an unique number to identify the */
    /*                        vPort that is installed */
    /* When fUpdate is true, vPortId is used to lookup the vPort handle in the */
    /*                       administration with the installed vPorts */
    unsigned int vPortId;

    /* General vPort Policy */
    CfyE_vPort_t Policy;
} Test_Case_CfyE_vPort_t;

/* CfyE rule related data structure used for RuleAdd and RuleUpdate functionality */
typedef struct
{
    /* When true, the rule is used to update the rule specified with RuleId */
    /* otherwise (false) the rule is installed. */
    bool fUpdate;

    /* The RuleId is only used when fUpdate is true to indicate which rule */
    /* must be updated */
    /* RuleId used as a local rule administration reference */
    /* When fUpdate is false, RuleId must be an unique number to identify the */
    /*                        rule that is installed */
    /* When fUpdate is true, RuleId is used to lookup the rule handle in the */
    /*                       administration with the installed rules */
    unsigned int RuleId;

    /* Lookup rule */
    /* Note: */
    /* - channel and vPort are part of the rule */
    /* - The Rule.Policy.vPortHandle is mis-used, and it refers to the vPortId */
    /*   as defined in Test_Case_CfyE_vPort_t. This vPortId is used in the */
    /*   look-up in the vPort adminstration when adding or updating the rule. */
    CfyE_Rule_t Rule;
} Test_Case_CfyE_Rule_t;

typedef struct
{
    unsigned int MTT_Count; /* Number of MTT entries */

    CfyE_MTT_t *MTT_p;
} Test_Case_CfyE_MTT_t;

typedef struct
{
    /* Number of CfyE channel setting entries */
    /* The test tool will use the CfyE channel settings only when */
    /* CfyE_DeviceCount is not set to 0 */
    unsigned int CfyE_ChannelCount;

    /* Pointer to the array of Test_Case_CfyE_Channel_t data structures */
    Test_Case_CfyE_Channel_t * CfyE_ChannelData_p;

    /* Number of CfyE vPorts for packet processing */
    /* The test tool will use the CfyE vPorts data only when */
    /* CfyE_vPortCount is not set to 0 */
    unsigned int CfyE_vPortCount;

    /* Pointer to the array of Test_Case_CfyE_vPort_t data structures */
    Test_Case_CfyE_vPort_t * CfyE_vPortData_p;

    /* Number of CfyE rule entries for packet processing */
    /* The test tool will use the CfyE rule data only when */
    /* CfyE_RuleCount is not set to 0 */
    unsigned int CfyE_RuleCount;

    /* Pointer to the array of Test_Case_CfyE_Rule_t data structures */
    Test_Case_CfyE_Rule_t * CfyE_RuleData_p;

    /* Expected CfyE global notifications after the packet is processed: */
    /* event mask using CFYE_EVENT_STAT_* flags */
    /* Note: Make sure that the threshold is set via Test_Case_CfyE_Channel_t */
    uint32_t EventMaskGlobal;

    /* Expected CfyE chnannel notifications after the packet is processed: */
    /* event mask using CFYE_EVENT_CHAN_* flags */
    uint32_t EventMaskChannel;

    /* MTT data */
    Test_Case_CfyE_MTT_t *MTT_Data_p;
} Test_Case_CfyE_Data_t;

/* vPort related statistics structure */
typedef struct
{
    /* vPort number to use */
    unsigned int vPort;

    /* Expected SecY statistics */
    /* The test tool will do this test only when SecYStat_p is not set to NULL */
    SecY_SecY_Stat_t * SecYStat_p;

    /* Expected IFC/IFC1 statistics */
    /* The test tool will do this test only when IfcStat_p is not set to NULL */
    SecY_Ifc_Stat_t * IfcStat_p;
} Test_Case_vPortStat_t;


/* Classification rules data structure */
typedef struct
{
    /* Channel number/index to install the rule for */
    unsigned int Channel;

    /* SecTAG parsing and compare rules for each packet */
    SecY_Channel_Rule_SecTAG_t * SecTag_Rules_p;
} Test_Case_Channel_Rules_t;

typedef struct
{
    /* Secure Channel number/index to install the rule for */
    unsigned int SecureChannel;

    /* Egress MTU rules for each packet */
    SecY_SC_Rule_MTUCheck_t * MTU_Rules_p;
} Test_Case_SC_Rules_t;


/* Test packet data */
typedef struct
{
    /* MAC destination address */
    uint8_t * MAC_DA_p;

    /* MAC source address */
    uint8_t * MAC_SA_p;

    /* EtherType */
    uint16_t EtherType;

    /* SecTAG Offset (should be 12 as default) */
    unsigned int SecTAGOffset;

    /* Source packet size in bytes, */
    unsigned int SrcPkt_ByteCount;

    /* Source packet data */
    /* when 0 the test tool will generate a packet */
    uint8_t * SrcPkt_p;

    /* Index to the array of the Test_Case_Transform_t structures, */
    /* this packet will be bound to this transform. */
    /* the test tool will ignore this parameter is negative */
    int TransformIndex;

    /* Reserved, always set to 0 */
    uint32_t Reserved;

    /* Known Answer (expected test results) that will be use by the test tool */
    /* for comparison with the received result */

    /* Destination packet data length, */
    /* when 0 the test tool will not use it for comparison */
    uint32_t DstPkt_ByteCount;

    /* Destination packet data */
    /* when 0 the test tool will not use it for comparison */
    uint8_t * DstPkt_p;

    /* Expected SecY notifications after the packet is processed: */
    /* event mask using SECY_EVENT_* flags */
    uint32_t EventMask;

    /* expected SecY per-channel notifications. */
    /* event mask usint SECY_EVENT_* flasg */
    uint32_t ChannelEventMask;

    /* Channel on which the packet must be sent/received. */
    unsigned int ChannelID;

    /* vPort on which packet must be sent/received. */
    unsigned int vPort;

    /* Packet must be marked as control packet. */
    bool fControl;
} Test_Case_Packet_t;


/* General test case configuration data and test vectors record */
typedef struct
{
    /* Test case configuration data, cannot be 0 */
    Test_Case_ConfParams_t * ConfParams_p;

    /* Zero-terminated test case name */
    const char * szTestCaseName;

    /* Pointer to the Test_Case_CfyE_Data_t structure */
    /* The test tool will use the CfyE related data only when not NULL */
    Test_Case_CfyE_Data_t * CfyE_Data_p;

    /* Number of transforms for packet processing */
    /* The test tool will use the transforms only */
    /* when TransformCount is not set to 0 */
    unsigned int TransformCount;

    /* Pointer to the array of Test_Case_Transform_t data structures */
    Test_Case_Transform_t * TransformData_p;

    /* Number of packets for processing */
    /* The test tool will do this test only */
    /* when PacketCount is not set to 0 */
    unsigned int PacketCount;

    /* Pointer to the array of Test_Case_Packet_t data structures */
    Test_Case_Packet_t * PacketData_p;

    /* Number of Channel rules to install */
    unsigned int ChannelRulesCount;

    /* Pointer to the array with the Channel rules to install */
    Test_Case_Channel_Rules_t * ChannelRules_p;

    /* Number of Secure Channel rules to install */
    unsigned int SCRulesCount;

    /* Pointer to the array with the Secure Channel rules to install */
    Test_Case_SC_Rules_t * SCRules_p;

    /* Number of vPorts to check the Statistics for */
    unsigned int vPortStatistisCount;

    /* vPort related statistics */
    /* Note: The test tool will do this test only, when vPortStatistis_p */
    /*       is not set to NULL */
    Test_Case_vPortStat_t * vPortStatistis_p;

    /* Specify type of special operation, such as rekeying. */
    Test_Case_Op_t SpecialOperation;
} Test_Case_Record_t;


#endif /* TEST_MACSEC_RECORD_H */


/* end of file test_record.h */
