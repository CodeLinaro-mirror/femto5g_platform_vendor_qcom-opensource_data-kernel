/* test_vector_kat2.h
 *
 * Test Tool for CfyE and SecY API's
 * Test vectors for the KAT2 test
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

#ifndef TEST_VECTOR_KAT_2_H_
#define TEST_VECTOR_KAT_2_H_

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Default configuration */
#include "c_test_macsec.h"

/* Test Case KAT 2 test vectors */
#include "test_vector_kat2_rekey.h"

#include "test_vector_kat2_rekey2.h"
#include "test_vector_kat2_updatepn.h"
#include "test_vector_kat2_bypass_macsec.h"
#include "test_vector_kat2_sa_retire.h"

#ifdef TEST_MACSEC_USE_CFYE
#include "test_vector_kat2_cfye.h"
#endif


/*----------------------------------------------------------------------------
 * Local variables
 */

static Test_Case_Record_t TCV_KAT_2 [] =
{
#ifdef TEST_MACSEC_MODE_EGRESS
    TEST_MACSEC_REC_PKT_REKEY_EGRESS,
    TEST_MACSEC_REC_PKT_REKEY_EGRESS_CHAIN,
    TEST_MACSEC_REC_PKT_REKEY_EGRESS_NON_CHAIN,
    TEST_MACSEC_REC_EGRESS_BYPASS_MACSEC,
#ifdef TEST_MACSEC_USE_CFYE
    TEST_MACSEC_REC_PKT_EGRESS_REUSE_SA_VPORT,
#endif
#endif /* TEST_MACSEC_MODE_EGRESS */

#ifdef TEST_MACSEC_MODE_INGRESS
    TEST_MACSEC_REC_PKT_REKEY_INGRESS,
    TEST_MACSEC_REC_PKT_REKEY_INGRESS_NOSCI,
    TEST_MACSEC_REC_PKT_UPDATEPN32_INGRESS,
    TEST_MACSEC_REC_PKT_UPDATEPN64_INGRESS,
    TEST_MACSEC_REC_INGRESS_BYPASS_MACSEC,
    TEST_MACSEC_REC_INGRESS_SA_RETIRE,
#ifdef TEST_MACSEC_USE_CFYE
    TEST_MACSEC_REC_PKT_INGRESS_REUSE_SA_VPORT,
#endif
#endif /* TEST_MACSEC_MODE_INGRESS */
};


#endif /* TEST_VECTOR_KAT_2_H_ */


/* end of file test_vector_kat2.h */
