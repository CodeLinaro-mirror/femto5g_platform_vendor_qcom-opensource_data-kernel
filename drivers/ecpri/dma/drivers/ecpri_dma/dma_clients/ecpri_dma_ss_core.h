/*
 * SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2025 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _ECPRI_DMA_SS_CORE_H_
#define _ECPRI_DMA_SS_CORE_H_

#include "ecpri_dma_i.h"
#include "ecpri_dma_utils.h"
#include "ecpri_dma_ecpri_ss.h"
#include <linux/mutex.h>
#include <linux/workqueue.h>
#include <linux/cdev.h>
#include <linux/types.h>
#include <linux/fs.h>

enum ecpri_dma_ss_oran_log_dev {
    ECPRI_DMA_SS_ORAN_LOG_EGRESS_DEV_ID, //0
    ECPRI_DMA_SS_ORAN_LOG_INGRESS_DEV_ID, //1
    ECPRI_DMA_SS_ORAN_LOG_NUM_DEVICES, //2
};

#define ECPRI_DMA_SS_ORAN_LOG_X100_GSI_ID           (1)
#define ECPRI_DMA_SS_ORAN_LOG_X100_EGRESS_ENDP_ID   (69)
#define ECPRI_DMA_SS_ORAN_LOG_X100_INGRESS_ENDP_ID  (70)
#define ECPRI_DMA_SS_ORAN_LOG_QRU_GSI_ID            (0)
#define ECPRI_DMA_SS_ORAN_LOG_QRU_EGRESS_ENDP_ID    (54)
#define ECPRI_DMA_SS_ORAN_LOG_QRU_INGRESS_ENDP_ID   (55)
#define ECPRI_DMA_SS_ORAN_LOG_PCAP_HDR_MAGIC        (0xa1b2c3d4)
#define ECPRI_DMA_SS_ORAN_LOG_PCAP_HDR_VER          (0x00040002)
#define ECPRI_DMA_SS_ORAN_LOG_PCAP_HDR_TMZ          (0)
#define ECPRI_DMA_SS_ORAN_LOG_PCAP_HDR_TMZ_ACR      (0)
#define ECPRI_DMA_SS_ORAN_LOG_PCAP_HDR_SNP_LEN      (0x00040000)
#define ECPRI_DMA_SS_ORAN_LOG_PCAP_HDR_LNK_TYPE     (0x00000001)

struct pkt_eth_hdr
{
    uint8_t src[6], dst[6];
    uint16_t type;
};

struct __packed ecpri_hdr
{
    uint8_t c : 1;
    uint8_t resv : 3;
    uint8_t ecpri_protocol : 4;
    uint8_t mesg_type;
    uint16_t payld_size;
} __packed;

struct ecpri_dma_ss_core_pcap_header {
    u32 magic;
    u32 version;
    u32 timezone;
    u32 timezone_accuracy;
    u32 snap_len;
    u32 link_type;
};

struct ecpri_dma_ss_core_pcap_pkt_header {
    u32 timestamp_sec;
    u32 timestamp_msec;
    u32 captured_len;
    u32 orig_len;
};

/**
 * struct ecpri_dma_eth_client_context - DMA ETH client context
 *
 * @lock:                       general lock to protect sensetive resources
 * @wq:                         workqueue struct
 * @ecpri_hw_ver:               type of eCPRI HW type (e.g. eCPRI 1.0 etc')
 * @hw_flavor:                  current HW flavor (Ru \ Du - L2 \ Du - PCIe)
 * @ready_cb:                   ecpri_ss_core client ready callback notifier
 * @ready_user_data:            userdata for ecpri_ss_core ready cb
 * @event_notify_cb:            ecpri_ss_core client to notify eCPRI SS driver
 *                              of DMA events
 * @event_notify_user_data:     userdata for ecpri_ss_core event notify CB
 * @log_msg_cb:                 ecpri_ss_core client to log a message
 *                              with eCPRI SS driver logging API
 * @log_msg_user_data:          userdata for ecpri_ss_core logging API
 * @oran_log_cdev:              char device to be used for reading ORAN
 *                              log PCAP output
 *
 */
struct ecpri_dma_ss_core_context {
    spinlock_t lock;
    struct workqueue_struct* wq;
    enum ecpri_hw_ver ecpri_hw_ver;
    enum ecpri_hw_flavor hw_flavor;
    ecpri_dma_ready_cb ready_cb;
    void* ready_user_data;
    ecpri_dma_ecpri_ss_dma_event_notify_cb event_notify_cb;
    void* event_notify_user_data;
    ecpri_dma_ecpri_ss_log_msg_cb log_msg_cb;
    void* log_msg_user_data;
    struct cdev oran_log_cdev[ECPRI_DMA_SS_ORAN_LOG_NUM_DEVICES];
    bool oran_log_cdev_read_state[ECPRI_DMA_SS_ORAN_LOG_NUM_DEVICES];
    bool oran_log_cdev_read_in_progress[ECPRI_DMA_SS_ORAN_LOG_NUM_DEVICES];
    u32 oran_log_pkt_idx[ECPRI_DMA_SS_ORAN_LOG_NUM_DEVICES];
    struct ecpri_dma_mem_buffer oran_log_mem[ECPRI_DMA_SS_ORAN_LOG_NUM_DEVICES];
    struct ecpri_dma_pkt* pkts[ECPRI_DMA_SS_ORAN_LOG_NUM_DEVICES];
    struct ecpri_dma_pkt **pkts_arr[ECPRI_DMA_SS_ORAN_LOG_NUM_DEVICES];
    struct ecpri_dma_mem_buffer* buffs[ECPRI_DMA_SS_ORAN_LOG_NUM_DEVICES];
    struct ecpri_dma_mem_buffer** buffs_arr[ECPRI_DMA_SS_ORAN_LOG_NUM_DEVICES];
    u32 pkt_size[ECPRI_DMA_SS_ORAN_LOG_NUM_DEVICES];
    u32 num_of_pkts[ECPRI_DMA_SS_ORAN_LOG_NUM_DEVICES];
};

#endif /* _ECPRI_DMA_SS_CORE_H_ */
