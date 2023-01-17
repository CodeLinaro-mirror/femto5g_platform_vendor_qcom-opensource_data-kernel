/* test_vector_conf.h
 *
 * Test Tool for CfyE and SecY API's
 * Test vectors test case configuration and general data
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

#ifndef TEST_VECTOR_CONF_H_
#define TEST_VECTOR_CONF_H_

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

/* Test case configuration data */
extern Test_Case_ConfParams_t ConfParamsEgressDefaultBypass;
extern Test_Case_ConfParams_t ConfParamsEgressInterruptsBypass;
extern Test_Case_ConfParams_t ConfParamsEgressDefaultDropInternal;
extern Test_Case_ConfParams_t ConfParamsEgressDefaultDropInternalKAT5;
extern Test_Case_ConfParams_t ConfParamsEgressDefaultDropCRC;
extern Test_Case_ConfParams_t ConfParamsEgressBasicTransform;
extern Test_Case_ConfParams_t ConfParamsEgressBasicTransformKAT5;
extern Test_Case_ConfParams_t ConfParamsEgressMultiTransform;
extern Test_Case_ConfParams_t ConfParamsEgressLowLatencyBypass;
extern Test_Case_ConfParams_t ConfParamsEgressExtPN;
extern Test_Case_ConfParams_t ConfParamsEgressReducedDropInternal;
extern Test_Case_ConfParams_t ConfParamsEgressReducedDropInternalIndex;
extern Test_Case_ConfParams_t ConfParamsEgressReducedDropCRC;

extern Test_Case_ConfParams_t ConfParamsIngressDefaultBypass;
extern Test_Case_ConfParams_t ConfParamsIngressDefaultDropInternal;
extern Test_Case_ConfParams_t ConfParamsIngressDefaultDropInternalKAT5;
extern Test_Case_ConfParams_t ConfParamsIngressDefaultDropCRC;
extern Test_Case_ConfParams_t ConfParamsIngressBasicTransform;
extern Test_Case_ConfParams_t ConfParamsIngressBasicTransformKAT5;
extern Test_Case_ConfParams_t ConfParamsIngressMultiTransform;
extern Test_Case_ConfParams_t ConfParamsIngressLowLatencyBypass;
extern Test_Case_ConfParams_t ConfParamsIngressReducedDropInternal;
extern Test_Case_ConfParams_t ConfParamsIngressReducedDropInternalIndex;
extern Test_Case_ConfParams_t ConfParamsIngressReducedDropCRC;

extern Test_Case_ConfParams_t ConfParamsCryptAuthenticateEncode;
extern Test_Case_ConfParams_t ConfParamsCryptAuthenticateDecode;

extern Test_Case_ConfParams_t ConfParamsEgress_Test;

#if defined(TEST_IPSEC_ENABLE)
extern Test_Case_ConfParams_t ConfParamsIPsecEgressBasicTransform;
extern Test_Case_ConfParams_t ConfParamsIPsecEgressMPLS;
extern Test_Case_ConfParams_t ConfParamsIPsecEgressVLAN;
extern Test_Case_ConfParams_t ConfParamsIPsecIngressBasicTransform;
extern Test_Case_ConfParams_t ConfParamsIPsecIngressVLANTransform;
extern Test_Case_ConfParams_t ConfParamsIPsecEgressMultiTransform;
extern Test_Case_ConfParams_t ConfParamsIPsecIngressMultiTransform;
#endif

#endif /* TEST_VECTOR_CONF_H_ */


/* end of file test_vector_conf.h */
