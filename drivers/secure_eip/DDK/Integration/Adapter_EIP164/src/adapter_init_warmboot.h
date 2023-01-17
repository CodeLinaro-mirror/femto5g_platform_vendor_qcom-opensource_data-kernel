/* adapter_init_warmboot.h
 *
 * WarmBoot support related to device initialization.
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

#ifndef INCLUDE_GUARD_ADAPTER_INIT_WARMBOOT_H
#define INCLUDE_GUARD_ADAPTER_INIT_WARMBOOT_H

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Driver Framework Basic Definitions API */
#include "basic_defs.h"         /* bool */

#include "device_types.h"        /* Device_Properties_t */

#include "api_driver164_init.h"  /* Driver164_DataPath_t */

/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * Adapter_Init_WarmBoot_MaxSize_Get
 *
 * This function returns the required size of the WarmBoot storage for the
 * Driver Framework in bytes.
 *
 * MaxByteCount_p (output)
 *     Size of the storage area in bytes.
 *
 * Return:
 *    true: success.
 *    false: failure.
 */
bool
Adapter_Init_WarmBoot_MaxSize_Get(
        unsigned int * const MaxByteCount_p);


/*----------------------------------------------------------------------------
 * Adapter_Init_WarmBoot_Device_Update
 *
 * This function updates the WarmBoot storage area for the given device.
 *
 * Index (input)
 *     Index of the device whose storage area must be updated.
 *
 * Props_p (input)
 *     Device properties of the device. When this pointer is NULL,
 *     the device is considered to be removed.
 *
 * Return:
 *    true: success.
 *    false: failure.
 */
bool
Adapter_Init_WarmBoot_Device_Update(
        unsigned int Index,
        const Device_Properties_t *Props_p);


/*----------------------------------------------------------------------------
 * Adapter_Init_WarmBoot_DataPath_Update
 *
 * This function updates the WarmBoot storage area for the given data path.
 *
 * Index (input)
 *     Index of the data path whose storage area must be updated.
 *
 * Props_p (input)
 *     Properties of the data path. When this pointer is NULL,
 *     the data path is considered to be removed.
 *
 * Return:
 *    true: success.
 *    false: failure.
 */
bool
Adapter_Init_WarmBoot_DataPath_Update(
        unsigned int Index,
        const Driver164_DataPath_t * Props_p);


/*----------------------------------------------------------------------------
 * Adapter_Init_WarmBoot_Init
 *
 * This function prepares the system for recording the Driver Framework state.
 * It allocates a WarmBot storage area and stores the actual state of
 * the Driver Framework in it.
 *
 * Return:
 *    true: success.
 *    false: failure.
 */
bool
Adapter_Init_WarmBoot_Init(void);


/*----------------------------------------------------------------------------
 * Adapter_Init_WarmBoot_Uninit
 *
 * This function releases any resources claimed by
 * Adapter_Init_WarmBoot_Init().  Any device operations performed
 * after this call will not be recorded in the WarmBoot area.
 *
 * Return:
 *    true: success.
 *    false: failure.
 */
bool
Adapter_Init_WarmBoot_Uninit(void);


/*----------------------------------------------------------------------------
 * Adapter_Init_WarmBoot_Shutdown
 *
 * This function indicates to the WarmBoot system that we have a planned
 * shutdown. Any device operations performed after this call will not
 * be recorded in the WarmBoot area.
 *
 * AreaId (input)
 *     ID of the WarmBoot storage area used to store the Driver Framework state.
 *
 * Return:
 *    zero: success.
 *    nonzero value: failure.
 */
int
Adapter_Init_WarmBoot_Shutdown(
        unsigned int AreaId);


/*----------------------------------------------------------------------------
 * Adapter_Init_WarmBoot_Restore
 *
 * This function restores the Driver Framework to the state recorded in
 * the WamrBoot storage area.
 *
 * AreaId (input)
 *     ID of the WarmBoot storage area used to store the Driver Framework state.
 *
 * Return:
 *    0: success.
 *    nonzero value: failure.
 */
int
Adapter_Init_WarmBoot_Restore(
        unsigned int AreaId);


#endif /* INCLUDE_GUARD_ADAPTER_INIT_ARMBOOT_H */


/* end of file adapter_init_warmboot.h */
