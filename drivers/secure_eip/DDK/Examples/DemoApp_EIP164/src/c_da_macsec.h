/* c_da_macsec.h
 *
 * Default Demo Application for MACsec
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

/* Top-level configuration */
#include "cs_da_macsec.h"

/* this file is included by da_macsec.c to get configuration switches */

/* log level for the entire adapter (for now) */
/* choose from LOG_SEVERITY_INFO, LOG_SEVERITY_WARN, LOG_SEVERITY_CRIT */
#ifndef LOG_SEVERITY_MAX
#define LOG_SEVERITY_MAX            LOG_SEVERITY_INFO
#endif

#ifndef DA_MACSEC_LICENSE
#define DA_MACSEC_LICENSE           "GPL"
#endif

/* Delay in milliseconds between tries to receive the packet */
#ifndef DA_MACSEC_PKT_GET_TIMEOUT_MS
#define DA_MACSEC_PKT_GET_TIMEOUT_MS    10
#endif

/* Maximum number of tries to receive the packet. */
#ifndef DA_MACSEC_PKT_GET_RETRY_COUNT
#define DA_MACSEC_PKT_GET_RETRY_COUNT   5000
#endif

/* Enable multiple packet tests */
/*#define DA_MACSEC_MULTIPLE_PKT_TEST */

/*#define DA_MACSEC_MODE_EGRESS */
/*#define DA_MACSEC_MODE_INGRESS */

#if !defined(DA_MACSEC_MODE_EGRESS) && !defined(DA_MACSEC_MODE_INGRESS)
#define DA_MACSEC_MODE_INGRESS
#endif

/* Enable the tests that use the CfyE API. */
#define DA_MACSEC_USE_CFYE

/* Enable the WarmBoot API */
/*#define DA_MACSEC_USE_WARMBOOT */

/* end of file c_da_macsec.h */
