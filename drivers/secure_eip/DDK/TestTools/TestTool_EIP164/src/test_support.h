/* test_support.h
 *
 * Test Tool for CfyE and SecY API's
 * Support module interface
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

#ifndef TEST_MACSEC_SUPPORT_H
#define TEST_MACSEC_SUPPORT_H

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Driver Framework Basic Defs API */
#include "basic_defs.h"

/* Test Case record format */
#include "test_record.h"

#ifdef TEST_MACSEC_USERMODE
#include <stdlib.h>
#include <unistd.h>             /* usleep */
#include <time.h>               /* time */
#else
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>       /* printk */
#include <linux/slab.h>
#include <asm/delay.h>          /* udelay */
#include <linux/time.h>         /* timeval, do_gettimeofday */
#include <linux/math64.h>       /* div64_s64 */
#include <linux/sched.h>        /* yield */
#endif /* TEST_MACSEC_USERMODE */


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

#ifdef TEST_MACSEC_USERMODE
#define test_macsec_malloc(s)      malloc(s)
#define test_macsec_free(s)        free(s)
#define test_macsec_usleep(s)      usleep(s)
#define test_macsec_get_time()     time(NULL)
#define test_macsec_div64(a,b)     (a / b)
#define test_macsec_schedule()
#else
#define test_macsec_malloc(s)      kmalloc(s, GFP_KERNEL)
#define test_macsec_free(s)        kfree(s)
#define test_macsec_usleep(s)      udelay(s)
#define test_macsec_get_time()     get_seconds()
#define test_macsec_div64(a,b)     div64_u64(a,b)
#define test_macsec_schedule()     yield()
#endif /* TEST_MACSEC_USERMODE */

typedef struct
{
    uint32_t Low32;
    uint32_t High32;
} Test_TSC_t;


/*----------------------------------------------------------------------------
 * Local variables
 */


/*----------------------------------------------------------------------------
 * test_macsec_discard_const
 *
 * Discards the const typedef to prevent warnings
 */
static inline void *
test_macsec_discard_const(
        const void * Ptr_p)
{
    union
    {
        const void * c_p;
        void * n_p;
    } Conversion;

    Conversion.c_p = Ptr_p;
    return Conversion.n_p;
}

/*----------------------------------------------------------------------------
 * test_macsec_rdtsc
 *
 * Read 64-bit time stamp counter value
 *
 * Note: this function is not supported on all host HW
 */
void
test_macsec_rdtsc(
        Test_TSC_t * const TSC_p);


/*----------------------------------------------------------------------------
 * test_macsec_subadd_rdtsc
 *
 * Subtract 64-bit time stamp counter value A from B and add the result to
 * the value C
 *
 * Return value
 *   True:  operation succeeded
 *   False: operation failed
 */
bool
test_macsec_subadd_rdtsc(
        Test_TSC_t * const A_TSC_p,
        Test_TSC_t * const B_TSC_p,
        Test_TSC_t * const C_TSC_p);


/*----------------------------------------------------------------------------
 * test_macsec_util_rdtsc
 *
 * Calculate the utilization as a percentage of value A from value B
 *
 * Return value
 *   True:  operation succeeded
 *   False: operation failed
 */
bool
test_macsec_util_rdtsc(
        Test_TSC_t * const A_TSC_p,
        Test_TSC_t * const B_TSC_p,
        unsigned int * const Utilization);


/*----------------------------------------------------------------------------
 * test_macsec_get16
 *
 * Write byte array to 16-bit value in network byte order.
 */
uint16_t
test_macsec_get16(
        uint8_t * p,
        const unsigned int offs);


/*----------------------------------------------------------------------------
 * test_macsec_put16
 *
 * Write 16-bit value to byte array in network byte order.
 */
void
test_macsec_put16(
        uint8_t * p,
        const unsigned int offs,
        const uint16_t val);


/*----------------------------------------------------------------------------
 * test_macsec_gen_frame
 *
 * Generate a valid Ethernet frame of the specified length
 * (must be at least MIN_PKT_BYTE_COUNT octets).
 */
void
test_macsec_gen_frame(
        uint8_t * Packet_p,
        unsigned int PacketByteCount,
        const uint8_t *MAC_DstAddr,
        const uint8_t *MAC_SrcAddr,
        const uint16_t Ether_Type);


#ifdef TEST_MACSEC_DEBUG
/*----------------------------------------------------------------------------
 * test_macsec_debug_read32
 *
 * Read 32-bit value from the driver device
 *
 * Note: this function is supported on for debugging mode only
 */
void
test_macsec_debug_read32(
        const char * const DeviceName_p,
        const unsigned int Offset);
#endif /* TEST_MACSEC_DEBUG */


#endif /* TEST_MACSEC_SUPPORT_H */


/* end of file test_support.h */
