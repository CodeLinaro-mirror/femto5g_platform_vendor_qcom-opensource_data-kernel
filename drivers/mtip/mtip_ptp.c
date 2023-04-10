//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#include <linux/init.h>
#include <linux/module.h>

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/gfp.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/in.h>
#include <linux/string.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/skbuff.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/bitrev.h>
#include <linux/slab.h>

#include <linux/moduleparam.h>

#include <linux/sched.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/errno.h>  /* error codes */
#include <linux/types.h>  /* size_t */
#include <linux/interrupt.h> /* mark_bh */

#include <linux/in.h>
#include <linux/netdevice.h>   /* struct device, and other headers */
#include <linux/etherdevice.h> /* eth_type_trans */
#include <linux/ip.h>          /* struct iphdr */
#include <linux/tcp.h>         /* struct tcphdr */
#include <linux/skbuff.h>

#include "mtip.h"
#include "mtip_logging.h"
#include "mtip_device.h"
#include "mtip_dma.h"
#include "mtip_mac.h"
#include "mtip_workq.h"
#include "mtip_ptp.h"

/*
 * initialize the ptp data structures for a link index
 */
int mtip_ptp_initialize(u32 link_index)
{
    mtip_ptp_tx_ts_lock_init(link_index);

    mtip_ptp_tx_ts_list_initialize(link_index);
    mtip_ptp_tx_ts_skb_list_initialize(link_index);
    return 0;
}

void mtip_ptp_finalize(u32 link_index)
{
    mtip_ptp_tx_ts_list_finalize(link_index);
    mtip_ptp_tx_ts_skb_list_finalize(link_index);
}

/**
 * Handle the hwtstamp ioctl
 */
int mtip_ptp_handle_hwtstamp_ioctl(struct ifreq *ifr, u32 link_index)
{
    struct hwtstamp_config config;

    CSMLOGDBG("hwtstamp ioctl received link_index: %d\n", link_index);

    if (copy_from_user(&config, ifr->ifr_data,
               sizeof(struct hwtstamp_config))) {
        // not able to copy from user
        return -EFAULT;
    }

    // check the flags
    if (config.flags) {
        return -EINVAL;
    }

    // check if TS is to be turned on or off
    if (config.tx_type == HWTSTAMP_TX_OFF) {

        CSMLOGDBG("Received an ioctl to disable HW Time stamping for link_index: %d\n", link_index);

        // set PTP TS disbled for the interface
        platform_driver_priv->mtip_links[link_index]->ptp_ts_enabled = false;
    }
    else if (config.tx_type == HWTSTAMP_TX_ON) {

        CSMLOGDBG("Received an ioctl to enable HW Time stamping for link_index: %d\n", link_index);

        // set PTP TS enabled for the interface
        platform_driver_priv->mtip_links[link_index]->ptp_ts_enabled = true;
    }
    else {
        return -ERANGE;
    }
    return 0;
}

void mtip_ptp_tx_ts_lock_init(u32 link_index)
{
    mutex_init(&platform_driver_priv->mtip_links[link_index]->dev_lock);
}

void mtip_ptp_tx_ts_lock_acquire(u32 link_index)
{
    mutex_lock(&platform_driver_priv->mtip_links[link_index]->dev_lock);
}

void mtip_ptp_tx_ts_lock_release(u32 link_index)
{
    mutex_unlock(&platform_driver_priv->mtip_links[link_index]->dev_lock);
}

int mtip_ptp_tx_ts_list_initialize(u32 link_index)
{
    struct mtip_tx_ts_list *listptr = &platform_driver_priv->mtip_links[link_index]->tx_ts_list;

   // initialize the head
    INIT_LIST_HEAD(&listptr->head);

   listptr->count = 0;
   return 0;
}

int mtip_ptp_tx_ts_list_finalize(u32 link_index)
{
   // go through all the packets and pop them

   // free the memory allocations
   return 0;
}

int mtip_ptp_tx_ts_list_size(u32 link_index)
{
   int rv;
   struct mtip_tx_ts_list *listptr = &platform_driver_priv->mtip_links[link_index]->tx_ts_list;

   rv = listptr->count;
   return rv;
}

int mtip_ptp_tx_ts_list_push(u32 link_index, u32 tstamp_secs, u32 tstamp_nsecs)
{
   int rv = 0;
   struct mtip_tx_ts_node* node = NULL;
   struct mtip_tx_ts_list *listptr = &platform_driver_priv->mtip_links[link_index]->tx_ts_list;

   // allocate a workq node
   node = kmalloc(sizeof(struct mtip_tx_ts_node), GFP_ATOMIC);

   // HANDLE THE ERROR
   if (node == NULL) 
   {
      rv = -ENOMEM;
      goto out;
   }

   // init the list
   INIT_LIST_HEAD(&node->list);

   node->tstamp_secs = tstamp_secs;
   node->tstamp_nsecs = tstamp_nsecs;

   list_add_tail(&node->list, &listptr->head);
   ++listptr->count;

out:
   return rv;
}

int mtip_ptp_tx_ts_list_pop(u32 link_index, u32* tstamp_secs, u32* tstamp_nsecs)
{
   int rv = 0;
   struct mtip_tx_ts_node* tmp;
   struct mtip_tx_ts_list *listptr = &platform_driver_priv->mtip_links[link_index]->tx_ts_list;

   rv = mtip_ptp_tx_ts_list_size(link_index);

   if (rv <= 0)
   {
      return -1;
   }

   // get the first entry
   tmp = list_entry(listptr->head.next, struct mtip_tx_ts_node, list);

   if (!list_empty(&listptr->head)) 
   {
      // delete the head
      list_del(&tmp->list);

      --listptr->count;
   }
   else {
      rv = -1;
   }

   if (rv == -1) 
   {
      CSMLOGERR("workq list is empty... mismatch with count\n");
   }
   else
   {
      *tstamp_secs = tmp->tstamp_secs;
      *tstamp_nsecs = tmp->tstamp_nsecs;

      // free the node
      kfree(tmp);
   }
   return rv;
}

int mtip_ptp_tx_ts_skb_list_initialize(u32 link_index)
{
    struct mtip_tx_ts_skb_list *listptr = &platform_driver_priv->mtip_links[link_index]->tx_ts_skb_list;

   // initialize the head
    INIT_LIST_HEAD(&listptr->head);

   listptr->count = 0;
   return 0;
}

int mtip_ptp_tx_ts_skb_list_finalize(u32 link_index)
{
   // go through all the packets and pop them

   // free the memory allocations
   return 0;
}

int mtip_ptp_tx_ts_skb_list_size(u32 link_index)
{
   int rv;
   struct mtip_tx_ts_skb_list *listptr = &platform_driver_priv->mtip_links[link_index]->tx_ts_skb_list;

   rv = listptr->count;
   return rv;
}

int mtip_ptp_tx_ts_skb_list_push(u32 link_index, struct sk_buff *skb)
{
   int rv = 0;
   struct mtip_tx_ts_skb_node* node = NULL;
   struct mtip_tx_ts_skb_list *listptr = &platform_driver_priv->mtip_links[link_index]->tx_ts_skb_list;

   // allocate a workq node
   node = kmalloc(sizeof(struct mtip_tx_ts_skb_node), GFP_ATOMIC);

   // HANDLE THE ERROR
   if (node == NULL) 
   {
      rv = -ENOMEM;
      goto out;
   }

   // init the list
   INIT_LIST_HEAD(&node->list);

   node->skb = skb;

   list_add_tail(&node->list, &listptr->head);
   ++listptr->count;

out:
   return rv;
}

int mtip_ptp_tx_ts_skb_list_pop(u32 link_index, struct sk_buff **skb)
{
   int rv = 0;
   struct mtip_tx_ts_skb_node* tmp;
   struct mtip_tx_ts_skb_list *listptr = &platform_driver_priv->mtip_links[link_index]->tx_ts_skb_list;

   rv = mtip_ptp_tx_ts_skb_list_size(link_index);

   if (rv <= 0)
   {
      return -1;
   }

   // get the first entry
   tmp = list_entry(listptr->head.next, struct mtip_tx_ts_skb_node, list);

   if (!list_empty(&listptr->head)) 
   {
      // delete the head
      list_del(&tmp->list);

      --listptr->count;
   }
   else {
      rv = -1;
   }

   if (rv == -1) 
   {
      CSMLOGERR("workq list is empty... mismatch with count\n");
   }
   else
   {
      *skb = tmp->skb;

      // free the node
      kfree(tmp);
   }
   return rv;
}

void post_mtip_process_timestamp(u32 link_index, u32 timestamp_secs, u32 timestamp_nsecs)
{
   struct mtip_process_timestamp_task* taskstruct = kmalloc(sizeof(struct mtip_process_timestamp_task), GFP_ATOMIC);
   taskstruct->link_index = link_index;
   taskstruct->timestamp_secs = timestamp_secs;
   taskstruct->timestamp_nsecs = timestamp_nsecs;
   mtip_queue_work(MTIP_WORKQ_TASK_PROCESS_TIMESTAMP, taskstruct);
}

void run_mtip_process_timestamp(void* work_ptr)
{
    struct mtip_process_timestamp_task* taskstruct = (struct mtip_process_timestamp_task*)work_ptr;
    u32 link_index = taskstruct->link_index;
    u32 timestamp_secs = taskstruct->timestamp_secs;
    u32 timestamp_nsecs = taskstruct->timestamp_nsecs;
    struct sk_buff* skb = NULL;

    CSMLOGDBG("process tx timestamp %d, %d\n", timestamp_secs, timestamp_nsecs);

    // bottom half of process a timestamp
    // acquire the lock
    mtip_ptp_tx_ts_lock_acquire(link_index);

    // check if there is an skb pending
    if (mtip_ptp_tx_ts_skb_list_size(link_index) == 0)
    {
        // there are no skbs pending
        // queue the timestamp
        mtip_ptp_tx_ts_list_push(link_index, timestamp_secs, timestamp_nsecs);
    }
    else
    {
        // there is a pending skb
        // set the timestamp on the skb
        mtip_ptp_tx_ts_skb_list_pop(link_index, &skb);

        // set the timestamp of the skb
        mtip_ptp_set_tx_timestamp(skb, timestamp_secs, timestamp_nsecs);

        CSMLOGDBG("freeing skb: len: %d\n", skb->len);

        dev_kfree_skb(skb);
    }

    // release the lock
    mtip_ptp_tx_ts_lock_release(link_index);

    // free the taskstruct
    kfree(taskstruct);
}

void mtip_ptp_set_rx_timestamp(struct sk_buff* skb, u32 timestamp_secs, u32 timestamp_nsecs)
{
    struct skb_shared_hwtstamps *shhwtstamp = NULL;
    u64 nanosecs = ((u64)timestamp_secs)*NSEC_PER_SEC + (u64)timestamp_nsecs;

    shhwtstamp = skb_hwtstamps(skb);
    memset(shhwtstamp, 0, sizeof(struct skb_shared_hwtstamps));

    CSMLOGDBG("Read rx nanosecs %ld\n", nanosecs);

    shhwtstamp->hwtstamp = ns_to_ktime(nanosecs);
}

void mtip_ptp_set_tx_timestamp(struct sk_buff* skb, u32 timestamp_secs, u32 timestamp_nsecs)
{
    struct skb_shared_hwtstamps shhwtstamp;
    u64 nanosecs = ((u64)timestamp_secs)*NSEC_PER_SEC + (u64)timestamp_nsecs;

    CSMLOGDBG("Read tx nanosecs %ld\n", nanosecs);

    memset(&shhwtstamp, 0, sizeof(struct skb_shared_hwtstamps));
    shhwtstamp.hwtstamp = ns_to_ktime(nanosecs);
    skb_tstamp_tx(skb, &shhwtstamp);
}

