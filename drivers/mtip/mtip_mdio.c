//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/netdevice.h>
#include <linux/phy.h>
#include <linux/of_mdio.h>
#include <linux/of_net.h>
#include <linux/mdio.h>
#include <linux/phylink.h>
#include <linux/delay.h>

#include "mtip_mdio.h"
#include "mtip_device.h"
#include "mtip_mac.h"
#include "mtip_dut.h"
#include "mtip.h"
#include "mtip_logging.h"
#include "mtip_sysfs.h"


// PHY ID for AR8031 PHY instances
#define PHY_ID0_MASK     0xffffffef  // Addr 0x4
#define PHY_ID1_MASK     0xffffffbf  // Addr 0x6
#define PHY_ID2_MASK     0xffffffef  // Addr 0x4
#define PHY_ID3_MASK     0xffffffbf  // Addr 0x6
#define PHY_ID15_MASK    0xffffffef  // Addr 0x4

// Command register offset and bit masks for register content
#define MTIP_MDIO_CMD_REG          0x00000034
#define MTIP_MDIO_PHY_ADDR_SHIFT   5
#define MTIP_MDIO_PHY_ADDR_MASK    GENMASK(9, 5)
#define MTIP_MDIO_REG_ADDR_SHIFT   0
#define MTIP_MDIO_REG_ADDR_MASK    GENMASK(4, 0)
#define MII_READ_MASK              0x00008000  //BIT(15)

// Data register offset
#define MTIP_MDIO_DATA_REG         0x00000038

// Config status register offset and bit masks for register content
#define MTIP_MDIO_CFG_STATUS_REG   0x00000030
#define MII_BUSY                   0x00000001  //BIT(0)
#define MII_READ_ERROR             0x00000002  //BIT(1)
#define MTIP_MDIO_CLK_DIV_SHIFT    7
#define MTIP_MDIO_CLK_DIV_MASK     GENMASK(15, 7)
#define MTIP_MDIO_C45_BIT          0x00000040  // BIT(6)

// Reg-address register offset for C45 and bit masks for register content
#define MTIP_MDIO_REGADDR_REG         0x0000003C

void mtip_mdio_link_up(struct phylink_config *config,
                      struct phy_device *phy, unsigned int mode,
                      phy_interface_t interface, int speed,
                      int duplex, bool tx_pause, bool rx_pause) {
   struct mtip_netdev_priv   *priv = netdev_priv(to_net_dev(config->dev));
   u32 link_index = priv->link_index;

   CSMLOGINFO("mtip_mac_link_up for MAC index %d", link_index);

   // Delay tuning for RX and TX
   mtip_dut_rx_tx_delay_tuning(link_index);

   // Process MAC link up state
   mtip_mac_link_up(link_index);

   if(priv->link_index == MTIP_DEBUG_ETH_LINK_INDEX)
      mtip_sysfs_mac_link_status(true);

   return;
}

void mtip_mdio_link_down(struct phylink_config *config, unsigned int mode,
                                phy_interface_t interface) {
   struct mtip_netdev_priv   *priv = netdev_priv(to_net_dev(config->dev));
   u32 link_index = priv->link_index;

   CSMLOGINFO("mtip_mac_link_down for MAC index %d", link_index);

   // Process MAC link down state
   mtip_mac_link_down(link_index);

   if(priv->link_index == MTIP_DEBUG_ETH_LINK_INDEX)
      mtip_sysfs_mac_link_status(false);

   return;
}

void mtip_mdio_phy_validate(struct phylink_config *config,
                           unsigned long *supported,
                           struct phylink_link_state *state) {
   __ETHTOOL_DECLARE_LINK_MODE_MASK(mac_supported) = { 0, };
   __ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = { 0, };

   phylink_set(mac_supported, 10baseT_Full);
   phylink_set(mac_supported, 100baseT_Full);
   phylink_set(mac_supported, 1000baseT_Full);
   phylink_set(mac_supported, 1000baseKX_Full);

   phylink_set(mac_supported, Autoneg);
   phylink_set(mac_supported, Pause);
   phylink_set(mac_supported, Asym_Pause);
   phylink_set_port_modes(mac_supported);

   bitmap_and(supported, supported, mac_supported,
              __ETHTOOL_LINK_MODE_MASK_NBITS);
   bitmap_andnot(supported, supported, mask,
                 __ETHTOOL_LINK_MODE_MASK_NBITS);
   bitmap_and(state->advertising, state->advertising, mac_supported,
              __ETHTOOL_LINK_MODE_MASK_NBITS);
   bitmap_andnot(state->advertising, state->advertising, mask,
                 __ETHTOOL_LINK_MODE_MASK_NBITS);

   return;
}

static const struct phylink_mac_ops mtip_phylink_mac_ops = {
	.validate = mtip_mdio_phy_validate,
	.mac_config = mtip_dut_iomacro_config,
	.mac_link_up = mtip_mdio_link_up,
	.mac_link_down = mtip_mdio_link_down,
};

static int mtip_mdio_configure(struct mii_bus *bus)
{
	struct net_device          *ndev = bus->priv;
	struct mtip_netdev_priv    *priv = netdev_priv(ndev);
	u32                         value = 0;
	int                         data = 1; // Clock divisor = 1
	u32                         v;

	value |= (data << MTIP_MDIO_CLK_DIV_SHIFT) & MTIP_MDIO_CLK_DIV_MASK;

	// Set this bit for C45 PHY devices
	if(bus->probe_capabilities == MDIOBUS_C45)
		value |= MTIP_MDIO_C45_BIT;
	
	// Wait for busy bit to clear - Can be removed
	if (readl_poll_timeout(priv->mac_ioaddr + MTIP_MDIO_CFG_STATUS_REG, 
		                   v, !(v & MII_BUSY), 100, 10000))
		return -EBUSY;

	// Configure config/status register with with clock divisor as 1
	iowrite32(value, priv->mac_ioaddr + MTIP_MDIO_CFG_STATUS_REG);

	return 0;
}

static int mtip_mdio_read_c45(struct mii_bus *bus, int phyaddr,
                                      int phyreg)
{
	struct net_device          *ndev = bus->priv;
	struct mtip_netdev_priv    *priv = netdev_priv(ndev);
	u32                         value = 0;
	int                         data = 0;
	u32                         v;
	u32                         error = 0;
	u32                         dev_addr = 0;
	u32                         port_addr = 0;
	
	CSMLOGDBG("mtip_mdio_read_c45 : phyaddr %d, phyreg %d", phyaddr, phyreg);

	dev_addr = (phyreg >> 16) & MTIP_MDIO_REG_ADDR_MASK;
	port_addr = (phyaddr << MTIP_MDIO_PHY_ADDR_SHIFT) & MTIP_MDIO_PHY_ADDR_MASK;
	
	value = dev_addr | port_addr;
	value |= MII_READ_MASK;

	// Wait for busy bit to clear
	if (readl_poll_timeout(priv->mac_ioaddr + MTIP_MDIO_CFG_STATUS_REG, v,
		                   !(v & MII_BUSY), 100, 10000))
		return -EBUSY;

	// Queue the read operation for the port and device address via command register per C45
	iowrite32(value, priv->mac_ioaddr + MTIP_MDIO_CMD_REG);

	// Write the regaddr for C45
	iowrite32(phyreg & 0xFFFF, priv->mac_ioaddr + MTIP_MDIO_REGADDR_REG);

	// Wait for busy bit to clear
	if (readl_poll_timeout(priv->mac_ioaddr + MTIP_MDIO_CFG_STATUS_REG, v,
		                   !(v & MII_BUSY), 100, 10000))
		return -EBUSY;

	/* Read the data content from the data register */
	data = (int)ioread32(priv->mac_ioaddr + MTIP_MDIO_DATA_REG);

	// Check if any error in reading
	error = (int)ioread32(priv->mac_ioaddr + MTIP_MDIO_CFG_STATUS_REG);
	if(error & MII_READ_ERROR)
		CSMLOGERR("mtip_mdio_read_c45 failed");

	return data;
}

static int mtip_mdio_write_c45(struct mii_bus *bus, int phyaddr, 
                                      int phyreg, u16 phydata)
{
	struct net_device         *ndev = bus->priv;
	struct mtip_netdev_priv   *priv = netdev_priv(ndev);
	u32                        value = 0;
	int                        data = phydata;
	u32                        v;
	u32                        error = 0;
	u32                        dev_addr = 0;
	u32                        port_addr = 0;

	CSMLOGDBG("mtip_mdio_write_c45 : phyaddr %d, phyreg %d", phyaddr, phyreg);

	dev_addr = (phyreg >> 16) & MTIP_MDIO_REG_ADDR_MASK;
	port_addr = (phyaddr << MTIP_MDIO_PHY_ADDR_SHIFT) & MTIP_MDIO_PHY_ADDR_MASK;
	
	value = dev_addr | port_addr;

	// Wait for busy bit to clear
	if (readl_poll_timeout(priv->mac_ioaddr + MTIP_MDIO_CFG_STATUS_REG, v,
		                   !(v & MII_BUSY), 100, 10000))
		return -EBUSY;

	// Write the port and device address via command register per C45
	iowrite32(value, priv->mac_ioaddr + MTIP_MDIO_CMD_REG);
	
	// Write the regaddr for C45
	iowrite32(phyreg & 0xFFFF, priv->mac_ioaddr + MTIP_MDIO_REGADDR_REG);

	// Write the data content to data register
	iowrite32(data, priv->mac_ioaddr + MTIP_MDIO_DATA_REG);

	// Wait for busy bit to clear
	if (readl_poll_timeout(priv->mac_ioaddr + MTIP_MDIO_CFG_STATUS_REG, v,
		                   !(v & MII_BUSY), 100, 10000))
		return -EBUSY;
	
	// Check if any error in reading
	error = (int)ioread32(priv->mac_ioaddr + MTIP_MDIO_CFG_STATUS_REG);
	if(error & MII_READ_ERROR)
		CSMLOGERR("mtip_mdio_write_c45 failed");

	return (error & MII_READ_ERROR);
}

static int mtip_mdio_read(struct mii_bus *bus, int phyaddr, int phyreg)
{
	struct net_device          *ndev = bus->priv;
	struct mtip_netdev_priv    *priv = netdev_priv(ndev);
	u32                         value = 0;
	int                         data = 0;
	u32                         v;
	u32                         error = 0;

	if(bus->probe_capabilities == MDIOBUS_C45)
		return mtip_mdio_read_c45(bus, phyaddr, phyreg);
	
	CSMLOGDBG("mtip_mdio_read : phyaddr %d, phyreg %d", phyaddr, phyreg);

	value |= (phyaddr << MTIP_MDIO_PHY_ADDR_SHIFT) & MTIP_MDIO_PHY_ADDR_MASK;
	value |= (phyreg << MTIP_MDIO_REG_ADDR_SHIFT) & MTIP_MDIO_REG_ADDR_MASK;
	value |= MII_READ_MASK;

	// Wait for busy bit to clear
	if (readl_poll_timeout(priv->mac_ioaddr + MTIP_MDIO_CFG_STATUS_REG, v,
		                   !(v & MII_BUSY), 100, 10000))
		return -EBUSY;

	// Queue the read operation for the address via command register
	iowrite32(value, priv->mac_ioaddr + MTIP_MDIO_CMD_REG);

	udelay(10);

	// Wait for busy bit to clear - Can be removed
	if (readl_poll_timeout(priv->mac_ioaddr + MTIP_MDIO_CFG_STATUS_REG, v,
		                   !(v & MII_BUSY), 100, 10000))
		return -EBUSY;
	
	/* Read the data content from the data register */
	data = (int)ioread32(priv->mac_ioaddr + MTIP_MDIO_DATA_REG);
	
	// Check if any error in reading
	error = (int)ioread32(priv->mac_ioaddr + MTIP_MDIO_CFG_STATUS_REG);
	if(error & MII_READ_ERROR)
		CSMLOGERR("mtip_mdio_read failed");

	return data;
}

static int mtip_mdio_write(struct mii_bus *bus, int phyaddr, 
                                int phyreg, u16 phydata)
{
	struct net_device         *ndev = bus->priv;
	struct mtip_netdev_priv   *priv = netdev_priv(ndev);
	u32                        value = 0;
	int                        data = phydata;
	u32                        v;
	u32                        error = 0;

	if(bus->probe_capabilities == MDIOBUS_C45)
		return mtip_mdio_write_c45(bus, phyaddr, phyreg, phydata);

	value |= (phyaddr << MTIP_MDIO_PHY_ADDR_SHIFT) & MTIP_MDIO_PHY_ADDR_MASK;
	value |= (phyreg << MTIP_MDIO_REG_ADDR_SHIFT) & MTIP_MDIO_REG_ADDR_MASK;
	
	CSMLOGDBG("mtip_mdio_write, phyaddr %d, phyreg %d, data %d", 
		      phyaddr, phyreg, data);

	// Wait for busy bit to clear
	if (readl_poll_timeout(priv->mac_ioaddr + MTIP_MDIO_CFG_STATUS_REG, v,
		                   !(v & MII_BUSY), 100, 10000))
		return -EBUSY;

	/* Set the address register and data to write */
	iowrite32(value, priv->mac_ioaddr + MTIP_MDIO_CMD_REG);
	iowrite32(data, priv->mac_ioaddr + MTIP_MDIO_DATA_REG);

	udelay(10);

	// Wait for busy bit to clear
	if (readl_poll_timeout(priv->mac_ioaddr + MTIP_MDIO_CFG_STATUS_REG, v,
		                   !(v & MII_BUSY), 100, 10000))
		return -EBUSY;
	
	// Check if any error in reading
	error = (int)ioread32(priv->mac_ioaddr + MTIP_MDIO_CFG_STATUS_REG);
	if(error & MII_READ_ERROR)
		CSMLOGERR("mtip_mdio_write failed");

	return (error & MII_READ_ERROR);
}

u32 mtip_mdio_get_phy_addr_mask(u32 link_index)
{
	switch(link_index)
	{
		case 0:
			return PHY_ID0_MASK;

		case 1:
			return PHY_ID1_MASK;

		case 2:
			return PHY_ID2_MASK;

		case 3:
			return PHY_ID3_MASK;

		case 15:
			return PHY_ID15_MASK;

		default:
			return 0xffffffff;
	}
}

int mtip_mdio_register(struct net_device *ndev, struct device_node *np)
{
	int                           err = 0;
	struct mii_bus               *new_bus;
	int                           addr;
	struct mtip_netdev_priv      *priv = netdev_priv(ndev);
	struct phylink               *phylink;
	phy_interface_t               mode;
	char                         *bus_name = "MTIP MDIO bus";

	CSMLOGINFO("mtip_mdio_register");

	new_bus = mdiobus_alloc();
	if (!new_bus)
		return -ENOMEM;

	snprintf(new_bus->id, MII_BUS_ID_SIZE, "%s%d", bus_name, priv->link_index);
	new_bus->name = new_bus->id;
	new_bus->read = &mtip_mdio_read;
	new_bus->write = &mtip_mdio_write;
	new_bus->priv = ndev;
	new_bus->parent = ndev->dev.parent;
	new_bus->phy_mask = mtip_mdio_get_phy_addr_mask(priv->link_index);

	// Change later based on DT config
	new_bus->probe_capabilities = MDIOBUS_C22;
	
	// MDIO configuration
	mtip_mdio_configure(new_bus);

	err = of_mdiobus_register(new_bus, NULL);
	if(err)
	{
		CSMLOGERR("MDIO registration failed with err = %d", err);
		return err;
	}

	for (addr = 0; addr < 32; addr++)
	{
		struct phy_device *phydev = mdiobus_get_phy(new_bus, addr);

		if (!phydev)
			continue;

		priv->phydev = phydev;

		phy_attached_info(phydev);

		CSMLOGDBG("PHY device detected !");
	}

	/* PHYLINK setup */
	priv->phylink_config.dev = &ndev->dev;
	priv->phylink_config.type = PHYLINK_NETDEV;
	of_get_phy_mode(np, &mode);

	phylink = phylink_create(&priv->phylink_config, of_fwnode_handle(np),
	                         mode, &mtip_phylink_mac_ops);
	if (IS_ERR(phylink))
	{
		CSMLOGERR("PHYLINK creation failed with err = %ld\n", PTR_ERR(phylink));
		return IS_ERR(phylink);
	}
	else
	{
		priv->phylink = phylink;
	}
	
	return 0;
}
