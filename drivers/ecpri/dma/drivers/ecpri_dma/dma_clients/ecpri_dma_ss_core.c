/*
 * SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2025 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include "ecpri_dma_ss_core.h"
#include "ecpri_dma_dp.h"
#include "gsi.h"

#define ECPRI_DMA_SS_CORE_ORAN_BUDGET			(2)

struct pkt_eth_hdr dummy_ethhdr = {
	.src = {0x00, 0x53, 0x4e, 0x55, 0x4c, 0x30},
	.dst = {0x00, 0x53, 0x4e, 0x55, 0x4c, 0x54},
	.type = 0xfeae, //eCPRI
};

struct ecpri_dma_ss_core_pcap_header pcap_hdr = {
	.magic = ECPRI_DMA_SS_ORAN_LOG_PCAP_HDR_MAGIC,
	.version = ECPRI_DMA_SS_ORAN_LOG_PCAP_HDR_VER,
	.timezone = ECPRI_DMA_SS_ORAN_LOG_PCAP_HDR_TMZ,
	.timezone_accuracy = ECPRI_DMA_SS_ORAN_LOG_PCAP_HDR_TMZ_ACR,
	.snap_len = ECPRI_DMA_SS_ORAN_LOG_PCAP_HDR_SNP_LEN,
	.link_type = ECPRI_DMA_SS_ORAN_LOG_PCAP_HDR_LNK_TYPE,
};

struct ecpri_dma_ss_core_pcap_pkt_header pcap_pkt_hdr = { 0 };
ssize_t ecpri_dma_ecpri_ss_read_oran_log_egress(struct file* file,
	char __user* buf, size_t count, loff_t* offset);
ssize_t ecpri_dma_ecpri_ss_read_oran_log_ingress(struct file* file,
	char __user* buf, size_t count, loff_t* offset);

struct ecpri_dma_ss_core_context
	*ecpri_dma_ss_core_ctx = NULL;

/* Char DEV ops*/
struct file_operations ecpri_dma_oran_log_egress_fops = {
	.owner = THIS_MODULE,
	.read = ecpri_dma_ecpri_ss_read_oran_log_egress,
};

struct file_operations ecpri_dma_oran_log_ingress_fops = {
	.owner = THIS_MODULE,
	.read = ecpri_dma_ecpri_ss_read_oran_log_ingress,
};

static void ecpri_dma_ss_core_wq_notify_ready(struct work_struct* work)
{
	unsigned long flags;
	void* ready_user_data;
	ecpri_dma_ready_cb ready_cb;

	if (!ecpri_dma_ss_core_ctx)
	{
		DMAERR("Context isn't initialized\n");
		return;
	}

	spin_lock_irqsave(&ecpri_dma_ss_core_ctx->lock, flags);
	ready_cb = ecpri_dma_ss_core_ctx->ready_cb;
	ready_user_data = ecpri_dma_ss_core_ctx->ready_user_data;
	spin_unlock_irqrestore(&ecpri_dma_ss_core_ctx->lock, flags);

	ready_cb(ready_user_data);
}

static DECLARE_WORK(ecpri_dma_ss_core_notify_ready_work,
	ecpri_dma_ss_core_wq_notify_ready);

int ecpri_dma_ecpri_ss_register(
	struct ecpri_dma_ecpri_ss_register_params* ready_info,
	bool* is_dma_ready)
{
	int ret = 0;
	unsigned long flags;
	dev_t cdev[ECPRI_DMA_SS_ORAN_LOG_NUM_DEVICES];
	int devno[ECPRI_DMA_SS_ORAN_LOG_NUM_DEVICES];
	struct class* pClass[ECPRI_DMA_SS_ORAN_LOG_NUM_DEVICES];
	struct device* pDev[ECPRI_DMA_SS_ORAN_LOG_NUM_DEVICES];

	if (ecpri_dma_ss_core_ctx != NULL) {
		DMAERR("Context already initialized\n");
		return -EPERM;
	}

	/* Verify parameters validity */
	if (!ready_info
		|| !ready_info->notify_ready
		|| !ready_info->dma_event_notify
		|| !ready_info->log_msg
		|| !is_dma_ready) {
		DMAERR("Invalid paramteres\n");
		return -EINVAL;
	}

	/* Initialize context */
	ecpri_dma_ss_core_ctx = kzalloc(
		sizeof(*ecpri_dma_ss_core_ctx),
		GFP_KERNEL);
	if (!ecpri_dma_ss_core_ctx) {
		DMAERR("SS Core Client context"
			" is not initialized\n");
		return -ENOMEM;
	}

	spin_lock_init(&ecpri_dma_ss_core_ctx->lock);

	spin_lock_irqsave(&ecpri_dma_ss_core_ctx->lock, flags);

	ecpri_dma_ss_core_ctx->ready_cb =
		ready_info->notify_ready;
	ecpri_dma_ss_core_ctx->ready_user_data =
		ready_info->userdata_ready;

	ecpri_dma_ss_core_ctx->event_notify_cb =
		ready_info->dma_event_notify;
	ecpri_dma_ss_core_ctx->event_notify_user_data =
		ready_info->userdata_dma_event_notify;

	ecpri_dma_ss_core_ctx->log_msg_cb =
		ready_info->log_msg;
	ecpri_dma_ss_core_ctx->log_msg_user_data =
		ready_info->userdata_log_msg;

	ecpri_dma_ss_core_ctx->ecpri_hw_ver =
		ECPRI_DMA_GET_CTX_HW_VER();
	ecpri_dma_ss_core_ctx->hw_flavor =
		ECPRI_DMA_GET_HW_FLAVOR();

	spin_unlock_irqrestore(&ecpri_dma_ss_core_ctx->lock, flags);

	/* Initialize workqueue */
	ecpri_dma_ss_core_ctx->wq =
		create_singlethread_workqueue("ecpri_dma_ss_core_wq");
	if (!ecpri_dma_ss_core_ctx->wq) {
		DMAERR("Failed to create workqueue\n");
		ret = -EFAULT;
		goto fail_create_wq;
	}
	do {
		/* Init the ORAN logging CDEV */
		ret = alloc_chrdev_region(&cdev[ECPRI_DMA_SS_ORAN_LOG_EGRESS_DEV_ID],
			0, 1, "ecpri_oran_log_egress");
		if (ret) {
			DMAERR("Alloc of ORAN egress logging CDEV failed with error %d\n", ret);
			break;
		}

		ret = alloc_chrdev_region(&cdev[ECPRI_DMA_SS_ORAN_LOG_INGRESS_DEV_ID],
			0, 1, "ecpri_oran_log_ingress");
		if (ret) {
			DMAERR("Alloc of ORAN ingress logging CDEV failed with error %d\n", ret);
			break;
		}

		devno[ECPRI_DMA_SS_ORAN_LOG_EGRESS_DEV_ID] =
			MKDEV(MAJOR(cdev[ECPRI_DMA_SS_ORAN_LOG_EGRESS_DEV_ID]), 0);

		cdev_init(
			&ecpri_dma_ss_core_ctx->oran_log_cdev[ECPRI_DMA_SS_ORAN_LOG_EGRESS_DEV_ID],
			&ecpri_dma_oran_log_egress_fops);

		ecpri_dma_ss_core_ctx->
			oran_log_cdev[ECPRI_DMA_SS_ORAN_LOG_EGRESS_DEV_ID].owner = THIS_MODULE;
		ecpri_dma_ss_core_ctx->
			oran_log_cdev[ECPRI_DMA_SS_ORAN_LOG_EGRESS_DEV_ID].ops =
			&ecpri_dma_oran_log_egress_fops;

		ret = cdev_add(&ecpri_dma_ss_core_ctx->
			oran_log_cdev[ECPRI_DMA_SS_ORAN_LOG_EGRESS_DEV_ID],
			devno[ECPRI_DMA_SS_ORAN_LOG_EGRESS_DEV_ID], 1);
		if (ret) {
				DMAERR("Creation of ORAN egress logging CDEV failed with error %d\n", ret);
				break;
			}

		ecpri_dma_ss_core_ctx->
			oran_log_cdev_read_in_progress[ECPRI_DMA_SS_ORAN_LOG_EGRESS_DEV_ID] =
			false;
		ecpri_dma_ss_core_ctx->
			oran_log_cdev_read_state[ECPRI_DMA_SS_ORAN_LOG_EGRESS_DEV_ID] =
			false;

		devno[ECPRI_DMA_SS_ORAN_LOG_INGRESS_DEV_ID] =
			MKDEV(MAJOR(cdev[ECPRI_DMA_SS_ORAN_LOG_INGRESS_DEV_ID]), 0);

		cdev_init(
			&ecpri_dma_ss_core_ctx->oran_log_cdev[ECPRI_DMA_SS_ORAN_LOG_INGRESS_DEV_ID],
			&ecpri_dma_oran_log_ingress_fops);

		ecpri_dma_ss_core_ctx->
			oran_log_cdev[ECPRI_DMA_SS_ORAN_LOG_INGRESS_DEV_ID].owner = THIS_MODULE;
		ecpri_dma_ss_core_ctx->
			oran_log_cdev[ECPRI_DMA_SS_ORAN_LOG_INGRESS_DEV_ID].ops =
				&ecpri_dma_oran_log_ingress_fops;

		ret = cdev_add(&ecpri_dma_ss_core_ctx->
			oran_log_cdev[ECPRI_DMA_SS_ORAN_LOG_INGRESS_DEV_ID],
			devno[ECPRI_DMA_SS_ORAN_LOG_INGRESS_DEV_ID], 1);
		if (ret) {
			DMAERR("Creation of ORAN ingress logging CDEV failed with error %d\n", ret);
			break;
		}

		ecpri_dma_ss_core_ctx->
			oran_log_cdev_read_in_progress[ECPRI_DMA_SS_ORAN_LOG_INGRESS_DEV_ID] =
			false;
		ecpri_dma_ss_core_ctx->
			oran_log_cdev_read_state[ECPRI_DMA_SS_ORAN_LOG_INGRESS_DEV_ID] =
			false;

		/*	Create / sys / class / ecpri_oran_logger in preparation of
			creating / dev / ecpri_oran_logger */
		pClass[ECPRI_DMA_SS_ORAN_LOG_EGRESS_DEV_ID] =
			class_create(THIS_MODULE, "ecpri_oran_logger_egress");
		if (IS_ERR(pClass[ECPRI_DMA_SS_ORAN_LOG_EGRESS_DEV_ID])) {
			DMAERR("can't create egress class \n");
			unregister_chrdev_region(cdev[ECPRI_DMA_SS_ORAN_LOG_EGRESS_DEV_ID], 1);
			break;
		}

		pClass[ECPRI_DMA_SS_ORAN_LOG_INGRESS_DEV_ID] =
			class_create(THIS_MODULE, "ecpri_oran_logger_ingress");
		if (IS_ERR(pClass[ECPRI_DMA_SS_ORAN_LOG_INGRESS_DEV_ID])) {
			DMAERR("can't create ingress class \n");
			unregister_chrdev_region(cdev[ECPRI_DMA_SS_ORAN_LOG_INGRESS_DEV_ID], 1);
			break;
		}

		/* Create /dev/kmem for this char dev */
		if (IS_ERR(pDev[ECPRI_DMA_SS_ORAN_LOG_EGRESS_DEV_ID] =
			device_create(pClass[ECPRI_DMA_SS_ORAN_LOG_EGRESS_DEV_ID],
				NULL, cdev[ECPRI_DMA_SS_ORAN_LOG_EGRESS_DEV_ID], NULL,
			"ecpri_oran_logger_egress"))) {
			DMAERR("can't create device /dev/ecpri_oran_logger_egress\n");
			class_destroy(pClass[ECPRI_DMA_SS_ORAN_LOG_EGRESS_DEV_ID]);
			unregister_chrdev_region(cdev[ECPRI_DMA_SS_ORAN_LOG_EGRESS_DEV_ID], 1);
			break;
		}

		if (IS_ERR(pDev[ECPRI_DMA_SS_ORAN_LOG_INGRESS_DEV_ID] =
			device_create(pClass[ECPRI_DMA_SS_ORAN_LOG_INGRESS_DEV_ID],
				NULL, cdev[ECPRI_DMA_SS_ORAN_LOG_INGRESS_DEV_ID], NULL,
			"ecpri_oran_logger_ingress"))) {
			DMAERR("can't create device /dev/ecpri_oran_logger_ingress\n");
			class_destroy(pClass[ECPRI_DMA_SS_ORAN_LOG_INGRESS_DEV_ID]);
			unregister_chrdev_region(cdev[ECPRI_DMA_SS_ORAN_LOG_INGRESS_DEV_ID], 1);
			break;
		}

	} while(0);
	/* Check dma is ready */
	mutex_lock(&ecpri_dma_ctx->lock);
	*(is_dma_ready) = ecpri_dma_is_ready();
	mutex_unlock(&ecpri_dma_ctx->lock);

	if (*(is_dma_ready)) {
		queue_work(ecpri_dma_ss_core_ctx->wq,
			&ecpri_dma_ss_core_notify_ready_work);
	}
	else {
		ret = ecpri_dma_register_ready_cb(
			ecpri_dma_ss_core_ctx->ready_cb,
			ecpri_dma_ss_core_ctx->ready_user_data);
	}

	return 0;

fail_create_wq:
	kfree(ecpri_dma_ss_core_ctx);
	ecpri_dma_ss_core_ctx = NULL;
	return ret;
}

/**
 * ecpri_dma_ecpri_ss_deregister() - eCPRI SS driver remove registeration with
 * DMA driver
 */
void ecpri_dma_ecpri_ss_deregister()
{
	cdev_del(
		&ecpri_dma_ss_core_ctx->oran_log_cdev[ECPRI_DMA_SS_ORAN_LOG_EGRESS_DEV_ID]);
	cdev_del(
		&ecpri_dma_ss_core_ctx->oran_log_cdev[ECPRI_DMA_SS_ORAN_LOG_INGRESS_DEV_ID]);

	ecpri_dma_ss_core_ctx->ready_cb = NULL;
	ecpri_dma_ss_core_ctx->ready_user_data = NULL;

	ecpri_dma_ss_core_ctx->event_notify_cb = NULL;
	ecpri_dma_ss_core_ctx->event_notify_user_data = NULL;

	ecpri_dma_ss_core_ctx->log_msg_cb = NULL;
	ecpri_dma_ss_core_ctx->log_msg_user_data = NULL;

	destroy_workqueue(ecpri_dma_ss_core_ctx->wq);

	kfree(ecpri_dma_ss_core_ctx);
	ecpri_dma_ss_core_ctx = NULL;
}

/**
 * ecpri_dma_ecpri_ss_get_endp_mapping() - DMA driver to provide ENDP mapping
 * to eCPRI SS driver
 * @endp_map:   [out] Pointer to structure with ENDP mapping & port information
 *              according to eCPRI HW flavor
 *
 * Returns:	0 on success, negative on failure
 */
int ecpri_dma_ecpri_ss_get_endp_mapping(
	struct ecpri_dma_endp_mapping* endp_map)
{
	int ret = 0;

	if (ecpri_dma_ss_core_ctx == NULL) {
		DMAERR("Context is not initialized\n");
		return -EPERM;
	}

	ret = ecpri_dma_get_port_mapping(
		ecpri_dma_ss_core_ctx->ecpri_hw_ver,
		ecpri_dma_ss_core_ctx->hw_flavor, endp_map);
	if (ret != 0) {
		DMAERR("Cant get port mapping\n");
		return -EPERM;
	}

	return 0;
}

/**
 * ecpri_dma_ecpri_ss_nfapi_config() - eCPRI SS driver to provide nFAPI
 * configurations to DMA driver
 * @cfg:    [out] nFAPI configurations provided by nFAPI user app
 *
 * Returns:	0 on success, negative on failure
 */
int ecpri_dma_ecpri_ss_nfapi_config(struct ecpri_dma_ecpri_ss_nfapi_cfg cfg)
{
	return 0;
}

/**
 * ecpri_dma_ecpri_ss_query_stats() - eCPRI SS driver to query DMA driver
 * statistics
 * @stats:		  [out] Structure of the DMA statistics collected
 *
 * Returns:	0 on success, negative on failure
 */
int ecpri_dma_ecpri_ss_query_stats(struct ecpri_dma_stats* stats)
{
	return 0;
}

/**
 * ecpri_dma_ecpri_ss_notify_ssr() - TBD
 *
 * Returns:	0 on success, negative on failure
 */
int ecpri_dma_ecpri_ss_notify_ssr(void)
{
	return 0;
}

int ecpri_dma_ecpri_ss_start_oran_log(u32 mem_size, u32 pkt_size,
	enum ecpri_dma_oran_logging_direction dir)
{
	int ret = 0;
	u32 i = 0;
	struct ecpri_dma_ecpri_endp_alloc_params endp_params = { 0 };
	struct ecpri_dma_moderation_config mod_cfg = { 0 };
	struct device* pdev;
	struct ecpri_dma_pkt* pkts, **pkts_arr;
	struct ecpri_dma_mem_buffer* buffs, **buffs_arr;
	struct ecpri_dma_endp_context* endp_ctx;
	enum ecpri_dma_ss_oran_log_dev dev_id;
	u32 endp_id, gsi_id;

	pdev = ecpri_dma_get_smmu_ctx(ECPRI_DMA_SMMU_CB_ETH)->dev;

	if (dir == ECPRI_DMA_ORAN_LOGGING_DIRECTION_INGRESS) {
		if (ECPRI_DMA_GET_HW_FLAVOR() == ECPRI_HW_FLAVOR_RU) {
			endp_ctx = &ecpri_dma_ctx->endp_ctx[ECPRI_DMA_SS_ORAN_LOG_QRU_GSI_ID]
				[ECPRI_DMA_SS_ORAN_LOG_QRU_INGRESS_ENDP_ID];
			endp_id = ECPRI_DMA_SS_ORAN_LOG_QRU_INGRESS_ENDP_ID;
			gsi_id = ECPRI_DMA_SS_ORAN_LOG_QRU_GSI_ID;
		}
		else{
			endp_ctx = &ecpri_dma_ctx->endp_ctx[ECPRI_DMA_SS_ORAN_LOG_X100_GSI_ID]
				[ECPRI_DMA_SS_ORAN_LOG_X100_INGRESS_ENDP_ID];
			endp_id = ECPRI_DMA_SS_ORAN_LOG_X100_INGRESS_ENDP_ID;
			gsi_id = ECPRI_DMA_SS_ORAN_LOG_X100_GSI_ID;
		}
		dev_id = ECPRI_DMA_SS_ORAN_LOG_INGRESS_DEV_ID;
	}
	else {
		if (ECPRI_DMA_GET_HW_FLAVOR() == ECPRI_HW_FLAVOR_RU) {
			endp_ctx = &ecpri_dma_ctx->endp_ctx[ECPRI_DMA_SS_ORAN_LOG_QRU_GSI_ID]
				[ECPRI_DMA_SS_ORAN_LOG_QRU_EGRESS_ENDP_ID];
			endp_id = ECPRI_DMA_SS_ORAN_LOG_QRU_EGRESS_ENDP_ID;
			gsi_id = ECPRI_DMA_SS_ORAN_LOG_QRU_GSI_ID;
		}
		else {
			endp_ctx = &ecpri_dma_ctx->endp_ctx[ECPRI_DMA_SS_ORAN_LOG_X100_GSI_ID]
				[ECPRI_DMA_SS_ORAN_LOG_X100_EGRESS_ENDP_ID];
			endp_id = ECPRI_DMA_SS_ORAN_LOG_X100_EGRESS_ENDP_ID;
			gsi_id = ECPRI_DMA_SS_ORAN_LOG_X100_GSI_ID;
		}
		dev_id = ECPRI_DMA_SS_ORAN_LOG_EGRESS_DEV_ID;
	}

	ecpri_dma_ss_core_ctx->oran_log_cdev_read_state[dev_id] = false;

	if (!pdev) {
		DMAERR("Platform dev is not valid");
		return -EFAULT;
	}

	/* if ENDP is already allocated - reset and dealloc */
	if (endp_ctx && endp_ctx->valid) {

		ret = ecpri_dma_stop_endp(endp_ctx);
		if (ret != 0) {
			DMAERR("Unable to stop endp, endp_id: %d, gsi_id %d\n",
				endp_id, gsi_id);
			goto fail_dealloc_endp;
		}

		ret = ecpri_dma_reset_endp(endp_ctx);
		if (ret != 0) {
			DMAERR("Unable to reset endp, endp_id: %d, gsi_id %d\n",
				endp_id, gsi_id);
			goto fail_dealloc_endp;
		}

		ret = ecpri_dma_dealloc_endp(endp_ctx);
		if (ret != 0) {
			DMAERR("Unable to dealloc endp, endp_id: %d, gsi_id %d\n",
				endp_id, gsi_id);
			goto fail_dealloc_endp;
		}

		for(i=0; i<ecpri_dma_ss_core_ctx->num_of_pkts[dev_id]; i++){
			dma_free_coherent(pdev,ecpri_dma_ss_core_ctx->pkt_size[dev_id], ecpri_dma_ss_core_ctx->buffs[dev_id][i].virt_base,
					ecpri_dma_ss_core_ctx->buffs[dev_id][i].phys_base);
		}
		kfree(ecpri_dma_ss_core_ctx->buffs_arr[dev_id]);
		kfree(ecpri_dma_ss_core_ctx->pkts_arr[dev_id]);
		kfree(ecpri_dma_ss_core_ctx->buffs[dev_id]);
		kfree(ecpri_dma_ss_core_ctx->pkts[dev_id]);
	}

	/* Prepare memory for log ring */
	ecpri_dma_ss_core_ctx->pkt_size[dev_id] = DMA_BUFFER_SIZE;
	ecpri_dma_ss_core_ctx->num_of_pkts[dev_id] = mem_size / ecpri_dma_ss_core_ctx->pkt_size[dev_id];
	ecpri_dma_ss_core_ctx->oran_log_mem[dev_id].size = mem_size;

	pkts = kmalloc(sizeof(struct ecpri_dma_pkt) *
		ecpri_dma_ss_core_ctx->num_of_pkts[dev_id], GFP_KERNEL);
	if (!pkts) {
		DMAERR("malloc pkts failed\n");
		ret = -ENOMEM;
		goto ret;
	}

	buffs = kmalloc(sizeof(struct ecpri_dma_mem_buffer) *
		ecpri_dma_ss_core_ctx->num_of_pkts[dev_id], GFP_KERNEL);
	if (!buffs) {
		DMAERR("malloc buffs failed\n");
		ret = -ENOMEM;
		goto fail_alloc_buffs;
	}

	pkts_arr = kmalloc(sizeof(struct ecpri_dma_pkt*) *
		ecpri_dma_ss_core_ctx->num_of_pkts[dev_id], GFP_KERNEL);
	if (!pkts_arr) {
		DMAERR("malloc pkts_arr failed\n");
		ret = -ENOMEM;
		goto fail_alloc_pkts_arr;
	}

	buffs_arr = kmalloc(sizeof(struct ecpri_dma_mem_buffer*) *
		ecpri_dma_ss_core_ctx->num_of_pkts[dev_id], GFP_KERNEL);
	if (!buffs_arr) {
		DMAERR("malloc buffs_arr failed\n");
		ret = -ENOMEM;
		goto fail_alloc_buffs_arr;
	}

	ecpri_dma_ss_core_ctx->pkts[dev_id] = pkts;
	ecpri_dma_ss_core_ctx->pkts_arr[dev_id] = pkts_arr;
	ecpri_dma_ss_core_ctx->buffs[dev_id] = buffs;
	ecpri_dma_ss_core_ctx->buffs_arr[dev_id] = buffs_arr;

	endp_params.gsi_id = gsi_id;
	endp_params.endp_id = endp_id;
	endp_params.ring_length = ecpri_dma_ss_core_ctx->num_of_pkts[dev_id];
	endp_params.mod_cfg = &mod_cfg;
	endp_params.is_over_pcie = false;
	endp_params.notify_comp = NULL;
	endp_params.cb_to_use = ECPRI_DMA_SMMU_CB_ETH;
	endp_params.align_ring_mem = true;

	ret = ecpri_dma_alloc_endp(&endp_params);

	if (ret != 0) {
		DMAERR("Unable to allocate  endp_id: %d, gsi_id %d\n",
			endp_id, gsi_id);
		goto fail_alloc_endp;
	}

	ret = ecpri_dma_start_endp(endp_ctx);
	if (ret != 0) {
		DMAERR("Unable to start endp, endp_id: %d, gsi_id %d\n",
			endp_id, gsi_id);
		goto fail_start_endp;
	}

	/* queue credits to the endp */
	for (i = 0; i < ecpri_dma_ss_core_ctx->num_of_pkts[dev_id]; i++) {
		/* Prepare buffers and pkt wrappers for queueing*/
		buffs[i].size = ecpri_dma_ss_core_ctx->pkt_size[dev_id];
		buffs_arr[i] = &buffs[i];
		pkts[i].buffs = &buffs_arr[i];
		pkts[i].num_of_buffers = 1;
		pkts_arr[i] = &pkts[i];

		buffs[i].virt_base = dma_alloc_coherent(pdev,
			ecpri_dma_ss_core_ctx->pkt_size[dev_id]+sizeof(struct ecpri_hdr),
			&buffs[i].phys_base, GFP_KERNEL);

	        if (!buffs[i].virt_base) {
			DMAERR("dma_alloc_coherent failed, DMA buff size %d\n",
				ecpri_dma_ss_core_ctx->pkt_size[dev_id]+sizeof(struct ecpri_hdr));
			ret = -ENOMEM;
			goto fail_alloc_pkts;
		}

		ret = ecpri_dma_dp_transmit(endp_ctx, &pkts_arr[i], 1, false);
		if (ret != 0) {
			DMAERR("Unable to queue credits\n");
			goto fail_queue_credits;
		}
	}

	/* ring CH and EV DBs outside of the ring */
	ret = gsi_ring_ch_ring_db(endp_ctx->gsi_chan_hdl,
		endp_ctx->gsi_mem_info.chan_ring_base_addr +
		(ecpri_dma_ss_core_ctx->num_of_pkts[dev_id] * GSI_CHAN_RE_SIZE_16B));
	if (ret != 0) {
		DMAERR("Unable to ring CH DB\n");
		goto fail_queue_credits;
	}

	ret = gsi_ring_evt_ring_db(endp_ctx->gsi_evt_ring_hdl,
		endp_ctx->gsi_mem_info.evt_ring_base_addr +
		(ecpri_dma_ss_core_ctx->num_of_pkts[dev_id] * GSI_EVT_RING_RE_SIZE_16B));
	if (ret != 0) {
		DMAERR("Unable to ring EV DB\n");
		goto fail_queue_credits;
	}

	return 0;

fail_queue_credits:
        ecpri_dma_stop_endp(endp_ctx);
fail_alloc_pkts:
        for(i=0; i<ecpri_dma_ss_core_ctx->num_of_pkts[dev_id]; i++){
               dma_free_coherent(pdev,ecpri_dma_ss_core_ctx->pkt_size[dev_id], ecpri_dma_ss_core_ctx->buffs[dev_id][i].virt_base,
                               ecpri_dma_ss_core_ctx->buffs[dev_id][i].phys_base);
        }
fail_start_endp:
        ecpri_dma_dealloc_endp(endp_ctx);
fail_alloc_endp:
        kfree(buffs_arr);
fail_alloc_buffs_arr:
        kfree(pkts_arr);
fail_alloc_pkts_arr:
        kfree(buffs);
fail_alloc_buffs:
        kfree(pkts);
	goto ret;

fail_dealloc_endp:
        for(i=0; i<ecpri_dma_ss_core_ctx->num_of_pkts[dev_id]; i++){
               dma_free_coherent(pdev,ecpri_dma_ss_core_ctx->pkt_size[dev_id], ecpri_dma_ss_core_ctx->buffs[dev_id][i].virt_base,
                               ecpri_dma_ss_core_ctx->buffs[dev_id][i].phys_base);
        }
	kfree(ecpri_dma_ss_core_ctx->buffs_arr[dev_id]);
	kfree(ecpri_dma_ss_core_ctx->pkts_arr[dev_id]);
	kfree(ecpri_dma_ss_core_ctx->buffs[dev_id]);
	kfree(ecpri_dma_ss_core_ctx->pkts[dev_id]);
ret:
	return ret;
}

int ecpri_dma_ecpri_ss_stop_oran_log(
	enum ecpri_dma_oran_logging_direction dir)
{
	int ret = 0;
	struct ecpri_dma_endp_context* endp_ctx;
	u32 endp_id, gsi_id;
	enum ecpri_dma_ss_oran_log_dev dev_id;

	if (dir == ECPRI_DMA_ORAN_LOGGING_DIRECTION_INGRESS) {
		if (ECPRI_DMA_GET_HW_FLAVOR() == ECPRI_HW_FLAVOR_RU) {
			endp_ctx = &ecpri_dma_ctx->endp_ctx[ECPRI_DMA_SS_ORAN_LOG_QRU_GSI_ID]
				[ECPRI_DMA_SS_ORAN_LOG_QRU_INGRESS_ENDP_ID];
			endp_id = ECPRI_DMA_SS_ORAN_LOG_QRU_INGRESS_ENDP_ID;
			gsi_id = ECPRI_DMA_SS_ORAN_LOG_QRU_GSI_ID;
		}
		else {
			endp_ctx = &ecpri_dma_ctx->endp_ctx[ECPRI_DMA_SS_ORAN_LOG_X100_GSI_ID]
				[ECPRI_DMA_SS_ORAN_LOG_X100_INGRESS_ENDP_ID];
			endp_id = ECPRI_DMA_SS_ORAN_LOG_X100_INGRESS_ENDP_ID;
			gsi_id = ECPRI_DMA_SS_ORAN_LOG_X100_GSI_ID;
		}
		dev_id = ECPRI_DMA_SS_ORAN_LOG_INGRESS_DEV_ID;
	}
	else {
		if (ECPRI_DMA_GET_HW_FLAVOR() == ECPRI_HW_FLAVOR_RU) {
			endp_ctx = &ecpri_dma_ctx->endp_ctx[ECPRI_DMA_SS_ORAN_LOG_QRU_GSI_ID]
				[ECPRI_DMA_SS_ORAN_LOG_QRU_EGRESS_ENDP_ID];
			endp_id = ECPRI_DMA_SS_ORAN_LOG_QRU_EGRESS_ENDP_ID;
			gsi_id = ECPRI_DMA_SS_ORAN_LOG_QRU_GSI_ID;
		}
		else {
			endp_ctx = &ecpri_dma_ctx->endp_ctx[ECPRI_DMA_SS_ORAN_LOG_X100_GSI_ID]
				[ECPRI_DMA_SS_ORAN_LOG_X100_EGRESS_ENDP_ID];
			endp_id = ECPRI_DMA_SS_ORAN_LOG_X100_EGRESS_ENDP_ID;
			gsi_id = ECPRI_DMA_SS_ORAN_LOG_X100_GSI_ID;
		}
		dev_id = ECPRI_DMA_SS_ORAN_LOG_EGRESS_DEV_ID;
	}

	ret = ecpri_dma_stop_endp(endp_ctx);
	if (ret)
	{
		DMAERR("Failed to stop ORAN logging endp_id: %d, gsi_id %d\n",
			endp_ctx->endp_id,
			endp_ctx->gsi_id);
	}
	ecpri_dma_ss_core_ctx->oran_log_cdev_read_state[dev_id] = true;

	return ret;
}

uint8_t log_pkt[BUFFER_SIZE]={0};

static void extract_ecpri_header(uint8_t *packet, struct ecpri_hdr *header) {

	header->protocol_revision = (packet[0] >> 4) & 0x0F;
	header->reserved = (packet[0] >> 1) & 0x07;
	header->c_bit = packet[0] & 0x01;
	header->message_type = packet[1];
	header->payload_size = (packet[2] << 8) | packet[3];
}

static ssize_t ecpri_dma_ecpri_ss_read_oran_log(
	struct ecpri_dma_endp_context* endp_ctx,
	enum ecpri_dma_ss_oran_log_dev dev_id,
	struct file* file, char __user* buf, size_t count, loff_t* offset)
{
	int ret = 0;
	u32 actual_num = 0, i = 0, j = 0;
	struct ecpri_dma_pkt_completion_wrapper* oran_pkts_arr;
	struct ecpri_dma_pkt_completion_wrapper** oran_pkts;
	ssize_t total_cnt = 0;
	union __packed gsi_channel_scratch scrth;
	u16 pkt_len = 0;
	u32 len=count;
	u32 size=0;
	u32 budget = 0, num_of_buffs = 0;
	int k, s_idx, buff_count = 0;
	struct ecpri_hdr header;

	if (!endp_ctx || !endp_ctx->valid)
	{
		return -ENODATA;
	}

	if (ecpri_dma_ss_core_ctx->oran_log_cdev_read_state[dev_id] == false)
	{
		return -EINPROGRESS;
	}

	if (!ecpri_dma_ss_core_ctx->oran_log_cdev_read_in_progress[dev_id]) {
	
		ret = ecpri_dma_stop_endp(endp_ctx);
		if (ret != 0) {
			DMAERR("Unable to stop endp, endp_id: %d, gsi_id %d\n",
				endp_ctx->endp_id, endp_ctx->gsi_id);
			return -EFAULT;
		}
		len= len-sizeof(pcap_hdr);
		if(len<0)
			return -EFAULT;
		/* Prepare PCAP hdr and copy to user */
		ret = copy_to_user(buf + total_cnt, &pcap_hdr, sizeof(pcap_hdr));
		if (ret) {
			DMAERR("copy_to_user failed for PCAP header err:%d\n", ret);
			return -EFAULT;
		}
		total_cnt += sizeof(pcap_hdr);
		*offset += sizeof(pcap_hdr);

		ecpri_dma_ss_core_ctx->oran_log_cdev_read_in_progress[dev_id] = true;
		ecpri_dma_ss_core_ctx->oran_log_pkt_idx[dev_id] = 0;

		/*
		 * If enough packets have been recieved that the RP have wrapped around
		 * we need to update the GSI driver local RP to read from the oldest
		 * packet in the ring
		 */
		ret = gsi_read_channel_scratch(endp_ctx->gsi_chan_hdl, &scrth);
		if (ret != GSI_STATUS_SUCCESS)
		{
			DMAERR("Failed to read CH scratch chan_hdl=%lu\n",
				endp_ctx->gsi_chan_hdl);
			ecpri_dma_assert();
		}

		if (scrth.mhi.total_buffs > endp_ctx->ring_length) {

			ret = gsi_update_evt_rp(endp_ctx->gsi_chan_hdl);
			if (ret != GSI_STATUS_SUCCESS) {
				DMAERR("GSI update EVT RP failed %d", ret);
				ecpri_dma_assert();
			}

			ret = ecpri_dma_advance_outstanding_list(endp_ctx);
			if (ret) {
				DMAERR("ecpri_dma_advance_outstanding_list failed %d", ret);
				ecpri_dma_assert();
			}
		}
	}

	size = sizeof(dummy_ethhdr) + sizeof(pcap_pkt_hdr) + ecpri_dma_ss_core_ctx->pkt_size[dev_id];
	num_of_buffs = (len/size);
	budget = num_of_buffs/DMA_MAX_BUFFERS_PER_PACKET;

	/* Prepare memory */
	oran_pkts_arr = kzalloc(
		sizeof(struct ecpri_dma_pkt_completion_wrapper) *
		num_of_buffs, GFP_KERNEL);
	ecpri_dma_assert_on(!oran_pkts_arr);

	oran_pkts = kzalloc(
		sizeof(struct ecpri_dma_pkt_completion_wrapper*) *
		num_of_buffs, GFP_KERNEL);
	ecpri_dma_assert_on(!oran_pkts);

	for (i = 0; i < num_of_buffs; i++) {
		oran_pkts[i] = &(oran_pkts_arr[i]);
	}

	ret = ecpri_dma_dp_poll(endp_ctx, budget,
		oran_pkts, &actual_num);
	if (ret) {
		DMAERR("ORAN logging endp polling failed err:%d\n", ret);
		kfree(oran_pkts_arr);
		kfree(oran_pkts);
		ecpri_dma_assert();
	}

	s_idx = 0;
	for (i = 0; i < actual_num; i++) {

		memset(log_pkt,0,BUFFER_SIZE);
		pkt_len = 0;
		j = 0;

		for(k = s_idx; k < (s_idx + DMA_MAX_BUFFERS_PER_PACKET); k++) {

			if (oran_pkts[k]->comp_code == ECPRI_DMA_COMPLETION_CODE_OVERFLOW)
			{
				memcpy(log_pkt+pkt_len, oran_pkts[k]->pkt->buffs[0]->virt_base, oran_pkts[k]->pkt->buffs[0]->size);
				pkt_len += oran_pkts[k]->pkt->buffs[0]->size;
				buff_count++;  // count valid buffers
				j++;
			}
			else if (oran_pkts[k]->comp_code == ECPRI_DMA_COMPLETION_CODE_EOT)
			{
				memcpy(log_pkt+pkt_len, oran_pkts[k]->pkt->buffs[0]->virt_base, oran_pkts[k]->pkt->buffs[0]->size);
				pkt_len += oran_pkts[k]->pkt->buffs[0]->size;
				buff_count++;
				j++;

				if(ecpri_dma_ss_core_ctx->oran_log_pkt_idx[dev_id] == 0)
				{
					extract_ecpri_header(log_pkt, &header);
					if(header.payload_size != (pkt_len - sizeof(struct ecpri_hdr)))
					{
						ecpri_dma_ss_core_ctx->oran_log_pkt_idx[dev_id]++;
						break;
					}
				}

				pcap_pkt_hdr.captured_len = pkt_len + sizeof(dummy_ethhdr);
				pcap_pkt_hdr.orig_len = pkt_len + sizeof(dummy_ethhdr);
				pcap_pkt_hdr.timestamp_msec =
				ecpri_dma_ss_core_ctx->oran_log_pkt_idx[dev_id]++;

				ret =
					copy_to_user(buf + total_cnt, &pcap_pkt_hdr, sizeof(pcap_pkt_hdr));
				if (ret) {
					DMAERR("copy_to_user failed for PCAP pkt header err:%d\n", ret);
					ret = -EFAULT;
					goto oran_read_exit;
				}

				total_cnt += sizeof(pcap_pkt_hdr);
				*offset += sizeof(pcap_pkt_hdr);

				ret =
					copy_to_user(buf + total_cnt, &dummy_ethhdr, sizeof(dummy_ethhdr));
				if (ret) {
					DMAERR("copy_to_user failed for ETH pkt header err:%d\n", ret);
					ret = -EFAULT;
					goto oran_read_exit;
				}

				total_cnt += sizeof(dummy_ethhdr);
				*offset += sizeof(dummy_ethhdr);

				ret = copy_to_user(buf + total_cnt, log_pkt, pkt_len);
				if (ret) {
					DMAERR("copy_to_user failed for buffer  err:%d\n", ret);
					ret = -EFAULT;
					goto oran_read_exit;
				}

				total_cnt += pkt_len;
				*offset += pkt_len;

				break;                    // break if EOT detected
			}
		}
		s_idx = buff_count;
	}
oran_read_exit:
	kfree(oran_pkts_arr);
	kfree(oran_pkts);

	if (total_cnt == 0) {
		ecpri_dma_ss_core_ctx->oran_log_cdev_read_in_progress[dev_id] = false;
		ecpri_dma_ss_core_ctx->oran_log_cdev_read_state[dev_id] = false;
	}
	return total_cnt;
}

ssize_t ecpri_dma_ecpri_ss_read_oran_log_egress(struct file* file,
	char __user* buf, size_t count, loff_t* offset)
{
	struct ecpri_dma_endp_context* endp_ctx;

	if (ECPRI_DMA_GET_HW_FLAVOR() == ECPRI_HW_FLAVOR_RU)
		endp_ctx = &ecpri_dma_ctx->endp_ctx[ECPRI_DMA_SS_ORAN_LOG_QRU_GSI_ID]
		[ECPRI_DMA_SS_ORAN_LOG_QRU_EGRESS_ENDP_ID];
	else
		endp_ctx = &ecpri_dma_ctx->endp_ctx[ECPRI_DMA_SS_ORAN_LOG_X100_GSI_ID]
		[ECPRI_DMA_SS_ORAN_LOG_X100_EGRESS_ENDP_ID];

	return ecpri_dma_ecpri_ss_read_oran_log(
		endp_ctx, ECPRI_DMA_SS_ORAN_LOG_EGRESS_DEV_ID,
		file, buf, count, offset);
}

ssize_t ecpri_dma_ecpri_ss_read_oran_log_ingress(struct file* file,
	char __user* buf, size_t count, loff_t* offset)
{
	struct ecpri_dma_endp_context* endp_ctx;

	if (ECPRI_DMA_GET_HW_FLAVOR() == ECPRI_HW_FLAVOR_RU)
		endp_ctx = &ecpri_dma_ctx->endp_ctx[ECPRI_DMA_SS_ORAN_LOG_QRU_GSI_ID]
		[ECPRI_DMA_SS_ORAN_LOG_QRU_INGRESS_ENDP_ID];
	else
		endp_ctx = &ecpri_dma_ctx->endp_ctx[ECPRI_DMA_SS_ORAN_LOG_X100_GSI_ID]
		[ECPRI_DMA_SS_ORAN_LOG_X100_INGRESS_ENDP_ID];


	return ecpri_dma_ecpri_ss_read_oran_log(
		endp_ctx, ECPRI_DMA_SS_ORAN_LOG_INGRESS_DEV_ID,
		file, buf, count, offset);
}

/* API exposed structure */
const struct ecpri_dma_ecpri_ss_ops dma_ecpri_ss_driver_ops = {
	.ecpri_dma_ecpri_ss_register = ecpri_dma_ecpri_ss_register,
	.ecpri_dma_ecpri_ss_deregister = ecpri_dma_ecpri_ss_deregister,
	.ecpri_dma_ecpri_ss_get_endp_mapping = ecpri_dma_ecpri_ss_get_endp_mapping,
	.ecpri_dma_ecpri_ss_nfapi_config = ecpri_dma_ecpri_ss_nfapi_config,
	.ecpri_dma_ecpri_ss_query_stats = ecpri_dma_ecpri_ss_query_stats,
	.ecpri_dma_ecpri_ss_notify_ssr = ecpri_dma_ecpri_ss_notify_ssr,
	.ecpri_dma_ecpri_ss_start_oran_log = ecpri_dma_ecpri_ss_start_oran_log,
	.ecpri_dma_ecpri_ss_stop_oran_log = ecpri_dma_ecpri_ss_stop_oran_log,
};
EXPORT_SYMBOL(dma_ecpri_ss_driver_ops);

