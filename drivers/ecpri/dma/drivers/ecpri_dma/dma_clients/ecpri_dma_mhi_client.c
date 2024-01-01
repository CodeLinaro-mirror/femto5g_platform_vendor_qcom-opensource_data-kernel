/*
 * SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include "ecpri_dma_mhi_client.h"
#include "gsihal.h"

#define ECPRI_DMA_MHI_CLIENT_MEMCPY_ASYNC_BUDGET (15)

struct ecpri_dma_mhi_client_context*
	ecpri_dma_mhi_client_ctx[ECPRI_DMA_MHI_CLIENT_FUNCTION_NUM] = { NULL };

struct ecpri_dma_mhi_memcpy_context*
	ecpri_dma_mhi_memcpy_ctx[ECPRI_DMA_MHI_CLIENT_FUNCTION_NUM] = { NULL };
#define ECPRI_DMA_MHI_CLIENT_WQ_NAME_LEN (20)

static const char* wq_name[ECPRI_DMA_MHI_CLIENT_FUNCTION_NUM]
[ECPRI_DMA_MHI_CLIENT_WQ_NAME_LEN] =
{
	{
		"ecpri_dma_mhi_wq_vm_0",
		"ecpri_dma_mhi_wq_vm_1",
		"ecpri_dma_mhi_wq_vm_2",
		"ecpri_dma_mhi_wq_vm_3",
		"ecpri_dma_mhi_wq_vf_1",
		"ecpri_dma_mhi_wq_vf_2",
		"ecpri_dma_mhi_wq_vf_3",
		"ecpri_dma_mhi_wq_vf_4",
		"ecpri_dma_mhi_wq_vf_5",
		"ecpri_dma_mhi_wq_vf_a",
		"ecpri_dma_mhi_wq_vf_b",
		"ecpri_dma_mhi_wq_vf_c",
		"ecpri_dma_mhi_wq_vf_d",
		"ecpri_dma_mhi_wq_vf_e",
		"ecpri_dma_mhi_wq_pf"
	}
};

static const struct ecpri_dma_mhi_ee_gsi_tuple
ecpri_dma_mhi_function_map[ECPRI_DMA_VM_IDS_MAX] = {
	[ECPRI_DMA_VM_IDS_VM0] = {ECPRI_DMA_EE_VM0, ECPRI_DMA_GSI_ID_0},
	[ECPRI_DMA_VM_IDS_VM1] = {ECPRI_DMA_EE_VM1, ECPRI_DMA_GSI_ID_0},
	[ECPRI_DMA_VM_IDS_VM2] = {ECPRI_DMA_EE_VM2, ECPRI_DMA_GSI_ID_0},
	[ECPRI_DMA_VM_IDS_VM3] = {ECPRI_DMA_EE_VM3, ECPRI_DMA_GSI_ID_0},
	[ECPRI_DMA_VM_IDS_VFA] = {ECPRI_DMA_EE_VFA, ECPRI_DMA_GSI_ID_1},
	[ECPRI_DMA_VM_IDS_VFB] = {ECPRI_DMA_EE_VFB, ECPRI_DMA_GSI_ID_1},
	[ECPRI_DMA_VM_IDS_VFC] = {ECPRI_DMA_EE_VFC, ECPRI_DMA_GSI_ID_1},
	[ECPRI_DMA_VM_IDS_VF1] = {ECPRI_DMA_EE_VF1, ECPRI_DMA_GSI_ID_1},
	[ECPRI_DMA_VM_IDS_VF2] = {ECPRI_DMA_EE_VF2, ECPRI_DMA_GSI_ID_1},
	[ECPRI_DMA_VM_IDS_VFD] = {ECPRI_DMA_EE_VFD, ECPRI_DMA_GSI_ID_2},
	[ECPRI_DMA_VM_IDS_VFE] = {ECPRI_DMA_EE_VFE, ECPRI_DMA_GSI_ID_2},
	[ECPRI_DMA_VM_IDS_VF3] = {ECPRI_DMA_EE_VF3, ECPRI_DMA_GSI_ID_2},
	[ECPRI_DMA_VM_IDS_VF4] = {ECPRI_DMA_EE_VF4, ECPRI_DMA_GSI_ID_2},
	[ECPRI_DMA_VM_IDS_VF5] = {ECPRI_DMA_EE_VF5, ECPRI_DMA_GSI_ID_2},
};

static const struct ecpri_dma_mhi_ee_gsi_tuple
	ecpri_dma_mhi_physical_function_tuple =
		{ ECPRI_DMA_EE_PF, ECPRI_DMA_GSI_ID_0 };

static const struct ecpri_dma_mhi_function_endp_data
ecpri_dma_mhi_function_endp_dt[ECPRI_HW_MAX][ECPRI_DMA_MHI_CLIENT_FUNCTION_NUM] =
{
	[ECPRI_HW_V1_0][ECPRI_DMA_VM_IDS_VM0] = {
		.sync_src_id   = 22,
		.sync_dest_id  = 59,
		.async_src_id  = ECPRI_DMA_MHI_INVALID_ENDP_ID,
		.async_dest_id = ECPRI_DMA_MHI_INVALID_ENDP_ID
	},
	[ECPRI_HW_V1_0][ECPRI_DMA_VM_IDS_VM1] = {
		.sync_src_id   = 25,
		.sync_dest_id  = 62,
		.async_src_id  = ECPRI_DMA_MHI_INVALID_ENDP_ID,
		.async_dest_id = ECPRI_DMA_MHI_INVALID_ENDP_ID
	},
	[ECPRI_HW_V1_0][ECPRI_DMA_VM_IDS_VM2] = {
		.sync_src_id   = 28,
		.sync_dest_id  = 65,
		.async_src_id  = ECPRI_DMA_MHI_INVALID_ENDP_ID,
		.async_dest_id = ECPRI_DMA_MHI_INVALID_ENDP_ID
	},
	[ECPRI_HW_V1_0][ECPRI_DMA_VM_IDS_VM3] = {
		.sync_src_id   = 31,
		.sync_dest_id  = 68,
		.async_src_id  = ECPRI_DMA_MHI_INVALID_ENDP_ID,
		.async_dest_id = ECPRI_DMA_MHI_INVALID_ENDP_ID
	},
	[ECPRI_HW_V1_0][ECPRI_DMA_VM_IDS_VF1 ... ECPRI_DMA_VM_IDS_VFE] = {
		.sync_src_id   = ECPRI_DMA_MHI_INVALID_ENDP_ID,
		.sync_dest_id  = ECPRI_DMA_MHI_INVALID_ENDP_ID,
		.async_src_id  = ECPRI_DMA_MHI_INVALID_ENDP_ID,
		.async_dest_id = ECPRI_DMA_MHI_INVALID_ENDP_ID
	},
	[ECPRI_HW_V1_0][ECPRI_DMA_MHI_PF_ID] = {
		.sync_src_id   = 32,
		.sync_dest_id  = 69,
		.async_src_id  = 33,
		.async_dest_id = 70
	},
	[ECPRI_HW_V2_0][ECPRI_DMA_VM_IDS_VM0 ... ECPRI_DMA_VM_IDS_VFE] = {
		.sync_src_id   = ECPRI_DMA_MHI_INVALID_ENDP_ID,
		.sync_dest_id  = ECPRI_DMA_MHI_INVALID_ENDP_ID,
		.async_src_id  = ECPRI_DMA_MHI_INVALID_ENDP_ID,
		.async_dest_id = ECPRI_DMA_MHI_INVALID_ENDP_ID
	},
	[ECPRI_HW_V2_0][ECPRI_DMA_MHI_PF_ID] = {
		.sync_src_id   = 19,
		.sync_dest_id  = 56,
		.async_src_id  = 20,
		.async_dest_id = 57
	}
};

static int ecpri_dma_mhi_pkt_alloc_from_heap(
	struct mhi_dma_function_params **function_ptr,
	struct ecpri_dma_pkt **pkt_ptr)
{
	*function_ptr =
		(struct mhi_dma_function_params*)kzalloc(
		sizeof(struct mhi_dma_function_params),
		GFP_KERNEL);

	if (!function_ptr) {
		DMAERR("failed to alloc packets array \n");
		return -ENOMEM;
	}

	*pkt_ptr = kzalloc(sizeof(struct ecpri_dma_pkt), GFP_KERNEL);
	if (!*pkt_ptr) {
		DMAERR("failed to alloc packets array \n");
		kfree(function_ptr);
		return -ENOMEM;
	}

	(*pkt_ptr)->buffs =
		kzalloc(sizeof(*((*pkt_ptr)->buffs)), GFP_KERNEL);
	if (!((*pkt_ptr)->buffs)) {
		DMAERR("failed to alloc buffers array \n");
		kfree(*pkt_ptr);
		kfree(*function_ptr);
		return -ENOMEM;
	}

	(*pkt_ptr)->buffs[0] = kzalloc(
		sizeof(*((*pkt_ptr)->buffs[0])), GFP_KERNEL);
	if (!(*pkt_ptr)->buffs[0]) {
		DMAERR("failed to alloc dma buff wrapper\n");
		kfree((*pkt_ptr)->buffs);
		kfree(*pkt_ptr);
		kfree(*function_ptr);
		return -ENOMEM;
	}

	return 0;
}
/**
 * ecpri_dma_mhi_pkt_alloc_from_ring() -
 * get  memory needed for packet from a preallocated memory ring
 *
 * @function_ptr: pointer to the virtual function
 * @dir: in/out packets
 * @memcpy_ctx: memcpy memory context
 * @pkt_ptr: pointer to allocated packet wrapper
 *
 * Returns: 0 on success, Negative on failure
 */
static int ecpri_dma_mhi_pkt_alloc_from_ring(
	struct mhi_dma_function_params **function_ptr,
	struct ecpri_dma_pkt** pkt_ptr,
	enum ecpri_dma_endp_dir dir,
	struct ecpri_dma_mhi_memcpy_context* memcpy_ctx)
{
	/* Allocate items */
	if (ECPRI_DMA_ENDP_DIR_SRC == dir) {
		ECPRI_DMA_MEMRING_ALLOC_ITEM(memcpy_ctx->src_func_ring);
		ECPRI_DMA_MEMRING_ALLOC_ITEM(memcpy_ctx->src_pkt_ring);
		ECPRI_DMA_MEMRING_ALLOC_ITEM(memcpy_ctx->src_bufs_ptr_ring);
		ECPRI_DMA_MEMRING_ALLOC_ITEM(memcpy_ctx->src_bufs_ring);

		/* Get pointers */
		*function_ptr =
			&ECPRI_DMA_MEMRING_ACCESS_WP(memcpy_ctx->src_func_ring);
		*pkt_ptr =
			&ECPRI_DMA_MEMRING_ACCESS_WP(memcpy_ctx->src_pkt_ring);
		(*pkt_ptr)->buffs =
			&ECPRI_DMA_MEMRING_ACCESS_WP(memcpy_ctx->src_bufs_ptr_ring);
		(*pkt_ptr)->buffs[0] =
			&ECPRI_DMA_MEMRING_ACCESS_WP(memcpy_ctx->src_bufs_ring);

	} else {
		ECPRI_DMA_MEMRING_ALLOC_ITEM(memcpy_ctx->dst_func_ring);
		ECPRI_DMA_MEMRING_ALLOC_ITEM(memcpy_ctx->dst_pkt_ring);
		ECPRI_DMA_MEMRING_ALLOC_ITEM(memcpy_ctx->dst_bufs_ptr_ring);
		ECPRI_DMA_MEMRING_ALLOC_ITEM(memcpy_ctx->dst_bufs_ring);

		/* Get pointers */
		*function_ptr =
		 	&ECPRI_DMA_MEMRING_ACCESS_WP(memcpy_ctx->dst_func_ring);
		*pkt_ptr =
		 	&ECPRI_DMA_MEMRING_ACCESS_WP(memcpy_ctx->dst_pkt_ring);
		(*pkt_ptr)->buffs =
		 	&ECPRI_DMA_MEMRING_ACCESS_WP(memcpy_ctx->dst_bufs_ptr_ring);
		(*pkt_ptr)->buffs[0] =
			 &ECPRI_DMA_MEMRING_ACCESS_WP(memcpy_ctx->dst_bufs_ring);
	}

	return 0;
}

/**
 * ecpri_dma_mhi_free_pkt_from_heap() - Frees
 * the allocated memory for packet's
 *
 * @pkt:       [IN] Allocated packets data
 *
 */
static void ecpri_dma_mhi_free_pkt_from_heap(
	struct ecpri_dma_pkt** pkt)
{
	kfree((*pkt)->user_data);
	kfree((*pkt)->buffs[0]);
	kfree((*pkt)->buffs);
	kfree(*pkt);
	*pkt = NULL;
}

static void ecpri_dma_mhi_free_pkt_from_ring(
	enum ecpri_dma_endp_dir  pkt_dir,
	struct ecpri_dma_mhi_memcpy_context* memcpy_ctx)
{
	if (ECPRI_DMA_ENDP_DIR_SRC == pkt_dir) {
		ECPRI_DMA_MEMRING_INC_RP(memcpy_ctx->src_func_ring);
		ECPRI_DMA_MEMRING_INC_RP(memcpy_ctx->src_pkt_ring);
		ECPRI_DMA_MEMRING_INC_RP(memcpy_ctx->src_bufs_ptr_ring);
		ECPRI_DMA_MEMRING_INC_RP(memcpy_ctx->src_bufs_ring);
	} else {
		ECPRI_DMA_MEMRING_INC_RP(memcpy_ctx->dst_func_ring);
		ECPRI_DMA_MEMRING_INC_RP(memcpy_ctx->dst_pkt_ring);
		ECPRI_DMA_MEMRING_INC_RP(memcpy_ctx->dst_bufs_ptr_ring);
		ECPRI_DMA_MEMRING_INC_RP(memcpy_ctx->dst_bufs_ring);
	}
}

/*
* ecpri_dma_mhi_get_function_mapping() - Maps VF index to corresponding EE and
* GSI ID
*/
static int ecpri_dma_mhi_get_function_mapping(
	struct mhi_dma_function_params function,
	const struct ecpri_dma_mhi_ee_gsi_tuple** tuple)
{
	if (function.function_type == MHI_DMA_FUNCTION_TYPE_VIRTUAL &&
		function.vf_id < ECPRI_DMA_MHI_CLIENT_FUNCTION_NUM - 1) {
		*(tuple) = &ecpri_dma_mhi_function_map[function.vf_id];
	}
	else if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
	{
		*(tuple) = &ecpri_dma_mhi_physical_function_tuple;
	}
	else {
		DMAERR("Unexpected function type, type: %d, vf_id: %d\n",
			function.function_type, function.vf_id);
		return -EINVAL;
	}

	return 0;
}

static inline void ecpri_dma_mhi_get_sync_async_endp_ids(
	int* sync_src_endp_id, int* sync_dest_endp_id,
	int* async_src_endp_id, int* async_dest_endp_id, int idx)
{
	int hw_ver = ECPRI_DMA_GET_CTX_HW_VER();
	if (hw_ver == ECPRI_HW_V1_0) {
		*(sync_src_endp_id) =
			ecpri_dma_mhi_function_endp_dt[hw_ver][idx].sync_src_id;
		*(sync_dest_endp_id) =
			ecpri_dma_mhi_function_endp_dt[hw_ver][idx].sync_dest_id;
		*(async_src_endp_id) =
			ecpri_dma_mhi_function_endp_dt[hw_ver][idx].async_src_id;
		*(async_dest_endp_id) =
			ecpri_dma_mhi_function_endp_dt[hw_ver][idx].async_dest_id;
	}
	else {
		*(sync_src_endp_id) =
			ecpri_dma_mhi_function_endp_dt[hw_ver][ECPRI_DMA_MHI_PF_ID]
			.sync_src_id;
		*(sync_dest_endp_id) =
			ecpri_dma_mhi_function_endp_dt[hw_ver][ECPRI_DMA_MHI_PF_ID]
			.sync_dest_id;
		*(async_src_endp_id) =
			ecpri_dma_mhi_function_endp_dt[hw_ver][ECPRI_DMA_MHI_PF_ID]
			.async_src_id;
		*(async_dest_endp_id) =
			ecpri_dma_mhi_function_endp_dt[hw_ver][ECPRI_DMA_MHI_PF_ID]
			.async_dest_id;
	}
}

static inline bool ecpri_dma_mhi_check_destroy_pending(
	struct ecpri_dma_mhi_memcpy_context* memcpy_ctx)
{
	bool destroy_pending = false;
	unsigned long flags;
	unsigned long flags_sync;
	unsigned long flags_async;

	spin_lock_irqsave(&memcpy_ctx->lock, flags);
	spin_lock_irqsave(&memcpy_ctx->async_lock, flags_async);
	spin_lock_irqsave(&memcpy_ctx->sync_lock, flags_sync);

	destroy_pending = memcpy_ctx->destroy_pending;

	spin_unlock_irqrestore(&memcpy_ctx->sync_lock,
		flags_sync);
	spin_unlock_irqrestore(&memcpy_ctx->async_lock,
		flags_async);
	spin_unlock_irqrestore(&memcpy_ctx->lock,
		flags);

	return destroy_pending;
}

static inline int ecpri_dma_mhi_get_function_context_index(
	struct mhi_dma_function_params function, int* idx,
	enum ecpri_dma_mhi_dma_context_type ctx_type)
{
	int ret = 0;
	enum ecpri_hw_ver hw_ver = ECPRI_DMA_GET_CTX_HW_VER();

	switch (ctx_type)
	{
	case ECPRI_DMA_MHI_DMA_CLIENT_CTX:
		if (function.function_type ==
			MHI_DMA_FUNCTION_TYPE_VIRTUAL &&
			function.vf_id < ECPRI_DMA_MHI_CLIENT_FUNCTION_NUM - 1) {
			*(idx) = function.vf_id;
		}
		else if (function.function_type ==
			MHI_DMA_FUNCTION_TYPE_PHYSICAL) {
			*(idx) = ECPRI_DMA_MHI_PF_ID;
		}
		break;
	case ECPRI_DMA_MHI_DMA_MEMCPY_CTX:
		/* V1 Code */
		if (hw_ver == ECPRI_HW_V1_0) {
			if (function.function_type ==
				MHI_DMA_FUNCTION_TYPE_VIRTUAL &&
				function.vf_id < ECPRI_DMA_MHI_CLIENT_FUNCTION_NUM - 1) {
				*(idx) = function.vf_id;
			}
			else if (function.function_type ==
				MHI_DMA_FUNCTION_TYPE_PHYSICAL) {
				*(idx) = (ECPRI_DMA_MHI_CLIENT_FUNCTION_NUM - 1);
			}
			else {
				DMAERR("Unexpected function type, type: %d, vf_id: %d\n",
					function.function_type, function.vf_id);
				ret = -EINVAL;
			}
		}
		/* V2 Code */
		else {
			*(idx) = ECPRI_DMA_MHI_PF_ID;
		}
		break;
	default:
		DMAERR("Unexpected client type, type: %d, vf_id: %d\n", ctx_type);
		ret = -EINVAL;
	}

	return ret;
}

static inline void ecpri_dma_mhi_set_endps(int idx,
	struct ecpri_dma_mhi_memcpy_context* memcpy_ctx)
{
	int sync_src_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int sync_dest_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int async_src_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int async_dest_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	enum ecpri_dma_gsi_id gsi_id = ECPRI_DMA_GSI_ID_0;

	ecpri_dma_mhi_get_sync_async_endp_ids(&sync_src_endp_id,
		&sync_dest_endp_id, &async_src_endp_id, &async_dest_endp_id, idx);

	memcpy_ctx->sync_dest_endp =
		&ecpri_dma_ctx->endp_ctx[gsi_id][sync_dest_endp_id];
	memcpy_ctx->sync_src_endp =
		&ecpri_dma_ctx->endp_ctx[gsi_id][sync_src_endp_id];

	if (async_src_endp_id != ECPRI_DMA_MHI_INVALID_ENDP_ID &&
		async_dest_endp_id != ECPRI_DMA_MHI_INVALID_ENDP_ID)
	{
		memcpy_ctx->async_dest_endp =
			&ecpri_dma_ctx->endp_ctx[gsi_id][async_dest_endp_id];
		memcpy_ctx->async_src_endp =
			&ecpri_dma_ctx->endp_ctx[gsi_id][async_src_endp_id];
	}
}

/**
 * ecpri_dma_mhi_get_endp_ctx() - Gets the endpoint
 * GSI configuration data, by EE ID and CH ID
 *
 * @ee_idx:      [IN] EE ID
 * @channel_id:  [IN] CH ID
 * @endp_cfg:    [OUT] GSI endp configuration data
 *
 */
static int ecpri_dma_mhi_get_endp_ctx(
	struct mhi_dma_function_params function, u8 channel_id,
	struct ecpri_dma_endp_context** endp_ctx)
{
	int ret = -EINVAL;
	int endp_id, gsi_id;

	enum ecpri_dma_ees ee_idx;
	const struct ecpri_dma_mhi_ee_gsi_tuple* func_map;

	ret = ecpri_dma_mhi_get_function_mapping(function, &func_map);
	if (ret)
	{
		DMAERR("Unknown function");
		return ret;
	}
	ee_idx = func_map->ee_id;
	gsi_id = func_map->gsi_id;

	if (gsi_id == ECPRI_DMA_GSI_NUM_MAX) {
		DMAERR("Invalid GSI ID");
		return -EINVAL;
	}

	for (endp_id = 0; endp_id < ECPRI_DMA_ENDP_NUM_MAX; endp_id++)
	{
		if ((*ecpri_dma_ctx->endp_map)[gsi_id][endp_id].valid &&
			(*ecpri_dma_ctx->endp_map)[gsi_id][endp_id].dma_gsi_chan_num ==
			channel_id &&
			(*ecpri_dma_ctx->endp_map)[gsi_id][endp_id].ee == ee_idx) {
			*(endp_ctx) = &ecpri_dma_ctx->endp_ctx[gsi_id][endp_id];
			ecpri_dma_ctx->endp_ctx[gsi_id][endp_id].gsi_id = gsi_id;
			ecpri_dma_ctx->endp_ctx[gsi_id][endp_id].endp_id = endp_id;
			ret = 0;
			break;
		}
	}

	return ret;
}

static void ecpri_dma_mhi_get_l2_ch_bitmap(
	struct mhi_dma_function_params function, u32 idx, u32 *bitmap)
{
	int endp_id;
	enum ecpri_dma_gsi_id gsi_id;
	enum ecpri_dma_ees ee_idx;
	const struct ecpri_dma_mhi_ee_gsi_tuple* func_map;
	enum ecpri_hw_ver hw_ver = ECPRI_DMA_GET_CTX_HW_VER();

	if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
		DMADBG_LOW("Physical \n");
	else
		DMADBG_LOW("Virtual ID %d \n", function.vf_id);

	*bitmap = 0;

	if (ecpri_dma_mhi_get_function_mapping(function, &func_map))
	{
		DMAERR("Unknown function");
	}

	if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
	{
		return;
	}

	ee_idx = func_map->ee_id;
	gsi_id = func_map->gsi_id;

	for (endp_id = 0; endp_id < ECPRI_DMA_ENDP_NUM_MAX; endp_id++)
	{
		/* Note: For V2 there is no SW Chanels in VM */
		if ((*ecpri_dma_ctx->endp_map)[gsi_id][endp_id].valid &&
			(*ecpri_dma_ctx->endp_map)[gsi_id][endp_id].ee == ee_idx &&
			endp_id != ecpri_dma_mhi_function_endp_dt[hw_ver][idx].sync_src_id &&
			endp_id != ecpri_dma_mhi_function_endp_dt[hw_ver][idx].sync_dest_id &&
			endp_id != ecpri_dma_mhi_function_endp_dt[hw_ver][idx].async_src_id &&
			endp_id != ecpri_dma_mhi_function_endp_dt[hw_ver][idx].async_dest_id){
			*bitmap |= 1 << (*ecpri_dma_ctx->endp_map)[gsi_id][endp_id]
				.dma_gsi_chan_num;
		}
	}
}

/**
 * ecpri_dma_mhi_alloc_pkt() - Allocates
 * memory for MHI SW CH packet wrapper
 * @params: packet allocation params
 * @pkt_ptr: [OUT] pointer to a packet
 * Return codes: 0: success
 *		-EINVAL: Illegal buffer address
 */
static int ecpri_dma_mhi_alloc_pkt(
	struct ecpri_dma_mhi_alloc_pkt_params* params,
	struct ecpri_dma_pkt** pkt_ptr)
{
	int ret = 0;
	struct ecpri_dma_pkt* pkt = NULL;
	struct mhi_dma_function_params* function_ptr = NULL;

	/* Choose which allocation type to use */
	if (ECPRI_DMA_MHI_ASYNC_PACKET == params->pkt_type)
		ret = ecpri_dma_mhi_pkt_alloc_from_ring(
			&function_ptr, &pkt, params->dir, params->memcpy_ctx);
	else
		ret = ecpri_dma_mhi_pkt_alloc_from_heap(
			&function_ptr, &pkt);

	pkt->buffs[0]->phys_base = (dma_addr_t)(params->buff_addr);
	pkt->buffs[0]->size = params->len;
	pkt->num_of_buffers = 1;
	pkt->user_data = function_ptr;

	function_ptr->function_type = params->function->function_type;
	function_ptr->vf_id = params->function->vf_id;

	*pkt_ptr = pkt;

	return ret;
}

/**
 * ecpri_dma_mhi_wq_notify_ready() - Notify MHI client on ready
 *
 * This function is called from DMA MHI workqueue to notify
 * MHI client driver on ready event
 *
 */
static void ecpri_dma_mhi_wq_notify_ready(struct work_struct* work)
{
	struct ecpri_dma_mhi_wq_work_type* ecpri_dma_mhi_work =
		container_of(work,
			struct ecpri_dma_mhi_wq_work_type,
			work);
	ecpri_dma_mhi_work->ctx->notify_cb(
		ecpri_dma_mhi_work->ctx->user_data,
		MHI_DMA_EVENT_READY,
		0);

	kfree(ecpri_dma_mhi_work);
}

/**
 * ecpri_dma_mhi_memcpy_async_wq_cb_ready() - Notify MHI client on async comp
 *
 * This function is called to notify ASYNC transfer completion.
 *
 */
static void ecpri_dma_mhi_memcpy_async_wq_cb_ready(struct work_struct* work)
{
	struct ecpri_dma_mhi_memcpy_context *memcpy_ctx = NULL;
	unsigned long flags;
	struct ecpri_dma_mhi_xfer_wrapper xfer_desc;

	struct ecpri_dma_mhi_async_wq_work_type *async_work = container_of(
		work, struct ecpri_dma_mhi_async_wq_work_type, work);

	DMADBG_LOW("Begin\n");

	memcpy_ctx = ecpri_dma_mhi_memcpy_ctx[ECPRI_DMA_MHI_PF_ID];
	if (!memcpy_ctx) {
		DMAERR("Memcpy context is not initialized\n");
		return;
	}

	if (ecpri_dma_mhi_check_destroy_pending(memcpy_ctx) == true) {
		DMAERR("Memcpy destroy in progress\n");
		return;
	}

	/* Enter lock section */
	spin_lock_irqsave(&memcpy_ctx->async_lock, flags);

	/* Verify there are transfer pending */
	if (ECPRI_DMA_MEMRING_IS_EMPTY(memcpy_ctx->xfer_descr_ring)) {
		DMAERR("Expected pending xfers, but none found.\n");
		spin_unlock_irqrestore(&memcpy_ctx->async_lock, flags);
		return;
	}

	async_work->xfer_desc =
		&ECPRI_DMA_MEMRING_ACCESS_RP(memcpy_ctx->xfer_descr_ring);

	xfer_desc.user_cb = async_work->xfer_desc->user_cb;
	xfer_desc.user_data = async_work->xfer_desc->user_data;

	/* Update xfer counters */
	atomic_dec(&memcpy_ctx->async_pending);
	atomic_inc(&memcpy_ctx->async_total);

	/* Remove oldest added xfer */
	ECPRI_DMA_MEMRING_INC_RP(memcpy_ctx->xfer_descr_ring);

	/* Free work item */
	ECPRI_DMA_MEMRING_INC_RP(memcpy_ctx->async_work_ring);

	/* Exit locked section */
	spin_unlock_irqrestore(&memcpy_ctx->async_lock, flags);

	/* Run user cllaback*/
	xfer_desc.user_cb(xfer_desc.user_data);
}

/**
 * ecpri_dma_mhi_memcpy_async_wq_cb_ready_vms() - Notify MHI client on async comp
 *
 * This function is called to notify ASYNC transfer completion.
 *
 */
static void ecpri_dma_mhi_memcpy_async_wq_cb_ready_vms(struct work_struct* work)
{
	int idx = 0, ret = 0;
	struct ecpri_dma_mhi_memcpy_context* memcpy_ctx = NULL;
	struct ecpri_dma_mhi_async_wq_work_type* async_work = container_of(
		work, struct ecpri_dma_mhi_async_wq_work_type, work);

	DMADBG_LOW("Begin\n");

	/* Get the index of VM/PF */
	ret = ecpri_dma_mhi_get_function_context_index(
		async_work->xfer_desc->function, &idx, ECPRI_DMA_MHI_DMA_MEMCPY_CTX);
	if (ret != 0) {
		DMAERR("Function params are invalid,"
			"function type: %d, vf_id: %d\n",
			async_work->xfer_desc->function.function_type,
			async_work->xfer_desc->function.vf_id);
		return;
	}

	memcpy_ctx = ecpri_dma_mhi_memcpy_ctx[idx];
	if (!memcpy_ctx) {
		DMAERR("Memcpy context is not initialized\n");
		return;
	}

	if (ecpri_dma_mhi_check_destroy_pending(memcpy_ctx) == true) {
		DMAERR("Memcpy destroy in progress\n");
		return;
	}

	async_work->xfer_desc->user_cb(async_work->xfer_desc->user_data);

	/* Remove oldest added xfer */
	ECPRI_DMA_MEMRING_INC_RP(memcpy_ctx->xfer_descr_ring);

	/* Free work item */
	ECPRI_DMA_MEMRING_INC_RP(memcpy_ctx->async_work_ring);
}

/**
 * ecpri_dma_mhi_memcpy_async_notify_comp() - Notifies on sending completion
 *
 * @endp: endpoint context
 * @comp_pkt: the packets data
 * @num_of_completed: Number of completed packets
 *
 * This function notifies MHI driver on async completion
 * using supplied callback function
 *
 */
static void ecpri_dma_mhi_memcpy_async_notify_comp(
	struct ecpri_dma_endp_context* endp,
	struct ecpri_dma_pkt_completion_wrapper** comp_pkt,
	u32 num_of_completed)
{
	int i = 0;
	int ret = 0;
	struct ecpri_dma_mhi_memcpy_context* memcpy_ctx = NULL;
	struct ecpri_dma_pkt_completion_wrapper
		async_pkts_arr[ECPRI_DMA_MHI_CLIENT_MEMCPY_ASYNC_BUDGET];
	struct ecpri_dma_pkt_completion_wrapper*
		async_pkts[ECPRI_DMA_MHI_CLIENT_MEMCPY_ASYNC_BUDGET];
	struct ecpri_dma_mhi_async_wq_work_type *work = NULL;
	u32 actual_num = 0;
	int hw_ver = ECPRI_DMA_GET_CTX_HW_VER();

	if (ECPRI_HW_MAX == hw_ver) {
		DMAERR("Invalid HW version\n");
		return;
	}

	if (!endp) {
		DMAERR("Null params args\n");
		return;
	}

	/* Skip VMs, pass the PF only*/
	if (endp->endp_id !=
		ecpri_dma_mhi_function_endp_dt[hw_ver][ECPRI_DMA_MHI_PF_ID]
		.async_dest_id) {
		DMAERR("Received unexpected async completion on ENDP %d\n",
			endp->endp_id);
		return;
	}

	memcpy_ctx = ecpri_dma_mhi_memcpy_ctx[ECPRI_DMA_MHI_PF_ID];
	if (!memcpy_ctx) {
		DMAERR("Memcpy context is not initialized\n");
		return;
	}

	if (ecpri_dma_mhi_check_destroy_pending(memcpy_ctx) == true) {
		DMAERR("Memcpy destroy in progress\n");
		return;
	}

	for (i = 0; i < ECPRI_DMA_MHI_CLIENT_MEMCPY_ASYNC_BUDGET; i++) {
		async_pkts[i] = &async_pkts_arr[i];
	}

	/* memcpy uses single buffer packet so actual_num == num of buffers
		no need to check for EOT */
	ret = ecpri_dma_dp_poll(endp,
				   ECPRI_DMA_MHI_CLIENT_MEMCPY_ASYNC_BUDGET,
				   async_pkts, &actual_num);
	if (ret) {
		DMAERR("ASYNC endp polling failed\n");
		ecpri_dma_assert();
	}

	if (!actual_num)
	{
		/* No Async PKTs pending */
		ret = ecpri_dma_set_endp_mode(endp, ECPRI_DMA_NOTIFY_MODE_IRQ);
		if (ret) {
			DMAERR("Setting ASYNC endp to IRQ mode failed\n");
			ecpri_dma_assert();
		}
		return;
	}

	for (i = 0; i < actual_num; i++)
	{
		/* Allocate work item */
		ECPRI_DMA_MEMRING_ALLOC_ITEM(memcpy_ctx->async_work_ring);
		work = &ECPRI_DMA_MEMRING_ACCESS_WP(memcpy_ctx->async_work_ring);

		INIT_WORK(&work->work,
			ecpri_dma_mhi_memcpy_async_wq_cb_ready);

		queue_work(memcpy_ctx->async_wq, &work->work);

		/* Free destination packet */
		ecpri_dma_mhi_free_pkt_from_ring(
			ECPRI_DMA_ENDP_DIR_DEST,
			memcpy_ctx);
	}

	/* There might be more packet to poll, rescheduale tasklet */
	tasklet_hi_schedule(&endp->tasklet);
}

/**
 * ecpri_dma_mhi_alloc_sync_async_endps() - Helper function to allocate endps
 */
static int ecpri_dma_mhi_alloc_sync_async_endps(
	struct mhi_dma_function_params function, int idx)
{
	int ret = 0;
	int sync_src_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int sync_dest_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int async_src_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int async_dest_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	enum ecpri_dma_gsi_id gsi_id = ECPRI_DMA_GSI_ID_0;
	const struct ecpri_dma_mhi_ee_gsi_tuple* func_map;
	enum ecpri_hw_ver hw_ver = ECPRI_DMA_GET_CTX_HW_VER();
	struct ecpri_dma_moderation_config sync_mod_cfg, async_mod_cfg;

	sync_mod_cfg.moderation_counter_threshold = 1;
	sync_mod_cfg.moderation_timer_threshold = 0;
	async_mod_cfg.moderation_counter_threshold = 32;
	async_mod_cfg.moderation_timer_threshold = 10;

	ret = ecpri_dma_mhi_get_function_mapping(function, &func_map);
	if (ret)
	{
		DMAERR("Unknown function");
		return ret;
	}
	gsi_id = func_map->gsi_id;

	ecpri_dma_mhi_get_sync_async_endp_ids(&sync_src_endp_id, &sync_dest_endp_id,
		&async_src_endp_id, &async_dest_endp_id, idx);

	ecpri_dma_ctx->
		endp_ctx[gsi_id][sync_src_endp_id].eventless_endp = true;

	ret = ecpri_dma_alloc_endp(gsi_id, sync_src_endp_id,
		ECPRI_DMA_MHI_SYNC_MEMCPY_RLEN, &sync_mod_cfg, false, NULL, false);
	if (ret != 0) {
		DMAERR("Unable to allocate SYNC_SRC ENDP, endp_id: %d\n",
			sync_src_endp_id);
		goto fail_alloc_sync_src;
	}

	ret = ecpri_dma_alloc_endp(gsi_id,
		sync_dest_endp_id, ECPRI_DMA_MHI_SYNC_MEMCPY_RLEN,
		&sync_mod_cfg, false, NULL, false);
	if (ret != 0) {
		DMAERR("Unable to allocate SYNC_DEST ENDP, endp_id: %d\n",
			sync_dest_endp_id);
		goto fail_alloc_sync_dest;
	}

	if (hw_ver > ECPRI_HW_V1_0)
	{
		ecpri_dma_ctx->
			endp_ctx[gsi_id][sync_src_endp_id].dynamic_vf_enabled = true;
		ecpri_dma_ctx->
			endp_ctx[gsi_id][sync_dest_endp_id].dynamic_vf_enabled = true;
	}

	/* Skip the VMs */
	if (async_src_endp_id == ECPRI_DMA_MHI_INVALID_ENDP_ID ||
		async_dest_endp_id == ECPRI_DMA_MHI_INVALID_ENDP_ID)
		return ret;

	ecpri_dma_ctx->
		endp_ctx[gsi_id][async_src_endp_id].eventless_endp = true;
	ret = ecpri_dma_alloc_endp(gsi_id,
		async_src_endp_id, ECPRI_DMA_MHI_ASYNC_MEMCPY_RLEN,
		&async_mod_cfg, false, NULL, false);
	if (ret != 0) {
		DMAERR("Unable to allocate ASYNC_SRC ENDP, endp_id: %d\n",
			async_src_endp_id);
		goto fail_alloc_async_src;
	}

	ret = ecpri_dma_alloc_endp(gsi_id,
		async_dest_endp_id, ECPRI_DMA_MHI_ASYNC_MEMCPY_RLEN,
		&async_mod_cfg, false,
		ecpri_dma_mhi_memcpy_async_notify_comp, false);
	if (ret != 0) {
		DMAERR("Unable to allocate ASYNC_DEST ENDP, endp_id: %d\n",
			async_dest_endp_id);
		goto fail_alloc_async_dest;
	}

	if (hw_ver > ECPRI_HW_V1_0)
	{
		ecpri_dma_ctx->
			endp_ctx[gsi_id][async_src_endp_id].dynamic_vf_enabled = true;
		ecpri_dma_ctx->
			endp_ctx[gsi_id][async_dest_endp_id].dynamic_vf_enabled = true;
	}

	ret = 0;
	goto success;

fail_alloc_async_dest:
	ecpri_dma_dealloc_endp(
		&ecpri_dma_ctx->endp_ctx[gsi_id][async_src_endp_id]);
fail_alloc_async_src:
	ecpri_dma_dealloc_endp(
		&ecpri_dma_ctx->endp_ctx[gsi_id][sync_dest_endp_id]);
fail_alloc_sync_dest:
	ecpri_dma_dealloc_endp(
		&ecpri_dma_ctx->endp_ctx[gsi_id][sync_src_endp_id]);
fail_alloc_sync_src:
success:
	return ret;
}

/**
 * ecpri_dma_mhi_enable_mhi_memcpy_endps() - Helper function
 * to enable endpnts
 *
 */
static int ecpri_dma_mhi_enable_mhi_memcpy_endps(int idx)
{
	int ret = 0;

	int sync_src_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int sync_dest_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int async_src_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int async_dest_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	enum ecpri_dma_gsi_id gsi_id = ECPRI_DMA_GSI_ID_0;

	ecpri_dma_mhi_get_sync_async_endp_ids(&sync_src_endp_id,
		&sync_dest_endp_id, &async_src_endp_id, &async_dest_endp_id, idx);

	ret = ecpri_dma_enable_dma_endp(
		&ecpri_dma_ctx->endp_ctx[gsi_id][sync_src_endp_id]);
	if (ret != 0) {
		DMAERR("Unable to enable SYNC SRC endpoint %d, GSI %d\n",
			sync_src_endp_id, gsi_id);
		ret = -EFAULT;
		goto fail_enable_sync_src;
	}

	ret = ecpri_dma_enable_dma_endp(
		&ecpri_dma_ctx->endp_ctx[gsi_id][sync_dest_endp_id]);
	if (ret != 0) {
		DMAERR("Unable to enable SYNC DEST endpoint %d, GSI %d\n",
			sync_dest_endp_id, gsi_id);
		ret = -EFAULT;
		goto fail_enable_sync_dest;
	}

	/* Skip the VMs */
	if (async_src_endp_id == ECPRI_DMA_MHI_INVALID_ENDP_ID ||
		async_dest_endp_id == ECPRI_DMA_MHI_INVALID_ENDP_ID)
		return ret;

	ret = ecpri_dma_enable_dma_endp(
		&ecpri_dma_ctx->endp_ctx[gsi_id][async_src_endp_id]);
	if (ret != 0) {
		DMAERR("Unable to enable ASYNC SRC endpoint %d, GSI %d\n",
			async_src_endp_id, gsi_id);
		ret = -EFAULT;
		goto fail_enable_async_src;
	}

	ret = ecpri_dma_enable_dma_endp(
		&ecpri_dma_ctx->endp_ctx[gsi_id][async_dest_endp_id]);
	if (ret != 0) {
		DMAERR("Unable to enable ASYNC DEST endpoint %d, GSI %d\n",
			async_dest_endp_id, gsi_id);
		ret = -EFAULT;
		goto fail_enable_async_dest;
	}

	ret = 0;
	goto success;

fail_enable_async_dest:
	ecpri_dma_reset_endp(
		&ecpri_dma_ctx->endp_ctx[gsi_id][async_src_endp_id]);
fail_enable_async_src:
	ecpri_dma_reset_endp(
		&ecpri_dma_ctx->endp_ctx[gsi_id][sync_dest_endp_id]);
fail_enable_sync_dest:
	ecpri_dma_reset_endp(
		&ecpri_dma_ctx->endp_ctx[gsi_id][sync_src_endp_id]);
fail_enable_sync_src:
success:
	return ret;
}

/**
 * ecpri_dma_mhi_start_memcpy_endps() - Helper function to start endpnts
 *
 */
static int ecpri_dma_mhi_start_memcpy_endps(int idx)
{
	int ret = 0;

	int sync_src_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int sync_dest_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int async_src_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int async_dest_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	enum ecpri_dma_gsi_id gsi_id = ECPRI_DMA_GSI_ID_0;

	ecpri_dma_mhi_get_sync_async_endp_ids(&sync_src_endp_id,
		&sync_dest_endp_id, &async_src_endp_id, &async_dest_endp_id, idx);

	ret = ecpri_dma_start_endp(
		&ecpri_dma_ctx->endp_ctx[gsi_id][sync_src_endp_id]);
	if (ret != 0) {
		DMAERR("Unable to start endp, endp_id: %d, gsi_id %d\n",
			sync_src_endp_id, gsi_id);
		ret = -EFAULT;
		goto fail_start_sync_src;
	}

	ret = ecpri_dma_start_endp(
		&ecpri_dma_ctx->endp_ctx[gsi_id][sync_dest_endp_id]);
	if (ret != 0) {
		DMAERR("Unable to start endp, endp_id: %d, gsi_id %d\n",
			sync_dest_endp_id, gsi_id);
		ret = -EFAULT;
		goto fail_start_sync_dest;
	}

	/* Skip the VMs */
	if (async_src_endp_id == ECPRI_DMA_MHI_INVALID_ENDP_ID ||
		async_dest_endp_id == ECPRI_DMA_MHI_INVALID_ENDP_ID)
		goto success;

	ret = ecpri_dma_start_endp(
		&ecpri_dma_ctx->endp_ctx[gsi_id][async_src_endp_id]);
	if (ret != 0) {
		DMAERR("Unable to start endp, endp_id: %d, gsi_id %d\n",
			async_src_endp_id, gsi_id);
		ret = -EFAULT;
		goto fail_start_async_src;
	}

	ret = ecpri_dma_start_endp(
		&ecpri_dma_ctx->endp_ctx[gsi_id][async_dest_endp_id]);
	if (ret != 0) {
		DMAERR("Unable to start endp, endp_id: %d, gsi_id %d\n",
			async_dest_endp_id, gsi_id);
		ret = -EFAULT;
		goto fail_start_async_dest;
	}

	ret = 0;
	goto success;

fail_start_async_dest:
	ecpri_dma_stop_endp(
		&ecpri_dma_ctx->endp_ctx[gsi_id][async_src_endp_id]);
fail_start_async_src:
	ecpri_dma_stop_endp(
		&ecpri_dma_ctx->endp_ctx[gsi_id][sync_dest_endp_id]);
fail_start_sync_dest:
	ecpri_dma_stop_endp(
		&ecpri_dma_ctx->endp_ctx[gsi_id][sync_src_endp_id]);
fail_start_sync_src:
success:
	return ret;
}

/**
 * ecpri_dma_mhi_set_memcpy_endps_mode() - Helper function to set endpnts mode
 *
 */
static int ecpri_dma_mhi_set_memcpy_endps_mode(int idx)
{
	int ret = 0;

	int sync_src_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int sync_dest_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int async_src_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int async_dest_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	enum ecpri_dma_gsi_id gsi_id = ECPRI_DMA_GSI_ID_0;

	ecpri_dma_mhi_get_sync_async_endp_ids(&sync_src_endp_id,
		&sync_dest_endp_id, &async_src_endp_id, &async_dest_endp_id, idx);

	ret = ecpri_dma_set_endp_mode(
		&ecpri_dma_ctx->endp_ctx[gsi_id][sync_dest_endp_id],
		ECPRI_DMA_NOTIFY_MODE_POLL);
	if (ret != 0) {
		DMAERR("Unable to set mode, ENDP ID:%d, GSI ID %d, mode: %d, \n",
			sync_dest_endp_id, gsi_id,
			ECPRI_DMA_NOTIFY_MODE_POLL);
		return ret;
	}

	/* Skip the VMs */
	if (async_src_endp_id == ECPRI_DMA_MHI_INVALID_ENDP_ID ||
		async_dest_endp_id == ECPRI_DMA_MHI_INVALID_ENDP_ID)
		return ret;

	/* Note: Async channels are by default in IRQ mode, no need to set  */

	return ret;
}

/**
 * ecpri_dma_mhi_stop_memcpy_endps() - Helper function to stop endpnts
 *
 */
static int ecpri_dma_mhi_stop_memcpy_endps(int idx)
{
	int ret = 0;

	int sync_src_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int sync_dest_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int async_src_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int async_dest_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	enum ecpri_dma_gsi_id gsi_id = ECPRI_DMA_GSI_ID_0;

	ecpri_dma_mhi_get_sync_async_endp_ids(&sync_src_endp_id,
		&sync_dest_endp_id, &async_src_endp_id, &async_dest_endp_id, idx);

	ret = ecpri_dma_stop_endp(
		&ecpri_dma_ctx->endp_ctx[gsi_id][sync_src_endp_id]);
	if (ret != 0) {
		DMAERR("Unable to stop endp, endp_id: %d, gsi_id %d\n",
			sync_src_endp_id, gsi_id);
		return ret;
	}


	ret = ecpri_dma_stop_endp(
		&ecpri_dma_ctx->endp_ctx[gsi_id][sync_dest_endp_id]);
	if (ret != 0) {
		DMAERR("Unable to stop endp, endp_id: %d, gsi_id %d\n",
			sync_dest_endp_id, gsi_id);
		return ret;
	}

	/* Skip the VMs */
	if (async_src_endp_id == ECPRI_DMA_MHI_INVALID_ENDP_ID ||
		async_dest_endp_id == ECPRI_DMA_MHI_INVALID_ENDP_ID)
		return ret;

	ret = ecpri_dma_stop_endp(
		&ecpri_dma_ctx->endp_ctx[gsi_id][async_src_endp_id]);
	if (ret != 0) {
		DMAERR("Unable to stop endp, endp_id: %d, gsi_id %d\n",
			async_src_endp_id, gsi_id);
		return ret;
	}

	ret = ecpri_dma_stop_endp(
		&ecpri_dma_ctx->endp_ctx[gsi_id][async_dest_endp_id]);
	if (ret != 0) {
		DMAERR("Unable to stop endp, endp_id: %d, gsi_id %d\n",
			async_dest_endp_id, gsi_id);
		return ret;
	}

	return ret;
}

/**
 * ecpri_dma_mhi_dealloc_memcpy_endps() - Helper function to dealloc endpnts
 *
 */
static int ecpri_dma_mhi_dealloc_memcpy_endps(int idx)
{
	int ret = 0;

	int sync_src_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int sync_dest_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int async_src_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int async_dest_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	enum ecpri_dma_gsi_id gsi_id = ECPRI_DMA_GSI_ID_0;

	ecpri_dma_mhi_get_sync_async_endp_ids(&sync_src_endp_id,
		&sync_dest_endp_id, &async_src_endp_id, &async_dest_endp_id, idx);

	ret = ecpri_dma_dealloc_endp(
		&ecpri_dma_ctx->endp_ctx[gsi_id][sync_src_endp_id]);
	if (ret != 0) {
		DMAERR("Unable to deallocate endp, endp_id: %d, gsi_id: %d\n",
			sync_src_endp_id, gsi_id);
		return ret;
	}

	ret = ecpri_dma_dealloc_endp(
		&ecpri_dma_ctx->endp_ctx[gsi_id][sync_dest_endp_id]);
	if (ret != 0) {
		DMAERR("Unable to deallocate endp, endp_id: %d, gsi_id: %d\n",
			sync_dest_endp_id, gsi_id);
		return ret;
	}

	/* Skip the VMs */
	if (async_src_endp_id == ECPRI_DMA_MHI_INVALID_ENDP_ID ||
		async_dest_endp_id == ECPRI_DMA_MHI_INVALID_ENDP_ID)
		return ret;

	ret = ecpri_dma_dealloc_endp(
		&ecpri_dma_ctx->endp_ctx[gsi_id][async_src_endp_id]);
	if (ret != 0) {
		DMAERR("Unable to deallocate endp, endp_id: %d, gsi_id: %d\n",
			async_src_endp_id, gsi_id);
		return ret;
	}

	ret = ecpri_dma_dealloc_endp(
		&ecpri_dma_ctx->endp_ctx[gsi_id][async_dest_endp_id]);
	if (ret != 0) {
		DMAERR("Unable to deallocate endp, endp_id: %d, gsi_id: %d\n",
			async_dest_endp_id, gsi_id);
		return ret;
	}

	return ret;
}

/**
 * ecpri_dma_mhi_reset_memcpy_endps() - Helper function to reset endpnts
 *
 */
static int ecpri_dma_mhi_reset_memcpy_endps(int idx)
{
	int ret = 0;
	struct ecpri_dma_endp_context* endp_cfg = NULL;

	int sync_src_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int sync_dest_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int async_src_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int async_dest_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	enum ecpri_dma_gsi_id gsi_id = ECPRI_DMA_GSI_ID_0;

	ecpri_dma_mhi_get_sync_async_endp_ids(&sync_src_endp_id,
		&sync_dest_endp_id, &async_src_endp_id, &async_dest_endp_id, idx);

	endp_cfg = &ecpri_dma_ctx->endp_ctx[gsi_id][sync_src_endp_id];
	ret = ecpri_dma_reset_endp(endp_cfg);
	if (ret != GSI_STATUS_SUCCESS) {
		DMAERR("Unable to reset endp, endp_id: %d, gsi_id %d\n",
			sync_src_endp_id, gsi_id);
		return ret;
	}

	endp_cfg = &ecpri_dma_ctx->endp_ctx[gsi_id][sync_dest_endp_id];
	ret = ecpri_dma_reset_endp(endp_cfg);
	if (ret != GSI_STATUS_SUCCESS) {
		DMAERR("Unable to reset endp, endp_id: %d, gsi_id %d\n",
			sync_dest_endp_id, gsi_id);
		return ret;
	}

	/* Skip the VMs */
	if (async_src_endp_id == ECPRI_DMA_MHI_INVALID_ENDP_ID ||
		async_dest_endp_id == ECPRI_DMA_MHI_INVALID_ENDP_ID)
		return ret;

	endp_cfg = &ecpri_dma_ctx->endp_ctx[gsi_id][async_src_endp_id];
	ret = ecpri_dma_reset_endp(endp_cfg);
	if (ret != GSI_STATUS_SUCCESS) {
		DMAERR("Unable to reset endp, endp_id: %d, gsi_id %d\n",
			async_src_endp_id, gsi_id);
		return ret;
	}

	endp_cfg = &ecpri_dma_ctx->endp_ctx[gsi_id][async_dest_endp_id];
	ret = ecpri_dma_reset_endp(endp_cfg);
	if (ret != GSI_STATUS_SUCCESS) {
		DMAERR("Unable to reset endp, endp_id: %d, gsi_id %d\n",
			async_dest_endp_id, gsi_id);
		return ret;
	}

	return ret;
}

/**
 * ecpri_dma_mhi_memcpy_init() - Initialize memory copy DMA.
 * @function: function parameters
 *
 * This function initialize all memory copy DMA internal data and connect dma:
 *	MEMCPY_DMA_SYNC_PROD ->MEMCPY_DMA_SYNC_CONS
 *	MEMCPY_DMA_ASYNC_PROD->MEMCPY_DMA_SYNC_CONS
 *
 * Can be executed several times (re-entrant)
 *
 * NOTE: Init memcpy API for SW ENDPs.
 *		 These ENDPs are managed by the A55 DMA driver and are not
 *		 HW accelerated.
 *		 VMs \ PF manages these ENDPs only via the PCIe and
 *		 A55 DMA drivers.
 *
 * Return codes: 0: success
 *		-EFAULT: Mismatch between context existence and init ref_cnt
 *		-EINVAL: HW driver is not initialized
 *		-ENOMEM: allocating memory error
 *		-EPERM: ENDP connection failed
 */
static int ecpri_dma_mhi_memcpy_init(struct mhi_dma_function_params function)
{
	int idx, ret;

	bool ready = false;
	struct ecpri_dma_mhi_memcpy_context* memcpy_ctx = NULL;

	if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
		DMADBG_LOW("Physical \n");
	else
		DMADBG_LOW("Virtual ID %d \n", function.vf_id);

	if (function.function_type != MHI_DMA_FUNCTION_TYPE_PHYSICAL &&
		function.vf_id > ECPRI_DMA_MHI_MAX_VIRTUAL_FUNCTIONS_ID) {
		DMAERR("Illegal function id, vf_id: %d\n",
			function.vf_id);
		return -EINVAL;
	}

	/* Check DMA driver state */
	mutex_lock(&ecpri_dma_ctx->lock);
	ready = ecpri_dma_is_ready();
	mutex_unlock(&ecpri_dma_ctx->lock);

	if (!ready) {
		DMAERR("DMA driver is not ready\n");
		return -EPERM;
	}

	/* Get the index of VM/PF */
	ret = ecpri_dma_mhi_get_function_context_index(
		function, &idx, ECPRI_DMA_MHI_DMA_MEMCPY_CTX);
	if (ret != 0) {
		DMAERR("Function params are invalid,"
			"function type: %d, vf_id: %d\n",
			function.function_type, function.vf_id);
		return -EINVAL;
	}

	mutex_lock(&ecpri_dma_ctx->mhi_memcpy_setup_lock);

	if (!ecpri_dma_mhi_memcpy_ctx[idx]) {
		ecpri_dma_mhi_memcpy_ctx[idx] = kzalloc(
			sizeof(*ecpri_dma_mhi_memcpy_ctx[0]),
			GFP_ATOMIC);
		if (!ecpri_dma_mhi_memcpy_ctx[idx]) {
			ret = -EFAULT;
			goto fail_alloc_ctx;
		}
	}
	else {
		mutex_unlock(&ecpri_dma_ctx->mhi_memcpy_setup_lock);
		return 0;
	}
	memcpy_ctx = ecpri_dma_mhi_memcpy_ctx[idx];

	spin_lock_init(&memcpy_ctx->lock);
	spin_lock_init(&memcpy_ctx->sync_lock);
	spin_lock_init(&memcpy_ctx->async_lock);
	memcpy_ctx->async_wq = alloc_ordered_workqueue("%s",
		__WQ_LEGACY | WQ_MEM_RECLAIM | WQ_HIGHPRI,
		"ECPRI_DMA_MHI_MEMCPY_ASYNC_WQ");
	init_completion(&memcpy_ctx->done);
	memcpy_ctx->destroy_pending = false;
	atomic_set(&memcpy_ctx->ref_count, 0);
	atomic_set(&memcpy_ctx->async_pending, 0);
	atomic_set(&memcpy_ctx->sync_pending, 0);
	atomic_set(&memcpy_ctx->sync_total, 0);
	atomic_set(&memcpy_ctx->async_total, 0);

	/* Allocate endpoints */
	ret = ecpri_dma_mhi_alloc_sync_async_endps(function, idx);
	if (ret != 0) {
		DMAERR("Unable to allocate endp\n");
		goto fail_alloc_endp;
	}

	/* Enable endpoints */
	ret = ecpri_dma_mhi_enable_mhi_memcpy_endps(idx);
	if (ret != 0) {
		DMAERR("Unable to enable endp\n");
		goto fail_enable_endp;
	}

	/* Set endpoints */
	ecpri_dma_mhi_set_endps(idx, memcpy_ctx);

	// TODO: init_memcpy_debugfs()

	ECPRI_DMA_MEMRING_INIT(memcpy_ctx->async_work_ring,
	ECPRI_DMA_MHI_ASYNC_MEMCPY_RLEN);

	ECPRI_DMA_MEMRING_INIT(memcpy_ctx->xfer_descr_ring,
	ECPRI_DMA_MHI_ASYNC_MEMCPY_RLEN);

	ECPRI_DMA_MEMRING_INIT(memcpy_ctx->src_func_ring,
	ECPRI_DMA_MHI_ASYNC_MEMCPY_RLEN);

	ECPRI_DMA_MEMRING_INIT(memcpy_ctx->dst_func_ring,
	ECPRI_DMA_MHI_ASYNC_MEMCPY_RLEN);

	ECPRI_DMA_MEMRING_INIT(memcpy_ctx->src_pkt_ring,
	ECPRI_DMA_MHI_ASYNC_MEMCPY_RLEN);

	ECPRI_DMA_MEMRING_INIT(memcpy_ctx->src_bufs_ptr_ring,
	ECPRI_DMA_MHI_ASYNC_MEMCPY_RLEN);

	ECPRI_DMA_MEMRING_INIT(memcpy_ctx->src_bufs_ring,
	ECPRI_DMA_MHI_ASYNC_MEMCPY_RLEN);

	ECPRI_DMA_MEMRING_INIT(memcpy_ctx->dst_pkt_ring,
	ECPRI_DMA_MHI_ASYNC_MEMCPY_RLEN);

	ECPRI_DMA_MEMRING_INIT(memcpy_ctx->dst_bufs_ptr_ring,
	ECPRI_DMA_MHI_ASYNC_MEMCPY_RLEN);

	ECPRI_DMA_MEMRING_INIT(memcpy_ctx->dst_bufs_ring,
	ECPRI_DMA_MHI_ASYNC_MEMCPY_RLEN);

	ret = 0;
	goto success;

fail_enable_endp:
	/* Dealloc endpoints */
	ret = ecpri_dma_mhi_dealloc_memcpy_endps(idx);
	if (ret != 0) {
		DMAERR("Unable to deallocate endps\n");
		ecpri_dma_assert();
	}
fail_alloc_endp:
	kfree(ecpri_dma_mhi_memcpy_ctx[idx]);
	ecpri_dma_mhi_memcpy_ctx[idx] = NULL;
success:
fail_alloc_ctx:
	if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
		DMADBG_LOW("Done Physical \n");
	else
		DMADBG_LOW("Done Virtual ID %d \n", function.vf_id);
	mutex_unlock(&ecpri_dma_ctx->mhi_memcpy_setup_lock);

	return ret;
}

static void ecpri_dma_mhi_memcpy_destroy(
	struct mhi_dma_function_params function)
{
	int ret, idx;

	int sync_src_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int sync_dest_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int async_src_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int async_dest_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	struct ecpri_dma_mhi_memcpy_context* memcpy_ctx = NULL;
	const struct ecpri_dma_mhi_ee_gsi_tuple* func_map;

	if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
		DMADBG_LOW("Physical \n");
	else
		DMADBG_LOW("Virtual ID %d \n", function.vf_id);

	ret = ecpri_dma_mhi_get_function_mapping(function, &func_map);
	if (ret)
	{
		DMAERR("Unknown function");
		return;
	}

	/* Get the index of VM/PF */
	ret = ecpri_dma_mhi_get_function_context_index(
		function, &idx, ECPRI_DMA_MHI_DMA_MEMCPY_CTX);
	if (ret != 0) {
		DMAERR("Function params are invalid,"
			"function type: %d, vf_id: %d\n",
			function.function_type, function.vf_id);
		return;
	}

	mutex_lock(&ecpri_dma_ctx->mhi_memcpy_setup_lock);
	memcpy_ctx = ecpri_dma_mhi_memcpy_ctx[idx];
	if (!memcpy_ctx) {
		DMAERR("Memcpy context for IDX %d uninitialized\n",
			idx);
		mutex_unlock(&ecpri_dma_ctx->mhi_memcpy_setup_lock);
		return;
	}

	if (!ecpri_dma_mhi_check_destroy_pending(memcpy_ctx)) {
		DMAERR("Memcpy destroy is not in progress\n");
		mutex_unlock(&ecpri_dma_ctx->mhi_memcpy_setup_lock);
		return;
	}

	ecpri_dma_mhi_get_sync_async_endp_ids(&sync_src_endp_id,
		&sync_dest_endp_id, &async_src_endp_id, &async_dest_endp_id, idx);

	/* Reset endpoints */
	ret = ecpri_dma_mhi_reset_memcpy_endps(idx);
	if (ret != 0) {
		DMAERR("Unable to reset endps\n");
		ecpri_dma_assert();
	}

	/* Dealloc endpoints */
	ret = ecpri_dma_mhi_dealloc_memcpy_endps(idx);
	if (ret != 0) {
		DMAERR("Unable to deallocate endps\n");
		ecpri_dma_assert();
	}

	/* Reset variables */
	memcpy_ctx->destroy_pending = false;
	atomic_set(&memcpy_ctx->ref_count, 0);
	atomic_set(&memcpy_ctx->async_pending, 0);
	atomic_set(&memcpy_ctx->sync_pending, 0);
	atomic_set(&memcpy_ctx->sync_total, 0);
	atomic_set(&memcpy_ctx->async_total, 0);

	/* Reset endpoints */
	memcpy_ctx->sync_dest_endp = NULL;
	memcpy_ctx->sync_src_endp = NULL;

	if (async_src_endp_id != ECPRI_DMA_MHI_INVALID_ENDP_ID &&
		async_dest_endp_id != ECPRI_DMA_MHI_INVALID_ENDP_ID)
	{
		memcpy_ctx->async_dest_endp = NULL;
		memcpy_ctx->async_src_endp = NULL;
	}

	kfree(ecpri_dma_mhi_memcpy_ctx[idx]);
	ecpri_dma_mhi_memcpy_ctx[idx] = NULL;

	if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
		DMADBG_LOW("Done Physical \n");
	else
		DMADBG_LOW("Done Virtual ID %d \n", function.vf_id);
	mutex_unlock(&ecpri_dma_ctx->mhi_memcpy_setup_lock);
}

/**
* ecpri_dma_mhi_dma_sync_memcpy()- Perform synchronous
* memcpy using DMA.
*
* @dest: physical address to store the copied data.
* @src: physical address of the source data to copy.
* @len: number of bytes to copy.
* @function: function parameters
*
* Return codes:    0: success
*		            -EINVAL: invalid params
*		            -EPERM: operation not permitted as dma isn't
*		            	    enable or initialized
*		            -gsi_status : on GSI failures
*		            -EFAULT: other
*/
static int ecpri_dma_mhi_dma_sync_memcpy(
	u64 dest, u64 src, int len,
	struct mhi_dma_function_params function)
{
	int idx;
	int ret;
	u32 actual_num;
	unsigned long flags;

	struct ecpri_dma_pkt* pkts_dest = NULL;
	struct ecpri_dma_pkt* pkts_src = NULL;
	struct ecpri_dma_mhi_memcpy_context* memcpy_ctx = NULL;
	struct ecpri_dma_pkt_completion_wrapper* pkt_wrapper = NULL;

	struct ecpri_dma_mhi_alloc_pkt_params src_params = {0};
	struct ecpri_dma_mhi_alloc_pkt_params dst_params = {0};

	if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
		DMADBG_LOW("Physical \n");
	else
		DMADBG_LOW("Virtual ID %d \n", function.vf_id);

	if ((max(src, dest) - min(src, dest)) < len) {
		DMAERR("Invalid addresses - overlapping buffers\n");
		return -EINVAL;
	}

	if (len > ECPRI_DMA_MHI_DMA_MAX_PKT_SZ || len <= 0) {
		DMAERR("Invalid len, %d\n", len);
		return -EINVAL;
	}

	/* Get the index of VM/PF */
	ret = ecpri_dma_mhi_get_function_context_index(
		function, &idx, ECPRI_DMA_MHI_DMA_MEMCPY_CTX);
	if (ret != 0) {
		DMAERR("Function params are invalid,"
			"function type: %d, vf_id: %d\n",
			function.function_type, function.vf_id);
		return -EINVAL;
	}

	memcpy_ctx = ecpri_dma_mhi_memcpy_ctx[idx];
	if (!memcpy_ctx) {
		DMAERR("Memcpy context is not initialized\n");
		return -EPERM;
	}

	if (ecpri_dma_mhi_check_destroy_pending(memcpy_ctx) == true) {
		DMAERR("Memcpy destroy in progress\n");
		return -EFAULT;
	}

	if (atomic_read(&memcpy_ctx->ref_count) == 0) {
		DMAERR("Reference count is equal to zero\n");
		return -EPERM;
	}

	/* Only single SYNC transfer allowed */
	spin_lock_irqsave(&memcpy_ctx->sync_lock, flags);
	while (atomic_read(&memcpy_ctx->sync_pending) > 0) {
		spin_unlock_irqrestore(&memcpy_ctx->sync_lock, flags);
		usleep_range(ECPRI_DMA_MHI_POLLING_MIN_SLEEP_RX,
			ECPRI_DMA_MHI_POLLING_MAX_SLEEP_RX);
		spin_lock_irqsave(&memcpy_ctx->sync_lock, flags);
	}

	atomic_inc(&memcpy_ctx->sync_pending);
	spin_unlock_irqrestore(&memcpy_ctx->sync_lock, flags);

	dst_params.buff_addr = dest;
	dst_params.len = len;
	dst_params.function = &function;
	dst_params.pkt_type = ECPRI_DMA_MHI_SYNC_PACKET;

	/* Allocate packets */
	ret = ecpri_dma_mhi_alloc_pkt(&dst_params, &pkts_dest);

	if (ret != 0) {
		DMAERR("Unable to allocate packets for destination\n");
		ret = -EPERM;
		goto fail_dest_alloc;
	}

	src_params.buff_addr = src;
	src_params.len = len;
	src_params.function = &function;
	src_params.pkt_type = ECPRI_DMA_MHI_SYNC_PACKET;
	ret = ecpri_dma_mhi_alloc_pkt(&src_params, &pkts_src);

	if (ret != 0) {
		DMAERR("Unable to allocate packets for source\n");
		ret = -EPERM;
		goto fail_src_alloc;
	}

	/* Transmit packets */
	ret = ecpri_dma_dp_transmit(memcpy_ctx->sync_dest_endp,
		&pkts_dest, 1, true);
	if (ret != 0) {
		DMAERR("Unable to transmit dest\n");
		ret = -EFAULT;
		goto fail_transmit;
	}

	ret = ecpri_dma_dp_transmit(memcpy_ctx->sync_src_endp,
		&pkts_src, 1, true);
	if (ret != 0) {
		DMAERR("Unable to transmit SRC but dest is already queued\n");
		ecpri_dma_assert();
	}

	actual_num = 0;
	memcpy_ctx->loop_counter = 0;
	pkt_wrapper = kzalloc(sizeof(struct ecpri_dma_pkt_completion_wrapper),
		GFP_KERNEL);
	if (!pkt_wrapper) {
		DMAERR("Unable to allocate pkt_wrapper\n");
		ret = -ENOMEM;
		goto fail_alloc_wrapper;
	}

	while (actual_num == 0)
	{
		memcpy_ctx->loop_counter++;

		/* memcpy uses single buffer packet so actual_num == num of buffers
		no need to check for EOT */
		ret = ecpri_dma_dp_poll(memcpy_ctx->sync_dest_endp, 1,
			&pkt_wrapper, &actual_num);
		if (ret != 0) {
			DMAERR("Unable to poll\n");
			ret = -EPERM;
			goto fail_poll_rx;
		}
	}
	memcpy_ctx->loop_counter = 0;

	spin_lock_irqsave(&memcpy_ctx->sync_lock, flags);
	atomic_inc(&memcpy_ctx->sync_total);
	atomic_dec(&memcpy_ctx->sync_pending);
	spin_unlock_irqrestore(&memcpy_ctx->sync_lock, flags);

	ret = 0;
	goto success;

fail_poll_rx:
	kfree(pkt_wrapper);
	atomic_dec(&memcpy_ctx->sync_pending);
fail_alloc_wrapper:
fail_transmit:
success:
	ecpri_dma_mhi_free_pkt_from_heap(&pkts_src);
fail_src_alloc:
	ecpri_dma_mhi_free_pkt_from_heap(&pkts_dest);
fail_dest_alloc:

	if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
		DMADBG_LOW("Done Physical \n");
	else
		DMADBG_LOW("Done Virtual ID %d \n", function.vf_id);

	return ret;
}

static int ecpri_dma_mhi_dma_async_memcpy_vm_handling(
	u64 dest, u64 src, int len,
	struct mhi_dma_function_params function,
	void (*user_cb)(void* user1),
	void* user_param)
{
	int ret = 0, idx = 0;
	struct ecpri_dma_mhi_async_wq_work_type* work = NULL;
	struct ecpri_dma_mhi_memcpy_context* memcpy_ctx = NULL;

	/* Get the index of VM/PF */
	ret = ecpri_dma_mhi_get_function_context_index(
		function, &idx, ECPRI_DMA_MHI_DMA_MEMCPY_CTX);
	if (ret != 0) {
		DMAERR("Function params are invalid,"
			"function type: %d, vf_id: %d\n",
			function.function_type, function.vf_id);
		return -EINVAL;
	}

	memcpy_ctx = ecpri_dma_mhi_memcpy_ctx[idx];
	if (!memcpy_ctx) {
		DMAERR("Memcpy context is not initialized\n");
		return -EPERM;
	}

	if (ecpri_dma_mhi_check_destroy_pending(memcpy_ctx) == true) {
		DMAERR("Memcpy destroy in progress\n");
		return -EFAULT;
	}

	/* Allocate xfer descriptor  */
	ECPRI_DMA_MEMRING_ALLOC_ITEM(memcpy_ctx->xfer_descr_ring);

	/* Assign items */
	ECPRI_DMA_MEMRING_ACCESS_WP(memcpy_ctx->xfer_descr_ring).user_cb = user_cb;
	ECPRI_DMA_MEMRING_ACCESS_WP(memcpy_ctx->xfer_descr_ring).user_data = user_param;
	ECPRI_DMA_MEMRING_ACCESS_WP(memcpy_ctx->xfer_descr_ring).function = function;

	/* Allocate item */
	ECPRI_DMA_MEMRING_ALLOC_ITEM(memcpy_ctx->async_work_ring);
	work = &ECPRI_DMA_MEMRING_ACCESS_WP(memcpy_ctx->async_work_ring);

	ret = ecpri_dma_mhi_dma_sync_memcpy(dest, src, len, function);
	if (ret)
	{
		DMAERR("SYNC transfer failed, ret = %d\n", ret);
		return ret;
	}

	INIT_WORK(&work->work,
		ecpri_dma_mhi_memcpy_async_wq_cb_ready_vms);
	work->xfer_desc = &ECPRI_DMA_MEMRING_ACCESS_WP(memcpy_ctx->xfer_descr_ring);

	queue_work(memcpy_ctx->async_wq, &work->work);

	return 0;
}

/**
 * ecpri_dma_mhi_dma_async_memcpy()- Perform asynchronous
 * memcpy using DMA.
 *
 * @dest: physical address to store the copied data.
 * @src: physical address of the source data to copy.
 * @len: number of bytes to copy.
 * @user_cb: callback function to notify the client when the copy was done.
 * @user_param: cookie for user_cb.
 *
 * Return codes:    0: success
 *		            -EINVAL: invalid params
 *		            -EPERM: operation not permitted as dma isn't
 *		            	    enable or initialized
 *		            -gsi_status : on GSI failures
 *		            -EFAULT: descr fifo is full.
 */
static int ecpri_dma_mhi_dma_async_memcpy(
	u64 dest, u64 src, int len,
	struct mhi_dma_function_params function,
	void (*user_cb)(void* user1),
	void* user_param)
{
	int idx;
	int ret = 0;
	unsigned long flags;
	struct ecpri_dma_pkt* pkt_dest = NULL;
	struct ecpri_dma_pkt* pkt_src = NULL;
	struct ecpri_dma_mhi_memcpy_context* memcpy_ctx = NULL;
	struct ecpri_dma_mhi_alloc_pkt_params src_params = {0};
	struct ecpri_dma_mhi_alloc_pkt_params dst_params = {0};
	int hw_ver = ECPRI_DMA_GET_CTX_HW_VER();

	if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
		DMADBG_LOW("Physical \n");
	else
		DMADBG_LOW("Virtual ID %d \n", function.vf_id);

	if ((max(src, dest) - min(src, dest)) < len) {
		DMAERR("Invalid addresses - overlapping buffers\n");
		return -EINVAL;
	}
	if (len > ECPRI_DMA_MHI_DMA_MAX_PKT_SZ || len <= 0) {
		DMAERR("Invalid len, %d\n", len);
		return -EINVAL;
	}

	/* Get the index of VM/PF */
	ret = ecpri_dma_mhi_get_function_context_index(
		function, &idx, ECPRI_DMA_MHI_DMA_MEMCPY_CTX);
	if (ret != 0) {
		DMAERR("Function params are invalid,"
			"function type: %d, vf_id: %d\n",
			function.function_type, function.vf_id);
		return -EINVAL;
	}

	memcpy_ctx = ecpri_dma_mhi_memcpy_ctx[idx];
	if (!memcpy_ctx) {
		DMAERR("Memcpy context is not initialized\n");
		return -EPERM;
	}

	if (ecpri_dma_mhi_check_destroy_pending(memcpy_ctx) == true) {
		DMAERR("Memcpy destroy in progress\n");
		return -EFAULT;
	}

	if (!user_cb) {
		DMAERR("null pointer: user_cb\n");
		return -EINVAL;
	}

	if (function.function_type ==
		MHI_DMA_FUNCTION_TYPE_VIRTUAL && hw_ver == ECPRI_HW_V1_0) {
		DMADBG("No ASYNC for VM, using SYNC instead\n");
		return ecpri_dma_mhi_dma_async_memcpy_vm_handling(dest, src, len,
			function, user_cb, user_param);
	}

	if (atomic_read(&memcpy_ctx->ref_count) == 0) {
		DMAERR("Reference count is equal to zero\n");
		return -EPERM;
	}

	/* Start async transfer section */
	spin_lock_irqsave(&memcpy_ctx->async_lock, flags);

	/* Alloc new item */
	ECPRI_DMA_MEMRING_ALLOC_ITEM(memcpy_ctx->xfer_descr_ring);

	/* Assign user callback */
	ECPRI_DMA_MEMRING_ACCESS_WP(
		memcpy_ctx->xfer_descr_ring).user_cb = user_cb;

	/* Assign user param */
	ECPRI_DMA_MEMRING_ACCESS_WP(
		memcpy_ctx->xfer_descr_ring).user_data = user_param;
	dst_params.buff_addr = dest;
	dst_params.len = len;
	dst_params.function = &function;
	dst_params.pkt_type = ECPRI_DMA_MHI_ASYNC_PACKET;
	dst_params.dir = ECPRI_DMA_ENDP_DIR_DEST;
	dst_params.memcpy_ctx = memcpy_ctx;

	/* Allocate destination packet */
	ret = ecpri_dma_mhi_alloc_pkt(&dst_params, &pkt_dest);

	if (ret != 0) {
		DMAERR("Unable to allocate packets for destination\n");
		ecpri_dma_assert();
	}

	src_params.buff_addr = src;
	src_params.len = len;
	src_params.function = &function;
	src_params.pkt_type = ECPRI_DMA_MHI_ASYNC_PACKET;
	src_params.dir = ECPRI_DMA_ENDP_DIR_SRC;
	src_params.memcpy_ctx = memcpy_ctx;

	/* Allocate source packet */
	ret = ecpri_dma_mhi_alloc_pkt(&src_params, &pkt_src);

	if (ret != 0) {
		DMAERR("Unable to allocate packets for source\n");
		ecpri_dma_assert();
	}

	/* Update number of pending async transmits */
	atomic_inc(&memcpy_ctx->async_pending);

	ret = ecpri_dma_dp_transmit(
		memcpy_ctx->async_dest_endp,
		&pkt_dest, 1, true);

	if (ret != 0) {
		DMAERR("Unable to transmit DST\n");
		ecpri_dma_assert();
	}

	ret = ecpri_dma_dp_transmit(
		memcpy_ctx->async_src_endp,
		&pkt_src, 1, true);

	if (ret != 0) {
		DMAERR("Unable to transmit SRC but dest is already queued\n");
		ecpri_dma_assert();
	}

	/* Free the source packet */
	ecpri_dma_mhi_free_pkt_from_ring(
		ECPRI_DMA_ENDP_DIR_SRC,
		memcpy_ctx);

	/* Exit async transfer section */
	spin_unlock_irqrestore(&memcpy_ctx->async_lock, flags);

	if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
		DMADBG_LOW("Done Physical \n");
	else
		DMADBG_LOW("Done Virtual ID %d \n", function.vf_id);

	return ret;
}

/**
 * ecpri_dma_mhi_dma_memcpy_disable()- Unvote for HW clocks.
 *
 * @function: function parameters
 *
 * enter to power save mode.
 *
 * Return codes: 0: success
 *		-EINVAL: HW DMA is not initialized
 *		-EPERM: Operation not permitted as mhi_dma is already diabled
 *		-EFAULT: can not disable mhi_dma as there are pending memcopy works
 */
static int ecpri_dma_mhi_dma_memcpy_disable(
	struct mhi_dma_function_params function)
{
	int idx;
	int ret = 0;

	unsigned long flags;
	unsigned long flags_sync;
	unsigned long flags_async;

	struct ecpri_dma_mhi_memcpy_context* memcpy_ctx;

	if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
		DMADBG_LOW("Physical \n");
	else
		DMADBG_LOW("Virtual ID %d \n", function.vf_id);

	/* Get the index of VM/PF */
	ret = ecpri_dma_mhi_get_function_context_index(
		function, &idx, ECPRI_DMA_MHI_DMA_MEMCPY_CTX);
	if (ret != 0) {
		DMAERR("Function params are invalid,"
			"function type: %d, vf_id: %d\n",
			function.function_type, function.vf_id);
		return -EINVAL;
	}

	memcpy_ctx = ecpri_dma_mhi_memcpy_ctx[idx];
	if (!memcpy_ctx) {
		DMAERR(
			"Memcpy context is not initialized function type: %d, vf_id: %d",
			function.function_type, function.vf_id);
		return 0;
	}

	if (ecpri_dma_mhi_check_destroy_pending(memcpy_ctx) == true) {
		DMAERR("Memcpy destroy in progress\n");
		return -EFAULT;
	}

	spin_lock_irqsave(&memcpy_ctx->lock,
		flags);

	if (atomic_read(&memcpy_ctx->ref_count) > 1) {
		atomic_dec(&memcpy_ctx->ref_count);
		spin_unlock_irqrestore(
			&memcpy_ctx->lock,
			flags);

		if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
			DMADBG_LOW("Done Physical \n");
		else
			DMADBG_LOW("Done Virtual ID %d \n", function.vf_id);

		return 0;
	}

	if (atomic_read(&memcpy_ctx->ref_count) == 0) {
		spin_unlock_irqrestore(
			&memcpy_ctx->lock,
			flags);

		if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
			DMADBG_LOW("Done Physical \n");
		else
			DMADBG_LOW("Done Virtual ID %d \n", function.vf_id);

		return 0;
	}

	spin_lock_irqsave(
		&memcpy_ctx->async_lock,
		flags_async);
	if (atomic_read(&memcpy_ctx->async_pending) > 0) {
		spin_unlock_irqrestore(
			&memcpy_ctx->async_lock,
			flags_async);
		spin_unlock_irqrestore(
			&memcpy_ctx->lock,
			flags);
		return -EFAULT;
	}

	spin_lock_irqsave(
		&memcpy_ctx->sync_lock,
		flags_sync);
	if (atomic_read(&memcpy_ctx->sync_pending) > 0) {
		spin_unlock_irqrestore(
			&memcpy_ctx->sync_lock,
			flags_sync);
		spin_unlock_irqrestore(
			&memcpy_ctx->async_lock,
			flags_async);
		spin_unlock_irqrestore(
			&memcpy_ctx->lock,
			flags);
		return -EFAULT;
	}

	memcpy_ctx->destroy_pending = true;

	spin_unlock_irqrestore(&memcpy_ctx->sync_lock,
		flags_sync);
	spin_unlock_irqrestore(&memcpy_ctx->async_lock,
		flags_async);
	spin_unlock_irqrestore(&memcpy_ctx->lock,
		flags);

	/* Stop endpoints */
	ret = ecpri_dma_mhi_stop_memcpy_endps(idx);
	if (ret != 0) {
		DMAERR("Unable to stop endp\n");
		return ret;
	}

	if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
		DMADBG_LOW("Done Physical \n");
	else
		DMADBG_LOW("Done Virtual ID %d \n", function.vf_id);

	return ret;
}

/**
 * ecpri_dma_mhi_set_state() - Set the state of the MHI client
 * @ctx: MHI client context
 * @new_state: state to be changed to
 *
 * Return codes: 0: success
 *		-EPERM: failed to set state
 */
static int ecpri_dma_mhi_set_state(
	struct ecpri_dma_mhi_client_context* ctx,
	enum ecpri_dma_mhi_state new_state)
{
	int ret = -EPERM;
	unsigned long flags;

	DMADBG("Current state: %s\n",
		ECPRI_DMA_MHI_STATE_STR(ctx->state));
	spin_lock_irqsave(&ctx->lock, flags);

	if (ctx->state == ECPRI_DMA_MHI_STATE_INITIALIZED &&
		new_state == ECPRI_DMA_MHI_STATE_READY) {
		ctx->state = ECPRI_DMA_MHI_STATE_READY;
		ret = 0;
	}
	else if (ctx->state == ECPRI_DMA_MHI_STATE_READY &&
		new_state == ECPRI_DMA_MHI_STATE_STARTED) {
		ctx->state = ECPRI_DMA_MHI_STATE_STARTED;
		ret = 0;
	}
	else {
		DMAERR("Invalid state, current state: %d, new state: %d\n",
			ctx->state, new_state);
	}

	spin_unlock_irqrestore(&ctx->lock, flags);
	return ret;
}

/**
* mhi_dma_memcpy_enable() - Vote for HW clocks.
*
* @function: function parameters
*
* Return codes: 0: success
*	-EINVAL: HW DMA is not initialized
*/
static int ecpri_dma_mhi_dma_memcpy_enable(
	struct mhi_dma_function_params function)
{
	int idx;
	int ret = 0;
	int sync_src_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int sync_dest_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int async_src_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	int async_dest_endp_id = ECPRI_DMA_MHI_INVALID_ENDP_ID;
	struct ecpri_dma_mhi_memcpy_context* memcpy_ctx;
	const struct ecpri_dma_mhi_ee_gsi_tuple* func_map;

	if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
		DMADBG_LOW("Physical \n");
	else
		DMADBG_LOW("Virtual ID %d \n", function.vf_id);

	/* Check function params are valid */
	ret = ecpri_dma_mhi_get_function_mapping(function, &func_map);
	if (ret)
	{
		DMAERR("Unknown function");
		return ret;
	}

	ret = ecpri_dma_mhi_get_function_context_index(
		function, &idx, ECPRI_DMA_MHI_DMA_MEMCPY_CTX);
	if (ret != 0) {
		DMAERR("Function params are invalid,"
			"function type: %d, vf_id: %d\n",
			function.function_type, function.vf_id);
		return -EINVAL;
	}

	mutex_lock(&ecpri_dma_ctx->mhi_memcpy_setup_lock);
	if (!ecpri_dma_mhi_memcpy_ctx[idx]) {
		DMAERR("Memcpy context for IDX %d is not initialized\n",
			idx);
		mutex_unlock(&ecpri_dma_ctx->mhi_memcpy_setup_lock);
		return -EINVAL;
	}

	memcpy_ctx = ecpri_dma_mhi_memcpy_ctx[idx];

	if (ecpri_dma_mhi_check_destroy_pending(memcpy_ctx) == true) {
		DMAERR("Memcpy destroy in progress\n");
		mutex_unlock(&ecpri_dma_ctx->mhi_memcpy_setup_lock);
		return -EFAULT;
	}

	if (atomic_read(&memcpy_ctx->ref_count)) {
		atomic_inc(&memcpy_ctx->ref_count);
		if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
			DMADBG_LOW("Done Physical \n");
		else
			DMADBG_LOW("Done Virtual ID %d \n", function.vf_id);
		mutex_unlock(&ecpri_dma_ctx->mhi_memcpy_setup_lock);
		return 0;
	}

	ecpri_dma_mhi_get_sync_async_endp_ids(&sync_src_endp_id,
		&sync_dest_endp_id, &async_src_endp_id, &async_dest_endp_id, idx);

	atomic_inc(&memcpy_ctx->ref_count);

	/* Start endpoints */
	ret = ecpri_dma_mhi_start_memcpy_endps(idx);
	if (ret != 0) {
		DMAERR("Unable to start endp\n");
		ret = -EPERM;
		goto fail_start_endp;
	}

	/* Set endpoints mode */
	ret = ecpri_dma_mhi_set_memcpy_endps_mode(idx);
	if (ret != 0) {
		DMAERR("Unable to set endpoints mode\n");
		goto fail_set_mode;
	}

	ret = 0;
	goto success;

fail_set_mode:
	/* Stop endpoints */
	ret = ecpri_dma_mhi_stop_memcpy_endps(idx);
	if (ret != 0) {
		DMAERR("Unable to stop endps\n");
		ecpri_dma_assert();
	}
	/* Reset endpoints */
	ret = ecpri_dma_mhi_reset_memcpy_endps(idx);
	if (ret != 0) {
		DMAERR("Unable to reset endps\n");
		ecpri_dma_assert();
	}
fail_start_endp:
success:
	if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
		DMADBG_LOW("Done Physical \n");
	else
		DMADBG_LOW("Done Virtual ID %d \n", function.vf_id);
	mutex_unlock(&ecpri_dma_ctx->mhi_memcpy_setup_lock);

	return ret;
}

/**
 * ecpri_dma_mhi_client_init() - Register to DMA MHI client
 * @function: function parameters
 * @params: Registration params
 *
 * This function is called by MHI client driver on boot to register DMA MHI
 * Client. When this function returns device can move to READY state.
 * This function is doing the following:
 *	- Initialize MHI DMA internal data structures
 *	- Initialize debugfs
 *	- Initialize SYNC and ASYNC DMA ENDPs
 *
 * Return codes:    0 : success
 *		            negative : error
 */
static int ecpri_dma_mhi_client_init(
	struct mhi_dma_function_params function,
	struct mhi_dma_init_params *params, struct mhi_dma_init_out *out)
{
	int i;
	int idx;
	int ret;
	enum ecpri_dma_ees ee_idx;
	u32 gsi_id;
	struct ecpri_dma_mhi_wq_work_type* work = NULL;
	const struct ecpri_dma_mhi_ee_gsi_tuple* func_map;

	if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
		DMADBG_LOW("Physical \n");
	else
		DMADBG_LOW("Virtual ID %d \n", function.vf_id);


	if (!params) {
		DMAERR("Null params args\n");
		return -EINVAL;
	}

	if (!params->notify) {
		DMAERR("Null notify function\n");
		return -EINVAL;
	}

	ret = ecpri_dma_mhi_get_function_context_index(function, &idx,
		ECPRI_DMA_MHI_DMA_CLIENT_CTX);
	if (ret != 0) {
		DMAERR("Function params are invalid,"
			"function type: %d, vf_id: %d\n",
			function.function_type, function.vf_id);
		return -EINVAL;
	}

	if (ecpri_dma_mhi_client_ctx[idx] &&
		ecpri_dma_mhi_client_ctx[idx]->state ==
		ECPRI_DMA_MHI_STATE_READY) {
		DMAERR("Context with IDX: %d already in READY state\n",
			idx);
		ret = -EEXIST;
		goto fail_ready_state;
	}
	else if(ecpri_dma_mhi_client_ctx[idx])
	{
		DMAERR("Context with IDX: %d is already initialized\n",
			idx);
		return -EPERM;
	}

	/* Initialize context */
	ecpri_dma_mhi_client_ctx[idx] = kzalloc(
		sizeof(*ecpri_dma_mhi_client_ctx[0]),
		GFP_KERNEL);
	if (!ecpri_dma_mhi_client_ctx[idx]) {
		ret = -ENOMEM;
		goto fail_alloc_ctx;
	}

	ecpri_dma_mhi_client_ctx[idx]->notify_cb =
		params->notify;
	ecpri_dma_mhi_client_ctx[idx]->user_data =
		params->priv;
	ecpri_dma_mhi_client_ctx[idx]->msi_config =
		params->msi;
	ecpri_dma_mhi_client_ctx[idx]->mmio_addr =
		params->mmio_addr;
	ecpri_dma_mhi_client_ctx[idx]->first_ch =
		params->first_ch_idx;
	ecpri_dma_mhi_client_ctx[idx]->dev_scratch
		.mhi_base_chan_idx_valid = true;
	ecpri_dma_mhi_client_ctx[idx]->dev_scratch
		.mhi_base_chan_idx = params->first_ch_idx;
	ecpri_dma_mhi_client_ctx[idx]->first_ev =
		params->first_er_idx;
	ecpri_dma_mhi_client_ctx[idx]->is_over_pcie =
		!!params->assert_bit40;
	ecpri_dma_mhi_client_ctx[idx]->mhi_mstate =
		MHI_DMA_STATE_M0;
	ecpri_dma_mhi_client_ctx[idx]->state =
		ECPRI_DMA_MHI_STATE_INITIALIZED;

	spin_lock_init(&ecpri_dma_mhi_client_ctx[idx]->lock);

	/* Initialize workqueue */
	ecpri_dma_mhi_client_ctx[idx]->wq =
		create_singlethread_workqueue(wq_name[idx]);
	if (!ecpri_dma_mhi_client_ctx[idx]->wq) {
		DMAERR("Failed to create workqueue\n");
		ret = -EFAULT;
		goto fail_create_wq;
	}

	ret = ecpri_dma_mhi_memcpy_init(function);
	if (ret != 0) {
		DMAERR("Failed to init memcpy\n");
		ret = -EFAULT;
		goto fail_memcpy_init;
	}

	ret = ecpri_dma_mhi_dma_memcpy_enable(function);
	if (ret != 0) {
		DMAERR("Failed to enable memcpy\n");
		ret = -EFAULT;
		goto fail_memcpy_enable;
	}

	// TODO: Debugfs init()

	/* Init channels */
	for (i = 0; i < ECPRI_DMA_MHI_MAX_HW_CHANNELS; i++)
	{
		ecpri_dma_mhi_client_ctx[idx]->
			channels[i].valid = false;
		ecpri_dma_mhi_client_ctx[idx]->
			channels[i].state =
			ECPRI_DMA_HW_MHI_CHANNEL_STATE_INVALID;
	}

	idr_init(&ecpri_dma_mhi_client_ctx[idx]->idr);
	spin_lock_init(&ecpri_dma_mhi_client_ctx[idx]->idr_lock);

	/* Set state to READY */
	ret = ecpri_dma_mhi_set_state(ecpri_dma_mhi_client_ctx[idx],
		ECPRI_DMA_MHI_STATE_READY);
	if (ret != 0) {
		DMAERR("Unable to set state, State:%d\n",
			ECPRI_DMA_MHI_STATE_READY);
		ret = -EFAULT;
		goto fail_set_state;
	}

	ret = ecpri_dma_mhi_get_function_mapping(function, &func_map);
	if (ret)
	{
		DMAERR("Unknown function");
		return ret;
	}
	ee_idx = func_map->ee_id;
	gsi_id = func_map->gsi_id;

	/* Fill out param */
	ecpri_dma_mhi_get_l2_ch_bitmap(function, idx, &out->ch_db_fwd_msk);
	out->ev_db_fwd_msk = out->ch_db_fwd_msk;
	out->ch_db_fwd_base = gsihal_get_reg_pnk_addr(
		GSI_EE_n_GSI_CH_k_DOORBELL_0, gsi_id, ee_idx, 0);
	out->ev_db_fwd_base =gsihal_get_reg_pnk_addr(
		GSI_EE_n_EV_CH_k_DOORBELL_0, gsi_id, ee_idx, 0);

	/* Create notifier for driver ready */
	work = kzalloc(sizeof(*work), GFP_KERNEL);

	if (work) {
		INIT_WORK(&work->work,
			  ecpri_dma_mhi_wq_notify_ready);
		work->ctx = ecpri_dma_mhi_client_ctx[idx];

		queue_work(ecpri_dma_mhi_client_ctx[idx]->wq, &work->work);
	} else {
		DMAERR("Allocation error in workqueue\n");
		ret = -ENOMEM;
		goto fail_queue_work_wq;
	}


	if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
		DMADBG_LOW("Done Physical \n");
	else
		DMADBG_LOW("Done Virtual ID %d \n", function.vf_id);

	return 0;

fail_set_state:
fail_queue_work_wq:
	destroy_workqueue(ecpri_dma_mhi_client_ctx[idx]->wq);
	kfree(work);
fail_memcpy_enable:
	ecpri_dma_mhi_memcpy_destroy(function);
fail_memcpy_init:
fail_create_wq:
	kfree(ecpri_dma_mhi_client_ctx[idx]);
	ecpri_dma_mhi_client_ctx[idx] = NULL;
fail_alloc_ctx:
fail_ready_state:
	return ret;
}

/**
 * ecpri_dma_mhi_client_dma_start() - Start DMA MHI engine
 * @function: function parameters
 * @params: pcie addresses for MHI
 *
 * This function is called by MHI client driver on MHI engine start for
 * handling MHI accelerated channels. This function is called after
 * mhi_dma_init() was called and can be called after MHI reset to restart
 * MHI engine. When this function returns device can move to M0 state.
 *
 * Return codes: 0	  : success
 *		 negative : error
 */
static int ecpri_dma_mhi_client_dma_start(
	struct mhi_dma_function_params function,
	struct mhi_dma_start_params* params)
{
	int idx;
	int ret;
	unsigned long flags;
	unsigned long gsi_dev_hdl;
	enum ecpri_dma_ees ee_idx;
	u32 gsi_id;
	const struct ecpri_dma_mhi_ee_gsi_tuple* func_map;

	if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
		DMADBG_LOW("Physical \n");
	else
		DMADBG_LOW("Virtual ID %d \n", function.vf_id);

	if (!params) {
		DMAERR("Null params args\n");
		return -EINVAL;
	}

	ret = ecpri_dma_mhi_get_function_context_index(function, &idx,
	ECPRI_DMA_MHI_DMA_CLIENT_CTX);
	if (ret != 0) {
		DMAERR("Function params are invalid, function"
			" type: %d, vf_id: %d\n",
			function.function_type, function.vf_id);
		return -EINVAL;
	}

	if (!ecpri_dma_mhi_client_ctx[idx]) {
		DMAERR("Context not initialized\n");
		return -EPERM;
	}

	spin_lock_irqsave(
		&ecpri_dma_mhi_client_ctx[idx]->lock, flags);
	if (ecpri_dma_mhi_client_ctx[idx]->state !=
		ECPRI_DMA_MHI_STATE_READY) {
		DMAERR("MHI Client for EE %d is not ready\n", idx);
		spin_unlock_irqrestore(
			&ecpri_dma_mhi_client_ctx[idx]->lock, flags);
		return -EPERM;
	}
	spin_unlock_irqrestore(
		&ecpri_dma_mhi_client_ctx[idx]->lock, flags);

	ecpri_dma_mhi_client_ctx[idx]->host_ctrl_addr =
		params->host_ctrl_addr;
	ecpri_dma_mhi_client_ctx[idx]->host_data_addr =
		params->host_data_addr;
	ecpri_dma_mhi_client_ctx[idx]->channel_context_array_addr =
		params->channel_context_array_addr;
	ecpri_dma_mhi_client_ctx[idx]->event_context_array_addr =
		params->event_context_array_addr;

	ret = ecpri_dma_get_gsi_dev_hdl(&gsi_dev_hdl);
	if (ret != 0) {
		DMAERR("Unable to retrieve the GSI device handle\n");
		return -EFAULT;
	}

	ret = ecpri_dma_mhi_get_function_mapping(function, &func_map);
	if (ret)
	{
		DMAERR("Unknown function");
		return ret;
	}
	ee_idx = func_map->ee_id;
	gsi_id = func_map->gsi_id;

	ret = gsi_write_device_scratch(gsi_dev_hdl, gsi_id, ee_idx,
		&ecpri_dma_mhi_client_ctx[idx]->dev_scratch);
	if (ret != 0) {
		DMAERR("Unable to write device scratch, idx: %d,"
			"device handle: %lu\n",
			idx, gsi_dev_hdl);
		return -EFAULT;
	}

	ret = ecpri_dma_mhi_set_state(
		ecpri_dma_mhi_client_ctx[idx],
		ECPRI_DMA_MHI_STATE_STARTED);
	if (ret != 0) {
		DMAERR("Unable to set state, State:%d\n",
			ECPRI_DMA_MHI_STATE_STARTED);
		return -EFAULT;
	}

	if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
		DMADBG_LOW("Done Physical \n");
	else
		DMADBG_LOW("Done Virtual ID %d \n", function.vf_id);
	return ret;
}

/**
 * ecpri_dma_mhi_client_read_write_host() - Perform read/write operation
 * between host and device.
 *
 * @ctx: the MHI Client context
 * @dir: The direction of the operation
 * @dev_addr: device address
 * @host_addr: host adress
 * @size: buffer size
 *
 * Function reads/writes from/to device by using ecpri_dma_mhi_dma_sync_memcpy
 * Return codes: 0: success
 *		-EFAULT: invalid platform
 *		-ENOMEM: allocating memory error
 *      -EINVAL: invalid addresses
 */
static int ecpri_dma_mhi_client_read_write_host(
	struct ecpri_dma_mhi_client_context* ctx,
	enum ecpri_dma_mhi_dma_dir dir, void *dev_addr,
	u64 host_addr, int size,
	struct mhi_dma_function_params function)
{
	int ret = 0;
	struct device* pdev;
	struct ecpri_dma_mem_buffer mem;

	pdev = ecpri_dma_get_pdev();
	host_addr = ECPRI_DMA_MHI_HOST_ADDR_COND(host_addr, ctx);

	mem.size = size;
	if (pdev) {
		mem.virt_base = dma_alloc_coherent(pdev, mem.size,
			&mem.phys_base, GFP_KERNEL);
	}
	else {
		DMAERR("Platform dev is not valid");
		return -EFAULT;
	}
	if (!mem.virt_base) {
		DMAERR("dma_alloc_coherent failed, DMA buff size %d\n", mem.size);
		return -ENOMEM;
	}

	if (dir == ECPRI_DMA_MHI_DMA_FROM_HOST) {
		ret = ecpri_dma_mhi_dma_sync_memcpy(mem.phys_base, host_addr,
			size, function);
		if (ret) {
			DMAERR("ecpri_dma_mhi_dma_sync_memcpy from host fail%d\n", ret);
			goto failed_memcopy;
		}
		memcpy(dev_addr, mem.virt_base, size);
	}
	else {
		memcpy(mem.virt_base, dev_addr, size);
		ret = ecpri_dma_mhi_dma_sync_memcpy(host_addr, mem.phys_base,
			size, function);
		if (ret) {
			DMAERR("ecpri_dma_mhi_dma_sync_memcpy to host fail %d\n", ret);
			goto failed_memcopy;
		}
	}

	dma_free_coherent(pdev, mem.size, mem.virt_base, mem.phys_base);
	return 0;

failed_memcopy:
	DMAERR("Failed memcpy\n");
	dma_free_coherent(pdev, mem.size, mem.virt_base, mem.phys_base);
	return ret;
}


/**
 * ecpri_dma_mhi_client_read_ch_ctx() - Reads channel context.
 *
 * @ctx: the MHI Client context
 * @channel: pointer to MHI channel context
 * @function: params
 *
 * Return codes: 0: success
 *		-EFAULT: invalid platform
 *		-ENOMEM: allocating memory error
 *      -EINVAL: invalid addresses
 */
static int ecpri_dma_mhi_client_read_ch_ctx(
	struct ecpri_dma_mhi_client_context* ctx,
	struct ecpri_dma_mhi_channel_ctx* channel,
	struct mhi_dma_function_params function)
{
	int ret = 0;

	ret = ecpri_dma_mhi_client_read_write_host(ctx, ECPRI_DMA_MHI_DMA_FROM_HOST,
		&channel->ch_ctx_host, channel->channel_context_addr,
		sizeof(channel->ch_ctx_host), function);
	if (ret != 0) {
		DMAERR("ecpri_dma_mhi_client_read_write_host failed,"
			" return code %d\n", ret);
		return ret;
	}

	channel->ev_context_addr = ctx->event_context_array_addr +
		(channel->ch_ctx_host.erindex) *
		sizeof(struct ecpri_dma_mhi_host_ev_ctx);

	ret = ecpri_dma_mhi_client_read_write_host(ctx, ECPRI_DMA_MHI_DMA_FROM_HOST,
		&channel->ev_ctx_host, channel->ev_context_addr,
		sizeof(channel->ev_ctx_host), function);
	if (ret != 0) {
		DMAERR("ecpri_dma_mhi_client_read_write_host failed,"
			" return code %d\n", ret);
		return ret;
	}

	return ret;
}

/**
 * ecpri_dma_mhi_client_connect_internal() - Connect pipe to DMA
 * and start corresponding MHI channel
 *
 * @channel: MHI channel context
 * @ctx: MHI Client context
 * @function: params
 *
 * This function is called by MHI client driver on MHI channel start.
 * This function is called after MHI engine was started.
 *
 * Return codes: 0	  : success
 *		 negative     : error
 */
static int ecpri_dma_mhi_client_connect_internal(
	struct ecpri_dma_mhi_channel_ctx* channel,
	struct ecpri_dma_mhi_client_context* ctx,
	struct mhi_dma_function_params function)
{
	int ret;
	union __packed gsi_channel_scratch ch_scratch;
	struct ecpri_dma_moderation_config mod_cfg;
	union __packed gsi_evt_scratch ev_scratch;
	const struct dma_gsi_ep_config *gsi_ep_cfg =
		&((*ecpri_dma_ctx->endp_map)[channel->endp_ctx->gsi_id]
		[channel->endp_ctx->endp_id]);

	/* For LTE DEST CHs configure RP moderation values */
	if (gsi_ep_cfg->lte_enable && gsi_ep_cfg->dir == ECPRI_DMA_ENDP_DIR_DEST &&
		channel->int_modc == 0 && channel->int_modt == 0)
	{
		channel->int_modc = ECPRI_DMA_MHI_LTE_DEST_MOD_RP_COUNTER;
		channel->int_modt = ECPRI_DMA_MHI_LTE_DEST_MOD_RP_TIMER;
		channel->is_mod_rp_only_enabled = true;
	}

	mod_cfg.moderation_counter_threshold = channel->int_modc;
	mod_cfg.moderation_timer_threshold = channel->int_modt;

	ret = ecpri_dma_alloc_endp(channel->endp_ctx->gsi_id,
		channel->endp_ctx->endp_id, channel->rlen,
		&mod_cfg, channel->is_over_pcie, NULL, false);
	if (ret != 0) {
		DMAERR("Failed to allocate endp %d\n", channel->endp_ctx->endp_id);
		goto fail_al_endp;
	}

	/*	Enable NotifyMCS for LTE DEST CHs, also set MOD_RP_ONLY incase original
		modc & modt are 0 */
	if (channel->endp_ctx->gsi_ep_cfg->lte_enable &&
		channel->endp_ctx->gsi_ep_cfg->dir == ECPRI_DMA_ENDP_DIR_DEST)
	{
		ev_scratch.mhi.enable_notify_mcs = 1;
		ev_scratch.mhi.moderate_update_rp_only =
			channel->is_mod_rp_only_enabled ? 1 : 0;
		ret = gsi_write_evt_ring_scratch(channel->endp_ctx->gsi_evt_ring_hdl,
			ev_scratch);
		if (ret != 0) {
			DMAERR("Unable to write event scratch,"
				"gsi event handle: %lu\n",
				channel->endp_ctx->gsi_evt_ring_hdl);
			goto fail_write_scratch;
		}
	}

	ch_scratch.mhi.is_over_pcie = channel->is_over_pcie;
	ch_scratch.mhi.skip_overflow_ev = !!channel->disable_overflow_event;
	ret = gsi_write_channel_scratch(channel->endp_ctx->gsi_chan_hdl,
		ch_scratch);
	if (ret != 0) {
		DMAERR("Unable to write channel scratch,"
			"gsi channel handle: %lu\n",
			channel->endp_ctx->gsi_chan_hdl);
		goto fail_write_scratch;
	}

	ret = ecpri_dma_start_endp(channel->endp_ctx);
	if (ret != 0) {
		DMAERR("Unable to start endp, endp ID: %d\n",
			channel->endp_ctx->endp_id);
		goto fail_start_endp;
	}

	ret = ecpri_dma_enable_dma_endp(channel->endp_ctx);
	if (ret != 0) {
		DMAERR("Failed to enable the channel, endp ID: %d\n",
			channel->endp_ctx->endp_id);
		goto fail_enable_endp;
	}

	channel->state = ECPRI_DMA_HW_MHI_CHANNEL_STATE_RUN;

	ret = ecpri_dma_mhi_client_read_write_host(
		ctx, ECPRI_DMA_MHI_DMA_TO_HOST, &channel->ch_ctx_host,
		channel->channel_context_addr +
		offsetof(struct ecpri_dma_mhi_host_ch_ctx, chstate),
		sizeof(channel->ch_ctx_host.chstate),
		function);
	if (ret != 0) {
		DMAERR("Unable to read write host\n");
		goto fail_read_write;
	}

	ret = 0;
	goto success;

fail_read_write:
fail_enable_endp:
	ret = ecpri_dma_stop_endp(channel->endp_ctx);
	if (ret != 0) {
		DMAERR("Unable to stop the endp, ENDP ID: %d\n",
			channel->endp_ctx->endp_id);
		ecpri_dma_assert();
	}
fail_start_endp:
	ret = ecpri_dma_dealloc_endp(channel->endp_ctx);
	if (ret != 0) {
		DMAERR("Unable to deallocate the endp, ENDP ID: %d\n",
			channel->endp_ctx->endp_id);
		ecpri_dma_assert();
	}
fail_write_scratch:
fail_al_endp:
success:
	return ret;
}

/**
 * ecpri_dma_mhi_dma_connect_endp() - Connect endp to DMA and start
 * corresponding MHI channel
 * @function: function parameters
 * @in: connect parameters
 * @clnt_hdl: [out] client handle for this endp
 *
 * This function is called by MHI client driver on MHI channel start.
 * This function is called after MHI engine was started.
 *
 * Return codes:    0 : success
 *		            negative : error
 */
static int ecpri_dma_mhi_dma_connect_endp(
	struct mhi_dma_function_params function,
	struct mhi_dma_connect_params* in, u32* clnt_hdl)
{
	int idx;
	int ret;
	unsigned long flags;
	enum ecpri_dma_ees ee_idx;
	struct ecpri_dma_mhi_channel_ctx* channel;
	struct ecpri_dma_endp_context* endp_ctx;
	u32 ch_idx = ECPRI_DMA_MHI_INVALID_CH_ID;
	const struct ecpri_dma_mhi_ee_gsi_tuple* func_map;

	if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
		DMADBG_LOW("Physical \n");
	else
		DMADBG_LOW("Virtual ID %d \n", function.vf_id);

	if (!in) {
		DMAERR("Null params args\n");
		return -EINVAL;
	}

	ret = ecpri_dma_mhi_get_function_context_index(function, &idx,
		ECPRI_DMA_MHI_DMA_CLIENT_CTX);
	if (ret != 0) {
		DMAERR("Function params are invalid, function type: %d, vf_id: %d\n",
			function.function_type, function.vf_id);
		return -EINVAL;
	}

	if (!ecpri_dma_mhi_client_ctx[idx]) {
		DMAERR("Context not initialized\n");
		return -EPERM;
	}

	spin_lock_irqsave(
		&ecpri_dma_mhi_client_ctx[idx]->lock, flags);

	if (ecpri_dma_mhi_client_ctx[idx]->state !=
		ECPRI_DMA_MHI_STATE_STARTED) {
		DMAERR("MHI Client for EE %d is not started\n", idx);
		spin_unlock_irqrestore(
			&ecpri_dma_mhi_client_ctx[idx]->lock, flags);
		return -EPERM;
	}

	spin_unlock_irqrestore(
		&ecpri_dma_mhi_client_ctx[idx]->lock, flags);

	ch_idx = in->channel_id - ecpri_dma_mhi_client_ctx[idx]->first_ch;
	if (ch_idx > ECPRI_DMA_MHI_MAX_HW_CHANNELS) {
		DMAERR("CH IDX out of bounds %d\n", ch_idx);
		return -EINVAL;
	}

	channel = &ecpri_dma_mhi_client_ctx[idx]->channels[ch_idx];
	if (channel->valid) {
		DMAERR("Channel already connected\n");
		return -EPERM;
	}

	channel->channel_context_addr =
		ecpri_dma_mhi_client_ctx[idx]->channel_context_array_addr +
		(in->channel_id * sizeof(struct ecpri_dma_mhi_host_ch_ctx));

	ret = ecpri_dma_mhi_client_read_ch_ctx(
		ecpri_dma_mhi_client_ctx[idx], channel,
		function);
	if (ret != 0) {
		DMAERR("Unable to read channel context\n");
		return -EPERM;
	}

	channel->channel_id = ch_idx;
	channel->event_id = channel->ch_ctx_host.erindex -
		ecpri_dma_mhi_client_ctx[idx]->first_ev;
	ret = ecpri_dma_mhi_get_function_mapping(function, &func_map);
	if (ret)
	{
		DMAERR("Unknown function");
		return ret;
	}
	ee_idx = func_map->ee_id;

	ret = ecpri_dma_mhi_get_endp_ctx(function, ch_idx,
		&endp_ctx);
	if (ret != 0) {
		DMAERR("endp_ctx, ee: %d, ch_id: %d\n",
			ee_idx, ch_idx);
		return ret;
	}

	channel->endp_ctx = endp_ctx;
	channel->endp_ctx->disable_overflow_event =
		channel->ch_ctx_host.disableovrflw;
	channel->disable_overflow_event = channel->ch_ctx_host.disableovrflw;
	channel->endp_ctx->is_endp_mhi_l2 = true;
	channel->endp_ctx->is_over_pcie =
		ecpri_dma_mhi_client_ctx[idx]->is_over_pcie;
	channel->is_over_pcie = channel->endp_ctx->is_over_pcie;
	channel->endp_ctx->l2_mhi_channel_ptr = channel;
	channel->msi_config =
		&ecpri_dma_mhi_client_ctx[idx]->msi_config;
	channel->rlen = channel->ch_ctx_host.rlen;
	channel->ev_rlen = channel->ev_ctx_host.rlen;
	channel->int_modt = channel->ev_ctx_host.intmodt;
	channel->int_modc = channel->ev_ctx_host.intmodc;

	ret = ecpri_dma_mhi_client_connect_internal(channel,
		ecpri_dma_mhi_client_ctx[idx], function);
	if (ret != 0) {
		DMAERR("GSI endp config not found, ee: %d, ch_id: %d\n",
			ee_idx, ch_idx);
		return ret;
	}

	idr_preload(GFP_KERNEL);

	spin_lock_irqsave(
		&ecpri_dma_mhi_client_ctx[idx]->idr_lock, flags);

	*(clnt_hdl) = idr_alloc(
		&ecpri_dma_mhi_client_ctx[idx]->idr,
		channel, ECPRI_DMA_MHI_MIN_VALID_HDL, 0, GFP_NOWAIT);

	spin_unlock_irqrestore(
		&ecpri_dma_mhi_client_ctx[idx]->idr_lock, flags);

	idr_preload_end();

	channel->valid = true;
	channel->clnt_hdl = *(clnt_hdl);

	if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
		DMADBG_LOW("Done Physical \n");
	else
		DMADBG_LOW("Done Virtual ID %d \n", function.vf_id);

	return ret;
}

/**
 * ecpri_dma_mhi_dma_disconnect_endp() - Disconnect endp from DMA and
 * reset corresponding MHI channel
 *
 * @clnt_hdl: client handle for this endp
 *
 * This function is called by DMA MHI client driver on MHI channel reset.
 * This function is called after MHI channel was started.
 * This function is doing the following:
 *	- Send command to GSI to reset corresponding MHI channel
 *
 * Return codes: 0		: success
 *		  negative		: error
 */
static int ecpri_dma_mhi_dma_disconnect_endp(
	struct mhi_dma_function_params function,
	struct mhi_dma_disconnect_params* in)
{
	int idx = 0, memcpy_idx = 0;
	int ret = 0;
	struct ecpri_dma_mhi_channel_ctx* channel = NULL;
	struct ecpri_dma_mhi_memcpy_context* memcpy_ctx = NULL;

	if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
		DMADBG_LOW("Physical \n");
	else
		DMADBG_LOW("Virtual ID %d \n", function.vf_id);

	ret = ecpri_dma_mhi_get_function_context_index(function, &idx,
		ECPRI_DMA_MHI_DMA_CLIENT_CTX);
	if (ret != 0) {
		DMAERR("Function params are invalid, function type: %d, vf_id: %d\n",
			function.function_type, function.vf_id);
		return -EINVAL;
	}

	/* Get channel context */
	spin_lock_bh(&ecpri_dma_mhi_client_ctx[idx]->idr_lock);
	channel = idr_find(&ecpri_dma_mhi_client_ctx[idx]->idr, in->clnt_hdl);
	spin_unlock_bh(&ecpri_dma_mhi_client_ctx[idx]->idr_lock);

	channel->state = ECPRI_DMA_HW_MHI_CHANNEL_STATE_DISABLE;
	channel->valid = false;
	channel->clnt_hdl = ECPRI_DMA_MHI_MIN_VALID_HDL;

	/* Write new state only if memcpy context is still available */
	ret = ecpri_dma_mhi_get_function_context_index(
		function, &memcpy_idx, ECPRI_DMA_MHI_DMA_MEMCPY_CTX);
	if (ret != 0) {
		DMAERR("Function params are invalid,"
			"function type: %d, vf_id: %d\n",
			function.function_type, function.vf_id);
		return -EINVAL;
	}

	memcpy_ctx = ecpri_dma_mhi_memcpy_ctx[memcpy_idx];
	if (memcpy_ctx) {
		ret = ecpri_dma_mhi_client_read_write_host(
			ecpri_dma_mhi_client_ctx[idx],
			ECPRI_DMA_MHI_DMA_TO_HOST, &channel->ch_ctx_host,
			channel->channel_context_addr +
			offsetof(struct ecpri_dma_mhi_host_ch_ctx, chstate),
			sizeof(channel->ch_ctx_host.chstate),
			function);
		if (ret != 0) {
			DMAERR("Unable to read write host\n");
			return -EPERM;
		}
	}

	/* Stop */
	ret = ecpri_dma_stop_endp(channel->endp_ctx);
	if (ret != 0) {
		DMAERR("Unable to stop the endp, ENDP ID: %d\n",
			channel->endp_ctx->endp_id);
		ecpri_dma_assert();
	}

	/* Reset */
	ret = ecpri_dma_reset_endp(channel->endp_ctx);
	if (ret != GSI_STATUS_SUCCESS) {
		DMAERR("Unable to reset endp, endp_id: %d\n",
			channel->endp_ctx->endp_id);
		return ret;
	}

	/* Dealloc */
	ret = ecpri_dma_dealloc_endp(channel->endp_ctx);
	if (ret != 0) {
		DMAERR("Unable to deallocate the endp, ENDP ID: %d\n",
			channel->endp_ctx->endp_id);
		ecpri_dma_assert();
	}

	DMADBG("client (ep: %d) disconnected\n",
		channel->endp_ctx->endp_id);

	return ret;
}

int ecpri_dma_mhi_client_ready_cb(void (*mhi_ready_cb)(void *user_data),
			      void *user_data)
{
	return ecpri_dma_register_ready_cb(mhi_ready_cb, user_data);
}

int ecpri_dma_mhi_client_update_mstate(struct mhi_dma_function_params function,
			  enum mhi_dma_mstate mstate_info)
{
	int ret = 0;
	int idx = 0;
	unsigned long flags;

	if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
		DMADBG_LOW("Physical \n");
	else
		DMADBG_LOW("Virtual ID %d \n", function.vf_id);

	/* Function params validity check */
	ret = ecpri_dma_mhi_get_function_context_index(function, &idx,
		ECPRI_DMA_MHI_DMA_CLIENT_CTX);
	if (ret != 0) {
		DMAERR("Function params are invalid,"
		       "function type: %d, vf_id: %d\n",
		       function.function_type, function.vf_id);
		return -EINVAL;
	}

	if (!ecpri_dma_mhi_client_ctx[idx]) {
		DMAERR("MHI ontext for IDX %d is not initialized\n", idx);
		return -EINVAL;
	}

	DMADBG("Req update mstate to %d\n", mstate_info);
	spin_lock_irqsave(&ecpri_dma_mhi_client_ctx[idx]->lock, flags);
	ecpri_dma_mhi_client_ctx[idx]->mhi_mstate = mstate_info;
	spin_unlock_irqrestore(&ecpri_dma_mhi_client_ctx[idx]->lock, flags);

	if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
		DMADBG_LOW("Done Physical \n");
	else
		DMADBG_LOW("Done Virtual ID %d \n", function.vf_id);

	return 0;
}

static dma_addr_t ecpri_dma_mhi_client_map_buffer(void* virt, size_t size,
	enum dma_data_direction dir)
{
	dma_addr_t phys;
	DMADBG_LOW("Begin\n");

	phys = dma_map_single(ecpri_dma_ctx->pdev, virt, size, dir);
	if (dma_mapping_error(ecpri_dma_ctx->pdev, phys)) {
		DMAERR("failed to do dma map.\n");
		ecpri_dma_assert();
	}

	return phys;
}

static void ecpri_dma_mhi_client_unmap_buffer(dma_addr_t phys, size_t size,
	enum dma_data_direction dir)
{
	DMADBG_LOW("Begin\n");
	dma_unmap_single(ecpri_dma_ctx->pdev, phys, size, dir);
}

static void *ecpri_dma_mhi_client_alloc_buffer(size_t size,
	dma_addr_t* phys, gfp_t gfp)
{
	DMADBG_LOW("Begin\n");
	return  dma_alloc_coherent(ecpri_dma_ctx->pdev, size, phys, gfp);
}

static void ecpri_dma_mhi_client_free_buffer(size_t size, void* virt,
	dma_addr_t phys)
{
	DMADBG_LOW("Begin\n");

	dma_free_coherent(ecpri_dma_ctx->pdev, size, virt, phys);
}

static int ecpri_dma_mhi_client_resume(struct mhi_dma_function_params function)
{
	if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
		DMADBG_LOW("Physical \n");
	else
		DMADBG_LOW("Virtual ID %d \n", function.vf_id);

	return -EPERM;
}

static int ecpri_dma_mhi_client_suspend(
	struct mhi_dma_function_params function, bool force)
{
	if (function.function_type == MHI_DMA_FUNCTION_TYPE_PHYSICAL)
		DMADBG_LOW("Physical \n");
	else
		DMADBG_LOW("Virtual ID %d \n", function.vf_id);

	return -EPERM;
}

/**
 * ecpri_dma_mhi_destroy() - Destroy MHI DMA
 *
 * This function is called by MHI client driver on MHI reset to destroy all DMA
 * MHI resources.
 *
 */
static void ecpri_dma_mhi_destroy(
	struct mhi_dma_function_params function)
{
	int idx, i;
	int ret;
	struct mhi_dma_disconnect_params disconnect_params = { 0 };
	const struct ecpri_dma_mhi_ee_gsi_tuple* func_map;

	DMADBG("Function type: %d, vf_id: %d\n",
		function.function_type, function.vf_id);

	ret = ecpri_dma_mhi_get_function_context_index(
		function, &idx, ECPRI_DMA_MHI_DMA_CLIENT_CTX);
	if (ret != 0) {
		DMAERR("Function params are invalid,"
			"function type: %d, vf_id: %d\n",
			function.function_type, function.vf_id);
		return;
	}

	if (!ecpri_dma_mhi_client_ctx[idx]) {
		DMAERR("Context is not initialized\n");
		return;
	}

	/* Disconnect all HW CHs */
	for (i = 0; i < ECPRI_DMA_MHI_MAX_HW_CHANNELS; i++) {
		if (ecpri_dma_mhi_client_ctx[idx]->channels[i].valid) {
			disconnect_params.clnt_hdl = ecpri_dma_mhi_client_ctx[idx]->
				channels[i].clnt_hdl;
			ret = ecpri_dma_mhi_dma_disconnect_endp(function,
				&disconnect_params);
			if (ret != 0) {
				DMAERR("Failed to disconnect MHI HW CH %d vf_id %d\n", i,
					function.vf_id);
				ecpri_dma_assert();
			}
		}
	}

	ret = ecpri_dma_mhi_get_function_mapping(function, &func_map);
	if (ret) {
		DMAERR("Unknown function");
		return;
	}

	ret = gsi_dealloc_all_evt_rings(func_map->gsi_id, func_map->ee_id);
	if (ret) {
		DMAERR("Events deallocation failed"
			"function type : % d, vf_id : % d\n",
			function.function_type, function.vf_id);
		return;
	}

	ret = ecpri_dma_mhi_dma_memcpy_disable(function);
	if (ret != 0) {
		DMAERR("Failed to disable memcpy\n");
		ecpri_dma_assert();
	}

	ecpri_dma_mhi_memcpy_destroy(function);

	idr_destroy(&ecpri_dma_mhi_client_ctx[idx]->idr);

	// TODO: Destroy debugfs

	destroy_workqueue(ecpri_dma_mhi_client_ctx[idx]->wq);

	ecpri_dma_mhi_client_ctx[idx]->notify_cb = NULL;
	ecpri_dma_mhi_client_ctx[idx]->user_data = NULL;
	ecpri_dma_mhi_client_ctx[idx]->msi_config.addr_low = 0;
	ecpri_dma_mhi_client_ctx[idx]->msi_config.addr_hi = 0;
	ecpri_dma_mhi_client_ctx[idx]->msi_config.data = 0;
	ecpri_dma_mhi_client_ctx[idx]->msi_config.mask = 0;
	ecpri_dma_mhi_client_ctx[idx]->mmio_addr = 0;
	ecpri_dma_mhi_client_ctx[idx]->first_ch = 0;
	ecpri_dma_mhi_client_ctx[idx]->first_ev = 0;
	ecpri_dma_mhi_client_ctx[idx]->is_over_pcie = false;
	ecpri_dma_mhi_client_ctx[idx]->mhi_mstate =
		MHI_DMA_STATE_M_MAX;
	ecpri_dma_mhi_client_ctx[idx]->state =
		ECPRI_DMA_MHI_STATE_INVALID;
	ecpri_dma_mhi_client_ctx[idx]->dev_scratch
		.mhi_base_chan_idx_valid = false;
	ecpri_dma_mhi_client_ctx[idx]->dev_scratch
		.mhi_base_chan_idx = 0;

	kfree(ecpri_dma_mhi_client_ctx[idx]);
	ecpri_dma_mhi_client_ctx[idx] = NULL;
	DMADBG("DMA MHI was reset, ready for re-init\n");

	return;
}

/* API exposed structure */
const struct mhi_dma_ops ecpri_dma_mhi_driver_ops = {
	.mhi_dma_register_ready_cb = ecpri_dma_mhi_client_ready_cb,
	.mhi_dma_init = ecpri_dma_mhi_client_init,
	.mhi_dma_start = ecpri_dma_mhi_client_dma_start,
	.mhi_dma_connect_endp = ecpri_dma_mhi_dma_connect_endp,
	.mhi_dma_disconnect_endp = ecpri_dma_mhi_dma_disconnect_endp,
	.mhi_dma_destroy = ecpri_dma_mhi_destroy,
	.mhi_dma_memcpy_init = ecpri_dma_mhi_memcpy_init,
	.mhi_dma_memcpy_destroy = ecpri_dma_mhi_memcpy_destroy,
	.mhi_dma_sync_memcpy = ecpri_dma_mhi_dma_sync_memcpy,
	.mhi_dma_async_memcpy = ecpri_dma_mhi_dma_async_memcpy,
	.mhi_dma_memcpy_enable = ecpri_dma_mhi_dma_memcpy_enable,
	.mhi_dma_memcpy_disable = ecpri_dma_mhi_dma_memcpy_disable,
	.mhi_dma_map_buffer = ecpri_dma_mhi_client_map_buffer,
	.mhi_dma_unmap_buffer = ecpri_dma_mhi_client_unmap_buffer,
	.mhi_dma_alloc_buffer = ecpri_dma_mhi_client_alloc_buffer,
	.mhi_dma_free_buffer = ecpri_dma_mhi_client_free_buffer,
	.mhi_dma_update_mstate = ecpri_dma_mhi_client_update_mstate,
	.mhi_dma_resume = ecpri_dma_mhi_client_resume,
	.mhi_dma_suspend = ecpri_dma_mhi_client_suspend,
};

int ecpri_dma_mhi_provide_ops()
{
	return mhi_dma_provide_ops(&ecpri_dma_mhi_driver_ops);
}

int ecpri_dma_mhi_get_vf_id(struct ecpri_dma_mhi_ee_gsi_tuple *ee_gsi_tuple)
{
	int hw_ver = ECPRI_DMA_GET_CTX_HW_VER();
	enum ecpri_dma_vm_ids vf_id;
	int max_vf_id;

	/* Validate input*/
	if (NULL == ee_gsi_tuple)
		return -EINVAL;

	/* Get max vf_id by HW version version */
	if (hw_ver == ECPRI_HW_V1_0)
		max_vf_id = ECPRI_DMA_VM_IDS_MAX_V1;
	else
		max_vf_id = ECPRI_DMA_VM_IDS_MAX;

	/* Find VF id*/
	for (vf_id = ECPRI_DMA_VM_IDS_VM0; vf_id < max_vf_id; vf_id++)
		if ((ecpri_dma_mhi_function_map[vf_id].ee_id == ee_gsi_tuple->ee_id) &&
			(ecpri_dma_mhi_function_map[vf_id].gsi_id == ee_gsi_tuple->gsi_id))
				break;

	if (max_vf_id == vf_id)
		return ECPRI_DMA_VM_IDS_NONE;
	else
		return vf_id;
}
