/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _ECPRI_DMA_QMI_SERVICE_H_
#define _ECPRI_DMA_QMI_SERVICE_H_

#include <linux/soc/qcom/qmi.h>
#include "ecpri_dma_i.h"
#include "ecpri_dma_qmi_v01.h"

#define ECPRI_DMA_Q6_SVC_VERS 1
#define ECPRI_DMA_A55_SVC_VERS 1
#define ECPRI_DMA_QMI_COMPLETION_TIMEOUT (1 * HZ)
#define ECPRI_DMA_QMI_RESPONSE_TIMEOUT (60 * HZ)
#define ECPRI_DMA_QMI_INIT_COMPLETE_TIMEOUT (110 * HZ)
#define ECPRI_DMA_QMI_SYNC_COMPLETE_TIMEOUT (110 * HZ)

#define ECPRI_DMA_QMI_MAX_RETRIES (100)

#define ECPRI_DMA_A55_SERVICE_SVC_ID 0x434
#define ECPRI_DMA_A55_SERVICE_INS_ID 1
#define ECPRI_DMA_Q6_SERVICE_SVC_ID 0x434
#define ECPRI_DMA_Q6_SERVICE_INS_ID 2

#define ECPRI_DMA_CUR_DMA_QMI_SW_VER (ECPRI_DMA_QMI_SW_V3)

 /* This is the largest MAX_MSG_LEN we have for all the messages
  * we expect to receive. This argument will be used in
  * qmi_handle_init to allocate a receive buffer for the socket
  * associated with our qmi_handle
  */
#define QMI_ECPRI_DMA_MAX_MSG_LEN 22685

 /**
  * Defines QMI message falvors:
  * sync message blocks until indication is recieved
  * and async only waits for response.
  */
enum ecpri_dma_qmi_msg_type{
	ECPRI_DMA_QMI_MSG_ASYNC = 0,
	ECPRI_DMA_QMI_MSG_SYNC = 1,
};

 /**
  * Q6 QMI message versioning
  * ver 1: supports only init handshake
  * ver 2: adds support for ch cmd with stop endp
  * ver 3: adds support for ch cmd for start endp
  */
enum ecpri_dma_qmi_q6_sw_vsersion {
	ECPRI_DMA_QMI_Q6_SW_INVALID = 0,
	ECPRI_DMA_QMI_Q6_SW_VER_1 = 1,
	ECPRI_DMA_QMI_Q6_SW_VER_2 = 2,
	ECPRI_DMA_QMI_Q6_SW_VER_3 = 3,
};

 /**
  * DMA Q6 QMI message versioning
  * ver 1: supports only init handshake
  * ver 2: adds support for ch cmd for stop endp
  * ver 3: adds support for ch cmd for start endp
  */
enum ecpri_dma_qmi_dma_sw_versions {
	ECPRI_DMA_QMI_SW_INVALID = 0,
	ECPRI_DMA_QMI_SW_V1 = 1,
	ECPRI_DMA_QMI_SW_V2 = 2,
	ECPRI_DMA_QMI_SW_V3 = 3,
};

/* QMI hadnshake context */
struct ecpri_dma_qmi_context {
	struct qmi_handle* svc_handle;
	struct qmi_handle* q6_clnt;
	struct workqueue_struct* clnt_req_wq;
	struct mutex lock;
	struct sockaddr_qrtr client_sq;
	struct sockaddr_qrtr server_sq;
	u32 sending_retries;
	bool send_q6_init;
	bool q6_init_sent;
	bool q6_indication_recv;
	atomic_t q6_init_cmplt;
	atomic_t q6_response_recv;
	bool q6_registered;
	bool wq_stop;
	atomic_t q6_disconnected;
	struct completion qmi_q6_int_cmplt_completion;
	struct completion qmi_ch_cmd_sync_completion;
	u32 q6_hw_version;
	atomic_t q6_sw_version;
	enum ecpri_dma_qmi_dma_sw_versions  dma_sw_version;
	struct mutex sync_ch_cmd_lock;
	struct list_head pending_ch_cmd_indiciation_list;
	struct list_head ecpri_dma_pending_q6_msg;
	struct mutex cmd_list_lock;
	struct mutex deferred_cmd_list_lock;
};

int ecpri_dma_qmi_service_init(void);
int ecpri_dma_qmi_send_q6_msg(void);
void ecpri_dma_qmi_service_exit(void);

/**
 * QMI command structure
 * @req: command request
 * @flag: sync/async command sepcifier
 */
struct ecpri_dma_pending_qmi_cmd {
	struct ecpri_modem_ch_cmd_req_msg_v01 req;
	enum ecpri_dma_qmi_msg_type flag;
};

/**
 * Wrapper for the QMU command list item
 * @link: list attribute
 * @item: the QMI command
 */
struct ecpri_dma_pending_qmi_cmd_wrapper {
	struct list_head link;
	struct ecpri_dma_pending_qmi_cmd item;
};

/**
 * ecpri_dma_qmi_service_send_ch_cmd_q6() - tries to send QMI command to Q6
 *
 * @endp_cfg: A55 endpoint's context
 * @op: the operation to execute
 * @flag: sync/non sync command specifer
 * @enforce_order: When true - send this cmd, when false, check if this endp
 * has an earlier command to send
 *
 * Return: 0 on success Linux error on failure
 */
int ecpri_dma_qmi_service_send_ch_cmd_q6(
	struct ecpri_dma_endp_context *endp_cfg,
	enum ecpri_ch_cmd_type_enum_v01 op,
	enum ecpri_dma_qmi_msg_type flag,
	bool enforce_order);

/**
 * ecpri_dma_qmi_get_sw_ver() - get the QMI dma software version
 *
 * Return: supported qmi software version value
 */
enum ecpri_dma_qmi_dma_sw_versions ecpri_dma_qmi_get_sw_ver(void);

/**
 * ecpri_dma_qmi_get_q6_sw_ver() - get the reported QMI dma software version
 *
 * Return: Q6 reported software version value
 */
enum ecpri_dma_qmi_q6_sw_vsersion ecpri_dma_qmi_get_q6_sw_ver(void);

#endif /* _ECPRI_DMA_QMI_SERVICE_H_ */
