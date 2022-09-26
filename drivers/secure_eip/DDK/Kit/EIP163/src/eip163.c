/* eip163.c
 *
 * EIP-163 Driver Library API implementation
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

#include <clib.h>

/* EIP-163 Driver Library API */
#include "eip163.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Default configuration */
#include "c_eip163.h"

/* Driver Framework Basic Definitions API */
#include "basic_defs.h"             /* IDENTIFIER_NOT_USED, bool, uint32_t */

/* Driver Framework Device API */
#include "device_types.h"           /* Device_Handle_t */

/* EIP-163 Level0 interface */
#include "eip163_level0.h"

/* EIP-217 Level0 interface */
#include "eip217_level0.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

#define EIP163_STAT_CHAN_SUMMARY_MAX_COUNTERS 7

typedef enum
{
    EIP163_HW_CONF_E,
    EIP163_HW_CONF_I
} EIP163_HW_Conf_t;

/* I/O Area, used internally */
typedef struct
{
    Device_Handle_t         Device;
    EIP163_Device_Mode_t    Mode;
    EIP163_HW_Conf_t        HWConf;
    unsigned int            MaxChCount;
#if defined(EIP163_IPSEC_ENABLE)
    unsigned int            MaxMTTCount;
#endif
    unsigned int            MaxvPortCount;
    unsigned int            MaxRulesCount;
    bool                    fLookupSCI;
    bool                    fExternalTCAM;
    bool                    fHasTCAMPrio;
#if defined(EIP163_IPSEC_ENABLE)
    bool                    fSpareReg;
    bool                    fIPSecSupport;
#endif
    bool                    fReadPending;
} EIP163_True_IOArea_t;

#define IOAREA_IN(_p)    ((const volatile EIP163_True_IOArea_t * const)_p)
#define IOAREA_INOUT(_p) ((volatile EIP163_True_IOArea_t * const)_p)

#ifdef EIP163_STRICT_ARGS
#define EIP163_CHECK_POINTER(_p) \
    if (NULL == (_p)) \
        return EIP163_ARGUMENT_ERROR;
#define EIP163_CHECK_INT_INRANGE(_i, _min, _max) \
    if ((_i) < (_min) || (_i) > (_max)) \
        return EIP163_ARGUMENT_ERROR;
#define EIP163_CHECK_INT_ATLEAST(_i, _min) \
    if ((_i) < (_min)) \
        return EIP163_ARGUMENT_ERROR;
#define EIP163_CHECK_INT_ATMOST(_i, _max) \
    if ((_i) > (_max)) \
        return EIP163_ARGUMENT_ERROR;
#else
/* EIP163_STRICT_ARGS undefined */
#define EIP163_CHECK_POINTER(_p)
#define EIP163_CHECK_INT_INRANGE(_i, _min, _max)
#define EIP163_CHECK_INT_ATLEAST(_i, _min)
#define EIP163_CHECK_INT_ATMOST(_i, _max)
#endif /*end of EIP163_STRICT_ARGS */

#define TEST_SIZEOF(type, size) \
    extern int size##_must_bigger[1 - 2*((int)(sizeof(type) > size))]

/* validate the size of the fake and real IOArea structures */
TEST_SIZEOF(EIP163_True_IOArea_t, EIP163_IOAREA_REQUIRED_SIZE);
/*----------------------------------------------------------------------------
 * Definitions and macros
 */
#define HIGH_CH_BIT(ChannelCount)  (1 << ((ChannelCount + 31) % 32))
#define PREP_MASK(ChannelCount)   ((HIGH_CH_BIT(ChannelCount))| (HIGH_CH_BIT(ChannelCount) - 1))
#define MASK_UNUSED_CH_BITS(ChannelCount, ChannelMask) (PREP_MASK(ChannelCount) & (ChannelMask))


/*----------------------------------------------------------------------------
 * Local variables
 */

/*----------------------------------------------------------------------------
 * Local Functions
 */

/*----------------------------------------------------------------------------
 * MaskUnusedChBits
 *
 * Masks the Most Significant Channel bits.
 */

static void
MaskUnusedChBits(
    EIP163_Ch_Mask_t *const ChMask_p,
    const uint16_t ChannelCount)
{
    uint8_t i, k = 0;
    uint32_t val = 0;

    if (0 == ChannelCount) return;

    k = (ChannelCount + 31) / 32;

    /** Get the Channel Mask representing the higher channels */
    val = ChMask_p->ch_bitmask[k - 1];

    ChMask_p->ch_bitmask[k - 1] = MASK_UNUSED_CH_BITS(ChannelCount, val);

    for (i = k; i < EIP163_CHANNEL_WORDS; i++)
        ChMask_p->ch_bitmask[i] = 0;
}


/*----------------------------------------------------------------------------
 * Local variables
 */

/*----------------------------------------------------------------------------
 * EIP163Lib_Counter_Read
 */
static int
EIP163Lib_Counter_Read(
        const Device_Handle_t Device,
        const unsigned int Offset,
        const unsigned int Index,
        EIP163_UI64_t * const Counter_p,
        const bool fClear)
{
    int rc = 0;

    rc = EIP217_COUNTER_64_RD(Device,
                         Offset,
                         Index,
                         &Counter_p->low,
                         &Counter_p->hi);
    if (rc) return rc;

    if (fClear && (Counter_p->low || Counter_p->hi))
    {
        /* If the counter is non-zero, write the same value */
        /* to decrement to zero (but not losing any increments that might */
        /* have happened between the read and the write).. */
        rc = EIP217_COUNTER_64_WR(Device,
                                  Offset,
                                  Index,
                                  Counter_p->low,
                                  Counter_p->hi);
    }

    return rc;
}

/*----------------------------------------------------------------------------
 * EIP163Lib_HWRevision_Get
 */
static int
EIP163Lib_HWRevision_Get(
        const Device_Handle_t Device,
        EIP163_Options_t * const Options_p,
        EIP163_Version_t * const Version_p)
{
    int rc = 0;

    rc = EIP163_EIP_REV_RD(Device,
                           &Version_p->EipNumber,
                           &Version_p->ComplmtEipNumber,
                           &Version_p->HWPatchLevel,
                           &Version_p->MinHWRevision,
                           &Version_p->MajHWRevision);
    if (rc) return rc;

    rc = EIP163_CONFIG_RD(Device,
                          &Options_p->vPort_Count,
                          &Options_p->Rules_Count,
                          &Options_p->fIngressOnly,
                          &Options_p->fEgressOnly);
    if (rc) return rc;

    return EIP163_CONFIG2_RD(Device,
#if defined(EIP163_IPSEC_ENABLE)
                             &Options_p->MTT_Count,
#endif
                             &Options_p->Channel_Count,
#if defined(EIP163_IPSEC_ENABLE)
                             &Options_p->fSpareReg,
                             &Options_p->fIPSecSupport,
#endif
#if defined(EIP163_VXLAN_ENABLE)
                             &Options_p->fVxLAN,
#endif
                             &Options_p->fLookupSCI,
                             &Options_p->fExternalTCAM);
}


/*----------------------------------------------------------------------------
 * EIP163Lib_TCAM_HWRevision_Get
 */
static int
EIP163Lib_TCAM_HWRevision_Get(
        const Device_Handle_t Device,
        EIP163_TCAM_Options_t * const Options_p,
        EIP163_Version_t * const Version_p)
{
    int rc = 0;

    rc = EIP217_EIP_REV_RD(Device,
                           EIP163_REG_TCAM_STAT_CTRL_OFFS,
                           &Version_p->EipNumber,
                           &Version_p->ComplmtEipNumber,
                           &Version_p->HWPatchLevel,
                           &Version_p->MinHWRevision,
                           &Version_p->MajHWRevision);
    if (rc) return rc;

    rc = EIP217_OPTIONS_RD(Device,
                           EIP163_REG_TCAM_STAT_CTRL_OFFS,
                           &Options_p->TCAMHitPktCounters_Count);
    if (rc) return rc;

    return EIP217_OPTIONS2_RD(Device,
                              EIP163_REG_TCAM_STAT_CTRL_OFFS,
                              &Options_p->TCAMHitCounters_Count,
                              &Options_p->TCAMHitCountersWidth_BitCount);
}


/*----------------------------------------------------------------------------
 * EIP163Lib_Detect
 *
 * Checks the presence of EIP-163 device. Returns true when found.
 */
static EIP163_Error_t
EIP163Lib_Detect(
        const Device_Handle_t Device)
{
    uint32_t Value;

    int rc  = EIP163_Read32(Device, EIP163_REG_VERSION, &Value);
    if (rc) return rc;

    if (!EIP163_REV_SIGNATURE_MATCH( Value ))
        return EIP163_UNSUPPORTED_FEATURE_ERROR;

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163Lib_TCAM_Detect
 *
 * Checks the presence of EIP-163 TCAM device. Returns true when found.
 */
static EIP163_Error_t
EIP163Lib_TCAM_Detect(
        const Device_Handle_t Device)
{
    uint32_t Value = 0;

    int rc = EIP217_Read32(Device,
                    EIP163_REG_TCAM_STAT_CTRL_OFFS +
                    EIP217_REG_VERSION, &Value);

    if (rc) return rc;

    if (!EIP217_REV_SIGNATURE_MATCH(Value))
        return EIP163_UNSUPPORTED_FEATURE_ERROR;

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163Lib_Device_Is_Done
 */
static EIP163_Error_t
EIP163Lib_Device_Is_Done(
        const Device_Handle_t Device,
        const bool fExternalTCAM)
{
    bool fResetAllTCAM, fSaturateCtrs, fAutoCtrReset, fResetSummary, fIgnoreECC;
    int rc = 0;

    rc = EIP217_COUNT_CONTROL_RD(Device,
                                 EIP163_REG_TCAM_STAT_CTRL_OFFS,
                                 &fResetAllTCAM,
                                 &fSaturateCtrs,
                                 &fAutoCtrReset,
                                 &fResetSummary,
                                 &fIgnoreECC);
    if (rc) return rc;

    IDENTIFIER_NOT_USED(fSaturateCtrs);
    IDENTIFIER_NOT_USED(fAutoCtrReset);
    IDENTIFIER_NOT_USED(fResetSummary);

    if (fExternalTCAM)
    {
        bool fWriteBusy,fReadBusy,fDisableBusy,fEnabled;

        rc = EIP163_TCAM_STATUS_RD(Device,
                                   &fWriteBusy,
                                   &fReadBusy,
                                   &fDisableBusy,
                                   &fEnabled);
        if (rc) return rc;

        if (fDisableBusy)
            return EIP163_BUSY_RETRY_LATER;
    }

    /* CDS point #1: device initialization is done */

    /* Wait till this falls to false indicating that */
    /* the device initialization is completed */
    if (fResetAllTCAM)
        return EIP163_BUSY_RETRY_LATER;
    else
        return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163Lib_Device_Is_Sync_Done
 */
static EIP163_Error_t
EIP163Lib_Device_Is_Sync_Done(
        const Device_Handle_t Device)
{
    bool fLoadUnsafe;
    uint8_t Unsafe, InFlight;
    int rc = 0;

    rc = EIP163_SAM_IN_FLIGHT_RD(Device,
                                 &Unsafe,
                                 &InFlight,
                                 &fLoadUnsafe);
    if (rc) return rc;

    IDENTIFIER_NOT_USED(InFlight);
    IDENTIFIER_NOT_USED(fLoadUnsafe);

    /* CDS point #2: device synchronization w.r.t. the requested packets */
    /* processing completion is done */

    /* Wait till this field falls to 0 indicating that */
    /* the device synchronization is completed */
    if (Unsafe == 0) return EIP163_NO_ERROR;

    return EIP163_BUSY_RETRY_LATER;
}


/*----------------------------------------------------------------------------
 * EIP163_HWRevision_Get
 */
EIP163_Error_t
EIP163_HWRevision_Get(
        const Device_Handle_t Device,
        EIP163_Capabilities_t * const Capabilities_p)
{
    int rc = 0;

    EIP163_CHECK_POINTER(Capabilities_p);

    rc = EIP163Lib_HWRevision_Get(Device,
                                  &Capabilities_p->EIP163_Options,
                                  &Capabilities_p->EIP163_Version);
    if (rc) return rc;

    rc = EIP163Lib_TCAM_HWRevision_Get(Device,
                                  &Capabilities_p->TCAM_Options,
                                  &Capabilities_p->TCAM_Version);

    if (rc) return rc;

    else return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_Device_Init
 */
EIP163_Error_t
EIP163_Device_Init(
        EIP163_IOArea_t * const IOArea_p,
        const Device_Handle_t Device,
        const EIP163_Settings_t * const Settings_p)
{
    EIP163_Capabilities_t Capabilities;
    volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_INOUT(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_POINTER(Settings_p);

    /* Detect presence of EIP-163 and TCAM devices */
    rc = EIP163Lib_Detect(Device);
    if (rc) return rc;

    rc = EIP163Lib_TCAM_Detect(Device);
    if (rc) return rc;

    /* Initialize the IO Area */
    TrueIOArea_p->Device = Device;

    rc = EIP163Lib_HWRevision_Get(Device,
                                  &Capabilities.EIP163_Options,
                                  &Capabilities.EIP163_Version);
    if (rc) return rc;

    rc = EIP163Lib_TCAM_HWRevision_Get(Device,
                                       &Capabilities.TCAM_Options,
                                       &Capabilities.TCAM_Version);
    if (rc) return rc;

    /* Check compatibility between requested mode and HW configuration */
    if (Settings_p->Mode == EIP163_MODE_EGRESS &&
        Capabilities.EIP163_Options.fIngressOnly)
        return EIP163_HW_CONFIGURATION_MISMATCH;

    /* Check compatibility between requested mode and HW configuration */
    if (Settings_p->Mode == EIP163_MODE_INGRESS &&
        Capabilities.EIP163_Options.fEgressOnly)
        return EIP163_HW_CONFIGURATION_MISMATCH;

    /* Check TCAM init data size against TCAM size */
    if (Settings_p->TCAMInit.InitData_p &&
        (Settings_p->TCAMInit.WordOffset +
        Settings_p->TCAMInit.InitData_WordCount >=
        Capabilities.EIP163_Options.Rules_Count * EIP163_REG_TCAM_ENTRY_OFFS))
        return EIP163_HW_CONFIGURATION_MISMATCH;

    TrueIOArea_p->Mode       = Settings_p->Mode;
    TrueIOArea_p->fLookupSCI = Capabilities.EIP163_Options.fLookupSCI;

    /* Remember the EIP-163 HW configuration, e, i */
    if (Capabilities.EIP163_Options.fEgressOnly)
        TrueIOArea_p->HWConf = EIP163_HW_CONF_E;
    else
        TrueIOArea_p->HWConf = EIP163_HW_CONF_I;

    /* Store the maximum number of channels the device supports */
    TrueIOArea_p->MaxChCount = Capabilities.EIP163_Options.Channel_Count;

#if defined(EIP163_IPSEC_ENABLE)
    /* store the maximum number of MTT entries the devices supports */
    TrueIOArea_p->MaxMTTCount = Capabilities.EIP163_Options.MTT_Count;
#endif
    /* Store the maximum number of SC Channels and vPorts the device supports */
    TrueIOArea_p->MaxRulesCount = Capabilities.EIP163_Options.Rules_Count;
    TrueIOArea_p->MaxvPortCount = Capabilities.EIP163_Options.vPort_Count;
    TrueIOArea_p->fExternalTCAM = Capabilities.EIP163_Options.fExternalTCAM;
    TrueIOArea_p->fHasTCAMPrio = !TrueIOArea_p->fExternalTCAM &&
        Capabilities.EIP163_Version.MajHWRevision < 3;
#if defined(EIP163_IPSEC_ENABLE)
    TrueIOArea_p->fSpareReg     = Capabilities.EIP163_Options.fSpareReg;
    TrueIOArea_p->fIPSecSupport = Capabilities.EIP163_Options.fIPSecSupport;
#endif
    TrueIOArea_p->fReadPending = false;

    rc = EIP163_GLBL_CTRL_WR(Device,
                             Settings_p->fParsePktIPsec,
                             Settings_p->fDropControlPkts
                             );
    if (rc) return rc;

#ifndef EIP163_DEV_INIT_DISABLE
    if (TrueIOArea_p->fExternalTCAM)
    {
        /* Disable all entries. */
        rc = EIP163_TCAM_ENTRY_ENABLE_CTRL_WR(Device,
                                              0,
                                              false,
                                              false,
                                              0,
                                              false,
                                              true);
        if (rc) return rc;
    }

    /* Initialize TCAM entries */
    else if (Settings_p->TCAMInit.InitData_p)

    /* Initialize TCAM entries */
    if (Settings_p->TCAMInit.InitData_p)
    {
        rc = EIP163_TCAM_WR(Device,
                            Settings_p->TCAMInit.WordOffset,
                            Settings_p->TCAMInit.InitData_p,
                            Settings_p->TCAMInit.InitData_WordCount,
                            0);
        if (rc) return rc;
    }

    /* Threshold for the frame counters */
    rc = EIP217_COUNT_FRAME_THR_64_WR(Device,
                                      EIP163_REG_TCAM_STAT_CTRL_OFFS,
                                      Settings_p->CountFrameThrLo,
                                      Settings_p->CountFrameThrHi);
    if (rc) return rc;

    /* Threshold for the channel frame counters */
    rc = EIP217_COUNT_FRAME_THR_64_WR(Device,
                                      EIP163_REG_CHAN_STAT_CTRL_OFFS,
                                      Settings_p->ChanCountFrameThrLo,
                                      Settings_p->ChanCountFrameThrHi);
    if (rc) return rc;

#if defined(EIP163_IPSEC_ENABLE)
    /* Threshold for the MTT frame counters */
    rc = EIP217_COUNT_FRAME_THR_64_WR(Device,
                                      EIP163_REG_MTT_STAT_CTRL_OFFS,
                                      Settings_p->MTTCountFrameThrLo,
                                      Settings_p->MTTCountFrameThrHi);
    if (rc) return rc;
#endif

    /* Reset all statistics counters and threshold summary registers */
    rc = EIP217_COUNT_CONTROL_WR(Device,
                                 EIP163_REG_TCAM_STAT_CTRL_OFFS,
                                 true,    /* Reset */
                                 false,
                                 false,
                                 false,
                                 false);
    if (rc) return rc;

    /* Configure the statistics module to clear-on-read and saturating */
    rc = EIP217_COUNT_CONTROL_WR(Device,
                                 EIP163_REG_TCAM_STAT_CTRL_OFFS,
                                 false,   /* Do not reset */
                                 true,    /* Saturate counters */
                                 Settings_p->fAutoStatCntrsReset,
                                 false,  /* Do not reset */
                                 false);
    if (rc) return rc;

    /* Reset all statistics counters and threshold summary registers */
    rc = EIP217_COUNT_CONTROL_WR(Device,
                                 EIP163_REG_CHAN_STAT_CTRL_OFFS,
                                 true,    /* Reset */
                                 false,
                                 false,
                                 false,
                                 false);
    if (rc) return rc;

    /* Configure the statistics module to clear-on-read and saturating */
    rc = EIP217_COUNT_CONTROL_WR(Device,
                                 EIP163_REG_CHAN_STAT_CTRL_OFFS,
                                 false,   /* Do not reset */
                                 true,    /* Saturate counters */
                                 Settings_p->fAutoStatCntrsReset,
                                 false,  /* Do not reset */
                                 false);
    if (rc) return rc;

#if defined(EIP163_IPSEC_ENABLE)
    /* Reset all statistics counters and threshold summary registers */
    rc = EIP217_COUNT_CONTROL_WR(Device,
                                 EIP163_REG_MTT_STAT_CTRL_OFFS,
                                 true,    /* Reset */
                                 false,
                                 false,
                                 false,
                                 false);
    if (rc) return rc;

    /* Configure the statistics module to clear-on-read and saturating */
    rc = EIP217_COUNT_CONTROL_WR(Device,
                                 EIP163_REG_MTT_STAT_CTRL_OFFS,
                                 false,   /* Do not reset */
                                 true,    /* Saturate counters */
                                 Settings_p->fAutoStatCntrsReset,
                                 false,   /* Do not reset */
                                 false);
    if (rc) return rc;
#endif

    {
        uint16_t TCAMCntrMask, NumTCAMCntrs;
        uint32_t ChanCntrMask, NumChanCntrs;
#if defined(EIP163_IPSEC_ENABLE)
        uint32_t MTTCntrMask, NumMTTCntrs;
#endif

        /* Retrieve number of counters for every statistics module */
        NumTCAMCntrs = sizeof(EIP163_Statistics_TCAM_t) /
                                sizeof(EIP163_UI64_t);
        NumChanCntrs = sizeof(EIP163_Statistics_Channel_t) /
                                sizeof(EIP163_UI64_t);
#if defined(EIP163_IPSEC_ENABLE)
        NumMTTCntrs = sizeof(EIP163_Statistics_MTT_t) /
                                sizeof(EIP163_UI64_t);
#endif

        /* Calculate masks for every statistics module to cover all counters */
        TCAMCntrMask = ((1 << NumTCAMCntrs) - 1);
        ChanCntrMask = ((1 << NumChanCntrs) - 1);
#if defined(EIP163_IPSEC_ENABLE)
        MTTCntrMask = ((1 << NumMTTCntrs) - 1);
#endif

        /* Enable or disable counters, depending on the value of */
        /* Settings_p->CountIncDisCtrl */
        rc = EIP217_COUNT_INCEN1_WR(Device,
                                    EIP163_REG_TCAM_STAT_CTRL_OFFS,
                                    TCAMCntrMask *
                                    !(Settings_p->CountIncDisCtrl & EIP163_CFYE_TCAM_COUNT_INC_DIS));
        if (rc) return rc;

        rc = EIP217_COUNT_INCEN1_WR(Device,
                                    EIP163_REG_CHAN_STAT_CTRL_OFFS,
                                    ChanCntrMask *
                                    !(Settings_p->CountIncDisCtrl & EIP163_CFYE_CHAN_COUNT_INC_DIS));
        if (rc) return rc;

#if defined(EIP163_IPSEC_ENABLE)
        rc = EIP217_COUNT_INCEN1_WR(Device,
                                    EIP163_REG_MTT_STAT_CTRL_OFFS,
                                    MTTCntrMask *
                                    !(Settings_p->CountIncDisCtrl & EIP163_CFYE_MTT_COUNT_INC_DIS));
        if (rc) return rc;
#endif
    }

    /* Initialize PACK_TIMING registers. */
    rc = EIP217_COUNT_PACK_TIMING_WR(Device,
                                     EIP163_REG_TCAM_STAT_CTRL_OFFS,
                                     EIP163_PACK_TIMEOUT_VALUE,
                                     EIP163_PACK_TIMEOUT_ENABLE);
    if (rc) return rc;

    rc = EIP217_COUNT_PACK_TIMING_WR(Device,
                                     EIP163_REG_CHAN_STAT_CTRL_OFFS,
                                     EIP163_PACK_TIMEOUT_VALUE,
                                     EIP163_PACK_TIMEOUT_ENABLE);
    if (rc) return rc;

    /* Initialize all channels */
    {
        unsigned int i;

        for (i = 0; i < TrueIOArea_p->MaxChCount; i++)
        {
            rc = EIP163_CHANNEL_CTRL_WR(Device,
                                        i,
#ifdef EIP163_IPSEC_ENABLE
                                        false,
#endif
                                        Settings_p->fLowLatencyBypass);
            if (rc) return rc;
        }
    }

    rc = EIP163_Device_EOP_Configure(IOArea_p,
                                     Settings_p->EOPTimeoutVal,
                                     &Settings_p->EOPTimeoutCtrl);
    if (rc) return rc;

    rc = EIP163_Device_ECC_Configure(IOArea_p,
                                     Settings_p->ECCCorrectableThr,
                                     Settings_p->ECCUncorrectableThr);
    if (rc) return rc;

    return EIP163Lib_Device_Is_Done(Device, TrueIOArea_p->fExternalTCAM);
#else
    return EIP163_NO_ERROR;
#endif /* EIP163_DEV_INIT_DISABLE */
}


/*----------------------------------------------------------------------------
 * EIP163_Device_Is_Done
 *
 */
EIP163_Error_t
EIP163_Device_Is_Done(
        const EIP163_IOArea_t * const IOArea_p)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);

    EIP163_CHECK_POINTER(IOArea_p);

    Device = TrueIOArea_p->Device;

    return EIP163Lib_Device_Is_Done(Device, TrueIOArea_p->fExternalTCAM);
}


/*----------------------------------------------------------------------------
 * EIP163_Device_Uninit
 */
EIP163_Error_t
EIP163_Device_Uninit(
        EIP163_IOArea_t * const IOArea_p)
{
    unsigned int i;
    Device_Handle_t Device;
    volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_INOUT(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);

    Device = TrueIOArea_p->Device;

    /* Reset thresholds for the frame counters */
    rc = EIP217_COUNT_FRAME_THR_64_DEFAULT_WR(Device,
                                              EIP163_REG_TCAM_STAT_CTRL_OFFS);
    if (rc) return rc;

    rc = EIP217_COUNT_FRAME_THR_64_DEFAULT_WR(Device,
                                              EIP163_REG_CHAN_STAT_CTRL_OFFS);
    if (rc) return rc;

    /* Reset all statistics counters and threshold summary registers */
    rc = EIP217_COUNT_CONTROL_DEFAULT_WR(Device,
                                         EIP163_REG_TCAM_STAT_CTRL_OFFS);
    if (rc) return rc;

    rc = EIP217_COUNT_CONTROL_DEFAULT_WR(Device,
                                         EIP163_REG_CHAN_STAT_CTRL_OFFS);
    if (rc) return rc;

    /* Reset all channels */
    for (i = 0; i < TrueIOArea_p->MaxChCount; i++)
    {
        rc = EIP163_CHANNEL_CTRL_DEFAULT_WR(Device, i);
        if (rc) return rc;
    }

    return EIP163Lib_Device_Is_Done(Device, TrueIOArea_p->fExternalTCAM);
}


/*----------------------------------------------------------------------------
 * EIP163_Device_Sync
 *
 */
EIP163_Error_t
EIP163_Device_Sync(
        EIP163_IOArea_t * const IOArea_p)
{
    Device_Handle_t Device;
    volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_INOUT(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);

    Device = TrueIOArea_p->Device;

    /* CDS point #2 */
    /* Request device synchronization w.r.t. packets currently available */
    /* in the EIP-163 pipeline */
    rc = EIP163_SAM_IN_FLIGHT_WR(Device, true);
    if (rc) return rc;

    return EIP163Lib_Device_Is_Sync_Done(Device);
}


/*----------------------------------------------------------------------------
 * EIP163_Device_Is_Sync_Done
 *
 */
EIP163_Error_t
EIP163_Device_Is_Sync_Done(
        EIP163_IOArea_t * const IOArea_p)
{
    Device_Handle_t Device;
    volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_INOUT(IOArea_p);

    EIP163_CHECK_POINTER(IOArea_p);

    Device = TrueIOArea_p->Device;

    return EIP163Lib_Device_Is_Sync_Done(Device);
}


/*----------------------------------------------------------------------------
 * EIP163_Device_Clocks_On
 */
EIP163_Error_t
EIP163_Device_Clocks_On(
        const EIP163_IOArea_t * const IOArea_p,
        const uint32_t ClockMask,
        const bool fAlwaysOn)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);

    EIP163_CHECK_POINTER(IOArea_p);

    Device = TrueIOArea_p->Device;

    return EIP163_FORCE_CLOCK_ON_WR(Device, fAlwaysOn ? ClockMask : 0);
}


/*----------------------------------------------------------------------------
 * EIP163_Device_Clocks_Off
 */
EIP163_Error_t
EIP163_Device_Clocks_Off(
        const EIP163_IOArea_t * const IOArea_p,
        const uint32_t ClockMask)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);

    EIP163_CHECK_POINTER(IOArea_p);

    Device = TrueIOArea_p->Device;

    return EIP163_FORCE_CLOCK_OFF_WR(Device, ClockMask);
}


/*----------------------------------------------------------------------------
 * EIP163_Device_Update
 */
EIP163_Error_t
EIP163_Device_Update(
        const EIP163_IOArea_t * const IOArea_p,
        unsigned int ChannelId,
        const EIP163_Device_Control_t * const Control_p)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_POINTER(Control_p);
    EIP163_CHECK_INT_ATMOST(ChannelId, TrueIOArea_p->MaxChCount - 1);

    Device = TrueIOArea_p->Device;

    rc = EIP163_CHANNEL_CTRL_WR(Device,
                                ChannelId,
#if defined(EIP163_IPSEC_ENABLE)
                                Control_p->fIPSec,
#endif
                                Control_p->fLowLatencyBypass);
    if (rc) return rc;

    if (Control_p->Exceptions_p)
    {
        rc = EIP163_SAM_POLICY_WR(Device,
                                  ChannelId,
                                  Control_p->Exceptions_p->DropAction,
                                  Control_p->Exceptions_p->fForceDrop,
                                  Control_p->Exceptions_p->fDefaultVPortValid,
                                  Control_p->Exceptions_p->ECCDropAction,
                                  Control_p->Exceptions_p->fShouldSecure,
                                  Control_p->Exceptions_p->DefaultVPort);
        if (rc) return rc;
    }

#if defined(EIP163_VXLAN_ENABLE)
    if (Control_p->L3L4_p)
    {
        rc = EIP163_L3L4_ENABLE_WR(Device,
                                   ChannelId,
                                   Control_p->L3L4_p->flags);
        if (rc) return rc;
    }
#endif

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_Device_Control_Read
 */
EIP163_Error_t
EIP163_Device_Control_Read(
        const EIP163_IOArea_t * const IOArea_p,
        unsigned int ChannelId,
        EIP163_Device_Control_t * const Control_p)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    uint8_t DropAction, ECCDropAction;
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_POINTER(Control_p);
    EIP163_CHECK_INT_ATMOST(ChannelId, TrueIOArea_p->MaxChCount - 1);

    Device = TrueIOArea_p->Device;

#if defined(EIP163_IPSEC_ENABLE)
    Control_p->fIPSec = false;
#endif
    rc = EIP163_CHANNEL_CTRL_RD(Device,
                                ChannelId,
#if defined(EIP163_IPSEC_ENABLE)
                                &Control_p->fIPSec,
#endif
                                &Control_p->fLowLatencyBypass);
    if (rc) return rc;

    if (Control_p->Exceptions_p)
    {
        rc = EIP163_SAM_POLICY_RD(Device,
                                  ChannelId,
                                  &DropAction,
                                  &Control_p->Exceptions_p->fForceDrop,
                                  &Control_p->Exceptions_p->fDefaultVPortValid,
                                  &ECCDropAction,
                                  &Control_p->Exceptions_p->fShouldSecure,
                                  &Control_p->Exceptions_p->DefaultVPort);
        if (rc) return rc;

        Control_p->Exceptions_p->DropAction = (EIP163_DropType_t)DropAction;
        Control_p->Exceptions_p->ECCDropAction = (EIP163_DropType_t)ECCDropAction;
    }

#if defined(EIP163_VXLAN_ENABLE)
    if (Control_p->L3L4_p)
    {
        rc = EIP163_L3L4_ENABLE_RD(Device,
                                       ChannelId,
                                       &Control_p->L3L4_p->flags);
        if (rc) return rc;
    }
#endif

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_Device_ECC_Configure
 */
EIP163_Error_t
EIP163_Device_ECC_Configure(
        const EIP163_IOArea_t * const IOArea_p,
        const unsigned int CorrectableThr,
        const unsigned int UncorrectableThr)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    unsigned int CorrThrValue, DerrThrValue;
    uint32_t CorrMaskValue, DerrMaskValue;
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);

    Device = TrueIOArea_p->Device;

    if (CorrectableThr > 0)
    {
        CorrMaskValue = MASK_16_BITS;
        CorrThrValue = CorrectableThr - 1;
    }
    else
    {
        CorrMaskValue = 0;
        CorrThrValue = 0xffff;
    }

    if (UncorrectableThr > 0)
    {
        DerrMaskValue = MASK_16_BITS;
        DerrThrValue = UncorrectableThr - 1;
    }
    else
    {
        DerrMaskValue = 0;
        DerrThrValue = 0xffff;
    }

    rc = EIP163_ECC_THRESHOLDS_WR(Device, CorrThrValue, DerrThrValue);
    if (rc) return rc;

    rc = EIP163_ECC_CORR_ENABLE_WR(Device, CorrMaskValue);
    if (rc) return rc;

    rc = EIP163_ECC_DERR_ENABLE_WR(Device, DerrMaskValue);
    if (rc) return rc;

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_Device_ECC_Configuration_Get
 */
EIP163_Error_t
EIP163_Device_ECC_Configuration_Get(
        const EIP163_IOArea_t * const IOArea_p,
        unsigned int * const CorrectableThr_p,
        unsigned int * const UncorrectableThr_p)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    unsigned int CorrThrValue, DerrThrValue;
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);

    Device = TrueIOArea_p->Device;

    rc = EIP163_ECC_THRESHOLDS_RD(Device, &CorrThrValue, &DerrThrValue);

    if (rc) return rc;

    if (CorrThrValue == 0xffff)
    {
        *CorrectableThr_p = 0;
    }
    else
    {
        *CorrectableThr_p = CorrThrValue + 1;
    }

    if (DerrThrValue == 0xffff)
    {
        *UncorrectableThr_p = 0;
    }
    else
    {
        *UncorrectableThr_p = DerrThrValue + 1;
    }

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_Device_ECCStatus_Get
  */
EIP163_Error_t
EIP163_Device_ECCStatus_Get(
        const EIP163_IOArea_t * const IOArea_p,
        EIP163_Device_ECCStatus_t * const ECCStatus_p)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    unsigned int i;
    uint32_t CorrStatus, DerrStatus;
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_POINTER(ECCStatus_p);

    Device = TrueIOArea_p->Device;

    rc = EIP163_ECC_THR_CORR_STAT_RD(Device, &CorrStatus);
    if (rc) return rc;

    rc = EIP163_ECC_THR_DERR_STAT_RD(Device, &DerrStatus);
    if (rc) return rc;

    for (i = 0; i < EIP163_ECC_NOF_STATUS_COUNTERS; i++)
    {
        unsigned int CorrValue,DerrValue;

        rc = EIP163_ECC_COUNTER_RAM_RD(Device, i, &CorrValue, &DerrValue);
        if (rc) return rc;

        rc = EIP163_ECC_COUNTER_RAM_WR(Device, i, CorrValue, DerrValue);
        if (rc) return rc;

        ECCStatus_p[i].CorrectableCount = CorrValue;
        ECCStatus_p[i].UncorrectableCount = DerrValue;
        ECCStatus_p[i].fCorrectableThr = (CorrStatus & (1<<i)) != 0;
        ECCStatus_p[i].fUncorrectableThr = (DerrStatus & (1<<i)) != 0;
    }

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_Device_PktProcessDebug_Get
 */
EIP163_Error_t
EIP163_Device_PktProcessDebug_Get(
        const EIP163_IOArea_t * const IOArea_p,
        EIP163_Device_PktProcessDebug_t * const PktProcessDebug_p)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_POINTER(PktProcessDebug_p);

    Device = TrueIOArea_p->Device;

    rc = EIP163_CP_MATCH_DEBUG_RD(Device, &PktProcessDebug_p->CPMatchDebug);
    if (rc) return rc;

    rc = EIP163_TCAM_DEBUG_RD(Device, &PktProcessDebug_p->TCAMDebug);
    if (rc) return rc;

    rc = EIP163_SECTAG_DEBUG_RD(Device, &PktProcessDebug_p->SecTAGDebug);
    if (rc) return rc;

    rc = EIP163_SAMPP_DEBUG_RD(Device,
                               &PktProcessDebug_p->SAMPPDebug1,
                               &PktProcessDebug_p->SAMPPDebug2,
                               &PktProcessDebug_p->SAMPPDebug3);
    if (rc) return rc;

    rc = EIP163_DBG_PARSED_DA_RD(Device,
                                 &PktProcessDebug_p->ParsedDALo,
                                 &PktProcessDebug_p->ParsedDAHi);
    if (rc) return rc;

    rc = EIP163_DBG_PARSED_SA_RD(Device,
                                 &PktProcessDebug_p->ParsedSALo,
                                 &PktProcessDebug_p->ParsedSAHi);
    if (rc) return rc;

    rc = EIP163_DBG_PARSED_SECTAG_RD(Device,
                                     &PktProcessDebug_p->ParsedSecTAGLo,
                                     &PktProcessDebug_p->ParsedSecTAGHi);
    if (rc) return rc;

    rc = EIP163_DEBUG_FLOW_LOOKUP_RD(Device,
                                     &PktProcessDebug_p->DebugFlowLookup);
    if (rc) return rc;

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_Device_EOP_Configure
 */
EIP163_Error_t
EIP163_Device_EOP_Configure(
        const EIP163_IOArea_t * const IOArea_p,
        const unsigned int EOPTimeoutVal,
        const EIP163_Ch_Mask_t * const EOPTimeoutCtrl_p)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    uint16_t ChannelCount = TrueIOArea_p->MaxChCount;
    EIP163_Ch_Mask_t EOPTimeoutCtrl;
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_POINTER(EOPTimeoutCtrl_p);

    Device = TrueIOArea_p->Device;

    rc = EIP163_RX_TIMEOUT_VAL_WR(Device, EOPTimeoutVal);
    if (rc) return rc;

    memcpy(&EOPTimeoutCtrl, EOPTimeoutCtrl_p, sizeof(EIP163_Ch_Mask_t));
    MaskUnusedChBits(&EOPTimeoutCtrl, ChannelCount);

    rc = EIP163_RX_TIMEOUT_CTRL_WR(Device, ChannelCount, &EOPTimeoutCtrl);
    if (rc) return rc;

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_Device_EOP_Configuration_Get
 */
EIP163_Error_t
EIP163_Device_EOP_Configuration_Get(
        const EIP163_IOArea_t * const IOArea_p,
        unsigned int * const EOPTimeoutVal_p,
        EIP163_Ch_Mask_t * const EOPTimeoutCtrl_p)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    uint16_t ChannelCount = TrueIOArea_p->MaxChCount;
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_POINTER(EOPTimeoutVal_p);

    Device = TrueIOArea_p->Device;

    rc = EIP163_RX_TIMEOUT_VAL_RD(Device, EOPTimeoutVal_p);
    if (rc) return rc;

    rc = EIP163_RX_TIMEOUT_CTRL_RD(Device, ChannelCount, EOPTimeoutCtrl_p);
    if (rc) return rc;

    MaskUnusedChBits(EOPTimeoutCtrl_p, ChannelCount);

    return EIP163_NO_ERROR;

}


/*----------------------------------------------------------------------------
 * EIP163_Device_InsertSOP
 */
EIP163_Error_t
EIP163_Device_InsertSOP(
        const EIP163_IOArea_t * const IOArea_p,
         const EIP163_Ch_Mask_t * const ChannelMask_p)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    uint16_t ChannelCount = TrueIOArea_p->MaxChCount;
    EIP163_Ch_Mask_t Ch_Mask;
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_POINTER(ChannelMask_p);

    if (0 == ChannelCount) return EIP163_ARGUMENT_ERROR;
    Device = TrueIOArea_p->Device;

    memcpy(&Ch_Mask, ChannelMask_p, sizeof(EIP163_Ch_Mask_t));
    MaskUnusedChBits(&Ch_Mask, ChannelCount);

    rc = EIP163_RX_INSERT_SOP_WR(Device, ChannelCount, &Ch_Mask);
    if (rc) return rc;

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_Device_InsertEOP
 */
EIP163_Error_t
EIP163_Device_InsertEOP(
        const EIP163_IOArea_t * const IOArea_p,
        const EIP163_Ch_Mask_t * const ChannelMask_p)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    uint16_t ChannelCount = TrueIOArea_p->MaxChCount;
    EIP163_Ch_Mask_t Ch_Mask;
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_POINTER(ChannelMask_p);

    Device = TrueIOArea_p->Device;

    memcpy(&Ch_Mask, ChannelMask_p, sizeof(EIP163_Ch_Mask_t));
    MaskUnusedChBits(&Ch_Mask, ChannelCount);

    rc = EIP163_RX_INSERT_EOP_WR(Device, ChannelCount, &Ch_Mask);
    if (rc) return rc;

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_HeaderParser_Update
 */
EIP163_Error_t
EIP163_HeaderParser_Update(
        const EIP163_IOArea_t * const IOArea_p,
        unsigned int ChannelId,
        const EIP163_HeaderParser_t * const HdrParser_p)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_POINTER(HdrParser_p);
    EIP163_CHECK_INT_ATMOST(ChannelId, TrueIOArea_p->MaxChCount - 1);

    Device = TrueIOArea_p->Device;

#if defined(EIP163_IPSEC_ENABLE)
    if (HdrParser_p->EgressHeader_p)
    {
        /* Egress header is egress only operation */
        if (TrueIOArea_p->HWConf == EIP163_HW_CONF_I ||
            TrueIOArea_p->Mode   == EIP163_MODE_INGRESS)
            return EIP163_HW_CONFIGURATION_MISMATCH;

        rc = EIP163_EGRESS_HDR_ETYPE_WR(Device,
                                        ChannelId,
                                        HdrParser_p->EgressHeader_p->EgressHeaderEtype,
                                        HdrParser_p->EgressHeader_p->fEnable);
        if (rc) return rc;
    }
#endif

    if (HdrParser_p->SecTAG_Parser_p)
    {
        /* Check if the requested operation is supported by device */
        if (HdrParser_p->SecTAG_Parser_p->fLookupUseSCI &&
            !TrueIOArea_p->fLookupSCI)
            return EIP163_HW_CONFIGURATION_MISMATCH;

        rc = EIP163_SAM_NM_PARAMS_WR(Device,
                                     ChannelId,
                                     HdrParser_p->SecTAG_Parser_p->fCompType,
                                     HdrParser_p->SecTAG_Parser_p->fCheckVersion,
                                     HdrParser_p->SecTAG_Parser_p->fCheckKay,
                                     HdrParser_p->SecTAG_Parser_p->fLookupUseSCI,
                                     HdrParser_p->SecTAG_Parser_p->MACsecTagValue);
        if (rc) return rc;
    }

#if defined(EIP163_IPSEC_ENABLE)
    if (HdrParser_p->MPLS_Parser_p)
    {
        rc = EIP163_MPLS_ENB_SELECT_WR(Device,
                                       ChannelId,
                                       HdrParser_p->MPLS_Parser_p->MPLS3_Select1,
                                       HdrParser_p->MPLS_Parser_p->MPLS3_Select2,
                                       HdrParser_p->MPLS_Parser_p->MPLS4_Select1,
                                       HdrParser_p->MPLS_Parser_p->MPLS4_Select2,
                                       HdrParser_p->MPLS_Parser_p->MPLS5_Select1,
                                       HdrParser_p->MPLS_Parser_p->MPLS5_Select2,
                                       HdrParser_p->MPLS_Parser_p->MPLS_Etype[0].fCompare,
                                       HdrParser_p->MPLS_Parser_p->MPLS_Etype[1].fCompare,
                                       HdrParser_p->MPLS_Parser_p->MPLS_Etype[2].fCompare,
                                       HdrParser_p->MPLS_Parser_p->MPLS_Etype[3].fCompare);
        if (rc) return rc;

        if (HdrParser_p->MPLS_Parser_p->MPLS_Etype[0].fCompare ||
            HdrParser_p->MPLS_Parser_p->MPLS_Etype[1].fCompare)
        {
            rc = EIP163_MPLS_TYPE1_WR(
                          Device,
                          HdrParser_p->MPLS_Parser_p->MPLS_Etype[0].MPLS_Etype,
                          HdrParser_p->MPLS_Parser_p->MPLS_Etype[1].MPLS_Etype);
            if (rc) return rc;
        }

        if (HdrParser_p->MPLS_Parser_p->MPLS_Etype[2].fCompare ||
            HdrParser_p->MPLS_Parser_p->MPLS_Etype[3].fCompare)
        {
            rc = EIP163_MPLS_TYPE2_WR(
                      Device,
                      HdrParser_p->MPLS_Parser_p->MPLS_Etype[2].MPLS_Etype,
                      HdrParser_p->MPLS_Parser_p->MPLS_Etype[3].MPLS_Etype);
            if (rc) return rc;
        }
    }
#endif

#if defined(EIP163_IPSEC_ENABLE)
    if (HdrParser_p->IPsec_Parser_p)
    {
        EIP163_IPSEC_ENABLE_t IPsecCtrl;

        IPsecCtrl.fParseESP    = HdrParser_p->IPsec_Parser_p->fParseESP;
        IPsecCtrl.fParseIKE    = HdrParser_p->IPsec_Parser_p->fParseIKE;
        IPsecCtrl.fParseIP     = HdrParser_p->IPsec_Parser_p->fParseIP;
        IPsecCtrl.fParseNAT    = HdrParser_p->IPsec_Parser_p->fParseNAT;
        IPsecCtrl.fParseNATIKE = HdrParser_p->IPsec_Parser_p->fParseNATIKE;
        IPsecCtrl.fParseNATKeepAlive = HdrParser_p->IPsec_Parser_p->fParseNATKeepAlive;
        IPsecCtrl.fParseUDP = HdrParser_p->IPsec_Parser_p->fParseUDP;
        IPsecCtrl.fVerifyUDPChkSum = HdrParser_p->IPsec_Parser_p->fVerifyUDPChkSum;
        IPsecCtrl.fMACDACheck  = HdrParser_p->IPsec_Parser_p->fMACDACheck;
        IPsecCtrl.fAllowFragments  = HdrParser_p->IPsec_Parser_p->fAllowFragments;
        IPsecCtrl.fIgnoreIPv4ChkSum  = HdrParser_p->IPsec_Parser_p->fIgnoreIPv4ChkSum;
        IPsecCtrl.fSubParseIKE  = HdrParser_p->IPsec_Parser_p->fSubParseIKE;
        IPsecCtrl.fSubParseNATIKE  = HdrParser_p->IPsec_Parser_p->fSubParseNATIKE;
        IPsecCtrl.fSubParseNATKeepAlive  = HdrParser_p->IPsec_Parser_p->fSubParseNATKeepAlive;

        rc = EIP163_IPSEC_ENABLE_WR(Device,
                                    ChannelId,
                                    &IPsecCtrl);
        if (rc) return rc;

        rc = EIP163_UDP_PORT1_WR(Device,
                                 HdrParser_p->IPsec_Parser_p->IKE_Port,
                                 HdrParser_p->IPsec_Parser_p->NAT_Port);
        if (rc) return rc;

        rc =  EIP163_CP_MAC_DA_IPSEC_LO_WR(Device,
                                           HdrParser_p->IPsec_Parser_p->MAC_DA[0],
                                           HdrParser_p->IPsec_Parser_p->MAC_DA[1],
                                           HdrParser_p->IPsec_Parser_p->MAC_DA[2],
                                           HdrParser_p->IPsec_Parser_p->MAC_DA[3]);
        if (rc) return rc;

        rc =  EIP163_CP_MAC_DA_IPSEC_HI_WR(Device,
                                           HdrParser_p->IPsec_Parser_p->MAC_DA[4],
                                           HdrParser_p->IPsec_Parser_p->MAC_DA[5]);
        if (rc) return rc;
    }
#endif

    if (HdrParser_p->VLAN_Parser_p)
    {
        rc = EIP163_SAM_CP_TAG_ENB_WR(Device,
                                 ChannelId,
                                 HdrParser_p->VLAN_Parser_p->CP.fParseQTag,
                                 HdrParser_p->VLAN_Parser_p->CP.fParseStag1,
                                 HdrParser_p->VLAN_Parser_p->CP.fParseStag2,
                                 HdrParser_p->VLAN_Parser_p->CP.fParseStag3,
                                 HdrParser_p->VLAN_Parser_p->CP.fParseQinQ);
        if (rc) return rc;

        /* Note: EIP163_VLAN_UP_MAX_COUNT = 8 */
        rc = EIP163_SAM_CP_TAG_WR(Device,
                                  HdrParser_p->VLAN_Parser_p->UpTable1[0],
                                  HdrParser_p->VLAN_Parser_p->UpTable1[1],
                                  HdrParser_p->VLAN_Parser_p->UpTable1[2],
                                  HdrParser_p->VLAN_Parser_p->UpTable1[3],
                                  HdrParser_p->VLAN_Parser_p->UpTable1[4],
                                  HdrParser_p->VLAN_Parser_p->UpTable1[5],
                                  HdrParser_p->VLAN_Parser_p->UpTable1[6],
                                  HdrParser_p->VLAN_Parser_p->UpTable1[7],
                                  HdrParser_p->VLAN_Parser_p->DefaultUp,
                                  HdrParser_p->VLAN_Parser_p->fSTagUpEnable,
                                  HdrParser_p->VLAN_Parser_p->fQTagUpEnable);
        if (rc) return rc;

        if (HdrParser_p->VLAN_Parser_p->CP.fParseQinQ)
        {
            rc = EIP163_SAM_CP_TAG2_WR(Device,
                                    HdrParser_p->VLAN_Parser_p->UpTable2[0],
                                    HdrParser_p->VLAN_Parser_p->UpTable2[1],
                                    HdrParser_p->VLAN_Parser_p->UpTable2[2],
                                    HdrParser_p->VLAN_Parser_p->UpTable2[3],
                                    HdrParser_p->VLAN_Parser_p->UpTable2[4],
                                    HdrParser_p->VLAN_Parser_p->UpTable2[5],
                                    HdrParser_p->VLAN_Parser_p->UpTable2[6],
                                    HdrParser_p->VLAN_Parser_p->UpTable2[7]);
            if (rc) return rc;
        }

        if (HdrParser_p->VLAN_Parser_p->CP.fParseQTag  ||
            HdrParser_p->VLAN_Parser_p->CP.fParseStag1)
        {
            rc = EIP163_SAM_PP_TAGS_WR(
                    Device,
                    HdrParser_p->VLAN_Parser_p->QTag,
                    HdrParser_p->VLAN_Parser_p->STag1);
            if (rc) return rc;
        }

        if (HdrParser_p->VLAN_Parser_p->CP.fParseStag2  ||
            HdrParser_p->VLAN_Parser_p->CP.fParseStag3)
        {
            rc = EIP163_SAM_PP_TAGS2_WR(
                            Device,
                            HdrParser_p->VLAN_Parser_p->STag2,
                            HdrParser_p->VLAN_Parser_p->STag3);
            if (rc) return rc;
        }
    }
#if defined(EIP163_VXLAN_ENABLE)
    if (HdrParser_p->L4_Ports_p)
    {
#ifdef EIP163_VXLAN_ENABLE
        rc = EIP163_UDP_PORT2_WR(
                    Device,
                    HdrParser_p->L4_Ports_p->VxLAN_Port1,
                    HdrParser_p->L4_Ports_p->VxLAN_Port2);
        if (rc) return rc;
#endif
    }
#endif

    return EIP163_NO_ERROR;
}

/*
 * EIP163_HeaderParser_Read
 */
EIP163_Error_t
EIP163_HeaderParser_Read(
        const EIP163_IOArea_t * const IOArea_p,
        unsigned int ChannelId,
        EIP163_HeaderParser_t * const HdrParser_p)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_POINTER(HdrParser_p);
    EIP163_CHECK_INT_ATMOST(ChannelId, TrueIOArea_p->MaxChCount - 1);

    Device = TrueIOArea_p->Device;

#if defined(EIP163_IPSEC_ENABLE)
    if (HdrParser_p->EgressHeader_p)
    {
        /* Egress header is egress only operation */
        if (TrueIOArea_p->HWConf != EIP163_HW_CONF_I &&
            TrueIOArea_p->Mode != EIP163_MODE_INGRESS)
        {
            rc = EIP163_EGRESS_HDR_ETYPE_RD(Device,
                                            ChannelId,
                                            &HdrParser_p->EgressHeader_p->EgressHeaderEtype,
                                            &HdrParser_p->EgressHeader_p->fEnable);
            if (rc) return rc;
        }
    }
#endif

    if (HdrParser_p->SecTAG_Parser_p)
    {
        rc = EIP163_SAM_NM_PARAMS_RD(Device,
                                ChannelId,
                                &HdrParser_p->SecTAG_Parser_p->fCompType,
                                &HdrParser_p->SecTAG_Parser_p->fCheckVersion,
                                &HdrParser_p->SecTAG_Parser_p->fCheckKay,
                                &HdrParser_p->SecTAG_Parser_p->fLookupUseSCI,
                                &HdrParser_p->SecTAG_Parser_p->MACsecTagValue);
        if (rc) return rc;
    }

#if defined(EIP163_IPSEC_ENABLE)
    if (HdrParser_p->MPLS_Parser_p)
    {
        uint8_t MPLS3_Select1, MPLS3_Select2;
        uint8_t MPLS4_Select1, MPLS4_Select2;
        uint8_t MPLS5_Select1, MPLS5_Select2;

        rc = EIP163_MPLS_ENB_SELECT_RD(Device,
                                  ChannelId,
                                  &MPLS3_Select1,
                                  &MPLS3_Select2,
                                  &MPLS4_Select1,
                                  &MPLS4_Select2,
                                  &MPLS5_Select1,
                                  &MPLS5_Select2,
                                  &HdrParser_p->MPLS_Parser_p->MPLS_Etype[0].fCompare,
                                  &HdrParser_p->MPLS_Parser_p->MPLS_Etype[1].fCompare,
                                  &HdrParser_p->MPLS_Parser_p->MPLS_Etype[2].fCompare,
                                  &HdrParser_p->MPLS_Parser_p->MPLS_Etype[3].fCompare);
        if (rc) return rc;

        HdrParser_p->MPLS_Parser_p->MPLS3_Select1 = MPLS3_Select1;
        HdrParser_p->MPLS_Parser_p->MPLS3_Select2 = MPLS3_Select2;
        HdrParser_p->MPLS_Parser_p->MPLS4_Select1 = MPLS4_Select1;
        HdrParser_p->MPLS_Parser_p->MPLS4_Select2 = MPLS4_Select2;
        HdrParser_p->MPLS_Parser_p->MPLS5_Select1 = MPLS5_Select1;
        HdrParser_p->MPLS_Parser_p->MPLS5_Select2 = MPLS5_Select2;

        if (HdrParser_p->MPLS_Parser_p->MPLS_Etype[0].fCompare ||
            HdrParser_p->MPLS_Parser_p->MPLS_Etype[1].fCompare)
        {
            rc = EIP163_MPLS_TYPE1_RD(
                      Device,
                      &HdrParser_p->MPLS_Parser_p->MPLS_Etype[0].MPLS_Etype,
                      &HdrParser_p->MPLS_Parser_p->MPLS_Etype[1].MPLS_Etype);
            if (rc) return rc;
        }

        if (HdrParser_p->MPLS_Parser_p->MPLS_Etype[2].fCompare ||
            HdrParser_p->MPLS_Parser_p->MPLS_Etype[3].fCompare)
        {
            rc = EIP163_MPLS_TYPE2_RD(
                      Device,
                      &HdrParser_p->MPLS_Parser_p->MPLS_Etype[2].MPLS_Etype,
                      &HdrParser_p->MPLS_Parser_p->MPLS_Etype[3].MPLS_Etype);
            if (rc) return rc;
        }
    }

#endif

#if defined(EIP163_IPSEC_ENABLE)
    if (HdrParser_p->IPsec_Parser_p)
    {
        EIP163_IPSEC_ENABLE_t IPsecCtrl;
        ZEROINIT(IPsecCtrl);

        rc = EIP163_IPSEC_ENABLE_RD(Device,
                                    ChannelId,
                                    &IPsecCtrl);
        if (rc) return rc;

        HdrParser_p->IPsec_Parser_p->fParseIP = IPsecCtrl.fParseIP;
        HdrParser_p->IPsec_Parser_p->fParseUDP = IPsecCtrl.fParseUDP;
        HdrParser_p->IPsec_Parser_p->fParseNAT = IPsecCtrl.fParseNAT;
        HdrParser_p->IPsec_Parser_p->fParseESP = IPsecCtrl.fParseESP;
        HdrParser_p->IPsec_Parser_p->fParseIKE = IPsecCtrl.fParseIKE;
        HdrParser_p->IPsec_Parser_p->fParseNATIKE = IPsecCtrl.fParseNATIKE;
        HdrParser_p->IPsec_Parser_p->fParseNATKeepAlive = IPsecCtrl.fParseNATKeepAlive;
        HdrParser_p->IPsec_Parser_p->fVerifyUDPChkSum = IPsecCtrl.fVerifyUDPChkSum;
        HdrParser_p->IPsec_Parser_p->fMACDACheck = IPsecCtrl.fMACDACheck;
        HdrParser_p->IPsec_Parser_p->fAllowFragments = IPsecCtrl.fAllowFragments;
        HdrParser_p->IPsec_Parser_p->fIgnoreIPv4ChkSum = IPsecCtrl.fIgnoreIPv4ChkSum;
        HdrParser_p->IPsec_Parser_p->fSubParseIKE = IPsecCtrl.fSubParseIKE;
        HdrParser_p->IPsec_Parser_p->fSubParseNATIKE = IPsecCtrl.fSubParseNATIKE;
        HdrParser_p->IPsec_Parser_p->fSubParseNATKeepAlive = IPsecCtrl.fSubParseNATKeepAlive;

        rc = EIP163_UDP_PORT1_RD(Device,
                                 &HdrParser_p->IPsec_Parser_p->IKE_Port,
                                 &HdrParser_p->IPsec_Parser_p->NAT_Port);
        if (rc) return rc;

        rc =  EIP163_CP_MAC_DA_IPSEC_LO_RD(Device,
                                           &HdrParser_p->IPsec_Parser_p->MAC_DA[0],
                                           &HdrParser_p->IPsec_Parser_p->MAC_DA[1],
                                           &HdrParser_p->IPsec_Parser_p->MAC_DA[2],
                                           &HdrParser_p->IPsec_Parser_p->MAC_DA[3]);
        if (rc) return rc;

        rc =  EIP163_CP_MAC_DA_IPSEC_HI_RD(Device,
                                           &HdrParser_p->IPsec_Parser_p->MAC_DA[5],
                                           &HdrParser_p->IPsec_Parser_p->MAC_DA[6]);
        if (rc) return rc;
    }
#endif

    if (HdrParser_p->VLAN_Parser_p)
    {
        rc = EIP163_SAM_CP_TAG_ENB_RD(Device,
                                 ChannelId,
                                 &HdrParser_p->VLAN_Parser_p->CP.fParseQTag,
                                 &HdrParser_p->VLAN_Parser_p->CP.fParseStag1,
                                 &HdrParser_p->VLAN_Parser_p->CP.fParseStag2,
                                 &HdrParser_p->VLAN_Parser_p->CP.fParseStag3,
                                 &HdrParser_p->VLAN_Parser_p->CP.fParseQinQ);
        if (rc) return rc;

        /* Note: EIP163_VLAN_UP_MAX_COUNT = 8 */
        rc = EIP163_SAM_CP_TAG_RD(Device,
                             &HdrParser_p->VLAN_Parser_p->UpTable1[0],
                             &HdrParser_p->VLAN_Parser_p->UpTable1[1],
                             &HdrParser_p->VLAN_Parser_p->UpTable1[2],
                             &HdrParser_p->VLAN_Parser_p->UpTable1[3],
                             &HdrParser_p->VLAN_Parser_p->UpTable1[4],
                             &HdrParser_p->VLAN_Parser_p->UpTable1[5],
                             &HdrParser_p->VLAN_Parser_p->UpTable1[6],
                             &HdrParser_p->VLAN_Parser_p->UpTable1[7],
                             &HdrParser_p->VLAN_Parser_p->DefaultUp,
                             &HdrParser_p->VLAN_Parser_p->fSTagUpEnable,
                             &HdrParser_p->VLAN_Parser_p->fQTagUpEnable);
        if (rc) return rc;

        if (HdrParser_p->VLAN_Parser_p->CP.fParseQinQ)
        {
            rc = EIP163_SAM_CP_TAG2_RD(Device,
                                  &HdrParser_p->VLAN_Parser_p->UpTable2[0],
                                  &HdrParser_p->VLAN_Parser_p->UpTable2[1],
                                  &HdrParser_p->VLAN_Parser_p->UpTable2[2],
                                  &HdrParser_p->VLAN_Parser_p->UpTable2[3],
                                  &HdrParser_p->VLAN_Parser_p->UpTable2[4],
                                  &HdrParser_p->VLAN_Parser_p->UpTable2[5],
                                  &HdrParser_p->VLAN_Parser_p->UpTable2[6],
                                  &HdrParser_p->VLAN_Parser_p->UpTable2[7]);
            if (rc) return rc;
        }

        if (HdrParser_p->VLAN_Parser_p->CP.fParseQTag  ||
            HdrParser_p->VLAN_Parser_p->CP.fParseStag1)
        {
            rc = EIP163_SAM_PP_TAGS_RD(
                                Device,
                                &HdrParser_p->VLAN_Parser_p->QTag,
                                &HdrParser_p->VLAN_Parser_p->STag1);
            if (rc) return rc;
        }

        if (HdrParser_p->VLAN_Parser_p->CP.fParseStag2  ||
            HdrParser_p->VLAN_Parser_p->CP.fParseStag3)
        {
           rc = EIP163_SAM_PP_TAGS2_RD(
                    Device,
                    &HdrParser_p->VLAN_Parser_p->STag2,
                    &HdrParser_p->VLAN_Parser_p->STag3);
           if (rc) return rc;
        }
    }
#if defined(EIP163_VXLAN_ENABLE)
    if (HdrParser_p->L4_Ports_p)
    {
#ifdef EIP163_VXLAN_ENABLE
        rc = EIP163_UDP_PORT2_RD(
                    Device,
                    &HdrParser_p->L4_Ports_p->VxLAN_Port1,
                    &HdrParser_p->L4_Ports_p->VxLAN_Port2);
        if (rc) return rc;
#endif
    }
#endif

    return EIP163_NO_ERROR;
}

static bool EIP163Lib_AnyEnabled(
    const EIP163_ControlPacket_t * const CP_p,
    uint32_t mask)
{
    if ((CP_p->CPMatchEnableMask & mask) != 0)
        return true;
    else
        return false;
}

/*----------------------------------------------------------------------------
 * EIP163_ControlPacket_Update
 */
EIP163_Error_t
EIP163_ControlPacket_Update(
        const EIP163_IOArea_t * const IOArea_p,
        unsigned int ChannelId,
        const EIP163_ControlPacket_t * const CP_p)
{
    unsigned int i;
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_POINTER(CP_p);
    EIP163_CHECK_INT_ATMOST(ChannelId, TrueIOArea_p->MaxChCount - 1);

    Device = TrueIOArea_p->Device;

    if (EIP163Lib_AnyEnabled(CP_p, EIP163_REG_CP_MAC_DA_ET_MATCH_MASK))
    {
        for (i = 0; i < EIP163_MAC_DA_ET_MATCH_RULES_COUNT; i++)
        {
            if (EIP163Lib_AnyEnabled(CP_p,(BIT_0 << i)))
            {
#ifdef EIP163_STRICT_ARGS
                if (CP_p->MAC_DA_ET_Rules[i].MAC_DA_p == NULL)
                    return EIP163_ARGUMENT_ERROR;
#endif

                rc = EIP163_CP_MAC_DA_MATCH_WR(
                                      Device,
                                      i,
                                      CP_p->MAC_DA_ET_Rules[i].MAC_DA_p[0],
                                      CP_p->MAC_DA_ET_Rules[i].MAC_DA_p[1],
                                      CP_p->MAC_DA_ET_Rules[i].MAC_DA_p[2],
                                      CP_p->MAC_DA_ET_Rules[i].MAC_DA_p[3]);
                if (rc) return rc;

                rc = EIP163_CP_MAC_DA_ET_MATCH_WR(
                                      Device,
                                      i,
                                      CP_p->MAC_DA_ET_Rules[i].MAC_DA_p[4],
                                      CP_p->MAC_DA_ET_Rules[i].MAC_DA_p[5],
                                      CP_p->MAC_DA_ET_Rules[i].EtherType);
                if (rc) return rc;
            }
            else if (EIP163Lib_AnyEnabled(CP_p,(BIT_8 << i)))
            {
                rc = EIP163_CP_MAC_DA_ET_MATCH_WR(
                                      Device,
                                      i,
                                      0,
                                      0,
                                      CP_p->MAC_DA_ET_Rules[i].EtherType);
                if (rc) return rc;
            }
        } /* for */
    }

    if (EIP163Lib_AnyEnabled(CP_p, EIP163_REG_CP_MAC_DA_ET_RANGE_MASK))
    {
        for (i = 0; i < EIP163_MAC_DA_ET_RANGE_MATCH_RULES_COUNT; i++)
        {
            if (EIP163Lib_AnyEnabled(CP_p, (BIT_16 << i)))
            {
#ifdef EIP163_STRICT_ARGS
                if ((CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_Start_p == NULL) ||
                    (CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_End_p == NULL))
                    return EIP163_ARGUMENT_ERROR;
#endif

                rc = EIP163_CP_MAC_DA_START_LO_WR(
                             Device,
                             i,
                             CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_Start_p[0],
                             CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_Start_p[1],
                             CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_Start_p[2],
                             CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_Start_p[3]);
                if (rc) return rc;

                rc = EIP163_CP_MAC_DA_START_HI_WR(
                             Device,
                             i,
                             CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_Start_p[4],
                             CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_Start_p[5],
                             CP_p->MAC_DA_ET_Range[i].EtherType);
                if (rc) return rc;

                rc = EIP163_CP_MAC_DA_END_LO_WR(
                             Device,
                             i,
                             CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_End_p[0],
                             CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_End_p[1],
                             CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_End_p[2],
                             CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_End_p[3]);
                if (rc) return rc;

                rc = EIP163_CP_MAC_DA_END_HI_WR(
                             Device,
                             i,
                             CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_End_p[4],
                             CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_End_p[5]);
                if (rc) return rc;
            }
        } /* for */
    }

    if (EIP163Lib_AnyEnabled(CP_p, EIP163_REG_CP_MAC_DA_RANGE_MASK))
    {
#ifdef EIP163_STRICT_ARGS
        if ((CP_p->MAC_DA_Range.MAC_DA_Start_p == NULL) ||
            (CP_p->MAC_DA_Range.MAC_DA_End_p == NULL))
            return EIP163_ARGUMENT_ERROR;
#endif

        rc = EIP163_CP_MAC_DA_START_RO_LO_WR(
                            Device,
                            CP_p->MAC_DA_Range.MAC_DA_Start_p[0],
                            CP_p->MAC_DA_Range.MAC_DA_Start_p[1],
                            CP_p->MAC_DA_Range.MAC_DA_Start_p[2],
                            CP_p->MAC_DA_Range.MAC_DA_Start_p[3]);
        if (rc) return rc;

        rc = EIP163_CP_MAC_DA_START_RO_HI_WR(
                            Device,
                            CP_p->MAC_DA_Range.MAC_DA_Start_p[4],
                            CP_p->MAC_DA_Range.MAC_DA_Start_p[5]);
        if (rc) return rc;

        rc = EIP163_CP_MAC_DA_END_RO_LO_WR(
                            Device,
                            CP_p->MAC_DA_Range.MAC_DA_End_p[0],
                            CP_p->MAC_DA_Range.MAC_DA_End_p[1],
                            CP_p->MAC_DA_Range.MAC_DA_End_p[2],
                            CP_p->MAC_DA_Range.MAC_DA_End_p[3]);
        if (rc) return rc;

        rc = EIP163_CP_MAC_DA_END_RO_HI_WR(
                            Device,
                            CP_p->MAC_DA_Range.MAC_DA_End_p[4],
                            CP_p->MAC_DA_Range.MAC_DA_End_p[5]);
        if (rc) return rc;
    }

    if (EIP163Lib_AnyEnabled(CP_p, EIP163_REG_CP_MAC_DA_44BIT_MASK))
    {
#ifdef EIP163_STRICT_ARGS
        if (CP_p->MAC_DA_44Bit_Const_p == NULL)
            return EIP163_ARGUMENT_ERROR;
#endif

        rc = EIP163_CP_MAC_DA_44_BITS_LO_WR(
                            Device,
                            CP_p->MAC_DA_44Bit_Const_p[0],
                            CP_p->MAC_DA_44Bit_Const_p[1],
                            CP_p->MAC_DA_44Bit_Const_p[2],
                            CP_p->MAC_DA_44Bit_Const_p[3]);
        if (rc) return rc;

        rc = EIP163_CP_MAC_DA_44_BITS_HI_WR(
                        Device,
                        CP_p->MAC_DA_44Bit_Const_p[4],
                        CP_p->MAC_DA_44Bit_Const_p[5]);
        if (rc) return rc;
    }

    if (EIP163Lib_AnyEnabled(CP_p, EIP163_REG_CP_MAC_DA_48BIT_MASK))
    {
#ifdef EIP163_STRICT_ARGS
        if (CP_p->MAC_DA_48Bit_Const_p == NULL)
            return EIP163_ARGUMENT_ERROR;
#endif

        rc = EIP163_CP_MAC_DA_48_BITS_LO_WR(
                            Device,
                            CP_p->MAC_DA_48Bit_Const_p[0],
                            CP_p->MAC_DA_48Bit_Const_p[1],
                            CP_p->MAC_DA_48Bit_Const_p[2],
                            CP_p->MAC_DA_48Bit_Const_p[3]);
        if (rc) return rc;

        rc = EIP163_CP_MAC_DA_48_BITS_HI_WR(
                        Device,
                        CP_p->MAC_DA_48Bit_Const_p[4],
                        CP_p->MAC_DA_48Bit_Const_p[5]);
        if (rc) return rc;
    }

    rc = EIP163_CP_MATCH_MODE_WR(Device, ChannelId,
                                 CP_p->CPMatchModeMask,
                                 CP_p->CPMatchSubMask);
    if (rc) return rc;


    rc = EIP163_CP_MATCH_ENABLE_WR(Device, ChannelId, CP_p->CPMatchEnableMask);
    if (rc) return rc;


    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_ControlPacket_Read
 */
EIP163_Error_t
EIP163_ControlPacket_Read(
        const EIP163_IOArea_t * const IOArea_p,
        unsigned int ChannelId,
        EIP163_ControlPacket_t * const CP_p)
{
    unsigned int i;
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    uint8_t dummy[2];
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_POINTER(CP_p);
    EIP163_CHECK_INT_ATMOST(ChannelId, TrueIOArea_p->MaxChCount - 1);

    Device = TrueIOArea_p->Device;

    rc = EIP163_CP_MATCH_MODE_RD(Device, ChannelId,
                                 &CP_p->CPMatchModeMask,
                                 &CP_p->CPMatchSubMask);
    if (rc) return rc;

    rc = EIP163_CP_MATCH_ENABLE_RD(Device, ChannelId, &CP_p->CPMatchEnableMask);
    if (rc) return rc;

    if (EIP163Lib_AnyEnabled(CP_p, EIP163_REG_CP_MAC_DA_ET_MATCH_MASK))
    {
        for (i = 0; i < EIP163_MAC_DA_ET_MATCH_RULES_COUNT; i++)
        {
            if (EIP163Lib_AnyEnabled(CP_p, (BIT_0 << i)))
            {
#ifdef EIP163_STRICT_ARGS
                if (CP_p->MAC_DA_ET_Rules[i].MAC_DA_p == NULL)
                    return EIP163_ARGUMENT_ERROR;
#endif

                rc = EIP163_CP_MAC_DA_MATCH_RD(
                                      Device,
                                      i,
                                      &CP_p->MAC_DA_ET_Rules[i].MAC_DA_p[0],
                                      &CP_p->MAC_DA_ET_Rules[i].MAC_DA_p[1],
                                      &CP_p->MAC_DA_ET_Rules[i].MAC_DA_p[2],
                                      &CP_p->MAC_DA_ET_Rules[i].MAC_DA_p[3]);
                if (rc) return rc;

                rc = EIP163_CP_MAC_DA_ET_MATCH_RD(
                                      Device,
                                      i,
                                      &CP_p->MAC_DA_ET_Rules[i].MAC_DA_p[4],
                                      &CP_p->MAC_DA_ET_Rules[i].MAC_DA_p[5],
                                      &CP_p->MAC_DA_ET_Rules[i].EtherType);
                if (rc) return rc;
            }
            else if (EIP163Lib_AnyEnabled(CP_p, (BIT_8 << i)))
            {
                rc = EIP163_CP_MAC_DA_ET_MATCH_RD(
                                      Device,
                                      i,
                                      &dummy[0],
                                      &dummy[1],
                                      &CP_p->MAC_DA_ET_Rules[i].EtherType);
                if (rc) return rc;
            }
        } /* for */
    }

    if (EIP163Lib_AnyEnabled(CP_p, EIP163_REG_CP_MAC_DA_ET_RANGE_MASK))
    {
        for (i = 0; i < EIP163_MAC_DA_ET_RANGE_MATCH_RULES_COUNT; i++)
        {
            if (EIP163Lib_AnyEnabled(CP_p, (BIT_16 << i)))
            {
#ifdef EIP163_STRICT_ARGS
                if ((CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_Start_p == NULL) ||
                    (CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_End_p == NULL))
                    return EIP163_ARGUMENT_ERROR;
#endif

                rc = EIP163_CP_MAC_DA_START_LO_RD(
                             Device,
                             i,
                             &CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_Start_p[0],
                             &CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_Start_p[1],
                             &CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_Start_p[2],
                             &CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_Start_p[3]);
                if (rc) return rc;

                rc = EIP163_CP_MAC_DA_START_HI_RD(
                             Device,
                             i,
                             &CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_Start_p[4],
                             &CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_Start_p[5],
                             &CP_p->MAC_DA_ET_Range[i].EtherType);
                if (rc) return rc;

                rc = EIP163_CP_MAC_DA_END_LO_RD(
                             Device,
                             i,
                             &CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_End_p[0],
                             &CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_End_p[1],
                             &CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_End_p[2],
                             &CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_End_p[3]);
                if (rc) return rc;

                rc = EIP163_CP_MAC_DA_END_HI_RD(
                             Device,
                             i,
                             &CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_End_p[4],
                             &CP_p->MAC_DA_ET_Range[i].Range.MAC_DA_End_p[5]);
                if (rc) return rc;
            }
        } /* for */
    }

    if (EIP163Lib_AnyEnabled(CP_p, EIP163_REG_CP_MAC_DA_RANGE_MASK))
    {
#ifdef EIP163_STRICT_ARGS
        if ((CP_p->MAC_DA_Range.MAC_DA_Start_p == NULL) ||
            (CP_p->MAC_DA_Range.MAC_DA_End_p == NULL))
            return EIP163_ARGUMENT_ERROR;
#endif

        rc = EIP163_CP_MAC_DA_START_RO_LO_RD(
                            Device,
                            &CP_p->MAC_DA_Range.MAC_DA_Start_p[0],
                            &CP_p->MAC_DA_Range.MAC_DA_Start_p[1],
                            &CP_p->MAC_DA_Range.MAC_DA_Start_p[2],
                            &CP_p->MAC_DA_Range.MAC_DA_Start_p[3]);
        if (rc) return rc;

        rc = EIP163_CP_MAC_DA_START_RO_HI_RD(
                            Device,
                            &CP_p->MAC_DA_Range.MAC_DA_Start_p[4],
                            &CP_p->MAC_DA_Range.MAC_DA_Start_p[5]);
        if (rc) return rc;

        rc = EIP163_CP_MAC_DA_END_RO_LO_RD(
                            Device,
                            &CP_p->MAC_DA_Range.MAC_DA_End_p[0],
                            &CP_p->MAC_DA_Range.MAC_DA_End_p[1],
                            &CP_p->MAC_DA_Range.MAC_DA_End_p[2],
                            &CP_p->MAC_DA_Range.MAC_DA_End_p[3]);
        if (rc) return rc;

        rc = EIP163_CP_MAC_DA_END_RO_HI_RD(
                            Device,
                            &CP_p->MAC_DA_Range.MAC_DA_End_p[4],
                            &CP_p->MAC_DA_Range.MAC_DA_End_p[5]);
        if (rc) return rc;
    }

    if (EIP163Lib_AnyEnabled(CP_p, EIP163_REG_CP_MAC_DA_44BIT_MASK))
    {
#ifdef EIP163_STRICT_ARGS
        if (CP_p->MAC_DA_44Bit_Const_p == NULL)
            return EIP163_ARGUMENT_ERROR;
#endif

        rc = EIP163_CP_MAC_DA_44_BITS_LO_RD(
                        Device,
                        &CP_p->MAC_DA_44Bit_Const_p[0],
                        &CP_p->MAC_DA_44Bit_Const_p[1],
                        &CP_p->MAC_DA_44Bit_Const_p[2],
                        &CP_p->MAC_DA_44Bit_Const_p[3]);
        if (rc) return rc;

        rc = EIP163_CP_MAC_DA_44_BITS_HI_RD(
                        Device,
                        &CP_p->MAC_DA_44Bit_Const_p[4],
                        &CP_p->MAC_DA_44Bit_Const_p[5]);
        if (rc) return rc;
    }

    if (EIP163Lib_AnyEnabled(CP_p, EIP163_REG_CP_MAC_DA_48BIT_MASK))
    {
#ifdef EIP163_STRICT_ARGS
        if (CP_p->MAC_DA_48Bit_Const_p == NULL)
            return EIP163_ARGUMENT_ERROR;
#endif

        rc = EIP163_CP_MAC_DA_48_BITS_LO_RD(
                        Device,
                        &CP_p->MAC_DA_48Bit_Const_p[0],
                        &CP_p->MAC_DA_48Bit_Const_p[1],
                        &CP_p->MAC_DA_48Bit_Const_p[2],
                        &CP_p->MAC_DA_48Bit_Const_p[3]);
        if (rc) return rc;

        rc = EIP163_CP_MAC_DA_48_BITS_HI_RD(
                        Device,
                        &CP_p->MAC_DA_48Bit_Const_p[4],
                        &CP_p->MAC_DA_48Bit_Const_p[5]);
        if (rc) return rc;
    }

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_StatisticsControl_Update
 */
EIP163_Error_t
EIP163_StatisticsControl_Update(
        const EIP163_IOArea_t * const IOArea_p,
        const EIP163_Statistics_Control_t * const StatCtrl_p)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);

    Device = TrueIOArea_p->Device;

    /* Threshold for the frame counters */
    rc = EIP217_COUNT_FRAME_THR_64_WR(Device,
                                 EIP163_REG_TCAM_STAT_CTRL_OFFS,
                                 StatCtrl_p->CountFrameThr.low,
                                 StatCtrl_p->CountFrameThr.hi);
    if (rc) return rc;

    /* Threshold for the per-channel frame counters */
    rc = EIP217_COUNT_FRAME_THR_64_WR(Device,
                                 EIP163_REG_CHAN_STAT_CTRL_OFFS,
                                 StatCtrl_p->ChanCountFrameThr.low,
                                 StatCtrl_p->ChanCountFrameThr.hi);
    if (rc) return rc;

#if defined(EIP163_IPSEC_ENABLE)
    /* Threshold for the per-MTT frame counters */
    rc = EIP217_COUNT_FRAME_THR_64_WR(Device,
                                      EIP163_REG_MTT_STAT_CTRL_OFFS,
                                      StatCtrl_p->MTTCountFrameThr.low,
                                      StatCtrl_p->MTTCountFrameThr.hi);
    if (rc) return rc;
#endif

    /* Reset all statistics counters and threshold summary registers */
    rc = EIP217_COUNT_CONTROL_WR(Device,
                            EIP163_REG_TCAM_STAT_CTRL_OFFS,
                            true,    /* Reset */
                            false,
                            false,
                            false,
                            false);
    if (rc) return rc;

    /* Configure the statistics module to clear-on-read and saturating */
    rc = EIP217_COUNT_CONTROL_WR(Device,
                            EIP163_REG_TCAM_STAT_CTRL_OFFS,
                            false,   /* Do not reset */
                            true,    /* Saturate counters */
                            StatCtrl_p->fAutoStatCntrsReset,
                            false,  /* Do not reset */
                            false);
    if (rc) return rc;

    /* Reset all statistics counters and threshold summary registers */
    rc = EIP217_COUNT_CONTROL_WR(Device,
                            EIP163_REG_CHAN_STAT_CTRL_OFFS,
                            true,    /* Reset */
                            false,
                            false,
                            false,
                            false);
    if (rc) return rc;

    /* Configure the statistics module to clear-on-read and saturating */
    rc = EIP217_COUNT_CONTROL_WR(Device,
                            EIP163_REG_CHAN_STAT_CTRL_OFFS,
                            false,   /* Do not reset */
                            true,    /* Saturate counters */
                            StatCtrl_p->fAutoStatCntrsReset,
                            false,  /* Do not reset */
                            false);
    if (rc) return rc;

#if defined(EIP163_IPSEC_ENABLE)
    /* Reset all statistics counters and threshold summary registers */
    rc = EIP217_COUNT_CONTROL_WR(Device,
                            EIP163_REG_MTT_STAT_CTRL_OFFS,
                            true,    /* Reset */
                            false,
                            false,
                            false,
                            false);
    if (rc) return rc;

    /* Configure the statistics module to clear-on-read and saturating */
    rc = EIP217_COUNT_CONTROL_WR(Device,
                            EIP163_REG_MTT_STAT_CTRL_OFFS,
                            false,   /* Do not reset */
                            true,    /* Saturate counters */
                            StatCtrl_p->fAutoStatCntrsReset,
                            false,  /* Do not reset */
                            false);
    if (rc) return rc;
#endif

    {
        uint16_t TCAMCntrMask, NumTCAMCntrs;
        uint32_t ChanCntrMask, NumChanCntrs;
#if defined(EIP163_IPSEC_ENABLE)
        uint32_t MTTCntrMask, NumMTTCntrs;
#endif

        /* Retrieve number of counters for every statistics module */
        NumTCAMCntrs = sizeof(EIP163_Statistics_TCAM_t) /
                                sizeof(EIP163_UI64_t);
        NumChanCntrs = sizeof(EIP163_Statistics_Channel_t) /
                                sizeof(EIP163_UI64_t);
#if defined(EIP163_IPSEC_ENABLE)
        NumMTTCntrs = sizeof(EIP163_Statistics_MTT_t) /
                                sizeof(EIP163_UI64_t);
#endif

        /* Calculate masks for every statistics module to cover all counters */
        TCAMCntrMask = ((1 << NumTCAMCntrs) - 1);
        ChanCntrMask = ((1 << NumChanCntrs) - 1);
#if defined(EIP163_IPSEC_ENABLE)
        MTTCntrMask  = ((1 << NumMTTCntrs) - 1);
#endif

        /* Enable or disable counters, depending on the value of */
        /* Settings_p->CountIncDisCtrl */
        rc = EIP217_COUNT_INCEN1_WR(Device,
                               EIP163_REG_TCAM_STAT_CTRL_OFFS,
                               TCAMCntrMask *
                               !(StatCtrl_p->CountIncDisCtrl & EIP163_CFYE_TCAM_COUNT_INC_DIS));
        if (rc) return rc;

        rc = EIP217_COUNT_INCEN1_WR(Device,
                               EIP163_REG_CHAN_STAT_CTRL_OFFS,
                               ChanCntrMask *
                               !(StatCtrl_p->CountIncDisCtrl & EIP163_CFYE_CHAN_COUNT_INC_DIS));
        if (rc) return rc;

#if defined(EIP163_IPSEC_ENABLE)
        rc = EIP217_COUNT_INCEN1_WR(Device,
                               EIP163_REG_MTT_STAT_CTRL_OFFS,
                               MTTCntrMask *
                               !(StatCtrl_p->CountIncDisCtrl & EIP163_CFYE_MTT_COUNT_INC_DIS));
        if (rc) return rc;
#endif
    }

    return EIP163Lib_Device_Is_Done(Device, TrueIOArea_p->fExternalTCAM);
}


/*----------------------------------------------------------------------------
 * EIP163_StatisticsControl_Read
 */
EIP163_Error_t
EIP163_StatisticsControl_Read(
        const EIP163_IOArea_t * const IOArea_p,
        EIP163_Statistics_Control_t * const StatCtrl_p)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    bool dummy1, dummy2, dummy3, dummy4;
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);

    Device = TrueIOArea_p->Device;

    /* Threshold for the frame counters */
    rc = EIP217_COUNT_FRAME_THR_64_RD(Device,
                                 EIP163_REG_TCAM_STAT_CTRL_OFFS,
                                 &StatCtrl_p->CountFrameThr.low,
                                 &StatCtrl_p->CountFrameThr.hi);
    if (rc) return rc;

    /* Threshold for the per-channel frame counters */
    rc = EIP217_COUNT_FRAME_THR_64_RD(Device,
                                 EIP163_REG_CHAN_STAT_CTRL_OFFS,
                                 &StatCtrl_p->ChanCountFrameThr.low,
                                 &StatCtrl_p->ChanCountFrameThr.hi);
    if (rc) return rc;

#if defined(EIP163_IPSEC_ENABLE)
    /* Threshold for the per-MTT frame counters */
    rc = EIP217_COUNT_FRAME_THR_64_RD(Device,
                                 EIP163_REG_MTT_STAT_CTRL_OFFS,
                                 &StatCtrl_p->MTTCountFrameThr.low,
                                 &StatCtrl_p->MTTCountFrameThr.hi);
    if (rc) return rc;
#endif

    /* Read the statistics module to clear-on-read */
    rc = EIP217_COUNT_CONTROL_RD(Device,
                            EIP163_REG_TCAM_STAT_CTRL_OFFS,
                            &dummy1,
                            &dummy2,
                            &StatCtrl_p->fAutoStatCntrsReset,
                            &dummy3,  /* Do not reset */
                            &dummy4);
    if (rc) return rc;

    {
        uint32_t Mask;
        StatCtrl_p->CountIncDisCtrl = 0;

        rc = EIP217_COUNT_INCEN1_RD(Device,
                               EIP163_REG_TCAM_STAT_CTRL_OFFS,
                               &Mask);
        if (rc) return rc;

        if (Mask == 0)
        {
            StatCtrl_p->CountIncDisCtrl |= EIP163_CFYE_TCAM_COUNT_INC_DIS;
        }

        rc = EIP217_COUNT_INCEN1_RD(Device,
                               EIP163_REG_CHAN_STAT_CTRL_OFFS,
                               &Mask);
        if (rc) return rc;

        if (Mask == 0)
        {
            StatCtrl_p->CountIncDisCtrl |= EIP163_CFYE_CHAN_COUNT_INC_DIS;
        }
#if defined(EIP163_IPSEC_ENABLE)
        rc = EIP217_COUNT_INCEN1_RD(Device,
                                    EIP163_REG_MTT_STAT_CTRL_OFFS,
                                    &Mask);
        if (rc) return rc;

        if (Mask == 0)
        {
            StatCtrl_p->CountIncDisCtrl |= EIP163_CFYE_MTT_COUNT_INC_DIS;
        }
#endif
    }

    return EIP163Lib_Device_Is_Done(Device, TrueIOArea_p->fExternalTCAM);

}


/*----------------------------------------------------------------------------
 * EIP163_Statistics_TCAM_Get
 */
EIP163_Error_t
EIP163_Statistics_TCAM_Get(
        const EIP163_IOArea_t * const IOArea_p,
        const unsigned int StatIndex,
        EIP163_Statistics_TCAM_t * const Stat_p,
        const bool fClear)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_POINTER(Stat_p);
    EIP163_CHECK_INT_ATMOST(StatIndex + 1, TrueIOArea_p->MaxRulesCount);

    Device = TrueIOArea_p->Device;

    rc = EIP163Lib_Counter_Read(Device,
                           EIP163_REG_TCAM_STAT_COUNT_OFFS(StatIndex),
                           0,
                           &Stat_p->Counter,
                           fClear);
    if (rc) return rc;

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_Statistics_Channel_Get
 */
EIP163_Error_t
EIP163_Statistics_Channel_Get(
        const EIP163_IOArea_t * const IOArea_p,
        const unsigned int StatIndex,
        EIP163_Statistics_Channel_t * const Stat_p,
        const bool fClear)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_POINTER(Stat_p);
    EIP163_CHECK_INT_ATMOST(StatIndex + 1, TrueIOArea_p->MaxChCount);

    Device = TrueIOArea_p->Device;

    rc = EIP163Lib_Counter_Read(Device,
                           EIP163_REG_CHAN_STAT_COUNT_OFFS(StatIndex),
                           EIP163_CHAN_STAT_TCAM_HIT_MULTIPLE,
                           &Stat_p->TCAMHitMultiple,
                           fClear);
    if (rc) return rc;

    rc = EIP163Lib_Counter_Read(Device,
                           EIP163_REG_CHAN_STAT_COUNT_OFFS(StatIndex),
                           EIP163_CHAN_STAT_HDRPARSER_DROPPED_PKTS,
                           &Stat_p->HeaderParserDroppedPkts,
                           fClear);
    if (rc) return rc;

    rc = EIP163Lib_Counter_Read(Device,
                           EIP163_REG_CHAN_STAT_COUNT_OFFS(StatIndex),
                           EIP163_CHAN_STAT_TCAM_MISS,
                           &Stat_p->TCAMMiss,
                           fClear);
    if (rc) return rc;

    rc = EIP163Lib_Counter_Read(Device,
                           EIP163_REG_CHAN_STAT_COUNT_OFFS(StatIndex),
                           EIP163_CHAN_STAT_PKTS_CTRL,
                           &Stat_p->PktsCtrl,
                           fClear);
    if (rc) return rc;

    rc = EIP163Lib_Counter_Read(Device,
                         EIP163_REG_CHAN_STAT_COUNT_OFFS(StatIndex),
                         EIP163_CHAN_STAT_PKTS_DATA,
                         &Stat_p->PktsData,
                         fClear);
    if (rc) return rc;

    rc = EIP163Lib_Counter_Read(Device,
                         EIP163_REG_CHAN_STAT_COUNT_OFFS(StatIndex),
                         EIP163_CHAN_STAT_PKTS_DROP,
                         &Stat_p->PktsDropped,
                         fClear);
    if (rc) return rc;

    rc = EIP163Lib_Counter_Read(Device,
                         EIP163_REG_CHAN_STAT_COUNT_OFFS(StatIndex),
                         EIP163_CHAN_STAT_PKTS_ERR_IN,
                         &Stat_p->PktsErrIn,
                         fClear);
    if (rc) return rc;

#if defined(EIP163_IPSEC_ENABLE)
    rc = EIP163Lib_Counter_Read(Device,
                         EIP163_REG_CHAN_STAT_COUNT_OFFS(StatIndex),
                         EIP163_CHAN_STAT_PKTS_MTT_MISS,
                         &Stat_p->MTTMiss,
                         fClear);
    if (rc) return rc;
#endif

    return EIP163_NO_ERROR;
}


#if defined(EIP163_IPSEC_ENABLE)
/*----------------------------------------------------------------------------
 * EIP163_Statistics_MTT_Get
 */
EIP163_Error_t
EIP163_Statistics_MTT_Get(
        const EIP163_IOArea_t * const IOArea_p,
        const unsigned int StatIndex,
        EIP163_Statistics_MTT_t * const Stat_p,
        const bool fClear)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_POINTER(Stat_p);
    EIP163_CHECK_INT_ATMOST(StatIndex + 1, TrueIOArea_p->MaxMTTCount);

    Device = TrueIOArea_p->Device;

    rc = EIP163Lib_Counter_Read(Device,
                           EIP163_REG_MTT_STAT_COUNT_OFFS(StatIndex),
                           0,
                           &Stat_p->Counter,
                           fClear);
    if (rc) return rc;

    return EIP163_NO_ERROR;
}
#endif


/*----------------------------------------------------------------------------
 * EIP163_Statistics_Summary_TCAM_Read
 */
EIP163_Error_t
EIP163_Statistics_Summary_TCAM_Read(
        const EIP163_IOArea_t * const IOArea_p,
        const unsigned int StartOffset,
        uint32_t * const Summary_p,
        const unsigned int Count)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_POINTER(Summary_p);
    EIP163_CHECK_INT_ATMOST((StartOffset + Count) * sizeof(uint32_t),
                            TrueIOArea_p->MaxRulesCount);

    Device = TrueIOArea_p->Device;

    rc = EIP217_COUNT_SUMMARY_P_RD(Device,
                                   EIP163_REG_TCAM_SUMMARY_P_OFFS,
                                   StartOffset,
                                   Summary_p,
                                   Count,
                                   8);
    if (rc) return rc;

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_Statistics_Summary_TCAM_Write
 */
EIP163_Error_t
EIP163_Statistics_Summary_TCAM_Write(
        const EIP163_IOArea_t * const IOArea_p,
        const unsigned int StartOffset,
        const uint32_t * const Summary_p,
        const unsigned int Count)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_POINTER(Summary_p);
    EIP163_CHECK_INT_ATMOST((StartOffset + Count) * sizeof(uint32_t),
                            TrueIOArea_p->MaxRulesCount);

    Device = TrueIOArea_p->Device;

    rc = EIP217_COUNT_SUMMARY_P_WR(Device,
                                   EIP163_REG_TCAM_SUMMARY_P_OFFS,
                                   StartOffset,
                                   Summary_p,
                                   Count,
                                   8);
    if (rc) return rc;

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_Statistics_Summary_Channel_Read
 */
EIP163_Error_t
EIP163_Statistics_Summary_Channel_Read(
        const EIP163_IOArea_t * const IOArea_p,
        EIP163_Ch_Mask_t * const ChSummary_p)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    uint16_t ChannelCount = TrueIOArea_p->MaxChCount;
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_POINTER(ChSummary_p);

    Device = TrueIOArea_p->Device;

    rc = EIP217_COUNT_SUMMARY_P_RD(Device,
                                   EIP163_REG_CHAN_SUMMARY_P_OFFS,
                                   0,
                                   ChSummary_p->ch_bitmask,
                                   ((ChannelCount + 31) / 32),
                                   1);
    if (rc) return rc;

    MaskUnusedChBits(ChSummary_p, ChannelCount);

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_Statistics_Summary_Channel_Write
 */
EIP163_Error_t
EIP163_Statistics_Summary_Channel_Write(
        const EIP163_IOArea_t * const IOArea_p,
        const EIP163_Ch_Mask_t * const ChSummary_p)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    uint16_t ChannelCount = TrueIOArea_p->MaxChCount;
    EIP163_Ch_Mask_t Ch_Mask;
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_POINTER(ChSummary_p);

    Device = TrueIOArea_p->Device;

    memcpy(&Ch_Mask, ChSummary_p, sizeof(EIP163_Ch_Mask_t));
    MaskUnusedChBits(&Ch_Mask, ChannelCount);

    rc = EIP217_COUNT_SUMMARY_P_WR(Device,
                                   EIP163_REG_CHAN_SUMMARY_P_OFFS,
                                   0,
                                   ChSummary_p->ch_bitmask,
                                   ((ChannelCount + 31) / 32),
                                   1);
    if (rc) return rc;

    return EIP163_NO_ERROR;
}


#if defined(EIP163_IPSEC_ENABLE)
/*----------------------------------------------------------------------------
 * EIP163_Statistics_Summary_MTT_Read
 */
EIP163_Error_t
EIP163_Statistics_Summary_MTT_Read(
        const EIP163_IOArea_t * const IOArea_p,
        uint32_t * const Summary_p)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_POINTER(Summary_p);

    Device = TrueIOArea_p->Device;

    rc = EIP217_COUNT_SUMMARY_P_RD(Device,
                                   EIP163_REG_MTT_SUMMARY_P_OFFS,
                                   0,
                                   Summary_p,
                                   1,
                                   1);
    if (rc) return rc;

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_Statistics_Summary_MTT_Write
 */
EIP163_Error_t
EIP163_Statistics_Summary_MTT_Write(
        const EIP163_IOArea_t * const IOArea_p,
        uint32_t * const Summary_p)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_POINTER(Summary_p);

    Device = TrueIOArea_p->Device;

    rc = EIP217_COUNT_SUMMARY_P_WR(Device,
                                   EIP163_REG_MTT_SUMMARY_P_OFFS,
                                   0,
                                   Summary_p,
                                   1,
                                   1);
    if (rc) return rc;

    return EIP163_NO_ERROR;
}
#endif


/*----------------------------------------------------------------------------
 * EIP163_vPortPolicy_Update
 */
EIP163_Error_t
EIP163_vPortPolicy_Update(
        const EIP163_IOArea_t * const IOArea_p,
        const unsigned int PolicyIndex,
        const EIP163_vPortPolicy_t * const vPortPolicy_p)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_POINTER(vPortPolicy_p);
    EIP163_CHECK_INT_ATMOST(PolicyIndex + 1, TrueIOArea_p->MaxvPortCount);

    Device = TrueIOArea_p->Device;

    rc = EIP163_VPORT_POLICY_WR(Device,
                                PolicyIndex,
                                vPortPolicy_p->SecTagOffset,
#if defined(EIP163_IPSEC_ENABLE)
                                vPortPolicy_p->MPLS_Hdr,
#endif
                                vPortPolicy_p->PktExtension);
    if (rc) return rc;

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_vPortPolicy_Read
 */
EIP163_Error_t
EIP163_vPortPolicy_Read(
        const EIP163_IOArea_t * const IOArea_p,
        const unsigned int PolicyIndex,
        EIP163_vPortPolicy_t * const vPortPolicy_p)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_POINTER(vPortPolicy_p);
    EIP163_CHECK_INT_ATMOST(PolicyIndex + 1, TrueIOArea_p->MaxvPortCount);

    Device = TrueIOArea_p->Device;

    rc = EIP163_VPORT_POLICY_RD(Device,
                                PolicyIndex,
                                &vPortPolicy_p->SecTagOffset,
#if defined(EIP163_IPSEC_ENABLE)
                                &vPortPolicy_p->MPLS_Hdr,
#endif
                                &vPortPolicy_p->PktExtension);
    if (rc) return rc;

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_vPortPolicy_Remove
 */
EIP163_Error_t
EIP163_vPortPolicy_Remove(
        const EIP163_IOArea_t * const IOArea_p,
        const unsigned int PolicyIndex)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_INT_ATMOST(PolicyIndex + 1, TrueIOArea_p->MaxvPortCount);

    Device = TrueIOArea_p->Device;

    rc = EIP163_VPORT_POLICY_DEFAULT_WR(Device, PolicyIndex);
    if (rc) return rc;

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_Rule_Update
 */
EIP163_Error_t
EIP163_Rule_Update(
        const EIP163_IOArea_t * const IOArea_p,
        const unsigned int RuleIndex,
        const EIP163_Rule_t * const Rule_p,
        const EIP163_ChannelMode_t ChannelMode)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_POINTER(Rule_p);
    EIP163_CHECK_INT_ATMOST(RuleIndex + 1, TrueIOArea_p->MaxRulesCount);

    Device = TrueIOArea_p->Device;

    if (TrueIOArea_p->fExternalTCAM)
    {
        bool fWriteBusy,fReadBusy,fDisableBusy,fEnabled;

        rc = EIP163_TCAM_STATUS_RD(Device,
                                   &fWriteBusy,
                                   &fReadBusy,
                                   &fDisableBusy,
                                   &fEnabled);
        if (rc) return rc;

        if (fWriteBusy|fReadBusy)
            return EIP163_BUSY_RETRY_LATER;
    }

    if (EIP163_CHANNEL_MODE_MACSEC == ChannelMode)
    {
        /* Write TCAM policy */
        rc = EIP163_TCAM_POLICY_WR(Device,
                                   RuleIndex,
                                   Rule_p->Policy.vPortId,
                                         (TrueIOArea_p->fHasTCAMPrio ?
                                          Rule_p->Policy.Priority:0),
                                   Rule_p->Policy.fDrop,
                                   Rule_p->Policy.fControlPacket,
                                   TrueIOArea_p->fHasTCAMPrio ?
                                   Rule_p->Policy.fControlPacketSub:false);
        if (rc) return rc;
    }

#if defined(EIP163_IPSEC_ENABLE)
    else if (EIP163_CHANNEL_MODE_IPSEC == ChannelMode)
    {
        /* Write TCAM policy */
        rc = EIP163_IPSEC_TCAM_POLICY_WR(Device,
                                         RuleIndex,
                                         Rule_p->Policy.vPortId,
                                         (TrueIOArea_p->fHasTCAMPrio ?
                                          Rule_p->Policy.Priority:0),
                                         Rule_p->Policy.AN);
        if (rc) return rc;
     }
#endif

    /* Write key-half of the rule entry */
    rc = EIP163_TCAM_CTRL_KEY_WR(Device,
                                 RuleIndex,
                                 Rule_p->Key.NumTags,
                                 Rule_p->Key.PacketType,
                                 Rule_p->Key.ChannelID);

    if (rc) return rc;

    rc = EIP163_TCAM_WR(Device,
                        EIP163_REG_TCAM_KEY(RuleIndex, 1),
                        Rule_p->Data,
                        EIP163_RULE_NON_CTRL_WORD_COUNT,
                        EIP163_TCAM_NON_CTRL_WORD_COUNT);
    if (rc) return rc;

    /* Write mask-half of the rule entry */
    rc = EIP163_TCAM_CTRL_MASK_WR(Device,
                                  RuleIndex,
                                  Rule_p->Mask.NumTags,
                                  Rule_p->Mask.PacketType,
                                  Rule_p->Mask.ChannelID);

    if (rc) return rc;

    rc = EIP163_TCAM_WR(Device,
                        EIP163_REG_TCAM_MASK(RuleIndex, 1),
                        Rule_p->DataMask,
                        EIP163_RULE_NON_CTRL_WORD_COUNT,
                        EIP163_TCAM_NON_CTRL_WORD_COUNT);
    if (rc) return rc;

    if (TrueIOArea_p->fExternalTCAM)
    {
        bool fWriteBusy,fReadBusy,fDisableBusy,fEnabled;

        do {
            rc = EIP163_TCAM_STATUS_RD(Device,
                                       &fWriteBusy,
                                       &fReadBusy,
                                       &fDisableBusy,
                                       &fEnabled);
            if (rc) return rc;
        } while (fWriteBusy);
    }

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_Rule_Remove
 */
EIP163_Error_t
EIP163_Rule_Remove(
        const EIP163_IOArea_t * const IOArea_p,
        const unsigned int RuleIndex)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_INT_ATMOST(RuleIndex + 1, TrueIOArea_p->MaxRulesCount);

    Device = TrueIOArea_p->Device;

    if (!TrueIOArea_p->fExternalTCAM)
    {
        rc = EIP163_TCAM_POLICY_DEFAULT_WR(Device, RuleIndex);

        if (rc) return rc;
    }

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_Rule_Enable
 */
EIP163_Error_t
EIP163_Rule_Enable(
        const EIP163_IOArea_t * const IOArea_p,
        const unsigned int RuleIndex)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_INT_ATMOST(RuleIndex + 1, TrueIOArea_p->MaxRulesCount);

    Device = TrueIOArea_p->Device;

    if (!TrueIOArea_p->fExternalTCAM)
    {
        rc = EIP163_TCAM_ENTRY_SET_WR(Device,
                                     RuleIndex / 32,
                                     BIT_0 << (RuleIndex % 32));
        if (rc) return rc;
    }

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_Rule_Disable
 */
EIP163_Error_t
EIP163_Rule_Disable(
        const EIP163_IOArea_t * const IOArea_p,
        const unsigned int RuleIndex)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_INT_ATMOST(RuleIndex + 1, TrueIOArea_p->MaxRulesCount);

    Device = TrueIOArea_p->Device;

    if (TrueIOArea_p->fExternalTCAM)
    {
        bool fWriteBusy,fReadBusy,fDisableBusy,fEnabled;

        rc = EIP163_TCAM_STATUS_RD(Device,
                                   &fWriteBusy,
                                   &fReadBusy,
                                   &fDisableBusy,
                                   &fEnabled);
        if (rc) return rc;

        if (fDisableBusy)
            return EIP163_BUSY_RETRY_LATER;

        rc = EIP163_TCAM_ENTRY_ENABLE_CTRL_WR(Device,
                                              0,
                                              false,
                                              false,
                                              RuleIndex,
                                              true,
                                              true);
        if (rc) return rc;
    }
    else
    {

        rc = EIP163_TCAM_ENTRY_CLEAR_WR(Device,
                                        RuleIndex / 32,
                                        BIT_0 << (RuleIndex % 32));
        return rc;
    }

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_Rule_EnableDisable
 */
EIP163_Error_t
EIP163_Rule_EnableDisable(
        const EIP163_IOArea_t * const IOArea_p,
        const unsigned int IndexEnable,
        const unsigned int IndexDisable,
        const bool EnableSingle,
        const bool DisableSingle,
        const bool EnableAll,
        const bool DisableAll)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_INT_ATMOST(IndexEnable + 1, TrueIOArea_p->MaxRulesCount);
    EIP163_CHECK_INT_ATMOST(IndexDisable + 1, TrueIOArea_p->MaxRulesCount);

    Device = TrueIOArea_p->Device;

    if (TrueIOArea_p->fExternalTCAM)
    {
        bool fWriteBusy,fReadBusy,fDisableBusy,fEnabled;

        rc = EIP163_TCAM_STATUS_RD(Device,
                                   &fWriteBusy,
                                   &fReadBusy,
                                   &fDisableBusy,
                                   &fEnabled);
        if (rc) return rc;

        if (fDisableBusy)
            return EIP163_BUSY_RETRY_LATER;
    }

    rc = EIP163_TCAM_ENTRY_ENABLE_CTRL_WR(Device,
                                     IndexEnable,
                                     EnableSingle,
                                     EnableAll,
                                     IndexDisable,
                                     DisableSingle,
                                     DisableAll);
    if (rc) return rc;

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_Rule_Read
 */
EIP163_Error_t
EIP163_Rule_Read(
        EIP163_IOArea_t * const IOArea_p,
        const unsigned int RuleIndex,
        EIP163_Rule_t * const Rule_p,
        bool * const fEnabled_p,
        const EIP163_ChannelMode_t ChannelMode)
{
    Device_Handle_t Device;
    volatile EIP163_True_IOArea_t * TrueIOArea_p = IOAREA_INOUT(IOArea_p);
    uint8_t PacketType;
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_POINTER(Rule_p);
    EIP163_CHECK_INT_ATMOST(RuleIndex + 1, TrueIOArea_p->MaxRulesCount);

    Device = TrueIOArea_p->Device;

    if (TrueIOArea_p->fExternalTCAM)
    {
        bool fWriteBusy,fReadBusy,fDisableBusy,fEnabled;
        uint32_t Dummy;

        rc = EIP163_TCAM_STATUS_RD(Device,
                                   &fWriteBusy,
                                   &fReadBusy,
                                   &fDisableBusy,
                                   &fEnabled);
        if (rc) return rc;

        if (fWriteBusy|fReadBusy)
            return EIP163_BUSY_RETRY_LATER;

        if (!TrueIOArea_p->fReadPending)
        {
            rc = EIP163_TCAM_RD(Device,
                                EIP163_REG_TCAM_KEY(RuleIndex, 0),
                                &Dummy,
                                1);
            if (rc) return rc;

            TrueIOArea_p->fReadPending = true;
            return EIP163_BUSY_RETRY_LATER;
        }

        TrueIOArea_p->fReadPending = false;
        *fEnabled_p = fEnabled;
    }

    /* Write key-half of the rule entry */
    rc = EIP163_TCAM_CTRL_KEY_RD(Device,
                                 RuleIndex,
                                 &Rule_p->Key.NumTags,
                                 &PacketType,
                                 &Rule_p->Key.ChannelID);

    if (rc) return rc;

    Rule_p->Key.PacketType = PacketType;
    rc = EIP163_TCAM_RD(Device,
                   EIP163_REG_TCAM_KEY(RuleIndex, 1),
                   Rule_p->Data,
                   EIP163_RULE_NON_CTRL_WORD_COUNT);
    if (rc) return rc;

    /* Write mask-half of the rule entry */
    rc = EIP163_TCAM_CTRL_MASK_RD(Device,
                                  RuleIndex,
                                  &Rule_p->Mask.NumTags,
                                  &PacketType,
                                  &Rule_p->Mask.ChannelID);

    if (rc) return rc;

    Rule_p->Mask.PacketType = PacketType;

    rc = EIP163_TCAM_RD(Device,
                        EIP163_REG_TCAM_MASK(RuleIndex, 1),
                        Rule_p->DataMask,
                        EIP163_RULE_NON_CTRL_WORD_COUNT);
    if (rc) return rc;

    {
        bool Dummy;
        return EIP163_Rule_Policy_Read(IOArea_p,
                                       RuleIndex,
                                       &Rule_p->Policy,
                                       TrueIOArea_p->fExternalTCAM ?
                                           &Dummy:fEnabled_p,
                                       ChannelMode);
    }
}


/*----------------------------------------------------------------------------
 * EIP163_Rule_Policy_Read
 */
EIP163_Error_t
EIP163_Rule_Policy_Read(
        const EIP163_IOArea_t * const IOArea_p,
        const unsigned int RuleIndex,
        EIP163_Rule_Policy_t * const Policy_p,
        bool * const fEnabled_p,
        const EIP163_ChannelMode_t ChannelMode)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_POINTER(Policy_p);
    EIP163_CHECK_POINTER(fEnabled_p);

    EIP163_CHECK_INT_ATMOST(RuleIndex + 1, TrueIOArea_p->MaxRulesCount);

    Device = TrueIOArea_p->Device;

    if (TrueIOArea_p->fExternalTCAM)
    {
        *fEnabled_p = false;
    }
    else
    {
        rc = EIP163_TCAM_ENTRY_ENABLE_RD(Device, RuleIndex, fEnabled_p);
        if (rc) return rc;
    }

    if (EIP163_CHANNEL_MODE_MACSEC == ChannelMode)
    {
        rc = EIP163_TCAM_POLICY_RD(Device,
                                   RuleIndex,
                                   &Policy_p->vPortId,
                                   &Policy_p->Priority,
                                   &Policy_p->fDrop,
                                   &Policy_p->fControlPacket,
                                   &Policy_p->fControlPacketSub);
        if (rc) return rc;
    }
#if defined(EIP163_IPSEC_ENABLE)
    else if (EIP163_CHANNEL_MODE_IPSEC == ChannelMode)
    {
        rc = EIP163_IPSEC_TCAM_POLICY_RD(Device,
                                         RuleIndex,
                                         &Policy_p->vPortId,
                                         &Policy_p->Priority,
                                         &Policy_p->AN);
        if (rc) return rc;
    }
#endif

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_Device_Restore
 */
EIP163_Error_t
EIP163_Device_Restore(
        EIP163_IOArea_t * const IOArea_p,
        const Device_Handle_t Device,
        const EIP163_Device_Mode_t Mode)
{
    EIP163_Capabilities_t Capabilities;
    volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_INOUT(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);

    /* Initialize the IO Area */
    TrueIOArea_p->Device = Device;

    rc = EIP163Lib_HWRevision_Get(Device,
                             &Capabilities.EIP163_Options,
                             &Capabilities.EIP163_Version);
    if (rc) return rc;

    TrueIOArea_p->Mode       = Mode;
    TrueIOArea_p->fLookupSCI = Capabilities.EIP163_Options.fLookupSCI;

    /* Remember the EIP-163 HW configuration, e, i */
    if (Capabilities.EIP163_Options.fEgressOnly)
        TrueIOArea_p->HWConf = EIP163_HW_CONF_E;
    else
        TrueIOArea_p->HWConf = EIP163_HW_CONF_I;

    /* Store the maximum number of channels the device supports */
    TrueIOArea_p->MaxChCount = Capabilities.EIP163_Options.Channel_Count;
#if defined(EIP163_IPSEC_ENABLE)
    /* store the maximum number of MTT entries the devices supports */
    TrueIOArea_p->MaxMTTCount = Capabilities.EIP163_Options.MTT_Count;
#endif

    /* Store the maximum number of SC Channels and vPorts the device supports */
    TrueIOArea_p->MaxRulesCount = Capabilities.EIP163_Options.Rules_Count;
    TrueIOArea_p->MaxvPortCount = Capabilities.EIP163_Options.vPort_Count;
    TrueIOArea_p->fExternalTCAM = Capabilities.EIP163_Options.fExternalTCAM;
#if defined(EIP163_IPSEC_ENABLE)
    TrueIOArea_p->fSpareReg     = Capabilities.EIP163_Options.fSpareReg;
    TrueIOArea_p->fIPSecSupport = Capabilities.EIP163_Options.fIPSecSupport;
#endif
    TrueIOArea_p->fReadPending = false;

    return EIP163_NO_ERROR;
}


#if defined(EIP163_IPSEC_ENABLE)
/*----------------------------------------------------------------------------
 * EIP163_MTT_Update
 */
EIP163_Error_t
EIP163_MTT_Update(
        const EIP163_IOArea_t * const IOArea_p,
        const unsigned int MTTIndex,
        const EIP163_MTT_t * const MTT_p)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    EIP163_Ch_Mask_t Ch_Mask;
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_INT_ATMOST(MTTIndex + 1, TrueIOArea_p->MaxMTTCount);

    Device = TrueIOArea_p->Device;

    memcpy(&Ch_Mask, &MTT_p->Key.ChannelMask, sizeof(EIP163_Ch_Mask_t));
    MaskUnusedChBits(&Ch_Mask, TrueIOArea_p->MaxChCount);

    rc = EIP163_MTT_KEY_WR(Device,
                           MTTIndex,
                           TrueIOArea_p->MaxChCount,
                           &Ch_Mask,
                           MTT_p->Key.fIPv6,
                           MTT_p->Key.TagLabel1,
#if defined(EIP163_IPSEC_ENABLE)
                           MTT_p->Key.TagLabel2,
                           MTT_p->Key.fIPHdrValid,
#endif
                           MTT_p->IPAddr
#if defined(EIP163_IPSEC_ENABLE)
                           , MTT_p->Key.fPacketType
#endif
                           );

    if (rc) return rc;

    memcpy(&Ch_Mask, &MTT_p->Mask.ChannelMask, sizeof(EIP163_Ch_Mask_t));
    MaskUnusedChBits(&Ch_Mask, TrueIOArea_p->MaxChCount);

    rc = EIP163_MTT_MASK_WR(Device,
                           MTTIndex,
                           TrueIOArea_p->MaxChCount,
                           &Ch_Mask,
                           MTT_p->Mask.fIPv6,
                           MTT_p->Mask.TagLabel1,
#if defined(EIP163_IPSEC_ENABLE)
                           MTT_p->Mask.TagLabel2,
                           MTT_p->Mask.fIPHdrValid,
#endif
                           MTT_p->IPAddrMask
#if defined(EIP163_IPSEC_ENABLE)
                           , MTT_p->Mask.fPacketType
#endif
                           );
    return rc;
}


/*----------------------------------------------------------------------------
 * EIP163_MTT_Read
 */
EIP163_Error_t
EIP163_MTT_Read(
        EIP163_IOArea_t * const IOArea_p,
        const unsigned int MTTIndex,
        EIP163_MTT_t * const MTT_p,
        bool * const fEnabled_p)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_INT_ATMOST(MTTIndex + 1, TrueIOArea_p->MaxMTTCount);

    Device = TrueIOArea_p->Device;

    rc = EIP163_MTT_KEY_RD(Device,
                           MTTIndex,
                           TrueIOArea_p->MaxChCount,
                           &MTT_p->Key.ChannelMask,
                           &MTT_p->Key.fIPv6,
                           &MTT_p->Key.TagLabel1,
#if defined(EIP163_IPSEC_ENABLE)
                           &MTT_p->Key.TagLabel2,
                           &MTT_p->Key.fIPHdrValid,
#endif
                           MTT_p->IPAddr
#if defined(EIP163_IPSEC_ENABLE)
                           , &MTT_p->Key.fPacketType
#endif
                           );
    if (rc) return rc;

    MaskUnusedChBits(&MTT_p->Key.ChannelMask, TrueIOArea_p->MaxChCount);

    rc = EIP163_MTT_MASK_RD(Device,
                           MTTIndex,
                           TrueIOArea_p->MaxChCount,
                           &MTT_p->Mask.ChannelMask,
                           &MTT_p->Mask.fIPv6,
                           &MTT_p->Mask.TagLabel1,
#if defined(EIP163_IPSEC_ENABLE)
                           &MTT_p->Mask.TagLabel2,
                           &MTT_p->Mask.fIPHdrValid,
#endif
                           MTT_p->IPAddrMask
#if defined(EIP163_IPSEC_ENABLE)
                           , &MTT_p->Mask.fPacketType
#endif
                           );
    if (rc) return rc;

    MaskUnusedChBits(&MTT_p->Mask.ChannelMask, TrueIOArea_p->MaxChCount);

    rc = EIP163_MTT_ENTRY_ENABLE_RD(Device, MTTIndex, fEnabled_p);

    return rc;
}


/*----------------------------------------------------------------------------
 * EIP163_MTT_Enable
 */
EIP163_Error_t
EIP163_MTT_Enable(
        const EIP163_IOArea_t * const IOArea_p,
        const unsigned int MTTIndex)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_INT_ATMOST(MTTIndex + 1, TrueIOArea_p->MaxMTTCount);

    Device = TrueIOArea_p->Device;

    rc = EIP163_MTT_ENTRY_ENABLE_CTRL_WR(Device,
                                         MTTIndex,
                                         true,
                                         false,
                                         0,
                                         false,
                                         false);
    if (rc) return rc;

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_MTT_Disable
 */
EIP163_Error_t
EIP163_MTT_Disable(
        const EIP163_IOArea_t * const IOArea_p,
        const unsigned int MTTIndex)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_INT_ATMOST(MTTIndex + 1, TrueIOArea_p->MaxMTTCount);

    Device = TrueIOArea_p->Device;

    rc = EIP163_MTT_ENTRY_ENABLE_CTRL_WR(Device,
                                         0,
                                         false,
                                         false,
                                         MTTIndex,
                                         true,
                                         false);
    if (rc) return rc;

    return EIP163_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP163_MTT_EnableDisable
 */
EIP163_Error_t
EIP163_MTT_EnableDisable(
        const EIP163_IOArea_t * const IOArea_p,
        const unsigned int IndexEnable,
        const unsigned int IndexDisable,
        const bool EnableSingle,
        const bool DisableSingle,
        const bool EnableAll,
        const bool DisableAll)
{
    Device_Handle_t Device;
    const volatile EIP163_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP163_CHECK_POINTER(IOArea_p);
    EIP163_CHECK_INT_ATMOST(IndexEnable + 1, TrueIOArea_p->MaxMTTCount);
    EIP163_CHECK_INT_ATMOST(IndexDisable + 1, TrueIOArea_p->MaxMTTCount);

    Device = TrueIOArea_p->Device;

    rc = EIP163_MTT_ENTRY_ENABLE_CTRL_WR(Device,
                                         IndexEnable,
                                         EnableSingle,
                                         EnableAll,
                                         IndexDisable,
                                         DisableSingle,
                                         DisableAll);
    if (rc) return rc;

    return EIP163_NO_ERROR;
}
#endif

/* end of file eip163.c */
