/* test_case_kat5.c
 *
 * Test Tool for CfyE and SecY API's
 * KAT 5 test implementation
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

/* Definition of test cases to implement */
#include "test_case_specification.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Default configuration */
#include "c_test_macsec.h"

/* Test Case KAT 5 record format */
#include "test_record_kat5.h"

/* General test support internal interface */
#include "test_support.h"

/* General test case internal interface */
#include "test_case.h"

/* Driver Init API */
#include "api_driver164_init.h"

/* Driver Framework Basic Definitions API */
#include "basic_defs.h"

/* Driver Framework C-Library Abstraction API */
#include "clib.h"

/* Logging API */
#include "log.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * Local variables
 */


/*----------------------------------------------------------------------------
 * test_macsec_kat5
 */
void
test_macsec_kat5(
        unsigned int TestPass,
        const Test_Case_Record_KAT5_t * TestRec_p,
        const unsigned int TestRecordCount)
{
    unsigned int i, j, Count;
    bool fRetry;

    if ((TestRec_p == NULL) || (TestRecordCount == 0))
    {
        LOG_CRIT("\nTEST_MACSEC: Warning, no KAT5 test record(s) provided\n");
        return;
    }

    for (i = 0; i < TestRecordCount; i++)
    {
#ifdef TEST_MACSEC_USE_CFYE
        if (((TestPass == 0) && (TestRec_p->Generic.CfyE_Data_p != NULL)) ||
            ((TestPass != 0) && (TestRec_p->Generic.CfyE_Data_p == NULL)))
        {
            goto test_case_next;
        }
#else
        IDENTIFIER_NOT_USED(TestPass);
#endif /* TEST_MACSEC_USE_CFYE */

        if (TestRec_p->Devices != NULL && TestRec_p->DeviceCount >= 1)
        {
            Count = Driver164_Device_GetCount();
            if (Count > 0)
            {
                LOG_CRIT("\nTEST_MACSEC: KAT5, remove all %d devices\n", Count);

                fRetry = true;
                /* Remove all the devices from the device list */
                for (j = 0; j < Count; j++)
                {
                    /* Remove device at index j */
                    if (Driver164_Device_Remove(j) < 0)
                    {
                        LOG_CRIT("TEST_MACSEC: KAT5 "
                                 "failed to remove device %d\n",
                                 j);
                        goto test_error;
                    }

                    /* Try to remove the same device again, this should fail */
                    if (fRetry && Driver164_Device_Remove(j) >= 0)
                    {
                        LOG_CRIT("TEST_MACSEC: KAT5 failed, "
                                 "removed device %d twice\n",
                                 j);
                        goto test_error;
                    }
                    else
                        fRetry = false; /* do it for device[0] only */
                } /* for, remove devices */
            }

            LOG_CRIT("TEST_MACSEC: KAT5, add all %d devices\n", Count);

            Count = TestRec_p->DeviceCount;
            fRetry = true;
            /* Add devices from the device list */
            for (j = 0; j < Count; j++)
            {
                Driver164_Device_t Device;

                ZEROINIT(Device);

                Device.DeviceName_p =
                        test_macsec_malloc(
                               strlen(TestRec_p->Devices[j].DeviceName_p) + 1);
                if (Device.DeviceName_p)
                    strcpy(Device.DeviceName_p,
                           TestRec_p->Devices[j].DeviceName_p);
                else
                {
                    LOG_CRIT("TEST_MACSEC: KAT5, "
                             "failed to allocate memory for device %d\n", j);
                    goto test_error;
                }

                Device.Flags           = TestRec_p->Devices[j].Flags;
                Device.StartByteOffset = TestRec_p->Devices[j].Start;
                Device.LastByteOffset  = TestRec_p->Devices[j].End;

                /* Add device at index j */
                if (Driver164_Device_Add(j, &Device) < 0)
                {
                    LOG_CRIT("TEST_MACSEC: KAT5, failed to add device %d\n", j);
                    test_macsec_free(Device.DeviceName_p);
                    goto test_error;
                }

                /* Try to add another device at the same index, this should fail */
                if (fRetry && Driver164_Device_Add(j, &Device) >= 0)
                {
                    LOG_CRIT("TEST_MACSEC: KAT5 failed, "
                             "added device %d twice\n",
                             j);
                    test_macsec_free(Device.DeviceName_p);
                    goto test_error;
                }

                /* Try to add device with the same name at a new index, */
                /* this should fail */
                if (fRetry && Driver164_Device_Add(j + 1, &Device) >= 0)
                {
                    LOG_CRIT("TEST_MACSEC: KAT5 failed, "
                             "added device %s twice\n",
                             Device.DeviceName_p);
                    test_macsec_free(Device.DeviceName_p);
                    goto test_error;
                }
                else
                    fRetry = false; /* do it for device[0] only */

                test_macsec_free(Device.DeviceName_p);
            } /* for, add devices */
        } /* devices remove / add done */

        if (TestRec_p->DataPaths != NULL && TestRec_p->DataPathCount >= 1)
        {
            Count = Driver164_DataPath_GetCount();
            if (Count > 0)
            {
                LOG_CRIT("\nTEST_MACSEC: KAT5, remove all %d data paths\n", Count);

                fRetry = true;
                /* Remove all the data paths from the device list */
                for (j = 0; j < Count; j++)
                {
                    /* Remove data path at index j */
                    if (Driver164_DataPath_Remove(j) < 0)
                    {
                        LOG_CRIT("TEST_MACSEC: KAT5 "
                                 "failed to remove data path %d\n",
                                 j);
                        goto test_error;
                    }

                    /* Try to remove the same data again, this should fail */
                    if (fRetry && Driver164_DataPath_Remove(j) >= 0)
                    {
                        LOG_CRIT("TEST_MACSEC: KAT5 failed, "
                                 "removed data path %d twice\n",
                                 j);
                        goto test_error;
                    }
                    else
                        fRetry = false; /* do it for datapath[0] only */
                } /* for, remove data paths */
            }

            LOG_CRIT("TEST_MACSEC: KAT5, add all %d data paths\n", Count);

            Count = TestRec_p->DataPathCount;
            fRetry = true;
            /* Add data paths from the data path list */
            for (j = 0; j < Count; j++)
            {
                Driver164_DataPath_t DataPath;

                ZEROINIT(DataPath);

                DataPath.StartByteOffset1 =
                    TestRec_p->DataPaths[j].StartByteOffset1;
                DataPath.LastByteOffset1 =
                    TestRec_p->DataPaths[j].LastByteOffset1;
                DataPath.Flags1 = TestRec_p->DataPaths[j].Flags1;
                DataPath.StartByteOffset2 =
                    TestRec_p->DataPaths[j].StartByteOffset2;
                DataPath.LastByteOffset2 =
                    TestRec_p->DataPaths[j].LastByteOffset2;
                DataPath.Flags2 = TestRec_p->DataPaths[j].Flags2;

                /* Add data path at index j */
                if (Driver164_DataPath_Add(j, &DataPath) < 0)
                {
                    LOG_CRIT("TEST_MACSEC: KAT5, failed to add device %d\n", j);
                    goto test_error;
                }

                /* Try to add another data path at the same index, */
                /* this should fail */
                if (fRetry && Driver164_DataPath_Add(j, &DataPath) >= 0)
                {
                    LOG_CRIT("TEST_MACSEC: KAT5 failed, "
                             "added data path %d twice\n",
                             j);
                    goto test_error;
                }
            } /* for, add devices */
        } /* devices remove / add done */

        test_macsec_kat1(TestPass, &TestRec_p->Generic, 1);
        TestRec_p++;
        continue;

test_error:
        LOG_CRIT("\nTEST_MACSEC: <<  %s FAILED  >>\n",
                 TestRec_p->Generic.szTestCaseName);

test_case_next:
        TestRec_p++;
    } /* for, test records */

    return;
}


/* end of file test_case_kat5.c */
