// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2015-2021, The Linux Foundation. All rights reserved.
 * Copyright (c) 2022-2025 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#if defined(CONFIG_DEBUG_FS) && !defined(ECPRI_NO_PRINTS)
#include <linux/completion.h>
#include <linux/debugfs.h>
#include <linux/dma-mapping.h>
#include <linux/random.h>
#include <linux/uaccess.h>
#include <linux/msm_gsi.h>
#include "gsi.h"
#include "gsihal.h"

#define GSI_MAX_MSG_LEN 4096
#define GSI_MAX_READ_BLOCK (3000)
#define TERR(fmt, args...) \
		pr_err("%s:%d " fmt, __func__, __LINE__, ## args)
#define TDBG(fmt, args...) \
		pr_debug("%s:%d " fmt, __func__, __LINE__, ## args)
#define PRT_STAT(fmt, args...) \
		pr_err(fmt, ## args)

static struct dentry *dent;
static char dbg_buff[GSI_MAX_MSG_LEN];
static void *gsi_ipc_logbuf_low;
static uint32_t gsi_ch_dump_last_index = 0;
static uint32_t arg1, arg2, arg3, arg4;
static uint32_t gsi_dump_stats_min, gsi_dump_stats_max;
static int gsi_dump_stats_ch_id;
static int gsi_dump_stats_ee;
static int gsi_dump_stats_gsi_id;
static bool gsi_read_finished = false;

static void gsi_wq_print_dp_stats(struct work_struct *work);
static DECLARE_DELAYED_WORK(gsi_print_dp_stats_work, gsi_wq_print_dp_stats);
static void gsi_wq_update_dp_stats(struct work_struct *work);
static DECLARE_DELAYED_WORK(gsi_update_dp_stats_work, gsi_wq_update_dp_stats);

static ssize_t gsi_dump_evt_read(struct file *file,
	char __user *ubuf, size_t count, loff_t *ppos)
{
	int ret;
	int nbytes = 0;
	uint32_t val;
	struct gsi_evt_ctx *ctx;
	uint16_t i;
	loff_t pos = 0;

	if (gsi_read_finished) {
		gsi_read_finished = false;
		return 0;
	}

	if (arg1 >= gsi_ctx->max_ev) {
		nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes,
		"invalid evt ring id %u\n", arg1);

		ret =  simple_read_from_buffer(ubuf, nbytes + 1, ppos, dbg_buff, count);
		return ret;
	}

	/* For first entry */
	if (0 == gsi_ch_dump_last_index) {
		val = gsihal_read_reg_pnk(GSI_EE_n_EV_CH_k_CNTXT_0,
			arg3, arg2, arg1);
		nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes,"EV%2d EE%d GSI ID %d CTX0  0x%x\n", arg1, arg2, arg3, val);

		val = gsihal_read_reg_pnk(GSI_EE_n_EV_CH_k_CNTXT_1,
			arg3, arg2, arg1);
		nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes,"EV%2d EE%d GSI ID %d CTX1  0x%x\n", arg1, arg2, arg3, val);
		val = gsihal_read_reg_pnk(GSI_EE_n_EV_CH_k_CNTXT_2,
			arg3, arg2, arg1);
		nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes,"EV%2d EE%d GSI ID %d CTX2  0x%x\n", arg1, arg2, arg3, val);
		val = gsihal_read_reg_pnk(GSI_EE_n_EV_CH_k_CNTXT_3,
			arg3, arg2, arg1);
		nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes,"EV%2d EE%d GSI ID %d CTX3  0x%x\n", arg1, arg2, arg3, val);
		val = gsihal_read_reg_pnk(GSI_EE_n_EV_CH_k_CNTXT_4,
			arg3, arg2, arg1);
		nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes,"EV%2d EE%d GSI ID %d CTX4  0x%x\n", arg1, arg2, arg3, val);
		val = gsihal_read_reg_pnk(GSI_EE_n_EV_CH_k_CNTXT_5,
			arg3, arg2, arg1);
		nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes,"EV%2d EE%d GSI ID %d CTX5  0x%x\n", arg1, arg2, arg3, val);
		val = gsihal_read_reg_pnk(GSI_EE_n_EV_CH_k_CNTXT_6,
			arg3, arg2, arg1);
		nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes,"EV%2d EE%d GSI ID %d CTX6  0x%x\n", arg1, arg2, arg3, val);
		val = gsihal_read_reg_pnk(GSI_EE_n_EV_CH_k_CNTXT_7,
			arg3, arg2, arg1);
		nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes,"EV%2d EE%d GSI ID %d CTX7  0x%x\n", arg1, arg2, arg3, val);
		val = gsihal_read_reg_pnk(GSI_EE_n_EV_CH_k_CNTXT_8,
			arg3, arg2, arg1);
		nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes,"EV%2d EE%d GSI ID %d CTX8  0x%x\n", arg1, arg2, arg3, val);
		val = gsihal_read_reg_pnk(GSI_EE_n_EV_CH_k_CNTXT_9,
			arg3, arg2, arg1);
		nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes,"EV%2d EE%d GSI ID %d CTX9  0x%x\n", arg1, arg2, arg3, val);
		val = gsihal_read_reg_pnk(GSI_EE_n_EV_CH_k_CNTXT_10,
			arg3, arg2, arg1);
		nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes,"EV%2d EE%d GSI ID %d CTX10 0x%x\n", arg1, arg2, arg3, val);
		val = gsihal_read_reg_pnk(GSI_EE_n_EV_CH_k_CNTXT_11,
			arg3, arg2, arg1);
		nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes,"EV%2d EE%d GSI ID %d CTX11 0x%x\n", arg1, arg2, arg3, val);
		val = gsihal_read_reg_pnk(GSI_EE_n_EV_CH_k_CNTXT_12,
			arg3, arg2, arg1);
		nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes,"EV%2d EE%d GSI ID %d CTX12 0x%x\n", arg1, arg2, arg3, val);
		val = gsihal_read_reg_pnk(GSI_EE_n_EV_CH_k_CNTXT_13,
			arg3, arg2, arg1);
		nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes,"EV%2d EE%d GSI ID %d CTX13 0x%x\n", arg1, arg2, arg3, val);
		val = gsihal_read_reg_pnk(GSI_EE_n_EV_CH_k_SCRATCH_0,
			arg3, arg2, arg1);
		nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes,"EV%2d EE%d GSI ID %d SCR0  0x%x\n", arg1, arg2, arg3, val);
		val = gsihal_read_reg_pnk(GSI_EE_n_EV_CH_k_SCRATCH_1,
			arg3, arg2, arg1);
		nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes, "EV%2d EE%d GSI ID %d SCR1  0x%x\n", arg1, arg2, arg3, val);
	}

	gsi_read_finished = true;

	if (arg4) {
		ctx = &gsi_ctx->evtr[arg3][arg2][arg1];

		if (ctx->props.ring_base_vaddr) {
			for (i = gsi_ch_dump_last_index; i < ctx->props.ring_len / 16; i++) {
				nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes,"EV%2d EE%d GSI ID %d (0x%08llx) %08x %08x %08x %08x\n",
				arg1, arg2, arg3, ctx->props.ring_base_addr + i * 16,
				*(u32 *)((u8 *)ctx->props.ring_base_vaddr +
					i * 16 + 0),
				*(u32 *)((u8 *)ctx->props.ring_base_vaddr +
					i * 16 + 4),
				*(u32 *)((u8 *)ctx->props.ring_base_vaddr +
					i * 16 + 8),
				*(u32 *)((u8 *)ctx->props.ring_base_vaddr +
					i * 16 + 12));

				if (nbytes > GSI_MAX_READ_BLOCK) {
					gsi_read_finished = false;
					break;
				}
			}

			gsi_ch_dump_last_index = i + 1;

		} else {
			nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes,
			"No VA supplied for event ring id %u\n", arg1);
		}
	}

	ret = simple_read_from_buffer(ubuf,  nbytes + 1, &pos, dbg_buff, count);
	return ret;
}


static ssize_t gsi_dump_evt_write(struct file *file,
		const char __user *buf, size_t count, loff_t *ppos)
{
	unsigned long missing;
	char *sptr, *token;

	if (count >= sizeof(dbg_buff))
		return -EINVAL;

	missing = copy_from_user(dbg_buff, buf, count);
	if (missing)
		return -EFAULT;

	dbg_buff[count] = '\0';

	sptr = dbg_buff;

	token = strsep(&sptr, " ");
	if (!token)
		return -EINVAL;

	if (kstrtou32(token, 0, &arg1))
		return -EINVAL;

	token = strsep(&sptr, " ");
	if (!token)
		return -EINVAL;
	if (kstrtou32(token, 0, &arg2))
		return -EINVAL;

	token = strsep(&sptr, " ");
	if (!token)
		return -EINVAL;
	if (kstrtou32(token, 0, &arg3))
		return -EINVAL;

	token = strsep(&sptr, " ");
	if (!token)
		return -EINVAL;
	if (kstrtou32(token, 0, &arg4))
		return -EINVAL;

	if (arg1 >= gsi_ctx->max_ev) {
		TERR("invalid evt ring id %u\n", arg1);
		return -EINVAL;
	}

	/* Reset loop position */
	gsi_ch_dump_last_index = 0;
	gsi_read_finished = false;

	return count;
}

static ssize_t gsi_ch_dump_read(struct file *file,
	char __user *ubuf, size_t count, loff_t *ppos)
{
	int ret;
	u32 nbytes = 0;
	int i = 0;
	struct gsi_chan_ctx *ctx;
	loff_t pos = 0;

	if (gsi_read_finished) {
		gsi_read_finished = false;
		return 0;
	}

	ctx = &gsi_ctx->chan[arg3][arg2][arg1];

	/* Dump GSI info on first access*/
	if (0 == gsi_ch_dump_last_index)
		nbytes += gsi_dump_ch_info_to_buffer(ctx->hdl, dbg_buff + nbytes, GSI_MAX_MSG_LEN);

	gsi_read_finished = true;

	if (arg4) {
		if (ctx->props.ring_base_vaddr) {

			for (i = gsi_ch_dump_last_index; i < ctx->props.ring_len / 16; i++) {
				nbytes += scnprintf(
					dbg_buff + nbytes,
					GSI_MAX_MSG_LEN - nbytes,
					"CH%2d (0x%08llx) %08x %08x %08x %08x\n",

				arg1, ctx->props.ring_base_addr + i * 16,
				*(u32 *)((u8 *)ctx->props.ring_base_vaddr +
					i * 16 + 0),
				*(u32 *)((u8 *)ctx->props.ring_base_vaddr +
					i * 16 + 4),
				*(u32 *)((u8 *)ctx->props.ring_base_vaddr +
					i * 16 + 8),
				*(u32 *)((u8 *)ctx->props.ring_base_vaddr +
					i * 16 + 12));

				if (nbytes > GSI_MAX_READ_BLOCK) {
					gsi_read_finished = false;
					break;
				}
			}
			gsi_ch_dump_last_index = i + 1;

		} else {
			nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes,
			"No VA supplied for chan id %u\n", arg1);
		}
	}

	if (0 == nbytes) {
		gsi_ch_dump_last_index = 0;
		return 0;
	}

	ret = simple_read_from_buffer(ubuf, nbytes + 1, &pos, dbg_buff, count);
	return ret;
}


static ssize_t gsi_ch_dump_write(struct file *file,
		const char __user *buf, size_t count, loff_t *ppos)
{
	unsigned long missing;
	char *sptr, *token;
	if (count >= sizeof(dbg_buff))
		return -EINVAL;

	missing = copy_from_user(dbg_buff, buf, count);
	if (missing)
		return -EFAULT;

	dbg_buff[count] = '\0';

	sptr = dbg_buff;

	token = strsep(&sptr, " ");
	if (!token)
		return -EINVAL;

	if (kstrtou32(token, 0, &arg1))
		return -EINVAL;

	token = strsep(&sptr, " ");
	if (!token)
		return -EINVAL;

	if (kstrtou32(token, 0, &arg2))
		return -EINVAL;

	token = strsep(&sptr, " ");
	if (!token)
		return -EINVAL;

	if (kstrtou32(token, 0, &arg3))
		return -EINVAL;

	token = strsep(&sptr, " ");
	if (!token)
		return -EINVAL;

	if (kstrtou32(token, 0, &arg4))
		return -EINVAL;

	if (arg1 >= gsi_ctx->max_ch) {
		TERR("invalid chan id %u\n", arg1);
		return -EINVAL;
	}

	gsi_ch_dump_last_index = 0;
	gsi_read_finished = false;
	return count;
}

static int gsi_ch_dump_stats(u8* dbg_buff, struct gsi_chan_ctx *ctx)
{
	int nbytes = 0;

	if (!ctx->allocated)
		return nbytes;

	nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes, "CH%2d:\n", ctx->props.ch_id);
	nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes, "queued=%lu compl=%lu\n",
		ctx->stats.queued,
		ctx->stats.completed);
	nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes, "cb->poll=%lu poll->cb=%lu poll_pend_irq=%lu\n",
		ctx->stats.callback_to_poll,
		ctx->stats.poll_to_callback,
		ctx->stats.poll_pending_irq);
	nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes, "invalid_tre_error=%lu\n",
		ctx->stats.invalid_tre_error);
	nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes, "poll_ok=%lu poll_empty=%lu\n",
		ctx->stats.poll_ok, ctx->stats.poll_empty);
	if (ctx->evtr)
		nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes, "compl_evt=%lu\n",
			ctx->evtr->stats.completed);
	nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes, "userdata_in_use=%lu\n", ctx->stats.userdata_in_use);

	nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes, "ch_below_lo=%lu\n", ctx->stats.dp.ch_below_lo);
	nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes, "ch_below_hi=%lu\n", ctx->stats.dp.ch_below_hi);
	nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes, "ch_above_hi=%lu\n", ctx->stats.dp.ch_above_hi);
	nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes, "time_empty=%lums\n", ctx->stats.dp.empty_time);
	nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN - nbytes, "\n");

	return nbytes;
}

static ssize_t gsi_dump_stats_read(struct file *file,
	char __user *ubuf, size_t count, loff_t *ppos)
{
	int ret;
	u32 nbytes = 0;
	int ch_id;
	loff_t pos = 0;

	if (gsi_read_finished) {
		gsi_read_finished = false;
		return 0;
	}

	gsi_read_finished = true;

	for (ch_id = gsi_dump_stats_min; ch_id < gsi_dump_stats_max; ch_id++) {
		nbytes += gsi_ch_dump_stats(dbg_buff + nbytes,
			&gsi_ctx->chan[gsi_dump_stats_gsi_id][gsi_dump_stats_ee][ch_id]);

		if (nbytes > GSI_MAX_READ_BLOCK) {
			gsi_read_finished = false;
			break;
		}
	}

	/* Remember last read channel*/
	gsi_dump_stats_min = ch_id + 1;

	ret = simple_read_from_buffer(ubuf, nbytes + 1, &pos, dbg_buff, count);
	return ret;
}

static ssize_t gsi_dump_stats_write(struct file *file,
		const char __user *buf, size_t count, loff_t *ppos)
{

	unsigned long missing;
	char *sptr, *token;

	if (count >= sizeof(dbg_buff))
		return -EINVAL;

	missing = copy_from_user(dbg_buff, buf, count);
	if (missing)
		return -EFAULT;

	dbg_buff[count] = '\0';

	sptr = dbg_buff;

	token = strsep(&sptr, " ");
	if (!token)
		return -EINVAL;

	if (kstrtos32(token, 0, &gsi_dump_stats_ch_id))
		return -EINVAL;

	token = strsep(&sptr, " ");
	if (!token)
		return -EINVAL;

	if (kstrtos32(token, 0, &gsi_dump_stats_gsi_id))
		return -EINVAL;

	token = strsep(&sptr, " ");
	if (!token)
		return -EINVAL;

	if (kstrtos32(token, 0, &gsi_dump_stats_ee))
		return -EINVAL;

	if (gsi_dump_stats_ch_id == -1) {
		gsi_dump_stats_min = 0;
		gsi_dump_stats_max = gsi_ctx->max_ch;

	} else if (gsi_dump_stats_ch_id < 0 || gsi_dump_stats_ch_id >= gsi_ctx->max_ch) {
		TERR("Error: channel id is out of range [%d].\n",
		gsi_dump_stats_ch_id);
		return -EINVAL;

	} else if (
		!gsi_ctx->chan[gsi_dump_stats_gsi_id][gsi_dump_stats_ee] [gsi_dump_stats_ch_id].allocated) {
		TERR("Error: requested channel isn't allocated [%d].\n",
		 gsi_dump_stats_ch_id);
		return -EINVAL;

	} else {
		gsi_dump_stats_min = gsi_dump_stats_ch_id;
		gsi_dump_stats_max = gsi_dump_stats_ch_id + 1;
	}

	/* Reset read flag */
	gsi_read_finished = false;
	return count;
}

static int gsi_dbg_create_stats_wq(void)
{
	gsi_ctx->dp_stat_wq =
		create_singlethread_workqueue("gsi_stat");
	if (!gsi_ctx->dp_stat_wq) {
		TERR("failed create workqueue\n");
		return -ENOMEM;
	}

	return 0;
}

static void gsi_dbg_destroy_stats_wq(void)
{
	cancel_delayed_work_sync(&gsi_update_dp_stats_work);
	cancel_delayed_work_sync(&gsi_print_dp_stats_work);
	flush_workqueue(gsi_ctx->dp_stat_wq);
	destroy_workqueue(gsi_ctx->dp_stat_wq);
	gsi_ctx->dp_stat_wq = NULL;
}

static ssize_t gsi_enable_dp_stats(struct file *file,
	const char __user *buf, size_t count, loff_t *ppos)
{
	int ch_id, ee, gsi_id;
	bool enable;
	int ret;
	char *sptr, *token;


	if (count >= sizeof(dbg_buff))
		goto error;

	if (copy_from_user(dbg_buff, buf, count))
		goto error;

	sptr = dbg_buff;

	dbg_buff[count] = '\0';

	if (dbg_buff[0] != '+' && dbg_buff[0] != '-')
		goto error;

	enable = (dbg_buff[0] == '+');

	/* Skip +/- argments */
	sptr = dbg_buff + 2;

	token = strsep(&sptr, " ");
	if (!token)
		goto error;


	if (kstrtou32(token, 0, &ch_id))
		goto error;


	token = strsep(&sptr, " ");
	if (!token)
		goto error;


	if (kstrtou32(token, 0, &gsi_id))
		goto error;


	token = strsep(&sptr, " ");
	if (!token)
		goto error;


	if (kstrtou32(token, 0, &ee))
		goto error;

	if (ch_id < 0 || ch_id >= gsi_ctx->max_ch ||
		!gsi_ctx->chan[gsi_id][ee][ch_id].allocated) {
		goto error;
	}

	if (gsi_ctx->chan[gsi_id][ee][ch_id].enable_dp_stats == enable) {
		TERR("ch_%d: already enabled/disabled\n", ch_id);
		return -EINVAL;
	}

	gsi_ctx->chan[gsi_id][ee][ch_id].enable_dp_stats = enable;

	if (enable)
		gsi_ctx->num_ch_dp_stats++;
	else
		gsi_ctx->num_ch_dp_stats--;

	if (enable) {
		if (gsi_ctx->num_ch_dp_stats == 1) {
			ret = gsi_dbg_create_stats_wq();
			if (ret)
				return ret;
		}
		cancel_delayed_work_sync(&gsi_update_dp_stats_work);
		queue_delayed_work(gsi_ctx->dp_stat_wq,
			&gsi_update_dp_stats_work, msecs_to_jiffies(10));
	} else if (!enable && gsi_ctx->num_ch_dp_stats == 0) {
		gsi_dbg_destroy_stats_wq();
	}

	return count;
error:
	TERR("Usage: echo [+-] ch_id > enable_dp_stats\n");
	return -EINVAL;
}

static ssize_t gsi_set_max_elem_dp_stats(struct file *file,
		const char __user *buf, size_t count, loff_t *ppos)
{
	u32 ch_id, ee, gsi_id;
	u32 max_elem;
	unsigned long missing;
	char *sptr, *token;


	if (count >= sizeof(dbg_buff))
		goto error;

	missing = copy_from_user(dbg_buff, buf, count);
	if (missing)
		goto error;

	dbg_buff[count] = '\0';

	sptr = dbg_buff;

	token = strsep(&sptr, " ");
	if (!token)
		goto error;

	if (kstrtou32(token, 0, &ch_id))
		goto error;

	token = strsep(&sptr, " ");
	if (!token)
		goto error;

	if (kstrtou32(token, 0, &gsi_id))
		goto error;

	token = strsep(&sptr, " ");
	if (!token)
		goto error;

	if (kstrtou32(token, 0, &ee))
		goto error;


	token = strsep(&sptr, " ");
	if (!token) {
		/* get */
		if (kstrtou32(dbg_buff, 0, &ch_id))
			goto error;

		if (ch_id >= gsi_ctx->max_ch)
			goto error;

		PRT_STAT("ch %d: max_re_expected=%d\n", ch_id,
			gsi_ctx->chan[gsi_id][ee][ch_id].props.max_re_expected);
		return count;
	}
	if (kstrtou32(token, 0, &max_elem)) {
		TERR("\n");
		goto error;
	}

	TDBG("ch_id=%u max_elem=%u\n", ch_id, max_elem);

	if (ch_id >= gsi_ctx->max_ch) {
		TERR("invalid chan id %u\n", ch_id);
		goto error;
	}

	gsi_ctx->chan[gsi_id][ee][ch_id].props.max_re_expected = max_elem;

	return count;

error:
	TERR("Usage: (set) echo <ch_id> <max_elem> > max_elem_dp_stats\n");
	TERR("Usage: (get) echo <ch_id> > max_elem_dp_stats\n");
	return -EINVAL;
}

static void gsi_wq_print_dp_stats(struct work_struct *work)
{
	int ch_id, ee, gsi_id;

	for (gsi_id = 0; gsi_id < GSI_NUM_MAX; gsi_id++)
	{
		for (ee = 0; ee < GSI_EE_MAX; ee++)
		{
			if (ee == GSI_Q6_EE)
				continue;

			for (ch_id = 0; ch_id < gsi_ctx->max_ch; ch_id++) {
				if (gsi_ctx->chan[gsi_id][ee][ch_id].print_dp_stats)
					gsi_ch_dump_stats(dbg_buff, &gsi_ctx->chan[gsi_id][ee][ch_id]);
					TERR("%s\n", dbg_buff);
			}
		}
	}

	queue_delayed_work(gsi_ctx->dp_stat_wq, &gsi_print_dp_stats_work,
		msecs_to_jiffies(1000));
}

static void gsi_dbg_update_ch_dp_stats(struct gsi_chan_ctx *ctx)
{
	uint16_t start_hw;
	uint16_t end_hw;
	uint64_t rp_hw;
	uint64_t wp_hw;
	int gsi_id = ctx->props.gsi_id;
	int ee = ctx->props.ee;
	uint16_t used_hw;

	rp_hw = gsihal_read_reg_pnk(GSI_EE_n_GSI_CH_k_CNTXT_4,
		gsi_id, ee, ctx->props.ch_id);
	rp_hw |= ((uint64_t)gsihal_read_reg_pnk(GSI_EE_n_GSI_CH_k_CNTXT_5,
		gsi_id, ee, ctx->props.ch_id)) << 32;

	wp_hw = gsihal_read_reg_pnk(GSI_EE_n_GSI_CH_k_CNTXT_6,
		gsi_id, ee, ctx->props.ch_id);
	wp_hw |= ((uint64_t)gsihal_read_reg_pnk(GSI_EE_n_GSI_CH_k_CNTXT_7,
		gsi_id, ee, ctx->props.ch_id)) << 32;

	start_hw = gsi_find_idx_from_addr(&ctx->ring, rp_hw);
	end_hw = gsi_find_idx_from_addr(&ctx->ring, wp_hw);

	if (end_hw >= start_hw)
		used_hw = end_hw - start_hw;
	else
		used_hw = ctx->ring.max_num_elem - (start_hw - end_hw);

	TDBG("ch %d used %d\n", ctx->props.ch_id, used_hw);
	gsi_update_ch_dp_stats(ctx, used_hw);
}

static void gsi_wq_update_dp_stats(struct work_struct *work)
{
	int ch_id, ee, gsi_id;
	for (gsi_id = 0; gsi_id < GSI_NUM_MAX; gsi_id++)
	{
		for (ee = 0; ee < GSI_EE_MAX; ee++)
		{
			if (ee == GSI_Q6_EE)
				continue;
			for (ch_id = 0; ch_id < gsi_ctx->max_ch; ch_id++) {
				if (gsi_ctx->chan[gsi_id][ee][ch_id].allocated &&
					gsi_ctx->chan[gsi_id][ee][ch_id].enable_dp_stats)
					gsi_dbg_update_ch_dp_stats(&gsi_ctx->chan[gsi_id][ee][ch_id]);
			}
		}
	}

	queue_delayed_work(gsi_ctx->dp_stat_wq, &gsi_update_dp_stats_work,
		msecs_to_jiffies(10));
}


static ssize_t gsi_rst_stats(struct file *file,
		const char __user *buf, size_t count, loff_t *ppos)
{

	u32 ch_id, ee, gsi_id;
	unsigned long missing;
	char *sptr, *token;
	int min, max;

	if (count >= sizeof(dbg_buff))
		goto error;

	missing = copy_from_user(dbg_buff, buf, count);
	if (missing)
		goto error;

	dbg_buff[count] = '\0';

	sptr = dbg_buff;

	token = strsep(&sptr, " ");
	if (!token) {
		TERR("\n");
		goto error;
	}

	if (kstrtou32(token, 0, &ch_id)) {
		TERR("\n");
		goto error;
	}

	token = strsep(&sptr, " ");
	if (!token) {
		TERR("\n");
		goto error;
	}

	if (kstrtou32(token, 0, &gsi_id)) {
		TERR("\n");
		goto error;
	}

	token = strsep(&sptr, " ");
	if (!token) {
		TERR("\n");
		goto error;
	}

	if (kstrtou32(token, 0, &ee)) {
		TERR("\n");
		goto error;
	}

	if (ch_id == -1) {
		min = 0;
		max = gsi_ctx->max_ch;
	} else if (ch_id < 0 || ch_id >= gsi_ctx->max_ch ||
		   !gsi_ctx->chan[gsi_id][ee][ch_id].allocated) {
		goto error;
	} else {
		min = ch_id;
		max = ch_id + 1;
	}

	for (ch_id = min; ch_id < max; ch_id++)
		memset(&gsi_ctx->chan[gsi_id][ee][ch_id].stats, 0,
			sizeof(gsi_ctx->chan[gsi_id][ee][ch_id].stats));

	return count;
error:
	TERR("Usage: echo ch_id > rst_stats. Use -1 for all\n");
	return -EINVAL;
}

static ssize_t gsi_print_dp_stats(struct file *file,
	const char __user *buf, size_t count, loff_t *ppos)
{
	int ch_id, ee, gsi_id;
	bool enable;
	int ret;
	char *sptr, *token;

	if (count >= sizeof(dbg_buff))
		goto error;

	if (copy_from_user(dbg_buff, buf, count))
		goto error;

	dbg_buff[count] = '\0';

	if (dbg_buff[0] != '+' && dbg_buff[0] != '-')
		goto error;

	enable = (dbg_buff[0] == '+');

	if (count >= sizeof(dbg_buff))
		goto error;

	/* Skip +/- argments */
	sptr = dbg_buff + 2;

	token = strsep(&sptr, " ");
	if (!token) {
		TERR("\n");
		goto error;
	}

	if (kstrtou32(token, 0, &ch_id)) {
		TERR("\n");
		goto error;
	}

	token = strsep(&sptr, " ");
	if (!token) {
		TERR("\n");
		goto error;
	}

	if (kstrtou32(token, 0, &gsi_id)) {
		TERR("\n");
		goto error;
	}

	token = strsep(&sptr, " ");
	if (!token) {
		TERR("\n");
		goto error;
	}

	if (kstrtou32(token, 0, &ee)) {
		TERR("\n");
		goto error;
	}

	if (ch_id < 0 || ch_id >= gsi_ctx->max_ch ||
		!gsi_ctx->chan[gsi_id][ee][ch_id].allocated) {
		goto error;
	}

	if (gsi_ctx->chan[gsi_id][ee][ch_id].print_dp_stats == enable) {
		TERR("ch_%d: already enabled/disabled\n", ch_id);
		return -EINVAL;
	}

	gsi_ctx->chan[gsi_id][ee][ch_id].print_dp_stats = enable;

	if (enable)
		gsi_ctx->num_ch_dp_stats++;
	else
		gsi_ctx->num_ch_dp_stats--;

	if (enable) {
		if (gsi_ctx->num_ch_dp_stats == 1) {
			ret = gsi_dbg_create_stats_wq();
			if (ret)
				return ret;
		}
		cancel_delayed_work_sync(&gsi_print_dp_stats_work);
		queue_delayed_work(gsi_ctx->dp_stat_wq,
			&gsi_print_dp_stats_work, msecs_to_jiffies(10));
	} else if (!enable && gsi_ctx->num_ch_dp_stats <= 0) {
		gsi_dbg_destroy_stats_wq();
	}

	return count;
error:
	TERR("Usage: echo [+-]ch_id > print_dp_stats\n");
	return -EINVAL;
}

static ssize_t gsi_enable_ipc_low(struct file *file,
	const char __user *ubuf, size_t count, loff_t *ppos)
{
	s8 option = 0;
	int ret;

	ret = kstrtos8_from_user(ubuf, count, 0, &option);
	if (ret)
		return ret;

	mutex_lock(&gsi_ctx->mlock);
	if (option) {
		if (!gsi_ipc_logbuf_low) {
			gsi_ipc_logbuf_low =
				ipc_log_context_create(GSI_IPC_LOG_PAGES,
					"gsi_low", 0);
			if (gsi_ipc_logbuf_low == NULL)
				TERR("failed to get ipc_logbuf_low\n");
		}
		gsi_ctx->ipc_logbuf_low = gsi_ipc_logbuf_low;
	} else {
		gsi_ctx->ipc_logbuf_low = NULL;
	}
	mutex_unlock(&gsi_ctx->mlock);

	return count;
}

static ssize_t gsi_read_gsi_hw_profiling_stats(struct file *file,
	char __user *buf, size_t count, loff_t *ppos)
{
	struct gsi_hw_profiling_data stats;
	int nbytes = 0;
	u64 totalCycles = 0, util = 0;
	u32 gsi_id;
	int ret;
	loff_t pos = 0;

	if(gsi_read_finished == true) {
		gsi_read_finished = false;
		return 0;
	}

	for (gsi_id = 0; gsi_id < gsi_ctx->num_of_gsi; gsi_id++)
	{
		if (!gsi_get_hw_profiling_stats(&stats)) {
			totalCycles = stats.mcs_busy_cnt[gsi_id] +
				stats.mcs_idle_cnt[gsi_id] +
				stats.bp_and_pending_cnt[gsi_id];
			if (totalCycles != 0)
				util = div_u64(
					100 * (stats.mcs_busy_cnt[gsi_id] +
						stats.bp_and_pending_cnt[gsi_id]),
					totalCycles);
			else
				util = 0;

			nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN,
				"Results for GSI ID %d\n"
				"bp_count=0x%llx\n"
				"bp_and_pending_count=0x%llx\n"
				"mcs_busy=0x%llx\n"
				"mcs_idle=0x%llx\n"
				"total_cycle_count=0x%llx\n"
				"utilization_percentage=%llu%%\n",
				gsi_id,
				stats.bp_cnt[gsi_id],
				stats.bp_and_pending_cnt[gsi_id],
				stats.mcs_busy_cnt[gsi_id],
				stats.mcs_idle_cnt[gsi_id],
				totalCycles,
				util);
		}
		else {
			nbytes += scnprintf(dbg_buff + nbytes, GSI_MAX_MSG_LEN,
				"Fail to read GSI HW Profiling stats\n");
		}
	}
	ret = simple_read_from_buffer(buf, nbytes + 1, &pos, dbg_buff, count);

	gsi_read_finished = true;
	return ret;
}

static ssize_t gsi_read_gsi_fw_version(struct file *file,
	char __user *buf, size_t count, loff_t *ppos)
{
	struct gsi_fw_version ver;
	int nbytes = 0;
	int cnt = 0;
	loff_t pos = 0;
	int ret;

	if(gsi_read_finished == true) {
		gsi_read_finished = false;
		return 0;
	}

	if (!gsi_get_fw_version(&ver)) {
		nbytes += scnprintf(dbg_buff, GSI_MAX_MSG_LEN,
			"hw=%d\nflavor=%d\nfw=%d\n",
			ver.hw,
			ver.flavor,
			ver.fw);
		cnt += nbytes;
	} else {
		nbytes += scnprintf(dbg_buff, GSI_MAX_MSG_LEN,
			"Fail to read GSI FW version\n");
		cnt += nbytes;
	}

	ret = simple_read_from_buffer(buf, nbytes, &pos, dbg_buff, count);

	gsi_read_finished = true;
	return ret;
}

static const struct file_operations gsi_ev_dump_ops = {
	.write = gsi_dump_evt_write,
	.read =  gsi_dump_evt_read
};

static const struct file_operations gsi_ch_dump_ops = {
	.write = gsi_ch_dump_write,
	.read =  gsi_ch_dump_read
};

static const struct file_operations gsi_stats_ops = {
	.write = gsi_dump_stats_write,
	.read =  gsi_dump_stats_read
};

static const struct file_operations gsi_enable_dp_stats_ops = {
	.write = gsi_enable_dp_stats,
};

static const struct file_operations gsi_max_elem_dp_stats_ops = {
	.write = gsi_set_max_elem_dp_stats,
};

static const struct file_operations gsi_rst_stats_ops = {
	.write = gsi_rst_stats,
};

static const struct file_operations gsi_print_dp_stats_ops = {
	.write = gsi_print_dp_stats,
};

static const struct file_operations gsi_ipc_low_ops = {
	.write = gsi_enable_ipc_low,
};

static const struct file_operations gsi_hw_profiling_ops = {
	.read = gsi_read_gsi_hw_profiling_stats,
};

static const struct file_operations gsi_ver_ops = {
	.read = gsi_read_gsi_fw_version,
};

void gsi_debugfs_init(void)
{
	static struct dentry *dfile;
	const mode_t write_only_mode = 0220;
	const mode_t read_only_mode = 0440;
	const mode_t read_write_mode = 0664;

	dent = debugfs_create_dir("gsi", 0);
	if (IS_ERR(dent)) {
		TERR("fail to create dir\n");
		return;
	}

	dfile = debugfs_create_file("ev_dump", read_write_mode,
			dent, 0, &gsi_ev_dump_ops);
	if (!dfile || IS_ERR(dfile)) {
		TERR("fail to create ev_dump file\n");
		goto fail;
	}

	dfile = debugfs_create_file("ch_dump", read_write_mode,
			dent, 0, &gsi_ch_dump_ops);
	if (!dfile || IS_ERR(dfile)) {
		TERR("fail to create ch_dump file\n");
		goto fail;
	}

	dfile = debugfs_create_file("stats", read_write_mode, dent,
			0, &gsi_stats_ops);
	if (!dfile || IS_ERR(dfile)) {
		TERR("fail to create stats file\n");
		goto fail;
	}

	dfile = debugfs_create_file("enable_dp_stats", write_only_mode, dent,
			0, &gsi_enable_dp_stats_ops);
	if (!dfile || IS_ERR(dfile)) {
		TERR("fail to create stats file\n");
		goto fail;
	}

	dfile = debugfs_create_file("max_elem_dp_stats", write_only_mode,
		dent, 0, &gsi_max_elem_dp_stats_ops);
	if (!dfile || IS_ERR(dfile)) {
		TERR("fail to create stats file\n");
		goto fail;
	}

	dfile = debugfs_create_file("rst_stats", write_only_mode,
		dent, 0, &gsi_rst_stats_ops);
	if (!dfile || IS_ERR(dfile)) {
		TERR("fail to create stats file\n");
		goto fail;
	}

	dfile = debugfs_create_file("print_dp_stats",
		write_only_mode, dent, 0, &gsi_print_dp_stats_ops);
	if (!dfile || IS_ERR(dfile)) {
		TERR("fail to create stats file\n");
		goto fail;
	}

	dfile = debugfs_create_file("ipc_low", write_only_mode,
		dent, 0, &gsi_ipc_low_ops);
	if (!dfile || IS_ERR(dfile)) {
		TERR("could not create ipc_low\n");
		goto fail;
	}

	dfile = debugfs_create_file("gsi_hw_profiling_stats", read_only_mode,
				    dent, 0, &gsi_hw_profiling_ops);
	if (!dfile || IS_ERR(dfile)) {
		TERR("could not create gsi_hw_profiling_stats\n");
		goto fail;
	}

	dfile = debugfs_create_file("gsi_fw_version", read_only_mode, dent, 0,
				    &gsi_ver_ops);
	if (!dfile || IS_ERR(dfile)) {
		TERR("could not create gsi_fw_version\n");
		goto fail;
	}

	return;

fail:
	debugfs_remove_recursive(dent);
}
#endif //defined(CONFIG_DEBUG_FS) && !defined(ECPRI_NO_PRINTS)
