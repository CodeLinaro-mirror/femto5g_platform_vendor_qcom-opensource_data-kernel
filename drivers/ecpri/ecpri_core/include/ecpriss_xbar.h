/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef ECPRISS_XBAR_H_
#define ECPRISS_XBAR_H_

#define TOTAL_LINKS 12

#include "ecpriss_xbar_hal.h"
#include "ecpriss_flow.h"
#include "ecpriss_core.h"

#define ECPRISS_MAX_PCID_ENTRIES    1024

typedef enum
{
	ECPRI_XBAR_DEINIT,
	ECPRI_XBAR_COLD_INIT,
	ECRPI_XBAR_READY

}ecpriss_xbar_state_e;

typedef struct ecpriss_xbar_interrupt_cfg
{
	//place holder
}ecpriss_xbar_interrupt_cfg_s;

/**
 *
 */
typedef struct ecpriss_xbar_stats_s
{
	uint64_t xbar_fhrx_pkt_cnt[TOTAL_LINKS];
	uint64_t xbar_fhrx_dma_pkt_cnt;
	uint64_t xbar_fhrx_uc_pkt_cnt;
	uint64_t xbar_fhrx_uc_err_pkt_cnt;
	uint64_t xbar_fhrx_err_pkt_cnt;
	uint64_t xbar_fhtx_pkt_cnt[TOTAL_LINKS];
	uint64_t xbar_fhtx_c2c_pkt_ovf_cnt;
	uint64_t xbar_fhtx_dma_pkt_cnt;
	uint64_t xbar_c2c_pkt_ovf_cnt;
	uint64_t xbar_c2crx_dma_pkt_cnt;
	uint64_t xbar_c2crx_err_pkt_cnt;
	uint64_t xbar_fhtx_uc_pkt_cnt;
	uint64_t xbar_c2crx_pkt_cnt[TOTAL_LINKS];
	uint64_t xbar_c2ctx_pkt_cnt[TOTAL_LINKS];
}ecpriss_xbar_stats_s;

typedef struct ecpriss_xbar_port_cfg
{
	eth_ecpriss_port_params_s             eth_cfg;
	struct ecpri_dma_port_params          dma_port_cfg[ECPRISS_MAX_PORTS];
}ecpriss_xbar_port_cfg_s;

typedef struct ecpriss_xbar_flow_cfg
{
	uint32_t     pcid;
	uint32_t     dma_ring_id;
	uint32_t     oc_link_id;
	uint8_t      route_to_oran;
	uint8_t      route_to_c2c;
	uint8_t      route_to_dma;
	uint8_t      valid;
}ecpriss_xbar_pcid_flow_cfg_s;


typedef struct ecpriss_xbar_port_lut
{
	uint32_t	current_pcid;
	ecpriss_xbar_pcid_flow_cfg_s	lut_table[ECPRISS_MAX_PCID_ENTRIES];
}ecpriss_xbar_port_lut_s;

typedef struct ecpriss_xbar_oc_rx_flow_cfg
{
	uint32_t     pcid;
	uint32_t     l2_encap_info;
	uint32_t     l3_encap_info;
	uint32_t     l3_encap_valid;
	uint32_t     valid;
}ecpriss_xbar_oc_rx_flow_cfg_s;

typedef struct ecpriss_xbar_oc_rx_port_lut
{
	uint32_t	current_pcid;
	ecpriss_xbar_oc_rx_flow_cfg_s	lut_table[ECPRISS_MAX_PCID_ENTRIES];
}ecpriss_xbar_oc_rx_port_lut_s;

typedef struct ecpriss_flow_ctx
{
	ecpriss_xbar_port_lut_s		fh_xbar_lut[ECPRISS_MAX_PORTS];
	ecpriss_xbar_port_lut_s		c2c_dl_xbar_lut[ECPRISS_MAX_PORTS];
	ecpriss_xbar_port_lut_s		c2c_ul_xbar_lut[ECPRISS_MAX_PORTS];
	ecpriss_xbar_oc_rx_port_lut_s	oc_rx_xbar_lut[ECPRISS_MAX_PORTS];
}ecpriss_flow_ctx_s;

typedef struct ecpriss_xbar_ctx
{
	ecpriss_xbar_state_e		state;
	uint32_t			num_of_port_types;
	ecpriss_xbar_port_cfg_s		fh_port_cfg;
	ecpriss_xbar_port_cfg_s		c2c_port_cfg;
	ecpriss_xbar_port_cfg_s		l2_port_cfg;
	ecpriss_xbar_port_cfg_s		fh_exception_port_cfg;
	ecpriss_xbar_interrupt_cfg_s	interrupt_cfg;
	ecpriss_xbar_stats_s		stats;
	ecpriss_flow_ctx_s		flow_ctx;
	ecpriss_xbar_hal_context_s	*ecpriss_xbar_hal;
	bool				def_lut_cfg_done[ECPRISS_MAX_PORTS];
}ecpriss_xbar_ctx_s;



int ecpriss_xbar_cold_init(struct device *dev);
int ecpriss_xbar_fh_rx_lut(uint32_t port_index,
		ecpriss_flow_rx_cfg_s *xbar_rx_cfg);

int ecpriss_xbar_c2c_lut(void);
int ecpriss_xbar_l2_lut(void);
int ecpriss_xbar_oc_rx_lut(uint32_t port_index,
		ecpriss_flow_tx_cfg_s *xbar_tx_cfg);
void ecpriss_xbar_non_ecpri_lut_cfg(void);


#endif
