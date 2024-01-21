/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _LDMM_NOTIFIER_H
#define _LDMM_NOTIFIER_H

#include "ldmm_notifr.h"

void ldmm_enable_notification(void);
void ldmm_disable_notification(void);
int ldmm_qxdm_logger_link_change_notification(event_info_struct *event_info, int link_up);

int ldmm_fault_notifr_init(void);
int ldmm_fault_notifr_exit(void);

int ldmm_qxdm_timer_update_notifr_init(void);
int ldmm_qxdm_timer_update_notifr_exit(void);

#endif /* _LDMM_NOTIFIER_H */
