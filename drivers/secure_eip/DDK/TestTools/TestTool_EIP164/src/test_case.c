/* test_case.c
 *
 * Test Tool for CfyE and SecY API's
 * Implementation of the general test case functions
 *
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

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

#include "test_case.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Default configuration */
#include "c_test_macsec.h"

/* Test Case record format */
#include "test_record.h"

/* General test support internal interface */
#include "test_support.h"

/* CFYE API */
#include "api_cfye.h"

#ifdef TEST_MACSEC_USE_READ_API
/* CfyE extended API */
#include "api_cfye_ext.h"
#endif

/* SECY API */
#include "api_secy.h"

#ifdef TEST_MACSEC_USE_READ_API
/* SecY extended API */
#include "api_secy_ext.h"
#endif

/* SA Builder API */
#include "sa_builder_macsec.h"

/* AES callback function */
#include "aes.h"

/* Driver Framework Basic Definitions API */
#include "basic_defs.h"

/* Driver Framework C-Library Abstraction API */
#include "clib.h"

/* Logging API */
#include "log.h"

/* Packet I/O API */
#include "api_pktio.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

#ifdef TEST_MACSEC_DEBUG
#define TEST_MACSEC_DEBUG_EIP164_INT_STAT_OFF       0xF410
#define TEST_MACSEC_DEBUG_EIP201_EN_STAT_OFF        0xF810
#endif /* TEST_MACSEC_DEBUG */


/*----------------------------------------------------------------------------
 * Local variables
 */

#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
static volatile unsigned int SecY_GlobalNotificationsReceived = 0;
#ifdef SECY_CHANNEL_NOTIFY_NEEDED
static volatile unsigned int SecY_ChannelNotificationsReceived = 0;
#endif /* SECY_CHANNEL_NOTIFY_NEEDED */
#ifdef TEST_MACSEC_USE_CFYE
static volatile unsigned int CfyE_GlobalNotificationsReceived = 0;
static volatile unsigned int CfyE_ChannelNotificationsReceived = 0;
#endif /* TEST_MACSEC_USE_CFYE */
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */


#ifdef TEST_MACSEC_USE_READ_API
/* Exercise the Summary functions via SecY_Diag_Device_Dump(). */
#define TEST_MACSEC_SUMMARY_VIA_DIAG_API
#endif

#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
/*----------------------------------------------------------------------------
 * test_macsec_SecY_GlobalNotify
 */
static void
test_macsec_SecY_GlobalNotify(
        unsigned int Events)
{
    SecY_GlobalNotificationsReceived |= Events;

    Log_FormattedMessage("TEST_MACSEC: "
                         "Received SecY Global notification, events 0x%x\n",
                         Events);
}

#ifdef SECY_CHANNEL_NOTIFY_NEEDED
/*----------------------------------------------------------------------------
 * test_macsec_SecY_ChannelNotify
 */
static void
test_macsec_SecY_ChannelNotify(
        unsigned int Events)
{
    SecY_ChannelNotificationsReceived |= Events;

    Log_FormattedMessage("TEST_MACSEC: "
                         "Received SecY Channel notification, events 0x%x\n",
                         Events);
}
#endif /* SECY_CHANNEL_NOTIFY_NEEDED */

#ifdef TEST_MACSEC_USE_CFYE
/*----------------------------------------------------------------------------
 * test_macsec_CfyE_GlobalNotify
 */
static void
test_macsec_CfyE_GlobalNotify(
        unsigned int Events)
{
    CfyE_GlobalNotificationsReceived |= Events;

    Log_FormattedMessage("TEST_MACSEC: "
                         "Received CfyE Global notification, events 0x%x\n",
                         Events);
}

/*----------------------------------------------------------------------------
 * test_macsec_CfyE_ChannelNotify
 */
static void
test_macsec_CfyE_ChannelNotify(
        unsigned int Events)
{
    CfyE_ChannelNotificationsReceived |= Events;

    Log_FormattedMessage("TEST_MACSEC: "
                         "Received CfyE Channel notification, events 0x%x\n",
                         Events);
}
#endif /* TEST_MACSEC_USE_CFYE */
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */


/*----------------------------------------------------------------------------
 * test_macsec_configure_channel_default
 */
static void
test_macsec_configure_channel_default(
        SecY_Channel_t * const Channel_p,
        const unsigned int ChannelId,
        SecY_Settings_t * const Settings_p)
{
    Channel_p->ChannelId               = ChannelId;
    Channel_p->EtherType               = 0x88E5;
    Channel_p->RuleSecTAG.EtherType    = 0x88E5;
    Channel_p->RuleSecTAG.fCheckCE     = true;
    Channel_p->RuleSecTAG.fCheckKay    = true;
    Channel_p->RuleSecTAG.fCheckPN     = true;
    Channel_p->RuleSecTAG.fCheckSC     = true;
    Channel_p->RuleSecTAG.fCheckSL     = true;
    Channel_p->RuleSecTAG.fCheckV      = true;
    Channel_p->RuleSecTAG.fCompEType   = true;

    Channel_p->StatCtrl.SeqNrThreshold64.Lo = Settings_p->SeqNrThreshold64Lo;
    Channel_p->StatCtrl.SeqNrThreshold64.Hi = Settings_p->SeqNrThreshold64Hi;
    Channel_p->StatCtrl.SeqNrThreshold      = Settings_p->SeqNrThreshold;
}



/*----------------------------------------------------------------------------
 * test_macsec_sa_build
 *
 * Build a SA record from the supplied parameters.
 *
 * TransformParams_p (input)
 *      Transform parameters required to construct the SA.
 *
 * SARecord_pp (output)
 *      Location to store a pointer to the generated SA. NULL if no SA record
 *      is built. Thus function allocates space for the SA record, which
 *      must later be freed by the caller.
 *
 * SAWordCount_p (output)
 *      Location to store the SA Word Count.
 *
 * Return: true if successful, false otherwise.
 */
static bool
test_macsec_sa_build(
    const Test_Case_Transform_t * const TransformParams_p,
    void ** const SARecord_pp,
    unsigned int *  const SAWordCount_p)
{
    SABuilder_Params_t SAParams;
    SABuilder_Status_t rc;
    unsigned int SAWordCount;
    uint32_t *SABuffer_p;
    SABuilder_Direction_t direction = SAB_DIRECTION_EGRESS;
    SABuilder_Operation_t operation = SAB_OP_MACSEC;

    *SAWordCount_p = 0;

    switch (TransformParams_p->SA_Data.ActionType)
    {
    case SECY_SA_ACTION_EGRESS:
        direction = SAB_DIRECTION_EGRESS;
        break;

    case SECY_SA_ACTION_INGRESS:
        direction = SAB_DIRECTION_INGRESS;
        break;

#if defined(TEST_IPSEC_ENABLE)
    case SECY_SA_ACTION_IPSEC_EGRESS:
        direction = SAB_DIRECTION_EGRESS;
        break;

    case SECY_SA_ACTION_IPSEC_INGRESS:
        direction = SAB_DIRECTION_INGRESS;
        break;
#endif

    case SECY_SA_ACTION_CRYPT_AUTH:
        if (TransformParams_p->SeqNumLo == AUTHENC_OP_AES_GCM_DEC)
            direction = SAB_DIRECTION_INGRESS;
        else
            direction = SAB_DIRECTION_EGRESS;
        break;

    case SECY_SA_ACTION_BYPASS:
    case SECY_SA_ACTION_DROP:
        return true;
    default:
        return false;
    }

    rc = SABuilder_InitParams(&SAParams,
                              TransformParams_p->AN,
                              direction,
                              operation);
    if (rc != SAB_STATUS_OK)
    {
        LOG_CRIT("da_macsec_build_sa: SABuilder_InitParams error\n");
        return false;
    }

    if (TransformParams_p->SA_Data.ActionType == SECY_SA_ACTION_CRYPT_AUTH)
    {
        SAParams.ICVByteCount = TransformParams_p->SeqNumHi;
        switch (TransformParams_p->SeqNumLo)
        {
        case AUTHENC_OP_AES_CTR:
            SAParams.operation = SAB_OP_ENC_AES_CTR;
            break;
        case AUTHENC_OP_AES_GCM_ENC:
        case AUTHENC_OP_AES_GCM_DEC:
            SAParams.operation = SAB_OP_ENCAUTH_AES_GCM;
            break;
        }
    }

    SAParams.operation    = TransformParams_p->operation;
    SAParams.Salt_p       = TransformParams_p->Salt_p;
#if defined(TEST_IPSEC_ENABLE)
    SAParams.SPI          = TransformParams_p->SPI;
#endif
    SAParams.Key_p        = TransformParams_p->Key_p;
    SAParams.KeyByteCount = TransformParams_p->KeyByteCount;
    SAParams.SCI_p        = TransformParams_p->SCI_p;
    SAParams.SeqNumLo     = TransformParams_p->SeqNumLo;
    SAParams.WindowSize   = TransformParams_p->SeqMask;
    SAParams.flags        = TransformParams_p->flags;

    if (TransformParams_p->Salt_p)
    {
        if (SAB_OP_MACSEC == SAParams.operation)
            SAParams.flags |= SAB_MACSEC_FLAG_LONGSEQ;

        SAParams.Salt_p = TransformParams_p->Salt_p;
        SAParams.SSCI_p = TransformParams_p->SSCI_p;
        SAParams.SeqNumHi = TransformParams_p->SeqNumHi;
    }

    rc = SABuilder_GetSize(&SAParams, &SAWordCount);
    if (rc != SAB_STATUS_OK)
    {
        LOG_CRIT("test_macsec_sa_build: SABuilder_GetSize error\n");
        return false;
    }

    SABuffer_p = test_macsec_malloc(SAWordCount * sizeof(uint32_t));
    if (SABuffer_p == NULL)
    {
        LOG_CRIT("test_macsec_sa_build: memory allocation failure\n");
        return false;
    }

    rc = SABuilder_BuildSA(&SAParams, SABuffer_p, AES_Encrypt);
    if (rc != SAB_STATUS_OK)
    {
        test_macsec_free(SABuffer_p);
        LOG_CRIT("test_macsec_sa_build: error building SA\n");
        return false;
    }

    *SAWordCount_p = SAWordCount;
    *SARecord_pp = SABuffer_p;
    return true;
}


/*----------------------------------------------------------------------------
 * test_macsec_sa_copy
 */
void
test_macsec_sa_copy(
        const Test_Case_ConfParams_t * const TestConf_p,
        const SecY_SA_t * const SA_Input_p,
        const Test_Case_Transform_t * const TransformParams_p,
        Test_Transform_t * const Tr_Admin_p,
        SecY_SA_t * const SA_Output_p)
{
    IDENTIFIER_NOT_USED(TestConf_p);

    /* Copy input SA to output SA */
    memcpy(SA_Output_p, SA_Input_p, sizeof(SecY_SA_t));

    /* Override default with specifics */

    if (Tr_Admin_p->TransformRec_p == NULL)
    {
        unsigned int SAWordCount;
        if (!test_macsec_sa_build(TransformParams_p,
                                  &Tr_Admin_p->TransformRec_p,
                                  &SAWordCount))
        {
            return;
        }
        SA_Output_p->SA_WordCount = SAWordCount;
    }

    /* Point SA transform record to admin buffer */
    SA_Output_p->TransformRecord_p = Tr_Admin_p->TransformRec_p;

    /* Action type */
    if (SA_Input_p->ActionType == SECY_SA_ACTION_INGRESS)
    {
        /* SCI */
        SA_Output_p->Params.Ingress.SCI_p = TransformParams_p->SCI_p;

        /* AN */
        SA_Output_p->Params.Ingress.AN = TransformParams_p->AN;
    }
}


/*----------------------------------------------------------------------------
 * test_macsec_put_one
 */
bool
test_macsec_put_one(
        const Test_Case_ConfParams_t * const TestConf_p,
        const uint8_t * const Buffer_p,
        unsigned int ByteCount,
        unsigned int ChannelID,
        unsigned int vPort,
        unsigned int SecTAGOffset,
        bool fControl)
{
    int RetCode;
    PktIO_Packet_Status_In_t PktStatus;

    /* Fill in the status data structure */
    ZEROINIT(PktStatus);

    PktStatus.vPort        = vPort;
    PktStatus.SecTAGOffset = SecTAGOffset;

    if (fControl)
    {
        PktStatus.PacketStatusMask |= PKTIO_PACKET_CTRL_PKT;
    }

    /* Submit the packet */
    RetCode = PktIO_Packet_Put(Buffer_p,
                               ByteCount,
                               &PktStatus,
                               ChannelID,
                               TestConf_p->fIngress ?
                                   PKTIO_PACKET_DIRECTION_INGRESS :
                                   PKTIO_PACKET_DIRECTION_EGRESS);
    if (RetCode != 0)
    {
        LOG_CRIT("TEST_MACSEC: Failed, PktIO_Packet_Put()=%d\n",
                 RetCode);
        return false;
    }

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: PktIO_Packet_Put Size/StatusMask/"
                             "Channel/vPort/MACSAOffset/SecTAGOffset: "
                             "%d/0x%X/%d/%d/%d/%d\n",
                             ByteCount,
                             PktStatus.PacketStatusMask,
                             ChannelID,
                             PktStatus.vPort,
                             PktStatus.MACSAOffset,
                             PktStatus.SecTAGOffset);
    }

    return true;
}


/*----------------------------------------------------------------------------
 * test_macsec_get_one
 */
bool
test_macsec_get_one(
        const Test_Case_ConfParams_t * const TestConf_p,
        uint8_t * const Buffer_p,
        unsigned int * const ByteCount_p,
        unsigned int ChannelID)
{
    PktIO_Packet_Status_Out_t PktStatus;
    int LoopCounter = TestConf_p->RetryCount;

    /* Fill in the status data structure */
    ZEROINIT(PktStatus);

    while (LoopCounter > 0)
    {
        /* Try to get the processed packet from the driver */
        int RetCode = PktIO_Packet_Get(Buffer_p,
                                       ByteCount_p,
                                       &PktStatus,
                                       ChannelID,
                                       TestConf_p->fIngress ?
                                           PKTIO_PACKET_DIRECTION_INGRESS :
                                           PKTIO_PACKET_DIRECTION_EGRESS);
        if (RetCode != 0)
        {
            LOG_CRIT("TEST_MACSEC: Failed, PktIO_Packet_Get()=%d\n",
                 RetCode);
            return false;
        }

        if (*ByteCount_p > 0)
        {
            if (TestConf_p->fVerbose)
            {
                /* Check PacketStatusMask in case of CRC drop type, it should */
                /* indicate a CRC error */
                Log_FormattedMessage("TEST_MACSEC: PktIO_Packet_Get Size/"
                                     "StatusMask/Channel/vPort/SAIndex/SCIndex"
                                     "/RuleIndex: %d/0x%X/%d/%d/%d/%d/%d\n",
                                     *ByteCount_p,
                                     PktStatus.PacketStatusMask,
                                     ChannelID,
                                     PktStatus.vPort,
                                     PktStatus.SAIndex,
                                     PktStatus.SCIndex,
                                     PktStatus.RuleIndex);
            }

            return true;                /* packet is received */
        }

        /* Delay until next try */
        test_macsec_usleep(TestConf_p->TimeoutMS * 1000);

        LoopCounter--;
    }

    LOG_CRIT("TEST_MACSEC: Failed, Timeout reading packet\n");

    /* timeout, no result packet received */
    return false;
}


/*----------------------------------------------------------------------------
 * test_macsec_cmp_pkts
 */
bool
test_macsec_cmp_pkts(
        const void * Received_Pkt,
        const unsigned int Received_Bytecount,
        const void * Expected_Pkt,
        const unsigned int Expected_Bytecount)
{
    /* Compare the received packet with the expected. They must match. */
    if (Expected_Bytecount && (Received_Bytecount != Expected_Bytecount))
    {
        Log_FormattedMessage("TEST_MACSEC: Packet Byte Count "
                             "Expected=%d, Received=%d\n",
                             Expected_Bytecount,
                             Received_Bytecount);
        return false;
    }

    /* Compare the received packet data with the expected */
    if (Expected_Bytecount && Expected_Pkt &&
        (memcmp(Received_Pkt, Expected_Pkt, Received_Bytecount) != 0))
    {
        Log_FormattedMessage("TEST_MACSEC: Received packet data "
                             "differs from the expected\n");

        Log_HexDump("TEST_MACSEC: Expected packet data",
                    0,
                    Expected_Pkt,
                    Expected_Bytecount);

        return false;
    }

    return true;
}


/*----------------------------------------------------------------------------
 * test_macsec_device_init
 */
bool
test_macsec_device_init(
        const Test_Case_Record_t * const TestRec_p,
        unsigned int * const MaxChannelCount_p,
        unsigned int * const MaxvPortCount_p,
        unsigned int * const MaxSACount_p,
        unsigned int * const MaxSCCount_p,
        unsigned int * const MaxRuleCount_p)
{
    Test_Case_ConfParams_t * TestConf_p = TestRec_p->ConfParams_p;
    SecY_Settings_t Settings;
    unsigned int MaxChannels = 0;
    unsigned int MaxvPorts = 0;
#ifdef TEST_MACSEC_USE_CFYE
    unsigned int MaxCfyEChannels = 0;
    unsigned int MaxCfyEvPorts = 0;
    unsigned int MaxCfyERules = 0;

    /* CfyE initialization */
    if (TestRec_p->CfyE_Data_p != NULL)
    {
        CfyE_Status_t CfyE_Rc;
        CfyE_Role_t Role;
        CfyE_Init_t Settings;

        if (TestConf_p->fVerbose)
        {
            LOG_CRIT("TEST_MACSEC: Initializing CfyE\n");
        }

        Role = TestConf_p->fIngress ? CFYE_ROLE_INGRESS : CFYE_ROLE_EGRESS;

        ZEROINIT(Settings);
        Settings.fLowLatencyBypass = TestConf_p->fLowLatencyBypass;

        Settings.MaxChannelCount = TestConf_p->MaxChannelCount;
        Settings.MaxvPortCount = TestConf_p->MaxvPortCount;
        Settings.MaxRuleCount = TestConf_p->MaxRuleCount;

        Settings.fParsePktIPsec = true;

        CfyE_Rc = CfyE_Device_Init(TestConf_p->DeviceId, Role, &Settings);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("TEST_MACSEC: Failed, CfyE_Device_Init()=%d\n", CfyE_Rc);
            return false;
        }

        CfyE_Rc = CfyE_Device_Limits(TestConf_p->DeviceId,
                                     &MaxCfyEChannels,
                                     &MaxCfyEvPorts,
                                     &MaxCfyERules);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("TEST_MACSEC: Failed, CfyE_Device_Limits()=%d\n", CfyE_Rc);
            return false;
        }

        if (TestConf_p->fVerbose)
        {
            LOG_CRIT("TEST_MACSEC: CfyE initialization done, "
                     "max Channels/vPorts/Rules = %u/%u/%u\n",
                     MaxCfyEChannels, MaxCfyEvPorts, MaxCfyERules);
        }
    } /* CfyE initialization done */
#endif /* TEST_MACSEC_USE_CFYE */

    /* SecY initialization */
    {
        SecY_Status_t SecY_Rc;
        unsigned int TestMode;
        unsigned int MaxSAs = 0;
        unsigned int MaxSCs = 0;

        if (TestConf_p->fVerbose)
        {
            LOG_CRIT("TEST_MACSEC: Initializing SecY\n");
        }

        ZEROINIT(Settings);

        switch (TestConf_p->DefaultProcessRule)
        {
        default:
        case TEST_PKT_PROCESS_RULE_BYPASS:
            Settings.DropBypass.fBypass = true;
            break;
        case TEST_PKT_PROCESS_RULE_DROP_CRC_ERROR:
            Settings.DropBypass.DropType = SECY_SA_DROP_CRC_ERROR;
            break;
        case TEST_PKT_PROCESS_RULE_DROP_PKT_ERROR:
            Settings.DropBypass.DropType = SECY_SA_DROP_PKT_ERROR;
            break;
        case TEST_PKT_PROCESS_RULE_DROP_INTERNAL:
            Settings.DropBypass.DropType = SECY_SA_DROP_INTERNAL;
            break;
        }

        /* Set the triggers for CountSummary registers/notification events */
        /* See test_macsec_pkt_test() function for how it is used! */
        if ((TestRec_p->PacketData_p != NULL) &&
            (TestRec_p->PacketData_p->EventMask != 0))
        {
#ifdef TEST_MACSEC_MODE_EGRESS
            if ((TestRec_p->PacketData_p->EventMask & SECY_EVENT_PE_OB_SEQNR_THR) ||
                (TestRec_p->PacketData_p->EventMask & SECY_EVENT_SA_PN_THR))
            {
                if (TestRec_p->TransformCount >0 &&
                    TestRec_p->TransformData_p[0].Salt_p != NULL)
                {
                    /* For coverage purpose */
                    Settings.SeqNrThreshold64Lo = 1;
                }
                else
                {
                    Settings.SeqNrThreshold = 1;
                }
            }
#endif /* TEST_MACSEC_MODE_EGRESS */

            if ((TestRec_p->PacketData_p->EventMask & SECY_EVENT_ECC_ERR))
            {
                Settings.ECCCorrectableThr = 1;
                Settings.ECCUncorrectableThr = 1;
            }

#ifdef TEST_MACSEC_MODE_INGRESS
            if (TestRec_p->PacketData_p->EventMask & SECY_EVENT_STAT_RXCAM_THR)
            {
                Settings.RxCAMCountFrameThrLo = 1;
            }
#endif /* TEST_MACSEC_MODE_INGRESS */

            if (TestRec_p->PacketData_p->EventMask & SECY_EVENT_STAT_SA_THR)
            {
                Settings.SACountFrameThrLo = 1;
                Settings.SACountOctetThrLo = 1;
            }

            if (TestRec_p->PacketData_p->EventMask & SECY_EVENT_STAT_SECY_THR)
            {
                Settings.SecYCountFrameThrLo = 1;
            }

            if (TestRec_p->PacketData_p->EventMask & SECY_EVENT_STAT_IFC_THR)
            {
                Settings.IFCCountFrameThrLo = 1;
                Settings.IFCCountOctetThrLo = 1;
            }

            if (TestRec_p->PacketData_p->EventMask & SECY_EVENT_STAT_IFC1_THR)
            {
                Settings.IFC1CountFrameThrLo = 1;
                Settings.IFC1CountOctetThrLo = 1;
            }
        }

#if defined(TEST_MACSEC_MODE_EGRESS) && defined(TEST_MACSEC_MODE_INGRESS)
        TestMode = SECY_ROLE_EGRESS_INGRESS;
#else
        TestMode = TestConf_p->fIngress ? SECY_ROLE_INGRESS : SECY_ROLE_EGRESS;
#endif /* TEST_MACSEC_MODE_EGRESS && TEST_MACSEC_MODE_INGRESS */

        Settings.MaxChannelCount = TestConf_p->MaxChannelCount;
        Settings.MaxvPortCount = TestConf_p->MaxvPortCount;
        Settings.MaxSCCount = TestConf_p->MaxSCCount;
        Settings.MaxSACount = TestConf_p->MaxSACount;

#if defined(TEST_IPSEC_ENABLE)
        Settings.IngressHdrEtype = TestRec_p->ConfParams_p->IngressHdrEtype;
#endif

        SecY_Rc = SecY_Device_Init(TestConf_p->DeviceId, TestMode, &Settings);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("TEST_MACSEC: Failed, SecY_Device_Init()=%d\n", SecY_Rc);
            return false;
        }

        SecY_Rc = SecY_Device_Limits(TestConf_p->DeviceId,
                                     &MaxChannels, &MaxvPorts,
                                     &MaxSAs, &MaxSCs);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("TEST_MACSEC: Failed, SecY_Device_Limits()=%d\n",
                     SecY_Rc);
            return false;
        }

        if (TestConf_p->fVerbose)
        {
            LOG_CRIT("TEST_MACSEC: SecY initialization done, "
                     "max Channels/vPorts/SAs/SCs = %u/%u/%u/%u\n",
                     MaxChannels, MaxvPorts, MaxSAs, MaxSCs);
        }

#ifdef TEST_MACSEC_USE_CFYE
        if (TestRec_p->CfyE_Data_p != NULL)
        {
            if (MaxCfyEChannels > MaxChannels)
            {
                LOG_CRIT("TEST_MACSEC: Warning, CfyE Channels > SecY Channels\n");
            }
            else if (MaxCfyEChannels < MaxChannels)
            {
                LOG_CRIT("TEST_MACSEC: Warning, CfyE Channels < SecY Channels\n");
                MaxChannels = MaxCfyEChannels;
            }

            if (MaxCfyEvPorts > MaxvPorts)
            {
                LOG_CRIT("TEST_MACSEC: Warning, CfyE vPorts > SecY vPorts\n");
            }
            else if (MaxCfyEvPorts < MaxvPorts)
            {
                LOG_CRIT("TEST_MACSEC: Warning, CfyE vPorts < SecY vPorts\n");
                MaxvPorts = MaxCfyEvPorts;
            }
        }
        if (MaxRuleCount_p)
        {
            *MaxRuleCount_p = MaxCfyERules;
        }
#else
        if (MaxRuleCount_p)
        {
            *MaxRuleCount_p = 0;
        }
#endif /* TEST_MACSEC_USE_CFYE */
        if (MaxChannelCount_p)
        {
            *MaxChannelCount_p = MaxChannels;
        }
        if (MaxvPortCount_p)
        {
            *MaxvPortCount_p = MaxvPorts;
        }
        if (MaxSACount_p)
        {
            *MaxSACount_p = MaxSAs;
        }
        if (MaxSCCount_p)
        {
            *MaxSCCount_p = MaxSCs;
        }
    }                                   /* SecY initialization done */

    /* Channel initialization */
    {
        SecY_Status_t SecY_Rc;
        SecY_ChannelConf_t ChConf;
        SecY_Channel_t *ChParams_p;
        unsigned int i;

        ZEROINIT(ChConf);

        ChParams_p = test_macsec_malloc(MaxChannels * sizeof(SecY_Channel_t));
        if (ChParams_p == NULL)
        {
            LOG_CRIT("test_macsec_device_init: failed to alllocate channel parameters\n");
            return false;
        }
        memset(ChParams_p, 0, MaxChannels * sizeof(SecY_Channel_t));

        ChConf.Params.Channel_p = ChParams_p;
        ChConf.Params.ChannelCount = MaxChannels;

        if (TestConf_p->fVerbose)
        {
            LOG_CRIT("TEST_MACSEC: Initializing channels\n");
        }

        for (i = 0; i < MaxChannels; i++)
        {
            test_macsec_configure_channel_default(&ChParams_p[i],
                                                  i,
                                                  &Settings);
        }

#if defined(TEST_IPSEC_ENABLE)
        if (TestRec_p->TransformData_p != NULL &&
            SAB_OP_IPSEC == TestRec_p->TransformData_p->operation)
        {
            ChConf.Params.Channel_p->fIPsec = true;
        }
        else
        {
            ChConf.Params.Channel_p->fIPsec = false;
        }
#endif

        SecY_Rc = SecY_Channel_Config_Set(TestConf_p->DeviceId, &ChConf);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("TEST_MACSEC: Failed, SecY_Channel_Config_Set()=%d\n",
                     SecY_Rc);
            test_macsec_free(ChParams_p);
            return false;
        }

        if (TestConf_p->fVerbose)
        {
            LOG_CRIT("TEST_MACSEC: Channels initialized successfully\n");
        }
        test_macsec_free(ChParams_p);
    }                                   /* Channel initialization done */

    return true;
}


/*----------------------------------------------------------------------------
 * test_macsec_device_uninit
 */
void
test_macsec_device_uninit(
        const Test_Case_Record_t * const TestRec_p)
{
    Test_Case_ConfParams_t * TestConf_p = TestRec_p->ConfParams_p;

    /* SecY un-initialization */
    {
        SecY_Device_Uninit(TestConf_p->DeviceId);

        if (TestConf_p->fVerbose)
        {
            LOG_CRIT("TEST_MACSEC: SecY un-initialization done\n");
        }
    }

#ifdef TEST_MACSEC_USE_CFYE
    /* CfyE un-initialization */
    if (TestRec_p->CfyE_Data_p != NULL)
    {
        CfyE_Device_Uninit(TestConf_p->DeviceId);

        if (TestConf_p->fVerbose)
        {
            LOG_CRIT("TEST_MACSEC: CfyE un-initialization done\n");
        }
    }
#endif /* TEST_MACSEC_USE_CFYE */
}


/*----------------------------------------------------------------------------
 * test_macsec_transform_install
 */
bool
test_macsec_transform_install(
        const Test_Case_ConfParams_t * TestConf_p,
        const Test_Case_Record_t * TestRec_p,
        const unsigned int TransformStartIndex,
        const unsigned int NumberOfTransforms,
        Test_Transform_t ** Tr_Admin_pp)
{
    unsigned int i;
    SecY_Status_t SecY_Rc;
    SecY_SA_t SA_Params;
    Test_Transform_t * Tr_Admin_p;
    Test_Case_Transform_t * TC_Transform_p;

    if ((NumberOfTransforms == 0) ||
        ((TransformStartIndex + NumberOfTransforms) > TestRec_p->TransformCount))
    {
        LOG_CRIT("TEST_MACSEC: Failed, Invalid transform reference\n");
        return false;
    }

    /* Allocate an array for transform admin record */
    *Tr_Admin_pp = test_macsec_malloc(NumberOfTransforms *
                                      sizeof(Test_Transform_t));
    if (*Tr_Admin_pp == 0)
    {
        LOG_CRIT("TEST_MACSEC: Failed, Transform admin memory allocation\n");
        return false;
    }
    Tr_Admin_p = *Tr_Admin_pp;

    /* Initialize to 0 */
    memset(Tr_Admin_p, 0, NumberOfTransforms * sizeof(Test_Transform_t));

    /* Add SAs one by one */
    TC_Transform_p = &TestRec_p->TransformData_p[TransformStartIndex];
    for (i = 0; i < NumberOfTransforms; i++)
    {
        SecY_SA_t *SA_Input_p = &TC_Transform_p->SA_Data;

        ZEROINIT(SA_Params);

        /* Copy SA data */
        {
            test_macsec_sa_copy(TestConf_p,
                                SA_Input_p,
                                TC_Transform_p,
                                &Tr_Admin_p[i],
                                &SA_Params);
        }

        /* Add this SA */
        SecY_Rc = SecY_SA_Add(TestConf_p->DeviceId,
                              TC_Transform_p->vPort,
                              &(Tr_Admin_p[i].TransformHandle),
                              &SA_Params);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Add()=%d\n", SecY_Rc);
            return false;
        }
        SecY_Rc = SecY_SAIndex_Get(Tr_Admin_p[i].TransformHandle,
                                   &Tr_Admin_p[i].SAIndex,
                                   NULL);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("TEST_MACSEC: Failed, SecY_SAIndex_Get()=%d\n", SecY_Rc);
            return false;
        }

#ifdef TEST_MACSEC_MODE_INGRESS
        /* Verify that ingress SA is installed correctly. */
        if (SA_Params.ActionType == SECY_SA_ACTION_INGRESS)
        {
            SecY_SAHandle_t SAHandles[4];
            SecY_Rc = SecY_SA_Active_I_Get(TestConf_p->DeviceId,
                                           TC_Transform_p->vPort,
                                           TC_Transform_p->SCI_p,
                                           SAHandles);
            if (SecY_Rc != SECY_STATUS_OK)
            {
                LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Active_I_Get()=%d\n", SecY_Rc);
                return false;
            }
            if (!SecY_SAHandle_IsSame(&SAHandles[TC_Transform_p->AN],
                                      &(Tr_Admin_p[i].TransformHandle)))
            {
                LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Active_I_Get() returned wrong SA\n");
                return false;
            }

        }
#endif
#ifdef TEST_MACSEC_MODE_EGRESS
        if (SA_Params.ActionType == SECY_SA_ACTION_EGRESS)
        {
            SecY_SAHandle_t SAHandle;
            SecY_Rc = SecY_SA_Active_E_Get(TestConf_p->DeviceId,
                                           TC_Transform_p->vPort,
                                           &SAHandle);
            if (SecY_Rc != SECY_STATUS_OK)
            {
                LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Active_E_Get()=%d\n", SecY_Rc);
                return false;
            }
            if (!SecY_SAHandle_IsSame(&SAHandle,
                                      &(Tr_Admin_p[i].TransformHandle)))
            {
                LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Active_I_Get() returned wrong SA\n");
                return false;
            }
        }
#endif
        /* Read SA to check */
        if (SA_Input_p->SA_WordCount > 0)
        {
            SecY_Status_t SecY_Rc;
            uint32_t * TrRecRead_p;
            unsigned int TrRec_Size;
            bool fReadTrRecFailed = false;

            /* Allocate the temporary buffer to save transform record data */
            TrRec_Size = SA_Input_p->SA_WordCount * sizeof(uint32_t);
            TrRecRead_p = test_macsec_malloc(TrRec_Size);
            if (TrRecRead_p == 0)
            {
                LOG_CRIT("TEST_MACSEC: Failed, Transform record allocation\n");
                fReadTrRecFailed = true;
                goto read_sa_done;
            }

            /* Read out transform record data */
            SecY_Rc = SecY_SA_Read(TestConf_p->DeviceId,
                                   Tr_Admin_p[i].TransformHandle,
                                   0,
                                   SA_Input_p->SA_WordCount,
                                   TrRecRead_p);
            if (SecY_Rc != SECY_STATUS_OK)
            {
                LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Read()=%d\n",
                         SecY_Rc);
                fReadTrRecFailed = true;
                goto read_sa_done;
            }

            /* Exclude SA update control word from check. */
            if (TrRec_Size == 24 * sizeof(uint32_t))
                TrRec_Size -= 4;
            /* Check if it is correctly installed */
            if (memcmp(Tr_Admin_p[i].TransformRec_p, TrRecRead_p, TrRec_Size))
            {
                LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Read() result compare\n");
                fReadTrRecFailed = true;
                goto read_sa_done;
            }

read_sa_done:
            /* Free the memory allocated */
            test_macsec_free(TrRecRead_p);
            if (fReadTrRecFailed)
            {
                return false;
            }
        }

        /* Check SA handle and index */
        if (!SecY_SAHandle_SAIndex_IsSame(Tr_Admin_p[i].TransformHandle,
                                          (TransformStartIndex + i)))
        {
            LOG_CRIT("TEST_MACSEC: Failed, SecY_SAHandle_SAIndex_IsSame(), "
                     "unknown SA index for SA handle %p\n",
                     Tr_Admin_p[i].TransformHandle.p);
            return false;
        }

        if (TestConf_p->fVerbose)
        {
            Log_FormattedMessage("TEST_MACSEC: "
                                 "Transform 32-bit word count %d\n",
                                 SA_Params.SA_WordCount);
            Log_HexDump32("TEST_MACSEC: Transform data",
                        0,
                        SA_Params.TransformRecord_p,
                        SA_Params.SA_WordCount);
        }

        if (TestConf_p->fVerbose)
        {
            Log_FormattedMessage("TEST_MACSEC: Transform Record added\n");
        }

        TC_Transform_p++; /* Next transform */
    }

    return true; /* success */
}


/*----------------------------------------------------------------------------
 * test_macsec_single_transform_update
 */
bool
test_macsec_single_transform_update(
        const Test_Case_ConfParams_t * const TestConf_p,
        const Test_Case_Transform_t * const TestTransform_p,
        Test_Transform_t * Tr_Admin_p)
{
    SecY_Status_t SecY_Rc;
    SecY_SA_t SA_Params;

    ZEROINIT(SA_Params);

    if ((Tr_Admin_p == NULL) || (Tr_Admin_p->TransformRec_p == NULL))
    {
        LOG_CRIT("TEST_MACSEC: Invalid transform handle\n");
        return false;
    }

    /* Copy SA data */
    test_macsec_sa_copy(TestConf_p,
                        &TestTransform_p->SA_Data,
                        TestTransform_p,
                        Tr_Admin_p,
                        &SA_Params);

    /* Update SA */
    SecY_Rc = SecY_SA_Update(TestConf_p->DeviceId,
                             Tr_Admin_p->TransformHandle,
                             &SA_Params);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Update()=%d\n", SecY_Rc);
        return false;
    }

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Transform 32-bit word count %d\n",
                             SA_Params.SA_WordCount);
        Log_HexDump32("TEST_MACSEC: Transform data",
                    0,
                    SA_Params.TransformRecord_p,
                    SA_Params.SA_WordCount);
    }

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Transform Record updated\n");
    }

    return true;
}


/*----------------------------------------------------------------------------
 * test_macsec_transform_nextpn_update
 */
bool
test_macsec_transform_nextpn_update(
        const Test_Case_ConfParams_t * TestConf_p,
        Test_Transform_t * TR_Admin_p,
        uint32_t NextPN_Lo,
        uint32_t NextPN_Hi,
        uint32_t SeqMask)
{
    SecY_Status_t SecY_Rc;
    bool fNextPNWritten;
    uint32_t SeqNumNew[2],SeqNumOld[2];
    uint32_t SeqMaskNew;
    bool fExtPN;
    bool fExpectChange;

    /* Read sequence number from transform record data */
    SecY_Rc = SecY_SA_NextPN_Get(TestConf_p->DeviceId,
                                 TR_Admin_p[0].TransformHandle,
                                 &SeqNumOld[0],
                                 &SeqNumOld[1],
                                 &fExtPN);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Read()=%d\n", SecY_Rc);
        return false;
    }

    if (fExtPN)
    {
        Log_FormattedMessage("TEST_MACSEC: SA SequenceNumber is %x:%x\n",
                             SeqNumOld[0], SeqNumOld[1]);
        fExpectChange = (NextPN_Hi > SeqNumOld[1] ||
                         (NextPN_Hi == SeqNumOld[1] && NextPN_Lo > SeqNumOld[0]));
    }
    else
    {
        Log_FormattedMessage("TEST_MACSEC: SA SequenceNumber is %x\n",
                             SeqNumOld[0]);
        fExpectChange = (NextPN_Lo > SeqNumOld[0]);
    }

    SecY_Rc = SecY_SA_NextPN_Update(TestConf_p->DeviceId,
                                    TR_Admin_p[0].TransformHandle,
                                    NextPN_Lo,
                                    NextPN_Hi,
                                    &fNextPNWritten);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_NextPN_Update()=%d\n", SecY_Rc);
        return false;
    }

    SecY_Rc = SecY_SA_WindowSize_Update(TestConf_p->DeviceId,
                                        TR_Admin_p[0].TransformHandle,
                                        SeqMask);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        LOG_CRIT("TEST_MACSEC: Failed SecY_SA_WindowSize_Update()=%d\n",
                 SecY_Rc);
        return false;
    }

    /* Read sequence number transform record data */
    SecY_Rc = SecY_SA_NextPN_Get(TestConf_p->DeviceId,
                                 TR_Admin_p[0].TransformHandle,
                                 &SeqNumNew[0],
                                 &SeqNumNew[1],
                                 &fExtPN);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Read()=%d\n", SecY_Rc);
        return false;
    }

    if (fExtPN)
    {
        Log_FormattedMessage("TEST_MACSEC: New SA SequenceNumber is %x:%x\n",
                             SeqNumNew[0], SeqNumNew[1]);
    }
    else
    {
        Log_FormattedMessage("TEST_MACSEC: New SA SequenceNumber is %x\n",
                             SeqNumNew[0]);
    }
    if (fNextPNWritten)
    {
        Log_FormattedMessage("TEST_MACSEC: NextPN was changed\n");
        /* Check that the transform record was indeed updated. */
        if (NextPN_Lo != SeqNumNew[0])
        {
            return false;
        }
        if (!fExpectChange)
        {
            return false;
        }
    }
    else
    {
        Log_FormattedMessage("TEST_MACSEC: NextPN was NOT changed\n");
        /* Check that the transform record was indeed unchanged. */
        if (SeqNumOld[0] != SeqNumNew[0])
        {
            return false;
        }
        if (fExpectChange)
        {
            return false;
        }
    }

    /* Read sequence number transform record data */
    SecY_Rc = SecY_SA_WindowSize_Get(TestConf_p->DeviceId,
                                  TR_Admin_p[0].TransformHandle,
                                  &SeqMaskNew);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Read()=%d\n", SecY_Rc);
        return false;
    }

    if (SeqMaskNew != SeqMask)
    {
        LOG_CRIT("TEST_MACSEC: SeqMask was not changed\n");
        return false;
    }

    return true;
}

/*----------------------------------------------------------------------------
 * test_macsec_transform_uninstall
 */
bool
test_macsec_transform_uninstall(
        const Test_Case_ConfParams_t * TestConf_p,
        const unsigned int NumberOfTransforms,
        Test_Transform_t * Tr_Admin_p)
{
    bool fSuccess = true;

    if (Tr_Admin_p != NULL)
    {
        Test_Transform_t * Transform_p = Tr_Admin_p;
        unsigned int i;

        for (i = 0; i < NumberOfTransforms; i++)
        {
            if (!SecY_SAHandle_IsSame(&Transform_p->TransformHandle,
                                      &SecY_SAHandle_NULL))
            {
                SecY_Status_t SecY_Rc;

                /* Remove the transform record */
                SecY_Rc = SecY_SA_Remove(TestConf_p->DeviceId,
                                         Transform_p->TransformHandle);
                if (SecY_Rc != SECY_STATUS_OK)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Remove()=%d\n", SecY_Rc);
                    fSuccess = false;
                }
                else if (TestConf_p->fVerbose)
                {
                    Log_FormattedMessage("TEST_MACSEC: Transform removed\n");
                }

                /* Set transform record handle to null */
                Transform_p->TransformHandle = SecY_SAHandle_NULL;
            }

            /* Release the Transform Record buffer */
            if (Transform_p->TransformRec_p)
            {
                test_macsec_free(Transform_p->TransformRec_p);
                if (TestConf_p->fVerbose)
                {
                    Log_FormattedMessage("TEST_MACSEC: Transform Record "
                                         "buffer freed\n");
                }
            }

            Transform_p++;
        }

        /* Release transform admin buffer allocated */
        test_macsec_free(Tr_Admin_p);
    }

    return fSuccess;
}


/*----------------------------------------------------------------------------
 * test_macsec_pkt_sanity_check
 */
bool
test_macsec_pkt_sanity_check(
        const Test_Case_ConfParams_t * TestConf_p,
        const Test_Case_Record_t * TestRec_p)
{
    unsigned int i;
    Test_Case_Packet_t * Packet_p = TestRec_p->PacketData_p;

    IDENTIFIER_NOT_USED(TestConf_p);

    for (i = 0; i < TestRec_p->PacketCount; i++)
    {
        if ((Packet_p == 0) ||
            (Packet_p->SrcPkt_ByteCount == 0) ||
            (Packet_p->SrcPkt_p == 0))
        {
            LOG_CRIT("TEST_MACSEC: Failed, "
                     "Test Case Record packet data sanity check\n");
            return false;
        }

        Packet_p++;
    }

    return true;
}


/*----------------------------------------------------------------------------
 * test_macsec_pkt_alloc
 */
bool
test_macsec_pkt_alloc(
        const Test_Case_Record_t * TestRec_p,
        Test_Packet_t ** PKT_Admin_pp)
{
    unsigned int i;
    Test_Packet_t * Packet_p;

    if (TestRec_p->PacketCount == 0)
    {
        LOG_CRIT("TEST_MACSEC: Failed, No Packets to allocate\n");
        return false;
    }

    Packet_p = test_macsec_malloc(TestRec_p->PacketCount * sizeof(Test_Packet_t));
    if (Packet_p == 0)
    {
        LOG_CRIT("TEST_MACSEC: Failed, Packet admin allocation\n");
        return false;
    }

    *PKT_Admin_pp = Packet_p;
    memset(Packet_p, 0, TestRec_p->PacketCount * sizeof(Test_Packet_t));

    for (i = 0; i < TestRec_p->PacketCount; i++)
    {
        unsigned int SrcSize, DstSize;

        /* Allocate source packet buffer */
        SrcSize = TestRec_p->PacketData_p[i].SrcPkt_ByteCount;
        DstSize = TestRec_p->PacketData_p[i].DstPkt_ByteCount;
        if (SrcSize == 0)
        {
            LOG_CRIT("TEST_MACSEC: Failed, Source packet buffer size %u\n",
                     SrcSize);
            return false;
        }

        Packet_p->SrcPkt_p = test_macsec_malloc(SrcSize);
        if (Packet_p->SrcPkt_p == NULL)
        {
            LOG_CRIT("TEST_MACSEC: Failed, Source packet buffer (size %d) "
                     "allocation\n",
                     SrcSize);
            return false;
        }

        Packet_p->SrcPkt_ByteCount = SrcSize;
        Packet_p->DstPkt_ByteCount = DstSize;

        /* Determine destination packet buffer size to allocate */
        /* Note add 32 bytes to prevent possible buffer overflow on read (egress) */
        DstSize = MAX(SrcSize, DstSize) + 32;

        /* Allocate a destination packet buffer */
        Packet_p->DstPkt_p = test_macsec_malloc(DstSize);
        if (Packet_p->DstPkt_p == NULL)
        {
            LOG_CRIT("TEST_MACSEC: Failed, Destination packet buffer (size %d)"
                     " allocation\n",
                     DstSize);
            return false;
        }

        Packet_p++;
    }

    return true;
}


/*----------------------------------------------------------------------------
 * test_macsec_pkt_free
 */
bool
test_macsec_pkt_free(
        const Test_Case_Record_t * TestRec_p,
        Test_Packet_t * PKT_Admin_p)
{
    if (PKT_Admin_p != NULL)
    {
        unsigned int i;

        for (i = 0; i < TestRec_p->PacketCount; i++)
        {
            /* Free source packet buffers */
            if (PKT_Admin_p[i].SrcPkt_p != NULL)
            {
                test_macsec_free(PKT_Admin_p[i].SrcPkt_p);
            }

            /* Free destination packet buffers */
            if (PKT_Admin_p[i].DstPkt_p != NULL)
            {
                test_macsec_free(PKT_Admin_p[i].DstPkt_p);
            }
        }

        if (PKT_Admin_p)
        {
            test_macsec_free(PKT_Admin_p);
        }
    }

    return true;
}


/*----------------------------------------------------------------------------
 * test_macsec_pkt_test
 */
bool
test_macsec_pkt_test(
        const Test_Case_ConfParams_t * TestConf_p,
        const Test_Case_Record_t * TestRec_p,
        const unsigned int StartPacketIndex,
        const unsigned int NumberOfPackets,
        Test_Packet_t * PKT_Admin_p,
        unsigned int ChannelCount)
{
    unsigned int i;
    Test_Case_Packet_t * Pkt_p;
    Test_Packet_t * PktAdmin_p;
    unsigned int SecY_GlobalEventsToProcess;
    unsigned int SecY_ChannelEventsToProcess;
    SecY_Status_t SecY_Rc;
#ifdef TEST_MACSEC_USE_CFYE
    unsigned int CfyE_GlobalEventsToProcess;
    unsigned int CfyE_ChannelEventsToProcess;
    CfyE_Status_t CfyE_Rc;
    unsigned int MaxCfyEChannels;
#endif /* TEST_MACSEC_USE_CFYE */

    if ((TestRec_p->PacketData_p == NULL) ||
        (PKT_Admin_p == NULL) ||
        (NumberOfPackets == 0) ||
        ((StartPacketIndex + NumberOfPackets) > TestRec_p->PacketCount))
    {
        LOG_CRIT("TEST_MACSEC: Failed, Missing data for packet test\n");
        return false;
    }

#ifdef TEST_MACSEC_USE_CFYE
    if (TestRec_p->CfyE_Data_p != NULL)
    {
        CfyE_Rc = CfyE_Device_Limits(TestConf_p->DeviceId,
                                     &MaxCfyEChannels, NULL, NULL);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("TEST_MACSEC: Failed, CfyE_Device_Limits()=%d\n", CfyE_Rc);
            return false;
        }
    }
#endif

    Pkt_p = &TestRec_p->PacketData_p[StartPacketIndex];
    PktAdmin_p = &PKT_Admin_p[StartPacketIndex];
    for (i = 0; i < NumberOfPackets; i++)
    {
        unsigned int ByteCount;

        /* Copy the packet data to the allocated packet buffer */
        memcpy(PktAdmin_p->SrcPkt_p, Pkt_p->SrcPkt_p, Pkt_p->SrcPkt_ByteCount);

        if (TestConf_p->fVerbose)
        {
            Log_FormattedMessage("TEST_MACSEC: Process packet of size %d\n",
                                 Pkt_p->SrcPkt_ByteCount);
            Log_HexDump("TEST_MACSEC: Submitted packet data",
                        0,
                        PktAdmin_p->SrcPkt_p,
                        Pkt_p->SrcPkt_ByteCount);
        }

        /* Initialize notification variables */
        SecY_GlobalEventsToProcess = TestRec_p->PacketData_p->EventMask;
        SecY_ChannelEventsToProcess = TestRec_p->PacketData_p->ChannelEventMask;
        if (SecY_GlobalEventsToProcess != 0 ||
            SecY_ChannelEventsToProcess != 0)
        {
#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
            /* Request SecY notification events */
            SecY_GlobalNotificationsReceived = 0;
            if (SecY_GlobalEventsToProcess != 0)
            {
                SecY_Notify_t Notify;

                ZEROINIT(Notify);

                Notify.fGlobal   = true;
                Notify.EventMask = SecY_GlobalEventsToProcess;
                Notify.CBFunc_p  = test_macsec_SecY_GlobalNotify;

                SecY_Rc = SecY_Notify_Request(TestConf_p->DeviceId, &Notify);
                if (SecY_Rc != SECY_STATUS_OK)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, "
                             "SecY_Notify_Request(G)=%d\n",
                             SecY_Rc);
                    return false;
                }
            }
#ifdef SECY_CHANNEL_NOTIFY_NEEDED
            SecY_ChannelNotificationsReceived = 0;
            if (SecY_ChannelEventsToProcess != 0)
            {
                SecY_Notify_t Notify;

                ZEROINIT(Notify);

                Notify.fGlobal   = false;
                Notify.ChannelId = Pkt_p->ChannelID;
                Notify.EventMask = SecY_ChannelEventsToProcess;
                Notify.CBFunc_p  = test_macsec_SecY_ChannelNotify;

                SecY_Rc = SecY_Notify_Request(TestConf_p->DeviceId, &Notify);
                if (SecY_Rc != SECY_STATUS_OK)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, "
                             "SecY_Notify_Request(C)=%d\n",
                             SecY_Rc);
                    return false;
                }
            }
#endif /* SECY_CHANNEL_NOTIFY_NEEDED */

#ifdef TEST_MACSEC_DEBUG
            test_macsec_debug_read32(TEST_MACSEC_DEBUG_DEVICE_NAME,
                                     TEST_MACSEC_DEBUG_EIP164_INT_STAT_OFF);
#endif /* TEST_MACSEC_DEBUG */

            if (TestConf_p->fVerbose)
            {
                Log_FormattedMessage("TEST_MACSEC: SecY notifications enabled,"
                                     " mask = 0x%x\n",
                                     SecY_GlobalEventsToProcess);
            }
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */
        }

#ifdef TEST_MACSEC_USE_CFYE
        if ((TestRec_p->CfyE_Data_p != NULL) &&
            ((TestRec_p->CfyE_Data_p->EventMaskGlobal != 0) ||
             (TestRec_p->CfyE_Data_p->EventMaskChannel != 0)))
        {
            /* Initialize notification variables */
            CfyE_GlobalEventsToProcess  = TestRec_p->CfyE_Data_p->EventMaskGlobal;
            CfyE_ChannelEventsToProcess = TestRec_p->CfyE_Data_p->EventMaskChannel;

#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
            CfyE_GlobalNotificationsReceived = 0;
            if (CfyE_GlobalEventsToProcess != 0)
            {
                CfyE_Notify_t Notify;

                ZEROINIT(Notify);

                Notify.fGlobal   = true;
                Notify.EventMask = CfyE_GlobalEventsToProcess;
                Notify.CBFunc_p  = test_macsec_CfyE_GlobalNotify;

                LOG_CRIT("TEST_MACSEC: global event mask 0x%08x notification "
                         "requested at device %d\n",
                         Notify.EventMask,
                         TestConf_p->DeviceId);
                CfyE_Rc = CfyE_Notify_Request(TestConf_p->DeviceId, &Notify);
                if (CfyE_Rc != CFYE_STATUS_OK)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, "
                             "CfyE_Notify_Request(G)=%d\n",
                             CfyE_Rc);
                    return false;
                }
            }

            CfyE_ChannelNotificationsReceived = 0;
            if (CfyE_ChannelEventsToProcess != 0)
            {
                CfyE_Notify_t Notify;

                ZEROINIT(Notify);

                Notify.ChannelId = Pkt_p->ChannelID;
                Notify.EventMask = CfyE_ChannelEventsToProcess;
                Notify.CBFunc_p  = test_macsec_CfyE_ChannelNotify;

                LOG_CRIT("TEST_MACSEC: channel %d event mask 0x%08x notification "
                         "requested at device %d\n",
                         Notify.ChannelId,
                         Notify.EventMask,
                         TestConf_p->DeviceId);
                CfyE_Rc = CfyE_Notify_Request(TestConf_p->DeviceId, &Notify);
                if (CfyE_Rc != CFYE_STATUS_OK)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, "
                             "CfyE_Notify_Request(C)=%d\n",
                             CfyE_Rc);
                    return false;
                }
            }
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */
        }
        else
        {
            /* Make sure that the events are cleared */
            CfyE_GlobalEventsToProcess  = 0;
            CfyE_ChannelEventsToProcess = 0;
        }
#endif /* TEST_MACSEC_USE_CFYE */

        /* Submit the packet */
        /* Note: For the SecY-only configuration, the provided vPort is used, */
        /*       otherwise vPort = 0 (will be determined by the CfyE) */
        {
            unsigned vPort = 0;

            if (TestRec_p->CfyE_Data_p == NULL)
            {
                vPort = Pkt_p->vPort;
            }

            if (!test_macsec_put_one(TestConf_p,
                                     PktAdmin_p->SrcPkt_p,
                                     Pkt_p->SrcPkt_ByteCount,
                                     (Pkt_p->ChannelID >= ChannelCount ?
                                      0 : Pkt_p->ChannelID),
                                     vPort,
                                     Pkt_p->SecTAGOffset,
                                     Pkt_p->fControl))
            {
                LOG_CRIT("TEST_MACSEC: Failed, test_macsec_put_one()\n");
                return false;
            }
        }

        if (TestConf_p->fVerbose)
        {
            Log_FormattedMessage("TEST_MACSEC: Packet submitted\n");
        }

        /* Receive the result packet */
        if (!test_macsec_get_one(TestConf_p,
                                 PktAdmin_p->DstPkt_p,
                                 &ByteCount,
                                 (Pkt_p->ChannelID >= ChannelCount ?
                                  0 : Pkt_p->ChannelID)))
        {
            LOG_CRIT("TEST_MACSEC: Failed, test_macsec_get_one()\n");
            return false;
        }

        if (TestConf_p->fVerbose)
        {
            Log_FormattedMessage("TEST_MACSEC: Result packet received, "
                                 "size %d\n",
                                 ByteCount);
            Log_HexDump("TEST_MACSEC: Received packet data",
                        0,
                        PktAdmin_p->DstPkt_p,
                        ByteCount);
        }

        /* Compare the expected results to the received ones */
        if (Pkt_p->DstPkt_ByteCount != 0)
        {
            /* Check received packet size */
            if (ByteCount != Pkt_p->DstPkt_ByteCount)
            {
                LOG_CRIT("TEST_MACSEC: Failed, Packet Byte Count Expected=%d, "
                         "Received=%d\n",
                         Pkt_p->DstPkt_ByteCount,
                         ByteCount);
                return false;
            }
            else
            {
                LOG_CRIT("TEST_MACSEC: Packet Expected Byte Count = %d, "
                         "Received Byte Count = %d matches\n",
                         Pkt_p->DstPkt_ByteCount,
                         ByteCount);
            }

            /* Compare the received packet data with the expected */
            if ((Pkt_p->DstPkt_p != NULL) &&
                (memcmp(PktAdmin_p->DstPkt_p, Pkt_p->DstPkt_p, ByteCount) != 0))
            {
                Log_FormattedMessage("TEST_MACSEC: Error, Received packet data "
                                     "differs from the expected\n");
                Log_HexDump("TEST_MACSEC: Expected packet data",
                            0,
                            Pkt_p->DstPkt_p,
                            Pkt_p->DstPkt_ByteCount);
                return false;
            }
            else
            {
                Log_FormattedMessage("TEST_MACSEC: Received packet data "
                                     "matches with the expected\n");
            }
        }

        if ((SecY_GlobalEventsToProcess != 0) ||
#ifdef TEST_MACSEC_USE_CFYE
            (CfyE_GlobalEventsToProcess != 0) ||
            (CfyE_ChannelEventsToProcess != 0) ||
#endif /* TEST_MACSEC_USE_CFYE */
            (SecY_ChannelEventsToProcess != 0))
        {
#ifdef TEST_MACSEC_SUMMARY_VIA_DIAG_API
            bool fShowSummary = false;
#endif
#if !defined(TEST_MACSEC_SUMMARY_VIA_DIAG_API)
            unsigned int NumIndexes = 0;
#endif
            unsigned int * Indexes_p = 0;
            unsigned int j;
#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
            int LoopCounter = TestConf_p->RetryCount;
            unsigned int SecY_GlobalEvents2Handle = 0;
            unsigned int SecY_ChannelEvents2Handle = 0;
            unsigned int SecY_GlobalEvents2Process = SecY_GlobalEventsToProcess;
#ifdef TEST_MACSEC_USE_CFYE
            unsigned int CfyE_GlobalEvents2Handle   = 0;
            unsigned int CfyE_GlobalEvents2Process  = CfyE_GlobalEventsToProcess;
            unsigned int CfyE_ChannelEvents2Handle  = 0;
            unsigned int CfyE_ChannelEvents2Process = CfyE_ChannelEventsToProcess;
#endif /* TEST_MACSEC_USE_CFYE */
#else
            unsigned int SecY_GlobalEvents2Handle = SecY_GlobalEventsToProcess;
#ifdef TEST_MACSEC_USE_CFYE
            unsigned int CfyE_GlobalEvents2Handle  = CfyE_GlobalEventsToProcess;
            unsigned int CfyE_ChannelEvents2Handle = CfyE_ChannelEventsToProcess;
#endif /* TEST_MACSEC_USE_CFYE */
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */

            Indexes_p = test_macsec_malloc(256 * sizeof(unsigned int));
            if (Indexes_p == NULL)
            {
                LOG_CRIT("TEST_MACSEC: Failed, Index array allocation\n");
                return false;
            }

#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
            /* Wait and check if the SecY notification for the requested events */
            /* is received */
            while (LoopCounter > 0)
            {
                if (SecY_GlobalNotificationsReceived != 0)
                {
                    SecY_GlobalNotificationsReceived |= SECY_EVENT_ECC_ERR;
                    SecY_GlobalEvents2Handle = (SecY_GlobalNotificationsReceived &
                                                SecY_GlobalEventsToProcess);
                    if (SecY_GlobalEvents2Handle != 0)
                    {
                        Log_FormattedMessage("TEST_MACSEC: "
                                             "Received SecY notification 0x%x\n",
                                             SecY_GlobalNotificationsReceived);
                    }
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */

#ifdef TEST_MACSEC_MODE_EGRESS
                    if ((SecY_GlobalEvents2Handle & SECY_EVENT_SA_PN_THR) != 0)
                    {
#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                        SecY_GlobalEventsToProcess &= ~SECY_EVENT_SA_PN_THR;
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */
#ifndef TEST_MACSEC_SUMMARY_VIA_DIAG_API
                        /* Read SA Packet Number Threshold Summary register */
                        SecY_Rc = SecY_SA_PnThrSummary_CheckAndClear(
                                      TestConf_p->DeviceId,
                                      &Indexes_p,
                                      &NumIndexes);
                        if (SecY_Rc != SECY_STATUS_OK)
                        {
                            test_macsec_free(Indexes_p);
                            LOG_CRIT("TEST_MACSEC: Failed, SAPnThrSummary read\n");
                            return false;
                        }

                        Log_FormattedMessage("TEST_MACSEC: SAPnThrSummary, "
                                             "nof SA's above threshold %d\n",
                                             NumIndexes);

                        for (j = 0; j < NumIndexes; j++)
                        {
                            Log_FormattedMessage("\tSA index %d\n", Indexes_p[j]);
                        }
#else
                        fShowSummary = true;
#endif
                    }
                    /* Read SA Expired Summary register */
                    if ((SecY_GlobalEvents2Handle & SECY_EVENT_SA_EXPIRED) != 0)
                    {
#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                        SecY_GlobalEventsToProcess &= ~SECY_EVENT_SA_EXPIRED;
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */

#ifndef TEST_MACSEC_SUMMARY_VIA_DIAG_API
                        SecY_Rc = SecY_SA_ExpiredSummary_CheckAndClear(
                                      TestConf_p->DeviceId,
                                      &Indexes_p,
                                      &NumIndexes);
                        if (SecY_Rc != SECY_STATUS_OK)
                        {
                            test_macsec_free(Indexes_p);
                            LOG_CRIT("TEST_MACSEC: Failed, SAExpiredSummary read\n");
                            return false;
                        }

                        Log_FormattedMessage("TEST_MACSEC: SAExpiredSummary, "
                                             "nof SA's above threshold %d\n",
                                             NumIndexes);

                        for (j = 0; j < NumIndexes; j++)
                        {
                            Log_FormattedMessage("\tSA index %d\n", Indexes_p[j]);
                        }
#else
                        fShowSummary = true;
#endif
                    }

                    if ((SecY_GlobalEvents2Handle & SECY_EVENT_PE_OB_SEQNR_THR) != 0)
                    {
#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                        SecY_GlobalEventsToProcess &= ~SECY_EVENT_PE_OB_SEQNR_THR;
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */

                        Log_FormattedMessage("TEST_MACSEC: Received "
                                             "Sequence Number threshold Event\n");
                    }
#endif /* TEST_MACSEC_MODE_EGRESS */

#ifdef TEST_MACSEC_MODE_INGRESS
                    if ((SecY_GlobalEvents2Handle & SECY_EVENT_STAT_RXCAM_THR) != 0)
                    {
#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                        SecY_GlobalEventsToProcess &= ~SECY_EVENT_STAT_RXCAM_THR;
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */

#ifndef TEST_MACSEC_SUMMARY_VIA_DIAG_API
                        /* Read RxCAM Summary register */
                        SecY_Rc = SecY_Device_CountSummary_PRxCAM_CheckAndClear(
                                      TestConf_p->DeviceId,
                                      &Indexes_p,
                                      &NumIndexes);
                        if (SecY_Rc != SECY_STATUS_OK)
                        {
                            test_macsec_free(Indexes_p);
                            LOG_CRIT("TEST_MACSEC: Failed, CountSummaryPRxCAM read\n");
                            return false;
                        }

                        Log_FormattedMessage("TEST_MACSEC: CountSummaryPRxCAM, "
                                             "nof RxCAM's above threshold %d\n",
                                             NumIndexes);

                        for (j = 0; j < NumIndexes; j++)
                        {
                            SecY_RxCAM_Stat_t Stats;

                            /* Read RxCAM statistics */
                            SecY_Rc = SecY_RxCAM_Statistics_Get(
                                          TestConf_p->DeviceId,
                                          Indexes_p[j],
                                          &Stats,
                                          true);
                            if (SecY_Rc != SECY_STATUS_OK)
                            {
                                test_macsec_free(Indexes_p);
                                LOG_CRIT("TEST_MACSEC: Failed, RxCAM statistics read\n");
                                return false;
                            }

                            Log_FormattedMessage("\tRxCAM index %d : %d\n",
                                                 Indexes_p[j],
                                                 Stats.CAMHit.Lo);
                        }
#else
                        for (j = 0; j < 2; j++)
                        {
                            SecY_RxCAM_Stat_t Stats;

                            /* Read RxCAM statistics */
                            SecY_Rc = SecY_RxCAM_Statistics_Get(
                                          TestConf_p->DeviceId,
                                          j,
                                          &Stats,
                                          true);
                            if (SecY_Rc != SECY_STATUS_OK)
                            {
                                test_macsec_free(Indexes_p);
                                LOG_CRIT("TEST_MACSEC: Failed, RxCAM statistics read\n");
                                return false;
                            }

                            Log_FormattedMessage("\tRxCAM index %d : %d\n",
                                                 j,
                                                 Stats.CAMHit.Lo);
                        }
                        fShowSummary = true;
#endif
                    }
#endif /* TEST_MACSEC_MODE_INGRESS */

                    if ((SecY_GlobalEvents2Handle & SECY_EVENT_STAT_SA_THR) != 0)
                    {
#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                        SecY_GlobalEventsToProcess &= ~SECY_EVENT_STAT_SA_THR;
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */

#ifndef TEST_MACSEC_SUMMARY_VIA_DIAG_API
                        /* Read Per SA Count Summary register */
                        SecY_Rc = SecY_Device_CountSummary_PSA_CheckAndClear(
                                      TestConf_p->DeviceId,
                                      &Indexes_p,
                                      &NumIndexes);
                        if (SecY_Rc != SECY_STATUS_OK)
                        {
                            test_macsec_free(Indexes_p);
                            LOG_CRIT("TEST_MACSEC: Failed, CountSummaryPSA read\n");
                            return false;
                        }

                        Log_FormattedMessage("TEST_MACSEC: CountSummaryPSA, "
                                             "nof SA's above threshold %d\n",
                                             NumIndexes);
#ifdef TEST_MACSEC_PERCOUNTER_SUMMARY_ENABLE
                        for (j = 0; j < NumIndexes; j++)
                        {
                            uint32_t uiValue32 = 0;

                            /* Read SA Count Summary register */
                            SecY_Rc = SecY_Device_CountSummary_SA_CheckAndClear(
                                          TestConf_p->DeviceId,
                                          Indexes_p[j],
                                          &uiValue32);
                            if (SecY_Rc != SECY_STATUS_OK)
                            {
                                test_macsec_free(Indexes_p);
                                LOG_CRIT("TEST_MACSEC: Failed, CountSummarySA read\n");
                                return false;
                            }

                            Log_FormattedMessage("\tSA index %d, statistics bits 0x%x\n",
                                                 Indexes_p[j],
                                                 uiValue32);
                        }
#endif
#else
                        fShowSummary = true;
#endif
                    }

                    if ((SecY_GlobalEvents2Handle & SECY_EVENT_STAT_SECY_THR) != 0)
                    {
#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                        SecY_GlobalEventsToProcess &= ~SECY_EVENT_STAT_SECY_THR;
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */

#ifndef TEST_MACSEC_SUMMARY_VIA_DIAG_API
                        /* Read Per SecY Count Summary register */
                        SecY_Rc = SecY_Device_CountSummary_PSecY_CheckAndClear(
                                      TestConf_p->DeviceId,
                                      &Indexes_p,
                                      &NumIndexes);
                        if (SecY_Rc != SECY_STATUS_OK)
                        {
                            test_macsec_free(Indexes_p);
                            LOG_CRIT("TEST_MACSEC: Failed, CountSummaryPSecY read\n");
                            return false;
                        }

                        Log_FormattedMessage("TEST_MACSEC: CountSummaryPSecY, "
                                             "nof SecY's above threshold %d\n",
                                             NumIndexes);

#ifdef TEST_MACSEC_PERCOUNTER_SUMMARY_ENABLE
                        for (j = 0; j < NumIndexes; j++)
                        {
                            uint32_t uiValue32 = 0;

                            /* Read SecY Count Summary register */
                            SecY_Rc = SecY_Device_CountSummary_SecY_CheckAndClear(
                                          TestConf_p->DeviceId,
                                          Indexes_p[j],
                                          &uiValue32);
                            if (SecY_Rc != SECY_STATUS_OK)
                            {
                                test_macsec_free(Indexes_p);
                                LOG_CRIT("TEST_MACSEC: Failed, CountSummarySecY read\n");
                                return false;
                            }

                            Log_FormattedMessage("\tSecY index %d, statistics bits 0x%x\n",
                                                 Indexes_p[j],
                                                 uiValue32);
                        }
#endif
#else
                        fShowSummary = true;
#endif
                    }

                    if ((SecY_GlobalEvents2Handle & SECY_EVENT_STAT_IFC_THR) != 0)
                    {
#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                        SecY_GlobalEventsToProcess &= ~SECY_EVENT_STAT_IFC_THR;
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */

#ifndef TEST_MACSEC_SUMMARY_VIA_DIAG_API
                        /* Read Per IFC Count Summary register */
                        SecY_Rc = SecY_Device_CountSummary_PIfc_CheckAndClear(
                                      TestConf_p->DeviceId,
                                      &Indexes_p,
                                      &NumIndexes);
                        if (SecY_Rc != SECY_STATUS_OK)
                        {
                            test_macsec_free(Indexes_p);
                            LOG_CRIT("TEST_MACSEC: Failed, CountSummaryPIFC read\n");
                            return false;
                        }

                        Log_FormattedMessage("TEST_MACSEC: CountSummaryPIFC, "
                                             "nof IFC's above threshold %d\n",
                                             NumIndexes);

#ifdef TEST_MACSEC_PERCOUNTER_SUMMARY_ENABLE
                        for (j = 0; j < NumIndexes; j++)
                        {
                            uint32_t uiValue32 = 0;

                            /* Read IFC Count Summary register */
                            SecY_Rc = SecY_Device_CountSummary_Ifc_CheckAndClear(
                                          TestConf_p->DeviceId,
                                          Indexes_p[j],
                                          &uiValue32);
                            if (SecY_Rc != SECY_STATUS_OK)
                            {
                                test_macsec_free(Indexes_p);
                                LOG_CRIT("TEST_MACSEC: Failed, CountSummaryIFC read\n");
                                return false;
                            }

                            Log_FormattedMessage("\tIFC index %d, statistics bits 0x%x\n",
                                                 Indexes_p[j],
                                                 uiValue32);
                        }
#endif
#else
                        fShowSummary = true;
#endif
                    }

                    if ((SecY_GlobalEvents2Handle & SECY_EVENT_STAT_IFC1_THR) != 0)
                    {
#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                        SecY_GlobalEventsToProcess &= ~SECY_EVENT_STAT_IFC1_THR;
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */

#ifndef TEST_MACSEC_SUMMARY_VIA_DIAG_API
                        /* Read Per IFC1 Count Summary register */
                        SecY_Rc = SecY_Device_CountSummary_PIfc1_CheckAndClear(
                                      TestConf_p->DeviceId,
                                      &Indexes_p,
                                      &NumIndexes);
                        if (SecY_Rc != SECY_STATUS_OK)
                        {
                            test_macsec_free(Indexes_p);
                            LOG_CRIT("TEST_MACSEC: Failed, CountSummaryPIFC1 read\n");
                            return false;
                        }

                        Log_FormattedMessage("TEST_MACSEC: CountSummaryPIFC1, "
                                             "nof IFC1's above threshold %d\n",
                                             NumIndexes);

#ifdef TEST_MACSEC_PERCOUNTER_SUMMARY_ENABLE
                        for (j = 0; j < NumIndexes; j++)
                        {
                            uint32_t uiValue32 = 0;

                            /* Read IFC1 Count Summary register */
                            SecY_Rc = SecY_Device_CountSummary_Ifc1_CheckAndClear(
                                          TestConf_p->DeviceId,
                                          Indexes_p[j],
                                          &uiValue32);
                            if (SecY_Rc != SECY_STATUS_OK)
                            {
                                test_macsec_free(Indexes_p);
                                LOG_CRIT("TEST_MACSEC: Failed, CountSummaryIFC1 read\n");
                                return false;
                            }

                            Log_FormattedMessage("\tIFC1 index %d, statistics bits 0x%x\n",
                                                 Indexes_p[j],
                                                 uiValue32);
                        }
#endif
#else
                        fShowSummary = true;
#endif
                    }

                    if ((SecY_GlobalEvents2Handle & SECY_EVENT_ENG_IRQ) != 0)
                    {
#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                        SecY_GlobalEventsToProcess &= ~SECY_EVENT_ENG_IRQ;
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */

                        Log_FormattedMessage("TEST_MACSEC: Received Engine IRQ Event\n");
                    }

                    if ((SecY_GlobalEvents2Handle & SECY_EVENT_ECC_ERR) != 0)
                    {
                        SecY_ECCStatus_t ECCStatus;
                        SecY_DeviceStatus_t DeviceStatus;
                        unsigned int i;
                        ZEROINIT(DeviceStatus);
                        DeviceStatus.ECCStatus_p = &ECCStatus;
#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                        SecY_GlobalEventsToProcess &= ~SECY_EVENT_ECC_ERR;
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */
                        Log_FormattedMessage("TEST_MACSEC: Received ECC IRQ Event\n");
                        SecY_Rc = SecY_Device_Status_Get(
                            TestConf_p->DeviceId,
                            &DeviceStatus);
                        if (SecY_Rc != SECY_STATUS_OK)
                        {
                            test_macsec_free(Indexes_p);
                            LOG_CRIT("TEST_MACSEC: Failed, Device Status read\n");
                            return false;
                        }
                        for (i = 0; i < SECY_ECC_NOF_STATUS_COUNTERS; i++)
                        {
                            Log_FormattedMessage(
                                "TEST_MACSEC: ECC counter %u: correctable=%u thr=%d uncorrectable=%u thr=%d\n",
                                i,
                                ECCStatus.Counters[i].CorrectableCount,
                                ECCStatus.Counters[i].fCorrectableThr,
                                ECCStatus.Counters[i].UncorrectableCount,
                                ECCStatus.Counters[i].fUncorrectableThr);
                        }

                    }

#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                    if (SecY_GlobalEventsToProcess != 0)
                    {
                        /* Not all requested SecY notification events received */
                        /* yet, so request them again */
                        SecY_Notify_t Notify;

                        ZEROINIT(Notify);

                        Notify.fGlobal   = true;
                        Notify.EventMask = SecY_GlobalEvents2Process;
                        Notify.CBFunc_p  = test_macsec_SecY_GlobalNotify;

                        SecY_GlobalNotificationsReceived = 0;
                        SecY_Rc = SecY_Notify_Request(TestConf_p->DeviceId,
                                                      &Notify);
                        if (SecY_Rc != SECY_STATUS_OK)
                        {
                            LOG_CRIT("TEST_MACSEC: "
                                     "Failed, SecY_Notify_Request()=%d\n",
                                     SecY_Rc);
                            return false;
                        }
                    }
                }

#ifdef SECY_CHANNEL_NOTIFY_NEEDED
                if (SecY_ChannelNotificationsReceived != 0)
                {
                    SecY_ChannelEvents2Handle = (SecY_ChannelNotificationsReceived &
                                                         SecY_ChannelEventsToProcess);
                    if (SecY_ChannelEvents2Handle != 0)
                    {
                        Log_FormattedMessage("TEST_MACSEC: Received "
                                             "SecY channel notification 0x%x\n",
                                             SecY_ChannelEvents2Handle);
                    }


                    if (SecY_ChannelEvents2Handle & SECY_EVENT_CHAN_ERR_SOP_WO_EOP)
                        Log_FormattedMessage("TEST_MACSEC: SECY_EVENT_CHAN_ERR_SOP_WO_EOP\n");
                    if (SecY_ChannelEvents2Handle & SECY_EVENT_CHAN_ERR_EOP_WO_SOP)
                        Log_FormattedMessage("TEST_MACSEC: SECY_EVENT_CHAN_ERR_EOP_WO_SOP\n");
                    if (SecY_ChannelEvents2Handle & SECY_EVENT_CHAN_ERR_XFER_WO_SOP)
                        Log_FormattedMessage("TEST_MACSEC: SECY_EVENT_CHAN_ERR_XFER_WO_SOP\n");
                    if (SecY_ChannelEvents2Handle & SECY_EVENT_CHAN_ERR_SLOT_SOP)
                        Log_FormattedMessage("TEST_MACSEC: SECY_EVENT_CHAN_ERR_SLOT_SOP\n");
                    if (SecY_ChannelEvents2Handle & SECY_EVENT_CHAN_ERR_SLOT_CHID)
                        Log_FormattedMessage("TEST_MACSEC: SECY_EVENT_CHAN_ERR_SLOT_CHID\n");
                    if (SecY_ChannelEvents2Handle & SECY_EVENT_CHAN_ERR_NOT_B2B)
                        Log_FormattedMessage("TEST_MACSEC: SECY_EVENT_CHAN_ERR_NOT_B2B\n");
                    if (SecY_ChannelEvents2Handle & SECY_EVENT_CHAN_RXCAM_HIT_MULT)
                        Log_FormattedMessage("TEST_MACSEC: SECY_EVENT_CHAN_RXCAM_HIT_MULT\n");
                    if (SecY_ChannelEvents2Handle & SECY_EVENT_CHAN_RXCAM_MISS)
                        Log_FormattedMessage("TEST_MACSEC: SECY_EVENT_CHAN_RXCAM_MISS\n");

                    SecY_ChannelEventsToProcess &= ~SecY_ChannelNotificationsReceived;
                }
#endif
#ifdef TEST_MACSEC_USE_CFYE
                if (CfyE_GlobalNotificationsReceived != 0)
                {
                    CfyE_GlobalNotificationsReceived |= CFYE_EVENT_ECC_ERR;
                    CfyE_GlobalEvents2Handle = (CfyE_GlobalNotificationsReceived &
                                                CfyE_GlobalEventsToProcess);
                    if (CfyE_GlobalEvents2Handle != 0)
                    {
                        Log_FormattedMessage("TEST_MACSEC: Received "
                                             "CfyE global notification 0x%x\n",
                                             CfyE_GlobalEvents2Handle);
                    }
#endif /* TEST_MACSEC_USE_CFYE */
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */

#ifdef TEST_MACSEC_USE_CFYE
                    /* CfyE global notification events handling */
                    if ((CfyE_GlobalEvents2Handle & CFYE_EVENT_STAT_TCAM_THR) != 0)
                    {
#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                        CfyE_GlobalEventsToProcess &= ~CFYE_EVENT_STAT_TCAM_THR;
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */

                        CfyE_Rc = CfyE_Statistics_Summary_TCAM_Read(TestConf_p->DeviceId,
                                                               0,
                                                               Indexes_p,
                                                               1);
                        if (CfyE_Rc != CFYE_STATUS_OK)
                        {
                            test_macsec_free(Indexes_p);
                            LOG_CRIT("TEST_MACSEC: Failed, "
                                     "CfyE_Statistics_Summary_TCAM_Read()=%d\n",
                                     CfyE_Rc);
                            return false;
                        }

                        Log_FormattedMessage("TEST_MACSEC: CountSummaryTCAM, "
                                             "value=0x%x\n",
                                             Indexes_p[0]);

                        {
                            CfyE_Statistics_TCAM_t Stat;

                            CfyE_Rc = CfyE_Statistics_TCAM_Get(TestConf_p->DeviceId,
                                                           0,
                                                           &Stat,
                                                           true); /* device sync request */
                            if (CfyE_Rc != CFYE_STATUS_OK)
                            {
                                test_macsec_free(Indexes_p);
                                LOG_CRIT("TEST_MACSEC: Failed, "
                                         "CfyE_Statistics_TCAM_Get()=%d\n",
                                         CfyE_Rc);
                                return false;
                            }

                            Log_FormattedMessage("TEST_MACSEC: TCAM%u counter = %u\n",
                                                 0, Stat.Counter.Lo);
                            if (Stat.Counter.Lo != 0)
                            {
                                CfyE_Rc = CfyE_Statistics_TCAM_Get(TestConf_p->DeviceId,
                                                                   0,
                                                                   &Stat,
                                                                   true); /* device sync request */
                                if (CfyE_Rc != CFYE_STATUS_OK)
                                {
                                    test_macsec_free(Indexes_p);
                                    LOG_CRIT("TEST_MACSEC: Failed, "
                                             "CfyE_Statistics_TCAM_Get()=%d\n",
                                             CfyE_Rc);
                                    return false;
                                }

                                if (Stat.Counter.Lo != 0)
                                {
                                    test_macsec_free(Indexes_p);
                                    LOG_CRIT("TEST_MACSEC: failed TCAM statistics did not clear\n");
                                    return false;
                                }
                            }
                        }
                    }

                    if ((CfyE_GlobalEvents2Handle & CFYE_EVENT_STAT_CHAN_THR) != 0)
                    {
                        CfyE_Ch_Mask_t ChSummary;

#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                        CfyE_GlobalEventsToProcess &= ~CFYE_EVENT_STAT_CHAN_THR;
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */

                        Log_FormattedMessage("TEST_MACSEC: CfyE global channel statistics available\n");

                        ZEROINIT(ChSummary);

                        CfyE_Rc = CfyE_Statistics_Summary_Channel_Read(TestConf_p->DeviceId,
                                                                       &ChSummary);
                        if (CfyE_Rc != CFYE_STATUS_OK)
                        {
                            LOG_CRIT("TEST_MACSEC: Failed, "
                                     "CfyE_Statistics_Summary_Channel_Read() error %d\n",
                                     CfyE_Rc);
                            return false;
                        }

                        if (TestConf_p->fVerbose)
                        {
                            Log_FormattedMessage("TEST_MACSEC: Cfye per-channel Summary counters: ");

                            for (j = 0; j < MaxCfyEChannels; j++)
                                Log_FormattedMessage("%d ", (ChSummary.ch_bitmask[j / 32] & (1 << (j % 32))) != 0);

                            Log_FormattedMessage("\n");
                        }
                    }


                    if ((CfyE_GlobalEvents2Handle & CFYE_EVENT_ECC_ERR) != 0)
                    {
                        CfyE_ECCStatus_t ECCStatus;
                        CfyE_DeviceStatus_t DeviceStatus;
                        unsigned int i;
                        ZEROINIT(DeviceStatus);
                        DeviceStatus.ECCStatus_p = &ECCStatus;
#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                        CfyE_GlobalEventsToProcess &= ~CFYE_EVENT_ECC_ERR;
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */
                        Log_FormattedMessage("TEST_MACSEC: Received CfyE ECC IRQ Event\n");
                        CfyE_Rc = CfyE_Device_Status_Get(
                            TestConf_p->DeviceId,
                            &DeviceStatus);
                        if (CfyE_Rc != CFYE_STATUS_OK)
                        {
                            test_macsec_free(Indexes_p);
                            LOG_CRIT("TEST_MACSEC: Failed, ECC Status read\n");
                            return false;
                        }
                        for (i = 0; i < CFYE_ECC_NOF_STATUS_COUNTERS; i++)
                        {
                            Log_FormattedMessage(
                                "TEST_MACSEC: ECC counter %u: correctable=%u thr=%d uncorrectable=%u thr=%d\n",
                                i,
                                ECCStatus.Counters[i].CorrectableCount,
                                ECCStatus.Counters[i].fCorrectableThr,
                                ECCStatus.Counters[i].UncorrectableCount,
                                ECCStatus.Counters[i].fUncorrectableThr);
                        }
                    }

#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                    if (CfyE_GlobalEventsToProcess != 0)
                    {
                        /* Not all requested CfyE global notification events */
                        /* received yet, so request them again */
                        CfyE_Notify_t Notify;

                        ZEROINIT(Notify);

                        Notify.fGlobal   = true;
                        Notify.EventMask = CfyE_GlobalEvents2Process;
                        Notify.CBFunc_p  = test_macsec_CfyE_GlobalNotify;

                        CfyE_GlobalNotificationsReceived = 0;
                        LOG_CRIT("TEST_MACSEC: global event mask 0x%08x "
                                 "notification requested at device %d\n",
                                 Notify.EventMask,
                                 TestConf_p->DeviceId);
                        CfyE_Rc = CfyE_Notify_Request(TestConf_p->DeviceId,
                                                      &Notify);
                        if (CfyE_Rc != CFYE_STATUS_OK)
                        {
                            LOG_CRIT("TEST_MACSEC: Failed, "
                                     "CfyE_Notify_Request(G)=%d\n",
                                     CfyE_Rc);
                            return false;
                        }
                    }
                }

                if (CfyE_ChannelNotificationsReceived != 0)
                {
                    CfyE_ChannelEvents2Handle = (CfyE_ChannelNotificationsReceived &
                                                 CfyE_ChannelEventsToProcess);
                    if (CfyE_ChannelEvents2Handle != 0)
                    {
                        Log_FormattedMessage("TEST_MACSEC: Received "
                                             "CfyE channel notification 0x%x\n",
                                             CfyE_ChannelEvents2Handle);
                    }
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */

                    /* CfyE channel notification events handling */
                    if ((CfyE_ChannelEvents2Handle & CFYE_EVENT_CHAN_ERR_SOP_WO_EOP) != 0)
                    {
#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                        CfyE_ChannelEventsToProcess &= ~CFYE_EVENT_CHAN_ERR_SOP_WO_EOP;
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */

                        Log_FormattedMessage("TEST_MACSEC: CfyE CFYE_EVENT_CHAN_ERR_SOP_WO_EOP\n");
                    }

                    if ((CfyE_ChannelEvents2Handle & CFYE_EVENT_CHAN_ERR_EOP_WO_SOP) != 0)
                    {
#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                        CfyE_ChannelEventsToProcess &= ~CFYE_EVENT_CHAN_ERR_EOP_WO_SOP;
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */

                        Log_FormattedMessage("TEST_MACSEC: CfyE CFYE_EVENT_CHAN_ERR_EOP_WO_SOP\n");
                    }

                    if ((CfyE_ChannelEvents2Handle & CFYE_EVENT_CHAN_ERR_XFER_WO_SOP) != 0)
                    {
#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                        CfyE_ChannelEventsToProcess &= ~CFYE_EVENT_CHAN_ERR_XFER_WO_SOP;
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */

                        Log_FormattedMessage("TEST_MACSEC: CfyE CFYE_EVENT_CHAN_ERR_XFER_WO_SOP\n");
                    }

                    if ((CfyE_ChannelEvents2Handle & CFYE_EVENT_CHAN_ERR_SLOT_SOP) != 0)
                    {
#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                        CfyE_ChannelEventsToProcess &= ~CFYE_EVENT_CHAN_ERR_SLOT_SOP;
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */

                        Log_FormattedMessage("TEST_MACSEC: CfyE CFYE_EVENT_CHAN_ERR_SLOT_SOP\n");
                    }

                    if ((CfyE_ChannelEvents2Handle & CFYE_EVENT_CHAN_ERR_SLOT_CHID) != 0)
                    {
#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                        CfyE_ChannelEventsToProcess &= ~CFYE_EVENT_CHAN_ERR_SLOT_CHID;
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */

                        Log_FormattedMessage("TEST_MACSEC: CfyE CFYE_EVENT_CHAN_ERR_SLOT_CHID\n");
                    }

                    if ((CfyE_ChannelEvents2Handle & CFYE_EVENT_CHAN_ERR_NOT_B2B) != 0)
                    {
#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                        CfyE_ChannelEventsToProcess &= ~CFYE_EVENT_CHAN_ERR_NOT_B2B;
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */

                        Log_FormattedMessage("TEST_MACSEC: CfyE CFYE_EVENT_CHAN_ERR_NOT_B2B\n");
                    }

                    if ((CfyE_ChannelEvents2Handle & CFYE_EVENT_CHAN_CTRL_PACKET) != 0)
                    {
#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                        CfyE_ChannelEventsToProcess &= ~CFYE_EVENT_CHAN_CTRL_PACKET;
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */

                        Log_FormattedMessage("TEST_MACSEC: CfyE CFYE_EVENT_CHAN_CTRL_PACKET\n");

#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                        if ((CfyE_ChannelEventsToProcess & CFYE_EVENT_CHAN_DATA_PACKET) != 0)
                        {
                            /* Data packet event will never come, because */
                            /* packet was detected and labeled as control packet */
                            CfyE_ChannelEventsToProcess &= ~CFYE_EVENT_CHAN_DATA_PACKET;
                        }
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */
                    }

                    if ((CfyE_ChannelEvents2Handle & CFYE_EVENT_CHAN_DATA_PACKET) != 0)
                    {
#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                        CfyE_ChannelEventsToProcess &= ~CFYE_EVENT_CHAN_DATA_PACKET;
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */

                        Log_FormattedMessage("TEST_MACSEC: CfyE CFYE_EVENT_CHAN_DATA_PACKET\n");

#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                        if ((CfyE_ChannelEventsToProcess & CFYE_EVENT_CHAN_CTRL_PACKET) != 0)
                        {
                            /* Control packet event will never come, because */
                            /* packet was detected and labeled as data packet */
                            CfyE_ChannelEventsToProcess &= ~CFYE_EVENT_CHAN_CTRL_PACKET;
                        }
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */
                    }

                    if ((CfyE_ChannelEvents2Handle & CFYE_EVENT_CHAN_DROP_PACKET) != 0)
                    {
#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                        CfyE_ChannelEventsToProcess &= ~CFYE_EVENT_CHAN_DROP_PACKET;
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */

                        Log_FormattedMessage("TEST_MACSEC: CfyE CFYE_EVENT_CHAN_DROP_PACKET\n");
                    }

                    if ((CfyE_ChannelEvents2Handle & CFYE_EVENT_CHAN_TCAM_HIT_MULT) != 0)
                    {
#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                        CfyE_ChannelEventsToProcess &= ~CFYE_EVENT_CHAN_TCAM_HIT_MULT;
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */

                        Log_FormattedMessage("TEST_MACSEC: CfyE CFYE_EVENT_CHAN_TCAM_HIT_MULT\n");
                    }

                    if ((CfyE_ChannelEvents2Handle & CFYE_EVENT_CHAN_TCAM_MISS) != 0)
                    {
#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                        CfyE_ChannelEventsToProcess &= ~CFYE_EVENT_CHAN_TCAM_MISS;
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */

                        Log_FormattedMessage("TEST_MACSEC: CfyE CFYE_EVENT_CHAN_TCAM_MISS\n");
                    }

#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                    if (CfyE_ChannelEventsToProcess != 0)
                    {
                        /* Not all requested CfyE global notification events */
                        /* received yet, so request them again */
                        CfyE_Notify_t Notify;

                        ZEROINIT(Notify);

                        Notify.ChannelId = Pkt_p->ChannelID;
                        Notify.EventMask = CfyE_ChannelEvents2Process;
                        Notify.CBFunc_p  = test_macsec_CfyE_ChannelNotify;

                        CfyE_ChannelNotificationsReceived = 0;
                        LOG_CRIT("TEST_MACSEC: channel %d event mask 0x%08x "
                                 "notification requested at device %d\n",
                                 Notify.ChannelId,
                                 Notify.EventMask,
                                 TestConf_p->DeviceId);
                        CfyE_Rc = CfyE_Notify_Request(TestConf_p->DeviceId,
                                                      &Notify);
                        if (CfyE_Rc != CFYE_STATUS_OK)
                        {
                            LOG_CRIT("TEST_MACSEC: Failed, "
                                     "CfyE_Notify_Request(C)=%d\n",
                                     CfyE_Rc);
                            return false;
                        }
                    }
                }
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */
#endif /* TEST_MACSEC_USE_CFYE */

#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
                if ((SecY_GlobalEventsToProcess == 0) &&
#ifdef TEST_MACSEC_USE_CFYE
                    (CfyE_GlobalEventsToProcess == 0) &&
                    (CfyE_ChannelEventsToProcess == 0) &&
#endif /* TEST_MACSEC_USE_CFYE */
                    (SecY_ChannelEventsToProcess == 0))
                {
                    /* Handled all expected notifications */
                    break;
                }

                /* Delay until next try */
                test_macsec_usleep(TestConf_p->TimeoutMS * 1000);

                LoopCounter--;
            }
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */
#ifdef TEST_MACSEC_SUMMARY_VIA_DIAG_API
            if (fShowSummary)
            {
                SecY_Rc= SecY_Diag_Device_Dump(TestConf_p->DeviceId);
                if (SecY_Rc != SECY_STATUS_OK)
                {
                    test_macsec_free(Indexes_p);
                    LOG_CRIT("TEST_MACSEC: Failed, SecY_Diag_Device_Dumpn");
                    return false;
                        }
            }
#endif

            test_macsec_free(Indexes_p);

#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
            if (SecY_GlobalEventsToProcess != 0)
            {
                LOG_CRIT("TEST_MACSEC: Failed, SecY notification timeout "
                         "(Missed events mask 0x%x)\n",
                         SecY_GlobalEventsToProcess);

#ifdef TEST_MACSEC_DEBUG
                test_macsec_debug_read32(TEST_MACSEC_DEBUG_DEVICE_NAME,
                                         TEST_MACSEC_DEBUG_EIP164_INT_STAT_OFF);
                test_macsec_debug_read32(TEST_MACSEC_DEBUG_DEVICE_NAME,
                                         TEST_MACSEC_DEBUG_EIP201_EN_STAT_OFF);
#endif /* TEST_MACSEC_DEBUG */

                return false;
            }

#ifdef SECY_CHANNEL_NOTIFY_NEEDED
            if (SecY_ChannelEventsToProcess != 0)
            {
                    LOG_CRIT("TEST_MACSEC: Failed, ChannelNotifications=0x%x"
                             " expected=0x%x\n",
                             SecY_ChannelNotificationsReceived,
                             SecY_ChannelEventsToProcess);
                    return false;
            }
#endif /* SECY_CHANNEL_NOTIFY_NEEDED */


#ifdef TEST_MACSEC_USE_CFYE
            if (CfyE_GlobalEventsToProcess != 0)
            {
                LOG_CRIT("TEST_MACSEC: Failed, CfyE global notification "
                         "timeout (Missed events mask 0x%x)\n",
                         CfyE_GlobalEventsToProcess);

                return false;
            }

            if (CfyE_ChannelEventsToProcess != 0)
            {
                LOG_CRIT("TEST_MACSEC: Failed, CfyE channel notification "
                         "timeout (Missed events mask 0x%x)\n",
                         CfyE_ChannelEventsToProcess);

                return false;
            }
#endif /* TEST_MACSEC_USE_CFYE */
#endif /* TEST_MACSEC_SECY_NOTIFY_ENABLE */
        }

        /* Next packet */
        Pkt_p++;
        PktAdmin_p++;
    }

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Packet processing done\n");
    }

    return true;                        /* success */
}


/*----------------------------------------------------------------------------
 * test_macsec_single_transform_statistics_test
 */
bool
test_macsec_single_transform_statistics_test(
        const Test_Case_ConfParams_t * TestConf_p,
        const Test_Case_Transform_t * TC_Transform_p,
        Test_Transform_t * Tr_Admin_p)
{
    bool fSuccess = true;

    if (SecY_SAHandle_IsSame(&Tr_Admin_p->TransformHandle,
                             &SecY_SAHandle_NULL))
    {
        /* SA already removed */
        goto func_return;
    }

    if (NULL == TC_Transform_p)
    {
        Log_FormattedMessage("TEST_MACSEC: Invalid arguments\n");
        return false;
    }

#ifdef TEST_MACSEC_MODE_INGRESS
    if (TestConf_p->fIngress)
    {
        switch (TC_Transform_p->operation)
        {
        case SAB_OP_MACSEC:
        case SAB_OP_ENCAUTH_AES_GCM:
        case SAB_OP_ENC_AES_CTR:
        default:
        {
            SecY_Status_t SecY_Rc;
            SecY_SA_Stat_I_t Stat;

            ZEROINIT(Stat);

            SecY_Rc = SecY_SA_Statistics_I_Get(TestConf_p->DeviceId,
                                               Tr_Admin_p->TransformHandle,
                                               &Stat,
                                               true);
            if (SecY_Rc != SECY_STATUS_OK)
            {
                LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Statistics_I_Get()=%d\n",
                         SecY_Rc);
                fSuccess = false;
                goto func_return;
            }

            if (TestConf_p->fVerbose)
            {
                Log_FormattedMessage("TEST_MACSEC: Ingress SA Statistics:\n"
                                     "\tInOctetsDecrypted: %u\n"
                                     "\tInOctetsValidated: %u\n"
                                     "\tInPktsDelayed:     %u\n"
                                     "\tInPktsInvalid:     %u\n"
                                     "\tInPktsLate:        %u\n"
                                     "\tInPktsNotUsingSA:  %u\n"
                                     "\tInPktsNotValid:    %u\n"
                                     "\tInPktsOK:          %u\n"
                                     "\tInPktsUnchecked:   %u\n"
                                     "\tInPktsUnusedSA:    %u\n",
                                     Stat.InOctetsDecrypted.Lo,
                                     Stat.InOctetsValidated.Lo,
                                     Stat.InPktsDelayed.Lo,
                                     Stat.InPktsInvalid.Lo,
                                     Stat.InPktsLate.Lo,
                                     Stat.InPktsNotUsingSA.Lo,
                                     Stat.InPktsNotValid.Lo,
                                     Stat.InPktsOK.Lo,
                                     Stat.InPktsUnchecked.Lo,
                                     Stat.InPktsUnusedSA.Lo);
            }

            /* Only check if check data is available */
            if (TC_Transform_p->TransformStat_p != NULL)
            {
                SecY_SA_Stat_I_t * TStat_p;

                TStat_p = (SecY_SA_Stat_I_t *)TC_Transform_p->TransformStat_p;

                if (Stat.InOctetsDecrypted.Lo != TStat_p->InOctetsDecrypted.Lo)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInOctetsDecrypted.Lo %d, expected %d.\n",
                             Stat.InOctetsDecrypted.Lo,
                             TStat_p->InOctetsDecrypted.Lo);
                    fSuccess = false;
                }

                if (Stat.InOctetsDecrypted.Hi != TStat_p->InOctetsDecrypted.Hi)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInOctetsDecrypted.Hi %d, expected %d.\n",
                             Stat.InOctetsDecrypted.Hi,
                             TStat_p->InOctetsDecrypted.Hi);
                    fSuccess = false;
                }

                if (Stat.InOctetsValidated.Lo != TStat_p->InOctetsValidated.Lo)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInOctetsValidated.Lo %d, expected %d.\n",
                             Stat.InOctetsValidated.Lo,
                             TStat_p->InOctetsValidated.Lo);
                    fSuccess = false;
                }

                if (Stat.InOctetsValidated.Hi != TStat_p->InOctetsValidated.Hi)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInOctetsValidated.Hi %d, expected %d.\n",
                             Stat.InOctetsValidated.Hi,
                             TStat_p->InOctetsValidated.Hi);
                    fSuccess = false;
                }

                if (Stat.InPktsDelayed.Lo != TStat_p->InPktsDelayed.Lo)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsDelayed.Lo %d, expected %d.\n",
                             Stat.InPktsDelayed.Lo,
                             TStat_p->InPktsDelayed.Lo);
                    fSuccess = false;
                }

                if (Stat.InPktsDelayed.Hi != TStat_p->InPktsDelayed.Hi)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsDelayed.Hi %d, expected %d.\n",
                             Stat.InPktsDelayed.Hi,
                             TStat_p->InPktsDelayed.Hi);
                    fSuccess = false;
                }

                if (Stat.InPktsInvalid.Lo != TStat_p->InPktsInvalid.Lo)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsInvalid.Lo %d, expected %d.\n",
                             Stat.InPktsInvalid.Lo,
                             TStat_p->InPktsInvalid.Lo);
                    fSuccess = false;
                }

                if (Stat.InPktsInvalid.Hi != TStat_p->InPktsInvalid.Hi)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsInvalid.Hi %d, expected %d.\n",
                             Stat.InPktsInvalid.Hi,
                             TStat_p->InPktsInvalid.Hi);
                    fSuccess = false;
                }

                if (Stat.InPktsLate.Lo != TStat_p->InPktsLate.Lo)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsLate.Lo %d, expected %d.\n",
                             Stat.InPktsLate.Lo,
                             TStat_p->InPktsLate.Lo);
                    fSuccess = false;
                }

                if (Stat.InPktsLate.Hi != TStat_p->InPktsLate.Hi)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsLate.Hi %d, expected %d.\n",
                             Stat.InPktsLate.Hi,
                             TStat_p->InPktsLate.Hi);
                    fSuccess = false;
                }

                if (Stat.InPktsNotUsingSA.Lo != TStat_p->InPktsNotUsingSA.Lo)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsNotUsingSA.Lo %d, expected %d.\n",
                             Stat.InPktsNotUsingSA.Lo,
                             TStat_p->InPktsNotUsingSA.Lo);
                    fSuccess = false;
                }

                if (Stat.InPktsNotUsingSA.Hi != TStat_p->InPktsNotUsingSA.Hi)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsNotUsingSA.Hi %d, expected %d.\n",
                             Stat.InPktsNotUsingSA.Hi,
                             TStat_p->InPktsNotUsingSA.Hi);
                    fSuccess = false;
                }

                if (Stat.InPktsNotValid.Lo != TStat_p->InPktsNotValid.Lo)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsNotValid.Lo %d, expected %d.\n",
                             Stat.InPktsNotValid.Lo,
                             TStat_p->InPktsNotValid.Lo);
                    fSuccess = false;
                }

                if (Stat.InPktsNotValid.Hi != TStat_p->InPktsNotValid.Hi)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsNotValid.Hi %d, expected %d.\n",
                             Stat.InPktsNotValid.Hi,
                             TStat_p->InPktsNotValid.Hi);
                    fSuccess = false;
                }

                if (Stat.InPktsOK.Lo != TStat_p->InPktsOK.Lo)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsOK.Lo %d, expected %d.\n",
                             Stat.InPktsOK.Lo,
                             TStat_p->InPktsOK.Lo);
                    fSuccess = false;
                }

                if (Stat.InPktsOK.Hi != TStat_p->InPktsOK.Hi)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsOK.Hi %d, expected %d.\n",
                             Stat.InPktsOK.Hi,
                             TStat_p->InPktsOK.Hi);
                    fSuccess = false;
                }

                if (Stat.InPktsUnchecked.Lo != TStat_p->InPktsUnchecked.Lo)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsUnchecked.Lo %d, expected %d.\n",
                             Stat.InPktsUnchecked.Lo,
                             TStat_p->InPktsUnchecked.Lo);
                    fSuccess = false;
                }

                if (Stat.InPktsUnchecked.Hi != TStat_p->InPktsUnchecked.Hi)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsUnchecked.Hi %d, expected %d.\n",
                             Stat.InPktsUnchecked.Hi,
                             TStat_p->InPktsUnchecked.Hi);
                    fSuccess = false;
                }

                if (Stat.InPktsUnusedSA.Lo != TStat_p->InPktsUnusedSA.Lo)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsUnusedSA.Lo %d, expected %d.\n",
                             Stat.InPktsUnusedSA.Lo,
                             TStat_p->InPktsUnusedSA.Lo);
                    fSuccess = false;
                }

                if (Stat.InPktsUnusedSA.Hi != TStat_p->InPktsUnusedSA.Hi)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsUnusedSA.Hi %d, expected %d.\n",
                             Stat.InPktsUnusedSA.Hi,
                             TStat_p->InPktsUnusedSA.Hi);
                    fSuccess = false;
                }

                if (Stat.InPktsOK.Lo != 0)
                {
                    SecY_Rc = SecY_SA_Statistics_I_Get(TestConf_p->DeviceId,
                                                       Tr_Admin_p->TransformHandle,
                                                       &Stat,
                                                       true);
                    if (SecY_Rc != SECY_STATUS_OK)
                    {
                        LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Statistics_I_Get()=%d\n",
                                 SecY_Rc);
                        fSuccess = false;
                        goto func_return;
                    }
                    if (Stat.InPktsOK.Lo != 0)
                    {
                        LOG_CRIT("TEST_MACSEC: Failded to clear SA statistics\n");
                        fSuccess = false;
                        goto func_return;
                    }
                }
                if (TestConf_p->fVerbose)
                {
                    Log_FormattedMessage(
                        "TEST_MACSEC: Ingress SA statistics test %s.\n",
                        fSuccess ? "passed" : "failed");
                }
            }
        }
        break;
#if defined(TEST_IPSEC_ENABLE)
        case SAB_OP_IPSEC:
        {
            SecY_Status_t SecY_Rc;
            SecY_SA_Stat_IPsec_I_t Stat;

            ZEROINIT(Stat);

            SecY_Rc = SecY_SA_Statistics_IPsec_I_Get(TestConf_p->DeviceId,
                                                     Tr_Admin_p->TransformHandle,
                                                     &Stat,
                                                     true);
            if (SecY_Rc != SECY_STATUS_OK)
            {
                LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Statistics_IPsec_I_Get()=%d\n",
                         SecY_Rc);
                fSuccess = false;
                goto func_return;
            }

            if (TestConf_p->fVerbose)
            {
                Log_FormattedMessage("TEST_MACSEC: Ingress SA Statistics:\n"
                                     "\tInPktsPadNotValid  : %u\n"
                                     "\tInPktsReplayed     : %u\n"
                                     "\tInPktsLate         : %u\n"
                                     "\tInPktsOK           : %u\n"
                                     "\tInPktsPadLenF a i l: %u\n"
                                     "\tInPktsNotValid     : %u\n"
                                     "\tInPktsNotUsingSA   : %u\n"
                                     "\tInPktsPadDummy     : %u\n"
                                     "\tInOctetsDecrypted  : %u\n"
                                     "\tInOctetsValidated  : %u\n",
                                     Stat.InPktsPadNotValid.Lo,
                                     Stat.InPktsReplayed.Lo,
                                     Stat.InPktsLate.Lo,
                                     Stat.InPktsOK.Lo,
                                     Stat.InPktsPadLenFail.Lo,
                                     Stat.InPktsNotValid.Lo,
                                     Stat.InPktsNotUsingSA.Lo,
                                     Stat.InPktsPadDummy.Lo,
                                     Stat.InOctetsDecrypted.Lo,
                                     Stat.InOctetsValidated.Lo);
            }

            /* Only check if check data is available */
            if (TC_Transform_p->TransformStat_p != NULL)
            {
                SecY_SA_Stat_IPsec_I_t * TStat_p;

                TStat_p = (SecY_SA_Stat_IPsec_I_t *) TC_Transform_p->TransformStat_p;

                if (Stat.InOctetsDecrypted.Lo != TStat_p->InOctetsDecrypted.Lo)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInOctetsDecrypted.Lo %d, expected %d.\n",
                             Stat.InOctetsDecrypted.Lo,
                             TStat_p->InOctetsDecrypted.Lo);
                    fSuccess = false;
                }

                if (Stat.InOctetsDecrypted.Hi != TStat_p->InOctetsDecrypted.Hi)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInOctetsDecrypted.Hi %d, expected %d.\n",
                             Stat.InOctetsDecrypted.Hi,
                             TStat_p->InOctetsDecrypted.Hi);
                    fSuccess = false;
                }

                if (Stat.InOctetsValidated.Lo != TStat_p->InOctetsValidated.Lo)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInOctetsValidated.Lo %d, expected %d.\n",
                             Stat.InOctetsValidated.Lo,
                             TStat_p->InOctetsValidated.Lo);
                    fSuccess = false;
                }

                if (Stat.InOctetsValidated.Hi != TStat_p->InOctetsValidated.Hi)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInOctetsValidated.Hi %d, expected %d.\n",
                             Stat.InOctetsValidated.Hi,
                             TStat_p->InOctetsValidated.Hi);
                    fSuccess = false;
                }

                if (Stat.InPktsPadDummy.Lo != TStat_p->InPktsPadDummy.Lo)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsDelayed.Lo %d, expected %d.\n",
                             Stat.InPktsPadDummy.Lo,
                             TStat_p->InPktsPadDummy.Lo);
                    fSuccess = false;
                }

                if (Stat.InPktsPadDummy.Hi != TStat_p->InPktsPadDummy.Hi)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsPadDummy.Hi %d, expected %d.\n",
                             Stat.InPktsPadDummy.Hi,
                             TStat_p->InPktsPadDummy.Hi);
                    fSuccess = false;
                }

                if (Stat.InPktsPadLenFail.Lo != TStat_p->InPktsPadLenFail.Lo)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsPadLenF a i l.Lo %d, expected %d.\n",
                             Stat.InPktsPadLenFail.Lo,
                             TStat_p->InPktsPadLenFail.Lo);
                    fSuccess = false;
                }

                if (Stat.InPktsPadLenFail.Hi != TStat_p->InPktsPadLenFail.Hi)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsInvalid.Hi %d, expected %d.\n",
                             Stat.InPktsPadLenFail.Hi,
                             TStat_p->InPktsPadLenFail.Hi);
                    fSuccess = false;
                }

                if (Stat.InPktsLate.Lo != TStat_p->InPktsLate.Lo)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsLate.Lo %d, expected %d.\n",
                             Stat.InPktsLate.Lo,
                             TStat_p->InPktsLate.Lo);
                    fSuccess = false;
                }

                if (Stat.InPktsLate.Hi != TStat_p->InPktsLate.Hi)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsLate.Hi %d, expected %d.\n",
                             Stat.InPktsLate.Hi,
                             TStat_p->InPktsLate.Hi);
                    fSuccess = false;
                }

                if (Stat.InPktsNotUsingSA.Lo != TStat_p->InPktsNotUsingSA.Lo)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsNotUsingSA.Lo %d, expected %d.\n",
                             Stat.InPktsNotUsingSA.Lo,
                             TStat_p->InPktsNotUsingSA.Lo);
                    fSuccess = false;
                }

                if (Stat.InPktsNotUsingSA.Hi != TStat_p->InPktsNotUsingSA.Hi)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsNotUsingSA.Hi %d, expected %d.\n",
                             Stat.InPktsNotUsingSA.Hi,
                             TStat_p->InPktsNotUsingSA.Hi);
                    fSuccess = false;
                }

                if (Stat.InPktsNotValid.Lo != TStat_p->InPktsNotValid.Lo)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsNotValid.Lo %d, expected %d.\n",
                             Stat.InPktsNotValid.Lo,
                             TStat_p->InPktsNotValid.Lo);
                    fSuccess = false;
                }

                if (Stat.InPktsNotValid.Hi != TStat_p->InPktsNotValid.Hi)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsNotValid.Hi %d, expected %d.\n",
                             Stat.InPktsNotValid.Hi,
                             TStat_p->InPktsNotValid.Hi);
                    fSuccess = false;
                }

                if (Stat.InPktsOK.Lo != TStat_p->InPktsOK.Lo)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsOK.Lo %d, expected %d.\n",
                             Stat.InPktsOK.Lo,
                             TStat_p->InPktsOK.Lo);
                    fSuccess = false;
                }

                if (Stat.InPktsOK.Hi != TStat_p->InPktsOK.Hi)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsOK.Hi %d, expected %d.\n",
                             Stat.InPktsOK.Hi,
                             TStat_p->InPktsOK.Hi);
                    fSuccess = false;
                }

                if (Stat.InPktsReplayed.Lo != TStat_p->InPktsReplayed.Lo)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsReplayed.Lo %d, expected %d.\n",
                             Stat.InPktsReplayed.Lo,
                             TStat_p->InPktsReplayed.Lo);
                    fSuccess = false;
                }

                if (Stat.InPktsReplayed.Hi != TStat_p->InPktsReplayed.Hi)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsReplayed.Hi %d, expected %d.\n",
                             Stat.InPktsReplayed.Hi,
                             TStat_p->InPktsReplayed.Hi);
                    fSuccess = false;
                }

                if (Stat.InPktsPadNotValid.Lo != TStat_p->InPktsPadNotValid.Lo)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsReplayed.Lo %d, expected %d.\n",
                             Stat.InPktsReplayed.Lo,
                             TStat_p->InPktsPadNotValid.Lo);
                    fSuccess = false;
                }

                if (Stat.InPktsPadNotValid.Hi != TStat_p->InPktsPadNotValid.Hi)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                             "\tInPktsPadNotValid.Hi %d, expected %d.\n",
                             Stat.InPktsPadNotValid.Hi,
                             TStat_p->InPktsPadNotValid.Hi);
                    fSuccess = false;
                }

                if (Stat.InPktsOK.Lo != 0)
                {
                    SecY_Rc = SecY_SA_Statistics_IPsec_I_Get(TestConf_p->DeviceId,
                                                       Tr_Admin_p->TransformHandle,
                                                       &Stat,
                                                       true);
                    if (SecY_Rc != SECY_STATUS_OK)
                    {
                        LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Statistics_I_Get()=%d\n",
                                 SecY_Rc);
                        fSuccess = false;
                        goto func_return;
                    }
                    if (Stat.InPktsOK.Lo != 0)
                    {
                        LOG_CRIT("TEST_MACSEC: Failded to clear SA statistics\n");
                        fSuccess = false;
                        goto func_return;
                    }
                }
                if (TestConf_p->fVerbose)
                {
                    Log_FormattedMessage(
                        "TEST_MACSEC: IPsec Ingress SA statistics test %s.\n",
                        fSuccess ? "passed" : "failed");
                }
            }
        }
        break;
#endif /* TEST_IPSEC_ENABLE */
        }
    }
#endif /* TEST_MACSEC_MODE_INGRESS */

#ifdef TEST_MACSEC_MODE_EGRESS
    if (!TestConf_p->fIngress)
    {
        SecY_Status_t SecY_Rc;
        SecY_SA_Stat_E_t Stat;

        ZEROINIT(Stat);

        SecY_Rc = SecY_SA_Statistics_E_Get(TestConf_p->DeviceId,
                                           Tr_Admin_p->TransformHandle,
                                           &Stat,
                                           true);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Statistics_E_Get()=%d\n",
                     SecY_Rc);
            fSuccess = false;
            goto func_return;
        }

        if (TestConf_p->fVerbose)
        {
            Log_FormattedMessage("TEST_MACSEC: Egress SA Statistics:\n"
                                 "\tOutOctetsEncryptedProtected: %u\n"
                                 "\tOutPktsEncryptedProtected:   %u\n"
                                 "\tOutPktsTooLong:              %u\n"
                                 "\tOutPktsSANotInUse:           %u\n",
                                 Stat.OutOctetsEncryptedProtected.Lo,
                                 Stat.OutPktsEncryptedProtected.Lo,
                                 Stat.OutPktsTooLong.Lo,
                                 Stat.OutPktsSANotInUse.Lo);
        }

        /* Only check if check data is available */
        if (TC_Transform_p->TransformStat_p != NULL)
        {
            SecY_SA_Stat_E_t * TStat_p;

            TStat_p = (SecY_SA_Stat_E_t *)TC_Transform_p->TransformStat_p;

            if (Stat.OutOctetsEncryptedProtected.Lo !=
                TStat_p->OutOctetsEncryptedProtected.Lo)
            {
                LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                         "\tOutOctetsEncryptedProtected.Lo %d, expected %d.\n",
                         Stat.OutOctetsEncryptedProtected.Lo,
                         TStat_p->OutOctetsEncryptedProtected.Lo);
                fSuccess = false;
            }

            if (Stat.OutOctetsEncryptedProtected.Hi !=
                TStat_p->OutOctetsEncryptedProtected.Hi)
            {
                LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                         "\tOutOctetsEncryptedProtected.Hi %d, expected %d.\n",
                         Stat.OutOctetsEncryptedProtected.Hi,
                         TStat_p->OutOctetsEncryptedProtected.Hi);
                fSuccess = false;
            }

            if (Stat.OutPktsEncryptedProtected.Lo !=
                    TStat_p->OutPktsEncryptedProtected.Lo)
            {
                LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                         "\tOutPktsEncryptedProtected.Lo %d, expected %d.\n",
                         Stat.OutPktsEncryptedProtected.Lo,
                         TStat_p->OutPktsEncryptedProtected.Lo);
                fSuccess = false;
            }

            if (Stat.OutPktsEncryptedProtected.Hi !=
                TStat_p->OutPktsEncryptedProtected.Hi)
            {
                LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                         "\tOutPktsEncryptedProtected.Hi %d, expected %d.\n",
                         Stat.OutPktsEncryptedProtected.Hi,
                         TStat_p->OutPktsEncryptedProtected.Hi);
                fSuccess = false;
            }

            if (Stat.OutPktsTooLong.Lo != TStat_p->OutPktsTooLong.Lo)
            {
                LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                         "\tOutPktsTooLong.Lo %d, expected %d.\n",
                         Stat.OutPktsTooLong.Lo,
                         TStat_p->OutPktsTooLong.Lo);
                fSuccess = false;
            }

            if (Stat.OutPktsTooLong.Hi != TStat_p->OutPktsTooLong.Hi)
            {
                LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                         "\tOutPktsTooLong.Hi %d, expected %d.\n",
                         Stat.OutPktsTooLong.Hi,
                         TStat_p->OutPktsTooLong.Hi);
                fSuccess = false;
            }

            if (Stat.OutPktsSANotInUse.Lo != TStat_p->OutPktsSANotInUse.Lo)
            {
                LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                         "\tOutPktsSANotInUse.Lo %d, expected %d.\n",
                         Stat.OutPktsSANotInUse.Lo,
                         TStat_p->OutPktsSANotInUse.Lo);
                fSuccess = false;
            }

            if (Stat.OutPktsSANotInUse.Hi != TStat_p->OutPktsSANotInUse.Hi)
            {
                LOG_CRIT("TEST_MACSEC: Failed, SA statistics update,\n"
                         "\tOutPktsSANotInUse.Hi %d, expected %d.\n",
                         Stat.OutPktsSANotInUse.Hi,
                         TStat_p->OutPktsSANotInUse.Hi);
                fSuccess = false;
            }

            if (Stat.OutPktsEncryptedProtected.Lo != 0)
            {
                SecY_Rc = SecY_SA_Statistics_E_Get(TestConf_p->DeviceId,
                                                   Tr_Admin_p->TransformHandle,
                                                   &Stat,
                                                   true);
                if (SecY_Rc != SECY_STATUS_OK)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Statistics_I_Get()=%d\n",
                             SecY_Rc);
                    fSuccess = false;
                    goto func_return;
                }
                if (Stat.OutPktsEncryptedProtected.Lo != 0)
                {
                    LOG_CRIT("TEST_MACSEC: Failded to clear SA statistics\n");
                    fSuccess = false;
                    goto func_return;
                }
            }
            if (TestConf_p->fVerbose)
            {
                Log_FormattedMessage(
                    "TEST_MACSEC: Egress SA statistics test %s.\n",
                    fSuccess ? "passed" : "failed");
            }
        }
    }
#endif /* TEST_MACSEC_MODE_EGRESS */

func_return:

    return fSuccess;
}


/*----------------------------------------------------------------------------
 * test_macsec_transform_statistics_test
 */
bool
test_macsec_transform_statistics_test(
        const Test_Case_ConfParams_t * TestConf_p,
        const Test_Case_Record_t * TestRec_p,
        Test_Transform_t * Tr_Admin_p)
{
    bool fSuccess = true;
    unsigned int i;
    Test_Case_Transform_t * TC_Transform_p = TestRec_p->TransformData_p;
    Test_Transform_t *TR_Admin_p = Tr_Admin_p;

    if (TC_Transform_p != NULL)
    {
        for (i = 0; i < TestRec_p->TransformCount; i++)
        {
            if (!test_macsec_single_transform_statistics_test(TestConf_p,
                                                              TC_Transform_p,
                                                              TR_Admin_p))
            {
                /* Error(s) is already logged */
               fSuccess = false;
            }

            TR_Admin_p++;               /* Next transform administration entry */
            TC_Transform_p++;           /* Next transform record */
        }
    }

    return fSuccess;
}


/*----------------------------------------------------------------------------
 * test_macsec_SecY_vPort_statistics
 */
bool
test_macsec_SecY_vPort_statistics(
        const Test_Case_ConfParams_t * TestConf_p,
        const Test_Case_Record_t * TestRec_p,
        const unsigned int vPortToUseAsDefault,
        const Test_Case_vPortStat_t * vPortStatisticsToUse_p)
{
    Test_Case_vPortStat_t * vPortStatistics_p = NULL;
    bool fSuccess = true;
    unsigned int i = 1;

    if (vPortStatisticsToUse_p != NULL)
    {
        vPortStatistics_p = (Test_Case_vPortStat_t *)
                            test_macsec_discard_const(vPortStatisticsToUse_p);
    }
    else if ((TestRec_p != NULL) &&
             (TestRec_p->vPortStatistis_p != NULL))
    {
        vPortStatistics_p = TestRec_p->vPortStatistis_p;
        i = TestRec_p->vPortStatistisCount;
    }

    for (; i != 0; i--)
    {
        SecY_Status_t SecY_Rc;
        unsigned int vPort;

        if (vPortStatistics_p != NULL)
        {
            vPort = vPortStatistics_p->vPort;
        }
        else
        {
            vPort = vPortToUseAsDefault;
        }

#ifdef TEST_MACSEC_MODE_EGRESS
        /* Egress vPort statistics test */
        if (!TestConf_p->fIngress)
        {
            {
                SecY_SecY_Stat_E_t SecYStats;
                SecY_SecY_Stat_E_t * Stats_p = NULL;

                ZEROINIT(SecYStats);

                if ((vPortStatistics_p != NULL) &&
                    (vPortStatistics_p->SecYStat_p != NULL))
                {
                    Stats_p = &vPortStatistics_p->SecYStat_p->Egress;
                }

                /* Assume that any counters are less than 2^32, so we can just display
                   the low halves of the 64-bit counters */
                SecY_Rc = SecY_SecY_Statistics_E_Get(TestConf_p->DeviceId,
                                                     vPort,
                                                     &SecYStats,
                                                     true); /* Sync with device */
                if (SecY_Rc != SECY_STATUS_OK)
                {
                    LOG_CRIT(
                        "TEST_MACSEC: Failed, SecY_SecY_Statistics_E_Get(%d)=%d\n",
                        vPort, SecY_Rc);
                    fSuccess = false;
                    goto FuncEgressExit;
                }

                if (TestConf_p->fVerbose)
                {
                    Log_FormattedMessage(
                        "TEST_MACSEC: Egress SecY(%d) Statistics:\n"
                        "\tTransform E r r o r Packets Counter: %u\n"
                        "\tEgress Controlled Packets Counter:   %u\n"
                        "\tEgress Untagged Packets Counter:     %u\n",
                        vPort,
                        SecYStats.OutPktsTransformError.Lo,
                        SecYStats.OutPktsControl.Lo,
                        SecYStats.OutPktsUntagged.Lo);
                }

                if (Stats_p != NULL)
                {
                    bool fSuccessSecY = true;

                    /* Egress Transform error packets */
                    if (SecYStats.OutPktsTransformError.Lo !=
                        Stats_p->OutPktsTransformError.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, SecY(%d) statistics update,\n"
                            "\tOutPktsTransformError.Lo=%u, expected %u.\n",
                            vPort,
                            SecYStats.OutPktsTransformError.Lo,
                            Stats_p->OutPktsTransformError.Lo);
                        fSuccessSecY = false;
                    }
                    if (SecYStats.OutPktsTransformError.Hi !=
                        Stats_p->OutPktsTransformError.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, SecY(%d) statistics update,\n"
                            "\tOutPktsTransformError.Hi=%u, expected %u.\n",
                            vPort,
                            SecYStats.OutPktsTransformError.Hi,
                            Stats_p->OutPktsTransformError.Hi);
                        fSuccessSecY = false;
                    }

                    /* Egress Out control packets */
                    if (SecYStats.OutPktsControl.Lo !=
                        Stats_p->OutPktsControl.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, SecY(%d) statistics update,\n"
                            "\tOutPktsControl.Lo=%u, expected %u.\n",
                            vPort,
                            SecYStats.OutPktsControl.Lo,
                            Stats_p->OutPktsControl.Lo);
                        fSuccessSecY = false;
                    }
                    if (SecYStats.OutPktsControl.Hi !=
                        Stats_p->OutPktsControl.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, SecY(%d) statistics update,\n"
                            "\tOutPktsControl.Hi=%u, expected %u.\n",
                            vPort,
                            SecYStats.OutPktsControl.Hi,
                            Stats_p->OutPktsControl.Hi);
                        fSuccessSecY = false;
                    }

                    /* Egress Out untaggged packets */
                    if (SecYStats.OutPktsUntagged.Lo !=
                        Stats_p->OutPktsUntagged.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, SecY(%d) statistics update,\n"
                            "\tOutPktsUntagged.Lo=%u, expected %u.\n",
                            vPort,
                            SecYStats.OutPktsUntagged.Lo,
                            Stats_p->OutPktsUntagged.Lo);
                        fSuccessSecY = false;
                    }
                    if (SecYStats.OutPktsUntagged.Hi !=
                        Stats_p->OutPktsUntagged.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, SecY(%d) statistics update,\n"
                            "\tOutPktsUntagged.Hi=%u, expected %u.\n",
                            vPort,
                            SecYStats.OutPktsUntagged.Hi,
                            Stats_p->OutPktsUntagged.Hi);
                        fSuccessSecY = false;
                    }

                    if (TestConf_p->fVerbose)
                    {
                        Log_FormattedMessage(
                            "TEST_MACSEC: Egress SecY(%d) statistics test %s.\n",
                            vPort,
                            fSuccessSecY ? "passed" : "failed");
                    }
                    fSuccess &= fSuccessSecY;
                }
            }

            {
                SecY_Ifc_Stat_E_t IfcStats;
                SecY_Ifc_Stat_E_t * Stats_p = NULL;

                ZEROINIT(IfcStats);

                if ((vPortStatistics_p != NULL) &&
                    (vPortStatistics_p->SecYStat_p != NULL))
                {
                    Stats_p = &vPortStatistics_p->IfcStat_p->Egress;
                }

                /* Read the IFC/IFC1 ingress statistics counters. */
                /* Sync with the SecY device to get the exact counters values */
                SecY_Rc = SecY_Ifc_Statistics_E_Get(TestConf_p->DeviceId,
                                                    vPort,
                                                    &IfcStats,
                                                    true);
                if (SecY_Rc != SECY_STATUS_OK)
                {
                    LOG_CRIT(
                        "TEST_MACSEC: Failed, SecY_Ifc_Statistics_E_Get(%d)=%d\n",
                        vPort, SecY_Rc);
                    fSuccess = false;
                    goto FuncEgressExit;
                }

                /* Assume that any counters are less than 2^32, so we can just display */
                /* the low halves of the 64-bit counters */
                Log_FormattedMessage(
                    "TEST_MACSEC: Egress IFC/IFC1(%d) Statistics:\n"
                    "\tCommon Counters:\n"
                    "\t  Octects:             %u\n"
                    "\tUncontrolled Counters:\n"
                    "\t  Octects:             %u\n"
                    "\t  Packets Unicast:     %u\n"
                    "\t  Packets Multicast:   %u\n"
                    "\t  Packets Broadcast:   %u\n"
                    "\tControlled Counters:\n"
                    "\t  Octects:             %u\n"
                    "\t  Packets Unicast:     %u\n"
                    "\t  Packets Multicast:   %u\n"
                    "\t  Packets Broadcast:   %u\n",
                    vPort,
                    IfcStats.OutOctetsCommon.Lo,
                    IfcStats.OutOctetsUncontrolled.Lo,
                    IfcStats.OutPktsUnicastUncontrolled.Lo,
                    IfcStats.OutPktsMulticastUncontrolled.Lo,
                    IfcStats.OutPktsBroadcastUncontrolled.Lo,
                    IfcStats.OutOctetsControlled.Lo,
                    IfcStats.OutPktsUnicastControlled.Lo,
                    IfcStats.OutPktsMulticastControlled.Lo,
                    IfcStats.OutPktsBroadcastControlled.Lo);

                if (Stats_p != NULL)
                {
                    bool fSuccessIfc = true;

                    /* Test IFC/IFC1 Ingress statistics */
                    if (IfcStats.OutOctetsCommon.Lo !=
                        Stats_p->OutOctetsCommon.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC(%d) statistics update,\n"
                            "\tOutOctetsCommon.Lo=%u, expected %u.\n",
                            vPort,
                            IfcStats.OutOctetsCommon.Lo,
                            Stats_p->OutOctetsCommon.Lo);
                        fSuccessIfc = false;
                    }
                    if (IfcStats.OutOctetsCommon.Hi !=
                        Stats_p->OutOctetsCommon.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC(%d) statistics update,\n"
                            "\tOutOctetsCommon.Hi=%u, expected %u.\n",
                            vPort,
                            IfcStats.OutOctetsCommon.Hi,
                            Stats_p->OutOctetsCommon.Hi);
                        fSuccessIfc = false;
                    }

                    if (IfcStats.OutOctetsUncontrolled.Lo !=
                        Stats_p->OutOctetsUncontrolled.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC(%d) statistics update,\n"
                            "\tOutOctetsUncontrolled.Lo=%u, expected %u.\n",
                            vPort,
                            IfcStats.OutOctetsUncontrolled.Lo,
                            Stats_p->OutOctetsUncontrolled.Lo);
                        fSuccessIfc = false;
                    }
                    if (IfcStats.OutOctetsUncontrolled.Hi !=
                        Stats_p->OutOctetsUncontrolled.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC(%d) statistics update,\n"
                            "\tOutOctetsUncontrolled.Hi=%u, expected %u.\n",
                            vPort,
                            IfcStats.OutOctetsUncontrolled.Hi,
                            Stats_p->OutOctetsUncontrolled.Hi);
                        fSuccessIfc = false;
                    }

                    if (IfcStats.OutPktsUnicastUncontrolled.Lo !=
                        Stats_p->OutPktsUnicastUncontrolled.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC(%d) statistics update,\n"
                            "\tOutPktsUnicastUncontrolled.Lo=%u, expected %u.\n",
                            vPort,
                            IfcStats.OutPktsUnicastUncontrolled.Lo,
                            Stats_p->OutPktsUnicastUncontrolled.Lo);
                        fSuccessIfc = false;
                    }
                    if (IfcStats.OutPktsUnicastUncontrolled.Hi !=
                        Stats_p->OutPktsUnicastUncontrolled.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC(%d) statistics update,\n"
                            "\tOutPktsUnicastUncontrolled.Hi=%u, expected %u.\n",
                            vPort,
                            IfcStats.OutPktsUnicastUncontrolled.Hi,
                            Stats_p->OutPktsUnicastUncontrolled.Hi);
                        fSuccessIfc = false;
                    }

                    if (IfcStats.OutPktsMulticastUncontrolled.Lo !=
                        Stats_p->OutPktsMulticastUncontrolled.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC(%d) statistics update,\n"
                            "\tOutPktsMulticastUncontrolled.Lo=%u, expected %u.\n",
                            vPort,
                            IfcStats.OutPktsMulticastUncontrolled.Lo,
                            Stats_p->OutPktsMulticastUncontrolled.Lo);
                        fSuccessIfc = false;
                    }
                    if (IfcStats.OutPktsMulticastUncontrolled.Hi !=
                        Stats_p->OutPktsMulticastUncontrolled.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC(%d) statistics update,\n"
                            "\tOutPktsMulticastUncontrolled.Hi=%u, expected %u.\n",
                            vPort,
                            IfcStats.OutPktsMulticastUncontrolled.Hi,
                            Stats_p->OutPktsMulticastUncontrolled.Hi);
                        fSuccessIfc = false;
                    }

                    if (IfcStats.OutPktsBroadcastUncontrolled.Lo !=
                        Stats_p->OutPktsBroadcastUncontrolled.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC(%d) statistics update,\n"
                            "\tOutPktsBroadcastUncontrolled.Lo=%u, expected %u.\n",
                            vPort,
                            IfcStats.OutPktsBroadcastUncontrolled.Lo,
                            Stats_p->OutPktsBroadcastUncontrolled.Lo);
                        fSuccessIfc = false;
                    }
                    if (IfcStats.OutPktsBroadcastUncontrolled.Hi !=
                        Stats_p->OutPktsBroadcastUncontrolled.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC(%d) statistics update,\n"
                            "\tOutPktsBroadcastUncontrolled.Hi=%u, expected %u.\n",
                            vPort,
                            IfcStats.OutPktsBroadcastUncontrolled.Hi,
                            Stats_p->OutPktsBroadcastUncontrolled.Hi);
                        fSuccessIfc = false;
                    }

                    if (IfcStats.OutOctetsControlled.Lo !=
                        Stats_p->OutOctetsControlled.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC1(%d) statistics update,\n"
                            "\tOutOctetsControlled.Lo=%u, expected %u.\n",
                            vPort,
                            IfcStats.OutOctetsControlled.Lo,
                            Stats_p->OutOctetsControlled.Lo);
                        fSuccessIfc = false;
                    }
                    if (IfcStats.OutOctetsControlled.Hi !=
                        Stats_p->OutOctetsControlled.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC1(%d) statistics update,\n"
                            "\tOutOctetsControlled.Hi=%u, expected %u.\n",
                            vPort,
                            IfcStats.OutOctetsControlled.Hi,
                            Stats_p->OutOctetsControlled.Hi);
                        fSuccessIfc = false;
                    }

                    if (IfcStats.OutPktsUnicastControlled.Lo !=
                        Stats_p->OutPktsUnicastControlled.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC1(%d) statistics update,\n"
                            "\tOutPktsUnicastControlled.Lo=%u, expected %u.\n",
                            vPort,
                            IfcStats.OutPktsUnicastControlled.Lo,
                            Stats_p->OutPktsUnicastControlled.Lo);
                        fSuccessIfc = false;
                    }
                    if (IfcStats.OutPktsUnicastControlled.Hi !=
                        Stats_p->OutPktsUnicastControlled.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC1(%d) statistics update,\n"
                            "\tOutPktsUnicastControlled.Hi=%u, expected %u.\n",
                            vPort,
                            IfcStats.OutPktsUnicastControlled.Hi,
                            Stats_p->OutPktsUnicastControlled.Hi);
                        fSuccessIfc = false;
                    }

                    if (IfcStats.OutPktsMulticastControlled.Lo !=
                        Stats_p->OutPktsMulticastControlled.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC1(%d) statistics update,\n"
                            "\tOutPktsMulticastControlled.Lo=%u, expected %u.\n",
                            vPort,
                            IfcStats.OutPktsMulticastControlled.Lo,
                            Stats_p->OutPktsMulticastControlled.Lo);
                        fSuccessIfc = false;
                    }
                    if (IfcStats.OutPktsMulticastControlled.Hi !=
                        Stats_p->OutPktsMulticastControlled.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC1(%d) statistics update,\n"
                            "\tOutPktsMulticastControlled.Hi=%u, expected %u.\n",
                            vPort,
                            IfcStats.OutPktsMulticastControlled.Hi,
                            Stats_p->OutPktsMulticastControlled.Hi);
                        fSuccessIfc = false;
                    }

                    if (IfcStats.OutPktsBroadcastControlled.Lo !=
                        Stats_p->OutPktsBroadcastControlled.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC1(%d) statistics update,\n"
                            "\tOutPktsBroadcastControlled.Lo=%u, expected %u.\n",
                            vPort,
                            IfcStats.OutPktsBroadcastControlled.Lo,
                            Stats_p->OutPktsBroadcastControlled.Lo);
                        fSuccessIfc = false;
                    }
                    if (IfcStats.OutPktsBroadcastControlled.Hi !=
                        Stats_p->OutPktsBroadcastControlled.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC1(%d) statistics update,\n"
                            "\tOutPktsBroadcastControlled.Hi=%u, expected %u.\n",
                            vPort,
                            IfcStats.OutPktsBroadcastControlled.Hi,
                            Stats_p->OutPktsBroadcastControlled.Hi);
                        fSuccessIfc = false;
                    }

                    if (TestConf_p->fVerbose)
                    {
                        Log_FormattedMessage(
                            "TEST_MACSEC: Egress IFC/IFC1(%d) statistics test %s.\n",
                            vPort,
                            fSuccessIfc ? "passed" : "failed");
                    }
                    fSuccess &= fSuccessIfc;
                }
            }
        }
FuncEgressExit:
#endif /* TEST_MACSEC_MODE_EGRESS */

#ifdef TEST_MACSEC_MODE_INGRESS
        /* Ingress vPort statistics test */
        if (TestConf_p->fIngress)
        {
            {
                SecY_SecY_Stat_I_t SecYStats;
                SecY_SecY_Stat_I_t * Stats_p = NULL;

                ZEROINIT(SecYStats);

                if ((vPortStatistics_p != NULL) &&
                    (vPortStatistics_p->SecYStat_p != NULL))
                {
                    Stats_p = &vPortStatistics_p->SecYStat_p->Ingress;
                }

                /* Assume that any counters are less than 2^32, so we can just display
                   the low halves of the 64-bit counters */
                SecY_Rc = SecY_SecY_Statistics_I_Get(TestConf_p->DeviceId,
                                                     vPort,
                                                     &SecYStats,
                                                     true); /* Sync with device */
                if (SecY_Rc != SECY_STATUS_OK)
                {
                    LOG_CRIT(
                        "TEST_MACSEC: Failed, SecY_SecY_Statistics_I_Get(%d)=%d\n",
                        vPort, SecY_Rc);
                    fSuccess = false;
                    goto FuncIngressExit;
                }

                if (TestConf_p->fVerbose)
                {
                    Log_FormattedMessage(
                            "TEST_MACSEC: Ingress SecY(%d) Statistics:\n"
                            "\tTransform E r r o r Packets Counter:    %u\n"
                            "\tIngress Controlled Packets Counter:     %u\n"
                            "\tIngress Untagged Packets Counter:       %u\n"
                            "\tIngress No Tag Packets Counter:         %u\n"
                            "\tIngress Bad Tag Packets Counter:        %u\n"
                            "\tIngress No SCI Packets Counter:         %u\n"
                            "\tIngress Unknown SCI Packets Counter:    %u\n"
                            "\tIngress Tagged Control Packets Counter: %u\n",
                            vPort,
                            SecYStats.InPktsTransformError.Lo,
                            SecYStats.InPktsControl.Lo,
                            SecYStats.InPktsUntagged.Lo,
                            SecYStats.InPktsNoTag.Lo,
                            SecYStats.InPktsBadTag.Lo,
                            SecYStats.InPktsNoSCI.Lo,
                            SecYStats.InPktsUnknownSCI.Lo,
                            SecYStats.InPktsTaggedCtrl.Lo);
                }

                if (Stats_p != NULL)
                {
                    bool fSuccessSecY = true;

                    /* Transform error Packets Counter */
                    if (SecYStats.InPktsTransformError.Lo !=
                        Stats_p->InPktsTransformError.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, SecY(%d) statistics update,\n"
                            "\tInPktsTransformError.Lo=%u, expected %u.\n",
                            vPort,
                            SecYStats.InPktsTransformError.Lo,
                            Stats_p->InPktsTransformError.Lo);
                        fSuccessSecY = false;
                    }
                    if (SecYStats.InPktsTransformError.Hi !=
                        Stats_p->InPktsTransformError.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, SecY(%d) statistics update,\n"
                            "\tInPktsTransformError.Hi=%u, expected %u.\n",
                            vPort,
                            SecYStats.InPktsTransformError.Hi,
                            Stats_p->InPktsTransformError.Hi);
                        fSuccessSecY = false;
                    }

                    /* Ingress Control Packets Counter */
                    if (SecYStats.InPktsControl.Lo !=
                        Stats_p->InPktsControl.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, SecY(%d) statistics update,\n"
                            "\tInPktsControl.Lo=%u, expected %u.\n",
                            vPort,
                            SecYStats.InPktsControl.Lo,
                            Stats_p->InPktsControl.Lo);
                        fSuccessSecY = false;
                    }
                    if (SecYStats.InPktsControl.Hi !=
                        Stats_p->InPktsControl.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, SecY(%d) statistics update,\n"
                            "\tInPktsControl.Hi=%u, expected %u.\n",
                            vPort,
                            SecYStats.InPktsControl.Hi,
                            Stats_p->InPktsControl.Hi);
                        fSuccessSecY = false;
                    }

                    /* Ingress untagged Packets Counter */
                    if (SecYStats.InPktsUntagged.Lo !=
                        Stats_p->InPktsUntagged.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, SecY(%d) statistics update,\n"
                            "\tInPktsUntagged.Lo=%u, expected %u.\n",
                            vPort,
                            SecYStats.InPktsUntagged.Lo,
                            Stats_p->InPktsUntagged.Lo);
                        fSuccessSecY = false;
                    }
                    if (SecYStats.InPktsUntagged.Hi !=
                        Stats_p->InPktsUntagged.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, SecY(%d) statistics update,\n"
                            "\tInPktsUntagged.Hi=%u, expected %u.\n",
                            vPort,
                            SecYStats.InPktsUntagged.Hi,
                            Stats_p->InPktsUntagged.Hi);
                        fSuccessSecY = false;
                    }

                    /* Ingress No tag Packets Counter */
                    if (SecYStats.InPktsNoTag.Lo != Stats_p->InPktsNoTag.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, SecY(%d) statistics update,\n"
                            "\tInPktsNoTag.Lo=%u, expected %u.\n",
                            vPort,
                            SecYStats.InPktsNoTag.Lo,
                            Stats_p->InPktsNoTag.Lo);
                        fSuccessSecY = false;
                    }
                    if (SecYStats.InPktsNoTag.Hi != Stats_p->InPktsNoTag.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, SecY(%d) statistics update,\n"
                            "\tInPktsNoTag.Lo=%u, expected %u.\n",
                            vPort,
                            SecYStats.InPktsNoTag.Hi,
                            Stats_p->InPktsNoTag.Hi);
                        fSuccessSecY = false;
                    }

                    /* Ingress Bad Tag Packets Counter */
                    if (SecYStats.InPktsBadTag.Lo != Stats_p->InPktsBadTag.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, SecY(%d) statistics update,\n"
                            "\tInPktsBadTag.Lo=%u, expected %u.\n",
                            vPort,
                            SecYStats.InPktsBadTag.Lo,
                            Stats_p->InPktsBadTag.Lo);
                        fSuccessSecY = false;
                    }
                    if (SecYStats.InPktsBadTag.Hi != Stats_p->InPktsBadTag.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, SecY(%d) statistics update,\n"
                            "\tInPktsBadTag.Hi=%u, expected %u.\n",
                            vPort,
                            SecYStats.InPktsBadTag.Hi,
                            Stats_p->InPktsBadTag.Hi);
                        fSuccessSecY = false;
                    }

                    /* Ingress No SCI Packets Counter */
                    if (SecYStats.InPktsNoSCI.Lo != Stats_p->InPktsNoSCI.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, SecY(%d) statistics update,\n"
                            "\tInPktsNoSCI.Lo=%u, expected %u.\n",
                            vPort,
                            SecYStats.InPktsNoSCI.Lo,
                            Stats_p->InPktsNoSCI.Lo);
                        fSuccessSecY = false;
                    }
                    if (SecYStats.InPktsNoSCI.Hi != Stats_p->InPktsNoSCI.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, SecY(%d) statistics update,\n"
                            "\tInPktsNoSCI.Hi=%u, expected %u.\n",
                            vPort,
                            SecYStats.InPktsNoSCI.Hi,
                            Stats_p->InPktsNoSCI.Hi);
                        fSuccessSecY = false;
                    }


                    /* Ingress Unknown SCI Packets Counter */
                    if (SecYStats.InPktsUnknownSCI.Lo !=
                        Stats_p->InPktsUnknownSCI.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, SecY(%d) statistics update,\n"
                            "\tInPktsUnknownSCI.Lo=%u, expected %u.\n",
                            vPort,
                            SecYStats.InPktsUnknownSCI.Lo,
                            Stats_p->InPktsUnknownSCI.Lo);
                        fSuccessSecY = false;
                    }
                    if (SecYStats.InPktsUnknownSCI.Hi !=
                        Stats_p->InPktsUnknownSCI.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, SecY(%d) statistics update,\n"
                            "\tInPktsUnknownSCI.Hi=%u, expected %u.\n",
                            vPort,
                            SecYStats.InPktsUnknownSCI.Hi,
                            Stats_p->InPktsUnknownSCI.Hi);
                        fSuccessSecY = false;
                    }

                    /* Ingress Tagged Control Packets Counter */
                    if (SecYStats.InPktsTaggedCtrl.Lo !=
                        Stats_p->InPktsTaggedCtrl.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, SecY(%d) statistics update,\n"
                            "\tInPktsTaggedCtrl.Lo=%u, expected %u.\n",
                            vPort,
                            SecYStats.InPktsTaggedCtrl.Lo,
                            Stats_p->InPktsTaggedCtrl.Lo);
                        fSuccessSecY = false;
                    }
                    if (SecYStats.InPktsTaggedCtrl.Hi !=
                        Stats_p->InPktsTaggedCtrl.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, SecY(%d) statistics update,\n"
                            "\tInPktsTaggedCtrl.Hi=%u, expected %u.\n",
                            vPort,
                            SecYStats.InPktsTaggedCtrl.Hi,
                            Stats_p->InPktsTaggedCtrl.Hi);
                        fSuccessSecY = false;
                    }

                    if (TestConf_p->fVerbose && fSuccess)
                    {
                        Log_FormattedMessage(
                            "TEST_MACSEC: Ingress SecY(%d) statistics test %s.\n",
                            vPort,
                            fSuccessSecY ? "passed" : "failed");
                    }

                    fSuccess &= fSuccessSecY;
                }
            }

            {
                SecY_Ifc_Stat_I_t IfcStats;
                SecY_Ifc_Stat_I_t * Stats_p = NULL;

                ZEROINIT(IfcStats);

                if ((vPortStatistics_p != NULL) &&
                    (vPortStatistics_p->SecYStat_p != NULL))
                {
                    Stats_p = &vPortStatistics_p->IfcStat_p->Ingress;
                }

                /* Read the IFC/IFC1 ingress statistics counters. */
                /* Sync with the SecY device to get the exact counters values */
                SecY_Rc = SecY_Ifc_Statistics_I_Get(TestConf_p->DeviceId,
                                                    vPort,
                                                    &IfcStats,
                                                    true);
                if (SecY_Rc != SECY_STATUS_OK)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, SecY_Ifc_Statistics_I_Get(%d)=%d\n",
                             vPort, SecY_Rc);
                    fSuccess = false;
                    goto FuncIngressExit;
                }

                /* Assume that any counters are less than 2^32, so we can just display */
                /* the low halves of the 64-bit counters */
                Log_FormattedMessage(
                    "TEST_MACSEC: Ingress IFC/IFC1(%d) Statistics:\n"
                    "\tUncontrolled Counters:\n"
                    "\t  Octects:             %u\n"
                    "\t  Packets Unicast:     %u\n"
                    "\t  Packets Multicast:   %u\n"
                    "\t  Packets Broadcast:   %u\n"
                    "\tControlled Counters:\n"
                    "\t  Octects:             %u\n"
                    "\t  Packets Unicast:     %u\n"
                    "\t  Packets Multicast:   %u\n"
                    "\t  Packets Broadcast:   %u\n",
                    vPort,
                    IfcStats.InOctetsUncontrolled.Lo,
                    IfcStats.InPktsUnicastUncontrolled.Lo,
                    IfcStats.InPktsMulticastUncontrolled.Lo,
                    IfcStats.InPktsBroadcastUncontrolled.Lo,
                    IfcStats.InOctetsControlled.Lo,
                    IfcStats.InPktsUnicastControlled.Lo,
                    IfcStats.InPktsMulticastControlled.Lo,
                    IfcStats.InPktsBroadcastControlled.Lo);

                if (Stats_p != NULL)
                {
                    bool fSuccessIfc = true;

                    /* Test IFC/IFC1 Ingress statistics */
                    if (IfcStats.InOctetsUncontrolled.Lo !=
                        Stats_p->InOctetsUncontrolled.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC(%d) statistics update,\n"
                            "\tInOctetsUncontrolled.Lo=%u, expected %u.\n",
                            vPort,
                            IfcStats.InOctetsUncontrolled.Lo,
                            Stats_p->InOctetsUncontrolled.Lo);
                        fSuccessIfc = false;
                    }
                    if (IfcStats.InOctetsUncontrolled.Hi !=
                        Stats_p->InOctetsUncontrolled.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC(%d) statistics update,\n"
                            "\tInOctetsUncontrolled.Hi=%u, expected %u.\n",
                            vPort,
                            IfcStats.InOctetsUncontrolled.Hi,
                            Stats_p->InOctetsUncontrolled.Hi);
                        fSuccessIfc = false;
                    }

                    if (IfcStats.InPktsUnicastUncontrolled.Lo !=
                        Stats_p->InPktsUnicastUncontrolled.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC(%d) statistics update,\n"
                            "\tInPktsUnicastUncontrolled.Lo=%u, expected %u.\n",
                            vPort,
                            IfcStats.InPktsUnicastUncontrolled.Lo,
                            Stats_p->InPktsUnicastUncontrolled.Lo);
                        fSuccessIfc = false;
                    }
                    if (IfcStats.InPktsUnicastUncontrolled.Hi !=
                        Stats_p->InPktsUnicastUncontrolled.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC(%d) statistics update,\n"
                            "\tInPktsUnicastUncontrolled.Hi=%u, expected %u.\n",
                            vPort,
                            IfcStats.InPktsUnicastUncontrolled.Hi,
                            Stats_p->InPktsUnicastUncontrolled.Hi);
                        fSuccessIfc = false;
                    }

                    if (IfcStats.InPktsMulticastUncontrolled.Lo !=
                        Stats_p->InPktsMulticastUncontrolled.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC(%d) statistics update,\n"
                            "\tInPktsMulticastUncontrolled.Lo=%u, expected %u.\n",
                            vPort,
                            IfcStats.InPktsMulticastUncontrolled.Lo,
                            Stats_p->InPktsMulticastUncontrolled.Lo);
                        fSuccessIfc = false;
                    }
                    if (IfcStats.InPktsMulticastUncontrolled.Hi !=
                        Stats_p->InPktsMulticastUncontrolled.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC(%d) statistics update,\n"
                            "\tInPktsMulticastUncontrolled.Hi=%u, expected %u.\n",
                            vPort,
                            IfcStats.InPktsMulticastUncontrolled.Hi,
                            Stats_p->InPktsMulticastUncontrolled.Hi);
                        fSuccessIfc = false;
                    }

                    if (IfcStats.InPktsBroadcastUncontrolled.Lo !=
                        Stats_p->InPktsBroadcastUncontrolled.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC(%d) statistics update,\n"
                            "\tInPktsBroadcastUncontrolled.Lo=%u, expected %u.\n",
                            vPort,
                            IfcStats.InPktsBroadcastUncontrolled.Lo,
                            Stats_p->InPktsBroadcastUncontrolled.Lo);
                        fSuccessIfc = false;
                    }
                    if (IfcStats.InPktsBroadcastUncontrolled.Hi !=
                        Stats_p->InPktsBroadcastUncontrolled.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC(%d) statistics update,\n"
                            "\tInPktsBroadcastUncontrolled.Hi=%u, expected %u.\n",
                            vPort,
                            IfcStats.InPktsBroadcastUncontrolled.Hi,
                            Stats_p->InPktsBroadcastUncontrolled.Hi);
                        fSuccessIfc = false;
                    }

                    if (IfcStats.InOctetsControlled.Lo !=
                        Stats_p->InOctetsControlled.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC1(%d) statistics update,\n"
                            "\tInOctetsControlled.Lo=%u, expected %u.\n",
                            vPort,
                            IfcStats.InOctetsControlled.Lo,
                            Stats_p->InOctetsControlled.Lo);
                        fSuccessIfc = false;
                    }
                    if (IfcStats.InOctetsControlled.Hi !=
                        Stats_p->InOctetsControlled.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC1(%d) statistics update,\n"
                            "\tInOctetsControlled.Hi=%u, expected %u.\n",
                            vPort,
                            IfcStats.InOctetsControlled.Hi,
                            Stats_p->InOctetsControlled.Hi);
                        fSuccessIfc = false;
                    }

                    if (IfcStats.InPktsUnicastControlled.Lo !=
                        Stats_p->InPktsUnicastControlled.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC1(%d) statistics update,\n"
                            "\tInPktsUnicastControlled.Lo=%u, expected %u.\n",
                            vPort,
                            IfcStats.InPktsUnicastControlled.Lo,
                            Stats_p->InPktsUnicastControlled.Lo);
                        fSuccessIfc = false;
                    }
                    if (IfcStats.InPktsUnicastControlled.Hi !=
                        Stats_p->InPktsUnicastControlled.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC1(%d) statistics update,\n"
                            "\tInPktsUnicastControlled.Hi=%u, expected %u.\n",
                            vPort,
                            IfcStats.InPktsUnicastControlled.Hi,
                            Stats_p->InPktsUnicastControlled.Hi);
                        fSuccessIfc = false;
                    }

                    if (IfcStats.InPktsMulticastControlled.Lo !=
                        Stats_p->InPktsMulticastControlled.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC1(%d) statistics update,\n"
                            "\tInPktsMulticastControlled.Lo=%u, expected %u.\n",
                            vPort,
                            IfcStats.InPktsMulticastControlled.Lo,
                            Stats_p->InPktsMulticastControlled.Lo);
                        fSuccessIfc = false;
                    }
                    if (IfcStats.InPktsMulticastControlled.Hi !=
                        Stats_p->InPktsMulticastControlled.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC1(%d) statistics update,\n"
                            "\tInPktsMulticastControlled.Hi=%u, expected %u.\n",
                            vPort,
                            IfcStats.InPktsMulticastControlled.Hi,
                            Stats_p->InPktsMulticastControlled.Hi);
                        fSuccessIfc = false;
                    }

                    if (IfcStats.InPktsBroadcastControlled.Lo !=
                        Stats_p->InPktsBroadcastControlled.Lo)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC1(%d) statistics update,\n"
                            "\tInPktsBroadcastControlled.Lo=%u, expected %u.\n",
                            vPort,
                            IfcStats.InPktsBroadcastControlled.Lo,
                            Stats_p->InPktsBroadcastControlled.Lo);
                        fSuccessIfc = false;
                    }
                    if (IfcStats.InPktsBroadcastControlled.Hi !=
                        Stats_p->InPktsBroadcastControlled.Hi)
                    {
                        LOG_CRIT(
                            "TEST_MACSEC: Failed, IFC1(%d) statistics update,\n"
                            "\tInPktsBroadcastControlled.Hi=%u, expected %u.\n",
                            vPort,
                            IfcStats.InPktsBroadcastControlled.Hi,
                            Stats_p->InPktsBroadcastControlled.Hi);
                        fSuccessIfc = false;
                    }

                    if (TestConf_p->fVerbose)
                    {
                        Log_FormattedMessage(
                            "TEST_MACSEC: Ingress IFC/IFC1(%d) statistics test %s.\n",
                            vPort,
                            fSuccessIfc ? "passed" : "failed");
                    }

                    fSuccess &= fSuccessIfc;
                }
            }
        }
FuncIngressExit:
#endif /* TEST_MACSEC_MODE_INGRESS */

        if (vPortStatistics_p != NULL)
        {
            vPortStatistics_p++;
        }
    }

    return fSuccess;
}


/*----------------------------------------------------------------------------
 * test_macsec_channel_rules_update
 */
bool
test_macsec_channel_rules_update(
        const Test_Case_ConfParams_t * TestConf_p,
        const Test_Case_Record_t * TestRec_p)
{
    if (TestRec_p->ChannelRulesCount != 0 &&
        TestRec_p->ChannelRules_p != NULL)
    {
        unsigned int i;
        unsigned int MaxChannels;
        SecY_Status_t SecY_rc;
        Test_Case_Channel_Rules_t * Rule_p = TestRec_p->ChannelRules_p;

        SecY_rc = SecY_Device_Limits(TestConf_p->DeviceId,
                                     &MaxChannels, NULL, NULL, NULL);
        if (SecY_rc != SECY_STATUS_OK)
        {
            LOG_CRIT("TEST_MACSEC: Failed, SecY_Device_Limits()=%d\n", SecY_rc);
            return false;
        }

        for (i = 0; i < TestRec_p->ChannelRulesCount; i++)
        {
            if (Rule_p->SecTag_Rules_p != NULL && Rule_p->Channel < MaxChannels)
            {
                SecY_rc = SecY_Rules_SecTag_Update(TestConf_p->DeviceId,
                                                   Rule_p->Channel,
                                                   Rule_p->SecTag_Rules_p);
                if (SecY_rc != SECY_STATUS_OK)
                {
                    LOG_CRIT(
                        "TEST_MACSEC: Failed, SecY_Rules_SecTag_Update()=%d\n",
                        SecY_rc);
                    return false;
                }
            }
            Rule_p++;
        }

        Log_FormattedMessage("TEST_MACSEC: Installed channel rules\n");
    }

    return true;
}


/*----------------------------------------------------------------------------
 * test_macsec_secure_channel_rules_update
 */
bool
test_macsec_secure_channel_rules_update(
        const Test_Case_ConfParams_t * TestConf_p,
        const Test_Case_Record_t * TestRec_p)
{
    if (TestRec_p->SCRulesCount != 0 &&
        TestRec_p->SCRules_p != NULL)
    {
        unsigned int i;
        SecY_Status_t SecY_rc;
        Test_Case_SC_Rules_t * Rule_p = TestRec_p->SCRules_p;
        SecY_SC_Rule_MTUCheck_t MTURule;

        for (i = 0; i < TestRec_p->SCRulesCount; i++)
        {
            if (Rule_p->MTU_Rules_p != NULL)
            {
                SecY_rc = SecY_Rules_MTUCheck_Update(TestConf_p->DeviceId,
                                                     Rule_p->SecureChannel,
                                                     Rule_p->MTU_Rules_p);
                if (SecY_rc != SECY_STATUS_OK)
                {
                    LOG_CRIT(
                        "TEST_MACSEC: Failed, SecY_Rules_MTUCheck_Update()=%d\n",
                        SecY_rc);
                    return false;
                }

                /* Read updated MTU check rule back. */
                SecY_rc = SecY_Rules_MTUCheck_Get(TestConf_p->DeviceId,
                                                     Rule_p->SecureChannel,
                                                     &MTURule);
                if (SecY_rc != SECY_STATUS_OK)
                {
                    LOG_CRIT(
                        "TEST_MACSEC: Failed, SecY_Rules_MTUCheck_Get()=%d\n",
                        SecY_rc);
                    return false;
                }
                Log_FormattedMessage("TEST_MACSEC: MTU for channel %d set to %d, drop=%d\n",
                                    Rule_p->SecureChannel,
                                    MTURule.PacketMaxByteCount,
                                    MTURule.fOverSizeDrop);
                if (MTURule.PacketMaxByteCount != Rule_p->MTU_Rules_p->PacketMaxByteCount ||
                    MTURule.fOverSizeDrop != Rule_p->MTU_Rules_p->fOverSizeDrop)
                {
                    LOG_CRIT(
                        "TEST_MACSEC: Failed, read MTU not equal to what is set.\n");
                    return false;
                }
            }
            Rule_p++;
        }

        Log_FormattedMessage("TEST_MACSEC: Installed Secure Channel rules\n");
    }

    return true;
}


/*----------------------------------------------------------------------------
 * test_macsec_CfyE_install
 */
#ifdef TEST_MACSEC_USE_CFYE
bool
test_macsec_CfyE_install(
        const Test_Case_ConfParams_t * TestConf_p,
        const Test_Case_Record_t * TestRec_p,
        Test_CfyEvPort_t ** vPortAdmin_pp,
        Test_CfyERules_t ** RuleAdmin_pp,
        const bool fVerbose,
        const bool fDeviceUpdate,
        const unsigned int BaseRuleIndex)
{
    unsigned int i, AdminIndex;
    unsigned int MaxEntries;
    unsigned int MaxCfyEChannels;
    size_t AllocSize;
    CfyE_Status_t CfyE_Rc;

    if (vPortAdmin_pp == NULL)
    {
        return false;
    }

    *vPortAdmin_pp = NULL;
    if (RuleAdmin_pp != NULL)
    {
        *RuleAdmin_pp = NULL;
    }

    if ((TestRec_p->CfyE_Data_p == NULL) ||
        (TestRec_p->CfyE_Data_p->CfyE_vPortCount == 0) ||
        (TestRec_p->CfyE_Data_p->CfyE_vPortData_p == NULL))
    {
        /* No vPort(s) to install */
        return true;
    }

    CfyE_Rc = CfyE_Device_Limits(TestConf_p->DeviceId,
                                 &MaxCfyEChannels, NULL, NULL);
    if (CfyE_Rc != CFYE_STATUS_OK)
    {
        LOG_CRIT("TEST_MACSEC: Failed, CfyE_Device_Limits()=%d\n", CfyE_Rc);
            return false;
    }


    if (fDeviceUpdate &&
        (TestRec_p->CfyE_Data_p->CfyE_ChannelCount > 0) &&
        (TestRec_p->CfyE_Data_p->CfyE_ChannelData_p != NULL))
    {
        Test_Case_CfyE_Channel_t * Settings_p;

        if (fVerbose)
        {
            Log_FormattedMessage("TEST_MACSEC: Installing CfyE Channel "
                                 "settings...\n");
        }

        MaxEntries = MIN(MaxCfyEChannels, TestRec_p->CfyE_Data_p->CfyE_ChannelCount);
        Settings_p = TestRec_p->CfyE_Data_p->CfyE_ChannelData_p;

        for (i = 0; i < MaxEntries; i++)
        {
            CfyE_Device_t DeviceParams;
            CfyE_Statistics_Control_t StatsParams;
            CfyE_Device_Control_t DevCtrl;
            CfyE_Device_Exceptions_t DevExceptions;

            CfyE_ControlPacket_t CP;
            uint8_t EtherAddr[16][6];

            CfyE_HeaderParser_t HeaderParser;
#if defined(TEST_IPSEC_ENABLE)
            CfyE_EgressHeader_t EgressHeader;
            CfyE_MPLS_Parser_t MPLS_Parser;
#endif
            CfyE_SecTAG_Parser_t SecTAG_Parser;
            CfyE_VLAN_Parser_t VLAN_Parser;

            CfyE_EOPConf_t EOPParams;
            CfyE_ECCConf_t ECCParams;
            unsigned int j, k;
#if defined(TEST_IPSEC_ENABLE)
            ZEROINIT(EgressHeader);
            ZEROINIT(MPLS_Parser);
#endif
            ZEROINIT(StatsParams);
            ZEROINIT(DevExceptions);
            ZEROINIT(SecTAG_Parser);
            ZEROINIT(VLAN_Parser);
            ZEROINIT(EOPParams);
            ZEROINIT(ECCParams);

            ZEROINIT(DeviceParams);
            ZEROINIT(DevCtrl);
            ZEROINIT(EtherAddr);
            ZEROINIT(CP);
            ZEROINIT(HeaderParser);

            DeviceParams.Control_p = &DevCtrl;
            DevCtrl.Exceptions_p = &DevExceptions;

            /* Make all Ethernet address fields in CP structure point to
               valid buffers */
            for (j=0; j<8; j++)
                CP.MAC_DA_ET_Rules[j].MAC_DA_p = EtherAddr[j];
            CP.MAC_DA_ET_Range[0].Range.MAC_DA_Start_p = EtherAddr[8];
            CP.MAC_DA_ET_Range[0].Range.MAC_DA_End_p = EtherAddr[9];
            CP.MAC_DA_ET_Range[1].Range.MAC_DA_Start_p = EtherAddr[10];
            CP.MAC_DA_ET_Range[1].Range.MAC_DA_End_p = EtherAddr[11];
            CP.MAC_DA_Range.MAC_DA_Start_p = EtherAddr[12];
            CP.MAC_DA_Range.MAC_DA_End_p = EtherAddr[13];
            CP.MAC_DA_44Bit_Const_p = EtherAddr[14];
            CP.MAC_DA_48Bit_Const_p = EtherAddr[15];
            DeviceParams.CP_p = &CP;

            DeviceParams.HeaderParser_p = &HeaderParser;
#if defined(TEST_IPSEC_ENABLE)
            HeaderParser.EgressHeader_p = &EgressHeader;
            HeaderParser.MPLS_Parser_p = &MPLS_Parser;
#endif
            HeaderParser.SecTAG_Parser_p = &SecTAG_Parser;
            HeaderParser.VLAN_Parser_p = &VLAN_Parser;

            DeviceParams.StatControl_p = &StatsParams;
            DeviceParams.EOPConf_p = &EOPParams;
            DeviceParams.ECCConf_p = &ECCParams;

            if (Settings_p->ChannelID < MaxCfyEChannels)
            {
                CfyE_Rc = CfyE_Device_Update(TestConf_p->DeviceId,
                                             Settings_p->ChannelID,
                                             &Settings_p->Settings);
                if (CfyE_Rc != CFYE_STATUS_OK)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, CfyE_Device_Update()=%d\n",
                             CfyE_Rc);
                    return false;
                }

                CfyE_Rc = CfyE_Device_Config_Get(TestConf_p->DeviceId,
                                                 Settings_p->ChannelID,
                                                 &DeviceParams);
                if (CfyE_Rc != CFYE_STATUS_OK)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, CfyE_Device_Config_Get()=%d\n",
                             CfyE_Rc);
                    return false;
                }

                Log_FormattedMessage("TEST_MACSEC: CfyE Device Params read: EOPTimeoutVal=%u\n"
                                     "\t ECCCorrectable=%d ECCUncorrectable=%d autoreset=%d incdis=0x%x\n"
                                     "\t bypass=%d defvportvalid=%d defvport=%u\n"
                                     "\t VLAN QinQ=%d QTag=0x%04x\n",
                                     EOPParams.EOPTimeoutVal,
                                     ECCParams.ECCCorrectableThr,
                                     ECCParams.ECCUncorrectableThr,
                                     StatsParams.fAutoStatCntrsReset,
                                     StatsParams.CountIncDisCtrl,
                                     DevCtrl.fLowLatencyBypass,
                                     DevExceptions.fDefaultVPortValid,
                                     DevExceptions.DefaultVPort,
                                     VLAN_Parser.CP.fParseQinQ,
                                     VLAN_Parser.QTag);

                for (k = 0; k < ((MaxCfyEChannels + 31) / 32); k++)
                    Log_FormattedMessage("TEST_MACSEC: CfyE Device Params read: EOPTimeoutCtrl=0x%x\n",
                                             EOPParams.EOPTimeoutCtrl.ch_bitmask[k]);

                for (j=0; j<16; j++)
                {
                    Log_HexDump("CP eth.addr",
                                0,
                                EtherAddr[j],
                                6);
                }

#if defined(TEST_IPSEC_ENABLE)
                Log_FormattedMessage("TEST_IPSEC: CfyE Device Params read:\n"
                                     "\t MPLS3 select1=%d MPLS Etype0=0x%04x fCompare=%d\n",
                                     MPLS_Parser.MPLS3_Select1,
                                     MPLS_Parser.MPLS_Etype[0].MPLS_Etype,
                                     MPLS_Parser.MPLS_Etype[0].fCompare);
#endif
            }
            Settings_p++;
        }
    }

    {
        Test_CfyEvPort_t * vPortAdmin_p;
        Test_Case_CfyE_vPort_t * TC_vPort_p;

        if (fVerbose)
        {
            Log_FormattedMessage("TEST_MACSEC: Installing CfyE vPort(s)...\n");
        }

        /* Allocate and initialize the vPort administration */
        MaxEntries = TestRec_p->CfyE_Data_p->CfyE_vPortCount;
        AllocSize = MaxEntries * sizeof(Test_CfyEvPort_t);
        vPortAdmin_p = test_macsec_malloc(AllocSize);
        if (vPortAdmin_p == NULL)
        {
            LOG_CRIT("TEST_MACSEC: Failed, vPort admin allocation\n");
            return false;
        }

        *vPortAdmin_pp = vPortAdmin_p;

        memset(vPortAdmin_p, 0, AllocSize);

        /* Add vPort(s one by one) */
        TC_vPort_p = TestRec_p->CfyE_Data_p->CfyE_vPortData_p;
        AdminIndex = 0;

        for (i = 0; i < MaxEntries; i++)
        {
            if (!TC_vPort_p->fUpdate)
            {
                SecY_Channel_Mode_t ch_mode = SECY_MODE_MACSEC;

                if (NULL != TestRec_p->CfyE_Data_p &&
                    NULL != TestRec_p->CfyE_Data_p->CfyE_ChannelData_p &&
                    NULL != TestRec_p->CfyE_Data_p->CfyE_ChannelData_p[i].Settings.Control_p)
                {
                    ch_mode = TestRec_p->CfyE_Data_p->CfyE_ChannelData_p[i].Settings.Control_p->fIPsec ?
                                             SECY_MODE_IPSEC: SECY_MODE_MACSEC;
                }

                /* Add the vPort */
                CfyE_Rc = CfyE_vPort_Add(TestConf_p->DeviceId,
                                         &vPortAdmin_p[AdminIndex].vPortHandle,
                                         &TC_vPort_p->Policy,
                                         ch_mode);

                if (CfyE_Rc != CFYE_STATUS_OK)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, CfyE_vPort_Add(%u)=%d\n",
                             TC_vPort_p->vPortId, CfyE_Rc);
                    return false;
                }
                vPortAdmin_p[AdminIndex].vPortId = TC_vPort_p->vPortId;

                CfyE_Rc = CfyE_vPortIndex_Get(
                    vPortAdmin_p[AdminIndex].vPortHandle,
                    &vPortAdmin_p[AdminIndex].vPortIndex);
                if (CfyE_Rc != CFYE_STATUS_OK)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, CfyE_vPortIndex_Get %u)=%d\n",
                             TC_vPort_p->vPortId, CfyE_Rc);
                    return false;
                }

                if (fVerbose)
                {
                    Log_FormattedMessage("TEST_MACSEC: vPort %u (%p) added\n",
                                         TC_vPort_p->vPortId,
                                         vPortAdmin_p[AdminIndex].vPortHandle);
                }

                AdminIndex++;
            }
            TC_vPort_p++; /* Next vPort */
        }
    }

    if ((RuleAdmin_pp != NULL) &&
        (TestRec_p->CfyE_Data_p->CfyE_RuleCount > 0) &&
        (TestRec_p->CfyE_Data_p->CfyE_RuleData_p != NULL))
    {
        Test_CfyERules_t * RuleAdmin_p;
        Test_Case_CfyE_Rule_t * TC_Rule_p;
        Test_CfyEvPort_t * vPortAdmin_p;
        unsigned int Max_vPorts;
        unsigned int j;

        if (fVerbose)
        {
            Log_FormattedMessage("TEST_MACSEC: Installing CfyE Rules...\n");
        }

        /* Allocate and initialize the rule administration */
        MaxEntries = TestRec_p->CfyE_Data_p->CfyE_RuleCount;
        AllocSize = MaxEntries * sizeof(Test_CfyERules_t);
        RuleAdmin_p = test_macsec_malloc(AllocSize);
        if (RuleAdmin_p == NULL)
        {
            LOG_CRIT("TEST_MACSEC: Failed, rule admin allocation\n");
            return false;
        }
        *RuleAdmin_pp = RuleAdmin_p;

        memset(RuleAdmin_p, 0, AllocSize);

        vPortAdmin_p = *vPortAdmin_pp;
        Max_vPorts = TestRec_p->CfyE_Data_p->CfyE_vPortCount;
        TC_Rule_p = TestRec_p->CfyE_Data_p->CfyE_RuleData_p;
        AdminIndex = 0;
        for (i = 0; i < MaxEntries; i++)
        {
            if (!TC_Rule_p->fUpdate)
            {
                for (j = 0; j < Max_vPorts; j++)
                {
                    if ((uintptr_t)vPortAdmin_p[j].vPortId ==
                        (uintptr_t)TC_Rule_p->Rule.Policy.vPortHandle)
                    {
                        CfyE_Rule_t Rule;

                        memcpy (&Rule, &TC_Rule_p->Rule, sizeof(Rule));
                        Rule.Policy.vPortHandle = vPortAdmin_p[j].vPortHandle;

                        /* Install the rule and add it to the administration */
                        if (!TestConf_p->fAllocateIndex)
                        {
                            CfyE_Rc = CfyE_Rule_Add(TestConf_p->DeviceId,
                                                    Rule.Policy.vPortHandle,
                                                    &RuleAdmin_p[AdminIndex].RuleHandle,
                                                    &Rule);
                            if (CfyE_Rc != CFYE_STATUS_OK)
                            {
                                LOG_CRIT("TEST_MACSEC: Failed, "
                                         "CfyE_Rule_Add(%u)=%d\n",
                                         TC_Rule_p->RuleId, CfyE_Rc);
                                return false;
                            }
                        }
                        else
                        {

                            CfyE_Rc = CfyE_Rule_Add_Index(
                                TestConf_p->DeviceId,
                                Rule.Policy.vPortHandle,
                                &RuleAdmin_p[AdminIndex].RuleHandle,
                                &Rule,
                                BaseRuleIndex+AdminIndex);
                            if (CfyE_Rc != CFYE_STATUS_OK)
                            {
                                LOG_CRIT("TEST_MACSEC: Failed, "
                                         "CfyE_Rule_Add_Index(%u)=%d\n",
                                         TC_Rule_p->RuleId, CfyE_Rc);
                                return false;
                            }
                        }

                        RuleAdmin_p[AdminIndex].RuleId = TC_Rule_p->RuleId;

                        CfyE_Rc = CfyE_RuleIndex_Get(
                            RuleAdmin_p[AdminIndex].RuleHandle,
                            &RuleAdmin_p[AdminIndex].RuleIndex);
                        if (CfyE_Rc != CFYE_STATUS_OK)
                        {
                            LOG_CRIT("TEST_MACSEC: Failed, "
                                     "CfyE_RuleIndex_Get(%u)=%d\n",
                                     TC_Rule_p->RuleId, CfyE_Rc);
                            return false;
                        }

                        /* Enable the rule */
                        CfyE_Rc = CfyE_Rule_Enable(TestConf_p->DeviceId,
                                                   RuleAdmin_p[i].RuleHandle,
                                                   true); /* device sync */
                        if (CfyE_Rc != CFYE_STATUS_OK)
                        {
                            LOG_CRIT("TEST_MACSEC: Failed, "
                                     "CfyE_Rule_Enable(%u)=%d\n",
                                     TC_Rule_p->RuleId, CfyE_Rc);
                            return false;
                        }
                        break;
                    }
                } /* for */

                if (j >= Max_vPorts)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, vPort %u not found\n",
                             (unsigned int)(uintptr_t)TC_Rule_p->Rule.Policy.vPortHandle);
                    return false;
                }

                if (fVerbose)
                {
                    Log_FormattedMessage("TEST_MACSEC: Rule %u (%p) added\n",
                                         TC_Rule_p->RuleId,
                                         RuleAdmin_p[AdminIndex].RuleHandle);
                }
                AdminIndex++;
            }

            TC_Rule_p++;                /* Next rule */
        } /* for */
    }

    return true;
}
#endif /* TEST_MACSEC_USE_CFYE */

/*----------------------------------------------------------------------------
 * test_macsec_CfyE_uninstall
 */
#ifdef TEST_MACSEC_USE_CFYE
bool
test_macsec_CfyE_uninstall(
        const Test_Case_ConfParams_t * TestConf_p,
        const Test_Case_Record_t * TestRec_p,
        Test_CfyEvPort_t * vPortAdmin_p,
        Test_CfyERules_t * RuleAdmin_p,
        const bool fVerbose)
{
    unsigned int i;
    unsigned int MaxEntries;
    CfyE_Status_t CfyE_Rc;
    bool fSuccess = true;

    if (vPortAdmin_p == NULL)
    {
        /* Nothing to do */
        return fSuccess;
    }

    if (RuleAdmin_p != NULL)
    {
        MaxEntries = TestRec_p->CfyE_Data_p->CfyE_RuleCount;
        for (i = 0; i < MaxEntries; i++)
        {
            if (!CfyE_RuleHandle_IsSame(RuleAdmin_p[i].RuleHandle,
                                        CfyE_RuleHandle_NULL))
            {
                /* Disable rule */
                CfyE_Rc = CfyE_Rule_Disable(TestConf_p->DeviceId,
                                            RuleAdmin_p[i].RuleHandle,
                                            true); /* device sync */
                if (CfyE_Rc != CFYE_STATUS_OK)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, CfyE_Rule_Disable(%u)=%d\n",
                             RuleAdmin_p[i].RuleId, CfyE_Rc);
                    fSuccess = false;
                }

                /* Remove the rule from the administration */
                CfyE_Rc = CfyE_Rule_Remove(TestConf_p->DeviceId,
                                           RuleAdmin_p[i].RuleHandle);
                if (CfyE_Rc != CFYE_STATUS_OK)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, CfyE_Rule_Remove(%u)=%d\n",
                             RuleAdmin_p[i].RuleId, CfyE_Rc);
                    fSuccess = false;
                }
                else if (fVerbose)
                {
                    Log_FormattedMessage("TEST_MACSEC: Rule %u removed\n",
                                         RuleAdmin_p[i].RuleId);
                }

                RuleAdmin_p[i].RuleHandle = CfyE_RuleHandle_NULL;
                RuleAdmin_p[i].RuleId     = 0;
            }
        } /* for */

        /* Remove the rule administration */
        test_macsec_free(RuleAdmin_p);

    }

    MaxEntries = TestRec_p->CfyE_Data_p->CfyE_vPortCount;
    for (i = 0; i < MaxEntries; i++)
    {
        if (!CfyE_vPortHandle_IsSame(vPortAdmin_p[i].vPortHandle,
                                     CfyE_vPortHandle_NULL))
        {
            /* Remove the vPort from the administration */
            CfyE_Rc = CfyE_vPort_Remove(TestConf_p->DeviceId,
                                        vPortAdmin_p[i].vPortHandle);
            if (CfyE_Rc != CFYE_STATUS_OK)
            {
                LOG_CRIT("TEST_MACSEC: Failed, CfyE_vPort_Remove(%u)=%d\n",
                         vPortAdmin_p[i].vPortId, CfyE_Rc);
                fSuccess = false;
            }
            else if (fVerbose)
            {
                Log_FormattedMessage("TEST_MACSEC: vPort %u removed\n",
                                     vPortAdmin_p[i].vPortId);
            }

            /* Set vPort handle to null */
            vPortAdmin_p[i].vPortHandle = CfyE_vPortHandle_NULL;
            vPortAdmin_p[i].vPortId     = 0;
        }
    } /* for */

    /* Remove the vPort administration */
    test_macsec_free(vPortAdmin_p);

    return fSuccess;
}
#endif /* TEST_MACSEC_USE_CFYE */


/*----------------------------------------------------------------------------
 * test_macsec_CfyE_update
 */
#ifdef TEST_MACSEC_USE_CFYE
bool
test_macsec_CfyE_update(
        const Test_Case_ConfParams_t * TestConf_p,
        const Test_Case_Record_t * TestRec_p,
        Test_CfyEvPort_t * vPortAdmin_p,
        Test_CfyERules_t * RuleAdmin_p)
{
    unsigned int i;
    unsigned int j;
    unsigned int v;
    unsigned int MaxEntries;
    unsigned int Max_vPorts;
    CfyE_Status_t CfyE_Rc;
    CfyE_Rule_t Rule;
    Test_Case_CfyE_vPort_t * TC_vPort_p;
    Test_Case_CfyE_Rule_t * TC_Rule_p;

    if ((vPortAdmin_p == NULL) ||
        (RuleAdmin_p == NULL) ||
        (TestRec_p->CfyE_Data_p == NULL) ||
        (TestRec_p->CfyE_Data_p->CfyE_RuleCount == 0) ||
        (TestRec_p->CfyE_Data_p->CfyE_RuleData_p == NULL))
    {
        /* Nothing to do */
        return true;
    }

    LOG_CRIT("TEST_MACSEC: Updating CfyE vPorts....\n");

    Max_vPorts = TestRec_p->CfyE_Data_p->CfyE_vPortCount;
    TC_vPort_p = TestRec_p->CfyE_Data_p->CfyE_vPortData_p;
    for (i = 0; i < Max_vPorts; i++)
    {
        if (TC_vPort_p->fUpdate)
        {
            for (v = 0; v < Max_vPorts; v++)
            {
                if ((vPortAdmin_p[v].vPortId == TC_vPort_p->vPortId) &&
                    !CfyE_vPortHandle_IsSame(vPortAdmin_p[v].vPortHandle,
                                             CfyE_vPortHandle_NULL))
                {
                    CfyE_Rc = CfyE_vPort_Update(TestConf_p->DeviceId,
                                                vPortAdmin_p[v].vPortHandle,
                                                &TC_vPort_p->Policy);
                    if (CfyE_Rc != CFYE_STATUS_OK)
                    {
                        LOG_CRIT("TEST_MACSEC: Failed, "
                                 "CfyE_vPort_Update(%u)=%d\n",
                                 TC_vPort_p->vPortId, CfyE_Rc);
                        return false;
                    }

                    if (TestConf_p->fVerbose)
                    {
                        Log_FormattedMessage("TEST_MACSEC: vPort %u updated\n",
                                             TC_vPort_p->vPortId);
                    }

                    break;
                }
            } /* for */

            if (v >= Max_vPorts)
            {
                LOG_CRIT("TEST_MACSEC: Failed, vPort %u not found\n",
                         TC_vPort_p->vPortId);
                return false;
            }
        }

        TC_vPort_p++; /* Next vPort */
    } /* for */

    LOG_CRIT("TEST_MACSEC: Updating CfyE Rules....\n");

    MaxEntries = TestRec_p->CfyE_Data_p->CfyE_RuleCount;
    TC_Rule_p  = TestRec_p->CfyE_Data_p->CfyE_RuleData_p;

    for (i = 0; i < MaxEntries; i++)
    {
        if (TC_Rule_p->fUpdate)
        {
            for (j = 0; j < MaxEntries; j++)
            {
                if ((RuleAdmin_p[j].RuleId == TC_Rule_p->RuleId) &&
                    (RuleAdmin_p[j].RuleHandle != CfyE_RuleHandle_NULL))
                {
                    for (v = 0; v < Max_vPorts; v++)
                    {
                        if (((uintptr_t)vPortAdmin_p[v].vPortId ==
                             (uintptr_t)TC_Rule_p->Rule.Policy.vPortHandle) &&
                            !CfyE_vPortHandle_IsSame(vPortAdmin_p[v].vPortHandle,
                                                     CfyE_vPortHandle_NULL))
                        {
                            /* Disabled the rule */
                            CfyE_Rc = CfyE_Rule_EnableDisable(TestConf_p->DeviceId,
                                                              NULL,
                                                              RuleAdmin_p[j].RuleHandle,
                                                              false,
                                                              false,
                                                              true); /* device sync */
                            if (CfyE_Rc != CFYE_STATUS_OK)
                            {
                                LOG_CRIT("TEST_MACSEC: Failed, "
                                         "CfyE_Rule_EnableDisable(Disable %u)=%d\n",
                                         TC_Rule_p->RuleId, CfyE_Rc);
                                return false;
                            }

                            memcpy (&Rule, &TC_Rule_p->Rule, sizeof(Rule));
                            Rule.Policy.vPortHandle = vPortAdmin_p[v].vPortHandle;

                            CfyE_Rc = CfyE_Rule_Update(TestConf_p->DeviceId,
                                                       RuleAdmin_p[j].RuleHandle,
                                                       &Rule);
                            if (CfyE_Rc != CFYE_STATUS_OK)
                            {
                                LOG_CRIT("TEST_MACSEC: Failed, "
                                         "CfyE_Rule_Update(%u)=%d\n",
                                         TC_Rule_p->RuleId, CfyE_Rc);
                                return false;
                            }

                            if (TestConf_p->fVerbose)
                            {
                                Log_FormattedMessage("TEST_MACSEC: Rule %u updated\n",
                                                     TC_Rule_p->RuleId);
                            }

                            /* Enabled the rule again */
                            CfyE_Rc = CfyE_Rule_EnableDisable(TestConf_p->DeviceId,
                                                              RuleAdmin_p[j].RuleHandle,
                                                              NULL,
                                                              false,
                                                              false,
                                                              true); /* device sync */
                            if (CfyE_Rc != CFYE_STATUS_OK)
                            {
                                LOG_CRIT("TEST_MACSEC: Failed, "
                                         "CfyE_Rule_EnableDisable(Eanble %u)=%d\n",
                                         TC_Rule_p->RuleId, CfyE_Rc);
                                return false;
                            }
                            break;
                        }
                    } /* for */

                    if (v >= Max_vPorts)
                    {
                        LOG_CRIT("TEST_MACSEC: Failed, vPort %u not found\n",
                                 (unsigned int)(uintptr_t)TC_Rule_p->Rule.Policy.vPortHandle);
                        return false;
                    }
                    break;
                }
            } /* for */

            if (j >= MaxEntries)
            {
                LOG_CRIT("TEST_MACSEC: Failed, rule %u not found\n",
                         TC_Rule_p->RuleId);
                return false;
            }
        }

        TC_Rule_p++; /* Next rule */
    } /* for */

#if defined(TEST_IPSEC_ENABLE)
#if defined(ADAPTER_EIP164_MODE_INGRESS)
    if (true == TestConf_p->fIngress &&
        SAB_OP_IPSEC == TestRec_p->TransformData_p->operation)
    {
        Test_Case_CfyE_MTT_t *MTT_p = TestRec_p->CfyE_Data_p->MTT_Data_p;
        CfyE_Status_t CfyE_Rc;
        uint32_t i = 0;

        for (i = 0; i < MTT_p->MTT_Count; i++)
        {
            CfyE_Rc = CfyE_MTT_Update(TestConf_p->DeviceId,
                                      i,
                                      &MTT_p->MTT_p[i]);

            if (CFYE_STATUS_OK != CfyE_Rc)
            {
                LOG_CRIT("TEST_MACSEC: Failed, CfyE_MTT_Update()=%d\n",
                         CfyE_Rc);
                return false;
            }

            CfyE_Rc = CfyE_MTT_EnableDisable(TestConf_p->DeviceId,
                                             i,
                                             0,
                                             true,
                                             false,
                                             false,
                                             false,
                                             false);
            if (CFYE_STATUS_OK != CfyE_Rc)
            {
                LOG_CRIT("TEST_MACSEC: Failed, CfyE_MTT_EnableDisable()=%d\n",
                         CfyE_Rc);
                return false;
            }
        }
    }
#endif
#endif

    return true;
}
#endif /* TEST_MACSEC_USE_CFYE */


/*----------------------------------------------------------------------------
 * test_macsec_CfyE_statistics_test
 */
#ifdef TEST_MACSEC_USE_CFYE
bool
test_macsec_CfyE_statistics_test(
        const Test_Case_ConfParams_t * TestConf_p,
        const Test_Case_Record_t * TestRec_p,
        Test_CfyERules_t * RuleAdmin_p)
{
    bool fSuccess = true;
    unsigned int i;
    unsigned int MaxEntries;
    CfyE_Ch_Mask_t ChSummary;
    CfyE_Status_t CfyE_Rc;
    unsigned int MaxCfyEChannels;
    Test_Case_CfyE_Rule_t * TC_Rule_p;

    if ((RuleAdmin_p == NULL) ||
        (TestRec_p->CfyE_Data_p == NULL) ||
        (TestRec_p->CfyE_Data_p->CfyE_RuleCount == 0) ||
        (TestRec_p->CfyE_Data_p->CfyE_RuleData_p == NULL))
    {
        /* Nothing to do */
        return true;
    }

    CfyE_Rc = CfyE_Device_Limits(TestConf_p->DeviceId,
                                 &MaxCfyEChannels, NULL, NULL);
    if (CfyE_Rc != CFYE_STATUS_OK)
    {
        LOG_CRIT("TEST_MACSEC: Failed, CfyE_Device_Limits()=%d\n", CfyE_Rc);
        return false;
    }

    /* TCAM Statistics Summary is only displayed if available */
    /* Note: The TCAM threshold must be set to get summary information */
    MaxEntries = (TestRec_p->CfyE_Data_p->CfyE_RuleCount + 31) / 32;
    for (i = 0; i < MaxEntries; i++)
    {
        unsigned int Summary = 0;

        CfyE_Rc = CfyE_Statistics_Summary_TCAM_Read(TestConf_p->DeviceId,
                                                    i,
                                                    &Summary,
                                                    1);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("TEST_MACSEC: Failed, "
                     "CfyE_Statistics_Summary_Read(%d)=%d\n",
                     i, CfyE_Rc);
            fSuccess = false;
        }
        else if (TestConf_p->fVerbose && (Summary != 0))
        {
            Log_FormattedMessage("TEST_MACSEC: TCAM%u..%u Summary 0x%X\n",
                                 (i * 32), (((i + 1) * 32) - 1), Summary);
        }
    }

    ZEROINIT(ChSummary);

    CfyE_Rc = CfyE_Statistics_Summary_Channel_Read(TestConf_p->DeviceId,
                                                   &ChSummary);
    if (CfyE_Rc != CFYE_STATUS_OK)
    {
        LOG_CRIT("TEST_MACSEC: Failed, "
                 "CfyE_Statistics_Summary_Channel_Read() error %d\n",
                 CfyE_Rc);
        fSuccess = false;
    }

    if (fSuccess && TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: CfyE per-channel summary counters: ");

        for (i = 0; i < MaxCfyEChannels; i++)
            Log_FormattedMessage("%d ", (ChSummary.ch_bitmask[i / 32] & (1 << (i % 32))) != 0);

        Log_FormattedMessage("\n");
    }

    for (i = 0; i < MaxCfyEChannels; i++)
    {
        if ((ChSummary.ch_bitmask[i / 32] & (1 << (i % 32))) != 0)
        {
            CfyE_Statistics_Channel_t ChannelStat;
            Log_FormattedMessage("TEST_MACSEC: Channel %u has crossed threshold\n", i);
            CfyE_Rc = CfyE_Statistics_Channel_Get(TestConf_p->DeviceId,
                                                  i,
                                                  &ChannelStat,
                                                  true);
            if (CfyE_Rc != CFYE_STATUS_OK)
            {
                LOG_CRIT("TEST_MACSEC: Failed, "
                         "CfyE_Statistics_Channel_Get(%u)=%d\n",
                         i, CfyE_Rc);

                fSuccess = false;
            }

            if (TestConf_p->fVerbose)
            {
                Log_FormattedMessage("TEST_MACSec: Channel statistics for channel %u\n",i);
                Log_FormattedMessage("  TCAMHitMultiple        : %d\n",ChannelStat.TCAMHitMultiple.Lo);
                Log_FormattedMessage("  HeaderParserDroppedPkts: %d\n",ChannelStat.HeaderParserDroppedPkts.Lo);
                Log_FormattedMessage("  TCAMMiss               : %d\n",ChannelStat.TCAMMiss.Lo);
                Log_FormattedMessage("  PktsCtrl               : %d\n",ChannelStat.PktsCtrl.Lo);
                Log_FormattedMessage("  PktsData               : %d\n",ChannelStat.PktsData.Lo);
                Log_FormattedMessage("  PktsDropped            : %d\n",ChannelStat.PktsDropped.Lo);
                Log_FormattedMessage("  PktsErrIn              : %d\n",ChannelStat.PktsErrIn.Lo);
#if defined(TEST_IPSEC_ENABLE)
                Log_FormattedMessage("  MTTMiss                : %d\n",ChannelStat.MTTMiss.Lo);
#endif
            }
        }
    }

#if defined(TEST_IPSEC_ENABLE)
    /** TCAM is not present in Egress path for IPsec*/
    if (TestRec_p->TransformData_p != NULL &&
        SECY_SA_ACTION_IPSEC_EGRESS != TestRec_p->TransformData_p->SA_Data.ActionType)
#endif
    {
        /* TCAM Statistics is assumed to triggered */
        MaxEntries = TestRec_p->CfyE_Data_p->CfyE_RuleCount;
        TC_Rule_p  = TestRec_p->CfyE_Data_p->CfyE_RuleData_p;

        for (i = 0; i < MaxEntries; i++)
        {
            if (!TC_Rule_p->fUpdate)
            {
                CfyE_Statistics_TCAM_t Stat;

                CfyE_Rc = CfyE_Statistics_TCAM_Get(TestConf_p->DeviceId,
                                                   TC_Rule_p->RuleId,
                                                   &Stat,
                                                   true);/* device sync request */
                if (CfyE_Rc != CFYE_STATUS_OK)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, "
                             "CfyE_Statistics_TCAM_Get(%u)=%d\n",
                             TC_Rule_p->RuleId, CfyE_Rc);
                    fSuccess = false;
                }
                else
                {
                    if (TestConf_p->fVerbose)
                    {
                        Log_FormattedMessage("TEST_MACSEC: TCAM%u counter = %u\n",
                                             TC_Rule_p->RuleId, Stat.Counter.Lo);
                    }

                    if ((TestRec_p->CfyE_Data_p->EventMaskGlobal &
                         CFYE_EVENT_STAT_TCAM_THR) != 0)
                    {
                        if (Stat.Counter.Lo != 0)
                        {
                            LOG_CRIT("TEST_MACSEC: Failed, "
                                     "TCAM%u counter should be zero\n",
                                     TC_Rule_p->RuleId);
                            fSuccess = false;
                        }
                    }
                }
            }

            TC_Rule_p++; /* Next rule */
        }
    }

    return fSuccess;
}
#endif /* TEST_MACSEC_USE_CFYE */


/*----------------------------------------------------------------------------
 * test_macsec_CfyE_statsummary_test
 */
#ifdef TEST_MACSEC_USE_CFYE
bool
test_macsec_CfyE_statsummary_test(
        const Test_Case_ConfParams_t * TestConf_p,
        unsigned int BeginIndex,
        unsigned int NumberOfEntries,
        unsigned int SummaryMatchPattern)
{
    bool fSuccess = true;
    unsigned int i, j;
    unsigned int MaxEntries;
    CfyE_Status_t CfyE_Rc;
    unsigned int MaxCfyEChannels;
    CfyE_Ch_Mask_t ChSummary;

    CfyE_Rc = CfyE_Device_Limits(TestConf_p->DeviceId,
                                 &MaxCfyEChannels, NULL, NULL);
    if (CfyE_Rc != CFYE_STATUS_OK)
    {
        LOG_CRIT("TEST_MACSEC: Failed, CfyE_Device_Limits()=%d\n", CfyE_Rc);
        return false;
    }

    MaxEntries = (BeginIndex + NumberOfEntries + 31) / 32;
    for (i = 0; i < MaxEntries; i++)
    {
        unsigned int Summary = 0;

        CfyE_Rc = CfyE_Statistics_Summary_TCAM_Read(TestConf_p->DeviceId,
                                               i,
                                               &Summary,
                                               1);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("TEST_MACSEC: Failed, "
                     "CfyE_Statistics_Summary_TCAM_Read(%d)=%d\n",
                     i, CfyE_Rc);
            fSuccess = false;
        }
        else
        {
            for (j = 0; j < 32; j++)
            {
                if ( (Summary & (1<<j)) != 0)
                {
                    CfyE_Statistics_TCAM_t Stat;

                    CfyE_Rc = CfyE_Statistics_TCAM_Get(TestConf_p->DeviceId,
                                                       i*32 + j,
                                                       &Stat,
                                                       true); /* device sync request */
                    if (CfyE_Rc != CFYE_STATUS_OK)
                    {
                        LOG_CRIT("TEST_MACSEC: Failed, "
                                 "CfyE_Statistics_TCAM_Get()=%d\n",
                                 CfyE_Rc);
                        fSuccess = false;
                    }
                    if (Stat.Counter.Lo == 0)
                    {
                        LOG_CRIT("TEST_MACSEC: Failed, statistics=0\n");
                        fSuccess = false;
                    }

                    Log_FormattedMessage("TEST_MACSEC: TCAM%u counter = %u\n",
                                         i*32 + j, Stat.Counter.Lo);
                }
            }
            Summary ^= SummaryMatchPattern;
            if (Summary != 0)
            {
                if ((i + 1) >= MaxEntries)
                {
                    Summary &= (1 << ((BeginIndex + NumberOfEntries) & 0x1F))-1;
                    if (Summary == 0)
                    {
                        continue;
                    }
                }

                LOG_CRIT("TEST_MACSEC: Failed, TCAM%u..%u Summary 0x%X mismatch\n",
                                     (i * 32), (((i+1) * 32) -1), Summary);
                fSuccess = false;
            }
        }
    }

    if (fSuccess && TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: TCAM%u..%u Summary OK\n",
                             BeginIndex,
                             (BeginIndex + NumberOfEntries));
    }

    ZEROINIT(ChSummary);

    CfyE_Rc = CfyE_Statistics_Summary_Channel_Read(TestConf_p->DeviceId,
                                                   &ChSummary);
    if (CfyE_Rc != CFYE_STATUS_OK)
    {
        LOG_CRIT("TEST_MACSEC: Failed, "
                 "CfyE_Statistics_Summary_Channel_Read() error %d\n",
                 CfyE_Rc);
        fSuccess = false;
    }

    if (fSuccess && TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: CfyE per-channel summary counters: ");

        for (i = 0; i < MaxCfyEChannels; i++)
            Log_FormattedMessage("%d ", (ChSummary.ch_bitmask[i / 32] & (1 << (i % 32))) != 0);

        Log_FormattedMessage("\n");
    }

    for (i=0; i < MaxCfyEChannels; i++)
    {
        if ((ChSummary.ch_bitmask[i / 32] & (1 << (i % 32))) != 0)
        {
            CfyE_Statistics_Channel_t ChannelStat;
            Log_FormattedMessage("TEST_MACSEC: Channel %u has crossed threshold\n", i);
            CfyE_Rc = CfyE_Statistics_Channel_Get(TestConf_p->DeviceId,
                                                  i,
                                                  &ChannelStat,
                                                  true);
            if (CfyE_Rc != CFYE_STATUS_OK)
            {
                LOG_CRIT("TEST_MACSEC: Failed, "
                         "CfyE_Statistics_Channel_Get(%u)=%d\n",
                         i, CfyE_Rc);
                fSuccess = false;
            }
            if (TestConf_p->fVerbose)
            {
                Log_FormattedMessage("TEST_MACSec: Channel statistics for channel %u\n",i);
                Log_FormattedMessage("  TCAMHitMultiple        : %d\n",ChannelStat.TCAMHitMultiple.Lo);
                Log_FormattedMessage("  HeaderParserDroppedPkts: %d\n",ChannelStat.HeaderParserDroppedPkts.Lo);
                Log_FormattedMessage("  TCAMMiss               : %d\n",ChannelStat.TCAMMiss.Lo);
                Log_FormattedMessage("  PktsCtrl               : %d\n",ChannelStat.PktsCtrl.Lo);
                Log_FormattedMessage("  PktsData               : %d\n",ChannelStat.PktsData.Lo);
                Log_FormattedMessage("  PktsDropped            : %d\n",ChannelStat.PktsDropped.Lo);
                Log_FormattedMessage("  PktsErrIn              : %d\n",ChannelStat.PktsErrIn.Lo);
#if defined(TEST_IPSEC_ENABLE)
                Log_FormattedMessage("  MTTMiss                : %d\n",ChannelStat.MTTMiss.Lo);
#endif
            }
        }
    }


    return fSuccess;
}
#endif /* TEST_MACSEC_USE_CFYE */



#ifdef TEST_MACSEC_USE_READ_API
/*----------------------------------------------------------------------------
 * test_macsec_read_entries
 */
bool
test_macsec_read_entries(
        const unsigned int DeviceId,
        const bool fUseCfyE)
{
    SecY_Status_t SecY_Rc;
    SecY_SAHandle_t SAHandle;
    SecY_SA_t SAParams;
    uint8_t SCI[8];
    unsigned int SAIndex;
    unsigned int vPort;

#ifdef TEST_MACSEC_MODE_INGRESS
    const void * TmpHandle = NULL;
#endif

    ZEROINIT(SAParams);
    ZEROINIT(SCI);

#ifdef TEST_MACSEC_MODE_INGRESS
    SecY_Rc = SecY_SCI_Next_Get(DeviceId,
                                0,
                                &TmpHandle,
                                SCI,
                                NULL);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        LOG_CRIT("TEST_MACSEC: SecY_SCI_Next_Get returned error %d\n",SecY_Rc);
        return false;
    }
    while (TmpHandle != NULL)
    {
        Log_HexDump("TEST_MACSEC: SCI on vPort 0",0,SCI,8);
        SecY_Rc = SecY_SCI_Next_Get(DeviceId,
                                    0,
                                    &TmpHandle,
                                    SCI,
                                    NULL);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("TEST_MACSEC: SecY_SCI_Next_Get returned error %d\n",SecY_Rc);
            return false;
        }
    }
#endif

    SecY_Rc = SecY_SA_Next_Get(DeviceId,
                               SecY_SAHandle_NULL,
                               &SAHandle);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        LOG_CRIT("TEST_MACSEC: SecY_SA_Next_Get returned error %d\n",SecY_Rc);
        return false;
    }
    while (!SecY_SAHandle_IsSame(&SAHandle, &SecY_SAHandle_NULL))
    {
        SecY_SAIndex_Get(SAHandle, &SAIndex, NULL);

        SecY_Rc = SecY_SA_vPortIndex_Get(DeviceId,
                                         SAHandle,
                                         &vPort);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("TEST_MACSEC: SecY_SA_vPortIndex_Get returned error %d\n",SecY_Rc);
            return false;
        }

        Log_FormattedMessage("TEST_MACSEC; SecY_SA_Next_Get() returned SA with index %u vPort=%u\n",SAIndex,vPort);

        SecY_Rc = SecY_SA_Params_Read(DeviceId,
                                      SAHandle,
                                      &SAParams,
                                      SCI);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("TEST_MACSEC: SecY_SA_Params_Read returned error %d\n",SecY_Rc);
            return false;
        }
        switch (SAParams.ActionType)
        {
        case SECY_SA_ACTION_BYPASS:
            Log_FormattedMessage("TEST_MACSEC: SA type BYPASS\n");
            break;
        case SECY_SA_ACTION_DROP:
            Log_FormattedMessage("TEST_MACSEC: SA type DROP\n");
            break;
        case SECY_SA_ACTION_CRYPT_AUTH:
            Log_FormattedMessage("TEST_MACSEC: SA type CRYPT_AUTH\n");
            break;
        case SECY_SA_ACTION_EGRESS:
            Log_FormattedMessage("TEST_MACSEC: SA type EGRESS InUse=%d fIncludeSCI=%d PreSecTagAuthLength=%d\n",
                                 SAParams.Params.Egress.fSAInUse,
                                 SAParams.Params.Egress.fIncludeSCI,
                                 SAParams.Params.Egress.PreSecTagAuthLength);
            break;

        case SECY_SA_ACTION_INGRESS:
            Log_FormattedMessage("TEST_MACSEC: SA type INGRESS InUse=%d AN=%d fAllowUntagged=%d fAllowTagged=%d\n",
                                 SAParams.Params.Ingress.fSAInUse,
                                 SAParams.Params.Ingress.AN,
                                 SAParams.Params.Ingress.fAllowUntagged,
                                 SAParams.Params.Ingress.fAllowTagged);

            Log_HexDump("TEST_MACSEC: SCI", 0, SCI, 8);
            break;

#if defined(TEST_IPSEC_ENABLE)
        case SECY_SA_ACTION_IPSEC_EGRESS:
            Log_FormattedMessage("TEST_MACSEC: SA type EGRESS InUse=%d fUpdateUDP=%d fUpdateUDP=%d"
                                 "fUpdateUDP=%d fUpdateUDP=%d fUpdateUDP=%d fUpdateUDP=%d\n",
                                 SAParams.Params.IPsecEgress.fSAInUse,
                                 SAParams.Params.IPsecEgress.fUpdateUDP,
                                 SAParams.Params.IPsecEgress.fUpdateIP,
                                 SAParams.Params.IPsecEgress.fNAT_UDP,
                                 SAParams.Params.IPsecEgress.fOuterIPHdr,
                                 SAParams.Params.IPsecEgress.fConfProtect,
                                 SAParams.Params.IPsecEgress.fProtectFrames);
            break;
        case SECY_SA_ACTION_IPSEC_INGRESS:
            Log_FormattedMessage("TEST_MACSEC: SA type INGRESS InUse=%d fReplayProtect = %d"
                                 "fConfProtect = %d fPadNotValidDrop = %d fPadLenF a i lDrop = %d"
                                 "fUpdateIP = %d fUpdateTTL = %d",
                                 SAParams.Params.IPsecIngress.fSAInUse,
                                 SAParams.Params.IPsecIngress.fReplayProtect,
                                 SAParams.Params.IPsecIngress.fConfProtect,
                                 SAParams.Params.IPsecIngress.fPadNotValidDrop,
                                 SAParams.Params.IPsecIngress.fPadLenFailDrop,
                                 SAParams.Params.IPsecIngress.fUpdateIP,
                                 SAParams.Params.IPsecIngress.fUpdateTTL);
            Log_HexDump("TEST_MACSEC: SCI",0, SCI, 8);
            break;
#endif
        default:
            break;
        }

        SecY_Rc = SecY_SA_Next_Get(DeviceId,
                                   SAHandle,
                                           &SAHandle);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("TEST_MACSEC: SecY_SA_Next_Get returned error %d\n",SecY_Rc);
            return false;
        }
    }


#ifdef TEST_MACSEC_USE_CFYE
    if (fUseCfyE)
    {
        CfyE_Status_t CfyE_Rc;
        CfyE_vPortHandle_t vPortHandle;
        CfyE_vPort_t vPortPolicy;
        unsigned int vPortIndex;
        CfyE_RuleHandle_t RuleHandle;
        CfyE_Rule_t Rule;
        unsigned int RuleIndex;
        bool fRuleEnabled;

        CfyE_Rc = CfyE_vPort_Next_Get(DeviceId,
                                      CfyE_vPortHandle_NULL,
                                      &vPortHandle);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("TEST_MACSEC: CfyE_vPort_Next_Get returned error %d\n",CfyE_Rc);
            return false;
        }
        while (!CfyE_vPortHandle_IsSame(vPortHandle, CfyE_vPortHandle_NULL))
        {
            CfyE_vPortIndex_Get(vPortHandle, &vPortIndex);

            Log_FormattedMessage("TEST_MACSEC; CfyE_vPort_Next_Get() returned vPort with index %u\n",vPortIndex);

            CfyE_Rc = CfyE_vPort_Read(DeviceId,
                                          vPortHandle,
                                      &vPortPolicy);
            if (CfyE_Rc != CFYE_STATUS_OK)
            {
                LOG_CRIT("TEST_MACSEC: CfyE_vPort_Read returned error %d\n",CfyE_Rc);
                return false;
            }
            Log_FormattedMessage("TEST_MACSEC: SecTagOffset=%d PktExtesion=%d\n",
                                 vPortPolicy.SecTagOffset,
                                 vPortPolicy.PktExtension);
            CfyE_Rc = CfyE_vPort_Next_Get(DeviceId,
                                          vPortHandle,
                                          &vPortHandle);
            if (CfyE_Rc != CFYE_STATUS_OK)
            {
                    LOG_CRIT("TEST_MACSEC: CfyE_vPort_Next_Get returned error %d\n",CfyE_Rc);
                    return false;
            }
            }

        CfyE_Rc = CfyE_Rule_Next_Get(DeviceId,
                                     CfyE_RuleHandle_NULL,
                                     &RuleHandle);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("TEST_MACSEC: CfyE_Rule_Next_Get returned error %d\n",CfyE_Rc);
            return false;
        }

        RuleHandle = 0;

        while (!CfyE_RuleHandle_IsSame(RuleHandle, CfyE_RuleHandle_NULL))
        {
            CfyE_RuleIndex_Get(RuleHandle, &RuleIndex);

            Log_FormattedMessage("TEST_MACSEC; CfyE_Rule_Next_Get() returned Rule with index %u\n",RuleIndex);

            CfyE_Rc = CfyE_Rule_Read(DeviceId,
                                     RuleHandle,
                                     &Rule,
                                     &fRuleEnabled);
            if (CfyE_Rc != CFYE_STATUS_OK)
            {
                LOG_CRIT("TEST_MACSEC: CfyE_Rule_Read returned error %d\n",CfyE_Rc);
                    return false;
            }
            CfyE_vPortIndex_Get(Rule.Policy.vPortHandle, &vPortIndex);
            Log_FormattedMessage("TEST_MACSEC: vPort=%d enabled=%d\n",
                                     vPortIndex,
                                 fRuleEnabled);
            Log_HexDump32("Rule Data",
                        0,
                        Rule.Data,
                        CFYE_RULE_NON_CTRL_WORD_COUNT);

            Log_HexDump32("Rule Mask",
                        0,
                        Rule.DataMask,
                        CFYE_RULE_NON_CTRL_WORD_COUNT);

            CfyE_Rc = CfyE_Rule_Next_Get(DeviceId,
                                         RuleHandle,
                                         &RuleHandle);
            if (CfyE_Rc != CFYE_STATUS_OK)
            {
                LOG_CRIT("TEST_MACSEC: CfyE_Rule_Next_Get returned error %d\n",CfyE_Rc);
                return false;
            }
        }
    }
#endif /* TEST_MACSEC_USE_CFYE */

    return true;
}



/*----------------------------------------------------------------------------
 * test_macsec_show_diagnostics
 */
bool
test_macsec_show_diagnostics(
        const unsigned int DeviceId,
        unsigned int vPortCount,
        const bool fUseCfyE)
{
    SecY_Status_t SecY_Rc;
    unsigned int i;

    SecY_Rc = SecY_Diag_Device_Dump(DeviceId);
    if (SecY_Rc != SECY_STATUS_OK)
    {

        LOG_CRIT("TEST_MACSEC: SecY_Diag_Device_Dump() failed\n");
        return false;
    }

    if (vPortCount == 0)
    {
        SecY_Rc = SecY_Diag_Channel_Dump(DeviceId, 0, true);
        if (SecY_Rc != SECY_STATUS_OK)
        {

            LOG_CRIT("TEST_MACSEC: SecY_Diag_Channel_Dump() failed\n");
            return false;
        }

        SecY_Rc = SecY_Diag_vPort_Dump(DeviceId, 0, true, false);
        if (SecY_Rc != SECY_STATUS_OK)
        {

            LOG_CRIT("TEST_MACSEC: SecY_Diag_vPort_Dump() failed\n");
            return false;
        }
        SecY_Rc = SecY_Diag_SA_Dump(DeviceId, SecY_SAHandle_NULL, true);
        if (SecY_Rc != SECY_STATUS_OK)
        {

            LOG_CRIT("TEST_MACSEC: SecY_Diag_SA_Dump() failed\n");
            return false;
        }
    }
    else
    {
        SecY_Rc = SecY_Diag_Channel_Dump(DeviceId, 0, false);
        if (SecY_Rc != SECY_STATUS_OK)
        {

            LOG_CRIT("TEST_MACSEC: SecY_Diag_Channel_Dump() failed\n");
            return false;
        }

        for (i=0; i<vPortCount; i++)
        {

            SecY_Rc = SecY_Diag_vPort_Dump(DeviceId, i, false, true);
            if (SecY_Rc != SECY_STATUS_OK)
            {
                LOG_CRIT("TEST_MACSEC: SecY_Diag_vPort_Dump() failed\n");
                return false;
            }
        }
    }

#ifdef TEST_MACSEC_USE_CFYE
    if (fUseCfyE)
    {
        CfyE_Status_t CfyE_Rc;
        CfyE_Rc = CfyE_Diag_Device_Dump(DeviceId);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {

            LOG_CRIT("TEST_MACSEC: CfyE_Diag_Device_Dump() failed\n");
            return false;
        }


        CfyE_Rc = CfyE_Diag_Channel_Dump(DeviceId, 0, vPortCount==0);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {

            LOG_CRIT("TEST_MACSEC: CfyE_Diag_Channel_Dump() failed\n");
            return false;
        }

        CfyE_Rc = CfyE_Diag_vPort_Dump(DeviceId, CfyE_vPortHandle_NULL, true, true);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {

            LOG_CRIT("TEST_MACSEC: CfyE_Diag_vPort_Dump() failed\n");
            return false;
        }


        CfyE_Rc = CfyE_Diag_Rule_Dump(DeviceId, CfyE_RuleHandle_NULL, true);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {

            LOG_CRIT("TEST_MACSEC: CfyE_Diag_Rule_Dump() failed\n");
            return false;
        }

#if defined(TEST_IPSEC_ENABLE)
#if defined(ADAPTER_EIP164_MODE_INGRESS)
        CfyE_Rc = CfyE_Diag_MTT_Dump(DeviceId, 0, true);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("TEST_MACSEC: CfyE_Diag_MTT_Dump() failed\n");
            return false;
        }
#endif
#endif
    }
#endif
    return true;
}



#endif /* TEST_MACSEC_USE_READ_API */

/* end of file test_case.c */
