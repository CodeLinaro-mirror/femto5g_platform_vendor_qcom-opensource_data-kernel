/* c_eip217.h
 *
 * EIP-217 Driver Library Default Configuration.
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

#ifndef C_EIP217_H_
#define C_EIP217_H_


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Top-level configuration */
#include "cs_eip217.h"

/* Base offset used for all the EIP-217 registers */
#ifndef EIP217_CONF_BASE
#define EIP217_CONF_BASE                0x00
#endif /* EIP217_CONF_BASE */


#endif /* C_EIP217_H_ */


/* end of file c_eip217.h */
