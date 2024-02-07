/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2024 Qualcomm Innovation Center, Inc. All rights reserved.
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
#include <linux/nvmem-consumer.h>

#include "mtip.h"
#include "mtip_device.h"
#include "mtip_platform.h"
#include "mtip_ethtool.h"
#include "mtip_macstats.h"
#include "mtip_debug_eth.h"
#include "mtip_sysfs.h"
#include "mtip_debug_eth_gnl.h"

struct work_struct mtip_debug_eth_work;

struct resource debug_port_dev_resource;

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

const char * const mtip_debug_ethtool_stat_strings[] = {
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

#define MTIP_DEBUG_ETH_ETHTOOL_REG_OFFSET_ARRAY_SIZE 16
int mtip_debug_eth_ethtool_reg_buffer_size;

enum mtip_debug_eth_ethtool_regs_e
{
    MTIP_DEBUG_ETH_ETHTOOL_MAC,
    MTIP_DEBUG_ETH_ETHTOOL_PCS,
    MTIP_DEBUG_ETH_ETHTOOL_MAC_WRAPPER,
    MTIP_DEBUG_ETH_ETHTOOL_MAC_STATS,
    MTIP_DEBUG_ETH_ETHTOOL_RSFEC,
    MTIP_DEBUG_ETH_ETHTOOL_DEBUG_PORT_CSR,
    MTIP_DEBUG_ETH_ETHTOOL_DEBUG_FUSE,
    MTIP_DEBUG_ETH_ETHTOOL_REG_MAX
};

struct mtip_debug_eth_ethtool_reg_offset
{
    u32 start_offset;
    u32 end_offset;
    enum mtip_debug_eth_ethtool_regs_e mtip_debug_eth_ethtool_regs;
};


struct mtip_debug_eth_ethtool_reg_offset mtip_debug_eth_ethtool_reg_offset_val[MTIP_DEBUG_ETH_ETHTOOL_REG_OFFSET_ARRAY_SIZE] =
{   {0,             0x000000A0,     MTIP_DEBUG_ETH_ETHTOOL_MAC},
    {0,             0x000000D4,     MTIP_DEBUG_ETH_ETHTOOL_PCS},
    {0x00000320,    0x0000036C,     MTIP_DEBUG_ETH_ETHTOOL_PCS},
    {0x00000640,    0x0000068C,     MTIP_DEBUG_ETH_ETHTOOL_PCS},
    {0x00020000,    0x00020040,     MTIP_DEBUG_ETH_ETHTOOL_PCS},
    {0x00020100,    0x0002019C,     MTIP_DEBUG_ETH_ETHTOOL_PCS},
    {0,             0x000002E4,     MTIP_DEBUG_ETH_ETHTOOL_MAC_WRAPPER},
    {0,             0x00000004,     MTIP_DEBUG_ETH_ETHTOOL_MAC_STATS},
    {0x0000040,	    0x000000B8,     MTIP_DEBUG_ETH_ETHTOOL_MAC_STATS},
    {0x00000100,    0x000003B4,     MTIP_DEBUG_ETH_ETHTOOL_MAC_STATS},
    {0,             0x0000007c,     MTIP_DEBUG_ETH_ETHTOOL_RSFEC},
    {0x00000100,    0x0000012c,     MTIP_DEBUG_ETH_ETHTOOL_RSFEC},
    {0x00000200,    0x0000023c,     MTIP_DEBUG_ETH_ETHTOOL_RSFEC},
    {0x00000284,    0x00000290,     MTIP_DEBUG_ETH_ETHTOOL_RSFEC},
    {0x000002C0,    0x000002D8,     MTIP_DEBUG_ETH_ETHTOOL_RSFEC},
    {0,             0x00000200,     MTIP_DEBUG_ETH_ETHTOOL_DEBUG_PORT_CSR}
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

void mtip_debug_eth_irq_destroy(struct platform_device *pdev) {

  int debug_irq;
  if (pdev == NULL)
	return;
  debug_irq = platform_get_irq_byname(pdev, "debug-irq");
  if(debug_irq > 0) {
	disable_irq_wake(debug_irq);
	free_irq(debug_irq, NULL);
  }
}

int mtip_debug_eth_probe(struct platform_device *pdev) {
  int debug_ret = 0;
  //u32 fuse_csr_regs[2];
  u32 debug_csr_regs[2];
  void __iomem *addr;
  struct resource dev_resource = {0};
  bool fuse_enabled = true;
  u32 fuse_val;
  int ethernet_trace_disabled = 8;
  u32 *buf;
  size_t len;
  struct nvmem_cell *cell;

  CSMLOGINFO("mtip_debug_eth_probe called for device \"%s\"", pdev->name);
  cell = nvmem_cell_get(&pdev->dev, "debug_port_fuse");
  if (IS_ERR(cell)){
    CSMLOGERR("%s: Unable to get debug_port_fuse from devicetree\n",__func__);
    return -EINVAL;
  }

  buf = (u32 *)nvmem_cell_read(cell, &len);
  CSMLOGDBG("len = %d\n",len);

  if (IS_ERR(buf) || (len != 4)){
    nvmem_cell_put(cell);
    if(!IS_ERR(buf)){
      kfree(buf);
    }
    CSMLOGERR("%s: Unable to read debug_port_fuse value \n",__func__);
    return -EINVAL;
  }

  fuse_val = buf[0];
  CSMLOGDBG("fuse val is %d",fuse_val);
  if (fuse_val & (1 << ethernet_trace_disabled))
  {
    fuse_enabled = false;
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

    kfree(buf);
    nvmem_cell_put(cell);

    // Interrupt init
    mtip_debug_eth_irq_init(pdev);

    mtip_debug_eth_gnl_init();

    debug_port_dev_resource = dev_resource;
  }

  return debug_ret;
}

int mtip_debug_eth_set_ethtool_ops(void)
{
    struct net_device *netdev;

    //Replacing Ethtool ops for debug eth
    CSMLOGERR("Assigning Debug ethtool ops");
    if (platform_driver_priv->mtip_links[MTIP_DEBUG_ETH_LINK_INDEX] != NULL) 
    {
        netdev = platform_driver_priv->mtip_links[MTIP_DEBUG_ETH_LINK_INDEX]->dev;
        netdev->ethtool_ops = mtip_debug_eth_get_ethtool_ops();
    }
    else
    {
        CSMLOGERR("link_index %d is NULL", MTIP_DEBUG_ETH_LINK_INDEX);
    }
    return 0;
}

int mtip_debug_eth_remove(struct platform_device *pdev) {
  mtip_debug_eth_gnl_exit();
  mtip_debug_eth_irq_destroy(pdev);
  del_sysfs();
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

void mtip_debug_eth_unregister_platform_driver(void) {

    platform_driver_unregister(&mtip_debug_eth_driver);
}

void mtip_debug_eth_ethtool_get_dev_regs
(
    struct platform_device* port_pdev,
    void __iomem *dev_base_addr,
    void *buf,
    u32 *wr_ptr,
    struct resource *dev_resource,
    struct mtip_debug_eth_ethtool_reg_offset *reg_offset_array,
    u32 reg_offset_array_idx
)
{
    u32 *rbuf = (u32 *)buf;
    u32 *reg_addr = 0x0;
    u32 reg_offset = 0;

    CSMLOGINFO("mtip_debug_eth_ethtool: mtip_get_dev_regs port base = 0x%x, port end 0x%x port size = 0x%x "
               "Dev wr_ptr: %d addr 0x%x arry_idx %d \n",dev_resource->start, dev_resource->end,
               resource_size(dev_resource), *wr_ptr, dev_base_addr, reg_offset_array_idx);

    for (reg_offset = reg_offset_array[reg_offset_array_idx].start_offset;
         (reg_offset <= reg_offset_array[reg_offset_array_idx].end_offset) &&
         (*wr_ptr < mtip_debug_eth_ethtool_reg_buffer_size);)
    {
        reg_addr = (u32*)(dev_base_addr + reg_offset);
        rbuf[(*wr_ptr)++] = (u32)(dev_resource->start + reg_offset);    // Reg Address
        rbuf[(*wr_ptr)++] = (u32)ioread32(reg_addr);                    // Reg Value
        reg_offset+=4;
    }
}


static void mtip_debug_eth_ethtool_dump_regs(u32 link_index, void *buf)
{
    u32 wr_idx = 0;
    u32 port_type;
    struct mtip_link_device_info* link_device;
    struct resource *dev_resource = NULL;
    u32 mtip_reg_idx = 0;

    struct platform_device* pdev;
    void __iomem *dev_ioaddr = NULL;

    CSMLOGINFO("mtip_debug_eth_ethtool: Entering mtip_debug_eth_ethtool_dump_regs with link_idx %d \n", link_index);

    if (mtip_lookup_port_type_by_link_index(link_index, &port_type) < 0)
    {
        CSMLOGERR("invalid port_type for link_index %d", link_index);
        return;
    }

    link_device = &platform_driver_priv->devices.link_devices[link_index];

    for (mtip_reg_idx = 0; mtip_reg_idx < MTIP_DEBUG_ETH_ETHTOOL_REG_OFFSET_ARRAY_SIZE; mtip_reg_idx++)
    {
        switch (mtip_debug_eth_ethtool_reg_offset_val[mtip_reg_idx].mtip_debug_eth_ethtool_regs)
        {
            case MTIP_DEBUG_ETH_ETHTOOL_MAC:
                dev_ioaddr = link_device->mac_ioaddr;
                pdev = platform_driver_priv->devices.link_devices[link_index].link_pdev;
                dev_resource = platform_get_resource_byname(pdev, IORESOURCE_MEM, "mac");
            break;

            case MTIP_DEBUG_ETH_ETHTOOL_PCS:
                dev_ioaddr = link_device->pcs_ioaddr;
                pdev = platform_driver_priv->devices.link_devices[link_index].link_pdev;
                dev_resource = platform_get_resource_byname(pdev, IORESOURCE_MEM, "pcs");
            break;

            case MTIP_DEBUG_ETH_ETHTOOL_MAC_WRAPPER:
                dev_ioaddr = platform_driver_priv->devices.port_devices[port_type].wrapper_base_addr;
                pdev = platform_driver_priv->devices.port_devices[port_type].port_pdev;
                dev_resource = platform_get_resource_byname(pdev, IORESOURCE_MEM, "mac-wrapper");
            break;

            case MTIP_DEBUG_ETH_ETHTOOL_MAC_STATS:
                dev_ioaddr = platform_driver_priv->devices.port_devices[port_type].macstats_base_addr;
                pdev = platform_driver_priv->devices.port_devices[port_type].port_pdev;
                dev_resource = platform_get_resource_byname(pdev, IORESOURCE_MEM, "macstats");
            break;

            case MTIP_DEBUG_ETH_ETHTOOL_RSFEC:
                dev_ioaddr = platform_driver_priv->devices.port_devices[port_type].rsfec_base_addr;
                pdev = platform_driver_priv->devices.port_devices[port_type].port_pdev;
                dev_resource = platform_get_resource_byname(pdev, IORESOURCE_MEM, "rsfec");
            break;

            case MTIP_DEBUG_ETH_ETHTOOL_DEBUG_PORT_CSR:
                dev_ioaddr = get_debug_base_address();
                pdev = platform_driver_priv->devices.port_devices[port_type].port_pdev;
                dev_resource = &debug_port_dev_resource;
	    break;

            default:
            break;
        }
      if((dev_ioaddr != NULL) && (dev_resource != NULL))
      {
        mtip_debug_eth_ethtool_get_dev_regs(pdev, dev_ioaddr, buf, &wr_idx, dev_resource, mtip_debug_eth_ethtool_reg_offset_val, mtip_reg_idx);
      }
    }
}

static void mtip_debug_eth_ethtool_get_regs(struct net_device *dev, struct ethtool_regs *regs, void *buf)
{
    struct mtip_netdev_priv *priv;
    u32 link_index;

    priv = netdev_priv(dev);
    link_index = priv->link_index;

    CSMLOGINFO("mtip_debug_eth_ethtool: Entering mtip_get_regs with Dev %s link_idx %d \n", dev->name, link_index);

    mtip_debug_eth_ethtool_dump_regs(link_index, buf);
}

static int mtip_debug_eth_ethtool_dump_regs_len()
{
    u32 reg_buf_size = 0;
    u32 mtip_reg_idx = 0;

    for (mtip_reg_idx = 0; mtip_reg_idx < MTIP_DEBUG_ETH_ETHTOOL_REG_OFFSET_ARRAY_SIZE; mtip_reg_idx++)
    {
        // add 1 at the end to inlcude the reg at the current index as well
        reg_buf_size += (mtip_debug_eth_ethtool_reg_offset_val[mtip_reg_idx].end_offset - mtip_debug_eth_ethtool_reg_offset_val[mtip_reg_idx].start_offset)/4 + 1;
    }

    // Multiply by 2 to add addresses of registers in buffer
    mtip_debug_eth_ethtool_reg_buffer_size = reg_buf_size * 2;

    CSMLOGDBG("mtip_debug_eth_ethtool: reg buffer size %d  total buff size %d \n",
               reg_buf_size, mtip_debug_eth_ethtool_reg_buffer_size);

    // return size in bytes
    return (mtip_debug_eth_ethtool_reg_buffer_size * sizeof(u32));
}

static int mtip_debug_eth_ethtool_get_regs_len(struct net_device *dev)
{
    u32 reg_buf_size = 0;

    reg_buf_size = mtip_debug_eth_ethtool_dump_regs_len();

    return reg_buf_size;
}

void mtip_debug_eth_macstats_get_stats(struct net_device *netdev, u64 *data)
{
  struct mtip_netdev_priv* priv;
  u32 link_index;
  int i = 0;
  void __iomem *macstats_base_addr;
  void __iomem *debug_base_address;
  u32 port_type;

  CSMLOGDBG("mtip_debug_eth_macstats_get_stats called \n");

  priv = netdev_priv(netdev);
  link_index = priv->link_index;
  CSMLOGDBG("link_index in mtip_debug_eth_macstats_get_stats: %d\n",link_index);

  if (mtip_lookup_port_type_by_link_index(link_index, &port_type) < 0)
  {
    CSMLOGERR("port_type invalid for link_index %d", link_index);
    return;
  }

  CSMLOGERR("port_type : %d \n",port_type);

  macstats_base_addr = platform_driver_priv->devices.port_devices[port_type].macstats_base_addr;

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
    case ETH_SS_PRIV_FLAGS:
      return MTIP_ETHTOOL_PRIV_FLAGS_LEN;
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
  else if (stringset == ETH_SS_PRIV_FLAGS)
  {
    for (i = 0; i < MTIP_ETHTOOL_PRIV_FLAGS_LEN; i++) {
      strlcpy(data, mtip_ethtool_get_priv_flags_str(i),
              ETH_GSTRING_LEN);
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

bool check_if_valid_speed_for_debug_eth(u32 speed)
{
   if(speed == 10000 || speed == 25000)
      return true;
   else
      return false;
}

bool check_if_valid_port_config_for_debug_eth(enum mtip_port_config_enum port_config)
{
  switch (port_config)
  {
    /*
    case MTIP_PORT_CONFIG_1x100GBASE_R:
    case MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC_LL:
    case MTIP_PORT_CONFIG_1x100GBASE_R2:
    case MTIP_PORT_CONFIG_1x100GBASE_R2_RSFEC:
    case MTIP_PORT_CONFIG_1x50GBASE_R:
    case MTIP_PORT_CONFIG_1x50GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_1x50GBASE_R2:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_RSFEC:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_LUAI:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_LUAI_FEC:
    */
    case MTIP_PORT_CONFIG_1x25GBASE_R:
    case MTIP_PORT_CONFIG_1x25GBASE_R_FEC:
    case MTIP_PORT_CONFIG_1x25GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_1x10GBASE_R:
    case MTIP_PORT_CONFIG_1x10GBASE_R_FEC:
    {
      return true;
    }
    default:
    {
      return false;
    }
  }
  return false;
}

static const struct ethtool_ops mtip_debug_ethtool_ops = {
   .get_drvinfo = mtip_ethtool_getdrvinfo,
   .get_regs = mtip_debug_eth_ethtool_get_regs,
   .get_regs_len = mtip_debug_eth_ethtool_get_regs_len,
   .get_sset_count  = mtip_debug_eth_get_sset_count,
   .get_strings = mtip_debug_eth_get_strings,
   .get_ethtool_stats = mtip_debug_eth_ethtool_get_stats,
   .get_link_ksettings = mtip_ethtool_get_link_ksettings,
   .set_link_ksettings = mtip_ethtool_set_link_ksettings,
   .get_fecparam = mtip_ethtool_get_fecparam,
   .set_fecparam = mtip_ethtool_set_fecparam,
   .set_msglevel = mtip_ethtool_set_msglevel,
   .get_msglevel = mtip_ethtool_get_msglevel,
   .get_priv_flags = mtip_ethtool_get_priv_flags,
   .set_priv_flags = mtip_ethtool_set_priv_flags,
};

const struct ethtool_ops * mtip_debug_eth_get_ethtool_ops()
{
  return &mtip_debug_ethtool_ops;
}

char ** get_mtip_debug_ethtool_stat_strings()
{
    return (char **) mtip_debug_ethtool_stat_strings;
}

