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
   CSMLOGINFO("mtip_dma_ready_cb\n");

   if (platform_driver_priv->dma_is_ready == false) 
   {
      CSMLOGINFO("registering platform driver\n");

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

// tx completion callback
void mtip_dma_tx_comp_cb(void *user_data, ecpri_dma_eth_conn_hdl_t hdl, struct ecpri_dma_pkt_completion_wrapper **comp_pkts, u32 num_of_completed)
{
    int i;
    struct ecpri_dma_pkt_completion_wrapper **local_comp_pkts;

    CSMLOGDBG("mtip_dma_tx_comp_cb hdl: %d, num: %d\n", hdl, num_of_completed);

    if (num_of_completed == 0)
    {
        return;
    }

    // copy the pointers
    local_comp_pkts = (struct ecpri_dma_pkt_completion_wrapper **)kmalloc(num_of_completed * sizeof(struct ecpri_dma_pkt_completion_wrapper *), GFP_ATOMIC);

    for (i = 0; i < num_of_completed; ++i) {
        // allocate teh completion wrapper
        local_comp_pkts[i] = (struct ecpri_dma_pkt_completion_wrapper *)kmalloc(sizeof(struct ecpri_dma_pkt_completion_wrapper), GFP_ATOMIC);

        local_comp_pkts[i]->pkt = comp_pkts[i]->pkt;
        local_comp_pkts[i]->status_code = comp_pkts[i]->status_code;
        local_comp_pkts[i]->comp_code = comp_pkts[i]->comp_code;
    }

    post_mtip_tx_comp_cb(user_data, hdl, local_comp_pkts, num_of_completed);
}

// connect pipe
int mtip_connect_dma_pipe(u32 link_index, ecpri_dma_eth_conn_hdl_t* hdl)
{
   int rv = 0;
   struct ecpri_dma_eth_endpoint_connect_params pipe_params;

   pipe_params.link_index = link_index;
   pipe_params.tx_ring_length = MTIP_TX_RING_SIZE;
   pipe_params.rx_ring_length = MTIP_RX_RING_SIZE;

   pipe_params.p_type = ECPRI_DMA_ENDP_STREAM_DEST_FH;
   pipe_params.tx_mod_cfg.moderation_counter_threshold = MTIP_TX_MOD_COUNTER_THRESHOLD;
   pipe_params.tx_mod_cfg.moderation_timer_threshold = MTIP_TX_MOD_TIMER_THRESHOLD;

   // connect the pipe
   rv = (ecpri_dma_eth_driver_ops.ecpri_dma_eth_connect_endpoints)(&pipe_params, hdl);

   if (rv >= 0)
   {
      CSMLOGINFO("assigned connect handle %d\n", *hdl);
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
      CSMLOGINFO("disconnected pipe with handle %d\n", hdl);
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
      CSMLOGINFO("started pipe %d\n", hdl);
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
      CSMLOGINFO("stopped pipe %d\n", hdl);
   }
   return rv;
}

// replenish dma buffers
int mtip_replenish_dma_rx_buffers(struct net_device *netdev, ecpri_dma_eth_conn_hdl_t hdl, u32 num_of_pkts)
{
   int rv = 0;
   int j;
   int packet_size = MTIP_DMA_RX_PACKET_SIZE;
   struct ecpri_dma_pkt **pkts = NULL;
   struct ecpri_dma_mem_buffer **pbuffs = NULL;
   bool commit = true;
   struct sk_buff *skb;
   struct mtip_netdev_priv* priv;
   u32 link_index;

   priv = netdev_priv(netdev);

   link_index = priv->link_index;

   CSMLOGDBG("replenishing %d packets for hdl %d\n", num_of_pkts, hdl);

   // replenish the rx buffers
   // allocate space to hold pkt pointers
   pkts = (struct ecpri_dma_pkt **)kmalloc(num_of_pkts * sizeof(struct ecpri_dma_pkt *), GFP_KERNEL);

   for (j = 0; j < num_of_pkts; ++j)
   {
      // the dma pkt struct
      pkts[j] = (struct ecpri_dma_pkt *)kmalloc(sizeof(struct ecpri_dma_pkt), GFP_KERNEL);

      // the dma mem buffer struct
      pbuffs = (struct ecpri_dma_mem_buffer **)kmalloc(sizeof(struct ecpri_dma_mem_buffer *), GFP_KERNEL);

      pbuffs[0] = (struct ecpri_dma_mem_buffer *)kmalloc(sizeof(struct ecpri_dma_mem_buffer), GFP_KERNEL);;

      // HANDLE THE ERROR

      pkts[j]->num_of_buffers = 1;

      // allocate an skb where IP is aligned to 4 byte boundaries
      skb = __netdev_alloc_skb_ip_align(netdev, packet_size, GFP_KERNEL);

      // HANDLE THE ERROR

      // set the netdev of the skb
      skb->dev = netdev;

      // allocate space for one packet
      pbuffs[0]->virt_base = skb->data;
      pbuffs[0]->size = packet_size;
      pbuffs[0]->phys_base = 0;

      // allocate space for one mem_buffer
      pkts[j]->buffs = pbuffs;
      pkts[j]->user_data = (void*)skb;
   }

   // replenish the buffers
   rv = (ecpri_dma_eth_driver_ops.ecpri_dma_eth_replenish_buffers)(hdl, pkts, num_of_pkts, commit);

   if (rv < 0)
   {
      CSMLOGERR("failed to replenish packets for hdl: %d\n", hdl);

      // free all the allocated memory
   }

   // we can now free the pkts
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
         CSMLOGINFO("Packet: %d, %x:%x:%x:%x:%x:%x:%x:%x\n", i, buf[index + 0], buf[index + 1], buf[index + 2], buf[index + 3], buf[index + 4], buf[index + 5], buf[index + 6], buf[index + 7]);
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
int mtip_dma_send_packet(struct net_device *netdev, ecpri_dma_eth_conn_hdl_t hdl, struct sk_buff *skb)
{
   struct ecpri_dma_pkt **pkts;
   struct ecpri_dma_mem_buffer ** buffs;
   bool commit = true;
   int res;
   struct mtip_netdev_priv* priv;
   u32 link_index;
   spinlock_t *lock;
   unsigned long flags;

   priv = netdev_priv(netdev);

   link_index = priv->link_index;
   lock = &(priv->lock);

   // allocate space to hold dma_pkt pointers
   pkts = (struct ecpri_dma_pkt**)kmalloc(sizeof(struct ecpri_dma_pkt*), GFP_ATOMIC);

   pkts[0] = (struct ecpri_dma_pkt *)kmalloc(sizeof(struct ecpri_dma_pkt), GFP_ATOMIC);

   buffs = (struct ecpri_dma_mem_buffer **)kmalloc(sizeof(struct ecpri_dma_mem_buffer*), GFP_ATOMIC);

   buffs[0] = (struct ecpri_dma_mem_buffer *)kmalloc(sizeof(struct ecpri_dma_mem_buffer), GFP_ATOMIC);

   spin_lock_irqsave(lock, flags);

   // update tx stats
   ++(platform_driver_priv->mtip_links[link_index]->net_stats.tx_packets);

   platform_driver_priv->mtip_links[link_index]->net_stats.tx_bytes += skb->len;

   spin_unlock_irqrestore(lock, flags);

   // update the buffs
   buffs[0]->size = skb->len;
   buffs[0]->virt_base = skb->data;
   buffs[0]->phys_base = 0;

   pkts[0]->num_of_buffers = 1;
   pkts[0]->buffs = buffs;
   pkts[0]->user_data = (void*)skb;

   CSMLOGDBG("mtip_send_packet hdl %d, link: %d, skb->data: 0x%lx len: %d\n", hdl, link_index, (unsigned long)buffs[0]->virt_base, skb->len);

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
   kfree(pkts);
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

static int mtip_dma_process_packet(struct net_device *netdev, 
                                   struct napi_struct *napi_ptr, 
                                   enum ecpri_dma_status_code status_code, 
                                   enum ecpri_dma_completion_code comp_code, 
                                   struct ecpri_dma_pkt *pkt)
{
   int num_of_buffers;
   struct ecpri_dma_mem_buffer ** buffs;
   unsigned char* base;
   int size;
   int rv = 0;
   struct sk_buff *skb;
   struct mtip_netdev_priv* priv;
   u32 link_index;
   spinlock_t *lock;
   unsigned long flags;
   u64 timestamp;
   u32 timestamp_secs;
   u32 timestamp_nsecs;
   u64* tsptr;
   int i;
   struct iphdr* iphdr;
   struct mtip_security_device *sec_dev;

   priv = netdev_priv(netdev);

   link_index = priv->link_index;
   lock = &(priv->lock);
   sec_dev = priv->sec_dev;

   num_of_buffers = pkt->num_of_buffers;
   buffs = (struct ecpri_dma_mem_buffer **)pkt->buffs;

   // we expect to receive the entire packet in one buffer
   if (num_of_buffers != 1)
   {
      CSMLOGERR("num_of_buffers %d != 1.... dropping\n", num_of_buffers);

      // free up the data structs and return for now
      rv = -1;
      goto out;
   }

   base = buffs[0]->virt_base;
   size = buffs[0]->size;
   skb = (struct sk_buff*)pkt->user_data;

   // TBD: Handle all the error status codes here
   // we handle the following status codes
   if ((ECPRI_DMA_STATUS_CODE_TIMEOUT_ERROR <= status_code) && (status_code <= ECPRI_DMA_STATUS_CODE_UDP_CHECKSUM_ERROR)) 
   {
       CSMLOGERR("Rx packet received status code: %d ... dropping\n", status_code);
#ifdef MTIP_DUMP_PACKETS
       // dump the contents of the modified packet
       mtip_dma_dump_packet(base, size);
#endif
       // free up the data structs and return for now
       rv = -1;
       goto out;
   }

   CSMLOGDBG("Rx packet received status code: %d\n", status_code);

   if (status_code == ECPRI_DMA_STATUS_CODE_PTP)
   {
       CSMLOGERR("Rx packet status code is PTP, packet size = %d\n", status_code, size);

       // the packet holds the 8 bytes TS in trailer
       tsptr = (u64*)(base + size - 8);
       timestamp = *tsptr;

       // number of secs is the upper 32 bits
       timestamp_secs = (u32)(timestamp >> 32);

       // number of nanosecs is the lower 32 bits
       timestamp_nsecs = (u32)(timestamp & 0xFFFFFFFF);

       CSMLOGINFO("Rx packet timestamp %ld, timestamp_secs %d, timestamp_nsecs %d", timestamp, timestamp_secs, timestamp_nsecs);

       // set the timestamp in the skb
       mtip_ptp_set_rx_timestamp(skb, timestamp_secs, timestamp_nsecs);

       skb_put(skb, size - 8);
       //skb->len = size - 8;
   }
   else
   {
       // normal packet
       // pass it to the stack
       skb_put(skb, size);
       //skb->len = size;
   }

   skb->protocol = eth_type_trans(skb, netdev);
   //skb->ip_summed = CHECKSUM_UNNECESSARY; // no need to verify checksum

   spin_lock_irqsave(lock, flags);

   // update rx stats
   ++(platform_driver_priv->mtip_links[link_index]->net_stats.rx_packets);

   platform_driver_priv->mtip_links[link_index]->net_stats.rx_bytes += skb->len + ETH_HLEN;

   spin_unlock_irqrestore(lock, flags);

   if (mtip_loopback_mode != MTIP_MODE_DEFAULT && mtip_loopback_swap_addr)
   {
       // fixup the packet: ONLY IF LOOPBACK IS ENABLED
       iphdr = (struct iphdr *)(base + ETH_HLEN);
       fixup_packet(netdev, base, iphdr, size);
   }

#ifdef MTIP_DUMP_PACKETS
   // dump the contents of the modified packet
   mtip_dma_dump_packet(base, size);
#endif

   if (sec_dev && sec_dev->ops && sec_dev->ops->fixup_rx_skb) {
      if (sec_dev->ops->fixup_rx_skb(skb)) {
         ++(platform_driver_priv->mtip_links[link_index]->net_stats.rx_errors);
         dev_kfree_skb_any(skb);
         goto out;
      }
   }

   napi_gro_receive(napi_ptr, skb);

out:
   // free the container
   for (i = 0; i < num_of_buffers; ++i) 
   {
       kfree(buffs[i]);
   }
   kfree(buffs);

   kfree(pkt);

   return rv;
}

int mtip_dma_poll_rx_packets(struct net_device *netdev, struct napi_struct *napi_ptr, ecpri_dma_eth_conn_hdl_t hdl, int budget, int* npackets)
{
   int j;
   int k;
   int rv;
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

   pkts = (struct ecpri_dma_pkt_completion_wrapper **)kmalloc(budget * sizeof(struct ecpri_dma_pkt_completion_wrapper*), GFP_ATOMIC);

   if (pkts == NULL)
   {
       rv = -1;
       spin_unlock_irqrestore(lock, flags);
       goto out;
   }

   for (j = 0; j < budget; ++j) 
   {
      pkts[j] = (struct ecpri_dma_pkt_completion_wrapper *)kmalloc(sizeof(struct ecpri_dma_pkt_completion_wrapper), GFP_ATOMIC);

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
   rv = (ecpri_dma_eth_driver_ops.ecpri_dma_eth_rx_poll)(actual_handle, budget, (struct ecpri_dma_pkt_completion_wrapper **)pkts, npackets);

   if (rv < 0)
   {
      CSMLOGERR("dma_eth_rx_poll hdl: %d returned: %d\n", actual_handle, rv);
   }
   else
   {
      CSMLOGDBG("read from hdl %d: actual read packets: %d\n", actual_handle, *npackets);

      for (k = 0; k < *npackets; ++k)
      {
         // push the received skb into the stack
          mtip_dma_process_packet(netdev, napi_ptr, pkts[k]->status_code, pkts[k]->comp_code, pkts[k]->pkt);
      }
   }

out1:
   for (j = 0; j < budget; ++j) {
      kfree(pkts[j]);
   }
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
