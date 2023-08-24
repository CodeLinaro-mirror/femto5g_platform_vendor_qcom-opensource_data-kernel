
/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _LDMM_IPC_LOG_H
#define _LDMM_IPC_LOG_H

#include <linux/kernel.h>
#include <linux/printk.h> /* printk */
#include <linux/ipc_logging.h> /* ipc_logging */
#include "ldmm.h"

#define DRV_NAME "ldmm" /* driver name */

#define LDMM_IPC_LOGGING(buf, fmt, args...) \
        do { \
                if (buf) \
                        ipc_log_string((buf), fmt, __func__, __LINE__, \
                                ## args); \
        } while (0)

#define LDMM_LOG_DBG(fmt, args...) \
        do { \
                pr_debug(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ## args);\
        } while (0)

#define LDMM_LOG_ERR(fmt, args...) \
        do { \
		if(ldmm_core_context_g.ldmm_logbuf ) \
			LDMM_IPC_LOGGING(ldmm_core_context_g.ldmm_logbuf , \
						DRV_NAME " %s:%d " fmt, ## args); \
        } while (0)
#define LDMM_LOG_INFO(fmt, args...) \
        do { \
		if(ldmm_core_context_g.ldmm_logbuf ) \
			LDMM_IPC_LOGGING(ldmm_core_context_g.ldmm_logbuf , \
						DRV_NAME " %s:%d " fmt, ## args); \
        } while (0)

#endif /* _LDMM_IPC_LOG_H */
