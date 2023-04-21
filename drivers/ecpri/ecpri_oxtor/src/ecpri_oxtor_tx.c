/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include "ecpri_oxtor_core.h"
#include "ecpri_oxtor_tx.h"
#include "ecpri_oxtor_hal.h"

ecpri_oxtor_tx_ring_cntxt_s ecpri_oxtor_tx_ring_cnxt;


static int ecpri_oxtor_tx_ctor_cmd(ecpri_oxtor_core_tx_cmd_cfg_s *user_cmd,
		ecpri_oxtor_tx_ring_cmd_u *tx_cmd)
{
	tx_cmd->fields.pcid = user_cmd->flow_cfg.pcid;
	tx_cmd->fields.link_id = ECPRI_OXTOR_LINK_ID_GEN(
			user_cmd->flow_cfg.port_type,
			user_cmd->flow_cfg.port_idx,
			user_cmd->flow_cfg.link_idx);
	tx_cmd->fields.target_rx = user_cmd->flow_cfg.rx_oc_link_id;
	tx_cmd->fields.data_length = user_cmd->pkt_cfg.pkt_len;
	tx_cmd->fields.inter_pkt_delay = user_cmd->pkt_cfg.inter_pkt_delay;
	tx_cmd->fields.ecpri_msg_type = user_cmd->pkt_cfg.ecpri_msg_type;
	tx_cmd->fields.first_byte_prach_hdr = user_cmd->pkt_cfg.first_byte_prach_hdr;
	/* Set initData and xuId in oxtor cmd */
	tx_cmd->fields.init_data = user_cmd->pkt_cfg.init_data;
	tx_cmd->fields.xu_num = user_cmd->pkt_cfg.xu_id;

	return 0;
}

static int ecpri_oxtor_core_tx_ring_init()
{
	ecpri_oxtor_tx_ring_s *ring_ptr = NULL;
	u16 i;

	for (i = 0; i < ECPRI_OXTOR_TX_CHANNELS_MAX; ++i)
	{
		ring_ptr = &ecpri_oxtor_tx_ring_cnxt.ring_arr[i];
		memset(ring_ptr,0,sizeof(ecpri_oxtor_tx_ring_s));

		ring_ptr->ring_id = i;
		ring_ptr->initData = 0xCAFECAFE;
		ring_ptr->rd_idx = 0;
		ring_ptr->wr_idx = 0;
		ring_ptr->last_commit_idx = 0;
		ring_ptr->numValid = 0;

		/*Reset stats and status of tx ring */
		memset((void *)&ring_ptr->ring_stats, 0x0,
			sizeof(ecpri_oxtor_tx_ring_stats_s));
		memset((void *)&ring_ptr->ring_status, 0x0,
			sizeof(ecpri_oxtor_tx_ring_status_s));

	}

	ecpri_oxtor_tx_ring_cnxt.init = true;

	return 0;
}

int ecpri_oxtor_tx_init(void )
{
	ecpri_oxtor_core_tx_ring_init();

	return 0;
}
#ifdef UNUSED
static  ecpri_oxtor_tx_ring_cmd_u* ecprii_oxtor_tx_ring_find_next_cmd(
		u32 ring_id,  u32 *m_val)
{
	ecpri_oxtor_tx_ring_cmd_u *cmd_arr = NULL;
	ecpri_oxtor_tx_ring_s *ring_ptr =
		&ecpri_oxtor_tx_ring_cnxt.ring_arr[ring_id];

	cmd_arr = &ring_ptr->cmd_arr[ring_ptr->wr_idx];
	*m_val = ring_ptr->wr_idx;
	ring_ptr->wr_idx =
		((ring_ptr->wr_idx + 1) % ECPRI_OXTOR_MAX_TX_RING_ENTRIES);

	return cmd_arr;
}
#endif

int ecpri_oxtor_tx_ctl_reg_cfg(const ecpri_oxtor_tx_ring_config_s* cfg ,
		u32 ring_id)
{
	/* Config Tx ring specific initalization */
	ecpri_oxtor_tx_ring_s *ring_ptr = NULL;

	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_ctl_reg_s oxtor_cfg;
	memset (&oxtor_cfg, 0,
	sizeof(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_ctl_reg_s));
	/*
	 * TODO Mayank
	 *
	 * User must get the value of register,memset will zero all other fields
	 * ecpriss_oxtor_hal_read_reg_n_fields
	 */
	pr_info("<ecpri_oxtor_tx_ctl_reg_cfg> getting called \n");
	ring_ptr = &ecpri_oxtor_tx_ring_cnxt.ring_arr[ring_id];
	if (NULL == cfg)
	{
		pr_err("Invalid tx ring cfg");
		WARN_ON(1);
		return -EINVAL;

	}
	oxtor_cfg.wrap_en = cfg->run_mode;
	ecpriss_oxtor_hal_write_reg_n_fields(ECPRI_OXTOR_REG_TYPE_BASE,
			ECPRI_ORAN_XTOR_TX_n_CTL_REG,ring_id, &oxtor_cfg);

	/* Update the Tx ring ID with the Wrap EN settings */
	ring_ptr->ring_status.is_wrap_en = oxtor_cfg.wrap_en;

	return 0;
}
static int ecpri_oxtor_tx_stop(u32 ring_id, u32 timeout_ms)
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_data_idxs_reg_s
		data_idxs_reg_s;

	/* TODO: Mayank, need to take care of timer mechanism */
	/* VVDRV_ecpri_timer timer; */
	u32 curr_wr_idx;
	ecpri_oxtor_tx_ring_s *ring_ptr = NULL;

	ring_ptr= &ecpri_oxtor_tx_ring_cnxt.ring_arr[ring_id];

	ecpriss_oxtor_hal_read_reg_n_fields(ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG,
			ring_id, (void *)&data_idxs_reg_s);
	/* return success if ring already stopped for all running modes */
	if (data_idxs_reg_s.wr_idx == 0)
	{
		return 0;
	}
	else
	{
		curr_wr_idx = data_idxs_reg_s.wr_idx;
	}
	/* will be update only if current WR_IDX is not equal 0 */
	ring_ptr->PostedIdxBeforeStop = data_idxs_reg_s.wr_idx;

	/* In wrapping mode stop the oxtor ring by writing 0 to write index */
	if (ring_ptr->ring_status.is_wrap_en == ECPRI_OXTOR_RING_MODE_WRAPPING)
	{
		data_idxs_reg_s.wr_idx = 0;
		ecpriss_oxtor_hal_write_reg_n_fields(ECPRI_OXTOR_REG_TYPE_BASE,
				ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG, ring_id,
				(void *)&data_idxs_reg_s);

		/* updating the inner structure hw write index */
		ring_ptr->last_commit_idx = 0;
		/* updated for later stop validiation where wr and read
		 * indxes must be equal */
		curr_wr_idx = 0;
	}

	return 0;

}

int ecpri_oxtor_tx_ring_reset(u32 ring_id)
{
	u32 timeout_ms = 1000;
	u32 m;
	u32 k;
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_data_idxs_reg_s
	data_idxs_reg_s;
	ecpri_oxtor_tx_ring_cmd_u tx_cmd; /* Need to double check */
	ecpri_global_hwio_def_ecpri_global_xtor_cfg_s global_cfg;
	ecpri_oxtor_tx_ring_s *ring_ptr = NULL;
	int result;

	ring_ptr= &ecpri_oxtor_tx_ring_cnxt.ring_arr[ring_id];

	/* clean the commands from the oxtor tx ring memory  */
	/* Stop xmitting from ring, in wrap mode it will zero the WR_IDX */
	result = ecpri_oxtor_tx_stop(ring_id, timeout_ms);
	if(0 != result)
	{
		pr_err("Error in tx stop process");
		WARN_ON(1);
		return -EINVAL;
	}

	/* writing 0 to WR_IDX to brutally stop ring */
	data_idxs_reg_s.wr_idx = 0;
	ecpriss_oxtor_hal_write_reg_n_fields(ECPRI_OXTOR_REG_TYPE_BASE,
		ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG , ring_id, &data_idxs_reg_s);
	/* set all valid tx cmds in ring memory to 0 */
	for (m = 0; m < ring_ptr->numValid ; ++m)
	{
		for (k = 0; k < HWIO_ECPRI_ORAN_XTOR_TX_n_CMD_m_k_MAXk; ++k)
		{
			/* k = total 4 dwords per command */
			/* m = entryid */
			/* n = ringid */
			tx_cmd.val[k]= 0;
			ecpriss_oxtor_hal_write_reg_mnk_fields(
			ECPRI_OXTOR_REG_TYPE_BASE, ECPRI_ORAN_XTOR_TX_n_CMD_m_k,
			m,ring_id,k,&tx_cmd.val[k]);
		}
	}

	/* updating the inner structure indexes */
	ring_ptr->last_commit_idx = 0;
	ring_ptr->numValid = 0;
	ring_ptr->PostedIdxBeforeStop = 0;
	ring_ptr->wr_idx =0;


	/* reset the HW tx ring state */
	{
		/* TODO: Mayank, need to take care of timer concept */
		/* VVDRV_ecpri_timer timer;*/

		switch(ring_id)
		{
			case 0:
				global_cfg.oran_xtor_tx_reset_0 = 1;
				break;
			case 1:
				global_cfg.oran_xtor_tx_reset_1 = 1;
				break;
			case 2:
				global_cfg.oran_xtor_tx_reset_2 = 1;
				break;
			case 3:
				global_cfg.oran_xtor_tx_reset_3 = 1;
				break;
			default:
				break;
		}

		ecpriss_oxtor_hal_write_reg_n_fields(
		ECPRI_OXTOR_REG_TYPE_BASE, ECPRI_GLOBAL_XTOR_CFG, 0,
		&global_cfg );

		/* HW Feature: the reset is not set WR_IDX to zero
		 * NOT LIKE the RD_IDX which it is set to 0 */
		/* WA For this feature: Stop the ring manually by
		 * writing 0 to the WR_IDX */
		data_idxs_reg_s.wr_idx = 0;
		ecpriss_oxtor_hal_write_reg_n_fields(ECPRI_OXTOR_REG_TYPE_BASE,
				ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG, ring_id,
				&data_idxs_reg_s);
#if 0
		/* updating the inner structure indexes except num_valid
		   because we are not clearing the cmds mem*/
		m_nextSlot = 0;
		m_lastPostedIdx = 0;
		m_PostedIdxBeforeStop = 0;
#endif
		/*  timer.Sleep_us(10); */
		/* TBD: Mayank check why to set 1 followed by 0, as in VI code */
		switch(ring_id)
		{
			case 0:
				global_cfg.oran_xtor_tx_reset_0 = 0;
				break;
			case 1:
				global_cfg.oran_xtor_tx_reset_1 = 0;
				break;
			case 2:
				global_cfg.oran_xtor_tx_reset_2 = 0;
				break;
			case 3:
				global_cfg.oran_xtor_tx_reset_3 = 0;
				break;
			default:
				break;
		}
		ecpriss_oxtor_hal_write_reg_n_fields(ECPRI_OXTOR_REG_TYPE_BASE,
				ECPRI_GLOBAL_XTOR_CFG, 0, &global_cfg );
	}

	return 0;
}


#ifdef UNUSED
static int ecpri_oxtor_tx_ring_enable_wrap_mode(u32 ring_id, u8 enable)
{
	return 0;

}
#endif
int ecpri_oxtor_tx_ring_queue_cmd(ecpri_oxtor_core_tx_cmd_cfg_s user_cmd,
		u32 ring_id)
{
	ecpri_oxtor_tx_ring_s *ring_ptr = NULL;
	ecpri_oxtor_tx_ring_cmd_u *tx_cmd;
	u32 k;
	u32 cmd_idx;
	int res;
	/* TODO: Mayank, update variables with more intutive names */

	pr_err("ring_id %d \n",
			ring_id);
	/* TODO: Mayank, ring management code to be there */
	ring_ptr= &ecpri_oxtor_tx_ring_cnxt.ring_arr[ring_id];
	/*     tx_cmd = ecprii_oxtor_tx_ring_find_next_cmd(ring_id, &mval); */
	tx_cmd = &ring_ptr->cmd_arr[ring_ptr->wr_idx];
	cmd_idx = ring_ptr->wr_idx;

	pr_err("ecpri_oxtor_tx_ring_queue_cmd ()\n");
	pr_info("ring_ptr->numValid = %d \n", ring_ptr->numValid);

	if( tx_cmd == NULL )
	{
		pr_err("No free tx_cmd ring to queue ");
		WARN_ON(1);
		return -EINVAL;

	}
	res = ecpri_oxtor_tx_ctor_cmd( &user_cmd, tx_cmd);

	/* Tx cmd - 16B
	   Write 4 dwords of command in loop*/
	for (k = 0; k < HWIO_ECPRI_ORAN_XTOR_TX_n_CMD_m_k_MAXk; ++k)
	{
		/* k = total 4 dwords per command */
		/* m = entry id in the lut */
		/* n = ringid */
		ecpriss_oxtor_hal_write_reg_mnk_fields(
		ECPRI_OXTOR_REG_TYPE_BASE, ECPRI_ORAN_XTOR_TX_n_CMD_m_k,
		cmd_idx,ring_id,k,&tx_cmd->val[k]);

	}
	/* increment next wr_idx */
	ring_ptr->wr_idx =
		((ring_ptr->wr_idx + 1) % ECPRI_OXTOR_MAX_TX_RING_ENTRIES);

	if (ring_ptr->numValid < HWIO_ECPRI_ORAN_XTOR_TX_n_CMD_m_k_MAXm )
	{
		ring_ptr->numValid++;
	}
	pr_info("ring_ptr->numValid = %d \n", ring_ptr->numValid);
	return 0;
}


int ecpri_oxtor_tx_ring_commit(u32 num_cmd, u32 ring_id)
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_data_idxs_reg_s
	data_idxs_reg_s;
	ecpri_oxtor_tx_ring_s *ring_ptr = NULL;

	pr_err("ecpri_oxtor_tx_ring_commit(): num_cmds %d ring_id %d \n",
			num_cmd, ring_id);

	ring_ptr= &ecpri_oxtor_tx_ring_cnxt.ring_arr[ring_id];

	pr_err(
		"m_numValid[%u] m_lastPostedIdx[%u] num_cmds_to_post[%u]",
		ring_ptr->numValid, ring_ptr->last_commit_idx, num_cmd);

	/* Validate that the num is less than
	 * what was submitted to hw ring mem */
	if ( (ring_ptr->numValid - ring_ptr->last_commit_idx ) < num_cmd )
	{
		pr_err("no new commands to submit the oxtor ring.\n");
		WARN_ON(1);
		return -EINVAL;
	}

	/* Read the hw ring read register and check that oxtor is inactive.*/
	/* TODO fix this check to include wrap enabled */
	ecpriss_oxtor_hal_read_reg_n_fields(ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG,
			ring_id, (void *)&data_idxs_reg_s);

	if ( data_idxs_reg_s.rd_idx != ring_ptr->last_commit_idx)
	{
		pr_err("tx ring is not stopped before starting it with"
		"new commands\n ring_id[%u] hw_read_idx[%u] m_lastPostedIdx[%u]"
		,ring_id, data_idxs_reg_s.rd_idx, ring_ptr->last_commit_idx);
		WARN_ON(1);
		return -EINVAL;
	}

	/* write the index to the oxtor register
	 * which starts the oxtor consuming */

	/* taking care of case ring in wrap mode was
	 * stopped and now need to add the
	 * index posted before the stop */
	if (ECPRI_OXTOR_RING_MODE_WRAPPING == ring_ptr->ring_status.is_wrap_en)
	{
		/* recalculate the posted index for case
		 * the ring in wrap mode was stopped
		 * and its m_lastPostedIdx is 0 */
		if ((0 == ring_ptr->last_commit_idx) &&
				(0 != ring_ptr->PostedIdxBeforeStop))
		{
			ring_ptr->last_commit_idx =
				ring_ptr->PostedIdxBeforeStop;
		}
	}

	/* Add the num of cmds to the last posted and write to HW */
	ring_ptr->last_commit_idx += num_cmd;

	data_idxs_reg_s.wr_idx = ring_ptr->last_commit_idx ;
	ecpriss_oxtor_hal_write_reg_n_fields(ECPRI_OXTOR_REG_TYPE_BASE,
			ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG , ring_id,
			&data_idxs_reg_s );


#if 0
	/* validate the register write to the oxtor register */
	data_idxs_reg_s.wr_idx = 0;
	/* Reset write index to ensure correct reg read */
	ecpriss_oxtor_hal_read_reg_n_fields(
			ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG, ring_id,
			(void *)&data_idxs_reg_s);

	if ( data_idxs_reg_s.wr_idx != ring_ptr->last_commit_idx )
	{
		pr_err("Reg write failed data_idxs_reg_s->rd_idx = %d,
				lastPostedIdx = %d ",
				data_idxs_reg_s.wr_idx,
				ring_ptr->last_commit_idx );
		WARN_ON(1);
		return -EINVAL;
	}
#endif
	return 0;
}

#ifdef UNUSED
static int ecpri_oxtor_tx_stop_reset(u32 ring_id )
{
	int result;
	u32 timeout_ms=1000;
	ecpri_oxtor_tx_ring_s *ring_ptr = NULL;
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_data_idxs_reg_s
	data_idxs_reg_s;

	ring_ptr= &ecpri_oxtor_tx_ring_cnxt.ring_arr[ring_id];

	/* In wrap mode the stop will zero the WR_IDX.
	 * Since the ring could already be stopped, we have protection for
	 * the m_PostedIdxBeforeStop value inside the stop method. */
	result = ecpri_oxtor_tx_stop(ring_id, timeout_ms);
	if(0 != result)
	{
		pr_err("Error in tx stop process");
		WARN_ON(1);
		return -EINVAL;
	}

	/* in non wrap mode need to take the WR_IDX backwards to 0 */
	if (true != ring_ptr->ring_status.is_wrap_en )
	{
		data_idxs_reg_s.wr_idx = 0;
		ecpriss_oxtor_hal_write_reg_n_fields(ECPRI_OXTOR_REG_TYPE_BASE,
				ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG , ring_id,
				&data_idxs_reg_s );
		/* updating the inner structure hw write index */
		ring_ptr->last_commit_idx = 0;
	}

	result = ecpri_oxtor_tx_ring_commit(ring_ptr->PostedIdxBeforeStop,
			ring_id);
	if(0 != result)
	{
		pr_err("Error in tx stop process");
		WARN_ON(1);
		return -EINVAL;
	}

	return 0;
}
#endif

int ecpri_oxtor_tx_get_bandwidth(u32 ring_id)
{
	u32 temp_stat_val = 0;
	ecpri_oxtor_tx_ring_s *ring_ptr = NULL;

	ring_ptr= &ecpri_oxtor_tx_ring_cnxt.ring_arr[ring_id];

	if(ring_ptr == NULL)
	{
		pr_err("Null value\n");
		return -1;
	}


	ecpriss_oxtor_hal_read_reg_n_fields(ECPRI_ORAN_XTOR_RX_n_KBYTE_CNT_REG, ring_id, (void*)&temp_stat_val);

	pr_info("KB_count for ring_id %d is  %d\n",ring_id,temp_stat_val);

    return temp_stat_val;

}
int ecpri_oxtor_tx_get_status(u32 ring_id)
{
	ecpri_oxtor_tx_ring_s *ring_ptr = NULL;
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_data_idxs_reg_s
	data_idxs_reg_s;
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_rd_idx_wrap_cnt_s
	wrap_cnt;

	memset(&data_idxs_reg_s,0,
	sizeof(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_data_idxs_reg_s));
	memset(&wrap_cnt,0,
	sizeof(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_rd_idx_wrap_cnt_s)
	);

	ring_ptr= &ecpri_oxtor_tx_ring_cnxt.ring_arr[ring_id];

	ring_ptr->ring_status.curr_wr_idx = ring_ptr->last_commit_idx;
	/* Reset write index to ensure correct reg read */
	data_idxs_reg_s.wr_idx = 0;
	/* validate the register write to the oxtor register */
	ecpriss_oxtor_hal_read_reg_n_fields(ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG,
			ring_id, (void *)&data_idxs_reg_s);
	ring_ptr->ring_status.curr_rd_idx = data_idxs_reg_s.rd_idx;

	if (ring_ptr->ring_status.is_wrap_en == true)
	{

		ecpriss_oxtor_hal_read_reg_n_fields(
		ECPRI_ORAN_XTOR_TX_n_RD_IDX_WRAP_CNT, ring_id, &wrap_cnt );
		ring_ptr->ring_status.wrap_count = wrap_cnt.rd_idx_wrap_cnt;

	}
	else
	{
		ring_ptr->ring_status.is_wrap_en = false;
		ring_ptr->ring_status.wrap_count = 0;
	}

	return 0;

}

int ecpri_oxtor_tx_get_stats(u32 ring_id)
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_backpressure_cnt_reg_s
	bp_cnt;
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_pkt_cnt_reg_s pkt_cnt;
	ecpri_oxtor_tx_ring_s *ring_ptr = NULL;

	memset(&bp_cnt,0,
	sizeof(
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_backpressure_cnt_reg_s));
	memset(&pkt_cnt,0,
	sizeof(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_tx_n_pkt_cnt_reg_s));

	ring_ptr= &ecpri_oxtor_tx_ring_cnxt.ring_arr[ring_id];

	ecpriss_oxtor_hal_read_reg_n_fields(
	ECPRI_ORAN_XTOR_TX_n_BACKPRESSURE_CNT_REG, ring_id, &bp_cnt);
	ecpriss_oxtor_hal_read_reg_n_fields(ECPRI_ORAN_XTOR_TX_n_PKT_CNT_REG,
	ring_id, &pkt_cnt );

	ring_ptr->ring_stats.backpressure_cnt = bp_cnt.backpressure_cnt;
	ring_ptr->ring_stats.sent_pkts_cnt = pkt_cnt.pkt_cnt;

	pr_info("TX: Backpressure[%d] %d\n",ring_id,pkt_cnt.pkt_cnt);
	pr_info("TX: cont[%d] %d\n",
	ring_id,pkt_cnt.pkt_cnt);
	return
	ecpri_oxtor_tx_ring_cnxt.ring_arr[ring_id].ring_stats.sent_pkts_cnt;
}
