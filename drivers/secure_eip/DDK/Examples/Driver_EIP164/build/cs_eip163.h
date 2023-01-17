/** @file cs_eip163.h
 *
 * @brief EIP-163 Driver Library Top-Level Configuration.
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

#ifndef CS_EIP163_H_
#define CS_EIP163_H_


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Top-level driver configuration */
#include "cs_driver.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

/** EIP-163 Egress device mode */
#ifdef DRIVER_MODE_EGRESS
#define EIP163_DEVICE_MODE_EGRESS
#endif

/** EIP-163 Ingress device mode */
#ifdef DRIVER_MODE_INGRESS
#define EIP163_DEVICE_MODE_INGRESS
#endif

/* Base offset used for all the EIP-163 registers */
/*#define EIP163_CONF_BASE                    0x80000 */

/** Enables strict argument checking for the input parameters in all the
    EIP-163 Driver API functions */
#if !defined DRIVER_PERFORMANCE || defined ONLY_FOR_DOXYGEN
#define EIP163_STRICT_ARGS
#endif

/** Enable PACK timeout counter of statistics modules,
    granting the host access after a certain number of cycles. */
#define EIP163_PACK_TIMEOUT_ENABLE          1

/** Number of cycles for PACK timeout. */
#define EIP163_PACK_TIMEOUT_VALUE           1


#ifdef ONLY_FOR_DOXYGEN

/** If this configuration option is set, the strict argument checking of the
    input parameters is enabled and can detect some programming errors.
    If not set, the performance is increased and code size is reduced. */
#define EIP163_CONF_BASE                    0x00

/** Number of read operations required for the 0 unsafe counter for proper CDS */
#define EIP163_MAX_SYNC_COUNT               3

/** This configuration option sets (defines) the base offset for all the EIP-217
    registers. If not set, the default will be 0. */
#define EIP217_CONF_BASE

#endif /* ONLY_FOR_DOXYGEN */

#if defined DRIVER_IPSEC
#define EIP163_IPSEC_ENABLE
#endif
#if defined DRIVER_VXLAN
#define EIP163_VXLAN_ENABLE
#endif

/** Number of non-control words in each TCAM entry. The actual width of
    TCAM words may be larger than what is required by the rules.*/
#define EIP163_TCAM_NON_CTRL_WORD_COUNT 5

#endif /* CS_EIP163_H_ */


/* end of file cs_eip163.h */
