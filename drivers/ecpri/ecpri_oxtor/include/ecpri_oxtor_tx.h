/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef ECPRI_OXTOR_TX_H_
#define ECPRI_OXTOR_TX_H_

#include "ecpri_oxtor_ioctl.h"
/*---------------------------------------------------------------------------
 * Macros and definitions
 *--------------------------------------------------------------------------*/


#define ECPRI_OXTOR_RING_MODE_ONE_TIME                  0
#define ECPRI_OXTOR_RING_MODE_WRAPPING                  1

#define ECPRI_OXTOR_MAX_TX_CHANNELS                     4
#define ECPRI_OXTOR_MAX_TX_RING_ENTRIES                 30
#define ECPRI_OXTOR_MAX_TX_CMD_SIZE_IN_BYTES            16

#define ECPRI_OXTOR_TX_CHANNELS_MAX                     4
#define ECPRI_OXTOR_TX_PER_CH_CMDS_MAX                 30

#define ECPRI_OXTOR_TX_CMD_SIZE_MAX                     16
#define ECPRI_OXTOR_ECPRI_COMMON_HDR_SIZE               4

/*---------------------------------------------------------------------------
 * Macros and definitions
 *--------------------------------------------------------------------------*/
#define ECPRI_OXTOR_LINK_ID_GEN(port_type, port_idx, link_idx)      \
	(((port_type & 0x3) << 0x4) |                                   \
	 (((port_idx) & 0x3) << 0x2) |                                  \
	 ((link_idx) & 0x3))

/*---------------------------------------------------------------------------
 * Type definitions
 *--------------------------------------------------------------------------*/

typedef struct ecpri_oxtor_tx_ring_config
{
	u32 run_mode;        /** ring run mode see #ECPRI_OXTOR_RING_MODE */
}ecpri_oxtor_tx_ring_config_s;

typedef struct ecpri_oxtor_tx_ring_status
{
	u32 curr_rd_idx;
	u32 curr_wr_idx;
	bool is_wrap_en;
	u32 wrap_count;
} ecpri_oxtor_tx_ring_status_s ;

typedef struct ecpri_oxtor_tx_ring_stats
{
	u32 sent_pkts_cnt;
	u32 backpressure_cnt;
} ecpri_oxtor_tx_ring_stats_s;


typedef struct
{
	/* RAW WORD 0 */
	u32 pcid : 16;               /* bits 0-15 */
	/**@brief should be created by using the macro ECPRI_oxtor_LINK_ID_GEN*/
	u32 link_id : 6;             /* bits 16-21 */
	u32 target_rx : 2;           /* bits 22-23 */
	u32 rsvd_0_24 : 8;           /* bits 24-31 */

	/* RAW WORD 1 */
	/** @brief control the bw */
	u32 data_length : 16;         /* bits 0-15 */
	/** @brief value from enum ecpri_msg_type */
	u32 ecpri_msg_type : 8;      /* bits 16-23 */
	/**@brief DU/RU topology id,helping oxtor HW managing the tx/rx tables*/
	u32 xu_num : 5;              /* bits 24-28 */
	u32 rsvd_1_29 : 3;          /* bits 29-31 */

	/* RAW WORD 2 */
	/** @brief Inner randomized data sent to ooxtor */
	u32 init_data;               /* bits 0-31 */

	/* RAW WORD 3 */
	u32 inter_pkt_delay : 12;    /* bits 0-11 */
	u32 rsvd_3_12 : 20;          /* bits 12-31 */
}ecpri_xtor_tx_ring_cmd_s;

typedef union
{
	ecpri_xtor_tx_ring_cmd_s fields;
	u32 val[4];

}ecpri_oxtor_tx_ring_cmd_u;

typedef struct ecpri_oxtor_tx_ring
{

	u32 ring_id;    /**< ring id */
	u32 initData; /**< randomized init data to put in next oxtor cmd */

	/** mirror of the posted commands */
	ecpri_oxtor_tx_ring_cmd_u cmd_arr[ECPRI_OXTOR_TX_PER_CH_CMDS_MAX];

	u32 rd_idx;
	u32 wr_idx;       /**< next index to be used in the tx_ring_mirror */
	u32 last_commit_idx;  /**< last posted tx write idx */
	u32 numValid;       /**< number of valid commands in HW cmds ring */
	/** last posted write idx before it was stopped brutally by writing 0
	 * to WR_IDX */
	u32 PostedIdxBeforeStop;

	ecpri_oxtor_tx_ring_status_s ring_status;
	ecpri_oxtor_tx_ring_stats_s  ring_stats;
} ecpri_oxtor_tx_ring_s;

typedef struct ecpri_oxtor_tx_ring_cntxt
{

	bool init;
	/*Tx Ring array*/
	ecpri_oxtor_tx_ring_s ring_arr[ECPRI_OXTOR_TX_CHANNELS_MAX];

} ecpri_oxtor_tx_ring_cntxt_s;

int ecpri_oxtor_tx_init(void);
int ecpri_oxtor_tx_ring_queue_cmd(ecpri_oxtor_core_tx_cmd_cfg_s user_cmd,
		u32 ring_id);
int ecpri_oxtor_tx_ring_commit(u32 num_cmd, u32 ring_id);
int ecpri_oxtor_tx_ring_reset(u32 ring_id);
int ecpri_oxtor_tx_ctl_reg_cfg(const ecpri_oxtor_tx_ring_config_s* cfg ,
		u32 ring_id);
int ecpri_oxtor_tx_get_status(u32 ring_id);
int ecpri_oxtor_tx_get_stats(u32 ring_id);

#endif /* ECPRI_OXTOR_TX_H_ */
