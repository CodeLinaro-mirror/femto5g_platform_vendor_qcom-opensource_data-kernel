//SPDX-License-Identifier: GPL-2.0-only

/*
* Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
*/

#ifndef MACSEC_DEVICE_H_
#define MACSEC_DEVICE_H_

#include <linux/netdevice.h>
#include <net/macsec.h>
#include "api_secy.h"
#include "api_cfye.h"

#include "basic_defs.h"
#include "clib.h"
#include "log.h"
#include "sa_builder_macsec.h"

 /******************************************************
    ETH interfaces and MACSEC interfaces are linked as below.
    Each FH has 4 ETH interfaces like eth00, eth01, eth02, eth03.
    We need to compute device ID from the link index, so, the device ID
    is basically Ingress 0 and Egress 1 for FH0 eth links
    Ingress 2 and Egress 3 for FH1 eth links and so on.
    
 ******************************************************/ 
#define EIP_MAX_PORT 4
#define GET_INGRESS_ID_FROM_PORT_ID(port_id) port_id * 2;
#define GET_EGRESS_ID_FROM_PORT_ID(port_id ) port_id * 2 + 1;
#define   GET_PORT_ID_FROM_LINK_IDX(link_index)   link_index/4
#define   GET_INGRESS_ID_FROM_DEVICE_ID(device_id)  device_id*2
#define   GET_EGRESS_ID_FROM_DEVICE_ID( device_id)  device_id*2+1
#define   GET_CHANNEL_ID_FROM_LINK_IDX(link_index)   link_index%4
#define   GET_PORT_ID_FROM_DEVICE_ID(device_id)   device_id/2;

 /* 4 FH's. Each FH has maximum 4 Ports and each port has 
    Ingress Channel and Egress Channel
    so, its 4*4*2 = 32 channels */
#define MACSEC_MAX_LINK_IDS 32
#define MACSEC_MAX_SA  MACSEC_NUM_AN

extern const struct macsec_ops eip_macsec_ops;

void eip_macsec_initalize_priv_data(uint32_t device_id);

int eip_device_deinit(bool fVerbose, bool fIngress,
			      unsigned int device_id);

#endif				/* MACSEC_DEVICE_H_ */
