/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef ECPRI_OXTOR_IOCTL_H_
#define ECPRI_OXTOR_IOCTL_H_

#include <linux/ioctl.h>

/* 30*4, 30 cmds on each ring */
#define ECPRI_OXTOR_TEST_CFG_MAX 120
#define NUM_OF_CMDS 1


typedef enum
{
	ECPRI_OXTOR_IOCTL_CMD_TEST,
	ECPRI_OXTOR_IOCTL_CMD_MAX
}ecpri_oxtor_ioctl_cmd_type;

typedef enum
{
	ECPRI_OXTOR_TEST_MODE_TX_ONLY   = 0,
	ECPRI_OXTOR_TEST_MODE_RX_ONLY   = 1,
	ECPRI_OXTOR_TEST_MODE_TX_RX     = 2,
	ECPRI_OXTOR_TEST_MODE_MAX,

}ecpri_oxtor_core_test_mode_e;

typedef enum
{
	ECPRI_OXTOR_CORE_LINK_ID_PORT_TYPE_FH    = 0,
	ECPRI_OXTOR_CORE_LINK_ID_PORT_TYPE_C2C   = 1,
	ECPRI_OXTOR_CORE_LINK_ID_PORT_TYPE_OC    = 2
} ecpri_oxtor_core_linkid_port_type_e;


typedef enum  {
	ECPRI_OXTOR_CORE_LINK_ID_PORT_0      = 0,
	ECPRI_OXTOR_CORE_LINK_ID_PORT_1      = 1,
	ECPRI_OXTOR_CORE_LINK_ID_PORT_2      = 2
} ecpri_oxtor_core_linkid_port_idx_e;

/* For FH links when operating in 12x25G mode */
typedef enum
{
	ECPRI_OXTOR_CORE_LINK_ID_INDEX_0     = 0,
	ECPRI_OXTOR_CORE_LINK_ID_INDEX_1     = 1,
	ECPRI_OXTOR_CORE_LINK_ID_INDEX_2     = 2,
	ECPRI_OXTOR_CORE_LINK_ID_INDEX_3     = 3,
} ecpri_oxtor_core_linkid_idx_e;

/**
 * Oxtor Flow configuration (similar config set in XBAR/QUDP)
 */
typedef struct
{
	uint16_t pcid;
	/*link_id = port_type(2bits) + port_idx(2bits) + link idx (2bits) */
	ecpri_oxtor_core_linkid_port_type_e port_type;
	ecpri_oxtor_core_linkid_port_idx_e  port_idx;
	ecpri_oxtor_core_linkid_idx_e       link_idx;
	/*Tx OC intf id*/
	uint32_t tx_oc_link_id;
	/*Rx OC intf id*/
	uint32_t rx_oc_link_id;

} ecpri_oxtor_core_flow_cfg_s;

/**
 * Main oxtor Tx configration
 **/

typedef struct
{
	/*Current device id*/
	uint32_t xu_id;
	/*eCPRI pkt_len*/
	uint16_t pkt_len;
	/*Inter pkt delay*/
	uint16_t inter_pkt_delay;
	/*eCPRI payload init data*/
	uint32_t  init_data;
	/*eCPRI MSG type*/
	uint8_t ecpri_msg_type;
	/*Wrap mode enabled*/
	uint8_t ring_wrap_en;
} ecpri_oxtor_core_pkt_cmd_cfg_s;

/**
 * Oxtor Tx user command config
 **/

typedef struct
{
	/*eCPRI pkt cfg*/
	ecpri_oxtor_core_pkt_cmd_cfg_s pkt_cfg;
	/*eCPRI flow cfg*/
	ecpri_oxtor_core_flow_cfg_s   flow_cfg;
} ecpri_oxtor_core_tx_cmd_cfg_s;

/**
 * Oxtor Rx configration
 **/

typedef struct
{
	uint32_t dummy;
} ecpri_oxtor_core_rx_cfg_s;

/**
 * Main oxtor configration structure
 **/
typedef struct
{
	/*Test mode*/
	ecpri_oxtor_core_test_mode_e test_mode;
	/*Num Tx cmds*/
	uint32_t num_cmds;
	/* Tx cmd cfg*/
	ecpri_oxtor_core_tx_cmd_cfg_s *tx_cmd_cfg;
	/* Rx cmd cfg*/
	ecpri_oxtor_core_rx_cfg_s rx_cfg;

} ecpri_oxtor_core_cfg_s;
/* TODO will move def in new header */

typedef enum
{
	ECPRI_OXTOR_DEAFULT,
	ECPRI_OXTOR_MANUAL
}ecpri_oxtor_start_test_s;

typedef struct
{
	ecpri_oxtor_start_test_s start_test_mode;
	uint8_t num_cmds;
	uint32_t tx_oc_link_id;
} ecpri_oxtor_start_cfg_s;

typedef struct
{
	uint32_t rx_count[4];
	uint32_t tx_count[4];
} ecpri_oxtor_stats_s;
/*---------------------------------------------------------------------------
 * Macros and definitions
 *--------------------------------------------------------------------------*/

#define IOCTL_BASE	'W'
#define ECPRI_OXTOR_IOCTL_CONFIG _IOW(IOCTL_BASE, 'a', ecpri_oxtor_core_cfg_s *)
#define ECPRI_OXTOR_IOCTL_START	_IOW(IOCTL_BASE, 'b', ecpri_oxtor_start_cfg_s *)
#define ECPRI_OXTOR_IOCTL_RESET _IOW(IOCTL_BASE, 'c', uint32_t *)
#define ECPRI_OXTOR_IOCTL_GET_STATS _IOR(IOCTL_BASE, 'd', ecpri_oxtor_stats_s *)


#endif /* ECPRI_OXTOR_IOCTL_H_ */
