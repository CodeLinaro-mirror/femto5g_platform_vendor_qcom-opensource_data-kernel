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

    CSMLOGINFO("setting up GCC clocks\n");

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

    return ret;
}

static int mtip_clocks_setup_c2c_clocks(void)
{
    int ret;
    u32 index = 0;
    struct clk* pclk;
    struct device *dev = &platform_driver_priv->devices.root_pdev->dev;

    CSMLOGINFO("setting up C2C clocks\n");

    // enable C2C clocks
    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_C2C_0_HM_FF_0_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_C2C_0_HM_FF_0_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_ECPRI_FF_CLK_MAX_NOM);
    }
    platform_driver_priv->clocks.ecpricc_c2c_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_C2C_0_HM_FF_1_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_C2C_0_HM_FF_1_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_ECPRI_FF_CLK_MAX_NOM);
    }
    platform_driver_priv->clocks.ecpricc_c2c_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_MAC_C2C_HM_REF_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_MAC_C2C_HM_REF_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_ECPRI_MAC_HM_REF_CLK_MAX_NOM);
    }
    platform_driver_priv->clocks.ecpricc_c2c_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_C2C_HM_FF_0_DIV_CLK_SRC", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_C2C_HM_FF_0_DIV_CLK_SRC\n");
    }
    else
    {
        platform_driver_priv->clocks.ecpricc_c2c_clocks[index] = pclk;
    }
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_C2C_HM_FF_1_DIV_CLK_SRC", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_C2C_HM_FF_1_DIV_CLK_SRC\n");
    }
    platform_driver_priv->clocks.ecpricc_c2c_clocks[index] = pclk;
    ++index;

    return ret;
}

static int mtip_clocks_setup_dbg_clocks(void)
{
    int ret;
    u32 index = 0;
    struct clk* pclk;
    struct device *dev = &platform_driver_priv->devices.root_pdev->dev;

    CSMLOGINFO("setting up DBG clocks\n");

    // enable DBG clocks
    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_DBG_C2C_HM_FF_0_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_DBG_C2C_HM_FF_0_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_ECPRI_FF_CLK_MAX_NOM);
    }
    platform_driver_priv->clocks.ecpricc_dbg_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_DBG_C2C_HM_FF_1_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_DBG_C2C_HM_FF_1_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_ECPRI_FF_CLK_MAX_NOM);
    }
    platform_driver_priv->clocks.ecpricc_dbg_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_MAC_DBG_C2C_HM_REF_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_MAC_DBG_C2C_HM_REF_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_ECPRI_MAC_HM_REF_CLK_MAX_NOM);
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
    platform_driver_priv->clocks.ecpricc_dbg_clocks[index] = pclk;
    ++index;

    return ret;
}

static int mtip_clocks_setup_fh0_clocks(void)
{
    int ret;
    u32 index = 0;
    struct clk* pclk;
    struct device *dev = &platform_driver_priv->devices.root_pdev->dev;

    CSMLOGINFO("setting up FH0 clocks\n");

    // enable FH0 clocks
    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_0_HM_FF_0_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_0_HM_FF_0_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_ECPRI_FF_CLK_MAX_NOM);
    }
    platform_driver_priv->clocks.ecpricc_fh0_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_0_HM_FF_1_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_0_HM_FF_1_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_ECPRI_FF_CLK_MAX_NOM);
    }
    platform_driver_priv->clocks.ecpricc_fh0_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_0_HM_FF_2_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_0_HM_FF_2_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_ECPRI_FF_CLK_MAX_NOM);
    }
    platform_driver_priv->clocks.ecpricc_fh0_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_0_HM_FF_3_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_0_HM_FF_3_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_ECPRI_FF_CLK_MAX_NOM);
    }
    platform_driver_priv->clocks.ecpricc_fh0_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_MAC_FH0_HM_REF_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_MAC_FH0_HM_REF_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_ECPRI_MAC_HM_REF_CLK_MAX_NOM);
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

    return ret;
}

static int mtip_clocks_setup_fh1_clocks(void)
{
    int ret;
    u32 index = 0;
    struct clk* pclk;
    struct device *dev = &platform_driver_priv->devices.root_pdev->dev;

    CSMLOGINFO("setting up FH1 clocks\n");

    // enable FH1 clocks
    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_1_HM_FF_0_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_1_HM_FF_0_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_ECPRI_FF_CLK_MAX_NOM);
    }
    platform_driver_priv->clocks.ecpricc_fh1_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_1_HM_FF_1_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_1_HM_FF_1_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_ECPRI_FF_CLK_MAX_NOM);
    }
    platform_driver_priv->clocks.ecpricc_fh1_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_1_HM_FF_2_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_1_HM_FF_2_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_ECPRI_FF_CLK_MAX_NOM);
    }
    platform_driver_priv->clocks.ecpricc_fh1_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_1_HM_FF_3_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_1_HM_FF_3_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_ECPRI_FF_CLK_MAX_NOM);
    }
    platform_driver_priv->clocks.ecpricc_fh1_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_MAC_FH1_HM_REF_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_MAC_FH1_HM_REF_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_ECPRI_MAC_HM_REF_CLK_MAX_NOM);
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

    return ret;
}

static int mtip_clocks_setup_fh2_clocks(void)
{
    int ret;
    u32 index = 0;
    struct clk* pclk;
    struct device *dev = &platform_driver_priv->devices.root_pdev->dev;

    CSMLOGINFO("setting up FH2 clocks\n");

    // enable FH1 clocks
    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_2_HM_FF_0_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_2_HM_FF_0_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_ECPRI_FF_CLK_MAX_NOM);
    }
    platform_driver_priv->clocks.ecpricc_fh2_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_2_HM_FF_1_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_2_HM_FF_1_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_ECPRI_FF_CLK_MAX_NOM);
    }
    platform_driver_priv->clocks.ecpricc_fh2_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_2_HM_FF_2_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_2_HM_FF_2_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_ECPRI_FF_CLK_MAX_NOM);
    }
    platform_driver_priv->clocks.ecpricc_fh2_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_FH_2_HM_FF_3_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_FH_2_HM_FF_3_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_ECPRI_FF_CLK_MAX_NOM);
    }
    platform_driver_priv->clocks.ecpricc_fh2_clocks[index] = pclk;
    ++index;

    ret = mtip_clocks_enable_clock(dev, "ECPRI_CC_MAC_FH2_HM_REF_CLK", &pclk);
    if (ret)
    {
        CSMLOGERR("Failed to vote ECPRI_CC_MAC_FH2_HM_REF_CLK\n");
    }
    else
    {
        clk_set_rate(pclk, MTIP_ECPRI_MAC_HM_REF_CLK_MAX_NOM);
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

    return ret;
}

/*
 * mtip_clocks_setup_clocks
 */
void mtip_clocks_setup_clocks(void)
{
    CSMLOGINFO("MTIP started getting clocks\n");

    mtip_clocks_setup_gcc_clocks();

    mtip_clocks_setup_c2c_clocks();

    mtip_clocks_setup_dbg_clocks();

    mtip_clocks_setup_fh0_clocks();

    mtip_clocks_setup_fh1_clocks();

    mtip_clocks_setup_fh2_clocks();

    return;
}

