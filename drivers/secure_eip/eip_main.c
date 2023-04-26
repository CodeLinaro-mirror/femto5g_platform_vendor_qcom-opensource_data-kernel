//SPDX-License-Identifier: GPL-2.0-only
/*
* Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
*/

/*
* Main file for both MACSEC and IPSEC configuration and initalization.
*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/clk.h>
#include <linux/of.h>
#include <linux/spinlock.h>

#include "cs_driver.h"
#include "device_mgmt.h"
#include "adapter_init.h"
#include "api_driver164_init.h"
#include "macsec_eth.h"

#include <mtip_security.h>

#include "eip_device.h"
#include "eip_macsec.h"
#include "adapter_secy_support.h"
#include "adapter_cfye_support.h"
#include "eip_log.h"
#include "eip_debugfs.h"
#include "eip_reg.h"

/* ETHSS_FHx_MACSEC_WRAPPER_CSR Init sequence offsets and recommended values*/
#define MACSEC_WRAPPER_CFG_REG_OFFSET 0x000A8000
#define WRAPPER_MACSEC_BYPASS_REG_OFFSET 0x000A8028
#define MCSC_AMF_CFG_REG 0x000A8030
#define MCSC_CALENDAR_CFG_REG 0x000A8310
#define MCSC_EIP218_AMF_CFG_REG 0x000A8314
#define ETHSS_FH0_EIP218_0_CONTROL 0x000A0000
#define ETHSS_FH0_EIP218_1_CONTROL 0x000A0020
#define ETHSS_FH0_EIP218_2_CONTROL 0x000A0040
#define ETHSS_FH0_EIP218_3_CONTROL 0x000A0060
#define MCSC_CALENDAR_CFG_REG_VAL_4_LINKS 0x00001111
#define MCSC_CALENDAR_CFG_REG_VAL_2_LINKS 0x00000011
#define MCSC_CALENDAR_CFG_REG_VAL_1_LINKS 0x00000001
#define MCSC_EIP218_AMF_CFG_REG_VAL_4_LINKS 0x10101010
#define MCSC_EIP218_AMF_CFG_REG_VAL_2_LINKS 0x00001010
#define MCSC_EIP218_AMF_CFG_REG_VAL_1_LINKS 0x00000010

#define RATE_CTRL_BUF_EN 0x1
/* Setting TX_AMF_VAL to 0x10 and RX_AMF_VAL 0x00 */
#define AMF_CFG_REG_VAL 0x1000

#define EIP218_CONTROL_IFG_BYTES (0xA << 8)
#define EIP218_CONTROL_MODULO_8 (0x0 << 4)
#define EIP218_CONTROL_MODE_SELECT 0x1
#define EIP_WRAPPER_BYPASS_DISABLE 0x1
#define EIP_WRAPPER_BYPASS_ENABLE 0x0

#define EIP_CALENDAR_CFG_DEFAULT_LINKS_COUNT 4

extern void Device_SetPlatform(uint32_t __iomem *BaseAddr_p,
			       uint32_t device_id);

#define MAX_CHANNELS_PER_PORT 4
#define REG_SIZE 0x100000

static const struct of_device_id eip_match[] = {
	{
		.compatible = "qcom,secure-eip",
	},
	{},
};

struct eip_device {
	uint32_t port_id;
	uint32_t ingress_device_id;
	uint32_t egress_device_id;
	void __iomem *eip_base;
	uint32_t size;
	uint32_t irq;
	struct clk *eip_port_clk;
};

#define EIP_CLK_FREQ(x) (x * 1000 * 1000UL)

#define EIP_CLK_NOM_MAX (EIP_CLK_FREQ(200.0))

struct eip_device eip_device_platform_data[EIP_MAX_PORT];
struct eip_port *eip_ports[EIP_MAX_PORT];
uint32_t eip_reg_dump[EIP_MAX_PORT][REG_SIZE / sizeof(uint32_t)];

void eip_cache_register(unsigned int port_id, unsigned int byte_offset,
			uint32_t val)
{
	if ((port_id < EIP_MAX_PORT) && (byte_offset < REG_SIZE)) {
		eip_reg_dump[port_id][byte_offset / 4] = val;
	} else {
		eip_logerr("Invalid Index: port_id: %d, byte_offset: %d ",
			   port_id, byte_offset);
	}
}

static void eip_reg_write(struct eip_port *port, unsigned int offset,
			  uint32_t val)
{
	writel(val, port->base_addr + offset);
	eip_cache_register(port->id, offset, val);
}

static void eip_secy_cfye_spinlock_init(void)
{
	unsigned int i;
	for (i = 0; i < ADAPTER_EIP164_MAX_NOF_DEVICES; i++)
		spin_lock_init(&SecY_Device_StaticFields[i].Lock);
	for (i = 0; i < ADAPTER_EIP163_MAX_NOF_DEVICES; i++)
		spin_lock_init(&CfyE_Device_StaticFields[i].Lock);
}

static int eip_enable_clock(struct platform_device *pdev, uint32_t port_id)
{
	int ret;
	struct clk *eip_port_clk = NULL;

	if (port_id >= EIP_MAX_PORT) {
		pr_err("eip_main: Invalid port id %d", port_id);
		return -EINVAL;
	}

	eip_port_clk = devm_clk_get(&pdev->dev, "eip_port_clk");
	if (!eip_port_clk) {
		pr_err("eip_main: Failed to get clock for port %d\n", port_id);
		return -ENOMEM;
	}

	/* Vote clocks */

	ret = clk_prepare_enable(eip_port_clk);
	if (ret) {
		pr_err("eip_main: Failed to vote clock for port %d\n", port_id);
	} else {
		clk_set_rate(eip_port_clk, EIP_CLK_NOM_MAX);
	}

	eip_device_platform_data[port_id].eip_port_clk = eip_port_clk;

	return ret;
}

static int eip_device_init(bool fVerbose, bool fIngress, unsigned int device_id)
{
	int rc;
	CfyE_Init_t CfyE_Settings;
	SecY_Settings_t SecY_Settings;

	Log_FormattedMessage("%s : Starting test for %sgress\n", __func__,
			     fIngress ? "in" : "e");

	/* Initalize macsec related private data */
	eip_macsec_initalize_priv_data(device_id);

	Log_FormattedMessage("%s: Initializing CfyE\n", __func__);

	ZEROINIT(CfyE_Settings);

	rc = CfyE_Device_Init(device_id,
			      fIngress ? CFYE_ROLE_INGRESS : CFYE_ROLE_EGRESS,
			      &CfyE_Settings);
	if (rc != CFYE_STATUS_OK) {
		LOG_CRIT("DA_MACSEC: CfyE could not be initialized, error=%d\n",
			 rc);
		return rc;
	}

	Log_FormattedMessage("DA_MACSEC: CfyE is initialized successfully\n");

	Log_FormattedMessage("%s: Initializing SecY\n", __func__);

	ZEROINIT(SecY_Settings);

	/* Non-matching SA flow packet processing rules */
	/* Default rule is to drop non-matching SA packets */
	SecY_Settings.DropBypass.DropType = SECY_SA_DROP_PKT_ERROR;

	rc = SecY_Device_Init(device_id,
			      fIngress ? SECY_ROLE_INGRESS : SECY_ROLE_EGRESS,
			      &SecY_Settings);

	if (rc != SECY_STATUS_OK) {
		LOG_CRIT("DA_MACSEC: SecY could not be initialized, error=%d\n",
			 rc);
		return rc;
	}

	Log_FormattedMessage("DA_MACSEC: SecY is initialized successfully\n");

	return rc;
}

static int eip_port_init(uint32_t port_id)
{
	unsigned int ingress_device, egress_device, device_id, channel_id;

	LOG_CRIT("%s: called Port ID %d\n", __func__, port_id);

	device_id = port_id;

	ingress_device = GET_INGRESS_ID_FROM_PORT_ID(port_id);
	egress_device = GET_EGRESS_ID_FROM_PORT_ID(port_id);

	if (eip_device_init(true, true, ingress_device) < 0) {
		LOG_CRIT("Ingress Init config failed, return;");
		return -1;
	};
	if (eip_device_init(true, false, egress_device) < 0) {
		LOG_CRIT("Egress Init config failed, return;");
		return -1;
	}

	for (channel_id = 0; channel_id < MAX_CHANNELS_PER_PORT; ++channel_id) {
		/* The default bootup behavior :
		   1. Setup CFYE and SECY devices initalized
		   2. Setup the channels per port and set them in bypass mode
		 */

		CfyE_Channel_Bypass_Set(ingress_device, channel_id, true);
		SecY_Channel_Bypass_Set(ingress_device, channel_id, true);

		CfyE_Channel_Bypass_Set(egress_device, channel_id, true);
		SecY_Channel_Bypass_Set(egress_device, channel_id, true);
	}

	LOG_INFO("%s: macsec Init complete for Port %d\n", __func__, port_id);

	return 0;
}

static int eip_port_deinit(uint32_t port_id)
{
	unsigned int ingress_device, egress_device;

	LOG_CRIT("%s: called device_id %d\n", __func__, port_id);

	ingress_device = GET_INGRESS_ID_FROM_PORT_ID(port_id);
	egress_device = GET_EGRESS_ID_FROM_PORT_ID(port_id);

	if (eip_device_deinit(true, ingress_device) < 0) {
		/* capture error */
		LOG_CRIT("%s: failed uninit for ingress device %d ", __func__,
			 ingress_device);
		return -1;
	}

	if (eip_device_deinit(false, egress_device) < 0) {
		/* capture error */
		LOG_CRIT("%s: failed uninit for egress device %d", __func__,
			 egress_device);
		return -1;
	}

	return 0;
}

static inline void wrapper_bypass_set(struct eip_port *port, bool enable)
{
	u32 enable_val;

	enable_val =
		enable ? EIP_WRAPPER_BYPASS_ENABLE : EIP_WRAPPER_BYPASS_DISABLE;
	eip_reg_write(port, WRAPPER_MACSEC_BYPASS_REG_OFFSET, enable_val);
	pr_info(" eip_main: wrapper bypass ddr = 0x%x, val = %d \n",
		port->base_addr + WRAPPER_MACSEC_BYPASS_REG_OFFSET, enable_val);
}

static int eip_mtip_link_config(struct mtip_security_device *sdev,
				u32 active_links)
{
	u32 mcsc_calendar_val = 0;
	u32 mcsc_eip218_amf_val = 0;
	struct eip_port *port = (struct eip_port *)sdev->sec_priv;

	eip_loginfo("Setting %d active link configuration for port %d\n",
		    active_links, port->id);

	switch (active_links) {
	case 1:
		mcsc_calendar_val = MCSC_CALENDAR_CFG_REG_VAL_1_LINKS;
		mcsc_eip218_amf_val = MCSC_EIP218_AMF_CFG_REG_VAL_1_LINKS;
		break;
	case 2:
		mcsc_calendar_val = MCSC_CALENDAR_CFG_REG_VAL_2_LINKS;
		mcsc_eip218_amf_val = MCSC_EIP218_AMF_CFG_REG_VAL_2_LINKS;
		break;
	case 4:
		// Default 4 links config
		mcsc_calendar_val = MCSC_CALENDAR_CFG_REG_VAL_4_LINKS;
		mcsc_eip218_amf_val = MCSC_EIP218_AMF_CFG_REG_VAL_4_LINKS;
		break;
	default:
		eip_logerr("Invalid link configuration %d\n", active_links);
		return -EINVAL;
	}
	eip_reg_write(port, MCSC_CALENDAR_CFG_REG, mcsc_calendar_val);
	eip_logdbg("MCSC_CALENDAR_CFG_REG  ddr = 0x%X, Write val = 0x%X\n",
		   port->base_addr + MCSC_CALENDAR_CFG_REG, mcsc_calendar_val);
	eip_reg_write(port, MCSC_EIP218_AMF_CFG_REG, mcsc_eip218_amf_val);
	eip_logdbg("MCSC_EIP218_AMF_CFG_REG  ddr = 0x%X, Write val = 0x%X\n",
		   port->base_addr + MCSC_EIP218_AMF_CFG_REG,
		   mcsc_eip218_amf_val);

	port->num_active_links = active_links;

	return 0;
}

static inline void macsec_wrapper_init_config(struct mtip_security_device *sdev)
{
	u32 val;
	struct eip_port *port = (struct eip_port *)sdev->sec_priv;
	val = RATE_CTRL_BUF_EN;
	eip_reg_write(port, MACSEC_WRAPPER_CFG_REG_OFFSET, val);
	pr_info(" eip_main: MACSEC_WRAPPER_CFG_REG  ddr = 0x%x, val = %d \n",
		port->base_addr + MACSEC_WRAPPER_CFG_REG_OFFSET, val);

	val = AMF_CFG_REG_VAL;
	eip_reg_write(port, MCSC_AMF_CFG_REG, val);
	pr_info(" eip_main: MCSC_AMF_CFG_REG  ddr = 0x%x, val = %d \n",
		port->base_addr + MCSC_AMF_CFG_REG, val);

	val = MCSC_CALENDAR_CFG_REG_VAL_4_LINKS;
	eip_reg_write(port, MCSC_CALENDAR_CFG_REG, val);
	eip_logdbg("MCSC_CALENDAR_CFG_REG  ddr = 0x%X, Write val = 0x%X\n",
		   port->base_addr + MCSC_CALENDAR_CFG_REG, val);

	val = MCSC_EIP218_AMF_CFG_REG_VAL_4_LINKS;
	eip_reg_write(port, MCSC_EIP218_AMF_CFG_REG, val);
	eip_logdbg("MCSC_EIP218_AMF_CFG_REG  ddr = 0x%X, Write val = 0x%X\n",
		   port->base_addr + MCSC_EIP218_AMF_CFG_REG, val);

	val = EIP218_CONTROL_IFG_BYTES | EIP218_CONTROL_MODULO_8 |
	      EIP218_CONTROL_MODE_SELECT;
	eip_reg_write(port, ETHSS_FH0_EIP218_0_CONTROL, val);
	pr_info(" eip_main: ETHSS_FH0_EIP218_0_CONTROL  ddr = 0x%x, val = %d \n",
		port->base_addr + ETHSS_FH0_EIP218_0_CONTROL, val);

	val = EIP218_CONTROL_IFG_BYTES | EIP218_CONTROL_MODULO_8 |
	      EIP218_CONTROL_MODE_SELECT;
	eip_reg_write(port, ETHSS_FH0_EIP218_1_CONTROL, val);
	pr_info(" eip_main: ETHSS_FH0_EIP218_1_CONTROL  ddr = 0x%x, val = %d \n",
		port->base_addr + ETHSS_FH0_EIP218_1_CONTROL, val);

	val = EIP218_CONTROL_IFG_BYTES | EIP218_CONTROL_MODULO_8 |
	      EIP218_CONTROL_MODE_SELECT;
	eip_reg_write(port, ETHSS_FH0_EIP218_2_CONTROL, val);
	pr_info(" eip_main: ETHSS_FH0_EIP218_2_CONTROL  ddr = 0x%x, val = %d \n",
		port->base_addr + ETHSS_FH0_EIP218_2_CONTROL, val);

	val = EIP218_CONTROL_IFG_BYTES | EIP218_CONTROL_MODULO_8 |
	      EIP218_CONTROL_MODE_SELECT;
	eip_reg_write(port, ETHSS_FH0_EIP218_3_CONTROL, val);
	pr_info(" eip_main: ETHSS_FH0_EIP218_3_CONTROL  ddr = 0x%x, val = %d \n",
		port->base_addr + ETHSS_FH0_EIP218_3_CONTROL, val);
}

static int eip_mtip_add_link(struct net_device *ndev,
			     struct mtip_security_device *rx_sec, int rx_link,
			     struct mtip_security_device *tx_sec, int tx_link)
{
	struct eip_link *link;
	struct eip_port *rx_port = (struct eip_port *)rx_sec->sec_priv;
	struct eip_port *tx_port = (struct eip_port *)tx_sec->sec_priv;

	link = kzalloc(sizeof(*link), GFP_KERNEL);
	if (!link)
		return -ENOMEM;

	link->ndev = ndev;
	link->rx.dp = &rx_port->rx;
	link->rx.ch = rx_link;

	link->tx.dp = &tx_port->tx;
	link->tx.ch = tx_link;

	eip_logcrit("Seure_EIP: %s %s rx = (%u, %u, %u), tx = (%u, %u, %u)\n",
		    __func__, ndev->name, rx_sec->port_id, link->rx.dp->devid,
		    link->rx.ch, tx_sec->port_id, link->tx.dp->devid,
		    link->tx.ch);

	mtip_security_set_priv(ndev, link);

	return 0;
}

static void eip_mtip_del_link(struct net_device *ndev)
{
	struct eip_link *link = (struct eip_link *)mtip_security_get_priv(ndev);

	/* Necessary cleanup */

	kfree(link);
}

static int eip_channel_set_bypass(struct eip_channel *channel, bool bypass)
{
	CfyE_Status_t ce_rc;
	SecY_Status_t se_rc;
	unsigned int devid, chid;

	devid = channel->dp->devid;
	chid = channel->ch;

	ce_rc = CfyE_Channel_Bypass_Set(devid, chid, bypass);
	se_rc = SecY_Channel_Bypass_Set(devid, chid, bypass);

	if (ce_rc != CFYE_STATUS_OK || se_rc != SECY_STATUS_OK)
		return -EFAULT;

	return 0;
}

static int eip_link_set_bypass(struct eip_link *link, bool bypass)
{
	return eip_channel_set_bypass(&link->rx, bypass) |
	       eip_channel_set_bypass(&link->tx, bypass);
}

static int eip_mtip_enable_bypass(struct net_device *ndev)
{
	return eip_link_set_bypass(
		(struct eip_link *)mtip_security_get_priv(ndev), true);
}

static int eip_mtip_disable_bypass(struct net_device *ndev)
{
	return eip_link_set_bypass(
		(struct eip_link *)mtip_security_get_priv(ndev), false);
}

static struct mtip_security_ops mtip_sec_ops = {
	.add_link = eip_mtip_add_link,
	.del_link = eip_mtip_del_link,
	.enable_bypass = eip_mtip_enable_bypass,
	.disable_bypass = eip_mtip_disable_bypass,
	.update_config = eip_mtip_link_config
};

static int eip_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct resource *resource_base;
	u32 port_id = 0;
	struct resource *irq_resource;
	struct eip_port *port;

	pr_info("eip_main: eip_probe called \n");

	port = devm_kzalloc(&pdev->dev, sizeof(*port), GFP_KERNEL);
	if (!port)
		return -ENOMEM;

	platform_set_drvdata(pdev, port);

	/* Read the Port ID */
	ret = of_property_read_u32(pdev->dev.of_node, "qcom,port-id", &port_id);

	if (ret < 0) {
		pr_err("eip_main: get resource failed for port-id\n");
		return -ENODEV;
	}

	pr_info("eip_main: port id is %d\n", port_id);
	if (port_id >= EIP_MAX_PORT) {
		pr_err("eip_main: Invalid port id %d ", port_id);
		return -ENODEV;
	}

	ret = eip_enable_clock(pdev, port_id);
	if (ret) {
		pr_err("eip_main: EIP Clock enablment failed ");
		return -ENODEV;
	}

	port->id = port_id;
	port->rx.devid = port_id * 2;
	port->tx.devid = port->rx.devid + 1;

	eip_device_platform_data[port_id].port_id = port_id;

	/* Physical base address */
	resource_base =
		platform_get_resource_byname(pdev, IORESOURCE_MEM, "eip-base");
	if (!resource_base) {
		pr_err("eip_main: get resource failed for mem 0\n");
		return -ENODEV;
	}

	eip_device_platform_data[port_id].eip_base =
		devm_ioremap_resource(&pdev->dev, resource_base);
	eip_device_platform_data[port_id].size = resource_size(resource_base);
	if (IS_ERR(eip_device_platform_data[port_id].eip_base)) {
		pr_err("eip_main: IOREMAP failed");
		return PTR_ERR(eip_device_platform_data[port_id].eip_base);
	}
	port->base_addr = eip_device_platform_data[port_id].eip_base;
	eip_ports[port_id] = port;

	/* Get IRQ details */
	irq_resource =
		platform_get_resource_byname(pdev, IORESOURCE_IRQ, "eip-irq");
	if (!irq_resource) {
		pr_err("eip_main: get resource failed for irq 0\n");
		return -ENODEV;
	}

	eip_device_platform_data[port_id].irq = irq_resource->start;

	eip_device_platform_data[port_id].ingress_device_id =
		GET_INGRESS_ID_FROM_PORT_ID(port_id);
	eip_device_platform_data[port_id].egress_device_id =
		GET_EGRESS_ID_FROM_PORT_ID(port_id);

	/*Updat the platform IOREMAPped addresses to the platform */
	Device_SetPlatform(eip_device_platform_data[port_id].eip_base,
			   eip_device_platform_data[port_id].ingress_device_id);
	Device_SetPlatform(eip_device_platform_data[port_id].eip_base,
			   eip_device_platform_data[port_id].egress_device_id);

	wrapper_bypass_set(port, false);

	ret = eip_port_init(port_id);
	if (ret < 0) {
		pr_err("eip_main: eip device init failed, return error");
		return ret;
	}

	port->msec_dev.port_id = port->id;
	port->msec_dev.ops = &mtip_sec_ops;
	port->msec_dev.sec_priv = port;
	macsec_wrapper_init_config(&port->msec_dev);

	ret = eip_debugfs_add_port(port);
	if (ret) {
		eip_logerr("Failed, debugfs add port %d", port->id);
		goto fail_debugfs;
	}

	ret = mtip_security_register_device(&port->msec_dev);
	if (ret) {
		eip_logerr("mtip_security register_device, return error ");
		goto fail_mtip_register_dev;
	}

	goto success;

fail_mtip_register_dev:
	eip_debugfs_remove_port(port);
fail_debugfs:
	wrapper_bypass_set(port->id, true);
	eip_port_deinit(port->id);
	return ret;

success:
	eip_loginfo("eip_main: eip device init done");
	return ret;
}

static int eip_remove(struct platform_device *pdev)
{
	int ret = 0;
	struct eip_port *port = (struct eip_port *)platform_get_drvdata(pdev);

	mtip_security_unregister_device(&port->msec_dev);
	eip_debugfs_remove_port(port);

	wrapper_bypass_set(port, true);

	ret = eip_port_deinit(port->id);
	if (!ret)
		LOG_CRIT("eip_main: Device %d uniniatlized succesfully",
			 port->id);

	eip_ports[port->id] = NULL;

	return ret;
}

static struct platform_driver eip_driver = {
	.probe = eip_probe,
	.remove = eip_remove,
	.driver = {
		   .name = "secure-eip",
		   .of_match_table = of_match_ptr(eip_match),
		   },
};

MODULE_DEVICE_TABLE(of, eip_match);

static int eip_module_init(void)
{
	int ret = 0;
	int nIRQ = -1;

	ret = eip_log_init();
	if (ret) {
		pr_err("eip_main: eip_log_init with error: %d\n", ret);
		return -EINVAL;
	}
	pr_info("eip_main: secure eip_module_init called\n");

	eip_secy_cfye_spinlock_init();

	/* trigger first-time initialization of the adapter */
	ret = Device_Initialize(&nIRQ);
	if (ret)
		goto device_init_fail;

	ret = eip_debugfs_init();
	if (ret) {
		pr_err("eip_main: eip_debugfs_init with error: %d\n", ret);
		goto debugfs_init_fail;
	}

	ret = platform_driver_register(&eip_driver);
	if (ret) {
		pr_err("eip_main: platform_driver_register with error: %d\n",
		       ret);
		goto platform_reg_fail;
	}
	ret = macsec_eth_set_macsec_ops(&eip_macsec_ops);
	if (ret) {
		pr_err("eip_main: macsec_eth_set_macsec_ops failed with ret %d\n",
		       ret);
		goto macsec_ops_fail;
	}

	pr_info("eip_main: secure eip_module_init ret %d\n", ret);

	return ret;

macsec_ops_fail:
	platform_driver_unregister(&eip_driver);
platform_reg_fail:
	eip_debugfs_deinit();
debugfs_init_fail:
	Device_UnInitialize();
device_init_fail:
	eip_log_deinit();

	return ret;
}

static void eip_module_exit(void)
{
	printk("eip_main: eip_module_exit called\n");
	platform_driver_unregister(&eip_driver);
	eip_debugfs_deinit();
	Device_UnInitialize();
	eip_log_deinit();
}

int Driver164_Init(void)
{
	return eip_module_init();
}

void Driver164_Exit(void)
{
	eip_module_exit();
}

module_init(Driver164_Init);
module_exit(Driver164_Exit);

MODULE_LICENSE("GPL v2");
