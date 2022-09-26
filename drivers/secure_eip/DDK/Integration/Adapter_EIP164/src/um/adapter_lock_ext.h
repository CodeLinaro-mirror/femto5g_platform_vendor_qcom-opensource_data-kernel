/* adapter_lock_ext.h
 *
 * Adapter concurrency (locking) management
 * extensions for Linux user-space
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

#ifndef INCLUDE_GUARD_ADAPTER_LOCK_EXT_H
#define INCLUDE_GUARD_ADAPTER_LOCK_EXT_H

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Linux User API */
#include <pthread.h>        /* pthread_mutex_* */


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

#define ADAPTER_LOCK_DEFINE(Lock)   \
                pthread_mutex_t Lock = PTHREAD_MUTEX_INITIALIZER

/* Lock structure, so it can be part of another structure or array */
typedef pthread_mutex_t Adapter_Lock_Struct_t;

/* Initializer for elements of Adapter_Lock_Struct_t */
#define ADAPTER_LOCK_INITIALIZER PTHREAD_MUTEX_INITIALIZER


#endif /* INCLUDE_GUARD_ADAPTER_LOCK_EXT_H */


/* end of file adapter_lock_ext.h */
