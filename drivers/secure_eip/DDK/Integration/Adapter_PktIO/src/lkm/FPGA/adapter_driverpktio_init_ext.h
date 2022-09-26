/* adapter_driverpktio_init_ext.h
 *
 * Linux kernel specific Adapter extensions
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
 * This module uses (requires) the following interface(s):
 */

/* Top-level Adapter configuration */
#include "c_adapter_pktio.h"

/* Linux Kernel API */
#include <linux/init.h>     /* module_init, module_exit */
#include <linux/module.h>   /* EXPORT_SYMBOL */


/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

#include "api_pktio.h"             /* Packet I/O API */

MODULE_LICENSE(ADAPTER_PKTIO_LICENSE);


/* Driver Init API */
module_init(PktIO_Init);

/* Packet IO API */
EXPORT_SYMBOL(PktIO_Packet_Put);
EXPORT_SYMBOL(PktIO_Packet_Get);


/* end of file adapter_driverpktio_init_ext.h */
