/* c_eip66.h
 *
 * EIP-6x Driver Library Default Configuration.
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

#ifndef C_EIP66_H_
#define C_EIP66_H_


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Top-level configuration */
#include "cs_eip66.h"

/* Base offset used for all the EIP-66 registers */
#ifndef EIP66_CONF_BASE
#define EIP66_CONF_BASE                0x00
#endif /* EIP66_CONF_BASE */


#endif /* C_EIP66_H_ */


/* end of file c_eip66.h */
