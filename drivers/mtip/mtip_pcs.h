//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#ifndef _MTIP_PCS_H
#define _MTIP_PCS_H

#include <linux/slab.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/phylink.h>

#include "mtip.h"

// PCS register offsets
#define MTIP_PCS_CONTROL_REG_OFFSET             0x00000000
#define MTIP_PCS_VENDOR_PCS_MODE_OFFSET         0x00020040
#define MTIP_PCS_VENDOR_VL_INTVL_OFFSET         0x00020008

#define MTIP_PCS_VENDOR_VL0_0_OFFSET            0x00020020
#define MTIP_PCS_VENDOR_VL0_1_OFFSET            0x00020024
#define MTIP_PCS_VENDOR_VLn_OFFSET              0x00000008

#define MTIP_PCS_VL0_0_OFFSET                   0x00020100
#define MTIP_PCS_VL0_1_OFFSET                   0x00020104
#define MTIP_PCS_VLn_OFFSET                     0x00000008


// PCS register values
#define MTIP_PCS_LOOPBACK_CONTROL_BIT           0x00004000
#define MTIP_PCS_RESET_CONTROL_BIT              0x00008000

#define MTIP_PCS_VENDOR_PCS_ENA_CLAUSE49_BIT    0x00000001
#define MTIP_PCS_VENDOR_PCS_DISABLE_MLD_BIT     0x00000002
#define MTIP_PCS_VENDOR_PCS_HI_BER25_BIT        0x00000004
#define MTIP_PCS_VENDOR_PCS_HI_BER5_BIT         0x00000008
#define MTIP_PCS_VENDOR_PCS_ST_ENA_CLAUSE49_BIT 0x00000100
#define MTIP_PCS_VENDOR_PCS_ST_DISABLE_MLD_BIT  0x00000200

// RSFEC register offsets
#define MTIP_RSFEC_CONTROL_OFFSET               0x00000000
#define MTIP_RSFEC_DEC_THRESH_OFFSET            0x0000001C
#define MTIP_RSFEC_DEC_THRESH_4X25G_VAL         0x00000033
#define MTIP_RSFEC_DEC_THRESH_POR_VAL           0x00000019


#define MTIP_RSFEC_LINK_OFFSET                  0x00000020

// RSFEC register values
#define MTIP_RSFEC_CONTROL_BYPASS_CORRECTION_BIT 0x00000001
#define MTIP_RSFEC_CONTROL_BYPASS_ERROR_BIT      0x00000002
#define MTIP_RSFEC_CONTROL_DEGRADE_ENABLE_BIT    0x00000004
#define MTIP_RSFEC_CONTROL_AM16_COPY_DIS_BIT     0x00000008
#define MTIP_RSFEC_CONTROL_KP_ENABLE_BIT         0x00000100
#define MTIP_RSFEC_CONTROL_TC_PAD_VALUE_BIT      0x00000200
#define MTIP_RSFEC_CONTROL_TC_PAD_ALTER_BIT      0x00000400
#define MTIP_RSFEC_CONTROL_LL_MODE_BIT           0x00000800
#define MTIP_RSFEC_CONTROL_CK_MODE_BIT           0x00001000

/*
 * Other configuration items
 */
#define MTIP_PCS_RESET_DELAY_MSECS                10

int mtip_pcs_config_pcs(u32 link_index);

int mtip_pcs_enable_loopback(u32 link_index);

int mtip_rsfec_initialize(struct mtip_port_device_info* port_device);

// functions to enable/disable rsfec for 25g mode
void mtip_pcs_enable_rsfec_for_25g_mode(struct mtip_link_device_info* link_device);
void mtip_pcs_disable_rsfec_for_25g_mode(struct mtip_link_device_info* link_device);

void mtip_pcs_update_active_fec(u32 link_index,
                                            enum mtip_port_config_enum port_config,
                                            u32  sfp_port_type);

#endif // _MTIP_PCS_H
