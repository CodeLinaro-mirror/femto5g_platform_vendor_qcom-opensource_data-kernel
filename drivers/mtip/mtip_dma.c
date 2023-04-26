//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
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
#include <asm/io.h>
#include <linux/inetdevice.h>
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

#include "mtip_dma.h"
#include "mtip.h"
#include "mtip_platform.h"
#include "mtip_device.h"
#include "mtip_ptp.h"

void mtip_dma_ready_cb(void *user_data)
{
   CSMLOGDBG("mtip_dma_ready_cb\n");

   if (platform_driver_priv->dma_is_ready == false) 
   {
      CSMLOGDBG("registering platform driver\n");

      // call the platform driver register
      platform_driver_priv->perr = mtip_register_platform_driver();

      // HANDLE THE ERROR
   }

   // set the dma_is_ready flag
   platform_driver_priv->dma_is_ready = true;
}

// rx completion callback
void mtip_dma_rx_comp_cb(void *user_data, ecpri_dma_eth_conn_hdl_t hdl)
{
   u32 link_index;
   struct mtip_link_info* link;
   struct net_device *netdev;
   struct mtip_netdev_priv* priv;
   spinlock_t *lock;
   unsigned long flags;
   ecpri_dma_eth_conn_hdl_t used_handle = hdl;
   enum ecpri_dma_notify_mode setmode;

   if (mtip_loopback_mode != MTIP_MODE_DEFAULT) 
   {
#ifdef MTIP_LOOPBACK_SWAP_HANDLE
       switch (hdl)
       {
       case 1:
          used_handle = 2;
          break;
       case 2:
          used_handle = 1;
          break;
       case 3:
          used_handle = 4;
          break;
       case 4:
          used_handle = 3;
          break;
       case 5:
          used_handle = 6;
          break;
       case 6:
          used_handle = 5;
          break;
       case 7:
          used_handle = 8;
          break;
       case 8:
          used_handle = 7;
          break;
       case 9:
          used_handle = 10;
          break;
       case 10:
          used_handle = 9;
          break;
       case 11:
          used_handle = 12;
          break;
       case 12:
          used_handle = 11;
          break;
       }
#endif
   }

   CSMLOGDBG("mtip_dma_rx_comp_cb orig: %d, used hdl: %d\n", hdl, used_handle);

   // get the link index
   if (mtip_lookup_link_index_by_handle(used_handle, &link_index) < 0)
   {
      CSMLOGERR("unable to find link_index for handle: %d ..ignoring\n", used_handle);
   }
   else
   {
      if (platform_driver_priv->mtip_links[link_index]->state == MTIP_LINK_STATE_OPEN ||
          platform_driver_priv->mtip_links[link_index]->state == MTIP_LINK_STATE_UP)
      {
         link = platform_driver_priv->mtip_links[link_index];
         netdev = link->dev;

         CSMLOGDBG("napi schedule for hdl: %d, link_index: %d, link 0x%lx, netdev 0x%lx\n", used_handle, link_index, (unsigned long)link, (unsigned long)netdev);

         priv = netdev_priv(netdev);
         lock = &(priv->lock);

         spin_lock_irqsave(lock, flags);

         // schedule napi
         if (napi_schedule_prep(&(link->napi))) {
            __napi_schedule(&(link->napi));

            // set to POLL mode
            setmode = ECPRI_DMA_NOTIFY_MODE_POLL;

            // set the rx mode to POLL
            mtip_set_rx_mode_immediate(hdl, setmode);
         }

         spin_unlock_irqrestore(lock, flags);
      }
      else
      {
         CSMLOGERR("link not in open state for handle: %d ..ignoring\n", used_handle);
      }
   }
}

int mtip_dma_tx_comp_list_initialize(u32 link_index)
{
    struct mtip_tx_comp_list *listptr = &platform_driver_priv->mtip_links[link_index]->tx_comp_list;

   // initialize the head
    INIT_LIST_HEAD(&listptr->head);

   listptr->count = 0;
   return 0;
}

/*nt mtip_dma_tx_comp_list_finalize(u32 link_index)
{
   // go through all the packets and pop them

   // free the memory allocations
   return 0;
}*/

int mtip_dma_tx_comp_list_size(u32 link_index)
{
   int rv;
   struct mtip_tx_comp_list *listptr = &platform_driver_priv->mtip_links[link_index]->tx_comp_list;

   rv = listptr->count;
   return rv;
}

int mtip_dma_tx_comp_list_push(u32 link_index, void *user_data, ecpri_dma_eth_conn_hdl_t hdl,
                               struct ecpri_dma_pkt_completion_wrapper **comp_pkts,
                               u32 num_of_completed)
{
   int rv = 0;
   struct mtip_tx_comp_node* node = NULL;
   struct mtip_tx_comp_list *listptr = &platform_driver_priv->mtip_links[link_index]->tx_comp_list;

   // allocate a workq node
   node = kmalloc(sizeof(struct mtip_tx_comp_node), GFP_ATOMIC);

   // HANDLE THE ERROR
   if (node == NULL)
   {
      rv = -ENOMEM;
      goto out;
   }

   // init the list
   INIT_LIST_HEAD(&node->list);

   node->tx_comp_params.user_data = user_data;
   node->tx_comp_params.hdl = hdl;
   node->tx_comp_params.local_comp_pkts = comp_pkts;
   node->tx_comp_params.num_of_completed = num_of_completed;

   list_add_tail(&node->list, &listptr->head);
   ++listptr->count;

   //CSMLOGDBG(" link_index %d hdl %d num_of_completed: %d, counter: %d \n", link_index,hdl, num_of_completed, listptr->count);

out:
   return rv;
}

int mtip_dma_tx_comp_list_pop(u32 link_index, struct mtip_dma_tx_comp_params *tx_comp_params)
{
   int rv = 0;
   struct mtip_tx_comp_node* tmp;
   struct mtip_tx_comp_list *listptr = &platform_driver_priv->mtip_links[link_index]->tx_comp_list;

   rv = mtip_dma_tx_comp_list_size(link_index);

   if (rv <= 0)
   {
      return -1;
   }

   // get the first entry
   tmp = list_entry(listptr->head.next, struct mtip_tx_comp_node, list);

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
       tx_comp_params->user_data = tmp->tx_comp_params.user_data;
       tx_comp_params->hdl = tmp->tx_comp_params.hdl;
       tx_comp_params->local_comp_pkts = tmp->tx_comp_params.local_comp_pkts;
       tx_comp_params->num_of_completed = tmp->tx_comp_params.num_of_completed;

      // free the node
      kfree(tmp);
   }

   //CSMLOGDBG(" link_index %d num_of_completed: %d, counter: %d \n", link_index, tx_comp_params->num_of_completed, listptr->count);

   return rv;
}

void mtip_dma_tx_comp_cb(void *user_data, ecpri_dma_eth_conn_hdl_t hdl, struct ecpri_dma_pkt_completion_wrapper **comp_pkts, u32 num_of_completed)
{
    int i;
    struct ecpri_dma_pkt_completion_wrapper **local_comp_pkts;
    u32 link_index;
    struct mtip_link_info* link;
    struct net_device *netdev;
    struct mtip_netdev_priv* priv;
    spinlock_t *lock;
    unsigned long flags;

    //CSMLOGDBG(" hdl: %d, num_of_completed: %d\n", hdl, num_of_completed);

    if (num_of_completed == 0)
    {
        return;
    }

    // copy the pointers
    local_comp_pkts = (struct ecpri_dma_pkt_completion_wrapper **)kmalloc(num_of_completed * sizeof(struct ecpri_dma_pkt_completion_wrapper *), GFP_ATOMIC);

    for (i = 0; i < num_of_completed; ++i)
    {
        // allocate teh completion wrapper
        local_comp_pkts[i] = mtip_dma_alloc_completion_wrapper(GFP_ATOMIC);

        local_comp_pkts[i]->pkt = comp_pkts[i]->pkt;
        local_comp_pkts[i]->status_code = comp_pkts[i]->status_code;
        local_comp_pkts[i]->comp_code = comp_pkts[i]->comp_code;
    }

    if (mtip_lookup_link_index_by_handle(hdl, &link_index) < 0)
    {
      CSMLOGERR("unable to find link_index for handle: %d ..ignoring\n", hdl);
    }
    else
    {
         mtip_dma_tx_comp_list_push(link_index, user_data, hdl, local_comp_pkts, num_of_completed);

         link = platform_driver_priv->mtip_links[link_index];
         netdev = link->dev;

         //CSMLOGDBG("napi schedule for hdl: %d, link_index: %d \n", hdl, link_index);

         priv = netdev_priv(netdev);
         lock = &(priv->lock);

         spin_lock_irqsave(lock, flags);

         // schedule napi
         if (napi_schedule_prep(&(link->napi_tx)))
         {
            __napi_schedule(&(link->napi_tx));

            // set to POLL mode
            //setmode = ECPRI_DMA_NOTIFY_MODE_POLL;

            // set the rx mode to POLL
            //mtip_set_rx_mode_immediate(hdl, setmode);
         }

         spin_unlock_irqrestore(lock, flags);
    }
}

// connect pipe
int mtip_connect_dma_pipe(u32 link_index, ecpri_dma_eth_conn_hdl_t* hdl)
{
   int rv = 0;
   struct ecpri_dma_eth_endpoint_connect_params pipe_params;
   enum mtip_device_mode_enum mode = platform_driver_priv->devices.mode;

   memset(&pipe_params, 0, sizeof(pipe_params));
   pipe_params.link_index = link_index;
   pipe_params.tx_ring_length = MTIP_TX_RING_SIZE;
   pipe_params.rx_ring_length = MTIP_RX_RING_SIZE;

   pipe_params.p_type = ECPRI_DMA_ENDP_STREAM_DEST_FH;
   pipe_params.tx_mod_cfg.moderation_counter_threshold = MTIP_TX_MOD_COUNTER_THRESHOLD;
   pipe_params.tx_mod_cfg.moderation_timer_threshold = MTIP_TX_MOD_TIMER_THRESHOLD;

   if ((mode == MTIP_DEVICE_RUv2) || (mode == MTIP_DEVICE_DUv2))
   {
       pipe_params.enable_tx_pre_header = true;
   }

   // connect the pipe
   rv = (ecpri_dma_eth_driver_ops.ecpri_dma_eth_connect_endpoints)(&pipe_params, hdl);

   if (rv >= 0)
   {
      CSMLOGINFO("assigned connect handle %d to link_index: %d\n", *hdl, link_index);
   }
   return rv;
}

// disconnect pipe
int mtip_disconnect_dma_pipe(ecpri_dma_eth_conn_hdl_t hdl)
{
   int ret;

   // disconnect the pipe
   ret = (ecpri_dma_eth_driver_ops.ecpri_dma_eth_disconnect_endpoints)(hdl);

   if (ret >= 0)
   {
      CSMLOGDBG("disconnected pipe with handle %d\n", hdl);
   }
   return ret;
}

// start pipe
int mtip_start_dma_pipe(struct net_device *netdev, ecpri_dma_eth_conn_hdl_t hdl)
{
   int rv = 0;

   // start the pipes
   rv = (ecpri_dma_eth_driver_ops.ecpri_dma_eth_start_endpoints)(hdl);

   if (rv >= 0)
   {
      CSMLOGDBG("started pipe %d\n", hdl);
   }

   // set the initial set of rx buffers
   // the number of buffers to replenish has to be at most MTIP_RX_RING_SIZE - 1
   mtip_replenish_dma_rx_buffers(netdev, hdl, MTIP_RX_RING_SIZE - 1);

   return rv;
}

// stop pipe
int mtip_stop_dma_pipe(ecpri_dma_eth_conn_hdl_t hdl)
{
   int rv = 0;

   // stop the pipe
   rv = (ecpri_dma_eth_driver_ops.ecpri_dma_eth_stop_endpoints)(hdl);

   if (rv >= 0)
   {
      CSMLOGDBG("stopped pipe %d\n", hdl);
   }
   return rv;
}

// replenish dma buffers
int mtip_replenish_dma_rx_buffers(struct net_device *netdev, ecpri_dma_eth_conn_hdl_t hdl, u32 num_of_buffs)
{
   int rv = 0;
   int j;
   int buff_size = mtip_dma_max_rx_buff_size;
   struct ecpri_dma_pkt **pkts = NULL;
   struct ecpri_dma_mem_buffer **pbuffs = NULL;
   bool commit = true;
   struct sk_buff *skb;
   struct mtip_netdev_priv* priv;
   u32 link_index;

   priv = netdev_priv(netdev);

   link_index = priv->link_index;

   CSMLOGDBG("replenishing %d buffs for hdl %d\n", num_of_buffs, hdl);

   // replenish the rx buffers
   // allocate space to hold pkt pointers
   pkts = (struct ecpri_dma_pkt **)kmalloc(num_of_buffs * sizeof(struct ecpri_dma_pkt *), GFP_KERNEL);

   for (j = 0; j < num_of_buffs; ++j)
   {
      // the dma pkt struct
      pkts[j] = mtip_dma_alloc_dma_pkt(GFP_KERNEL);

      // the dma mem buffer struct
      pbuffs = mtip_dma_alloc_mem_buffer_single_ptr(GFP_KERNEL);

      pbuffs[0] = mtip_dma_alloc_mem_buffer(GFP_KERNEL);

      // HANDLE THE ERROR

      pkts[j]->num_of_buffers = 1;

      // allocate an skb where IP is aligned to 4 byte boundaries
      skb = __netdev_alloc_skb_ip_align(netdev, buff_size, GFP_KERNEL);

      // HANDLE THE ERROR

      // set the netdev of the skb
      skb->dev = netdev;

      // allocate space for one packet
      pbuffs[0]->virt_base = skb->data;
      pbuffs[0]->size = buff_size;
      pbuffs[0]->phys_base = 0;

      // allocate space for one mem_buffer
      pkts[j]->buffs = pbuffs;
      pkts[j]->user_data = (void*)skb;
   }

   // replenish the buffers
   rv = (ecpri_dma_eth_driver_ops.ecpri_dma_eth_replenish_buffers)(hdl, pkts, num_of_buffs, commit);

   if (rv < 0)
   {
      CSMLOGERR("failed to replenish packets for hdl: %d\n", hdl);

      // free all the allocated memory
   }

   // we can now free the pkts using kfree
   kfree(pkts);
   return 0;
}

#ifdef MTIP_DUMP_PACKETS
static void mtip_dma_dump_packet(char* buf, int len)
{
   int payload_len = len - 14;
   int num_dumps;
   int i;
   int index = 0;

   CSMLOGINFO("dumping packet of length: %d\n", len);
   CSMLOGINFO("packet dest MAC addr: %x:%x:%x:%x:%x:%x\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);
   CSMLOGINFO("packet src  MAC addr: %x:%x:%x:%x:%x:%x\n", buf[6], buf[7], buf[8], buf[9], buf[10], buf[11]);
   CSMLOGINFO("packet EtherType: %x:%x\n", buf[12], buf[13]);

   CSMLOGINFO("dumping packet payload length: %d\n", payload_len);
   if (payload_len > 0)
   {
      num_dumps = payload_len/8;

      if (num_dumps > 8)
      {
         num_dumps = 8;
      }

      index = 14;
      for (i = 0; i < num_dumps; ++i)
      {
         CSMLOGINFO("Packet: %d, %x:%x:%x:%x:%x:%x:%x:%x\n", i, 
                    buf[index + 0], buf[index + 1], buf[index + 2], buf[index + 3], 
                    buf[index + 4], buf[index + 5], buf[index + 6], buf[index + 7]);
         index += 8;
         if (index + 8 > len)
         {
            break;
         }
      }
   }
}
#endif

// send a packet
// if send_tx_pre_header is true
// then insert a 64-bit pre-header
// and set bit 33 to 1 and bits 34:36 to ts_seq_num
int mtip_dma_send_packet(struct net_device *netdev, ecpri_dma_eth_conn_hdl_t hdl, struct sk_buff *skb, bool send_tx_pre_header, bool send_tx_seq_num, u8 ts_seq_num)
{
   struct ecpri_dma_pkt **pkts;
   struct ecpri_dma_mem_buffer ** buffs;
   bool commit = true;
   int res;
   struct mtip_netdev_priv* priv;
   u32 link_index;
   spinlock_t *lock;
   unsigned long flags;
   u32 num_buffers = 1;
   struct ecpri_dma_tx_header *pre_header_buff;

   priv = netdev_priv(netdev);

   link_index = priv->link_index;
   lock = &(priv->lock);

   // allocate space to hold dma_pkt pointers
   pkts = mtip_dma_alloc_dma_pkt_ptr(GFP_ATOMIC);

   pkts[0] = mtip_dma_alloc_dma_pkt(GFP_ATOMIC);

   if (send_tx_pre_header == true)
   {
       num_buffers = 2;
       buffs = mtip_dma_alloc_mem_buffer_dual_ptr(GFP_ATOMIC);
   }
   else
   {
       num_buffers = 1;
       buffs = mtip_dma_alloc_mem_buffer_single_ptr(GFP_ATOMIC);
   }


   if (send_tx_pre_header == true)
   {
       pre_header_buff = mtip_dma_alloc_tx_header(GFP_ATOMIC);
       memset(pre_header_buff, 0, sizeof(struct ecpri_dma_tx_header));

       buffs[0] = mtip_dma_alloc_mem_buffer(GFP_ATOMIC);
       buffs[1] = mtip_dma_alloc_mem_buffer(GFP_ATOMIC);

       // set enable bit (Bit 33) and put time stamp seq num in bit 34:36
       if (send_tx_seq_num == true)
       {
           // Set Bit 33 flag for time stamping
           pre_header_buff->timestamp_packet =  0x1;
            // set time stamp seq num 3 bit
           pre_header_buff->timestamp_tag = (u8)ts_seq_num & MTIP_PKT_TS_SEQ_MASK;
       }

       buffs[0]->size = sizeof(struct ecpri_dma_tx_header);
       buffs[0]->virt_base = pre_header_buff;
       buffs[0]->phys_base = 0;

       // SKB data
       buffs[1]->size = skb->len;
       buffs[1]->virt_base = skb->data;
       buffs[1]->phys_base = 0;
   }
   else
   {
       buffs[0] = mtip_dma_alloc_mem_buffer(GFP_ATOMIC);

       // update the buffs
       buffs[0]->size = skb->len;
       buffs[0]->virt_base = skb->data;
       buffs[0]->phys_base = 0;
   }

   pkts[0]->num_of_buffers = num_buffers;
   pkts[0]->buffs = buffs;
   pkts[0]->user_data = (void*)skb;

   spin_lock_irqsave(lock, flags);

   // update tx stats
   ++(platform_driver_priv->mtip_links[link_index]->net_stats.tx_packets);

   platform_driver_priv->mtip_links[link_index]->net_stats.tx_bytes += skb->len;

   spin_unlock_irqrestore(lock, flags);

   CSMLOGDBG("mtip_send_packet hdl %d, link: %d, skb->data: 0x%lx len: %d seq_num %d \n", hdl, link_index, (unsigned long)buffs[0]->virt_base, skb->len, ts_seq_num);

#ifdef MTIP_DUMP_PACKETS
   mtip_dma_dump_packet(skb->data, skb->len);
#endif

   res = (ecpri_dma_eth_driver_ops.ecpri_dma_eth_transmit)(hdl, pkts, 1, commit);

   if (res < 0)
   {
      CSMLOGERR("transmit failed for handle %d with res = %d\n", hdl, res);

      // cleanup here
   }

   // free the container
   mtip_dma_free_dma_pkt_ptr(pkts);
   return res;
}

void mtip_dma_tx_commit(ecpri_dma_eth_conn_hdl_t hdl)
{
   (ecpri_dma_eth_driver_ops.ecpri_dma_eth_commit)(hdl);
}

bool mtip_dma_tx_available(ecpri_dma_eth_conn_hdl_t hdl)
{
   u32 available;

   (ecpri_dma_eth_driver_ops.ecpri_dma_eth_tx_ring_state)(hdl, &available);

   if (available <= MTIP_TX_PACKET_AVAILABILITY_THRESHOLD)
   {
      return false;
   }
   return true;
}

int mtip_dma_rx_available(ecpri_dma_eth_conn_hdl_t hdl, u32* available)
{
   return (ecpri_dma_eth_driver_ops.ecpri_dma_eth_rx_ring_state)(hdl, available);
}

static void fixup_packet(struct net_device* netdev, unsigned char* buf, struct iphdr *ih, u32 packetlen)
{
  	__be32 netdevaddr;
    u32* tmpptr;
   u8* srcaddr;
   u8* dstaddr;
   u8 tmpval;

   CSMLOGDBG("Fixing up_packet len %d buf: 0x%lx\n", packetlen, (unsigned long)buf);

   // get the interface IP address
   netdevaddr = inet_select_addr(netdev, 0, RT_SCOPE_UNIVERSE);

   tmpptr = &ih->saddr;
   srcaddr = (u8*)tmpptr;

   tmpptr = &ih->daddr;
   dstaddr = (u8*)tmpptr;

   ih->check = 0;

   // copy the destaddr last byte to src last byte
   srcaddr[3] = dstaddr[3];

   // copy the netdevaddr to dstaddr
   tmpval = (netdevaddr >> 24) & 0xFF;
   dstaddr[3] = tmpval;

   tmpval = (netdevaddr >> 16) & 0xFF;
   dstaddr[2] = tmpval;

   tmpval = (netdevaddr >> 8) & 0xFF;
   dstaddr[1] = tmpval;

   tmpval = (netdevaddr & 0xFF);
   dstaddr[0] = tmpval;

   srcaddr[0] = dstaddr[0];
   srcaddr[1] = dstaddr[1];
   srcaddr[2] = dstaddr[2];

   ih->check = ip_fast_csum((unsigned char *)ih, ih->ihl);
}

static void mtip_dma_skb_timestamp(struct sk_buff *head_skb)
{
    struct sk_buff *tail_skb, *next_skb;
    unsigned char* base;
    u64 timestamp;
    u32 timestamp_secs;
    u32 timestamp_nsecs;
    u64* tsptr;
    int size;
    int k = 0;
    bool fragmented_packet = false;

    tail_skb = head_skb;
    next_skb = skb_shinfo(head_skb)->frag_list;
    
    // find the last Skb in chain
   if (next_skb != NULL)
   {
        for (k = 1; k < MTIP_RX_DMA_MAX_BUFFERS_PER_PACKET; k++)
        {
            tail_skb = next_skb;
            next_skb = next_skb->next;
            if(next_skb == NULL)
            {
                break;
            }
        }

        fragmented_packet = true;
    }

    base = tail_skb->data;
    size = tail_skb->len;

    tsptr = (u64*)(base + size - 8);
    timestamp = *tsptr;

    // number of secs is the upper 32 bits
    timestamp_secs = (u32)(timestamp >> 32);

    // number of nanosecs is the lower 32 bits
    timestamp_nsecs = (u32)(timestamp & 0xFFFFFFFF);

    CSMLOGDBG("Rx packet timestamp %ld, timestamp_secs %d, timestamp_nsecs %d", 
               timestamp, timestamp_secs, timestamp_nsecs);

    // set the timestamp in the Head Skb
    mtip_ptp_set_rx_timestamp(head_skb, timestamp_secs, timestamp_nsecs);

    //skb_put(tail_skb, size - 8);
    if (fragmented_packet == true) 
    {
        // reduce the length of the tail only if the packet is fragmented
        tail_skb->len -= 8;
        tail_skb->tail -= 8;
    }

    head_skb->len -= 8;
    head_skb->data_len -= 8;
}

static void mtip_dma_process_packet(
    struct net_device *netdev, 
    struct napi_struct *napi_ptr,
    int num_packets,
    struct ecpri_dma_pkt_completion_wrapper **pkts,
    int s_idx,
    int e_idx
)
{
    int num_of_buffers;
    struct sk_buff *head_skb, *curr_skb, *nskb; // *tail_skb;
    int size;
    struct ecpri_dma_pkt *pkt;
    struct ecpri_dma_mem_buffer **buffs;
    spinlock_t *lock;
    unsigned long flags;
    unsigned char* head_base;
    struct mtip_netdev_priv* priv;
    enum ecpri_dma_status_code status_code;
    u32 link_index;
    struct iphdr* iphdr_ptr;
    struct mtip_security_device *sec_dev;
    int k = 0;
    int p, i; 

    priv = netdev_priv(netdev);
    link_index = priv->link_index;
    lock = &(priv->lock);
    sec_dev = priv->sec_dev;

    status_code = pkts[s_idx]->status_code;
    pkt = pkts[s_idx]->pkt;
    num_of_buffers = pkt->num_of_buffers;
    buffs = (struct ecpri_dma_mem_buffer **)pkt->buffs;

    size = buffs[0]->size;
    head_base = buffs[0]->virt_base;
    head_skb = (struct sk_buff *)pkt->user_data;
    curr_skb = head_skb;

    skb_put(head_skb, size);    

    // set the ethernet protocol type
    head_skb->protocol = eth_type_trans(head_skb, netdev);

    for (k = s_idx+1; k <= e_idx; k++)
    {
        pkt = pkts[k]->pkt;
        buffs = (struct ecpri_dma_mem_buffer **)pkt->buffs;
        size = buffs[0]->size;
        nskb = (struct sk_buff *)pkt->user_data;
        num_of_buffers = pkt->num_of_buffers;
        
        if (curr_skb == head_skb)
        {
            skb_shinfo(curr_skb)->frag_list = nskb;
        }
        else
        {
            curr_skb->next = nskb;
        }

        curr_skb = nskb;
        skb_put(curr_skb, size);

        if (curr_skb != head_skb)
        {
            head_skb->len += size;
            head_skb->data_len += size;
            head_skb->truesize += nskb->truesize;
        }        
    }

    // update rx stats
    spin_lock_irqsave(lock, flags);
    ++(platform_driver_priv->mtip_links[link_index]->net_stats.rx_packets);
    platform_driver_priv->mtip_links[link_index]->net_stats.rx_bytes += head_skb->len +  ETH_HLEN;
    spin_unlock_irqrestore(lock, flags);

    if (status_code == ECPRI_DMA_STATUS_CODE_PTP)
    {
        mtip_dma_skb_timestamp(head_skb);
    }

    if (mtip_loopback_mode != MTIP_MODE_DEFAULT && mtip_loopback_swap_addr)
    {
       // fixup the packet: ONLY IF LOOPBACK IS ENABLED
       iphdr_ptr = (struct iphdr *)(head_base + ETH_HLEN);
       fixup_packet(netdev, head_base, iphdr_ptr, head_skb->len);
    }

#ifdef MTIP_DUMP_PACKETS
   // dump the contents of the head buffer/SKB
   mtip_dma_dump_packet(head_base, head_skb->len);
#endif

    if (sec_dev && sec_dev->ops && sec_dev->ops->fixup_rx_skb) 
    {   
        if (sec_dev->ops->fixup_rx_skb(head_skb)) 
        {
            ++(platform_driver_priv->mtip_links[link_index]->net_stats.rx_errors);
            dev_kfree_skb_any(head_skb);
            goto out;
        }
    }
    
    napi_gro_receive(napi_ptr, head_skb);

out:
    // free the container
    for (p = s_idx; p <= e_idx; p++)
    {
        pkt = pkts[p]->pkt;
        buffs = (struct ecpri_dma_mem_buffer **)pkt->buffs;
        num_of_buffers = pkt->num_of_buffers;
        
        for (i = 0; i < num_of_buffers; ++i)
        {
            mtip_dma_free_mem_buffer(buffs[i]);
        }

        //CSMLOGINFO(" Pkt free p %d \n", p);
        mtip_dma_free_mem_buffer_single_ptr(buffs);
        mtip_dma_free_dma_pkt(pkt);
    }
}
 

int mtip_dma_poll_rx_packets(struct net_device *netdev, struct napi_struct *napi_ptr, ecpri_dma_eth_conn_hdl_t hdl, 
                             int budget, int* npackets, int *num_buffers)
{
   int j, k, s_idx;
   int rv;
   int num_pkt_allocs = budget*MTIP_RX_DMA_MAX_BUFFERS_PER_PACKET;
   struct ecpri_dma_pkt_completion_wrapper **pkts; 
   struct mtip_netdev_priv* priv;
   u32 link_index;
   spinlock_t *lock;
   unsigned long flags;
   ecpri_dma_eth_conn_hdl_t actual_handle = hdl;

   if (mtip_loopback_mode != MTIP_MODE_DEFAULT) 
   {
#ifdef MTIP_LOOPBACK_SWAP_HANDLE
       switch (hdl)
       {
       case 1:
          actual_handle = 2;
          break;
       case 2:
          actual_handle = 1;
          break;
       case 3:
          actual_handle = 4;
          break;
       case 4:
          actual_handle = 3;
          break;
       case 5:
          actual_handle = 6;
          break;
       case 6:
          actual_handle = 5;
          break;
       case 7:
          actual_handle = 8;
          break;
       case 8:
          actual_handle = 7;
          break;
       case 9:
          actual_handle = 10;
          break;
       case 10:
          actual_handle = 9;
          break;
       case 11:
          actual_handle = 12;
          break;
       case 12:
          actual_handle = 11;
          break;
       }
#endif
   }

   priv = netdev_priv(netdev);

   link_index = priv->link_index;
   lock = &(priv->lock);

   spin_lock_irqsave(lock, flags);

   pkts = (struct ecpri_dma_pkt_completion_wrapper **)kmalloc(num_pkt_allocs * sizeof(struct ecpri_dma_pkt_completion_wrapper*), GFP_ATOMIC);

   if (pkts == NULL)
   {
       rv = -1;
       spin_unlock_irqrestore(lock, flags);
       goto out;
   }

   for (j = 0; j < num_pkt_allocs; ++j) 
   {
      pkts[j] = mtip_dma_alloc_completion_wrapper(GFP_ATOMIC);

       if (pkts[j] == NULL)
       {
           rv = -1;
           spin_unlock_irqrestore(lock, flags);
           goto out1;
       }
   }

   spin_unlock_irqrestore(lock, flags);

   // set the number of packets to 0
   *npackets = 0;

   // read the packets
   rv = (ecpri_dma_eth_driver_ops.ecpri_dma_eth_rx_poll)(actual_handle, budget, 
                                                         (struct ecpri_dma_pkt_completion_wrapper **)pkts, 
                                                          npackets);

   if (rv < 0)
   {
      CSMLOGERR("dma_eth_rx_poll hdl: %d returned: %d\n", actual_handle, rv);
   }
   else
   {
      CSMLOGDBG("read from hdl %d: actual read packets: %d\n", actual_handle, *npackets);

      s_idx = 0;
      for (j = 0; j < *npackets; j++)   // loop over all packets
      {
          for(k = s_idx; k < (s_idx + MTIP_RX_DMA_MAX_BUFFERS_PER_PACKET); k++)  // Loop over all buffers from start idx (s_idx) to s_idx+4
          {
              if (pkts[k]->comp_code == ECPRI_DMA_COMPLETION_CODE_OVERFLOW)
              {
                  (*num_buffers)++;  // count valid buffers
              }

              if (pkts[k]->comp_code == ECPRI_DMA_COMPLETION_CODE_EOT)
              {
                  mtip_dma_process_packet(netdev, napi_ptr, *npackets, pkts, s_idx, k);                         
                  (*num_buffers)++;                    
                  break;                    // break if EOT detected
              }                           
          }
          s_idx = *num_buffers;
      }
   }
   

out1:
   
   for (j = 0; j < num_pkt_allocs; ++j) 
   {
       // free the completion wrappers
       mtip_dma_free_completion_wrapper(pkts[j]);
   }

   // this is freed using kfree
   kfree(pkts);

out:
   return rv;
}

int mtip_dma_get_ring_state(ecpri_dma_eth_conn_hdl_t hdl, u32* tx_available, u32* rx_available)
{
    int rv;

    rv = (ecpri_dma_eth_driver_ops.ecpri_dma_eth_tx_ring_state)(hdl, tx_available);
    rv = (ecpri_dma_eth_driver_ops.ecpri_dma_eth_rx_ring_state)(hdl, rx_available);
    return rv;
}

/* COMPLETION WRAPPER */
static void mtip_dma_alloc_completion_wrapper_ctor(void *arg)
{
	struct ecpri_dma_pkt_completion_wrapper* node = arg;

	memset(node, 0, sizeof(struct ecpri_dma_pkt_completion_wrapper));
}

static int mtip_dma_alloc_completion_wrapper_initialize(void)
{
    u32 index = MTIP_DMA_ALLOC_LIST_PKT_COMPLETION_WRAPPER;

    platform_driver_priv->mtip_dma_alloc_array[index].cachep = kmem_cache_create("comp_wrap_node",
            sizeof(struct ecpri_dma_pkt_completion_wrapper), 0,
            SLAB_PANIC | SLAB_RECLAIM_ACCOUNT,
            mtip_dma_alloc_completion_wrapper_ctor);
    return 0;
}

int mtip_dma_alloc_completion_wrapper_finalize(void)
{
    u32 index = MTIP_DMA_ALLOC_LIST_PKT_COMPLETION_WRAPPER;

    kmem_cache_destroy(platform_driver_priv->mtip_dma_alloc_array[index].cachep);
    return 0;
}

struct ecpri_dma_pkt_completion_wrapper* mtip_dma_alloc_completion_wrapper(gfp_t flags)
{
    u32 index = MTIP_DMA_ALLOC_LIST_PKT_COMPLETION_WRAPPER;
    return (struct ecpri_dma_pkt_completion_wrapper*)kmem_cache_alloc(platform_driver_priv->mtip_dma_alloc_array[index].cachep, flags);
}

void mtip_dma_free_completion_wrapper(struct ecpri_dma_pkt_completion_wrapper* ptr)
{
    u32 index = MTIP_DMA_ALLOC_LIST_PKT_COMPLETION_WRAPPER;
    kmem_cache_free(platform_driver_priv->mtip_dma_alloc_array[index].cachep, (void *)ptr);
}
/* COMPLETION WRAPPER */

/* DMA PKT PTR */
static void mtip_dma_alloc_dma_pkt_ptr_ctor(void *arg)
{
	struct ecpri_dma_pkt** node = arg;

	memset(node, 0, sizeof(struct ecpri_dma_pkt*));
}

static int mtip_dma_alloc_dma_pkt_ptr_initialize(void)
{
    u32 index = MTIP_DMA_ALLOC_LIST_PKT_PTR;

    platform_driver_priv->mtip_dma_alloc_array[index].cachep = kmem_cache_create("dma_pkt_ptr_node",
            sizeof(struct ecpri_dma_pkt*), 0,
            SLAB_PANIC | SLAB_RECLAIM_ACCOUNT,
            mtip_dma_alloc_dma_pkt_ptr_ctor);
    return 0;
}

int mtip_dma_alloc_dma_pkt_ptr_finalize(void)
{
    u32 index = MTIP_DMA_ALLOC_LIST_PKT_PTR;

    kmem_cache_destroy(platform_driver_priv->mtip_dma_alloc_array[index].cachep);
    return 0;
}

struct ecpri_dma_pkt** mtip_dma_alloc_dma_pkt_ptr(gfp_t flags)
{
    u32 index = MTIP_DMA_ALLOC_LIST_PKT_PTR;
    return (struct ecpri_dma_pkt**)kmem_cache_alloc(platform_driver_priv->mtip_dma_alloc_array[index].cachep, flags);
}

void mtip_dma_free_dma_pkt_ptr(struct ecpri_dma_pkt** ptr)
{    
    u32 index = MTIP_DMA_ALLOC_LIST_PKT_PTR;
    kmem_cache_free(platform_driver_priv->mtip_dma_alloc_array[index].cachep, (void *)ptr);
}
/* DMA PKT PTR */

/* DMA PKT */
static void mtip_dma_alloc_dma_pkt_ctor(void *arg)
{
	struct ecpri_dma_pkt* node = arg;

	memset(node, 0, sizeof(struct ecpri_dma_pkt));
}

static int mtip_dma_alloc_dma_pkt_initialize(void)
{
    u32 index = MTIP_DMA_ALLOC_LIST_PKT;

    platform_driver_priv->mtip_dma_alloc_array[index].cachep = kmem_cache_create("dma_pkt_node",
            sizeof(struct ecpri_dma_pkt), 0,
            SLAB_PANIC | SLAB_RECLAIM_ACCOUNT,
            mtip_dma_alloc_dma_pkt_ctor);
    return 0;
}

int mtip_dma_alloc_dma_pkt_finalize(void)
{
    u32 index = MTIP_DMA_ALLOC_LIST_PKT;

    kmem_cache_destroy(platform_driver_priv->mtip_dma_alloc_array[index].cachep);
    return 0;
}

struct ecpri_dma_pkt* mtip_dma_alloc_dma_pkt(gfp_t flags)
{
    u32 index = MTIP_DMA_ALLOC_LIST_PKT;
    return (struct ecpri_dma_pkt*)kmem_cache_alloc(platform_driver_priv->mtip_dma_alloc_array[index].cachep, flags);
}

void mtip_dma_free_dma_pkt(struct ecpri_dma_pkt* ptr)
{    
    u32 index = MTIP_DMA_ALLOC_LIST_PKT;
    kmem_cache_free(platform_driver_priv->mtip_dma_alloc_array[index].cachep, (void *)ptr);
}
/* DMA PKT */

/* MEM BUFFER SINGLE PTR */
static void mtip_dma_alloc_mem_buffer_single_ptr_ctor(void *arg)
{
	struct ecpri_dma_mem_buffer** node = arg;

	memset(node, 0, sizeof(struct ecpri_dma_mem_buffer*));
}

static int mtip_dma_alloc_mem_buffer_single_ptr_initialize(void)
{
    u32 index = MTIP_DMA_ALLOC_LIST_MEM_BUFFER_SINGLE_PTR;

    platform_driver_priv->mtip_dma_alloc_array[index].cachep = kmem_cache_create("mbuf_sing_node",
            sizeof(struct ecpri_dma_mem_buffer*), 0,
            SLAB_PANIC | SLAB_RECLAIM_ACCOUNT,
            mtip_dma_alloc_mem_buffer_single_ptr_ctor);
    return 0;
}

int mtip_dma_alloc_mem_buffer_single_ptr_finalize(void)
{
    u32 index = MTIP_DMA_ALLOC_LIST_MEM_BUFFER_SINGLE_PTR;

    kmem_cache_destroy(platform_driver_priv->mtip_dma_alloc_array[index].cachep);
    return 0;
}

struct ecpri_dma_mem_buffer** mtip_dma_alloc_mem_buffer_single_ptr(gfp_t flags)
{
    u32 index = MTIP_DMA_ALLOC_LIST_MEM_BUFFER_SINGLE_PTR;
    return (struct ecpri_dma_mem_buffer**)kmem_cache_alloc(platform_driver_priv->mtip_dma_alloc_array[index].cachep, flags);
}

void mtip_dma_free_mem_buffer_single_ptr(struct ecpri_dma_mem_buffer** ptr)
{    
    u32 index = MTIP_DMA_ALLOC_LIST_MEM_BUFFER_SINGLE_PTR;
    kmem_cache_free(platform_driver_priv->mtip_dma_alloc_array[index].cachep, (void *)ptr);
}
/* MEM BUFFER SINGLE PTR */

/* MEM BUFFER DUAL PTR */
static void mtip_dma_alloc_mem_buffer_dual_ptr_ctor(void *arg)
{
	struct ecpri_dma_mem_buffer** node = arg;

	memset(node, 0, 2*sizeof(struct ecpri_dma_mem_buffer*));
}

static int mtip_dma_alloc_mem_buffer_dual_ptr_initialize(void)
{
    u32 index = MTIP_DMA_ALLOC_LIST_MEM_BUFFER_DUAL_PTR;

    platform_driver_priv->mtip_dma_alloc_array[index].cachep = kmem_cache_create("mbuf_dual_node",
            2*sizeof(struct ecpri_dma_mem_buffer*), 0,
            SLAB_PANIC | SLAB_RECLAIM_ACCOUNT,
            mtip_dma_alloc_mem_buffer_dual_ptr_ctor);
    return 0;
}

int mtip_dma_alloc_mem_buffer_dual_ptr_finalize(void)
{
    u32 index = MTIP_DMA_ALLOC_LIST_MEM_BUFFER_DUAL_PTR;

    kmem_cache_destroy(platform_driver_priv->mtip_dma_alloc_array[index].cachep);
    return 0;
}

struct ecpri_dma_mem_buffer** mtip_dma_alloc_mem_buffer_dual_ptr(gfp_t flags)
{
    u32 index = MTIP_DMA_ALLOC_LIST_MEM_BUFFER_DUAL_PTR;
    return (struct ecpri_dma_mem_buffer**)kmem_cache_alloc(platform_driver_priv->mtip_dma_alloc_array[index].cachep, flags);
}

void mtip_dma_free_mem_buffer_dual_ptr(struct ecpri_dma_mem_buffer** ptr)
{    
    u32 index = MTIP_DMA_ALLOC_LIST_MEM_BUFFER_DUAL_PTR;
    kmem_cache_free(platform_driver_priv->mtip_dma_alloc_array[index].cachep, (void *)ptr);
}
/* MEM BUFFER DUAL PTR */

/* MEM BUFFER */
static void mtip_dma_alloc_mem_buffer_ctor(void *arg)
{
	struct ecpri_dma_mem_buffer* node = arg;

	memset(node, 0, sizeof(struct ecpri_dma_mem_buffer));
}

static int mtip_dma_alloc_mem_buffer_initialize(void)
{
    u32 index = MTIP_DMA_ALLOC_LIST_MEM_BUFFER;

    platform_driver_priv->mtip_dma_alloc_array[index].cachep = kmem_cache_create("mem_buf_node",
            sizeof(struct ecpri_dma_mem_buffer), 0,
            SLAB_PANIC | SLAB_RECLAIM_ACCOUNT,
            mtip_dma_alloc_mem_buffer_ctor);
    return 0;
}

int mtip_dma_alloc_mem_buffer_finalize(void)
{
    u32 index = MTIP_DMA_ALLOC_LIST_MEM_BUFFER;

    kmem_cache_destroy(platform_driver_priv->mtip_dma_alloc_array[index].cachep);
    return 0;
}

struct ecpri_dma_mem_buffer* mtip_dma_alloc_mem_buffer(gfp_t flags)
{
    u32 index = MTIP_DMA_ALLOC_LIST_MEM_BUFFER;
    return (struct ecpri_dma_mem_buffer*)kmem_cache_alloc(platform_driver_priv->mtip_dma_alloc_array[index].cachep, flags);
}

void mtip_dma_free_mem_buffer(struct ecpri_dma_mem_buffer* ptr)
{    
    u32 index = MTIP_DMA_ALLOC_LIST_MEM_BUFFER;
    kmem_cache_free(platform_driver_priv->mtip_dma_alloc_array[index].cachep, (void *)ptr);
}
/* MEM BUFFER */

/* TX HEADER */
static void mtip_dma_alloc_tx_header_ctor(void *arg)
{
	struct ecpri_dma_tx_header* node = arg;

	memset(node, 0, sizeof(struct ecpri_dma_tx_header));
}

static int mtip_dma_alloc_tx_header_initialize(void)
{
    u32 index = MTIP_DMA_ALLOC_LIST_TX_HEADER;

    platform_driver_priv->mtip_dma_alloc_array[index].cachep = kmem_cache_create("tx_hdr_node",
            sizeof(struct ecpri_dma_tx_header), 0,
            SLAB_PANIC | SLAB_RECLAIM_ACCOUNT,
            mtip_dma_alloc_tx_header_ctor);
    return 0;
}

int mtip_dma_alloc_tx_header_finalize(void)
{
    u32 index = MTIP_DMA_ALLOC_LIST_TX_HEADER;

    kmem_cache_destroy(platform_driver_priv->mtip_dma_alloc_array[index].cachep);
    return 0;
}

struct ecpri_dma_tx_header* mtip_dma_alloc_tx_header(gfp_t flags)
{
    u32 index = MTIP_DMA_ALLOC_LIST_TX_HEADER;
    return (struct ecpri_dma_tx_header*)kmem_cache_alloc(platform_driver_priv->mtip_dma_alloc_array[index].cachep, flags);
}

void mtip_dma_free_tx_header(struct ecpri_dma_tx_header* ptr)
{    
    u32 index = MTIP_DMA_ALLOC_LIST_TX_HEADER;
    kmem_cache_free(platform_driver_priv->mtip_dma_alloc_array[index].cachep, (void *)ptr);
}
/* TX HEADER */

int mtip_dma_alloc_initialize(u32 index)
{
    int rv;

    switch (index) 
    {
    case MTIP_DMA_ALLOC_LIST_PKT_COMPLETION_WRAPPER:
        {
            rv = mtip_dma_alloc_completion_wrapper_initialize();
        }
        break;
    case MTIP_DMA_ALLOC_LIST_PKT_PTR:
        {
            rv = mtip_dma_alloc_dma_pkt_ptr_initialize();
        }
        break;
    case MTIP_DMA_ALLOC_LIST_PKT:
        {
            rv = mtip_dma_alloc_dma_pkt_initialize();
        }
        break;
    case MTIP_DMA_ALLOC_LIST_MEM_BUFFER_SINGLE_PTR:
        {
            rv = mtip_dma_alloc_mem_buffer_single_ptr_initialize();
        }
        break;
    case MTIP_DMA_ALLOC_LIST_MEM_BUFFER_DUAL_PTR:
        {
            rv = mtip_dma_alloc_mem_buffer_dual_ptr_initialize();
        }
        break;
    case MTIP_DMA_ALLOC_LIST_MEM_BUFFER:
        {
            rv = mtip_dma_alloc_mem_buffer_initialize();
        }
        break;
    case MTIP_DMA_ALLOC_LIST_TX_HEADER:
        {
            rv = mtip_dma_alloc_tx_header_initialize();
        }
        break;
    default:
        {
            rv = -1;
        }
        break;
    }
    return rv;
}

int mtip_dma_alloc_finalize(u32 index)
{
    int rv;

    switch (index) 
    {
    case MTIP_DMA_ALLOC_LIST_PKT_COMPLETION_WRAPPER:
        {
            rv = mtip_dma_alloc_completion_wrapper_finalize();
        }
        break;
    case MTIP_DMA_ALLOC_LIST_PKT_PTR:
        {
            rv = mtip_dma_alloc_dma_pkt_ptr_finalize();
        }
        break;
    case MTIP_DMA_ALLOC_LIST_PKT:
        {
            rv = mtip_dma_alloc_dma_pkt_finalize();
        }
        break;
    case MTIP_DMA_ALLOC_LIST_MEM_BUFFER_SINGLE_PTR:
        {
            rv = mtip_dma_alloc_mem_buffer_single_ptr_finalize();
        }
        break;
    case MTIP_DMA_ALLOC_LIST_MEM_BUFFER_DUAL_PTR:
        {
            rv = mtip_dma_alloc_mem_buffer_dual_ptr_finalize();
        }
        break;
    case MTIP_DMA_ALLOC_LIST_MEM_BUFFER:
        {
            rv = mtip_dma_alloc_mem_buffer_finalize();
        }
        break;
    case MTIP_DMA_ALLOC_LIST_TX_HEADER:
        {
            rv = mtip_dma_alloc_tx_header_finalize();
        }
        break;
    default:
        {
            rv = -1;
        }
        break;
    }
    return rv;
}

