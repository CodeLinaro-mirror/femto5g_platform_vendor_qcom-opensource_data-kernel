/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

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

#undef pr_fmt
#define pr_fmt(fmt) "::%s:%u::" fmt, __func__, __LINE__

struct dentry *list_dv[64];
char input_string[] = TREE;
#define MAX_STR_SIZE (NUM_OF_FHP * LUT_INDEX * LUT_INDEX)
char max_str[NUM_OF_FHP * LUT_INDEX * LUT_INDEX];
/*
 * only white listed alphbates are allowed
 * { } , _  : and 0 to 9 a to z A to Z
 */
/*****************************************************************************/
static void remove_whitespaces(char * str){
        int i,j;
        for(i = 0, j=0; str[i] != '\0'; i++)
        {
                if((str[i] >= 'a' && str[i] <= 'z') ||
                                (str[i] >= 'A' && str[i] <='Z') ||
                                (str[i] >= '0' && str[i] <= '9') ||
                                (str[i] == '}') ||
                                (str[i] == '{') ||
                                (str[i] == ',') ||
				(str[i] == '_') ||
				(str[i] == ':'))
                {
                        str[j++]= str[i];
                }
        }
        str[j] = 0;
}
static char parser(char * source , char *delim, char *token, int *index){
        int i,j,k;

        if(!source || !token || !delim)
                return 0;

        memset(token,0,64);
        for(i= *index,j=0; source[i] !=0; i++){
                for(k=0;delim[k] !=0; k++){
                        if(source[i] == delim[k]){
                                if(strlen(token) == 0)
                                {
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
static void remove_firstchar(char * str){
	int i;
	int len;

	if(!str)
		return;
	len = strlen(str);

	for(i=0;i<len;i++){
		str[i] = str[i+1];
	}
	return;

}
static void get_file_name(char *filename){

	int index;
	char token[64];
	int i;
	int iscoln = 0;
	for(i=0; filename[i] !=0 || i < 64 ;i++){
		if(filename[i] ==  ':'){
			iscoln = 1;
			break;
		}
	}
	if(!iscoln)
		return;

	if(!filename)
		return;
	parser(filename, ":",token, &index);
	parser(filename, ":",token, &index);
	remove_firstchar(token);
	scnprintf(filename, sizeof(token), "%s", token);
	return;
}
/*****/
// Debugfs
typedef enum config_param{
	FHRX,
	OCRX,
	C2CRXUL,
	C2CRXDL,
	GLOBAL_CFG
}cfg_prm_u;

static ssize_t config_val_from_registers_qudp_ingress_mac_addr(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
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

		ecpriss_qudp_ingress_config_stats(fh_index);

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
		pr_err("strlen = %u \n",data_size);
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

		ecpriss_qudp_ingress_config_stats(fh_index);

		for(fltr_table_index = 0; fltr_table_index < NUM_OF_FLTR; fltr_table_index++){

			if(ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.ip_addr[fh_index][fltr_table_index].dst_ip0.value){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", fltr_table_index);
				RESET_STR(temp_stat_val_str);
				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
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

				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
						ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.ip_addr[fh_index][fltr_table_index].dst_ip1.value);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);

				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
						ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.ip_addr[fh_index][fltr_table_index].dst_ip2.value);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);

				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
						ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.ip_addr[fh_index][fltr_table_index].dst_ip3.value);
				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);
				strlcat(max_str, "\n",
						max_str_size);

			}

		}
		data_size = strlen(max_str);
		pr_err("strlen = %u \n",data_size);
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

		ecpriss_qudp_ingress_config_stats(fh_index);

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
		pr_err("strlen = %u \n",data_size);
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

		ecpriss_qudp_ingress_config_stats(fh_index);

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
		pr_err("strlen = %u \n",data_size);
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

		ecpriss_qudp_ingress_config_stats(fh_index);


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
		pr_err("strlen = %u \n",data_size);
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

		ecpriss_qudp_egress_config_stats(fh_index);

		for(egress_table_index = 0; egress_table_index < NUM_EGRESS_ENTRY; egress_table_index++){

			if(ecpriss_pdata->cfg_stats.qudp_cfg.egress.src_ip_addr[fh_index][egress_table_index].ip_src0.value){

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

			}

			if(ecpriss_pdata->cfg_stats.qudp_cfg.egress.src_ip_addr[fh_index][egress_table_index].ip_src1.value){

				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
						ecpriss_pdata->cfg_stats.qudp_cfg.egress.src_ip_addr[fh_index][egress_table_index].ip_src1.value);

				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);

			}

			if(ecpriss_pdata->cfg_stats.qudp_cfg.egress.src_ip_addr[fh_index][egress_table_index].ip_src2.value){

				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
						ecpriss_pdata->cfg_stats.qudp_cfg.egress.src_ip_addr[fh_index][egress_table_index].ip_src2.value);

				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);

			}

			if(ecpriss_pdata->cfg_stats.qudp_cfg.egress.src_ip_addr[fh_index][egress_table_index].ip_src3.value){

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
		pr_err("strlen = %u \n",data_size);
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

		ecpriss_qudp_egress_config_stats(fh_index);

		for(egress_table_index = 0; egress_table_index < NUM_EGRESS_ENTRY; egress_table_index++){

			if(ecpriss_pdata->cfg_stats.qudp_cfg.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst0.value){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", egress_table_index);
				RESET_STR(temp_stat_val_str);
				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
						ecpriss_pdata->cfg_stats.qudp_cfg.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst0.value);

				strlcat(max_str, "dst_ip_addr_0:1:2:3_fh_",
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

			}

			if(ecpriss_pdata->cfg_stats.qudp_cfg.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst1.value){

				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
						ecpriss_pdata->cfg_stats.qudp_cfg.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst1.value);

				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);

			}

			if(ecpriss_pdata->cfg_stats.qudp_cfg.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst2.value){

				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
						ecpriss_pdata->cfg_stats.qudp_cfg.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst2.value);

				strlcat(max_str, ":", max_str_size);
				strlcat(max_str, temp_stat_val_str,
						max_str_size);

			}

			if(ecpriss_pdata->cfg_stats.qudp_cfg.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst3.value){

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
		pr_err("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}

static ssize_t config_val_from_registers_qudp_egress_eth_src0_port(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
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

		ecpriss_qudp_egress_config_stats(fh_index);

		for(egress_table_index = 0; egress_table_index < NUM_EGRESS_ENTRY; egress_table_index++){

			if(ecpriss_pdata->cfg_stats.qudp_cfg.egress.eth_src0_port[fh_index][egress_table_index].value){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", egress_table_index);
				RESET_STR(temp_stat_val_str);
				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
						ecpriss_pdata->cfg_stats.qudp_cfg.egress.eth_src0_port[fh_index][egress_table_index].value);

				strlcat(max_str, "eth_src0_port_fh_",
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
		pr_err("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}

static ssize_t config_val_from_registers_qudp_egress_eth_src1_dst1_port(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
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

		ecpriss_qudp_egress_config_stats(fh_index);

		for(egress_table_index = 0; egress_table_index < NUM_EGRESS_ENTRY; egress_table_index++){

			if(ecpriss_pdata->cfg_stats.qudp_cfg.egress.eth_src1_dst1_port[fh_index][egress_table_index].dst_msb){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", egress_table_index);
				RESET_STR(temp_stat_val_str);
				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
						ecpriss_pdata->cfg_stats.qudp_cfg.egress.eth_src1_dst1_port[fh_index][egress_table_index].dst_msb);

				strlcat(max_str, "eth_src1_dst1_port_dst_msb_fh_",
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

			if(ecpriss_pdata->cfg_stats.qudp_cfg.egress.eth_src1_dst1_port[fh_index][egress_table_index].src_msb){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", egress_table_index);
				RESET_STR(temp_stat_val_str);
				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
						ecpriss_pdata->cfg_stats.qudp_cfg.egress.eth_src1_dst1_port[fh_index][egress_table_index].src_msb);

				strlcat(max_str, "eth_src1_dst1_port_src_msb_fh_",
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
		pr_err("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}


static ssize_t config_val_from_registers_qudp_egress_eth_dst0_port(char __user *buf, int fh_index, size_t *count, loff_t *ppos)
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

		ecpriss_qudp_egress_config_stats(fh_index);

		for(egress_table_index = 0; egress_table_index < NUM_EGRESS_ENTRY; egress_table_index++){

			if(ecpriss_pdata->cfg_stats.qudp_cfg.egress.eth_dst0_port[fh_index][egress_table_index].value){

				RESET_STR(index_str);
				scnprintf(index_str, TEMP_STR_MIN_SIZE, "%u", egress_table_index);
				RESET_STR(temp_stat_val_str);
				scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%u",
						ecpriss_pdata->cfg_stats.qudp_cfg.egress.eth_dst0_port[fh_index][egress_table_index].value);

				strlcat(max_str, "eth_dst0_port_fh_",
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
		pr_err("strlen = %u \n",data_size);
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

		ecpriss_qudp_egress_config_stats(fh_index);

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
		pr_err("strlen = %u \n",data_size);
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

		ecpriss_qudp_egress_config_stats(fh_index);

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
		pr_err("strlen = %u \n",data_size);
	}
	if(*ppos  >= max_str_size)
		return 0;

	if( *ppos + *count > data_size)
		*count =  data_size - *ppos;

	ret_val = copy_to_user(buf,(max_str + *ppos), *count);
	return data_size;
}
static ssize_t config_val_from_registers_xbar(char __user *buf, cfg_prm_u param)
{
	int fh_index;
	int pcid_index;
	char fh_str[TEMP_STR_MAX_SIZE];
	char pcid_str[TEMP_STR_MAX_SIZE];
	char temp_stat_val_str[TEMP_STAT_VAL_STR_MAX_SIZE];
	int ret_val = 0;
	int max_str_size = sizeof(max_str);

	memset(max_str,0,sizeof(max_str));

	ecpriss_xbar_config_sats();
	switch (param){
		case FHRX :
			for(fh_index=0; fh_index < NUM_OF_FHP; fh_index++) {
				for(pcid_index=0; pcid_index < LUT_INDEX; pcid_index++) {
					if(ecpriss_pdata->cfg_stats.xbar_cfg.lut_cfg.fhrx[fh_index][pcid_index]){
						RESET_STR(fh_str);
						scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);
						RESET_STR(pcid_str);
						scnprintf(pcid_str, TEMP_STR_MIN_SIZE, "%u", pcid_index);
						RESET_STR(temp_stat_val_str);
						scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
								ecpriss_pdata->cfg_stats.xbar_cfg.lut_cfg.fhrx[fh_index][pcid_index]);

						strlcat(max_str, "xbar_lut_fhrx_config_fh_",
								max_str_size);
						strlcat(max_str, fh_str,
								max_str_size);
						strlcat(max_str, "_pcid_",
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
			}
			break;
		case OCRX :
			for(fh_index=0; fh_index < NUM_OF_FHP; fh_index++) {
				for(pcid_index=0; pcid_index < LUT_INDEX; pcid_index++) {
					if(ecpriss_pdata->cfg_stats.xbar_cfg.lut_cfg.ocrx[fh_index][pcid_index]){
						RESET_STR(fh_str);
						scnprintf(fh_str, TEMP_STR_MIN_SIZE, "%u", fh_index);
						RESET_STR(pcid_str);
						scnprintf(pcid_str, TEMP_STR_MIN_SIZE, "%u", pcid_index);
						RESET_STR(temp_stat_val_str);
						scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
								ecpriss_pdata->cfg_stats.xbar_cfg.lut_cfg.ocrx[fh_index][pcid_index]);

						strlcat(max_str, "xbar_lut_ocrx_config_fh_",
								max_str_size);
						strlcat(max_str, fh_str,
								max_str_size);
						strlcat(max_str, "_pcid_",
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
			}
			break;
		case GLOBAL_CFG :
			strlcat(max_str, "xbar_lut_global_cfg:",max_str_size);
			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "0x%x",
				ecpriss_pdata->cfg_stats.xbar_cfg.global_cfg.global);
			strlcat(max_str, temp_stat_val_str, max_str_size);
			strlcat(max_str, "\n",max_str_size);
		default :
			pr_err("default case\n");
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
	uint32_t j = 0;
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
	char fh_index[TEMP_STR_MAX_SIZE];

	final_stats_str =
		(char *)kzalloc(FINAL_STATS_DYNAMIC_STR_MAX_SIZE, GFP_KERNEL);

	if (!final_stats_str)
	{
		goto err;
	}

	RESET_STR(temp_stat_val_str);
	RESET_STR(link_id);
	ecpriss_xbar_print_stats();

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
	for (i = 0; i < NUM_OF_FHP; i++)
	{
		RESET_STR(fh_index);
		scnprintf(fh_index, TEMP_STR_MIN_SIZE, "%u", i);

		for (j = 0; j < LUT_INDEX; j++)
		{
			RESET_STR(link_id);
			scnprintf(link_id, TEMP_STR_MIN_SIZE, "%u", j);

			temp_stat_val =
				ecpriss_pdata->xbar_ctx->stats.xbar_fh_port[i].xbar_fhrx_lut[j];
			scnprintf(temp_stat_val_str, TEMP_STAT_VAL_STR_MAX_SIZE, "%lu",
					  temp_stat_val);

			strlcat(final_stats_str, "xbar_lut_fhrx_config_fh_",
					FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
			strlcat(final_stats_str, fh_index,
					FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
			strlcat(final_stats_str, "_pcid_",
					FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
			strlcat(final_stats_str, link_id,
					FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
			strlcat(final_stats_str, ":", FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
			strlcat(final_stats_str, temp_stat_val_str,
					FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
			strlcat(final_stats_str, "}\n",
					FINAL_STATS_DYNAMIC_STR_MAX_SIZE);
		}
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
		pr_err("Memory allocation failure \n");
		goto err;
	}

	RESET_STR(temp_stat_val_str);

	ecpriss_qudp_print_fh_ingress_stats(port, link);
	ecpriss_qudp_print_fh_egress_stats(port, link);

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
		pr_err("Memory allocation failure \n");
		goto err;
	}

	RESET_STR(temp_stat_val_str);

	ecpriss_qudp_print_fh_ingress_stats(port, link);
	ecpriss_qudp_print_fh_egress_stats(port, link);

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

	pr_err("DUMINP mayank : %s \n",final_stats_str);

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
	len = error_value_from_registers_xbar(buf);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t cfg_value_from_xbar_lut_fhrx(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	len = config_val_from_registers_xbar(buf,FHRX);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;

	return count;
}
static ssize_t cfg_value_from_xbar_lut_ocrx(struct file *file, char __user *buf,
 				 size_t count, loff_t *ppos)
{
	uint32_t len;
	len = config_val_from_registers_xbar(buf,OCRX);
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
	len = config_val_from_registers_xbar(buf,C2CRXUL);
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
	len = config_val_from_registers_xbar(buf,C2CRXDL);
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
	len = config_val_from_registers_xbar(buf,GLOBAL_CFG);
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

	len = config_val_from_registers_qudp_egress_udp_ports(buf, 2 , &count , ppos);
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

	len = config_val_from_registers_qudp_egress_vlan_ethertype(buf, 2 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}

static ssize_t cfg_value_from_qudp_egress_eth_dst0_port_fh0(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	len = config_val_from_registers_qudp_egress_eth_dst0_port(buf, 0 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}

static ssize_t cfg_value_from_qudp_egress_eth_dst0_port_fh1(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	len = config_val_from_registers_qudp_egress_eth_dst0_port(buf, 1, &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}

static ssize_t cfg_value_from_qudp_egress_eth_dst0_port_fh2(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	len = config_val_from_registers_qudp_egress_eth_dst0_port(buf, 2 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}

static ssize_t cfg_value_from_qudp_egress_eth_src1_dst1_fh0(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	len = config_val_from_registers_qudp_egress_eth_src1_dst1_port(buf, 0 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}

static ssize_t cfg_value_from_qudp_egress_eth_src1_dst1_fh1(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	len = config_val_from_registers_qudp_egress_eth_src1_dst1_port(buf, 1 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}

static ssize_t cfg_value_from_qudp_egress_eth_src1_dst1_fh2(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	len = config_val_from_registers_qudp_egress_eth_src1_dst1_port(buf, 2 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}

static ssize_t cfg_value_from_qudp_egress_eth_src0_port_fh0(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	len = config_val_from_registers_qudp_egress_eth_src0_port(buf, 0 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}

static ssize_t cfg_value_from_qudp_egress_eth_src0_port_fh1(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	len = config_val_from_registers_qudp_egress_eth_src0_port(buf, 1 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
	return count;

}

static ssize_t cfg_value_from_qudp_egress_eth_src0_port_fh2(struct file *file, char __user *buf,
			size_t count, loff_t *ppos)
{
	uint32_t len;

	len = config_val_from_registers_qudp_egress_eth_src0_port(buf, 2 , &count , ppos);
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

	len = config_val_from_registers_qudp_ingress_global_cfg(buf, 2 , &count , ppos);
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

	len = config_val_from_registers_qudp_ingress_mac_addr(buf, 2 , &count , ppos);
	if((*ppos + count) > len){
		count = len - *ppos;
	}
	*ppos += count;
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

static struct file_operations cfg_xbar_lut_ops_fhrx = {
	.read = cfg_value_from_xbar_lut_fhrx,
};
static struct file_operations cfg_xbar_lut_ops_ocrx = {
	.read = cfg_value_from_xbar_lut_ocrx,
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
static struct file_operations qudp_egress_vlan_ethertype_fh0_ops = {
	.read = cfg_value_from_qudp_egress_vlan_ethertype_fh0,
};
static struct file_operations qudp_egress_eth0_dst0_fh0_ops = {
	.read = cfg_value_from_qudp_egress_eth_dst0_port_fh0,
};
static struct file_operations qudp_egress_eth_src1_dst1_fh0_ops = {
	.read = cfg_value_from_qudp_egress_eth_src1_dst1_fh0,
};
static struct file_operations qudp_egress_eth_src0_fh0_ops = {
	.read = cfg_value_from_qudp_egress_eth_src0_port_fh0,
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
static struct file_operations qudp_egress_vlan_ethertype_fh1_ops = {
	.read = cfg_value_from_qudp_egress_vlan_ethertype_fh1,
};
static struct file_operations qudp_egress_eth0_dst0_fh1_ops = {
	.read = cfg_value_from_qudp_egress_eth_dst0_port_fh1,
};
static struct file_operations qudp_egress_eth_src1_dst1_fh1_ops = {
	.read = cfg_value_from_qudp_egress_eth_src1_dst1_fh1,
};
static struct file_operations qudp_egress_eth_src0_fh1_ops = {
	.read = cfg_value_from_qudp_egress_eth_src0_port_fh1,
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
static struct file_operations qudp_egress_vlan_ethertype_fh2_ops = {
	.read = cfg_value_from_qudp_egress_vlan_ethertype_fh2,
};
static struct file_operations qudp_egress_eth0_dst0_fh2_ops = {
	.read = cfg_value_from_qudp_egress_eth_dst0_port_fh2,
};
static struct file_operations qudp_egress_eth_src1_dst1_fh2_ops = {
	.read = cfg_value_from_qudp_egress_eth_src1_dst1_fh2,
};
static struct file_operations qudp_egress_eth_src0_fh2_ops = {
	.read = cfg_value_from_qudp_egress_eth_src0_port_fh2,
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

static struct file_operations qudp_ingress_global_cfg_fh1 = {
	.read = cfg_value_from_qudp_ingress_global_cfg_fh1,
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

static struct file_operations qudp_ingress_global_cfg_fh2 = {
	.read = cfg_value_from_qudp_ingress_global_cfg_fh2,
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



static struct file_operations dummy;

static struct file_operations *file_name_to_wrapper(char *filename)
{
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
	else if (!strncmp(filename, "xb:stats", XBAR_WRAPPER_SIZE))
	{
		return &stats_xbar_ops;
	}
	else if (!strncmp(filename, "xb:interrupts", XBAR_WRAPPER_SIZE))
	{
		return &error_xbar_ops;
	}
	else if (!strncmp(filename, "ocrx", XBAR_WRAPPER_SIZE))
	{
		return &cfg_xbar_lut_ops_ocrx;
	}
	else if (!strncmp(filename, "fhrx", XBAR_WRAPPER_SIZE))
	{
		return &cfg_xbar_lut_ops_fhrx;
	}
	else if (!strncmp(filename, "c2crxDL", XBAR_WRAPPER_SIZE))
	{
		return &cfg_xbar_lut_ops_c2crxdl;
	}
	else if (!strncmp(filename, "c2crxUL", XBAR_WRAPPER_SIZE))
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
	else if (!strncmp(filename, "fh0:vlan_ethertype", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_vlan_ethertype_fh0_ops;
	}
	else if (!strncmp(filename, "fh0:eth_src0", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_eth_src0_fh0_ops;
	}
	else if (!strncmp(filename, "fh0:eth_src1", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_eth_src1_dst1_fh0_ops;
	}
	else if (!strncmp(filename, "fh0:eth_dst0", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_eth0_dst0_fh0_ops;
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
	else if (!strncmp(filename, "fh1:vlan_ethertype", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_vlan_ethertype_fh1_ops;
	}
	else if (!strncmp(filename, "fh1:eth_src0", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_eth_src0_fh1_ops;
	}
	else if (!strncmp(filename, "fh1:eth_src1", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_eth_src1_dst1_fh1_ops;
	}
	else if (!strncmp(filename, "fh1:eth_dst0", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_eth0_dst0_fh1_ops;
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
	else if (!strncmp(filename, "fh2:vlan_ethertype", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_vlan_ethertype_fh2_ops;
	}
	else if (!strncmp(filename, "fh2:eth_src0", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_eth_src0_fh2_ops;
	}
	else if (!strncmp(filename, "fh2:eth_src1", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_eth_src1_dst1_fh2_ops;
	}
	else if (!strncmp(filename, "fh2:eth_dst0", XBAR_WRAPPER_SIZE))
	{
		return &qudp_egress_eth0_dst0_fh2_ops;
	}


	else if (!strncmp(filename, "fh0:config", XBAR_WRAPPER_SIZE))
	{
		return &qudp_ingress_global_cfg_fh0;
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
	else if (!strncmp(filename, "fh1:config", XBAR_WRAPPER_SIZE))
	{
		return &qudp_ingress_global_cfg_fh1;
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

	else if (!strncmp(filename, "fh2:config", XBAR_WRAPPER_SIZE))
	{
		return &qudp_ingress_global_cfg_fh2;
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

	else{
		pr_err("Invalid file name, no entry available\n");
		return &dummy;
	}
	return NULL;
}


int32_t setup_debugfs_directory()
{
        char token[64];
	char my_delm;
        int index;
	int len= 0;
	struct file_operations *fileops = NULL;
	struct dentry *kobj_root;
	int curr_index = 0;

        remove_whitespaces(input_string);
	//pr_err("%s\n", input_string);
	my_delm = parser(input_string, "{},",token, &index);
        while (my_delm != 0){
		len= strlen(token);
		//pr_err("token: %s\n",token);

                if(token[0] == '{' && len >2)
                {
			remove_firstchar(token);
			//pr_err("token after removal: %s\n",token);

			if(curr_index == 0)
			{
				list_dv[curr_index] = debugfs_create_dir(token,NULL);
				//pr_err("Curr_index = %u, inserting %s, parent was null", curr_index, token);
				//pr_err("Incremmting cur_index +1\n");
				curr_index++;
			}else{
				kobj_root = debugfs_create_dir(token, list_dv[curr_index -1]);
				list_dv[curr_index] = kobj_root;
				//pr_err("Curr_index = %u, inserting %s, parent was %u", curr_index, token, curr_index-1);
				//pr_err("Incremmting cur_index +1\n");
				curr_index++;
			}
                }else if( token[0] == '}'  && len > 2)
                {
			remove_firstchar(token);
			//pr_err("token after removal: %s\n",token);
			//pr_err("Curr_index = %u, inserting %s, parent was %u", curr_index, token, curr_index-1);
			//pr_err("Decresing cur_index -1\n");
				curr_index--;
			//pr_err("inserting at Curr_index = %u, inserting %s, parent was %u", curr_index, token, curr_index-1);
			kobj_root = debugfs_create_dir(token, list_dv[curr_index -1 ]);
			list_dv[curr_index] = kobj_root;
				//pr_err("Incremmting cur_index +1\n");
				curr_index++;

                }else if(token[0] == ',' && len > 2){
			// we want to create file
			remove_firstchar(token);
			//pr_err("token after removal: %s\n",token);
			// file_name_to_callback , this will return a function pointer
			fileops = file_name_to_wrapper(token);
			get_file_name(token);
			//pr_err("token after get_file_name: %s\n",token);
			if(!debugfs_create_file(token, 0444, list_dv[curr_index - 1], 0, fileops)){
				//pr_err("Unable to create the debugfs file...\n");
			}
			//pr_err("Curr_index = %u, inserting %s, parent was %u", curr_index, token, curr_index -1 );

		}else if(token[0] == '}' && len < 2){
			//pr_err("Curr_index = %u, inserting Nothing, parent was %u", curr_index,  curr_index+1);
			//pr_err("Decresing cur_index -1\n");
			curr_index-- ;

		}
		my_delm = parser(input_string, "{},",token, &index);
        }
        return 0;

}
/*****************************************************************************/
