/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef ECPRISS_CACHE_H_
#define ECPRISS_CACHE_H_

#include "ecpri_oxtor_core.h"

#define MAX_CACHE_SIZE 20

typedef enum
{
	ECPRI_OXTOR_IOCTL_DEFAULT_S,
	ECPRI_OXTOR_IOCTL_CONFIG_S,
	ECPRI_OXTOR_IOCTL_START_S,
	ECPRI_OXTOR_IOCTL_RESET_S,
	ECPRI_OXTOR_IOCTL_GET_STATS_S,
	ECPRI_OXTOR_IOCTL_BANDWIDTH_ENABLE_S,
	ECPRI_OXTOR_IOCTL_BANDWIDTH_DISABLE_S,
	ECPRI_OXTOR_IOCTL_GET_BANDWIDTH_S
}ioctl_cmd;

typedef struct
{
	ioctl_cmd ioctl_cmd_state;

	ecpri_oxtor_core_cntxt_s core_contx;

	/* We will use dynamically allocated memory here, Kfree should be used*/
	ecpri_oxtor_core_cfg_s ioctl_cmds;

	/* Number of cmds commited on each ring 0..4*/
	u32 num_commited_cmds[4];

	/* Number of TX, Rx count on each ring 0..4*/
	ecpri_oxtor_stats_s tx_rx_stats;
}cache_stats;

typedef struct cache_list
{
	/* Index will inform about, how many times this has been called
	 * last cmd will have the largest index
	 */
	u32 index;
	cache_stats data;
}cache_list;

/*
 * This is a global cache, We will store MAX_CACHE_SIZE number if cmds into it
 * This is a circular buffer
 *
 */
typedef struct
{
	cache_list cache_info[MAX_CACHE_SIZE];

	/* One stats are collected this index will be incremented */
	u32 cache_index;
}ecpri_oxtor_cache;
#endif /* ECPRISS_CACHE_H_ */
