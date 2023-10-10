/*
 * SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include <linux/dmapool.h>
#include <linux/list.h>
#include <linux/genalloc.h>
#include <linux/io.h>
#include <linux/ratelimit.h>
#include <linux/msm_gsi.h>
#include <linux/mhi_dma.h>
#include "ecpri_dma_i.h"
#include "dmahal.h"
#include "gsi.h"
#include "ecpri_dma_dp.h"

int ecpri_dma_dp_exception_replenish(struct ecpri_dma_endp_context *endp,
				  u32 num_to_replenish)
{
	int ret = 0;
	int i = 0;
	u32 num_of_pkts_remain = num_to_replenish;
	u32 num_of_pkts_to_send = num_to_replenish;
	bool commit_transmit = false;

	if (!endp || !endp->valid || !endp->gsi_ep_cfg->is_exception) {
		DMAERR("Exception ENDP isn't valid");
		return -EINVAL;
	}

	for (i = 0; i < num_of_pkts_remain; i++)
	{
		memset(ecpri_dma_ctx->
			exception_ctx.exception_buffs[(i +
			ecpri_dma_ctx->exception_ctx.exception_pkt_idx) %
			ECPRI_DMA_EXCEPTION_RING_SIZE].virt_base, 0,
			ECPRI_DMA_DP_EXCEPTION_BUFF_SIZE);

		ecpri_dma_ctx->
			exception_ctx.exception_buffs[(i +
				ecpri_dma_ctx->exception_ctx.exception_pkt_idx) %
				ECPRI_DMA_EXCEPTION_RING_SIZE].size =
				ECPRI_DMA_DP_EXCEPTION_BUFF_SIZE;
	}

	while (num_of_pkts_remain) {
		if (num_of_pkts_remain > ECPRI_DMA_DP_MAX_DESC) {
			num_of_pkts_to_send = ECPRI_DMA_DP_MAX_DESC;
			commit_transmit = false;
		}
		else {
			num_of_pkts_to_send = num_of_pkts_remain;
			commit_transmit = true;
		}

		if (num_of_pkts_to_send + ecpri_dma_ctx->exception_ctx.exception_pkt_idx >
			ECPRI_DMA_EXCEPTION_RING_SIZE)
		{
			num_of_pkts_to_send = ECPRI_DMA_EXCEPTION_RING_SIZE -
				ecpri_dma_ctx->exception_ctx.exception_pkt_idx;
			commit_transmit = false;
		}

		ret = ecpri_dma_dp_transmit(endp,
			&ecpri_dma_ctx->exception_ctx.exception_pkts_arr[
				ecpri_dma_ctx->exception_ctx.exception_pkt_idx],
			num_of_pkts_to_send, commit_transmit);
		if (ret) {
			DMAERR("failed to replenish exception endp\n");
			ecpri_dma_assert();
		}
		ecpri_dma_ctx->exception_ctx.exception_pkt_idx =
			(ecpri_dma_ctx->exception_ctx.exception_pkt_idx + num_of_pkts_to_send) %
			ECPRI_DMA_EXCEPTION_RING_SIZE;
		num_of_pkts_remain -= num_of_pkts_to_send;
	}

	return 0;
}

static void ecpri_dma_dump_packet(char *buf, int len)
{
	int payload_len = len - 14;
	int num_dumps;
	int i;
	int index = 0;

	DMADBG("dumping packet of length: %d\n", len);

	DMADBG("packet dest MAC addr: %x:%x:%x:%x:%x:%x\n", buf[0], buf[1],
		   buf[2], buf[3], buf[4], buf[5]);
	DMADBG("packet src MAC addr: %x:%x:%x:%x:%x:%x\n", buf[6], buf[7],
		   buf[8], buf[9], buf[10], buf[11]);
	DMADBG("packet EtherType: %x:%x\n", buf[12], buf[13]);

	DMADBG("dumping packet payload length: %d\n", payload_len);
	if (payload_len > 0) {
		num_dumps = payload_len / 8;

		if (num_dumps > 8) {
			num_dumps = 8;
		}

		index = 14;
		for (i = 0; i < num_dumps; ++i) {
			DMADBG("Packet: %d, %x:%x:%x:%x:%x:%x:%x:%x\n", i,
				   buf[index + 0], buf[index + 1],
				   buf[index + 2], buf[index + 3],
				   buf[index + 4], buf[index + 5],
				   buf[index + 6], buf[index + 7]);
			index += 8;
			if (index + 8 > len) {
				break;
			}
		}
	}
}

void ecpri_dma_dp_tasklet_exception_notify(unsigned long data)
{
	int i = 0;
	int ret = 0;
	struct ecpri_dma_pkt_completion_wrapper *exception_pkts_arr;
	struct ecpri_dma_pkt_completion_wrapper **exception_pkts;
	u32 actual_num = 0, actual_buff_num = 0;
	struct ecpri_dma_endp_context *endp;
	unsigned long flags;

	endp = (struct ecpri_dma_endp_context *)data;

	if (unlikely(!endp || !endp->gsi_ep_cfg->is_exception)) {
		DMAERR("Exception pkt received on non exception endp\n");
		ecpri_dma_assert();
	}

	if (unlikely(atomic_read(&endp->disconnect_in_progress))) {
		DMAERR("ENDP disconnect in progress\n");
		return;
	}

	if (unlikely(!endp->valid)) {
		DMAERR("ENDP in non-valid state\n");
		return;
	}

	exception_pkts_arr = kzalloc(
		sizeof(struct ecpri_dma_pkt_completion_wrapper) *
				ECPRI_DMA_DP_EXCEPTION_BUDGET *
				ECPRI_DMA_DP_EXCEPTION_FH_RX_MAX_CHAIN, GFP_NOWAIT);
	ecpri_dma_assert_on(!exception_pkts_arr);

	exception_pkts = kzalloc(
		sizeof(struct ecpri_dma_pkt_completion_wrapper*) *
				ECPRI_DMA_DP_EXCEPTION_BUDGET *
				ECPRI_DMA_DP_EXCEPTION_FH_RX_MAX_CHAIN, GFP_NOWAIT);
	ecpri_dma_assert_on(!exception_pkts);

	for (i = 0; i < ECPRI_DMA_DP_EXCEPTION_BUDGET *
		ECPRI_DMA_DP_EXCEPTION_FH_RX_MAX_CHAIN ;i++) {
		exception_pkts[i] = &exception_pkts_arr[i];
	}

	spin_lock_irqsave(&ecpri_dma_ctx->exception_ctx.exception_spinlock, flags);
	/* Poll Exceptions & Increase exception statistics
		actual_num is in packets, need to check for jumbo packets */
	ret = ecpri_dma_dp_poll(endp, ECPRI_DMA_DP_EXCEPTION_BUDGET,
				   exception_pkts, &actual_num);
	if (ret) {
		DMAERR("Exception endp polling failed\n");
		kfree(exception_pkts_arr);
		kfree(exception_pkts);
		ecpri_dma_assert();
	}
	ecpri_dma_ctx->exception_ctx.exception_stats.num_of_pkts_received +=
		actual_num;

	/* Credits have only one buffer so no need to check num_of_buffs */
	i = 0;
	actual_buff_num = 0;
	while (i < actual_num) {
		DMAERR("Got exception packet with status %d, dumping\n",
		       exception_pkts[actual_buff_num]->status_code);
		ecpri_dma_ctx->exception_ctx.exception_stats.
			exception_status_statistics[
			exception_pkts[actual_buff_num]->status_code]++;
		//TODO: change from dump to terminal to dump to array

		/* Each packet may have more than one buffer, need to check for EOT */
		do {
			ecpri_dma_dump_packet(
				exception_pkts[actual_buff_num]->pkt->buffs[0]->virt_base,
				exception_pkts[actual_buff_num]->pkt->buffs[0]->size);
			ecpri_dma_ctx->exception_ctx.exception_stats.
				num_of_bytes_received +=
				exception_pkts[actual_buff_num]->pkt->buffs[0]->size;
			actual_buff_num++;
		} while (exception_pkts[actual_buff_num]->comp_code !=
			ECPRI_DMA_COMPLETION_CODE_EOT);
		i++;
	}

	if(actual_num == 0) {
		/* No more packets to poll, change back to IRQ mode */
		ret = ecpri_dma_set_endp_mode(endp, ECPRI_DMA_NOTIFY_MODE_IRQ);
		if (ret) {
			DMAERR("Setting exception endp to IRQ mode failed\n");
			kfree(exception_pkts_arr);
			kfree(exception_pkts);
			ecpri_dma_assert();
		}
	} else {
		ret = ecpri_dma_dp_exception_replenish(endp, actual_buff_num);
		if (ret) {
			DMAERR("Failed to replenish exception endp\n");
			kfree(exception_pkts_arr);
			kfree(exception_pkts);
			ecpri_dma_assert();
		}

		/* There might be more packet to poll, rescheduale tasklet */
		tasklet_schedule(&endp->tasklet);
	}

	spin_unlock_irqrestore(&ecpri_dma_ctx->exception_ctx.exception_spinlock, flags);
	kfree(exception_pkts_arr);
	kfree(exception_pkts);
}

void ecpri_dma_dp_exception_endp_notify_completion(
	struct ecpri_dma_endp_context *endp,
	struct ecpri_dma_pkt_completion_wrapper **comp_pkt,
	u32 num_of_completed)
{
	int ret = 0;
	if (!endp || !endp->valid || !endp->gsi_ep_cfg->is_exception) {
		DMAERR("Exception pkt received on non exception endp");
		ecpri_dma_assert();
	}

	ret = ecpri_dma_set_endp_mode(endp, ECPRI_DMA_NOTIFY_MODE_POLL);
	if(ret) {
		DMAERR("Setting exception endp to POLL mode failed\n");
		ecpri_dma_assert();
	}

	tasklet_schedule(&endp->tasklet);
}

//TODO: add documentation
static int ecpri_dma_dp_gen_gsi_xfer(struct ecpri_dma_pkt *pkt,
	struct gsi_xfer_elem *gsi_xfer,
	struct ecpri_dma_outstanding_pkt_wrapper *pkt_wrapper,
	u32 *total_bytes, struct ecpri_dma_dynamic_vf_params *vf_params)
{
	int i = 0;

	for (i = 0; i < pkt->num_of_buffers; i++) {
		/* Set gsi_xfer fields */
		gsi_xfer[i].addr = pkt->buffs[i]->phys_base;
		gsi_xfer[i].len = pkt->buffs[i]->size;
		gsi_xfer[i].type = GSI_XFER_ELEM_DATA;
		gsi_xfer[i].flags |= GSI_XFER_FLAG_BEI;

		/* Set EOT or CHAIN bits as appropriate */
		//TODO: Implement event moderation by not setting EOT flag here
		if (i == pkt->num_of_buffers - 1) {
			gsi_xfer[i].flags |= GSI_XFER_FLAG_EOT;
			gsi_xfer[i].xfer_user_data = (void*)pkt_wrapper;
		}
		else
			gsi_xfer[i].flags |= GSI_XFER_FLAG_CHAIN;

		if (vf_params->vf_override) {
			gsi_xfer[i].vf_override = vf_params->vf_override;
			gsi_xfer[i].vf_valid = vf_params->vf_valid;
			gsi_xfer[i].vf_id = vf_params->vf_id;
		}

		*total_bytes += pkt->buffs[i]->size;
	}

	return 0;
}

/**
 * ecpri_dma_tasklet_rx_done() - this function will be (eventually)
 * called when a Rx operation is complete
 * @data: user pointer point to the ecpri_dma_endp_context
 *
 * Will be called in deferred context.
 * - Notify client for Rx completion
 */
void ecpri_dma_tasklet_rx_done(unsigned long data)
{
	struct ecpri_dma_endp_context *endp;

	endp = (struct ecpri_dma_endp_context *)data;
	if (unlikely(!endp)) {
		DMAERR("NULL ENDP ptr in tasklet\n");
		ecpri_dma_assert();
	}

	if (unlikely(atomic_read(&endp->disconnect_in_progress))) {
		DMAERR("ENDP disconnect in progress\n");
		return;
	}

	if (unlikely(!endp->valid)) {
		DMAERR("ENDP in non-valid state\n");
		return;
	}

	DMADBG_LOW("Notify Rx ENDP %d on completion\n", endp->endp_id);
	/* Notify client on Rx completion */
	if (endp->notify_comp != NULL) {
		endp->notify_comp(endp, NULL, 0);
	}
	else {
		DMADBG("ENDP %d doesn't have notify function\n",
			endp->endp_id);
	}
}

/**
 * ecpri_dma_tasklet_tx_poll_irq() - this function will be (eventually)
 * called when a Tx operation is complete
 * @data: user pointer point to the ecpri_dma_endp_context
 *
 * Will be called in deferred context.
 * - call client callback to notify on tx completion
 */
void ecpri_dma_tasklet_tx_poll_irq(unsigned long data)
{
	struct ecpri_dma_endp_context *endp =
		(struct ecpri_dma_endp_context*)data;

	if (unlikely(!endp)) {
		DMAERR("NULL ENDP ptr in tasklet\n");
		ecpri_dma_assert();
	}

	if (unlikely(atomic_read(&endp->disconnect_in_progress))) {
		DMAERR("ENDP disconnect in progress\n");
		return;
	}

	if (unlikely(!endp->valid)) {
		DMAERR("ENDP in non-valid state\n");
		return;
	}

	/* Notify client on Tx completion */
	if (endp->notify_comp != NULL) {
		endp->notify_comp(endp, NULL, 0);
	}
	else {
		DMADBG("ENDP %d doesn't have notify function\n",
			endp->endp_id);
	}
}

/**
 * ecpri_dma_tasklet_transmit_done() - this function will be (eventually)
 * called when a Tx operation is complete
 * @data: user pointer point to the ecpri_dma_endp_context
 *
 * Will be called in deferred context.
 * - iterate over all completed packets and unmap the buffers using the SMMU
 * - invoke the callback supplied by the client who transmited the packets
 * - remove all the tx packet wrappers from the endp outstanding packets list
 */
void ecpri_dma_tasklet_transmit_done(unsigned long data)
{
	struct ecpri_dma_endp_context *endp;
	struct ecpri_dma_outstanding_pkt_wrapper *curr_pkt_wrapper = NULL;
	struct ecpri_dma_pkt_completion_wrapper **comp_pkts_arr;
	struct ecpri_dma_pkt *pkt;
	struct list_head *pos, *n;
	u32 num_of_completed = 0, completed_pkt_index = 0;
	int i = 0;
	unsigned long flags;

	endp = (struct ecpri_dma_endp_context *)data;

	if (unlikely(!endp)) {
		DMAERR("NULL ENDP ptr in tasklet\n");
		ecpri_dma_assert();
	}

	if (unlikely(atomic_read(&endp->disconnect_in_progress))) {
		DMAERR("ENDP disconnect in progress\n");
		return;
	}

	if (unlikely(!endp->valid)) {
		DMAERR("ENDP in non-valid state\n");
		return;
	}

	num_of_completed = atomic_read(&endp->xmit_eot_cnt);
	if (num_of_completed == 0)
		return;

	comp_pkts_arr =
		kzalloc(sizeof(struct ecpri_dma_pkt_completion_wrapper *) *
				num_of_completed, GFP_NOWAIT);
	if (!comp_pkts_arr) {
		DMAERR("Cannot allocate completed packets array\n");
		ecpri_dma_assert();
	}

	spin_lock_irqsave(&endp->spinlock, flags);

	if(!list_empty(&endp->outstanding_pkt_list))
		curr_pkt_wrapper = list_first_entry(&endp->outstanding_pkt_list,
			struct ecpri_dma_outstanding_pkt_wrapper, link);

	while (!list_empty(&endp->outstanding_pkt_list) &&
		completed_pkt_index < num_of_completed &&
		curr_pkt_wrapper &&
		curr_pkt_wrapper->xfer_done &&
		atomic_add_unless(&endp->xmit_eot_cnt, -1, 0)) {

		curr_pkt_wrapper = list_first_entry(&endp->outstanding_pkt_list,
			struct ecpri_dma_outstanding_pkt_wrapper, link);

		/* Perform unmapping using SMMU */
		pkt = curr_pkt_wrapper->comp_pkt.pkt;

		/* Unmapping is only required for ETH M2S ENDPs */
		if (endp->gsi_ep_cfg->stream_mode != ECPRI_DMA_ENDP_STREAM_MODE_M2M)
		{
			for (i = 0; i < pkt->num_of_buffers; i++) {
				dma_unmap_single(ecpri_dma_ctx->pdev,
					pkt->buffs[i]->phys_base,
					pkt->buffs[i]->size, DMA_TO_DEVICE);
				pkt->buffs[i]->phys_base = 0;
			}
		}

		/*	Remove completed packet wrapper from endp list and prepare
				the completed packets array for the client */
		comp_pkts_arr[completed_pkt_index] = &curr_pkt_wrapper->comp_pkt;
		list_move_tail(&curr_pkt_wrapper->link, &endp->completed_pkt_list);

		endp->curr_outstanding_num--;
		endp->curr_completed_num++;
		completed_pkt_index++;
	}

	spin_unlock_irqrestore(&endp->spinlock, flags);

	if(completed_pkt_index == 0)
	{
		kfree(comp_pkts_arr);
		return;
	}

	/* Notify client on all completed packets */
	if (endp->notify_comp != NULL) {
		endp->notify_comp(endp, comp_pkts_arr, completed_pkt_index);
	}
	else {
		DMADBG("ENDP %d doesn't have notify function\n",
			endp->endp_id);
	}

	/* Free allocated entry */
	spin_lock_irqsave(&endp->spinlock, flags);
	list_for_each_safe(pos, n, &endp->completed_pkt_list)
	{
		curr_pkt_wrapper = list_entry(pos,
			struct ecpri_dma_outstanding_pkt_wrapper,
			link);
		if (endp->avail_outstanding_pkts >=
		    ECPRI_DMA_OUTSTANDING_PKTS_CACHE_MAX_THRESHOLD) {
			list_del(&curr_pkt_wrapper->link);
			kmem_cache_free(endp->available_outstanding_pkts_cache,
				curr_pkt_wrapper);
		} else {
			list_move_tail(&curr_pkt_wrapper->link,
				&endp->available_outstanding_pkts_list);
			endp->avail_outstanding_pkts++;
		}
		endp->curr_completed_num--;
	}
	spin_unlock_irqrestore(&endp->spinlock, flags);

	kfree(comp_pkts_arr);
}

int ecpri_dma_set_endp_mode(struct ecpri_dma_endp_context *endp,
	enum ecpri_dma_notify_mode mode)
{
	int ret = 0;

	if (!endp || !endp->valid)
		return -EINVAL;

	switch (mode) {
	case ECPRI_DMA_NOTIFY_MODE_IRQ:
		ret = gsi_config_channel_mode(endp->gsi_chan_hdl,
			GSI_CHAN_MODE_CALLBACK);
		if ((ret != GSI_STATUS_SUCCESS) &&
			(ret != -GSI_STATUS_UNSUPPORTED_OP)) {
			DMAERR("Failed to switch to intr mode %d ch_id %d\n",
				endp->curr_polling_state, endp->gsi_chan_hdl);
			return ret;
		}
		break;
	case ECPRI_DMA_NOTIFY_MODE_POLL:
		ret = gsi_config_channel_mode(endp->gsi_chan_hdl,
			GSI_CHAN_MODE_POLL);
		if ((ret != GSI_STATUS_SUCCESS) &&
			(ret != -GSI_STATUS_UNSUPPORTED_OP)) {
			DMAERR("Failed to switch to poll mode %d ch_id %d\n",
				endp->curr_polling_state, endp->gsi_chan_hdl);
			return ret;
		}
		break;
	default:
		DMAERR("Invalid ENDP Notify mode received\n");
		return -EINVAL;
		break;
	}
	atomic_set(&endp->curr_polling_state, mode);

	return 0;
}

int ecpri_dma_get_endp_mode(struct ecpri_dma_endp_context *endp,
	enum ecpri_dma_notify_mode *mode)
{
	if (!endp || !endp->valid)
		return -EINVAL;

	*mode = atomic_read(&endp->curr_polling_state);

	return 0;
}

void ecpri_dma_dp_rx_comp_hdlr(struct gsi_chan_xfer_notify *notify)
{
	struct ecpri_dma_outstanding_pkt_wrapper *comp_pkt;
	struct ecpri_dma_endp_context *endp;
	int ret = 0;

	DMADBG_LOW("event code %d received for CH %d\n", notify->evt_id,
		notify->chid);

	switch (notify->evt_id) {
	case GSI_CHAN_EVT_EOT:
	case GSI_CHAN_EVT_OVERFLOW:
	case GSI_CHAN_EVT_EOB:
		comp_pkt = notify->xfer_user_data;
		endp = comp_pkt->endp;

		ret = ecpri_dma_set_endp_mode(endp, ECPRI_DMA_NOTIFY_MODE_POLL);
		if (ret) {
			DMAERR("Setting ENDP %d endp to POLL mode failed\n",endp->endp_id);
			ecpri_dma_assert();
		}

		/* Notify client on Rx completion */
		tasklet_schedule(&endp->tasklet);
		break;
	default:
		DMAERR("received unexpected event code %d on CH %d\n", notify->evt_id,
			notify->chid);
	}
}

void ecpri_dma_dp_tx_comp_poll_irq_hdlr(struct gsi_chan_xfer_notify *notify)
{
	struct ecpri_dma_outstanding_pkt_wrapper *comp_pkt;
	struct ecpri_dma_endp_context *endp;
	int ret = 0;

	DMADBG_LOW("event code %d received for CH %d\n", notify->evt_id,
		   notify->chid);

	switch (notify->evt_id) {
	case GSI_CHAN_EVT_EOT:
	case GSI_CHAN_EVT_EOB:
		comp_pkt = notify->xfer_user_data;
		endp = comp_pkt->endp;

		ret = ecpri_dma_set_endp_mode(endp, ECPRI_DMA_NOTIFY_MODE_POLL);
		if (ret) {
			DMAERR("Setting ENDP %d endp to POLL mode failed\n", endp->endp_id);
			ecpri_dma_assert();
		}

		tasklet_schedule(&endp->tasklet);
		break;
	default:
		DMAERR("received unexpected event code %d on CH %d\n", notify->evt_id,
			notify->chid);
	}
}

void ecpri_dma_dp_tx_comp_hdlr(struct gsi_chan_xfer_notify *notify)
{
	struct ecpri_dma_outstanding_pkt_wrapper *comp_pkt;
	struct ecpri_dma_endp_context *endp;

	DMADBG_LOW("event code %d received for CH %d\n", notify->evt_id,
		   notify->chid);

	switch (notify->evt_id) {
	case GSI_CHAN_EVT_EOT:
	case GSI_CHAN_EVT_EOB:
		comp_pkt = notify->xfer_user_data;
		endp = comp_pkt->endp;

		comp_pkt->xfer_done = true;
		atomic_inc(&endp->xmit_eot_cnt);

		tasklet_schedule(&endp->tasklet);
		break;
	default:
		DMAERR("received unexpected event code %d on CH %d\n", notify->evt_id,
			notify->chid);
	}
}

int ecpri_dma_dp_poll(struct ecpri_dma_endp_context *endp, u32 budget,
	struct ecpri_dma_pkt_completion_wrapper **pkts, u32 *actual_num)
{
	int ret = 0, i = 0, j = 0;
	u32 rem_budget = budget, num_of_buff = 0;
	u32 curr_iter_num_of_pkts = 0;
	bool is_poll_empty = false;
	struct ecpri_dma_outstanding_pkt_wrapper *curr_pkt_wrapper;
	struct list_head *pos, *n;
	struct gsi_chan_xfer_notify notify[ECPRI_DMA_DP_MAX_DESC];
	unsigned long flags;
	int dma_dir;

	if (!endp || !endp->valid || !budget || !pkts || !actual_num) {
		DMAERR("Invalid parameters\n");
		return -EINVAL;
	}

	if (endp->gsi_ep_cfg->dir == ECPRI_DMA_ENDP_DIR_SRC)
		dma_dir = DMA_TO_DEVICE;
	else
		dma_dir = DMA_FROM_DEVICE;

	spin_lock_irqsave(&endp->spinlock, flags);
	/* Begin polling the GSI event */
	while (rem_budget && !is_poll_empty) {
		ret = gsi_poll_n_channel(endp->gsi_chan_hdl, notify,
					rem_budget < ECPRI_DMA_DP_MAX_DESC ?
					rem_budget : ECPRI_DMA_DP_MAX_DESC, &num_of_buff);

		if (ret == GSI_STATUS_POLL_EMPTY) {
			is_poll_empty = true;
		} else if (ret != GSI_STATUS_SUCCESS && !num_of_buff) {
			/*	GSI encountered an issue, stop polling even if there's
					more budget, pass packets polled until now to the client */
			DMAERR("Poll channel err: %d\n", ret);
			break;
		}

		endp->total_pkts_recv += num_of_buff;

		/*	Transfer completion data from GSI event to completion pkts list */
		for (i = 0; i < num_of_buff; i++) {
			curr_pkt_wrapper = list_first_entry(&endp->outstanding_pkt_list,
				struct ecpri_dma_outstanding_pkt_wrapper, link);

			curr_pkt_wrapper->comp_pkt.status_code = notify[i].status;
			curr_pkt_wrapper->comp_pkt.phys_port = notify[i].phys_port;

			if (endp->gsi_ep_cfg->dir == ECPRI_DMA_ENDP_DIR_DEST) {
				curr_pkt_wrapper->bytes_xfered = notify[i].bytes_xfered;
				endp->total_bytes_recv += notify[i].bytes_xfered;
			}
			else {
				for (j = 0;
					j < curr_pkt_wrapper->comp_pkt.pkt->num_of_buffers;
					j++) {
					curr_pkt_wrapper->bytes_xfered +=
						curr_pkt_wrapper->comp_pkt.pkt->buffs[j]->size;
				}
			}

			switch (notify[i].evt_id) {
			case GSI_CHAN_EVT_EOT:
				curr_iter_num_of_pkts++;
				curr_pkt_wrapper->comp_pkt.comp_code =
					ECPRI_DMA_COMPLETION_CODE_EOT;
				break;
			case GSI_CHAN_EVT_OVERFLOW:
				curr_pkt_wrapper->comp_pkt.comp_code =
					ECPRI_DMA_COMPLETION_CODE_OVERFLOW;
				break;
			default:
				DMAERR("Unexpected event code %d\n", notify[i].evt_id);
				break;
			}

			list_move_tail(&curr_pkt_wrapper->link, &endp->completed_pkt_list);
			endp->curr_outstanding_num--;
			endp->curr_completed_num++;
		}

		/*	Budget is in packets, not buffers so we need to only count EoTs */
		rem_budget -= curr_iter_num_of_pkts;

		curr_iter_num_of_pkts = 0;
		num_of_buff = 0;
	}

	ret = 0;
	i = 0;
	list_for_each_safe(pos, n, &endp->completed_pkt_list)
	{
		curr_pkt_wrapper = list_entry(pos,
			struct ecpri_dma_outstanding_pkt_wrapper,
			link);

		/*	Transfer compeltion info from completed pkt wrapper to array
			provided by the client */
		pkts[i]->status_code = curr_pkt_wrapper->comp_pkt.status_code;
		pkts[i]->comp_code = curr_pkt_wrapper->comp_pkt.comp_code;
		pkts[i]->pkt = curr_pkt_wrapper->comp_pkt.pkt;
		for (j = 0; j < pkts[i]->pkt->num_of_buffers; j++) {
			/*	Unmapping is only required for ETH S2M ENDPs
				which are not exception ENDP */
			if (endp->gsi_ep_cfg->stream_mode != ECPRI_DMA_ENDP_STREAM_MODE_M2M &&
				!(endp->gsi_id == ecpri_dma_ctx->exception_ctx.
					exception_endp.gsi_id &&
					endp->endp_id == ecpri_dma_ctx->exception_ctx.
					exception_endp.endp_id)) {
				dma_unmap_single(ecpri_dma_ctx->pdev,
					pkts[i]->pkt->buffs[j]->phys_base,
					pkts[i]->pkt->buffs[j]->size, dma_dir);
				pkts[i]->pkt->buffs[j]->phys_base = 0;
			}

			if (endp->gsi_ep_cfg->dir == ECPRI_DMA_ENDP_DIR_DEST) {
				pkts[i]->pkt->buffs[j]->size = curr_pkt_wrapper->bytes_xfered;
			}
		}
		i++;

		/* Free completed packet wrappers*/
		if (endp->avail_outstanding_pkts >=
			ECPRI_DMA_OUTSTANDING_PKTS_CACHE_MAX_THRESHOLD) {
			list_del(&curr_pkt_wrapper->link);
			kmem_cache_free(endp->available_outstanding_pkts_cache,
				curr_pkt_wrapper);
		} else {
			list_move_tail(&curr_pkt_wrapper->link,
				&endp->available_outstanding_pkts_list);
			endp->avail_outstanding_pkts++;
		}
		endp->curr_completed_num--;
	}

	*actual_num = budget - rem_budget;
	spin_unlock_irqrestore(&endp->spinlock, flags);

	return ret;
}

int ecpri_dma_dp_commit(struct ecpri_dma_endp_context *endp)
{
	int ret;
	unsigned long flags;

	if (!endp || !endp->valid) {
		DMAERR("Invalid parameters\n");
		return -EINVAL;
	}

	spin_lock_irqsave(&endp->spinlock, flags);

	ret = gsi_queue_xfer(endp->gsi_chan_hdl, 0, NULL,
			     true);
	if (ret != GSI_STATUS_SUCCESS) {
		DMAERR("GSI xfer failed, ENDP ID%x\n", endp->endp_id);
		spin_unlock_irqrestore(&endp->spinlock, flags);
		return -EFAULT;
	}

	/* Release spinlock before returning from commit function */
	spin_unlock_irqrestore(&endp->spinlock, flags);

	return 0;
}

int ecpri_dma_dp_transmit(struct ecpri_dma_endp_context *endp,
			  struct ecpri_dma_pkt **pkts, u32 num_of_pkts,
			  bool commit)
{
	struct gsi_xfer_elem gsi_xfer_arr[ECPRI_DMA_DP_MAX_DESC];
	struct ecpri_dma_outstanding_pkt_wrapper *pkt_wrapper = NULL;
	int i = 0, j = 0, k = 0;
	int gsi_xfer_index = 0;
	int ret;
	int dma_dir;
	u32 total_bytes = 0;
	unsigned long flags;
	struct ecpri_dma_dynamic_vf_params vf_params;
	struct mhi_dma_function_params* function;

	memset(&vf_params, 0, sizeof(struct ecpri_dma_dynamic_vf_params));

	if (!endp || !endp->valid || !pkts || num_of_pkts == 0) {
		DMAERR("Invalid parameters\n");
		return -EINVAL;
	}

	DMADBG_LOW("Transmit start for ENDP %d GSI ID %d, num_of_pkts: %d\n",
		endp->endp_id, endp->gsi_id, num_of_pkts);

	if (endp->gsi_ep_cfg->dir == ECPRI_DMA_ENDP_DIR_SRC)
		dma_dir = DMA_TO_DEVICE;
	else
		dma_dir = DMA_FROM_DEVICE;

	for (i = 0; i < num_of_pkts; i++) {
		for (j = 0; j < pkts[i]->num_of_buffers; j++) {
			if (!pkts[i]->buffs[j]->phys_base) {
				/* Perform mapping using SMMU */
				pkts[i]->buffs[j]->phys_base =
					dma_map_single(ecpri_dma_ctx->pdev,
						pkts[i]->buffs[j]->virt_base,
						pkts[i]->buffs[j]->size, dma_dir);
				if (dma_mapping_error(ecpri_dma_ctx->pdev,
					pkts[i]->buffs[j]->phys_base)) {
					DMAERR("failed to do dma map.\n");
					ecpri_dma_assert();
				}
			}
		}
	}

	/* Extract VF params for MHI memcpy CHs */
	if (endp->dynamic_vf_enabled) {
		function = (struct mhi_dma_function_params*)(pkts[0]->user_data);
		vf_params.vf_override = true;

		if (function->function_type == MHI_DMA_FUNCTION_TYPE_VIRTUAL) {
			vf_params.vf_valid = true;
			vf_params.vf_id = function->vf_id;
		}
	}

	spin_lock_irqsave(&endp->spinlock, flags);

	if (unlikely(atomic_read(&endp->disconnect_in_progress)) || !endp->valid) {
		DMAERR("Pipe disconnect in progress dropping the packet\n");
		spin_unlock_irqrestore(&endp->spinlock, flags);
		return -EFAULT;
	}

	for (i = 0; i < num_of_pkts; i++) {

		/* Verify number of buffers passed */
		if (pkts[i]->num_of_buffers == 0) {
			DMAERR("Pkt has 0 buffers, index: %d \n", i);
			spin_unlock_irqrestore(&endp->spinlock, flags);
			return -EINVAL;
		}

		/* Verify all packets have chains smaller than TLV fifo size */
		if (pkts[i]->num_of_buffers > endp->gsi_ep_cfg->dma_if_tlv) {
			DMAERR("Chain too long for one packet, discarding all\n");
			spin_unlock_irqrestore(&endp->spinlock, flags);
			return -EFAULT;
		}

		/* Verify we have enough space in the gsi_xfer array for all buffers */
		if (gsi_xfer_index + pkts[i]->num_of_buffers >
		    ECPRI_DMA_DP_MAX_DESC) {
			DMAERR("Too many buffers for one transmit, discarding all\n");
			spin_unlock_irqrestore(&endp->spinlock, flags);
			return -EFAULT;
		}

		if (!endp->eventless_endp) {
			/*  Prepare outstanding packet wrapper which will be used to follow up
            on transfer status */
			if (!list_empty(
				    &endp->available_outstanding_pkts_list)) {
				pkt_wrapper = list_first_entry(
					&endp->available_outstanding_pkts_list,
					struct ecpri_dma_outstanding_pkt_wrapper,
					link);
				list_del(&pkt_wrapper->link);
				endp->avail_outstanding_pkts--;
			} else {
				pkt_wrapper = kmem_cache_zalloc(
					endp->available_outstanding_pkts_cache,
					GFP_ATOMIC);
			}
			if (!pkt_wrapper) {
				DMAERR("failed to alloc packet wrapper\n");
				spin_unlock_irqrestore(&endp->spinlock, flags);
				return -ENOMEM;
			}
			memset(pkt_wrapper, 0, sizeof(*pkt_wrapper));

			/* Init the packet wrapper and add it to endp list */
			pkt_wrapper->comp_pkt.pkt = pkts[i];
			pkt_wrapper->endp = endp;
			list_add_tail(&pkt_wrapper->link,
				      &endp->outstanding_pkt_list);
			endp->curr_outstanding_num++;
		}

		/* Generate parameters for GSI transfer */
		ret = ecpri_dma_dp_gen_gsi_xfer(pkts[i],
						&gsi_xfer_arr[gsi_xfer_index],
						pkt_wrapper, &total_bytes, &vf_params);
		if (ret)
		{
			DMAERR("Failed to generate gsi xfer for pkt %d\n", i);
			goto fail_handling;
		}
		gsi_xfer_index += pkts[i]->num_of_buffers;
	}

	if (endp->curr_outstanding_num > endp->ring_length) {
		DMAERR("This transfer will exceed ring length, dropping all\n");
		goto fail_handling;
	}

	/* We're now ready to queue the transfer to the GSI ring */
	DMADBG_LOW("ch:%lu queue xfer %d descriptors with commit %d\n",
		   endp->gsi_chan_hdl, gsi_xfer_index, commit);

	ret = gsi_queue_xfer(endp->gsi_chan_hdl, gsi_xfer_index, &gsi_xfer_arr[0],
			     commit);
	if (ret != GSI_STATUS_SUCCESS) {
		DMAERR("GSI xfer failed.\n");
		goto fail_handling;
	}

	/* Increase ENDP stats */
	endp->total_pkts_sent += num_of_pkts;
	endp->total_bytes_sent += total_bytes;

	/* Release spinlock before returning from transmit function */
	spin_unlock_irqrestore(&endp->spinlock, flags);

	DMADBG_LOW("Transmit finished\n");

	return 0;

fail_handling:
	/*  Error occured need to remove pkts from endp list & unmap buffers
        Only remove packet that were already queued and mapped */
	for (k = 0; k < i; k++) {
		for (j = 0; j < pkts[k]->num_of_buffers; j++) {
			/* Perform unmapping using SMMU */
			dma_unmap_single(ecpri_dma_ctx->pdev,
				pkts[k]->buffs[j]->phys_base,
				pkts[k]->buffs[j]->size, dma_dir);
			pkts[k]->buffs[j]->phys_base = 0;
		}

		/* Remove from list */
		pkt_wrapper = list_last_entry(&endp->outstanding_pkt_list,
			struct ecpri_dma_outstanding_pkt_wrapper, link);
		list_del(&pkt_wrapper->link);
		endp->curr_outstanding_num--;
		kmem_cache_free(endp->available_outstanding_pkts_cache,
				pkt_wrapper);
	}
	spin_unlock_irqrestore(&endp->spinlock, flags);
	return -EFAULT;
}
