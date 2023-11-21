//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#ifndef _MTIP_DMA_H
#define _MTIP_DMA_H

#include <linux/slab.h>
#include <linux/list.h>
#include <linux/mutex.h>

#include "ecpri_dma_eth.h"

// this is the extern to connect to dma driver
extern struct ecpri_dma_eth_ops ecpri_dma_eth_driver_ops;

struct mtip_dma_tx_comp_params
{
    void     *user_data;
    ecpri_dma_eth_conn_hdl_t hdl;
    struct ecpri_dma_pkt_completion_wrapper **local_comp_pkts;
    u32 num_of_completed;
};


struct mtip_tx_comp_node
{
   struct list_head list;
   struct mtip_dma_tx_comp_params tx_comp_params;
};

/*
 * list of TX comp call backs
 */
struct mtip_tx_comp_list
{
  struct list_head head;
  unsigned int count;
};

int mtip_dma_tx_comp_list_initialize(u32 link_index);
//int mtip_dma_tx_comp_list_finalize(u32 link_index);
int mtip_dma_tx_comp_list_size(u32 link_index);
int mtip_dma_tx_comp_list_push(u32 link_index, void *user_data, ecpri_dma_eth_conn_hdl_t hdl, 
                               struct ecpri_dma_pkt_completion_wrapper **comp_pkts, 
                               u32 num_of_completed);
int mtip_dma_tx_comp_list_pop(u32 link_index, struct mtip_dma_tx_comp_params *tx_comp_params);

void mtip_dma_ready_cb(void *user_data);
void mtip_dma_rx_comp_cb(void *user_data, ecpri_dma_eth_conn_hdl_t hdl);
void mtip_dma_tx_comp_cb(void *user_data, ecpri_dma_eth_conn_hdl_t hdl, struct ecpri_dma_pkt_completion_wrapper **comp_pkts, u32 num_of_completed);
void mtip_dma_tx_irq_comp_cb(void *user_data, ecpri_dma_eth_conn_hdl_t hdl);

int mtip_connect_dma_pipe(u32 link_index, ecpri_dma_eth_conn_hdl_t* hdl);
int mtip_disconnect_dma_pipe(ecpri_dma_eth_conn_hdl_t hdl);

int mtip_start_dma_pipe(struct net_device *netdev, ecpri_dma_eth_conn_hdl_t hdl);
int mtip_stop_dma_pipe(ecpri_dma_eth_conn_hdl_t hdl);

int mtip_replenish_dma_rx_buffers(struct net_device *netdev, ecpri_dma_eth_conn_hdl_t hdl, u32 num_of_buffs);
int mtip_replenish_dma_rx_buffers_reuse(struct net_device *netdev, ecpri_dma_eth_conn_hdl_t hdl, u32 num_of_buffs);
int mtip_dma_send_packet(struct net_device *netdev, ecpri_dma_eth_conn_hdl_t hdl, struct sk_buff *skb, bool send_tx_pre_header, bool send_tx_seq_num, u8 ts_seq_num);
void mtip_dma_tx_commit(ecpri_dma_eth_conn_hdl_t hdl);

bool mtip_dma_tx_available(ecpri_dma_eth_conn_hdl_t hdl);

int mtip_dma_rx_available(ecpri_dma_eth_conn_hdl_t hdl, u32* available);
int mtip_dma_poll_rx_packets(struct net_device *netdev, struct napi_struct *napi_ptr, ecpri_dma_eth_conn_hdl_t hdl, int budget, int* npackets, int *num_buffers);
int mtip_dma_poll_tx_comp_packets(struct net_device *netdev, struct napi_struct *napi_ptr, ecpri_dma_eth_conn_hdl_t hdl, int budget, int* npackets, int *num_buffers);

int mtip_dma_get_ring_state(ecpri_dma_eth_conn_hdl_t hdl, u32* tx_available, u32* rx_available);

struct mtip_dma_alloc_struct
{
    struct kmem_cache* cachep;
};

enum mtip_dma_alloc_list_enum
{
    MTIP_DMA_ALLOC_LIST_PKT_COMPLETION_WRAPPER,
    MTIP_DMA_ALLOC_LIST_PKT_PTR,
    MTIP_DMA_ALLOC_LIST_PKT,
    MTIP_DMA_ALLOC_LIST_MEM_BUFFER_SINGLE_PTR,
    MTIP_DMA_ALLOC_LIST_MEM_BUFFER_DUAL_PTR,
    MTIP_DMA_ALLOC_LIST_MEM_BUFFER,
    MTIP_DMA_ALLOC_LIST_TX_HEADER,
    MTIP_DMA_ALLOC_LIST_MAX
};

int mtip_dma_alloc_initialize(u32 index);
int mtip_dma_alloc_finalize(u32 index);

struct ecpri_dma_pkt_completion_wrapper* mtip_dma_alloc_completion_wrapper(gfp_t flags);
void mtip_dma_free_completion_wrapper(struct ecpri_dma_pkt_completion_wrapper* ptr);

struct ecpri_dma_pkt** mtip_dma_alloc_dma_pkt_ptr(gfp_t flags);
void mtip_dma_free_dma_pkt_ptr(struct ecpri_dma_pkt** ptr);

struct ecpri_dma_pkt* mtip_dma_alloc_dma_pkt(gfp_t flags);
void mtip_dma_free_dma_pkt(struct ecpri_dma_pkt* ptr);

struct ecpri_dma_mem_buffer** mtip_dma_alloc_mem_buffer_single_ptr(gfp_t flags);
void mtip_dma_free_mem_buffer_single_ptr(struct ecpri_dma_mem_buffer** ptr);

struct ecpri_dma_mem_buffer** mtip_dma_alloc_mem_buffer_dual_ptr(gfp_t flags);
void mtip_dma_free_mem_buffer_dual_ptr(struct ecpri_dma_mem_buffer** ptr);

struct ecpri_dma_mem_buffer* mtip_dma_alloc_mem_buffer(gfp_t flags);
void mtip_dma_free_mem_buffer(struct ecpri_dma_mem_buffer* ptr);

struct ecpri_dma_tx_header* mtip_dma_alloc_tx_header(gfp_t flags);
void mtip_dma_free_tx_header(struct ecpri_dma_tx_header* ptr);

void mtip_dma_free_pkt(struct ecpri_dma_pkt* pkt);
#endif // _MTIP_DMA_H
