/* test_case_specification.h
 *
 * Test Tool for CfyE and SecY API's
 * This module defines the test cases
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

#ifndef TEST_MACSEC_DEFINITION_H
#define TEST_MACSEC_DEFINITION_H

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Driver Framework Basic Defs API */
#include "basic_defs.h"

/* General test support internal interface */
#include "test_support.h"

/* Test Case KAT 1 record format */
#include "test_record_kat1.h"

/* Test Case KAT 2 record format */
#include "test_record_kat2.h"

/* Test Case KAT 3 record format */
#include "test_record_kat3.h"

/* Test Case KAT 4 record format */
#include "test_record_kat4.h"

/* Test Case KAT 5 record format */
#include "test_record_kat5.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * Local variables
 */


/*----------------------------------------------------------------------------
 * test_macsec_kat1
 *
 * Test case for packet processing Known Answer Tests set 1.
 *
 * TestPass (input)
 *     The pass level of the test. (Use depends on the build)
 *
 * TestRec_p (input)
 *     Pointer to the array of test case records that contain
 *     configuration parameters and test vectors
 *
 * TestRecordCount (input)
 *     Number of test records in the array
 *
 * Return
 *     true if all tests passed, otherwise false
 */
bool
test_macsec_kat1(
        unsigned int TestPass,
        const Test_Case_Record_t * TestRec_p,
        const unsigned int TestRecordCount);


/*----------------------------------------------------------------------------
 * test_macsec_kat2
 *
 * Test case for packet processing Known Answer Tests set 2.
 *
 * TestPass (input)
 *     The pass level of the test. (Use depends on the build)
 *
 * TestRec_p (input)
 *     Pointer to the array of test case records that contain
 *     configuration parameters and test vectors
 *
 * TestRecordCount (input)
 *     Number of test records in the array
 *
 * Return: none
 */
void
test_macsec_kat2(
        unsigned int TestPass,
        const Test_Case_Record_t * TestRec_p,
        const unsigned int TestRecordCount);


/*----------------------------------------------------------------------------
 * test_macsec_kat3
 *
 * Test case for packet processing Known Answer Tests set 3.
 *
 * TestPass (input)
 *     The pass level of the test. (Use depends on the build)
 *
 * TestRec_p (input)
 *     Pointer to the array of test case records that contain
 *     configuration parameters and test vectors
 *
 * TestRecordCount (input)
 *     Number of test records in the array
 *
 * Return: none
 */
void
test_macsec_kat3(
        unsigned int TestPass,
        const Test_Case_Record_t * TestRec_p,
        const unsigned int TestRecordCount);


/*----------------------------------------------------------------------------
 * test_macsec_kat4
 *
 * Test case for packet processing Known Answer Tests set 4.
 *
 * TestPass (input)
 *     The pass level of the test. (Use depends on the build)
 *
 * TestRec_p (input)
 *     Pointer to the array of test case records that contain
 *     configuration parameters and test vectors
 *
 * TestRecordCount (input)
 *     Number of test records in the array
 *
 * Return: none
 */
void
test_macsec_kat4(
        unsigned int TestPass,
        const Test_Case_Record_t * TestRec_p,
        const unsigned int TestRecordCount);


/*----------------------------------------------------------------------------
 * test_macsec_kat5
 *
 * Test case for packet processing Known Answer Tests set 5.
 *
 * TestPass (input)
 *     The pass level of the test. (Use depends on the build)
 *
 * TestRec_p (input)
 *     Pointer to the array of test case records that contain
 *     configuration parameters and test vectors
 *
 * TestRecordCount (input)
 *     Number of test records in the array
 *
 * Return: none
 */
void
test_macsec_kat5(
        unsigned int TestPass,
        const Test_Case_Record_KAT5_t * TestRec_p,
        const unsigned int TestRecordCount);


#endif /* TEST_MACSEC_DEFINITION_H */


/* end of file test_case_specification.h */
