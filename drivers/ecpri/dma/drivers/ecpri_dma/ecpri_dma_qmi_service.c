/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include <linux/soc/qcom/qmi.h>
#include "ecpri_dma_qmi_service.h"
#include "ecpri_dma_utils.h"
#include "ecpri_dma_qmi_v01.h"
#include "ecpri_dma_mhi_client.h"
#include "dmahal.h"

struct ecpri_dma_qmi_context* ecpri_dma_qmi_ctx;

static void
ecpri_dma_a55_svc_disconnect_cb(struct qmi_handle* qmi, unsigned int node,
	unsigned int port);
static int
ecpri_dma_qmi_service_q6_client_event_notify_new(struct qmi_handle* qmi,
	struct qmi_service* service);
static void
ecpri_dma_q6_clnt_svc_event_notify_svc_exit(struct qmi_handle* qmi,
	struct qmi_service* svc);
static void
ecpri_dma_q6_clnt_svc_event_notify_net_reset(struct qmi_handle* qmi);
static void
ecpri_dma_handle_init_indication(struct qmi_handle* qmi_handle,
	struct sockaddr_qrtr* sq,
	struct qmi_txn* txn,
	const void* decoded_msg);

static void
ecpri_dma_handle_ch_cmd_indication(struct qmi_handle* qmi_handle,
	struct sockaddr_qrtr* sq,
	struct qmi_txn* txn,
	const void* decoded_msg);

static struct qmi_ops server_ops = {
	.del_client = ecpri_dma_a55_svc_disconnect_cb,
};

static struct qmi_ops client_ops = {
	.new_server = ecpri_dma_qmi_service_q6_client_event_notify_new,
	.del_server = ecpri_dma_q6_clnt_svc_event_notify_svc_exit,
	.net_reset = ecpri_dma_q6_clnt_svc_event_notify_net_reset,
};

static struct qmi_msg_handler server_handlers[] = {};

/*  clinet_handlers are client callbacks that will be called from QMI context
 *  when an indication from Q6 server arrives.
 *  since the QMI_REQUEST/ QMI_RESPONSE are handled in a blocking fashion
 *  at the time of sending QMI_REQUESTs.
 */
static struct qmi_msg_handler client_handlers[] = {
	{
		.type = QMI_INDICATION,
		.msg_id = QMI_ECPRI_INIT_MODEM_DRIVER_COMPLETE_IND_V01,
		.ei = ecpri_init_modem_driver_cmplt_ind_msg_v01_ei,
		.decoded_size = sizeof(struct ecpri_init_modem_driver_cmplt_ind_msg_v01),
		.fn = ecpri_dma_handle_init_indication,
	},
	{
		.type = QMI_INDICATION,
		.msg_id = QMI_ECPRI_MODEM_CH_CMD_COMPLETE_IND_V01,
		.ei = ecpri_modem_ch_cmd_cmplt_ind_msg_v01_ei,
		.decoded_size = sizeof(struct ecpri_modem_ch_cmd_cmplt_ind_msg_v01),
		.fn = ecpri_dma_handle_ch_cmd_indication,
	},
};

static void ecpri_dma_qmi_service_q6_send_init_msg(struct work_struct* work);
static DECLARE_DELAYED_WORK(ecpri_dma_work_send_q6_init_msg,
	ecpri_dma_qmi_service_q6_send_init_msg);

static void ecpri_dma_q6_clnt_svc_exit(struct work_struct* work);
static DECLARE_DELAYED_WORK(ecpri_dma_work_svc_exit,
	ecpri_dma_q6_clnt_svc_exit);


static void ecpri_dma_send_q6_start_msg(struct work_struct* work);
static DECLARE_DELAYED_WORK(ecpri_dma_work_send_q6_start_msg,
	ecpri_dma_send_q6_start_msg);


struct ecpri_dma_q6_msg_wrapper {
	struct list_head link;
	struct ecpri_dma_endp_context *endp_ctx;
	enum ecpri_ch_cmd_type_enum_v01 op;
	enum ecpri_dma_qmi_msg_type flag;
};

static bool ecpri_dma_is_handshake_complete() {
	return atomic_read(&ecpri_dma_qmi_ctx->q6_init_cmplt) &&
		atomic_read(&ecpri_dma_qmi_ctx->q6_response_recv);
}

static void ecpri_dma_a55_svc_disconnect_cb(struct qmi_handle* qmi, unsigned int node,
	unsigned int port)
{
	DMADBG_LOW("Received QMI client disconnect\n");
}

static void ecpri_dma_q6_clnt_svc_event_notify_net_reset(struct qmi_handle* qmi)
{
	if (!atomic_read(&ecpri_dma_qmi_ctx->wq_stop))
        	queue_delayed_work(ecpri_dma_qmi_ctx->clnt_req_wq,
			&ecpri_dma_work_svc_exit,
			0);
}

static void ecpri_dma_q6_clnt_svc_event_notify_svc_exit(struct qmi_handle* qmi,
	struct qmi_service* svc)
{
	DMADBG("QMI svc:%d vers:%d ins:%d node:%d port:%d\n", svc->service,
		svc->version, svc->instance, svc->node, svc->port);

	if (!atomic_read(&ecpri_dma_qmi_ctx->wq_stop))
		queue_delayed_work(ecpri_dma_qmi_ctx->clnt_req_wq,
			&ecpri_dma_work_svc_exit,
			0);
}

static void ecpri_dma_q6_clnt_svc_exit(struct work_struct* work)
{
	if (ecpri_dma_qmi_ctx != NULL) {
		atomic_set(&ecpri_dma_qmi_ctx->q6_disconnected,true);
		DMADBG("Q6 disconnected\n");
	}
}

enum ecpri_dma_qmi_dma_sw_versions ecpri_dma_qmi_get_sw_ver()
{
	return ECPRI_DMA_CUR_DMA_QMI_SW_VER;
}

enum ecpri_dma_qmi_q6_sw_vsersion ecpri_dma_qmi_get_q6_sw_ver()
{
	return atomic_read(&ecpri_dma_qmi_ctx->q6_sw_version);
}

int ecpri_dma_qmi_service_init(void)
{
	int ret = 0;

	if (ecpri_dma_qmi_ctx) {
		DMADBG("QMI already allocated\n");
		return 0;
	}

	ecpri_dma_qmi_ctx = kzalloc(sizeof(*ecpri_dma_qmi_ctx), GFP_KERNEL);
	if (!ecpri_dma_qmi_ctx) {
		DMAERR("QMI can not be allocated\n");
		return -ENOMEM;
	}

	ecpri_dma_qmi_ctx->send_q6_init = true;
	ecpri_dma_qmi_ctx->q6_init_sent = false;
	ecpri_dma_qmi_ctx->q6_indication_recv = false;
	atomic_set(&ecpri_dma_qmi_ctx->q6_init_cmplt,false);
	atomic_set(&ecpri_dma_qmi_ctx->q6_response_recv,false);
	ecpri_dma_qmi_ctx->q6_registered = false;
	atomic_set(&ecpri_dma_qmi_ctx->q6_disconnected,false);
	atomic_set(&ecpri_dma_qmi_ctx->wq_stop, false);
	ecpri_dma_qmi_ctx->sending_retries = 0;
	ecpri_dma_qmi_ctx->dma_sw_version = ecpri_dma_qmi_get_sw_ver();

	init_completion(&ecpri_dma_qmi_ctx->qmi_ch_cmd_sync_completion);

	/* Init lists */
	INIT_LIST_HEAD(&ecpri_dma_qmi_ctx->pending_ch_cmd_indiciation_list);
	INIT_LIST_HEAD(&ecpri_dma_qmi_ctx->ecpri_dma_pending_q6_msg);

	/* Initialize mutexes */
	mutex_init(&ecpri_dma_qmi_ctx->lock);
	mutex_init(&ecpri_dma_qmi_ctx->cmd_list_lock);
	mutex_init(&ecpri_dma_qmi_ctx->deferred_cmd_list_lock);
	mutex_init(&ecpri_dma_qmi_ctx->sync_ch_cmd_lock);

	ecpri_dma_qmi_ctx->svc_handle =
		kzalloc(sizeof(*ecpri_dma_qmi_ctx->svc_handle), GFP_KERNEL);
	if (!ecpri_dma_qmi_ctx->svc_handle) {
		DMAERR("svc_handle can not be allocated\n");
		ret = -ENOMEM;
		goto destroy_qmi_ctx;
	}

	ret = qmi_handle_init(ecpri_dma_qmi_ctx->svc_handle,
		QMI_ECPRI_DMA_MAX_MSG_LEN, &server_ops,
		server_handlers);
	if (ret < 0) {
		DMAERR("Initializing A55 eCPRI DMA svc failed %d\n", ret);
		goto destroy_qmi_handle;
	}

	ret = qmi_add_server(ecpri_dma_qmi_ctx->svc_handle,
		ECPRI_DMA_A55_SERVICE_SVC_ID,
		ECPRI_DMA_A55_SVC_VERS, ECPRI_DMA_A55_SERVICE_INS_ID);
	if (ret < 0) {
		DMAERR("Registering DMA A55 svc failed %d\n", ret);
		goto deregister_qmi_srv;
	}

	/* Initialize QMI-client */
	ecpri_dma_qmi_ctx->clnt_req_wq =
		create_singlethread_workqueue("DMA_A55_CLNT_REQ");
	if (!ecpri_dma_qmi_ctx->clnt_req_wq) {
		DMAERR("Creating clnt_req workqueue failed\n");
		goto deregister_qmi_srv;
	}

	ecpri_dma_qmi_ctx->q6_clnt =
		kzalloc(sizeof(*ecpri_dma_qmi_ctx->q6_clnt), GFP_KERNEL);
	if (!ecpri_dma_qmi_ctx->q6_clnt) {
		DMAERR("q6_clnt can not be allocated\n");
		ret = -ENOMEM;
		goto destroy_clnt_req_wq;
	}

	ret = qmi_handle_init(ecpri_dma_qmi_ctx->q6_clnt,
		QMI_ECPRI_DMA_MAX_MSG_LEN, &client_ops,
		client_handlers);

	if (ret < 0) {
		DMAERR("Creating clnt handle failed\n");
		goto destroy_qmi_client_handle;
	}

	ret = qmi_add_lookup(ecpri_dma_qmi_ctx->q6_clnt,
		ECPRI_DMA_Q6_SERVICE_SVC_ID, ECPRI_DMA_Q6_SVC_VERS,
		ECPRI_DMA_Q6_SERVICE_INS_ID);

	if (ret < 0) {
		DMAERR("Adding Q6 SVC failed\n");
		goto deregister_qmi_client;
	}

	/* get Q6 service and start send modem-initial to Q6 */
	DMADBG("QMI wait service available\n");

	return 0;

deregister_qmi_client:
	qmi_handle_release(ecpri_dma_qmi_ctx->q6_clnt);
destroy_qmi_client_handle:
	kfree(ecpri_dma_qmi_ctx->q6_clnt);
	ecpri_dma_qmi_ctx->q6_clnt = NULL;
destroy_clnt_req_wq:
	destroy_workqueue(ecpri_dma_qmi_ctx->clnt_req_wq);
	ecpri_dma_qmi_ctx->clnt_req_wq = NULL;
deregister_qmi_srv:
	qmi_handle_release(ecpri_dma_qmi_ctx->svc_handle);
destroy_qmi_handle:
	kfree(ecpri_dma_qmi_ctx->svc_handle);
	ecpri_dma_qmi_ctx->svc_handle = NULL;
destroy_qmi_ctx:
	kfree(ecpri_dma_qmi_ctx);
	ecpri_dma_qmi_ctx = NULL;
	return ret;
}

void ecpri_dma_qmi_service_exit(void)
{
	struct ecpri_dma_qmi_context* temp_ctx;

	mutex_lock(&ecpri_dma_qmi_ctx->lock);

	atomic_set(&ecpri_dma_qmi_ctx->wq_stop, true);
	DMADBG("wq_stop: %d\n",
	atomic_read(&ecpri_dma_qmi_ctx->wq_stop));

	/* qmi-service */
	if (ecpri_dma_qmi_ctx->svc_handle != NULL) {
		qmi_handle_release(ecpri_dma_qmi_ctx->svc_handle);
		kfree(ecpri_dma_qmi_ctx->svc_handle);
		ecpri_dma_qmi_ctx->svc_handle = NULL;
	}

	/* Release client handle */
	if (ecpri_dma_qmi_ctx->q6_clnt != NULL) {
		qmi_handle_release(ecpri_dma_qmi_ctx->q6_clnt);
		kfree(ecpri_dma_qmi_ctx->q6_clnt);
		ecpri_dma_qmi_ctx->q6_clnt = NULL;
		if (ecpri_dma_qmi_ctx->clnt_req_wq) {
			destroy_workqueue(ecpri_dma_qmi_ctx->clnt_req_wq);
			ecpri_dma_qmi_ctx->clnt_req_wq = NULL;
		}
	}

	/* clean the QMI msg cache */
	temp_ctx = ecpri_dma_qmi_ctx;
	ecpri_dma_qmi_ctx = NULL;

	mutex_unlock(&temp_ctx->lock);
	kfree(temp_ctx);
}

void ecpri_dma_qmi_stop_workqueues(void)
{
	DMADBG("Stopping all QMI workqueues\n");

	/* Stopping all workqueues so new work won't be scheduled */
	atomic_set(&ecpri_dma_qmi_ctx->wq_stop, true);
	DMADBG("q_stop: %d\n",
	atomic_read(&ecpri_dma_qmi_ctx->wq_stop));

}

static int
ecpri_dma_qmi_service_q6_client_event_notify_new(struct qmi_handle* qmi,
	struct qmi_service* service)
{
	int ret = 0;

	DMADBG("QMI svc:%d vers:%d ins:%d node:%d port:%d\n",
		service->service, service->version, service->instance,
		service->node, service->port);


	if ((service->service != ECPRI_DMA_Q6_SERVICE_SVC_ID) ||
		(service->instance != ECPRI_DMA_Q6_SERVICE_INS_ID))  {
			DMADBG("Non supported QMI service notification, no further action.\n");
			return 0;
	}

	if (!ecpri_dma_qmi_ctx) {
		DMAERR("QMI service isn't ready\n");
		return -EPERM;
	}

	ecpri_dma_qmi_ctx->server_sq.sq_family = AF_QIPCRTR;
	ecpri_dma_qmi_ctx->server_sq.sq_node = service->node;
	ecpri_dma_qmi_ctx->server_sq.sq_port = service->port;

	if (unlikely(!ecpri_dma_qmi_ctx->q6_clnt)) {
		DMAERR("Invalid q6 clnt. Ignore sending ind.\n");
		return -EINVAL;
	}

	ecpri_dma_qmi_ctx->q6_registered = true;
	DMADBG("q6_registered: %d\n",
	ecpri_dma_qmi_ctx->q6_registered);

	ret = kernel_connect(ecpri_dma_qmi_ctx->q6_clnt->sock,
		(struct sockaddr*)&ecpri_dma_qmi_ctx->server_sq,
		sizeof(ecpri_dma_qmi_ctx->server_sq), 0);
	if (ret < 0) {
		DMAERR("Couldnt connect Server\n");
		return -EFAULT;
	}

	return 0;
}

int ecpri_dma_qmi_send_q6_msg(void)
{
	if (!atomic_read(&ecpri_dma_qmi_ctx->wq_stop)) {
		queue_delayed_work(ecpri_dma_qmi_ctx->clnt_req_wq,
			&ecpri_dma_work_send_q6_init_msg, 0);
	}

	return 0;
}

static int ecpri_dma_qmi_service_init_q6_send_msg(void)
{
	/* Define request message */
	struct ecpri_init_modem_driver_req_msg_v01 req = {
		.platform_type = ECPRI_DMA_GET_HW_FLAVOR(),
		.ep_desc_list_len = ECPRI_NUM_MODEM_EP_V01,
		.hw_version_valid = true,
		.hw_version = ECPRI_DMA_GET_CTX_HW_VER(),
		.sw_version_valid = true,
		.sw_version = ecpri_dma_qmi_get_sw_ver(),
	};

	struct qmi_txn txn;
	int ret;
	struct ecpri_init_modem_driver_resp_msg_v01 resp = {};

	if (!ecpri_dma_qmi_ctx->q6_clnt)
		return -EINVAL;

	DMADBG("QMI send message started\n");

	/* Create request */
	ret = qmi_txn_init(
		ecpri_dma_qmi_ctx->q6_clnt,
		&txn,
		ecpri_init_modem_driver_resp_msg_v01_ei,
		&resp);

	if (ret < 0) {
		DMAERR("QMI txn init failed, ret= %d\n", ret);
		return ret;
	}

	mutex_lock(&ecpri_dma_qmi_ctx->lock);

	ret = qmi_send_request(
		ecpri_dma_qmi_ctx->q6_clnt,
		&ecpri_dma_qmi_ctx->server_sq,
		&txn,
		QMI_ECPRI_INIT_MODEM_DRIVER_REQ_V01,
		ECPRI_INIT_MODEM_DRIVER_REQ_MSG_V01_MAX_MSG_LEN,
		ecpri_init_modem_driver_req_msg_v01_ei,
		&req);

	if (unlikely(!ecpri_dma_qmi_ctx->q6_clnt)) {
		DMAERR("QMI Q6 client is NULL\n");
		mutex_unlock(&ecpri_dma_qmi_ctx->lock);
		return -EINVAL;
	}

	if (ret < 0) {
		DMAERR("QMI send request failed error: %d\n", ret);
		qmi_txn_cancel(&txn);
		mutex_unlock(&ecpri_dma_qmi_ctx->lock);
		return ret;
	}

	ecpri_dma_qmi_ctx->q6_init_sent = true;
	DMADBG("q6_init_sent: %d\n",
	ecpri_dma_qmi_ctx->q6_init_sent);

	ecpri_dma_qmi_ctx->send_q6_init = false;
	DMADBG("send_q6_init: %d\n",
	ecpri_dma_qmi_ctx->send_q6_init);

	mutex_unlock(&ecpri_dma_qmi_ctx->lock);

	ret = qmi_txn_wait(&txn,
		msecs_to_jiffies(ECPRI_DMA_QMI_RESPONSE_TIMEOUT));

	if (ret >= 0) {
		DMADBG("q6 response: sw_version - %d sw_version_valid - %d\n",
		resp.sw_version,
		resp.sw_version_valid);

		if (resp.sw_version_valid) {
			atomic_set(&ecpri_dma_qmi_ctx->q6_sw_version, resp.sw_version);
		}
		else {
			DMAERR("Error: Q6 QMI sw version is not valid\n");
		}

		atomic_set(&ecpri_dma_qmi_ctx->q6_response_recv, true);
		DMADBG("q6_response_recv: %d\n",
			atomic_read(&ecpri_dma_qmi_ctx->q6_response_recv));

	} else {
		DMAERR("Error: response timeout\n");
	}

	return ret;
}

static void ecpri_dma_send_q6_start_msg(struct work_struct* work) {
	struct ecpri_dma_q6_msg_wrapper *entry;
	struct ecpri_dma_q6_msg_wrapper *next;

	DMADBG_LOW("Entered ecpri_dma_send_q6_start_msg");


	if (!ecpri_dma_qmi_ctx || !ecpri_dma_qmi_ctx->q6_clnt) {
		DMAERR("Invalid ctx or q6 clnt. don't send q6 msg.\n");
		return;
	}

	if (!ecpri_dma_is_handshake_complete()) {
		queue_delayed_work(ecpri_dma_qmi_ctx->clnt_req_wq,
			&ecpri_dma_work_send_q6_start_msg,
			ECPRI_DMA_QMI_COMPLETION_TIMEOUT);

		return;
	}

	list_for_each_entry_safe(entry, next,
		&ecpri_dma_qmi_ctx->ecpri_dma_pending_q6_msg, link)
	{
		DMADBG("Handeling deferred endpoint %d\n", entry->endp_ctx->endp_id);
		ecpri_dma_qmi_service_send_ch_cmd_q6(
			entry->endp_ctx,
			entry->op,
			entry->flag,
			true);

		/* remove from list once done */
		mutex_lock(&ecpri_dma_qmi_ctx->deferred_cmd_list_lock);
		list_del(&entry->link);
		mutex_unlock(&ecpri_dma_qmi_ctx->deferred_cmd_list_lock);

		kfree(entry);
	}
}

static void ecpri_dma_qmi_service_q6_send_init_msg(struct work_struct* work)
{
	int ret = 0;

	if (!ecpri_dma_qmi_ctx || !ecpri_dma_qmi_ctx->q6_clnt) {
		DMAERR("Invalid ctx or q6 clnt. don't send q6 msg.\n");
		return;
	}

	if (!ecpri_dma_qmi_ctx->send_q6_init) {
		DMADBG("No need to send message, return\n");
		return;
	}

	if (!ecpri_dma_qmi_ctx->q6_registered) {
		ecpri_dma_qmi_ctx->sending_retries++;
		if (ecpri_dma_qmi_ctx->sending_retries >
			ECPRI_DMA_QMI_MAX_RETRIES) {

			DMAERR("Q6 isn't registered and we've done over %d retires\n",
				ECPRI_DMA_QMI_MAX_RETRIES);
			return;

		}

		DMADBG("QMI handshake retry number: %d \n",
			ecpri_dma_qmi_ctx->sending_retries);

		queue_delayed_work(ecpri_dma_qmi_ctx->clnt_req_wq,
			&ecpri_dma_work_send_q6_init_msg,
			ECPRI_DMA_QMI_COMPLETION_TIMEOUT);

		return;
	}

	ret = ecpri_dma_qmi_service_init_q6_send_msg();
	if ((ret == -ENETRESET) || (ret == -ENODEV) || (ret == -ECONNRESET)) {
		DMAERR(
			"ecpri_dma_qmi_service_init_q6_send_msg failed due to SSR!\n");
		mutex_lock(&ecpri_dma_qmi_ctx->lock);
		qmi_handle_release(ecpri_dma_qmi_ctx->q6_clnt);
		kfree(ecpri_dma_qmi_ctx->q6_clnt);
		ecpri_dma_qmi_ctx->q6_clnt = NULL;
		mutex_unlock(&ecpri_dma_qmi_ctx->lock);
		return;
	}

	if (ret < 0) {
		DMAERR("ecpri_dma_qmi_service_init_q6_send_msg failed ERRNO:[%d]\n", ret);
		/*
		 * Hardware not responding.
		 * This is a very unexpected scenario
		 * which requires a kernel panic in
		 * order to forete dumps for QMI/Q6 side analysis.
		 */
	}
}

static void ecpri_dma_handle_init_indication(struct qmi_handle* qmi_handle,
	struct sockaddr_qrtr* sq,
	struct qmi_txn* txn,
	const void* decoded_msg)
{
	struct ecpri_init_modem_driver_cmplt_ind_msg_v01 *cmplt_indication;

	cmplt_indication =
	(struct ecpri_init_modem_driver_cmplt_ind_msg_v01*)decoded_msg;

	ecpri_dma_qmi_ctx->q6_indication_recv = true;
	DMADBG("q6_indication_recv: %d\n",
	ecpri_dma_qmi_ctx->q6_indication_recv);

	DMADBG("Indication: driver mode - %d driver valid - %d\n",
	cmplt_indication->modem_driver_mode,
	cmplt_indication->modem_driver_mode_valid);

	/* Cache the client sq */
	memcpy(&ecpri_dma_qmi_ctx->client_sq, sq, sizeof(*sq));

	atomic_set(&ecpri_dma_qmi_ctx->q6_init_cmplt, true);

	DMADBG("q6_init_cmplt: %d\n",
		atomic_read(&ecpri_dma_qmi_ctx->q6_init_cmplt));
}

static void ecpri_dma_handle_ch_cmd_indication(struct qmi_handle* qmi_handle,
	struct sockaddr_qrtr* sq,
	struct qmi_txn* txn,
	const void* decoded_msg)
{
	struct ecpri_modem_ch_cmd_cmplt_ind_msg_v01 *ch_cmd_indication;
	struct ecpri_dma_pending_qmi_cmd_wrapper* entry;
	struct ecpri_dma_pending_qmi_cmd_wrapper* next;

	/* Recast the indication to the correct type */
	ch_cmd_indication =
	(struct ecpri_modem_ch_cmd_cmplt_ind_msg_v01*)decoded_msg;

	mutex_lock(&ecpri_dma_qmi_ctx->cmd_list_lock);

	list_for_each_entry_safe(entry, next,
		&ecpri_dma_qmi_ctx->pending_ch_cmd_indiciation_list, link) {

		if(ch_cmd_indication->txn_id.a55_endp_id == entry->item.req.txn_id.a55_endp_id) {

			DMADBG("Indication Q6 endp cmd %d %d %d\n",
				entry->item.req.txn_id.a55_endp_id,
				entry->item.req.txn_id.q6_endp_id,
				entry->item.req.ch_cmd);

			/* Complete sync command*/
			if (ECPRI_DMA_QMI_MSG_SYNC == entry->item.flag)
				complete(&ecpri_dma_qmi_ctx->qmi_ch_cmd_sync_completion);

			/* remove from list once notify is done */
			list_del(&entry->link);
			kfree(entry);
		}
	}

	mutex_unlock(&ecpri_dma_qmi_ctx->cmd_list_lock);
}

static int ecpri_dma_qmi_service_q6_send_ch_msg(struct ecpri_dma_pending_qmi_cmd* command)
{
	struct qmi_txn txn;
	int ret = 0;
	struct ecpri_modem_ch_cmd_resp_msg_v01 resp = {};

	if (!ecpri_dma_qmi_ctx->q6_clnt)
		return -EINVAL;

	if (!command)
		return -EINVAL;

	DMADBG("Handeling Q6 endp cmd %d %d %d\n",
		command->req.txn_id.a55_endp_id,
		command->req.txn_id.q6_endp_id,
		command->req.ch_cmd);

	/* Create request */
	ret = qmi_txn_init(
		ecpri_dma_qmi_ctx->q6_clnt,
		&txn,
		ecpri_modem_ch_cmd_resp_msg_v01_ei,
		&resp);

	if (ret < 0) {
		DMAERR("QMI txn init failed, ret= %d\n", ret);
		return ret;
	}

	mutex_lock(&ecpri_dma_qmi_ctx->lock);

	ret = qmi_send_request(
		ecpri_dma_qmi_ctx->q6_clnt,
		&ecpri_dma_qmi_ctx->server_sq,
		&txn,
		QMI_ECPRI_MODEM_CH_CMD_REQ_V01,
		ECPRI_MODEM_CH_CMD_REQ_MSG_V01_MAX_MSG_LEN ,
		ecpri_modem_ch_cmd_req_msg_v01_ei,
		&command->req);

	mutex_unlock(&ecpri_dma_qmi_ctx->lock);

	if (ret < 0) {
		DMAERR("QMI send request failed\n");
		return ret;
	}

	ret = qmi_txn_wait(&txn,
		msecs_to_jiffies(ECPRI_DMA_QMI_COMPLETION_TIMEOUT));

	if (0 == ret) {
		DMAERR("QMI response timeout\n");
		return -ETIMEDOUT;
	}

	return 0;
}

int ecpri_dma_qmi_service_send_ch_cmd_q6(
	struct ecpri_dma_endp_context *endp_ctx,
	enum ecpri_ch_cmd_type_enum_v01 op,
	enum ecpri_dma_qmi_msg_type flag,
	bool enforce_order)
{
	struct ecpri_dma_mhi_ee_gsi_tuple ee_gsi_tuple = {0};
	struct ecpri_dma_endp_gsi_tuple q6_endp;
	struct ecpri_dma_endp_filter filter = {0};
	struct ecpri_dma_pending_qmi_cmd_wrapper *qmi_cmd = NULL;
	const struct dma_gsi_ep_config *dest_endp;
	int dest_endp_id, dest_gsi_id, q6_endp_id, q6_gsi_id, a55_endp_id,
		a55_gsi_id;
	struct ecpri_dma_q6_msg_wrapper *q6_msg_wrapper;
	int result = 0;
	struct ecpri_dma_q6_msg_wrapper* entry, *next;

	/* Validate endpoint  */
	if (NULL == endp_ctx) {
		DMAERR("Provided endp is NULL\n");
		return -EINVAL;
	}

	/* Validate qmi was initialized */
	if (NULL == ecpri_dma_qmi_ctx) {
		DMAERR("QMI context is NULL\n");
		return -EINVAL;
	}

	/* Set A55 endpoint id */
	a55_endp_id = endp_ctx->endp_id;

	/* Set A55 GSI id */
	a55_gsi_id = endp_ctx->gsi_id;

	/* Check for disconnect after init */
	if (ecpri_dma_is_handshake_complete() &&
		atomic_read(&ecpri_dma_qmi_ctx->q6_disconnected))
			return 0;

	/* Check only for M2M ENDPs */
	if (endp_ctx->gsi_ep_cfg->stream_mode != ECPRI_DMA_ENDP_STREAM_MODE_M2M)
		return 0;

	if (ECPRI_DMA_ENDP_DIR_SRC == endp_ctx->gsi_ep_cfg->dir) {
		/* Get the destination endpoint  */
		dest_endp_id = endp_ctx->gsi_ep_cfg->dest;

		/* Get the GSI id, assuming deset has the same GSI id*/
		dest_gsi_id = endp_ctx->gsi_id;

		/* Get destination endpoint configuration */
		dest_endp = &(*ecpri_dma_ctx->endp_map)[dest_gsi_id][dest_endp_id];

		if ((!(dest_endp->valid)) ||
			(dest_endp->stream_mode != ECPRI_DMA_ENDP_STREAM_MODE_M2M) ||
			(dest_endp->ee != ECPRI_DMA_EE_Q6)) {

			DMADBG("ECPRI_DMA_ENDP_DIR_SRC "
			"deset_endp gsi_id:[%d] endp_id[%d] is not a valid Q6 endp\n",
			dest_gsi_id,
			dest_endp_id);

			return 0;
		}

		/* Assign Q6 Endpoint */
		q6_endp_id = dest_endp_id;
		q6_gsi_id = dest_gsi_id;

	} else {
		filter.valid = true;
		filter.valid_enable = true;
		filter.ee = ECPRI_DMA_EE_Q6;
		filter.ee_enable = true;
		filter.stream_mode = ECPRI_DMA_ENDP_STREAM_MODE_M2M;
		filter.stream_mode_enable = true;
		filter.dir = ECPRI_DMA_ENDP_DIR_SRC;
		filter.dir_enable = true;
		filter.gsi_id = endp_ctx->gsi_id;
		filter.gsi_id_enable = true;
		filter.dest = endp_ctx->endp_id;
		filter.dest_enable = true;

		/* Try to find Q6 source endpoint */
		result = ecpri_dma_filter_endps(&filter, &q6_endp, 1);
		if (result < 0) {
			DMAERR("Filtering of endpoint failed\n");
			return result;
		} else if (result == 0) {
			DMADBG("Q6 endpoint not found");
			return 0;
		} else {
			q6_endp_id = q6_endp.endp_id;
			q6_gsi_id = q6_endp.gsi_id;
		}
	}

	/* Wait for init completion*/
	if (!ecpri_dma_is_handshake_complete()) {
		DMADBG("Q6 handshke isn't completed, defer message\n");

		if (ECPRI_DMA_QMI_MSG_SYNC == flag) {
			DMAERR("Unable to send SYNC message as handshake isn't completed");
			return 0;
		}

		/* Defer command send after init is complete */
		q6_msg_wrapper =
			kmalloc(sizeof(struct ecpri_dma_q6_msg_wrapper), GFP_KERNEL);

		if (!q6_msg_wrapper) {
			DMAERR("Failed to create wrapper %d\n", q6_endp_id);
			return -ENOMEM;
		}

		/* Assign values */
		q6_msg_wrapper->endp_ctx = endp_ctx;
		q6_msg_wrapper->op = op;
		q6_msg_wrapper->flag = flag;

		mutex_lock(&ecpri_dma_qmi_ctx->deferred_cmd_list_lock);

		/* Add to list of pending messages*/
		list_add_tail(&q6_msg_wrapper->link,
			&ecpri_dma_qmi_ctx->ecpri_dma_pending_q6_msg);

		mutex_unlock(&ecpri_dma_qmi_ctx->deferred_cmd_list_lock);

		/* Start delayed work */
		queue_delayed_work(ecpri_dma_qmi_ctx->clnt_req_wq,
			&ecpri_dma_work_send_q6_start_msg,
			ECPRI_DMA_QMI_COMPLETION_TIMEOUT);

		return 0;
	}

	/* Check version */
	if (atomic_read(&ecpri_dma_qmi_ctx->q6_sw_version)
		< ECPRI_DMA_QMI_Q6_SW_VER_2) {
		DMADBG("Exit reason version 2 endp %d\n", endp_ctx->endp_id);
		return 0;
	}

	if ((atomic_read(&ecpri_dma_qmi_ctx->q6_sw_version)
		< ECPRI_DMA_QMI_Q6_SW_VER_3) &&
		(op == QMI_ECPRI_CH_CMD_TYPE_START_V01)) {
		DMADBG("Exit reason version 3 %d\n", endp_ctx->endp_id);
		return 0;
	}

	if (!enforce_order) {
		/*	Check if there's a deferred work queued for this ENDP to enforce
			order */
		mutex_lock(&ecpri_dma_qmi_ctx->deferred_cmd_list_lock);

		list_for_each_entry_safe(entry, next,
			&ecpri_dma_qmi_ctx->ecpri_dma_pending_q6_msg, link)
		{
			if (entry->endp_ctx->endp_id == endp_ctx->endp_id) {
				/* Found a qeueued deferred work for this ENDP, enforce order*/
				q6_msg_wrapper =
					kmalloc(sizeof(struct ecpri_dma_q6_msg_wrapper),
						GFP_ATOMIC);

				if (!q6_msg_wrapper) {
					DMAERR("Failed to create wrapper %d\n", q6_endp_id);
					mutex_unlock(&ecpri_dma_qmi_ctx->deferred_cmd_list_lock);
					return -ENOMEM;
				}

				/* Assign values */
				q6_msg_wrapper->endp_ctx = endp_ctx;
				q6_msg_wrapper->op = op;
				q6_msg_wrapper->flag = flag;

				/* Add to list of pending messages*/
				list_add_tail(&q6_msg_wrapper->link,
					&ecpri_dma_qmi_ctx->ecpri_dma_pending_q6_msg);

				mutex_unlock(&ecpri_dma_qmi_ctx->deferred_cmd_list_lock);

				/* Start delayed work */
				queue_delayed_work(ecpri_dma_qmi_ctx->clnt_req_wq,
					&ecpri_dma_work_send_q6_start_msg,
					ECPRI_DMA_QMI_COMPLETION_TIMEOUT);

				return 0;
			}
		}

		mutex_unlock(&ecpri_dma_qmi_ctx->deferred_cmd_list_lock);
	}

	qmi_cmd =
		kmalloc(sizeof(struct ecpri_dma_pending_qmi_cmd_wrapper), GFP_KERNEL);

	if (NULL == qmi_cmd) {
		DMAERR("QMI command allocation failed\n");
		ecpri_dma_assert();
	}

	/* Allow SYNC command to be added if the current one is async */
	if (ECPRI_DMA_QMI_MSG_SYNC == flag)
		mutex_lock(&ecpri_dma_qmi_ctx->sync_ch_cmd_lock);

	/* Assign values */
	qmi_cmd->item.req.txn_id.q6_endp_id = q6_endp_id;
	qmi_cmd->item.req.txn_id.a55_endp_id = a55_endp_id;
	qmi_cmd->item.req.txn_id.gsi_id = a55_gsi_id;
	qmi_cmd->item.req.ch_cmd = op;

	if ((*ecpri_dma_ctx->endp_map)[q6_gsi_id][q6_endp_id].is_nfapi)
		qmi_cmd->item.req.vf_id =
		(*ecpri_dma_ctx->endp_map)[q6_gsi_id][q6_endp_id].nfapi_dest_vm_id;
	else {

		ee_gsi_tuple.ee_id = endp_ctx->gsi_ep_cfg->ee;
		ee_gsi_tuple.gsi_id = a55_gsi_id;

		result = ecpri_dma_mhi_get_vf_id(&ee_gsi_tuple);

		if (result < 0) {
			DMAERR("Bad ee_gsi_tuple tupple pointer\n");
			return -EFAULT;
		} else if (ECPRI_DMA_VM_IDS_NONE == result) {
			DMAERR("VF wasn't found for A55 endpoint");
			ecpri_dma_assert();
		} else {
			qmi_cmd->item.req.vf_id = result;
		}
	}

	qmi_cmd->item.flag = flag;

	mutex_lock(&ecpri_dma_qmi_ctx->cmd_list_lock);

	/* Add item */
	list_add_tail(&qmi_cmd->link,
	 &ecpri_dma_qmi_ctx->pending_ch_cmd_indiciation_list);

	mutex_unlock(&ecpri_dma_qmi_ctx->cmd_list_lock);

	result = ecpri_dma_qmi_service_q6_send_ch_msg(&qmi_cmd->item);

	if (result != 0) {
		if (ECPRI_DMA_QMI_MSG_SYNC == flag)
			mutex_unlock(&ecpri_dma_qmi_ctx->sync_ch_cmd_lock);

		return result;
	}

	/* Wait for indication for sync messages */
	if (ECPRI_DMA_QMI_MSG_SYNC == flag) {
		result = wait_for_completion_timeout(
		&ecpri_dma_qmi_ctx->qmi_ch_cmd_sync_completion,
		msecs_to_jiffies(ECPRI_DMA_QMI_SYNC_COMPLETE_TIMEOUT));

		/* Timeout */
		if (0 == result) {

			if (!atomic_read(&ecpri_dma_qmi_ctx->q6_disconnected)) {
				DMAERR("Commmand message timeout\n");
				ecpri_dma_assert();
			}
		}

		/* Unlock QMI sync command */
		mutex_unlock(&ecpri_dma_qmi_ctx->sync_ch_cmd_lock);
	}
	return 0;
}

int ecpri_dma_qmi_service_ssr_reset(void)
{
	ecpri_hwio_def_ecpri_spare_reg_u spare_reg;

	if (!ecpri_dma_qmi_ctx) {
		DMADBG("QMI is not allocated\n");
		return EINVAL;
	}

	DMADBG("SSR: QMI: Entry QMI reset\n");

	mutex_lock(&ecpri_dma_qmi_ctx->lock);
	atomic_set(&ecpri_dma_qmi_ctx->wq_stop, true);

	ecpri_dma_qmi_ctx->send_q6_init = true;
	ecpri_dma_qmi_ctx->q6_init_sent = false;
	ecpri_dma_qmi_ctx->q6_indication_recv = false;
	atomic_set(&ecpri_dma_qmi_ctx->q6_init_cmplt, false);
	atomic_set(&ecpri_dma_qmi_ctx->q6_response_recv, false);
	ecpri_dma_qmi_ctx->q6_registered = false;
	atomic_set(&ecpri_dma_qmi_ctx->q6_disconnected, false);

	ecpri_dma_qmi_ctx->sending_retries = 0;
	ecpri_dma_qmi_ctx->dma_sw_version = ecpri_dma_qmi_get_sw_ver();

	init_completion(&ecpri_dma_qmi_ctx->qmi_ch_cmd_sync_completion);

	/* Reset Spare reg legacy handshake */
	spare_reg.value = 0;
	ecpri_dma_hal_write_reg(ECPRI_SPARE_REG, spare_reg.value);

	atomic_set(&ecpri_dma_qmi_ctx->wq_stop, false);
	mutex_unlock(&ecpri_dma_qmi_ctx->lock);

	DMADBG("SSR: QMI: Exit QMI reset\n");

	return 0;
}

int ecpri_dma_qmi_service_ssr_reset_q6_handshake(void)
{
	ecpri_hwio_def_ecpri_spare_reg_u spare_reg;

	if (!ecpri_dma_qmi_ctx) {
		DMADBG("QMI is not allocated\n");
		return EINVAL;
	}

	DMADBG("SSR: QMI: Entry QMI reset Q6 handshake\n");

	/* Clear disconnected flag */
	atomic_set(&ecpri_dma_qmi_ctx->q6_disconnected, false);

	/* Trigger Q6 init without QMI */
	spare_reg.value = ECPRI_DMA_GET_HW_FLAVOR();
	ecpri_dma_hal_write_reg(
		ECPRI_SPARE_REG, spare_reg.value);

	/* Trigger QMI message */
	ecpri_dma_qmi_send_q6_msg();
	DMADBG("SSR: QMI: EXIT QMI reset Q6 handshake\n");

	return 0;
}
