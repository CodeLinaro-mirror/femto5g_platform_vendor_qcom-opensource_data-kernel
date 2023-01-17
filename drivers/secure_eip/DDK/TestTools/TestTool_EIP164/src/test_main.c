/* test_main.c
 *
 * Test Tool for CfyE and SecY API's
 * Test Tool main module
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
 * This module uses (requires) the following interface(s):
 */

/* Default configuration */
#include "c_test_macsec.h"

#ifdef TEST_MACSEC_USERMODE
#include "api_driver164_init.h"
#endif /* TEST_MACSEC_USERMODE */

#include "api_cfye.h"
#include "api_secy.h"
#include "api_pktio.h"

/* Driver Framework Basic Defs API */
#include "basic_defs.h"

/* Driver Framework CLib Abstraction API */
#include "clib.h"

/* Logging API */
#include "log.h"

/* Test case support functionality */
#include "test_support.h"

/* Warmboot support functionality. */
#include "test_warmboot.h"

/* Test case record management */
#include "test_record_kat1.h"
#include "test_record_kat2.h"
#include "test_record_kat3.h"
#include "test_record_kat4.h"
#include "test_record_kat5.h"

/* Test cases definition */
#include "test_case_specification.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

#ifndef TEST_MACSEC_USERMODE
#define EXPORT_SYMTAB
MODULE_LICENSE(TEST_MACSEC_LICENSE);
#endif /* TEST_MACSEC_USERMODE */


/*----------------------------------------------------------------------------
 * test_macsec_module_init
 */
static int
test_macsec_module_init(void)
{
    unsigned int TestPass;
    unsigned int TestRecordCount;

    Log_FormattedMessage("\nTEST_MACSEC: Test Tool loaded\n");

#ifdef TEST_MACSEC_USE_CFYE
    for(TestPass = 0; TestPass < 2; TestPass++)
#else
    for(TestPass = 0; TestPass < 1; TestPass++)
#endif /* TEST_MACSEC_USE_CFYE */
    {
        Log_FormattedMessage("\nTEST_MACSEC: Pass %d\n", (TestPass + 1));

#ifndef TEST_MACSEC_KAT1_REMOVE
        {
            /* Test case: TEST_MACSEC_TC_ID_KAT_1 */
            Test_Case_Record_t * TestRec_p = NULL;

            TestRecordCount = 0;
            test_macsec_kat1_rec_init(&TestRec_p, &TestRecordCount);

            if ((TestRecordCount != 0) && (TestRec_p != NULL))
                test_macsec_kat1(TestPass, TestRec_p, TestRecordCount);

            test_macsec_kat1_rec_uninit(TestRec_p, TestRecordCount);
        }
#endif

#ifndef TEST_MACSEC_KAT2_REMOVE
        {
            /* Test case: TEST_MACSEC_TC_ID_KAT_2 */
            Test_Case_Record_t * TestRec_p = NULL;

            TestRecordCount = 0;
            test_macsec_kat2_rec_init(&TestRec_p, &TestRecordCount);

            if ((TestRecordCount != 0) && (TestRec_p != NULL))
                test_macsec_kat2(TestPass, TestRec_p, TestRecordCount);

            test_macsec_kat2_rec_uninit(TestRec_p, TestRecordCount);
        }
#endif

#ifndef TEST_MACSEC_KAT3_REMOVE
        {
            /* Test case: TEST_MACSEC_TC_ID_KAT_3 */
            Test_Case_Record_t * TestRec_p = NULL;

            TestRecordCount = 0;
            test_macsec_kat3_rec_init(&TestRec_p, &TestRecordCount);

            if ((TestRecordCount != 0) && (TestRec_p != NULL))
                test_macsec_kat3(TestPass, TestRec_p, TestRecordCount);

            test_macsec_kat3_rec_uninit(TestRec_p, TestRecordCount);
        }
#endif

#ifndef TEST_MACSEC_KAT4_REMOVE
        {
            /* Test case: TEST_MACSEC_TC_ID_KAT_4 */
            Test_Case_Record_t * TestRec_p = NULL;

            TestRecordCount = 0;
            test_macsec_kat4_rec_init(&TestRec_p, &TestRecordCount);

            if ((TestRecordCount != 0) && (TestRec_p != NULL))
                test_macsec_kat4(TestPass, TestRec_p, TestRecordCount);

            test_macsec_kat4_rec_uninit(TestRec_p, TestRecordCount);
        }
#endif

#ifndef TEST_MACSEC_KAT5_REMOVE
        {
            Test_Case_Record_KAT5_t * TestRecKAT5_p = NULL;

            /* Test case: TEST_MACSEC_TC_ID_KAT_5 */
            TestRecordCount = 0;
            test_macsec_kat5_rec_init(&TestRecKAT5_p, &TestRecordCount);

            if ((TestRecordCount != 0) && (TestRecKAT5_p != NULL))
                test_macsec_kat5(TestPass, TestRecKAT5_p, TestRecordCount);

            test_macsec_kat5_rec_uninit(TestRecKAT5_p, TestRecordCount);
        }
#endif

#ifdef TEST_MACSEC_USE_WARMBOOT
        /* Note: Only run this test after the first pass, as it will access */
        /* EIP163 registers, causing the test system to switch to CfyE mode. */
        test_macsec_warmboot_maxsize_get();
#endif
    }

    return 0;
}


/*----------------------------------------------------------------------------
 * test_macsec_module_exit
 */
static void
test_macsec_module_exit(void)
{
    Log_FormattedMessage("\nTEST_MACSEC: Test Tool unloaded\n");
}


#ifdef TEST_MACSEC_USERMODE
/*----------------------------------------------------------------------------
 * main
 */
int main(void)
{
#ifdef TEST_MACSEC_USE_WARMBOOT
    if (!test_macsec_warmboot_init())
    {
        return -1;
    }
#endif

    Driver164_Init();
    PktIO_Init();

    test_macsec_module_init();
    test_macsec_module_exit();

    Driver164_Exit();
#ifdef TEST_MACSEC_USE_WARMBOOT
    test_macsec_warmboot_uninit();
#endif

    return 0;
}
#else
module_init(test_macsec_module_init);
module_exit(test_macsec_module_exit);
#endif /* TEST_MACSEC_USERMODE */


/* end of file test_main.c */
