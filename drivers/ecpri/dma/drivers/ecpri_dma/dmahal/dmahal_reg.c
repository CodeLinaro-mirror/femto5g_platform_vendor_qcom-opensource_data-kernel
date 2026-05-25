/*
 * SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
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
	__stringify(ECPRI_HW_PARAMS_0),
	__stringify(ECPRI_HW_PARAMS_2),
	__stringify(ECPRI_NFAPI_CFG_0),
	__stringify(ECPRI_NFAPI_CFG_1),
	__stringify(ECPRI_NFAPI_CFG_2),
	__stringify(ECPRI_NFAPI_REASSEMBLY_CFG_0),
	__stringify(ECPRI_NFAPI_REASSEMBLY_FEC_0),
	__stringify(ECPRI_NFAPI_REASSEMBLY_FEC_1),
	__stringify(ECPRI_NFAPI_REASSEMBLY_FEC_2),
	__stringify(ECPRI_NFAPI_REASSEMBLY_FEC_3),
	__stringify(ECPRI_NFAPI_REASSEMBLY_FEC_4),
	__stringify(ECPRI_NFAPI_REASSEMBLY_FEC_5),
	__stringify(ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_PKT_CNT),
	__stringify(ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_LSB),
	__stringify(ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_MSB),
	__stringify(ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_PKT_CNT),
	__stringify(ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_LSB),
	__stringify(ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_MSB),
	__stringify(ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_PKT_CNT),
	__stringify(ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB),
	__stringify(ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB),
	__stringify(ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_PKT_CNT),
	__stringify(
		ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB),
	__stringify(
		ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB),
	__stringify(ECPRI_NFAPI_REASSEMBLY_STATE),
	__stringify(ECPRI_DMA_STREAM_CTRL),
	__stringify(ECPRI_DMA_STREAM_STATUS),
	__stringify(ECPRI_DMA_STREAM_ARB),
	__stringify(ECPRI_DMA_FL_PACKET_ID_CTRL),
	__stringify(ECPRI_DMA_FL_PACKET_ID_STATUS),
	__stringify(ECPRI_DMA_FL_MEMORY_SECTOR_CTRL),
	__stringify(ECPRI_DMA_FL_MEMORY_SECTOR_STATUS),
	__stringify(ECPRI_DMA_XBAR),
	__stringify(ECPRI_DMA_DBG_CTRL),
	__stringify(ECPRI_DMA_GBL_CFG),
	__stringify(ECPRI_DMA_TESTBUS_CTRL),
	__stringify(ECPRI_DMA_GP_REG3),
	__stringify(ECPRI_DMA_AOS_FIFO_STAT),
	__stringify(ECPRI_DMA_GP_STAT1),
	__stringify(ECPRI_DMA_TESTBUS),
	__stringify(ECPRI_DMA_GP_STAT3),
	__stringify(ECPRI_DMA_IDLE_REG),
	__stringify(ECPRI_DMA_EXCEPTION_CHANNEL),
	__stringify(ECPRI_DMA_PKT_DROP_FULL),
	__stringify(ECPRI_DMA_PKT_DROP_RE_EMPTY),
	__stringify(ECPRI_DMA_DPL_CFG),
	__stringify(ECPRI_DMA_TPDM_CFG),
	__stringify(ECPRI_NSO_CFG),
	__stringify(ECPRI_NSO_JUMBO_PKT_CFG),
	__stringify(ECPRI_NSO_SHORT_PKT_CFG),
	__stringify(ECPRI_NSO_LEN_ERR_STATUS_1),
	__stringify(ECPRI_NSO_LEN_ERR_STATUS_2),
	__stringify(ECPRI_NSO_LEN_ERR_STATUS_3),
	__stringify(ECPRI_NSO_DBG_MISC_INFO),
	__stringify(ECPRI_NSO_JUMBO_PKT_EN),
	__stringify(ECPRI_NSO_LEN_ERR_STATUS_HDR_n),
	__stringify(ECPRI_NSO_DBG_CNTXT_n_INFO_1),
	__stringify(ECPRI_NSO_DBG_CNTXT_n_INFO_2),
	__stringify(ECPRI_IRQ_STTS_EE_n),
	__stringify(ECPRI_IRQ_EN_EE_n),
	__stringify(ECPRI_IRQ_CLR_EE_n),
	__stringify(ECPRI_ENDP_CFG_DEST),
	__stringify(ECPRI_ENDP_CFG_XBAR),
	__stringify(ECPRI_ENDP_CFG_AGGR),
	__stringify(ECPRI_ENDP_NFAPI_REASSEMBLY_CFG),
	__stringify(ECPRI_ENDP_INIT_CTRL_STATUS),
	__stringify(ECPRI_ENDP_AXI_ATTR),
	__stringify(ECPRI_ENDP_YELLOW_RED_MARKER_CFG),
	__stringify(ECPRI_ENDP_GSI_CONS_BYTES_TLV),
	__stringify(ECPRI_ENDP_GSI_CONS_BYTES_AOS),
	__stringify(ECPRI_ENDP_GSI_IF_FIFO_CFG_TLV),
	__stringify(ECPRI_ENDP_GSI_IF_FIFO_CFG_AOS),
	__stringify(ECPRI_ENDP_CFG_VFID),
	__stringify(ECPRI_ENDP_GSI_CFG),
	__stringify(ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n),
	__stringify(ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n),
	__stringify(ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n),
	__stringify(ECPRI_YELLOW_MARKER_BELOW),
	__stringify(ECPRI_YELLOW_MARKER_BELOW_EN),
	__stringify(ECPRI_RED_MARKER_BELOW),
	__stringify(ECPRI_RED_MARKER_BELOW_EN),
	__stringify(ECPRI_YELLOW_MARKER_SHADOW),
	__stringify(ECPRI_RED_MARKER_SHADOW),
	__stringify(ECPRI_YELLOW_MARKER_ABOVE),
	__stringify(ECPRI_YELLOW_MARKER_ABOVE_EN),
	__stringify(ECPRI_RED_MARKER_ABOVE),
	__stringify(ECPRI_RED_MARKER_ABOVE_EN),
	__stringify(ECPRI_QMB_CFG),
	__stringify(ECPRI_QMB_0_STATUS),
	__stringify(ECPRI_QMB_1_STATUS),
	__stringify(ECPRI_QMB_CFG_PARAM),
	__stringify(ECPRI_QMB0_SNOC_MONITOR_CNT),
	__stringify(ECPRI_QMB1_SNOC_MONITOR_CNT),
	__stringify(ECPRI_GSI_SNOC_MONITOR_CNT),
	__stringify(ECPRI_GSI_TLV_FIFO_STATUS),
	__stringify(ECPRI_GSI_AOS_FIFO_STATUS),
	__stringify(ECPRI_GSI_EE_VFID),
	__stringify(ECPRI_ENDP_DPL_CFG),
	__stringify(ECPRI_DPL_TRIG_CTRL_n),
	__stringify(ECPRI_DPL_TRIG_A_n),
	__stringify(ECPRI_DPL_TRIG_B_n),
	__stringify(ECPRI_SPARE_REG),
	__stringify(ECPRI_DST_ACKMNGR_CMDQ_STATUS),
	__stringify(ECPRI_STATE_GSI_IF),
	__stringify(ECPRI_GEN_CFG),
	__stringify(ECPRI_CLKON_CFG),
	__stringify(ECPRI_AOS_CFG),
	__stringify(ECPRI_TIMERS_XO_CLK_DIV_CFG),
	__stringify(ECPRI_TIMERS_PULSE_GRAN_CFG),
	__stringify(ECPRI_QTIME_LSB),
	__stringify(ECPRI_QTIME_MSB),
	__stringify(ECPRI_SNOC_FEC),
	__stringify(ECPRI_SNOC_MONITORING_CFG),
	__stringify(ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY),
	__stringify(ECPRI_DST_ACKMNGR_CMDQ_COUNT),
	__stringify(ECPRI_STATE_GSI_TLV_FIFO_EMPTY),
	__stringify(ECPRI_STATE_GSI_AOS_FIFO_EMPTY),
	/* V2 section */
	__stringify(ECPRI_DMA_HW_PARAMS_1),
	__stringify(ECPRI_DMA_RAM_FIFO_CONTENT_LINE_l_WORD_n),
	__stringify(ECPRI_DMA_AHB2RAM_FIFOS_CFG),
	__stringify(ECPRI_DMA_SNIFFER_CTRL1),
	__stringify(ECPRI_DMA_SNIFFER_CTRL2),
	__stringify(ECPRI_DMA_SNIFFER_STAT),
	__stringify(ECPRI_DMA_LTE_DEBUG_CFG),
	__stringify(ECPRI_DMA_LTE_WATERMARKS),
	__stringify(ECPRI_DMA_STATUS_XBAR_FH_PORT_RX),
	__stringify(ECPRI_DMA_STATUS_XBAR_FH_PORT_TX),
	__stringify(ECPRI_DMA_STATUS_XBAR_C2C_PORT_RX),
	__stringify(ECPRI_DMA_STATUS_XBAR_C2C_PORT_TX),
	__stringify(ECPRI_DMA_INTERFACE_DDH_DF),
	__stringify(ECPRI_DMA_INTERFACE_DF_C2C),
	__stringify(ECPRI_DMA_INTERFACE_DF_NSO),
	__stringify(ECPRI_DMA_INTERFACE_DF_FH),
	__stringify(ECPRI_DMA_INTERFACE_DF_TXM),
	__stringify(ECPRI_DMA_INTERFACE_DDH_TXM),
	__stringify(ECPRI_DMA_STATUS_GSI0_A),
	__stringify(ECPRI_DMA_STATUS_GSI0_B),
	__stringify(ECPRI_DMA_STATUS_GSI1_A),
	__stringify(ECPRI_DMA_STATUS_GSI1_B),
	__stringify(ECPRI_DMA_STATUS_GSI2_A),
	__stringify(ECPRI_DMA_STATUS_GSI2_B),
	__stringify(ECPRI_DMA_XBAR_RX_PORT_DPL_STATUS),
	__stringify(ECPRI_DMA_STATUS_XBAR_RX_PORT_m),
	__stringify(ECPRI_DMA_STATUS_XBAR_RX_DROP),
	__stringify(ECPRI_DMA_ENDP_LTE_CFG_GSI_m_CH_n),
	__stringify(ECPRI_DMA_SDH_PREFETCH_LSB_GSI_m_CH_n),
	__stringify(ECPRI_DMA_SDH_PREFETCH_MSB_GSI_m_CH_n),
	__stringify(ECPRI_DMA_STATUS_LTE_PKT_DROP_FULL),
	__stringify(ECPRI_DMA_RATE_LIMITER),
	__stringify(ECPRI_DMA_DPL_MONITOR_CFG),
	__stringify(ECPRI_DMA_DPL_MONITOR_CNT_0),
	__stringify(ECPRI_DMA_DPL_MONITOR_CNT_1),
	__stringify(ECPRI_DMA_REDIRECT_CHANNEL),
	__stringify(ECPRI_DMA_STATUS_DST_DROP_PKT_GSI_m_REG_n),
	__stringify(ECPRI_DMA_STATUS_DST_DROP_PKT_CLEAR),
	__stringify(ECPRI_DMA_UNIT_CLK_ENABLE),
	__stringify(ECPRI_DMA_LTE_CFG),
	__stringify(ECPRI_DMA_STATUS_LTE_PKT_DROP_TLV_FIFO_EMPTY),
	__stringify(ECPRI_DMA_STATUS_PKT_DROP_TLV_FIFO_EMPTY),
	__stringify(ECPRI_DMA_LTE_LATENCY_BUFFER_WORD),
	__stringify(ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL),
	__stringify(ECPRI_DMA1_THROTTLE_THROTTLE_0_CGC_CNTRL),
	__stringify(ECPRI_DMA1_THROTTLE_THROTTLE_0_RESET_CNTRL),
	__stringify(ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG),
	__stringify(ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_PERIOD),
	__stringify(ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_COUNT),
	__stringify(ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_00),
	__stringify(ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_01),
	__stringify(ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_02),
	__stringify(ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_03),
	__stringify(ECPRI_DMA1_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT),
	__stringify(ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_CNTL),
	__stringify(ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_READBACK),
	__stringify(ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL),
	__stringify(ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_STATUS),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_CLEAR),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_CORE_CLOCKON_CONTROL),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON_SW_RESET),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON_CGC_CNTRL),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON_CLEAR),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON_BYTE_COUNT),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON_THRESHOLD),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MASK),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MATCH),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ENABLE),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON2_CLEAR),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON2_WINDOW_TIMER),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MASK),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MATCH),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MASK),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MATCH),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_PERIOD),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON_ACCEPT_COUNT),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNT),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON_IDLE_COUNT),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON_INTR_TARGET),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_CNTL),
	__stringify(ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_READBACK),
	__stringify(ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL),
	__stringify(ECPRI_DMA0_THROTTLE_THROTTLE_0_CGC_CNTRL),
	__stringify(ECPRI_DMA0_THROTTLE_THROTTLE_0_RESET_CNTRL),
	__stringify(ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG),
	__stringify(ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_PERIOD),
	__stringify(ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_COUNT),
	__stringify(ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_00),
	__stringify(ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_01),
	__stringify(ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_02),
	__stringify(ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_03),
	__stringify(ECPRI_DMA0_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT),
	__stringify(ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_CNTL),
	__stringify(ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_READBACK),
	__stringify(ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL),
	__stringify(ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_STATUS),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_CLEAR),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_CORE_CLOCKON_CONTROL),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON_SW_RESET),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON_CGC_CNTRL),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON_CLEAR),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON_BYTE_COUNT),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON_THRESHOLD),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MASK),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MATCH),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ENABLE),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON2_CLEAR),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON2_WINDOW_TIMER),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MASK),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MATCH),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MASK),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MATCH),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_PERIOD),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON_ACCEPT_COUNT),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNT),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON_IDLE_COUNT),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON_INTR_TARGET),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_CNTL),
	__stringify(ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_READBACK),
};

/* Constructs and parsers  */
static void ecpri_dma_reg_construct_dummy(enum ecpri_dma_hal_reg_name reg,
	const void* fields, u32* val)
{
	WARN(1, "invalid register operation");
	DMAHAL_ERR("No construct function for %s\n",
		ecpri_dma_hal_reg_name_str(reg));
}

static void ecpri_dma_reg_parse_dummy(enum ecpri_dma_hal_reg_name reg,
	void* fields, u32 val)
{
	DMAHAL_ERR("No parse function for %s\n",
		ecpri_dma_hal_reg_name_str(reg));
	WARN(1, "invalid register operation");
}

static void ecpri_dma_reg_construct_endp_cfg_xbar_v1(
	enum ecpri_dma_hal_reg_name reg, const void* fields, u32* val)
{
	struct ecpri_dma_ecpri_endp_cfg_xbar_fields* cfg_xbar_fields =
		(struct ecpri_dma_ecpri_endp_cfg_xbar_fields*)fields;
	ecpri_hwio_def_ecpri_endp_cfg_xbar_u* cfg_xbar_val =
		(ecpri_hwio_def_ecpri_endp_cfg_xbar_u*)val;

	cfg_xbar_val->def_v1.dest_stream = cfg_xbar_fields->dest_stream;
	cfg_xbar_val->def_v1.xbar_tid = cfg_xbar_fields->xbar_tid;
	cfg_xbar_val->def_v1.xbar_tuser = cfg_xbar_fields->xbar_tuser;
	cfg_xbar_val->def_v1.l2_segmentation_en = cfg_xbar_fields->l2_segmentation_en;
}

static void ecpri_dma_reg_construct_endp_cfg_xbar_v2(
	enum ecpri_dma_hal_reg_name reg, const void* fields, u32* val)
{
	struct ecpri_dma_ecpri_endp_cfg_xbar_fields* cfg_xbar_fields =
		(struct ecpri_dma_ecpri_endp_cfg_xbar_fields*)fields;
	ecpri_hwio_def_ecpri_endp_cfg_xbar_u* cfg_xbar_val =
		(ecpri_hwio_def_ecpri_endp_cfg_xbar_u*)val;

	cfg_xbar_val->def_v2.dest_stream = cfg_xbar_fields->dest_stream;
	cfg_xbar_val->def_v2.xbar_tid = cfg_xbar_fields->xbar_tid;
	cfg_xbar_val->def_v2.xbar_tuser = cfg_xbar_fields->xbar_tuser;
	cfg_xbar_val->def_v2.loopback_en = cfg_xbar_fields->loopback_en;
	cfg_xbar_val->def_v2.pre_hdr_en = cfg_xbar_fields->pre_hdr_en;
	cfg_xbar_val->def_v2.nfapi_without_offload =
		cfg_xbar_fields->nfapi_without_offload;
}

static void ecpri_dma_reg_parse_endp_cfg_xbar_v1(enum ecpri_dma_hal_reg_name reg,
	void* fields, u32 val)
{
	struct ecpri_dma_ecpri_endp_cfg_xbar_fields* cfg_xbar_fields =
		(struct ecpri_dma_ecpri_endp_cfg_xbar_fields*)fields;
	ecpri_hwio_def_ecpri_endp_cfg_xbar_u cfg_xbar_val =
		(ecpri_hwio_def_ecpri_endp_cfg_xbar_u)val;

	cfg_xbar_fields->dest_stream = cfg_xbar_val.def_v1.dest_stream;
	cfg_xbar_fields->xbar_tid = cfg_xbar_val.def_v1.xbar_tid;
	cfg_xbar_fields->xbar_tuser = cfg_xbar_val.def_v1.xbar_tuser;
	cfg_xbar_fields->l2_segmentation_en = cfg_xbar_val.def_v1.l2_segmentation_en;
}

static void ecpri_dma_reg_parse_endp_cfg_xbar_v2(enum ecpri_dma_hal_reg_name reg,
	void* fields, u32 val)
{
	struct ecpri_dma_ecpri_endp_cfg_xbar_fields* cfg_xbar_fields =
		(struct ecpri_dma_ecpri_endp_cfg_xbar_fields*)fields;
	ecpri_hwio_def_ecpri_endp_cfg_xbar_u cfg_xbar_val =
		(ecpri_hwio_def_ecpri_endp_cfg_xbar_u)val;

	cfg_xbar_fields->dest_stream = cfg_xbar_val.def_v2.dest_stream;
	cfg_xbar_fields->xbar_tid = cfg_xbar_val.def_v2.xbar_tid;
	cfg_xbar_fields->xbar_tuser = cfg_xbar_val.def_v2.xbar_tuser;
	cfg_xbar_fields->loopback_en = cfg_xbar_val.def_v2.loopback_en;
	cfg_xbar_fields->pre_hdr_en = cfg_xbar_val.def_v2.pre_hdr_en;
	cfg_xbar_fields->nfapi_without_offload =
		cfg_xbar_val.def_v2.nfapi_without_offload;
}

static void ecpri_dma_reg_construct_testbus_ctrl_v1(
	enum ecpri_dma_hal_reg_name reg, const void* fields, u32* val)
{
	struct ecpri_dma_ecpri_testbus_ctrl_fields* testbus_ctrl_fields =
		(struct ecpri_dma_ecpri_testbus_ctrl_fields*)fields;
	ecpri_hwio_def_ecpri_dma_testbus_ctrl_u* testbus_ctrl_val =
		(ecpri_hwio_def_ecpri_dma_testbus_ctrl_u*)val;

	testbus_ctrl_val->def_v1.sel = testbus_ctrl_fields->sel;
	testbus_ctrl_val->def_v1.sel_internal = testbus_ctrl_fields->sel_internal;
}

static void ecpri_dma_reg_construct_testbus_ctrl_v2(
	enum ecpri_dma_hal_reg_name reg, const void* fields, u32* val)
{
	struct ecpri_dma_ecpri_testbus_ctrl_fields* testbus_ctrl_fields =
		(struct ecpri_dma_ecpri_testbus_ctrl_fields*)fields;
	ecpri_hwio_def_ecpri_dma_testbus_ctrl_u* testbus_ctrl_val =
		(ecpri_hwio_def_ecpri_dma_testbus_ctrl_u*)val;

	testbus_ctrl_val->def_v2.sel = testbus_ctrl_fields->sel;
	testbus_ctrl_val->def_v2.sel_internal = testbus_ctrl_fields->sel_internal;
}

static void ecpri_dma_reg_parse_testbus_ctrl_v1(
	enum ecpri_dma_hal_reg_name reg, void* fields, u32 val)
{
	struct ecpri_dma_ecpri_testbus_ctrl_fields* testbus_ctrl_fields =
		(struct ecpri_dma_ecpri_testbus_ctrl_fields*)fields;
	ecpri_hwio_def_ecpri_dma_testbus_ctrl_u testbus_ctrl_val =
		(ecpri_hwio_def_ecpri_dma_testbus_ctrl_u)val;

	testbus_ctrl_fields->sel = testbus_ctrl_val.def_v1.sel;
	testbus_ctrl_fields->sel_internal = testbus_ctrl_val.def_v1.sel_internal;
}

static void ecpri_dma_reg_parse_testbus_ctrl_v2(
	enum ecpri_dma_hal_reg_name reg, void* fields, u32 val)
{
	struct ecpri_dma_ecpri_testbus_ctrl_fields* testbus_ctrl_fields =
		(struct ecpri_dma_ecpri_testbus_ctrl_fields*)fields;
	ecpri_hwio_def_ecpri_dma_testbus_ctrl_u testbus_ctrl_val =
		(ecpri_hwio_def_ecpri_dma_testbus_ctrl_u)val;

	testbus_ctrl_fields->sel = testbus_ctrl_val.def_v2.sel;
	testbus_ctrl_fields->sel_internal = testbus_ctrl_val.def_v2.sel_internal;
}

static void ecpri_dma_reg_construct_endp_exception_channel_v1(
	enum ecpri_dma_hal_reg_name reg, const void* fields, u32* val)
{
	struct ecpri_dma_ecpri_endp_exception_channel_fields* exception_ch_fields =
		(struct ecpri_dma_ecpri_endp_exception_channel_fields*)fields;
	ecpri_hwio_def_ecpri_dma_exception_channel_u* exception_ch_val =
		(ecpri_hwio_def_ecpri_dma_exception_channel_u*)val;

	exception_ch_val->def_v1.channel = exception_ch_fields->channel;
	exception_ch_val->def_v1.enable = exception_ch_fields->enable;
}

static void ecpri_dma_reg_construct_endp_exception_channel_v2(
	enum ecpri_dma_hal_reg_name reg, const void* fields, u32* val)
{
	struct ecpri_dma_ecpri_endp_exception_channel_fields* exception_ch_fields =
		(struct ecpri_dma_ecpri_endp_exception_channel_fields*)fields;
	ecpri_hwio_def_ecpri_dma_exception_channel_u* exception_ch_val =
		(ecpri_hwio_def_ecpri_dma_exception_channel_u*)val;

	exception_ch_val->def_v2.channel = exception_ch_fields->channel;
	exception_ch_val->def_v2.gid = exception_ch_fields->gid;
	exception_ch_val->def_v2.enable = exception_ch_fields->enable;
}

static void ecpri_dma_reg_parse_endp_exception_channel_v1(
	enum ecpri_dma_hal_reg_name reg, void* fields, u32 val)
{
	struct ecpri_dma_ecpri_endp_exception_channel_fields* exception_ch_fields =
		(struct ecpri_dma_ecpri_endp_exception_channel_fields*)fields;
	ecpri_hwio_def_ecpri_dma_exception_channel_u exception_ch_val =
		(ecpri_hwio_def_ecpri_dma_exception_channel_u)val;

	exception_ch_fields->channel = exception_ch_val.def_v1.channel;
	exception_ch_fields->enable = exception_ch_val.def_v1.enable;
}

static void ecpri_dma_reg_parse_endp_exception_channel_v2(
	enum ecpri_dma_hal_reg_name reg, void* fields, u32 val)
{
	struct ecpri_dma_ecpri_endp_exception_channel_fields* exception_ch_fields =
		(struct ecpri_dma_ecpri_endp_exception_channel_fields*)fields;
	ecpri_hwio_def_ecpri_dma_exception_channel_u exception_ch_val =
		(ecpri_hwio_def_ecpri_dma_exception_channel_u)val;

	exception_ch_fields->channel = exception_ch_val.def_v2.channel;
	exception_ch_fields->gid = exception_ch_val.def_v2.gid;
	exception_ch_fields->enable = exception_ch_val.def_v2.enable;
}

static void ecpri_dma_reg_construct_ecpri_dpl_trig_ctrl_v1(
	enum ecpri_dma_hal_reg_name reg, const void* fields, u32* val)
{
	struct ecpri_dma_ecpri_dpl_trig_ctrl_fields* trig_ctrl_fields =
		(struct ecpri_dma_ecpri_dpl_trig_ctrl_fields*)fields;
	ecpri_hwio_def_ecpri_dpl_trig_ctrl_n_u* trig_ctrl_val =
		(ecpri_hwio_def_ecpri_dpl_trig_ctrl_n_u*)val;

	trig_ctrl_val->def_v1.b_enable = trig_ctrl_fields->b_enable;
	trig_ctrl_val->def_v1.b_width = trig_ctrl_fields->b_width;
	trig_ctrl_val->def_v1.b_location = trig_ctrl_fields->b_location;
	trig_ctrl_val->def_v1.a_enable = trig_ctrl_fields->a_enable;
	trig_ctrl_val->def_v1.a_width = trig_ctrl_fields->a_width;
	trig_ctrl_val->def_v1.a_location = trig_ctrl_fields->a_location;
	trig_ctrl_val->def_v1.dst_channel = trig_ctrl_fields->dst_channel;
}

static void ecpri_dma_reg_construct_ecpri_dpl_trig_ctrl_v2(
	enum ecpri_dma_hal_reg_name reg, const void* fields, u32* val)
{
	struct ecpri_dma_ecpri_dpl_trig_ctrl_fields* trig_ctrl_fields =
		(struct ecpri_dma_ecpri_dpl_trig_ctrl_fields*)fields;
	ecpri_hwio_def_ecpri_dpl_trig_ctrl_n_u* trig_ctrl_val =
		(ecpri_hwio_def_ecpri_dpl_trig_ctrl_n_u*)val;

	trig_ctrl_val->def_v2.b_enable = trig_ctrl_fields->b_enable;
	trig_ctrl_val->def_v2.b_width = trig_ctrl_fields->b_width;
	trig_ctrl_val->def_v2.b_location = trig_ctrl_fields->b_location;
	trig_ctrl_val->def_v2.a_enable = trig_ctrl_fields->a_enable;
	trig_ctrl_val->def_v2.a_width = trig_ctrl_fields->a_width;
	trig_ctrl_val->def_v2.a_location = trig_ctrl_fields->a_location;
	trig_ctrl_val->def_v2.dst_channel = trig_ctrl_fields->dst_channel;
	trig_ctrl_val->def_v2.dst_gid = trig_ctrl_fields->dst_gid;
}

static void ecpri_dma_reg_parse_ecpri_dpl_trig_ctrl_v1(
	enum ecpri_dma_hal_reg_name reg, void* fields, u32 val)
{
	struct ecpri_dma_ecpri_dpl_trig_ctrl_fields* trig_ctrl_fields =
		(struct ecpri_dma_ecpri_dpl_trig_ctrl_fields*)fields;
	ecpri_hwio_def_ecpri_dpl_trig_ctrl_n_u trig_ctrl_val =
		(ecpri_hwio_def_ecpri_dpl_trig_ctrl_n_u)val;

	trig_ctrl_fields->b_enable = trig_ctrl_val.def_v1.b_enable;
	trig_ctrl_fields->b_width = trig_ctrl_val.def_v1.b_width;
	trig_ctrl_fields->b_location = trig_ctrl_val.def_v1.b_location;
	trig_ctrl_fields->a_enable = trig_ctrl_val.def_v1.a_enable;
	trig_ctrl_fields->a_width = trig_ctrl_val.def_v1.a_width;
	trig_ctrl_fields->a_location = trig_ctrl_val.def_v1.a_location;
	trig_ctrl_fields->dst_channel = trig_ctrl_val.def_v1.dst_channel;
}

static void ecpri_dma_reg_parse_ecpri_dpl_trig_ctrl_v2(
	enum ecpri_dma_hal_reg_name reg, void* fields, u32 val)
{
	struct ecpri_dma_ecpri_dpl_trig_ctrl_fields* trig_ctrl_fields =
		(struct ecpri_dma_ecpri_dpl_trig_ctrl_fields*)fields;
	ecpri_hwio_def_ecpri_dpl_trig_ctrl_n_u trig_ctrl_val =
		(ecpri_hwio_def_ecpri_dpl_trig_ctrl_n_u)val;

	trig_ctrl_fields->b_enable = trig_ctrl_val.def_v2.b_enable;
	trig_ctrl_fields->b_width = trig_ctrl_val.def_v2.b_width;
	trig_ctrl_fields->b_location = trig_ctrl_val.def_v2.b_location;
	trig_ctrl_fields->a_enable = trig_ctrl_val.def_v2.a_enable;
	trig_ctrl_fields->a_width = trig_ctrl_val.def_v2.a_width;
	trig_ctrl_fields->a_location = trig_ctrl_val.def_v2.a_location;
	trig_ctrl_fields->dst_channel = trig_ctrl_val.def_v2.dst_channel;
	trig_ctrl_fields->dst_gid = trig_ctrl_val.def_v2.dst_gid;
}

static void ecpri_dma_reg_construct_ecpri_dpl_cfg_v1(
	enum ecpri_dma_hal_reg_name reg, const void* fields, u32* val)
{
	struct ecpri_dma_ecpri_dpl_cfg_fields* dpl_cfg_fields =
		(struct ecpri_dma_ecpri_dpl_cfg_fields*)fields;
	ecpri_hwio_def_ecpri_dma_dpl_cfg_u* dpl_cfg_val =
		(ecpri_hwio_def_ecpri_dma_dpl_cfg_u*)val;

	dpl_cfg_val->def_v1.dpl_mtu = dpl_cfg_fields->dpl_mtu;
	dpl_cfg_val->def_v1.dpl_select = dpl_cfg_fields->dpl_select;
	dpl_cfg_val->def_v1.dpl_flush_pkt = dpl_cfg_fields->dpl_flush_pkt;
}

static void ecpri_dma_reg_construct_ecpri_dpl_cfg_v2(
	enum ecpri_dma_hal_reg_name reg, const void* fields, u32* val)
{
	struct ecpri_dma_ecpri_dpl_cfg_fields* dpl_cfg_fields =
		(struct ecpri_dma_ecpri_dpl_cfg_fields*)fields;
	ecpri_hwio_def_ecpri_dma_dpl_cfg_u* dpl_cfg_val =
		(ecpri_hwio_def_ecpri_dma_dpl_cfg_u*)val;

	dpl_cfg_val->def_v2.dpl_mtu = dpl_cfg_fields->dpl_mtu;
	dpl_cfg_val->def_v2.dpl_select = dpl_cfg_fields->dpl_select;
	dpl_cfg_val->def_v2.dpl_tre_mirror_en = dpl_cfg_fields->dpl_tre_mirror_en;
	dpl_cfg_val->def_v2.dpl_flush_clr = dpl_cfg_fields->dpl_flush_clr;
	dpl_cfg_val->def_v2.dpl_flush_pkt = dpl_cfg_fields->dpl_flush_pkt;
}

static void ecpri_dma_reg_parse_ecpri_dpl_cfg_v1(
	enum ecpri_dma_hal_reg_name reg, void* fields, u32 val)
{
	struct ecpri_dma_ecpri_dpl_cfg_fields* dpl_cfg_fields =
		(struct ecpri_dma_ecpri_dpl_cfg_fields*)fields;
	ecpri_hwio_def_ecpri_dma_dpl_cfg_u dpl_cfg_val =
		(ecpri_hwio_def_ecpri_dma_dpl_cfg_u)val;

	dpl_cfg_fields->dpl_mtu = dpl_cfg_val.def_v1.dpl_mtu;
	dpl_cfg_fields->dpl_select = dpl_cfg_val.def_v1.dpl_select;
	dpl_cfg_fields->dpl_flush_pkt = dpl_cfg_val.def_v1.dpl_flush_pkt;
}

static void ecpri_dma_reg_parse_ecpri_dpl_cfg_v2(
	enum ecpri_dma_hal_reg_name reg, void* fields, u32 val)
{
	struct ecpri_dma_ecpri_dpl_cfg_fields* dpl_cfg_fields =
		(struct ecpri_dma_ecpri_dpl_cfg_fields*)fields;
	ecpri_hwio_def_ecpri_dma_dpl_cfg_u dpl_cfg_val =
		(ecpri_hwio_def_ecpri_dma_dpl_cfg_u)val;

	dpl_cfg_fields->dpl_mtu = dpl_cfg_val.def_v2.dpl_mtu;
	dpl_cfg_fields->dpl_select = dpl_cfg_val.def_v2.dpl_select;
	dpl_cfg_fields->dpl_tre_mirror_en = dpl_cfg_val.def_v2.dpl_tre_mirror_en;
	dpl_cfg_fields->dpl_flush_clr = dpl_cfg_val.def_v2.dpl_flush_clr;
	dpl_cfg_fields->dpl_flush_pkt = dpl_cfg_val.def_v2.dpl_flush_pkt;
}

static void ecpri_dma_reg_construct_ecpri_tpdm_cfg_v1(
	enum ecpri_dma_hal_reg_name reg, const void* fields, u32* val)
{
	struct ecpri_dma_ecpri_tpdm_cfg_fields* tpdm_cfg_fields =
		(struct ecpri_dma_ecpri_tpdm_cfg_fields*)fields;
	ecpri_hwio_def_ecpri_dma_tpdm_cfg_u* tpdm_cfg_val =
		(ecpri_hwio_def_ecpri_dma_tpdm_cfg_u*)val;

	tpdm_cfg_val->def_v1.record_type = tpdm_cfg_fields->record_type;
	tpdm_cfg_val->def_v1.record_rate = tpdm_cfg_fields->record_rate;
	tpdm_cfg_val->def_v1.record_channel = tpdm_cfg_fields->record_channel;
	tpdm_cfg_val->def_v1.record_gid = tpdm_cfg_fields->record_gid;
	tpdm_cfg_val->def_v1.record_en = tpdm_cfg_fields->record_en;
	tpdm_cfg_val->def_v1.unit_en = tpdm_cfg_fields->unit_en;
}

static void ecpri_dma_reg_construct_ecpri_tpdm_cfg_v2(
	enum ecpri_dma_hal_reg_name reg, const void* fields, u32* val)
{
	struct ecpri_dma_ecpri_tpdm_cfg_fields* tpdm_cfg_fields =
		(struct ecpri_dma_ecpri_tpdm_cfg_fields*)fields;
	ecpri_hwio_def_ecpri_dma_tpdm_cfg_u* tpdm_cfg_val =
		(ecpri_hwio_def_ecpri_dma_tpdm_cfg_u*)val;

	tpdm_cfg_val->def_v2.record_rate = tpdm_cfg_fields->record_rate;
	tpdm_cfg_val->def_v2.record_channel = tpdm_cfg_fields->record_channel;
	tpdm_cfg_val->def_v2.record_gid = tpdm_cfg_fields->record_gid;
	tpdm_cfg_val->def_v2.record_en = tpdm_cfg_fields->record_en;
	tpdm_cfg_val->def_v2.unit_en = tpdm_cfg_fields->unit_en;
}

static void ecpri_dma_reg_parse_ecpri_tpdm_cfg_v1(
	enum ecpri_dma_hal_reg_name reg, void* fields, u32 val)
{
	struct ecpri_dma_ecpri_tpdm_cfg_fields* tpdm_cfg_fields =
		(struct ecpri_dma_ecpri_tpdm_cfg_fields*)fields;
	ecpri_hwio_def_ecpri_dma_tpdm_cfg_u tpdm_cfg_val =
		(ecpri_hwio_def_ecpri_dma_tpdm_cfg_u)val;

	tpdm_cfg_fields->record_type = tpdm_cfg_val.def_v1.record_type;
	tpdm_cfg_fields->record_rate = tpdm_cfg_val.def_v1.record_rate;
	tpdm_cfg_fields->record_channel = tpdm_cfg_val.def_v1.record_channel;
	tpdm_cfg_fields->record_gid = tpdm_cfg_val.def_v1.record_gid;
	tpdm_cfg_fields->record_en = tpdm_cfg_val.def_v1.record_en;
	tpdm_cfg_fields->unit_en = tpdm_cfg_val.def_v1.unit_en;
}

static void ecpri_dma_reg_parse_ecpri_tpdm_cfg_v2(
	enum ecpri_dma_hal_reg_name reg, void* fields, u32 val)
{
	struct ecpri_dma_ecpri_tpdm_cfg_fields* tpdm_cfg_fields =
		(struct ecpri_dma_ecpri_tpdm_cfg_fields*)fields;
	ecpri_hwio_def_ecpri_dma_tpdm_cfg_u tpdm_cfg_val =
		(ecpri_hwio_def_ecpri_dma_tpdm_cfg_u)val;

	tpdm_cfg_fields->record_rate = tpdm_cfg_val.def_v2.record_rate;
	tpdm_cfg_fields->record_channel = tpdm_cfg_val.def_v2.record_channel;
	tpdm_cfg_fields->record_gid = tpdm_cfg_val.def_v2.record_gid;
	tpdm_cfg_fields->record_en = tpdm_cfg_val.def_v2.record_en;
	tpdm_cfg_fields->unit_en = tpdm_cfg_val.def_v2.unit_en;
}


static void ecpri_dma_reg_construct_ecpri_nso_dbg_cntxt_info_1_v1(
	enum ecpri_dma_hal_reg_name reg, const void* fields, u32* val)
{
	struct ecpri_dma_ecpri_nso_dbg_cntxt_info_1_fields* dgb_cntxt_fields =
		(struct ecpri_dma_ecpri_nso_dbg_cntxt_info_1_fields*)fields;
	ecpri_hwio_def_ecpri_nso_dbg_cntxt_n_info_1_u* dgb_cntxt_val =
		(ecpri_hwio_def_ecpri_nso_dbg_cntxt_n_info_1_u*)val;

	dgb_cntxt_val->def_v1.eng_state = dgb_cntxt_fields->eng_state;
	dgb_cntxt_val->def_v1.src_id = dgb_cntxt_fields->src_id;
	dgb_cntxt_val->def_v1.size = dgb_cntxt_fields->size;
	dgb_cntxt_val->def_v1.num_of_sectors = dgb_cntxt_fields->num_of_sectors;
	dgb_cntxt_val->def_v1.last = dgb_cntxt_fields->last;
	dgb_cntxt_val->def_v1.msg_too_long = dgb_cntxt_fields->msg_too_long;
	dgb_cntxt_val->def_v1.jumbo_pkt_en = dgb_cntxt_fields->jumbo_pkt_en;
	dgb_cntxt_val->def_v1.nfapi_hdr_valid = dgb_cntxt_fields->nfapi_hdr_valid;
}

static void ecpri_dma_reg_construct_ecpri_nso_dbg_cntxt_info_1_v2(
	enum ecpri_dma_hal_reg_name reg, const void* fields, u32* val)
{
	struct ecpri_dma_ecpri_nso_dbg_cntxt_info_1_fields* dgb_cntxt_fields =
		(struct ecpri_dma_ecpri_nso_dbg_cntxt_info_1_fields*)fields;
	ecpri_hwio_def_ecpri_nso_dbg_cntxt_n_info_1_u* dgb_cntxt_val =
		(ecpri_hwio_def_ecpri_nso_dbg_cntxt_n_info_1_u*)val;

	dgb_cntxt_val->def_v2.eng_state = dgb_cntxt_fields->eng_state;
	dgb_cntxt_val->def_v2.src_id = dgb_cntxt_fields->src_id;
	dgb_cntxt_val->def_v2.size = dgb_cntxt_fields->size;
	dgb_cntxt_val->def_v2.num_of_sectors = dgb_cntxt_fields->num_of_sectors;
	dgb_cntxt_val->def_v2.last = dgb_cntxt_fields->last;
	dgb_cntxt_val->def_v2.gsi_id = dgb_cntxt_fields->gsi_id;
	dgb_cntxt_val->def_v2.msg_too_long = dgb_cntxt_fields->msg_too_long;
}

static void ecpri_dma_reg_parse_ecpri_nso_dbg_cntxt_info_1_v1(
	enum ecpri_dma_hal_reg_name reg, void* fields, u32 val)
{
	struct ecpri_dma_ecpri_nso_dbg_cntxt_info_1_fields* dgb_cntxt_fields =
		(struct ecpri_dma_ecpri_nso_dbg_cntxt_info_1_fields*)fields;
	ecpri_hwio_def_ecpri_nso_dbg_cntxt_n_info_1_u dgb_cntxt_val =
		(ecpri_hwio_def_ecpri_nso_dbg_cntxt_n_info_1_u)val;

	dgb_cntxt_fields->eng_state = dgb_cntxt_val.def_v1.eng_state;
	dgb_cntxt_fields->src_id = dgb_cntxt_val.def_v1.src_id;
	dgb_cntxt_fields->size = dgb_cntxt_val.def_v1.size;
	dgb_cntxt_fields->num_of_sectors = dgb_cntxt_val.def_v1.num_of_sectors;
	dgb_cntxt_fields->last = dgb_cntxt_val.def_v1.last;
	dgb_cntxt_fields->msg_too_long = dgb_cntxt_val.def_v1.msg_too_long;
	dgb_cntxt_fields->jumbo_pkt_en = dgb_cntxt_val.def_v1.jumbo_pkt_en;
	dgb_cntxt_fields->nfapi_hdr_valid = dgb_cntxt_val.def_v1.nfapi_hdr_valid;
}

static void ecpri_dma_reg_parse_ecpri_nso_dbg_cntxt_info_1_v2(
	enum ecpri_dma_hal_reg_name reg, void* fields, u32 val)
{
	struct ecpri_dma_ecpri_nso_dbg_cntxt_info_1_fields* dgb_cntxt_fields =
		(struct ecpri_dma_ecpri_nso_dbg_cntxt_info_1_fields*)fields;
	ecpri_hwio_def_ecpri_nso_dbg_cntxt_n_info_1_u dgb_cntxt_val =
		(ecpri_hwio_def_ecpri_nso_dbg_cntxt_n_info_1_u)val;

	dgb_cntxt_fields->eng_state = dgb_cntxt_val.def_v2.eng_state;
	dgb_cntxt_fields->src_id = dgb_cntxt_val.def_v2.src_id ;
	dgb_cntxt_fields->size = dgb_cntxt_val.def_v2.size;
	dgb_cntxt_fields->num_of_sectors = dgb_cntxt_val.def_v2.num_of_sectors;
	dgb_cntxt_fields->last = dgb_cntxt_val.def_v2.last;
	dgb_cntxt_fields->gsi_id = dgb_cntxt_val.def_v2.gsi_id;
	dgb_cntxt_fields->msg_too_long = dgb_cntxt_val.def_v2.msg_too_long;
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
 * @m_end - MAXm
 * @max_n - MAXn
 */
struct ecpri_dma_hal_reg_obj {
	void (*construct)(enum ecpri_dma_hal_reg_name reg, const void* fields,
		u32* val);
	void (*parse)(enum ecpri_dma_hal_reg_name reg, void* fields,
		u32 val);
	u32 offset;
	u32 n_ofst;
	int n_start;
	int n_end;
	bool en_print;
	u32 m_ofst;
	enum ecpri_dma_hal_reg_attr attr;
	u32 m_end;
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
	[ECPRI_HW_V1_0][ECPRI_HW_PARAMS_0] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_HW_PARAMS_0_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_HW_PARAMS_0_ATTR},
	[ECPRI_HW_V1_0][ECPRI_HW_PARAMS_2] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_HW_PARAMS_2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_HW_PARAMS_2_ATTR},
	[ECPRI_HW_V1_0][ECPRI_NFAPI_CFG_0] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_CFG_0_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_CFG_0_ATTR},
	[ECPRI_HW_V1_0][ECPRI_NFAPI_CFG_1] = {
		ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_CFG_1_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_CFG_1_ATTR},
	[ECPRI_HW_V1_0][ECPRI_NFAPI_CFG_2] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_CFG_2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_CFG_2_ATTR},
	[ECPRI_HW_V1_0][ECPRI_ENDP_CFG_AGGR] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_CFG_AGGR_n_OFFS(0),
	HWIO_ECPRI_ENDP_CFG_AGGR_n_OFFS(1) -
	HWIO_ECPRI_ENDP_CFG_AGGR_n_OFFS(0), 0,
	HWIO_ECPRI_ENDP_CFG_AGGR_n_MAXn, 0, 0,
	HWIO_ECPRI_ENDP_CFG_AGGR_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_ENDP_NFAPI_REASSEMBLY_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_n_OFFS(0),
	HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_n_OFFS(1) -
	HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_n_OFFS(0), 0,
	HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_n_MAXn, 0, 0,
	HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_OFFS(0),
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_OFFS(1) -
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_OFFS(0), 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_MAXn, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_ATTR},
	[ECPRI_HW_V1_0][ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_OFFS(0),
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_OFFS(1) -
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_OFFS(0), 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_MAXn, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_ATTR},
	[ECPRI_HW_V1_0][ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_OFFS(0),
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_OFFS(1) -
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_OFFS(0), 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_MAXn, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_ATTR},
	[ECPRI_HW_V1_0][ECPRI_ENDP_GSI_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_GSI_CFG_n_OFFS(0),
	HWIO_ECPRI_ENDP_GSI_CFG_n_OFFS(1) -
	HWIO_ECPRI_ENDP_GSI_CFG_n_OFFS(0), 0,
	HWIO_ECPRI_ENDP_GSI_CFG_n_MAXn, 0, 0,
	HWIO_ECPRI_ENDP_GSI_CFG_n_ATTR},
	[ECPRI_HW_V1_0][ECPRI_NFAPI_REASSEMBLY_CFG_0] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_CFG_0_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_CFG_0_ATTR},
	[ECPRI_HW_V1_0][ECPRI_NFAPI_REASSEMBLY_FEC_0] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_ATTR},
	[ECPRI_HW_V1_0][ECPRI_NFAPI_REASSEMBLY_FEC_1] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_1_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_1_ATTR},
	[ECPRI_HW_V1_0][ECPRI_NFAPI_REASSEMBLY_FEC_2] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_2_ATTR},
	[ECPRI_HW_V1_0][ECPRI_NFAPI_REASSEMBLY_FEC_3] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_3_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_3_ATTR },
	[ECPRI_HW_V1_0][ECPRI_NFAPI_REASSEMBLY_FEC_4] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_4_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_4_ATTR },
	[ECPRI_HW_V1_0][ECPRI_NFAPI_REASSEMBLY_FEC_5] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_5_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_5_ATTR },
	[ECPRI_HW_V1_0]
	[ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_PKT_CNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_PKT_CNT_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_PKT_CNT_ATTR },
	[ECPRI_HW_V1_0]
	[ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_LSB] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_LSB_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_LSB_ATTR },
	[ECPRI_HW_V1_0]
	[ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_MSB] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_MSB_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_MSB_ATTR },
	[ECPRI_HW_V1_0]
	[ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_PKT_CNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_PKT_CNT_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_PKT_CNT_ATTR },
	[ECPRI_HW_V1_0]
	[ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_LSB] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_LSB_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_LSB_ATTR },
	[ECPRI_HW_V1_0]
	[ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_MSB] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_MSB_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_MSB_ATTR },
	[ECPRI_HW_V1_0]
	[ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_PKT_CNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_PKT_CNT_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_PKT_CNT_ATTR },
	[ECPRI_HW_V1_0]
	[ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_ATTR
	},
	[ECPRI_HW_V1_0]
	[ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_ATTR
	},
	[ECPRI_HW_V1_0]
	[ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_PKT_CNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_PKT_CNT_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_PKT_CNT_ATTR
	},
	[ECPRI_HW_V1_0]
	[ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB]
	= {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_ATTR
	},
	[ECPRI_HW_V1_0]
	[ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB]
	= {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_ATTR
	},
	[ECPRI_HW_V1_0][ECPRI_NFAPI_REASSEMBLY_STATE] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_STATE_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_STATE_ATTR },
	[ECPRI_HW_V1_0][ECPRI_DMA_STREAM_CTRL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_STREAM_CTRL_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_STREAM_CTRL_ATTR },
	[ECPRI_HW_V1_0][ECPRI_DMA_STREAM_STATUS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_STREAM_STATUS_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_STREAM_STATUS_ATTR },
	[ECPRI_HW_V1_0][ECPRI_DMA_STREAM_ARB] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_STREAM_ARB_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_STREAM_ARB_ATTR },
	[ECPRI_HW_V1_0][ECPRI_DMA_FL_PACKET_ID_CTRL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_FL_PACKET_ID_CTRL_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_FL_PACKET_ID_CTRL_ATTR },
	[ECPRI_HW_V1_0][ECPRI_DMA_FL_PACKET_ID_STATUS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_FL_PACKET_ID_STATUS_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_FL_PACKET_ID_STATUS_ATTR },
	[ECPRI_HW_V1_0][ECPRI_DMA_FL_MEMORY_SECTOR_CTRL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_CTRL_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_CTRL_ATTR },
	[ECPRI_HW_V1_0][ECPRI_DMA_FL_MEMORY_SECTOR_STATUS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_STATUS_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_STATUS_ATTR },
	[ECPRI_HW_V1_0][ECPRI_DMA_XBAR] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_XBAR_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_XBAR_ATTR },
	[ECPRI_HW_V1_0][ECPRI_DMA_DBG_CTRL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_DBG_CTRL_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_DBG_CTRL_ATTR },
	[ECPRI_HW_V1_0][ECPRI_DMA_GBL_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_GBL_CFG_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_GBL_CFG_ATTR },
	[ECPRI_HW_V1_0][ECPRI_DMA_TESTBUS_CTRL] = {
	ecpri_dma_reg_construct_testbus_ctrl_v1,
	ecpri_dma_reg_parse_testbus_ctrl_v1,
	HWIO_ECPRI_DMA_TESTBUS_CTRL_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_TESTBUS_CTRL_ATTR },
	[ECPRI_HW_V1_0][ECPRI_DMA_GP_REG3] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_GP_REG3_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_GP_REG3_ATTR },
	[ECPRI_HW_V1_0][ECPRI_DMA_AOS_FIFO_STAT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_AOS_FIFO_STAT_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_AOS_FIFO_STAT_ATTR },
	[ECPRI_HW_V1_0][ECPRI_DMA_GP_STAT1] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_GP_STAT1_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_GP_STAT1_ATTR },
	[ECPRI_HW_V1_0][ECPRI_DMA_TESTBUS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_TESTBUS_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_TESTBUS_ATTR },
	[ECPRI_HW_V1_0][ECPRI_DMA_GP_STAT3] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_GP_STAT3_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_GP_STAT3_ATTR },
	[ECPRI_HW_V1_0][ECPRI_DMA_IDLE_REG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_IDLE_REG_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_IDLE_REG_ATTR },
	[ECPRI_HW_V1_0][ECPRI_DMA_EXCEPTION_CHANNEL] = {
	ecpri_dma_reg_construct_endp_exception_channel_v1,
	ecpri_dma_reg_parse_endp_exception_channel_v1,
	HWIO_ECPRI_DMA_EXCEPTION_CHANNEL_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_EXCEPTION_CHANNEL_ATTR },
	[ECPRI_HW_V1_0][ECPRI_DMA_PKT_DROP_FULL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_PKT_DROP_FULL_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_PKT_DROP_FULL_ATTR },
	[ECPRI_HW_V1_0][ECPRI_DMA_PKT_DROP_RE_EMPTY] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_PKT_DROP_RE_EMPTY_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_PKT_DROP_RE_EMPTY_ATTR },
	[ECPRI_HW_V1_0][ECPRI_DMA_DPL_CFG] = {
	ecpri_dma_reg_construct_ecpri_dpl_cfg_v1,
	ecpri_dma_reg_parse_ecpri_dpl_cfg_v1,
	HWIO_ECPRI_DMA_DPL_CFG_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_DPL_CFG_ATTR },
	[ECPRI_HW_V1_0][ECPRI_DMA_TPDM_CFG] = {
	ecpri_dma_reg_construct_ecpri_tpdm_cfg_v1,
	ecpri_dma_reg_parse_ecpri_tpdm_cfg_v1,
	HWIO_ECPRI_DMA_TPDM_CFG_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_TPDM_CFG_ATTR },
	[ECPRI_HW_V1_0][ECPRI_NSO_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NSO_CFG_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NSO_CFG_ATTR },
	[ECPRI_HW_V1_0][ECPRI_NSO_JUMBO_PKT_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NSO_JUMBO_PKT_CFG_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NSO_JUMBO_PKT_CFG_ATTR },
	[ECPRI_HW_V1_0][ECPRI_NSO_SHORT_PKT_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NSO_SHORT_PKT_CFG_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NSO_SHORT_PKT_CFG_ATTR },
	[ECPRI_HW_V1_0][ECPRI_NSO_LEN_ERR_STATUS_1] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_ATTR },
	[ECPRI_HW_V1_0][ECPRI_NSO_LEN_ERR_STATUS_2] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NSO_LEN_ERR_STATUS_2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NSO_LEN_ERR_STATUS_2_ATTR },
	[ECPRI_HW_V1_0][ECPRI_NSO_LEN_ERR_STATUS_3] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NSO_LEN_ERR_STATUS_3_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NSO_LEN_ERR_STATUS_3_ATTR },
	[ECPRI_HW_V1_0][ECPRI_NSO_DBG_MISC_INFO] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NSO_DBG_MISC_INFO_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NSO_DBG_MISC_INFO_ATTR },
	[ECPRI_HW_V1_0][ECPRI_NSO_JUMBO_PKT_EN] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NSO_JUMBO_PKT_EN_n_OFFS(0),
	HWIO_ECPRI_NSO_JUMBO_PKT_EN_n_OFFS(1) -
	HWIO_ECPRI_NSO_JUMBO_PKT_EN_n_OFFS(0), 0,
	HWIO_ECPRI_NSO_JUMBO_PKT_EN_n_MAXn, 0, 0,
	HWIO_ECPRI_NSO_JUMBO_PKT_EN_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_NSO_LEN_ERR_STATUS_HDR_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NSO_LEN_ERR_STATUS_HDR_n_OFFS(0),
	HWIO_ECPRI_NSO_LEN_ERR_STATUS_HDR_n_OFFS(1) -
	HWIO_ECPRI_NSO_LEN_ERR_STATUS_HDR_n_OFFS(0), 0,
	HWIO_ECPRI_NSO_LEN_ERR_STATUS_HDR_n_MAXn, 0, 0,
	HWIO_ECPRI_NSO_LEN_ERR_STATUS_HDR_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_NSO_DBG_CNTXT_n_INFO_1] = {
	ecpri_dma_reg_construct_ecpri_nso_dbg_cntxt_info_1_v1,
	ecpri_dma_reg_parse_ecpri_nso_dbg_cntxt_info_1_v1,
	HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_OFFS(0),
	HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_OFFS(1) -
	HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_OFFS(0),
	0, HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_MAXn, 0, 0,
	HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_NSO_DBG_CNTXT_n_INFO_2] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_OFFS(0),
	HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_OFFS(1) -
	HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_OFFS(0),
	0, HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_MAXn, 0, 0,
	HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_IRQ_STTS_EE_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_IRQ_STTS_EE_n_OFFS(0),
	HWIO_ECPRI_IRQ_STTS_EE_n_OFFS(1) -
	HWIO_ECPRI_IRQ_STTS_EE_n_OFFS(0), 0,
	HWIO_ECPRI_IRQ_STTS_EE_n_MAXn, 0, 0,
	HWIO_ECPRI_IRQ_STTS_EE_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_IRQ_EN_EE_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_IRQ_EN_EE_n_OFFS(0),
	HWIO_ECPRI_IRQ_EN_EE_n_OFFS(1) -
	HWIO_ECPRI_IRQ_EN_EE_n_OFFS(0), 0,
	HWIO_ECPRI_IRQ_EN_EE_n_MAXn, 0, 0,
	HWIO_ECPRI_IRQ_EN_EE_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_IRQ_CLR_EE_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_IRQ_CLR_EE_n_OFFS(0),
	HWIO_ECPRI_IRQ_CLR_EE_n_OFFS(1) -
	HWIO_ECPRI_IRQ_CLR_EE_n_OFFS(0), 0,
	HWIO_ECPRI_IRQ_CLR_EE_n_MAXn, 0, 0,
	HWIO_ECPRI_IRQ_CLR_EE_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_ENDP_CFG_DEST] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_CFG_DESTn_OFFS(0),
	HWIO_ECPRI_ENDP_CFG_DESTn_OFFS(1) -
	HWIO_ECPRI_ENDP_CFG_DESTn_OFFS(0), 0,
	HWIO_ECPRI_ENDP_CFG_DESTn_MAXn, 0, 0,
	HWIO_ECPRI_ENDP_CFG_DESTn_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_ENDP_CFG_XBAR] = {
	ecpri_dma_reg_construct_endp_cfg_xbar_v1,
	ecpri_dma_reg_parse_endp_cfg_xbar_v1,
	HWIO_ECPRI_ENDP_CFG_XBARn_OFFS(0),
	HWIO_ECPRI_ENDP_CFG_XBARn_OFFS(1) -
	HWIO_ECPRI_ENDP_CFG_XBARn_OFFS(0), 0,
	HWIO_ECPRI_ENDP_CFG_XBARn_MAXn, 0, 0,
	HWIO_ECPRI_ENDP_CFG_XBARn_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_ENDP_INIT_CTRL_STATUS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_INIT_CTRL_STATUS_n_OFFS(0),
	HWIO_ECPRI_ENDP_INIT_CTRL_STATUS_n_OFFS(1) -
	HWIO_ECPRI_ENDP_INIT_CTRL_STATUS_n_OFFS(0), 0,
	HWIO_ECPRI_ENDP_INIT_CTRL_STATUS_n_MAXn, 0, 0,
	HWIO_ECPRI_ENDP_INIT_CTRL_STATUS_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_ENDP_AXI_ATTR] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_AXI_ATTR_n_OFFS(0),
	HWIO_ECPRI_ENDP_AXI_ATTR_n_OFFS(1) -
	HWIO_ECPRI_ENDP_AXI_ATTR_n_OFFS(0), 0,
	HWIO_ECPRI_ENDP_AXI_ATTR_n_MAXn, 0, 0,
	HWIO_ECPRI_ENDP_AXI_ATTR_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_ENDP_YELLOW_RED_MARKER_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_n_OFFS(0),
	HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_n_OFFS(1) -
	HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_n_OFFS(0), 0,
	HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_n_MAXn, 0, 0,
	HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_ENDP_GSI_CONS_BYTES_TLV] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_GSI_CONS_BYTES_TLV_n_OFFS(0),
	HWIO_ECPRI_ENDP_GSI_CONS_BYTES_TLV_n_OFFS(1) -
	HWIO_ECPRI_ENDP_GSI_CONS_BYTES_TLV_n_OFFS(0), 0,
	HWIO_ECPRI_ENDP_GSI_CONS_BYTES_TLV_n_MAXn, 0, 0,
	HWIO_ECPRI_ENDP_GSI_CONS_BYTES_TLV_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_ENDP_GSI_CONS_BYTES_AOS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_GSI_CONS_BYTES_AOS_n_OFFS(0),
	HWIO_ECPRI_ENDP_GSI_CONS_BYTES_AOS_n_OFFS(1) -
	HWIO_ECPRI_ENDP_GSI_CONS_BYTES_AOS_n_OFFS(0), 0,
	HWIO_ECPRI_ENDP_GSI_CONS_BYTES_AOS_n_MAXn, 0, 0,
	HWIO_ECPRI_ENDP_GSI_CONS_BYTES_AOS_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_ENDP_GSI_IF_FIFO_CFG_TLV] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_GSI_IF_FIFO_CFG_TLV_n_OFFS(0),
	HWIO_ECPRI_ENDP_GSI_IF_FIFO_CFG_TLV_n_OFFS(1) -
	HWIO_ECPRI_ENDP_GSI_IF_FIFO_CFG_TLV_n_OFFS(0), 0,
	HWIO_ECPRI_ENDP_GSI_IF_FIFO_CFG_TLV_n_MAXn, 0, 0,
	HWIO_ECPRI_ENDP_GSI_IF_FIFO_CFG_TLV_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_ENDP_GSI_IF_FIFO_CFG_AOS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_GSI_IF_FIFO_CFG_AOS_n_OFFS(0),
	HWIO_ECPRI_ENDP_GSI_IF_FIFO_CFG_AOS_n_OFFS(1) -
	HWIO_ECPRI_ENDP_GSI_IF_FIFO_CFG_AOS_n_OFFS(0), 0,
	HWIO_ECPRI_ENDP_GSI_IF_FIFO_CFG_AOS_n_MAXn, 0, 0,
	HWIO_ECPRI_ENDP_GSI_IF_FIFO_CFG_AOS_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_ENDP_CFG_VFID] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_CFG_VFID_n_OFFS(0),
	HWIO_ECPRI_ENDP_CFG_VFID_n_OFFS(1) -
	HWIO_ECPRI_ENDP_CFG_VFID_n_OFFS(0), 0,
	HWIO_ECPRI_ENDP_CFG_VFID_n_MAXn, 0, 0,
	HWIO_ECPRI_ENDP_CFG_VFID_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_YELLOW_MARKER_BELOW] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_YELLOW_MARKER_BELOW_n_OFFS(0),
	HWIO_ECPRI_YELLOW_MARKER_BELOW_n_OFFS(1) -
	HWIO_ECPRI_YELLOW_MARKER_BELOW_n_OFFS(0), 0,
	HWIO_ECPRI_YELLOW_MARKER_BELOW_n_MAXn, 0, 0,
	HWIO_ECPRI_YELLOW_MARKER_BELOW_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_YELLOW_MARKER_BELOW_EN] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_n_OFFS(0),
	HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_n_OFFS(1) -
	HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_n_OFFS(0), 0,
	HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_n_MAXn, 0, 0,
	HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_RED_MARKER_BELOW] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_RED_MARKER_BELOW_n_OFFS(0),
	HWIO_ECPRI_RED_MARKER_BELOW_n_OFFS(1) -
	HWIO_ECPRI_RED_MARKER_BELOW_n_OFFS(0), 0,
	HWIO_ECPRI_RED_MARKER_BELOW_n_MAXn, 0, 0,
	HWIO_ECPRI_RED_MARKER_BELOW_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_RED_MARKER_BELOW_EN] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_RED_MARKER_BELOW_EN_n_OFFS(0),
	HWIO_ECPRI_RED_MARKER_BELOW_EN_n_OFFS(1) -
	HWIO_ECPRI_RED_MARKER_BELOW_EN_n_OFFS(0), 0,
	HWIO_ECPRI_RED_MARKER_BELOW_EN_n_MAXn, 0, 0,
	HWIO_ECPRI_RED_MARKER_BELOW_EN_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_YELLOW_MARKER_SHADOW] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_YELLOW_MARKER_SHADOW_n_OFFS(0),
	HWIO_ECPRI_YELLOW_MARKER_SHADOW_n_OFFS(1) -
	HWIO_ECPRI_YELLOW_MARKER_SHADOW_n_OFFS(0), 0,
	HWIO_ECPRI_YELLOW_MARKER_SHADOW_n_MAXn, 0, 0,
	HWIO_ECPRI_YELLOW_MARKER_SHADOW_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_RED_MARKER_SHADOW] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_RED_MARKER_SHADOW_n_OFFS(0),
	HWIO_ECPRI_RED_MARKER_SHADOW_n_OFFS(1) -
	HWIO_ECPRI_RED_MARKER_SHADOW_n_OFFS(0), 0,
	HWIO_ECPRI_RED_MARKER_SHADOW_n_MAXn, 0, 0,
	HWIO_ECPRI_RED_MARKER_SHADOW_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_YELLOW_MARKER_ABOVE] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_YELLOW_MARKER_ABOVE_n_OFFS(0),
	HWIO_ECPRI_YELLOW_MARKER_ABOVE_n_OFFS(1) -
	HWIO_ECPRI_YELLOW_MARKER_ABOVE_n_OFFS(0), 0,
	HWIO_ECPRI_YELLOW_MARKER_ABOVE_n_MAXn, 0, 0,
	HWIO_ECPRI_YELLOW_MARKER_ABOVE_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_YELLOW_MARKER_ABOVE_EN] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_n_OFFS(0),
	HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_n_OFFS(1) -
	HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_n_OFFS(0), 0,
	HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_n_MAXn, 0, 0,
	HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_RED_MARKER_ABOVE] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_RED_MARKER_ABOVE_n_OFFS(0),
	HWIO_ECPRI_RED_MARKER_ABOVE_n_OFFS(1) -
	HWIO_ECPRI_RED_MARKER_ABOVE_n_OFFS(0), 0,
	HWIO_ECPRI_RED_MARKER_ABOVE_n_MAXn, 0, 0,
	HWIO_ECPRI_RED_MARKER_ABOVE_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_RED_MARKER_ABOVE_EN] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_RED_MARKER_ABOVE_EN_n_OFFS(0),
	HWIO_ECPRI_RED_MARKER_ABOVE_EN_n_OFFS(1) -
	HWIO_ECPRI_RED_MARKER_ABOVE_EN_n_OFFS(0), 0,
	HWIO_ECPRI_RED_MARKER_ABOVE_EN_n_MAXn, 0, 0,
	HWIO_ECPRI_RED_MARKER_ABOVE_EN_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_QMB_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_QMB_CFG_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_QMB_CFG_ATTR },
	[ECPRI_HW_V1_0][ECPRI_QMB_0_STATUS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_QMB_0_STATUS_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_QMB_0_STATUS_ATTR },
	[ECPRI_HW_V1_0][ECPRI_QMB_1_STATUS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_QMB_1_STATUS_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_QMB_1_STATUS_ATTR },
	[ECPRI_HW_V1_0][ECPRI_QMB_CFG_PARAM] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_QMB_CFG_PARAM_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_QMB_CFG_PARAM_ATTR },
	[ECPRI_HW_V1_0][ECPRI_QMB0_SNOC_MONITOR_CNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_QMB0_SNOC_MONITOR_CNT_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_QMB0_SNOC_MONITOR_CNT_ATTR },
	[ECPRI_HW_V1_0][ECPRI_QMB1_SNOC_MONITOR_CNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_QMB1_SNOC_MONITOR_CNT_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_QMB1_SNOC_MONITOR_CNT_ATTR },
	[ECPRI_HW_V1_0][ECPRI_GSI_SNOC_MONITOR_CNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_ATTR },
	[ECPRI_HW_V1_0][ECPRI_GSI_TLV_FIFO_STATUS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_GSI_TLV_FIFO_STATUS_n_OFFS(0),
	HWIO_ECPRI_GSI_TLV_FIFO_STATUS_n_OFFS(1) -
	HWIO_ECPRI_GSI_TLV_FIFO_STATUS_n_OFFS(0), 0,
	HWIO_ECPRI_GSI_TLV_FIFO_STATUS_n_MAXn, 0, 0,
	HWIO_ECPRI_GSI_TLV_FIFO_STATUS_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_GSI_AOS_FIFO_STATUS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_GSI_AOS_FIFO_STATUS_n_OFFS(0),
	HWIO_ECPRI_GSI_AOS_FIFO_STATUS_n_OFFS(1) -
	HWIO_ECPRI_GSI_AOS_FIFO_STATUS_n_OFFS(0), 0,
	HWIO_ECPRI_GSI_AOS_FIFO_STATUS_n_MAXn, 0, 0,
	HWIO_ECPRI_GSI_AOS_FIFO_STATUS_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_ENDP_DPL_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_DPL_CFG_n_OFFS(0),
	HWIO_ECPRI_DMA_DPL_CFG_n_OFFS(1) -
	HWIO_ECPRI_DMA_DPL_CFG_n_OFFS(0), 0,
	HWIO_ECPRI_DMA_DPL_CFG_n_MAXn, 0, 0,
	HWIO_ECPRI_DMA_DPL_CFG_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_DPL_TRIG_CTRL_n] = {
	ecpri_dma_reg_construct_ecpri_dpl_trig_ctrl_v1,
	ecpri_dma_reg_parse_ecpri_dpl_trig_ctrl_v1,
	HWIO_ECPRI_DPL_TRIG_CTRL_n_OFFS(0),
	HWIO_ECPRI_DPL_TRIG_CTRL_n_OFFS(1) -
	HWIO_ECPRI_DPL_TRIG_CTRL_n_OFFS(0), 0,
	HWIO_ECPRI_DPL_TRIG_CTRL_n_MAXn, 0, 0,
	HWIO_ECPRI_DPL_TRIG_CTRL_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_DPL_TRIG_A_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DPL_TRIG_A_n_OFFS(0),
	HWIO_ECPRI_DPL_TRIG_A_n_OFFS(1) -
	HWIO_ECPRI_DPL_TRIG_A_n_OFFS(0), 0,
	HWIO_ECPRI_DPL_TRIG_A_n_MAXn, 0, 0,
	HWIO_ECPRI_DPL_TRIG_A_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_DPL_TRIG_B_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DPL_TRIG_B_n_OFFS(0),
	HWIO_ECPRI_DPL_TRIG_B_n_OFFS(1) -
	HWIO_ECPRI_DPL_TRIG_B_n_OFFS(0), 0,
	HWIO_ECPRI_DPL_TRIG_B_n_MAXn, 0, 0,
	HWIO_ECPRI_DPL_TRIG_B_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_GSI_EE_VFID] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_GSI_EE_VFID_n_OFFS(0),
	HWIO_ECPRI_GSI_EE_VFID_n_OFFS(1) -
	HWIO_ECPRI_GSI_EE_VFID_n_OFFS(0), 0,
	HWIO_ECPRI_GSI_EE_VFID_n_MAXn, 0, 0,
	HWIO_ECPRI_GSI_EE_VFID_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_SPARE_REG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_SPARE_REG_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_SPARE_REG_ATTR },
	[ECPRI_HW_V1_0][ECPRI_DST_ACKMNGR_CMDQ_STATUS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_ATTR },
	[ECPRI_HW_V1_0][ECPRI_STATE_GSI_IF] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_STATE_GSI_IF_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_STATE_GSI_IF_ATTR },
	[ECPRI_HW_V1_0][ECPRI_GEN_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_GEN_CFG_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_GEN_CFG_ATTR },
	[ECPRI_HW_V1_0][ECPRI_CLKON_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_CLKON_CFG_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_CLKON_CFG_ATTR },
	[ECPRI_HW_V1_0][ECPRI_AOS_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_AOS_CFG_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_AOS_CFG_ATTR },
	[ECPRI_HW_V1_0][ECPRI_TIMERS_XO_CLK_DIV_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_TIMERS_XO_CLK_DIV_CFG_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_TIMERS_XO_CLK_DIV_CFG_ATTR },
	[ECPRI_HW_V1_0][ECPRI_TIMERS_PULSE_GRAN_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_TIMERS_PULSE_GRAN_CFG_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_TIMERS_PULSE_GRAN_CFG_ATTR },
	[ECPRI_HW_V1_0][ECPRI_QTIME_LSB] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_QTIME_LSB_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_QTIME_LSB_ATTR },
	[ECPRI_HW_V1_0][ECPRI_QTIME_MSB] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_QTIME_MSB_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_QTIME_MSB_ATTR },
	[ECPRI_HW_V1_0][ECPRI_SNOC_FEC] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_SNOC_FEC_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_SNOC_FEC_ATTR },
	[ECPRI_HW_V1_0][ECPRI_SNOC_MONITORING_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_SNOC_MONITORING_CFG_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_SNOC_MONITORING_CFG_ATTR },
	[ECPRI_HW_V1_0][ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY_n_OFFS(0),
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY_n_OFFS(1) -
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY_n_OFFS(0), 0,
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY_n_MAXn, 0, 0,
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_DST_ACKMNGR_CMDQ_COUNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_COUNT_n_OFFS(0),
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_COUNT_n_OFFS(1) -
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_COUNT_n_OFFS(0), 0,
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_COUNT_n_MAXn, 0, 0,
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_COUNT_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_STATE_GSI_TLV_FIFO_EMPTY] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_STATE_GSI_TLV_FIFO_EMPTY_n_OFFS(0),
	HWIO_ECPRI_STATE_GSI_TLV_FIFO_EMPTY_n_OFFS(1) -
	HWIO_ECPRI_STATE_GSI_TLV_FIFO_EMPTY_n_OFFS(0), 0,
	HWIO_ECPRI_STATE_GSI_TLV_FIFO_EMPTY_n_MAXn, 0, 0,
	HWIO_ECPRI_STATE_GSI_TLV_FIFO_EMPTY_n_ATTR, 0},
	[ECPRI_HW_V1_0][ECPRI_STATE_GSI_AOS_FIFO_EMPTY] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_STATE_GSI_AOS_FIFO_EMPTY_n_OFFS(0),
	HWIO_ECPRI_STATE_GSI_AOS_FIFO_EMPTY_n_OFFS(1) -
	HWIO_ECPRI_STATE_GSI_AOS_FIFO_EMPTY_n_OFFS(0), 0,
	HWIO_ECPRI_STATE_GSI_AOS_FIFO_EMPTY_n_MAXn, 0, 0,
	HWIO_ECPRI_STATE_GSI_AOS_FIFO_EMPTY_n_ATTR, 0},
	/* V2 */
	[ECPRI_HW_V2_0][ECPRI_HW_PARAMS_0] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_HW_PARAMS_0_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_HW_PARAMS_0_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_HW_PARAMS_1] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_HW_PARAMS_1_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_HW_PARAMS_1_ATTR },
	[ECPRI_HW_V2_0][ECPRI_HW_PARAMS_2] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_HW_PARAMS_2_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_HW_PARAMS_2_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_RAM_FIFO_CONTENT_LINE_l_WORD_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_RAM_FIFO_CONTENT_LINE_l_WORD_n_OFFS(0, 0),
	HWIO_ECPRI_RAM_FIFO_CONTENT_LINE_l_WORD_n_OFFS(0, 1) -
	HWIO_ECPRI_RAM_FIFO_CONTENT_LINE_l_WORD_n_OFFS(0, 0), 0,
	HWIO_ECPRI_RAM_FIFO_CONTENT_LINE_l_WORD_n_MAXn, 0,
	HWIO_ECPRI_RAM_FIFO_CONTENT_LINE_l_WORD_n_OFFS(1, 0) -
	HWIO_ECPRI_RAM_FIFO_CONTENT_LINE_l_WORD_n_OFFS(0, 0),
	HWIO_ECPRI_RAM_FIFO_CONTENT_LINE_l_WORD_n_ATTR,
	HWIO_ECPRI_RAM_FIFO_CONTENT_LINE_l_WORD_n_MAXl},
	[ECPRI_HW_V2_0][ECPRI_NFAPI_REASSEMBLY_CFG_0] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_CFG_0_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_CFG_0_ATTR },
	[ECPRI_HW_V2_0][ECPRI_NFAPI_REASSEMBLY_FEC_0] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_0_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_NFAPI_REASSEMBLY_FEC_1] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_1_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_1_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_NFAPI_REASSEMBLY_FEC_2] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_2_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_2_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_NFAPI_REASSEMBLY_FEC_3] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_3_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_3_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_NFAPI_REASSEMBLY_FEC_4] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_4_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_4_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_NFAPI_REASSEMBLY_FEC_5] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_5_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_FEC_5_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_PKT_CNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_PKT_CNT_V2_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_PKT_CNT_V2_ATTR },
	[ECPRI_HW_V2_0]
	[ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_LSB] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_LSB_V2_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_LSB_V2_ATTR },
	[ECPRI_HW_V2_0]
	[ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_MSB] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_MSB_V2_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TOTAL_SDU_LENGTH_BYTE_CNT_MSB_V2_ATTR },
	[ECPRI_HW_V2_0]
	[ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_PKT_CNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_PKT_CNT_V2_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_PKT_CNT_V2_ATTR },
	[ECPRI_HW_V2_0]
	[ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_LSB] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_LSB_V2_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_LSB_V2_ATTR },
	[ECPRI_HW_V2_0]
	[ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_MSB] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_MSB_V2_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_BAD_TIMESTAMP_BYTE_CNT_MSB_V2_ATTR },
	[ECPRI_HW_V2_0]
	[ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_PKT_CNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_ATTR },
	[ECPRI_HW_V2_0]
	[ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_ATTR
	},
	[ECPRI_HW_V2_0]
	[ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_PACKET_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_ATTR
	},
	[ECPRI_HW_V2_0]
	[ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_PKT_CNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_PKT_CNT_V2_ATTR
	},
	[ECPRI_HW_V2_0]
	[ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB]
	= {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_LSB_V2_ATTR
	},
	[ECPRI_HW_V2_0]
	[ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB]
	= {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_ERROR_MESSAGE_BYTES_BIGGER_THAN_SDU_LENGTH_BYTE_CNT_MSB_V2_ATTR
	},
	[ECPRI_HW_V2_0][ECPRI_NFAPI_REASSEMBLY_STATE] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_STATE_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_STATE_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_STREAM_CTRL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_STREAM_CTRL_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_STREAM_CTRL_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_STREAM_STATUS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_STREAM_STATUS_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_STREAM_STATUS_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_STREAM_ARB] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_STREAM_ARB_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_STREAM_ARB_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_FL_PACKET_ID_CTRL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_FL_PACKET_ID_CTRL_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_FL_PACKET_ID_CTRL_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_FL_PACKET_ID_STATUS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_FL_PACKET_ID_CTRL_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_FL_PACKET_ID_CTRL_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_FL_MEMORY_SECTOR_CTRL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_CTRL_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_CTRL_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_FL_MEMORY_SECTOR_STATUS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_STATUS_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_FL_MEMORY_SECTOR_STATUS_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_XBAR] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_XBAR_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_XBAR_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_DBG_CTRL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_DBG_CTRL_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_DBG_CTRL_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_GBL_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_GBL_CFG_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_GBL_CFG_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_TESTBUS_CTRL] = {
	ecpri_dma_reg_construct_testbus_ctrl_v2,
	ecpri_dma_reg_parse_testbus_ctrl_v2,
	HWIO_ECPRI_DMA_TESTBUS_CTRL_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_TESTBUS_CTRL_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_GP_REG3] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_GP_REG3_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_GP_REG3_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_AOS_FIFO_STAT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_AOS_FIFO_STAT_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_AOS_FIFO_STAT_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_GP_STAT1] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_GP_STAT1_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_GP_STAT1_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_TESTBUS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	 HWIO_ECPRI_DMA_TESTBUS_V2_OFFS, 0, 0, 0, 0, 0,
	 HWIO_ECPRI_DMA_TESTBUS_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_GP_STAT3] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_GP_STAT3_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_GP_STAT3_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_IDLE_REG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_IDLE_REG_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_IDLE_REG_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_EXCEPTION_CHANNEL] = {
	ecpri_dma_reg_construct_endp_exception_channel_v2,
	ecpri_dma_reg_parse_endp_exception_channel_v2,
	HWIO_ECPRI_DMA_EXCEPTION_CHANNEL_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_EXCEPTION_CHANNEL_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_STATUS_PKT_DROP_FULL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_STATUS_PKT_DROP_FULL_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_STATUS_PKT_DROP_FULL_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_PKT_DROP_RE_EMPTY] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	-1, 0, 0, 0, 0, 0, 0 },
	[ECPRI_HW_V2_0][ECPRI_DMA_DPL_CFG] = {
	ecpri_dma_reg_construct_ecpri_dpl_cfg_v2,
	ecpri_dma_reg_parse_ecpri_dpl_cfg_v2,
	HWIO_ECPRI_DMA_DPL_CFG_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_DPL_CFG_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_TPDM_CFG] = {
	ecpri_dma_reg_construct_ecpri_tpdm_cfg_v2,
	ecpri_dma_reg_parse_ecpri_tpdm_cfg_v2,
	HWIO_ECPRI_DMA_TPDM_CFG_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_TPDM_CFG_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_NSO_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NSO_CFG_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NSO_CFG_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_NSO_JUMBO_PKT_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NSO_JUMBO_PKT_CFG_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NSO_JUMBO_PKT_CFG_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_NSO_SHORT_PKT_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NSO_SHORT_PKT_CFG_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NSO_SHORT_PKT_CFG_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_NSO_LEN_ERR_STATUS_1] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NSO_LEN_ERR_STATUS_1_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_NSO_LEN_ERR_STATUS_2] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NSO_LEN_ERR_STATUS_2_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NSO_LEN_ERR_STATUS_2_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_NSO_LEN_ERR_STATUS_3] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NSO_LEN_ERR_STATUS_3_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NSO_LEN_ERR_STATUS_3_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_NSO_DBG_MISC_INFO] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NSO_DBG_MISC_INFO_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_NSO_DBG_MISC_INFO_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_NSO_JUMBO_PKT_EN] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NSO_JUMBO_PKT_EN_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_NSO_JUMBO_PKT_EN_V2_GSI_m_REG_n_OFFS(0, 1) -
	HWIO_ECPRI_NSO_JUMBO_PKT_EN_V2_GSI_m_REG_n_OFFS(0, 0), 0,
	HWIO_ECPRI_NSO_JUMBO_PKT_EN_V2_GSI_m_REG_n_MAXn, 0,
	HWIO_ECPRI_NSO_JUMBO_PKT_EN_V2_GSI_m_REG_n_OFFS(1, 0) -
	HWIO_ECPRI_NSO_JUMBO_PKT_EN_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_NSO_JUMBO_PKT_EN_V2_GSI_m_REG_n_ATTR,
	HWIO_ECPRI_NSO_JUMBO_PKT_EN_V2_GSI_m_REG_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_NSO_LEN_ERR_STATUS_HDR_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NSO_LEN_ERR_STATUS_HDR_n_V2_OFFS(0),
	HWIO_ECPRI_NSO_LEN_ERR_STATUS_HDR_n_V2_OFFS(1) -
	HWIO_ECPRI_NSO_LEN_ERR_STATUS_HDR_n_V2_OFFS(0), 0,
	HWIO_ECPRI_NSO_LEN_ERR_STATUS_HDR_n_V2_MAXn, 0, 0,
	HWIO_ECPRI_NSO_LEN_ERR_STATUS_HDR_n_V2_ATTR, 0},
	[ECPRI_HW_V2_0][ECPRI_NSO_DBG_CNTXT_n_INFO_1] = {
	ecpri_dma_reg_construct_ecpri_nso_dbg_cntxt_info_1_v2,
	ecpri_dma_reg_parse_ecpri_nso_dbg_cntxt_info_1_v2,
	HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_OFFS(0),
	HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_OFFS(1) -
	HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_OFFS(0),
	0, HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_MAXn, 0, 0,
	HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_1_ATTR, 0},
	[ECPRI_HW_V2_0][ECPRI_NSO_DBG_CNTXT_n_INFO_2] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_OFFS(0),
	HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_OFFS(1) -
	HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_OFFS(0),
	0, HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_MAXn, 0, 0,
	HWIO_ECPRI_NSO_DBG_CNTXT_n_INFO_2_ATTR, 0},
	[ECPRI_HW_V2_0][ECPRI_IRQ_STTS_EE_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_IRQ_STTS_EE_n_V2_OFFS(0),
	HWIO_ECPRI_IRQ_STTS_EE_n_V2_OFFS(1) -
	HWIO_ECPRI_IRQ_STTS_EE_n_V2_OFFS(0), 0,
	HWIO_ECPRI_IRQ_STTS_EE_n_V2_MAXn, 0, 0,
	HWIO_ECPRI_IRQ_STTS_EE_n_V2_ATTR, 0},
	[ECPRI_HW_V2_0][ECPRI_IRQ_EN_EE_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_IRQ_EN_EE_n_V2_OFFS(0),
	HWIO_ECPRI_IRQ_EN_EE_n_V2_OFFS(1) -
	HWIO_ECPRI_IRQ_EN_EE_n_V2_OFFS(0), 0,
	HWIO_ECPRI_IRQ_EN_EE_n_V2_MAXn, 0, 0,
	HWIO_ECPRI_IRQ_EN_EE_n_V2_ATTR, 0},
	[ECPRI_HW_V2_0][ECPRI_IRQ_CLR_EE_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_IRQ_CLR_EE_n_V2_OFFS(0),
	HWIO_ECPRI_IRQ_CLR_EE_n_V2_OFFS(1) -
	HWIO_ECPRI_IRQ_CLR_EE_n_V2_OFFS(0), 0,
	HWIO_ECPRI_IRQ_CLR_EE_n_V2_MAXn, 0, 0,
	HWIO_ECPRI_IRQ_CLR_EE_n_V2_ATTR, 0},
	[ECPRI_HW_V2_0][ECPRI_ENDP_CFG_DEST] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_OFFS(0, 1) -
	HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_OFFS(0, 0), 0,
	HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_MAXn, 0,
	HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_OFFS(1, 0) -
	HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_ATTR,
	HWIO_ECPRI_ENDP_CFG_DEST_V2_GSI_m_CH_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_ENDP_CFG_XBAR] = {
	ecpri_dma_reg_construct_endp_cfg_xbar_v2,
	ecpri_dma_reg_parse_endp_cfg_xbar_v2,
	HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_OFFS(0, 1) -
	HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_OFFS(0, 0), 0,
	HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_MAXn, 0,
	HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_OFFS(1, 0) -
	HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_ATTR,
	HWIO_ECPRI_ENDP_CFG_XBAR_V2_GSI_m_CH_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_ENDP_CFG_AGGR] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_CFG_AGGR_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_CFG_AGGR_V2_GSI_m_CH_n_OFFS(0, 1) -
	HWIO_ECPRI_ENDP_CFG_AGGR_V2_GSI_m_CH_n_OFFS(0, 0), 0,
	HWIO_ECPRI_ENDP_CFG_AGGR_V2_GSI_m_CH_n_MAXn, 0,
	HWIO_ECPRI_ENDP_CFG_AGGR_V2_GSI_m_CH_n_OFFS(1, 0) -
	HWIO_ECPRI_ENDP_CFG_AGGR_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_CFG_AGGR_V2_GSI_m_CH_n_ATTR,
	HWIO_ECPRI_ENDP_CFG_AGGR_V2_GSI_m_CH_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_ENDP_NFAPI_REASSEMBLY_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_V2_GSI_m_CH_n_OFFS(0, 1) -
	HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_V2_GSI_m_CH_n_OFFS(0, 0), 0,
	HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_V2_GSI_m_CH_n_MAXn, 0,
	HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_V2_GSI_m_CH_n_OFFS(1, 0) -
	HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_V2_GSI_m_CH_n_ATTR,
	HWIO_ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_V2_GSI_m_CH_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_V2_OFFS(0),
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_V2_OFFS(1) -
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_V2_OFFS(0), 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_V2_MAXn, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n_V2_ATTR, 0},
	[ECPRI_HW_V2_0][ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_V2_OFFS(0),
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_V2_OFFS(1) -
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_V2_OFFS(0), 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_V2_MAXn, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n_V2_ATTR, 0},
	[ECPRI_HW_V2_0][ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_V2_OFFS(0),
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_V2_OFFS(1) -
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_V2_OFFS(0), 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_V2_MAXn, 0, 0,
	HWIO_ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n_V2_ATTR, 0},
	[ECPRI_HW_V2_0][ECPRI_ENDP_GSI_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_OFFS(0, 1) -
	HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_OFFS(0, 0), 0,
	HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_MAXn, 0,
	HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_OFFS(1, 0) -
	HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_ATTR,
	HWIO_ECPRI_ENDP_GSI_CFG_V2_GSI_m_CH_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_ENDP_INIT_CTRL_STATUS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_INIT_CTRL_STATUS_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_INIT_CTRL_STATUS_V2_GSI_m_CH_n_OFFS(0, 1) -
	HWIO_ECPRI_ENDP_INIT_CTRL_STATUS_V2_GSI_m_CH_n_OFFS(0, 0), 0,
	HWIO_ECPRI_ENDP_INIT_CTRL_STATUS_V2_GSI_m_CH_n_MAXn, 0,
	HWIO_ECPRI_ENDP_INIT_CTRL_STATUS_V2_GSI_m_CH_n_OFFS(1, 0) -
	HWIO_ECPRI_ENDP_INIT_CTRL_STATUS_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_INIT_CTRL_STATUS_V2_GSI_m_CH_n_ATTR,
	HWIO_ECPRI_ENDP_INIT_CTRL_STATUS_V2_GSI_m_CH_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_ENDP_AXI_ATTR] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_OFFS(0, 1) -
	HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_OFFS(0, 0), 0,
	HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_MAXn, 0,
	HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_OFFS(1, 0) -
	HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_ATTR,
	HWIO_ECPRI_ENDP_AXI_ATTR_V2_GSI_m_CH_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_ENDP_YELLOW_RED_MARKER_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_OFFS(0, 1) -
	HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_OFFS(0, 0), 0,
	HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_MAXn, 0,
	HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_OFFS(1, 0) -
	HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_ATTR,
	HWIO_ECPRI_ENDP_YELLOW_RED_MARKER_CFG_V2_GSI_m_CH_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_ENDP_GSI_CONS_BYTES_TLV] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_GSI_CONS_BYTES_AOS_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_GSI_CONS_BYTES_AOS_V2_GSI_m_CH_n_OFFS(0, 1) -
	HWIO_ECPRI_ENDP_GSI_CONS_BYTES_AOS_V2_GSI_m_CH_n_OFFS(0, 0), 0,
	HWIO_ECPRI_ENDP_GSI_CONS_BYTES_AOS_V2_GSI_m_CH_n_MAXn, 0,
	HWIO_ECPRI_ENDP_GSI_CONS_BYTES_AOS_V2_GSI_m_CH_n_OFFS(1, 0) -
	HWIO_ECPRI_ENDP_GSI_CONS_BYTES_AOS_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_GSI_CONS_BYTES_AOS_V2_GSI_m_CH_n_ATTR,
	HWIO_ECPRI_ENDP_GSI_CONS_BYTES_TLV_V2_GSI_m_CH_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_ENDP_GSI_CONS_BYTES_AOS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_GSI_CONS_BYTES_TLV_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_GSI_CONS_BYTES_TLV_V2_GSI_m_CH_n_OFFS(0, 1) -
	HWIO_ECPRI_ENDP_GSI_CONS_BYTES_TLV_V2_GSI_m_CH_n_OFFS(0, 0), 0,
	HWIO_ECPRI_ENDP_GSI_CONS_BYTES_TLV_V2_GSI_m_CH_n_MAXn, 0,
	HWIO_ECPRI_ENDP_GSI_CONS_BYTES_TLV_V2_GSI_m_CH_n_OFFS(1, 0) -
	HWIO_ECPRI_ENDP_GSI_CONS_BYTES_TLV_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_GSI_CONS_BYTES_TLV_V2_GSI_m_CH_n_ATTR,
	HWIO_ECPRI_ENDP_GSI_CONS_BYTES_AOS_V2_GSI_m_CH_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_ENDP_GSI_IF_FIFO_CFG_TLV] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_OFFS(0, 1) -
	HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_OFFS(0, 0), 0,
	HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_MAXn, 0,
	HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_OFFS(1, 0) -
	HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_ATTR,
	HWIO_ECPRI_ENDP_CFG_TLV_FIFO_V2_GSI_m_CH_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_ENDP_GSI_IF_FIFO_CFG_AOS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_OFFS(0, 1) -
	HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_OFFS(0, 0), 0,
	HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_MAXn, 0,
	HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_OFFS(1, 0) -
	HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_ATTR,
	HWIO_ECPRI_ENDP_CFG_AOS_FIFO_V2_GSI_m_CH_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_ENDP_CFG_VFID] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_OFFS(0, 1) -
	HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_OFFS(0, 0), 0,
	HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_MAXn, 0,
	HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_OFFS(1, 0) -
	HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_ATTR,
	HWIO_ECPRI_ENDP_CFG_VFID_V2_GSI_m_CH_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_YELLOW_MARKER_BELOW] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_YELLOW_MARKER_BELOW_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_YELLOW_MARKER_BELOW_V2_GSI_m_REG_n_OFFS(0, 1) -
	HWIO_ECPRI_YELLOW_MARKER_BELOW_V2_GSI_m_REG_n_OFFS(0, 0), 0,
	HWIO_ECPRI_YELLOW_MARKER_BELOW_V2_GSI_m_REG_n_MAXn, 0,
	HWIO_ECPRI_YELLOW_MARKER_BELOW_V2_GSI_m_REG_n_OFFS(1, 0) -
	HWIO_ECPRI_YELLOW_MARKER_BELOW_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_YELLOW_MARKER_BELOW_V2_GSI_m_REG_n_ATTR },
	[ECPRI_HW_V2_0][ECPRI_YELLOW_MARKER_BELOW_EN] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_V2_GSI_m_REG_n_OFFS(0, 1) -
	HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_V2_GSI_m_REG_n_OFFS(0, 0), 0,
	HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_V2_GSI_m_REG_n_MAXn, 0,
	HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_V2_GSI_m_REG_n_OFFS(1, 0) -
	HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_V2_GSI_m_REG_n_ATTR,
	HWIO_ECPRI_YELLOW_MARKER_BELOW_EN_V2_GSI_m_REG_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_RED_MARKER_BELOW] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_RED_MARKER_BELOW_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_RED_MARKER_BELOW_V2_GSI_m_REG_n_OFFS(0, 1) -
	HWIO_ECPRI_RED_MARKER_BELOW_V2_GSI_m_REG_n_OFFS(0, 0), 0,
	HWIO_ECPRI_RED_MARKER_BELOW_V2_GSI_m_REG_n_MAXn, 0,
	HWIO_ECPRI_RED_MARKER_BELOW_V2_GSI_m_REG_n_OFFS(1, 0) -
	HWIO_ECPRI_RED_MARKER_BELOW_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_RED_MARKER_BELOW_V2_GSI_m_REG_n_ATTR,
	HWIO_ECPRI_RED_MARKER_BELOW_V2_GSI_m_REG_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_RED_MARKER_BELOW_EN] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_RED_MARKER_BELOW_EN_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_RED_MARKER_BELOW_EN_V2_GSI_m_REG_n_OFFS(0, 1) -
	HWIO_ECPRI_RED_MARKER_BELOW_EN_V2_GSI_m_REG_n_OFFS(0, 0), 0,
	HWIO_ECPRI_RED_MARKER_BELOW_EN_V2_GSI_m_REG_n_MAXn, 0,
	HWIO_ECPRI_RED_MARKER_BELOW_EN_V2_GSI_m_REG_n_OFFS(1, 0) -
	HWIO_ECPRI_RED_MARKER_BELOW_EN_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_RED_MARKER_BELOW_EN_V2_GSI_m_REG_n_ATTR,
	HWIO_ECPRI_RED_MARKER_BELOW_EN_V2_GSI_m_REG_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_YELLOW_MARKER_SHADOW] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_YELLOW_MARKER_SHADOW_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_YELLOW_MARKER_SHADOW_V2_GSI_m_REG_n_OFFS(0, 1) -
	HWIO_ECPRI_YELLOW_MARKER_SHADOW_V2_GSI_m_REG_n_OFFS(0, 0), 0,
	HWIO_ECPRI_YELLOW_MARKER_SHADOW_V2_GSI_m_REG_n_MAXn, 0,
	HWIO_ECPRI_YELLOW_MARKER_SHADOW_V2_GSI_m_REG_n_OFFS(1, 0) -
	HWIO_ECPRI_YELLOW_MARKER_SHADOW_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_YELLOW_MARKER_SHADOW_V2_GSI_m_REG_n_ATTR,
	HWIO_ECPRI_YELLOW_MARKER_SHADOW_V2_GSI_m_REG_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_RED_MARKER_SHADOW] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_RED_MARKER_SHADOW_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_RED_MARKER_SHADOW_V2_GSI_m_REG_n_OFFS(0, 1) -
	HWIO_ECPRI_RED_MARKER_SHADOW_V2_GSI_m_REG_n_OFFS(0, 0), 0,
	HWIO_ECPRI_RED_MARKER_SHADOW_V2_GSI_m_REG_n_MAXn, 0,
	HWIO_ECPRI_RED_MARKER_SHADOW_V2_GSI_m_REG_n_OFFS(1, 0) -
	HWIO_ECPRI_RED_MARKER_SHADOW_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_RED_MARKER_SHADOW_V2_GSI_m_REG_n_ATTR,
	HWIO_ECPRI_RED_MARKER_SHADOW_V2_GSI_m_REG_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_YELLOW_MARKER_ABOVE] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_YELLOW_MARKER_ABOVE_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_YELLOW_MARKER_ABOVE_V2_GSI_m_REG_n_OFFS(0, 1) -
	HWIO_ECPRI_YELLOW_MARKER_ABOVE_V2_GSI_m_REG_n_OFFS(0, 0), 0,
	HWIO_ECPRI_YELLOW_MARKER_ABOVE_V2_GSI_m_REG_n_MAXn, 0,
	HWIO_ECPRI_YELLOW_MARKER_ABOVE_V2_GSI_m_REG_n_OFFS(1, 0) -
	HWIO_ECPRI_YELLOW_MARKER_ABOVE_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_YELLOW_MARKER_ABOVE_V2_GSI_m_REG_n_ATTR,
	HWIO_ECPRI_YELLOW_MARKER_ABOVE_V2_GSI_m_REG_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_YELLOW_MARKER_ABOVE_EN] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_V2_GSI_m_REG_n_OFFS(0, 1) -
	HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_V2_GSI_m_REG_n_OFFS(0, 0), 0,
	HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_V2_GSI_m_REG_n_MAXn, 0,
	HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_V2_GSI_m_REG_n_OFFS(1, 0) -
	HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_V2_GSI_m_REG_n_ATTR,
	HWIO_ECPRI_YELLOW_MARKER_ABOVE_EN_V2_GSI_m_REG_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_RED_MARKER_ABOVE] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_RED_MARKER_ABOVE_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_RED_MARKER_ABOVE_V2_GSI_m_REG_n_OFFS(0, 1) -
	HWIO_ECPRI_RED_MARKER_ABOVE_V2_GSI_m_REG_n_OFFS(0, 0), 0,
	HWIO_ECPRI_RED_MARKER_ABOVE_V2_GSI_m_REG_n_MAXn, 0,
	HWIO_ECPRI_RED_MARKER_ABOVE_V2_GSI_m_REG_n_OFFS(1, 0) -
	HWIO_ECPRI_RED_MARKER_ABOVE_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_RED_MARKER_ABOVE_V2_GSI_m_REG_n_ATTR,
	HWIO_ECPRI_RED_MARKER_ABOVE_V2_GSI_m_REG_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_RED_MARKER_ABOVE_EN] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_RED_MARKER_ABOVE_EN_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_RED_MARKER_ABOVE_EN_V2_GSI_m_REG_n_OFFS(0, 1) -
	HWIO_ECPRI_RED_MARKER_ABOVE_EN_V2_GSI_m_REG_n_OFFS(0, 0), 0,
	HWIO_ECPRI_RED_MARKER_ABOVE_EN_V2_GSI_m_REG_n_MAXn, 0,
	HWIO_ECPRI_RED_MARKER_ABOVE_EN_V2_GSI_m_REG_n_OFFS(1, 0) -
	HWIO_ECPRI_RED_MARKER_ABOVE_EN_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_RED_MARKER_ABOVE_EN_V2_GSI_m_REG_n_ATTR,
	HWIO_ECPRI_RED_MARKER_ABOVE_EN_V2_GSI_m_REG_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_QMB_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_QMB_CFG_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_QMB_CFG_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_QMB_0_STATUS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_QMB_0_STATUS_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_QMB_0_STATUS_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_QMB_1_STATUS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_QMB_1_STATUS_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_QMB_1_STATUS_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_QMB_CFG_PARAM] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_QMB_CFG_PARAM_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_QMB_CFG_PARAM_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_QMB0_SNOC_MONITOR_CNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_QMB0_SNOC_MONITOR_CNT_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_QMB0_SNOC_MONITOR_CNT_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_QMB1_SNOC_MONITOR_CNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_QMB1_SNOC_MONITOR_CNT_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_QMB1_SNOC_MONITOR_CNT_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_GSI_SNOC_MONITOR_CNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_GSI_SNOC_MONITOR_CNT_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_GSI_TLV_FIFO_STATUS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_OFFS(0, 1) -
	HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_OFFS(0, 0), 0,
	HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_MAXn, 0,
	HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_OFFS(1, 0) -
	HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_ATTR,
	HWIO_ECPRI_GSI_TLV_FIFO_STATUS_V2_GSI_m_CH_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_GSI_AOS_FIFO_STATUS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_OFFS(0, 1) -
	HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_OFFS(0, 0), 0,
	HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_MAXn, 0,
	HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_OFFS(1, 0) -
	HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_ATTR,
	HWIO_ECPRI_GSI_AOS_FIFO_STATUS_V2_GSI_m_CH_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_ENDP_DPL_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_OFFS(0, 1) -
	HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_OFFS(0, 0), 0,
	HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_MAXn, 0,
	HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_OFFS(1, 0) -
	HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_ATTR,
	HWIO_ECPRI_ENDP_DPL_CFG_V2_GSI_m_CH_n_MAXm },
	[ECPRI_HW_V2_0][ECPRI_DPL_TRIG_CTRL_n] = {
	ecpri_dma_reg_construct_ecpri_dpl_trig_ctrl_v2,
	ecpri_dma_reg_parse_ecpri_dpl_trig_ctrl_v2,
	HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_OFFS(0),
	HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_OFFS(1) -
	HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_OFFS(0), 0,
	HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_MAXn, 0, 0,
	HWIO_ECPRI_DPL_TRIG_CTRL_n_V2_ATTR, 0},
	[ECPRI_HW_V2_0][ECPRI_DPL_TRIG_A_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DPL_TRIG_A_n_V2_OFFS(0),
	HWIO_ECPRI_DPL_TRIG_A_n_V2_OFFS(1) -
	HWIO_ECPRI_DPL_TRIG_A_n_V2_OFFS(0), 0,
	HWIO_ECPRI_DPL_TRIG_A_n_V2_MAXn, 0, 0,
	HWIO_ECPRI_DPL_TRIG_A_n_V2_ATTR, 0},
	[ECPRI_HW_V2_0][ECPRI_DPL_TRIG_B_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DPL_TRIG_B_n_V2_OFFS(0),
	HWIO_ECPRI_DPL_TRIG_B_n_V2_OFFS(1) -
	HWIO_ECPRI_DPL_TRIG_B_n_V2_OFFS(0), 0,
	HWIO_ECPRI_DPL_TRIG_B_n_V2_MAXn, 0, 0,
	HWIO_ECPRI_DPL_TRIG_B_n_V2_ATTR, 0},
	[ECPRI_HW_V2_0][ECPRI_GSI_EE_VFID] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_OFFS(0, 0),
	HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_OFFS(0, 1) -
	HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_OFFS(0, 0), 0,
	HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_MAXn, 0,
	HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_OFFS(1, 0) -
	HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_OFFS(0, 0),
	HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_ATTR,
	HWIO_ECPRI_GSI_EE_VFID_GSI_m_EE_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_SPARE_REG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_SPARE_REG_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_SPARE_REG_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DST_ACKMNGR_CMDQ_STATUS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_V2_GSI_m_OFFS(0),
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_V2_GSI_m_OFFS(1) -
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_V2_GSI_m_OFFS(0), 0,
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_V2_GSI_m_MAXm, 0, 0,
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_V2_GSI_m_ATTR, 0},
	[ECPRI_HW_V2_0][ECPRI_STATE_GSI_IF] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_STATE_GSI_IF_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_STATE_GSI_IF_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_GEN_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_GEN_CFG_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_GEN_CFG_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_CLKON_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_CLKON_CFG_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_CLKON_CFG_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_AOS_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_AOS_CFG_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_AOS_CFG_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_TIMERS_XO_CLK_DIV_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_TIMERS_XO_CLK_DIV_CFG_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_TIMERS_XO_CLK_DIV_CFG_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_TIMERS_PULSE_GRAN_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_TIMERS_PULSE_GRAN_CFG_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_TIMERS_PULSE_GRAN_CFG_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_QTIME_LSB] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_QTIME_LSB_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_QTIME_LSB_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_QTIME_MSB] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_QTIME_MSB_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_QTIME_MSB_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_SNOC_FEC] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_SNOC_FEC_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_SNOC_FEC_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_SNOC_MONITORING_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_SNOC_MONITORING_CFG_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_SNOC_MONITORING_CFG_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_OFFS(0, 1) -
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_OFFS(0, 0), 0,
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_MAXn, 0,
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_OFFS(1, 0) -
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_ATTR,
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_STATUS_EMPTY_V2_GSI_m_REG_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_DST_ACKMNGR_CMDQ_COUNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_OFFS(0, 1) -
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_OFFS(0, 0), 0,
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_MAXn, 0,
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_OFFS(1, 0) -
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_ATTR,
	HWIO_ECPRI_DST_ACKMNGR_CMDQ_COUNT_V2_GSI_m_CH_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_STATE_GSI_TLV_FIFO_EMPTY] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_STATE_GSI_TLV_FIFO_EMPTY_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_STATE_GSI_TLV_FIFO_EMPTY_V2_GSI_m_REG_n_OFFS(0, 1) -
	HWIO_ECPRI_STATE_GSI_TLV_FIFO_EMPTY_V2_GSI_m_REG_n_OFFS(0, 0), 0,
	HWIO_ECPRI_STATE_GSI_TLV_FIFO_EMPTY_V2_GSI_m_REG_n_MAXn, 0,
	HWIO_ECPRI_STATE_GSI_TLV_FIFO_EMPTY_V2_GSI_m_REG_n_OFFS(1, 0) -
	HWIO_ECPRI_STATE_GSI_TLV_FIFO_EMPTY_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_STATE_GSI_TLV_FIFO_EMPTY_V2_GSI_m_REG_n_ATTR,
	HWIO_ECPRI_STATE_GSI_TLV_FIFO_EMPTY_V2_GSI_m_REG_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_STATE_GSI_AOS_FIFO_EMPTY] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_STATE_GSI_AOS_FIFO_EMPTY_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_STATE_GSI_AOS_FIFO_EMPTY_V2_GSI_m_REG_n_OFFS(0, 1) -
	HWIO_ECPRI_STATE_GSI_AOS_FIFO_EMPTY_V2_GSI_m_REG_n_OFFS(0, 0), 0,
	HWIO_ECPRI_STATE_GSI_AOS_FIFO_EMPTY_V2_GSI_m_REG_n_MAXn, 0,
	HWIO_ECPRI_STATE_GSI_AOS_FIFO_EMPTY_V2_GSI_m_REG_n_OFFS(1, 0) -
	HWIO_ECPRI_STATE_GSI_AOS_FIFO_EMPTY_V2_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_STATE_GSI_AOS_FIFO_EMPTY_V2_GSI_m_REG_n_ATTR,
	HWIO_ECPRI_STATE_GSI_AOS_FIFO_EMPTY_V2_GSI_m_REG_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_DMA_AHB2RAM_FIFOS_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_AHB2RAM_FIFOS_CFG_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_AHB2RAM_FIFOS_CFG_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_SNIFFER_CTRL2] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_SNIFFER_CTRL2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_SNIFFER_CTRL2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_SNIFFER_CTRL1] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_SNIFFER_CTRL1_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_SNIFFER_CTRL1_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_SNIFFER_STAT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_SNIFFER_STAT_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_SNIFFER_STAT_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_LTE_DEBUG_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_LTE_DEBUG_CFG_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_LTE_DEBUG_CFG_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_LTE_WATERMARKS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_LTE_WATERMARKS_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_LTE_WATERMARKS_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_STATUS_XBAR_FH_PORT_RX] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_STATUS_XBAR_FH_PORT_RX_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_STATUS_XBAR_FH_PORT_RX_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_STATUS_XBAR_FH_PORT_TX] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_STATUS_XBAR_FH_PORT_TX_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_STATUS_XBAR_FH_PORT_TX_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_STATUS_XBAR_C2C_PORT_RX] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_STATUS_XBAR_C2C_PORT_RX_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_STATUS_XBAR_C2C_PORT_RX_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_STATUS_XBAR_C2C_PORT_TX] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_STATUS_XBAR_C2C_PORT_TX_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_STATUS_XBAR_C2C_PORT_TX_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_INTERFACE_DDH_DF] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_INTERFACE_DDH_DF_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_INTERFACE_DDH_DF_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_INTERFACE_DF_C2C] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_INTERFACE_DF_C2C_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_INTERFACE_DF_C2C_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_INTERFACE_DF_NSO] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_INTERFACE_DF_NSO_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_INTERFACE_DF_NSO_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_INTERFACE_DF_FH] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_INTERFACE_DF_FH_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_INTERFACE_DF_FH_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_INTERFACE_DF_TXM] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_INTERFACE_DF_TXM_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_INTERFACE_DF_TXM_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_INTERFACE_DDH_TXM] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_INTERFACE_DDH_TXM_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_INTERFACE_DDH_TXM_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_STATUS_GSI0_A] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_STATUS_GSI0_A_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_STATUS_GSI0_A_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_STATUS_GSI0_B] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_STATUS_GSI0_B_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_STATUS_GSI0_B_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_STATUS_GSI1_A] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_STATUS_GSI1_A_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_STATUS_GSI1_A_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_STATUS_GSI1_B] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_STATUS_GSI1_B_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_STATUS_GSI1_B_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_STATUS_GSI2_A] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_STATUS_GSI2_A_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_STATUS_GSI2_A_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_STATUS_GSI2_B] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_STATUS_GSI2_B_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_STATUS_GSI2_B_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_XBAR_RX_PORT_DPL_STATUS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA_XBAR_RX_PORT_DPL_STATUS_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA_XBAR_RX_PORT_DPL_STATUS_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_STATUS_XBAR_RX_PORT_m] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_STATUS_XBAR_RX_PORT_m_OFFS(0),
	HWIO_ECPRI_STATUS_XBAR_RX_PORT_m_OFFS(1) -
	HWIO_ECPRI_STATUS_XBAR_RX_PORT_m_OFFS(0), 0,
	HWIO_ECPRI_DMA_STATUS_XBAR_RX_PORT_m_V2_MAXn, 0, 0,
	HWIO_ECPRI_STATUS_XBAR_RX_PORT_m_ATTR, 0},
	[ECPRI_HW_V2_0][ECPRI_DMA_STATUS_XBAR_RX_DROP] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_STATUS_XBAR_RX_DROP_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_STATUS_XBAR_RX_DROP_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_ENDP_LTE_CFG_GSI_m_CH_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_ENDP_LTE_CFG_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_LTE_CFG_GSI_m_CH_n_OFFS(0, 1) -
	HWIO_ECPRI_ENDP_LTE_CFG_GSI_m_CH_n_OFFS(0, 0), 0,
	HWIO_ECPRI_ENDP_LTE_CFG_GSI_m_CH_n_MAXn, 0,
	HWIO_ECPRI_ENDP_LTE_CFG_GSI_m_CH_n_OFFS(1, 0) -
	HWIO_ECPRI_ENDP_LTE_CFG_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_ENDP_LTE_CFG_GSI_m_CH_n_ATTR,
	HWIO_ECPRI_ENDP_LTE_CFG_GSI_m_CH_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_DMA_SDH_PREFETCH_LSB_GSI_m_CH_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_SDH_PREFETCH_LSB_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_SDH_PREFETCH_LSB_GSI_m_CH_n_OFFS(0, 1) -
	HWIO_ECPRI_SDH_PREFETCH_LSB_GSI_m_CH_n_OFFS(0, 0), 0,
	HWIO_ECPRI_SDH_PREFETCH_LSB_GSI_m_CH_n_MAXn, 0,
	HWIO_ECPRI_SDH_PREFETCH_LSB_GSI_m_CH_n_OFFS(1, 0) -
	HWIO_ECPRI_SDH_PREFETCH_LSB_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_SDH_PREFETCH_LSB_GSI_m_CH_n_ATTR,
	HWIO_ECPRI_SDH_PREFETCH_LSB_GSI_m_CH_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_DMA_SDH_PREFETCH_MSB_GSI_m_CH_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_OFFS(0, 1) -
	HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_OFFS(0, 0), 0,
	HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_MAXn, 0,
	HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_OFFS(1, 0) -
	HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_OFFS(0, 0),
	HWIO_ECPRI_SDH_PREFETCH_MSB_GSI_m_CH_n_ATTR,
	HWIO_ECPRI_SDH_PREFETCH_LSB_GSI_m_CH_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_DMA_STATUS_LTE_PKT_DROP_FULL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_STATUS_LTE_PKT_DROP_FULL_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_STATUS_LTE_PKT_DROP_FULL_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_RATE_LIMITER] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_RATE_LIMITER_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_RATE_LIMITER_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_DPL_MONITOR_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DPL_MONITOR_CFG_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DPL_MONITOR_CFG_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_DPL_MONITOR_CNT_0] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DPL_MONITOR_CNT_0_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DPL_MONITOR_CNT_0_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_DPL_MONITOR_CNT_1] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DPL_MONITOR_CNT_1_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DPL_MONITOR_CNT_1_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_REDIRECT_CHANNEL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_REDIRECT_CHANNEL_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_REDIRECT_CHANNEL_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_STATUS_DST_DROP_PKT_CLEAR] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_STATUS_DST_DROP_PKT_CLEAR_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_STATUS_DST_DROP_PKT_CLEAR_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_STATUS_DST_DROP_PKT_GSI_m_REG_n] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_STATUS_DST_DROP_PKT_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_STATUS_DST_DROP_PKT_GSI_m_REG_n_OFFS(0, 1) -
	HWIO_ECPRI_STATUS_DST_DROP_PKT_GSI_m_REG_n_OFFS(0, 0), 0,
	HWIO_ECPRI_DMA_STATUS_DST_DROP_PKT_GSI_m_REG_n_V2_GSI_m_REG_n_MAXn, 0,
	HWIO_ECPRI_STATUS_DST_DROP_PKT_GSI_m_REG_n_OFFS(1, 0) -
	HWIO_ECPRI_STATUS_DST_DROP_PKT_GSI_m_REG_n_OFFS(0, 0),
	HWIO_ECPRI_STATUS_DST_DROP_PKT_GSI_m_REG_n_ATTR,
	HWIO_ECPRI_SDH_PREFETCH_LSB_GSI_m_CH_n_MAXm},
	[ECPRI_HW_V2_0][ECPRI_DMA_UNIT_CLK_ENABLE] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_UNIT_CLK_ENABLE_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_UNIT_CLK_ENABLE_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_LTE_CFG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_LTE_CFG_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_LTE_CFG_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_STATUS_PKT_DROP_TLV_FIFO_EMPTY] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_STATUS_PKT_DROP_TLV_FIFO_EMPTY_V2_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_STATUS_PKT_DROP_TLV_FIFO_EMPTY_V2_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_STATUS_LTE_PKT_DROP_TLV_FIFO_EMPTY] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_STATUS_LTE_PKT_DROP_TLV_FIFO_EMPTY_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_STATUS_LTE_PKT_DROP_TLV_FIFO_EMPTY_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA_LTE_LATENCY_BUFFER_WORD] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_LTE_LATENCY_BUFFER_WORD_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_LTE_LATENCY_BUFFER_WORD_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CNTRL_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_THROTTLE_0_CGC_CNTRL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CGC_CNTRL_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CGC_CNTRL_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_THROTTLE_0_RESET_CNTRL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_RESET_CNTRL_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_RESET_CNTRL_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_PERIOD] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_PERIOD_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_PERIOD_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_COUNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_COUNT_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_GRANT_COUNT_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_00] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_00_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_00_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_01] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_01_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_01_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_02] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_02_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_02_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_03] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_03_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_THRESHOLD_03_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_CNTL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_CNTL_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_CNTL_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_READBACK] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_READBACK_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_DEBUG_READBACK_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_THROTTLE_0_SPARE_REGS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_STATUS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_STATUS_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_STATUS_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_CLEAR] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_CLEAR_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_CLEAR_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_INTERRUPT_ENABLE_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_CORE_CLOCKON_CONTROL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON_SW_RESET] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_SW_RESET_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_SW_RESET_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON_CGC_CNTRL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CGC_CNTRL_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CGC_CNTRL_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ENABLE_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON_CLEAR] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CLEAR_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_CLEAR_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON_BYTE_COUNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BYTE_COUNT_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BYTE_COUNT_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON_THRESHOLD] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_THRESHOLD_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_THRESHOLD_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MASK] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MASK_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MASK_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MATCH] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MATCH_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_MID_MATCH_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ENABLE] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ENABLE_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ENABLE_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON2_CLEAR] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_CLEAR_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_CLEAR_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_BYTE_COUNT_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONE_COUNT_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_OFFS(0),
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_OFFS(1) -
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_OFFS(0), 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_MAXn, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_ATTR, 0},
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MASK] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MASK_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MASK_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MATCH] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MATCH_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_PID_MATCH_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MASK] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MASK_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MASK_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MATCH] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MASK_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_BID_MASK_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_PERIOD] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_PERIOD_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_PERIOD_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON_ACCEPT_COUNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ACCEPT_COUNT_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_ACCEPT_COUNT_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNT_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_REJECT_COUNT_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON_IDLE_COUNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_IDLE_COUNT_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_IDLE_COUNT_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON_INTR_TARGET] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_INTR_TARGET_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_INTR_TARGET_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_CNTL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_CNTL_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_CNTL_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_READBACK] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_CNTL_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA1_THROTTLE_BWMON_BWMON_DEBUG_CNTL_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CNTRL_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_THROTTLE_0_CGC_CNTRL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CGC_CNTRL_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CGC_CNTRL_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_PERIOD] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_PERIOD_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_PERIOD_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_COUNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_COUNT_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_GRANT_COUNT_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_00] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_00_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_00_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_01] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_01_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_01_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_02] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_02_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_02_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_03] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_03_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_THRESHOLD_03_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_PEAK_ACCUM_CREDIT_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_CNTL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_CNTL_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_CNTL_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_READBACK] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_READBACK_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_DEBUG_READBACK_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_CONFIG_CLK_CONTROL_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_THROTTLE_0_SPARE_REGS_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_STATUS_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_CLEAR_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_GLOBAL_INTERRUPT_ENABLE_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_STATUS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_STATUS_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_STATUS_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_CLEAR] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_CLEAR_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_CLEAR_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_INTERRUPT_ENABLE_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_CORE_CLOCKON_CONTROL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_CORE_CLOCKON_CONTROL_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON_SW_RESET] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_SW_RESET_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_SW_RESET_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON_CGC_CNTRL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CGC_CNTRL_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CGC_CNTRL_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ENABLE_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON_CLEAR] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CLEAR_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_CLEAR_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON_BYTE_COUNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BYTE_COUNT_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BYTE_COUNT_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON_THRESHOLD] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_THRESHOLD_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_THRESHOLD_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MASK] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MASK_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MASK_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MATCH] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MATCH_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_MID_MATCH_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ENABLE] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ENABLE_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ENABLE_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON2_CLEAR] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_CLEAR_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_CLEAR_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_SAMPLING_WINDOW_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_HIGH_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_MEDIUM_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_THRESHOLD_LOW_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_ACTIONS_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_THRESHOLD_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_BYTE_COUNT_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON2_WINDOW_TIMER] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_WINDOW_TIMER_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_WINDOW_TIMER_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONE_COUNT_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_OFFS(0),
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_OFFS(1) -
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_OFFS(0), 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_MAXn, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON2_ZONEn_MAX_BYTE_COUNT_ATTR, 0},
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MASK] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MASK_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MASK_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MATCH] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MATCH_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_PID_MATCH_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MASK] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MASK_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MASK_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MATCH] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MATCH_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_BID_MATCH_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_STATUS_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_CLEAR_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_STATS_COUNTER_INTERRUPT_ENABLE_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_OFFS,
	0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNTERS_ENABLE_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_PERIOD] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_PERIOD_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_PERIOD_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON_ACCEPT_COUNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ACCEPT_COUNT_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_ACCEPT_COUNT_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNT_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_REJECT_COUNT_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON_IDLE_COUNT] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_IDLE_COUNT_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_IDLE_COUNT_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON_INTR_TARGET] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_INTR_TARGET_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_INTR_TARGET_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_CNTL] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_CNTL_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_CNTL_ATTR },
	[ECPRI_HW_V2_0][ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_READBACK] = {
	ecpri_dma_reg_construct_dummy, ecpri_dma_reg_parse_dummy,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_READBACK_OFFS, 0, 0, 0, 0, 0,
	HWIO_ECPRI_DMA0_THROTTLE_BWMON_BWMON_DEBUG_READBACK_ATTR }
};

/*
 * ecpri_dma_hal_read_reg_n_fields() - Get the parsed value of n parameterized reg
 */
u32 ecpri_dma_hal_read_reg_fields(enum ecpri_dma_hal_reg_name reg, void* fields)
{
	return ecpri_dma_hal_read_reg_mn_fields(reg, 0, 0, fields);
}

/*
 * ecpri_dma_hal_read_reg_n_fields() - Get the parsed value of n parameterized reg
 */
u32 ecpri_dma_hal_read_reg_n_fields(enum ecpri_dma_hal_reg_name reg, u32 n, void* fields)
{
	return ecpri_dma_hal_read_reg_mn_fields(reg, 0, n, fields);
}

/*
 * ecpri_dma_hal_read_reg_mn_fields() - Get the parsed value of n parameterized reg
 */
u32 ecpri_dma_hal_read_reg_mn_fields(enum ecpri_dma_hal_reg_name reg,
	u32 m, u32 n, void* fields)
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

	offset = ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].offset;
	if (offset == -1) {
		DMAHAL_ERR("Read access to obsolete reg=%s\n",
			ecpri_dma_hal_reg_name_str(reg));
		WARN_ON(1);
		return -EPERM;
	}

	if ((ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].attr &
		ECPRI_DMA_HAL_REG_ATTR_READ_ONLY) == 0) {
		DMAHAL_ERR("Register doesn't have READ permissions reg=%u\n", reg);
		WARN_ON(1);
		return -EINVAL;
	}

	DMAHAL_DBG_LOW("read from %s m=%u n=%u and parse it\n",
		ecpri_dma_hal_reg_name_str(reg), m, n);
	offset += ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].m_ofst * m;
	offset += ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].n_ofst * n;
	val = ioread32(ecpri_dma_hal_ctx->base + offset);
	ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].parse(reg, fields, val);

	return val;
}

/*
 * ecpri_dma_hal_write_reg_fields() - Write to parameterized reg a prased value
 */
void ecpri_dma_hal_write_reg_fields(enum ecpri_dma_hal_reg_name reg,
	const void* fields)
{
	ecpri_dma_hal_write_reg_mn_fields(reg, 0, 0, fields);
}

/*
 * ecpri_dma_hal_write_reg_n_fields() - Write to n parameterized reg a prased value
 */
void ecpri_dma_hal_write_reg_n_fields(enum ecpri_dma_hal_reg_name reg, u32 n,
	const void* fields)
{
	ecpri_dma_hal_write_reg_mn_fields(reg, 0, n, fields);
}

/*
 * ecpri_dma_hal_write_reg_mn_fields() - Write to n parameterized reg a prased value
 */
void ecpri_dma_hal_write_reg_mn_fields(enum ecpri_dma_hal_reg_name reg, u32 m,
	u32 n, const void* fields)
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


	offset = ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].offset;
	if (offset == -1) {
		DMAHAL_ERR("Write access to obsolete reg=%s\n",
			ecpri_dma_hal_reg_name_str(reg));
		WARN_ON(1);
		return;
	}

	if ((ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].attr &
		ECPRI_DMA_HAL_REG_ATTR_WRITE_ONLY) == 0) {
		DMAHAL_ERR("Register doesn't have WRITE permissions reg=%u\n", reg);
		WARN_ON(1);
		return;
	}

	DMAHAL_DBG_LOW("write to %s m=%u n=%u after constructing it\n",
		ecpri_dma_hal_reg_name_str(reg), m, n);
	offset += ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].m_ofst * m;
	offset += ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].n_ofst * n;
	ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].construct(reg, fields, &val);

	iowrite32(val, ecpri_dma_hal_ctx->base + offset);
}

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
	return ecpri_dma_hal_read_reg_mn(reg, 0, n);
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

	offset = ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].offset;
	if (offset == -1) {
		DMAHAL_ERR("Read access to obsolete reg=%s\n",
			ecpri_dma_hal_reg_name_str(reg));
		WARN_ON_ONCE(1);
		return -EPERM;
	}

	if ((ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].attr &
		ECPRI_DMA_HAL_REG_ATTR_READ_ONLY) == 0) {
		DMAHAL_ERR("Register doesn't have READ permissions reg=%u\n", reg);
		WARN_ON(1);
		return -EINVAL;
	}

	//DMAHAL_DBG_LOW("read %s m=%u n=%u\n",
	//	ecpri_dma_hal_reg_name_str(reg), m, n);

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

	offset = ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].offset;
	if (offset == -1) {
		DMAHAL_ERR("Write access to obsolete reg=%s\n",
			ecpri_dma_hal_reg_name_str(reg));
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

	offset = ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].offset;
	if (offset == -1) {
		DMAHAL_ERR("Access to obsolete reg=%s\n",
			ecpri_dma_hal_reg_name_str(reg));
		WARN_ON(1);
		return -EPERM;
	}

	DMAHAL_DBG_LOW("get offset of %s m=%u n=%u\n",
		ecpri_dma_hal_reg_name_str(reg), m, n);

	offset += ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].m_ofst * m;
	offset += ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].n_ofst * n;

	return offset;
}

/*
 * Gets _MAXm from the HWIO
 */
u32 ecpri_dma_hal_get_reg_max_m(enum ecpri_dma_hal_reg_name reg)
{
	u32 m_end;
	u32 offset;

	if (reg >= DMA_REG_MAX) {
		DMAHAL_ERR("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return -EINVAL;
	}

	offset = ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].offset;
	if (offset == -1) {
		DMAHAL_ERR("Access to obsolete reg=%s\n",
			ecpri_dma_hal_reg_name_str(reg));
		WARN_ON(1);
		return -EPERM;
	}

	DMAHAL_DBG_LOW("get max m for %s\n",
		ecpri_dma_hal_reg_name_str(reg));

	m_end = ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].m_end;

	return m_end;
}

/*
 * Gets _MAXn from the HWIO
 */
u32 ecpri_dma_hal_get_reg_max_n(enum ecpri_dma_hal_reg_name reg)
{
	u32 max_n;
	u32 offset;

	if (reg >= DMA_REG_MAX) {
		DMAHAL_ERR("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return -EINVAL;
	}

	offset = ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].offset;
	if (offset == -1) {
		DMAHAL_ERR("Access to obsolete reg=%s\n",
			ecpri_dma_hal_reg_name_str(reg));
		WARN_ON(1);
		return -EPERM;
	}

	DMAHAL_DBG_LOW("get max n for %s\n",
		ecpri_dma_hal_reg_name_str(reg));

	max_n = ecpri_dma_hal_reg_objs[ecpri_dma_hal_ctx->ecpri_hw_ver][reg].n_end;

	return max_n;
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
