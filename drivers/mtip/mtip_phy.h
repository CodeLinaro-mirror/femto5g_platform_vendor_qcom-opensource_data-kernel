//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#ifndef _MTIP_PHY_H
#define _MTIP_PHY_H

#include <linux/slab.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/phylink.h>

#include "mtip.h"

// PHY driver related functions
int mtip_phy_register_eth(void);
int mtip_phy_deregister_eth(void);

int mtip_phy_setup_phy(struct mtip_port_device_info* port_device);

int mtip_phy_bringup_phy(u32 link_index, int sfp_port_type);
int mtip_phy_teardown_phy(u32 link_index);
int mtip_phy_notify_link_status(u32 link_index, bool status);

// PHYLINK related functions and structs
struct mtip_portdev_priv 
{
    u32 port_type;
};

int mtip_phy_create_phylink(struct mtip_port_device_info* port_device);

#endif // _MTIP_PHY_H
