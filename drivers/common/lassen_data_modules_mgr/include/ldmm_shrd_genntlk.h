/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */
#ifndef _LDMM_SHRD_GENL_H
#define _LDMM_SHRD_GENL_H

#include "ldmm_genl.h"

enum{
	UNICAST_MSG = 0,
	MULTICAST_MSG,
	MAX_MSG_TYPE = 4,
};

int init_genlldmm(void);
void exit_genlldmm(void);
int fult_mgmt_snd(uint32_t buf, int mode);

#endif /* _LDMM_SHRD_GENL_H */
