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

/*----------------------Default FH supported speed mask-----------------------*/
// For 100G lane speed all speed modes are allowed
#define MTIP_DEVICE_PRIV_FLAGS_BIT_MASK_100G               0xFFFFFFFF
#define MTIP_DEVICE_PRIV_FLAGS_BIT_MASK_NON_FEC            0x2928A2A9

/*------------------Default Debug ETH supported speed mask--------------------*/
// For Debug port, port configurations with max 1 link and 2 lanes are valid
#define MTIP_DEVICE_PRIV_FLAGS_BIT_MASK_DBG_PORT           0x6707E01F
// Mask for all lane speeds supported by Debug ETH except FEC modes
#define MTIP_DEVICE_PRIV_FLAGS_BIT_MASK_DBG_PORT_NON_FEC   0x2100A009
// Mask for all lane speeds supported by Debug ETH except FEC modes and 50G lane speeds.
#define MTIP_DEVICE_PRIV_FLAGS_BIT_MASK_DBG_PORT_NON_FEC_NON_50G   0x21000000

/*-----------------------Ethtool speed setting mask --------------------------*/
// 100G link speed configuration mask
#define MTIP_DEVICE_PRIV_FLAGS_BIT_MASK_100G_ONLY          0x0000007F

// 50G link speed configuration mask
#define MTIP_DEVICE_PRIV_FLAGS_BIT_MASK_50G_ONLY           0x0007FF80

// 40G link speed configuration mask
#define MTIP_DEVICE_PRIV_FLAGS_BIT_MASK_40G_ONLY           0x00180000

// 25G link speed configuration mask
#define MTIP_DEVICE_PRIV_FLAGS_BIT_MASK_25G_ONLY           0x07E00000

// 10G link speed configuration mask
#define MTIP_DEVICE_PRIV_FLAGS_BIT_MASK_10G_ONLY           0x78000000

// 100G link speed configuration mask
#define MTIP_DEVICE_PRIV_FLAGS_BIT_MASK_100G_ONLY_DBG_PORT 0x0000001F

// 50G link speed configuration mask
#define MTIP_DEVICE_PRIV_FLAGS_BIT_MASK_50G_ONLY_DBG_PORT  0x0007E000

// 25G link speed configuration mask
#define MTIP_DEVICE_PRIV_FLAGS_BIT_MASK_25G_ONLY_DBG_PORT  0x07000000

// 10G link speed configuration mask
#define MTIP_DEVICE_PRIV_FLAGS_BIT_MASK_10G_ONLY_DBG_PORT  0x60000000

// the net device structure
struct mtip_netdev_priv {
   u32 link_index;
   spinlock_t lock;
   void __iomem           *mac_ioaddr;
   u64 hashtablebits;
   u32 priv_flags;
   int num_pkts_pending_completion;
   bool priv_flags_set;

   struct mtip_security_device *sec_dev;
   void *sec_priv;

   // these are used only for RUMI E2E
   struct phy_device      *phydev;
   struct phylink         *phylink;
   struct phylink_config   phylink_config;
   struct ecpri_dma_pkt_completion_wrapper **tx_comp_pkts;
   struct ecpri_dma_pkt_completion_wrapper **rx_comp_pkts;
   struct ecpri_dma_pkt **head;
   uint16_t rx_curr_index;
   uint16_t rx_polled_count;
   struct ecpri_dma_pkt *tx_pkts[MTIP_TX_RING_SIZE];
   uint16_t tx_curr_index;
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

struct mtip_tx_comp_cb_task
{
    void *user_data;
    ecpri_dma_eth_conn_hdl_t hdl;
    struct ecpri_dma_pkt_completion_wrapper **comp_pkts;
    u32 num_of_completed;
};

struct mtip_process_link_state_task
{
    u32 link_index;
    bool link_up;
};

void post_mtip_process_link_state(u32 link_index, bool link_up);
void run_mtip_process_link_state(void* work_ptr);
void mtip_process_link_state(u32 link_index, bool link_up);
void mtip_device_configure_port(u32 port_type);
void post_mtip_process_configure_port_using_lane(u32 port_type, u32 lane_index);
void run_mtip_process_configure_port_using_lane(void* workptr);

struct mtip_process_configure_port_using_lane_task
{
    u32 port_type;
    u32 lane_index;
};

void post_mtip_process_configure_port_using_link(u32 port_type, u32 link_index);
void run_mtip_process_configure_port_using_link(void* workptr);

struct mtip_process_configure_port_using_link_task
{
    u32 port_type;
    u32 link_index;
};

void post_mtip_process_an_result(enum mtip_port_type_enum port_type, bool an_result, enum mtip_port_config_enum port_config, u8 seq_num);
void run_mtip_process_an_result(void* workptr);

struct mtip_process_an_result_task
{
    u32 port_type;
    bool an_result;
    enum mtip_port_config_enum port_config;
    u8 seq_num;
};

void post_mtip_process_netdev_open(struct net_device *netdev);
void run_mtip_process_netdev_open(void* workptr);
void post_mtip_process_netdev_close(struct net_device *netdev);
void run_mtip_process_netdev_close(void* workptr);

struct mtip_process_process_netdev_events
{
    struct net_device *netdev;
};

void post_mtip_process_reconfigure_port(u32 port_type);
void run_mtip_process_reconfigure_port(void* workptr);

struct mtip_process_reconfigure_port
{
    u32 port_type;
};


/*
 * Immediate tasks
 */
void mtip_set_rx_mode_immediate(ecpri_dma_eth_conn_hdl_t hdl, enum ecpri_dma_notify_mode setmode);
void mtip_set_tx_mode_immediate(ecpri_dma_eth_conn_hdl_t hdl, enum ecpri_dma_notify_mode setmode);

/*
 * Functions exposed by mtip_device
 */
int mtip_napi_poll(struct napi_struct *napi_ptr, int budget);
int mtip_napi_poll_tx(struct napi_struct *napi_ptr, int budget);
void mtip_netdevice_init(struct net_device *dev);

enum mtip_link_state_enum mtip_get_link_state_by_link_index(u32 link_index);

/* completion of device open if it is deferred */
int mtip_device_open_completion(u32 link_index);

int mtip_set_netdev_hw_mac_addr(struct net_device *netdev, u32 link_index);
int mtip_netdev_setup_port_hw(u32 port_type);

int mtip_netdev_set_port_priv_flags(struct net_device *netdev);
int mtip_netdev_set_port_config(u32 port_type);
int mtip_device_update_security_config(struct net_device *netdev, enum mtip_port_config_enum port_config);

// get the next ptp ts seq num to use
u8 mtip_netdev_get_next_ptp_ts_seq_num(u32 link_index);

u32 mtip_device_filter_priv_flags(u32 port_type);
int mtip_device_lookup_lane_qsfp_cfg(u32 port_type, struct qsfp_info *lane_qsfp_info);

void mtip_process_tx_comp_cb(ecpri_dma_eth_conn_hdl_t hdl, struct mtip_dma_tx_comp_params *tx_comp_params);
#endif // _MTIP_DEVICE_H
