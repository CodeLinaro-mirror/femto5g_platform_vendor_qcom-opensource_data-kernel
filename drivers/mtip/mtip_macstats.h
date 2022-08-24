//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#ifndef _MTIP_MACSTATS_H
#define _MTIP_MACSTATS_H

#include <linux/slab.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/phylink.h>

#include "mtip.h"
#include "mtip_device.h"

/*
 * The offsets below apply to FH0, FH1 and FH2 and their links
 */
#define MTIP_MACSTATS_DATA_HI_OFFSET                                  0x00000000

#define MTIP_MACSTATS_ETHERSTATSOCTETS_REG_OFFET                      0x00000100
#define MTIP_MACSTATS_OCTETSRECEIVEDOK_REG_OFFET                      0x00000104
#define MTIP_MACSTATS_VLANRECEIVEDOK_REG_OFFSET                       0x00000120
#define MTIP_MACSTATS_INERRORS_REG_OFFET                              0x00000124
#define MTIP_MACSTATS_INUCASTPKTS_REG_OFFET                           0x00000128
#define MTIP_MACSTATS_INMCASTPKTS_REG_OFFET                           0x0000012C
#define MTIP_MACSTATS_INBCASTPKTS_REG_OFFET                           0x00000130
#define MTIP_MACSTATS_ETHERSTATSDROPS_REG_OFFET                       0x00000134
#define MTIP_MACSTATS_ETHERSTATSPKTS_REG_OFFET                        0x00000138

#define MTIP_MACSTATS_OCTETSTRANSMITTEDOK_REG_OFFET                   0x00000334
#define MTIP_MACSTATS_VLANTRANSMITTEDOK_OFFET                         0x00000340
#define MTIP_MACSTATS_OUTERRORS_REG_OFFET                             0x00000344
#define MTIP_MACSTATS_OUTUCASTPKTS_REG_OFFET                          0x00000348
#define MTIP_MACSTATS_OUTMCASTPKTS_REG_OFFET                          0x0000034C
#define MTIP_MACSTATS_OUTBCASTPKTS_REG_OFFET                          0x00000350

#define MTIP_MACSTATS_RX_BLOCKSIZE                                    0x0000008C
#define MTIP_MACSTATS_TX_BLOCKSIZE                                    0x00000068

void mtip_macstats_get_stats(struct net_device *netdev, u64 *data);

#endif // _MTIP_MACSTATS_H
