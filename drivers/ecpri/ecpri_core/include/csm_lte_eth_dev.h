/* SPDX-License-Identifier: GPL-2.0-only
 *  Copyright (c)2024 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/**
 *   @file
 *   csm_lte_eth_dev.h
 *
 *   @brief
 *   This file provides Fronthaul Ethernet control messaging
 *   definitions for host and X100 device communication
 *
 **/

/*===========================================================================
 *
 *   EDIT HISTORY FOR MODULE
 *
 *   This section contains comments describing changes made to the module.
 *   Notice that changes are listed in reverse chronological order.
 *
 *   $Header:  $
 *
 *   when       who     what, where, why
 *--------   ---     ----------------------------------------------------------
 *===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CSM_LTE_ETH_DEV_H
#define CSM_LTE_ETH_DEV_H

#define CSM_LTE_MAC_ADDR_LEN_MAX   6

	/**
	 *  enum CSM Eth FH link rate
	*/
	typedef enum
	{
		CSM_LTE_ETHDEV_LINK_RATE_10 = 0,
		CSM_LTE_ETHDEV_LINK_RATE_25,
		CSM_LTE_ETHDEV_LINK_RATE_40,
		CSM_LTE_ETHDEV_LINK_RATE_50,
		CSM_LTE_ETHDEV_LINK_RATE_100,
		CSM_LTE_ETHDEV_LINK_RATE_MAX
	} csm_lte_ethdev_link_rate_e;

	/**
	 * enum CSM Eth FH link state
	*/
	typedef enum
	{
		CSM_LTE_ETHDEV_LINK_STATE_INIT = 0,
		CSM_LTE_ETHDEV_LINK_STATE_OPEN,
		CSM_LTE_ETHDEV_LINK_STATE_CLOSE,
		CSM_LTE_ETHDEV_LINK_STATE_UP,
		CSM_LTE_ETHDEV_LINK_STATE_DOWN,
		CSM_LTE_ETHDEV_LINK_STATE_MAX
	} csm_lte_ethdev_link_state_e;

	/**
	 *  enum CSM Eth msg cmd type
	*/
	typedef enum
	{
		CSM_LTE_ETHDEV_CMD_TYPE_REQ = 0,
		CSM_LTE_ETHDEV_CMD_TYPE_RESP,
		CSM_LTE_ETHDEV_CMD_TYPE_IND,
		CSM_LTE_ETHDEV_CMD_TYPE_MAX
	} csm_lte_ethdev_cmd_type_e;

	/**
	 * enum CSM Eth cmd id
	*/
	typedef enum
	{
		CSM_LTE_ETHDEV_CMD_GET_LINK_STATE = 0,
		CSM_LTE_ETHDEV_CMD_SET_LINK_STATE,
		CSM_LTE_ETHDEV_CMD_GET_LINK_RATE,
		CSM_LTE_ETHDEV_CMD_GET_MTU,
		CSM_LTE_ETHDEV_CMD_GET_STATS,
		CSM_LTE_ETHDEV_CMD_GET_MAC_ADDR,
		CSM_LTE_ETHDEV_CMD_SET_MAC_ADDR,
		CSM_LTE_ETHDEV_CMD_MAX
	} csm_lte_ethdev_cmd_e;

	/**
	 * enum CSM Eth msg result
	*/
	typedef enum
	{
		CSM_LTE_ETHDEV_RES_SUCCESS = 0,
		CSM_LTE_ETHDEV_RES_FAILURE,
		CSM_LTE_ETHDEV_RES_CMD_INVALID,
		CSM_LTE_ETHDEV_RES_CMD_MSG_INVALID,
		CSM_LTE_ETHDEV_RES_CMD_UNSUPPORTED,
		CSM_LTE_ETHDEV_RES_CMD_FAILURE,
		CSM_LTE_ETHDEV_RES_MAX
	} csm_lte_ethdev_result_e;

	/**
	 * CSM LTE ethtool control msg header construct
	 *
	 */
	typedef struct
	{
		uint32_t  version     : 4;
		uint32_t  cmd_type    : 4;
		uint32_t  cmd_id      : 8;
		uint32_t  seq_num     : 8;
		uint32_t  result      : 8;
		uint32_t  reserved    : 8;
		uint32_t  eth_link_id : 8;
		uint32_t  len         : 16;
	} __attribute__((__packed__)) csm_lte_ethdev_msg_hdr_s;

	/**
	 * CSM Eth link info - rate
	 * Respsonse data for CSM_LTE_ETHDEV_CMD_GET_LINK_RATE request
	 * msg by host
	 */
	typedef struct
	{
		uint32_t link_rate;
	} __attribute__((__packed__)) csm_lte_ethdev_rate_s;

	/**
	 * CSM Eth link info - state.
	 * Response data for CSM_LTE_ETHDEV_CMD_GET_LINK_STATE Request
	 * msg by host
	 */
	typedef struct
	{
		uint32_t link_state;
	} __attribute__((__packed__)) csm_lte_ethdev_state_s;

	/**
	 * CSM Eth mtu.
	 * Response data for CSM_LTE_ETHDEV_CMD_GET_MTU Request
	 * msg by host
	 */
	typedef struct
	{
		uint32_t mtu;
	} __attribute__((__packed__)) csm_lte_ethdev_mtu_s;

	/**
	 * CSM Eth link info - Mac address info for below Request msgs
	 * by host
	 * CSM_LTE_ETHDEV_CMD_GET_MAC_ADDR,
	 * CSM_LTE_ETHDEV_CMD_SET_MAC_ADDR,
	 */
	typedef struct
	{
		uint8_t  mac_addr[CSM_LTE_MAC_ADDR_LEN_MAX];
	} __attribute__((__packed__)) csm_lte_ethdev_mac_s;

	/**
	 * CSM Eth link stats - all
	 * Response data for CSM_LTE_ETHDEV_CMD_GET_STATS request msg
	 * by host
	 */
	typedef struct
	{
		uint64_t tx_pkt_cnt;
		uint64_t rx_pkt_cnt;
		uint64_t tx_pkt_bytes;
		uint64_t rx_pkt_bytes;
		uint64_t tx_errors;
		uint64_t rx_errors;
	} __attribute__((__packed__)) csm_lte_ethdev_stats_s;

	/**
	 * CSM LTE ethtool control msg payload construct
	 *		 *
	 */

	typedef union
	{

		csm_lte_ethdev_rate_s link_rate;
		csm_lte_ethdev_state_s link_state;
		csm_lte_ethdev_mtu_s mtu;
		csm_lte_ethdev_mac_s mac_addr;
		csm_lte_ethdev_stats_s stats;

	} csm_lte_ethdev_msg_payload_s;

	/**
	 * CSM LTE ethtool control msg construct
	 *
	 */
	typedef struct
	{
		csm_lte_ethdev_msg_hdr_s hdr;
		csm_lte_ethdev_msg_payload_s payload;

	} __attribute__((__packed__)) csm_lte_ethdev_msg_s;


#endif /* CSM_LTE_ETH_DEV_H */
#ifdef __cplusplus
}
#endif
