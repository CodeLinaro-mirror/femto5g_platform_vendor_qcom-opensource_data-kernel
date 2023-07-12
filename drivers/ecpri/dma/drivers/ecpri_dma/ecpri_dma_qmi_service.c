/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include <linux/soc/qcom/qmi.h>
#include "ecpri_dma_qmi_service.h"
#include "ecpri_dma_utils.h"
#include "ecpri_dma_qmi_v01.h"

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
ecpri_dma_handle_indication(struct qmi_handle* qmi_handle,
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
 *  In our case, client_handlers needs handling only for QMI_INDICATION,
 *  since the QMI_REQUEST/ QMI_RESPONSE are handled in a blocking fashion
 *  at the time of sending QMI_REQUESTs.
 */
static struct qmi_msg_handler client_handlers[] = {
	{
		.type = QMI_INDICATION,
		.msg_id = QMI_ECPRI_INIT_MODEM_DRIVER_COMPLETE_IND_V01,
		.ei = ecpri_init_modem_driver_cmplt_ind_msg_v01_ei,
		.decoded_size = sizeof(struct ecpri_init_modem_driver_cmplt_ind_msg_v01),
		.fn = ecpri_dma_handle_indication,
	},
};

static void ecpri_dma_qmi_service_q6_send_init_msg(struct work_struct* work);
static DECLARE_DELAYED_WORK(ecpri_dma_work_send_q6_init_msg,
	ecpri_dma_qmi_service_q6_send_init_msg);
static void ecpri_dma_q6_clnt_svc_exit(struct work_struct* work);
static DECLARE_DELAYED_WORK(ecpri_dma_work_svc_exit,
	ecpri_dma_q6_clnt_svc_exit);

static void ecpri_dma_a55_svc_disconnect_cb(struct qmi_handle* qmi, unsigned int node,
	unsigned int port)
{
	DMADBG("Received QMI client disconnect\n");
}

static void ecpri_dma_q6_clnt_svc_event_notify_net_reset(struct qmi_handle* qmi)
{
	if (!ecpri_dma_qmi_ctx->wq_stop)
		queue_delayed_work(ecpri_dma_qmi_ctx->clnt_req_wq,
			&ecpri_dma_work_svc_exit,
			0);
}

static void ecpri_dma_q6_clnt_svc_event_notify_svc_exit(struct qmi_handle* qmi,
	struct qmi_service* svc)
{
	DMADBG("QMI svc:%d vers:%d ins:%d node:%d port:%d\n", svc->service,
		svc->version, svc->instance, svc->node, svc->port);

	if (!ecpri_dma_qmi_ctx->wq_stop)
		queue_delayed_work(ecpri_dma_qmi_ctx->clnt_req_wq,
			&ecpri_dma_work_svc_exit,
			0);
}

static void ecpri_dma_q6_clnt_svc_exit(struct work_struct* work)
{
	if (ecpri_dma_qmi_ctx != NULL) {
		ecpri_dma_qmi_ctx->q6_disconnected = true;
		DMADBG("Q6 disconnected\n");
	}
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
	ecpri_dma_qmi_ctx->q6_init_cmplt = false;
	ecpri_dma_qmi_ctx->q6_response_recv = false;
	ecpri_dma_qmi_ctx->q6_registered = false;
	ecpri_dma_qmi_ctx->q6_disconnected = false;
	ecpri_dma_qmi_ctx->wq_stop = false;
	ecpri_dma_qmi_ctx->sending_retries = 0;

	mutex_init(&ecpri_dma_qmi_ctx->lock);

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

	ecpri_dma_qmi_ctx->wq_stop = true;
	DMADBG("wq_stop: %d\n",
	ecpri_dma_qmi_ctx->wq_stop);

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
	ecpri_dma_qmi_ctx->wq_stop = true;
	DMADBG("q_stop: %d\n",
	ecpri_dma_qmi_ctx->wq_stop);

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
	if (!ecpri_dma_qmi_ctx->wq_stop) {
		queue_delayed_work(ecpri_dma_qmi_ctx->clnt_req_wq,
			&ecpri_dma_work_send_q6_init_msg, 0);
	}

	return 0;
}

static int ecpri_dma_qmi_service_init_q6_send_msg(void)
{
	/* Define request message */
	struct ecpri_init_modem_driver_req_msg_v01 req = {
		.platform_type = ecpri_dma_get_ctx_hw_flavor(),
		.ep_desc_list_len = ECPRI_NUM_MODEM_EP_V01,
		.hw_version_valid = true,
		.hw_version = ecpri_dma_get_ctx_hw_ver(),
		.sw_version_valid = true,
		.sw_version = ecpri_dma_get_sw_ver(),
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
		ecpri_dma_qmi_ctx->q6_response_recv = true;
		DMADBG("q6_response_recv: %d\n",
		ecpri_dma_qmi_ctx->q6_response_recv);

		DMADBG("q6 response: sw_version - %d sw_version_valid - %d\n",
		resp.sw_version,
		resp.sw_version_valid);

	} else {
		DMAERR("Error: response timeout\n");
	}

	return ret;
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

		DMAERR("QMI handshake retry number: %d \n",
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

static void ecpri_dma_handle_indication(struct qmi_handle* qmi_handle,
	struct sockaddr_qrtr* sq,
	struct qmi_txn* txn,
	const void* decoded_msg)
{
	struct ecpri_init_modem_driver_cmplt_ind_msg_v01 *indication;

	indication	=
	(struct ecpri_init_modem_driver_cmplt_ind_msg_v01*)decoded_msg;

	ecpri_dma_qmi_ctx->q6_indication_recv = true;
	DMADBG("q6_indication_recv: %d\n",
	ecpri_dma_qmi_ctx->q6_indication_recv);

	DMADBG("Indication: driver mode - %d driver valid - %d\n",
	indication->modem_driver_mode,
	indication->modem_driver_mode_valid);

	ecpri_dma_qmi_ctx->q6_init_cmplt = true;
	DMADBG("q6_init_cmplt: %d\n",
	ecpri_dma_qmi_ctx->q6_init_cmplt);

	/* Cache the client sq */
	memcpy(&ecpri_dma_qmi_ctx->client_sq, sq, sizeof(*sq));
}
