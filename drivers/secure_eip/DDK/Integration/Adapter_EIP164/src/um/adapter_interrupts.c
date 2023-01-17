/* adapter_interrupts.c
 *
 * Adapter module responsible for interrupt management in the Linux user-space
 * applications using the Interrupt Dispatcher API.
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

#include "adapter_interrupts.h"

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Default configuration */
#include "c_adapter_eip164.h"

#include "intdispatch_mgmt.h"   /* Interrupt Dispatcher API, Shutdown */
#include "intdispatch.h"        /* Interrupt Dispatcher API, the rest */

/* Driver Framework Basic Definitions API */
#include "basic_defs.h"

/* Driver Framework Device API */
#include "device_mgmt.h"        /* Device_Find */

/* Logging API */
#include "log.h"

/* EIP-201 Driver Library API */
#include "eip201.h"             /* Advanced Interrupt Controller */

/* Adapter Alloc API */
#include "adapter_alloc.h"      /* Adapter_Alloc()/_Free() */


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

#define ADAPTER_INT_MASK_ALL_SOURCES        0x3FFFFFF

typedef struct
{
    int                         nIRQ;
    Adapter_InterruptHandler_t  Function;
    IntDispatch_Handle_t        Handle;
    Device_Handle_t             DeviceIC;
    EIP201_Source_t             Sources;
} AdapterINT_Admin_t;

#define ADAPTER_INTERRUPT_ERROR_INTERNAL 0x1

/*----------------------------------------------------------------------------
 * Local variables
 */

static AdapterINT_Admin_t *
                volatile AdapterINT_Handlers[ADAPTER_INTERRUPTS_MAX_COUNT];

static const unsigned int AdapterINT_ICDevice_Count =
                                        ADAPTER_INTERRUPTS_MAX_COUNT;


/*----------------------------------------------------------------------------
 * AdapterINT_EIP201Sources_Get
 */
static inline uint32_t
AdapterINT_EIP201Sources_Get(
        const unsigned int RequestedEvents)
{
    /* One-to-one mapping from adapter interrupts events to EIP-201 sources */
    return (uint32_t)RequestedEvents;
}


/*----------------------------------------------------------------------------
 * AdapterINT_Events_Get
 */
static inline unsigned int
AdapterINT_Events_Get(
        const uint32_t Sources)
{
    /* One-to-one mapping from EIP-201 sources to adapter interrupts events */
    return (unsigned int)Sources;
}


/*----------------------------------------------------------------------------
 * AdapterINT_Interrupt_Dispatcher_CB
 */
static void
AdapterINT_Interrupt_Dispatcher_CB(
        void * Param_p)
{
    int nIRQ = *((int*)Param_p);
    unsigned int ICDeviceId = nIRQ;
    unsigned int HandlerId = ADAPTER_EIP164_INT_HANDLER_ID(ICDeviceId);

    LOG_INFO("%s invoked, IRQ %d\n", __func__, nIRQ);

    /* DeviceId is expected here as nIRQ */
    if (nIRQ < 0 || HandlerId >= AdapterINT_ICDevice_Count)
    {
        LOG_CRIT("%s: Failed, unsupported interrupt number %d\n",
                 __func__,
                 nIRQ);
        return;
    }

    /* continue only if we have been initialized */
    if (AdapterINT_Handlers[HandlerId] == NULL)
    {
        LOG_CRIT("%s: Failed, invalid while uninitialized\n", __func__);
        return;
    }

    if(AdapterINT_Handlers[HandlerId]->Function)
    {
        unsigned int EventMask = 0;

        /* Determine the interrupt sources here and store them in Flags */
        {
            EIP201_Status_t res201;
            EIP201_SourceBitmap_t Sources;

            LOG_INFO("\n\t\t EIP201_SourceStatus_ReadAllEnabled \n");

            /* read the active interrupts from EIP201 */
            res201 = EIP201_SourceStatus_ReadAllEnabledCheck(
                AdapterINT_Handlers[HandlerId]->DeviceIC,
                &Sources);
            if (res201 != EIP201_STATUS_SUCCESS)
            {
                LOG_CRIT("%s: Failed, "
                         "EIP201_SourceStatus_ReadAllEnabledCheck() error %d\n",
                         __func__,
                         res201);
            }


            LOG_INFO("\n\t\t EIP201_SourceMask_DisableSource \n");

            /* Disable these interrupt sources */
            res201 = EIP201_SourceMask_DisableSource(
                                     AdapterINT_Handlers[HandlerId]->DeviceIC,
                                     Sources);
            if (res201 != EIP201_STATUS_SUCCESS)
            {
                LOG_CRIT("%s: Failed, "
                         "EIP201_SourceMask_DisableSource() error %d\n",
                         __func__,
                         res201);
            }

            LOG_INFO("\n\t\t EIP201_Acknowledge \n");

            /* Clear these interrupt sources */
            res201 = EIP201_Acknowledge(
                              AdapterINT_Handlers[HandlerId]->DeviceIC,
                              Sources);
            if (res201 != EIP201_STATUS_SUCCESS)
            {
                LOG_CRIT("%s: Failed, EIP201_Acknowledge() error %d\n",
                         __func__,
                         res201);
            }

            Sources &= AdapterINT_Handlers[HandlerId]->Sources;
            if (Sources)
            {
                EventMask = AdapterINT_Events_Get(Sources);

                if (EventMask & ADAPTER_EIP164_INTERRUPTS_TRACEFILTER)
                {
                    Log_FormattedMessage("%s: Invoking for events 0x%08x\n",
                                         __func__,
                                         EventMask);
                }

                /* Invoke the callback */
                AdapterINT_Handlers[HandlerId]->Function(nIRQ, EventMask);
            }
        }
    }

    LOG_INFO("\n\t %s done \n", __func__);

    return;
}


/*----------------------------------------------------------------------------
 * Adapter_Interrupt_Enable
 */
int
Adapter_Interrupt_Enable(
        const int nIRQ,
        const unsigned int Flags)
{
    int res;
    unsigned int ICDeviceId = nIRQ;
    unsigned int HandlerId = ADAPTER_EIP164_INT_HANDLER_ID(ICDeviceId);

    LOG_INFO("\n\t %s \n", __func__);

    /* DeviceId is expected here as nIRQ */
    if (nIRQ < 0 || HandlerId >= AdapterINT_ICDevice_Count)
    {
        LOG_CRIT("%s: Failed, unsupported interrupt number %d\n",
                 __func__,
                 nIRQ);
        return ADAPTER_INTERRUPT_ERROR_INTERNAL;
    }

    /* continue only if we have been initialized */
    if (AdapterINT_Handlers[HandlerId] == NULL)
    {
        LOG_CRIT("%s: Failed, invalid while uninitialized\n", __func__);
        return ADAPTER_INTERRUPT_ERROR_INTERNAL;
    }

    /* Enable interrupt sources at the device */
    {
        EIP201_Status_t res201;
        AdapterINT_Handlers[HandlerId]->Sources =
                            AdapterINT_EIP201Sources_Get(Flags);

        LOG_INFO("\n\t\t EIP201_SourceMask_EnableSource \n");

        res201 = EIP201_SourceMask_EnableSource(
                                    AdapterINT_Handlers[HandlerId]->DeviceIC,
                                    AdapterINT_Handlers[HandlerId]->Sources);
        if (res201 != EIP201_STATUS_SUCCESS)
        {
            LOG_CRIT("%s: Failed, EIP201_SourceMask_EnableSource() error %d\n",
                     __func__,
                     res201);
            return res201;
        }
    }

    res = IntDispatch_Unmask(AdapterINT_Handlers[HandlerId]->Handle);
    if(res == 0)
    {
        LOG_INFO("%s: interrupt number %d enabled\n", __func__, nIRQ);
    }
    else
    {
        LOG_CRIT("%s: Failed, IntDispatch_Unmask error=%d\n", __func__, res);
        return ADAPTER_INTERRUPT_ERROR_INTERNAL;
    }

    LOG_INFO("\n\t %s done \n", __func__);

    return 0;
}


/*----------------------------------------------------------------------------
 * Adapter_Interrupt_Disable
 */
int
Adapter_Interrupt_Disable(
        const int nIRQ,
        const unsigned int Flags)
{
    int res;
    unsigned int ICDeviceId = nIRQ;
    unsigned int HandlerId = ADAPTER_EIP164_INT_HANDLER_ID(ICDeviceId);

    LOG_INFO("\n\t %s \n", __func__);

    /* DeviceId is expected here as nIRQ */
    if (nIRQ < 0 || HandlerId >= AdapterINT_ICDevice_Count)
    {
        LOG_CRIT("%s: Failed, unsupported interrupt number %d\n",
                 __func__,
                 nIRQ);
        return ADAPTER_INTERRUPT_ERROR_INTERNAL;
    }

    /* continue only if we have been initialized */
    if (AdapterINT_Handlers[HandlerId] == NULL)
    {
        LOG_CRIT("%s: Failed, invalid while uninitialized\n", __func__);
        return ADAPTER_INTERRUPT_ERROR_INTERNAL;
    }

    /* Enable interrupt sources at the device */
    {
        EIP201_Status_t res201;
        AdapterINT_Handlers[HandlerId]->Sources =
                                AdapterINT_EIP201Sources_Get(Flags);

        LOG_INFO("\n\t\t EIP201_SourceMask_EnableSource \n");

        res201 = EIP201_SourceMask_DisableSource(
                                    AdapterINT_Handlers[HandlerId]->DeviceIC,
                                    AdapterINT_Handlers[HandlerId]->Sources);
        if (res201 != EIP201_STATUS_SUCCESS)
        {
            LOG_CRIT("%s: Failed, EIP201_SourceMask_DisableSource() error %d\n",
                     __func__,
                     res201);
            return res201;
        }
    }

    res = IntDispatch_Mask(AdapterINT_Handlers[HandlerId]->Handle);
    if(res == 0)
    {
        LOG_INFO("%s: interrupt number %d disabled\n", __func__, nIRQ);
    }
    else
    {
        LOG_CRIT("%s: Failed, IntDispatch_Mmask error=%d\n", __func__, res);
        return ADAPTER_INTERRUPT_ERROR_INTERNAL;
    }
    LOG_INFO("\n\t %s done \n", __func__);

    return 0;
}


/*----------------------------------------------------------------------------
 * Adapter_Interrupt_EnabledStatus_Get
 */
int
Adapter_Interrupt_EnabledStatus_Get(
    const int nIRQ,
    unsigned int * Sources_p)
{
    unsigned int Sources;
    EIP201_Status_t res201;
    unsigned int ICDeviceId = nIRQ;
    unsigned int HandlerId = ADAPTER_EIP164_INT_HANDLER_ID(ICDeviceId);

    LOG_INFO("\n\t %s \n", __func__);
    *Sources_p = 0;

    /* DeviceId is expected here as nIRQ */
    if (nIRQ < 0 || HandlerId >= AdapterINT_ICDevice_Count)
    {
        LOG_CRIT("%s: Failed, unsupported interrupt number %d\n",
                 __func__,
                 nIRQ);
        return ADAPTER_INTERRUPT_ERROR_INTERNAL;
    }

    /* continue only if we have been initialized */
    if (AdapterINT_Handlers[HandlerId] == NULL)
    {
        LOG_CRIT("%s: Failed, invalid while uninitialized\n", __func__);
        return ADAPTER_INTERRUPT_ERROR_INTERNAL;
    }

    res201 = EIP201_SourceStatus_ReadAllEnabledCheck(
                                 AdapterINT_Handlers[HandlerId]->DeviceIC,
                                 &Sources);
    if (res201 != 0)
        return res201;

    LOG_INFO("\n\t %s done \n", __func__);

    *Sources_p =  AdapterINT_Events_Get(Sources);
    return 0;
}


/*----------------------------------------------------------------------------
 * Adapter_Interrupt_Clear
 */
int
Adapter_Interrupt_Clear(
        const int nIRQ,
        const unsigned int Flags)
{
    unsigned int ICDeviceId = nIRQ;
    unsigned int HandlerId = ADAPTER_EIP164_INT_HANDLER_ID(ICDeviceId);

    LOG_INFO("\n\t %s \n", __func__);

    /* DeviceId is expected here as nIRQ */
    if (nIRQ < 0 || HandlerId >= AdapterINT_ICDevice_Count)
    {
        LOG_CRIT("%s: Failed, unsupported interrupt number %d\n",
                 __func__,
                 nIRQ);
        return ADAPTER_INTERRUPT_ERROR_INTERNAL;
    }

    /* continue only if we have been initialized */
    if (AdapterINT_Handlers[HandlerId] == NULL)
    {
        LOG_CRIT("%s: Failed, invalid while uninitialized\n", __func__);
        return ADAPTER_INTERRUPT_ERROR_INTERNAL;
    }

    /* Enable interrupt sources at the device */
    {
        EIP201_Status_t res201;
        AdapterINT_Handlers[HandlerId]->Sources =
                                AdapterINT_EIP201Sources_Get(Flags);

        LOG_INFO("\n\t\t EIP201_SourceMask_EnableSource \n");

        res201 = EIP201_Acknowledge(
                                    AdapterINT_Handlers[HandlerId]->DeviceIC,
                                    AdapterINT_Handlers[HandlerId]->Sources);
        if (res201 != EIP201_STATUS_SUCCESS)
        {
            LOG_CRIT("%s: Failed, EIP201_Acknowledge() error %d\n",
                     __func__,
                     res201);
            return res201;
        }
    }

    return 0;
}


/*----------------------------------------------------------------------------
 * Adapter_Interrupts_Init
 */
int
Adapter_Interrupts_Init(
        const int nIRQ)
{
    unsigned int ICDeviceId = nIRQ;
    unsigned int HandlerId = ADAPTER_EIP164_INT_HANDLER_ID(ICDeviceId);

    LOG_INFO("\n\t %s \n", __func__);

    /* One interrupt line per one EIP-164 IC device */
    /* IC DeviceId is expected here as nIRQ */
    if (nIRQ < 0 || HandlerId >= AdapterINT_ICDevice_Count)
    {
        LOG_CRIT("%s: Failed, unsupported interrupt number %d\n",
                 __func__,
                 nIRQ);
        return ADAPTER_INTERRUPT_ERROR_INTERNAL;
    }

    if (AdapterINT_Handlers[HandlerId] == NULL)
    {
        int res;
        char * Devname_p = Device_GetName(ICDeviceId);
        AdapterINT_Admin_t * H_p;

        H_p = Adapter_Alloc(sizeof(AdapterINT_Admin_t));
        if (H_p == NULL)
        {
            LOG_CRIT("%s: Failed, out of memory for interrupt number %d\n",
                     __func__,
                     nIRQ);
            return ADAPTER_INTERRUPT_ERROR_INTERNAL;
        }

        /* find the EIP-201 device */
        H_p->DeviceIC = Device_Find(Devname_p);
        if (H_p->DeviceIC == NULL)
        {
            LOG_CRIT("%s: Failed to find IC device %s\n",
                     __func__,
                     Devname_p);
            Adapter_Free(H_p);
            return ADAPTER_INTERRUPT_ERROR_INTERNAL;
        }

        AdapterINT_Handlers[HandlerId] = H_p;

#ifndef ADAPTER_EIP164_DEV_INIT_DISABLE
        /* configure the EIP-201 */
        {
            EIP201_Status_t res201;
            const EIP201_SourceSettings_t Sources =
                        {BIT_31, EIP201_CONFIG_ACTIVE_LOW, false};

            LOG_INFO("\n\t\t EIP201_Initialize \n");

            res201 = EIP201_Initialize(H_p->DeviceIC, &Sources, 1);
            if (res201 != EIP201_STATUS_SUCCESS)
            {
                LOG_INFO("%s: Failed, EIP201_Initialize() error %d\n",
                         __func__,
                         res201);
                Adapter_Free(H_p);
                AdapterINT_Handlers[HandlerId] = NULL;
                return res201;
            }
        }
#endif

        res = IntDispatch_Initialize();
        if (res < 0)
        {
            LOG_CRIT("%s: Failed, IntDispatch_Initialize() returned %d\n",
                     __func__,
                     res);

            Adapter_Free(H_p);
            AdapterINT_Handlers[HandlerId] = NULL;
            return ADAPTER_INTERRUPT_ERROR_INTERNAL; /* failed */
        }

        H_p->Function     = NULL;
        H_p->nIRQ         = nIRQ;

        LOG_INFO("%s: Successfully initialized interrupt number %d (%s)\n",
                 __func__,
                 nIRQ,
                 Devname_p);
    }

    LOG_INFO("\n\t %s done \n", __func__);

    return 0; /* success */
}


/*----------------------------------------------------------------------------
 * Adapter_Interrupts_UnInit
 */
int
Adapter_Interrupts_UnInit(
        const int nIRQ)
{
    unsigned int ICDeviceId = nIRQ;
    unsigned int HandlerId = ADAPTER_EIP164_INT_HANDLER_ID(ICDeviceId);

    LOG_INFO("\n\t %s \n", __func__);

    /* DeviceId is expected here as nIRQ */
    if (nIRQ < 0 || HandlerId >= AdapterINT_ICDevice_Count)
    {
        LOG_CRIT("%s: Failed, unsupported interrupt number %d\n",
                 __func__,
                 nIRQ);
        return ADAPTER_INTERRUPT_ERROR_INTERNAL;
    }

    if (AdapterINT_Handlers[HandlerId])
    {
        unsigned int i, HandlerCount = 0;

        if (AdapterINT_Handlers[HandlerId]->Function)
        {
            IntDispatch_Unhook(AdapterINT_Handlers[HandlerId]->Handle);

            AdapterINT_Handlers[HandlerId]->Sources = 0;
            AdapterINT_Handlers[HandlerId]->Function = NULL;
        }

        AdapterINT_Handlers[HandlerId]->nIRQ = 0;

        Adapter_Free(AdapterINT_Handlers[HandlerId]);
        AdapterINT_Handlers[HandlerId] = NULL;

        for(i = 0; i < AdapterINT_ICDevice_Count; i++)
        {
            if (AdapterINT_Handlers[i])
                HandlerCount++;
        }

        if (HandlerCount == 0)
            IntDispatch_Shutdown();
    }

    LOG_INFO("\n\t %s done \n", __func__);

    return 0;
}


/*----------------------------------------------------------------------------
 * Adapter_Interrupt_SetHandler
 */
int
Adapter_Interrupt_SetHandler(
        const int nIRQ,
        Adapter_InterruptHandler_t HandlerFunction)
{
    int res;
    IntDispatch_Handle_t Handle;
    char * Devname_p;
    unsigned int ICDeviceId = nIRQ;
    unsigned int HandlerId = ADAPTER_EIP164_INT_HANDLER_ID(ICDeviceId);

    LOG_INFO("\n\t %s \n", __func__);

    /* DeviceId is expected here as nIRQ */
    if (nIRQ < 0 || HandlerId >= AdapterINT_ICDevice_Count)
    {
        LOG_CRIT("%s: Failed, unsupported interrupt number %d\n",
                 __func__,
                 nIRQ);
        return ADAPTER_INTERRUPT_ERROR_INTERNAL;
    }

    /* continue only if we have been initialized */
    if (AdapterINT_Handlers[HandlerId] == NULL)
    {
        LOG_CRIT("%s: Failed, invalid while uninitialized\n", __func__);
        return ADAPTER_INTERRUPT_ERROR_INTERNAL;
    }

    AdapterINT_Handlers[HandlerId]->Function = HandlerFunction;

    Devname_p = Device_GetName(ICDeviceId);

    res = IntDispatch_Hook(Devname_p,
                           AdapterINT_Interrupt_Dispatcher_CB,
                           &AdapterINT_Handlers[HandlerId]->nIRQ,
                           &Handle);
    if (res == 0)
    {
        LOG_INFO("%s: successfully hooked "
                 "HandlerFnc=%p for interrupt %s number %d\n",
                 __func__,
                 HandlerFunction,
                 Devname_p,
                 nIRQ);

        AdapterINT_Handlers[HandlerId]->Handle = Handle;
    }
    else
    {
        LOG_CRIT("%s: IntDispatch_Hook failed, "
                 "HandlerFnc=%p for interrupt %s number %d, error=%d\n",
                 __func__,
                 HandlerFunction,
                 Devname_p,
                 nIRQ,
                 res);

        AdapterINT_Handlers[HandlerId]->Function = NULL;
        return ADAPTER_INTERRUPT_ERROR_INTERNAL;
    }

    /* Leave the interrupt masked for now, reset the edge history */
    {
        EIP201_Status_t res201;

        LOG_INFO("\n\t\t EIP201_Acknowledge \n");

        res201 = EIP201_Acknowledge(AdapterINT_Handlers[HandlerId]->DeviceIC,
                                    ADAPTER_INT_MASK_ALL_SOURCES);
        if (res201 != EIP201_STATUS_SUCCESS)
        {
            LOG_CRIT("%s: Failed, EIP201_Acknowledge() error %d\n",
                     __func__,
                     res201);
            return res201;
        }
    }

    LOG_INFO("\n\t %s done \n", __func__);

    return 0;
}


/* end of file adapter_interrupts.c */
