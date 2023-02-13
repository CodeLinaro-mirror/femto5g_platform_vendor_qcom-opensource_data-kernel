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
#define ECPRI_DMA_QMI_COMPLETION_TIMEOUT (60 * HZ)
#define ECPRI_DMA_QMI_MAX_RETRIES (100)

#define ECPRI_DMA_A55_SERVICE_SVC_ID 0x434
#define ECPRI_DMA_A55_SERVICE_INS_ID 1
#define ECPRI_DMA_Q6_SERVICE_SVC_ID 0x434
#define ECPRI_DMA_Q6_SERVICE_INS_ID 2

 /* This is the largest MAX_MSG_LEN we have for all the messages
  * we expect to receive. This argument will be used in
  * qmi_handle_init to allocate a receive buffer for the socket
  * associated with our qmi_handle
  */
#define QMI_ECPRI_DMA_MAX_MSG_LEN 22685

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
	bool q6_init_cmplt;
	bool q6_response_recv;
	bool q6_registered;
	bool wq_stop;
};

int ecpri_dma_qmi_service_init(void);
int ecpri_dma_qmi_send_q6_msg(void);

#endif /* _ECPRI_DMA_QMI_SERVICE_H_ */