//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#ifndef _MTIP_PTP_H
#define _MTIP_PTP_H

#include <linux/slab.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/phylink.h>

#define MTIP_PKT_TS_SEQ_MASK 0x07

struct mtip_tx_ts_node
{
   struct list_head list;
   u32              tstamp_secs;
   u32              tstamp_nsecs;
   u8               ts_seq_num;
};

struct mtip_tx_ts_skb_node
{
   struct list_head list;
   struct sk_buff *skb;
   u8 ts_seq_num;
};

/*
 * list of TX Timestamps read
 */
struct mtip_tx_ts_list
{
  struct list_head head;
  unsigned int count;
};

/*
 * list of Tx SKBs pending to be timestamped
 */
struct mtip_tx_ts_skb_list
{
  struct list_head head;
  unsigned int count;
};

int mtip_ptp_initialize(u32 link_index);
int mtip_ptp_handle_hwtstamp_ioctl(struct ifreq *ifr, u32 link_index);

void mtip_ptp_set_rx_timestamp(struct sk_buff* skb, u32 timestamp_secs, u32 timestamp_nsecs);
void mtip_ptp_set_tx_timestamp(struct sk_buff* skb, u32 timestamp_secs, u32 timestamp_nsecs);

void post_mtip_process_timestamp(u32 link_index, u32 timestamp_secs, u32 timestamp_nsecs, u8 ts_seq_num);
void run_mtip_process_timestamp(void* workptr);

void mtip_ptp_resolve_queues(u32 link_index);

void mtip_ptp_tx_ts_lock_init(u32 link_index);
void mtip_ptp_tx_ts_lock_acquire(u32 link_index);
void mtip_ptp_tx_ts_lock_release(u32 link_index);

int mtip_ptp_tx_ts_list_initialize(u32 link_index);
int mtip_ptp_tx_ts_list_finalize(u32 link_index);
int mtip_ptp_tx_ts_list_size(u32 link_index);
int mtip_ptp_tx_ts_list_push(u32 link_index, u32 tstamp_secs, u32 tstamp_nsecs, u8 ts_seq_num);
int mtip_ptp_tx_ts_list_pop(u32 link_index, u32* tstamp_secs, u32* tstamp_nsecs, u8* ts_seq_num);
int mtip_ptp_tx_ts_list_peek(u32 link_index, u32* tstamp_secs, u32* tstamp_nsecs, u8* ts_seq_num);

int mtip_ptp_tx_ts_skb_list_initialize(u32 link_index);
int mtip_ptp_tx_ts_skb_list_finalize(u32 link_index);
int mtip_ptp_tx_ts_skb_list_size(u32 link_index);
int mtip_ptp_tx_ts_skb_list_push(u32 link_index, struct sk_buff *skb, u8 ts_seq_num);
int mtip_ptp_tx_ts_skb_list_pop(u32 link_index, struct sk_buff** skb, u8* ts_seq_num);
int mtip_ptp_tx_ts_skb_list_peek(u32 link_index, struct sk_buff** skb, u8* ts_seq_num);

#endif // _MTIP_PTP_H
