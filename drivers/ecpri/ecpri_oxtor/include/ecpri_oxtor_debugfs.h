/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef ECPRISS_DEBUGFS_H_
#define ECPRISS_DEBUGFS_H_

#ifndef NO_DEBUGFS_PERF

#include <linux/string.h>
#include <linux/types.h>

#include "ecpri_oxtor_core.h"
#include "ecpri_oxtor_hal.h"
#include <linux/errno.h>     /* error codes */
#include <linux/interrupt.h> /* mark_bh */
#include <linux/kernel.h>    /* printk() */
#include <linux/sched.h>
#include <linux/slab.h>  /* kmalloc() */
#include <linux/types.h> /* size_t */

#define FINAL_STATS_STR_MAX_SIZE (1024)
#define FINAL_STATS_DYNAMIC_STR_MAX_SIZE (4096)
#define TEMP_STAT_VAL_STR_MAX_SIZE (100)
#define TEMP_STR_MAX_SIZE (128)
#define TEMP_STR_MIN_SIZE (16)
#define RESET_STR(str) memset(str, 0, sizeof(str))
#define RESET_VAL(val) val = 0
#define FH_WRAPPER_SIZE (32)
#define XBAR_WRAPPER_SIZE (9)

int setup_debugfs_directory(void);

#endif /* NO_DEBUGFS_PERF */

#endif /* ECPRISS_DEBUGFS_H_ */
