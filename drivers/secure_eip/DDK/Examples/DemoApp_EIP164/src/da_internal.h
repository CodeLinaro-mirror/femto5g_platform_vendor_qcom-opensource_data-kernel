/* da_internal.h
 *
 * Demo Application for MACsec.
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

#ifndef DA_INTERNAL_H_
#define DA_INTERNAL_H_

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
#include "api_cfye.h"
#include "sa_builder_macsec.h"

#include "basic_defs.h"
#include "clib.h"
#include "log.h"

/* Packet I/O API */
#include "api_pktio.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

#ifdef DA_MACSEC_USERMODE
#define da_macsec_malloc(s) malloc(s)
#define da_macsec_free(s)   free(s)
#define da_macsec_usleep(s) usleep(s)
#else
#define EXPORT_SYMTAB

#define da_macsec_malloc(s) kmalloc(s, GFP_KERNEL)
#define da_macsec_free(s)   kfree(s)
#define da_macsec_usleep(s) udelay(s)
#endif

#ifdef DA_MACSEC_MODE_EGRESS
#define SECY_DEVICE_ID       1
#define CFYE_DEVICE_ID       1
#endif

#ifdef DA_MACSEC_MODE_INGRESS
#undef SECY_DEVICE_ID
#define SECY_DEVICE_ID       0
#undef CFYE_DEVICE_ID
#define CFYE_DEVICE_ID       0
#endif

/* Ethernet frame length */
#define MIN_PKT_BYTE_COUNT      60
#define MAX_PKT_BYTE_COUNT      1500
#define PKT_BUFFER_BYTE_COUNT   (MAX_PKT_BYTE_COUNT + 128)


/*----------------------------------------------------------------------------
 * Definitions and macros
 */
#define HIGH_CH_BIT(ChannelCount)  (1 << ((ChannelCount + 31) % 32))
#define PREP_MASK(ChannelCount)   ((HIGH_CH_BIT(ChannelCount))| (HIGH_CH_BIT(ChannelCount) - 1))
#define MASK_UNUSED_CH_BITS(ChannelCount, ChannelMask) (PREP_MASK(ChannelCount) & (ChannelMask))

/* Parameters that specify SA creation. */
typedef struct
{
    SABuilder_Direction_t direction;
    SABuilder_Operation_t operation;
    uint32_t flags;
    uint8_t AN;
    uint8_t *Key_p;
    unsigned int KeyByteCount;
    uint8_t *SCI_p;
    uint8_t *SSCI_p;
    uint8_t *Salt_p;
    uint32_t SeqNumLo;
    uint32_t SeqNumHi;
    uint32_t SeqMask;
#if defined(DA_IPSEC_ENABLE)
    uint32_t SPI;
#endif
} da_sa_params_t;



/*----------------------------------------------------------------------------
 * da_macsec_discard_const
 *
 * Discard const qualifier from pointer.
 */
static inline void *
da_macsec_discard_const(
        const void * Ptr_p)
{
    union
    {
        const void * c_p;
        void * n_p;
    } Conversion;

    Conversion.c_p = Ptr_p;
    return Conversion.n_p;
}


/*----------------------------------------------------------------------------
 * da_macsec_put16
 *
 * Write 16-bit value to byte array in network byte order.
 */
void
da_macsec_put16(
        uint8_t * p,
        unsigned int offs,
        uint16_t val);


/*----------------------------------------------------------------------------
 * da_macsec_gen_frame
 *
 * Generate a valid Ethernet frame of the specified length
 * (must be at least MIN_PKT_BYTE_COUNT octets).
 */
void
da_macsec_gen_frame(
        uint8_t * Packet_p,
        unsigned int PacketByteCount);

/*----------------------------------------------------------------------------
 * da_macsec_get_one
 *
 * Attempt to receive a single packet.
 * Try this a configurable number of times. When a packet is received,
 * check its status.
 *
 * Buffer_p (output)
 *      Pointer to memory location where the processed packet will be stored.
 *
 * ByteCount_p (output)
 *      Pointer to memory location where the processed packet length (in bytes)
 *      will be stored.
 *
 * PktStatus_p (output)
 *      Pointer to memory location where the processed packet status
 *      will be stored.
 *
 * ChannelID (input)
 *      Channel identifier for the packet.
 *
 * Return: 0 if no packet received (timeout) or the packet had an error.
 *         1 if a packet was received.
 */
unsigned int
da_macsec_get_one(
        bool fIngress,
        uint8_t * Buffer_p,
        unsigned int * const ByteCount_p,
        PktIO_Packet_Status_Out_t * const PktStatus_p,
        unsigned int ChannelID);


/*----------------------------------------------------------------------------
 * da_secy_bypass_drop
 *
 * Perform the packet bypass or drop test.
 *
 * I.  For the EIP-164 egress configuration
 *     1) Initialize the EIP-164 device SecY functionality via the 164 driver
 *        SecY API.
 *     2) Submit the Ethernet frame to the EIP-164 device via the Packet I/O
 *        API.
 *     3) Wait inside the test till the Packet I/O API Packet_Get() function
 *        reads the Ethernet frame from the EIP-164 device, compare this frame
 *        to the expected one.
 *     4) Read the SecY and IFC/IFC1 statistics for the initialized EIP-164
 *        device via the 164 driver SecY API, check the statistics counters
 *        are sane (some must be incremented).
 *     5) Uninitialize the EIP-164 device SecY functionality via the 164 driver
 *        SecY API.
 *
 * II. For the EIP-164 ingress configuration
 *     The steps are similar to I. except that in 1) and 2) ingress mode must
 *     be set instead of the egress mode and in 4) the ingress counters must
 *     be used.
 *
 * fVerbose (input)
 *     If true, display verbose logging info for each packet.
 *
 * fDrop (input)
 *     If true, perform drop operation, else bypass operation.
 *
 * fIngress (input)
 *     If true, perform ingress operation, else egress operation.
 *
 * MinPktSize (input)
 *     Minimum packet size (must be at least 28)
 *
 * MaxPktSize (input)
 *     Maximum packet size.
 *
 * SizeStep (input)
 *     Step by which to increase the size of each packet in the range from
 *     minimum to maximum,
 *
 * Return true if successful, false in case of failure.
 */
bool
da_secy_bypass_drop(
        bool fVerbose,
        bool fDrop,
        bool fIngress,
        unsigned int MinPktSize,
        unsigned int MaxPktSize,
        unsigned int SizeStep);


/*----------------------------------------------------------------------------
 * da_secy_macsec_transform
 *
 * Perform the packet MACsec transform test.
 *
 * I.  For the EIP-164 egress configuration
 *     1) Initialize the EIP-164 device SecY functionality via the 164 driver
 *        SecY API.
 *     2) Install the SA flow with transform record via the 164 driver SecY
 *        API.
 *     3) Submit the Ethernet frame to the EIP-164 device via the Packet I/O
 *        API.
 *     4) Wait inside the test till the Packet I/O API Packet_Get() function
 *        reads the Ethernet frame from the EIP-164 device, compare this frame
 *        to the expected one.
 *     5) Read the SA, SecY and IFC/IFC1 statistics for the initialized EIP-164
 *        device via the 164 driver SecY API, check the statistics counters are
 *        sane (some must be incremented).
 *     6) Uninstall the SA flow via the 164 driver SecY API.
 *     7) Uninitialize the EIP-164 device SecY functionality via the 164 driver
 *        SecY API.
 *
 * II. For the EIP-164 ingress configuration
 *     The steps are similar to I. except that in 1) and 2) ingress mode must
 *     be set instead of the egress mode and in 5) the ingress counters must
 *     be used.
 *
 * fVerbose (input)
 *     If true, display verbose logging info for each packet.
 *
 * fIngress (input)
 *     If true, perform ingress operation, else egress operation.
 *
 * Return true if successful, false in case of failure.
 */
bool
da_secy_macsec_transform(
        bool fVerbose,
        bool fIngress);


/*----------------------------------------------------------------------------
 * da_secy_macsec_rekey
 *
 * Perform the packet MACsec transform rekey test.
 *
 * I.  For the EIP-164 egress configuration
 *     1 Install the first SA (AN=0)
 *     2 Process a packet, must be protected by SA#1
 *     3 Install a second SA (AN=1) via SecY_SA_Chain()
 *     4 Process a packet, must still be protected by SA#1
 *     5 Switch to new SA using SecY_SA_Switch
 *     6 Remove the first SA
 *     7 Process a packet, must be protected by SA#2
 *     8 Remove the second SA.
 *
 *
 * II. For the EIP-164 ingress configuration
 *     1 Install the first SA (AN=0)
 *     2 Process a packet for SA#1, correctly decrypted.
 *     3 Install a second SA (AN=1) for same ingress SCI.
 *     4 Process packet for SA#1, must pass.
 *     5 Remove the first SA.
 *     6 Process a packet for SA#2, must pass.
 *     7 Remove the second SA.
 *
 * fVerbose (input)
 *     If true, display verbose logging info for each packet.
 *
 * fIngress (input)
 *     If true, perform ingress operation, else egress operation.
 *
 * Return true if successful, false in case of failure.
 */
bool
da_secy_macsec_rekey(
        bool fVerbose,
        bool fIngress);


/*----------------------------------------------------------------------------
 * da_secy_cfye_bypass_drop
 *
 * Perform the packet bypass or drop test.
 *
 * I.  For the EIP-164 egress configuration
 *     1) Initialize the EIP-164 device SecY functionality via the 164 driver
 *        SecY API.
 *     2) Install the EIP-164 flow for bypass/drop via the SecY API.
 *     3) Install the flow with the packet classification rule for the
 *        installed vPort via the 164 driver CfyE API. Enable the flow via the
 *        CfyE API.
 *     4) Submit the Ethernet frame to the EIP-164 device via the Packet I/O
 *        API.
 *     5) Wait inside the test till the Packet I/O API Packet_Get() function
 *        reads the Ethernet frame from the EIP-164 device, compare this frame
 *        to the expected one.
 *     6) Read the SecY and IFC/IFC1 statistics for the initialized EIP-164
 *        device via the 164 driver SecY API, check the statistics counters are
 *        sane(some must be incremented).
 *     7) Remove the EIP-164 flow and classification flow using the SecY and
 *        CfyE API
 *     8) Uninitialize the EIP-164 device SecY functionality via the 164 driver
 *        SecY API.
 *
 * II. For the EIP-164 ingress configuration
 *     The steps are similar to I. except that in 1), 2) and 3) ingress mode
 *     must be set instead of the egress mode and in 6) the ingress counters
 *     must be used.
 *
 * fVerbose (input)
 *     If true, display verbose logging info for each packet.
 *
 * fDrop (input)
 *     If true, perform drop operation, else bypass operation.
 *
 * fIngress (input)
 *     If true, perform ingress operation, else egress operation.
 *
 * MinPktSize (input)
 *     Minimum packet size (must be at least 28)
 *
 * MaxPktSize (input)
 *     Maximum packet size.
 *
 * SizeStep (input)
 *     Step by which to increase the size of each packet in the range from
 *     minimum to maximum,
 *
 * Return true if successful, false in case of failure.
 */
bool
da_secy_cfye_bypass_drop(
        bool fVerbose,
        bool fDrop,
        bool fIngress,
        unsigned int MinPktSize,
        unsigned int MaxPktSize,
        unsigned int SizeStep);

/*----------------------------------------------------------------------------
 * da_secy_cfye_macsec_transform
 *
 * Perform the packet MACsec transform test.
 *
 * I.  For the EIP-164 egress configuration
 *     1) Initialize the EIP-164 device CfyE and SecY functionality via the
 *        respectively the 164 driver CfyE API and SecY API.
 *     2) Install the SA flow with transform record via the 164 driver SecY
 *        API.
 *     3) Install the flow with the packet classification rule for the
 *        installed SA via the 164 driver CfyE API. Enable the flow via the
 *        CfyE API.
 *     4) Submit the Ethernet frame to the EIP-164 device via the Packet I/O
 *        API.
 *     5) Wait inside the test till the Packet I/O API Packet_Get() function
 *        reads the Ethernet frame from the EIP-164 device, compare this frame
 *        to the expected one.
 *     6) Read the SA, SecY and IFC/IFC1 statistics for the initialized
 *        EIP-164 device via the 164 driver SecY API, check the statistics
 *        counters are sane (some must be incremented).
 *     7) Disable the flow and uninstall the flow via the 164 driver CfyE API.
 *     8) Uninstall the SA via the 164 driver SecY API.
 *     9) Uninitialize the EIP-164 device SecY functionality via the 164
 *        driver SecY API.
 *
 * II. For the EIP-164 ingress configuration Similar to I.
 *
 * fVerbose (input)
 *     If true, display verbose logging info for each packet.
 *
 * fIngress (input)
 *     If true, perform ingress operation, else egress operation.
 *
 * Return true if successful, false in case of failure.
 */
bool
da_secy_cfye_macsec_transform(
        bool fVerbose,
        bool fIngress);


/*----------------------------------------------------------------------------
 * da_secy_cfye_macsec_transform_sm4
 *
 * Perform the packet MACsec transform test.
 *
 * I.  For the EIP-164 egress configuration
 *     1) Initialize the EIP-164 device CfyE and SecY functionality via the
 *        respectively the 164 driver CfyE API and SecY API.
 *     2) Install the SA flow with transform record via the 164 driver SecY
 *        API.
 *     3) Install the flow with the packet classification rule for the
 *        installed SA via the 164 driver CfyE API. Enable the flow via the
 *        CfyE API.
 *     4) Submit the Ethernet frame to the EIP-164 device via the Packet I/O
 *        API.
 *     5) Wait inside the test till the Packet I/O API Packet_Get() function
 *        reads the Ethernet frame from the EIP-164 device, compare this frame
 *        to the expected one.
 *     6) Read the SA, SecY and IFC/IFC1 statistics for the initialized
 *        EIP-164 device via the 164 driver SecY API, check the statistics
 *        counters are sane (some must be incremented).
 *     7) Disable the flow and uninstall the flow via the 164 driver CfyE API.
 *     8) Uninstall the SA via the 164 driver SecY API.
 *     9) Uninitialize the EIP-164 device SecY functionality via the 164
 *        driver SecY API.
 *
 * II. For the EIP-164 ingress configuration Similar to I.
 *
 * fVerbose (input)
 *     If true, display verbose logging info for each packet.
 *
 * fIngress (input)
 *     If true, perform ingress operation, else egress operation.
 *
 * Return true if successful, false in case of failure.
 */
bool
da_secy_cfye_macsec_transform_sm4(
        bool fVerbose,
        bool fIngress);


/*----------------------------------------------------------------------------
 * da_secy_cfye_should_secure
 *
 * Perform a test with must-secure and should-secure settings.
 *
 * I.  For the EIP-164 egress configuration
 *     1) Initialize the EIP-164 device CfyE and SecY functionality via the
 *        respectively the 164 driver CfyE API and SecY API.
 *     2) Configure the control packet parser.
 *     3) Configure one channel on the  device for must-secure and
 *        one for should-secure. If the whole device is configured to drop
 *        control packets, do not enable should-secure.
 *     4) Send a control packet and a data packet on the must-secure channel.
 *        The control packet should be passed and the data packet should be
 *        dropped. If the whole device is configured to drop control packets,
 *        both packets must be dropped.
 *     5) Send a control packet and a data packet on the should-secure channel.
 *        Both should be passed. If the whole device is configured to drop
 *        control packets, both must be dropped.
 *     6) Uninitialize the EIP-164 device SecY and EIP-163 device CfyE
 *        functionality via the 164 driver SecY API and CfyE API.
 *
 * II. For the EIP-164 ingress configuration Similar to I.
 *
 * fVerbose (input)
 *     If true, display verbose logging info for each packet.
 *
 * fDropControl (input)
 *     If true, configure the device to drop control packets.
 *
 * fIngress (input)
 *     If true, perform ingress operation, else egress operation.
 *
 * Return true if successful, false in case of failure.
 */
bool
da_secy_cfye_should_secure(
        bool fVerbose,
        bool fDropControl,
        bool fIngress);


/*----------------------------------------------------------------------------
 * da_secy_cfye_control_pkt_nodef
 *
 * Demonstrate configuring a vPort such that control packets are passed and
 * data packets are either passed or dropped depending on should-secure setting
 * before a real SA is added, after adding one and after removing it.
 *
 * This test matches all packets to a specific vPort and does not rely on
 * default per-channel must-secure or should-secure settings that are only
 * available for HW3.0 and later. Hence the test also works on HW2.x
 * Neither does it use default vPorts
 *
 * 1 Initialize the CfyE and SecY devices
 * 2 Program the control packet parser.
 * 3 Program TCAM rules so each channel goes to a separate vPort.
 *   Program yet another TCAM rule to assign a different vPort to a specific
 *   VLAN tag on one of the channels.
 * 4 Program dummy MACsec SAs on 3 vPorts: one for must-secure, two for should
 *   secure
 * 5 Process packets to check the configurationn.
 *   control packets are always passed, data packets are passed on should-secure
 *   channel, dropped on must-secure channel.
 * 6 Install proper MACsec SAs, remove the dummy SAs.
 * 7 Process packets to check the configuration.
 *   control packets are always passed, data packets are encrypted for egress,
 *   passed on ingress should-secure, dropped on ingress must-secure.
 *   MACsec packets are decrypted.
 * 8 Disable the MACsec SAs, disable the current SA without removing,
 * 9 Process packets to check the configuration.
 *   control packets are always passed, data packets are passed on should-secure
 * 10 Remove all SAs, vPorts and rules,  clean up and uninitialize the devices.
 *
 * fVerbose (input)
 *     If true, display verbose logging info for each packet.
 *
 * fIngress (input)
 *     If true, perform ingress operation, else egress operation.
 *
 * Return true if successful, false in case of failure.
 */
bool
da_secy_cfye_control_pkt_nodef(
        bool fVerbose,
        bool fIngress);

/*----------------------------------------------------------------------------
 * da_secy_cfye_control_pkt
 *
 * Demonstrate configuring default vPorts, such that control packets are
 * always bypassed and data packets are bypassed for should-secure
 * configurations and dropped for must-secure configurations. For the entire
 * device there is one default vPort for should-secure and one for must-secure.
 *
 * When MACsec SAs are installed, matching TCAM rules are installed, directing
 * the traffic to the vPorts belonging to the MACsec SAs instead of the default
 * vPorts.
 *
 * This test creates default vPorts with associated SAs and does not rely on
 * default per-channel must-secure or should-secure settings that are only
 * available for HW3.0 and later. Hence the test also works on HW2.x
 *
 * 1 Initialize the CfyE and SecY devices
 * 2 Install the default vPorts using a dummy MACsec SA for must-secure and
 *   a bypass SA for should-secure.
 * 3 Program the channels on the EIP163, selecting one of the default vPorts
 *   for each channel. Also configure the control packet parser and VLAN tag
 *   parser.
 * 5 Process packets to check the configuration.
 *   control packets are always passed, data packets are passed on should-secure
 *   channel, dropped on must-secure channel.
 * 6 Install proper MACsec vPorts with a MACsec SA for each vPort. Also install
 *   TCAM rules to direct traffic to the MACsec vPorts
 * 7 Process packets to check the configuration.
 *   control packets are always passed, data packets are encrypted for egress,
 *   passed on ingress should-secure, dropped on ingress must-secure.
 *   MACsec packets are decrypted on ingress configurations.
 *   Packets that do not match one of the MACSec rules are still processed by
 *   the default vPorts.
 * 8 Uninstall the MACsec SAs. First disable the TCAM rule, then remove the
 *   TCAM rule, vPort and SA.
 * 9 Process packets to check the configuration.
 *   control packets are always passed, data packets are passed on should-secure
 * 10 Remove all remaining SAs and vPorts, clean up and uninitialize the
 *    devices.
 *
 * fVerbose (input)
 *     If true, display verbose logging info for each packet.
 *
 * fIngress (input)
 *     If true, perform ingress operation, else egress operation.
 *
 * Return true if successful, false in case of failure.
 */
bool
da_secy_cfye_control_pkt(
        bool fVerbose,
        bool fIngress);

/*----------------------------------------------------------------------------
 * da_secy_cfye_deverror
 *
 * Perform the packet MACsec transform test, like da_secy_cfye_macsec_transform,
 * but force register read/write errors in some Driver Framework functions.
 * and check that the API function fails as expected and returns the expected
 * error code. Retry any functions that could not complete, so the
 * operation can proceed.
 *
 * fVerbose (input)
 *     If true, display verbose logging info for each packet.
 *
 * fIngress (input)
 *     If true, perform ingress operation, else egress operation.
 *
 * Return true if successful, false in case of failure.
 */
bool
da_secy_cfye_deverror(
        bool fVerbose,
        bool fIngress);




/*----------------------------------------------------------------------------
 * da_secy_cfye_QinQ_MACsec_transform
 *
 * Perform the packet MACsec transform test for two VLAN tags (QinQ)
 *
 * I.  For the EIP-164 egress configuration
 *     1)  Initialize the EIP-164 device CfyE and SecY functionality via the
 *         respectively the 164 driver CfyE API and SecY API.
 *     2)  Install VLAN parser rules for the used channel via the 164 driver
 *         CfyE API.
 *     3)  Install the SA flow with transform record via the 164 driver SecY
 *         API.
 *     4)  Install the flow with the packet classification rule for the
 *         installed SA via the 164 driver CfyE API. Enable the flow via the
 *         CfyE API.
 *     5)  Submit the Ethernet frame to the EIP-164 device via the Packet I/O
 *         API.
 *     6)  Wait inside the test till the Packet I/O API Packet_Get() function
 *         reads the Ethernet frame from the EIP-164 device, compare this frame
 *         to the expected one.
 *     7)  Read the CfyE TCAM statistics for the installed rule via the 164
 *         driver CfyE API, check the statistics counters are sane (TCAM 0
 *         must be incremented).
 *     8)  Read the SA, SecY and IFC/IFC1 statistics for the initialized
 *         EIP-164 device via the 164 driver SecY API, check the statistics
 *         counters are sane (some must be incremented).
 *     9)  Disable the flow and uninstall the flow via the 164 driver CfyE API.
 *     10) Uninstall the SA via the 164 driver SecY API.
 *     11) Uninitialize the EIP-164 device SecY functionality via the 164
 *         driver SecY API.
 *
 * II. For the EIP-164 ingress configuration
 *     The steps are similar to I. except that in 1), 2), 3) and 4) ingress
 *     mode must be set instead of the egress mode and in 8) the ingress
 *     counters must be used.
 *
 * fVerbose (input)
 *     If true, display verbose logging info for each packet.
 *
 * fIngress (input)
 *     If true, perform ingress operation, else egress operation.
 *
 * Return true if successful, false in case of failure.
 */
bool
da_secy_cfye_QinQ_MACsec_transform(
        bool fVerbose,
        bool fIngress);


/*----------------------------------------------------------------------------
 * da_macsec_build_sa
 *
 * Create SA record using MACsec SA Builder.
 *
 * params (input)
 *     Parameters that specify MACsec SA.
 *
 * SAWordCount_p (output)
 * Return: pointer to buffer allocated by da_macsec malloc(),
 *         containing SA record. Caller must free the buffer.
 *         NULL in case of error.
 */
uint32_t * da_macsec_build_sa(
    const da_sa_params_t * const params,
    uint32_t * const SAWordCount_p);

/*----------------------------------------------------------------------------
 * da_secy_cfye_ipsec_transform
 *
 * Perform the packet IPsec transform test.
 *
 * I.  For the EIP-164 egress configuration
 *     1) Initialize the EIP-164 device CfyE and SecY functionality via the
 *        respectively the 164 driver CfyE API and SecY API.
 *     2) Install the SA flow with transform record via the 164 driver SecY
 *        API.
 *     3) Install the flow with the packet classification rule for the
 *        installed SA via the 164 driver CfyE API. Enable the flow via the
 *        CfyE API.
 *     4) Submit the Ethernet frame to the EIP-164 device via the Packet I/O
 *        API.
 *     5) Wait inside the test till the Packet I/O API Packet_Get() function
 *        reads the Ethernet frame from the EIP-164 device, compare this frame
 *        to the expected one.
 *     6) Read the SA, SecY and IFC/IFC1 statistics for the initialized
 *        EIP-164 device via the 164 driver SecY API, check the statistics
 *        counters are sane (some must be incremented).
 *     7) Disable the flow and uninstall the flow via the 164 driver CfyE API.
 *     8) Uninstall the SA via the 164 driver SecY API.
 *     9) Uninitialize the EIP-164 device SecY functionality via the 164
 *        driver SecY API.
 *
 * II. For the EIP-164 ingress configuration Similar to I. In addition to I,
 *     below steps need to be performed.
 *     1) Install classification and MTT rules via the 164 driver CfyE API.
 *     2) Read the CfyE TCAM and MTT statistics for the installed rule via
 *        the 164 driver CfyE API, check the statistics counters are sane
 *        (TCAM 0 and MTT 0 must be incremented).
 *
 * fVerbose (input)
 *     If true, display verbose logging info for each packet.
 *
 * fIngress (input)
 *     If true, perform ingress operation, else egress operation.
 *
 * Return true if successful, false in case of failure.
 */
bool
da_secy_cfye_IPsec_transform(
        bool fVerbose,
        bool fIngress);

/*----------------------------------------------------------------------------
 * da_secy_cfye_VxLAN_MACsec_transform
 *
 * Perform the packet MACsec transform test for a 802.1Q Ethernet over
 * VxLAN
 *
 * I.  For the EIP-164 egress configuration
 *     1)  Initialize the EIP-164 device CfyE and SecY functionality via the
 *         respectively the 164 driver CfyE API and SecY API.
 *     2)  Install L3/L4 parser rules for the used channel via the 164 driver
 *         CfyE API.
 *     3)  Install the SA flow with transform record via the 164 driver SecY
 *         API.
 *     4)  Install the flow with the packet classification rule for the
 *         installed SA via the 164 driver CfyE API. Enable the flow via the
 *         CfyE API.
 *     5)  Submit the Ethernet frame to the EIP-164 device via the Packet I/O
 *         API.
 *     6)  Wait inside the test till the Packet I/O API Packet_Get() function
 *         reads the Ethernet frame from the EIP-164 device, compare this frame
 *         to the expected one.
 *     7)  Read the CfyE TCAM statistics for the installed rule via the 164
 *         driver CfyE API, check the statistics counters are sane (TCAM 0
 *         must be incremented).
 *     8)  Read the SA, SecY and IFC/IFC1 statistics for the initialized
 *         EIP-164 device via the 164 driver SecY API, check the statistics
 *         counters are sane (some must be incremented).
 *     9)  Disable the flow and uninstall the flow via the 164 driver CfyE API.
 *     10) Uninstall the SA via the 164 driver SecY API.
 *     11) Uninitialize the EIP-164 device SecY functionality via the 164
 *         driver SecY API.
 *
 * II. For the EIP-164 ingress configuration
 *     The steps are similar to I. except that in 1), 2), 3) and 4) ingress
 *     mode must be set instead of the egress mode and in 8) the ingress
 *     counters must be used.
 *
 * fVerbose (input)
 *     If true, display verbose logging info for each packet.
 *
 * fIngress (input)
 *     If true, perform ingress operation, else egress operation.
 *
 * Return true if successful, false in case of failure.
 */
bool
da_secy_cfye_VxLAN_MACsec_transform(
        bool fVerbose,
        bool fIngress);


#endif /* DA_INTERNAL_H_ */


/* end of file da_internal.h */
