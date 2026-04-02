/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2025 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef ECPRI_FLOW_H
#define ECPRI_FLOW_H

#define ECPRISS_MAC_ADDR_LEN        6
#define ECPRISS_IP_ADDR_MAX_WORDS   4
#define ECPRISS_MAX_PORTS           3
	/*!40B - Max ipv6 and ipv4 string with no tunneling*/
#define ECPRISS_IP_ADDR_LEN_MAX   16
#define MAX_MAC_FILTER_ENTRIES    20

#define ECPRISS_MAX_PCID_ENTRIES 65535

/*
 * We can support up to 16 Mac Addresses per port.
 * For now it is limited to 12 mac only.
 */
#define ECPRISS_MAX_LTE_MAC_PER_PORT 12
#define ECPRISS_MAX_NR_MAC_PER_PORT 4
#define ECPRISS_MAX_LTE_VF 5
#define ECPRISS_MAX_KERNEL_NETLINK_FLOW 64
	typedef enum
	{
		ECPRISS_QUDP_RX_CFG_FLTR_MASK_IP_DADDR		= 0x01,
		ECPRISS_QUDP_RX_CFG_FLTR_MASK_UDP_DPORT		= 0x02,
		ECPRISS_QUDP_RX_CFG_FLTR_MASK_VLAN		= 0x04,
		ECPRISS_QUDP_RX_CFG_FLTR_MASK_LOCAL_MAC_ADDR	= 0x08
	}ecpriss_ingress_filter_mask_e;

	/*! Ether type definitions*/
	typedef enum
	{
		ECPRISS_ETHERTYPE_IPV4     = 0x0800,
		ECPRISS_ETHERTYPE_IPV6     = 0x86DD,
		ECPRISS_ETHERTYPE_ECPRI    = 0xAEFE,
		ECPRISS_ETHERTYPE_VLAN     = 0x8100,
		ECPRISS_ETHERTYPE_MAX      = 0xFFFF
	}ecpriss_ethertype_e;

	/*!eCPRI configuration message ids User-User*/
	typedef enum
	{
		ECPRISS_MSG_ID_FLOW_CFG      = 0,
		ECPRISS_MSG_ID_TRANSP_CFG    = 1,
		ECPRISS_MSG_ID_FLOW_RECFG    = 2,
		ECPRISS_MSG_ID_TRANSP_RECFG  = 3,
		ECPRISS_MSG_ID_FLOW_DECFG    = 4,
		ECPRISS_MSG_ID_TRANSP_DECFG  = 5,
		ECPRISS_MSG_ID_MAX
	}ecpriss_msg_id_e;

	/*!eCPRI core driver flow configuration message ids User-kernel*/
	typedef enum
	{
		ECPRISS_CORE_FLOW_CFG_MSG_ID_FH  = 0,
		ECPRISS_CORE_FLOW_CFG_MSG_ID_OC  = 1,
		ECPRISS_CORE_FLOW_CFG_MSG_ID_C2C = 2,
		ECPRISS_CORE_FLOW_CFG_MSG_ID_L2  = 3,
		ECPRISS_CORE_FLOW_CFG_MSG_ID_MAX
	}ecpriss_core_flow_cfg_msg_id_e;

	/*!eCPRI core driver flow configuration message ids User-kernel*/
	typedef enum
	{
		ECPRISS_CORE_LINK_ID_0  = 0,
		ECPRISS_CORE_LINK_ID_1  = 1,
		ECPRISS_CORE_LINK_ID_2 = 2,
		ECPRISS_CORE_LINK_ID_3  = 3,
		ECPRISS_CFG_LINK_ID_MAX
	}ecpriss_core_link_id_e;

	typedef enum
	{
		ECPRISS_CORE_ROUTE_FH_TO_OC  = 0,
		ECPRISS_CORE_ROUTE_FH_TO_C2C = 1,
		ECPRISS_CORE_ROUTE_C2C_TO_OC = 2,
		ECPRISS_CORE_ROUTE_OC_TO_FH  = 3,
		ECPRISS_CORE_ROUTE_OC_TO_C2C  = 4,
		ECPRISS_CORE_ROUTE_C2C_TO_FH  = 5,
		ECPRISS_CORE_ROUTE_MAX
	}ecpriss_core_flow_route_id_e;

	typedef enum
	{
		ECPRISS_MSG_TYPE_REQ  = 0,
		ECPRISS_MSG_TYPE_RESP = 1,
		ECPRISS_MSG_TYPE_MAX
	}ecpriss_msg_type_e;;


	/**
	 * typedef ecpriss_ip_type - IP packet type
	 * @ECPRISS_IPV4_TYPE: ipv4 packet type
	 * @ECPRISS_IPV6_TYPE: ipv6 packet type
	 */
	typedef enum
	{
		ECPRISS_IPV4_TYPE,
		ECPRISS_IPV6_TYPE
	} ecpriss_ip_type;


	/**
	 * typedef ecpri_route_src_e - ECPRI LUT source route enum
	 * @ECPRISS_ROUTE_SRC_OC: Route originating from OC
	 * @ECPRISS_ROUTE_SRC_C2C: Route originating from C2C
	 * @ECPRISS_ROUTE_SRC_FH: Route originating from FH
	 */
	typedef enum
	{
		ECPRISS_ROUTE_SRC_OC,
		ECPRISS_ROUTE_SRC_C2C,
		ECPRISS_ROUTE_SRC_FH,
		/* Required ? Always bidirectional flow and is there a
		 * possibility of unidirectional flow,
		 * if only bidir then no reqd
		 */
		ECPRISS_ROUTE_SRC_L2
	} ecpriss_route_src_e;


	/**
	 * typedef ecpri_route_src_e - ECPRI LUT destination route enum
	 * @ECPRISS_ROUTE_DST_OC: Route with OC as destination
	 * @ECPRISS_ROUTE_DST_C2C: Route with OC as destination
	 * @ECPRISS_ROUTE_DST_FH: Route with FH as destination
	 * @ECPRISS_ROUTE_DST_OC_C2C: Route from OC to C2C as
	 *                            destination
	 */
	typedef enum
	{
		ECPRISS_ROUTE_DST_OC,
		ECPRISS_ROUTE_DST_C2C,
		ECPRISS_ROUTE_DST_FH,
		ECPRISS_ROUTE_DST_OC_C2C,
		/* Required ? Always bidirectional flow and is there a
		 * possibility of unidirectional flow,
		 * if only bidir then no reqd
		 */
		ECPRISS_ROUTE_DST_L2
	}ecpriss_route_dst_e;


	/**
	 * typedef ecpri_flow_dir_e - ECPRI flow direction enum
	 * @ECPRISS_FLOW_DIR_UL: Uplink flow
	 * @ECPRISS_FLOW_DIR_DL: Downlink flow
	 */
	typedef enum
	{
		ECPRISS_FLOW_DIR_UL,
		ECPRISS_FLOW_DIR_DL
	}ecpriss_flow_dir_e;

	/**
	 * ecpri configuration msg header construct(8B)
	 * This header is applicable for both
	 * 1. User-User messaging and
	 * 2. User-Kernel messaging
	 */
	typedef struct
	{
		uint32_t  version  : 4;
		uint32_t  msg_type : 4;
		uint32_t  client_id : 4;
		uint32_t  msg_id : 4;
		uint32_t  num_msg : 8;
		uint32_t  reserved : 8;
		uint32_t  seq_num: 16;
		uint32_t  len : 16;
	}ecpriss_msg_hdr_s;

	/*!@brief
	  CPRI QUDP cfg type for Rx filtering
	  @fltr_en_mask:    Filter types to be enabled(VLAN,ip,udp) in per
	  port INGRESS_CFG
	  @rsvd:            Reserved for future use
	  @vlan_addr_port:  VLan tag address port for whitelist fitering
	  @udp_dst_port:    UDP port to be filtered
	  @ip_type:         IPV4/V6 type
	  @ip_dst_addr:     ip dst addr for filtering
	  */
	typedef struct
	{
		uint8_t			fltr_en_mask;
		uint16_t                rsvd;
		uint16_t		vlan_addr_port;
		uint16_t		udp_dst_port;
		ecpriss_ip_type		ip_type;
		ecpriss_core_link_id_e  link_id;
		uint8_t		ip_dst_addr[ECPRISS_IP_ADDR_LEN_MAX];
	} ecpriss_qudp_rx_cfg_s;

	/*!@brief
	  eCPRI XBAR cfg type for Rx
	  1. FH RX LUT  - FH->OC/C2C (DL)
	  2. C2C RX LUT - C2C->OC (UL or DL)

	flow dir:   to determine C2C UL/DL LUT
	dst:        Destination client
	FLow_id:    PCID - for FH and C2C UL/DL LUT*
	oc_link_id: OC dst intf
	*/
	typedef struct
	{
		ecpriss_flow_dir_e   flow_dir;
		ecpriss_route_dst_e  dst;
		uint16_t             flow_id;
		uint16_t             oc_link_id;
	}ecpriss_xbar_rx_cfg_s;

	/*!@brief
	  eCPRI QUDP Tx Eth header config
	  @src_mac_addr
	  @dst_mac_addr
	  @vlan_data: PRI, CFI, VLAN ID
	  @orig_ethertype: ECPRISS_ETH_TYPE_IPV4
	  ECPRISS_ETH_TYPE_IPV6
	*/
	typedef struct
	{
		uint8_t  src_mac_addr[ECPRISS_MAC_ADDR_LEN];
		uint8_t  dst_mac_addr[ECPRISS_MAC_ADDR_LEN];
		uint16_t vlan_data;
		uint8_t  is_vlan;
		ecpriss_ethertype_e orig_ethertype;
		uint8_t  vport;
		uint8_t  vport_action;
	} ecpriss_qudp_tx_eth_hdr_s;

	/*!@brief
	  eCPRI QUDP Tx UDP/IP header config
	  @src_ip_addr
	  @dst_ip_addr
	  @src_udp_port
	  @dst_udp_port
	  @ip_type
	  @udp_chksum_en
	  @df_en: Dont Fragment bit in IPv4
	  @ipsec_en
	  @tos: {DSCP,ECN} for IPV4, {traffic class,ECN} for IPV6
	  @sa_tag_data
	 */
	typedef struct
	{
		uint8_t  src_ip_addr[ECPRISS_IP_ADDR_LEN_MAX];
		uint8_t  dst_ip_addr[ECPRISS_IP_ADDR_LEN_MAX];
		uint16_t src_udp_port;
		uint16_t dst_udp_port;
		ecpriss_ip_type ip_type;
		uint16_t udp_chksum_en : 1;
		uint16_t df_en : 1;
		uint16_t ipsec_en : 1;
		uint16_t rsvd: 4;
		uint8_t tos;
		uint16_t sa_tag_data;
	} ecpriss_qudp_tx_ip_hdr_s;

	/*!@brief
	  eCPRI QUDP Tx static per port IPV4/V6 fileds
	*/
	typedef struct
	{
		uint8_t  ttl;
		uint16_t identification;
		uint32_t flow_label;
		uint8_t  hop_limit;
	} ecpriss_qudp_per_port_tx_ip_hdr_s;

	/*!@brief
	  eCPRI QUDP cfg type for Tx framing
	  @eth hdr: L2 Ethernet header
	  @ip hdr: L3 UDP/IP header
	  @ip_hdr_p: Per port static V4/V6 fields
	 */
	typedef struct
	{
		uint16_t                         l2_hdr_tbl_idx;
		uint16_t                         l3_hdr_tbl_idx;
		ecpriss_qudp_tx_eth_hdr_s          eth_hdr;
		ecpriss_qudp_tx_ip_hdr_s           ip_hdr;
		ecpriss_qudp_per_port_tx_ip_hdr_s  ip_hdr_p;
	}ecpriss_qudp_tx_cfg_s;

	/*!@brief
	  eCPRI XBAR cfg type for Tx data flows
	  1. OC RX LUT - OC->FH
	  2. OC->C2C (No Lookup)
	  3. C2C RX LUT - C2C->FH (UL traffic)
	  */
	typedef struct
	{
		uint16_t pcid;
		ecpriss_route_dst_e   dst;
		uint16_t l2_hdr_tbl_idx;
		uint16_t l3_hdr_valid : 1;
		uint16_t rsvd : 7;
		uint16_t l3_hdr_tbl_idx;
	}ecpriss_xbar_tx_cfg_s;

	/*!@brief
	  eCPRI Flow cong type for Rx filtering
	  1. FH->OC/C2C (DL traffic)
	  2. C2C->OC (UL or DL traffic)
	  */
	typedef struct
	{
		ecpriss_route_src_e     src;
		uint32_t                port_index;
		ecpriss_qudp_rx_cfg_s   qudp_rx_cfg;
		ecpriss_xbar_rx_cfg_s   xbar_rx_cfg;
	} ecpriss_flow_rx_cfg_s;

	/*!@brief
	  eCPRI Flow cong type for Tx framing
	  1. OC->FH (UL traffic)
	  2. OC->C2C (No Lookup)
	  3. C2C->FH (UL traffic)
	  */

	typedef struct
	{
		ecpriss_route_src_e     src;
		uint32_t                port_index;
		ecpriss_qudp_tx_cfg_s  qudp_tx_cfg;
		ecpriss_xbar_tx_cfg_s  xbar_tx_cfg;
	} ecpriss_flow_tx_cfg_s;

	typedef struct
	{
		ecpriss_route_src_e		src;
		ecpriss_core_flow_route_id_e  flow_route;
		ecpriss_flow_dir_e            flow_dir;
	} ecpriss_flow_route_dir_s;

typedef struct
{
	uint8_t mac[ECPRISS_MAC_ADDR_LEN];
}ecpriss_mac_s;

typedef struct
{
	ecpriss_mac_s lte_mac_addr[ECPRISS_MAX_PORTS][ECPRISS_MAX_LTE_MAC_PER_PORT];
}ecpriss_lte_mac_addr_cfg_s;

typedef struct
{
	uint8_t mac[ECPRISS_MAC_ADDR_LEN];
	int filter_index;
	bool filter_added;
}ecpriss_loopback_mac_s;

typedef struct
{
	ecpriss_loopback_mac_s loopback_mac_addr[ECPRISS_MAX_PORTS][MAX_MAC_FILTER_ENTRIES];
	uint8_t num_of_loopback_filters_added[ECPRISS_MAX_PORTS];
}ecpriss_loopback_filter_cfg_s;

/**
 * typedef ecpri_log_dir_e - ECPRI logging direction enum
 * @ECPRISS_LOG_DIR_UL: Uplink logging
 * @ECPRISS_LOG_DIR_DL: Downlink logging
 */
typedef enum
{
        ECPRISS_LOG_DIR_UL,
        ECPRISS_LOG_DIR_DL,
        ECPRISS_LOG_DIR_UL_DL
}ecpriss_log_dir_e;

/**
 * typedef ecpriss_logging_action - CU PLANE DATA LOGGING ACTION
 * @ECPRISS_LOGGING_STOP: Stop logging data
 * @ECPRISS_LOGGING_START: Start logging data
 */
typedef enum
{
       ECPRISS_LOGGING_STOP,
       ECPRISS_LOGGING_START
}ecpriss_logging_action;

typedef struct
{
  ecpriss_logging_action action;
  ecpriss_log_dir_e      log_dir;
  uint16_t               packet_size;
  uint16_t               log_buf_size;
  uint16_t               pcids[ECPRISS_MAX_KERNEL_NETLINK_FLOW];
  uint32_t               num_of_pcid;
} ecpriss_log_cfg_s;

typedef enum ecpriss_transp_type_e{
	ECPRISS_L2_TRANSP,
	ECPRISS_L3_TRANSP,
	ECPRISS_L2_L3_TRANSP,
	ECPRISS_INVALID_TRANSP
}ecpriss_transp_type;

typedef struct {

	uint64_t xbar_fhrx_pkt_cnt_link_0;
	uint64_t xbar_fhtx_pkt_cnt_link_0;
	uint64_t xbar_fhrx_pkt_cnt_link_1;
	uint64_t xbar_fhtx_pkt_cnt_link_1;
	uint64_t xbar_fhrx_pkt_cnt_link_2;
	uint64_t xbar_fhtx_pkt_cnt_link_2;
	uint64_t xbar_fhrx_pkt_cnt_link_3;
	uint64_t xbar_fhtx_pkt_cnt_link_3;
	uint64_t xbar_fhrx_pkt_cnt_link_4;
	uint64_t xbar_fhtx_pkt_cnt_link_4;
	uint64_t xbar_fhrx_pkt_cnt_link_5;
	uint64_t xbar_fhtx_pkt_cnt_link_5;
	uint64_t xbar_fhrx_pkt_cnt_link_6;
	uint64_t xbar_fhtx_pkt_cnt_link_6;
	uint64_t xbar_fhrx_pkt_cnt_link_7;
	uint64_t xbar_fhtx_pkt_cnt_link_7;
	uint64_t xbar_fhrx_pkt_cnt_link_8;
	uint64_t xbar_fhtx_pkt_cnt_link_8;
	uint64_t xbar_fhrx_pkt_cnt_link_9;
	uint64_t xbar_fhtx_pkt_cnt_link_9;
	uint64_t xbar_fhrx_pkt_cnt_link_10;
	uint64_t xbar_fhtx_pkt_cnt_link_10;
	uint64_t xbar_fhrx_pkt_cnt_link_11;
	uint64_t xbar_fhtx_pkt_cnt_link_11;
	uint64_t xbar_fhrx_dma_pkt_cnt;
	uint64_t xbar_fhrx_uc_pkt_cnt;
	uint64_t xbar_fhrx_uc_err_pkt_cnt;
	uint64_t xbar_fhrx_err_pkt_cnt;
	uint64_t xbar_fhtx_c2c_pkt_ovf_cnt;
	uint64_t xbar_fhtx_dma_pkt_cnt;
	uint64_t xbar_fhtx_uc_pkt_cnt;
	uint64_t xbar_fhrx_c2c_pkt_cnt_fh0;
	uint64_t xbar_fhrx_oc_pkt_cnt_fh0;
	uint64_t xbar_fhrx_c2c_pkt_cnt_fh1;
	uint64_t xbar_fhrx_oc_pkt_cnt_fh1;
	uint64_t xbar_fhrx_c2c_pkt_cnt_fh2;
	uint64_t xbar_fhrx_oc_pkt_cnt_fh2;
	uint64_t xbar_octx_c2c_pkt_drop_cnt;
	uint64_t xbar_octx_fh_pkt_drop_cnt;
	uint64_t xbar_octx_c2c_len_err_cnt;
	uint64_t xbar_octx_fh_len_err_cnt;
	uint64_t xbar_octx_pkt_cnt_link0;
	uint64_t xbar_ocrx_pkt_cnt_link0;
	uint64_t xbar_octx_pkt_cnt_link1;
	uint64_t xbar_ocrx_pkt_cnt_link1;
	uint64_t xbar_octx_pkt_cnt_link2;
	uint64_t xbar_ocrx_pkt_cnt_link2;
	uint64_t xbar_octx_pkt_cnt_link3;
	uint64_t xbar_ocrx_pkt_cnt_link3;
	uint64_t xbar_ocrx_fh_pkt_cnt_link0;
	uint64_t xbar_ocrx_fh_pkt_cnt_link1;
	uint64_t xbar_ocrx_fh_pkt_cnt_link2;
	uint64_t xbar_ocrx_fh_pkt_cnt_link3;
	uint64_t xbar_ocrx_fh_pkt_cnt_link4;
	uint64_t xbar_ocrx_fh_pkt_cnt_link5;
	uint64_t xbar_ocrx_fh_pkt_cnt_link6;
	uint64_t xbar_ocrx_fh_pkt_cnt_link7;
	uint64_t xbar_ocrx_fh_pkt_cnt_link8;
	uint64_t xbar_ocrx_fh_pkt_cnt_link9;
	uint64_t xbar_ocrx_fh_pkt_cnt_link10;
	uint64_t xbar_ocrx_fh_pkt_cnt_link11;
	uint64_t xbar_ocrx_c2c_pkt_cnt_fh0;
	uint64_t xbar_ocrx_c2c_pkt_cnt_fh1;
	uint64_t xbar_ocrx_c2c_pkt_cnt_fh2;
	uint64_t xbar_dbg_fhrx_unknown_pcid_cnt_fhrx_0_cnt;
	uint64_t xbar_dbg_fhrx_unknown_pcid_cnt_fhrx_1_cnt;
	uint64_t xbar_dbg_fhrx_unknown_pcid_cnt_fhrx_2_cnt;
	uint64_t xbar_dbg_ocrx_unknown_pcid_cnt_ocrx_fh_0_cnt;
	uint64_t xbar_dbg_ocrx_unknown_pcid_cnt_ocrx_fh_1_cnt;
	uint64_t xbar_dbg_ocrx_unknown_pcid_cnt_ocrx_fh_2_cnt;
	uint64_t fhrx_unknown_pcid_info_1_n_fh0;
	uint64_t fhrx_unknown_pcid_info_2_n_fh0;
	uint64_t ocrx_unknown_pcid_info_1_n_fh0;
	uint64_t ocrx_unknown_pcid_info_2_n_fh0;
	uint64_t fhrx_unknown_pcid_info_1_n_fh1;
	uint64_t fhrx_unknown_pcid_info_2_n_fh1;
	uint64_t ocrx_unknown_pcid_info_1_n_fh1;
	uint64_t ocrx_unknown_pcid_info_2_n_fh1;
	uint64_t fhrx_unknown_pcid_info_1_n_fh2;
	uint64_t fhrx_unknown_pcid_info_2_n_fh2;
	uint64_t ocrx_unknown_pcid_info_1_n_fh2;
	uint64_t ocrx_unknown_pcid_info_2_n_fh2;

} ecpriss_Xbar_Stats;

typedef struct {

	uint64_t egress_num_udp_packets;
	uint64_t egress_num_eth_packets;
	uint64_t egress_num_bypassed_packets;
	uint64_t egress_num_mtu_err_packets;
	uint64_t ingress_num_eth_udp_packets;
	uint64_t ingress_num_fcs_err_packets;
	uint64_t ingress_num_ipv4_cs_err_packets;
	uint64_t ingress_num_udp_cs_err_packets;
	uint64_t ingress_ip_filtered_packets;
	uint64_t ingress_num_vlan_filtered_packets;
	uint64_t ingress_num_sec_err_packets;
	uint64_t ingress_ip_len_err_packets;
	uint64_t ingress_num_eth_ecpri_packets;
	uint64_t ingress_num_eth_ptp_packets;
	uint64_t ingress_num_eth_other_packets;
	uint64_t ingress_num_udp_ecpri_or_nfapi_packets;
	uint64_t ingress_num_udp_ptp_packets;
	uint64_t ingress_num_udp_other_packets;

} ecpriss_Qudp_Stats;

typedef struct {
	ecpriss_Qudp_Stats stats;
}  __attribute__((packed))ecpriss_Link;

typedef struct {
	ecpriss_Link link_0;
	ecpriss_Link link_1;
	ecpriss_Link link_2;
	ecpriss_Link link_3;
}  __attribute__((packed))ecpriss_FH;

typedef struct {
	ecpriss_FH fh_0;
	ecpriss_FH fh_1;
	ecpriss_FH fh_2;
} __attribute__((packed)) ecpriss_QUDP;

typedef struct {
	ecpriss_Xbar_Stats stats;
} __attribute__((packed)) ecpriss_XBAR;

typedef struct {
	ecpriss_QUDP qudp;
	ecpriss_XBAR xbar;
}  __attribute__((packed))datacsm_ecpriss_stats_info_s;

#endif /* ECPRI_FLOW_H */
