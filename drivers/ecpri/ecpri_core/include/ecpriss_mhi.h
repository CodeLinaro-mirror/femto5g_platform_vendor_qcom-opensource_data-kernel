/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef ECPRISS_MHI_H_
#define ECPRISS_MHI_H_


#include "ecpriss_core.h"
#include "csm_lte_eth_dev.h"
#include <linux/msm_mhi_dev.h>

#define ECPRISS_MHI_MAX_VF 3
#define ECPRISS_MAX_MHI_CHANNEL_VF 2
#define ECPRISS_MHI_MAX_PKT_SIZE 2000
#define ECPRISS_MHI_MAX_PKTS 32
#define ECPRISS_MAX_REQ_CACHE_CNT 80


#define VF_5 5
#define VF_8 8
#define VF_9 9


/* Ecpriss MHI Channel State */
enum ecpriss_mhi_ch_state {

	ECPRISS_MHI_CH_STATE_INIT, /*ECPRISS_MHI_CH_STATE_INIT*/
	ECPRISS_MHI_CH_STATE_CONNECTED, /*ECPRISS_MHI_CH_STATE_CONNECTED*/
	ECPRISS_MHI_CH_STATE_DISCONNECTED, /*ECPRISS_MHI_CH_STATE_DISCONNECTED*/
	ECPRISS_MHI_CH_STATE_OPEN, /*ECPRISS_MHI_CH_STATE_OPEN*/
	ECPRISS_MHI_CH_STATE_CLOSE /*ECPRISS_MHI_CH_STATE_CLOSE*/
};

/* Ecpriss MHI Channel State */
enum ecpriss_mhi_chan_dir {

	ECPRISS_MHI_CH_DIR_OUT = 0x0,
	ECPRISS_MHI_CH_DIR_IN = 0x1,
	ECPRISS_MHI_CH_DIR_reserved = 0x80000000
};

/*Ecpriss MHI Channel Attributes*/
struct ecpriss_mhi_ch_attr_s {

	struct mhi_dev_client *handle; /*MHI Client Handle*/
	enum mhi_client_channel ch_id; /*Channel ID*/
	enum ecpriss_mhi_chan_dir dir; /* Channel Direction*/
	atomic_t ch_state; /* Channel State */
	int vf_id; /* Channel VF ID*/
	size_t max_pkt_size; /*Max Channel Payload Size */
	struct work_struct work; /* Work Struct for handling Req/Rsp*/
	struct work_struct state_work; /* Wor Struct for Handling Channel State*/
	u32 nr_pkts; /* Max Packets Supported */
	void *buf;  /* Buffer for Channel read Operations*/
	void (*event_notifier)(struct mhi_dev_client_cb_reason *cb); /* Input Req handler */
	void (*state_notifier)(struct mhi_dev_client_cb_data *cb_data); /* State Change Handler*/
	void *ctx;
	csm_lte_ethdev_msg_s req[ECPRISS_MAX_REQ_CACHE_CNT] ; /*Read Req Cache*/
	int curr_req_idx; /*Read req Counter*/
	csm_lte_ethdev_msg_s rsp[ECPRISS_MAX_REQ_CACHE_CNT] ; /*Rsp Cache*/
	int curr_rsp_idx; /* Write curr Counter */
	int num_pkts; /* Num Pkts Received on Channel */
	int num_bytes; /* Num Bytes Rcvd on Channel */
	struct mutex ch_mtx; /*Channel Mutex*/

};

/*Ecpriss VF Ctx */
struct ecpriss_mhi_vf_ctx_s {

	int vf_id; /* VF_ID*/
	struct ecpriss_mhi_ch_attr_s ch_info[ECPRISS_MAX_MHI_CHANNEL_VF]; /*Channel Context */

};

/* Ecpriss MHI Client Context*/

typedef struct ecpriss_mhi_client_ctx_s {

	struct ecpriss_mhi_vf_ctx_s * mhi_vf_info; /* Pointer to VF Ctx Info*/
	struct workqueue_struct *mhi_wq[ECPRISS_MHI_MAX_VF]; /* Wq Array per VF for Req Processing*/
	struct workqueue_struct *mhi_chan_st_wq; /* Wq to handle State Change Notifications*/
	spinlock_t ctx_lock; /* Ctx Lock*/

}ecpriss_mhi_client_ctx_t;

int ecpriss_mhi_vf_init_all(void);
int ecpriss_mhi_vf_deinit_all(void);
int ecpriss_mhi_ctx_init(void **mhi_ctx);
int ecpriss_mhi_ctx_deinit(void *mhi_ctx);
int ecpriss_mhi_chan_init(struct ecpriss_mhi_ch_attr_s *ch_attr);
int ecpriss_mhi_chan_deinit(struct ecpriss_mhi_ch_attr_s *ch_attr);
void ecpriss_mhi_client_cb(struct mhi_dev_client_cb_reason *reason);
void ecpriss_mhi_ch_state_cb(struct mhi_dev_client_cb_data *cb_data);
void ecpriss_mhi_process_request(void *buf, int len, struct ecpriss_mhi_ch_attr_s *ch_info);
void ecpriss_mhi_work_fn(struct work_struct *work);
void ecpriss_mhi_state_work_fn(struct work_struct *work);
void ecpriss_mhi_write_complete_cb(void *req);
int ecpriss_mhi_send_rsp(void *buf, int len,
                 struct ecpriss_mhi_ch_attr_s *ch_attr);
int ecpriss_mhi_get_wq_idx_from_vfid(int vf_id);
void ecpriss_mhi_process_get_link_state(csm_lte_ethdev_msg_s *req,
		struct ecpriss_mhi_ch_attr_s *ch_info);
void ecpriss_mhi_process_get_link_rate(csm_lte_ethdev_msg_s *req,
		struct ecpriss_mhi_ch_attr_s *ch_info);

void ecpriss_mhi_process_async_link_state(int port, int link, int state);
void ecpriss_mhi_process_async_link_state_util(int port, int link, int state, int vf_id);
void ecpriss_mhi_gen_rsp_util(csm_lte_ethdev_msg_s *req, csm_lte_ethdev_msg_s *rsp,
		                csm_lte_ethdev_result_e status);

#endif
