/* cs_test_macsec.h
 *
 * Test Tool for CfyE and SecY API's
 * Top-level configuration file
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


#include "cs_systemtestconfig.h"        /* defines SYSTEMTEST_CONFIG_Cnn */

#include "cs_test_macsec_ext.h"         /* Platform-specific conf parameters */

#include "cs_hwpal.h"                   /* HWPAL_DEVICES */

/* Devices that can be added and removed one at a time. */
/* Borrow these from the HWPAL configuration. */
/*    Name           StartOffs LastOFfs  Flags */

#define HWPAL_DEVICE_ADD(_name,_devnr,_start,_end,_flags)   \
    {_name, _start, _end, _flags}

#define TEST_MACSEC_DEVICES HWPAL_DEVICES


/* EIP164 data paths (consisting of many sub-devices) to be added */
/* and removed one a a time. */
/*      EIP164                       EIP163 */
/*   Id StartOffs   LastOffs  Flags StartOffs   LastOffs  Flags */
#define TEST_MACSEC_DATAPATHS \
    {0, 0x00000000, 0x001fffff, 7,  0x00800000, 0x0087ffff, 7}, \
    {1, 0x00000000, 0x001fffff, 7,  0x00800000, 0x0087ffff, 7}


/*----------------------------------------------------------------------------
 * CAUTION: These configuration parameter are derived from
 *          the build environment configuration and may not be modified here!
 */
/*---------------------------------------------------------------------------*/

/* log level for the entire adapter (for now) */
/* choose from LOG_SEVERITY_INFO, LOG_SEVERITY_WARN, LOG_SEVERITY_CRIT */
#define LOG_SEVERITY_MAX  LOG_SEVERITY_WARN

#define TEST_MACSEC_LICENSE "GPL"

/* Enables debugging traces */
/*#define TEST_MACSEC_DEBUG */

/* C0 = SecY notifications, Egress, HW conf -e */
#ifdef SYSTEMTEST_CONFIGURATION_C0
#define TEST_MACSEC_MODE_EGRESS
/*#define TEST_MACSEC_MODE_INGRESS */
#define TEST_MACSEC_SECY_NOTIFY_ENABLE
#define TEST_MACSEC_USE_WARMBOOT
#define TEST_MACSEC_WRITE_TO_DECREMENT 1
#endif

/* C1 = No SecY notifications, Ingress, HW conf -i */
#ifdef SYSTEMTEST_CONFIGURATION_C1
/*#define TEST_MACSEC_MODE_EGRESS */
#define TEST_MACSEC_MODE_INGRESS
/*#define TEST_MACSEC_SECY_NOTIFY_ENABLE */
#define TEST_MACSEC_USE_WARMBOOT
#define TEST_MACSEC_WRITE_TO_DECREMENT 1
#endif

/* C3 = No SecY notifications, Egress, HW conf -e */
#ifdef SYSTEMTEST_CONFIGURATION_C3
#define TEST_MACSEC_MODE_EGRESS
/*#define TEST_MACSEC_MODE_INGRESS */
/*#define TEST_MACSEC_SECY_NOTIFY_ENABLE */
/*#define TEST_MACSEC_USE_WARMBOOT */
#define TEST_MACSEC_WRITE_TO_DECREMENT 0
#endif

/* C4 = SecY notifications, Ingress, HW conf -i */
#ifdef SYSTEMTEST_CONFIGURATION_C4
/*#define TEST_MACSEC_MODE_EGRESS */
#define TEST_MACSEC_MODE_INGRESS
#define TEST_MACSEC_SECY_NOTIFY_ENABLE
/*#define TEST_MACSEC_USE_WARMBOOT */
#define TEST_MACSEC_WRITE_TO_DECREMENT 0
#endif


/* Enable the crypt-authenticate feature verification, */
/* which can be provided as part of the MACsec Engine (SecY) */
#define TEST_MACSEC_SECY_CRYPT_AUTH_ENABLE

/* Enable the classification functionality, */
/* which is provided by the Classification Engine (CfyE) */
#define TEST_MACSEC_USE_CFYE

/* Use the Driver Read functions to read SA parameters, rules, vPorts */
#define TEST_MACSEC_USE_READ_API

#ifdef TEST_MACSEC_SECY_NOTIFY_ENABLE
#define SECY_CHANNEL_NOTIFY_NEEDED
#endif

/* Enable per-counter summary registers. */
/*#define TEST_MACSEC_PERCOUNTER_SUMMARY_ENABLE */

/*#define TEST_MACSEC_KAT1_REMOVE */
/*#define TEST_MACSEC_KAT2_REMOVE */
/*#define TEST_MACSEC_KAT3_REMOVE */
/*#define TEST_MACSEC_KAT4_REMOVE */
/*#define TEST_MACSEC_KAT5_REMOVE */


/* end of file cs_test_macsec.h */
