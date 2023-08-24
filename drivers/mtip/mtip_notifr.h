//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _MTIP_NOTIF_H
#define _MTIP_NOTIF_H

#include <linux/slab.h>
#include <linux/notifier.h>
#include <linux/export.h>
#include "mtip_workq.h"
#include "ldmm_notifr.h"

#define MTIP_NOTIFY_TIMER          1000

void mtip_fault_notifr_status(struct work_struct *work);
int mtip_fault_notifr_init(void);
void mtip_snd_event_notification(uint32_t interface, uint32_t event);

#endif /* _MTIP_NOTIF_H */
