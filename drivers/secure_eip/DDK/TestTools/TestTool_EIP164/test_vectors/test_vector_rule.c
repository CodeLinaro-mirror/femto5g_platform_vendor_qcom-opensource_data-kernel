/* test_vector_rule.c
 *
 * Implementation of the test vectors for the test case rule data
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

#include "test_vector_rule.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Test Case record format */
#include "test_record.h"

/* General test vectors and configuration data */
#include "test_vector_conf.h"
#include "test_vector_packet.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

static SecY_Channel_Rule_SecTAG_t SecTag_General_Rule =
{
    /* fCompEType */
    true,

    /* fCheckV */
    true,

    /* fCheckKay */
    true,

    /* fCheckCE */
    true,

    /* fCheckSC, */
    true,

    /* fCheckSL */
    true,

    /* fCheckPN */
    true,

    /* fCheckSLExt */
    false,

    /* EtherType */
    0x88E5
};

/* For ingress ExtPN the CheckPN test must be disabled, zero is a valid packet */
/* number. */
SecY_Channel_Rule_SecTAG_t SecTag_Rules_ExtPN =
{
    /* fCompEType */
    true,

    /* fCheckV */
    true,

    /* fCheckKay */
    true,

    /* fCheckCE */
    true,

    /* fCheckSC, */
    true,

    /* fCheckSL */
    true,

    /* fCheckPN */
    false,

    /* fCheckSLExt */
    false,

    /* EtherType */
    0x88E5
};


Test_Case_Channel_Rules_t ChannelRules_Egress_Default[] =
{
    { 0, &SecTag_General_Rule },
    { 1, &SecTag_General_Rule },
    { 2, &SecTag_General_Rule },
    { 3, &SecTag_General_Rule }
};

Test_Case_Channel_Rules_t ChannelRules_Ingress_Default[] =
{
    { 0, &SecTag_General_Rule },
    { 1, &SecTag_General_Rule },
    { 2, &SecTag_General_Rule },
    { 3, &SecTag_General_Rule }
};


Test_Case_Channel_Rules_t ChannelRules_Ingress_ExtPN[] =
{
    { 0, &SecTag_Rules_ExtPN },
    { 1, &SecTag_Rules_ExtPN },
    { 2, &SecTag_General_Rule },
    { 3, &SecTag_General_Rule }
};


SecY_SC_Rule_MTUCheck_t Rule_MTU_Check_Drop =
{
    /* Maximum packet size (in bytes) allowed for packets */
    256,

    /* Drop (by corrupting the CRC) all packets that are longer */
    true
};

SecY_SC_Rule_MTUCheck_t Rule_MTU_Check_Pass =
{
    /* Maximum packet size (in bytes) allowed for packets */
    256,

    /* Pass on all packets that are longer */
    false
};


Test_Case_SC_Rules_t SCRules_Egress_MTU_Check_Drop[] =
{
    { 0, &Rule_MTU_Check_Drop}
};

Test_Case_SC_Rules_t SCRules_Egress_MTU_Check_Pass[] =
{
    { 0, &Rule_MTU_Check_Pass}
};


/* end of file test_vector_rule.c */
