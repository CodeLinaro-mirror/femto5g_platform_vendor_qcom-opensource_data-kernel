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

#include "mtip_clocks.h"
#include "mtip.h"
#include "mtip_logging.h"
#include "mtip_ethtool.h"

static int mtip_clocks_enable_clock(struct device* dev, const char* id, struct clk** clk)
{
    int ret;
    struct clk* pclk = NULL;
    *clk = NULL;

    pclk = devm_clk_get(dev, id);

    if (!pclk) {
        CSMLOGERR("Failed to get %s\n", id);
        return -ENOMEM;
    }
    ret = clk_prepare_enable(pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote %s\n", id);
        *clk = NULL;
        return ret;
    }
    *clk = pclk;
    return 0;
}

static int mtip_clocks_setup_gcc_clocks(void)
{
    int ret;
    u32 index = 0;
    struct clk* pclk;
    struct device *dev = &platform_driver_priv->devices.root_pdev->dev;

    CSMLOGDBG("setting up GCC clocks\n");

    // enable GCC clocks
    ret = mtip_clocks_enable_clock(dev, "GCC_C2C_HM_APB_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote GCC_C2C_HM_APB_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_GCC_APB_CLK_MAX_NOM);
    }
    platform_driver_priv->clocks.gcc_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "GCC_FH_HM_APB_0_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote GCC_FH_HM_APB_0_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_GCC_APB_CLK_MAX_NOM);
    }
    platform_driver_priv->clocks.gcc_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "GCC_FH_HM_APB_1_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote GCC_FH_HM_APB_1_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_GCC_APB_CLK_MAX_NOM);
    }
    platform_driver_priv->clocks.gcc_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "GCC_FH_HM_APB_2_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote GCC_FH_HM_APB_2_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_GCC_APB_CLK_MAX_NOM);
    }
    platform_driver_priv->clocks.gcc_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "GCC_ETH_DBG_C2C_HM_APB_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote GCC_ETH_DBG_C2C_HM_APB_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_GCC_APB_CLK_MAX_NOM);
    }
    platform_driver_priv->clocks.gcc_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "GCC_ETH_DBG_SNOC_AXI_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote GCC_ETH_DBG_SNOC_AXI_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_GCC_SNOC_AXI_CLK_MAX_NOM);
    }
    platform_driver_priv->clocks.gcc_clocks[index] = pclk;
    ++index;

    CSMLOGDBG("gcc clocks index: %d, arr size: %d", index, MTIP_CLOCKS_NUM_GCC_CLOCKS);

    return ret;
}

static int mtip_clocks_setup_c2c_clocks(void)
{
    int ret;
    u32 index = 0;
    struct clk* pclk;
    struct device *dev = &platform_driver_priv->devices.root_pdev->dev;

    CSMLOGDBG("setting up C2C clocks\n");

    // enable C2C clocks
    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_C2C_0_HM_FF_0_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_C2C_0_HM_FF_0_CLK\n");
    }
    platform_driver_priv->clocks.ecpricc_c2c_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_C2C_0_HM_FF_1_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_C2C_0_HM_FF_1_CLK\n");
    }
    platform_driver_priv->clocks.ecpricc_c2c_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_MAC_C2C_HM_REF_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_MAC_C2C_HM_REF_CLK\n");
    }
    platform_driver_priv->clocks.ecpricc_c2c_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_C2C_HM_FF_0_DIV_CLK_SRC", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_C2C_HM_FF_0_DIV_CLK_SRC\n");
    }
    platform_driver_priv->clocks.ecpricc_c2c_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_C2C_HM_FF_1_DIV_CLK_SRC", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_C2C_HM_FF_1_DIV_CLK_SRC\n");
    }
    platform_driver_priv->clocks.ecpricc_c2c_clocks[index] = pclk;
    ++index;

    CSMLOGDBG("c2c clocks index: %d, arr size: %d", index, MTIP_CLOCKS_NUM_ECPRICC_C2C_CLOCKS);

    return ret;
}

static int mtip_clocks_setup_dbg_clocks(void)
{
    int ret;
    u32 index = 0;
    struct clk* pclk;
    struct device *dev = &platform_driver_priv->devices.root_pdev->dev;

    CSMLOGDBG("setting up DBG clocks\n");

    // enable DBG clocks
    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_DBG_C2C_HM_FF_0_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_DBG_C2C_HM_FF_0_CLK\n");
    }
    platform_driver_priv->clocks.ecpricc_dbg_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_DBG_C2C_HM_FF_1_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_DBG_C2C_HM_FF_1_CLK\n");
    }
    platform_driver_priv->clocks.ecpricc_dbg_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_MAC_DBG_C2C_HM_REF_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_MAC_DBG_C2C_HM_REF_CLK\n");
    }
    platform_driver_priv->clocks.ecpricc_dbg_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_DBG_C2C_HM_FF_0_DIV_CLK_SRC", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_DBG_C2C_HM_FF_0_DIV_CLK_SRC\n");
    }
    platform_driver_priv->clocks.ecpricc_dbg_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_DBG_C2C_HM_FF_1_DIV_CLK_SRC", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_DBG_C2C_HM_FF_1_DIV_CLK_SRC\n");
    }
    platform_driver_priv->clocks.ecpricc_dbg_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_MSS_EMAC_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_MSS_EMAC_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_ECPRI_MSS_EMAC_REF_CLK_MAX_NOM);
    }
    platform_driver_priv->clocks.ecpricc_dbg_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_ETH_DBG_NOC_AXI_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_ETH_DBG_NOC_AXI_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_ECPRI_ETH_DBG_NOC_REF_CLK_MAX_NOM);
    }
    platform_driver_priv->clocks.ecpricc_dbg_clocks[index] = pclk;
    ++index;

    CSMLOGDBG("dbg clocks index: %d, arr size: %d", index, MTIP_CLOCKS_NUM_ECPRICC_DBG_CLOCKS);

    return ret;
}

static int mtip_clocks_setup_fh0_clocks(void)
{
    int ret;
    u32 index = 0;
    struct clk* pclk;
    struct device *dev = &platform_driver_priv->devices.root_pdev->dev;

    CSMLOGDBG("setting up FH0 clocks\n");

    // enable FH0 clocks
    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_0_HM_FF_0_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_0_HM_FF_0_CLK\n");
    }
    platform_driver_priv->clocks.ecpricc_fh0_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_0_HM_FF_1_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_0_HM_FF_1_CLK\n");
    }
    platform_driver_priv->clocks.ecpricc_fh0_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_0_HM_FF_2_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_0_HM_FF_2_CLK\n");
    }
    platform_driver_priv->clocks.ecpricc_fh0_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_0_HM_FF_3_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_0_HM_FF_3_CLK\n");
    }
    platform_driver_priv->clocks.ecpricc_fh0_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_MAC_FH0_HM_REF_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_MAC_FH0_HM_REF_CLK\n");
    }
    platform_driver_priv->clocks.ecpricc_fh0_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_0_HM_FF_0_DIV_CLK_SRC", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_0_HM_FF_0_DIV_CLK_SRC\n");
    }
    platform_driver_priv->clocks.ecpricc_fh0_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_0_HM_FF_1_DIV_CLK_SRC", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_0_HM_FF_1_DIV_CLK_SRC\n");
    }
    platform_driver_priv->clocks.ecpricc_fh0_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_0_HM_FF_2_DIV_CLK_SRC", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_0_HM_FF_2_DIV_CLK_SRC\n");
    }
    platform_driver_priv->clocks.ecpricc_fh0_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_0_HM_FF_3_DIV_CLK_SRC", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_0_HM_FF_3_DIV_CLK_SRC\n");
    }
    platform_driver_priv->clocks.ecpricc_fh0_clocks[index] = pclk;
    ++index;

    CSMLOGDBG("fh0 clocks index: %d, arr size: %d", index, MTIP_CLOCKS_NUM_ECPRICC_FH_CLOCKS);

    return ret;
}

static int mtip_clocks_setup_fh1_clocks(void)
{
    int ret;
    u32 index = 0;
    struct clk* pclk;
    struct device *dev = &platform_driver_priv->devices.root_pdev->dev;

    CSMLOGDBG("setting up FH1 clocks\n");

    // enable FH1 clocks
    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_1_HM_FF_0_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_1_HM_FF_0_CLK\n");
    }
    platform_driver_priv->clocks.ecpricc_fh1_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_1_HM_FF_1_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_1_HM_FF_1_CLK\n");
    }
    platform_driver_priv->clocks.ecpricc_fh1_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_1_HM_FF_2_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_1_HM_FF_2_CLK\n");
    }
    platform_driver_priv->clocks.ecpricc_fh1_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_1_HM_FF_3_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_1_HM_FF_3_CLK\n");
    }
    platform_driver_priv->clocks.ecpricc_fh1_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_MAC_FH1_HM_REF_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_MAC_FH1_HM_REF_CLK\n");
    }
    platform_driver_priv->clocks.ecpricc_fh1_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_1_HM_FF_0_DIV_CLK_SRC", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_1_HM_FF_0_DIV_CLK_SRC\n");
    }
    platform_driver_priv->clocks.ecpricc_fh1_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_1_HM_FF_1_DIV_CLK_SRC", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_1_HM_FF_1_DIV_CLK_SRC\n");
    }
    platform_driver_priv->clocks.ecpricc_fh1_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_1_HM_FF_2_DIV_CLK_SRC", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_1_HM_FF_2_DIV_CLK_SRC\n");
    }
    platform_driver_priv->clocks.ecpricc_fh1_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_1_HM_FF_3_DIV_CLK_SRC", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_1_HM_FF_3_DIV_CLK_SRC\n");
    }
    platform_driver_priv->clocks.ecpricc_fh1_clocks[index] = pclk;
    ++index;

    CSMLOGDBG("fh1 clocks index: %d, arr size: %d", index, MTIP_CLOCKS_NUM_ECPRICC_FH_CLOCKS);

    return ret;
}

static int mtip_clocks_setup_fh2_clocks(void)
{
    int ret;
    u32 index = 0;
    struct clk* pclk;
    struct device *dev = &platform_driver_priv->devices.root_pdev->dev;

    CSMLOGDBG("setting up FH2 clocks\n");

    // enable FH1 clocks
    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_2_HM_FF_0_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_2_HM_FF_0_CLK\n");
    }
    platform_driver_priv->clocks.ecpricc_fh2_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_2_HM_FF_1_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_2_HM_FF_1_CLK\n");
    }
    platform_driver_priv->clocks.ecpricc_fh2_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_2_HM_FF_2_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_2_HM_FF_2_CLK\n");
    }
    platform_driver_priv->clocks.ecpricc_fh2_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_2_HM_FF_3_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_2_HM_FF_3_CLK\n");
    }
    platform_driver_priv->clocks.ecpricc_fh2_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_MAC_FH2_HM_REF_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_MAC_FH2_HM_REF_CLK\n");
    }
    platform_driver_priv->clocks.ecpricc_fh2_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_2_HM_FF_0_DIV_CLK_SRC", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_2_HM_FF_0_DIV_CLK_SRC\n");
    }
    platform_driver_priv->clocks.ecpricc_fh2_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_2_HM_FF_1_DIV_CLK_SRC", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_2_HM_FF_1_DIV_CLK_SRC\n");
    }
    platform_driver_priv->clocks.ecpricc_fh2_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_2_HM_FF_2_DIV_CLK_SRC", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_2_HM_FF_2_DIV_CLK_SRC\n");
    }
    platform_driver_priv->clocks.ecpricc_fh2_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_2_HM_FF_3_DIV_CLK_SRC", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_2_HM_FF_3_DIV_CLK_SRC\n");
    }
    platform_driver_priv->clocks.ecpricc_fh2_clocks[index] = pclk;
    ++index;

    CSMLOGDBG("fh2 clocks index: %d, arr size: %d", index, MTIP_CLOCKS_NUM_ECPRICC_FH_CLOCKS);

    return ret;
}

/*
 * mtip_clocks_setup_clocks
 */
void mtip_clocks_setup_clocks(void)
{
    CSMLOGDBG("MTIP started getting clocks\n");

    mtip_clocks_setup_gcc_clocks();

    mtip_clocks_setup_c2c_clocks();

    mtip_clocks_setup_dbg_clocks();

    mtip_clocks_setup_fh0_clocks();

    mtip_clocks_setup_fh1_clocks();

    mtip_clocks_setup_fh2_clocks();

    return;
}

static void mtip_clocks_set_fh0_clock_rates(enum mtip_port_config_enum port_config)
{
    u32 ff_0_index = 0;
    u32 ff_1_index = 1;
    u32 ff_2_index = 2;
    u32 ff_3_index = 3;
    u32 hm_ref_index = 4;
    unsigned long ff_0_rate = MTIP_ECPRI_FF_CLK_MAX_NOM;
    unsigned long ff_1_rate = MTIP_ECPRI_FF_CLK_MAX_NOM;
    unsigned long ff_2_rate = MTIP_ECPRI_FF_CLK_MAX_NOM;
    unsigned long ff_3_rate = MTIP_ECPRI_FF_CLK_MAX_NOM;
    unsigned long hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_MAX_NOM;

    struct clk* ff_0_clock = platform_driver_priv->clocks.ecpricc_fh0_clocks[ff_0_index];
    struct clk* ff_1_clock = platform_driver_priv->clocks.ecpricc_fh0_clocks[ff_1_index];
    struct clk* ff_2_clock = platform_driver_priv->clocks.ecpricc_fh0_clocks[ff_2_index];
    struct clk* ff_3_clock = platform_driver_priv->clocks.ecpricc_fh0_clocks[ff_3_index];
    struct clk* hm_ref_clock = platform_driver_priv->clocks.ecpricc_fh0_clocks[hm_ref_index];

    switch (port_config) 
    {
        // config 1 is 100GBASE_R family
    case MTIP_PORT_CONFIG_1x100GBASE_R:
    case MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC_LL:
    case MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC:
        // config 2 is 100GBASE_R2 family
    case MTIP_PORT_CONFIG_1x100GBASE_R2:
    case MTIP_PORT_CONFIG_1x100GBASE_R2_RSFEC:
        // config 3 is 100GBASE_R4 family
    case MTIP_PORT_CONFIG_1x100GBASE_R4:
    case MTIP_PORT_CONFIG_1x100GBASE_R4_RSFEC:
        {
            // set ff0 to high and rest to off
            ff_0_rate = MTIP_ECPRI_FF_CLK_HIGH;
            ff_1_rate = MTIP_ECPRI_FF_CLK_HIGH;//MTIP_ECPRI_FF_CLK_OFF;
            ff_2_rate = MTIP_ECPRI_FF_CLK_HIGH;//MTIP_ECPRI_FF_CLK_OFF;
            ff_3_rate = MTIP_ECPRI_FF_CLK_HIGH;//MTIP_ECPRI_FF_CLK_OFF;

            // set hm ref to high
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_HIGH;
        }
        break;
        // config 4 is 1x50GBASE_R2 family
    case MTIP_PORT_CONFIG_1x50GBASE_R2:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_RSFEC:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_LUAI:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_LUAI_FEC:
        {
            // set ff0 to medium and rest to off
            ff_0_rate = MTIP_ECPRI_FF_CLK_MED;
            ff_1_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;
            ff_2_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;
            ff_3_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;

            // set hm ref to high
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_HIGH;
        }
        break;
        // config 5 is 40GBASE_R4 family
    case MTIP_PORT_CONFIG_1x40GBASE_R4:
    case MTIP_PORT_CONFIG_1x40GBASE_R4_FEC:
        {
            // set ff0 to medium and rest to off
            ff_0_rate = MTIP_ECPRI_FF_CLK_MED;
            ff_1_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;
            ff_2_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;
            ff_3_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;

            // set hm ref to medium
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_MED;
        }
        break;
        // config 6 2x50GBASE_R family
    case MTIP_PORT_CONFIG_2x50GBASE_R:
    case MTIP_PORT_CONFIG_2x50GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_1x50GBASE_R:
    case MTIP_PORT_CONFIG_1x50GBASE_R_RSFEC:
        {
            // set ff0 and ff1 to medium and rest to off
            ff_0_rate = MTIP_ECPRI_FF_CLK_MED;
            ff_1_rate = MTIP_ECPRI_FF_CLK_MED;
            ff_2_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;
            ff_3_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;

            // set hm ref to high
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_HIGH;
        }
        break;
        // config 11 is 4x25GBASE_R family
    case MTIP_PORT_CONFIG_1x25GBASE_R:
    case MTIP_PORT_CONFIG_1x25GBASE_R_FEC:
    case MTIP_PORT_CONFIG_4x25GBASE_R:
    case MTIP_PORT_CONFIG_4x25GBASE_R_FEC:
    case MTIP_PORT_CONFIG_1x25GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_4x25GBASE_R_RSFEC:
        {
            // set all to medium
            ff_0_rate = MTIP_ECPRI_FF_CLK_MED;
            ff_1_rate = MTIP_ECPRI_FF_CLK_MED;
            ff_2_rate = MTIP_ECPRI_FF_CLK_MED;
            ff_3_rate = MTIP_ECPRI_FF_CLK_MED;

            // set hm ref to medium
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_MED;
        }
        break;
        // config 12 is 4x10GBASE_R family
    case MTIP_PORT_CONFIG_1x10GBASE_R:
    case MTIP_PORT_CONFIG_1x10GBASE_R_FEC:
    case MTIP_PORT_CONFIG_4x10GBASE_R:
    case MTIP_PORT_CONFIG_4x10GBASE_R_FEC:
        {
            // set all to low
            ff_0_rate = MTIP_ECPRI_FF_CLK_LOW;
            ff_1_rate = MTIP_ECPRI_FF_CLK_LOW;
            ff_2_rate = MTIP_ECPRI_FF_CLK_LOW;
            ff_3_rate = MTIP_ECPRI_FF_CLK_LOW;

            // set hm ref to low
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_LOW;
        }
        break;
        // config 13 is 2x50GBASE_R2 family
    case MTIP_PORT_CONFIG_2x50GBASE_R2:
    case MTIP_PORT_CONFIG_2x50GBASE_R2_FEC:
    case MTIP_PORT_CONFIG_2x50GBASE_R2_LUAI:
    case MTIP_PORT_CONFIG_2x50GBASE_R2_LUAI_FEC:
        {
            // set ff0 and ff1 to medium and rest to off
            ff_0_rate = MTIP_ECPRI_FF_CLK_MED;
            ff_1_rate = MTIP_ECPRI_FF_CLK_MED;
            ff_2_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;
            ff_3_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;

            // set hm ref to high
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_HIGH;
        }
        break;
    default:
        break;
    }

    CSMLOGDBG("Setting fh0 clock[%d] to %ld", ff_0_index, ff_0_rate);
    CSMLOGDBG("Setting fh0 clock[%d] to %ld", ff_1_index, ff_1_rate);
    CSMLOGDBG("Setting fh0 clock[%d] to %ld", ff_2_index, ff_2_rate);
    CSMLOGDBG("Setting fh0 clock[%d] to %ld", ff_3_index, ff_3_rate);
    CSMLOGDBG("Setting fh0 clock[%d] to %ld", hm_ref_index, hm_ref_rate);

    clk_set_rate(ff_0_clock, ff_0_rate);
    clk_set_rate(ff_1_clock, ff_1_rate);
    clk_set_rate(ff_2_clock, ff_2_rate);
    clk_set_rate(ff_3_clock, ff_3_rate);

    clk_set_rate(hm_ref_clock, hm_ref_rate);
}

static void mtip_clocks_set_fh1_clock_rates(enum mtip_port_config_enum port_config)
{
    u32 ff_0_index = 0;
    u32 ff_1_index = 1;
    u32 ff_2_index = 2;
    u32 ff_3_index = 3;
    u32 hm_ref_index = 4;
    unsigned long ff_0_rate = MTIP_ECPRI_FF_CLK_MAX_NOM;
    unsigned long ff_1_rate = MTIP_ECPRI_FF_CLK_MAX_NOM;
    unsigned long ff_2_rate = MTIP_ECPRI_FF_CLK_MAX_NOM;
    unsigned long ff_3_rate = MTIP_ECPRI_FF_CLK_MAX_NOM;
    unsigned long hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_MAX_NOM;

    struct clk* ff_0_clock = platform_driver_priv->clocks.ecpricc_fh1_clocks[ff_0_index];
    struct clk* ff_1_clock = platform_driver_priv->clocks.ecpricc_fh1_clocks[ff_1_index];
    struct clk* ff_2_clock = platform_driver_priv->clocks.ecpricc_fh1_clocks[ff_2_index];
    struct clk* ff_3_clock = platform_driver_priv->clocks.ecpricc_fh1_clocks[ff_3_index];
    struct clk* hm_ref_clock = platform_driver_priv->clocks.ecpricc_fh1_clocks[hm_ref_index];

    switch (port_config) 
    {
        // config 1 is 100GBASE_R family
    case MTIP_PORT_CONFIG_1x100GBASE_R:
    case MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC_LL:
    case MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC:
        // config 2 is 100GBASE_R2 family
    case MTIP_PORT_CONFIG_1x100GBASE_R2:
    case MTIP_PORT_CONFIG_1x100GBASE_R2_RSFEC:
        // config 3 is 100GBASE_R4 family
    case MTIP_PORT_CONFIG_1x100GBASE_R4:
    case MTIP_PORT_CONFIG_1x100GBASE_R4_RSFEC:
        {
            // set ff0 to high and rest to off
            ff_0_rate = MTIP_ECPRI_FF_CLK_HIGH;
            ff_1_rate = MTIP_ECPRI_FF_CLK_HIGH;//MTIP_ECPRI_FF_CLK_OFF;
            ff_2_rate = MTIP_ECPRI_FF_CLK_HIGH;//MTIP_ECPRI_FF_CLK_OFF;
            ff_3_rate = MTIP_ECPRI_FF_CLK_HIGH;//MTIP_ECPRI_FF_CLK_OFF;

            // set hm ref to high
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_HIGH;
        }
        break;
        // config 4 is 1x50GBASE_R2 family
    case MTIP_PORT_CONFIG_1x50GBASE_R2:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_RSFEC:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_LUAI:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_LUAI_FEC:
        {
            // set ff0 to medium and rest to off
            ff_0_rate = MTIP_ECPRI_FF_CLK_MED;
            ff_1_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;
            ff_2_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;
            ff_3_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;

            // set hm ref to high
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_HIGH;
        }
        break;
        // config 5 is 40GBASE_R4 family
    case MTIP_PORT_CONFIG_1x40GBASE_R4:
    case MTIP_PORT_CONFIG_1x40GBASE_R4_FEC:
        {
            // set ff0 to medium and rest to off
            ff_0_rate = MTIP_ECPRI_FF_CLK_MED;
            ff_1_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;
            ff_2_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;
            ff_3_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;

            // set hm ref to medium
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_MED;
        }
        break;
        // config 6 2x50GBASE_R family
    case MTIP_PORT_CONFIG_2x50GBASE_R:
    case MTIP_PORT_CONFIG_2x50GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_1x50GBASE_R:
    case MTIP_PORT_CONFIG_1x50GBASE_R_RSFEC:
        {
            // set ff0 and ff1 to medium and rest to off
            ff_0_rate = MTIP_ECPRI_FF_CLK_MED;
            ff_1_rate = MTIP_ECPRI_FF_CLK_MED;
            ff_2_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;
            ff_3_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;

            // set hm ref to high
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_HIGH;
        }
        break;
        // config 11 is 4x25GBASE_R family
    case MTIP_PORT_CONFIG_1x25GBASE_R:
    case MTIP_PORT_CONFIG_1x25GBASE_R_FEC:
    case MTIP_PORT_CONFIG_4x25GBASE_R:
    case MTIP_PORT_CONFIG_4x25GBASE_R_FEC:
    case MTIP_PORT_CONFIG_1x25GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_4x25GBASE_R_RSFEC:
        {
            // set all to medium
            ff_0_rate = MTIP_ECPRI_FF_CLK_MED;
            ff_1_rate = MTIP_ECPRI_FF_CLK_MED;
            ff_2_rate = MTIP_ECPRI_FF_CLK_MED;
            ff_3_rate = MTIP_ECPRI_FF_CLK_MED;

            // set hm ref to medium
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_MED;
        }
        break;
        // config 12 is 4x10GBASE_R family
    case MTIP_PORT_CONFIG_1x10GBASE_R:
    case MTIP_PORT_CONFIG_1x10GBASE_R_FEC:
    case MTIP_PORT_CONFIG_4x10GBASE_R:
    case MTIP_PORT_CONFIG_4x10GBASE_R_FEC:
        {
            // set all to low
            ff_0_rate = MTIP_ECPRI_FF_CLK_LOW;
            ff_1_rate = MTIP_ECPRI_FF_CLK_LOW;
            ff_2_rate = MTIP_ECPRI_FF_CLK_LOW;
            ff_3_rate = MTIP_ECPRI_FF_CLK_LOW;

            // set hm ref to low
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_LOW;
        }
        break;
        // config 13 is 2x50GBASE_R2 family
    case MTIP_PORT_CONFIG_2x50GBASE_R2:
    case MTIP_PORT_CONFIG_2x50GBASE_R2_FEC:
    case MTIP_PORT_CONFIG_2x50GBASE_R2_LUAI:
    case MTIP_PORT_CONFIG_2x50GBASE_R2_LUAI_FEC:
        {
            // set ff0 and ff1 to medium and rest to off
            ff_0_rate = MTIP_ECPRI_FF_CLK_MED;
            ff_1_rate = MTIP_ECPRI_FF_CLK_MED;
            ff_2_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;
            ff_3_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;

            // set hm ref to high
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_HIGH;
        }
        break;
    default:
        break;
    }

    CSMLOGDBG("Setting fh1 clock[%d] to %ld", ff_0_index, ff_0_rate);
    CSMLOGDBG("Setting fh1 clock[%d] to %ld", ff_1_index, ff_1_rate);
    CSMLOGDBG("Setting fh1 clock[%d] to %ld", ff_2_index, ff_2_rate);
    CSMLOGDBG("Setting fh1 clock[%d] to %ld", ff_3_index, ff_3_rate);
    CSMLOGDBG("Setting fh1 clock[%d] to %ld", hm_ref_index, hm_ref_rate);

    clk_set_rate(ff_0_clock, ff_0_rate);
    clk_set_rate(ff_1_clock, ff_1_rate);
    clk_set_rate(ff_2_clock, ff_2_rate);
    clk_set_rate(ff_3_clock, ff_3_rate);

    clk_set_rate(hm_ref_clock, hm_ref_rate);
}

static void mtip_clocks_set_fh2_clock_rates(enum mtip_port_config_enum port_config)
{
    u32 ff_0_index = 0;
    u32 ff_1_index = 1;
    u32 ff_2_index = 2;
    u32 ff_3_index = 3;
    u32 hm_ref_index = 4;
    unsigned long ff_0_rate = MTIP_ECPRI_FF_CLK_MAX_NOM;
    unsigned long ff_1_rate = MTIP_ECPRI_FF_CLK_MAX_NOM;
    unsigned long ff_2_rate = MTIP_ECPRI_FF_CLK_MAX_NOM;
    unsigned long ff_3_rate = MTIP_ECPRI_FF_CLK_MAX_NOM;
    unsigned long hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_MAX_NOM;

    struct clk* ff_0_clock = platform_driver_priv->clocks.ecpricc_fh2_clocks[ff_0_index];
    struct clk* ff_1_clock = platform_driver_priv->clocks.ecpricc_fh2_clocks[ff_1_index];
    struct clk* ff_2_clock = platform_driver_priv->clocks.ecpricc_fh2_clocks[ff_2_index];
    struct clk* ff_3_clock = platform_driver_priv->clocks.ecpricc_fh2_clocks[ff_3_index];
    struct clk* hm_ref_clock = platform_driver_priv->clocks.ecpricc_fh2_clocks[hm_ref_index];

    switch (port_config) 
    {
        // config 1 is 100GBASE_R family
    case MTIP_PORT_CONFIG_1x100GBASE_R:
    case MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC_LL:
    case MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC:
        // config 2 is 100GBASE_R2 family
    case MTIP_PORT_CONFIG_1x100GBASE_R2:
    case MTIP_PORT_CONFIG_1x100GBASE_R2_RSFEC:
        // config 3 is 100GBASE_R4 family
    case MTIP_PORT_CONFIG_1x100GBASE_R4:
    case MTIP_PORT_CONFIG_1x100GBASE_R4_RSFEC:
        {
            // set ff0 to high and rest to off
            ff_0_rate = MTIP_ECPRI_FF_CLK_HIGH;
            ff_1_rate = MTIP_ECPRI_FF_CLK_HIGH;//MTIP_ECPRI_FF_CLK_OFF;
            ff_2_rate = MTIP_ECPRI_FF_CLK_HIGH;//MTIP_ECPRI_FF_CLK_OFF;
            ff_3_rate = MTIP_ECPRI_FF_CLK_HIGH;//MTIP_ECPRI_FF_CLK_OFF;

            // set hm ref to high
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_HIGH;
        }
        break;
        // config 4 is 1x50GBASE_R2 family
    case MTIP_PORT_CONFIG_1x50GBASE_R2:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_RSFEC:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_LUAI:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_LUAI_FEC:
        {
            // set ff0 to medium and rest to off
            ff_0_rate = MTIP_ECPRI_FF_CLK_MED;
            ff_1_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;
            ff_2_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;
            ff_3_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;

            // set hm ref to high
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_HIGH;
        }
        break;
        // config 5 is 40GBASE_R4 family
    case MTIP_PORT_CONFIG_1x40GBASE_R4:
    case MTIP_PORT_CONFIG_1x40GBASE_R4_FEC:
        {
            // set ff0 to medium and rest to off
            ff_0_rate = MTIP_ECPRI_FF_CLK_MED;
            ff_1_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;
            ff_2_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;
            ff_3_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;

            // set hm ref to medium
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_MED;
        }
        break;
        // config 6 2x50GBASE_R family
    case MTIP_PORT_CONFIG_2x50GBASE_R:
    case MTIP_PORT_CONFIG_2x50GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_1x50GBASE_R:
    case MTIP_PORT_CONFIG_1x50GBASE_R_RSFEC:
        {
            // set ff0 and ff1 to medium and rest to off
            ff_0_rate = MTIP_ECPRI_FF_CLK_MED;
            ff_1_rate = MTIP_ECPRI_FF_CLK_MED;
            ff_2_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;
            ff_3_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;

            // set hm ref to high
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_HIGH;
        }
        break;
        // config 11 is 4x25GBASE_R family
    case MTIP_PORT_CONFIG_1x25GBASE_R:
    case MTIP_PORT_CONFIG_1x25GBASE_R_FEC:
    case MTIP_PORT_CONFIG_4x25GBASE_R:
    case MTIP_PORT_CONFIG_4x25GBASE_R_FEC:
    case MTIP_PORT_CONFIG_1x25GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_4x25GBASE_R_RSFEC:
        {
            // set all to medium
            ff_0_rate = MTIP_ECPRI_FF_CLK_MED;
            ff_1_rate = MTIP_ECPRI_FF_CLK_MED;
            ff_2_rate = MTIP_ECPRI_FF_CLK_MED;
            ff_3_rate = MTIP_ECPRI_FF_CLK_MED;

            // set hm ref to medium
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_MED;
        }
        break;
        // config 12 is 4x10GBASE_R family
    case MTIP_PORT_CONFIG_1x10GBASE_R:
    case MTIP_PORT_CONFIG_1x10GBASE_R_FEC:
    case MTIP_PORT_CONFIG_4x10GBASE_R:
    case MTIP_PORT_CONFIG_4x10GBASE_R_FEC:
        {
            // set all to low
            ff_0_rate = MTIP_ECPRI_FF_CLK_LOW;
            ff_1_rate = MTIP_ECPRI_FF_CLK_LOW;
            ff_2_rate = MTIP_ECPRI_FF_CLK_LOW;
            ff_3_rate = MTIP_ECPRI_FF_CLK_LOW;

            // set hm ref to low
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_LOW;
        }
        break;
        // config 13 is 2x50GBASE_R2 family
    case MTIP_PORT_CONFIG_2x50GBASE_R2:
    case MTIP_PORT_CONFIG_2x50GBASE_R2_FEC:
    case MTIP_PORT_CONFIG_2x50GBASE_R2_LUAI:
    case MTIP_PORT_CONFIG_2x50GBASE_R2_LUAI_FEC:
        {
            // set ff0 and ff1 to medium and rest to off
            ff_0_rate = MTIP_ECPRI_FF_CLK_MED;
            ff_1_rate = MTIP_ECPRI_FF_CLK_MED;
            ff_2_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;
            ff_3_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;

            // set hm ref to high
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_HIGH;
        }
        break;
    default:
        break;
    }

    CSMLOGDBG("Setting fh2 clock[%d] to %ld", ff_0_index, ff_0_rate);
    CSMLOGDBG("Setting fh2 clock[%d] to %ld", ff_1_index, ff_1_rate);
    CSMLOGDBG("Setting fh2 clock[%d] to %ld", ff_2_index, ff_2_rate);
    CSMLOGDBG("Setting fh2 clock[%d] to %ld", ff_3_index, ff_3_rate);
    CSMLOGDBG("Setting fh2 clock[%d] to %ld", hm_ref_index, hm_ref_rate);

    clk_set_rate(ff_0_clock, ff_0_rate);
    clk_set_rate(ff_1_clock, ff_1_rate);
    clk_set_rate(ff_2_clock, ff_2_rate);
    clk_set_rate(ff_3_clock, ff_3_rate);

    clk_set_rate(hm_ref_clock, hm_ref_rate);
}

static void mtip_clocks_set_c2c_clock_rates(enum mtip_port_config_enum port_config)
{
    u32 c2c_ff_0_index = 0;
    u32 c2c_ff_1_index = 1;
    u32 dbg_ff_0_index = 0;
    u32 c2c_hm_ref_index = 2;
    unsigned long c2c_ff_0_rate;
    unsigned long c2c_ff_1_rate;
    unsigned long dbg_ff_0_rate;
    unsigned long c2c_hm_ref_rate;

    struct clk* c2c_ff_0_clock = platform_driver_priv->clocks.ecpricc_c2c_clocks[c2c_ff_0_index];
    struct clk* c2c_ff_1_clock = platform_driver_priv->clocks.ecpricc_c2c_clocks[c2c_ff_1_index];

    struct clk* dbg_ff_0_clock = platform_driver_priv->clocks.ecpricc_dbg_clocks[dbg_ff_0_index];

    struct clk* c2c_hm_ref_clock = platform_driver_priv->clocks.ecpricc_c2c_clocks[c2c_hm_ref_index];

    switch (port_config)
    {
        // config 1 is 100GBASE_R family
    case MTIP_PORT_CONFIG_1x100GBASE_R:
    case MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC_LL:
    case MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC:
        {
            // set ff0 to high and rest to off
            c2c_ff_0_rate = MTIP_ECPRI_FF_CLK_HIGH;
            c2c_ff_1_rate = MTIP_ECPRI_FF_CLK_HIGH;//MTIP_ECPRI_FF_CLK_OFF;
            dbg_ff_0_rate = MTIP_ECPRI_FF_CLK_HIGH;//MTIP_ECPRI_FF_CLK_OFF;

            // set hm ref to high
            c2c_hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_HIGH;
        }
        break;

        // config 2 is 100GBASE_R2 family
    case MTIP_PORT_CONFIG_1x100GBASE_R2:
    case MTIP_PORT_CONFIG_1x100GBASE_R2_RSFEC:
        {
            // set ff0 to high and rest to off
            c2c_ff_0_rate = MTIP_ECPRI_FF_CLK_HIGH;
            c2c_ff_1_rate = MTIP_ECPRI_FF_CLK_HIGH;//MTIP_ECPRI_FF_CLK_OFF;
            dbg_ff_0_rate = MTIP_ECPRI_FF_CLK_HIGH;//MTIP_ECPRI_FF_CLK_OFF;

            // set hm ref to high
            c2c_hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_HIGH;
        }
        break;

        // config 3 is 100GBASE_R4 family
    case MTIP_PORT_CONFIG_1x100GBASE_R4:
    case MTIP_PORT_CONFIG_1x100GBASE_R4_RSFEC:
        {
            // set ff0 to high and rest to off
            c2c_ff_0_rate = MTIP_ECPRI_FF_CLK_HIGH;
            c2c_ff_1_rate = MTIP_ECPRI_FF_CLK_HIGH;//MTIP_ECPRI_FF_CLK_OFF;
            dbg_ff_0_rate = MTIP_ECPRI_FF_CLK_HIGH;//MTIP_ECPRI_FF_CLK_OFF;

            // set hm ref to high
            c2c_hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_HIGH;
        }
        break;

        // config 4 is 50GBASE_R2 family
    case MTIP_PORT_CONFIG_1x50GBASE_R2:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_RSFEC:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_LUAI:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_LUAI_FEC:
    case MTIP_PORT_CONFIG_2x50GBASE_R2:
    case MTIP_PORT_CONFIG_2x50GBASE_R2_FEC:
    case MTIP_PORT_CONFIG_2x50GBASE_R2_LUAI:
    case MTIP_PORT_CONFIG_2x50GBASE_R2_LUAI_FEC:
        {
            // set ff0 to medium and rest to off
            c2c_ff_0_rate = MTIP_ECPRI_FF_CLK_MED;
            c2c_ff_1_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;
            dbg_ff_0_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;

            // set hm ref to high
            c2c_hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_HIGH;
        }
        break;

        // config 6 is 40GBASE_R4 family
    case MTIP_PORT_CONFIG_1x40GBASE_R4:
    case MTIP_PORT_CONFIG_1x40GBASE_R4_FEC:
        {
            // set ff0 to medium and rest to off
            c2c_ff_0_rate = MTIP_ECPRI_FF_CLK_MED;
            c2c_ff_1_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;
            dbg_ff_0_rate = MTIP_ECPRI_FF_CLK_MED;//MTIP_ECPRI_FF_CLK_OFF;

            // set hm ref to medium
            c2c_hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_MED;
        }
        break;

    case MTIP_PORT_CONFIG_1x50GBASE_R:
    case MTIP_PORT_CONFIG_1x50GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_2x50GBASE_R:
    case MTIP_PORT_CONFIG_2x50GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_1x25GBASE_R:
    case MTIP_PORT_CONFIG_1x25GBASE_R_FEC:
    case MTIP_PORT_CONFIG_4x25GBASE_R:
    case MTIP_PORT_CONFIG_4x25GBASE_R_FEC:
    case MTIP_PORT_CONFIG_1x25GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_4x25GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_1x10GBASE_R:
    case MTIP_PORT_CONFIG_1x10GBASE_R_FEC:
    case MTIP_PORT_CONFIG_4x10GBASE_R:
    case MTIP_PORT_CONFIG_4x10GBASE_R_FEC:
    default:
        {
            CSMLOGDBG("Not changing clock rate... leaving as default");
            c2c_ff_0_rate = MTIP_ECPRI_FF_CLK_MAX_NOM;
            c2c_ff_1_rate = MTIP_ECPRI_FF_CLK_MAX_NOM;
            dbg_ff_0_rate = MTIP_ECPRI_FF_CLK_MAX_NOM;

            c2c_hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_MAX_NOM;
        }
        break;
    }

    CSMLOGDBG("Setting c2c clock[%d] to %ld", c2c_ff_0_index, c2c_ff_0_rate);
    CSMLOGDBG("Setting c2c clock[%d] to %ld", c2c_ff_1_index, c2c_ff_1_rate);
    CSMLOGDBG("Setting dbg clock[%d] to %ld", dbg_ff_0_index, dbg_ff_0_rate);
    CSMLOGDBG("Setting c2c clock[%d] to %ld", c2c_hm_ref_index, c2c_hm_ref_rate);

    clk_set_rate(c2c_ff_0_clock, c2c_ff_0_rate);
    clk_set_rate(c2c_ff_1_clock, c2c_ff_1_rate);
    clk_set_rate(dbg_ff_0_clock, dbg_ff_0_rate);

    clk_set_rate(c2c_hm_ref_clock, c2c_hm_ref_rate);
}

static void mtip_clocks_set_dbg_clock_rates(enum mtip_port_config_enum port_config)
{
    u32 ff_1_index = 1;
    u32 hm_ref_index = 2;
    unsigned long ff_1_rate;
    unsigned long hm_ref_rate;

    struct clk* ff_1_clock = platform_driver_priv->clocks.ecpricc_dbg_clocks[ff_1_index];
    struct clk* hm_ref_clock = platform_driver_priv->clocks.ecpricc_dbg_clocks[hm_ref_index];

    switch (port_config) 
    {
        // config 1 is 100GBASE_R family
    case MTIP_PORT_CONFIG_1x100GBASE_R:
    case MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC_LL:
    case MTIP_PORT_CONFIG_1x100GBASE_R_RSFEC:
        {
            // set ff1 to high
            ff_1_rate = MTIP_ECPRI_FF_CLK_HIGH;

            // set hm ref to high
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_HIGH;
        }
        break;

        // config 2 is 100GBASE_R2 family
    case MTIP_PORT_CONFIG_1x100GBASE_R2:
    case MTIP_PORT_CONFIG_1x100GBASE_R2_RSFEC:
        {
            // set ff1 to high
            ff_1_rate = MTIP_ECPRI_FF_CLK_HIGH;

            // set hm ref to high
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_HIGH;
        }
        break;

        // config 3 is 50GBASE_R2 family
    case MTIP_PORT_CONFIG_1x50GBASE_R2:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_RSFEC:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_LUAI:
    case MTIP_PORT_CONFIG_1x50GBASE_R2_LUAI_FEC:
        {
            // set ff1 to medium
            ff_1_rate = MTIP_ECPRI_FF_CLK_MED;

            // set hm ref to high
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_HIGH;
        }
        break;

        // config 4 is 20GBASE_R2 family: NOT SUPPORTED
        // config 5 is 25GBASE_R family
    case MTIP_PORT_CONFIG_1x25GBASE_R:
    case MTIP_PORT_CONFIG_1x25GBASE_R_FEC:
    case MTIP_PORT_CONFIG_4x25GBASE_R:
    case MTIP_PORT_CONFIG_4x25GBASE_R_FEC:
    case MTIP_PORT_CONFIG_1x25GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_4x25GBASE_R_RSFEC:
        {
            // set ff1 to medium
            ff_1_rate = MTIP_ECPRI_FF_CLK_MED;

            // set hm ref to medium
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_MED;
        }
        break;

        // config 6 is 50GBASE_R family
    case MTIP_PORT_CONFIG_1x50GBASE_R:
    case MTIP_PORT_CONFIG_1x50GBASE_R_RSFEC:
    case MTIP_PORT_CONFIG_2x50GBASE_R:
    case MTIP_PORT_CONFIG_2x50GBASE_R_RSFEC:
        {
            // set ff1 to medium
            ff_1_rate = MTIP_ECPRI_FF_CLK_MED;

            // set hm ref to high
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_HIGH;
        }
        break;

        // config 7 is 10GBASE_R family
    case MTIP_PORT_CONFIG_1x10GBASE_R:
    case MTIP_PORT_CONFIG_1x10GBASE_R_FEC:
    case MTIP_PORT_CONFIG_4x10GBASE_R:
    case MTIP_PORT_CONFIG_4x10GBASE_R_FEC:
        {
            // set ff1 to low
            ff_1_rate = MTIP_ECPRI_FF_CLK_LOW;

            // set hm ref to low
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_LOW;
        }
        break;

    case MTIP_PORT_CONFIG_1x100GBASE_R4:
    case MTIP_PORT_CONFIG_1x100GBASE_R4_RSFEC:
    case MTIP_PORT_CONFIG_2x50GBASE_R2:
    case MTIP_PORT_CONFIG_2x50GBASE_R2_FEC:
    case MTIP_PORT_CONFIG_2x50GBASE_R2_LUAI:
    case MTIP_PORT_CONFIG_2x50GBASE_R2_LUAI_FEC:
    case MTIP_PORT_CONFIG_1x40GBASE_R4:
    case MTIP_PORT_CONFIG_1x40GBASE_R4_FEC:
    default:
        {
            CSMLOGDBG("Not changing clock rate.. leaving at default");
            ff_1_rate = MTIP_ECPRI_FF_CLK_MAX_NOM;
            hm_ref_rate = MTIP_ECPRI_MAC_HM_REF_CLK_MAX_NOM;
        }
        break;
    }

    CSMLOGDBG("Setting dbg clock[%d] to %ld", ff_1_index, ff_1_rate);
    CSMLOGDBG("Setting dbg clock[%d] to %ld", hm_ref_index, hm_ref_rate);

    clk_set_rate(ff_1_clock, ff_1_rate);

    clk_set_rate(hm_ref_clock, hm_ref_rate);
}

/**
 * mtip_clocks_set_clock_rates 
 * Set the clock rates for the port based on port config 
 * Most of the clocks are unchanged 
 * Only ff_0, ff_1, ff_2, ff_3, hm_ref have to set according to 
 * port configuration 
 */
void mtip_clocks_set_clock_rates(enum mtip_port_type_enum port_type, enum mtip_port_config_enum port_config)
{
    CSMLOGDBG("Setting clock rates for port %d with port config %d str %s", port_type, port_config, mtip_ethtool_get_port_config_str(port_config));

    switch (port_type) 
    {
    case MTIP_PORT_TYPE_FH_0:
        {
            mtip_clocks_set_fh0_clock_rates(port_config);
        }
        break;
    case MTIP_PORT_TYPE_FH_1:
        {
            mtip_clocks_set_fh1_clock_rates(port_config);
        }
        break;
    case MTIP_PORT_TYPE_FH_2:
        {
            mtip_clocks_set_fh2_clock_rates(port_config);
        }
        break;
    case MTIP_PORT_TYPE_L2:
        {
            mtip_clocks_set_c2c_clock_rates(port_config);
        }
        break;
    case MTIP_PORT_TYPE_DEBUG:
        {
            mtip_clocks_set_dbg_clock_rates(port_config);
        }
        break;
    default:
        {
            CSMLOGERR("Unknown port type %d", port_type);
        }
        break;
    }
}
