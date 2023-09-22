//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#ifndef _MTIP_ETHTOOL_H
#define _MTIP_ETHTOOL_H

#include <linux/ethtool.h>

#define MTIP_ETHTOOL_SET_PFLAG(params, pflag, enable)			\
 	do {							\
 		if (enable)					\
 			(params)->priv_flags |= BIT(pflag);		\
 		else						\
 			(params)->priv_flags &= ~(BIT(pflag));	\
	} while (0)

void mtip_ethtool_set_ops(struct net_device *netdev);
bool mtip_check_if_running(struct net_device *dev);
void mtip_ethtool_getdrvinfo(struct net_device *dev, struct ethtool_drvinfo *info);
int mtip_ethtool_get_link_ksettings(struct net_device *dev, struct ethtool_link_ksettings *cmd);
int mtip_ethtool_set_link_ksettings(struct net_device *netdev, const struct ethtool_link_ksettings *cmd);
const char* mtip_ethtool_get_priv_flags_str(u32 index);
int mtip_ethtool_get_fecparam(struct net_device* netdev, struct ethtool_fecparam* pfec);
int mtip_ethtool_set_fecparam(struct net_device* netdev, struct ethtool_fecparam* pfec);
void mtip_ethtool_set_msglevel(struct net_device *netdev, u32 level);
u32 mtip_ethtool_get_msglevel(struct net_device *netdev);
u32 mtip_ethtool_get_priv_flags(struct net_device *netdev);
int mtip_ethtool_set_priv_flags(struct net_device *netdev, u32 flags);
int mtip_ethtool_handle_pflag(struct net_device *netdev, u32 wanted_flags, u32 flag);
int get_mtip_ethtool_priv_flags_len(void);


#endif // _MTIP_ETHTOOL_H
