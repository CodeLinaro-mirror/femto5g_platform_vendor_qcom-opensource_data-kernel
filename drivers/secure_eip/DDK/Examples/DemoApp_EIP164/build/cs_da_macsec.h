/* cs_da_macsec.h
 *
 * Top-level Demo Application for MACsec
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

/* this file is included by c_da_macsec.h to get configuration switches */

#include "cs_systemtestconfig.h"      /* defines SYSTEMTEST_CONFIG_Cnn */

#include "cs_da_macsec_ext.h"         /* Platform-specific extensions */

/* log level for the entire adapter (for now) */
/* choose from LOG_SEVERITY_INFO, LOG_SEVERITY_WARN, LOG_SEVERITY_CRIT */
#define LOG_SEVERITY_MAX  LOG_SEVERITY_INFO

#define DA_MACSEC_LICENSE "GPL"

/* C0 = Egress, HW conf -e */
#ifdef SYSTEMTEST_CONFIGURATION_C0
#define DA_MACSEC_MODE_EGRESS
/*#define DA_MACSEC_MODE_INGRESS */
#define DA_MACSEC_USE_WARMBOOT
#endif

/* C1 = Ingress, HW conf -i */
#ifdef SYSTEMTEST_CONFIGURATION_C1
/*#define DA_MACSEC_MODE_EGRESS */
#define DA_MACSEC_MODE_INGRESS
#define DA_MACSEC_USE_WARMBOOT
#endif

/* C3 = Egress, HW conf -e */
#ifdef SYSTEMTEST_CONFIGURATION_C3
#define DA_MACSEC_MODE_EGRESS
/*#define DA_MACSEC_MODE_INGRESS */
/*#define DA_MACSEC_USE_WARMBOOT */
#endif

/* C4 = Ingress, HW conf -i */
#ifdef SYSTEMTEST_CONFIGURATION_C4
/*#define DA_MACSEC_MODE_EGRESS */
#define DA_MACSEC_MODE_INGRESS
/*#define DA_MACSEC_USE_WARMBOOT */
#endif


/* Enable the tests that use the CfyE API */
#define DA_MACSEC_USE_CFYE

/* Test SM4 operation (not supported on all hardware configurations) */
/* #define DA_MACSEC_SM4 */

/* end of file cs_da_macsec.h */
