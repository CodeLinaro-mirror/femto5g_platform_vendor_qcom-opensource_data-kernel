/** @file api_driver164_init.h
 *
 * @brief Security-IP-164 MACsec Driver Initialization API.
 *
 * This API specifies the driver entry and exit points.
 *
 * Note: one driver instance can support multiple Security-IP-164 MACsec
 *       hardware acceleration devices.
 */

/*****************************************************************************
* Copyright (c) 2015-2021 by Rambus, Inc. and/or its subsidiaries.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 2 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#ifndef DRIVER164_INIT_H_
#define DRIVER164_INIT_H_

/*----------------------------------------------------------------------------
 * Definitions and macros
 */

/** Device administration structure */
typedef struct
{
    /** Device name */
    char * DeviceName_p;

    /** Device start offset in the device register range in system memory map */
    unsigned int StartByteOffset;

    /** Device end offset in the device register range in system memory map */
    unsigned int LastByteOffset;

    /** Implementation specific device flags */
    char Flags;

} Driver164_Device_t;


/** Data path administration structure */
typedef struct
{
    /**  Device start offset  inside system memory map of first sub-device
         chain.*/
    unsigned int StartByteOffset1;
    /**  Device last offset  inside system memory map of second sub-device
         chain.*/
    unsigned int LastByteOffset1;

    /**  Device start offset  inside system memory map of first sub-device
         chain.*/
    unsigned int StartByteOffset2;
    /**  Device last offset  inside system memory map of second sub-device
         chain.*/
    unsigned int LastByteOffset2;

    /** Implementation specific device flags for first chain */
    char Flags1;

    /** Implementation specific device flags for second chain */
    char Flags2;

} Driver164_DataPath_t;


/**---------------------------------------------------------------------------
 * @fn Driver164_Init(void)
 *
 * Initialize the driver. This function must be called before any other
 * driver API function can be called.
 *
 * @return 0 : success
 * @return -1: failure
 */
int
Driver164_Init(void);


/**---------------------------------------------------------------------------
 * @fn Driver164_Exit(void)
 *
 * Initialize the driver. After this function is called no other driver API
 * function can be called except Driver164_Init().
 */
void
Driver164_Exit(void);


/**---------------------------------------------------------------------------
 * @fn Driver164_Device_Add(
 *     const unsigned int Index,
 *     const Driver164_Device_t * const Device_p)
 *
 * Adds a new device to the driver device list.
 * It can be used as an alternative or in combination with static device list
 * configuration in the driver.
 *
 * @pre This function must be called before any other driver function can
 *      reference this device.
 *
 * @param [in] Index
 *     Device index where the device must be added in the device list
 *
 * @param [in] Device_p
 *     Pointer to memory location where device data is stored, may not be NULL
 *
 * @return 0 : success
 * @return -1: failure
 */
int
Driver164_Device_Add(
        const unsigned int Index,
        const Driver164_Device_t * const Device_p);


/**---------------------------------------------------------------------------
 * @fn Driver164_Device_Remove(
 *     const unsigned int Index)
 *
 * Removes device from the driver device list at the requested index,
 * the device must be previously added either statically or via a call
 * to the Driver164_Device_Add() function.
 *
 * @pre This function must be called when no other driver function can reference
 *      this device.
 *
 * @param [in] Index
 *     Device index where the device must be added in the device list
 *
 * @return 0 : success
 * @return -1: failure
 */
int
Driver164_Device_Remove(
        const unsigned int Index);


/**----------------------------------------------------------------------------
 * @fn Driver164_Device_GetCount(void)
 *
 * This function returns the number of devices present in the device list.
 *
 * @return : device count.
 */
unsigned int
Driver164_Device_GetCount(void);


/**---------------------------------------------------------------------------
 * @fn Driver164_DataPath_Add(
 *       const unsigned int Index,
 *       const Driver164_DataPath_t * const DataPath_p);
 *
 * Adds all devices for a complete data path to the driver device list.
 *
 * This function must be called before any other driver function can reference
 * this data path. It can be used as an alternative or in combination with
 * static device list configuration in the driver.
 *
 * @param [in] Index
 *     Data path index of the data path that must be added in the device list
 *
 * @param [in] DataPath_p
 *     Pointer to memory location where data path properties are stored, may
 *     not be NULL
 *
 * @return 0 : success
 * @return -1: failure
 */
int
Driver164_DataPath_Add(
        const unsigned int Index,
        const Driver164_DataPath_t * const DataPath_p);


/**---------------------------------------------------------------------------
 * @fn Driver164_DataPath_Remove(
 *        const unsigned int Index);
 *
 * Removes all devices of a data path from the driver device list at
 * the requested index, the data path must be previously added either
 * statically or via a call to the Driver164_DataPath_Add() function.
 *
 * This function must be called when no other driver function can reference
 * this device.
 *
 * @param [in] Index
 *     Data path index of the data path that must be removed from the device
 *     list
 *
 * @return 0 : success
 * @return -1: failure
 */
int
Driver164_DataPath_Remove(
        const unsigned int Index);


/**----------------------------------------------------------------------------
 * @fn Driver164_DataPath_GetCount(void)
 *
 * This function returns the number of data paths supported by the Driver.
 *
 * @return: Data path count.
 */
unsigned int
Driver164_DataPath_GetCount(void);


#endif /* DRIVER164_INIT_H_ */


/* end of file api_driver164_init.h */
