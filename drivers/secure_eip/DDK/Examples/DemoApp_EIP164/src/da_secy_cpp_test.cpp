/* da_xtsecy_cpp_test.cpp
 *
 * Demo Application for c plus plus test of c driver lib
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

extern "C" {
#include "api_secy.h"
#include "basic_defs.h"
#include "clib.h"
#define LOG_SEVERITY_MAX LOG_SEVERITY_INFO
#include "log.h"
/* Packet I/O API */
#include "api_pktio.h"
#include "da_internal.h"
#include "da_warmboot.h"
#ifdef DA_MACSEC_USERMODE
/* Driver Init API */
#include "api_driver164_init.h"
#endif
}

#include <iostream>

/* MACsec key */
static uint8_t K1[] = {
    0xad, 0x7a, 0x2b, 0xd0, 0x3e, 0xac, 0x83, 0x5a,
    0x6f, 0x62, 0x0f, 0xdc, 0xb5, 0x06, 0xb3, 0x45,
};

/* MACsec SCI */
static uint8_t SCI1[] = {
    0x12, 0x15, 0x35, 0x24, 0xc0, 0x89, 0x5e, 0x81,
};


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
};
#endif

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
};
#endif

/* Basic SA transform source packet */
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

/* Basic SA transform destination packet */
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

static bool
cplusplus_test( bool fIngress, bool fVerbose);

static bool
cplusplus_test( bool fIngress, bool fVerbose) {

    SecY_Settings_t Settings;
    SecY_Status_t SecY_Rc;
    bool fSuccess = false;
    SecY_SAHandle_t SecY_SAHandle = { 0 };
    uint8_t *InputPktHostAddress = new uint8_t[PKT_BUFFER_BYTE_COUNT];
    uint8_t *ProcessedPktHostAddress = new uint8_t[PKT_BUFFER_BYTE_COUNT];
    uint8_t *ExpectedPktHostAddress = new uint8_t[PKT_BUFFER_BYTE_COUNT];

    std::cout << "DA_MACSEC: Initializing SecY\n";
    ZEROINIT(Settings);

    SecY_Rc = SecY_Device_Init(SECY_DEVICE_ID,
                               fIngress ? SECY_ROLE_INGRESS :
                               SECY_ROLE_EGRESS,
                               &Settings);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        LOG_CRIT("DA_MACSEC: SecY could not be initialized, error=%d\n",SecY_Rc);
        goto error_exit_init;
    }
    if(fVerbose)
    {
        std::cout << "DA_MACSEC: SecY is initialized successfully\n";
        }
    /* Install SA with transform record */
    {
        SecY_SA_t SA_Params;
        unsigned int SAWordCount;

        ZEROINIT(SA_Params);

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
        SecY_Rc = SecY_SA_Add(SECY_DEVICE_ID,
                              0,
                              &SecY_SAHandle,
                              &SA_Params);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: Failed, SecY_SA_Add()=%d\n", SecY_Rc);
            goto error_exit_init;
        }

        if (fVerbose)
        {
            Log_FormattedMessage("DA_MACSEC: Transform 32-bit word count %d\n",
                                 SA_Params.SA_WordCount);
            Log_HexDump("DA_MACSEC: Transform data",
                        0,
                        (uint8_t*)SA_Params.TransformRecord_p,
                        SA_Params.SA_WordCount * sizeof (uint32_t));
        }

        if (SA_Params.TransformRecord_p)
        {
            da_macsec_free(SA_Params.TransformRecord_p);
        }

        if (fVerbose)
        {
            Log_FormattedMessage("DA_MACSEC: "
                                        "SA with Transform Record added\n");
        }
    }

    {
        PktIO_Packet_Status_In_t PktStatusIn;
        PktIO_Packet_Status_Out_t PktStatusOut;
        unsigned int ByteCount;
        int RetCode;
        unsigned int input_len,exp_len;
        if (fIngress)
        {
            input_len = sizeof MACsec_Pkt;
            exp_len = sizeof Plaintext_Pkt;
            memcpy(InputPktHostAddress, MACsec_Pkt, input_len);
            memcpy(ExpectedPktHostAddress, Plaintext_Pkt, exp_len);
        }
        else
        {
            input_len = sizeof Plaintext_Pkt;
            exp_len = sizeof MACsec_Pkt;
            memcpy(InputPktHostAddress, Plaintext_Pkt, input_len);
            memcpy(ExpectedPktHostAddress, MACsec_Pkt, exp_len);
        }

        if (fVerbose)
        {
            Log_FormattedMessage("DA_MACSEC: "
                                 "Process input packet of size %d\n",
                                 input_len);
            Log_HexDump("Input packet",
                        0,
                        InputPktHostAddress,
                        input_len);
        }
        /* Fill in the status data structure */
        ZEROINIT(PktStatusIn);
        PktStatusIn.vPort        = 0;
        PktStatusIn.SecTAGOffset = 12;
        RetCode = PktIO_Packet_Put(InputPktHostAddress,
                                   input_len,
                                   &PktStatusIn,
                                   0,
                                   fIngress ? PKTIO_PACKET_DIRECTION_INGRESS :
                                   PKTIO_PACKET_DIRECTION_EGRESS);
        if (RetCode != 0)
        {
            LOG_CRIT("DA_MACSEC: PktIO_Packet_Put error %d\n", RetCode);
            goto error_exit;
        }
        /* Fill in the status data structure */
        ZEROINIT(PktStatusOut);

        /* Receive the processed packet */
        if (da_macsec_get_one(fIngress,
                              ProcessedPktHostAddress,
                              &ByteCount,
                              &PktStatusOut,
                              0) == 0 &&
            PktStatusOut.PacketStatusMask == 0)
        {
            LOG_CRIT("DA_MACSEC: Error obtaining result packet\n");
            goto error_exit;
        }

        if (fVerbose)
        {
            Log_FormattedMessage("DA_MACSEC: PktIO_Packet_Get Size/"
                                 "StatusMask/RuleIndex: %d/0x%X\n",
                                 ByteCount,
                                 PktStatusOut.PacketStatusMask);
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
            goto error_exit;
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
            goto error_exit;
        }
    }
    fSuccess = true;
error_exit:
    /* Remove SA */
    SecY_Rc = SecY_SA_Remove(SECY_DEVICE_ID,
                             SecY_SAHandle);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        LOG_CRIT("DA_MACSEC: Failed, SecY_SA_Remove()=%d\n", SecY_Rc);
        fSuccess = false;
    }

    SecY_Device_Uninit(SECY_DEVICE_ID);
error_exit_init:
    delete[] InputPktHostAddress;
    delete[] ProcessedPktHostAddress;
    delete[] ExpectedPktHostAddress;
    return fSuccess;
}


int main()
{
    bool fSuccess;
#ifdef DA_MACSEC_USE_WARMBOOT
    da_macsec_warmboot_init();
#endif
    Driver164_Init();
    PktIO_Init();
#ifdef DA_MACSEC_MODE_EGRESS
    {
        /* Run the tests for the egress device configuration */
        fSuccess = cplusplus_test(false, true);
        if (fSuccess)
            std::cout << "C++ Test PASSED\n";
        else
            std::cout << "C++ Test FAILED\n";
    }
#endif
#ifdef DA_MACSEC_MODE_INGRESS
    {
        /* Run the tests for the egress device configuration */
        fSuccess = cplusplus_test(true, true);
        if (fSuccess)
            std::cout << "C++ Test PASSED\n";
        else
            std::cout << "C++ Test FAILED\n";
    }
#endif

    Driver164_Exit();
#ifdef DA_MACSEC_USE_WARMBOOT
    da_macsec_warmboot_uninit();
#endif
}
