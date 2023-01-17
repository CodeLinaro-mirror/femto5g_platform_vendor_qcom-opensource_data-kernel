  /* da_secy_cfye_control_pkt.c
 *
 * Demo Application, Process control packet processing before, during and
 * after SA lifetime using SecY and CfyE API.
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
#define CONTROL_ETYPE 0x888e /* Ether type for control packets */
#define TEST_VLAN_ID1 0x432  /* VLAN ID to be used in this test */
#define TEST_VLAN_ID2 0x234  /* VLAN ID to be used in this test */
#define CHANNEL_MUST 0   /* Channel configured as must-secure */
#define CHANNEL_SHOULD 1 /* Channel configured as should-secure */

#define NR_DEFAULT_VPORTS 2 /* Two default vPorts, one for must-secure, one for
                             should-secure. */
#define DEFAULT_MUST 0
#define DEFAULT_SHOULD 1

#define NR_VPORTS 3 /* Number of vPorts to use */
/* The test uses 5 vPorts
 *
 * 0 One default vPort for must-secure, pass only control packets.
 * 1 One default vPort for should-secure, pass all packets.
 *
 * 2 a vPort that carries all traffic on channel #0, will be must-secure.
 * 3 a vPort that carries all traffic on channel #1 with VLAN ID 0x432, will
 *   be should-secure.
 * 4 a vPort that carries all traffic on channel #1 with VLAN ID 0x234, will
 *   be should-secure.
 *
 * When the SAs for vPorts 2, 3, 4 are not active, the corresponding TCAM
 * rules are not enabled and the traffic will hit the per-channel default
 * vPort.
 */

/*----------------------------------------------------------------------------
 * Local variables
 */

/* MACsec key */
static uint8_t K1[] = {
    0xad, 0x7a, 0x2b, 0xd0, 0x3e, 0xac, 0x83, 0x5a,
    0x6f, 0x62, 0x0f, 0xdc, 0xb5, 0x06, 0xb3, 0x45,
};

/* MACsec SCI */
static uint8_t SCI1[] = {
    0x12, 0x15, 0x35, 0x24, 0xc0, 0x89, 0x5e, 0x81,
};




#ifdef DA_MACSEC_MODE_INGRESS

static da_sa_params_t Transform_Params_MACsec =
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
    0,
#if defined(DA_IPSEC_ENABLE)
    0,
#endif
};

/* Dummy SCI */
static uint8_t SCI2[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

#endif /* DA_MACSEC_MODE_INGRESS */

#ifdef DA_MACSEC_MODE_EGRESS
static da_sa_params_t Transform_Params_MACsec =
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


#endif /* DA_MACSEC_MODE_EGRESS */


/* MACsec control packet  */
static const uint8_t Control_Pkt[] =
{
    0xd6, 0x09, 0xb1, 0xf0,
    0x56, 0x63, 0x7a, 0x0d,
    0x46, 0xdf, 0x99, 0x8d,
    0x88, 0x8e, 0x0f, 0x10,
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


/* MACsec data packet (plaintext)  */
static const uint8_t Plaintext_Pkt[] =
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

/* MACsec encrypted packet */
static const uint8_t MACsec_Pkt[] =
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

/* MACsec control packet with VLAN  */
static const uint8_t Control_Pkt_VLAN1[] =
{
    0xd6, 0x09, 0xb1, 0xf0,
    0x56, 0x63, 0x7a, 0x0d,
    0x46, 0xdf, 0x99, 0x8d,
    0x81, 0x00, 0x04, 0x32,
    0x88, 0x8e, 0x0f, 0x10,
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


/* MACsec data packet (plaintext) with VLAN */
static const uint8_t Plaintext_Pkt_VLAN1[] =
{
    0xd6, 0x09, 0xb1, 0xf0,
    0x56, 0x63, 0x7a, 0x0d,
    0x46, 0xdf, 0x99, 0x8d,
    0x81, 0x00, 0x04, 0x32,
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

/* MACsec encrypted packet with VLAN */
static const uint8_t MACsec_Pkt_VLAN1[] =
{
    0xd6, 0x09, 0xb1, 0xf0,
    0x56, 0x63, 0x7a, 0x0d,
    0x46, 0xdf, 0x99, 0x8d,
    0x81, 0x00, 0x04, 0x32,
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

/* MACsec control packet with VLAN  */
static const uint8_t Control_Pkt_VLAN2[] =
{
    0xd6, 0x09, 0xb1, 0xf0,
    0x56, 0x63, 0x7a, 0x0d,
    0x46, 0xdf, 0x99, 0x8d,
    0x81, 0x00, 0x02, 0x34,
    0x88, 0x8e, 0x0f, 0x10,
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


/* MACsec data packet (plaintext) with VLAN */
static const uint8_t Plaintext_Pkt_VLAN2[] =
{
    0xd6, 0x09, 0xb1, 0xf0,
    0x56, 0x63, 0x7a, 0x0d,
    0x46, 0xdf, 0x99, 0x8d,
    0x81, 0x00, 0x02, 0x34,
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

/* MACsec encrypted packet with VLAN */
static const uint8_t MACsec_Pkt_VLAN2[] =
{
    0xd6, 0x09, 0xb1, 0xf0,
    0x56, 0x63, 0x7a, 0x0d,
    0x46, 0xdf, 0x99, 0x8d,
    0x81, 0x00, 0x02, 0x34,
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



static uint8_t InputPktHostAddress[PKT_BUFFER_BYTE_COUNT];
static uint8_t ProcessedPktHostAddress[PKT_BUFFER_BYTE_COUNT];
static uint8_t ExpectedPktHostAddress[PKT_BUFFER_BYTE_COUNT];

static bool
da_secy_process_pkt(
    bool fIngress,
    bool fVerbose,
    unsigned int channel,
    const uint8_t *input_pkt,
    unsigned int input_len,
    const uint8_t *exp_pkt,
    unsigned int exp_len,
    bool fExpectDrop)
{
    PktIO_Packet_Status_In_t PktStatusIn;
    PktIO_Packet_Status_Out_t PktStatusOut;
    unsigned int ByteCount;
    int RetCode;

    memcpy(InputPktHostAddress, input_pkt, input_len);
    memcpy(ExpectedPktHostAddress, exp_pkt, exp_len);

    if (fExpectDrop && !fIngress)
    {
        exp_len=0;
        Log_FormattedMessage("DA_MACSEC: expect internal drop for egress.\n");
    }

    if (fVerbose)
    {
        Log_FormattedMessage("DA_MACSEC: "
                             "Process input packet of size %d\n",
                             input_len);
        Log_HexDump("Input packet",
                    0,
                    input_pkt,
                    input_len);
    }
    /* Fill in the status data structure */
    ZEROINIT(PktStatusIn);
    RetCode = PktIO_Packet_Put(InputPktHostAddress,
                               input_len,
                               &PktStatusIn,
                               channel,
                               fIngress ? PKTIO_PACKET_DIRECTION_INGRESS :
                               PKTIO_PACKET_DIRECTION_EGRESS);
    if (RetCode != 0)
    {
        LOG_CRIT("DA_MACSEC: PktIO_Packet_Put error %d\n", RetCode);
        return false;
    }
    /* Fill in the status data structure */
    ZEROINIT(PktStatusOut);

    /* Receive the processed packet */
    if (da_macsec_get_one(fIngress,
                          ProcessedPktHostAddress,
                          &ByteCount,
                          &PktStatusOut,
                          channel) == 0 &&
        PktStatusOut.PacketStatusMask == 0)
    {
        LOG_CRIT("DA_MACSEC: Error obtaining result packet\n");
        return false;
    }

    if (fVerbose)
    {
        Log_FormattedMessage("DA_MACSEC: PktIO_Packet_Get Size/"
                             "StatusMask/Channel/vPort/SAIndex/SCIndex"
                             "/RuleIndex: %d/0x%X/%d/%d/%d/%d/%d\n",
                             ByteCount,
                             PktStatusOut.PacketStatusMask,
                             channel,
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
    if ( ByteCount != exp_len)
    {
        LOG_CRIT("DA_MACSEC: Packet sizes differ expected=%d, received=%d\n",
                 exp_len,
                 ByteCount);
        Log_HexDump("Expected packet",
                    0,
                    ExpectedPktHostAddress,
                    exp_len);
        return false;
    }

    if (memcmp(ProcessedPktHostAddress,
               ExpectedPktHostAddress,
               exp_len) != 0)
    {
        LOG_CRIT("DA_MACSEC: Contents of packets differ size=%d\n",
                 exp_len);
        Log_HexDump("Expected packet",
                    0,
                    ExpectedPktHostAddress,
                    exp_len);
        return false;
    }

    if ( fExpectDrop)
    {
        if((PktStatusOut.PacketStatusMask & PKTIO_PACKET_CRC_ERROR) == 0)
        {
            LOG_CRIT("DA_MACSEC: Error: No CRC error on packet that must be dropped"
                     "           on must-secure channel\n");
            return false;
        }
        else
        {
            Log_FormattedMessage("DA_MACSEC: Packet has expected CRC e r r o r\n");
        }
    }
    else
    {
        if ((PktStatusOut.PacketStatusMask & PKTIO_PACKET_CRC_ERROR) != 0)
        {
            LOG_CRIT("DA_MACSEC: Error: Unexpected CRC error on packet\n");
            return false;
        }
        else
        {
            Log_FormattedMessage("DA_MACSEC: Packet has no CRC e r r o r OK\n");
        }
    }

    return true;
};

static SecY_SAHandle_t SecY_SAHandle[NR_VPORTS];
static CfyE_vPortHandle_t CfyE_vPortHandle[NR_VPORTS];
static unsigned int vPortIndex[NR_VPORTS];
static CfyE_RuleHandle_t CfyE_RuleHandle[NR_VPORTS];

static SecY_SAHandle_t SecY_SAHandleDefault[NR_DEFAULT_VPORTS];
static CfyE_vPortHandle_t CfyE_vPortHandleDefault[NR_DEFAULT_VPORTS];
static unsigned int vPortIndexDefault[NR_DEFAULT_VPORTS];

/*----------------------------------------------------------------------------
 * da_secy_cfye_control_pkt
 */
bool
da_secy_cfye_control_pkt(
        bool fVerbose,
        bool fIngress)
{
    SecY_Status_t SecY_Rc;
    CfyE_Status_t CfyE_Rc;
    bool fSuccess = false;
    unsigned int i;
    Log_FormattedMessage("DA_MACSEC: Starting test for %sgress\n",
                         fIngress ? "in" : "e");

    /* Initialize resource variables to NULL */
    for (i=0; i<NR_VPORTS; i++)
    {
        SecY_SAHandle[i] = SecY_SAHandle_NULL;
        CfyE_vPortHandle[i] = CfyE_vPortHandle_NULL;
        CfyE_RuleHandle[i] = CfyE_RuleHandle_NULL;
    }

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

    /* Create default vPorts */
    for (i=0; i<NR_DEFAULT_VPORTS; i++)
    {
        CfyE_vPort_t vPortParams;

        ZEROINIT(vPortParams);
        vPortParams.SecTagOffset = 12;
#ifdef DA_MACSEC_MODE_EGRESS
        vPortParams.PktExtension = 3;
#endif

        CfyE_Rc = CfyE_vPort_Add(CFYE_DEVICE_ID,
                                 &CfyE_vPortHandleDefault[i],
                                 &vPortParams,
                                 SECY_MODE_MACSEC);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: Failed, CfyE_vPort_Add()=%d\n", CfyE_Rc);
            goto error_exit;
        }

        /* Now get vPort index to use when installing SA: */
        CfyE_vPortIndex_Get(CfyE_vPortHandleDefault[i], &vPortIndexDefault[i]);

        if (fVerbose)
        {
            Log_FormattedMessage("DA_MACSEC: D e f a u l t vPort %d added\n",i);
        }
    }


    /* Install default SAs.*/
    for (i=0; i<NR_DEFAULT_VPORTS; i++)
    {
        SecY_SA_t SA_Params;

        ZEROINIT(SA_Params);
#ifdef DA_MACSEC_MODE_INGRESS
        if (fIngress)
        {
            SA_Params.DropType = SECY_SA_DROP_CRC_ERROR;
            SA_Params.DestPort = SECY_PORT_CONTROLLED;
            if (i == DEFAULT_SHOULD)
            {
                SA_Params.ActionType = SECY_SA_ACTION_BYPASS;
            }
            else
            {
                SA_Params.ActionType = SECY_SA_ACTION_INGRESS;

                SA_Params.Params.Ingress.fSAInUse = false;
                SA_Params.Params.Ingress.ValidateFramesTagged =
                    SECY_FRAME_VALIDATE_DISABLE;
                SA_Params.Params.Ingress.fReplayProtect = false;
                SA_Params.Params.Ingress.SCI_p = SCI2;
                SA_Params.Params.Ingress.AN = 0;
                SA_Params.Params.Ingress.fAllowTagged = false;
                SA_Params.Params.Ingress.fAllowUntagged = false;
                SA_Params.Params.Ingress.PreSecTagAuthLength = 12;
            }
        }
#endif /* DA_MACSEC_MODE_INGRESS */

#ifdef DA_MACSEC_MODE_EGRESS
        if (!fIngress)
        {
            SA_Params.DropType = SECY_SA_DROP_INTERNAL;
            SA_Params.DestPort = SECY_PORT_COMMON;

            if (i == DEFAULT_SHOULD)
            {
                SA_Params.ActionType = SECY_SA_ACTION_BYPASS;
            }
            else
            {
                SA_Params.ActionType = SECY_SA_ACTION_EGRESS;
                SA_Params.Params.Egress.fSAInUse = false;
                SA_Params.Params.Egress.fProtectFrames = false;
                SA_Params.Params.Egress.fIncludeSCI = false;
                SA_Params.Params.Egress.fConfProtect = false;
                SA_Params.Params.Egress.fAllowDataPkts = false;
                SA_Params.Params.Egress.PreSecTagAuthLength = 12;
            }
        }
#endif /* DA_MACSEC_MODE_EGRESS */

        SecY_Rc = SecY_SA_Add(SECY_DEVICE_ID, vPortIndexDefault[i],
                              &SecY_SAHandleDefault[i], &SA_Params);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: Failed, SecY_SA_Add()=%d\n", SecY_Rc);
            goto error_exit;
        }
        if (i == DEFAULT_MUST)
        {
            /* SecY_SA_Add() creates SA that is always enabled, disable it
               by calling SecY_SA_Update(). This does not apply to the
               bypass SA in should-secure */
            SecY_Rc = SecY_SA_Update(SECY_DEVICE_ID, SecY_SAHandleDefault[i],
                                     &SA_Params);
            if (SecY_Rc != SECY_STATUS_OK)
            {
                LOG_CRIT("DA_MACSEC: Failed, SecY_SA_Update()=%d\n", SecY_Rc);
                goto error_exit;
            }
        }

        if (SA_Params.TransformRecord_p)
        {
            da_macsec_free(SA_Params.TransformRecord_p);
        }

        if (fVerbose)
        {
            Log_FormattedMessage("DA_MACSEC: D e f a u l t  SA for vPort %d added\n",
                                 i);
        }
    }

    /* Configure control packet and VLAN parsers, as well as default vPorts
       for each channel. Channel 0 will be must-secure all others
       should-secure */
    {
        CfyE_Device_t DeviceParams;
        CfyE_Device_Exceptions_t DeviceExceptions;
        CfyE_Device_Control_t DeviceControl;
        CfyE_ControlPacket_t CP;
        CfyE_HeaderParser_t HeaderParams;
        CfyE_VLAN_Parser_t VLANTagParams;
        CfyE_Device_Limits_t DeviceLimits;
        ZEROINIT(DeviceParams);
        ZEROINIT(HeaderParams);
        ZEROINIT(VLANTagParams);
        ZEROINIT(CP);
        ZEROINIT(DeviceControl);
        ZEROINIT(DeviceExceptions);

        CP.MAC_DA_ET_Rules[0].EtherType = CONTROL_ETYPE;
        CP.CPMatchEnableMask = BIT_8; /* Enable Etype[0] matching */
        CP.CPMatchModeMask = BIT_0; /* Etype[0] matching after VLAN tag */
        DeviceParams.CP_p = &CP;

        DeviceExceptions.DropAction = CFYE_DO_NOT_DROP;
        DeviceExceptions.fForceDrop = false;
        DeviceExceptions.fDefaultVPortValid = true;
        DeviceControl.fLowLatencyBypass = false;
        DeviceControl.Exceptions_p = &DeviceExceptions;
        DeviceParams.Control_p = &DeviceControl;

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

        HeaderParams.VLAN_Parser_p = &VLANTagParams;
        DeviceParams.HeaderParser_p = &HeaderParams;

        CfyE_Rc = CfyE_Device_Limits_Get(CFYE_DEVICE_ID, &DeviceLimits);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: Failed, CfyE_Device_Limits_Get()=%d\n",
                     CfyE_Rc);
            goto error_exit;
        }

        for (i = 0; i < DeviceLimits.channel_count; i++)
        {
            /* Determine here which channels are must-secure or should-secure*/
            if (i == CHANNEL_MUST)
                DeviceExceptions.DefaultVPort = vPortIndexDefault[DEFAULT_MUST];
            else
                DeviceExceptions.DefaultVPort = vPortIndexDefault[DEFAULT_SHOULD];

            CfyE_Rc = CfyE_Device_Update(CFYE_DEVICE_ID, i, &DeviceParams);
            if (CfyE_Rc != CFYE_STATUS_OK)
            {
                LOG_CRIT("DA_MACSEC: CfyE device could not be updated, error=%d\n",
                         CfyE_Rc);
                goto error_exit;
            }
        }
    }

    /* At this point the Engine is ready to pass control packets on all channels
       and pass data packets on channels with should-secure policy using the
       per-channel default vPorts.

       The actual MACsec SAs, vPorts and rules  have not been installed yet.
    */
    if (fVerbose)
    {
        Log_FormattedMessage("DA_MACSEC: Ready to process packets"
                             " before SA installed.\n");
    }

    /* Packet processing */
    if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_MUST,
                             Plaintext_Pkt, sizeof(Plaintext_Pkt),
                             Plaintext_Pkt, sizeof(Plaintext_Pkt), true))
        goto error_exit;
    if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_SHOULD,
                             Plaintext_Pkt, sizeof(Plaintext_Pkt),
                             Plaintext_Pkt, sizeof(Plaintext_Pkt), false))
        goto error_exit;
    if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_SHOULD,
                             Plaintext_Pkt_VLAN1, sizeof(Plaintext_Pkt_VLAN1),
                             Plaintext_Pkt_VLAN1, sizeof(Plaintext_Pkt_VLAN1),
                             false))
        goto error_exit;
    if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_SHOULD,
                             Plaintext_Pkt_VLAN2, sizeof(Plaintext_Pkt_VLAN2),
                             Plaintext_Pkt_VLAN2, sizeof(Plaintext_Pkt_VLAN2),
                             false))
        goto error_exit;
    /* MACsec packet on channel 0 without a VLAN tag,
       will not match a rule, will be dropped by must-secure default. */
    if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_MUST,
                             MACsec_Pkt, sizeof(MACsec_Pkt),
                             MACsec_Pkt, sizeof(MACsec_Pkt), true))
            goto error_exit;
    /* MACsec packet on channel 1 without a VLAN tag,
       will not match a rule, will be bypassed by should-secure default. */
    if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_SHOULD,
                             MACsec_Pkt, sizeof(MACsec_Pkt),
                             MACsec_Pkt, sizeof(MACsec_Pkt), false))
            goto error_exit;
    if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_MUST,
                             Control_Pkt, sizeof(Control_Pkt),
                             Control_Pkt, sizeof(Control_Pkt), false))
        goto error_exit;
    if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_SHOULD,
                             Control_Pkt, sizeof(Control_Pkt),
                             Control_Pkt, sizeof(Control_Pkt), false))
        goto error_exit;
    if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_SHOULD,
                             Control_Pkt_VLAN1, sizeof(Control_Pkt_VLAN1),
                             Control_Pkt_VLAN1, sizeof(Control_Pkt_VLAN1),
                             false))
        goto error_exit;
    if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_SHOULD,
                             Control_Pkt_VLAN2, sizeof(Control_Pkt_VLAN2),
                             Control_Pkt_VLAN2, sizeof(Control_Pkt_VLAN2),
                             false))
        goto error_exit;

    /* Create vPorts */
    for (i = 0; i < NR_VPORTS; i++)
    {
        CfyE_vPort_t vPortParams;
        SecY_SA_t SA_Params;
        uint32_t SAWordCount = 0;
        CfyE_Rule_t RuleParams;

        ZEROINIT(vPortParams);
        ZEROINIT(SA_Params);
        ZEROINIT(RuleParams);

        if (i>0)
            vPortParams.SecTagOffset = 16; /* vPorts 3 and 4 have VLAN tag */
        else
            vPortParams.SecTagOffset = 12; /* vPort 2 has no VLAN tag */
#ifdef DA_MACSEC_MODE_EGRESS
        vPortParams.PktExtension = 3;
#endif

        CfyE_Rc = CfyE_vPort_Add(CFYE_DEVICE_ID,
                                 &CfyE_vPortHandle[i],
                                 &vPortParams,
                                 SECY_MODE_MACSEC);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: Failed, CfyE_vPort_Add()=%d\n", CfyE_Rc);
            goto error_exit;
        }

        /* Now get vPort index to use when installing SA: */
        CfyE_vPortIndex_Get(CfyE_vPortHandle[i], &vPortIndex[i]);

        if (fVerbose)
        {
            Log_FormattedMessage("DA_MACSEC: vPort %d added\n",
                                 i + NR_DEFAULT_VPORTS);
        }

#ifdef DA_MACSEC_MODE_INGRESS
        if (fIngress)
        {
            SA_Params.ActionType = SECY_SA_ACTION_INGRESS;
            SA_Params.DropType = SECY_SA_DROP_CRC_ERROR;
            SA_Params.DestPort = SECY_PORT_CONTROLLED;

            SA_Params.Params.Ingress.ValidateFramesTagged =
                SECY_FRAME_VALIDATE_STRICT;
            SA_Params.Params.Ingress.fSAInUse = true;
            SA_Params.Params.Ingress.fReplayProtect = true;
            SA_Params.Params.Ingress.SCI_p = SCI1;
            SA_Params.Params.Ingress.AN = 2;
            SA_Params.Params.Ingress.fAllowTagged = true;
            SA_Params.Params.Ingress.fAllowUntagged = (i != 0);
            SA_Params.Params.Ingress.PreSecTagAuthLength = 12;

            SA_Params.TransformRecord_p =
                da_macsec_build_sa(&Transform_Params_MACsec,
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
                da_macsec_build_sa(&Transform_Params_MACsec,
                                   &SAWordCount);
            SA_Params.SA_WordCount = SAWordCount;
        }
#endif /* DA_MACSEC_MODE_EGRESS */

        SecY_Rc = SecY_SA_Add(SECY_DEVICE_ID, vPortIndex[i], &SecY_SAHandle[i],
                              &SA_Params);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: Failed, SecY_SA_Add()=%d\n", SecY_Rc);
            goto error_exit;
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
            Log_FormattedMessage("DA_MACSEC: MACsec SA for vPort %d added\n",
                                 i + NR_DEFAULT_VPORTS);
        }


        RuleParams.Policy.vPortHandle = CfyE_vPortHandle[i];

        /* Exact match on channel, no other fields to match on. */
        RuleParams.Mask.ChannelID = 0x3f;

        RuleParams.Key.ChannelID = (i==0) ? CHANNEL_MUST : CHANNEL_SHOULD;

        /* Rule 0 matches on entire channel, rules 1 and 2 match
           on specific VLAN tag on channel 1. */
        if (i>0)
        {
            /* Create a match on specific VLAN tag */
            RuleParams.Mask.NumTags = 0x3f;
            RuleParams.Key.NumTags = 0x02;  /* Match on exactly one tag */
            RuleParams.DataMask[2] = 0xff0f0000; /* Match on VLAN ID */
            if (i==1)
                RuleParams.Data[2] = ((TEST_VLAN_ID1 >> 8) << 16) |
                    ((TEST_VLAN_ID1 & 0xff) << 24);
            else
                RuleParams.Data[2] = ((TEST_VLAN_ID2 >> 8) << 16) |
                    ((TEST_VLAN_ID2 & 0xff) << 24);
        }

        CfyE_Rc = CfyE_Rule_Add(CFYE_DEVICE_ID, CfyE_vPortHandle[i],
                                &CfyE_RuleHandle[i], &RuleParams);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: Failed, CfyE_Rule_Add()=%d\n", CfyE_Rc);
            goto error_exit;
        }

        CfyE_Rc = CfyE_Rule_Enable(CFYE_DEVICE_ID, CfyE_RuleHandle[i], true);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: Failed, CfyE_Rule_Enable()=%d\n", CfyE_Rc);
            goto error_exit;
        }

        if (fVerbose)
        {
            Log_FormattedMessage("DA_MACSEC: Rule enabled for vPort %d\n",
                                 i + NR_DEFAULT_VPORTS);
        }
    }

    /* At this point, the MACsec SAs and associated rules have been installed.
       For egress, all (non-control) data packets will be encrypted regardless
       of must-secure/should-secure status.
       For ingress, MACsec packets will be decrypted. Non-MAcsec data packets
       will be passed in should-secure, dropped in must-secure.

       Data packets on a channel that do not match a TCAM rule will be handled
       by the default vPort of that channel (should-secure or must-secure).

       Control packets are passed unchanged in all cases. If they match a rule
       they will be passed by the actual MACsec SAs, if they do not match a
       rule, they will be passed by the dummy SAs on the default vPorts.
     */
    if (fIngress)
    {
        /* Untagged data packet on must-secure, drop */
        if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_MUST,
                                 Plaintext_Pkt, sizeof(Plaintext_Pkt),
                                 Plaintext_Pkt, sizeof(Plaintext_Pkt), true))
            goto error_exit;
        /* Untagged data packet on should-secure, default rule, pass */
        if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_SHOULD,
                                 Plaintext_Pkt, sizeof(Plaintext_Pkt),
                                 Plaintext_Pkt, sizeof(Plaintext_Pkt), false))
            goto error_exit;
        /* Untagged data packet on should-secure, match rule, pass */
        if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_SHOULD,
                                 Plaintext_Pkt_VLAN1,
                                 sizeof(Plaintext_Pkt_VLAN1),
                                 Plaintext_Pkt_VLAN1,
                                 sizeof(Plaintext_Pkt_VLAN1), false))
            goto error_exit;
        /* Untagged data packet on should-secure, match rule, pass */
        if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_SHOULD,
                                 Plaintext_Pkt_VLAN2,
                                 sizeof(Plaintext_Pkt_VLAN2),
                                 Plaintext_Pkt_VLAN2,
                                 sizeof(Plaintext_Pkt_VLAN2), false))
            goto error_exit;
        /* Macsec packets will be processed */
        if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_MUST,
                                 MACsec_Pkt, sizeof(MACsec_Pkt),
                                 Plaintext_Pkt, sizeof(Plaintext_Pkt), false))
            goto error_exit;
        if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_SHOULD,
                                 MACsec_Pkt_VLAN1, sizeof(MACsec_Pkt_VLAN1),
                                 Plaintext_Pkt_VLAN1,
                                 sizeof(Plaintext_Pkt_VLAN1), false))
            goto error_exit;
        if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_SHOULD,
                                 MACsec_Pkt_VLAN2, sizeof(MACsec_Pkt_VLAN2),
                                 Plaintext_Pkt_VLAN2,
                                 sizeof(Plaintext_Pkt_VLAN2), false))
            goto error_exit;
        /* MACsec packet on channel 1 without a VLAN tag,
           will not match a rule, will be bypassed by should-secure default. */
        if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_SHOULD,
                                 MACsec_Pkt, sizeof(MACsec_Pkt),
                                 MACsec_Pkt, sizeof(MACsec_Pkt), false))
            goto error_exit;
    }
    else
    {
        /* Packet will be encrypted */
        if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_MUST,
                                 Plaintext_Pkt, sizeof(Plaintext_Pkt),
                                 MACsec_Pkt, sizeof(MACsec_Pkt), false))
            goto error_exit;
        /* Data packet on channel 1, matches none of the rules, relies on
           default vPort (should-secure) */
        if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_SHOULD,
                         Plaintext_Pkt, sizeof(Plaintext_Pkt),
                         Plaintext_Pkt, sizeof(Plaintext_Pkt), false))
            goto error_exit;
        /* Packet will be encrypted */
        if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_SHOULD,
                         Plaintext_Pkt_VLAN1, sizeof(Plaintext_Pkt_VLAN1),
                         MACsec_Pkt_VLAN1, sizeof(MACsec_Pkt_VLAN1), false))
            goto error_exit;
        /* Packet will be encrypted */
        if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_SHOULD,
                         Plaintext_Pkt_VLAN2, sizeof(Plaintext_Pkt_VLAN2),
                         MACsec_Pkt_VLAN2, sizeof(MACsec_Pkt_VLAN2), false))
            goto error_exit;
    }
    /* control packets will be passed */
    if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_MUST,
                             Control_Pkt, sizeof(Control_Pkt),
                             Control_Pkt, sizeof(Control_Pkt), false))
        goto error_exit;
    if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_SHOULD,
                             Control_Pkt, sizeof(Control_Pkt),
                             Control_Pkt, sizeof(Control_Pkt), false))
        goto error_exit;
    if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_SHOULD,
                             Control_Pkt_VLAN1, sizeof(Control_Pkt_VLAN1),
                             Control_Pkt_VLAN1, sizeof(Control_Pkt_VLAN1),
                             false))
        goto error_exit;
    if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_SHOULD,
                             Control_Pkt_VLAN2, sizeof(Control_Pkt_VLAN2),
                             Control_Pkt_VLAN2, sizeof(Control_Pkt_VLAN2),
                             false))
        goto error_exit;

    /* Remove rules, SAs and vPorts associated with MACsec SAs. */
    for (i=0; i<NR_VPORTS; i++)
    {
        CfyE_Rc = CfyE_Rule_Disable(CFYE_DEVICE_ID, CfyE_RuleHandle[i], true);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: Failed, CfyE_Rule_Disable()=%d\n", CfyE_Rc);
            goto error_exit;
        }

        CfyE_Rc = CfyE_Rule_Remove(CFYE_DEVICE_ID, CfyE_RuleHandle[i]);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: Failed, CfyE_Rule_Remove()=%d\n", CfyE_Rc);
            goto error_exit;
        }
        CfyE_RuleHandle[i] = CfyE_RuleHandle_NULL;

        CfyE_Rc = CfyE_vPort_Remove(CFYE_DEVICE_ID,CfyE_vPortHandle[i]);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: Failed, CfyE_vPort_Remove()=%d\n", CfyE_Rc);
            goto error_exit;
        }
        CfyE_vPortHandle[i] = CfyE_vPortHandle_NULL;

        SecY_Rc = SecY_SA_Remove(SECY_DEVICE_ID, SecY_SAHandle[i]);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: Failed, SecY_SA_Remove()=%d\n", SecY_Rc);
            goto error_exit;
        }
        SecY_SAHandle[i] = SecY_SAHandle_NULL;

        if (fVerbose)
        {
            Log_FormattedMessage("DA_MACSEC:  vPort %d removed\n",i+2);
        }
    }

    /* At this point, the MACsec SAs and their rules have been removed.
       Packets are now processed the same way as before the MACsec SAs were
       installed, relying on default vPorts. */

    /* Packet processing */
    if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_MUST,
                             Plaintext_Pkt, sizeof(Plaintext_Pkt),
                             Plaintext_Pkt, sizeof(Plaintext_Pkt), true))
        goto error_exit;
    if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_SHOULD,
                             Plaintext_Pkt, sizeof(Plaintext_Pkt),
                             Plaintext_Pkt, sizeof(Plaintext_Pkt), false))
        goto error_exit;
    if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_SHOULD,
                             Plaintext_Pkt_VLAN1, sizeof(Plaintext_Pkt_VLAN1),
                             Plaintext_Pkt_VLAN1, sizeof(Plaintext_Pkt_VLAN1),
                             false))
        goto error_exit;
    if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_SHOULD,
                             Plaintext_Pkt_VLAN2, sizeof(Plaintext_Pkt_VLAN2),
                             Plaintext_Pkt_VLAN2, sizeof(Plaintext_Pkt_VLAN2),
                             false))
        goto error_exit;
    /* MACsec packet on channel 0 without a VLAN tag,
       will not match a rule, will be dropped by must-secure default. */
    if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_MUST,
                             MACsec_Pkt, sizeof(MACsec_Pkt),
                             MACsec_Pkt, sizeof(MACsec_Pkt), true))
            goto error_exit;
    /* MACsec packet on channel 1 without a VLAN tag,
       will not match a rule, will be bypassed by should-secure default. */
    if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_SHOULD,
                             MACsec_Pkt, sizeof(MACsec_Pkt),
                             MACsec_Pkt, sizeof(MACsec_Pkt), false))
            goto error_exit;
    if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_MUST,
                             Control_Pkt, sizeof(Control_Pkt),
                             Control_Pkt, sizeof(Control_Pkt), false))
        goto error_exit;
    if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_SHOULD,
                             Control_Pkt, sizeof(Control_Pkt),
                             Control_Pkt, sizeof(Control_Pkt), false))
        goto error_exit;
    if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_SHOULD,
                             Control_Pkt_VLAN1, sizeof(Control_Pkt_VLAN1),
                             Control_Pkt_VLAN1, sizeof(Control_Pkt_VLAN1),
                             false))
        goto error_exit;
    if (!da_secy_process_pkt(fIngress, fVerbose, CHANNEL_SHOULD,
                             Control_Pkt_VLAN2, sizeof(Control_Pkt_VLAN2),
                             Control_Pkt_VLAN2, sizeof(Control_Pkt_VLAN2),
                             false))
        goto error_exit;



    /* If we made it to here, consider this run a success. Any jump */
    /* to the error label below will skip "success = true" */
    fSuccess = true;

error_exit:

    /* Remove any and all resources */
    for (i=0; i<NR_VPORTS; i++)
    {
        if(!CfyE_RuleHandle_IsSame(CfyE_RuleHandle[i], CfyE_RuleHandle_NULL))
        {
            CfyE_Rule_Disable(CFYE_DEVICE_ID, CfyE_RuleHandle[i], true);
            CfyE_Rule_Remove(CFYE_DEVICE_ID, CfyE_RuleHandle[i]);
            CfyE_RuleHandle[i] = CfyE_RuleHandle_NULL;
        }
        if(!CfyE_vPortHandle_IsSame(CfyE_vPortHandle[i], CfyE_vPortHandle_NULL))
        {
            CfyE_vPort_Remove(CFYE_DEVICE_ID,CfyE_vPortHandle[i]);
            CfyE_vPortHandle[i] = CfyE_vPortHandle_NULL;
        }
        if(!SecY_SAHandle_IsSame(&SecY_SAHandle[i], &SecY_SAHandle_NULL))
        {
            SecY_SA_Remove(SECY_DEVICE_ID, SecY_SAHandle[i]);
            SecY_SAHandle[i] = SecY_SAHandle_NULL;
        }
    }
    for (i=0; i<NR_DEFAULT_VPORTS; i++)
    {
        if(!CfyE_vPortHandle_IsSame(CfyE_vPortHandleDefault[i],
                                    CfyE_vPortHandle_NULL))
        {
            CfyE_vPort_Remove(CFYE_DEVICE_ID,CfyE_vPortHandleDefault[i]);
            CfyE_vPortHandleDefault[i] = CfyE_vPortHandle_NULL;
        }
        if(!SecY_SAHandle_IsSame(&SecY_SAHandleDefault[i],
                                 &SecY_SAHandle_NULL))
        {
            SecY_SA_Remove(SECY_DEVICE_ID, SecY_SAHandleDefault[i]);
            SecY_SAHandleDefault[i] = SecY_SAHandle_NULL;
        }
    }

    SecY_Device_Uninit(SECY_DEVICE_ID);
    CfyE_Device_Uninit(CFYE_DEVICE_ID);

    return fSuccess;
}

#endif /* DA_MACSEC_USE_CFYE */

/* end of file da_secy_cfye_macsec.c */
