
/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _ECPRI_H
#define _ECPRI_H
#include <linux/kernel.h>
#include <linux/printk.h> /* printk */
#include <linux/ipc_logging.h> /* ipc_logging */
#include "ecpri_oxtor_core.h"
#define DRV_NAME "ecpri_oxtor" /* driver name */

#define ECPRI_IPC_LOGGING(buf, fmt, args...) \
        do { \
                if (buf) \
                        ipc_log_string((buf), fmt, __func__, __LINE__, \
                                ## args); \
        } while (0)

#define ECPRISS_OXTOR_LOG_DBG(fmt, args...) \
        do { \
                pr_debug(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ## args);\
        } while (0)

#define ECPRISS_OXTOR_LOG_ERR(fmt, args...) \
        do { \
		if(ecpri_oxtor_core_context->ecpri_oxtor_logbuf) \
			ECPRI_IPC_LOGGING(ecpri_oxtor_core_context->ecpri_oxtor_logbuf, \
						DRV_NAME " %s:%d " fmt, ## args); \
        } while (0)
#define ECPRISS_OXTOR_LOG_INFO(fmt, args...) \
        do { \
		if(ecpri_oxtor_core_context->ecpri_oxtor_logbuf) \
			ECPRI_IPC_LOGGING(ecpri_oxtor_core_context->ecpri_oxtor_logbuf, \
						DRV_NAME " %s:%d " fmt, ## args); \
        } while (0)

#endif
