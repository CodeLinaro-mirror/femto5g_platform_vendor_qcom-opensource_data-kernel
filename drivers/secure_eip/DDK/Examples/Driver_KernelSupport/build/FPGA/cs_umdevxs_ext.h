/* cs_umdevxs_ext.h
 *
 * Configuration Switches for UMPCI driver
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

#ifndef CS_UMDEVXS_EXT_H_
#define CS_UMDEVXS_EXT_H_


#if defined(ARCH_X86)||defined(ARCH_POWERPC)

#define UMDEVXS_REMOVE_DEVICE_OF
/* PCI device Vendor ID and Device ID */
/* used to match the driver to the appropriate device */

/* Target PCI chip */
#define UMDEVXS_PCI_VENDOR_ID  0x10EE
#define UMDEVXS_PCI_DEVICE_ID  0x6018

/* logging level (choose one) */
/*#define LOG_SEVERITY_MAX LOG_SEVERITY_CRIT */
/*#define LOG_SEVERITY_MAX LOG_SEVERITY_WARN */

/*#define UMDEVXS_LOG_PREFIX "UMDevXS: " */
#define UMDEVXS_LOG_PREFIX "UMPCI: "

#define UMDEVXS_MODULENAME "driver_ks"


/* definition of device resources */
/*                   Name                Start       Last */
#define UMDEVXS_DEVICES \
    UMDEVXS_DEVICE_ADD_PCI("IPC.SRAM", 2, UMDEVXS_PCI_BAR2_SUBSET_START, 4096)

/* in addition to the above devices, the memory windows of the */
/* PCI devices can be retrieved as PCI.<bar> with <bar> being */
/* a single digit and in the valid range for the device (0..n). */
/* To more easily support large windows, we allow a subset to */
/* used using the following switches */
#define UMDEVXS_PCI_BAR0_SUBSET_START  0
#define UMDEVXS_PCI_BAR0_SUBSET_SIZE   1*1024*1024

/* BAR 1 is the EIP HW */
#define UMDEVXS_PCI_BAR1_SUBSET_START  0
#define UMDEVXS_PCI_BAR1_SUBSET_SIZE   1*1024*1024

/* BAR 2 is the SRAM */
#define UMDEVXS_PCI_BAR2_SUBSET_START  0x08000000
#define UMDEVXS_PCI_BAR2_SUBSET_SIZE   2*1024*1024

#define UMDEVXS_PCI_BAR3_SUBSET_START  0
#define UMDEVXS_PCI_BAR3_SUBSET_SIZE   1*1024*1024

#ifndef ARCH_ARM64
/* Enable when using MSI interrupts on PCI */
#define UMDEVXS_USE_MSI
#endif

#else
#define UMDEVXS_REMOVE_PCI
#define UMDEVXS_REMOVE_SMALL_PCIWINDOW_SUPPORT

/* Device name in the Device Tree Structure */
#define UMDEVXS_PLATFORM_DEVICE_NAME    "security-ip-164"

/* Index of the IRQ in the "interrupts" property of the Open Firmware device */
/* tree entry. 0 is the first IRQ listed, 1 is the second IRQ listed, etc. */
#define UMDEVXS_PLATFORM_IRQ_IDX 0

#define UMDEVXS_LOG_PREFIX "UMDevXS: "

#define UMDEVXS_MODULENAME "driver_ks"

/* definition of device resources */
/*                           Name      Start    Last */
#define UMDEVXS_DEVICES \
      UMDEVXS_DEVICE_ADD_OF("EIP-164", 0x00000, 0x3FFFF)


/* Filter for tracing interrupts: 0 - no traces, 0xFFFFFFFF - all interrupts */
#define UMDEVXS_INTERRUPT_TRACE_FILTER  0x0
#endif

/* Filter for tracing interrupts: 0 - no traces, 0xFFFFFFFF - all interrupts */
#define UMDEVXS_INTERRUPT_TRACE_FILTER  0x0


#define UMDEVXS_SMBUF_UNCACHED_MAPPING
#define UMDEVXS_DCACHE_CTRL_USERMODE

#endif /* CS_UMDEVXS_EXT_H_ */


/* end of file cs_umdevxs_ext.h */
