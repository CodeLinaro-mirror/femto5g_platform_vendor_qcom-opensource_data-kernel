/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <net/netlink.h>
#include <net/net_namespace.h>
#include <linux/signal.h>           /* Definition of SIGEV_* constants */
#include <linux/jiffies.h>
#include <linux/uaccess.h>
#include <linux/workqueue.h>
#include <linux/netdevice.h>
#include <linux/of_device.h>
#include <linux/debugfs.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/atomic.h>
#include <linux/fs.h>
#include "ecpri_oxtor_hal.h"


static const char *ecpriss_oxtor_hal_reg_name_to_str[ECPRI_OXTOR_OXTOR_MAX+1]={
	"ECPRI_GLOBAL_XTOR_CFG",
	"ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL",
	"ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB",
	"ECPRI_ORAN_XTOR_RX_n_MAX_LATENCY_EXPECTED",
	"ECPRI_ORAN_XTOR_RX_n_CTL_REG",
	"ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG",
	"ECPRI_ORAN_XTOR_TX_n_CTL_REG",
	"ECPRI_ORAN_XTOR_TX_n_CMD_m_k",
	"ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG",
	"ECPRI_ORAN_XTOR_RX_n_ERROR_REG",
	"ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_1",
	"ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_0",
	"ECPRI_ORAN_XTOR_RX_n_KBYTE_CNT_REG",
	"ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1",
	"ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0",
	"ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG",
	"ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_1_REG",
	"ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_2_REG",
	"ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_3_REG",
	"ECPRI_ORAN_XTOR_TX_n_BACKPRESSURE_CNT_REG",
	"ECPRI_ORAN_XTOR_TX_n_PKT_CNT_REG",
	"ECPRI_OXTOR_OXTOR_MAX"
};

ecpriss_oxtor_hal_context_s ecpriss_oxtor_hal_ctx;

static int ecpri_oxtor_global_cfg_init(void)
{
	ecpri_global_hwio_def_ecpri_global_xtor_cfg_u xtor_global_cfg;

	memset(&xtor_global_cfg,0,
			sizeof(ecpri_global_hwio_def_ecpri_global_xtor_cfg_u));

	/*Enable ORAN Xactor*/
	xtor_global_cfg.def.oran_xtor_en = true;

	/*Rx*/
	xtor_global_cfg.def.oran_xtor_rx_reset_0 = true;
	xtor_global_cfg.def.oran_xtor_rx_reset_1 = true;
	xtor_global_cfg.def.oran_xtor_rx_reset_2 = true;
	xtor_global_cfg.def.oran_xtor_rx_reset_3 = true;

	/*Tx*/
	xtor_global_cfg.def.oran_xtor_tx_reset_0 = true;
	xtor_global_cfg.def.oran_xtor_tx_reset_1 = true;
	xtor_global_cfg.def.oran_xtor_tx_reset_2 = true;
	xtor_global_cfg.def.oran_xtor_tx_reset_3 = true;

	ecpriss_oxtor_hal_write_reg_n_fields(ECPRI_OXTOR_REG_TYPE_GLOBAL,
			ECPRI_GLOBAL_XTOR_CFG, 0, &xtor_global_cfg);

	/*ecpriss_oxtor_hal_read_reg_n_fields(ECPRI_OXTOR_REG_TYPE_GLOBAL,
			ECPRI_GLOBAL_XTOR_CFG, 0, &xtor_global_cfg);
	*/


	/*Rx*/
	xtor_global_cfg.def.oran_xtor_rx_reset_0 = 0;
	xtor_global_cfg.def.oran_xtor_rx_reset_1 = 0;
	xtor_global_cfg.def.oran_xtor_rx_reset_2 = 0;
	xtor_global_cfg.def.oran_xtor_rx_reset_3 = 0;

	/*Tx*/
	xtor_global_cfg.def.oran_xtor_tx_reset_0 = 0;
	xtor_global_cfg.def.oran_xtor_tx_reset_1 = 0;
	xtor_global_cfg.def.oran_xtor_tx_reset_2 = 0;
	xtor_global_cfg.def.oran_xtor_tx_reset_3 = 0;

	ecpriss_oxtor_hal_write_reg_n_fields(ECPRI_OXTOR_REG_TYPE_GLOBAL,
			ECPRI_GLOBAL_XTOR_CFG, 0, &xtor_global_cfg);

	return 0;
}

int ecpriss_oxtor_hal_ctx_init(void )
{
	ecpriss_oxtor_hal_ctx.hw_type = ECPRISS_OXTOR_HW_v1_0;
	/* ecpriss_oxtor_hal_ctx.base = ECPRI_ORAN_XTOR_REG_BASE; */
	/* Need to do ioremap and also need to take care of */
	/* ECPRI_GLOBAL_XTOR_CFG TODO: Mayank*/

	ecpriss_oxtor_hal_ctx.phy_base = ECPRI_OXTOR_BASE;
	ecpriss_oxtor_hal_ctx.base     = ioremap(ecpriss_oxtor_hal_ctx.phy_base,
			ECPRI_OXTOR_BASE_SIZE);


	ecpriss_oxtor_hal_ctx.phy_global_base = ECPRI_OXTOR_GLOBAL_BASE;
	ecpriss_oxtor_hal_ctx.global_base     = ioremap(
			ecpriss_oxtor_hal_ctx.phy_global_base,
			ECPRI_OXTOR_GLOBAL_BASE_SIZE);


	ecpri_oxtor_global_cfg_init();

	ecpriss_oxtor_hal_ctx.init = 1;
	return 0;
}

/*
 * ecpriss_oxtor_hal_reg_name_str() - returns string that represent the register
 * @reg_name: [in] register name
 */
const char *ecpriss_oxtor_hal_reg_name_str(
		enum ecpriss_oxtor_hal_reg_name reg_name)
{
	if (reg_name < 0 || reg_name >= ECPRI_OXTOR_OXTOR_MAX) {
		pr_err("requested name of invalid reg=%d\n", reg_name);
		return "Invalid Register";
	}

	return ecpriss_oxtor_hal_reg_name_to_str[reg_name];
}

	static void ecpriss_oxtor_hal_reg_construct_global_oxtor_cfg
(enum ecpriss_oxtor_hal_reg_name reg, const void *fields, u32* val)
{
	ecpri_global_hwio_def_ecpri_global_xtor_cfg_s *oran_xtor_global_cfg
		= (ecpri_global_hwio_def_ecpri_global_xtor_cfg_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			oran_xtor_global_cfg->oran_xtor_en,
			HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_EN_SHFT,
			HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_EN_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			oran_xtor_global_cfg->oran_xtor_rx_reset_0,
			HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_RX_RESET_0_SHFT,
			HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_RX_RESET_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			oran_xtor_global_cfg->oran_xtor_rx_reset_1,
			HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_RX_RESET_1_SHFT,
			HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_RX_RESET_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			oran_xtor_global_cfg->oran_xtor_rx_reset_2,
			HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_RX_RESET_2_SHFT,
			HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_RX_RESET_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			oran_xtor_global_cfg->oran_xtor_rx_reset_3,
			HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_RX_RESET_3_SHFT,
			HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_RX_RESET_3_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			oran_xtor_global_cfg->oran_xtor_tx_reset_0,
			HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_TX_RESET_0_SHFT,
			HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_TX_RESET_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			oran_xtor_global_cfg->oran_xtor_tx_reset_1,
			HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_TX_RESET_1_SHFT,
			HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_TX_RESET_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			oran_xtor_global_cfg->oran_xtor_tx_reset_2,
			HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_TX_RESET_2_SHFT,
			HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_TX_RESET_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			oran_xtor_global_cfg->oran_xtor_tx_reset_3,
			HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_TX_RESET_3_SHFT,
			HWIO_ECPRI_GLOBAL_XTOR_CFG_ORAN_XTOR_TX_RESET_3_BMSK);

	return;
}


	static void ecpriss_oxtor_hal_reg_construct_rx_kbyte_cnt_ctl
(enum ecpriss_oxtor_hal_reg_name reg, const void *fields, u32* val)
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_kbyte_cnt_ctl_s
		*rx_kbyte_cnt_ctl =
	(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_kbyte_cnt_ctl_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			rx_kbyte_cnt_ctl->en,
			HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL_EN_SHFT,
			HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL_EN_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			rx_kbyte_cnt_ctl->clr,
			HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL_CLR_SHFT,
			HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL_CLR_BMSK);

	return;
}


	static void ecpriss_oxtor_hal_reg_construct_qtimer_offset_msb
(enum ecpriss_oxtor_hal_reg_name reg, const void *fields, u32* val)
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_qtimer_offset_msb_s
		*qtimer_offset_msb_s =
	(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_qtimer_offset_msb_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
		qtimer_offset_msb_s->offset_msbs,
		HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB_OFFSET_MSBS_SHFT,
		HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB_OFFSET_MSBS_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
		qtimer_offset_msb_s->offset_sign_bit,
		HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB_OFFSET_SIGN_BIT_SHFT,
		HWIO_ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB_OFFSET_SIGN_BIT_BMSK);

	return;
}


	static void ecpriss_oxtor_hal_reg_construct_rx_n_max_latency_expected
(enum ecpriss_oxtor_hal_reg_name reg, const void *fields, u32* val)
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_max_latency_expected_s
		*rx_n_max_latency_expected_s =
(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_max_latency_expected_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	rx_n_max_latency_expected_s->max_latency,
	HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LATENCY_EXPECTED_MAX_LATENCY_SHFT,
	HWIO_ECPRI_ORAN_XTOR_RX_n_MAX_LATENCY_EXPECTED_MAX_LATENCY_BMSK);

	return;
}
	static void ecpriss_oxtor_hal_reg_construct_rx_n_ctl_reg
(enum ecpriss_oxtor_hal_reg_name reg, const void *fields, u32* val)
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_ctl_reg_s *rx_n_ctl_reg_s
	= (ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_ctl_reg_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			rx_n_ctl_reg_s->tgt_rx_err_en,
			HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_TGT_RX_ERR_EN_SHFT,
			HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_TGT_RX_ERR_EN_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			rx_n_ctl_reg_s->data_err_en,
			HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_DATA_ERR_EN_SHFT,
			HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_DATA_ERR_EN_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			rx_n_ctl_reg_s->time_err_en,
			HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_TIME_ERR_EN_SHFT,
			HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_TIME_ERR_EN_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			rx_n_ctl_reg_s->len_err_en,
			HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_LEN_ERR_EN_SHFT,
			HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_LEN_ERR_EN_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			rx_n_ctl_reg_s->crc_err_en,
			HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_CRC_ERR_EN_SHFT,
			HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_CRC_ERR_EN_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			rx_n_ctl_reg_s->latency_err_en ,
			HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_LATENCY_ERR_EN_SHFT,
			HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_LATENCY_ERR_EN_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			rx_n_ctl_reg_s->seqnum_err_en ,
			HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_SEQNUM_ERR_EN_SHFT,
			HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_SEQNUM_ERR_EN_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
		rx_n_ctl_reg_s->avg_latency_clear ,
		HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_AVG_LATENCY_CLEAR_SHFT,
		HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_AVG_LATENCY_CLEAR_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
		rx_n_ctl_reg_s->min_latency_clear ,
		HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_MIN_LATENCY_CLEAR_SHFT,
		HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_MIN_LATENCY_CLEAR_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
		rx_n_ctl_reg_s->max_latency_clear ,
		HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_MAX_LATENCY_CLEAR_SHFT,
		HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_MAX_LATENCY_CLEAR_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			rx_n_ctl_reg_s->min_bw_clear ,
			HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_MIN_BW_CLEAR_SHFT,
			HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_MIN_BW_CLEAR_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			rx_n_ctl_reg_s->max_bw_clear  ,
			HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_MAX_BW_CLEAR_SHFT,
			HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_MAX_BW_CLEAR_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			rx_n_ctl_reg_s->min_bw_en  ,
			HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_MIN_BW_EN_SHFT,
			HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_MIN_BW_EN_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			rx_n_ctl_reg_s->max_bw_en   ,
			HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_MAX_BW_EN_SHFT,
			HWIO_ECPRI_ORAN_XTOR_RX_n_CTL_REG_MAX_BW_EN_BMSK);

	return;
}

	static void ecpriss_oxtor_hal_reg_construct_rx_n_error_status_dump_reg
(enum ecpriss_oxtor_hal_reg_name reg, const void *fields, u32* val)
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_status_dump_reg_s
	*dump_reg_s =
(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_status_dump_reg_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	dump_reg_s->reset_error_dump,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_RESET_ERROR_DUMP_SHFT,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_RESET_ERROR_DUMP_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	dump_reg_s->tgt_rx_err,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_TGT_RX_ERR_SHFT ,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_TGT_RX_ERR_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	dump_reg_s->data_err,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_DATA_ERR_SHFT ,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_DATA_ERR_BMSK );

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	dump_reg_s->time_err,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_TIME_ERR_SHFT,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_TIME_ERR_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	dump_reg_s->len_err,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_LEN_ERR_SHFT,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_LEN_ERR_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	dump_reg_s->crc_err,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_CRC_ERR_SHFT,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_CRC_ERR_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	dump_reg_s->latency_err,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_LATENCY_ERR_SHFT,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_LATENCY_ERR_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	dump_reg_s->seqnum_err,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_SEQNUM_ERR_SHFT ,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_SEQNUM_ERR_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	dump_reg_s->xu_num,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_XU_NUM_SHFT ,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG_XU_NUM_BMSK );

	return;
}

	static void ecpriss_oxtor_hal_reg_construct_tx_n_ctl_reg
(enum ecpriss_oxtor_hal_reg_name reg, const void *fields, u32 *val)
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_ctl_reg_s
	*tx_n_ctl_reg_s =
	(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_ctl_reg_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	tx_n_ctl_reg_s->wrap_en,
	HWIO_ECPRI_ORAN_XTOR_TX_n_CTL_REG_WRAP_EN_SHFT,
	HWIO_ECPRI_ORAN_XTOR_TX_n_CTL_REG_WRAP_EN_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	tx_n_ctl_reg_s->rd_idx_wrap_cnt_saturate_en,
	HWIO_ECPRI_ORAN_XTOR_TX_n_CTL_REG_RD_IDX_WRAP_CNT_SATURATE_EN_SHFT,
	HWIO_ECPRI_ORAN_XTOR_TX_n_CTL_REG_RD_IDX_WRAP_CNT_SATURATE_EN_BMSK);

	return;
}

static void ecpriss_oxtor_hal_reg_parse_dummy(
		enum ecpriss_oxtor_hal_reg_name reg,
		void *fields,
		u32 val)
{
	return;
}

static void ecpriss_oxtor_hal_reg_parse_global_oxtor_cfg(
		enum ecpriss_oxtor_hal_reg_name reg,
		void *fields,
		u32 val)
{
	return;
}


static void ecpriss_oxtor_hal_reg_construct_tx_n_cmd_m_k
(enum ecpriss_oxtor_hal_reg_name reg, const void *fields, u32* val)
{

	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_cmd_m_k_s *tx_cmd
	= (ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_cmd_m_k_s *)fields;


	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			tx_cmd->data,
			HWIO_ECPRI_ORAN_XTOR_TX_n_CMD_m_k_DATA_SHFT,
			HWIO_ECPRI_ORAN_XTOR_TX_n_CMD_m_k_DATA_BMSK);

	return;
}

	static void ecpriss_oxtor_hal_reg_construct_tx_n_data_idxs_reg
(enum ecpriss_oxtor_hal_reg_name reg, const void *fields, u32* val)
{

	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_data_idxs_reg_s
	*data_idxs_reg_s =
	(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_data_idxs_reg_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			data_idxs_reg_s->rd_idx,
			HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_RD_IDX_SHFT,
			HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_RD_IDX_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			data_idxs_reg_s->wr_idx,
			HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_WR_IDX_SHFT,
			HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_WR_IDX_BMSK);

	return;
}
#ifdef NO_CALLED
	static void ecpriss_oxtor_hal_reg_parse_tx_n_data_idxs_reg
(enum ecpriss_oxtor_hal_reg_name reg, const void *fields, u32 val)
{

	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_data_idxs_reg_s
	*data_idxs_reg_s =
	(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_data_idxs_reg_s *)fields;

	data_idxs_reg_s->rd_idx = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_RD_IDX_SHFT,
			HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_RD_IDX_BMSK);

	data_idxs_reg_s->wr_idx = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_WR_IDX_SHFT,
			HWIO_ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG_WR_IDX_BMSK);

	return;
}
#endif


	static void ecpriss_oxtor_hal_reg_construct_rx_n_error_reg
(enum ecpriss_oxtor_hal_reg_name reg, const void *fields, u32* val)
{

	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_reg_s
	*error_reg_s =
	(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_reg_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
		error_reg_s->reset_err_status,
		HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_RESET_ERR_STATUS_SHFT,
		HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_RESET_ERR_STATUS_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
		error_reg_s->tgt_rx_err,
		HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_TGT_RX_ERR_SHFT,
		HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_TGT_RX_ERR_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
		error_reg_s->data_err,
		HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_DATA_ERR_SHFT,
		HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_DATA_ERR_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
		error_reg_s->time_err,
		HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_TIME_ERR_SHFT,
		HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_TIME_ERR_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
		error_reg_s->len_err,
		HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_LEN_ERR_SHFT,
		HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_LEN_ERR_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
		error_reg_s->crc_err,
		HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_CRC_ERR_SHFT,
		HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_CRC_ERR_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
		error_reg_s->latency_err,
		HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_LATENCY_ERR_SHFT,
		HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_LATENCY_ERR_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
		error_reg_s->seqnum_err,
		HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_SEQNUM_ERR_SHFT,
		HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_REG_SEQNUM_ERR_BMSK);

	return;
}

static void ecpriss_oxtor_hal_reg_construct_rx_kbyte_cnt_qtimer_delta_1
(enum ecpriss_oxtor_hal_reg_name reg, const void *fields, u32* val)
{

	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_kbyte_cnt_qtimer_delta_1_s
	*qtimer_delta_1 =
(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_kbyte_cnt_qtimer_delta_1_s *)
fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	qtimer_delta_1->qtimer_msb,
	HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_1_QTIMER_MSB_SHFT,
	HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_1_QTIMER_MSB_BMSK);

}
static void ecpriss_oxtor_hal_reg_construct_rx_kbyte_cnt_qtimer_delta_0
(enum ecpriss_oxtor_hal_reg_name reg, const void *fields, u32* val)
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_kbyte_cnt_qtimer_delta_0_s
	*qtimer_delta_0 =
(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_kbyte_cnt_qtimer_delta_0_s *)
fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	qtimer_delta_0->qtimer_lsb,
	HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_0_QTIMER_LSB_SHFT,
	HWIO_ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_0_QTIMER_LSB_BMSK);

	return;
}
	static void ecpriss_oxtor_hal_reg_construct_rx_n_kbyte_cnt_reg
(enum ecpriss_oxtor_hal_reg_name reg, const void *fields, u32* val)
{

	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_kbyte_cnt_reg_s
	*kbyte_cnt_reg =
	(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_kbyte_cnt_reg_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			kbyte_cnt_reg->kbyte_cnt,
			HWIO_ECPRI_ORAN_XTOR_RX_n_KBYTE_CNT_REG_KBYTE_CNT_SHFT,
			HWIO_ECPRI_ORAN_XTOR_RX_n_KBYTE_CNT_REG_KBYTE_CNT_BMSK);

	return;
}
	static void ecpriss_oxtor_hal_reg_construct_rx_n_err_counters_1
(enum ecpriss_oxtor_hal_reg_name reg, const void *fields, u32* val)
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_err_counters_1_s
	*err_counters_1 =
(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_err_counters_1_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	err_counters_1->crc_err_count,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1_CRC_ERR_COUNT_SHFT,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1_CRC_ERR_COUNT_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	err_counters_1->data_err_count,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1_DATA_ERR_COUNT_SHFT,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1_DATA_ERR_COUNT_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	err_counters_1->latency_err_count,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1_LATENCY_ERR_COUNT_SHFT,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1_LATENCY_ERR_COUNT_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	err_counters_1->overall_err_count,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1_OVERALL_ERR_COUNT_SHFT,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1_OVERALL_ERR_COUNT_BMSK);

	return;
}
	static void ecpriss_oxtor_hal_reg_construct_rx_n_err_counters_0
(enum ecpriss_oxtor_hal_reg_name reg, const void *fields, u32* val)
{

	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_err_counters_0_s
	*err_counters_0 =
(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_err_counters_0_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	err_counters_0->seqnum_err_count,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0_SEQNUM_ERR_COUNT_SHFT,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0_SEQNUM_ERR_COUNT_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	err_counters_0->len_err_count,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0_LEN_ERR_COUNT_SHFT,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0_LEN_ERR_COUNT_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	err_counters_0->time_err_count,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0_TIME_ERR_COUNT_SHFT,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0_TIME_ERR_COUNT_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	err_counters_0->tgt_rx_err_count,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0_TGT_RX_ERR_COUNT_SHFT,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0_TGT_RX_ERR_COUNT_BMSK);

	return;
}
static void ecpriss_oxtor_hal_reg_construct_rx_n_error_dump_0_reg
(enum ecpriss_oxtor_hal_reg_name reg, const void *fields, u32* val)
{

	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_0_reg_s
	*error_dump_0_reg =
(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_0_reg_s *)fields;


	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	error_dump_0_reg->ecpri_msg_type,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_ECPRI_MSG_TYPE_SHFT,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_ECPRI_MSG_TYPE_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	error_dump_0_reg->src_tx,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_SRC_TX_SHFT,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_SRC_TX_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	error_dump_0_reg->tgt_rx,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_TGT_RX_SHFT,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_TGT_RX_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	error_dump_0_reg->seqnum,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_SEQNUM_SHFT,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_SEQNUM_BMSK);


	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	error_dump_0_reg->xu_num,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_XU_NUM_SHFT,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG_XU_NUM_BMSK);

	return;
}
static void ecpriss_oxtor_hal_reg_construct_rx_n_error_dump_1_reg
(enum ecpriss_oxtor_hal_reg_name reg, const void *fields, u32* val)
{

	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_1_reg_s
	*error_dump_1_reg =
(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_1_reg_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	error_dump_1_reg->ecpri_payload_size,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_1_REG_ECPRI_PAYLOAD_SIZE_SHFT,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_1_REG_ECPRI_PAYLOAD_SIZE_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	error_dump_1_reg->ecpri_pcid,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_1_REG_ECPRI_PCID_SHFT,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_1_REG_ECPRI_PCID_BMSK);

	return;
}
static void ecpriss_oxtor_hal_reg_construct_rx_n_error_dump_2_reg
(enum ecpriss_oxtor_hal_reg_name reg, const void *fields, u32* val)
{

	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_2_reg_s
	*error_dump_2_reg =
(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_2_reg_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	error_dump_2_reg->timestamp,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_2_REG_TIMESTAMP_SHFT,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_2_REG_TIMESTAMP_BMSK);

	return;
}
static void ecpriss_oxtor_hal_reg_construct_rx_n_error_dump_3_reg
(enum ecpriss_oxtor_hal_reg_name reg, const void *fields, u32* val)
{

	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_3_reg_s
	*error_dump_3_reg =
(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_3_reg_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	error_dump_3_reg->init_data,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_3_REG_INIT_DATA_SHFT,
	HWIO_ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_3_REG_INIT_DATA_BMSK);

	return;
}
	static void ecpriss_oxtor_hal_reg_construct_tx_n_backpressure_cnt_reg
(enum ecpriss_oxtor_hal_reg_name reg, const void *fields, u32* val)
{

	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_backpressure_cnt_reg_s
	*backpressure_cnt_reg =
(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_backpressure_cnt_reg_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	backpressure_cnt_reg->backpressure_cnt,
	HWIO_ECPRI_ORAN_XTOR_TX_n_BACKPRESSURE_CNT_REG_BACKPRESSURE_CNT_SHFT,
	HWIO_ECPRI_ORAN_XTOR_TX_n_BACKPRESSURE_CNT_REG_BACKPRESSURE_CNT_BMSK);

	return;
}

static void ecpriss_oxtor_hal_reg_construct_tx_n_pkt_cnt_reg
(enum ecpriss_oxtor_hal_reg_name reg, const void *fields, u32* val)
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_pkt_cnt_reg_s
	*tx_n_pkt_cnt_reg =
(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_pkt_cnt_reg_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
		tx_n_pkt_cnt_reg->pkt_cnt,
		HWIO_ECPRI_ORAN_XTOR_TX_n_PKT_CNT_REG_PKT_CNT_SHFT,
		HWIO_ECPRI_ORAN_XTOR_TX_n_PKT_CNT_REG_PKT_CNT_BMSK);

	return;
}

	static void ecpriss_oxtor_hal_reg_parse_tx_n_pkt_cnt_reg
(enum ecpriss_oxtor_hal_reg_name reg, void *fields, u32 val)
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_pkt_cnt_reg_s
	*tx_n_pkt_cnt_reg =
	(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_pkt_cnt_reg_s *)fields;

	tx_n_pkt_cnt_reg->pkt_cnt = ECPRISS_HAL_GETFIELD_FROM_REG( val,
		HWIO_ECPRI_ORAN_XTOR_TX_n_PKT_CNT_REG_PKT_CNT_SHFT,
		HWIO_ECPRI_ORAN_XTOR_TX_n_PKT_CNT_REG_PKT_CNT_BMSK);

	return;
}


static void ecpriss_oxtor_hal_reg_construct_rx_n_pkt_cnt_reg
(enum ecpriss_oxtor_hal_reg_name reg, const void *fields, u32* val)
{

	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_pkt_cnt_reg_s
	*rx_n_pkt_cnt_reg =
	(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_pkt_cnt_reg_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			rx_n_pkt_cnt_reg->pkt_cnt,
			HWIO_ECPRI_ORAN_XTOR_RX_n_PKT_CNT_REG_PKT_CNT_SHFT,
			HWIO_ECPRI_ORAN_XTOR_RX_n_PKT_CNT_REG_PKT_CNT_BMSK);

	return;
}

	static void ecpriss_oxtor_hal_reg_parse_rx_n_pkt_cnt_reg
(enum ecpriss_oxtor_hal_reg_name reg, void *fields, u32 val)
{


	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_pkt_cnt_reg_s
	*rx_n_pkt_cnt_reg
	= (ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_pkt_cnt_reg_s *)fields;


	rx_n_pkt_cnt_reg->pkt_cnt = ECPRISS_HAL_GETFIELD_FROM_REG( val,
			HWIO_ECPRI_ORAN_XTOR_RX_n_PKT_CNT_REG_PKT_CNT_SHFT,
			HWIO_ECPRI_ORAN_XTOR_RX_n_PKT_CNT_REG_PKT_CNT_BMSK);

	return;
}


	static void ecpriss_oxtor_hal_reg_construct_tx_n_rd_idx_wrap_cnt_reg
(enum ecpriss_oxtor_hal_reg_name reg, const void *fields, u32* val)
{

	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_rd_idx_wrap_cnt_s
	*wrap_cnt =
(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_rd_idx_wrap_cnt_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
	wrap_cnt->rd_idx_wrap_cnt,
	HWIO_ECPRI_ORAN_XTOR_TX_n_RD_IDX_WRAP_CNT_RD_IDX_WRAP_CNT_SHFT,
	HWIO_ECPRI_ORAN_XTOR_TX_n_RD_IDX_WRAP_CNT_RD_IDX_WRAP_CNT_BMSK);

	return;
}

static void ecpriss_oxtor_hal_reg_parse_tx_n_rd_idx_wrap_cnt_reg
(enum ecpriss_oxtor_hal_reg_name reg, void *fields, u32 val)
{

	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_rd_idx_wrap_cnt_s
	*wrap_cnt =
(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_rd_idx_wrap_cnt_s *)fields;
	wrap_cnt->rd_idx_wrap_cnt = ECPRISS_HAL_GETFIELD_FROM_REG( val,
	HWIO_ECPRI_ORAN_XTOR_TX_n_RD_IDX_WRAP_CNT_RD_IDX_WRAP_CNT_SHFT,
	HWIO_ECPRI_ORAN_XTOR_TX_n_RD_IDX_WRAP_CNT_RD_IDX_WRAP_CNT_BMSK);

	return;
}

static struct ecpriss_oxtor_hal_reg_obj ecpriss_oxtor_hal_reg_objs[
	ECPRISS_OXTOR_HW_MAX][ECPRI_OXTOR_OXTOR_MAX] = {

	[ECPRISS_OXTOR_HW_v1_0][ECPRI_GLOBAL_XTOR_CFG] = {
		ecpriss_oxtor_hal_reg_construct_global_oxtor_cfg,
		ecpriss_oxtor_hal_reg_parse_global_oxtor_cfg,
		0x92100000,0x10, 0, 0, 0, 0, 0, 0},
	[ECPRISS_OXTOR_HW_v1_0][ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL] = {
		ecpriss_oxtor_hal_reg_construct_rx_kbyte_cnt_ctl,
		ecpriss_oxtor_hal_reg_parse_dummy,
		0x09228000,  0x1030, 0, 0, 0, 0, 0, 0},
	[ECPRISS_OXTOR_HW_v1_0][ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB] = {
		ecpriss_oxtor_hal_reg_construct_qtimer_offset_msb,
		ecpriss_oxtor_hal_reg_parse_dummy,
		0x09228000, 0x1030, 0, 0, 0, 0, 0, 0},
	[ECPRISS_OXTOR_HW_v1_0][ECPRI_ORAN_XTOR_RX_n_MAX_LATENCY_EXPECTED] = {
		ecpriss_oxtor_hal_reg_construct_rx_n_max_latency_expected,
		ecpriss_oxtor_hal_reg_parse_dummy,
		0x09228000,  0x1164, 0x200, 0, 0, 0, 0, 0},
	[ECPRISS_OXTOR_HW_v1_0][ECPRI_ORAN_XTOR_RX_n_CTL_REG] = {
		ecpriss_oxtor_hal_reg_construct_rx_n_ctl_reg,
		ecpriss_oxtor_hal_reg_parse_dummy,
		0x09228000,  0x00001000, 0x200, 0, 0, 0, 0, 0},
	[ECPRISS_OXTOR_HW_v1_0][ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG] = {
		ecpriss_oxtor_hal_reg_construct_rx_n_error_status_dump_reg,
		ecpriss_oxtor_hal_reg_parse_dummy,
		0x09228000,  0x1020, 0x200, 0, 0, 0, 0, 0},
	[ECPRISS_OXTOR_HW_v1_0][ECPRI_ORAN_XTOR_TX_n_CTL_REG] = {
		ecpriss_oxtor_hal_reg_construct_tx_n_ctl_reg,
		ecpriss_oxtor_hal_reg_parse_dummy,
		0x09228000 , 0x0, 0x300, 0, 0, 0, 0, 0},
	[ECPRISS_OXTOR_HW_v1_0][ECPRI_ORAN_XTOR_TX_n_CMD_m_k] = {
		ecpriss_oxtor_hal_reg_construct_tx_n_cmd_m_k,
		ecpriss_oxtor_hal_reg_parse_dummy,
		0x09228000,  0x00000010, 0x300, 0, 0, 0, 0x10, 0x4},
	[ECPRISS_OXTOR_HW_v1_0][ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG] = {
		ecpriss_oxtor_hal_reg_construct_tx_n_data_idxs_reg,
		ecpriss_oxtor_hal_reg_parse_dummy,
		0x09228000 , 0x00000004, 0x300, 0, 0, 0, 0, 0},
	[ECPRISS_OXTOR_HW_v1_0][ECPRI_ORAN_XTOR_RX_n_ERROR_REG] = {
		ecpriss_oxtor_hal_reg_construct_rx_n_error_reg,
		ecpriss_oxtor_hal_reg_parse_dummy,
		0x09228000, 0x1004, 0x200, 0, 0, 0, 0, 0},
	[ECPRISS_OXTOR_HW_v1_0][ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_1] = {
		ecpriss_oxtor_hal_reg_construct_rx_kbyte_cnt_qtimer_delta_1,
		ecpriss_oxtor_hal_reg_parse_dummy,
		0x09228000,  0x1038, 0, 0, 0, 0, 0, 0},
	[ECPRISS_OXTOR_HW_v1_0][ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_0] = {
		ecpriss_oxtor_hal_reg_construct_rx_kbyte_cnt_qtimer_delta_0,
		ecpriss_oxtor_hal_reg_parse_dummy,
		0x09228000,  0x1034, 0, 0, 0, 0, 0, 0},
	[ECPRISS_OXTOR_HW_v1_0][ECPRI_ORAN_XTOR_RX_n_KBYTE_CNT_REG] = {
		ecpriss_oxtor_hal_reg_construct_rx_n_kbyte_cnt_reg,
		ecpriss_oxtor_hal_reg_parse_dummy,
		0x09228000,  0x0000102C, 0x200, 0, 0, 0, 0, 0},
	[ECPRISS_OXTOR_HW_v1_0][ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1] = {
		ecpriss_oxtor_hal_reg_construct_rx_n_err_counters_1,
		ecpriss_oxtor_hal_reg_parse_dummy,
		0x09228000,  0x1160, 0x200, 0, 0, 0, 0, 0},
	[ECPRISS_OXTOR_HW_v1_0][ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0] = {
		ecpriss_oxtor_hal_reg_construct_rx_n_err_counters_0,
		ecpriss_oxtor_hal_reg_parse_dummy,
		0x09228000,  0x115C, 0x200, 0, 0, 0, 0, 0},
	[ECPRISS_OXTOR_HW_v1_0][ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG] = {
		ecpriss_oxtor_hal_reg_construct_rx_n_error_dump_0_reg,
		ecpriss_oxtor_hal_reg_parse_dummy,
		0x09228000,  0x1010, 0x00000200, 0, 0, 0, 0x40000, 0},
	[ECPRISS_OXTOR_HW_v1_0][ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_1_REG] = {
		ecpriss_oxtor_hal_reg_construct_rx_n_error_dump_1_reg,
		ecpriss_oxtor_hal_reg_parse_dummy,
		0x09228000,  0x00001014, 0x200, 0, 0, 0, 0, 0},
	[ECPRISS_OXTOR_HW_v1_0][ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_2_REG] = {
		ecpriss_oxtor_hal_reg_construct_rx_n_error_dump_2_reg,
		ecpriss_oxtor_hal_reg_parse_dummy,
		0x09228000,  0x1018, 0x200, 0, 0, 0, 0, 0},
	[ECPRISS_OXTOR_HW_v1_0][ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_3_REG] = {
		ecpriss_oxtor_hal_reg_construct_rx_n_error_dump_3_reg,
		ecpriss_oxtor_hal_reg_parse_dummy,
		0x09228000,  0x101C, 0x200, 0, 0, 0, 0, 0},
	[ECPRISS_OXTOR_HW_v1_0][ECPRI_ORAN_XTOR_TX_n_BACKPRESSURE_CNT_REG] = {
		ecpriss_oxtor_hal_reg_construct_tx_n_backpressure_cnt_reg,
		ecpriss_oxtor_hal_reg_parse_dummy,
		0x09228000,  0x0000000C, 0x300, 0, 0, 0, 0, 0},
	[ECPRISS_OXTOR_HW_v1_0][ECPRI_ORAN_XTOR_TX_n_PKT_CNT_REG] = {
		ecpriss_oxtor_hal_reg_construct_tx_n_pkt_cnt_reg,
		ecpriss_oxtor_hal_reg_parse_tx_n_pkt_cnt_reg,
		0x09228000 , 0x00000008, 0x300, 0, 0, 0, 0, 0},
	[ECPRISS_OXTOR_HW_v1_0][ECPRI_ORAN_XTOR_RX_n_PKT_CNT_REG] = {
		ecpriss_oxtor_hal_reg_construct_rx_n_pkt_cnt_reg,
		ecpriss_oxtor_hal_reg_parse_rx_n_pkt_cnt_reg,
		0x09228000 , 0x01008, 0x200, 0, 0, 0, 0, 0},
	[ECPRISS_OXTOR_HW_v1_0][ECPRI_ORAN_XTOR_TX_n_RD_IDX_WRAP_CNT] = {
		ecpriss_oxtor_hal_reg_construct_tx_n_rd_idx_wrap_cnt_reg,
		ecpriss_oxtor_hal_reg_parse_tx_n_rd_idx_wrap_cnt_reg,
		0x09228000 , 0x00000290, 0x300, 0, 0, 0, 0, 0},
};


uint32_t ecpri_oxtor_hal_reg_read(ecpri_oxtor_hal_reg_type_e reg_type,
		u32 offset, u32 *val)
{
	if(!val)
	{
		pr_err("Null pointer\n");
		return -1;
	}
	if(reg_type == ECPRI_OXTOR_REG_TYPE_GLOBAL) {

		*val  = ioread32(ecpriss_oxtor_hal_ctx.global_base + offset);
	}
	else if(reg_type == ECPRI_OXTOR_REG_TYPE_BASE) {

		*val = ioread32(ecpriss_oxtor_hal_ctx.base + offset);
	}

	return 0;
}

void ecpri_oxtor_hal_reg_write(ecpri_oxtor_hal_reg_type_e reg_type,
		u32 offset, u32 val)
{
	if(reg_type == ECPRI_OXTOR_REG_TYPE_GLOBAL) {

		iowrite32(val, ecpriss_oxtor_hal_ctx.global_base + offset);
	}
	else if(reg_type == ECPRI_OXTOR_REG_TYPE_BASE) {

		iowrite32(val, ecpriss_oxtor_hal_ctx.base + offset);
	}
	return;
}

/*
 * ecpriss_oxtor_hal_read_reg_n() - Get n parameterized reg value
 */
u32 ecpriss_oxtor_hal_read_reg_n(enum ecpriss_oxtor_hal_reg_name reg, u32 n)
{
	u32 offset;
	int val=0;
	u32 base;
	if (reg >= ECPRI_OXTOR_OXTOR_MAX) {
		pr_err("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return -EINVAL;
	}

	pr_info(
	"read from %s n=%u\n",
	ecpriss_oxtor_hal_reg_name_str(reg), n);

	base =
	ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].base;
	offset =
	ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].offset;

	if (offset == -1) {
		pr_err("Read access to obsolete reg=%s\n",
				ecpriss_oxtor_hal_reg_name_str(reg));
		WARN_ON(1);
		return -EPERM;
	}
	offset +=
ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].n_ofst * n;
	base +=
	offset;
	val =ioread32(&base);
	return val;
}



/*
 * ecpriss_oxtor_hal_read_reg_mn() - Get mn parameterized reg value
 */
u32 ecpriss_oxtor_hal_read_reg_mn(enum ecpriss_oxtor_hal_reg_name reg, u32 m,
		u32 n)
{
	u32 offset;
	int val=0;
	u32 base;
	if (reg >= ECPRI_OXTOR_OXTOR_MAX) {
		pr_err("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return -EINVAL;
	}

	pr_info("read %s m=%u n=%u\n",
			ecpriss_oxtor_hal_reg_name_str(reg), m, n);

	base =
	ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].base;
	offset =
	ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].offset;
	if (offset == -1) {
		pr_err("Read access to obsolete reg=%s\n",
				ecpriss_oxtor_hal_reg_name_str(reg));
		WARN_ON_ONCE(1);
		return -EPERM;
	}

	offset +=
ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].m_ofst * m;
	offset +=
ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].n_ofst * n;
	base += offset;
	val =ioread32(&base);
	return val;
}



/*
 * ecpriss_oxtor_hal_write_reg_mn() - Write to m/n parameterized reg a raw value
 */
void ecpriss_oxtor_hal_write_reg_mn(enum ecpriss_oxtor_hal_reg_name reg, u32 m,
		u32 n, u32 val)
{
	u32 offset;
	u32 base;

	if (reg >= ECPRI_OXTOR_OXTOR_MAX) {
		pr_err("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return;
	}

	pr_info("write to %s m=%u n=%u val=%u\n",
			ecpriss_oxtor_hal_reg_name_str(reg), m, n, val);

	base =
	ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].base;
	offset =
	ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].offset;
	if (offset == -1) {
		pr_err("Write access to obsolete reg=%s\n",
				ecpriss_oxtor_hal_reg_name_str(reg));
		WARN_ON(1);
		return;
	}

	offset +=
ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].m_ofst * m;
	offset +=
ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].n_ofst * n;
	base += offset;
	iowrite32(val, &base);
	return;
}

/*
 * ecpriss_oxtor_hal_write_reg_mn() - Write to m/n parameterized reg a raw value
 */
void ecpriss_oxtor_hal_write_reg_mn_fields(enum ecpriss_oxtor_hal_reg_name reg,
		u32 m, u32 n, void *fields)
{
	u32 offset;
	u32 val = 0;
	u32 base;
	if (reg >= ECPRI_OXTOR_OXTOR_MAX) {
		pr_err("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return;
	}

	pr_info("write to %s m=%u n=%u val=%u\n",
		ecpriss_oxtor_hal_reg_name_str(reg), m, n, val);

	base =
	ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].base;
	offset =
	ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].offset;
	if (offset == -1) {
		pr_err("Write access to obsolete reg=%s\n",
				ecpriss_oxtor_hal_reg_name_str(reg));
		WARN_ON(1);
		return;
	}

	offset +=
ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].m_ofst * m;
	offset +=
ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].n_ofst * n;
	ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].construct
	(reg, fields, &val);
	base += offset;
	iowrite32(val, &base);
}

u32 ecpriss_oxtor_hal_read_reg_mn_fields(enum ecpriss_oxtor_hal_reg_name reg,
		u32 m, u32 n, void *fields)
{
	u32 val = 0;
	u32 offset;
	u32 base;

	if (!fields) {
		pr_err("Input error fields\n");
		WARN_ON(1);
		return -EINVAL;
	}

	if (reg >= ECPRI_OXTOR_OXTOR_MAX) {
		pr_err("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return -EINVAL;
	}

	pr_info("read from %s n=%u and parse it\n",
			ecpriss_oxtor_hal_reg_name_str(reg), n);

	base =
	ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].base;
	offset =
	ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].offset;
	if (offset == -1) {
		pr_err("Read access to obsolete reg=%s\n",
				ecpriss_oxtor_hal_reg_name_str(reg));
		WARN_ON(1);
		return -EPERM;
	}
	offset +=
ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].m_ofst * m;
	offset +=
ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].n_ofst * n;
	base += offset;
	val =ioread32(&base);
	ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].parse
		(reg, fields, val);
	return val;
}

/*
 * ecpriss_oxtor_*_fields(),Get the parsed value of n parameterized reg
 */
u32 ecpriss_oxtor_hal_read_reg_n_fields(enum ecpriss_oxtor_hal_reg_name reg,
		u32 n, void *fields)
{
	u32 val = 0;
	u32 offset;
	u32 base;

	if (!fields) {
		pr_err("Input error fields\n");
		WARN_ON(1);
		return -EINVAL;
	}

	if (reg >= ECPRI_OXTOR_OXTOR_MAX) {
		pr_err("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return -EINVAL;
	}

	pr_info("read from %s n=%u and parse it\n",
			ecpriss_oxtor_hal_reg_name_str(reg), n);
	base =
	ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].base;
	offset =
	ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].offset;
	if (offset == -1) {
		pr_err("Read access to obsolete reg=%s\n",
				ecpriss_oxtor_hal_reg_name_str(reg));
		WARN_ON(1);
		return -EPERM;
	}
	offset +=
ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].n_ofst * n;
	/*
	 * base += offset;
	 * val =ioread32(&base);
	 * Mayank hardcoding ECPRI_OXTOR_REG_TYPE_BASE,
	 * pr_info("BASE TYPE IS : ECPRI_OXTOR_REG_TYPE_GLOBAL\n");
	 * ecpri_oxtor_hal_reg_read(ECPRI_OXTOR_REG_TYPE_GLOBAL, base, &val);
	 */
	ecpri_oxtor_hal_reg_read(ECPRI_OXTOR_REG_TYPE_BASE, offset, &val);
	ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].parse
		(reg, fields, val);
	return val;
}

/*
 * ecpriss_oxtor_*_fields() - Write to n parameterized reg a prased value
 */
void ecpriss_oxtor_hal_write_reg_n_fields(ecpri_oxtor_hal_reg_type_e reg_type,
		enum ecpriss_oxtor_hal_reg_name reg,
		u32 n,
		const void *fields)
{
	u32 val = 0;
	u32 offset;
	u32 base;

	if (!fields) {
		pr_err("Input error fields=%pK\n", fields);
		WARN_ON(1);
		return;
	}

	if (reg >= ECPRI_OXTOR_OXTOR_MAX) {
		pr_err("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return;
	}

	pr_info("write to %s n=%u after constructing it\n",
			ecpriss_oxtor_hal_reg_name_str(reg), n);
	base =
	ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].base;
	offset =
	ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].offset;
	if (offset == -1) {
		pr_err("Write access to obsolete reg=%s\n",
				ecpriss_oxtor_hal_reg_name_str(reg));
		WARN_ON(1);
		return;
	}
	offset +=
ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].n_ofst * n;

	ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].construct
	(reg, fields, &val);

	ecpri_oxtor_hal_reg_write(reg_type,offset,val);

	return;
}

u32 ecpriss_oxtor_hal_read_reg_mnk_fields(enum ecpriss_oxtor_hal_reg_name reg,
		u32 m, u32 n, u32 k, void *fields)
{
	u32 val = 0;
	u32 offset;
	u32 base;

	if (!fields) {
		pr_err("Input error fields\n");
		WARN_ON(1);
		return -EINVAL;
	}

	if (reg >= ECPRI_OXTOR_OXTOR_MAX) {
		pr_err("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return -EINVAL;
	}

	pr_info("read from %s n=%u and parse it\n",
			ecpriss_oxtor_hal_reg_name_str(reg), n);

	base =
	ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].base;
	offset =
	ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].offset;
	if (offset == -1) {
		pr_err("Read access to obsolete reg=%s\n",
				ecpriss_oxtor_hal_reg_name_str(reg));
		WARN_ON(1);
		return -EPERM;
	}
	offset +=
ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].m_ofst * m;
	offset +=
ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].n_ofst * n;
	offset +=
ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].n_ofst * k;
	base += offset;
	val =ioread32(&base);
	ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].parse
		(reg, fields, val);
	return val;
}

void ecpriss_oxtor_hal_write_reg_mnk_fields(ecpri_oxtor_hal_reg_type_e reg_type,
	enum ecpriss_oxtor_hal_reg_name reg, u32 m, u32 n, u32 k, void *fields)
{

	/*
	 * m = cmd entry idx in Tx ring
	 * n = ring_id,
	 * k = word ofst of tx cmd
	 * fields = 4B of tx cmd at kth ofst
	 */

	u32 offset;
	u32 val = 0;
	u32 base;
	if (reg >= ECPRI_OXTOR_OXTOR_MAX) {
		pr_err("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return;
	}

	pr_info("write to %s m=%u n=%u val=%u\n",
			ecpriss_oxtor_hal_reg_name_str(reg), m, n, val);

	base =
	ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].base;
	offset =
	ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].offset;
	if (offset == -1) {
		pr_err("Write access to obsolete reg=%s\n",
				ecpriss_oxtor_hal_reg_name_str(reg));
		WARN_ON(1);
		return;
	}

	offset +=
ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].m_ofst * m;
	offset +=
ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].n_ofst * n;
	offset +=
ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].k_ofst * k;
	ecpriss_oxtor_hal_reg_objs[ecpriss_oxtor_hal_ctx.hw_type][reg].construct
		(reg, fields, &val);

	ecpri_oxtor_hal_reg_write(reg_type,offset,val);
	/*
	 * base += offset;
	 * iowrite32(val, &base);
	 */
}
