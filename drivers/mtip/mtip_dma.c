//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022-2024 Qualcomm Innovation Center, Inc. All rights reserved.
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
#include <linux/icmp.h>         /* struct icmphdr */
#include <linux/skbuff.h>

#include "mtip_dma.h"
#include "mtip.h"
#include "mtip_platform.h"
#include "mtip_device.h"
#include "mtip_ptp.h"

#define DMA_HANDLE_MAX 16

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
   ecpri_dma_eth_conn_hdl_t used_handle = hdl;
   enum ecpri_dma_notify_mode setmode = ECPRI_DMA_NOTIFY_MODE_POLL;

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
      if (platform_driver_priv->mtip_links[link_index]->state == MTIP_LINK_STATE_OPEN_DONE ||
          platform_driver_priv->mtip_links[link_index]->state == MTIP_LINK_STATE_UP)
      {
         link = platform_driver_priv->mtip_links[link_index];
         netdev = link->dev;


         priv = netdev_priv(netdev);

         // schedule napi
         if (napi_schedule_prep(&(link->napi))) {
            __napi_schedule(&(link->napi));
            CSMLOGDBG("RX napi schedule for hdl: %d, link_index: %d, link 0x%lx, netdev 0x%lx\n", used_handle, link_index, (unsigned long)link, (unsigned long)netdev);

            // set the rx mode to POLL
            mtip_set_rx_mode_immediate(hdl, setmode);
         }
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

void mtip_dma_tx_irq_comp_cb(void *user_data, ecpri_dma_eth_conn_hdl_t hdl)
{
   u32 link_index;
   struct mtip_link_info* link;
   struct net_device *netdev;
   struct mtip_netdev_priv* priv;
   ecpri_dma_eth_conn_hdl_t used_handle = hdl;
   enum ecpri_dma_notify_mode setmode = ECPRI_DMA_NOTIFY_MODE_POLL;

   CSMLOGDBG("mtip_dma_tx_irq_comp_cb orig: %d, used hdl: %d\n", hdl, used_handle);

   // get the link index
   if (mtip_lookup_link_index_by_handle(used_handle, &link_index) < 0)
   {
      CSMLOGERR("unable to find link_index for handle: %d ..ignoring\n", used_handle);
   }
   else
   {
      if (platform_driver_priv->mtip_links[link_index]->state == MTIP_LINK_STATE_OPEN_DONE ||
          platform_driver_priv->mtip_links[link_index]->state == MTIP_LINK_STATE_UP)
      {
         link = platform_driver_priv->mtip_links[link_index];
         netdev = link->dev;

         CSMLOGDBG("TX napi schedule for hdl: %d, link_index: %d, link 0x%lx, netdev 0x%lx\n", used_handle, link_index, (unsigned long)link, (unsigned long)netdev);

         priv = netdev_priv(netdev);

         // schedule napi
         if (napi_schedule_prep(&(link->napi_tx))) {
            __napi_schedule(&(link->napi_tx));

            // set the tx mode to POLL
            mtip_set_tx_mode_immediate(hdl, setmode);
         }
      }
      else
      {
         CSMLOGERR("link not in open state for handle: %d ..ignoring\n", used_handle);
      }
   }
}


void mtip_dma_tx_comp_cb(void *user_data, ecpri_dma_eth_conn_hdl_t hdl, struct ecpri_dma_pkt_completion_wrapper **comp_pkts, u32 num_of_completed)
{
    int i;
    struct ecpri_dma_pkt_completion_wrapper **local_comp_pkts;
    u32 link_index;
    struct mtip_link_info* link;
    struct net_device *netdev;
    struct mtip_netdev_priv* priv;

    //CSMLOGDBG(" hdl: %d, num_of_completed: %d\n", hdl, num_of_completed);

    if (num_of_completed == 0)
    {
        return;
    }

    // copy the pointers
    local_comp_pkts = (struct ecpri_dma_pkt_completion_wrapper **)kmalloc(num_of_completed * sizeof(struct ecpri_dma_pkt_completion_wrapper *), GFP_ATOMIC);
    if(local_comp_pkts == NULL)
    {
      CSMLOGERR("memory alloc failed\n");
      return;
    }

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

         // schedule napi
         if (napi_schedule_prep(&(link->napi_tx)))
         {
            __napi_schedule(&(link->napi_tx));

         }

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

   if (link_index == MTIP_L2_ETH_LINK_INDEX)
   	 pipe_params.p_type = ECPRI_DMA_ENDP_STREAM_DEST_L2;
   else if (link_index == MTIP_C2C1_ETH_LINK_INDEX || link_index == MTIP_C2C0_ETH_LINK_INDEX)
   	 pipe_params.p_type = ECPRI_DMA_ENDP_STREAM_DEST_C2C;
   else
     pipe_params.p_type = ECPRI_DMA_ENDP_STREAM_DEST_FH;
   
   pipe_params.tx_mod_cfg.moderation_counter_threshold = MTIP_TX_MOD_COUNTER_THRESHOLD;
   pipe_params.tx_mod_cfg.moderation_timer_threshold = MTIP_TX_MOD_TIMER_THRESHOLD;

   if ((mode == MTIP_DEVICE_RUv2) || (mode == MTIP_DEVICE_DUv2))
   {
       pipe_params.enable_tx_pre_header = true;
   }

   // Enable TX completion napi poll 
   pipe_params.enable_tx_poll = enable_tx_comp_poll;
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
   static bool hdl_repl[DMA_HANDLE_MAX] = {0};
   struct mtip_netdev_priv *priv = NULL;
   int rx_index = 0, tx_index = 0, i = 0;
   struct ecpri_dma_pkt_completion_wrapper **pkts;
   int num_pkt_allocs = MTIP_NAPI_WEIGHT * MTIP_RX_DMA_MAX_BUFFERS_PER_PACKET;
   u32 tx_available = 0;
   u32 rx_available = 0;
   enum ecpri_dma_notify_mode mode = ECPRI_DMA_NOTIFY_MODE_MAX;
   enum ecpri_dma_notify_mode setmode = ECPRI_DMA_NOTIFY_MODE_IRQ;
   u32 link_index;
   struct mtip_link_info* link=NULL;

   // start the pipes
   rv = (ecpri_dma_eth_driver_ops.ecpri_dma_eth_start_endpoints)(hdl);

   if (rv >= 0)
   {
      CSMLOGDBG("started pipe %d\n", hdl);
   }

   priv = netdev_priv(netdev);

   // get the link index
   if (mtip_lookup_link_index_by_handle(hdl, &link_index) < 0)
   {
      rv = -1;
      CSMLOGERR("unable to find link_index for handle: %d ..ignoring\n", hdl);
      goto ret;
   }
   // set the initial set of rx buffers
   // the number of buffers to replenish has to be at most MTIP_RX_RING_SIZE - 1
   if(hdl_repl[hdl] == false)
   {
      pkts = (struct ecpri_dma_pkt_completion_wrapper **)kmalloc(num_pkt_allocs * sizeof(struct ecpri_dma_pkt_completion_wrapper*), GFP_KERNEL);

      if (pkts == NULL)
      {
         rv = -1;
         CSMLOGERR("Memory alloc for tx completion wrapper failed\n");
         goto ret;
      }

      priv->tx_comp_pkts = pkts;

      for (tx_index = 0; tx_index < num_pkt_allocs; ++tx_index)
      {
         pkts[tx_index] = mtip_dma_alloc_completion_wrapper(GFP_KERNEL);

         if (pkts[tx_index] == NULL)
         {
            rv = -1;
            CSMLOGERR("Memory alloc for tx completion wrapper failed\n");
            goto free_tx_buf;
         }
      }

      pkts = NULL;
      pkts = (struct ecpri_dma_pkt_completion_wrapper **)kmalloc(num_pkt_allocs * sizeof(struct ecpri_dma_pkt_completion_wrapper*), GFP_KERNEL);
      if (pkts == NULL)
      {
         rv = -1;
         CSMLOGERR("Memory alloc for rx completion wrapper failed\n");
         goto free_tx_buf;
      }

      priv->rx_comp_pkts = pkts;

      for (rx_index = 0; rx_index < num_pkt_allocs; ++rx_index)
      {
         pkts[rx_index] = mtip_dma_alloc_completion_wrapper(GFP_KERNEL);

         if (pkts[rx_index] == NULL)
         {
            rv = -1;
            CSMLOGERR("Memory alloc for rx completion wrapper failed\n");
            goto free_rx_buf;
         }
      }

      rv = mtip_dma_get_ring_state(hdl, &tx_available, &rx_available);
      if (rv < 0)
      {
         CSMLOGERR("get ring state from DMA failed for hdl: %d\n", hdl);
      }
      CSMLOGINFO("rx_available: %d,priv->rx_polled_count %d,link_index=%d\n", rx_available,priv->rx_polled_count,link_index);

      mtip_replenish_dma_rx_buffers(netdev, hdl, MTIP_RX_RING_SIZE - 1);

      rv = mtip_dma_get_ring_state(hdl, &tx_available, &rx_available);
      if (rv < 0)
      {
         CSMLOGERR("get ring state from DMA failed for hdl: %d\n", hdl);
      }
      CSMLOGINFO("rx_available: %d,priv->rx_polled_count %d,link_index=%d\n", rx_available,priv->rx_polled_count,link_index);

         // set the rx mode to IRQ
      setmode = ECPRI_DMA_NOTIFY_MODE_IRQ;
      mtip_set_rx_mode_immediate(hdl, setmode);

      mtip_get_rx_mode_immediate(hdl, &mode);
      CSMLOGINFO("rx mode is:%d for hdl: %d\n", mode,hdl);

      hdl_repl[hdl] = true;
   }
   else
   {

      rv = mtip_dma_get_ring_state(hdl, &tx_available, &rx_available);
      CSMLOGINFO("rx_available: %d, priv->rx_polled_count %d\n", rx_available, priv->rx_polled_count);
      if (rv < 0)
      {
         CSMLOGERR("get ring state from DMA failed for hdl: %d\n", hdl);
         goto ret;
      }
      else if(rx_available > 1)
      {
         rv = mtip_replenish_dma_rx_buffers_reuse(netdev, hdl, rx_available-1);
         if(rv == 0)
            priv->rx_polled_count = 0;
      }

      if(rx_available == MTIP_RX_RING_SIZE)
      {
         // set the rx mode to IRQ
         setmode = ECPRI_DMA_NOTIFY_MODE_IRQ;
         mtip_set_rx_mode_immediate(hdl, setmode);

         mtip_get_rx_mode_immediate(hdl, &mode);
         CSMLOGINFO("rx mode is:%d for hdl: %d\n", mode,hdl);
      }
      else
      {
         link = platform_driver_priv->mtip_links[link_index];

         if (napi_schedule_prep(&(link->napi)))
         {
            // set the rx mode to POLL
            setmode = ECPRI_DMA_NOTIFY_MODE_POLL;
            mtip_set_rx_mode_immediate(hdl, setmode);

            mtip_get_rx_mode_immediate(hdl, &mode);
            CSMLOGINFO("rx mode is:%d for hdl: %d\n", mode,hdl);

            __napi_schedule(&(link->napi));
            CSMLOGINFO("RX napi schedule for hdl: %d, link_index: %d, link 0x%lx, netdev 0x%lx\n", hdl, link_index, (unsigned long)link, (unsigned long)netdev);      // schedule napi
         }
      }
   }

   goto ret;

free_rx_buf:
   pkts = priv->rx_comp_pkts;
   for (i = 0; i < rx_index; ++i)
   {
      if(pkts[i])
         mtip_dma_free_completion_wrapper(pkts[i]);
   }
   kfree(pkts);
   priv->rx_comp_pkts = NULL;

free_tx_buf:
   pkts = priv->tx_comp_pkts;
   for (i = 0; i < tx_index; ++i)
   {
      if(pkts[i])
         mtip_dma_free_completion_wrapper(pkts[i]);
   }
   kfree(pkts);
   priv->tx_comp_pkts = NULL;

ret:
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

int mtip_replenish_dma_rx_buffers_reuse(struct net_device *netdev, ecpri_dma_eth_conn_hdl_t hdl, u32 num_of_buffs)
{
   int rv = 0;
   int j,i,start_index = 0;
   uint16_t curr_index = 0;
   int buff_size = mtip_dma_max_rx_buff_size;
   struct ecpri_dma_pkt **pkts = NULL;
   struct ecpri_dma_pkt **head_pkt = NULL;
   struct ecpri_dma_mem_buffer **pbuffs = NULL;
   struct mtip_pkt_priv *pkt_priv = NULL;
   bool commit = true;
   struct sk_buff *skb = NULL;
   struct mtip_netdev_priv* priv;
   u32 link_index;
   u32 num_of_pkts_to_send = num_of_buffs;
   u32 num_of_pkts_remain = num_of_buffs;
   u32 successful_pkts = 0;
   priv = netdev_priv(netdev);

   link_index = priv->link_index;

   CSMLOGDBG("Replenishing reused %d buffs for hdl %d\n", num_of_buffs, hdl);

   pkts = priv->head;
   if(pkts == NULL)
   {
      CSMLOGERR("HEAD is NULL, No buffers allocated and replenished to DMA\n");
      return -1;
   }

   curr_index = priv->rx_curr_index;

   for (j = 0; j < num_of_buffs ; ++j)
   {
      curr_index = (priv->rx_curr_index + j)%(MTIP_RX_RING_SIZE - 1);

      skb = netdev_alloc_skb_ip_align(netdev, buff_size);
      if(skb == NULL)
      {
         CSMLOGERR("Skb alloc with netdev_alloc_skb_ip_align failed\n");
         goto skb_free;
      }

      // set the netdev of the skb
      skb->dev = netdev;

      pbuffs = pkts[curr_index]->buffs;

      memset(pbuffs[0], 0, sizeof(struct ecpri_dma_mem_buffer));
      pbuffs[0]->virt_base = skb->data;
      pbuffs[0]->size = buff_size;
      pbuffs[0]->phys_base = 0;

      pkt_priv = (struct mtip_pkt_priv *)(pkts[curr_index]->user_data);
      pkt_priv->skb = skb;
      pkts[curr_index]->buffs = pbuffs;

   }

   head_pkt = priv->head;

   while(num_of_pkts_remain)
   {
      if( (num_of_pkts_to_send + priv->rx_curr_index) > (MTIP_RX_RING_SIZE - 1))
         num_of_pkts_to_send = (MTIP_RX_RING_SIZE - 1) - priv->rx_curr_index;
      else
         num_of_pkts_to_send = num_of_pkts_remain;

      pkts = &(head_pkt[priv->rx_curr_index]);
      // replenish the buffers
      rv = (ecpri_dma_eth_driver_ops.ecpri_dma_eth_replenish_buffers)(hdl, pkts,num_of_pkts_to_send, commit, &successful_pkts);
      if (rv < 0)
      {
         CSMLOGERR("Failed to replenish packets for hdl:%d,curr_index:%d,num_of_pkts_to_send:%d,num_of_pkts_remain:%d\n", hdl,priv->rx_curr_index,num_of_pkts_to_send,num_of_pkts_remain);
         //return -1;
         start_index = successful_pkts;
         goto skb_free;
      }

      num_of_pkts_remain -= num_of_pkts_to_send;
      priv->rx_curr_index = ( (priv->rx_curr_index) + num_of_pkts_to_send )%(MTIP_RX_RING_SIZE - 1);
   }

   goto ret;

skb_free:
   pkts = priv->head;
   for (i = start_index; i < j ; ++i)
   {
      curr_index = (priv->rx_curr_index + i)%(MTIP_RX_RING_SIZE - 1);
      // free the skb
      pkt_priv = (struct mtip_pkt_priv *)(pkts[curr_index]->user_data);
      if(pkt_priv)
      {
         if(pkt_priv->skb)
            dev_kfree_skb(pkt_priv->skb);
      }
   }
   return -1;
ret:
   return 0;
}


int mtip_replenish_dma_rx_buffers(struct net_device *netdev, ecpri_dma_eth_conn_hdl_t hdl, u32 num_of_buffs)
{
   int rv = 0;
   int j,i, start_index = 0;
   int buff_size = mtip_dma_max_rx_buff_size;
   struct ecpri_dma_pkt **pkts = NULL;
   struct ecpri_dma_mem_buffer **pbuffs = NULL;
   bool commit = true;
   struct sk_buff *skb = NULL;
   struct mtip_netdev_priv* priv;
   u32 link_index;
   struct mtip_pkt_priv *pkt_priv = NULL;
   u32 successful_pkts = 0;

   priv = netdev_priv(netdev);

   link_index = priv->link_index;

   CSMLOGDBG("Replenishing %d buffs for hdl %d\n", num_of_buffs, hdl);

   // replenish the rx buffers
   // allocate space to hold pkt pointers
   pkts = (struct ecpri_dma_pkt **)kmalloc(num_of_buffs * sizeof(struct ecpri_dma_pkt *), GFP_KERNEL);
   if(pkts == NULL)
   {
      CSMLOGERR("Memory alloc with kmalloc for ecpri_dma_pkt failed\n");
      return -1;
   }
   priv->head = pkts;
   priv->rx_curr_index = 0;

   for (j = 0; j < num_of_buffs; ++j)
   {
      // the dma pkt struct
      pkts[j] = mtip_dma_alloc_dma_pkt(GFP_KERNEL);
      if(pkts[j] == NULL)
      {
         CSMLOGERR("Memory alloc with mtip_dma_alloc_dma_pkt failed\n");
         goto cleanup;
      }

      // the dma mem buffer struct
      pbuffs = mtip_dma_alloc_mem_buffer_single_ptr(GFP_KERNEL);
      if(pbuffs == NULL)
      {
         CSMLOGERR("Single pointer alloc with mtip_dma_alloc_mem_buffer_single_ptr failed\n");
         goto cleanup;
      }

      pbuffs[0] = mtip_dma_alloc_mem_buffer(GFP_KERNEL);
      if(pbuffs[0] == NULL)
      {
         CSMLOGERR("Mem buffer alloc with mtip_dma_alloc_mem_buffer failed\n");
         goto cleanup;
      }

      pkts[j]->num_of_buffers = 1;

      // allocate an skb where IP is aligned to 4 byte boundaries
      skb = __netdev_alloc_skb_ip_align(netdev, buff_size, GFP_KERNEL);
      if(skb == NULL)
      {
         CSMLOGERR("Skb alloc with __netdev_alloc_skb_ip_align failed\n");
         goto cleanup;
      }

      // set the netdev of the skb
      skb->dev = netdev;

      // allocate space for one packet
      pbuffs[0]->virt_base = skb->data;
      pbuffs[0]->size = buff_size;
      pbuffs[0]->phys_base = 0;

      // allocate space for one mem_buffer
      pkts[j]->buffs = pbuffs;

      // allocate mtip packet priv structure
      pkt_priv = (struct mtip_pkt_priv *)kmalloc(sizeof(struct mtip_pkt_priv), GFP_KERNEL);
      if(pkt_priv == NULL)
      {
         CSMLOGERR("Pkt priv alloc failed\n");
         goto cleanup;
      }
      pkt_priv->skb = skb;
      pkt_priv->tx_index = 0;

      pkts[j]->user_data = (void*)pkt_priv;
   }

   // replenish the buffers
   rv = (ecpri_dma_eth_driver_ops.ecpri_dma_eth_replenish_buffers)(hdl, pkts, num_of_buffs, commit, &successful_pkts);

   if (rv < 0)
   {
      CSMLOGERR("Failed to replenish packets for hdl: %d\n", hdl);
      start_index = successful_pkts;
      goto cleanup;
   }
   goto ret;

cleanup:
   for (i = start_index ; i < j; i++)
   {
      if(pkts[i] == NULL)
         continue;

      mtip_dma_free_pkt(pkts[i]);
      pkts[i] = NULL;
   }
   kfree(pkts);
   return -1;

ret:
   return 0;
}

#ifdef MTIP_DUMP_PACKETS
static void mtip_dma_dump_packet(char* buf, int len)
{
   int payload_len = len - 14;
   int num_dumps;
   int i;
   int index = 0;

   CSMLOGDBG("dumping packet of length: %d\n", len);
   CSMLOGDBG("packet dest MAC addr: %02x %02x %02x %02x %02x %02x\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);
   CSMLOGDBG("packet src  MAC addr: %02x %02x %02x %02x %02x %02x\n", buf[6], buf[7], buf[8], buf[9], buf[10], buf[11]);
   CSMLOGDBG("packet EtherType: %02x %02x\n", buf[12], buf[13]);

   CSMLOGDBG("dumping packet payload length: %d\n", payload_len);
   
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
         CSMLOGDBG("Packet: %d, %02x %02x %02x %02x %02x %02x %02x %02x\n", i,
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
   int res = -1;
   struct mtip_netdev_priv* priv;
   u32 link_index;
   spinlock_t *lock;
   unsigned long flags;
   u32 num_buffers = 1;
   struct ecpri_dma_tx_header *pre_header_buff;
   struct ecpri_dma_pkt *tx_pkt;
   uint16_t tx_curr_index;
   struct mtip_pkt_priv *pkt_priv = NULL;

   priv = netdev_priv(netdev);

   link_index = priv->link_index;
   lock = &(priv->lock);

   // allocate space to hold dma_pkt pointers
   pkts = mtip_dma_alloc_dma_pkt_ptr(GFP_ATOMIC);

   pkts[0] = mtip_dma_alloc_dma_pkt(GFP_ATOMIC);
   memset(pkts[0], 0, sizeof(struct ecpri_dma_pkt));

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
   
   // allocate mtip packet priv structure
   pkt_priv = (struct mtip_pkt_priv *)kmalloc(sizeof(struct mtip_pkt_priv), GFP_ATOMIC);
   if(pkt_priv == NULL)
   {
       CSMLOGERR("Pkt priv alloc failed\n");
       goto cleanup;
   }
   pkt_priv->skb = skb;
   pkt_priv->tx_index = priv->tx_curr_index;

   pkts[0]->user_data = (void*)pkt_priv;

   spin_lock_irqsave(lock, flags);

   // update tx stats
   ++(platform_driver_priv->mtip_links[link_index]->net_stats.tx_packets);

   platform_driver_priv->mtip_links[link_index]->net_stats.tx_bytes += skb->len;

   spin_unlock_irqrestore(lock, flags);

   CSMLOGDBG("mtip_send_packet hdl %d, link: %d, skb->data: 0x%lx len: %d seq_num %d \n", hdl, link_index, (unsigned long)buffs[0]->virt_base, skb->len, ts_seq_num);

#ifdef MTIP_DUMP_PACKETS
   mtip_dma_dump_packet(skb->data, skb->len);
#endif

   tx_curr_index = priv->tx_curr_index;
   tx_pkt = priv->tx_pkts[tx_curr_index];

   if(tx_pkt)
   {
      CSMLOGINFO("PT:TX COMP MISSED FOR THIS PACKET-FREE THIS PACKET:link_index=%d,tx_curr_index=%d,pkt=0x%x\n",link_index,tx_curr_index,tx_pkt);
      mtip_dma_free_pkt(tx_pkt);
   }
   priv->tx_pkts[tx_curr_index] = pkts[0];

   res = (ecpri_dma_eth_driver_ops.ecpri_dma_eth_transmit)(hdl, pkts, 1, commit);

   if (res < 0)
   {
      CSMLOGERR("DMA transmit failed for handle %d with res = %d\n", hdl, res);
      if(pkts[0])
      {
         pkt_priv = (struct mtip_pkt_priv *)(pkts[0]->user_data);
         if(pkt_priv)
            pkt_priv->skb = NULL;
         mtip_dma_free_pkt(pkts[0]);
         priv->tx_pkts[tx_curr_index] = NULL;

      }
      goto ret;
   }
   priv->tx_curr_index = (tx_curr_index + 1)% MTIP_TX_RING_SIZE;
   goto ret;

cleanup:
   mtip_dma_free_pkt(pkts[0]);
ret:
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
    char* tmp=NULL;
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

    CSMLOGPTP("Rx packet timestamp %ld, timestamp_secs %d, timestamp_nsecs %d",
               timestamp, timestamp_secs, timestamp_nsecs);
    tmp=(char*)head_skb->data;
    
    CSMLOGPTP("pkt_type=%x,seq_id=%x%x,skb=0x%lx,timestamp_secs=%d,timestamp_nsecs=%d \
       \n",tmp[46],tmp[44],tmp[45],(unsigned long)head_skb->data, \
       timestamp_secs,timestamp_nsecs,__func__);
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
}

static u16 csum(u16 old_csum)
{
    u16 new_checksum = 0;
    new_checksum = ~(~old_csum + (-8) + 0);
    return new_checksum;
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
    struct mtip_pkt_priv *pkt_priv = NULL;
    struct ethhdr *eth;
    unsigned char tmp_addr[ETH_ALEN];
    unsigned char tmp_ip_addr[4];
    struct icmphdr *icmp;
    char *str;
    u16 old_csum = 0;

    if(pkts == NULL)
    {
      CSMLOGERR("pkts is NULL\n");
      return;
    }
    priv = netdev_priv(netdev);
    link_index = priv->link_index;
    lock = &(priv->rx_lock);
    sec_dev = priv->sec_dev;

    status_code = pkts[s_idx]->status_code;
    pkt = pkts[s_idx]->pkt;
    if(pkt == NULL)
    {
      CSMLOGERR("pkt is NULL\n");
      return;
    }
    num_of_buffers = pkt->num_of_buffers;
    buffs = (struct ecpri_dma_mem_buffer **)pkt->buffs;
    if(buffs == NULL || buffs[0] == NULL)
    {
      CSMLOGERR("buffs is NULL\n");
      return;
    }

    size = buffs[0]->size;
    head_base = buffs[0]->virt_base;
    pkt_priv = (struct mtip_pkt_priv *)(pkt->user_data);
    head_skb = pkt_priv->skb;
    pkt_priv->skb = NULL;
    curr_skb = head_skb;
    if(head_skb == NULL)
    {
      CSMLOGERR("head_skb is NULL\n");
      return;
    }

    skb_put(head_skb, size);    

    // set the ethernet protocol type
    head_skb->protocol = eth_type_trans(head_skb, netdev);

    for (k = s_idx+1; k <= e_idx; k++)
    {
        pkt = pkts[k]->pkt;
        buffs = (struct ecpri_dma_mem_buffer **)pkt->buffs;
        size = buffs[0]->size;
        pkt_priv = (struct mtip_pkt_priv *)(pkt->user_data);
        nskb = pkt_priv->skb;
        pkt_priv->skb = NULL;
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

    if ((status_code == ECPRI_DMA_STATUS_CODE_PTP) ||
        (status_code == ECPRI_DMA_STATUS_CODE_QUDP_TRAPPED_PKT_PKT_0) ||
        (status_code == ECPRI_DMA_STATUS_CODE_QUDP_TRAPPED_PKT_PKT_1) ||
	(status_code == ECPRI_DMA_STATUS_CODE_QUDP_TRAPPED_PKT_PKT_2) ||
	(status_code == ECPRI_DMA_STATUS_CODE_QUDP_TRAPPED_PKT_PKT_3))
    {
        mtip_dma_skb_timestamp(head_skb);
    }

       if(link_index == MTIP_L2_ETH_LINK_INDEX && mtip_c2c2_loopback_mode != MTIP_MODE_DEFAULT && mtip_loopback_swap_addr)
       {
           CSMLOGDBG("swap addr packet\n");
           eth = (struct ethhdr *)(head_base);
           str=(char*)head_base;

	   // Check if packet is ARP, make ARP response
           if(str[12]==0x8 && str[13]==0x6)
           {
               tmp_addr[0]=0x48;
               tmp_addr[1]=0xA2;
               tmp_addr[2]=0x7E;
               tmp_addr[3]=0xDB;
               tmp_addr[4]=0x00;
               tmp_addr[5]=0x00;

               memcpy(tmp_ip_addr,&str[38], 4);
               memcpy(&str[38],&str[28], 4);
               memcpy(&str[28],&tmp_ip_addr, 4);
               str[21]=0x02;
               memcpy(&str[0],&str[6], 6);
               memcpy(&str[6],&tmp_addr, 6);
               memcpy(&str[22],&tmp_addr, 6);
               memcpy(&str[32],&str[0], 6);
           }
           else 
           {
	       // Make ICMP response
               memcpy(tmp_addr,eth->h_source, ETH_ALEN);
               memcpy(eth->h_source,eth->h_dest, ETH_ALEN);
               memcpy(eth->h_dest, tmp_addr, ETH_ALEN);

               icmp = (struct icmphdr *)(head_base + ETH_HLEN+20);
               icmp->type = 0;
               old_csum = icmp->checksum;
               icmp->checksum = csum(old_csum);
               // fixup the packet: ONLY IF LOOPBACK IS ENABLED
               iphdr_ptr = (struct iphdr *)(head_base + ETH_HLEN);
               fixup_packet(netdev, head_base, iphdr_ptr, head_skb->len);
           }
       }
       else if(link_index != MTIP_L2_ETH_LINK_INDEX && mtip_loopback_mode != MTIP_MODE_DEFAULT && mtip_loopback_swap_addr)
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
            return;
        }
    }
    
    napi_gro_receive(napi_ptr, head_skb);

}
 

int mtip_dma_poll_tx_comp_packets(struct net_device *netdev, struct napi_struct *napi_ptr, ecpri_dma_eth_conn_hdl_t hdl,
                             int budget, int* npackets, int *num_buffers)
{
   int rv;
   struct ecpri_dma_pkt_completion_wrapper **pkts;
   struct mtip_dma_tx_comp_params tx_comp_params={0};
   struct mtip_netdev_priv* priv;
   u32 link_index;
   ecpri_dma_eth_conn_hdl_t actual_handle = hdl;

   priv = netdev_priv(netdev);

   link_index = priv->link_index;

   pkts=priv->tx_comp_pkts;
   if (pkts == NULL)
   {
       rv = -1;
       goto out;
   }

   // set the number of packets to 0
   *npackets = 0;

   // read the packets
   rv = (ecpri_dma_eth_driver_ops.ecpri_dma_eth_tx_poll)(actual_handle, budget,
                                                         (struct ecpri_dma_pkt_completion_wrapper **)pkts,
                                                          npackets);

   if (rv < 0)
   {
      CSMLOGERR("dma_eth_tx_poll hdl: %d returned: %d\n", actual_handle, rv);
   }
   else
   {
      CSMLOGDBG("read from hdl %d: actual read tx comp packets: %d\n", actual_handle, *npackets);
      tx_comp_params.local_comp_pkts = pkts;
      tx_comp_params.num_of_completed = *npackets;
      mtip_process_tx_comp_cb(hdl, &tx_comp_params);
      goto out;
   }

out:
   return rv;
}


int mtip_dma_poll_rx_packets(struct net_device *netdev, struct napi_struct *napi_ptr, ecpri_dma_eth_conn_hdl_t hdl, 
                             int budget, int* npackets, int *num_buffers)
{
   int j, k, s_idx;
   int rv = 0;
   struct ecpri_dma_pkt_completion_wrapper **pkts = NULL; 
   struct mtip_netdev_priv* priv;
   u32 link_index;
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

   pkts = priv->rx_comp_pkts;
   if (pkts == NULL)
   {
       rv = -1;
       goto out;
   }

   // set the number of packets to 0
   *npackets = 0;

   // read the packets
   rv = (ecpri_dma_eth_driver_ops.ecpri_dma_eth_rx_poll)(actual_handle, budget, 
                                                         (struct ecpri_dma_pkt_completion_wrapper **)pkts, 
                                                          npackets);

   if (rv < 0)
   {
      *npackets = 0;
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

out:
   return rv;
}

int mtip_dma_get_ring_state(ecpri_dma_eth_conn_hdl_t hdl, u32* tx_available, u32* rx_available)
{
    int rv;

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

// FREE Complete DMA Packet along with Buffers, Preheader and Skb

void mtip_dma_free_pkt(struct ecpri_dma_pkt* pkt)
{
   struct ecpri_dma_tx_header *pre_header_buff;
   struct ecpri_dma_mem_buffer **buffs;
   struct mtip_pkt_priv *pkt_priv = NULL;
   int j,num_buffers;

   if(!pkt)
      return;

   if(pkt->buffs)
   {
      buffs = (struct ecpri_dma_mem_buffer **)pkt->buffs;
      num_buffers = pkt->num_of_buffers;

      for (j = 0; j < num_buffers; ++j)
      {
         if(num_buffers == 2 && j == 0)
         {
            pre_header_buff = (struct ecpri_dma_tx_header *)buffs[j]->virt_base;
            // free the pre header buff
            if(pre_header_buff)
               mtip_dma_free_tx_header(pre_header_buff);
         }
         mtip_dma_free_mem_buffer(buffs[j]);
      }
      if(num_buffers == 2)
         mtip_dma_free_mem_buffer_dual_ptr(buffs);
      else
         mtip_dma_free_mem_buffer_single_ptr(buffs);
   }

   // free the skb
   pkt_priv = (struct mtip_pkt_priv *)(pkt->user_data);
   if(pkt_priv)
   {
      if(pkt_priv->skb)
         dev_kfree_skb(pkt_priv->skb);
      kfree(pkt_priv);
   }

   mtip_dma_free_dma_pkt(pkt);
}

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

