/* workerthread_linuxusermode.c
 *
 * Worker Thread implementation for Linux User Mode Applications.
 */

/*****************************************************************************
* Copyright (c) 2008-2021 by Rambus, Inc. and/or its subsidiaries.
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

/* Driver Framework Basic Defs API */
#include "basic_defs.h"

/* Worker thread API */
#include "workerthread.h"

/* System includes */
#include <semaphore.h>          /* sem_t, sem_init, destroy, wait */
#include <pthread.h>            /* pthread_t, pthread_create */

typedef struct
{
    WorkerThread_HandlerFuncPtr_t HandlerFuncPtr;
    void * HandlerParam_p;
    sem_t * ThreadSem_p;
    sem_t * AckSem_p;          /* used during creation */
    bool fStop;                /* true when worker thread must terminate */
    pthread_t ThreadId;
    void * Shadow_p;           /* Pointer to a shadow view */
} WorkerThread_ThreadArgs_t;


/*----------------------------------------------------------------------------
 * WorkerThread_MainLoop
 *
 * This is the worker thread main loop that is invoked from the worker thread
 * function.
 */
static void
WorkerThread_MainLoop(
        WorkerThread_ThreadArgs_t * const p)
{
    while(p)
    {
        /* acquire the worker thread semaphore */
        /* note: not using timeout version */
        sem_wait(p->ThreadSem_p);

        if (p->fStop)
            break;

        /* call the handler function */
        p->HandlerFuncPtr(p->HandlerParam_p);

    } /* (endless) while */
}


/*----------------------------------------------------------------------------
 * WorkerThread_pthread_Main
 *
 * This is the main function for a worker thread as required by SPAL.
 * The argument is a pointer to a set of arguments that we copy. We must then
 * signal
 */
static void *
WorkerThread_pthread_Main(
        void * arg)
{
    WorkerThread_ThreadArgs_t Args;
    sem_t Sem;

    {
        WorkerThread_ThreadArgs_t * const InOutArgs_p =
                            (WorkerThread_ThreadArgs_t *)arg;

        /* create the worker-thread semaphore */
        if (sem_init(&Sem, /*shared:*/0, /*initCount:*/0) != 0)
            return NULL;       /* ## RETURN ## */

        /* copy the worker thread arguments onto our local stack */
        Args = *InOutArgs_p;

        /* return a  pointer to our local copy of the semaphore */
        InOutArgs_p->ThreadSem_p = &Sem;

        Args.ThreadSem_p = &Sem;

        /* return a  pointer to our local copy (shadow) */
        InOutArgs_p->Shadow_p = &Args;

        /* signal the creator that we have copied the arguments */
        sem_post(InOutArgs_p->AckSem_p);
    }

    /* invoke the handler function */
    WorkerThread_MainLoop(&Args);

    sem_destroy(Args.ThreadSem_p);

    /* No call to pthread_exit() to avoid valgrind-detectable memory leaks */

    return NULL;
}


/*----------------------------------------------------------------------------
 * WorkerThread_Start
 */
bool
WorkerThread_Start(
        const char * Name_p,                            /* input */
        WorkerThread_HandlerFuncPtr_t HandlerFuncPtr,   /* input */
        void * const HandlerParam_p,                    /* input */
        WorkerThreadRef_t * const WorkerThreadRef_p)    /* output */
{
    WorkerThread_ThreadArgs_t Args;
    sem_t AckSem;
    pthread_t ThreadId;

    IDENTIFIER_NOT_USED(Name_p);

    /* create the thread-creation acknowledgment semaphore */
    if (sem_init(&AckSem, /*shared:*/0, /*initCount:*/0) != 0)
        return false;       /* ## RETURN ## */

    /* fill in the arguments block */
    Args.HandlerFuncPtr = HandlerFuncPtr;
    Args.HandlerParam_p = HandlerParam_p;
    Args.ThreadSem_p = NULL;    /* will be filled in by thread */
    Args.AckSem_p = &AckSem;
    Args.fStop = false;
    Args.Shadow_p = NULL;

    /* create the worker thread and provide the arguments (by reference) */
    if (pthread_create(
                &ThreadId,
                /*attr:*/ NULL,
                WorkerThread_pthread_Main,
                &Args) != 0)
    {
        /* destroy the semaphore again */
        sem_destroy(&AckSem);
        return false;       /* ## RETURN ## */
    }

    /* sleep on the Acknowledgment Semaphore to make sure that the worker */
    /* thread has started and copied the arguments. */
    /* this avoids us from reusing the stack on which the startup parameters */
    /* are placed before the worker thread has copied them. */
    sem_wait(&AckSem);

    /* destroy the temporary semaphore again */
    sem_destroy(&AckSem);

    /* check that worker thread reference is actually invalid */
    if (Args.Shadow_p == NULL || Args.ThreadSem_p == NULL)
    {
        void * p;

        pthread_cancel(ThreadId);
        pthread_join(ThreadId, &p);
        IDENTIFIER_NOT_USED(p);
        return false;       /* ## RETURN ## */
    }

    {
        WorkerThread_ThreadArgs_t * const InOutArgs_p =
                                (WorkerThread_ThreadArgs_t *)Args.Shadow_p;

        InOutArgs_p->ThreadId = ThreadId;
    }

    /* the worker thread reference we return is actually the shadow pointer */
    *WorkerThreadRef_p = Args.Shadow_p;

    /* it is now OK to release the memory for Args */

    return true;
}


/*----------------------------------------------------------------------------
 * WorkerThread_Signal
 *
 * Signals the worker thread. The pointer IS the handler to the semaphore
 * (WorkerThreadRef_t is a void *).
 * It is not possible to validate the pointer.
 */
void
WorkerThread_Signal(
        WorkerThreadRef_t WorkerThreadRef)    /* input */
{
    WorkerThread_ThreadArgs_t * const InOutArgs_p =
                            (WorkerThread_ThreadArgs_t *)WorkerThreadRef;

    if (InOutArgs_p)
        sem_post(InOutArgs_p->ThreadSem_p); /* Increase the semaphore */
}


/*----------------------------------------------------------------------------
 * WorkerThread_Stop
 */
void
WorkerThread_Stop(
        WorkerThreadRef_t WorkerThreadRef)    /* input */
{
    WorkerThread_ThreadArgs_t * const InOutArgs_p =
                        (WorkerThread_ThreadArgs_t *)WorkerThreadRef;

    if (InOutArgs_p)
    {
        void * p;
        pthread_t ThreadId = InOutArgs_p->ThreadId;

        InOutArgs_p->fStop = true; /* Terminate the worker thread */

        sem_post(InOutArgs_p->ThreadSem_p); /* Signal the worker thread */

        /* Wait till the worker thread terminates */
        pthread_join(ThreadId, &p);

        IDENTIFIER_NOT_USED(p);
    }
}


/* end of file workerthread_linuxusermode.c */
