// SPDX-License-Identifier: GPL-2.0-only

/*
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include <linux/debugfs.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/types.h>
#include <net/xfrm.h>

#include "eip_macsec.h"
#include "eip_ipsec.h"
#include "eip_debugfs.h"
#include "eip_log.h"
#include "eip_device.h"
#include "api_cfye.h"
#include "api_cfye_ext.h"
#include "api_secy_ext.h"
#include "api_secy_types.h"
#include "eip_debugfs.h"
#include "eip_macsec.h"
#include "eip_log.h"
#include "macsec_eth.h"
#include "eip_device.h"

#define EIP_DEBUGFS_ROOT_DIRNAME "secure_eip"
#define MAX_KBUFF_SIZE (PAGE_SIZE * 64)
char max_kbuff[MAX_KBUFF_SIZE];

struct eip_debugfs_file_attr {
	const char *name;
	umode_t mode;
	const struct file_operations fops;
};

const char *const col_title[] = {
	"ID",	 "Ctrl",  "SA Upd", "Key0", "Key1", "Key2",
	"Key3",	 "Key4",  "Key5",   "Key6", "Key7", "Hkey0",
	"Hkey1", "Hkey2", "Hkey3",  "Seq0", "Seq1", "MTU/MASK",
	"ISO",	 "ISI",	  "IS2",    "IV0",  "IV1",
};

#define COL_HEAD_LEN ARRAY_SIZE(col_title)
#define SA_WORD_START 0
#define SA_WORD_END 24
#define TABLE_MAX_WIDTH 12
#define TR_KEYS_START_IDX 3
#define TR_KEYS_END_IDX 14

#define CHECK_NULL(x) ((x) ? (x) : 0)
#define IS_KEY(i, s, e) ((i) >= (s) && ((i) <= (e)))
#define GET_XFRM_SPI_ID(x) x->xs->id.spi

static struct dentry *root;

static void __print_data_tabular_format(char *buffer, size_t buffer_size,
					const char *const column_headers[],
					uint32_t **row_data, int num_columns,
					unsigned int num_rows)
{
	int i, j;
	int offset = 0, bytes_written;

	// Print the header row.
	for (i = 0; i < num_columns; i++) {
		bytes_written =
			snprintf(buffer + offset, buffer_size - offset, "%-*s",
				 TABLE_MAX_WIDTH, column_headers[i]);
		offset += bytes_written;
	}
	snprintf(buffer + offset, buffer_size - offset, "\n");
	offset += 1;

	// Print the data rows.
	for (i = 0; i < num_rows; i++) {
		for (j = 0; j < num_columns; j++) {
			if (IS_KEY(j, TR_KEYS_START_IDX, TR_KEYS_END_IDX)) {
#ifdef DRIVER_IPSEC_DEBUG
				bytes_written =
					snprintf(buffer + offset,
						 buffer_size - offset, "%-*X",
						 TABLE_MAX_WIDTH,
						 CHECK_NULL(row_data[i][j]));
#else
				bytes_written =
					snprintf(buffer + offset,
						 buffer_size - offset, "%-*s",
						 TABLE_MAX_WIDTH, "********");
#endif
			} else {
				bytes_written =
					snprintf(buffer + offset,
						 buffer_size - offset, "%-*X",
						 TABLE_MAX_WIDTH,
						 CHECK_NULL(row_data[i][j]));
			}
			offset += bytes_written;
		}
		snprintf(buffer + offset, buffer_size - offset, "\n");
		offset += 1;
	}
}

static ssize_t __read_secy_diag_device_dump(struct file *file,
					    char __user *ubuf, size_t count,
					    loff_t *ppos)
{
	SecY_Status_t SecY_Rc;
	struct eip_datapath *dp_ctx = (struct eip_datapath *)file->private_data;

	SecY_Rc = SecY_Diag_Device_Dump(dp_ctx->devid);
	if (SecY_Rc != SECY_STATUS_OK) {
		eip_logerr("SecY_Dump Status: failed");
		return -EIO;
	}
	return 0;
}

static ssize_t __read_secy_diag_channel_dump(struct file *file,
					     char __user *ubuf, size_t count,
					     loff_t *ppos)
{
	SecY_Status_t SecY_Rc;
	struct eip_datapath *dp_ctx = (struct eip_datapath *)file->private_data;

	SecY_Rc = SecY_Diag_Channel_Dump(dp_ctx->devid, 0, true);
	if (SecY_Rc != SECY_STATUS_OK) {
		eip_logerr("SecY_Dump Status: failed");
		return -EIO;
	}
	return 0;
}

static ssize_t __read_secy_diag_vport_dump(struct file *file, char __user *ubuf,
					   size_t count, loff_t *ppos)
{
	SecY_Status_t SecY_Rc;
	struct eip_datapath *dp_ctx = (struct eip_datapath *)file->private_data;

	SecY_Rc = SecY_Diag_vPort_Dump(dp_ctx->devid, 0, true, true);
	if (SecY_Rc != SECY_STATUS_OK) {
		eip_logerr("SecY_Dump Status: failed");
		return -EIO;
	}
	return 0;
}

static ssize_t __read_secy_diag_sa_dump(struct file *file, char __user *ubuf,
					size_t count, loff_t *ppos)
{
	SecY_Status_t SecY_Rc;
	struct eip_datapath *dp_ctx = (struct eip_datapath *)file->private_data;

	SecY_Rc = SecY_Diag_SA_Dump(dp_ctx->devid, SecY_SAHandle_NULL, true);
	if (SecY_Rc != SECY_STATUS_OK) {
		eip_logerr("SecY_Dump Status: failed");
		return -EIO;
	}
	return 0;
}

static ssize_t __read_cfye_diag_device_dump(struct file *file,
					    char __user *ubuf, size_t count,
					    loff_t *ppos)
{
	CfyE_Status_t CfyE_Rc;
	struct eip_datapath *dp_ctx = (struct eip_datapath *)file->private_data;

	CfyE_Rc = CfyE_Diag_Device_Dump(dp_ctx->devid);
	if (CfyE_Rc != CFYE_STATUS_OK) {
		eip_logerr("CfyE_Dump Status: failed");
		return -EIO;
	}
	return 0;
}

static ssize_t __read_cfye_diag_channel_dump(struct file *file,
					     char __user *ubuf, size_t count,
					     loff_t *ppos)
{
	CfyE_Status_t CfyE_Rc;
	struct eip_datapath *dp_ctx = (struct eip_datapath *)file->private_data;

	CfyE_Rc = CfyE_Diag_Channel_Dump(dp_ctx->devid, 0, true);
	if (CfyE_Rc != CFYE_STATUS_OK) {
		eip_logerr("CfyE_Dump Status: failed");
		return -EIO;
	}
	return 0;
}

static ssize_t __read_cfye_diag_vport_dump(struct file *file, char __user *ubuf,
					   size_t count, loff_t *ppos)
{
	CfyE_Status_t CfyE_Rc;
	struct eip_datapath *dp_ctx = (struct eip_datapath *)file->private_data;

	CfyE_Rc = CfyE_Diag_vPort_Dump(dp_ctx->devid, CfyE_vPortHandle_NULL,
				       true, true);
	if (CfyE_Rc != CFYE_STATUS_OK) {
		eip_logerr("CfyE_Dump Status: failed");
		return -EIO;
	}
	return 0;
}

static ssize_t __read_cfye_diag_rule_dump(struct file *file, char __user *ubuf,
					  size_t count, loff_t *ppos)
{
	CfyE_Status_t CfyE_Rc;
	struct eip_datapath *dp_ctx = (struct eip_datapath *)file->private_data;

	CfyE_Rc =
		CfyE_Diag_Rule_Dump(dp_ctx->devid, CfyE_vPortHandle_NULL, true);

	if (CfyE_Rc != CFYE_STATUS_OK) {
		eip_logerr("CfyE_Dump Status: failed");
		return -EIO;
	}
	return 0;
}

static ssize_t __read_ch_tr_dump(struct file *file, char __user *ubuf,
				 size_t count, loff_t *ppos)
{
	struct eip_datapath *dp_ctx = (struct eip_datapath *)file->private_data;
	int i;
	static int data_size = 0;
	unsigned int max_sa_cnt = 0;
	SecY_Status_t SecY_Rc;
	uint32_t **tr_table;
	unsigned int avail_sa_cnt = 0;
	SecY_SAHandle_t sa_h_prev = SecY_SAHandle_NULL, sa_h_curr;
	unsigned int sa_index;

	if (*ppos == 0) {
		memset(max_kbuff, 0, sizeof(max_kbuff));
	}

	if (*ppos >= MAX_KBUFF_SIZE)
		return 0;

	SecY_Rc = SecY_Device_Limits(dp_ctx->devid, NULL, NULL, &max_sa_cnt,
				     NULL);
	if (SecY_Rc != SECY_STATUS_OK) {
		eip_logerr("SecY_Device_Limits returned error %d", SecY_Rc);
		return -EIO;
	}
	tr_table =
		(uint32_t **)kzalloc(max_sa_cnt * sizeof(uint32_t), GFP_KERNEL);
	if (!tr_table)
		return -ENOMEM;

	for (i = 0; i < max_sa_cnt; ++i) {
		SecY_Rc =
			SecY_SA_Next_Get(dp_ctx->devid, sa_h_prev, &sa_h_curr);
		if (SecY_Rc != SECY_STATUS_OK) {
			eip_logerr("SecY_SA_Next_Get returned error %d",
				   SecY_Rc);
			return -EIO;
		}

		if (!SecY_SAHandle_IsSame(&sa_h_curr, &SecY_SAHandle_NULL)) {
			tr_table[i] = (uint32_t *)kzalloc(25 * sizeof(uint32_t),
							  GFP_KERNEL);
			if (!tr_table[i])
				return -ENOMEM;

			SecY_Rc = SecY_SA_Read(dp_ctx->devid, sa_h_curr,
					       SA_WORD_START, SA_WORD_END,
					       &tr_table[i][1]);
			if (SecY_Rc != SECY_STATUS_OK) {
				eip_logerr("SecY_SA_Read returned error %d",
					   SecY_Rc);
				return -EIO;
			}

			SecY_SAIndex_Get(sa_h_curr, &sa_index, NULL);
			tr_table[i][0] = sa_index;
			sa_h_prev = sa_h_curr;
			avail_sa_cnt++;
		} else {
			//No more SA available to read
			break;
		}
	}
	__print_data_tabular_format(max_kbuff, MAX_KBUFF_SIZE, col_title,
				    tr_table, COL_HEAD_LEN, avail_sa_cnt);
	data_size = strlen(max_kbuff);

	if (copy_to_user(ubuf, (max_kbuff + *ppos), count)) {
		eip_logerr("copy_to_user failed");
		return -EIO;
	}

	if ((*ppos + count) > data_size)
		count = data_size - *ppos;

	*ppos += count;

	for (i = 0; i < avail_sa_cnt; ++i) {
		if (tr_table[i])
			kfree(tr_table[i]);
	}
	kfree(tr_table);

	return count;
}

static ssize_t __read_ch_ipsec_spi_dump(struct file *file, char __user *ubuf,
					size_t count, loff_t *ppos)
{
	static int data_size = 0;
	struct eip_xfrm_state *eip_xs;
	struct eip_channel *ch_ctx = (struct eip_channel *)file->private_data;
	int offset = 0;
	int bytes_written;
	struct eip_ipsec_link *ilink = ndev_to_ipsec(ch_ctx->ndev);

	if (*ppos == 0) {
		memset(max_kbuff, 0, sizeof(max_kbuff));
	}

	if (*ppos >= MAX_KBUFF_SIZE)
		return 0;

	bytes_written = scnprintf(max_kbuff + offset, MAX_KBUFF_SIZE - offset,
				  "%-*s%-*s\n", TABLE_MAX_WIDTH, "SPI ID",
				  TABLE_MAX_WIDTH, "SA Index");
	offset += bytes_written;

	read_lock(&ilink->lock);
	list_for_each_entry (eip_xs, &ilink->eip_xs_l, eip_xs_l) {
		if (ch_ctx->inbound == eip_xs->inbound) {
			bytes_written =
				scnprintf(max_kbuff + offset,
					  MAX_KBUFF_SIZE - offset,
					  "0x%-*X%-*d\n", TABLE_MAX_WIDTH,
					  GET_XFRM_SPI_ID(eip_xs),
					  TABLE_MAX_WIDTH, eip_xs->sa_index);
			offset += bytes_written;
		}
	}
	read_unlock(&ilink->lock);

	data_size = strlen(max_kbuff);

	if (copy_to_user(ubuf, (max_kbuff + *ppos), count)) {
		eip_logerr("copy_to_user failed");
		return -EIO;
	}

	if ((*ppos + count) > data_size)
		count = data_size - *ppos;

	*ppos += count;

	return count;
}

static const struct eip_debugfs_file_attr eip_debugfs_dump_files[] = {
	{ "SecY_Diag_Device_Dump",
	  S_IRUSR | S_IRGRP,
	  {
		  .open = simple_open,
		  .read = __read_secy_diag_device_dump,
		  .owner = THIS_MODULE,
		  .llseek = default_llseek,
	  } },
	{ "SecY_Diag_Channel_Dump",
	  S_IRUSR | S_IRGRP,
	  {
		  .open = simple_open,
		  .read = __read_secy_diag_channel_dump,
		  .owner = THIS_MODULE,
		  .llseek = default_llseek,
	  } },
	{ "SecY_Diag_vPort_Dump",
	  S_IRUSR | S_IRGRP,
	  {
		  .open = simple_open,
		  .read = __read_secy_diag_vport_dump,
		  .owner = THIS_MODULE,
		  .llseek = default_llseek,
	  } },
	{ "SecY_Diag_SA_Dump",
	  S_IRUSR | S_IRGRP,
	  {
		  .open = simple_open,
		  .read = __read_secy_diag_sa_dump,
		  .owner = THIS_MODULE,
		  .llseek = default_llseek,
	  } },
	{ "CfyE_Diag_Device_Dump",
	  S_IRUSR | S_IRGRP,
	  {
		  .open = simple_open,
		  .read = __read_cfye_diag_device_dump,
		  .owner = THIS_MODULE,
		  .llseek = default_llseek,
	  } },
	{ "CfyE_Diag_Channel_Dump",
	  S_IRUSR | S_IRGRP,
	  {
		  .open = simple_open,
		  .read = __read_cfye_diag_channel_dump,
		  .owner = THIS_MODULE,
		  .llseek = default_llseek,
	  } },
	{ "CfyE_Diag_vPort_Dump",
	  S_IRUSR | S_IRGRP,
	  {
		  .open = simple_open,
		  .read = __read_cfye_diag_vport_dump,
		  .owner = THIS_MODULE,
		  .llseek = default_llseek,
	  } },
	{ "CfyE_Diag_Rule_Dump",
	  S_IRUSR | S_IRGRP,
	  {
		  .open = simple_open,
		  .read = __read_cfye_diag_rule_dump,
		  .owner = THIS_MODULE,
		  .llseek = default_llseek,
	  } },
	{ "transform_records",
	  S_IRUSR | S_IRGRP,
	  {
		  .open = simple_open,
		  .read = __read_ch_tr_dump,
		  .owner = THIS_MODULE,
		  .llseek = default_llseek,
	  } },
};

static const size_t NUM_OF_DUMP_FILE = ARRAY_SIZE(eip_debugfs_dump_files);

static const struct eip_debugfs_file_attr
	eip_debugfs_link_attr = { .name = "ipsec_sas",
				  .mode = S_IRUSR | S_IRGRP,
				  .fops = {
					  .open = simple_open,
					  .read = __read_ch_ipsec_spi_dump,
					  .owner = THIS_MODULE,
					  .llseek = default_llseek,
				  } };

int eip_debugfs_init(void)
{
	root = debugfs_create_dir(EIP_DEBUGFS_ROOT_DIRNAME, NULL);
	if (IS_ERR_OR_NULL(root)) {
		eip_logerr(" Failed for creating entry under debugfs");
		return -EINVAL;
	}
	return 0;
}

void eip_debugfs_deinit(void)
{
	debugfs_remove_recursive(root);
	root = NULL;
	eip_loginfo("Secure EIP debugfs removed successfully");
}

static int create_dump_files(struct eip_port *port, const char *dir_name,
			     void *ctx)
{
	size_t i = 0;
	struct dentry *file;
	struct eip_datapath *dp = (struct eip_datapath *)ctx;

	dp->dbgfs_dp_dent = debugfs_create_dir(dir_name, port->dbgfs_dent);
	if (IS_ERR_OR_NULL(dp->dbgfs_dp_dent)) {
		eip_logerr("Failed to create directory: %s", dir_name);
		return -EINVAL;
	}
	for (i = 0; i < NUM_OF_DUMP_FILE; ++i) {
		const struct eip_debugfs_file_attr *file_info =
			&eip_debugfs_dump_files[i];

		file = debugfs_create_file(file_info->name, file_info->mode,
					   dp->dbgfs_dp_dent, ctx,
					   &file_info->fops);
		if (IS_ERR_OR_NULL(file)) {
			eip_logerr(
				"failed to create file for debug_fs under %s",
				file_info->name);
			return -EINVAL;
		}
	}
	return 0;
}

int eip_debugfs_add_port(struct eip_port *port)
{
	char dir_name_buff[DNAME_INLINE_LEN] = { 0 };
	int ret = 0;

	snprintf(dir_name_buff, DNAME_INLINE_LEN, "port%d", port->id);

	port->dbgfs_dent = debugfs_create_dir(dir_name_buff, root);
	if (IS_ERR_OR_NULL(port->dbgfs_dent)) {
		eip_logerr("Failed to create directory %s", dir_name_buff);
		return -EINVAL;
	}

	ret = create_dump_files(port, "rx", &port->rx);
	if (ret) {
		eip_logerr("Failed to create file attr \"rx\" %s",
			   dir_name_buff);
		goto fail_dbgfs_dent;
	}

	ret = create_dump_files(port, "tx", &port->tx);
	if (ret) {
		eip_logerr("Failed to create file attr \"tx\" %s",
			   dir_name_buff);
		goto fail_dbgfs_dent;
	}
	return 0;

fail_dbgfs_dent:
	debugfs_remove_recursive(port->dbgfs_dent);

	return -EINVAL;
}

void eip_debugfs_remove_port(struct eip_port *port)
{
	debugfs_remove_recursive(port->dbgfs_dent);
	port->dbgfs_dent = NULL;
}

int eip_debugfs_add_link(struct eip_link *link)
{
	int ret = 0;
	char dir_name_buff[DNAME_INLINE_LEN] = { 0 };
	struct dentry *tmp;
	struct eip_channel *rx = &link->rx;
	struct eip_channel *tx = &link->tx;

	snprintf(dir_name_buff, DNAME_INLINE_LEN, "ch-%d", rx->ch);
	rx->dbgfs_ch_dent =
		debugfs_create_dir(dir_name_buff, rx->dp->dbgfs_dp_dent);
	if (IS_ERR_OR_NULL(rx->dbgfs_ch_dent)) {
		eip_logerr("Failed to create directory %s", dir_name_buff);
		return -EINVAL;
	}
	tmp = debugfs_create_file(eip_debugfs_link_attr.name,
				  eip_debugfs_link_attr.mode, rx->dbgfs_ch_dent,
				  rx, &eip_debugfs_link_attr.fops);
	if (IS_ERR_OR_NULL(tmp)) {
		eip_logerr("failed to create file for debug_fs under %s",
			   eip_debugfs_link_attr.name);
		return -EINVAL;
	}

	snprintf(dir_name_buff, DNAME_INLINE_LEN, "ch-%d", tx->ch);
	tx->dbgfs_ch_dent =
		debugfs_create_dir(dir_name_buff, tx->dp->dbgfs_dp_dent);
	if (IS_ERR_OR_NULL(tx->dbgfs_ch_dent)) {
		eip_logerr("Failed to create directory %s", dir_name_buff);
		return -EINVAL;
	}
	tmp = debugfs_create_file(eip_debugfs_link_attr.name,
				  eip_debugfs_link_attr.mode, tx->dbgfs_ch_dent,
				  tx, &eip_debugfs_link_attr.fops);
	if (IS_ERR_OR_NULL(tmp)) {
		eip_logerr("failed to create file for debug_fs under %s",
			   eip_debugfs_link_attr.name);
		return -EINVAL;
	}
	return ret;
}

void eip_debugfs_remove_link(struct eip_link *link)
{
	struct eip_channel *rx = &link->rx;
	struct eip_channel *tx = &link->tx;

	debugfs_remove_recursive(rx->dbgfs_ch_dent);
	rx->dbgfs_ch_dent = NULL;

	debugfs_remove_recursive(tx->dbgfs_ch_dent);
	tx->dbgfs_ch_dent = NULL;
}
