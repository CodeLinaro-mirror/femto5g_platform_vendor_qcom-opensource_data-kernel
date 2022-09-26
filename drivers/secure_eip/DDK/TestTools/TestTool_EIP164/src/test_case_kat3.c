/* test_case_kat3.c
 *
 * Test Tool for CfyE and SecY API's
 * KAT 3 test implementation
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

/* Test Case KAT 3 record format */
#include "test_record_kat3.h"

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

/* Driver Framework C-Library Abtraction API */
#include "clib.h"

/* Logging API */
#include "log.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

#define MAX_NUM_OF_SA_TO_BE_TESTED 256

/*----------------------------------------------------------------------------
 * Local variables
 */


/*----------------------------------------------------------------------------
 * test_macsec_kat3
 */
void
test_macsec_kat3(
        unsigned int TestPass,
        const Test_Case_Record_t * TestRec_p,
        const unsigned int TestRecordCount)
{
    unsigned int i;

    if ((TestRec_p == NULL) || (TestRecordCount == 0))
    {
        LOG_CRIT("TEST_MACSEC: Warning, no KAT3 test record(s) provided\n");
        return;
    }

    for (i = 0; i < TestRecordCount; i++)
    {
        unsigned int j;
        unsigned int Size;
        unsigned int vPortIndex;
        bool fFailed = false;
        Test_Case_ConfParams_t * TestConf_p = TestRec_p->ConfParams_p;
        Test_Packet_t * PktAdmin_p = NULL;
        SecY_Status_t SecY_Rc;
        SecY_SAHandle_t * SAHandle_p = NULL;
        unsigned int * SAIndex_p = NULL;
#ifdef TEST_MACSEC_USE_CFYE
        Test_CfyEvPort_t ** vPortAdmin_pp = NULL;
        Test_CfyERules_t ** RuleAdmin_pp = NULL;
#endif /* TEST_MACSEC_USE_CFYE */
        Test_Case_vPortStat_t vPortStatisticsToUse;
        Test_Case_vPortStat_t * vPortStatisticsToUse_p = NULL;
        SecY_SAHandle_t SAHandle_Check;
        unsigned int SAIndexCheck;
        unsigned int MaxChannels = 0;
        unsigned int MaxvPorts = 0;
        unsigned int MaxSAs = 0;
        unsigned int MaxSCs = 0;
        unsigned int MaxRules = 0;
        SecY_SA_t SA_Params;
        Test_Transform_t * TransformAdmin_p = 0;

        if (TestConf_p == NULL)
        {
            LOG_CRIT("TEST_MACSEC: Failed, no configuration parameters (KAT3)\n");
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

        LOG_CRIT("\nTEST_MACSEC: >>  %s <<  \n\n", TestRec_p->szTestCaseName);

        /* Check the input parameters */
        if ((TestRec_p->TransformCount != 1) ||
            (TestRec_p->TransformData_p == NULL) ||
#ifdef TEST_MACSEC_USE_CFYE
            ((TestRec_p->CfyE_Data_p != NULL) &&
             ((TestRec_p->CfyE_Data_p->CfyE_ChannelCount == 0) ||
              (TestRec_p->CfyE_Data_p->CfyE_ChannelData_p == NULL) ||
              (TestRec_p->CfyE_Data_p->CfyE_vPortCount != 1) ||
              (TestRec_p->CfyE_Data_p->CfyE_vPortData_p == NULL) ||
              (TestRec_p->CfyE_Data_p->CfyE_RuleCount != 2) ||
              (TestRec_p->CfyE_Data_p->CfyE_RuleData_p == NULL))) ||
#endif /* TEST_MACSEC_USE_CFYE */
            (TestRec_p->PacketCount != 1) ||
            (TestRec_p->PacketData_p == NULL))
        {
            fFailed = true;
            LOG_CRIT("TEST_MACSEC: Failed, invalid test vector input\n");
            goto test_case_done;
        }

        /* Initialize the device */
        if (!test_macsec_device_init(TestRec_p, &MaxChannels, &MaxvPorts,
                                     &MaxSAs, &MaxSCs, &MaxRules))
        {
            fFailed = true;
            LOG_CRIT("TEST_MACSEC: Failed, test_macsec_device_init()\n");
            goto test_case_done;
        }

#ifdef TEST_MACSEC_USE_CFYE
        if (TestRec_p->CfyE_Data_p != NULL)
        {
            if ((2 * MaxvPorts) > MaxRules)
            {
                MaxvPorts = MaxRules / 2;
            }
        }

        if (TestRec_p->CfyE_Data_p != NULL)
        {
            CfyE_Rule_t Rule;
            CfyE_Status_t CfyE_Rc;
            uint32_t * ptr;

            CfyE_RuleHandle_t RuleHandle_Check;
            CfyE_vPortHandle_t vPortHandle_Check;
            unsigned int vPortIndexCheck, RuleIndexCheck;


            if (TestConf_p->fVerbose)
            {
                LOG_CRIT("TEST_MACSEC: Installing vPorts and Rules...\n");
            }

            /* Allocate vPort and rule administration */
            Size = MaxvPorts * sizeof(Test_CfyEvPort_t *);
            vPortAdmin_pp = (Test_CfyEvPort_t **)test_macsec_malloc(Size);
            if (vPortAdmin_pp == NULL)
            {
                fFailed = true;
                LOG_CRIT("TEST_MACSEC: Failed, vPort administration\n");
                goto test_case_done;
            }
            memset(vPortAdmin_pp, 0, Size);

            Size = 2 * MaxvPorts * sizeof(Test_CfyERules_t *);
            RuleAdmin_pp = (Test_CfyERules_t **)test_macsec_malloc(Size);
            if (RuleAdmin_pp == NULL)
            {
                fFailed = true;
                LOG_CRIT("TEST_MACSEC: Failed, Rule administration\n");
                goto test_case_done;
            }
            memset(RuleAdmin_pp, 0, Size);

            /* Copy rule data for update of MAC DA to make it unique */
            memcpy (&Rule,
                    &TestRec_p->CfyE_Data_p->CfyE_RuleData_p->Rule,
                    sizeof(Rule));
            ptr = (uint32_t *)&Rule.Data[0];

            /* Install and enable the maximal possible vPorts and rules */
            for (j = 0; j < MaxvPorts; j++)
            {
                if (!test_macsec_CfyE_install(TestConf_p, TestRec_p,
                                              (vPortAdmin_pp + j),
                                              (RuleAdmin_pp + j),
                                              false,
                                              j==0,
                                              2*j))
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, test_macsec_CfyE_install(%u)\n",
                             j);
                    goto test_case_done;
                }

                /* Adapt the VLAN ID of the first rule to make it unique */
                /* Access the Rule data as little-endian 32-bit words. */
                /* Word 2 of the match key contains the VLAN ID */
                /* in most signiifcant words. */
                Rule.Policy.vPortHandle = (*(vPortAdmin_pp + j))->vPortHandle;
                ptr[2] = (ptr[2] & 0x00f0ffff) | ((j & 0xff) << 24) | ((j>>8)<<16);
                Rule.Key.ChannelID = j % MaxChannels;

                CfyE_Rc = CfyE_Rule_Update(TestConf_p->DeviceId,
                                           (*(RuleAdmin_pp + j))->RuleHandle,
                                           &Rule);
                if (CfyE_Rc != CFYE_STATUS_OK)
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, CfyE_Rule_Update(%u)=%d\n",
                             j, CfyE_Rc);
                    goto test_case_done;
                }


                /* For Coverage: Check that the index can be */
                /* retrieved from the handle. And that using the */
                /* retrieved index, the original handle can be */
                /* retrieved again. */

                /* vPort Handle check */
                CfyE_Rc = CfyE_vPortIndex_Get(
                        (*(vPortAdmin_pp + j))->vPortHandle,
                        &vPortIndexCheck);
                if (CfyE_Rc != CFYE_STATUS_OK)
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, CfyE_vPortIndex_Get\n");
                    goto test_case_done;
                }

                CfyE_Rc = CfyE_vPortHandle_Get(TestConf_p->DeviceId,
                        vPortIndexCheck,
                        &vPortHandle_Check);
                if (CfyE_Rc != CFYE_STATUS_OK)
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, CfyE_vPortHandle_Get\n");
                    goto test_case_done;
                }

                if (!CfyE_vPortHandle_IsSame(
                        (*(vPortAdmin_pp + j))->vPortHandle,
                        vPortHandle_Check))
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, CfyE_vPortHandle_IsSame\n");
                    goto test_case_done;
                }

                /* Rule Handle check */
                CfyE_Rc = CfyE_RuleIndex_Get(
                        (*(RuleAdmin_pp + j))->RuleHandle,
                        &RuleIndexCheck);
                if (CfyE_Rc != CFYE_STATUS_OK)
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, CfyE_RuleIndex_Get\n");
                    goto test_case_done;
                }

                CfyE_Rc = CfyE_RuleHandle_Get(TestConf_p->DeviceId,
                        RuleIndexCheck,
                        &RuleHandle_Check);
                if (CfyE_Rc != CFYE_STATUS_OK)
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, CfyE_RuleHandle_Get\n");
                    goto test_case_done;
                }

                if (!CfyE_RuleHandle_IsSame(
                        (*(RuleAdmin_pp + j))->RuleHandle,
                        RuleHandle_Check))
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, CfyE_RuleHandle_IsSame\n");
                    goto test_case_done;
                }
            }

            if (TestConf_p->fVerbose)
            {
                LOG_CRIT("TEST_MACSEC: vPorts and Rules installed.\n");
            }
        }
#endif /* TEST_MACSEC_USE_CFYE */

        if (TestConf_p->fVerbose)
        {
            LOG_CRIT("TEST_MACSEC: Installing SAs...\n");
        }

        /* Allocate SA administration */
        Size = MaxSAs * sizeof(SecY_SAHandle_t);
        SAHandle_p = (SecY_SAHandle_t *)test_macsec_malloc(Size);
        if (SAHandle_p == NULL)
        {
            fFailed = true;
            LOG_CRIT("TEST_MACSEC: Failed, SA administration\n");
            goto test_case_done;
        }
        memset(SAHandle_p, 0, Size);

        /* Allocate SA index value array. */
        Size = MaxSAs * sizeof(unsigned int);
        SAIndex_p = (unsigned int *)test_macsec_malloc(Size);
        if (SAHandle_p == NULL)
        {
            fFailed = true;
            LOG_CRIT("TEST_MACSEC: Failed, SA administration\n");
            goto test_case_done;
        }
        memset(SAIndex_p, 0, Size);

        TransformAdmin_p = test_macsec_malloc(sizeof(Test_Transform_t));
        if (TransformAdmin_p == NULL)
        {
            fFailed = true;
            LOG_CRIT("TEST_MACSEC: Failed, Second Transform admin allocation\n");
            goto test_case_done;
        }
        memset(TransformAdmin_p, 0, sizeof(Test_Transform_t));

        /* Copy SA data */
        test_macsec_sa_copy(TestConf_p,
                            &TestRec_p->TransformData_p->SA_Data,
                            TestRec_p->TransformData_p,
                            TransformAdmin_p,
                            &SA_Params);


        /* Install the maximal possible SA's */
        /* (each SA is installed on a corresponding vPort, if the vPort maximum */
        /*  is reached the vPort numbering is reset to zero) */
        for (j = 0; j < MaxSAs; j++)
        {
#ifdef TEST_MACSEC_USE_CFYE
            if (TestRec_p->CfyE_Data_p != NULL)
            {
                CfyE_vPortIndex_Get(
                        (*(vPortAdmin_pp + (j % (MaxvPorts ? MaxvPorts: 1))))
                            ->vPortHandle,
                        &vPortIndex);
            }
            else
            {
                vPortIndex = (j % (MaxvPorts ? MaxvPorts: 1));
            }
#else
            vPortIndex = (j % (MaxvPorts ? MaxvPorts: 1));
#endif
            SecY_Rc = SecY_SA_Add(TestConf_p->DeviceId,
                                  vPortIndex,
                                  &SAHandle_p[j],
                                  &SA_Params);
            if (SecY_Rc != SECY_STATUS_OK)
            {
                fFailed = true;
                LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Add(%u)=%d\n",
                         j, SecY_Rc);
                goto test_case_done;
            }

            /* For Coverage: Check that the index can be */
            /* retrieved from the handle. And that using the */
            /* retrieved index, the original handle can be */
            /* retrieved again. */
            /* Also need the index in case of WarmBoot restore. */
            SecY_Rc = SecY_SAIndex_Get(
                    SAHandle_p[j],
                    &SAIndexCheck,
                    NULL);
            if (SecY_Rc != SECY_STATUS_OK)
            {
                fFailed = true;
                LOG_CRIT("TEST_MACSEC: Failed, SecY_SAIndex_Get\n");
                goto test_case_done;
            }
            SAIndex_p[j] = SAIndexCheck;

            SecY_Rc = SecY_SAHandle_Get(TestConf_p->DeviceId,
                    SAIndexCheck,
                    &SAHandle_Check);
            if (SecY_Rc != SECY_STATUS_OK)
            {
                fFailed = true;
                LOG_CRIT("TEST_MACSEC: Failed, SecY_SAHandle_Get = %i\n",
                        SecY_Rc);
                goto test_case_done;
            }

            if (!SecY_SAHandle_IsSame(&SAHandle_p[j], &SAHandle_Check))
            {
                fFailed = true;
                LOG_CRIT("TEST_MACSEC: Failed, SecY_SAHandle_IsSame\n");
                goto test_case_done;
            }
        }

        if (TestConf_p->fVerbose)
        {
            LOG_CRIT("TEST_MACSEC: SAs installed.\n");
        }

        /* Update the channel rules if requested */
        if (!test_macsec_channel_rules_update(TestConf_p, TestRec_p))
        {
            fFailed = true;
            LOG_CRIT("TEST_MACSEC: Failed, test_macsec_channel_rules_update()\n");
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

        /* Copy the packet data to the allocated packet buffer */
        memcpy(PktAdmin_p->SrcPkt_p,
               TestRec_p->PacketData_p->SrcPkt_p,
               TestRec_p->PacketData_p->SrcPkt_ByteCount);

        /* Prepare the vPort related statistics for test validation */
        if ((TestRec_p->vPortStatistisCount > 0) &&
            (TestRec_p->vPortStatistis_p != NULL))
        {
            vPortStatisticsToUse_p = &vPortStatisticsToUse;
            memcpy(vPortStatisticsToUse_p,
                   TestRec_p->vPortStatistis_p,
                   sizeof(vPortStatisticsToUse));
        }

        if (TestConf_p->fVerbose)
        {
            LOG_CRIT("TEST_MACSEC: Sending/receiving packets and reading "
                     "statistics...\n");
        }

#ifdef TEST_MACSEC_USE_WARMBOOT
        test_macsec_warmboot_shutdown();
        test_macsec_warmboot_restore();

        /* Restore the SA Handle array from the saved indexes. */
        for (j = 0; j < MaxSAs; j++)
        {
            SecY_SAHandle_Get(TestConf_p->DeviceId,
                              SAIndex_p[j],
                              &SAHandle_p[j]);
        }
#ifdef TEST_MACSEC_USE_CFYE
        if (TestRec_p->CfyE_Data_p != NULL)
        {
            for (j = 0; j < MaxvPorts; j++)
            {

                /* Restore the vPort handles from saved indexes. */
                if (vPortAdmin_pp != NULL &&
                    !CfyE_vPortHandle_IsSame(vPortAdmin_pp[j]->vPortHandle,
                                            CfyE_vPortHandle_NULL))
                {
                    CfyE_vPortHandle_Get(TestConf_p->DeviceId,
                                         vPortAdmin_pp[j]->vPortIndex,
                                         &vPortAdmin_pp[j]->vPortHandle);
                }
            }
            for (j = 0; j < MaxvPorts; j++)
            {
                unsigned int k;
                for (k=0; k<2; k++)
                {
                    if (RuleAdmin_pp != NULL &&
                        !CfyE_RuleHandle_IsSame(RuleAdmin_pp[j][k].RuleHandle,
                                                CfyE_RuleHandle_NULL))
                    {
                        /* Restore the rule handles from saved indexes. */
                        CfyE_RuleHandle_Get(TestConf_p->DeviceId,
                                        RuleAdmin_pp[j][k].RuleIndex,
                                            &RuleAdmin_pp[j][k].RuleHandle);
                    }
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
#endif /* TEST_MACSEC_USE_READ_API */

        /* Test packets */
        for (j = 0; j < MaxvPorts; j++)
        {
            unsigned int vPort = 0;
            unsigned int ByteCount = 0;
            unsigned int ChanId = (j % MaxChannels);

#ifdef TEST_MACSEC_USE_CFYE
            if (TestRec_p->CfyE_Data_p == NULL)
            {
                /* Use provided vPort, otherwise vPort = 0 */
                vPort = j;
            }
            else
            {
                /* Modify the VLAN ID to match the rule */
                uint8_t *ptr = (uint8_t *)PktAdmin_p->SrcPkt_p;
                ptr[14] = (ptr[14]&0xf0) | (uint8_t)(j >> 8);
                ptr[15] = (uint8_t)(j);
            }
#else
            vPort = j;
#endif /* TEST_MACSEC_USE_CFYE */

            if (!test_macsec_put_one(TestConf_p,
                                     PktAdmin_p->SrcPkt_p,
                                     PktAdmin_p->SrcPkt_ByteCount,
                                     ChanId,
                                     vPort,
                                     TestRec_p->PacketData_p->SecTAGOffset,
                                     TestRec_p->PacketData_p->fControl))
            {
                fFailed = true;
                LOG_CRIT("TEST_MACSEC: Failed, test_macsec_put_one(%u)\n", j);
                goto test_case_done;
            }
            /* Wait until channel has packets in flight. */
            {
                SecY_Ch_Mask_t Mask;
                bool fInFlight = false;
                unsigned int LoopCounter = TestConf_p->RetryCount;
                while (--LoopCounter)
                {
                    SecY_Rc = SecY_Channel_PacketsInflight_Get(
                        TestConf_p->DeviceId,
                        ChanId,
                        &fInFlight,
                        &Mask);
                    if (SecY_Rc != SECY_STATUS_OK)
                    {
                        fFailed = true;
                        LOG_CRIT("TEST_MACSEC: Failed, SecY_Channel_PacketsInflight_Get rc=%d\n", SecY_Rc);
                    }
                    if (fInFlight) break;
                    /* Do not delay in this loop, may miss the inflight condition*/
                }
                if (!fInFlight)
                {
                    fFailed=true;
                    LOG_CRIT("TEST_MACSEC: SecY_Channel_PacketsInflight_Get did not report packet in flight on channel %d.\n",ChanId);
                }
                else
                {
                    unsigned int k;
                    unsigned int ExpectedMask;
                    LOG_CRIT("TEST_MACSEC: SecY_Channel_PacketsInflight_Get\n"
                             " reported packet in flight on channel %d.\n",ChanId);
                    for (k=0; k<SECY_CHANNEL_WORDS; k++)
                    {
                        LOG_CRIT(" Mask[%d]=0x%08x\n",k,Mask.ch_bitmask[k]);
                        if (ChanId >= 32*k && ChanId < 32*k+32)
                            ExpectedMask = (1<<(ChanId % 32));
                        else
                            ExpectedMask = 0;
                        if (Mask.ch_bitmask[k] != ExpectedMask)
                        {
                            LOG_CRIT("TEST_MACSEC: SecY_Channel_PacketsInflight_Get\n"
                                     "Mask mismatch Expected = 0x%08x\n",ExpectedMask);
                            fFailed=true;
                        }
                    }
                }
            }

            if (!test_macsec_get_one(TestConf_p,
                                     PktAdmin_p->DstPkt_p,
                                     &ByteCount,
                                     ChanId))
            {
                fFailed = true;
                LOG_CRIT("TEST_MACSEC: Failed, test_macsec_get_one(%u)\n", j);
                goto test_case_done;
            }

            {
                Test_Transform_t TestTransform;
                TestTransform.TransformHandle = SAHandle_p[j + MaxvPorts];
                /* Perform Transform Statistics Test if configured */
                if (!test_macsec_single_transform_statistics_test(
                        TestConf_p,
                        TestRec_p->TransformData_p,
                        &TestTransform))
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, "
                             "test_macsec_transform_statistics_test()\n");
                    goto test_case_done;
                }
            }

            /* Perform vPort statistics test if configured */
            if (vPortStatisticsToUse_p != NULL)
            {
                vPortStatisticsToUse_p->vPort = j;
            }
            if (!test_macsec_SecY_vPort_statistics(TestConf_p, TestRec_p,
                                                   j, vPortStatisticsToUse_p))
            {
                fFailed = true;
                LOG_CRIT("TEST_MACSEC: Failed, "
                         "test_macsec_SecY_vPort_statistics()\n");
                goto test_case_done;
            }
        }

#ifdef TEST_MACSEC_USE_CFYE
        if (TestRec_p->CfyE_Data_p != NULL)
        {
            if (!test_macsec_CfyE_statsummary_test(TestConf_p,
                                                   0,
                                                   (2 * MaxvPorts),
                                                   0x55555555))
            {
                fFailed = true;
                LOG_CRIT("TEST_MACSEC: Failed, "
                         "test_macsec_CfyE_statsummary_test()\n");
                goto test_case_done;
            }
        }
#endif /* TEST_MACSEC_USE_CFYE */

test_case_done:
        /* Free packet buffers */
        if (!test_macsec_pkt_free(TestRec_p, PktAdmin_p))
        {
            fFailed = true;
        }

#ifdef TEST_MACSEC_USE_CFYE
        /* Remove all vPorts and rules */
        if (vPortAdmin_pp != NULL)
        {
            if (RuleAdmin_pp != NULL)
            {
                for (j = 0; j < MaxvPorts; j++)
                {
                    if (*(vPortAdmin_pp + j) != NULL)
                    {
                        if (!test_macsec_CfyE_uninstall(TestConf_p, TestRec_p,
                                                        *(vPortAdmin_pp + j),
                                                        *(RuleAdmin_pp + j),
                                                        false))
                        {
                            fFailed = true;
                            LOG_CRIT("TEST_MACSEC: Failed, "
                                     "test_macsec_CfyE_uninstall(%u)\n",
                                     j);
                        }
                    }
                }

                /* Release rule administration */
                test_macsec_free(RuleAdmin_pp);
            }

            /* Release vPort administration */
            test_macsec_free(vPortAdmin_pp);
        }
#endif /* TEST_MACSEC_USE_CFYE */

        if (SAHandle_p != NULL)
        {
            /* Remove all installed SAs */
            for (j = 0; j < MaxSAs; j++)
            {
                if (!SecY_SAHandle_IsSame(&SAHandle_p[j], &SecY_SAHandle_NULL))
                {
                    SecY_Rc = SecY_SA_Remove(TestConf_p->DeviceId,
                                             SAHandle_p[j]);
                    if (SecY_Rc != SECY_STATUS_OK)
                    {
                        LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Remove(%u)=%d\n",
                                 j, SecY_Rc);
                        fFailed = true;
                    }
                }
            }

            /* Release SA administration */
            test_macsec_free(SAHandle_p);
        }
        if (SAIndex_p != NULL)
        {
            test_macsec_free(SAIndex_p);
        }

        if (TransformAdmin_p != NULL)
        {
            if (TransformAdmin_p->TransformRec_p != NULL)
                test_macsec_free(TransformAdmin_p->TransformRec_p);
            test_macsec_free(TransformAdmin_p);
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


/* end of file test_case_kat3.c */
