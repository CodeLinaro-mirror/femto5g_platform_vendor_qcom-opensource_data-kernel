/* test_record_kat5.h
 *
 * Test Tool for CfyE and SecY API's
 * Test Record initialization for the Packet KAT 5 test case
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

#ifndef TEST_RECORD_KAT_5_H_
#define TEST_RECORD_KAT_5_H_

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

/* Device administration structure */
typedef struct
{
    /* Device name */
    const char * DeviceName_p;

    /* Device offset range inside system memory map */
    unsigned int Start;
    unsigned int End;

    /* Implementation specific device flags */
    char Flags;

} Test_Device_t;


/* Data path administration structure */
typedef struct
{
    /* Data path index. */
    unsigned int index;

    /* Device offset range and flags of EIP164 */
    unsigned int StartByteOffset1;
    unsigned int LastByteOffset1;
    unsigned int Flags1;

    /* Device offset range and flags of EIP163 */
    unsigned int StartByteOffset2;
    unsigned int LastByteOffset2;
    unsigned int Flags2;
} Test_DataPath_t;


/* KAT5 test record */
typedef struct
{
    /* Number of test devices, nut used when Devices below is set to NULL */
    unsigned int DeviceCount;

    /* Device list of DeviceCount elements to be used for tests. */
    /* If NULL then the already existing devices will be used. */
    /* If not-NULL then all the existing devices will be removed and */
    /* the new ones from the list will be added. */
    Test_Device_t * Devices;

    /* Number of test data paths, nut used when DataPaths below is set to NULL */
    unsigned int DataPathCount;

    /* List of data paths to be added back after removing the existing ones. */
    Test_DataPath_t * DataPaths;

    /* Generic part of the test record */
    Test_Case_Record_t Generic;

} Test_Case_Record_KAT5_t;


/*----------------------------------------------------------------------------
 * test_macsec_kat5_rec_init
 */
void
test_macsec_kat5_rec_init(
        Test_Case_Record_KAT5_t ** TestRec_pp,
        unsigned int * const TestRecordCount_p);


/*----------------------------------------------------------------------------
 * test_macsec_kat5_rec_uninit
 */
void
test_macsec_kat5_rec_uninit(
        Test_Case_Record_KAT5_t * TestRec_p,
        const unsigned int TestRecordCount);


#endif /* TEST_RECORD_KAT_5_H_ */


/* end of file test_record_kat5.h */
