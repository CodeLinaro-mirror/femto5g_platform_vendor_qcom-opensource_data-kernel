/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _EIP_DEVICE_H_
#define _EIP_DEVICE_H_

#include <linux/netdevice.h>

#include <mtip_security.h>

/******************************************************
    ETH interfaces and MACSEC interfaces are linked as below.
    Each FH has 4 ETH interfaces like eth00, eth01, eth02, eth03.
    We need to compute device ID from the link index, so, the device ID
    is basically Ingress 0 and Egress 1 for FH0 eth links
    Ingress 2 and Egress 3 for FH1 eth links and so on.

 ******************************************************/
#define EIP_MAX_PORT 4
#define GET_INGRESS_ID_FROM_PORT_ID(port_id) port_id * 2;
#define GET_EGRESS_ID_FROM_PORT_ID(port_id) port_id * 2 + 1;
#define GET_PORT_ID_FROM_LINK_IDX(link_index) link_index / 4
#define GET_INGRESS_ID_FROM_DEVICE_ID(device_id) device_id * 2
#define GET_EGRESS_ID_FROM_DEVICE_ID(device_id) device_id * 2 + 1
#define GET_CHANNEL_ID_FROM_LINK_IDX(link_index) link_index % 4
#define GET_PORT_ID_FROM_DEVICE_ID(device_id) device_id / 2;

#define EIP_BITS_PER_WORD 32

struct eip_port;

struct eip_datapath {
	int devid;
	struct eip_port *port;
};

struct eip_port {
	int id;
	void __iomem *base_addr;
	u32 num_active_links;

	struct eip_datapath rx;
	struct eip_datapath tx;

	struct mtip_security_device msec_dev;

	struct dentry *dbgfs_dent;
};

struct eip_channel {
	struct eip_datapath *dp;
	int ch;
};

#define eip_chid(eip_ch) ((eip_ch)->ch)
#define eip_devid(eip_ch) ((eip_ch)->dp->devid)

/* Represents the pair of EIP channels associated with a net device */
struct eip_link {
	struct net_device *ndev;
	struct eip_channel rx;
	struct eip_channel tx;

	void *ipsec_priv;
};

#endif /* _EIP_DEVICE_H_ */
