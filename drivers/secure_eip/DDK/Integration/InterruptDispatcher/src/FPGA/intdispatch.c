/* intdispatch.c
 *
 * The Interrupt Dispatcher SW module dispatches these to the interested
 * parties in the Linux user-space.
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

#include "intdispatch_mgmt.h"        /* the API to implement, part 1 */
#include "intdispatch.h"             /* the API to implement, part 2 */


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Default configuration */
#include "c_intdispatch.h"   /* mapping of names to sources */

/* UMDevXS Proxy API */
#include "umdevxsproxy_interrupt.h"  /* interrupt support */
#include "umdevxsproxy_device.h"     /* for INTC access */

/* Driver Framework Device API */
#include "device_mgmt.h"             /* Device_GetReference, Device_Find */

/* Worker Thread API */
#include "workerthread.h"

/* Logging API */
#ifdef INTDISPATCH_LOG_SEVERITY
#define LOG_SEVERITY_MAX  INTDISPATCH_LOG_SEVERITY
#else
#define LOG_SEVERITY_MAX  LOG_SEVERITY_CRIT
#endif
#include "log.h"

/* Driver Framework Basic Definitions API */
#include "basic_defs.h"              /* NULL, inline */

/* Driver Framework CLib API */
#include "clib.h"                    /* strcmp */

/* Adapter Alloc */
#include "adapter_alloc.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

typedef struct
{
    int  Id;
    bool fIsHooked;
    bool fShutdown;
    void * Arg_p;
    IntDispatch_Callback_t CBFunc_p;
    WorkerThreadRef_t WTRef;
} IntDispatchLib_HookAdmin_t;

typedef void (* IntDispatchLib_HandlerFunc_t)(void * Arg_p);


/*----------------------------------------------------------------------------
 * IntDispatcherLib_HandlerFunc
 *
 * This function is called by the worker thread library every time it is
 * signaled. We never return from this function and instead use it its
 * execution context.
 *
 * We wait for interrupts reported by the kernel driver by calling the
 * UMDevXS Proxy to wait for such an events. The proxy call will block until
 * the interrupt or the timeout occurs.
 *
 * This function then calls the interrupt dispatcher to check
 * for interrupts and call the registered callback functions.
 */
static void
IntDispatcherLib_HandlerFunc(
        void * const HandlerParam_p);


/*----------------------------------------------------------------------------
 * Local variables
 */

static IntDispatchLib_HookAdmin_t *
            volatile IntDispatchLib_HookAdmin[INTDISPATCH_MAX_NOF_RESOURCES];

static const int IntDispatchLib_IntCount = INTDISPATCH_MAX_NOF_RESOURCES;

static bool IntDispatchLib_Initialized;


/*----------------------------------------------------------------------------
 * IntDispatcherLib_AdminIndex2Handle
 */
#define IntDispatchLib_AdminIndex2Handle(i) ((int)i)


/*----------------------------------------------------------------------------
 * IntDispatcherLib_Handle2AdminIndex
 *
 * Return the index or <0 on error.
 */
static inline int
IntDispatchLib_Handle2AdminIndex(
        IntDispatch_Handle_t Handle)
{
    int AdminIndex = Handle;

    if (AdminIndex >= 0 && AdminIndex < IntDispatchLib_IntCount)
        return AdminIndex;

    return -1;
}


/*----------------------------------------------------------------------------
 * IntDispatcherLib_HandlerFunc
 */
static void
IntDispatcherLib_HandlerFunc(
        void * const HandlerParam_p)
{
    int res;
    IntDispatchLib_HookAdmin_t * p;
    int HandlerId = *((int*)HandlerParam_p);

    if (HandlerId < 0 || HandlerId >= IntDispatchLib_IntCount)
    {
        LOG_CRIT("%s: Invalid index  %d for handler, skipping it\n",
                 __func__,
                 HandlerId);
        return;
    }

    p = IntDispatchLib_HookAdmin[HandlerId];

    if (p == NULL)
    {
        LOG_CRIT("%s: Invalid handler %d, not hooked, skipping it\n",
                 __func__,
                 HandlerId);
        return;
    }

    LOG_INFO("%s() invoked, index %d\n", __func__, HandlerId);

    do
    {
        if (p->fShutdown)
            break;

        res = UMDevXSProxy_Interrupt_WaitWithTimeout(/*timeout_ms:*/500,
                                                     HandlerId);
        if (res == 0)
        {
            /* interrupt (not timeout) */
            if (p->fIsHooked)
            {
                p->CBFunc_p(p->Arg_p);
            }
            else
            {
                LOG_WARN("IntDispatcher: failed to dispatch for handler %d\n",
                         HandlerId);
            }
        }
    }
    while(res >= 0);
}


/*----------------------------------------------------------------------------
 * IntDispatch_Initialize
 *
 * This function creates the interrupt dispatcher context, which will call
 * the UMDevXS Proxy to receive interrupt events from the kernel domain.
 */
int
IntDispatch_Initialize(void)
{
    if (IntDispatchLib_Initialized)
        return 0; /* success */

    IntDispatchLib_Initialized = true;

    return 0; /* success */
}


/*----------------------------------------------------------------------------
 * IntDispatch_Shutdown
 */
int
IntDispatch_Shutdown(void)
{
    unsigned int i;

    for (i = 0; i < INTDISPATCH_MAX_NOF_RESOURCES; i++)
    {
        Adapter_Free(IntDispatchLib_HookAdmin[i]);
        IntDispatchLib_HookAdmin[i] = NULL;
    }

    IntDispatchLib_Initialized = false;

    return 0;
}


/*----------------------------------------------------------------------------
 * IntDispatch_Hook
 */
int
IntDispatch_Hook(
        const char * const szIntName_p,
        IntDispatch_Callback_t CBFunc,
        void * Arg_p,
        IntDispatch_Handle_t * const Handle_p)
{
    Device_Handle_t Device;

    /* ensure we are initialized */
    if (!IntDispatchLib_Initialized)
    {
        LOG_CRIT("%s: not initialized yet\n", __func__);
        return -99;
    }

    Device = Device_Find(szIntName_p);

    if (Device == NULL || szIntName_p == NULL || CBFunc == NULL ||
        Handle_p == NULL)
    {
        LOG_CRIT("%s: invalid input for interrupt %s\n",
                __func__,
                 szIntName_p);
        return -1;
    }

    /* initialize the output parameters */
    *Handle_p = 0;

    {
        unsigned int HandlerId =
                    INTDISPATCH_INT_HANDLER_ID(Device_GetIndex(Device));
        IntDispatchLib_HookAdmin_t * p =
                        IntDispatchLib_HookAdmin[HandlerId];

        if (p)
        {
            LOG_WARN("%s: Interrupt %s is already hooked!\n",
                     __func__,
                     szIntName_p);
            return -2;
        }

        p = Adapter_Alloc(sizeof(IntDispatchLib_HookAdmin_t));
        if (p == NULL)
        {
            LOG_CRIT("%s: out of memory for interrupt %s\n",
                     __func__,
                     szIntName_p);
            return -3;
        }

        /* store the configuration */
        p->Arg_p = Arg_p;
        p->CBFunc_p = CBFunc;
        p->fIsHooked = true;
        p->fShutdown = false;
        p->Id = HandlerId;

        /* create the worker thread context */
        /* that will wait for kernel events using UMDevXS Proxy */
        if (!WorkerThread_Start(
                        "Interrupt Dispatcher",
                        IntDispatcherLib_HandlerFunc,
                        (void * const)&p->Id,
                        (WorkerThreadRef_t * const)&p->WTRef))
        {
            LOG_CRIT("%s: Failed to start "
                     "worker thread for interrupt %s\n",
                     __func__,
                     szIntName_p);
            Adapter_Free(p);
            return -4;
        }

        /* immediately get the handler function called */
        WorkerThread_Signal(p->WTRef);

        /* fill in the output parameter */
        *Handle_p = IntDispatchLib_AdminIndex2Handle(HandlerId);

        IntDispatchLib_HookAdmin[HandlerId] = p;
    }

    return 0; /* success */
}


/*----------------------------------------------------------------------------
 * IntDispatch_Unhook
 */
int
IntDispatch_Unhook(
        const IntDispatch_Handle_t Handle)
{
    int HandlerId = IntDispatchLib_Handle2AdminIndex(Handle);

    /* ensure we are initialized */
    if (!IntDispatchLib_Initialized)
    {
        LOG_CRIT("%s: not initialized yet\n", __func__);
        return -99;
    }

    if (HandlerId < 0 || HandlerId >= IntDispatchLib_IntCount ||
        IntDispatchLib_HookAdmin[HandlerId] == NULL)
    {
        LOG_CRIT("%s: invalid handle %d\n", __func__, HandlerId);
        return -1;
    }

    {
        IntDispatchLib_HookAdmin_t * const p =
                                IntDispatchLib_HookAdmin[HandlerId];

        if (p->fIsHooked == false)
            return -2;

        /* disable the interrupt source */
        if (IntDispatch_Mask(Handle) < 0)
            return -3;

        /* remove the callback details */
        p->Arg_p = NULL;
        p->CBFunc_p = NULL;
        p->fIsHooked = false;
        p->fShutdown = true;
        p->Id = -1;

        WorkerThread_Stop(p->WTRef);

        p->WTRef = NULL;

        Adapter_Free(p);
        IntDispatchLib_HookAdmin[HandlerId] = NULL;
    }

    return 0; /* success */
}


/*----------------------------------------------------------------------------
 * IntDispatch_Mask
 */
int
IntDispatch_Mask(
        const IntDispatch_Handle_t Handle)
{
    int HandlerId;

    /* ensure we are initialized */
    if (!IntDispatchLib_Initialized)
    {
        LOG_CRIT("%s: not initialized yet\n", __func__);
        return -99;
    }

    HandlerId = IntDispatchLib_Handle2AdminIndex(Handle);

    if (HandlerId < 0 || HandlerId >= IntDispatchLib_IntCount ||
        IntDispatchLib_HookAdmin[HandlerId] == NULL)
    {
        LOG_CRIT("%s: invalid handle %d\n", __func__, HandlerId);
        return -1;
    }

    return 0; /* success */
}


/*----------------------------------------------------------------------------
 * IntDispatch_Unmask
 */
int
IntDispatch_Unmask(
        const IntDispatch_Handle_t Handle)
{
    int HandlerId;

    /* ensure we are initialized */
    if (!IntDispatchLib_Initialized)
    {
        LOG_CRIT("%s: not initialized yet\n", __func__);
        return -99;
    }

    HandlerId = IntDispatchLib_Handle2AdminIndex(Handle);

    if (HandlerId < 0 || HandlerId >= IntDispatchLib_IntCount ||
        IntDispatchLib_HookAdmin[HandlerId] == NULL)
    {
        LOG_CRIT("%s: invalid handle %d\n", __func__, HandlerId);
        return -1;
    }

    return 0; /* success */
}


/* end of file intdispatch.c */
