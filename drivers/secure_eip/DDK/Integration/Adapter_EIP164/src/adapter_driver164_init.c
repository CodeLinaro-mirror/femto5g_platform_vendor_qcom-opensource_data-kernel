/* adapter_driver164_init.c
 *
 * Adapter top level module, Security-IP-164 driver's entry point.
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

#include "api_driver164_init.h"    /* Driver Init API */


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Top-level Adapter configuration */
#include "cs_adapter.h"             /* ADAPTER_DRIVER_NAME */

/* Adapter Initialization API */
#include "adapter_init.h"           /* Adapter_* */

/* Logging API */
#include "log.h"                     /* LOG_INFO */

/* Driver Framework Basic Defs API */
#include "basic_defs.h"

/* Driver Framework C Run-time Library API */
#include "clib.h"

/* Driver Framework Device API */
#include "device_mgmt.h"

/* WarmBoot init API */
#include "adapter_init_warmboot.h"

/* Adapter init support API. */
#include "adapter_init_support.h"

/*----------------------------------------------------------------------------
 * Driver164_Init
 */
int
Driver164_Init(void)
{
    LOG_INFO("\n\t %s \n", __func__);

    LOG_INFO("%s driver: initializing\n", ADAPTER_EIP164_DRIVER_NAME);

    Adapter_Report_Build_Params();

    if (!Adapter_Init())
    {
        return -1;
    }
#ifdef ADAPTER_WARMBOOT_ENABLE
    if (!Adapter_Init_WarmBoot_Init())
    {
        return -1;
    }
#endif


    LOG_INFO("\n\t %s done \n", __func__);

    return 0;   /* success */
}


/*----------------------------------------------------------------------------
 * Driver164_Exit
 */
void
Driver164_Exit(void)
{
    LOG_INFO("\n\t %s \n", __func__);

    LOG_INFO("%s driver: exit\n", ADAPTER_EIP164_DRIVER_NAME);

#ifdef ADAPTER_WARMBOOT_ENABLE
    Adapter_Init_WarmBoot_Uninit();
#endif
    Adapter_UnInit();

    LOG_INFO("\n\t %s done \n", __func__);
}


/*----------------------------------------------------------------------------
 * Driver164_Device_Add
 */
int
Driver164_Device_Add(
        const unsigned int Index,
        const Driver164_Device_t * const Device_p)
{
    int Rc;
    Device_Properties_t Props;

    LOG_INFO("\n\t %s \n", __func__);

    ZEROINIT(Props);

    Props.Flags             = Device_p->Flags;
    Props.Name_p            = Device_p->DeviceName_p;
    Props.StartByteOffset   = Device_p->StartByteOffset;
    Props.LastByteOffset    = Device_p->LastByteOffset;

    Rc = Device_Add(Index, &Props);

#ifdef ADAPTER_WARMBOOT_ENABLE
    if (Rc == 0)
    {
        Adapter_Init_WarmBoot_Device_Update(Index, &Props);
    }
#endif

    LOG_INFO("\n\t %s done \n", __func__);

    return Rc;
}


/*----------------------------------------------------------------------------
 * Driver164_Device_Remove
 */
int
Driver164_Device_Remove(
        const unsigned int Index)
{
    int Rc;

    LOG_INFO("\n\t %s \n", __func__);

    Rc = Device_Remove(Index);

    LOG_INFO("\n\t %s done \n", __func__);

#ifdef ADAPTER_WARMBOOT_ENABLE
    if (Rc == 0)
    {
        Adapter_Init_WarmBoot_Device_Update(Index, NULL);
    }
#endif

    return Rc;
}


/*-----------------------------------------------------------------------------
 * Driver164_Device_GetCount
 */
unsigned int
Driver164_Device_GetCount(void)
{
    unsigned int Count;

    LOG_INFO("\n\t %s \n", __func__);

    Count = Device_GetCount();

    LOG_INFO("\n\t %s done \n", __func__);

    return Count;
}


/*----------------------------------------------------------------------------
 * Driver164_DataPath_Add
 */
int
Driver164_DataPath_Add(
        const unsigned int Index,
        const Driver164_DataPath_t * const DataPath_p)
{
    int Rc;

    LOG_INFO("\n\t %s \n", __func__);

    if (Index >= ADAPTER_EIP164_MAX_NOF_DEVICES)
        return -1;

    Rc = Adapter_Init_DataPath_Add(Index, DataPath_p);

#ifdef ADAPTER_WARMBOOT_ENABLE
    if (Rc == 0)
    {
        Adapter_Init_WarmBoot_DataPath_Update(Index, DataPath_p);
    }
#endif

    LOG_INFO("\n\t %s done \n", __func__);

    return Rc;
}


/*----------------------------------------------------------------------------
 * Driver164_DataPath_Remove
 */
int
Driver164_DataPath_Remove(
        const unsigned int Index)
{
    int Rc;

    LOG_INFO("\n\t %s \n", __func__);

    if (Index >= ADAPTER_EIP164_MAX_NOF_DEVICES)
        return -1;

    Rc = Adapter_Init_DataPath_Remove(Index);

    LOG_INFO("\n\t %s done \n", __func__);

#ifdef ADAPTER_WARMBOOT_ENABLE
    if (Rc == 0)
    {
        Adapter_Init_WarmBoot_DataPath_Update(Index, NULL);
    }
#endif

    return Rc;
}


/*-----------------------------------------------------------------------------
 * Driver164_DataPath_GetCount
 */
unsigned int
Driver164_DataPath_GetCount(void)
{
    return ADAPTER_EIP164_MAX_NOF_DEVICES;
}


#include "adapter_driver164_init_ext.h"


/* end of file adapter_driver164_init.c */
