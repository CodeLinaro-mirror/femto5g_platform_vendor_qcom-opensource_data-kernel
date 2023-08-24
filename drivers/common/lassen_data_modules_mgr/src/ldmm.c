/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/ioctl.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/delay.h>

#include "ldmm_shrd_genntlk.h"
#include "ldmm_shrd_notifr.h"
#include "ldmm_ipc_log.h"
#include "ldmm.h"

#define LDMM_IPC_LOG_PAGES   50

lddm_core_context_info_s ldmm_core_context_g;

static int __init lassen_data_modules_mgr_init(void)
{
        LDMM_LOG_INFO("lassen_data_modules_mgr_init()\n");
	ldmm_core_context_g.ldmm_logbuf =
		ipc_log_context_create(LDMM_IPC_LOG_PAGES, "ldmm", 0);

        if(init_genlldmm()){
		pr_err("ldmm: Generic netlink init failed \n");
		goto out1;
	}
	if(ldmm_fault_notifr_init()){
		pr_err("ldmm: Kernel Notifier chain registration failed\n");
		goto out2;
	}
	return 0;
out2:
	exit_genlldmm();
out1:
	if(ldmm_core_context_g.ldmm_logbuf)
		ipc_log_context_destroy(ldmm_core_context_g.ldmm_logbuf);


	return -1;
}
static void __exit lassen_data_modules_mgr_exit(void){
	LDMM_LOG_INFO("exiting LDMM\n");

	if(ldmm_core_context_g.ldmm_logbuf)
		ipc_log_context_destroy(ldmm_core_context_g.ldmm_logbuf);
	exit_genlldmm();
	ldmm_fault_notifr_exit();

	pr_info("ldmm exit complete\n");
	return;
}
MODULE_LICENSE("GPL");
module_init(lassen_data_modules_mgr_init);
module_exit(lassen_data_modules_mgr_exit);
