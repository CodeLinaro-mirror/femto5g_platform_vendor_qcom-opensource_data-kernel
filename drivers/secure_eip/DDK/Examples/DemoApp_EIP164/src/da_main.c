/* da_main.c
 *
 * Demo Application for MACsec.
 * Packets are classified in hardware (as configured by the CfyE API
 * according to the SA's installed via the SecY API.
 * Frames are submitted and retrieved via the VBAL Packet I/O API.
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

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Default configuration */
#include "c_da_macsec.h"

#ifdef DA_MACSEC_USERMODE
#include <stdlib.h>
#include <unistd.h>  /* usleep */
#include "api_driver164_init.h"
#else
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>       /* printk */
#include <linux/slab.h>
#include <asm/delay.h>          /* udelay */
#endif

#include "api_secy.h"
#include "api_cfye.h"

#include "basic_defs.h"
#include "clib.h"
#include "log.h"

/* Packet I/O API */
#include "api_pktio.h"

#include "da_internal.h"
#include "da_warmboot.h"

/*----------------------------------------------------------------------------
 * Definitions and macros
 */

#ifndef DA_MACSEC_USERMODE
MODULE_LICENSE(DA_MACSEC_LICENSE);
#endif

static void
da_macsec_test(
        bool fIngress)
{
    bool fResult;

    fResult = da_secy_bypass_drop(true,
                                  true, /* drop */
                                  fIngress,
                                  MIN_PKT_BYTE_COUNT,
                                  MIN_PKT_BYTE_COUNT,
                                  1);
    LOG_CRIT("DA_MACSEC: Single packet SecY drop test %s\n",
             fResult ? "PASSED" : "FAILED");

    fResult = da_secy_bypass_drop(true,
                                  false, /* bypass */
                                  fIngress,
                                  MIN_PKT_BYTE_COUNT,
                                  MIN_PKT_BYTE_COUNT,
                                  1);
    LOG_CRIT("DA_MACSEC: Single packet SecY bypass test %s\n",
             fResult ? "PASSED" : "FAILED");

#ifdef DA_MACSEC_MULTIPLE_PKT_TEST
    fResult = da_secy_bypass_drop(true,
                                  false, /* bypass */
                                  fIngress,
                                  MIN_PKT_BYTE_COUNT,
                                  MAX_PKT_BYTE_COUNT,
                                  13);
    LOG_CRIT("DA_MACSEC: Multiple packet SecY bypass test %s\n",
             fResult ? "PASSED" : "FAILED");
#endif /* DA_MACSEC_MULTIPLE_PKT_TEST */

    fResult = da_secy_macsec_transform(true, fIngress);
    LOG_CRIT("DA_MACSEC: Single packet SecY MACsec transform test %s\n",
             fResult ? "PASSED" : "FAILED");

    fResult = da_secy_macsec_rekey(true, fIngress);
    LOG_CRIT("DA_MACSEC: Single packet SecY MACsec rekey test %s\n",
             fResult ? "PASSED" : "FAILED");

#ifdef DA_MACSEC_USE_CFYE
    fResult = da_secy_cfye_bypass_drop(true,
                                       true, /* drop */
                                       fIngress,
                                       MIN_PKT_BYTE_COUNT,
                                       MIN_PKT_BYTE_COUNT,
                                       1);
    LOG_CRIT("DA_MACSEC: Single packet SecY/CfyE drop test %s\n",
             fResult ? "PASSED" : "FAILED");

    fResult = da_secy_cfye_bypass_drop(true,
                                       false, /* bypass */
                                       fIngress,
                                       MIN_PKT_BYTE_COUNT,
                                       MIN_PKT_BYTE_COUNT,
                                       1);
    LOG_CRIT("DA_MACSEC: Single packet SecY/CfyE bypass test %s\n",
             fResult ? "PASSED" : "FAILED");

#ifdef DA_MACSEC_MULTIPLE_PKT_TEST
    fResult = da_secy_cfye_bypass_drop(true,
                                       false, /* bypass */
                                       fIngress,
                                       MIN_PKT_BYTE_COUNT,
                                       MAX_PKT_BYTE_COUNT,
                                       13);
    LOG_CRIT("DA_MACSEC: Multiple packet SecY/CfyE bypass test %s\n",
             fResult ? "PASSED" : "FAILED");
#endif /* DA_MACSEC_MULTIPLE_PKT_TEST */

    fResult = da_secy_cfye_macsec_transform(true, fIngress);
    LOG_CRIT("DA_MACSEC: Single packet SecY/CfyE MACsec transform test %s\n",
             fResult ? "PASSED" : "FAILED");

#ifdef DA_MACSEC_SM4
    fResult = da_secy_cfye_macsec_transform_sm4(true, fIngress);
    LOG_CRIT("DA_MACSEC: Single packet SecY/CfyE SM4 MACsec transform test %s\n",
             fResult ? "PASSED" : "FAILED");
#endif

#ifdef DA_MACSEC_USE_DEVERROR
    fResult = da_secy_cfye_deverror(true, fIngress);
    LOG_CRIT("DA_MACSEC: Single packet SecY/CfyE MACsec device error test %s\n",
             fResult ? "PASSED" : "FAILED");
#endif

    fResult = da_secy_cfye_should_secure(true, false, fIngress);
    LOG_CRIT("DA_MACSEC: Single packet SecY/CfyE should-secure test %s\n",
             fResult ? "PASSED" : "FAILED");

    fResult = da_secy_cfye_should_secure(true, true, fIngress);
    LOG_CRIT("DA_MACSEC: Single packet SecY/CfyE drop-control test %s\n",
             fResult ? "PASSED" : "FAILED");

    fResult = da_secy_cfye_control_pkt_nodef(true, fIngress);
    LOG_CRIT("DA_MACSEC: Single packet SecY/CfyE control-packets no d e f a u l t vPorts test %s\n",
             fResult ? "PASSED" : "FAILED");

    fResult = da_secy_cfye_control_pkt(true, fIngress);
    LOG_CRIT("DA_MACSEC: Single packet SecY/CfyE control-packets test %s\n",
             fResult ? "PASSED" : "FAILED");


    fResult = da_secy_cfye_QinQ_MACsec_transform(true, fIngress);
    LOG_CRIT("DA_MACSEC: Single packet SecY/CfyE two VLAN tags (QinQ) MACsec "
             "transform test %s\n",
             fResult ? "PASSED" : "FAILED");

#ifdef DA_IPSEC_ENABLE
    /** IPsec test case */
    fResult = da_secy_cfye_IPsec_transform(true, fIngress);
    LOG_CRIT("DA_MACSEC: Single packet SecY/CfyE IPSec transform test %s\n",
             fResult ? "PASSED" : "FAILED");
#endif

#ifdef DA_MACSEC_VXLAN_ENABLE
    fResult = da_secy_cfye_VxLAN_MACsec_transform(true, fIngress);
    LOG_CRIT("DA_MACSEC: Single packet SecY/CfyE VxLAN "
             "MACsec transform test %s\n",
             fResult ? "PASSED" : "FAILED");

#endif

#endif  /* end of DA_MACSEC_USE_CFYE */
}


static int
da_macsec_module_init(void)
{
#ifdef DA_MACSEC_MODE_EGRESS
    /* Run the tests for the egress device configuration */
    da_macsec_test(false);
#endif

#ifdef DA_MACSEC_MODE_INGRESS
    /* Run the tests for the ingress device configuration */
    da_macsec_test(true);
#endif

    return 0;
}


static void
da_macsec_module_exit(void)
{
    Log_FormattedMessage("DA_MACSEC unloaded\n");
}


#ifdef DA_MACSEC_USERMODE
/* Application entry point */
int main(void)
{
#ifdef DA_MACSEC_USE_WARMBOOT
    da_macsec_warmboot_init();
#endif
    Driver164_Init();
    PktIO_Init();

    da_macsec_module_init();
    da_macsec_module_exit();

    Driver164_Exit();
#ifdef DA_MACSEC_USE_WARMBOOT
    da_macsec_warmboot_uninit();
#endif
    return 0;
}
#else
module_init(da_macsec_module_init);
module_exit(da_macsec_module_exit);
#endif


/* end of file da_main.c */
