/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _LDMM_H
#define _LDMM_H

typedef struct lddm_core_context_info{
	void *ldmm_logbuf;
}lddm_core_context_info_s;

extern lddm_core_context_info_s ldmm_core_context_g;

#endif /* _LDMM_H */
