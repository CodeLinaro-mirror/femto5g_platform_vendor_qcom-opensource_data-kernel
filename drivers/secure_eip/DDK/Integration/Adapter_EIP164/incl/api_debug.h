/* api_debug.h
 *
 * Driver Debugging API
 *
 */

/*****************************************************************************
* Copyright (c) 2012-2021 by Rambus, Inc. and/or its subsidiaries.
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

#ifndef API_DEBUG_H_
#define API_DEBUG_H_

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Driver Framework Basic Definitions API */
#include "basic_defs.h"             /* uint32_t */

/* Driver Framework Device API */
#include "device_mgmt.h"         /* SecY_SAHandle_t, SecY_Rules_* */


/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * Debug_Device_Read32
 *
 * Reads a device static resource such as register or internal memory
 *
 * API use order:
 *      None
 *
 * DeviceName_p (input)
 *      Device name to be read
 *
 * ReadOffset (input)
 *      Resource read offset within the device memory map
 *
 * Value_p (output)
 *      Pointer to a memory location where the read result will be stored.
 *
 * This function is re-entrant for the same or different DeviceName_p.
 *
 * This function can be called concurrently with any other Debug API
 * function for the same or different DeviceId provided the API use order
 * is followed.
 *
 * Return value:
 *     0 :  device resource is read
 *     <0 : failure
 */
int
Debug_Device_Read32(
        const char * const DeviceName_p,
        const unsigned int ReadOffset,
        uint32_t * Value_p);


#endif /* API_DEBUG_H_ */


/* end of file api_debug.h */
