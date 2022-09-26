/* adapter_interrupts.c
 *
 * Adapter module responsible for interrupt management in the Linux user-space
 * applications using the Interrupt Dispatcher API.
 *
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

#include "adapter_interrupts.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Default configuration */
#include "c_adapter_eip164.h"

/* Driver Framework Basic Definitions API */
#include "basic_defs.h"

/* Driver Framework Device API */
#include "device_mgmt.h"             /* Device_GetReference */

/* Logging API */
#include "log.h"

/* EIP-201 Driver Library API */
#include "eip201.h"                  /* Advanced Interrupt Controller */

/* Linux Kernel API */
#include <linux/interrupt.h>       /* request_irq, free_irq, */
                                   /* DECLARE_TASKLET, tasklet_schedule, */
                                   /* IRQ_DISABLED */
#include <linux/irq.h>             /* IRQ_TYPE_LEVEL_HIGH */
#include <linux/irqreturn.h>       /* irqreturn_t */

/* Adapter Alloc API */
#include "adapter_alloc.h"      /* Adapter_Alloc()/_Free() */


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

#define ADAPTER_INT_MASK_ALL_SOURCES        0x3FFFFFF

#define ADAPTER_INT_EVENT_DROP_CLASS        0x01

#define ADAPTER_INT_REQUEST_IRQ_FLAGS       (IRQF_SHARED)

#define ADAPTER_INT_SANITY_CHECK_MAX_WAIT_LOOPS     10000000

#define ADAPTER_INT_SANITY_CHECK_IRQ        0

typedef struct
{
    Adapter_InterruptHandler_t  Function;
    Device_Handle_t             DeviceIC;
    EIP201_Source_t             Sources;
    struct tasklet_struct       Tasklet;
} AdapterINT_Admin_t;

#define ADAPTER_INTERRUPT_ERROR_INTERNAL 1

/*----------------------------------------------------------------------------
 * Local variables
 */

static AdapterINT_Admin_t *
                volatile AdapterINT_Handlers[ADAPTER_INTERRUPTS_MAX_COUNT];

static volatile bool AdapterINT_InterruptHasOccurred = false;

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
 * AdapterINT_OSIrqFromAdapterIrq_Get
 */
static inline int
AdapterINT_OSIrqFromAdapterIrq_Get(
        const int AdapterIrq)
{
    /* One-to-one mapping from adapter interrupt events to OS interrupts (irq) */
    /* Note: this must be customized for a specific HW platform. */
    /*       Also some OS'es differentiate between physical and virtual */
    /*       interrupts. */
    return (int)AdapterIrq;
}


/*----------------------------------------------------------------------------
 * AdapterINT_AdapterIrqFromOSIrq_Get
 */
static inline int
AdapterINT_AdapterIrqFromOSIrq_Get(
        const int OSIrq)
{
    /* One-to-one mapping from OS interrupts (irq) to adapter interrupt events */
    /* Note: this must be customized for a specific HW platform. */
    return (unsigned int)OSIrq;
}


/*-----------------------------------------------------------------------------
 * AdapterINT_SanityCheckHandler
 */
static void
AdapterINT_SanityCheckHandler(
        const int nIRQ,
        const unsigned int Flags)
{
    LOG_INFO("%s: handler called\n", __func__);

    AdapterINT_InterruptHasOccurred = true;
}


/*----------------------------------------------------------------------------
 * AdapterINT_CommonTasklet
 *
 * This handler is scheduled in the top-halve interrupt handler.
 * The data parameter is the IRQ value (from adapter_interrupts.h) for that
 * specific interrupt source.
 */
static void
AdapterINT_CommonTasklet(
        unsigned long data)
{
    int nIRQ = (int)data; /* Expect DeviceId here */
    unsigned int ICDeviceId = nIRQ;
    unsigned int HandlerId = ADAPTER_EIP164_INT_HANDLER_ID(ICDeviceId);

    LOG_INFO("%s: IRQ %d tasklet invoked\n", __func__, nIRQ);

    if (nIRQ < 0 || HandlerId >= AdapterINT_ICDevice_Count ||
        AdapterINT_Handlers[HandlerId] == NULL)
    {
        LOG_CRIT("%s: Failed, unsupported interrupt number %d\n",
                 __func__,
                 nIRQ);
        return;
    }

    if(AdapterINT_Handlers[HandlerId]->Function)
    {
        unsigned int EventMask = 0;

        /* Determine the interrupt sources here and store them in Flags */
        {
            EIP201_Status_t res201;
            EIP201_SourceBitmap_t Sources;

            /* read the active interrupts from EIP-201 */
            res201 = EIP201_SourceStatus_ReadAllRawCheck(
                         AdapterINT_Handlers[HandlerId]->DeviceIC,
                         &Sources);

            if (res201 != EIP201_STATUS_SUCCESS)
            {
                LOG_CRIT("%s: Failed, EIP201_Acknowledge()=%d\n",
                         __func__,
                         res201);
            }

            /* Clear these interrupt sources */
            res201 = EIP201_Acknowledge(AdapterINT_Handlers[HandlerId]->DeviceIC,
                                        Sources);
            if (res201 != EIP201_STATUS_SUCCESS)
            {
                LOG_CRIT("%s: Failed, EIP201_Acknowledge()=%d\n",
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
}


/*----------------------------------------------------------------------------
 * AdapterINT_TopHalfHandler
 *
 * This is the interrupt handler function call by the kernel when the hooked
 * interrupt is active.
 * Schedule a bottom-half handler. This handler invokes the installed handlers.
 */
static irqreturn_t
AdapterINT_TopHalfHandler(
        int irq,
        void * dev_id)
{
    IDENTIFIER_NOT_USED(dev_id);

    LOG_INFO("%s: interrupt number %d\n", __func__, irq);

    if (irq < 0)
        return IRQ_NONE;

    /* Schedule bottom-half handler */
    {
        int nIRQ;
        unsigned int ICDeviceId, HandlerId;

        /* Translate the OS-specific interrupt number to Adapter IRQ */
        nIRQ = AdapterINT_AdapterIrqFromOSIrq_Get(irq);

        ICDeviceId = nIRQ;
        HandlerId = ADAPTER_EIP164_INT_HANDLER_ID(ICDeviceId);

        /* Verify the Adapter IRQ */
        if (nIRQ < 0 || HandlerId >= AdapterINT_ICDevice_Count)
        {
            LOG_CRIT("%s: Failed, unknown interrupt number %d\n",
                     __func__,
                     nIRQ);
            return IRQ_NONE;
        }

        /* Disable the device interrupts to avoid spinning */
        {
            EIP201_Status_t res201;
            EIP201_SourceBitmap_t Sources;

            /* read the active interrupts from EIP-201 */
            res201 = EIP201_SourceStatus_ReadAllEnabledCheck(
                            AdapterINT_Handlers[HandlerId]->DeviceIC,
                            &Sources);
            if (res201 != EIP201_STATUS_SUCCESS)
            {
                LOG_CRIT("%s: Failed, "
                         "EIP201_SourceStatus_ReadAllEnbaledCheck() error %d\n",
                         __func__,
                         res201);
            }

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
        }

        tasklet_schedule(&AdapterINT_Handlers[HandlerId]->Tasklet);
    }

    LOG_INFO("%s: bottom-half is scheduled\n", __func__);

    return IRQ_HANDLED;
}


/*-----------------------------------------------------------------------------
 * AdapterINT_SanityCheck
 *
 * Install a temporary handler for an interrupt and force that interrupt.
 * Check that the interrupt does occur.
 *
 * Return true if the sanity check passes, false if it fails.
 *
 */
static bool
AdapterINT_SanityCheck(void)
{
    int i;
    EIP201_SourceBitmap_t Sources =
            AdapterINT_EIP201Sources_Get(ADAPTER_INT_EVENT_DROP_CLASS);

    Adapter_Interrupt_SetHandler(ADAPTER_INT_SANITY_CHECK_IRQ,
                                 AdapterINT_SanityCheckHandler);

    Adapter_Interrupt_Enable(ADAPTER_INT_SANITY_CHECK_IRQ,
                             ADAPTER_INT_EVENT_DROP_CLASS);

    AdapterINT_InterruptHasOccurred = false;

    /* By changing from rising to falling edge, the edge detection logic */
    /* will detect an edge, so the interrupt will be triggered. */
    EIP201_Config_Change(
            AdapterINT_Handlers[ADAPTER_INT_SANITY_CHECK_IRQ]->DeviceIC,
            Sources,
            EIP201_CONFIG_RISING_EDGE);

    /* Restore the interrupt polarity to normal. */
    EIP201_Config_Change(
            AdapterINT_Handlers[ADAPTER_INT_SANITY_CHECK_IRQ]->DeviceIC,
            Sources,
            EIP201_CONFIG_FALLING_EDGE);

    /* Restore the interrupt polarity to normal. */
    EIP201_Config_Change(
            AdapterINT_Handlers[ADAPTER_INT_SANITY_CHECK_IRQ]->DeviceIC,
            Sources,
            EIP201_CONFIG_ACTIVE_LOW);

    /* Wait for the interrupt to occur */
    for (i = 0; i < ADAPTER_INT_SANITY_CHECK_MAX_WAIT_LOOPS; i++)
    {
        if(AdapterINT_InterruptHasOccurred)
            break;
    }

    Adapter_Interrupt_SetHandler(ADAPTER_INT_SANITY_CHECK_IRQ, NULL);

    return AdapterINT_InterruptHasOccurred;
}


/*----------------------------------------------------------------------------
 * Adapter_Interrupt_Enable
 */
int
Adapter_Interrupt_Enable(
        const int nIRQ,
        const unsigned int Flags)
{
    unsigned int ICDeviceId = nIRQ;
    unsigned int HandlerId = ADAPTER_EIP164_INT_HANDLER_ID(ICDeviceId);

    LOG_INFO("\n\t %s \n", __func__);

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
    unsigned int ICDeviceId = nIRQ;
    unsigned int HandlerId = ADAPTER_EIP164_INT_HANDLER_ID(ICDeviceId);

    LOG_INFO("\n\t %s \n", __func__);

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

        LOG_INFO("\n\t\t EIP201_SourceMask_DisableSource \n");

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

    LOG_INFO("\n\t %s done \n", __func__);

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

    /* Acknowledge interrupt sources at the device */
    {
        EIP201_Status_t res201;

        AdapterINT_Handlers[HandlerId]->Sources =
                                AdapterINT_EIP201Sources_Get(Flags);

        LOG_INFO("\n\t\t EIP201_Acknowledge \n");

        res201 = EIP201_Acknowledge(AdapterINT_Handlers[HandlerId]->DeviceIC,
                                    AdapterINT_Handlers[HandlerId]->Sources);
        if (res201 != EIP201_STATUS_SUCCESS)
        {
            LOG_CRIT("%s: Failed, EIP201_Acknowledge() error %d\n",
                     __func__,
                     res201);
            return res201;
        }
    }

    LOG_INFO("\n\t %s done \n", __func__);

    return ADAPTER_INTERRUPT_ERROR_INTERNAL;
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
    unsigned int ICDeviceId = nIRQ;
    unsigned int HandlerId = ADAPTER_EIP164_INT_HANDLER_ID(ICDeviceId);
    EIP201_Status_t res201;

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
    if (res201 != EIP201_STATUS_SUCCESS)
    {
        LOG_CRIT("%s: Failed, EIP201_SourceStatus_ReadAllEnabled() error %d\n",
                 __func__,
                 res201);
        return res201;
    }

    LOG_INFO("\n\t %s done \n", __func__);

    *Sources_p = AdapterINT_Events_Get(Sources);
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
        AdapterINT_Admin_t * H_p;
        struct device * Device_p;
        char * Devname_p = Device_GetName(ICDeviceId);

        /* Get device reference for this resource */
        Device_p = Device_GetReference(NULL, NULL);

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
            return ADAPTER_INTERRUPT_ERROR_INTERNAL;
        }

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
                return res201;
            }
        }
#endif

        H_p->Function = NULL;

        AdapterINT_Handlers[HandlerId] = H_p;

        /* Initialize tasklet */
        {
            tasklet_init(&AdapterINT_Handlers[HandlerId]->Tasklet,
                         AdapterINT_CommonTasklet,
                         nIRQ);
        }

        /* Hook the OS interrupt */
        res = request_irq(AdapterINT_OSIrqFromAdapterIrq_Get(nIRQ),
                          AdapterINT_TopHalfHandler,
                          ADAPTER_INT_REQUEST_IRQ_FLAGS,
                          ADAPTER_EIP164_DRIVER_NAME,
                          Device_p);
        if (res)
        {
            LOG_CRIT("%s: Failed, request_irq()=%d\n", __func__, res);

            LOG_INFO("\n\t\t EIP201_SourceMask_DisableSource \n");

            EIP201_SourceMask_DisableSource(
                    H_p->DeviceIC,
                    AdapterINT_EIP201Sources_Get(ADAPTER_INT_MASK_ALL_SOURCES));

            return ADAPTER_INTERRUPT_ERROR_INTERNAL;
        }
        else if (!AdapterINT_SanityCheck())
        {
            LOG_CRIT("%s: Failed, Sanity check\n", __func__);

            LOG_INFO("\n\t\t EIP201_SourceMask_DisableSource \n");

            EIP201_SourceMask_DisableSource(
                   H_p->DeviceIC ,
                   AdapterINT_EIP201Sources_Get(ADAPTER_INT_MASK_ALL_SOURCES));

            free_irq(AdapterINT_OSIrqFromAdapterIrq_Get(nIRQ), Device_p);
            return ADAPTER_INTERRUPT_ERROR_INTERNAL;
        }
        else
        {
            LOG_INFO("%s: Successfully hooked IRQ %d\n", __func__, nIRQ);
        }

        LOG_INFO("%s: Successfully initialized IRQ %d (%s)\n",
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
        struct device * Device_p;

        /* Get device reference for this resource */
        Device_p = Device_GetReference(NULL, NULL);

        if (AdapterINT_Handlers[HandlerId]->Function)
        {
            AdapterINT_Handlers[HandlerId]->Sources = 0;
            AdapterINT_Handlers[HandlerId]->Function = NULL;
        }

        tasklet_kill(&AdapterINT_Handlers[HandlerId]->Tasklet);

        /* Unhook the OS interrupt */
        free_irq(AdapterINT_OSIrqFromAdapterIrq_Get(nIRQ), Device_p);

        Adapter_Free(AdapterINT_Handlers[HandlerId]);
        AdapterINT_Handlers[HandlerId] = NULL;
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
    if (AdapterINT_Handlers[HandlerId])
    {
        LOG_CRIT("%s: Failed, invalid while uninitialized\n", __func__);
        return ADAPTER_INTERRUPT_ERROR_INTERNAL;
    }

    AdapterINT_Handlers[HandlerId]->Function = HandlerFunction;

    /* Leave the interrupt masked for now, reset the edge history */
    {
        EIP201_Status_t res201;

        LOG_INFO("\n\t\t EIP201_Acknowledge \n");

        res201 = EIP201_Acknowledge(
                AdapterINT_Handlers[HandlerId]->DeviceIC,
                AdapterINT_EIP201Sources_Get(ADAPTER_INT_MASK_ALL_SOURCES));
        if (res201 != EIP201_STATUS_SUCCESS)
        {
            LOG_CRIT("%s: Failed, EIP201_Acknowledge() erro %d\n",
                     __func__,
                     res201);
            return res201;
        }
    }

    LOG_INFO("\n\t %s done \n", __func__);

    return 0;
}


/* end of file adapter_interrupts.c */
