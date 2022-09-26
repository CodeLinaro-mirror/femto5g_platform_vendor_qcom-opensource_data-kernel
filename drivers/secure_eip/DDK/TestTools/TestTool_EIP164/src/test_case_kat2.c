/* test_case_kat2.c
 *
 * Test Tool for CfyE and SecY API's
 * KAT 2 test implementation
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
#include "test_record_kat2.h"

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

#ifdef TEST_MACSEC_USE_READ_API
/* Extended SecY API */
#include "api_secy_ext.h"
#endif

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


#ifdef TEST_MACSEC_MODE_EGRESS


/*----------------------------------------------------------------------------
 * test_macsec_egress_rekey_test
 *
 * 1. Add one SA and test a packet, it should pass.
 * 2. Add a second SA on the same vPort, it should now be active.
 * 3. Remove the first SA.
 * 4. Re-test the packet, the output data should be protected by the second SA.
 */
static bool
test_macsec_egress_rekey_addsa_test(
    const Test_Case_ConfParams_t * const TestConf_p,
    const Test_Case_Record_t * TestRec_p)
{
    bool fSuccess = true;
    SecY_SA_t *SA_Input_p;
    SecY_SA_t SA_Params;
    SecY_Status_t SecY_Rc;

    Test_Transform_t * FirstTransformAdmin_p = 0;
    Test_Transform_t * SecondTransformAdmin_p = 0;
    Test_Packet_t * PktAdmin_p = 0, *OrigPktAdmin_p = 0;

    Test_Case_Transform_t * TC_Transform_p = TestRec_p->TransformData_p;
    Test_Case_Packet_t * TC_Pkt_p = TestRec_p->PacketData_p;

    if (TestRec_p->TransformCount < 2)
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, Not enough transforms\n");
        goto test_done;
    }

    /* Install the first SA */
    if (!test_macsec_transform_install(TestConf_p, TestRec_p,
                                       0, 1,
                                       &FirstTransformAdmin_p))
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_transform_install()\n");
        goto test_done;
    }


    /* Allocate buffers for both first and the second packets */
    if (!test_macsec_pkt_alloc(TestRec_p, &PktAdmin_p))
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_pkt_alloc()\n");
        goto test_done;
    }
    OrigPktAdmin_p = PktAdmin_p;

    /* Test the packet */
    memcpy(PktAdmin_p->SrcPkt_p, TC_Pkt_p->SrcPkt_p, PktAdmin_p->SrcPkt_ByteCount);

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Process packet of size %d\n",
                             PktAdmin_p->SrcPkt_ByteCount);
        Log_HexDump("TEST_MACSEC: Submitted packet data",
                    0,
                    PktAdmin_p->SrcPkt_p,
                    PktAdmin_p->SrcPkt_ByteCount);
    }

    /* Submit the packet */
    {
        unsigned vPort = 0;

        if (TestRec_p->CfyE_Data_p == NULL)
        {
            /* Use provided vPort, otherwise vPort = 0 */
            vPort = TC_Pkt_p->vPort;
        }

        if (!test_macsec_put_one(TestConf_p,
                                 PktAdmin_p->SrcPkt_p,
                                 PktAdmin_p->SrcPkt_ByteCount,
                                 TC_Pkt_p->ChannelID,
                                 vPort,
                                 TC_Pkt_p->SecTAGOffset,
                                 TC_Pkt_p->fControl))
        {
            fSuccess = false;
            LOG_CRIT("TEST_MACSEC: Failed, test_macsec_put_one()\n");
            goto test_done;
        }
    }

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Packet1 submitted\n");
    }

    /* Receive the result packet */
    if (!test_macsec_get_one(TestConf_p,
                             PktAdmin_p->DstPkt_p,
                             &PktAdmin_p->DstPkt_ByteCount,
                             TC_Pkt_p->ChannelID))
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_get_one()\n");
        goto test_done;
    }

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Result packet received, size %d\n",
                             PktAdmin_p->DstPkt_ByteCount);
        Log_HexDump("TEST_MACSEC: Received packet data",
                    0,
                    PktAdmin_p->DstPkt_p,
                    PktAdmin_p->DstPkt_ByteCount);
    }

    /* The result packet should be protected by the first SA */
    if (!test_macsec_cmp_pkts(PktAdmin_p->DstPkt_p,
                              PktAdmin_p->DstPkt_ByteCount,
                              TC_Pkt_p->DstPkt_p,
                              TC_Pkt_p->DstPkt_ByteCount))
    {
        fSuccess = false;
        goto test_done;
    }

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Result and expected packet match\n");
    }

    /* Packet should be classified */
    if (!test_macsec_single_transform_statistics_test(TestConf_p,
                                                      TC_Transform_p,
                                                      FirstTransformAdmin_p))
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, "
                 "test_macsec_single_transform_statistics_test()\n");
        goto test_done;
    }

    /* Install the second SA */
    TC_Transform_p++;
    SA_Input_p = &TC_Transform_p->SA_Data;
    ZEROINIT(SA_Params);

    SecondTransformAdmin_p = test_macsec_malloc(sizeof(Test_Transform_t));
    if (SecondTransformAdmin_p == NULL)
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, Second Transform admin allocation\n");
        goto test_done;
    }
    memset(SecondTransformAdmin_p, 0, sizeof(Test_Transform_t));

    /* Copy SA data */
    test_macsec_sa_copy(TestConf_p,
                        SA_Input_p,
                        TC_Transform_p,
                        SecondTransformAdmin_p,
                        &SA_Params);

    /* Chain the second SA to the first SA */
    SecY_Rc = SecY_SA_Add(TestConf_p->DeviceId,
                          0,
                          &SecondTransformAdmin_p->TransformHandle,
                          &SA_Params);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Add()=%d\n", SecY_Rc);
        goto test_done;
    }


    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Second transform installed overrules first\n");
    }

    /* Remove first transform record. */
    if (!test_macsec_transform_uninstall(TestConf_p, 1, FirstTransformAdmin_p))
    {
        fSuccess = false;
    }

    /* Test the second packet */
    PktAdmin_p++;
    TC_Pkt_p++;
    memcpy(PktAdmin_p->SrcPkt_p, TC_Pkt_p->SrcPkt_p, PktAdmin_p->SrcPkt_ByteCount);

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Process packet of size %d\n",
                             PktAdmin_p->SrcPkt_ByteCount);
        Log_HexDump("TEST_MACSEC: Submitted packet data",
                    0,
                    PktAdmin_p->SrcPkt_p,
                    PktAdmin_p->SrcPkt_ByteCount);
    }

    /* Submit the packet */
    {
        unsigned vPort = 0;

        if (TestRec_p->CfyE_Data_p == NULL)
        {
            /* Use provided vPort, otherwise vPort = 0 */
            vPort = TC_Pkt_p->vPort;
        }

        if (!test_macsec_put_one(TestConf_p,
                                 PktAdmin_p->SrcPkt_p,
                                 PktAdmin_p->SrcPkt_ByteCount,
                                 TC_Pkt_p->ChannelID,
                                 vPort,
                                 TC_Pkt_p->SecTAGOffset,
                                 TC_Pkt_p->fControl))
        {
            fSuccess = false;
            LOG_CRIT("TEST_MACSEC: Failed, test_macsec_put_one()\n");
            goto test_done;
        }
    }

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Packet2 submitted\n");
    }

    /* Receive the result packet */
    if (!test_macsec_get_one(TestConf_p,
                             PktAdmin_p->DstPkt_p,
                             &PktAdmin_p->DstPkt_ByteCount,
                             TC_Pkt_p->ChannelID))
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_get_one()\n");
        goto test_done;
    }

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Result packet received, size %d\n",
                             PktAdmin_p->DstPkt_ByteCount);
        Log_HexDump("TEST_MACSEC: Received packet data",
                    0,
                    PktAdmin_p->DstPkt_p,
                    PktAdmin_p->DstPkt_ByteCount);
    }

    /* The result packet should be protected by the second SA */
    if (!test_macsec_cmp_pkts(PktAdmin_p->DstPkt_p,
                              PktAdmin_p->DstPkt_ByteCount,
                              TC_Pkt_p->DstPkt_p,
                              TC_Pkt_p->DstPkt_ByteCount))
    {
        fSuccess = false;
        goto test_done;
    }

    /* Should pass for the second SA */
    if (!test_macsec_single_transform_statistics_test(TestConf_p,
                                                      TC_Transform_p,
                                                      SecondTransformAdmin_p))
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, "
                 "test_macsec_single_transform_statistics_test()\n");
        goto test_done;
    }

    /* Restore the pointers */
    PktAdmin_p--;

test_done:
    /* Free packet buffers */
    if (!test_macsec_pkt_free(TestRec_p, OrigPktAdmin_p))
    {
        fSuccess = false;
    }

    if (!test_macsec_transform_uninstall(TestConf_p, 1, SecondTransformAdmin_p))
    {
        fSuccess = false;
    }

    return fSuccess;
}


/*----------------------------------------------------------------------------
 * test_macsec_egress_rekey_test
 *
 * 1. Add one SA.
 * 2. Chain a second SA on the same vPort.
 * 3. Process a packet using the first SA.
 * 4. Switch to the second SA, either automatically by the HW or manually
 *    by calling SecY_SA_Switch().
 * 5. Remove the first SA.
 * 6. Re-test the packet, the output data should be protected by the second SA.
 */
static bool
test_macsec_egress_rekey_test(
    const Test_Case_ConfParams_t * const TestConf_p,
    const Test_Case_Record_t * TestRec_p,
    const bool fAutoSwitch)
{
    bool fSuccess = true;
    SecY_SA_t *SA_Input_p;
    SecY_SA_t SA_Params;
    SecY_Status_t SecY_Rc;

    Test_Transform_t * FirstTransformAdmin_p = 0;
    Test_Transform_t * SecondTransformAdmin_p = 0;
    Test_Packet_t * PktAdmin_p = 0, *OrigPktAdmin_p = 0;

    Test_Case_Transform_t * TC_Transform_p = TestRec_p->TransformData_p;
    Test_Case_Packet_t * TC_Pkt_p = TestRec_p->PacketData_p;

    if (TestRec_p->TransformCount < 2)
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, Not enough transforms\n");
        goto test_done;
    }

    /* Update the secure channel rules if requested */
    if (!test_macsec_secure_channel_rules_update(TestConf_p, TestRec_p))
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_secure_channel_rules_update()\n");
        goto test_done;

    }
    /* Install the first SA */
    if (!test_macsec_transform_install(TestConf_p, TestRec_p,
                                       0, 1,
                                       &FirstTransformAdmin_p))
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_transform_install()\n");
        goto test_done;
    }

    /* Chain the second SA */
    TC_Transform_p++;
    SA_Input_p = &TC_Transform_p->SA_Data;
    ZEROINIT(SA_Params);

    SecondTransformAdmin_p = test_macsec_malloc(sizeof(Test_Transform_t));
    if (SecondTransformAdmin_p == NULL)
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, Second Transform admin allocation\n");
        goto test_done;
    }
    memset(SecondTransformAdmin_p, 0, sizeof(Test_Transform_t));

    /* Copy SA data */
    test_macsec_sa_copy(TestConf_p,
                        SA_Input_p,
                        TC_Transform_p,
                        SecondTransformAdmin_p,
                        &SA_Params);

    /* Chain the second SA to the first SA */
    SecY_Rc = SecY_SA_Chain(TestConf_p->DeviceId,
                            FirstTransformAdmin_p->TransformHandle,
                            &SecondTransformAdmin_p->TransformHandle,
                            &SA_Params);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Chain()=%d\n", SecY_Rc);
        goto test_done;
    }
    SecY_Rc = SecY_SAIndex_Get(SecondTransformAdmin_p->TransformHandle,
                               &SecondTransformAdmin_p->SAIndex,
                               NULL);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        LOG_CRIT("TEST_MACSEC: Failed, SecY_SAIndex_Get()=%d\n", SecY_Rc);
        fSuccess = false;
        goto test_done;
    }

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Second transform installed, chained to first\n");
    }

#ifdef TEST_MACSEC_USE_READ_API
    test_macsec_show_diagnostics(TestConf_p->DeviceId, 1, false);
#endif
    /* Allocate buffers for both first and the second packets */
    if (!test_macsec_pkt_alloc(TestRec_p, &PktAdmin_p))
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_pkt_alloc()\n");
        goto test_done;
    }
    OrigPktAdmin_p = PktAdmin_p;

    /* Test the packet */
    memcpy(PktAdmin_p->SrcPkt_p, TC_Pkt_p->SrcPkt_p, PktAdmin_p->SrcPkt_ByteCount);

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Process packet of size %d\n",
                             PktAdmin_p->SrcPkt_ByteCount);
        Log_HexDump("TEST_MACSEC: Submitted packet data",
                    0,
                    PktAdmin_p->SrcPkt_p,
                    PktAdmin_p->SrcPkt_ByteCount);
    }

    /* Submit the packet */
    {
        unsigned vPort = 0;

        if (TestRec_p->CfyE_Data_p == NULL)
        {
            /* Use provided vPort, otherwise vPort = 0 */
            vPort = TC_Pkt_p->vPort;
        }

        if (!test_macsec_put_one(TestConf_p,
                                 PktAdmin_p->SrcPkt_p,
                                 PktAdmin_p->SrcPkt_ByteCount,
                                 TC_Pkt_p->ChannelID,
                                 vPort,
                                 TC_Pkt_p->SecTAGOffset,
                                 TC_Pkt_p->fControl))
        {
            fSuccess = false;
            LOG_CRIT("TEST_MACSEC: Failed, test_macsec_put_one()\n");
            goto test_done;
        }
    }

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Packet1 submitted\n");
    }

    /* Receive the result packet */
    if (!test_macsec_get_one(TestConf_p,
                             PktAdmin_p->DstPkt_p,
                             &PktAdmin_p->DstPkt_ByteCount,
                             TC_Pkt_p->ChannelID))
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_get_one()\n");
        goto test_done;
    }

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Result packet received, size %d\n",
                             PktAdmin_p->DstPkt_ByteCount);
        Log_HexDump("TEST_MACSEC: Received packet data",
                    0,
                    PktAdmin_p->DstPkt_p,
                    PktAdmin_p->DstPkt_ByteCount);
    }

    /* The result packet should be protected by the first SA */
    if (!test_macsec_cmp_pkts(PktAdmin_p->DstPkt_p,
                              PktAdmin_p->DstPkt_ByteCount,
                              TC_Pkt_p->DstPkt_p,
                              TC_Pkt_p->DstPkt_ByteCount))
    {
        fSuccess = false;
        goto test_done;
    }

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Result and expected packet match\n");
    }

    /* Packet should be classified */
    if (!test_macsec_single_transform_statistics_test(TestConf_p,
                                                      TC_Transform_p - 1,
                                                      FirstTransformAdmin_p))
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, "
                 "test_macsec_single_transform_statistics_test()\n");
        goto test_done;
    }

#ifdef TEST_MACSEC_USE_WARMBOOT
        test_macsec_warmboot_shutdown();
        test_macsec_warmboot_restore();


        SecY_SAHandle_Get(TestConf_p->DeviceId,
                          FirstTransformAdmin_p->SAIndex,
                          &FirstTransformAdmin_p->TransformHandle);
        SecY_SAHandle_Get(TestConf_p->DeviceId,
                          SecondTransformAdmin_p->SAIndex,
                          &SecondTransformAdmin_p->TransformHandle);
#endif
#ifdef TEST_MACSEC_USE_READ_API
        {
            SecY_SAHandle_t NewTransformHandle;
            SecY_Rc = SecY_SA_Chained_Get(TestConf_p->DeviceId,
                                          FirstTransformAdmin_p->TransformHandle,
                                          &NewTransformHandle);
            if (SecY_Rc != SECY_STATUS_OK)
            {
                fSuccess = false;
                LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Chained_Get()=%d\n", SecY_Rc);
                goto test_done;
            }
            if (!SecY_SAHandle_IsSame(&NewTransformHandle,
                                      &SecondTransformAdmin_p->TransformHandle))
            {
                fSuccess = false;
                LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Chained_Get() returned wrong handle\n");
                goto test_done;
            }

            if (TestConf_p->fVerbose)
            {
                Log_FormattedMessage("TEST_MACSEC: Chained SA detected for first SA.\n");
            }

            SecY_Rc = SecY_SA_Chained_Get(TestConf_p->DeviceId,
                                          SecondTransformAdmin_p->TransformHandle,
                                          &NewTransformHandle);
            if (SecY_Rc != SECY_STATUS_OK)
            {
                fSuccess = false;
                LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Chained_Get()=%d\n", SecY_Rc);
                goto test_done;
            }
            if (!SecY_SAHandle_IsSame(&NewTransformHandle,
                                      &SecY_SAHandle_NULL))
            {
                fSuccess = false;
                LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Chained_Get() returned non-null handle for non-chained SA\n");
                goto test_done;
            }

            if (TestConf_p->fVerbose)
            {
                Log_FormattedMessage("TEST_MACSEC: No chained SA detected for second SA.\n");
            }

        }
#endif


    if (!fAutoSwitch)
    {
        /* Switch to the second SA */
        SecY_Rc = SecY_SA_Switch(TestConf_p->DeviceId,
                                 FirstTransformAdmin_p->TransformHandle,
                                 SecondTransformAdmin_p->TransformHandle,
                                 &SA_Params);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            fSuccess = false;
            LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Switch()=%d\n", SecY_Rc);
            goto test_done;
        }
        if (TestConf_p->fVerbose)
        {
            Log_FormattedMessage("TEST_MACSEC: Manual switch to second transform\n");
        }

    }


    /* Update the first SA for coverage purpose. */
    {
        Test_Case_Transform_t SA_Input;
        Test_Case_Transform_t * TC_Transform_p = TestRec_p->TransformData_p;

        ZEROINIT(SA_Input);

        /* Copy SA and de-activate it */
        memcpy(&SA_Input.SA_Data, &TC_Transform_p->SA_Data, sizeof(SecY_SA_t));
        SA_Input.SA_Data.Params.Egress.fSAInUse = false;

        SA_Input.TransformStat_p = TC_Transform_p->TransformStat_p;

        /* Update SA */
        if (!test_macsec_single_transform_update(TestConf_p,
                                                 &SA_Input,
                                                 FirstTransformAdmin_p))
        {
            fSuccess = false;
            LOG_CRIT("TEST_MACSEC: Failed, "
                     "test_macsec_single_transform_update()\n");
            goto test_done;
        }
    }
    /* Remove the first transform record. */
    if (!test_macsec_transform_uninstall(TestConf_p, 1, FirstTransformAdmin_p))
    {
        fSuccess = false;
    }

    /* Check that the Active SA is now the second SA. */
    {
        unsigned int vPort = 0;
        SecY_SAHandle_t SAHandle;
        /* Switch to the second SA */
        SecY_Rc = SecY_SA_Active_E_Get(TestConf_p->DeviceId,
                                       vPort,
                                       &SAHandle);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            fSuccess = false;
            LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Active_E_Get()=%d\n", SecY_Rc);
            goto test_done;
        }
        if (!SecY_SAHandle_IsSame(&SecondTransformAdmin_p->TransformHandle, &SAHandle))
        {
            fSuccess = false;
            LOG_CRIT("TEST_MACSEC: Failed: returned SA Handle differs from expected one\n");
            goto test_done;
        }
        if (TestConf_p->fVerbose)
        {
            Log_FormattedMessage("TEST_MACSEC: Verified currently active SA\n");
        }
    }

    /* Test the second packet */
    PktAdmin_p++;
    TC_Pkt_p++;
    memcpy(PktAdmin_p->SrcPkt_p, TC_Pkt_p->SrcPkt_p, PktAdmin_p->SrcPkt_ByteCount);

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Process packet of size %d\n",
                             PktAdmin_p->SrcPkt_ByteCount);
        Log_HexDump("TEST_MACSEC: Submitted packet data",
                    0,
                    PktAdmin_p->SrcPkt_p,
                    PktAdmin_p->SrcPkt_ByteCount);
    }

    /* Submit the packet */
    {
        unsigned vPort = 0;

        if (TestRec_p->CfyE_Data_p == NULL)
        {
            /* Use provided vPort, otherwise vPort = 0 */
            vPort = TC_Pkt_p->vPort;
        }

        if (!test_macsec_put_one(TestConf_p,
                                 PktAdmin_p->SrcPkt_p,
                                 PktAdmin_p->SrcPkt_ByteCount,
                                 TC_Pkt_p->ChannelID,
                                 vPort,
                                 TC_Pkt_p->SecTAGOffset,
                                 TC_Pkt_p->fControl))
        {
            fSuccess = false;
            LOG_CRIT("TEST_MACSEC: Failed, test_macsec_put_one()\n");
            goto test_done;
        }
    }

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Packet2 submitted\n");
    }

    /* Receive the result packet */
    if (!test_macsec_get_one(TestConf_p,
                             PktAdmin_p->DstPkt_p,
                             &PktAdmin_p->DstPkt_ByteCount,
                             TC_Pkt_p->ChannelID))
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_get_one()\n");
        goto test_done;
    }

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Result packet received, size %d\n",
                             PktAdmin_p->DstPkt_ByteCount);
        Log_HexDump("TEST_MACSEC: Received packet data",
                    0,
                    PktAdmin_p->DstPkt_p,
                    PktAdmin_p->DstPkt_ByteCount);
    }

    /* The result packet should be protected by the second SA */
    if (!test_macsec_cmp_pkts(PktAdmin_p->DstPkt_p,
                              PktAdmin_p->DstPkt_ByteCount,
                              TC_Pkt_p->DstPkt_p,
                              TC_Pkt_p->DstPkt_ByteCount))
    {
        fSuccess = false;
        goto test_done;
    }

    /* Should pass for the second SA */
    if (!test_macsec_single_transform_statistics_test(TestConf_p,
                                                      TC_Transform_p,
                                                      SecondTransformAdmin_p))
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, "
                 "test_macsec_single_transform_statistics_test()\n");
        goto test_done;
    }

    /* Restore the pointers */
    PktAdmin_p--;

test_done:
    /* Free packet buffers */
    if (!test_macsec_pkt_free(TestRec_p, OrigPktAdmin_p))
    {
        fSuccess = false;
    }

    if (!test_macsec_transform_uninstall(TestConf_p, 1, SecondTransformAdmin_p))
    {
        fSuccess = false;
    }

    return fSuccess;
}

#endif /*#ifdef TEST_MACSEC_MODE_EGRESS */

#ifdef TEST_MACSEC_MODE_INGRESS
/*----------------------------------------------------------------------------
 * test_macsec_ingress_rekey_test
 * 1. Add the first SA (old key) and test a first packet, it should pass.
 * 2. Add a second SA (new key) and test a second packet, it should pass.
 * 3. De-activate the first SA (old key) via SecY_SA_Update()
 *    but keep its flow active, test it with the first packet,
 *    the packet can be still classified, but not transformed.
 * 4. Disable the first SA, send the first packet, it should be dropped.
 *
 * Note: The ingress SA's and packets must use the same vPort. The ingress SA's
 *       should have different AN's.
 */
static bool
test_macsec_ingress_rekey_test(
    const Test_Case_ConfParams_t * const TestConf_p,
    const Test_Case_Record_t * TestRec_p)
{
    bool fSuccess = true;

    Test_Transform_t * TransformAdmin_p = 0;
    Test_Packet_t * PktAdmin_p = 0;
    Test_Packet_t * TestPkt_p = 0;
    Test_Case_Packet_t * TC_Pkt_p = TestRec_p->PacketData_p;

    if (TestRec_p->TransformCount < 2)
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, Not enough transforms\n");
        goto test_done;
    }

    /* Install the all SA's (differ AN's) */
    if (!test_macsec_transform_install(TestConf_p, TestRec_p,
                                       0, TestRec_p->TransformCount,
                                       &TransformAdmin_p))
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_transform_install()\n");
        goto test_done;
    }

    /* Allocate buffers for both packets */
    if (!test_macsec_pkt_alloc(TestRec_p, &PktAdmin_p))
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_pkt_alloc()\n");
        goto test_done;
    }
    TestPkt_p = PktAdmin_p;

    /* Sanity check for the provided packet test vectors */
    if (!test_macsec_pkt_sanity_check(TestConf_p, TestRec_p))
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_pkt_sanity_check()\n");
        goto test_done;
    }

    /* Test both packets */
    if (!test_macsec_pkt_test(TestConf_p, TestRec_p,
                              0, TestRec_p->PacketCount, PktAdmin_p, 64))
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_pkt_test()\n");
        goto test_done;
    }

    /* Perform Transform Statistics Test if configured */
    if (!test_macsec_transform_statistics_test(TestConf_p, TestRec_p,
                                               TransformAdmin_p))
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, "
                 "test_macsec_transform_statistics_test()\n");
        goto test_done;
    }

    /* Update the first SA */
    {
        Test_Case_Transform_t SA_Input;
        Test_Case_Transform_t * TC_Transform_p = TestRec_p->TransformData_p;

        ZEROINIT(SA_Input);

        /* Copy SA and de-activate it */
        memcpy(&SA_Input.SA_Data, &TC_Transform_p->SA_Data, sizeof(SecY_SA_t));
        SA_Input.SA_Data.Params.Ingress.fSAInUse = false;

        SA_Input.TransformStat_p = TC_Transform_p->TransformStat_p;

        /* Update SA */
        if (!test_macsec_single_transform_update(TestConf_p,
                                                 &SA_Input,
                                                 TransformAdmin_p))
        {
            fSuccess = false;
            LOG_CRIT("TEST_MACSEC: Failed, "
                     "test_macsec_single_transform_update()\n");
            goto test_done;
        }
    }

    /* Test the first packet again after updating (disabling) the first SA */
    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Process packet of size %d\n",
                             TestPkt_p->SrcPkt_ByteCount);
        Log_HexDump("TEST_MACSEC: Submitted packet data",
                    0,
                    TestPkt_p->SrcPkt_p,
                    TestPkt_p->SrcPkt_ByteCount);
    }

    /* Submit the packet */
    {
        unsigned vPort = 0;

        if (TestRec_p->CfyE_Data_p == NULL)
        {
            /* Use provided vPort, otherwise vPort = 0 */
            vPort = TC_Pkt_p->vPort;
        }

        if (!test_macsec_put_one(TestConf_p,
                                 TestPkt_p->SrcPkt_p,
                                 TestPkt_p->SrcPkt_ByteCount,
                                 TC_Pkt_p->ChannelID,
                                 vPort,
                                 TC_Pkt_p->SecTAGOffset,
                                 TC_Pkt_p->fControl))
        {
            fSuccess = false;
            LOG_CRIT("TEST_MACSEC: Failed, test_macsec_put_one()\n");
            goto test_done;
        }
    }

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Packet submitted (%s)\n", __func__);
    }

    /* Receive the result packet */
    if (!test_macsec_get_one(TestConf_p,
                             TestPkt_p->DstPkt_p,
                             &TestPkt_p->DstPkt_ByteCount,
                             TC_Pkt_p->ChannelID))
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_get_one()\n");
        goto test_done;
    }

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Result packet received, size %d\n",
                             TestPkt_p->DstPkt_ByteCount);
        Log_HexDump("TEST_MACSEC: Received packet data",
                    0,
                    TestPkt_p->DstPkt_p,
                    TestPkt_p->DstPkt_ByteCount);
    }

    /* The received packets should be the same as the submit one */
    if (!test_macsec_cmp_pkts(TestPkt_p->DstPkt_p,
                              TestPkt_p->DstPkt_ByteCount,
                              TC_Pkt_p->SrcPkt_p,
                              TC_Pkt_p->SrcPkt_ByteCount))
    {
        fSuccess = false;
        goto test_done;
    }

    /* Check SA statistics */
    {
        SecY_Status_t SecY_Rc;
        SecY_SA_Stat_I_t Stat;

        ZEROINIT(Stat);

        SecY_Rc = SecY_SA_Statistics_I_Get(TestConf_p->DeviceId,
                                           TransformAdmin_p->TransformHandle,
                                           &Stat,
                                           true);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            fSuccess = false;
            LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Statistics_I_Get()=%d\n",
                     SecY_Rc);
            goto test_done;
        }

        if (TestConf_p->fVerbose)
        {
            Log_FormattedMessage("TEST_MACSEC: Ingress SA Statistics:\n"
                                 "\tInOctetsDecrypted: %u\n"
                                 "\tInOctetsValidated: %u\n"
                                 "\tInPktsDelayed:     %u\n"
                                 "\tInPktsInvalid:     %u\n"
                                 "\tInPktsLate:        %u\n"
                                 "\tInPktsNotUsingSA:  %u\n"
                                 "\tInPktsNotValid:    %u\n"
                                 "\tInPktsOK:          %u\n"
                                 "\tInPktsUnchecked:   %u\n"
                                 "\tInPktsUnusedSA:    %u\n",
                                 Stat.InOctetsDecrypted.Lo,
                                 Stat.InOctetsValidated.Lo,
                                 Stat.InPktsDelayed.Lo,
                                 Stat.InPktsInvalid.Lo,
                                 Stat.InPktsLate.Lo,
                                 Stat.InPktsNotUsingSA.Lo,
                                 Stat.InPktsNotValid.Lo,
                                 Stat.InPktsOK.Lo,
                                 Stat.InPktsUnchecked.Lo,
                                 Stat.InPktsUnusedSA.Lo);
        }

        /* Check statistics */
        if ((Stat.InOctetsDecrypted.Lo != 0) ||
            (Stat.InOctetsValidated.Lo != 0) ||
            (Stat.InPktsDelayed.Lo != 0) ||
            (Stat.InPktsInvalid.Lo != 0) ||
            (Stat.InPktsLate.Lo != 0) ||
            (Stat.InPktsNotUsingSA.Lo != 1) ||
            (Stat.InPktsNotValid.Lo != 0) ||
            (Stat.InPktsOK.Lo != 0) ||
            (Stat.InPktsNotValid.Lo != 0) ||
            (Stat.InPktsUnusedSA.Lo != 0))
        {
            fSuccess = false;
            LOG_CRIT("TEST_MACSEC: Failed, SA statistics check,\n"
                     "\tInOctetsDecrypted=%u, expected 0\n"
                     "\tInOctetsValidated=%u, expected 0\n"
                     "\tInPktsDelayed=%u, expected 0\n"
                     "\tInPktsInvalid=%u, expected 0\n"
                     "\tInPktsLate=%u, expected 0\n"
                     "\tInPktsNotUsingSA=%u, expected 1\n"
                     "\tInPktsNotValid=%u, expected 0\n"
                     "\tInPktsOK=%u, expected 0\n"
                     "\tInPktsNotValid=%u, expected 0\n"
                     "\tInPktsUnusedSA=%u, expected 0\n",
                     Stat.InOctetsDecrypted.Lo,
                     Stat.InOctetsValidated.Lo,
                     Stat.InPktsDelayed.Lo,
                     Stat.InPktsInvalid.Lo,
                     Stat.InPktsLate.Lo,
                     Stat.InPktsNotUsingSA.Lo,
                     Stat.InPktsNotValid.Lo,
                     Stat.InPktsOK.Lo,
                     Stat.InPktsUnchecked.Lo,
                     Stat.InPktsUnusedSA.Lo);
            goto test_done;
        }
    }

    if (TestRec_p->TransformData_p->SA_Data.Params.Ingress.ValidateFramesTagged == SECY_FRAME_VALIDATE_CHECK)
    {
        /* Submit a slightly modified first packet again */
        /* -> The e and c bit of the TCI are cleared to test statistics behaviour */
        ((uint8_t *)(TestPkt_p->SrcPkt_p))[14] &= ~(MASK_2_BITS << 2); /* clear e and c bit */

        if (TestConf_p->fVerbose)
        {
            Log_FormattedMessage("TEST_MACSEC: Process packet of size %d\n",
                                 TestPkt_p->SrcPkt_ByteCount);
            Log_HexDump("TEST_MACSEC: Submitted packet data",
                        0,
                        TestPkt_p->SrcPkt_p,
                        TestPkt_p->SrcPkt_ByteCount);
        }

        /* Submit the packet */
        {
            unsigned vPort = 0;

            if (TestRec_p->CfyE_Data_p == NULL)
            {
                /* Use provided vPort, otherwise vPort = 0 */
                vPort = TC_Pkt_p->vPort;
            }

            if (!test_macsec_put_one(TestConf_p,
                                     TestPkt_p->SrcPkt_p,
                                     TestPkt_p->SrcPkt_ByteCount,
                                     TC_Pkt_p->ChannelID,
                                     vPort,
                                     TC_Pkt_p->SecTAGOffset,
                                     TC_Pkt_p->fControl))
            {
                fSuccess = false;
                LOG_CRIT("TEST_MACSEC: Failed, test_macsec_put_one()\n");
                goto test_done;
            }
        }

        if (TestConf_p->fVerbose)
        {
            Log_FormattedMessage("TEST_MACSEC: Packet submitted (%s)\n", __func__);
        }

        /* Receive the result packet */
        if (!test_macsec_get_one(TestConf_p,
                                 TestPkt_p->DstPkt_p,
                                 &TestPkt_p->DstPkt_ByteCount,
                                 TC_Pkt_p->ChannelID))
        {
            fSuccess = false;
            LOG_CRIT("TEST_MACSEC: Failed, test_macsec_get_one()\n");
            goto test_done;
        }

        if (TestConf_p->fVerbose)
        {
            Log_FormattedMessage("TEST_MACSEC: Result packet received, size %d\n",
                                 TestPkt_p->DstPkt_ByteCount);
            Log_HexDump("TEST_MACSEC: Received packet data",
                        0,
                        TestPkt_p->DstPkt_p,
                        TestPkt_p->DstPkt_ByteCount);
        }

        /* Check SA statistics */
        {
            SecY_Status_t SecY_Rc;
            SecY_SA_Stat_I_t Stat;

            ZEROINIT(Stat);

            SecY_Rc = SecY_SA_Statistics_I_Get(TestConf_p->DeviceId,
                                               TransformAdmin_p->TransformHandle,
                                               &Stat,
                                               true);
            if (SecY_Rc != SECY_STATUS_OK)
            {
                fSuccess = false;
                LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Statistics_I_Get()=%d\n",
                         SecY_Rc);
                goto test_done;
            }

            if (TestConf_p->fVerbose)
            {
                Log_FormattedMessage("TEST_MACSEC: Ingress SA Statistics:\n"
                                     "\tInOctetsDecrypted: %u\n"
                                     "\tInOctetsValidated: %u\n"
                                     "\tInPktsDelayed:     %u\n"
                                     "\tInPktsInvalid:     %u\n"
                                     "\tInPktsLate:        %u\n"
                                     "\tInPktsNotUsingSA:  %u\n"
                                     "\tInPktsNotValid:    %u\n"
                                     "\tInPktsOK:          %u\n"
                                     "\tInPktsUnchecked:   %u\n"
                                     "\tInPktsUnusedSA:    %u\n",
                                     Stat.InOctetsDecrypted.Lo,
                                     Stat.InOctetsValidated.Lo,
                                     Stat.InPktsDelayed.Lo,
                                     Stat.InPktsInvalid.Lo,
                                     Stat.InPktsLate.Lo,
                                     Stat.InPktsNotUsingSA.Lo,
                                     Stat.InPktsNotValid.Lo,
                                     Stat.InPktsOK.Lo,
                                     Stat.InPktsUnchecked.Lo,
                                     Stat.InPktsUnusedSA.Lo);
            }

            /* Check statistics */
            if ((Stat.InOctetsDecrypted.Lo != 0) ||
                (Stat.InOctetsValidated.Lo != 0) ||
                (Stat.InPktsDelayed.Lo != 0) ||
                (Stat.InPktsInvalid.Lo != 0) ||
                (Stat.InPktsLate.Lo != 0) ||
                (Stat.InPktsNotUsingSA.Lo != 0) ||
                (Stat.InPktsNotValid.Lo != 0) ||
                (Stat.InPktsOK.Lo != 0) ||
                (Stat.InPktsNotValid.Lo != 0) ||
                (Stat.InPktsUnusedSA.Lo != 1))
            {
                fSuccess = false;
                LOG_CRIT("TEST_MACSEC: Failed, SA statistics check,\n"
                         "\tInOctetsDecrypted=%u, expected 0\n"
                         "\tInOctetsValidated=%u, expected 0\n"
                         "\tInPktsDelayed=%u, expected 0\n"
                         "\tInPktsInvalid=%u, expected 0\n"
                         "\tInPktsLate=%u, expected 0\n"
                         "\tInPktsNotUsingSA=%u, expected 0\n"
                         "\tInPktsNotValid=%u, expected 0\n"
                         "\tInPktsOK=%u, expected 0\n"
                         "\tInPktsNotValid=%u, expected 0\n"
                         "\tInPktsUnusedSA=%u, expected 1\n",
                         Stat.InOctetsDecrypted.Lo,
                         Stat.InOctetsValidated.Lo,
                         Stat.InPktsDelayed.Lo,
                         Stat.InPktsInvalid.Lo,
                         Stat.InPktsLate.Lo,
                         Stat.InPktsNotUsingSA.Lo,
                         Stat.InPktsNotValid.Lo,
                         Stat.InPktsOK.Lo,
                         Stat.InPktsUnchecked.Lo,
                         Stat.InPktsUnusedSA.Lo);
                goto test_done;
            }
        }
    }

    /* Test the second packet again (should be handled according the Mask setting) */
    TC_Pkt_p++;
    TestPkt_p++;

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Process packet of size %d\n",
                             TestPkt_p->SrcPkt_ByteCount);
        Log_HexDump("TEST_MACSEC: Submitted packet data",
                    0,
                    TestPkt_p->SrcPkt_p,
                    TestPkt_p->SrcPkt_ByteCount);
    }

    /* Submit the first packet */
    {
        unsigned vPort = 0;

        if (TestRec_p->CfyE_Data_p == NULL)
        {
            /* Use provided vPort, otherwise vPort = 0 */
            vPort = TC_Pkt_p->vPort;
        }

        if (!test_macsec_put_one(TestConf_p,
                                 TestPkt_p->SrcPkt_p,
                                 TestPkt_p->SrcPkt_ByteCount,
                                 TC_Pkt_p->ChannelID,
                                 vPort,
                                 TC_Pkt_p->SecTAGOffset,
                                 TC_Pkt_p->fControl))
        {
            LOG_CRIT("TEST_MACSEC: Failed, test_macsec_put_one()\n");
            fSuccess = false;
            goto test_done;
        }
    }

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Packet submitted\n");
    }

    /* Receive the result packet */
    if (!test_macsec_get_one(TestConf_p,
                             TestPkt_p->DstPkt_p,
                             &TestPkt_p->DstPkt_ByteCount,
                             TC_Pkt_p->ChannelID))
    {
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_get_one()\n");
        fSuccess = false;
        goto test_done;
    }

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Result packet received, size %d\n",
                             TestPkt_p->DstPkt_ByteCount);
        Log_HexDump("TEST_MACSEC: Received packet data",
                    0,
                    TestPkt_p->DstPkt_p,
                    TestPkt_p->DstPkt_ByteCount);
    }

    /* The received packets should be processed */
    if (!test_macsec_cmp_pkts(TestPkt_p->DstPkt_p,
                              TestPkt_p->DstPkt_ByteCount,
                              TC_Pkt_p->DstPkt_p,
                              TC_Pkt_p->DstPkt_ByteCount))
    {
        fSuccess = false;
        goto test_done;
    }

    /* Check SA statistics, the packet should not be counted due to packet */
    /* number update that has happened previously */
    {
        SecY_Status_t SecY_Rc;
        SecY_SA_Stat_I_t Stat;
        uint32_t ExpectedLate = 0;
        uint32_t ExpectedOK = 0;

        ZEROINIT(Stat);

        SecY_Rc = SecY_SA_Statistics_I_Get(TestConf_p->DeviceId,
                                           TransformAdmin_p[1].TransformHandle,
                                           &Stat,
                                           true);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            fSuccess = false;
            LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Statistics_I_Get()=%d\n",
                     SecY_Rc);
            goto test_done;
        }

        if (TestConf_p->fVerbose)
        {
            Log_FormattedMessage("TEST_MACSEC: Ingress SA Statistics:\n"
                                 "\tInOctetsDecrypted: %u\n"
                                 "\tInOctetsValidated: %u\n"
                                 "\tInPktsDelayed:     %u\n"
                                 "\tInPktsInvalid:     %u\n"
                                 "\tInPktsLate:        %u\n"
                                 "\tInPktsNotUsingSA:  %u\n"
                                 "\tInPktsNotValid:    %u\n"
                                 "\tInPktsOK:          %u\n"
                                 "\tInPktsUnchecked:   %u\n"
                                 "\tInPktsUnusedSA:    %u\n",
                                 Stat.InOctetsDecrypted.Lo,
                                 Stat.InOctetsValidated.Lo,
                                 Stat.InPktsDelayed.Lo,
                                 Stat.InPktsInvalid.Lo,
                                 Stat.InPktsLate.Lo,
                                 Stat.InPktsNotUsingSA.Lo,
                                 Stat.InPktsNotValid.Lo,
                                 Stat.InPktsOK.Lo,
                                 Stat.InPktsUnchecked.Lo,
                                 Stat.InPktsUnusedSA.Lo);
        }

        if (TestRec_p->TransformData_p->SA_Data.Params.Ingress.ValidateFramesTagged == SECY_FRAME_VALIDATE_CHECK)
        {
            /* No ReplayProtection */
            ExpectedLate = 1;
        }
        else
        {
            /* ReplayProtection window */
            ExpectedOK = 1;
        }

        /* Check statistics */
        if ((Stat.InOctetsDecrypted.Lo != 49) ||
            (Stat.InOctetsValidated.Lo != 0) ||
            (Stat.InPktsDelayed.Lo != 0) ||
            (Stat.InPktsInvalid.Lo != 0) ||
            (Stat.InPktsLate.Lo != ExpectedLate) ||
            (Stat.InPktsNotUsingSA.Lo != 0) ||
            (Stat.InPktsNotValid.Lo != 0) ||
            (Stat.InPktsOK.Lo != ExpectedOK) ||
            (Stat.InPktsNotValid.Lo != 0) ||
            (Stat.InPktsUnusedSA.Lo != 0))
        {
            fSuccess = false;
            LOG_CRIT("TEST_MACSEC: Failed, SA statistics check,\n"
                     "\tInOctetsDecrypted=%u, expected 49\n"
                     "\tInOctetsValidated=%u, expected 0\n"
                     "\tInPktsDelayed=%u, expected 0\n"
                     "\tInPktsInvalid=%u, expected 0\n"
                     "\tInPktsLate=%u, expected %d\n"
                     "\tInPktsNotUsingSA=%u, expected 0\n"
                     "\tInPktsNotValid=%u, expected 0\n"
                     "\tInPktsOK=%u, expected %d\n"
                     "\tInPktsNotValid=%u, expected 0\n"
                     "\tInPktsUnusedSA=%u, expected 0\n",
                     Stat.InOctetsDecrypted.Lo,
                     Stat.InOctetsValidated.Lo,
                     Stat.InPktsDelayed.Lo,
                     Stat.InPktsInvalid.Lo,
                     Stat.InPktsLate.Lo, ExpectedLate,
                     Stat.InPktsNotUsingSA.Lo,
                     Stat.InPktsNotValid.Lo,
                     Stat.InPktsOK.Lo, ExpectedOK,
                     Stat.InPktsUnchecked.Lo,
                     Stat.InPktsUnusedSA.Lo);
            goto test_done;
        }
    }

test_done:
    /* Free packet buffers */
    if (!test_macsec_pkt_free(TestRec_p, PktAdmin_p))
    {
        fSuccess = false;
    }

    if (!test_macsec_transform_uninstall(TestConf_p,
                                         TestRec_p->TransformCount,
                                         TransformAdmin_p))
    {
        fSuccess = false;
    }

    return fSuccess;
}


/*----------------------------------------------------------------------------
 * test_macsec_ingress_updatepn_test
 * 1. Add an SA and a  flow, enable this flow,
 * 2. Update NextPN.
 * 3. Process the packet and verify that it succeeds.
 * 4. Update NextPN again.
 */
static bool
test_macsec_ingress_updatepn_test(
        const Test_Case_ConfParams_t * const TestConf_p,
        const Test_Case_Record_t * TestRec_p,
        unsigned int MaxSAs)
{
    bool fFailed = false;
    unsigned int i;

    Test_Transform_t * TransformAdmin_p = 0;
    Test_Packet_t * PktAdmin_p = 0;

    /* Install the SA, will use SA index 0 */
    if (!test_macsec_transform_install(TestConf_p, TestRec_p,
                                       0, TestRec_p->TransformCount,
                                       &TransformAdmin_p))
    {
        fFailed = true;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_transform_install()\n");
        goto test_done;
    }

    /* Allocate buffers for the packets */
    if (!test_macsec_pkt_alloc(TestRec_p, &PktAdmin_p))
    {
        fFailed = true;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_pkt_alloc()\n");
        goto test_done;
    }

    /* Sanity check for the provided packet test vectors */
    if (!test_macsec_pkt_sanity_check(TestConf_p, TestRec_p))
    {
        fFailed = true;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_pkt_sanity_check()\n");
        goto test_done;
    }

    /* Update NextPN field. */
    /* Will update sequence number to 12 in 32-bit SA. */
    /* Will have no offect for 64-bit SA as original number is higher. */
    if (!test_macsec_transform_nextpn_update(TestConf_p,
                                             TransformAdmin_p,
                                             12,
                                             0,
                                             333))
    {
        fFailed = true;
        LOG_CRIT("TEST_MACSEC: Failed, "
                 "test_macsec_transform_nextpn_update()\n");
        goto test_done;
    }

    /* Test packet */
    if (!test_macsec_pkt_test(TestConf_p, TestRec_p,
                              0, TestRec_p->PacketCount, PktAdmin_p, 64))
    {
        fFailed = true;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_pkt_test()\n");
        goto test_done;
    }

    /* Update NextPN field. */
    /* Will have no effect in 32-bit SA (high number ignored) */
    /* Will update 64-bit sequence number. */
    if (!test_macsec_transform_nextpn_update(TestConf_p,
                                             TransformAdmin_p,
                                             0,
                                             0xf0000000,
                                             44))
    {
        fFailed = true;
        LOG_CRIT("TEST_MACSEC: Failed, "
                 "test_macsec_transform_nextpn_update()\n");
        goto test_done;
    }

    /* Perform Transform Statistics Test if configured */
    if (!test_macsec_transform_statistics_test(TestConf_p, TestRec_p,
                                               TransformAdmin_p))
    {
        fFailed = true;
        LOG_CRIT("TEST_MACSEC: Failed, "
                 "test_macsec_transform_statistics_test()\n");
        goto test_done;
    }

test_done:
    /* Free packet buffers */
    if (!test_macsec_pkt_free(TestRec_p, PktAdmin_p))
    {
        fFailed = true;
    }

    if (!test_macsec_transform_uninstall(TestConf_p,
                                         TestRec_p->TransformCount,
                                         TransformAdmin_p))
    {
        fFailed = true;
    }
    if (fFailed) return false;

    /* Test NextPN update for subsequent SAs also. This will use SA
       index 1..max */
    for (i=1; i < MIN(MaxSAs,4096) && !fFailed; i++)
    {
        /* Add SA */
        SecY_SA_t *SA_Input_p;
        SecY_SA_t SA_Params;
        SecY_Status_t SecY_Rc;
        Test_Case_Transform_t * TC_Transform_p = TestRec_p->TransformData_p;
        Test_Transform_t TransformAdmin;
        SA_Input_p = &TC_Transform_p->SA_Data;
        ZEROINIT(SA_Params);
        ZEROINIT(TransformAdmin);

        /* Copy SA data */
        test_macsec_sa_copy(TestConf_p,
                            SA_Input_p,
                            TC_Transform_p,
                            &TransformAdmin,
                            &SA_Params);

        /* Add SA in driver, purpose is causing a higher SA index to be
           picked for the NextPN Update */
        SecY_Rc = SecY_SA_Add(TestConf_p->DeviceId,
                              0,
                              &TransformAdmin.TransformHandle,
                              &SA_Params);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            fFailed = true;
            LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Add()=%d\n", SecY_Rc);
            goto test_done;
        }

        /* Update NextPN field. */
        /* Will update sequence number to 12 in 32-bit SA. */
        /* Will have no offect for 64-bit SA as original number is higher. */
        if (!test_macsec_transform_nextpn_update(TestConf_p,
                                                 &TransformAdmin,
                                                 12,
                                                 0,
                                                 333))
        {
            fFailed = true;
            LOG_CRIT("TEST_MACSEC: Failed, "
                     "test_macsec_transform_nextpn_update()\n");
        }

        /* Update NextPN field. */
        /* Will have no effect in 32-bit SA (high number ignored) */
        /* Will update 64-bit sequence number. */
        if (!test_macsec_transform_nextpn_update(TestConf_p,
                                                 &TransformAdmin,
                                                 0,
                                                 0xf0000000,
                                                 44))
        {
            fFailed = true;
            LOG_CRIT("TEST_MACSEC: Failed, "
                     "test_macsec_transform_nextpn_update()\n");
        }

        /* Remove the SA */
        SecY_SA_Remove(TestConf_p->DeviceId, TransformAdmin.TransformHandle);
        test_macsec_free(TransformAdmin.TransformRec_p);
    }
    return !fFailed;
}


#define TEST_MACSEC_RELTIRE_LOOPCOUNT 1000
#define TEST_MACSEC_RETIRE_PRESCALE 8192
#define TEST_MACSEC_RETIRE_TIMEOUT 20


/*----------------------------------------------------------------------------
 * test_macsec_ingress_sa_retire_test
 * 1. Check whether this hardware supports the feature.
 * 2. Enable SA retire feature.
 * 3  Add an SA.
 * 4. Process a packet
 * 5. Verify that SA is not retire yet.
 * 6. Wait the SA retire time.
 * 7. Verify that SA expire is reported for this SA.
 */
static bool
test_macsec_ingress_sa_retire_test(
        const Test_Case_ConfParams_t * const TestConf_p,
        const Test_Case_Record_t * TestRec_p)
{
    bool fFailed = false;

    Test_Transform_t * TransformAdmin_p = 0;
    Test_Packet_t * PktAdmin_p = 0;
    unsigned int SAIndex;
    unsigned int LoopCounter = TEST_MACSEC_RELTIRE_LOOPCOUNT;
    unsigned int *Indexes_p = 0;
    unsigned int NumIndexes;
    SecY_Status_t SecY_Rc;
    {
        SecY_Device_Params_t Device_Control;
        SecY_SARetireConf_t RetireConf;
        ZEROINIT(Device_Control);
        ZEROINIT(RetireConf);
        Device_Control.SARetireConf_p = &RetireConf;
        RetireConf.TimerPrescale = TEST_MACSEC_RETIRE_PRESCALE;
        RetireConf.SATimeout = TEST_MACSEC_RETIRE_TIMEOUT;
        SecY_Rc = SecY_Device_Update(TestConf_p->DeviceId, &Device_Control);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("SecY_Device_Update returned error %d\n",SecY_Rc);
            return false;
        }
        ZEROINIT(RetireConf);
        SecY_Rc = SecY_Device_Config_Get(TestConf_p->DeviceId, &Device_Control);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("SecY_Device_Config_Get returned error %d\n",SecY_Rc);
            return false;
        }
        LOG_CRIT("TEST_MACSEC: TimerPrescale=%d SATimeout=%d\n",
                 RetireConf.TimerPrescale,
                 RetireConf.SATimeout);
        if (RetireConf.TimerPrescale == TEST_MACSEC_RETIRE_PRESCALE
            && RetireConf.SATimeout == TEST_MACSEC_RETIRE_TIMEOUT)
        {
            LOG_CRIT("This hardware supports the SA retire registers, continuing\n");
        }
        else
        {
            LOG_CRIT("This hardware does not support the SA retire registers, skipping\n");
            return true;
        }
    }
    Indexes_p = test_macsec_malloc(256 * sizeof(unsigned int));
    if (Indexes_p == 0)
    {
        return false;
    }

    /* Install the SA */
    if (!test_macsec_transform_install(TestConf_p, TestRec_p,
                                       0, TestRec_p->TransformCount,
                                       &TransformAdmin_p))
    {
        fFailed = true;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_transform_install()\n");
        goto test_done;
    }

    /* Allocate buffers for the packets */
    if (!test_macsec_pkt_alloc(TestRec_p, &PktAdmin_p))
    {
        fFailed = true;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_pkt_alloc()\n");
        goto test_done;
    }

    /* Sanity check for the provided packet test vectors */
    if (!test_macsec_pkt_sanity_check(TestConf_p, TestRec_p))
    {
        fFailed = true;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_pkt_sanity_check()\n");
        goto test_done;
    }

    LOG_CRIT("Clear the SA Expired Summary registers\n");
    SecY_Rc = SecY_SA_ExpiredSummary_CheckAndClear(
        TestConf_p->DeviceId,
        &Indexes_p,
        &NumIndexes);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        fFailed = true;
        LOG_CRIT("TEST_MACSEC: Failed, SecY_SAIndex_Get\n");
        goto test_done;
    }

    /* Test packet */
    if (!test_macsec_pkt_test(TestConf_p, TestRec_p,
                              0, TestRec_p->PacketCount, PktAdmin_p, 64))
    {
        fFailed = true;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_pkt_test()\n");
        goto test_done;
    }
    SecY_Rc = SecY_SAIndex_Get(TransformAdmin_p[0].TransformHandle,
                               &SAIndex,
                               NULL);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        fFailed = true;
        LOG_CRIT("TEST_MACSEC: Failed, SecY_SAIndex_Get\n");
        goto test_done;
    }

    SecY_Rc = SecY_SA_ExpiredSummary_CheckAndClear(
        TestConf_p->DeviceId,
        &Indexes_p,
        &NumIndexes);
    if (SecY_Rc != SECY_STATUS_OK)
    {
        fFailed = true;
        LOG_CRIT("TEST_MACSEC: Failed, SecY_SAIndex_Get\n");
        goto test_done;
    }
    if (NumIndexes != 0)
    {
        fFailed = true;
        LOG_CRIT("TEST_MACSEC: SA expired unexpectedly\n");
        goto test_done;
    }

    while (--LoopCounter)
    {
        SecY_Rc = SecY_SA_ExpiredSummary_CheckAndClear(
            TestConf_p->DeviceId,
            &Indexes_p,
            &NumIndexes);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            fFailed = true;
            LOG_CRIT("TEST_MACSEC: Failed, SecY_SAIndex_Get\n");
            goto test_done;
        }
        if (NumIndexes == 1 && Indexes_p[0]==SAIndex)
        {
            LOG_CRIT("TEST_MACSEC: SA expire after %d calls\n",
                     TEST_MACSEC_RELTIRE_LOOPCOUNT - LoopCounter);
            break;
        }
        test_macsec_usleep(TestConf_p->TimeoutMS * 1000);
    }
    if (LoopCounter == 0)
    {
        fFailed = true;
        LOG_CRIT("TEST_MACSEC: SA expire timeout\n");
        goto test_done;
    }

    /* Perform Transform Statistics Test if configured */
    if (!test_macsec_transform_statistics_test(TestConf_p, TestRec_p,
                                               TransformAdmin_p))
    {
        fFailed = true;
        LOG_CRIT("TEST_MACSEC: Failed, "
                 "test_macsec_transform_statistics_test()\n");
        goto test_done;
    }

test_done:
    test_macsec_free(Indexes_p);

    /* Free packet buffers */
    if (!test_macsec_pkt_free(TestRec_p, PktAdmin_p))
    {
        fFailed = true;
    }

    if (!test_macsec_transform_uninstall(TestConf_p,
                                         TestRec_p->TransformCount,
                                         TransformAdmin_p))
    {
        fFailed = true;
    }

    return !fFailed;
}


#endif /*#ifdef TEST_MACSEC_MODE_INGRESS */


/*----------------------------------------------------------------------------
 * test_macsec_all_counters_zero
 *
 * Check if all counters in a statistics structure are zero.
 *
 * Counters_p (input)
 *     Pointer to the statistics structure containing just statistics counters.
 *
 * nItems (input)
 *     Number of 32-bit integers contained in the structure.
 *
 * Return: true if all counters are zero, false otherwise.
 */
static bool
test_macsec_all_counters_zero(
        void * Counters_p,
        unsigned int nItems)
{
    uint32_t *p = Counters_p;
    unsigned int i;

    for (i=0; i < nItems; i++)
    {
        if (p[i] != 0)
        {
            return false;
        }
    }
    return true;
}


/*----------------------------------------------------------------------------
 * test_macsec_reuse_sa_vport_test
 * 1 Add one or more vPorts and SA records.
 * 2 Process packets with them, making statistics counters nonzero.
 * 3 Remove these again.
 * 4 Add and remove vPorts and SAs so the records used in step 1 will be next.
 * 5 Allocated one or more vPorts and SA records, reused from step 1.
 * 6 Verify that all statistics counters are zero.
 *
 */
static bool
test_macsec_reuse_sa_vport_test(
        const Test_Case_ConfParams_t * const TestConf_p,
        const Test_Case_Record_t * TestRec_p,
        const unsigned int MaxvPorts,
        const unsigned int MaxSAs)
{
    bool fFailed = false;
    Test_Transform_t * TransformAdmin_p = 0;
    Test_Packet_t * PktAdmin_p = 0;
#ifdef TEST_MACSEC_USE_CFYE
    Test_CfyEvPort_t * vPortAdmin_p = 0;
    Test_CfyERules_t * RuleAdmin_p = 0;
#endif /* TEST_MACSEC_USE_CFYE */

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
            goto test_done;
        }
    }

    if (TransformAdmin_p != NULL)
    {
        /* Check that the SA Update control word is zero, as the
           transform record in this test has the Sequence number
           rollover bit set.*/
        SecY_Status_t SecY_Rc;
        uint32_t UpdateCtrl;

        SecY_Rc = SecY_SA_Read(TestConf_p->DeviceId,
                               TransformAdmin_p->TransformHandle,
                               1,
                               1,
                               &UpdateCtrl);
        if (SecY_Rc != SECY_STATUS_OK)
        {
            LOG_CRIT("TEST_MACSEC: SecY_SA_Read failed, error=%d\n",SecY_Rc);
            fFailed = true;
            goto test_done;
        }
        if (UpdateCtrl != 0)
        {
            LOG_CRIT("TEST_MACSEC: Updated control word set, while not desired value=0x%08x\n",UpdateCtrl);
            fFailed = true;
            goto test_done;
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
            goto test_done;
        }
    }
#endif /* TEST_MACSEC_USE_CFYE */
    /* Update the channel rules if requested */
    if (!test_macsec_channel_rules_update(TestConf_p, TestRec_p))
    {
        fFailed = true;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_channel_rules_update()\n");
        goto test_done;
    }

    /* Update the secure channel rules if requested */
    if (!test_macsec_secure_channel_rules_update(TestConf_p, TestRec_p))
    {
            fFailed = true;
            LOG_CRIT("TEST_MACSEC: Failed, test_macsec_secure_channel_rules_update()\n");
            goto test_done;
    }

#ifdef TEST_MACSEC_USE_CFYE
    if (!test_macsec_CfyE_update(TestConf_p, TestRec_p,
                                 vPortAdmin_p, RuleAdmin_p))
    {
        fFailed = true;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_CfyE_Rules_update()\n");
        goto test_done;
    }
#endif /* TEST_MACSEC_USE_CFYE */
    /* Allocate packet buffers */
    if (!test_macsec_pkt_alloc(TestRec_p, &PktAdmin_p))
    {
        fFailed = true;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_pkt_alloc()\n");
        goto test_done;
    }

    /* Sanity check for the provided packet test vectors */
    if (!test_macsec_pkt_sanity_check(TestConf_p, TestRec_p))
    {
        fFailed = true;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_pkt_sanity_check()\n");
        goto test_done;
    }

    /* Test packets */
    if (!test_macsec_pkt_test(TestConf_p, TestRec_p,
                              0, TestRec_p->PacketCount, PktAdmin_p, 64))
    {
        fFailed = true;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_pkt_test()\n");
        goto test_done;
    }

test_done:
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

    if (fFailed)
    {
        return false;
    }
    /* Now we have SA and vPort with nonzero statistics. Allocate SA
       records until original SA record is reused, check statistics to
       be zero. Add vPorts until original vPort is reused, check
       statistics to be zero. */
    {
        unsigned int i;

        Log_FormattedMessage("TEST_MACSEC: Iterate over %u vPorts and %u SAs\n",
                            MaxvPorts, MaxSAs);
#ifdef TEST_MACSEC_USE_CFYE
        for (i=0; i < MaxvPorts; i++)
        {
            unsigned int vPort;
            SecY_Status_t SecY_Rc;
            /* Allocate a vPort, purpose is to validate that
               statistics of newly added vPort are cleared. */
            if (!test_macsec_CfyE_install(TestConf_p, TestRec_p,
                                          &vPortAdmin_p, &RuleAdmin_p,
                                          false, false, 0))
            {
                LOG_CRIT("TEST_MACSEC: Failed, test_macsec_CfyE_install()\n");
                return false;
            }

            CfyE_vPortIndex_Get(vPortAdmin_p->vPortHandle,
                                &vPort);
            Log_FormattedMessage("TEST_MACSEC: check zero statistics for vPort=%u\n",vPort);
            /* Read SecY and interface statistics, check they are zero.  */
#ifdef TEST_MACSEC_MODE_EGRESS
            if (!TestConf_p->fIngress)
            {
                SecY_SecY_Stat_E_t Stats;
                SecY_Ifc_Stat_E_t Stats2;
                SecY_Rc = SecY_SecY_Statistics_E_Get(TestConf_p->DeviceId,
                                                     vPort,
                                                     &Stats,
                                                     false);
                if (SecY_Rc !=SECY_STATUS_OK)
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, SecY_SecY_Statistics_E_Get=%d\n", SecY_Rc);
                }
                if (!test_macsec_all_counters_zero(&Stats, sizeof(Stats)/sizeof(uint32_t)))
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, not all SecY statistics are zero\n");
                }

                SecY_Rc = SecY_Ifc_Statistics_E_Get(TestConf_p->DeviceId,
                                                    vPort,
                                                    &Stats2,
                                                    false);
                if (SecY_Rc !=SECY_STATUS_OK)
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, SecY_Ifc_Statistics_E_Get=%d\n", SecY_Rc);
                }
                if (!test_macsec_all_counters_zero(&Stats2, sizeof(Stats2)/sizeof(uint32_t)))
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, not all Ifc statistics are zero\n");
                }
            }
#endif
#ifdef TEST_MACSEC_MODE_INGRESS
            if (TestConf_p->fIngress)
            {
                SecY_SecY_Stat_I_t Stats;
                SecY_Ifc_Stat_I_t Stats2;
                SecY_Rc = SecY_SecY_Statistics_I_Get(TestConf_p->DeviceId,
                                                     vPort,
                                                     &Stats,
                                                     false);
                if (SecY_Rc !=SECY_STATUS_OK)
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, SecY_SecY_Statistics_I_Get=%d\n", SecY_Rc);
                }
                if (!test_macsec_all_counters_zero(&Stats, sizeof(Stats)/sizeof(uint32_t)))
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, not all SecY statistics are zero\n");
                }

                SecY_Rc = SecY_Ifc_Statistics_I_Get(TestConf_p->DeviceId,
                                                     vPort,
                                                     &Stats2,
                                                     false);
                if (SecY_Rc !=SECY_STATUS_OK)
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, SecY_Ifc_Statistics_I_Get=%d\n", SecY_Rc);
                }
                if (!test_macsec_all_counters_zero(&Stats2, sizeof(Stats2)/sizeof(uint32_t)))
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, not all Ifc statistics are zero\n");
                }
            }
#endif
            /* Remove the vPort */
            if (!test_macsec_CfyE_uninstall(TestConf_p, TestRec_p,
                                            vPortAdmin_p, RuleAdmin_p,
                                            false))
            {
                fFailed = true;
            }
        }
#endif

        for (i=0; i < MaxSAs; i++)
        {
            unsigned int SAIndex;
            /* Add SA */
            SecY_SA_t *SA_Input_p;
            SecY_SA_t SA_Params;
            SecY_Status_t SecY_Rc;
            Test_Case_Transform_t * TC_Transform_p = TestRec_p->TransformData_p;
            Test_Transform_t TransformAdmin;
            SA_Input_p = &TC_Transform_p->SA_Data;
            ZEROINIT(SA_Params);
            ZEROINIT(TransformAdmin);

            /* Copy SA data */
            test_macsec_sa_copy(TestConf_p,
                                SA_Input_p,
                                TC_Transform_p,
                                &TransformAdmin,
                                &SA_Params);

            /* Add SA in driver, purpose is validating that
               SA Statistics are cleared. */
            SecY_Rc = SecY_SA_Add(TestConf_p->DeviceId,
                                  0,
                                  &TransformAdmin.TransformHandle,
                                  &SA_Params);
            if (SecY_Rc != SECY_STATUS_OK)
            {
                fFailed = true;
                LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Add()=%d\n", SecY_Rc);
            }

            SecY_SAIndex_Get(TransformAdmin.TransformHandle, &SAIndex, NULL);
            Log_FormattedMessage("TEST_MACSEC: check zero statistics for SA=%u\n",SAIndex);

            /* Read SA statistics, check they are zero. */
#ifdef TEST_MACSEC_MODE_EGRESS
            if (!TestConf_p->fIngress)
            {
                SecY_SA_Stat_E_t Stats;
                SecY_Rc = SecY_SA_Statistics_E_Get(TestConf_p->DeviceId,
                                                   TransformAdmin.TransformHandle,
                                                   &Stats,
                                                   false);
                if (SecY_Rc !=SECY_STATUS_OK)
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Statistics_E_Get=%d\n", SecY_Rc);
                    goto test_done2;
                }
                if (!test_macsec_all_counters_zero(&Stats, sizeof(Stats)/sizeof(uint32_t)))
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, not all SA statistics are zero\n");
                }
            }
#endif
#ifdef TEST_MACSEC_MODE_INGRESS
            if (TestConf_p->fIngress)
            {
                SecY_SA_Stat_I_t Stats;
                SecY_Rc = SecY_SA_Statistics_I_Get(TestConf_p->DeviceId,
                                                   TransformAdmin.TransformHandle,
                                                   &Stats,
                                                   false);
                if (SecY_Rc !=SECY_STATUS_OK)
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, SecY_SA_Statistics_I_Get=%d\n", SecY_Rc);
                    goto test_done2;
                }
                if (!test_macsec_all_counters_zero(&Stats, sizeof(Stats)/sizeof(uint32_t)))
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, not all SA statistics are zero\n");
                    goto test_done2;
                }
            }
#endif

            /* Remove the SA */
            SecY_SA_Remove(TestConf_p->DeviceId, TransformAdmin.TransformHandle);
            test_macsec_free(TransformAdmin.TransformRec_p);
        }
    }
test_done2:
    return !fFailed;
}


/*----------------------------------------------------------------------------
 * test_macsec_bypass_sa_macsec
 *
 * 1. Add a Bypass SA.
 * 2. Remove the Bypass SA
 * 3. Add a MACsec SA on the same vPort
 * 4. Process a packet with it.
 * 5. Remove the MACsec SA.
 */
static bool
test_macsec_bypass_sa_macsec(
    const Test_Case_ConfParams_t * const TestConf_p,
    const Test_Case_Record_t * TestRec_p)
{
    bool fSuccess = true;

    Test_Transform_t * FirstTransformAdmin_p = 0;
    Test_Transform_t * SecondTransformAdmin_p = 0;
    Test_Packet_t * PktAdmin_p = 0;

    if (TestRec_p->TransformCount < 2)
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, Not enough transforms\n");
        goto test_done;
    }

    /* Install the first SA, bypass SA on vPort 0 */
    if (!test_macsec_transform_install(TestConf_p, TestRec_p,
                                       0, 1,
                                       &FirstTransformAdmin_p))
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_transform_install()\n");
        goto test_done;
    }


    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: First bypass transform installed\n");
    }

#ifdef TEST_MACSEC_USE_WARMBOOT
    test_macsec_warmboot_shutdown();
    test_macsec_warmboot_restore();

    if (FirstTransformAdmin_p != NULL)
    {
        /* Restore SA handle after warm boot. */
        SecY_SAHandle_Get(TestConf_p->DeviceId,
                          FirstTransformAdmin_p->SAIndex,
                          &FirstTransformAdmin_p->TransformHandle);
    }
#endif
    /* Remove the first transform record. */
    if (!test_macsec_transform_uninstall(TestConf_p, 1, FirstTransformAdmin_p))
    {
        fSuccess = false;
        goto test_done;
    }

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: First bypass transform removed\n");
    }

    /* Install the second SA, bypass SA on vPort 0 */
    if (!test_macsec_transform_install(TestConf_p, TestRec_p,
                                       1, 1,
                                       &SecondTransformAdmin_p))
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_transform_install()\n");
        goto test_done;
    }

    if (TestConf_p->fVerbose)
    {
        Log_FormattedMessage("TEST_MACSEC: Second MACsec transform installed\n");
    }

    /* Allocate packet buffers */
    if (!test_macsec_pkt_alloc(TestRec_p, &PktAdmin_p))
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_pkt_alloc()\n");
        goto test_done;
    }
    /* Check packet processing for MACsec SA */
    if (!test_macsec_pkt_test(TestConf_p, TestRec_p, 0, 1, PktAdmin_p, 64))
    {
        fSuccess = false;
        LOG_CRIT("TEST_MACSEC: Failed, test_macsec_pkt_test()\n");
        goto test_done;
    }


test_done:
    /* Free packet buffers */
    if (!test_macsec_pkt_free(TestRec_p, PktAdmin_p))
    {
        fSuccess = false;
    }

    if (!test_macsec_transform_uninstall(TestConf_p, 1, SecondTransformAdmin_p))
    {
        fSuccess = false;
    }

    return fSuccess;
}


/*----------------------------------------------------------------------------
 * test_macsec_kat2
 */
void
test_macsec_kat2(
        unsigned int TestPass,
        const Test_Case_Record_t * TestRec_p,
        const unsigned int TestRecordCount)
{
    unsigned int i;
    unsigned int MaxvPorts, MaxSAs;

    if ((TestRec_p == NULL) || (TestRecordCount == 0))
    {
        LOG_CRIT("TEST_MACSEC: Warning, no KAT2 test record(s) provided\n");
        return;
    }

    for (i = 0; i < TestRecordCount; i++)
    {
        bool fFailed = false;
        Test_Case_ConfParams_t * TestConf_p = TestRec_p->ConfParams_p;

        if (TestConf_p == NULL)
        {
            LOG_CRIT("TEST_MACSEC: Failed, no configuration parameters (KAT2)\n");
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

        IDENTIFIER_NOT_USED_LOG_OFF(fFailed);

        /* Initialize the device */
        /* Note that the device statistics are initialized (reset) as well */
        if (!test_macsec_device_init(TestRec_p, NULL,  &MaxvPorts, &MaxSAs, NULL, NULL))
        {
            fFailed = true;
            LOG_CRIT("TEST_MACSEC: Failed, test_macsec_device_init()\n");
            goto test_case_done;
        }

        /* Check the input parameters */
        if ((TestRec_p->TransformData_p == NULL) ||
            (TestRec_p->PacketData_p == NULL))
        {
            fFailed = true;
            LOG_CRIT("TEST_MACSEC: Failed, invalid input\n");
            goto test_case_done;
        }

#ifdef TEST_MACSEC_MODE_INGRESS
        /* Perform ingress rekey test */
        if (TestConf_p->fIngress)
        {
            if (TestRec_p->SpecialOperation == TEST_MACSEC_OP_UPDATE_PN)
            {
                if (!test_macsec_ingress_updatepn_test(TestConf_p, TestRec_p, MaxSAs))
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, "
                             "test_macsec_ingress_updatepn_test()\n");
                    goto test_case_done;
                }
            }
            else if (TestRec_p->SpecialOperation == TEST_MACSEC_OP_REKEY)
            {
                if (!test_macsec_ingress_rekey_test(TestConf_p, TestRec_p))
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, "
                             "test_macsec_ingress_rekey_test()\n");
                    goto test_case_done;
                }
            }
            else if (TestRec_p->SpecialOperation == TEST_MACSEC_OP_REUSE_SA_VPORT)
            {
                if (!test_macsec_reuse_sa_vport_test(TestConf_p, TestRec_p, MaxvPorts, MaxSAs))
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, "
                             "test_macsec_reuse_sa_vport_test()\n");
                    goto test_case_done;
                }
            }
            else if (TestRec_p->SpecialOperation == TEST_MACSEC_OP_BYPASS_SA_MACSEC)
            {
                if (!test_macsec_bypass_sa_macsec(TestConf_p, TestRec_p))
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, "
                             "test_macsec_bypass_sa_macsec()\n");
                    goto test_case_done;
                }
            }
            else if (TestRec_p->SpecialOperation == TEST_MACSEC_OP_SA_RETIRE)
            {
                if (!test_macsec_ingress_sa_retire_test(TestConf_p, TestRec_p))
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, "
                             "test_macsec_ingress_sa_retire()\n");
                    goto test_case_done;
                }
            }
            else
            {
                    LOG_CRIT("TEST_MACSEC: Failed, "
                             "no operation specified for KAT2\n");
                    goto test_case_done;
            }
        }
#endif /* TEST_MACSEC_MODE_INGRESS */

#ifdef TEST_MACSEC_MODE_EGRESS
        /* Perform egress rekey test */
        if (!TestConf_p->fIngress)
        {
            if (TestRec_p->SpecialOperation == TEST_MACSEC_OP_REKEY_ADDSA)
            {
                if (!test_macsec_egress_rekey_addsa_test(TestConf_p,
                                                         TestRec_p))
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, "
                             "test_macsec_egress_addsa_rekey_test()\n");
                    goto test_case_done;
                }

            }
            else if (TestRec_p->SpecialOperation == TEST_MACSEC_OP_REUSE_SA_VPORT)
            {
                if (!test_macsec_reuse_sa_vport_test(TestConf_p, TestRec_p, MaxvPorts, MaxSAs))
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, "
                             "test_macsec_reuse_sa_vport_test()\n");
                    goto test_case_done;
                }
            }
            else if (TestRec_p->SpecialOperation == TEST_MACSEC_OP_BYPASS_SA_MACSEC)
            {
                if (!test_macsec_bypass_sa_macsec(TestConf_p, TestRec_p))
                {
                    fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, "
                             "test_macsec_bypass_sa_macsec()\n");
                    goto test_case_done;
                }
            }
            else if (!test_macsec_egress_rekey_test(TestConf_p,
                                               TestRec_p,
                                               TestRec_p->SpecialOperation == TEST_MACSEC_OP_REKEY_CHAINED))
            {
                fFailed = true;
                    LOG_CRIT("TEST_MACSEC: Failed, "
                             "test_macsec_egress_rekey_test()\n");
                    goto test_case_done;
            }
        }
#endif /* TEST_MACSEC_MODE_EGRESS */

        /* Perform vPort related Statistics Test if configured */
        if (!test_macsec_SecY_vPort_statistics(TestConf_p, TestRec_p, 0, NULL))
        {
            fFailed = true;
            LOG_CRIT("TEST_MACSEC: Failed, "
                     "test_macsec_SecY_vPort_statistics()\n");
            goto test_case_done;
        }

test_case_done:

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

NextTestCase:
        TestRec_p++;                    /* Next test case record */
    }
}


/* end of file test_case_kat2.c */
