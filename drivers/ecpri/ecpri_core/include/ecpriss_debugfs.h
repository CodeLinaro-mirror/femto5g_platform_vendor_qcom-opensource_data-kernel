 /* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef __ECPRISS_STATS_AND_INTERRUPTS__
#define __ECPRISS_STATS_AND_INTERRUPTS__

#ifdef CONFIG_DEBUG_FS
#define FINAL_STATS_STR_MAX_SIZE 1024
#define FINAL_STATS_DYNAMIC_STR_MAX_SIZE 4096
#define TEMP_STAT_VAL_STR_MAX_SIZE 100
#define TEMP_STR_MAX_SIZE 128
#define TEMP_STR_MIN_SIZE 16
#define RESET_STR(str) memset(str, 0, sizeof(str))
#define FH_WRAPPER_SIZE 64
#define XBAR_WRAPPER_SIZE 64

int setup_debugfs_directory(void);
#endif
#endif
