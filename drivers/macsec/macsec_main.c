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

MODULE_LICENSE("GPL v2");

#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>

#include <linux/sched.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/errno.h>  /* error codes */
#include <linux/types.h>  /* size_t */
#include <linux/interrupt.h> /* mark_bh */
#include <linux/clk.h>

#include <linux/in.h>
#include <linux/netdevice.h>   /* struct device, and other headers */
#include <linux/etherdevice.h> /* eth_type_trans */
#include <linux/ip.h>          /* struct iphdr */
#include <linux/tcp.h>         /* struct tcphdr */
#include <linux/skbuff.h>
#include <linux/of.h>

static const struct of_device_id macsec_match[] = {
	{ .compatible = "qcom,rambus-macsec", },
	{ }
};

MODULE_DEVICE_TABLE(of, macsec_match);

#define MACSEC_CLK_FREQ(x) (x * 1000 * 1000UL)

#define MACSEC_CLK_NOM_MAX (MACSEC_CLK_FREQ(200.0))

struct clk* macsec_c2c_clk = NULL;
struct clk* macsec_fh0_clk = NULL;
struct clk* macsec_fh1_clk = NULL;
struct clk* macsec_fh2_clk = NULL;

static int macsec_clock_enablement(struct platform_device *pdev)
{
	int ret;

	/* Get Clocks */
	printk("macsec started getting clocks\n");

	macsec_c2c_clk = devm_clk_get(&pdev->dev, "macsec_c2c_clk");
	if (!macsec_c2c_clk) {
		printk("Failed to get macsec_c2c_clk\n");
		return -ENOMEM;
	}

	macsec_fh0_clk = devm_clk_get(&pdev->dev, "macsec_fh0_clk");
	if (!macsec_fh0_clk) {
		printk("Failed to get macsec_fh0_clk\n");
		return -ENOMEM;
	}

	macsec_fh1_clk = devm_clk_get(&pdev->dev, "macsec_fh1_clk");
	if (!macsec_fh1_clk) {
		printk("Failed to get macsec_fh1_clk\n");
		return -ENOMEM;
	}

	macsec_fh2_clk = devm_clk_get(&pdev->dev, "macsec_fh2_clk");
	if (!macsec_fh2_clk) {
		printk("Failed to get macsec_fh2_clk\n");
		return -ENOMEM;
	}

	/* Vote clocks */
	printk("macsec started clocks vote\n");

	ret = clk_prepare_enable(macsec_c2c_clk);
	if (ret)
	{
		printk("Failed to vote macsec_c2c_clk\n");
	}
	else
	{
		clk_set_rate(macsec_c2c_clk, MACSEC_CLK_NOM_MAX);
	}

	ret = clk_prepare_enable(macsec_fh0_clk);
	if (ret)
	{
		printk("Failed to vote macsec_fh0_clk\n");
	}
	else
	{
		clk_set_rate(macsec_fh0_clk, MACSEC_CLK_NOM_MAX);
	}

	ret = clk_prepare_enable(macsec_fh1_clk);
	if (ret)
	{
		printk("Failed to vote macsec_fh1_clk\n");
	}
	else
	{
		clk_set_rate(macsec_fh1_clk, MACSEC_CLK_NOM_MAX);
	}

	ret = clk_prepare_enable(macsec_fh2_clk);
	if (ret)
	{
		printk("Failed to vote macsec_fh2_clk\n");
	}
	else
	{
		clk_set_rate(macsec_fh2_clk, MACSEC_CLK_NOM_MAX);
	}

	return ret;
}

int macsec_platform_set_bypass(unsigned int base_address)
{
    void __iomem *macsec_base;
    uint32_t val;

    printk("write bypass value to 164-I \n");

    macsec_base = ioremap(base_address + 0x0FE00, 4);
    printk("macsec base = %x\n", macsec_base);
    iowrite32(0x1, macsec_base);

    macsec_base = ioremap(base_address + 0x0FE04, 4);
    printk("macsec base = %x\n", macsec_base);
    iowrite32(0x1, macsec_base);

    macsec_base = ioremap(base_address + 0x0FE08, 4);
    printk("macsec base = %x\n", macsec_base);
    iowrite32(0x1, macsec_base);

    macsec_base = ioremap(base_address + 0x0FE0C, 4);
    printk("macsec base = %x\n", macsec_base);
    iowrite32(0x1, macsec_base);

    printk("write bypass value to 164-E \n");

    macsec_base = ioremap(base_address + 0x4FE00, 4);
    printk("macsec base = %x\n", macsec_base);
    iowrite32(0x1, macsec_base);

    macsec_base = ioremap(base_address + 0x4FE04, 4);
    printk("macsec base = %x\n", macsec_base);
    iowrite32(0x1, macsec_base);

    macsec_base = ioremap(base_address + 0x4FE08, 4);
    printk("macsec base = %x\n", macsec_base);
    iowrite32(0x1, macsec_base);

    macsec_base = ioremap(base_address + 0x4FE0C, 4);
    printk("macsec base = %x\n", macsec_base);
    iowrite32(0x1, macsec_base);

    printk("write bypass value to 163-I \n");

    macsec_base = ioremap(base_address + 0x8FE00, 4);
    printk("macsec base = %x\n", macsec_base);
    iowrite32(0x1, macsec_base);

    macsec_base = ioremap(base_address + 0x8FE04, 4);
    printk("macsec base = %x\n", macsec_base);
    iowrite32(0x1, macsec_base);

    macsec_base = ioremap(base_address + 0x8FE08, 4);
    printk("macsec base = %x\n", macsec_base);
    iowrite32(0x1, macsec_base);

    macsec_base = ioremap(base_address + 0x8FE0C, 4);
    printk("macsec base = %x\n", macsec_base);
    iowrite32(0x1, macsec_base);

    printk("write bypass value to 163-E \n");

    macsec_base = ioremap(base_address + 0x9FE00, 4);
    printk("macsec base = %x\n", macsec_base);
    iowrite32(0x1, macsec_base);

    macsec_base = ioremap(base_address + 0x9FE04, 4);
    printk("macsec base = %x\n", macsec_base);
    iowrite32(0x1, macsec_base);

    macsec_base = ioremap(base_address + 0x9FE08, 4);
    printk("macsec base = %x\n", macsec_base);
    iowrite32(0x1, macsec_base);

    macsec_base = ioremap(base_address + 0x9FE0C, 4);
    printk("macsec base = %x\n", macsec_base);
    iowrite32(0x1, macsec_base);

    val = ioread32(macsec_base);
    printk("read val = %x\n", val);

    return 0;
}

int macsec_platform_probe(struct platform_device *pdev) {

	printk("macsec_platform_probe called\n");

    macsec_clock_enablement(pdev);

    macsec_platform_set_bypass(0x22900000);

    macsec_platform_set_bypass(0x23700000);

    macsec_platform_set_bypass(0x24500000);

    macsec_platform_set_bypass(0x25300000);

	return 0;
}

int macsec_platform_remove(struct platform_device *pdev)
{
	int result = 0;
	return result;
}

static struct platform_driver macsec_platform_driver = {
	.probe  = macsec_platform_probe,
	.remove = macsec_platform_remove,
	.driver = {
		.name = "RAMBUS-MACSEC",
		.of_match_table = of_match_ptr(macsec_match),
	},
};

/**
 * macsec_register_platform_driver
 *  - register as a platform driver
 */
int macsec_register_platform_driver(void)
{
	int ret = 0;
	int perr;

	printk("macsec_register_platform_driver called\n");

	// register for the platform driver
	perr = platform_driver_register(&macsec_platform_driver);

	// HANDLE THE ERROR
	if (perr < 0)
	{
		ret = perr;

		printk("platform_driver_register with error: %d\n", ret);
	}

	return ret;
}

static int macsec_module_init(void)
{
	int ret = 0;

	printk("macsec_module_init called\n");

	ret = macsec_register_platform_driver();

	return ret;
}

static void macsec_module_exit(void)
{
	printk("macsec_module_exit called\n");

	platform_driver_unregister(&macsec_platform_driver);

	return;
}

module_init(macsec_module_init);
module_exit(macsec_module_exit);

