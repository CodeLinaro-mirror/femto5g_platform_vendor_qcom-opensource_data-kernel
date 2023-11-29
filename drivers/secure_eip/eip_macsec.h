//SPDX-License-Identifier: GPL-2.0-only

/*
* Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
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
#include "eip_device.h"

/* 4 FH's. Each FH has maximum 4 Ports and each port has
    Ingress Channel and Egress Channel
    so, its 4*4*2 = 32 channels */
#define MACSEC_MAX_LINK_IDS 32
#define MACSEC_MAX_SA MACSEC_NUM_AN

extern const struct macsec_ops eip_macsec_ops;

void eip_macsec_initalize_priv_data(uint32_t device_id);

int eip_device_deinit(bool fIngress, unsigned int device_id);

void eip_macsec_init_link(struct eip_link *link);
void eip_macsec_deinit_link(struct eip_link *link);

#endif /* MACSEC_DEVICE_H_ */
