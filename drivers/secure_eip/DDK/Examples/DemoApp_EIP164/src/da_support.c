/* da_support.c
 *
 * Demo Application for MACsec.
 * Support functions across multiple use cases.
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
#include "api_cfye.h"
#include "sa_builder_macsec.h"
#include "aes.h"

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
static const uint8_t MAC_SA[]    = {  1,  2,  3,  4,  5,  6 };
static const uint8_t MAC_DA[]    = { 11, 12, 13, 14, 15, 16 };


/*----------------------------------------------------------------------------
 * da_macsec_put16
 *
 * Write 16-bit value to byte array in network byte order.
 */
void
da_macsec_put16(
        uint8_t * p,
        unsigned int offs,
        uint16_t val)
{
    p[offs] = val >> 8;
    p[offs+1] = val & 0xff;
}


/*----------------------------------------------------------------------------
 * da_macsec_gen_frame
 *
 * Generate a valid Ethernet frame of the specified length
 * (must be at least MIN_PKT_BYTE_COUNT octets).
 */
void
da_macsec_gen_frame(
        uint8_t * Packet_p,
        unsigned int PacketByteCount)
{
    unsigned int i;
    uint8_t c = PacketByteCount & 0xff;

    /* Clear Ethernet frame header */
    memset(Packet_p, 0, 12);

    /* Fill in Ethernet frame header */
    memcpy(Packet_p, MAC_DA, 6);        /* Destination address */
    memcpy(&Packet_p[6], MAC_SA, 6);    /* Source address */

    /* Ethertype */
    da_macsec_put16(Packet_p, 12, 0x0800); /* Internet protocol, v4 */

    /* Fill in some payload data. */
    for (i = 14; i < PacketByteCount; i++)
    {
        Packet_p[i] = c;
        c++;
    }

    /* Add CRC-32 (empty) */
    da_macsec_put16(Packet_p, PacketByteCount, 0x0000);
    da_macsec_put16(Packet_p, PacketByteCount + 2, 0x0000);
}


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
        unsigned int ChannelID)
{
    int RetCode;
    int LoopCounter = DA_MACSEC_PKT_GET_RETRY_COUNT;

    while (LoopCounter > 0)
    {
        /* Try to get the processed packet from the driver */
        RetCode = PktIO_Packet_Get(Buffer_p,
                                   ByteCount_p,
                                   PktStatus_p,
                                   ChannelID,
                                   fIngress ? PKTIO_PACKET_DIRECTION_INGRESS :
                                              PKTIO_PACKET_DIRECTION_EGRESS);
        if (RetCode != 0)
        {
            LOG_CRIT("DA_MACSEC: Error from PktIO_Packet_Get: %d\n",
                     RetCode);
            return 0;                   /* error */
        }

        if (*ByteCount_p > 0)
            return 1;                   /* packet is received */

        if (PktStatus_p->PacketStatusMask != 0)
            return 0;                   /* packet is processed, drop or error */

        /* Delay until next try */
        da_macsec_usleep(DA_MACSEC_PKT_GET_TIMEOUT_MS * 1000);

        LoopCounter--;
    }

    LOG_CRIT("DA_MACSEC: Timeout when reading packet\n");

    /* timeout, no result packet received */
    return 0;
}


/*----------------------------------------------------------------------------
 * da_macsec_build_sa
 */
uint32_t * da_macsec_build_sa(
    const da_sa_params_t * const params,
    uint32_t * const SAWordCount_p)
{
    SABuilder_Params_t SAParams;
    SABuilder_Status_t rc;
    unsigned int SAWordCount;
    uint32_t *SABuffer_p;

    memset(&SAParams, 0, sizeof(SAParams));

    rc = SABuilder_InitParams(&SAParams,
                              params->AN,
                              params->direction,
                              params->operation);
    if (rc != SAB_STATUS_OK)
    {
        LOG_CRIT("da_macsec_build_sa: SABuilder_InitParams error\n");
        return NULL;
    }

    SAParams.operation = params->operation;
    SAParams.Key_p = params->Key_p;
    SAParams.KeyByteCount = params->KeyByteCount;
    SAParams.SCI_p = params->SCI_p;
    SAParams.SeqNumLo = params->SeqNumLo;
    SAParams.WindowSize = params->SeqMask;

    if (params->flags & SAB_MACSEC_FLAG_SM4)
    {
        /* The DDK does not contain a software implementation of the SM4
           block cipher (one for the AES block cipher is included).

           Therefore the SA Builder cannot perform the HKEY computation
           internally for SM4. If the application provides an implementation of
           the SM4 block cipher, it can call the SA Builder with a pointer to
           such function instead of AES_Encrypt and then the SA Builder could
           perform the HKEY computation internally.

           Instead this demo application provides the pre-compute HKEY just
           after the cipher key.
         */
        SAParams.HKey_p = params->Key_p + 16;
    }

#if defined(DA_IPSEC_ENABLE)
    SAParams.SPI = params->SPI;
#endif

    SAParams.flags |= params->flags;

    if (params->Salt_p)
    {
        if (SAB_OP_MACSEC == params->operation)
            SAParams.flags |= SAB_MACSEC_FLAG_LONGSEQ;

        SAParams.Salt_p = params->Salt_p;
        SAParams.SSCI_p = params->SSCI_p;
        SAParams.SeqNumLo = params->SeqNumLo;
        SAParams.SeqNumHi = params->SeqNumHi;
    }

    rc = SABuilder_GetSize(&SAParams, &SAWordCount);
    if (rc != SAB_STATUS_OK)
    {
        LOG_CRIT("da_macsec_build_sa: SABuilder_GetSize error\n");
        return NULL;
    }

    SABuffer_p = da_macsec_malloc(SAWordCount * sizeof(uint32_t));
    if (SABuffer_p == NULL)
    {
        LOG_CRIT("da_macsec_build_sa: memory allocation failure\n");
        return NULL;
    }

    *SAWordCount_p = SAWordCount;

    rc = SABuilder_BuildSA(&SAParams, SABuffer_p, AES_Encrypt);
    if (rc != SAB_STATUS_OK)
    {
        da_macsec_free(SABuffer_p);
        LOG_CRIT("da_macsec_build_sa: error building SA\n");
        return NULL;
    }

    return SABuffer_p;
}


/* end of file da_support.c */
