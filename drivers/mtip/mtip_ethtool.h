//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#ifndef _MTIP_ETHTOOL_H
#define _MTIP_ETHTOOL_H

#include <linux/ethtool.h>

void mtip_ethtool_set_ops(struct net_device *netdev);

#endif // _MTIP_ETHTOOL_H
