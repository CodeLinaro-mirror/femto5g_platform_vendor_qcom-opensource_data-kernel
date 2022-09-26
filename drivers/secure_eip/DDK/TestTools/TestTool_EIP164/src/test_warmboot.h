/* test_warmboot.h
 *
 * Test Tool for CfyE and SecY API's
 * WarmBoot module interface.
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

#ifndef TEST_MACSEC_WARMBOOT_H
#define TEST_MACSEC_WARMBOOT_H

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Driver Framework Basic Defs API */
#include "basic_defs.h"


/*----------------------------------------------------------------------------
 * test_macsec_warmboot_maxsize_get
 *
 * Test the WarmBoot_MaxSize_Get function.
 *
 * Return: true for success, false for failure.
 */
bool
test_macsec_warmboot_maxsize_get(void);

/*----------------------------------------------------------------------------
 * test_macsec_warmboot_init
 *
 * Initialize the WarmBoot subsystem.
 *
 * Return: true for success, false for failure.
 */
bool
test_macsec_warmboot_init(void);

/*----------------------------------------------------------------------------
 * test_macsec_warmboot_shutdown
 *
 * Simulate a driver shutdown...
 *
 * Return: true for success, false for failure.
 */
bool
test_macsec_warmboot_shutdown(void);


/*----------------------------------------------------------------------------
 * test_macsec_warmboot_restore
 *
 * Restore the driver after a WarmBoot shutdown.
 *
 * Return: true for success, false for failure.
 */
bool
test_macsec_warmboot_restore(void);

/*----------------------------------------------------------------------------
 * test_macsec_warmboot_uninit
 *
 * Uninitialize the WarmBoot subsystem. Free any used resources.
 *
 * Return: true for success, false for failure.
 */
bool
test_macsec_warmboot_uninit(void);


#endif /* TEST_MACSEC_WARMBOOT_H */


/* end of file test_warmboot.h */
