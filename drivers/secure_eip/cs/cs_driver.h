/** @file cs_driver.h
 *
 * @brief Top-level Product Configuration Settings.
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

#ifndef INCLUDE_GUARD_CS_DRIVER_H
#define INCLUDE_GUARD_CS_DRIVER_H

/* System configuration defines */
#include "cs_systemtestconfig.h"

/* Driver extentions */
#include "cs_driver_ext.h"

/*----------------------------------------------------------------------------
 * CAUTION: These configuration parameter are derived from
 *          the build environment configuration and may not be modified here!
 */

/*---------------------------------------------------------------------------*/

/** Selecting Egress mode */
#define DRIVER_MODE_EGRESS

/** Selecting Ingress mode */
#define DRIVER_MODE_INGRESS

/* The Driver can be used with or without interrupts. It provides an
   API function that can be used to register a callback to be invoked on
   receiving device interrupts. These callbacks typically read the device
   status or trigger this functionality in other execution contexts.\n
   When interrupts are off, the Driver is said to be in 'polling mode'.
   In this mode, the caller of the Driver API should poll the device
   registers for the device status. When interrupts are enabled, result
   notification callbacks are invoked asynchronously with respect to the
   mainapplication. */
/* #define DRIVER_INTERRUPTS*/ 
#define DRIVER_PERFORMANCE
#define DRIVER_OPTIONAL_DEVICE_COUNT 1

//The driver can be compiled with or without support for the WarmBoot API
//#define DRIVER_WARMBOOT

/** The driver can be compiled with or without write-to-decrement for statisics
    counters. When not enabled, Clear-on-read will be selected*/
#define DRIVER_WRITE_TO_DECREMENT

#define DA_MACSEC_MODE_INGRESS
#define DA_MACSEC_MODE_EGRESS


/** Specifies the driver license type for the driver registration inside the
    Linux kernel, GPL or Proprietary */
#define DRIVER_LICENSE  "GPL"

/** Specifies the driver name used for reporting in the log files and
    operating system. */
#define DRIVER_NAME     "Security_IP-164"

/** Enables the endianness conversion by the host CPU when there is a
    different endianness between the host and the device (little endian). */
#if defined ARCH_POWERPC || defined ONLY_FOR_DOXYGEN
#define DRIVER_SWAPENDIAN
#endif /*ARCH_POWERPC */

#ifdef ONLY_FOR_DOXYGEN
/** Enable per-counter summary */
#define DRIVER_PERCOUNTER_SUMMARY
#endif

/** Maximum number of attempts for the Driver during the device
    initialization to get the device status initialized. */
#define DRIVER_MAX_NOF_INIT_RETRY_COUNT 1000

/** Timeout in milliseconds between two consecutive status polls for the
    Driver during the device initialization. */
#define DRIVER_INIT_RETRY_TIMEOUT_MS    1

/** Maximum number of attempts for the Driver during the device
    uninitialization to get the device status initialized. */
#define DRIVER_MAX_NOF_UNINIT_RETRY_COUNT 1000

/** Timeout in milliseconds between two consecutive status polls for the
    Driver during the device uninitialization. */
#define DRIVER_UNINIT_RETRY_TIMEOUT_MS    10

/** Maximum number of status polls for the Driver for the host-device
    synchronization. */
#define DRIVER_MAX_NOF_SYNC_RETRY_COUNT 250

/** Timeout in milliseconds between two consecutive synchronization
    status polls */
#define DRIVER_SYNC_RETRY_TIMEOUT_MS    10

/* Constant for this driver release, cannot be changed to a higher value */
/** Maximum number of EIP-163 devices supported by the driver */
#define DRIVER_MAX_NOF_EIP163_DEVICES   8
/** Maximum number of EIP-164 devices supported by the driver */
#define DRIVER_MAX_NOF_EIP164_DEVICES   8
/** Maximum number of EIP-163 and eip164 devices supported by the driver */
#define DRIVER_MAX_NOF_DEVICES          (DRIVER_MAX_NOF_EIP163_DEVICES + \
                                         DRIVER_MAX_NOF_EIP164_DEVICES)

/** Name of the EIP-164 device 0. */
#define DRIVER_DEVICE_NAME_0    "DEV_EIP164_0"
/** Name of the EIP-164 device 1. */
#define DRIVER_DEVICE_NAME_1    "DEV_EIP164_1"

/** Name of the Global AIC for EIP-163 device 0. */
#define DRIVER_CE_DEVICE_NAME_0 "DEV_EIP163_0"
/** Name of the Global AIC for EIP-163 device 1. */
#define DRIVER_CE_DEVICE_NAME_1 "DEV_EIP163_1"

/** Name of the Global EIP-201 device 0. */
#define DRIVER_IC_NAME_0        "DEV_EIP201_0"
/** Name of the Global EIP-201 device 1. */
#define DRIVER_IC_NAME_1        "DEV_EIP201_1"

/** Names of the Channel 0..19 EIP-201 device 0. */
#define DRIVER_IC_NAME_0_CH(n)    "DEV_EIP201_0_CH" # n

/** Names of the Channel 0..19 EIP-201 device 1. */
#define DRIVER_IC_NAME_1_CH(n)    "DEV_EIP201_1_CH" # n


/** EIP-164 Packet Engine EIP-201 AIC name for device 0.*/
#define DRIVER_PE_IC_NAME_0     "DEV_PE_EIP201_0"
/** EIP-164 Packet Engine EIP-201 AIC name for device 1.*/
#define DRIVER_PE_IC_NAME_1     "DEV_PE_EIP201_1"


/** EIP-163 Global EIP-201 AIC name for device 0 */
#define DRIVER_CE_IC_NAME_0     "DEV_CE_EIP201_0"
/** EIP-163 Global EIP-201 AIC name for device 1 */
#define DRIVER_CE_IC_NAME_1     "DEV_CE_EIP201_1"

/* EIP-163 Channel (0..19) EIP-201 AIC name */
/** EIP-201 Channel 0..19 AIC name for device 0 */
#define DRIVER_CE_IC_NAME_0_CH(n) "DEV_CE_EIP201_0_CH" #n

/** EIP-201 Channel (0..19) AIC name for device 1 */
#define DRIVER_CE_IC_NAME_1_CH(n) "DEV_CE_EIP201_1_CH" #n

/** Maximum length in bytes of the device name in the device list */
#define DRIVER_MAX_DEVICE_NAME_LENGTH       32

/**  Maximum number of internal channel AIC's per one EIP-163 or EIP-164 device */
#define DRIVER_MAX_NOF_CHANNEL_IC_DEVICES  4

/** 1 Global AIC, 1 Packet Engine AIC and channel AIC's */
#define DRIVER_MAX_NOF_EIP164_IC_DEVICES   ((DRIVER_MAX_NOF_EIP164_DEVICES) * \
                                     (2 + DRIVER_MAX_NOF_CHANNEL_IC_DEVICES))

/** 1 Global AIC, 1 dummy AIC and channel AIC's */
#define DRIVER_MAX_NOF_EIP163_IC_DEVICES   ((DRIVER_MAX_NOF_EIP163_DEVICES) * \
                                     (2 + DRIVER_MAX_NOF_CHANNEL_IC_DEVICES))

/** Calculate driver AIC device ID from its parent EIP-163/4 device ID
    Note 1: this formula should match the device order rules
    in the HWPAL_DEVICES device list (see cs_hwpal.h) */
#define DRIVER_ICDEV_ID(DevID, fGlobal, fPE, ChID) \
          (fGlobal) ? (DevID + 1) : ((fPE) ? (DevID + 2) : (DevID + 3 + ChID))

/** Calculate driver interrupt handler ID from EIP-201 AIC device ID,
   see Note 1 above. One interrupt handler is used per one AIC device. */
#define DRIVER_INT_HANDLER_ID(ICDevID) \
    ((((ICDevID - DRIVER_OPTIONAL_DEVICE_COUNT) / \
      (3 + DRIVER_MAX_NOF_CHANNEL_IC_DEVICES)) * \
        (2 + DRIVER_MAX_NOF_CHANNEL_IC_DEVICES)) + \
          ((ICDevID - DRIVER_OPTIONAL_DEVICE_COUNT) % \
              (3 + DRIVER_MAX_NOF_CHANNEL_IC_DEVICES)) - 1)

/** EIP-164 device name */
#define DRIVER_EIP164_NAME(devid)         "DEV_EIP164_" #devid

/** EIP-163 device name */
#define DRIVER_EIP163_NAME(devid)         "DEV_EIP163_" #devid

/** EIP-201 Global AIC device name */
#define DRIVER_G_AIC_NAME(devid)          "DEV_EIP201_" #devid

/** EIP-201 CE Global AIC device name */
#define DRIVER_CE_G_AIC_NAME(devid)       "DEV_CE_EIP201_" #devid

/** EIP-201 Packet Engine AIC device name */
#define DRIVER_PE_AIC_NAME(devid)         "DEV_PE_EIP201_" #devid

/** Dummy AIC device name */
#define DRIVER_DUMMY_NAME(devid)          "Dummy_" #devid

/** EIP-201 Channel AIC device name for EIP-164 */
#define DRIVER_IC_NAME_CH(devid, chid)    "DEV_EIP201_" #devid "_CH" #chid

/** EIP-201 Channel AIC device name for EIP-163 */
#define DRIVER_CE_IC_NAME_CH(devid, chid) "DEV_CE_EIP201_" #devid "_CH" #chid

#ifdef ONLY_FOR_DOXYGEN
/** EIP-164 device chain:
    1  EIP-164 device,
    1  EIP-201 Global AIC device (sub-device in EIP-164),
    1  EIP-201 Packet Engine AIC device (sub-device in EIP-164),
    24 EIP-201 Channel AIC devices (sub-devices in EIP-164)

    Fields per device:
    - Name
    - DevNr
    - Start byte offset
    - End byte offset
    - Flags */
#define DRIVER_EIP164_CHAIN(devid,n,s,e,f)


/** EIP-163 device chain:
    1  EIP-163 device,
    1  Dummy AIC device.
    1  EIP-201 Packet Engine AIC device (sub-device in EIP-163),
    24 EIP-201 Channel AIC devices (sub-devices in EIP-163)

    Fields per device:
    - Name
    - DevNr
    - Start byte offset
    - End byte offset
    - Flags */
#define DRIVER_EIP163_CHAIN(devid,n,s,e,f)

#else /* ONLY_FOR_DOXYGEN */
/** EIP-164 device chain:
    1  EIP-164 device,
    1  EIP-201 Global AIC device (sub-device in EIP-164),
    1  EIP-201 Packet Engine AIC device (sub-device in EIP-164),
    24 EIP-201 Channel AIC devices (sub-devices in EIP-164)

    Fields per device:         Name          DevNr Start            End            Flags */
#define DRIVER_EIP164_CHAIN(devid,n,s,e,f)                                                \
    /* EIP-164 device */                                                                  \
    DRIVER_DEVICE_ADD(DRIVER_EIP164_NAME(devid),  n,s,               e,               f), \
    /* EIP-164 device: Global EIP-201 AIC */                                              \
    DRIVER_DEVICE_ADD(DRIVER_G_AIC_NAME(devid),   n,s+0xfc00,        s+0xfcff,        f), \
    /* EIP-164 device: Packet Engine EIP-201 AIC  */                                      \
    DRIVER_DEVICE_ADD(DRIVER_PE_AIC_NAME(devid),  n,s+0x5c00,        s+0x5c3f,        f), \
    /* EIP-164 device: 64 Channel EIP-201 AIC's */                 \
    DRIVER_DEVICE_ADD(DRIVER_IC_NAME_CH(devid, 0), n, s + 0xf400 + (0x10000 * (0 >> 5)) + ((0 & 0x1f) * 0x40), s + 0xf43f +  (0x10000 * (0 >> 5)) + ((0 & 0x1f) * 0x40), f),\
    DRIVER_DEVICE_ADD(DRIVER_IC_NAME_CH(devid, 1), n, s + 0xf400 + (0x10000 * (1 >> 5)) + ((1 & 0x1f) * 0x40), s + 0xf43f +  (0x10000 * (1 >> 5)) + ((1 & 0x1f) * 0x40), f),\
    DRIVER_DEVICE_ADD(DRIVER_IC_NAME_CH(devid, 2), n, s + 0xf400 + (0x10000 * (2 >> 5)) + ((2 & 0x1f) * 0x40), s + 0xf43f +  (0x10000 * (2 >> 5)) + ((2 & 0x1f) * 0x40), f),\
    DRIVER_DEVICE_ADD(DRIVER_IC_NAME_CH(devid, 3), n, s + 0xf400 + (0x10000 * (3 >> 5)) + ((3 & 0x1f) * 0x40), s + 0xf43f +  (0x10000 * (3 >> 5)) + ((3 & 0x1f) * 0x40), f)

/** EIP-163 device chain:
    1  EIP-163 device,
    1  EIP-201 Global AIC device (sub-device in EIP-163),
    1  Dummy AIC device,
    24 EIP-201 Channel AIC devices (sub-devices in EIP-163)

    Fields per device:         Name             DevNr Start            End            Flags */
#define DRIVER_EIP163_CHAIN(devid,n,s,e,f)                                                   \
    /* EIP-163 device */                                                                     \
    DRIVER_DEVICE_ADD(DRIVER_EIP163_NAME(devid),     n,s,               e,               f), \
    /* EIP-163 device: Global EIP-201 AIC */                                                 \
    DRIVER_DEVICE_ADD(DRIVER_CE_G_AIC_NAME(devid),   n,s+0xfc00,        s+0xfcff,        f), \
    /* EIP-163 device: Packet Engine EIP-201 AIC  */                                         \
    DRIVER_DEVICE_ADD(DRIVER_DUMMY_NAME(devid),      n,0,               0,               f), \
    /* EIP-164 device: 64 Channel EIP-201 AIC's */                    \
    DRIVER_DEVICE_ADD(DRIVER_CE_IC_NAME_CH(devid, 0), n, s + 0xf400 + (0x10000 * (0 >> 5)) + ((0 & 0x1f) * 0x40), s + 0xf43f + (0x10000 * (0 >> 5)) + ((0 & 0x1f) * 0x40), f),\
    DRIVER_DEVICE_ADD(DRIVER_CE_IC_NAME_CH(devid, 1), n, s + 0xf400 + (0x10000 * (1 >> 5)) + ((1 & 0x1f) * 0x40), s + 0xf43f + (0x10000 * (1 >> 5)) + ((1 & 0x1f) * 0x40), f),\
    DRIVER_DEVICE_ADD(DRIVER_CE_IC_NAME_CH(devid, 2), n, s + 0xf400 + (0x10000 * (2 >> 5)) + ((2 & 0x1f) * 0x40), s + 0xf43f + (0x10000 * (2 >> 5)) + ((2 & 0x1f) * 0x40), f),\
    DRIVER_DEVICE_ADD(DRIVER_CE_IC_NAME_CH(devid, 3), n, s + 0xf400 + (0x10000 * (3 >> 5)) + ((3 & 0x1f) * 0x40), s + 0xf43f + (0x10000 * (3 >> 5)) + ((3 & 0x1f) * 0x40), f)

#endif /* ONLY_FOR_DOXYGEN */

/** Ingress or egress  data path,
    one port consists of both ingress and egress data path,
   first ingress followed by egress data path in the device list per port */
#define DRIVER_DATAPATH(dpid,n1,s1,e1,f1,n2,s2,e2,f2) \
            DRIVER_EIP164_CHAIN(dpid,n1,s1,e1,f1),          \
            DRIVER_EIP163_CHAIN(dpid,n2,s2,e2,f2)

#ifdef ONLY_FOR_DOXYGEN
/** Disable device initialization register writes,
    this can be used to speed up initialization by offloading these register
    writes to another processor with lower register write overhead */
#define DRIVER_DEV_INIT_DISABLE

/** Disable device initialization register writes,
    this can be used to speed up initialization by offloading these register
    writes to another processor with lower register write overhead */
#define DRIVER_DEV_UNINIT_DISABLE
#endif /* ONLY_FOR_DOXYGEN */

/* C0 = Interrupts, Egress (HW conf -e), Perf=N */
#ifdef SYSTEMTEST_CONFIGURATION_C0
/** Selecting Egress mode */
#define DRIVER_MODE_EGRESS
/** The Driver can be used with or without interrupts. It provides an
    API function that can be used to register a callback to be invoked on
    receiving device interrupts. These callbacks typically read the device
    status or trigger this functionality in other execution contexts.\n
    When interrupts are off, the Driver is said to be in 'polling mode'.
    In this mode, the caller of the Driver API should poll the device
    registers for the device status. When interrupts are enabled, result
    notification callbacks are invoked asynchronously with respect to the
    mainapplication. */
/* #define DRIVER_INTERRUPTS*/ 
/*#define DRIVER_PERFORMANCE */
/** The driver can be compiled with or without support for the WarmBoot API.
 */
//#define DRIVER_WARMBOOT
/** The driver can be compiled with or without write-to-decrement for statisics
    counters. When not enabled, Clear-on-read will be selected*/
#define DRIVER_WRITE_TO_DECREMENT
#endif

/* C1 = Polling, Ingress (HW conf -i), Perf=Y */
#if defined SYSTEMTEST_CONFIGURATION_C1 || defined ONLY_FOR_DOXYGEN
/** Selecting Ingress mode */
#define DRIVER_MODE_INGRESS
/*#define DRIVER_INTERRUPTS */
/** Enabling this parameter in the Driver suppresses informational
    messages. These messages are helpful in debugging but otherwise
    slow-down the Driver. */
#define DRIVER_PERFORMANCE
#ifndef ONLY_FOR_DOXYGEN
//#define DRIVER_WARMBOOT
#endif
#ifndef ONLY_FOR_DOXYGEN
#define DRIVER_WRITE_TO_DECREMENT
#endif
#endif

/* C3 = Polling, Egress (HW conf -e), Perf=Y */
#ifdef SYSTEMTEST_CONFIGURATION_C3
#define DRIVER_MODE_EGRESS
/*#define DRIVER_INTERRUPTS */
#define DRIVER_PERFORMANCE
/*#define DRIVER_WARMBOOT */
/*#define DRIVER_WRITE_TO_DECREMENT */
#endif

/* C4 = Interrupts, Ingress (HW conf -i), Perf=N */
#ifdef SYSTEMTEST_CONFIGURATION_C4
#define DRIVER_MODE_INGRESS
#define DRIVER_INTERRUPTS

/*#define DRIVER_PERFORMANCE */
/*#define DRIVER_WARMBOOT */
/*#define DRIVER_WRITE_TO_DECREMENT */
#endif

#ifdef ONLY_FOR_DOXYGEN
/** Define this if the Driver is to be compiled for a platform that has
    64-bit addresses. Leave this undefined for a 32-bit platform.\n
    This option is normally passed via the make file from the
    DDK_HOST64 environment variable. */
#define DRIVER_64BIT_HOST
#endif

#endif /* Include Guard */


/* end of file cs_driver.h */
