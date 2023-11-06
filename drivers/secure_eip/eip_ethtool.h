/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _EIP_ETHTOOL_H_
#define _EIP_ETHTOOL_H_

#include <linux/netdevice.h>

int eip_ethtool_get_stats(struct net_device *netdev, u64 *data);
int eip_ethtool_get_sset_strings(struct net_device *netdev, u8 *stats_strings);
int eip_ethtool_get_sset_count(struct net_device *netdev);

#endif // _EIP_ETHTOOL_H_
