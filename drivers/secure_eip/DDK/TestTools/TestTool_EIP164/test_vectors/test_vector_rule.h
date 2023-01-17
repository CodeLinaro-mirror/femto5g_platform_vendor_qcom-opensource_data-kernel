/* test_vector_rule.h
 *
 * Test vectors for the test case rule data
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

#ifndef TEST_VECTOR_RULE_H_
#define TEST_VECTOR_RULE_H_

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Test Case record format */
#include "test_record.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

extern Test_Case_Channel_Rules_t ChannelRules_Egress_Default[];
extern Test_Case_Channel_Rules_t ChannelRules_Ingress_Default[];
extern Test_Case_Channel_Rules_t ChannelRules_Ingress_ExtPN[];

extern Test_Case_SC_Rules_t SCRules_Egress_MTU_Check_Drop[];
extern Test_Case_SC_Rules_t SCRules_Egress_MTU_Check_Pass[];

#endif /* TEST_VECTOR_RULE_H_ */


/* end of file test_vector_rule.h */
