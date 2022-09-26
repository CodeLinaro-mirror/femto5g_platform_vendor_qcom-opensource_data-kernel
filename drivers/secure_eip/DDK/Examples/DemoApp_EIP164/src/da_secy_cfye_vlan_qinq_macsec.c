/* da_secy_cfye_vlan_qinq_macsec.c
 *
 * Demo Application, MACsec transform test using SecY and CfyE API for VLAN
 * QinQ with one VLAN tag in the clear and one inside the MACsec part
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

#ifdef DA_MACSEC_USE_CFYE
#include "api_cfye.h"

/*----------------------------------------------------------------------------
 * Definitions and macros
 */

/*----------------------------------------------------------------------------
 * Local variables
 */

#ifdef DA_MACSEC_MODE_INGRESS
/* MACsec key */
static uint8_t K1[] = {
    0x88, 0xee, 0x08, 0x7f, 0xd9, 0x5d, 0xa9, 0xfb,
    0xf6, 0x72, 0x5a, 0xa9, 0xd7, 0x57, 0xb0, 0xcd,
};

/* MACsec SCI */
static uint8_t SCI1[] = {
    0x7a, 0xe8, 0xe2, 0xca, 0x4e, 0xc5, 0x9a, 0x21,
};

static da_sa_params_t Transform_Params_QinQ_Ingress_MACsec =
{
    SAB_DIRECTION_INGRESS,
    SAB_OP_MACSEC,
    0,
    1,
    K1,
    sizeof(K1),
    SCI1,
    NULL,
    NULL,
    0x2e58495c, /* Seq0 */
    0,
    0,
#if defined(DA_IPSEC_ENABLE)
    0,
#endif
};

/* VLAN QinQ (MACsec) source packet */
static const uint8_t SrcPacket_QinQ_MACsec_Ingress[] =
{
    0xD6, 0x09, 0xB1, 0xF0, 0x56, 0x63, 0x7A, 0x0D, 0x46, 0xDF, 0x99, 0x8D, 0x81, 0x00, 0x01, 0xA1,
    0x88, 0xE5, 0x2D, 0x00, 0x2E, 0x58, 0x49, 0x5C, 0x7A, 0xE8, 0xE2, 0xCA, 0x4E, 0xC5, 0x9A, 0x21,
    0xE1, 0x22, 0x13, 0x26, 0x20, 0x8A, 0x7D, 0xFA, 0x33, 0xEE, 0xBB, 0x4E, 0x49, 0xB1, 0x98, 0x84,
    0x2E, 0xE2, 0x15, 0xC0, 0x6A, 0xDF, 0x1D, 0x2D, 0xDD, 0xC6, 0x00, 0xE6, 0x73, 0xD8, 0x7E, 0x68,
    0xBD, 0xAF, 0x92, 0x48, 0x0C, 0x9D, 0x52, 0xA9, 0x13, 0x1C, 0xDB, 0x7C, 0x3A, 0x0E, 0xEE, 0xD7,
    0xDD, 0x84, 0x89, 0x46, 0xBA, 0xD8, 0x3A, 0x91, 0xAB, 0xEA, 0x89, 0xD1, 0xBD, 0xB0, 0xFB, 0x1D,
    0x2E, 0xEF, 0x9C, 0xC3, 0xD7, 0x84
};

static const uint8_t * MAC_DA_QinQ_MACsec_Ingress_p =
    &SrcPacket_QinQ_MACsec_Ingress[0];
static const uint8_t * VLAN_1Q_MACsec_Ingress_p =
    &SrcPacket_QinQ_MACsec_Ingress[12];
static const uint8_t * TCI_AN_QinQ_MACsec_Ingress_p =
    &SrcPacket_QinQ_MACsec_Ingress[18];
static const uint8_t * SCI_QinQ_MACsec_Ingress_p =
    &SrcPacket_QinQ_MACsec_Ingress[24];

/* VLAN QinQ destination packet */
static const uint8_t DstPacket_QinQ_MACsec_Ingress[] =
{
    0xD6, 0x09, 0xB1, 0xF0, 0x56, 0x63, 0x7A, 0x0D, 0x46, 0xDF, 0x99, 0x8D, 0x81, 0x00, 0x01, 0xA1,
    0x92, 0x00, 0x02, 0xB2, 0x08, 0x00, 0x24, 0xC6, 0x98, 0x02, 0xB5, 0x76, 0x99, 0x42, 0xD7, 0xE8,
    0xE2, 0x6E, 0x85, 0x36, 0xDC, 0x96, 0x7F, 0xE9, 0x7E, 0x9E, 0x0C, 0xA0, 0x2C, 0x57, 0xA9, 0x97,
    0x8D, 0x12, 0x8A, 0xDA, 0xE4, 0x65, 0x82, 0xAD, 0x06, 0xEF, 0x16, 0x6B, 0xC7, 0xF0, 0x32, 0x6C,
    0xE0, 0x77, 0x11, 0x56, 0x19, 0xAB,
};
#endif /* DA_MACSEC_MODE_INGRESS */

#ifdef DA_MACSEC_MODE_EGRESS
/* MACsec key */
static uint8_t K2[] = {
    0x88, 0xee, 0x08, 0x7f, 0xd9, 0x5d, 0xa9, 0xfb,
    0xf6, 0x72, 0x5a, 0xa9, 0xd7, 0x57, 0xb0, 0xcd,
};

/* MACsec SCI */
static uint8_t SCI2[] = {
    0x7a, 0xe8, 0xe2, 0xca, 0x4e, 0xc5, 0x9a, 0x21,
};

static da_sa_params_t Transform_Params_QinQ_Egress_MACsec =
{
    SAB_DIRECTION_EGRESS,
    SAB_OP_MACSEC,
    0,
    1,
    K2,
    sizeof(K2),
    SCI2,
    NULL,
    NULL,
    0x2e58495b, /* Seq0 */
    0,
    0,
#if defined(DA_IPSEC_ENABLE)
    0,
#endif
};

/* VLAN QinQ source packet */
static const uint8_t SrcPacket_QinQ_MACsec_Egress[] =
{
    0xD6, 0x09, 0xB1, 0xF0, 0x56, 0x63, 0x7A, 0x0D, 0x46, 0xDF, 0x99, 0x8D, 0x81, 0x00, 0x01, 0xA1,
    0x92, 0x00, 0x02, 0xB2, 0x08, 0x00, 0x24, 0xC6, 0x98, 0x02, 0xB5, 0x76, 0x99, 0x42, 0xD7, 0xE8,
    0xE2, 0x6E, 0x85, 0x36, 0xDC, 0x96, 0x7F, 0xE9, 0x7E, 0x9E, 0x0C, 0xA0, 0x2C, 0x57, 0xA9, 0x97,
    0x8D, 0x12, 0x8A, 0xDA, 0xE4, 0x65, 0x82, 0xAD, 0x06, 0xEF, 0x16, 0x6B, 0xC7, 0xF0, 0x32, 0x6C,
    0xE0, 0x77, 0x11, 0x56, 0x19, 0xAB,
};

static const uint8_t * MAC_DA_QinQ_MACsec_Egress_p =
    &SrcPacket_QinQ_MACsec_Egress[0];
static const uint8_t * VLAN_1Q_MACsec_Egress_p =
    &SrcPacket_QinQ_MACsec_Egress[12];

/* VLAN QinQ (MACsec) destination packet */
static const uint8_t DstPacket_QinQ_MACsec_Egress[] =
{
    0xD6, 0x09, 0xB1, 0xF0, 0x56, 0x63, 0x7A, 0x0D, 0x46, 0xDF, 0x99, 0x8D, 0x81, 0x00, 0x01, 0xA1,
    0x88, 0xE5, 0x2D, 0x00, 0x2E, 0x58, 0x49, 0x5C, 0x7A, 0xE8, 0xE2, 0xCA, 0x4E, 0xC5, 0x9A, 0x21,
    0xE1, 0x22, 0x13, 0x26, 0x20, 0x8A, 0x7D, 0xFA, 0x33, 0xEE, 0xBB, 0x4E, 0x49, 0xB1, 0x98, 0x84,
    0x2E, 0xE2, 0x15, 0xC0, 0x6A, 0xDF, 0x1D, 0x2D, 0xDD, 0xC6, 0x00, 0xE6, 0x73, 0xD8, 0x7E, 0x68,
    0xBD, 0xAF, 0x92, 0x48, 0x0C, 0x9D, 0x52, 0xA9, 0x13, 0x1C, 0xDB, 0x7C, 0x3A, 0x0E, 0xEE, 0xD7,
    0xDD, 0x84, 0x89, 0x46, 0xBA, 0xD8, 0x3A, 0x91, 0xAB, 0xEA, 0x89, 0xD1, 0xBD, 0xB0, 0xFB, 0x1D,
    0x2E, 0xEF, 0x9C, 0xC3, 0xD7, 0x84
};
#endif /* DA_MACSEC_MODE_EGRESS */


/*----------------------------------------------------------------------------
 * da_secy_cfye_macsec_transform
 */
bool
da_secy_cfye_QinQ_MACsec_transform(
        bool fVerbose,
        bool fIngress)
{
    unsigned int vPort = 0;
    unsigned int Channel = 0;

    SecY_Status_t SecY_Rc;
    SecY_SAHandle_t SecY_SAHandle;
    CfyE_Status_t CfyE_Rc;
    CfyE_vPortHandle_t CfyE_vPortHandle = CfyE_vPortHandle_NULL;
    CfyE_RuleHandle_t CfyE_RuleHandle = CfyE_RuleHandle_NULL;

    unsigned int PktByteCount;
    unsigned int ExpectedPktByteCount;
    uint8_t * InputPktHostAddress = NULL;
    uint8_t * ProcessedPktHostAddress = NULL;
    uint8_t * ExpectedPktHostAddress = NULL;
    bool fSuccess = false;

    Log_FormattedMessage("DA_MACSEC: Starting test for %sgress\n",
                         fIngress ? "in" : "e");

    if (fVerbose)
    {
        Log_FormattedMessage("DA_MACSEC: Perform Transform for 802.1Q "
                             "(QinQ)\n");
    }

    SecY_SAHandle = SecY_SAHandle_NULL;

#ifndef DA_MACSEC_MODE_INGRESS
    if (fIngress)
        return false;
#endif
#ifndef DA_MACSEC_MODE_EGRESS
    if (!fIngress)
        return false;
#endif

#if defined(DA_MACSEC_MODE_EGRESS) && defined(DA_MACSEC_MODE_INGRESS)
    #error "Not supported combination"
#endif
    {
        CfyE_Init_t Settings;

        Log_FormattedMessage("DA_MACSEC: Initializing CfyE\n");

        ZEROINIT(Settings);

        CfyE_Rc = CfyE_Device_Init(CFYE_DEVICE_ID,
                                   fIngress ? CFYE_ROLE_INGRESS :
                                              CFYE_ROLE_EGRESS,
                                   &Settings);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: CfyE could not be initialized, error=%d\n",
                     CfyE_Rc);
            return false;
        }

        Log_FormattedMessage("DA_MACSEC: CfyE is initialized successfully\n");
    }

    {
        SecY_Settings_t Settings;

        Log_FormattedMessage("DA_MACSEC: Initializing SecY\n");

        ZEROINIT(Settings);

        /* Non-matching SA flow packet processing rules */
        /* Default rule is to drop non-matching SA packets */
        Settings.DropBypass.DropType = SECY_SA_DROP_CRC_ERROR;

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


    if (fVerbose)
    {
        Log_FormattedMessage("DA_MACSEC: Preparing packet(s)\n");
    }

    /* Install vPort for use with SA */
    {
        CfyE_vPort_t vPortParams;

        ZEROINIT(vPortParams);

        vPortParams.SecTagOffset = 16;
#ifdef DA_MACSEC_MODE_EGRESS
        vPortParams.PktExtension = 3;
#endif

        CfyE_Rc = CfyE_vPort_Add(CFYE_DEVICE_ID,
                                 &CfyE_vPortHandle,
                                 &vPortParams,
                                 SECY_MODE_MACSEC);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: Failed, CfyE_vPort_Add()=%d\n", CfyE_Rc);
            goto error_exit;
        }

        /* Now get vPort index to use when installing SA: */
        CfyE_vPortIndex_Get(CfyE_vPortHandle, &vPort);

        if (fVerbose)
        {
            Log_FormattedMessage("DA_MACSEC: vPort added\n");
        }

    }

    /* Install SA with transform record */
    {
        SecY_SA_t SA_Params;
        uint32_t SAWordCount = 0;

        ZEROINIT(SA_Params);

#ifdef DA_MACSEC_MODE_INGRESS
        if (fIngress)
        {
            SA_Params.ActionType = SECY_SA_ACTION_INGRESS;
            SA_Params.DropType = SECY_SA_DROP_CRC_ERROR;
            SA_Params.DestPort = SECY_PORT_CONTROLLED;

            SA_Params.Params.Ingress.fSAInUse = true;
            SA_Params.Params.Ingress.fReplayProtect = true;
            SA_Params.Params.Ingress.ValidateFramesTagged =
                SECY_FRAME_VALIDATE_STRICT;
            SA_Params.Params.Ingress.SCI_p =
                da_macsec_discard_const(SCI_QinQ_MACsec_Ingress_p);
            SA_Params.Params.Ingress.AN = *TCI_AN_QinQ_MACsec_Ingress_p & 3;
            SA_Params.Params.Ingress.fAllowTagged = true;
            SA_Params.Params.Ingress.PreSecTagAuthLength = 12;

            SA_Params.TransformRecord_p =
                da_macsec_build_sa(&Transform_Params_QinQ_Ingress_MACsec,
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

            SA_Params.Params.Egress.fSAInUse = true;
            SA_Params.Params.Egress.fProtectFrames = true;
            SA_Params.Params.Egress.fIncludeSCI = true;
            SA_Params.Params.Egress.fConfProtect = true;
            SA_Params.Params.Egress.fAllowDataPkts = true;
            SA_Params.Params.Egress.PreSecTagAuthLength = 12;

            SA_Params.TransformRecord_p =
                da_macsec_build_sa(&Transform_Params_QinQ_Egress_MACsec,
                    &SAWordCount);
            SA_Params.SA_WordCount = SAWordCount;
        }
#endif /* DA_MACSEC_MODE_EGRESS */

        SecY_Rc = SecY_SA_Add(SECY_DEVICE_ID, vPort, &SecY_SAHandle, &SA_Params);
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

    /* Install parsers settings for SecTAG and VLAN tags */
    /* Also disable unused counters (for coverage) */
    {
        CfyE_Device_t DeviceParams;
        CfyE_HeaderParser_t HeaderParams;
        CfyE_SecTAG_Parser_t SecTAGParams;
        CfyE_VLAN_Parser_t VLANTagParams;
        CfyE_Statistics_Control_t StatisticsParams;

        ZEROINIT(DeviceParams);
        ZEROINIT(HeaderParams);
        ZEROINIT(SecTAGParams);
        ZEROINIT(VLANTagParams);
        ZEROINIT(StatisticsParams);

        SecTAGParams.fCheckVersion = true;
        SecTAGParams.fCheckKay = true;
        SecTAGParams.fCompType = true;
        SecTAGParams.MACsecTagValue = 0x88E5;

        VLANTagParams.CP.fParseQinQ = true;
        VLANTagParams.CP.fParseQTag = true;
        VLANTagParams.CP.fParseStag1 = true;
        VLANTagParams.fSTagUpEnable = true;
        VLANTagParams.fQTagUpEnable = true;
        VLANTagParams.DefaultUp = 0;
        VLANTagParams.UpTable1[0] = VLANTagParams.UpTable2[0] = 0;
        VLANTagParams.UpTable1[1] = VLANTagParams.UpTable2[1] = 1;
        VLANTagParams.UpTable1[2] = VLANTagParams.UpTable2[2] = 2;
        VLANTagParams.UpTable1[3] = VLANTagParams.UpTable2[3] = 3;
        VLANTagParams.UpTable1[4] = VLANTagParams.UpTable2[4] = 4;
        VLANTagParams.UpTable1[5] = VLANTagParams.UpTable2[5] = 5;
        VLANTagParams.UpTable1[6] = VLANTagParams.UpTable2[6] = 6;
        VLANTagParams.UpTable1[7] = VLANTagParams.UpTable2[7] = 7;
        VLANTagParams.QTag = 0x8100;
        VLANTagParams.STag1 = 0x9200;

        HeaderParams.SecTAG_Parser_p = &SecTAGParams;
        HeaderParams.VLAN_Parser_p = &VLANTagParams;
        DeviceParams.HeaderParser_p = &HeaderParams;

        /* Enable reset on read */
        StatisticsParams.fAutoStatCntrsReset = true;
        /* Disable the Classifier Channel related counters */
        StatisticsParams.CountIncDisCtrl = CFYE_CHAN_COUNT_INC_DIS;
        DeviceParams.StatControl_p = &StatisticsParams;

        CfyE_Rc = CfyE_Device_Update(CFYE_DEVICE_ID,
                                     Channel,
                                     &DeviceParams);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: Failed, CfyE_Device_Update()=%d\n", CfyE_Rc);
            goto error_exit_init;
        }
    }

    /* Install vPort which refers to the transform record installed previously */
    {
        CfyE_Rule_t RuleParams;

        ZEROINIT(RuleParams);

        RuleParams.Policy.vPortHandle = CfyE_vPortHandle;

        RuleParams.Mask.PacketType = CFYE_RULE_PKT_TYPE_MASK; /* Exact match on all these fields. */
        RuleParams.Mask.ChannelID = CFYE_RULE_CHANNEL_ID_MASK;
        RuleParams.Mask.NumTags = CFYE_RULE_NUMTAGS_MASK;

        RuleParams.Key.PacketType = CFYE_RULE_PKT_TYPE_OTHER;
        RuleParams.Key.ChannelID = Channel;
#ifdef DA_MACSEC_MODE_INGRESS
        RuleParams.Key.NumTags = (0x1 << 1);
#endif
#ifdef DA_MACSEC_MODE_EGRESS
        RuleParams.Key.NumTags = (0x1 << 2);
#endif

        RuleParams.DataMask[0] = 0xffffffff; /* Match on Destination address. */
        RuleParams.DataMask[1] = 0x0000ffff;
        RuleParams.DataMask[2] = 0xffffffff;

        {
            const uint8_t *p = NULL;
            const uint8_t *q = NULL;
#ifdef DA_MACSEC_MODE_INGRESS
            if (fIngress)
            {
                p = MAC_DA_QinQ_MACsec_Ingress_p;
                q = VLAN_1Q_MACsec_Ingress_p;

                RuleParams.Data[2] = (q[3]<<24) | (q[2]<<16) | 0xE588;
                RuleParams.DataMask[3] = 0x00000000;
            }
#endif
#ifdef DA_MACSEC_MODE_EGRESS
            if (!fIngress)
            {
                p = MAC_DA_QinQ_MACsec_Egress_p;
                q = VLAN_1Q_MACsec_Egress_p;

                RuleParams.Data[2] = (q[3]<<24) | (q[2]<<16) | 0x0008;
                RuleParams.Data[3] = (q[7]<<16) | (q[6]<<8);
                RuleParams.DataMask[3] = 0x00ffff00;
            }
#endif
            RuleParams.Data[0] = p[0] | (p[1]<<8) | (p[2]<<16) | (p[3]<<24);
            RuleParams.Data[1] = p[4] | (p[5]<<8);
        }

        CfyE_Rc = CfyE_Rule_Add(CFYE_DEVICE_ID, CfyE_vPortHandle,
                                &CfyE_RuleHandle, &RuleParams);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: Failed, CfyE_Rule_Add()=%d\n", CfyE_Rc);
            goto error_exit;
        }

        CfyE_Rc = CfyE_Rule_Enable(CFYE_DEVICE_ID, CfyE_RuleHandle, true);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: Failed, CfyE_Rule_Enable()=%d\n", CfyE_Rc);
            goto error_exit;
        }

        if (fVerbose)
        {
            Log_FormattedMessage("DA_MACSEC: Rule enabled\n");
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

    /* Packet processing */
    {
        PktIO_Packet_Status_In_t PktStatusIn;
        PktIO_Packet_Status_Out_t PktStatusOut;
        int RetCode;
        unsigned int ByteCount;

#ifdef DA_MACSEC_MODE_INGRESS
        if (fIngress)
        {
            /* Input packet */
            PktByteCount = sizeof(SrcPacket_QinQ_MACsec_Ingress);
            memcpy(InputPktHostAddress,
                   SrcPacket_QinQ_MACsec_Ingress,
                   PktByteCount);

            if (fVerbose)
            {
                Log_FormattedMessage("DA_MACSEC: "
                                     "Process input packet of size %d\n",
                                     PktByteCount);
                Log_HexDump("Input packet",
                            0,
                            SrcPacket_QinQ_MACsec_Ingress,
                            PktByteCount);
            }

            /* Expected packet */
            ExpectedPktByteCount = sizeof(DstPacket_QinQ_MACsec_Ingress);
            memcpy(ExpectedPktHostAddress,
                   DstPacket_QinQ_MACsec_Ingress,
                   ExpectedPktByteCount);
        }
#endif /* DA_MACSEC_MODE_INGRESS */

#ifdef DA_MACSEC_MODE_EGRESS
        if (!fIngress)
        {
            /* Input packet */
            PktByteCount = sizeof(SrcPacket_QinQ_MACsec_Egress);
            memcpy(InputPktHostAddress,
                   SrcPacket_QinQ_MACsec_Egress,
                   PktByteCount);

            if (fVerbose)
            {
                Log_FormattedMessage("DA_MACSEC: "
                                     "Process input packet of size %d\n",
                                     PktByteCount);
                Log_HexDump("Input packet",
                            0,
                            SrcPacket_QinQ_MACsec_Egress,
                            PktByteCount);
            }

            /* Expected packet */
            ExpectedPktByteCount = sizeof(DstPacket_QinQ_MACsec_Egress);
            memcpy(ExpectedPktHostAddress,
                   DstPacket_QinQ_MACsec_Egress,
                   ExpectedPktByteCount);
        }
#endif /* DA_MACSEC_MODE_EGRESS */

        /* Fill in the status data structure */
        ZEROINIT(PktStatusIn);

        PktStatusIn.SecTAGOffset = 16;  /* = 12 (first MAC addresses) + */
                                        /*   4 (first VLAN tag) bytes */

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

        /* Read the TCAM hit statistics counter */
        /* Note: It is assumed that the rule is inserted at the first index (0) */
        {
            CfyE_Statistics_TCAM_t TCAMStat;

            ZEROINIT(TCAMStat);

            CfyE_Rc = CfyE_Statistics_TCAM_Get(CFYE_DEVICE_ID, 0, &TCAMStat, true);
            if (CfyE_Rc != CFYE_STATUS_OK)
            {
                LOG_CRIT("DA_MACSEC: Failed, CfyE_TCAM__Statistics_Get()=%d\n",
                         CfyE_Rc);
                goto error_exit;
            }

            Log_FormattedMessage("DA_MACSEC: TCAM0 counter = %u\n",
                                 TCAMStat.Counter.Lo);

            if (TCAMStat.Counter.Lo == 0)
            {
                LOG_CRIT("DA_MACSEC: Failed, "
                         "TCAM0 counter should be not zero\n");
                goto error_exit;
            }
        }

#ifdef DA_MACSEC_MODE_INGRESS
        if (fIngress)
        {
            {
                SecY_SA_Stat_I_t SAStats;

                ZEROINIT(SAStats);

                /* Read the SA ingress statistics counters, */
                /* request device synchronization before reading out the statistics */
                SecY_Rc = SecY_SA_Statistics_I_Get(SECY_DEVICE_ID,
                                                   SecY_SAHandle,
                                                   &SAStats,
                                                   true);
                if (SecY_Rc != SECY_STATUS_OK)
                {
                    LOG_CRIT("DA_MACSEC: Failed, SecY_SA_Statistics_I_Get()=%d\n",
                             SecY_Rc);
                    goto error_exit;
                }

                /* Assume that any counters are less than 2^32, so we can just display */
                /* the low halves of the 64-bit counters */
                Log_FormattedMessage("DA_MACSEC:Ingress SA Statistics:\n"
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
                                     SAStats.InOctetsDecrypted.Lo,
                                     SAStats.InOctetsValidated.Lo,
                                     SAStats.InPktsDelayed.Lo,
                                     SAStats.InPktsInvalid.Lo,
                                     SAStats.InPktsLate.Lo,
                                     SAStats.InPktsNotUsingSA.Lo,
                                     SAStats.InPktsNotValid.Lo,
                                     SAStats.InPktsOK.Lo,
                                     SAStats.InPktsUnchecked.Lo,
                                     SAStats.InPktsUnusedSA.Lo);

                if ((SAStats.InOctetsDecrypted.Lo != 54) ||
                    (SAStats.InOctetsValidated.Lo != 0) ||
                    (SAStats.InPktsDelayed.Lo != 0) ||
                    (SAStats.InPktsInvalid.Lo != 0) ||
                    (SAStats.InPktsLate.Lo != 0) ||
                    (SAStats.InPktsNotUsingSA.Lo != 0) ||
                    (SAStats.InPktsNotValid.Lo != 0) ||
                    (SAStats.InPktsOK.Lo != 1) ||
                    (SAStats.InPktsUnchecked.Lo != 0) ||
                    (SAStats.InPktsUnusedSA.Lo != 0))
                {
                    LOG_CRIT("DA_MACSEC: Failed, SA statistics check:\n"
                             "\tInOctetsDecrypted=%u, expected 54\n"
                             "\tInOctetsValidated=%u, expected 0\n"
                             "\tInPktsDelayed=%u, expected 0\n"
                             "\tInPktsInvalid=%u, expected 0\n"
                             "\tInPktsLate=%u, expected 0\n"
                             "\tInPktsNotUsingSA=%u, expected 0\n"
                             "\tInPktsNotValid=%u, expected 0\n"
                             "\tInPktsOK=%u, expected 1\n"
                             "\tInPktsUnchecked=%u, expected 0\n"
                             "\tInPktsUnusedSA=%u, expected 0\n",
                             SAStats.InOctetsDecrypted.Lo,
                             SAStats.InOctetsValidated.Lo,
                             SAStats.InPktsDelayed.Lo,
                             SAStats.InPktsInvalid.Lo,
                             SAStats.InPktsLate.Lo,
                             SAStats.InPktsNotUsingSA.Lo,
                             SAStats.InPktsNotValid.Lo,
                             SAStats.InPktsOK.Lo,
                             SAStats.InPktsUnchecked.Lo,
                             SAStats.InPktsUnusedSA.Lo);
                    goto error_exit;
                }
            }

            {
                SecY_SecY_Stat_I_t SecYStats;

                ZEROINIT(SecYStats);

                /* Read the SecY ingress statistics counters. */
                /* Sync with the SecY device to get the exact counters values */
                SecY_Rc = SecY_SecY_Statistics_I_Get(SECY_DEVICE_ID,
                                                     vPort,
                                                     &SecYStats,
                                                     true);
                if (SecY_Rc != SECY_STATUS_OK)
                {
                    LOG_CRIT("DA_MACSEC: Failed, SecY_SecY_Statistics_I_Get()=%d\n",
                             SecY_Rc);
                    goto error_exit;
                }

                /* Assume that any counters are less than 2^32, so we can just display */
                /* the low halves of the 64-bit counters */
                Log_FormattedMessage(
                        "DA_MACSEC: Ingress SecY(%d) Statistics:\n"
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

                if ((SecYStats.InPktsTransformError.Lo != 0) ||
                    (SecYStats.InPktsControl.Lo != 0) ||
                    (SecYStats.InPktsUntagged.Lo != 0) ||
                    (SecYStats.InPktsNoTag.Lo != 0) ||
                    (SecYStats.InPktsBadTag.Lo != 0) ||
                    (SecYStats.InPktsNoSCI.Lo != 0) ||
                    (SecYStats.InPktsUnknownSCI.Lo != 0) ||
                    (SecYStats.InPktsTaggedCtrl.Lo != 0))
                {
                    LOG_CRIT("DA_MACSEC: Failed, SecY statistics check:\n"
                             "\tInPktsTransformError=%u, expected 0\n"
                             "\tInPktsControl=%u, expected 0\n"
                             "\tInPktsUntagged=%u, expected 0\n"
                             "\tInPktsNoTag=%u, expected 0\n"
                             "\tInPktsBadTag=%u, expected 0\n"
                             "\tInPktsNoSCI=%u, expected 0\n"
                             "\tInPktsUnknownSCI=%u, expected 0\n"
                             "\tInPktsTaggedCtrl=%u, expected 0\n",
                             SecYStats.InPktsTransformError.Lo,
                             SecYStats.InPktsControl.Lo,
                             SecYStats.InPktsUntagged.Lo,
                             SecYStats.InPktsNoTag.Lo,
                             SecYStats.InPktsBadTag.Lo,
                             SecYStats.InPktsNoSCI.Lo,
                             SecYStats.InPktsUnknownSCI.Lo,
                             SecYStats.InPktsTaggedCtrl.Lo);
                    goto error_exit;
                }
            }

            {
                SecY_Ifc_Stat_I_t IfcStats;

                ZEROINIT(IfcStats);

                /* Read the IFC/IFC1 ingress statistics counters. */
                /* Sync with the SecY device to get the exact counters values */
                SecY_Rc = SecY_Ifc_Statistics_I_Get(SECY_DEVICE_ID,
                                                    vPort,
                                                    &IfcStats,
                                                    true);
                if (SecY_Rc != SECY_STATUS_OK)
                {
                    LOG_CRIT("DA_MACSEC: Failed, SecY_Ifc_Statistics_I_Get()=%d\n",
                             SecY_Rc);
                    goto error_exit;
                }

                /* Assume that any counters are less than 2^32, so we can just display */
                /* the low halves of the 64-bit counters */
                Log_FormattedMessage(
                    "DA_MACSEC: Ingress IFC/IFC1(%d) Statistics:\n"
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

                if ((IfcStats.InOctetsUncontrolled.Lo != 102) ||
                    (IfcStats.InPktsUnicastUncontrolled.Lo != 1) ||
                    (IfcStats.InPktsMulticastUncontrolled.Lo != 0) ||
                    (IfcStats.InPktsBroadcastUncontrolled.Lo != 0) ||
                    (IfcStats.InOctetsControlled.Lo != 66) ||
                    (IfcStats.InPktsUnicastControlled.Lo != 1) ||
                    (IfcStats.InPktsMulticastControlled.Lo != 0) ||
                    (IfcStats.InPktsBroadcastControlled.Lo != 0))
                {
                    LOG_CRIT("DA_MACSEC: Failed, IFC/IFC1 statistics check:\n"
                             "\tInOctetsUncontrolled=%u, expected 102\n"
                             "\tInPktsUnicastUncontrolled=%u, expected 1\n"
                             "\tInPktsMulticastUncontrolled=%u, expected 0\n"
                             "\tInPktsBroadcastUncontrolled=%u, expected 0\n"
                             "\tInOctetsControlled=%u, expected 66\n"
                             "\tInPktsUnicastControlled=%u, expected 1\n"
                             "\tInPktsMulticastControlled=%u, expected 0\n"
                             "\tInPktsBroadcastControlled=%u, expected 0\n",
                             IfcStats.InOctetsUncontrolled.Lo,
                             IfcStats.InPktsUnicastUncontrolled.Lo,
                             IfcStats.InPktsMulticastUncontrolled.Lo,
                             IfcStats.InPktsBroadcastUncontrolled.Lo,
                             IfcStats.InOctetsControlled.Lo,
                             IfcStats.InPktsUnicastControlled.Lo,
                             IfcStats.InPktsMulticastControlled.Lo,
                             IfcStats.InPktsBroadcastControlled.Lo);
                    goto error_exit;
                }
            }
        }
#endif /* DA_MACSEC_MODE_INGRESS */

#ifdef DA_MACSEC_MODE_EGRESS
        if (!fIngress)
        {
            {
                SecY_SA_Stat_E_t SAStats;

                ZEROINIT(SAStats);

                /* Read out egress SA statistics, */
                /* request device synchronization before reading out statistics */
                SecY_Rc = SecY_SA_Statistics_E_Get(SECY_DEVICE_ID,
                                                   SecY_SAHandle,
                                                   &SAStats,
                                                   true);
                if (SecY_Rc != SECY_STATUS_OK)
                {
                    LOG_CRIT("DA_MACSEC: Failed, SecY_SA_Statistics_E_Get()=%d\n",
                             SecY_Rc);
                    goto error_exit;
                }

                /* Assume that any counters are less than 2^32, so we can just display */
                /* the low halves of the 64-bit counters */
                Log_FormattedMessage("DA_MACSEC: Egress SA Statistics:\n"
                                     "\tOutOctetsEncryptedProtected: %u\n"
                                     "\tOutPktsEncryptedProtected:   %u\n"
                                     "\tOutPktsTooLong:              %u\n"
                                     "\tOutPktsSANotInUse:           %u\n",
                                     SAStats.OutOctetsEncryptedProtected.Lo,
                                     SAStats.OutPktsEncryptedProtected.Lo,
                                     SAStats.OutPktsTooLong.Lo,
                                     SAStats.OutPktsSANotInUse.Lo);

                if ((SAStats.OutOctetsEncryptedProtected.Lo != 54) ||
                    (SAStats.OutPktsEncryptedProtected.Lo != 1) ||
                    (SAStats.OutPktsTooLong.Lo != 0) ||
                    (SAStats.OutPktsSANotInUse.Lo != 0))
                {
                    LOG_CRIT("DA_MACSEC: Failed, SA statistics check:\n"
                             "\tOutOctetsEncryptedProtected=%u, expected 54,\n"
                             "\tOutPktsEncryptedProtected=%u, expected 1\n"
                             "\tOutPktsTooLong=%u, expected 0\n"
                             "\tOutPktsSANotInUse=%u, expected 0\n",
                             SAStats.OutOctetsEncryptedProtected.Lo,
                             SAStats.OutPktsEncryptedProtected.Lo,
                             SAStats.OutPktsTooLong.Lo,
                             SAStats.OutPktsSANotInUse.Lo);
                    goto error_exit;
                }
            }

            {
                SecY_SecY_Stat_E_t SecYStats;

                ZEROINIT(SecYStats);

                /* Read the SecY ingress statistics counters. */
                /* Sync with the SecY device to get the exact counters values */
                SecY_Rc = SecY_SecY_Statistics_E_Get(SECY_DEVICE_ID,
                                                     vPort,
                                                     &SecYStats,
                                                     true);
                if (SecY_Rc != SECY_STATUS_OK)
                {
                    LOG_CRIT("DA_MACSEC: Failed, SecY_SecY_Statistics_E_Get()=%d\n",
                             SecY_Rc);
                    goto error_exit;
                }

                /* Assume that any counters are less than 2^32, so we can just display */
                /* the low halves of the 64-bit counters */
                Log_FormattedMessage(
                    "DA_MACSEC: Egress SecY(%d) Statistics:\n"
                    "\tTransform E r r o r Packets Counter: %u\n"
                    "\tEgress Controlled Packets Counter:   %u\n"
                    "\tEgress Untagged Packets Counter:     %u\n",
                    vPort,
                    SecYStats.OutPktsTransformError.Lo,
                    SecYStats.OutPktsControl.Lo,
                    SecYStats.OutPktsUntagged.Lo);

                if ((SecYStats.OutPktsTransformError.Lo != 0) ||
                    (SecYStats.OutPktsControl.Lo != 0) ||
                    (SecYStats.OutPktsUntagged.Lo != 0))
                {
                    LOG_CRIT("DA_MACSEC: Failed, SecY statistics check:\n"
                             "\tOutPktsTransformError=%u, expected 0\n"
                             "\tOutPktsControl=%u, expected 0\n"
                             "\tOutPktsUntagged=%u, expected 0\n",
                             SecYStats.OutPktsTransformError.Lo,
                             SecYStats.OutPktsControl.Lo,
                             SecYStats.OutPktsUntagged.Lo);
                    goto error_exit;
                }
            }

            {
                SecY_Ifc_Stat_E_t IfcStats;

                ZEROINIT(IfcStats);

                /* Read the IFC/IFC1 ingress statistics counters. */
                /* Sync with the SecY device to get the exact counters values */
                SecY_Rc = SecY_Ifc_Statistics_E_Get(SECY_DEVICE_ID,
                                                    vPort,
                                                    &IfcStats,
                                                    true);
                if (SecY_Rc != SECY_STATUS_OK)
                {
                    LOG_CRIT("DA_MACSEC: Failed, SecY_Ifc_Statistics_E_Get()=%d\n",
                             SecY_Rc);
                    goto error_exit;
                }

                /* Assume that any counters are less than 2^32, so we can just display */
                /* the low halves of the 64-bit counters */
                Log_FormattedMessage(
                    "DA_MACSEC: Egress IFC/IFC1(%d) Statistics:\n"
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

                if ((IfcStats.OutOctetsCommon.Lo != 102) ||
                    (IfcStats.OutOctetsUncontrolled.Lo != 0) ||
                    (IfcStats.OutPktsUnicastUncontrolled.Lo != 0) ||
                    (IfcStats.OutPktsMulticastUncontrolled.Lo != 0) ||
                    (IfcStats.OutPktsBroadcastUncontrolled.Lo != 0) ||
                    (IfcStats.OutOctetsControlled.Lo != 66) ||
                    (IfcStats.OutPktsUnicastControlled.Lo != 1) ||
                    (IfcStats.OutPktsMulticastControlled.Lo != 0) ||
                    (IfcStats.OutPktsBroadcastControlled.Lo != 0))
                {
                    LOG_CRIT("DA_MACSEC: Failed, IFC/IFC1 statistics check:\n"
                             "\tOutOctetsCommon=%u, expected 102\n"
                             "\tOutOctetsUncontrolled=%u, expected 0\n"
                             "\tOutPktsUnicastUncontrolled=%u, expected 0\n"
                             "\tOutPktsMulticastUncontrolled=%u, expected 0\n"
                             "\tOutPktsBroadcastUncontrolled=%u, expected 0\n"
                             "\tOutOctetsControlled=%u, expected 66\n"
                             "\tOutPktsUnicastControlled=%u, expected 1\n"
                             "\tOutPktsMulticastControlled=%u, expected 0\n"
                             "\tOutPktsBroadcastControlled=%u, expected 0\n",
                             IfcStats.OutOctetsCommon.Lo,
                             IfcStats.OutOctetsUncontrolled.Lo,
                             IfcStats.OutPktsUnicastUncontrolled.Lo,
                             IfcStats.OutPktsMulticastUncontrolled.Lo,
                             IfcStats.OutPktsBroadcastUncontrolled.Lo,
                             IfcStats.OutOctetsControlled.Lo,
                             IfcStats.OutPktsUnicastControlled.Lo,
                             IfcStats.OutPktsMulticastControlled.Lo,
                             IfcStats.OutPktsBroadcastControlled.Lo);
                    goto error_exit;
                }
            }
        }
#endif /* DA_MACSEC_MODE_EGRESS */
    }

    if (fVerbose)
    {
        Log_FormattedMessage("DA_MACSEC: Finished processing packets\n");
    }

    /* If we made it to here, consider this run a success. Any jump */
    /* to one of the error labels below will skip "success = true" */
    fSuccess = true;

error_exit:

    CfyE_Rc = CfyE_Rule_Disable(CFYE_DEVICE_ID, CfyE_RuleHandle, true);
    if (CfyE_Rc != CFYE_STATUS_OK)
    {
        LOG_CRIT("DA_MACSEC: Failed, CfyE_Rule_Disable()=%d\n", CfyE_Rc);
        fSuccess = false;
    }

    CfyE_Rc = CfyE_Rule_Remove(CFYE_DEVICE_ID, CfyE_RuleHandle);
    if (CfyE_Rc != CFYE_STATUS_OK)
    {
        LOG_CRIT("DA_MACSEC: Failed, CfyE_Rule_Remove()=%d\n", CfyE_Rc);
        fSuccess = false;
    }

    /* Remove vPort */
    CfyE_Rc = CfyE_vPort_Remove(CFYE_DEVICE_ID, CfyE_vPortHandle);
    if (CfyE_Rc != CFYE_STATUS_OK)
    {
        LOG_CRIT("DA_MACSEC: Failed, CfyE_vPort_Remove()=%d\n", CfyE_Rc);
        fSuccess = false;
    }

    /* Remove SA */
    SecY_Rc = SecY_SA_Remove(SECY_DEVICE_ID, SecY_SAHandle);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        LOG_CRIT("DA_MACSEC: Failed, SecY_SA_Remove()=%d\n", SecY_Rc);
        fSuccess = false;
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
    CfyE_Device_Uninit(SECY_DEVICE_ID);

    return fSuccess;
}

#endif /* DA_MACSEC_USE_CFYE */

/* end of file da_secy_cfye_vlan_qinq_macsec.c */
