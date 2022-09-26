/* c_eip164.h
 *
 * EIP-164 Driver Library Default Configuration.
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

#ifndef C_EIP164_H_
#define C_EIP164_H_


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Top-level configuration */
#include "cs_eip164.h"

/* One device instance (core) mode of operation */
/*#define EIP164_DEVICE_MODE_EGRESS */
/*#define EIP164_DEVICE_MODE_INGRESS */

/* Base offset used for all the EIP-164 registers */
#ifndef EIP164_CONF_BASE
#define EIP164_CONF_BASE                    0x00
#endif /* EIP164_CONF_BASE */

/* Number of read operations required for the 0 unsafe counter */
/* for proper CDS */
#ifndef EIP164_SECY_MAX_SYNC_COUNT
#define EIP164_SECY_MAX_SYNC_COUNT          3
#endif

/* Maximum value for crypt-authenticate bypass length */
#ifndef EIP164_SECY_CRYPT_AUTH_MAX_BYPASS_LEN
#define EIP164_SECY_CRYPT_AUTH_MAX_BYPASS_LEN            255
#endif

/* Enable PACK timeout counter of statistics modules, */
/* granting the host access after a certain number of cycles. */
#ifndef EIP164_PACK_TIMEOUT_ENABLE
#define EIP164_PACK_TIMEOUT_ENABLE          1
#endif

/* Number of cycles for PACK timeout. */
#ifndef EIP164_PACK_TIMEOUT_VALUE
#define EIP164_PACK_TIMEOUT_VALUE           1
#endif


/* Enable EIP-164 Crypt-Authenticate feature */
/*#define EIP164_CRYPT_AUTH_ENABLE */

/* Strict argument checking for the input parameters */
/* If required then define this parameter in the top-level configuration */
/*#define EIP164_STRICT_ARGS */

/* Enable per-counter summary */
/* #define EIP164_PERCOUNTER_SUMMARY_ENABLE */

/* Disable EIP-164 device initialization register writes, */
/* this can be used to speed up initialization by offloading these register */
/* writes to another processor with lower EIP-164 register write overhead */
/*#define EIP164_DEV_INIT_DISABLE */


#endif /* C_EIP164_H_ */


/* end of file c_eip164.h */
