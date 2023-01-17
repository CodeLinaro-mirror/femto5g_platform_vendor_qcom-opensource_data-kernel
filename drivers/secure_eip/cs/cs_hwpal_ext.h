/* cs_hwpal_ext.h
 *
 * Security-IP-164 (FPGA) PCI/OpenFirmware chip specific configuration
 * parameters
*/

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Module        : ddk164                                                   */
/*   Version       : 3.2                                                      */
/*   Configuration : DDK-164-IPSEC-GPL                                        */
/*                                                                            */
/*   Date          : 2022-Jan-10                                              */
/*                                                                            */
/* Copyright (c) 2008-2021 by Rambus, Inc. and/or its subsidiaries.           */
/* Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.  */
/*                                                                            */
/* This program is free software: you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation, either version 2 of the License, or          */
/* any later version.                                                         */
/*                                                                            */
/* This program is distributed in the hope that it will be useful,            */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of             */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               */
/* GNU General Public License for more details.                               */
/*                                                                            */
/* You should have received a copy of the GNU General Public License          */
/* along with this program. If not, see <http://www.gnu.org/licenses/>.       */
/* -------------------------------------------------------------------------- */

#ifndef CS_HWPAL_EXT_H_
#define CS_HWPAL_EXT_H_


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

/* For obtaining the IRQ number */
#ifdef DRIVER_INTERRUPTS
#define HWPAL_INTERRUPTS
#endif

#if defined(ARCH_X86)||defined(ARCH_POWERPC)

/* FPGA board device ID. */
#define HWPAL_DEVICE_ID             0x6018

/* Xilinx PCI vendor ID */
#define HWPAL_VENDOR_ID             0x10EE

#define HWPAL_MAGIC_PCICONFIGSPACE  0xFF434647      /* 43 46 47 = C F G */
#define hw_a                        HWPAL_MAGIC_PCICONFIGSPACE

#define HWPAL_REMAP_ADDRESSES   ;

#define HWPAL_DEVICE_TO_FIND       "PCI.0" /* PCI Bar 0 */

/* definition of static resources inside the PCI device */
/* Refer to the data sheet of device for the correct values */
/*                   Name                 DevNr Start    Last     Flags (see below) */
#define HWPAL_PLATFORM_SPECIFIC_DEVICES \
    HWPAL_DEVICE_ADD("PCI_CONFIG_SPACE",  0,    hw_a,    hw_a+1024, 7),

#define HWPAL_PLATFORM_SPECIFIC_DEVICES_COUNT   1

#ifndef ARCH_ARM64
#define HWPAL_USE_MSI
#endif

#else

/* Disable PCI Configuration Space support support */
#define HWPAL_REMOVE_DEVICE_PCICONFIGSPACE

/* Device name in the Device Tree Structure */
#define HWPAL_PLATFORM_DEVICE_NAME  "security-ip-164"

/* Index of the IRQ in the "interrupts" property of the Open Firmware device */
/* tree entry. 0 is the first IRQ listed, 1 is the second IRQ listed, etc. */
#define HWPAL_PLATFORM_IRQ_IDX 0

#define HWPAL_REMAP_ADDRESSES   ;

#define HWPAL_PLATFORM_SPECIFIC_DEVICES
#define HWPAL_PLATFORM_SPECIFIC_DEVICES_COUNT   0

#endif

/* Optional devices in HWPAL_DEVICES, see below */
#define HWPAL_OPTIONAL_DEVICES_COUNT (HWPAL_PLATFORM_SPECIFIC_DEVICES_COUNT + 1)

#if HWPAL_OPTIONAL_DEVICES_COUNT != DRIVER_OPTIONAL_DEVICE_COUNT
#error "Optional devices configuration mismatch"
#endif

/* Definition of static resources (devices), */
/* refer to the data sheet of device for the correct values */

/* HWPAL_DEVICES static configuration example below lists devices for one port, */
/* namely port 0, using 2 EIP-164 and 2 EIP-163 devices. */
#define HWPAL_DEVICES                                                       \
    /* Optional devices */                                                  \
                                                                            \
    /* Platform devices */                                                  \
    HWPAL_PLATFORM_SPECIFIC_DEVICES                                         \
                                                                            \
    /* Fields per device:     Name          DevNr  Start     End   Flags */ \
                                                                            \
    /* FPGA board control device */                                         \
    HWPAL_DEVICE_ADD("BOARD_CTRL",              0, 0x0A0000, 0x0A0fff, 7),  \
                                                                            \
    /* Mandatory devices */                                                 \
                                                                            \
    /* Port 0, egress and ingress data path */                              \
                                                                            \
    /* Fields per device: D-path DevNr Start     End      Flags         */  \
    HWPAL_DATAPATH_INGRESS(0,   0,    0x0000000, 0x003ffff,  3,  /*EIP164*/  \
                                0,    0x0080000, 0x008ffff,  3), /*EIP163*/  \
    HWPAL_DATAPATH_EGRESS(1,    1,    0x0040000, 0x007ffff,  3,  /*EIP164*/  \
                                1,    0x0090000, 0x009ffff,  3),  /*EIP163*/ \
                                                                             \
    HWPAL_DATAPATH_INGRESS(2,   2,    0x0000000, 0x003ffff,  3,  /*EIP164*/  \
                                2,    0x0080000, 0x008ffff,  3), /*EIP163*/  \
    HWPAL_DATAPATH_EGRESS(3,    3,    0x0040000, 0x007ffff,  3,  /*EIP164*/  \
                                3,    0x0090000, 0x009ffff,  3),  /*EIP163*/ \
                                                                             \
    HWPAL_DATAPATH_INGRESS(4,   4,    0x0000000, 0x003ffff,  3,  /*EIP164*/  \
                                4,    0x0080000, 0x008ffff,  3), /*EIP163*/  \
    HWPAL_DATAPATH_EGRESS (5,   5,    0x0040000, 0x007ffff,  3,  /*EIP164*/  \
                                5,    0x0090000, 0x009ffff,  3),  /*EIP163*/ \
                                                                             \
    HWPAL_DATAPATH_INGRESS(6,   6,    0x0000000, 0x003ffff,  3,  /*EIP164*/  \
                                6,    0x0080000, 0x008ffff,  3), /*EIP163*/  \
    HWPAL_DATAPATH_EGRESS (7,   7,    0x0040000, 0x007ffff,  3,  /*EIP164*/  \
                                7,    0x0090000, 0x009ffff,  3)  /*EIP163*/

/* Note: EIP-164 register memory map size is 0xp0000 and end address 0xp0000-1 */
/*       where p = (MaxSA_Count >> 7), */
/*       EIP-163 register memory map size is 0xp0000 and end address 0xp0000-1 */
/*       where p = (MaxTCAMRules_Count >> 9), */
/*       see EIP-164 and EIP-163 Programmer Manuals for details */

/* Flags: */
/*   bit0 = Trace Device_Read32(), requires HWPAL_TRACE_DEVICE_READ */
/*   bit1 = Trace Device_Write32(), requires HWPAL_TRACE_DEVICE_WRITE */
/*   bit2 = Swap word endianness (requires HWPAL_DEVICE_ENABLE_SWAP) */


#endif /* CS_HWPAL_EXT_H_ */


/* end of file cs_hwpal_ext.h */
