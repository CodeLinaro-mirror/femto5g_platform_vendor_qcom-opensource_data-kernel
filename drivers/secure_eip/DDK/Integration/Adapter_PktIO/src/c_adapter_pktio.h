/* c_adapter_pktio.h
 *
 * Default PktIO configuration
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

#ifndef INCLUDE_GUARD_C_ADAPTER_PKTIO_H
#define INCLUDE_GUARD_C_ADAPTER_PKTIO_H

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Top-level PktIO configuration */
#include "cs_adapter_pktio.h"

/* Enables Egress Adapter Packet I/O configuration */
/*#define ADAPTER_PKTIO_MODE_EGRESS */

/* Enables Ingress Adapter Packet I/O configuration */
/*#define ADAPTER_PKTIO_MODE_INGRESS */

#ifndef ADAPTER_PKTIO_LICENSE
#define ADAPTER_PKTIO_LICENSE         "GPL"
#endif

#endif /* Include Guard */


/* end of file c_adapter_pktio.h */
