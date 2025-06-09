/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */
#ifndef NO_DEBUGFS_PERF
/* global includes */
#include <linux/fcntl.h>
#include <linux/string.h>
#include <linux/types.h>
#include <linux/slab.h>  /* kmalloc() */
#include <linux/types.h> /* size_t */
#include <linux/fs.h>
#include <linux/file.h>
#include "ecpriss_core.h"
#include "ecpriss_debugfs.h"

#include "debug_dir_struct.h"
#include "ecpriss_log.h"
#include "ecpriss_xbar_hwio_v2.h"

#undef pr_fmt
#define pr_fmt(fmt) "::%s:%u::" fmt, __func__, __LINE__

struct dentry *list_dv[64];
char input_string[] = TREE;
#define MAX_STR_SIZE (NUM_OF_FHP * 1000 * 128)
char max_str[MAX_STR_SIZE];

typedef struct{
	char *source;
	char *delim;
	char *token;
	uint32_t *index;
	uint32_t token_len;
	uint32_t delim_len;
	uint32_t source_len;
}parser_s;
int isv2 = 1;

// Debugfs
typedef enum config_param{
	FHRX,
	OCRX,
	C2CRXUL,
	C2CRXDL,
	GLOBAL_CFG
}cfg_prm_u;

uint32_t min_lut_index = 0;
uint32_t max_lut_index = 299;

typedef union msb_mac{
	uint16_t msb_mac;
	uint8_t mac[2];
}ecpriss_msb_mac;

typedef union lsb_mac{
	uint32_t lsb_mac;
	uint8_t mac[4];
}ecpriss_lsb_mac;
typedef union ipv4_addrs{
	uint32_t ipv4;
	uint8_t ip[4];
}ecpriss_ipv4_addr;
/*
 * only white listed alphbates are allowed
 * { } , _  : and 0 to 9 a to z A to Z
 */
/*****************************************************************************/
static void remove_whitespaces(char * str, uint32_t len)
{
        int i,j;

	if(!str){
		ECPRILOGERR("Null pointer Input\n");
		return;
	}
        for(i = 0, j=0; str[i] != '\0'; i++){
		if(i > len){
			ECPRILOGERR("Invalid Input\n");
			return;
		}
                if((str[i] >= 'a' && str[i] <= 'z') ||
                                (str[i] >= 'A' && str[i] <='Z') ||
                                (str[i] >= '0' && str[i] <= '9') ||
                                (str[i] == '}') ||
                                (str[i] == '{') ||
                                (str[i] == ',') ||
				(str[i] == '_') ||
				(str[i] == ':')){
                        str[j++]= str[i];
                }
        }
        str[j] = 0;
}
static char parser(parser_s *parser_in)
{
        int i,j,k;

	if(!parser_in)
		return 0;

        if(!parser_in->source || !parser_in->token || !parser_in->delim)
                return 0;

        memset(parser_in->token, 0, parser_in->token_len);

        for(i= *parser_in->index, j = 0; parser_in->source[i] !=0 ; i++){
		if(j > parser_in->token_len){
			ECPRILOGERR("Invalid token length\n");
			return 0;
		}
		if(i > parser_in->source_len){
			ECPRILOGERR("Invalid Input\n");
			return 0;
		}

                for(k = 0; parser_in->delim[k] !=0; k++){
			if(k > parser_in->delim_len){
				ECPRILOGERR("Invalid Input\n");
				break;
			}
                        if(parser_in->source[i] == parser_in->delim[k]){
                                if(strlen(parser_in->token) == 0){
                                        continue;
                                }
                                *parser_in->index = i++;
                                return parser_in->delim[k];
                        }
                }
                parser_in->token[j++] = parser_in->source[i];

        }
        return 0;
}
static void remove_firstchar(char * str, uint32_t len)
{
	int i;

	if(!str)
		return;

	for(i=0;i<len;i++){
		str[i] = str[i+1];

		if(str[i] == 0)
			break;
	}
	return;

}
static void get_file_name(char *filename, uint32_t len)
{
	int index = 0;
	char token[64];
	int i = 0;
	int iscoln = 0;
	parser_s parser_in;

	if(!filename){
		ECPRILOGERR("Null Pointer Input\n");
		return ;
	}

	for(i=0; len && filename[i] !=0 ;i++){
		if(filename[i] ==  ':'){
			iscoln = 1;
			break;
		}
	}
	if(!iscoln)
		return;

	parser_in.source = filename;
	parser_in.delim = ":";
	parser_in.token = token;
	parser_in.index = &index;
	parser_in.token_len = sizeof(token);
	parser_in.delim_len = 1;
	parser_in.source_len = len;

	parser(&parser_in);
	parser(&parser_in);
	remove_firstchar(token, sizeof(token));
	scnprintf(filename, sizeof(token), "%s", token);
	return;
}

void process_fhrx(int num, char *result, int size){

	char link_id_string[32];
	int slen  = 0;

	memset(link_id_string, '\0', sizeof(link_id_string));
	if((num & HWIO_ECPRI_XBAR_FHRX_m_LUT_n_DL_ROUTE_TO_ORAN_BMSK) != 0){
		scnprintf(link_id_string, sizeof(link_id_string), " DL2OC:Link %d,", (num & HWIO_ECPRI_XBAR_FHRX_m_LUT_n_DL_OC_LINK_ID_BMSK));
		strlcat(result, link_id_string, size);
	}

	if((num & HWIO_ECPRI_XBAR_FHRX_m_LUT_n_DL_ROUTE_TO_C2C_BMSK) != 0)
		strlcat(result, " DL2C2C,", size);

	if((num & HWIO_ECPRI_XBAR_FHRX_m_LUT_n_DL_ROUTE_TO_DMA_BMSK) != 0)
		strlcat(result, " DL2DMA,", size);

	memset(link_id_string, '\0', sizeof(link_id_string));
	if((num & HWIO_ECPRI_XBAR_FHRX_m_LUT_n_UL_ROUTE_TO_ORAN_BMSK) != 0){
		scnprintf(link_id_string, sizeof(link_id_string), " UL2OC:Link %d,", (num & HWIO_ECPRI_XBAR_FHRX_m_LUT_n_UL_OC_LINK_ID_BMSK));
		strlcat(result, link_id_string, size);
	}

	if((num & HWIO_ECPRI_XBAR_FHRX_m_LUT_n_UL_ROUTE_TO_C2C_BMSK) != 0)
		strlcat(result, " UL2C2C,", size);

	if((num & HWIO_ECPRI_XBAR_FHRX_m_LUT_n_UL_ROUTE_TO_DMA_BMSK) != 0)
		strlcat(result, " UL2DMA,", size);

	slen = strlen(result);
	if(slen > 0)
		result[slen-1] = '\0';
}

void process_ocrx(int num, char *result, int size){

	char link_id_string[32];
	int slen  = 0;

	memset(link_id_string, '\0', sizeof(link_id_string));
	if((num & HWIO_ECPRI_XBAR_OCRX_m_LUT_n_VALID_BMSK) != 0){
		scnprintf(link_id_string, sizeof(link_id_string), " L2:index %d,", (num & HWIO_ECPRI_XBAR_OCRX_m_LUT_n_L2_ENCAP_INFO_BMSK));
		strlcat(result, link_id_string, size);

		memset(link_id_string, '\0', sizeof(link_id_string));
		if((num & HWIO_ECPRI_XBAR_OCRX_m_LUT_n_L3_ENCAP_VALID_BMSK) !=  0){
			scnprintf(link_id_string, sizeof(link_id_string), " L3:index %d,", (num & HWIO_ECPRI_XBAR_OCRX_m_LUT_n_L3_ENCAP_INFO_BMSK));
			strlcat(result, link_id_string, size);
		}
	}

	slen = strlen(result);
	if(slen > 0)
		result[slen-1] = '\0';
}

static ssize_t config_val_from_qudp_ecpriss_filt(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	int isvlanfiltenabled = 0;
	static int data_size = 0;
	int ret_val = 0;

	if(*ppos == 0 ) {

		memset(max_str,0,sizeof(max_str));

		isvlanfiltenabled = ecpriss_qudp_get_ecpriss_filt_enable_info();

		if(isvlanfiltenabled) {
			strlcat(max_str, "1\n", MAX_STR_SIZE);
		}else{
			strlcat(max_str, "0\n", MAX_STR_SIZE);
		}
		data_size = strlen(max_str);
	}

	if(*ppos  >= MAX_STR_SIZE)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}

static ssize_t config_val_to_qudp_ecpriss_filt(const char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	int val = -1;

	if(kstrtouint_from_user(buf, *count, TEMP_STR_MAX_SIZE, &val))
		return -EFAULT;

	ecpriss_qudp_set_ecpriss_filt_enable_info(val);

	return *count;
}

static ssize_t config_val_to_global_ecpriss_stats_timeout(const char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	int val = -1;

	if(kstrtouint_from_user(buf, *count, 10, &val))
		return -EFAULT;

	ecpriss_core_set_stats_timeout_info(val);

	return *count;
}
static ssize_t config_val_to_global_ecpriss_enable_len_check(const char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	int val = -1;

	if(kstrtouint_from_user(buf, *count, 10, &val))
		return -EFAULT;

	ecpriss_core_set_enable_len_check_info(val);
	ecpriss_xbar_oc_cfg_enable_len_check_v2(val);
	return *count;
}
static ssize_t config_val_to_qudp_ingress_action(const char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	int val = -1;

	if(kstrtouint_from_user(buf, *count, 10, &val))
		return -EFAULT;

	if(val > ECPRISS_QUDP_ACTION_CONTINUE || val < ECPRISS_QUDP_ACTION_PASS_TO_UC)
		return -EINVAL;

	ecpriss_qudp_set_ingress_action(val);

	return *count;
}
static ssize_t config_val_to_qudp_strict_filt(const char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	int val = -1;

	if(kstrtouint_from_user(buf, *count, 10, &val))
		return -EFAULT;

	if(val < 0 || val > 1)
		return -EINVAL;

	ecpriss_qudp_set_strict_filter_config(val, fh_index);

	return *count;
}
static ssize_t config_val_to_xbar_lut_ocrx(const char __user *buf, size_t *count, loff_t *ppos)
{
	char input_buf[TEMP_STR_MAX_SIZE];
	int min_lut = -1;
	int max_lut = -1;

	if(copy_from_user(input_buf,buf,TEMP_STR_MAX_SIZE)){
		return -EFAULT;
	}


	sscanf(input_buf,"%d-%d",&min_lut,&max_lut);

	min_lut_index = min_lut;
	max_lut_index = max_lut;

	return *count;
}
static ssize_t config_val_to_xbar_lut_fhrx(const char __user *buf, size_t *count, loff_t *ppos)
{
	char input_buf[TEMP_STR_MAX_SIZE];
	int min_lut = -1;
	int max_lut = -1;

	if(copy_from_user(input_buf,buf,TEMP_STR_MAX_SIZE)){
		return -EFAULT;
	}


	sscanf(input_buf,"%d-%d",&min_lut,&max_lut);

	min_lut_index = min_lut;
	max_lut_index = max_lut;


	return *count;
}

static ssize_t config_val_from_global_ecpriss_stats_timeout(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	int stats_timeout = 0;
	static int data_size = 0;
	int ret_val = 0;

	if(*ppos == 0 ) {

		memset(max_str,0,sizeof(max_str));

		stats_timeout = ecpriss_core_get_stats_timeout_info();

		scnprintf(max_str, MAX_STR_SIZE, "%d\n", stats_timeout);
		data_size = strlen(max_str);
	}

	if(*ppos  >= MAX_STR_SIZE)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}

static ssize_t config_val_from_global_ecpriss_enable_len_check(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	int enable_len_check = 0;
	static int data_size = 0;
	int ret_val = 0;

	if(*ppos == 0 ) {

		memset(max_str,0,sizeof(max_str));

		enable_len_check = ecpriss_core_get_enable_len_check_info();

		scnprintf(max_str, MAX_STR_SIZE, "%d\n", enable_len_check);
		data_size = strlen(max_str);
	}

	if(*ppos  >= MAX_STR_SIZE)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}


static ssize_t config_val_from_qudp_ingress_action(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	int action = 0;
	static int data_size = 0;
	int ret_val = 0;

	if(*ppos == 0 ) {

		memset(max_str,0,sizeof(max_str));

		action = ecpriss_qudp_get_ingress_action();

		scnprintf(max_str, MAX_STR_SIZE, "%d\n", action);
		data_size = strlen(max_str);
	}

	if(*ppos  >= MAX_STR_SIZE)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}

static ssize_t config_val_from_qudp_strict_filt(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	int strict_filt_cfg = 0;
	static int data_size = 0;
	int ret_val = 0;

	if(*ppos == 0 ) {

		memset(max_str,0,sizeof(max_str));

		strict_filt_cfg = ecpriss_qudp_get_strict_filter_config(fh_index);

		scnprintf(max_str, MAX_STR_SIZE, "%d\n", strict_filt_cfg);
		data_size = strlen(max_str);
	}

	if(*ppos  >= MAX_STR_SIZE)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}


static ssize_t config_val_from_registers_qudp_ingress_mac_addr(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	char fh_str[TEMP_STR_MAX_SIZE];
	char index_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int max_str_size = MAX_STR_SIZE;
	int fltr_table_index = 0;
	int ret_val = 0;
	static int data_size = 0;

	if(*ppos == 0 ){
		memset(max_str,0,sizeof(max_str));

		RESET_STR(fh_str);
		scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);

		ecpriss_qudp_ingress_config_stats_update(fh_index);

		for(fltr_table_index = 0; fltr_table_index < NUM_OF_FLTR; fltr_table_index++){

			if(ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.mac_addr[fh_index][fltr_table_index].mac_msb.value ||
					ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.mac_addr[fh_index][fltr_table_index].mac_lsb.value){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", fltr_table_index);
				RESET_STR(temp_stat_val_str);
				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
						ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.mac_addr[fh_index][fltr_table_index].mac_msb.value);

				strlcat(max_str, "mac_msb:lsb_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);

				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
						ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.mac_addr[fh_index][fltr_table_index].mac_lsb.value);

				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				strlcat(max_str, "\n",
						max_str_size);

			}

		}
		data_size = strlen(max_str);
		ECPRILOGDBG("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}

static ssize_t config_val_from_registers_qudp_ingress_mac_addr_v2(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	char fh_str[TEMP_STR_MAX_SIZE];
	char index_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int max_str_size = MAX_STR_SIZE;
	int fltr_table_index = 0;
	int ret_val = 0;
	static int data_size = 0;

	if(*ppos == 0 )
	{
		memset(max_str,0,sizeof(max_str));

		RESET_STR(fh_str);
		scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);

		ecpriss_qudp_ingress_config_stats_update_v2(fh_index);

		for(fltr_table_index = 0; fltr_table_index < MAX_MAC_FILTER_ENTRIES; fltr_table_index++){

			if(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.mac_addr[fh_index][fltr_table_index].mac_msb.value ||
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.mac_addr[fh_index][fltr_table_index].mac_lsb.value){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", fltr_table_index);
				RESET_STR(temp_stat_val_str);
				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
						ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.mac_addr[fh_index][fltr_table_index].mac_msb.value);
				/*
				 * First four mac addresses are reserved for NR
				 * mac addr
				 */

				if(fltr_table_index < ECPRISS_MAX_NR_MAC_PER_PORT){
					strlcat(max_str, "NR:",
						max_str_size);
				}else{
					strlcat(max_str, "LTE:",
						max_str_size);
				}
				strlcat(max_str, "mac_msb:lsb_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);

				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
						ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.mac_addr[fh_index][fltr_table_index].mac_lsb.value);

				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				strlcat(max_str, "\n",
						max_str_size);

			}

		}
		data_size = strlen(max_str);
		ECPRILOGDBG("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}


static ssize_t config_val_from_registers_qudp_ingress_dst_ip(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	char fh_str[TEMP_STR_MAX_SIZE];
	char index_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int max_str_size = MAX_STR_SIZE;
	int fltr_table_index = 0;
	int ret_val = 0;
	static int data_size = 0;

	if(*ppos == 0 )
	{
		memset(max_str,0,sizeof(max_str));

		RESET_STR(fh_str);
		scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);

		ecpriss_qudp_ingress_config_stats_update(fh_index);

		for(fltr_table_index = 0; fltr_table_index < NUM_OF_FLTR; fltr_table_index++){

			if(ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.ip_addr[fh_index][fltr_table_index].dst_ip0.value){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", fltr_table_index);
				RESET_STR(temp_stat_val_str);
				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
						ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.ip_addr[fh_index][fltr_table_index].dst_ip0.value);

				strlcat(max_str, "dst_ip_0:1:2:3_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				strlcat(max_str, "\n",
						max_str_size);

				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
						ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.ip_addr[fh_index][fltr_table_index].dst_ip1.value);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);

				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
						ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.ip_addr[fh_index][fltr_table_index].dst_ip2.value);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);

				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
						ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.ip_addr[fh_index][fltr_table_index].dst_ip3.value);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				strlcat(max_str, "\n",
						max_str_size);

			}

		}
		data_size = strlen(max_str);
		ECPRILOGDBG("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}
static ssize_t config_val_from_registers_qudp_ingress_dst_ip_v2(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	char fh_str[TEMP_STR_MAX_SIZE];
	char index_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int max_str_size = MAX_STR_SIZE;
	int fltr_table_index = 0;
	int ret_val = 0;
	static int data_size = 0;
	bool is_ipv4 = false;
	ecpriss_ipv4_addr ipv4_addrs;
	if(*ppos == 0 )
	{
		memset(max_str,0,sizeof(max_str));

		RESET_STR(fh_str);
		scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);

		ecpriss_qudp_ingress_config_stats_update_v2(fh_index);

		for(fltr_table_index = 0; fltr_table_index < NUM_OF_FLTR; fltr_table_index++){

			if(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.ip_addr[fh_index][fltr_table_index].dst_ip0.value){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", fltr_table_index);
				RESET_STR(temp_stat_val_str);
				/*
				 * The assumption here is that if only ip0 is non zero and ip1,ip2 & ip3 are zero, most probably it is a ipv4 address
				 * there are no official ways to validate the ip filter type.
				 * this logic will not work in case of ipv6 addresses like 1::
				 */
				if(!ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.ip_addr[fh_index][fltr_table_index].dst_ip1.value &&
						!ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.ip_addr[fh_index][fltr_table_index].dst_ip2.value &&
						!ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.ip_addr[fh_index][fltr_table_index].dst_ip3.value &&
						ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.ip_addr[fh_index][fltr_table_index].dst_ip0.value ){
					is_ipv4 = true;
					ipv4_addrs.ipv4 = ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.ip_addr[fh_index][fltr_table_index].dst_ip0.value; 
					scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u.%u.%u.%u\n",ipv4_addrs.ip[3],ipv4_addrs.ip[2],ipv4_addrs.ip[1],ipv4_addrs.ip[0]);
				}else{
					scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
							ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.ip_addr[fh_index][fltr_table_index].dst_ip0.value);
				}
				strlcat(max_str, "dst_ip_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				if(!is_ipv4){
					scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
							ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.ip_addr[fh_index][fltr_table_index].dst_ip1.value);
					strlcat(max_str, ":", max_str_size);
					strlcat(max_str, temp_stat_val_str,
							max_str_size);

					scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
							ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.ip_addr[fh_index][fltr_table_index].dst_ip2.value);
					strlcat(max_str, ":", max_str_size);
					strlcat(max_str, temp_stat_val_str,
							max_str_size);

					scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
							ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.ip_addr[fh_index][fltr_table_index].dst_ip3.value);
					strlcat(max_str, ":", max_str_size);
					strlcat(max_str, temp_stat_val_str,
							max_str_size);
				}
				strlcat(max_str, "\n",
						max_str_size);

			}

		}
		data_size = strlen(max_str);
		ECPRILOGDBG("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}


static ssize_t config_val_from_registers_qudp_ingress_udp_clss_port(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	char fh_str[TEMP_STR_MAX_SIZE];
	char index_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int max_str_size = MAX_STR_SIZE;
	int fltr_table_index = 0;
	int ret_val = 0;
	static int data_size = 0;

	if(*ppos == 0 )
	{
		memset(max_str,0,sizeof(max_str));

		RESET_STR(fh_str);
		scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);

		ecpriss_qudp_ingress_config_stats_update(fh_index);

		for(fltr_table_index = 0; fltr_table_index < NUM_OF_FLTR; fltr_table_index++){

			if(ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.udp_clss[fh_index][fltr_table_index].value){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", fltr_table_index);
				RESET_STR(temp_stat_val_str);
				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
						ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.udp_clss[fh_index][fltr_table_index].value);

				strlcat(max_str, "udp_classification_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				strlcat(max_str, "\n",
						max_str_size);
			}

		}
		data_size = strlen(max_str);
		ECPRILOGDBG("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}

static ssize_t config_val_from_registers_qudp_ingress_udp_clss_port_v2(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	char fh_str[TEMP_STR_MAX_SIZE];
	char index_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int max_str_size = MAX_STR_SIZE;
	int fltr_table_index = 0;
	int ret_val = 0;
	static int data_size = 0;

	if(*ppos == 0 )
	{
		memset(max_str,0,sizeof(max_str));

		RESET_STR(fh_str);
		scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);

		ecpriss_qudp_ingress_config_stats_update_v2(fh_index);

		for(fltr_table_index = 0; fltr_table_index < NUM_OF_FLTR; fltr_table_index++){

			if(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.udp_clss[fh_index][fltr_table_index].value){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", fltr_table_index);
				RESET_STR(temp_stat_val_str);
				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
						ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.udp_clss[fh_index][fltr_table_index].value);

				strlcat(max_str, "udp_classification_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				strlcat(max_str, "\n",
						max_str_size);
			}

		}
		data_size = strlen(max_str);
		ECPRILOGDBG("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}


static ssize_t config_val_from_registers_qudp_ingress_vlan(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	char fh_str[TEMP_STR_MAX_SIZE];
	char index_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int max_str_size = MAX_STR_SIZE;
	int fltr_table_index = 0;
	int ret_val = 0;
	static int data_size = 0;

	if(*ppos == 0 )
	{
		memset(max_str,0,sizeof(max_str));

		RESET_STR(fh_str);
		scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);

		ecpriss_qudp_ingress_config_stats_update(fh_index);

		for(fltr_table_index = 0; fltr_table_index < NUM_OF_FLTR; fltr_table_index++){

			if(ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.vlan[fh_index][fltr_table_index].value){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", fltr_table_index);
				RESET_STR(temp_stat_val_str);
				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
						ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.vlan[fh_index][fltr_table_index].value);

				strlcat(max_str, "vlan_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				strlcat(max_str, "\n",
						max_str_size);

			}
		}
		data_size = strlen(max_str);
		ECPRILOGDBG("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}

static ssize_t config_val_from_valid_bits_filt(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	char fh_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int max_str_size = MAX_STR_SIZE;
	int ret_val = 0;
	static int data_size = 0;

	if(*ppos == 0 )
	{
		memset(max_str,0,sizeof(max_str));

		RESET_STR(fh_str);
		scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);

		ecpriss_qudp_ingress_config_stats_update(fh_index);



		RESET_STR(temp_stat_val_str);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%x",
				ecpriss_pdata->cfg_stats.qudp_cfg.ingress.vbits.vlan[fh_index]);

		strlcat(max_str, "vlan_valid_bits_fh_",
				max_str_size);
		strlcat(max_str, fh_str,
				max_str_size);
		strlcat(max_str, ":", max_str_size);
		strlcat(max_str, temp_stat_val_str,
				max_str_size);
		strlcat(max_str, "\n",
				max_str_size);

		RESET_STR(temp_stat_val_str);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%x",
				ecpriss_pdata->cfg_stats.qudp_cfg.ingress.vbits.udp_clss[fh_index]);

		strlcat(max_str, "udp_class_valid_bits_fh_",
				max_str_size);
		strlcat(max_str, fh_str,
				max_str_size);
		strlcat(max_str, ":", max_str_size);
		strlcat(max_str, temp_stat_val_str,
				max_str_size);
		strlcat(max_str, "\n",
				max_str_size);

		RESET_STR(temp_stat_val_str);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%x",
				ecpriss_pdata->cfg_stats.qudp_cfg.ingress.vbits.ip_addr[fh_index]);

		strlcat(max_str, "ipaddr_valid_bits_fh_",
				max_str_size);
		strlcat(max_str, fh_str,
				max_str_size);
		strlcat(max_str, ":", max_str_size);
		strlcat(max_str, temp_stat_val_str,
				max_str_size);
		strlcat(max_str, "\n",
				max_str_size);
#if 0
		RESET_STR(temp_stat_val_str);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
				ecpriss_pdata->cfg_stats.qudp_cfg.ingress.vbits.mac_addr[fh_index]);

		strlcat(max_str, "mac_addr_valid_bits_fh_",
				max_str_size);
		strlcat(max_str, fh_str,
				max_str_size);
		strlcat(max_str, ":", max_str_size);
		strlcat(max_str, temp_stat_val_str,
				max_str_size);
		strlcat(max_str, "\n",
				max_str_size);

#endif

		data_size = strlen(max_str);
		ECPRILOGERR("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;

}

static ssize_t config_val_from_valid_bits_filt_v2(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	char fh_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int max_str_size = MAX_STR_SIZE;
	int ret_val = 0;
	static int data_size = 0;

	if(*ppos == 0 )
	{
		memset(max_str,0,sizeof(max_str));

		RESET_STR(fh_str);
		scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);

		ecpriss_qudp_ingress_config_stats_update_v2(fh_index);



		RESET_STR(temp_stat_val_str);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%x",
				ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.vbits.vlan[fh_index]);

		strlcat(max_str, "vlan_valid_bits_fh_",
				max_str_size);
		strlcat(max_str, fh_str,
				max_str_size);
		strlcat(max_str, ":", max_str_size);
		strlcat(max_str, temp_stat_val_str,
				max_str_size);
		strlcat(max_str, "\n",
				max_str_size);

		RESET_STR(temp_stat_val_str);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%x",
				ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.vbits.udp_clss[fh_index]);

		strlcat(max_str, "udp_class_valid_bits_fh_",
				max_str_size);
		strlcat(max_str, fh_str,
				max_str_size);
		strlcat(max_str, ":", max_str_size);
		strlcat(max_str, temp_stat_val_str,
				max_str_size);
		strlcat(max_str, "\n",
				max_str_size);

		RESET_STR(temp_stat_val_str);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%x",
				ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.vbits.ip_addr[fh_index]);

		strlcat(max_str, "ipaddr_valid_bits_fh_",
				max_str_size);
		strlcat(max_str, fh_str,
				max_str_size);
		strlcat(max_str, ":", max_str_size);
		strlcat(max_str, temp_stat_val_str,
				max_str_size);
		strlcat(max_str, "\n",
				max_str_size);

		RESET_STR(temp_stat_val_str);
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%x",
				ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.vbits.mac_addr[fh_index]);

		strlcat(max_str, "mac_addr_valid_bits_fh_",
				max_str_size);
		strlcat(max_str, fh_str,
				max_str_size);
		strlcat(max_str, ":", max_str_size);
		strlcat(max_str, temp_stat_val_str,
				max_str_size);
		strlcat(max_str, "\n",
				max_str_size);


		data_size = strlen(max_str);
		ECPRILOGERR("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;

}


static ssize_t config_val_from_registers_qudp_ingress_vlan_v2(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	char fh_str[TEMP_STR_MAX_SIZE];
	char index_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int max_str_size = MAX_STR_SIZE;
	int fltr_table_index = 0;
	int ret_val = 0;
	static int data_size = 0;

	if(*ppos == 0 )
	{
		memset(max_str,0,sizeof(max_str));

		RESET_STR(fh_str);
		scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);

		ecpriss_qudp_ingress_config_stats_update_v2(fh_index);

		for(fltr_table_index = 0; fltr_table_index < NUM_OF_FLTR; fltr_table_index++){

			if(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.vlan[fh_index][fltr_table_index].value){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", fltr_table_index);
				RESET_STR(temp_stat_val_str);
				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
						ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.vlan[fh_index][fltr_table_index].value);

				strlcat(max_str, "vlan_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				strlcat(max_str, "\n",
						max_str_size);

			}
		}
		data_size = strlen(max_str);
		ECPRILOGDBG("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}


static ssize_t config_val_from_registers_qudp_ingress_global_cfg(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	char fh_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int max_str_size = MAX_STR_SIZE;
	int ret_val = 0;
	static int data_size = 0;

	if(*ppos == 0 )
	{
		memset(max_str,0,sizeof(max_str));

		RESET_STR(fh_str);
		scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);

		ecpriss_qudp_ingress_config_stats_update(fh_index);


			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[fh_index].enable_ip_dst_filt);

			strlcat(max_str, "enable_ip_dst_filt_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);

			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[fh_index].enable_udp_dst_class);

			strlcat(max_str, "enable_udp_dst_class_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);
			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[fh_index].enable_vlan_filt);

			strlcat(max_str, "enable_vlan_filt_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);

			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[fh_index].enable_ip_len_check);

			strlcat(max_str, "enable_ip_len_check_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);




			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[fh_index].ipv4_cs_err_action);

			strlcat(max_str, "ipv4_cs_err_action_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);



			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[fh_index].udp_cs_err_action);

			strlcat(max_str, "udp_cs_err_action_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);



			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[fh_index].fcs_err_action);

			strlcat(max_str, "fcs_err_action_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);



			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[fh_index].pkt_err_action);

			strlcat(max_str, "pkt_err_action_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);


			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[fh_index].disable_st_and_fw);

			strlcat(max_str, "disable_st_and_fw_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);


			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[fh_index].enable_mac_dst_check);

			strlcat(max_str, "enable_mac_dst_check_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);

			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[fh_index].use_external_not_local_mac_dst);

			strlcat(max_str, "use_external_not_local_mac_dst_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);

			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[fh_index].enable_broadcast_check);

			strlcat(max_str, "enable_broadcast_check_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);

			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[fh_index].last_in_chain);

			strlcat(max_str, "last_in_chain_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);

			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[fh_index].non_local_dst_action);

			strlcat(max_str, "non_local_dst_action_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);

			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[fh_index].enable_shared_filtering_2_links);

			strlcat(max_str, "enable_shared_filtering_2_links_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);

			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[fh_index].enable_shared_filtering_4_links);

			strlcat(max_str, "enable_shared_filtering_4_links_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);

			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[fh_index].enable_eth_padding_removal);

			strlcat(max_str, "enable_eth_padding_removal_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);


		data_size = strlen(max_str);
		ECPRILOGDBG("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}

static ssize_t config_val_from_registers_qudp_ingress_global_cfg_v2(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	char fh_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int max_str_size = MAX_STR_SIZE;
	int ret_val = 0;
	static int data_size = 0;

	if(*ppos == 0 )
	{
		memset(max_str,0,sizeof(max_str));

		RESET_STR(fh_str);
		scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);

		ecpriss_qudp_ingress_config_stats_update_v2(fh_index);


			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].enable_ip_dst_filt);

			strlcat(max_str, "enable_ip_dst_filt_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);

			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].enable_udp_dst_class);

			strlcat(max_str, "enable_udp_dst_class_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);
			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].enable_vlan_filt);

			strlcat(max_str, "enable_vlan_filt_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);

			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].enable_ip_len_check);

			strlcat(max_str, "enable_ip_len_check_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);




			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].ipv4_cs_err_action);

			strlcat(max_str, "ipv4_cs_err_action_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);



			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].udp_cs_err_action);

			strlcat(max_str, "udp_cs_err_action_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);



			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].fcs_err_action);

			strlcat(max_str, "fcs_err_action_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);



			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].pkt_err_action);

			strlcat(max_str, "pkt_err_action_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);


			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].disable_st_and_fw);

			strlcat(max_str, "disable_st_and_fw_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);


			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].enable_mac_dst_check);

			strlcat(max_str, "enable_mac_dst_check_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);

			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].use_external_not_local_mac_dst);

			strlcat(max_str, "use_external_not_local_mac_dst_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);

			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].enable_broadcast_check);

			strlcat(max_str, "enable_broadcast_check_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);

			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].last_in_chain);

			strlcat(max_str, "last_in_chain_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);

			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].non_local_dst_action);

			strlcat(max_str, "non_local_dst_action_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);

			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].enable_shared_filtering_2_links);

			strlcat(max_str, "enable_shared_filtering_2_links_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);

			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].enable_shared_filtering_4_links);

			strlcat(max_str, "enable_shared_filtering_4_links_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);

			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].enable_eth_padding_removal);

			strlcat(max_str, "enable_eth_padding_removal_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);

			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].enable_ip_dst_filt);

			strlcat(max_str, "enable_ip_dst_filt_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);

			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].enable_udp_cs_check);

			strlcat(max_str, "enable_udp_cs_check_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);

			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].ip_filt_miss_action);

			strlcat(max_str, "ip_filt_miss_action_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);

			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].ip_len_err_action);

			strlcat(max_str, "ip_len_err_action_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);

			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].vlan_filt_miss_action);

			strlcat(max_str, "vlan_filt_miss_action_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);



		data_size = strlen(max_str);
		ECPRILOGDBG("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}

static ssize_t config_val_from_registers_qudp_egress_ipv4_cfg_v2(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	char fh_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int max_str_size = MAX_STR_SIZE;
	int ret_val = 0;
	static int data_size = 0;

	if(*ppos == 0 )
	{
		memset(max_str,0,sizeof(max_str));

		RESET_STR(fh_str);
		scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);

		ecpriss_qudp_egress_config_stats_update_v2(fh_index);


			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.ipv4_cfg[fh_index].id);

			strlcat(max_str, "ipv4_id_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);

			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.ipv4_cfg[fh_index].ttl);

			strlcat(max_str, "ipv4_ttl_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);

		data_size = strlen(max_str);
		ECPRILOGDBG("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}

static ssize_t config_val_from_registers_qudp_egress_ipv6_cfg_v2(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	char fh_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int max_str_size = MAX_STR_SIZE;
	int ret_val = 0;
	static int data_size = 0;

	if(*ppos == 0 )
	{
		memset(max_str,0,sizeof(max_str));

		RESET_STR(fh_str);
		scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);

		ecpriss_qudp_egress_config_stats_update_v2(fh_index);


			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.ipv6_cfg[fh_index].hop_limit);

			strlcat(max_str, "ipv6_hop_limit_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);

			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.ipv6_cfg[fh_index].flow_label);

			strlcat(max_str, "ipv6_flow_label_fh_",
					max_str_size);
			strlcat(max_str, fh_str,
					max_str_size);
			strlcat(max_str, ":", max_str_size);
			strlcat(max_str, temp_stat_val_str,
					max_str_size);
			strlcat(max_str, "\n",
					max_str_size);

		data_size = strlen(max_str);
		ECPRILOGDBG("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}
static ssize_t config_val_from_registers_qudp_egress_src_ip_addr(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	char fh_str[TEMP_STR_MAX_SIZE];
	char index_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int max_str_size = MAX_STR_SIZE;
	int egress_table_index = 0;
	int ret_val = 0;
	static int data_size = 0;

	if(*ppos == 0 )
	{
		memset(max_str,0,sizeof(max_str));

		RESET_STR(fh_str);
		scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);

		ecpriss_qudp_egress_config_stats_update(fh_index);

		for(egress_table_index = 0; egress_table_index < NUM_EGRESS_ENTRY; egress_table_index++){
			/*
			 * If it is an ipv4 address then only ip_src0 should be a non zero address i.e 0xce80001:0:0:0.
			 * For it is IPV6 any field can be zero i.e fe80:0:0:325
			 * To display it correctly we should print all four fields
			 * IF any of field is non zero, print all fields.
			 */
			if(ecpriss_pdata->cfg_stats.qudp_cfg.egress.src_ip_addr[fh_index][egress_table_index].ip_src0.value ||
					ecpriss_pdata->cfg_stats.qudp_cfg.egress.src_ip_addr[fh_index][egress_table_index].ip_src1.value ||
					ecpriss_pdata->cfg_stats.qudp_cfg.egress.src_ip_addr[fh_index][egress_table_index].ip_src2.value ||
					ecpriss_pdata->cfg_stats.qudp_cfg.egress.src_ip_addr[fh_index][egress_table_index].ip_src3.value){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", egress_table_index);
				RESET_STR(temp_stat_val_str);
				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
						ecpriss_pdata->cfg_stats.qudp_cfg.egress.src_ip_addr[fh_index][egress_table_index].ip_src0.value);

				strlcat(max_str, "src_ip_addr_0:1:2:3_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);


				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
						ecpriss_pdata->cfg_stats.qudp_cfg.egress.src_ip_addr[fh_index][egress_table_index].ip_src1.value);

				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);


				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
						ecpriss_pdata->cfg_stats.qudp_cfg.egress.src_ip_addr[fh_index][egress_table_index].ip_src2.value);

				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);



				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
						ecpriss_pdata->cfg_stats.qudp_cfg.egress.src_ip_addr[fh_index][egress_table_index].ip_src3.value);

				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				strlcat(max_str, "\n",
						max_str_size);

			}


		}
		data_size = strlen(max_str);
		ECPRILOGDBG("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}

static ssize_t config_val_from_registers_qudp_egress_src_ip_addr_v2(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	char fh_str[TEMP_STR_MAX_SIZE];
	char index_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int max_str_size = MAX_STR_SIZE;
	int egress_table_index = 0;
	int ret_val = 0;
	static int data_size = 0;
	ecpriss_ipv4_addr ipv4_addrs;

	if(*ppos == 0 )
	{
		memset(max_str,0,sizeof(max_str));

		RESET_STR(fh_str);
		scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);

		ecpriss_qudp_egress_config_stats_update_v2(fh_index);

		for(egress_table_index = 0; egress_table_index < NUM_EGRESS_ENTRY; egress_table_index++){
			/*
			 * If it is an ipv4 address then only ip_src0 should be a non zero address i.e 0xce80001:0:0:0.
			 * For it is IPV6 any field can be zero i.e fe80:0:0:325
			 * To display it correctly we should print all four fields
			 * IF any of field is non zero, print all fields.
			 */
			if(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.src_ip_addr[fh_index][egress_table_index].ip_src0.value ||
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.src_ip_addr[fh_index][egress_table_index].ip_src1.value ||
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.src_ip_addr[fh_index][egress_table_index].ip_src2.value ||
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.src_ip_addr[fh_index][egress_table_index].ip_src3.value){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", egress_table_index);
				RESET_STR(temp_stat_val_str);

				if (ECPRISS_ETHERTYPE_IPV4 == ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.vlan_ethertype[fh_index][egress_table_index].ethertype){
					ipv4_addrs.ipv4 = ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.src_ip_addr[fh_index][egress_table_index].ip_src0.value; 
					scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u.%u.%u.%u",ipv4_addrs.ip[3],ipv4_addrs.ip[2],ipv4_addrs.ip[1],ipv4_addrs.ip[0]);
				}else{
					scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
							ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.src_ip_addr[fh_index][egress_table_index].ip_src0.value);
				}

				strlcat(max_str, "src_ip_addr_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);


				if (ECPRISS_ETHERTYPE_IPV6 == ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.vlan_ethertype[fh_index][egress_table_index].ethertype){
					scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
							ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.src_ip_addr[fh_index][egress_table_index].ip_src1.value);

					strlcat(max_str, ":", max_str_size);
					strlcat(max_str, temp_stat_val_str,
							max_str_size);


					scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
							ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.src_ip_addr[fh_index][egress_table_index].ip_src2.value);

					strlcat(max_str, ":", max_str_size);
					strlcat(max_str, temp_stat_val_str,
							max_str_size);



					scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
							ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.src_ip_addr[fh_index][egress_table_index].ip_src3.value);

					strlcat(max_str, ":", max_str_size);
					strlcat(max_str, temp_stat_val_str,
							max_str_size);

				}
				strlcat(max_str, "\n",
						max_str_size);

			}


		}
		data_size = strlen(max_str);
		ECPRILOGDBG("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}


static ssize_t config_val_from_registers_qudp_egress_dst_ip_addr(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	char fh_str[TEMP_STR_MAX_SIZE];
	char index_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int max_str_size = MAX_STR_SIZE;
	int egress_table_index = 0;
	int ret_val = 0;
	static int data_size = 0;

	if(*ppos == 0 )
	{
		memset(max_str,0,sizeof(max_str));

		RESET_STR(fh_str);
		scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);

		ecpriss_qudp_egress_config_stats_update(fh_index);

		for(egress_table_index = 0; egress_table_index < NUM_EGRESS_ENTRY; egress_table_index++){

			if(ecpriss_pdata->cfg_stats.qudp_cfg.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst0.value ||
					ecpriss_pdata->cfg_stats.qudp_cfg.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst1.value ||
					ecpriss_pdata->cfg_stats.qudp_cfg.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst2.value ||
					ecpriss_pdata->cfg_stats.qudp_cfg.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst3.value ){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", egress_table_index);
				RESET_STR(temp_stat_val_str);
				strlcat(max_str, "dst_ip_addr_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);


				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
						ecpriss_pdata->cfg_stats.qudp_cfg.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst1.value);

				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);

				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
						ecpriss_pdata->cfg_stats.qudp_cfg.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst2.value);

				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);

				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
						ecpriss_pdata->cfg_stats.qudp_cfg.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst3.value);

				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				strlcat(max_str, "\n",
						max_str_size);

			}


		}
		data_size = strlen(max_str);
		ECPRILOGDBG("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}
static ssize_t config_val_from_registers_qudp_egress_dst_ip_addr_v2(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	char fh_str[TEMP_STR_MAX_SIZE];
	char index_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int max_str_size = MAX_STR_SIZE;
	int egress_table_index = 0;
	int ret_val = 0;
	static int data_size = 0;
	ecpriss_ipv4_addr ipv4_addrs;
	if(*ppos == 0 )
	{
		memset(max_str,0,sizeof(max_str));

		RESET_STR(fh_str);
		scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);

		ecpriss_qudp_egress_config_stats_update_v2(fh_index);

		for(egress_table_index = 0; egress_table_index < NUM_EGRESS_ENTRY; egress_table_index++){

			if(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst0.value ||
				ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst1.value ||
				ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst2.value ||
				ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst3.value ){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", egress_table_index);
				RESET_STR(temp_stat_val_str);

				if (ECPRISS_ETHERTYPE_IPV4 == ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.vlan_ethertype[fh_index][egress_table_index].ethertype){
					ipv4_addrs.ipv4 = ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst0.value; 
					scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u.%u.%u.%u",ipv4_addrs.ip[3],ipv4_addrs.ip[2],ipv4_addrs.ip[1],ipv4_addrs.ip[0]);
				}else{
					scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
							ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst0.value);
				}
				strlcat(max_str, "dst_ip_addr_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, ": ", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);

				if (ECPRISS_ETHERTYPE_IPV6 == ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.vlan_ethertype[fh_index][egress_table_index].ethertype){

					scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
							ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst1.value);

					strlcat(max_str, ":", max_str_size);
					strlcat(max_str, temp_stat_val_str,
							max_str_size);

					scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
							ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst2.value);

					strlcat(max_str, ":", max_str_size);
					strlcat(max_str, temp_stat_val_str,
							max_str_size);

					scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
							ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst3.value);

					strlcat(max_str, ":", max_str_size);
					strlcat(max_str, temp_stat_val_str,
							max_str_size);
				}
				strlcat(max_str, "\n",
						max_str_size);

			}


		}
		data_size = strlen(max_str);
		ECPRILOGDBG("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}

static ssize_t config_val_from_registers_qudp_egress_fh_src_mac_v2(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	char fh_str[TEMP_STR_MAX_SIZE];
	char index_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int max_str_size = MAX_STR_SIZE;
	int egress_table_index = 0;
	int ret_val = 0;
	static int data_size = 0;
	ecpriss_msb_mac mac0;
	ecpriss_lsb_mac mac1;

	if(*ppos == 0 )
	{
		memset(max_str,0,sizeof(max_str));

		RESET_STR(fh_str);
		scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);

		ecpriss_qudp_egress_config_stats_update_v2(fh_index);

		for(egress_table_index = 0; egress_table_index < NUM_EGRESS_ENTRY; egress_table_index++){

			if(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.eth_src0_port[fh_index][egress_table_index].value ||
					ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.eth_src1_dst1_port[fh_index][egress_table_index].src_msb){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", egress_table_index);
				RESET_STR(temp_stat_val_str);

				mac0.msb_mac = ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.eth_src1_dst1_port[fh_index][egress_table_index].src_msb;
				mac1.lsb_mac = ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.eth_src0_port[fh_index][egress_table_index].value;

				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%x:%x:%x:%x:%x:%x",mac0.mac[1], mac0.mac[0]
						,mac1.mac[3],mac1.mac[2],mac1.mac[1],mac1.mac[0]);


				strlcat(max_str, "src_mac_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, "- ", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				strlcat(max_str, "\n",
						max_str_size);

			}
		}
		data_size = strlen(max_str);
		ECPRILOGDBG("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;

}

static ssize_t config_val_from_registers_qudp_egress_fh_dst_mac_v2(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	char fh_str[TEMP_STR_MAX_SIZE];
	char index_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int max_str_size = MAX_STR_SIZE;
	int egress_table_index = 0;
	int ret_val = 0;
	static int data_size = 0;
	ecpriss_msb_mac mac0;
	ecpriss_lsb_mac mac1;

	if(*ppos == 0 )
	{
		memset(max_str,0,sizeof(max_str));

		RESET_STR(fh_str);
		scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);

		ecpriss_qudp_egress_config_stats_update_v2(fh_index);

		for(egress_table_index = 0; egress_table_index < NUM_EGRESS_ENTRY; egress_table_index++){

			if(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.eth_src0_port[fh_index][egress_table_index].value){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", egress_table_index);
				RESET_STR(temp_stat_val_str);

				mac0.msb_mac = ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.eth_src1_dst1_port[fh_index][egress_table_index].dst_msb;
				mac1.lsb_mac = ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.eth_dst0_port[fh_index][egress_table_index].value;

				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%x:%x:%x:%x:%x:%x",mac0.mac[1], mac0.mac[0]
						,mac1.mac[3],mac1.mac[2],mac1.mac[1],mac1.mac[0]);


				strlcat(max_str, "dst_mac_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, "- ", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				strlcat(max_str, "\n",
						max_str_size);

			}
		}
		data_size = strlen(max_str);
		ECPRILOGDBG("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;

}

static ssize_t config_val_from_registers_qudp_egress_vlan_ethertype(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	char fh_str[TEMP_STR_MAX_SIZE];
	char index_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int max_str_size = MAX_STR_SIZE;
	int egress_table_index = 0;
	int ret_val = 0;
	static int data_size = 0;

	if(*ppos == 0 )
	{
		memset(max_str,0,sizeof(max_str));

		RESET_STR(fh_str);
		scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);

		ecpriss_qudp_egress_config_stats_update(fh_index);

		for(egress_table_index = 0; egress_table_index < NUM_EGRESS_ENTRY; egress_table_index++){

			if(ecpriss_pdata->cfg_stats.qudp_cfg.egress.vlan_ethertype[fh_index][egress_table_index].ethertype){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", egress_table_index);
				RESET_STR(temp_stat_val_str);
				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
						ecpriss_pdata->cfg_stats.qudp_cfg.egress.vlan_ethertype[fh_index][egress_table_index].ethertype);

				strlcat(max_str, "ethertype_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				strlcat(max_str, "\n",
						max_str_size);

			}

			if(ecpriss_pdata->cfg_stats.qudp_cfg.egress.vlan_ethertype[fh_index][egress_table_index].vlan_data){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", egress_table_index);
				RESET_STR(temp_stat_val_str);
				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
						ecpriss_pdata->cfg_stats.qudp_cfg.egress.vlan_ethertype[fh_index][egress_table_index].vlan_data);

				strlcat(max_str, "vlan_data_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				strlcat(max_str, "\n",
						max_str_size);

			}
		}
		data_size = strlen(max_str);
		ECPRILOGDBG("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}

static ssize_t config_val_from_registers_qudp_egress_sa_tag_ip_tos_misc_port_v2(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	char fh_str[TEMP_STR_MAX_SIZE];
	char index_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int max_str_size = MAX_STR_SIZE;
	int egress_table_index = 0;
	int ret_val = 0;
	static int data_size = 0;

	if(*ppos == 0 )
	{
		memset(max_str,0,sizeof(max_str));

		RESET_STR(fh_str);
		scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);

		ecpriss_qudp_egress_config_stats_update_v2(fh_index);

		for(egress_table_index = 0; egress_table_index < NUM_EGRESS_ENTRY; egress_table_index++){

			if(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.vlan_ethertype[fh_index][egress_table_index].ethertype){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", egress_table_index);
				RESET_STR(temp_stat_val_str);
				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
						ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.sa_ip_tos_misc_port[fh_index][egress_table_index].sa_tag_data);

				strlcat(max_str, "Sa_Tag_Data_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				strlcat(max_str, "\n",
						max_str_size);

				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
						ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.sa_ip_tos_misc_port[fh_index][egress_table_index].tos);
				strlcat(max_str, "TOS_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				strlcat(max_str, "\n",
						max_str_size);

				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%s",
						(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.sa_ip_tos_misc_port[fh_index][egress_table_index].ip_type == 0)? "Ipv4":"Ipv6");
				strlcat(max_str, "IP_Type_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				strlcat(max_str, "\n",
						max_str_size);

				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%s",
						(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.sa_ip_tos_misc_port[fh_index][egress_table_index].is_ipsec == 0)? "Disable":"Enable");
				strlcat(max_str, "Is_Ipsec_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				strlcat(max_str, "\n",
						max_str_size);

				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%s",
						(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.sa_ip_tos_misc_port[fh_index][egress_table_index].df_bit == 0)? "Disable":"Enable");
				strlcat(max_str, "Defragmentation_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				strlcat(max_str, "\n",
						max_str_size);


				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%s",
						(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.sa_ip_tos_misc_port[fh_index][egress_table_index].calc_udp_cs == 0)? "No":"Yes");
				strlcat(max_str, "Calculate_Udp_Checksum_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				strlcat(max_str, "\n\n",
						max_str_size);

			}

		}
		data_size = strlen(max_str);
		ECPRILOGDBG("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;

}

static ssize_t config_val_from_registers_qudp_egress_vlan_ethertype_v2(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	char fh_str[TEMP_STR_MAX_SIZE];
	char index_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int max_str_size = MAX_STR_SIZE;
	int egress_table_index = 0;
	int ret_val = 0;
	static int data_size = 0;

	if(*ppos == 0 )
	{
		memset(max_str,0,sizeof(max_str));

		RESET_STR(fh_str);
		scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);

		ecpriss_qudp_egress_config_stats_update_v2(fh_index);

		for(egress_table_index = 0; egress_table_index < NUM_EGRESS_ENTRY; egress_table_index++){

			if(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.vlan_ethertype[fh_index][egress_table_index].ethertype){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", egress_table_index);
				RESET_STR(temp_stat_val_str);
				if(ECPRISS_ETHERTYPE_ECPRI == ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.vlan_ethertype[fh_index][egress_table_index].ethertype){
					scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "ECPRI");
				}else if (ECPRISS_ETHERTYPE_IPV4 == ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.vlan_ethertype[fh_index][egress_table_index].ethertype){
					scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "IPV4");
				}else if (ECPRISS_ETHERTYPE_IPV6 == ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.vlan_ethertype[fh_index][egress_table_index].ethertype){
					scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "IPV6");
				}else{
					scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
							ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.vlan_ethertype[fh_index][egress_table_index].ethertype);
				}
				strlcat(max_str, "ethertype_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				strlcat(max_str, "\n",
						max_str_size);

			}

			if(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.vlan_ethertype[fh_index][egress_table_index].vlan_data){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", egress_table_index);
				RESET_STR(temp_stat_val_str);
				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
						ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.vlan_ethertype[fh_index][egress_table_index].vlan_data);

				strlcat(max_str, "vlan_data_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				strlcat(max_str, "\n",
						max_str_size);

			}
		}
		data_size = strlen(max_str);
		ECPRILOGDBG("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}



static ssize_t config_val_from_registers_qudp_egress_udp_ports(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	char fh_str[TEMP_STR_MAX_SIZE];
	char index_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int max_str_size = MAX_STR_SIZE;
	int egress_table_index = 0;
	int ret_val = 0;
	static int data_size = 0;

	if(*ppos == 0 )
	{
		memset(max_str,0,sizeof(max_str));

		RESET_STR(fh_str);
		scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);

		ecpriss_qudp_egress_config_stats_update(fh_index);

		for(egress_table_index = 0; egress_table_index < NUM_EGRESS_ENTRY; egress_table_index++){

			if(ecpriss_pdata->cfg_stats.qudp_cfg.egress.udp_ports[fh_index][egress_table_index].src){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", egress_table_index);
				RESET_STR(temp_stat_val_str);
				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
						ecpriss_pdata->cfg_stats.qudp_cfg.egress.udp_ports[fh_index][egress_table_index].src);

				strlcat(max_str, "udp_classification_src_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				strlcat(max_str, "\n",
						max_str_size);

			}

			if(ecpriss_pdata->cfg_stats.qudp_cfg.egress.udp_ports[fh_index][egress_table_index].dst){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", egress_table_index);
				RESET_STR(temp_stat_val_str);
				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
						ecpriss_pdata->cfg_stats.qudp_cfg.egress.udp_ports[fh_index][egress_table_index].dst);

				strlcat(max_str, "udp_classification_dst_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				strlcat(max_str, "\n",
						max_str_size);

			}
		}
		data_size = strlen(max_str);
		ECPRILOGDBG("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}

static ssize_t config_val_from_registers_qudp_egress_udp_ports_v2(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
{
	char fh_str[TEMP_STR_MAX_SIZE];
	char index_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int max_str_size = MAX_STR_SIZE;
	int egress_table_index = 0;
	int ret_val = 0;
	static int data_size = 0;

	if(*ppos == 0 )
	{
		memset(max_str,0,sizeof(max_str));

		RESET_STR(fh_str);
		scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);

		ecpriss_qudp_egress_config_stats_update_v2(fh_index);

		for(egress_table_index = 0; egress_table_index < NUM_EGRESS_ENTRY; egress_table_index++){

			if(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.udp_ports[fh_index][egress_table_index].src){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", egress_table_index);
				RESET_STR(temp_stat_val_str);
				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
						ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.udp_ports[fh_index][egress_table_index].src);

				strlcat(max_str, "udp_classification_src_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				strlcat(max_str, "\n",
						max_str_size);

			}

			if(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.udp_ports[fh_index][egress_table_index].dst){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", egress_table_index);
				RESET_STR(temp_stat_val_str);
				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
						ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.udp_ports[fh_index][egress_table_index].dst);

				strlcat(max_str, "udp_classification_dst_fh_",
						max_str_size);
				strlcat(max_str, fh_str,
						max_str_size);
				strlcat(max_str, "_table_index_",
						max_str_size);
				strlcat(max_str, index_str,
						max_str_size);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				strlcat(max_str, "\n",
						max_str_size);

			}
		}
		data_size = strlen(max_str);
		ECPRILOGDBG("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}
static ssize_t config_val_from_registers_xbar(char __user *buf, cfg_prm_u param,int fh_index)
{
	int pcid_index;
	char fh_str[TEMP_STR_MAX_SIZE];
	char pcid_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int ret_val = 0;
	int max_str_size = sizeof(max_str);

	memset(max_str,0,sizeof(max_str));

	if(min_lut_index < 0 || min_lut_index > 65534)
		min_lut_index = 0;

	if(max_lut_index > 65534)
		max_lut_index = 299;

	if(max_lut_index < min_lut_index)
		max_lut_index = (max_lut_index > min_lut_index)? max_lut_index : min_lut_index;

	ecpriss_xbar_config_stats_update();
	switch (param){
		case FHRX :
			for(pcid_index=min_lut_index; pcid_index < max_lut_index; pcid_index++) {
				if(ecpriss_pdata->cfg_stats.xbar_cfg.lut_cfg.fhrx[fh_index][pcid_index]){
					RESET_STR(fh_str);
					scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);
					RESET_STR(pcid_str);
					scnprintf(pcid_str, TEMP_STR_MIN_SIZE, "%u", pcid_index);
					RESET_STR(temp_stat_val_str);
					scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
							ecpriss_pdata->cfg_stats.xbar_cfg.lut_cfg.fhrx[fh_index][pcid_index]);

					strlcat(max_str, "fh_",
							max_str_size);
					strlcat(max_str, fh_str,
							max_str_size);
					strlcat(max_str, ":",
							max_str_size);
					strlcat(max_str, pcid_str,
							max_str_size);
					strlcat(max_str, ":", max_str_size);
					strlcat(max_str, temp_stat_val_str,
							max_str_size);
					strlcat(max_str, "\n",
							max_str_size);

				}
			}
			break;
		case OCRX :
			for(pcid_index=min_lut_index; pcid_index < max_lut_index; pcid_index++) {
				if(ecpriss_pdata->cfg_stats.xbar_cfg.lut_cfg.ocrx[fh_index][pcid_index]){
					RESET_STR(fh_str);
					scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);
					RESET_STR(pcid_str);
					scnprintf(pcid_str, TEMP_STR_MIN_SIZE, "%u", pcid_index);
					RESET_STR(temp_stat_val_str);
					scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
							ecpriss_pdata->cfg_stats.xbar_cfg.lut_cfg.ocrx[fh_index][pcid_index]);

					strlcat(max_str, "fh_",
							max_str_size);
					strlcat(max_str, fh_str,
							max_str_size);
					strlcat(max_str, ":",
							max_str_size);
					strlcat(max_str, pcid_str,
							max_str_size);
					strlcat(max_str, ":", max_str_size);
					strlcat(max_str, temp_stat_val_str,
							max_str_size);
					strlcat(max_str, "\n",
							max_str_size);

				}
			}
			break;
		case GLOBAL_CFG :
			strlcat(max_str, "xbar_lut_global_cfg:",max_str_size);
			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
				ecpriss_pdata->cfg_stats.xbar_cfg.global_cfg.global);
			strlcat(max_str, temp_stat_val_str, max_str_size);
			strlcat(max_str, "\n",max_str_size);
		default :
			ECPRILOGDBG("default case\n");
			break;
	}
	ret_val = copy_to_user(buf,max_str,FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	ret_val = strlen(max_str);
	return ret_val;

}
static ssize_t config_val_from_registers_xbar_v2(char __user *buf, cfg_prm_u param,int fh_index)
{
	int pcid_index;
	char fh_str[TEMP_STR_MAX_SIZE];
	char pcid_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int ret_val = 0;
	int max_str_size = sizeof(max_str);

	char res_stat_val_str[TEMP_STR_MAX_SIZE];

	memset(max_str,0,sizeof(max_str));

	if(min_lut_index < 0 || min_lut_index > 65534)
		min_lut_index = 0;

	if(max_lut_index > 65534)
		max_lut_index = 299;

	if(max_lut_index < min_lut_index)
		max_lut_index = (max_lut_index > min_lut_index)? max_lut_index : min_lut_index;


	ecpriss_xbar_config_stats_update_v2();
	switch (param){
		case FHRX :
			for(pcid_index=min_lut_index; pcid_index < max_lut_index; pcid_index++) {
				if(ecpriss_pdata_v2->cfg_stats_v2.xbar_cfg_v2.lut_cfg.fhrx[fh_index][pcid_index]){
					RESET_STR(fh_str);
					scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);
					RESET_STR(pcid_str);
					scnprintf(pcid_str, TEMP_STR_MIN_SIZE, "%u", pcid_index);
					RESET_STR(temp_stat_val_str);
					scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
						ecpriss_pdata_v2->cfg_stats_v2.xbar_cfg_v2.lut_cfg.fhrx[fh_index][pcid_index]);

					RESET_STR(res_stat_val_str);
					process_fhrx(ecpriss_pdata_v2->cfg_stats_v2.xbar_cfg_v2.lut_cfg.fhrx[fh_index][pcid_index], res_stat_val_str, TEMP_STR_MAX_SIZE);

					strlcat(max_str, "fh_",
							max_str_size);
					strlcat(max_str, fh_str,
							max_str_size);
					strlcat(max_str, ":",
							max_str_size);
					strlcat(max_str, pcid_str,
							max_str_size);
					strlcat(max_str, ":", max_str_size);
					strlcat(max_str, res_stat_val_str,
							max_str_size);
					strlcat(max_str, "\n",
							max_str_size);
					}
				}
			break;
		case OCRX :
			for(pcid_index=min_lut_index; pcid_index < max_lut_index; pcid_index++) {
				if(ecpriss_pdata_v2->cfg_stats_v2.xbar_cfg_v2.lut_cfg.ocrx[fh_index][pcid_index]){
					RESET_STR(fh_str);
					scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);
					RESET_STR(pcid_str);
					scnprintf(pcid_str, TEMP_STR_MIN_SIZE, "%u", pcid_index);
					RESET_STR(temp_stat_val_str);
					scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
							ecpriss_pdata_v2->cfg_stats_v2.xbar_cfg_v2.lut_cfg.ocrx[fh_index][pcid_index]);

					RESET_STR(res_stat_val_str);
					process_ocrx(ecpriss_pdata_v2->cfg_stats_v2.xbar_cfg_v2.lut_cfg.ocrx[fh_index][pcid_index], res_stat_val_str, TEMP_STR_MAX_SIZE);

					strlcat(max_str, "fh_",
							max_str_size);
					strlcat(max_str, fh_str,
							max_str_size);
					strlcat(max_str, ":",
							max_str_size);
					strlcat(max_str, pcid_str,
							max_str_size);
					strlcat(max_str, ":", max_str_size);
					strlcat(max_str, res_stat_val_str,
							max_str_size);
					strlcat(max_str, "\n",
							max_str_size);

				}
			}
			break;
		case GLOBAL_CFG :
			strlcat(max_str, "xbar_lut_global_cfg:",max_str_size);
			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
				ecpriss_pdata_v2->cfg_stats_v2.xbar_cfg_v2.global_cfg.global);
			strlcat(max_str, temp_stat_val_str, max_str_size);
			strlcat(max_str, "\n",max_str_size);
		default :
			ECPRILOGDBG("default case\n");
			break;
	}
	ret_val = copy_to_user(buf,max_str,FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	ret_val = strlen(max_str);
	return ret_val;

}
static ssize_t stats_value_from_registers_xbar(char __user *buf)
{
	char *final_stats_str = NULL;
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	uint32_t temp_stat_val = 0;
	uint32_t i = 0;
	uint32_t ret_val = 0;

	char temp_stat_val_str_1[TEMP_STR_MAX_SIZE] =
		"{xbar_fhrx_pkt_cnt_link_";
	char temp_stat_val_str_2[TEMP_STR_MAX_SIZE] =
		"{xbar_fhtx_pkt_cnt_link_";
	char temp_stat_val_str_3[TEMP_STR_MAX_SIZE] =
		"{xbar_c2crx_pkt_cnt_link_";
	char temp_stat_val_str_4[TEMP_STR_MAX_SIZE] =
		"{xbar_c2ctx_pkt_cnt_link_";
	char temp_stat_val_str_5[TEMP_STR_MAX_SIZE] =
		"{xbar_octx_pkt_cnt_link_";
	char temp_stat_val_str_6[TEMP_STR_MAX_SIZE] =
		"{xbar_ocrx_pkt_cnt_link_";

	char link_id[TEMP_STR_MAX_SIZE];

	final_stats_str =
		(char *)kzalloc(FINAL_STATS_DYNAMIC_STR_MAX_SIZE, GFP_KERNEL);

	if (!final_stats_str)
	{
		goto err;
	}

	RESET_STR(temp_stat_val_str);
	RESET_STR(link_id);

	for (i = 0; i < TOTAL_LINKS; i++)
	{

		RESET_STR(link_id);
		scnprintf(link_id, TEMP_STR_MIN_SIZE, "%u", i);

		temp_stat_val =
			ecpriss_pdata->xbar_ctx->stats.xbar_fhrx_pkt_cnt[i];
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
				temp_stat_val);

		strlcat(final_stats_str, temp_stat_val_str_1,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, link_id,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, ":", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "}\n",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		temp_stat_val =
			ecpriss_pdata->xbar_ctx->stats.xbar_c2crx_pkt_cnt[i];
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
				temp_stat_val);

		strlcat(final_stats_str, temp_stat_val_str_3,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, link_id,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, ":", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "}\n",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	}

	temp_stat_val = ecpriss_pdata->xbar_ctx->stats.xbar_fhrx_dma_pkt_cnt;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_fhrx_dma_pkt_cnt:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->xbar_ctx->stats.xbar_fhrx_uc_pkt_cnt;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_fhrx_uc_pkt_cnt:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->xbar_ctx->stats.xbar_fhrx_uc_err_pkt_cnt;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_fhrx_uc_err_pkt_cnt:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->xbar_ctx->stats.xbar_fhrx_err_pkt_cnt;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_fhrx_err_pkt_cnt:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->xbar_ctx->stats.xbar_c2crx_dma_pkt_cnt;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_c2crx_dma_pkt_cnt:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->xbar_ctx->stats.xbar_c2crx_err_pkt_cnt;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_c2crx_err_pkt_cnt:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	for (i = 0; i < TOTAL_LINKS; i++)
	{

		RESET_STR(link_id);
		scnprintf(link_id, TEMP_STR_MIN_SIZE, "%u", i);

		temp_stat_val =
			ecpriss_pdata->xbar_ctx->stats.xbar_fhtx_pkt_cnt[i];
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
				temp_stat_val);

		strlcat(final_stats_str, temp_stat_val_str_2,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, link_id,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, ":", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "}\n",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		temp_stat_val =
			ecpriss_pdata->xbar_ctx->stats.xbar_c2ctx_pkt_cnt[i];
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
				temp_stat_val);

		strlcat(final_stats_str, temp_stat_val_str_4,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, link_id,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, ":", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "}\n",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	}

	temp_stat_val =
		ecpriss_pdata->xbar_ctx->stats.xbar_fhtx_c2c_pkt_ovf_cnt;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			temp_stat_val);
	strlcat(final_stats_str, "{xbar_fhtx_c2c_pkt_ovf_cnt:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->xbar_ctx->stats.xbar_fhtx_dma_pkt_cnt;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			temp_stat_val, FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str,
			"{xbar_fhtx_dma_pkt_cnt:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->xbar_ctx->stats.xbar_c2c_pkt_ovf_cnt;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_c2c_pkt_ovf_cnt:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->xbar_ctx->stats.xbar_fhtx_uc_pkt_cnt;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_fhtx_uc_pkt_cnt:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	for (i = 0; i < XBAR_LINKS; i++)
	{

		RESET_STR(link_id);
		scnprintf(link_id, TEMP_STR_MIN_SIZE, "%u", i);

		temp_stat_val =
			ecpriss_pdata->xbar_ctx->stats.xbar_octx_pkt_cnt[i];
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
				temp_stat_val);

		strlcat(final_stats_str, temp_stat_val_str_5,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, link_id,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, ":", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "}\n",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		temp_stat_val =
			ecpriss_pdata->xbar_ctx->stats.xbar_ocrx_pkt_cnt[i];
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
				temp_stat_val);

		strlcat(final_stats_str, temp_stat_val_str_6,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, link_id,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, ":", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "}\n",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	}


	temp_stat_val = ecpriss_pdata->xbar_ctx->stats.xbar_ocrx_fh_buff_watermark_fh0;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_ocrx_fh_buff_watermark-->fh0 :", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->xbar_ctx->stats.xbar_ocrx_fh_buff_watermark_fh1;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_ocrx_fh_buff_watermark-->fh1 :", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->xbar_ctx->stats.xbar_ocrx_fh_buff_watermark_fh2;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_ocrx_fh_buff_watermark-->fh2 :", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);



	temp_stat_val = ecpriss_pdata->xbar_ctx->stats.xbar_dbg_ocrx_0_1_buff_watermark_cc0;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_dbg_ocrx_0_1_buff_watermark-->cc0 :", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->xbar_ctx->stats.xbar_dbg_ocrx_0_1_buff_watermark_cc1;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_dbg_ocrx_0_1_buff_watermark-->cc1 :", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);


	temp_stat_val = ecpriss_pdata->xbar_ctx->stats.xbar_dbg_ocrx_2_3_buff_watermark_cc2;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_dbg_ocrx_2_3_buff_watermark-->cc2 :", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->xbar_ctx->stats.xbar_dbg_ocrx_2_3_buff_watermark_cc3;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_dbg_ocrx_2_3_buff_watermark-->cc3 :", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);



	temp_stat_val = ecpriss_pdata->xbar_ctx->stats.octx_oc_0_1_buff_watermark_cc0;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_octx_oc_0_1_buff_watermark-->cc0 :", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);


	temp_stat_val = ecpriss_pdata->xbar_ctx->stats.octx_oc_0_1_buff_watermark_cc1;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_octx_oc_0_1_buff_watermark-->cc1 :", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);


	temp_stat_val = ecpriss_pdata->xbar_ctx->stats.octx_oc_2_3_buff_watermark_cc2;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_octx_oc_2_3_buff_watermark-->cc2 :", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->xbar_ctx->stats.octx_oc_2_3_buff_watermark_cc3;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_octx_oc_2_3_buff_watermark-->cc3 :", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);


	temp_stat_val = ecpriss_pdata->xbar_ctx->stats.xbar_dbg_fhrx_unknown_pcid_cnt_fhrx_0_cnt;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_dbg_fhrx_unknown_pcid_cnt-->fhrx_0_cnt :", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->xbar_ctx->stats.xbar_dbg_fhrx_unknown_pcid_cnt_fhrx_1_cnt;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_dbg_fhrx_unknown_pcid_cnt-->fhrx_1_cnt :", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->xbar_ctx->stats.xbar_dbg_fhrx_unknown_pcid_cnt_fhrx_2_cnt;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_dbg_fhrx_unknown_pcid_cnt-->fhrx_2_cnt :", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);


	temp_stat_val = ecpriss_pdata->xbar_ctx->stats.xbar_dbg_ocrx_unknown_pcid_cnt_ocrx_fh_0_cnt;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_dbg_ocrx_unknown_pcid_cnt-->ocrx_fh_0_cnt :", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->xbar_ctx->stats.xbar_dbg_ocrx_unknown_pcid_cnt_ocrx_fh_1_cnt;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_dbg_ocrx_unknown_pcid_cnt-->ocrx_fh_1_cnt :", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->xbar_ctx->stats.xbar_dbg_ocrx_unknown_pcid_cnt_ocrx_fh_2_cnt;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_dbg_ocrx_unknown_pcid_cnt-->ocrx_fh_2_cnt :", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	for (i = 0; i < NUM_OF_FHP; i++)
	{

		RESET_STR(link_id);
		scnprintf(link_id, TEMP_STR_MIN_SIZE, "%u", i);

		temp_stat_val =
			ecpriss_pdata->xbar_ctx->stats.fhrx_unknown_pcid_info_1_n[i];
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%x",
				temp_stat_val);

		strlcat(final_stats_str, "{fhrx_unknown_pcid_info_1_n_fh",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, link_id,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, ":", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "}\n",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		temp_stat_val =
			ecpriss_pdata->xbar_ctx->stats.fhrx_unknown_pcid_info_2_n[i];
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%x",
				temp_stat_val);

		strlcat(final_stats_str, "{fhrx_unknown_pcid_info_2_n_fh",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, link_id,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, ":", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "}\n",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		temp_stat_val =
			ecpriss_pdata->xbar_ctx->stats.ocrx_unknown_pcid_info_1_n[i];
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%x",
				temp_stat_val);

		strlcat(final_stats_str, "{ocrx_unknown_pcid_info_1_n_fh",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, link_id,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, ":", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "}\n",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		temp_stat_val =
			ecpriss_pdata->xbar_ctx->stats.ocrx_unknown_pcid_info_2_n[i];
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%x",
				temp_stat_val);
		strlcat(final_stats_str, "{ocrx_unknown_pcid_info_2_n_fh",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, link_id,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, ":", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "}\n",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	}


	ret_val = copy_to_user(buf,final_stats_str,FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	ret_val = strlen(final_stats_str);
	kfree(final_stats_str);
	final_stats_str = NULL;
	return ret_val;

err:
	kfree(final_stats_str);
	return 0;
}
static ssize_t stats_value_from_registers_xbar_v2(char __user *buf)
{

	char *final_stats_str = NULL;
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	uint64_t temp_stat_val = 0;
	uint32_t i = 0;
	uint32_t ret_val = 0;

	char temp_stat_val_str_1[TEMP_STR_MAX_SIZE] =
		"{xbar_fhrx_pkt_cnt_link_";
	char temp_stat_val_str_2[TEMP_STR_MAX_SIZE] =
		"{xbar_fhtx_pkt_cnt_link_";

	char link_id[TEMP_STR_MAX_SIZE];
	char fh_index[TEMP_STR_MAX_SIZE];

	final_stats_str =
		(char *)kzalloc(FINAL_STATS_DYNAMIC_STR_MAX_SIZE, GFP_KERNEL);

	if (!final_stats_str)
	{
		goto err;
	}

	RESET_STR(temp_stat_val_str);
	RESET_STR(link_id);

	for (i = 0; i < TOTAL_LINKS; i++)
	{

		RESET_STR(link_id);
		scnprintf(link_id, TEMP_STR_MIN_SIZE, "%u", i);

		temp_stat_val =
			ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_fhrx_pkt_cnt[i];
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
				  temp_stat_val);

		strlcat(final_stats_str, temp_stat_val_str_1,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, link_id,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, ":", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "}\n",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		temp_stat_val =
			ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_fhtx_pkt_cnt[i];
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
				  temp_stat_val);

		strlcat(final_stats_str, temp_stat_val_str_2,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, link_id,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, ":", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "}\n",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	}

	temp_stat_val = ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_fhrx_dma_pkt_cnt;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_fhrx_dma_pkt_cnt:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_fhrx_uc_pkt_cnt;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_fhrx_uc_pkt_cnt:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_fhrx_uc_err_pkt_cnt;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_fhrx_uc_err_pkt_cnt:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_fhrx_err_pkt_cnt;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_fhrx_err_pkt_cnt:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_fhtx_c2c_pkt_ovf_cnt;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str, "{xbar_fhtx_c2c_pkt_ovf_cnt:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_fhtx_dma_pkt_cnt;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val, FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str,
			"{xbar_fhtx_dma_pkt_cnt:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_fhtx_uc_pkt_cnt;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_fhtx_uc_pkt_cnt:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	for (i = 0; i < NUM_OF_FHP; i++)
	{
		RESET_STR(fh_index);
		scnprintf(fh_index, TEMP_STR_MIN_SIZE, "%u", i);


			temp_stat_val =
				ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_fhrx_c2c_pkt_cnt[i];
			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
					  temp_stat_val);

			strlcat(final_stats_str, "{xbar_fhrx_c2c_pkt_cnt_fh",
					FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
			strlcat(final_stats_str, fh_index,
					FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
			strlcat(final_stats_str, ":", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
			strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
			strlcat(final_stats_str, "}\n",
					FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

			temp_stat_val =
				ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_fhrx_oc_pkt_cnt[i];
			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
					  temp_stat_val);

			strlcat(final_stats_str, "{xbar_fhrx_oc_pkt_cnt_fh",
					FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
			strlcat(final_stats_str, fh_index,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
			strlcat(final_stats_str, ":", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
			strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
			strlcat(final_stats_str, "}\n",
					FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	}

	temp_stat_val = ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_octx_c2c_pkt_drop_cnt;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_octx_c2c_pkt_drop_cnt:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_octx_fh_pkt_drop_cnt;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_octx_fh_pkt_drop_cnt:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_octx_c2c_len_err_cnt;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_octx_c2c_len_err_cnt:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);


	temp_stat_val = ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_octx_fh_len_err_cnt;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{xbar_octx_fh_len_err_cnt:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	RESET_STR(temp_stat_val_str);
	RESET_STR(link_id);

	for (i = 0; i < XBAR_LINKS; i++)
	{

		RESET_STR(link_id);
		scnprintf(link_id, TEMP_STR_MIN_SIZE, "%u", i);

		temp_stat_val =
			ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_octx_pkt_cnt[i];
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
				  temp_stat_val);

		strlcat(final_stats_str, "{xbar_octx_pkt_cnt_link",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, link_id,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, ":", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "}\n",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		temp_stat_val =
			ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_ocrx_pkt_cnt[i];
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
				  temp_stat_val);

		strlcat(final_stats_str, "{xbar_ocrx_pkt_cnt_link",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, link_id,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, ":", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "}\n",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	}
	for (i = 0; i < TOTAL_LINKS; i++)
	{

		RESET_STR(link_id);
		scnprintf(link_id, TEMP_STR_MIN_SIZE, "%u", i);

		temp_stat_val =
			ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_ocrx_fh_pkt_cnt[i];
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
				  temp_stat_val);

		strlcat(final_stats_str, "{xbar_ocrx_fh_pkt_cnt_link",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, link_id,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, ":", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "}\n",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	}
	for (i = 0; i < NUM_OF_FHP; i++)
	{
		RESET_STR(fh_index);
		scnprintf(fh_index, TEMP_STR_MIN_SIZE, "%u", i);


			temp_stat_val =
				ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_ocrx_c2c_pkt_cnt[i];
			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
					  temp_stat_val);

			strlcat(final_stats_str, "{xbar_ocrx_c2c_pkt_cnt_fh",
					FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
			strlcat(final_stats_str, fh_index,
					FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
			strlcat(final_stats_str, ":", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
			strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
			strlcat(final_stats_str, "}\n",
					FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	}

	temp_stat_val = ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_dbg_fhrx_unknown_pcid_cnt_fhrx_0_cnt;
        scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
                        temp_stat_val);
        strlcat(final_stats_str,
                        "{xbar_dbg_fhrx_unknown_pcid_cnt-->fhrx_0_cnt :", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
        strlcat(final_stats_str, temp_stat_val_str,
                        FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
        strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

        temp_stat_val = ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_dbg_fhrx_unknown_pcid_cnt_fhrx_1_cnt;
        scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
                        temp_stat_val);
        strlcat(final_stats_str,
                        "{xbar_dbg_fhrx_unknown_pcid_cnt-->fhrx_1_cnt :", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
        strlcat(final_stats_str, temp_stat_val_str,
                        FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
        strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

        temp_stat_val = ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_dbg_fhrx_unknown_pcid_cnt_fhrx_2_cnt;
        scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
                        temp_stat_val);
        strlcat(final_stats_str,
                        "{xbar_dbg_fhrx_unknown_pcid_cnt-->fhrx_2_cnt :", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
        strlcat(final_stats_str, temp_stat_val_str,
                        FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
        strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);


	temp_stat_val = ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_dbg_ocrx_unknown_pcid_cnt_ocrx_fh_0_cnt;
        scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
                        temp_stat_val);
        strlcat(final_stats_str,
                        "{xbar_dbg_ocrx_unknown_pcid_cnt-->ocrx_fh_0_cnt :", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
        strlcat(final_stats_str, temp_stat_val_str,
                        FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
        strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

        temp_stat_val = ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_dbg_ocrx_unknown_pcid_cnt_ocrx_fh_1_cnt;
        scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
                        temp_stat_val);
        strlcat(final_stats_str,
                        "{xbar_dbg_ocrx_unknown_pcid_cnt-->ocrx_fh_1_cnt :", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
        strlcat(final_stats_str, temp_stat_val_str,
                        FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
        strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

        temp_stat_val = ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.xbar_dbg_ocrx_unknown_pcid_cnt_ocrx_fh_2_cnt;
        scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
                        temp_stat_val);
        strlcat(final_stats_str,
                        "{xbar_dbg_ocrx_unknown_pcid_cnt-->ocrx_fh_2_cnt :", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
        strlcat(final_stats_str, temp_stat_val_str,
                        FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
        strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);



	for (i = 0; i < NUM_OF_FHP; i++)
	{
		RESET_STR(link_id);
		scnprintf(link_id, TEMP_STR_MIN_SIZE, "%u", i);

		temp_stat_val =
			ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.fhrx_unknown_pcid_info_1_n[i];
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%x",
				temp_stat_val);

		strlcat(final_stats_str, "{fhrx_unknown_pcid_info_1_n_fh",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, link_id,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, ":", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "}\n",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		temp_stat_val =
			ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.fhrx_unknown_pcid_info_2_n[i];
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%x",
				temp_stat_val);

		strlcat(final_stats_str, "{fhrx_unknown_pcid_info_2_n_fh",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, link_id,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, ":", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "}\n",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		temp_stat_val =
			ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.ocrx_unknown_pcid_info_1_n[i];
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%x",
				temp_stat_val);

		strlcat(final_stats_str, "{ocrx_unknown_pcid_info_1_n_fh",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, link_id,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, ":", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "}\n",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

		temp_stat_val =
			ecpriss_pdata_v2->xbar_ctx_v2->stats_v2.ocrx_unknown_pcid_info_2_n[i];
		scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%x",
				temp_stat_val);
		strlcat(final_stats_str, "{ocrx_unknown_pcid_info_2_n_fh",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, link_id,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, ":", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, temp_stat_val_str,
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		strlcat(final_stats_str, "}\n",
				FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	}
	ret_val = copy_to_user(buf,final_stats_str,FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	ret_val = strlen(final_stats_str);
	kfree(final_stats_str);
	final_stats_str = NULL;
	return ret_val;

err:
	kfree(final_stats_str);
	return 0;
}


static ssize_t error_value_from_registers_xbar(char __user *buf)
{

	char *final_stats_str = NULL;
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	uint32_t temp_stat_val = 0;
	uint32_t ret_val = 0;

	final_stats_str =
		(char *)kzalloc(FINAL_STATS_DYNAMIC_STR_MAX_SIZE, GFP_KERNEL);

	if (!final_stats_str)
	{
		goto err;
	}

	RESET_STR(temp_stat_val_str);
	temp_stat_val =
		ecpriss_pdata->xbar_ctx->interrupt_stats.octx_fh_len_err;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{octx_fh_len_err:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata->xbar_ctx->interrupt_stats.octx_c2c_len_err;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{octx_c2c_len_err:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata->xbar_ctx->interrupt_stats.fhtx_c2c_overflow;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{fhtx_c2c_overflow:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata->xbar_ctx->interrupt_stats.c2ctx_fh_overflow;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{c2ctx_fh_overflow:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata->xbar_ctx->interrupt_stats.octx_c2c_overflow;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{octx_c2c_overflow:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata->xbar_ctx->interrupt_stats.fhrx_uc_overflow;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{fhrx_uc_overflow:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata->xbar_ctx->interrupt_stats.fhrx_uc_pkt_drop;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{fhrx_uc_pkt_drop:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata->xbar_ctx->interrupt_stats.fhrx_uc_pkt_err;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{fhrx_uc_pkt_err:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata->xbar_ctx->interrupt_stats.fhrx_uc_pkt_pending;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{fhrx_uc_pkt_pending:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata->xbar_ctx->interrupt_stats.ocrx_unknown_pcid;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{ocrx_unknown_pcid:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata->xbar_ctx->interrupt_stats.fhrx_unknown_pcid;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{fhrx_unknown_pcid:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata->xbar_ctx->interrupt_stats.c2crx_unkown_pcid;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{c2crx_unkown_pcid:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	ret_val = copy_to_user(buf,final_stats_str,FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	ret_val = strlen(final_stats_str);
	kfree(final_stats_str);
	final_stats_str = NULL;
	return ret_val;

err:
	kfree(final_stats_str);
	return 0;
}

static ssize_t error_value_from_registers_xbar_v2(char __user *buf)
{

	char *final_stats_str = NULL;
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	uint32_t temp_stat_val = 0;
	uint32_t ret_val = 0;

	final_stats_str =
		(char *)kzalloc(FINAL_STATS_DYNAMIC_STR_MAX_SIZE, GFP_KERNEL);

	if (!final_stats_str)
	{
		goto err;
	}

	RESET_STR(temp_stat_val_str);
	temp_stat_val =
		ecpriss_pdata_v2->xbar_ctx_v2->interrupt_stats_v2.octx_fh_len_err;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{octx_fh_len_err:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata_v2->xbar_ctx_v2->interrupt_stats_v2.octx_c2c_len_err;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{octx_c2c_len_err:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata_v2->xbar_ctx_v2->interrupt_stats_v2.fhtx_c2c_overflow;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{fhtx_c2c_overflow:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata_v2->xbar_ctx_v2->interrupt_stats_v2.c2ctx_fh_overflow;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{c2ctx_fh_overflow:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata_v2->xbar_ctx_v2->interrupt_stats_v2.octx_c2c_overflow;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{octx_c2c_overflow:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata_v2->xbar_ctx_v2->interrupt_stats_v2.fhrx_uc_overflow;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{fhrx_uc_overflow:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata_v2->xbar_ctx_v2->interrupt_stats_v2.fhrx_uc_pkt_drop;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{fhrx_uc_pkt_drop:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata_v2->xbar_ctx_v2->interrupt_stats_v2.fhrx_uc_pkt_err;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{fhrx_uc_pkt_err:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata_v2->xbar_ctx_v2->interrupt_stats_v2.fhrx_uc_pkt_pending;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{fhrx_uc_pkt_pending:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata_v2->xbar_ctx_v2->interrupt_stats_v2.ocrx_unknown_pcid;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{ocrx_unknown_pcid:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	ret_val = copy_to_user(buf,final_stats_str,FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	ret_val = strlen(final_stats_str);
	kfree(final_stats_str);
	final_stats_str = NULL;
	return ret_val;

err:
	kfree(final_stats_str);
	return 0;
}


static ssize_t error_value_from_registers_fh(char __user *buf, int port, int link)
{

	char *final_stats_str = NULL;
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE] = "";
	uint32_t temp_stat_val = 0;
	uint32_t ret_val = 0;

	final_stats_str =
		(char *)kzalloc(FINAL_STATS_DYNAMIC_STR_MAX_SIZE, GFP_KERNEL);

	if (!final_stats_str)
	{
		ECPRILOGDBG("Memory allocation failure \n");
		goto err;
	}

	RESET_STR(temp_stat_val_str);

	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port]
						.interrupt_stats.egress_mtu_err_packet_link[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str, "{egress_mtu_err_packet_link:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port]
						.interrupt_stats.ingress_fcs_err_packet_link[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str, "ingress_fcs_err_packet_link:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port]
						.interrupt_stats.ingress_udp_cs_error_link[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"ingress_udp_cs_error_link:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata->qudp_ctx->fh_port_cfg[port]
			.interrupt_stats.ingress_ip_filtered_packet_link[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str, "ingress_ip_filtered_packet_link:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata->qudp_ctx->fh_port_cfg[port]
			.interrupt_stats.ingress_vlan_filtered_packet_link[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str, "ingress_vlan_filtered_packet_link:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port]
						.interrupt_stats.ingress_sec_err_packet_link[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str, "ingress_sec_err_packet_link:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata->qudp_ctx->fh_port_cfg[port]
			.interrupt_stats.ingress_ip_len_err_packet_link[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str, "ingress_ip_len_err_packet_link:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port]
						.interrupt_stats.ingress_trap_rule_0_link[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"ingress_trap_rule_0_link:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port]
						.interrupt_stats.ingress_trap_rule_1_link[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"ingress_trap_rule_1_link:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port]
						.interrupt_stats.ingress_trap_rule_2_link[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"ingress_trap_rule_2_link:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port]
						.interrupt_stats.ingress_trap_rule_3_link[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"ingress_trap_rule_3_link:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata->qudp_ctx->fh_port_cfg[port]
			.interrupt_stats
			.ingress_last_in_chain_non_local_dst_packet_link[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"ingress_last_in_chain_non_local_dst_packet_link:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port]
						.interrupt_stats.ingress_ipv4_cs_error_link[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str, "ingress_ipv4_cs_error_link:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	ret_val = copy_to_user(buf,final_stats_str,FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	ret_val = strlen(final_stats_str);
	kfree(final_stats_str);
	final_stats_str = NULL;
	return ret_val;
err:
	kfree(final_stats_str);
	return 0;
}
static ssize_t error_value_from_registers_fh_v2(char __user *buf, int port, int link)
{

	char *final_stats_str = NULL;
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE] = "";
	uint32_t temp_stat_val = 0;
	uint32_t ret_val = 0;

	final_stats_str =
		(char *)kzalloc(FINAL_STATS_DYNAMIC_STR_MAX_SIZE, GFP_KERNEL);

	if (!final_stats_str)
	{
		ECPRILOGERR("Memory allocation failure \n");
		goto err;
	}

	RESET_STR(temp_stat_val_str);


	temp_stat_val = ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
						.interrupt_stats_v2.egress_mtu_err_packet_link[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str, "{egress_mtu_err_packet_link:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
						.interrupt_stats_v2.ingress_fcs_err_packet_link[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str, "ingress_fcs_err_packet_link:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
						.interrupt_stats_v2.ingress_udp_cs_error_link[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"ingress_udp_cs_error_link:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
			.interrupt_stats_v2.ingress_ip_filtered_packet_link[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str, "ingress_ip_filtered_packet_link:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
			.interrupt_stats_v2.ingress_vlan_filtered_packet_link[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str, "ingress_vlan_filtered_packet_link:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
						.interrupt_stats_v2.ingress_sec_err_packet_link[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str, "ingress_sec_err_packet_link:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
			.interrupt_stats_v2.ingress_ip_len_err_packet_link[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str, "ingress_ip_len_err_packet_link:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
						.interrupt_stats_v2.ingress_trap_rule_0_link[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"ingress_trap_rule_0_link:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
						.interrupt_stats_v2.ingress_trap_rule_1_link[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"ingress_trap_rule_1_link:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
						.interrupt_stats_v2.ingress_trap_rule_2_link[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"ingress_trap_rule_2_link:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
						.interrupt_stats_v2.ingress_trap_rule_3_link[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"ingress_trap_rule_3_link:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val =
		ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
			.interrupt_stats_v2
			.ingress_last_in_chain_non_local_dst_packet_link[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str,
			"ingress_last_in_chain_non_local_dst_packet_link:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
						.interrupt_stats_v2.ingress_ipv4_cs_error_link[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
			  temp_stat_val);
	strlcat(final_stats_str, "ingress_ipv4_cs_error_link:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	ret_val = copy_to_user(buf,final_stats_str,FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	ret_val = strlen(final_stats_str);
	kfree(final_stats_str);
	final_stats_str = NULL;
	return ret_val;
err:
	kfree(final_stats_str);
	return 0;
}


static ssize_t stats_value_from_registers_fh(char __user *buf, int port, int link)
{
	char *final_stats_str = NULL;
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE] = "";
	uint64_t temp_stat_val = 0;
	uint32_t ret_val = 0;

	final_stats_str =
		(char *)kzalloc(FINAL_STATS_DYNAMIC_STR_MAX_SIZE, GFP_KERNEL);

	if (!final_stats_str)
	{
		ECPRILOGERR("Memory allocation failure \n");
		goto err;
	}

	RESET_STR(temp_stat_val_str);

	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port]
						.stats.egress_num_udp_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{egress_num_udp_packets:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port]
						.stats.egress_num_eth_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{egress_num_eth_packets:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port]
						.stats.egress_num_bypassed_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			  temp_stat_val);
	strlcat(final_stats_str, "{egress_num_bypassed_packets:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port]
						.stats.egress_num_mtu_err_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			  temp_stat_val);
	strlcat(final_stats_str, "{egress_num_mtu_err_packets:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port]
						.stats.ingress_num_udp_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{ingress_num_udp_packets:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port]
						.stats.ingress_num_non_udp_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			  temp_stat_val);
	strlcat(final_stats_str, "{ingress_num_non_udp_packets:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port]
						.stats.ingress_num_fcs_err_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			  temp_stat_val);
	strlcat(final_stats_str, "{ingress_num_fcs_err_packets:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port]
						.stats.ingress_num_ipv4_cs_err_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			  temp_stat_val);
	strlcat(final_stats_str, "{ingress_num_ipv4_cs_err_packets:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port]
						.stats.ingress_num_udp_cs_err_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			  temp_stat_val);
	strlcat(final_stats_str, "{ingress_num_udp_cs_err_packets:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port]
						.stats.ingress_num_vlan_filtered_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			  temp_stat_val);
	strlcat(final_stats_str, "{ingress_num_vlan_filtered_packets:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port]
						.stats.ingress_num_sec_err_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			  temp_stat_val);
	strlcat(final_stats_str, "{ingress_num_sec_err_packets:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port]
						.stats.ingress_ip_len_err_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			  temp_stat_val);
	strlcat(final_stats_str, "{ingress_ip_len_err_packets:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port]
						.stats.ingress_ip_filtered_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			  temp_stat_val);
	strlcat(final_stats_str, "{ingress_ip_filtred_packets:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);


	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port].stats.fh_egress_udp_watermark_port_p_pkt_fifo;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			  temp_stat_val);
	strlcat(final_stats_str, "{fh_egress_udp_watermark-->pkt_fifo:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port].stats.fh_egress_udp_watermark_port_p_hdri_cfg_index_fifo;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			  temp_stat_val);
	strlcat(final_stats_str, "{fh_egress_udp_watermark-->hdri_cfg_index_fifo:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);


	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port].stats.fh_egress_udp_watermark_port_p_hdri_output_fifo;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			  temp_stat_val);
	strlcat(final_stats_str, "{fh_egress_udp_watermark-->hdri_output_fifo:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);


	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port].stats.fh_egress_udp_watermark_port_p_cs_calc_fifo;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			  temp_stat_val);
	strlcat(final_stats_str, "{fh_egress_udp_watermark-->cs_calc_fifo:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);


	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port].stats.fh_egress_udp_watermark_port_p_cs_update_fifo;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			  temp_stat_val);
	strlcat(final_stats_str, "{fh_egress_udp_watermark-->cs_update_fifo:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);


	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port].stats.fh_egress_udp_watermark_port_p_aligner_output_fifo;
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			  temp_stat_val);
	strlcat(final_stats_str, "{fh_egress_udp_watermark-->aligner_output_fifo:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);


	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port].stats.fh_ingress_udp_watermark_port_p_link_n_pkt_fifo[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			  temp_stat_val);
	strlcat(final_stats_str, "{fh_ingress_udp_watermark_port-->pkt_fifo:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port].stats.fh_ingress_udp_watermark_port_p_link_n_cmd_fifo[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			  temp_stat_val);
	strlcat(final_stats_str, "{fh_ingress_udp_watermark_port-->cmd_fifo:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port].stats.fh_ingress_udp_watermark_port_p_link_n_pkt_handler_sync_fifos[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			  temp_stat_val);
	strlcat(final_stats_str, "{fh_ingress_udp_watermark_port-->pkt_handler_sync_fifos:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);


	temp_stat_val = ecpriss_pdata->qudp_ctx->fh_port_cfg[port].stats.fh_ingress_udp_watermark_port_p_link_n_ptp_timestamp_fifo[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
			  temp_stat_val);
	strlcat(final_stats_str, "{fh_ingress_udp_watermark_port-->ptp_timestamp_fifo:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	ret_val = copy_to_user(buf,final_stats_str,FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	ret_val = strlen(final_stats_str);
	kfree(final_stats_str);
	final_stats_str = NULL;
	return ret_val;
err:
	kfree(final_stats_str);
	return 0;
}
static ssize_t stats_value_from_registers_fh_v2(char __user *buf, int port, int link)
{
	char *final_stats_str = NULL;
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE] = "";
	uint64_t temp_stat_val = 0;
	uint32_t ret_val = 0;

	final_stats_str =
		(char *)kzalloc(FINAL_STATS_DYNAMIC_STR_MAX_SIZE, GFP_KERNEL);

	if (!final_stats_str)
	{
		ECPRILOGDBG("Memory allocation failure \n");
		goto err;
	}

	RESET_STR(temp_stat_val_str);


	temp_stat_val = ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
						.stats_v2.egress_num_udp_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{egress_num_udp_packets:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
						.stats_v2.egress_num_eth_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{egress_num_eth_packets:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
						.stats_v2.egress_num_bypassed_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str, "{egress_num_bypassed_packets:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
						.stats_v2.egress_num_mtu_err_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str, "{egress_num_mtu_err_packets:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
						.stats_v2.ingress_num_eth_udp_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str,
			"{ingress_num_eth_udp_packets:", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
						.stats_v2.ingress_num_fcs_err_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str, "{ingress_num_fcs_err_packets:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
						.stats_v2.ingress_num_ipv4_cs_err_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str, "{ingress_num_ipv4_cs_err_packets:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
						.stats_v2.ingress_num_udp_cs_err_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str, "{ingress_num_udp_cs_err_packets:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
						.stats_v2.ingress_ip_filtered_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str, "{ingress_ip_filtered_packets:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);


	temp_stat_val = ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
						.stats_v2.ingress_num_vlan_filtered_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str, "{ingress_num_vlan_filtered_packets:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
						.stats_v2.ingress_num_sec_err_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str, "{ingress_num_sec_err_packets:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
						.stats_v2.ingress_ip_len_err_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str, "{ingress_ip_len_err_packets:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
						.stats_v2.ingress_num_eth_ecpri_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str, "{ingress_num_eth_ecpri_packets:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
						.stats_v2.ingress_num_eth_ptp_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str, "{ingress_num_eth_ptp_packets:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
						.stats_v2.ingress_num_eth_other_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str, "{ingress_num_eth_other_packets:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
						.stats_v2.ingress_num_udp_ecpri_or_nfapi_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str, "{ingress_num_udp_ecpri_or_nfapi_packets:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
						.stats_v2.ingress_num_udp_ptp_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str, "{ingress_num_udp_ptp_packets:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	temp_stat_val = ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port]
						.stats_v2.ingress_num_udp_other_packets[link];
	scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%llu",
			  temp_stat_val);
	strlcat(final_stats_str, "{ingress_num_udp_other_packets:",
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, temp_stat_val_str,
			FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
	strlcat(final_stats_str, "}\n", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);


	ret_val = copy_to_user(buf,final_stats_str,FINAL_STATS_DYNAMIC_STR_MAX_SIZE);

	ret_val = strlen(final_stats_str);
	kfree(final_stats_str);
	final_stats_str = NULL;
	return ret_val;
err:
	kfree(final_stats_str);
	return 0;
}


static ssize_t error_value_from_registers_fh_00(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = error_value_from_registers_fh_v2(buf, 0, 0);
	else
		len = error_value_from_registers_fh(buf, 0, 0);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t error_value_from_registers_fh_01(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = error_value_from_registers_fh_v2(buf, 0, 1);
	else
		len = error_value_from_registers_fh(buf, 0, 1);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t error_value_from_registers_fh_02(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = error_value_from_registers_fh_v2(buf, 0, 2);
	else
		len = error_value_from_registers_fh(buf, 0, 2);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t error_value_from_registers_fh_03(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = error_value_from_registers_fh_v2(buf, 0, 3);
	else
		len = error_value_from_registers_fh(buf, 0, 3);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t error_value_from_registers_fh_10(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = error_value_from_registers_fh_v2(buf, 1, 0);
	else
		len = error_value_from_registers_fh(buf, 1, 0);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t error_value_from_registers_fh_11(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = error_value_from_registers_fh_v2(buf, 1, 1);
	else
		len = error_value_from_registers_fh(buf, 1, 1);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t error_value_from_registers_fh_12(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = error_value_from_registers_fh_v2(buf, 1, 2);
	else
		len = error_value_from_registers_fh(buf, 1, 2);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t error_value_from_registers_fh_13(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = error_value_from_registers_fh_v2(buf, 1, 3);
	else
		len = error_value_from_registers_fh(buf, 1, 3);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t error_value_from_registers_fh_20(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = error_value_from_registers_fh_v2(buf, 2, 0);
	else
		len = error_value_from_registers_fh(buf, 2, 0);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t error_value_from_registers_fh_21(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = error_value_from_registers_fh_v2(buf, 2, 1);
	else
		len = error_value_from_registers_fh(buf, 2, 1);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t error_value_from_registers_fh_22(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = error_value_from_registers_fh_v2(buf, 2, 2);
	else
		len = error_value_from_registers_fh(buf, 2, 2);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t error_value_from_registers_fh_23(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = error_value_from_registers_fh_v2(buf, 2, 3);
	else
		len = error_value_from_registers_fh(buf, 2, 3);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}

static ssize_t stats_value_from_registers_fh_00(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = stats_value_from_registers_fh_v2(buf, 0, 0);
	else
		len = stats_value_from_registers_fh(buf, 0, 0);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t stats_value_from_registers_fh_01(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = stats_value_from_registers_fh_v2(buf, 0, 1);
	else
		len = stats_value_from_registers_fh(buf, 0, 1);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t stats_value_from_registers_fh_02(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = stats_value_from_registers_fh_v2(buf, 0, 2);
	else
		len = stats_value_from_registers_fh(buf, 0, 2);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t stats_value_from_registers_fh_03(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = stats_value_from_registers_fh_v2(buf, 0, 3);
	else
		len = stats_value_from_registers_fh(buf, 0, 3);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t stats_value_from_registers_fh_10(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = stats_value_from_registers_fh_v2(buf, 1, 0);
	else
		len = stats_value_from_registers_fh(buf, 1, 0);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t stats_value_from_registers_fh_11(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = stats_value_from_registers_fh_v2(buf, 1, 1);
	else
		len = stats_value_from_registers_fh(buf, 1, 1);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t stats_value_from_registers_fh_12(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = stats_value_from_registers_fh_v2(buf, 1, 2);
	else
		len = stats_value_from_registers_fh(buf, 1, 2);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t stats_value_from_registers_fh_13(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = stats_value_from_registers_fh_v2(buf, 1, 3);
	else
		len = stats_value_from_registers_fh(buf, 1, 3);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t stats_value_from_registers_fh_20(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = stats_value_from_registers_fh_v2(buf, 2, 0);
	else
		len = stats_value_from_registers_fh(buf, 2, 0);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t stats_value_from_registers_fh_21(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = stats_value_from_registers_fh_v2(buf, 2, 1);
	else
		len = stats_value_from_registers_fh(buf, 2, 1);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t stats_value_from_registers_fh_22(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = stats_value_from_registers_fh_v2(buf, 2, 2);
	else
		len = stats_value_from_registers_fh(buf, 2, 2);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t stats_value_from_registers_fh_23(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = stats_value_from_registers_fh_v2(buf, 2, 3);
	else
		len = stats_value_from_registers_fh(buf, 2, 3);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t stats_value_from_xbar(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = stats_value_from_registers_xbar_v2(buf);
	else
		len = stats_value_from_registers_xbar(buf);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t error_value_from_xbar(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = error_value_from_registers_xbar_v2(buf);
	else
		len = error_value_from_registers_xbar(buf);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t cfg_value_from_xbar_lut_fhrx_0(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_xbar_v2(buf,FHRX,0);
	else
		len = config_val_from_registers_xbar(buf,FHRX,0);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}

static ssize_t cfg_value_from_xbar_lut_fhrx_1(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_xbar_v2(buf,FHRX,1);
	else
		len = config_val_from_registers_xbar(buf,FHRX,1);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t cfg_value_from_xbar_lut_fhrx_2(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_xbar_v2(buf,FHRX,2);
	else
		len = config_val_from_registers_xbar(buf,FHRX,2);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t cfg_value_from_xbar_lut_ocrx_0(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_xbar_v2(buf,OCRX,0);
	else
		len = config_val_from_registers_xbar(buf,OCRX,0);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t cfg_value_from_xbar_lut_ocrx_1(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_xbar_v2(buf,OCRX,1);
	else
		len = config_val_from_registers_xbar(buf,OCRX,1);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t cfg_value_from_xbar_lut_ocrx_2(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_xbar_v2(buf,OCRX,2);
	else
		len = config_val_from_registers_xbar(buf,OCRX,2);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t cfg_value_from_xbar_lut_c2crxul(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_xbar_v2(buf,C2CRXUL,0);
	else
		len = config_val_from_registers_xbar(buf,C2CRXUL,0);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t cfg_value_from_xbar_lut_c2crxdl(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_xbar_v2(buf,C2CRXDL,0);
	else
		len = config_val_from_registers_xbar(buf,C2CRXDL,0);

	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t cfg_value_from_xbar_global(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_xbar_v2(buf,GLOBAL_CFG,0);
	else
		len = config_val_from_registers_xbar(buf,GLOBAL_CFG,0);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t cfg_value_from_qudp_egress_udp_ports_fh0(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_egress_udp_ports_v2(buf, 0 , &count , ppos);
	else
		len = config_val_from_registers_qudp_egress_udp_ports(buf, 0 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_qudp_egress_udp_ports_fh1(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_egress_udp_ports_v2(buf, 1 , &count , ppos);
	else
		len = config_val_from_registers_qudp_egress_udp_ports(buf, 1 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_qudp_egress_udp_ports_fh2(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_egress_udp_ports_v2(buf, 2 , &count , ppos);
	else
		len = config_val_from_registers_qudp_egress_udp_ports(buf, 2 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_qudp_egress_misc_cfg_fh0(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_egress_sa_tag_ip_tos_misc_port_v2(buf, 0 , &count , ppos);
	else{
		ECPRILOGERR("Debugfs, MISC port is not supported for V1 HW \n");
		return -EINVAL;
	}
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_qudp_egress_misc_cfg_fh1(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_egress_sa_tag_ip_tos_misc_port_v2(buf, 1 , &count , ppos);
	else{
		ECPRILOGERR("Debugfs, MISC port is not supported for V1 HW \n");
		return -EINVAL;
	}
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_qudp_egress_misc_cfg_fh2(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_egress_sa_tag_ip_tos_misc_port_v2(buf, 2 , &count , ppos);
	else{
		ECPRILOGERR("Debugfs, MISC port is not supported for V1 HW \n");
		return -EINVAL;
	}
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_qudp_egress_vlan_ethertype_fh0(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_egress_vlan_ethertype_v2(buf, 0 , &count , ppos);
	else
		len = config_val_from_registers_qudp_egress_vlan_ethertype(buf, 0 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}

static ssize_t cfg_value_from_qudp_egress_vlan_ethertype_fh1(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_egress_vlan_ethertype_v2(buf, 1 , &count , ppos);
	else
		len = config_val_from_registers_qudp_egress_vlan_ethertype(buf, 1 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}

static ssize_t cfg_value_from_qudp_egress_vlan_ethertype_fh2(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_egress_vlan_ethertype_v2(buf, 2 , &count , ppos);
	else
		len = config_val_from_registers_qudp_egress_vlan_ethertype(buf, 2 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}

static ssize_t cfg_value_from_qudp_egress_fh0_src_mac(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len = 0;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_egress_fh_src_mac_v2(buf, 0 , &count , ppos);
	else{
		ECPRILOGERR("V1 is not supported for src_mac read in debugfs\n");
		return -EINVAL;
	}
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;



}

static ssize_t cfg_value_from_qudp_egress_fh0_dst_mac(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len = 0;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_egress_fh_dst_mac_v2(buf, 0 , &count , ppos);
	else{
		ECPRILOGERR("V1 is not supported for dst_mac read in debugfs\n");
		return -EINVAL;
	}
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;



}
static ssize_t cfg_value_from_qudp_egress_fh1_src_mac(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len = 0;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_egress_fh_src_mac_v2(buf, 1 , &count , ppos);
	else{
		ECPRILOGERR("V1 is not supported for src_mac read in debugfs\n");
		return -EINVAL;
	}
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;



}

static ssize_t cfg_value_from_qudp_egress_fh1_dst_mac(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len = 0;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_egress_fh_dst_mac_v2(buf, 1 , &count , ppos);
	else{
		ECPRILOGERR("V1 is not supported for dst_mac read in debugfs\n");
		return -EINVAL;
	}
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;



}
static ssize_t cfg_value_from_qudp_egress_fh2_src_mac(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len = 0;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_egress_fh_src_mac_v2(buf, 2 , &count , ppos);
	else{
		ECPRILOGERR("V1 is not supported for src_mac read in debugfs\n");
		return -EINVAL;
	}
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;



}

static ssize_t cfg_value_from_qudp_egress_fh2_dst_mac(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len = 0;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_egress_fh_dst_mac_v2(buf, 2 , &count , ppos);
	else{
		ECPRILOGERR("V1 is not supported for dst_mac read in debugfs\n");
		return -EINVAL;
	}
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;



}

static ssize_t cfg_value_from_qudp_egress_dst_ip_addr_fh0(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_egress_dst_ip_addr_v2(buf, 0 , &count , ppos);
	else
		len = config_val_from_registers_qudp_egress_dst_ip_addr(buf, 0 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}

static ssize_t cfg_value_from_qudp_egress_dst_ip_addr_fh1(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_egress_dst_ip_addr_v2(buf, 1 , &count , ppos);
	else
		len = config_val_from_registers_qudp_egress_dst_ip_addr(buf, 1 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}

static ssize_t cfg_value_from_qudp_egress_dst_ip_addr_fh2(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_egress_dst_ip_addr_v2(buf, 2 , &count , ppos);
	else
		len = config_val_from_registers_qudp_egress_dst_ip_addr(buf, 2 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}

static ssize_t cfg_value_from_qudp_egress_src_ip_addr_fh0(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_egress_src_ip_addr_v2(buf, 0 , &count , ppos);
	else
		len = config_val_from_registers_qudp_egress_src_ip_addr(buf, 0 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}

static ssize_t cfg_value_from_qudp_egress_src_ip_addr_fh1(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_egress_src_ip_addr_v2(buf, 1 , &count , ppos);
	else
		len = config_val_from_registers_qudp_egress_src_ip_addr(buf, 1 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_qudp_egress_src_ip_addr_fh2(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_egress_src_ip_addr_v2(buf, 2 , &count , ppos);
	else
		len = config_val_from_registers_qudp_egress_src_ip_addr(buf, 2 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_qudp_ingress_global_cfg_fh0(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_ingress_global_cfg_v2(buf, 0 , &count , ppos);
	else
		len = config_val_from_registers_qudp_ingress_global_cfg(buf, 0 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_qudp_ingress_global_cfg_fh1(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_ingress_global_cfg_v2(buf, 1 , &count , ppos);
	else
		len = config_val_from_registers_qudp_ingress_global_cfg(buf, 1 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_qudp_ingress_global_cfg_fh2(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_ingress_global_cfg_v2(buf, 2 , &count , ppos);
	else
		len = config_val_from_registers_qudp_ingress_global_cfg(buf, 2 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}

static ssize_t cfg_value_from_qudp_egress_ipv4_cfg_fh0(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_egress_ipv4_cfg_v2(buf, 0 , &count , ppos);
	else{
		ECPRILOGERR("Debugfs, IPV4 fields are not supported for V1 HW \n");
		return -EINVAL;
	}
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_qudp_egress_ipv4_cfg_fh1(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_egress_ipv4_cfg_v2(buf, 1 , &count , ppos);
	else{
		ECPRILOGERR("Debugfs, IPV4 fields are not supported for V1 HW \n");
		return -EINVAL;
	}
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_qudp_egress_ipv4_cfg_fh2(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_egress_ipv4_cfg_v2(buf, 2 , &count , ppos);
	else{
		ECPRILOGERR("Debugfs, IPV4 fields are not supported for V1 HW \n");
		return -EINVAL;
	}
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;
}

static ssize_t cfg_value_from_qudp_egress_ipv6_cfg_fh0(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_egress_ipv6_cfg_v2(buf, 0 , &count , ppos);
	else{
		ECPRILOGERR("Debugfs, IPV6 fields are not supported for V1 HW \n");
		return -EINVAL;
	}
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_qudp_egress_ipv6_cfg_fh1(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_egress_ipv6_cfg_v2(buf, 1 , &count , ppos);
	else{
		ECPRILOGERR("Debugfs, IPV6 fields are not supported for V1 HW \n");
		return -EINVAL;
	}
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_qudp_egress_ipv6_cfg_fh2(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_egress_ipv6_cfg_v2(buf, 2 , &count , ppos);
	else{
		ECPRILOGERR("Debugfs, IPV6 fields are not supported for V1 HW \n");
		return -EINVAL;
	}
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;
}

static ssize_t cfg_value_from_qudp_ingress_vlan_fh0(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_ingress_vlan_v2(buf, 0 , &count , ppos);
	else
		len = config_val_from_registers_qudp_ingress_vlan(buf, 0 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_qudp_ingress_vlan_fh1(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_ingress_vlan_v2(buf, 1 , &count , ppos);
	else
		len = config_val_from_registers_qudp_ingress_vlan(buf, 1 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_qudp_ingress_vlan_fh2(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_ingress_vlan_v2(buf, 2 , &count , ppos);
	else
		len = config_val_from_registers_qudp_ingress_vlan(buf, 2 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_qudp_ingress_udp_class_fh0(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_ingress_udp_clss_port_v2(buf, 0 , &count , ppos);
	else
		len = config_val_from_registers_qudp_ingress_udp_clss_port(buf, 0 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_qudp_ingress_udp_class_fh1(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_ingress_udp_clss_port_v2(buf, 1 , &count , ppos);
	else
		len = config_val_from_registers_qudp_ingress_udp_clss_port(buf, 1 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_qudp_ingress_udp_class_fh2(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_ingress_udp_clss_port_v2(buf, 2 , &count , ppos);
	else
		len = config_val_from_registers_qudp_ingress_udp_clss_port(buf, 2 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}

static ssize_t cfg_value_from_qudp_ingress_dst_ip_fh0(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_ingress_dst_ip_v2(buf, 0 , &count , ppos);
	else
		len = config_val_from_registers_qudp_ingress_dst_ip(buf, 0 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_qudp_ingress_dst_ip_fh1(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_ingress_dst_ip_v2(buf, 1 , &count , ppos);
	else
		len = config_val_from_registers_qudp_ingress_dst_ip(buf, 1 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_qudp_ingress_dst_ip_fh2(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_ingress_dst_ip_v2(buf, 2 , &count , ppos);
	else
		len = config_val_from_registers_qudp_ingress_dst_ip(buf, 2 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_qudp_ingress_mac_addr_fh0(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_ingress_mac_addr_v2(buf, 0 , &count , ppos);
	else
		len = config_val_from_registers_qudp_ingress_mac_addr(buf, 0 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_qudp_ingress_mac_addr_fh1(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_ingress_mac_addr_v2(buf, 1 , &count , ppos);
	else
		len = config_val_from_registers_qudp_ingress_mac_addr(buf, 1 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_qudp_ingress_mac_addr_fh2(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_registers_qudp_ingress_mac_addr_v2(buf, 2 , &count , ppos);
	else
		len = config_val_from_registers_qudp_ingress_mac_addr(buf, 2 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_valid_bits_filt_fh0(struct file *file, char __user *buf,
		size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_valid_bits_filt_v2(buf, 0 , &count , ppos);
	else
		len = config_val_from_valid_bits_filt(buf, 0 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_valid_bits_filt_fh1(struct file *file, char __user *buf,
		size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_valid_bits_filt_v2(buf, 1 , &count , ppos);
	else
		len = config_val_from_valid_bits_filt(buf, 1 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_valid_bits_filt_fh2(struct file *file, char __user *buf,
		size_t count, loff_t *ppos)
{
	uint32_t len;

	if(ecpriss_hw_ver == 2)
		len = config_val_from_valid_bits_filt_v2(buf, 2 , &count , ppos);
	else
		len = config_val_from_valid_bits_filt(buf, 2 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}
static ssize_t cfg_value_from_qudp_ecpriss_filt(struct file *file, char __user *buf,
		size_t count, loff_t *ppos)
{
	uint32_t len;

	len = config_val_from_qudp_ecpriss_filt(buf, 2 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}

static ssize_t cfg_value_to_qudp_ecpriss_filt(struct file *file, const  char __user *buf,
		size_t count, loff_t *ppos)
{
	uint32_t len;

	len = config_val_to_qudp_ecpriss_filt(buf, 2 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;

}

static ssize_t cfg_value_from_global_ecpriss_stats_timeout(struct file *file, char __user *buf,
		size_t count, loff_t *ppos)
{
	uint32_t len;

	len = config_val_from_global_ecpriss_stats_timeout(buf, 2, &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}

static ssize_t cfg_value_to_global_ecpriss_stats_timeout(struct file *file, const char __user *buf,
		size_t count, loff_t *ppos)
{
	uint32_t len;

	len = config_val_to_global_ecpriss_stats_timeout(buf, 2, &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;


}
static ssize_t cfg_value_from_global_ecpriss_enable_len_check(struct file *file, char __user *buf,
		size_t count, loff_t *ppos)
{
	uint32_t len;

	len = config_val_from_global_ecpriss_enable_len_check(buf, 2, &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}

static ssize_t cfg_value_to_global_ecpriss_enable_len_check(struct file *file, const char __user *buf,
		size_t count, loff_t *ppos)
{
	uint32_t len;

	len = config_val_to_global_ecpriss_enable_len_check(buf, 2, &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;


}

static ssize_t cfg_value_from_qudp_ingress_action(struct file *file, char __user *buf,
		size_t count, loff_t *ppos)
{
	uint32_t len;

	len = config_val_from_qudp_ingress_action(buf, 2, &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}

static ssize_t cfg_value_to_qudp_ingress_action(struct file *file, const char __user *buf,
		size_t count, loff_t *ppos)
{
	uint32_t len;

	len = config_val_to_qudp_ingress_action(buf, 2, &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;


}

static ssize_t cfg_value_from_qudp_strict_filt_fh0(struct file *file, char __user *buf,
		size_t count, loff_t *ppos)
{
	uint32_t len;

	len = config_val_from_qudp_strict_filt(buf, 0, &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}

static ssize_t cfg_value_to_qudp_strict_filt_fh0(struct file *file, const char __user *buf,
		size_t count, loff_t *ppos)
{
	uint32_t len;

	len = config_val_to_qudp_strict_filt(buf, 0, &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;


}

static ssize_t cfg_value_from_qudp_strict_filt_fh1(struct file *file, char __user *buf,
		size_t count, loff_t *ppos)
{
	uint32_t len;

	len = config_val_from_qudp_strict_filt(buf, 1, &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}

static ssize_t cfg_value_to_qudp_strict_filt_fh1(struct file *file, const char __user *buf,
		size_t count, loff_t *ppos)
{
	uint32_t len;

	len = config_val_to_qudp_strict_filt(buf, 1, &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;


}

static ssize_t cfg_value_from_qudp_strict_filt_fh2(struct file *file, char __user *buf,
		size_t count, loff_t *ppos)
{
	uint32_t len;

	len = config_val_from_qudp_strict_filt(buf, 2, &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}

static ssize_t cfg_value_to_qudp_strict_filt_fh2(struct file *file, const char __user *buf,
		size_t count, loff_t *ppos)
{
	uint32_t len;

	len = config_val_to_qudp_strict_filt(buf, 2, &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;


}
static ssize_t cfg_value_to_xbar_lut_ocrx(struct file *file, const char __user *buf,
		size_t count, loff_t *ppos)
{
	uint32_t len;
	len = config_val_to_xbar_lut_ocrx(buf, &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;


}
static ssize_t cfg_value_to_xbar_lut_fhrx(struct file *file, const char __user *buf,
		size_t count, loff_t *ppos)
{
	uint32_t len;

	len = config_val_to_xbar_lut_fhrx(buf, &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;
}

void ecpriss_clear_all_qudp_stats(void)
{
	int i;
	// clearing QUDP stats for FH port
	for(i =0;i < MAX_PORTS; i++)
	{
	memset(&ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[i].stats_v2,0,sizeof(ecpriss_qudp_stats_v2));
	}
}
void ecpriss_clear_all_xbar_stats(void)
{
   // clearing XBAR stats
   memset(&ecpriss_pdata_v2->xbar_ctx_v2->stats_v2,0,sizeof(ecpriss_xbar_stats_s_v2));
}
void ecpriss_clear_all_stats(void)
{
   mutex_lock(&ecpriss_pdata_v2->ecpriss_mutex_lock);
   ecpriss_clear_all_qudp_stats();
   ecpriss_clear_all_xbar_stats();
   mutex_unlock(&ecpriss_pdata_v2->ecpriss_mutex_lock);
}
static ssize_t cfg_value_to_ecpriss_clear_stats(struct file *file, const char __user *buf,
		size_t count, loff_t *ppos)
{
	ecpriss_clear_all_stats();
	return count;
}
static struct file_operations stats_fh_ops_00 = {
	.read = stats_value_from_registers_fh_00,
};
static struct file_operations stats_fh_ops_01 = {
	.read = stats_value_from_registers_fh_01,
};
static struct file_operations stats_fh_ops_02 = {
	.read = stats_value_from_registers_fh_02,
};
static struct file_operations stats_fh_ops_03 = {
	.read = stats_value_from_registers_fh_03,
};
static struct file_operations stats_fh_ops_10 = {
	.read = stats_value_from_registers_fh_10,
};
static struct file_operations stats_fh_ops_11 = {
	.read = stats_value_from_registers_fh_11,
};
static struct file_operations stats_fh_ops_12 = {
	.read = stats_value_from_registers_fh_12,
};
static struct file_operations stats_fh_ops_13 = {
	.read = stats_value_from_registers_fh_13,
};
static struct file_operations stats_fh_ops_20 = {
	.read = stats_value_from_registers_fh_20,
};
static struct file_operations stats_fh_ops_21 = {
	.read = stats_value_from_registers_fh_21,
};
static struct file_operations stats_fh_ops_22 = {
	.read = stats_value_from_registers_fh_22,
};
static struct file_operations stats_fh_ops_23 = {
	.read = stats_value_from_registers_fh_23,
};

static struct file_operations error_fh_ops_00 = {
	.read = error_value_from_registers_fh_00,
};
static struct file_operations error_fh_ops_01 = {
	.read = error_value_from_registers_fh_01,
};
static struct file_operations error_fh_ops_02 = {
	.read = error_value_from_registers_fh_02,
};
static struct file_operations error_fh_ops_03 = {
	.read = error_value_from_registers_fh_03,
};
static struct file_operations error_fh_ops_10 = {
	.read = error_value_from_registers_fh_10,
};
static struct file_operations error_fh_ops_11 = {
	.read = error_value_from_registers_fh_11,
};
static struct file_operations error_fh_ops_12 = {
	.read = error_value_from_registers_fh_12,
};
static struct file_operations error_fh_ops_13 = {
	.read = error_value_from_registers_fh_13,
};
static struct file_operations error_fh_ops_20 = {
	.read = error_value_from_registers_fh_20,
};
static struct file_operations error_fh_ops_21 = {
	.read = error_value_from_registers_fh_21,
};
static struct file_operations error_fh_ops_22 = {
	.read = error_value_from_registers_fh_22,
};
static struct file_operations error_fh_ops_23 = {
	.read = error_value_from_registers_fh_23,
};

static struct file_operations stats_xbar_ops = {
	.read = stats_value_from_xbar,
};
static struct file_operations error_xbar_ops = {
	.read = error_value_from_xbar,
};

static struct file_operations cfg_xbar_lut_ops_fhrx_0 = {
	.read = cfg_value_from_xbar_lut_fhrx_0,
	.write = cfg_value_to_xbar_lut_fhrx,
};
static struct file_operations cfg_xbar_lut_ops_fhrx_1 = {
	.read = cfg_value_from_xbar_lut_fhrx_1,
	.write = cfg_value_to_xbar_lut_fhrx,
};
static struct file_operations cfg_xbar_lut_ops_fhrx_2 = {
	.read = cfg_value_from_xbar_lut_fhrx_2,
	.write = cfg_value_to_xbar_lut_fhrx,
};
static struct file_operations cfg_xbar_lut_ops_ocrx_0 = {
	.read = cfg_value_from_xbar_lut_ocrx_0,
	.write = cfg_value_to_xbar_lut_ocrx,
};
static struct file_operations cfg_xbar_lut_ops_ocrx_1 = {
	.read = cfg_value_from_xbar_lut_ocrx_1,
	.write = cfg_value_to_xbar_lut_ocrx,
};
static struct file_operations cfg_xbar_lut_ops_ocrx_2 = {
	.read = cfg_value_from_xbar_lut_ocrx_2,
	.write = cfg_value_to_xbar_lut_ocrx,
};
static struct file_operations cfg_xbar_lut_ops_c2crxul = {
	.read = cfg_value_from_xbar_lut_c2crxul,
};
static struct file_operations cfg_xbar_lut_ops_c2crxdl = {
	.read = cfg_value_from_xbar_lut_c2crxdl,
};
static struct file_operations cfg_xbar_global_ops = {
	.read = cfg_value_from_xbar_global,
};
static struct file_operations qudp_egress_udp_ports_fh0_ops = {
	.read = cfg_value_from_qudp_egress_udp_ports_fh0,
};
static struct file_operations qudp_egress_misc_cfg_fh0_ops = {
	.read = cfg_value_from_qudp_egress_misc_cfg_fh0,
};
static struct file_operations qudp_egress_vlan_ethertype_fh0_ops = {
	.read = cfg_value_from_qudp_egress_vlan_ethertype_fh0,
};
static struct file_operations qudp_egress_fh0_src_mac = {
	.read = cfg_value_from_qudp_egress_fh0_src_mac,
};
static struct file_operations qudp_egress_fh0_dst_mac = {
	.read = cfg_value_from_qudp_egress_fh0_dst_mac,
};
static struct file_operations qudp_egress_dst_ip_addr_fh0_ops = {
	.read = cfg_value_from_qudp_egress_dst_ip_addr_fh0,
};
static struct file_operations qudp_egress_src_ip_addr_fh0_ops = {
	.read = cfg_value_from_qudp_egress_src_ip_addr_fh0,
};
static struct file_operations qudp_egress_udp_ports_fh1_ops = {
	.read = cfg_value_from_qudp_egress_udp_ports_fh1,
};
static struct file_operations qudp_egress_misc_cfg_fh1_ops = {
	.read = cfg_value_from_qudp_egress_misc_cfg_fh1,
};
static struct file_operations qudp_egress_vlan_ethertype_fh1_ops = {
	.read = cfg_value_from_qudp_egress_vlan_ethertype_fh1,
};
static struct file_operations qudp_egress_fh1_src_mac = {
	.read = cfg_value_from_qudp_egress_fh1_src_mac,
};
static struct file_operations qudp_egress_fh1_dst_mac = {
	.read = cfg_value_from_qudp_egress_fh1_dst_mac,
};
static struct file_operations qudp_egress_dst_ip_addr_fh1_ops = {
	.read = cfg_value_from_qudp_egress_dst_ip_addr_fh1,
};
static struct file_operations qudp_egress_src_ip_addr_fh1_ops = {
	.read = cfg_value_from_qudp_egress_src_ip_addr_fh1,
};

static struct file_operations qudp_egress_udp_ports_fh2_ops = {
	.read = cfg_value_from_qudp_egress_udp_ports_fh2,
};
static struct file_operations qudp_egress_misc_cfg_fh2_ops = {
	.read = cfg_value_from_qudp_egress_misc_cfg_fh2,
};
static struct file_operations qudp_egress_vlan_ethertype_fh2_ops = {
	.read = cfg_value_from_qudp_egress_vlan_ethertype_fh2,
};
static struct file_operations qudp_egress_fh2_src_mac = {
	.read = cfg_value_from_qudp_egress_fh2_src_mac,
};
static struct file_operations qudp_egress_fh2_dst_mac = {
	.read = cfg_value_from_qudp_egress_fh2_dst_mac,
};
static struct file_operations qudp_egress_dst_ip_addr_fh2_ops = {
	.read = cfg_value_from_qudp_egress_dst_ip_addr_fh2,
};
static struct file_operations qudp_egress_src_ip_addr_fh2_ops = {
	.read = cfg_value_from_qudp_egress_src_ip_addr_fh2,
};

static struct file_operations qudp_ingress_global_cfg_fh0 = {
	.read = cfg_value_from_qudp_ingress_global_cfg_fh0,
};
static struct file_operations qudp_egress_global_cfg_ipv4_fh0 = {
	.read = cfg_value_from_qudp_egress_ipv4_cfg_fh0,
};
static struct file_operations qudp_egress_global_cfg_ipv6_fh0 = {
	.read = cfg_value_from_qudp_egress_ipv6_cfg_fh0,
};
static struct file_operations qudp_ingress_vlan_cfg_fh0 = {
	.read = cfg_value_from_qudp_ingress_vlan_fh0,
};
static struct file_operations qudp_ingress_udp_class_fh0 = {
	.read = cfg_value_from_qudp_ingress_udp_class_fh0,
};
static struct file_operations qudp_ingress_dst_ip_fh0 = {
	.read = cfg_value_from_qudp_ingress_dst_ip_fh0,
};
static struct file_operations qudp_ingress_mac_addr_fh0 = {
	.read = cfg_value_from_qudp_ingress_mac_addr_fh0,
};
static struct file_operations qudp_ingress_fltr_valid_bits_fh0 = {
	.read = cfg_value_from_valid_bits_filt_fh0,
};

static struct file_operations qudp_ingress_global_cfg_fh1 = {
	.read = cfg_value_from_qudp_ingress_global_cfg_fh1,
};
static struct file_operations qudp_egress_global_cfg_ipv4_fh1 = {
	.read = cfg_value_from_qudp_egress_ipv4_cfg_fh1,
};
static struct file_operations qudp_egress_global_cfg_ipv6_fh1 = {
	.read = cfg_value_from_qudp_egress_ipv6_cfg_fh1,
};
static struct file_operations qudp_ingress_vlan_cfg_fh1 = {
	.read = cfg_value_from_qudp_ingress_vlan_fh1,
};
static struct file_operations qudp_ingress_udp_class_fh1 = {
	.read = cfg_value_from_qudp_ingress_udp_class_fh1,
};
static struct file_operations qudp_ingress_dst_ip_fh1 = {
	.read = cfg_value_from_qudp_ingress_dst_ip_fh1,
};
static struct file_operations qudp_ingress_mac_addr_fh1 = {
	.read = cfg_value_from_qudp_ingress_mac_addr_fh1,
};
static struct file_operations qudp_ingress_fltr_valid_bits_fh1 = {
	.read = cfg_value_from_valid_bits_filt_fh1,
};

static struct file_operations qudp_ingress_global_cfg_fh2 = {
	.read = cfg_value_from_qudp_ingress_global_cfg_fh2,
};
static struct file_operations qudp_egress_global_cfg_ipv4_fh2 = {
	.read = cfg_value_from_qudp_egress_ipv4_cfg_fh2,
};
static struct file_operations qudp_egress_global_cfg_ipv6_fh2 = {
	.read = cfg_value_from_qudp_egress_ipv6_cfg_fh2,
};
static struct file_operations qudp_ingress_vlan_cfg_fh2 = {
	.read = cfg_value_from_qudp_ingress_vlan_fh2,
};
static struct file_operations qudp_ingress_udp_class_fh2 = {
	.read = cfg_value_from_qudp_ingress_udp_class_fh2,
};
static struct file_operations qudp_ingress_dst_ip_fh2 = {
	.read = cfg_value_from_qudp_ingress_dst_ip_fh2,
};
static struct file_operations qudp_ingress_mac_addr_fh2 = {
	.read = cfg_value_from_qudp_ingress_mac_addr_fh2,
};
static struct file_operations qudp_ingress_fltr_valid_bits_fh2 = {
	.read = cfg_value_from_valid_bits_filt_fh2,
};

static struct file_operations qudp_ecpriss_filt_config = {
	.read = cfg_value_from_qudp_ecpriss_filt,
	.write = cfg_value_to_qudp_ecpriss_filt,
};
static struct file_operations global_ecpriss_clear_stats_config={
	 .write=cfg_value_to_ecpriss_clear_stats,
};
static struct file_operations global_stats_timeout_config = {
	.read = cfg_value_from_global_ecpriss_stats_timeout,
	.write = cfg_value_to_global_ecpriss_stats_timeout,
};
static struct file_operations global_enable_len_check_config = {
	.read = cfg_value_from_global_ecpriss_enable_len_check,
	.write = cfg_value_to_global_ecpriss_enable_len_check,
};
static struct file_operations qudp_ingress_action_config = {
	.read = cfg_value_from_qudp_ingress_action,
	.write = cfg_value_to_qudp_ingress_action,
};
static struct file_operations qudp_strict_filt_config_fh0 = {
	.read = cfg_value_from_qudp_strict_filt_fh0,
	.write = cfg_value_to_qudp_strict_filt_fh0,
};
static struct file_operations qudp_strict_filt_config_fh1 = {
	.read = cfg_value_from_qudp_strict_filt_fh1,
	.write = cfg_value_to_qudp_strict_filt_fh1,
};
static struct file_operations qudp_strict_filt_config_fh2 = {
	.read = cfg_value_from_qudp_strict_filt_fh2,
	.write = cfg_value_to_qudp_strict_filt_fh2,
};



static struct file_operations dummy;

static struct file_operations *file_name_to_wrapper(char *filename)
{
	if(!filename){
		ECPRILOGERR("Null Pointer Input\n");
		return NULL;
	}
	if (!strncmp(filename, "fh:stats:00", FH_WRAPPER_SIZE))
	{
		return &stats_fh_ops_00;
	}
	else if (!strncmp(filename, "fh:stats:01", FH_WRAPPER_SIZE))
	{
		return &stats_fh_ops_01;
	}
	else if (!strncmp(filename, "fh:stats:02", FH_WRAPPER_SIZE))
	{
		return &stats_fh_ops_02;
	}
	else if (!strncmp(filename, "fh:stats:03", FH_WRAPPER_SIZE))
	{
		return &stats_fh_ops_03;
	}
	else if (!strncmp(filename, "fh:stats:10", FH_WRAPPER_SIZE))
	{
		return &stats_fh_ops_10;
	}
	else if (!strncmp(filename, "fh:stats:11", FH_WRAPPER_SIZE))
	{
		return &stats_fh_ops_11;
	}
	else if (!strncmp(filename, "fh:stats:12", FH_WRAPPER_SIZE))
	{
		return &stats_fh_ops_12;
	}
	else if (!strncmp(filename, "fh:stats:13", FH_WRAPPER_SIZE))
	{
		return &stats_fh_ops_13;
	}
	else if (!strncmp(filename, "fh:stats:20", FH_WRAPPER_SIZE))
	{
		return &stats_fh_ops_20;
	}
	else if (!strncmp(filename, "fh:stats:21", FH_WRAPPER_SIZE))
	{
		return &stats_fh_ops_21;
	}
	else if (!strncmp(filename, "fh:stats:22", FH_WRAPPER_SIZE))
	{
		return &stats_fh_ops_22;
	}
	else if (!strncmp(filename, "fh:stats:23", FH_WRAPPER_SIZE))
	{
		return &stats_fh_ops_23;
	}
	else if (!strncmp(filename, "fh:interrupts:00", FH_WRAPPER_SIZE))
	{
		return &error_fh_ops_00;
	}
	else if (!strncmp(filename, "fh:interrupts:01", FH_WRAPPER_SIZE))
	{
		return &error_fh_ops_01;
	}
	else if (!strncmp(filename, "fh:interrupts:02", FH_WRAPPER_SIZE))
	{
		return &error_fh_ops_02;
	}
	else if (!strncmp(filename, "fh:interrupts:03", FH_WRAPPER_SIZE))
	{
		return &error_fh_ops_03;
	}
	else if (!strncmp(filename, "fh:interrupts:10", FH_WRAPPER_SIZE))
	{
		return &error_fh_ops_10;
	}
	else if (!strncmp(filename, "fh:interrupts:11", FH_WRAPPER_SIZE))
	{
		return &error_fh_ops_11;
	}
	else if (!strncmp(filename, "fh:interrupts:12", FH_WRAPPER_SIZE))
	{
		return &error_fh_ops_12;
	}
	else if (!strncmp(filename, "fh:interrupts:13", FH_WRAPPER_SIZE))
	{
		return &error_fh_ops_13;
	}
	else if (!strncmp(filename, "fh:interrupts:20", FH_WRAPPER_SIZE))
	{
		return &error_fh_ops_20;
	}
	else if (!strncmp(filename, "fh:interrupts:21", FH_WRAPPER_SIZE))
	{
		return &error_fh_ops_21;
	}
	else if (!strncmp(filename, "fh:interrupts:22", FH_WRAPPER_SIZE))
	{
		return &error_fh_ops_22;
	}
	else if (!strncmp(filename, "fh:interrupts:23", FH_WRAPPER_SIZE))
	{
		return &error_fh_ops_23;
	}
	else if (!strncmp(filename, "ecpriss_filt", XBAR_WRAPPER_SIZE))
	{
		return &qudp_ecpriss_filt_config;
	}
	else if(!strncmp(filename, "ecpriss_clear_stats", XBAR_WRAPPER_SIZE))
	{
		return &global_ecpriss_clear_stats_config;
	}
	else if (!strncmp(filename, "xb:stats", XBAR_WRAPPER_SIZE))
	{
		return &stats_xbar_ops;
	}
	else if (!strncmp(filename, "xb:interrupts", XBAR_WRAPPER_SIZE))
	{
		return &error_xbar_ops;
	}
	else if (!strncmp(filename, "fh0:ocrx_fh0", XBAR_WRAPPER_SIZE))
	{
		return &cfg_xbar_lut_ops_ocrx_0;
	}
	else if (!strncmp(filename, "fh1:ocrx_fh1", XBAR_WRAPPER_SIZE))
	{
		return &cfg_xbar_lut_ops_ocrx_1;
	}
	else if (!strncmp(filename, "fh2:ocrx_fh2", XBAR_WRAPPER_SIZE))
	{
		return &cfg_xbar_lut_ops_ocrx_2;
	}
	else if (!strncmp(filename, "fh0:fhrx_fh0", XBAR_WRAPPER_SIZE))
	{
		return &cfg_xbar_lut_ops_fhrx_0;
	}
	else if (!strncmp(filename, "fh1:fhrx_fh1", XBAR_WRAPPER_SIZE))
	{
		return &cfg_xbar_lut_ops_fhrx_1;
	}
	else if (!strncmp(filename, "fh2:fhrx_fh2", XBAR_WRAPPER_SIZE))
	{
		return &cfg_xbar_lut_ops_fhrx_2;
	}
	else if (!strncmp(filename, "fh0:c2crxDL_fh0", XBAR_WRAPPER_SIZE))
	{
		return &cfg_xbar_lut_ops_c2crxdl;
	}
	else if (!strncmp(filename, "fh1:c2crxDL_fh1", XBAR_WRAPPER_SIZE))
	{
		return &cfg_xbar_lut_ops_c2crxdl;
	}
	else if (!strncmp(filename, "fh2:c2crxDL_fh2", XBAR_WRAPPER_SIZE))
	{
		return &cfg_xbar_lut_ops_c2crxdl;
	}
	else if (!strncmp(filename, "fh0:c2crxUL_fh0", XBAR_WRAPPER_SIZE))
	{
		return &cfg_xbar_lut_ops_c2crxul;
	}
	else if (!strncmp(filename, "fh1:c2crxUL_fh1", XBAR_WRAPPER_SIZE))
	{
		return &cfg_xbar_lut_ops_c2crxul;
	}
	else if (!strncmp(filename, "fh2:c2crxUL_fh2", XBAR_WRAPPER_SIZE))
	{
		return &cfg_xbar_lut_ops_c2crxul;
	}
	else if (!strncmp(filename, "xbar:global_config", XBAR_WRAPPER_SIZE))
	{
		return &cfg_xbar_global_ops;
	}

	else if (!strncmp(filename, "fh0:udp_ports", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_udp_ports_fh0_ops;
	}
	else if (!strncmp(filename, "fh0:src_ip_addr", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_src_ip_addr_fh0_ops;
	}
	else if (!strncmp(filename, "fh0:dst_ip_addr", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_dst_ip_addr_fh0_ops;
	}
	else if (!strncmp(filename, "fh0:misc", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_misc_cfg_fh0_ops;
	}
	else if (!strncmp(filename, "fh0:vlan_ethertype", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_vlan_ethertype_fh0_ops;
	}
	else if (!strncmp(filename, "fh0:src_mac", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_fh0_src_mac;
	}
	else if (!strncmp(filename, "fh0:dst_mac", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_fh0_dst_mac;
	}
	else if (!strncmp(filename, "fh1:udp_ports", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_udp_ports_fh1_ops;
	}
	else if (!strncmp(filename, "fh1:src_ip_addr", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_src_ip_addr_fh1_ops;
	}
	else if (!strncmp(filename, "fh1:dst_ip_addr", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_dst_ip_addr_fh1_ops;
	}
	else if (!strncmp(filename, "fh1:misc", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_misc_cfg_fh1_ops;
	}
	else if (!strncmp(filename, "fh1:vlan_ethertype", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_vlan_ethertype_fh1_ops;
	}
	else if (!strncmp(filename, "fh1:src_mac", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_fh1_src_mac;
	}
	else if (!strncmp(filename, "fh1:dst_mac", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_fh1_dst_mac;
	}

	else if (!strncmp(filename, "fh2:udp_ports", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_udp_ports_fh2_ops;
	}
	else if (!strncmp(filename, "fh2:src_ip_addr", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_src_ip_addr_fh2_ops;
	}
	else if (!strncmp(filename, "fh2:dst_ip_addr", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_dst_ip_addr_fh2_ops;
	}
	else if (!strncmp(filename, "fh2:misc", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_misc_cfg_fh2_ops;
	}
	else if (!strncmp(filename, "fh2:vlan_ethertype", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_vlan_ethertype_fh2_ops;
	}
	else if (!strncmp(filename, "fh2:src_mac", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_fh2_src_mac;
	}
	else if (!strncmp(filename, "fh2:dst_mac", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_fh2_dst_mac;
	}
	else if (!strncmp(filename, "fh0:ingress_config", XBAR_WRAPPER_SIZE))
	{
		return &qudp_ingress_global_cfg_fh0;
	}
	else if (!strncmp(filename, "fh0:egress_ipv4_cfg", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_global_cfg_ipv4_fh0;
	}
	else if (!strncmp(filename, "fh0:egress_ipv6_cfg", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_global_cfg_ipv6_fh0;
	}
	else if (!strncmp(filename, "fh0:vlan_fltr", XBAR_WRAPPER_SIZE))
	{
		return &qudp_ingress_vlan_cfg_fh0;
	}
	else if (!strncmp(filename, "fh0:udp_classification", XBAR_WRAPPER_SIZE))
	{
		return &qudp_ingress_udp_class_fh0;
	}
	else if (!strncmp(filename, "fh0:ip_dts_fltr", XBAR_WRAPPER_SIZE))
	{
		return &qudp_ingress_dst_ip_fh0;
	}
	else if (!strncmp(filename, "fh0:mac", XBAR_WRAPPER_SIZE))
	{
		return &qudp_ingress_mac_addr_fh0;
	}
	else if (!strncmp(filename, "fh0:valid_bits", XBAR_WRAPPER_SIZE))
	{
		return &qudp_ingress_fltr_valid_bits_fh0;
	}
	else if (!strncmp(filename, "fh1:ingress_config", XBAR_WRAPPER_SIZE))
	{
		return &qudp_ingress_global_cfg_fh1;
	}
	else if (!strncmp(filename, "fh1:egress_ipv4_cfg", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_global_cfg_ipv4_fh1;
	}
	else if (!strncmp(filename, "fh1:egress_ipv6_cfg", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_global_cfg_ipv6_fh1;
	}
	else if (!strncmp(filename, "fh1:vlan_fltr", XBAR_WRAPPER_SIZE))
	{
		return &qudp_ingress_vlan_cfg_fh1;
	}
	else if (!strncmp(filename, "fh1:udp_classification", XBAR_WRAPPER_SIZE))
	{
		return &qudp_ingress_udp_class_fh1;
	}
	else if (!strncmp(filename, "fh1:ip_dts_fltr", XBAR_WRAPPER_SIZE))
	{
		return &qudp_ingress_dst_ip_fh1;
	}
	else if (!strncmp(filename, "fh1:mac", XBAR_WRAPPER_SIZE))
	{
		return &qudp_ingress_mac_addr_fh1;
	}
	else if (!strncmp(filename, "fh1:valid_bits", XBAR_WRAPPER_SIZE))
	{
		return &qudp_ingress_fltr_valid_bits_fh1;
	}

	else if (!strncmp(filename, "fh2:ingress_config", XBAR_WRAPPER_SIZE))
	{
		return &qudp_ingress_global_cfg_fh2;
	}
	else if (!strncmp(filename, "fh2:egress_ipv4_cfg", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_global_cfg_ipv4_fh2;
	}
	else if (!strncmp(filename, "fh2:egress_ipv6_cfg", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_global_cfg_ipv6_fh2;
	}
	else if (!strncmp(filename, "fh2:vlan_fltr", XBAR_WRAPPER_SIZE))
	{
		return &qudp_ingress_vlan_cfg_fh2;
	}
	else if (!strncmp(filename, "fh2:udp_classification", XBAR_WRAPPER_SIZE))
	{
		return &qudp_ingress_udp_class_fh2;
	}
	else if (!strncmp(filename, "fh2:ip_dts_fltr", XBAR_WRAPPER_SIZE))
	{
		return &qudp_ingress_dst_ip_fh2;
	}
	else if (!strncmp(filename, "fh2:mac", XBAR_WRAPPER_SIZE))
	{
		return &qudp_ingress_mac_addr_fh2;
	}
	else if (!strncmp(filename, "fh2:valid_bits", XBAR_WRAPPER_SIZE))
	{
		return &qudp_ingress_fltr_valid_bits_fh2;
	}
	else if (!strncmp(filename, "ecpriss_stats_timeout", XBAR_WRAPPER_SIZE))
	{
		return &global_stats_timeout_config;
	}
	else if (!strncmp(filename, "ecpriss_enable_len_check", XBAR_WRAPPER_SIZE))
	{
		return &global_enable_len_check_config;
	}

	else if (!strncmp(filename, "ecpriss_enable_len_check", XBAR_WRAPPER_SIZE))
	{
		return &global_enable_len_check_config;
	}

	else if (!strncmp(filename, "ecpriss_config_qudp_ingress_action", XBAR_WRAPPER_SIZE))
	{
		return &qudp_ingress_action_config;
	}
	else if (!strncmp(filename, "fh0:qudp_strict_filt_cfg_fh0", XBAR_WRAPPER_SIZE))
	{
		return &qudp_strict_filt_config_fh0;
	}
	else if (!strncmp(filename, "fh1:qudp_strict_filt_cfg_fh1", XBAR_WRAPPER_SIZE))
	{
		return &qudp_strict_filt_config_fh1;
	}
	else if (!strncmp(filename, "fh2:qudp_strict_filt_cfg_fh2", XBAR_WRAPPER_SIZE))
	{
		return &qudp_strict_filt_config_fh2;
	}

	else{
		ECPRILOGDBG("Invalid file name, no entry available\n");
		return &dummy;
	}
	return NULL;
}


int32_t setup_debugfs_directory()
{
        char token[64];
	char my_delm;
        int index = 0;
	int len = 0;
	struct file_operations *fileops = NULL;
	struct dentry *kobj_root = NULL;
	int curr_index = 0;
	parser_s parser_in;

        remove_whitespaces(input_string, sizeof(input_string));
	//ECPRILOGERR("%s\n", input_string);
	token[63] = '\0';

	parser_in.source = input_string;
	parser_in.delim = "{},";
	parser_in.token = token;
	parser_in.index = &index;
	parser_in.token_len = sizeof(token);
	parser_in.delim_len = 4;
	parser_in.source_len = sizeof(input_string);

	my_delm = parser(&parser_in);
        while (my_delm != 0){
		len= strlen(token);
		//ECPRILOGERR("token: %s\n",token);

                if(token[0] == '{' && len >2)
                {
			remove_firstchar(token, sizeof(token));
			//ECPRILOGERR("token after removal: %s\n",token);

			if(curr_index == 0)
			{
				list_dv[curr_index] = debugfs_create_dir(token,NULL);
				//ECPRILOGERR("Curr_index = %u, inserting %s, parent was null", curr_index, token);
				//ECPRILOGERR("Incremmting cur_index +1\n");
				curr_index++;
			}else{
				kobj_root = debugfs_create_dir(token, list_dv[curr_index -1]);
				list_dv[curr_index] = kobj_root;
				//ECPRILOGERR("Curr_index = %u, inserting %s, parent was %u", curr_index, token, curr_index-1);
				//ECPRILOGERR("Incremmting cur_index +1\n");
				curr_index++;
			}
                }else if( token[0] == '}'  && len > 2)
                {
				remove_firstchar(token, sizeof(token));
				//ECPRILOGERR("token after removal: %s\n",token);
				//ECPRILOGERR("Curr_index = %u, inserting %s, parent was %u", curr_index, token, curr_index-1);
				//ECPRILOGERR("Decresing cur_index -1\n");
					curr_index--;
			if(curr_index > 0){
				//ECPRILOGERR("inserting at Curr_index = %u, inserting %s, parent was %u", curr_index, token, curr_index-1);
				kobj_root = debugfs_create_dir(token, list_dv[curr_index -1 ]);
				list_dv[curr_index] = kobj_root;
					//ECPRILOGERR("Incremmting cur_index +1\n");
					curr_index++;
			}

                }else if(token[0] == ',' && len > 2){

			// we want to create file
			remove_firstchar(token, sizeof(token));
			//ECPRILOGERR("token after removal: %s\n",token);
			// file_name_to_callback , this will return a function pointer
			fileops = file_name_to_wrapper(token);
			get_file_name(token, sizeof(token));
			//ECPRILOGERR("token after get_file_name: %s\n",token);
			if(!debugfs_create_file(token, 0444, list_dv[curr_index - 1], 0, fileops)){
				//ECPRILOGERR("Unable to create the debugfs file...\n");
			}
			//ECPRILOGERR("Curr_index = %u, inserting %s, parent was %u", curr_index, token, curr_index -1 );

		}else if(token[0] == '}' && len < 2){
			//ECPRILOGERR("Curr_index = %u, inserting Nothing, parent was %u", curr_index,  curr_index+1);
			//ECPRILOGERR("Decresing cur_index -1\n");
			curr_index-- ;

		}
		my_delm = parser(&parser_in);
        }
        return 0;

}
void clear_debugfs_directory(void)
{
	if(list_dv[0])
		debugfs_remove_recursive(list_dv[0]);
}
/*****************************************************************************/
#endif /* CONFIG_DEBUG_FS */
