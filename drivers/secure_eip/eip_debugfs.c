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

#include "eip_macsec.h"
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

struct eip_debugfs_file_attr {
	const char *name;
	umode_t mode;
	const struct file_operations fops;
};

static struct dentry *root;

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
};

static const size_t NUM_OF_DUMP_FILE = ARRAY_SIZE(eip_debugfs_dump_files);

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
	struct dentry *file, *local_dir;

	local_dir = debugfs_create_dir(dir_name, port->dbgfs_dent);
	if (IS_ERR_OR_NULL(local_dir)) {
		eip_logerr("Failed to create directory: %s", dir_name);
		return -EINVAL;
	}
	for (i = 0; i < NUM_OF_DUMP_FILE; ++i) {
		const struct eip_debugfs_file_attr *file_info =
			&eip_debugfs_dump_files[i];

		file = debugfs_create_file(file_info->name, file_info->mode,
					   local_dir, ctx, &file_info->fops);
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
