/* da_secy_cfye_vxlan_macsec.c
 *
 * Demo Application, MACsec transform test using SecY and CfyE API for
 * VxLAN.
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

#ifdef DA_MACSEC_VXLAN_ENABLE

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
    0x54, 0xa6, 0x61, 0xa3, 0x77, 0x91, 0xde, 0x1f,
    0xc2, 0x55, 0x1e, 0x01, 0xd4, 0x7a, 0xa1, 0xbf,
};

/* MACsec SCI */
static uint8_t SCI1[] = {
    0x75, 0x89, 0xab, 0x04, 0xf6, 0x2f, 0x00, 0x00,
};

static da_sa_params_t Transform_Params_VxLAN_Ingress_MACsec =
{
    SAB_DIRECTION_INGRESS,
    SAB_OP_MACSEC,
    0,
    0,
    K1,
    sizeof(K1),
    SCI1,
    NULL,
    NULL,
    0, /* Seq0 */
    0,
    0,
#if defined(DA_IPSEC_ENABLE)
    0,
#endif
};


/* VxLAN (MACsec) source packet */
static const uint8_t SrcPacket_VxLAN_MACsec_Ingress[] =
{
    0x95, 0x6f, 0xe7, 0x22, 0x6a, 0x80, 0x98, 0xc5,
    0x0c, 0xf1, 0x38, 0x07, 0x08, 0x00, 0x45, 0x00,
    0x01, 0x07, 0x11, 0x12, 0x00, 0x00, 0xe1, 0x11,
    0x75, 0x7a, 0x61, 0x4b, 0x63, 0x97, 0x72, 0x06,
    0x1b, 0x71, 0x39, 0xad, 0x12, 0xb5, 0x00, 0xf3,
    0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
    0x06, 0x07, 0xee, 0x30, 0x7a, 0x1b, 0x2c, 0x1a,
    0x75, 0x89, 0xab, 0x04, 0xf6, 0x2f, 0x88, 0xe5,
    0x5c, 0x00, 0x00, 0x00, 0x00, 0x01, 0xed, 0x8c,
    0x70, 0x45, 0x39, 0x53, 0xb0, 0xda, 0xc1, 0xda,
    0xb6, 0x57, 0xf3, 0x97, 0xd1, 0xcb, 0x08, 0x0c,
    0x5d, 0x22, 0xc7, 0x45, 0xe8, 0x10, 0xe2, 0x80,
    0x7f, 0xa3, 0x73, 0x54, 0x80, 0xea, 0xb5, 0x8a,
    0x59, 0x19, 0xb3, 0xc1, 0x40, 0xce, 0xac, 0x75,
    0x38, 0xef, 0x42, 0x93, 0x90, 0x2d, 0xc1, 0x60,
    0x5f, 0xec, 0x10, 0x5a, 0x0a, 0x3c, 0x25, 0x59,
    0x44, 0x4d, 0x1c, 0xb1, 0x5f, 0x03, 0x63, 0x66,
    0xe8, 0xd9, 0x34, 0x17, 0x1b, 0xf2, 0xef, 0x33,
    0xe5, 0x4a, 0x39, 0x44, 0xd6, 0xcf, 0x05, 0xaa,
    0xbc, 0x80, 0x1b, 0x09, 0xb1, 0x86, 0x70, 0x54,
    0xa6, 0x4c, 0x93, 0xb6, 0x4b, 0xf3, 0x86, 0x5b,
    0xe9, 0x9a, 0x44, 0xdf, 0x51, 0x58, 0x9a, 0xad,
    0x94, 0xd1, 0xc3, 0x24, 0x78, 0xd7, 0x20, 0x52,
    0xf7, 0x14, 0xcf, 0xb3, 0xd0, 0xe1, 0xf3, 0xca,
    0xa6, 0x12, 0x2e, 0x1d, 0x0e, 0x86, 0xb5, 0x04,
    0x8b, 0x25, 0x59, 0x9f, 0xfa, 0x6a, 0xad, 0x00,
    0x7f, 0x1b, 0x1f, 0xbb, 0x43, 0x52, 0x27, 0x1d,
    0x7c, 0x6d, 0xaa, 0xb8, 0x13, 0x5c, 0xaa, 0x85,
    0x8e, 0x73, 0x4d, 0x0b, 0x99, 0x02, 0x75, 0x2f,
    0x42, 0x4b, 0xc7, 0xd1, 0x1c, 0x4c, 0xc7, 0xcb,
    0x92, 0x6e, 0x0c, 0xe6, 0x4b, 0x17, 0x2e, 0xe2,
    0x20, 0xa5, 0x0d, 0x61, 0x4a, 0x24, 0x32, 0xeb,
    0xf5, 0xd1, 0xe8, 0x0e, 0xb0, 0xd6, 0x92, 0x36,
    0xb4, 0xbe, 0x66, 0x0b, 0x4e, 0x38, 0x43, 0xa4,
    0x41, 0x27, 0xe5, 0x82, 0x2e,
};

static const uint8_t * IP_DA_VxLAN_MACsec_Ingress_p =
    &SrcPacket_VxLAN_MACsec_Ingress[50];


/* VxLAN destination packet */
static const uint8_t DstPacket_VxLAN_MACsec_Ingress[] =
{
    0x95, 0x6f, 0xe7, 0x22, 0x6a, 0x80, 0x98, 0xc5,
    0x0c, 0xf1, 0x38, 0x07, 0x08, 0x00, 0x45, 0x00,
    0x00, 0xef, 0x11, 0x12, 0x00, 0x00, 0xe1, 0x11,
    0x75, 0x92, 0x61, 0x4b, 0x63, 0x97, 0x72, 0x06,
    0x1b, 0x71, 0x39, 0xad, 0x12, 0xb5, 0x00, 0xdb,
    0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
    0x06, 0x07, 0xee, 0x30, 0x7a, 0x1b, 0x2c, 0x1a,
    0x75, 0x89, 0xab, 0x04, 0xf6, 0x2f, 0x00, 0xbd,
    0xeb, 0xde, 0x89, 0x8a, 0x17, 0x4d, 0xa9, 0x97,
    0x30, 0xe9, 0x9d, 0x35, 0x87, 0xba, 0x35, 0xe6,
    0x34, 0x3b, 0xfa, 0x92, 0x36, 0xbb, 0x35, 0x8c,
    0x10, 0x23, 0x59, 0xe9, 0xd3, 0x20, 0x5e, 0x67,
    0x8e, 0xce, 0xa6, 0xbb, 0xc1, 0xbf, 0x66, 0x35,
    0x03, 0xdc, 0x30, 0x6c, 0x19, 0xa0, 0x6c, 0x52,
    0x57, 0x08, 0x75, 0x35, 0x26, 0x74, 0x19, 0x3c,
    0x20, 0xdc, 0x19, 0x24, 0x01, 0xe7, 0xce, 0x86,
    0x87, 0xef, 0xa8, 0x48, 0x95, 0x84, 0x4b, 0xbb,
    0x68, 0xdc, 0x9a, 0x87, 0x32, 0xed, 0x4a, 0x02,
    0x00, 0x0c, 0xf7, 0xb8, 0xb4, 0x4a, 0x38, 0x11,
    0xdd, 0x02, 0x69, 0x8a, 0x4f, 0x2c, 0xc6, 0x16,
    0x6b, 0x1f, 0x71, 0x2b, 0xb3, 0x01, 0x0d, 0xe5,
    0x9b, 0xef, 0xae, 0x2d, 0x5b, 0x65, 0x9a, 0x2a,
    0x40, 0x96, 0xb0, 0x72, 0x6e, 0xa7, 0x81, 0x3e,
    0x17, 0x0e, 0x0a, 0x60, 0x26, 0x3d, 0x81, 0x3f,
    0x3c, 0x07, 0x47, 0x71, 0xe4, 0x98, 0x54, 0x7d,
    0x53, 0x1a, 0x6b, 0xba, 0xce, 0x96, 0xc9, 0xb4,
    0xcf, 0xa7, 0x18, 0x44, 0xde, 0xbd, 0x9a, 0x07,
    0x19, 0xf5, 0xac, 0xa9, 0xd1, 0x07, 0xbc, 0x1c,
    0xf0, 0x70, 0xf1, 0x84, 0x3a, 0x08, 0xe0, 0x75,
    0x65, 0x35, 0xf2, 0x63, 0x85, 0x11, 0x0b, 0x1e,
    0x68, 0xc6, 0x8a, 0x87, 0xe1, 0x8f, 0xf8, 0xdb,
    0x6e, 0xd4, 0x89, 0xaa, 0xae,
};
#endif /* DA_MACSEC_MODE_INGRESS */

#ifdef DA_MACSEC_MODE_EGRESS
/* MACsec key */
static uint8_t K2[] = {
    0x54, 0xa6, 0x61, 0xa3, 0x77, 0x91, 0xde, 0x1f,
    0xc2, 0x55, 0x1e, 0x01, 0xd4, 0x7a, 0xa1, 0xbf,
};

/* MACsec SCI */
static uint8_t SCI2[] = {
    0x75, 0x89, 0xab, 0x04, 0xf6, 0x2f, 0x00, 0x00,
};

static da_sa_params_t Transform_Params_VxLAN_Egress_MACsec =
{
    SAB_DIRECTION_EGRESS,
    SAB_OP_MACSEC,
    0,
    0,
    K2,
    sizeof(K2),
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

/* VxLAN source packet */
static const uint8_t SrcPacket_VxLAN_MACsec_Egress[] =
{
    0x95, 0x6f, 0xe7, 0x22, 0x6a, 0x80, 0x98, 0xc5,
    0x0c, 0xf1, 0x38, 0x07, 0x08, 0x00, 0x45, 0x00,
    0x00, 0xef, 0x11, 0x12, 0x00, 0x00, 0xe1, 0x11,
    0x75, 0x92, 0x61, 0x4b, 0x63, 0x97, 0x72, 0x06,
    0x1b, 0x71, 0x39, 0xad, 0x12, 0xb5, 0x00, 0xdb,
    0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
    0x06, 0x07, 0xee, 0x30, 0x7a, 0x1b, 0x2c, 0x1a,
    0x75, 0x89, 0xab, 0x04, 0xf6, 0x2f, 0x00, 0xbd,
    0xeb, 0xde, 0x89, 0x8a, 0x17, 0x4d, 0xa9, 0x97,
    0x30, 0xe9, 0x9d, 0x35, 0x87, 0xba, 0x35, 0xe6,
    0x34, 0x3b, 0xfa, 0x92, 0x36, 0xbb, 0x35, 0x8c,
    0x10, 0x23, 0x59, 0xe9, 0xd3, 0x20, 0x5e, 0x67,
    0x8e, 0xce, 0xa6, 0xbb, 0xc1, 0xbf, 0x66, 0x35,
    0x03, 0xdc, 0x30, 0x6c, 0x19, 0xa0, 0x6c, 0x52,
    0x57, 0x08, 0x75, 0x35, 0x26, 0x74, 0x19, 0x3c,
    0x20, 0xdc, 0x19, 0x24, 0x01, 0xe7, 0xce, 0x86,
    0x87, 0xef, 0xa8, 0x48, 0x95, 0x84, 0x4b, 0xbb,
    0x68, 0xdc, 0x9a, 0x87, 0x32, 0xed, 0x4a, 0x02,
    0x00, 0x0c, 0xf7, 0xb8, 0xb4, 0x4a, 0x38, 0x11,
    0xdd, 0x02, 0x69, 0x8a, 0x4f, 0x2c, 0xc6, 0x16,
    0x6b, 0x1f, 0x71, 0x2b, 0xb3, 0x01, 0x0d, 0xe5,
    0x9b, 0xef, 0xae, 0x2d, 0x5b, 0x65, 0x9a, 0x2a,
    0x40, 0x96, 0xb0, 0x72, 0x6e, 0xa7, 0x81, 0x3e,
    0x17, 0x0e, 0x0a, 0x60, 0x26, 0x3d, 0x81, 0x3f,
    0x3c, 0x07, 0x47, 0x71, 0xe4, 0x98, 0x54, 0x7d,
    0x53, 0x1a, 0x6b, 0xba, 0xce, 0x96, 0xc9, 0xb4,
    0xcf, 0xa7, 0x18, 0x44, 0xde, 0xbd, 0x9a, 0x07,
    0x19, 0xf5, 0xac, 0xa9, 0xd1, 0x07, 0xbc, 0x1c,
    0xf0, 0x70, 0xf1, 0x84, 0x3a, 0x08, 0xe0, 0x75,
    0x65, 0x35, 0xf2, 0x63, 0x85, 0x11, 0x0b, 0x1e,
    0x68, 0xc6, 0x8a, 0x87, 0xe1, 0x8f, 0xf8, 0xdb,
    0x6e, 0xd4, 0x89, 0xaa, 0xae,
};

static const uint8_t * IP_DA_VxLAN_MACsec_Egress_p =
    &SrcPacket_VxLAN_MACsec_Egress[50];

/* VxLAN (MACsec) destination packet */
static const uint8_t DstPacket_VxLAN_MACsec_Egress[] =
{
    0x95, 0x6f, 0xe7, 0x22, 0x6a, 0x80, 0x98, 0xc5,
    0x0c, 0xf1, 0x38, 0x07, 0x08, 0x00, 0x45, 0x00,
    0x01, 0x07, 0x11, 0x12, 0x00, 0x00, 0xe1, 0x11,
    0x75, 0x7a, 0x61, 0x4b, 0x63, 0x97, 0x72, 0x06,
    0x1b, 0x71, 0x39, 0xad, 0x12, 0xb5, 0x00, 0xf3,
    0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
    0x06, 0x07, 0xee, 0x30, 0x7a, 0x1b, 0x2c, 0x1a,
    0x75, 0x89, 0xab, 0x04, 0xf6, 0x2f, 0x88, 0xe5,
    0x5c, 0x00, 0x00, 0x00, 0x00, 0x01, 0xed, 0x8c,
    0x70, 0x45, 0x39, 0x53, 0xb0, 0xda, 0xc1, 0xda,
    0xb6, 0x57, 0xf3, 0x97, 0xd1, 0xcb, 0x08, 0x0c,
    0x5d, 0x22, 0xc7, 0x45, 0xe8, 0x10, 0xe2, 0x80,
    0x7f, 0xa3, 0x73, 0x54, 0x80, 0xea, 0xb5, 0x8a,
    0x59, 0x19, 0xb3, 0xc1, 0x40, 0xce, 0xac, 0x75,
    0x38, 0xef, 0x42, 0x93, 0x90, 0x2d, 0xc1, 0x60,
    0x5f, 0xec, 0x10, 0x5a, 0x0a, 0x3c, 0x25, 0x59,
    0x44, 0x4d, 0x1c, 0xb1, 0x5f, 0x03, 0x63, 0x66,
    0xe8, 0xd9, 0x34, 0x17, 0x1b, 0xf2, 0xef, 0x33,
    0xe5, 0x4a, 0x39, 0x44, 0xd6, 0xcf, 0x05, 0xaa,
    0xbc, 0x80, 0x1b, 0x09, 0xb1, 0x86, 0x70, 0x54,
    0xa6, 0x4c, 0x93, 0xb6, 0x4b, 0xf3, 0x86, 0x5b,
    0xe9, 0x9a, 0x44, 0xdf, 0x51, 0x58, 0x9a, 0xad,
    0x94, 0xd1, 0xc3, 0x24, 0x78, 0xd7, 0x20, 0x52,
    0xf7, 0x14, 0xcf, 0xb3, 0xd0, 0xe1, 0xf3, 0xca,
    0xa6, 0x12, 0x2e, 0x1d, 0x0e, 0x86, 0xb5, 0x04,
    0x8b, 0x25, 0x59, 0x9f, 0xfa, 0x6a, 0xad, 0x00,
    0x7f, 0x1b, 0x1f, 0xbb, 0x43, 0x52, 0x27, 0x1d,
    0x7c, 0x6d, 0xaa, 0xb8, 0x13, 0x5c, 0xaa, 0x85,
    0x8e, 0x73, 0x4d, 0x0b, 0x99, 0x02, 0x75, 0x2f,
    0x42, 0x4b, 0xc7, 0xd1, 0x1c, 0x4c, 0xc7, 0xcb,
    0x92, 0x6e, 0x0c, 0xe6, 0x4b, 0x17, 0x2e, 0xe2,
    0x20, 0xa5, 0x0d, 0x61, 0x4a, 0x24, 0x32, 0xeb,
    0xf5, 0xd1, 0xe8, 0x0e, 0xb0, 0xd6, 0x92, 0x36,
    0xb4, 0xbe, 0x66, 0x0b, 0x4e, 0x38, 0x43, 0xa4,
    0x41, 0x27, 0xe5, 0x82, 0x2e,
};
#endif /* DA_MACSEC_MODE_EGRESS */


/*----------------------------------------------------------------------------
 * da_secy_cfye_VxLAN_MACsec_transform
 */
bool
da_secy_cfye_VxLAN_MACsec_transform(
        bool fVerbose,
        bool fIngress)
{
    unsigned int vPort = 0;
    unsigned int Channel = 1;

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
        Log_FormattedMessage("DA_MACSEC: Perform Transform for VxLAN\n");
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
        CfyE_Status_t CfyE_Rc;
        CfyE_Device_Limits_t Device_Limits;

        CfyE_Rc = CfyE_Device_Limits_Get(CFYE_DEVICE_ID,
                                             &Device_Limits);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("CfyE_Device_Limits returned error %d\n", CfyE_Rc);
            return false;
        }


        if (Device_Limits.fVxLAN)
        {
            Log_FormattedMessage("VxLAN is supported on this HW\n");
        }
        else
        {
            Log_FormattedMessage("VxLAN is not\n"
                                 "supported on this HW version, skipping.\n");
                CfyE_Device_Uninit(CFYE_DEVICE_ID);
                return true;
        }
    }

    {
        SecY_Settings_t Settings;

        Log_FormattedMessage("DA_MACSEC: Initializing SecY\n");

        ZEROINIT(Settings);

        /* Non-matching SA flow packet processing rules */
        /* Default rule is to drop non-matching SA packets */
        Settings.DropBypass.DropType = SECY_SA_DROP_INTERNAL;

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

    /* Install vPort to use with SA */
    {
        CfyE_vPort_t vPortParams;

        ZEROINIT(vPortParams);

        vPortParams.SecTagOffset = 12;
#ifdef DA_MACSEC_MODE_EGRESS
        vPortParams.PktExtension = 2;
#endif

        CfyE_Rc = CfyE_vPort_Add(CFYE_DEVICE_ID,
                                 &CfyE_vPortHandle,
                                 &vPortParams,
                                 CYFE_MODE_MACSEC);
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
                SCI1;
            SA_Params.Params.Ingress.AN = 0;
            SA_Params.Params.Ingress.fAllowTagged = true;
            SA_Params.Params.Ingress.PreSecTagAuthStart = 0;
            SA_Params.Params.Ingress.PreSecTagAuthLength = 12;

            SA_Params.TransformRecord_p =
                da_macsec_build_sa(&Transform_Params_VxLAN_Ingress_MACsec,
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
            SA_Params.Params.Egress.fUseES = true;
            SA_Params.Params.Egress.fUseSCB = true;
            SA_Params.Params.Egress.fIncludeSCI = false;
            SA_Params.Params.Egress.fConfProtect = true;
            SA_Params.Params.Egress.fAllowDataPkts = true;
            SA_Params.Params.Egress.PreSecTagAuthStart = 0;
            SA_Params.Params.Egress.PreSecTagAuthLength = 12;

            SA_Params.TransformRecord_p =
                da_macsec_build_sa(&Transform_Params_VxLAN_Egress_MACsec,
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

    /* Install parsers settings for SecTAG and VxLAN ports */
    {
        CfyE_Device_t DeviceParams;
        CfyE_HeaderParser_t HeaderParams;
        CfyE_SecTAG_Parser_t SecTAGParams;
        CfyE_L4_Ports_t L4_Ports;
        CfyE_Channel_L3L4_t L3L4;
        CfyE_Device_Control_t DeviceCtrl;

        ZEROINIT(DeviceParams);
        ZEROINIT(HeaderParams);
        ZEROINIT(SecTAGParams);
        ZEROINIT(L4_Ports);
        ZEROINIT(L3L4);
        ZEROINIT(DeviceCtrl);

        SecTAGParams.fCheckVersion = true;
        SecTAGParams.fCheckKay = true;
        SecTAGParams.fCompType = true;
        SecTAGParams.MACsecTagValue = 0x88E5;

        L3L4.flags = CFYE_VXL_FLAG_PARSE_IP | CFYE_VXL_FLAG_PARSE_UDP |
            CFYE_VXL_FLAG_PARSE_VXLAN1;
        L4_Ports.VxLAN_Port1 = 0x12b5;
        L4_Ports.VxLAN_Port2 = 0;

        HeaderParams.SecTAG_Parser_p = &SecTAGParams;
        HeaderParams.L4_Ports_p = &L4_Ports;
        DeviceParams.HeaderParser_p = &HeaderParams;

        DeviceCtrl.L3L4_p = &L3L4;
        DeviceParams.Control_p = &DeviceCtrl;

        CfyE_Rc = CfyE_Device_Update(CFYE_DEVICE_ID,
                                     Channel,
                                     &DeviceParams);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: Failed, CfyE_Device_Update()=%d\n", CfyE_Rc);
            goto error_exit_init;
        }
    }

    /* Install rule */
    {
        CfyE_Rule_t RuleParams;
        unsigned int MaxCfyEChannels = 0;

        ZEROINIT(RuleParams);

        RuleParams.Policy.vPortHandle = CfyE_vPortHandle;

        RuleParams.Mask.PacketType = CFYE_RULE_PKT_TYPE_MASK; /* Exact match on all these fields. */
        RuleParams.Mask.ChannelID = CFYE_RULE_CHANNEL_ID_MASK;
        RuleParams.Mask.NumTags = CFYE_RULE_NUMTAGS_MASK;
        RuleParams.Key.PacketType = CFYE_RULE_PKT_TYPE_OTHER;
        RuleParams.Key.ChannelID = Channel;
        RuleParams.Key.NumTags = 0x21;


        CfyE_Rc = CfyE_Device_Limits(CFYE_DEVICE_ID,
                                     &MaxCfyEChannels,
                                     NULL,
                                     NULL);

        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("CfyE_Device_Limits returned error %d\n", CfyE_Rc);
            return CfyE_Rc;
        }


        RuleParams.DataMask[0] = 0xffffffff; /* Match on dest mac */
        RuleParams.DataMask[1] = 0x0000ffff;
        RuleParams.DataMask[2] = 0x00000000;
        RuleParams.DataMask[3] = 0x00000000;

        {
            const uint8_t *p = NULL;
#ifdef DA_MACSEC_MODE_INGRESS
            if (fIngress)
            {
                p = IP_DA_VxLAN_MACsec_Ingress_p;
            }
#endif
#ifdef DA_MACSEC_MODE_EGRESS
            if (!fIngress)
            {
                p = IP_DA_VxLAN_MACsec_Egress_p;
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
            PktByteCount = sizeof(SrcPacket_VxLAN_MACsec_Ingress);
            memcpy(InputPktHostAddress,
                   SrcPacket_VxLAN_MACsec_Ingress,
                   PktByteCount);

            if (fVerbose)
            {
                Log_FormattedMessage("DA_MACSEC: "
                                     "Process input packet of size %d\n",
                                     PktByteCount);
                Log_HexDump("Input packet",
                            0,
                            SrcPacket_VxLAN_MACsec_Ingress,
                            PktByteCount);
            }

            /* Expected packet */
            ExpectedPktByteCount = sizeof(DstPacket_VxLAN_MACsec_Ingress);
            memcpy(ExpectedPktHostAddress,
                   DstPacket_VxLAN_MACsec_Ingress,
                   ExpectedPktByteCount);
        }
#endif /* DA_MACSEC_MODE_INGRESS */

#ifdef DA_MACSEC_MODE_EGRESS
        if (!fIngress)
        {
            /* Input packet */
            PktByteCount = sizeof(SrcPacket_VxLAN_MACsec_Egress);
            memcpy(InputPktHostAddress,
                   SrcPacket_VxLAN_MACsec_Egress,
                   PktByteCount);

            if (fVerbose)
            {
                Log_FormattedMessage("DA_MACSEC: "
                                     "Process input packet of size %d\n",
                                     PktByteCount);
                Log_HexDump("Input packet",
                            0,
                            SrcPacket_VxLAN_MACsec_Egress,
                            PktByteCount);
            }

            /* Expected packet */
            ExpectedPktByteCount = sizeof(DstPacket_VxLAN_MACsec_Egress);
            memcpy(ExpectedPktHostAddress,
                   DstPacket_VxLAN_MACsec_Egress,
                   ExpectedPktByteCount);
        }
#endif /* DA_MACSEC_MODE_EGRESS */

        /* Fill in the status data structure */
        ZEROINIT(PktStatusIn);

        PktStatusIn.SecTAGOffset = 12;

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

        /* Read the TCAM hit statistics counters */
        /* Note: It is assumed that the rule is inserted at the first index (0) */
        {
            CfyE_Statistics_TCAM_t TCAMStat;

            ZEROINIT(TCAMStat);

            CfyE_Rc = CfyE_Statistics_TCAM_Get(CFYE_DEVICE_ID, 0, &TCAMStat, true);
            if (CfyE_Rc != CFYE_STATUS_OK)
            {
                LOG_CRIT("DA_MACSEC: Failed, CfyE_TCAM_Statistics_Get)=%d\n",
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

                if ((SAStats.InOctetsDecrypted.Lo != 191) ||
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
                             "\tInOctetsDecrypted=%u, expected 191\n"
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

                if ((IfcStats.InOctetsUncontrolled.Lo != 277) ||
                    (IfcStats.InPktsUnicastUncontrolled.Lo != 0) ||
                    (IfcStats.InPktsMulticastUncontrolled.Lo != 1) ||
                    (IfcStats.InPktsBroadcastUncontrolled.Lo != 0) ||
                    (IfcStats.InOctetsControlled.Lo != 203) ||
                    (IfcStats.InPktsUnicastControlled.Lo != 0) ||
                    (IfcStats.InPktsMulticastControlled.Lo != 1) ||
                    (IfcStats.InPktsBroadcastControlled.Lo != 0))
                {
                    LOG_CRIT("DA_MACSEC: Failed, IFC/IFC1 statistics check:\n"
                             "\tInOctetsUncontrolled=%u, expected 277\n"
                             "\tInPktsUnicastUncontrolled=%u, expected 0\n"
                             "\tInPktsMulticastUncontrolled=%u, expected 1\n"
                             "\tInPktsBroadcastUncontrolled=%u, expected 0\n"
                             "\tInOctetsControlled=%u, expected 203\n"
                             "\tInPktsUnicastControlled=%u, expected 0\n"
                             "\tInPktsMulticastControlled=%u, expected 1\n"
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

                if ((SAStats.OutOctetsEncryptedProtected.Lo != 191) ||
                    (SAStats.OutPktsEncryptedProtected.Lo != 1) ||
                    (SAStats.OutPktsTooLong.Lo != 0) ||
                    (SAStats.OutPktsSANotInUse.Lo != 0))
                {
                    LOG_CRIT("DA_MACSEC: Failed, SA statistics check:\n"
                             "\tOutOctetsEncryptedProtected=%u, expected 191,\n"
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

                if ((IfcStats.OutOctetsCommon.Lo != 277) ||
                    (IfcStats.OutOctetsUncontrolled.Lo != 0) ||
                    (IfcStats.OutPktsUnicastUncontrolled.Lo != 0) ||
                    (IfcStats.OutPktsMulticastUncontrolled.Lo != 0) ||
                    (IfcStats.OutPktsBroadcastUncontrolled.Lo != 0) ||
                    (IfcStats.OutOctetsControlled.Lo != 203) ||
                    (IfcStats.OutPktsUnicastControlled.Lo != 0) ||
                    (IfcStats.OutPktsMulticastControlled.Lo != 1) ||
                    (IfcStats.OutPktsBroadcastControlled.Lo != 0))
                {
                    LOG_CRIT("DA_MACSEC: Failed, IFC/IFC1 statistics check:\n"
                             "\tOutOctetsCommon=%u, expected 277\n"
                             "\tOutOctetsUncontrolled=%u, expected 0\n"
                             "\tOutPktsUnicastUncontrolled=%u, expected 0\n"
                             "\tOutPktsMulticastUncontrolled=%u, expected 0\n"
                             "\tOutPktsBroadcastUncontrolled=%u, expected 0\n"
                             "\tOutOctetsControlled=%u, expected 203\n"
                             "\tOutPktsUnicastControlled=%u, expected 0\n"
                             "\tOutPktsMulticastControlled=%u, expected 1\n"
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
#endif /* DA_MACSEC_VXLAN_ENABLE */

/* end of file da_secy_cfye_vxlan_macsec.c */
