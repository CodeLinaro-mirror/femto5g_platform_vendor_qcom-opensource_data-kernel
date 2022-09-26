 /* da_secy_cfye_should_secure.c
 *
 * Demo application, show effect of per-channel should-secure and must-secure.
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
#define CONTROL_ETYPE 0x888e

/*----------------------------------------------------------------------------
 * Local variables
 */


/*----------------------------------------------------------------------------
 * da_secy_cfye_should_secure
 */
bool
da_secy_cfye_should_secure(
        bool fVerbose,
        bool fDropControl,
        bool fIngress)
{
    unsigned int IsControl;
    unsigned int ch;
    unsigned int ChannelShould = 1;
    unsigned int PktByteCount;
    CfyE_Status_t CfyE_Rc;

    SecY_Status_t SecY_Rc;

    unsigned int ExpectedPktByteCount;
    uint8_t * InputPktHostAddress = NULL;
    uint8_t * ProcessedPktHostAddress = NULL;
    uint8_t * ExpectedPktHostAddress = NULL;
    bool fSuccess = false;


    Log_FormattedMessage("DA_MACSEC: Starting test for %sgress\n",
                         fIngress ? "in" : "e");

    {
        CfyE_Init_t Settings;

        Log_FormattedMessage("DA_MACSEC: Initializing CfyE\n");

        ZEROINIT(Settings);
        Settings.fDropControlPkts = fDropControl;

        CfyE_Rc = CfyE_Device_Init(SECY_DEVICE_ID,
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

    /* CfyE_Device_Limits */
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

        Log_FormattedMessage("CfyE_Diag_Device version=%d.%d.%d\n"
                             "Channels=%d\nvPorts=%d\nRules=%d\n",
                             Device_Limits.major_version,
                             Device_Limits.minor_version,
                             Device_Limits.patch_level,
                             Device_Limits.channel_count,
                             Device_Limits.vport_count,
                             Device_Limits.rule_count);

        if (Device_Limits.major_version >= 3)
        {
            Log_FormattedMessage("Test with per-channel should-secure supported on this HW\n");
        }
        else
        {
            Log_FormattedMessage("Test with per-channel should-secure is not\n"
                                 "supported on this HW version, skipping.\n");
                CfyE_Device_Uninit(CFYE_DEVICE_ID);
                return true;
        }
    }

    {
        SecY_Settings_t Settings;

        Log_FormattedMessage("DA_MACSEC: Initializing SecY\n");

        ZEROINIT(Settings);

        Settings.fDropControlPkts = fDropControl;
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

    /* Iniitialize control packet parser and CfyE should-secure */
    {
        CfyE_Device_t DeviceParams;
        CfyE_ControlPacket_t CP;
        CfyE_Device_Exceptions_t DeviceExceptions;
        CfyE_Device_Control_t DeviceControl;
        ZEROINIT(DeviceExceptions);
        ZEROINIT(DeviceParams);
        ZEROINIT(DeviceControl);
        ZEROINIT(CP);
        CP.MAC_DA_ET_Rules[0].EtherType = CONTROL_ETYPE;
        CP.CPMatchEnableMask = BIT_8; /* Enable Etype[0] matching */

        DeviceControl.fLowLatencyBypass = false;
            DeviceControl.Exceptions_p = &DeviceExceptions;
            DeviceParams.Control_p = &DeviceControl;
            DeviceParams.CP_p = &CP;

            for (ch = 0; ch < 2; ch++)
            {
                if (ch== ChannelShould && !fDropControl)
                {
                    /* Configure for should-secure only when entire device
                       is not configured to drop control packets */
                    DeviceExceptions.fShouldSecure = true;
                }
                CfyE_Rc = CfyE_Device_Update(CFYE_DEVICE_ID, ch, &DeviceParams);
                if (CfyE_Rc != CFYE_STATUS_OK)
                {
                    LOG_CRIT("DA_MACSEC: CfyE device could not be updated, error=%d\n",
                             CfyE_Rc);
                    goto error_exit;
                }
            }
    }

    /* Configure SecY channels for must-secure and should-secure. */
    {
        SecY_Channel_t Channel;
        for (ch = 0; ch < 2; ch++)
        {
            SecY_Rc = SecY_Channel_Config_Get(SECY_DEVICE_ID, ch, &Channel);
            if (SecY_Rc != SECY_STATUS_OK)
            {
                LOG_CRIT("DA_MACSEC: SecY_Channel_Config_Get, error=%d\n",
                         SecY_Rc);
                goto error_exit;
            }

            if (ch == ChannelShould && !fDropControl)
            {
                /* Configure for should-secure only when entire device
                   is not configured to drop control packets */
                Channel.fShouldSecure = true;
            }
            else
            {
                Channel.fShouldSecure = false;
            }
            SecY_Rc = SecY_Channel_Config_Update(SECY_DEVICE_ID, ch,  &Channel);
            if (SecY_Rc != SECY_STATUS_OK)
            {
                LOG_CRIT("DA_MACSEC: SecY_Channel_Config_Set, error=%d\n",
                         SecY_Rc);
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

    /* At this point the Engine is ready to accept packets and
     * perform classification and processing autonomously.*/
    if (fVerbose)
    {
        Log_FormattedMessage("DA_MACSEC: Ready to process packets\n");
    }

    /* The main packet processing loop */
    for (ch = 0; ch < 2; ch++)
    {
        for (IsControl = 0; IsControl < 2; IsControl++)
        {
            PktIO_Packet_Status_In_t PktStatusIn;
            PktIO_Packet_Status_Out_t PktStatusOut;
            int RetCode;
            unsigned int ByteCount;
            bool fDrop;
            PktByteCount = 60;

            /* Generate a valid Ethernet frame of the desired size for the test. */
            da_macsec_gen_frame(InputPktHostAddress, PktByteCount);
            if (IsControl)
            {
                /* We have a control packet, so change ether type */
                    da_macsec_put16(InputPktHostAddress, 12, CONTROL_ETYPE);
            }

            if(fDropControl)
            {
                fDrop = true;
                }
            else if (IsControl)
            {
                fDrop = false;
            }
            else if (ch == ChannelShould)
            {
                fDrop = false;
            }
            else
            {
                fDrop = true;
            }

            if (fVerbose)
            {
                LOG_CRIT("DA_MACSEC: DropControl=%d IsControl=%d"
                             " ShouldSecure=%d Expect drop=%d\n",
                         fDropControl,
                         IsControl,
                         ch==ChannelShould && !fDropControl,
                         fDrop);
            }

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
            RetCode = PktIO_Packet_Put(InputPktHostAddress,
                                       PktByteCount,
                                       &PktStatusIn,
                                       ch,
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
                                  ch) == 0 &&
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
                                     ch,
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


    SecY_Device_Uninit(SECY_DEVICE_ID);
    CfyE_Device_Uninit(SECY_DEVICE_ID);

    return fSuccess;
}

#endif /* DA_MACSEC_USE_CFYE */

/* end of file da_secy_cfye_bypass_drop.c */
