/*
 * SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2025 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include "ecpri_dma_utils.h"
#include "ecpri_dma_ss_core.h"
#include "ecpri_hwio_def.h"
#include "dmahal_reg.h"
#include "ecpri_dma_ut_framework.h"

extern struct ecpri_dma_ss_core_context* ecpri_dma_ss_core_ctx;

#define ECPRI_DMA_SS_CORE_CLIENT_UT_READY_RCVD_TMOUT_MS (500)
#define ECPRI_DMA_SS_CORE_CLIENT_UT_READY_USER_DATA     (0xDEAD0001)
#define ECPRI_DMA_SS_CORE_CLIENT_UT_DMA_EVENT_USER_DATA (0xDEAD0002)
#define ECPRI_DMA_SS_CORE_CLIENT_UT_LOG_MSG_USER_DATA   (0xDEAD0003)

/**
 * ecpri_dma_ss_core_suite_context - all the information that
 * has to be available globally during the test
 *
 * @userdata_dma_event_notify:
 * @userdata_log_msg:
 * @userdata_ready: user data for Ready notify callback
 * @ready_received: Callback notier of DMA driver is ready
 *
 */
struct ecpri_dma_ss_core_suite_context {
	u32 userdata_dma_event_notify;
	u32 userdata_log_msg;
	u32 userdata_ready;
	struct completion ready_received;
	struct ecpri_dma_ecpri_ss_register_params ready_info;
};

struct ecpri_dma_ss_core_suite_context ecpri_dma_ss_core_suite_ctx;

static void ecpri_dma_ss_core_client_test_ready_cb(
	void* userdata_ready)
{
	if (ecpri_dma_ss_core_suite_ctx.userdata_ready
		!= (*(u32*)userdata_ready)) {
		DMA_UT_TEST_FAIL_REPORT("Received mismatched "
			"Ready user data\n");
		return;
	}

	complete(&ecpri_dma_ss_core_suite_ctx.ready_received);
}

static void ecpri_dma_ss_core_client_test_event_notify_cb(
	void* user_data,
	enum ecpri_dma_event_type ev_type)
{
	if (ecpri_dma_ss_core_suite_ctx.userdata_dma_event_notify
		!= (*(u32*)user_data)) {
		DMA_UT_TEST_FAIL_REPORT("Received mismatched "
			"DMA Event Notify user data\n");
		return;
	}
}

static void ecpri_dma_ss_core_client_test_log_msg_cb(
	void* user_data,
	const char* fmt, ...)
{
	if (ecpri_dma_ss_core_suite_ctx.userdata_log_msg != (*(u32*)user_data)) {
		DMA_UT_TEST_FAIL_REPORT("Received mismatched "
			"Log_Msg user data\n");
		return;
	}
}

/**
 * ecpri_dma_ss_core_client_test_util_create_params() - mock ETH
 * callbacks and register provides DMA driver with ETH client data
 *
 */
static void ecpri_dma_ss_core_client_test_util_create_params(
	bool* is_dma_ready,
	struct ecpri_dma_ecpri_ss_register_params* ready_info)
{
	DMA_UT_DBG("ENTRY\n");
	ready_info->notify_ready =
		&ecpri_dma_ss_core_client_test_ready_cb;
	ready_info->userdata_ready =
		&ecpri_dma_ss_core_suite_ctx.userdata_ready;

	ready_info->dma_event_notify =
		&ecpri_dma_ss_core_client_test_event_notify_cb;
	ready_info->userdata_dma_event_notify =
		&ecpri_dma_ss_core_suite_ctx.userdata_dma_event_notify;

	ready_info->log_msg =
		&ecpri_dma_ss_core_client_test_log_msg_cb;
	ready_info->userdata_log_msg =
		&ecpri_dma_ss_core_suite_ctx.userdata_log_msg;
}

static int ecpri_dma_ss_core_client_test_suite_setup(void** ppriv)
{
	DMA_UT_DBG("Start Setup\n");

	memset(&ecpri_dma_ss_core_suite_ctx, 0,
		sizeof(ecpri_dma_ss_core_suite_ctx));

	init_completion(
		&ecpri_dma_ss_core_suite_ctx.ready_received);

	ecpri_dma_ss_core_suite_ctx.userdata_ready =
		ECPRI_DMA_SS_CORE_CLIENT_UT_READY_USER_DATA;

	ecpri_dma_ss_core_suite_ctx.userdata_dma_event_notify =
		ECPRI_DMA_SS_CORE_CLIENT_UT_DMA_EVENT_USER_DATA;

	ecpri_dma_ss_core_suite_ctx.userdata_log_msg =
		ECPRI_DMA_SS_CORE_CLIENT_UT_LOG_MSG_USER_DATA;

	return 0;
}

static int ecpri_dma_ss_core_client_test_suite_teardown(void* priv)
{
	DMA_UT_DBG("Start Teardown\n");
	return 0;
}

/**
 * ecpri_dma_verify_endp_lte_config() -
 * Test LTE endpoint configuration
*/
int ecpri_dma_ss_core_client_test_lte_config(void * priv)
{

	enum ecpri_hw_ver ver = 0;
	enum ecpri_hw_flavor flv =0;
	struct ecpri_dma_endp_mapping *port_topology;
	struct ecpri_dma_topology_params *cur_destination = 0;
	struct ecpri_dma_port_params *cur_port = 0;
	struct ecpri_dma_ring_params *cur_link = 0;
	int result;
	u32 endp_id;
	u32 gsi_id;
	int i = 0;
	int j = 0;
	int k = 0;
	ecpri_hwio_def_ecpri_endp_lte_cfg_gsi_m_ch_n_u lte_cfg = { 0 };
	bool is_lte_in_topology[ECPRI_DMA_GSI_NUM_MAX][ECPRI_DMA_ENDP_NUM_MAX] = {0};
	bool is_lte_enabled_expected;

	const struct dma_gsi_ep_config \
		(*test_endp_map_ptr)[ECPRI_DMA_GSI_NUM_MAX][ECPRI_DMA_ENDP_NUM_MAX] = {0};

	/* Get current HW */
	ver = ECPRI_DMA_GET_CTX_HW_VER();
	flv = ECPRI_DMA_GET_HW_FLAVOR();

	port_topology = kzalloc(
		sizeof(struct ecpri_dma_endp_mapping), GFP_KERNEL);

	/* Get endpoints */
	result =
		ecpri_dma_get_endp_mapping(
			ver,
			flv,
			&test_endp_map_ptr);

	if (result < 0) {
		DMA_UT_ERR("Failed to get endpoint mapping\n");
		kfree(port_topology);
		return result;
	}

	result = ecpri_dma_get_port_mapping(
		ver,
		flv,
		port_topology);

	if (result < 0) {
		DMA_UT_ERR("Failed to get port mapping\n");
		kfree(port_topology);
		return result;
	}

	/* Scan the destinations supported by this topology */
	for(i = 0; i < port_topology->num_of_port_types; i++) {

		/* Get current destination */
		cur_destination =
		(struct ecpri_dma_topology_params *)&port_topology->topology_params[i];

		/* Process only FH LTE destinations */
		if (ECPRI_DMA_ENDP_STREAM_DEST_FH_LTE ==
				cur_destination->port_type) {

				/* Scan each port for this destination */
				for (j = 0; j < cur_destination->num_of_ports; j++) {

					/* Get current port*/
					cur_port = &cur_destination->dma_port_param[j];

					/* Scan port's links*/
					for(k = 0; k < cur_port->num_of_rings; k++) {
						cur_link = &cur_port->dma_rings_param[k];

						endp_id = cur_link->dest_dma_ring_id;
						gsi_id = cur_link->dest_dma_ring_gsi_id;

						/* Remember dest endpoint is LTE */
						is_lte_in_topology[gsi_id][endp_id] = true;

						endp_id = cur_link->src_dma_ring_id;
						gsi_id = cur_link->src_dma_ring_gsi_id;

						/* Remember src endpoint is LTE */
						is_lte_in_topology[gsi_id][endp_id] = true;

					}
				}
		}
	}

	/* Check for config differences between topology and endpoint maps */
	for (gsi_id = 0; gsi_id < ECPRI_DMA_GSI_NUM_MAX; gsi_id++)
		for (endp_id = 0; endp_id < ECPRI_DMA_ENDP_NUM_MAX; endp_id++) {

			/* Check for differences between topology and endp maps*/
			if((*test_endp_map_ptr)[gsi_id][endp_id].lte_enable !=
				is_lte_in_topology[gsi_id][endp_id]) {

				DMA_UT_ERR("Endpoint gsi id:%d endp id:%d "
						"configuration mismatch "
						"between topology and endpoint mapping\n",
						 gsi_id, endp_id);

				kfree(port_topology);
				return -EFAULT;
			}

			/* Verify LTE endpoints are not M2M*/
			if (ECPRI_DMA_ENDP_STREAM_MODE_M2M ==
				(*test_endp_map_ptr)[gsi_id][endp_id].stream_mode){

			 	DMA_UT_ERR("Endpoint gsi id:%d endp id:%d "
						"configuration is M2M\n",
						gsi_id, endp_id);

				kfree(port_topology);
				return -EFAULT;
			}

			if (ECPRI_DMA_ENDP_DIR_DEST ==
				(*test_endp_map_ptr)[gsi_id][endp_id].dir)

				is_lte_enabled_expected =
					(*test_endp_map_ptr)[gsi_id][endp_id].lte_enable;
			 else
				is_lte_enabled_expected = false;

			/* Check register value */
			lte_cfg.value = ecpri_dma_hal_read_reg_mn(
					ECPRI_DMA_ENDP_LTE_CFG_GSI_m_CH_n, gsi_id, endp_id);

			/* Check register matches configuration */
			if (is_lte_enabled_expected != lte_cfg.def.is_lte) {
			 	DMA_UT_ERR("Endpoint gsi id:%d endp id:%d "
						"configuration mismatch "
						"between register value and configuration %d\n",
						gsi_id, endp_id, is_lte_enabled_expected);

				kfree(port_topology);
				return -EFAULT;
			}
		}
	kfree(port_topology);
	return 0;
}

static int ecpri_dma_ss_core_client_test_suite_registration(void* priv) {
	int ret = 0;
	bool is_dma_ready = false;

	DMA_UT_DBG("Start Registration\n");

	/* Register */
	DMA_UT_DBG("Prepare params\n");
	ecpri_dma_ss_core_client_test_util_create_params(&is_dma_ready,
		&ecpri_dma_ss_core_suite_ctx.ready_info);

	DMA_UT_DBG("Registration\n");

	ret = ecpri_dma_ecpri_ss_register(&ecpri_dma_ss_core_suite_ctx.ready_info,
		&is_dma_ready);
	if (ret != 0) {
		DMA_UT_TEST_FAIL_REPORT("Failed on register");
		ret = -EFAULT;
		goto fail;
	}

	msleep(100);

	if (wait_for_completion_timeout(&ecpri_dma_ss_core_suite_ctx.ready_received,
		msecs_to_jiffies(ECPRI_DMA_SS_CORE_CLIENT_UT_READY_RCVD_TMOUT_MS)) == 0) {
		DMA_UT_TEST_FAIL_REPORT("Test failed due to completion timeout");
		return -EFAULT;
	}

	/* Check SS Core driver state matches the expectations */
	if (ecpri_dma_ss_core_ctx->ready_cb
		!= ecpri_dma_ss_core_suite_ctx.ready_info.notify_ready) {
		DMA_UT_TEST_FAIL_REPORT("Test failed due to "
			"mismatch of Ready CB address\n");
		ret = -EFAULT;
		goto fail;
	}

	if (ecpri_dma_ss_core_ctx->event_notify_cb
		!= ecpri_dma_ss_core_suite_ctx.ready_info.dma_event_notify) {
		DMA_UT_TEST_FAIL_REPORT("Test failed due to "
			"mismatch of DMA Event Notify CB address\n");
		ret = -EFAULT;
		goto fail;
	}

	if (ecpri_dma_ss_core_ctx->log_msg_cb
		!= ecpri_dma_ss_core_suite_ctx.ready_info.log_msg) {
		DMA_UT_TEST_FAIL_REPORT("Test failed due to "
			"mismatch of Log Msg CB comp cb address\n");
		ret = -EFAULT;
		goto fail;
	}

	/* Deregister and check */
	ecpri_dma_ecpri_ss_deregister();

	if (ecpri_dma_ss_core_ctx != NULL) {
		DMA_UT_TEST_FAIL_REPORT("Context wasn't destroyed\n");
		ret = -EFAULT;
		goto fail;
	}

fail:
	return ret;
}


static int ecpri_dma_ss_core_client_test_suite_registration_no_deregister(void* priv) {
	int ret = 0;
	bool is_dma_ready = false;

	DMA_UT_DBG("Start Registration\n");

	/* Register */
	DMA_UT_DBG("Prepare params\n");
	ecpri_dma_ss_core_client_test_util_create_params(&is_dma_ready,
		&ecpri_dma_ss_core_suite_ctx.ready_info);

	DMA_UT_DBG("Registration\n");

	ret = ecpri_dma_ecpri_ss_register(&ecpri_dma_ss_core_suite_ctx.ready_info,
		&is_dma_ready);
	if (ret != 0) {
		DMA_UT_TEST_FAIL_REPORT("Failed on register");
		ret = -EFAULT;
		goto fail;
	}

	msleep(100);

	if (wait_for_completion_timeout(&ecpri_dma_ss_core_suite_ctx.ready_received,
		msecs_to_jiffies(ECPRI_DMA_SS_CORE_CLIENT_UT_READY_RCVD_TMOUT_MS)) == 0) {
		DMA_UT_TEST_FAIL_REPORT("Test failed due to completion timeout");
		return -EFAULT;
	}

	/* Check SS Core driver state matches the expectations */
	if (ecpri_dma_ss_core_ctx->ready_cb
		!= ecpri_dma_ss_core_suite_ctx.ready_info.notify_ready) {
		DMA_UT_TEST_FAIL_REPORT("Test failed due to "
			"mismatch of Ready CB address\n");
		ret = -EFAULT;
		goto fail;
	}

	if (ecpri_dma_ss_core_ctx->event_notify_cb
		!= ecpri_dma_ss_core_suite_ctx.ready_info.dma_event_notify) {
		DMA_UT_TEST_FAIL_REPORT("Test failed due to "
			"mismatch of DMA Event Notify CB address\n");
		ret = -EFAULT;
		goto fail;
	}

	if (ecpri_dma_ss_core_ctx->log_msg_cb
		!= ecpri_dma_ss_core_suite_ctx.ready_info.log_msg) {
		DMA_UT_TEST_FAIL_REPORT("Test failed due to "
			"mismatch of Log Msg CB comp cb address\n");
		ret = -EFAULT;
		goto fail;
	}

fail:
	return ret;
}

/* Suite definition block */
DMA_UT_DEFINE_SUITE_START(ss_core_client, "SS Core Client suite",
	ecpri_dma_ss_core_client_test_suite_setup,
	ecpri_dma_ss_core_client_test_suite_teardown) {
	DMA_UT_ADD_TEST(
		register,
		"This test will verify the registration process"
		" of the SS Core Client.",
		ecpri_dma_ss_core_client_test_suite_registration, true,
		ECPRI_HW_V1_0, ECPRI_HW_MAX),
	DMA_UT_ADD_TEST(
		register_no_deregister,
		"This test will verify the registration process"
		" of the SS Core Client. without deregister",
		ecpri_dma_ss_core_client_test_suite_registration_no_deregister, false,
		ECPRI_HW_V1_0, ECPRI_HW_MAX),
	DMA_UT_ADD_TEST(
		lte_testing,
		"This test will verify LTE endpoint configuration",
		ecpri_dma_ss_core_client_test_lte_config, true,
		ECPRI_HW_V2_0, ECPRI_HW_MAX),

} DMA_UT_DEFINE_SUITE_END(ss_core_client);
