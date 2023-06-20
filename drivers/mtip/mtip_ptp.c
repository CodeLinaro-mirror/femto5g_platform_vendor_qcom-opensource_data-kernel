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

// resolve the differences between the skb and timestamp queues
// called in the context of ts_lock
void mtip_ptp_resolve_queues(u32 link_index)
{
    u8 read_ts_seq_num;
    u8 pkt_ts_seq_num;
    struct sk_buff* skb = NULL;
    enum mtip_device_mode_enum mode = platform_driver_priv->devices.mode;
    bool loopflag = true;
    int skb_list_size;
    int ts_list_size;
    u32 timestamp_secs;
    u32 timestamp_nsecs;

    if ((mode == MTIP_DEVICE_RU) || (mode == MTIP_DEVICE_DU)) 
    {
        // we should not run into this on V1
        CSMLOGERR("resolve queues called for V1!");
    }

    // loop through pending skbs and find matching timestamps
    while (loopflag) 
    {
        skb_list_size = mtip_ptp_tx_ts_skb_list_size(link_index);
        ts_list_size = mtip_ptp_tx_ts_list_size(link_index);

        CSMLOGDBG("PTP resolving queues: skbs: %d, ts: %d", skb_list_size, ts_list_size);

        // pop the top skb
        mtip_ptp_tx_ts_skb_list_pop(link_index, &skb, &pkt_ts_seq_num);

        // the timestamp list can only be later than or equal to skb list
        // peek the top of the timestamp list
        mtip_ptp_tx_ts_list_peek(link_index, &timestamp_secs, &timestamp_nsecs, &read_ts_seq_num);

        // check if the sequence numbers match
        if (read_ts_seq_num == pkt_ts_seq_num) 
        {
            // pop the timestamp
            mtip_ptp_tx_ts_list_pop(link_index, &timestamp_secs, &timestamp_nsecs, &read_ts_seq_num);

            // set the timestamp of the skb
            mtip_ptp_set_tx_timestamp(skb, timestamp_secs, timestamp_nsecs);
        }
        else
        {
            CSMLOGERR("detected skb loss pkt seq num: %d, ts seq num: %d", pkt_ts_seq_num, read_ts_seq_num);

            // set the timestamp of the skb to 0
            // this will be ignored by the app
            mtip_ptp_set_tx_timestamp(skb, 0, 0);
        }

        // free the skb
        CSMLOGDBG("freeing skb: len: %d\n", skb->len);

        dev_kfree_skb(skb);
        skb = NULL;

        // exit the loop if there are no more skbs or timestamps
        if ((mtip_ptp_tx_ts_skb_list_size(link_index) == 0) || (mtip_ptp_tx_ts_list_size(link_index) == 0))
        {
            loopflag = false;
            break;
        }
    }
}

void mtip_ptp_tx_ts_lock_init(u32 link_index)
{
    spin_lock_init(&platform_driver_priv->mtip_links[link_index]->ptp_lock);
    //mutex_init(&platform_driver_priv->mtip_links[link_index]->dev_lock);
}

void mtip_ptp_tx_ts_lock_acquire(u32 link_index)
{
    spin_lock_irqsave(&platform_driver_priv->mtip_links[link_index]->ptp_lock, platform_driver_priv->mtip_links[link_index]->flags);
    //mutex_lock(&platform_driver_priv->mtip_links[link_index]->dev_lock);
}

void mtip_ptp_tx_ts_lock_release(u32 link_index)
{
    spin_unlock_irqrestore(&platform_driver_priv->mtip_links[link_index]->ptp_lock, platform_driver_priv->mtip_links[link_index]->flags);
    //mutex_unlock(&platform_driver_priv->mtip_links[link_index]->dev_lock);
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

int mtip_ptp_tx_ts_list_push(u32 link_index, u32 tstamp_secs, u32 tstamp_nsecs, u8 ts_seq_num)
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
   node->ts_seq_num = ts_seq_num;

   list_add_tail(&node->list, &listptr->head);
   ++listptr->count;

out:
   return rv;
}

int mtip_ptp_tx_ts_list_pop(u32 link_index, u32* tstamp_secs, u32* tstamp_nsecs, u8* ts_seq_num)
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
      *ts_seq_num = tmp->ts_seq_num;

      // free the node
      kfree(tmp);
   }
   return rv;
}

int mtip_ptp_tx_ts_list_peek(u32 link_index, u32* tstamp_secs, u32* tstamp_nsecs, u8* ts_seq_num)
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
       *tstamp_secs = tmp->tstamp_secs;
       *tstamp_nsecs = tmp->tstamp_nsecs;
       *ts_seq_num = tmp->ts_seq_num;
   }
   else 
   {
       CSMLOGERR("workq list is empty... mismatch with count\n");
       rv = -1;
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

int mtip_ptp_tx_ts_skb_list_push(u32 link_index, struct sk_buff *skb, u8 ts_seq_num)
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
   node->ts_seq_num = ts_seq_num;

   list_add_tail(&node->list, &listptr->head);
   ++listptr->count;

out:
   return rv;
}

int mtip_ptp_tx_ts_skb_list_pop(u32 link_index, struct sk_buff **skb, u8* ts_seq_num)
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
      *ts_seq_num = tmp->ts_seq_num;

      // free the node
      kfree(tmp);
   }
   return rv;
}

int mtip_ptp_tx_ts_skb_list_peek(u32 link_index, struct sk_buff **skb, u8* ts_seq_num)
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
       *skb = tmp->skb;
       *ts_seq_num = tmp->ts_seq_num;
   }
   else 
   {
       CSMLOGERR("workq list is empty... mismatch with count\n");
       rv = -1;
   }
   return rv;
}

void post_mtip_process_timestamp(u32 link_index, u32 timestamp_secs, u32 timestamp_nsecs, u8 ts_seq_num)
{
   struct mtip_process_timestamp_task* taskstruct = kmalloc(sizeof(struct mtip_process_timestamp_task), GFP_ATOMIC);
   if(taskstruct == NULL)
   {
	CSMLOGERR("memory alloc failed\n");
	return;
   }
   taskstruct->link_index = link_index;
   taskstruct->timestamp_secs = timestamp_secs;
   taskstruct->timestamp_nsecs = timestamp_nsecs;
   taskstruct->ts_seq_num = ts_seq_num;
   mtip_queue_work(MTIP_WORKQ_TASK_PROCESS_TIMESTAMP, taskstruct);
}

void run_mtip_process_timestamp(void* work_ptr)
{
    struct mtip_process_timestamp_task* taskstruct = (struct mtip_process_timestamp_task*)work_ptr;
    u32 link_index = taskstruct->link_index;
    u32 timestamp_secs = taskstruct->timestamp_secs;
    u32 timestamp_nsecs = taskstruct->timestamp_nsecs;
    u8 read_ts_seq_num = taskstruct->ts_seq_num;
    u8 pkt_ts_seq_num = 0;
    struct sk_buff* skb = NULL;

    CSMLOGDBG("process tx timestamp %d, %d, read_ts_seq_num: %d\n", timestamp_secs, timestamp_nsecs, read_ts_seq_num);

    // bottom half of process a timestamp
    // acquire the lock
    mtip_ptp_tx_ts_lock_acquire(link_index);
    CSMLOGPTP("hw_ts_seq_num=%d,timestamp_secs=%d, timestamp_nsecs=%d,ts_list_size=%d, \
       skb_list_size=%d[%s]\n",read_ts_seq_num,timestamp_secs, \
       timestamp_nsecs,mtip_ptp_tx_ts_list_size(link_index), \
       mtip_ptp_tx_ts_skb_list_size(link_index),__func__);
    // check if there is an skb pending
    if (mtip_ptp_tx_ts_skb_list_size(link_index) == 0)
    {
        // there are no skbs pending
        // queue the timestamp and ts_seq_num
        mtip_ptp_tx_ts_list_push(link_index, timestamp_secs, timestamp_nsecs, read_ts_seq_num);
    }
    else
    {
        // there are pending skbs
        mtip_ptp_tx_ts_skb_list_peek(link_index, &skb, &pkt_ts_seq_num);
         
        // check if the timestamps match         
        // match the read_ts_seq_num and the pkt_ts_seq_num
        if (read_ts_seq_num == pkt_ts_seq_num)
        {
            // the timestamps match
            mtip_ptp_tx_ts_skb_list_pop(link_index, &skb, &pkt_ts_seq_num);

            // set the timestamp of the skb
            mtip_ptp_set_tx_timestamp(skb, timestamp_secs, timestamp_nsecs);

            CSMLOGDBG("freeing skb: len: %d\n", skb->len);

            dev_kfree_skb(skb);
        }
        else
        {
            // queue the timestamp and ts_seq_num
            mtip_ptp_tx_ts_list_push(link_index, timestamp_secs, timestamp_nsecs, read_ts_seq_num);

            // resolve the differences between the ts and skb queues
            mtip_ptp_resolve_queues(link_index);
        }
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

