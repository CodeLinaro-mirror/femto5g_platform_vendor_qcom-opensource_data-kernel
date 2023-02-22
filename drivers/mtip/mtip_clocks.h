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

#include "eth_phy_iface.h"

#define MTIP_CLK_FREQ(x) (x * 1000 * 1000UL)

/* Fixed frequency MTIP clocks */
#define MTIP_GCC_APB_CLK_MAX_NOM (MTIP_CLK_FREQ(100))
#define MTIP_GCC_SNOC_AXI_CLK_MAX_NOM (MTIP_CLK_FREQ(200))
#define MTIP_ECPRI_MSS_EMAC_REF_CLK_MAX_NOM (MTIP_CLK_FREQ(403))
#define MTIP_ECPRI_ETH_DBG_NOC_REF_CLK_MAX_NOM (MTIP_CLK_FREQ(403))

/* Variable frequency MTIP clocks */
#define MTIP_ECPRI_FF_CLK_HIGH (MTIP_CLK_FREQ(466))
#define MTIP_ECPRI_FF_CLK_MED (MTIP_CLK_FREQ(402))
#define MTIP_ECPRI_FF_CLK_LOW (MTIP_CLK_FREQ(201))
#define MTIP_ECPRI_FF_CLK_OFF (MTIP_CLK_FREQ(0))

#define MTIP_ECPRI_FF_CLK_MAX_NOM MTIP_ECPRI_FF_CLK_MED

#define MTIP_ECPRI_MAC_HM_REF_CLK_HIGH (MTIP_CLK_FREQ(805))
#define MTIP_ECPRI_MAC_HM_REF_CLK_MED (MTIP_CLK_FREQ(699))
#define MTIP_ECPRI_MAC_HM_REF_CLK_LOW (MTIP_CLK_FREQ(533))

#define MTIP_ECPRI_MAC_HM_REF_CLK_MAX_NOM MTIP_ECPRI_MAC_HM_REF_CLK_MED

#define MTIP_CLOCKS_NUM_GCC_CLOCKS                 6
#define MTIP_CLOCKS_NUM_ECPRICC_C2C_CLOCKS         5
#define MTIP_CLOCKS_NUM_ECPRICC_DBG_CLOCKS         7
#define MTIP_CLOCKS_NUM_ECPRICC_FH_CLOCKS          9

enum mtip_port_config_enum;

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

void mtip_clocks_set_clock_rates(enum mtip_port_type_enum port_type, enum mtip_port_config_enum port_config);

#endif // _MTIP_CLOCKS_H
