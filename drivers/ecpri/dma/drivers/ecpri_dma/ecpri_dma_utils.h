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

#define ECPRI_DMA_GET_CTX_HW_VER() (ecpri_dma_ctx->ecpri_hw_ver)
#define ECPRI_DMA_GET_SW_VER() (ecpri_dma_ctx->driver_ver)
#define ECPRI_DMA_GET_HW_FLAVOR() (ecpri_dma_ctx->hw_flavor)

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
int ecpri_dma_get_gsi_dev_hdl(unsigned long* dev_hdl);
struct device* ecpri_dma_get_pdev(void);
void ecpri_dma_lte_set_loopback(int val);

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

/*------------------------------------------*/
/*            === MEMRING API ===           */
/*------------------------------------------*/

/**
 * ECPRI_DMA_MEMRING_CREATE() - Define a new cyclic buffer memory,
 * @name: unique name for the ring
 * @type: ring item type, can be any leagal c type
 * @ring_size: the size of the ring, must be an integer literal
 */
#define ECPRI_DMA_MEMRING_CREATE(name, type, ring_size)                        \
	u32 name##_wp;                                                             \
	u32 name##_rp;                                                             \
	u32 name##_size;                                                           \
	type name##_memory[ring_size];

 /**
  * ECPRI_DMA_MEMRING_CREATE() - Initiazlie the new cyclic buffer memory,
  * Should be called before first usage
  * @name: name of the ring
  * @ring_size: ring size
  */
#define ECPRI_DMA_MEMRING_INIT(name, ring_size)                                \
	name##_wp = 0;                                                             \
	name##_rp = 0;                                                             \
	name##_size = ring_size;                                                   \
	memset(name##_memory, 0, sizeof(name##_memory))

/**
 * ECPRI_DMA_MEMRING_ALLOC_ITEM() - get an item handler from the ring
 * @name: ring's name
 */
#define ECPRI_DMA_MEMRING_ALLOC_ITEM(name)                                     \
	if (ECPRI_DMA_MEMRING_IS_FULL(name)) {                                     \
		DMAERR("failed to alloc memring items in %s\n", __stringify(name));    \
		ecpri_dma_assert();                                                    \
	}                                                                          \
	name##_wp = (name##_wp + 1) % name##_size

 /**
 * ECPRI_DMA_MEMRING_ACCESS_INDEX() - access ring item for read/write
 * @name: name of ring
 * @item_handle:	memring handle previously recieved via 
 *					ECPRI_DMA_MEMRING_GET_ITEM
 */
#define ECPRI_DMA_MEMRING_ACCESS_INDEX(name, index) name##_memory[index]

/**
 * ECPRI_DMA_MEMRING_ACCESS_WP() - access Newest taken ring item for read/write
 * @name: ring's name
 * 
 * WP points to the next free index
 * This macro will access the last added item - (WP - 1) % size
 */
#define ECPRI_DMA_MEMRING_ACCESS_WP(name)                                      \
	ECPRI_DMA_MEMRING_ACCESS_INDEX(name, (name##_wp + name##_size - 1) % name##_size)

/**
 * ECPRI_DMA_MEMRING_ACCESS_RP() - access Oldest taken ring item for read/write
 * @name: ring's name
 */
#define ECPRI_DMA_MEMRING_ACCESS_RP(name) name##_memory[name##_rp]

/**
 * ECPRI_DMA_MEMRING_IS_EMPTY() - check if no item has been allocated from
 * the ring
 * @name: ring's name
 */
#define ECPRI_DMA_MEMRING_IS_EMPTY(name)                                       \
	(name##_wp == name##_rp)

/**
 * ECPRI_DMA_MEMRING_IS_FULL() - check if the memrting is full
 * the ring
 * @name: ring's name
 */
#define ECPRI_DMA_MEMRING_IS_FULL(name)                                        \
	(((name##_wp + 1) % (name##_size)) == name##_rp)

/**
 * ECPRI_DMA_MEMRING_INC_RP() - Frees the oldeset assigned handle
 * @name: ring's name
 */
#define ECPRI_DMA_MEMRING_INC_RP(name)                                         \
	if (!ECPRI_DMA_MEMRING_IS_EMPTY(name)) {                                   \
		name##_rp = (name##_rp + 1) % name##_size;                             \
	}

/**
 * _ECPRI_DMA_MEMRING_GET_VAR() - Debug macro, get the value of an internal
 * variable
 * @name: ring's name
 * @var: one of _wp, _rp, _size
 */
#define _ECPRI_DMA_MEMRING_GET_VAR(name, var) name##var

/*------------------------------------------*/
/*          === MEMRING API End ===         */
/*------------------------------------------*/

#endif /* _ECPRI_DMA_UTILS_H_ */
