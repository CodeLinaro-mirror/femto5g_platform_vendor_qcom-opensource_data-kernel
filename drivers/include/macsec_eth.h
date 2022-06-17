/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */
 
#ifndef _MACSEC_ETH_H
#define _MACSEC_ETH_H

#include <net/macsec.h>
#include <linux/netdevice.h>

int macsec_eth_set_macsec_ops(const struct macsec_ops *rb_macsec_ops);

int macsec_eth_lookup_eth_link_by_netdev(struct net_device *netdev, u32 *link_index);

struct net_device *macsec_eth_get_netdev_from_link(u32 link_index);

#endif // _MACSEC_ETH_H
