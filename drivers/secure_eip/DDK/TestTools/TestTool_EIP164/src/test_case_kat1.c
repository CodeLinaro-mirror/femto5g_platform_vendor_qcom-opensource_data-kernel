/* test_case_kat1.c
 *
 * Test Tool for CfyE and SecY API's
 * KAT 1 test implementation
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

/* Test Case KAT 1 record format */
#include "test_record_kat1.h"

/* General test support internal interface */
#include "test_support.h"

/* Warmboot support functionality. */
#include "test_warmboot.h"

/* General test case internal interface */
#include "test_case.h"

/* CFYE API */
#include "api_cfye.h"

/* SECY API */
#include "api_secy.h"

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
 * test_macsec_kat1
 */
bool
test_macsec_kat1(
        unsigned int TestPass,
        const Test_Case_Record_t * TestRec_p,
        const unsigned int TestRecordCount)
{
    unsigned int i;
    unsigned int MaxChannels;
    bool fAllPassed = true;

    if ((TestRec_p == NULL) || (TestRecordCount == 0))
    {
        LOG_CRIT("TEST_MACSEC: Warning, no KAT1 test record(s) provided\n");
        return false;
    }

    for (i = 0; i < TestRecordCount; i++)
    {
        bool fFailed = false;
        Test_Case_ConfParams_t * TestConf_p = TestRec_p->ConfParams_p;
        Test_Transform_t * TransformAdmin_p = 0;
        Test_Packet_t * PktAdmin_p = 0;
#ifdef TEST_MACSEC_USE_CFYE
        Test_CfyEvPort_t * vPortAdmin_p = 0;
        Test_CfyERules_t * RuleAdmin_p = 0;
#endif /* TEST_MACSEC_USE_CFYE */

#ifdef TEST_MACSEC_USE_CFYE
        if (((TestPass == 0) && (TestRec_p->CfyE_Data_p != NULL)) ||
            ((TestPass != 0) && (TestRec_p->CfyE_Data_p == NULL)))
        {
            goto test_case_next;
        }
#else
        IDENTIFIER_NOT_USED(TestPass);
#endif /* TEST_MACSEC_USE_CFYE */

        LOG_CRIT("\nTEST_MACSEC: >>  %s << \n\n", TestRec_p->szTestCaseName);

        if (TestConf_p == NULL)
        {
            LOG_CRIT("TEST_MACSEC: Failed, no configuration parameters\n");
            goto test_case_next;
        }

        /* Initialize the device */
        /* Note that the device statistics are initialized (reset) as well */
        if (!test_macsec_device_init(TestRec_p, &MaxChannels, NULL, NULL, NULL, NULL))
        {
            fFailed = true;
            LOG_CRIT("TEST_MACSEC: Failed, test_macsec_device_init()\n");
            goto test_case_done;
        }
#ifdef TEST_IPSEC_ENABLE
        if (TestRec_p->SpecialOperation  == TEST_MACSEC_OP_IPSEC)
        {
            CfyE_Status_t CfyE_Rc;
            CfyE_Device_Limits_t Device_Limits;

            CfyE_Rc = CfyE_Device_Limits_Get(TestConf_p->DeviceId,
                                             &Device_Limits);
            if (CfyE_Rc != CFYE_STATUS_OK)
            {
                fFailed = true;
                LOG_CRIT("TEST_MACSEC: Failed, CfyE_Device_Limits()\n");
                goto test_case_done;
            }
            if (!Device_Limits.fIPsec)
            {
                LOG_CRIT("TEST_MACSEC: IPsec not supported on this HW, skipping\n");
                /* Un-initialization the device */
                test_macsec_device_uninit(TestRec_p);
                goto test_case_next;
            }
        }
#endif
#ifdef TEST_MACSEC_VXLAN_ENABLE
        if (TestRec_p->SpecialOperation  == TEST_MACSEC_OP_VXLAN)
        {
            CfyE_Status_t CfyE_Rc;
            CfyE_Device_Limits_t Device_Limits;

            CfyE_Rc = CfyE_Device_Limits_Get(TestConf_p->DeviceId,
                                             &Device_Limits);
            if (CfyE_Rc != CFYE_STATUS_OK)
            {
                fFailed = true;
                LOG_CRIT("TEST_MACSEC: Failed, CfyE_Device_Limits()\n");
                goto test_case_done;
            }
            if (!Device_Limits.fVxLAN)
            {
                LOG_CRIT("TEST_MACSEC: VxLAN not supported on this HW, skipping\n");
                /* Un-initialization the device */
                test_macsec_device_uninit(TestRec_p);
                goto test_case_next;
            }
        }
#endif

#ifdef TEST_MACSEC_SECY_CRYPT_AUTH_ENABLE
        /* Set Crypt-authenticate bypass length, if applicable */
        if (TestConf_p->CryptAuthBypassLen)
        {
            unsigned int CryptAuthBypassLen;
            if (SECY_STATUS_OK !=
                SecY_CryptAuth_BypassLen_Update(TestConf_p->DeviceId,
                                                TestConf_p->CryptAuthBypassLen))
            {
                fFailed = true;
                LOG_CRIT("TEST_MACSEC: Failed, "
                         "SecY_CryptAuth_BypassLen_Update()\n");
                goto test_case_done;
            }
            if (SECY_STATUS_OK !=
                SecY_CryptAuth_BypassLen_Get(TestConf_p->DeviceId,
                                                &CryptAuthBypassLen))
            {
                 fFailed = true;
                LOG_CRIT("TEST_MACSEC: Failed, "
                         "SecY_CryptAuth_BypassLen_Get()\n");
                goto test_case_done;
            }
            if (TestConf_p->CryptAuthBypassLen != CryptAuthBypassLen)
            {
                fFailed = true;
                LOG_CRIT("TEST_MACSEC: Failed, "
                         "Read CryptAuthBypassLen not the same.\n");
                goto test_case_done;
            }
        }
#endif /* TEST_MACSEC_SECY_CRYPT_AUTH_ENABLE */

        /* Install transform records if requested */
        if ((TestRec_p->TransformCount > 0) &&
            (TestRec_p->TransformData_p != NULL))
        {
            if (!test_macsec_transform_install(TestConf_p,
                                               TestRec_p,
                                               0,
                                               TestRec_p->TransformCount,
                                               &TransformAdmin_p))
            {
                fFailed = true;
                LOG_CRIT("TEST_MACSEC: Failed, "
                         "test_macsec_transform_install()\n");
                goto test_case_done;
            }
        }

        if (TestConf_p->fLowLatencyBypass)
        {
            unsigned int k;
            SecY_Status_t SecY_Rc;
            /* If the CfyE device is configured for low-latency bypas, */
            /* so must the SecY device. */
            for (k=0; k < MaxChannels; k++)
            {
                SecY_Rc = SecY_Channel_Bypass_Set(TestConf_p->DeviceId,
                                        k,
                                        true);
                if (SecY_Rc != SECY_STATUS_OK)
                {
                    LOG_CRIT("TEST_MACSEC: Failed, "
                             "SecY_Channel_Bypass_Set()\n");
                    goto test_case_done;
                }
            }

        }

#ifdef TEST_MACSEC_USE_CFYE
        if (TestRec_p->CfyE_Data_p != NULL)
        {
            /* Install and enable the vPort(s) and rule(s) */
            if (!test_macsec_CfyE_install(TestConf_p, TestRec_p,
                                          &vPortAdmin_p, &RuleAdmin_p,
                                          TestConf_p->fVerbose, true, 0))
            {
                fFailed = true;
                LOG_CRIT("TEST_MACSEC: Failed, test_macsec_CfyE_install()\n");
                goto test_case_done;
            }
        }
#endif /* TEST_MACSEC_USE_CFYE */

        /* Update the channel rules if requested */
        if (!test_macsec_channel_rules_update(TestConf_p, TestRec_p))
        {
            fFailed = true;
            LOG_CRIT("TEST_MACSEC: Failed, test_macsec_channel_rules_update()\n");
            goto test_case_done;
        }

        /* Update the secure channel rules if requested */
        if (!test_macsec_secure_channel_rules_update(TestConf_p, TestRec_p))
        {
            fFailed = true;
            LOG_CRIT("TEST_MACSEC: Failed, test_macsec_secure_channel_rules_update()\n");
            goto test_case_done;
        }

#ifdef TEST_MACSEC_USE_CFYE
        if (!test_macsec_CfyE_update(TestConf_p, TestRec_p,
                                     vPortAdmin_p, RuleAdmin_p))
        {
            fFailed = true;
            LOG_CRIT("TEST_MACSEC: Failed, test_macsec_CfyE_Rules_update()\n");
            goto test_case_done;
        }
#endif /* TEST_MACSEC_USE_CFYE */

        /* Allocate packet buffers */
        if (!test_macsec_pkt_alloc(TestRec_p, &PktAdmin_p))
        {
            fFailed = true;
            LOG_CRIT("TEST_MACSEC: Failed, test_macsec_pkt_alloc()\n");
            goto test_case_done;
        }

        /* Sanity check for the provided packet test vectors */
        if (!test_macsec_pkt_sanity_check(TestConf_p, TestRec_p))
        {
            fFailed = true;
            LOG_CRIT("TEST_MACSEC: Failed, test_macsec_pkt_sanity_check()\n");
            goto test_case_done;
        }

#ifdef TEST_MACSEC_USE_WARMBOOT
        test_macsec_warmboot_shutdown();
        test_macsec_warmboot_restore();

        if (TransformAdmin_p != NULL)
        {
            /* Restore the SA Handles from the saved SA Index values. */
            unsigned int i;
            for (i=0; i < TestRec_p->TransformCount; i++)
            {
                SecY_SAHandle_Get(TestConf_p->DeviceId,
                                  TransformAdmin_p[i].SAIndex,
                                  &TransformAdmin_p[i].TransformHandle);
            }
        }

#ifdef TEST_MACSEC_USE_CFYE
        if (TestRec_p->CfyE_Data_p != NULL)
        {
            unsigned int i;
            for (i=0; i<TestRec_p->CfyE_Data_p->CfyE_vPortCount; i++)
            {
                if (vPortAdmin_p != NULL &&
                    !CfyE_vPortHandle_IsSame(vPortAdmin_p[i].vPortHandle,
                                            CfyE_vPortHandle_NULL))
                {
                    CfyE_vPortHandle_Get(TestConf_p->DeviceId,
                                         vPortAdmin_p[i].vPortIndex,
                                         &vPortAdmin_p[i].vPortHandle);
                }
            }
            for (i=0; i<TestRec_p->CfyE_Data_p->CfyE_RuleCount; i++)
            {
                if (RuleAdmin_p != NULL &&
                    !CfyE_RuleHandle_IsSame(RuleAdmin_p[i].RuleHandle,
                                            CfyE_RuleHandle_NULL))
                {
                    CfyE_RuleHandle_Get(TestConf_p->DeviceId,
                                        RuleAdmin_p[i].RuleIndex,
                                        &RuleAdmin_p[i].RuleHandle);
                }
            }
        }
#endif
#endif

#ifdef TEST_MACSEC_USE_READ_API
        if (!test_macsec_read_entries(TestConf_p->DeviceId,
                                      TestRec_p->CfyE_Data_p != NULL))
        {
            fFailed = true;
            goto test_case_done;
        }
        if (!test_macsec_show_diagnostics(TestConf_p->DeviceId,
                                          TestRec_p->TransformCount,
                                          TestRec_p->CfyE_Data_p != NULL))
        {
            fFailed = true;
            goto test_case_done;
        }
#endif /* TEST_MACSEC_USE_READ_API */

        /* Test packets */
        if (!test_macsec_pkt_test(TestConf_p, TestRec_p,
                                  0, TestRec_p->PacketCount, PktAdmin_p, MaxChannels))
        {
            fFailed = true;
            LOG_CRIT("TEST_MACSEC: Failed, test_macsec_pkt_test()\n");
            goto test_case_done;
        }

        if (!test_macsec_pkt_free(TestRec_p, PktAdmin_p))
        {
            fFailed = true;
        }
        else
        {
            PktAdmin_p = NULL;
        }

#ifdef TEST_MACSEC_USE_CFYE
        if (!test_macsec_CfyE_statistics_test(TestConf_p, TestRec_p, RuleAdmin_p))
        {
            fFailed = true;
            LOG_CRIT("TEST_MACSEC: Failed, test_macsec_CfyE_statistics_test()\n");
            goto test_case_done;
        }
#endif /* TEST_MACSEC_USE_CFYE */

        /* Perform Transform Statistics Test if configured */
        if (!test_macsec_transform_statistics_test(TestConf_p, TestRec_p,
                                                   TransformAdmin_p))
        {
            fFailed = true;
            LOG_CRIT("TEST_MACSEC: Failed, "
                     "test_macsec_transform_statistics_test()\n");
            goto test_case_done;
        }

        /* Perform vPort Statistics Test if configured */
        if (!test_macsec_SecY_vPort_statistics(TestConf_p, TestRec_p, 0, NULL))
        {
            fFailed = true;
            LOG_CRIT("TEST_MACSEC: Failed, "
                     "test_macsec_SecY_vPort_statistics()\n");
            goto test_case_done;
        }

test_case_done:
        /* Free packet buffers */
        if (!test_macsec_pkt_free(TestRec_p, PktAdmin_p))
        {
            fFailed = true;
        }

#ifdef TEST_MACSEC_USE_CFYE
        /* Remove the vPort(s) and rules */
        if (!test_macsec_CfyE_uninstall(TestConf_p, TestRec_p,
                                        vPortAdmin_p, RuleAdmin_p,
                                        TestConf_p->fVerbose))
        {
            fFailed = true;
        }
#endif /* TEST_MACSEC_USE_CFYE */

        /* Remove installed transform records if requested */
        if (!test_macsec_transform_uninstall(TestConf_p,
                                             TestRec_p->TransformCount,
                                             TransformAdmin_p))
        {
            fFailed = true;
        }

        /* Un-initialization the device */
        test_macsec_device_uninit(TestRec_p);
        if (TestConf_p->fVerbose)
        {
            LOG_CRIT("TEST_MACSEC: Device un-initialization done\n");
        }

        /* Report the test case result */
        LOG_CRIT("\nTEST_MACSEC: <<  %s %s  >>\n",
                 TestRec_p->szTestCaseName,
                 fFailed ? "FAILED" : "PASSED");

        test_macsec_schedule();

test_case_next:
        if (fFailed)
            fAllPassed = false;

        TestRec_p++;                    /* Next test case record */
    }

    return fAllPassed;
}


/* end of file test_case_kat1.c */
