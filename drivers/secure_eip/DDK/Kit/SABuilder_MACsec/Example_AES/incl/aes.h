/* aes.h
*
* Include file for AES definitions
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

#ifndef AES_H
#define AES_H

/*************************** HEADER FILES ***************************/
#include "basic_defs.h"


/*----------------------------------------------------------------------------
* AES_Encrypt
*
* Wrapper function as required by the SA Builder. Encrypts a single
* data block using AES.
*
* pInput
*     Pointer to a 16 byte buffer with the plain data.
*
* pOutput
*     Pointer to a 16 bytes buffer with received the encrypted data.
*
* pKey
*     Pointer to the encryption key.
*
* nKeyLen
*     The length of the encryption key in bytes.
*     This must be a value if 16, 24 or 32.
*
* Return Value:
*     No return value.
*/
void
AES_Encrypt(
    const uint8_t *const pInput,
    uint8_t *const pOutput,
    const uint8_t *const pKey,
    const unsigned int nKeyLen);

#endif   /* AES_H */

/* end of file aes.h */

