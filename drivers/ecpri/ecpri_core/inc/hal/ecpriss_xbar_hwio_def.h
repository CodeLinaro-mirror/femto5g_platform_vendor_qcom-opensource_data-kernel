/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef __ECPRI_XBAR_HWIO_DEF_H__
#define __ECPRI_XBAR_HWIO_DEF_H__
/**
  @file ecpri_xbar_hwio.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
  ECPRI_XBAR.*

  'Include' filters applied: <none>
  'Exclude' filters applied: RESERVED DUMMY
  */
/*----------------------------------------------------------------------------
 * MODULE: ECPRI_XBAR
 *--------------------------------------------------------------------------*/
#include <linux/types.h>

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_CFG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t fhrx_cnt_en : 1;
	uint32_t fhtx_cnt_en : 1;
	uint32_t ocrx_cnt_en : 1;
	uint32_t octx_cnt_en : 1;
	uint32_t c2crx_cnt_en : 1;
	uint32_t c2ctx_cnt_en : 1;
	uint32_t xbar_cnt_en : 1;
	uint32_t xbar_cnt_clr_en : 1;
	uint32_t tpdm_en : 1;
	uint32_t reserved0 : 23;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_cfg_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_cfg_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_cfg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_IPG_CFG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t oc_sop_ipg : 8;
	uint32_t dma_sop_ipg : 8;
	uint32_t oc_eop_ipg : 8;
	uint32_t dma_eop_ipg : 8;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_ipg_cfg_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_ipg_cfg_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_ipg_cfg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_IPG_CFG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t oc_sop_ipg : 8;
	uint32_t dma_sop_ipg : 8;
	uint32_t oc_eop_ipg : 8;
	uint32_t dma_eop_ipg : 8;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_ipg_cfg_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_ipg_cfg_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_ipg_cfg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_CFG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t fh_prio : 2;
	uint32_t oran_prio : 2;
	uint32_t dma_prio : 2;
	uint32_t dma_dst_port : 2;
	uint32_t reserved0 : 24;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_cfg_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_cfg_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_cfg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_CFG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t c2c_prio : 2;
	uint32_t oran_prio : 2;
	uint32_t uc_prio : 2;
	uint32_t dma_prio : 2;
	uint32_t reserved0 : 24;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_cfg_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_cfg_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_cfg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_OC_CFG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t octx_len_chk_enable : 1;
	uint32_t octx_len_chk_drop : 1;
	uint32_t octx_dynamic_prio_en : 1;
	uint32_t ocrx_output_threshold : 6;
	uint32_t reserved0 : 2;
	uint32_t ocrx_async_threshold : 3;
	uint32_t reserved1 : 18;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oc_cfg_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oc_cfg_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oc_cfg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_OC_LOOPBACK_CFG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t octx_0_src : 2;
	uint32_t octx_1_src : 2;
	uint32_t octx_2_src : 2;
	uint32_t octx_3_src : 2;
	uint32_t reserved0 : 24;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oc_loopback_cfg_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oc_loopback_cfg_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oc_loopback_cfg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FLUSH
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t flush_fh_0_tx : 1;
	uint32_t flush_fh_0_rx : 1;
	uint32_t flush_fh_1_tx : 1;
	uint32_t flush_fh_1_rx : 1;
	uint32_t flush_fh_2_tx : 1;
	uint32_t flush_fh_2_rx : 1;
	uint32_t reserved0 : 1;
	uint32_t flush_c2c_0_tx : 1;
	uint32_t flush_c2c_0_rx : 1;
	uint32_t flush_c2c_1_tx : 1;
	uint32_t flush_c2c_1_rx : 1;
	uint32_t flush_c2c_2_tx : 1;
	uint32_t flush_c2c_2_rx : 1;
	uint32_t reserved1 : 3;
	uint32_t flush_oc_0_tx : 1;
	uint32_t flush_oc_0_rx : 1;
	uint32_t flush_oc_1_tx : 1;
	uint32_t flush_oc_1_rx : 1;
	uint32_t flush_oc_2_tx : 1;
	uint32_t flush_oc_2_rx : 1;
	uint32_t flush_oc_3_tx : 1;
	uint32_t flush_oc_3_rx : 1;
	uint32_t reserved2 : 8;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_flush_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_flush_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_flush_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_STATUS
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t tx_c2c_overflow : 3;
	uint32_t reserved0 : 29;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_status_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_status_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_status_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_STATUS
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t tx_fh_overflow : 3;
	uint32_t reserved0 : 29;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_status_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_status_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_status_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_OCTX_STATUS
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t tx_fh_drop : 3;
	uint32_t tx_c2c_drop : 3;
	uint32_t tx_fh_overflow : 3;
	uint32_t tx_c2c_overflow : 3;
	uint32_t tx_fh_len_err : 3;
	uint32_t tx_c2c_len_err : 3;
	uint32_t reserved0 : 14;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_octx_status_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_octx_status_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_octx_status_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_LUT_STATUS
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t fhrx_lut_init_done : 3;
	uint32_t c2crx_dl_lut_init_done : 3;
	uint32_t c2crx_ul_lut_init_done : 3;
	uint32_t ocrx_lut_init_done : 3;
	uint32_t reserved0 : 20;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_lut_status_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_lut_status_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_lut_status_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FW_IRQ_STATUS
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t octx_fh_len_err : 1;
	uint32_t octx_c2c_len_err : 1;
	uint32_t reserved0 : 1;
	uint32_t fhtx_c2c_overflow : 1;
	uint32_t c2ctx_fh_overflow : 1;
	uint32_t octx_fh_overflow : 1;
	uint32_t octx_c2c_overflow : 1;
	uint32_t fhrx_uc_pkt_pending : 1;
	uint32_t fhrx_uc_overflow : 1;
	uint32_t fhrx_uc_pkt_err : 1;
	uint32_t fhrx_uc_pkt_drop : 1;
	uint32_t ocrx_unknown_pcid : 1;
	uint32_t fhrx_unknown_pcid : 1;
	uint32_t c2crx_unknown_pcid : 1;
	uint32_t reserved1 : 18;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fw_irq_status_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fw_irq_status_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fw_irq_status_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FW_IRQ_MASK
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t octx_fh_len_err : 1;
	uint32_t octx_c2c_len_err : 1;
	uint32_t reserved0 : 1;
	uint32_t fhtx_c2c_overflow : 1;
	uint32_t c2ctx_fh_overflow : 1;
	uint32_t octx_fh_overflow : 1;
	uint32_t octx_c2c_overflow : 1;
	uint32_t fhrx_uc_pkt_pending : 1;
	uint32_t fhrx_uc_overflow : 1;
	uint32_t fhrx_uc_pkt_err : 1;
	uint32_t fhrx_uc_pkt_drop : 1;
	uint32_t ocrx_unknown_pcid : 1;
	uint32_t fhrx_unknown_pcid : 1;
	uint32_t c2crx_unknown_pcid : 1;
	uint32_t reserved1 : 18;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fw_irq_mask_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fw_irq_mask_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fw_irq_mask_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FW_IRQ_CLR
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t octx_fh_len_err : 1;
	uint32_t octx_c2c_len_err : 1;
	uint32_t reserved0 : 1;
	uint32_t fhtx_c2c_overflow : 1;
	uint32_t c2ctx_fh_overflow : 1;
	uint32_t octx_fh_overflow : 1;
	uint32_t octx_c2c_overflow : 1;
	uint32_t fhrx_uc_pkt_pending : 1;
	uint32_t fhrx_uc_overflow : 1;
	uint32_t fhrx_uc_pkt_err : 1;
	uint32_t fhrx_uc_pkt_drop : 1;
	uint32_t ocrx_unknown_pcid : 1;
	uint32_t fhrx_unknown_pcid : 1;
	uint32_t c2crx_unknown_pcid : 1;
	uint32_t reserved1 : 18;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fw_irq_clr_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fw_irq_clr_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fw_irq_clr_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_SW_IRQ_STATUS
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t octx_fh_len_err : 1;
	uint32_t octx_c2c_len_err : 1;
	uint32_t reserved0 : 1;
	uint32_t fhtx_c2c_overflow : 1;
	uint32_t c2ctx_fh_overflow : 1;
	uint32_t octx_fh_overflow : 1;
	uint32_t octx_c2c_overflow : 1;
	uint32_t fhrx_uc_pkt_pending : 1;
	uint32_t fhrx_uc_overflow : 1;
	uint32_t fhrx_uc_pkt_err : 1;
	uint32_t fhrx_uc_pkt_drop : 1;
	uint32_t ocrx_unknown_pcid : 1;
	uint32_t fhrx_unknown_pcid : 1;
	uint32_t c2crx_unknown_pcid : 1;
	uint32_t reserved1 : 18;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_sw_irq_status_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_sw_irq_status_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_sw_irq_status_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_SW_IRQ_MASK
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t octx_fh_len_err : 1;
	uint32_t octx_c2c_len_err : 1;
	uint32_t reserved0 : 1;
	uint32_t fhtx_c2c_overflow : 1;
	uint32_t c2ctx_fh_overflow : 1;
	uint32_t octx_fh_overflow : 1;
	uint32_t octx_c2c_overflow : 1;
	uint32_t fhrx_uc_pkt_pending : 1;
	uint32_t fhrx_uc_overflow : 1;
	uint32_t fhrx_uc_pkt_err : 1;
	uint32_t fhrx_uc_pkt_drop : 1;
	uint32_t ocrx_unknown_pcid : 1;
	uint32_t fhrx_unknown_pcid : 1;
	uint32_t c2crx_unknown_pcid : 1;
	uint32_t reserved1 : 18;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_sw_irq_mask_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_sw_irq_mask_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_sw_irq_mask_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_SW_IRQ_CLR
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t octx_fh_len_err : 1;
	uint32_t octx_c2c_len_err : 1;
	uint32_t reserved0 : 1;
	uint32_t fhtx_c2c_overflow : 1;
	uint32_t c2ctx_fh_overflow : 1;
	uint32_t octx_fh_overflow : 1;
	uint32_t octx_c2c_overflow : 1;
	uint32_t fhrx_uc_pkt_pending : 1;
	uint32_t fhrx_uc_overflow : 1;
	uint32_t fhrx_uc_pkt_err : 1;
	uint32_t fhrx_uc_pkt_drop : 1;
	uint32_t ocrx_unknown_pcid : 1;
	uint32_t fhrx_unknown_pcid : 1;
	uint32_t c2crx_unknown_pcid : 1;
	uint32_t reserved1 : 18;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_sw_irq_clr_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_sw_irq_clr_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_sw_irq_clr_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_IDLE_1
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t xbar_is_idle : 1;
	uint32_t fh_is_idle : 1;
	uint32_t c2c_is_idle : 1;
	uint32_t oran_is_idle : 1;
	uint32_t reserved0 : 28;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_idle_1_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_idle_1_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_idle_1_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_IDLE_2
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t ocrx_oran_is_idle : 4;
	uint32_t ocrx_fh_is_idle : 3;
	uint32_t ocrx_c2c_is_idle : 3;
	uint32_t octx_oran_is_idle : 4;
	uint32_t octx_fh_is_idle : 3;
	uint32_t octx_c2c_is_idle : 3;
	uint32_t fhrx_is_idle : 3;
	uint32_t fhtx_is_idle : 3;
	uint32_t c2crx_is_idle : 3;
	uint32_t c2ctx_is_idle : 3;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_idle_2_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_idle_2_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_idle_2_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_0_CFG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t capture_point_id : 4;
	uint32_t reserved0 : 4;
	uint32_t capture_point_sub_id : 8;
	uint32_t capture_point_valid : 1;
	uint32_t reserved1 : 15;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_0_cfg_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_0_cfg_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_0_cfg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_MASK_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_0_data_mask_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_0_data_mask_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_0_data_mask_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_0_DATA_VALUE_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t value : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_0_data_value_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_0_data_value_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_0_data_value_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_MASK_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_0_tuser_mask_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_0_tuser_mask_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_0_tuser_mask_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_0_TUSER_VALUE_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t value : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_0_tuser_value_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_0_tuser_value_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_0_tuser_value_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_0_TID_MASK_VALUE
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 16;
	uint32_t value : 16;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_0_tid_mask_value_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_0_tid_mask_value_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_0_tid_mask_value_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_0_MISC_MASK_VALUE
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t tdest_mask : 8;
	uint32_t tdest_value : 8;
	uint32_t terror_mask : 1;
	uint32_t terror_value : 1;
	uint32_t reserved0 : 14;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_0_misc_mask_value_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_0_misc_mask_value_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_0_misc_mask_value_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_1_CFG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t capture_point_id : 4;
	uint32_t reserved0 : 4;
	uint32_t capture_point_sub_id : 8;
	uint32_t capture_point_valid : 1;
	uint32_t reserved1 : 15;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_1_cfg_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_1_cfg_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_1_cfg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_MASK_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_1_data_mask_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_1_data_mask_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_1_data_mask_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_1_DATA_VALUE_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t value : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_1_data_value_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_1_data_value_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_1_data_value_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_MASK_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_1_tuser_mask_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_1_tuser_mask_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_1_tuser_mask_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_1_TUSER_VALUE_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t value : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_1_tuser_value_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_1_tuser_value_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_1_tuser_value_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_1_TID_MASK_VALUE
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 16;
	uint32_t value : 16;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_1_tid_mask_value_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_1_tid_mask_value_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_1_tid_mask_value_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_1_MISC_MASK_VALUE
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t tdest_mask : 8;
	uint32_t tdest_value : 8;
	uint32_t terror_mask : 1;
	uint32_t terror_value : 1;
	uint32_t reserved0 : 14;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_1_misc_mask_value_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_1_misc_mask_value_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_1_misc_mask_value_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_2_CFG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t capture_point_id : 4;
	uint32_t reserved0 : 4;
	uint32_t capture_point_sub_id : 8;
	uint32_t capture_point_valid : 1;
	uint32_t reserved1 : 15;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_2_cfg_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_2_cfg_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_2_cfg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_MASK_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_2_data_mask_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_2_data_mask_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_2_data_mask_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_2_DATA_VALUE_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t value : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_2_data_value_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_2_data_value_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_2_data_value_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_MASK_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_2_tuser_mask_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_2_tuser_mask_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_2_tuser_mask_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_2_TUSER_VALUE_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t value : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_2_tuser_value_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_2_tuser_value_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_2_tuser_value_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_2_TID_MASK_VALUE
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 16;
	uint32_t value : 16;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_2_tid_mask_value_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_2_tid_mask_value_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_2_tid_mask_value_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_2_MISC_MASK_VALUE
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t tdest_mask : 8;
	uint32_t tdest_value : 8;
	uint32_t terror_mask : 1;
	uint32_t terror_value : 1;
	uint32_t reserved0 : 14;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_2_misc_mask_value_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_2_misc_mask_value_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_2_misc_mask_value_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_3_CFG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t capture_point_id : 4;
	uint32_t reserved0 : 4;
	uint32_t capture_point_sub_id : 8;
	uint32_t capture_point_valid : 1;
	uint32_t reserved1 : 15;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_3_cfg_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_3_cfg_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_3_cfg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_MASK_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_3_data_mask_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_3_data_mask_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_3_data_mask_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_3_DATA_VALUE_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t value : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_3_data_value_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_3_data_value_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_3_data_value_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_MASK_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_3_tuser_mask_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_3_tuser_mask_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_3_tuser_mask_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_3_TUSER_VALUE_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t value : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_3_tuser_value_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_3_tuser_value_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_3_tuser_value_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_3_TID_MASK_VALUE
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 16;
	uint32_t value : 16;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_3_tid_mask_value_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_3_tid_mask_value_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_3_tid_mask_value_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_TPDM_3_MISC_MASK_VALUE
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t tdest_mask : 8;
	uint32_t tdest_value : 8;
	uint32_t terror_mask : 1;
	uint32_t terror_value : 1;
	uint32_t reserved0 : 14;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_3_misc_mask_value_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_3_misc_mask_value_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_tpdm_3_misc_mask_value_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_0_CFG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t capture_point_id : 4;
	uint32_t reserved0 : 4;
	uint32_t capture_point_sub_id : 8;
	uint32_t capture_point_valid : 1;
	uint32_t reserved1 : 15;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_0_cfg_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_0_cfg_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_0_cfg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_MASK_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_0_data_mask_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_0_data_mask_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_0_data_mask_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_0_DATA_VALUE_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t value : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_0_data_value_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_0_data_value_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_0_data_value_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_MASK_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_0_tuser_mask_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_0_tuser_mask_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_0_tuser_mask_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_0_TUSER_VALUE_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t value : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_0_tuser_value_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_0_tuser_value_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_0_tuser_value_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_0_TID_MASK_VALUE
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 16;
	uint32_t value : 16;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_0_tid_mask_value_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_0_tid_mask_value_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_0_tid_mask_value_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_0_MISC_MASK_VALUE
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t tdest_mask : 8;
	uint32_t tdest_value : 8;
	uint32_t terror_mask : 1;
	uint32_t terror_value : 1;
	uint32_t reserved0 : 14;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_0_misc_mask_value_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_0_misc_mask_value_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_0_misc_mask_value_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_1_CFG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t capture_point_id : 4;
	uint32_t reserved0 : 4;
	uint32_t capture_point_sub_id : 8;
	uint32_t capture_point_valid : 1;
	uint32_t reserved1 : 15;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_1_cfg_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_1_cfg_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_1_cfg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_MASK_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_1_data_mask_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_1_data_mask_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_1_data_mask_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_1_DATA_VALUE_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t value : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_1_data_value_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_1_data_value_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_1_data_value_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_MASK_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_1_tuser_mask_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_1_tuser_mask_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_1_tuser_mask_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_1_TUSER_VALUE_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t value : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_1_tuser_value_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_1_tuser_value_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_1_tuser_value_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_1_TID_MASK_VALUE
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 16;
	uint32_t value : 16;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_1_tid_mask_value_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_1_tid_mask_value_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_1_tid_mask_value_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_1_MISC_MASK_VALUE
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t tdest_mask : 8;
	uint32_t tdest_value : 8;
	uint32_t terror_mask : 1;
	uint32_t terror_value : 1;
	uint32_t reserved0 : 14;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_1_misc_mask_value_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_1_misc_mask_value_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_1_misc_mask_value_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_2_CFG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t capture_point_id : 4;
	uint32_t reserved0 : 4;
	uint32_t capture_point_sub_id : 8;
	uint32_t capture_point_valid : 1;
	uint32_t reserved1 : 15;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_2_cfg_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_2_cfg_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_2_cfg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_MASK_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_2_data_mask_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_2_data_mask_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_2_data_mask_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_2_DATA_VALUE_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t value : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_2_data_value_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_2_data_value_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_2_data_value_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_MASK_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_2_tuser_mask_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_2_tuser_mask_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_2_tuser_mask_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_2_TUSER_VALUE_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t value : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_2_tuser_value_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_2_tuser_value_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_2_tuser_value_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_2_TID_MASK_VALUE
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 16;
	uint32_t value : 16;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_2_tid_mask_value_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_2_tid_mask_value_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_2_tid_mask_value_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_2_MISC_MASK_VALUE
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t tdest_mask : 8;
	uint32_t tdest_value : 8;
	uint32_t terror_mask : 1;
	uint32_t terror_value : 1;
	uint32_t reserved0 : 14;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_2_misc_mask_value_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_2_misc_mask_value_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_2_misc_mask_value_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_3_CFG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t capture_point_id : 4;
	uint32_t reserved0 : 4;
	uint32_t capture_point_sub_id : 8;
	uint32_t capture_point_valid : 1;
	uint32_t reserved1 : 15;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_3_cfg_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_3_cfg_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_3_cfg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_MASK_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_3_data_mask_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_3_data_mask_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_3_data_mask_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_3_DATA_VALUE_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t value : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_3_data_value_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_3_data_value_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_3_data_value_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_MASK_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_3_tuser_mask_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_3_tuser_mask_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_3_tuser_mask_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_3_TUSER_VALUE_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t value : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_3_tuser_value_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_3_tuser_value_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_3_tuser_value_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_3_TID_MASK_VALUE
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 16;
	uint32_t value : 16;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_3_tid_mask_value_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_3_tid_mask_value_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_3_tid_mask_value_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_TPDM_3_MISC_MASK_VALUE
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t tdest_mask : 8;
	uint32_t tdest_value : 8;
	uint32_t terror_mask : 1;
	uint32_t terror_value : 1;
	uint32_t reserved0 : 14;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_3_misc_mask_value_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_3_misc_mask_value_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_tpdm_3_misc_mask_value_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_0_CFG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t capture_point_id : 4;
	uint32_t reserved0 : 4;
	uint32_t capture_point_sub_id : 8;
	uint32_t capture_point_valid : 1;
	uint32_t reserved1 : 15;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_0_cfg_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_0_cfg_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_0_cfg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_MASK_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_0_data_mask_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_0_data_mask_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_0_data_mask_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_0_DATA_VALUE_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t value : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_0_data_value_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_0_data_value_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_0_data_value_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_MASK_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_0_tuser_mask_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_0_tuser_mask_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_0_tuser_mask_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_0_TUSER_VALUE_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t value : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_0_tuser_value_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_0_tuser_value_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_0_tuser_value_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_0_TID_MASK_VALUE
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 16;
	uint32_t value : 16;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_0_tid_mask_value_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_0_tid_mask_value_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_0_tid_mask_value_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_0_MISC_MASK_VALUE
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t tdest_mask : 8;
	uint32_t tdest_value : 8;
	uint32_t terror_mask : 1;
	uint32_t terror_value : 1;
	uint32_t reserved0 : 14;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_0_misc_mask_value_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_0_misc_mask_value_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_0_misc_mask_value_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_1_CFG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t capture_point_id : 4;
	uint32_t reserved0 : 4;
	uint32_t capture_point_sub_id : 8;
	uint32_t capture_point_valid : 1;
	uint32_t reserved1 : 15;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_1_cfg_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_1_cfg_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_1_cfg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_MASK_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_1_data_mask_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_1_data_mask_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_1_data_mask_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_1_DATA_VALUE_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t value : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_1_data_value_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_1_data_value_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_1_data_value_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_MASK_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_1_tuser_mask_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_1_tuser_mask_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_1_tuser_mask_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_1_TUSER_VALUE_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t value : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_1_tuser_value_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_1_tuser_value_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_1_tuser_value_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_1_TID_MASK_VALUE
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 16;
	uint32_t value : 16;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_1_tid_mask_value_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_1_tid_mask_value_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_1_tid_mask_value_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_1_MISC_MASK_VALUE
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t tdest_mask : 8;
	uint32_t tdest_value : 8;
	uint32_t terror_mask : 1;
	uint32_t terror_value : 1;
	uint32_t reserved0 : 14;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_1_misc_mask_value_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_1_misc_mask_value_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_1_misc_mask_value_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_2_CFG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t capture_point_id : 4;
	uint32_t reserved0 : 4;
	uint32_t capture_point_sub_id : 8;
	uint32_t capture_point_valid : 1;
	uint32_t reserved1 : 15;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_2_cfg_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_2_cfg_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_2_cfg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_MASK_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_2_data_mask_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_2_data_mask_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_2_data_mask_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_2_DATA_VALUE_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t value : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_2_data_value_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_2_data_value_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_2_data_value_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_MASK_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_2_tuser_mask_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_2_tuser_mask_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_2_tuser_mask_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_2_TUSER_VALUE_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t value : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_2_tuser_value_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_2_tuser_value_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_2_tuser_value_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_2_TID_MASK_VALUE
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 16;
	uint32_t value : 16;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_2_tid_mask_value_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_2_tid_mask_value_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_2_tid_mask_value_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_2_MISC_MASK_VALUE
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t tdest_mask : 8;
	uint32_t tdest_value : 8;
	uint32_t terror_mask : 1;
	uint32_t terror_value : 1;
	uint32_t reserved0 : 14;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_2_misc_mask_value_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_2_misc_mask_value_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_2_misc_mask_value_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_3_CFG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t capture_point_id : 4;
	uint32_t reserved0 : 4;
	uint32_t capture_point_sub_id : 8;
	uint32_t capture_point_valid : 1;
	uint32_t reserved1 : 15;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_3_cfg_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_3_cfg_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_3_cfg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_MASK_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_3_data_mask_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_3_data_mask_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_3_data_mask_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_3_DATA_VALUE_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t value : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_3_data_value_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_3_data_value_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_3_data_value_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_MASK_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_3_tuser_mask_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_3_tuser_mask_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_3_tuser_mask_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_3_TUSER_VALUE_m
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t value : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_3_tuser_value_m_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_3_tuser_value_m_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_3_tuser_value_m_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_3_TID_MASK_VALUE
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t mask : 16;
	uint32_t value : 16;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_3_tid_mask_value_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_3_tid_mask_value_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_3_tid_mask_value_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_ORAN_TPDM_3_MISC_MASK_VALUE
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t tdest_mask : 8;
	uint32_t tdest_value : 8;
	uint32_t terror_mask : 1;
	uint32_t terror_value : 1;
	uint32_t reserved0 : 14;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_3_misc_mask_value_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_3_misc_mask_value_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_oran_tpdm_3_misc_mask_value_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_TPDM_GLOBAL_CFG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t shared_data_mode : 1;
	uint32_t reserved0 : 31;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_tpdm_global_cfg_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_tpdm_global_cfg_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_tpdm_global_cfg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t ring_id_0 : 8;
	uint32_t ring_id_1 : 8;
	uint32_t ring_id_2 : 8;
	uint32_t ring_id_3 : 8;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_0_non_ecpri_lut_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_0_non_ecpri_lut_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_0_non_ecpri_lut_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t ring_id_0 : 8;
	uint32_t ring_id_1 : 8;
	uint32_t ring_id_2 : 8;
	uint32_t ring_id_3 : 8;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_1_non_ecpri_lut_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_1_non_ecpri_lut_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_1_non_ecpri_lut_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t ring_id_0 : 8;
	uint32_t ring_id_1 : 8;
	uint32_t ring_id_2 : 8;
	uint32_t ring_id_3 : 8;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_2_non_ecpri_lut_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_2_non_ecpri_lut_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_2_non_ecpri_lut_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FHRX_n_DEFAULT_LUT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t dma_ring_id : 7;
	uint32_t oc_link_id : 2;
	uint32_t route_to_oran : 1;
	uint32_t route_to_c2c : 1;
	uint32_t route_to_dma : 1;
	uint32_t reserved0 : 20;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_n_default_lut_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_n_default_lut_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_n_default_lut_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_0
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t msg_type_0 : 8;
	uint32_t valid_0 : 1;
	uint32_t reserved0 : 1;
	uint32_t msg_type_1 : 8;
	uint32_t valid_1 : 1;
	uint32_t reserved1 : 1;
	uint32_t msg_type_2 : 8;
	uint32_t valid_2 : 1;
	uint32_t reserved2 : 3;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_msg_type_lut_0_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_msg_type_lut_0_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_msg_type_lut_0_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_1
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t msg_type_3 : 8;
	uint32_t valid_3 : 1;
	uint32_t reserved0 : 1;
	uint32_t msg_type_4 : 8;
	uint32_t valid_4 : 1;
	uint32_t reserved1 : 1;
	uint32_t msg_type_5 : 8;
	uint32_t valid_5 : 1;
	uint32_t reserved2 : 3;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_msg_type_lut_1_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_msg_type_lut_1_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_msg_type_lut_1_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t dma_ring_id : 7;
	uint32_t oc_link_id : 2;
	uint32_t route_to_oran : 1;
	uint32_t route_to_c2c : 1;
	uint32_t route_to_dma : 1;
	uint32_t reserved0 : 20;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_msg_type_n_lut_result_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_msg_type_n_lut_result_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_msg_type_n_lut_result_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t msg_type_0 : 8;
	uint32_t valid_0 : 1;
	uint32_t reserved0 : 1;
	uint32_t msg_type_1 : 8;
	uint32_t valid_1 : 1;
	uint32_t reserved1 : 1;
	uint32_t msg_type_2 : 8;
	uint32_t valid_2 : 1;
	uint32_t reserved2 : 3;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2crx_msg_type_lut_0_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2crx_msg_type_lut_0_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2crx_msg_type_lut_0_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_1
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t msg_type_3 : 8;
	uint32_t valid_3 : 1;
	uint32_t reserved0 : 1;
	uint32_t msg_type_4 : 8;
	uint32_t valid_4 : 1;
	uint32_t reserved1 : 1;
	uint32_t msg_type_5 : 8;
	uint32_t valid_5 : 1;
	uint32_t reserved2 : 3;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2crx_msg_type_lut_1_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2crx_msg_type_lut_1_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2crx_msg_type_lut_1_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t dma_ring_id : 7;
	uint32_t oc_link_id : 2;
	uint32_t l2_encap_info : 8;
	uint32_t l3_encap_info : 8;
	uint32_t l3_encap_valid : 1;
	uint32_t route_to_oran : 1;
	uint32_t route_to_fh : 1;
	uint32_t route_to_dma : 1;
	uint32_t reserved0 : 3;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2crx_msg_type_n_lut_result_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2crx_msg_type_n_lut_result_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2crx_msg_type_n_lut_result_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t dma_ring_id : 7;
	uint32_t oc_link_id : 2;
	uint32_t l2_encap_info : 8;
	uint32_t l3_encap_info : 8;
	uint32_t l3_encap_valid : 1;
	uint32_t route_to_oran : 1;
	uint32_t route_to_fh : 1;
	uint32_t route_to_dma : 1;
	uint32_t reserved0 : 3;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2crx_n_dl_default_lut_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2crx_n_dl_default_lut_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2crx_n_dl_default_lut_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t dma_ring_id : 7;
	uint32_t oc_link_id : 2;
	uint32_t l2_encap_info : 8;
	uint32_t l3_encap_info : 8;
	uint32_t l3_encap_valid : 1;
	uint32_t route_to_oran : 1;
	uint32_t route_to_fh : 1;
	uint32_t route_to_dma : 1;
	uint32_t reserved0 : 3;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2crx_n_ul_default_lut_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2crx_n_ul_default_lut_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2crx_n_ul_default_lut_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2CRX_NON_ECPRI_LUT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t ring_id_0 : 8;
	uint32_t ring_id_1 : 8;
	uint32_t ring_id_2 : 8;
	uint32_t reserved0 : 8;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2crx_non_ecpri_lut_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2crx_non_ecpri_lut_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2crx_non_ecpri_lut_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_OCRX_FH_n_DEFAULT_LUT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t l2_encap_info : 8;
	uint32_t l3_encap_info : 8;
	uint32_t l3_encap_valid : 1;
	uint32_t drop : 1;
	uint32_t reserved0 : 14;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_ocrx_fh_n_default_lut_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_ocrx_fh_n_default_lut_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_ocrx_fh_n_default_lut_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_OCRX_C2C_DEFAULT_LUT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t l2_encap_info : 8;
	uint32_t l3_encap_info : 8;
	uint32_t l3_encap_valid : 1;
	uint32_t reserved0 : 7;
	uint32_t c2c_port_num : 2;
	uint32_t reserved1 : 6;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_ocrx_c2c_default_lut_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_ocrx_c2c_default_lut_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_ocrx_c2c_default_lut_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_UC_FHRX_BUFF_ADDR
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t addr : 16;
	uint32_t reserved0 : 16;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fhrx_buff_addr_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fhrx_buff_addr_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fhrx_buff_addr_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_UC_FHRX_BUFF_SIZE
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t size : 15;
	uint32_t reserved0 : 17;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fhrx_buff_size_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fhrx_buff_size_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fhrx_buff_size_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_UC_FHRX_BUFF_RD
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t addr : 16;
	uint32_t reserved0 : 16;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fhrx_buff_rd_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fhrx_buff_rd_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fhrx_buff_rd_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_POP
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t length : 14;
	uint32_t reserved0 : 2;
	uint32_t link : 2;
	uint32_t port : 2;
	uint32_t reserved1 : 4;
	uint32_t err : 1;
	uint32_t reserved2 : 7;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fhrx_pkt_attr_pop_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fhrx_pkt_attr_pop_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fhrx_pkt_attr_pop_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_NO_POP
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t length : 14;
	uint32_t reserved0 : 2;
	uint32_t link : 2;
	uint32_t port : 2;
	uint32_t reserved1 : 4;
	uint32_t err : 1;
	uint32_t reserved2 : 7;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fhrx_pkt_attr_no_pop_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fhrx_pkt_attr_no_pop_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fhrx_pkt_attr_no_pop_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_UC_FHRX_STATUS
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t uc_pkt_pending : 1;
	uint32_t uc_pkt_overflow : 3;
	uint32_t uc_pkt_err : 3;
	uint32_t uc_pkt_drop : 3;
	uint32_t reserved0 : 22;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fhrx_status_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fhrx_status_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fhrx_status_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_UC_FH_CTRL
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t fhrx_uc_enable : 1;
	uint32_t fhrx_uc_pkt_err_drop : 1;
	uint32_t reserved0 : 30;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fh_ctrl_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fh_ctrl_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fh_ctrl_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_UC_FHTX_PKT_ADDR
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t addr : 16;
	uint32_t length : 14;
	uint32_t reserved0 : 2;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fhtx_pkt_addr_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fhtx_pkt_addr_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fhtx_pkt_addr_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t l2_encap : 9;
	uint32_t l3_encap : 9;
	uint32_t l2_encap_valid : 1;
	uint32_t l3_encap_valid : 1;
	uint32_t reserved0 : 4;
	uint32_t link : 2;
	uint32_t port : 2;
	uint32_t reserved1 : 3;
	uint32_t pkt_avail : 1;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fhtx_pkt_attr_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fhtx_pkt_attr_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fhtx_pkt_attr_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_FHRX_PKT_CNT_n
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t cnt : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhrx_pkt_cnt_n_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhrx_pkt_cnt_n_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhrx_pkt_cnt_n_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_FHRX_DMA_PKT_CNT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t cnt : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhrx_dma_pkt_cnt_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhrx_dma_pkt_cnt_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhrx_dma_pkt_cnt_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_FHRX_UC_PKT_CNT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t cnt : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhrx_uc_pkt_cnt_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhrx_uc_pkt_cnt_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhrx_uc_pkt_cnt_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_FHRX_UC_ERR_PKT_CNT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t cnt : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhrx_uc_err_pkt_cnt_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhrx_uc_err_pkt_cnt_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhrx_uc_err_pkt_cnt_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_FHRX_ERR_PKT_CNT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t cnt : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhrx_err_pkt_cnt_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhrx_err_pkt_cnt_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhrx_err_pkt_cnt_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_FHTX_PKT_CNT_n
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t cnt : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhtx_pkt_cnt_n_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhtx_pkt_cnt_n_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhtx_pkt_cnt_n_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_FHTX_C2C_PKT_OVF_CNT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t cnt : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhtx_c2c_pkt_ovf_cnt_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhtx_c2c_pkt_ovf_cnt_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhtx_c2c_pkt_ovf_cnt_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_FHTX_DMA_PKT_CNT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t cnt : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhtx_dma_pkt_cnt_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhtx_dma_pkt_cnt_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhtx_dma_pkt_cnt_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_FHTX_UC_PKT_CNT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t cnt : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhtx_uc_pkt_cnt_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhtx_uc_pkt_cnt_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhtx_uc_pkt_cnt_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_C2CRX_PKT_CNT_n
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t cnt : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2crx_pkt_cnt_n_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2crx_pkt_cnt_n_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2crx_pkt_cnt_n_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_C2CRX_DMA_PKT_CNT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t cnt : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2crx_dma_pkt_cnt_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2crx_dma_pkt_cnt_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2crx_dma_pkt_cnt_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_C2CRX_ERR_PKT_CNT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t cnt : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2crx_err_pkt_cnt_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2crx_err_pkt_cnt_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2crx_err_pkt_cnt_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_C2CTX_PKT_CNT_n
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t cnt : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2ctx_pkt_cnt_n_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2ctx_pkt_cnt_n_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2ctx_pkt_cnt_n_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_C2CTX_FH_PKT_OVF_CNT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t cnt : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2ctx_fh_pkt_ovf_cnt_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2ctx_fh_pkt_ovf_cnt_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2ctx_fh_pkt_ovf_cnt_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_C2CTX_DMA_PKT_CNT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t cnt : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2ctx_dma_pkt_cnt_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2ctx_dma_pkt_cnt_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2ctx_dma_pkt_cnt_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_OCTX_C2C_PKT_DROP_CNT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t cnt : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_octx_c2c_pkt_drop_cnt_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_octx_c2c_pkt_drop_cnt_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_octx_c2c_pkt_drop_cnt_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_OCTX_FH_PKT_DROP_CNT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t cnt : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_octx_fh_pkt_drop_cnt_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_octx_fh_pkt_drop_cnt_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_octx_fh_pkt_drop_cnt_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_OCTX_PKT_CNT_n
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t cnt : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_octx_pkt_cnt_n_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_octx_pkt_cnt_n_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_octx_pkt_cnt_n_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_OCRX_PKT_CNT_n
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t cnt : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_pkt_cnt_n_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_pkt_cnt_n_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_pkt_cnt_n_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_OCRX_FH_PKT_CNT_n
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t cnt : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_fh_pkt_cnt_n_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_fh_pkt_cnt_n_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_fh_pkt_cnt_n_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_OCRX_C2C_PKT_CNT_n
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t cnt : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_c2c_pkt_cnt_n_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_c2c_pkt_cnt_n_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_c2c_pkt_cnt_n_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t ocrx_fh_0_cnt : 10;
	uint32_t ocrx_fh_1_cnt : 10;
	uint32_t ocrx_fh_2_cnt : 10;
	uint32_t reserved0 : 2;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_unknown_pcid_cnt_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_unknown_pcid_cnt_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_unknown_pcid_cnt_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t info : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_unknown_pcid_info_1_n_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_unknown_pcid_info_1_n_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_unknown_pcid_info_1_n_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t info : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_unknown_pcid_info_2_n_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_unknown_pcid_info_2_n_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_unknown_pcid_info_2_n_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t fhrx_0_cnt : 10;
	uint32_t fhrx_1_cnt : 10;
	uint32_t fhrx_2_cnt : 10;
	uint32_t reserved0 : 2;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhrx_unknown_pcid_cnt_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhrx_unknown_pcid_cnt_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhrx_unknown_pcid_cnt_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t info : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhrx_unknown_pcid_info_1_n_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhrx_unknown_pcid_info_1_n_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhrx_unknown_pcid_info_1_n_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t info : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhrx_unknown_pcid_info_2_n_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhrx_unknown_pcid_info_2_n_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhrx_unknown_pcid_info_2_n_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t c2crx_0_cnt : 10;
	uint32_t c2crx_1_cnt : 10;
	uint32_t c2crx_2_cnt : 10;
	uint32_t reserved0 : 2;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2crx_unknown_pcid_cnt_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2crx_unknown_pcid_cnt_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2crx_unknown_pcid_cnt_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_1_n
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t info : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2crx_unknown_pcid_info_1_n_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2crx_unknown_pcid_info_1_n_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2crx_unknown_pcid_info_1_n_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_INFO_2_n
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t info : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2crx_unknown_pcid_info_2_n_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2crx_unknown_pcid_info_2_n_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2crx_unknown_pcid_info_2_n_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_TESTBUS_SELECT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t xbar_testbus_sel : 8;
	uint32_t oran_testbus_sel : 8;
	uint32_t reserved0 : 16;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_testbus_select_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_testbus_select_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_testbus_select_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_XBAR_TESTBUS
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t xbar_testbus : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_xbar_testbus_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_xbar_testbus_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_xbar_testbus_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_ORAN_TESTBUS
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t oran_testbus : 32;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_oran_testbus_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_oran_testbus_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_oran_testbus_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_OCTX_FH_BUFF_WATERMARK_n
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t fh0 : 10;
	uint32_t fh1 : 10;
	uint32_t fh2 : 10;
	uint32_t reserved0 : 2;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_octx_fh_buff_watermark_n_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_octx_fh_buff_watermark_n_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_octx_fh_buff_watermark_n_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_OCTX_C2C_BUFF_WATERMARK_n
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t c2c0 : 10;
	uint32_t c2c1 : 10;
	uint32_t c2c2 : 10;
	uint32_t reserved0 : 2;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_octx_c2c_buff_watermark_n_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_octx_c2c_buff_watermark_n_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_octx_c2c_buff_watermark_n_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t cc0 : 10;
	uint32_t cc1 : 10;
	uint32_t reserved0 : 12;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_0_1_buff_watermark_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_0_1_buff_watermark_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_0_1_buff_watermark_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t cc2 : 10;
	uint32_t cc3 : 10;
	uint32_t reserved0 : 12;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_2_3_buff_watermark_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_2_3_buff_watermark_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_2_3_buff_watermark_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_OCRX_C2C_BUFF_WATERMARK
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t c2c0 : 10;
	uint32_t c2c1 : 10;
	uint32_t c2c2 : 10;
	uint32_t reserved0 : 2;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_c2c_buff_watermark_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_c2c_buff_watermark_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_c2c_buff_watermark_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_OCRX_FH_BUFF_WATERMARK
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t fh0 : 10;
	uint32_t fh1 : 10;
	uint32_t fh2 : 10;
	uint32_t reserved0 : 2;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_fh_buff_watermark_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_fh_buff_watermark_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_fh_buff_watermark_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_FHTX_C2C_BUFF_WATERMARK
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t fh0 : 10;
	uint32_t fh1 : 10;
	uint32_t fh2 : 10;
	uint32_t reserved0 : 2;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhtx_c2c_buff_watermark_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhtx_c2c_buff_watermark_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhtx_c2c_buff_watermark_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_C2CTX_FH_BUFF_WATERMARK
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t c2c0 : 10;
	uint32_t c2c1 : 10;
	uint32_t c2c2 : 10;
	uint32_t reserved0 : 2;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2ctx_fh_buff_watermark_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2ctx_fh_buff_watermark_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_c2ctx_fh_buff_watermark_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t cc0 : 10;
	uint32_t cc1 : 10;
	uint32_t reserved0 : 12;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_octx_oc_0_1_buff_watermark_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_octx_oc_0_1_buff_watermark_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_octx_oc_0_1_buff_watermark_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t cc2 : 10;
	uint32_t cc3 : 10;
	uint32_t reserved0 : 12;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_octx_oc_2_3_buff_watermark_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_octx_oc_2_3_buff_watermark_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_octx_oc_2_3_buff_watermark_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_FH_STATUS_SHADOW
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t tx_c2c_overflow : 3;
	uint32_t reserved0 : 29;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_status_shadow_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_status_shadow_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_fh_status_shadow_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_C2C_STATUS_SHADOW
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t tx_fh_overflow : 3;
	uint32_t reserved0 : 29;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_status_shadow_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_status_shadow_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2c_status_shadow_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_OCTX_STATUS_SHADOW
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t tx_fh_drop : 3;
	uint32_t tx_c2c_drop : 3;
	uint32_t tx_fh_overflow : 3;
	uint32_t tx_c2c_overflow : 3;
	uint32_t reserved0 : 20;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_octx_status_shadow_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_octx_status_shadow_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_octx_status_shadow_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_XBAR_UC_FHRX_STATUS_SHADOW
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t uc_pkt_pending : 1;
	uint32_t uc_pkt_overflow : 3;
	uint32_t uc_pkt_err : 3;
	uint32_t uc_pkt_drop : 3;
	uint32_t reserved0 : 22;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fhrx_status_shadow_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fhrx_status_shadow_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_xbar_uc_fhrx_status_shadow_u;

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_XBAR_LUT
 *--------------------------------------------------------------------------*/

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_LUT_XBAR_FHRX_m_LUT_n
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t dma_ring_id : 7;
	uint32_t oc_link_id : 2;
	uint32_t route_to_oran : 1;
	uint32_t route_to_c2c : 1;
	uint32_t route_to_dma : 1;
	uint32_t valid : 1;
	uint32_t reserved0 : 19;
} ecpri_xbar_hwio_def_ecpri_xbar_lut_xbar_fhrx_m_lut_n_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_lut_xbar_fhrx_m_lut_n_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_lut_xbar_fhrx_m_lut_n_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_LUT_XBAR_C2CRX_m_DL_LUT_n
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t dma_ring_id : 7;
	uint32_t oc_link_id : 2;
	uint32_t l2_encap_info : 8;
	uint32_t l3_encap_info : 8;
	uint32_t l3_encap_valid : 1;
	uint32_t route_to_oran : 1;
	uint32_t route_to_fh : 1;
	uint32_t route_to_dma : 1;
	uint32_t valid : 1;
	uint32_t reserved0 : 2;
} ecpri_xbar_hwio_def_ecpri_xbar_lut_xbar_c2crx_m_dl_lut_n_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_lut_xbar_c2crx_m_dl_lut_n_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_lut_xbar_c2crx_m_dl_lut_n_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_LUT_XBAR_C2CRX_m_UL_LUT_n
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t dma_ring_id : 7;
	uint32_t oc_link_id : 2;
	uint32_t l2_encap_info : 8;
	uint32_t l3_encap_info : 8;
	uint32_t l3_encap_valid : 1;
	uint32_t route_to_oran : 1;
	uint32_t route_to_fh : 1;
	uint32_t route_to_dma : 1;
	uint32_t valid : 1;
	uint32_t reserved0 : 2;
} ecpri_xbar_hwio_def_ecpri_xbar_lut_xbar_c2crx_m_ul_lut_n_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_lut_xbar_c2crx_m_ul_lut_n_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_lut_xbar_c2crx_m_ul_lut_n_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_XBAR_LUT_XBAR_OCRX_m_LUT_n
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	uint32_t l2_encap_info : 8;
	uint32_t l3_encap_info : 8;
	uint32_t l3_encap_valid : 1;
	uint32_t valid : 1;
	uint32_t reserved0 : 14;
} ecpri_xbar_hwio_def_ecpri_xbar_lut_xbar_ocrx_m_lut_n_s;

/* Union definition of register */
typedef union
{
	ecpri_xbar_hwio_def_ecpri_xbar_lut_xbar_ocrx_m_lut_n_s def;
	uint32_t value;
} ecpri_xbar_hwio_def_ecpri_xbar_lut_xbar_ocrx_m_lut_n_u;


#endif /* __ECPRI_XBAR_HWIO_DEF_H__ */
