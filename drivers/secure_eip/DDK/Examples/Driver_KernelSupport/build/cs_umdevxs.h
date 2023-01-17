/* cs_umdevxs.h
 *
 * Configuration for Kernel Suppor Driver top-level configuration
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

#ifndef CS_UMDEVXS_H_
#define CS_UMDEVXS_H_


#include "cs_umdevxs_ext.h"

/*----------------------------------------------------------------------------
 * Definitions and macros
 */

#define UMDEVXS_LICENSE    "GPL"

/* logging level (choose one) */
#ifndef LOG_SEVERITY_MAX
#define LOG_SEVERITY_MAX LOG_SEVERITY_WARN
#endif

/* uncomment to remove selected functionality */
/*#define UMDEVXS_REMOVE_DEVICE */
/*#define UMDEVXS_REMOVE_PCI */
/*#define UMDEVXS_REMOVE_DMABUF */
#define UMDEVXS_REMOVE_SMBUF
#define UMDEVXS_REMOVE_SMBUF_PROVIDER
#define UMDEVXS_REMOVE_SMBUF_OBTAINER
#define UMDEVXS_REMOVE_SIMULATION
/*#define UMDEVXS_REMOVE_INTERRUPT */
#define UMDEVXS_REMOVE_SMALL_PCIWINDOW_SUPPORT

/* Use non-cached DMA buffer mapping to user-space */
#define UMDEVXS_SMBUF_UNCACHED_MAPPING

/* Use non-cached DMA buffer mapping to user-space for PCI */
#define UMDEVXS_PCI_UNCACHED_MAPPING

/* Use user-space buffer address for CPU Data Cache control (flush/invalidate) */
#define UMDEVXS_DCACHE_CTRL_UADDR

/* Size of mapped device region in bytes, use 0 for auto-detect. */
#define UMDEVXS_PCI_DEVICE_RESOURCE_BYTE_COUNT 0

/* Assume each EIP HW Advanced Interrupt Controller (AIC) has a dedicated */
/* irq line in the system: */
/* EIP-163 Engine AIC's: 1 Global, 1 PE, 1 per Channel (24x), for egress and ingress */
/* EIP-164 Engine AIC's: 1 Global, 1 dummy, 1 per Channel (24x), for egress and ingress */
/* Note: This should be set as equal to DRIVER_MAX_NOF_EIP164_IC_DEVICES + */
/*                                      DRIVER_MAX_NOF_EIP163_IC_DEVICES */
/*       (see Examples/Driver_EIP164/build/cs_driver.h) */
#define UMDEVXS_INTERRUPT_IC_DEVICE_COUNT        (2 * 2 * (2 + 24))


#endif /* CS_UMDEVXS_H_ */


/* end of file cs_umdevxs.h */
