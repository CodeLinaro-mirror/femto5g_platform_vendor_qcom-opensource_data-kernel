/* api_pktio.h
 *
 * Packet I/O API
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


#ifndef API_PKTIO_H_
#define API_PKTIO_H_

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */



/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

/* Bit masks for packet and classification status */
#define PKTIO_PACKET_PKT_ERROR      0x01
#define PKTIO_PACKET_CRC_ERROR      0x02
#define PKTIO_PACKET_LP_IDLE        0x04
#define PKTIO_PACKET_SA_HIT         0x08  /* SA in use */
#define PKTIO_PACKET_RULE_HIT       0x10  /* TCAM rule hit (=vPort found) */
#define PKTIO_PACKET_CLASS_DROP     0x20  /* drop by classifier */
#define PKTIO_PACKET_SC_HIT         0x40  /* SC found */
#define PKTIO_PACKET_EG_HDR         0x80  /* Egress header present */
#define PKTIO_PACKET_CTRL_PKT       0x100 /* Control packet identifier */
#define PKTIO_PACKET_VPORT_VALID    0x200 /* vPort valid */

/* Mask to identify if packet is dropped */
#define PKTIO_PACKET_DROPPED_MASK   (PKTIO_PACKET_PKT_ERROR + \
                                     PKTIO_PACKET_CRC_ERROR)

/* Packet processing direction, egress or ingress */
typedef enum
{
    PKTIO_PACKET_DIRECTION_EGRESS,
    PKTIO_PACKET_DIRECTION_INGRESS
} PktIO_Packet_Direction_t;

/* Packet status (used for Put function) */
typedef struct
{
    unsigned int vPort;                 /* virtual port number */

    unsigned int SecTAGOffset;          /* SecTAG offset */
    unsigned int MACSAOffset;           /* MAC SA offset */

    /* See bit masks for packet and classification status above */
    unsigned int PacketStatusMask;

} PktIO_Packet_Status_In_t;

/* Packet status (used for Get function) */
typedef struct
{
    unsigned int vPort;                 /* virtual port number */

    /* Output debug status, used only for output packet */
    unsigned int SAIndex;               /* pkt_tx_sa_index */
    unsigned int SCIndex;               /* pkt_tx_sc_index */
    unsigned int RuleIndex;             /* pkt_tx_rule_index */

    /* See bit masks for packet and classification status above */
    unsigned int PacketStatusMask;

} PktIO_Packet_Status_Out_t;


/*----------------------------------------------------------------------------
 * Local variables
 */


/*----------------------------------------------------------------------------
 * PktIO_Init
 *
 * Initializes the Packet I/O driver
 *
 * Return value:
 *     0 : success
 *    <0 : failure
 */
int
PktIO_Init(void);


/*----------------------------------------------------------------------------
 * PktIO_Packet_Put
 *
 * Submits a packet to the engine.
 *
 * Packet_p (input)
 *      Pointer to a buffer containing packet data.
 *
 * PacketByteCount (input)
 *      Packet length in bytes.
 *
 * PktStatus_p (input)
 *      Packet status associated with the passed packet.
 *
 * ChannelID (input)
 *      Channel identifier for the packet.
 *
 * Direction (input)
 *      Packet processing direction, see PktIO_Packet_Direction_t.
 *
 * Return value:
 *     0 : success
 *    <0 : failure
 */
int
PktIO_Packet_Put(
        const unsigned char * Packet_p,
        const unsigned int PacketByteCount,
        const PktIO_Packet_Status_In_t * const PktStatus_p,
        unsigned int ChannelID,
        PktIO_Packet_Direction_t Direction);


/*----------------------------------------------------------------------------
 * PktIO_Packet_Get
 *
 * Retrieves a packet from the engine. Returns packet byte count set to 0
 * when no packet is retrieved.
 *
 * Packet_pp (output)
 *      Pointer to a memory location where the packet data will be stored.
 *
 * PacketByteCount_p (output)
 *      Pointer to a memory location where the packet length in bytes
 *      will be stored.
 *
 * PktStatus_p (output)
 *      Pointer to a memory location where the packet status will be stored.
 *
 * ChannelID (input)
 *      Channel identifier for the packet.
 *
 * Direction (input)
 *      Packet processing direction, see PktIO_Packet_Direction_t.
 *
 * Return value:
 *     0 : success
 *    <0 : failure
 */
int
PktIO_Packet_Get(
        unsigned char * Packet_pp,
        unsigned int * const PacketByteCount_p,
        PktIO_Packet_Status_Out_t * const PktStatus_p,
        unsigned int ChannelID,
        PktIO_Packet_Direction_t Direction);


#endif /* API_PKTIO_H_ */


/* end of file api_pktio.h */
