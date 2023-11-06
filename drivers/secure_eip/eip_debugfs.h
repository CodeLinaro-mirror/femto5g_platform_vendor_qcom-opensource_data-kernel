// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _EIP_DEBUGFS_H
#define _EIP_DEBUGFS_H

#include "eip_device.h"

#if CONFIG_DEBUG_FS
int eip_debugfs_init(void);
void eip_debugfs_deinit(void);
int eip_debugfs_add_port(struct eip_port *port);
void eip_debugfs_remove_port(struct eip_port *port);
int eip_debugfs_add_link(struct eip_link *link);
void eip_debugfs_remove_link(struct eip_link *link);
#else
static inline int eip_debugfs_init(void)
{
	return 0;
}
static inline void eip_debugfs_deinit(void)
{
}
static inline int eip_debugfs_add_port(struct eip_port *port)
{
	return 0;
}
static inline void eip_debugfs_remove_port(struct eip_port *port)
{
}
static int eip_debugfs_add_link(struct eip_link *link)
{
	return 0;
}
static int eip_debugfs_remove_link(struct eip_link *link)
{
}
#endif

#endif // _EIP_DEBUGFS_H