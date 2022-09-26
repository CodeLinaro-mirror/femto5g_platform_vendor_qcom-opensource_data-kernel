/** @file  api_warmboot_types.h
 *
 * @brief Warm Boot API, implementation-specific device types.
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

#ifndef API_WARMBOOT_TYPES_H_
#define API_WARMBOOT_TYPESH_

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */


/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/** Type describing the device */
typedef enum
{
    WARMBOOT_DEVICE_TYPE_SECY_E,
    WARMBOOT_DEVICE_TYPE_SECY_I,
    WARMBOOT_DEVICE_TYPE_CFYE_E,
    WARMBOOT_DEVICE_TYPE_CFYE_I,
    WARMBOOT_DEVICE_TYPE_DF,
} WarmBoot_DeviceType_t;


#endif /* API_WARMBOOT_TYPESH_ */


/* end of file api_warmboot_types.h */
