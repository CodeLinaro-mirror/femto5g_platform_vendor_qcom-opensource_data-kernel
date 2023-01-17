/* test_support.c
 *
 * Test Tool for CfyE and SecY API's
 * Support module for test case implementation
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

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

#include "test_support.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Default configuration */
#include "c_test_macsec.h"

/* Driver Framework Basic Defs API */
#include "basic_defs.h"

/* Driver Framework CLib Abstraction API */
#include "clib.h"

/* Test Case record format */
#include "test_record.h"

/* Logging API */
#include "log.h"

#ifdef TEST_MACSEC_DEBUG
/* Driver Debugging API */
#include "api_debug.h"
#endif /* TEST_MACSEC_DEBUG */


/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * test_macsec_rdtsc
 *
 * Read 64-bit time stamp counter value
 *
 * Note: this function is not supported on all host HW
 */
#ifdef ENABLE_THIS_SUPPORT_IF_NEEDED
void
test_macsec_rdtsc(
        Test_TSC_t * const TSC_p)
{
#ifdef ARCH_X86
    uint32_t Low32 = 0;
    uint32_t High32 = 0;

       asm ("xorl %%eax, %%eax\n\t"
            "cpuid\n\t"                       /* ensure in-order execution */
            "rdtsc\n\t"
            "movl %%eax, %0\n\t"
            "movl %%edx, %1"
            :"=r"(Low32), "=r"(High32)        /* output */
            :                                 /* no input */
            :"%eax", "%ebx", "%ecx", "%edx"   /* clobbered registers */
           );

    TSC_p->Low32  = Low32;
    TSC_p->High32 = High32;
#else
    /* Not supported for this host HW platform */
    IDENTIFIER_NOT_USED(TSC_p);
#endif /* !ARCH_X86 */
}
#endif /* ENABLE_THIS_SUPPORT_IF_NEEDED */


/*----------------------------------------------------------------------------
 * test_macsec_subadd_rdtsc
 */
#ifdef ENABLE_THIS_SUPPORT_IF_NEEDED
bool
test_macsec_subadd_rdtsc(
        Test_TSC_t * const A_TSC_p,
        Test_TSC_t * const B_TSC_p,
        Test_TSC_t * const C_TSC_p)
{
#ifdef ARCH_X86
    Test_TSC_t Temp_TSC;
    uint32_t Temp;

    ZEROINIT(Temp_TSC);

    /* Consistency checks */
    if (A_TSC_p->High32 > B_TSC_p->High32)
        return false; /* Unexpected input, does not compute! */

    if (A_TSC_p->Low32 > B_TSC_p->Low32 &&
        A_TSC_p->High32 == B_TSC_p->High32)
        return false; /* Unexpected input, does not compute! */

    /* Subtract low 32-bit counter */
    Temp_TSC.Low32 = B_TSC_p->Low32 - A_TSC_p->Low32;

    if (A_TSC_p->Low32 > B_TSC_p->Low32)
    {
        /* Consistency checks */
        if (B_TSC_p->High32 == 0)
            return false; /* Unexpected input, does not compute! */

        B_TSC_p->High32--;
    }

    /* Consistency checks */
    if (A_TSC_p->High32 > B_TSC_p->High32)
        return false; /* Unexpected input, does not compute! */

    /* Subtract high 32-bit counter */
    Temp_TSC.High32 = B_TSC_p->High32 - A_TSC_p->High32;

    /* Add low 32-bit counter */
    Temp = C_TSC_p->Low32 + Temp_TSC.Low32;

    /* Check for the overflow of the low 32-bit result counter */
    if (Temp < C_TSC_p->Low32)
    {
        /* Handle the overflow of the low 32-bit result counter */
        Temp = C_TSC_p->High32 + 1;

        if (Temp < C_TSC_p->High32)
            return false; /* Unexpected input, does not compute! */

        C_TSC_p->High32++;
    }

    /* Add high 32-bit counter */
    Temp = C_TSC_p->High32 + Temp_TSC.High32;

    /* Check for the overflow of the high 32-bit result counter */
    if (Temp < C_TSC_p->High32)
        return false; /* Unexpected input, does not compute! */

    C_TSC_p->Low32  += Temp_TSC.Low32;
    C_TSC_p->High32 += Temp_TSC.High32;

    return true; /* success */
#else
    /* Not supported for this host HW platform */
    IDENTIFIER_NOT_USED(A_TSC_p);
    IDENTIFIER_NOT_USED(B_TSC_p);
    IDENTIFIER_NOT_USED(C_TSC_p);

    return true;
#endif /* !ARCH_X86 */
}
#endif /* ENABLE_THIS_SUPPORT_IF_NEEDED */


/*----------------------------------------------------------------------------
 * test_macsec_util_rdtsc
 */
#ifdef ENABLE_THIS_SUPPORT_IF_NEEDED
bool
test_macsec_util_rdtsc(
        Test_TSC_t * const A_TSC_p,
        Test_TSC_t * const B_TSC_p,
        unsigned int * const Utilization)
{
#ifdef ARCH_X86
    /* Consistency checks */
    if (A_TSC_p->High32 > B_TSC_p->High32)
        return false; /* Unexpected input, does not compute! */

    if (A_TSC_p->Low32 > B_TSC_p->Low32 &&
        A_TSC_p->High32 == B_TSC_p->High32)
        return false; /* Unexpected input, does not compute! */

    if ((B_TSC_p->Low32 == 0) && (B_TSC_p->High32 == 0))
        return false; /* Unexpected input, does not compute! */

    {
        unsigned long long x, y, k, n;
        unsigned long long M = 0xFFFFFFFFl;

        M++;
        x = A_TSC_p->High32;
        y = A_TSC_p->Low32;
        k = B_TSC_p->High32;
        n = B_TSC_p->Low32;

        *Utilization = (unsigned int)test_macsec_div64((100 * (M * x + y)),
                                                        (M * k + n));
    }

    return true; /* success */
#else
    /* Not supported for this host HW platform */
    IDENTIFIER_NOT_USED(A_TSC_p);
    IDENTIFIER_NOT_USED(B_TSC_p);
    IDENTIFIER_NOT_USED(Utilization);

    return true;
#endif /* !ARCH_X86 */
}
#endif /* ENABLE_THIS_SUPPORT_IF_NEEDED */


/*----------------------------------------------------------------------------
 * test_macsec_get16
 */
#ifdef ENABLE_THIS_SUPPORT_IF_NEEDED
uint16_t
test_macsec_get16(
         uint8_t * p,
         const unsigned int offs)
{
    return (p[offs]<<8) | p[offs+1];
}
#endif /* ENABLE_THIS_SUPPORT_IF_NEEDED */


/*----------------------------------------------------------------------------
 * test_macsec_put16
 */
void
test_macsec_put16(
        uint8_t * p,
        const unsigned int offs,
        const uint16_t val)
{
    p[offs] = val >> 8;
    p[offs+1] = val & 0xff;
}


/*----------------------------------------------------------------------------
 * test_macsec_gen_frame
 */
void
test_macsec_gen_frame(
        uint8_t * Packet_p,
        unsigned int PacketByteCount,
        const uint8_t *MAC_DstAddr,
        const uint8_t *MAC_SrcAddr,
        const uint16_t Ether_Type)
{
    unsigned int i;
    uint8_t c = PacketByteCount & 0xff;

    /* Clear Ethernet frame header */
    memset(Packet_p, 0, 12);

    /* Fill in Ethernet frame header */
    memcpy(Packet_p, MAC_DstAddr, 6);        /* Destination address */
    memcpy(&Packet_p[6], MAC_SrcAddr, 6);    /* Source address */

    /* Ethertype */
    test_macsec_put16(Packet_p, 12, Ether_Type); /* EtherType */

    /* Fill in some payload data. */
    for (i = 14; i < PacketByteCount; i++)
    {
        Packet_p[i] = c;
        c++;
    }
}


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
        const unsigned int Offset)
{
    uint32_t Value32 = 0;

    if (Debug_Device_Read32(DeviceName_p,
                            Offset,
                            &Value32) == 0)
    {
        Log_FormattedMessage("TEST_MACSEC: Debug read32, "
                             "device %s, offset 0x%x, value 0x%x\n",
                             DeviceName_p,
                             Offset,
                             Value32);
    }
    else
    {
        LOG_CRIT("TEST_MACSEC: Failed, Debug read32 device %s\n",
                 DeviceName_p);
    }

    return;
}
#endif /* TEST_MACSEC_DEBUG */


/* end of file test_support.c */
