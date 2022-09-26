/* adapter_cfye_vport.c
 *
 * CfyE API vPort lementation
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

#include "api_cfye.h"               /* CfyE API */

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Top-level Adapter configuration */
#include "c_adapter_eip163.h"       /* ADAPTER_EIP163_DRIVER_NAME */

/* Logging API */
#include "log.h"                    /* LOG_* */

/* Driver Framework Basic Definitions API */
#include "basic_defs.h"             /* uint32_t */

/* Driver Framework Device API */
#include "device_types.h"

/* Driver Framework Run-Time C Library Abstraction API */
#include "clib.h"                    /* ZEROINIT() */

/* EIP-163 Driver Library API */
#include "eip163.h"

/* List API */
#include "list.h"

/* Adapter internal API */
#include "adapter_cfye_support.h"
#ifdef ADAPTER_EIP163_WARMBOOT_ENABLE
#include "adapter_cfye_warmboot.h"
#endif

/* SecYLib API SecY_vPort_Statistics_Clear */
#include "adapter_secy_support.h"


/*----------------------------------------------------------------------------
 * External variables
 *
 */

const CfyE_vPortHandle_t CfyE_vPortHandle_NULL = NULL;


/*----------------------------------------------------------------------------
 * CfyELib_vPort_Update
 */
static CfyE_Status_t
CfyELib_vPort_Update(
        const unsigned int DeviceId,
        const unsigned int vPortId,
        const CfyE_vPortHandle_t vPortHandle,
        const CfyE_vPort_t * const vPort_p)
{
    EIP163_Error_t EIP163_Rc;
    EIP163_vPortPolicy_t DevicePort;

    /* Fill in device-specific vPort data structure for packet classification */
    ZEROINIT(DevicePort);

    DevicePort.PktExtension    = vPort_p->PktExtension;
    DevicePort.SecTagOffset    = vPort_p->SecTagOffset;
#if defined(ADAPTER_EIP164_IPSEC_ENABLE)
    DevicePort.MPLS_Hdr        = vPort_p->MPLS_Hdr;
#endif
    LOG_INFO("\n\t EIP163_vPortPolicy_Update \n");

    /* Add the vPort to the Classification device */
    EIP163_Rc = EIP163_vPortPolicy_Update(&CfyE_Devices[DeviceId]->IOArea,
                                          vPortId,
                                          &DevicePort);

    IDENTIFIER_NOT_USED_LOG_OFF(vPortHandle);

    if (EIP163_Rc != EIP163_NO_ERROR)
    {
        LOG_CRIT("%s: Failed to update vPort %p (id=%d) "
                 "for EIP-163 device %d (%s), error %d\n",
                 __func__,
                 vPortHandle,
                 vPortId,
                 DeviceId,
                 ADAPTER_EIP163_DEVICE_NAME(DeviceId),
                 EIP163_Rc);
        return CFYE_DLIB_ERROR(EIP163_Rc);
    }

    return CFYE_STATUS_OK;
}


/*----------------------------------------------------------------------------
 * CfyELib_RulesCount_Get
 *
 * Get the numbers of rules associated with this vPort handle
 */
static unsigned int
CfyELib_RulesCount_Get(
        const CfyE_vPortHandle_t vPortHandle)
{
    CfyE_vPort_Descriptor_Internal_t * vPortDscr_p =
                                (CfyE_vPort_Descriptor_Internal_t*)vPortHandle;

    return vPortDscr_p->u.InUse.BoundRulesCount;
}


/*----------------------------------------------------------------------------
 * CfyE_vPort_Add
 */
CfyE_Status_t
CfyE_vPort_Add(
        const unsigned int DeviceId,
        CfyE_vPortHandle_t * const vPortHandle_p,
        const CfyE_vPort_t * const vPort_p,
        const CfyE_Channel_Mode_t ChannelMode)
{
    unsigned int vPortId;

    LOG_INFO("\n %s \n", __func__);

    ADAPTER_EIP163_CHECK_INT_ATMOST(DeviceId, ADAPTER_EIP163_MAX_NOF_DEVICES - 1);
    ADAPTER_EIP163_CHECK_POINTER(vPort_p);

    CfyELib_Device_Lock(DeviceId);

    if (!CfyELib_Initialized_Check(DeviceId, __func__, true))
    {
        CfyELib_Device_Unlock(DeviceId);
        return CFYE_ERROR_INTERNAL;
    }

    /* Obtain a free vPort for this classification device */
    {
        List_Element_t * vPortElmt_p;
        CfyE_vPort_Descriptor_Internal_t * vPortDscr_p;
        void * const PFL_p = CfyE_Devices[DeviceId]->vPortFreeList_p;

        List_Status_t List_Rc = List_RemoveFromTail(0, PFL_p, &vPortElmt_p);
        if (List_Rc != LIST_STATUS_OK || vPortElmt_p->DataObject_p == NULL)
        {
            LOG_CRIT("%s: Failed to obtain a free vPort for "
                     "EIP-163 device %d (%s), error %d\n",
                     __func__,
                     DeviceId,
                     ADAPTER_EIP163_DEVICE_NAME(DeviceId),
                     List_Rc);
            CfyELib_Device_Unlock(DeviceId);
            return CFYE_ERROR_INTERNAL;
        }

        /* Convert vPort descriptor to vPort index and handle */
        vPortDscr_p =
                  (CfyE_vPort_Descriptor_Internal_t*)vPortElmt_p->DataObject_p;
        vPortId = vPortDscr_p - CfyE_Devices[DeviceId]->vPortDscr_p;
        vPortDscr_p->u.InUse.vPortPolicyId = vPortId;
        vPortDscr_p->u.InUse.ChannelMode = ChannelMode;

        /* vPort descriptor magic number */
        vPortDscr_p->Magic = ADAPTER_EIP163_VPORT_DSCR_MAGIC;

        *vPortHandle_p  = vPortDscr_p;
        vPortDscr_p->u.InUse.BoundRulesCount = 0;
    }

#ifdef ADAPTER_EIP163_WARMBOOT_ENABLE
    CfyELib_WarmBoot_vPort_Set(DeviceId, vPortId);

#ifdef TEST_IPSEC_ENABLE
    if (CYFE_MODE_IPSEC == ChannelMode)
    {
        CfyELib_WarmBoot_ChMode_Set(DeviceId, vPortId);
    }
#endif
#endif

    /* Now we have vPortId */
    {
        CfyE_Status_t rc;

        rc = CfyELib_vPort_Update(DeviceId, vPortId, *vPortHandle_p, vPort_p);

        CfyELib_Device_Unlock(DeviceId);

        LOG_INFO("\n %s done \n", __func__);

        if (rc != 0)
            return rc;
    }

    /* Clear the vPort statistics on the associated EIP164 device */
    {
        SecY_Status_t SecY_Rc;
        SecY_Rc = SecYLib_vPort_Statistics_Clear(DeviceId, vPortId);

        if (SecY_Rc != SECY_STATUS_OK)
            return SecY_Rc;

    }
    return CFYE_STATUS_OK;
}


/*----------------------------------------------------------------------------
 * CfyE_vPort_Remove
 */
CfyE_Status_t
CfyE_vPort_Remove(
        const unsigned int DeviceId,
        const CfyE_vPortHandle_t vPortHandle)
{
    EIP163_Error_t EIP163_Rc;
    unsigned int vPortId;
#if defined(TEST_IPSEC_ENABLE) && defined(ADAPTER_EIP163_WARMBOOT_ENABLE)
    CfyE_vPort_Descriptor_Internal_t * vPortDscr_p =
                                (CfyE_vPort_Descriptor_Internal_t*)vPortHandle;
#endif

    LOG_INFO("\n %s \n", __func__);

    ADAPTER_EIP163_CHECK_INT_ATMOST(DeviceId, ADAPTER_EIP163_MAX_NOF_DEVICES - 1);

    if (!CfyELib_vPortHandle_IsValid(vPortHandle))
        return CFYE_ERROR_BAD_PARAMETER;

    CfyELib_Device_Lock(DeviceId);

    if (!CfyELib_Initialized_Check(DeviceId, __func__, true))
    {
        CfyELib_Device_Unlock(DeviceId);
        return CFYE_ERROR_INTERNAL;
    }

    /* Get the vPort index in the device for this vPort handle */
    vPortId = CfyELib_vPortId_Get(vPortHandle);

    if (vPortId >= CfyE_Devices[DeviceId]->vPortCount)
    {
        CfyELib_Device_Unlock(DeviceId);
        return CFYE_ERROR_INTERNAL;
    }

#ifdef ADAPTER_EIP163_WARMBOOT_ENABLE
    CfyELib_WarmBoot_vPort_Clear(DeviceId, vPortId);

#ifdef TEST_IPSEC_ENABLE
    if (CYFE_MODE_IPSEC == vPortDscr_p->u.InUse.ChannelMode)
    {
        CfyELib_WarmBoot_ChMode_Clear(DeviceId, vPortId);
    }
#endif
#endif

    /* Check there are no rules associated with this vPort */
    {
        unsigned int RulesCount = CfyELib_RulesCount_Get(vPortHandle);

        if (RulesCount)
        {
            LOG_CRIT("%s: Failed to remove vPort %p (id=%d) "
                     "from EIP-163 device %d (%s), bound rules count %d\n",
                     __func__,
                     vPortHandle,
                     vPortId,
                     DeviceId,
                     ADAPTER_EIP163_DEVICE_NAME(DeviceId),
                     RulesCount);
            CfyELib_Device_Unlock(DeviceId);
            return CFYE_ERROR_INTERNAL;
        }
    }

    LOG_INFO("\n\t EIP163_vPortPolicy_Remove \n");

    EIP163_Rc = EIP163_vPortPolicy_Remove(&CfyE_Devices[DeviceId]->IOArea, vPortId);
    if (EIP163_Rc != EIP163_NO_ERROR)
    {
        LOG_CRIT("%s: Failed to remove vPort %p (id=%d) "
                 "from EIP-163 device %d (%s), error %d\n",
                 __func__,
                 vPortHandle,
                 vPortId,
                 DeviceId,
                 ADAPTER_EIP163_DEVICE_NAME(DeviceId),
                 EIP163_Rc);
    }

    /* Add vPort to be removed to the vPort free list */
    {
        List_Status_t List_Rc;
        void * const PFL_p = CfyE_Devices[DeviceId]->vPortFreeList_p;
        List_Element_t * const vPortElmt_p =
                            &CfyE_Devices[DeviceId]->vPortDscr_p[vPortId].u.free;
        /* Invalidate magic number. */
        CfyE_Devices[DeviceId]->vPortDscr_p[vPortId].Magic = 0;

        vPortElmt_p->DataObject_p = &CfyE_Devices[DeviceId]->vPortDscr_p[vPortId];

        List_Rc = List_AddToHead(0, PFL_p, vPortElmt_p);
        if (List_Rc != LIST_STATUS_OK)
        {
            LOG_CRIT("%s: Failed to add vPort %p (id=%d) to free list for "
                     "EIP-163 device %d (%s)\n",
                     __func__,
                     vPortHandle,
                     vPortId,
                     DeviceId,
                     ADAPTER_EIP163_DEVICE_NAME(DeviceId));
            CfyELib_Device_Unlock(DeviceId);
            return CFYE_ERROR_INTERNAL;
        }
    }

    CfyELib_Device_Unlock(DeviceId);

    LOG_INFO("\n %s done \n", __func__);

    if (EIP163_Rc == EIP163_NO_ERROR)
    {
        return CFYE_STATUS_OK;
    }
    else
    {
        return CFYE_DLIB_ERROR(EIP163_Rc);
    }
}


/*----------------------------------------------------------------------------
 * CfyE_vPort_Update
 */
CfyE_Status_t
CfyE_vPort_Update(
        const unsigned int DeviceId,
        const CfyE_vPortHandle_t vPortHandle,
        const CfyE_vPort_t * const vPort_p)
{
    LOG_INFO("\n %s \n", __func__);

    ADAPTER_EIP163_CHECK_INT_ATMOST(DeviceId, ADAPTER_EIP163_MAX_NOF_DEVICES - 1);
    ADAPTER_EIP163_CHECK_POINTER(vPort_p);

    if (!CfyELib_vPortHandle_IsValid(vPortHandle))
        return CFYE_ERROR_BAD_PARAMETER;

    CfyELib_Device_Lock(DeviceId);

    if (!CfyELib_Initialized_Check(DeviceId, __func__, true))
    {
        CfyELib_Device_Unlock(DeviceId);
        return CFYE_ERROR_INTERNAL;
    }

    {
        CfyE_Status_t rc;

        rc = CfyELib_vPort_Update(DeviceId,
                                  CfyELib_vPortId_Get(vPortHandle),
                                  vPortHandle,
                                  vPort_p);

        CfyELib_Device_Unlock(DeviceId);

        LOG_INFO("\n %s done \n", __func__);

        return rc;
    }
}


/*-----------------------------------------------------------------------------
 * CfyE_vPortIndex_Get
 */
CfyE_Status_t
CfyE_vPortIndex_Get(
        const CfyE_vPortHandle_t vPortHandle,
        unsigned int * const vPortIndex_p)
{
    if (!CfyELib_vPortHandle_IsValid(vPortHandle))
        return CFYE_ERROR_BAD_PARAMETER;

    ADAPTER_EIP163_CHECK_POINTER(vPortIndex_p);

    *vPortIndex_p = CfyELib_vPortId_Get(vPortHandle);

    return CFYE_STATUS_OK;
}


/*----------------------------------------------------------------------------
 * CfyE_vPortHandle_IsSame
 */
bool
CfyE_vPortHandle_IsSame(
        const CfyE_vPortHandle_t Handle1_p,
        const CfyE_vPortHandle_t Handle2_p)
{
    return CfyELib_vPortHandle_IsSame(Handle1_p, Handle2_p);
}


/*-----------------------------------------------------------------------------
 * CfyE_vPortHandle_Get
 */
CfyE_Status_t
CfyE_vPortHandle_Get(
        const unsigned int DeviceId,
        const unsigned int vPortIndex,
        CfyE_vPortHandle_t * const vPortHandle_p)
{
    CfyE_Status_t CfyE_Rc = CFYE_STATUS_OK;
    ADAPTER_EIP163_CHECK_POINTER(vPortHandle_p);

    CfyELib_Device_Lock(DeviceId);

    if (!CfyELib_Initialized_Check(DeviceId, __func__, true))
    {
        CfyELib_Device_Unlock(DeviceId);
        return CFYE_ERROR_INTERNAL;
    }

    if(!CfyELib_vPortIndexToHandle(DeviceId,
                                   vPortIndex,
                                   vPortHandle_p))
    {
        CfyE_Rc = CFYE_ERROR_INTERNAL;
    }

    CfyELib_Device_Unlock(DeviceId);
    return CfyE_Rc;
}


/* end of file adapter_cfye_vport.c */
