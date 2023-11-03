/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _MTIP_SECURITY_H_
#define _MTIP_SECURITY_H_

#include <linux/netdevice.h>

struct mtip_security_device;

/**
 * struct mtip_security_ops - Call backs into security device
 *
 * @add_link: Called before a net device starts using any other call backs
 * @del_link: Called after a net device is done using the sec port
 *
 * @enable_bypass:  Called when a channel need to be put in bypass mode
 * @disable_bypass: Called when a channel need to be put in secure mode
 * @fixup_rx_skb: Called for every incoming skb to perform any fixups necessary
 *                for hardware offload
 * @fixup_tx_skb: Called for every outgoing skb to perform any fixups necessary
 *                for hardware offload
 *
 * @update_config: Called when port level config is changed
 *
 * @get_sset_count: Called when ethtool request for stats set count
 * @get_sset_strings: Called when ethtool request for stats string set
 * @get_stats: Called when ethtool request for stats of secure hw
 */
struct mtip_security_ops {
	int (*add_link) (struct net_device * ndev,
			 struct mtip_security_device * rx_sec, int rx_link,
			 struct mtip_security_device * tx_sec, int tx_link);
	void (*del_link) (struct net_device * ndev);

	int (*enable_bypass) (struct net_device * ndev);
	int (*disable_bypass) (struct net_device * ndev);

	int (*fixup_rx_skb) (struct sk_buff * skb);
	int (*fixup_tx_skb) (struct sk_buff * skb);

	int (*update_config) (struct mtip_security_device * sdev, u32 active_links);

	/*ethtool stats callback*/
	int (*get_sset_count) (struct net_device *netdev);
	int (*get_sset_strings) (struct net_device *netdev,u8* stats_strings);
	int (*get_stats) (struct net_device *netdev, u64 *data);
};

/** struct mtip_security_device - Defines a security port device
 *
 * @port_id: FH port that is managed by this device
 * @sec_priv: Private data store area for the security driver
 * @ops: Security device ops
 */
struct mtip_security_device {
	u32 port_id;
	void *sec_priv;
	struct mtip_security_ops *ops;
};

int mtip_security_register_device(struct mtip_security_device *sdev);
void mtip_security_unregister_device(struct mtip_security_device *sdev);

void mtip_security_set_priv(struct net_device *netdev, void *data);
void *mtip_security_get_priv(struct net_device *netdev);

int mtip_security_get_sset_count(struct net_device *netdev);
int mtip_security_get_strings(struct net_device *netdev, u8 *stats_strings);
int mtip_security_get_stats(struct net_device *netdev, u64 *data);

#endif // _MTIP_SECURITY_H_
