//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _EIP_LOG_H
#define _EIP_LOG_H

#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/ipc_logging.h>

#include "basic_defs.h"

#define DRV_NAME "secure_eip"

/*----------------------------------------------------------------------------
 * LOG_SEVERITY_MAX
 *
 * This is used to control three classes of log messages as part of DDK
 * logging. Informational, Warnings and Critical
 */
#undef LOG_SEVERITY_MAX
#define LOG_SEVERITY_MAX LOG_SEVERITY_CRIT

extern void *secure_eip_ipc_log_norm;
extern void *secure_eip_ipc_log_prio;

#define __eip_debugfs_eip_log_msg(ipcbuf, fmt, args...)                        \
	do {                                                                   \
		void *__buf = (ipcbuf);                                        \
		if (__buf)                                                     \
			ipc_log_string(__buf, " %s:%d " fmt "\n", __func__,    \
				       __LINE__, ##args);                      \
	} while (0)

#define eip_logdbg(fmt, args...)                                               \
	do {                                                                   \
		pr_debug(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ##args);  \
		__eip_debugfs_eip_log_msg(secure_eip_ipc_log_norm, "DBG:" fmt, \
					  ##args);                             \
	} while (0)

#define eip_logerr(fmt, args...)                                               \
	do {                                                                   \
		pr_err(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ##args);    \
		__eip_debugfs_eip_log_msg(secure_eip_ipc_log_norm, "ERR:" fmt, \
					  ##args);                             \
		__eip_debugfs_eip_log_msg(secure_eip_ipc_log_prio,             \
					  "CRIT:" fmt, ##args);                \
	} while (0)

#define eip_loginfo(fmt, args...)                                              \
	do {                                                                   \
		pr_info(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ##args);   \
		__eip_debugfs_eip_log_msg(secure_eip_ipc_log_norm,             \
					  "INFO:" fmt, ##args);                \
	} while (0)

#define eip_logcrit(fmt, args...)                                              \
	do {                                                                   \
		pr_crit(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ##args);   \
		__eip_debugfs_eip_log_msg(secure_eip_ipc_log_norm,             \
					  "CRIT:" fmt, ##args);                \
		__eip_debugfs_eip_log_msg(secure_eip_ipc_log_prio,             \
					  "CRIT:" fmt, ##args);                \
	} while (0)

#define eip_logwarn(fmt, args...)                                              \
	do {                                                                   \
		pr_warn(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ##args);   \
		__eip_debugfs_eip_log_msg(secure_eip_ipc_log_norm,             \
					  "WARN:" fmt, ##args);                \
		__eip_debugfs_eip_log_msg(secure_eip_ipc_log_prio,             \
					  "WARN:" fmt, ##args);                \
	} while (0)

int eip_log_init(void);
void eip_log_deinit(void);

#endif // _EIP_LOG_H
