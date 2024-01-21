//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022-2024 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef LOG_IMPL_H
#define LOG_IMPL_H

#include "eip_log.h"

#ifdef LOG_SEVERITY_MAX
#undef LOG_SEVERITY_MAX
#define LOG_SEVERITY_MAX LOG_SEVERITY_CRIT
#else
#define LOG_SEVERITY_MAX LOG_SEVERITY_CRIT
#endif

#define Log_Message eip_logdbg
#define Log_FormattedMessage eip_logdbg

#define Log_FormattedMessageINFO eip_loginfo
#define Log_FormattedMessageWARN eip_logwarn
#define Log_FormattedMessageCRIT eip_logcrit

#endif /* LOG_IMPL_H */
