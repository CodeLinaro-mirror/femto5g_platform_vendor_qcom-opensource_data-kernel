//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022-2024 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>
#include <linux/init.h>

#include "mtip_workq.h"
#include "mtip.h"
#include "mtip_device.h"
#include "mtip_dma.h"
#include "mtip_client.h"
#include "mtip_ptp.h"
#include "mtip_platform.h"
#include "mtip_phy.h"

static void mtip_workq_handler(struct work_struct *w);

static int mtip_workq_list_initialize(u32 port_type);
static int mtip_workq_list_finalize(u32 port_type);
static int mtip_workq_list_size(u32 port_type);
static int mtip_workq_list_push(unsigned int work_type, void* work_ptr, u32 port_type);
static int mtip_workq_list_pop(unsigned int* work_type, void** work_ptr, u32 port_type);

static struct mtip_workq_struct mtip_wq_array[MTIP_PORT_TYPE_MAX] = {0};

static struct mtip_workq_list* mtip_workq_head[MTIP_PORT_TYPE_MAX] = {NULL};

struct workqueue_struct *delayed_wq = NULL;
struct mutex delayed_wq_mutex_lock;
extern struct mtip_delayed_work_q_params *delayed_wq_notifr_param;

#define MTIP_WORKQ_NAME_PREFIX      "mtip_workq"
#define MTIP_WORKQ_NAME_MAX_LEN     20

static void mtip_workq_handler(struct work_struct *w)
{
   int i;
   int tasks = 0;
   unsigned int     work_type;
   void*            work_ptr;
   struct mtip_workq_struct *wq_struct = container_of(w, struct mtip_workq_struct, work);
   u32 port_type;

   if(!wq_struct)
      return;

   port_type = wq_struct->port_type;

   tasks = mtip_workq_list_size(port_type);

   // handle tasks queued to the workq
   CSMLOGDBG("workq handler running with %d tasks pending\n", tasks);

   for (i = 0; i < tasks; ++i)
   {
      mtip_workq_list_pop(&work_type, &work_ptr, port_type);

      CSMLOGDBG("going to run work_type: %d\n", work_type);

      switch (work_type) 
      {
      case MTIP_WORKQ_TASK_NOP:
         break;
      case MTIP_WORKQ_TASK_INDICATE_READY:
          {
              run_mtip_client_send_ready(work_ptr);
          }
          break;
      case MTIP_WORKQ_TASK_TX_COMP_CB:
          {
              //run_mtip_tx_comp_cb(work_ptr);
          }
          break;
      case MTIP_WORKQ_TASK_PROCESS_TIMESTAMP:
          {
              run_mtip_process_timestamp(work_ptr);
          }
          break;
      case MTIP_WORKQ_TASK_PROCESS_LINK_STATE:
          {
              run_mtip_process_link_state(work_ptr);
          }
          break;
      case MTIP_WORKQ_TASK_PROCESS_LANE_UP:
          {
              run_mtip_process_lane_up(work_ptr);
          }
          break;
      case MTIP_WORKQ_TASK_PROCESS_LANE_DOWN:
          {
              run_mtip_process_lane_down(work_ptr);
          }
          break;
      case MTIP_WORKQ_TASK_PROCESS_CDR_LOCK_IND:
          {
              run_mtip_process_cdr_lock_ind(work_ptr);
          }
          break;
      case MTIP_WORKQ_TASK_CREATE_PHYLINK:
          {
              run_mtip_process_create_phylink(work_ptr);
          }
          break;
      case MTIP_WORKQ_TASK_PROCESS_PORT_CONFIGURATION_USING_LANE:
          {
              run_mtip_process_configure_port_using_lane(work_ptr);
          }
          break;
      case MTIP_WORKQ_TASK_PROCESS_PORT_CONFIGURATION_USING_LINK:
          {
              run_mtip_process_configure_port_using_link(work_ptr);
          }
          break;
      case MTIP_WORKQ_TASK_PROCESS_AN_RESULT:
          {
              run_mtip_process_an_result(work_ptr);
          }
          break;
      case MTIP_WORKQ_TASK_PROCESS_NETDEV_OPEN:
          {
              run_mtip_process_netdev_open(work_ptr);
          }
          break;
      case MTIP_WORKQ_TASK_PROCESS_NETDEV_CLOSE:
          {
              run_mtip_process_netdev_close(work_ptr);
          }
          break;
      case MTIP_WORKQ_TASK_PROCESS_RECONFIGURE_PORT:
          {
              run_mtip_process_reconfigure_port(work_ptr);
          }
          break;
      case MTIP_WORKQ_TASK_PROCESS_NEXT_SPEED_MODE:
          {
              run_mtip_process_next_speed_mode(work_ptr);
          }
          break;
      case MTIP_WORKQ_TASK_PROCESS_RETRY_PHY_BRINGUP:
          {
              run_mtip_phy_retry_bringup(work_ptr);
          }
          break;
      default:
         {
            CSMLOGERR("Unknown task type: %d\n", work_type);
         }
         break;
      }
   }
}

int mtip_queue_work(unsigned int work_type, void* work_ptr, u32 port_type)
{
   int rv = 0;

   if(port_type >= MTIP_PORT_TYPE_MAX)
      return -1;

   if (mtip_wq_array[port_type].mtip_wq)
   {
      rv = mtip_workq_list_push(work_type, work_ptr, port_type);

      if (rv >= 0)
      {
         // queue to do work
         queue_work(mtip_wq_array[port_type].mtip_wq, &mtip_wq_array[port_type].work);
      }
   }
   else
   {
      CSMLOGERR("mtip_wq not initialized!\n");
      rv = -1;
   }
   return rv;
}

int mtip_initialize_workq(void)
{
   int retval = 0;
   u32 port_type;
   char wq_name[MTIP_WORKQ_NAME_MAX_LEN] = {0};

   for(port_type = MTIP_PORT_TYPE_FH_0; port_type < MTIP_PORT_TYPE_MAX; port_type++){

      if (!mtip_wq_array[port_type].mtip_wq) {

         // allocate the space for the head
         mtip_workq_head[port_type] = (struct mtip_workq_list *)kmalloc(sizeof(struct mtip_workq_list), GFP_KERNEL);

         // HANDLE THE ERROR
         if (mtip_workq_head[port_type] == NULL)
         {
            retval = -ENOMEM;
            goto cleanup;
         }

         // initialize the queue of tasks
         mtip_workq_list_initialize(port_type);

         snprintf(wq_name, sizeof(wq_name), "%s_%d", MTIP_WORKQ_NAME_PREFIX, port_type);

         // create the workq
         mtip_wq_array[port_type].mtip_wq = alloc_workqueue(wq_name,  WQ_MEM_RECLAIM | WQ_UNBOUND | WQ_SYSFS | WQ_HIGHPRI, 1);

         // HANDLE THE ERROR
         if (mtip_wq_array[port_type].mtip_wq == NULL)
         {
            retval = -ENOMEM;
            goto cleanup;
         }

         mtip_wq_array[port_type].port_type = port_type;

         INIT_WORK(&mtip_wq_array[port_type].work, mtip_workq_handler);

      }
   }

   mutex_init(&delayed_wq_mutex_lock);
   delayed_wq = create_singlethread_workqueue("mtip_delayed_workq");

   goto out;

cleanup:
   for(port_type = MTIP_PORT_TYPE_FH_0; port_type < MTIP_PORT_TYPE_MAX; port_type++){

      if (mtip_workq_head[port_type]) {
         kfree(mtip_workq_head[port_type]);
         mtip_workq_head[port_type] = NULL;
      }

      if (mtip_wq_array[port_type].mtip_wq) {
         destroy_workqueue(mtip_wq_array[port_type].mtip_wq);
         mtip_wq_array[port_type].mtip_wq = NULL;
      }
   }

out:
   return retval;
}

int mtip_destroy_workq(void)
{
   u32 port_type;

   for(port_type = MTIP_PORT_TYPE_FH_0; port_type < MTIP_PORT_TYPE_MAX; port_type++){

      if (mtip_wq_array[port_type].mtip_wq) {
         destroy_workqueue(mtip_wq_array[port_type].mtip_wq);
         mtip_wq_array[port_type].mtip_wq = NULL;

         // finalize the queue of tasks
         mtip_workq_list_finalize(port_type);

         // free the task list head
         if (mtip_workq_head[port_type] != NULL)
         {
            kfree(mtip_workq_head[port_type]);
            mtip_workq_head[port_type] = NULL;
         }

      }
   }

   mutex_lock(&delayed_wq_mutex_lock);

   //flush and cancel delayed work
   cancel_delayed_work(&delayed_wq_notifr_param->wq_item);
   flush_delayed_work(&delayed_wq_notifr_param->wq_item);

   flush_workqueue(delayed_wq);
   destroy_workqueue(delayed_wq);
   delayed_wq = NULL;

   mutex_unlock(&delayed_wq_mutex_lock);
   mutex_destroy(&delayed_wq_mutex_lock);

   return 0;
}

int mtip_workq_list_initialize(u32 port_type)
{
   // initialize the head
   INIT_LIST_HEAD(&mtip_workq_head[port_type]->head);

   mtip_workq_head[port_type]->count = 0;

   spin_lock_init(&mtip_workq_head[port_type]->lock);
   return 0;
}

int mtip_workq_list_finalize(u32 port_type)
{
   // go through all the packets and pop them
   // free the memory allocations
   unsigned int     work_type;
   void*            work_ptr;
   struct mtip_send_ready_task* taskstruct = NULL;

   while(mtip_workq_list_size(port_type))
   {
      mtip_workq_list_pop(&work_type, &work_ptr, port_type);
      taskstruct = (struct mtip_send_ready_task*)work_ptr;
      kfree(taskstruct);
   }

   return 0;
}

int mtip_workq_list_size(u32 port_type)
{
   int rv;
   unsigned long flags;
   spinlock_t *lock = &(mtip_workq_head[port_type]->lock);

   spin_lock_irqsave(lock, flags);

   rv = mtip_workq_head[port_type]->count;

   spin_unlock_irqrestore(lock, flags);
   return rv;
}

int mtip_workq_list_push(unsigned int work_type, void* work_ptr, u32 port_type)
{
   int rv = 0;
   struct mtip_workq_node* node = NULL;
   unsigned long flags;
   spinlock_t *lock = &(mtip_workq_head[port_type]->lock);

   // allocate a workq node
   node = kmalloc(sizeof(struct mtip_workq_node), GFP_ATOMIC);

   // HANDLE THE ERROR
   if (node == NULL) 
   {
      rv = -ENOMEM;
      goto out;
   }

   // init the list
   INIT_LIST_HEAD(&node->list);

   // copy the pkt pointer
   node->work_type = work_type;
   node->work_ptr = work_ptr;

   spin_lock_irqsave(lock, flags);

   list_add_tail(&node->list, &mtip_workq_head[port_type]->head);
   ++mtip_workq_head[port_type]->count;

   spin_unlock_irqrestore(lock, flags);

out:
   return rv;
}

int mtip_workq_list_pop(unsigned int* work_type, void** work_ptr, u32 port_type)
{
   int rv = 0;
   struct mtip_workq_node* tmp;
   unsigned long flags;
   spinlock_t *lock = &(mtip_workq_head[port_type]->lock);

   rv = mtip_workq_list_size(port_type);

   if (rv <= 0)
   {
      return -1;
   }

   spin_lock_irqsave(lock, flags);

   // get the first entry
   tmp = list_entry(mtip_workq_head[port_type]->head.next, struct mtip_workq_node, list);

   if (!list_empty(&mtip_workq_head[port_type]->head)) 
   {
      // delete the head
      list_del(&tmp->list);

      --mtip_workq_head[port_type]->count;
   }
   else {
      rv = -1;
   }

   spin_unlock_irqrestore(lock, flags);

   if (rv == -1) 
   {
      CSMLOGERR("workq list is empty... mismatch with count\n");
   }
   else
   {
      *work_type = tmp->work_type;
      *work_ptr = tmp->work_ptr;

      // free the node
      kfree(tmp);
   }
   return rv;
}

int mtip_workq_queue_delayed_work(struct mtip_delayed_work_q_params *wq_params, int delay_ms)
{
   queue_delayed_work(delayed_wq, &wq_params->wq_item, msecs_to_jiffies(delay_ms));
   return 0;
}

