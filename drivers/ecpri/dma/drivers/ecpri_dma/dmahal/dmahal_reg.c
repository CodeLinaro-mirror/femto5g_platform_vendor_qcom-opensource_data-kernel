/*
 * SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include "dmahal_i.h"
#include "dmahal_reg.h"
#include "dmahal_reg_i.h"

#define DMA_MAX_MSG_LEN 4096

#define DMA_BIT_MAP_CELL_NUM(num) ((num) >> 5)
#define DMA_BIT_MAP_CELL_MSK(num) \
	(1 << (num - (DMA_BIT_MAP_CELL_NUM(num) << 5)))

enum ecpri_dma_hal_reg_attr {
	ECPRI_DMA_HAL_REG_ATTR_CMD_REG = 0,
	ECPRI_DMA_HAL_REG_ATTR_READ_ONLY = 1,
	ECPRI_DMA_HAL_REG_ATTR_WRITE_ONLY = 2,
	ECPRI_DMA_HAL_REG_ATTR_READ_WRITE = 3,
};

static const char *ecpri_dma_reg_name_to_str[DMA_REG_MAX] = {
	__stringify(ECPRI_DMA_ECPRI_HW_PARAMS_0),
	__stringify(ECPRI_DMA_ECPRI_NFAPI_CFG_0),
	__stringify(ECPRI_DMA_ECPRI_NFAPI_CFG_1),
	__stringify(ECPRI_DMA_ECPRI_NFAPI_CFG_2),
	__stringify(ECPRI_DMA_ECPRI_DMA_STREAM_CTRL),
	__stringify(ECPRI_DMA_ECPRI_NSO_CFG),
	__stringify(ECPRI_DMA_ECPRI_NSO_JUMBO_PKT_CFG),
	__stringify(ECPRI_DMA_ECPRI_IRQ_STTS_EE_n),
	__stringify(ECPRI_DMA_ECPRI_IRQ_EN_EE_n),
	__stringify(ECPRI_DMA_ECPRI_IRQ_CLR_EE_n),
	__stringify(ECPRI_DMA_ECPRI_ENDP_CFG_DEST_n),
	__stringify(ECPRI_DMA_ECPRI_ENDP_CFG_XBAR_n),
	__stringify(ECPRI_DMA_ECPRI_DMA_EXCEPTION_CHANNEL),
	__stringify(ECPRI_DMA_ECPRI_ENDP_CFG_AGGR_n),
	__stringify(ECPRI_DMA_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_n),
	__stringify(ECPRI_DMA_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n),
	__stringify(ECPRI_DMA_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n),
	__stringify(ECPRI_DMA_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n),
	__stringify(ECPRI_DMA_ECPRI_ENDP_GSI_CFG_n),
	__stringify(ECPRI_SPARE_REG),
};

static void ecpri_dma_reg_construct_dummy(enum ecpri_dma_hal_reg_name reg,
	const void *fields, u32 *val)
{
	DMAHAL_ERR("No construct function for %s\n",
		ecpri_dma_hal_reg_name_str(reg));
	WARN(1, "invalid register operation");
}

static void ecpri_dma_reg_parse_dummy(enum ecpri_dma_hal_reg_name reg,
	void *fields, u32 val)
{
	DMAHAL_ERR("No parse function for %s\n",
		ecpri_dma_hal_reg_name_str(reg));
	WARN(1, "invalid register operation");
}

static void ecpri_dma_reg_parse_hw_params_0(enum ecpri_dma_hal_reg_name reg,
	void *fields, u32 val)
{
	ecpri_hwio_def_ecpri_hw_params_0_s *hw_params0 =
		(ecpri_hwio_def_ecpri_hw_params_0_s *)fields;

	hw_params0->dst_channel_n = DMA_GETFIELD_FROM_REG(val,
		HWIO_ECPRI_HW_PARAMS_0_DST_CHANNEL_N_SHFT,
		HWIO_ECPRI_HW_PARAMS_0_DST_CHANNEL_N_BMSK);

	hw_params0->src_channel_n = DMA_GETFIELD_FROM_REG(val,
		HWIO_ECPRI_HW_PARAMS_0_SRC_CHANNEL_N_SHFT,
		HWIO_ECPRI_HW_PARAMS_0_SRC_CHANNEL_N_BMSK);

	hw_params0->total_channels_n = DMA_GETFIELD_FROM_REG(val,
		HWIO_ECPRI_HW_PARAMS_0_TOTAL_CHANNELS_N_SHFT,
		HWIO_ECPRI_HW_PARAMS_0_TOTAL_CHANNELS_N_BMSK);
}

static void ecpri_dma_reg_construct_nfapi_cfg_0(enum ecpri_dma_hal_reg_name reg,
	const void *fields, u32 *val)
{
	ecpri_hwio_def_ecpri_nfapi_cfg_0_s *nfapi_cfg_0 =
		(ecpri_hwio_def_ecpri_nfapi_cfg_0_s *)fields;

	DMA_SETFIELD_IN_REG(*val, nfapi_cfg_0->header_length,
		HWIO_ECPRI_NFAPI_CFG_0_HEADER_LENGTH_SHFT,
		HWIO_ECPRI_NFAPI_CFG_0_HEADER_LENGTH_BMSK);
}

static void ecpri_dma_reg_construct_nfapi_cfg_1(enum ecpri_dma_hal_reg_name reg,
	const void *fields, u32 *val)
{
	ecpri_hwio_def_ecpri_nfapi_cfg_1_s *nfapi_cfg_1 =
		(ecpri_hwio_def_ecpri_nfapi_cfg_1_s *)fields;

	DMA_SETFIELD_IN_REG(*val, nfapi_cfg_1->byte_offset_offset,
		HWIO_ECPRI_NFAPI_CFG_1_BYTE_OFFSET_OFFSET_SHFT,
		HWIO_ECPRI_NFAPI_CFG_1_BYTE_OFFSET_OFFSET_BMSK);
	DMA_SETFIELD_IN_REG(*val, nfapi_cfg_1->total_sdu_length_offset,
		HWIO_ECPRI_NFAPI_CFG_1_TOTAL_SDU_LENGTH_OFFSET_SHFT,
		HWIO_ECPRI_NFAPI_CFG_1_TOTAL_SDU_LENGTH_OFFSET_BMSK);
	DMA_SETFIELD_IN_REG(*val, nfapi_cfg_1->sequence_number_offset,
		HWIO_ECPRI_NFAPI_CFG_1_SEQUENCE_NUMBER_OFFSET_SHFT,
		HWIO_ECPRI_NFAPI_CFG_1_SEQUENCE_NUMBER_OFFSET_BMSK);
	DMA_SETFIELD_IN_REG(*val, nfapi_cfg_1->time_stamp_offset,
		HWIO_ECPRI_NFAPI_CFG_1_TIME_STAMP_OFFSET_SHFT,
		HWIO_ECPRI_NFAPI_CFG_1_TIME_STAMP_OFFSET_BMSK);
}

static void ecpri_dma_reg_construct_nfapi_cfg_2(enum ecpri_dma_hal_reg_name reg,
	const void *fields, u32 *val)
{
	ecpri_hwio_def_ecpri_nfapi_cfg_2_s *nfapi_cfg_2 =
		(ecpri_hwio_def_ecpri_nfapi_cfg_2_s *)fields;

	DMA_SETFIELD_IN_REG(*val, nfapi_cfg_2->byte_offset_size,
		HWIO_ECPRI_NFAPI_CFG_2_BYTE_OFFSET_SIZE_SHFT,
		HWIO_ECPRI_NFAPI_CFG_2_BYTE_OFFSET_SIZE_BMSK);
	DMA_SETFIELD_IN_REG(*val, nfapi_cfg_2->total_sdu_length_size,
		HWIO_ECPRI_NFAPI_CFG_2_TOTAL_SDU_LENGTH_SIZE_SHFT,
		HWIO_ECPRI_NFAPI_CFG_2_TOTAL_SDU_LENGTH_SIZE_BMSK);
	DMA_SETFIELD_IN_REG(*val, nfapi_cfg_2->sequence_number_size,
		HWIO_ECPRI_NFAPI_CFG_2_SEQUENCE_NUMBER_SIZE_SHFT,
		HWIO_ECPRI_NFAPI_CFG_2_SEQUENCE_NUMBER_SIZE_BMSK);
	DMA_SETFIELD_IN_REG(*val, nfapi_cfg_2->time_stamp_size,
		HWIO_ECPRI_NFAPI_CFG_2_TIME_STAMP_SIZE_SHFT,
		HWIO_ECPRI_NFAPI_CFG_2_TIME_STAMP_SIZE_BMSK);
}

static void ecpri_dma_reg_construct_dma_stream_ctrl(enum ecpri_dma_hal_reg_name reg,
	const void *fields, u32 *val)
{
	ecpri_hwio_def_ecpri_dma_stream_ctrl_s *stream_ctrl =
		(ecpri_hwio_def_ecpri_dma_stream_ctrl_s *)fields;

	DMA_SETFIELD_IN_REG(*val, stream_ctrl->mem_limit,
		HWIO_ECPRI_DMA_STREAM_CTRL_MEM_LIMIT_SHFT,
		HWIO_ECPRI_DMA_STREAM_CTRL_MEM_LIMIT_BMSK);
	DMA_SETFIELD_IN_REG(*val, stream_ctrl->c2c_limit,
		HWIO_ECPRI_DMA_STREAM_CTRL_C2C_LIMIT_SHFT,
		HWIO_ECPRI_DMA_STREAM_CTRL_C2C_LIMIT_BMSK);
	DMA_SETFIELD_IN_REG(*val, stream_ctrl->l2_limit,
		HWIO_ECPRI_DMA_STREAM_CTRL_L2_LIMIT_SHFT,
		HWIO_ECPRI_DMA_STREAM_CTRL_L2_LIMIT_BMSK);
	DMA_SETFIELD_IN_REG(*val, stream_ctrl->fh_limit,
		HWIO_ECPRI_DMA_STREAM_CTRL_FH_LIMIT_SHFT,
		HWIO_ECPRI_DMA_STREAM_CTRL_FH_LIMIT_BMSK);
}

static void ecpri_dma_reg_construct_nso_cfg(enum ecpri_dma_hal_reg_name reg,
	const void *fields, u32 *val)
{
	ecpri_hwio_def_ecpri_nso_cfg_s *nso_cfg =
		(ecpri_hwio_def_ecpri_nso_cfg_s *)fields;

	DMA_SETFIELD_IN_REG(*val, nso_cfg->nfapi_hdr_byte_swap,
		HWIO_ECPRI_NSO_CFG_NFAPI_HDR_BYTE_SWAP_SHFT,
		HWIO_ECPRI_NSO_CFG_NFAPI_HDR_BYTE_SWAP_BMSK);
	DMA_SETFIELD_IN_REG(*val, nso_cfg->min_pkt_enable,
		HWIO_ECPRI_NSO_CFG_MIN_PKT_ENABLE_SHFT,
		HWIO_ECPRI_NSO_CFG_MIN_PKT_ENABLE_BMSK);
	DMA_SETFIELD_IN_REG(*val, nso_cfg->max_num_of_sectors,
		HWIO_ECPRI_NSO_CFG_MAX_NUM_OF_SECTORS_SHFT,
		HWIO_ECPRI_NSO_CFG_MAX_NUM_OF_SECTORS_BMSK);
	DMA_SETFIELD_IN_REG(*val, nso_cfg->max_df_sectors,
		HWIO_ECPRI_NSO_CFG_MAX_DF_SECTORS_SHFT,
		HWIO_ECPRI_NSO_CFG_MAX_DF_SECTORS_BMSK);
}

static void ecpri_dma_reg_construct_nso_jumbo_pkt_cfg(enum ecpri_dma_hal_reg_name reg,
	const void *fields, u32 *val)
{
	ecpri_hwio_def_ecpri_nso_jumbo_pkt_cfg_s *nso_jumbo =
		(ecpri_hwio_def_ecpri_nso_jumbo_pkt_cfg_s *)fields;

	DMA_SETFIELD_IN_REG(*val, nso_jumbo->jumbo_max_pkt_len,
		HWIO_ECPRI_NSO_JUMBO_PKT_CFG_JUMBO_MAX_PKT_LEN_SHFT,
		HWIO_ECPRI_NSO_JUMBO_PKT_CFG_JUMBO_MAX_PKT_LEN_BMSK);
	DMA_SETFIELD_IN_REG(*val, nso_jumbo->jumbo_min_pkt_len,
		HWIO_ECPRI_NSO_JUMBO_PKT_CFG_JUMBO_MIN_PKT_LEN_SHFT,
		HWIO_ECPRI_NSO_JUMBO_PKT_CFG_JUMBO_MIN_PKT_LEN_BMSK);
}

static void ecpri_dma_reg_construct_endp_cfg_dest_n(enum ecpri_dma_hal_reg_name reg,
	const void *fields, u32 *val)
{
	ecpri_hwio_def_ecpri_endp_cfg_destn_s *endp_cfg =
		(ecpri_hwio_def_ecpri_endp_cfg_destn_s *)fields;

	DMA_SETFIELD_IN_REG(*val, endp_cfg->use_dest_cfg,
		HWIO_ECPRI_ENDP_CFG_DESTn_USE_DEST_CFG_SHFT,
		HWIO_ECPRI_ENDP_CFG_DESTn_USE_DEST_CFG_BMSK);
	DMA_SETFIELD_IN_REG(*val, endp_cfg->arb_weight,
		HWIO_ECPRI_ENDP_CFG_DESTn_ARB_WEIGHT_SHFT,
		HWIO_ECPRI_ENDP_CFG_DESTn_ARB_WEIGHT_BMSK);
	DMA_SETFIELD_IN_REG(*val, endp_cfg->dest_mem_channel,
		HWIO_ECPRI_ENDP_CFG_DESTn_DEST_MEM_CHANNEL_SHFT,
		HWIO_ECPRI_ENDP_CFG_DESTn_DEST_MEM_CHANNEL_BMSK);
}

/*
 * struct ecpri_dma_hal_reg_obj - Register H/W information for specific DMA version
 * @construct - CB to construct register value from abstracted structure
 * @parse - CB to parse register value to abstracted structure
 * @offset - register offset relative to base address
 * @n_ofst - N parameterized register sub-offset
 * @n_start - starting n for n_registers used for printing
 * @n_end - ending n for n_registers used for printing
 * @en_print - enable this register to be printed when the device crashes
 * @m_ofst - M parameterized register sub-offset
 * @attr - register permissions attribute
 */
struct ecpri_dma_hal_reg_obj {
	void (*construct)(enum ecpri_dma_hal_reg_name reg, const void *fields,
		u32 *val);
	void (*parse)(enum ecpri_dma_hal_reg_name reg, void *fields,
		u32 val);
	u32 offset;
	u32 n_ofst;
	int n_start;
	int n_end;
	bool en_print;
	u32 m_ofst;
	enum ecpri_dma_hal_reg_attr attr;
};

/*
 * This table contains the info regarding each register for DMAv3 and later.
 * Information like: offset and construct/parse functions.
 * All the information on the register on DMAv3 are statically defined below.
 * If information is missing regarding some register on some DMA version,
 *  the init function will fill it with the information from the previous
 *  DMA version.
 * Information is considered missing if all of the fields are 0.
 * If offset is -1, this means that the register is removed on the
 *  specific version.
 */
static struct ecpri_dma_hal_reg_obj ecpri_dma_hal_reg_objs[ECPRI_HW_MAX][DMA_REG_MAX] = {
	[ECPRI_HW_V1_0][HW_PARAMS_0] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_hw_params_0,
	HWIO_ECPRI_HW_PARAMS_0_OFFS, 0, 0, 0, 0, 0, HWIO_ECPRI_HW_PARAMS_0_ATTR},
	[ECPRI_HW_V1_0][ECPRI_NFAPI_CFG_0] = {
	ecpri_dma_reg_construct_nfapi_cfg_0, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_CFG_0_OFFS, 0, 0, 0, 0, 0, HWIO_ECPRI_NFAPI_CFG_0_ATTR},
	[ECPRI_HW_V1_0][ECPRI_NFAPI_CFG_1] = {
	ecpri_dma_reg_construct_nfapi_cfg_1, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_CFG_1_OFFS, 0, 0, 0, 0, 0, HWIO_ECPRI_NFAPI_CFG_1_ATTR},
	[ECPRI_HW_V1_0][ECPRI_NFAPI_CFG_2] = {
	ecpri_dma_reg_construct_nfapi_cfg_2, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_CFG_2_OFFS, 0, 0, 0, 0, 0, HWIO_ECPRI_NFAPI_CFG_2_ATTR},
	[ECPRI_HW_V1_0][ECPRI_DMA_STREAM_CTRL] = {
	ecpri_dma_reg_construct_dma_stream_ctrl, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_STREAM_CTRL_OFFS, 0, 0, 0, 0, 0, HWIO_ECPRI_DMA_STREAM_CTRL_ATTR},
	[ECPRI_HW_V1_0][ECPRI_NSO_CFG] = {
	ecpri_dma_reg_construct_nso_cfg, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NSO_CFG_OFFS, 0, 0, 0, 0, 0, HWIO_ECPRI_NSO_CFG_ATTR},
	[ECPRI_HW_V1_0][ECPRI_NSO_JUMBO_PKT_CFG] = {
	ecpri_dma_reg_construct_nso_jumbo_pkt_cfg, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NSO_JUMBO_PKT_CFG_OFFS, 0, 0, 0, 0, 0, HWIO_ECPRI_NSO_JUMBO_PKT_CFG_ATTR},
	[ECPRI_HW_V1_0][ECPRI_IRQ_STTS_EE_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_IRQ_STTS_EE_n_OFFS(0), HWIO_ECPRI_IRQ_STTS_EE_n_OFFS(1) -
	HWIO_ECPRI_IRQ_STTS_EE_n_OFFS(0), 0, HWIO_ECPRI_IRQ_STTS_EE_n_MAXn, 0, 0,
	HWIO_ECPRI_IRQ_STTS_EE_n_ATTR},
	[ECPRI_HW_V1_0][ECPRI_IRQ_EN_EE_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_IRQ_EN_EE_n_OFFS(0), HWIO_ECPRI_IRQ_EN_EE_n_OFFS(1) -
	HWIO_ECPRI_IRQ_EN_EE_n_OFFS(0), 0, HWIO_ECPRI_IRQ_EN_EE_n_MAXn, 0, 0,
	HWIO_ECPRI_IRQ_EN_EE_n_ATTR},
	[ECPRI_HW_V1_0][ECPRI_IRQ_CLR_EE_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_IRQ_CLR_EE_n_OFFS(0), HWIO_ECPRI_IRQ_CLR_EE_n_OFFS(1) -
	HWIO_ECPRI_IRQ_CLR_EE_n_OFFS(0), 0, HWIO_ECPRI_IRQ_CLR_EE_n_MAXn, 0, 0,
	HWIO_ECPRI_IRQ_CLR_EE_n_ATTR},
	[ECPRI_HW_V1_0][ECPRI_ENDP_CFG_DEST_n] = {
	ecpri_dma_reg_construct_endp_cfg_dest_n, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_CFG_DESTn_OFFS(0), HWIO_ECPRI_ENDP_CFG_DESTn_OFFS(1) -
	HWIO_ECPRI_ENDP_CFG_DESTn_OFFS(0), 0, HWIO_ECPRI_ENDP_CFG_DESTn_MAXn, 0, 0,
	HWIO_ECPRI_ENDP_CFG_DESTn_ATTR},
	[ECPRI_HW_V1_0][ECPRI_ENDP_CFG_XBAR_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_CFG_XBARn_OFFS(0), HWIO_ECPRI_ENDP_CFG_XBARn_OFFS(1) -
	HWIO_ECPRI_ENDP_CFG_XBARn_OFFS(0), 0, HWIO_ECPRI_ENDP_CFG_XBARn_MAXn, 0, 0,
	HWIO_ECPRI_ENDP_CFG_XBARn_ATTR},
	[ECPRI_HW_V1_0][ECPRI_DMA_EXCEPTION_CHANNEL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_EXCEPTION_CHANNEL_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_EXCEPTION_CHANNEL_ATTR},
	[ECPRI_HW_V1_0][ECPRI_ENDP_CFG_AGGR_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_CFG_AGGR_n_OFFS(0), HWIO_ECPRI_ENDP_CFG_AGGR_n_OFFS(1) -
	HWIO_ECPRI_ENDP_CFG_AGGR_n_OFFS(0), 0, HWIO_ECPRI_ENDP_CFG_AGGR_n_MAXn, 0, 0,
	HWIO_ECPRI_ENDP_CFG_AGGR_n_ATTR},
	[ECPRI_HW_V1_0][ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_n_OFFS(0), HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_n_OFFS(1) -
	HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_n_OFFS(0), 0, HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_n_MAXn, 0, 0,
	HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_n_ATTR},
	[ECPRI_HW_V1_0][ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_OFFS(0), HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_OFFS(1) -
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_OFFS(0), 0, HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_MAXn, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_ATTR},
	[ECPRI_HW_V1_0][ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_OFFS(0), HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_OFFS(1) -
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_OFFS(0), 0, HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_MAXn, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_ATTR},
	[ECPRI_HW_V1_0][ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_OFFS(0), HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_OFFS(1) -
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_OFFS(0), 0, HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_MAXn, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_ATTR},
	[ECPRI_HW_V1_0][ECPRI_ENDP_GSI_CFG_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_GSI_CFG_n_OFFS(0), HWIO_ECPRI_ENDP_GSI_CFG_n_OFFS(1) -
	HWIO_ECPRI_ENDP_GSI_CFG_n_OFFS(0), 0, HWIO_ECPRI_ENDP_GSI_CFG_n_MAXn, 0, 0,
	HWIO_ECPRI_ENDP_GSI_CFG_n_ATTR},
	[ECPRI_HW_V1_0][ECPRI_SPARE_REG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_SPARE_REG_OFFS, 0, 0, 0, 0, 0, HWIO_ECPRI_SPARE_REG_ATTR},
};

/*
 * ecpri_dma_hal_print_all_regs() - Loop and read and print all the valid registers
 *  Parameterized registers are also printed for all the valid ranges.
 *  Print to dmsg and IPC logs
 */
void ecpri_dma_hal_print_all_regs(bool print_to_dmesg)
{
	int i, j;
	struct ecpri_dma_hal_reg_obj *reg;

	DMAHAL_DBG("Printing all registers for ecpri_hw_ver %d\n",
		ecpri_dma_hal_ctx->ecpri_hw_ver);

	if (ecpri_dma_hal_ctx->ecpri_hw_ver >= ECPRI_HW_MAX) {
		DMAHAL_ERR("invalid DMA HW type (%d)\n", ecpri_dma_hal_ctx->ecpri_hw_ver);
		return;
	}

	for (i = 0; i < DMA_REG_MAX ; i++) {
		reg = &(ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][i]);

		/* skip obsolete registers */
		if (reg->offset == -1)
			continue;

		if (!reg->en_print)
			continue;

		j = reg->n_start;

		if (j == reg->n_end && (reg->n_ofst == 0)) {
			if (print_to_dmesg)
				DMAHAL_DBG_REG("%s=0x%x\n",
					ecpri_dma_hal_reg_name_str(i),
					ecpri_dma_hal_read_reg_n(i, j));
			else
				DMAHAL_DBG_REG_IPC_ONLY("%s=0x%x\n",
					ecpri_dma_hal_reg_name_str(i),
					ecpri_dma_hal_read_reg_n(i, j));
		} else {
			for (; j <= reg->n_end; j++) {
				if (print_to_dmesg)
					DMAHAL_DBG_REG("%s_%u=0x%x\n",
						ecpri_dma_hal_reg_name_str(i),
						j, ecpri_dma_hal_read_reg_n(i, j));
				else
					DMAHAL_DBG_REG_IPC_ONLY("%s_%u=0x%x\n",
						ecpri_dma_hal_reg_name_str(i),
						j, ecpri_dma_hal_read_reg_n(i, j));
			}
		}
	}
}

/*
 * ecpri_dma_hal_reg_init() - Build the registers information table
 *  See ecpri_dma_hal_reg_objs[][] comments
 *
 * Note: As global variables are initialized with zero, any un-overridden
 *  register entry will be zero. By this we recognize them.
 */
int ecpri_dma_hal_reg_init(enum ecpri_hw_ver ecpri_hw_ver)
{
	int i;
	int j;
	struct ecpri_dma_hal_reg_obj zero_obj;

	DMAHAL_DBG_LOW("Entry - HW_TYPE=%d\n", ecpri_hw_ver);

	if ((ecpri_hw_ver < ECPRI_HW_NONE) ||
		(ecpri_hw_ver >= ECPRI_HW_MAX)) {
		DMAHAL_ERR("invalid DMA HW type (%d)\n", ecpri_hw_ver);
		return -EINVAL;
	}

	memset(&zero_obj, 0, sizeof(zero_obj));
	for (i = ECPRI_HW_V1_0; i < ecpri_hw_ver; i++) {
		for (j = 0; j < DMA_REG_MAX ; j++) {
			if (!memcmp(&ecpri_dma_hal_reg_objs[i+1][j], &zero_obj,
				sizeof(struct ecpri_dma_hal_reg_obj))) {
				memcpy(&ecpri_dma_hal_reg_objs[i+1][j],
					&ecpri_dma_hal_reg_objs[i][j],
					sizeof(struct ecpri_dma_hal_reg_obj));
			} else {
				/*
				 * explicitly overridden register.
				 * Check validity
				 */
				if (!ecpri_dma_hal_reg_objs[i+1][j].construct) {
					DMAHAL_ERR(
					  "reg=%s with NULL construct func ecpri_hw_ver=%d\n",
					  ecpri_dma_hal_reg_name_str(j), i+1);
					WARN_ON(1);
				}
				if (!ecpri_dma_hal_reg_objs[i+1][j].parse) {
					DMAHAL_ERR(
					  "reg=%s with NULL parse func ecpri_hw_ver=%d\n",
					  ecpri_dma_hal_reg_name_str(j), i+1);
					WARN_ON(1);
				}
			}
		}
	}

	return 0;
}

/*
 * ecpri_dma_hal_reg_name_str() - returns string that represent the register
 * @reg_name: [in] register name
 */
const char *ecpri_dma_hal_reg_name_str(enum ecpri_dma_hal_reg_name reg_name)
{
	if (reg_name < 0 || reg_name >= DMA_REG_MAX) {
		DMAHAL_ERR("requested name of invalid reg=%d\n", reg_name);
		return "Invalid Register";
	}

	return ecpri_dma_reg_name_to_str[reg_name];
}

/*
 * ecpri_dma_hal_read_reg_n() - Get n parameterized reg value
 */
u32 ecpri_dma_hal_read_reg_n(enum ecpri_dma_hal_reg_name reg, u32 n)
{
	u32 offset;

	if (reg >= DMA_REG_MAX) {
		DMAHAL_ERR("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return -EINVAL;
	}

	if ((ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].attr &
		ECPRI_DMA_HAL_REG_ATTR_READ_ONLY) == 0) {
		DMAHAL_ERR("Register doesn't have READ permissions reg=%u\n", reg);
		WARN_ON(1);
		return -EINVAL;
	}

	DMAHAL_DBG_LOW("read from %s n=%u\n",
		ecpri_dma_hal_reg_name_str(reg), n);

	offset = ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].offset;
	if (offset == -1) {
		DMAHAL_ERR("Read access to obsolete reg=%s\n",
			ecpri_dma_hal_reg_name_str(reg));
		WARN_ON(1);
		return -EPERM;
	}
	offset += ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].n_ofst * n;
	return ioread32(ecpri_dma_hal_ctx->base + offset);
}

/*
* ecpri_dma_hal_read_ep_reg() - Get the raw value of a ep reg
*/
u32 ecpri_dma_hal_read_ep_reg(enum ecpri_dma_hal_reg_name reg, u32 ep_num)
{
	return ecpri_dma_hal_read_reg_n(reg, DMA_BIT_MAP_CELL_NUM(ep_num));
}

/*
 * ecpri_dma_hal_test_ep_bit() - return true if a ep bit is set
 */
bool ecpri_dma_hal_test_ep_bit(u32 reg_val, u32 ep_num)
{
	return !!(reg_val & DMA_BIT_MAP_CELL_MSK(ep_num));
}

/*
 * ecpri_dma_hal_get_ep_bit() - get ep bit set in the right offset
 */
u32 ecpri_dma_hal_get_ep_bit(u32 ep_num)
{
	return DMA_BIT_MAP_CELL_MSK(ep_num);
}
EXPORT_SYMBOL(ecpri_dma_hal_get_ep_bit);

/*
 * ecpri_dma_hal_get_ep_reg_idx() - get ep reg index according to ep num
 */
u32 ecpri_dma_hal_get_ep_reg_idx(u32 ep_num)
{
	return DMA_BIT_MAP_CELL_NUM(ep_num);
}
EXPORT_SYMBOL(ecpri_dma_hal_get_ep_reg_idx);

/*
 * ecpri_dma_hal_read_reg_mn() - Get mn parameterized reg value
 */
u32 ecpri_dma_hal_read_reg_mn(enum ecpri_dma_hal_reg_name reg, u32 m, u32 n)
{
	u32 offset;

	if (reg >= DMA_REG_MAX) {
		DMAHAL_ERR("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return -EINVAL;
	}

	if ((ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].attr &
		ECPRI_DMA_HAL_REG_ATTR_READ_ONLY) == 0) {
		DMAHAL_ERR("Register doesn't have READ permissions reg=%u\n", reg);
		WARN_ON(1);
		return -EINVAL;
	}

	DMAHAL_DBG_LOW("read %s m=%u n=%u\n",
		ecpri_dma_hal_reg_name_str(reg), m, n);
	offset = ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].offset;
	if (offset == -1) {
		DMAHAL_ERR("Read access to obsolete reg=%s\n",
			ecpri_dma_hal_reg_name_str(reg));
		WARN_ON_ONCE(1);
		return -EPERM;
	}

	offset += ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].m_ofst * m;
	offset += ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].n_ofst * n;
	return ioread32(ecpri_dma_hal_ctx->base + offset);
}

/*
* ecpri_dma_hal_read_ep_reg_n() - Get n parameterized reg value according to ep
*/
u32 ecpri_dma_hal_read_ep_reg_n(enum ecpri_dma_hal_reg_name reg, u32 n, u32 ep_num)
{
	return ecpri_dma_hal_read_reg_mn(reg, DMA_BIT_MAP_CELL_NUM(ep_num), n);
}

/*
 * ecpri_dma_hal_write_reg_mn() - Write to m/n parameterized reg a raw value
 */
void ecpri_dma_hal_write_reg_mn(enum ecpri_dma_hal_reg_name reg, u32 m, u32 n, u32 val)
{
	u32 offset;

	if (reg >= DMA_REG_MAX) {
		DMAHAL_ERR("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return;
	}

	if ((ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].attr &
		ECPRI_DMA_HAL_REG_ATTR_WRITE_ONLY) == 0) {
		DMAHAL_ERR("Register doesn't have WRITE permissions reg=%u\n", reg);
		WARN_ON(1);
		return;
	}

	DMAHAL_DBG_LOW("write to %s m=%u n=%u val=%x\n",
		ecpri_dma_hal_reg_name_str(reg), m, n, val);
	offset = ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].offset;
	if (offset == -1) {
		DMAHAL_ERR("Write access to obsolete reg=%s\n",
			ecpri_dma_hal_reg_name_str(reg));
		WARN_ON(1);
		return;
	}

	offset += ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].m_ofst * m;
	offset += ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].n_ofst * n;
	iowrite32(val, ecpri_dma_hal_ctx->base + offset);
}

/*
 * ecpri_dma_hal_write_ep_reg() - Write to ep reg a raw value
 */
void ecpri_dma_hal_write_ep_reg(enum ecpri_dma_hal_reg_name reg, u32 ep_num, u32 val)
{
	return ecpri_dma_hal_write_reg_n(reg, DMA_BIT_MAP_CELL_NUM(ep_num), val);
}

/*
 * ecpri_dma_hal_write_ep_reg_n() - Write to ep reg a raw value of n parameterized reg
 */
void ecpri_dma_hal_write_ep_reg_n(enum ecpri_dma_hal_reg_name reg, u32 n, u32 ep_num, u32 val)
{
	return ecpri_dma_hal_write_reg_mn(reg, DMA_BIT_MAP_CELL_NUM(ep_num), n, val);
}

/*
 * ecpri_dma_hal_read_reg_n_fields() - Get the parsed value of n parameterized reg
 */
u32 ecpri_dma_hal_read_reg_n_fields(enum ecpri_dma_hal_reg_name reg, u32 n, void *fields)
{
	u32 val = 0;
	u32 offset;

	if (!fields) {
		DMAHAL_ERR("Input error fields\n");
		WARN_ON(1);
		return -EINVAL;
	}

	if (reg >= DMA_REG_MAX) {
		DMAHAL_ERR("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return -EINVAL;
	}

	if ((ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].attr &
		ECPRI_DMA_HAL_REG_ATTR_READ_ONLY) == 0) {
		DMAHAL_ERR("Register doesn't have READ permissions reg=%u\n", reg);
		WARN_ON(1);
		return -EINVAL;
	}

	DMAHAL_DBG_LOW("read from %s n=%u and parse it\n",
		ecpri_dma_hal_reg_name_str(reg), n);
	offset = ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].offset;
	if (offset == -1) {
		DMAHAL_ERR("Read access to obsolete reg=%s\n",
			ecpri_dma_hal_reg_name_str(reg));
		WARN_ON(1);
		return -EPERM;
	}
	offset += ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].n_ofst * n;
	val = ioread32(ecpri_dma_hal_ctx->base + offset);
	ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].parse(reg, fields, val);

	return val;
}

/*
 * ecpri_dma_hal_write_reg_n_fields() - Write to n parameterized reg a prased value
 */
void ecpri_dma_hal_write_reg_n_fields(enum ecpri_dma_hal_reg_name reg, u32 n,
		const void *fields)
{
	u32 val = 0;
	u32 offset;

	if (!fields) {
		DMAHAL_ERR("Input error fields=%px\n", fields);
		WARN_ON(1);
		return;
	}

	if (reg >= DMA_REG_MAX) {
		DMAHAL_ERR("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return;
	}

	if ((ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].attr &
		ECPRI_DMA_HAL_REG_ATTR_WRITE_ONLY) == 0) {
		DMAHAL_ERR("Register doesn't have WRITE permissions reg=%u\n", reg);
		WARN_ON(1);
		return;
	}

	DMAHAL_DBG_LOW("write to %s n=%u after constructing it\n",
		ecpri_dma_hal_reg_name_str(reg), n);
	offset = ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].offset;
	if (offset == -1) {
		DMAHAL_ERR("Write access to obsolete reg=%s\n",
			ecpri_dma_hal_reg_name_str(reg));
		WARN_ON(1);
		return;
	}
	offset += ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].n_ofst * n;
	ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].construct(reg, fields, &val);

	iowrite32(val, ecpri_dma_hal_ctx->base + offset);
}

/*
 * Get the offset of a m/n parameterized register
 */
u32 ecpri_dma_hal_get_reg_mn_ofst(enum ecpri_dma_hal_reg_name reg, u32 m, u32 n)
{
	u32 offset;

	if (reg >= DMA_REG_MAX) {
		DMAHAL_ERR("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return -EINVAL;
	}

	DMAHAL_DBG_LOW("get offset of %s m=%u n=%u\n",
		ecpri_dma_hal_reg_name_str(reg), m, n);
	offset = ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].offset;
	if (offset == -1) {
		DMAHAL_ERR("Access to obsolete reg=%s\n",
			ecpri_dma_hal_reg_name_str(reg));
		WARN_ON(1);
		return -EPERM;
	}

	offset += ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].m_ofst * m;
	offset += ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].n_ofst * n;

	return offset;
}

/*
 * Get the offset of a ep register according to ep index
 */
u32 ecpri_dma_hal_get_ep_reg_offset(enum ecpri_dma_hal_reg_name reg, u32 ep_num)
{
	return ecpri_dma_hal_get_reg_mn_ofst(reg, 0, DMA_BIT_MAP_CELL_NUM(ep_num));
}

/*
* Get the offset of a ep n register according to ep index and k
*/
u32 ecpri_dma_hal_get_reg_nk_offset(enum ecpri_dma_hal_reg_name reg, u32 n, u32 k)
{
	return ecpri_dma_hal_get_reg_mn_ofst(reg, k, n);
}

u32 ecpri_dma_hal_get_reg_base(void)
{
	if (!ecpri_dma_hal_ctx || ecpri_dma_hal_ctx->ecpri_dma_cfg_offset == 0)
		return 0;
	else
		return ecpri_dma_hal_ctx->ecpri_dma_cfg_offset;
}
