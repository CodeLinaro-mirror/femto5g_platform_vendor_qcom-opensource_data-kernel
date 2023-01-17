/* c_intdispatch.h
 *
 * Default Interrupt Dispatcher configuration parameters.
 */

/*****************************************************************************
* Copyright (c) 2009-2021 by Rambus, Inc. and/or its subsidiaries.
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

#ifndef INCLUDE_GUARD_C_INTDISPATCH_UMDEVXS_H
#define INCLUDE_GUARD_C_INTDISPATCH_UMDEVXS_H

/* Top-level configuration parameters */
#include "cs_intdispatch.h"

/* Trace level for logging messages */
#ifndef INTDISPATCH_LOG_SEVERITY
#define INTDISPATCH_LOG_SEVERITY LOG_SEVERITY_INFO
#endif

/* Interrupt Controller device to request from Driver Framework (Device) */
/*#define INTDISPATCH_IC_DEVICE "EIP201" */

/* Enables synchronization for concurrent application execution contexts */
/* accessing the Interrupt Controller device */
/*#define INTDISPATCH_NOT_REENTRANT */

/* Maximum number of supported IC (Interrupt Controllers) devices */
#ifndef INTDISPATCH_MAX_NOF_RESOURCES
#define INTDISPATCH_MAX_NOF_RESOURCES   1
#endif

/* IC device configuration parameters */
#ifndef INTDISPATCH_RESOURCES
/*                                        Name    Source  Config */
#define INTDISPATCH_RESOURCES           { "null",  0,      0 }
#endif

/* Macro to calculate AIC device ID from its parent EIP-164 device ID */
#ifndef INTDISPATCH_ICDEV_ID
#error "INTDISPATCH_ICDEV_ID undefined"
#endif

/* Macro to calculate Interrup Dispatcher EIP-164 interrupt handler ID */
/* from EIP-201 AIC device ID */
#ifndef INTDISPATCH_INT_HANDLER_ID
#error "INTDISPATCH_INT_HANDLER_ID undefined"
#endif


#endif /* Include Guard */


/* end of file c_intdispatch.h */
