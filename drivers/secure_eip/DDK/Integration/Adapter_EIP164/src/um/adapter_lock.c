/* adapter_lock.c
 *
 * Adapter concurrency (locking) management
 * Linux user-space implementation
 *
 */

/*****************************************************************************
* Copyright (c) 2013-2021 by Rambus, Inc. and/or its subsidiaries.
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

/* Adapter locking API */
#include "adapter_lock.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Driver Framework Basic Definitions API */
#include "basic_defs.h"     /* IDENTIFIER_NOT_USED */

/* Adapter Lock Internal API */
#include "adapter_lock_internal.h"

/* Adapter Memory Allocation API */
#include "adapter_alloc.h"

/* Logging API */
#undef LOG_SEVERITY_MAX
#define LOG_SEVERITY_MAX    LOG_SEVERITY_WARN

/* Logging API */
#include "log.h"

/* Linux User API */
#include <pthread.h>        /* pthread_mutex_* */


/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * Adapter_Lock_Alloc
 */
Adapter_Lock_t
Adapter_Lock_Alloc(void)
{
    pthread_mutex_t * Lock_p;

    Lock_p = Adapter_Alloc(sizeof(pthread_mutex_t));
    if (Lock_p == NULL)
        return Adapter_Lock_NULL;

    Log_FormattedMessage("%s: Lock = pthread_mutex\n", __func__);

    pthread_mutex_init(Lock_p, NULL);

    return Lock_p;
}


/*----------------------------------------------------------------------------
 * Adapter_Lock_Free
 */
void
Adapter_Lock_Free(Adapter_Lock_t Lock)
{
    pthread_mutex_destroy((pthread_mutex_t*)Lock);

    Adapter_Free((void*)Lock);
}


/*----------------------------------------------------------------------------
 * Adapter_Lock_Acquire
 */
void
Adapter_Lock_Acquire(
        Adapter_Lock_t Lock,
        unsigned long * Flags)
{
    IDENTIFIER_NOT_USED(Flags);

    pthread_mutex_lock((pthread_mutex_t*)Lock);
}


/*----------------------------------------------------------------------------
 * Adapter_Lock_Release
 */
void
Adapter_Lock_Release(
        Adapter_Lock_t Lock,
        unsigned long * Flags)
{
    IDENTIFIER_NOT_USED(Flags);

    pthread_mutex_unlock((pthread_mutex_t*)Lock);
}


/* end of file adapter_lock.c */
