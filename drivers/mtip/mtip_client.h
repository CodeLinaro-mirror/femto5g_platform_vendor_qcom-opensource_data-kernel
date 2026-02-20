//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#ifndef _MTIP_CLIENT_H
#define _MTIP_CLIENT_H

#include <linux/slab.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/phylink.h>

#include "eth_ecpriss_iface.h"

/*
 * Ethernet client related data
 */
#define MTIP_MAX_CLIENTS    2

// client related information
struct mtip_client_struct
{
   eth_ecpriss_topology_ready_cb ready_cb;
   eth_ecpriss_interface_events_cb events_cb;
};

/* 
  Posted task structures 
 */ 
struct mtip_send_ready_task
{

};

struct mtip_send_event_task
{
    eth_ecpriss_event_e event;
    u32 link_index;
};

void post_mtip_client_send_ready(void);
void run_mtip_client_send_ready(void* work_ptr);
void mtip_client_send_event(eth_ecpriss_event_e event, u32 link_index);

int mtip_setup_topology(void);
void mtip_free_topology(void);
eth_ecpriss_status_e mtip_eth_get_topology(eth_ecpriss_dev_mode_e *device_mode, eth_ecpriss_topology_root_s *topology_params);
eth_ecpriss_status_e mtip_eth_register_events_cb(eth_ecpriss_interface_events_cb events_cb);
eth_ecpriss_status_e mtip_eth_deregister_events_cb(void);
eth_ecpriss_status_e mtip_eth_register_ready_cb(eth_ecpriss_topology_ready_cb ready_cb, bool *is_ready);
void mtip_print_topology(eth_ecpriss_topology_root_s *topology);
void mtip_eth_reeval_logging_port(void);

#endif // _MTIP_CLIENT_H
