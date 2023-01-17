/* test_record_kat2.h
 *
 * Test Tool for CfyE and SecY API's
 * Test Record initialization for the Packet KAT 2 test case
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

#ifndef TEST_RECORD_KAT_2_H_
#define TEST_RECORD_KAT_2_H_

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Driver Framework Basic Defs API */
#include "basic_defs.h"

/* Test Case record format */
#include "test_record.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

/*----------------------------------------------------------------------------
 * test_macsec_kat2_rec_init
 */
void
test_macsec_kat2_rec_init(
        Test_Case_Record_t ** TestRec_pp,
        unsigned int * const TestRecordCount_p);


/*----------------------------------------------------------------------------
 * test_macsec_kat2_rec_uninit
 */
void
test_macsec_kat2_rec_uninit(
        Test_Case_Record_t * TestRec_p,
        const unsigned int TestRecordCount);


#endif /* TEST_RECORD_KAT_2_H_ */


/* end of file test_record_kat2.h */
