/* adapter_interrupts_ext.h
 *
 * Host hardware specific extensions for the Adapter Interrupts interface
 * EIP-164 hardware
 */

/*****************************************************************************
* Copyright (c) 2012-2021 by Rambus, Inc. and/or its subsidiaries.
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

#ifndef ADAPTER_INTERRUPTS_EXT_H_
#define ADAPTER_INTERRUPTS_EXT_H_

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

/* Adapter logical EIP-164 SecY Device interrupts */
/* Each EIP-164 device has just one physical interrupt output line */
/* and each device has its own EIP-201 Advanced Interrupt Controller */

#define IRQ_LAST_LINE   1

int
Adapter_Interrupt_EnabledStatus_Get(const int nIRQ, unsigned int *Status_p);


#endif /* ADAPTER_INTERRUPTS_EXT_H_ */


/* end of file adapter_interrupts_ext.h */
