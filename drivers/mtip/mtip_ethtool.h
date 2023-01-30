//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#ifndef _MTIP_ETHTOOL_H
#define _MTIP_ETHTOOL_H

#include <linux/ethtool.h>

void mtip_ethtool_set_ops(struct net_device *netdev);
int mtip_check_if_running(struct net_device *dev);
void mtip_getdrvinfo(struct net_device *dev, struct ethtool_drvinfo *info);
int mtip_get_link_ksettings(struct net_device *dev, struct ethtool_link_ksettings *cmd);
const char* mtip_ethtool_get_priv_flags_str(u32 index);

#endif // _MTIP_ETHTOOL_H
