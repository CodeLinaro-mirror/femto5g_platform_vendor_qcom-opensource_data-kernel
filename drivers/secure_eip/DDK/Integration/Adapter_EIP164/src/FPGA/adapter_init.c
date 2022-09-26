/* adapter_init.c
 *
 * Adapter module responsible for adapter initialization tasks.
 *
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

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

#include "adapter_init.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Top-level Adapter configuration */
#include "c_adapter_eip164.h"

#include "adapter_pciconfig.h"  /* PCICONFIG_* */

/* Logging API */
#include "log.h"            /* LOG_* */

/* Driver Framework Device API */
#include "device_mgmt.h"    /* Device_Initialize, Device_UnInitialize */
#include "device_rw.h"      /* Device_Read32, Device_Write32 */

/* Driver Framework Basic Definitions API */
#include "basic_defs.h"     /* bool, true, false */


/*----------------------------------------------------------------------------
 * Local variables
 */

static bool Adapter_IsInitialized = false;
static Device_Handle_t Adapter_Device_BOARDCTRL;
static Device_Handle_t Adapter_Device_PCIConfigSpace;


/*----------------------------------------------------------------------------
 * Adapter_Init
 *
 * Return Value
 *     true   Success
 *     false  Failure (fatal!)
 */
bool
Adapter_Init(void)
{
    int nIRQ = -1;

    if (Adapter_IsInitialized != false)
    {
        LOG_WARN("Adapter_Init: Already initialized\n");
        return true;
    }

    /* trigger first-time initialization of the adapter */
    if (Device_Initialize(&nIRQ) < 0)
        return false;

    Adapter_Device_PCIConfigSpace = Device_Find("PCI_CONFIG_SPACE");
    if (Adapter_Device_PCIConfigSpace == NULL)
    {
        LOG_CRIT("Adapter_Init: Failed to locate PCI_CONFIG_SPACE\n");
        return false;
    }

    Adapter_Device_BOARDCTRL = Device_Find("BOARD_CTRL");
    if (Adapter_Device_BOARDCTRL == NULL)
    {
        LOG_CRIT("Adapter_Init: Failed to locate BOARD_CTRL\n");
        return false;
    }

    {
        uint32_t Value;
        int VendorID, DeviceID;

        Value = Device_Read32(
                    Adapter_Device_PCIConfigSpace,
                    PCICONFIG_REG_ID);

        VendorID = PCICONFIG_ID_EXTRACT_VENDOR(Value);
        DeviceID = PCICONFIG_ID_EXTRACT_DEVICE(Value);

        IDENTIFIER_NOT_USED(VendorID);
        IDENTIFIER_NOT_USED(DeviceID);

        LOG_INFO(
            "Adapter_Init: "
            "PCI device: "
            "Vendor=0x%X, "
            "Device=0x%X\n",
            VendorID,
            DeviceID);
    }

    /* initialize the PCI device */
    /* command and status register - Writing value 0x146 to this register */
    /* is recommended before accessing EIP-164 FPGA */
    {
        uint32_t Value;

        Value = PCICONFIG_STATCMD_MEMORYACCESS_ENABLE +
                PCICONFIG_STATCMD_BUSMASTER_ENABLE +
                PCICONFIG_STATCMD_PARITYERR_ENABLE +
                PCICONFIG_STATCMD_SYSTEMERR_ENABLE;

        Device_Write32(
                Adapter_Device_PCIConfigSpace,
                PCICONFIG_REG_STATCMD,
                Value);
    }

    /* Setting cache line size */
    /* maintain all other bits (set by BIOS or OS) */
    {
        uint32_t OldValue, Value;

        Value = Device_Read32(
                    Adapter_Device_PCIConfigSpace,
                    PCICONFIG_REG_CONFIG);
        OldValue = Value;

        IDENTIFIER_NOT_USED(OldValue);

        Value = PCICONFIG_CONFIG_UPDATE_CACHELINESIZE(
                    Value,
                    ADAPTER_PCICONFIG_CACHELINESIZE);

#ifdef ADAPTER_PCICONFIG_MASTERLATENCYTIMER
        Value = PCICONFIG_CONFIG_UPDATE_MASTERLATENCYTIMER(
                    Value,
                    ADAPTER_PCICONFIG_MASTERLATENCYTIMER);
#endif

        Device_Write32(
                Adapter_Device_PCIConfigSpace,
                PCICONFIG_REG_CONFIG,
                Value);

        LOG_INFO(
            "Adapter_Init: "
            "Changed PCI_Config[0x0c] "
            "from 0x%08x "
            "to 0x%08x\n",
            OldValue,
            Value);
    }

    /* FPGA board specific functionality */
    {
        /* Enable PLB access on the board */
        Device_Write32(Adapter_Device_BOARDCTRL, 0x8, 0x00200000);

#ifdef ADAPTER_FPGA_HW_RESET_ENABLE
        /* Perform HW Reset for the EIP-164 FPGA board */
        Device_Write32(Adapter_Device_BOARDCTRL, 0x2000, 0);
        Device_Write32(Adapter_Device_BOARDCTRL, 0x2000, 0xFFFFFFFF);
        Device_Write32(Adapter_Device_BOARDCTRL, 0x2000, 0);
#endif /* ADAPTER_FPGA_HW_RESET_ENABLE */
    }

    Adapter_IsInitialized = true;

    return true;    /* success */
}


/*----------------------------------------------------------------------------
 * Adapter_UnInit
 */
void
Adapter_UnInit(void)
{
    if (!Adapter_IsInitialized)
    {
        LOG_WARN("Adapter_UnInit: Adapter is not initialized\n");
        return;
    }

    Adapter_IsInitialized = false;

    Device_UnInitialize();
}


/*----------------------------------------------------------------------------
 * Adapter_Report_Build_Params
 */
void
Adapter_Report_Build_Params(void)
{
#ifdef LOG_INFO_ENABLED
    int dummy = 0;

    /* This function is dependent on config file cs_adapter.h. */
    /* Please update this when Config file for Adapter is changed. */
    Log_FormattedMessage("Adapter build configuration:\n");

#define REPORT_SET(_X) \
    Log_FormattedMessage("\t" #_X "\n")

#define REPORT_STR(_X) \
    Log_FormattedMessage("\t" #_X ": %s\n", _X)

#define REPORT_INT(_X) \
    dummy = _X; Log_FormattedMessage("\t" #_X ": %d\n", _X)

#define REPORT_HEX32(_X) \
    dummy = _X; Log_FormattedMessage("\t" #_X ": 0x%08X\n", _X)

#define REPORT_EQ(_X, _Y) \
    dummy = (_X + _Y); Log_FormattedMessage("\t" #_X " == " #_Y "\n")

#define REPORT_EXPL(_X, _Y) \
    Log_FormattedMessage("\t" #_X _Y "\n")

    /* Adapter EIP-164 */
    LOG_INFO("Adapter EIP-164:\n");
    REPORT_STR(ADAPTER_EIP164_DRIVER_NAME);
    REPORT_STR(ADAPTER_EIP164_LICENSE);

#ifdef ADAPTER_EIP164_DBG
    REPORT_SET(ADAPTER_EIP164_DBG);
#endif

#ifdef ADAPTER_EIP164_STRICT_ARGS
    REPORT_SET(ADAPTER_EIP164_STRICT_ARGS);
#endif

    REPORT_INT(ADAPTER_EIP164_MAX_NOF_INIT_RETRY_COUNT);
    REPORT_INT(ADAPTER_EIP164_INIT_RETRY_TIMEOUT_MS);
    REPORT_INT(ADAPTER_EIP164_MAX_NOF_SYNC_RETRY_COUNT);
    REPORT_INT(ADAPTER_EIP164_SYNC_RETRY_TIMEOUT_MS);

    REPORT_INT(ADAPTER_EIP164_FIXED_LATENCY);
    REPORT_INT(ADAPTER_EIP164_STATIC_BYPASS);
    REPORT_INT(ADAPTER_EIP164_CLEAR_ON_READ);
    REPORT_INT(ADAPTER_EIP164_DEVICE_CLOCK_CONTROL);

    REPORT_INT(ADAPTER_EIP164_MAX_NOF_DEVICES);
    REPORT_INT(ADAPTER_EIP164_MAX_IC_COUNT);

#ifdef ADAPTER_EIP164_INTERRUPTS_ENABLE
    REPORT_EXPL(ADAPTER_EIP164_INTERRUPTS_ENABLE,
                " is SET => Interrupts ENABLED");
    REPORT_HEX32(ADAPTER_EIP164_INTERRUPTS_TRACEFILTER);
#else
    REPORT_EXPL(ADAPTER_EIP164_INTERRUPTS_ENABLE,
                " is NOT set => Interrupts DISABLED");
#endif

#ifdef ADAPTER_EIP164_64BIT_HOST
    REPORT_EXPL(ADAPTER_EIP164_64BIT_HOST,
                " is SET => addresses are 64-bit");
#else
    REPORT_EXPL(ADAPTER_EIP164_64BIT_HOST,
                " is NOT set => addresses are 32-bit");
#endif

#ifdef ADAPTER_EIP164_MODE_EGRESS
    REPORT_SET(ADAPTER_EIP164_MODE_EGRESS);
    /*REPORT_STR(ADAPTER_EIP164_DEVICE_NAME_EGRESS); */
#endif

#ifdef ADAPTER_EIP164_MODE_INGRESS
    REPORT_SET(ADAPTER_EIP164_MODE_INGRESS);
    /*REPORT_STR(ADAPTER_EIP164_DEVICE_NAME_INGRESS); */
#endif

#ifdef ADAPTER_EIP163_DRIVER_NAME
    /* Adapter EIP-163 */
    LOG_INFO("Adapter EIP-163:\n");
#ifdef ADAPTER_EIP163_DBG
    REPORT_SET(ADAPTER_EIP163_DBG);
#endif

#ifdef ADAPTER_EIP163_STRICT_ARGS
    REPORT_SET(ADAPTER_EIP163_STRICT_ARGS);
#endif

#ifdef ADAPTER_EIP163_MAX_NOF_INIT_RETRY_COUNT
    REPORT_INT(ADAPTER_EIP163_MAX_NOF_INIT_RETRY_COUNT);
#endif

#ifdef ADAPTER_EIP163_INIT_RETRY_TIMEOUT_MS
    REPORT_INT(ADAPTER_EIP163_INIT_RETRY_TIMEOUT_MS);
#endif

#ifdef ADAPTER_EIP163_MAX_NOF_SYNC_RETRY_COUNT
    REPORT_INT(ADAPTER_EIP163_MAX_NOF_SYNC_RETRY_COUNT);
#endif

#ifdef ADAPTER_EIP163_SYNC_RETRY_TIMEOUT_MS
    REPORT_INT(ADAPTER_EIP163_SYNC_RETRY_TIMEOUT_MS);
#endif

#ifdef ADAPTER_EIP163_CLOCK_CONTROL
    REPORT_INT(ADAPTER_EIP163_CLOCK_CONTROL);
#endif

#ifdef ADAPTER_EIP163_LOW_LATENCY_BYPASS
    REPORT_INT(ADAPTER_EIP163_LOW_LATENCY_BYPASS);
#endif

#ifdef ADAPTER_EIP163_CLEAR_ON_READ
    REPORT_INT(ADAPTER_EIP163_CLEAR_ON_READ);
#endif

#ifdef ADAPTER_EIP163_IC_DEVICE_OFFSET
    REPORT_INT(ADAPTER_EIP163_IC_DEVICE_OFFSET);
#endif

#ifdef ADAPTER_EIP163_MAX_NOF_DEVICES
    REPORT_INT(ADAPTER_EIP163_MAX_NOF_DEVICES);
#endif

#ifdef ADAPTER_EIP163_MAX_IC_COUNT
    REPORT_INT(ADAPTER_EIP163_MAX_IC_COUNT);
#endif

#ifdef ADAPTER_EIP163_INTERRUPTS_ENABLE
    REPORT_EXPL(ADAPTER_EIP163_INTERRUPTS_ENABLE,
                " is SET => Interrupts ENABLED");
#else
    REPORT_EXPL(ADAPTER_EIP163_INTERRUPTS_ENABLE,
                " is NOT set => Interrupts DISABLED");
#endif

#ifdef ADAPTER_EIP163_INTERRUPTS_TRACEFILTER
    REPORT_HEX32(ADAPTER_EIP163_INTERRUPTS_TRACEFILTER);
#endif

#ifdef ADAPTER_EIP163_MODE_EGRESS
    REPORT_SET(ADAPTER_EIP163_MODE_EGRESS);
    /*REPORT_STR(ADAPTER_EIP163_DEVICE_NAME_EGRESS); */
#endif

#ifdef ADAPTER_EIP163_MODE_INGRESS
    REPORT_SET(ADAPTER_EIP163_MODE_INGRESS);
    /*REPORT_STR(ADAPTER_EIP163_DEVICE_NAME_INGRESS); */
#endif
#endif /* ADAPTER_EIP163_DRIVER_NAME */

    /* Log */
    Log_FormattedMessage("Logging:\n");

#if (LOG_SEVERITY_MAX == LOG_SEVERITY_INFO)
    REPORT_EQ(LOG_SEVERITY_MAX, LOG_SEVERITY_INFO);
#elif (LOG_SEVERITY_MAX == LOG_SEVERITY_WARNING)
    REPORT_EQ(LOG_SEVERITY_MAX, LOG_SEVERITY_WARNING);
#elif (LOG_SEVERITY_MAX == LOG_SEVERITY_CRITICAL)
    REPORT_EQ(LOG_SEVERITY_MAX, LOG_SEVERITY_CRITICAL);
#else
    REPORT_EXPL(LOG_SEVERITY_MAX, " - Unknown (not info/warn/crit)");
#endif

    IDENTIFIER_NOT_USED(dummy);

#endif /* LOG_INFO_ENABLED */
}


/* end of file adapter_init.c */
