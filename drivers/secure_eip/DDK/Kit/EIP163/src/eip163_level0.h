/* eip163_level0.h
 *
 * EIP-163 Classification Engine Level0 Internal interface
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

#ifndef EIP163_LEVEL0_H_
#define EIP163_LEVEL0_H_


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Default configuration */
#include "c_eip163.h"

/* Driver Framework Basic Definitions API */
#include "basic_defs.h"         /* BIT definitions, bool, uint32_t */

/* Driver Framework Device API */
#include "device_types.h"       /* Device_Handle_t */
#include "device_rw.h"          /* Read32, Write32 */

/* EIP-163 register interface */
#include "eip163_hw_interface.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

/*----------------------------------------------------------------------------
 * EIP163_Swap16
 *
 * Swaps 2 bytes in a 2-byte word
 */
static inline uint16_t
EIP163_Swap16(
        const uint16_t Value16)
{
    return ((Value16 & MASK_8_BITS) << 8) | ((Value16 >> 8) & MASK_8_BITS);
}


/*----------------------------------------------------------------------------
 * EIP163_Read32
 *
 * This routine reads a 32-bit word from a Register location at Offset
 * in the EIP-163.
 */
static inline int
EIP163_Read32(
        Device_Handle_t Device,
        const unsigned int Offset,
        uint32_t * const Value_p)
{
    return Device_Read32Check(Device, Offset, Value_p);
}


/*----------------------------------------------------------------------------
 * EIP163_Write32
 *
 * This routine writes to a Register location in the EIP-163.
 */
static inline int
EIP163_Write32(
        Device_Handle_t Device,
        const unsigned int Offset,
        const uint32_t Value)
{
   return  Device_Write32(Device, Offset, Value);
}


/*----------------------------------------------------------------------------
 * EIP163_Read32Array
 *
 * This routine reads MemoryDst_p array of Count 32-bit words from a Register
 * location in the EIP-163 at Offset.
 */
static inline int
EIP163_Read32Array(
        Device_Handle_t Device,
        const unsigned int Offset,
        uint32_t * MemoryDst_p,
        const int Count)
{
    return Device_Read32Array(Device, Offset, MemoryDst_p, Count);
}


/*----------------------------------------------------------------------------
 * EIP163_Write32Array
 *
 * This routine writes MemorySrc_p array of Count 32-bit words to a Register
 * location at Offset in the EIP-163.
 */
static inline int
EIP163_Write32Array(
        Device_Handle_t Device,
        const unsigned int Offset,
        const uint32_t * MemorySrc_p,
        const int Count)
{
    return Device_Write32Array(Device, Offset, MemorySrc_p, Count);
}


static inline bool
EIP163_REV_SIGNATURE_MATCH(
        const uint32_t Rev)
{
    return (((uint16_t)Rev) == EIP163_SIGNATURE);
}


static inline int
EIP163_EIP_REV_RD(
        Device_Handle_t Device,
        uint8_t * const EipNumber,
        uint8_t * const ComplmtEipNumber,
        uint8_t * const HWPatchLevel,
        uint8_t * const MinHWRevision,
        uint8_t * const MajHWRevision)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_VERSION, &RegVal);

    if (!rc)
    {
        *MajHWRevision    = (uint8_t)((RegVal >> 24) & MASK_4_BITS);
        *MinHWRevision    = (uint8_t)((RegVal >> 20) & MASK_4_BITS);
        *HWPatchLevel     = (uint8_t)((RegVal >> 16) & MASK_4_BITS);
        *ComplmtEipNumber = (uint8_t)((RegVal >> 8)  & MASK_8_BITS);
        *EipNumber        = (uint8_t)((RegVal)       & MASK_8_BITS);
    }

    return rc;
}


static inline int
EIP163_CONFIG_RD(
        Device_Handle_t Device,
        uint16_t * const vPortCount_p,
        uint16_t * const RulesCount_p,
        bool * const fIngressOnly,
        bool * const fEgressOnly)
{
    uint32_t RegVal =  0;
    int rc = 0;
    unsigned int ShiftCount;

    rc = EIP163_Read32(Device, EIP163_REG_CONFIG, &RegVal);

    if (!rc)
    {
        ShiftCount = RegVal & MASK_3_BITS;
        *fEgressOnly  = ((RegVal & BIT_31) != 0);
        *fIngressOnly = ((RegVal & BIT_30) != 0);
        *RulesCount_p = (uint16_t)((RegVal >> 20) & MASK_10_BITS);

        if (*RulesCount_p == 0)
            *RulesCount_p = 1024;

        *RulesCount_p <<= ShiftCount;
        *vPortCount_p = (uint16_t)((RegVal >> 10) & MASK_10_BITS);
        *vPortCount_p <<= ShiftCount;
    }

    return rc;
}


static inline int
EIP163_CONFIG2_RD(
        Device_Handle_t Device,
#if defined(EIP163_IPSEC_ENABLE)
        uint8_t * const MTT_Count_p,
#endif
        uint8_t * const Channel_Count_p,
#if defined(EIP163_IPSEC_ENABLE)
        bool * const fSpareReg_p,
        bool * const fIPSecSupport_p,
#endif
#if defined(EIP163_VXLAN_ENABLE)
        bool * const fVxLAN_p,
#endif
        bool * const fLookupSCI_p,
        bool * const fExternalTCAM_p)
{
    uint32_t RegVal =  0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_CONFIG2, &RegVal);

    if (!rc)
    {
        *fLookupSCI_p    = ((RegVal & BIT_31) != 0);
        *Channel_Count_p = (uint8_t)((RegVal >> 24) & MASK_6_BITS);
        *fExternalTCAM_p = ((RegVal & BIT_22) != 0);
#if defined(EIP163_IPSEC_ENABLE)
        *fSpareReg_p     = ((RegVal & BIT_23) != 0);
        *fIPSecSupport_p = ((RegVal & BIT_19) != 0);
#endif
#if defined(EIP163_VXLAN_ENABLE)
        *fVxLAN_p = ((RegVal & BIT_14) != 0);
#endif
#if defined(EIP163_IPSEC_ENABLE)
        *MTT_Count_p =  (RegVal & MASK_8_BITS);
#endif
    }

    return rc;
}


static inline int
EIP163_CP_MATCH_DEBUG_RD(
        Device_Handle_t Device,
        uint32_t * const Value_p)
{
    return EIP163_Read32(Device, EIP163_REG_CP_MATCH_DEBUG, Value_p);
}


static inline int
EIP163_TCAM_DEBUG_RD(
        Device_Handle_t Device,
        uint32_t * const Value_p)
{
    return EIP163_Read32(Device, EIP163_REG_TCAM_DEBUG, Value_p);
}


static inline int
EIP163_SECTAG_DEBUG_RD(
        Device_Handle_t Device,
        uint32_t * const Value_p)
{
    return EIP163_Read32(Device, EIP163_REG_SECTAG_DEBUG, Value_p);
}


static inline int
EIP163_SAMPP_DEBUG_RD(
        Device_Handle_t Device,
        uint32_t * const Value1_p,
        uint32_t * const Value2_p,
        uint32_t * const Value3_p)
{
    int rc = 0;

     rc = EIP163_Read32(Device, EIP163_REG_SAMPP_DEBUG1, Value1_p);
     if (rc) return rc;

     rc = EIP163_Read32(Device, EIP163_REG_SAMPP_DEBUG2, Value2_p);
     if (rc) return rc;

     return EIP163_Read32(Device, EIP163_REG_SAMPP_DEBUG2, Value3_p);
}


static inline int
EIP163_DBG_PARSED_DA_RD(
        Device_Handle_t Device,
        uint32_t * const Lo_p,
        uint32_t * const Hi_p)
{
     int rc = 0;

     rc = EIP163_Read32(Device, EIP163_REG_DBG_PARSED_DA_LO, Lo_p);
     if (rc) return rc;

     return EIP163_Read32(Device, EIP163_REG_DBG_PARSED_DA_HI, Hi_p);
}


static inline int
EIP163_DBG_PARSED_SA_RD(
        Device_Handle_t Device,
        uint32_t * const Lo_p,
        uint32_t * const Hi_p)
{
     int rc =0;

     rc = EIP163_Read32(Device, EIP163_REG_DBG_PARSED_SA_LO, Lo_p);
     if (rc) return rc;

     return EIP163_Read32(Device, EIP163_REG_DBG_PARSED_SA_HI, Hi_p);
}


static inline int
EIP163_DBG_PARSED_SECTAG_RD(
        Device_Handle_t Device,
        uint32_t * const Lo_p,
        uint32_t * const Hi_p)
{
     int rc = 0;

     rc = EIP163_Read32(Device, EIP163_REG_DBG_PARSED_SECTAG_LO, Lo_p);
     if (rc) return rc;

     return EIP163_Read32(Device, EIP163_REG_DBG_PARSED_SECTAG_HI, Hi_p);
}


static inline int
EIP163_DEBUG_FLOW_LOOKUP_RD(
        Device_Handle_t Device,
        uint32_t * const Value_p)
{
     return EIP163_Read32(Device, EIP163_REG_DEBUG_FLOW_LOOKUP, Value_p);
}


static inline int
EIP163_TCAM_WR(
        Device_Handle_t Device,
        const unsigned int OffsetInTCAM,
        const uint32_t * Word32_p,
        const uint32_t WordCount,
        const uint32_t MinWordCount)
{
    unsigned int i;
    int rc;

    rc = EIP163_Write32Array(Device,
                             EIP163_REG_TCAM_KEY(0, 0) + /* TCAM start + */
                               OffsetInTCAM,             /* offset in TCAM */
                             Word32_p,
                             WordCount);

    if (rc) return rc;

    if (MinWordCount > WordCount)
    {
        for (i=0; i<MinWordCount - WordCount; i++)
        {
            rc = EIP163_Write32(Device,
                                EIP163_REG_TCAM_KEY(0, 0) + /* TCAM start + */
                                OffsetInTCAM +             /* offset in TCAM */
                                WordCount*4 + i*4,
                                0);
            if (rc) return rc;
        }
    }
    return 0;
}


static inline int
EIP163_TCAM_RD(
        Device_Handle_t Device,
        const unsigned int OffsetInTCAM,
        uint32_t * Word32_p,
        const uint32_t WordCount)
{
    return EIP163_Read32Array(Device,
                              EIP163_REG_TCAM_KEY(0, 0) + /* TCAM start + */
                              OffsetInTCAM,               /* offset in TCAM */
                              Word32_p,
                              WordCount);
}


static inline uint32_t
EIP163_TCAM_CTRL_FR(
        const uint8_t NumTags,
        const uint8_t PacketType,
        const uint16_t ChannelID)
{
    uint32_t RegVal = EIP163_REG_TCAM_CTRL_KEY_DEFAULT;

    RegVal |= ((ChannelID  & MASK_7_BITS) << 16);
#if EIP163_RULE_PKT_TYPE_MASK!=0
    RegVal |= ((PacketType & EIP163_RULE_PKT_TYPE_MASK)  << 8);
#else
    IDENTIFIER_NOT_USED(PacketType);
#endif
    RegVal |= (NumTags     & MASK_7_BITS);

    return RegVal;
}

static inline void
EIP163_TCAM_CTRL_SPLIT(
        const uint32_t RegVal,
        uint8_t * const NumTags,
        uint8_t * const PacketType,
        uint16_t * const ChannelID)
{
    *NumTags    = RegVal & MASK_7_BITS;
    *PacketType = (RegVal >> 8) & EIP163_RULE_PKT_TYPE_MASK;
    *ChannelID  = (RegVal >> 16) & MASK_7_BITS;
}

static inline int
EIP163_TCAM_CTRL_WR(
        Device_Handle_t Device,
        const unsigned int Offset,
        const uint8_t NumTags,
        const uint8_t PacketType,
        const uint16_t ChannelID)
{
    return EIP163_Write32(Device,
                          Offset,
                          EIP163_TCAM_CTRL_FR(NumTags,
                                              PacketType,
                                              ChannelID));
}

static inline int
EIP163_TCAM_CTRL_RD(
        Device_Handle_t Device,
        const unsigned int Offset,
        uint8_t * const NumTags,
        uint8_t * const PacketType,
        uint16_t * const ChannelID)
{
    uint32_t RegVal =  0;
    int rc = 0;

    rc = EIP163_Read32(Device, Offset, &RegVal);

    if (!rc)
    {
        EIP163_TCAM_CTRL_SPLIT(RegVal,
                               NumTags,
                               PacketType,
                               ChannelID);
    }

    return rc;
}


static inline int
EIP163_TCAM_CTRL_KEY_DEFAULT_WR(
        Device_Handle_t Device,
        const unsigned int TCAMEntryID)
{
    return EIP163_Write32(Device,
                          EIP163_REG_TCAM_CTRL_KEY(TCAMEntryID),
                          EIP163_REG_TCAM_CTRL_KEY_DEFAULT);
}


static inline int
EIP163_TCAM_CTRL_KEY_WR(
        Device_Handle_t Device,
        const unsigned int TCAMEntryID,
        const uint8_t NumTags,
        const uint8_t PacketType,
        const uint16_t ChannelID)
{
    return EIP163_TCAM_CTRL_WR(Device,
                               EIP163_REG_TCAM_CTRL_KEY(TCAMEntryID),
                               NumTags,
                               PacketType,
                               ChannelID);
}


static inline int
EIP163_TCAM_CTRL_KEY_RD(
        Device_Handle_t Device,
        const unsigned int TCAMEntryID,
        uint8_t * const NumTags,
        uint8_t * const PacketType,
        uint16_t * const ChannelID)
{
    return EIP163_TCAM_CTRL_RD(Device,
                               EIP163_REG_TCAM_CTRL_KEY(TCAMEntryID),
                               NumTags,
                               PacketType,
                               ChannelID);
}


static inline int
EIP163_TCAM_CTRL_MASK_DEFAULT_WR(
        Device_Handle_t Device,
        const unsigned int TCAMEntryID)
{
    return EIP163_Write32(Device,
                          EIP163_REG_TCAM_CTRL_MASK(TCAMEntryID),
                          EIP163_REG_TCAM_CTRL_MASK_DEFAULT);
}


static inline int
EIP163_TCAM_CTRL_MASK_WR(
        Device_Handle_t Device,
        const unsigned int TCAMEntryID,
        const uint8_t NumTagsMask,
        const uint8_t PacketTypeMask,
        const uint16_t ChannelIDMask)
{
    return EIP163_TCAM_CTRL_WR(Device,
                               EIP163_REG_TCAM_CTRL_MASK(TCAMEntryID),
                               NumTagsMask,
                               PacketTypeMask,
                               ChannelIDMask);
}


static inline int
EIP163_TCAM_CTRL_MASK_RD(
        Device_Handle_t Device,
        const unsigned int TCAMEntryID,
        uint8_t * const NumTagsMask,
        uint8_t * const PacketTypeMask,
        uint16_t * const ChannelIDMask)
{
    return EIP163_TCAM_CTRL_RD(Device,
                               EIP163_REG_TCAM_CTRL_MASK(TCAMEntryID),
                               NumTagsMask,
                               PacketTypeMask,
                               ChannelIDMask);
}


static inline int
EIP163_TCAM_STATUS_RD(
        Device_Handle_t Device,
        bool * const fWriteBusy,
        bool * const fReadBusy,
        bool * const fDisableBusy,
        bool * const fEnabled)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_TCAM_STATUS, &RegVal);

    if (!rc)
    {
        *fWriteBusy   = (RegVal & BIT_0) != 0;
        *fReadBusy    = (RegVal & BIT_1) != 0;
        *fDisableBusy = (RegVal & BIT_2) != 0;
        *fEnabled     = (RegVal & BIT_8) != 0;
    }

    return rc;
}


static inline int
EIP163_TCAM_ENTRY_SET_WR(
        Device_Handle_t Device,
        const uint8_t Index,
        const uint32_t Mask)
{
    return EIP163_Write32(Device, EIP163_REG_TCAM_ENTRY_SET(Index), Mask);
}


static inline int
EIP163_TCAM_ENTRY_CLEAR_WR(
        Device_Handle_t Device,
        const uint8_t Index,
        const uint32_t Mask)
{
    return EIP163_Write32(Device, EIP163_REG_TCAM_ENTRY_CLEAR(Index), Mask);
}


static inline int
EIP163_TCAM_ENTRY_ENABLE_CTRL_WR(
        Device_Handle_t Device,
        const unsigned int IndexSet,
        const bool fSetEnable,
        const bool fEnableAll,
        const unsigned int IndexClear,
        const bool fClearEnable,
        const bool fClearAll)
{
    uint32_t RegVal = EIP163_REG_TCAM_ENTRY_ENABLE_CTRL_DEFAULT;

    if(fSetEnable)
        RegVal |= BIT_14;

    if(fEnableAll)
        RegVal |= BIT_15;

    if(fClearEnable)
        RegVal |= BIT_30;

    if(fClearAll)
        RegVal |= BIT_31;

    RegVal |= ((IndexClear  & MASK_14_BITS) << 16);
    RegVal |= (IndexSet     & MASK_14_BITS);

    return EIP163_Write32(Device, EIP163_REG_TCAM_ENTRY_ENABLE_CTRL, RegVal);
}

static inline int
EIP163_TCAM_ENTRY_ENABLE_RD(
        Device_Handle_t Device,
        const unsigned int RuleIndex,
        bool * const fEnabled_p)
{
    unsigned int RegIndex = RuleIndex / 32;
    uint32_t RegVal;
    uint32_t RegMask = 1 << (RuleIndex % 32);
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_TCAM_ENTRY_ENABLE(RegIndex), &RegVal);

    if (!rc)
    {
      *fEnabled_p = (RegVal & RegMask) != 0;
    }

    return rc;
}


static inline int
EIP163_SAM_IN_FLIGHT_WR(
        Device_Handle_t Device,
        const bool fLoadUnsafe)
{
    uint32_t RegVal = EIP163_REG_SAM_IN_FLIGHT_DEFAULT;

    if(fLoadUnsafe)
        RegVal |= BIT_31;

    return EIP163_Write32(Device, EIP163_REG_SAM_IN_FLIGHT, RegVal);
}


static inline int
EIP163_SAM_IN_FLIGHT_RD(
        Device_Handle_t Device,
        uint8_t * const Unsafe,
        uint8_t * const InFlight,
        bool * const fLoadUnsafe)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_SAM_IN_FLIGHT, &RegVal);

    if (!rc)
    {
        *Unsafe      = (uint8_t)((RegVal >> 0) & MASK_6_BITS);
        *InFlight    = (uint8_t)((RegVal >> 8) & MASK_6_BITS);
        *fLoadUnsafe = ((RegVal & BIT_31) != 0);
    }

    return rc;
}


static inline int
EIP163_VPORT_POLICY_DEFAULT_WR(
        Device_Handle_t Device,
        const unsigned int Index)
{
    return EIP163_Write32(Device,
                   EIP163_REG_VPORT_POLICY(Index),
                   EIP163_REG_VPORT_POLICY_DEFAULT);
}


static inline int
EIP163_VPORT_POLICY_WR(
        Device_Handle_t Device,
        const unsigned int Index,
        const uint8_t SecTagOffset,
#if defined(EIP163_IPSEC_ENABLE)
        const uint8_t MPLS_Hdr,
#endif
        const uint8_t PktExtension)
{
    uint32_t RegVal = EIP163_REG_VPORT_POLICY_DEFAULT;

    RegVal |= ((PktExtension & MASK_2_BITS) << 10);
#if defined(EIP163_IPSEC_ENABLE)
    RegVal |= ((MPLS_Hdr & MASK_2_BITS) << 8);
#endif
    RegVal |= (SecTagOffset  & MASK_7_BITS);

    return EIP163_Write32(Device, EIP163_REG_VPORT_POLICY(Index), RegVal);
}


static inline int
EIP163_VPORT_POLICY_RD(
        Device_Handle_t Device,
        const unsigned int Index,
        uint8_t * const  SecTagOffset_p,
#if defined(EIP163_IPSEC_ENABLE)
        uint8_t * MPLS_Hdr_p,
#endif
        uint8_t * const PktExtension_p)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_VPORT_POLICY(Index), &RegVal);

    if (!rc)
    {
      *PktExtension_p = (RegVal >> 10) & MASK_2_BITS;
#if defined(EIP163_IPSEC_ENABLE)
      *MPLS_Hdr_p = (RegVal >> 8) & MASK_2_BITS;
#endif
      *SecTagOffset_p = RegVal & MASK_7_BITS;
    }

    return rc;
}


#if defined(EIP163_IPSEC_ENABLE)
static inline int
EIP163_IPSEC_TCAM_POLICY_WR(
        Device_Handle_t Device,
        const unsigned int Index,
        const uint16_t vPortIndex,
        const uint8_t Priority,
        const uint8_t AN)
{
    uint32_t RegVal = EIP163_REG_TCAM_POLICY_DEFAULT;

    RegVal |= (vPortIndex & MASK_16_BITS);
    RegVal |= ((Priority  & MASK_3_BITS) << 27);
    RegVal |= ((AN & MASK_2_BITS )<< 30);

    return EIP163_Write32(Device, EIP163_REG_TCAM_POLICY(Index), RegVal);
}

static inline int
EIP163_IPSEC_TCAM_POLICY_RD(
        Device_Handle_t Device,
        const unsigned int Index,
        uint16_t * const vPortIndex_p,
        uint8_t * const Priority_p,
        uint8_t  * const AN_p)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_TCAM_POLICY(Index), &RegVal);

    if (!rc)
    {
        *vPortIndex_p = RegVal & MASK_16_BITS;
        *Priority_p =  (RegVal >> 27) & MASK_3_BITS;
        *AN_p = (RegVal >> 30) & MASK_2_BITS;
    }

    return rc;
}
#endif


static inline int
EIP163_TCAM_POLICY_DEFAULT_WR(
        Device_Handle_t Device,
        const unsigned int Index)
{
    return EIP163_Write32(Device,
                          EIP163_REG_TCAM_POLICY(Index),
                          EIP163_REG_TCAM_POLICY_DEFAULT);
}


static inline int
EIP163_TCAM_POLICY_WR(
        Device_Handle_t Device,
        const unsigned int Index,
        const uint16_t vPortIndex,
        const uint8_t Priority,
        const bool fDrop,
        const bool fControlPkt,
        const bool fControlPktSub)
{
    uint32_t RegVal = EIP163_REG_TCAM_POLICY_DEFAULT;

    if(fControlPkt)
        RegVal |= BIT_31;

    if(fDrop)
        RegVal |= BIT_30;

    if(fControlPktSub)
        RegVal |= BIT_29;

    RegVal |= ((Priority  & MASK_3_BITS)   << 27);
    RegVal |= (vPortIndex & MASK_16_BITS);

    return EIP163_Write32(Device, EIP163_REG_TCAM_POLICY(Index), RegVal);
}


static inline int
EIP163_TCAM_POLICY_RD(
        Device_Handle_t Device,
        const unsigned int Index,
        uint16_t * const vPortIndex_p,
        uint8_t * const  Priority_p,
        bool * fDrop_p,
        bool * fControlPkt_p,
        bool * fControlPktSub_p)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_TCAM_POLICY(Index), &RegVal);

    if (!rc)
    {
      *fControlPkt_p  = (RegVal & BIT_31) != 0;
      *fDrop_p = (RegVal & BIT_30) != 0;
      *fControlPktSub_p = (RegVal & BIT_29) != 0;
      *Priority_p = (RegVal >> 27) & MASK_3_BITS;
      *vPortIndex_p = RegVal & MASK_16_BITS;
    }

    return rc;
}

static inline int
EIP163_SAM_NM_PARAMS_WR(
        Device_Handle_t Device,
        const unsigned int ChannelId,
        const bool fCompEtype,
        const bool fCheckVersion,
        const bool fCheckKay,
        const bool fLookupUseSCI,
        const uint16_t MACsecTagValue)
{
    uint32_t RegVal = EIP163_REG_SAM_NM_PARAMS_DEFAULT;

    if(fCompEtype)
        RegVal |= BIT_0;
    else
        RegVal &= ~BIT_0;

    if(fCheckVersion)
        RegVal |= BIT_1;
    else
        RegVal &= ~BIT_1;

    if(fCheckKay)
        RegVal |= BIT_2;
    else
        RegVal &= ~BIT_2;

    if(fLookupUseSCI)
        RegVal |= BIT_15;
    else
        RegVal &= ~BIT_15;

    RegVal |= ((EIP163_Swap16(MACsecTagValue) & MASK_16_BITS) << 16);

    return EIP163_Write32(Device, EIP163_REG_SAM_NM_PARAMS(ChannelId), RegVal);
}


static inline int
EIP163_SAM_NM_PARAMS_RD(
        Device_Handle_t Device,
        const unsigned int ChannelId,
        bool * const fCompEtype,
        bool * const fCheckVersion,
        bool * const fCheckKay,
        bool * const fLookupUseSCI,
        uint16_t * const MACsecTagValue)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_SAM_NM_PARAMS(ChannelId), &RegVal);

    if (!rc)
    {
        *fCompEtype = (RegVal & BIT_0) != 0;
        *fCheckVersion = (RegVal & BIT_1) != 0;
        *fCheckKay = (RegVal & BIT_2) != 0;
        *fLookupUseSCI = (RegVal & BIT_15) != 0;
        *MACsecTagValue = EIP163_Swap16((RegVal >> 16) & MASK_16_BITS);
    }

    return rc;
}


static inline int
EIP163_CP_MATCH_MODE_WR(
        Device_Handle_t Device,
        const unsigned int ChannelId,
        const uint32_t MatchMode,
        const uint32_t MatchSub)
{
    uint32_t RegVal = (MatchMode & EIP163_REG_CP_MATCH_MODE_MASK) << 8;

    RegVal |= MatchSub & (BIT_31 | MASK_8_BITS);
    RegVal |= (MatchSub & (MASK_13_BITS << 8)) << 10;

    return EIP163_Write32(Device, EIP163_REG_CP_MATCH_MODE(ChannelId), RegVal);
}


static inline int
EIP163_CP_MATCH_MODE_RD(
        Device_Handle_t Device,
        const unsigned int ChannelId,
        uint32_t * const MatchMode,
        uint32_t * const MatchSub)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_CP_MATCH_MODE(ChannelId), &RegVal);

    if (!rc)
    {
        *MatchMode = (RegVal >> 8) & EIP163_REG_CP_MATCH_MODE_MASK;
        *MatchSub = (RegVal & (BIT_31 | MASK_8_BITS)) |
            ((RegVal & (MASK_13_BITS << 18)) >> 10);
    }

    return rc;
}


static inline int
EIP163_CP_MATCH_ENABLE_WR(
        Device_Handle_t Device,
        const unsigned int ChannelId,
        const uint32_t MatchEnable)
{
    uint32_t RegVal = MatchEnable & EIP163_REG_CP_MATCH_ENABLE_MASK;

    return EIP163_Write32(Device, EIP163_REG_CP_MATCH_ENABLE(ChannelId), RegVal);
}


static inline int
EIP163_CP_MATCH_ENABLE_RD(
        Device_Handle_t Device,
        const unsigned int ChannelId,
        uint32_t * const MatchEnable)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_CP_MATCH_ENABLE(ChannelId), &RegVal);

    if (!rc)
    {
        *MatchEnable = RegVal & EIP163_REG_CP_MATCH_ENABLE_MASK;
    }

    return rc;
}


static inline int
EIP163_GLBL_CTRL_RD(
    Device_Handle_t Device,
    bool * const fParsePktIPsec,
    bool * const fDropControlPkts)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_GLBL_CTRL, &RegVal);

    if (!rc)
    {
        *fDropControlPkts = (RegVal & BIT_2) != 0;
        *fParsePktIPsec = (RegVal & BIT_1) != 0;
    }

    return rc;
}


static inline int
EIP163_GLBL_CTRL_WR(
    Device_Handle_t Device,
    const bool fParsePktIPsec,
    const bool fDropControlPkts)
{
    uint32_t RegVal = 0;
#ifndef EIP163_IPSEC_ENABLE
    IDENTIFIER_NOT_USED(fParsePktIPsec);
#endif

    if (fDropControlPkts)
        RegVal |= BIT_2;
#ifdef EIP163_IPSEC_ENABLE
    if (fParsePktIPsec)
          RegVal |= BIT_1;
#endif
    return EIP163_Write32(Device, EIP163_REG_GLBL_CTRL, RegVal);
}



static inline int
EIP163_SAM_POLICY_WR(
        Device_Handle_t Device,
        const unsigned int ChannelId,
        const uint8_t DropAction,
        const bool fForceDrop,
        const bool fDefaultVPortValid,
        const uint8_t ECCDropAction,
        const bool fShouldSecure,
        const uint16_t DefaultVPort)
{
    uint32_t RegVal = EIP163_REG_SAM_POLICY_DEFAULT;

    if(fForceDrop)
        RegVal |= BIT_2;

    if(fDefaultVPortValid)
        RegVal |= BIT_3;

    if(fShouldSecure)
        RegVal |= BIT_6;

    RegVal |= ((DefaultVPort & MASK_16_BITS) << 16);
    RegVal |= (DropAction    & MASK_2_BITS);
    RegVal |= (ECCDropAction & MASK_2_BITS) << 4;

    return EIP163_Write32(Device, EIP163_REG_SAM_POLICY(ChannelId), RegVal);
}


static inline int
EIP163_SAM_POLICY_RD(
        Device_Handle_t Device,
        const unsigned int ChannelId,
        uint8_t * const DropAction,
        bool * const fForceDrop,
        bool *const fDefaultVPortValid,
        uint8_t * const ECCDropAction,
        bool * const fShouldSecure,
        uint16_t *const DefaultVPort)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_SAM_POLICY(ChannelId), &RegVal);

    if (!rc)
    {
        *fForceDrop = (RegVal & BIT_2) != 0;
        *fDefaultVPortValid = (RegVal & BIT_3) != 0;
        *DefaultVPort = (RegVal>>16) & MASK_16_BITS;
        *DropAction = RegVal & MASK_2_BITS;
        *ECCDropAction = (RegVal>>4) & MASK_2_BITS;
        *fShouldSecure = (RegVal & BIT_6) != 0;
    }

    return rc;
}

static inline int
EIP163_SAM_PP_TAGS_WR(
        Device_Handle_t Device,
        const uint16_t QTag,
        const uint16_t STag)
{
    uint32_t RegVal = 0; /* EIP163_REG_SAM_PP_TAGS_DEFAULT; */

    RegVal |= ((EIP163_Swap16(STag) & MASK_16_BITS) << 16);
    RegVal |= (EIP163_Swap16(QTag)  & MASK_16_BITS);

    return EIP163_Write32(Device, EIP163_REG_SAM_PP_TAGS, RegVal);
}


static inline int
EIP163_SAM_PP_TAGS_RD(
        Device_Handle_t Device,
        uint16_t * const QTag,
        uint16_t * const STag)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_SAM_PP_TAGS, &RegVal);

    if (!rc)
    {
        *QTag = EIP163_Swap16(RegVal & MASK_16_BITS);
        *STag = EIP163_Swap16((RegVal >> 16) & MASK_16_BITS);
    }

    return rc;
}


static inline int
EIP163_SAM_PP_TAGS2_WR(
        Device_Handle_t Device,
        const uint16_t STag2,
        const uint16_t STag3)
{
    uint32_t RegVal = 0; /* EIP163_REG_SAM_PP_TAGS2_DEFAULT; */

    RegVal |= ((EIP163_Swap16(STag3) & MASK_16_BITS) << 16);
    RegVal |= (EIP163_Swap16(STag2)  & MASK_16_BITS);

    return EIP163_Write32(Device, EIP163_REG_SAM_PP_TAGS2, RegVal);
}


static inline int
EIP163_SAM_PP_TAGS2_RD(
        Device_Handle_t Device,
        uint16_t * const STag2,
        uint16_t * const STag3)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_SAM_PP_TAGS2, &RegVal);

    if (!rc)
    {
        *STag2 = EIP163_Swap16(RegVal & MASK_16_BITS);
        *STag3 = EIP163_Swap16((RegVal >> 16) & MASK_16_BITS);
    }

    return rc;
}

#if defined(EIP163_VXLAN_ENABLE)
static inline int
EIP163_L3L4_ENABLE_WR(
        Device_Handle_t Device,
        unsigned int ChannelId,
        const uint32_t flags)
{
    return EIP163_Write32(Device, EIP163_REG_L3L4_ENABLE(ChannelId), flags);
}


static inline int
EIP163_L3L4_ENABLE_RD(
        Device_Handle_t Device,
        unsigned int ChannelId,
        uint32_t * const flags)
{
    uint32_t RegVal;

    int rc = EIP163_Read32(Device, EIP163_REG_L3L4_ENABLE(ChannelId), &RegVal);

    if (!rc)
    {
        *flags = RegVal;
    }
    return rc;
}
#endif



#if defined(EIP163_IPSEC_ENABLE)
static inline int
EIP163_MPLS_ENB_SELECT_WR(
        Device_Handle_t Device,
        const unsigned int ChannelId,
        const uint8_t MPLS3_Select1,
        const uint8_t MPLS3_Select2,
        const uint8_t MPLS4_Select1,
        const uint8_t MPLS4_Select2,
        const uint8_t MPLS5_Select1,
        const uint8_t MPLS5_Select2,
        const bool fParseMPLS1,
        const bool fParseMPLS2,
        const bool fParseMPLS3,
        const bool fParseMPLS4)
{
    uint32_t RegVal = EIP163_REG_MPLS_ENB_SELECT_DEFAULT;

    if (fParseMPLS1)
        RegVal |= BIT_24;

    if (fParseMPLS2)
        RegVal |= BIT_25;

    if (fParseMPLS3)
        RegVal |= BIT_26;

    if (fParseMPLS4)
        RegVal |= BIT_27;

    RegVal |= ((MPLS5_Select2 & MASK_3_BITS)  << 11);
    RegVal |= ((MPLS5_Select1 & MASK_3_BITS)  << 8);
    RegVal |= ((MPLS4_Select2 & MASK_2_BITS)  << 6);
    RegVal |= ((MPLS4_Select1 & MASK_2_BITS)  << 4);
    RegVal |= ((MPLS3_Select2 & MASK_2_BITS)  << 2);
    RegVal |= (MPLS3_Select1  & MASK_2_BITS);

    return EIP163_Write32(Device, EIP163_REG_MPLS_ENB_SELECT(ChannelId), RegVal);
}


static inline int
EIP163_MPLS_ENB_SELECT_RD(
        Device_Handle_t Device,
        const unsigned int ChannelId,
        uint8_t * const MPLS3_Select1,
        uint8_t * const MPLS3_Select2,
        uint8_t * const MPLS4_Select1,
        uint8_t * const MPLS4_Select2,
        uint8_t * const MPLS5_Select1,
        uint8_t * const MPLS5_Select2,
        bool * const fParseMPLS1,
        bool * const fParseMPLS2,
        bool * const fParseMPLS3,
        bool * const fParseMPLS4)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_MPLS_ENB_SELECT(ChannelId), &RegVal);

    if (!rc)
    {
        *fParseMPLS1 = (RegVal & BIT_24) != 0;
        *fParseMPLS2 = (RegVal & BIT_25) != 0;
        *fParseMPLS3 = (RegVal & BIT_26) != 0;
        *fParseMPLS4 = (RegVal & BIT_27) != 0;

        *MPLS5_Select2 = (RegVal >> 11) & MASK_3_BITS;
        *MPLS5_Select1 = (RegVal >>  8) & MASK_3_BITS;
        *MPLS4_Select2 = (RegVal >>  6) & MASK_2_BITS;
        *MPLS4_Select1 = (RegVal >>  4) & MASK_2_BITS;
        *MPLS3_Select2 = (RegVal >>  2) & MASK_2_BITS;
        *MPLS3_Select1 =  RegVal        & MASK_2_BITS;
    }

    return rc;
}

static inline int
EIP163_EGRESS_HDR_ETYPE_WR(
        Device_Handle_t Device,
        const unsigned int ChannelId,
        const uint16_t EgressHdrEtype,
        const bool fEnable)
{
    uint32_t RegVal = EIP163_REG_EGRESS_HDR_ETYPE_DEFAULT;

    if (fEnable)
        RegVal |= BIT_31;

    RegVal |= (EgressHdrEtype & MASK_16_BITS);

    return EIP163_Write32(Device, EIP163_REG_EGRESS_HDR_ETYPE(ChannelId), RegVal);
}


static inline int
EIP163_EGRESS_HDR_ETYPE_RD(
        Device_Handle_t Device,
        const unsigned int ChannelId,
        uint16_t * const EgressHdrEtype_p,
        bool * const fEnable_p)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_EGRESS_HDR_ETYPE(ChannelId), &RegVal);

    if (!rc)
    {
        *fEnable_p = (RegVal & BIT_31) != 0;
        *EgressHdrEtype_p = RegVal & MASK_16_BITS;
    }

    return rc;
}
#endif


#if defined(EIP163_IPSEC_ENABLE)
static inline int
EIP163_IPSEC_ENABLE_WR(
        Device_Handle_t Device,
        const unsigned int ChannelId,
        const EIP163_IPSEC_ENABLE_t * const IPSecEn_p)
{
    uint32_t RegVal = EIP163_REG_IPSEC_ENABLE_DEFAULT;

    if (IPSecEn_p->fParseIP)
        RegVal |= BIT_0;

    if (IPSecEn_p->fParseUDP)
        RegVal |= BIT_1;

    if (IPSecEn_p->fParseNAT)
        RegVal |= BIT_2;

    if (IPSecEn_p->fParseESP)
        RegVal |= BIT_3;

    if (IPSecEn_p->fParseIKE)
        RegVal |= BIT_4;

    if (IPSecEn_p->fParseNATIKE)
        RegVal |= BIT_5;

    if (IPSecEn_p->fParseNATKeepAlive)
        RegVal |= BIT_6;

    if (IPSecEn_p->fVerifyUDPChkSum)
        RegVal |= BIT_7;

    if (IPSecEn_p->fMACDACheck)
        RegVal |= BIT_8;

    if (IPSecEn_p->fAllowFragments)
        RegVal |= BIT_12;

    if (IPSecEn_p->fIgnoreIPv4ChkSum)
        RegVal |= BIT_13;

    if (IPSecEn_p->fSubParseIKE)
        RegVal |= BIT_29;

    if (IPSecEn_p->fSubParseNATIKE)
        RegVal |= BIT_30;

    if (IPSecEn_p->fSubParseNATKeepAlive)
        RegVal |= BIT_31;

    return EIP163_Write32(Device, EIP163_REG_IPSEC_ENABLE(ChannelId), RegVal);
}


static inline int
EIP163_IPSEC_ENABLE_RD(
        Device_Handle_t Device,
        const unsigned int ChannelId,
        EIP163_IPSEC_ENABLE_t * const IPSecEn_p)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_EGRESS_HDR_ETYPE(ChannelId), &RegVal);

    if (!rc)
    {
        IPSecEn_p->fParseIP              = (RegVal & BIT_0) != 0;
        IPSecEn_p->fParseUDP             = (RegVal & BIT_1) != 0;
        IPSecEn_p->fParseNAT             = (RegVal & BIT_2) != 0;
        IPSecEn_p->fParseESP             = (RegVal & BIT_3) != 0;
        IPSecEn_p->fParseIKE             = (RegVal & BIT_4) != 0;
        IPSecEn_p->fParseNATIKE          = (RegVal & BIT_5) != 0;
        IPSecEn_p->fParseNATKeepAlive    = (RegVal & BIT_6) != 0;
        IPSecEn_p->fVerifyUDPChkSum      = (RegVal & BIT_7) != 0;
        IPSecEn_p->fMACDACheck           = (RegVal & BIT_8) != 0;
        IPSecEn_p->fAllowFragments       = (RegVal & BIT_12) != 0;
        IPSecEn_p->fIgnoreIPv4ChkSum     = (RegVal & BIT_13) != 0;
        IPSecEn_p->fSubParseIKE          = (RegVal & BIT_29) != 0;
        IPSecEn_p->fSubParseNATIKE       = (RegVal & BIT_30) != 0;
        IPSecEn_p->fSubParseNATKeepAlive = (RegVal & BIT_31) != 0;
    }

    return rc;
}

static inline int
EIP163_EHDR_DEBUG_RD(
        Device_Handle_t Device,
        unsigned int * const VportIndex_p,
        uint8_t * const Action_p,
        bool * const fValid_p)
{
     uint32_t RegVal = 0;
     int rc = 0;

     rc = EIP163_Read32(Device, EIP163_REG_EHDR_DEBUG, &RegVal);

     if (!rc)
     {
        *VportIndex_p = (RegVal & MASK_16_BITS);
        *Action_p =  ((RegVal >> 16) & MASK_2_BITS);
        *fValid_p = (RegVal & BIT_31) != 0;
     }

     return rc;
}
#endif


static inline int
EIP163_SAM_CP_TAG_ENB_WR(
        Device_Handle_t Device,
        const unsigned int ChannelId,
        const bool fParseQtag,
        const bool fParseStag1,
        const bool fParseStag2,
        const bool fParseStag3,
        const bool fParseQinQ)
{
    uint32_t RegVal = EIP163_REG_SAM_CP_TAG_ENB_DEFAULT;

    if(fParseQinQ)
        RegVal |= BIT_31;

    if(fParseStag3)
        RegVal |= BIT_3;

    if(fParseStag2)
        RegVal |= BIT_2;

    if(fParseStag1)
        RegVal |= BIT_1;

    if(fParseQtag)
        RegVal |= BIT_0;

    return EIP163_Write32(Device, EIP163_REG_SAM_CP_TAG_ENB(ChannelId), RegVal);
}

static inline int
EIP163_SAM_CP_TAG_ENB_RD(
        Device_Handle_t Device,
        const unsigned int ChannelId,
        bool * const fParseQtag,
        bool * const fParseStag1,
        bool * const fParseStag2,
        bool * const fParseStag3,
        bool * const fParseQinQ)
{
    uint32_t RegVal =  0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_SAM_CP_TAG_ENB(ChannelId), &RegVal);

    if (!rc)
    {
        *fParseQinQ  = (RegVal & BIT_31) != 0;
        *fParseStag3 = (RegVal & BIT_3) != 0;
        *fParseStag2 = (RegVal & BIT_2) != 0;
        *fParseStag1 = (RegVal & BIT_1) != 0;
        *fParseQtag  = (RegVal & BIT_0) != 0;
    }

    return rc;
}

static inline int
EIP163_CP_MAC_DA_MATCH_WR(
        Device_Handle_t Device,
        const unsigned int Index,
        const uint8_t DA_Byte1,
        const uint8_t DA_Byte2,
        const uint8_t DA_Byte3,
        const uint8_t DA_Byte4)
{
    uint32_t RegVal = 0; /* EIP163_REG_CP_MAC_DA_MATCH_DEFAULT; */

    RegVal |= ((DA_Byte4   & MASK_8_BITS) << 24);
    RegVal |= ((DA_Byte3   & MASK_8_BITS) << 16);
    RegVal |= ((DA_Byte2   & MASK_8_BITS) << 8);
    RegVal |= (DA_Byte1    & MASK_8_BITS);

    return EIP163_Write32(Device, EIP163_REG_CP_MAC_DA_MATCH(Index), RegVal);
}


static inline int
EIP163_CP_MAC_DA_MATCH_RD(
        Device_Handle_t Device,
        const unsigned int Index,
        uint8_t * const DA_Byte1,
        uint8_t * const DA_Byte2,
        uint8_t * const DA_Byte3,
        uint8_t * const DA_Byte4)
{
    uint32_t RegVal =  0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_CP_MAC_DA_MATCH(Index), &RegVal);

    if (!rc)
    {
        *DA_Byte1 = RegVal & MASK_8_BITS;
        *DA_Byte2 = (RegVal >> 8) & MASK_8_BITS;
        *DA_Byte3 = (RegVal >> 16) & MASK_8_BITS;
        *DA_Byte4 = (RegVal >> 24) & MASK_8_BITS;
    }

    return rc;
}


static inline int
EIP163_CP_MAC_DA_ET_MATCH_WR(
        Device_Handle_t Device,
        const unsigned int Index,
        const uint8_t DA_Byte5,
        const uint8_t DA_Byte6,
        const uint16_t EtherType)
{
    uint32_t RegVal = 0; /* EIP163_REG_CP_MAC_DA_ET_MATCH_DEFAULT; */
    uint32_t Swapped = EIP163_Swap16(EtherType);

    RegVal |= ((Swapped    & MASK_16_BITS) << 16);
    RegVal |= ((DA_Byte6   & MASK_8_BITS)  << 8);
    RegVal |= (DA_Byte5    & MASK_8_BITS);

    return EIP163_Write32(Device, EIP163_REG_CP_MAC_DA_ET_MATCH(Index), RegVal);
}


static inline int
EIP163_CP_MAC_DA_ET_MATCH_RD(
        Device_Handle_t Device,
        const unsigned int Index,
        uint8_t * const DA_Byte5,
        uint8_t * const DA_Byte6,
        uint16_t * const EtherType)
{
    uint32_t RegVal =  0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_CP_MAC_DA_ET_MATCH(Index), &RegVal);

    if (!rc)
    {
        *DA_Byte5 = RegVal & MASK_8_BITS;
        *DA_Byte6 = (RegVal >> 8) & MASK_8_BITS;
        *EtherType = EIP163_Swap16(RegVal >> 16);
    }

    return rc;
}


static inline int
EIP163_CP_MAC_DA_START_LO_WR(
        Device_Handle_t Device,
        const unsigned int Index,
        const uint8_t DA_Byte1,
        const uint8_t DA_Byte2,
        const uint8_t DA_Byte3,
        const uint8_t DA_Byte4)
{
    uint32_t RegVal = 0; /* EIP163_REG_CP_MAC_DA_MATCH_DEFAULT; */

    RegVal |= ((DA_Byte4   & MASK_8_BITS) << 24);
    RegVal |= ((DA_Byte3   & MASK_8_BITS) << 16);
    RegVal |= ((DA_Byte2   & MASK_8_BITS) << 8);
    RegVal |= (DA_Byte1    & MASK_8_BITS);

    return EIP163_Write32(Device, EIP163_REG_CP_MAC_DA_START_LO(Index), RegVal);
}


static inline int
EIP163_CP_MAC_DA_START_LO_RD(
        Device_Handle_t Device,
        const unsigned int Index,
        uint8_t * const DA_Byte1,
        uint8_t * const DA_Byte2,
        uint8_t * const DA_Byte3,
        uint8_t * const DA_Byte4)
{
    uint32_t RegVal =  0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_CP_MAC_DA_START_LO(Index), &RegVal);

    if (!rc)
    {
        *DA_Byte1 = RegVal & MASK_8_BITS;
        *DA_Byte2 = (RegVal >> 8) & MASK_8_BITS;
        *DA_Byte3 = (RegVal >> 16) & MASK_8_BITS;
        *DA_Byte4 = (RegVal >> 24) & MASK_8_BITS;
    }

    return rc;
}


static inline int
EIP163_CP_MAC_DA_START_HI_WR(
        Device_Handle_t Device,
        const unsigned int Index,
        const uint8_t DA_Byte5,
        const uint8_t DA_Byte6,
        const uint16_t EtherType)
{
    uint32_t RegVal = 0; /* EIP163_REG_CP_MAC_DA_ET_MATCH_DEFAULT; */
    uint32_t Swapped = EIP163_Swap16(EtherType);

    RegVal |= ((Swapped    & MASK_16_BITS) << 16);
    RegVal |= ((DA_Byte6   & MASK_8_BITS) << 8);
    RegVal |= (DA_Byte5    & MASK_8_BITS);

    return EIP163_Write32(Device, EIP163_REG_CP_MAC_DA_START_HI(Index), RegVal);
}

static inline int
EIP163_CP_MAC_DA_START_HI_RD(
        Device_Handle_t Device,
        const unsigned int Index,
        uint8_t * const DA_Byte5,
        uint8_t * const DA_Byte6,
        uint16_t * const EtherType)
{
    uint32_t RegVal =  0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_CP_MAC_DA_START_HI(Index), &RegVal);

    if (!rc)
    {
        *DA_Byte5 = RegVal & MASK_8_BITS;
        *DA_Byte6 = (RegVal >> 8) & MASK_8_BITS;
        *EtherType = EIP163_Swap16(RegVal >> 16);
    }

    return rc;
}


static inline int
EIP163_CP_MAC_DA_END_LO_WR(
        Device_Handle_t Device,
        const unsigned int Index,
        const uint8_t DA_Byte1,
        const uint8_t DA_Byte2,
        const uint8_t DA_Byte3,
        const uint8_t DA_Byte4)
{
    uint32_t RegVal = 0; /* EIP163_REG_CP_MAC_DA_MATCH_DEFAULT; */

    RegVal |= ((DA_Byte4   & MASK_8_BITS) << 24);
    RegVal |= ((DA_Byte3   & MASK_8_BITS) << 16);
    RegVal |= ((DA_Byte2   & MASK_8_BITS) << 8);
    RegVal |= (DA_Byte1    & MASK_8_BITS);

    return EIP163_Write32(Device, EIP163_REG_CP_MAC_DA_END_LO(Index), RegVal);
}


static inline int
EIP163_CP_MAC_DA_END_LO_RD(
        Device_Handle_t Device,
        const unsigned int Index,
        uint8_t * const DA_Byte1,
        uint8_t * const DA_Byte2,
        uint8_t * const DA_Byte3,
        uint8_t * const DA_Byte4)
{
    uint32_t RegVal =  0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_CP_MAC_DA_END_LO(Index), &RegVal);

    if (!rc)
    {
        *DA_Byte1 = RegVal & MASK_8_BITS;
        *DA_Byte2 = (RegVal >> 8) & MASK_8_BITS;
        *DA_Byte3 = (RegVal >> 16) & MASK_8_BITS;
        *DA_Byte4 = (RegVal >> 24) & MASK_8_BITS;
    }

    return rc;
}


static inline int
EIP163_CP_MAC_DA_END_HI_WR(
        Device_Handle_t Device,
        const unsigned int Index,
        const uint8_t DA_Byte5,
        const uint8_t DA_Byte6)
{
    uint32_t RegVal = 0; /* EIP163_REG_CP_MAC_DA_ET_MATCH_DEFAULT; */

    RegVal |= ((DA_Byte6   & MASK_8_BITS) << 8);
    RegVal |= (DA_Byte5    & MASK_8_BITS);

    return EIP163_Write32(Device, EIP163_REG_CP_MAC_DA_END_HI(Index), RegVal);
}


static inline int
EIP163_CP_MAC_DA_END_HI_RD(
        Device_Handle_t Device,
        const unsigned int Index,
        uint8_t * const DA_Byte5,
        uint8_t * const DA_Byte6)
{
    uint32_t RegVal =  0;
    int rc = 0;
    rc = EIP163_Read32(Device, EIP163_REG_CP_MAC_DA_END_HI(Index), &RegVal);

    if (!rc)
    {
        *DA_Byte5 = RegVal & MASK_8_BITS;
        *DA_Byte6 = (RegVal >> 8) & MASK_8_BITS;
    }

    return rc;
}


static inline int
EIP163_CP_MAC_DA_START_RO_LO_WR(
        Device_Handle_t Device,
        const uint8_t DA_Byte1,
        const uint8_t DA_Byte2,
        const uint8_t DA_Byte3,
        const uint8_t DA_Byte4)
{
    uint32_t RegVal = 0; /* EIP163_REG_CP_MAC_DA_MATCH_DEFAULT; */

    RegVal |= ((DA_Byte4   & MASK_8_BITS) << 24);
    RegVal |= ((DA_Byte3   & MASK_8_BITS) << 16);
    RegVal |= ((DA_Byte2   & MASK_8_BITS) << 8);
    RegVal |= (DA_Byte1    & MASK_8_BITS);

    return EIP163_Write32(Device, EIP163_REG_CP_MAC_DA_START_RO_LO, RegVal);
}


static inline int
EIP163_CP_MAC_DA_START_RO_LO_RD(
        Device_Handle_t Device,
        uint8_t * const DA_Byte1,
        uint8_t * const DA_Byte2,
        uint8_t * const DA_Byte3,
        uint8_t * const DA_Byte4)
{
    uint32_t RegVal =  0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_CP_MAC_DA_START_RO_LO, &RegVal);

    if (!rc)
    {
        *DA_Byte1 = RegVal & MASK_8_BITS;
        *DA_Byte2 = (RegVal >> 8) & MASK_8_BITS;
        *DA_Byte3 = (RegVal >> 16) & MASK_8_BITS;
        *DA_Byte4 = (RegVal >> 24) & MASK_8_BITS;
    }

    return rc;
}


static inline int
EIP163_CP_MAC_DA_START_RO_HI_WR(
        Device_Handle_t Device,
        const uint8_t DA_Byte5,
        const uint8_t DA_Byte6)
{
    uint32_t RegVal = 0; /* EIP163_REG_CP_MAC_DA_ET_MATCH_DEFAULT; */

    RegVal |= ((DA_Byte6   & MASK_8_BITS) << 8);
    RegVal |= (DA_Byte5    & MASK_8_BITS);

    return EIP163_Write32(Device, EIP163_REG_CP_MAC_DA_START_RO_HI, RegVal);
}


static inline int
EIP163_CP_MAC_DA_START_RO_HI_RD(
        Device_Handle_t Device,
        uint8_t * const DA_Byte5,
        uint8_t * const DA_Byte6)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_CP_MAC_DA_START_RO_HI, &RegVal);

    if (!rc)
    {
        *DA_Byte5 = RegVal & MASK_8_BITS;
        *DA_Byte6 = (RegVal >> 8) & MASK_8_BITS;
    }

    return rc;
}


static inline int
EIP163_CP_MAC_DA_END_RO_LO_WR(
        Device_Handle_t Device,
        const uint8_t DA_Byte1,
        const uint8_t DA_Byte2,
        const uint8_t DA_Byte3,
        const uint8_t DA_Byte4)
{
    uint32_t RegVal = 0; /* EIP163_REG_CP_MAC_DA_MATCH_DEFAULT; */

    RegVal |= ((DA_Byte4   & MASK_8_BITS) << 24);
    RegVal |= ((DA_Byte3   & MASK_8_BITS) << 16);
    RegVal |= ((DA_Byte2   & MASK_8_BITS) << 8);
    RegVal |= (DA_Byte1    & MASK_8_BITS);

    return EIP163_Write32(Device, EIP163_REG_CP_MAC_DA_END_RO_LO, RegVal);
}


static inline int
EIP163_CP_MAC_DA_END_RO_LO_RD(
        Device_Handle_t Device,
        uint8_t * const DA_Byte1,
        uint8_t * const DA_Byte2,
        uint8_t * const DA_Byte3,
        uint8_t * const DA_Byte4)
{
    uint32_t RegVal =  0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_CP_MAC_DA_END_RO_LO, &RegVal);

    if (!rc)
    {
        *DA_Byte1 = RegVal & MASK_8_BITS;
        *DA_Byte2 = (RegVal >> 8) & MASK_8_BITS;
        *DA_Byte3 = (RegVal >> 16) & MASK_8_BITS;
        *DA_Byte4 = (RegVal >> 24) & MASK_8_BITS;
    }

    return rc;
}


static inline int
EIP163_CP_MAC_DA_END_RO_HI_WR(
        Device_Handle_t Device,
        const uint8_t DA_Byte5,
        const uint8_t DA_Byte6)
{
    uint32_t RegVal = 0; /* EIP163_REG_CP_MAC_DA_ET_MATCH_DEFAULT; */

    RegVal |= ((DA_Byte6   & MASK_8_BITS) << 8);
    RegVal |= (DA_Byte5    & MASK_8_BITS);

    return EIP163_Write32(Device, EIP163_REG_CP_MAC_DA_END_RO_HI, RegVal);
}


static inline int
EIP163_CP_MAC_DA_END_RO_HI_RD(
        Device_Handle_t Device,
        uint8_t * const DA_Byte5,
        uint8_t * const DA_Byte6)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_CP_MAC_DA_END_RO_HI, &RegVal);

    if (!rc)
    {
        *DA_Byte5 = RegVal & MASK_8_BITS;
        *DA_Byte6 = (RegVal >> 8) & MASK_8_BITS;
    }

    return rc;
}


static inline int
EIP163_CP_MAC_DA_44_BITS_LO_WR(
        Device_Handle_t Device,
        const uint8_t DA_Byte1,
        const uint8_t DA_Byte2,
        const uint8_t DA_Byte3,
        const uint8_t DA_Byte4)
{
    uint32_t RegVal = 0; /* EIP163_REG_CP_MAC_DA_44_BITS_LO_DEFAULT; */

    RegVal |= ((DA_Byte4   & MASK_8_BITS) << 24);
    RegVal |= ((DA_Byte3   & MASK_8_BITS) << 16);
    RegVal |= ((DA_Byte2   & MASK_8_BITS) << 8);
    RegVal |= (DA_Byte1    & MASK_8_BITS);

    return EIP163_Write32(Device, EIP163_REG_CP_MAC_DA_44_BITS_LO, RegVal);
}


static inline int
EIP163_CP_MAC_DA_44_BITS_LO_RD(
        Device_Handle_t Device,
        uint8_t * const DA_Byte1,
        uint8_t * const DA_Byte2,
        uint8_t * const DA_Byte3,
        uint8_t * const DA_Byte4)
{
    uint32_t RegVal =  0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_CP_MAC_DA_44_BITS_LO, &RegVal);

    if (!rc)
    {
        *DA_Byte1 = RegVal & MASK_8_BITS;
        *DA_Byte2 = (RegVal >> 8) & MASK_8_BITS;
        *DA_Byte3 = (RegVal >> 16) & MASK_8_BITS;
        *DA_Byte4 = (RegVal >> 24) & MASK_8_BITS;
    }

    return rc;
}


static inline int
EIP163_CP_MAC_DA_44_BITS_HI_WR(
        Device_Handle_t Device,
        const uint8_t DA_Byte5,
        const uint8_t DA_Byte6)
{
    uint32_t RegVal = 0; /* EIP163_REG_CP_MAC_DA_44_BITS_HI_DEFAULT; */

    RegVal |= ((DA_Byte6 &        0xF0) << 8);
    RegVal |= (DA_Byte5  & MASK_8_BITS);

    return EIP163_Write32(Device, EIP163_REG_CP_MAC_DA_44_BITS_HI, RegVal);
}


static inline int
EIP163_CP_MAC_DA_44_BITS_HI_RD(
        Device_Handle_t Device,
        uint8_t * const DA_Byte5,
        uint8_t * const DA_Byte6)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_CP_MAC_DA_44_BITS_HI, &RegVal);

    if (!rc)
    {
        *DA_Byte5 = RegVal & MASK_8_BITS;
        *DA_Byte6 = (RegVal >> 8) & MASK_8_BITS;
    }

    return rc;
}


static inline int
EIP163_CP_MAC_DA_48_BITS_LO_WR(
        Device_Handle_t Device,
        const uint8_t DA_Byte1,
        const uint8_t DA_Byte2,
        const uint8_t DA_Byte3,
        const uint8_t DA_Byte4)
{
    uint32_t RegVal = 0; /* EIP163_REG_CP_MAC_DA_48_BITS_LO_DEFAULT; */

    RegVal |= ((DA_Byte4   & MASK_8_BITS) << 24);
    RegVal |= ((DA_Byte3   & MASK_8_BITS) << 16);
    RegVal |= ((DA_Byte2   & MASK_8_BITS) << 8);
    RegVal |= (DA_Byte1    & MASK_8_BITS);

    return EIP163_Write32(Device, EIP163_REG_CP_MAC_DA_48_BITS_LO, RegVal);
}


static inline int
EIP163_CP_MAC_DA_48_BITS_LO_RD(
        Device_Handle_t Device,
        uint8_t * const DA_Byte1,
        uint8_t * const DA_Byte2,
        uint8_t * const DA_Byte3,
        uint8_t * const DA_Byte4)
{
    uint32_t RegVal =  0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_CP_MAC_DA_48_BITS_LO, &RegVal);

    if (!rc)
    {
        *DA_Byte1 = RegVal & MASK_8_BITS;
        *DA_Byte2 = (RegVal >> 8) & MASK_8_BITS;
        *DA_Byte3 = (RegVal >> 16) & MASK_8_BITS;
        *DA_Byte4 = (RegVal >> 24) & MASK_8_BITS;
    }

    return rc;
}


static inline int
EIP163_CP_MAC_DA_48_BITS_HI_WR(
        Device_Handle_t Device,
        const uint8_t DA_Byte5,
        const uint8_t DA_Byte6)
{
    uint32_t RegVal = 0; /* EIP163_REG_CP_MAC_DA_48_BITS_HI_DEFAULT; */

    RegVal |= ((DA_Byte6   & MASK_8_BITS) << 8);
    RegVal |= (DA_Byte5    & MASK_8_BITS);

    return EIP163_Write32(Device, EIP163_REG_CP_MAC_DA_48_BITS_HI, RegVal);
}


static inline int
EIP163_CP_MAC_DA_48_BITS_HI_RD(
        Device_Handle_t Device,
        uint8_t * const DA_Byte5,
        uint8_t * const DA_Byte6)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_CP_MAC_DA_48_BITS_HI, &RegVal);

    if (!rc)
    {
        *DA_Byte5 = RegVal & MASK_8_BITS;
        *DA_Byte6 = (RegVal >> 8) & MASK_8_BITS;
    }

    return rc;
}


static inline int
EIP163_SAM_CP_TAG_WR(
        Device_Handle_t Device,
        const uint8_t UP0,
        const uint8_t UP1,
        const uint8_t UP2,
        const uint8_t UP3,
        const uint8_t UP4,
        const uint8_t UP5,
        const uint8_t UP6,
        const uint8_t UP7,
        const uint8_t DefaultUP,
        const bool fSTagUPEnable,
        const bool fQTagUPEnable)
{
    uint32_t RegVal = EIP163_REG_SAM_CP_TAG_DEFAULT;

    if(fQTagUPEnable)
        RegVal |= BIT_28;

    if(fSTagUPEnable)
        RegVal |= BIT_27;

    RegVal |= ((DefaultUP & MASK_3_BITS)  << 24);
    RegVal |= ((UP7       & MASK_3_BITS)  << 21);
    RegVal |= ((UP6       & MASK_3_BITS)  << 18);
    RegVal |= ((UP5       & MASK_3_BITS)  << 15);
    RegVal |= ((UP4       & MASK_3_BITS)  << 12);
    RegVal |= ((UP3       & MASK_3_BITS)  << 9);
    RegVal |= ((UP2       & MASK_3_BITS)  << 6);
    RegVal |= ((UP1       & MASK_3_BITS)  << 3);
    RegVal |= (UP0        & MASK_3_BITS);

    return EIP163_Write32(Device, EIP163_REG_SAM_CP_TAG, RegVal);
}


static inline int
EIP163_SAM_CP_TAG_RD(
        Device_Handle_t Device,
        uint8_t * const UP0,
        uint8_t * const UP1,
        uint8_t * const UP2,
        uint8_t * const UP3,
        uint8_t * const UP4,
        uint8_t * const UP5,
        uint8_t * const UP6,
        uint8_t * const UP7,
        uint8_t * const DefaultUP,
        bool * const fSTagUPEnable,
        bool * const fQTagUPEnable)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_SAM_CP_TAG, &RegVal);

    if (!rc)
    {
      *fQTagUPEnable = (RegVal & BIT_28) != 0;
      *fSTagUPEnable = (RegVal & BIT_27) != 0;

      *DefaultUP = (RegVal >> 24) & MASK_3_BITS;
      *UP7       = (RegVal >> 21) & MASK_3_BITS;
      *UP6       = (RegVal >> 18) & MASK_3_BITS;
      *UP5       = (RegVal >> 15) & MASK_3_BITS;
      *UP4       = (RegVal >> 12) & MASK_3_BITS;
      *UP3       = (RegVal >>  9) & MASK_3_BITS;
      *UP2       = (RegVal >>  6) & MASK_3_BITS;
      *UP1       = (RegVal >>  3) & MASK_3_BITS;
      *UP0       =  RegVal        & MASK_3_BITS;
    }

    return rc;
}


static inline int
EIP163_SAM_CP_TAG2_WR(
        Device_Handle_t Device,
        const uint8_t UP0,
        const uint8_t UP1,
        const uint8_t UP2,
        const uint8_t UP3,
        const uint8_t UP4,
        const uint8_t UP5,
        const uint8_t UP6,
        const uint8_t UP7)
{
    uint32_t RegVal = EIP163_REG_SAM_CP_TAG2_DEFAULT;

    RegVal |= ((UP7       & MASK_3_BITS)  << 21);
    RegVal |= ((UP6       & MASK_3_BITS)  << 18);
    RegVal |= ((UP5       & MASK_3_BITS)  << 15);
    RegVal |= ((UP4       & MASK_3_BITS)  << 12);
    RegVal |= ((UP3       & MASK_3_BITS)  << 9);
    RegVal |= ((UP2       & MASK_3_BITS)  << 6);
    RegVal |= ((UP1       & MASK_3_BITS)  << 3);
    RegVal |= (UP0        & MASK_3_BITS);

    return EIP163_Write32(Device, EIP163_REG_SAM_CP_TAG2, RegVal);
}


static inline int
EIP163_SAM_CP_TAG2_RD(
        Device_Handle_t Device,
        uint8_t * const UP0,
        uint8_t * const UP1,
        uint8_t * const UP2,
        uint8_t * const UP3,
        uint8_t * const UP4,
        uint8_t * const UP5,
        uint8_t * const UP6,
        uint8_t * const UP7)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_SAM_CP_TAG2, &RegVal);

    if (!rc)
    {
      *UP7 = (RegVal >> 21) & MASK_3_BITS;
      *UP6 = (RegVal >> 18) & MASK_3_BITS;
      *UP5 = (RegVal >> 15) & MASK_3_BITS;
      *UP4 = (RegVal >> 12) & MASK_3_BITS;
      *UP3 = (RegVal >>  9) & MASK_3_BITS;
      *UP2 = (RegVal >>  6) & MASK_3_BITS;
      *UP1 = (RegVal >>  3) & MASK_3_BITS;
      *UP0 =  RegVal        & MASK_3_BITS;
    }

    return rc;
}


#if defined(EIP163_IPSEC_ENABLE)
static inline int
EIP163_MPLS_TYPE1_WR(
        Device_Handle_t Device,
        const uint16_t MPLS_Etype1,
        const uint16_t MPLS_Etype2)
{
    uint32_t RegVal = 0; /* EIP163_REG_MPLS_TYPE1_DEFAULT; */

    RegVal |= ((EIP163_Swap16(MPLS_Etype2) & MASK_16_BITS) << 16);
    RegVal |= (EIP163_Swap16(MPLS_Etype1)  & MASK_16_BITS);

    return EIP163_Write32(Device, EIP163_REG_MPLS_ETYPE1, RegVal);
}


static inline int
EIP163_MPLS_TYPE1_RD(
        Device_Handle_t Device,
        uint16_t * const MPLS_Etype1,
        uint16_t * const MPLS_Etype2)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_MPLS_ETYPE1, &RegVal);

    if (!rc)
    {
      *MPLS_Etype1 = EIP163_Swap16(RegVal & MASK_16_BITS);
      *MPLS_Etype2  = EIP163_Swap16((RegVal >> 16) & MASK_16_BITS);
    }

    return rc;
}


static inline int
EIP163_MPLS_TYPE2_WR(
        Device_Handle_t Device,
        const uint16_t MPLS_Etype3,
        const uint16_t MPLS_Etype4)
{
    uint32_t RegVal = 0; /* EIP163_REG_MPLS_TYPE2_DEFAULT; */

    RegVal |= ((EIP163_Swap16(MPLS_Etype4) & MASK_16_BITS) << 16);
    RegVal |= (EIP163_Swap16(MPLS_Etype3)  & MASK_16_BITS);

    return EIP163_Write32(Device, EIP163_REG_MPLS_ETYPE2, RegVal);
}


static inline int
EIP163_MPLS_TYPE2_RD(
        Device_Handle_t Device,
        uint16_t * const MPLS_Etype3,
        uint16_t * const MPLS_Etype4)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_MPLS_ETYPE2, &RegVal);

    if (!rc)
    {
      *MPLS_Etype3  = EIP163_Swap16(RegVal & MASK_16_BITS);
      *MPLS_Etype4  = EIP163_Swap16((RegVal >> 16) & MASK_16_BITS);
    }

    return rc;
}
#endif

#if defined(EIP163_IPSEC_ENABLE)
static inline int
EIP163_MPLS_DEBUG1_RD(
    Device_Handle_t Device,
    uint32_t * const MPLS_Label1_p,
    uint8_t * const MPLS_Exp1_p,
    bool * const MPLS_S1_p,
    uint8_t * const NumLabels_p,
    bool * const MPLS_Valid_p)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_MPLS_DEBUG1, &RegVal);

    if (!rc)
    {
      *MPLS_Label1_p = RegVal & MASK_20_BITS;
      *MPLS_Exp1_p   = (uint8_t) ((RegVal >> 20) & MASK_3_BITS);
      *MPLS_S1_p     = (RegVal & BIT_23) != 0;
      *NumLabels_p   = (uint8_t) ((RegVal >> 24) & MASK_3_BITS);
      *MPLS_Valid_p  = (RegVal & BIT_31) != 0;
    }

    return rc;
}

static inline int
EIP163_MPLS_DEBUG2_RD(
    Device_Handle_t Device,
    uint32_t * const MPLS_Label2_p,
    uint8_t * const MPLS_Exp2_p,
    bool * const MPLS_S2_p)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_MPLS_DEBUG2, &RegVal);

    if (!rc)
    {
      *MPLS_Label2_p = RegVal & MASK_20_BITS;
      *MPLS_Exp2_p   = (uint8_t) ((RegVal >> 20) & MASK_3_BITS);
      *MPLS_S2_p     = (RegVal & BIT_23) != 0;
    }

    return rc;
}

static inline int
EIP163_UDP_PORT1_RD(
        Device_Handle_t Device,
        uint16_t * const IKE_Port,
        uint16_t * const NAT_Port)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_UDP_PORT1, &RegVal);

    if (!rc)
    {
      *IKE_Port  = (RegVal & MASK_16_BITS);
      *NAT_Port  = ((RegVal >> 16) & MASK_16_BITS);
    }

    return rc;
}


static inline int
EIP163_UDP_PORT1_WR(
        Device_Handle_t Device,
        const uint16_t IKE_Port,
        const uint16_t NAT_Port)
{
    uint32_t RegVal = 0;

    RegVal |= ((IKE_Port)  & MASK_16_BITS);
    RegVal |= ((NAT_Port & MASK_16_BITS) << 16);

    return EIP163_Write32(Device, EIP163_REG_UDP_PORT1, RegVal);
}


static inline int
EIP163_CP_MAC_DA_IPSEC_LO_WR(
        Device_Handle_t Device,
        const uint8_t DA_Byte1, /* mac_da_match[23:16] */
        const uint8_t DA_Byte2, /* mac_da_match[31:24] */
        const uint8_t DA_Byte3, /* mac_da_match[39:32] */
        const uint8_t DA_Byte4  /* mac_da_match[47:40] */)
{
    uint32_t RegVal = 0; /* EIP163_REG_CP_MAC_DA_MATCH_DEFAULT; */

    RegVal |= ((DA_Byte4 & MASK_8_BITS) << 24);
    RegVal |= ((DA_Byte3 & MASK_8_BITS) << 16);
    RegVal |= ((DA_Byte2 & MASK_8_BITS) << 8);
    RegVal |= (DA_Byte1  & MASK_8_BITS);

    return EIP163_Write32(Device, EIP163_REG_CP_MAC_DA_IPSEC_LO, RegVal);
}


static inline int
EIP163_CP_MAC_DA_IPSEC_LO_RD(
        Device_Handle_t Device,
        uint8_t * const DA_Byte1  /* mac_da_match[23:16] */,
        uint8_t * const DA_Byte2  /* mac_da_match[31:24] */,
        uint8_t * const DA_Byte3  /* mac_da_match[39:32] */,
        uint8_t * const DA_Byte4  /* mac_da_match[47:40] */)
{
    uint32_t RegVal =  0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_CP_MAC_DA_IPSEC_LO, &RegVal);

    if (!rc)
    {
        *DA_Byte1 = RegVal & MASK_8_BITS;
        *DA_Byte2 = (RegVal >> 8) & MASK_8_BITS;
        *DA_Byte3 = (RegVal >> 16) & MASK_8_BITS;
        *DA_Byte4 = (RegVal >> 24) & MASK_8_BITS;
    }

    return rc;
}


static inline int
EIP163_CP_MAC_DA_IPSEC_HI_WR(
        Device_Handle_t Device,
        const uint8_t DA_Byte5  /* mac_da_match[15:8] */,
        const uint8_t DA_Byte6  /* mac_da_match[7:0]  */)
{
    uint32_t RegVal = 0; /* EIP163_REG_CP_MAC_DA_ET_MATCH_DEFAULT; */

    RegVal |= ((DA_Byte6 & MASK_8_BITS) << 8);
    RegVal |= (DA_Byte5  & MASK_8_BITS);

    return EIP163_Write32(Device, EIP163_REG_CP_MAC_DA_IPSEC_HI, RegVal);
}

static inline int
EIP163_CP_MAC_DA_IPSEC_HI_RD(
        Device_Handle_t Device,
        uint8_t * const DA_Byte5 /* mac_da_match[15:8] */,
        uint8_t * const DA_Byte6 /* mac_da_match[7:0]  */)
{
    uint32_t RegVal =  0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_CP_MAC_DA_IPSEC_HI, &RegVal);

    if (!rc)
    {
        *DA_Byte5 = RegVal & MASK_8_BITS;
        *DA_Byte6 = (RegVal >> 8) & MASK_8_BITS;
    }

    return rc;
}

static inline int
EIP163_IP_DEBUG1_RD(
    Device_Handle_t Device,
    uint16_t * const Lenght_p,
    uint8_t * const Protocol_p,
    bool * const fIPV4Valid_p,
    bool * const fIPV6Valid_p)
{
    uint32_t RegVal =  0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_IP_DEBUG1, &RegVal);

    if (!rc)
    {
        *Lenght_p = RegVal & MASK_16_BITS;
        *Protocol_p = (RegVal >> 16) & MASK_8_BITS;
        *fIPV4Valid_p = ((RegVal & BIT_30) != 0);
        *fIPV6Valid_p = ((RegVal & BIT_31) != 0);
    }

    return rc;
}

static inline int
EIP163_IP_DEBUG2_RD(
    Device_Handle_t Device,
    uint16_t * const Checksum_p,
    uint8_t * const TTL_p,
    uint8_t * const IPV4_IHL_p,
    uint8_t * const Version_p)
{
    uint32_t RegVal =  0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_IP_DEBUG2, &RegVal);

    if (!rc)
    {
        *Checksum_p = RegVal & MASK_16_BITS;
        *TTL_p = (RegVal >> 16) & MASK_8_BITS;
        *IPV4_IHL_p = (RegVal >> 24) & MASK_3_BITS;
        *Version_p = (RegVal >> 28) & MASK_4_BITS;
    }

    return rc;
}

static inline int
EIP163_DEBUG_DA_IPADD_RD(
    Device_Handle_t Device,
    uint32_t * const IP_DEBUG_DA0_p,
    uint32_t * const IP_DEBUG_DA1_p,
    uint32_t * const IP_DEBUG_DA2_p,
    uint32_t * const IP_DEBUG_DA3_p)
{
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_IP_DEBUG_DA0, IP_DEBUG_DA0_p);
    if (rc) return rc;

    rc = EIP163_Read32(Device, EIP163_REG_IP_DEBUG_DA1, IP_DEBUG_DA1_p);
    if (rc) return rc;

    rc = EIP163_Read32(Device, EIP163_REG_IP_DEBUG_DA2, IP_DEBUG_DA2_p);
    if (rc) return rc;

    rc = EIP163_Read32(Device, EIP163_REG_IP_DEBUG_DA3, IP_DEBUG_DA3_p);

    return rc;
}

static inline int
EIP163_UDP_DEBUG1_RD(
    Device_Handle_t Device,
    uint16_t * const SrcPort_p,
    uint16_t * const DstPort_p)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_UDP_DEBUG1, &RegVal);

    if (!rc)
    {
        *SrcPort_p = RegVal & MASK_16_BITS;
        *DstPort_p = ((RegVal >> 16) & MASK_16_BITS);
    }

    return rc;
}

static inline int
EIP163_UDP_DEBUG2_RD(
    Device_Handle_t Device,
    uint16_t * const Lenght_p,
    uint16_t * const CheckSum_p)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_UDP_DEBUG1, &RegVal);

    if (!rc)
    {
        *Lenght_p = RegVal & MASK_16_BITS;
        *CheckSum_p = ((RegVal >> 16) & MASK_16_BITS);
    }

    return rc;
}
#endif


#if defined(EIP163_VXLAN_ENABLE)
static inline int
EIP163_UDP_PORT2_RD(
        Device_Handle_t Device,
        uint16_t * const VxLAN_Port1,
        uint16_t * const VxLAN_Port2)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_UDP_PORT2, &RegVal);

    if (!rc)
    {
        *VxLAN_Port1  = (RegVal & MASK_16_BITS);
        *VxLAN_Port2  = ((RegVal >> 16) & MASK_16_BITS);
    }

    return rc;
}


static inline int
EIP163_UDP_PORT2_WR(
        Device_Handle_t Device,
        const uint16_t VxLAN_Port1,
        const uint16_t VxLAN_Port2)
{
    uint32_t RegVal = 0;

    RegVal |= ((VxLAN_Port1)  & MASK_16_BITS);
    RegVal |= ((VxLAN_Port2 & MASK_16_BITS) << 16);

    return EIP163_Write32(Device, EIP163_REG_UDP_PORT2, RegVal);
}


#endif
static inline int
EIP163_CHANNEL_CTRL_RD(
        Device_Handle_t Device,
        const unsigned int ChannelId,
#if defined(EIP163_IPSEC_ENABLE)
        bool * const fIPSec,
#endif
        bool * const fBypassMode)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_CHANNEL_CTRL(ChannelId), &RegVal);

    if (!rc)
    {
      *fBypassMode = ((RegVal & BIT_0) != 0);
#if defined(EIP163_IPSEC_ENABLE)
      *fIPSec = ((RegVal & BIT_1) != 0);
#endif
    }

    return rc;
}


static inline int
EIP163_CHANNEL_CTRL_DEFAULT_WR(
        Device_Handle_t Device,
        const unsigned int ChannelId)
{
    return EIP163_Write32(Device,
                   EIP163_REG_CHANNEL_CTRL(ChannelId),
                   EIP163_REG_CHANNEL_CTRL_DEFAULT);
}


static inline int
EIP163_CHANNEL_CTRL_WR(
        Device_Handle_t Device,
        const unsigned int Index,
#if defined(EIP163_IPSEC_ENABLE)
        const bool fIPSec,
#endif
        const bool fBypassMode)
{
    uint32_t RegVal = EIP163_REG_CHANNEL_CTRL_DEFAULT;

    if (fBypassMode)
        RegVal |= BIT_0;
    else
        RegVal &= ~BIT_0;

#if defined(EIP163_IPSEC_ENABLE)
    if (fIPSec)
        RegVal |= BIT_1;
    else
        RegVal &= ~BIT_1;
#endif

    return EIP163_Write32(Device, EIP163_REG_CHANNEL_CTRL(Index), RegVal);
}


static inline int
EIP163_FORCE_CLOCK_ON_WR(
        Device_Handle_t Device,
        const uint32_t ClockMask)
{
    uint32_t RegVal = (ClockMask & MASK_4_BITS);

    return EIP163_Write32(Device, EIP163_REG_FORCE_CLOCK_ON, RegVal);
}


static inline int
EIP163_FORCE_CLOCK_OFF_WR(
        Device_Handle_t Device,
        const uint32_t ClockMask)
{
    uint32_t RegVal = (ClockMask & MASK_4_BITS);

    return EIP163_Write32(Device, EIP163_REG_FORCE_CLOCK_OFF, RegVal);
}


static inline int
EIP163_LOW_LAT_CONFIG_WR(
        Device_Handle_t Device,
        bool fLowLatencyBypass)
{
    return EIP163_Write32(Device, EIP163_REG_LOW_LAT_CONFIG,
                   fLowLatencyBypass ? 1 : 0);
}


static inline int
EIP163_RX_INSERT_SOP_WR(
        Device_Handle_t Device,
        const uint16_t ChannelCount,
        const EIP163_Ch_Mask_t * const ChannelMask_p)
{
    int rc = 0;
    uint16_t i = 0;

    for (i = 0; i < ((ChannelCount + 31) / 32); i++)
    {
         rc = EIP163_Write32(Device,
                             EIP163_REG_RX_INSERT_SOP(i),
                             ChannelMask_p->ch_bitmask[i]);
        if (rc) return rc;
    }

    return rc;
}


static inline int
EIP163_RX_INSERT_EOP_WR(
        Device_Handle_t Device,
        const uint16_t ChannelCount,
        const EIP163_Ch_Mask_t * const ChannelMask_p)
{
    int rc = 0;
    uint16_t i = 0;

    for (i = 0; i < ((ChannelCount + 31) / 32); i++)
    {
        rc = EIP163_Write32(Device,
                            EIP163_REG_RX_INSERT_EOP(i),
                            ChannelMask_p->ch_bitmask[i]);
        if (rc) return rc;
    }

    return rc;
}


static inline int
EIP163_RX_TIMEOUT_CTRL_WR(
        Device_Handle_t Device,
        const uint16_t ChannelCount,
        const EIP163_Ch_Mask_t * const ChannelMask_p)
{
    uint16_t i = 0;
    int rc = 0;

    for (i = 0; i < (ChannelCount + 31) / 32; i++)
    {
        rc = EIP163_Write32(Device,
                            EIP163_REG_RX_TIMEOUT_CTRL(i),
                            ChannelMask_p->ch_bitmask[i]);
        if (rc) return rc;
    }

    return rc;
}


static inline int
EIP163_RX_TIMEOUT_CTRL_RD(
        Device_Handle_t Device,
        const uint16_t ChannelCount,
        EIP163_Ch_Mask_t * const ChannelMask_p)
{
    uint16_t i = 0;
    int rc = 0;

    for (i = 0; i < ((ChannelCount + 31) / 32); i++)
    {
        rc = EIP163_Read32(Device,
                           EIP163_REG_RX_TIMEOUT_CTRL(i),
                           &ChannelMask_p->ch_bitmask[i]);
        if (rc) return rc;
    }

    return rc;
}

static inline int
EIP163_RX_TIMEOUT_VAL_WR(
        Device_Handle_t Device,
        unsigned int TimeoutVal)
{
    uint32_t RegVal = TimeoutVal & MASK_16_BITS;

    return EIP163_Write32(Device, EIP163_REG_RX_TIMEOUT_VAL, RegVal);
}

static inline int
EIP163_RX_TIMEOUT_VAL_RD(
        Device_Handle_t Device,
        unsigned int * TimeoutVal)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_RX_TIMEOUT_VAL, &RegVal);

    if (!rc)
    {
      *TimeoutVal = RegVal & MASK_16_BITS;
    }

    return rc;
}

static inline int
EIP163_ECC_COUNTER_RAM_RD(
        Device_Handle_t Device,
        unsigned int Index,
        unsigned int *CorrValue,
        unsigned int *DerrValue)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_ECC_COUNTER_RAM(Index), &RegVal);

    if (!rc)
    {
       *CorrValue = (RegVal >> 16) & MASK_16_BITS;
       *DerrValue = RegVal & MASK_16_BITS;
    }

    return rc;
}

static inline int
EIP163_ECC_COUNTER_RAM_WR(
        Device_Handle_t Device,
        unsigned int Index,
        unsigned int CorrValue,
        unsigned int DerrValue)
{

    uint32_t RegVal = ((CorrValue & MASK_16_BITS) << 16) |
                      (DerrValue & MASK_16_BITS);

    return EIP163_Write32(Device, EIP163_REG_ECC_COUNTER_RAM(Index), RegVal);
}


static inline int
EIP163_ECC_THR_CORR_STAT_RD(
        Device_Handle_t Device,
        uint32_t *ThrMask)
{
    return EIP163_Read32(Device, EIP163_REG_ECC_THR_CORR_STAT, ThrMask);
}

static inline int
EIP163_ECC_THR_DERR_STAT_RD(
        Device_Handle_t Device,
        uint32_t *ThrMask)
{
    return EIP163_Read32(Device, EIP163_REG_ECC_THR_DERR_STAT, ThrMask);
}


static inline int
EIP163_ECC_CORR_ENABLE_WR(
        Device_Handle_t Device,
        uint32_t EnableMask)
{
    return EIP163_Write32(Device, EIP163_REG_ECC_CORR_ENABLE, EnableMask);
}

static inline int
EIP163_ECC_DERR_ENABLE_WR(
        Device_Handle_t Device,
        uint32_t EnableMask)
{
    return EIP163_Write32(Device, EIP163_REG_ECC_DERR_ENABLE, EnableMask);
}

static inline int
EIP163_ECC_THRESHOLDS_WR(
        Device_Handle_t Device,
        unsigned int CorrValue,
        unsigned int DerrValue)
{
    uint32_t RegVal = ((CorrValue & MASK_16_BITS) << 16) |
                      (DerrValue & MASK_16_BITS);

    return EIP163_Write32(Device, EIP163_REG_ECC_THRESHOLDS, RegVal);
}

static inline int
EIP163_ECC_THRESHOLDS_RD(
        Device_Handle_t Device,
        unsigned int * CorrValue,
        unsigned int * DerrValue)
{
    uint32_t RegVal = 0;
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_ECC_THRESHOLDS, &RegVal);

    if (!rc)
    {
      *CorrValue = (RegVal >> 16) & MASK_16_BITS;
      *DerrValue = RegVal & MASK_16_BITS;
    }

    return rc;
}


#if defined(EIP163_IPSEC_ENABLE)
static inline int
EIP163_MTT_WR(
        Device_Handle_t Device,
        const unsigned int Offset,
        const uint16_t ChannelCount,
        const EIP163_Ch_Mask_t * const ChannelMask_p,
        const bool fIPv6,
        const uint32_t TagLabel1,
#if defined(EIP163_IPSEC_ENABLE)
        const uint32_t TagLabel2,
        const bool fIPHdrValid,
#endif
        const uint32_t * const IPAddr
#if defined(EIP163_IPSEC_ENABLE)
        , const bool fPacketType
#endif
        )
{
    uint32_t RegVal = 0;
    int rc = 0;
    uint16_t i = 0;

    for (i = 0; i < ((ChannelCount + 31) / 32); i++)
    {
        rc = EIP163_Write32(Device,
                            (Offset + (i * 0x1C)),
                            ChannelMask_p->ch_bitmask[i]);
        if (rc) return rc;
    }

    RegVal = TagLabel1 & MASK_24_BITS;


#if defined(EIP163_IPSEC_ENABLE)

    if (fIPHdrValid)
        RegVal |= BIT_29;

    if (fPacketType)
        RegVal |= BIT_31;
#endif

    if (fIPv6)
        RegVal |= BIT_30;

    rc = EIP163_Write32(Device, Offset + 4, RegVal);
    if (rc) return rc;

#if defined(EIP163_IPSEC_ENABLE)
    rc = EIP163_Write32(Device, Offset + 8, (TagLabel2 & MASK_24_BITS));
    if (rc) return rc;
#endif

    for (i = 0; i < 4; i++)
    {
        rc = EIP163_Write32(Device, Offset + 12 + 4 * i, IPAddr[i]);
        if (rc) return rc;
    }

    return 0;
}


static inline int
EIP163_MTT_RD(
        Device_Handle_t Device,
        const unsigned int Offset,
        const uint16_t ChannelCount,
        EIP163_Ch_Mask_t * const ChannelMask_p,
        bool * const fIPv6,
        uint32_t * const TagLabel1,
#if defined(EIP163_IPSEC_ENABLE)
        uint32_t * const TagLabel2,
        bool * const fIPHdrValid_p,
#endif
        uint32_t * const IPAddr
#if defined(EIP163_IPSEC_ENABLE)
        , bool * const fPacketType
#endif
        )
{
    uint32_t RegVal = 0;
    int rc = 0;
    uint16_t i = 0;

    for (i = 0; i < ((ChannelCount + 31) / 32); i++)
    {
        rc = EIP163_Read32(Device,
                           (Offset + (i * 0x1C)),
                           &ChannelMask_p->ch_bitmask[i]);
        if (rc) return rc;
    }

    rc = EIP163_Read32(Device, Offset + 4, &RegVal);
    if (rc) return rc;

    *TagLabel1 = RegVal & MASK_24_BITS;

#if defined(EIP163_IPSEC_ENABLE)
    *fIPHdrValid_p = ((RegVal & BIT_29) != 0);
    *fPacketType   = ((RegVal & BIT_31) != 0);
#endif
    *fIPv6         = ((RegVal & BIT_30) != 0);

#if defined(EIP163_IPSEC_ENABLE)
    RegVal = 0;
    rc = EIP163_Read32(Device, Offset + 8, &RegVal);
    if (rc) return rc;

    *TagLabel2     = RegVal & MASK_24_BITS;
#endif

    for (i = 0; i < 4; i++)
    {
        rc = EIP163_Read32(Device, Offset + 12 + 4 * i, &IPAddr[i]);
        if (rc) return rc;
    }

    return 0;
}


static inline int
EIP163_MTT_KEY_WR(
        Device_Handle_t Device,
        const unsigned int Index,
        const uint16_t ChannelCount,
        const EIP163_Ch_Mask_t * const ChannelMask_p,
        const bool fIPv6,
        const uint16_t TagLabel1,
#if defined(EIP163_IPSEC_ENABLE)
        const uint16_t TagLabel2,
        const bool fIPHdrValid,
#endif
        const uint32_t * const IPAddr
#if defined(EIP163_IPSEC_ENABLE)
        , const bool fPacketType
#endif
        )
{
    return EIP163_MTT_WR(Device,
                         EIP163_REG_MTT_KEY(Index),
                         ChannelCount,
                         ChannelMask_p,
                         fIPv6,
                         TagLabel1,
#if defined(EIP163_IPSEC_ENABLE)
                         TagLabel2,
                         fIPHdrValid,
#endif
                         IPAddr
#if defined(EIP163_IPSEC_ENABLE)
                         , fPacketType
#endif
                         );
}


static inline int
EIP163_MTT_MASK_WR(
        Device_Handle_t Device,
        const unsigned int Index,
        const uint16_t ChannelCount,
        const EIP163_Ch_Mask_t * const ChannelMask_p,
        const bool fIPv6,
        const uint16_t TagLabel1,
#if defined(EIP163_IPSEC_ENABLE)
        const uint16_t TagLabel2,
        const bool fIPHdrValid,
#endif
        const uint32_t * const IPAddr
#if defined(EIP163_IPSEC_ENABLE)
        , const bool fPacketType
#endif
        )
{
    return EIP163_MTT_WR(Device,
                         EIP163_REG_MTT_MASK(Index),
                         ChannelCount,
                         ChannelMask_p,
                         fIPv6,
                         TagLabel1,
#if defined(EIP163_IPSEC_ENABLE)
                         TagLabel2,
                         fIPHdrValid,
#endif
                         IPAddr
#if defined(EIP163_IPSEC_ENABLE)
                         , fPacketType
#endif
                         );
}


static inline int
EIP163_MTT_KEY_RD(
        Device_Handle_t Device,
        const unsigned int Index,
        const uint16_t ChannelCount,
        EIP163_Ch_Mask_t * const ChannelMask_p,
        bool * const fIPv6_p,
        uint32_t * const TagLabel1_p,
#if defined(EIP163_IPSEC_ENABLE)
        uint32_t * const TagLabel2_p,
        bool * const fIPHdrValid_p,
#endif
        uint32_t * const IPAddr_p
#if defined(EIP163_IPSEC_ENABLE)
        , bool * const fPacketType_p
#endif
        )
{
    return EIP163_MTT_RD(Device,
                         EIP163_REG_MTT_KEY(Index),
                         ChannelCount,
                         ChannelMask_p,
                         fIPv6_p,
                         TagLabel1_p,
#if defined(EIP163_IPSEC_ENABLE)
                         TagLabel2_p,
                         fIPHdrValid_p,
#endif
                         IPAddr_p
#if defined(EIP163_IPSEC_ENABLE)
                         , fPacketType_p
#endif
                         );
}


static inline int
EIP163_MTT_MASK_RD(
        Device_Handle_t Device,
        const unsigned int Index,
        const uint16_t ChannelCount,
        EIP163_Ch_Mask_t * const ChannelMask_p,
        bool * const fIPv6_p,
        uint32_t * const TagLabel1_p,
#if defined(EIP163_IPSEC_ENABLE)
        uint32_t * const TagLabel2_p,
        bool * const fIPHdrValid_p,
#endif
        uint32_t * const IPAddr_p
#if defined(EIP163_IPSEC_ENABLE)
        , bool * const fPacketType_p
#endif
        )
{
    return EIP163_MTT_RD(Device,
                         EIP163_REG_MTT_MASK(Index),
                         ChannelCount,
                         ChannelMask_p,
                         fIPv6_p,
                         TagLabel1_p,
#if defined(EIP163_IPSEC_ENABLE)
                         TagLabel2_p,
                         fIPHdrValid_p,
#endif
                         IPAddr_p
#if defined(EIP163_IPSEC_ENABLE)
                         , fPacketType_p
#endif
                         );
}


static inline int
EIP163_MTT_ENTRY_ENABLE_CTRL_WR(
        Device_Handle_t Device,
        const unsigned int IndexSet,
        const bool fSetEnable,
        const bool fEnableAll,
        const unsigned int IndexClear,
        const bool fClearEnable,
        const bool fClearAll)
{
    uint32_t RegVal = EIP163_REG_TCAM_ENTRY_ENABLE_CTRL_DEFAULT;

    if (fSetEnable)
        RegVal |= BIT_14;

    if (fEnableAll)
        RegVal |= BIT_15;

    if (fClearEnable)
        RegVal |= BIT_30;

    if (fClearAll)
        RegVal |= BIT_31;

    RegVal |= ((IndexClear  & MASK_14_BITS) << 16);
    RegVal |= (IndexSet     & MASK_14_BITS);

    return EIP163_Write32(Device, EIP163_REG_MTT_ENABLE_CTRL, RegVal);
}

static inline int
EIP163_MTT_ENTRY_ENABLE_RD(
        Device_Handle_t Device,
        const unsigned int MTTIndex,
        bool * const fEnabled_p)
{
    uint32_t RegVal = 0;
    uint32_t RegMask = 1 << (MTTIndex % 32);
    int rc = 0;

    rc = EIP163_Read32(Device, EIP163_REG_MTT_ENABLE, &RegVal);

    if (!rc)
    {
      *fEnabled_p = (RegVal & RegMask) != 0;
    }

    return rc;
}
#endif /* defined(EIP163_IPSEC_ENABLE) */

#endif /* EIP163_LEVEL0_H_ */


/* end of file eip163_level0.h */
