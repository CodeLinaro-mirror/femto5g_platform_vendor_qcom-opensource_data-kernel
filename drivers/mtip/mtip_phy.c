//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#include <linux/init.h>
#include <linux/module.h>

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/gfp.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/in.h>
#include <linux/string.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/skbuff.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/bitrev.h>
#include <linux/slab.h>

#include <linux/moduleparam.h>

#include <linux/sched.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/errno.h>  /* error codes */
#include <linux/types.h>  /* size_t */
#include <linux/interrupt.h> /* mark_bh */

#include <linux/in.h>
#include <linux/netdevice.h>   /* struct device, and other headers */
#include <linux/etherdevice.h> /* eth_type_trans */
#include <linux/ip.h>          /* struct iphdr */
#include <linux/tcp.h>         /* struct tcphdr */
#include <linux/skbuff.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/of_net.h>

#include "mtip.h"
#include "mtip_device.h"
#include "mtip_phy.h"
#include "eth_phy_iface.h"
#include "mtip_sysfs.h"
#include "mtip_mac.h"

struct eth_phy_iface_eth_register_params mtip_phy_eth_params;

extern struct eth_phy_iface_ops qcom_aw_phy_driver_iface_ops;

static void mtip_phy_ready_cb(void *user_data)
{
    CSMLOGINFO("Got the PHY ready cb\n");

    if (platform_driver_priv->phy_is_ready == false) 
    {
        // TBD: do we wait for both DMA and PHY?
    }

    // set the phy_is_ready flag
    platform_driver_priv->phy_is_ready = true;
    return;
}

static void mtip_phy_an_complete_cb(enum mtip_port_type_enum port_type, enum eth_phy_iface_phy_lane_num_enum lane_num)
{
    CSMLOGINFO("Got AN complete CB for port: %d\n", port_type);

    // TBD: we need AN complete for all lanes of a link

    return;
}

int mtip_phy_register_eth(void)
{
    int res = 0;
    bool is_ready = false;
    mtip_phy_eth_params.notify_an_complete = mtip_phy_an_complete_cb;
    mtip_phy_eth_params.userdata_ready = NULL;
    mtip_phy_eth_params.notify_ready = mtip_phy_ready_cb;

    // register with the PHY
    res = (qcom_aw_phy_driver_iface_ops.eth_phy_iface_eth_register)(&mtip_phy_eth_params, &is_ready);

    if (res < 0) 
    {
        CSMLOGERR("Failed to register with PHY: %d\n", res);
        return res;
    }

    // check if PHY is ready
    if (is_ready)
    {
        platform_driver_priv->phy_is_ready = true;
    }
    return 0;
}

int mtip_phy_deregister_eth(void)
{
    CSMLOGINFO("Deregistering with the phy driver\n");

    // deregister with the PHY driver
    (qcom_aw_phy_driver_iface_ops.eth_phy_iface_eth_deregister)();

    return 0;
}

int mtip_phy_setup_phy(struct mtip_port_device_info* port_device)
{
    // setup the phy for the port
    // pass the consolidated lane config of the port to phy
    return (qcom_aw_phy_driver_iface_ops.eth_phy_iface_phy_setup)(port_device->port_type, port_device->lane_config);
}

static void mtip_phy_get_lanes_of_link(u32 link_index, bool lanes_enabled[PHY_LANE_MAX])
{
    u32 port_device_index;
    u32 link_device_index;
    u32 num_lanes;
    int i;
    u32 lane;

    if (mtip_lookup_device_by_link_index(link_index, &port_device_index, &link_device_index) < 0)
    {
        CSMLOGERR("Unable to find device for link index: %d\n", link_index);
        return;
    }

    num_lanes = platform_driver_priv->devices.port_devices[port_device_index].link_devices[link_device_index].num_lanes;

    for (i = 0; i < PHY_LANE_MAX; ++i)
    {
        lanes_enabled[i] = false;
    }

    for (i = 0; i < num_lanes; ++i)
    {
        lane = platform_driver_priv->devices.port_devices[port_device_index].link_devices[link_device_index].lanes[i];
        lanes_enabled[lane] = true;
    }

}

int mtip_phy_bringup_phy(u32 link_index)
{
    enum mtip_port_type_enum port_type;
    bool lanes_enabled[PHY_LANE_MAX];
    u32 port_device_index;
    u32 link_device_index;
    int sfp_port_type = 0; // for now set this to 0

    if (mtip_lookup_device_by_link_index(link_index, &port_device_index, &link_device_index) < 0)
    {
        CSMLOGERR("Unable to find device for link index: %d\n", link_index);
        return -1;
    }

    port_type = platform_driver_priv->devices.port_devices[port_device_index].port_type;

    mtip_phy_get_lanes_of_link(link_index, lanes_enabled);

    // bringup the phy for the specified lanes
    return (qcom_aw_phy_driver_iface_ops.eth_phy_iface_phy_bringup)(port_type, lanes_enabled, sfp_port_type); 
}

int mtip_phy_teardown_phy(u32 link_index)
{
    enum mtip_port_type_enum port_type;
    bool lanes_enabled[PHY_LANE_MAX];
    u32 port_device_index;
    u32 link_device_index;

    if (mtip_lookup_device_by_link_index(link_index, &port_device_index, &link_device_index) < 0)
    {
        CSMLOGERR("Unable to find device for link index: %d\n", link_index);
        return -1;
    }

    port_type = platform_driver_priv->devices.port_devices[port_device_index].port_type;

    mtip_phy_get_lanes_of_link(link_index, lanes_enabled);

    // teardown the phy for the specified lanes
    return (qcom_aw_phy_driver_iface_ops.eth_phy_iface_phy_teardown)(port_type, lanes_enabled);
}

static void mtip_phy_phy_validate(struct phylink_config *config,
                           unsigned long *supported,
                           struct phylink_link_state *state) 
{
   return;
}

static void mtip_phy_get_link_state(struct phylink_config *config,
				 struct phylink_link_state *state)
{
    state->link = 0;

    CSMLOGINFO("mtip_mac_link_state %d", state->link);

	return;
}

static void mtip_phy_config(struct phylink_config *config,
                     unsigned int mode,
                     const struct phylink_link_state *state) 
{
   return;
}

static void mtip_phy_link_up(struct phylink_config *config,
                      struct phy_device *phy, unsigned int mode,
                      phy_interface_t interface, int speed,
                      int duplex, bool tx_pause, bool rx_pause) 
{
    struct mtip_netdev_priv   *priv = netdev_priv(to_net_dev(config->dev));
    u32 link_index = priv->link_index;

    CSMLOGINFO("mtip_phy_link_up for MAC index %d", link_index);

    // process this link up

    // Enable TX and RX on MAC
    mtip_mac_enable_tx_rx(link_index);

    if(priv->link_index == MTIP_DEBUG_ETH_LINK_INDEX)
      mtip_sysfs_mac_link_status(true);

   return;
}

static void mtip_phy_link_down(struct phylink_config *config, unsigned int mode,
                                phy_interface_t interface) 
{
   struct mtip_netdev_priv   *priv = netdev_priv(to_net_dev(config->dev));
   u32 link_index = priv->link_index;

    CSMLOGINFO("mtip_phy_link_down for MAC index %d", link_index);

    // Disable TX and RX on MAC
    mtip_mac_disable_tx_rx(link_index);

   if(priv->link_index == MTIP_DEBUG_ETH_LINK_INDEX)
      mtip_sysfs_mac_link_status(false);
   return;
}

static const struct phylink_mac_ops mtip_phylink_mac_ops = {
	.validate = mtip_phy_phy_validate,
	.mac_pcs_get_state = mtip_phy_get_link_state,
	.mac_config = mtip_phy_config,
	.mac_link_up = mtip_phy_link_up,
	.mac_link_down = mtip_phy_link_down,
};

int mtip_phy_create_phylink(struct net_device *ndev)
{
    u32 link_index;
    u32 port_device_index;
    u32 link_device_index;
    struct mtip_netdev_priv* priv = netdev_priv(ndev);
    struct platform_device* link_pdev;
    phy_interface_t mode;
	struct phylink* phylink;

    link_index = priv->link_index;

    mtip_lookup_device_by_link_index(link_index, &port_device_index, &link_device_index);

    link_pdev = platform_driver_priv->devices.port_devices[port_device_index].link_devices[link_device_index].link_pdev;

	/* PHYLINK setup */
	priv->phylink_config.dev = &ndev->dev;
	priv->phylink_config.type = PHYLINK_NETDEV;
	of_get_phy_mode(link_pdev->dev.of_node, &mode);

	phylink = phylink_create(&priv->phylink_config, of_fwnode_handle(link_pdev->dev.of_node),
	                         mode, &mtip_phylink_mac_ops);
	if (IS_ERR(phylink))
	{
		CSMLOGERR("PHYLINK creation failed with err = %d", PTR_ERR(phylink));
		return IS_ERR(phylink);
	}
	else
	{
		priv->phylink = phylink;
	}

    return 0;
}


