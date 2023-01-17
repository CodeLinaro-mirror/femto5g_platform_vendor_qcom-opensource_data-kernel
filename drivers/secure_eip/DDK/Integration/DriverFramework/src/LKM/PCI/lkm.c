/* lkm.c
 *
 * Linux Kernel Module implementation for PCI device drivers
 *
 */

/*****************************************************************************
* Copyright (c) 2016-2021 by Rambus, Inc. and/or its subsidiaries.
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

/* Linux Kernel Module interface */
#include "lkm.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Default configuration */
#include "c_lkm.h"

/* Driver Framework Basic Definitions API */
#include "basic_defs.h"             /* uint32_t, NULL, inline, bool, */
                                    /* IDENTIFIER_NOT_USED */

/* Driver Framework C Run-Time Library API */
#include "clib.h"                   /* memcmp */

/* Logging API */
#undef LOG_SEVERITY_MAX
#define LOG_SEVERITY_MAX  LKM_LOG_SEVERITY
#include "log.h"                    /* LOG_* */

/* Linux Kernel API */
#include <linux/types.h>            /* phys_addr_t, resource_size_t */
#include <linux/version.h>          /* LINUX_VERSION_CODE, KERNEL_VERSION */
#include <linux/device.h>           /* struct device */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/moduleparam.h>


/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/* LKM PCI implementation administration data */
typedef struct
{
    /* declarations native to Linux kernel */
    struct pci_dev * PCI_Device_p;

    /* virtual address returned by ioremap() */
    uint32_t __iomem * MappedBaseAddr_p;

    /* physical address passed to ioremap() */
    phys_addr_t PhysBaseAddr;

    /* PCI device driver data */
    struct pci_driver PCI_Driver;

    /* PCI aperture identifier (Bar ID) */
    int ResId;

    /* PCI aperture size in bytes */
    resource_size_t ResByteCount;

    /* true - MSI is used, false otherwise */
    bool fUseMSI;

    bool fRetainMap;

    /* Initialization flag, true - initialized, otherwise - false */
    bool fInitialized;

} LKM_Admin_t;


/*----------------------------------------------------------------------------
 * Local variables
 */

static const struct pci_device_id LKM_IDTable[] =
{
    {PCI_DEVICE(LKM_VENDOR_ID, LKM_DEVICE_ID), },
    {0, }
};

MODULE_DEVICE_TABLE(pci, LKM_IDTable);

/* LKM administration data */
static LKM_Admin_t LKM_Admin;


/*----------------------------------------------------------------------------
 * LKM_Probe
 */
static int
LKM_Probe(
        struct pci_dev * PCI_Device_p,
        const struct pci_device_id * id)
{
    int res;
    LKM_Admin_t * p = &LKM_Admin;

    LOG_INFO(LKM_LOG_PREFIX "%s: entered\n", __func__);

    if (PCI_Device_p == NULL)
    {
        LOG_CRIT(LKM_LOG_PREFIX
                 "%s: failed, missing PCI device\n",
                 __func__);
        return -ENODEV;
    }

    /* enable the device */
    /* this also looks up the IRQ */
    res = pci_enable_device(PCI_Device_p);
    if (res)
    {
        LOG_CRIT(LKM_LOG_PREFIX
                 "%s: Failed to enable PCI device %s\n",
                 __func__,
                 pci_name(PCI_Device_p));
        return res;
    }

    /* remember the device reference */
    p->PCI_Device_p = PCI_Device_p;

    if (p->fRetainMap)
    {
        /* now map the chip into kernel memory */
        /* so we can access the EIP static resources */
        p->PhysBaseAddr = pci_resource_start(p->PCI_Device_p, p->ResId);
        p->PhysBaseAddr &= ~0xf; /* Chop off the control bits */

        if (p->ResByteCount == 0)
            p->ResByteCount = pci_resource_len(p->PCI_Device_p, p->ResId);

        /* note: ioremap is uncached by default */
        p->MappedBaseAddr_p = ioremap(p->PhysBaseAddr, p->ResByteCount);
        if (p->MappedBaseAddr_p == NULL)
        {
            LOG_CRIT(LKM_LOG_PREFIX
                     "%s: failed to ioremap PCI device %s, "
                     "bar %d, phys addr 0x%p, size %ul\n",
                     __func__,
                     pci_name(p->PCI_Device_p),
                     p->ResId,
                     (void*)(uintptr_t)p->PhysBaseAddr,
                     (unsigned int)p->ResByteCount);
            return -ENODEV;
        }

        LOG_INFO(LKM_LOG_PREFIX
                 "%s: Mapped PCI device %s addr %p, phys addr 0x%p, "
                 "sizeof(resource_size_t)=%d\n bar=%d, start=0x%x, end=0x%x, "
                 "size=0x%x, flags=0x%x, irq=%d\n",
                 __func__,
                 pci_name(p->PCI_Device_p),
                 p->MappedBaseAddr_p,
                 (void*)p->PhysBaseAddr,
                 (int)sizeof(resource_size_t),
                 p->ResId,
                 (unsigned int)pci_resource_start(p->PCI_Device_p, p->ResId),
                 (unsigned int)pci_resource_end(p->PCI_Device_p, p->ResId),
                 (unsigned int)p->ResByteCount,
                 (unsigned int)pci_resource_flags(p->PCI_Device_p, p->ResId),
                 p->PCI_Device_p->irq);
    }

    IDENTIFIER_NOT_USED(id);

    LOG_INFO(LKM_LOG_PREFIX "%s: left\n", __func__);

    /* return 0 to indicate "we decided to take ownership" */
    return 0;
}


/*----------------------------------------------------------------------------
 * LKM_Remove
 */
static void
LKM_Remove(
        struct pci_dev * PCI_Device_p)
{
    LKM_Admin_t * p = &LKM_Admin;

    LOG_INFO(LKM_LOG_PREFIX "%s: entered\n", __func__);

    if (p->PCI_Device_p != PCI_Device_p)
    {
        LOG_CRIT(LKM_LOG_PREFIX
                 "%s: failed, missing or wrong PCI device\n",
                 __func__);
        return;
    }

    LOG_INFO(LKM_LOG_PREFIX
             "%s: mapped base addr=%p\n", __func__, p->MappedBaseAddr_p);

    if (p->MappedBaseAddr_p && p->fRetainMap)
    {
        iounmap(p->MappedBaseAddr_p);
        p->MappedBaseAddr_p = NULL;
    }

    pci_disable_device(PCI_Device_p);

    LOG_INFO(LKM_LOG_PREFIX "%s: left\n", __func__);
}


/*-----------------------------------------------------------------------------
 * LKM_Init
 */
int
LKM_Init(
        LKM_Init_t * const InitData_p)
{
    int Status;
    LKM_Admin_t * p = &LKM_Admin;

    LOG_INFO(LKM_LOG_PREFIX "%s: entered\n", __func__);

    /* Check input parameters */
    if(InitData_p == NULL)
    {
        LOG_CRIT(LKM_LOG_PREFIX "%s: failed, missing init data\n", __func__);
        return -1;
    }

    if (p->fInitialized)
    {
        LOG_CRIT(LKM_LOG_PREFIX "%s: failed, already initialized\n", __func__);
        return -2;
    }

    /* Fill in PCI device driver data */
    p->fUseMSI                  = InitData_p->fUseMSI;
    p->fRetainMap               = InitData_p->fRetainMap;
    p->ResId                    = InitData_p->ResId;
    p->ResByteCount             = InitData_p->ResByteCount;

    p->PCI_Driver.name          = InitData_p->DriverName_p;
    p->PCI_Driver.id_table      = LKM_IDTable;
    p->PCI_Driver.probe         = LKM_Probe;
    p->PCI_Driver.remove        = LKM_Remove;

    p->PCI_Driver.driver.name   = InitData_p->DriverName_p;
    p->PCI_Driver.driver.owner  = THIS_MODULE;
    p->PCI_Driver.driver.pm     = InitData_p->PM_p;

    Status = pci_register_driver(&p->PCI_Driver);
    if (Status < 0)
    {
        LOG_CRIT(LKM_LOG_PREFIX
                 "%s: failed to register the PCI device driver\n",
                 __func__);
        return -3;
    }

    if (p->PCI_Device_p == NULL)
    {
        LOG_CRIT(LKM_LOG_PREFIX "%s: failed, no device detected\n", __func__);
        pci_unregister_driver(&p->PCI_Driver);
        return -4;
    }

    /* if provided, CustomInitData_p points to an "int" */
    /* we return the "irq" number via this output parameter */
    if (InitData_p->CustomInitData_p)
    {
        int * Data_p = (int *)InitData_p->CustomInitData_p;

        if (p->fUseMSI)
        {
#if LINUX_VERSION_CODE < KERNEL_VERSION(4,10,0)
            pci_enable_msi(p->PCI_Device_p);
            *Data_p = p->PCI_Device_p->irq;
#else
            int IrqCount, IrqIdx;
            IrqCount = pci_alloc_irq_vectors(p->PCI_Device_p,
                                             1,
                                             4,
                                             PCI_IRQ_ALL_TYPES);
            if (IrqCount <= LKM_PLATFORM_IRQ_IDX)
                IrqIdx = 0;
            else
                IrqIdx = LKM_PLATFORM_IRQ_IDX;
            LOG_CRIT("LKM: PCI number of IRQs = %d, selected irq=%d\n",
                     IrqCount, IrqIdx);
            *Data_p = pci_irq_vector(p->PCI_Device_p, IrqIdx);
#endif
        }
        else
        {
            *Data_p = p->PCI_Device_p->irq;
        }
    }

    pci_set_master(p->PCI_Device_p);

    p->fInitialized = true;

    LOG_INFO(LKM_LOG_PREFIX "%s: left\n", __func__);

    return 0; /* success */
}


/*-----------------------------------------------------------------------------
 * LKM_Uninit
 */
void
LKM_Uninit(void)
{
    LKM_Admin_t * p = &LKM_Admin;

    LOG_INFO(LKM_LOG_PREFIX "%s: entered\n", __func__);

    if (!p->fInitialized)
    {
        LOG_CRIT(LKM_LOG_PREFIX "%s: failed, not initialized yet\n", __func__);
        return;
    }

    LOG_INFO(LKM_LOG_PREFIX "%s: calling pci_unregister_driver\n", __func__);

    pci_unregister_driver(&p->PCI_Driver);

    if (p->PCI_Device_p)
    {
        if (p->fUseMSI)
        {
#if LINUX_VERSION_CODE < KERNEL_VERSION(4,10,0)
            pci_disable_msi(p->PCI_Device_p);
#else
            pci_free_irq_vectors(p->PCI_Device_p);
#endif
        }
        /* side-effect of pci_disable_device is clearing of the Master bit */
        /* if the device tries DMA, it can hang */
        /* to prevent this, re-enable the Master capability of the device */
        pci_set_master(p->PCI_Device_p);
    }

    ZEROINIT(LKM_Admin); /*p->fInitialized = false; */

    LOG_INFO(LKM_LOG_PREFIX "%s: left\n", __func__);
}


/*-----------------------------------------------------------------------------
 * LKM_DeviceGeneric_Get
 */
void *
LKM_DeviceGeneric_Get(void)
{
    LKM_Admin_t * p = &LKM_Admin;

    return &p->PCI_Device_p->dev;
}


/*-----------------------------------------------------------------------------
 * LKM_DeviceSpecific_Get
 */
void *
LKM_DeviceSpecific_Get(void)
{
    LKM_Admin_t * p = &LKM_Admin;

    return p->PCI_Device_p;
}


/*-----------------------------------------------------------------------------
 * LKM_PhysBaseAddr_Get
 */
void *
LKM_PhysBaseAddr_Get(void)
{
    LKM_Admin_t * p = &LKM_Admin;

    return (void*)(uintptr_t)p->PhysBaseAddr;
}


/*-----------------------------------------------------------------------------
 * LKM_MappedBaseAddr_Get
 */
void __iomem *
LKM_MappedBaseAddr_Get(void)
{
    LKM_Admin_t * p = &LKM_Admin;

    return p->MappedBaseAddr_p;
}


/* end of file lkm.c */
