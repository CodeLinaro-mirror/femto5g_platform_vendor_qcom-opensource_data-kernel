//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#ifndef MTIP_MDIO_H
#define MTIP_MDIO_H

#include <linux/netdevice.h>


int mtip_mdio_register(struct net_device *ndev, struct device_node *np);

void mtip_mdio_phy_validate(struct phylink_config *config,
                                   unsigned long *supported,
                                   struct phylink_link_state *state);


#endif /* MTIP_MDIO_H */
