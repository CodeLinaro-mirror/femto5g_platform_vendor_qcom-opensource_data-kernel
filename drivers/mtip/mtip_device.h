//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#ifndef _MTIP_DEVICE_H
#define _MTIP_DEVICE_H

#include <linux/slab.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/phylink.h>

#include "mtip.h"
#include "mtip_security.h"

#include "ecpri_dma_eth.h"

// the net device structure
struct mtip_netdev_priv {
   u32 link_index;
   spinlock_t lock;
   void __iomem           *mac_ioaddr;
   u64 hashtablebits;
   u32 priv_flags;

   struct mtip_security_device *sec_dev;
   void *sec_priv;

   // these are used only for RUMI E2E
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
   u32                 num_of_buffs;
};
void run_mtip_replenish_dma_rx_buffers(void* work_ptr);

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
 * Immediate tasks
 */
void mtip_set_rx_mode_immediate(ecpri_dma_eth_conn_hdl_t hdl, enum ecpri_dma_notify_mode setmode);

/*
 * Functions exposed by mtip_device
 */
int mtip_napi_poll(struct napi_struct *napi_ptr, int budget);
void mtip_netdevice_init(struct net_device *dev);

enum mtip_link_state_enum mtip_get_link_state_by_device(u32 port_device_index, u32 link_device_index);

int mtip_set_netdev_hw_mac_addr(struct net_device *netdev, u32 link_index);

int mtip_netdev_set_port_config(struct net_device *netdev);
int mtip_device_update_security_config(struct net_device *netdev, enum mtip_port_config_enum port_config);

// get the next ptp ts seq num to use
u8 mtip_netdev_get_next_ptp_ts_seq_num(u32 link_index);

#endif // _MTIP_DEVICE_H
