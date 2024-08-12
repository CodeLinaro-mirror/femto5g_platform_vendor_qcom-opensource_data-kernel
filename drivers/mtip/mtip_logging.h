//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022-2024 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#ifndef	_CSM_LOGGING_H
#define	_CSM_LOGGING_H


#include <linux/ipc_logging.h>
#include "mtip.h"

#define CSM_IPC_LOG_PAGES 50

#define CSM_IPC_Log(buf, fmt, args...) \
do {\
     if (buf) \
			ipc_log_string((buf), fmt, __func__, __LINE__, ## args); \
} while (0)

#define CSMLOGDBG(fmt, args...) \
do {\
	pr_debug(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ## args); \
    if (mtip_ethtool_debug_logging_enable) {\
            pr_err(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ## args);\
            if (platform_driver_priv) {\
                CSM_IPC_Log(platform_driver_priv->ipc_log_buf_dbg , \
                            DRV_NAME " %s:%d " fmt, ## args); \
            } \
        } \
} while (0)

#define CSMLOGERR(fmt, args...) \
do {\
	pr_err(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ## args);\
    if (platform_driver_priv) {\
			CSM_IPC_Log(platform_driver_priv->ipc_log_buf , \
				DRV_NAME " %s:%d " fmt, ## args); \
        } \
} while (0)

#define CSMLOGINFO(fmt, args...) \
do {\
	pr_info(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ## args);\
    if (mtip_ethtool_debug_logging_enable) {\
            pr_err(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ## args);\
        } \
    if (platform_driver_priv) { \
			CSM_IPC_Log(platform_driver_priv->ipc_log_buf_low , \
				DRV_NAME " %s:%d " fmt, ## args); \
        } \
} while (0)

#define CSMLOGPTP(fmt, args...) \
do {\
    if (mtip_ethtool_debug_logging_enable) {\
        if (platform_driver_priv) {\
	    CSM_IPC_Log(platform_driver_priv->ipc_ptp_log_buf , \
		DRV_NAME " %s:%d " fmt, ## args); \
        } \
   } \
} while (0)
#endif // _CSM_LOGGING_H
