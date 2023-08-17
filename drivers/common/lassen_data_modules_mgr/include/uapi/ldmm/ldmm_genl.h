/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _LDMM_GENL_H
#define _LDMM_GENL_H

/*
 * This header includes definitions that are shared with kernel space and user
 * space. This header would be put in a place visible to user space.
 */

#define LDMM_GENL_NAME "ldmm_mgmt"
#define LDMM_GENL_VERSION 1
#define LDMM_MC_GRP_NAME "ldmm_mcgrp"

/* Attributes */
enum genlldmm_attrs {
	LDMM_A_UNSPEC,
	LDMM_A_MSG,
	__LDMM_A_MAX,
};

#define LDMM_A_MAX (__LDMM_A_MAX - 1)

/* Commands */
enum genlldmm_cmds {
	LDMM_CMD_UNSPEC,
	LDMM_CMD_FULT_MGMT_RCV,
	__LDMM_CMD_MAX,
};

typedef enum ldmm_fault{
	LDMM_HIGH_BER_SET = 0,
	LDMM_HIGH_BER_CLR,
	LDMM_PCS_IF_UP,
	LDMM_PCS_IF_DOWN,
	LDMM_IF_UP,
	LDMM_IF_DOWN,
	LDMM_INVALID = 128,
}ldmm_fault_en;

#define FAULT_NUM_MASK 0x0FF0
#define FAULT_NUM_SHIFT 4

#define LINK_ID_MASK 0xF
#define LINK_ID_SHIFT 0

#define LDMM_SETFIELD_IN_REG(reg, val, shift, mask) \
        (reg |= ((val) << (shift)) & (mask))
#define LDMM_GETFIELD_FROM_REG(reg, shift, mask) \
        (((reg) & (mask)) >> (shift))

#define LDMM_CMD_MAX (__LDMM_CMD_MAX - 1)

#define HELLO_NUM 1234

#endif /* _LDMM_GENL_H */
