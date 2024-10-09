/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _ECPRISS_WORKQ_H
#define _ECPRISS_WORKQ_H

#include <linux/slab.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>

struct ecpri_delayed_work_q_params{
   struct delayed_work                    wq_item;
   void                                  *user_data;
};

typedef void (*ecpriss_workq_cb)(void *user_data);

int ecpriss_queue_work(struct workqueue_struct	*ecpriss_wq,
		struct work_struct	*ecpriss_work);
int ecpriss_queue_delayed_work(struct delayed_work *ecpriss_delay_work, int delay_ms);

int ecpriss_initialize_workq(void);
int ecpriss_initialize_workq_v2(void);
int ecpriss_destroy_workq(void);

#endif // _DMA_WORKQ_H
