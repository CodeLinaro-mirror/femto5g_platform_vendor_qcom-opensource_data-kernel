/* cs_lkm.h
 *
 * Top-level LKM configuration.
 */

/*****************************************************************************
* Copyright (c) 2016-2021 by Rambus, Inc. and/or its subsidiaries.
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

#ifndef CS_LKM_H
#define CS_LKM_H

#include "cs_umdevxs.h"

/*-----------------------------------------------------------------------------
 * Configuration parameters that may not be modified!
 */

/* Device identification required for implementation of PCI device driver */
#define LKM_DEVICE_ID             0x6018

/* Device vendor identification required for implementation of PCI device driver */
#define LKM_VENDOR_ID             0x10EE


/*-----------------------------------------------------------------------------
 * Configuration parameters that may be modified at top level configuration
 */

/* Enables strict argument checking for input parameters */
#define LKM_STRICT_ARGS_CHECK

/* Choose from LOG_SEVERITY_INFO, LOG_SEVERITY_WARN, LOG_SEVERITY_CRIT */
#define LKM_LOG_SEVERITY LOG_SEVERITY_CRIT

/* logging prefix */
#ifdef UMDEVXS_LOG_PREFIX
#define LKM_LOG_PREFIX UMDEVXS_LOG_PREFIX
#endif

/* Device name for Open Firmware platform. */
#define LKM_PLATFORM_DEVICE_NAME "sfxl-eip164"

#endif /* CS_LKM_H */


/* end of file cs_lkm.h */
