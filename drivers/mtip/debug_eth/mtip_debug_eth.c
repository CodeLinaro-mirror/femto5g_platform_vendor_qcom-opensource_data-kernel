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
#include "mtip_device.h"
#include "mtip_platform.h"
#include "mtip_ethtool.h"
#include "mtip_macstats.h"
#include "mtip_debug_eth.h"
#include "mtip_sysfs.h"
#include "mtip_debug_eth_gnl.h"

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

static const char * const mtip_debug_ethtool_stat_strings[] = {
    "EtherStatsOctets",
    "OctetsReceivedOK",
    "VLANReceivedOK",
    "InErrors",
    "InUCastPkts",
    "InMCastPkts",
    "InBCastPkts",
    "EtherStatsDrops",
    "EtherStatsPkts",
    "OctetsTransmittedOK",
    "VLANTransmittedOK",
    "OutErrors",
    "OutUCastPkts",
    "OutMCastPkts",
    "OutBCastPkts",
    "FIFO_0_TX_Count",
    "FIFO_1_TX_Count",
    "FIFO_2_TX_Count",
    "FIFO_3_TX_Count",
    "FIFO_4_TX_Count",
    "FIFO_5_TX_Count",
    "FIFO_6_TX_Count",
    "FIFO_7_TX_Count",
};

#define MTIP_DEBUG_ETHTOOL_STATS_LEN ARRAY_SIZE(mtip_debug_ethtool_stat_strings)

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

    debug_irq = platform_get_irq_byname(pdev, "debug-irq");

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
  u32 fuse_val;
  int ethernet_trace_disabled = 8;

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
    fuse_val = (u32)ioread32(addr);
    CSMLOGERR("fuse val is %d",fuse_val);
    if (fuse_val & (1 << ethernet_trace_disabled))
    {
	    fuse_enabled = false;
     }
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

    mtip_debug_eth_gnl_init();
  }

  return debug_ret;
}

int mtip_debug_eth_remove(struct platform_device *pdev) {
  mtip_debug_eth_gnl_exit();
  return 0; 
}

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

void mtip_debug_eth_macstats_get_stats(struct net_device *netdev, u64 *data)
{
  struct mtip_netdev_priv* priv;
  u32 link_index;
  int i = 0;
  void __iomem *macstats_base_addr;
  void __iomem *debug_base_address;
  u32 port_device_index;
  u32 link_device_index;
  u32 port_type;

  CSMLOGDBG("mtip_debug_eth_macstats_get_stats called \n");

  priv = netdev_priv(netdev);
  link_index = priv->link_index;
  CSMLOGDBG("link_index in mtip_debug_eth_macstats_get_stats: %d\n",link_index);

  mtip_lookup_device_by_link_index(link_index,
                                   &port_device_index, &link_device_index);
  port_type =
        platform_driver_priv->devices.port_devices[port_device_index].port_type;
  CSMLOGERR("port_type : %d \n",port_type);

  macstats_base_addr = platform_driver_priv->devices.port_devices[port_device_index].macstats_base_addr;

  // the Rx stats
  data[i] = mtip_macstats_read_stat(macstats_base_addr,
                           MTIP_DEBUG_ETH_MACSTATS_ETHERSTATSOCTETS_REG_OFFET);
  data[++i] = mtip_macstats_read_stat(macstats_base_addr,
                            MTIP_DEBUG_ETH_MACSTATS_OCTETSRECEIVEDOK_REG_OFFET);
  data[++i] = mtip_macstats_read_stat(macstats_base_addr,
                             MTIP_DEBUG_ETH_MACSTATS_VLANRECEIVEDOK_REG_OFFSET);
  data[++i] = mtip_macstats_read_stat(macstats_base_addr,
                                    MTIP_DEBUG_ETH_MACSTATS_INERRORS_REG_OFFET);
  data[++i] = mtip_macstats_read_stat(macstats_base_addr,
                                 MTIP_DEBUG_ETH_MACSTATS_INUCASTPKTS_REG_OFFET);
  data[++i] = mtip_macstats_read_stat(macstats_base_addr,
                                 MTIP_DEBUG_ETH_MACSTATS_INMCASTPKTS_REG_OFFET);
  data[++i] = mtip_macstats_read_stat(macstats_base_addr,
                                 MTIP_DEBUG_ETH_MACSTATS_INBCASTPKTS_REG_OFFET);
  data[++i] = mtip_macstats_read_stat(macstats_base_addr,
                             MTIP_DEBUG_ETH_MACSTATS_ETHERSTATSDROPS_REG_OFFET);
  data[++i] = mtip_macstats_read_stat(macstats_base_addr,
                              MTIP_DEBUG_ETH_MACSTATS_ETHERSTATSPKTS_REG_OFFET);

  // the Tx stats
  data[++i] = mtip_macstats_read_stat(macstats_base_addr,
                         MTIP_DEBUG_ETH_MACSTATS_OCTETSTRANSMITTEDOK_REG_OFFET);
  data[++i] = mtip_macstats_read_stat(macstats_base_addr,
                               MTIP_DEBUG_ETH_MACSTATS_VLANTRANSMITTEDOK_OFFET);
  data[++i] = mtip_macstats_read_stat(macstats_base_addr,
                                   MTIP_DEBUG_ETH_MACSTATS_OUTERRORS_REG_OFFET);
  data[++i] = mtip_macstats_read_stat(macstats_base_addr,
                                MTIP_DEBUG_ETH_MACSTATS_OUTUCASTPKTS_REG_OFFET);
  data[++i] = mtip_macstats_read_stat(macstats_base_addr,
                                MTIP_DEBUG_ETH_MACSTATS_OUTMCASTPKTS_REG_OFFET);
  data[++i] = mtip_macstats_read_stat(macstats_base_addr,
                                MTIP_DEBUG_ETH_MACSTATS_OUTBCASTPKTS_REG_OFFET);

  debug_base_address = get_debug_base_address();

  // Debug Eth specific
  data[++i] = (u64)ioread32(debug_base_address + STREAM_PKT_CNT_0);
  data[++i] = (u64)ioread32(debug_base_address + STREAM_PKT_CNT_1);
  data[++i] = (u64)ioread32(debug_base_address + STREAM_PKT_CNT_2);
  data[++i] = (u64)ioread32(debug_base_address + STREAM_PKT_CNT_3);
  data[++i] = (u64)ioread32(debug_base_address + STREAM_PKT_CNT_4);
  data[++i] = (u64)ioread32(debug_base_address + PACKET_FIFO1_PKT_CNT);
  data[++i] = (u64)ioread32(debug_base_address + PACKET_FIFO2_PKT_CNT);
  data[++i] = (u64)ioread32(debug_base_address + PACKET_FIFO3_PKT_CNT);

  return;
}

static int mtip_debug_eth_get_sset_count(struct net_device *netdev, int sset)
{
  CSMLOGDBG("debug ethtool: get_sset_count %d, %d\n", sset,
            MTIP_DEBUG_ETHTOOL_STATS_LEN);

  switch (sset) {
    case ETH_SS_STATS:
    return MTIP_DEBUG_ETHTOOL_STATS_LEN;
  default:
    return -EOPNOTSUPP;
  }
}

static void mtip_debug_eth_get_strings(struct net_device *netdev, u32 stringset, u8 *data)
{
  int i;
  CSMLOGDBG("debug ethtool: get_strings stringset %d, %d\n", stringset,
            MTIP_DEBUG_ETHTOOL_STATS_LEN);

  if (stringset == ETH_SS_STATS)
  {
    for (i = 0; i < MTIP_DEBUG_ETHTOOL_STATS_LEN; i++) {
      strlcpy(data, mtip_debug_ethtool_stat_strings[i], ETH_GSTRING_LEN);
      data += ETH_GSTRING_LEN;
    }
  }

  return;
}

static void mtip_debug_eth_ethtool_get_stats(struct net_device *netdev,
                                        struct ethtool_stats *stats, u64 *data)
{
  CSMLOGDBG("debug ethtool: get_stats\n");

  memset(data, 0, MTIP_DEBUG_ETHTOOL_STATS_LEN*sizeof(u64));

  // read the stats from the HW
  mtip_debug_eth_macstats_get_stats(netdev, data);

  return;
}

static const struct ethtool_ops mtip_debug_ethtool_ops = {
   .begin = mtip_check_if_running,
   .get_drvinfo = mtip_getdrvinfo,
   .get_sset_count  = mtip_debug_eth_get_sset_count,
   .get_strings = mtip_debug_eth_get_strings,
   .get_ethtool_stats = mtip_debug_eth_ethtool_get_stats,
   .get_link_ksettings = mtip_get_link_ksettings,
};

const struct ethtool_ops * mtip_debug_eth_get_ethtool_ops()
{
  return &mtip_debug_ethtool_ops;
}

