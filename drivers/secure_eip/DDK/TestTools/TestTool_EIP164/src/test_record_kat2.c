/* test_record_kat2.c
 *
 * Test Tool for CfyE and SecY API's
 * Test record definition for KAT1 test
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

#include "test_record_kat2.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

#include "test_support.h"

/* Driver Framework Basic Defs API */
#include "basic_defs.h"

/* Driver Framework CLib aAbstraction API */
#include "clib.h"                  /* ZEROINIT() */

/* Test configuration and vectors for the Packet Sanity Check Fail test case */
#include "test_vector_kat2.h"      /* TCV_KAT_2 */


/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * Local variables
 */


/*----------------------------------------------------------------------------
 * test_macsec_kat2_rec_init
 */
void
test_macsec_kat2_rec_init(
        Test_Case_Record_t ** TestRec_pp,
        unsigned int * const TestRecordCount_p)
{
    /* Set the pre-set test case conf params and vectors in the record */
    *TestRecordCount_p = (sizeof(TCV_KAT_2) / sizeof(Test_Case_Record_t));
    *TestRec_pp        = TCV_KAT_2;

    return;
}


/*----------------------------------------------------------------------------
 * test_macsec_kat2_rec_uninit
 */
void
test_macsec_kat2_rec_uninit(
        Test_Case_Record_t * TestRec_p,
        const unsigned int TestRecordCount)
{
    IDENTIFIER_NOT_USED(TestRec_p);
    IDENTIFIER_NOT_USED(TestRecordCount);

    return;
}


/* end of file test_record_kat2.c */
