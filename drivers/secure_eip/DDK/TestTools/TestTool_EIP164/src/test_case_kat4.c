/* test_case_kat4.c
 *
 * Test Tool for CfyE and SecY API's
 * KAT 4 test implementation
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

/* Test Case KAT 4 record format */
#include "test_record_kat4.h"

/* General test support internal interface */
#include "test_support.h"

/* General test case internal interface */
#include "test_case.h"

/* CFYE API */
#include "api_cfye.h"

/* SECY API */
#include "api_secy.h"

/* Driver Framework Basic Definitions API */
#include "basic_defs.h"

/* Driver Framework C-Library Abtraction API */
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
 * test_macsec_multiple_channel_test
 */
static bool
test_macsec_multiple_channel_test(
    const Test_Case_ConfParams_t * const TestConf_p,
    const Test_Case_Record_t * TestRec_p,
    Test_Transform_t * Tr_Admin_p,
#ifdef TEST_MACSEC_USE_CFYE
    Test_CfyEvPort_t * vPortAdmin_p,
    Test_CfyERules_t * RuleAdmin_p,
#endif /* TEST_MACSEC_USE_CFYE */
    Test_Packet_t * PktAdmin_p)
{
    SecY_Status_t SecY_Rc;
    SecY_ChannelConf_t ChannelConf;
    SecY_Channel_t * ChannelParams_p;
    unsigned int UsedChCount;
    unsigned int i;
    bool LowLatencyBypass;

#ifdef TEST_MACSEC_USE_CFYE
    CfyE_Status_t CfyE_Rc;
    IDENTIFIER_NOT_USED(vPortAdmin_p);
#endif /* TEST_MACSEC_USE_CFYE */

    ZEROINIT(ChannelConf);

    SecY_Rc = SecY_Device_Limits(TestConf_p->DeviceId,
                                 &UsedChCount, 0, 0, 0);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        LOG_CRIT("TEST_MACSEC: Failed, SecY_Device_Limits()=%d\n",
                     SecY_Rc);
        return false;
    }

    ChannelParams_p = test_macsec_malloc(UsedChCount * sizeof(SecY_Channel_t));
    if (ChannelParams_p == NULL)
    {
        LOG_CRIT("test_macsec_device_init: failed to alllocate channel parameters\n");
        return false;
    }

    ChannelConf.Params.ChannelCount = UsedChCount;
    ChannelConf.Params.Channel_p    = ChannelParams_p;
    memset(ChannelParams_p, 0, UsedChCount * sizeof(SecY_Channel_t));
    for (i = 0; i < UsedChCount; i++)
    {
        SecY_Rc = SecY_Channel_Config_Get(TestConf_p->DeviceId,
                                          i,
                                          &ChannelParams_p[i]);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("TEST_MACSEC: Failed, SecY_Channel_Config_Get()=%d\n",
                     SecY_Rc);
            test_macsec_free(ChannelParams_p);
            return false;
        }
        if (ChannelParams_p[i].fLowLatencyBypass != 0)
        {
            LOG_CRIT("TEST_MACSEC:"
                     "Failed, SecY_Channel_Config_Get() LowLatencyBypass set"
                     "for channel %d\n",i);
            test_macsec_free(ChannelParams_p);
            return false;
        }
        Log_FormattedMessage("TEST_MACSEC: Channel parameters of channel %d\n"
                             "\t bypass=%d SecTAG Etype=0x%04x egress Etype=0x%04x\n",
                             ChannelParams_p[i].ChannelId,
                             ChannelParams_p[i].fLowLatencyBypass,
                             ChannelParams_p[i].RuleSecTAG.EtherType,
                             ChannelParams_p[i].EtherType);
    }

    SecY_Rc = SecY_Channel_Config_Set(TestConf_p->DeviceId, &ChannelConf);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        LOG_CRIT("TEST_MACSEC: Failed, SecY_Channel_Config_Set()=%d\n",
                 SecY_Rc);
        test_macsec_free(ChannelParams_p);
        return false;
    }

    test_macsec_free(ChannelParams_p);

#ifdef TEST_MACSEC_USE_READ_API
    if (!test_macsec_show_diagnostics(TestConf_p->DeviceId, 0,  TestRec_p->CfyE_Data_p != NULL ))
    {
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_show_diagnostics)\n");
        return false;
    }
#endif

    /* Change channel 0 to low latency bypass */
    SecY_Rc = SecY_Channel_Bypass_Set(TestConf_p->DeviceId, 0, true);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        LOG_CRIT("TEST_MACSEC: Failed, SecY_Channel_Bypass_Set()=%d\n",
                 SecY_Rc);
        return false;
    }
#ifdef TEST_MACSEC_USE_CFYE
    /* Same operatuib when CfyE is configured. */
    if (TestRec_p->CfyE_Data_p != NULL)
    {
        /* Change channel 0 to low latency bypass */
        CfyE_Rc = CfyE_Channel_Bypass_Set(TestConf_p->DeviceId, 0, true);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("TEST_MACSEC: Failed, CfyE_Channel_Bypass_Set()=%d\n",
                     CfyE_Rc);
            return false;
        }
    }
#endif

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Channel 0 set to low latency bypass\n");
    }
#ifdef TEST_MACSEC_USE_READ_API
    if (!test_macsec_show_diagnostics(TestConf_p->DeviceId, 1, TestRec_p->CfyE_Data_p != NULL ))
    {
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_show_diagnostics)\n");
        return false;
    }
#endif

    /* Check packet processing of channel 0 (bypass) */
    if (!test_macsec_pkt_test(TestConf_p, TestRec_p, 0, 1, PktAdmin_p, UsedChCount))
    {
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_pkt_test(2)\n");
        return false;
    }

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Channel 0 remove low latency bypass\n");
    }

    /* Get current (new) channel 0 low latency bypass setting */
    SecY_Rc = SecY_Channel_Bypass_Get(TestConf_p->DeviceId,
                                      0,
                                      &LowLatencyBypass);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        LOG_CRIT("TEST_MACSEC: Failed, SecY_Channel_Bypass_Get()=%d\n",
                 SecY_Rc);
        return false;
    }
    if (!LowLatencyBypass)
    {
        LOG_CRIT("TEST_MACSEC: Failed, expected low latency bypass mode\n");
        return false;
    }
    /* Change channel 0 to non low latency bypass */
    SecY_Rc = SecY_Channel_Bypass_Set(TestConf_p->DeviceId, 0, false);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        LOG_CRIT("TEST_MACSEC: Failed, SecY_Channel_Bypass_Set()=%d\n",
                 SecY_Rc);
        return false;
    }
    /* Get current (new) channel 0 low latency bypass setting */
    SecY_Rc = SecY_Channel_Bypass_Get(TestConf_p->DeviceId,
                                      0,
                                      &LowLatencyBypass);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        LOG_CRIT("TEST_MACSEC: Failed, SecY_Channel_Bypass_Get()=%d\n",
                 SecY_Rc);
        return false;
    }
    if (LowLatencyBypass)
    {
        LOG_CRIT("TEST_MACSEC: Failed, expected low latency bypass mode off\n");
        return false;
    }

#ifdef TEST_MACSEC_USE_CFYE
    /* Same operation when CfyE is configured. */
    if (TestRec_p->CfyE_Data_p != NULL)
    {

        /* Get current channel 0 low latency bypass setting */
        CfyE_Rc = CfyE_Channel_Bypass_Get(TestConf_p->DeviceId,
                                          0,
                                          &LowLatencyBypass);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("TEST_MACSEC: Failed, CfyE_Channel_Bypass_Get()=%d\n",
                     CfyE_Rc);
            return false;
        }
        if (!LowLatencyBypass)
        {
            LOG_CRIT("TEST_MACSEC: Failed, expected low latency bypass mode\n");
            return false;
        }

        /* Change channel 0 to non low latency bypass */
        CfyE_Rc = CfyE_Channel_Bypass_Set(TestConf_p->DeviceId, 0, false);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("TEST_MACSEC: Failed, CfyE_Channel_Bypass_Set()=%d\n",
                     CfyE_Rc);
            return false;
        }

        /* Get current (new) channel 0 low latency bypass setting */
        CfyE_Rc = CfyE_Channel_Bypass_Get(TestConf_p->DeviceId,
                                          0,
                                          &LowLatencyBypass);
        if (CfyE_Rc != CFYE_STATUS_OK)
        {
            LOG_CRIT("TEST_MACSEC: Failed, CfyE_Channel_Bypass_Get()=%d\n",
                     CfyE_Rc);
            return false;
        }
        if (LowLatencyBypass)
        {
            LOG_CRIT("TEST_MACSEC: Failed, expected non-bypass mode\n");
            return false;
        }

        if (TestConf_p->fVerbose)
        {
            Log_FormattedMessage("TEST_MACSEC: CfyE Channel 0 set to normal mode\n");
        }
    }
#endif

    /* Check packet processing of four channels */
    if (!test_macsec_pkt_test(TestConf_p, TestRec_p, 1, 4, PktAdmin_p, UsedChCount))
    {
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_pkt_test(1)\n");
        return false;
    }

    /* Remove SA from channel 1 */
    {
        Test_Transform_t * Transform_p = &Tr_Admin_p[3];

        SecY_Rc = SecY_SA_Remove(TestConf_p->DeviceId,
                                 Transform_p->TransformHandle);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Remove()\n");
            return false;
        }

        /* Set transform record handle to null */
        Transform_p->TransformHandle = SecY_SAHandle_NULL;

        if (TestConf_p->fVerbose)
        {
            Log_FormattedMessage("TEST_MACSEC: Transform removed\n");
        }
    }

#ifdef TEST_MACSEC_USE_CFYE
    /* Remove rule and vPort for channel 1 if the CfyE is available */
    if (TestRec_p->CfyE_Data_p != NULL)
    {

        if (RuleAdmin_p != NULL)
        {
            Test_CfyERules_t * Rule_p = &RuleAdmin_p[3];

            /* Disable the rule */
            CfyE_Rc = CfyE_Rule_Disable(TestConf_p->DeviceId,
                                        Rule_p->RuleHandle,
                                        true); /* device sync */
            if (CfyE_Rc != CFYE_STATUS_OK)
            {
                LOG_CRIT("TEST_MACSEC: Failed, CfyE_Rule_Disable(%u)=%d\n",
                         Rule_p->RuleId, CfyE_Rc);
                return false;
            }

            /* Remove the rule from the administration */
            CfyE_Rc = CfyE_Rule_Remove(TestConf_p->DeviceId,
                                       Rule_p->RuleHandle);
            if (CfyE_Rc != CFYE_STATUS_OK)
            {
                LOG_CRIT("TEST_MACSEC: Failed, CfyE_Rule_Remove(%u)=%d\n",
                         Rule_p->RuleId, CfyE_Rc);
                return false;
            }

            if (TestConf_p->fVerbose)
            {
                Log_FormattedMessage("TEST_MACSEC: Rule %u removed\n",
                                     Rule_p->RuleId);
            }

            Rule_p->RuleHandle = CfyE_RuleHandle_NULL;
            Rule_p->RuleId     = 0;
        }

        if (vPortAdmin_p != NULL)
        {
            Test_CfyEvPort_t * vPort_p = &vPortAdmin_p[3];

            /* Remove the vPort from the administration */
            CfyE_Rc = CfyE_vPort_Remove(TestConf_p->DeviceId,
                                        vPort_p->vPortHandle);
            if (CfyE_Rc != CFYE_STATUS_OK)
            {
                LOG_CRIT("TEST_MACSEC: Failed, CfyE_vPort_Remove(%u)=%d\n",
                         vPort_p->vPortId, CfyE_Rc);
                return false;
            }

            if (TestConf_p->fVerbose)
            {
                Log_FormattedMessage("TEST_MACSEC: vPort %u removed\n",
                                     vPort_p->vPortId);
            }

            /* Set vPort handle to null */
            vPort_p->vPortHandle = CfyE_vPortHandle_NULL;
            vPort_p->vPortId     = 0;
        }
    }
#endif /* TEST_MACSEC_USE_CFYE */

    /* Check packet processing of channels 0 & 2 */
    if (!test_macsec_pkt_test(TestConf_p, TestRec_p, 5, 2, PktAdmin_p, UsedChCount))
    {
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_pkt_test(2)\n");
        return false;
    }

    /* Test in-flight counters */
    {
        bool fInflight;
        SecY_Ch_Mask_t  InflightMask;
        unsigned int i;

        if (TestConf_p->fVerbose)
        {
            Log_FormattedMessage("TEST_MACSEC: Reconfiguring channels\n");
        }

        for (i=0; i<UsedChCount; i++)
        {
            /* Get packets in flight information for each channel separately. */
            SecY_Rc = SecY_Channel_PacketsInflight_Get(TestConf_p->DeviceId, i, &fInflight, NULL);
            if (SecY_Rc != SECY_STATUS_OK)
            {
                LOG_CRIT("TEST_MACSEC: Failed, SecY_Channel_PacketsInflight_Get()=%d\n",
                         SecY_Rc);
                return false;
            }
            if (fInflight)
            {
                LOG_CRIT("TEST_MACSEC: Failed, there are still packets in flight on channel %u\n",i);
                return false;
            }
        }
        /* Get packets in flight information for all channels combined. */
        SecY_Rc = SecY_Channel_PacketsInflight_Get(TestConf_p->DeviceId, 0, NULL, &InflightMask);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("TEST_MACSEC: Failed, SecY_Channel_PacketsInflight_Get()=%d\n",
                     SecY_Rc);
            return false;
        }
        for (i=0; i< SECY_CHANNEL_WORDS; i++)
        {
            if (InflightMask.ch_bitmask[i] != 0)
            {
                LOG_CRIT("TEST_MACSEC: Failed, there are still packets in flight\n");
                return false;
            }
        }
    }

    /* Check packet processing of channel 0, 2 and 3. */
    if (!test_macsec_pkt_test(TestConf_p, TestRec_p, 7, 3, PktAdmin_p, UsedChCount))
    {
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_pkt_test(3)\n");
        return false;
    }

    /* Get current channel 1 low latency bypass setting */
    SecY_Rc = SecY_Channel_Bypass_Get(TestConf_p->DeviceId,
                                      1,
                                      &LowLatencyBypass);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        LOG_CRIT("TEST_MACSEC: Failed, SecY_Channel_Bypass_Get()=%d\n",
                 SecY_Rc);
        return false;
    }
    if (LowLatencyBypass)
    {
        LOG_CRIT("TEST_MACSEC: Failed, expected MACsec mode\n");
        return false;
    }

    /* Change channel 1 to low latency bypass */
    SecY_Rc = SecY_Channel_Bypass_Set(TestConf_p->DeviceId, 1, true);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        LOG_CRIT("TEST_MACSEC: Failed, SecY_Channel_Bypass_Set()=%d\n",
                 SecY_Rc);
        return false;
    }

    /* Get current (new) channel 1 low latency bypass setting */
    SecY_Rc = SecY_Channel_Bypass_Get(TestConf_p->DeviceId,
                                      1,
                                      &LowLatencyBypass);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        LOG_CRIT("TEST_MACSEC: Failed, SecY_Channel_Bypass_Get()=%d\n",
                 SecY_Rc);
        return false;
    }
    if (!LowLatencyBypass)
    {
        LOG_CRIT("TEST_MACSEC: Failed, expected low latency bypass mode\n");
        return false;
    }

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Channel 1 set to low latency bypass\n");
    }

    /* Check packet processing of channel 1 (in bypass). */
    if (!test_macsec_pkt_test(TestConf_p, TestRec_p, 10, 1, PktAdmin_p, UsedChCount))
    {
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_pkt_test(3)\n");
        return false;
    }

    return true;
}


/*----------------------------------------------------------------------------
 * test_macsec_kat4
 */
void
test_macsec_kat4(
        unsigned int TestPass,
        const Test_Case_Record_t * TestRec_p,
        const unsigned int TestRecordCount)
{
    unsigned int i;

    if ((TestRec_p == NULL) || (TestRecordCount == 0))
    {
        LOG_CRIT("TEST_MACSEC: Warning, no KAT4 test record(s) provided\n");
        return;
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

        if (TestConf_p == NULL)
        {
            LOG_CRIT("TEST_MACSEC: Failed, no configuration parameters (KAT4)\n");
            goto NextTestCase;
        }

#ifdef TEST_MACSEC_USE_CFYE
        if (((TestPass == 0) && (TestRec_p->CfyE_Data_p != NULL)) ||
            ((TestPass != 0) && (TestRec_p->CfyE_Data_p == NULL)))
        {
            goto NextTestCase;
        }
#else
        IDENTIFIER_NOT_USED(TestPass);
#endif /* TEST_MACSEC_USE_CFYE */

        LOG_CRIT("\nTEST_MACSEC: >>  %s  <<\n\n", TestRec_p->szTestCaseName);

        /* Initialize the device */
        /* Note that the device statistics are initialized (reset) as well */
        if (!test_macsec_device_init(TestRec_p, NULL, NULL, NULL, NULL, NULL))
        {
            fFailed = true;
            LOG_CRIT("TEST_MACSEC: Failed, test_macsec_device_init()\n");
            goto test_case_done;
        }

        /* Install transform records if requested */
        if (!test_macsec_transform_install(TestConf_p, TestRec_p,
                                           0, TestRec_p->TransformCount,
                                           &TransformAdmin_p))
        {
            fFailed = true;
            LOG_CRIT("TEST_MACSEC: Failed, "
                     "test_macsec_transform_install()\n");
            goto test_case_done;
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

#ifdef TEST_MACSEC_MODE_EGRESS
        /* Perform egress tests */
        if (!TestConf_p->fIngress)
        {
            if (!test_macsec_multiple_channel_test(TestConf_p,
                                                   TestRec_p,
                                                   TransformAdmin_p,
#ifdef TEST_MACSEC_USE_CFYE
                                                   vPortAdmin_p,
                                                   RuleAdmin_p,
#endif /* TEST_MACSEC_USE_CFYE */
                                                   PktAdmin_p))
            {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, "
                             "test_macsec_channel_reconfigure_test()\n");
                    goto test_case_done;
            }
        }
#endif /* TEST_MACSEC_MODE_EGRESS */

#ifdef TEST_MACSEC_MODE_INGRESS
        /* Perform ingress tests */
        if (TestConf_p->fIngress)
        {
            if (!test_macsec_multiple_channel_test(TestConf_p,
                                                   TestRec_p,
                                                   TransformAdmin_p,
#ifdef TEST_MACSEC_USE_CFYE
                                                   vPortAdmin_p,
                                                   RuleAdmin_p,
#endif /* TEST_MACSEC_USE_CFYE */
                                                   PktAdmin_p))
            {
                fFailed = true;
                LOG_CRIT("TEST_MACSEC: Failed, "
                         "test_macsec_channel_reconfigure_test()\n");
                goto test_case_done;
            }
        }
#endif /* TEST_MACSEC_MODE_INGRESS */

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

        IDENTIFIER_NOT_USED_LOG_OFF(fFailed);

        /* Report the test case result */
        LOG_CRIT("\nTEST_MACSEC: <<  %s %s  >>\n",
                 TestRec_p->szTestCaseName,
                 fFailed ? "FAILED" : "PASSED");

        test_macsec_schedule();

NextTestCase:
        TestRec_p++;                    /* Next test case record */
    }
}


/* end of file test_case_kat4.c */
