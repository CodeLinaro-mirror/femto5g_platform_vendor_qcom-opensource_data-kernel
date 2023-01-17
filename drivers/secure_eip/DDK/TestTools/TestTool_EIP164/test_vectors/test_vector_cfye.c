/* test_vector_cfye.c
 *
 * Implementation of the test vectors for the test case CfyE vport and device
 * data
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

#include "test_vector_cfye.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Default configuration */
#include "c_test_macsec.h"

/* Test Case record format */
#include "test_record.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

static Test_Case_CfyE_Rule_t CfyE_Rule_Untagged_MACsec_bn =
{
    /* fUpdate */
    false,

    /* Rule ID */
    0,

    /* Rule definition */
    {
        /* Key */
        CfyE_Rule_KeyMask_Other(0, 0, 0),

        /* KeyMask */
        CfyE_Rule_KeyMask_Raw(0x0, 0x00, CFYE_RULE_CHANNEL_ID_MASK, 0, 0),

        /* Data */
        {
            /* MAC address, least significant bytes (3..0) */
            0x13D5C584,

            /* MAC address, most significant bytes (5, 4) */
            0x0000AAD2,

            /* Packet data (EtherType, VLAN tag) */
            0x00000000,
            0x00000000,
            0x00000000
        },

        /* DataMask */
        {
            0xFFFFFFFF,
            0x0000FFFF,
            0x00000000,
            0x00000000,
            0x00000000
        },

        /* Policy */
        Common_CfyE_Rule_Policy(0, 1, 0, false, false)
    }
};

static Test_Case_CfyE_Rule_t CfyE_Rule_MultipleChannels_UntaggedMACsec[] =
{
    {
        /* fUpdate */
        false,

        /* Rule ID */
        0,

        /* Rule definition */
        {
            /* Key */
            CfyE_Rule_KeyMask_Other(0, 0, 0),

            /* KeyMask */
            CfyE_Rule_KeyMask_Raw(0x0, 0x00, CFYE_RULE_CHANNEL_ID_MASK, 0, 0),

            /* Data */
            {
                /* MAC address, least significant bytes (3..0) */
                0x13D5C584,
                /* MAC address, most significant bytes (5, 4) */
                0x0000AAD2,
                /* Packet data (EtherType, VLAN tag) */
                0x00000000,
                0x00000000
            },

            /* DataMask */
            {
                0xFFFFFFFF,
                0x0000FFFF,
                0x00000000,
                0x00000000
            },

            /* Policy */
            Common_CfyE_Rule_Policy(0, 1, 0, false, false)
        }
    },
    {
        /* fUpdate */
        false,

        /* Rule ID */
        1,

        /* Rule definition */
        {
            /* Key */
            CfyE_Rule_KeyMask_Other(1, 0, 0),

            /* KeyMask */
            CfyE_Rule_KeyMask_Raw(0x0, 0x00, CFYE_RULE_CHANNEL_ID_MASK, 0, 0),

            /* Data */
            {
                /* MAC address, least significant bytes (3..0) */
                0x13D5C584,
                /* MAC address, most significant bytes (5, 4) */
                0x0000ABD2,
                /* Packet data (EtherType, VLAN tag) */
                0x00000000,
                0x00000000
            },

            /* DataMask */
            {
                0xFFFFFFFF,
                0x0000FFFF,
                0x00000000,
                0x00000000
            },

            /* Policy */
            Common_CfyE_Rule_Policy(1, 1, 0, false, false)
        }
    },
    {
        /* fUpdate */
        false,

        /* Rule ID */
        2,

        /* Rule definition */
        {
            /* Key */
            CfyE_Rule_KeyMask_Other(2, 0, 0),

            /* KeyMask */
            CfyE_Rule_KeyMask_Raw(0x0, 0x00, 0x00, 0, 0),

            /* Data */
            {
                /* MAC address, least significant bytes (3..0) */
                0x13D5C584,
                /* MAC address, most significant bytes (5, 4) */
                0x0000ACD2,
                /* Packet data (EtherType, VLAN tag) */
                0x00000000,
                0x00000000
            },

            /* DataMask */
            {
                0xFFFFFFFF,
                0x0000FFFF,
                0x00000000,
                0x00000000
            },

            /* Policy */
            Common_CfyE_Rule_Policy(2, 1, 0, false, false)
        }
    },
    {
        /* fUpdate */
        false,

        /* Rule ID */
        3,

        /* Rule definition */
        {
            /* Key */
            CfyE_Rule_KeyMask_Other(3, 0, 0),

            /* KeyMask */
            CfyE_Rule_KeyMask_Raw(0x0, 0x00, 0x00, 0, 0),

            /* Data */
            {
                /* MAC address, least significant bytes (3..0) */
                0x13D5C584,
                /* MAC address, most significant bytes (5, 4) */
                0x0000ADD2,
                /* Packet data (EtherType, VLAN tag) */
                0x00000000,
                0x00000000
            },

            /* DataMask */
            {
                0xFFFFFFFF,
                0x0000FFFF,
                0x00000000,
                0x00000000
            },

            /* Policy */
            Common_CfyE_Rule_Policy(3, 1, 0, false, false)
        }
    }
};

static Test_Case_CfyE_Rule_t CfyE_Rule_VLAN_1Q_Egress_MACsec_M2_update[] =
{
    {
        /* fUpdate */
        false,

        /* Rule ID */
        0,

        /* Rule definition */
        {
            /* Key */
            CfyE_Rule_KeyMask_VLAN(0, 1, 0),

            /* KeyMask */
            CfyE_Rule_KeyMask_Raw(CFYE_RULE_PKT_TYPE_MASK,
                                  CFYE_RULE_NUMTAGS_MASK,
                                  CFYE_RULE_CHANNEL_ID_MASK, 0, 0),

            /* Data */
            {
                /* MAC address, least significant bytes (3..0) */
                0xF0B109D6,
                /* MAC address, most significant bytes (5, 4) */
                0x00006355,
                /* Packet data (EtherType, VLAN tag) */
                0x00000008,
                0x00000000
            },

            /* DataMask */
            {
                0xFFFFFFFF,
                0x0000FFFF,
                0x0000FFFF,
                0x00000000
            },

            /* Policy */
            Common_CfyE_Rule_Policy(0, 1, 0, false, false)
        }
    },
    {
        /* fUpdate */
        true,

        /* Rule ID */
        0,

        /* Rule definition */
        {
            /* Key */
            CfyE_Rule_KeyMask_VLAN(0, 1, 0),

            /* KeyMask */
            CfyE_Rule_KeyMask_Raw(CFYE_RULE_PKT_TYPE_MASK,
                                  CFYE_RULE_NUMTAGS_MASK,
                                  CFYE_RULE_CHANNEL_ID_MASK, 0, 0),

            /* Data */
            {
                /* MAC address, least significant bytes (3..0) */
                0xF0B109D6,
                /* MAC address, most significant bytes (5, 4) */
                0x00006356,
                /* Packet data (EtherType, VLAN tag) */
                0x00000008,
                0x00000000
            },

            /* DataMask */
            {
                0xFFFFFFFF,
                0x0000FFFF,
                0x0000FFFF,
                0x00000000
            },

            /* Policy */
            Common_CfyE_Rule_Policy(0, 1, 0, false, false)
        }
    }
};
#if defined(TEST_MACSEC_VXLAN_ENABLE)
static Test_Case_CfyE_Rule_t CfyE_Rule_VxLAN[] =
{
    {
        /* fUpdate */
        false,

        /* Rule ID */
        0,

        /* Rule definition */
        {
            /* Key */
            CfyE_Rule_KeyMask_VXLAN(0, 0),

            /* KeyMask */
            CfyE_Rule_KeyMask_Raw(CFYE_RULE_PKT_TYPE_MASK,
                                  CFYE_RULE_NUMTAGS_MASK,
                                  CFYE_RULE_CHANNEL_ID_MASK, 0, 0),

            /* Data */
            {
                /* MAC address, least significant bytes (3..0) */
                0xe252a9f9,
                /* MAC address, most significant bytes (5, 4) */
                0x0000f805,
                /* Packet data (EtherType, VLAN tag) */
                0x00000008,
                0x00000000
            },

            /* DataMask */
            {
                0xFFFFFFFF,
                0x0000FFFF,
                0x00000000,
                0x00000000
            },

            /* Policy */
            Common_CfyE_Rule_Policy(0, 1, 0, false, false)
        }
    },
    {
        /* fUpdate */
        false,

        /* Rule ID */
        1,

        /* Rule definition */
        {
            /* Key */
            CfyE_Rule_KeyMask_VXLAN(0, 1),

            /* KeyMask */
            CfyE_Rule_KeyMask_Raw(CFYE_RULE_PKT_TYPE_MASK,
                                  CFYE_RULE_NUMTAGS_MASK,
                                  CFYE_RULE_CHANNEL_ID_MASK, 0, 0),

            /* Data */
            {
                /* MAC address, least significant bytes (3..0) */
                0x1f572357,
                /* MAC address, most significant bytes (5, 4) */
                0x00000272,
                /* Packet data (EtherType, VLAN tag) */
                0x00000008,
                0x00000000
            },

            /* DataMask */
            {
                0xFFFFFFFF,
                0x0000FFFF,
                0x00000000,
                0x00000000
            },

            /* Policy */
            Common_CfyE_Rule_Policy(0, 1, 0, false, false)
        }
    }
};
#endif

#if defined(TEST_IPSEC_ENABLE)
static Test_Case_CfyE_Rule_t CfyE_Rule_MPLS_Egress_IPsec =
{

    /* fUpdate */
    false,

    /* Rule ID */
    0,

    /* Rule definition */
    {
        /* Key */
        CfyE_Rule_KeyMask_MPLS_IPSEC(0, 1, 0),

        /* KeyMask */
        CfyE_Rule_KeyMask_Raw(CFYE_RULE_PKT_TYPE_MASK, 0, 0, 0, 0),

        /* Data */
        {
            /* MAC address, least significant bytes (3..0) */
            0x5cdb1054,
            /* MAC address, most significant bytes (5, 4) */
            0x00009570,
            /* Packet data (EtherType, VLAN tag) */
            0,
            0x00000000
        },

        /* DataMask */
        {
            0xffffffff,
            0x0000ffff,
            0,
            0
        },

        /* Policy */
        Common_CfyE_Rule_Policy(0, 0, 0, false, false)
    }
};

static Test_Case_CfyE_Rule_t CfyE_Rule_MultiSA_IPsec_Egress[] =
{
    {
        /* fUpdate */
        false,

        /* Rule ID */
        0,

        /* Rule definition */
        {
            /* Key */
            CfyE_Rule_KeyMask_MPLS_IPSEC(0, 1, 0),

            /* KeyMask */
            CfyE_Rule_KeyMask_Raw(CFYE_RULE_PKT_TYPE_MASK, 0, 0, 0, 0),

            /* Data */
            {
                /* MAC address, least significant bytes (3..0) */
                0x00000000,
                /* MAC address, most significant bytes (5, 4) */
                0x00000000,
                /* Packet data (EtherType, VLAN tag) */
                0,
                0x00000000
            },

            /* DataMask */
            {
                0xffffffff,
                0x0000ffff,
                0,
                0
            },

            /* Policy */
            Common_CfyE_Rule_Policy(0, 0, 0, false, false)
        }
    },

    {
        /* fUpdate */
        false,

        /* Rule ID */
        1,

        /* Rule definition */
        {
            /* Key */
            CfyE_Rule_KeyMask_MPLS_IPSEC(0, 1, 0),

            /* KeyMask */
            CfyE_Rule_KeyMask_Raw(CFYE_RULE_PKT_TYPE_MASK, 0, 0, 0, 0),

            /* Data */
            {
                /* MAC address, least significant bytes (3..0) */
                0x3d688884,
                /* MAC address, most significant bytes (5, 4) */
                0x000010ea,
                /* Packet data (EtherType, VLAN tag) */
                0,
                0x00000000
            },

            /* DataMask */
            {
                0xffffffff,
                0x0000ffff,
                0,
                0
            },

            /* Policy */
            Common_CfyE_Rule_Policy(1, 0, 0, false, false)
        }
    },
};

static Test_Case_CfyE_Rule_t CfyE_Rule_VLAN_Egress_IPsec =
{

    /* fUpdate */
    false,

    /* Rule ID */
    0,

    /* Rule definition */
    {
        /* Key */
        CfyE_Rule_KeyMask_VLAN(0, 1, 0),

        /* KeyMask */
        CfyE_Rule_KeyMask_Raw(CFYE_RULE_PKT_TYPE_MASK, 0, 0, 0, 0),

        /* Data */
        {
            /* MAC address, least significant bytes (3..0) */
            0,
            /* MAC address, most significant bytes (5, 4) */
            0,
            /* Packet data (EtherType, VLAN tag) */
            0,
            0x00000000
        },

        /* DataMask */
        {
            0,
            0,
            0,
            0
        },

        /* Policy */
        Common_CfyE_Rule_Policy(0, 0, 0, false, false)
    }
};

static Test_Case_CfyE_Rule_t CfyE_Rule_IPsec_Ingress =
{

    /* fUpdate */
    false,

    /* Rule ID */
    0,

    /* Rule definition */
    {
        /* Key */
        CfyE_Rule_KeyMask_IPSEC_INGRESS(0, 0, 0),

        /* KeyMask */
        CfyE_Rule_KeyMask_Raw(CFYE_RULE_PKT_TYPE_MASK,
                              CFYE_RULE_NUMTAGS_MASK,
                              CFYE_RULE_CHANNEL_ID_MASK, 0, 0),

        /* Data */
        {
            /* MAC address, least significant bytes (3..0) */
            0x19262a3a,
            /* MAC address, most significant bytes (5, 4) */
            0xf7f,
            /* Packet data (SPI) */
            0x416bd021,
            0x00000000
        },

        /* DataMask */
        {
            0xffffffff,
            0xffff,
            0xffffffff,
            0xf
        },

        /* Policy */
        Common_CfyE_Rule_Policy(0, 0, 0, false, false)
    }
};

static Test_Case_CfyE_Rule_t CfyE_Rule_IPsec_IngressUDP =
{

    /* fUpdate */
    false,

    /* Rule ID */
    0,

    /* Rule definition */
    {
        /* Key */
        CfyE_Rule_KeyMask_IPsec_Ingress_Common(CFYE_RULE_PKT_TYPE_IPSEC_UDP, 0, 0),

        /* KeyMask */
        CfyE_Rule_KeyMask_Raw(CFYE_RULE_PKT_TYPE_MASK,
                              CFYE_RULE_NUMTAGS_MASK,
                              CFYE_RULE_CHANNEL_ID_MASK, 0, 0),

        /* Data */
        {
            /* MAC address, least significant bytes (3..0) */
            0,
            /* MAC address, most significant bytes (5, 4) */
            0,
            /* Packet data (SPI) */
            0x448c645d,
            0x00000000
        },

        /* DataMask */
        {
            0x0,
            0x0,
            0xffffffff,
            0x0
        },

        /* Policy */
        Common_CfyE_Rule_Policy(0, 0, 0, false, false)
    }
};

static Test_Case_CfyE_Rule_t CfyE_Rule_IPsecIngressVLAN =
{

    /* fUpdate */
    false,

    /* Rule ID */
    0,

    /* Rule definition */
    {
        /* Key */
        CfyE_Rule_KeyMask_IPSEC_INGRESS(0, 0, 0),

        /* KeyMask */
        CfyE_Rule_KeyMask_Raw(CFYE_RULE_PKT_TYPE_MASK,
                              CFYE_RULE_NUMTAGS_MASK,
                              CFYE_RULE_CHANNEL_ID_MASK, 0, 0),

        /* Data */
        {
            /* MAC address, least significant bytes (3..0) */
            0,
            /* MAC address, most significant bytes (5, 4) */
            0,
            /* Packet data (SPI) */
            0x2b8e212e,
            0x00000000
        },

        /* DataMask */
        {
            0,
            0,
            0xffffffff,
            0xf
        },

        /* Policy */
        Common_CfyE_Rule_Policy(0, 0, 0, false, false)
    }
};

static Test_Case_CfyE_Rule_t CfyE_Rule_IPsecIngressMPLS =
{

    /* fUpdate */
    false,

    /* Rule ID */
    0,

    /* Rule definition */
    {
        /* Key */
        CfyE_Rule_KeyMask_IPsec_Ingress_Common(CFYE_RULE_PKT_TYPE_IPSEC_MPLS, 0, 0),

        /* KeyMask */
        CfyE_Rule_KeyMask_Raw(CFYE_RULE_PKT_TYPE_MASK,
                              CFYE_RULE_NUMTAGS_MASK,
                              CFYE_RULE_CHANNEL_ID_MASK, 0, 0),

        /* Data */
        {
            /* MAC address, least significant bytes (3..0) */
            0x61a16ddc,
            /* MAC address, most significant bytes (5, 4) */
            0x0000c13a,
            /* Packet data (SPI) */
            0x3511adb7,
            0x00000000
        },

        /* DataMask */
        {
            0xffffffff,
            0x0000ffff,
            0xffffffff,
            0x0000000f
        },

        /* Policy */
        Common_CfyE_Rule_Policy(0, 0, 0, false, false)
    }
};

static Test_Case_CfyE_Rule_t CfyE_Rule_IPsecIngressMPLS_Bypass =
{
    /* fUpdate */
    false,

    /* Rule ID */
    0,

    /* Rule definition */
    {
        /* Key */
        CfyE_Rule_KeyMask_IPSEC_INGRESS(0, 0, 0),

        /* KeyMask */
        CfyE_Rule_KeyMask_Raw(CFYE_RULE_PKT_TYPE_MASK,
                              CFYE_RULE_NUMTAGS_MASK,
                              CFYE_RULE_CHANNEL_ID_MASK, 0, 0),

        /* Data */
        {
            /* MAC address, least significant bytes (3..0) */
            0xb5e2cbc4,
            /* MAC address, most significant bytes (5, 4) */
            0x0000adfa,
            /* Packet data (SPI) */
            0x0e11e900,
            0x00000000
        },

        /* DataMask */
        {
            0xffffffff,
            0x0000ffff,
            0xffffffff,
            0x0000000f
        },

        /* Policy */
        Common_CfyE_Rule_Policy(0, 0, 0, false, false)
    }
};


static Test_Case_CfyE_Rule_t CfyE_Rule_MultiSA_IPsec_Ingress[] =
{
    {
        /* fUpdate */
        false,

        /* Rule ID */
        0,

        /* Rule definition */
        {
            /* Key */
            CfyE_Rule_KeyMask_IPSEC_INGRESS(0, 0, 0),

            /* KeyMask */
            CfyE_Rule_KeyMask_Raw(CFYE_RULE_PKT_TYPE_MASK,
                              CFYE_RULE_NUMTAGS_MASK,
                              CFYE_RULE_CHANNEL_ID_MASK, 0, 0),

            /* Data */
            {
                /* MAC address, least significant bytes (3..0) */
                0x66fb31b4,
                /* MAC address, most significant bytes (5, 4) */
                0x00006d6c,
                /* Packet data (SPI) */
                0x7863d384,
                0x00000000
            },

            /* DataMask */
            {
                0xffffffff,
                0x0000ffff,
                0xffffffff,
                0x0000000f
            },

            /* Policy */
            Common_CfyE_Rule_Policy(0, 0, 0, false, false)
        }
    },

    {
        /* fUpdate */
        false,

        /* Rule ID */
        1,

        /* Rule definition */
        {
            /* Key */
            CfyE_Rule_KeyMask_IPSEC_INGRESS(0, 0, 0),

            /* KeyMask */
            CfyE_Rule_KeyMask_Raw(CFYE_RULE_PKT_TYPE_MASK,
                                  CFYE_RULE_NUMTAGS_MASK,
                                  CFYE_RULE_CHANNEL_ID_MASK, 0, 0),

            /* Data */
            {
                /* MAC address, least significant bytes (3..0) */
                0xe21756b2,
                /* MAC address, most significant bytes (5, 4) */
                0x0000669e,
                /* Packet data (SPI) */
                0x7c533e2f,
                0x00000000
            },

            /* DataMask */
            {
                0xffffffff,
                0x0000ffff,
                0xffffffff,
                0x0000000f
            },

            /* Policy */
            Common_CfyE_Rule_Policy(1, 0, 0, false, false)
        }
    },

    {
            /* fUpdate */
            false,

            /* Rule ID */
            2,

            /* Rule definition */
            {
                /* Key */
                CfyE_Rule_KeyMask_IPSEC_INGRESS(0, 0, 0),

                /* KeyMask */
                CfyE_Rule_KeyMask_Raw(CFYE_RULE_PKT_TYPE_MASK,
                                      CFYE_RULE_NUMTAGS_MASK,
                                      CFYE_RULE_CHANNEL_ID_MASK, 0, 0),

                /* Data */
                {
                    /* MAC address, least significant bytes (3..0) */
                    0x3f5ed366,
                    /* MAC address, most significant bytes (5, 4) */
                    0x00000262,
                    /* Packet data (SPI) */
                    0x09c08e42,
                    0x00000000
                },

                /* DataMask */
                {
                    0xffffffff,
                    0x0000ffff,
                    0xffffffff,
                    0x0000000f
                },

                /* Policy */
                Common_CfyE_Rule_Policy(2, 0, 0, false, false)
            }
        },
};


static Test_Case_CfyE_Rule_t CfyE_Rule_ReplayFail_IPsec_Ingress[] =
{
    {
        /* fUpdate */
        false,

        /* Rule ID */
        0,

        /* Rule definition */
        {
            /* Key */
            CfyE_Rule_KeyMask_IPsec_Ingress_Common(CFYE_RULE_PKT_TYPE_IPSEC, 0, 0),

            /* KeyMask */
            CfyE_Rule_KeyMask_IPSEC_Ingress_Common(7, 127, 15),

            /* Data */
            {
                /* MAC address, least significant bytes (3..0) */
                0x4b95e154,
                /* MAC address, most significant bytes (5, 4) */
                0x00005fb4,
                /* Packet data (SPI) */
                0x7e7f7675,
                0x00000000
            },

            /* DataMask */
            {
                0xffffffff,
                0x0000ffff,
                0xffffffff,
                0x0000000f
            },

            /* Policy */
            Common_CfyE_Rule_Policy(0, 0, 0, false, false)
        }
    },

    {
        /* fUpdate */
        false,

        /* Rule ID */
        1,

        /* Rule definition */
        {
            /* Key */
            CfyE_Rule_KeyMask_IPsec_Ingress_Common(CFYE_RULE_PKT_TYPE_IPSEC, 0, 0),

            /* KeyMask */
            CfyE_Rule_KeyMask_IPSEC_Ingress_Common(7, 127, 15),


            /* Data */
            {
                /* MAC address, least significant bytes (3..0) */
                0xbd3c4258,

                /* MAC address, most significant bytes (5, 4) */
                0x0000c167,

                /* Packet data (SPI) */
                0x5f746a69,

                0x00000000
            },

            /* DataMask */
            {
                0xffffffff,
                0x0000ffff,
                0xffffffff,
                0x0000000f
            },

            /* Policy */
            Common_CfyE_Rule_Policy(1, 0, 0, false, false)
        }
    },
};


static Test_Case_CfyE_Rule_t CfyE_Rule_IPsec_Ingress_LateCheck =
{
    /* fUpdate */
    false,

    /* Rule ID */
    0,

    /* Rule definition */
    {
        /* Key */
        CfyE_Rule_KeyMask_IPSEC_INGRESS(0, 0, 0),

        /* KeyMask */
        CfyE_Rule_KeyMask_Raw(CFYE_RULE_PKT_TYPE_MASK,
                              CFYE_RULE_NUMTAGS_MASK,
                              CFYE_RULE_CHANNEL_ID_MASK, 0, 0),

        /* Data */
        {
            /* MAC address, least significant bytes (3..0) */
            0xba5467b6,
            /* MAC address, most significant bytes (5, 4) */
            0x0000423f,
            /* Packet data (SPI) */
            0x392761dd,
            0x00000000
        },

        /* DataMask */
        {
            0xffffffff,
            0xffff,
            0xffffffff,
            0xf
        },

        /* Policy */
        Common_CfyE_Rule_Policy(0, 0, 0, false, false)
    }
};


static Test_Case_CfyE_Rule_t CfyE_Rule_MultiSA_IPsec_Egress_Test =
{
    /* fUpdate */
    false,

    /* Rule ID */
    0,

    /* Rule definition */
    {
        /* Key */
        CfyE_Rule_KeyMask_Other(0, 0, 0),

        /* KeyMask */
        CfyE_Rule_KeyMask_IPSEC_Other(7, 0, 0, 0, 0),

        /* Data */
        {
            /* MAC address, least significant bytes (3..0) */
            0xa1381c22,

            /* MAC address, most significant bytes (5, 4) */
            0x0000d76c,

            /* Packet data (EtherType, VLAN tag) */
            0,
            0x00000000
        },

        /* DataMask */
        {
            0xffffffff,
            0x0000ffff,
            0,
            0
        },

        /* Policy */
        Common_CfyE_Rule_Policy(0, 0, 0, false, false)
    }
};

#endif

static Test_Case_CfyE_Rule_t CfyE_Rule_VLAN_1Q_Ingress_MACsec_O1 =
{
    /* fUpdate */
    false,

    /* Rule ID */
    0,

    /* Rule definition */
    {
        /* Key */
        CfyE_Rule_KeyMask_Other(0, 1, 0),

        /* KeyMask */
        CfyE_Rule_KeyMask_Raw(CFYE_RULE_PKT_TYPE_MASK,
                              CFYE_RULE_NUMTAGS_MASK,
                              CFYE_RULE_CHANNEL_ID_MASK, 0, 0),

        /* Data */
        {
            /* MAC address, least significant bytes (3..0) */
            0xF0B109D6,
            /* MAC address, most significant bytes (5, 4) */
            0x00006356,
            /* Packet data (EtherType, VLAN tag) */
            0x0000E588,
            0x00000000
        },

        /* DataMask */
        {
            0xFFFFFFFF,
            0x0000FFFF,
            0x00000000,
            0x00000000
        },

        /* Policy */
        Common_CfyE_Rule_Policy(0, 0, 0, false, false)
    }
};

static Test_Case_CfyE_Rule_t CfyE_Rule_VLAN_1Q_Ingress_MACsec_O2 =
{
    /* fUpdate */
    false,

    /* Rule ID */
    0,

    /* Rule definition */
    {
        /* Key */
        CfyE_Rule_KeyMask_VLAN(0, 1, 0),

        /* KeyMask */
        CfyE_Rule_KeyMask_Raw(CFYE_RULE_PKT_TYPE_MASK,
                              CFYE_RULE_NUMTAGS_MASK,
                              CFYE_RULE_CHANNEL_ID_MASK, 0, 0),

        /* Data */
        {
            /* MAC address, least significant bytes (3..0) */
            0xF0B109D6,
            /* MAC address, most significant bytes (5, 4) */
            0x00006356,
            /* Packet data (EtherType, VLAN tag) */
            0x9998E588,
            0x00000000,
        },

        /* DataMask */
        {
            0xFFFFFFFF,
            0x0000FFFF,
            0x0000FFFF,
            0x00000000
        },

        /* Policy */
        Common_CfyE_Rule_Policy(0, 0, 0, false, false)
    }
};

static Test_Case_CfyE_Rule_t CfyE_Rule_VLAN_QinQ_Egress_MACsec_M1 =
{
    /* fUpdate */
    false,

    /* Rule ID */
    0,

    /* Rule definition */
    {
        /* Key */
        CfyE_Rule_KeyMask_VLAN(0, 2, 0),

        /* KeyMask */
        CfyE_Rule_KeyMask_Raw(CFYE_RULE_PKT_TYPE_MASK,
                              CFYE_RULE_NUMTAGS_MASK,
                              CFYE_RULE_CHANNEL_ID_MASK, 0, 0),

        /* Data */
        {
            /* MAC address, least significant bytes (3..0) */
            0xF0B109D6,
            /* MAC address, most significant bytes (5, 4) */
            0x00006356,
            /* Packet data (EtherType, VLAN tag) */
            0x99010008,
            0x00999800
        },

        /* DataMask */
        {
            0xFFFFFFFF,
            0x0000FFFF,
            0xFFFFFFFF,
            0x00FFFF00
        },

        /* Policy */
        Common_CfyE_Rule_Policy(0, 1, 0, false, false)
    }
};

static Test_Case_CfyE_Rule_t CfyE_Rule_VLAN_QinQ_Ingress_MACsec_O3 =
{
    /* fUpdate */
    false,

    /* Rule ID */
    0,

    /* Rule definition */
    {
        /* Key */
        CfyE_Rule_KeyMask_VLAN(0, 2, 0),

        /* KeyMask */
        CfyE_Rule_KeyMask_Raw(CFYE_RULE_PKT_TYPE_MASK,
                              CFYE_RULE_NUMTAGS_MASK,
                              CFYE_RULE_CHANNEL_ID_MASK, 0, 0),

        /* Data */
        {
            /* MAC address, least significant bytes (3..0) */
            0xF0B109D6,
            /* MAC address, most significant bytes (5, 4) */
            0x00006356,
            /* Packet data (EtherType, VLAN tag) */
            0x9901E588,
            0x00999800
        },

        /* DataMask */
        {
            0xFFFFFFFF,
            0x0000FFFF,
            0xFFFFFFFF,
            0x00FFFF00
        },

        /* Policy */
        Common_CfyE_Rule_Policy(0, 1, 0, false, false)
    }
};

static Test_Case_CfyE_Rule_t CfyE_Rule_VLAN_QinQinQ_Egress_MACsec_M1 =
{
    /* fUpdate */
    false,

    /* Rule ID */
    0,

    /* Rule definition */
    {
        /* Key */
        CfyE_Rule_KeyMask_VLAN(0, 3, 0),

        /* KeyMask */
        CfyE_Rule_KeyMask_Raw(CFYE_RULE_PKT_TYPE_MASK,
                              CFYE_RULE_NUMTAGS_MASK,
                              CFYE_RULE_CHANNEL_ID_MASK, 0, 0),

        /* Data */
        {
            /* MAC address, least significant bytes (3..0) */
            0xF0B109D6,
            /* MAC address, most significant bytes (5, 4) */
            0x00006356,
            /* Packet data (EtherType, VLAN tag) */
            0x99010008,
            0x00999800
        },

        /* DataMask */
        {
            0xFFFFFFFF,
            0x0000FFFF,
            0xFFFFFFFF,
            0x00FFFF00
        },

        /* Policy */
        Common_CfyE_Rule_Policy(0, 1, 0, false, false)
    }
};

static Test_Case_CfyE_Rule_t CfyE_Rule_VLAN_QinQinQ_Ingress_MACsec_O4 =
{
    /* fUpdate */
    false,

    /* Rule ID */
    0,

    /* Rule definition */
    {
        /* Key */
        CfyE_Rule_KeyMask_VLAN(0, 3, 0),

        /* KeyMask */
        CfyE_Rule_KeyMask_Raw(CFYE_RULE_PKT_TYPE_MASK,
                              CFYE_RULE_NUMTAGS_MASK,
                              CFYE_RULE_CHANNEL_ID_MASK, 0, 0),

        /* Data */
        {
            /* MAC address, least significant bytes (3..0) */
            0xF0B109D6,
            /* MAC address, most significant bytes (5, 4) */
            0x00006356,
            /* Packet data (EtherType, VLAN tag) */
            0x9901E588,
            0x00999800
        },

        /* DataMask */
        {
            0xFFFFFFFF,
            0x0000FFFF,
            0xFFFFFFFF,
            0x00FFFF00
        },

        /* Policy */
        Common_CfyE_Rule_Policy(0, 1, 0, false, false)
    }
};

static Test_Case_CfyE_Rule_t CfyE_Rule_ForLimits_VLAN_1Q_MACsec[] =
{
    {
        /* fUpdate */
        false,

        /* Rule ID */
        0,

        /* Rule definition */
        {
            /* Key */
            CfyE_Rule_KeyMask_VLAN(0, 1, 0),

            /* KeyMask */
            CfyE_Rule_KeyMask_Raw(CFYE_RULE_PKT_TYPE_MASK,
                              CFYE_RULE_NUMTAGS_MASK,
                              CFYE_RULE_CHANNEL_ID_MASK, 0, 0),

            /* Data */
            {
                /* MAC address, least significant bytes (3..0) */
                0xF0B109D6,
                /* MAC address, most significant bytes (5, 4) */
                0x00006356,
                /* Packet data (EtherType, VLAN tag) */
                0x99980000,
                0x00000000
            },

            /* DataMask */
            {
                0xFFFFFFFF,
                0x0000FFFF,
                0xFF0F0000,
                0x00000000
            },

            /* Policy */
            Common_CfyE_Rule_Policy(0, 1, 0, false, false)
        }
    },
    {
        /* fUpdate */
        false,

        /* Rule ID */
        0,

        /* Rule definition */
        {
            /* Key */
            CfyE_Rule_KeyMask_VLAN(0, 1, 0),

            /* KeyMask */
            CfyE_Rule_KeyMask_Raw(CFYE_RULE_PKT_TYPE_MASK,
                              CFYE_RULE_NUMTAGS_MASK,
                              CFYE_RULE_CHANNEL_ID_MASK, 0, 0),

            /* Data */
            {
                /* MAC address, least significant bytes (3..0) */
                0x9EBD1B80,
                /* MAC address, most significant bytes (5, 4) */
                0x00001538,
                /* Packet data (EtherType, VLAN tag) */
                0x99980000,
                0x00000000
            },

            /* DataMask */
            {
                0xFFFFFFFF,
                0x0000FFFF,
                0xFF0F0000,
                0x00000000
            },

            /* Policy */
            Common_CfyE_Rule_Policy(0, 1, 0, false, false)
        }
    }
};

static CfyE_Device_Exceptions_t CfyEDevExcept_DefaultP0 =
{
    CFYE_DROP_INTERNAL,                 /* Drop action */
    false,                              /* No drop */
    true,                               /* Default vPort */
    0,                                   /* vPort */
    CFYE_DROP_INTERNAL,                 /* Drop action */
    false                               /* Should secure */
};

/* Device (channel) control defaults */
static CfyE_Device_Control_t CfyEDevCtrl_LowLatency =
{
    /* Low Latency if true */
    true,

    /* L3L4 enable */
    NULL,
    /* true - if IPsec mode is supported.*/
    false,

    /* true - Spare register and interrupt controller are present */
    false,

    /* Exception cases settings */
    NULL
};

static CfyE_Device_Control_t CfyEDevCtrl_DefaultP0 =
{
    /* Low Latency if true */
    false,


    /* L3L4 enable */
    NULL,
    /* true - if IPsec mode is supported.*/
    false,

    /* true - Spare register and interrupt controller are present */
    false,

    /* Exception cases settings */
    &CfyEDevExcept_DefaultP0
};
#if defined(TEST_MACSEC_VXLAN_ENABLE)

static CfyE_Channel_L3L4_t L3L4_VxLAN =
{
    CFYE_VXL_FLAG_PARSE_IP | CFYE_VXL_FLAG_PARSE_UDP |
    CFYE_VXL_FLAG_PARSE_VXLAN1 | CFYE_VXL_FLAG_PARSE_VXLAN2
};

static CfyE_Device_Control_t CfyEDevCtrl_VxLAN =
{
    /* Low Latency if true */
    false,


    /* L3L4 enable */
    &L3L4_VxLAN,
    /* true - if IPsec mode is supported.*/
    false,

    /* true - Spare register and interrupt controller are present */
    false,

    /* Exception cases settings */
    &CfyEDevExcept_DefaultP0
};

#endif

#if defined(TEST_IPSEC_ENABLE)
static CfyE_Device_Exceptions_t CfyEDevExcept_IPsecDefault =
{
    CFYE_DO_NOT_DROP,                   /* Drop action */
    false,                              /* No drop */
    false,                              /* Default vPort */
    0,                                  /* vPort */
    CFYE_DROP_INTERNAL,                 /* Drop action */
    false                               /* Should secure */
};

static CfyE_Device_Control_t CfyEDevCtrl_IPsec_DefaultP0 =
{
    /* Low Latency if true */
    false,

    /* L3L4 enable */
    NULL,

    /* true - if IPsec mode is supported.*/
    true,

    /* true - Spare register and interrupt controller are present */
    false,

    /* Exception cases settings */
    &CfyEDevExcept_IPsecDefault
};

/* Statistics control defaults */
static CfyE_Statistics_Control_t CfyEStatCtrl_IPsecIngressMPLS =
{
    /* Reset on read if true */
    true,

    /* Threshold */
    { 1, 0 },

    /* Channel Threshold */
    { 1, 0 },

    /** Threshold for the per-MTT frame counters */
    { 1, 0 },

    /* Disable no counters types */
    0
};
#endif

/* Statistics control defaults */
static CfyE_Statistics_Control_t CfyEStatCtrl_NoResetNoThreshold =
{
    /* Reset on read if true */
    false,

    /* Threshold */
    { 0, 0 },

    /* Channel Threshold */
    { 0, 0 },

    /* MTT Threshold */
    { 0, 0},

    /* Disable no counters types */
    0
};

static CfyE_Statistics_Control_t CfyEStatCtrl_ResetNoThreshold =
{
    /* Reset on read if true */
    !TEST_MACSEC_WRITE_TO_DECREMENT,

    /* Threshold */
    { 0, 0 },

    /* Channel Threshold */
    { 0, 0 },

    /* MTT Threshold */
    { 0, 0},

    /* Disable no counters types */
    0
};

static CfyE_Statistics_Control_t CfyEStatCtrl_ResetThreshold =
{
    /* Reset on read if true */
    !TEST_MACSEC_WRITE_TO_DECREMENT,

    /* Threshold */
    { 1, 0 },

    /* Channel Threshold */
    { 1, 0 },

    /* MTT Threshold */
    { 0, 0},

    /* Disable no counters types */
    0
};


static CfyE_SecTAG_Parser_t CfyESecTAGParser_MACsecTCAMNoSCI =
{
    true,
    true,
    true,
    false,
    0x88E5
};


#define CfyE_VLAN_ParseTag(fParseQTag,                                      \
                           fParseStag1, fParseStag2, fParseStag3,           \
                           fParseQinQ)                                      \
{                                                                           \
    fParseQTag,                                                             \
    fParseStag1,                                                            \
    fParseStag2,                                                            \
    fParseStag3,                                                            \
    fParseQinQ                                                              \
}

static CfyE_VLAN_Parser_t CfyEParser_VLAN_1Q =
{
    CfyE_VLAN_ParseTag(true, false, false, false, false),
    false,
    false,
    0,
    { 0 },
    { 0 },
    0x8100,
    0,
    0,
    0
};

static CfyE_VLAN_Parser_t CfyEParser_VLAN_QinQ =
{
    CfyE_VLAN_ParseTag(true, true, true, false, true),
    true,
    true,
    0,
    { 0, 1, 2, 3, 4, 5, 6, 7 },
    { 0, 1, 2, 3, 4, 5, 6, 7 },
    0x8100,
    0x9100,
    0x9200,
    0
};

static CfyE_HeaderParser_t CfyEParser_SecTAG_MACsecNoSCI =
{
    NULL,                 /* egress header parser */
    &CfyESecTAGParser_MACsecTCAMNoSCI,
   NULL,                  /* MPLS parser */
   NULL,                  /* VLAN tag parser */
   NULL,                  /* L4 parser */
   NULL,                 /* IPsec parser */
};


#if defined(TEST_MACSEC_VXLAN_ENABLE)
static CfyE_L4_Ports_t L4Port_VxLAN = {
    4789,
    4790,
};

static CfyE_HeaderParser_t CfyEParser_VxLAN =
{
    NULL,
    &CfyESecTAGParser_MACsecTCAMNoSCI,
   NULL,                  /* MPLS parser */
   &CfyEParser_VLAN_1Q,   /* VLAN tag parser */
   &L4Port_VxLAN,         /* L4 parser */
   NULL,                 /* IPsec parser */
};
#endif

#if defined(TEST_IPSEC_ENABLE)
static CfyE_EgressHeader_t CfyEIPsecEgressHeader =
{
    /** Enable flag */
    true,

    /** Egress header type */
    0x9999,
};

static CfyE_MPLS_Parser_t CfyEIPsecMPLSHeader =
{
    .MPLS_Etype = {
        {.fCompare = true, .MPLS_Etype = 0x8848},
        {.fCompare = true, .MPLS_Etype = 0x8847},
        {.fCompare = true, .MPLS_Etype = 0x0},
        {.fCompare = true, .MPLS_Etype = 0x0},
    },
};

static CfyE_IPSEC_Parser_t CfyEIPsecParser =
{
    /** Enable outer IP header parsing */
    true,

    /** Enable UDP parsing after outer IP header. */
    true,

    /** Enable parsing of UDP encapsulated packets */
    true,

    /** Enable detection of ESP header */
    true,

    /** Enable detection and bypassing of IKE v1/v2 header */
    true,

    /** Enable detection and bypassing of NAT-T IKE. */
    true,

    /** Enable detection and bypassing of NAT Keepalive. */
    true,

    /** Enable detection and bypassing of UDP headers that have non-zero checksum */
    false,

    /** Ingress-only field: Enable MAC DA check for IPsec processing */
    false,

    /** Ingress-only field: allow fragments */
    false,

    /** Ingress-only field: ignore IPv5 Checksum */
    false,

    /** Ingress-only field: mark IKE packets as sub-control packets */
    true,

    /** Ingress-only field: mark NAT-T IKE packets as sub-control packets */
    true,

    /** Ingress-only field: mark NAT-T Keep Alive  packets as sub-control
        packets */
    false,

    /** Global Controls */

    /** Default IKE port */
    500,

    /** Default NAT port */
    4500,

    /** MAC destination address, 6 bytes */
    {0, 0, 0, 0, 0, 0},
};

static CfyE_IPSEC_Parser_t CfyE_IPsecHdrParser_IPsecIngressVLAN =
{
    /** Enable outer IP header parsing */
    true,

    /** Enable UDP parsing after outer IP header. */
    false,

    /** Enable parsing of UDP encapsulated packets */
    false,

    /** Enable detection of ESP header */
    true,

    /** Enable detection and bypassing of IKE v1/v2 header */
    true,

    /** Enable detection and bypassing of NAT-T IKE. */
    true,

    /** Enable detection and bypassing of NAT Keepalive. */
    true,

    /** Enable detection and bypassing of UDP headers that have non-zero checksum */
    true,

    /** Ingress-only field: Enable MAC DA check for IPsec processing */
    false,

    /** Ingress-only field: allow fragments */
    false,

    /** Ingress-only field: ignore IPv5 Checksum */
    false,

    /** Ingress-only field: mark IKE packets as sub-control packets */
    true,

    /** Ingress-only field: mark NAT-T IKE packets as sub-control packets */
    true,

    /** Ingress-only field: mark NAT-T Keep Alive  packets as sub-control
        packets */
    false,

    /** Global Controls */

    /** Default IKE port */
    0,

    /** Default NAT port */
    0,

    /** MAC destination address, 6 bytes */
    {0, 0, 0, 0, 0, 0},
};

static CfyE_VLAN_Parser_t CfyE_VLAN_IPsecParser =
{
    {true, true, true, true, true},
    true,
    true,
    0,
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    0x8100,   /* QTag */
    0x88a8,   /* STag 1 */
    0,        /* STag 2 */
    0,        /* STag 3 */
};

static CfyE_VLAN_Parser_t CfyE_VLAN_HdrParser_IPsecIngressVLAN =
{
    {true, true, true, true, true},
    true,
    true,
    0,
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    0x8100,   /* QTag */
    0x88a8,   /* STag 1 */
    0,        /* STag 2 */
    0,        /* STag 3 */
};

static CfyE_HeaderParser_t CfyE_HeaderParser_IPsecVLAN =
{
    &CfyEIPsecEgressHeader,
    NULL,
    NULL,
    &CfyE_VLAN_IPsecParser,
    NULL,
    &CfyEIPsecParser,
};

static CfyE_HeaderParser_t CfyE_HeaderParser_IPsec =
{
    &CfyEIPsecEgressHeader,
    NULL,
    NULL,
    NULL,
    NULL,
    &CfyEIPsecParser,
};

static CfyE_HeaderParser_t CfyE_HeaderParser_IPsecIngress =
{
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &CfyEIPsecParser,
};

static CfyE_HeaderParser_t CfyE_HeaderParser_IPsecIngressVLAN =
{
    NULL,
    NULL,
    NULL,
    &CfyE_VLAN_HdrParser_IPsecIngressVLAN,
    NULL,
    &CfyE_IPsecHdrParser_IPsecIngressVLAN,
};

static CfyE_MPLS_Parser_t CfyE_VLAN_HdrParser_IPsecIngressMPLS =
{
    .MPLS_Etype = {
        {.fCompare = true, .MPLS_Etype = 0x8848},
        {.fCompare = true, .MPLS_Etype = 0x8847},
        {.fCompare = true, .MPLS_Etype = 0x0},
        {.fCompare = true, .MPLS_Etype = 0x0},
    },
};

static CfyE_HeaderParser_t CfyE_HeaderParser_IPsecIngressMPLS =
{
    NULL,
    NULL,
    &CfyE_VLAN_HdrParser_IPsecIngressMPLS,
    NULL,
    NULL,
    &CfyE_IPsecHdrParser_IPsecIngressVLAN,
};

static CfyE_MPLS_Parser_t CfyE_HdrParser_MPLS_IPsecIngress =
{
    .MPLS_Etype = {
        {.fCompare = true, .MPLS_Etype = 0x8848},
        {.fCompare = true, .MPLS_Etype = 0x8847},
        {.fCompare = true, .MPLS_Etype = 0x0},
        {.fCompare = true, .MPLS_Etype = 0x0},
    },
};

static CfyE_VLAN_Parser_t CfyE_HdrParser_VLAN_IPsecIngress =
{
    {true, true, true, true, true},
    true,
    true,
    0,
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    0x8100,   /* QTag */
    0x88a8,   /* STag 1 */
    0,        /* STag 2 */
    0,        /* STag 3 */
};

static CfyE_IPSEC_Parser_t CfyE_IPsecHdrParser_IPsecIngress =
{
    /** Enable outer IP header parsing */
    true,

    /** Enable UDP parsing after outer IP header. */
    false,

    /** Enable parsing of UDP encapsulated packets */
    false,

    /** Enable detection of ESP header */
    true,

    /** Enable detection and bypassing of IKE v1/v2 header */
    true,

    /** Enable detection and bypassing of NAT-T IKE. */
    true,

    /** Enable detection and bypassing of NAT Keepalive. */
    true,

    /** Enable detection and bypassing of UDP headers that have non-zero checksum */
    true,

    /** Ingress-only field: Enable MAC DA check for IPsec processing */
    false,

    /** Ingress-only field: allow fragments */
    false,

    /** Ingress-only field: ignore IPv5 Checksum */
    false,

    /** Ingress-only field: mark IKE packets as sub-control packets */
    true,

    /** Ingress-only field: mark NAT-T IKE packets as sub-control packets */
    true,

    /** Ingress-only field: mark NAT-T Keep Alive  packets as sub-control
        packets */
    false,

    /** Global Controls */

    /** Default IKE port */
    0,

    /** Default NAT port */
    0,

    /** MAC destination address, 6 bytes */
    {0, 0, 0, 0, 0, 0},
};


static CfyE_HeaderParser_t CfyE_HdrParser_IPsecIngress =
{
    NULL,
    NULL,
    &CfyE_HdrParser_MPLS_IPsecIngress,
    &CfyE_HdrParser_VLAN_IPsecIngress,
    NULL,
    &CfyE_IPsecHdrParser_IPsecIngress,
};

static CfyE_HeaderParser_t CfyE_HeaderParser_IPsecMPLS =
{
    &CfyEIPsecEgressHeader,
    NULL,
    &CfyEIPsecMPLSHeader,
    NULL,
    NULL,
    &CfyEIPsecParser,
};
#endif


static CfyE_HeaderParser_t CfyEParser_VLAN_1Q_MACsecNoSCI =
{
    NULL,                 /* egress header parser */
    &CfyESecTAGParser_MACsecTCAMNoSCI,
   NULL,                  /* MPLS parser */
    &CfyEParser_VLAN_1Q,
   NULL,                  /* L4 parser */
   NULL,                 /* IPsec parser */
};

static CfyE_HeaderParser_t CfyEParser_VLAN_QinQ_MACsecNoSCI =
{
    NULL,                 /* egress header parser */
    &CfyESecTAGParser_MACsecTCAMNoSCI,
   NULL,                  /* MPLS parser */
    &CfyEParser_VLAN_QinQ,
   NULL,                  /* L4 parser */
   NULL,                 /* IPsec parser */
};

static CfyE_ControlPacket_t CfyECtrlPkt_Empty =
{
    {
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 }
    },
    {
        { { NULL, NULL }, 0 },
        { { NULL, NULL }, 0 }
    },
    { NULL, NULL },
    NULL,
    NULL,
    0,
    0,
    0,
};

static uint8_t CfyE_MAC_DA_CDP_VTP[] =
{
    0x01, 0x00, 0x0C, 0xCC, 0xCC, 0xCC
};

static uint8_t CfyE_MAC_DA_LLDP[] =
{
    0x01, 0x80, 0xC2, 0x00, 0x00, 0x00
};

static uint8_t CfyE_MAC_DA_Match1[] =
{
    0xE4, 0xDF, 0x98, 0x10, 0x22, 0x64
};

static uint8_t CfyE_MAC_DA_Match2[] =
{
    0x78, 0x68, 0x58, 0x48, 0x38, 0x28
};

static uint8_t CfyE_MAC_DA_Range1B[] =
{
    0x78, 0x88, 0x98, 0xA8, 0xB8, 0xC8
};
static uint8_t CfyE_MAC_DA_Range1E[] =
{
    0x78, 0x88, 0x98, 0xA8, 0xB8, 0xCA
};

static uint8_t CfyE_MAC_DA_Range2B[] =
{
    0x78, 0x9A, 0xBC, 0xCD, 0x00, 0x55
};

static uint8_t CfyE_MAC_DA_Range2E[] =
{
    0x78, 0x9A, 0xBC, 0xCD, 0x00, 0x58
};

static CfyE_ControlPacket_t CfyECtrlPkt_ForGenTestPurpose =
{
    {
        { CfyE_MAC_DA_Match1, 0 },
        { NULL, 0x8809 },
        { CfyE_MAC_DA_Match2, 0x7886 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
    },
    {
        { { CfyE_MAC_DA_Range1B, CfyE_MAC_DA_Range1E }, 0x6872 },
        { { NULL, NULL }, 0 }
    },
    { CfyE_MAC_DA_Range2B, CfyE_MAC_DA_Range2E },
    CfyE_MAC_DA_LLDP,
    CfyE_MAC_DA_CDP_VTP,
    0x00000205,
    0x801D0205,
    0x01D0205,
};

static CfyE_ControlPacket_t CfyECtrlPkt_TestPrimary =
{
    {
        { CfyE_MAC_DA_Match1, 0 },
        { NULL, 0x8809 },
        { CfyE_MAC_DA_Match2, 0x7886 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
        { NULL, 0 },
    },
    {
        { { CfyE_MAC_DA_Range1B, CfyE_MAC_DA_Range1E }, 0x6872 },
        { { NULL, NULL }, 0 }
    },
    { CfyE_MAC_DA_Range2B, CfyE_MAC_DA_Range2E },
    CfyE_MAC_DA_LLDP,
    CfyE_MAC_DA_CDP_VTP,
    0x00000205,
    0x801D0205,
    0x001d0205,
};

static CfyE_EOPConf_t CfyE_EOPConf_Enable =
{
    1000,
    {{0x0f, 0}}
};


static CfyE_ECCConf_t CfyE_ECCConf_Enable =
{
    1,
    1,
};

static Test_Case_CfyE_Channel_t CfyE_Channel1_LowLatency =
{
    /* Channel number */
    1,

    /* Device settings */
    {
        /* Bypass settings */
        &CfyEDevCtrl_LowLatency,

        /* Control packet detection settings */
        &CfyECtrlPkt_Empty,

        /* Header parser control */
        NULL,

        /* Statistics control */
        &CfyEStatCtrl_NoResetNoThreshold,

        /* EOP config */
        NULL,

        /* ECC config */
        NULL,
    }
};

static Test_Case_CfyE_Channel_t CfyE_Channel0_MACsecSCI_StatThreshold =
{
    /* Channel number */
    0,

    /* Device settings */
    {
        /* Bypass settings */
        &CfyEDevCtrl_DefaultP0,

        /* Control packet detection settings */
        NULL,

        /* Header parser control */
        &CfyEParser_SecTAG_MACsecNoSCI,

        /* Statistics control */
        &CfyEStatCtrl_ResetThreshold,

        /* EOP config */
        &CfyE_EOPConf_Enable,

        /* ECC config */
        &CfyE_ECCConf_Enable,
    }
};

static Test_Case_CfyE_Channel_t CfyE_Channel0_NoEnc =
{
    /* Channel number */
    0,

    /* Device settings */
    {
        /* Bypass settings */
        &CfyEDevCtrl_DefaultP0,

        /* Control packet detection settings */
        &CfyECtrlPkt_ForGenTestPurpose,

        /* Header parser control */
        NULL,

        /* Statistics control */
        NULL,

        /* EOP config */
        NULL,

        /* ECC config */
        NULL,
    }
};

static Test_Case_CfyE_Channel_t CfyE_Channel0_MACsecSCI =
{
    /* Channel number */
    0,

    /* Device settings */
    {
        /* Bypass settings */
        &CfyEDevCtrl_DefaultP0,

        /* Control packet detection settings */
        &CfyECtrlPkt_TestPrimary,

        /* Header parser control */
        &CfyEParser_SecTAG_MACsecNoSCI,

        /* Statistics control */
        &CfyEStatCtrl_ResetThreshold,

        /* EOP config */
        NULL,

        /* ECC config */
        NULL,
    }
};

static Test_Case_CfyE_Channel_t CfyE_Channel_MultipleChannelReconfig_MACsecSCI[] =
{
    {
        /* Channel number */
        0,

        /* Device settings */
        {
            /* Bypass settings */
            NULL,/*&CfyEDevCtrl_DefaultP0, */

            /* Control packet detection settings */
            NULL,

            /* Header parser control */
            &CfyEParser_SecTAG_MACsecNoSCI,

            /* Statistics control */
            &CfyEStatCtrl_ResetNoThreshold,

            /* EOP config */
            NULL,

            /* ECC config */
            NULL,
        }
    },
    {
        /* Channel number */
        1,

        /* Device settings */
        {
            /* Bypass settings */
            NULL,/*&CfyEDevCtrl_DefaultP0, */

            /* Control packet detection settings */
            NULL,

            /* Header parser control */
            &CfyEParser_SecTAG_MACsecNoSCI,

            /* Statistics control */
            &CfyEStatCtrl_ResetNoThreshold,

            /* EOP config */
            NULL,

            /* ECC config */
            NULL,
        }
    },
    {
        /* Channel number */
        2,

        /* Device settings */
        {
            /* Bypass settings */
            NULL,/*&CfyEDevCtrl_DefaultP0, */

            /* Control packet detection settings */
            NULL,

            /* Header parser control */
            &CfyEParser_SecTAG_MACsecNoSCI,

            /* Statistics control */
            &CfyEStatCtrl_ResetNoThreshold,

            /* EOP config */
            NULL,

            /* ECC config */
            NULL,
        }
    },
    {
        /* Channel number */
        3,

        /* Device settings */
        {
            /* Bypass settings */
            NULL,/*&CfyEDevCtrl_DefaultP0, */

            /* Control packet detection settings */
            NULL,

            /* Header parser control */
            &CfyEParser_SecTAG_MACsecNoSCI,

            /* Statistics control */
            &CfyEStatCtrl_ResetNoThreshold,

            /* EOP config */
            NULL,

            /* ECC config */
            NULL,
        }
    }
};

#if defined(TEST_MACSEC_VXLAN_ENABLE)
static Test_Case_CfyE_Channel_t CfyE_Channel0_VxLAN =
{
    /* Channel number */
    0,

    /* Device settings */
    {
        /* Bypass settings */
        &CfyEDevCtrl_VxLAN,

        /* Control packet detection settings */
        &CfyECtrlPkt_TestPrimary,

        /* Header parser control */
        &CfyEParser_VxLAN,

        /* Statistics control */
        &CfyEStatCtrl_ResetThreshold,

        /* EOP config */
        NULL,

        /* ECC config */
        NULL,
    }
};

#endif

#if defined(TEST_IPSEC_ENABLE)
static Test_Case_CfyE_Channel_t CfyE_Channel0_IPsec =
{
    /* Channel number */
    0,

    /* Device settings */
    {
        &CfyEDevCtrl_IPsec_DefaultP0,

        /* Control packet detection settings */
        NULL,

        /* Header parser control */
        &CfyE_HeaderParser_IPsec,

        /* Statistics control */
        NULL,/*&CfyEStatCtrl_ResetNoThreshold */

        /* EOP config */
        NULL,

        /* ECC config */
        NULL,
    }
};


static Test_Case_CfyE_Channel_t CfyE_Channel0_MultiSA_IPsec_Egress_Test =
{
        /* Channel number */
        0,

        /* Device settings */
        {
            &CfyEDevCtrl_IPsec_DefaultP0,

            /* Control packet detection settings */
            NULL,

            /* Header parser control */
            &CfyE_HeaderParser_IPsec,

            /* Statistics control */
            NULL,/*&CfyEStatCtrl_ResetNoThreshold */

            /* EOP config */
            NULL,

            /* ECC config */
            NULL,
        }
};


static Test_Case_CfyE_Channel_t CfyE_Channel0_MultiSA_IPsec_Egress[] =
{
    {
        /* Channel number */
        0,

        /* Device settings */
        {
            &CfyEDevCtrl_IPsec_DefaultP0,

            /* Control packet detection settings */
            NULL,

            /* Header parser control */
            &CfyE_HeaderParser_IPsec,

            /* Statistics control */
            NULL,/*&CfyEStatCtrl_ResetNoThreshold */

            /* EOP config */
            NULL,

            /* ECC config */
            NULL,
        }
    },

    {
        /* Channel number */
        0,

        /* Device settings */
        {
            &CfyEDevCtrl_IPsec_DefaultP0,

            /* Control packet detection settings */
            NULL,

            /* Header parser control */
            &CfyE_HeaderParser_IPsec,

            /* Statistics control */
            NULL,/*&CfyEStatCtrl_ResetNoThreshold */

            /* EOP config */
            NULL,

            /* ECC config */
            NULL,
        }
    },
};


static Test_Case_CfyE_Channel_t CfyE_Channel0_IPsecMPLS =
{
    /* Channel number */
    0,

    /* Device settings */
    {
        &CfyEDevCtrl_IPsec_DefaultP0,

        /* Control packet detection settings */
        NULL,

        /* Header parser control */
        &CfyE_HeaderParser_IPsecMPLS,

        /* Statistics control */
        NULL,/*&CfyEStatCtrl_ResetNoThreshold */

        /* EOP config */
        NULL,

        /* ECC config */
        NULL,
    }
};

static Test_Case_CfyE_Channel_t CfyE_Channel0_IPsecVLAN =
{
    /* Channel number */
    0,

    /* Device settings */
    {
        &CfyEDevCtrl_IPsec_DefaultP0,

        /* Control packet detection settings */
        NULL,

        /* Header parser control */
        &CfyE_HeaderParser_IPsecVLAN,

        /* Statistics control */
        NULL,

        /* EOP config */
        NULL,

        /* ECC config */
        NULL,
    }
};

static Test_Case_CfyE_Channel_t CfyE_Channel0_IPsec_Ingress =
{
    /* Channel number */
    0,

    /* Device settings */
    {
        &CfyEDevCtrl_IPsec_DefaultP0,

        /* Control packet detection settings */
        NULL,

        /* Header parser control */
        &CfyE_HeaderParser_IPsecIngress,

        /* Statistics control */
        NULL,

        /* EOP config */
        NULL,

        /* ECC config */
        NULL,
    }
};

static Test_Case_CfyE_Channel_t CfyE_Channel0_IPsecIngressVLAN =
{
    /* Channel number */
    0,

    /* Device settings */
    {
        &CfyEDevCtrl_IPsec_DefaultP0,

        /* Control packet detection settings */
        NULL,

        /* Header parser control */
        &CfyE_HeaderParser_IPsecIngressVLAN,

        /* Statistics control */
        NULL,/*&CfyEStatCtrl_ResetNoThreshold */

        /* EOP config */
        NULL,

        /* ECC config */
        NULL,
    }
};

static Test_Case_CfyE_Channel_t CfyE_Channel0_IPsecIngressMPLS =
{
    /* Channel number */
    0,

    /* Device settings */
    {
        &CfyEDevCtrl_IPsec_DefaultP0,

        /* Control packet detection settings */
        NULL,

        /* Header parser control */
        &CfyE_HeaderParser_IPsecIngressMPLS,

        /* Statistics control */
        &CfyEStatCtrl_IPsecIngressMPLS,

        /* EOP config */
        NULL,

        /* ECC config */
        NULL,
    }
};

static Test_Case_CfyE_Channel_t CfyE_Channel0_IPsec_Ingress_LateCheck =
{
    /* Channel number */
    0,

    /* Device settings */
    {
        &CfyEDevCtrl_IPsec_DefaultP0,

        /* Control packet detection settings */
        NULL,

        /* Header parser control */
        &CfyE_HeaderParser_IPsecIngress,

        /* Statistics control */
        NULL,

        /* EOP config */
        NULL,

        /* ECC config */
        NULL,
    }
};

static Test_Case_CfyE_Channel_t CfyE_Channel_Egress_IPsec_MACsec[] =
{
    {
        /* Channel number */
        0,

        /* Device settings */
        {
            &CfyEDevCtrl_IPsec_DefaultP0,

            /* Control packet detection settings */
            NULL,

            /* Header parser control */
            &CfyE_HeaderParser_IPsec,

            /* Statistics control */
            NULL,/*&CfyEStatCtrl_ResetNoThreshold */

            /* EOP config */
            NULL,

            /* ECC config */
            NULL,
        }
    },

    {
        /* Channel number */
        1,

        /* Device settings */
        {
            &CfyEDevCtrl_DefaultP0,

            /* Control packet detection settings */
            NULL,

            /* Header parser control */
            &CfyEParser_SecTAG_MACsecNoSCI,

            /* Statistics control */
            NULL,

            /* EOP config */
            NULL,

            /* ECC config */
            NULL,
        }
    },
};


static Test_Case_CfyE_Channel_t CfyE_Channel_IPsec_MACsec_Ingress[] =
{
    {
        /* Channel number */
        0,

        /* Device settings */
        {
            &CfyEDevCtrl_IPsec_DefaultP0,

            /* Control packet detection settings */
            NULL,

            /* Header parser control */
            &CfyE_HeaderParser_IPsecIngress,

            /* Statistics control */
            NULL,

            /* EOP config */
            NULL,

            /* ECC config */
            NULL,
        }
    },

    {
        /* Channel number */
        1,

        /* Device settings */
        {
            /* Bypass settings */
            NULL, /* &CfyEDevCtrl_Default, */

            /* Control packet detection settings */
            NULL,

            /* Header parser control */
            &CfyEParser_SecTAG_MACsecNoSCI,

            /* Statistics control */
            NULL, /* &CfyEStatCtrl_ResetNoThreshold, */

            /* EOP config */
            NULL,

            /* ECC config */
            NULL,
        }
    },
};

static Test_Case_CfyE_Channel_t CfyE_Channel0_MultiSA_IPsec_Ingress[] =
{
    {
        /* Channel number */
        0,

        /* Device settings */
        {
            &CfyEDevCtrl_IPsec_DefaultP0,

            /* Control packet detection settings */
            NULL,

            /* Header parser control */
            &CfyE_HdrParser_IPsecIngress,

            /* Statistics control */
            NULL,

            /* EOP config */
            NULL,

            /* ECC config */
            NULL,
        }
    },

    {
        /* Channel number */
        0,

        /* Device settings */
        {
            &CfyEDevCtrl_IPsec_DefaultP0,

            /* Control packet detection settings */
            NULL,

            /* Header parser control */
            &CfyE_HdrParser_IPsecIngress,

            /* Statistics control */
            NULL,

            /* EOP config */
            NULL,

            /* ECC config */
            NULL,
        }
    },

            {
        /* Channel number */
        0,

        /* Device settings */
        {
            &CfyEDevCtrl_IPsec_DefaultP0,

            /* Control packet detection settings */
            NULL,

            /* Header parser control */
            &CfyE_HdrParser_IPsecIngress,

            /* Statistics control */
            NULL,

            /* EOP config */
            NULL,

            /* ECC config */
            NULL,
        }
    },
};


static Test_Case_CfyE_Channel_t CfyE_Channel0_ReplayFail_IPsec_Ingress[] =
{
    {
        /* Channel number */
        0,

        /* Device settings */
        {
            &CfyEDevCtrl_IPsec_DefaultP0,

            /* Control packet detection settings */
            NULL,

            /* Header parser control */
            &CfyE_HdrParser_IPsecIngress,

            /* Statistics control */
            NULL,

            /* EOP config */
            NULL,

            /* ECC config */
            NULL,
        }
    },
};
#endif

static Test_Case_CfyE_Channel_t CfyE_Channel0_VLAN_1Q_MACsecSCI =
{
    /* Channel number */
    0,

    /* Device settings */
    {
        /* Bypass settings */
        &CfyEDevCtrl_DefaultP0,

        /* Control packet detection settings */
        NULL,

        /* Header parser control */
        &CfyEParser_VLAN_1Q_MACsecNoSCI,

        /* Statistics control */
        NULL,/*&CfyEStatCtrl_ResetNoThreshold */

        /* EOP config */
        NULL,

        /* ECC config */
        NULL,
    }
};


static Test_Case_CfyE_Channel_t CfyE_Channel0_VLAN_QinQ_MACsecSCI =
{
    /* Channel number */
    0,

    /* Device settings */
    {
        /* Bypass settings */
        &CfyEDevCtrl_DefaultP0,

        /* Control packet detection settings */
        NULL,

        /* Header parser control */
        &CfyEParser_VLAN_QinQ_MACsecNoSCI,

        /* Statistics control */
        NULL,/*&CfyEStatCtrl_ResetNoThreshold */

        /* EOP config */
        NULL,

        /* ECC config */
        NULL,
    }
};

#define CFYE_CHANNELN_VLAN_1Q_MACSECSCI(n)                                   \
{                                                                           \
    /* Channel number */                                                    \
    n,                                                                      \
                                                                            \
    /* Device settings */                                                   \
    {                                                                       \
        /* Bypass settings */                                               \
        NULL,                                                               \
                                                                            \
        /* Control packet detection settings */                             \
        &CfyECtrlPkt_TestPrimary,                                           \
                                                                            \
        /* Header parser control */                                         \
        &CfyEParser_VLAN_1Q_MACsecNoSCI,                                    \
                                                                            \
        /* Statistics control */                                            \
        &CfyEStatCtrl_ResetThreshold,                                       \
                                                                            \
        /* EOP Config */                                                    \
        NULL,                                                               \
                                                                            \
        /* ECC Config */                                                    \
        NULL,                                                               \
    }                                                                       \
}

static Test_Case_CfyE_Channel_t CfyE_Channels_VLAN_1Q_MACsecSCI[] =
{
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(0),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(1),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(2),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(3),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(4),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(5),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(6),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(7),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(8),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(9),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(10),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(11),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(12),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(13),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(14),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(15),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(16),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(17),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(18),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(19),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(20),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(21),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(22),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(23),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(24),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(25),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(26),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(27),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(28),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(29),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(30),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(31),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(32),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(33),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(34),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(35),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(36),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(37),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(38),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(39),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(40),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(41),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(42),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(43),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(44),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(45),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(46),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(47),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(48),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(49),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(50),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(51),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(52),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(53),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(54),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(55),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(56),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(57),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(58),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(59),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(60),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(61),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(62),
    CFYE_CHANNELN_VLAN_1Q_MACSECSCI(63),
};

static Test_Case_CfyE_vPort_t CfyE_vPort_LowLatencyBypass =
{
    /* fUpdate */
    false,

    /* vPortId */
    0,

    /* General vPort Policy */
    Common_CfyE_vPort_Policy(12, 0, false, false, 0)
};

static Test_Case_CfyE_vPort_t CfyE_vPort_Untagged_NoEnc =
{
    /* fUpdate */
    false,

    /* vPortId */
    0,

    /* General vPort Policy */
    Common_CfyE_vPort_Policy(0, 0, false, false, 0)
};

static Test_Case_CfyE_vPort_t CfyE_vPort_Untagged_Egress_MACsec_bn =
{
    /* fUpdate */
    false,

    /* vPortId */
    0,

    /* General vPort Policy */
    Common_CfyE_vPort_Policy(12, 0, false, false, 3)
};

static Test_Case_CfyE_vPort_t CfyE_vPort_Untagged_Ingress_MACsec_bn =
{
    /* fUpdate */
    false,

    /* vPortId */
    0,

    /* General vPort Policy */
    Common_CfyE_vPort_Policy(12, 0, false, false, 0)
};


static Test_Case_CfyE_vPort_t CfyE_vPort_MultipleChannels_Egress_UntaggedMACsec[] =
{
    {
        /* fUpdate */
        false,

        /* vPortId */
        0,

        /* General vPort Policy */
        Common_CfyE_vPort_Policy(12, 0, false, false, 3)
    },
    {
        /* fUpdate */
        false,

        /* vPortId */
        1,

        /* General vPort Policy */
        Common_CfyE_vPort_Policy(12, 0, false, false, 3)
    },
    {
        /* fUpdate */
        false,

        /* vPortId */
        2,

        /* General vPort Policy */
        Common_CfyE_vPort_Policy(12, 0, false, false, 3)
    },
    {
        /* fUpdate */
        false,

        /* vPortId */
        3,

        /* General vPort Policy */
        Common_CfyE_vPort_Policy(12, 0, false, false, 3)
    }
};

static Test_Case_CfyE_vPort_t CfyE_vPort_MultipleChannels_Ingress_UntaggedMACsec[] =
{
    {
        /* fUpdate */
        false,

        /* vPortId */
        0,

        /* General vPort Policy */
        Common_CfyE_vPort_Policy(12, 0, false, false, 0)
    },
    {
        /* fUpdate */
        false,

        /* vPortId */
        1,

        /* General vPort Policy */
        Common_CfyE_vPort_Policy(12, 0, false, false, 0)
    },
    {
        /* fUpdate */
        false,

        /* vPortId */
        2,

        /* General vPort Policy */
        Common_CfyE_vPort_Policy(12, 0, false, false, 0)
    },
    {
        /* fUpdate */
        false,

        /* vPortId */
        3,

        /* General vPort Policy */
        Common_CfyE_vPort_Policy(12, 0, false, false, 0)
    }
};

static Test_Case_CfyE_vPort_t CfyE_vPort_VLAN_Egress_MACsec_O1_update[] =
{
    {
        /* fUpdate */
        false,

        /* vPortId */
        0,

        /* General vPort Policy */
        Common_CfyE_vPort_Policy(0, 0, false, false, 3)
    },
    {
        /* fUpdate */
        true,

        /* vPortId */
        0,

        /* General vPort Policy */
        Common_CfyE_vPort_Policy(12, 0, false, false, 3)
    }
};

#if defined(TEST_IPSEC_ENABLE)
static Test_Case_CfyE_vPort_t CfyE_vPort_Egress_IPsec =
{
    /* fUpdate */
    false,

    /* vPortId */
    0,

    /* General vPort Policy */
    Common_CfyE_vPort_Policy(0, 0, false, false, 1)
};


static Test_Case_CfyE_vPort_t CfyE_vPort_MultiSA_IPsec_Egress_Test =
{
        /* fUpdate */
        false,

        /* vPortId */
        0,

        /* General vPort Policy */
        Common_CfyE_vPort_Policy(0, 0, false, false, 1)
};

static Test_Case_CfyE_vPort_t CfyE_vPort_MultiSA_IPsec_Egress[] =
{
    {
        /* fUpdate */
        false,

        /* vPortId */
        0,

        /* General vPort Policy */
        Common_CfyE_vPort_Policy(0, 0, false, false, 1)
    },

    {
        /* fUpdate */
        false,

        /* vPortId */
        1,

        /* General vPort Policy */
        Common_CfyE_vPort_Policy(0, 0, false, false, 1)
    },
};

static Test_Case_CfyE_vPort_t CfyE_vPort_Egress_IPsecMPLS =
{
    /* fUpdate */
    false,

    /* vPortId */
    0,

    /* General vPort Policy */
    Common_CfyE_vPort_Policy(0, 0, false, false, 1)
};

static Test_Case_CfyE_vPort_t CfyE_vPort_Ingress_IPsec =
{
    /* fUpdate */
    false,

    /* vPortId */
    0,

    /* General vPort Policy */
    Common_CfyE_vPort_Policy(0, 0, false, false, 1)
};

static Test_Case_CfyE_vPort_t CfyE_vPort_Egress_IPsec_MACsec[] =
{
    {
        /* fUpdate */
        false,

        /* vPortId */
        0,

        /* General vPort Policy */
        Common_CfyE_vPort_Policy(0, 0, false, false, 1)
    },

    {
        /* fUpdate */
        false,

        /* vPortId */
        1,

        /* General vPort Policy */
        Common_CfyE_vPort_Policy(12, 0, false, false, 3)
    },
};

static Test_Case_CfyE_vPort_t CfyE_vPort_IPsec_MACsec_Ingress[] =
{
    {
        /* fUpdate */
        false,

        /* vPortId */
        0,

        /* General vPort Policy */
        Common_CfyE_vPort_Policy(0, 0, false, false, 1)
    },
    {
        /* fUpdate */
        false,

        /* vPortId */
        1,

        /* General vPort Policy */
        Common_CfyE_vPort_Policy(12, 0, false, false, 3)
    },
};

static Test_Case_CfyE_vPort_t CfyE_vPort_ReplayFail_IPsec_Ingress[] =
{
    {
        /* fUpdate */
        false,

        /* vPortId */
        0,

        /* General vPort Policy */
        Common_CfyE_vPort_Policy(0, 0, false, false, 1)
    },

    {
        /* fUpdate */
        false,

        /* vPortId */
        1,

        /* General vPort Policy */
        Common_CfyE_vPort_Policy(0, 0, false, false, 1)
    },
};

static Test_Case_CfyE_vPort_t CfyE_vPort_MultiSA_IPsec_Ingress[] =
{
    {
        /* fUpdate */
        false,

        /* vPortId */
        0,

        /* General vPort Policy */
        Common_CfyE_vPort_Policy(0, 0, false, false, 1)
    },

    {
        /* fUpdate */
        false,

        /* vPortId */
        1,

        /* General vPort Policy */
        Common_CfyE_vPort_Policy(0, 0, false, false, 1)
    },

    {
        /* fUpdate */
        false,

        /* vPortId */
        2,

        /* General vPort Policy */
        Common_CfyE_vPort_Policy(0, 0, false, false, 1)
    },
};

#endif

static Test_Case_CfyE_vPort_t CfyE_vPort_VLAN_Egress_MACsec_O2 =
{
    /* fUpdate */
    false,

    /* vPortId */
    0,

    /* General vPort Policy */
    Common_CfyE_vPort_Policy(16, 0, false, false, 3)
};

static Test_Case_CfyE_vPort_t CfyE_vPort_VLAN_Egress_MACsec_O3 =
{
    /* fUpdate */
    false,

    /* vPortId */
    0,

    /* General vPort Policy */
    Common_CfyE_vPort_Policy(20, 0, false, false, 3)
};

static Test_Case_CfyE_vPort_t CfyE_vPort_VLAN_Egress_MACsec_O4 =
{
    /* fUpdate */
    false,

    /* vPortId */
    0,

    /* General vPort Policy */
    Common_CfyE_vPort_Policy(24, 0, false, false, 3)
};

static Test_Case_CfyE_vPort_t CfyE_vPort_VLAN_Ingress_MACsec_O1 =
{
    /* fUpdate */
    false,

    /* vPortId */
    0,

    /* General vPort Policy */
    Common_CfyE_vPort_Policy(12, 0, false, false, 0)
};

static Test_Case_CfyE_vPort_t CfyE_vPort_VLAN_Ingress_MACsec_O2 =
{
    /* fUpdate */
    false,

    /* vPortId */
    0,

    /* General vPort Policy */
    Common_CfyE_vPort_Policy(16, 0, false, false, 0)
};

static Test_Case_CfyE_vPort_t CfyE_vPort_VLAN_Ingress_MACsec_O3 =
{
    /* fUpdate */
    false,

    /* vPortId */
    0,

    /* General vPort Policy */
    Common_CfyE_vPort_Policy(20, 0, false, false, 0)
};

static Test_Case_CfyE_vPort_t CfyE_vPort_VLAN_Ingress_MACsec_O4 =
{
    /* fUpdate */
    false,

    /* vPortId */
    0,

    /* General vPort Policy */
    Common_CfyE_vPort_Policy(24, 0, false, false, 0)
};

Test_Case_CfyE_Data_t CfyE_Data_LowLatencyBypass =
{
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel1_LowLatency,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_LowLatencyBypass,

    /* Number of CfyE rules */
    0,

    /* CfyE rule data */
    NULL,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* CfyE MTT data */
    NULL,
};

Test_Case_CfyE_Data_t CfyE_Data_Untagged_Egress_NoEnc =
{
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_NoEnc,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_Untagged_NoEnc,

    /* Number of CfyE rules */
    1,

    /* CfyE rule data */
    &CfyE_Rule_Untagged_MACsec_bn,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* CfyE MTT data */
    NULL,
};

Test_Case_CfyE_Data_t CfyE_Data_Untagged_Egress_MACsec_bn =
{
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_MACsecSCI_StatThreshold,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_Untagged_Egress_MACsec_bn,

    /* Number of CfyE rules */
    1,

    /* CfyE rule data */
    &CfyE_Rule_Untagged_MACsec_bn,

    /* CfyE global notification events */
    (CFYE_EVENT_STAT_TCAM_THR|CFYE_EVENT_ECC_ERR),

    /* CfyE channel notification events */
    (CFYE_EVENT_CHAN_DATA_PACKET),

    /* CfyE MTT data */
    NULL,
};

Test_Case_CfyE_Data_t CfyE_Data_Untagged_Ingress_NoEnc =
{
    /* Number of CfyE device settings */
    0,

    /* CfyE device settings data */
    NULL,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_Untagged_Ingress_MACsec_bn,

    /* Number of CfyE rules */
    1,

    /* CfyE rule data */
    &CfyE_Rule_Untagged_MACsec_bn,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* CfyE MTT data */
    NULL,
};

Test_Case_CfyE_Data_t CfyE_Data_Untagged_Ingress_MACsec_bn =
{
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_MACsecSCI,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_Untagged_Ingress_MACsec_bn,

    /* Number of CfyE rules */
    1,

    /* CfyE rule data */
    &CfyE_Rule_Untagged_MACsec_bn,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* CfyE MTT data */
    NULL,
};

#if defined(TEST_MACSEC_VXLAN_ENABLE)
Test_Case_CfyE_Data_t CfyE_Data_VxLAN_IPv6_Egress_MACsec =
{
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_VxLAN,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_Untagged_Egress_MACsec_bn,

    /* Number of CfyE rules */
    2,

    /* CfyE rule data */
    CfyE_Rule_VxLAN,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* MTT data */
    NULL,
};

Test_Case_CfyE_Data_t CfyE_Data_VxLAN_IPv4_Egress_MACsec =
    {
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_VxLAN,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_VLAN_Egress_MACsec_O2,

    /* Number of CfyE rules */
    2,

    /* CfyE rule data */
    CfyE_Rule_VxLAN,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* MTT data */
    NULL,
};

Test_Case_CfyE_Data_t CfyE_Data_VxLAN_IPv6_Ingress_MACsec =
    {
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_VxLAN,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_Untagged_Ingress_MACsec_bn,

    /* Number of CfyE rules */
    2,

    /* CfyE rule data */
    CfyE_Rule_VxLAN,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* MTT data */
    NULL,
};

Test_Case_CfyE_Data_t CfyE_Data_VxLAN_IPv4_Ingress_MACsec =
    {
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_VxLAN,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_VLAN_Ingress_MACsec_O2,

    /* Number of CfyE rules */
    2,

    /* CfyE rule data */
    CfyE_Rule_VxLAN,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* MTT data */
    NULL,
};

#endif

#if defined(TEST_IPSEC_ENABLE)
Test_Case_CfyE_Data_t CfyE_Data_Egress_IPsec_O1 =
{
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_IPsec,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_Egress_IPsec,

    /* Number of CfyE rules */
    0,

    /* CfyE rule data */
    NULL,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* MTT data */
    NULL,
};


Test_Case_CfyE_Data_t CfyE_Data_Egress_IPsec_UDP =
{
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_IPsec,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_Egress_IPsec,

    /* Number of CfyE rules */
    0,

    /* CfyE rule data */
    NULL,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* MTT data */
    NULL,
};


Test_Case_CfyE_Data_t CfyE_Data_MultiSA_IPsec_Egress =
{
    /* Number of CfyE device settings */
    2,

    /* CfyE device settings data */
    CfyE_Channel0_MultiSA_IPsec_Egress,

    /* Number of CfyE vPorts */
    2,

    /* CfyE vPort data */
    CfyE_vPort_MultiSA_IPsec_Egress,

    /* Number of CfyE rules */
    2,

    /* CfyE rule data */
    CfyE_Rule_MultiSA_IPsec_Egress,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* MTT data */
    NULL,
};

Test_Case_CfyE_Data_t CfyE_Data_MultiSA_IPsec_Egress_Test =
{
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_MultiSA_IPsec_Egress_Test,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_MultiSA_IPsec_Egress_Test,

    /* Number of CfyE rules */
    1,

    /* CfyE rule data */
    &CfyE_Rule_MultiSA_IPsec_Egress_Test,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* MTT data */
    NULL,
};

Test_Case_CfyE_Data_t CfyE_Data_Egress_IPsecMPLS =
{
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_IPsecMPLS,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_Egress_IPsecMPLS,

    /* Number of CfyE rules */
    1,

    /* CfyE rule data */
    &CfyE_Rule_MPLS_Egress_IPsec,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* MTT data */
    NULL,
};

Test_Case_CfyE_Data_t CfyE_Data_Egress_IPsecVLAN =
{
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_IPsecVLAN,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_Egress_IPsecMPLS,

    /* Number of CfyE rules */
    1,

    /* CfyE rule data */
    &CfyE_Rule_VLAN_Egress_IPsec,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* MTT data */
    NULL,
};

static CfyE_MTT_t CfyE_MTT_Entries_IPSec_Ingress =
{
    /* Key */
    {
        /* channel mask */
        {
            {0x1, 0},
        },

        true,  /* IPv6 */
        0,     /* TagLabel */
        0,     /* TagLabe2 */
        0,     /* fIPHdrValid */
        false,
    },

    /* mask bits for matching */
    {
        {
            {0xffffffff, 0xffffffff}
        },

        true,
        0,
        0,
        0,
        true,
    },

    {   /* IP address */
        0x870c0667,
        0xfe5f7a08,
        0x6ab85439,
        0x23ef7fdd,
    },

    /* Address mask */
    {
        0xffffffff,
        0xffffffff,
        0xffffffff,
        0xffffffff,
    }
};

static CfyE_MTT_t CfyE_MTT_Entries_IPSec_Ingress_LateCheck =
{
    /* Key */
    {
        /* channel mask */
        {
            {0x1, 0},
        },

        true,  /* IPv6 */
        0,     /* TagLabel */
        0,     /* TagLabe2 */
        0,     /* fIPHdrValid */
        false,
    },

    /* mask bits for matching */
    {
        {
            {0xffffffff, 0xffffffff}
        },

        true,
        0,
        0,
        0,
        true,
    },

    {   /* IP address */
        0,
        0,
        0,
        0,
    },

    /* Address mask */
    {
        0,
        0,
        0,
        0,
    }
};


static CfyE_MTT_t CfyE_MTT_Entries_IPSecIngressVLAN =
{
    /* Key */
    {
        /* channel mask */
        {
            {0, 0},
        },

        false, /* IPv6 */
        0,     /* TagLabel */
        0,     /* TagLabe2 */
        0,     /* fIPHdrValid */
        false,
    },

    /* mask bits for matching */
    {
        {
            {0, 0}
        },

        true,
        0,
        0,
        0,     /* fIPHdrValid */
        true,
    },

    {   /* IP address */
        0,
        0,
        0,
        0,
    },

    /* Address mask */
    {
        0,
        0,
        0,
        0,
    }
};

static CfyE_MTT_t CfyE_MTT_Entries_IPSecIngressMPLS =
{
    /* Key */
    {
        /* channel mask */
        {
            {0, 0},
        },

        false, /* IPv6 */
        0,     /* TagLabel */
        0,     /* TagLabe2 */
        0,     /* fIPHdrValid */
        true,
    },

    /* mask bits for matching */
    {
        {
            {0, 0}
        },

        true,
        0,
        0,
        0,     /* fIPHdrValid */
        true,
    },

    {   /* IP address */
        0,
        0,
        0,
        0,
    },

    /* Address mask */
    {
        0,
        0,
        0,
        0,
    }
};


static CfyE_MTT_t CfyE_MTT_Entries_IPSecIngressUDP =
{
    /* Key */
    {
        /* channel mask */
        {
            {0, 0},
        },

        false, /* IPv6 */
        0,     /* TagLabel */
        0,     /* TagLabe2 */
        0,     /* fIPHdrValid */
        false,
    },

    /* mask bits for matching */
    {
        {
            {0, 0}
        },

        true,
        0,
        0,
        0,     /* fIPHdrValid */
        true,
    },

    {   /* IP address */
        0,
        0,
        0,
        0,
    },

    /* Address mask */
    {
        0,
        0,
        0,
        0,
    }
};

static CfyE_MTT_t CfyE_MTT_Entries_MultiSA_IPsec_Ingress[] =
{
    {
        /* Key */
        {
            /* channel mask */
            {
                {0, 0},
            },

            false, /* IPv6 */
            0,     /* TagLabel */
            0,     /* TagLabe2 */
            0,     /* fIPHdrValid */
            false,
        },

        /* mask bits for matching */
        {
            {
                {0, 0}
            },

            true,
            0,
            0,
            0,     /* fIPHdrValid */
            true,
        },

        {   /* IP address */
            0,
            0,
            0,
            0,
        },

        /* Address mask */
        {
            0,
            0,
            0,
            0,
        }
    },

    {
        /* Key */
        {
            /* channel mask */
            {
                {0, 0},
            },

            false, /* IPv6 */
            0,     /* TagLabel */
            0,     /* TagLabe2 */
            0,     /* fIPHdrValid */
            false,
        },

        /* mask bits for matching */
        {
            {
                {0, 0}
            },

            true,
            0,
            0,
            0,     /* fIPHdrValid */
            true,
        },

        {   /* IP address */
            0,
            0,
            0,
            0,
        },

        /* Address mask */
        {
            0,
            0,
            0,
            0,
        }
    },

    {
        /* Key */
        {
            /* channel mask */
            {
                {0, 0},
            },

            false, /* IPv6 */
            0,     /* TagLabel */
            0,     /* TagLabe2 */
            0,     /* fIPHdrValid */
            false,
        },

        /* mask bits for matching */
        {
            {
                {0, 0}
            },

            true,
            0,
            0,
            0,     /* fIPHdrValid */
            true,
        },

        {   /* IP address */
            0,
            0,
            0,
            0,
        },

        /* Address mask */
        {
            0,
            0,
            0,
            0,
        }
    }
};


static CfyE_MTT_t CfyE_MTT_Rule_IPsecMACsec_Ingress[] =
{
    {
        /* Key */
        {
            /* channel mask */
            {
                {0x1, 0},
            },

            true,  /* IPv6 */
            0,     /* TagLabel */
            0,     /* TagLabe2 */
            0,     /* fIPHdrValid */
            false,
        },

        /* mask bits for matching */
        {
            {
                {0xffffffff, 0xffffffff}
            },

            true,
            0,
            0,
            0,
            true,
        },

        {   /* IP address */
            0x870c0667,
            0xfe5f7a08,
            0x6ab85439,
            0x23ef7fdd,
        },

        /* Address mask */
        {
            0xffffffff,
            0xffffffff,
            0xffffffff,
            0xffffffff,
        }
    }
};

Test_Case_CfyE_MTT_t CfyE_MTT_IPSec_MACsec_Ingress =
{
    1, /* number of MTT entries */

    CfyE_MTT_Rule_IPsecMACsec_Ingress,
};

static CfyE_MTT_t CfyE_MTT_Entries_ReplayFail_IPsec_Ingress[] =
{
    {
        /* Key */
        {
            /* channel mask */
            {
                {0x1, 0},
            },

            true,  /* IPv6 */
            0,     /* TagLabel */
            0,     /* TagLabe2 */
            true,  /* fIPHdrValid */
            false,
        },

        /* mask bits for matching */
        {
            {
                {0xffffffff, 0xffffffff}
            },

            true,
            0,
            0,
            true,
            true,
        },

        {   /* IP address */
            0xc26d7efe,
            0x1f586d37,
            0x89fcd31a,
            0xbe79e4e7,
        },

        /* Address mask */
        {
            0xffffffff,
            0xffffffff,
            0xffffffff,
            0xffffffff,
        }
    },

    {
        /* Key */
        {
            /* channel mask */
            {
                {0, 0},
            },

            false, /* IPv6 */
            0,     /* TagLabel */
            0,     /* TagLabe2 */
            0,     /* fIPHdrValid */
            false,
        },

        /* mask bits for matching */
        {
            {
                {0, 0}
            },

            true,
            0,
            0,
            0,     /* fIPHdrValid */
            true,
        },

        {   /* IP address */
            0,
            0,
            0,
            0,
        },

        /* Address mask */
        {
            0,
            0,
            0,
            0,
        }
    },

    {
        /* Key */
        {
            /* channel mask */
            {
                {0, 0},
            },

            false, /* IPv6 */
            0,     /* TagLabel */
            0,     /* TagLabe2 */
            0,     /* fIPHdrValid */
            false,
        },

        /* mask bits for matching */
        {
            {
                {0, 0}
            },

            true,
            0,
            0,
            0,     /* fIPHdrValid */
            true,
        },

        {   /* IP address */
            0,
            0,
            0,
            0,
        },

        /* Address mask */
        {
            0,
            0,
            0,
            0,
        }
    }
};

Test_Case_CfyE_MTT_t CfyE_MTT_IPSec_Ingress_LateCheck =
{
    1, /* number of MTT entries */

    &CfyE_MTT_Entries_IPSec_Ingress_LateCheck
};

Test_Case_CfyE_MTT_t CfyE_MTT_IPSec_Ingress =
{
    1, /* number of MTT entries */

    &CfyE_MTT_Entries_IPSec_Ingress
};

Test_Case_CfyE_MTT_t CfyE_MTT_IPSec_IngressUDP =
{
    1, /* number of MTT entries */

    &CfyE_MTT_Entries_IPSecIngressUDP
};

Test_Case_CfyE_MTT_t CfyE_MTT_IPSecIngressVLAN =
{
    1, /* number of MTT entries */

    &CfyE_MTT_Entries_IPSecIngressVLAN
};

Test_Case_CfyE_MTT_t CfyE_MTT_IPSecIngressMPLS =
{
    1, /* number of MTT entries */

    &CfyE_MTT_Entries_IPSecIngressMPLS
};

Test_Case_CfyE_MTT_t CfyE_MTT_MultiSA_IPsec_Ingress =
{
    3, /* number of MTT entries */

    CfyE_MTT_Entries_MultiSA_IPsec_Ingress
};

Test_Case_CfyE_MTT_t CfyE_MTT_ReplayFail_IPsec_Ingress =
{
    1, /* number of MTT entries */

    CfyE_MTT_Entries_ReplayFail_IPsec_Ingress
};

Test_Case_CfyE_Data_t CfyE_Data_Ingress_IPsec_O1 =
{
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_IPsec_Ingress,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_Ingress_IPsec,

    /* Number of CfyE rules */
    1,

    /* CfyE rule data */
    &CfyE_Rule_IPsec_Ingress,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* MTT data */
    &CfyE_MTT_IPSec_Ingress,
};

Test_Case_CfyE_Data_t CfyE_Data_Ingress_IPsec_UDP =
{
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_IPsec_Ingress,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_Ingress_IPsec,

    /* Number of CfyE rules */
    1,

    /* CfyE rule data */
    &CfyE_Rule_IPsec_IngressUDP,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* MTT data */
    &CfyE_MTT_IPSec_IngressUDP,
};

Test_Case_CfyE_Data_t CfyE_Data_IPsecIngressVLAN =
{
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_IPsecIngressVLAN,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_Ingress_IPsec,

    /* Number of CfyE rules */
    1,

    /* CfyE rule data */
    &CfyE_Rule_IPsecIngressVLAN,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* MTT data */
    &CfyE_MTT_IPSecIngressVLAN,
};

Test_Case_CfyE_Data_t CfyE_Data_IPsecIngressMPLS =
{
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_IPsecIngressMPLS,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_Ingress_IPsec,

    /* Number of CfyE rules */
    1,

    /* CfyE rule data */
    &CfyE_Rule_IPsecIngressMPLS,

    /* CfyE global notification events */
    (CFYE_EVENT_STAT_TCAM_THR|CFYE_EVENT_ECC_ERR),

    /* CfyE channel notification events */
    0,

    /* MTT data */
    &CfyE_MTT_IPSecIngressMPLS,
};

Test_Case_CfyE_Data_t CfyE_Data_IPsecIngressMPLS_Bypass =
{
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_IPsecIngressMPLS,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_Ingress_IPsec,

    /* Number of CfyE rules */
    1,

    /* CfyE rule data */
    &CfyE_Rule_IPsecIngressMPLS_Bypass,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* MTT data */
    &CfyE_MTT_IPSecIngressMPLS,
};

Test_Case_CfyE_Data_t CfyE_Data_Ingress_IPsec_LateCheck =
{
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_IPsec_Ingress_LateCheck,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_Ingress_IPsec,

    /* Number of CfyE rules */
    1,

    /* CfyE rule data */
    &CfyE_Rule_IPsec_Ingress_LateCheck,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* MTT data */
    &CfyE_MTT_IPSec_Ingress_LateCheck,
};

Test_Case_CfyE_Data_t CfyE_Data_MultiSA_IPsec_Ingress =
{
    /* Number of CfyE device settings */
    3,

    /* CfyE device settings data */
    CfyE_Channel0_MultiSA_IPsec_Ingress,

    /* Number of CfyE vPorts */
    3,

    /* CfyE vPort data */
    CfyE_vPort_MultiSA_IPsec_Ingress,

    /* Number of CfyE rules */
    3,

    /* CfyE rule data */
    CfyE_Rule_MultiSA_IPsec_Ingress,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* MTT data */
    &CfyE_MTT_MultiSA_IPsec_Ingress,
};


static Test_Case_CfyE_Rule_t CfyE_Rule_MultipleChannels_IPsec_MACsec[] =
{
    {
        /* fUpdate */
        false,

        /* Rule ID */
        0,

        /* Rule definition */
        {
            /* Key */
            CfyE_Rule_KeyMask_Other(0, 0, 0),

            /* KeyMask */
            CfyE_Rule_KeyMask_Raw(0x0, 0x00, 0x0, 0, 0),

            /* Data */
            {
                /* MAC address, least significant bytes (3..0) */
                0,
                /* MAC address, most significant bytes (5, 4) */
                00,
                /* Packet data (EtherType, VLAN tag, MPLS label) */
                0x00000000,
                0x00000000
            },

            /* DataMask */
            {
                0xFFFFFFFF,
                0x0000FFFF,
                0x00000000,
                0x00000000
            },

            /* Policy */
            Common_CfyE_Rule_Policy(0, 1, 0, false, false)
        }
    },
    {
        /* fUpdate */
        false,

        /* Rule ID */
        1,

        /* Rule definition */
        {
            /* Key */
            CfyE_Rule_KeyMask_Other(1, 0, 0),

            /* KeyMask */
            CfyE_Rule_KeyMask_Raw(0x0, 0x00, CFYE_RULE_CHANNEL_ID_MASK, 0, 0),

            /* Data */
            {
                /* MAC address, least significant bytes (3..0) */
                0x13D5C584,
                /* MAC address, most significant bytes (5, 4) */
                0x0000ABD2,
                /* Packet data (EtherType, VLAN tag, MPLS label) */
                0x00000000,
                0x00000000
            },

            /* DataMask */
            {
                0xFFFFFFFF,
                0x0000FFFF,
                0x00000000,
                0x00000000
            },

            /* Policy */
            Common_CfyE_Rule_Policy(1, 1, 0, false, false)
        }
    },
};

static Test_Case_CfyE_Rule_t CfyE_Rule_MultiChs_IPsec_MACsec_Ingress[] =
{
    {
        /* fUpdate */
        false,

        /* Rule ID */
        0,

        /* Rule definition */
        {
            /* Key */
            CfyE_Rule_KeyMask_IPSEC_INGRESS(0, 0, 0),

            /* KeyMask */
            CfyE_Rule_KeyMask_Raw(CFYE_RULE_PKT_TYPE_MASK,
                              CFYE_RULE_NUMTAGS_MASK,
                              CFYE_RULE_CHANNEL_ID_MASK, 0, 0),

            /* Data */
            {
                /* MAC address, least significant bytes (3..0) */
                0x19262a3a,

                /* MAC address, most significant bytes (5, 4) */
                0xf7f,

                /* Packet data (EtherType, VLAN tag, MPLS label) */
                0x416bd021,

                0x00000000
            },

            /* DataMask */
            {
                0xffffffff,
                0xffff,
                0xffffffff,
                0xf
            },

            /* Policy */
            Common_CfyE_Rule_Policy(0, 0, 0, false, false)
        }
    },

    {
       /* fUpdate */
       false,

       /* Rule ID */
       1,

       /* Rule definition */
       {
           /* Key */
           CfyE_Rule_KeyMask_Other(1, 0, 0),
           /* KeyMask */
           CfyE_Rule_KeyMask_Raw(CFYE_RULE_PKT_TYPE_MASK, 0x00,
                                 CFYE_RULE_CHANNEL_ID_MASK, 0, 0),
           /* Data */
           {
               /* MAC address, least significant bytes (3..0) */
               0x13D5C584,

               /* MAC address, most significant bytes (5, 4) */
               0x0000ABD2,

               /* Packet data (EtherType, VLAN tag, MPLS label) */
               0x00000000,
               0x00000000
           },

           /* DataMask */
           {
               0xFFFFFFFF,
               0x0000FFFF,
               0x00000000,
               0x00000000
           },

           /* Policy */
           Common_CfyE_Rule_Policy(1, 1, 0, false, false)
       }
   },
};

Test_Case_CfyE_Data_t CfyE_Data_Egress_IPsec_MACsec =
{
    /* Number of CfyE Channel Count */
    2,

    /* CfyE device settings data */
    CfyE_Channel_Egress_IPsec_MACsec,

    /* Number of CfyE vPorts */
    2,

    /* CfyE vPort data */
    CfyE_vPort_Egress_IPsec_MACsec,

    /* Number of CfyE rules */
    2,

    /* CfyE rule data */
    CfyE_Rule_MultipleChannels_IPsec_MACsec,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* MTT data */
    NULL,
};

Test_Case_CfyE_Data_t CfyE_Data_IPsec_MACsec_Ingress =
{
    /* Number of CfyE Channel Count */
    2,

    /* CfyE device settings data */
    CfyE_Channel_IPsec_MACsec_Ingress,

    /* Number of CfyE vPorts */
    2,

    /* CfyE vPort data */
    CfyE_vPort_IPsec_MACsec_Ingress,

    /* Number of CfyE rules */
    2,

    /* CfyE rule data */
    CfyE_Rule_MultiChs_IPsec_MACsec_Ingress,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* MTT data */
    &CfyE_MTT_IPSec_MACsec_Ingress,
};

Test_Case_CfyE_Data_t CfyE_Data_ReplayFail_IPsec_Ingress =
{
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    CfyE_Channel0_ReplayFail_IPsec_Ingress,

    /* Number of CfyE vPorts */
    2,

    /* CfyE vPort data */
    CfyE_vPort_ReplayFail_IPsec_Ingress,

    /* Number of CfyE rules */
    2,

    /* CfyE rule data */
    CfyE_Rule_ReplayFail_IPsec_Ingress,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* MTT data */
    &CfyE_MTT_ReplayFail_IPsec_Ingress,
};
#endif

Test_Case_CfyE_Data_t CfyE_Data_VLAN_1Q_Egress_MACsec_O1 =
{
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_VLAN_1Q_MACsecSCI,

    /* Number of CfyE vPorts */
    2,

    /* CfyE vPort data */
    CfyE_vPort_VLAN_Egress_MACsec_O1_update,

    /* Number of CfyE rules */
    2,

    /* CfyE rule data */
    CfyE_Rule_VLAN_1Q_Egress_MACsec_M2_update,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* CfyE MTT data */
    NULL,
};

Test_Case_CfyE_Data_t CfyE_Data_VLAN_1Q_Egress_MACsec_O2 =
{
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_VLAN_1Q_MACsecSCI,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_VLAN_Egress_MACsec_O2,

    /* Number of CfyE rules */
    2,

    /* CfyE rule data */
    CfyE_Rule_VLAN_1Q_Egress_MACsec_M2_update,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* CfyE MTT data */
    NULL,
};

Test_Case_CfyE_Data_t CfyE_Data_VLAN_1Q_Ingress_MACsec_O1 =
{
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_MACsecSCI,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_VLAN_Ingress_MACsec_O1,

    /* Number of CfyE rules */
    1,

    /* CfyE rule data */
    &CfyE_Rule_VLAN_1Q_Ingress_MACsec_O1,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* CfyE MTT data */
    NULL,
};

Test_Case_CfyE_Data_t CfyE_Data_VLAN_1Q_Ingress_MACsec_O2 =
{
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_VLAN_1Q_MACsecSCI,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_VLAN_Ingress_MACsec_O2,

    /* Number of CfyE rules */
    1,

    /* CfyE rule data */
    &CfyE_Rule_VLAN_1Q_Ingress_MACsec_O2,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* CfyE MTT data */
    NULL,
};

Test_Case_CfyE_Data_t CfyE_Data_VLAN_QinQ_Egress_MACsec_O3 =
{
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_VLAN_QinQ_MACsecSCI,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_VLAN_Egress_MACsec_O3,

    /* Number of CfyE rules */
    1,

    /* CfyE rule data */
    &CfyE_Rule_VLAN_QinQ_Egress_MACsec_M1,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* CfyE MTT data */
    NULL,
};

Test_Case_CfyE_Data_t CfyE_Data_VLAN_QinQ_Ingress_MACsec_O3 =
{
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_VLAN_QinQ_MACsecSCI,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_VLAN_Ingress_MACsec_O3,

    /* Number of CfyE rules */
    1,

    /* CfyE rule data */
    &CfyE_Rule_VLAN_QinQ_Ingress_MACsec_O3,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* CfyE MTT data */
    NULL,
};

Test_Case_CfyE_Data_t CfyE_Data_VLAN_QinQinQ_Egress_MACsec_O4 =
{
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_VLAN_QinQ_MACsecSCI,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_VLAN_Egress_MACsec_O4,

    /* Number of CfyE rules */
    1,

    /* CfyE rule data */
    &CfyE_Rule_VLAN_QinQinQ_Egress_MACsec_M1,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* CfyE MTT data */
    NULL,
};

Test_Case_CfyE_Data_t CfyE_Data_VLAN_QinQinQ_Ingress_MACsec_O4 =
{
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_VLAN_QinQ_MACsecSCI,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_VLAN_Ingress_MACsec_O4,

    /* Number of CfyE rules */
    1,

    /* CfyE rule data */
    &CfyE_Rule_VLAN_QinQinQ_Ingress_MACsec_O4,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* CfyE MTT data */
    NULL,
};

Test_Case_CfyE_Data_t CfyE_Data_CtrlPacket_PriEgress =
{
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_MACsecSCI,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_Untagged_Egress_MACsec_bn,

    /* Number of CfyE rules */
    1,

    /* CfyE rule data */
    &CfyE_Rule_Untagged_MACsec_bn,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* CfyE MTT data */
    NULL,
};

Test_Case_CfyE_Data_t CfyE_Data_CtrlPacket_PriIngress =
{
    /* Number of CfyE device settings */
    1,

    /* CfyE device settings data */
    &CfyE_Channel0_MACsecSCI,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_Untagged_Egress_MACsec_bn,

    /* Number of CfyE rules */
    1,

    /* CfyE rule data */
    &CfyE_Rule_Untagged_MACsec_bn,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* CfyE MTT data */
    NULL,
};

Test_Case_CfyE_Data_t CfyE_Data_LimitsEgress =
{
    /* Number of CfyE device settings */
    64,

    /* CfyE device settings data */
    CfyE_Channels_VLAN_1Q_MACsecSCI,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_VLAN_Egress_MACsec_O2,

    /* Number of CfyE rules */
    2,

    /* CfyE rule data */
    CfyE_Rule_ForLimits_VLAN_1Q_MACsec,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* CfyE MTT data */
    NULL,
};

Test_Case_CfyE_Data_t CfyE_Data_LimitsIngress =
{
    /* Number of CfyE device settings */
    64,

    /* CfyE device settings data */
    CfyE_Channels_VLAN_1Q_MACsecSCI,

    /* Number of CfyE vPorts */
    1,

    /* CfyE vPort data */
    &CfyE_vPort_VLAN_Ingress_MACsec_O2,

    /* Number of CfyE rules */
    2,

    /* CfyE rule data */
    CfyE_Rule_ForLimits_VLAN_1Q_MACsec,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* CfyE MTT data */
    NULL,
};


Test_Case_CfyE_Data_t CfyE_Data_MultipleChannelReconfig_Egress_UntaggedMACsec =
{
    /* Number of CfyE device settings */
    4,

    /* CfyE device settings data */
    CfyE_Channel_MultipleChannelReconfig_MACsecSCI,

    /* Number of CfyE vPorts */
    4,

    /* CfyE vPort data */
    CfyE_vPort_MultipleChannels_Egress_UntaggedMACsec,

    /* Number of CfyE rules */
    4,

    /* CfyE rule data */
    CfyE_Rule_MultipleChannels_UntaggedMACsec,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* CfyE MTT data */
    NULL,
};

Test_Case_CfyE_Data_t CfyE_Data_MultipleChannelReconfig_Ingress_UntaggedMACsec =
{
    /* Number of CfyE device settings */
    4,

    /* CfyE device settings data */
    CfyE_Channel_MultipleChannelReconfig_MACsecSCI,

    /* Number of CfyE vPorts */
    4,

    /* CfyE vPort data */
    CfyE_vPort_MultipleChannels_Ingress_UntaggedMACsec,

    /* Number of CfyE rules */
    4,

    /* CfyE rule data */
    CfyE_Rule_MultipleChannels_UntaggedMACsec,

    /* CfyE global notification events */
    0,

    /* CfyE channel notification events */
    0,

    /* CfyE MTT data */
    NULL,
};



/* end of file test_vector_cfye.c */
