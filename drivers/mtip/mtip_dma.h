//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#ifndef _MTIP_DMA_H
#define _MTIP_DMA_H

#include <linux/slab.h>
#include <linux/list.h>
#include <linux/mutex.h>

#include "ecpri_dma_eth.h"

// this is the extern to connect to dma driver
extern struct ecpri_dma_eth_ops ecpri_dma_eth_driver_ops;

void mtip_dma_ready_cb(void *user_data);
void mtip_dma_rx_comp_cb(void *user_data, ecpri_dma_eth_conn_hdl_t hdl);
void mtip_dma_tx_comp_cb(void *user_data, ecpri_dma_eth_conn_hdl_t hdl, struct ecpri_dma_pkt_completion_wrapper **comp_pkts, u32 num_of_completed);

int mtip_connect_dma_pipe(u32 link_index, ecpri_dma_eth_conn_hdl_t* hdl);
int mtip_disconnect_dma_pipe(ecpri_dma_eth_conn_hdl_t hdl);

int mtip_start_dma_pipe(struct net_device *netdev, ecpri_dma_eth_conn_hdl_t hdl);
int mtip_stop_dma_pipe(ecpri_dma_eth_conn_hdl_t hdl);

int mtip_replenish_dma_rx_buffers(struct net_device *netdev, ecpri_dma_eth_conn_hdl_t hdl, u32 num_of_pkts);
int mtip_dma_send_packet(struct net_device *netdev, ecpri_dma_eth_conn_hdl_t hdl, struct sk_buff *skb);
void mtip_dma_tx_commit(ecpri_dma_eth_conn_hdl_t hdl);

bool mtip_dma_tx_available(ecpri_dma_eth_conn_hdl_t hdl);

int mtip_dma_rx_available(ecpri_dma_eth_conn_hdl_t hdl, u32* available);
int mtip_dma_poll_rx_packets(struct net_device *netdev, struct napi_struct *napi_ptr, ecpri_dma_eth_conn_hdl_t hdl, int budget, int* npackets);

int mtip_dma_get_ring_state(ecpri_dma_eth_conn_hdl_t hdl, u32* tx_available, u32* rx_available);

#endif // _MTIP_DMA_H
