/* da_warmboot.c
 *
 * Test Tool for CfyE and SecY API's
 * Module to support WarmBoot functionality.
 *
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
 * This module implements (provides) the following interface(s):
 */

#include "da_warmboot.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Default configuration */
#include "c_da_macsec.h"

/* Driver Framework Basic Defs API */
#include "basic_defs.h"

/* Driver Framework CLib Abstraction API */
#include "clib.h"

/* Logging API */
#include "log.h"

/* WarmBoot API */
#include "api_warmboot.h"

/* support API */
#include "da_internal.h"

/*----------------------------------------------------------------------------
 * Definitions and macros
 */

#ifdef DA_MACSEC_USE_WARMBOOT
#define DA_MACSEC_WARMBOOT_NOF_AREAS    512

/*----------------------------------------------------------------------------
 * Local variables
 */

static void * da_macsec_warmboot_area[DA_MACSEC_WARMBOOT_NOF_AREAS];


/*----------------------------------------------------------------------
 * da_macsec_warmboot_alloc
 *
 * Implementation of the WarmBoot Alloc callback.
 */
static WarmBoot_Status_t
da_macsec_warmboot_alloc(
            const unsigned int StorageByteCount,
            unsigned int * const AreaId_p)
{
    unsigned int i;

    LOG_INFO("WarmBoot Alloc callback: alloc %u bytes\n",StorageByteCount);
    for (i=0; i<DA_MACSEC_WARMBOOT_NOF_AREAS; i++)
    {
        if (da_macsec_warmboot_area[i] == NULL)
        {
            /* Found unused area. */
            da_macsec_warmboot_area[i] = da_macsec_malloc(StorageByteCount);
            if (da_macsec_warmboot_area[i] == NULL)
            {
                /* Allocation failed. */
                return WARMBOOT_ERROR_ALLOCATION;
            }
            else
            {
                LOG_INFO("Warmboot_Alloc: allocated area %u\n",i);
                memset(da_macsec_warmboot_area[i], 0, StorageByteCount);
                *AreaId_p = i;
                return WARMBOOT_STATUS_OK;
            }
        }
    }
    /* No unused area found. */
    return WARMBOOT_ERROR_ALLOCATION;
}

/*----------------------------------------------------------------------
 * da_macsec_warmboot_free
 *
 * Implementation of the WarmBoot Free callback.
 */
static WarmBoot_Status_t
da_macsec_warmboot_free(
            const unsigned int AreaId)
{
    if (AreaId >= DA_MACSEC_WARMBOOT_NOF_AREAS)
    {
        return false;
    }
    if (da_macsec_warmboot_area[AreaId] == NULL)
    {
        return WARMBOOT_ERROR_BAD_PARAMETER;
    }
    LOG_INFO("WarmBoot Free callback: free area  %u\n",AreaId);

    da_macsec_free(da_macsec_warmboot_area[AreaId]);
    da_macsec_warmboot_area[AreaId] = NULL;
    return WARMBOOT_STATUS_OK;
}


/*----------------------------------------------------------------------
 * da_macsec_warmboot_write
 *
 * Implementation of the WarmBoot Write callback.
 */
static WarmBoot_Status_t
da_macsec_warmboot_write(
        const unsigned int AreaId,
        const unsigned char * const restrict  Data_p,
        const unsigned int ByteOffset,
        const unsigned int ByteCount)
{
    if (AreaId >= DA_MACSEC_WARMBOOT_NOF_AREAS)
    {
        return WARMBOOT_ERROR_BAD_PARAMETER;
    }
    if (da_macsec_warmboot_area[AreaId] == NULL ||
        Data_p == NULL)
    {
        return WARMBOOT_ERROR_BAD_PARAMETER;
    }
    LOG_INFO("WarmBoot Write Callback: area=%u offset=%u size=%u\n",
             AreaId,ByteOffset,ByteCount);

    memcpy((unsigned char *)da_macsec_warmboot_area[AreaId] + ByteOffset,
           Data_p,
           ByteCount);
    return WARMBOOT_STATUS_OK;
}

/*----------------------------------------------------------------------
 * da_macsec_warmboot_read
 *
 * Implementation of the WarmBoot Read callback.
 */
static WarmBoot_Status_t
da_macsec_warmboot_read(
        const unsigned int AreaId,
        unsigned char * const restrict  Data_p,
        const unsigned int ByteOffset,
        const unsigned int ByteCount)
{
    if (AreaId >= DA_MACSEC_WARMBOOT_NOF_AREAS)
    {
        return WARMBOOT_ERROR_BAD_PARAMETER;
    }
    if (da_macsec_warmboot_area[AreaId] == NULL ||
        Data_p == NULL)
    {
        return WARMBOOT_ERROR_BAD_PARAMETER;
    }
    LOG_INFO("WarmBoot Read Callback: area=%u offset=%u size=%u\n",
             AreaId,ByteOffset,ByteCount);

    memcpy(Data_p,
           (unsigned char *)da_macsec_warmboot_area[AreaId] + ByteOffset,
           ByteCount);
    return WARMBOOT_STATUS_OK;
}



/*----------------------------------------------------------------------------
 * da_macsec_warmboot_init
 */
bool
da_macsec_warmboot_init(void)
{
    WarmBoot_Status_t rc;

    rc = WarmBoot_Register(da_macsec_warmboot_alloc,
                           da_macsec_warmboot_free,
                           da_macsec_warmboot_write,
                           da_macsec_warmboot_read);

    if (rc != WARMBOOT_STATUS_OK)
    {
        LOG_CRIT("Da_MACsec: WarmBoot_Register failed.\n");
        return false;
    }

    return true;
}

/*----------------------------------------------------------------------------
 * da_macsec_warmboot_shutdown
 */
bool
da_macsec_warmboot_shutdown(void)
{
    unsigned int i;
    WarmBoot_Status_t rc;
    LOG_INFO("da_macsec_warmboot_shutdown\n");
    for (i=0; i<DA_MACSEC_WARMBOOT_NOF_AREAS; i++)
    {
        if (da_macsec_warmboot_area[i] != NULL)
        {
            LOG_INFO("da_macsec_warmboot_shutdown: area=%u\n",i);
            rc = WarmBoot_Shutdown(i);
            if (rc != WARMBOOT_STATUS_OK)
            {
                LOG_CRIT("Da_MACsec: WarmBoot_Shutdown failed.\n");
                return false;
            }
        }
    }
    return true;
}


/*----------------------------------------------------------------------------
 * da_macsec_warmboot_restore
 */
int
da_macsec_warmboot_restore(
        unsigned int StartIndex,
        unsigned int NItems)
{
    unsigned int i;
    WarmBoot_Status_t rc;
    LOG_INFO("da_macsec_warmboot_restore\n");
    for (i=StartIndex; i<StartIndex+NItems; i++)
    {
        if (da_macsec_warmboot_area[i] != NULL)
        {
            LOG_INFO("da_macsec_warmboot_restore: area=%u\n",i);
            rc = WarmBoot_Restore(i);
            if (rc != WARMBOOT_STATUS_OK)
            {
                LOG_CRIT("Da_MACsec: WarmBoot_Restore failed.\n");
                return rc;
            }
        }
    }
    return 0;
}

/*----------------------------------------------------------------------------
 * da_macsec_warmboot_uninit
 */
bool
da_macsec_warmboot_uninit(void)
{
    LOG_INFO("da_macsec_warmboot_uninit\n");
    return true;
}

#endif /* DA_MACSEC_USE_WARMBOOT */

/* end of file da_warmboot.c */
