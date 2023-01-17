/* c_test_macsec.h
 *
 * Test Tool for CfyE and SecY API's
 * Default configuration file
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

#ifndef C_TEST_MACSEC_H_
#define C_TEST_MACSEC_H_

#include "cs_test_macsec.h"

/* this file is included by test_macsec.c to get configuration switches */

/* log level for the entire adapter (for now) */
/* choose from LOG_SEVERITY_INFO, LOG_SEVERITY_WARN, LOG_SEVERITY_CRIT */
#ifndef LOG_SEVERITY_MAX
#define LOG_SEVERITY_MAX                      LOG_SEVERITY_INFO
#endif

/* Enables debugging traces */
/*#define TEST_MACSEC_DEBUG */

#ifndef TEST_MACSEC_LICENSE
#define TEST_MACSEC_LICENSE                   "GPL"
#endif

/* Delay in millisconds between tries to receive the packet */
#ifndef TEST_MACSEC_RETRY_DELAY_MS
#define TEST_MACSEC_RETRY_DELAY_MS             10
#endif

/* Maximum number of tries to receive the packet */
#ifndef TEST_MACSEC_NOF_TRIES
#define TEST_MACSEC_NOF_TRIES                  4000
#endif

/* Number of test packets */
#ifndef TEST_MACSEC_NR_TEST_PACKETS
#define TEST_MACSEC_NR_TEST_PACKETS            10
#endif

/*#define TEST_MACSEC_MODE_EGRESS */
/*#define TEST_MACSEC_MODE_INGRESS */

/* Enable use of the SecY API notification */
/*#define TEST_MACSEC_SECY_NOTIFY_ENABLE */

/* Enable the crypt-authenticate feature verification */
/* which can be provided as part of the MACsec Engine (SecY) */
/*#define TEST_MACSEC_SECY_CRYPT_AUTH_ENABLE */

/* Enable the classification functionality, */
/* which is provided by the Classification Engine (CfyE) */
/*#define TEST_MACSEC_USE_CFYE */

/* Enable the WarmBoot functionality */
/*#define TEST_MACSEC_USE_WARMBOOT */

/* Use the Driver Read functions to read SA parameters, rules, vPorts */
/*#define TEST_MACSEC_USE_READ_API */

/* Is driver configured for write-to-decrement and should clear-on-read be
   disabled? */
#ifndef TEST_MACSEC_WRITE_TO_DECREMENT
#define TEST_MACSEC_WRITE_TO_DECREMENT 0
#endif

#ifdef TEST_MACSEC_DEBUG

#ifdef TEST_MACSEC_MODE_EGRESS
#ifndef TEST_MACSEC_DEBUG_DEVICE_NAME
#define TEST_MACSEC_DEBUG_DEVICE_NAME       "DEV_EIP164_EGRESS"
#endif
#endif /* TEST_MACSEC_MODE_EGRESS */

#ifdef TEST_MACSEC_MODE_INGRESS
#ifndef TEST_MACSEC_DEBUG_DEVICE_NAME
#define TEST_MACSEC_DEBUG_DEVICE_NAME       "DEV_EIP164_INGRESS"
#endif
#endif /* TEST_MACSEC_MODE_INGRESS */

/* Enable per-counter summary registers. */
/*#define TEST_MACSEC_PERCOUNTER_SUMMARY_ENABLE */

#endif /* TEST_MACSEC_DEBUG */

/*#define TEST_MACSEC_KAT1_REMOVE */
/*#define TEST_MACSEC_KAT2_REMOVE */
/*#define TEST_MACSEC_KAT3_REMOVE */
/*#define TEST_MACSEC_KAT4_REMOVE */
/*#define TEST_MACSEC_KAT5_REMOVE */

#ifndef TEST_MACSEC_KAT5_REMOVE
#ifndef TEST_MACSEC_DEVICES
#error "TEST_MACSEC_DEVICES undefined"
#endif
#endif /* !TEST_MACSEC_KAT5_REMOVE */


#endif /* C_TEST_MACSEC_H_ */


/* end of file c_test_macsec.h */
