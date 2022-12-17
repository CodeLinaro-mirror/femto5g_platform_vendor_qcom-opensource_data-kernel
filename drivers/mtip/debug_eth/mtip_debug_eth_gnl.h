/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/**
  @brief Interface header file between Debug ETH and DIAG Framework.

  This file defines interface between DIAG user space library and
  Debug Ethernet.
*/

#ifndef MTIP_DEBUG_ETH_GNL_H
#define MTIP_DEBUG_ETH_GNL_H

#include <net/genetlink.h>
#include "mtip_debug_eth_gnl_uapi.h"

// Netlink APIs
int mtip_debug_eth_gnl_set_common_params(struct sk_buff *sender_skb,
                                         struct genl_info *info);
int mtip_debug_eth_gnl_set_addr_range(struct sk_buff *sender_skb,
                                      struct genl_info *info);
int mtip_debug_eth_gnl_set_port(struct sk_buff *sender_skb,
                                struct genl_info *info);
int mtip_debug_eth_gnl_set_flush(struct sk_buff *sender_skb,
                                 struct genl_info *info);
int mtip_debug_eth_gnl_set_threshold(struct sk_buff *sender_skb,
                                     struct genl_info *info);
int mtip_debug_eth_gnl_set_timeout(struct sk_buff *sender_skb,
                                   struct genl_info *info);
int mtip_debug_eth_gnl_set_vlanID(struct sk_buff *sender_skb,
                                  struct genl_info *info);
int mtip_debug_eth_gnl_get_result(struct sk_buff *sender_skb,
                                  struct genl_info *info);

int mtip_debug_eth_gnl_init(void);
void mtip_debug_eth_gnl_exit(void);

#endif /* MTIP_DEBUG_ETH_GNL_H */
