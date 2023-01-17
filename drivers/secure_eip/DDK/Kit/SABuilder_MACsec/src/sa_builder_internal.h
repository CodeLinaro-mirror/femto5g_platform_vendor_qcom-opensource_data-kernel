
/* sa_builder_internal.h
 *
 * Internal API of the MAcsec SA Builder.
 * - layout of the control words.
 * - Headers for shared functions and protocol-specific functions.
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


#ifndef SA_BUILDER_INTERNAL_H_
#define SA_BUILDER_INTERNAL_H_
#include "c_sa_builder_macsec.h"
#include "sa_builder_macsec.h"

/*----------------------------------------------------------------------------
 * Definitions and macros
 */

/* Context control word values for MACsec */
#define SAB_CW0_MACSEC_EG32 0x1000A000
#define SAB_CW0_MACSEC_IG32 0x1000A001
#define SAB_CW0_MACSEC_EG64 0x2000A000
#define SAB_CW0_MACSEC_IG64 0x2000A081


/* Context control word values for IPsec */
#define SAB_CW0_IPSEC_EG32 0x1000A006
#define SAB_CW0_IPSEC_IG32 0xD000A00F
#define SAB_CW0_IPSEC_EG64 0x2000A006
#define SAB_CW0_IPSEC_IG64 0xE000A00F

/* Context control word values for basic encryption/authentication */
#define SAB_CW0_ENCAUTH_AES_GCM  0x82018006
#define SAB_CW0_AUTHDEC_AES_GCM  0x8201800f
#define SAB_CW0_ENC_AES_CTR      0x80010004

/* Context control word values for various AES key lengths. */
#define SAB_CW0_AES128 0x000a0000
#define SAB_CW0_AES192 0x000c0000
#define SAB_CW0_AES256 0x000e0000
#define SAB_CW0_SM4    0x00080000

/* Various options for MACsec SAs */
#define SAB_CW0_UPDATE_SEQ       0x00002000
#define SAB_CW0_ROLLOVER         0x00000400
#define SAB_CW0_KEEP_SECTAG      0x00000200
#define SAB_CW0_KEEP_ICV         0x00000100
#define SAB_CW0_NO_LATE_CHECK    0x00000040
#define SAB_CW0_LATE_HDR_DROP    0x00000020
#define SAB_CW0_LATE_HDR_CHECK   0x00000010
#define SAB_CW0_NO_ICV_CHECK     0x00000080
#define SAB_CW0_KEEP_PAD         0x00000800
#define SAB_CW0_PAD_CHECK        0x00001000
#define SAB_CW0_REPLAY_CHECK     0x40000000
#define SAB_CW0_IG_HDR_INSERT    0x80000000

/* Data structure to represent offsets of various fields.  If an
   offset is zero, the corresponding field is not present. */
typedef struct {
    uint8_t KeyOffs;
    uint8_t HKeyOffs;
    uint8_t SeqNumOffs;
    uint8_t MaskOffs;
    uint8_t CtxSaltOffs;
    uint8_t SaltOffs;
    uint8_t IVOffs;
    uint8_t UpdateCtrlOffs;
    uint8_t MTUOffs;
    uint8_t MaxOffs;
    uint8_t SPIOffs;
    uint32_t ReservedBitsMask;
} SABuilder_Offsets_t;


/*----------------------------------------------------------------------------
 * SABuilderLib_ParamsSupported
 *
 * This is a device-specific function.
 * Check if device supports the supplied parameters. Check only those
 * that are supported on some MACsec devices, but not on others.
 *
 * SAParams_p (input)
 *    SA parameters to be checked.
 *
 * Return:
 *    true if device supports the supplied parameters/
 *    false if device does not support the supplied parameters
 */
bool
SABuilderLib_ParamsSupported(
        const SABuilder_Params_t * const SAParams_p);


/*----------------------------------------------------------------------------
 * SABuilderLib_SetOffsets
 *
 * This is a device-specific function.
 * Compute the offsets of the various fields in the SA record. depending
 * on the specified operation. Fields not supported are returned as zero.
 *
 * SAParams_p (input)
 *    SA parameters specifying the operation.
 * SAOffsets_p (output)
 *    Data structure containing the offsets of the various fields.
 */
void
SABuilderLib_SetOffsets(
        const SABuilder_Params_t * const SAParams_p,
        SABuilder_Offsets_t * const SAOffsets_p);


#endif /* SA_BUILDER_INTERNAL_H_ */


/* end of file sa_builder_internal.h */
