/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include "ecpriss_core.h"

#define ECPRISS_PORT_OC_3 3
#define ENABLE_BIT 1
#define DISABLE_BIT 0




void ecpriss_xbar_print_stats(void)
{
	uint32_t val=0;
	int link_index;
	for(link_index=0;link_index<TOTAL_LINKS;link_index++) {
		val = ecpriss_xbar_hal_read_reg_n(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_FHRX_PKT_CNT_n,link_index);
		ecpriss_pdata->xbar_ctx->stats.xbar_fhrx_pkt_cnt[link_index] = val;
		pr_info("ECPRI_XBAR_XBAR_DBG_FHRX_PKT_CNT_n val = %d link_index = %d\n",val,link_index);

		val = ecpriss_xbar_hal_read_reg_n(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_FHTX_PKT_CNT_n,link_index);
		pr_info("ECPRI_XBAR_XBAR_DBG_FHTX_PKT_CNT_n val = %d link_index = %d\n",val,link_index);
		ecpriss_pdata->xbar_ctx->stats.xbar_fhtx_pkt_cnt[link_index] = val;

		val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_C2CRX_PKT_CNT_n);
		pr_info("ECPRI_XBAR_XBAR_DBG_C2CRX_PKT_CNT_n val = %d link_index = %d\n",val,link_index);
		ecpriss_pdata->xbar_ctx->stats.xbar_c2crx_pkt_cnt[link_index] = val;

		val = ecpriss_xbar_hal_read_reg_n(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_C2CTX_PKT_CNT_n,link_index);
		pr_info("ECPRI_XBAR_XBAR_DBG_C2CTX_PKT_CNT_n val = %d link_index = %d\n",val,link_index);
		ecpriss_pdata->xbar_ctx->stats.xbar_c2ctx_pkt_cnt[link_index] = val;
	}


	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_FHRX_DMA_PKT_CNT);
	pr_info("ECPRI_XBAR_XBAR_DBG_FHRX_DMA_PKT_CNT val = %d\n",val);
	ecpriss_pdata->xbar_ctx->stats.xbar_fhrx_dma_pkt_cnt = val;

	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_FHRX_UC_PKT_CNT);
	pr_info("ECPRI_XBAR_XBAR_DBG_FHRX_UC_PKT_CNT val = %d\n",val);
	ecpriss_pdata->xbar_ctx->stats.xbar_fhrx_uc_pkt_cnt = val;

	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_FHRX_UC_ERR_PKT_CNT);
	pr_info("ECPRI_XBAR_XBAR_DBG_FHRX_UC_ERR_PKT_CNT val = %d\n",val);
	ecpriss_pdata->xbar_ctx->stats.xbar_fhrx_uc_err_pkt_cnt = val;

	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_FHRX_ERR_PKT_CNT);
	pr_info("ECPRI_XBAR_XBAR_DBG_FHRX_ERR_PKT_CNT val = %d\n",val);
	ecpriss_pdata->xbar_ctx->stats.xbar_fhrx_err_pkt_cnt = val;



	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_FHTX_C2C_PKT_OVF_CNT);
	pr_info("ECPRI_XBAR_XBAR_DBG_FHTX_C2C_PKT_OVF_CNT val = %d\n",val);
	ecpriss_pdata->xbar_ctx->stats.xbar_fhtx_c2c_pkt_ovf_cnt = val;

	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_FHTX_DMA_PKT_CNT);
	pr_info("	ECPRI_XBAR_XBAR_DBG_FHTX_DMA_PKT_CNT val = %d\n",val);
	ecpriss_pdata->xbar_ctx->stats.xbar_fhtx_dma_pkt_cnt = val;


	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_C2CRX_DMA_PKT_CNT);
	pr_info("ECPRI_XBAR_XBAR_DBG_C2CRX_DMA_PKT_CNT val = %d\n",val);
	ecpriss_pdata->xbar_ctx->stats.xbar_c2crx_dma_pkt_cnt = val;

	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_C2CRX_ERR_PKT_CNT);
	pr_info("ECPRI_XBAR_XBAR_DBG_C2CRX_ERR_PKT_CNT val = %d\n",val);
	ecpriss_pdata->xbar_ctx->stats.xbar_c2crx_err_pkt_cnt = val;

	val = ecpriss_xbar_hal_read_reg(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_DBG_FHTX_UC_PKT_CNT);
	pr_info("ECPRI_XBAR_XBAR_DBG_FHTX_UC_PKT_CNT val = %d\n",val);
	ecpriss_pdata->xbar_ctx->stats.xbar_fhtx_uc_pkt_cnt = val;

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
			pr_info("ecpriss_xbar_check_entry_valid_bits(): XBAR HW LUT Inited\n");
		}
		else
		{
			pr_info("Init LUT done error\n");
			break;
		}
	}while (0);
	return ret;
}

#if 0
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
	xbar_flush.flush_fh_0_rx = ENABLE_BIT;
	xbar_flush.flush_fh_0_tx = ENABLE_BIT;
	xbar_flush.flush_fh_1_rx = ENABLE_BIT;
	xbar_flush.flush_fh_1_tx = ENABLE_BIT;
	xbar_flush.flush_fh_2_rx = ENABLE_BIT;
	xbar_flush.flush_fh_2_tx = ENABLE_BIT;

	xbar_flush.flush_c2c_0_rx = ENABLE_BIT;
	xbar_flush.flush_c2c_0_tx = ENABLE_BIT;
	xbar_flush.flush_c2c_1_rx = ENABLE_BIT;
	xbar_flush.flush_c2c_1_tx = ENABLE_BIT;
	xbar_flush.flush_c2c_2_rx = ENABLE_BIT;
	xbar_flush.flush_c2c_2_tx = ENABLE_BIT;

	xbar_flush.flush_oc_0_rx = ENABLE_BIT;
	xbar_flush.flush_oc_0_tx = ENABLE_BIT;
	xbar_flush.flush_oc_1_rx = ENABLE_BIT;
	xbar_flush.flush_oc_1_tx = ENABLE_BIT;
	xbar_flush.flush_oc_2_rx = ENABLE_BIT;
	xbar_flush.flush_oc_2_tx = ENABLE_BIT;
	xbar_flush.flush_oc_3_rx = ENABLE_BIT;
	xbar_flush.flush_oc_3_tx = ENABLE_BIT;

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

/**
 * ecpriss_xbar_register_interrupts()
 *
 *
 * Returns:	0 on success, negative on failure
 */
static int ecpriss_xbar_register_interrupts(void)
{
	//Check ipa_interrupts for reference
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
	pr_info("Reset xbar cfg val = 0x%04x\n", *cfg_val);


	xbar_cfg.fhrx_cnt_en = ENABLE_BIT;
	xbar_cfg.fhtx_cnt_en = ENABLE_BIT;
	xbar_cfg.ocrx_cnt_en = ENABLE_BIT;
	xbar_cfg.octx_cnt_en = ENABLE_BIT;
	xbar_cfg.c2crx_cnt_en = ENABLE_BIT;
	xbar_cfg.c2ctx_cnt_en = ENABLE_BIT;
	xbar_cfg.xbar_cnt_en = ENABLE_BIT;
	xbar_cfg.xbar_cnt_clr_en = DISABLE_BIT;
	xbar_cfg.tpdm_en = ENABLE_BIT;

	ecpriss_xbar_hal_write_reg_n_fields(ECPRISS_XBAR_GLOBAL,ECPRI_XBAR_XBAR_CFG,
			0,
			&xbar_cfg);

	/*Read post write value*/
	ecpriss_xbar_hal_read_reg_n_fields(ECPRISS_XBAR_GLOBAL, ECPRI_XBAR_XBAR_CFG,0, &xbar_cfg);
	cfg_val = (int*)(&xbar_cfg);
	pr_info("xbar cfg val post write= 0x%x\n", *cfg_val);
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
							pr_err("Wrong default value %d\n",j);
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
							pr_err("Wrong default value %d\n",j);
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
							pr_err("Wrong default value j = %d\n",j);
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

		ret = ecpriss_xbar_hal_reg_init(dev);
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
		ret = ecpriss_xbar_register_interrupts();
		if(ret < 0)
		{
			break;
		}

		ecpriss_xbar_enable_stats();

		if(ecpriss_pdata)
		{
			if(ecpriss_pdata->xbar_ctx)
			{
				ecpriss_pdata->xbar_ctx->state = ECPRI_XBAR_COLD_INIT ;
			}
			else
			{
				pr_err("xbar ctxt is NULL\n");
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

		pr_err("ecpriss_xbar_fh_rx_lut: PICD %d OC LInk ID %d and Valid %d Route to Oran %d",
				current_pcid_index, xbar_fhrx_m_lut_n.oc_link_id , xbar_fhrx_m_lut_n.valid , xbar_fhrx_m_lut_n.route_to_oran);

		ecpriss_xbar_hal_write_reg_mn_fields(ECPRISS_XBAR_LUT,
				ECPRI_XBAR_LUT_XBAR_FHRX_m_LUT_n,
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

		pr_err("ecpriss_xbar_oc_rx_lut: PCID %d L2 Index %d L3 Index  and Valid " , ocrx_xbar_port_lut->lut_table[current_pcid_index].pcid,
				xbar_ocrx_m_lut_n.l2_encap_info , xbar_ocrx_m_lut_n.l3_encap_info , xbar_ocrx_m_lut_n.valid );
		ecpriss_xbar_hal_write_reg_mn_fields(ECPRISS_XBAR_LUT,
				ECPRI_XBAR_LUT_XBAR_OCRX_m_LUT_n,
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
