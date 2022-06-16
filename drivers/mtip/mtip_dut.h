//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#ifndef _MTIP_DUT_H
#define _MTIP_DUT_H

#include <linux/slab.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/phylink.h>

// RGMII IO Macro register offsets
#define MTIP_RGMII_IO_MACRO_CFG_REG_OFFSET        0x110
#define MTIP_RGMII_IO_MACRO_CFG_REG_MAC_OFFSET    0x30

// RGMII IO Macro register values
#define MTIP_RGMII_IO_MACRO_CFG_VAL               0xC3
#define MTIP_RGMII_IO_MACRO_LOOPBACK_VAL          0x20C7

// TX delay tuning 
#define MTIP_TX_DELAY_CTL_REG_OFFSET  0x108

#define MTIP_TXC_DELAY_CNT_VAL_IN_ADDR_SHIFT         16
#define MTIP_TXC_DELAY_CNT_VAL_IN_ADDR_MASK          GENMASK(20, 16)
#define MTIP_TXC_DELAY_LD_ADDR_SHIFT                 21
#define MTIP_TXC_DELAY_CNT_VAL_OUT_ADDR_SHIFT        24
#define MTIP_TXC_DELAY_CNT_VAL_OUT_ADDR_MASK         GENMASK(28, 24)

#define MTIP_TXD_DELAY_CNT_VAL_IN_ADDR_MASK          GENMASK(4, 0)
#define MTIP_TXD_DELAY_LD_ADDR_SHIFT                 5
#define MTIP_TXD_DELAY_CNT_VAL_OUT_ADDR_SHIFT        8
#define MTIP_TXD_DELAY_CNT_VAL_OUT_ADDR_MASK         GENMASK(15, 8)


// RX delay tuning
#define MTIP_RX_CLK_PS_MMCM_CFG_REG_OFFSET           0x1C0
#define MTIP_RX_CLK_PS_MMCM_MAC_OFFSET               0x10
#define MTIP_RX_CLK_PS_MMCM_CFG_RESET_ADDR_SHIFT     20
#define MTIP_RX_CLK_PS_MMCM_CFG_TAP_ADDR_MASK        GENMASK(15, 0)

// Emulation DUT reset register offset
#define MTIP_MAC_FH0_EMULATION_RESET_REG          0x00000004

// Emulation DUT reset value to be written
#define MTIP_MAC_FH0_EMULATION_RESET_VAL          0x000001FF

// default delay values
#define TX_DELAY_DEFAULT_VAL      -1
#define RX_DELAY_DEFAULT_VAL      -1

int mtip_dut_get_tx_delay(int index);
int mtip_dut_get_rx_delay(int index);

void __iomem * mtip_dut_get_base_addr(u32 port_number);

void mtip_dut_reset(void __iomem *addr);
void mtip_dut_rx_tx_delay_tuning(u32 link_index);

void mtip_dut_iomacro_config(struct phylink_config *config,
                     unsigned int mode,
                     const struct phylink_link_state *state);
void mtip_dut_enable_rgmii_loopback(u32 link_index);

#endif // _MTIP_DUT_H
