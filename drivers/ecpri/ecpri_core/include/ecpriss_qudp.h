/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef ECPRISS_QUDP_H_
#define ECPRISS_QUDP_H_

#include "ecpriss_qudp_hal.h"
#include "ecpriss_flow.h"
#include "ecpriss_core.h"

#define MAX_WHITELIST_ENTRIES       16
#define QUDP_IRQ_MAX                6
#define ECPRISS_MAX_LINKS           4

typedef enum
{
	ECPRISS_UDP_C2C_IRQ_PORT0,
	ECPRISS_UDP_C2C_IRQ_PORT1,
	ECPRISS_UDP_FH_IRQ_PORT0,
	ECPRISS_UDP_FH_IRQ_PORT1,
	ECPRISS_UDP_FH_IRQ_PORT2,
	ECPRISS_UDP_L2_IRQ
}ecpriss_qudp_interrupt_events_e;


/**
 * enum ecpriss_port_dir
 */
typedef enum {
	ECPRISS_PORT_0 = 0,
	ECPRISS_PORT_1,
	ECPRISS_PORT_2,
	ECPRISS_PORT_MAX
}ecpriss_port_idx_e;



typedef enum
{
	ECPRI_QUDP_DEINIT,
	ECPRI_QUDP_READY

}epriss_qudp_state_e;

/**
 *
 */
typedef struct ecpriss_qudp_ingress_per_port_cfg
{
	uint32_t	num_ip_fltr_entries;
	uint32_t	num_vlan_fltr_entries;
	uint32_t	num_udp_fltr_entries;
	uint32_t
		ipdst_addr[MAX_WHITELIST_ENTRIES][ECPRISS_IP_ADDR_MAX_WORDS];
	uint32_t	vlan_addr[MAX_WHITELIST_ENTRIES];
	uint32_t        udp_port[MAX_WHITELIST_ENTRIES];
	//change to smaller struct with only filter values
	ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_config_p_s   fh_ingress_config;
	ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_config_p_s   l2_ingress_config;
}ecpriss_qudp_ingress_per_port_cfg_s;

/**
 *
 */
typedef struct ecpriss_qudp_egress_port_cfg
{
	uint32_t	num_l2_tbl_entries;
	uint32_t	num_l3_tbl_entries;
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_mtu_p_s   egress_eth_mtu;
}ecpriss_qudp_egress_per_port_cfg_s;

/**
 *
 */
typedef struct ecpriss_qudp_trap_cfg
{
	//place holder
}ecpriss_qudp_trap_cfg_s;

/**
 *
 */
typedef struct ecpriss_qudp_interrupt_cfg
{
	//place holder
}ecpriss_qudp_interrupt_cfg_s;

typedef struct ecpriss_qudp_stats
{
	uint64_t egress_num_udp_packets[ECPRISS_MAX_LINKS];
	uint64_t egress_num_eth_packets[ECPRISS_MAX_LINKS];
	uint64_t egress_num_bypassed_packets[ECPRISS_MAX_LINKS];
	uint64_t egress_num_mtu_err_packets[ECPRISS_MAX_LINKS];
	uint64_t ingress_num_udp_packets[ECPRISS_MAX_LINKS];
	uint64_t ingress_num_non_udp_packets[ECPRISS_MAX_LINKS];
	uint64_t ingress_num_fcs_err_packets[ECPRISS_MAX_LINKS];
	uint64_t ingress_num_ipv4_cs_err_packets[ECPRISS_MAX_LINKS];
	uint64_t ingress_num_udp_cs_err_packets[ECPRISS_MAX_LINKS];
	uint64_t ingress_num_vlan_filtered_packets[ECPRISS_MAX_LINKS];
	uint64_t ingress_num_sec_err_packets[ECPRISS_MAX_LINKS];
	uint64_t ingress_ip_len_err_packets[ECPRISS_MAX_LINKS];
	uint64_t ingress_ip_filtered_packets[ECPRISS_MAX_LINKS];
}ecpriss_qudp_stats;

typedef struct ecpriss_qudp_interrupt_stats
{
	uint32_t egress_mtu_err_packet_link[ECPRISS_MAX_LINKS];
	uint32_t ingress_fcs_err_packet_link[ECPRISS_MAX_LINKS];
	uint32_t ingress_pkt_fifo_empty_before_eop_link[ECPRISS_MAX_LINKS];
	uint32_t ingress_ipv4_cs_error_link[ECPRISS_MAX_LINKS];
	uint32_t ingress_udp_cs_error_link[ECPRISS_MAX_LINKS];
	uint32_t ingress_ip_filtered_packet_link[ECPRISS_MAX_LINKS];
	uint32_t ingress_vlan_filtered_packet_link[ECPRISS_MAX_LINKS];
	uint32_t ingress_sec_err_packet_link[ECPRISS_MAX_LINKS];
	uint32_t ingress_ip_len_err_packet_link[ECPRISS_MAX_LINKS];
	uint32_t ingress_trap_rule_0_link[ECPRISS_MAX_LINKS];
	uint32_t ingress_trap_rule_1_link[ECPRISS_MAX_LINKS];
	uint32_t ingress_trap_rule_2_link[ECPRISS_MAX_LINKS];
	uint32_t ingress_trap_rule_3_link[ECPRISS_MAX_LINKS];
	uint32_t
	ingress_last_in_chain_non_local_dst_packet_link[ECPRISS_MAX_LINKS];
}ecpriss_qudp_interrupt_stats_s;


/**
 *
 */
typedef struct ecpriss_qudp_port_cfg
{
	//ecpriss_port_type_e                   port_type;
	ecpriss_port_idx_e                    port_index;
	ecpriss_qudp_ingress_per_port_cfg_s   ingress_port_cfg;
	ecpriss_qudp_egress_per_port_cfg_s    egress_cfg;
	ecpriss_qudp_trap_cfg_s               trap_cfg;
	ecpriss_qudp_interrupt_cfg_s          interrupt_cfg;
	ecpriss_qudp_interrupt_stats_s        interrupt_stats;
	ecpriss_qudp_stats                    stats;
	eth_ecpriss_port_params_s             eth_cfg;
}ecpriss_qudp_port_cfg_s;


/**
 *
 */
typedef struct ecpriss_qudp_ctx
{
	epriss_qudp_state_e                 state;
	uint32_t                            num_ports;
	ecpriss_qudp_port_cfg_s             fh_port_cfg[ECPRISS_PORT_MAX];
	ecpriss_qudp_port_cfg_s             c2c_port_cfg[ECPRISS_PORT_MAX];
	ecpriss_qudp_port_cfg_s             l2_port_cfg[ECPRISS_PORT_MAX];
	//Todo:change to typedef
	ecpriss_qudp_hal_context_s         *ecpriss_qudp_hal_ctx;
}ecpriss_qudp_ctx_s;



int ecpriss_qudp_init(struct device *dev);
int ecpriss_qudp_fh_tx_hdr_ins_cfg(uint32_t               port_index,
		ecpriss_qudp_tx_cfg_s *tx_cfg);
int ecpriss_qudp_fh_rx_filter_cfg(uint32_t               port_index,
		ecpriss_qudp_rx_cfg_s *rx_cfg);

void ecpriss_qudp_print_fh_ingress_stats(uint32_t port_index,
		uint32_t link_index);
void ecpriss_qudp_print_fh_egress_stats(uint32_t port_index,
		uint32_t link_index);
void ecpriss_qudp_ingress_config_stats(int32_t fh_index);
void debug_qudp_ingress_config(void);
void ecpriss_qudp_egress_config_stats(int32_t fh_index);
void debug_qudp_egress_config(void);

void ecpriss_qudp_print_c2c_ingress_stats(uint32_t port_index,
		uint32_t link_index);
void ecpriss_qudp_print_c2c_egress_stats(uint32_t port_index,
		uint32_t link_index);


void ecpriss_qudp_print_l2_ingress_stats(uint32_t port_index,
		uint32_t link_index);
void ecpriss_qudp_print_l2_egress_stats(uint32_t port_index,
		uint32_t link_index);
void ecpriss_qudp_clear_stats(uint32_t port_index,
		uint32_t link_index);
#endif
