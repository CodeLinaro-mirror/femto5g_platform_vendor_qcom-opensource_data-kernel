/* eip164_rules.h
 *
 * EIP-164 Driver Library Packet Classification Rules interface
 *
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

#ifndef EIP164_RULES_H_
#define EIP164_RULES_H_

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Driver Framework Device API */
#include "device_types.h"           /* Device_Handle_t */

/* EIP-164 Driver Library Types API */
#include "eip164_types.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

/*----------------------------------------------------------------------------
 * EIP164_Rules_SecTag_Update
 *
 * This function updates the rules for the classification of packets using the
 * SecTAG field for the EIP-164 device identified by IOArea_p parameter.
 *
 * IOArea_p (input)
 *      Pointer to the Device instance I/O area in memory that identifies the
 *      EIP-164 device to be used.
 *
 * ChannelId (input)
 *     The channel number/index to set the SecTAG parsing rules for.
 *
 * SecTag_Rules_p (input)
 *     Pointer to a memory location where the SecTAG parsing and compare rules
 *     for each packet are specified.
 *
 * This function is re-entrant for the same or different Devices.
 *
 * This function can be called concurrently with any other Rules API
 * function for the same or different Device.
 *
 * Return value
 *      EIP164_NO_ERROR : Operation is completed
 *      EIP164_ARGUMENT_ERROR : Passed wrong argument.
 */
EIP164_Error_t
EIP164_Rules_SecTag_Update(
        const EIP164_IOArea_t * const IOArea_p,
        const unsigned int ChannelId,
        const EIP164_Channel_Rule_SecTAG_t * const SecTag_Rules_p);


/*----------------------------------------------------------------------------
 * EIP164_Rules_SecTag_Read
 *
 * This function reads the rules for the classification of packets using the
 * SecTAG field for the EIP-164 device identified by IOArea_p parameter.
 *
 * IOArea_p (input)
 *      Pointer to the Device instance I/O area in memory that identifies the
 *      EIP-164 device to be used.
 *
 * ChannelId (input)
 *     The channel number/index to read the SecTAG parsing rules for.
 *
 * SecTag_Rules_p (input)
 *     Pointer to a memory location where the SecTAG parsing and compare rules
 *     for each packet are stored.
 *
 * This function is re-entrant for the same or different Devices.
 *
 * This function can be called concurrently with any other Rules API
 * function for the same or different Device.
 *
 * Return value
 *      EIP164_NO_ERROR : Operation is completed
 *      EIP164_ARGUMENT_ERROR : Passed wrong argument.
 */
EIP164_Error_t
EIP164_Rules_SecTag_Read(
        const EIP164_IOArea_t * const IOArea_p,
        const unsigned int ChannelId,
        EIP164_Channel_Rule_SecTAG_t * const SecTag_Rules_p);


#endif /* EIP164_RULES_H_ */


/* end of file eip164_rules.h */
