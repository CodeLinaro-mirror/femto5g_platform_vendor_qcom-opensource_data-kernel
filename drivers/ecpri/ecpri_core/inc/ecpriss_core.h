/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef ECPRISS_CORE_H_
#define ECPRISS_CORE_H_

#include <linux/module.h>
#include <linux/kernel.h>
//#include <linux/delay.h>
#include <net/netlink.h>
#include <net/net_namespace.h>
#include <linux/signal.h>           /* Definition of SIGEV_* constants */
#include <linux/jiffies.h>
#include <linux/uaccess.h>
#include <linux/workqueue.h>
#include <linux/netdevice.h>
#include <linux/of_device.h>
#include <linux/debugfs.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/atomic.h>
#include <linux/fs.h>
#include <linux/interrupt.h>

#include "ecpri_dma_ecpri_ss.h"
#include "eth_ecpriss_iface.h"
#include "ecpriss_xbar.h"
#include "ecpriss_qudp.h"
#include "ecpriss_flow.h"

#define ECPRI_DMA_RING_PER_PORT_MAX 4

#define ENABLE_ECPRI_TEST    1

typedef enum
{
	ECPRI_CORE_PRE_INIT,
	ECPRI_CORE_COLD_INIT,
	ECPRI_CORE_INIT,
	ECPRI_CORE_DEINIT
} ecpriss_core_state_e;

/**
 * enum dev mode
 */
typedef enum {
	ECPRISS_DEV_MODE_DU = 0,
	ECPRISS_DEV_MODE_RU,
	ECPRISS_DEV_MODE_MAX
}ecpriss_dev_mode_e;

typedef struct ecpriss_core_callback_flags
{
	uint32_t eth_link_callback_rcvd;
	uint32_t dma_callback_rcvd;
	uint32_t ssr_callback_rcvd;
	uint32_t macsec_callback_rcvd;
}ecpriss_core_callback_flags_s;


/**
 * enum ecpriss_port_dir
 */
typedef enum {
	ECPRISS_PORT_DIR_RX = 0,
	ECPRISS_PORT_DIR_TX,
	ECPRISS_PORT_DIR_MAX
}ecpriss_port_dir_e;



/**
 * enum ecpriss_eth_link_rate - link rate(Gbps)
 */
typedef enum {
	ECPRISS_ETH_LINK_RATE_1000 = 0,
	ECPRISS_ETH_LINK_RATE_100,
	ECPRISS_ETH_LINK_RATE_25,
	ECPRISS_ETH_LINK_RATE_10,
	ECPRISS_ETH_LINK_RATE_MAX,
}ecpriss_eth_link_rate_e;

/**
 * enum ecpriss_eth_port_type - port type
 */
typedef enum {
	ECPRISS_PORT_TYPE_FH = 0,
	ECPRISS_PORT_TYPE_C2C,
	ECPRISS_PORT_TYPE_L2,
	ECPRISS_PORT_TYPE_OC,
	ECPRISS_PORT_TYPE_MAX
}ecpriss_port_type_e;



/**
 * enum eth_ecpriss_event_e - event type
 */
typedef enum {
	ECPRISS_ETH_EVENT_CREATE = 0,
	ECPRISS_ETH_EVENT_UP,
	ECPRISS_ETH_EVENT_DOWN,
	ECPRISS_ETH_EVENT_DESTROY,
	ECPRISS_ETH_EVENT_MAX
}ecpriss_eth_event_e;



typedef struct ecpri_kernel_events_workqueue_params
{
	struct work_struct          *ecpriss_eth_events_rdy_work;
	struct work_struct          *ecpriss_dma_events_rdy_work;
	struct work_struct          *ecpriss_eth_topology_events_rdy_work;
	struct workqueue_struct     *kernel_events_workqueue;
}ecpri_events_workqueue_params_s;


typedef struct ecpri_interrupt_events_workqueue_params
{
	struct work_struct          *ecpriss_interrupt_events_rdy_work;
	struct workqueue_struct     *ecpriss_interrupts_workq;
}ecpri_interrupt_workqueue_params_s;



/**
 * struct ecpri_dma_endp_cfg - DMA endpoint configurations
 * @ecpri_state:
 * @callback_flag:
 * @user_pid:
 * @netlink_socket:
 * @dma_endp:
 * @eth_link_params:
 * @flow_id_tbl:
 * @stats:
 * @ecpriss_core_logbuf:
 */
typedef struct ecpriss_core_private_s {
	ecpriss_core_state_e                  ecpri_state;
	ecpriss_core_callback_flags_s        *callback_flag;
	uint32_t                              user_pid;
	struct sock                          *netlink_socket;
	struct ecpri_dma_endp_mapping        *dma_endp;
	eth_ecpriss_topology_root_s          *eth_topology_params;
	void                                 *ecpriss_core_logbuf;
	ecpri_events_workqueue_params_s      *events_workqueue;
	ecpri_interrupt_workqueue_params_s   *interrupts_workqueue;
	eth_ecpriss_topology_ready_cb        *ready_cb;
	ecpriss_dev_mode_e                    dev_mode;
	ecpriss_qudp_ctx_s                   *qudp_ctx;
	ecpriss_xbar_ctx_s                   *xbar_ctx;
	struct mutex                          ecpriss_mutex_lock;
} ecpriss_core_private_s;

extern ecpriss_core_private_s *ecpriss_pdata;
extern ecpriss_xbar_ctx_s     xbar_ctx_g;
extern ecpriss_qudp_ctx_s     qudp_ctx_g;
static spinlock_t irq_lock;


void ecpriss_eth_event_processing_wq(struct work_struct *work);
void ecpriss_dma_event_processing_wq(struct work_struct *work);
void ecpriss_eth_topology_init_wq(struct work_struct *work);

#endif
