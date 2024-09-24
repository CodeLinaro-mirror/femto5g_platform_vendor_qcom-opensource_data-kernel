//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022-2024 Qualcomm Innovation Center, Inc. All rights reserved.
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

#define MTIP_ETHTOOL_PRIV_FLAGS_LEN 10

void mtip_ethtool_set_ops(struct net_device *netdev);
void mtip_ethtool_getdrvinfo(struct net_device *dev, struct ethtool_drvinfo *info);
int mtip_ethtool_get_link_ksettings(struct net_device *dev, struct ethtool_link_ksettings *cmd);
int mtip_ethtool_set_link_ksettings(struct net_device *netdev, const struct ethtool_link_ksettings *cmd);
const char* mtip_ethtool_get_priv_flags_str(u32 index);
const char* mtip_ethtool_get_port_config_str(u32 index);
int mtip_ethtool_get_fecparam(struct net_device* netdev, struct ethtool_fecparam* pfec);
int mtip_ethtool_set_fecparam(struct net_device* netdev, struct ethtool_fecparam* pfec);
void mtip_ethtool_set_msglevel(struct net_device *netdev, u32 level);
u32 mtip_ethtool_get_msglevel(struct net_device *netdev);
u32 mtip_ethtool_get_priv_flags(struct net_device *netdev);
int mtip_ethtool_set_priv_flags(struct net_device *netdev, u32 flags);
int get_mtip_ethtool_priv_flags_len(void);
int mtip_ethtool_get_module_eeprom(struct net_device *netdev, struct ethtool_eeprom *ee, u8 *data);
int mtip_ethtool_get_module_info(struct net_device *netdev, struct ethtool_modinfo *modinfo);


#endif // _MTIP_ETHTOOL_H
