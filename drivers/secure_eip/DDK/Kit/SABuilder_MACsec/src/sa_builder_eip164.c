/* sa_builder_eip164.c
 *
 * Device specific functions of the EIP-164 SA builder.
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
#include "sa_builder_macsec.h"
#include "sa_builder_internal.h"  /* Internal SA Builder API */

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */
#include "c_sa_builder_macsec.h"  /* configuration */
#include "basic_defs.h"           /* basuc defubtuibs */
#include "log.h"                  /* Log */


/*----------------------------------------------------------------------------
 * Local variables
 */
#if SAB_MACSEC_SA_WORD_COUNT != 24
#error "SA word count other than 24 not supported"
#endif

/*----------------------------------------------------------------------------
 * SABuilderLib_ParamsSupported
 */
bool
SABuilderLib_ParamsSupported(
        const SABuilder_Params_t * const SAParams_p)
{
    /* The EIP-164 does not support 192-bit AES keys. */
    if (SAParams_p->KeyByteCount == 24)
    {
        LOG_CRIT("SABuilder_BuildSA: AES-192 not supported\n");
        return false;
    }

    /* The EIP-164 does not support SA time stamps. */
    if ((SAParams_p->flags & SAB_MACSEC_FLAG_UPDATE_TIME) != 0)
    {
        LOG_CRIT("SABuilder_BuildSA: Time stamps not supported\n");
        return false;
    }

    return true;
}


/*----------------------------------------------------------------------------
 * SABuilderLib_SetOffsets
 */
void
SABuilderLib_SetOffsets(
        const SABuilder_Params_t * const SAParams_p,
        SABuilder_Offsets_t * const SAOffsets_p)
{
    SAOffsets_p->ReservedBitsMask = 0xFFFFFFFF;

    if (SAParams_p->direction == SAB_DIRECTION_EGRESS)
    {
        if (SAB_OP_MACSEC == SAParams_p->operation ||
            SAB_OP_ENC_AES_CTR == SAParams_p->operation ||
            SAB_OP_ENCAUTH_AES_GCM == SAParams_p->operation)
        {
            SAOffsets_p->CtxSaltOffs = 17;
            SAOffsets_p->IVOffs  = 20;
            SAOffsets_p->MaxOffs = 21;
        }
#if defined(DRIVER_IPSEC)
        else if (SAB_OP_IPSEC == SAParams_p->operation)
        {
            SAOffsets_p->SaltOffs = 17;
            SAOffsets_p->SPIOffs  = 20;
            SAOffsets_p->MaxOffs = 21;
            SAOffsets_p->CtxSaltOffs = 0;
            SAOffsets_p->IVOffs = 0;
        }
#endif
    }
    else if ((SAParams_p->flags & SAB_MACSEC_FLAG_LONGSEQ) != 0)
    {
        SAOffsets_p->CtxSaltOffs = 17;
        SAOffsets_p->IVOffs = 0;
        SAOffsets_p->MaxOffs = 19;

#if defined(DRIVER_IPSEC)
        if (SAB_OP_IPSEC == SAParams_p->operation)
        {
            SAOffsets_p->SaltOffs = 17;
            SAOffsets_p->CtxSaltOffs = 0;
        }
#endif
    }
    else
    {
        SAOffsets_p->CtxSaltOffs = 0;
        SAOffsets_p->MaxOffs = 19;
#if defined(DRIVER_IPSEC)
        SAOffsets_p->SaltOffs = 17;
#endif

        if (SAB_OP_MACSEC == SAParams_p->operation)
        {
            SAOffsets_p->IVOffs = 17;
        }
#if defined(DRIVER_IPSEC)
        else if (SAB_OP_IPSEC == SAParams_p->operation)
        {
            SAOffsets_p->IVOffs = 0;
        }
#endif
    }

    /* For the EIP-164 all fields have a fixed offset. */
    SAOffsets_p->UpdateCtrlOffs = 1;
    SAOffsets_p->KeyOffs = 2;
    SAOffsets_p->HKeyOffs = 10;
    SAOffsets_p->SeqNumOffs = 14;
    SAOffsets_p->MaskOffs = 16;
    SAOffsets_p->MTUOffs = 16;

    if (SAB_OP_MACSEC == SAParams_p->operation)
    {
        /* Setting 0 for the reserved bits and other flags */
        SAOffsets_p->ReservedBitsMask &= ~(BIT_31 | BIT_30 | BIT_25 | BIT_24 |
                                           BIT_23 | BIT_22 | BIT_21 | BIT_20 |
                                           BIT_16 | BIT_14 | BIT_12 | BIT_11 |
                                           BIT_10 | BIT_9  | BIT_8  | BIT_7  |
                                           BIT_6  | BIT_5  | BIT_4);
    }
#if defined(DRIVER_IPSEC)
    else if (SAB_OP_IPSEC == SAParams_p->operation)
    {
        /* Setting 0 for the reserved bits and other flags */
        SAOffsets_p->ReservedBitsMask &= ~(BIT_27 | BIT_26 | BIT_25 | BIT_24 |
                                           BIT_23 | BIT_22 | BIT_21 | BIT_20 |
                                           BIT_9  | BIT_8  | BIT_7  | BIT_6);

        /* Encrypt the GHASH output. Must be set to 1b */
        SAOffsets_p->ReservedBitsMask |= BIT_15 | BIT_13;
    }
#endif
}

/* end of file sa_builder_eip164.c */
