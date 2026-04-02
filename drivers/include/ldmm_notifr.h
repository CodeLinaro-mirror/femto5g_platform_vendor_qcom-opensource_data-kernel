/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/*
 * It has definition of faults shared between ldmm and mtip
 */

#ifndef _LDMM_NOTIFR_H
#define _LDMM_NOTIFR_H

#include "ldmm_genl.h"

enum{
	HIGH_BER_SET,
	HIGH_BER_CLR,
	IF_UP,
	IF_DOWN,
	PCS_IF_UP,
	PCS_IF_DOWN,
	RX_LOS_SET,
	RX_LOS_CLR,
	LOCAL_PLUG_OUT_SET,
	LOCAL_PLUG_OUT_CLR
};

typedef struct {
  	int port_type;
  	int interface;
} event_info_struct;

/*Structure between LDMM and ETH to share information*/
struct ldmm_eth_iface_ops {
	stats_info (*ldmm_eth_iface_get_stats_info)(int link_index);
	config_packet_info (*ldmm_eth_iface_get_config_info)(void);
	bool (*ldmm_eth_iface_get_if_link_up)(int link_index);
	int (*ldmm_eth_iface_set_loopback_interfaces)(char **interface_list, int interface_count);
};

#endif /* _LDMM_NOTIFR_H */
