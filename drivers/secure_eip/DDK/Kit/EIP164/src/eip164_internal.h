/* eip164_internal.h
 *
 * EIP-164 Global Control Driver Library Internal interface
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

#ifndef EIP164_INTERNAL_H_
#define EIP164_INTERNAL_H_

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Default configuration */
#include "c_eip164.h"

/* Driver Framework Device API */
#include "device_types.h"       /* Device_Handle_t */

/* EIP-164 Driver Library Types API */
#include "eip164_types.h"       /* EIP164_* types */


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

typedef enum
{
    EIP164_HW_CONF_E,
    EIP164_HW_CONF_I,
    EIP164_HW_CONF_IE
} EIP164_HW_Conf_t;

/* I/O Area, used internally */
typedef struct
{
    Device_Handle_t                 Device;
    EIP164_Device_Mode_t            Mode;
    EIP164_HW_Conf_t                HWConf;
    unsigned int                    MaxSACount;
    unsigned int                    MaxChCount;
    unsigned int                    MaxSCCount;
    unsigned int                    MaxvPortCount;
    bool                            fExternalRxCAM;
    bool                            fReadPending;
    bool                            fRetireEnabled;
} EIP164_True_IOArea_t;

#define IOAREA_IN(_p)    ((const volatile EIP164_True_IOArea_t * const)_p)
#define IOAREA_INOUT(_p) ((volatile EIP164_True_IOArea_t * const)_p)

#ifdef EIP164_STRICT_ARGS
#define EIP164_CHECK_POINTER(_p) \
    if (NULL == (_p)) \
        return EIP164_ARGUMENT_ERROR;
#define EIP164_CHECK_INT_INRANGE(_i, _min, _max) \
    if ((_i) < (_min) || (_i) > (_max)) \
        return EIP164_ARGUMENT_ERROR;
#define EIP164_CHECK_INT_ATLEAST(_i, _min) \
    if ((_i) < (_min)) \
        return EIP164_ARGUMENT_ERROR;
#define EIP164_CHECK_INT_ATMOST(_i, _max) \
    if ((_i) > (_max)) \
        return EIP164_ARGUMENT_ERROR;
#else
/* EIP164_STRICT_ARGS undefined */
#define EIP164_CHECK_POINTER(_p)
#define EIP164_CHECK_INT_INRANGE(_i, _min, _max)
#define EIP164_CHECK_INT_ATLEAST(_i, _min)
#define EIP164_CHECK_INT_ATMOST(_i, _max)
#endif /*end of EIP164_STRICT_ARGS */

#define TEST_SIZEOF(type, size) \
    extern int size##_must_bigger[1 - 2*((int)(sizeof(type) > size))]

/* validate the size of the fake and real IOArea structures */
TEST_SIZEOF(EIP164_True_IOArea_t, EIP164_IOAREA_REQUIRED_SIZE);


#endif /* EIP164_INTERNAL_H_ */


/* end of file eip164_internal.h */
