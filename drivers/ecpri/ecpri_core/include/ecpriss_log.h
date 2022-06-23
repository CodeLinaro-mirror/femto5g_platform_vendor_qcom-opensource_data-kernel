/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#define DRIVER_NAME             "ecpriss_core"

#define ECPRISS_CORE_DEBUG(fmt, args...) \
	do { \
		pr_debug(DRIVER_NAME " %s:%d "\
				fmt, __func__, __LINE__, ## args);\
#if 0
		if (ecpriss_core_logbuf) { \
			ECPRISS_CORE_IPC_LOGGING(ecpriss_core_logbuf, \
					DRIVER_NAME " %s:%d " fmt, ## args); \
		} \
#endif
	} while (0)


#define ECPRISS_CORE_INFO(fmt, args...) \
	do { \
		pr_info(DRIVER_NAME "@%s@%d@ctx:%s: "\
			fmt, __func__, __LINE__, current->comm, ## args);\
#if 0
		if (ecpriss_core_logbuf) { \
			ECPRISS_CORE_IPC_LOGGING(ecpriss_core_logbuf, \
				DRIVER_NAME " %s:%d " fmt, ## args); \
		} \
#endif
	} while (0)

#define ECPRISS_CORE_ERROR(fmt, args...) \
	do { \
		pr_err(DRIVER_NAME "@%s@%d@ctx:%s: "\
			fmt, __func__, __LINE__, current->comm, ## args);\
#if 0
		if (ecpriss_core_logbuf) { \
			ECPRISS_CORE_IPC_LOGGING(ecpriss_core_logbuf, \
					DRIVER_NAME " %s:%d " fmt, ## args); \
		} \
#endif
	} while (0)

#define NULL_CHECK(ptr) \
	do { \
		if (!(ptr)) { \
			ECPRISS_CORE_ERROR("null pointer #ptr\n"); \
			ret = -EINVAL; \
		} \
	} \
	while (0)
