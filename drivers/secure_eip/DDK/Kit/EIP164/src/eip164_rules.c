/* eip164_rules.c
 *
 * EIP-164 Driver Library Packet Classification Rules interface implementation
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

/* EIP-164 Driver Library Classification Rules API */
#include "eip164_rules.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* EIP-164 Driver Library SecY types API */
#include "eip164_types.h"

/* Driver Framework Basic Definitions API */
#include "basic_defs.h"             /* IDENTIFIER_NOT_USED, bool, uint32_t */

/* Driver Framework Device API */
#include "device_types.h"           /* Device_Handle_t */

/* EIP-164 register interface */
#include "eip164_level0.h"

/* EIP-164 Internal interface */
#include "eip164_internal.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * Local variables
 */


/*----------------------------------------------------------------------------
 * EIP164_Rules_SecTag_Update
 */
EIP164_Error_t
EIP164_Rules_SecTag_Update(
        const EIP164_IOArea_t * const IOArea_p,
        const unsigned int ChannelId,
        const EIP164_Channel_Rule_SecTAG_t * const SecTag_Rules_p)
{
    Device_Handle_t Device;
    const volatile EIP164_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP164_CHECK_POINTER(IOArea_p);
    EIP164_CHECK_INT_ATMOST(ChannelId, (TrueIOArea_p->MaxChCount - 1));

    Device = TrueIOArea_p->Device;

    rc = EIP164_SAM_NM_PARAMS_WR(Device,
                                 ChannelId,
                                 SecTag_Rules_p->fCompEType,
                                 SecTag_Rules_p->fCheckV,
                                 SecTag_Rules_p->fCheckKay,
                                 SecTag_Rules_p->fCheckCE,
                                 SecTag_Rules_p->fCheckSC,
                                 SecTag_Rules_p->fCheckSL,
                                 SecTag_Rules_p->fCheckPN,
                                 SecTag_Rules_p->fCheckSLExt,
                                 SecTag_Rules_p->EtherType);
    if (rc) return rc;

    return EIP164_NO_ERROR;
}


/*----------------------------------------------------------------------------
 * EIP164_Rules_SecTag_Read
 */
EIP164_Error_t
EIP164_Rules_SecTag_Read(
        const EIP164_IOArea_t * const IOArea_p,
        const unsigned int ChannelId,
        EIP164_Channel_Rule_SecTAG_t * const SecTag_Rules_p)
{
    Device_Handle_t Device;
    const volatile EIP164_True_IOArea_t * const TrueIOArea_p = IOAREA_IN(IOArea_p);
    int rc = 0;

    EIP164_CHECK_POINTER(IOArea_p);
    EIP164_CHECK_INT_ATMOST(ChannelId, (TrueIOArea_p->MaxChCount - 1));

    Device = TrueIOArea_p->Device;

    rc = EIP164_SAM_NM_PARAMS_RD(Device,
                                 ChannelId,
                                 &SecTag_Rules_p->fCompEType,
                                 &SecTag_Rules_p->fCheckV,
                                 &SecTag_Rules_p->fCheckKay,
                                 &SecTag_Rules_p->fCheckCE,
                                 &SecTag_Rules_p->fCheckSC,
                                 &SecTag_Rules_p->fCheckSL,
                                 &SecTag_Rules_p->fCheckPN,
                                 &SecTag_Rules_p->fCheckSLExt,
                                 &SecTag_Rules_p->EtherType);

    if (rc) return rc;

    return EIP164_NO_ERROR;
}


/* end of file eip164_rules.c */
