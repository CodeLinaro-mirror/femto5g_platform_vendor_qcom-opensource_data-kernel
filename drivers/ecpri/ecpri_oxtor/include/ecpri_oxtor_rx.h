/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef ECPRI_OXTOR_RX_H_
#define ECPRI_OXTOR_RX_H_

#define ECPRI_OXTOR_RX_CHANNELS_MAX       4

typedef struct ecpri_oxtor_rx_ring_status
{
	u32 dummy;
} ecpri_oxtor_rx_ring_status_s ;

typedef struct ecpri_oxtor_rx_ring_stats
{
	u32 recv_pkts_cnt;
} ecpri_oxtor_rx_ring_stats_s;


typedef struct
{
	u32 ring_id;	  /**< ring id */
	u32 max_exp_latency;

	ecpri_oxtor_rx_ring_status_s ring_status;
	ecpri_oxtor_rx_ring_stats_s  ring_stats;

} ecpri_oxtor_rx_ring_s;

typedef struct
{
	/*Rx Ring array*/
	ecpri_oxtor_rx_ring_s ring_arr[ECPRI_OXTOR_RX_CHANNELS_MAX];

} ecpri_oxtor_rx_ring_cntxt_s;

int ecpri_oxtor_rx_init(void);
uint32_t ecpri_oxtor_rx_get_stats(u32 ring_id);
int ecpri_oxtor_rx_ring_reset(u32 ring_id);
uint32_t ecpri_oxtor_rx_get_latency(u32 ring_id);

#endif /* ECPRI_OXTOR_RX_H_ */
