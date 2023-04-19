/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _EIP_DEVICE_H_
#define _EIP_DEVICE_H_

#include <linux/netdevice.h>

#include <mtip_security.h>

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
};

#endif /* _EIP_DEVICE_H_ */
