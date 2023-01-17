/* da_secy_cfye_macsec_sm4.c
 *
 * Demo Application, MACsec transform test using SecY and CfyE API, SM4 cipher.
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
    /* 128-bit SM4 key */
    0xa9, 0xc4, 0xb0, 0xab, 0xc5, 0xe4, 0x4a, 0x80,
    0x36, 0x3c, 0x8a, 0xc8, 0x52, 0x1c, 0x43, 0xb2,
    /* HKEY must be provided too as SM4 block cipher implementation is not
       included in the DDK. */
    0xf8, 0xc2, 0x37, 0x56, 0x34, 0x89, 0x9f, 0xeb,
    0x80, 0x46, 0xbc, 0xc9, 0xeb, 0xcb, 0x54, 0x72,
};

/* MACsec SCI */
static uint8_t SCI1[] = {
    0xb6, 0x9d, 0xfe, 0xab, 0xbb, 0x61, 0x16, 0x4b,
};

static da_sa_params_t Transform_Params_Basic_Transform_Ingress =
{
    SAB_DIRECTION_INGRESS,
    SAB_OP_MACSEC,
    SAB_MACSEC_FLAG_SM4,
    0,
    K1,
    16,
    SCI1,
    NULL,
    NULL,
    0, /* Sequence number. */
    0,
    0,
#if defined(DA_IPSEC_ENABLE)
    0,
#endif
};

/* Basic SA transform source packet */
static const uint8_t SrcPacket_Basic_Transform_Ingress[] =
{
    0x36, 0x6a, 0xb6, 0x7d, 0xb3, 0x39, 0xb0, 0x55,
    0x62, 0x4e, 0xfa, 0xa5, 0x88, 0xe5, 0x2c, 0x00,
    0x00, 0x00, 0x00, 0x01, 0xb6, 0x9d, 0xfe, 0xab,
    0xbb, 0x61, 0x16, 0x4b, 0x66, 0x79, 0xdd, 0x25,
    0xab, 0x13, 0x22, 0x51, 0x9d, 0xe9, 0xc5, 0x40,
    0xab, 0xf2, 0xc3, 0x4c, 0x3e, 0x7d, 0x8b, 0x6c,
    0x73, 0x26, 0x72, 0xf5, 0x72, 0xc6, 0xb8, 0x00,
    0xe2, 0xf7, 0x66, 0xbc, 0x65, 0xce, 0x08, 0x76,
    0xfa, 0x11, 0x8b, 0xdb, 0x77, 0x80, 0x87, 0xb2,
    0x6a, 0x80, 0x85, 0xe7, 0xb9, 0x45, 0x89, 0x36,
    0x03, 0x7d, 0x31, 0x86, 0x62, 0x8e, 0xc9, 0xad,
    0x54, 0xde, 0xea, 0x48, 0x72, 0x1d, 0xb4, 0xdb,
    0x89, 0xf8, 0xd8, 0x11, 0x4d, 0x10, 0xaa, 0xcc,
    0x4d, 0x67,
};

static const uint8_t * MAC_DA_Basic_Transform_Ingress_p = &SrcPacket_Basic_Transform_Ingress[0];
static const uint8_t * TCI_AN_Basic_Transform_Ingress_p = &SrcPacket_Basic_Transform_Ingress[14];
static const uint8_t * SCI_Basic_Transform_Ingress_p = &SrcPacket_Basic_Transform_Ingress[20];

/* Basic SA transform destination packet */
static const uint8_t DstPacket_Basic_Transform_Ingress[] =
{
    0x36, 0x6a, 0xb6, 0x7d, 0xb3, 0x39, 0xb0, 0x55,
    0x62, 0x4e, 0xfa, 0xa5, 0x00, 0x3c, 0xe0, 0x57,
    0xca, 0xb7, 0xc8, 0x3e, 0x73, 0x7a, 0x5f, 0x25,
    0xd8, 0x37, 0x30, 0x7e, 0xe3, 0xd1, 0xca, 0xa6,
    0x9a, 0xc8, 0xe0, 0x13, 0xb9, 0x08, 0xe4, 0xd2,
    0x93, 0x5b, 0x98, 0x0c, 0x4d, 0xa3, 0x2e, 0x09,
    0x05, 0xae, 0xbd, 0xca, 0x4d, 0xf0, 0x37, 0x83,
    0x07, 0x01, 0x8c, 0x58, 0x6d, 0x65, 0xae, 0xcb,
    0xce, 0x52, 0x4f, 0x45, 0xf2, 0x26, 0xe1, 0x99,
    0xd6, 0x40,
};
#endif /* DA_MACSEC_MODE_INGRESS */

#ifdef DA_MACSEC_MODE_EGRESS
/* MACsec key */
static uint8_t K2[] = {
    /* 128-bit SM4 key */
    0xa9, 0xc4, 0xb0, 0xab, 0xc5, 0xe4, 0x4a, 0x80,
    0x36, 0x3c, 0x8a, 0xc8, 0x52, 0x1c, 0x43, 0xb2,
    /* HKEY must be provided too as SM4 block cipher implementation is
       not included in the DDK. */
    0xf8, 0xc2, 0x37, 0x56, 0x34, 0x89, 0x9f, 0xeb,
    0x80, 0x46, 0xbc, 0xc9, 0xeb, 0xcb, 0x54, 0x72,
};

/* MACsec SCI */
static uint8_t SCI2[] = {
    0xb6, 0x9d, 0xfe, 0xab, 0xbb, 0x61, 0x16, 0x4b,
};

static da_sa_params_t Transform_Params_Basic_Transform_Egress =
{
    SAB_DIRECTION_EGRESS,
    SAB_OP_MACSEC,
    SAB_MACSEC_FLAG_SM4,
    0,
    K2,
    16,
    SCI2,
    NULL,
    NULL,
    0, /* Sequence number. */
    0,
    0,
#if defined(DA_IPSEC_ENABLE)
    0,
#endif
};

/* Basic SA transform source packet */
static const uint8_t SrcPacket_Basic_Transform_Egress[] =
{
    0x36, 0x6a, 0xb6, 0x7d, 0xb3, 0x39, 0xb0, 0x55,
    0x62, 0x4e, 0xfa, 0xa5, 0x00, 0x3c, 0xe0, 0x57,
    0xca, 0xb7, 0xc8, 0x3e, 0x73, 0x7a, 0x5f, 0x25,
    0xd8, 0x37, 0x30, 0x7e, 0xe3, 0xd1, 0xca, 0xa6,
    0x9a, 0xc8, 0xe0, 0x13, 0xb9, 0x08, 0xe4, 0xd2,
    0x93, 0x5b, 0x98, 0x0c, 0x4d, 0xa3, 0x2e, 0x09,
    0x05, 0xae, 0xbd, 0xca, 0x4d, 0xf0, 0x37, 0x83,
    0x07, 0x01, 0x8c, 0x58, 0x6d, 0x65, 0xae, 0xcb,
    0xce, 0x52, 0x4f, 0x45, 0xf2, 0x26, 0xe1, 0x99,
    0xd6, 0x40,
};

static const uint8_t * MAC_DA_Basic_Transform_Egress_p = &SrcPacket_Basic_Transform_Egress[0];


/* Basic SA transform destination packet */
static const uint8_t DstPacket_Basic_Transform_Egress[] =
{
    0x36, 0x6a, 0xb6, 0x7d, 0xb3, 0x39, 0xb0, 0x55,
    0x62, 0x4e, 0xfa, 0xa5, 0x88, 0xe5, 0x2c, 0x00,
    0x00, 0x00, 0x00, 0x01, 0xb6, 0x9d, 0xfe, 0xab,
    0xbb, 0x61, 0x16, 0x4b, 0x66, 0x79, 0xdd, 0x25,
    0xab, 0x13, 0x22, 0x51, 0x9d, 0xe9, 0xc5, 0x40,
    0xab, 0xf2, 0xc3, 0x4c, 0x3e, 0x7d, 0x8b, 0x6c,
    0x73, 0x26, 0x72, 0xf5, 0x72, 0xc6, 0xb8, 0x00,
    0xe2, 0xf7, 0x66, 0xbc, 0x65, 0xce, 0x08, 0x76,
    0xfa, 0x11, 0x8b, 0xdb, 0x77, 0x80, 0x87, 0xb2,
    0x6a, 0x80, 0x85, 0xe7, 0xb9, 0x45, 0x89, 0x36,
    0x03, 0x7d, 0x31, 0x86, 0x62, 0x8e, 0xc9, 0xad,
    0x54, 0xde, 0xea, 0x48, 0x72, 0x1d, 0xb4, 0xdb,
    0x89, 0xf8, 0xd8, 0x11, 0x4d, 0x10, 0xaa, 0xcc,
    0x4d, 0x67,
};
#endif /* DA_MACSEC_MODE_EGRESS */


/* Bypass packet, has to take default policy on TCAM miss. */
/* It has the sixth byte of the DA set to 0x61 instead of 0x63, */
/* so it will not match the TCAM rule for MACsec */
static const uint8_t BypassPacket[] =
{
    0xd6, 0x09, 0xb1, 0xf0,
    0x56, 0x61, 0x7a, 0x0d,
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

/*----------------------------------------------------------------------------
 * da_secy_cfye_macsec_transform_sm4
 */
bool
da_secy_cfye_macsec_transform_sm4(
        bool fVerbose,
        bool fIngress)
{
    unsigned int vPort = 0;
    unsigned int vPortDefault = 0;
    unsigned int Channel = 0;

    SecY_Status_t SecY_Rc;
    SecY_SAHandle_t SecY_SAHandle;
    SecY_SAHandle_t SecY_SAHandleDrop;
    CfyE_Status_t CfyE_Rc;
    CfyE_vPortHandle_t CfyE_vPortHandle = CfyE_vPortHandle_NULL;
    CfyE_vPortHandle_t CfyE_vPortHandleDefault = CfyE_vPortHandle_NULL;
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
        Log_FormattedMessage("DA_MACSEC: Perform Transform\n");
    }

    SecY_SAHandle = SecY_SAHandle_NULL;
    SecY_SAHandleDrop = SecY_SAHandle_NULL;

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

    if (fVerbose)
    {
        Log_FormattedMessage("DA_MACSEC: Preparing packet(s)\n");
    }

    /* Install default vPort for use with TCAM miss. */
    {
        CfyE_vPort_t vPortParams;

        ZEROINIT(vPortParams);

        CfyE_Rc = CfyE_vPort_Add(CFYE_DEVICE_ID,
                                 &CfyE_vPortHandleDefault,
                                 &vPortParams,
                                 SECY_MODE_MACSEC);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: Failed, CfyE_vPort_Add()=%d\n", CfyE_Rc);
            goto error_exit;
        }

        /* Now get vPort index to use when installing SA: */
        CfyE_vPortIndex_Get(CfyE_vPortHandleDefault, &vPortDefault);

        if (fVerbose)
        {
            Log_FormattedMessage("DA_MACSEC: Non-match vPort added\n");
        }
    }

    /* Install drop SA with Drop-action is bypass-with-crc on default vPort */
    {
        SecY_SA_t SA_Params;

        ZEROINIT(SA_Params);
        SA_Params.ActionType = SECY_SA_ACTION_DROP;
        SA_Params.DropType = SECY_SA_DROP_CRC_ERROR;
        if (fIngress)
        {
            SA_Params.DestPort = SECY_PORT_UNCONTROLLED;
        }
        else
        {
            SA_Params.DestPort = SECY_PORT_COMMON;
        }
        SA_Params.SA_WordCount = 0;
        SA_Params.TransformRecord_p = NULL;

        SecY_Rc = SecY_SA_Add(SECY_DEVICE_ID, vPortDefault, &SecY_SAHandleDrop, &SA_Params);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: Failed, SecY_SA_Add()=%d\n", SecY_Rc);
            goto error_exit;
        }

        if (fVerbose)
        {
            Log_FormattedMessage("DA_MACSEC: Drop flow for non-match vPort added\n");
        }

    }

    /* Configure default vPort on CfyE device */
    {
        CfyE_Device_Exceptions_t DeviceExceptions;
        CfyE_Device_Control_t DeviceControl;
        CfyE_Device_Limits_t DeviceLimits;
        CfyE_Device_t Device;
        unsigned int i;
        ZEROINIT(Device);
        ZEROINIT(DeviceControl);
        DeviceExceptions.DropAction = CFYE_DO_NOT_DROP;
        DeviceExceptions.ECCDropAction = CFYE_DROP_CRC_ERROR;
        DeviceExceptions.fForceDrop = false;
        DeviceExceptions.fDefaultVPortValid = true;
        DeviceExceptions.fShouldSecure = false;
        DeviceExceptions.DefaultVPort = vPortDefault;
        DeviceControl.fLowLatencyBypass = false;
        DeviceControl.Exceptions_p = &DeviceExceptions;
        Device.Control_p = &DeviceControl;

        CfyE_Rc = CfyE_Device_Limits_Get(CFYE_DEVICE_ID, &DeviceLimits);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: Failed, CfyE_Device_Limits_Get()=%d\n", CfyE_Rc);
            goto error_exit;
        }

        /* Call the cfyE_Device_Update for all channels that you want to use. */
        for (i = 0; i < DeviceLimits.channel_count; i++)
        {
            CfyE_Rc = CfyE_Device_Update(CFYE_DEVICE_ID, i, &Device);
            if (CfyE_Rc != CFYE_STATUS_OK)
            {
                LOG_CRIT("DA_MACSEC: Failed, CfyE_Device_Update()=%d\n", CfyE_Rc);
                goto error_exit;
            }
        }
        if (fVerbose)
        {
            Log_FormattedMessage("DA_MACSEC: Non-match vPort configured for all channels\n");
        }

    }

    /* Install vPort for use with SA */
    {
        CfyE_vPort_t vPortParams;

        ZEROINIT(vPortParams);
        vPortParams.SecTagOffset = 12;
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

            SA_Params.Params.Ingress.ValidateFramesTagged =
                SECY_FRAME_VALIDATE_STRICT;
            SA_Params.Params.Ingress.fReplayProtect = true;
            SA_Params.Params.Ingress.SCI_p =
                da_macsec_discard_const(SCI_Basic_Transform_Ingress_p);
            SA_Params.Params.Ingress.AN = *TCI_AN_Basic_Transform_Ingress_p & 3;
            SA_Params.Params.Ingress.fAllowTagged = true;
            SA_Params.Params.Ingress.PreSecTagAuthLength = 12;

            SA_Params.TransformRecord_p =
                da_macsec_build_sa(&Transform_Params_Basic_Transform_Ingress,
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
                da_macsec_build_sa(&Transform_Params_Basic_Transform_Egress,
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

    /* Install Rule */
    {
        CfyE_Rule_t RuleParams;

        ZEROINIT(RuleParams);
        RuleParams.Policy.vPortHandle = CfyE_vPortHandle;

        RuleParams.Mask.PacketType = CFYE_RULE_PKT_TYPE_MASK; /* Exact match on all these fields. */
        RuleParams.Mask.ChannelID = CFYE_RULE_CHANNEL_ID_MASK;
        RuleParams.Mask.NumTags = CFYE_RULE_NUMTAGS_MASK;

        RuleParams.Key.PacketType = CFYE_RULE_PKT_TYPE_OTHER;
        RuleParams.Key.ChannelID = Channel;
        RuleParams.Key.NumTags = 0x01;

        RuleParams.DataMask[0]=0xffffffff; /* Match on Destination address. */
        RuleParams.DataMask[1]=0x0000ffff;

        {
            const uint8_t *p = NULL;
            if (fIngress)
            {
#ifdef DA_MACSEC_MODE_INGRESS
                p = MAC_DA_Basic_Transform_Ingress_p;
#endif
            }
            else
            {
#ifdef DA_MACSEC_MODE_EGRESS
                p = MAC_DA_Basic_Transform_Egress_p;
#endif
            }
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
            PktByteCount = sizeof(SrcPacket_Basic_Transform_Ingress);
            memcpy(InputPktHostAddress,
                   SrcPacket_Basic_Transform_Ingress,
                   PktByteCount);

            if (fVerbose)
            {
                Log_FormattedMessage("DA_MACSEC: "
                                     "Process input packet of size %d\n",
                                     PktByteCount);
                Log_HexDump("Input packet",
                            0,
                            SrcPacket_Basic_Transform_Ingress,
                            PktByteCount);
            }

            /* Expected packet */
            ExpectedPktByteCount = sizeof(DstPacket_Basic_Transform_Ingress);
            memcpy(ExpectedPktHostAddress,
                   DstPacket_Basic_Transform_Ingress,
                   ExpectedPktByteCount);
        }
#endif /* DA_MACSEC_MODE_INGRESS */

#ifdef DA_MACSEC_MODE_EGRESS
        if (!fIngress)
        {
            /* Input packet */
            PktByteCount = sizeof(SrcPacket_Basic_Transform_Egress);
            memcpy(InputPktHostAddress,
                   SrcPacket_Basic_Transform_Egress,
                   PktByteCount);

            if (fVerbose)
            {
                Log_FormattedMessage("DA_MACSEC: "
                                     "Process input packet of size %d\n",
                                     PktByteCount);
                Log_HexDump("Input packet",
                            0,
                            SrcPacket_Basic_Transform_Egress,
                            PktByteCount);
            }

            /* Expected packet */
            ExpectedPktByteCount = sizeof(DstPacket_Basic_Transform_Egress);
            memcpy(ExpectedPktHostAddress,
                   DstPacket_Basic_Transform_Egress,
                   ExpectedPktByteCount);
        }
#endif /* DA_MACSEC_MODE_EGRESS */

        /* Fill in the status data structure */
        ZEROINIT(PktStatusIn);

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

        /* Process a second packet, that will miss TCAM */
        /* Input packet*/
        PktByteCount = sizeof(BypassPacket);
        memcpy(InputPktHostAddress,
               BypassPacket,
               PktByteCount);

        if (fVerbose)
        {
            Log_FormattedMessage("DA_MACSEC: "
                                 "Process input packet of size %d\n",
                                 PktByteCount);
            Log_HexDump("Input packet",
                        0,
                        InputPktHostAddress,
                        PktByteCount);
        }

        /* Expected packet */
        ExpectedPktByteCount = sizeof(BypassPacket);
        memcpy(ExpectedPktHostAddress,
               BypassPacket,
               ExpectedPktByteCount);

        /* Fill in the status data structure */
        ZEROINIT(PktStatusIn);

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
            Log_FormattedMessage("DA_MACSEC: Second packet submitted\n");
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
            Log_HexDump("Second result packet",
                        0,
                        ProcessedPktHostAddress,
                        ByteCount);
        }
        /* This packet must have a CRC error as specified by default vPort
           policy */
        if ( (PktStatusOut.PacketStatusMask & PKTIO_PACKET_CRC_ERROR) == 0)
        {
            LOG_CRIT("DA_MACSEC: Error: No CRC error on packet missing TCAM\n"
                     "          expected to be added by non-match rule\n");
            goto error_exit;
        }
        else
        {
            Log_FormattedMessage("DA_MACSEC: Packet has expected CRC e r r o r\n");
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

                if ((SAStats.InOctetsDecrypted.Lo != 62) ||
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
                             "\tInOctetsDecrypted=%u, expected 62\n"
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

                if ((IfcStats.InOctetsUncontrolled.Lo != 106) ||
                    (IfcStats.InPktsUnicastUncontrolled.Lo != 1) ||
                    (IfcStats.InPktsMulticastUncontrolled.Lo != 0) ||
                    (IfcStats.InPktsBroadcastUncontrolled.Lo != 0) ||
                    (IfcStats.InOctetsControlled.Lo != 74) ||
                    (IfcStats.InPktsUnicastControlled.Lo != 1) ||
                    (IfcStats.InPktsMulticastControlled.Lo != 0) ||
                    (IfcStats.InPktsBroadcastControlled.Lo != 0))
                {
                    LOG_CRIT("DA_MACSEC: Failed, IFC/IFC1 statistics check:\n"
                             "\tInOctetsUncontrolled=%u, expected 106\n"
                             "\tInPktsUnicastUncontrolled=%u, expected 1\n"
                             "\tInPktsMulticastUncontrolled=%u, expected 0\n"
                             "\tInPktsBroadcastUncontrolled=%u, expected 0\n"
                             "\tInOctetsControlled=%u, expected 74\n"
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

                if ((SAStats.OutOctetsEncryptedProtected.Lo != 62) ||
                    (SAStats.OutPktsEncryptedProtected.Lo != 1) ||
                    (SAStats.OutPktsTooLong.Lo != 0) ||
                    (SAStats.OutPktsSANotInUse.Lo != 0))
                {
                    LOG_CRIT("DA_MACSEC: Failed, SA statistics check:\n"
                             "\tOutOctetsEncryptedProtected=%u, expected 62,\n"
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

                if ((IfcStats.OutOctetsCommon.Lo != 106) ||
                    (IfcStats.OutOctetsUncontrolled.Lo != 0) ||
                    (IfcStats.OutPktsUnicastUncontrolled.Lo != 0) ||
                    (IfcStats.OutPktsMulticastUncontrolled.Lo != 0) ||
                    (IfcStats.OutPktsBroadcastUncontrolled.Lo != 0) ||
                    (IfcStats.OutOctetsControlled.Lo != 74) ||
                    (IfcStats.OutPktsUnicastControlled.Lo != 1) ||
                    (IfcStats.OutPktsMulticastControlled.Lo != 0) ||
                    (IfcStats.OutPktsBroadcastControlled.Lo != 0))
                {
                    LOG_CRIT("DA_MACSEC: Failed, IFC/IFC1 statistics check:\n"
                             "\tOutOctetsCommon=%u, expected 106\n"
                             "\tOutOctetsUncontrolled=%u, expected 0\n"
                             "\tOutPktsUnicastUncontrolled=%u, expected 0\n"
                             "\tOutPktsMulticastUncontrolled=%u, expected 0\n"
                             "\tOutPktsBroadcastUncontrolled=%u, expected 0\n"
                             "\tOutOctetsControlled=%u, expected 74\n"
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

    /* Remove default vPort */
    CfyE_Rc = CfyE_vPort_Remove(CFYE_DEVICE_ID, CfyE_vPortHandleDefault);
    if (CfyE_Rc != CFYE_STATUS_OK)
    {
        LOG_CRIT("DA_MACSEC: Failed, CfyE_vPort_Remove()=%d\n", CfyE_Rc);
        fSuccess = false;
    }

    /* Remove default  SA */
    SecY_Rc = SecY_SA_Remove(SECY_DEVICE_ID, SecY_SAHandleDrop);
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

/* end of file da_secy_cfye_macsec_sm4.c */
