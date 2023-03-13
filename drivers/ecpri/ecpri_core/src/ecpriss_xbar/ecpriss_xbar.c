/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include "ecpriss_core.h"

#define ECPRISS_PORT_OC_3 3
#define ENABLE_BIT 1
#define DISABLE_BIT 0
#include "ecpriss_log.h"

void ecpriss_xbar_config_stats_update(void){
	uint64_t val=0;
	int fh_index;
	int pcid_index;

	ecpri_xbar_hwio_def_ecpri_xbar_lut_xbar_fhrx_m_lut_n_s xbar_fhrx_m_lut_n;
#ifdef C2C
	ecpri_xbar_hwio_def_ecpri_xbar_lut_xbar_c2crx_m_dl_lut_n_s xbar_c2crx_m_dl_n;
	ecpri_xbar_hwio_def_ecpri_xbar_lut_xbar_c2crx_m_ul_lut_n_s xbar_c2crx_m_ul_n;
#endif
	ecpri_xbar_hwio_def_ecpri_xbar_lut_xbar_ocrx_m_lut_n_s xbar_ocrx_m_lut_n;
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_cfg_s xbar_cfg;


	val = ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL, ECPRI_XBAR_XBAR_CFG,0, &xbar_cfg);
	ecpriss_pdata->cfg_stats.xbar_cfg.global_cfg.global  = val;
#ifdef DEBUG
	ECPRILOGINFO(" ECPRI_XBAR_XBAR_CFG val = 0x%x \n",val);
#endif
	for(fh_index=0; fh_index < NUM_OF_FHP; fh_index++) {
		for(pcid_index=0; pcid_index < LUT_INDEX; pcid_index++) {
			val = ecpriss_xbar_hal_read_reg_mn_fields(ECPRISS_XBAR_LUT,
					ECPRI_XBAR_LUT_XBAR_FHRX_m_LUT_n,
					fh_index,
					pcid_index,
					&xbar_fhrx_m_lut_n);
			ecpriss_pdata->cfg_stats.xbar_cfg.lut_cfg.fhrx[fh_index][pcid_index]  = val;

#ifdef DEBUG
			ECPRILOGINFO(" ECPRI_XBAR_LUT_XBAR_FHRX_m_LUT_n val = 0x%x FH_index = %d, PCID_index = %d\n",val,fh_index,pcid_index);
#endif
#ifdef C2C
			val = ecpriss_xbar_hal_read_reg_mn_fields(ECPRISS_XBAR_LUT,
					ECPRI_XBAR_LUT_XBAR_C2CRX_m_UL_LUT_n,
					fh_index,
					pcid_index,
					&xbar_c2crx_m_ul_n);
			ECPRILOGINFO(" ECPRI_XBAR_LUT_XBAR_C2CRX_m_UL_LUT_n, val = 0x%x FH_index = %d, PCID_index = %d\n",val,fh_index,pcid_index);

			val = ecpriss_xbar_hal_read_reg_mn_fields(ECPRISS_XBAR_LUT,
					ECPRI_XBAR_LUT_XBAR_C2CRX_m_DL_LUT_n,
					fh_index,
					pcid_index,
					&xbar_c2crx_m_dl_n);
			ECPRILOGINFO(" ECPRI_XBAR_LUT_XBAR_C2CRX_m_DL_LUT_n, val = 0x%x FH_index = %d, PCID_index = %d\n",val,fh_index,pcid_index);
#endif
			val = ecpriss_xbar_hal_read_reg_mn_fields(ECPRISS_XBAR_LUT,
					ECPRI_XBAR_LUT_XBAR_OCRX_m_LUT_n,
					fh_index,
					pcid_index,
					&xbar_ocrx_m_lut_n);
			ecpriss_pdata->cfg_stats.xbar_cfg.lut_cfg.ocrx[fh_index][pcid_index]  = val;
#ifdef DEBUG
			ECPRILOGINFO(" ECPRI_XBAR_LUT_XBAR_OCRX_m_LUT_n, val = 0x%x FH_index = %d, PCID_index = %d\n",val,fh_index,pcid_index);
#endif
		}
	}
}
void ecpriss_xbar_config_stats_update_v2(void){
	uint64_t val=0;
	int fh_index;
	int pcid_index;

	ecpri_xbar_hwio_def_ecpri_xbar_fhrx_m_lut_n_s xbar_fhrx_m_lut_n;
#ifdef C2C
	ecpri_xbar_hwio_def_ecpri_xbar_c2crx_m_lut_n_s xbar_c2crx_m_n;
#endif
	ecpri_xbar_hwio_def_ecpri_xbar_ocrx_m_lut_n_s xbar_ocrx_m_lut_n;
	ecpri_xbar_hwio_def_ecpri_xbar_cfg_s xbar_cfg;


	val = ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL, ECPRI_XBAR_CFG,0, &xbar_cfg);
	ecpriss_pdata_v2->cfg_stats_v2.xbar_cfg_v2.global_cfg.global  = val;
#ifdef DEBUG
	ECPRILOGINFO(" ECPRI_XBAR_XBAR_CFG val = 0x%x \n",val);
#endif
	for(fh_index=0; fh_index < NUM_OF_FHP; fh_index++) {
		for(pcid_index=0; pcid_index < LUT_INDEX; pcid_index++) {
			val = ecpriss_xbar_hal_read_reg_mn_fields(ECPRISS_XBAR_LUT,
					ECPRI_XBAR_LUT_XBAR_FHRX_m_LUT_n_V2,
					fh_index,
					pcid_index,
					&xbar_fhrx_m_lut_n);
			ecpriss_pdata_v2->cfg_stats_v2.xbar_cfg_v2.lut_cfg.fhrx[fh_index][pcid_index]  = val;

#ifdef DEBUG
			ECPRILOGINFO(" ECPRI_XBAR_LUT_XBAR_FHRX_m_LUT_n val = 0x%x FH_index = %d, PCID_index = %d\n",val,fh_index,pcid_i
#endif
#ifdef C2C
					val = ecpriss_xbar_hal_read_reg_mn_fields(ECPRISS_XBAR_LUT,
						ECPRI_XBAR_LUT_XBAR_C2CRX_m_LUT_n_V2,
						fh_index,
						pcid_index,
						&xbar_c2crx_m_n);
					ECPRILOGINFO(" ECPRI_XBAR_LUT_XBAR_C2CRX_m_LUT_n, val = 0x%x FH_index = %d, PCID_index = %d\n",val,fh_index,pcid
#endif
						val = ecpriss_xbar_hal_read_reg_mn_fields(ECPRISS_XBAR_LUT,
							ECPRI_XBAR_LUT_XBAR_OCRX_m_LUT_n_V2,
							fh_index,
							pcid_index,
							&xbar_ocrx_m_lut_n);
						ecpriss_pdata_v2->cfg_stats_v2.xbar_cfg_v2.lut_cfg.ocrx[fh_index][pcid_index]  = val;
#ifdef DEBUG
						ECPRILOGINFO(" ECPRI_XBAR_LUT_XBAR_OCRX_m_LUT_n, val = 0x%x FH_index = %d, PCID_index = %d\n",val,fh_index,pcid_
#endif
							}
							}
}


void ecpriss_xbar_stats_update(void)
{
	uint64_t val=0;
	int link_index;
	uint64_t curr_wm_index = 0;

	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_fh_buff_watermark_s xbar_ocrx_fh_buff_watermark;
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_0_1_buff_watermark_s xbar_dbg_ocrx_0_1_buff_watermark;
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_2_3_buff_watermark_s xbar_dbg_ocrx_2_3_buff_watermark;
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_octx_oc_0_1_buff_watermark_s octx_oc_0_1_buff_watermark;
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_octx_oc_2_3_buff_watermark_s octx_oc_2_3_buff_watermark;
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_fhrx_unknown_pcid_cnt_s xbar_dbg_fhrx_unknown_pcid_cnt;
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_dbg_ocrx_unknown_pcid_cnt_s xbar_dbg_ocrx_unknown_pcid_cnt;

	curr_wm_index = ecpriss_pdata->xbar_ctx->stats.curr_wm_index % MAX_XBAR_WM_ENTRY;
	ecpriss_pdata->xbar_ctx->stats.curr_wm_index++ ;

	for(link_index=0;link_index<TOTAL_LINKS;link_index++) {
		val = ecpriss_xbar_hal_read_reg_n(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_FHRX_PKT_CNT_n,link_index);
		ecpriss_pdata->xbar_ctx->stats.xbar_fhrx_pkt_cnt[link_index] += val;
		ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_FHRX_PKT_CNT_n val = %d link_index = %d\n",val,link_index);

		val = ecpriss_xbar_hal_read_reg_n(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_FHTX_PKT_CNT_n,link_index);
		ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_FHTX_PKT_CNT_n val = %d link_index = %d\n",val,link_index);
		ecpriss_pdata->xbar_ctx->stats.xbar_fhtx_pkt_cnt[link_index] += val;

		val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_C2CRX_PKT_CNT_n);
		ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_C2CRX_PKT_CNT_n val = %d link_index = %d\n",val,link_index);
		ecpriss_pdata->xbar_ctx->stats.xbar_c2crx_pkt_cnt[link_index] += val;

		val = ecpriss_xbar_hal_read_reg_n(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_C2CTX_PKT_CNT_n,link_index);
		ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_C2CTX_PKT_CNT_n val = %d link_index = %d\n",val,link_index);
		ecpriss_pdata->xbar_ctx->stats.xbar_c2ctx_pkt_cnt[link_index] += val;

		val = ecpriss_xbar_hal_read_reg_n(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n,link_index);
		ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n val = %d link_index = %d\n",val,link_index);
		ecpriss_pdata->xbar_ctx->stats.ocrx_unknown_pcid_info_1_n[link_index] += val;

		val = ecpriss_xbar_hal_read_reg_n(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n,link_index);
		ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n val = %d link_index = %d\n",val,link_index);
		ecpriss_pdata->xbar_ctx->stats.ocrx_unknown_pcid_info_2_n[link_index] += val;

		val = ecpriss_xbar_hal_read_reg_n(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n,link_index);
		ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n val = %d link_index = %d\n",val,link_index);
		ecpriss_pdata->xbar_ctx->stats.fhrx_unknown_pcid_info_1_n[link_index] += val;

		val = ecpriss_xbar_hal_read_reg_n(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n,link_index);
		ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n val = %d link_index = %d\n",val,link_index);
		ecpriss_pdata->xbar_ctx->stats.fhrx_unknown_pcid_info_2_n[link_index] += val;

	}
	for(link_index=0; link_index < XBAR_LINKS; link_index++) {

		val = ecpriss_xbar_hal_read_reg_n(ECPRISS_XBAR_GLOBAL, ECPRI_XBAR_XBAR_DBG_OCTX_PKT_CNT_n,link_index);
		ecpriss_pdata->xbar_ctx->stats.xbar_octx_pkt_cnt[link_index] += val;
		ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_OCTX_PKT_CNT_n val = %d link_index = %d\n",val,link_index);

		val = ecpriss_xbar_hal_read_reg_n(ECPRISS_XBAR_GLOBAL, ECPRI_XBAR_XBAR_DBG_OCRX_PKT_CNT_n,link_index);
		ecpriss_pdata->xbar_ctx->stats.xbar_ocrx_pkt_cnt[link_index] += val;
		ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_OCRX_PKT_CNT_n val = %d link_index = %d\n",val,link_index);

	}

	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_FHRX_DMA_PKT_CNT);
	ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_FHRX_DMA_PKT_CNT val = %d\n",val);
	ecpriss_pdata->xbar_ctx->stats.xbar_fhrx_dma_pkt_cnt += val;

	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_FHRX_UC_PKT_CNT);
	ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_FHRX_UC_PKT_CNT val = %d\n",val);
	ecpriss_pdata->xbar_ctx->stats.xbar_fhrx_uc_pkt_cnt += val;

	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_FHRX_UC_ERR_PKT_CNT);
	ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_FHRX_UC_ERR_PKT_CNT val = %d\n",val);
	ecpriss_pdata->xbar_ctx->stats.xbar_fhrx_uc_err_pkt_cnt += val;

	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_FHRX_ERR_PKT_CNT);
	ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_FHRX_ERR_PKT_CNT val = %d\n",val);
	ecpriss_pdata->xbar_ctx->stats.xbar_fhrx_err_pkt_cnt += val;



	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_FHTX_C2C_PKT_OVF_CNT);
	ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_FHTX_C2C_PKT_OVF_CNT val = %d\n",val);
	ecpriss_pdata->xbar_ctx->stats.xbar_fhtx_c2c_pkt_ovf_cnt += val;

	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_FHTX_DMA_PKT_CNT);
	ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_FHTX_DMA_PKT_CNT val = %d\n",val);
	ecpriss_pdata->xbar_ctx->stats.xbar_fhtx_dma_pkt_cnt += val;

	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_C2CRX_DMA_PKT_CNT);
	ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_C2CRX_DMA_PKT_CNT val = %d\n",val);
	ecpriss_pdata->xbar_ctx->stats.xbar_c2crx_dma_pkt_cnt += val;

	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_C2CRX_ERR_PKT_CNT);
	ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_C2CRX_ERR_PKT_CNT val = %d\n",val);
	ecpriss_pdata->xbar_ctx->stats.xbar_c2crx_err_pkt_cnt += val;



	val = ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL,
			ECPRI_XBAR_XBAR_DBG_OCRX_FH_BUFF_WATERMARK,
			0, &xbar_ocrx_fh_buff_watermark);
	ecpriss_pdata->xbar_ctx->stats.xbar_ocrx_fh_buff_watermark_fh0 = xbar_ocrx_fh_buff_watermark.fh0;
	ecpriss_pdata->xbar_ctx->stats.xbar_ocrx_fh_buff_watermark_fh1 = xbar_ocrx_fh_buff_watermark.fh1;
	ecpriss_pdata->xbar_ctx->stats.xbar_ocrx_fh_buff_watermark_fh2 = xbar_ocrx_fh_buff_watermark.fh2;

	ecpriss_pdata->xbar_ctx->stats.ocrx_fh_wm_fh0[curr_wm_index] = xbar_ocrx_fh_buff_watermark.fh0;
	ecpriss_pdata->xbar_ctx->stats.ocrx_fh_wm_fh1[curr_wm_index] = xbar_ocrx_fh_buff_watermark.fh1;
	ecpriss_pdata->xbar_ctx->stats.ocrx_fh_wm_fh2[curr_wm_index] = xbar_ocrx_fh_buff_watermark.fh2;


	ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_FHTX_UC_PKT_CNT val = %u\n",
			xbar_ocrx_fh_buff_watermark);

	val = ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL,
			ECPRI_XBAR_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK,
			0, &xbar_dbg_ocrx_0_1_buff_watermark);
	ecpriss_pdata->xbar_ctx->stats.xbar_dbg_ocrx_0_1_buff_watermark_cc0 = xbar_dbg_ocrx_0_1_buff_watermark.cc0;
	ecpriss_pdata->xbar_ctx->stats.xbar_dbg_ocrx_0_1_buff_watermark_cc1 = xbar_dbg_ocrx_0_1_buff_watermark.cc1;

	ecpriss_pdata->xbar_ctx->stats.ocrx_0_1_wm_cc0[curr_wm_index] = xbar_dbg_ocrx_0_1_buff_watermark.cc0;
	ecpriss_pdata->xbar_ctx->stats.ocrx_0_1_wm_cc1[curr_wm_index] = xbar_dbg_ocrx_0_1_buff_watermark.cc1;

	ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK val = %u\n",
			xbar_dbg_ocrx_0_1_buff_watermark);

	val = ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL,
			ECPRI_XBAR_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK,
			0,&xbar_dbg_ocrx_2_3_buff_watermark);
	ecpriss_pdata->xbar_ctx->stats.xbar_dbg_ocrx_2_3_buff_watermark_cc2 = xbar_dbg_ocrx_2_3_buff_watermark.cc2;
	ecpriss_pdata->xbar_ctx->stats.xbar_dbg_ocrx_2_3_buff_watermark_cc3 = xbar_dbg_ocrx_2_3_buff_watermark.cc3;

	ecpriss_pdata->xbar_ctx->stats.ocrx_2_3_wm_cc2[curr_wm_index] = xbar_dbg_ocrx_2_3_buff_watermark.cc2;
	ecpriss_pdata->xbar_ctx->stats.ocrx_2_3_wm_cc3[curr_wm_index] = xbar_dbg_ocrx_2_3_buff_watermark.cc3;


	ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK, val = %u\n",
			xbar_dbg_ocrx_2_3_buff_watermark);

	val = ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL,
			ECPRI_XBAR_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK,
			0,&octx_oc_0_1_buff_watermark);
	ecpriss_pdata->xbar_ctx->stats.octx_oc_0_1_buff_watermark_cc0 = octx_oc_0_1_buff_watermark.cc0;
	ecpriss_pdata->xbar_ctx->stats.octx_oc_0_1_buff_watermark_cc1 = octx_oc_0_1_buff_watermark.cc1;

	ecpriss_pdata->xbar_ctx->stats.octx_0_1_wm_cc0[curr_wm_index] = octx_oc_0_1_buff_watermark.cc0;
	ecpriss_pdata->xbar_ctx->stats.octx_0_1_wm_cc1[curr_wm_index] = octx_oc_0_1_buff_watermark.cc1;


	ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK, val = %u\n",
			octx_oc_0_1_buff_watermark);

	val = ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL,
			ECPRI_XBAR_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK,
			0, &octx_oc_2_3_buff_watermark);
	ecpriss_pdata->xbar_ctx->stats.octx_oc_2_3_buff_watermark_cc2 = octx_oc_2_3_buff_watermark.cc2;
	ecpriss_pdata->xbar_ctx->stats.octx_oc_2_3_buff_watermark_cc3 = octx_oc_2_3_buff_watermark.cc3;

	ecpriss_pdata->xbar_ctx->stats.octx_2_3_wm_cc2[curr_wm_index] = octx_oc_2_3_buff_watermark.cc2;
	ecpriss_pdata->xbar_ctx->stats.octx_2_3_wm_cc3[curr_wm_index] = octx_oc_2_3_buff_watermark.cc3;


	ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK, val = %u\n",
			octx_oc_2_3_buff_watermark);


	val = ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL,
			ECPRI_XBAR_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT,
			0,&xbar_dbg_fhrx_unknown_pcid_cnt);

	ecpriss_pdata->xbar_ctx->stats.xbar_dbg_fhrx_unknown_pcid_cnt_fhrx_0_cnt = xbar_dbg_fhrx_unknown_pcid_cnt.fhrx_0_cnt;
	ecpriss_pdata->xbar_ctx->stats.xbar_dbg_fhrx_unknown_pcid_cnt_fhrx_1_cnt = xbar_dbg_fhrx_unknown_pcid_cnt.fhrx_1_cnt;
	ecpriss_pdata->xbar_ctx->stats.xbar_dbg_fhrx_unknown_pcid_cnt_fhrx_2_cnt = xbar_dbg_fhrx_unknown_pcid_cnt.fhrx_2_cnt;

	val = ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL,
			ECPRI_XBAR_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT,
			0,&xbar_dbg_ocrx_unknown_pcid_cnt);

	ecpriss_pdata->xbar_ctx->stats.xbar_dbg_ocrx_unknown_pcid_cnt_ocrx_fh_0_cnt = xbar_dbg_ocrx_unknown_pcid_cnt.ocrx_fh_0_cnt;
	ecpriss_pdata->xbar_ctx->stats.xbar_dbg_ocrx_unknown_pcid_cnt_ocrx_fh_1_cnt = xbar_dbg_ocrx_unknown_pcid_cnt.ocrx_fh_1_cnt;
	ecpriss_pdata->xbar_ctx->stats.xbar_dbg_ocrx_unknown_pcid_cnt_ocrx_fh_2_cnt = xbar_dbg_ocrx_unknown_pcid_cnt.ocrx_fh_2_cnt;

	return;
}

void ecpriss_xbar_stats_update_v2(void)
{
	uint64_t val=0;
	int link_index;
	uint64_t curr_wm_index = 0;

	ecpri_xbar_hwio_def_ecpri_xbar_dbg_ocrx_fh_buff_watermark_s xbar_ocrx_fh_buff_watermark;
	ecpri_xbar_hwio_def_ecpri_xbar_dbg_ocrx_0_1_buff_watermark_s xbar_dbg_ocrx_0_1_buff_watermark;
	ecpri_xbar_hwio_def_ecpri_xbar_dbg_ocrx_2_3_buff_watermark_s xbar_dbg_ocrx_2_3_buff_watermark;
	ecpri_xbar_hwio_def_ecpri_xbar_dbg_octx_oc_0_1_buff_watermark_s octx_oc_0_1_buff_watermark;
	ecpri_xbar_hwio_def_ecpri_xbar_dbg_octx_oc_2_3_buff_watermark_s octx_oc_2_3_buff_watermark;
	ecpri_xbar_hwio_def_ecpri_xbar_dbg_fhrx_unknown_pcid_cnt_s xbar_dbg_fhrx_unknown_pcid_cnt;
        ecpri_xbar_hwio_def_ecpri_xbar_dbg_ocrx_unknown_pcid_cnt_s xbar_dbg_ocrx_unknown_pcid_cnt;

	curr_wm_index = ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.curr_wm_index % MAX_XBAR_WM_ENTRY;
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.curr_wm_index++ ;

	for(link_index=0;link_index<TOTAL_LINKS;link_index++) {
		val = ecpriss_xbar_hal_read_reg_n(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_DBG_FHRX_PKT_CNT_n,link_index);
		ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_fhrx_pkt_cnt[link_index] += val;
		ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_FHRX_PKT_CNT_n val = %d link_index = %d\n",val,link_index);

		val = ecpriss_xbar_hal_read_reg_n(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_DBG_FHTX_PKT_CNT_n,link_index);
		ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_FHTX_PKT_CNT_n val = %d link_index = %d\n",val,link_index);
		ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_fhtx_pkt_cnt[link_index] += val;

		val = ecpriss_xbar_hal_read_reg_n(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_DBG_OCRX_FH_PKT_CNT_n,link_index);
		ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_OCRX_FH_PKT_CNT_n val = %d link_index = %d\n",val,link_index);
		ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_ocrx_fh_pkt_cnt[link_index] += val;

		val = ecpriss_xbar_hal_read_reg_n(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n,link_index);
                ECPRILOGDBG("ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_1_n val = %d link_index = %d\n",val,link_index);
                ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.ocrx_unknown_pcid_info_1_n[link_index] = val;

                val = ecpriss_xbar_hal_read_reg_n(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n,link_index);
                ECPRILOGDBG("ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_INFO_2_n val = %d link_index = %d\n",val,link_index);
                ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.ocrx_unknown_pcid_info_2_n[link_index] = val;

                val = ecpriss_xbar_hal_read_reg_n(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n,link_index);
                ECPRILOGDBG("ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_1_n val = %d link_index = %d\n",val,link_index);
                ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.fhrx_unknown_pcid_info_1_n[link_index] = val;

                val = ecpriss_xbar_hal_read_reg_n(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n,link_index);
                ECPRILOGDBG("ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_INFO_2_n val = %d link_index = %d\n",val,link_index);
                ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.fhrx_unknown_pcid_info_2_n[link_index] = val;


	}
	for(link_index=0; link_index < XBAR_LINKS; link_index++) {

		val = ecpriss_xbar_hal_read_reg_n(ECPRISS_XBAR_GLOBAL, ECPRI_XBAR_DBG_OCTX_PKT_CNT_n,link_index);
		ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_octx_pkt_cnt[link_index] += val;
		ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_OCTX_PKT_CNT_n val = %d link_index = %d\n",val,link_index);

		val = ecpriss_xbar_hal_read_reg_n(ECPRISS_XBAR_GLOBAL, ECPRI_XBAR_DBG_OCRX_PKT_CNT_n,link_index);
		ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_ocrx_pkt_cnt[link_index] += val;
		ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_OCRX_PKT_CNT_n val = %d link_index = %d\n",val,link_index);

	}

	for(link_index=0; link_index < NUM_OF_FHP; link_index++) {

		val = ecpriss_xbar_hal_read_reg_n(ECPRISS_XBAR_GLOBAL, ECPRI_XBAR_DBG_FHRX_OC_PKT_CNT,link_index);
		ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_fhrx_oc_pkt_cnt[link_index] += val;
		ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_FHRX_OC_PKT_CNT_n val = %d link_index = %d\n",val,link_index);

		val = ecpriss_xbar_hal_read_reg_n(ECPRISS_XBAR_GLOBAL, ECPRI_XBAR_DBG_FHRX_C2C_PKT_CNT,link_index);
		ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_fhrx_c2c_pkt_cnt[link_index] += val;
		ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_FHRX_C2C_PKT_CNT_n val = %d link_index = %d\n",val,link_index);

		val = ecpriss_xbar_hal_read_reg_n(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_DBG_OCRX_C2C_PKT_CNT_n,link_index);
		ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_C2CTX_PKT_CNT_n val = %d link_index = %d\n",val,link_index);
		ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_ocrx_c2c_pkt_cnt[link_index] += val;


	}
	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_DBG_FHRX_DMA_PKT_CNT);
	ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_FHRX_DMA_PKT_CNT val = %d\n",val);
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_fhrx_dma_pkt_cnt += val;

	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_DBG_FHRX_UC_PKT_CNT);
	ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_FHRX_UC_PKT_CNT val = %d\n",val);
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_fhrx_uc_pkt_cnt += val;

	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_DBG_FHRX_UC_ERR_PKT_CNT);
	ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_FHRX_UC_ERR_PKT_CNT val = %d\n",val);
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_fhrx_uc_err_pkt_cnt += val;

	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_DBG_FHRX_ERR_PKT_CNT);
	ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_FHRX_ERR_PKT_CNT val = %d\n",val);
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_fhrx_err_pkt_cnt += val;


	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_DBG_FHTX_C2C_PKT_OVF_DROP_CNT);
	ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_FHTX_C2C_PKT_OVF_CNT val = %d\n",val);
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_fhtx_c2c_pkt_ovf_cnt += val;

	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_DBG_FHTX_DMA_PKT_CNT);
	ECPRILOGDBG("       ECPRI_XBAR_XBAR_DBG_FHTX_DMA_PKT_CNT val = %d\n",val);
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_fhtx_dma_pkt_cnt += val;

	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_DBG_FHTX_UC_PKT_CNT);
	ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_FHTX_UC_PKT_CNT val = %d\n",val);
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_fhtx_uc_pkt_cnt += val;

	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_DBG_OCTX_C2C_PKT_DROP_CNT);
	ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_OCTX_C2C_PKT_DROP_CNT val = %d\n",val);
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_octx_c2c_pkt_drop_cnt += val;

	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_DBG_OCTX_FH_PKT_DROP_CNT);
	ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_OCTX_C2C_PKT_DROP_CNT val = %d\n",val);
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_octx_fh_pkt_drop_cnt += val;

	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_DBG_OCTX_C2C_LEN_ERR_CNT);
	ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_OCTX_C2C_LEN_ERR_CNT val = %d\n",val);
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_octx_c2c_len_err_cnt += val;

	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_DBG_OCTX_FH_LEN_ERR_CNT);
	ECPRILOGDBG("ECPRI_XBAR_XBAR_DBG_OCTX_FH_LEN_ERR_CNT val = %d\n",val);
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_octx_fh_len_err_cnt += val;

       val = ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL,
                        ECPRI_XBAR_DBG_FHRX_UNKNOWN_PCID_CNT,
                        0,&xbar_dbg_fhrx_unknown_pcid_cnt);

        ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_dbg_fhrx_unknown_pcid_cnt_fhrx_0_cnt += xbar_dbg_fhrx_unknown_pcid_cnt.fhrx_0_cnt;
        ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_dbg_fhrx_unknown_pcid_cnt_fhrx_1_cnt += xbar_dbg_fhrx_unknown_pcid_cnt.fhrx_1_cnt;
        ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_dbg_fhrx_unknown_pcid_cnt_fhrx_2_cnt += xbar_dbg_fhrx_unknown_pcid_cnt.fhrx_2_cnt;

        val = ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL,
                        ECPRI_XBAR_DBG_OCRX_UNKNOWN_PCID_CNT,
                        0,&xbar_dbg_ocrx_unknown_pcid_cnt);

        ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_dbg_ocrx_unknown_pcid_cnt_ocrx_fh_0_cnt += xbar_dbg_ocrx_unknown_pcid_cnt.ocrx_fh_0_cnt;
        ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_dbg_ocrx_unknown_pcid_cnt_ocrx_fh_1_cnt += xbar_dbg_ocrx_unknown_pcid_cnt.ocrx_fh_1_cnt;
        ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_dbg_ocrx_unknown_pcid_cnt_ocrx_fh_2_cnt += xbar_dbg_ocrx_unknown_pcid_cnt.ocrx_fh_2_cnt;

	val = ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL,
			ECPRI_XBAR_DBG_OCRX_FH_BUFF_WATERMARK,
			0, &xbar_ocrx_fh_buff_watermark);
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_ocrx_fh_buff_watermark_fh0 = xbar_ocrx_fh_buff_watermark.fh0;
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_ocrx_fh_buff_watermark_fh1 = xbar_ocrx_fh_buff_watermark.fh1;
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_ocrx_fh_buff_watermark_fh2 = xbar_ocrx_fh_buff_watermark.fh2;

	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.ocrx_fh_wm_fh0[curr_wm_index] = xbar_ocrx_fh_buff_watermark.fh0;
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.ocrx_fh_wm_fh1[curr_wm_index] = xbar_ocrx_fh_buff_watermark.fh1;
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.ocrx_fh_wm_fh2[curr_wm_index] = xbar_ocrx_fh_buff_watermark.fh2;

	val = ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL,
			ECPRI_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK,
			0, &xbar_dbg_ocrx_0_1_buff_watermark);
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_dbg_ocrx_0_1_buff_watermark_cc0 = xbar_dbg_ocrx_0_1_buff_watermark.cc0;
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_dbg_ocrx_0_1_buff_watermark_cc1 = xbar_dbg_ocrx_0_1_buff_watermark.cc1;

	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.ocrx_0_1_wm_cc0[curr_wm_index] = xbar_dbg_ocrx_0_1_buff_watermark.cc0;
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.ocrx_0_1_wm_cc1[curr_wm_index] = xbar_dbg_ocrx_0_1_buff_watermark.cc1;

	ECPRILOGDBG("ECPRI_XBAR_DBG_OCRX_0_1_BUFF_WATERMARK val = %u\n",
			xbar_dbg_ocrx_0_1_buff_watermark);

	val = ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL,
			ECPRI_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK,
			0,&xbar_dbg_ocrx_2_3_buff_watermark);
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_dbg_ocrx_2_3_buff_watermark_cc2 = xbar_dbg_ocrx_2_3_buff_watermark.cc2;
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_dbg_ocrx_2_3_buff_watermark_cc3 = xbar_dbg_ocrx_2_3_buff_watermark.cc3;

	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.ocrx_2_3_wm_cc2[curr_wm_index] = xbar_dbg_ocrx_2_3_buff_watermark.cc2;
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.ocrx_2_3_wm_cc3[curr_wm_index] = xbar_dbg_ocrx_2_3_buff_watermark.cc3;


	ECPRILOGDBG("ECPRI_XBAR_DBG_OCRX_2_3_BUFF_WATERMARK, val = %u\n",
			xbar_dbg_ocrx_2_3_buff_watermark);

	val = ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL,
			ECPRI_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK,
			0,&octx_oc_0_1_buff_watermark);
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.octx_oc_0_1_buff_watermark_cc0 = octx_oc_0_1_buff_watermark.cc0;
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.octx_oc_0_1_buff_watermark_cc1 = octx_oc_0_1_buff_watermark.cc1;

	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.octx_0_1_wm_cc0[curr_wm_index] = octx_oc_0_1_buff_watermark.cc0;
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.octx_0_1_wm_cc1[curr_wm_index] = octx_oc_0_1_buff_watermark.cc1;


	ECPRILOGDBG("ECPRI_XBAR_DBG_OCTX_OC_0_1_BUFF_WATERMARK, val = %u\n",
			octx_oc_0_1_buff_watermark);

	val = ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL,
			ECPRI_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK,
			0, &octx_oc_2_3_buff_watermark);
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.octx_oc_2_3_buff_watermark_cc2 = octx_oc_2_3_buff_watermark.cc2;
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.octx_oc_2_3_buff_watermark_cc3 = octx_oc_2_3_buff_watermark.cc3;

	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.octx_2_3_wm_cc2[curr_wm_index] = octx_oc_2_3_buff_watermark.cc2;
	ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.octx_2_3_wm_cc3[curr_wm_index] = octx_oc_2_3_buff_watermark.cc3;


	ECPRILOGDBG("ECPRI_XBAR_DBG_OCTX_OC_2_3_BUFF_WATERMARK, val = %u\n",
			octx_oc_2_3_buff_watermark);

	return;
}

/**
 * ecpriss_check_entry_valid_bits()
 *
 *
 * Returns:	0 on success, negative on failure
 */
static int ecpriss_xbar_check_entry_valid_bits(void)
{
	int ret = 0;
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_lut_status_s xbar_lut_status;
	do{
		memset(&xbar_lut_status,0,sizeof(xbar_lut_status));
		ret = ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL,
				ECPRI_XBAR_XBAR_LUT_STATUS,
				0, &xbar_lut_status);

		if(xbar_lut_status.fhrx_lut_init_done ||
				xbar_lut_status.c2crx_dl_lut_init_done ||
				xbar_lut_status.c2crx_ul_lut_init_done ||
				xbar_lut_status.ocrx_lut_init_done)
		{
			ECPRILOGINFO("ecpriss_xbar_check_entry_valid_bits(): XBAR HW LUT Inited\n");
		}
		else
		{
			ECPRILOGERR("Init LUT done error\n");
			break;
		}
	}while (0);
	return ret;
}


static int ecpriss_xbar_check_entry_valid_bits_v2(void)
{
	int ret = 0;
	ecpri_xbar_hwio_def_ecpri_xbar_lut_status_s xbar_lut_status;
	do{
		memset(&xbar_lut_status,0,sizeof(xbar_lut_status));
		ret = ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL,
				ECPRI_XBAR_LUT_STATUS,
				0, &xbar_lut_status);

		if(xbar_lut_status.fhrx_lut_init_done ||
				xbar_lut_status.c2crx_lut_init_done ||
				xbar_lut_status.ocrx_lut_init_done)
		{
			ECPRILOGINFO("ecpriss_xbar_check_entry_valid_bits(): XBAR HW LUT Inited\n");
		}
		else
		{
			ECPRILOGINFO("Init LUT done error\n");
			break;
		}
	}while (0);
	return ret;
}
static void ecpriss_xbar_flush_init()
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_flush_s xbar_flush;
	int *flush_val;
	memset(&xbar_flush,0xFF,sizeof(xbar_flush));

	/*Read Reset value*/
	ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL, ECPRI_XBAR_XBAR_FLUSH,0, &xbar_flush);
	flush_val = (int*)(&xbar_flush);
	pr_info("Reset xbar flush val = 0x%x\n", *flush_val);

	/*Enable Flush*/
	xbar_flush.flush_fh_0_rx = DISABLE_BIT;
	xbar_flush.flush_fh_0_tx = ENABLE_BIT;
	xbar_flush.flush_fh_1_rx = DISABLE_BIT;
	xbar_flush.flush_fh_1_tx = ENABLE_BIT;
	xbar_flush.flush_fh_2_rx = DISABLE_BIT;
	xbar_flush.flush_fh_2_tx = ENABLE_BIT;
#if 0
	xbar_flush.flush_c2c_0_rx = ENABLE_BIT;
	xbar_flush.flush_c2c_0_tx = ENABLE_BIT;
	xbar_flush.flush_c2c_1_rx = ENABLE_BIT;
	xbar_flush.flush_c2c_1_tx = ENABLE_BIT;
	xbar_flush.flush_c2c_2_rx = ENABLE_BIT;
	xbar_flush.flush_c2c_2_tx = ENABLE_BIT;
#endif
	xbar_flush.flush_oc_0_rx = DISABLE_BIT;
	xbar_flush.flush_oc_0_tx = DISABLE_BIT;
	xbar_flush.flush_oc_1_rx = DISABLE_BIT;
	xbar_flush.flush_oc_1_tx = DISABLE_BIT;
	xbar_flush.flush_oc_2_rx = DISABLE_BIT;
	xbar_flush.flush_oc_2_tx = DISABLE_BIT;
	xbar_flush.flush_oc_3_rx = DISABLE_BIT;
	xbar_flush.flush_oc_3_tx = DISABLE_BIT;

	xbar_flush.reserved0 = 0;
	xbar_flush.reserved1 = 0;
	xbar_flush.reserved2 = 0;

	ecpriss_xbar_hal_write_reg_n_fields(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_FLUSH,
			0,
			&xbar_flush);

	/*Read and check*/
	ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL, ECPRI_XBAR_XBAR_FLUSH,0, &xbar_flush);

	flush_val = (int*)(&xbar_flush);

	pr_info("xbar flush val post write = 0x%x\n", *flush_val);
	return;
}

#if 0
/**
 * ecpriss_xbar_flush()
 *
 *
 * Returns:	0 on success, negative on failure
 */
static void ecpriss_xbar_flush(ecpriss_port_type_e    port_type,
		ecpriss_port_idx_e     port_idx,
		ecpriss_port_dir_e     port_dir)
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_flush_s xbar_flush;

	if(port_type == ECPRISS_PORT_TYPE_FH ||
			port_idx == ECPRISS_PORT_0 ||
			port_dir == ECPRISS_PORT_DIR_RX)
	{
		xbar_flush.flush_fh_0_rx = ENABLE_BIT;
	}
	else if (port_type == ECPRISS_PORT_TYPE_FH ||
			port_idx == ECPRISS_PORT_0 ||
			port_dir == ECPRISS_PORT_DIR_TX)
	{
		xbar_flush.flush_fh_0_tx = ENABLE_BIT;
	}
	else if (port_type == ECPRISS_PORT_TYPE_FH ||
			port_idx == ECPRISS_PORT_1 ||
			port_dir == ECPRISS_PORT_DIR_RX)
	{
		xbar_flush.flush_fh_1_rx = ENABLE_BIT;
	}
	else if (port_type == ECPRISS_PORT_TYPE_FH ||
			port_idx == ECPRISS_PORT_1 ||
			port_dir == ECPRISS_PORT_DIR_TX)
	{
		xbar_flush.flush_fh_1_tx = ENABLE_BIT;
	}
	else if (port_type == ECPRISS_PORT_TYPE_FH ||
			port_idx == ECPRISS_PORT_2 ||
			port_dir == ECPRISS_PORT_DIR_RX)
	{
		xbar_flush.flush_fh_2_rx = ENABLE_BIT;
	}
	else if (port_type == ECPRISS_PORT_TYPE_FH ||
			port_idx == ECPRISS_PORT_2 ||
			port_dir == ECPRISS_PORT_DIR_TX)
	{
		xbar_flush.flush_fh_2_tx = ENABLE_BIT;
	}
	else if (port_type == ECPRISS_PORT_TYPE_C2C ||
			port_idx == ECPRISS_PORT_0 ||
			port_dir == ECPRISS_PORT_DIR_RX)
	{
		xbar_flush.flush_c2c_0_rx = ENABLE_BIT;
	}
	else if (port_type == ECPRISS_PORT_TYPE_C2C ||
			port_idx == ECPRISS_PORT_0 ||
			port_dir == ECPRISS_PORT_DIR_TX)
	{
		xbar_flush.flush_c2c_0_tx = ENABLE_BIT;
	}
	else if (port_type == ECPRISS_PORT_TYPE_C2C ||
			port_idx == ECPRISS_PORT_1 ||
			port_dir == ECPRISS_PORT_DIR_RX)
	{
		xbar_flush.flush_c2c_1_rx = ENABLE_BIT;
	}
	else if (port_type == ECPRISS_PORT_TYPE_C2C ||
			port_idx == ECPRISS_PORT_1 ||
			port_dir == ECPRISS_PORT_DIR_TX)
	{
		xbar_flush.flush_c2c_1_tx = ENABLE_BIT;
	}
	else if (port_type == ECPRISS_PORT_TYPE_C2C ||
			port_idx == ECPRISS_PORT_2 ||
			port_dir == ECPRISS_PORT_DIR_RX)
	{
		xbar_flush.flush_c2c_2_rx = ENABLE_BIT;
	}
	else if (port_type == ECPRISS_PORT_TYPE_C2C ||
			port_idx == ECPRISS_PORT_2 ||
			port_dir == ECPRISS_PORT_DIR_TX)
	{
		xbar_flush.flush_c2c_2_tx = ENABLE_BIT;
	}
	else if (port_type == ECPRISS_PORT_TYPE_OC ||
			port_idx == ECPRISS_PORT_0 ||
			port_dir == ECPRISS_PORT_DIR_RX)
	{
		xbar_flush.flush_oc_0_rx = ENABLE_BIT;
	}
	else if (port_type == ECPRISS_PORT_TYPE_OC ||
			port_idx == ECPRISS_PORT_0 ||
			port_dir == ECPRISS_PORT_DIR_TX)
	{
		xbar_flush.flush_oc_0_tx = ENABLE_BIT;
	}
	else if (port_type == ECPRISS_PORT_TYPE_OC ||
			port_idx == ECPRISS_PORT_1 ||
			port_dir == ECPRISS_PORT_DIR_RX)
	{
		xbar_flush.flush_oc_1_rx = ENABLE_BIT;
	}
	else if (port_type == ECPRISS_PORT_TYPE_OC ||
			port_idx == ECPRISS_PORT_1 ||
			port_dir == ECPRISS_PORT_DIR_TX)
	{
		xbar_flush.flush_oc_1_tx = ENABLE_BIT;
	}
	else if (port_type == ECPRISS_PORT_TYPE_OC ||
			port_idx == ECPRISS_PORT_2 ||
			port_dir == ECPRISS_PORT_DIR_RX)
	{
		xbar_flush.flush_oc_2_rx = ENABLE_BIT;
	}
	else if (port_type == ECPRISS_PORT_TYPE_OC ||
			port_idx == ECPRISS_PORT_2 ||
			port_dir == ECPRISS_PORT_DIR_TX)
	{
		xbar_flush.flush_oc_2_tx = ENABLE_BIT;
	}
	else if (port_type == ECPRISS_PORT_TYPE_OC ||
			port_idx == ECPRISS_PORT_OC_3 ||
			port_dir == ECPRISS_PORT_DIR_RX)
	{
		xbar_flush.flush_oc_3_rx = ENABLE_BIT;
	}
	else if (port_type == ECPRISS_PORT_TYPE_OC ||
			port_idx == ECPRISS_PORT_OC_3 ||
			port_dir == ECPRISS_PORT_DIR_TX)
	{
		xbar_flush.flush_oc_3_tx = ENABLE_BIT;
	}

	ecpriss_xbar_hal_write_reg_n_fields(ECPRISS_XBAR_GLOBAL,
			ECPRI_XBAR_XBAR_FLUSH,
			0,
			&xbar_flush);
	return;
}
#endif

void ecpriss_configure_xbar_flush(ecpriss_port_type_e port_type,
                ecpriss_port_idx_e port_idx, eth_ecpriss_event_e event_type)
{
        ecpri_xbar_hwio_def_ecpri_xbar_xbar_flush_s xbar_flush;

        ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL, ECPRI_XBAR_XBAR_FLUSH,0, &xbar_flush);

        if (port_type == ECPRISS_PORT_TYPE_FH &&
                        port_idx == ECPRISS_PORT_0 &&
                        event_type == ETH_ECPRISS_EVENT_UP){
                pr_err("XBAR flush for port 0 | enable: %d\n", DISABLE_BIT);
                xbar_flush.flush_fh_0_tx = DISABLE_BIT;
        }
        else if (port_type == ECPRISS_PORT_TYPE_FH &&
                        port_idx == ECPRISS_PORT_1 &&
                        event_type == ETH_ECPRISS_EVENT_UP){
                pr_err("XBAR flush for port 1 | enable: %d\n", DISABLE_BIT);
                xbar_flush.flush_fh_1_tx = DISABLE_BIT;
        }
        else if (port_type == ECPRISS_PORT_TYPE_FH &&
                        port_idx == ECPRISS_PORT_2 &&
                        event_type == ETH_ECPRISS_EVENT_UP){
                pr_err("XBAR flush for port 2 | enable: %d\n", DISABLE_BIT);
                xbar_flush.flush_fh_2_tx = DISABLE_BIT;
        }
        else if (port_type == ECPRISS_PORT_TYPE_FH &&
                        port_idx == ECPRISS_PORT_0 &&
                        event_type == ETH_ECPRISS_EVENT_DOWN){
                pr_err("XBAR flush for port 0 | enable: %d\n", ENABLE_BIT);
                xbar_flush.flush_fh_0_tx = ENABLE_BIT;
        }
        else if (port_type == ECPRISS_PORT_TYPE_FH &&
                        port_idx == ECPRISS_PORT_1 &&
                        event_type == ETH_ECPRISS_EVENT_DOWN){
                pr_err("XBAR flush for port 1 | enable: %d\n", ENABLE_BIT);
                xbar_flush.flush_fh_1_tx = ENABLE_BIT;
        }
        else if (port_type == ECPRISS_PORT_TYPE_FH &&
                        port_idx == ECPRISS_PORT_2 &&
                        event_type == ETH_ECPRISS_EVENT_DOWN){
                pr_err("XBAR flush for port 2 | enable: %d\n", ENABLE_BIT);
                xbar_flush.flush_fh_2_tx = ENABLE_BIT;
        }


        ecpriss_xbar_hal_write_reg_n_fields(ECPRISS_XBAR_GLOBAL,
                        ECPRI_XBAR_XBAR_FLUSH,
                        0,
                        &xbar_flush);
        return;
}

static irqreturn_t ecpriss_xbar_isr(int irq, void *ctxt)
{
	unsigned long flags = 0;
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_sw_irq_status_s xbar_sw_irq_status;
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_sw_irq_clr_s xbar_sw_irq_clear;

	spin_lock_irqsave(&ecpriss_pdata->irq_lock, flags);

	ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL,
			ECPRI_XBAR_XBAR_SW_IRQ_STATUS, 0,&xbar_sw_irq_status);

	if(xbar_sw_irq_status.octx_fh_len_err){
		xbar_sw_irq_clear.octx_fh_len_err = 1;
		ecpriss_pdata->xbar_ctx->interrupt_stats.octx_fh_len_err += 1;
	}
	if(xbar_sw_irq_status.octx_c2c_len_err){
		xbar_sw_irq_clear.octx_c2c_len_err = 1;
		ecpriss_pdata->xbar_ctx->interrupt_stats.octx_c2c_len_err += 1;
	}
	if(xbar_sw_irq_status.fhtx_c2c_overflow){
		xbar_sw_irq_clear.fhtx_c2c_overflow = 1;
		ecpriss_pdata->xbar_ctx->interrupt_stats.fhtx_c2c_overflow += 1;
	}
	if(xbar_sw_irq_status.c2ctx_fh_overflow){
		xbar_sw_irq_clear.c2ctx_fh_overflow = 1;
		ecpriss_pdata->xbar_ctx->interrupt_stats.c2ctx_fh_overflow += 1;
	}
	if(xbar_sw_irq_status.octx_fh_overflow){
		xbar_sw_irq_clear.octx_fh_overflow = 1;
		ecpriss_pdata->xbar_ctx->interrupt_stats.octx_fh_overflow += 1;
	}
	if(xbar_sw_irq_status.octx_c2c_overflow){
		xbar_sw_irq_clear.octx_c2c_overflow = 1;
		ecpriss_pdata->xbar_ctx->interrupt_stats.octx_c2c_overflow += 1;
	}
	if(xbar_sw_irq_status.fhrx_uc_pkt_pending){
		xbar_sw_irq_clear.fhrx_uc_pkt_pending = 1;
		ecpriss_pdata->xbar_ctx->interrupt_stats.fhrx_uc_pkt_pending += 1;
	}
	if(xbar_sw_irq_status.fhrx_uc_overflow){
		xbar_sw_irq_clear.fhrx_uc_overflow = 1;
		ecpriss_pdata->xbar_ctx->interrupt_stats.fhrx_uc_overflow += 1;
	}
	if(xbar_sw_irq_status.fhrx_uc_pkt_err){
		xbar_sw_irq_clear.octx_c2c_len_err = 1;
		ecpriss_pdata->xbar_ctx->interrupt_stats.fhrx_uc_pkt_err += 1;
	}
	if(xbar_sw_irq_status.fhrx_uc_pkt_drop){
		xbar_sw_irq_clear.fhrx_uc_pkt_drop = 1;
		ecpriss_pdata->xbar_ctx->interrupt_stats.fhrx_uc_pkt_drop += 1;
	}
	if(xbar_sw_irq_status.ocrx_unknown_pcid){
		xbar_sw_irq_clear.ocrx_unknown_pcid = 1;
		ecpriss_pdata->xbar_ctx->interrupt_stats.ocrx_unknown_pcid += 1;
	}
	if(xbar_sw_irq_status.fhrx_unknown_pcid){
		xbar_sw_irq_clear.fhrx_unknown_pcid = 1;
		ecpriss_pdata->xbar_ctx->interrupt_stats.fhrx_unknown_pcid += 1;
	}
	if(xbar_sw_irq_status.c2crx_unknown_pcid){
		xbar_sw_irq_clear.c2crx_unknown_pcid = 1;
		ecpriss_pdata->xbar_ctx->interrupt_stats.c2crx_unkown_pcid += 1;
	}
	ecpriss_xbar_hal_write_reg_n_fields(ECPRISS_XBAR_GLOBAL,
			ECPRI_XBAR_XBAR_SW_IRQ_CLR , 0, &xbar_sw_irq_clear);
	spin_unlock_irqrestore(&ecpriss_pdata->irq_lock, flags);
	return IRQ_HANDLED;
}


static irqreturn_t ecpriss_xbar_isr_v2(int irq, void *ctxt)
{
	unsigned long flags = 0;
	ecpri_xbar_hwio_def_ecpri_xbar_sw_irq_status_s xbar_sw_irq_status;
	ecpri_xbar_hwio_def_ecpri_xbar_sw_irq_clr_s xbar_sw_irq_clear;

	spin_lock_irqsave(&ecpriss_pdata_v2->irq_lock, flags);

	ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL,
			ECPRI_XBAR_SW_IRQ_STATUS, 0,&xbar_sw_irq_status);

	if(xbar_sw_irq_status.octx_fh_len_err){
		xbar_sw_irq_clear.octx_fh_len_err = 1;
		ecpriss_pdata_v2->xbar_ctx_v2->interrupt_stats_v2.octx_fh_len_err += 1;
	}
	if(xbar_sw_irq_status.octx_c2c_len_err){
		xbar_sw_irq_clear.octx_c2c_len_err = 1;
		ecpriss_pdata_v2->xbar_ctx_v2->interrupt_stats_v2.octx_c2c_len_err += 1;
	}
	if(xbar_sw_irq_status.fhtx_c2c_overflow){
		xbar_sw_irq_clear.fhtx_c2c_overflow = 1;
		ecpriss_pdata_v2->xbar_ctx_v2->interrupt_stats_v2.fhtx_c2c_overflow += 1;
	}
	if(xbar_sw_irq_status.c2ctx_fh_overflow){
		xbar_sw_irq_clear.c2ctx_fh_overflow = 1;
		ecpriss_pdata_v2->xbar_ctx_v2->interrupt_stats_v2.c2ctx_fh_overflow += 1;
	}
	if(xbar_sw_irq_status.octx_fh_overflow){
		xbar_sw_irq_clear.octx_fh_overflow = 1;
		ecpriss_pdata_v2->xbar_ctx_v2->interrupt_stats_v2.octx_fh_overflow += 1;
	}
	if(xbar_sw_irq_status.octx_c2c_overflow){
		xbar_sw_irq_clear.octx_c2c_overflow = 1;
		ecpriss_pdata_v2->xbar_ctx_v2->interrupt_stats_v2.octx_c2c_overflow += 1;
	}
	if(xbar_sw_irq_status.fhrx_uc_pkt_pending){
		xbar_sw_irq_clear.fhrx_uc_pkt_pending = 1;
		ecpriss_pdata_v2->xbar_ctx_v2->interrupt_stats_v2.fhrx_uc_pkt_pending += 1;
	}
	if(xbar_sw_irq_status.fhrx_uc_overflow){
		xbar_sw_irq_clear.fhrx_uc_overflow = 1;
		ecpriss_pdata_v2->xbar_ctx_v2->interrupt_stats_v2.fhrx_uc_overflow += 1;
	}
	if(xbar_sw_irq_status.fhrx_uc_pkt_drop){
		xbar_sw_irq_clear.fhrx_uc_pkt_drop = 1;
		ecpriss_pdata_v2->xbar_ctx_v2->interrupt_stats_v2.fhrx_uc_pkt_drop += 1;
	}
	if(xbar_sw_irq_status.ocrx_unknown_pcid){
		xbar_sw_irq_clear.ocrx_unknown_pcid = 1;
		ecpriss_pdata_v2->xbar_ctx_v2->interrupt_stats_v2.ocrx_unknown_pcid += 1;
	}
	if(xbar_sw_irq_status.fhrx_unknown_pcid){
		xbar_sw_irq_clear.fhrx_unknown_pcid = 1;
		ecpriss_pdata_v2->xbar_ctx_v2->interrupt_stats_v2.fhrx_unknown_pcid += 1;
	}
	if(xbar_sw_irq_status.c2crx_unknown_pcid){
		xbar_sw_irq_clear.c2crx_unknown_pcid = 1;
		ecpriss_pdata_v2->xbar_ctx_v2->interrupt_stats_v2.c2crx_unkown_pcid += 1;
	}
	ecpriss_xbar_hal_write_reg_n_fields(ECPRISS_XBAR_GLOBAL,
			ECPRI_XBAR_SW_IRQ_CLR , 0, &xbar_sw_irq_clear);
	spin_unlock_irqrestore(&ecpriss_pdata_v2->irq_lock, flags);
	return IRQ_HANDLED;
}


/**
 * ecpriss_xbar_register_interrupts()
 *
 *
 * Returns:	0 on success, negative on failure
 */
static int ecpriss_xbar_register_interrupts(struct device *dev)
{
	int res = 0;
	int xbar_irq_mapping = 0;
	struct platform_device *pdev = NULL;

	do{
		pdev = to_platform_device(dev);

		if(dev ==  NULL){
			ECPRILOGERR("ecpriss_xbar_irq_init pdev is NULL" );
			goto err;
		}
		xbar_irq_mapping =  platform_get_irq(pdev, EXPRISS_XBAR_INDEX);
		res = request_irq(xbar_irq_mapping, ecpriss_xbar_isr,
				IRQF_TRIGGER_HIGH, "ecpri_ss", NULL);
		if (res){
			ECPRILOGERR("IRQ request failed irq=%d res=%d\n",
					xbar_irq_mapping, res);
			goto err;
		}
		res = enable_irq_wake(xbar_irq_mapping);
		if (res){
			ECPRILOGERR("fail to enable IPA IRQ wakeup irq=%d res=%d\n",
					xbar_irq_mapping, res);
			goto err;
		}
		ECPRILOGINFO("XBAR interrupt id %d registered with ecpriss_irq_init Interrupt Registration Success\n",xbar_irq_mapping);
	}while(0);

	return 0;
err:
	return -1;
	return 0;
}
static int ecpriss_xbar_register_interrupts_v2(struct device *dev)
{
	int res = 0;
	int xbar_irq_mapping = 0;
	struct platform_device *pdev = NULL;

	do{
		pdev = to_platform_device(dev);

		if(dev ==  NULL){
			ECPRILOGERR("ecpriss_xbar_irq_init pdev is NULL" );
			goto err;
		}
		xbar_irq_mapping =  platform_get_irq(pdev, EXPRISS_XBAR_INDEX);
		res = request_irq(xbar_irq_mapping, ecpriss_xbar_isr_v2,
				IRQF_TRIGGER_RISING, "ecpri_ss", NULL);
		if (res){
			ECPRILOGERR("IRQ request failed irq=%d res=%d\n",
					xbar_irq_mapping, res);
			goto err;
		}
		res = enable_irq_wake(xbar_irq_mapping);
		if (res){
			ECPRILOGERR("fail to enable IPA IRQ wakeup irq=%d res=%d\n",
					xbar_irq_mapping, res);
			goto err;
		}
		ECPRILOGINFO("XBAR interrupt id %d registered with ecpriss_irq_init Interrupt Registration Success \n",
				xbar_irq_mapping);

	}while(0);

	return 0;
err:
	return -1;
	return 0;
}



/**
 * ecpriss_xbar_enable_stats()
 *
 *
 * Returns:	0 on success, negative on failure
 */
static void ecpriss_xbar_enable_stats(void)
{

	ecpri_xbar_hwio_def_ecpri_xbar_xbar_cfg_s xbar_cfg;
	int *cfg_val;

	memset(&xbar_cfg,0,sizeof(ecpri_xbar_hwio_def_ecpri_xbar_xbar_cfg_s));

	/*Read Reset value*/
	ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL, ECPRI_XBAR_XBAR_CFG,0, &xbar_cfg);
	cfg_val = (int*)(&xbar_cfg);
	ECPRILOGINFO("Reset xbar cfg val = 0x%04x\n", *cfg_val);


	xbar_cfg.fhrx_cnt_en = ENABLE_BIT;
	xbar_cfg.fhtx_cnt_en = ENABLE_BIT;
	xbar_cfg.ocrx_cnt_en = ENABLE_BIT;
	xbar_cfg.octx_cnt_en = ENABLE_BIT;
	xbar_cfg.c2crx_cnt_en = ENABLE_BIT;
	xbar_cfg.c2ctx_cnt_en = ENABLE_BIT;
	xbar_cfg.xbar_cnt_en = ENABLE_BIT;
	xbar_cfg.xbar_cnt_clr_en = ENABLE_BIT;
	xbar_cfg.tpdm_en = ENABLE_BIT;
	xbar_cfg.axis_arb_fix_en = ENABLE_BIT;

	ecpriss_xbar_hal_write_reg_n_fields(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_CFG,
			0,
			&xbar_cfg);

	/*Read post write value*/
	ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL, ECPRI_XBAR_XBAR_CFG,0, &xbar_cfg);
	cfg_val = (int*)(&xbar_cfg);
	ECPRILOGINFO("xbar cfg val post write= 0x%x\n", *cfg_val);
	return;
}


static void ecpriss_xbar_enable_stats_v2(void)
{

	ecpri_xbar_hwio_def_ecpri_xbar_cfg_s xbar_cfg;
	int *cfg_val;

	memset(&xbar_cfg,0,sizeof(ecpri_xbar_hwio_def_ecpri_xbar_cfg_s));

	/*Read Reset value*/
	ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL, ECPRI_XBAR_CFG,0, &xbar_cfg);
	cfg_val = (int*)(&xbar_cfg);
	ECPRILOGINFO("Reset xbar cfg val = 0x%04x\n", *cfg_val);


	xbar_cfg.fhrx_cnt_en = ENABLE_BIT;
	xbar_cfg.fhtx_cnt_en = ENABLE_BIT;
	xbar_cfg.ocrx_cnt_en = ENABLE_BIT;
	xbar_cfg.octx_cnt_en = ENABLE_BIT;
	xbar_cfg.c2crx_cnt_en = ENABLE_BIT;
	xbar_cfg.c2ctx_cnt_en = ENABLE_BIT;
	xbar_cfg.xbar_cnt_en = ENABLE_BIT;
	xbar_cfg.xbar_cnt_clr_en = ENABLE_BIT;
	xbar_cfg.tpdm_en = ENABLE_BIT;
	xbar_cfg.axis_arb_fix_en = ENABLE_BIT;

	ecpriss_xbar_hal_write_reg_n_fields(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_CFG,
			0,
			&xbar_cfg);

	/*Read post write value*/
	ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL, ECPRI_XBAR_CFG,0, &xbar_cfg);
	cfg_val = (int*)(&xbar_cfg);
	ECPRILOGINFO("xbar cfg val post write= 0x%x\n", *cfg_val);
	return;
}
/**
 * ecpriss_xbar_c2c_msg_lut_0_init()
 *
 *
 * Returns:	0 on success, negative on failure
 */
void ecpriss_xbar_c2c_msg_lut_0_init(void)
{
	ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2crx_msg_type_lut_0_s xbar_c2crx_msg_type_lut_0;
	memset(&xbar_c2crx_msg_type_lut_0,0,sizeof(ecpri_xbar_hwio_def_ecpri_xbar_xbar_c2crx_msg_type_lut_0_s));
	ecpriss_xbar_hal_write_reg_n_fields(ECPRISS_XBAR_LUT,
			ECPRI_XBAR_XBAR_C2CRX_MSG_TYPE_LUT_0,
			0,
			&xbar_c2crx_msg_type_lut_0);
	return;
}


/**
 * ecpriss_xbar_non_ecpri_lut_cfg()
 *
 *
 * Returns:	0 on success, negative on failure
 */
void ecpriss_xbar_non_ecpri_lut_cfg(void)
{
	int i,j;

	for(i=0;i<ECPRISS_PORT_MAX;i++)
	{
		struct ecpri_dma_port_params   *dma_port_cfg= &ecpriss_pdata->xbar_ctx->fh_port_cfg.dma_port_cfg[i];
		if(dma_port_cfg->port_index == ECPRISS_PORT_0)
		{

			ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_0_non_ecpri_lut_s xbar_fhrx_0_non_ecpri_lut;
			memset(&xbar_fhrx_0_non_ecpri_lut,0,sizeof(ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_0_non_ecpri_lut_s));

			for(j=0;j<dma_port_cfg->num_of_rings;j++)
			{
				if(dma_port_cfg->dma_rings_param[j].dma_ring_type == ECPRI_DMA_RING_TYPE_FH_DEFAULT)
				{
					switch(j)
					{
						case 0:
							xbar_fhrx_0_non_ecpri_lut.ring_id_0 = dma_port_cfg->dma_rings_param[0].dest_dma_ring_id;
							break;
						case 1:
							xbar_fhrx_0_non_ecpri_lut.ring_id_1 = dma_port_cfg->dma_rings_param[1].dest_dma_ring_id;
							break;
						case 2:
							xbar_fhrx_0_non_ecpri_lut.ring_id_2 = dma_port_cfg->dma_rings_param[2].dest_dma_ring_id;
							break;
						case 3:
							xbar_fhrx_0_non_ecpri_lut.ring_id_3 = dma_port_cfg->dma_rings_param[3].dest_dma_ring_id;
							break;
						default:
							ECPRILOGERR("Wrong default value %d\n",j);
							break;
					}
				}
			}



			ecpriss_xbar_hal_write_reg_n_fields(ECPRISS_XBAR_GLOBAL,
					ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT,
					dma_port_cfg->port_index,
					&xbar_fhrx_0_non_ecpri_lut);

			memset(&xbar_fhrx_0_non_ecpri_lut,0,sizeof(ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_0_non_ecpri_lut_s));


			ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL,
					ECPRI_XBAR_XBAR_FHRX_0_NON_ECPRI_LUT,
					dma_port_cfg->port_index,
					&xbar_fhrx_0_non_ecpri_lut);


			ecpriss_pdata->xbar_ctx->def_lut_cfg_done[ECPRISS_PORT_0] = 1;

		}
		else if (dma_port_cfg->port_index == ECPRISS_PORT_1)
		{

			ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_1_non_ecpri_lut_s xbar_fhrx_1_non_ecpri_lut;
			memset(&xbar_fhrx_1_non_ecpri_lut,0,sizeof(ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_1_non_ecpri_lut_s));

			for(j=0;j<dma_port_cfg->num_of_rings;j++)
			{
				if(dma_port_cfg->dma_rings_param[j].dma_ring_type == ECPRI_DMA_RING_TYPE_FH_DEFAULT)
				{
					switch(j)
					{
						case 0:
							xbar_fhrx_1_non_ecpri_lut.ring_id_0 = dma_port_cfg->dma_rings_param[0].dest_dma_ring_id;
							break;
						case 1:
							xbar_fhrx_1_non_ecpri_lut.ring_id_1 = dma_port_cfg->dma_rings_param[1].dest_dma_ring_id;
							break;
						case 2:
							xbar_fhrx_1_non_ecpri_lut.ring_id_2 = dma_port_cfg->dma_rings_param[2].dest_dma_ring_id;
							break;
						case 3:
							xbar_fhrx_1_non_ecpri_lut.ring_id_3 = dma_port_cfg->dma_rings_param[3].dest_dma_ring_id;
							break;
						default:
							ECPRILOGERR("Wrong default value %d\n",j);
							break;
					}
				}
			}

			ecpriss_xbar_hal_write_reg_n_fields(ECPRISS_XBAR_GLOBAL,
					ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT,
					dma_port_cfg->port_index,
					&xbar_fhrx_1_non_ecpri_lut);

			memset(&xbar_fhrx_1_non_ecpri_lut,0,
					sizeof(ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_1_non_ecpri_lut_s));

			ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL,
					ECPRI_XBAR_XBAR_FHRX_1_NON_ECPRI_LUT,
					dma_port_cfg->port_index,
					&xbar_fhrx_1_non_ecpri_lut);

			ecpriss_pdata->xbar_ctx->def_lut_cfg_done[ECPRISS_PORT_1] = 1;


		}
		else if (dma_port_cfg->port_index == ECPRISS_PORT_2)
		{
			ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_2_non_ecpri_lut_s xbar_fhrx_2_non_ecpri_lut;
			memset(&xbar_fhrx_2_non_ecpri_lut,0,sizeof(ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_2_non_ecpri_lut_s));

			for(j=0;j<dma_port_cfg->num_of_rings;j++)
			{
				if(dma_port_cfg->dma_rings_param[j].dma_ring_type == ECPRI_DMA_RING_TYPE_FH_DEFAULT)
				{
					switch(j)
					{
						case 0:
							xbar_fhrx_2_non_ecpri_lut.ring_id_0 = dma_port_cfg->dma_rings_param[0].dest_dma_ring_id;
							break;
						case 1:
							xbar_fhrx_2_non_ecpri_lut.ring_id_1 = dma_port_cfg->dma_rings_param[1].dest_dma_ring_id;
							break;
						case 2:
							xbar_fhrx_2_non_ecpri_lut.ring_id_2 = dma_port_cfg->dma_rings_param[2].dest_dma_ring_id;
							break;
						case 3:
							xbar_fhrx_2_non_ecpri_lut.ring_id_3 = dma_port_cfg->dma_rings_param[3].dest_dma_ring_id;
							break;
						default:
							ECPRILOGERR("Wrong default value j = %d\n",j);
							break;
					}
				}
			}

			ecpriss_xbar_hal_write_reg_n_fields(ECPRISS_XBAR_GLOBAL,
					ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT,
					dma_port_cfg->port_index,
					&xbar_fhrx_2_non_ecpri_lut);

			memset(&xbar_fhrx_2_non_ecpri_lut,0,
					sizeof(ecpri_xbar_hwio_def_ecpri_xbar_xbar_fhrx_2_non_ecpri_lut_s));


			ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL,
					ECPRI_XBAR_XBAR_FHRX_2_NON_ECPRI_LUT,
					dma_port_cfg->port_index,
					&xbar_fhrx_2_non_ecpri_lut);

			ecpriss_pdata->xbar_ctx->def_lut_cfg_done[ECPRISS_PORT_2] = 1;

		}
	}
	return;
}

/**
 * ecpriss_xbar_init()
 *
 *
 * Returns:	0 on success, negative on failure
 */
int ecpriss_xbar_cold_init(struct device *dev)
{
	int ret = 0;
	do{

		ret = ecpriss_xbar_hal_reg_init(dev,
			(ecpriss_xbar_hw_name_e)ecpriss_pdata->ecpri_hw_ver);
		if(ret < 0)
		{
			break;
		}

		ret = ecpriss_xbar_hal_lut_reg_init(dev);
		if(ret < 0)
		{
			break;
		}

		ret = ecpriss_xbar_check_entry_valid_bits(); //Implement this
		if(ret < 0)
		{
			break;
		}
#if 0
		ecpriss_xbar_flush_init();
#endif
		ret = ecpriss_xbar_register_interrupts(dev);
		if(ret < 0)
		{
			break;
		}

		ecpriss_xbar_enable_stats();
		ecpriss_xbar_flush_init();
		if(ecpriss_pdata)
		{
			if(ecpriss_pdata->xbar_ctx)
			{
				ecpriss_pdata->xbar_ctx->state = ECPRI_XBAR_COLD_INIT ;
			}
			else
			{
				ECPRILOGERR("xbar ctxt is NULL\n");
			}
		}


	}while (0);

	return ret;
}
int ecpriss_xbar_cold_init_v2(struct device *dev)
{
	int ret = 0;
	do{

		ret = ecpriss_xbar_hal_reg_init(dev,
			(ecpriss_xbar_hw_name_e)ecpriss_pdata_v2->ecpri_hw_ver);
		if(ret < 0)
		{
			break;
		}

		ret = ecpriss_xbar_hal_lut_reg_init(dev);
		if(ret < 0)
		{
			break;
		}

		ret = ecpriss_xbar_check_entry_valid_bits_v2(); //Implement this
		if(ret < 0)
		{
			break;
		}
#if 0
		ecpriss_xbar_flush_init_v2();
#endif
		ret = ecpriss_xbar_register_interrupts_v2(dev);
		if(ret < 0)
		{
			break;
		}

		ecpriss_xbar_enable_stats_v2();

		if(ecpriss_pdata)
		{
			if(ecpriss_pdata_v2->xbar_ctx_v2)
			{
				ecpriss_pdata_v2->xbar_ctx_v2->state = ECPRI_XBAR_COLD_INIT ;
			}
			else
			{
				ECPRILOGERR("xbar ctxt is NULL\n");
			}
		}


	}while (0);

	return ret;
}


/**
 * ecpriss_xbar_fh_rx_lut()
 *
 * args - Devmode and xbar_rx_cfg struct
 *
 * Description - Used to configure the FH RX LUT
 *
 *  Configuring the register : XBAR_FHRX_m_LUT_n (Assumption :
 *  Each function call is configuring one entry)
 *
 *  1. Find the port index and number of entries
 *  		a. Maintain the number of entries in the XBAR context
 *  		b. How to get port index ? --> part of flow config
 *  		packet?
 *
 * 2. Configure DMA ring ID --> should be already available once
 * port index is identified (Is this required ? As there is
 * another register for the same: XBAR_FHRX_x_NON_ECPRI_LUT  )
 *		NULL
 *
 *    3. OC link id
 *  	part of the xbar_rx_cfg
 *
 *		4. Route_to_oran --> 1
 *
 *		5. Route_to_c2c -->  0
 *
 *		6. Route_to_dma --> 0
 *
 *		7. Valid --> Set to 1
 *
 * Returns:	0 on success, negative on failure
 */
int ecpriss_xbar_fh_rx_lut(uint32_t  port_index,
		ecpriss_flow_rx_cfg_s *xbar_rx_cfg)
{
	int	current_pcid_index;
	int ret=0;
	ecpri_xbar_hwio_def_ecpri_xbar_lut_xbar_fhrx_m_lut_n_s xbar_fhrx_m_lut_n;
	ecpriss_xbar_port_lut_s *xbar_port_lut = NULL;
	current_pcid_index = 0;
	do{
		if(xbar_rx_cfg == NULL) {
			ret = -ENOMEM;
			break;
		}
		memset(&xbar_fhrx_m_lut_n,
				0,
				sizeof(xbar_fhrx_m_lut_n));
		xbar_port_lut = &ecpriss_pdata->xbar_ctx->flow_ctx.fh_xbar_lut[port_index];

		current_pcid_index = xbar_rx_cfg->xbar_rx_cfg.flow_id;
		xbar_port_lut->lut_table[current_pcid_index].pcid = xbar_rx_cfg->xbar_rx_cfg.flow_id;
		xbar_port_lut->lut_table[current_pcid_index].oc_link_id = xbar_rx_cfg->xbar_rx_cfg.oc_link_id;
		xbar_fhrx_m_lut_n.oc_link_id = xbar_rx_cfg->xbar_rx_cfg.oc_link_id;
		xbar_port_lut->lut_table[current_pcid_index].route_to_oran = 1;
		xbar_fhrx_m_lut_n.route_to_oran = 1;
		xbar_port_lut->lut_table[current_pcid_index].valid = 1;
		xbar_fhrx_m_lut_n.valid = 1;

		ECPRILOGDBG("ecpriss_xbar_fh_rx_lut: PICD %d OC LInk ID %d and Valid %d Route to Oran %d",
				current_pcid_index, xbar_fhrx_m_lut_n.oc_link_id , xbar_fhrx_m_lut_n.valid , xbar_fhrx_m_lut_n.route_to_oran);

		ecpriss_xbar_hal_write_reg_mn_fields(ECPRISS_XBAR_LUT,
				ECPRI_XBAR_LUT_XBAR_FHRX_m_LUT_n,
				port_index,
				current_pcid_index,
				&xbar_fhrx_m_lut_n);
	}while (0);
	return ret;
}


int ecpriss_xbar_fh_rx_lut_v2(uint32_t  port_index,
		ecpriss_flow_rx_cfg_s *xbar_rx_cfg)
{
	int current_pcid_index;
	int ret = 0;
	ecpri_xbar_hwio_def_ecpri_xbar_fhrx_m_lut_n_s xbar_fhrx_m_lut_n;
	ecpriss_xbar_port_lut_s_v2 *xbar_port_lut = NULL;
	current_pcid_index = 0;
	do{
		if(xbar_rx_cfg == NULL) {
			ret = -ENOMEM;
			break;
		}
		memset(&xbar_fhrx_m_lut_n,
				0,
				sizeof(xbar_fhrx_m_lut_n));

		ecpriss_xbar_hal_read_reg_mn_fields(ECPRISS_XBAR_LUT,
				ECPRI_XBAR_LUT_XBAR_FHRX_m_LUT_n_V2,
				port_index,
				current_pcid_index,
				&xbar_fhrx_m_lut_n);


		current_pcid_index = xbar_rx_cfg->xbar_rx_cfg.flow_id;
		xbar_port_lut = &ecpriss_pdata_v2->xbar_ctx_v2->flow_ctx_v2.fh_xbar_lut[port_index];
		xbar_port_lut->lut_table[current_pcid_index].pcid = xbar_rx_cfg->xbar_rx_cfg.flow_id;

		if(xbar_rx_cfg->xbar_rx_cfg.flow_dir == ECPRISS_FLOW_DIR_UL){

			xbar_fhrx_m_lut_n.ul_oc_link_id |=
				xbar_rx_cfg->xbar_rx_cfg.oc_link_id;
			xbar_fhrx_m_lut_n.ul_route_to_oran |= 1;

			xbar_port_lut->lut_table[current_pcid_index].ul_oc_link_id =
				xbar_rx_cfg->xbar_rx_cfg.oc_link_id;

			xbar_port_lut->lut_table[current_pcid_index].ul_route_to_oran = 1;

			ECPRILOGERR("ecpriss_xbar_fh_rx_lut: PCID %d OC LInk ID %d Route UL Oran %d",
					current_pcid_index, xbar_fhrx_m_lut_n.ul_oc_link_id , xbar_fhrx_m_lut_n.ul_route_to_oran);

		}else {
			xbar_fhrx_m_lut_n.dl_oc_link_id |=
				xbar_rx_cfg->xbar_rx_cfg.oc_link_id;
			xbar_fhrx_m_lut_n.dl_route_to_oran |= 1;

			xbar_port_lut->lut_table[current_pcid_index].dl_oc_link_id =
				xbar_rx_cfg->xbar_rx_cfg.oc_link_id;
			xbar_port_lut->lut_table[current_pcid_index].dl_route_to_oran = 1;

			ECPRILOGERR("ecpriss_xbar_fh_rx_lut: PCID %d OC LInk ID %d Route DL Oran %d",
					current_pcid_index, xbar_fhrx_m_lut_n.dl_oc_link_id , xbar_fhrx_m_lut_n.dl_route_to_oran);

		}

		ecpriss_xbar_hal_write_reg_mn_fields(ECPRISS_XBAR_LUT,
				ECPRI_XBAR_LUT_XBAR_FHRX_m_LUT_n_V2,
				port_index,
				current_pcid_index,
				&xbar_fhrx_m_lut_n);

	}while (0);
	return ret;
}



/**
 * ecpriss_xbar_oc_rx_lut
 *
 * Description -
 *
 * Port index required and maintain the next table entry
 *
 * 1. L2_ENCAP_INFO --> Table index for	QUDP L2 encapsulation
 * (Available in xbar_tx_cfg)
 *
 * 2. L3_ENCAP_INFO --> Table index for QUDP L3 encap info
 *(Available in xbar_tx_cfg)
 *
 * 3. L3_ENCAPSULATION_VALID --> Set it to valid if required
 *(Available in xbar_tx_cfg)
 *
 * 4. Entry valid
 *(Available in xbar_tx_cfg)
 *
 * Returns:	0 on success, negative on failure
 */
int ecpriss_xbar_oc_rx_lut(uint32_t               port_index,
		ecpriss_flow_tx_cfg_s *xbar_tx_cfg)
{
	int	current_pcid_index;
	ecpriss_xbar_oc_rx_port_lut_s *ocrx_xbar_port_lut = NULL;
	int ret = 0;
	ecpri_xbar_hwio_def_ecpri_xbar_lut_xbar_ocrx_m_lut_n_s xbar_ocrx_m_lut_n ;
	do{
		if(xbar_tx_cfg == NULL) {
			ret = -ENOMEM;
			break;
		}

		memset(&xbar_ocrx_m_lut_n,
				0,
				sizeof(xbar_ocrx_m_lut_n));

		ocrx_xbar_port_lut = &ecpriss_pdata->xbar_ctx->flow_ctx.oc_rx_xbar_lut[port_index];

		current_pcid_index = xbar_tx_cfg->xbar_tx_cfg.pcid;

		ocrx_xbar_port_lut->lut_table[current_pcid_index].pcid = xbar_tx_cfg->xbar_tx_cfg.pcid;
		ocrx_xbar_port_lut->lut_table[current_pcid_index].l2_encap_info = xbar_tx_cfg->xbar_tx_cfg.l2_hdr_tbl_idx;
		xbar_ocrx_m_lut_n.l2_encap_info = xbar_tx_cfg->xbar_tx_cfg.l2_hdr_tbl_idx;

		ocrx_xbar_port_lut->lut_table[current_pcid_index].l3_encap_info = xbar_tx_cfg->xbar_tx_cfg.l3_hdr_tbl_idx;
		xbar_ocrx_m_lut_n.l3_encap_info = xbar_tx_cfg->xbar_tx_cfg.l3_hdr_tbl_idx;

		ocrx_xbar_port_lut->lut_table[current_pcid_index].l3_encap_valid = xbar_tx_cfg->xbar_tx_cfg.l3_hdr_valid;
		xbar_ocrx_m_lut_n.l3_encap_valid = xbar_tx_cfg->xbar_tx_cfg.l3_hdr_valid;

		xbar_ocrx_m_lut_n.valid = 1;
		ocrx_xbar_port_lut->lut_table[current_pcid_index].valid = 1;

		ECPRILOGDBG("ecpriss_xbar_oc_rx_lut: PCID %d L2 Index %d L3 Index  and Valid " , ocrx_xbar_port_lut->lut_table[current_pcid_index].pcid,
				xbar_ocrx_m_lut_n.l2_encap_info , xbar_ocrx_m_lut_n.l3_encap_info , xbar_ocrx_m_lut_n.valid );
		ecpriss_xbar_hal_write_reg_mn_fields(ECPRISS_XBAR_LUT,
				ECPRI_XBAR_LUT_XBAR_OCRX_m_LUT_n,
				port_index,
				current_pcid_index,
				&xbar_ocrx_m_lut_n);
	}while (0);
	return ret;
}

int ecpriss_xbar_oc_rx_lut_v2(uint32_t               port_index,
		ecpriss_flow_tx_cfg_s *xbar_tx_cfg)
{
	int     current_pcid_index;
	ecpriss_xbar_oc_rx_port_lut_s *ocrx_xbar_port_lut = NULL;
	int ret = 0;
	ecpri_xbar_hwio_def_ecpri_xbar_ocrx_m_lut_n_s xbar_ocrx_m_lut_n ;
	do{
		if(xbar_tx_cfg == NULL) {
			ret = -ENOMEM;
			break;
		}

		memset(&xbar_ocrx_m_lut_n,
				0,
				sizeof(xbar_ocrx_m_lut_n));

		ocrx_xbar_port_lut = &ecpriss_pdata_v2->xbar_ctx_v2->flow_ctx_v2.oc_rx_xbar_lut[port_index];

		current_pcid_index = xbar_tx_cfg->xbar_tx_cfg.pcid;

		ocrx_xbar_port_lut->lut_table[current_pcid_index].pcid = xbar_tx_cfg->xbar_tx_cfg.pcid;
		ocrx_xbar_port_lut->lut_table[current_pcid_index].l2_encap_info = xbar_tx_cfg->xbar_tx_cfg.l2_hdr_tbl_idx;
		xbar_ocrx_m_lut_n.l2_encap_info = xbar_tx_cfg->xbar_tx_cfg.l2_hdr_tbl_idx;

		ocrx_xbar_port_lut->lut_table[current_pcid_index].l3_encap_info = xbar_tx_cfg->xbar_tx_cfg.l3_hdr_tbl_idx;
		xbar_ocrx_m_lut_n.l3_encap_info = xbar_tx_cfg->xbar_tx_cfg.l3_hdr_tbl_idx;

		ocrx_xbar_port_lut->lut_table[current_pcid_index].l3_encap_valid = xbar_tx_cfg->xbar_tx_cfg.l3_hdr_valid;
		xbar_ocrx_m_lut_n.l3_encap_valid = xbar_tx_cfg->xbar_tx_cfg.l3_hdr_valid;

		xbar_ocrx_m_lut_n.valid = 1;
		ocrx_xbar_port_lut->lut_table[current_pcid_index].valid = 1;
		ECPRILOGERR("ecpriss_xbar_oc_rx_lut: PCID %d L2 Index %d L3 Index  and Valid " , ocrx_xbar_port_lut->lut_table[current_pcid_index].pcid,
				xbar_ocrx_m_lut_n.l2_encap_info , xbar_ocrx_m_lut_n.l3_encap_info , xbar_ocrx_m_lut_n.valid );
	
		ecpriss_xbar_hal_write_reg_mn_fields(ECPRISS_XBAR_LUT,
				ECPRI_XBAR_LUT_XBAR_OCRX_m_LUT_n_V2,
				port_index,
				current_pcid_index,
				&xbar_ocrx_m_lut_n);
	}while (0);
	return ret;
}

/**
 * ecpriss_xbar_c2c_lut()
 *
 *
 * Returns:	0 on success, negative on failure
 */
int ecpriss_xbar_c2c_lut(void)
{
	return 0;
}

/**
 * ecpriss_xbar_l2_lut()
 *
 *
 * Returns:	0 on success, negative on failure
 */
int ecpriss_xbar_l2_lut(void)
{
	return 0;
}
