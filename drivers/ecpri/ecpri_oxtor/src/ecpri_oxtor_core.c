/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/ioctl.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include "ecpri_oxtor_core.h"
#include "ecpri_oxtor_ioctl.h"
#include "ecpri_oxtor_hal.h"
#include "ecpri_oxtor_tx.h"
#include "ecpri_oxtor_rx.h"
#include "ecpri_oxtor_cache.h"
#include "ecpri_oxtor_debugfs.h"

#define ECPRISS_CORE_IPC_LOG_PAGES   50
#define DEVICE_NAME "ecpri_oxtor"
#define MOD_INC_USE_COUNT
#define MOD_DEC_USE_COUNT


extern  ecpri_oxtor_tx_ring_cntxt_s ecpri_oxtor_tx_ring_cnxt;
extern ecpri_oxtor_rx_ring_cntxt_s ecpri_oxtor_rx_ring_cnxt;
extern ecpriss_oxtor_hal_context_s ecpriss_oxtor_hal_ctx;

ecpri_oxtor_cache g_cache;
ecpri_oxtor_stats_s stats_data;

ecpri_oxtor_core_cntxt_s     ecpri_oxtor_core_cntxt;
ecpri_oxtor_irq_wq_params_s  irq_wq_s;
char* ecpri_oxtor_interface_name = DEVICE_NAME;

static int ecpri_oxtor_core_open(struct inode *inode, struct file *filp);
static int ecpri_oxtor_core_release(struct inode *inode, struct file *filp);
static int ecpri_oxtor_core_remove(struct platform_device *pdev);
static int ecpri_oxtor_core_suspend(struct device *dev);
static int ecpri_oxtor_core_resume(struct device *dev);
static int ecpri_oxtor_core_init(void);
static int ecpri_oxtor_init(struct platform_device *pdev);
static long ecpri_oxtor_core_ioctl_hdlr(struct file *filp, unsigned int cmd,
		unsigned long arg);
static int ecpri_oxtor_core_probe(struct platform_device *pdev);
static int ecpri_oxtor_core_ioctl_init(void);

static void ecpri_oxtor_free_cmd(ecpri_oxtor_core_cfg_s *oxtor_cmd)
{
	if(!oxtor_cmd){
		pr_err("Null Pointer \n");
		return;
	}
	if(oxtor_cmd->tx_cmd_cfg){
		kfree(oxtor_cmd->tx_cmd_cfg);
		oxtor_cmd->tx_cmd_cfg = NULL;
	}
	return;
}
static void ecpri_oxtor_init_cache(ecpri_oxtor_cache *oxtor_cache)
{
	int i = 0;

	if(!oxtor_cache){
		pr_err("Null Pointer oxtor_cache \n");
		return;
	}
	memset(oxtor_cache, 0,sizeof(ecpri_oxtor_cache));
	/* Holds the current index of ring buffer use % by MAX_CACHE_SIZE */
	oxtor_cache->cache_index = 0;

	for(i=0; i<MAX_CACHE_SIZE; i++){
		/* index -1 means never used before */
		oxtor_cache->cache_info[i].index = -1;
		oxtor_cache->cache_info[i].data.ioctl_cmd_state =
			ECPRI_OXTOR_IOCTL_DEFAULT_S;
	}
	pr_info("GLobal Cache init phase done\n");
	return;
}

static int ecpri_oxtor_core_open(struct inode *inode, struct file *filp)
{
	/*
	 * Only one app can open it at a time
	 */
	if (ecpri_oxtor_core_cntxt.device_info.ref)
		return -EBUSY;
	ecpri_oxtor_core_cntxt.device_info.ref++;
	MOD_INC_USE_COUNT;

	pr_info("ecpri_oxtor device file open\n");

	return 0;
}

static int ecpri_oxtor_core_release(struct inode *inode, struct file *filp)
{
	pr_info("ecpri_oxtor device file closed\n");

	ecpri_oxtor_core_cntxt.device_info.ref--;

	return 0;
}

static int ecpri_oxtor_core_remove(struct platform_device *pdev)
{
	return 0;
}

static int ecpri_oxtor_core_suspend(struct device *dev)
{
	return 0;
}

static int ecpri_oxtor_core_resume(struct device *dev)
{
	return 0;
}

struct file_operations fops = {
	.owner          = THIS_MODULE,
	.read           = NULL,
	.write          = NULL,
	.open           = ecpri_oxtor_core_open,
	.unlocked_ioctl = ecpri_oxtor_core_ioctl_hdlr,
	.release        = ecpri_oxtor_core_release
};

static int ecpri_oxtor_core_init(void)
{

	ecpri_oxtor_core_cntxt_s  *core_cntxt_ptr = &ecpri_oxtor_core_cntxt;

	pr_info(" Executing oxtor core init \n");

	/* Initialize ecpriss_oxtor_hal_ctx */

	ecpriss_oxtor_hal_ctx_init();


	core_cntxt_ptr->xu_id = ECPRI_OXTOR_XU_ID_DEFAULT;

	core_cntxt_ptr->tx_ring_cntxt_ptr = &ecpri_oxtor_tx_ring_cnxt;
	core_cntxt_ptr->rx_ring_cntxt_ptr = &ecpri_oxtor_rx_ring_cnxt;

	core_cntxt_ptr->init = true;

	return 0;
}




static int ecpri_oxtor_init(struct platform_device *pdev)
{
	int ret = 0;
	memset(&ecpri_oxtor_core_cntxt,0,sizeof(ecpri_oxtor_core_cntxt_s));

	do {

		ret = ecpri_oxtor_core_ioctl_init();
		if(ret < 0) {
			pr_err("Ioctl init failed\n");
			break;
		}

		ret = ecpri_oxtor_core_init();
		if(ret < 0) {
			pr_err("Work queue init failed\n");
			break;
		}
		/*
		   ret = ecpri_oxtor_workq_init();
		   if(ret < 0) {
		   pr_err("Work queue init failed\n");
		   break;
		   }
		   */
		ret = ecpri_oxtor_tx_init();
		if(ret < 0) {
			pr_err("Tx Init failed\n");
			break;
		}
		else{
			pr_err("ecpri_oxtor_tx_init()\n");
		}

		ret = ecpri_oxtor_rx_init();
		if(ret < 0) {
			pr_err("Tx Init failed\n");
			break;
		}
		else{
			pr_err("ecpri_oxtor_rx_init()\n");
		}

		/* Init Global cache */
		ecpri_oxtor_init_cache(&g_cache);
	} while (0);

	return ret;
}

/* On successful validation it returns zero */
static int ecpri_oxtor_core_validate_config(ecpri_oxtor_core_cfg_s *var)
{
	u8 i = 0;

	if(!var){
		pr_err("Null Pointer var \n");
		return -1;
	}
	if (var->test_mode < ECPRI_OXTOR_TEST_MODE_TX_ONLY ||
			var->test_mode > ECPRI_OXTOR_TEST_MODE_MAX){
		pr_err("Ivalid Data var->test_mode = %d\n", var->test_mode);
		return -1;
	}
	if (var->num_cmds < 0 || var->num_cmds > U32_MAX){
		pr_err("Ivalid Data var->num_cmds = %d\n", var->num_cmds);
		return -1;
	}
	if (var->tx_cmd_cfg == NULL){
		pr_err("Null Pointer var->tx_cmd_cfg \n");
		return -1;
	}

	for (i = 0; i < var->num_cmds; i++){

		if (var->tx_cmd_cfg[i].pkt_cfg.xu_id < 0  ||
				var->tx_cmd_cfg[i].pkt_cfg.xu_id > U32_MAX){
			pr_err("Invalid var->tx_cmd_cfg[%d].pkt_cfg.xu_id ="
					"%d\n",i,
					var->tx_cmd_cfg[i].pkt_cfg.xu_id);
			return -1;
		}
		if (var->tx_cmd_cfg[i].pkt_cfg.pkt_len < 0  ||
				var->tx_cmd_cfg[i].pkt_cfg.pkt_len > U16_MAX){
			pr_err("Invalid var->tx_cmd_cfg[%d].pkt_cfg.pkt_len ="
					"%d\n",i,
					var->tx_cmd_cfg[i].pkt_cfg.pkt_len);
			return -1;
		}
		if (var->tx_cmd_cfg[i].pkt_cfg.inter_pkt_delay < 0  ||
				var->tx_cmd_cfg[i].pkt_cfg.inter_pkt_delay >
				U16_MAX){
			pr_err("Invalid"
				"var->tx_cmd_cfg[%d].pkt_cfg.inter_pkt_delay ="
				"%d\n",i,
				var->tx_cmd_cfg[i].pkt_cfg.inter_pkt_delay);
			return -1;
		}
		if (var->tx_cmd_cfg[i].pkt_cfg.init_data < 0  ||
				var->tx_cmd_cfg[i].pkt_cfg.inter_pkt_delay >
				U32_MAX){
			pr_err("Invalid var->tx_cmd_cfg[%d].pkt_cfg.init_data ="
					"%d\n",i,
					var->tx_cmd_cfg[i].pkt_cfg.init_data);
			return -1;
		}
		if (var->tx_cmd_cfg[i].pkt_cfg.ecpri_msg_type < 0  ||
				var->tx_cmd_cfg[i].pkt_cfg.ecpri_msg_type >
				U8_MAX){
			pr_err("Invalid"
				"var->tx_cmd_cfg[%d].pkt_cfg.ecpri_msg_type ="
				"%d\n",i,
				var->tx_cmd_cfg[i].pkt_cfg.ecpri_msg_type);
			return -1;
		}
		if (var->tx_cmd_cfg[i].pkt_cfg.ring_wrap_en < 0  ||
				var->tx_cmd_cfg[i].pkt_cfg.ring_wrap_en >
				U8_MAX){
			pr_err("Invali var->tx_cmd_cfg[%d].pkt_cfg.ring_wrap_en"
				"= %d\n",
				var->tx_cmd_cfg[i].pkt_cfg.ring_wrap_en);
			return -1;
		}
		if (var->tx_cmd_cfg[i].flow_cfg.pcid < 0  ||
				var->tx_cmd_cfg[i].flow_cfg.pcid > U16_MAX){
			pr_err("Invalid var->tx_cmd_cfg[%d].flow_cfg.pcid ="
					"%d\n",i,
					var->tx_cmd_cfg[i].flow_cfg.pcid);
			return -1;
		}
		if (var->tx_cmd_cfg[i].flow_cfg.port_type <
				ECPRI_OXTOR_CORE_LINK_ID_PORT_TYPE_FH  ||
				var->tx_cmd_cfg[i].flow_cfg.port_type >
				ECPRI_OXTOR_CORE_LINK_ID_PORT_TYPE_OC){
			pr_err("Invalid var->tx_cmd_cfg[%d].flow_cfg.port_type="
					"%d\n",i,
					var->tx_cmd_cfg[i].flow_cfg.pcid);
			return -1;
		}
		if (var->tx_cmd_cfg[i].flow_cfg.port_type <
				ECPRI_OXTOR_CORE_LINK_ID_PORT_0  ||
				var->tx_cmd_cfg[i].flow_cfg.port_type >
				ECPRI_OXTOR_CORE_LINK_ID_PORT_2){
			pr_err("Invalid var->tx_cmd_cfg[%d].flow_cfg.port_idx ="
					"%d\n",i,
					var->tx_cmd_cfg[i].flow_cfg.port_idx);
			return -1;
		}
		if (var->tx_cmd_cfg[i].flow_cfg.link_idx <
				ECPRI_OXTOR_CORE_LINK_ID_INDEX_0  ||
				var->tx_cmd_cfg[i].flow_cfg.link_idx >
				ECPRI_OXTOR_CORE_LINK_ID_INDEX_3){
			pr_err("Invalid var->tx_cmd_cfg[%d].flow_cfg.link_idx ="
					"%d\n",i,
					var->tx_cmd_cfg[i].flow_cfg.link_idx);
			return -1;
		}
		if (var->tx_cmd_cfg[i].flow_cfg.tx_oc_link_id < 0  ||
				var->tx_cmd_cfg[i].flow_cfg.tx_oc_link_id >
				U32_MAX){
			pr_err("Invalid"
				"var->tx_cmd_cfg[%d].flow_cfg.tx_oc_link_id ="
				"%d\n",i,
				var->tx_cmd_cfg[i].flow_cfg.tx_oc_link_id);
			return -1;
		}
		if (var->tx_cmd_cfg[i].pkt_cfg.xu_id < 0  ||
				var->tx_cmd_cfg[i].pkt_cfg.xu_id > U32_MAX){
			pr_err("Invalid"
				"var->tx_cmd_cfg[%d].flow_cfg.rx_oc_link_id ="
				"%d\n",i,
				var->tx_cmd_cfg[i].flow_cfg.rx_oc_link_id);
			return -1;
		}
	}

	if (var->rx_cfg.dummy < 0  || var->rx_cfg.dummy > U32_MAX){
		pr_err("Invalid var->rx_cfg.dummy = %d\n",var->rx_cfg.dummy);
		return -1;
	}
	return 0;
}
static long ecpri_oxtor_core_ioctl_hdlr(struct file *filp, unsigned int cmd,
		unsigned long arg)
{
	ecpri_oxtor_core_cfg_s var;
	ecpri_oxtor_start_cfg_s data;
	u32 reset_ring_id;
	ecpri_oxtor_core_tx_cmd_cfg_s *bck;
	ecpri_oxtor_tx_ring_config_s wrap_cfg;
	u8 wrap_en[4];
	u8 i;
	u8 arr_idx = g_cache.cache_index % MAX_CACHE_SIZE;

	static ecpri_oxtor_core_linkid_port_idx_e  port_idx;
	memset(wrap_en,0,sizeof(wrap_en));
	memset(&var,0,sizeof(ecpri_oxtor_core_cfg_s));

	switch (cmd) {

		case ECPRI_OXTOR_IOCTL_CONFIG : /*ECPRI_OXTOR_IOCTL_CONFIG:*/
			printk(KERN_INFO "<%s> ioctl:ECPRI_OXTOR_IOCTL_CONFIG\n"
					,DEVICE_NAME);
			if(copy_from_user(&var, (ecpri_oxtor_core_cfg_s *)arg,
						sizeof(var))){
				pr_err("copy_from_user_failed in ioctls\n");
				return 0;
			}
			/* We can not pass more than 30 commands */
			if(var.num_cmds < 1 || var.num_cmds >30*4){
				pr_err("Invalid Number of commands %d \n",
						var.num_cmds);
				return 0;
			}
			bck = var.tx_cmd_cfg;
			var.tx_cmd_cfg = kmalloc(var.num_cmds *
					sizeof(ecpri_oxtor_core_tx_cmd_cfg_s),
					GFP_KERNEL);
			if(!var.tx_cmd_cfg){
				pr_err("kmalloc failed \n");
				return 0;
			}
			if(copy_from_user(var.tx_cmd_cfg, bck, var.num_cmds *
					sizeof(ecpri_oxtor_core_tx_cmd_cfg_s))){
				pr_err("copy_from_user_failed in ioctls\n");
				return 0;
			}

			for (i = 0; i < var.num_cmds; i++){
				pr_info(
				"var.test_mode = %d \n"
				"var.num_cmds = %d \n\n"
				"var.tx_cmd_cfg[%d].pkt_cfg \n\t"
				"var.tx_cmd_cfg[%d].pkt_cfg.xu_id = %d \n\t"
				"var.tx_cmd_cfg[%d].pkt_cfg.pkt_len = %d \n\t"
				"var.tx_cmd_cfg[%d].pkt_cfg.inter_pkt_delay= %d"
				"\n\t"
				"var.tx_cmd_cfg[%d].pkt_cfg.init_data = %d \n\t"
				"var.tx_cmd_cfg[%d].pkt_cfg.ecpri_msg_type = %d"
				"\n\t"
				"var.tx_cmd_cfg[%d].pkt_cfg.ring_wrap_en"
				"= %d \n\n"
				"var.tx_cmd_cfg[%d].flow_cfg \n\t"
				"var.tx_cmd_cfg[%d].flow_cfg.pcid = %d \n\t"
				"var.tx_cmd_cfg[%d].flow_cfg.port_type = %d\n\t"
				"var.tx_cmd_cfg[%d].flow_cfg.port_idx = %d \n\t"
				"var.tx_cmd_cfg[%d].flow_cfg.link_idx = %d \n\t"
				"var.tx_cmd_cfg[%d].flow_cfg.tx_oc_link_id = %d"
				"\n\t"
				"var.tx_cmd_cfg[%d].flow_cfg.rx_oc_link_id = %d"
				"\n"
				"var.rx_cfg \n\t"
				"var.rx_cfg.dummy = %d \n\n"
				,var.test_mode
				,var.num_cmds
				,i
				,i,var.tx_cmd_cfg[i].pkt_cfg.xu_id
				,i,var.tx_cmd_cfg[i].pkt_cfg.pkt_len
				,i,var.tx_cmd_cfg[i].pkt_cfg.inter_pkt_delay
				,i,var.tx_cmd_cfg[i].pkt_cfg.init_data
				,i,var.tx_cmd_cfg[i].pkt_cfg.ecpri_msg_type
				,i,var.tx_cmd_cfg[i].pkt_cfg.ring_wrap_en
				,i
				,i,var.tx_cmd_cfg[i].flow_cfg.pcid
				,i,var.tx_cmd_cfg[i].flow_cfg.port_type
				,i,var.tx_cmd_cfg[i].flow_cfg.port_idx
				,i,var.tx_cmd_cfg[i].flow_cfg.link_idx
				,i,var.tx_cmd_cfg[i].flow_cfg.tx_oc_link_id
				,i,var.tx_cmd_cfg[i].flow_cfg.rx_oc_link_id
				,var.rx_cfg.dummy);

				/*
				 * Validate the Cmd Data
				 */
				if (ecpri_oxtor_core_validate_config(&var)){
					pr_err(
					"Data we got i IOCTL is invalid \n");
					/*
					 * not sure about ioctl codes, need to
					 * study and return error accordingly
					 */
					return -1;
				}
				/*
				 * Queue cmds (IOCTL_CFG)
				 */
				if(0 != ecpri_oxtor_tx_ring_queue_cmd (
				var.tx_cmd_cfg[i] ,
				var.tx_cmd_cfg[i].flow_cfg.tx_oc_link_id)){
					pr_err("Commit failed \n");
					return -1;
				}
				if(!
				wrap_en[
				var.tx_cmd_cfg[i].flow_cfg.tx_oc_link_id
				]
				&& var.tx_cmd_cfg[i].pkt_cfg.ring_wrap_en){
					wrap_en[
					var.tx_cmd_cfg[i].flow_cfg.tx_oc_link_id
					] = 1;
				}

			}
			/*
			 * If Wrap mode is enabled for any of the ring id
			 * set the flag
			 */
			for(i=0;i<4;i++){
				if(! wrap_en[i]){
					continue;
				}
				wrap_cfg.run_mode =
					ECPRI_OXTOR_RING_MODE_WRAPPING;
				ecpri_oxtor_tx_ctl_reg_cfg(&wrap_cfg, i);
			}

			port_idx = var.tx_cmd_cfg[i].flow_cfg.port_idx;

			/* Global cache update */

			if(g_cache.cache_info[arr_idx].index != -1){
				/* Already data present */
				pr_info("Already data available, Free it \n");
				ecpri_oxtor_free_cmd(
				&g_cache.cache_info[arr_idx].data.ioctl_cmds);
				memset(
				&g_cache.cache_info[arr_idx].data, 0 ,
				sizeof(cache_stats));

			}
			g_cache.cache_info[arr_idx].index = g_cache.cache_index;
			g_cache.cache_info[arr_idx].data.ioctl_cmd_state =
				ECPRI_OXTOR_IOCTL_CONFIG_S;
			memcpy(&g_cache.cache_info[arr_idx].data.ioctl_cmds,
					&var, sizeof(ecpri_oxtor_core_cfg_s));
			break;
		case ECPRI_OXTOR_IOCTL_START :/*Commit commnads to TX packets*/
			if(copy_from_user(&data,(ecpri_oxtor_start_cfg_s *)arg,
						sizeof(data))){
				pr_err("copy_from_user_failed in ioctls\n");
				return 0;
			}
			pr_info("data.start_test_mode = %d\n"
					"data.num_of_cmds = %d\n"
					"data.tx_oc_link_id = %d\n",
					data.start_test_mode,
					data.num_cmds,data.tx_oc_link_id);
			ecpri_oxtor_tx_ring_commit(data.num_cmds,
					data.tx_oc_link_id);

			/* Global cache update */
			g_cache.cache_info[arr_idx].data.ioctl_cmd_state =
				ECPRI_OXTOR_IOCTL_START_S;
			g_cache.cache_info[arr_idx].data.num_commited_cmds[
				data.tx_oc_link_id
				] = data.num_cmds;
			break;

		case ECPRI_OXTOR_IOCTL_RESET : /* Reset Tx Rings */
			if(copy_from_user(&reset_ring_id,(u32 *)arg,
						sizeof(reset_ring_id))){
				pr_err("copy_from_user_failed in ioctls\n");
				return 0;
			}
			/*
			 * If Wrap mode is enabled for any of the ring id
			 * set the flag
			 */
			pr_info("Resetting the oxtor and wrap mode\n");
			wrap_cfg.run_mode = ECPRI_OXTOR_RING_MODE_ONE_TIME;
			ecpri_oxtor_tx_ctl_reg_cfg(&wrap_cfg, reset_ring_id);

			/*
			 * THis code will go inside new ioctl of get status
			 */
			/* get status and stats before resetting */
			ecpri_oxtor_tx_get_status(reset_ring_id);
			stats_data.tx_count[reset_ring_id] =
				ecpri_oxtor_tx_get_stats(reset_ring_id);
			pr_info("TX: ring_id[ %d ], TX: stats [ %d ]\n",
					reset_ring_id,
					stats_data.tx_count[reset_ring_id]);
			stats_data.rx_count[reset_ring_id] =
				ecpri_oxtor_rx_get_stats(reset_ring_id);
			pr_info("RX: ring_id[ %d ], RX: stats [ %d ]\n",
					reset_ring_id,
					stats_data.rx_count[reset_ring_id]);

			ecpri_oxtor_tx_ring_reset(reset_ring_id);
			ecpri_oxtor_rx_ring_reset(reset_ring_id);

			/* Global cache update */
			g_cache.cache_info[arr_idx].data.ioctl_cmd_state =
				ECPRI_OXTOR_IOCTL_RESET_S;

			break;

		/* This should be called just after RESET command */
		case ECPRI_OXTOR_IOCTL_GET_STATS :
			if(copy_to_user((ecpri_oxtor_stats_s *)arg, &stats_data,
						sizeof(stats_data))){
				pr_err("copy_to_user_failed in ioctls\n");
				return 0;
			}
			pr_info("Stats are send to application\n");
			pr_info("Ringid   TX_count   RX_count\n");
			for(i = 0; i < 4; i++){
				pr_info("0x0%x 0x0%x 0x0%x\n",i,
						stats_data.tx_count[i],
						stats_data.rx_count[i]);
			}
			pr_info("\nEND OF TABLE\n");

			/* Global cache update */
			g_cache.cache_info[arr_idx].data.ioctl_cmd_state =
				ECPRI_OXTOR_IOCTL_GET_STATS_S;
			memcpy(&g_cache.cache_info[arr_idx].data.tx_rx_stats,
					&stats_data,
					sizeof(ecpri_oxtor_stats_s));
			memcpy(&g_cache.cache_info[arr_idx].data.core_contx,
					&ecpri_oxtor_core_cntxt,
					sizeof(ecpri_oxtor_core_cntxt_s));
			g_cache.cache_index++;
			break;

		default:
			break;
	}

	return 0;
}

static int ecpri_oxtor_core_probe(struct platform_device *pdev)
{
	pr_info("ecpri_oxtor_core_probe()\n");
	ecpri_oxtor_init(pdev);
	pr_info("ecpri_oxtor_core_probe(): Completed\n");
	setup_debugfs_directory();
	return 0;
}

static const struct of_device_id ecpri_oxtor_core_dt_match[] = {
	{ .compatible = "qcom,ecpri_oxtor" },
	{ },
};

MODULE_DEVICE_TABLE(of, ecpri_oxtor_core_dt_match);

static const struct dev_pm_ops ecpri_oxtor_core_pm_ops = {
	.suspend = ecpri_oxtor_core_suspend,
	.resume = ecpri_oxtor_core_resume,
};

static struct platform_driver ecpri_oxtor_core_driver = {
	.driver = {
		.name = "ecpri_oxtor",
		.owner = THIS_MODULE,
		.of_match_table = ecpri_oxtor_core_dt_match,
		.pm = &ecpri_oxtor_core_pm_ops,
	},
	.probe = ecpri_oxtor_core_probe,
	.remove = ecpri_oxtor_core_remove,
};


static int __init ecpri_oxtor_core_module_init(void)
{
	pr_info("ecpri_oxtor_core_module_init()\n");
	return platform_driver_register(&ecpri_oxtor_core_driver);
}

static int ecpri_oxtor_core_ioctl_init(void)
{
	int err = 0;
	ecpri_oxtor_device_info_s *dev_info_ptr = NULL;

	dev_info_ptr  = &ecpri_oxtor_core_cntxt.device_info;

	pr_info("Executing ecpri_oxtor_core_ioctl_init\n");

	/*Allocate Major number*/
	if((alloc_chrdev_region(&(dev_info_ptr->ecpri_oxtor_dev), 0, 1,
					"ecpri_oxtor")) <0){
		pr_err("Cannot allocate major number\n");
		return -1;
	}

	dev_info_ptr->major_num = MAJOR(dev_info_ptr->ecpri_oxtor_dev);
	dev_info_ptr->minor_num = MINOR(dev_info_ptr->ecpri_oxtor_dev);

	pr_info("Major = %d Minor = %d \n",dev_info_ptr->major_num,
			dev_info_ptr->minor_num);

	/*Create cdev structure*/
	cdev_init(&(dev_info_ptr->ecpri_oxtor_cdev),&fops);

	/*Updating the Owner*/
	dev_info_ptr->ecpri_oxtor_cdev.owner = THIS_MODULE;

	/*Adding character device to the system*/
	if((cdev_add(&(dev_info_ptr->ecpri_oxtor_cdev),
					dev_info_ptr->ecpri_oxtor_dev,1)) < 0){
		pr_err("Cannot add the device to the system\n");
		goto r_unreg;
	}
	/*Creating struct class*/
	dev_info_ptr->dev_class = class_create(THIS_MODULE,"ecpri_oxtor");
	if(IS_ERR(dev_info_ptr->dev_class)){
		err = PTR_ERR(dev_info_ptr->dev_class);
		goto r_dev;
	}

	/*Creating device*/
	dev_info_ptr->dev_number =
		device_create(dev_info_ptr->dev_class,NULL,
				dev_info_ptr->ecpri_oxtor_dev,NULL,
				"ecpri_oxtor");
	if(IS_ERR(dev_info_ptr->dev_number)){
		err = PTR_ERR(dev_info_ptr->dev_number);
		goto r_class;
	}

	return 0;

r_class:
	class_destroy(dev_info_ptr->dev_class);
r_dev:
	cdev_del(&(dev_info_ptr->ecpri_oxtor_cdev));
r_unreg:
	unregister_chrdev_region(dev_info_ptr->ecpri_oxtor_dev, 1);
	platform_driver_unregister(&ecpri_oxtor_core_driver);

	return -1;
}

static void __exit ecpri_oxtor_core_module_exit(void)
{
	ecpri_oxtor_device_info_s *dev_info_ptr = NULL;

	dev_info_ptr  = &ecpri_oxtor_core_cntxt.device_info;

	pr_info("ecpri oxtor driver exit!\n");

	device_destroy(dev_info_ptr->dev_class,dev_info_ptr->ecpri_oxtor_dev);
	class_destroy(dev_info_ptr->dev_class);
	cdev_del(&(dev_info_ptr->ecpri_oxtor_cdev));
	/*Unregister devce */
	unregister_chrdev_region(dev_info_ptr->ecpri_oxtor_dev, 1);
	platform_driver_unregister(&ecpri_oxtor_core_driver);
}


MODULE_LICENSE("GPL");
module_init(ecpri_oxtor_core_module_init);
module_exit(ecpri_oxtor_core_module_exit);
