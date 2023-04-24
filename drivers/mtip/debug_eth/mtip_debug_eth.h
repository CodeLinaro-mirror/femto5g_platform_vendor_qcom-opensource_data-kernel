/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/**
  @file mtip_debug_eth.h
  @brief Debug ETH MAC Driver Header.

  This file defines the header for Debug Ethernet MAC driver.
*/

#ifndef MTIP_DEBUG_ETH_H
#define MTIP_DEBUG_ETH_H

#include "mtip.h"

#define MTIP_DEBUG_ETH_MACSTATS_ETHERSTATSOCTETS_REG_OFFET            0x00000360
#define MTIP_DEBUG_ETH_MACSTATS_OCTETSRECEIVEDOK_REG_OFFET            0x00000064
#define MTIP_DEBUG_ETH_MACSTATS_VLANRECEIVEDOK_REG_OFFSET             0x00000368
#define MTIP_DEBUG_ETH_MACSTATS_INERRORS_REG_OFFET                    0x0000006C
#define MTIP_DEBUG_ETH_MACSTATS_INUCASTPKTS_REG_OFFET                 0x0000016C
#define MTIP_DEBUG_ETH_MACSTATS_INMCASTPKTS_REG_OFFET                 0x0000026C
#define MTIP_DEBUG_ETH_MACSTATS_INBCASTPKTS_REG_OFFET                 0x0000036C
#define MTIP_DEBUG_ETH_MACSTATS_ETHERSTATSDROPS_REG_OFFET             0x00000070
#define MTIP_DEBUG_ETH_MACSTATS_ETHERSTATSPKTS_REG_OFFET              0x00000170

#define MTIP_DEBUG_ETH_MACSTATS_OCTETSTRANSMITTEDOK_REG_OFFET         0x000001A0
#define MTIP_DEBUG_ETH_MACSTATS_VLANTRANSMITTEDOK_OFFET               0x000000A4
#define MTIP_DEBUG_ETH_MACSTATS_OUTERRORS_REG_OFFET                   0x000001A4
#define MTIP_DEBUG_ETH_MACSTATS_OUTUCASTPKTS_REG_OFFET                0x000002A4
#define MTIP_DEBUG_ETH_MACSTATS_OUTMCASTPKTS_REG_OFFET                0x000003A4
#define MTIP_DEBUG_ETH_MACSTATS_OUTBCASTPKTS_REG_OFFET                0x000000A8

int mtip_debug_eth_start_xmit(struct sk_buff *skb, struct net_device *netdev);
int mtip_debug_eth_probe(struct platform_device *pdev);
int mtip_debug_eth_remove(struct platform_device *pdev);
int mtip_debug_eth_register_platform_driver(void);
void mtip_debug_eth_unregister_platform_driver(void);
const struct ethtool_ops * mtip_debug_eth_get_ethtool_ops(void);

#endif /* MTIP_DEBUG_ETH_H */
