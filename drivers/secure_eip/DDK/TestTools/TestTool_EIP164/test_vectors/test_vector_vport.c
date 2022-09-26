/* test_vector_vport.c
 *
 * Test Tool for CfyE and SecY API's
 * Implementation of the test vector for the test case vport data
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

#include "test_vector_vport.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Driver Framework Basic Defs API */
#include "basic_defs.h"

/* Test Case KAT 1 record format */
#include "test_record.h"

/* General test vectors and configuration data */
#include "test_vector_conf.h"
#include "test_vector_packet.h"


/*----------------------------------------------------------------------------
 * Local defines
 */
static SecY_SecY_Stat_t SecYStatTest_Egress_AllZero =
{
    .Egress =
    {
        /* Egress OutPktsTransformError */
        {0, 0},

        /* Egress OutPktsControl */
        {0, 0},

        /* Egress OutPktsUntagged */
        {0, 0},

        /* Egress OutPktsSANotInUse */
        {0, 0}
    }
};

static SecY_SecY_Stat_t SecYStatTest_Ingress_AllZero =
{
    .Ingress =
    {
        /* Ingress InPktsTransformError */
        {0, 0},

        /* Ingress InPktsControl */
        {0, 0},

        /* Ingress InPktsUntagged */
        {0, 0},

        /* Ingress InPktsNoTag */
        {0, 0},

        /* Ingress InPktsBadTag */
        {0, 0},

        /* Ingress InPktsNoSCI */
        {0, 0},

        /* Ingress InPktsUnknownSCI */
        {0, 0},

        /* Ingress InPktsTaggedCtrl */
        {0, 0},

        /* Ingress InPktsSANotInUSe */
        {0, 0}
    }
};


Test_Case_vPortStat_t vPortStat_Static_Bypass_Egress =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Egress_AllZero,

    /* IFC/IFC1 statistics */
    NULL
};

Test_Case_vPortStat_t vPortStat_Static_Bypass_Ingress =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_AllZero,

    /* IFC/IFC1 statistics */
    NULL
};

static SecY_Ifc_Stat_t IfcStatTest_SA_Drop_Egress =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {1, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {0, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {0, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {158, 0},
        /* Egress OutOctetsControlled */
        {0, 0},
        /* Egress OutOctetsCommon */
        {0, 0}
    }
};

Test_Case_vPortStat_t vPortStat_SA_Drop_Egress =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Egress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_SA_Drop_Egress
};


static SecY_Ifc_Stat_t IfcStatTest_SA_Drop_Ingress =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {1, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {0, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {0, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {158, 0},
        /* Ingress InOctetsControlled */
        {0, 0}
    }
};

Test_Case_vPortStat_t vPortStat_SA_Drop_Ingress =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_SA_Drop_Ingress
};


static SecY_Ifc_Stat_t IfcStatTest_SA_Bypass_Egress =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {1, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {0, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {0, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {135, 0},
        /* Egress OutOctetsControlled */
        {0, 0},
        /* Egress OutOctetsCommon */
        {135, 0}
    }
};

Test_Case_vPortStat_t vPortStat_SA_Bypass_Egress =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Egress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_SA_Bypass_Egress
};


static SecY_Ifc_Stat_t IfcStatTest_SA_Bypass_Ingress =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {1, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {0, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {0, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {135, 0},
        /* Ingress InOctetsControlled */
        {135, 0}
    }
};

Test_Case_vPortStat_t vPortStat_SA_Bypass_Ingress =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_SA_Bypass_Ingress
};

Test_Case_vPortStat_t vPortStat_Tag_Bypass_Egress =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Egress_AllZero,

    /* IFC/IFC1 statistics */
    NULL
};

Test_Case_vPortStat_t vPortStat_Tag_Bypass_Ingress =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_AllZero,

    /* IFC/IFC1 statistics */
    NULL
};

static SecY_Ifc_Stat_t IfcStatTest_Basic_Transform_Egress =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {0, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {1, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {0, 0},
        /* Egress OutOctetsControlled */
        {72, 0},
        /* Egress OutOctetsCommon */
        {104, 0}
    }
};

Test_Case_vPortStat_t vPortStat_Basic_Transform_Egress =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Egress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_Basic_Transform_Egress
};


static SecY_Ifc_Stat_t IfcStatTest_Basic_Transform_Ingress =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {1, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {0, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {1, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {104, 0},
        /* Ingress InOctetsControlled */
        {72, 0}
    }
};

Test_Case_vPortStat_t vPortStat_Basic_Transform_Ingress =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_Basic_Transform_Ingress
};


static SecY_Ifc_Stat_t IfcStatTest_Multi_SA_Transform_Ingress =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {3, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {0, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {3, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {281, 0},
        /* Ingress InOctetsControlled */
        {193, 0}
    }
};

Test_Case_vPortStat_t vPortStat_Multi_SA_Transform_Ingress =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_Multi_SA_Transform_Ingress
};


static SecY_Ifc_Stat_t IfcStatTest_Multi_SCI_AN_Transform =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {5, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {0, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {5, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {568, 0},
        /* Ingress InOctetsControlled */
        {408, 0}
    }
};

Test_Case_vPortStat_t vPortStat_Multi_SCI_AN_Transform =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_Multi_SCI_AN_Transform
};

static SecY_Ifc_Stat_t IfcStatTest_Multi_SA_Transform_Egress_1 =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {0, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {1, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {0, 0},
        /* Egress OutOctetsControlled */
        {72, 0},
        /* Egress OutOctetsCommon */
        {96, 0}
    }
};

static SecY_Ifc_Stat_t IfcStatTest_Multi_SA_Transform_Egress_2 =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {0, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {1, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {0, 0},
        /* Egress OutOctetsControlled */
        {60, 0},
        /* Egress OutOctetsCommon */
        {92, 0}
    }
};

static SecY_Ifc_Stat_t IfcStatTest_Multi_SA_Transform_Egress_3 =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {0, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {1, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {0, 0},
        /* Egress OutOctetsControlled */
        {61, 0},
        /* Egress OutOctetsCommon */
        {93, 0}
    }
};

#define VPORTSTAT_MULTI_SA_TRANSFORM_EGRESS_1                               \
{                                                                           \
    /* vPort */                                                             \
    0,                                                                      \
                                                                            \
    /* SecY statistics */                                                   \
    &SecYStatTest_Egress_AllZero,                                           \
                                                                            \
    /* IFC/IFC1 statistics */                                               \
    &IfcStatTest_Multi_SA_Transform_Egress_1                                \
}

#define VPORTSTAT_MULTI_SA_TRANSFORM_EGRESS_2                               \
{                                                                           \
    /* vPort */                                                             \
    1,                                                                      \
                                                                            \
    /* SecY statistics */                                                   \
    &SecYStatTest_Egress_AllZero,                                           \
                                                                            \
    /* IFC/IFC1 statistics */                                               \
    &IfcStatTest_Multi_SA_Transform_Egress_2                                \
}

#define VPORTSTAT_MULTI_SA_TRANSFORM_EGRESS_3                               \
{                                                                           \
    /* vPort */                                                             \
    2,                                                                      \
                                                                            \
    /* SecY statistics */                                                   \
    &SecYStatTest_Egress_AllZero,                                           \
                                                                            \
    /* IFC/IFC1 statistics */                                               \
    &IfcStatTest_Multi_SA_Transform_Egress_3                                \
}

Test_Case_vPortStat_t vPortStat_Multi_SA_Transform_Egress[] =
{
    VPORTSTAT_MULTI_SA_TRANSFORM_EGRESS_1,
    VPORTSTAT_MULTI_SA_TRANSFORM_EGRESS_2,
    VPORTSTAT_MULTI_SA_TRANSFORM_EGRESS_3
};

static SecY_Ifc_Stat_t IfcStatTest_CryptAuthenticateEncode_ECB =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {1, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {0, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {62, 0},
        /* Egress OutOctetsControlled */
        {0, 0},
        /* Egress OutOctetsCommon */
        {62, 0}
    }
};

Test_Case_vPortStat_t vPortStat_CryptAuthenticateEncode_ECB =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Egress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_CryptAuthenticateEncode_ECB
};


static SecY_Ifc_Stat_t IfcStatTest_CryptAuthenticateEncode_CTR =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {1, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {0, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {94, 0},
        /* Egress OutOctetsControlled */
        {0, 0},
        /* Egress OutOctetsCommon */
        {94, 0}
    }
};

Test_Case_vPortStat_t vPortStat_CryptAuthenticateEncode_CTR =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Egress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_CryptAuthenticateEncode_CTR
};


static SecY_Ifc_Stat_t IfcStatTest_CryptAuthenticateEncode_GMAC =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {1, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {0, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {174, 0},
        /* Egress OutOctetsControlled */
        {0, 0},
        /* Egress OutOctetsCommon */
        {174, 0}
    }
};

Test_Case_vPortStat_t vPortStat_CryptAuthenticateEncode_GMAC =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Egress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_CryptAuthenticateEncode_GMAC
};


static SecY_Ifc_Stat_t IfcStatTest_CryptAuthenticateEncode_GCM =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {1, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {0, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {174, 0},
        /* Egress OutOctetsControlled */
        {0, 0},
        /* Egress OutOctetsCommon */
        {174, 0}
    }
};

Test_Case_vPortStat_t vPortStat_CryptAuthenticateEncode_GCM =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Egress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_CryptAuthenticateEncode_GCM
};


static SecY_Ifc_Stat_t IfcStatTest_CryptAuthenticateEncode_GCM2 =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {1, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {0, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {126, 0},
        /* Egress OutOctetsControlled */
        {0, 0},
        /* Egress OutOctetsCommon */
        {126, 0}
    }
};

Test_Case_vPortStat_t vPortStat_CryptAuthenticateEncode_GCM2 =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Egress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_CryptAuthenticateEncode_GCM2
};


static SecY_Ifc_Stat_t IfcStatTest_CryptAuthenticateDecode_ECB =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {0, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {1, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {0, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {64, 0},
        /* Ingress InOctetsControlled */
        {64, 0}
    }
};

Test_Case_vPortStat_t vPortStat_CryptAuthenticateDecode_ECB =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_CryptAuthenticateDecode_ECB
};


static SecY_Ifc_Stat_t IfcStatTest_CryptAuthenticateDecode_CTR =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {0, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {1, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {0, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {96, 0},
        /* Ingress InOctetsControlled */
        {96, 0}
    }
};

Test_Case_vPortStat_t vPortStat_CryptAuthenticateDecode_CTR =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_CryptAuthenticateDecode_CTR
};


static SecY_Ifc_Stat_t IfcStatTest_CryptAuthenticateDecode_GMAC =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {0, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {1, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {0, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {176, 0},
        /* Ingress InOctetsControlled */
        {160, 0}
    }
};

Test_Case_vPortStat_t vPortStat_CryptAuthenticateDecode_GMAC =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_CryptAuthenticateDecode_GMAC
};


static SecY_Ifc_Stat_t IfcStatTest_CryptAuthenticateDecode_GCM =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {0, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {1, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {0, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {176, 0},
        /* Ingress InOctetsControlled */
        {160, 0}
    }
};

Test_Case_vPortStat_t vPortStat_CryptAuthenticateDecode_GCM =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_CryptAuthenticateDecode_GCM
};


static SecY_Ifc_Stat_t IfcStatTest_CryptAuthenticateDecode_GCM2 =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {0, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {1, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {0, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {128, 0},
        /* Ingress InOctetsControlled */
        {112, 0}
    }
};

Test_Case_vPortStat_t vPortStat_CryptAuthenticateDecode_GCM2 =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_CryptAuthenticateDecode_GCM2
};


static SecY_Ifc_Stat_t IfcStatTest_ExtPN_Egress =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {0, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {1, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {0, 0},
        /* Egress OutOctetsControlled */
        {60, 0},
        /* Egress OutOctetsCommon */
        {92, 0}
    }
};

Test_Case_vPortStat_t vPortStat_ExtPN_Egress =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Egress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_ExtPN_Egress
};


static SecY_Ifc_Stat_t IfcStatTest_ExtPN_Ingress =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {1, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {0, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {1, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {92, 0},
        /* Ingress InOctetsControlled */
        {60, 0}
    }
};

Test_Case_vPortStat_t vPortStat_ExtPN_Ingress =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_ExtPN_Ingress
};


static SecY_Ifc_Stat_t IfcStatTest_Rekey_Egress =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {0, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {2, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {0, 0},
        /* Egress OutOctetsControlled */
        {121, 0},
        /* Egress OutOctetsCommon */
        {185, 0}
    }
};

Test_Case_vPortStat_t vPortStat_Rekey_Egress =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Egress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_Rekey_Egress
};


static SecY_Ifc_Stat_t IfcStatTest_Rekey_EgressChained =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {0, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {2, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {0, 0},
        /* Egress OutOctetsControlled */
        {124, 0},
        /* Egress OutOctetsCommon */
        {172, 0}
    }
};

Test_Case_vPortStat_t vPortStat_Rekey_EgressChained =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Egress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_Rekey_EgressChained
};


static SecY_Ifc_Stat_t IfcStatTest_Rekey_EgressNonChained =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {0, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {2, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {0, 0},
        /* Egress OutOctetsControlled */
        {121, 0},
        /* Egress OutOctetsCommon */
        {185, 0}
    }
};

Test_Case_vPortStat_t vPortStat_Rekey_EgressNonChained =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Egress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_Rekey_EgressNonChained
};


static SecY_Ifc_Stat_t IfcStatTest_Rekey_Ingress =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {4, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {0, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {3, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {370, 0},
        /* Ingress InOctetsControlled */
        {182, 0}
    }
};

Test_Case_vPortStat_t vPortStat_Rekey_Ingress =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_Rekey_Ingress
};


static SecY_Ifc_Stat_t IfcStatTest_Rekey_Ingress_NoSCI =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {5, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {0, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {3, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {422, 0},
        /* Ingress InOctetsControlled */
        {181, 0}
    }
};

Test_Case_vPortStat_t vPortStat_Rekey_Ingress_NoSCI =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_Rekey_Ingress_NoSCI
};


static SecY_Ifc_Stat_t IfcStatTest_AllowEgressDataPackets_1 =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {0, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {1, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {0, 0},
        /* Egress OutOctetsControlled */
        {60, 0},
        /* Egress OutOctetsCommon */
        {92, 0}
    }
};

static SecY_Ifc_Stat_t IfcStatTest_AllowEgressDataPackets_2 =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {0, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},

        /* Egress OutPktsUnicastControlled */
        {1, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {0, 0},
        /* Egress OutOctetsControlled */
        {61, 0},
        /* Egress OutOctetsCommon */
        {0, 0}
    }
};

#define VPORTSTAT_ALLOWEGRESSDATAPACKETS_1                                  \
{                                                                           \
    /* vPort */                                                             \
    0,                                                                      \
                                                                            \
    /* SecY statistics */                                                   \
    &SecYStatTest_Egress_AllZero,                                           \
                                                                            \
    /* IFC/IFC1 statistics */                                               \
    &IfcStatTest_AllowEgressDataPackets_1                                   \
}

#define VPORTSTAT_ALLOWEGRESSDATAPACKETS_2                                  \
{                                                                           \
    /* vPort */                                                             \
    1,                                                                      \
                                                                            \
    /* SecY statistics */                                                   \
    &SecYStatTest_Egress_AllZero,                                           \
                                                                            \
    /* IFC/IFC1 statistics */                                               \
    &IfcStatTest_AllowEgressDataPackets_2                                   \
}

Test_Case_vPortStat_t vPortStat_AllowEgressDataPackets[] =
{
    VPORTSTAT_ALLOWEGRESSDATAPACKETS_1,
    VPORTSTAT_ALLOWEGRESSDATAPACKETS_2
};


static SecY_SecY_Stat_t SecYStatTest_EgressUntaggedPacket =
{
    .Egress =
    {
        /* Egress OutPktsTransformError */
        { 0, 0 },

        /* Egress OutPktsControl */
        { 0, 0 },

        /* Egress OutPktsUntagged */
        { 1, 0 },

        /* Egress OutPktsSANotInUse */
        { 0, 0 },
    }
};

static SecY_Ifc_Stat_t IfcStatTest_EgressUntaggedPacket =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {0, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {1, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {0, 0},
        /* Egress OutOctetsControlled */
        {120, 0},
        /* Egress OutOctetsCommon */
        {120, 0}
    }
};

Test_Case_vPortStat_t vPortStat_EgressUntaggedPacket =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_EgressUntaggedPacket,

    /* IFC/IFC1 statistics */
    &IfcStatTest_EgressUntaggedPacket
};


static SecY_SecY_Stat_t SecYStatTest_AllowIngressUntaggedPackets_1 =
{
    .Ingress =
    {
        /* Ingress InPktsTransformError */
        {0, 0},

        /* Ingress InPktsControl */
        {0, 0},

        /* Ingress InPktsUntagged */
        {1, 0},

        /* Ingress InPktsNoTag */
        {0, 0},

        /* Ingress InPktsBadTag */
        {0, 0},

        /* Ingress InPktsNoSCI */
        {0, 0},

        /* Ingress InPktsUnknownSCI */
        {0, 0},

        /* Ingress InPktsTaggedCtrl */
        {0, 0},

        /* Ingress InPktsSANotInUse */
        {0, 0}
    }
};

static SecY_SecY_Stat_t SecYStatTest_AllowIngressUntaggedPackets_2 =
{
    .Ingress =
    {
        /* Ingress InPktsTransformError */
        {0, 0},

        /* Ingress InPktsControl */
        {0, 0},

        /* Ingress InPktsUntagged */
        {0, 0},

        /* Ingress InPktsNoTag */
        {1, 0},

        /* Ingress InPktsBadTag */
        {0, 0},

        /* Ingress InPktsNoSCI */
        {0, 0},

        /* Ingress InPktsUnknownSCI */
        {0, 0},

        /* Ingress InPktsTaggedCtrl */
        {0, 0},

        /* Ingress InPktsSANotInUse */
        {0, 0}
    }
};

static SecY_Ifc_Stat_t IfcStatTest_AllowIngressUntaggedPackets_1 =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {1, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {0, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {1, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {60, 0},
        /* Ingress InOctetsControlled */
        {60, 0}
    }
};

static SecY_Ifc_Stat_t IfcStatTest_AllowIngressUntaggedPackets_2 =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {1, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {0, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {0, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {61, 0},
        /* Ingress InOctetsControlled */
        {0, 0}
    }
};

#define vPortStat_AllowIngressUntaggedPackets_1                             \
{                                                                           \
    /* vPort */                                                             \
    0,                                                                      \
                                                                            \
    /* SecY statistics */                                                   \
    &SecYStatTest_AllowIngressUntaggedPackets_1,                            \
                                                                            \
    /* IFC/IFC1 statistics */                                               \
    &IfcStatTest_AllowIngressUntaggedPackets_1                              \
}

#define vPortStat_AllowIngressUntaggedPackets_2                             \
{                                                                           \
    /* vPort */                                                             \
    1,                                                                      \
                                                                            \
    /* SecY statistics */                                                   \
    &SecYStatTest_AllowIngressUntaggedPackets_2,                            \
                                                                            \
    /* IFC/IFC1 statistics */                                               \
    &IfcStatTest_AllowIngressUntaggedPackets_2                              \
}

Test_Case_vPortStat_t vPortStat_AllowIngressUntaggedPackets[] =
{
    vPortStat_AllowIngressUntaggedPackets_1,
    vPortStat_AllowIngressUntaggedPackets_2
};


static SecY_SecY_Stat_t SecYStatTest_Ingress_BadTag =
{
    .Ingress =
    {
        /* Ingress InPktsTransformError */
        {0, 0},

        /* Ingress InPktsControl */
        {0, 0},

        /* Ingress InPktsUntagged */
        {0, 0},

        /* Ingress InPktsNoTag */
        {0, 0},

        /* Ingress InPktsBadTag */
        {1, 0},

        /* Ingress InPktsNoSCI */
        {0, 0},

        /* Ingress InPktsUnknownSCI */
        {0, 0},

        /* Ingress InPktsTaggedCtrl */
        {0, 0},

        /* Ingress InPktsSANotInUse */
        {0, 0}
    }
};

static SecY_Ifc_Stat_t IfcStatTest_Ingress_BadTag =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {1, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {0, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {0, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {104, 0},
        /* Ingress InOctetsControlled */
        {0, 0}
    }
};

Test_Case_vPortStat_t vPortStat_Ingress_BadTag =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_BadTag,

    /* IFC/IFC1 statistics */
    &IfcStatTest_Ingress_BadTag
};

static SecY_SecY_Stat_t SecYStatTest_Ingress_NoSCI =
{
    .Ingress =
    {
        /* Ingress InPktsTransformError */
        {0, 0},

        /* Ingress InPktsControl */
        {0, 0},

        /* Ingress InPktsUntagged */
        {0, 0},

        /* Ingress InPktsNoTag */
        {0, 0},

        /* Ingress InPktsBadTag */
        {0, 0},

        /* Ingress InPktsNoSCI */
        {1, 0},

        /* Ingress InPktsUnknownSCI */
        {0, 0},

        /* Ingress InPktsTaggedCtrl */
        {0, 0},

        /* Ingress InPktsSANotInUse */
        {0, 0}
    }
};

static SecY_Ifc_Stat_t IfcStatTest_Ingress_NoSCI =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {1, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {0, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {0, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {104, 0},
        /* Ingress InOctetsControlled */
        {0, 0}
    }
};

Test_Case_vPortStat_t vPortStat_Ingress_NoSCI =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_NoSCI,

    /* IFC/IFC1 statistics */
    &IfcStatTest_Ingress_NoSCI
};


static SecY_SecY_Stat_t SecYStatTest_Ingress_KaY_Packet =
{
    .Ingress =
    {
        /* Ingress InPktsTransformError */
        {0, 0},

        /* Ingress InPktsControl */
        {0, 0},

        /* Ingress InPktsUntagged */
        {0, 0},

        /* Ingress InPktsNoTag */
        {0, 0},

        /* Ingress InPktsBadTag */
        {0, 0},

        /* Ingress InPktsNoSCI */
        {0, 0},

        /* Ingress InPktsUnknownSCI */
        {0, 0},

        /* Ingress InPktsTaggedCtrl */
        {1, 0},

        /* Ingress InPktsSANotInUse */
        {0, 0},
    }
};

static SecY_Ifc_Stat_t IfcStatTest_Ingress_KaY_Packet =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {1, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {0, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {0, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {104, 0},
        /* Ingress InOctetsControlled */
        {0, 0}
    }
};

Test_Case_vPortStat_t vPortStat_Ingress_KaY_Packet =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_KaY_Packet,

    /* IFC/IFC1 statistics */
    &IfcStatTest_Ingress_KaY_Packet
};

static SecY_Ifc_Stat_t IfcStatTest_EgressMTUCheck =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {0, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {1, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {0, 0},
        /* Egress OutOctetsControlled */
        {300, 0},
        /* Egress OutOctetsCommon */
        {332, 0}
    }
};

Test_Case_vPortStat_t vPortStat_EgressMTUCheck =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Egress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_EgressMTUCheck
};


static SecY_Ifc_Stat_t IfcStatTest_EgressChannelReconfiguration_1 =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {0, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {3, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {0, 0},
        /* Egress OutOctetsControlled */
        {226, 0},
        /* Egress OutOctetsCommon */
        {322, 0}
    }
};

static SecY_Ifc_Stat_t IfcStatTest_EgressChannelReconfiguration_2 =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {0, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {2, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {0, 0},
        /* Egress OutOctetsControlled */
        {169, 0},
        /* Egress OutOctetsCommon */
        {233, 0}
    }
};

static SecY_Ifc_Stat_t IfcStatTest_EgressChannelReconfiguration_3 =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {0, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {3, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {0, 0},
        /* Egress OutOctetsControlled */
        {235, 0},
        /* Egress OutOctetsCommon */
        {331, 0}
    }
};

static SecY_Ifc_Stat_t IfcStatTest_EgressChannelReconfiguration_4 =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {0, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {1, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {0, 0},
        /* Egress OutOctetsControlled */
        {72, 0},
        /* Egress OutOctetsCommon */
        {104, 0}
    }
};

#define VPORTSTAT_EGRESSCHANNELRECONFIGURATION_1                            \
{                                                                           \
    /* vPort */                                                             \
    0,                                                                      \
                                                                            \
    /* SecY statistics */                                                   \
    &SecYStatTest_Egress_AllZero,                                           \
                                                                            \
    /* IFC/IFC1 statistics */                                               \
    &IfcStatTest_EgressChannelReconfiguration_1                             \
}

#define VPORTSTAT_EGRESSCHANNELRECONFIGURATION_2                            \
{                                                                           \
    /* vPort */                                                             \
    1,                                                                      \
                                                                            \
    /* SecY statistics */                                                   \
    &SecYStatTest_Egress_AllZero,                                           \
                                                                            \
    /* IFC/IFC1 statistics */                                               \
    &IfcStatTest_EgressChannelReconfiguration_2                             \
}

#define VPORTSTAT_EGRESSCHANNELRECONFIGURATION_3                            \
{                                                                           \
    /* vPort */                                                             \
    2,                                                                      \
                                                                            \
    /* SecY statistics */                                                   \
    &SecYStatTest_Egress_AllZero,                                           \
                                                                            \
    /* IFC/IFC1 statistics */                                               \
    &IfcStatTest_EgressChannelReconfiguration_3                             \
}

#define VPORTSTAT_EGRESSCHANNELRECONFIGURATION_4                            \
{                                                                           \
    /* vPort */                                                             \
    3,                                                                      \
                                                                            \
    /* SecY statistics */                                                   \
    &SecYStatTest_Egress_AllZero,                                           \
                                                                            \
    /* IFC/IFC1 statistics */                                               \
    &IfcStatTest_EgressChannelReconfiguration_4                             \
}

Test_Case_vPortStat_t vPortStat_EgressChannelReconfiguration[] =
{
    VPORTSTAT_EGRESSCHANNELRECONFIGURATION_1,
    VPORTSTAT_EGRESSCHANNELRECONFIGURATION_2,
    VPORTSTAT_EGRESSCHANNELRECONFIGURATION_3,
    VPORTSTAT_EGRESSCHANNELRECONFIGURATION_4
};


static SecY_Ifc_Stat_t IfcStatTest_IngressChannelReconfiguration_1 =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {3, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {0, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {3, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {322, 0},
        /* Ingress InOctetsControlled */
        {226, 0}
    }
};

static SecY_Ifc_Stat_t IfcStatTest_IngressChannelReconfiguration_2 =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {2, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {0, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {2, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {233, 0},
        /* Ingress InOctetsControlled */
        {169, 0}
    }
};

static SecY_Ifc_Stat_t IfcStatTest_IngressChannelReconfiguration_3 =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {3, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {0, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {3, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {331, 0},
        /* Ingress InOctetsControlled */
        {235, 0}
    }
};

static SecY_Ifc_Stat_t IfcStatTest_IngressChannelReconfiguration_4 =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {1, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {0, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {1, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {104, 0},
        /* Ingress InOctetsControlled */
        {72, 0}
    }
};

#define VPORTSTAT_INGRESSCHANNELRECONFIGURATION_1                           \
{                                                                           \
    /* vPort */                                                             \
    0,                                                                      \
                                                                            \
    /* SecY statistics */                                                   \
    &SecYStatTest_Ingress_AllZero,                                          \
                                                                            \
    /* IFC/IFC1 statistics */                                               \
    &IfcStatTest_IngressChannelReconfiguration_1                            \
}

#define VPORTSTAT_INGRESSCHANNELRECONFIGURATION_2                           \
{                                                                           \
    /* vPort */                                                             \
    1,                                                                      \
                                                                            \
    /* SecY statistics */                                                   \
    &SecYStatTest_Ingress_AllZero,                                          \
                                                                            \
    /* IFC/IFC1 statistics */                                               \
    &IfcStatTest_IngressChannelReconfiguration_2                            \
}

#define VPORTSTAT_INGRESSCHANNELRECONFIGURATION_3                           \
{                                                                           \
    /* vPort */                                                             \
    2,                                                                      \
                                                                            \
    /* SecY statistics */                                                   \
    &SecYStatTest_Ingress_AllZero,                                          \
                                                                            \
    /* IFC/IFC1 statistics */                                               \
    &IfcStatTest_IngressChannelReconfiguration_3                            \
}

#define VPORTSTAT_INGRESSCHANNELRECONFIGURATION_4                           \
{                                                                           \
    /* vPort */                                                             \
    3,                                                                      \
                                                                            \
    /* SecY statistics */                                                   \
    &SecYStatTest_Ingress_AllZero,                                          \
                                                                            \
    /* IFC/IFC1 statistics */                                               \
    &IfcStatTest_IngressChannelReconfiguration_4                            \
}

Test_Case_vPortStat_t vPortStat_IngressChannelReconfiguration[] =
{
    VPORTSTAT_INGRESSCHANNELRECONFIGURATION_1,
    VPORTSTAT_INGRESSCHANNELRECONFIGURATION_2,
    VPORTSTAT_INGRESSCHANNELRECONFIGURATION_3,
    VPORTSTAT_INGRESSCHANNELRECONFIGURATION_4
};


static SecY_Ifc_Stat_t IfcStatTest_Untagged_Egress_MACsec_bn =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {0, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {1, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {0, 0},
        /* Egress OutOctetsControlled */
        {61, 0},
        /* Egress OutOctetsCommon */
        {93, 0}
    }
};

Test_Case_vPortStat_t vPortStat_Untagged_Egress_MACsec_bn =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Egress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_Untagged_Egress_MACsec_bn
};


static SecY_Ifc_Stat_t IfcStatTest_Untagged_Egress_NoEnc =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {1, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {0, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {0, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {61, 0},
        /* Egress OutOctetsControlled */
        {0, 0},
        /* Egress OutOctetsCommon */
        {61, 0}
    }
};

Test_Case_vPortStat_t vPortStat_Untagged_Egress_NoEnc =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Egress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_Untagged_Egress_NoEnc
};

static SecY_Ifc_Stat_t IfcStatTest_Ingress_MACsec_bn =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {1, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {0, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {1, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {93, 0},
        /* Ingress InOctetsControlled */
        {61, 0}
    }
};

Test_Case_vPortStat_t vPortStat_Untagged_Ingress_MACsec_bn =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_Ingress_MACsec_bn
};

static SecY_Ifc_Stat_t IfcStatTest_Untagged_Ingress_NoEnc =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {1, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {0, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {0, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {61, 0},
        /* Ingress InOctetsControlled */
        {61, 0}
    }
};

Test_Case_vPortStat_t vPortStat_Untagged_Ingress_NoEnc =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_Untagged_Ingress_NoEnc
};

static SecY_Ifc_Stat_t IfcStatTest_VLAN_1Q_Egress_MACsec_O1 =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {0, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {1, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {0, 0},
        /* Egress OutOctetsControlled */
        {60, 0},
        /* Egress OutOctetsCommon */
        {92, 0}
    }
};

Test_Case_vPortStat_t vPortStat_VLAN_1Q_Egress_MACsec_O1 =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Egress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_VLAN_1Q_Egress_MACsec_O1
};

static SecY_Ifc_Stat_t IfcStatTest_VLAN_1Q_Egress_MACsec_O2 =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {0, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {1, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {0, 0},
        /* Egress OutOctetsControlled */
        {56, 0},
        /* Egress OutOctetsCommon */
        {92, 0}
    }
};

Test_Case_vPortStat_t vPortStat_VLAN_1Q_Egress_MACsec_O2 =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Egress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_VLAN_1Q_Egress_MACsec_O2
};


static SecY_Ifc_Stat_t IfcStatTest_VLAN_1Q_Ingress_MACsec_O1 =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {1, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {0, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {1, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {92, 0},
        /* Ingress InOctetsControlled */
        {60, 0}
    }
};

Test_Case_vPortStat_t vPortStat_VLAN_1Q_Ingress_MACsec_O1 =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_VLAN_1Q_Ingress_MACsec_O1
};

static SecY_Ifc_Stat_t IfcStatTest_VLAN_1Q_Ingress_MACsec_O2 =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {1, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {0, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {1, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {92, 0},
        /* Ingress InOctetsControlled */
        {56, 0}
    }
};

Test_Case_vPortStat_t vPortStat_VLAN_1Q_Ingress_MACsec_O2 =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_VLAN_1Q_Ingress_MACsec_O2
};


static SecY_Ifc_Stat_t IfcStatTest_VLAN_QinQ_Egress_MACsec_O3 =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {0, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {1, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {0, 0},
        /* Egress OutOctetsControlled */
        {54, 0},
        /* Egress OutOctetsCommon */
        {94, 0}
    }
};

Test_Case_vPortStat_t vPortStat_VLAN_QinQ_Egress_MACsec_O3 =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Egress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_VLAN_QinQ_Egress_MACsec_O3
};

static SecY_Ifc_Stat_t IfcStatTest_VLAN_QinQ_Ingress_MACsec_O3 =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {1, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {0, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {1, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {94, 0},
        /* Ingress InOctetsControlled */
        {54, 0}
    }
};

Test_Case_vPortStat_t vPortStat_VLAN_QinQ_Ingress_MACsec_O3 =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_VLAN_QinQ_Ingress_MACsec_O3
};

static SecY_Ifc_Stat_t IfcStatTest_VLAN_QinQinQ_Egress_MACsec_O4 =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {0, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {1, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {0, 0},
        /* Egress OutOctetsControlled */
        {54, 0},
        /* Egress OutOctetsCommon */
        {98, 0}
    }
};

Test_Case_vPortStat_t vPortStat_VLAN_QinQinQ_Egress_MACsec_O4 =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Egress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_VLAN_QinQinQ_Egress_MACsec_O4
};

static SecY_Ifc_Stat_t IfcStatTest_VLAN_QinQinQ_Ingress_MACsec_O4 =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {1, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {0, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {1, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {98, 0},
        /* Ingress InOctetsControlled */
        {54, 0}
    }
};

Test_Case_vPortStat_t vPortStat_VLAN_QinQinQ_Ingress_MACsec_O4 =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_VLAN_QinQinQ_Ingress_MACsec_O4
};

static SecY_SecY_Stat_t SecYStatTest_CtrlPacket_PriEgress =
{
    .Egress =
    {
        /* Egress OutPktsTransformError */
        {0, 0},

        /* Egress OutPktsControl */
        {7, 0},

        /* Egress OutPktsUntagged */
        {0, 0},

        /* Egress OutPktsSANotInUse */
        {0, 0}
    }
};

static SecY_Ifc_Stat_t IfcStatTest_CtrlPacket_PriEgress =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {5, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {2, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {1, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {537, 0},
        /* Egress OutOctetsControlled */
        {61, 0},
        /* Egress OutOctetsCommon */
        {630, 0}
    }
};

Test_Case_vPortStat_t vPortStat_CtrlPacket_PriEgress =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_CtrlPacket_PriEgress,

    /* IFC/IFC1 statistics */
    &IfcStatTest_CtrlPacket_PriEgress
};

static SecY_SecY_Stat_t SecYStatTest_CtrlPacket_PriIngress =
{
    .Ingress =
    {
        /* Ingress InPktsTransformError */
        {0, 0},

        /* Ingress InPktsControl */
        {7, 0},

        /* Ingress InPktsUntagged */
        {0, 0},

        /* Ingress InPktsNoTag */
        {0, 0},

        /* Ingress InPktsBadTag */
        {0, 0},

        /* Ingress InPktsNoSCI */
        {0, 0},

        /* Ingress InPktsUnknownSCI */
        {0, 0},

        /* Ingress InPktsTaggedCtrl */
        {0, 0},

        /* Ingress InPktsSANotInUse */
        {0, 0}
    }
};

static SecY_Ifc_Stat_t IfcStatTest_CtrlPacket_PriIngress =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {6, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {2, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {1, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {630, 0},
        /* Ingress InOctetsControlled */
        {61, 0}
    }
};

Test_Case_vPortStat_t vPortStat_CtrlPacket_PriIngress =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_CtrlPacket_PriIngress,

    /* IFC/IFC1 statistics */
    &IfcStatTest_CtrlPacket_PriIngress
};

static SecY_Ifc_Stat_t IfcStatTest_CfyELimitsEgress =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {0, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {1, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
         /* Egress OutOctetsUncontrolled */
        {0, 0},
        /* Egress OutOctetsControlled */
        {56, 0},
        /* Egress OutOctetsCommon */
        {92, 0}
    }
};

Test_Case_vPortStat_t vPortStat_CfyELimitsEgress =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Egress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_CfyELimitsEgress
};

static SecY_Ifc_Stat_t IfcStatTest_CfyELimitsIngress =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {1, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {0, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {1, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {92, 0},
        /* Ingress InOctetsControlled */
        {56, 0}
    }
};

Test_Case_vPortStat_t vPortStat_CfyELimitsIngress =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_CfyELimitsIngress
};

#if defined(TEST_MACSEC_VXLAN_ENABLE)
static SecY_Ifc_Stat_t IfcStatTest_VxLAN_IPv6_Egress_MACsec =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {0, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {0, 0},
        /* Egress OutPktsMulticastControlled */
        {1, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {0, 0},
        /* Egress OutOctetsControlled */
        {312, 0},
        /* Egress OutOctetsCommon */
        {410, 0}
    }
};

Test_Case_vPortStat_t vPortStat_VxLAN_IPv6_Egress_MACsec =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Egress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_VxLAN_IPv6_Egress_MACsec,
};

static SecY_Ifc_Stat_t IfcStatTest_VxLAN_IPv4_Egress_MACsec =
{
    .Egress =
    {
        /* Egress OutPktsUnicastUncontrolled */
        {0, 0},
        /* Egress OutPktsMulticastUncontrolled */
        {0, 0},
        /* Egress OutPktsBroadcastUncontrolled */
        {0, 0},
        /* Egress OutPktsUnicastControlled */
        {1, 0},
        /* Egress OutPktsMulticastControlled */
        {0, 0},
        /* Egress OutPktsBroadcastControlled */
        {0, 0},
        /* Egress OutOctetsUncontrolled */
        {0, 0},
        /* Egress OutOctetsControlled */
        {301, 0},
        /* Egress OutOctetsCommon */
        {387, 0}
    }
};


Test_Case_vPortStat_t vPortStat_VxLAN_IPv4_Egress_MACsec =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Egress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_VxLAN_IPv4_Egress_MACsec,
};

static SecY_Ifc_Stat_t IfcStatTest_VxLAN_IPv6_Ingress_MACsec =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {0, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {1, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {0, 0},
        /* Ingress InPktsMulticastControlled */
        {1, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {410, 0},
        /* Ingress InOctetsControlled */
        {312, 0}
    }
};

Test_Case_vPortStat_t vPortStat_VxLAN_IPv6_Ingress_MACsec =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_VxLAN_IPv6_Ingress_MACsec,
};

static SecY_Ifc_Stat_t IfcStatTest_VxLAN_IPv4_Ingress_MACsec =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {1, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {0, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {1, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {387, 0},
        /* Ingress InOctetsControlled */
        {301, 0}
    }
};

Test_Case_vPortStat_t vPortStat_VxLAN_IPv4_Ingress_MACsec =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_VxLAN_IPv4_Ingress_MACsec,
};
#endif

#if defined(TEST_IPSEC_ENABLE)
static SecY_Ifc_Stat_t IfcStatTest_CfyELimitsIPSecIngressMPLS =
{
    .Ingress =
    {
        /* Ingress InPktsUnicastUncontrolled */
        {1, 0},
        /* Ingress InPktsMulticastUncontrolled */
        {0, 0},
        /* Ingress InPktsBroadcastUncontrolled */
        {0, 0},
        /* Ingress InPktsUnicastControlled */
        {1, 0},
        /* Ingress InPktsMulticastControlled */
        {0, 0},
        /* Ingress InPktsBroadcastControlled */
        {0, 0},
        /* Ingress InOctetsUncontrolled */
        {422, 0},
        /* Ingress InOctetsControlled */
        {388, 0}
    }
};

Test_Case_vPortStat_t vPortStat_CfyELimitsIPsecIngressMPLS =
{
    /* vPort */
    0,

    /* SecY statistics */
    &SecYStatTest_Ingress_AllZero,

    /* IFC/IFC1 statistics */
    &IfcStatTest_CfyELimitsIPSecIngressMPLS,
};
#endif

/* end of file test_vector_vport.c */
