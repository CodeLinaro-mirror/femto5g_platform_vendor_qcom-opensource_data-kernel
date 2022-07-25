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
#include "mtip_ethtool.h"
#include "mtip_client.h"
#include "mtip_ptp.h"
#include "mtip_debug_eth.h"

int macsec_eth_set_macsec_ops(const struct macsec_ops* rb_macsec_ops)
{
    int i;

    // set the macsec ops of the platform
    platform_driver_priv->security_macsec_ops = (struct macsec_ops*)rb_macsec_ops;

    for (i = 0; i < MTIP_MAX_LINKS; ++i)
    {
        if (platform_driver_priv->mtip_links[i] != NULL)
        {
            platform_driver_priv->mtip_links[i]->dev->macsec_ops = rb_macsec_ops;
            platform_driver_priv->mtip_links[i]->dev->features |= NETIF_F_HW_MACSEC;
        }
    }
    return 0;
}

EXPORT_SYMBOL(macsec_eth_set_macsec_ops);

int macsec_eth_lookup_eth_link_by_netdev(struct net_device* netdev, u32* link_index)
{
    struct mtip_netdev_priv* priv;

    priv = netdev_priv(netdev);

    *link_index = priv->link_index;
    return 0;
}

EXPORT_SYMBOL(macsec_eth_lookup_eth_link_by_netdev);

struct net_device* macsec_eth_get_netdev_from_link(u32 link_index)
{
    if (platform_driver_priv->mtip_links[link_index] == NULL)
    {
        return NULL;
    }
    return platform_driver_priv->mtip_links[link_index]->dev;
}

EXPORT_SYMBOL(macsec_eth_get_netdev_from_link);

static void post_mtip_replenish_dma_rx_buffers(struct net_device *netdev, ecpri_dma_eth_conn_hdl_t hdl, u32 num_of_pkts)
{
   struct mtip_replenish_dma_rx_buffers_task* taskstruct = kmalloc(sizeof(struct mtip_replenish_dma_rx_buffers_task), GFP_ATOMIC);
   taskstruct->netdev = netdev;
   taskstruct->hdl = hdl;
   taskstruct->num_of_pkts = num_of_pkts;
   mtip_queue_work(MTIP_WORKQ_TASK_REPLENISH_RX_BUFFERS, taskstruct);
}

void run_mtip_replenish_dma_rx_buffers(void* work_ptr)
{
   int rv;

   struct mtip_replenish_dma_rx_buffers_task* taskstruct = (struct mtip_replenish_dma_rx_buffers_task*)work_ptr;
   rv = mtip_replenish_dma_rx_buffers(taskstruct->netdev, taskstruct->hdl, taskstruct->num_of_pkts);

   // free the taskstruct
   kfree(taskstruct);
}

void post_mtip_set_rx_mode(ecpri_dma_eth_conn_hdl_t hdl, enum ecpri_dma_notify_mode setmode)
{
   struct mtip_set_rx_mode_task* taskstruct = kmalloc(sizeof(struct mtip_set_rx_mode_task), GFP_ATOMIC);
   taskstruct->hdl = hdl;
   taskstruct->setmode = setmode;
   mtip_queue_work(MTIP_WORKQ_TASK_SET_RX_MODE, taskstruct);
}

void run_mtip_set_rx_mode(void* work_ptr)
{
   int rv;
   struct mtip_set_rx_mode_task* taskstruct = (struct mtip_set_rx_mode_task*)work_ptr;

   CSMLOGINFO("setting Rx mode to %d for hdl %d\n", taskstruct->setmode, taskstruct->hdl);

   rv = (ecpri_dma_eth_driver_ops.ecpri_dma_eth_rx_mode_set)(taskstruct->hdl, taskstruct->setmode);

   // free the taskstruct
   kfree(taskstruct);
}

void post_mtip_tx_comp_cb(void *user_data, ecpri_dma_eth_conn_hdl_t hdl, struct ecpri_dma_pkt_completion_wrapper **comp_pkts, u32 num_of_completed)
{
   struct mtip_tx_comp_cb_task* taskstruct = kmalloc(sizeof(struct mtip_tx_comp_cb_task), GFP_ATOMIC);
   taskstruct->user_data = user_data;
   taskstruct->hdl = hdl;
   taskstruct->comp_pkts = comp_pkts;
   taskstruct->num_of_completed = num_of_completed;
   mtip_queue_work(MTIP_WORKQ_TASK_TX_COMP_CB, taskstruct);
}

void run_mtip_tx_comp_cb(void* work_ptr)
{
   int i;
   int j;
   struct mtip_tx_comp_cb_task* taskstruct = (struct mtip_tx_comp_cb_task*)work_ptr;
   ecpri_dma_eth_conn_hdl_t hdl;
   struct ecpri_dma_pkt_completion_wrapper **comp_pkts;
   u32 num_of_completed;
   struct ecpri_dma_pkt_completion_wrapper *comp;
   struct ecpri_dma_pkt* pkt = NULL;
   struct sk_buff *skb;
   struct ecpri_dma_mem_buffer **buffs;
   unsigned int num_of_buffers;
   struct net_device *netdev = NULL;
   struct mtip_netdev_priv *priv;
   u32 link_index;
   bool free_skb = true;
   u64 nanosecs;

   hdl = taskstruct->hdl;
   comp_pkts = taskstruct->comp_pkts;
   num_of_completed = taskstruct->num_of_completed;

   CSMLOGINFO("Tx comp callback for hdl: %d, num_of_completed: %d\n", hdl, num_of_completed);

   // process the Tx completions
   for (i = 0; i < num_of_completed; ++i)
   {
      // for each completed packet
      comp = comp_pkts[i];
      pkt = comp->pkt;

      skb = (struct sk_buff*)pkt->user_data;

      CSMLOGINFO("Tx comp for hdl: %d, skb->data: 0x%lx\n", hdl, (unsigned long)skb->data);

      // store the netdev
      netdev = skb->dev;
      priv = netdev_priv(netdev);
      link_index = priv->link_index;

      free_skb = true;

      // check if this skb needs HW timestamping
      if ((skb_shinfo(skb)->tx_flags & SKBTX_IN_PROGRESS)  != 0)
      {
          CSMLOGINFO("Tx comp cb for packet needing HW_TSTAMP\n");

          // this packet needs to be timestamped
          // acquire the ptp lock
          mtip_ptp_tx_ts_lock_acquire(link_index);

          // check if there is a timestamp available
          if (mtip_ptp_tx_ts_list_size(link_index) == 0)
          {
              // no timestamp interrupt received yet
              // push the skb to the list
              mtip_ptp_tx_ts_skb_list_push(link_index, skb);

              // don't free the skb just yet
              free_skb = false;
          }
          else
          {
              // there is a timestamp available
              mtip_ptp_tx_ts_list_pop(link_index, &nanosecs);

              // set the timestamp of the skb
              mtip_ptp_set_tx_timestamp(skb, nanosecs);

              free_skb = true;
          }

          // release the ptp lock
          mtip_ptp_tx_ts_lock_release(link_index);
      }
      
      if (free_skb == true) {
          // no Tx timestamping needed for this packet
          CSMLOGDBG("freeing skb hdl: %d, len: %d\n", hdl, skb->len);

          dev_kfree_skb(skb);
      }

      buffs = (struct ecpri_dma_mem_buffer **)pkt->buffs;
      num_of_buffers = pkt->num_of_buffers;

      CSMLOGDBG("i: %d, buffers: %d\n", i, num_of_buffers);

      for (j = 0; j < num_of_buffers; ++j) {
         // free the mem buffer
         kfree(buffs[j]);
      }

      // free the container
      kfree(buffs);

      // free the dma pkt
      kfree(pkt);
   }

   // free the completion wrappers
   for (i = 0; i < num_of_completed; ++i)
   {
      kfree(comp_pkts[i]);
   }

   // free the container of comp_pkts
   kfree(comp_pkts);

   // free the taskstruct
   kfree(taskstruct);

   // check if there is space for at least one packet
   // should be true since we just got a comp cb
   if (mtip_dma_tx_available(hdl) == true)
   {
      if (netif_queue_stopped(netdev))
      {
         CSMLOGINFO("netdev queue stopped... waking now\n");
         
         // wake the queue
         netif_wake_queue(netdev);
      }
   }
}

void post_mtip_process_link_state(u32 link_index, bool link_up)
{
   struct mtip_process_link_state_task* taskstruct = kmalloc(sizeof(struct mtip_process_link_state_task), GFP_ATOMIC);
   taskstruct->link_index = link_index;
   taskstruct->link_up = link_up;
   mtip_queue_work(MTIP_WORKQ_TASK_PROCESS_LINK_STATE, taskstruct);
}

void run_mtip_process_link_state(void* work_ptr)
{
    struct mtip_process_link_state_task* taskstruct = (struct mtip_process_link_state_task*)work_ptr;
    u32 link_index = taskstruct->link_index;
    bool link_up = taskstruct->link_up;

    if (link_up)
    {
        CSMLOGINFO("Processing LINK_UP for link_index: %d\n", link_index);

        // enable tx_rx on the link
        mtip_mac_enable_tx_rx(link_index);
    }
    else
    {
        CSMLOGINFO("Processing LINK_DOWN for link_index: %d\n", link_index);

        // disable tx_rx on the link
        mtip_mac_disable_tx_rx(link_index);
    }
}

static int mtip_set_mac_address(struct net_device *dev, void *addr)
{
   unsigned long flags;
   struct mtip_netdev_priv* priv;
   u32 link_index;
   struct sockaddr *saddr = addr;
   spinlock_t *lock;

   if (!is_valid_ether_addr(saddr->sa_data))
      return -EADDRNOTAVAIL;

   priv = netdev_priv(dev);

   link_index = priv->link_index;
   lock = &(priv->lock);

   CSMLOGINFO("mtip_set_mac_address called for link_index: %d\n", link_index);

   spin_lock_irqsave(lock, flags);
   memcpy(dev->dev_addr, saddr->sa_data, ETH_ALEN);
   mtip_mac_set_mac_address(priv, saddr);
   spin_unlock_irqrestore(lock, flags);

   /* Send update to clients */
   post_mtip_client_send_event(ETH_ECPRISS_EVENT_UP, link_index);

   return 0;
}

static int mtip_set_netdev_hw_mac_addr(struct net_device *netdev, u32 link_index)
{
    u32 port_device_index;
    u32 link_device_index;
    uint8_t saddr[ETH_ALEN];

    mtip_lookup_device_by_link_index(link_index, &port_device_index, &link_device_index);

    mtip_mac_get_mac_address_by_device(port_device_index, link_device_index, saddr);

    CSMLOGINFO("Setting MAC address of link_index: %d port: %d, link: %d\n", link_index, port_device_index, link_device_index);

    memcpy(netdev->dev_addr, saddr, ETH_ALEN);

    return 0;
}

/* NAPI Poll function */
int mtip_napi_poll(struct napi_struct *napi_ptr, int budget)
{
   int rv = 0;
   int npackets = 0;
   enum ecpri_dma_notify_mode setmode = ECPRI_DMA_NOTIFY_MODE_IRQ;
   struct mtip_link_info* link = container_of(napi_ptr, struct mtip_link_info, napi);
   ecpri_dma_eth_conn_hdl_t hdl = link->dma_hdl;
   u32 link_index;
   struct net_device* dev;
   struct mtip_netdev_priv *priv;
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

   rv = mtip_lookup_link_index_by_handle(hdl, &link_index);

   // HANDLE THE ERROR
   if (rv < 0)
   {
      CSMLOGERR("Unable to find link_index of hdl: %d\n", hdl);
      return 0;
   }

   dev = platform_driver_priv->mtip_links[link_index]->dev;
   priv = netdev_priv(dev);

   CSMLOGINFO("mtip_napi_poll called with budget %d for link_index %d hdl %d\n", budget, link_index, hdl);

   // read the packets and push into the stack
   rv = mtip_dma_poll_rx_packets(dev, napi_ptr, hdl, budget, &npackets);

   // HANDLE THE ERROR
   if (rv < 0)
   {
      CSMLOGERR("poll_rx_packets failed for hdl: %d\n", hdl);
   }

   /* If we processed all packets, we're done; tell the kernel and re-enable ints */
   if (npackets < budget) {
      napi_complete(napi_ptr);

      // set the rx mode to IRQ
      post_mtip_set_rx_mode(actual_handle, setmode);
   }
   else
   {
      // we can remain in POLL
      setmode = ECPRI_DMA_NOTIFY_MODE_POLL;

      // set the rx modE
      post_mtip_set_rx_mode(actual_handle, setmode);
   }

   // replenish the rx buffers for the packets processed
   post_mtip_replenish_dma_rx_buffers(dev, actual_handle, npackets);
   return npackets;
}

/* Transmit the packet */
static int mtip_start_xmit(struct sk_buff *skb, struct net_device *netdev)
{
   u32 link_index;
   ecpri_dma_eth_conn_hdl_t hdl;
   struct mtip_netdev_priv *priv;
   int ret;
   ecpri_dma_eth_conn_hdl_t other_hdl;
   u32 other_link_index;

   CSMLOGDBG("mtip_start_xmit called\n");

   priv = netdev_priv(netdev);
   link_index = priv->link_index;
   hdl = platform_driver_priv->mtip_links[link_index]->dma_hdl;

   if(priv->link_index == MTIP_DEBUG_ETH_LINK_INDEX){
      return mtip_debug_eth_start_xmit(skb, netdev);
   }

   if (mtip_loopback_mode != MTIP_MODE_DEFAULT)
   {
       switch (hdl)
       {
       case 1:
          other_hdl = 2;
          break;
       case 2:
          other_hdl = 1;
          break;
       case 3:
          other_hdl = 4;
          break;
       case 4:
          other_hdl = 3;
          break;
       case 5:
          other_hdl = 6;
          break;
       case 6:
          other_hdl = 5;
          break;
       case 7:
          other_hdl = 8;
          break;
       case 8:
          other_hdl = 7;
          break;
       case 9:
          other_hdl = 10;
          break;
       case 10:
          other_hdl = 9;
          break;
       case 11:
          other_hdl = 12;
          break;
       case 12:
          other_hdl = 11;
          break;
       }

       if (mtip_lookup_link_index_by_handle(other_hdl, &other_link_index) < 0)
       {
          CSMLOGERR("did not find other link index for hdl: %d\n", other_hdl);

          // free the skb
          dev_kfree_skb(skb);

          // drop the packet
          return NETDEV_TX_OK;
       }

       // check if it is a neighbor solicitation msg and drop it for now
       if ((skb->data[0] == 0x33) && (skb->data[1] == 0x33) && (skb->data[12] == 0x86) && (skb->data[13] == 0xdd))
       {
          CSMLOGERR("Dropping neighbor solicitation msg in loopback mode\n");

          // free the skb
          dev_kfree_skb(skb);

          // drop the packet
          return NETDEV_TX_OK;
       }

       // check that both links are in OPEN state
       if ((platform_driver_priv->mtip_links[link_index]->state != MTIP_LINK_STATE_OPEN) || 
           (platform_driver_priv->mtip_links[other_link_index]->state != MTIP_LINK_STATE_OPEN))
       {
          CSMLOGERR("Waiting for both interfaces to open... dropping\n");

          // free the skb
          dev_kfree_skb(skb);

          // drop the packet
          return NETDEV_TX_OK;
       }
   }

   // check if this packet needs timestamping
   if ((skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) != 0)
   {
       CSMLOGINFO("Tx packet needing HW_TSTAMP skb->data: 0x%lx\n", (unsigned long)skb->data);

       // set the flag to in progress
       skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
   }

   ret = mtip_dma_send_packet(netdev, hdl, skb);

   // HANDLE THE ERROR
   if (ret < 0) {
      if (!netif_queue_stopped(netdev))
      {
         netif_stop_queue(netdev);

         CSMLOGERR("Tx ring full when queue awake\n");
      }
      return NETDEV_TX_BUSY;
   }

   // commit the packet
   mtip_dma_tx_commit(hdl);

   // check if there is space for at least one packet
   if (mtip_dma_tx_available(hdl) == false)
   {
      // wait for space to become available
      netif_stop_queue(netdev);

      CSMLOGERR("Tx ring full when queue awake\n");
   }
   return NETDEV_TX_OK;
}

static void mtip_configure_hashtable(struct mtip_netdev_priv *priv, u64 original_hashtablebits, u64 new_hashtablebits)
{
    u8 i;
    u8 val = 0;
    u64 pattern = 0x01;
    u64 delta = original_hashtablebits ^ new_hashtablebits;

    CSMLOGDBG("orig: %x, new: %x, delta: %x\n", original_hashtablebits, new_hashtablebits, delta);

    for (i = 0; i < MTIP_MAC_HASHTABLE_SIZE; ++i)
    {
        if ((delta & pattern) != 0)
        {
            if ((new_hashtablebits & pattern) != 0)
            {
                val = 0x01;
            }
            mtip_mac_set_hashtable_entry(priv, i, val);

            CSMLOGDBG("set hashtable entry: %d to val: %d\n", i, val);
        }
        pattern = pattern << 1;
    }
}

static u8 mtip_xor_bits(u8 bits)
{
    int i;
    u8 rv = 0;
    u8 tmpbits = bits;
    u8 val;

    for (i = 0; i < 8; ++i) {
        // find the least significant bit
        val = tmpbits & 0x01;

        rv = rv ^ val;

        tmpbits = tmpbits >> 1;
    }

    return rv;
}

static void mtip_generate_entry_address(struct netdev_hw_addr *ha, u8* entry_address)
{
    int i;
    u8 val;
    *entry_address = 0;

    // set the least significant bits
    for (i = 0; i < 6; ++i)
    {
        val = mtip_xor_bits(ha->addr[i]);

        CSMLOGDBG("addr: 0x%x, val: %d, i: %d\n", ha->addr[i], val, i);

        // shift val by i
        val = val << i;

        *entry_address |= val;
    }

    CSMLOGDBG("generated entry address: 0x%x\n", *entry_address);
}

static void mtip_generate_hashtablebits(struct net_device *netdev, u64* hashtablebits)
{
    int i;
    struct netdev_hw_addr *ha;
    u8 entry_address;
    u64 pattern;

    *hashtablebits = 0;

    netdev_for_each_mc_addr(ha, netdev) {

        mtip_generate_entry_address(ha, &entry_address);

        CSMLOGDBG("entry address generated: 0x%x\n", entry_address);

        pattern = 0x01;
        // set the corresponding hashtablebit to 1
        for (i = 0; i < MTIP_MAC_HASHTABLE_SIZE; ++i) {
            pattern = pattern << 1;
        }
        *hashtablebits |= pattern;

        CSMLOGDBG("hashtablebits: 0x%x\n", hashtablebits);
    }

    CSMLOGDBG("Final hashtablebits: 0x%x\n", hashtablebits);
}

/* Configure Multicast and Promiscuous modes */
static void mtip_rx_mode_set(struct net_device *netdev)
{
   bool is_multicast_enabled = !!(netdev->flags & IFF_MULTICAST);
   bool all_multi_needed = !!(netdev->flags & IFF_ALLMULTI);
   bool promisc_needed = !!(netdev->flags & IFF_PROMISC);
   struct mtip_netdev_priv *priv;
   u32 link_index;
   u64 hashtablebits = 0;
   int ret = 0;

   priv = netdev_priv(netdev);
   link_index = priv->link_index;

   CSMLOGINFO("mtip_rx_mode_set called for link_index: %d (%d, %d, %d)\n", link_index, is_multicast_enabled, all_multi_needed, promisc_needed);

 	if (promisc_needed) 
    {
        /* 
         * Set the PROMISC MODE if IFF_PROMISC is explicitly set 
         */ 
        // set the promiscous mode
        ret = mtip_mac_set_promisc_mode(priv, true);
        CSMLOGINFO("Setting promiscuous mode ON for link index: %d\n", link_index);
 	} 
    else if ((netdev_mc_count(netdev) > MTIP_MAC_HASHTABLE_SIZE) || (all_multi_needed))
    {
        ret = mtip_mac_set_promisc_mode(priv, true);
        CSMLOGINFO("Enabling all multicast for link index: %d\n", link_index);
 	} 
    else
    {
        if (netdev_mc_empty(netdev))
        {
            hashtablebits = 0;
        }
        else
        {
            mtip_generate_hashtablebits(netdev, &hashtablebits);
        }

        CSMLOGINFO("Setting up hashtable for multicast for link index: %d, original: 0x%x, new: 0x%x\n", link_index, priv->hashtablebits, hashtablebits);

        // reset promisc mode
        mtip_mac_set_promisc_mode(priv, false);

        mtip_configure_hashtable(priv, priv->hashtablebits, hashtablebits);

        priv->hashtablebits = hashtablebits;
    }

    /* update the topology only if there was an actual change */
    if (ret == 0)
    {
        /* Send update to clients */
        post_mtip_client_send_event(ETH_ECPRISS_EVENT_UP, link_index);
    }

   return; 
}

/* Change the Maximum Transfer Unit (MTU) */
static int mtip_change_mtu(struct net_device *netdev, int new_mtu)
{
   unsigned long flags;
   struct mtip_netdev_priv *priv;
   spinlock_t *lock;
   u32 link_index;
   
   priv = (struct mtip_netdev_priv*)netdev_priv(netdev);
   lock = &(priv->lock);
   link_index = priv->link_index;

   CSMLOGINFO("mtip_change_mtu called for link index: %d\n", link_index);

   /* check ranges */
   if ((new_mtu < MTIP_MIN_MTU_SIZE) || (new_mtu > MTIP_MAX_MTU_SIZE))
      return -EINVAL;

   spin_lock_irqsave(lock, flags);
   netdev->mtu = new_mtu;
   mtip_mac_set_frame_length(priv, new_mtu);
   spin_unlock_irqrestore(lock, flags);

   /* Send update to clients */
   post_mtip_client_send_event(ETH_ECPRISS_EVENT_UP, link_index);

   return 0;
}

/* Called when the network interface is made active */
static int mtip_open(struct net_device *netdev)
{
   struct mtip_netdev_priv* priv;
   u32 link_index;
   ecpri_dma_eth_conn_hdl_t hdl;

   priv = netdev_priv(netdev);

   link_index = priv->link_index;

   hdl = platform_driver_priv->mtip_links[link_index]->dma_hdl;

   CSMLOGINFO("mtip_open called for link_index: %d with hdl: %d\n", link_index, hdl);

   if (mtip_loopback_mode == MTIP_MODE_DEFAULT)
   {
       // Configure phylib in poll mode
       priv->phydev->irq = PHY_POLL;

       // PHYLINK-PHY binding and PHY bringup
       phylink_connect_phy(priv->phylink, priv->phydev);

       // Start the PHYLINK
       phylink_start(priv->phylink);
   }

   if(hdl){
      // start the pipe
      mtip_start_dma_pipe(netdev, hdl);

      // set the netdev MAC address from the HW
       mtip_set_netdev_hw_mac_addr(netdev, link_index);

      /*
       * enable napi
       */
      napi_enable(&(platform_driver_priv->mtip_links[link_index]->napi));

      /* 
       * Start the interface's transmit queue 
       * (allowing it to accept packets for transmission) 
       * once it is ready to start sending data. 
       */
      netif_start_queue(netdev);
   }

   /*
    * set the ethtool ops
    */
   mtip_ethtool_set_ops(netdev);

   /* 
    * set the link state to OPEN * 
    */
   platform_driver_priv->mtip_links[link_index]->state = MTIP_LINK_STATE_OPEN; 

   /* Send update to clients */
   post_mtip_client_send_event(ETH_ECPRISS_EVENT_UP, link_index);

   return 0;
}

/* Called when the network interface is disabled */
static int mtip_close(struct net_device *netdev)
{
   struct mtip_netdev_priv* priv;
   ecpri_dma_eth_conn_hdl_t hdl;
   u32 link_index;

   priv = netdev_priv(netdev);

   link_index = priv->link_index;

   hdl = platform_driver_priv->mtip_links[link_index]->dma_hdl;

   CSMLOGINFO("mtip_close called with link_index: %d with hdl: %d\n", link_index, hdl);

   if (mtip_loopback_mode == MTIP_MODE_DEFAULT)
   {
       /* Stop and disconnect the PHY */
       phylink_stop(priv->phylink);
       phylink_disconnect_phy(priv->phylink);
   }

   if(hdl){
      // stop the pipe
      mtip_stop_dma_pipe(hdl);

      /*
       * disable napi
       */
      napi_disable(&(platform_driver_priv->mtip_links[link_index]->napi));

      /* release ports, irq and such -- like fops->close */
      netif_stop_queue(netdev);
   }

   CSMLOGERR("Stopping netdev queue\n");

   platform_driver_priv->mtip_links[link_index]->state = MTIP_LINK_STATE_CLOSE;

   /* Send update to clients */
   post_mtip_client_send_event(ETH_ECPRISS_EVENT_DOWN, link_index);
   return 0;
}

/* Respond to a TX hang
 *  This function is called when a packet transmission fails to
 *   complete within a reasonable time. The driver will mark the error in the
 *   netdev structure and arrange for the device to be reset to a sane state
 *   in order to transmit a new packet.
 */
static void mtip_tx_timeout(struct net_device *netdev, unsigned int txqueue)
{
   CSMLOGERR("mtip_tx_timeout called\n");

   netif_trans_update(netdev); /* prevent tx timeout */
   netif_wake_queue(netdev);
}

/* IOCTL support for the interface */
static int mtip_ioctl(struct net_device *netdev, struct ifreq *ifr, int cmd)
{
   int ret = -EOPNOTSUPP;
   struct mtip_netdev_priv* priv;
   u32 link_index;

   priv = netdev_priv(netdev);
   link_index = priv->link_index;

   CSMLOGINFO("mtip_ioctl called cmd: %d, link_index: %d\n", cmd, link_index);

   if (!netif_running(netdev))
      return -EINVAL;

   switch (cmd) 
   {
   case SIOCGHWTSTAMP:
   case SIOCSHWTSTAMP:
      {
         ret = mtip_ptp_handle_hwtstamp_ioctl(ifr, link_index);
      }
      break;
   default:
      break;
   }
   return ret;
}

static int mtip_siocdevprivate(struct net_device *netdev, struct ifreq *ifr, void __user *udata, int cmd)
{
   int ret = -EOPNOTSUPP;
   struct mtip_netdev_priv* priv;
   u32 link_index;

   priv = netdev_priv(netdev);
   link_index = priv->link_index;

   CSMLOGINFO("mtip_siocdevprivate called cmd: %d, link_index: %d\n", cmd, link_index);

   if (!netif_running(netdev))
      return -EINVAL;

   return ret;
}

/* Provide network statistics info for the interface */
static void mtip_get_stats64(struct net_device *netdev,
			     struct rtnl_link_stats64 *net_stats)
{
   unsigned long flags;
   struct mtip_netdev_priv *priv;
   spinlock_t *lock;
   u32 link_index;

   priv = (struct mtip_netdev_priv*)netdev_priv(netdev);
   lock = &(priv->lock);
   link_index = priv->link_index;

   CSMLOGDBG("mtip_get_stats64 called for link_index: %d\n", link_index);

   spin_lock_irqsave(lock, flags);

   memcpy(net_stats, &(platform_driver_priv->mtip_links[link_index]->net_stats), sizeof(struct rtnl_link_stats64));

   spin_unlock_irqrestore(lock, flags);
   return;
}

/*
 * mtip_netdev_header: fill the eth header 
 * Only needed for test purposes. Use default on target 
 */
static int mtip_netdev_header(struct sk_buff *skb, struct net_device *dev,
		 unsigned short type, const void *daddr, const void *saddr,
                 unsigned int len) {
   struct ethhdr *eth = (struct ethhdr *)skb_push(skb,ETH_HLEN);

   CSMLOGDBG("mtip_netdev_header called\n");
   
   eth->h_proto = htons(type);
   memcpy(eth->h_source, saddr ? saddr : dev->dev_addr, dev->addr_len);
   memcpy(eth->h_dest,   daddr ? daddr : dev->dev_addr, dev->addr_len);
   eth->h_dest[ETH_ALEN-1]   ^= 0x01;   /* dest is us xor 1 */
   return (dev->hard_header_len);
}

static const struct header_ops mtip_header_ops = {
   .create  = mtip_netdev_header,
   .cache   = NULL,
};

static const struct net_device_ops mtip_netdev_ops = {
	.ndo_open		      = mtip_open,
	.ndo_stop		      = mtip_close,
	.ndo_start_xmit	   = mtip_start_xmit,
	.ndo_change_mtu	   = mtip_change_mtu,
	.ndo_eth_ioctl		   = mtip_ioctl,
    .ndo_siocdevprivate = mtip_siocdevprivate,
	.ndo_tx_timeout	   = mtip_tx_timeout,
	.ndo_get_stats64	   = mtip_get_stats64,
	.ndo_set_rx_mode     = mtip_rx_mode_set,
   .ndo_set_mac_address = mtip_set_mac_address,
};

void mtip_netdevice_init(struct net_device *dev) 
{
   struct mtip_netdev_priv* priv;

   CSMLOGINFO("mtip_netdevice_init called 0x%lx\n", (unsigned long)dev);

   ether_setup(dev);

   // HANDLE THE ERROR

   dev->netdev_ops = &mtip_netdev_ops;

   if (mtip_loopback_mode != MTIP_MODE_DEFAULT)
   {
       dev->header_ops = &mtip_header_ops;

       /* add NOARP */
       dev->flags           |= IFF_NOARP;
   }

   dev->watchdog_timeo = MTIP_TIMEOUT;

   priv = netdev_priv(dev);

   // initialize the lock
   spin_lock_init(&priv->lock);
}

enum mtip_link_state_enum mtip_get_link_state_by_device(u32 port_device_index, u32 link_device_index)
{
    u32 link_index;
    mtip_lookup_link_index_by_device(&link_index, port_device_index, link_device_index);

    CSMLOGINFO("Getting link state of link index: %d\n", link_index);

    if (platform_driver_priv->mtip_links[link_index] == NULL) {
        return MTIP_LINK_STATE_INIT;
    }
    else {
        return platform_driver_priv->mtip_links[link_index]->state;
    }
}
