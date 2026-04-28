//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022-2024 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#ifndef _MTIP_WORKQ_H
#define _MTIP_WORKQ_H

#include <linux/slab.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>
#include "eth_phy_iface.h"

// enumeration of the list of tasks handled by the workq
typedef enum {
   MTIP_WORKQ_TASK_NOP = 0,
   MTIP_WORKQ_TASK_INDICATE_READY = 50,
   MTIP_WORKQ_TASK_TX_COMP_CB,
   MTIP_WORKQ_TASK_PROCESS_TIMESTAMP = 150,
   MTIP_WORKQ_TASK_PROCESS_LINK_STATE,
   MTIP_WORKQ_TASK_PROCESS_LANE_UP,
   MTIP_WORKQ_TASK_PROCESS_LANE_DOWN,
   MTIP_WORKQ_TASK_PROCESS_CDR_LOCK_IND,
   MTIP_WORKQ_TASK_CREATE_PHYLINK = 160,
   MTIP_WORKQ_TASK_PROCESS_PORT_CONFIGURATION_USING_LANE,
   MTIP_WORKQ_TASK_PROCESS_PORT_CONFIGURATION_USING_LINK,
   MTIP_WORKQ_TASK_PROCESS_AN_RESULT,
   MTIP_WORKQ_TASK_PROCESS_NETDEV_OPEN,
   MTIP_WORKQ_TASK_PROCESS_NETDEV_CLOSE,
   MTIP_WORKQ_TASK_PROCESS_RECONFIGURE_PORT,
   MTIP_WORKQ_TASK_PROCESS_NEXT_SPEED_MODE,
   MTIP_WORKQ_TASK_PROCESS_RETRY_PHY_BRINGUP,
   MTIP_WORKQ_TASK_PROCESS_LOOPBACK_CONFIG,
   MTIP_WORKQ_TASK_MAX
} mtip_workq_task_e;

struct mtip_workq_node
{
   struct list_head list;
   unsigned int     work_type;
   void*            work_ptr;
};

struct mtip_workq_list
{
   struct list_head head;
   unsigned int count;
   spinlock_t lock;
};

struct mtip_workq_struct
{
   struct workqueue_struct    *mtip_wq;
   struct work_struct          work;
   u32                         port_type;
};

/* Work structure to be passed to work queue for deferred processing */
struct mtip_delayed_work_q_params{
   struct delayed_work                    wq_item;
   u32                                    link_index;
   void                                  *user_data;
};

/*
 * mtip workq related functions
 */
int mtip_queue_work(unsigned int work_type, void* work_ptr, u32 port_type);
int mtip_initialize_workq(void);
int mtip_destroy_workq(void);
int mtip_workq_queue_delayed_work(struct mtip_delayed_work_q_params *wq_params, int delay_ms);

#endif // _MTIP_WORKQ_H
