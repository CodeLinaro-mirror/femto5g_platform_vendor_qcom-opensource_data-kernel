//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#ifndef _MTIP_DEVICE_H
#define _MTIP_DEVICE_H

#include <linux/slab.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/phylink.h>

#include "ecpri_dma_eth.h"

// the net device structure
struct mtip_netdev_priv {
   u32 link_index;
   spinlock_t lock;
   void __iomem           *mac_ioaddr;
   u64 hashtablebits;
   struct phy_device      *phydev;
   struct phylink         *phylink;
   struct phylink_config   phylink_config;
};

/*
 * posted task structures
 */
struct mtip_replenish_dma_rx_buffers_task
{
   struct net_device * netdev;
   ecpri_dma_eth_conn_hdl_t  hdl;
   u32                 num_of_pkts;
};
void run_mtip_replenish_dma_rx_buffers(void* work_ptr);

struct mtip_set_rx_mode_task
{
   ecpri_dma_eth_conn_hdl_t  hdl;
   enum ecpri_dma_notify_mode setmode;
};
void post_mtip_set_rx_mode(ecpri_dma_eth_conn_hdl_t hdl, enum ecpri_dma_notify_mode setmode);
void run_mtip_set_rx_mode(void* work_ptr);

struct mtip_tx_comp_cb_task
{
    void *user_data;
    ecpri_dma_eth_conn_hdl_t hdl;
    struct ecpri_dma_pkt_completion_wrapper **comp_pkts;
    u32 num_of_completed;
};
void post_mtip_tx_comp_cb(void *user_data, ecpri_dma_eth_conn_hdl_t hdl, struct ecpri_dma_pkt_completion_wrapper **comp_pkts, u32 num_of_completed);
void run_mtip_tx_comp_cb(void* work_ptr);

struct mtip_process_link_state_task
{
    u32 link_index;
    bool link_up;
};

void post_mtip_process_link_state(u32 link_index, bool link_up);
void run_mtip_process_link_state(void* work_ptr);

/*
 * Functions exposed by mtip_device
 */
int mtip_napi_poll(struct napi_struct *napi_ptr, int budget);
void mtip_netdevice_init(struct net_device *dev);

enum mtip_link_state_enum mtip_get_link_state_by_device(u32 port_device_index, u32 link_device_index);

#endif // _MTIP_DEVICE_H
