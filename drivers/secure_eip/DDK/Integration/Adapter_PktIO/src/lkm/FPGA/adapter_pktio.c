/* adapter_pktio.c
 *
 * User-space PktIO API implementation for FPGA
 *
 * This is a stub implementation and must be filled in with actual functionality
 * during the customization.
 */

/*****************************************************************************
* Copyright (c) 2015-2021 by Rambus, Inc. and/or its subsidiaries.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 2 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

#include "api_pktio.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Driver Framework Basic Definitions API */
#include "basic_defs.h" /* IDENTIFIER_NOT_USED */


/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * Local variables
 */


/*----------------------------------------------------------------------------
 * PktIO_Init
 */
int
PktIO_Init(void)
{
    return -1; /* not implemented */
}


/*----------------------------------------------------------------------------
 * PktIO_Packet_Put
 */
int
PktIO_Packet_Put(
        const unsigned char * Packet_p,
        const unsigned int PacketByteCount,
        const PktIO_Packet_Status_In_t * const PktStatus_p,
        unsigned int ChannelID,
        PktIO_Packet_Direction_t Direction)
{
    IDENTIFIER_NOT_USED(Packet_p);
    IDENTIFIER_NOT_USED(PacketByteCount);
    IDENTIFIER_NOT_USED(PktStatus_p);
    IDENTIFIER_NOT_USED(ChannelID);
    IDENTIFIER_NOT_USED(Direction);

    return -1; /* not implemented */
}


/*----------------------------------------------------------------------------
 * PktIO_Packet_Get
 */
int
PktIO_Packet_Get(
        unsigned char * Packet_pp,
        unsigned int * const PacketByteCount_p,
        PktIO_Packet_Status_Out_t * const PktStatus_p,
        unsigned int ChannelID,
        PktIO_Packet_Direction_t Direction)
{
    IDENTIFIER_NOT_USED(Packet_pp);
    IDENTIFIER_NOT_USED(PacketByteCount_p);
    IDENTIFIER_NOT_USED(PktStatus_p);
    IDENTIFIER_NOT_USED(ChannelID);
    IDENTIFIER_NOT_USED(Direction);

    return -1; /* not implemented */
}


#include "adapter_driverpktio_init_ext.h"


/* end of file adapter_pktio.c */
