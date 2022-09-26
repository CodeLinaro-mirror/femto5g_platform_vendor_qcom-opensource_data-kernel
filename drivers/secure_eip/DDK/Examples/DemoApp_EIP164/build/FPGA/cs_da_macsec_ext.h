/* cs_da_macsec_ext.h
 *
 * Demo Application Top-level Configuration, FPGA extensions
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


/* this file is included by cs_da_macsec.h to get configuration switches */

/* Delay in milliseconds between tries to receive the packet */
#define DA_MACSEC_PKT_GET_TIMEOUT_MS      2

/* Maximum number of tries to receive the packet */
#define DA_MACSEC_PKT_GET_RETRY_COUNT     500

/* Enable multiple packet tests */
/*#define DA_MACSEC_MULTIPLE_PKT_TEST */

/* Enable the tests that check device error returns */
/*#define DA_MACSEC_USE_DEVERROR */

/* end of file cs_da_macsec_ext.h */
