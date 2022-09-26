/* test_record_kat1.c
 *
 * Test Tool for CfyE and SecY API's
 * Test record definition for KAT1 test
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

#include "test_record_kat1.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

#include "test_support.h"

/* Driver Framework Basic Defs API */
#include "basic_defs.h"

/* Driver Framework CLib aAbstraction API */
#include "clib.h"                  /* ZEROINIT() */

/* Test configuration and vectors for the Packet Sanity Check Fail test case */
#include "test_vector_kat1.h"      /* TCV_KAT_1 */


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

#define TEST_MACSEC_SRC_PKT_TOOL_ALLOCATED      BIT_0


/*----------------------------------------------------------------------------
 * Local variables
 */
struct PktAllocEntry
{
    struct PktAllocEntry * pNext;
    uint8_t PacketData[4];
};

static struct PktAllocEntry * gl_pPktAllocAdmin = NULL;

/*----------------------------------------------------------------------------
 * test_macsec_kat1_rec_init
 */
void
test_macsec_kat1_rec_init(
        Test_Case_Record_t ** TestRec_pp,
        unsigned int * const TestRecordCount_p)
{
    unsigned int i, j, count;
    Test_Case_Record_t * TestRec_p = TCV_KAT_1;

    /* Set the pre-set test case conf params and vectors in the record */
    count = sizeof(TCV_KAT_1) / sizeof(Test_Case_Record_t);

    *TestRecordCount_p = count;
    *TestRec_pp = TestRec_p;

    /* Override the pre-set test case conf params and vectors in the record */
    for (i = 0; i < count; i++)
    {
        Test_Case_Packet_t * Pkt_p = TestRec_p->PacketData_p;

        if (Pkt_p != 0)
        {
            for (j = 0; j < TestRec_p->PacketCount; j++)
            {
                if ((Pkt_p->SrcPkt_p == NULL) &&
                    (Pkt_p->SrcPkt_ByteCount != 0))
                {
                    /* Create source packet data */
                    struct PktAllocEntry * PktEntry_p;

                    PktEntry_p = test_macsec_malloc(Pkt_p->SrcPkt_ByteCount +
                                                    sizeof(struct PktAllocEntry));
                    if (PktEntry_p != NULL)
                    {
                        /* Assign packet and place entry in the administration */
                        PktEntry_p->pNext = gl_pPktAllocAdmin;
                        gl_pPktAllocAdmin = PktEntry_p;
                        Pkt_p->SrcPkt_p = PktEntry_p->PacketData;

                        /* Generate a valid Ethernet frame */
                        test_macsec_gen_frame(Pkt_p->SrcPkt_p,
                                              Pkt_p->SrcPkt_ByteCount,
                                              Pkt_p->MAC_DA_p,
                                              Pkt_p->MAC_SA_p,
                                              Pkt_p->EtherType);
                    }
                }

                Pkt_p++;
            }
        }

        TestRec_p++;
    }
}


/*----------------------------------------------------------------------------
 * test_macsec_kat1_rec_uninit
 */
void
test_macsec_kat1_rec_uninit(
        Test_Case_Record_t * TestRec_p,
        const unsigned int TestRecordCount)
{
    IDENTIFIER_NOT_USED(TestRec_p);
    IDENTIFIER_NOT_USED(TestRecordCount);

    while (gl_pPktAllocAdmin != NULL)
    {
        struct PktAllocEntry * PktEntry_p = gl_pPktAllocAdmin->pNext;

        test_macsec_free(gl_pPktAllocAdmin);

        gl_pPktAllocAdmin = PktEntry_p;
    }
}


/* end of file test_record_kat1.c */
