/***************************************************************************

Copyright (c) 2019-2021 The Linux Foundation. All rights reserved.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License version 2 and
only version 2 as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.


**************************************************************************/

/***************************************************************************
*
* File: DWC_ETH_QOS_ipc.h
* Header file to define log apis for dwc eth driver debugging
*
***************************************************************************/

#include <linux/ipc_logging.h>
#include <linux/ratelimit.h>

extern void *ipc_emac_log_ctxt;
extern void *ipc_emac_log_ctxt_low;
#define IPC_RATELIMIT_BURST 1
#define WARNON_RATELIMIT_BURST 1

#define IPCLOG_STATE_PAGES 50
#define __FILENAME__ (strrchr(__FILE__, '/') ? \
	strrchr(__FILE__, '/') + 1 : __FILE__)

#define EMACDBG(fmt, args...) \
do {\
	pr_debug(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ## args);\
	if (ipc_emac_log_ctxt) { \
		ipc_log_string(ipc_emac_log_ctxt, \
		"%s: %s[%u]:[emac] DEBUG:" fmt, __FILENAME__ , \
		__func__, __LINE__, ## args); \
	} \
}while(0)
#define EMACINFO(fmt, args...) \
do {\
	pr_info(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ## args);\
	if (ipc_emac_log_ctxt) { \
		ipc_log_string(ipc_emac_log_ctxt, \
		"%s: %s[%u]:[emac] INFO:" fmt, __FILENAME__ , \
		__func__, __LINE__, ## args); \
	} \
}while(0)
#define EMACERR(fmt, args...) \
do {\
	pr_err(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ## args);\
	if (ipc_emac_log_ctxt) { \
		ipc_log_string(ipc_emac_log_ctxt, \
		"%s: %s[%u]:[emac] ERROR:" fmt, __FILENAME__ , \
		__func__, __LINE__, ## args); \
	} \
}while(0)

#define EMACKPI(fmt, args...) \
do {\
	pr_info_once(DRV_NAME " %s:%d" fmt, __func__, __LINE__, ## args);\
	if (ipc_emac_log_ctxt) { \
		ipc_log_string(ipc_emac_log_ctxt, \
		"KPI %s[%u]:" fmt, __func__, __LINE__, ## args); \
	} \
}while(0)

#define IPC_LOW(fmt, args...) \
do {\
	pr_info(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ## args);\
	if (ipc_emac_log_ctxt_low) { \
		ipc_log_string(ipc_emac_log_ctxt_low, \
		"%s: %s[%u]:[ipc] DEBUG:" fmt, __FILENAME__ , \
		__func__, __LINE__, ## args); \
	} \
}while(0)

/*
	Printing one warning message in 5 seconds if multiple warning messages
	are coming back to back.
*/
#define WARN_ON_RATELIMIT_IPC(condition) \
({ \
	static DEFINE_RATELIMIT_STATE(_rs, DEFAULT_RATELIMIT_INTERVAL, WARNON_RATELIMIT_BURST); \
	int rtn = !!(condition); \
	if (unlikely(rtn && __ratelimit(&_rs))) \
		WARN_ON(rtn); \
})

/*
	Printing one error message in 5 seconds if multiple error messages
	are coming back to back.
*/
#define pr_err_ratelimited_ipc(fmt, ...) \
	printk_ratelimited_ipc(KERN_ERR pr_fmt(fmt), ##__VA_ARGS__)
#define printk_ratelimited_ipc(fmt, ...) \
({ \
	static DEFINE_RATELIMIT_STATE(_rs, DEFAULT_RATELIMIT_INTERVAL, IPC_RATELIMIT_BURST); \
	if (__ratelimit(&_rs)) \
		printk(fmt, ##__VA_ARGS__); \
})
#define IPCERR_RL(fmt, args...) \
do { \
	pr_err_ratelimited_ipc(DRV_NAME " %s:%d " fmt, __func__,\
	__LINE__, ## args);\
	if (ipc_emac_log_ctxt) { \
		ipc_log_string(ipc_emac_log_ctxt, \
		"%s: %s[%u]:[emac] Error:" fmt, __FILENAME__ , \
		__func__, __LINE__, ## args); \
	} \
} while (0)

