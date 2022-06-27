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

int mtip_debug_eth_start_xmit(struct sk_buff *skb, struct net_device *netdev);
int mtip_debug_eth_probe(struct platform_device *pdev);
int mtip_debug_eth_remove(struct platform_device *pdev);
int mtip_debug_eth_register_platform_driver(void);

#endif /* MTIP_DEBUG_ETH_H */
