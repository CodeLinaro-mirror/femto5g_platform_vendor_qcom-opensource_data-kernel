/*
 * SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#if defined(CONFIG_DEBUG_FS) && !defined(ECPRI_NO_PRINTS)

#include <linux/debugfs.h>
#include <linux/kernel.h>
#include <linux/stringify.h>
#include "ecpri_dma_i.h"
#include "dmahal.h"
#include "ecpri_dma_reg_dump.h"
#include "ecpri_dma_qmi_service.h"
#include "ecpri_dma_eth_client.h"
#include "dmahal_reg.h"

#define DMA_MAX_ENTRY_STRING_LEN 500
#define DMA_MAX_MSG_LEN 4096

#define DMA_DUMP_STATUS_FIELD(f) \
	pr_err(#f "=0x%x\n", status->f)

#define DMA_READ_ONLY_MODE  0444
#define DMA_READ_WRITE_MODE 0664
#define DMA_WRITE_ONLY_MODE 0220
#define DMA_MIN_READ_BUFFER_REMINING_SIZE (500)
#define ECPRI_DMA_MIN_DEST_ENDP (37)

struct ecpri_dma_debugfs_file {
	const char *name;
	umode_t mode;
	void *data;
	const struct file_operations fops;
};

static struct dentry *dent;
static char dbg_buff[DMA_MAX_MSG_LEN + 1];

extern struct ecpri_dma_qmi_context* ecpri_dma_qmi_ctx;
extern struct ecpri_dma_context* ecpri_dma_ctx;

extern struct ecpri_dma_eth_client_endp_mapping
	eth_client_endp_map[ECPRI_HW_MAX][ECPRI_HW_FLAVOR_MAX]
	[ECPRI_DMA_ETH_CLIENT_MAX_CONNTECTIONS];

static s8 ep_reg_idx = 0;
static s8 ep_reg_gsi_idx = 0;
static s8 dev_connection = 0;
static s8 dev_port = 0;
static s8 dev_link = 0;

static bool is_read_in_progress = true;


static ssize_t ecpri_dma_write_ep_reg(struct file *file, const char __user *buf,
		size_t count, loff_t *ppos)
{
	s8 ep;
	s8 gsi;
	unsigned long missing;
	char *sptr, *token;

	/* Veriy debug buffer has enough space*/
	if (count >= sizeof(dbg_buff))
		return -EINVAL;

	/* Copy user data to debug buffer */
	missing = copy_from_user(dbg_buff, buf, count);
	if (missing)
		return -EFAULT;

	/* Terminate debug buffer */
	dbg_buff[count] = '\0';

	/* Point to debug buffer */
	sptr = dbg_buff;

	/* Split intput by delimiter token*/
	token = strsep(&sptr, " ");
	if (!token)
		return -EINVAL;

	/* Convert endp string to number */
	if (kstrtos8(token, 0, &gsi))
		return -EINVAL;

	/* Convert GSI string to number */
	if (kstrtos8(sptr, 0, &ep))
		return -EINVAL;

	if (ep >= (s8)ecpri_dma_ctx->ecpri_dma_num_endps) {
		DMAERR("bad endp specified %d\n", ep);
		return count;
	}

	if (gsi >= (s8)ecpri_dma_ctx->num_of_gsi) {
		DMAERR("bad gsi specified %d\n", gsi);
		return count;
	}

	DMAERR("Recieved ep %d and gsi %d\n", ep, gsi);
	ep_reg_idx = ep;
	ep_reg_gsi_idx = gsi;

	return count;
}

/**
 * ecpri_dma_read_ep_reg_n() - Reads and prints endpoint configuration registers
 *
 * Returns the number of characters printed
 */
int ecpri_dma_read_ep_reg_n(char *buf, int max_len, int gsi_id, int endp)
{
	int nbytes = 0;

	nbytes += scnprintf(
		buf + nbytes, max_len,
		"ECPRI_DMA_ECPRI_ENDP_CFG_DEST_%u_%u=0x%x\n"
		"ECPRI_DMA_ECPRI_ENDP_CFG_XBAR_%u_%u=0x%x\n"
		"ECPRI_DMA_ECPRI_ENDP_GSI_CFG_%u_%u=0x%x\n",

		gsi_id, endp, ecpri_dma_hal_read_reg_mn(ECPRI_ENDP_CFG_DEST, gsi_id, endp),
		gsi_id, endp, ecpri_dma_hal_read_reg_mn(ECPRI_ENDP_CFG_XBAR, gsi_id, endp),
		gsi_id, endp, ecpri_dma_hal_read_reg_mn(ECPRI_ENDP_GSI_CFG, gsi_id, endp)
		);

	/* V2 registers section */
	if (ecpri_dma_ctx->ecpri_hw_ver < ECPRI_HW_V2_0)
		return nbytes;

	if (endp >= ECPRI_DMA_MIN_DEST_ENDP)
		nbytes += scnprintf(buf + nbytes, max_len,
			"ECPRI_DMA_ENDP_LTE_CFG_GSI_%u_%u=0x%x\n",
			gsi_id, endp, ecpri_dma_hal_read_reg_mn(
				ECPRI_DMA_ENDP_LTE_CFG_GSI_m_CH_n, gsi_id, endp));

	return nbytes;
}

static ssize_t ecpri_dma_read_ep_reg(struct file *file, char __user *ubuf,
		size_t count, loff_t *ppos)
{
	int nbytes;
	static int i, j;
	static int endp_start, endp_end;
	static int gsi_start, gsi_end;
	int ret = 0;
	loff_t pos = 0;
	bool break_loop = false;

	/* Set read ranges in the first access to read */
	if (is_read_in_progress == true) {

		if (ep_reg_idx < 0) {
			endp_start = 0;
			endp_end = ecpri_dma_ctx->ecpri_dma_num_endps - 1;
			gsi_start = 0;
			gsi_end = ecpri_dma_ctx->num_of_gsi - 1;

		} else {
			endp_start = ep_reg_idx;
			endp_end = endp_start;
			gsi_start = ep_reg_gsi_idx;
			gsi_end = gsi_start;
		}

		is_read_in_progress = false;
	}

	/* Initialize byte counter */
	nbytes = 0;

	/* Initialize loop break signal */
	break_loop = false;

	/* Get register values */
	for (j = gsi_start; j <= gsi_end; j++) {
		for (i = endp_start; i <= endp_end; i++) {
			nbytes +=
				ecpri_dma_read_ep_reg_n(
					dbg_buff + nbytes, count - nbytes, j, i);

			/* Check if we are running out of space */
			if ((count - nbytes) < DMA_MIN_READ_BUFFER_REMINING_SIZE) {
				break_loop = true;
				break;
			}
		}

		if (break_loop) {
			break;
		}
	}

	/* Check if read finsihed */
	if (nbytes == 0) {

		/* Reset read operation */
		is_read_in_progress = true;
		return 0;
	}

	/* Save last indexes  */
	endp_start = i + 1;
	gsi_start = j;

	/* Copy to user buffer */
	ret = simple_read_from_buffer(ubuf, nbytes + 1, &pos, dbg_buff, count);

	/* Check returned value */
	if (ret < 0) {
		DMAERR("Read from buffer failed\n");
		return ret;
	}

	/* Advance pointer */
	*ppos += ret;

	return ret;
}

static ssize_t ecpri_dma_read_exception(struct file *file, char __user *ubuf,
		size_t count, loff_t *ppos)
{
	int nbytes = 0;
	int cnt = 0;
	int i;
	u32 num_of_pkts_received;
	u32 num_of_bytes_received;
	u32 *exception_status_statistics_ptr;
	struct ecpri_dma_endp_context* except_endp = NULL;

	/* Verify context pointer */
	if (NULL == ecpri_dma_ctx) {
		DMAERR("ecpri_dma_ctx pointer is NULL");
		return -EINVAL;
	}

	if (!is_read_in_progress) {
		is_read_in_progress = true;
		return 0;
	}

	num_of_pkts_received =
		ecpri_dma_ctx->exception_ctx.exception_stats.num_of_pkts_received;

	num_of_bytes_received =
		ecpri_dma_ctx->exception_ctx.exception_stats.num_of_bytes_received;

	exception_status_statistics_ptr =
		ecpri_dma_ctx->exception_ctx.exception_stats.exception_status_statistics;

	/* Get exception endpoint */
	except_endp =
		&ecpri_dma_ctx->endp_ctx \
		[ecpri_dma_ctx->exception_ctx.exception_endp.gsi_id]
		[ecpri_dma_ctx->exception_ctx.exception_endp.endp_id];

	nbytes += scnprintf(dbg_buff + nbytes, count - nbytes,
		"Exception endpoint ID: %d GSI ID: %d GSI Channel: %d EE: %d\n",
			except_endp->endp_id,
			except_endp->gsi_id,
			except_endp->gsi_ep_cfg->dma_gsi_chan_num,
			except_endp->gsi_ep_cfg->ee);

	nbytes += scnprintf(dbg_buff + nbytes, count - nbytes,
		"Histogram of packet errors:\n");

	for (i = 0; i < ECPRI_DMA_STATUS_CODE_MAX; i ++) {

		/* Skip if exception is not defined */
		if (NULL == ecpri_dma_status_code_to_str(i))
			continue;

		/* Skip if no exception*/
		if (0 == exception_status_statistics_ptr[i])
			continue;

		nbytes += scnprintf(dbg_buff + nbytes, count,
			"%s: %d\n", ecpri_dma_status_code_to_str(i),
			 exception_status_statistics_ptr[i]);
	}

	nbytes += scnprintf(dbg_buff + nbytes, count - nbytes,
		"Number of exception packets received: %d\n", num_of_pkts_received);

	nbytes += scnprintf(dbg_buff + nbytes, count - nbytes,
		"Total of received bytes: %d\n", num_of_bytes_received);

	/* Copy data to user buffer */
	cnt = simple_read_from_buffer(ubuf, nbytes + 1, ppos, dbg_buff, count);

	is_read_in_progress = false;
	return cnt;
}

static ssize_t ecpri_dma_link_stat_write(struct file *file, const char __user *buf,
		size_t count, loff_t *ppos)
{
	s8 dev;
	int links_per_port = 4;
	unsigned long missing;
	const char * dev_str = "eth";

	/* Veriy debug buffer has enough space*/
	if (count >= sizeof(dbg_buff))
		return -EINVAL;

	/* Copy user data to debug buffer */
	missing = copy_from_user(dbg_buff, buf, count);
	if (missing) {
		DMAERR("Failed to read user input\n");
		return count;
	}

	/* Terminate debug buffer */
	dbg_buff[count] = '\0';

	/* Convert device string to number */
	if (kstrtos8(&dbg_buff[strlen(dev_str)], 0, &dev)) {
		DMAERR("Failed to convert device string to number\n");
		return count;
	}

	/* Extract port and link of the device */
	dev_port = dev / 10;
	dev_link = dev % 10;

	if (dev_port  < 0 || dev_link < 0) {
		DMAERR("Bad params specified port: %d link: %d\n", dev_port, dev_link);
		dev_connection = -EINVAL;
		return count;
	}

	if ((dev_link >= links_per_port) || (dev_link + dev_port * links_per_port) >= 12) {
		DMAERR("Invalid link port combination link: %d port: %d", dev_link, dev_port);
		dev_connection = -EINVAL;
		return count;
	}

	/* Calculate connection entry */
	dev_connection = dev_link + (dev_port * links_per_port);

	/* Reset file read */
	is_read_in_progress = true;

	return count;
}

static ssize_t ecpri_dma_link_stat_read(struct file *file, char __user *ubuf,
		size_t count, loff_t *ppos)
{
	int nbytes = 0;
	int cnt = 0;
	int hw_ver;
	int hw_flavor;
	struct ecpri_dma_eth_client_endp_mapping *current_map = NULL;
	struct ecpri_dma_endp_context* tx_endp = NULL;
	struct ecpri_dma_endp_context* rx_endp = NULL;

	/* Exit on repeated call */
	if (!is_read_in_progress) {
		is_read_in_progress = true;
		return 0;
	}

	/* Verify connection */
	if (is_read_in_progress) {
		if (-EINVAL == dev_connection) {
			nbytes += scnprintf(dbg_buff + nbytes, count - nbytes,
				"Wrong device provided\n");

			cnt = simple_read_from_buffer(ubuf, nbytes + 1,
				ppos, dbg_buff, count);

			is_read_in_progress = false;

			return cnt;
		}
	}

	/* Get HW */
	hw_ver = ecpri_dma_ctx->ecpri_hw_ver;

	/* Get flavor */
	hw_flavor = ecpri_dma_ctx->hw_flavor;

	/* Get endpoint mapping for the link */
	current_map = &eth_client_endp_map[hw_ver][hw_flavor][dev_connection];

	/* Get link's tx endpoint */
	tx_endp =
		&ecpri_dma_ctx->endp_ctx \
		[current_map->tx_endp.gsi_id][current_map->tx_endp.endp_id];

	/* Get link's rx endpoint */
	rx_endp =
		&ecpri_dma_ctx->endp_ctx \
		[current_map->rx_endp.gsi_id][current_map->rx_endp.endp_id];

	nbytes += scnprintf(dbg_buff + nbytes, count - nbytes,
		"DMA ENDPs associated with eth%d%d stats:\n", dev_port, dev_link);

	nbytes += scnprintf(dbg_buff + nbytes, count - nbytes,
		"Packets sent: %d received: %d\n",
		tx_endp->total_pkts_sent, rx_endp->total_pkts_recv);

	nbytes += scnprintf(dbg_buff + nbytes, count - nbytes,
		"Bytes sent: %d received: %d\n",
		 tx_endp->total_bytes_sent, rx_endp->total_bytes_recv);

	nbytes += scnprintf(dbg_buff + nbytes, count - nbytes,
		"Tx endpoint ID: %d GSI ID: %d GSI Channel: %d EE: %d\n",
			tx_endp->endp_id,
			tx_endp->gsi_id,
			tx_endp->gsi_ep_cfg->dma_gsi_chan_num,
			tx_endp->gsi_ep_cfg->ee);

	nbytes += scnprintf(dbg_buff + nbytes, count - nbytes,
		"Rx endpoint ID: %d GSI ID: %d GSI channel: %d EE: %d\n",
			rx_endp->endp_id,
			rx_endp->gsi_id,
			rx_endp->gsi_ep_cfg->dma_gsi_chan_num,
			rx_endp->gsi_ep_cfg->ee);

	/* Copy data to user buffer */
	cnt = simple_read_from_buffer(ubuf, nbytes + 1, ppos, dbg_buff, count);

	is_read_in_progress = false;
	return cnt;
}

static ssize_t ecpri_dma_read_qmi_info(struct file *file, char __user *ubuf,
		size_t count, loff_t *ppos)
{
	int nbytes = 0;
	int cnt = 0;

	/* Exit on repeated call */
	if (!is_read_in_progress) {
		is_read_in_progress = true;
		return 0;
	}

	nbytes += scnprintf(dbg_buff + nbytes, count, "QMI info:\n");

	nbytes += scnprintf(dbg_buff + nbytes, count,
		"send_q6_init: %d\n", ecpri_dma_qmi_ctx->send_q6_init);

	nbytes += scnprintf(dbg_buff + nbytes, count,
		"q6_registered: %d\n", ecpri_dma_qmi_ctx->q6_registered);

	nbytes += scnprintf(dbg_buff + nbytes, count,
		"q6_init_sent: %d\n", ecpri_dma_qmi_ctx->q6_init_sent);

	nbytes += scnprintf(dbg_buff + nbytes, count,
		"sending_retries: %d\n", ecpri_dma_qmi_ctx->sending_retries);

	nbytes += scnprintf(dbg_buff + nbytes, count,
		"q6_response_recv: %d\n", ecpri_dma_qmi_ctx->q6_response_recv);

	nbytes += scnprintf(dbg_buff + nbytes, count,
		"q6_indication_recv: %d\n", ecpri_dma_qmi_ctx->q6_indication_recv);

	nbytes += scnprintf(dbg_buff + nbytes, count,
		"q6_disconnected: %d\n",  ecpri_dma_qmi_ctx->q6_disconnected);

	nbytes += scnprintf(dbg_buff + nbytes, count,
		"wq_stop: %d\n",
		ecpri_dma_qmi_ctx->wq_stop);

	nbytes += scnprintf(dbg_buff + nbytes, count,
		"q6_init_cmplt: %d\n",  ecpri_dma_qmi_ctx->q6_init_cmplt);

	/* Copy data to user buffer */
	cnt = simple_read_from_buffer(ubuf, nbytes + 1, ppos, dbg_buff, count);

	is_read_in_progress = false;
	return cnt;
}

static ssize_t ecpri_dma_read_dma_stat(struct file *file, char __user *ubuf,
		size_t count, loff_t *ppos)
{
	int nbytes = 0;
	int cnt = 0;
	int m, n;

	if (!is_read_in_progress) {
		is_read_in_progress = true;
		return 0;
	}

	/* Verify HW version */
	if (ecpri_dma_ctx->ecpri_hw_ver < ECPRI_HW_V2_0) {

		nbytes += scnprintf(dbg_buff + nbytes, count,
			"DMA stats registers are only availble in Lassen V2 and above\n");

		cnt = simple_read_from_buffer(ubuf, nbytes, ppos, dbg_buff, count);

		is_read_in_progress = false;

		return cnt;
	}

	nbytes += scnprintf(dbg_buff + nbytes, count- nbytes,
	"ECPRI_DMA_STATUS_XBAR_FH_PORT_RX=0x%x\n",
	ecpri_dma_hal_read_reg(ECPRI_DMA_STATUS_XBAR_FH_PORT_RX));

	nbytes += scnprintf(dbg_buff + nbytes, count- nbytes,
	"ECPRI_DMA_STATUS_XBAR_FH_PORT_TX=0x%x\n",
	ecpri_dma_hal_read_reg(ECPRI_DMA_STATUS_XBAR_FH_PORT_TX));

	nbytes += scnprintf(dbg_buff + nbytes, count- nbytes,
	"ECPRI_DMA_STATUS_XBAR_C2C_PORT_RX=0x%x\n",
	ecpri_dma_hal_read_reg(ECPRI_DMA_STATUS_XBAR_C2C_PORT_RX));

	nbytes += scnprintf(dbg_buff + nbytes, count- nbytes,
	"ECPRI_DMA_STATUS_XBAR_C2C_PORT_TX=0x%x\n",
	ecpri_dma_hal_read_reg(ECPRI_DMA_STATUS_XBAR_C2C_PORT_TX));

	nbytes += scnprintf(dbg_buff + nbytes, count- nbytes,
	"ECPRI_DMA_STATUS_GSI0_A=0x%x\n",
	ecpri_dma_hal_read_reg(ECPRI_DMA_STATUS_GSI0_A));

	nbytes += scnprintf(dbg_buff + nbytes, count- nbytes,
	"ECPRI_DMA_STATUS_GSI0_B=0x%x\n",
	ecpri_dma_hal_read_reg(ECPRI_DMA_STATUS_GSI0_B));

	nbytes += scnprintf(dbg_buff + nbytes, count- nbytes,
	"ECPRI_DMA_STATUS_GSI1_A=0x%x\n",
	ecpri_dma_hal_read_reg(ECPRI_DMA_STATUS_GSI1_A));

	nbytes += scnprintf(dbg_buff + nbytes, count- nbytes,
	"ECPRI_DMA_STATUS_GSI1_B=0x%x\n",
	ecpri_dma_hal_read_reg(ECPRI_DMA_STATUS_GSI1_B));

	nbytes += scnprintf(dbg_buff + nbytes, count- nbytes,
	"ECPRI_DMA_STATUS_GSI2_A=0x%x\n",
	ecpri_dma_hal_read_reg(ECPRI_DMA_STATUS_GSI2_A));

	nbytes += scnprintf(dbg_buff + nbytes, count- nbytes,
	"ECPRI_DMA_STATUS_GSI2_B=0x%x\n",
	ecpri_dma_hal_read_reg(ECPRI_DMA_STATUS_GSI2_B));

	nbytes += scnprintf(dbg_buff + nbytes, count - nbytes,
	"ECPRI_DMA_STATUS_XBAR_RX_DROP=0x%x\n",
	ecpri_dma_hal_read_reg(ECPRI_DMA_STATUS_XBAR_RX_DROP));

	nbytes += scnprintf(dbg_buff + nbytes, count- nbytes,
	"ECPRI_DMA_STATUS_LTE_PKT_DROP_FULL=0x%x\n",
	ecpri_dma_hal_read_reg(ECPRI_DMA_STATUS_LTE_PKT_DROP_FULL));

	nbytes += scnprintf(dbg_buff + nbytes, count - nbytes,
	"ECPRI_STATUS_PKT_DROP_FULL=0x%x\n",
	ecpri_dma_hal_read_reg(ECPRI_STATUS_PKT_DROP_FULL));

	nbytes += scnprintf(dbg_buff + nbytes, count - nbytes,
	"ECPRI_DMA_STATUS_PKT_DROP_TLV_FIFO_EMPTY=0x%x\n",
	ecpri_dma_hal_read_reg(ECPRI_DMA_STATUS_PKT_DROP_TLV_FIFO_EMPTY));

	nbytes += scnprintf(dbg_buff + nbytes, count - nbytes,
	"ECPRI_DMA_STATUS_DST_DROP_PKT_CLEAR=0x%x\n",
	ecpri_dma_hal_read_reg(ECPRI_DMA_STATUS_DST_DROP_PKT_CLEAR));

	nbytes += scnprintf(dbg_buff + nbytes, count - nbytes,
	"ECPRI_DMA_STATUS_LTE_PKT_DROP_TLV_FIFO_EMPTY=0x%x\n",
	ecpri_dma_hal_read_reg(ECPRI_DMA_STATUS_LTE_PKT_DROP_TLV_FIFO_EMPTY));

	for (m=0; m <= ecpri_dma_hal_get_reg_max_n(ECPRI_DMA_STATUS_XBAR_RX_PORT_m); m++)
		nbytes += scnprintf(dbg_buff + nbytes, count - nbytes,
		"ECPRI_DMA_STATUS_XBAR_RX_PORT_%d=0x%x\n", m,
		ecpri_dma_hal_read_reg_n(ECPRI_DMA_STATUS_XBAR_RX_PORT_m, m));

	for (m = 0; m <= ecpri_dma_hal_get_reg_max_m(ECPRI_DMA_STATUS_DST_DROP_PKT_GSI_m_REG_n); m++)
		for (n = 0; n <= ecpri_dma_hal_get_reg_max_n(ECPRI_DMA_STATUS_DST_DROP_PKT_GSI_m_REG_n); n++)
			nbytes += scnprintf(dbg_buff + nbytes, count - nbytes,
			"ECPRI_DMA_STATUS_DST_DROP_PKT_GSI_%d_REG_%d=0x%x\n", m, n,
			ecpri_dma_hal_read_reg_mn(ECPRI_DMA_STATUS_DST_DROP_PKT_GSI_m_REG_n, m, n));

	/* Copy data to user buffer */
	cnt = simple_read_from_buffer(ubuf, nbytes + 1, ppos, dbg_buff, count);

	is_read_in_progress = false;
	return cnt;
}

static const struct ecpri_dma_debugfs_file debugfs_files[] = {
	{
		"ep_reg", DMA_READ_WRITE_MODE, NULL, {
			.read = ecpri_dma_read_ep_reg,
			.write = ecpri_dma_write_ep_reg,
		}
	}, {
		"exception", DMA_READ_ONLY_MODE, NULL, {
			.read = ecpri_dma_read_exception,
		}
	},{
		"linkstat", DMA_READ_WRITE_MODE, NULL, {
			.read = ecpri_dma_link_stat_read,
			.write = ecpri_dma_link_stat_write
		}
	}, {
		"qmi", DMA_READ_ONLY_MODE, NULL, {
			.read = ecpri_dma_read_qmi_info,
		},
	},{
		"dma_stat", DMA_READ_ONLY_MODE, NULL, {
			.read = ecpri_dma_read_dma_stat,
		},
	},
};

void ecpri_dma_debugfs_init(void)
{
	const size_t debugfs_files_num =
		sizeof(debugfs_files) / sizeof(struct ecpri_dma_debugfs_file);
	size_t i;
	struct dentry *file;

	dent = debugfs_create_dir("ecpri_dma", NULL);
	if (IS_ERR(dent)) {
		DMAERR("fail to create folder in debug_fs.\n");
		return;
	}

	debugfs_create_u32("ecpri_hw_ver", DMA_READ_ONLY_MODE,
		dent, &ecpri_dma_ctx->ecpri_hw_ver);

	debugfs_create_u32("hw_flavor", DMA_READ_ONLY_MODE,
		dent, &ecpri_dma_ctx->hw_flavor);

	for (i = 0; i < debugfs_files_num; ++i) {
		const struct ecpri_dma_debugfs_file *curr = &debugfs_files[i];

		file = debugfs_create_file(curr->name, curr->mode, dent,
			curr->data, &curr->fops);
		if (!file || IS_ERR(file)) {
			DMAERR("fail to create file for debug_fs %s\n",
				curr->name);
			goto fail;
		}
	}

	return;

fail:
	debugfs_remove_recursive(dent);
}

void ecpri_dma_debugfs_remove(void)
{
	if (IS_ERR(dent)) {
		DMAERR("Debugfs:folder was not created.\n");
		return;
	}
	debugfs_remove_recursive(dent);
}

struct dentry *ecpri_dma_debugfs_get_root(void)
{
	return dent;
}
EXPORT_SYMBOL(ecpri_dma_debugfs_get_root);

#else /* !CONFIG_DEBUG_FS */
#define INVALID_NO_OF_CHAR (-1)
void ecpri_dma_debugfs_init(void) {}
void ecpri_dma_debugfs_remove(void) {}
#endif
