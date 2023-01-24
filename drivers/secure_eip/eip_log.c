//SPDX-License-Identifier: GPL-2.0-only

/*
* Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
*/

#include "eip_log.h"

#define EIP_IPC_LOG_PAGES 50

void *secure_eip_ipc_log_norm = NULL;
void *secure_eip_ipc_log_prio = NULL;

int eip_log_init(void)
{
	secure_eip_ipc_log_norm = ipc_log_context_create(
		EIP_IPC_LOG_PAGES, "secure_eip_log_norm", 0);
	if (!secure_eip_ipc_log_norm) {
		pr_err("seure_eip: Failed to create IPC log context\n");
		return -EINVAL;
	}

	secure_eip_ipc_log_prio = ipc_log_context_create(
		EIP_IPC_LOG_PAGES, "secure_eip_log_prio", 0);
	if (!secure_eip_ipc_log_prio) {
		pr_err("seure_eip: Failed to create IPC log context\n");
		ipc_log_context_destroy(secure_eip_ipc_log_norm);
		secure_eip_ipc_log_norm = NULL;
		return -EINVAL;
	}

	return 0;
}

void eip_log_deinit(void)
{
	eip_loginfo("De-initializing EIP logging!\n");
	if (secure_eip_ipc_log_norm) {
		ipc_log_context_destroy(secure_eip_ipc_log_norm);
		secure_eip_ipc_log_norm = NULL;
	}
	if (secure_eip_ipc_log_prio) {
		ipc_log_context_destroy(secure_eip_ipc_log_prio);
		secure_eip_ipc_log_prio = NULL;
	}
}
