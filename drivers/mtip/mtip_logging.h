//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#ifndef	_CSM_LOGGING_H
#define	_CSM_LOGGING_H

#define CSMLOGDBG(fmt, args...) \
do {\
	pr_debug(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ## args);\
} while (0)

#define CSMLOGERR(fmt, args...) \
do {\
	pr_err(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ## args);\
} while (0)

#define CSMLOGINFO(fmt, args...) \
do {\
	pr_info(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ## args);\
} while (0)

#endif // _CSM_LOGGING_H
