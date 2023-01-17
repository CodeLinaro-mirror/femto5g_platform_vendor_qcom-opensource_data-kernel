/* test_record_kat5.c
 *
 * Test Tool for CfyE and SecY API's
 * Test record definition for KAT4 test
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

#include "test_record_kat5.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

#include "test_record.h"

/* Test configuration and vectors for the KAT 5 test case */
#include "test_vector_kat5.h"      /* TCV_KAT_5 */


/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * Local variables
 */


/*----------------------------------------------------------------------------
 * test_macsec_kat5_rec_init
 */
void
test_macsec_kat5_rec_init(
        Test_Case_Record_KAT5_t ** TestRec_pp,
        unsigned int * const TestRecordCount_p)
{
    unsigned int i, count;
    Test_Case_Record_KAT5_t * TestRec_p = TCV_KAT_5;

    /* Set the pre-set test case conf params and vectors in the record */
    count = sizeof(TCV_KAT_5) / sizeof(Test_Case_Record_KAT5_t);

    *TestRecordCount_p = count;
    *TestRec_pp        = TestRec_p;

    /* Override the pre-set test case conf params and vectors in the record */
    for (i = 0; i < count; i++)
    {
        Test_Device_t * Device_p = TestRec_p->Devices;
        Test_DataPath_t * DataPath_p = TestRec_p->DataPaths;

        TestRec_p->DeviceCount = 0;

        /* Count all the devices in the device list for each test record */
        while(Device_p &&
              !(Device_p->DeviceName_p == NULL &&
                Device_p->Start == 0 &&
                Device_p->End == 0 &&
                Device_p->Flags == 0)) /* loop until 0-device is found */
        {
            TestRec_p->DeviceCount++;
            Device_p++;
        } /* while */

        TestRec_p->DataPathCount = 0;

        /* Count all the data paths in the data path list for each test record */
        while(DataPath_p &&
              !(DataPath_p->LastByteOffset1 == 0 &&
                DataPath_p->LastByteOffset2 == 0))
        /* loop until 0-datapath is found */
        {
            TestRec_p->DataPathCount++;
            DataPath_p++;
        } /* while */

        TestRec_p++;
    } /* for */

    return;
}


/*----------------------------------------------------------------------------
 * test_macsec_kat5_rec_uninit
 */
void
test_macsec_kat5_rec_uninit(
        Test_Case_Record_KAT5_t * TestRec_p,
        const unsigned int TestRecordCount)
{
    IDENTIFIER_NOT_USED(TestRec_p);
    IDENTIFIER_NOT_USED(TestRecordCount);

    return;
}


/* end of file test_record_kat5.c */
