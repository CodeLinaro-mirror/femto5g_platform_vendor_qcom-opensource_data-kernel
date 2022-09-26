/* cs_intdispatch_umdevxs.h
 *
 * Configuration Settings for the Interrupt Dispatcher.
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

#ifndef INCLUDE_GUARD_CS_INTDISPATCH_UMDEVXS_H
#define INCLUDE_GUARD_CS_INTDISPATCH_UMDEVXS_H

#include "cs_driver.h"
#include "cs_intdispatch_umdevxs_ext.h"

/* logging level for Interrupt Dispatcher */
/* Choose from LOG_SEVERITY_INFO, LOG_SEVERITY_WARN, LOG_SEVERITY_CRIT */
#undef LOG_SEVERITY_MAX
#ifdef DRIVER_PERFORMANCE
#define INTDISPATCH_LOG_SEVERITY  LOG_SEVERITY_CRITICAL
#else
#define INTDISPATCH_LOG_SEVERITY  LOG_SEVERITY_WARN
#endif

#if defined(DRIVER_MAX_NOF_EIP163_IC_DEVICES) && defined(DRIVER_MAX_NOF_EIP164_IC_DEVICES)
#define INTDISPATCH_MAX_NOF_RESOURCES   (DRIVER_MAX_NOF_EIP163_IC_DEVICES + \
                                         DRIVER_MAX_NOF_EIP164_IC_DEVICES)
#else
#error "DRIVER_MAX_NOF_EIP16[3|4]_IC_DEVICES not defined"
#endif

/* Calculate AIC device ID from its parent EIP-164 device ID */
#define INTDISPATCH_ICDEV_ID         DRIVER_ICDEV_ID

/* Calculate EIP-164 interrupt handler ID from EIP-201 AIC device ID */
#define INTDISPATCH_INT_HANDLER_ID   DRIVER_INT_HANDLER_ID


#endif /* Include Guard */


/* end of file cs_intdispatch_umdevxs.h */
