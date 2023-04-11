// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include "mtip.h"
#include "mtip_device.h"

#include "mtip_security.h"

/* update port config on all links. */
static void __update_security_port_config()
{
    u32 link_index;
    struct net_device *netdev;
    struct mtip_link_info *link;
    struct mtip_netdev_priv *mtip_priv;
    u32 port_type;
    enum mtip_port_config_enum port_config = MTIP_PORT_CONFIG_4x25GBASE_R;

    for (link_index = 0; link_index < MTIP_MAX_LINKS; ++link_index) {
        link = platform_driver_priv->mtip_links[link_index];
        if (!link)
            continue;

		if (mtip_lookup_port_type_by_link_index(link_index, &port_type) < 0)
		{
			CSMLOGERR("invalid port_type for link_index %d", link_index);
			continue;
		}

        netdev = link->dev;
        mtip_priv = (struct mtip_netdev_priv *)netdev_priv(netdev);

        port_config = platform_driver_priv->mtip_ports[port_type]->port_config;

        // provide an update to security driver regarding port config
        mtip_device_update_security_config(netdev, port_config);
    }
}

/* Register security device recursively on all links. */
static int __register_security_device(struct mtip_security_device *sdev, u32 link_index)
{
	int ret = 0;
	u32 rx_link_id, tx_link_id;
	struct net_device *netdev;
	struct mtip_link_info *link;
	struct mtip_netdev_priv *mtip_priv;
    u32 port_type;

	if (link_index >= MTIP_MAX_LINKS)
		return 0;

	link = platform_driver_priv->mtip_links[link_index];

    if (mtip_lookup_port_type_by_link_index(link_index, &port_type) < 0)
	{
		CSMLOGDBG("invalid port_type for link_index %d", link_index);
		goto fail;
	}

	if (!link || port_type != sdev->port_id)
		return __register_security_device(sdev, link_index + 1);

	tx_link_id = link->link_index;
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

	ret = __register_security_device(sdev, link_index + 1);
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
    int retval = 0;
	if (!sdev->ops || !sdev->ops->add_link || !sdev->ops->del_link)
		return -EINVAL;

	retval = __register_security_device(sdev, 0);

    // update the number of links of all ports
    __update_security_port_config();

    return retval;
}
EXPORT_SYMBOL(mtip_security_register_device);

/**
 * mtip_security_unregister_device - unregisters a security port/device with MTIP driver
 * @sdev: Security device that was previously registered
 */
void mtip_security_unregister_device(struct mtip_security_device *sdev)
{
	u32 link_index;
	struct net_device *netdev;
	struct mtip_link_info *link;
	struct mtip_netdev_priv *mtip_priv;
    u32 port_type;

	for (link_index = 0; link_index < MTIP_MAX_LINKS; ++link_index) {
		link = platform_driver_priv->mtip_links[link_index];
		if (!link)
			continue;

        if (mtip_lookup_port_type_by_link_index(link_index, &port_type) < 0)
		{
			CSMLOGERR("invalid port_type for link_index %d", link_index);
			continue;
		}

		if (sdev->port_id != port_type)
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
