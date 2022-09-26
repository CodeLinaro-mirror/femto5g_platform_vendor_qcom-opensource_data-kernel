/* adapter_secy_warmboot.h
 *
 * SecY WarmBoot interface
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

#ifndef INCLUDE_GUARD_ADAPTER_SECY_WARMBOOT_H
#define INCLUDE_GUARD_ADAPTER_SECY_WARMBOOT_H

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Driver Framework Basic Definitions API */
#include "basic_defs.h"         /* bool */

/*----------------------------------------------------------------------------
 * Definitions and macros
 */

/*----------------------------------------------------------------------------
 * SecYLib_WarmBoot_SA_Set
 *
 * Mark SA as allocated for the purpose of the WarmBoot administration.
 *
 * DeviceId (input)
 *      ID of the selected device.
 *
 * SAIndex (input)
 *      SA index of the record to mark as allocated.
 */
void
SecYLib_WarmBoot_SA_Set(
        unsigned int DeviceId,
        unsigned int SAIndex);


/*----------------------------------------------------------------------------
 * SecYLib_WarmBoot_SA_Clear
 *
 * Mark SA as free for the purpose of the WarmBoot administration..
 *
 * DeviceId (input)
 *      ID of the selected device.
 *
 * SAIndex (input)
 *      SA index of the record to mark as free.
 */
void
SecYLib_WarmBoot_SA_Clear(
        unsigned int DeviceId,
        unsigned int SAIndex);


/*----------------------------------------------------------------------------
 * SecYLib_WarmBoot_ChMode_Set
 *
 * Mark the Channel Mode as IPsec for the purpose of the WarmBoot administration.
 *
 * DeviceId (input)
 *      ID of the selected device.
 *
 * vPortIndex (input)
 *      vPort index of the record for which the Channel mode to be set as IPsec.
 */
void
SecYLib_WarmBoot_ChMode_Set(
    unsigned int DeviceId,
    unsigned int vPortIndex);


/*----------------------------------------------------------------------------
 * SecYLib_WarmBoot_ChMode_Clear
 *
 * Mark the Channel Mode as MACsec for the purpose of the WarmBoot administration..
 *
 * DeviceId (input)
 *      ID of the selected device.
 *
 * vPortIndex (input)
 *      vPort index of the record for which the Channel mode to be set as MACsec.
 */

void
SecYLib_WarmBoot_ChMode_Clear(
    unsigned int DeviceId,
    unsigned int vPortIndex);


/*----------------------------------------------------------------------------
 * SecYLib_WarmBoot_MaxSize_Get
 *
 * Determine the maximum size required for a WarmBoot area when the device
 * is initialized.
 *
 * DeviceId (input)
 *      ID of the selected device.
 *
 * fIngress (input)
 *      true if the device is for ingress.
 *
 * MaxByteCount_p (output)
 *      Maximum size of the WarmBoot area for that device.
 *
 * Return value:
 *     true: success.
 *     false: failure
 */
bool
SecYLib_WarmBoot_MaxSize_Get(
        const unsigned int DeviceId,
        const bool fIngress,
        unsigned int *MaxByteCount_p);

/*----------------------------------------------------------------------------
 * SecYLib_WarmBoot_Device_Init
 *
 * Initialize the WarmBoot administration when a device is initialized.
 *
 * DeviceId (input)
 *      ID of the selected device.
 *
 * Return value:
 *     true: success.
 *     false: failure
 */
bool
SecYLib_WarmBoot_Device_Init(
        unsigned int DeviceId);


/*----------------------------------------------------------------------------
 * SecYLib_WarmBoot_Device_Uninit
 *
 * Free the WarmBoot administration if a device is uninitialized.
 *
 * DeviceId (input)
 *      ID of the selected device.
 *
 */
void
SecYLib_WarmBoot_Device_Uninit(
        unsigned int DeviceId);

/*----------------------------------------------------------------------------
 * SecYLib_WarmBoot_Shutdown().
 *
 * SecY API specific function for WarmBoot Shutdown.
 *
 * DeviceId (input)
 *     Device Id of the device to be shut down.
 *
 * AreaId (input)
 *     Id of the storage area where device info is stored.
 *
 * Return:
 *    0: success.
 *    nonzero value: failure.
 */
int
SecYLib_WarmBoot_Shutdown(
        unsigned int DeviceId,
        unsigned int AreaId);


/*----------------------------------------------------------------------------
 * SecYLib_WarmBoot_Restore().
 *
 * SecY API specific function for WarmBoot Restore.
 *
 * DeviceId (input)
 *     Device Id of the device to be restored.
 *
 * AreaId (input)
 *     Id of the storage area where device info is stored.
 *
 * Return:
 *    0: success.
 *    nonzero value: failure.
 */
int
SecYLib_WarmBoot_Restore(
        unsigned int DeviceId,
        unsigned int AreaId);


#endif /* INCLUDE_GUARD_ADAPTER_SECY_WARMBOOT_H */


/* end of file adapter_secy_warmboot.h */
