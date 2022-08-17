/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/* global includes */

#include <ecpri_oxtor_debugfs.h>
#include <linux/debugfs.h> /* debugfs addition*/
#include <linux/file.h>
#include <linux/fs.h>

#include "code.h"

#undef pr_fmt
#define pr_fmt(fmt) "::%s:%d::" fmt, __func__, __LINE__

struct dentry *list_dv[64];
char input_string[] = TREE;

/*
 * only white listed alphbates are allowed
 * { } , 0 to 9 a to z A to Z
 */
/*****************************************************************************/
void remove_whitespaces(char *str) {
		int i, j;
		for (i = 0, j = 0; str[i] != '\0'; i++) {
				if ((str[i] >= 'a' && str[i] <= 'z') ||
					(str[i] >= 'A' && str[i] <= 'Z') ||
					(str[i] >= '0' && str[i] <= '9') || (str[i] == '}') ||
					(str[i] == '{') || (str[i] == ',') || (str[i] == '_') ||
					(str[i] == ':')) {
						str[j++] = str[i];
				}
		}
		str[j] = 0;
}
char parser(char *source, char *delim, char *token, int *index) {
		int i, j, k;

		if (!source || !token || !delim)
				return 0;

		memset(token, 0, 64);
		for (i = *index, j = 0; source[i] != 0; i++) {
				for (k = 0; delim[k] != 0; k++) {
						if (source[i] == delim[k]) {
								if (strlen(token) == 0) {
										continue;
								}
								*index = i++;
								return delim[k];
						}
				}
				token[j++] = source[i];
		}
		return 0;
}
void remove_firstchar(char *str) {
		int i;
		int len;

		if (!str)
				return;
		len = strlen(str);

		for (i = 0; i < len; i++) {
				str[i] = str[i + 1];
		}
		return;
}
void get_file_name(char *filename) {

		int index;
		char token[64];
		int i;
		int iscoln = 0;
		for (i = 0; filename[i] != 0 || i < 64; i++) {
				if (filename[i] == ':') {
						iscoln = 1;
						break;
				}
		}
		if (!iscoln)
				return;

		if (!filename)
				return;
		parser(filename, ":", token, &index);
		parser(filename, ":", token, &index);
		remove_firstchar(token);
		scnprintf(filename, sizeof(token), "%s", token);
		return;
}

ssize_t stats_value_from_registers_oxtor_rx(char __user *buf, int ring_id) {

		char *final_stats_str = NULL;
		char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE] = "";
		uint64_t temp_stat_val = 0;
		uint64_t ret_val = 0;

		final_stats_str =
			(char *)kzalloc(FINAL_STATS_DYNAMIC_STR_MAX_SIZE, GFP_KERNEL);

		if (!final_stats_str) {
				pr_err("Memory allocation failure \n");
				goto err;
		}
		RESET_STR(temp_stat_val_str);
		memset(&temp_stat_val, 0, sizeof(temp_stat_val));
		ecpriss_oxtor_hal_read_reg_n_fields(ECPRI_ORAN_XTOR_RX_n_CTL_REG,
											ring_id, &temp_stat_val);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
				  temp_stat_val);
		strlcat(final_stats_str, "ECPRI_ORAN_XTOR_RX_n_CTL_REG:",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		memset(&temp_stat_val, 0, sizeof(temp_stat_val));
		ecpriss_oxtor_hal_read_reg_n_fields(ECPRI_ORAN_XTOR_RX_n_PKT_CNT_REG,
											ring_id, &temp_stat_val);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
				  temp_stat_val);
		strlcat(final_stats_str, "ECPRI_ORAN_XTOR_RX_n_PKT_CNT_REG:",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		memset(&temp_stat_val, 0, sizeof(temp_stat_val));
		ecpriss_oxtor_hal_read_reg_n_fields(ECPRI_ORAN_XTOR_RX_n_KBYTE_CNT_REG,
											ring_id, &temp_stat_val);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
				  temp_stat_val);
		strlcat(final_stats_str, "ECPRI_ORAN_XTOR_RX_n_KBYTE_CNT_REG:",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		memset(&temp_stat_val, 0, sizeof(temp_stat_val));
		ecpriss_oxtor_hal_read_reg_n_fields(ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL,
											ring_id, &temp_stat_val);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
				  temp_stat_val);
		strlcat(final_stats_str, "ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL:",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		memset(&temp_stat_val, 0, sizeof(temp_stat_val));
		ecpriss_oxtor_hal_read_reg_n_fields(
			ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_0, ring_id,
			&temp_stat_val);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
				  temp_stat_val);
		strlcat(final_stats_str, "ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_0:",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		memset(&temp_stat_val, 0, sizeof(temp_stat_val));
		ecpriss_oxtor_hal_read_reg_n_fields(
			ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_1, ring_id,
			&temp_stat_val);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
				  temp_stat_val);
		strlcat(final_stats_str, "ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_1:",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		memset(&temp_stat_val, 0, sizeof(temp_stat_val));
		ecpriss_oxtor_hal_read_reg_n_fields(
			ECPRI_ORAN_XTOR_RX_n_MAX_LATENCY_EXPECTED, ring_id, &temp_stat_val);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
				  temp_stat_val);
		strlcat(final_stats_str, "ECPRI_ORAN_XTOR_RX_n_MAX_LATENCY_EXPECTED:",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		memset(&temp_stat_val, 0, sizeof(temp_stat_val));
		ecpriss_oxtor_hal_read_reg_n_fields(ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB,
											ring_id, &temp_stat_val);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
				  temp_stat_val);
		strlcat(final_stats_str, "ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB:",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		memset(&temp_stat_val, 0, sizeof(temp_stat_val));
		ecpriss_oxtor_hal_read_reg_n_fields(ECPRI_ORAN_XTOR_RX_n_ERROR_REG,
											ring_id, &temp_stat_val);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
				  temp_stat_val);
		strlcat(final_stats_str, "ECPRI_ORAN_XTOR_RX_n_ERROR_REG:",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		memset(&temp_stat_val, 0, sizeof(temp_stat_val));
		ecpriss_oxtor_hal_read_reg_n_fields(
			ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG, ring_id, &temp_stat_val);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
				  temp_stat_val);
		strlcat(final_stats_str, "ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG:",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		memset(&temp_stat_val, 0, sizeof(temp_stat_val));
		ecpriss_oxtor_hal_read_reg_n_fields(
			ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_1_REG, ring_id, &temp_stat_val);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
				  temp_stat_val);
		strlcat(final_stats_str, "ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_1_REG:",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		memset(&temp_stat_val, 0, sizeof(temp_stat_val));
		ecpriss_oxtor_hal_read_reg_n_fields(
			ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_2_REG, ring_id, &temp_stat_val);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
				  temp_stat_val);
		strlcat(final_stats_str, "ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_2_REG:",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		memset(&temp_stat_val, 0, sizeof(temp_stat_val));
		ecpriss_oxtor_hal_read_reg_n_fields(
			ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_3_REG, ring_id, &temp_stat_val);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
				  temp_stat_val);
		strlcat(final_stats_str, "ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_3_REG:",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		memset(&temp_stat_val, 0, sizeof(temp_stat_val));
		ecpriss_oxtor_hal_read_reg_n_fields(
			ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG, ring_id,
			&temp_stat_val);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
				  temp_stat_val);
		strlcat(final_stats_str, "ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG:",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		memset(&temp_stat_val, 0, sizeof(temp_stat_val));
		ecpriss_oxtor_hal_read_reg_n_fields(ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0,
											ring_id, &temp_stat_val);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
				  temp_stat_val);
		strlcat(final_stats_str, "ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0:",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		memset(&temp_stat_val, 0, sizeof(temp_stat_val));
		ecpriss_oxtor_hal_read_reg_n_fields(ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1,
											ring_id, &temp_stat_val);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
				  temp_stat_val);
		strlcat(final_stats_str, "ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1:",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		pr_err("DUMPING Saptarsi : %s \n", final_stats_str);

		ret_val = copy_to_user(buf, final_stats_str,
							   FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		ret_val = strlen(final_stats_str);
		kfree(final_stats_str);
		final_stats_str = NULL;
		return ret_val;
err:
		kfree(final_stats_str);
		return 0;
}

ssize_t stats_value_from_registers_oxtor_tx(char __user *buf, int ring_id) {

		char *final_stats_str = NULL;
		char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE] = "";
		uint32_t temp_stat_val = 0;
		uint32_t ret_val = 0;

		final_stats_str =
			(char *)kzalloc(FINAL_STATS_DYNAMIC_STR_MAX_SIZE, GFP_KERNEL);

		if (!final_stats_str) {
				pr_err("Memory allocation failure \n");
				goto err;
		}
		RESET_STR(temp_stat_val_str);
		memset(&temp_stat_val, 0, sizeof(temp_stat_val));
		ecpriss_oxtor_hal_read_reg_n_fields(ECPRI_ORAN_XTOR_TX_n_CTL_REG,
											ring_id, &temp_stat_val);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
				  temp_stat_val);
		strlcat(final_stats_str, "{ECPRI_ORAN_XTOR_TX_n_CTL_REG:",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		memset(&temp_stat_val, 0, sizeof(temp_stat_val));
		ecpriss_oxtor_hal_read_reg_n_fields(ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG,
											ring_id, &temp_stat_val);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
				  temp_stat_val);
		strlcat(final_stats_str, "ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG:",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		memset(&temp_stat_val, 0, sizeof(temp_stat_val));
		ecpriss_oxtor_hal_read_reg_n_fields(ECPRI_ORAN_XTOR_TX_n_PKT_CNT_REG,
											ring_id, &temp_stat_val);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
				  temp_stat_val);
		strlcat(final_stats_str, "ECPRI_ORAN_XTOR_TX_n_PKT_CNT_REG:",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		memset(&temp_stat_val, 0, sizeof(temp_stat_val));
		ecpriss_oxtor_hal_read_reg_n_fields(
			ECPRI_ORAN_XTOR_TX_n_BACKPRESSURE_CNT_REG, ring_id, &temp_stat_val);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
				  temp_stat_val);
		strlcat(final_stats_str, "ECPRI_ORAN_XTOR_TX_n_BACKPRESSURE_CNT_REG:",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		memset(&temp_stat_val, 0, sizeof(temp_stat_val));
		ecpriss_oxtor_hal_read_reg_n_fields(
			ECPRI_ORAN_XTOR_TX_n_RD_IDX_WRAP_CNT, ring_id, &temp_stat_val);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
				  temp_stat_val);
		strlcat(final_stats_str, "ECPRI_ORAN_XTOR_TX_n_RD_IDX_WRAP_CNT:",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		ret_val = copy_to_user(buf, final_stats_str,
							   FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		ret_val = strlen(final_stats_str);
		kfree(final_stats_str);
		final_stats_str = NULL;
		return ret_val;
err:
		kfree(final_stats_str);
		return 0;
}

ssize_t error_value_from_registers_oxtor_rx(char __user *buf, int ring_id) {
		return 0;
		// No error value from TX_OXTOR_REGISTERS REQUIRED
}

ssize_t error_value_from_registers_oxtor_tx(char __user *buf, int ring_id) {
		return 0;
		// No error value from TX_OXTOR_REGISTERS REQUIRED
}

static ssize_t stats_value_from_registers_oxtor_tx_0(struct file *file,
													 char __user *buf,
													 size_t count,
													 loff_t *ppos) {
		uint32_t len;
		len = stats_value_from_registers_oxtor_tx(buf, 0);
		if ((*ppos + count) > len) {
				count = len - *ppos;
		}
		*ppos += count;

		return count;
}

static ssize_t stats_value_from_registers_oxtor_tx_1(struct file *file,
													 char __user *buf,
													 size_t count,
													 loff_t *ppos) {
		uint32_t len;
		len = stats_value_from_registers_oxtor_tx(buf, 1);
		if ((*ppos + count) > len) {
				count = len - *ppos;
		}
		*ppos += count;

		return count;
}

static ssize_t stats_value_from_registers_oxtor_tx_2(struct file *file,
													 char __user *buf,
													 size_t count,
													 loff_t *ppos) {
		uint32_t len;
		len = stats_value_from_registers_oxtor_tx(buf, 2);
		if ((*ppos + count) > len) {
				count = len - *ppos;
		}
		*ppos += count;

		return count;
}

static ssize_t stats_value_from_registers_oxtor_tx_3(struct file *file,
													 char __user *buf,
													 size_t count,
													 loff_t *ppos) {
		uint32_t len;
		len = stats_value_from_registers_oxtor_tx(buf, 3);
		if ((*ppos + count) > len) {
				count = len - *ppos;
		}
		*ppos += count;

		return count;
}

static ssize_t error_value_from_registers_oxtor_tx_0(struct file *file,
													 char __user *buf,
													 size_t count,
													 loff_t *ppos) {
		uint32_t len;
		len = error_value_from_registers_oxtor_tx(buf, 0);
		if ((*ppos + count) > len) {
				count = len - *ppos;
		}
		*ppos += count;

		return count;
}

static ssize_t error_value_from_registers_oxtor_tx_1(struct file *file,
													 char __user *buf,
													 size_t count,
													 loff_t *ppos) {
		uint32_t len;
		len = error_value_from_registers_oxtor_tx(buf, 1);
		if ((*ppos + count) > len) {
				count = len - *ppos;
		}
		*ppos += count;

		return count;
}

static ssize_t error_value_from_registers_oxtor_tx_2(struct file *file,
													 char __user *buf,
													 size_t count,
													 loff_t *ppos) {
		uint32_t len;
		len = error_value_from_registers_oxtor_tx(buf, 2);
		if ((*ppos + count) > len) {
				count = len - *ppos;
		}
		*ppos += count;

		return count;
}

static ssize_t error_value_from_registers_oxtor_tx_3(struct file *file,
													 char __user *buf,
													 size_t count,
													 loff_t *ppos) {
		uint32_t len;
		len = error_value_from_registers_oxtor_tx(buf, 3);
		if ((*ppos + count) > len) {
				count = len - *ppos;
		}
		*ppos += count;

		return count;
}

static ssize_t stats_value_from_registers_oxtor_rx_0(struct file *file,
													 char __user *buf,
													 size_t count,
													 loff_t *ppos) {
		uint32_t len;
		len = stats_value_from_registers_oxtor_rx(buf, 0);
		if ((*ppos + count) > len) {
				count = len - *ppos;
		}
		*ppos += count;

		return count;
}

static ssize_t stats_value_from_registers_oxtor_rx_1(struct file *file,
													 char __user *buf,
													 size_t count,
													 loff_t *ppos) {
		uint32_t len;
		len = stats_value_from_registers_oxtor_rx(buf, 1);
		if ((*ppos + count) > len) {
				count = len - *ppos;
		}
		*ppos += count;

		return count;
}

static ssize_t stats_value_from_registers_oxtor_rx_2(struct file *file,
													 char __user *buf,
													 size_t count,
													 loff_t *ppos) {
		uint32_t len;
		len = stats_value_from_registers_oxtor_rx(buf, 2);
		if ((*ppos + count) > len) {
				count = len - *ppos;
		}
		*ppos += count;

		return count;
}

static ssize_t stats_value_from_registers_oxtor_rx_3(struct file *file,
													 char __user *buf,
													 size_t count,
													 loff_t *ppos) {
		uint32_t len;
		len = stats_value_from_registers_oxtor_rx(buf, 3);
		if ((*ppos + count) > len) {
				count = len - *ppos;
		}
		*ppos += count;

		return count;
}

static ssize_t error_value_from_registers_oxtor_rx_0(struct file *file,
													 char __user *buf,
													 size_t count,
													 loff_t *ppos) {
		uint32_t len;
		len = error_value_from_registers_oxtor_rx(buf, 0);
		if ((*ppos + count) > len) {
				count = len - *ppos;
		}
		*ppos += count;

		return count;
}

static ssize_t error_value_from_registers_oxtor_rx_1(struct file *file,
													 char __user *buf,
													 size_t count,
													 loff_t *ppos) {
		uint32_t len;
		len = error_value_from_registers_oxtor_rx(buf, 1);
		if ((*ppos + count) > len) {
				count = len - *ppos;
		}
		*ppos += count;

		return count;
}

static ssize_t error_value_from_registers_oxtor_rx_2(struct file *file,
													 char __user *buf,
													 size_t count,
													 loff_t *ppos) {
		uint32_t len;
		len = error_value_from_registers_oxtor_rx(buf, 2);
		if ((*ppos + count) > len) {
				count = len - *ppos;
		}
		*ppos += count;

		return count;
}

static ssize_t error_value_from_registers_oxtor_rx_3(struct file *file,
													 char __user *buf,
													 size_t count,
													 loff_t *ppos) {
		uint32_t len;
		len = error_value_from_registers_oxtor_rx(buf, 3);
		if ((*ppos + count) > len) {
				count = len - *ppos;
		}
		*ppos += count;

		return count;
}

static struct file_operations stats_oxtor_tx_0 = {
	.read = stats_value_from_registers_oxtor_tx_0,
};
static struct file_operations stats_oxtor_tx_1 = {
	.read = stats_value_from_registers_oxtor_tx_1,
};
static struct file_operations stats_oxtor_tx_2 = {
	.read = stats_value_from_registers_oxtor_tx_2,
};
static struct file_operations stats_oxtor_tx_3 = {
	.read = stats_value_from_registers_oxtor_tx_3,
};
static struct file_operations interrupts_oxtor_tx_0 = {
	.read = error_value_from_registers_oxtor_tx_0,
};
static struct file_operations interrupts_oxtor_tx_1 = {
	.read = error_value_from_registers_oxtor_tx_1,
};
static struct file_operations interrupts_oxtor_tx_2 = {
	.read = error_value_from_registers_oxtor_tx_2,
};
static struct file_operations interrupts_oxtor_tx_3 = {
	.read = error_value_from_registers_oxtor_tx_3,
};
static struct file_operations stats_oxtor_rx_0 = {
	.read = stats_value_from_registers_oxtor_rx_0,
};
static struct file_operations stats_oxtor_rx_1 = {
	.read = stats_value_from_registers_oxtor_rx_1,
};
static struct file_operations stats_oxtor_rx_2 = {
	.read = stats_value_from_registers_oxtor_rx_2,
};
static struct file_operations stats_oxtor_rx_3 = {
	.read = stats_value_from_registers_oxtor_rx_3,
};
static struct file_operations interrupts_oxtor_rx_0 = {
	.read = error_value_from_registers_oxtor_rx_0,
};
static struct file_operations interrupts_oxtor_rx_1 = {
	.read = error_value_from_registers_oxtor_rx_1,
};
static struct file_operations interrupts_oxtor_rx_2 = {
	.read = error_value_from_registers_oxtor_rx_2,
};
static struct file_operations interrupts_oxtor_rx_3 = {
	.read = error_value_from_registers_oxtor_rx_3,
};

static struct file_operations dummy;

static struct file_operations *file_name_to_wrapper(char *filename) {
		if (!strncmp(filename, "oxtr:stats:tx0", FH_WRAPPER_SIZE)) {
				return &stats_oxtor_tx_0;
		} else if (!strncmp(filename, "oxtr:interrupts:tx0", FH_WRAPPER_SIZE)) {
				return &interrupts_oxtor_tx_0;
		} else if (!strncmp(filename, "oxtr:stats:tx1", FH_WRAPPER_SIZE)) {
				return &stats_oxtor_tx_1;
		} else if (!strncmp(filename, "oxtr:interrupts:tx1", FH_WRAPPER_SIZE)) {
				return &interrupts_oxtor_tx_1;
		} else if (!strncmp(filename, "oxtr:stats:tx2", FH_WRAPPER_SIZE)) {
				return &stats_oxtor_tx_2;
		} else if (!strncmp(filename, "oxtr:interrupts:tx2", FH_WRAPPER_SIZE)) {
				return &interrupts_oxtor_tx_2;
		} else if (!strncmp(filename, "oxtr:stats:tx3", FH_WRAPPER_SIZE)) {
				return &stats_oxtor_tx_3;
		} else if (!strncmp(filename, "oxtr:interrupts:tx3", FH_WRAPPER_SIZE)) {
				return &interrupts_oxtor_tx_3;
		} else if (!strncmp(filename, "oxtr:stats:rx0", FH_WRAPPER_SIZE)) {
				return &stats_oxtor_rx_0;
		} else if (!strncmp(filename, "oxtr:interrupts:rx0", FH_WRAPPER_SIZE)) {
				return &interrupts_oxtor_rx_0;
		} else if (!strncmp(filename, "oxtr:stats:rx1", FH_WRAPPER_SIZE)) {
				return &stats_oxtor_rx_1;
		} else if (!strncmp(filename, "oxtr:interrupts:rx1", FH_WRAPPER_SIZE)) {
				return &interrupts_oxtor_rx_1;
		} else if (!strncmp(filename, "oxtr:stats:rx2", FH_WRAPPER_SIZE)) {
				return &stats_oxtor_rx_2;
		} else if (!strncmp(filename, "oxtr:interrupts:rx2", FH_WRAPPER_SIZE)) {
				return &interrupts_oxtor_rx_2;
		} else if (!strncmp(filename, "oxtr:stats:rx3", FH_WRAPPER_SIZE)) {
				return &stats_oxtor_rx_3;
		} else if (!strncmp(filename, "oxtr:interrupts:rx3", FH_WRAPPER_SIZE)) {
				return &interrupts_oxtor_rx_3;
		} else {
				pr_err("Invalid file name, no entry available\n");
				return &dummy;
		}
		return NULL;
}

int setup_debugfs_directory(void) {
		char token[64];
		char my_delm;
		int index;
		int len = 0;
		struct file_operations *fileops = NULL;
		struct dentry *kobj_root;
		int curr_index = 0;

		remove_whitespaces(input_string);
		my_delm = parser(input_string, "{},", token, &index);
		while (my_delm != 0) {
				len = strlen(token);

				if (token[0] == '{' && len > 2) {
						remove_firstchar(token);

						if (curr_index == 0) {
								list_dv[curr_index] =
									debugfs_create_dir(token, NULL);
								curr_index++;
						} else {
								kobj_root = debugfs_create_dir(
									token, list_dv[curr_index - 1]);
								list_dv[curr_index] = kobj_root;
								curr_index++;
						}
				} else if (token[0] == '}' && len > 2) {
						remove_firstchar(token);
						curr_index--;
						kobj_root =
							debugfs_create_dir(token, list_dv[curr_index - 1]);
						list_dv[curr_index] = kobj_root;
						curr_index++;
				} else if (token[0] == ',' && len > 2) {
						remove_firstchar(token);
						fileops = file_name_to_wrapper(token);
						get_file_name(token);
						if (!debugfs_create_file(token, 0444,
												 list_dv[curr_index - 1], 0,
												 fileops)) {
						}
				} else if (token[0] == '}' && len < 2) {
						curr_index--;
				}
				my_delm = parser(input_string, "{},", token, &index);
		}
		return 0;
}
