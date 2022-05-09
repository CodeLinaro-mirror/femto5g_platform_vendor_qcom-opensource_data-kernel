/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include <linux/module.h>
#include <linux/kernel.h>
//#include <linux/delay.h>
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
#include <asm/io.h>

#include "ecpriss_xbar_hal.h"


static const char *ecpriss_xbar_hal_reg_name_to_str[ECPRI_XBAR_XBAR_MAX+1] = {

	"ECPRI_XBAR_XBAR_CFG",
	"ECPRI_XBAR_XBAR_C2C_IPG_CFG" ,
	"ECPRI_XBAR_XBAR_C2C_CFG",
	"ECPRI_XBAR_XBAR_FH_CFG",
	"ECPRI_XBAR_XBAR_OC_CFG",
	"ECPRI_XBAR_XBAR_OC_LOOPBACK_CFG",
	"ECPRI_XBAR_XBAR_FLUSH",
	"ECPRI_XBAR_XBAR_FH_STATUS",
	"ECPRI_XBAR_XBAR_C2C_STATUS",
	"ECPRI_XBAR_XBAR_OCTX_STATUS",
	"ECPRI_XBAR_XBAR_LUT_STATUS",
	"ECPRI_XBAR_XBAR_FW_IRQ_STATUS",
	"ECPRI_XBAR_XBAR_FW_IRQ_MASK",
	"ECPRI_XBAR_XBAR_FW_IRQ_CLR",
	"ECPRI_XBAR_XBAR_SW_IRQ_STATUS",
	"ECPRI_XBAR_XBAR_SW_IRQ_MASK",
	"ECPRI_XBAR_XBAR_SW_IRQ_CLR",
	"ECPRI_XBAR_XBAR_TPDM_GLOBAL_CFG",
	"ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT",
	"ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT",
	"ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT",
	"ECPRI_XBAR_XBAR_FHRX_n_DEFAULT_LUT",
	"ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_0",
	"ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_1",
	"ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_n_LUT_RESULT",
	"ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0",
	"ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_1",
	"ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_n_LUT_RESULT",
	"ECPRI_XBAR_XBAR_C2CRX_n_DL_DEFAULT_LUT",
	"ECPRI_XBAR_XBAR_C2CRX_n_UL_DEFAULT_LUT",
	"ECPRI_XBAR_XBAR_C2CRX_NON_ECPRI_LUT",
	"ECPRI_XBAR_XBAR_OCRX_FH_n_DEFAULT_LUT",
	"ECPRI_XBAR_XBAR_OCRX_C2C_DEFAULT_LUT",
	"ECPRI_XBAR_XBAR_UC_FHRX_BUFF_ADDR",
	"ECPRI_XBAR_XBAR_UC_FHRX_BUFF_SIZE",
	"ECPRI_XBAR_XBAR_UC_FHRX_BUFF_RD",
	"ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_POP",
	"ECPRI_XBAR_XBAR_UC_FHRX_PKT_ATTR_NO_POP",
	"ECPRI_XBAR_XBAR_UC_FHRX_STATUS",
	"ECPRI_XBAR_XBAR_UC_FH_CTRL",
	"ECPRI_XBAR_XBAR_UC_FHTX_PKT_ADDR",
	"ECPRI_XBAR_XBAR_UC_FHTX_PKT_ATTR",
	"ECPRI_XBAR_LUT_XBAR_FHRX_m_LUT_n",
	"ECPRI_XBAR_LUT_XBAR_C2CRX_m_DL_LUT_n",
	"ECPRI_XBAR_LUT_XBAR_C2CRX_m_UL_LUT_n",
	"ECPRI_XBAR_LUT_XBAR_OCRX_m_LUT_n",
	//Stats
	"ECPRI_XBAR_XBAR_DBG_FHRX_PKT_CNT_n",//per link
	"ECPRI_XBAR_XBAR_DBG_FHRX_DMA_PKT_CNT",
	"ECPRI_XBAR_XBAR_DBG_FHRX_UC_PKT_CNT",
	"ECPRI_XBAR_XBAR_DBG_FHRX_UC_ERR_PKT_CNT",
	"ECPRI_XBAR_XBAR_DBG_FHRX_ERR_PKT_CNT",
	"ECPRI_XBAR_XBAR_DBG_FHTX_PKT_CNT_n",//per link
	"ECPRI_XBAR_XBAR_DBG_FHTX_C2C_PKT_OVF_CNT",
	"ECPRI_XBAR_XBAR_DBG_FHTX_DMA_PKT_CNT",
	"ECPRI_XBAR_XBAR_DBG_FHTX_UC_PKT_CNT",
	"ECPRI_XBAR_XBAR_DBG_C2CRX_PKT_CNT_n",// per link
	"ECPRI_XBAR_XBAR_DBG_C2CRX_DMA_PKT_CNT",
	"ECPRI_XBAR_XBAR_DBG_C2CRX_ERR_PKT_CNT",
	"ECPRI_XBAR_XBAR_DBG_C2CTX_PKT_CNT_n",//per link
	"ECPRI_XBAR_XBAR_DBG_C2CTX_FH_PKT_OVF_CNT",
	"ECPRI_XBAR_XBAR_DBG_C2CTX_DMA_PKT_CNT",
	"ECPRI_XBAR_XBAR_DBG_OCTX_C2C_PKT_DROP_CNT",
	"ECPRI_XBAR_XBAR_DBG_OCTX_PKT_CNT_n", //per link
	"ECPRI_XBAR_XBAR_DBG_OCRX_PKT_CNT_n", //per link
	"ECPRI_XBAR_XBAR_DBG_OCRX_FH_PKT_CNT_n",//per link
	"ECPRI_XBAR_XBAR_DBG_OCRX_C2C_PKT_CNT_n", //per link
	"ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT",
	"ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT",
	"ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT",
	"ECPRI_XBAR_XBAR_MAX"

};

ecpriss_xbar_hal_context_s ecpriss_xbar_hal_ctx;

/*
 * ecpriss_xbar_hal_reg_name_str() - returns string that represent the register
 * @reg_name: [in] register name
 */
const char *ecpriss_xbar_hal_reg_name_str(enum ecpriss_xbar_hal_reg_name reg_name)
{
	if (reg_name < 0 || reg_name >= ECPRI_XBAR_XBAR_MAX) {
		pr_err("requested name of invalid reg=%d\n", reg_name);
		return "Invalid Register";
	}

	return ecpriss_xbar_hal_reg_name_to_str[reg_name];
}

	static void ecpriss_xbar_hal_reg_construct_xbar_cfg
(enum ecpriss_xbar_hal_reg_name reg, const void *fields, uint32_t* val)
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_cfg_s *xbar_cfg
		= (ecpri_xbar_hwio_def_ecpri_xbar_xbar_cfg_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_cfg->fhrx_cnt_en,
			HWIO_ECPRI_XBAR_XBAR_CFG_FHRX_CNT_EN_SHFT,
			HWIO_ECPRI_XBAR_XBAR_CFG_FHRX_CNT_EN_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_cfg->fhtx_cnt_en,
			HWIO_ECPRI_XBAR_XBAR_CFG_FHTX_CNT_EN_SHFT,
			HWIO_ECPRI_XBAR_XBAR_CFG_FHTX_CNT_EN_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_cfg->ocrx_cnt_en,
			HWIO_ECPRI_XBAR_XBAR_CFG_OCRX_CNT_EN_SHFT,
			HWIO_ECPRI_XBAR_XBAR_CFG_OCRX_CNT_EN_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_cfg->octx_cnt_en,
			HWIO_ECPRI_XBAR_XBAR_CFG_OCTX_CNT_EN_SHFT,
			HWIO_ECPRI_XBAR_XBAR_CFG_OCTX_CNT_EN_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_cfg->c2crx_cnt_en,
			HWIO_ECPRI_XBAR_XBAR_CFG_C2CRX_CNT_EN_SHFT,
			HWIO_ECPRI_XBAR_XBAR_CFG_C2CRX_CNT_EN_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_cfg->c2ctx_cnt_en,
			HWIO_ECPRI_XBAR_XBAR_CFG_C2CTX_CNT_EN_SHFT,
			HWIO_ECPRI_XBAR_XBAR_CFG_C2CTX_CNT_EN_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_cfg->xbar_cnt_en,
			HWIO_ECPRI_XBAR_XBAR_CFG_XBAR_CNT_EN_SHFT,
			HWIO_ECPRI_XBAR_XBAR_CFG_XBAR_CNT_EN_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_cfg->xbar_cnt_clr_en,
			HWIO_ECPRI_XBAR_XBAR_CFG_XBAR_CNT_CLR_EN_SHFT,
			HWIO_ECPRI_XBAR_XBAR_CFG_XBAR_CNT_CLR_EN_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_cfg->tpdm_en,
			HWIO_ECPRI_XBAR_XBAR_CFG_TPDM_EN_SHFT,
			HWIO_ECPRI_XBAR_XBAR_CFG_TPDM_EN_BMSK);

	return;
}


	static void ecpriss_xbar_hal_reg_construct_fhrx_0_non_ecpri_lut
(enum ecpriss_xbar_hal_reg_name reg, const void *fields, uint32_t* val)
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_0_non_ecpri_lut_s *fhrx_0_non_ecpri_lut
		= (ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_0_non_ecpri_lut_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fhrx_0_non_ecpri_lut->ring_id_0,
			HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_0_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fhrx_0_non_ecpri_lut->ring_id_1,
			HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_1_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fhrx_0_non_ecpri_lut->ring_id_2,
			HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_2_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fhrx_0_non_ecpri_lut->ring_id_3,
			HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_3_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_3_BMSK);

	return;
}

	static void ecpriss_xbar_hal_reg_parse_fhrx_0_non_ecpri_lut
(enum ecpriss_xbar_hal_reg_name reg, void *fields, uint32_t val)
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_0_non_ecpri_lut_s *fhrx_0_non_ecpri_lut
		= (ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_0_non_ecpri_lut_s *)fields;

	fhrx_0_non_ecpri_lut->ring_id_0 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_0_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_0_BMSK);

	fhrx_0_non_ecpri_lut->ring_id_1 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_1_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_1_BMSK);

	fhrx_0_non_ecpri_lut->ring_id_2 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_2_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_2_BMSK);

	fhrx_0_non_ecpri_lut->ring_id_3 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_3_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT_RING_ID_3_BMSK);

	return;
}

	static void ecpriss_xbar_hal_reg_construct_fhrx_1_non_ecpri_lut
(enum ecpriss_xbar_hal_reg_name reg, const void *fields, uint32_t* val)
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_1_non_ecpri_lut_s *fhrx_1_non_ecpri_lut
		= (ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_1_non_ecpri_lut_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fhrx_1_non_ecpri_lut->ring_id_0,
			HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_RING_ID_0_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_RING_ID_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fhrx_1_non_ecpri_lut->ring_id_1,
			HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_RING_ID_1_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_RING_ID_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fhrx_1_non_ecpri_lut->ring_id_2,
			HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_RING_ID_2_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_RING_ID_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fhrx_1_non_ecpri_lut->ring_id_3,
			HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_RING_ID_3_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_RING_ID_3_BMSK);

	return;
}

	static void ecpriss_xbar_hal_reg_parse_fhrx_1_non_ecpri_lut
(enum ecpriss_xbar_hal_reg_name reg, void *fields, uint32_t val)
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_1_non_ecpri_lut_s *fhrx_1_non_ecpri_lut
		= (ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_1_non_ecpri_lut_s *)fields;

	fhrx_1_non_ecpri_lut->ring_id_0 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_RING_ID_0_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_RING_ID_0_BMSK);

	fhrx_1_non_ecpri_lut->ring_id_1 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_RING_ID_1_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_RING_ID_1_BMSK);

	fhrx_1_non_ecpri_lut->ring_id_2 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_RING_ID_2_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_RING_ID_2_BMSK);

	fhrx_1_non_ecpri_lut->ring_id_3 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_RING_ID_3_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT_RING_ID_3_BMSK);

	return;
}


	static void ecpriss_xbar_hal_reg_construct_fhrx_2_non_ecpri_lut
(enum ecpriss_xbar_hal_reg_name reg, const void *fields, uint32_t* val)
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_2_non_ecpri_lut_s *fhrx_2_non_ecpri_lut
		= (ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_2_non_ecpri_lut_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fhrx_2_non_ecpri_lut->ring_id_0,
			HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_RING_ID_0_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_RING_ID_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fhrx_2_non_ecpri_lut->ring_id_1,
			HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_RING_ID_1_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_RING_ID_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fhrx_2_non_ecpri_lut->ring_id_2,
			HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_RING_ID_2_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_RING_ID_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fhrx_2_non_ecpri_lut->ring_id_3,
			HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_RING_ID_3_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_RING_ID_3_BMSK);

	return;
}

	static void ecpriss_xbar_hal_reg_parse_fhrx_2_non_ecpri_lut
(enum ecpriss_xbar_hal_reg_name reg, void *fields, uint32_t val)
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_2_non_ecpri_lut_s *fhrx_2_non_ecpri_lut
		= (ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_2_non_ecpri_lut_s *)fields;

	fhrx_2_non_ecpri_lut->ring_id_0 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_RING_ID_0_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_RING_ID_0_BMSK);

	fhrx_2_non_ecpri_lut->ring_id_1 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_RING_ID_1_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_RING_ID_1_BMSK);

	fhrx_2_non_ecpri_lut->ring_id_2 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_RING_ID_2_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_RING_ID_2_BMSK);

	fhrx_2_non_ecpri_lut->ring_id_3 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_RING_ID_3_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT_RING_ID_3_BMSK);

	return;
}

#if 0
	static void ecpriss_xbar_hal_reg_construct_lut_status
(enum ecpriss_xbar_hal_reg_name reg, const void *fields, uint32_t* val)
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_lut_status_s *lut_status
		= (ecpri_xbar_hwio_def_ecpri_xbar_xbar_lut_status_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			lut_status->fhrx_lut_init_done,
			HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_FHRX_LUT_INIT_DONE_SHFT,
			HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_FHRX_LUT_INIT_DONE_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			lut_status->c2crx_dl_lut_init_done,
			HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_C2CRX_DL_LUT_INIT_DONE_SHFT,
			HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_C2CRX_DL_LUT_INIT_DONE_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			lut_status->c2crx_ul_lut_init_done,
			HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_C2CRX_UL_LUT_INIT_DONE_SHFT,
			HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_C2CRX_UL_LUT_INIT_DONE_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			lut_status->ocrx_lut_init_done,
			HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_OCRX_LUT_INIT_DONE_SHFT,
			HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_OCRX_LUT_INIT_DONE_BMSK);
	return;
}

#endif

	static void ecpriss_xbar_hal_reg_construct_xbar_flush
(enum ecpriss_xbar_hal_reg_name reg, const void *fields, uint32_t* val)
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_flush_s *xbar_flush
		= (ecpri_xbar_hwio_def_ecpri_xbar_xbar_flush_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_flush->flush_fh_0_tx,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_0_TX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_0_TX_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_flush->flush_fh_0_rx,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_0_RX_SHFT ,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_0_RX_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_flush->flush_fh_1_tx,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_1_TX_SHFT ,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_1_TX_BMSK );

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_flush->flush_fh_1_rx,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_1_RX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_1_RX_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_flush->flush_fh_2_tx,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_2_TX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_2_TX_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_flush->flush_fh_2_rx,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_2_RX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_2_RX_BMSK);


	//C2C
	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_flush->flush_c2c_0_tx,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_0_TX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_0_TX_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_flush->flush_c2c_0_rx,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_0_RX_SHFT ,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_0_RX_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_flush->flush_c2c_1_tx,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_1_TX_SHFT ,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_1_TX_BMSK );

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_flush->flush_c2c_1_rx,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_1_RX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_1_RX_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_flush->flush_c2c_2_tx,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_2_TX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_2_TX_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_flush->flush_c2c_2_rx,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_2_RX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_2_RX_BMSK);

	//OC

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_flush->flush_oc_0_tx,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_0_TX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_0_TX_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_flush->flush_oc_0_rx,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_0_RX_SHFT ,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_0_RX_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_flush->flush_oc_1_tx,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_1_TX_SHFT ,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_1_TX_BMSK );

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_flush->flush_oc_1_rx,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_1_RX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_1_RX_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_flush->flush_oc_2_tx,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_2_TX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_2_TX_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_flush->flush_oc_2_rx,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_2_RX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_2_RX_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_flush->flush_oc_3_tx,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_3_TX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_3_TX_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_flush->flush_oc_3_rx,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_3_RX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_3_RX_BMSK);
	return;
}

static void ecpriss_xbar_hal_reg_parse_lut_status(enum ecpriss_xbar_hal_reg_name reg, void *fields,
		u32 val)
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_lut_status_s *lut_status;
	lut_status = (ecpri_xbar_hwio_def_ecpri_xbar_xbar_lut_status_s *)fields;

	pr_info("ecpriss_xbar_hal_reg_parse_lut_status: 0x%x", val);

	lut_status->fhrx_lut_init_done = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_FHRX_LUT_INIT_DONE_SHFT,
			HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_FHRX_LUT_INIT_DONE_BMSK);
	lut_status->c2crx_dl_lut_init_done = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_C2CRX_DL_LUT_INIT_DONE_SHFT,
			HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_C2CRX_DL_LUT_INIT_DONE_BMSK);
	lut_status->c2crx_ul_lut_init_done = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_C2CRX_UL_LUT_INIT_DONE_SHFT,
			HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_C2CRX_UL_LUT_INIT_DONE_BMSK);
	lut_status->ocrx_lut_init_done = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_OCRX_LUT_INIT_DONE_SHFT,
			HWIO_ECPRI_XBAR_XBAR_LUT_STATUS_OCRX_LUT_INIT_DONE_BMSK);

	return;
}

static void ecpriss_xbar_hal_reg_parse_xbar_flush(enum ecpriss_xbar_hal_reg_name reg, void *fields,
		u32 val)
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_flush_u *xbar_flush;
	xbar_flush = fields;

	/*C2C0 RX TX*/
	xbar_flush->def.flush_c2c_0_rx = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_0_RX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_0_RX_BMSK);
	xbar_flush->def.flush_c2c_0_tx = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_0_TX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_0_TX_BMSK);

	/*C2C1 RX TX*/
	xbar_flush->def.flush_c2c_1_rx = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_1_RX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_1_RX_BMSK);
	xbar_flush->def.flush_c2c_1_tx = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_1_TX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_1_TX_BMSK);

	/*C2C2 RX TX*/
	xbar_flush->def.flush_c2c_2_rx = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_2_RX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_2_RX_BMSK);
	xbar_flush->def.flush_c2c_2_tx = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_2_TX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_C2C_2_TX_BMSK);


	/*FH0 RX TX*/
	xbar_flush->def.flush_fh_0_rx = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_0_RX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_0_RX_BMSK);
	xbar_flush->def.flush_fh_0_tx = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_0_TX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_0_TX_BMSK);

	/*FH1 RX TX*/
	xbar_flush->def.flush_fh_1_rx = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_1_RX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_1_RX_BMSK);
	xbar_flush->def.flush_fh_1_tx = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_1_TX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_1_TX_BMSK);

	/*FH2 RX TX*/
	xbar_flush->def.flush_fh_2_rx = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_2_RX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_2_RX_BMSK);
	xbar_flush->def.flush_fh_2_tx = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_2_TX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_FH_2_TX_BMSK);



	/*OC0 RX TX*/
	xbar_flush->def.flush_oc_0_rx = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_0_RX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_0_RX_BMSK);
	xbar_flush->def.flush_oc_0_tx = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_0_TX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_0_TX_BMSK);

	/*OC1 RX TX*/
	xbar_flush->def.flush_oc_1_rx = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_1_RX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_1_RX_BMSK);
	xbar_flush->def.flush_oc_1_tx = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_1_TX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_1_TX_BMSK);

	/*OC2 RX TX*/
	xbar_flush->def.flush_oc_2_rx = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_2_RX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_2_RX_BMSK);
	xbar_flush->def.flush_oc_2_tx = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_2_TX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_2_TX_BMSK);

	/*OC3 RX TX*/
	xbar_flush->def.flush_oc_3_rx = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_3_RX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_3_RX_BMSK);
	xbar_flush->def.flush_oc_3_tx = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_3_TX_SHFT,
			HWIO_ECPRI_XBAR_XBAR_FLUSH_FLUSH_OC_3_TX_BMSK);

	return;
}

static void ecpriss_xbar_hal_reg_parse_xbar_cfg(enum ecpriss_xbar_hal_reg_name reg, void *fields,
		u32 val)
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_cfg_u *xbar_cfg;
	xbar_cfg = fields;


	xbar_cfg->def.c2crx_cnt_en = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_CFG_C2CRX_CNT_EN_SHFT,
			HWIO_ECPRI_XBAR_XBAR_CFG_C2CRX_CNT_EN_BMSK);
	xbar_cfg->def.c2ctx_cnt_en = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_CFG_C2CTX_CNT_EN_SHFT,
			HWIO_ECPRI_XBAR_XBAR_CFG_C2CTX_CNT_EN_BMSK);

	xbar_cfg->def.fhrx_cnt_en = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_CFG_FHRX_CNT_EN_SHFT,
			HWIO_ECPRI_XBAR_XBAR_CFG_FHRX_CNT_EN_BMSK);
	xbar_cfg->def.fhtx_cnt_en = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_CFG_FHTX_CNT_EN_SHFT,
			HWIO_ECPRI_XBAR_XBAR_CFG_FHTX_CNT_EN_BMSK);

	xbar_cfg->def.ocrx_cnt_en = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_CFG_OCRX_CNT_EN_SHFT,
			HWIO_ECPRI_XBAR_XBAR_CFG_OCRX_CNT_EN_BMSK);
	xbar_cfg->def.octx_cnt_en = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_CFG_OCTX_CNT_EN_SHFT,
			HWIO_ECPRI_XBAR_XBAR_CFG_OCTX_CNT_EN_BMSK);

	xbar_cfg->def.xbar_cnt_en = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_CFG_XBAR_CNT_EN_SHFT,
			HWIO_ECPRI_XBAR_XBAR_CFG_XBAR_CNT_EN_BMSK);
	xbar_cfg->def.xbar_cnt_clr_en = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_CFG_XBAR_CNT_CLR_EN_SHFT,
			HWIO_ECPRI_XBAR_XBAR_CFG_XBAR_CNT_CLR_EN_BMSK);

	xbar_cfg->def.tpdm_en = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_XBAR_XBAR_CFG_TPDM_EN_SHFT,
			HWIO_ECPRI_XBAR_XBAR_CFG_TPDM_EN_BMSK);

	return;
}

static void ecpriss_xbar_hal_reg_parse_dummy(enum ecpriss_xbar_hal_reg_name reg, void *fields,
		u32 val)
{
	return;
}

	static void ecpriss_xbar_hal_reg_construct_dummy
(enum ecpriss_xbar_hal_reg_name reg, const void *fields, uint32_t* val)
{
	return;
}

	static void ecpriss_xbar_hal_reg_construct_lut_xbar_fhrx_msg_type_lut_0
(enum ecpriss_xbar_hal_reg_name reg, const void *fields, uint32_t* val)
{
	return;
}


	static void ecpriss_xbar_hal_reg_construct_lut_xbar_fhrx_msg_type_lut_1
(enum ecpriss_xbar_hal_reg_name reg, const void *fields, uint32_t* val)
{
	return;
}

#if 0
	static void ecpriss_xbar_hal_reg_construct_c2crx_msg_type_lut_0
(enum ecpriss_xbar_hal_reg_name reg, const void *fields, uint32_t* val)
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2crx_msg_type_lut_0_s *c2crx_msg_type_lut
		= (ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2crx_msg_type_lut_0_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			c2crx_msg_type_lut->msg_type_0,
			HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_MSG_TYPE_0_SHFT,
			HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_MSG_TYPE_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			c2crx_msg_type_lut->valid_0,
			HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_VALID_0_SHFT,
			HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_VALID_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			c2crx_msg_type_lut->msg_type_1,
			HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_MSG_TYPE_1_SHFT,
			HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_MSG_TYPE_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			c2crx_msg_type_lut->valid_1,
			HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_VALID_1_SHFT,
			HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_VALID_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			c2crx_msg_type_lut->msg_type_2,
			HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_MSG_TYPE_2_SHFT,
			HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_MSG_TYPE_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			c2crx_msg_type_lut->valid_2,
			HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_VALID_2_SHFT,
			HWIO_ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0_VALID_2_BMSK);
	return;
}
#endif
	static void  ecpriss_xbar_hal_reg_parse_lut_xbar_fw_irq_status
(enum ecpriss_xbar_hal_reg_name reg, void *fields,u32 val)
{
	return;
}

	static void ecpriss_xbar_hal_reg_construct_lut_xbar_fw_irq_clr
(enum ecpriss_xbar_hal_reg_name reg, const void *fields, uint32_t* val)
{
	return;
}

	static void ecpriss_xbar_hal_reg_construct_lut_xbar_fw_irq_mask
(enum ecpriss_xbar_hal_reg_name reg, const void *fields, uint32_t* val)
{
	return;
}

	static void ecpriss_xbar_hal_reg_construct_lut_xbar_fhrx_m_lut_n
(enum ecpriss_xbar_hal_reg_name reg, const void *fields, uint32_t* val)
{
	ecpri_xbar_hwio_def_ecpri_xbar_lut_xbar_fhrx_m_lut_n_s *xbar_fhrx_m_lut_n
		= (ecpri_xbar_hwio_def_ecpri_xbar_lut_xbar_fhrx_m_lut_n_s *)fields;


	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_fhrx_m_lut_n->dma_ring_id,
			ECPRI_XBAR_XBAR_FH_RX_LUT_DMA_RING_ID_SHFT,
			ECPRI_XBAR_XBAR_FH_RX_LUT_DMA_RING_ID_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_fhrx_m_lut_n->oc_link_id,
			ECPRI_XBAR_XBAR_FH_RX_LUT_LINK_ID_SHFT,
			ECPRI_XBAR_XBAR_FH_RX_LUT_LINK_ID_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_fhrx_m_lut_n->route_to_oran,
			ECPRI_XBAR_XBAR_FH_RX_LUT_ROUTE_ORAN_SHFT,
			ECPRI_XBAR_XBAR_FH_RX_LUT_ROUTE_ORAN_BMSK);


	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_fhrx_m_lut_n->route_to_c2c,
			ECPRI_XBAR_XBAR_FH_RX_LUT_ROUTE_C2C_SHFT,
			ECPRI_XBAR_XBAR_FH_RX_LUT_ROUTE_C2C_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_fhrx_m_lut_n->route_to_dma,
			ECPRI_XBAR_XBAR_FH_RX_LUT_ROUTE_DMA_SHFT,
			ECPRI_XBAR_XBAR_FH_RX_LUT_ROUTE_DMA_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_fhrx_m_lut_n->valid,
			ECPRI_XBAR_XBAR_FH_RX_LUT_IS_VALID_SHFT,
			ECPRI_XBAR_XBAR_FH_RX_LUT_IS_VALID_BMSK);

	return;
}

	static void ecpriss_xbar_hal_reg_construct_lut_xbar_c2crx_m_dl_lut_n
(enum ecpriss_xbar_hal_reg_name reg, const void *fields, uint32_t* val)
{
	return;
}

	static void  ecpriss_xbar_hal_reg_construct_lut_xbar_c2crx_m_ul_lut_n
(enum ecpriss_xbar_hal_reg_name reg, const void *fields, uint32_t* val)
{
	return;
}

	static void  ecpriss_xbar_hal_reg_construct_lut_xbar_ocrx_m_lut_n
(enum ecpriss_xbar_hal_reg_name reg, const void *fields, uint32_t* val)
{

	ecpri_xbar_hwio_def_ecpri_xbar_lut_xbar_ocrx_m_lut_n_s * xbar_ocrx_m_lut_n
		= (ecpri_xbar_hwio_def_ecpri_xbar_lut_xbar_ocrx_m_lut_n_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_ocrx_m_lut_n->l2_encap_info,
			ECPRI_XBAR_XBAR_OCRX_LUT_M_L2_ENCAP_SHFT,
			ECPRI_XBAR_XBAR_OCRX_LUT_M_L2_ENCAP_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_ocrx_m_lut_n->l3_encap_info,
			ECPRI_XBAR_XBAR_OCRX_LUT_M_L3_ENCAP_SHFT,
			ECPRI_XBAR_XBAR_OCRX_LUT_M_L3_ENCAP_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_ocrx_m_lut_n->l3_encap_valid,
			ECPRI_XBAR_XBAR_OCRX_LUT_M_L3_ENCAP_VALID_SHFT,
			ECPRI_XBAR_XBAR_OCRX_LUT_M_L3_ENCAP_VALID_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			xbar_ocrx_m_lut_n->valid,
			ECPRI_XBAR_XBAR_OCRX_LUT_M_VALID_SHFT, //17 0x3ff
			ECPRI_XBAR_XBAR_OCRX_LUT_M_VALID_BMSK);

	return;
}



static struct ecpriss_xbar_hal_reg_obj ecpriss_xbar_hal_reg_objs[ECPRISS_XBAR_HW_MAX][ECPRI_XBAR_XBAR_MAX] = {
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_CFG] = {
		ecpriss_xbar_hal_reg_construct_xbar_cfg,
		ecpriss_xbar_hal_reg_parse_xbar_cfg,
		0x09220000, 0x0, 0, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT] = {
		ecpriss_xbar_hal_reg_construct_fhrx_0_non_ecpri_lut,
		ecpriss_xbar_hal_reg_parse_fhrx_0_non_ecpri_lut,
		0x09220000, 0x00000800, 0, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT] = {
		ecpriss_xbar_hal_reg_construct_fhrx_1_non_ecpri_lut,
		ecpriss_xbar_hal_reg_parse_fhrx_1_non_ecpri_lut,
		0x09220000, 0x00000804, 0, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT] = {
		ecpriss_xbar_hal_reg_construct_fhrx_2_non_ecpri_lut,
		ecpriss_xbar_hal_reg_parse_fhrx_2_non_ecpri_lut,
		0x09220000, 0x00000808, 0, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_LUT_STATUS] = {
		ecpriss_xbar_hal_reg_construct_dummy,
		ecpriss_xbar_hal_reg_parse_lut_status,
		0x09220000, 0x00000030, 0, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_FLUSH] = {
		ecpriss_xbar_hal_reg_construct_xbar_flush,
		ecpriss_xbar_hal_reg_parse_xbar_flush,
		0x09220000, 0x0000001C, 0, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_0] = {
		ecpriss_xbar_hal_reg_construct_lut_xbar_fhrx_msg_type_lut_0,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09220000, 0x00000820, 0, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_FHRX_MSG_TYPE_LUT_1] = {
		ecpriss_xbar_hal_reg_construct_lut_xbar_fhrx_msg_type_lut_1,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09220000, 0x00000824, 0, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_FW_IRQ_STATUS] = {
		ecpriss_xbar_hal_reg_construct_dummy,
		ecpriss_xbar_hal_reg_parse_lut_xbar_fw_irq_status,
		0x09220000, 0x00000040, 0, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_FW_IRQ_MASK] = {
		ecpriss_xbar_hal_reg_construct_lut_xbar_fw_irq_mask,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09220000, 0x00000044, 0, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_FW_IRQ_CLR] = {
		ecpriss_xbar_hal_reg_construct_lut_xbar_fw_irq_clr,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09220000, 0x00000048, 0, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_LUT_XBAR_FHRX_m_LUT_n] = {
		ecpriss_xbar_hal_reg_construct_lut_xbar_fhrx_m_lut_n,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09300000, 0x0, 0x4, 0, 0, 0, 0x40000},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_LUT_XBAR_C2CRX_m_DL_LUT_n] = {
		ecpriss_xbar_hal_reg_construct_lut_xbar_c2crx_m_dl_lut_n,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09300000, 0xC0000, 0x4, 0, 0, 0, 0x40000},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_LUT_XBAR_C2CRX_m_DL_LUT_n] = {
		ecpriss_xbar_hal_reg_construct_lut_xbar_c2crx_m_ul_lut_n,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09300000, 0x180000, 0x4, 0, 0, 0, 0x40000},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_LUT_XBAR_OCRX_m_LUT_n] = {
		ecpriss_xbar_hal_reg_construct_lut_xbar_ocrx_m_lut_n,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09300000, 0x240000, 0x4, 0, 0, 0, 0x40000},

	//Stats
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_DBG_FHRX_PKT_CNT_n] = {
		ecpriss_xbar_hal_reg_construct_dummy,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09220000, 0x2000, 0x4, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_DBG_FHRX_DMA_PKT_CNT] = {
		ecpriss_xbar_hal_reg_construct_dummy,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09220000, 0x2060, 0, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_DBG_FHRX_UC_PKT_CNT] = {
		ecpriss_xbar_hal_reg_construct_dummy,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09220000, 0x2090, 0, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_DBG_FHRX_UC_ERR_PKT_CNT] = {
		ecpriss_xbar_hal_reg_construct_dummy,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09220000, 0x2098, 0, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_DBG_FHRX_ERR_PKT_CNT] = {
		ecpriss_xbar_hal_reg_construct_dummy,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09220000, 0x20A0, 0, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_DBG_FHTX_PKT_CNT_n] = {
		ecpriss_xbar_hal_reg_construct_dummy,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09220000, 	0x2100, 0x4, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_DBG_FHTX_C2C_PKT_OVF_CNT] = {
		ecpriss_xbar_hal_reg_construct_dummy,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09220000, 0x2190, 0, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_DBG_FHTX_DMA_PKT_CNT] = {
		ecpriss_xbar_hal_reg_construct_dummy,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09220000, 0x2194, 0, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_DBG_FHTX_UC_PKT_CNT] = {
		ecpriss_xbar_hal_reg_construct_dummy,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09220000, 0x2198, 0, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_DBG_C2CRX_PKT_CNT_n] = {
		ecpriss_xbar_hal_reg_construct_dummy,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09220000, 0x2200, 0x4, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_DBG_C2CRX_DMA_PKT_CNT] = {
		ecpriss_xbar_hal_reg_construct_dummy,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09220000, 0x2230, 0, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_DBG_C2CRX_ERR_PKT_CNT] = {
		ecpriss_xbar_hal_reg_construct_dummy,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09220000, 0x2234, 0, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_DBG_C2CTX_PKT_CNT_n] = {
		ecpriss_xbar_hal_reg_construct_dummy,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09220000, 0x2260, 0x4, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_DBG_C2CTX_FH_PKT_OVF_CNT] = {
		ecpriss_xbar_hal_reg_construct_dummy,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09220000, 0x2290, 0, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_DBG_C2CTX_DMA_PKT_CNT] = {
		ecpriss_xbar_hal_reg_construct_dummy,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09220000, 0x2300, 0, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_DBG_OCTX_C2C_PKT_DROP_CNT] = {
		ecpriss_xbar_hal_reg_construct_dummy,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09220000, 0x2304, 0, 0, 0, 0,0},
	[ECPRISS_XBAR_HW_v1_0][	ECPRI_XBAR_XBAR_DBG_OCTX_PKT_CNT_n] = {
		ecpriss_xbar_hal_reg_construct_dummy,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09220000, 0x2310, 0x4, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_DBG_OCRX_PKT_CNT_n] = {
		ecpriss_xbar_hal_reg_construct_dummy,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09220000, 0x2320, 0x4, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_DBG_OCRX_FH_PKT_CNT_n] = {
		ecpriss_xbar_hal_reg_construct_dummy,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09220000, 	0x2330, 0x4, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_DBG_OCRX_C2C_PKT_CNT_n] = {
		ecpriss_xbar_hal_reg_construct_dummy,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09220000, 0x2360, 0x4, 0, 0, 0, 0x0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT] = {
		ecpriss_xbar_hal_reg_construct_dummy,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09220000, 0x2370, 0x0, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT] = {
		ecpriss_xbar_hal_reg_construct_dummy,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09220000, 	0x23A0, 0x0, 0, 0, 0, 0},
	[ECPRISS_XBAR_HW_v1_0][ECPRI_XBAR_XBAR_DBG_C2CRX_UNKNOWN_PCID_CNT] = {
		ecpriss_xbar_hal_reg_construct_dummy,
		ecpriss_xbar_hal_reg_parse_dummy,
		0x09220000, 0x23D0, 0x0, 0, 0, 0, 0}
};





/*
 * ecpriss_xbar_hal_reg_init() - Build the registers information table
 *  See ecpriss_xbar_hal_reg_objs[][] comments
 *
 * Note: As global variables are initialized with zero, any un-overridden
 *  register entry will be zero. By this we recognize them.
 */
#if 1
int ecpriss_xbar_hal_reg_init(struct device *dev)
{
	int result = 0;
	/* setup ECPRISS register access */

	pr_err(" ecpriss_xbar_hal_reg_init #### ");
	do
	{
		ecpriss_xbar_hal_ctx.hw_type = ECPRISS_XBAR_HW_v1_0;
		ecpriss_xbar_hal_ctx.ecpriss_pdev = dev;

		ecpriss_xbar_hal_ctx.phy_base = ECPRISS_XBAR_REG_BASE_ADDRESS;
		pr_err("Mapping  XBAR HAL reg space : 0x%x\n", ecpriss_xbar_hal_ctx.phy_base);

		ecpriss_xbar_hal_ctx.base = ioremap(ecpriss_xbar_hal_ctx.phy_base,ECPRISS_XBAR_REG_SIZE);
		pr_err("XBAR HAL reg mapped : 0x%x\n", ecpriss_xbar_hal_ctx.base);

		if (!ecpriss_xbar_hal_ctx.base) {
			pr_err(":ecpriss_xbar_base ioremap err\n");
			result = -EFAULT;
			break;
		}
	}while(0);

	return result;
}
#endif

int ecpriss_xbar_hal_lut_reg_init(struct device *dev)
{
	int result = 0;
	/* setup ECPRISS register access */
	do
	{
		ecpriss_xbar_hal_ctx.lut_phy_base = FH_TABLE_LUT_BASE_ADDRESS;

		ecpriss_xbar_hal_ctx.lut_base = ioremap(ecpriss_xbar_hal_ctx.lut_phy_base, ECPRISS_XBAR_LUT_SIZE);

		if (!ecpriss_xbar_hal_ctx.lut_base) {
			pr_err(":ecpriss-base ioremap err\n");
			result = -EFAULT;
			break;
		}
	}while(0);

	return result;
}

uint32_t ecpriss_xbar_reg_read(ecpriss_xbar_hal_reg_type_e  reg_type, uint32_t offset)
{
	uint32_t val = 0;
	if(reg_type == ECPRISS_XBAR_GLOBAL) {
		val = ioread32(ecpriss_xbar_hal_ctx.base + offset);
	}
	else if(reg_type == ECPRISS_XBAR_LUT) {
		val = ioread32(ecpriss_xbar_hal_ctx.lut_base + offset);
	}
	return val;
}



void ecpriss_xbar_reg_write(ecpriss_xbar_hal_reg_type_e  reg_type,
		uint32_t offset,
		uint32_t val)
{
	if(reg_type == ECPRISS_XBAR_GLOBAL) {
		iowrite32(val, ecpriss_xbar_hal_ctx.base + offset);
	}
	else if(reg_type == ECPRISS_XBAR_LUT) {
		iowrite32(val, ecpriss_xbar_hal_ctx.lut_base + offset);
	}
	return;
}




/*
 * ecpriss_xbar_hal_read_reg_n() - Get n parameterized reg value
 */
u32 ecpriss_xbar_hal_read_reg(ecpriss_xbar_hal_reg_type_e  reg_type,
		enum ecpriss_xbar_hal_reg_name reg)
{
	u32 offset;
	int val=0;
	if (reg >= ECPRI_XBAR_XBAR_MAX) {
		pr_err("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return -EINVAL;
	}

	//	pr_info("read from %s \n",
	//	ecpriss_xbar_hal_reg_name_str(reg));

	offset = ecpriss_xbar_hal_reg_objs[ecpriss_xbar_hal_ctx.hw_type][reg].offset;
	if (offset == -1) {
		pr_err("Read access to obsolete reg=%s\n",
				ecpriss_xbar_hal_reg_name_str(reg));
		WARN_ON(1);
		return -EPERM;
	}
	//offset += ecpriss_xbar_hal_reg_objs[ecpriss_xbar_hal_ctx.hw_type][reg].n_ofst * n;
	val =ecpriss_xbar_reg_read(reg_type,offset);
	return val;
}



/*
 * ecpriss_xbar_hal_read_reg_n() - Get n parameterized reg value
 */
u32 ecpriss_xbar_hal_read_reg_n(ecpriss_xbar_hal_reg_type_e  reg_type,
		enum ecpriss_xbar_hal_reg_name reg,
		u32 n)
{
	u32 offset;
	int val=0;
	if (reg >= ECPRI_XBAR_XBAR_MAX) {
		pr_err("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return -EINVAL;
	}

	//pr_info("read from %s n=%u\n",
	//ecpriss_xbar_hal_reg_name_str(reg), n);

	offset = ecpriss_xbar_hal_reg_objs[ecpriss_xbar_hal_ctx.hw_type][reg].offset;
	if (offset == -1) {
		pr_err("Read access to obsolete reg=%s\n",
				ecpriss_xbar_hal_reg_name_str(reg));
		WARN_ON(1);
		return -EPERM;
	}
	offset += ecpriss_xbar_hal_reg_objs[ecpriss_xbar_hal_ctx.hw_type][reg].n_ofst * n;
	val =ecpriss_xbar_reg_read(reg_type,offset);
	return val;
}



/*
 * ecpriss_xbar_hal_read_reg_mn() - Get mn parameterized reg value
 */
u32 ecpriss_xbar_hal_read_reg_mn(ecpriss_xbar_hal_reg_type_e  reg_type,
		enum ecpriss_xbar_hal_reg_name reg,
		u32 m,
		u32 n)
{
	u32 offset;
	int val=0;
	if (reg >= ECPRI_XBAR_XBAR_MAX) {
		pr_err("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return -EINVAL;
	}

	//pr_info("read %s m=%u n=%u\n",
	//ecpriss_xbar_hal_reg_name_str(reg), m, n);
	offset = ecpriss_xbar_hal_reg_objs[ecpriss_xbar_hal_ctx.hw_type][reg].offset;
	if (offset == -1) {
		pr_err("Read access to obsolete reg=%s\n",
				ecpriss_xbar_hal_reg_name_str(reg));
		WARN_ON_ONCE(1);
		return -EPERM;
	}

	offset += ecpriss_xbar_hal_reg_objs[ecpriss_xbar_hal_ctx.hw_type][reg].m_ofst * m;
	offset += ecpriss_xbar_hal_reg_objs[ecpriss_xbar_hal_ctx.hw_type][reg].n_ofst * n;
	val =ecpriss_xbar_reg_read(reg_type,offset);
	return val;
}



/*
 * ecpriss_xbar_hal_write_reg_mn() - Write to m/n parameterized reg a raw value
 */
void ecpriss_xbar_hal_write_reg_mn(ecpriss_xbar_hal_reg_type_e  reg_type,
		enum ecpriss_xbar_hal_reg_name reg,
		u32 m,
		u32 n,
		u32 val)
{
	u32 offset;

	if (reg >= ECPRI_XBAR_XBAR_MAX) {
		pr_err("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return;
	}

	//	pr_info("write to %s m=%u n=%u val=%u\n",
	//	ecpriss_xbar_hal_reg_name_str(reg), m, n, val);
	offset = ecpriss_xbar_hal_reg_objs[ecpriss_xbar_hal_ctx.hw_type][reg].offset;
	if (offset == -1) {
		pr_err("Write access to obsolete reg=%s\n",
				ecpriss_xbar_hal_reg_name_str(reg));
		WARN_ON(1);
		return;
	}

	offset += ecpriss_xbar_hal_reg_objs[ecpriss_xbar_hal_ctx.hw_type][reg].m_ofst * m;
	offset += ecpriss_xbar_hal_reg_objs[ecpriss_xbar_hal_ctx.hw_type][reg].n_ofst * n;
	ecpriss_xbar_reg_write(reg_type,offset,val);
	return;
}

/*
 * ecpriss_xbar_hal_write_reg_mn() - Write to m/n parameterized reg a raw value
 */
void ecpriss_xbar_hal_write_reg_mn_fields(ecpriss_xbar_hal_reg_type_e  reg_type,
		enum ecpriss_xbar_hal_reg_name reg,
		u32 m,
		u32 n,
		void *fields)
{
	u32 offset;
	u32 val = 0;
	if (reg >= ECPRI_XBAR_XBAR_MAX) {
		pr_err("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return;
	}

	//pr_info("write to %s m=%u n=%u val=%u\n",
	//ecpriss_xbar_hal_reg_name_str(reg), m, n, val);
	offset = ecpriss_xbar_hal_reg_objs[ecpriss_xbar_hal_ctx.hw_type][reg].offset;
	if (offset == -1) {
		pr_err("Write access to obsolete reg=%s\n",
				ecpriss_xbar_hal_reg_name_str(reg));
		WARN_ON(1);
		return;
	}

	offset += ecpriss_xbar_hal_reg_objs[ecpriss_xbar_hal_ctx.hw_type][reg].m_ofst * m;
	offset += ecpriss_xbar_hal_reg_objs[ecpriss_xbar_hal_ctx.hw_type][reg].n_ofst * n;
	ecpriss_xbar_hal_reg_objs[ecpriss_xbar_hal_ctx.hw_type][reg].construct(reg, fields, &val);
	ecpriss_xbar_reg_write(reg_type,offset,val);
}

u32 ecpriss_xbar_hal_read_reg_mn_fields(ecpriss_xbar_hal_reg_type_e  reg_type,
		enum ecpriss_xbar_hal_reg_name reg,
		u32 m,
		u32 n,
		void *fields)
{
	u32 val = 0;
	u32 offset;

	if (!fields) {
		pr_err("Input error fields\n");
		WARN_ON(1);
		return -EINVAL;
	}

	if (reg >= ECPRI_XBAR_XBAR_MAX) {
		pr_err("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return -EINVAL;
	}

	//pr_info("read from %s n=%u and parse it\n",
	//	ecpriss_xbar_hal_reg_name_str(reg), n);
	offset = ecpriss_xbar_hal_reg_objs[ecpriss_xbar_hal_ctx.hw_type][reg].offset;
	if (offset == -1) {
		pr_err("Read access to obsolete reg=%s\n",
				ecpriss_xbar_hal_reg_name_str(reg));
		WARN_ON(1);
		return -EPERM;
	}
	offset += ecpriss_xbar_hal_reg_objs[ecpriss_xbar_hal_ctx.hw_type][reg].m_ofst * m;
	offset += ecpriss_xbar_hal_reg_objs[ecpriss_xbar_hal_ctx.hw_type][reg].n_ofst * n;
	val =ecpriss_xbar_reg_read(reg_type,offset);
	ecpriss_xbar_hal_reg_objs[ecpriss_xbar_hal_ctx.hw_type][reg].parse(reg, fields, val);
	return val;
}

/*
 * ecpriss_xbar_hal_read_reg_n_fields() - Get the parsed value of n parameterized reg
 */
u32 ecpriss_xbar_hal_read_reg_n_fields(ecpriss_xbar_hal_reg_type_e  reg_type,
		enum ecpriss_xbar_hal_reg_name reg,
		u32 n,
		void *fields)
{
	u32 val = 0;
	u32 offset;

	if (!fields) {
		pr_err("Input error fields\n");
		WARN_ON(1);
		return -EINVAL;
	}

	if (reg >= ECPRI_XBAR_XBAR_MAX) {
		pr_err("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return -EINVAL;
	}

	//	pr_info("read from %s n=%u and parse it\n",	ecpriss_xbar_hal_reg_name_str(reg), n);

	offset = ecpriss_xbar_hal_reg_objs[ecpriss_xbar_hal_ctx.hw_type][reg].offset;
	pr_info("read reg ofst 0x%x \n",	offset);

	if (offset == -1) {
		pr_err("Read access to obsolete reg=%s\n",
				ecpriss_xbar_hal_reg_name_str(reg));
		WARN_ON(1);
		return -EPERM;
	}
	offset += ecpriss_xbar_hal_reg_objs[ecpriss_xbar_hal_ctx.hw_type][reg].n_ofst * n;
	//	pr_info("read reg ofst after n_ofst adjust 0x%x \n",	offset);

	val = ecpriss_xbar_reg_read(reg_type,offset);
	ecpriss_xbar_hal_reg_objs[ecpriss_xbar_hal_ctx.hw_type][reg].parse(reg, fields, val);

	return val;
}

/*
 * ecpriss_xbar_hal_write_reg_n_fields() - Write to n parameterized reg a prased value
 */
void ecpriss_xbar_hal_write_reg_n_fields(ecpriss_xbar_hal_reg_type_e  reg_type,
		enum ecpriss_xbar_hal_reg_name reg,
		u32 n,
		const void *fields)
{
	u32 val = 0;
	u32 offset;

	if (!fields) {
		pr_err("Input error fields=%pK\n", fields);
		WARN_ON(1);
		return;
	}

	if (reg >= ECPRI_XBAR_XBAR_MAX) {
		pr_err("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return;
	}

	// pr_info("write to %s n=%u after constructing it\n",
	//ecpriss_xbar_hal_reg_name_str(reg), n);
	offset = ecpriss_xbar_hal_reg_objs[ecpriss_xbar_hal_ctx.hw_type][reg].offset;
	if (offset == -1) {
		pr_err("Write access to obsolete reg=%s\n",
				ecpriss_xbar_hal_reg_name_str(reg));
		WARN_ON(1);
		return;
	}
	offset += ecpriss_xbar_hal_reg_objs[ecpriss_xbar_hal_ctx.hw_type][reg].n_ofst * n;
	ecpriss_xbar_hal_reg_objs[ecpriss_xbar_hal_ctx.hw_type][reg].construct(reg, fields, &val);
	ecpriss_xbar_reg_write(reg_type,offset,val);
	return;
}
