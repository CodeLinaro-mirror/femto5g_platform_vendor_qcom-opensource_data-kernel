/* adapter_debug.c
 *
 * Driver Debugging API implementation.
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

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

#include "api_debug.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Top-level Adapter configuration */
/*#include "c_adapter_debug.h" */

/* Driver Framework Device API */
#include "device_types.h"   /* Device_Handle_t */
#include "device_mgmt.h"    /* Device_Find */
#include "device_rw.h"      /* Device_Read32, Device_Write32 */

/* Driver Framework Basic Definitions API */
#include "basic_defs.h"     /* bool, true, false */


/*----------------------------------------------------------------------------
 * Local variables
 */


/*----------------------------------------------------------------------------
 * Debug_Device_Read32
 */
int
Debug_Device_Read32(
        const char * const DeviceName_p,
        const unsigned int ReadOffset,
        uint32_t * Value_p)
{
    Device_Handle_t Device = Device_Find(DeviceName_p);

    if (Device == NULL)
        return -1; /* failure, device not found */

    *Value_p = Device_Read32(Device, ReadOffset);

    return 0; /* success */
}


/* end of file adapter_debug.c */
