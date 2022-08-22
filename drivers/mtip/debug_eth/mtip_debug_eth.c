/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/**
  @file mtip_debug_eth.c
  @brief Debug ETH MAC Driver.

  This file implements the Debug Ethernet MAC driver functionality.
*/

#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/skbuff.h>
#include <linux/types.h>

#include "mtip.h"
#include "mtip_debug_eth.h"
#include "mtip_sysfs.h"

struct work_struct mtip_debug_eth_work;

static const struct of_device_id mtip_debug_eth_match[] = {
    {
        .compatible = "debug_eth_regs",
    },
    {}};

MODULE_DEVICE_TABLE(of, mtip_debug_eth_match);

static struct platform_driver mtip_debug_eth_driver = {
    .probe = mtip_debug_eth_probe,
    .remove = mtip_debug_eth_remove,
    .driver =
        {
            .name = "MTIP__DEBUG_ETH",
            .of_match_table = of_match_ptr(mtip_debug_eth_match),
        },
};

int mtip_debug_eth_start_xmit(struct sk_buff *skb, struct net_device *netdev) {
  pr_err("Clearing extra packets for Debug ETH Link");

  // free the skb
  dev_kfree_skb(skb);

  // drop the packet
  return NETDEV_TX_OK;
}
static irqreturn_t mtip_debug_eth_irq_isr(int irq, void *ctxt) {
  queue_work(system_wq, &mtip_debug_eth_work);
  return IRQ_HANDLED;
}

static int mtip_debug_eth_irq_init(struct platform_device *pdev) {
  int res = 0;
  int debug_irq;

  do {
    if (pdev == NULL) {
      pr_err("debug_irq_int pdev is NULL");
      break;
    }

    INIT_WORK(&mtip_debug_eth_work, mtip_sysfs_isr_work_thread);

    // Change this read later
    debug_irq = platform_get_irq(pdev, 0);

    res = request_irq(debug_irq, mtip_debug_eth_irq_isr, IRQF_TRIGGER_RISING,
                      "debug_irq", NULL);
    if (res) {
      pr_err("IRQ request failed irq=%d res=%d\n", debug_irq, res);
      break;
    }

    res = enable_irq_wake(debug_irq);
    if (res) {
      pr_err("fail to enable IRQ wakeup irq=%d res=%d\n", debug_irq, res);
      break;
    }

    pr_err("debug_irq_init Interrupt Registration Success %d", debug_irq);

  } while (0);

  return res;
}

int mtip_debug_eth_probe(struct platform_device *pdev) {
  int debug_ret = 0;
  u32 fuse_csr_regs[2];
  u32 debug_csr_regs[2];
  void __iomem *addr;
  struct resource dev_resource;
  bool fuse_enabled = true;
  // u32 fuse_val;
  // int ethernet_trace_disabled = 8;

  CSMLOGINFO("mtip_debug_eth_probe called for device \"%s\"", pdev->name);

  // Debug Port Changes
  debug_ret = of_property_read_u32_array(
      pdev->dev.of_node, "qcom,debug-port-fuse", fuse_csr_regs, 2);
  if (!debug_ret) {
    // Fetch the debug port fuse address
    dev_resource.start = fuse_csr_regs[0];
    dev_resource.end = fuse_csr_regs[0] + fuse_csr_regs[1];
    dev_resource.flags = IORESOURCE_MEM;
    dev_resource.parent = dev_resource.child = dev_resource.sibling = NULL;
    addr = devm_ioremap_resource(&pdev->dev, &dev_resource);
    // fuse_val = (u32)ioread32(addr);
    // CSMLOGERR("fuse val is %d",fuse_val);
    // if (fuse_val & (1 << ethernet_trace_disabled))
    // {
    //	  CSMLOGERR("fuse val is %d",fuse_val);
    //	  fuse_enabled = false;
    // }
  }

  if (fuse_enabled) {
    debug_ret = of_property_read_u32_array(
        pdev->dev.of_node, "qcom,debug-port-csr", debug_csr_regs, 2);
    if (!debug_ret) {
      // Fetch the debug port base address
      dev_resource.start = debug_csr_regs[0];
      dev_resource.end = debug_csr_regs[0] + debug_csr_regs[1];
      dev_resource.flags = IORESOURCE_MEM;
      dev_resource.parent = dev_resource.child = dev_resource.sibling = NULL;
      addr = devm_ioremap_resource(&pdev->dev, &dev_resource);
      setup_sysfs(addr, &pdev->dev);
    } else {
      CSMLOGERR("ERROR : debug_csr_regs[0] : %x, "
                "debug_csr_regs[1] = %x, ret: %d\n",
                debug_csr_regs[0], debug_csr_regs[1], debug_ret);
    }

    // Interrupt init
    mtip_debug_eth_irq_init(pdev);
  }

  return debug_ret;
}

int mtip_debug_eth_remove(struct platform_device *pdev) { return 0; }

int mtip_debug_eth_register_platform_driver() {
  int ret_val;

  ret_val = platform_driver_register(&mtip_debug_eth_driver);

  // HANDLE THE ERROR
  if (ret_val < 0) {
    CSMLOGERR("platform registration failed for Debug ETH with error: %d",
              ret_val);
  }

  return ret_val;
}
