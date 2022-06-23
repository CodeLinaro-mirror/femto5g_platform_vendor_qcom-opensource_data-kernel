/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef __ECPRI_ORAN_XTOR_HWIO_DEF_H__
#define __ECPRI_ORAN_XTOR_HWIO_DEF_H__
/**
  @file ecpri_oran_xtor_hwio.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
  ECPRI_ORAN_XTOR.*

  'Include' filters applied: <none>
  'Exclude' filters applied: RESERVED DUMMY
  */
/*----------------------------------------------------------------------------
 * MODULE: ECPRI_ORAN_XTOR
 *--------------------------------------------------------------------------*/

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_ORAN_XTOR_TX_n_CTL_REG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 wrap_en : 1;
	u32 rd_idx_wrap_cnt_saturate_en : 1;
	u32 reserved0 : 30;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_ctl_reg_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_ctl_reg_s def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_ctl_reg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_ORAN_XTOR_TX_n_CMD_m_k
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 data : 32;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_cmd_m_k_s;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 wr_idx : 5;
	u32 reserved0 : 3;
	u32 rd_idx : 5;
	u32 reserved1 : 19;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_data_idxs_reg_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_data_idxs_reg_s def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_data_idxs_reg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_ORAN_XTOR_TX_n_PKT_CNT_REG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 pkt_cnt : 32;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_pkt_cnt_reg_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_pkt_cnt_reg_s def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_pkt_cnt_reg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register:
  ECPRI_ORAN_XTOR_TX_n_BACKPRESSURE_CNT_REG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 backpressure_cnt : 32;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_backpressure_cnt_reg_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_backpressure_cnt_reg_s
		def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_backpressure_cnt_reg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_ORAN_XTOR_TX_n_RD_IDX_WRAP_CNT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 rd_idx_wrap_cnt : 24;
	u32 reserved0 : 8;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_rd_idx_wrap_cnt_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_rd_idx_wrap_cnt_s def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_rd_idx_wrap_cnt_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_ORAN_XTOR_RX_n_CTL_REG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 tgt_rx_err_en : 1;
	u32 reserved0 : 3;
	u32 data_err_en : 1;
	u32 reserved1 : 3;
	u32 time_err_en : 1;
	u32 reserved2 : 3;
	u32 len_err_en : 1;
	u32 reserved3 : 3;
	u32 crc_err_en : 1;
	u32 reserved4 : 3;
	u32 latency_err_en : 1;
	u32 reserved5 : 3;
	u32 seqnum_err_en : 1;
	u32 avg_latency_clear : 1;
	u32 min_latency_clear : 1;
	u32 max_latency_clear : 1;
	u32 min_bw_clear : 1;
	u32 max_bw_clear : 1;
	u32 min_bw_en : 1;
	u32 max_bw_en : 1;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_ctl_reg_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_ctl_reg_s def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_ctl_reg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_ORAN_XTOR_RX_n_ERROR_REG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 reset_err_status : 1;
	u32 reserved0 : 3;
	u32 tgt_rx_err : 1;
	u32 reserved1 : 3;
	u32 data_err : 1;
	u32 reserved2 : 3;
	u32 time_err : 1;
	u32 reserved3 : 3;
	u32 len_err : 1;
	u32 reserved4 : 3;
	u32 crc_err : 1;
	u32 reserved5 : 3;
	u32 latency_err : 1;
	u32 reserved6 : 3;
	u32 seqnum_err : 4;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_reg_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_reg_s def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_reg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_ORAN_XTOR_RX_n_PKT_CNT_REG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 pkt_cnt : 32;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_pkt_cnt_reg_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_pkt_cnt_reg_s def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_pkt_cnt_reg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 ecpri_msg_type : 8;
	u32 src_tx : 2;
	u32 reserved0 : 2;
	u32 tgt_rx : 2;
	u32 reserved1 : 2;
	u32 seqnum : 5;
	u32 reserved2 : 3;
	u32 xu_num : 5;
	u32 reserved3 : 3;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_0_reg_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_0_reg_s def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_0_reg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_1_REG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 ecpri_payload_size : 16;
	u32 ecpri_pcid : 16;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_1_reg_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_1_reg_s def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_1_reg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_2_REG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 timestamp : 32;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_2_reg_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_2_reg_s def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_2_reg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_3_REG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 init_data : 32;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_3_reg_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_3_reg_s def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_3_reg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register:
  ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 reset_error_dump : 1;
	u32 tgt_rx_err : 1;
	u32 data_err : 1;
	u32 time_err : 1;
	u32 len_err : 1;
	u32 crc_err : 1;
	u32 latency_err : 1;
	u32 seqnum_err : 4;
	u32 xu_num : 5;
	u32 reserved0 : 16;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_status_dump_reg_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_status_dump_reg_s
	def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_status_dump_reg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register:
  ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_PACKET_LATENCY
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 actual_latency : 32;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_reg_packet_latency_s;

/* Union definition of register */
typedef union
{
ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_reg_packet_latency_s
	def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_reg_packet_latency_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register:
  ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_EXPECTED_VALUES
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 expected_seqnum : 5;
	u32 reserved0 : 11;
	u32 actual_length : 16;
}ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_reg_expected_values_s;

/* Union definition of register */
typedef union
{
ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_reg_expected_values_s
	def;
	u32 value;
}ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_reg_expected_values_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_ORAN_XTOR_RX_n_KBYTE_CNT_REG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 kbyte_cnt : 32;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_kbyte_cnt_reg_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_kbyte_cnt_reg_s def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_kbyte_cnt_reg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 en : 1;
	u32 clr : 1;
	u32 reserved0 : 30;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_kbyte_cnt_ctl_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_kbyte_cnt_ctl_s def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_kbyte_cnt_ctl_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register:
  ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_0
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 qtimer_lsb : 32;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_kbyte_cnt_qtimer_delta_0_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_kbyte_cnt_qtimer_delta_0_s
	def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_kbyte_cnt_qtimer_delta_0_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register:
  ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_1
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 qtimer_msb : 24;
	u32 reserved0 : 8;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_kbyte_cnt_qtimer_delta_1_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_kbyte_cnt_qtimer_delta_1_s
	def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_kbyte_cnt_qtimer_delta_1_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_ORAN_XTOR_RX_n_MSRMNT_PER_REG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 msrmnt_per : 32;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_msrmnt_per_reg_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_msrmnt_per_reg_s def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_msrmnt_per_reg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register:
  ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_BW_REG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 per_cnt_abv_tgt_bw : 32;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_per_cnt_abv_tgt_bw_reg_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_per_cnt_abv_tgt_bw_reg_s
	def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_per_cnt_abv_tgt_bw_reg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register:
  ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_BW_REG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 per_cnt_blw_tgt_bw : 32;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_per_cnt_blw_tgt_bw_reg_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_per_cnt_blw_tgt_bw_reg_s
	def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_per_cnt_blw_tgt_bw_reg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register:
  ECPRI_ORAN_XTOR_RX_n_PER_CNT_ABV_TGT_LAT_REG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 per_cnt_abv_tgt_lat : 32;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_per_cnt_abv_tgt_lat_reg_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_per_cnt_abv_tgt_lat_reg_s
	def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_per_cnt_abv_tgt_lat_reg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register:
  ECPRI_ORAN_XTOR_RX_n_PER_CNT_BLW_TGT_LAT_REG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 per_cnt_blw_tgt_lat : 32;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_per_cnt_blw_tgt_lat_reg_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_per_cnt_blw_tgt_lat_reg_s
	def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_per_cnt_blw_tgt_lat_reg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_ORAN_XTOR_RX_n_TGT_BW_VAL_REG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 tgt_bw : 32;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_tgt_bw_val_reg_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_tgt_bw_val_reg_s def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_tgt_bw_val_reg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_ORAN_XTOR_RX_n_MAX_BW_VAL_REG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 max_bw : 32;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_max_bw_val_reg_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_max_bw_val_reg_s def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_max_bw_val_reg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_ORAN_XTOR_RX_n_MIN_BW_VAL_REG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 min_bw : 32;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_min_bw_val_reg_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_min_bw_val_reg_s def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_min_bw_val_reg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_ORAN_XTOR_RX_n_TGT_LAT_VAL_REG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 tgt_latency : 32;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_tgt_lat_val_reg_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_tgt_lat_val_reg_s def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_tgt_lat_val_reg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_ORAN_XTOR_RX_n_MAX_LAT_VAL_REG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 max_latency : 32;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_max_lat_val_reg_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_max_lat_val_reg_s def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_max_lat_val_reg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_ORAN_XTOR_RX_n_MIN_LAT_VAL_REG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 min_latency : 32;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_min_lat_val_reg_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_min_lat_val_reg_s def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_min_lat_val_reg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 seqnum_err_count : 8;
	u32 len_err_count : 8;
	u32 time_err_count : 8;
	u32 tgt_rx_err_count : 8;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_err_counters_0_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_err_counters_0_s def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_err_counters_0_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 crc_err_count : 8;
	u32 data_err_count : 8;
	u32 latency_err_count : 8;
	u32 overall_err_count : 8;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_err_counters_1_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_err_counters_1_s def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_err_counters_1_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register:
  ECPRI_ORAN_XTOR_RX_n_MAX_LATENCY_EXPECTED
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 max_latency : 32;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_max_latency_expected_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_max_latency_expected_s
	def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_max_latency_expected_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_ORAN_XTOR_QTIMER_OFFSET_LSB
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 offset_lsbs : 32;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_qtimer_offset_lsb_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_qtimer_offset_lsb_s def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_qtimer_offset_lsb_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 offset_msbs : 24;
	u32 offset_sign_bit : 1;
	u32 reserved0 : 7;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_qtimer_offset_msb_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_qtimer_offset_msb_s def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_qtimer_offset_msb_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_ORAN_XTOR_HW_PARAMS
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 ring_size : 5;
	u32 reserved0 : 3;
	u32 num_tx_ports : 4;
	u32 num_rx_ports : 4;
	u32 reserved1 : 16;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_hw_params_s;

/* Union definition of register */
typedef union
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_hw_params_s def;
	u32 value;
} ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_hw_params_u;

#endif /* __ECPRI_ORAN_XTOR_HWIO_DEF_H__ */
