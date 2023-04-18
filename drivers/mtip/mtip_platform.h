//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#ifndef _MTIP_PLATFORM_H
#define _MTIP_PLATFORM_H

#include <linux/slab.h>
#include <linux/list.h>
#include <linux/mutex.h>

#include "eth_phy_iface.h"

int mtip_port_probe(struct platform_device *pdev);
int mtip_link_probe(struct platform_device *pdev);
int mtip_platform_probe(struct platform_device *pdev);
int mtip_link_remove(struct platform_device *pdev);
int mtip_port_remove(struct platform_device *pdev);

int mtip_platform_setup_ethernet(unsigned int port_device);
int mtip_platform_convert_lane_speed_to_gbps(enum eth_phy_iface_phy_lane_speed_enum lane_speed);
void mtip_platform_print_platform(void);

#endif // _MTIP_PLATFORM_H
