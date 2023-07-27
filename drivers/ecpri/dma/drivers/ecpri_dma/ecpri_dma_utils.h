/*
 * SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _ECPRI_DMA_UTILS_H_
#define _ECPRI_DMA_UTILS_H_

#include "ecpri_dma_ecpri_ss.h"
#include "ecpri_dma_i.h"

#define ECPRI_DMA_DEFAULT_PORT_ID 0
#define ECPRI_DMA_L2_PORT_ID 2
#define ECPRI_DMA_TLV_TRSHLD 7

#define ECPRI_DMA_GSI_CHANNEL_STOP_MAX_RETRY 10
#define ECPRI_DMA_GSI_CHANNEL_STOP_SLEEP_MIN_USEC (3000)
#define ECPRI_DMA_GSI_CHANNEL_STOP_SLEEP_MAX_USEC (5000)

/**
 * Endpoint map's filter structure.
 * Contins pairs of filter field and its enable value.
 * @valid: is endp valid
 * @valid_enable: enable switch
 * @ee: endp's execution environment
 * @ee_eanble: enable switch
 * @dir: endp's direction
 * @dir_enable: enable switch
 * @stream_mode: endp's stream mode
 * @stream_mode_enable:enable switch
 * @gsi_id: endp's gsi id
 * @gsi_id_enable:enable switch
 * @dest: endp's dest
 * @dest_enable:enable switch
 */
struct ecpri_dma_endp_filter {
	bool valid;
	bool valid_enable;

	enum ecpri_dma_ees ee;
	bool ee_enable;

	enum ecpri_dma_endp_dir dir;
	bool dir_enable;

	enum ecpri_dma_endp_stream_mode stream_mode;
	bool stream_mode_enable;

	u32 gsi_id;
	bool gsi_id_enable;

	u32 dest;
	bool dest_enable;
};

 /** Functions **/

//TODO: Complete documentation of functions below
int ecpri_dma_get_endp_mapping(enum ecpri_hw_ver ver, enum ecpri_hw_flavor flv,
    const struct dma_gsi_ep_config (**endp_map)
    [ECPRI_DMA_GSI_NUM_MAX][ECPRI_DMA_ENDP_NUM_MAX]);
int ecpri_dma_get_port_mapping(enum ecpri_hw_ver ver, enum ecpri_hw_flavor flv,
    struct ecpri_dma_endp_mapping *endp_map);
int ecpri_dma_set_tx_pre_header(struct ecpri_dma_endp_context *ep);
int ecpri_dma_enable_dma_endp(struct ecpri_dma_endp_context *ep);
int ecpri_dma_disable_dma_endp(struct ecpri_dma_endp_context *ep);
int ecpri_dma_setup_dma_endps(
    const struct dma_gsi_ep_config (*endp_map)
    [ECPRI_DMA_GSI_NUM_MAX][ECPRI_DMA_ENDP_NUM_MAX]);
int ecpri_dma_enable_dma_endps(
    const struct dma_gsi_ep_config (*endp_map)
    [ECPRI_DMA_GSI_NUM_MAX][ECPRI_DMA_ENDP_NUM_MAX]);
irq_handler_t ecpri_dma_get_isr(void);
const char *ecpri_dma_get_version_string(enum ecpri_hw_ver ver);
bool ecpri_dma_is_ready(void);
int ecpri_dma_gsi_setup_event_ring(struct ecpri_dma_endp_context *ep,
    u32 ring_length, gfp_t mem_flag);
int ecpri_dma_gsi_setup_transfer_ring(struct ecpri_dma_endp_context *ep,
    u32 ring_length, gfp_t mem_flag);
int ecpri_dma_gsi_setup_channel(struct ecpri_dma_endp_context *ep);
int ecpri_dma_gsi_release_channel(struct ecpri_dma_endp_context *ep);
int ecpri_dma_gsi_start_channel(struct ecpri_dma_endp_context *ep);
int ecpri_dma_gsi_stop_channel(struct ecpri_dma_endp_context *ep);
int ecpri_dma_gsi_reset_channel(struct ecpri_dma_endp_context *ep);
int ecpri_dma_hw_init(void);

u32 ecpri_dma_get_ctx_hw_ver(void);
u32 ecpri_dma_get_ctx_hw_flavor(void);
int ecpri_dma_get_gsi_dev_hdl(unsigned long* dev_hdl);
struct device* ecpri_dma_get_pdev(void);

/**
 * ecpri_dma_filter_endps() - filter endpoint map endpoits by filter criteria
 * @filter: the applied filter
 * @endpoint_list: the returned list of endpoints
 * @max_size: max size of endpoints
 *
 * Return:  number of found endpoints, or negative value for Linux error
 */
int ecpri_dma_filter_endps(
	struct ecpri_dma_endp_filter *filter,
	struct ecpri_dma_endp_gsi_tuple  *endpoint_list,
	size_t max_size);

#endif /* _ECPRI_DMA_UTILS_H_ */
