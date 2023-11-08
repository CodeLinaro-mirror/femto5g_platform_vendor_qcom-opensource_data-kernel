/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */
#ifndef _LDMM_SHRD_GENL_H
#define _LDMM_SHRD_GENL_H

#include <net/genetlink.h>
#include "ldmm_genl.h"

enum{
	UNICAST_MSG = 0,
	MULTICAST_MSG,
	MAX_MSG_TYPE = 4,
};

int init_genlldmm(void);
void exit_genlldmm(void);
int fult_mgmt_snd(uint32_t buf, int mode);

// LDMM QXDM LOGGER Netlink APIs
int ldmm_qxdm_logger_get_stats_info(struct sk_buff *sender_skb, struct genl_info *info);
int ldmm_qxdm_logger_get_config_info(struct sk_buff *sender_skb, struct genl_info *info);
int ldmm_qxdm_logger_no_action(struct sk_buff *sender_skb, struct genl_info *info);

#endif /* _LDMM_SHRD_GENL_H */
