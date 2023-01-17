/* cs_driver_ext.h
 *
 * Top-level Product Configuration Settings specific for FPGA.
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

#ifndef INCLUDE_GUARD_CS_DRIVER_EXT_H
#define INCLUDE_GUARD_CS_DRIVER_EXT_H

/* EIP-164 FPGA board specific parameters */
#define ADAPTER_FPGA_HW_RESET_ENABLE

/* Maximum number of optional devices in device list */
#if defined(ARCH_X86)||defined(ARCH_POWERPC)
#define DRIVER_OPTIONAL_DEVICE_COUNT  2
#else
#define DRIVER_OPTIONAL_DEVICE_COUNT  1
#endif


#endif /* Include Guard */


/* end of file cs_driver_ext.h */
