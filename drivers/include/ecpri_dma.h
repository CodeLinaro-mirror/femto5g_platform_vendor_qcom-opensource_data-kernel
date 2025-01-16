/*
 * SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2025 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _ECPRI_DMA_H_
#define _ECPRI_DMA_H_

#include <linux/types.h>
/* Defines & Enums */

/**
 * max size of the name of the resource
 */
#define ECPRI_DMA_RESOURCE_NAME_MAX 32


/**
 * max number of LTE VFs
 */
#define ECPRI_DMA_LTE_VF_MAX (5)


/**
 * max number of topologies
 */
#define ECPRI_DMA_TOPOLOGIES_NUMBER_MAX \
	(ECPRI_DMA_ENDP_STREAM_DEST_MAX + ECPRI_DMA_LTE_VF_MAX)

/**
 * enum ecpri_hw_ver - eCPRI hardware version type
 * @ECPRI_HW_NONE: eCPRI hardware version not defined
 * @ECPRI_HW_V1_0: eCPRI hardware version 1.0
 */
enum ecpri_hw_ver {
	ECPRI_HW_NONE = 0,
	ECPRI_HW_V1_0 = 1,
	ECPRI_HW_V2_0 = 2,
	ECPRI_HW_MAX = 3,
};

/**
 * enum ecpri_hw_flavor - eCPRI hardware flavor type
 * @ECPRI_HW_FLAVOR_NONE: eCPRI hardware flavor not defined
 * @ECPRI_HW_FLAVOR_RU: eCPRI hardware flavor RU
 * @ECPRI_HW_FLAVOR_DU_PCIE: eCPRI hardware flavor DU - PCIe
 * ECPRI_HW_FLAVOR_DU_PCIE_3_X_12: eCPRI hardware flavor DU_PCIE_3_X_12
 * @ECPRI_HW_FLAVOR_DU_L2: eCPRI hardware flavor DU - L2
 * ECPRI_HW_FLAVOR_DU_PCIE_4_X_9: eCPRI hardware flavor DU_PCIE_4_X_9
 * ECPRI_HW_FLAVOR_DU_PCIE_5_X_6: eCPRI hardware flavor DU_PCIE_5_X_6
 */
enum ecpri_hw_flavor {
	ECPRI_HW_FLAVOR_NONE = 0,
	ECPRI_HW_FLAVOR_RU = 1,
	ECPRI_HW_FLAVOR_DU_PCIE = 2,
	ECPRI_HW_FLAVOR_DU_PCIE_3_X_12 = ECPRI_HW_FLAVOR_DU_PCIE,
	ECPRI_HW_FLAVOR_DU_L2 = 3,
	ECPRI_HW_FLAVOR_DU_PCIE_4_X_9 = 4,
	ECPRI_HW_FLAVOR_DU_PCIE_5_X_6 = 5,
	ECPRI_HW_FLAVOR_MAX,
};

/**
 * enum ecpri_dma_endp_dir - DMA ENDP direction
 */
enum ecpri_dma_endp_dir {
	ECPRI_DMA_ENDP_DIR_SRC = 0,
	ECPRI_DMA_ENDP_DIR_DEST = 1,
};

/**
 * enum ecpri_dma_endp_stream_mode - DMA ENDP stream mode
 */
enum ecpri_dma_endp_stream_mode {
	ECPRI_DMA_ENDP_STREAM_MODE_M2M = 0,
	ECPRI_DMA_ENDP_STREAM_MODE_S2M = 1,
	ECPRI_DMA_ENDP_STREAM_MODE_M2S = 2,
};

/**
 * enum ecpri_dma_endp_stream_dest - DMA ENDP stream destination
 */
enum ecpri_dma_endp_stream_dest {
	ECPRI_DMA_ENDP_STREAM_DEST_FH = 0,
	ECPRI_DMA_ENDP_STREAM_DEST_C2C = 1,
	ECPRI_DMA_ENDP_STREAM_DEST_L2 = 2,
	ECPRI_DMA_ENDP_STREAM_DEST_FH_EXCEPTION = 3,
	ECPRI_DMA_ENDP_STREAM_DEST_FH_LTE = 4,
	ECPRI_DMA_ENDP_STREAM_DEST_ORAN_LOG = 5,
	ECPRI_DMA_ENDP_STREAM_DEST_MAX,
};

/**
 * enum ecpri_dma_ees - DMA Execution environments
 */
enum ecpri_dma_ees {
	ECPRI_DMA_EE_AP  = 0, //Same EE ID for all GSIs
	ECPRI_DMA_EE_Q6  = 1, //Same EE ID for all GSIs
	ECPRI_DMA_EE_VM0 = 2, // GSI0
	ECPRI_DMA_EE_VM1 = 3, // GSI0
	ECPRI_DMA_EE_VM2 = 4, // GSI0
	ECPRI_DMA_EE_VM3 = 5, // GSI0
	ECPRI_DMA_EE_VF1 = 6, // GSI0
	ECPRI_DMA_EE_VFA = 2, // GSI1
	ECPRI_DMA_EE_VFB = 3, // GSI1
	ECPRI_DMA_EE_VFC = 4, // GSI1
	ECPRI_DMA_EE_PF  = 5, // GSI1
	ECPRI_DMA_EE_VF4 = 6, // GSI1
	ECPRI_DMA_EE_VFD = 2, // GSI2
	ECPRI_DMA_EE_VFE = 3, // GSI2
	ECPRI_DMA_EE_VF2 = 4, // GSI2
	ECPRI_DMA_EE_VF3 = 5, // GSI2
	ECPRI_DMA_EE_VF5 = 6, // GSI2
};

enum ecpri_dma_vm_ids {
	ECPRI_DMA_VM_IDS_VM0 = 0,
	ECPRI_DMA_VM_IDS_VM1,
	ECPRI_DMA_VM_IDS_VM2,
	ECPRI_DMA_VM_IDS_VM3,
	ECPRI_DMA_VM_IDS_VF1,
	ECPRI_DMA_VM_IDS_VF2,
	ECPRI_DMA_VM_IDS_VF3,
	ECPRI_DMA_VM_IDS_VF4,
	ECPRI_DMA_VM_IDS_VF5,
	ECPRI_DMA_VM_IDS_VFA,
	ECPRI_DMA_VM_IDS_VFB,
	ECPRI_DMA_VM_IDS_VFC,
	ECPRI_DMA_VM_IDS_VFD,
	ECPRI_DMA_VM_IDS_VFE,
	ECPRI_DMA_VM_IDS_UNUSED1,
	ECPRI_DMA_VM_IDS_UNUSED2,
	ECPRI_DMA_VM_IDS_MAX,
	ECPRI_DMA_VM_IDS_NONE = ECPRI_DMA_VM_IDS_MAX,
	ECPRI_DMA_VM_IDS_MAX_V1 = ECPRI_DMA_VM_IDS_VF1,
};

/**
 * enum ecpri_dma_status_code - DMA trafer status code
 */
enum ecpri_dma_status_code {
	/* General*/
	ECPRI_DMA_STATUS_CODE_NORMAL = 0,
	ECPRI_DMA_STATUS_CODE_PTP = 1,
	ECPRI_DMA_STATUS_CODE_FLUSHED = 2,
	ECPRI_DMA_STATUS_CODE_P7_EXCEPTION = 3,
	/* nFAPI Error code */
	ECPRI_DMA_STATUS_CODE_TIMEOUT_ERROR = 16,
	ECPRI_DMA_STATUS_CODE_PKT_LENGTH_ERROR = 17,
	ECPRI_DMA_STATUS_CODE_SDU_LENGTH_MISMATCH_ERROR = 18,
	ECPRI_DMA_STATUS_CODE_TIMESTAMP_ERROR = 19,
	ECPRI_DMA_STATUS_CODE_MSG_LENGTH_ERROR = 20,
	/* Ethernet Error code */
	ECPRI_DMA_STATUS_CODE_MAC_FCS_ERROR = 32,
	ECPRI_DMA_STATUS_CODE_SECURITY_ERROR = 33,
	ECPRI_DMA_STATUS_CODE_IPV4_CHECKSUM_ERROR = 34,
	ECPRI_DMA_STATUS_CODE_UDP_CHECKSUM_ERROR = 35,
	/* Unsupported Ethernet Error code */
	ECPRI_DMA_STATUS_CODE_QUDP_TRAPPED_PKT = 40,
	ECPRI_DMA_STATUS_CODE_MAC_DST_MULTICAST = 41,
	ECPRI_DMA_STATUS_CODE_NON_LCL_MAC_DST = 42,
	ECPRI_DMA_STATUS_CODE_VLAN_FLTR_MISS = 43,
	ECPRI_DMA_STATUS_CODE_IP_FLTR_MISS = 44,
	ECPRI_DMA_STATUS_CODE_IPV4_FRAG = 45,
	ECPRI_DMA_STATUS_CODE_IPV4_OPTIONS = 46,
	ECPRI_DMA_STATUS_CODE_UNSUP_ETHER_TYPE = 47,
	ECPRI_DMA_STATUS_CODE_UNSUP_IP_PROT = 48,
	ECPRI_DMA_STATUS_CODE_UDP_FLRT_MISS = 49,
	ECPRI_DMA_STATUS_CODE_UDP_MAC_ADDR_HIT = 50,
	ECPRI_DMA_STATUS_CODE_QUDP_TRAPPED_PKT_PKT_0 = 51,
	ECPRI_DMA_STATUS_CODE_QUDP_TRAPPED_PKT_PKT_1 = 52,
	ECPRI_DMA_STATUS_CODE_QUDP_TRAPPED_PKT_PKT_2 = 53,
	ECPRI_DMA_STATUS_CODE_QUDP_TRAPPED_PKT_PKT_3 = 54,
	ECPRI_DMA_STATUS_CODE_MAX,
};

/**
 * enum ecpri_dma_completion_code - DMA completion code
 */
enum ecpri_dma_completion_code {
	ECPRI_DMA_COMPLETION_CODE_EOT = 0,
	ECPRI_DMA_COMPLETION_CODE_OVERFLOW,
};

/**
 * enum ecpri_dma_notify_mode - Rx endpoints notification mode
 */
enum ecpri_dma_notify_mode {
	ECPRI_DMA_NOTIFY_MODE_IRQ = 0,
	ECPRI_DMA_NOTIFY_MODE_POLL,
	ECPRI_DMA_NOTIFY_MODE_MAX,
};

/* Architecture prototypes */

/**
 * struct ecpri_dma_moderation_config - DMA Tx endpoint parameters
 *
 * @moderation_counter_threshold: Threshold for moderation counter.
 * @moderation_timer_threshold: Threshold for moderation timer in cycles.
 */
struct ecpri_dma_moderation_config {
	u32 moderation_counter_threshold;
	u32 moderation_timer_threshold;
};

/**
 * struct ecpri_dma_mem_buffer - DMA memory buffer
 * @virt_base: virtual base
 * @phys_base: physical base address
 * @size: size of memory buffer
 */
struct ecpri_dma_mem_buffer {
	void *virt_base;
	dma_addr_t phys_base;
	u32 size;
};

/**
 * struct ecpri_dma_pkt - DMA packet
 * @buffs: array of buffers with the packet payload
 * @num_of_buffers: array size
 * @user_data: per packet user data
 */
struct ecpri_dma_pkt {
	struct ecpri_dma_mem_buffer **buffs;
	u32 num_of_buffers;
	void *user_data;
};

/**
 * struct ecpri_dma_pkt_completion_wrapper - completed DMA packet
 * @pkt: pointer to the completed packet provided by ETH driver
 * @status_code: DMA status code returned from DMA upon completion
 * @comp_code: Trasnfer completion code.
 * @phys_port: Physical port
 */
struct ecpri_dma_pkt_completion_wrapper {
	struct ecpri_dma_pkt *pkt;
	enum ecpri_dma_status_code status_code;
	enum ecpri_dma_completion_code comp_code;
	uint8_t phys_port;
};

/**
 * Packet pre-header stucture
 *
 * @l2_index: L2 Index used by the UDP logic to add the L2 Header to the
 *	 		  nFAPI Tx Packets
 *
 * @l3_index: L3 Index used by the UDP logic to add the L3 Header to the
 * 			  nFAPI Tx Packets
 *
 * @l2_index_valid: L2 Index valid. If not set, it is assumed SW prepended this
 *					field to the data.
 *
 * @l3_index_valid: L3 Index valid. If not set, it is assumed SW prepended this
 *					 field to the data.
 *
 * @l2_index_source: If set, use L2 Index and Valid from Header. If not, use L2 Index
 *					 and Valid from Channel Configuration.
 *
 * @l3_index_source:1; If set, use L3 Index and Valid from Header. If not, use L3
 *  				   Index and Valid from Channel Configuration.
 *
 * @vport: VPORT field to be used by MACSEC.
 *
 * @action: Action to perform by MACSEC Core
 *
 * @vport_valid: Valid bit for fields {VPORT, Action}. If not set, user CSR
 *				 registers values
 *
 * @timestamp_packet: If set, Ethernet TX logic shall generate a Timestamp when packet
 *  				   is transmitted. Timestamp shall be returned via PTP RX
 * 					   Timestamp FIFO.
 *
 * @timestamp_tag: Use to Tag Timestamp in PTP Rx FIFO.
 *
 * @link_id: Physical Ethernet Link to send this packet.
 *
 * @port_id: Physical Ethernet Port to send this packet. For nFAPI packets,
 * 			 this field should be set to “0x2”.
 *
 * @link_id_port_id_valid: Valid bit for LinkID/PortID field. If Valid bit == 0, use
 * 						   LinkID/PortID from Channel Configuration. For nFAPI packets,
 *	 					   this bit should be set to “1”.
 *
 * @destination_channel: If the packet is sent from a Channel configured in Loopback
 *						 mode, the packet is sent to a predefined (CSR) physical
 *						 link and looped back to the Destination Channel
 *						 (along with the GSI_ID).
 *
 *	@gsi_id: If the packet is sent from a Channel configured in
 * 		     Loopback mode, the packet is sent to a predefined (CSR) physical
 *			 link and looped back to the GSI_ID
 *			 (along with the Destination Channel).
 */
struct ecpri_dma_tx_header
{
	u32 l2_index : 9;
	u32 l3_index : 9;
	u32 l2_index_valid : 1;
	u32 l3_index_valid : 1;
	u32 l2_index_source : 1;
	u32 l3_index_source : 1;
	u32 vport : 8;
	u32 action : 2;
	u32 vport_valid : 1;
	u32 timestamp_packet : 1;
	u32 timestamp_tag : 3;
	u32 reserved : 1;
	u32 link_id : 2;
	u32 port_id : 2;
	u32 link_id_port_id_valid : 1;
	u32 reserved_1 : 5;
	u32 destination_channel : 8;
	u32 gsi_id : 2;
	u32 reserved_2 : 6;
};

/**
 * struct ecpri_dma_endp_statistics - DMA ENDP stastistics
 * @total_pkts: Total number of packets transfered to \ from the ENDP
 * @total_bytes: Total number of bytes transfered to \ from the ENDP
 */
struct ecpri_dma_endp_statistics {
	u64 total_pkts;
	u64 total_bytes;
};

typedef void (*ecpri_dma_ready_cb)(void *user_data);

/** ecpri_dma_status_code_to_str() - return the string represnetaion os the status code
 * @status_code: status code to translate to string
 */
const char *ecpri_dma_status_code_to_str(enum ecpri_dma_status_code status_code);

/* Architecture API functions */

#endif //_ECPRI_DMA_H_
