/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2024 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef ECPRISS_NETLINK_H_
#define ECPRISS_NETLINK_H_
#include "ecpriss_flow.h"


#define NETLINK_ECPRI 25


typedef enum
{
	ECPRISS_CLIENT_MPLANE,
	ECPRISS_CLIENT_NFAPI,
	ECPRISS_KERNEL
}ecpriss_client_id_e;

/**
 * typedef ecpri_flow_dir_e - ECPRI flow direction enum
 * @ECPRISS_FLOW_DIR_UL: Uplink flow
 * @ECPRISS_FLOW_DIR_DL: Downlink flow
 */
typedef enum
{
	ECPRISS_PACKET_UL,
	ECPRISS_PACKET_DL,
}ecpriss_packet_dir_e;


typedef enum
{
	ECPRISS_MESSAGE_REGISTER_CLIENT,
	ECPRISS_MESSAGE_FLOW_CFG,
	ECPRISS_MESSAGE_TRANSPORT_CFG,
	ECPRISS_MESSAGE_FLOW_RECFG,
	ECPRISS_MESSAGE_TRANSPORT_RECFG,
	ECPRISS_MESSAGE_FLOW_DECFG,
	ECPRISS_MESSAGE_TRANSPORT_DECFG,
	ECPRISS_MESSAGE_RESPONSE,
	ECPRISS_MESSAGE_EVENT,
	ECPRISS_MESSAGE_TEST,
	ECPRISS_MESSAGE_STAT,
	ECPRISS_MESSAGE_DEREGISTER_CLIENT,
	ECPRISS_MESSAGE_TRANSPORT_ELEMENT_TO_TRANSPORT_HDLR_MAP,
	ECPRISS_MESSAGE_FLOW_TRANSP_DECFG,
	ECPRISS_MESSAGE_TRANSPORT_EGRESS_L2_TABLE_RECFG,
	ECPRISS_MESSAGE_TRANSPORT_EGRESS_L3_TABLE_RECFG,
	ECPRISS_MESSAGE_TRANSPORT_EGRESS_L2_L3_TABLE_RECFG,
	ECPRISS_MESSAGE_TRANSPORT_INGESS_TABLE_CFG,
	ECPRISS_MESSAGE_TRANSPORT_INGESS_TABLE_DECFG,
	ECPRISS_MESSAGE_LTE_MAC_CFG
}ecpriss_message_id_e;

typedef union ecpriss_netlink_flow
{
	ecpriss_flow_tx_cfg_s  flow_tx_cfg;
	ecpriss_flow_rx_cfg_s  flow_rx_cfg;
	ecpriss_lte_mac_addr_cfg_s mac_cfg;
}ecpriss_packet_flow_u;


typedef struct ecpriss_netlink_packet_payload
{
	ecpriss_packet_dir_e   dir;
	uint32_t               payload_size;
	ecpriss_packet_flow_u  flow_cfg;
}ecpriss_packet_payload_s;


typedef struct ecpriss_netlink_packet_hdr_s
{
	uint8_t                version;
	uint8_t                client_id;
	uint8_t                message_id;
	uint8_t                num_flows;
	uint8_t                reserved;
	uint16_t               seq_id;
	uint16_t               len;
}ecpriss_packet_hdr_s;

typedef struct ecpriss_packet
{
	ecpriss_packet_hdr_s     header;
	ecpriss_packet_payload_s payload[ECPRISS_MAX_KERNEL_NETLINK_FLOW];
} ecpriss_packet_s;


int ecpriss_netlink_socket_create(void);
int ecpriss_netlink_socket_create_v2(void);
void ecpriss_process_packet(ecpriss_packet_payload_s *packet);
void ecpriss_process_packet_decfg(ecpriss_packet_payload_s *packet, ecpriss_message_id_e config_parameter);
#endif
