/** @file cs_eip164.h
 *
 * @brief Top-level configuration parameters
 * for the EIP-164 Driver Library
 *
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

#ifndef CS_EIP164_H_
#define CS_EIP164_H_


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */
#include "cs_driver.h"

/*----------------------------------------------------------------------------
 * Definitions and macros
 */

/* One device instance (core) mode of operation */
/** EIP-164 Egress device mode */
#ifdef DRIVER_MODE_EGRESS
#define EIP164_DEVICE_MODE_EGRESS
#endif

/** EIP-164 Ingress device mode */
#ifdef DRIVER_MODE_INGRESS
#define EIP164_DEVICE_MODE_INGRESS
#endif

/** If this parameter is defined, the driver will support basic
    crypt-authenticate  operations (nonMACsec), which can be used for
    test purposes. */
#define EIP164_CRYPT_AUTH_ENABLE

/** Enables strict argument checking for the input parameters in all the
    EIP-164 Driver API functions */
#define EIP164_STRICT_ARGS

/** Enable PACK timeout counter of statistics modules,
    granting the host access after a certain number of cycles. */
#define EIP164_PACK_TIMEOUT_ENABLE          1

/** Number of cycles for PACK timeout. */
#define EIP164_PACK_TIMEOUT_VALUE           1

/** Does device support per-counter summary? */
#if defined DRIVER_PERCOUNTER_SUMMARY || defined ONLY_FOR_DOXYGEN
#define EIP164_PERCOUNTER_SUMMARY_ENABLE
#endif


#ifdef ONLY_FOR_DOXYGEN

/** If this configuration option is set, the strict argument checking of the
    input parameters is enabled and can detect some programming errors.
    If not set, the performance is increased and code size is reduced. */
#define EIP164_CONF_BASE                    0x00

/** This configuration option sets (defines) the maximum crypt-authenticate
    bypass length. If not set, the default will be 255. */
#define EIP164_SECY_CRYPT_AUTH_MAX_BYPASS_LEN

/** This configuration option sets (defines) the base offset for all the
    EIP-66 registers. If not set, the default will be 0. */
#define EIP66_CONF_BASE

/** This configuration option sets (defines) the base offset for all the EIP-217
    registers. If not set, the default will be 0. */
#define EIP217_CONF_BASE

#endif /* ONLY_FOR_DOXYGEN */

#if defined DRIVER_IPSEC
#define EIP164_IPSEC_ENABLE
#endif
#if defined DRIVER_VXLAN
#define EIP164_VXLAN_ENABLE
#endif

#endif /* CS_EIP164_H_ */


/* end of file cs_eip164.h */
