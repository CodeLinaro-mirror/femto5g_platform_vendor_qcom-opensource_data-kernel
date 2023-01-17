/* adapter_cfye_rule.c
 *
 * CfyE Ruke API implementation
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

/* Driver Framework Run-Time C Library Abstraction API */
#include "clib.h"                    /* ZEROINIT() */

/* Sleep API */
#include "adapter_sleep.h"

/* EIP-163 Driver Library API */
#include "eip163.h"

/* List API */
#include "list.h"

/* Adapter internal API */
#include "adapter_cfye_support.h"    /* Access to data structures. */
#ifdef ADAPTER_EIP163_WARMBOOT_ENABLE
#include "adapter_cfye_warmboot.h"
#endif

/*----------------------------------------------------------------------------
 * External variables
 *
 */

const CfyE_RuleHandle_t  CfyE_RuleHandle_NULL  = NULL;


/*----------------------------------------------------------------------------
 * CfyELib_Rule_Update
 */
static CfyE_Status_t
CfyELib_Rule_Update(
        const unsigned int DeviceId,
        const unsigned int RuleId,
        const CfyE_RuleHandle_t RuleHandle,
        const CfyE_Rule_t * const Rule_p)
{
    EIP163_Error_t EIP163_Rc;
    EIP163_Rule_t DeviceRule;
    CfyE_Channel_Mode_t ChannelMode = CYFE_MODE_MACSEC;

    CfyE_Rule_Descriptor_Internal_t *RuleDscr_p = (CfyE_Rule_Descriptor_Internal_t *) RuleHandle;
    CfyE_vPort_Descriptor_Internal_t *vPortDscr = (CfyE_vPort_Descriptor_Internal_t *) RuleDscr_p->u.InUse.vPortDscr_p;

    /* Fill in device-specific rule data structure for packet classification */
    ZEROINIT(DeviceRule);

    ChannelMode = vPortDscr->u.InUse.ChannelMode;

    LOG_INFO("%s: ChannelMode: %u\n", __FUNCTION__, ChannelMode);

    /* Copy rule key, mask and packet data */
    DeviceRule.Key.NumTags    = Rule_p->Key.NumTags;
    DeviceRule.Key.PacketType = Rule_p->Key.PacketType;
    DeviceRule.Key.ChannelID  = Rule_p->Key.ChannelID;

    memcpy(DeviceRule.Data,
           Rule_p->Data,
           EIP163_RULE_NON_CTRL_WORD_COUNT * sizeof(uint32_t));

    DeviceRule.Mask.NumTags    = Rule_p->Mask.NumTags;
    DeviceRule.Mask.PacketType = Rule_p->Mask.PacketType;
    DeviceRule.Mask.ChannelID  = Rule_p->Mask.ChannelID;
    memcpy(DeviceRule.DataMask,
           Rule_p->DataMask,
           EIP163_RULE_NON_CTRL_WORD_COUNT * sizeof(uint32_t));

    /* Copy matching rule policy data */
    DeviceRule.Policy.Priority = Rule_p->Policy.Priority;
#if defined(ADAPTER_EIP163_IPSEC_ENABLE)
    DeviceRule.Policy.AN = Rule_p->Policy.AN;
#endif
    DeviceRule.Policy.vPortId =
                            CfyELib_vPortId_Get(Rule_p->Policy.vPortHandle);
    DeviceRule.Policy.fDrop = Rule_p->Policy.fDrop;
    DeviceRule.Policy.fControlPacket = Rule_p->Policy.fControlPacket;
    DeviceRule.Policy.fControlPacketSub = Rule_p->Policy.fControlPacketSub;

    {
        unsigned int LoopCounter = ADAPTER_EIP163_MAX_NOF_SYNC_RETRY_COUNT;

        IDENTIFIER_NOT_USED_LOG_OFF(RuleHandle);

        for(;;)
        {
            LoopCounter--;

            LOG_INFO("\n\t EIP163_Rule_Update \n");

            /* Add the vPort to the Classification device */
            EIP163_Rc = EIP163_Rule_Update(&CfyE_Devices[DeviceId]->IOArea,
                                           RuleId,
                                           &DeviceRule,
                                           (EIP163_ChannelMode_t) ChannelMode);
            if (EIP163_Rc == EIP163_NO_ERROR)
            {
                break;
            }
            else if (EIP163_Rc != EIP163_BUSY_RETRY_LATER || LoopCounter == 0)
            {
                LOG_CRIT("%s: Failed to update rule %p (id=%d) "
                         "for EIP-163 device %d (%s), error %d\n",
                         __func__,
                         RuleHandle,
                         RuleId,
                         DeviceId,
                         ADAPTER_EIP163_DEVICE_NAME(DeviceId),
                         EIP163_Rc);
                return CFYE_DLIB_ERROR(EIP163_Rc);
            }
            Adapter_SleepMS(ADAPTER_EIP163_SYNC_RETRY_TIMEOUT_MS);
        }
    }

   return CFYE_STATUS_OK;
}


/*----------------------------------------------------------------------------
 * CfyE_Rule_Add
 */
CfyE_Status_t
CfyE_Rule_Add(
        const unsigned int DeviceId,
        const CfyE_vPortHandle_t vPortHandle,
        CfyE_RuleHandle_t * const RuleHandle_p,
        const CfyE_Rule_t * const Rule_p)
{
    unsigned int RuleId;

    LOG_INFO("\n %s \n", __func__);

    ADAPTER_EIP163_CHECK_INT_ATMOST(DeviceId, ADAPTER_EIP163_MAX_NOF_DEVICES - 1);
    ADAPTER_EIP163_CHECK_POINTER(Rule_p);

    if (!CfyELib_vPortHandle_IsValid(vPortHandle))
        return CFYE_ERROR_BAD_PARAMETER;

    CfyELib_Device_Lock(DeviceId);

    if (!CfyELib_Initialized_Check(DeviceId, __func__, true))
    {
        CfyELib_Device_Unlock(DeviceId);
        return CFYE_ERROR_INTERNAL;
    }

    *RuleHandle_p = NULL;

    /* Obtain a free Rule for this classification device */
    {
        List_Element_t * RuleElmt_p;
        CfyE_Rule_Descriptor_Internal_t * RuleDscr_p;
        void * const RFL_p = CfyE_Devices[DeviceId]->RuleFreeList_p;

        List_Status_t List_Rc = List_RemoveFromTail(0, RFL_p, &RuleElmt_p);
        if (List_Rc != LIST_STATUS_OK || RuleElmt_p->DataObject_p == NULL)
        {
            LOG_CRIT("%s: Failed to obtain a free Rule for "
                     "EIP-163 device %d (%s), error %d\n",
                     __func__,
                     DeviceId,
                     ADAPTER_EIP163_DEVICE_NAME(DeviceId),
                     List_Rc);
            CfyELib_Device_Unlock(DeviceId);
            return CFYE_ERROR_INTERNAL;
        }

        /* Convert Rule descriptor to Rule index and handle */
        RuleDscr_p     =
                  (CfyE_Rule_Descriptor_Internal_t*)RuleElmt_p->DataObject_p;
        RuleId = RuleDscr_p - CfyE_Devices[DeviceId]->RuleDscr_p;
        RuleDscr_p->u.InUse.RuleId = RuleId;
        /* Rule descriptor magic number */
        RuleDscr_p->Magic = ADAPTER_EIP163_RULE_DSCR_MAGIC;
        RuleDscr_p->u.InUse.vPortDscr_p = (CfyE_vPort_Descriptor_Internal_t *)vPortHandle;
        RuleDscr_p->u.InUse.vPortDscr_p->u.InUse.BoundRulesCount++;

        *RuleHandle_p  = RuleDscr_p;
    }

#ifdef ADAPTER_EIP163_WARMBOOT_ENABLE
    CfyELib_WarmBoot_Rule_Set(DeviceId, RuleId);
#endif

    /* Now we have RuleId */
    {
        CfyE_Status_t rc;

        rc = CfyELib_Rule_Update(DeviceId, RuleId, *RuleHandle_p, Rule_p);

        CfyELib_Device_Unlock(DeviceId);

        LOG_INFO("\n %s done \n", __func__);

        return rc;
    }
}


/*-----------------------------------------------------------------------------
 * CfyE_Rule_Add_Index
 */
CfyE_Status_t
CfyE_Rule_Add_Index(
        const unsigned int DeviceId,
        const CfyE_vPortHandle_t vPortHandle,
        CfyE_RuleHandle_t * const RuleHandle_p,
        const CfyE_Rule_t * const Rule_p,
        const unsigned int RuleId)
{
    LOG_INFO("\n %s \n", __func__);

    ADAPTER_EIP163_CHECK_INT_ATMOST(DeviceId, ADAPTER_EIP163_MAX_NOF_DEVICES - 1);
    ADAPTER_EIP163_CHECK_POINTER(Rule_p);

    if (!CfyELib_vPortHandle_IsValid(vPortHandle))
        return CFYE_ERROR_BAD_PARAMETER;

    CfyELib_Device_Lock(DeviceId);

    if (!CfyELib_Initialized_Check(DeviceId, __func__, true))
    {
        CfyELib_Device_Unlock(DeviceId);
        return CFYE_ERROR_INTERNAL;
    }

    if (RuleId >= CfyE_Devices[DeviceId]->RulesCount)
    {
        CfyELib_Device_Unlock(DeviceId);
        return CFYE_ERROR_BAD_PARAMETER;
    }

    *RuleHandle_p = NULL;

    /* Obtain a free Rule for this classification device */
    {
        List_Status_t List_Rc;
        List_Element_t * RuleElmt_p;
        CfyE_Rule_Descriptor_Internal_t * RuleDscr_p;
        void * const RFL_p = CfyE_Devices[DeviceId]->RuleFreeList_p;

        RuleDscr_p = &CfyE_Devices[DeviceId]->RuleDscr_p[RuleId];
        if (RuleDscr_p->Magic == ADAPTER_EIP163_RULE_DSCR_MAGIC)
        {
            /* Rule with desired index already in use. */
            LOG_CRIT("%s: Desired rule index %d already in use for "
                     "EIP-163 device %d (%s)\n",
                     __func__,
                     RuleId,
                     DeviceId,
                     ADAPTER_EIP163_DEVICE_NAME(DeviceId));
            CfyELib_Device_Unlock(DeviceId);
            return CFYE_ERROR_BAD_PARAMETER;
        }

        RuleElmt_p = &RuleDscr_p->u.free;

        List_Rc = List_RemoveAnywhere(0, RFL_p, RuleElmt_p);
        if (List_Rc != LIST_STATUS_OK || RuleElmt_p->DataObject_p == NULL)
        {
            LOG_CRIT("%s: Failed to obtain a free Rule for "
                     "EIP-163 device %d (%s), error %d\n",
                     __func__,
                     DeviceId,
                     ADAPTER_EIP163_DEVICE_NAME(DeviceId),
                     List_Rc);
            CfyELib_Device_Unlock(DeviceId);
            return CFYE_ERROR_INTERNAL;
        }

        /* Convert Rule descriptor to Rule index and handle */
        RuleDscr_p->u.InUse.RuleId = RuleId;
        /* Rule descriptor magic number */
        RuleDscr_p->Magic = ADAPTER_EIP163_RULE_DSCR_MAGIC;
        RuleDscr_p->u.InUse.vPortDscr_p = (CfyE_vPort_Descriptor_Internal_t *)vPortHandle;
        RuleDscr_p->u.InUse.vPortDscr_p->u.InUse.BoundRulesCount++;
        *RuleHandle_p  = RuleDscr_p;
    }

#ifdef ADAPTER_EIP163_WARMBOOT_ENABLE
    CfyELib_WarmBoot_Rule_Set(DeviceId, RuleId);
#endif

    /* Now we have RuleId */
    {
        CfyE_Status_t rc;

        rc = CfyELib_Rule_Update(DeviceId, RuleId, *RuleHandle_p, Rule_p);

        CfyELib_Device_Unlock(DeviceId);

        LOG_INFO("\n %s done \n", __func__);

        return rc;
    }
}


/*----------------------------------------------------------------------------
 * CfyE_Rule_Remove
 */
CfyE_Status_t
CfyE_Rule_Remove(
        const unsigned int DeviceId,
        const CfyE_RuleHandle_t RuleHandle)
{
    EIP163_Error_t EIP163_Rc;
    unsigned int RuleId;

    LOG_INFO("\n %s \n", __func__);

    ADAPTER_EIP163_CHECK_INT_ATMOST(DeviceId, ADAPTER_EIP163_MAX_NOF_DEVICES - 1);

    if (!CfyELib_RuleHandle_IsValid(RuleHandle))
        return CFYE_ERROR_BAD_PARAMETER;

    CfyELib_Device_Lock(DeviceId);

    if (!CfyELib_Initialized_Check(DeviceId, __func__, true))
    {
        CfyELib_Device_Unlock(DeviceId);
        return CFYE_ERROR_INTERNAL;
    }

    RuleId = CfyELib_RuleId_Get(RuleHandle);

    if (RuleId >= CfyE_Devices[DeviceId]->RulesCount)
    {
            CfyELib_Device_Unlock(DeviceId);
            return CFYE_ERROR_INTERNAL;
    }

#ifdef ADAPTER_EIP163_WARMBOOT_ENABLE
    CfyELib_WarmBoot_Rule_Clear(DeviceId, RuleId);
#endif

    {
        unsigned int LoopCounter = ADAPTER_EIP163_MAX_NOF_SYNC_RETRY_COUNT;

         for(;;)
        {
            LoopCounter--;

            LOG_INFO("\n\t EIP163_Rule_Remove \n");
            EIP163_Rc = EIP163_Rule_Remove(&CfyE_Devices[DeviceId]->IOArea,
                                           RuleId);
            if (EIP163_Rc == EIP163_NO_ERROR)
            {
                break;
            }
            else if (EIP163_Rc != EIP163_BUSY_RETRY_LATER || LoopCounter == 0)
            {
                LOG_CRIT("%s: Failed to remove Rule %p (id=%d) "
                         "from EIP-163 device %d (%s), error %d\n",
                         __func__,
                         RuleHandle,
                         RuleId,
                         DeviceId,
                         ADAPTER_EIP163_DEVICE_NAME(DeviceId),
                         EIP163_Rc);
                CfyELib_Device_Unlock(DeviceId);
                return CFYE_DLIB_ERROR(EIP163_Rc);
            }
            Adapter_SleepMS(ADAPTER_EIP163_SYNC_RETRY_TIMEOUT_MS);
        }
    }
    /* Add removed Rule to the Rule free list */
    {
        List_Status_t List_Rc;
        void * const RFL_p = CfyE_Devices[DeviceId]->RuleFreeList_p;
        List_Element_t * const RuleElmt_p =
                            &CfyE_Devices[DeviceId]->RuleDscr_p[RuleId].u.free;

        /* Invalidate magic number. */
        CfyE_Devices[DeviceId]->RuleDscr_p[RuleId].Magic = 0;

        CfyE_Devices[DeviceId]->RuleDscr_p[RuleId].u.InUse.vPortDscr_p->u.InUse.BoundRulesCount--;
        RuleElmt_p->DataObject_p = &CfyE_Devices[DeviceId]->RuleDscr_p[RuleId];

        List_Rc = List_AddToHead(0, RFL_p, RuleElmt_p);
        if (List_Rc != LIST_STATUS_OK)
        {
            LOG_CRIT("%s: Failed to add Rule %p (id=%d) to free list for "
                     "EIP-163 device %d (%s)\n",
                     __func__,
                     RuleHandle,
                     RuleId,
                     DeviceId,
                     ADAPTER_EIP163_DEVICE_NAME(DeviceId));
            CfyELib_Device_Unlock(DeviceId);
            return CFYE_ERROR_INTERNAL;
        }
    }

    CfyELib_Device_Unlock(DeviceId);

    LOG_INFO("\n %s done \n", __func__);

    return CFYE_STATUS_OK;
}


/*----------------------------------------------------------------------------
 * CfyE_Rule_Update
 */
CfyE_Status_t
CfyE_Rule_Update(
        const unsigned int DeviceId,
        const CfyE_RuleHandle_t RuleHandle,
        const CfyE_Rule_t * const Rule_p)
{
    unsigned int RuleId;

    LOG_INFO("\n %s \n", __func__);

    ADAPTER_EIP163_CHECK_INT_ATMOST(DeviceId, ADAPTER_EIP163_MAX_NOF_DEVICES - 1);
    ADAPTER_EIP163_CHECK_POINTER(Rule_p);

    if (!CfyELib_RuleHandle_IsValid(RuleHandle))
        return CFYE_ERROR_BAD_PARAMETER;

    CfyELib_Device_Lock(DeviceId);

    if (!CfyELib_Initialized_Check(DeviceId, __func__, true))
    {
        CfyELib_Device_Unlock(DeviceId);
        return CFYE_ERROR_INTERNAL;
    }

    RuleId = CfyELib_RuleId_Get(RuleHandle);

    if (CfyE_Devices[DeviceId]->RuleDscr_p[RuleId].u.InUse.vPortDscr_p == NULL)
    {
        LOG_CRIT("%s: Failed, missing vPort for rule %p (id=%d) "
                 "for EIP-163 device %d (%s)\n",
                 __func__,
                 RuleHandle,
                 RuleId,
                 DeviceId,
                 ADAPTER_EIP163_DEVICE_NAME(DeviceId));
        CfyELib_Device_Unlock(DeviceId);
        return CFYE_ERROR_INTERNAL;
    }

    {
        CfyE_Status_t rc;

        rc = CfyELib_Rule_Update(DeviceId, RuleId, RuleHandle, Rule_p);

        CfyELib_Device_Unlock(DeviceId);

        LOG_INFO("\n %s done \n", __func__);

        return rc;
    }
}


/*----------------------------------------------------------------------------
 * CfyE_Rule_Enable
 */
CfyE_Status_t
CfyE_Rule_Enable(
        const unsigned int DeviceId,
        const CfyE_RuleHandle_t RuleHandle,
        const bool fSync)
{
    EIP163_Error_t EIP163_Rc;
    CfyE_Status_t Rc;
    unsigned int RuleId;

    LOG_INFO("\n %s \n", __func__);

    ADAPTER_EIP163_CHECK_INT_ATMOST(DeviceId, ADAPTER_EIP163_MAX_NOF_DEVICES - 1);

    if (!CfyELib_RuleHandle_IsValid(RuleHandle))
        return CFYE_ERROR_BAD_PARAMETER;

    CfyELib_Device_Lock(DeviceId);

    if (!CfyELib_Initialized_Check(DeviceId, __func__, true))
    {
        CfyELib_Device_Unlock(DeviceId);
        return CFYE_ERROR_INTERNAL;
    }

    /* Synchronize with the device if required */
    if (fSync)
    {
        Rc = CfyELib_Device_Sync(DeviceId);
        if (Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("%s: synchronization failed for device %d, error %d\n",
                     __func__, DeviceId, Rc);
            CfyELib_Device_Unlock(DeviceId);
            return Rc;
        }
    }

    RuleId = CfyELib_RuleId_Get(RuleHandle);

    if (CfyE_Devices[DeviceId]->RuleDscr_p[RuleId].u.InUse.vPortDscr_p == NULL)
    {
        LOG_CRIT("%s: Failed, missing vPort for rule %p (id=%d) "
                 "for EIP-163 device %d (%s)\n",
                 __func__,
                 RuleHandle,
                 RuleId,
                 DeviceId,
                 ADAPTER_EIP163_DEVICE_NAME(DeviceId));
        CfyELib_Device_Unlock(DeviceId);
        return CFYE_ERROR_INTERNAL;
    }

    LOG_INFO("\n\t EIP163_Rule_Enable \n");

    EIP163_Rc = EIP163_Rule_Enable(&CfyE_Devices[DeviceId]->IOArea, RuleId);
    if (EIP163_Rc != EIP163_NO_ERROR)
    {
        LOG_CRIT("%s: Failed to enable rule %p (id=%d) "
                 "for EIP-163 device %d (%s), error %d\n",
                 __func__,
                 RuleHandle,
                 RuleId,
                 DeviceId,
                 ADAPTER_EIP163_DEVICE_NAME(DeviceId),
                 EIP163_Rc);
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
 * CfyE_Rule_Disable
 */
CfyE_Status_t
CfyE_Rule_Disable(
        const unsigned int DeviceId,
        const CfyE_RuleHandle_t RuleHandle,
        const bool fSync)
{
    EIP163_Error_t EIP163_Rc;
    CfyE_Status_t Rc;
    unsigned int RuleId;

    LOG_INFO("\n %s \n", __func__);

    ADAPTER_EIP163_CHECK_INT_ATMOST(DeviceId, ADAPTER_EIP163_MAX_NOF_DEVICES - 1);

    if (!CfyELib_RuleHandle_IsValid(RuleHandle))
        return CFYE_ERROR_BAD_PARAMETER;

    CfyELib_Device_Lock(DeviceId);

    if (!CfyELib_Initialized_Check(DeviceId, __func__, true))
    {
        CfyELib_Device_Unlock(DeviceId);
        return CFYE_ERROR_INTERNAL;
    }

    RuleId = CfyELib_RuleId_Get(RuleHandle);

    if (RuleId >= CfyE_Devices[DeviceId]->RulesCount)
    {
            CfyELib_Device_Unlock(DeviceId);
            return CFYE_ERROR_INTERNAL;
    }

    if (CfyE_Devices[DeviceId]->RuleDscr_p[RuleId].u.InUse.vPortDscr_p == NULL)
    {
        LOG_CRIT("%s: Failed, missing vPort for rule %p (id=%d) "
                 "for EIP-163 device %d (%s)\n",
                 __func__,
                 RuleHandle,
                 RuleId,
                 DeviceId,
                 ADAPTER_EIP163_DEVICE_NAME(DeviceId));
        CfyELib_Device_Unlock(DeviceId);
        return CFYE_ERROR_INTERNAL;
    }

    {
        unsigned int LoopCounter = ADAPTER_EIP163_MAX_NOF_SYNC_RETRY_COUNT;

        for(;;)
        {
            LoopCounter--;
            LOG_INFO("\n\t EIP163_Rule_Disable \n");

            EIP163_Rc = EIP163_Rule_Disable(&CfyE_Devices[DeviceId]->IOArea, RuleId);
            if (EIP163_Rc == EIP163_NO_ERROR)
            {
                break;
            }
            else if (EIP163_Rc != EIP163_BUSY_RETRY_LATER || LoopCounter == 0)
            {
                LOG_CRIT("%s: Failed to disable rule %p (id=%d) "
                         "for EIP-163 device %d (%s), error %d\n",
                         __func__,
                         RuleHandle,
                         RuleId,
                         DeviceId,
                         ADAPTER_EIP163_DEVICE_NAME(DeviceId),
                         EIP163_Rc);
                CfyELib_Device_Unlock(DeviceId);
                return CFYE_DLIB_ERROR(EIP163_Rc);
            }
            Adapter_SleepMS(ADAPTER_EIP163_SYNC_RETRY_TIMEOUT_MS);
        }
    }

    /* Synchronize with the device if required */
    if (fSync)
    {
        Rc = CfyELib_Device_Sync(DeviceId);
        if (Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("%s: synchronization failed for device %d, error %d\n",
                     __func__, DeviceId, Rc);
            CfyELib_Device_Unlock(DeviceId);
            return Rc;
        }
    }

    CfyELib_Device_Unlock(DeviceId);

    LOG_INFO("\n %s done \n", __func__);

    return CFYE_STATUS_OK;
}


/*----------------------------------------------------------------------------
 * CfyE_Rule_EnableDisable
 */
CfyE_Status_t
CfyE_Rule_EnableDisable(
        const unsigned int DeviceId,
        const CfyE_RuleHandle_t RuleHandleEnable,
        const CfyE_RuleHandle_t RuleHandleDisable,
        const bool EnableAll,
        const bool DisableAll,
        const bool fSync)
{
    EIP163_Error_t EIP163_Rc;
    CfyE_Status_t Rc;
    unsigned int RuleIdEnable = 0, RuleIdDisable = 0;
    bool fEnable = false, fDisable = false;

    LOG_INFO("\n %s \n", __func__);

    ADAPTER_EIP163_CHECK_INT_ATMOST(DeviceId, ADAPTER_EIP163_MAX_NOF_DEVICES - 1);

    CfyELib_Device_Lock(DeviceId);

    if (!CfyELib_Initialized_Check(DeviceId, __func__, true))
    {
        CfyELib_Device_Unlock(DeviceId);
        return CFYE_ERROR_INTERNAL;
    }

    {
        unsigned int LoopCounter = ADAPTER_EIP163_MAX_NOF_SYNC_RETRY_COUNT;

        for(;;)
        {
            LoopCounter--;

            if (EnableAll)
            {
                LOG_INFO("\n\t EIP163_Rule_EnableDisable \n");

                EIP163_Rc = EIP163_Rule_EnableDisable(&CfyE_Devices[DeviceId]->IOArea,
                                                      0,
                                                      0,
                                                      fEnable,
                                                      fDisable,
                                                      true,
                                                      false);
            }
            else if (DisableAll)
            {
                LOG_INFO("\n\t EIP163_Rule_EnableDisable \n");

                EIP163_Rc = EIP163_Rule_EnableDisable(&CfyE_Devices[DeviceId]->IOArea,
                                                      0,
                                                      0,
                                                      fEnable,
                                                      fDisable,
                                                      false,
                                                      true);
            }
            else
            {
                fEnable = !CfyELib_RuleHandle_IsSame(RuleHandleEnable,
                                                     CfyE_RuleHandle_NULL);
                if (fEnable)
                {
                    if (!CfyELib_RuleHandle_IsValid(RuleHandleEnable))
                    {
                        CfyELib_Device_Unlock(DeviceId);
                        return CFYE_ERROR_BAD_PARAMETER;
                    }

                    RuleIdEnable  = CfyELib_RuleId_Get(RuleHandleEnable);
                }

                if (CfyE_Devices[DeviceId]->RuleDscr_p[RuleIdEnable].u.InUse.vPortDscr_p == NULL)
                {
                    LOG_CRIT("%s: Failed, missing vPort for rule %p (id=%d) "
                             "for EIP-163 device %d (%s)\n",
                             __func__,
                             RuleHandleEnable,
                             RuleIdEnable,
                             DeviceId,
                             ADAPTER_EIP163_DEVICE_NAME(DeviceId));
                    CfyELib_Device_Unlock(DeviceId);
                    return CFYE_ERROR_INTERNAL;
                }

                fDisable = !CfyELib_RuleHandle_IsSame(RuleHandleDisable,
                                                      CfyE_RuleHandle_NULL);
                if (fDisable)
                {
                    if (!CfyELib_RuleHandle_IsValid(RuleHandleDisable))
                    {
                        CfyELib_Device_Unlock(DeviceId);
                        return CFYE_ERROR_BAD_PARAMETER;
                    }

                    RuleIdDisable = CfyELib_RuleId_Get(RuleHandleDisable);
                }

                if (CfyE_Devices[DeviceId]->RuleDscr_p[RuleIdDisable].u.InUse.vPortDscr_p == NULL)
                {
                    LOG_CRIT("%s: Failed, missing vPort for rule %p (id=%d) "
                             "for EIP-163 device %d (%s)\n",
                             __func__,
                             RuleHandleDisable,
                             RuleIdDisable,
                             DeviceId,
                             ADAPTER_EIP163_DEVICE_NAME(DeviceId));
                    CfyELib_Device_Unlock(DeviceId);
                    return CFYE_ERROR_INTERNAL;
                }

                LOG_INFO("\n\t EIP163_Rule_EnableDisable \n");

                EIP163_Rc = EIP163_Rule_EnableDisable(&CfyE_Devices[DeviceId]->IOArea,
                                                      RuleIdEnable,
                                                      RuleIdDisable,
                                                      fEnable,
                                                      fDisable,
                                                      false,
                                                      false);
            }

            if (EIP163_Rc == EIP163_NO_ERROR)
            {
                break;
            }
            else if (EIP163_Rc != EIP163_BUSY_RETRY_LATER || LoopCounter == 0)
            {
                LOG_CRIT("%s: Failed to enable/disable rule %p/%p "
                         "(id %d/%d, enable/disable %d/%d) "
                         "for EIP-163 device %d (%s), error %d\n",
                 __func__,
                         RuleHandleEnable,
                         RuleHandleDisable,
                         RuleIdEnable,
                         RuleIdDisable,
                         fEnable,
                         fDisable,
                         DeviceId,
                         ADAPTER_EIP163_DEVICE_NAME(DeviceId),
                         EIP163_Rc);
                CfyELib_Device_Unlock(DeviceId);
                return CFYE_ERROR_INTERNAL;
            }
            Adapter_SleepMS(ADAPTER_EIP163_SYNC_RETRY_TIMEOUT_MS);
        }
    }
    /* Synchronize with the device if required */
    if (fSync)
    {
        Rc = CfyELib_Device_Sync(DeviceId);
        if (Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("%s: synchronization failed for device %d, error %d\n",
                     __func__, DeviceId, Rc);
            CfyELib_Device_Unlock(DeviceId);
            return Rc;
        }
    }

    CfyELib_Device_Unlock(DeviceId);

    LOG_INFO("\n %s done \n", __func__);

    return CFYE_STATUS_OK;
}


/*----------------------------------------------------------------------------
 * CfyE_RuleHandle_IsSame
 */
bool
CfyE_RuleHandle_IsSame(
        const CfyE_RuleHandle_t Handle1_p,
        const CfyE_RuleHandle_t Handle2_p)
{
    return CfyELib_RuleHandle_IsSame(Handle1_p, Handle2_p);
}


/*-----------------------------------------------------------------------------
 * CfyE_RuleIndex_Get
 */
CfyE_Status_t
CfyE_RuleIndex_Get(
        const CfyE_RuleHandle_t RuleHandle,
        unsigned int * const RuleIndex_p)
{
    if (!CfyELib_RuleHandle_IsValid(RuleHandle))
        return CFYE_ERROR_BAD_PARAMETER;

    ADAPTER_EIP163_CHECK_POINTER(RuleIndex_p);

    *RuleIndex_p = CfyELib_RuleId_Get(RuleHandle);

    return CFYE_STATUS_OK;
}


/*-----------------------------------------------------------------------------
 * CfyE_RuleHandle_Get
 */
CfyE_Status_t
CfyE_RuleHandle_Get(
        const unsigned int DeviceId,
        const unsigned int RuleIndex,
        CfyE_RuleHandle_t * const RuleHandle_p)
{
    CfyE_Status_t CfyE_Rc = CFYE_STATUS_OK;
    ADAPTER_EIP163_CHECK_POINTER(RuleHandle_p);

    CfyELib_Device_Lock(DeviceId);

    if (!CfyELib_Initialized_Check(DeviceId, __func__, true))
    {
        CfyELib_Device_Unlock(DeviceId);
        return CFYE_ERROR_INTERNAL;
    }

    if(!CfyELib_RuleIndexToHandle(DeviceId,
                                  RuleIndex,
                                  RuleHandle_p))
    {
        CfyE_Rc = CFYE_ERROR_INTERNAL;
    }

    CfyELib_Device_Unlock(DeviceId);
    return CfyE_Rc;
}

#if defined(ADAPTER_EIP163_IPSEC_ENABLE)
/*-----------------------------------------------------------------------------
 * CfyE_MTT_Update
 */
CfyE_Status_t
CfyE_MTT_Update(
        const unsigned int DeviceId,
        const unsigned int MTTIndex,
        const CfyE_MTT_t * const MTT_p)
{
    EIP163_Error_t EIP163_Rc;
    EIP163_MTT_t DeviceMTT;

    LOG_INFO("\n %s \n", __func__);

    ADAPTER_EIP163_CHECK_INT_ATMOST(DeviceId, ADAPTER_EIP163_MAX_NOF_DEVICES - 1);

    CfyELib_Device_Lock(DeviceId);

    if (!CfyELib_Initialized_Check(DeviceId, __func__, true))
    {
        CfyELib_Device_Unlock(DeviceId);
        return CFYE_ERROR_INTERNAL;
    }

    LOG_INFO("\n\t EIP163_MTT_Update \n");

    memcpy(&DeviceMTT.Key.ChannelMask, &MTT_p->Key.ChannelMask, sizeof(CfyE_Ch_Mask_t));
    DeviceMTT.Key.fIPv6       = MTT_p->Key.fIPv6;
    DeviceMTT.Key.TagLabel1   = MTT_p->Key.TagLabel1;
#if defined(ADAPTER_EIP163_IPSEC_ENABLE)
    DeviceMTT.Key.fIPHdrValid = MTT_p->Key.fIPHdrValid;
    DeviceMTT.Key.TagLabel2   = MTT_p->Key.TagLabel2;
    DeviceMTT.Key.fPacketType = MTT_p->Key.fPacketType;
#endif
    memcpy(DeviceMTT.IPAddr, MTT_p->IPAddr, 16);

    memcpy(&DeviceMTT.Mask.ChannelMask, &MTT_p->Mask.ChannelMask, sizeof(CfyE_Ch_Mask_t));
    DeviceMTT.Mask.fIPv6       = MTT_p->Mask.fIPv6;
    DeviceMTT.Mask.TagLabel1   = MTT_p->Mask.TagLabel1;
#if defined(ADAPTER_EIP163_IPSEC_ENABLE)
    DeviceMTT.Mask.fIPHdrValid = MTT_p->Mask.fIPHdrValid;
    DeviceMTT.Mask.TagLabel2   = MTT_p->Mask.TagLabel2;
    DeviceMTT.Mask.fPacketType = MTT_p->Mask.fPacketType;
#endif
    memcpy(DeviceMTT.IPAddrMask, MTT_p->IPAddrMask, 16);

    EIP163_Rc = EIP163_MTT_Update(&CfyE_Devices[DeviceId]->IOArea,
                                  MTTIndex,
                                  &DeviceMTT);
    if (EIP163_Rc != EIP163_NO_ERROR)
    {
        LOG_CRIT("%s: Failed to enable rule %d "
                 "for EIP-163 device %d (%s), error %d\n",
                 __func__,
                 MTTIndex,
                 DeviceId,
                 ADAPTER_EIP163_DEVICE_NAME(DeviceId),
                 EIP163_Rc);
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


/*-----------------------------------------------------------------------------
 * CfyE_MTT_Enable
 */
CfyE_Status_t
CfyE_MTT_Enable(
        const unsigned int DeviceId,
        const unsigned int MTTIndex,
        const bool fSync)
{
    EIP163_Error_t EIP163_Rc;
    CfyE_Status_t Rc;

    LOG_INFO("\n %s \n", __func__);

    ADAPTER_EIP163_CHECK_INT_ATMOST(DeviceId, ADAPTER_EIP163_MAX_NOF_DEVICES - 1);

    CfyELib_Device_Lock(DeviceId);

    if (!CfyELib_Initialized_Check(DeviceId, __func__, true))
    {
        CfyELib_Device_Unlock(DeviceId);
        return CFYE_ERROR_INTERNAL;
    }

    /* Synchronize with the device if required */
    if (fSync)
    {
        Rc = CfyELib_Device_Sync(DeviceId);
        if (Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("%s: synchronization failed for device %d, error %d\n",
                     __func__, DeviceId, Rc);
            CfyELib_Device_Unlock(DeviceId);
            return Rc;
        }
    }

    LOG_INFO("\n\t EIP163_MTT_Enable \n");

    EIP163_Rc = EIP163_MTT_Enable(&CfyE_Devices[DeviceId]->IOArea, MTTIndex);
    if (EIP163_Rc != EIP163_NO_ERROR)
    {
        LOG_CRIT("%s: Failed to enable rule %d "
                 "for EIP-163 device %d (%s), error %d\n",
                 __func__,
                 MTTIndex,
                 DeviceId,
                 ADAPTER_EIP163_DEVICE_NAME(DeviceId),
                 EIP163_Rc);
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


/*-----------------------------------------------------------------------------
 * CfyE_MTT_Disable
  */
CfyE_Status_t
CfyE_MTT_Disable(
        const unsigned int DeviceId,
        const unsigned int MTTIndex,
        const bool fSync)
{
    EIP163_Error_t EIP163_Rc;
    CfyE_Status_t Rc;

    LOG_INFO("\n %s \n", __func__);

    ADAPTER_EIP163_CHECK_INT_ATMOST(DeviceId, ADAPTER_EIP163_MAX_NOF_DEVICES - 1);

    CfyELib_Device_Lock(DeviceId);

    if (!CfyELib_Initialized_Check(DeviceId, __func__, true))
    {
        CfyELib_Device_Unlock(DeviceId);
        return CFYE_ERROR_INTERNAL;
    }

    LOG_INFO("\n\t EIP163_MTT_Disable \n");

    EIP163_Rc = EIP163_MTT_Disable(&CfyE_Devices[DeviceId]->IOArea, MTTIndex);
    if (EIP163_Rc != EIP163_NO_ERROR)
    {
        LOG_CRIT("%s: Failed to disable rule %d "
                 "for EIP-163 device %d (%s), error %d\n",
                 __func__,
                 MTTIndex,
                 DeviceId,
                 ADAPTER_EIP163_DEVICE_NAME(DeviceId),
                 EIP163_Rc);
    }

    /* Synchronize with the device if required */
    if (fSync)
    {
        Rc = CfyELib_Device_Sync(DeviceId);
        if (Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("%s: synchronization failed for device %d, error %d\n",
                     __func__, DeviceId, Rc);
            CfyELib_Device_Unlock(DeviceId);
            return Rc;
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


/*-----------------------------------------------------------------------------
 * CfyE_MTT_EnableDisable
 */
CfyE_Status_t
CfyE_MTT_EnableDisable(
        const unsigned int DeviceId,
        const unsigned int MTTEnable,
        const unsigned int MTTDisable,
        const bool EnableSingle,
        const bool DisableSingle,
        const bool EnableAll,
        const bool DisableAll,
        const bool fSync)
{
    EIP163_Error_t EIP163_Rc;
    CfyE_Status_t Rc;

    LOG_INFO("\n %s \n", __func__);

    ADAPTER_EIP163_CHECK_INT_ATMOST(DeviceId, ADAPTER_EIP163_MAX_NOF_DEVICES - 1);

    CfyELib_Device_Lock(DeviceId);

    if (!CfyELib_Initialized_Check(DeviceId, __func__, true))
    {
        CfyELib_Device_Unlock(DeviceId);
        return CFYE_ERROR_INTERNAL;
    }

    LOG_INFO("\n\t EIP163_MTT_EnableDisable \n");

    EIP163_Rc = EIP163_MTT_EnableDisable(&CfyE_Devices[DeviceId]->IOArea,
                                  MTTEnable,
                                  MTTDisable,
                                  EnableSingle,
                                  DisableSingle,
                                  EnableAll,
                                  DisableAll);
    if (EIP163_Rc != EIP163_NO_ERROR)
    {
        LOG_CRIT("%s: Failed to enable/disable rules "
                 "for EIP-163 device %d (%s), error %d\n",
                 __func__,
                 DeviceId,
                 ADAPTER_EIP163_DEVICE_NAME(DeviceId),
                 EIP163_Rc);
    }

    /* Synchronize with the device if required */
    if (fSync)
    {
        Rc = CfyELib_Device_Sync(DeviceId);
        if (Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("%s: synchronization failed for device %d, error %d\n",
                     __func__, DeviceId, Rc);
            CfyELib_Device_Unlock(DeviceId);
            return Rc;
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


#endif
/* end of file adapter_cfye_rule.c */
