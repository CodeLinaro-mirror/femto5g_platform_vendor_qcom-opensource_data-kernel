/* test_vector_kat3.h
 *
 * Test Tool for CfyE and SecY API's
 * Test vectors for the KAT3 test
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

#ifndef TEST_VECTOR_KAT_3_H_
#define TEST_VECTOR_KAT_3_H_

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Test Case KAT 3 test vectors */
#include "test_vector_kat3_basic_transform.h"
#include "test_vector_kat3_cfye.h"

/*----------------------------------------------------------------------------
 * Local variables
 */

static Test_Case_Record_t TCV_KAT_3 [] =
{
#ifdef TEST_MACSEC_MODE_EGRESS
    TEST_MACSEC_REC_PKT_BASIC_TRANSFORM_EGRESS_MAX_SA,
    TEST_MACSEC_REC_PKT_BASIC_TRANSFORM_EGRESS_REDUCED_SA,

#ifdef TEST_MACSEC_USE_CFYE
    TEST_MACSEC_REC_CFYE_LIMITS_EGRESS,
    TEST_MACSEC_REC_CFYE_REDUCED_LIMITS_EGRESS,
    TEST_MACSEC_REC_CFYE_REDUCED_LIMITS_INDEX_EGRESS,
#endif /* TEST_MACSEC_USE_CFYE */
#endif /* TEST_MACSEC_MODE_EGRESS */

#ifdef TEST_MACSEC_MODE_INGRESS
    TEST_MACSEC_REC_PKT_BASIC_TRANSFORM_INGRESS_MAX_SA,
    TEST_MACSEC_REC_PKT_BASIC_TRANSFORM_INGRESS_REDUCED_SA,

#ifdef TEST_MACSEC_USE_CFYE
    TEST_MACSEC_REC_CFYE_LIMITS_INGRESS,
    TEST_MACSEC_REC_CFYE_REDUCED_LIMITS_INGRESS,
    TEST_MACSEC_REC_CFYE_REDUCED_LIMITS_INDEX_INGRESS,
#endif /* TEST_MACSEC_USE_CFYE */
#endif /* TEST_MACSEC_MODE_INGRESS */
};


#endif /* TEST_VECTOR_KAT_3_H_ */


/* end of file test_vector_kat3.h */
