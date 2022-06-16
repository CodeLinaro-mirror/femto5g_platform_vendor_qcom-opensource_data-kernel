//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#ifndef _MTIP_CLOCKS_H
#define _MTIP_CLOCKS_H

#include <linux/slab.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/phylink.h>
#include <linux/clk.h>

#define MTIP_CLK_FREQ(x) (x * 1000 * 1000UL)

/* MTIP clocks */
#define MTIP_GCC_APB_CLK_MAX_NOM (MTIP_CLK_FREQ(100))
#define MTIP_GCC_SNOC_AXI_CLK_MAX_NOM (MTIP_CLK_FREQ(200))
#define MTIP_ECPRI_FF_CLK_MAX_NOM (MTIP_CLK_FREQ(466.5))
#define MTIP_ECPRI_MAC_HM_REF_CLK_MAX_NOM (MTIP_CLK_FREQ(806))

#define MTIP_CLOCKS_NUM_GCC_CLOCKS                 6
#define MTIP_CLOCKS_NUM_ECPRICC_C2C_CLOCKS         5
#define MTIP_CLOCKS_NUM_ECPRICC_DBG_CLOCKS         5
#define MTIP_CLOCKS_NUM_ECPRICC_FH_CLOCKS          9

struct mtip_clocks_clock_struct
{
    struct clk* gcc_clocks[MTIP_CLOCKS_NUM_GCC_CLOCKS];
    struct clk* ecpricc_c2c_clocks[MTIP_CLOCKS_NUM_ECPRICC_C2C_CLOCKS];
    struct clk* ecpricc_dbg_clocks[MTIP_CLOCKS_NUM_ECPRICC_DBG_CLOCKS];
    struct clk* ecpricc_fh0_clocks[MTIP_CLOCKS_NUM_ECPRICC_FH_CLOCKS];
    struct clk* ecpricc_fh1_clocks[MTIP_CLOCKS_NUM_ECPRICC_FH_CLOCKS];
    struct clk* ecpricc_fh2_clocks[MTIP_CLOCKS_NUM_ECPRICC_FH_CLOCKS];
};

void mtip_clocks_setup_clocks(void);

#endif // _MTIP_CLOCKS_H
