/* adapter_warmboot_support.h
 *
 * WarmBoot support interface.
 */

/*****************************************************************************
* Copyright (c) 2017-2021 by Rambus, Inc. and/or its subsidiaries.
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

#ifndef INCLUDE_GUARD_ADAPTER_WARMBOOT_SUPPORT_H
#define INCLUDE_GUARD_ADAPTER_WARMBOOT_SUPPORT_H

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Driver Framework Basic Definitions API */
#include "basic_defs.h"         /* bool */

/*----------------------------------------------------------------------------
 * Definitions and macros
 */
#define restrict  /* restrict keyword may not be accepted by some compilers. */


/*----------------------------------------------------------------------------
 * WarmBootLib_Alloc
 *
 * This function allocates a storage area of the desired size in
 * a memory area that will be preserved across CPU reboots. The allocated
 * area is filled entirely with bytes of value zero. The returned AreaId
 * represents a valid storage area. Each allocated (and not yet freed) storage
 * area has a unique AreaId.
 *
 * StorageByteCount (input)
 *     Size of the storage area in bytes.
 *
 * AreaId_p (output)
 *     ID of the allocated storage area.
 *
 * Return value:
 *     true: success.
 *     false: failure
 */
bool
WarmBootLib_Alloc(
        const unsigned int StorageByteCount,
        unsigned int * const AreaId_p);


/*----------------------------------------------------------------------------
 * WarmBootLib_Free
 *
 * This function frees a storage area previously allocated by
 * the WarnBoot_Alloc callback.  After this call, AreaId no longer corresponds
 * to a valid storage area and it may no longer be passed to callbacks of this
 * API. Future calls to the WarmBoot_Alloc callback may re-use this AreaId.
 *
 * AreaId (input)
 *     ID of the storage area to be freed.
 *
 * Return value:
 *     true: success.
 *     false: failure
 */
bool
WarmBootLib_Free(
        const unsigned int AreaId);


/*----------------------------------------------------------------------------
 * WarmBootLib_Write
 *
 * This function writes data to the storage area described by
 * the AreaId. It overwrites the data starting at ByteOffset and with size
 * ByteCount. Other bytes stored in this area are unchanged.
 *
 * AreaId (input)
 *     ID of the storage area to write to.
 * Data_p (input)
 *     Pointer to the data to be written.
 * ByteOffset (input)
 *     Offset from the start of the storage area where the first data
 *     byte will be written (ByteOffset == 0 corresponds to start of area).
 * ByteCount (input)
 *     Number of bytes to write.
 *
 * Note: data may be partially written in case of an unexpected reboot.
 *       The last byte will be written last, so it can be used as a flag to
 *       indicate validity.
 *
 * Return value:
 *     true: success.
 *     false: failure
 */
bool
WarmBootLib_Write(
        const unsigned int AreaId,
        const unsigned char * const restrict  Data_p,
        const unsigned int ByteOffset,
        const unsigned int ByteCount);


/*----------------------------------------------------------------------------
 * WarmBootLib_Read
 *
 *
 * This function reads data from the storage area described by
 * the AreaId. It reads the data starting at ByteOffset and with size
 * ByteCount
 *
 * AreaId (input)
 *     ID of the storage area to read from.
 * Data_p (output)
 *     Pointer an area where the read data will be stored.
 * ByteOffset (input)
 *     Offset from the start of the storage area where the first data
 *     byte will be read (ByteOffset == 0 corresponds to start of area).
 * ByteCount (input)
 *     Number of bytes to read.
 *
 * Return value:
 *     true: success.
 *     false: failure
 */
bool
WarmBootLib_Read(
        const unsigned int AreaId,
        unsigned char * const restrict Data_p,
        const unsigned int ByteOffset,
        const unsigned int ByteCount);


#endif /* INCLUDE_GUARD_ADAPTER_WARMBOOT_SUPPORT_H */


/* end of file adapter_warmboot_support.h */
