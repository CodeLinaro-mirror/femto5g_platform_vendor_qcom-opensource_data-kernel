/* da_secy_rekey.c
 *
 * Demo Application, MACsec transform rekeying test using SecY API only.
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
 * This module uses (requires) the following interface(s):
 */

/* Default configuration */
#include "c_da_macsec.h"

#ifdef DA_MACSEC_USERMODE
#include <stdlib.h>
#include <unistd.h>  /* usleep */
#include "api_driver164_init.h"
#else
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>       /* printk */
#include <linux/slab.h>
#include <asm/delay.h>          /* udelay */
#endif

#include "api_secy.h"

#include "basic_defs.h"
#include "clib.h"
#include "log.h"

/* Packet I/O API */
#include "api_pktio.h"

#include "da_internal.h"

/*----------------------------------------------------------------------------
 * Definitions and macros
 */

/*----------------------------------------------------------------------------
 * Local variables
 */

/* MACsec key */
static uint8_t K1[] = {
    0xad, 0x7a, 0x2b, 0xd0, 0x3e, 0xac, 0x83, 0x5a,
    0x6f, 0x62, 0x0f, 0xdc, 0xb5, 0x06, 0xb3, 0x45,
};

static uint8_t K2[] = {
    0xda, 0xa7, 0xb2, 0x0d, 0xe3, 0xca, 0x38, 0xa5,
    0xf6, 0x26, 0xf0, 0xcd, 0x5b, 0x60, 0x3b, 0x54,
};


/* MACsec SCI */
static uint8_t SCI1[] = {
    0x12, 0x15, 0x35, 0x24, 0xc0, 0x89, 0x5e, 0x81,
};

#ifdef DA_MACSEC_MODE_INGRESS

static da_sa_params_t Transform_Params_Ingress1 =
{
    SAB_DIRECTION_INGRESS,
    SAB_OP_MACSEC,
    0,
    2,
    K1,
    sizeof(K1),
    SCI1,
    NULL,
    NULL,
    0xb2c28465, /* Sequence number. */
    0,
    128,
#if defined(DA_IPSEC_ENABLE)
    0,
#endif
};


static da_sa_params_t Transform_Params_Ingress2 =
{
    SAB_DIRECTION_INGRESS,
    SAB_OP_MACSEC,
    0,
    3,
    K2,
    sizeof(K2),
    SCI1,
    NULL,
    NULL,
    0x00000001, /* Sequence number. */
    0,
    128,
#if defined(DA_IPSEC_ENABLE)
    0,
#endif
};

#endif

#ifdef DA_MACSEC_MODE_EGRESS


static da_sa_params_t Transform_Params_Egress1 =
{
    SAB_DIRECTION_EGRESS,
    SAB_OP_MACSEC,
    0,
    2,
    K1,
    sizeof(K1),
    SCI1,
    NULL,
    NULL,
    0xb2c28464, /* Sequence number. */
    0,
    0,
#if defined(DA_IPSEC_ENABLE)
    0,
#endif
};

static da_sa_params_t Transform_Params_Egress2 =
{
    SAB_DIRECTION_EGRESS,
    SAB_OP_MACSEC,
    0,
    3,
    K2,
    sizeof(K2),
    SCI1,
    NULL,
    NULL,
    0x00000000, /* Sequence number. */
    0,
    0,
#if defined(DA_IPSEC_ENABLE)
    0,
#endif
};
#endif

/* Plaintext packet */
static const uint8_t Plain_Packet[] =
{
    0xd6, 0x09, 0xb1, 0xf0,
    0x56, 0x63, 0x7a, 0x0d,
    0x46, 0xdf, 0x99, 0x8d,
    0x08, 0x00, 0x0f, 0x10,
    0x11, 0x12, 0x13, 0x14,
    0x15, 0x16, 0x17, 0x18,
    0x19, 0x1a, 0x1b, 0x1c,
    0x1d, 0x1e, 0x1f, 0x20,
    0x21, 0x22, 0x23, 0x24,
    0x25, 0x26, 0x27, 0x28,
    0x29, 0x2a, 0x2b, 0x2c,
    0x2d, 0x2e, 0x2f, 0x30,
    0x31, 0x32, 0x33, 0x34,
    0x35, 0x36, 0x37, 0x38,
    0x39, 0x3a, 0x00, 0x02
};


/* First packet encrypted with MACsec (SA1, seqnr=0xb2c28465) */
static const uint8_t Macsec_Packet1[] =
{
    0xd6, 0x09, 0xb1, 0xf0,
    0x56, 0x63, 0x7a, 0x0d,
    0x46, 0xdf, 0x99, 0x8d,
    0x88, 0xe5, 0x2e, 0x00,
    0xb2, 0xc2, 0x84, 0x65,
    0x12, 0x15, 0x35, 0x24,
    0xc0, 0x89, 0x5e, 0x81,
    0x70, 0x1a, 0xfa, 0x1c,
    0xc0, 0x39, 0xc0, 0xd7,
    0x65, 0x12, 0x8a, 0x66,
    0x5d, 0xab, 0x69, 0x24,
    0x38, 0x99, 0xbf, 0x73,
    0x18, 0xcc, 0xdc, 0x81,
    0xc9, 0x93, 0x1d, 0xa1,
    0x7f, 0xbe, 0x8e, 0xdd,
    0x7d, 0x17, 0xcb, 0x8b,
    0x4c, 0x26, 0xfc, 0x81,
    0xe3, 0x28, 0x4f, 0x2b,
    0x7f, 0xba, 0x71, 0x3d,
    0x4f, 0x8d, 0x55, 0xe7,
    0xd3, 0xf0, 0x6f, 0xd5,
    0xa1, 0x3c, 0x0c, 0x29,
    0xb9, 0xd5, 0xb8, 0x80
};


/* Second packet encrypted with MACsec (SA1, seqnr=0xb2c28466) */
static const uint8_t Macsec_Packet2[] =
{
    0xD6, 0x09, 0xB1, 0xF0,
    0x56, 0x63, 0x7A, 0x0D,
    0x46, 0xDF, 0x99, 0x8D,
    0x88, 0xE5, 0x2E, 0x00,
    0xB2, 0xC2, 0x84, 0x66,
    0x12, 0x15, 0x35, 0x24,
    0xC0, 0x89, 0x5E, 0x81,
    0x33, 0xE2, 0x05, 0xD6,
    0xC4, 0xFC, 0x9B, 0x4D,
    0x4A, 0x18, 0x91, 0x77,
    0xC4, 0xEE, 0x7D, 0x5E,
    0x67, 0x6C, 0x61, 0x0C,
    0xCC, 0x56, 0x43, 0xBF,
    0xEA, 0xE3, 0x10, 0xD9,
    0x64, 0x55, 0xB5, 0x46,
    0x7A, 0xD0, 0x5D, 0x5F,
    0xA8, 0x90, 0x8E, 0xCE,
    0x6F, 0x41, 0xE9, 0x12,
    0x22, 0x18, 0x8B, 0xA3,
    0xC3, 0xE8, 0xBF, 0x6A,
    0x00, 0xE6, 0x3E, 0x59,
    0x02, 0xC3, 0x70, 0x3A,
    0xF3, 0x0F, 0x00, 0x9D,
};

/* Third packet encrypted with MACsec (SA2, seqnr=0x00000001) */
static const uint8_t Macsec_Packet3[] =
{
    0xD6, 0x09, 0xB1, 0xF0,
    0x56, 0x63, 0x7A, 0x0D,
    0x46, 0xDF, 0x99, 0x8D,
    0x88, 0xE5, 0x2F, 0x00,
    0x00, 0x00, 0x00, 0x01,
    0x12, 0x15, 0x35, 0x24,
    0xC0, 0x89, 0x5E, 0x81,
    0xDB, 0x65, 0xB6, 0x21,
    0xE5, 0x62, 0x21, 0xAF,
    0xD1, 0xEE, 0x52, 0x58,
    0xA9, 0x0C, 0xA1, 0x98,
    0x86, 0x94, 0x8F, 0xA9,
    0x96, 0xB4, 0xFA, 0xD3,
    0x10, 0x13, 0xA0, 0x75,
    0xBC, 0x86, 0xF6, 0xF9,
    0xC6, 0x67, 0x3C, 0xBA,
    0xA9, 0x9B, 0x6B, 0x82,
    0xD1, 0xF9, 0x98, 0x22,
    0x1C, 0xE9, 0xDE, 0x51,
    0x21, 0x58, 0xCB, 0x3B,
    0x4D, 0xB3, 0x29, 0xA5,
    0xFD, 0x03, 0x19, 0xC0,
    0xB9, 0x1A, 0xE7, 0x2D,
};

/*----------------------------------------------------------------------------
 * da_secy_macsec_transform
 */
bool
da_secy_macsec_rekey(
        bool fVerbose,
        bool fIngress)
{
    unsigned int vPort = 0;
    unsigned int Channel = 0;

    SecY_Status_t SecY_Rc;
    SecY_SA_t SA_Params;
    uint32_t SAWordCount = 0;
    SecY_SAHandle_t SecY_SAHandle1;
    SecY_SAHandle_t SecY_SAHandle2;

    unsigned int PktByteCount;
    unsigned int ExpectedPktByteCount;
    uint8_t * InputPktHostAddress = NULL;
    uint8_t * ProcessedPktHostAddress = NULL;
    uint8_t * ExpectedPktHostAddress = NULL;
    bool fSuccess = false;

    SecY_SAHandle1 = SecY_SAHandle_NULL;
    SecY_SAHandle2 = SecY_SAHandle_NULL;

    Log_FormattedMessage("DA_MACSEC: Starting test for %sgress\n",
                         fIngress ? "in" : "e");

    if (fVerbose)
    {
        Log_FormattedMessage("DA_MACSEC: Perform Transform\n");
    }
#ifndef DA_MACSEC_MODE_INGRESS
    if (fIngress)
        return false;
#endif
#ifndef DA_MACSEC_MODE_EGRESS
    if (!fIngress)
        return false;
#endif

    {
        SecY_Settings_t Settings;

        Log_FormattedMessage("DA_MACSEC: Initializing SecY\n");

        ZEROINIT(Settings);

        /* Non-matching SA flow packet processing rules */
        /* Default rule is to drop non-matching SA packets */
        Settings.DropBypass.DropType = SECY_SA_DROP_PKT_ERROR;

#if defined(DA_MACSEC_MODE_EGRESS) && defined(DA_MACSEC_MODE_INGRESS)
        SecY_Rc = SecY_Device_Init(SECY_DEVICE_ID,
                                   SECY_ROLE_EGRESS_INGRESS,
                                   &Settings);
#else
        SecY_Rc = SecY_Device_Init(SECY_DEVICE_ID,
                                   fIngress ? SECY_ROLE_INGRESS :
                                              SECY_ROLE_EGRESS,
                                   &Settings);
#endif
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: SecY could not be initialized, error=%d\n",
                     SecY_Rc);
            return false;
        }

        Log_FormattedMessage("DA_MACSEC: SecY is initialized successfully\n");
    }


    /* Install SA with transform record */
    {
        ZEROINIT(SA_Params);

#ifdef DA_MACSEC_MODE_INGRESS
        if (fIngress)
        {
            SA_Params.ActionType = SECY_SA_ACTION_INGRESS;
            SA_Params.DropType = SECY_SA_DROP_CRC_ERROR;
            SA_Params.DestPort = SECY_PORT_CONTROLLED;

            SA_Params.Params.Ingress.ValidateFramesTagged =
                SECY_FRAME_VALIDATE_STRICT;
            SA_Params.Params.Ingress.fReplayProtect = true;
            SA_Params.Params.Ingress.SCI_p = SCI1;
            SA_Params.Params.Ingress.AN = 2;
            SA_Params.Params.Ingress.fAllowTagged = true;
            SA_Params.Params.Ingress.PreSecTagAuthLength = 12;

            SA_Params.TransformRecord_p =
                da_macsec_build_sa(&Transform_Params_Ingress1,
                    &SAWordCount);
            SA_Params.SA_WordCount = SAWordCount;
        }
#endif /* DA_MACSEC_MODE_INGRESS */

#ifdef DA_MACSEC_MODE_EGRESS
        if (!fIngress)
        {
            SA_Params.ActionType = SECY_SA_ACTION_EGRESS;
            SA_Params.DropType = SECY_SA_DROP_INTERNAL;
            SA_Params.DestPort = SECY_PORT_COMMON;

            SA_Params.Params.Egress.fProtectFrames = true;
            SA_Params.Params.Egress.fIncludeSCI = true;
            SA_Params.Params.Egress.fConfProtect = true;
            SA_Params.Params.Egress.fAllowDataPkts = true;
            SA_Params.Params.Egress.PreSecTagAuthLength = 12;

            SA_Params.TransformRecord_p =
                da_macsec_build_sa(&Transform_Params_Egress1, &SAWordCount);
            SA_Params.SA_WordCount = SAWordCount;
        }
#endif /* DA_MACSEC_MODE_EGRESS */

        SecY_Rc = SecY_SA_Add(SECY_DEVICE_ID, vPort, &SecY_SAHandle1, &SA_Params);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: Failed, SecY_SA_Add()=%d\n", SecY_Rc);
            goto error_exit_init;
        }

        if (fVerbose)
        {
            Log_FormattedMessage("DA_MACSEC: Transform 32-bit word count %d\n",
                                 SA_Params.SA_WordCount);
            Log_HexDump32("DA_MACSEC: Transform data",
                          0,
                          SA_Params.TransformRecord_p,
                          SA_Params.SA_WordCount);
        }

        if (SA_Params.TransformRecord_p)
        {
            da_macsec_free(SA_Params.TransformRecord_p);
        }

        if (fVerbose)
        {
            Log_FormattedMessage("DA_MACSEC: SA with Transform Record added\n");
        }
    }

    /* Allocate packet buffers */
    InputPktHostAddress = da_macsec_malloc(PKT_BUFFER_BYTE_COUNT);
    if (InputPktHostAddress == NULL)
    {
        LOG_CRIT("DA_MACSEC: Failed, packet buffer allocation\n");
        goto error_exit;
    }

    ProcessedPktHostAddress = da_macsec_malloc(PKT_BUFFER_BYTE_COUNT);
    if (ProcessedPktHostAddress == NULL)
    {
        LOG_CRIT("DA_MACSEC: Failed, packet buffer allocation\n");
        goto error_exit;
    }

    ExpectedPktHostAddress = da_macsec_malloc(PKT_BUFFER_BYTE_COUNT);
    if (ExpectedPktHostAddress == NULL)
    {
        LOG_CRIT("DA_MACSEC: Failed, packet buffer allocation\n");
        goto error_exit;
    }

    if (fVerbose)
    {
        Log_FormattedMessage("DA_MACSEC: Packet buffers allocated\n");
    }

    /* At this point the Engine is ready to accept packets and
       perform classification and processing autonomously */
    if (fVerbose)
    {
        Log_FormattedMessage("DA_MACSEC: Ready to process packets\n");
    }

    /* Packet processing Packet #1 using old key. */
    {
        PktIO_Packet_Status_In_t PktStatusIn;
        PktIO_Packet_Status_Out_t PktStatusOut;
        int RetCode;
        unsigned int ByteCount;

        if (fVerbose)
        {
            Log_FormattedMessage("DA_MACSEC: First packet, use old key.\n");
        }


#ifdef DA_MACSEC_MODE_INGRESS
        if (fIngress)
        {
            /* Input packet */
            PktByteCount = sizeof(Macsec_Packet1);
            memcpy(InputPktHostAddress,
                   Macsec_Packet1,
                   PktByteCount);

            if (fVerbose)
            {
                Log_FormattedMessage("DA_MACSEC: "
                                     "Process input packet of size %d\n",
                                     PktByteCount);
                Log_HexDump("Input packet",
                            0,
                            Macsec_Packet1,
                            PktByteCount);
            }

            /* Expected packet */
            ExpectedPktByteCount = sizeof(Plain_Packet);
            memcpy(ExpectedPktHostAddress,
                   Plain_Packet,
                   ExpectedPktByteCount);
        }
#endif /* DA_MACSEC_MODE_INGRESS */

#ifdef DA_MACSEC_MODE_EGRESS
        if (!fIngress)
        {
            /* Input packet */
            PktByteCount = sizeof(Plain_Packet);
            memcpy(InputPktHostAddress,
                   Plain_Packet,
                   PktByteCount);

            if (fVerbose)
            {
                Log_FormattedMessage("DA_MACSEC: "
                                     "Process input packet of size %d\n",
                                     PktByteCount);
                Log_HexDump("Input packet",
                            0,
                            Plain_Packet,
                            PktByteCount);
            }

            /* Expected packet */
            ExpectedPktByteCount = sizeof(Macsec_Packet1);
            memcpy(ExpectedPktHostAddress,
                   Macsec_Packet1,
                   ExpectedPktByteCount);
        }
#endif /* DA_MACSEC_MODE_EGRESS */

        /* Fill in the status data structure */
        ZEROINIT(PktStatusIn);

        /* Set vPort number */
        PktStatusIn.vPort        = vPort;
        PktStatusIn.SecTAGOffset = 12;  /* 12 bytes for typical Ethernet frame */

        RetCode = PktIO_Packet_Put(InputPktHostAddress,
                                   PktByteCount,
                                   &PktStatusIn,
                                   Channel,
                                   fIngress ? PKTIO_PACKET_DIRECTION_INGRESS :
                                              PKTIO_PACKET_DIRECTION_EGRESS);
        if (RetCode != 0)
        {
            LOG_CRIT("DA_MACSEC: PktIO_Packet_Put error %d\n", RetCode);
            goto error_exit;
        }
        if (fVerbose)
        {
            Log_FormattedMessage("DA_MACSEC: Packet submitted\n");
        }

        /* Fill in the status data structure */
        ZEROINIT(PktStatusOut);

        /* Receive the processed packet */
        if (da_macsec_get_one(fIngress,
                              ProcessedPktHostAddress,
                              &ByteCount,
                              &PktStatusOut,
                              Channel) == 0 &&
            PktStatusOut.PacketStatusMask == 0)
        {
            LOG_CRIT("DA_MACSEC: Error obtaining result packet\n");
            goto error_exit;
        }

        if (fVerbose)
        {
            Log_FormattedMessage("DA_MACSEC: PktIO_Packet_Get Size/"
                                 "StatusMask/Channel/vPort/SAIndex/SCIndex"
                                 "/RuleIndex: %d/0x%X/%d/%d/%d/%d/%d\n",
                                 ByteCount,
                                 PktStatusOut.PacketStatusMask,
                                 Channel,
                                 PktStatusOut.vPort,
                                 PktStatusOut.SAIndex,
                                 PktStatusOut.SCIndex,
                                 PktStatusOut.RuleIndex);
            Log_HexDump("Result packet",
                        0,
                        ProcessedPktHostAddress,
                        ByteCount);
        }

        /* Compare the received packet with the expected. They must match. */
        if ( ByteCount != ExpectedPktByteCount)
        {
            LOG_CRIT("DA_MACSEC: Packet sizes differ expected=%d, received=%d\n",
                     ExpectedPktByteCount,
                     ByteCount);
            Log_HexDump("Expected packet",
                        0,
                        ExpectedPktHostAddress,
                        ExpectedPktByteCount);
            goto error_exit;
        }

        if (memcmp(ProcessedPktHostAddress,
                   ExpectedPktHostAddress,
                   ExpectedPktByteCount) != 0)
        {
            LOG_CRIT("DA_MACSEC: Contents of packets differ size=%d\n",
                     ExpectedPktByteCount);
            Log_HexDump("Expected packet",
                        0,
                        ExpectedPktHostAddress,
                        ExpectedPktByteCount);
            goto error_exit;
        }
    }

    /* Install second SA with transform record */
    {
        ZEROINIT(SA_Params);

#ifdef DA_MACSEC_MODE_INGRESS
        if (fIngress)
        {
            SA_Params.ActionType = SECY_SA_ACTION_INGRESS;
            SA_Params.DropType = SECY_SA_DROP_CRC_ERROR;
            SA_Params.DestPort = SECY_PORT_CONTROLLED;

            SA_Params.Params.Ingress.ValidateFramesTagged =
                SECY_FRAME_VALIDATE_STRICT;
            SA_Params.Params.Ingress.fReplayProtect = true;
            SA_Params.Params.Ingress.SCI_p = SCI1;
            SA_Params.Params.Ingress.AN = 3;
            SA_Params.Params.Ingress.fAllowTagged = true;
            SA_Params.Params.Ingress.PreSecTagAuthLength = 12;

            SA_Params.TransformRecord_p =
                da_macsec_build_sa(&Transform_Params_Ingress2, &SAWordCount);
            SA_Params.SA_WordCount = SAWordCount;
        }

        SecY_Rc = SecY_SA_Add(SECY_DEVICE_ID, vPort, &SecY_SAHandle2, &SA_Params);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: Failed, SecY_SA_Add()=%d\n", SecY_Rc);
            goto error_exit;
        }

#endif /* DA_MACSEC_MODE_INGRESS */

#ifdef DA_MACSEC_MODE_EGRESS
        if (!fIngress)
        {
            SA_Params.ActionType = SECY_SA_ACTION_EGRESS;
            SA_Params.DropType = SECY_SA_DROP_INTERNAL;
            SA_Params.DestPort = SECY_PORT_COMMON;

            SA_Params.Params.Egress.fProtectFrames = true;
            SA_Params.Params.Egress.fIncludeSCI = true;
            SA_Params.Params.Egress.fConfProtect = true;
            SA_Params.Params.Egress.fAllowDataPkts = true;
            SA_Params.Params.Egress.PreSecTagAuthLength = 12;

            SA_Params.TransformRecord_p =
                da_macsec_build_sa(&Transform_Params_Egress2, &SAWordCount);
            SA_Params.SA_WordCount = SAWordCount;
        }

        /* Use SecY_SA_Chain instead of SecY_SA_Add to add new egress SA. */
        SecY_Rc = SecY_SA_Chain(SECY_DEVICE_ID,
                                SecY_SAHandle1,
                                &SecY_SAHandle2,
                                &SA_Params);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: Failed, SecY_SA_Chain()=%d\n", SecY_Rc);
            goto error_exit;
        }


#endif /* DA_MACSEC_MODE_EGRESS */


        if (fVerbose)
        {
            Log_FormattedMessage("DA_MACSEC: Transform 32-bit word count %d\n",
                                 SA_Params.SA_WordCount);
            Log_HexDump32("DA_MACSEC: Transform data",
                          0,
                          SA_Params.TransformRecord_p,
                          SA_Params.SA_WordCount);
        }

        if (SA_Params.TransformRecord_p)
        {
            da_macsec_free(SA_Params.TransformRecord_p);
        }

        if (fVerbose)
        {
            Log_FormattedMessage("DA_MACSEC: Second SA with Transform Record added\n");
        }
    }

    if (fVerbose)
    {
        Log_FormattedMessage("DA_MACSEC: Process second packet, old key\n");
    }

    /* Packet processing Packet #2 using old key. */
    {
        PktIO_Packet_Status_In_t PktStatusIn;
        PktIO_Packet_Status_Out_t PktStatusOut;
        int RetCode;
        unsigned int ByteCount;

#ifdef DA_MACSEC_MODE_INGRESS
        if (fIngress)
        {
            /* Input packet */
            PktByteCount = sizeof(Macsec_Packet2);
            memcpy(InputPktHostAddress,
                   Macsec_Packet2,
                   PktByteCount);

            if (fVerbose)
            {
                Log_FormattedMessage("DA_MACSEC: "
                                     "Process input packet of size %d\n",
                                     PktByteCount);
                Log_HexDump("Input packet",
                            0,
                            Macsec_Packet2,
                            PktByteCount);
            }

            /* Expected packet */
            ExpectedPktByteCount = sizeof(Plain_Packet);
            memcpy(ExpectedPktHostAddress,
                   Plain_Packet,
                   ExpectedPktByteCount);
        }
#endif /* DA_MACSEC_MODE_INGRESS */

#ifdef DA_MACSEC_MODE_EGRESS
        if (!fIngress)
        {
            /* Input packet */
            PktByteCount = sizeof(Plain_Packet);
            memcpy(InputPktHostAddress,
                   Plain_Packet,
                   PktByteCount);

            if (fVerbose)
            {
                Log_FormattedMessage("DA_MACSEC: "
                                     "Process input packet of size %d\n",
                                     PktByteCount);
                Log_HexDump("Input packet",
                            0,
                            Plain_Packet,
                            PktByteCount);
            }

            /* Expected packet */
            ExpectedPktByteCount = sizeof(Macsec_Packet2);
            memcpy(ExpectedPktHostAddress,
                   Macsec_Packet2,
                   ExpectedPktByteCount);
        }
#endif /* DA_MACSEC_MODE_EGRESS */

        /* Fill in the status data structure */
        ZEROINIT(PktStatusIn);

        /* Set vPort number */
        PktStatusIn.vPort        = vPort;
        PktStatusIn.SecTAGOffset = 12;  /* 12 bytes for typical Ethernet frame */

        RetCode = PktIO_Packet_Put(InputPktHostAddress,
                                   PktByteCount,
                                   &PktStatusIn,
                                   Channel,
                                   fIngress ? PKTIO_PACKET_DIRECTION_INGRESS :
                                              PKTIO_PACKET_DIRECTION_EGRESS);
        if (RetCode != 0)
        {
            LOG_CRIT("DA_MACSEC: PktIO_Packet_Put error %d\n", RetCode);
            goto error_exit;
        }
        if (fVerbose)
        {
            Log_FormattedMessage("DA_MACSEC: Packet submitted\n");
        }

        /* Fill in the status data structure */
        ZEROINIT(PktStatusOut);

        /* Receive the processed packet */
        if (da_macsec_get_one(fIngress,
                              ProcessedPktHostAddress,
                              &ByteCount,
                              &PktStatusOut,
                              Channel) == 0 &&
            PktStatusOut.PacketStatusMask == 0)
        {
            LOG_CRIT("DA_MACSEC: Error obtaining result packet\n");
            goto error_exit;
        }

        if (fVerbose)
        {
            Log_FormattedMessage("DA_MACSEC: PktIO_Packet_Get Size/"
                                 "StatusMask/Channel/vPort/SAIndex/SCIndex"
                                 "/RuleIndex: %d/0x%X/%d/%d/%d/%d/%d\n",
                                 ByteCount,
                                 PktStatusOut.PacketStatusMask,
                                 Channel,
                                 PktStatusOut.vPort,
                                 PktStatusOut.SAIndex,
                                 PktStatusOut.SCIndex,
                                 PktStatusOut.RuleIndex);
            Log_HexDump("Result packet",
                        0,
                        ProcessedPktHostAddress,
                        ByteCount);
        }

        /* Compare the received packet with the expected. They must match. */
        if ( ByteCount != ExpectedPktByteCount)
        {
            LOG_CRIT("DA_MACSEC: Packet sizes differ expected=%d, received=%d\n",
                     ExpectedPktByteCount,
                     ByteCount);
            Log_HexDump("Expected packet",
                        0,
                        ExpectedPktHostAddress,
                        ExpectedPktByteCount);
            goto error_exit;
        }

        if (memcmp(ProcessedPktHostAddress,
                   ExpectedPktHostAddress,
                   ExpectedPktByteCount) != 0)
        {
            LOG_CRIT("DA_MACSEC: Contents of packets differ size=%d\n",
                     ExpectedPktByteCount);
            Log_HexDump("Expected packet",
                        0,
                        ExpectedPktHostAddress,
                        ExpectedPktByteCount);
            goto error_exit;
        }
    }


#ifdef DA_MACSEC_MODE_EGRESS
    /* For egress, do a manual switch from SA 1 to SA 2. */
    SecY_Rc = SecY_SA_Switch(SECY_DEVICE_ID,
                             SecY_SAHandle1,
                             SecY_SAHandle2,
                             &SA_Params);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        LOG_CRIT("DA_MACSEC: Failed, SecY_SA_Remove()=%d\n", SecY_Rc);
        goto error_exit;
    }
    if (fVerbose)
    {
        Log_FormattedMessage("DA_MACSEC: Egress SA switched\n");
    }

#endif

    SecY_Rc = SecY_SA_Remove(SECY_DEVICE_ID, SecY_SAHandle1);
    SecY_SAHandle1 = SecY_SAHandle_NULL;
    if (SecY_Rc != SECY_STATUS_OK)
    {
            LOG_CRIT("DA_MACSEC: Failed, SecY_SA_Remove()=%d\n", SecY_Rc);
            fSuccess = false;
    }
    if (fVerbose)
    {
        Log_FormattedMessage("DA_MACSEC: Old SA removed\n");
    }

    if (fVerbose)
    {
        Log_FormattedMessage("DA_MACSEC: Process third packet, new key\n");
    }
    /* Packet processing Packet #3 using new key. */
    {
        PktIO_Packet_Status_In_t PktStatusIn;
        PktIO_Packet_Status_Out_t PktStatusOut;
        int RetCode;
        unsigned int ByteCount;

#ifdef DA_MACSEC_MODE_INGRESS
        if (fIngress)
        {
            /* Input packet */
            PktByteCount = sizeof(Macsec_Packet3);
            memcpy(InputPktHostAddress,
                   Macsec_Packet3,
                   PktByteCount);

            if (fVerbose)
            {
                Log_FormattedMessage("DA_MACSEC: "
                                     "Process input packet of size %d\n",
                                     PktByteCount);
                Log_HexDump("Input packet",
                            0,
                            Macsec_Packet3,
                            PktByteCount);
            }

            /* Expected packet */
            ExpectedPktByteCount = sizeof(Plain_Packet);
            memcpy(ExpectedPktHostAddress,
                   Plain_Packet,
                   ExpectedPktByteCount);
        }
#endif /* DA_MACSEC_MODE_INGRESS */

#ifdef DA_MACSEC_MODE_EGRESS
        if (!fIngress)
        {
            /* Input packet */
            PktByteCount = sizeof(Plain_Packet);
            memcpy(InputPktHostAddress,
                   Plain_Packet,
                   PktByteCount);

            if (fVerbose)
            {
                Log_FormattedMessage("DA_MACSEC: "
                                     "Process input packet of size %d\n",
                                     PktByteCount);
                Log_HexDump("Input packet",
                            0,
                            Plain_Packet,
                            PktByteCount);
            }

            /* Expected packet */
            ExpectedPktByteCount = sizeof(Macsec_Packet3);
            memcpy(ExpectedPktHostAddress,
                   Macsec_Packet3,
                   ExpectedPktByteCount);
        }
#endif /* DA_MACSEC_MODE_EGRESS */

        /* Fill in the status data structure */
        ZEROINIT(PktStatusIn);

        /* Set vPort number */
        PktStatusIn.vPort        = vPort;
        PktStatusIn.SecTAGOffset = 12;  /* 12 bytes for typical Ethernet frame */

        RetCode = PktIO_Packet_Put(InputPktHostAddress,
                                   PktByteCount,
                                   &PktStatusIn,
                                   Channel,
                                   fIngress ? PKTIO_PACKET_DIRECTION_INGRESS :
                                              PKTIO_PACKET_DIRECTION_EGRESS);
        if (RetCode != 0)
        {
            LOG_CRIT("DA_MACSEC: PktIO_Packet_Put error %d\n", RetCode);
            goto error_exit;
        }
        if (fVerbose)
        {
            Log_FormattedMessage("DA_MACSEC: Packet submitted\n");
        }

        /* Fill in the status data structure */
        ZEROINIT(PktStatusOut);

        /* Receive the processed packet */
        if (da_macsec_get_one(fIngress,
                              ProcessedPktHostAddress,
                              &ByteCount,
                              &PktStatusOut,
                              Channel) == 0 &&
            PktStatusOut.PacketStatusMask == 0)
        {
            LOG_CRIT("DA_MACSEC: Error obtaining result packet\n");
            goto error_exit;
        }

        if (fVerbose)
        {
            Log_FormattedMessage("DA_MACSEC: PktIO_Packet_Get Size/"
                                 "StatusMask/Channel/vPort/SAIndex/SCIndex"
                                 "/RuleIndex: %d/0x%X/%d/%d/%d/%d/%d\n",
                                 ByteCount,
                                 PktStatusOut.PacketStatusMask,
                                 Channel,
                                 PktStatusOut.vPort,
                                 PktStatusOut.SAIndex,
                                 PktStatusOut.SCIndex,
                                 PktStatusOut.RuleIndex);
            Log_HexDump("Result packet",
                        0,
                        ProcessedPktHostAddress,
                        ByteCount);
        }

        /* Compare the received packet with the expected. They must match. */
        if ( ByteCount != ExpectedPktByteCount)
        {
            LOG_CRIT("DA_MACSEC: Packet sizes differ expected=%d, received=%d\n",
                     ExpectedPktByteCount,
                     ByteCount);
            Log_HexDump("Expected packet",
                        0,
                        ExpectedPktHostAddress,
                        ExpectedPktByteCount);
            goto error_exit;
        }

        if (memcmp(ProcessedPktHostAddress,
                   ExpectedPktHostAddress,
                   ExpectedPktByteCount) != 0)
        {
            LOG_CRIT("DA_MACSEC: Contents of packets differ size=%d\n",
                     ExpectedPktByteCount);
            Log_HexDump("Expected packet",
                        0,
                        ExpectedPktHostAddress,
                        ExpectedPktByteCount);
            goto error_exit;
        }
    }



    if (fVerbose)
    {
        Log_FormattedMessage("DA_MACSEC: Finished processing packets\n");
    }


    /* If we made it to here, consider this run a success. Any jump */
    /* to one of the error labels below will skip "success = true" */
    fSuccess = true;

error_exit:

    /* Remove SA */
    if (!SecY_SAHandle_IsSame(&SecY_SAHandle1, &SecY_SAHandle_NULL))
    {
        SecY_Rc = SecY_SA_Remove(SECY_DEVICE_ID, SecY_SAHandle1);
        SecY_SAHandle1 = SecY_SAHandle_NULL;
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: Failed, SecY_SA_Remove()=%d\n", SecY_Rc);
            fSuccess = false;
        }
    }

    if (!SecY_SAHandle_IsSame(&SecY_SAHandle2, &SecY_SAHandle_NULL))
    {
        SecY_Rc = SecY_SA_Remove(SECY_DEVICE_ID, SecY_SAHandle2);
        SecY_SAHandle2 = SecY_SAHandle_NULL;
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: Failed, SecY_SA_Remove()=%d\n", SecY_Rc);
            fSuccess = false;
        }
    }


    /* Remove the buffers occupied by the packets */
    if (InputPktHostAddress)
    {
        da_macsec_free(InputPktHostAddress);
    }

    if (ProcessedPktHostAddress)
    {
        da_macsec_free(ProcessedPktHostAddress);
    }

    if (ExpectedPktHostAddress)
    {
        da_macsec_free(ExpectedPktHostAddress);
    }


error_exit_init:
    SecY_Device_Uninit(SECY_DEVICE_ID);

    return fSuccess;
    }


/* end of file da_secy_rekey.c */
