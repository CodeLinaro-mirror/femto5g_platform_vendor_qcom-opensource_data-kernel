/* adapter_warmboot_support.c
 *
 * Top-level implementation of the WarmBoot API (Warmboot_Register) and
 * driver-internal API.
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

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

/* WarmBoot API */
#include "api_warmboot.h"

/* WarmBoot internal API */
#include "adapter_warmboot_support.h"

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Default configuration */
#include "c_adapter_warmboot.h"

/* Driver Framework Basic Definitions API */
#include "basic_defs.h"

#ifdef ADAPTER_WARMBOOT_ENABLE
/*----------------------------------------------------------------------------
 * Definitions and macros
 */
typedef struct
{
    WarmBoot_Alloc_Callback_t Alloc_CB;
    WarmBoot_Free_Callback_t Free_CB;
    WarmBoot_Write_Callback_t Write_CB;
    WarmBoot_Read_Callback_t Read_CB;
} WarmBoot_Callbacks_t;


/*----------------------------------------------------------------------------
 * Local variables
 */
static WarmBoot_Callbacks_t WarmBoot_Callbacks;


/*----------------------------------------------------------------------------
 * WarmBootLib_Alloc
 */
bool
WarmBootLib_Alloc(
        const unsigned int StorageByteCount,
        unsigned int * const AreaId_p)
{
    WarmBoot_Status_t rc;
    if(WarmBoot_Callbacks.Alloc_CB == NULL)
        return false;
    rc = WarmBoot_Callbacks.Alloc_CB(StorageByteCount, AreaId_p);
    return rc == WARMBOOT_STATUS_OK;
}


/*----------------------------------------------------------------------------
 * WarmBootLib_Free
 */
bool
WarmBootLib_Free(
        const unsigned int AreaId)
{
    WarmBoot_Status_t rc;
    if(WarmBoot_Callbacks.Free_CB == NULL)
        return true;
    rc = WarmBoot_Callbacks.Free_CB(AreaId);
    return rc == WARMBOOT_STATUS_OK;
}


/*----------------------------------------------------------------------------
 * WarmBootLib_Write
 */
bool
WarmBootLib_Write(
        const unsigned int AreaId,
        const unsigned char * const restrict  Data_p,
        const unsigned int ByteOffset,
        const unsigned int ByteCount)
{
    WarmBoot_Status_t rc;
    if(WarmBoot_Callbacks.Write_CB == NULL)
        return false;
    rc = WarmBoot_Callbacks.Write_CB(AreaId,Data_p,ByteOffset,ByteCount);
    return rc == WARMBOOT_STATUS_OK;
}


/*----------------------------------------------------------------------------
 * WarmBootLib_Read
 */
bool
WarmBootLib_Read(
        const unsigned int AreaId,
        unsigned char * const restrict Data_p,
        const unsigned int ByteOffset,
        const unsigned int ByteCount)
{
    WarmBoot_Status_t rc;
    if(WarmBoot_Callbacks.Read_CB == NULL)
        return false;
    rc = WarmBoot_Callbacks.Read_CB(AreaId,Data_p,ByteOffset,ByteCount);
    return rc == WARMBOOT_STATUS_OK;
}


/*----------------------------------------------------------------------------
 * WarmBoot_Register
 */
WarmBoot_Status_t
WarmBoot_Register(
        WarmBoot_Alloc_Callback_t Alloc_CB,
        WarmBoot_Free_Callback_t Free_CB,
        WarmBoot_Write_Callback_t Write_CB,
        WarmBoot_Read_Callback_t Read_CB)
{
    if (Alloc_CB == NULL ||
        Write_CB == NULL || Read_CB == NULL)
    {
        return WARMBOOT_ERROR_BAD_PARAMETER;
    }

    WarmBoot_Callbacks.Alloc_CB = Alloc_CB;
    WarmBoot_Callbacks.Free_CB = Free_CB;
    WarmBoot_Callbacks.Write_CB = Write_CB;
    WarmBoot_Callbacks.Read_CB = Read_CB;
    return WARMBOOT_STATUS_OK;
}

#endif /* ADAPTER_WARMBOOT_ENABLE */

/* end of file adapter_warmboot_support.c */
