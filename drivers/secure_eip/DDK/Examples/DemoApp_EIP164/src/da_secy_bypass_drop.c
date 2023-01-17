 /* da_secy_bypass_drop.c
 *
 * Demo application. bypass and drop tests using SecY API only.
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
 * MaskUnusedChBits
 *
 * Masks the Most Significant Channel bits.
 */

static void
MaskUnusedChBits(
    SecY_Ch_Mask_t *const ChMask_p,
    const uint16_t ChannelCount)
{
    uint8_t i, k = 0;
    uint32_t val = 0;

    if (0 == ChannelCount) return;

    k = (ChannelCount + 31) / 32;

    /** Get the Channel Mask representing the higher channels */
    val = ChMask_p->ch_bitmask[k - 1];

    ChMask_p->ch_bitmask[k - 1] = MASK_UNUSED_CH_BITS(ChannelCount, val);

    for (i = k; i < SECY_CHANNEL_WORDS; i++)
        ChMask_p->ch_bitmask[i] = 0;
}


/*----------------------------------------------------------------------------
 * da_secy_bypass_drop
 */
bool
da_secy_bypass_drop(
        bool fVerbose,
        bool fDrop,
        bool fIngress,
        unsigned int MinPktSize,
        unsigned int MaxPktSize,
        unsigned int SizeStep)
{
    unsigned int vPort = 0;
    unsigned int Channel = 0;
    unsigned int PktByteCount;

    SecY_Status_t SecY_Rc;

    unsigned int ExpectedPktByteCount;
    uint8_t * InputPktHostAddress = NULL;
    uint8_t * ProcessedPktHostAddress = NULL;
    uint8_t * ExpectedPktHostAddress = NULL;
    SecY_Channel_t *ChannelParams;
    bool fSuccess = false;
    SecY_Ch_Mask_t ChannelMask;

    if (MinPktSize > PKT_BUFFER_BYTE_COUNT ||
        MaxPktSize > PKT_BUFFER_BYTE_COUNT)
    {
        return false;
    }

    Log_FormattedMessage("DA_MACSEC: Starting test for %sgress\n",
                         fIngress ? "in" : "e");

    if (fVerbose)
    {
        Log_FormattedMessage("DA_MACSEC: Perform %s\n",
                             fDrop ? "Drop" : "Bypass");
    }

    {
        SecY_Settings_t Settings;

        Log_FormattedMessage("DA_MACSEC: Initializing SecY\n");

        ZEROINIT(Settings);

        if (fDrop)
        {
#ifdef DA_MACSEC_MODE_EGRESS
            Settings.DropBypass.DropType = SECY_SA_DROP_INTERNAL;
            /* Note: SECY_SA_DROP_CRC_ERROR could be used too but then */
            /*       the packet data may be transmited */
#endif
#ifdef DA_MACSEC_MODE_INGRESS
            Settings.DropBypass.DropType = SECY_SA_DROP_CRC_ERROR;
            /* Note: SECY_SA_DROP_PKT_ERROR can be used too but then */
            /*       the packet data may be modified by the testbench */
#endif
        }
        else
        {
            Settings.DropBypass.fBypass = true;
        }

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

    /* Disable unused counter types (for coverage) */
    {
        SecY_Device_Params_t DeviceParams, DeviceParams2;
        SecY_EOPConf_t EOPParams, EOPParams2;
        SecY_ECCConf_t ECCParams, ECCParams2;
        SecY_ChannelConf_t ChannelConf;
        SecY_Statistics_Control_t StatsParams, StatsParams2;
        unsigned int i;
        unsigned int MaxSecYChannels = 0;

        SecY_Rc = SecY_Device_Limits(SECY_DEVICE_ID,
                                     &MaxSecYChannels,
                                     NULL,
                                     NULL,
                                     NULL);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("SecY_Device_Limits returned error %d\n",SecY_Rc);
            return SecY_Rc;
        }

        LOG_CRIT("DA_MACSEC: Maximum Channels supported: %u\n", MaxSecYChannels);

        ChannelParams = da_macsec_malloc(sizeof(SecY_Channel_t) * MaxSecYChannels);

        if (ChannelParams == NULL)
            goto error_exit;

        memset(ChannelParams, 0, sizeof(SecY_Channel_t) * MaxSecYChannels);

        ZEROINIT(DeviceParams);
        ZEROINIT(DeviceParams2);
        ZEROINIT(ChannelConf);
        ZEROINIT(StatsParams);

        EOPParams.EOPTimeoutVal = 10000;

        for (i = 0; i < ((MaxSecYChannels + 31) / 32); i++)
            EOPParams.EOPTimeoutCtrl.ch_bitmask[i] = 0xffffffff;

        MaskUnusedChBits(&EOPParams.EOPTimeoutCtrl, MaxSecYChannels);

        DeviceParams.EOPConf_p = &EOPParams;

        ECCParams.ECCCorrectableThr = 1;
        ECCParams.ECCUncorrectableThr = 1;
        DeviceParams.ECCConf_p = &ECCParams;

        /* Enable reset on read */
        StatsParams.fAutoStatCntrsReset = true;

        /* Disable the SA, TCAM and RxCAM counters */
        StatsParams.CountIncDisCtrl = SECY_SA_COUNT_INC_DIS |
                                      SECY_RXCAM_COUNT_INC_DIS;

        DeviceParams.StatControl_p = &StatsParams;

        SecY_Rc = SecY_Device_Update(SECY_DEVICE_ID,
                                     &DeviceParams);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: Failed, SecY_Device_Update()=%d\n",
                            SecY_Rc);
            goto error_exit;
        }

        DeviceParams2.ChConf_p = &ChannelConf;
        ChannelConf.Params.Channel_p = ChannelParams;
        DeviceParams2.StatControl_p = &StatsParams2;
        DeviceParams2.EOPConf_p = &EOPParams2;
        DeviceParams2.ECCConf_p = &ECCParams2;

        SecY_Rc = SecY_Device_Config_Get(SECY_DEVICE_ID,
                                          &DeviceParams2);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("DA_MACSEC: Failed, SecY_Device_Config_Get()=%d\n",
                            SecY_Rc);
            goto error_exit;
        }

        for (i = 0; i < ((MaxSecYChannels + 31) / 32); i++)
            EOPParams.EOPTimeoutCtrl.ch_bitmask[i] = 0xffffffff;

        MaskUnusedChBits(&EOPParams.EOPTimeoutCtrl, MaxSecYChannels);

        /* EOPTimeoutCtrl has as many bits as there are channels. */
        Log_FormattedMessage("DA_MACSEC: SecY Device Params read: EOPTimeoutVal=%u\n"
                             "\t ECCCorrectable=%d ECCUncorrectable=%d autoreset=%d incdis=0x%x #chans=%d\n",
                             EOPParams2.EOPTimeoutVal,
                             ECCParams2.ECCCorrectableThr,
                             ECCParams2.ECCUncorrectableThr,
                             StatsParams2.fAutoStatCntrsReset,
                             StatsParams2.CountIncDisCtrl,
                             ChannelConf.Params.ChannelCount);

        for (i = 0; i < ((ChannelConf.Params.ChannelCount + 31) / 32); i++)
            Log_FormattedMessage("DA_MACSEC: SecY Device Params read - Channel Bank: %u EOPTimeoutCtrl=0x%x\n",
                                 i, EOPParams2.EOPTimeoutCtrl.ch_bitmask[i]);

        if (EOPParams2.EOPTimeoutVal != EOPParams.EOPTimeoutVal ||
            ECCParams2.ECCCorrectableThr != ECCParams.ECCCorrectableThr ||
            ECCParams2.ECCUncorrectableThr != ECCParams.ECCUncorrectableThr ||
            StatsParams2.fAutoStatCntrsReset != StatsParams.fAutoStatCntrsReset ||
            StatsParams2.CountIncDisCtrl!= StatsParams.CountIncDisCtrl ||
            ChannelConf.Params.ChannelCount == 0)
        {
            Log_FormattedMessage("Received Data - DA_MACSEC: SecY Device Params read: EOPTimeoutVal=%u\n"
                                 "\t ECCCorrectable=%d ECCUncorrectable=%d autoreset=%d incdis=0x%x #chans=%d\n",
                                 EOPParams2.EOPTimeoutVal,
                                 ECCParams2.ECCCorrectableThr,
                                 ECCParams2.ECCUncorrectableThr,
                                 StatsParams2.fAutoStatCntrsReset,
                                 StatsParams2.CountIncDisCtrl,
                                 ChannelConf.Params.ChannelCount);

            Log_FormattedMessage("Expected Data - DA_MACSEC: SecY Device Params read: EOPTimeoutVal=%u\n"
                                 "\t ECCCorrectable=%d ECCUncorrectable=%d autoreset=%d incdis=0x%x #chans=%d\n",
                                 EOPParams.EOPTimeoutVal,
                                 ECCParams.ECCCorrectableThr,
                                 ECCParams.ECCUncorrectableThr,
                                 StatsParams.fAutoStatCntrsReset,
                                 StatsParams.CountIncDisCtrl,
                                 ChannelConf.Params.ChannelCount);

            LOG_CRIT("DA_MACSEC: Failed, SecY_Device_Config_Get() did not return expected data\n");
            goto error_exit;
        }

        for (i = 0; i < ((ChannelConf.Params.ChannelCount + 31) / 32); i++)
        {
            if (EOPParams2.EOPTimeoutCtrl.ch_bitmask[i] != EOPParams.EOPTimeoutCtrl.ch_bitmask[i])
            {
                Log_FormattedMessage("Received Data - DA_MACSEC: EOPTimeoutCtrl=0x%x\n",
                                     EOPParams2.EOPTimeoutCtrl.ch_bitmask[i]);

                Log_FormattedMessage("Expected Data - DA_MACSEC: EOPTimeoutCtrl=0x%x\n",
                                     EOPParams.EOPTimeoutCtrl.ch_bitmask[i]);

                LOG_CRIT("DA_MACSEC: Failed, SecY_Device_Config_Get() did not return expected data\n");
                goto error_exit;
            }
        }

        for (i = 0; i < (ChannelConf.Params.ChannelCount + 31) / 32; i++)
        {
            Log_FormattedMessage("DA_MACSEC: Channel config for channel %d\n"
                                 "\t bypass=%d SecTAG Etype=0x%04x egress Etype=0x%04x\n",
                                 ChannelParams[i].ChannelId,
                                 ChannelParams[i].fLowLatencyBypass,
                                 ChannelParams[i].RuleSecTAG.EtherType,
                                 ChannelParams[i].EtherType);
            if ( (fIngress && ChannelParams[i].RuleSecTAG.EtherType != 0x88e5) ||
                 (!fIngress && ChannelParams[i].EtherType != 0x88e5) ||
                 i != ChannelParams[i].ChannelId)
            {
                LOG_CRIT("DA_MACSEC: Failed, SecY_Device_Config_Read() did not return expected per-channel data\n");
                goto error_exit;
            }
        }
    }

    if (fVerbose)
    {
        Log_FormattedMessage("DA_MACSEC: Preparing packet(s)\n");
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

    /* Insert SOP+EOP on channel 0 and verify that a dummy packet
       is available. This is not required for drop and/or bypass
       packets, but just a test to cover this functionality. */
    ZEROINIT(ChannelMask);
    ChannelMask.ch_bitmask[0] = 0x1;

    SecY_Rc = SecY_Device_InsertSOP(SECY_DEVICE_ID, &ChannelMask);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        LOG_CRIT("DA_MACSEC: Failed, inser SOP\n");
        goto error_exit;
    }

    SecY_Rc = SecY_Device_InsertEOP(SECY_DEVICE_ID, &ChannelMask);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        LOG_CRIT("DA_MACSEC: Failed, inser EOP\n");
        goto error_exit;
    }
    if (fVerbose)
    {
        Log_FormattedMessage("DA_MACSEC: Dummy SOP/EOP sent\n");
    }

    /* Receive the dummy packet that resulted from SOP+EOP */
    {
        PktIO_Packet_Status_Out_t PktStatusOut;
        unsigned int ByteCount;

        if (da_macsec_get_one(fIngress,
                              ProcessedPktHostAddress,
                              &ByteCount,
                              &PktStatusOut,
                              Channel) == 0 &&
            PktStatusOut.PacketStatusMask == 0)
        {
            LOG_CRIT("DA_MACSEC: Error obtaining dummy packet\n");
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
            Log_FormattedMessage("DA_MACSEC: Dummy packet received\n");
        }
    }

    /* At this point the Engine is ready to accept packets and
     * perform classification and processing autonomously.*/
    if (fVerbose)
    {
        Log_FormattedMessage("DA_MACSEC: Ready to process packets\n");
    }

    /* The main packet processing loop */
    for(PktByteCount = MinPktSize;
        PktByteCount <= MaxPktSize;
        PktByteCount += SizeStep)
    {
        PktIO_Packet_Status_In_t PktStatusIn;
        PktIO_Packet_Status_Out_t PktStatusOut;
        int RetCode;
        unsigned int ByteCount;

        /* Generate a valid Ethernet frame of the desired size for the test. */
        da_macsec_gen_frame(InputPktHostAddress, PktByteCount);

        if (fVerbose)
        {
            Log_FormattedMessage("DA_MACSEC: Process input packet of size %d\n",
                                 PktByteCount);
            Log_HexDump("Input packet", 0, InputPktHostAddress, PktByteCount);
        }

        /* In bypass test the expected packet is identical to the input packet */
        memcpy(ExpectedPktHostAddress, InputPktHostAddress, PktByteCount);
        ExpectedPktByteCount = PktByteCount;

        /* Fill in the packet status data structure */
        ZEROINIT(PktStatusIn);

        /* Set vPort number */
        PktStatusIn.vPort        = vPort;
        PktStatusIn.SecTAGOffset = 12; /* 12 bytes for typical Ethernet frame */

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
        if (!fDrop && ByteCount != ExpectedPktByteCount)
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

        if (!fDrop && memcmp(ProcessedPktHostAddress,
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

        if (fDrop &&
            ((PktStatusOut.PacketStatusMask & PKTIO_PACKET_CRC_ERROR) == 0))
        {
            LOG_CRIT("DA_MACSEC: Failed, Drop flow CRC error check, "
                     "output packet status 0x%x\n",
                     PktStatusOut.PacketStatusMask);
            goto error_exit;
        }

#ifdef DA_MACSEC_MODE_INGRESS
        if (fIngress)
        {
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

                if ((IfcStats.InOctetsUncontrolled.Lo != 60) ||
                    (IfcStats.InPktsUnicastUncontrolled.Lo != 0) ||
                    (IfcStats.InPktsMulticastUncontrolled.Lo != 1) ||
                    (IfcStats.InPktsBroadcastUncontrolled.Lo != 0) ||
                    ( fDrop && IfcStats.InOctetsControlled.Lo != 0) ||
                    (!fDrop && IfcStats.InOctetsControlled.Lo != 60) ||
                    (IfcStats.InPktsUnicastControlled.Lo != 0) ||
                    (IfcStats.InPktsMulticastControlled.Lo != 0) ||
                    (IfcStats.InPktsBroadcastControlled.Lo != 0))
                {
                    LOG_CRIT("DA_MACSEC: Failed, IFC/IFC1 statistics check:\n"
                             "\tInOctetsUncontrolled=%u, expected 60\n"
                             "\tInPktsUnicastUncontrolled=%u, expected 0\n"
                             "\tInPktsMulticastUncontrolled=%u, expected 1\n"
                             "\tInPktsBroadcastUncontrolled=%u, expected 0\n"
                             "\tInOctetsControlled=%u, expected %u\n"
                             "\tInPktsUnicastControlled=%u, expected 0\n"
                             "\tInPktsMulticastControlled=%u, expected 0\n"
                             "\tInPktsBroadcastControlled=%u, expected 0\n",
                             IfcStats.InOctetsUncontrolled.Lo,
                             IfcStats.InPktsUnicastUncontrolled.Lo,
                             IfcStats.InPktsMulticastUncontrolled.Lo,
                             IfcStats.InPktsBroadcastUncontrolled.Lo,
                             IfcStats.InOctetsControlled.Lo,
                             fDrop ? 0 : 60,
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
                        "\tControlled Packets Counter:          %u\n"
                        "\tUntagged Packets Counter:            %u\n",
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

                if ((!fDrop && IfcStats.OutOctetsCommon.Lo != 60) ||
                    ( fDrop && IfcStats.OutOctetsCommon.Lo != 0) ||
                    (IfcStats.OutOctetsUncontrolled.Lo != 60) ||
                    (IfcStats.OutPktsUnicastUncontrolled.Lo != 0) ||
                    (IfcStats.OutPktsMulticastUncontrolled.Lo != 1) ||
                    (IfcStats.OutPktsBroadcastUncontrolled.Lo != 0) ||
                    (IfcStats.OutOctetsControlled.Lo != 0) ||
                    (IfcStats.OutPktsUnicastControlled.Lo != 0) ||
                    (IfcStats.OutPktsMulticastControlled.Lo != 0) ||
                    (IfcStats.OutPktsBroadcastControlled.Lo != 0))
                {
                    LOG_CRIT("DA_MACSEC: Failed, IFC/IFC1 statistics check:\n"
                             "\tOutOctetsCommon=%u, expected %u\n"
                             "\tOutOctetsUncontrolled=%u, expected 60\n"
                             "\tOutPktsUnicastUncontrolled=%u, expected 0\n"
                             "\tOutPktsMulticastUncontrolled=%u, expected 1\n"
                             "\tOutPktsBroadcastUncontrolled=%u, expected 0\n"
                             "\tOutOctetsControlled=%u, expected 0\n"
                             "\tOutPktsUnicastControlled=%u, expected 0\n"
                             "\tOutPktsMulticastControlled=%u, expected 0\n"
                             "\tOutPktsBroadcastControlled=%u, expected 0\n",
                             IfcStats.OutOctetsCommon.Lo,
                             fDrop ? 0 : 60,
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


    if (ChannelParams)
    {
        da_macsec_free(ChannelParams);
    }

    SecY_Device_Uninit(SECY_DEVICE_ID);

    return fSuccess;
}

/* end of file da_secy_bypass_drop.c */
