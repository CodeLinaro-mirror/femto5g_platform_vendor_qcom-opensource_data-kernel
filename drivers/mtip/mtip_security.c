// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include "mtip.h"
#include "mtip_device.h"

#include "mtip_security.h"

/* Register security device recursively on all links. */
static int __register_security_device(struct mtip_security_device *sdev, u32 link_id)
{
	int ret;
	u32 rx_link_id, tx_link_id;
	struct net_device *netdev;
	struct mtip_link_info *link;
	struct mtip_netdev_priv *mtip_priv;

	if (link_id >= MTIP_MAX_LINKS)
		return 0;

	link = platform_driver_priv->mtip_links[link_id];

	if (!link || link->port_device_index != sdev->port_id)
		return __register_security_device(sdev, link_id + 1);

	tx_link_id = link->link_device_index;
#ifdef MTIP_LOOPBACK_SWAP_HANDLE
	rx_link_id = tx_link_id ^ 0x1;
#else
	rx_link_id = tx_link_id;
#endif

	netdev = link->dev;
	mtip_priv = (struct mtip_netdev_priv *)netdev_priv(netdev);
	mtip_priv->sec_dev = sdev;

	ret = sdev->ops->add_link(netdev, sdev, rx_link_id, sdev, tx_link_id);
	if (ret)
		goto fail;

	ret = __register_security_device(sdev, link_id + 1);
	if (ret)
		sdev->ops->del_link(netdev);

fail:
	if (ret)
		mtip_priv->sec_dev = NULL;

	return ret;
}

/**
 * mtip_security_register_device - register a security port/device with MTIP driver
 * @sdev: Security device
 *
 * Register a security device with MTIP driver to offload various fronthaul security
 * operations (like MACsec, IPsec, etc.) to the security hardware.
 */
int mtip_security_register_device(struct mtip_security_device *sdev)
{
	if (!sdev->ops || !sdev->ops->add_link || !sdev->ops->del_link)
		return -EINVAL;

	return __register_security_device(sdev, 0);
}
EXPORT_SYMBOL(mtip_security_register_device);

/**
 * mtip_security_unregister_device - unregisters a security port/device with MTIP driver
 * @sdev: Security device that was previously registered
 */
void mtip_security_unregister_device(struct mtip_security_device *sdev)
{
	u32 link_id;
	struct net_device *netdev;
	struct mtip_link_info *link;
	struct mtip_netdev_priv *mtip_priv;

	for (link_id = 0; link_id < MTIP_MAX_LINKS; ++link_id) {
		link = platform_driver_priv->mtip_links[link_id];
		if (!link)
			continue;

		if (sdev->port_id != link->port_device_index)
			continue;

		netdev = link->dev;
		mtip_priv = (struct mtip_netdev_priv *)netdev_priv(netdev);

		if (mtip_priv->sec_dev != sdev)
			continue;

		if (sdev->ops && sdev->ops->del_link)
			sdev->ops->del_link(netdev);

		mtip_priv->sec_dev = NULL;
	}
}
EXPORT_SYMBOL(mtip_security_unregister_device);

void mtip_security_set_priv(struct net_device *netdev, void *data)
{
	((struct mtip_netdev_priv *)netdev_priv(netdev))->sec_priv = data;
}
EXPORT_SYMBOL(mtip_security_set_priv);

void *mtip_security_get_priv(struct net_device *netdev)
{
	return ((struct mtip_netdev_priv *)netdev_priv(netdev))->sec_priv;
}
EXPORT_SYMBOL(mtip_security_get_priv);
