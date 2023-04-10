/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _ECPRI_H
#define _ECPRI_H
#include <linux/kernel.h>
#include <linux/printk.h> /* printk */
#include <linux/ipc_logging.h> /* ipc_logging */
#include "ecpriss_core.h"
#define DRV_NAME "ecpri" /* driver name */

#define ECPRI_IPC_LOGGING(buf, fmt, args...) \
        do { \
                if (buf) \
                        ipc_log_string((buf), fmt, __func__, __LINE__, \
                                ## args); \
        } while (0)

#define ECPRILOGDBG(fmt, args...) \
        do { \
                pr_debug(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ## args);\
        } while (0)

#define ECPRILOGERR(fmt, args...) \
        do { \
                pr_err(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ## args);\
		if( ecpriss_hw_ver == ECPRISS_HW_v1_0){ \
			if (ecpriss_pdata) { \
				ECPRI_IPC_LOGGING(ecpriss_pdata -> ecpriss_core_logbuf, \
						DRV_NAME " %s:%d " fmt, ## args); \
			} \
		} else {\
			if (ecpriss_pdata) { \
				ECPRI_IPC_LOGGING(ecpriss_pdata_v2 -> ecpriss_core_logbuf, \
						DRV_NAME " %s:%d " fmt, ## args); \
			} \
		}\
        } while (0)
#define ECPRILOGINFO(fmt, args...) \
        do { \
                pr_info(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ## args);\
		if( ecpriss_hw_ver == ECPRISS_HW_v1_0){ \
			if (ecpriss_pdata) { \
				ECPRI_IPC_LOGGING(ecpriss_pdata -> ecpriss_core_logbuf, \
						DRV_NAME " %s:%d " fmt, ## args); \
			} \
		} \
		else {\
			if (ecpriss_pdata_v2) { \
				ECPRI_IPC_LOGGING(ecpriss_pdata_v2 -> ecpriss_core_logbuf, \
						DRV_NAME " %s:%d " fmt, ## args); \
			} \
		}\
        } while (0)
#define ECPRILOGCFG(fmt, args...) \
        do { \
		if( ecpriss_hw_ver == ECPRISS_HW_v1_0){ \
			if (ecpriss_pdata) { \
				ECPRI_IPC_LOGGING(ecpriss_pdata -> ecpriss_core_cfg_logbuf, \
						DRV_NAME " %s:%d " fmt, ## args); \
			} \
		} \
		else{\
			if (ecpriss_pdata_v2) { \
				ECPRI_IPC_LOGGING(ecpriss_pdata_v2 -> ecpriss_core_cfg_logbuf, \
						DRV_NAME " %s:%d " fmt, ## args); \
			} \
		}\
	} while (0)

#endif
