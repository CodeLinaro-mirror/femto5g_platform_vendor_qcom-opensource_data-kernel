/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include "ecpri_oxtor_core.h"
#include "ecpri_oxtor_rx.h"
#include "ecpri_oxtor_hal.h"
#include "ecpri_oxtor_log.h"

ecpri_oxtor_rx_ring_cntxt_s ecpri_oxtor_rx_ring_cnxt;

int ecpri_oxtor_rx_init(void)
{
	int i = 0;
	ecpri_oxtor_rx_ring_s *ring_arr = NULL;

	for(i=0; i<ECPRI_OXTOR_RX_CHANNELS_MAX; i++)
	{
		ring_arr = &ecpri_oxtor_rx_ring_cnxt.ring_arr[i];

		ring_arr->ring_id = i;
		ring_arr->max_exp_latency = 0;

	}
	return 0;
}

uint32_t ecpri_oxtor_rx_get_stats(u32 ring_id)
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_pkt_cnt_reg_s pkt_cnt;
	ecpri_oxtor_rx_ring_s *ring_ptr = NULL;

	memset(&pkt_cnt,0,
	sizeof(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_pkt_cnt_reg_s));

	ring_ptr= &ecpri_oxtor_rx_ring_cnxt.ring_arr[ring_id];

	ecpriss_oxtor_hal_read_reg_n_fields(
	ECPRI_ORAN_XTOR_RX_n_PKT_CNT_REG, ring_id, &pkt_cnt );

	ring_ptr->ring_stats.recv_pkts_cnt = pkt_cnt.pkt_cnt;

	ECPRISS_OXTOR_LOG_INFO("RX: count[%d] %d\n",ring_id,pkt_cnt.pkt_cnt);
return ecpri_oxtor_rx_ring_cnxt.ring_arr[ring_id].ring_stats.recv_pkts_cnt;
}

int ecpri_oxtor_rx_ring_reset(u32 ring_id)
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_pkt_cnt_reg_s pkt_cnt;

	memset(&pkt_cnt,0,
	sizeof(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_pkt_cnt_reg_s));

	pkt_cnt.pkt_cnt = 0;
	/* Set rx pkt count zero */
	ecpriss_oxtor_hal_write_reg_n_fields(ECPRI_OXTOR_REG_TYPE_BASE,
			ECPRI_ORAN_XTOR_RX_n_PKT_CNT_REG , ring_id, &pkt_cnt );

	return 0;

}
uint32_t ecpri_oxtor_rx_get_latency(u32 ring_id)
{
	ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_reg_packet_latency_s rx_n_error_dump_reg_packet_latency;
	memset(&rx_n_error_dump_reg_packet_latency,0,
	sizeof(ecpri_oran_xtor_hwio_def_ecpri_oran_xtor_rx_n_error_dump_reg_packet_latency_s));
    /*
	setting the 0x9429024 register value red;
	*/
	ecpriss_oxtor_hal_read_reg_n_fields(ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_REG_PACKET_LATENCY, ring_id , (void*) &rx_n_error_dump_reg_packet_latency);
	ECPRISS_OXTOR_LOG_ERR(" Inside rx_get_latency ");
	ECPRISS_OXTOR_LOG_ERR(" Value of latency extracted 0x0%x \n",rx_n_error_dump_reg_packet_latency.actual_latency);
	return rx_n_error_dump_reg_packet_latency.actual_latency;
}
