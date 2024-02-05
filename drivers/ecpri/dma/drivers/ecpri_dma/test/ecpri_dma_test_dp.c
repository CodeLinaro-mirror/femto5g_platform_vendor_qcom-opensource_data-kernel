/*
 * SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include "ecpri_dma_ut_framework.h"
#include "ecpri_dma_utils.h"
#include "ecpri_dma_dp.h"
#include "dmahal.h"

/**
  * DMA Driver Data Path DMA Unit-test suite
  * Suite will verify DMA data path via loopback SRC ENDP to DEST ENDP and
  * transfering data.
  *
  * The default loopback for the tests is M2M
  *	------------						     -----------
  *	|          |  ==={SRC  ENDP 0  EE 0}==>  |         |
  *	|   TEST   |			  			     |   DMA   |
  *	|          |  <=={DEST ENDP 37 EE 0}===  |         |
  *	------------						     -----------
  */


/* GSI ID for loopback */
#define ECPRI_DMA_DP_UT_GSI_ID 0

/* Define for test endp IRQ timer moderation */
#define ECPRI_DMA_DP_TEST_ENDP_MODT 0

/* Define for test endp IRQ counter moderation */
#define ECPRI_DMA_DP_TEST_ENDP_MODC 1

/* Define for test endp buffer size */
#define ECPRI_DMA_DP_TEST_BUFF_SIZE 1500

/* Define for test Tx endp buffer size */
#define ECPRI_DMA_DP_TEST_TX_BUFF_SIZE 16

/* Define for test endp ring length */
#define ECPRI_DMA_DP_TEST_RING_LEN 10

/* Define for number of buffs in ring */
#define ECPRI_DMA_DP_TEST_NUM_OF_BUFFS_IN_RING (ECPRI_DMA_DP_TEST_RING_LEN - 1)

/* Define for test max buffers per packet */
#define ECPRI_DMA_DP_TEST_MAX_BUFFS 3

/* Define for test packet initial content */
#define ECPRI_DMA_DP_TEST_PACKET_CONTENT 0x12345678

#define ECPRI_DMA_DP_TEST_RX_BUDGET (5)
#define ECPRI_DMA_ENDP_DIR_MAX (ECPRI_DMA_ENDP_DIR_DEST + 1)

#define BUFFER_HDR_INDEX (0)

/* Number of Tx buffers not used for data */
#define NUM_OF_NON_DATA_BUFFS (1)

#define ECPRI_DMA_DP_UT_SRC_ENDP_ID (0)
#define ECPRI_DMA_DP_UT_SRC_ENDP_GSI_ID (0)

#define ECPRI_DMA_DP_UT_DEST_ENDP_ID (37)
#define ECPRI_DMA_DP_UT_DEST_ENDP_GSI_ID (0)

#define ECPRI_DMA_DP_UT_REDIRECT_ENDP_ID (57)
#define ECPRI_DMA_DP_UT_REDIRECT_ENDP_GSI_ID (1)

#define ECPRI_DMA_DP_UT_BRAODCAST0_ENDP_ID (58)
#define ECPRI_DMA_DP_UT_BRAODCAST0_ENDP_GSI_ID (1)

#define ECPRI_DMA_DP_UT_BRAODCAST1_ENDP_ID (39)
#define ECPRI_DMA_DP_UT_BRAODCAST1_ENDP_GSI_ID (0)

/**
  * enum ecpri_dma_dp_test_suite_endp_num enumeration of test's endpoints
  * note: this is an enumeration of endpoints for the test suite,
  *		 which is different the endpoint id/gsi_id.
  */
enum ecpri_dma_dp_test_suite_endp_num {
	ECPRI_DMA_DP_TEST_ENDPOINT_DEFAULT_SRC = 0,
	ECPRI_DMA_DP_TEST_ENDPOINT_DEFAULT_DEST,
	ECPRI_DMA_DP_TEST_ENDPOINT_REDIRECT,
	ECPRI_DMA_DP_TEST_ENDPOINT_BROADCAST0,
	ECPRI_DMA_DP_TEST_ENDPOINT_BROADCAST1,

	ECPRI_DMA_DP_TEST_ENDPOINT_MAX,
};

/**
  * enum ecpri_dma_dp_test_suite_endp_route enumeration of endpoit routing
  */
enum ecpri_dma_dp_test_suite_endp_route {
	ECPRI_DMA_ENDP_ROUTE_TO_XBAR = 0,
	ECPRI_DMA_ENDP_ROUTE_TO_MEM = 1,
};

/**
  * enum ecpri_dma_dp_test_suite_endp_route
  * loopback enable/disable state
  */
enum ecpri_dma_dp_test_suite_endp_loopback_state {
	ECPRI_DMA_ENDP_XBAR_LOOPBACK_DISABLED = 0,
	ECPRI_DMA_ENDP_XBAR_LOOPBACK_ENABLED = 1,
	ECPRI_DMA_ENDP_XBAR_LOOPBACK_NOT_USED = 0,
};

/**
  * enum ecpri_dma_dp_test_suite_endp_route enumeration of
  * tx header nable/disable state
  */
enum ecpri_dma_dp_test_suite_endp_tx_header_state {
	ECPRI_DMA_ENDP_TX_HEADER_DISABLED = 0,
	ECPRI_DMA_ENDP_TX_HEADER_ENABLED = 1,
	ECPRI_DMA_ENDP_TX_HEADER_NOT_USED = 0,
};


/**
  * struct ecpri_dma_dp_test_suite_endp - Test endpoint descriptor
  *
  * @is_started:        true if this this endpoint was allocated and started
  * @dir                endpoint's direction
  * @id:                endpoint's id
  * @gsi_id:            GSI id to which the endpoint belgongs
  * @routing_config:    For source, selects between mem or xbar routing. Not used for dest
  * @default_endp_dest: For source, specifys default destination. Not used for dest
  * @is_xbar_loopback_used:  For source, enable/disable loopback. Not used for dest
  * @is_pre_header_used: For source, enable/disable tx header. Not used for dest
  * @irq_received:      IRQ synchonization mechanism
  * @num_of_tx_pkts:    number of sent packets for tx endpoint
  * @endp_ctx:          endpoint context
  * @rx_pkts:           array of packets for an rx endpoint
  * @rx_pkt_idx:        current packet index for rx endpoint
  */
struct ecpri_dma_dp_test_suite_endp {
	bool is_started;
	enum ecpri_dma_endp_dir dir;
	int id;
	int gsi_id;
	enum ecpri_dma_dp_test_suite_endp_route routing_config;
	enum ecpri_dma_dp_test_suite_endp_num default_endp_dest;
	bool is_xbar_loopback_used;
	bool is_pre_header_used;
	struct completion irq_received;
	u32 num_of_tx_pkts;
	struct ecpri_dma_endp_context *endp_ctx;
	struct ecpri_dma_pkt *rx_pkts[ECPRI_DMA_DP_TEST_NUM_OF_BUFFS_IN_RING];
	u32 rx_pkt_idx;
};

/**
  * struct ecpri_dma_dp_test_suite_context test context data structure
  */
struct ecpri_dma_dp_test_suite_context {
	struct ecpri_dma_dp_test_suite_endp
		endps[ECPRI_DMA_DP_TEST_ENDPOINT_MAX];
};

/* Test context */
struct ecpri_dma_dp_test_suite_context dp_test_suite_ctx;

/**
  * Finds a test endpoint with the given (id, gsi_id) pair
  *
  * @id: requested id
  * @gsi_id: requested gsi_id
  * @ret_num: [out] pointer to endpoint number
  *
  * Return: 0 - success, linux error code - failure
  */
static int ecpri_dma_dp_test_find_ep(int id, int gsi_id,
						  enum ecpri_dma_dp_test_suite_endp_num *ret_num) {

	enum ecpri_dma_dp_test_suite_endp_num i;

	for (i = 0; i < ECPRI_DMA_DP_TEST_ENDPOINT_MAX; i++) {

		if ((id == dp_test_suite_ctx.endps[i].id) &&
			(gsi_id == dp_test_suite_ctx.endps[i].gsi_id)) {
			break;
		}
	}

	if (i < ECPRI_DMA_DP_TEST_ENDPOINT_MAX) {
		*ret_num = i;
		return 0;
	} else {
		return -EINVAL;
	}
}

/**
  * ecpri_dma_dp_test_stuite_free_rx_packets_wrapper() -
  * Free the memory allocated for rx packets
  *
  * @num_of_packets: number of packets to free
  * @rx_pkts_array: packets array to free
  */
static void ecpri_dma_dp_test_stuite_free_rx_packets_wrapper(
	int num_of_packets,
	struct ecpri_dma_pkt_completion_wrapper **rx_pkts_array)
{
	int i;

	/* Check Rx array pointer */
	if (NULL == rx_pkts_array)
	{
		DMA_UT_LOG("NULL pointer passed to packet array\n");
		return;
	}

	/* Free packets */
	for (i = 0; i < num_of_packets; i++)
	{
		if (0 != rx_pkts_array[i])
		{
			kfree(rx_pkts_array[i]);
		}
	}

	kfree(rx_pkts_array);
}

/**
  * Allocate Rx packets wrappers
  *
  * @num_of_pkts: number of packets to alocate
  * @rx_pkts_ptr: pointer to packets
  *
  * Return: 0 - success, linux error code - failure
  */
static int ecpri_dma_dp_test_suite_allocate_rx_packets_wrapper(
	int num_of_pkts,
	struct ecpri_dma_pkt_completion_wrapper ***rx_pkts_ptr)
{
	struct ecpri_dma_pkt_completion_wrapper **rx_pkts;
	int i;

	/* Check pointer validity */
	if (NULL == rx_pkts_ptr)
	{
		DMA_UT_LOG("NULL pointer passed for packet array\n");
		return -EINVAL;
	}

	/* Allocate RX packet array */
	rx_pkts = kzalloc(sizeof(*rx_pkts) * num_of_pkts, GFP_KERNEL);

	if (!rx_pkts)
	{
		DMA_UT_LOG("failed to alloc Rx packets array\n");
		return -ENOMEM;
	}

	/* Allocate Rx packets */
	for (i = 0; i < num_of_pkts; i++)
	{
		rx_pkts[i] = kzalloc(sizeof(*rx_pkts[i]), GFP_KERNEL);

		/* Handle allocation failure */
		if (!rx_pkts[i])
		{
			DMA_UT_LOG("failed to alloc Rx packet\n");
			ecpri_dma_dp_test_stuite_free_rx_packets_wrapper(
				num_of_pkts,
				rx_pkts);

			return -ENOMEM;
		}
	}

	/* Assign return value */
	*rx_pkts_ptr = rx_pkts;

	return 0;
}

/**
  * Free allocated tx pakcets
  *
  * @num_of_packets: number of packets to free
  * @num_of_buffs: number of buffers per oackets
  * @tx_pkts: pointer to packets
  */
static void ecpri_dma_dp_test_stuite_free_tx_packets(
	int num_of_packets,
	int num_of_buffs,
	struct ecpri_dma_pkt **tx_pkts)
{
	int i;
	int j;

	/* Check Tx array pointer validity */
	if (NULL == tx_pkts){
		DMA_UT_LOG("NULL pointer passed for Tx packet array\n");
		return;
	}

	/* Iterate over each packet */
	for (i = 0; i < num_of_packets; i++){
		/* Verify buffers array have been allocated */
		if (NULL == tx_pkts[i]->buffs){
			continue;
		}

		/* Iterate over each buffer */
		for (j = 0; j < num_of_buffs; j++){
			if (NULL != tx_pkts[i]->buffs[j]){
				if (NULL != tx_pkts[i]->buffs[j]->virt_base){
					kfree(tx_pkts[i]->buffs[j]->virt_base);
				}

				kfree(tx_pkts[i]->buffs[j]);
			}
		}

		/* Free buffer array */
		kfree(tx_pkts[i]->buffs);
	}

	/* Free packets array */
	kfree(tx_pkts);
}

/**
  * Allocate tx packets
  *
  * @num_pkts: number of packets to allocate
  * @num_of_buffs: number of buffers per packet
  * @buffer_size: the size of each buffer
  * @ecpri_dma_pkt: pointer to packets
  * @tx_pkts_ptr: pointer to packets array
  *
  * Return: 0 - success, linux error code - failure
  */
static int ecpri_dma_dp_test_suite_allocate_tx_packets(
	int num_of_pkts,
	size_t num_of_buffs,
	size_t buffer_size,
	struct ecpri_dma_pkt ***tx_pkts_ptr) {

	u32 packet_content = ECPRI_DMA_DP_TEST_PACKET_CONTENT;
	struct ecpri_dma_pkt **tx_pkts;
	int i;
	int j;

	/* Check packet array pointer validity */
	if (NULL == tx_pkts_ptr) {
		DMA_UT_LOG("NULL pointer passed to Tx array\n");
		return -ENOMEM;
	}

	/* Check buffer number validity */
	if (num_of_buffs > ECPRI_DMA_DP_TEST_MAX_BUFFS) {
		DMA_UT_LOG("Requested number of buffers %d is greater than max %d\n",
			num_of_buffs, ECPRI_DMA_DP_TEST_MAX_BUFFS);

		return -ENOMEM;
	}

	/* Allocate Tx packets array */
	tx_pkts = kzalloc(sizeof(*tx_pkts) * num_of_pkts, GFP_KERNEL);

	if (!tx_pkts) {
		DMA_UT_LOG("failed to alloc Tx packets array \n");
		return -ENOMEM;
	}

	for (i = 0; i < num_of_pkts; i++) {
		/* Allocate packet */
		tx_pkts[i] = kzalloc(sizeof(*tx_pkts[i]), GFP_KERNEL);

		/* Handle packet allocation failure */
		if (NULL == tx_pkts[i])
		{
			DMA_UT_LOG("failed to alloc Tx packet\n");
			ecpri_dma_dp_test_stuite_free_tx_packets(
				num_of_pkts, num_of_buffs, tx_pkts);

			return -ENOMEM;
		}

		/* Allocate buffer array per packet */
		tx_pkts[i]->buffs =
			kzalloc(sizeof(tx_pkts[i]->buffs) * num_of_buffs, GFP_KERNEL);

		if (NULL == tx_pkts[i]->buffs)
		{
			DMA_UT_LOG("failed to alloc buffer array for a pakcet\n");
			ecpri_dma_dp_test_stuite_free_tx_packets(
				num_of_pkts, num_of_buffs, tx_pkts);
			return -ENOMEM;
		}

		/* Allocate buffers */
		for (j = 0; j < num_of_buffs; j++) {
			/* Allocate buffer wrapper */
			tx_pkts[i]->buffs[j] = kzalloc(
				sizeof(tx_pkts[i]->buffs[j]), GFP_KERNEL);

			if (!tx_pkts[i]->buffs[j]) {
				DMA_UT_LOG("failed to alloc dma buff wrapper\n");

				ecpri_dma_dp_test_stuite_free_tx_packets(
					num_of_pkts,
					num_of_buffs,
					tx_pkts);

				return -ENOMEM;
			}

			/* Allocate buffer memory */
			tx_pkts[i]->buffs[j]->virt_base =
				kzalloc(buffer_size, GFP_KERNEL);

			if (!tx_pkts[i]->buffs[j]->virt_base) {
				DMA_UT_LOG("failed to alloc buffer\n");

				ecpri_dma_dp_test_stuite_free_tx_packets(
					num_of_pkts,
					num_of_buffs,
					tx_pkts);

				return -ENOMEM;
			}

			tx_pkts[i]->buffs[j]->size = buffer_size;

			/* Write content */
			*(u32 *)tx_pkts[i]->buffs[j]->virt_base =
				packet_content++;
		}

		/* Update number of buffers */
		tx_pkts[i]->num_of_buffers = num_of_buffs;
	}

	*tx_pkts_ptr = tx_pkts;

	return 0;
}

/**
  * ecpri_dma_dp_test_buffers_array_allocate() -
  *  creates a packet array formated for
  * broadcasting the provided data
  *
  * @data_buf_num: number of buffer
  * @buf_size: buffer size
  * @data_bufs_array_ptr:  pointer to buffer array
  *
  * Return: 0 - success, linux error code - failure
  */
static int ecpri_dma_dp_test_buffers_array_allocate(
	size_t data_buf_num,
	size_t buf_size,
	struct ecpri_dma_mem_buffer ***data_bufs_array_ptr) {

	int buf_idx;
	struct ecpri_dma_mem_buffer **data_bufs_array;

	if (NULL == data_bufs_array_ptr) {
		DMA_UT_LOG("Error: NULL pointer argement for data buffers");
		return -ENOMEM;
	}

	/* Check buffer number validity */
	if (data_buf_num > ECPRI_DMA_DP_TEST_MAX_BUFFS) {
		DMA_UT_LOG("Requested number of buffers %d is greater than max %d\n",
				   data_buf_num, ECPRI_DMA_DP_TEST_MAX_BUFFS);

		return -ENOMEM;
	}

	/* Allocate buffer array */
	data_bufs_array =
		kzalloc(
			sizeof(struct ecpri_dma_mem_buffer *) * data_buf_num, GFP_KERNEL);

	/* Verify allocation */
	if (NULL == data_bufs_array) {

		DMA_UT_LOG("Error: data buffers array allocation failed");
		return -ENOMEM;
	}

	/* Allocate buffers */
	for (buf_idx = 0; buf_idx < data_buf_num; buf_idx++) {
		data_bufs_array[buf_idx] =
				kzalloc(sizeof(struct ecpri_dma_mem_buffer), GFP_KERNEL);
	}

	/* Allocate memory */
	for (buf_idx = 0; buf_idx < data_buf_num; buf_idx++) {
		data_bufs_array[buf_idx]->virt_base = kzalloc(buf_size, GFP_KERNEL);
		data_bufs_array[buf_idx]->size = buf_size;
	}

	*data_bufs_array_ptr = data_bufs_array;
	return 0;
}

/**
  * ecpri_dma_dp_test_buffers_array_free() - frees previously allocated buffer array
  *
  * @data_bufs_array: buffer array
  * @buf_num: number of buffers in the array
  *
  * Return: 0 - success, linux error code - failure
  */
static int ecpri_dma_dp_test_buffers_array_free(
 struct ecpri_dma_mem_buffer **data_bufs_array,
 size_t buf_num) {

	int i;

	/* Verify pointer */
	if (NULL == data_bufs_array) {
		DMA_UT_LOG("Error: NULL pointer argement for data buffers");
		return -EINVAL;
	}

	for (i = 0; i < buf_num; i++) {

		if (NULL != data_bufs_array[i]) {

			/* Free buffer pointed content */
			if (NULL != data_bufs_array[i]->virt_base) {
				kfree(data_bufs_array[i]->virt_base);
			}

			/* Free buffer */
			kfree(data_bufs_array[i]);
		}
	}

	/* Free array pointer */
	kfree(data_bufs_array);
	return 0;
}

/**
  * ecpri_dma_dp_test_create_broadcast_pkts_from_data() -
  * creates a packet array formated for broadcasting the provided data
  *
  * @data_bufs_array: array of data buffers to transmit.
  * @data_buf_num: number of data buffers.
  * @endps_array: array of destination endpoints
  * @endps_num: size of endpoints array
  * @tx_pkts_array_ptr: output parameter containing the packets
  *
  * The procedure creates a packet array where each packet recieves
  * a tx header redirecting the packet to one of the endpoints provided by
  * the caller and the packet's data buffers are assigned to point to the
  * provided data buffers.
  *
  * Return: 0 - success, linux error code - failure
  */
static int ecpri_dma_dp_test_create_broadcast_pkts_from_data(
	struct ecpri_dma_mem_buffer **data_bufs_array,
	size_t data_buf_num,
	struct ecpri_dma_dp_test_suite_endp **endps_array,
	size_t endps_num,
	struct ecpri_dma_pkt ***tx_pkts_array_ptr) {

	struct ecpri_dma_pkt **tx_pkts_array;
	size_t pkt_num = endps_num;
	int endp_idx;
	int buf_idx;
	int ret;

	/* Verify data buffers */
	if (NULL == data_bufs_array) {
		DMA_UT_LOG("Error: NULL pointer passed as data buffers");
		return -ENOMEM;
	}

	/* Verify endpoints array */
	if (NULL == endps_array) {
		DMA_UT_LOG("Error: NULL pointer passed as endpoints array");
		return -ENOMEM;
	}

	/* Verify return packets array */
	if (NULL == tx_pkts_array_ptr) {
		DMA_UT_LOG("Error: NULL pointer passed as returned packets array");
		return -ENOMEM;
	}

	/* Verify each endpoint has been intiialized */
	for (endp_idx = 0; endp_idx < endps_num; endp_idx++) {
		if (false == endps_array[endp_idx]->is_started) {
			DMA_UT_LOG("Error: Non initialized endpoint, passed to function");
			return -ENOMEM;
		}
	}

	/* ecpri_dma_dp_test_suite_allocate_tx_packets()- allocate packets array
		number of buffers: number of data buffers + 1 (tx header buffer)
		size of each buffer: 1. This is an arbitrray value,
		that will be replaced later in the code
	*/
	ret = ecpri_dma_dp_test_suite_allocate_tx_packets(
		endps_num,
		data_buf_num + NUM_OF_NON_DATA_BUFFS,
		1,
		&tx_pkts_array);

	if (0 != ret) {
		DMA_UT_LOG("Failed to allocate tx packets\n");
		return ret;
	}

	/* Free packet buffers memory content -
		it will be reassigned to the data buffers */
	for (endp_idx = 0 ; endp_idx < endps_num; endp_idx++) {
		for (buf_idx = 0 ; buf_idx < data_buf_num; buf_idx++) {
			kfree(tx_pkts_array[endp_idx]->buffs[buf_idx]->virt_base);
		}
	}

	/* Add tx header to each packet */
	for (endp_idx = 0; endp_idx < pkt_num; endp_idx++) {

		struct ecpri_dma_tx_header *tx_header_ptr;

		/* Allocate tx header*/
		tx_header_ptr = kzalloc(sizeof(struct ecpri_dma_tx_header), GFP_KERNEL);

		/* Verify allocation */
		if (NULL == tx_header_ptr) {

			ecpri_dma_dp_test_stuite_free_tx_packets(
				pkt_num,
				data_buf_num,
				tx_pkts_array);

			return -ENOMEM;
		}

		/* Set tx header values */
		tx_header_ptr->gsi_id = endps_array[endp_idx]->gsi_id;
		tx_header_ptr->destination_channel = endps_array[endp_idx]->id;

		/* Link tx header buffer to allocated memory*/
		tx_pkts_array[endp_idx]->buffs[0]->virt_base = tx_header_ptr;
		tx_pkts_array[endp_idx]->buffs[0]->size =
			sizeof(struct ecpri_dma_tx_header);
	}

	/* Point buffers to data */
	for (endp_idx = 0 ; endp_idx < endps_num; endp_idx++) {
		for (buf_idx = 0 ; buf_idx < data_buf_num; buf_idx++) {

			tx_pkts_array[endp_idx]->buffs[buf_idx + NUM_OF_NON_DATA_BUFFS]->virt_base =
				data_bufs_array[buf_idx]->virt_base;

			tx_pkts_array[endp_idx]->buffs[buf_idx + NUM_OF_NON_DATA_BUFFS]->size =
				data_bufs_array[buf_idx]->size;
		}
	}

	/* Point to return value */
	*tx_pkts_array_ptr = tx_pkts_array;

	return 0;
}

/**
  * ecpri_dma_dp_test_destroy_broadcast_pkts() -
  * 	destroys the packets created by
  * 	ecpri_dma_dp_test_create_broadcast_pkts_from_data()
  *
  * @tx_pkts_array: tx packets array.
  * @pkt_num: number of packets.
  * @buf_num: number of buffers
  *
  * Note: this doesn't free the payload
  */
void ecpri_dma_dp_test_destroy_broadcast_pkts(
	struct ecpri_dma_pkt **tx_pkts_array,
	size_t pkt_num,
	size_t buf_num) {

	int i;
	int j;
	size_t actual_buf_num;

	/* Check Tx array pointer validity */
	if (NULL == tx_pkts_array) {
		DMA_UT_LOG("NULL pointer passed for Tx packet array\n");
		return;
	}

	/* Sum of data buffers and non data (header) buffers */
	actual_buf_num = buf_num + NUM_OF_NON_DATA_BUFFS;

	/* Iterate over each packet */
	for (i = 0; i < pkt_num; i++){

		/* Verify buffers array have been allocated */
		if (NULL == tx_pkts_array[i]->buffs){
			continue;
		}

		/* Iterate over each buffer */
		for (j = 0; j < actual_buf_num; j++){
			if (NULL != tx_pkts_array[i]->buffs[j]){

				/* Destory memory allocated for the header buffer (0) */
				if ((0 == j) &&
					 (NULL != tx_pkts_array[i]->buffs[j]->virt_base)) {
					kfree(tx_pkts_array[i]->buffs[j]->virt_base);
				}

				kfree(tx_pkts_array[i]->buffs[j]);
			}
		}

		/* Free buffer array */
		kfree(tx_pkts_array[i]->buffs);
	}

	/* Free packets array */
	kfree(tx_pkts_array);
}

/**
  * ecpri_dma_dp_test_dump_packet() - print the contents of a packet
  *
  * @buf: packet's buffer
  * @len: packet's length
  */
static void ecpri_dma_dp_test_dump_packet(char *buf, int len) {

	int payload_len = len;
	int num_dumps;
	int i;
	int index = 0;

	DMA_UT_LOG("dumping buff of length: %d\n", len);

	if (payload_len > 0) {
		num_dumps = payload_len / 8;

		if (num_dumps > 8) {
			num_dumps = 8;
		}

		for (i = 0; i < num_dumps; ++i) {
			DMA_UT_LOG("buff: %d, %x:%x:%x:%x:%x:%x:%x:%x\n", i,
				buf[index + 0], buf[index + 1],
				buf[index + 2], buf[index + 3],
				buf[index + 4], buf[index + 5],
				buf[index + 6], buf[index + 7]);
			index += 8;
			if (index + 8 > len) {
				break;
			}
		}
	}
}

static int ecpri_dma_dp_test_setup_dma_endps(
	enum ecpri_dma_dp_test_suite_endp_num endpoint_num,
	bool enable_loopback) {

	int endp_id;
	int gsi_id;
	bool is_xbar_loopback_used;
	bool is_pre_header_used;
	ecpri_hwio_def_ecpri_endp_cfg_dest_gsi_m_ch_n_u endp_cfg_dest = {0};
	struct ecpri_dma_ecpri_endp_cfg_xbar_fields endp_cfg_xbar = {0};
	ecpri_hwio_def_ecpri_endp_gsi_cfg_gsi_m_ch_n_u endp_gsi_cfg = {0};
	ecpri_hwio_def_ecpri_endp_cfg_aggr_gsi_m_ch_n_u cfg_aggr = {0};
	ecpri_hwio_def_ecpri_endp_nfapi_reassembly_cfg_gsi_m_ch_n_u reassembly_cfg =
		{0};

	DMA_UT_DBG("!!Entering: ecpri_dma_dp_test_setup_dma_endps\n");

	/* Validate endpoint mapping pointer */
	if (!(*ecpri_dma_ctx->endp_map)) {
		DMA_UT_DBG("Error: endpoint map pointer is NULL\n");
		return -EINVAL;
	}

	/* Get endpoint's props */
	endp_id = dp_test_suite_ctx.endps[endpoint_num].id;
	gsi_id = dp_test_suite_ctx.endps[endpoint_num].gsi_id;
	is_xbar_loopback_used =
		dp_test_suite_ctx.endps[endpoint_num].is_xbar_loopback_used;
	is_pre_header_used =
		dp_test_suite_ctx.endps[endpoint_num].is_pre_header_used;

	/* Validate endpoint's map */
	if (!(*ecpri_dma_ctx->endp_map)[gsi_id][endp_id].valid ||
		(*ecpri_dma_ctx->endp_map)[gsi_id][endp_id].is_exception) {
			DMA_UT_DBG("Error: endpoint is not valid / has exception\n");
			return -EINVAL;
		}

	/* Configure test SRC ENDP to loopback into test DEST ENDP*/
	memset(&endp_cfg_dest, 0, sizeof(endp_cfg_dest));
	memset(&endp_cfg_xbar, 0, sizeof(endp_cfg_xbar));
	memset(&endp_gsi_cfg, 0, sizeof(endp_gsi_cfg));
	memset(&cfg_aggr, 0, sizeof(cfg_aggr));
	memset(&reassembly_cfg, 0, sizeof(reassembly_cfg));

	/* First disable ENDP*/
	ecpri_dma_hal_write_reg_mn(
		ECPRI_ENDP_GSI_CFG, gsi_id, endp_id, 0);

	if (enable_loopback) {
		switch ((*ecpri_dma_ctx->endp_map)[gsi_id][endp_id].dir) {
		case ECPRI_DMA_ENDP_DIR_SRC:

			/* Configure endpoint's routing */

			if (is_xbar_loopback_used)
				endp_cfg_dest.def.use_dest_cfg = ECPRI_DMA_ENDP_ROUTE_TO_XBAR;
			else
				endp_cfg_dest.def.use_dest_cfg = ECPRI_DMA_ENDP_ROUTE_TO_MEM;

			/* Set XBAR loopback mode */
			endp_cfg_xbar.loopback_en = is_xbar_loopback_used;

			/* Set pre header mode */
			endp_cfg_xbar.pre_hdr_en = is_pre_header_used;

			/* Set default destinaion */
			endp_cfg_dest.def.dest_mem_channel = ECPRI_DMA_DP_UT_DEST_ENDP_ID;

			ecpri_dma_hal_write_reg_mn(
				ECPRI_ENDP_CFG_DEST, gsi_id, endp_id,
									   endp_cfg_dest.value);

			ecpri_dma_hal_write_reg_mn_fields(
				ECPRI_ENDP_CFG_XBAR, gsi_id, endp_id,
				&endp_cfg_xbar);
			break;
		case ECPRI_DMA_ENDP_DIR_DEST:
			ecpri_dma_hal_write_reg_mn(
				ECPRI_ENDP_CFG_AGGR, gsi_id,
				endp_id, cfg_aggr.value);
			ecpri_dma_hal_write_reg_mn(
				ECPRI_ENDP_NFAPI_REASSEMBLY_CFG, gsi_id,
				endp_id, reassembly_cfg.value);
			break;
		default:
			DMAERR("ENDP isn't SRC nor DEST\n");
			return -EINVAL;
			break;
		}
	}
	else {
		switch ((*ecpri_dma_ctx->endp_map)[gsi_id][endp_id].dir) {
		case ECPRI_DMA_ENDP_DIR_SRC:
			switch ((*ecpri_dma_ctx->endp_map)[gsi_id][endp_id].stream_mode) {
			case ECPRI_DMA_ENDP_STREAM_MODE_M2M:
				endp_cfg_dest.def.use_dest_cfg = 1;
				endp_cfg_dest.def.dest_mem_channel =
					(*ecpri_dma_ctx->endp_map)[gsi_id][endp_id].dest;
				ecpri_dma_hal_write_reg_mn(
					ECPRI_ENDP_CFG_DEST, gsi_id, endp_id,
					endp_cfg_dest.value);
				break;
			case ECPRI_DMA_ENDP_STREAM_MODE_M2S:
				endp_cfg_dest.def.use_dest_cfg = 0;
				endp_cfg_xbar.dest_stream =
					(*ecpri_dma_ctx->endp_map)[gsi_id][endp_id].dest;
				endp_cfg_xbar.xbar_tid =
					(*ecpri_dma_ctx->endp_map)[gsi_id][endp_id].tid.value;
				//TODO: Below are required for nFAPI
				//endp_cfg_xbar.xbar_user = Get from Core driver, need API
				endp_cfg_xbar.l2_segmentation_en =
					(*ecpri_dma_ctx->endp_map)[gsi_id][endp_id].is_nfapi ? 1 : 0;
				ecpri_dma_hal_write_reg_mn(
					ECPRI_ENDP_CFG_DEST, gsi_id, endp_id,
					endp_cfg_dest.value);
				ecpri_dma_hal_write_reg_mn_fields(
					ECPRI_ENDP_CFG_XBAR, gsi_id, endp_id,
					&endp_cfg_xbar);
				break;
			default:
				DMAERR("SRC ENDP %d, GSI ID %d isn't M2M or M2S,"
					"address = 0x%px\n", endp_id, gsi_id,
					&(*ecpri_dma_ctx->endp_map)[gsi_id][endp_id]);
				return -EINVAL;
				break;
			}
			break;
		case ECPRI_DMA_ENDP_DIR_DEST:
			switch ((*ecpri_dma_ctx->endp_map)[gsi_id][endp_id].stream_mode) {
			case ECPRI_DMA_ENDP_STREAM_MODE_M2M:
				break;
			case ECPRI_DMA_ENDP_STREAM_MODE_S2M:
				if ((*ecpri_dma_ctx->endp_map)[gsi_id][endp_id].is_nfapi) {
					memset(&cfg_aggr, 0,
						sizeof(cfg_aggr));
					memset(&reassembly_cfg, 0,
						sizeof(reassembly_cfg));
					cfg_aggr.def.aggr_type = 1;
					reassembly_cfg.def.vm_id =
						(*ecpri_dma_ctx->endp_map)[gsi_id][endp_id]
						.nfapi_dest_vm_id;
					ecpri_dma_hal_write_reg_n(
						ECPRI_ENDP_CFG_AGGR,
						endp_id, cfg_aggr.value);
					ecpri_dma_hal_write_reg_n(
						ECPRI_ENDP_NFAPI_REASSEMBLY_CFG,
						endp_id, reassembly_cfg.value);
				}
				break;
			default:
				DMAERR("DEST ENDP %d, GSI ID %d isn't M2M or S2M,"
					"address = 0x%px\n", endp_id, gsi_id,
					&(*ecpri_dma_ctx->endp_map)[gsi_id][endp_id]);
				return -EINVAL;
				break;
			}
			break;
		default:
			DMAERR("ENDP isn't SRC nor DEST\n");
			return -EINVAL;
			break;
			}
	}

	/* Re-enable ENDP*/
	ecpri_dma_hal_write_reg_mn(
		ECPRI_ENDP_GSI_CFG, gsi_id, endp_id, 1);

	return 0;
}

int ecpri_dma_dp_test_rx_replenish(struct ecpri_dma_endp_context *endp,
	u32 num_to_replenish)
{
	int ret = 0;
	int rem_to_repelnish = num_to_replenish;
	int first_batch = 0;
	u32 first_idx;
	u32 *i;
	enum ecpri_dma_dp_test_suite_endp_num endpoint_num;
	struct ecpri_dma_dp_test_suite_endp *endpoint_ptr;

	if (!endp || !endp->valid || endp->gsi_ep_cfg->is_exception) {
		DMA_UT_LOG("Test DEST ENDP isn't valid or is defined as exception");
		return -EINVAL;
	}

	/* Find endpoint */
	ret =
		ecpri_dma_dp_test_find_ep(endp->endp_id, endp->gsi_id, &endpoint_num);

	/* Verify found */
	if (0 != ret) {
		DMA_UT_LOG("Failed to find test endpoint for the provided context\n");
		return ret;
	}

	/* Point to endpoint */
	endpoint_ptr = &dp_test_suite_ctx.endps[endpoint_num];

	i = &endpoint_ptr->rx_pkt_idx;
	first_idx = *i;

	while (rem_to_repelnish) {
		endpoint_ptr->rx_pkts[*i] =
			kzalloc(sizeof(*endpoint_ptr->rx_pkts[*i]), GFP_KERNEL);
		if (!endpoint_ptr->rx_pkts[*i]) {
			DMA_UT_LOG("failed to alloc packet\n");
			ret = -ENOMEM;
			goto fail_alloc;
		}

		endpoint_ptr->rx_pkts[*i]->buffs =
			kzalloc(sizeof(*endpoint_ptr->rx_pkts[*i]->buffs), GFP_KERNEL);
		if (!endpoint_ptr->rx_pkts[*i]->buffs) {
			DMA_UT_LOG("failed to alloc dma buff wrapper\n");
			kfree(endpoint_ptr->rx_pkts[*i]);
			ret = -ENOMEM;
			goto fail_alloc;
		}

		endpoint_ptr->rx_pkts[*i]->buffs[0] =
			kzalloc(sizeof(*endpoint_ptr->rx_pkts[*i]->buffs[0]), GFP_KERNEL);
		if (!endpoint_ptr->rx_pkts[*i]->buffs[0]) {
			DMA_UT_LOG("failed to alloc dma buff wrapper\n");
			kfree(endpoint_ptr->rx_pkts[*i]->buffs);
			kfree(endpoint_ptr->rx_pkts[*i]);
			ret = -ENOMEM;
			goto fail_alloc;
		}
		endpoint_ptr->rx_pkts[*i]->num_of_buffers = 1;

		endpoint_ptr->rx_pkts[*i]->buffs[0]->virt_base =
			kzalloc(ECPRI_DMA_DP_TEST_BUFF_SIZE, GFP_KERNEL);
		if (!endpoint_ptr->rx_pkts[*i]->buffs[0]->virt_base) {
			DMA_UT_LOG("failed to alloc buffer\n");
			kfree(endpoint_ptr->rx_pkts[*i]->buffs[0]);
			kfree(endpoint_ptr->rx_pkts[*i]->buffs);
			kfree(endpoint_ptr->rx_pkts[*i]);
			ret = -ENOMEM;
			goto fail_alloc;
		}

		endpoint_ptr->rx_pkts[*i]->buffs[0]->size =
			ECPRI_DMA_DP_TEST_BUFF_SIZE;

		*i = (*i + 1) % (ECPRI_DMA_DP_TEST_NUM_OF_BUFFS_IN_RING);
		rem_to_repelnish--;
	}

	if (first_idx + num_to_replenish > ECPRI_DMA_DP_TEST_NUM_OF_BUFFS_IN_RING)
	{
		/* Handle array wrap around */
		first_batch = ECPRI_DMA_DP_TEST_NUM_OF_BUFFS_IN_RING - first_idx;
		rem_to_repelnish = num_to_replenish - first_batch;
		ret = ecpri_dma_dp_transmit(endp, &endpoint_ptr->rx_pkts[first_idx],
			first_batch, true);
		if (ret) {
			DMA_UT_LOG("failed to replenish Rx endp\n");
			goto fail_alloc;
		}

		ret = ecpri_dma_dp_transmit(endp, &endpoint_ptr->rx_pkts[0],
			rem_to_repelnish, true);
		if (ret) {
			DMA_UT_LOG("failed to replenish Rx endp\n");
			goto fail_alloc;
		}
	}
	else
	{
		/* No need to handle wrap around*/
		ret = ecpri_dma_dp_transmit(endp, &endpoint_ptr->rx_pkts[first_idx],
			num_to_replenish, true);
		if (ret) {
			DMA_UT_LOG("failed to replenish Rx endp\n");
			goto fail_alloc;
		}
	}

	return 0;

fail_alloc:
	/* An allocation failed, free memory backwards */
	while (rem_to_repelnish < num_to_replenish) {
		*i = (*i - 1) % ECPRI_DMA_DP_TEST_RING_LEN;
		kfree(endpoint_ptr->rx_pkts[*i]->buffs[0]->virt_base);
		kfree(endpoint_ptr->rx_pkts[*i]->buffs[0]);
		kfree(endpoint_ptr->rx_pkts[*i]->buffs);
		kfree(endpoint_ptr->rx_pkts[*i]);
		rem_to_repelnish++;
	}

	return ret;
}

static void ecpri_dma_dp_test_rx_client_notify_comp(
	struct ecpri_dma_endp_context *endp,
	struct ecpri_dma_pkt_completion_wrapper **comp_pkt,
	u32 num_of_completed)
{
	int ret = 0;
	enum ecpri_dma_notify_mode mode;
	enum ecpri_dma_dp_test_suite_endp_num endpoint_num;

	if (!endp || !endp->valid) {
		DMA_UT_LOG("Rx Test ENDP is not valid\n");
	}

	ret = ecpri_dma_get_endp_mode(endp, &mode);
	if (ret) {
		DMA_UT_LOG("Failed to get current Rx test ENDP mode\n");
	}

	/* Find endpoint */
	ret =
		ecpri_dma_dp_test_find_ep(endp->endp_id, endp->gsi_id, &endpoint_num);

	if (0 != ret) {
		DMA_UT_LOG("Failed to find test endpoint for the provided context\n");
		return;
	}

	DMA_UT_LOG("RX notify endpoint %d\n", endpoint_num);

	/* Signal completion to endpoint */
	complete(&dp_test_suite_ctx.endps[endpoint_num].irq_received);
}

static void ecpri_dma_dp_test_tx_client_notify_comp(
	struct ecpri_dma_endp_context *endp,
	struct ecpri_dma_pkt_completion_wrapper **comp_pkt, u32 num_of_completed) {

	enum ecpri_dma_dp_test_suite_endp_num endpoint_num;
	int ret;

	if (!endp || !endp->valid) {
		DMA_UT_LOG("Tx Test ENDP is not valid\n");
	}

	/* Find endpoint */
	ret =
		ecpri_dma_dp_test_find_ep(endp->endp_id, endp->gsi_id, &endpoint_num);

	if (0 != ret) {
		DMA_UT_LOG("Failed to find test endpoint for the provided context\n");
		return;
	}


	DMA_UT_LOG("TX notify endpoint %d\n", endpoint_num);

	/* Increase number of received packets */
	dp_test_suite_ctx.endps[endpoint_num].num_of_tx_pkts +=
		num_of_completed;

	/* Signal completion to endpoint */
	complete(&dp_test_suite_ctx.endps[endpoint_num].irq_received);
}

/**
  * ecpri_dma_dp_test_alloc_and_start_endp()-
  * Configures and allocates an endpoint
  *
  * @endpoint_num: the index of the endpoint to configure
  *
  * Return: 0 - success, linux error code - failure
  */
static int ecpri_dma_dp_test_alloc_and_start_endp(
	enum ecpri_dma_dp_test_suite_endp_num endpoint_num) {

	struct ecpri_dma_dp_test_suite_endp *endp_ptr;
	struct ecpri_dma_moderation_config mod_cfg = {0, 0};
	struct ecpri_dma_ecpri_endp_alloc_params endp_params = {0};

	int ret = 0;

	client_notify_comp notify;

	/* Assign pointer to the endpoint */
	endp_ptr = &dp_test_suite_ctx.endps[endpoint_num];

	/* Choose transfer complete function*/
	if (ECPRI_DMA_ENDP_DIR_SRC == endp_ptr->dir) {
		notify = &ecpri_dma_dp_test_tx_client_notify_comp;
	} else {
		notify = &ecpri_dma_dp_test_rx_client_notify_comp;
	}

	/* Get pointer to context */
	endp_ptr->endp_ctx =
	 &ecpri_dma_ctx->endp_ctx[endp_ptr->gsi_id][endp_ptr->id];

	/* Configure endpoint */
	mod_cfg.moderation_counter_threshold =
		ECPRI_DMA_DP_TEST_ENDP_MODC;
	mod_cfg.moderation_timer_threshold =
		ECPRI_DMA_DP_TEST_ENDP_MODT;


	endp_params.gsi_id = endp_ptr->gsi_id;
	endp_params.endp_id =  endp_ptr->id;
	endp_params.ring_length = ECPRI_DMA_DP_TEST_RING_LEN;
	endp_params.mod_cfg = &mod_cfg;
	endp_params.is_over_pcie = false;
	endp_params.notify_comp = notify;
	endp_params.enable_tx_poll = false;
	endp_params.cb_to_use = ECPRI_DMA_SMMU_CB_ETH ;

	ret = ecpri_dma_alloc_endp(&endp_params);

	if (ret) {
		DMA_UT_LOG("Failed to allocte test ENDP id: %d  gsi_id: %d\n",
				   endp_ptr->id, endp_ptr->gsi_id);

		goto fail_gen;
	}

	ret = ecpri_dma_start_endp(endp_ptr->endp_ctx);
	if (ret) {
		DMA_UT_LOG("Failed to start test ENDP id: %d  gsi_id: %d\n",
			endp_ptr->id,
			endp_ptr->gsi_id);

		goto fail_start;
	}

	if (ECPRI_DMA_GET_CTX_HW_VER() != ECPRI_HW_V1_0) {
		/* Fill ring with credtis */
		if (ECPRI_DMA_ENDP_DIR_DEST == endp_ptr->dir) {
			ret = ecpri_dma_dp_test_rx_replenish(endp_ptr->endp_ctx,
						endp_ptr->endp_ctx->ring_length - 1);
			if (ret) {
				DMA_UT_LOG("Failed to replenish test Rx endp\n");
				goto fail_replenish;
			}
		}
	}

	return 0;

fail_replenish:
	ecpri_dma_stop_endp(endp_ptr->endp_ctx);
fail_start:
	ecpri_dma_dealloc_endp(endp_ptr->endp_ctx);
fail_gen:
	return ret;
}

/**
  * ecpri_dma_dp_test_destroy_endp()-
  * Destroies the endpoint
  *
  * @endpoint_num: the index of the endpoint to configure
  *
  * Return: 0 - success, linux error code - failure
  */
static int ecpri_dma_dp_test_destroy_endp(
	enum ecpri_dma_dp_test_suite_endp_num endpoint_num) {
	int i;
	int ret = 0;
	int endp_id;
	int gsi_id = ECPRI_DMA_DP_UT_GSI_ID;

	struct ecpri_dma_endp_context *endp_cfg = NULL;
	struct ecpri_dma_dp_test_suite_endp *endpoint_ptr;

	/* Point to the endpoint */
	endpoint_ptr = &dp_test_suite_ctx.endps[endpoint_num];

	/* Verify endpoint is started */
	if (false == endpoint_ptr->is_started) {
		return 0;
	}

	/* Assign endpoint fields  */
	endp_cfg = endpoint_ptr->endp_ctx;
	endp_id = endpoint_ptr->id;
	gsi_id = endpoint_ptr->gsi_id;

	if (NULL == endp_cfg) {
		DMA_UT_LOG("Stop ENDP %d, GSI ID %d failed with code %d\n", endp_id,
				   gsi_id, ret);
		return -EINVAL;
	}

	ret = ecpri_dma_stop_endp(endp_cfg);
	if (ret != GSI_STATUS_SUCCESS)
	{
		DMA_UT_LOG("Stop ENDP %d, GSI ID %d failed with code %d\n",
			endp_id, gsi_id, ret);
		return ret;
	}

	ret = ecpri_dma_reset_endp(endp_cfg);
	if (ret != GSI_STATUS_SUCCESS)
	{
		DMA_UT_LOG("Reset ENDP %d, GSI ID %d failed with code %d\n",
			endp_id, gsi_id, ret);
		return ret;
	}

	ret = ecpri_dma_dealloc_endp(endp_cfg);
	if (ret != GSI_STATUS_SUCCESS) {
		DMA_UT_LOG("Dealloc ENDP %d, GSI ID %d failed with code %d\n", endp_id,
				   gsi_id, ret);
	}

	ret = ecpri_dma_dp_test_setup_dma_endps(endpoint_num, false);
	if (ret != GSI_STATUS_SUCCESS) {
		DMA_UT_LOG("Disable loopback ENDP %d, GSI ID %d failed with code %d\n",
				   endp_id, gsi_id, ret);
	}

	if (ECPRI_DMA_GET_CTX_HW_VER() != ECPRI_HW_V1_0)
	{
		for (i = 0; i < ECPRI_DMA_DP_TEST_NUM_OF_BUFFS_IN_RING; i++)
		{
			/* Verify pointers */
			if ((NULL == endpoint_ptr->rx_pkts[i]) ||
				(NULL == endpoint_ptr->rx_pkts[i]->buffs) ||
				(NULL == endpoint_ptr->rx_pkts[i]->buffs[0]) ||
				(NULL == endpoint_ptr->rx_pkts[i]->buffs[0]->virt_base)) {
				DMA_UT_LOG("Warning: rx_pkts or some of it isn't allocated\n");
				continue;
			}

			kfree(endpoint_ptr->rx_pkts[i]->buffs[0]->virt_base);
			kfree(endpoint_ptr->rx_pkts[i]->buffs[0]);
			kfree(endpoint_ptr->rx_pkts[i]->buffs);
			kfree(endpoint_ptr->rx_pkts[i]);
		}
	}

	/* Clear endpoint data */
	memset(endpoint_ptr, 0, sizeof(*endpoint_ptr));

	return 0;
}

/**
  * ecpri_dma_dp_test_create_endp() -
  * configre and allocate the required endpoint
  *
  * @endpoint_num:      the endpoint to configure
  * @id:                requsted endpoint's id
  * @gsi_id:            requsted endpoint' gsi_id
  * @dir:               endpoint's direction
  * @is_xbar_loopback_used:  loopback enable for a source ep
  * @is_pre_header_used: tx header enable for source ep
  * @loopback:          configure the endpoint in loopback mode
  *
  * Return: 0 - success, linux error code - failure
  */
static int ecpri_dma_dp_test_create_endp(
	enum ecpri_dma_dp_test_suite_endp_num endpoint_num,
	int id,
	int gsi_id,
	enum ecpri_dma_endp_dir dir,
	bool is_xbar_loopback_used,
	bool is_pre_header_used,
	bool loopback)
{
	int ret;

	DMA_UT_DBG("!!Entering: ecpri_dma_dp_test_create_endp,"
				"id: %d\n"
				"gsi_id: %d\n"
				"dir: %d\n"
				"loopback enable: %d\n"
				"tx header enable: %d\n"
				"loopback param: %d\n",
				id,
				gsi_id,
				dir,
				is_xbar_loopback_used,
				is_pre_header_used,loopback);

	/* Destroy if the EP is already started  */
	if (true == dp_test_suite_ctx.endps[endpoint_num].is_started) {
		ecpri_dma_dp_test_destroy_endp(endpoint_num);
		dp_test_suite_ctx.endps[endpoint_num].is_started = false;
	}

	/* Update endpoint configuration parameters */
	dp_test_suite_ctx.endps[endpoint_num].dir = dir;
	dp_test_suite_ctx.endps[endpoint_num].id = id;
	dp_test_suite_ctx.endps[endpoint_num].gsi_id = gsi_id;
	dp_test_suite_ctx.endps[endpoint_num].is_xbar_loopback_used =
		is_xbar_loopback_used;
	dp_test_suite_ctx.endps[endpoint_num].is_pre_header_used =
		is_pre_header_used;

	/* Configure the endpoint */
	ret = ecpri_dma_dp_test_setup_dma_endps(endpoint_num, loopback);
	if (0 != ret) {
		return ret;
	}

	/* Allocate the endpoint */
	ret = ecpri_dma_dp_test_alloc_and_start_endp(endpoint_num);
	if (ret) {
		return ret;
	}

	/* Initalize complition mechanism */
	init_completion(&dp_test_suite_ctx.endps[endpoint_num].irq_received);

	/* Mark as started */
	dp_test_suite_ctx.endps[endpoint_num].is_started = true;

	return 0;
}

static int ecpri_dma_dp_test_suite_setup(void **ppriv) {

	int ret = 0;

	DMA_UT_DBG("!!Enter: ecpri_dma_dp_test_suite_setup\n");

	/* Clear test's context */
	memset(&dp_test_suite_ctx, 0, sizeof(dp_test_suite_ctx));

	/* Setup source endpoint*/
	ret = ecpri_dma_dp_test_create_endp(
		ECPRI_DMA_DP_TEST_ENDPOINT_DEFAULT_SRC,
		ECPRI_DMA_DP_UT_SRC_ENDP_ID,
		ECPRI_DMA_DP_UT_SRC_ENDP_GSI_ID,
		ECPRI_DMA_ENDP_DIR_SRC,
		ECPRI_DMA_ENDP_XBAR_LOOPBACK_DISABLED,
		ECPRI_DMA_ENDP_TX_HEADER_DISABLED,
		true);

	if (0 != ret) {
		return ret;
	}

	/* Destination endpoint */
	ret = ecpri_dma_dp_test_create_endp(
		ECPRI_DMA_DP_TEST_ENDPOINT_DEFAULT_DEST,
		ECPRI_DMA_DP_UT_DEST_ENDP_ID,
		ECPRI_DMA_DP_UT_DEST_ENDP_GSI_ID,
		ECPRI_DMA_ENDP_DIR_DEST,
		ECPRI_DMA_ENDP_XBAR_LOOPBACK_NOT_USED,
		ECPRI_DMA_ENDP_TX_HEADER_NOT_USED,
		true);

	if (0 != ret) {
		return ret;
	}

	return ret;
}

/**
  * ecpri_dma_dp_test_suite_teardown()-
  * Destoies the test suite
  *
  * @priv:
  *
  * Return: 0 - success, Linux error - failure
  */
static int ecpri_dma_dp_test_suite_teardown(void *priv) {
	int i = 0;

	DMA_UT_DBG("!!Enter: ecpri_dma_dp_test_suite_teardown\n");

	for (i = 0; i < ECPRI_DMA_DP_TEST_ENDPOINT_MAX; i++)
		if (true == dp_test_suite_ctx.endps[i].is_started)
			ecpri_dma_dp_test_destroy_endp(i);

	return 0;
}
/**
  * ecpri_dma_dp_test_suite_prepare_test_data()-
  * Allcoates test memory
  *
  * @num_of_pkts: number of packets
  * @single_buffer: chooses between single on multiple buffer
  * @tx_pkts_ptr: pointer to tx packets array
  * @rx_pkts_ptr: pointer to rx packet wrappers array
  *
  * Return: 0 - success, Linux error - failure
  */
static int ecpri_dma_dp_test_suite_prepare_test_data(
	int num_of_pkts, bool single_buffer, struct ecpri_dma_pkt ***tx_pkts_ptr,
	struct ecpri_dma_pkt_completion_wrapper ***rx_pkts_ptr)
{
	int num_of_buffs = single_buffer ? 1 : ECPRI_DMA_DP_TEST_MAX_BUFFS;
	int buffer_size = ECPRI_DMA_DP_TEST_TX_BUFF_SIZE;
	int res;

	res =  ecpri_dma_dp_test_suite_allocate_tx_packets(
		num_of_pkts,
		num_of_buffs,
		buffer_size,
		tx_pkts_ptr);

	if (0 != res) {
		DMA_UT_LOG("failed to alloc Tx packets array \n");
		return -ENOMEM;
	}

	res = ecpri_dma_dp_test_suite_allocate_rx_packets_wrapper(
		num_of_pkts, rx_pkts_ptr);

	if (0 != res) {
		DMA_UT_LOG("failed to alloc Rx packets array \n");
		return -ENOMEM;
	}

	return 0;
}

/**
  * ecpri_dma_dp_test_suite_destroy_test_data() -
  * free memory allocated by ecpri_dma_dp_test_suite_prepare_test_data()
  *
  * @num_of_pkts: number of packets
  * @single_buffer: single/multiple buffers
  * @tx_pkts_array: tx packet array
  * @rx_wrapper_array: rx packet wrapper array
  *
  * Return: 0 - success, Linux error - failure
  */
static void ecpri_dma_dp_test_suite_destroy_test_data(
	int num_of_pkts, bool single_buffer, struct ecpri_dma_pkt **tx_pkts_array,
	struct ecpri_dma_pkt_completion_wrapper **rx_wrapper_array) {

	int num_of_buffs = single_buffer ? 1 : ECPRI_DMA_DP_TEST_MAX_BUFFS;

	ecpri_dma_dp_test_stuite_free_rx_packets_wrapper(
		num_of_pkts,
		rx_wrapper_array);

	ecpri_dma_dp_test_stuite_free_tx_packets(
		num_of_pkts,
		num_of_buffs,
		tx_pkts_array);
}

/**
  * ecpri_dma_dp_test_suite_wait_for_tx_comp()-
  * Waits until the given number of packets transactions
  * are registered for the endpoint
  *
  * @endpoint_num: the quireid endpoint
  * @comp_number: number of completions to wait for
  *
  * Return: 0 - success, -EFAULT otherwise
  */
static int ecpri_dma_dp_test_suite_wait_for_tx_comp(
	enum ecpri_dma_dp_test_suite_endp_num endpoint_num, u32 comp_number) {

	int res = 0;

	while (dp_test_suite_ctx.endps[
			endpoint_num].num_of_tx_pkts < comp_number) {

		/* Wait for transaction end */
		res = wait_for_completion_timeout(
			&dp_test_suite_ctx.endps[endpoint_num].irq_received,
			msecs_to_jiffies(10000));

		/* Check for timeout */
		if (0 == res) {
			DMA_UT_LOG(
			"Timeout while waiting for tx" \
			"complete endp: %d, completion number%d",
			endpoint_num,
			comp_number);

			return -EFAULT;
		}
	}

	return 0;
}

/**
  * ecpri_dma_dp_test_suite_wait_for_irq() -
  * waits for an endpoint to recieve an IRQ
  *
  * @endpoint_num: the quireid endpoint
  *
  * Return: 0 - success, -EFAULT otherwise
  */
static int ecpri_dma_dp_test_suite_wait_for_irq(
	enum ecpri_dma_dp_test_suite_endp_num endpoint_num) {

	int res = 0;

	/* Wait for IRQ */
	res = wait_for_completion_timeout(
		&dp_test_suite_ctx.endps[endpoint_num].irq_received,
		msecs_to_jiffies(10000));


	/* Check for timeout */
	if (0 == res) {
		DMA_UT_LOG("Timeout while waiting for IRQ endp: %d", endpoint_num);
		return -EFAULT;
		}

	return 0;
}

static int ecpri_dma_dp_test_suite_verify_rx(
	bool expecting_irq, u32 num_of_pkts_sent, struct ecpri_dma_pkt** tx_pkts,
	struct ecpri_dma_pkt_completion_wrapper** rx_pkts,
	int* total_rx_buffs_to_replenish)
{
	int res = 0;
	int actual_num = 0, actual_buff_num = 0;
	int sent_pkt_idx = 0, sent_pkt_buff_idx = 0;
	int i = 0;
	int curr_pkt_recv_size = 0;
	unsigned long tx_buff_size = 0;
	void* tx_buff_to_compare = NULL;
	void* rx_buff_to_compare = NULL;
	struct ecpri_dma_endp_context* rx_endp = NULL;

	rx_endp = &ecpri_dma_ctx->
		endp_ctx[ECPRI_DMA_DP_UT_GSI_ID][ECPRI_DMA_DP_UT_DEST_ENDP_ID];

	*total_rx_buffs_to_replenish = 0;

	if (expecting_irq)
	{
		/* Wait for transaction end */
		res = wait_for_completion_timeout(
			&dp_test_suite_ctx.endps[
				ECPRI_DMA_DP_TEST_ENDPOINT_DEFAULT_DEST].irq_received,
			msecs_to_jiffies(10000));

		if (0 == res) {
			DMA_UT_LOG("Test failed due to Rx timeout");
			return -EFAULT;
		}
	}

	while (sent_pkt_idx != num_of_pkts_sent) {
		actual_num = 0;

		/* actual_num is in packets, need to check for jumbo packets */
		res = ecpri_dma_dp_poll(rx_endp, ECPRI_DMA_DP_TEST_RX_BUDGET,
			rx_pkts, &actual_num);
		if (res || !actual_num) {
			DMA_UT_LOG("Test failed to perform rx poll, res = %d, actual = %d",
				res, actual_num);
			return -EFAULT;
		}

		tx_buff_to_compare =
			tx_pkts[sent_pkt_idx]->buffs[sent_pkt_buff_idx]->virt_base;
		tx_buff_size = tx_pkts[sent_pkt_idx]->buffs[sent_pkt_buff_idx]->size;
		i = 0;
		actual_buff_num = 0;
		while (i < actual_num) {
			curr_pkt_recv_size = rx_pkts[actual_buff_num]->pkt->buffs[0]->size;

			if (rx_pkts[actual_buff_num]->comp_code !=
				ECPRI_DMA_COMPLETION_CODE_EOT)
			{
				/* Over flow event */
				if (memcmp(
					tx_buff_to_compare,
					rx_pkts[actual_buff_num]->pkt->buffs[0]->virt_base,
					curr_pkt_recv_size)) {
					DMA_UT_LOG(
						"Test failed due to buffers don't match i= %d\n",i);
					DMA_UT_LOG("tx buff:\n");
						ecpri_dma_dp_test_dump_packet(tx_buff_to_compare,
							curr_pkt_recv_size);
					DMA_UT_LOG("rx buff:\n");
						ecpri_dma_dp_test_dump_packet(
							rx_pkts[actual_buff_num]->pkt->buffs[0]->virt_base,
							curr_pkt_recv_size);
					return -EFAULT;
				}
				tx_buff_to_compare =
					(void*)((unsigned long)tx_buff_to_compare +
						rx_pkts[actual_buff_num]->pkt->buffs[0]->size);
				tx_buff_size -= ECPRI_DMA_DP_TEST_BUFF_SIZE;
			}
			else if (curr_pkt_recv_size == tx_buff_size)
			{
				/* Buffers context matches and Tx EOT */
				if (memcmp(
					tx_buff_to_compare,
					rx_pkts[actual_buff_num]->pkt->buffs[0]->virt_base,
					curr_pkt_recv_size)) {
					DMA_UT_LOG(
						"Test failed due to buffers don't match i= %d\n",i);
					DMA_UT_LOG("tx buff:\n");
						ecpri_dma_dp_test_dump_packet(tx_buff_to_compare,
							curr_pkt_recv_size);
					DMA_UT_LOG("rx buff:\n");
						ecpri_dma_dp_test_dump_packet(
							rx_pkts[actual_buff_num]->pkt->buffs[0]->virt_base,
							curr_pkt_recv_size);
					return -EFAULT;
				}
				sent_pkt_buff_idx++;
				if (sent_pkt_buff_idx == tx_pkts[sent_pkt_idx]->num_of_buffers)
				{
					sent_pkt_buff_idx = 0;
					sent_pkt_idx++;
					if (num_of_pkts_sent == sent_pkt_idx)
					{
						kfree(rx_pkts[actual_buff_num]->pkt->buffs[0]->virt_base);
						kfree(rx_pkts[actual_buff_num]->pkt->buffs[0]);
						kfree(rx_pkts[actual_buff_num]->pkt->buffs);
						kfree(rx_pkts[actual_buff_num]->pkt);
						(*total_rx_buffs_to_replenish)++;
						actual_buff_num++;
						break;
					}
				}
				tx_buff_to_compare =
					tx_pkts[sent_pkt_idx]->buffs[sent_pkt_buff_idx]->virt_base;
				tx_buff_size =
					tx_pkts[sent_pkt_idx]->buffs[sent_pkt_buff_idx]->size;
			}
			else if (curr_pkt_recv_size > tx_buff_size)
			{
				/*	Tx chained buffers smaller than credit so HW put them all in
					one credit buffer */
				rx_buff_to_compare = rx_pkts[actual_buff_num]->pkt->buffs[0]->virt_base;
				while (curr_pkt_recv_size &&
					sent_pkt_buff_idx < tx_pkts[sent_pkt_idx]->num_of_buffers)
				{
					if (curr_pkt_recv_size < tx_buff_size)
					{
						/* Overflow to next Rx buff*/
						/* Over flow event */
						if (memcmp(
							tx_buff_to_compare,
							rx_buff_to_compare,
							curr_pkt_recv_size)) {
							DMA_UT_LOG(
								"Test failed due to buffers don't match i= %d\n",i);
							DMA_UT_LOG("tx buff:\n");
								ecpri_dma_dp_test_dump_packet(tx_buff_to_compare,
									curr_pkt_recv_size);
							DMA_UT_LOG("rx buff:\n");
								ecpri_dma_dp_test_dump_packet(
									rx_buff_to_compare,
									curr_pkt_recv_size);
							return -EFAULT;
						}
						tx_buff_to_compare =
							(void*)((unsigned long)tx_buff_to_compare +
								curr_pkt_recv_size);
						tx_buff_size -= curr_pkt_recv_size;

					}
					else
					{
						/* No overflow */
						if (memcmp(
							tx_buff_to_compare,
							rx_buff_to_compare,
							tx_buff_size)) {
							DMA_UT_LOG(
								"Test failed due to buffers don't match i= %d\n",i);
							DMA_UT_LOG("tx buff:\n");
								ecpri_dma_dp_test_dump_packet(tx_buff_to_compare,
									curr_pkt_recv_size);
							DMA_UT_LOG("rx buff:\n");
								ecpri_dma_dp_test_dump_packet(
									rx_buff_to_compare,
									curr_pkt_recv_size);
							return -EFAULT;
						}

						rx_buff_to_compare =
							(void*)((unsigned long)rx_buff_to_compare +
								tx_buff_size);
						curr_pkt_recv_size -= tx_buff_size;
						sent_pkt_buff_idx++;
						if (sent_pkt_buff_idx ==
							tx_pkts[sent_pkt_idx]->num_of_buffers)
						{
							/* Got all Tx packet buffers in this Rx buffer */
							sent_pkt_buff_idx = 0;
							sent_pkt_idx++;
							if (num_of_pkts_sent == sent_pkt_idx)
								break;
						}
						tx_buff_to_compare =
							tx_pkts[sent_pkt_idx]->buffs[sent_pkt_buff_idx]->
							virt_base;
						tx_buff_size =
							tx_pkts[sent_pkt_idx]->buffs[sent_pkt_buff_idx]->
							size;
					}
				}
			}

			if (rx_pkts[actual_buff_num]->comp_code ==
				ECPRI_DMA_COMPLETION_CODE_EOT)
			{
				i++;
			}

			kfree(rx_pkts[actual_buff_num]->pkt->buffs[0]->virt_base);
			kfree(rx_pkts[actual_buff_num]->pkt->buffs[0]);
			kfree(rx_pkts[actual_buff_num]->pkt->buffs);
			kfree(rx_pkts[actual_buff_num]->pkt);
			(*total_rx_buffs_to_replenish)++;
			actual_buff_num++;
		}
	}

	return 0;
}

static int ecpri_dma_dp_test_suite_verify_read_write_ptr(
	struct ecpri_dma_endp_context* rx_endp, struct gsi_chan_info* ch_info)
{
	int res = 0;

	res = gsi_query_channel_info(rx_endp->gsi_chan_hdl, ch_info);
	if (res) {
		DMA_UT_LOG("Failed to query Rx channel info\n");
		return -EFAULT;
	}

	if (ch_info->rp != ch_info->wp) {
		DMA_UT_LOG("Channel: 0x%x - rp:  0x%x and "
			"wp: 0x%x mismatch \n", rx_endp->gsi_chan_hdl,
			(unsigned long)ch_info->rp, (unsigned long)ch_info->wp);
		return -EFAULT;
	}

	return res;
}

static int ecpri_dma_dp_test_suite_calculate_credits(int idx,
	struct ecpri_dma_pkt** tx_pkts, int num_of_pkts, int* credits)
{
	int i;
	int res = 0;
	int curr_pkt;
	int total_buff_size = 0;
	int total_credits = 0;

	DMA_UT_LOG("Curr idx %d\n", idx);
	for (curr_pkt = idx; curr_pkt < idx + num_of_pkts; curr_pkt++) {
		DMA_UT_LOG("curr_pkt %d\n", curr_pkt);
		total_buff_size = 0;
		/* For each packet calculate total buffers size */
		for (i = 0; i < tx_pkts[curr_pkt]->num_of_buffers; i++) {
			total_buff_size += tx_pkts[curr_pkt]->buffs[i]->size;
			DMA_UT_LOG("Total buff size %d\n", total_buff_size);
		}

		if(ECPRI_DMA_DP_TEST_BUFF_SIZE < total_buff_size) {
			total_credits += (total_buff_size / ECPRI_DMA_DP_TEST_BUFF_SIZE);
			/* Ceiling */
			if (total_buff_size % ECPRI_DMA_DP_TEST_BUFF_SIZE != 0) {
				total_credits++;
			}
		} else {
			total_credits++;
		}
	}

	*credits = total_credits;
	DMA_UT_LOG("Total credits %d\n", total_credits);
	return res;
}

static int ecpri_dma_dp_test_suite_single_pkt_single_buffer(void *priv)
{
	int res = 0;
	int num_of_pkts = 1;
	bool single_buffer = true;
	int buffs_to_replenish = 0;
	struct gsi_chan_info ch_info;
	struct ecpri_dma_pkt **tx_pkts = NULL;
	struct ecpri_dma_pkt_completion_wrapper **rx_pkts = NULL;
	struct ecpri_dma_endp_context *tx_endp = NULL, *rx_endp = NULL;

	DMA_UT_LOG("Start single packet single buffer test\n");

	rx_endp = &ecpri_dma_ctx->
		endp_ctx[ECPRI_DMA_DP_UT_GSI_ID][ECPRI_DMA_DP_UT_DEST_ENDP_ID];
	tx_endp = &ecpri_dma_ctx->
		endp_ctx[ECPRI_DMA_DP_UT_GSI_ID][ECPRI_DMA_DP_UT_SRC_ENDP_ID];


	/* Provide mocked pointers to allocated space for data and credit packets */
	res = ecpri_dma_dp_test_suite_prepare_test_data(num_of_pkts, single_buffer,
		&tx_pkts, &rx_pkts);
	if (res) {
		DMA_UT_LOG("failed to prepare test data\n");
		return res;
	}

	/* Prepare exact amount of credits equal to amount of buffers sent */
	if (ECPRI_DMA_GET_CTX_HW_VER() == ECPRI_HW_V1_0) {
		res = ecpri_dma_dp_test_suite_calculate_credits(0, tx_pkts, num_of_pkts,
			&buffs_to_replenish);
		if (res) {
			DMA_UT_LOG("Failed to calculate credits\n");
			return res;
		}

		res = ecpri_dma_dp_test_rx_replenish(rx_endp, buffs_to_replenish);
		if (res) {
			DMA_UT_LOG("Failed to replenish test Rx endp\n");
			return res;
		}
	}

	/* Transmit data packets */
	res = ecpri_dma_dp_transmit(tx_endp, tx_pkts, num_of_pkts, true);
	if (res != 0) {
		DMA_UT_TEST_FAIL_REPORT("Failed on transmit");
		return -EFAULT;
	}

	/* Wait for transmit completion of ALL sent packets */
	res = ecpri_dma_dp_test_suite_wait_for_tx_comp(ECPRI_DMA_DP_TEST_ENDPOINT_DEFAULT_SRC,
		num_of_pkts);
	if (res != 0) {
		DMA_UT_TEST_FAIL_REPORT("Test failed due to Tx timeout");
		return -EFAULT;
	}

	/* Poll completed packets and compare to the sent one */
	res = ecpri_dma_dp_test_suite_verify_rx(true, num_of_pkts, tx_pkts, rx_pkts,
		&buffs_to_replenish);
	if (res != 0) {
		DMA_UT_TEST_FAIL_REPORT("Test failed due to Rx fail");
		return -EFAULT;
	}

	/* Replenish all buffers */
	if (ECPRI_DMA_GET_CTX_HW_VER() != ECPRI_HW_V1_0) {
		res = ecpri_dma_dp_test_rx_replenish(rx_endp, buffs_to_replenish);
		if (res) {
			DMA_UT_TEST_FAIL_REPORT("Test failed to perform rx replenish");
			return -EFAULT;
		}
	}

	ecpri_dma_dp_test_suite_destroy_test_data(num_of_pkts, single_buffer,
		tx_pkts, rx_pkts);

	res = ecpri_dma_set_endp_mode(rx_endp, ECPRI_DMA_NOTIFY_MODE_IRQ);
	if (res) {
		DMA_UT_LOG("Failed to change Rx test ENDP mode to IRQ\n");
	}

	if (ECPRI_DMA_GET_CTX_HW_VER() == ECPRI_HW_V1_0) {
		res = ecpri_dma_dp_test_suite_verify_read_write_ptr(rx_endp, &ch_info);
		if (res) {
			DMA_UT_LOG("RP/WP mismatch\n");
			return -EFAULT;
		}
	}

	return 0;
}

static int ecpri_dma_dp_test_suite_tx_header(void *priv) {
	int ret = 0;
	int i;
	u32 actual_number;
	size_t num_of_pkts = 1;
	size_t num_of_buffers_per_packet = 1;
	size_t buffer_size =
		ECPRI_DMA_DP_TEST_TX_BUFF_SIZE + sizeof(struct ecpri_dma_tx_header);

	struct ecpri_dma_pkt **tx_pkts = NULL;
	struct ecpri_dma_pkt_completion_wrapper **rx_pkts = NULL;
	struct ecpri_dma_dp_test_suite_endp *tx_endp = NULL;
	struct ecpri_dma_dp_test_suite_endp *rx_endp = NULL;
	struct ecpri_dma_dp_test_suite_endp *redirect_endp = NULL;
	struct ecpri_dma_tx_header *packet_header_ptr;

	u8 *p_packet_body;
	enum ecpri_hw_flavor hw_flavor = ECPRI_DMA_GET_CTX_HW_FLAVOR();

	DMA_UT_LOG("Start Tx pre-header test\n");
	if (hw_flavor == ECPRI_HW_FLAVOR_RU || hw_flavor == ECPRI_HW_FLAVOR_DU_L2)
	{
		DMAERR("Tx pre-header test requires Multi-GSI which is only supported "
			" on PCIe flavor\n");
		return 0;
	}

	/* Point to Endpoints */
	tx_endp = &dp_test_suite_ctx.endps[ECPRI_DMA_DP_TEST_ENDPOINT_DEFAULT_SRC];
	rx_endp = &dp_test_suite_ctx.endps[ECPRI_DMA_DP_TEST_ENDPOINT_DEFAULT_DEST];
	redirect_endp = &dp_test_suite_ctx.endps[ECPRI_DMA_DP_TEST_ENDPOINT_REDIRECT];

	/* Configure source for tx header redirection */
	ret = ecpri_dma_dp_test_create_endp(
		ECPRI_DMA_DP_TEST_ENDPOINT_DEFAULT_SRC,
		ECPRI_DMA_DP_UT_SRC_ENDP_ID,
		ECPRI_DMA_DP_UT_SRC_ENDP_GSI_ID,
		ECPRI_DMA_ENDP_DIR_SRC,
		ECPRI_DMA_ENDP_XBAR_LOOPBACK_ENABLED,
		ECPRI_DMA_ENDP_TX_HEADER_ENABLED,
		true);

	if (0 != ret) {
		DMA_UT_LOG("Failed to reconfigure source endpoint for tx header\n");
		return ret;
	}

	/* Create endpoint for traffic redirection */
	ret = ecpri_dma_dp_test_create_endp(
		ECPRI_DMA_DP_TEST_ENDPOINT_REDIRECT,
		ECPRI_DMA_DP_UT_REDIRECT_ENDP_ID,
		ECPRI_DMA_DP_UT_REDIRECT_ENDP_GSI_ID,
		ECPRI_DMA_ENDP_DIR_DEST,
		ECPRI_DMA_ENDP_XBAR_LOOPBACK_NOT_USED,
		ECPRI_DMA_ENDP_TX_HEADER_NOT_USED,
		true);

	if (0 != ret) {
		DMA_UT_LOG("Failed to create redirection endpoint\n");
		return ret;
	}

	/* Allocate memory Tx packets */
	ret = ecpri_dma_dp_test_suite_allocate_tx_packets(
		num_of_pkts, num_of_buffers_per_packet, buffer_size, &tx_pkts);

	if (0 != ret) {
		DMA_UT_LOG("Failed to allocate tx packets\n");
		return ret;
	}

	/* Set pointer to packet header */
	packet_header_ptr = tx_pkts[0]->buffs[0]->virt_base;

	/* Redirect packet destination */
	packet_header_ptr->gsi_id = redirect_endp->gsi_id;
	packet_header_ptr->destination_channel = redirect_endp->id;

	/* Set pointer to packet content */
	p_packet_body =
		(u8 *)tx_pkts[0]->buffs[0]->virt_base + sizeof(struct ecpri_dma_tx_header);

	/* Fill packet content */
	for (i = 0; i < ECPRI_DMA_DP_TEST_TX_BUFF_SIZE; i++) {
		p_packet_body[i] = i;
	}

	/* Transmit data packets */
	ret = ecpri_dma_dp_transmit
	(tx_endp->endp_ctx, tx_pkts, num_of_pkts, true);
	if (ret != 0) {
		DMA_UT_TEST_FAIL_REPORT("Failed on transmit\n");
		return -EFAULT;
	}

	/* Wait for packet tx complete  */
	ret = ecpri_dma_dp_test_suite_wait_for_tx_comp(
		ECPRI_DMA_DP_TEST_ENDPOINT_DEFAULT_SRC, num_of_pkts);

	if (ret != 0) {
		DMA_UT_TEST_FAIL_REPORT("Test failed due to Tx timeout\n");
		return -EFAULT;
	}

	/* Wait for packet rx complete  */
	ret = ecpri_dma_dp_test_suite_wait_for_irq(
		ECPRI_DMA_DP_TEST_ENDPOINT_REDIRECT);

	if (ret != 0) {
		DMA_UT_TEST_FAIL_REPORT("Test failed due to Rx timeout\n");
		return -EFAULT;
	}

	/* Verify packets didn't arrive to the default endpoint */
	ret = ecpri_dma_dp_test_suite_wait_for_irq(
		ECPRI_DMA_DP_TEST_ENDPOINT_DEFAULT_DEST);

	if (ret == 0) {
		DMA_UT_TEST_FAIL_REPORT("Packets arrived to default endpoint\n");
		return -EFAULT;
	}

	/* Allocate memory for Rx packets wrappers */
	ret = ecpri_dma_dp_test_suite_allocate_rx_packets_wrapper(
		num_of_pkts, &rx_pkts);

	if (0 != ret) {
		DMA_UT_LOG("Failed to allocate rx packets wrappers\n");
		return ret;
	}

	/* Get Rx packets */
	/* Test is sending single buffer packets so actual_num == number
			of buffers, no need to check for EOT */
	ret = ecpri_dma_dp_poll(
			redirect_endp->endp_ctx,
			ECPRI_DMA_DP_TEST_RX_BUDGET,
			rx_pkts,
			&actual_number);

	if (ret != 0) {
		DMA_UT_TEST_FAIL_REPORT("Test failed due to Rx fail\n");
		return -EFAULT;
	}

	/* Compare buffer sizes */
	if (tx_pkts[0]->buffs[0]->size !=
		(rx_pkts[0]->pkt->buffs[0]->size +
			sizeof(struct ecpri_dma_tx_header))) {

		DMA_UT_TEST_FAIL_REPORT("Tx and Rx buffer size mismatch\n");
		return -EFAULT;
	}

	/* Compare sent to recived data */
	ret = memcmp(p_packet_body, rx_pkts[0]->pkt->buffs[0]->virt_base,
				 rx_pkts[0]->pkt->buffs[0]->size);

	if (ret != 0) {
		DMA_UT_TEST_FAIL_REPORT("Sent and recieved buffers are not equal\n");
		return -EFAULT;
	}

	/* Free rx packet */
	kfree(rx_pkts[0]->pkt->buffs[0]->virt_base);
	kfree(rx_pkts[0]->pkt->buffs[0]);
	kfree(rx_pkts[0]->pkt->buffs);
	kfree(rx_pkts[0]->pkt);

	/* Replenish all buffers */
	ret = ecpri_dma_dp_test_rx_replenish(redirect_endp->endp_ctx, actual_number);
	if (ret) {
		DMA_UT_TEST_FAIL_REPORT("Test failed to perform rx replenish\n");
		return -EFAULT;
	}

	/* Free data */
	ecpri_dma_dp_test_suite_destroy_test_data(num_of_pkts,
		true, tx_pkts, rx_pkts);

	/* Free redirection endpoint */
	ret = ecpri_dma_dp_test_destroy_endp(ECPRI_DMA_DP_TEST_ENDPOINT_REDIRECT);
	if (ret)
		DMA_UT_LOG("Failed free endpoint\n");


	/* Restore source endpoint state */
	ret = ecpri_dma_dp_test_create_endp(
		ECPRI_DMA_DP_TEST_ENDPOINT_DEFAULT_SRC,
		ECPRI_DMA_DP_UT_SRC_ENDP_ID,
		ECPRI_DMA_DP_UT_SRC_ENDP_GSI_ID,
		ECPRI_DMA_ENDP_DIR_SRC,
		ECPRI_DMA_ENDP_XBAR_LOOPBACK_DISABLED,
		ECPRI_DMA_ENDP_TX_HEADER_DISABLED,
		true);

	if (0 != ret) {
		return ret;
	}

	ret = ecpri_dma_set_endp_mode(
	 rx_endp->endp_ctx,
	 ECPRI_DMA_NOTIFY_MODE_IRQ);

	if (0 != ret) {
		DMA_UT_LOG("Failed to change Rx test ENDP mode to IRQ\n");
	}

	return 0;
}

static int ecpri_dma_dp_test_suite_tx_broadcast(void *priv) {

	/* Start: variable declaraion */

	struct ecpri_dma_dp_test_suite_endp *tx_endp =
		&dp_test_suite_ctx.endps[ECPRI_DMA_DP_TEST_ENDPOINT_DEFAULT_SRC];

	struct ecpri_dma_dp_test_suite_endp *def_rx_endp =
		&dp_test_suite_ctx.endps[ECPRI_DMA_DP_TEST_ENDPOINT_DEFAULT_DEST];

	struct ecpri_dma_dp_test_suite_endp *broadcast_endps_arr[] = {
		&dp_test_suite_ctx.endps[ECPRI_DMA_DP_TEST_ENDPOINT_BROADCAST0],
		&dp_test_suite_ctx.endps[ECPRI_DMA_DP_TEST_ENDPOINT_BROADCAST1],
	};

	int num_broadcast_endp = ARRAY_SIZE(broadcast_endps_arr);
	int num_pkts = num_broadcast_endp;
	int num_of_buffers_per_packet = 1;
	size_t buffer_size = ECPRI_DMA_DP_TEST_TX_BUFF_SIZE;
	struct ecpri_dma_mem_buffer **buf_array;
	struct ecpri_dma_pkt_completion_wrapper **rx_pkt_wrapper = NULL;
	struct ecpri_dma_pkt **tx_pkts = NULL;
	u8 *tx_data;
	u8 *rx_data;
	int ret = 0;
	int i;
	int j;
	enum ecpri_hw_flavor hw_flavor = ECPRI_DMA_GET_CTX_HW_FLAVOR();

	/* End: variable declaraion */

	DMA_UT_LOG("Start Tx braodcast test\n");

	if (hw_flavor == ECPRI_HW_FLAVOR_RU || hw_flavor == ECPRI_HW_FLAVOR_DU_L2)
	{
		DMAERR("Tx braodcast test requires Multi-GSI which is only supported "
			" on PCIe flavor\n");
		return 0;
	}

	/* Configure source for tx header redirection */
	ret = ecpri_dma_dp_test_create_endp(
		ECPRI_DMA_DP_TEST_ENDPOINT_DEFAULT_SRC,
		ECPRI_DMA_DP_UT_SRC_ENDP_ID,
		ECPRI_DMA_DP_UT_SRC_ENDP_GSI_ID,
		ECPRI_DMA_ENDP_DIR_SRC,
		ECPRI_DMA_ENDP_XBAR_LOOPBACK_ENABLED,
		ECPRI_DMA_ENDP_TX_HEADER_ENABLED,
		true);

	if (0 != ret) {
		DMA_UT_LOG("Failed to reconfigure source endpoint for tx header\n");
		return ret;
	}

	ret = ecpri_dma_dp_test_create_endp(
		ECPRI_DMA_DP_TEST_ENDPOINT_BROADCAST0,
		ECPRI_DMA_DP_UT_BRAODCAST0_ENDP_ID,
		ECPRI_DMA_DP_UT_BRAODCAST0_ENDP_GSI_ID,
		ECPRI_DMA_ENDP_DIR_DEST,
		ECPRI_DMA_ENDP_XBAR_LOOPBACK_NOT_USED,
		ECPRI_DMA_ENDP_TX_HEADER_NOT_USED,
		false);

	if (0 != ret) {
		DMA_UT_LOG("Failed to reconfigure broadcasr point 0\n");
		return ret;
	}

	ret = ecpri_dma_dp_test_create_endp(
		ECPRI_DMA_DP_TEST_ENDPOINT_BROADCAST1,
		ECPRI_DMA_DP_UT_BRAODCAST1_ENDP_ID,
		ECPRI_DMA_DP_UT_BRAODCAST1_ENDP_GSI_ID,
		ECPRI_DMA_ENDP_DIR_DEST,
		ECPRI_DMA_ENDP_XBAR_LOOPBACK_NOT_USED,
		ECPRI_DMA_ENDP_TX_HEADER_NOT_USED,
		false);

	if (0 != ret) {
		DMA_UT_LOG("Failed to reconfigure broadcasr point 1\n");
		return ret;
	}

	/* Create tx data buffers array */
	ret = ecpri_dma_dp_test_buffers_array_allocate(
		num_of_buffers_per_packet,
		buffer_size,
		&buf_array);

	if (0 != ret) {
		DMA_UT_LOG("Failed to allocate buffer array\n");
		return -EFAULT;
	}

	/* Fill tx data buffers with content */
	for (i = 0; i < num_of_buffers_per_packet; i++) {
		tx_data = buf_array[i]->virt_base;

		for (j = 0; j < ECPRI_DMA_DP_TEST_TX_BUFF_SIZE; j++) {
			tx_data[j] = i + 1;
		}
	}

	/* Create tx data for broadcast */
	ret = ecpri_dma_dp_test_create_broadcast_pkts_from_data(
		buf_array,
		num_of_buffers_per_packet,
		broadcast_endps_arr,
		num_broadcast_endp,
		&tx_pkts);

	if (0 != ret) {
		DMA_UT_LOG("Failed to allocate tx packets\n");
		return ret;
	}

	/* Transmit the data packets */
	ret = ecpri_dma_dp_transmit(tx_endp->endp_ctx, tx_pkts, num_pkts, true);

	if (ret != 0) {
		DMA_UT_TEST_FAIL_REPORT("Failed on transmit\n");
		return -EFAULT;
	}

	/* Wait for tx completion  */
	ret = ecpri_dma_dp_test_suite_wait_for_tx_comp(
		ECPRI_DMA_DP_TEST_ENDPOINT_DEFAULT_SRC,
	 	num_pkts);

	if (ret != 0) {
		DMA_UT_TEST_FAIL_REPORT("Test failed due to Tx timeois_startedut\n");
		return -EFAULT;
	}

	/* Wait for broadcast finish for the rx endpoints */
	for (i = 0; i < num_broadcast_endp; i++) {

		ret = ecpri_dma_dp_test_suite_wait_for_irq(
			ECPRI_DMA_DP_TEST_ENDPOINT_BROADCAST0 + i);

		if (ret != 0) {
			DMA_UT_LOG("Rx broadcast endpoint timeout %d\n",
			 	ECPRI_DMA_DP_TEST_ENDPOINT_BROADCAST0 + i);
			return -EFAULT;
		}
	}

	/* Verify packets didn't arrive to the default endpoint */
	ret = ecpri_dma_dp_test_suite_wait_for_irq(
		ECPRI_DMA_DP_TEST_ENDPOINT_DEFAULT_DEST);

	if (ret == 0) {
		DMA_UT_TEST_FAIL_REPORT("Packets arrived to default endpoint\n");
		return -EFAULT;
	}

	/* Verify transaction */
	for (i = 0; i < num_broadcast_endp; i++) {

		u32 actual_number;
		u32 tx_buffer_size;
		int j;

		/* Allocate memory for Rx packets wrapper needed for data readout */
		ret = ecpri_dma_dp_test_suite_allocate_rx_packets_wrapper(
			1, &rx_pkt_wrapper);

		if (0 != ret) {
			DMA_UT_LOG("Failed to allocate rx packets wrappers\n");
			return ret;
		}

		/* Get rx packets */
		/* Test is sending single buffer packets so actual_num == number
			of buffers, no need to check for EOT */
		ret =
			ecpri_dma_dp_poll(broadcast_endps_arr[i]->endp_ctx,
								ECPRI_DMA_DP_TEST_RX_BUDGET,
								rx_pkt_wrapper, &actual_number);
		if (ret != 0) {
			DMA_UT_TEST_FAIL_REPORT("Rx packets poll failiure\n");
			return -EFAULT;
		}

		/* Calcuate total size of tx data */
		tx_buffer_size = 0;

		for (j = 0; j < num_of_buffers_per_packet; j++) {
			tx_buffer_size += tx_pkts[i]->buffs[
				j + NUM_OF_NON_DATA_BUFFS]->size;
		}

		/* Compare sent and received data size */
		if (tx_buffer_size != rx_pkt_wrapper[0]->pkt->buffs[0]->size) {

			DMA_UT_LOG(
				"Sent (%d bytes) and recieved (%d bytes). "
				"Buffers sizes are not equal\n",
				 tx_buffer_size,
				 rx_pkt_wrapper[0]->pkt->buffs[0]->size);

			return -EFAULT;
		}

		/* Point to rx data */
		rx_data = rx_pkt_wrapper[0]->pkt->buffs[0]->virt_base;

		/* Compare sent to received data */
		for (j = 0; j < num_of_buffers_per_packet; j++) {

			/* Point to data buffer (buffer 0 is used for header)*/
			tx_data = tx_pkts[i]->buffs[j +
				NUM_OF_NON_DATA_BUFFS]->virt_base;

			/* Get buffer size */
			tx_buffer_size =
				tx_pkts[i]->buffs[j + NUM_OF_NON_DATA_BUFFS]->size;

			/* Compare sent to recived data */
			ret = memcmp(tx_data, rx_data, tx_buffer_size);

			if (ret != 0) {
				DMA_UT_TEST_FAIL_REPORT(
					"Sent and recieved buffers are not equal\n");
				return -EFAULT;
			}

			/* Advance rx buffer pointer by the size of last tx buffer */
			rx_data += tx_buffer_size;
		}

		/* Free rx buffer data */
		kfree(rx_pkt_wrapper[0]->pkt->buffs[0]->virt_base);

		/* Free rx buffer */
		kfree(rx_pkt_wrapper[0]->pkt->buffs[0]);

		/* Free rx buffer array */
		kfree(rx_pkt_wrapper[0]->pkt->buffs);

		/* Free rx packet */
		kfree(rx_pkt_wrapper[0]->pkt);

		/* Replenish rx buffers for the endpoint */
		ret = ecpri_dma_dp_test_rx_replenish(broadcast_endps_arr[i]->endp_ctx,
			 num_of_buffers_per_packet);

		if (ret) {
			DMA_UT_TEST_FAIL_REPORT("Test failed to perform rx replenish\n");
			return -EFAULT;
		}

		/* Free rx packet wrapper */
		ecpri_dma_dp_test_stuite_free_rx_packets_wrapper(1, rx_pkt_wrapper);

	}

	/* Free buffers array */
	ret = ecpri_dma_dp_test_buffers_array_free(
		buf_array, num_of_buffers_per_packet);

	if (0 != ret) {
		DMA_UT_TEST_FAIL_REPORT("Failed to free buffers array\n");
	}

	/* Free broadcast packets array (including header buffer)*/
	ecpri_dma_dp_test_destroy_broadcast_pkts(tx_pkts, num_pkts,
		num_of_buffers_per_packet);

	for (i = 0; i < num_broadcast_endp; i++) {

		/* Free redirection endpoint */
		ret = ecpri_dma_dp_test_destroy_endp(
			ECPRI_DMA_DP_TEST_ENDPOINT_BROADCAST0 + i);
		if (ret) {
			DMA_UT_LOG("Failed free endpoint\n");
		}
	}

	/* Restore source endpoint config */
	ret = ecpri_dma_dp_test_create_endp(
		ECPRI_DMA_DP_TEST_ENDPOINT_DEFAULT_SRC,
		ECPRI_DMA_DP_UT_SRC_ENDP_ID,
		ECPRI_DMA_DP_UT_SRC_ENDP_GSI_ID,
		ECPRI_DMA_ENDP_DIR_SRC,
		ECPRI_DMA_ENDP_XBAR_LOOPBACK_DISABLED,
		ECPRI_DMA_ENDP_TX_HEADER_DISABLED,
		true);

	if (0 != ret) {
		DMA_UT_LOG("Failed to reconfigure source endpoint for tx header\n");
		return ret;
	}

	ret = ecpri_dma_set_endp_mode(
		def_rx_endp->endp_ctx, ECPRI_DMA_NOTIFY_MODE_IRQ);

	if (0 != ret) {
		DMA_UT_LOG("Failed to change Rx test ENDP mode to IRQ\n");
	}

	DMA_UT_DBG("End Test: tx_broadcast!\n");

	return 0;
}

static int ecpri_dma_dp_test_suite_single_pkt_mult_buffer(void *priv)
{
	int res = 0;
	int num_of_pkts = 1;
	bool single_buffer = false;
	int buffs_to_replenish = 0;
	struct gsi_chan_info ch_info;
	struct ecpri_dma_pkt **tx_pkts = NULL;
	struct ecpri_dma_pkt_completion_wrapper **rx_pkts = NULL;
	struct ecpri_dma_endp_context *tx_endp = NULL, *rx_endp = NULL;

	DMA_UT_LOG("Start single packet multiple buffer test\n");

	tx_endp = &ecpri_dma_ctx->
		endp_ctx[ECPRI_DMA_DP_UT_GSI_ID][ECPRI_DMA_DP_UT_SRC_ENDP_ID];
	rx_endp = &ecpri_dma_ctx->
		endp_ctx[ECPRI_DMA_DP_UT_GSI_ID][ECPRI_DMA_DP_UT_DEST_ENDP_ID];

	res = ecpri_dma_dp_test_suite_prepare_test_data(num_of_pkts, single_buffer,
		&tx_pkts, &rx_pkts);
	if (res) {
		DMA_UT_LOG("failed to prepare test data\n");
		return res;
	}

	/* Prepare exact amount of credits equal to amount of buffers sent */
	if (ECPRI_DMA_GET_CTX_HW_VER() == ECPRI_HW_V1_0) {
		res = ecpri_dma_dp_test_suite_calculate_credits(0, tx_pkts, num_of_pkts,
			&buffs_to_replenish);
		if (res) {
			DMA_UT_LOG("Failed to calculate credits\n");
			return res;
		}

		res = ecpri_dma_dp_test_rx_replenish(rx_endp, buffs_to_replenish);
		if (res) {
			DMA_UT_LOG("Failed to replenish test Rx endp\n");
			return res;
		}
	}

	res = ecpri_dma_dp_transmit(tx_endp, tx_pkts, num_of_pkts, true);
	if (res != 0) {
		DMA_UT_TEST_FAIL_REPORT("Failed on transmit");
		return -EFAULT;
	}

	res = ecpri_dma_dp_test_suite_wait_for_tx_comp(ECPRI_DMA_DP_TEST_ENDPOINT_DEFAULT_SRC,
		num_of_pkts);

		if (res != 0) {
		DMA_UT_TEST_FAIL_REPORT("Test failed due to Tx timeout");
		return -EFAULT;
	}

	res = ecpri_dma_dp_test_suite_verify_rx(true, num_of_pkts, tx_pkts, rx_pkts,
		&buffs_to_replenish);
	if (res != 0) {
		DMA_UT_TEST_FAIL_REPORT("Test failed due to Tx fail");
		return -EFAULT;
	}

	if (ECPRI_DMA_GET_CTX_HW_VER() != ECPRI_HW_V1_0) {
		res = ecpri_dma_dp_test_rx_replenish(rx_endp, buffs_to_replenish);
		if (res) {
			DMA_UT_TEST_FAIL_REPORT("Test failed to perform rx replenish");
			return -EFAULT;
		}
	}

	ecpri_dma_dp_test_suite_destroy_test_data(num_of_pkts, false,
		tx_pkts, rx_pkts);

	res = ecpri_dma_set_endp_mode(rx_endp, ECPRI_DMA_NOTIFY_MODE_IRQ);
	if (res) {
		DMA_UT_LOG("Failed to change Rx test ENDP mode to IRQ\n");
	}

	if (ECPRI_DMA_GET_CTX_HW_VER() == ECPRI_HW_V1_0) {
		res = ecpri_dma_dp_test_suite_verify_read_write_ptr(rx_endp, &ch_info);
		if (res) {
			DMA_UT_LOG("RP/WP mismatch\n");
			return -EFAULT;
		}
	}

	return 0;
}

static int ecpri_dma_dp_test_suite_mult_pkt_single_buffer(void *priv)
{
	int res = 0;
	bool single_buffer = true;
	int buffs_to_replenish = 0;
	struct gsi_chan_info ch_info;
	struct ecpri_dma_pkt **tx_pkts = NULL;
	struct ecpri_dma_pkt_completion_wrapper **rx_pkts = NULL;
	struct ecpri_dma_endp_context *tx_endp = NULL, *rx_endp = NULL;
	int num_of_pkts_to_send = ECPRI_DMA_DP_TEST_NUM_OF_BUFFS_IN_RING;

	DMA_UT_LOG("Start multiple packet singel buffer test\n");

	tx_endp = &ecpri_dma_ctx->
		endp_ctx[ECPRI_DMA_DP_UT_GSI_ID][ECPRI_DMA_DP_UT_SRC_ENDP_ID];
	rx_endp = &ecpri_dma_ctx->
		endp_ctx[ECPRI_DMA_DP_UT_GSI_ID][ECPRI_DMA_DP_UT_DEST_ENDP_ID];

	res = ecpri_dma_dp_test_suite_prepare_test_data(
		num_of_pkts_to_send, single_buffer, &tx_pkts, &rx_pkts);
	if (res) {
		DMA_UT_LOG("failed to prepare test data\n");
		return res;
	}

	/* Prepare exact amount of credits equal to amount of buffers sent */
	if (ECPRI_DMA_GET_CTX_HW_VER() == ECPRI_HW_V1_0) {
		res = ecpri_dma_dp_test_suite_calculate_credits(0, tx_pkts,
			num_of_pkts_to_send, &buffs_to_replenish);
		if (res) {
			DMA_UT_LOG("Failed to calculate credits\n");
			return res;
		}

		res = ecpri_dma_dp_test_rx_replenish(rx_endp, buffs_to_replenish);
		if (res) {
			DMA_UT_LOG("Failed to replenish test Rx endp\n");
			return res;
		}
	}

	res = ecpri_dma_dp_transmit(tx_endp, tx_pkts, num_of_pkts_to_send, true);
	if (res != 0) {
		DMA_UT_TEST_FAIL_REPORT("Failed on transmit");
		return -EFAULT;
	}

	res = ecpri_dma_dp_test_suite_wait_for_tx_comp(ECPRI_DMA_DP_TEST_ENDPOINT_DEFAULT_SRC,
	 	num_of_pkts_to_send);

	if (res != 0) {
		DMA_UT_TEST_FAIL_REPORT("Test failed due to Tx timeout");
		return -EFAULT;
	}

	res = ecpri_dma_dp_test_suite_verify_rx(true, num_of_pkts_to_send, tx_pkts,
						rx_pkts, &buffs_to_replenish);
	if (res != 0) {
		DMA_UT_TEST_FAIL_REPORT("Test failed due to Tx fail");
		return -EFAULT;
	}

	if (ECPRI_DMA_GET_CTX_HW_VER() != ECPRI_HW_V1_0) {
		res = ecpri_dma_dp_test_rx_replenish(rx_endp, buffs_to_replenish);
		if (res) {
			DMA_UT_TEST_FAIL_REPORT("Test failed to perform rx replenish");
			return -EFAULT;
		}
	}

	ecpri_dma_dp_test_suite_destroy_test_data(num_of_pkts_to_send, true,
						   tx_pkts, rx_pkts);

	res = ecpri_dma_set_endp_mode(rx_endp, ECPRI_DMA_NOTIFY_MODE_IRQ);
	if (res) {
		DMA_UT_LOG("Failed to change Rx test ENDP mode to IRQ\n");
	}

	if (ECPRI_DMA_GET_CTX_HW_VER() == ECPRI_HW_V1_0) {
		res = ecpri_dma_dp_test_suite_verify_read_write_ptr(rx_endp, &ch_info);
		if (res) {
			DMA_UT_LOG("RP/WP mismatch\n");
			return -EFAULT;
		}
	}

	return 0;
}

static int ecpri_dma_dp_test_suite_mult_pkt_mult_buffer(void *priv)
{
	int res = 0;
	bool single_buffer = false;
	int buffs_to_replenish = 0;
	struct gsi_chan_info ch_info;
	struct ecpri_dma_pkt **tx_pkts = NULL;
	struct ecpri_dma_pkt_completion_wrapper **rx_pkts = NULL;
	struct ecpri_dma_endp_context *tx_endp = NULL, *rx_endp = NULL;
	int num_of_pkts_to_send =
		(ECPRI_DMA_DP_TEST_NUM_OF_BUFFS_IN_RING) /
		ECPRI_DMA_DP_TEST_MAX_BUFFS;

	DMA_UT_LOG("Start multiple packet multiple buffer test\n");

	tx_endp = &ecpri_dma_ctx->
		endp_ctx[ECPRI_DMA_DP_UT_GSI_ID][ECPRI_DMA_DP_UT_SRC_ENDP_ID];
	rx_endp = &ecpri_dma_ctx->
		endp_ctx[ECPRI_DMA_DP_UT_GSI_ID][ECPRI_DMA_DP_UT_DEST_ENDP_ID];

	res = ecpri_dma_dp_test_suite_prepare_test_data(
		num_of_pkts_to_send, single_buffer, &tx_pkts, &rx_pkts);
	if (res) {
		DMA_UT_LOG("failed to prepare test data\n");
		return res;
	}

	/* Prepare exact amount of credits equal to amount of buffers sent */
	if (ECPRI_DMA_GET_CTX_HW_VER() == ECPRI_HW_V1_0) {
		res = ecpri_dma_dp_test_suite_calculate_credits(0, tx_pkts,
			num_of_pkts_to_send, &buffs_to_replenish);
		if (res) {
			DMA_UT_LOG("Failed to calculate credits\n");
			return res;
		}

		res = ecpri_dma_dp_test_rx_replenish(rx_endp, buffs_to_replenish);
		if (res) {
			DMA_UT_LOG("Failed to replenish test Rx endp\n");
			return res;
		}
	}

	res = ecpri_dma_dp_transmit(tx_endp, tx_pkts, num_of_pkts_to_send, true);
	if (res != 0) {
		DMA_UT_TEST_FAIL_REPORT("Failed on transmit");
		return -EFAULT;
	}

	res = ecpri_dma_dp_test_suite_wait_for_tx_comp(ECPRI_DMA_DP_TEST_ENDPOINT_DEFAULT_SRC,
	 	num_of_pkts_to_send);

	if (res != 0) {
		DMA_UT_TEST_FAIL_REPORT("Test failed due to Tx timeout");
		return -EFAULT;
	}

	res = ecpri_dma_dp_test_suite_verify_rx(true, num_of_pkts_to_send, tx_pkts,
		rx_pkts, &buffs_to_replenish);
	if (res != 0) {
		DMA_UT_TEST_FAIL_REPORT("Test failed due to Tx fail");
		return -EFAULT;
	}

	if (ECPRI_DMA_GET_CTX_HW_VER() != ECPRI_HW_V1_0) {
		res = ecpri_dma_dp_test_rx_replenish(
			rx_endp, buffs_to_replenish);
		if (res) {
			DMA_UT_TEST_FAIL_REPORT("Test failed to perform rx replenish");
			return -EFAULT;
		}
	}

	ecpri_dma_dp_test_suite_destroy_test_data(num_of_pkts_to_send, single_buffer,
		tx_pkts, rx_pkts);

	res = ecpri_dma_set_endp_mode(rx_endp, ECPRI_DMA_NOTIFY_MODE_IRQ);
	if (res) {
		DMA_UT_LOG("Failed to change Rx test ENDP mode to IRQ\n");
	}

	if (ECPRI_DMA_GET_CTX_HW_VER() == ECPRI_HW_V1_0) {
		res = ecpri_dma_dp_test_suite_verify_read_write_ptr(rx_endp, &ch_info);
		if (res) {
			DMA_UT_LOG("RP/WP mismatch\n");
			return -EFAULT;
		}
	}

	return 0;
}

static int ecpri_dma_dp_test_suite_wrap_around_single_buffer(void *priv)
{
	int res = 0;
	bool single_buffer = true;
	int buffs_to_replenish = 0;
	struct gsi_chan_info ch_info;
	struct ecpri_dma_pkt **tx_pkts = NULL;
	struct ecpri_dma_pkt_completion_wrapper **rx_pkts = NULL;
	struct ecpri_dma_endp_context *tx_endp = NULL, *rx_endp = NULL;
	int num_of_pkts_to_send = ECPRI_DMA_DP_TEST_NUM_OF_BUFFS_IN_RING;
	int num_of_iter = 3;
	int i = 0;
	bool expecting_irq = true;

	DMA_UT_LOG("Start wrap around singel buffer test\n");

	tx_endp = &ecpri_dma_ctx->
		endp_ctx[ECPRI_DMA_DP_UT_GSI_ID][ECPRI_DMA_DP_UT_SRC_ENDP_ID];
	rx_endp = &ecpri_dma_ctx->
		endp_ctx[ECPRI_DMA_DP_UT_GSI_ID][ECPRI_DMA_DP_UT_DEST_ENDP_ID];

	res = ecpri_dma_dp_test_suite_prepare_test_data(
		num_of_iter * num_of_pkts_to_send, single_buffer, &tx_pkts, &rx_pkts);
	if (res) {
		DMA_UT_LOG("failed to prepare test data\n");
		return res;
	}

	for (i = 0; i < num_of_iter; i++) {
		/* Prepare exact amount of credits equal to amount of buffers sent */
		if (ECPRI_DMA_GET_CTX_HW_VER() == ECPRI_HW_V1_0) {
			res = ecpri_dma_dp_test_suite_calculate_credits(
				i * num_of_pkts_to_send, tx_pkts,
				num_of_pkts_to_send,
				&buffs_to_replenish);
			if (res) {
				DMA_UT_LOG("Failed to calculate credits\n");
				return res;
			}

			DMA_UT_LOG("Credits to replensih %d at index %d\n",
				buffs_to_replenish, num_of_pkts_to_send);

			res = ecpri_dma_dp_test_rx_replenish(rx_endp, buffs_to_replenish);
			if (res) {
				DMA_UT_LOG("Failed to replenish test Rx endp\n");
				return res;
			}
		}

		res = ecpri_dma_dp_transmit(tx_endp,
			&tx_pkts[i * num_of_pkts_to_send],
			num_of_pkts_to_send, true);
		if (res != 0) {
			DMAERR("Failed on transmit, iteration %d\n", i);
			DMA_UT_TEST_FAIL_REPORT("Failed on transmit");
			return -EFAULT;
		}

		res = ecpri_dma_dp_test_suite_wait_for_tx_comp(
			ECPRI_DMA_DP_TEST_ENDPOINT_DEFAULT_SRC,
	 	(i + 1) * num_of_pkts_to_send);

		if (res != 0) {
			DMA_UT_TEST_FAIL_REPORT("Test failed due to Tx timeout");
			return -EFAULT;
		}

		res = ecpri_dma_dp_test_suite_verify_rx(expecting_irq,
			num_of_pkts_to_send, &tx_pkts[i * num_of_pkts_to_send],
			rx_pkts, &buffs_to_replenish);
		if (res != 0) {
			DMA_UT_TEST_FAIL_REPORT("Test failed due to Tx fail");
			return -EFAULT;
		}

		expecting_irq = false;

		if (ECPRI_DMA_GET_CTX_HW_VER() != ECPRI_HW_V1_0) {
			res = ecpri_dma_dp_test_rx_replenish(rx_endp, buffs_to_replenish);
			if (res) {
				DMA_UT_TEST_FAIL_REPORT("Test failed to perform rx replenish");
				return -EFAULT;
			}
		}
	}

	ecpri_dma_dp_test_suite_destroy_test_data(
		num_of_iter * num_of_pkts_to_send, single_buffer,
		tx_pkts, rx_pkts);

	res = ecpri_dma_set_endp_mode(rx_endp, ECPRI_DMA_NOTIFY_MODE_IRQ);
	if (res) {
		DMA_UT_LOG("Failed to change Rx test ENDP mode to IRQ\n");
	}

	if (ECPRI_DMA_GET_CTX_HW_VER() == ECPRI_HW_V1_0) {
		res = ecpri_dma_dp_test_suite_verify_read_write_ptr(rx_endp, &ch_info);
		if (res) {
			DMA_UT_LOG("RP/WP mismatch\n");
			return -EFAULT;
		}
	}

	return 0;
}

static int ecpri_dma_dp_test_suite_wrap_around_mult_buffer(void *priv)
{
	int res = 0;
	bool single_buffer = false;
	int buffs_to_replenish = 0;
	struct gsi_chan_info ch_info;
	struct ecpri_dma_pkt **tx_pkts = NULL;
	struct ecpri_dma_pkt_completion_wrapper **rx_pkts = NULL;
	struct ecpri_dma_endp_context *tx_endp = NULL, *rx_endp = NULL;
	int num_of_pkts_to_send =
		(ECPRI_DMA_DP_TEST_NUM_OF_BUFFS_IN_RING) /
		ECPRI_DMA_DP_TEST_MAX_BUFFS;
	int num_of_iter = 3;
	int i = 0;
	bool expecting_irq = true;

	DMA_UT_LOG("Start wrap around mult buffer test\n");

	tx_endp = &ecpri_dma_ctx->
		endp_ctx[ECPRI_DMA_DP_UT_GSI_ID][ECPRI_DMA_DP_UT_SRC_ENDP_ID];
	rx_endp = &ecpri_dma_ctx->
		endp_ctx[ECPRI_DMA_DP_UT_GSI_ID][ECPRI_DMA_DP_UT_DEST_ENDP_ID];

	res = ecpri_dma_dp_test_suite_prepare_test_data(
		num_of_iter * num_of_pkts_to_send, single_buffer, &tx_pkts, &rx_pkts);
	if (res) {
		DMA_UT_LOG("failed to prepare test data\n");
		return res;
	}

	for (i = 0; i < num_of_iter; i++) {
		/* Prepare exact amount of credits equal to amount of buffers sent */
		if (ECPRI_DMA_GET_CTX_HW_VER() == ECPRI_HW_V1_0) {
			res = ecpri_dma_dp_test_suite_calculate_credits(
				i * num_of_pkts_to_send, tx_pkts,
				num_of_pkts_to_send,
				&buffs_to_replenish);
			if (res) {
				DMA_UT_LOG("Failed to calculate credits\n");
				return res;
			}

			DMA_UT_LOG("Credits to replensih %d at index %d\n",
				buffs_to_replenish, num_of_pkts_to_send);

			res = ecpri_dma_dp_test_rx_replenish(rx_endp, buffs_to_replenish);
			if (res) {
				DMA_UT_LOG("Failed to replenish test Rx endp\n");
				return res;
			}
		}

		res = ecpri_dma_dp_transmit(tx_endp,
			&tx_pkts[i * num_of_pkts_to_send],
			num_of_pkts_to_send, true);
		if (res != 0) {
			DMA_UT_TEST_FAIL_REPORT("Failed on transmit");
			return -EFAULT;
		}

		res = ecpri_dma_dp_test_suite_wait_for_tx_comp(ECPRI_DMA_DP_TEST_ENDPOINT_DEFAULT_SRC,
	 		num_of_pkts_to_send);

		if (res != 0) {
			DMA_UT_TEST_FAIL_REPORT("Test failed due to Tx timeout");
			return -EFAULT;
		}

		res = ecpri_dma_dp_test_suite_verify_rx(expecting_irq,
			num_of_pkts_to_send, &tx_pkts[i * num_of_pkts_to_send],
			rx_pkts, &buffs_to_replenish);
		if (res != 0) {
			DMA_UT_TEST_FAIL_REPORT("Test failed due to Tx fail");
			return -EFAULT;
		}

		expecting_irq = false;

		if (ECPRI_DMA_GET_CTX_HW_VER() != ECPRI_HW_V1_0) {
			res = ecpri_dma_dp_test_rx_replenish(
				rx_endp, buffs_to_replenish);
			if (res) {
				DMA_UT_TEST_FAIL_REPORT("Test failed to perform rx replenish");
				return -EFAULT;
			}
		}
	}

	ecpri_dma_dp_test_suite_destroy_test_data(
		num_of_iter * num_of_pkts_to_send, single_buffer,
		tx_pkts, rx_pkts);

	res = ecpri_dma_set_endp_mode(rx_endp, ECPRI_DMA_NOTIFY_MODE_IRQ);
	if (res) {
		DMA_UT_LOG("Failed to change Rx test ENDP mode to IRQ\n");
	}

	if (ECPRI_DMA_GET_CTX_HW_VER() == ECPRI_HW_V1_0) {
		res = ecpri_dma_dp_test_suite_verify_read_write_ptr(rx_endp, &ch_info);
		if (res) {
			DMA_UT_LOG("RP/WP mismatch\n");
			return -EFAULT;
		}
	}

	return 0;
}

/* Suite definition block */
DMA_UT_DEFINE_SUITE_START(driver_dp, "Driver Data Path suite",
						  ecpri_dma_dp_test_suite_setup,
						  ecpri_dma_dp_test_suite_teardown){
	DMA_UT_ADD_TEST(
		single_pkt_single_buffer,
		"This test will verify data path by sending one packet with single buffer on SRC ENDP and verifying it is received the same on DEST ENDP",
		ecpri_dma_dp_test_suite_single_pkt_single_buffer, true,
		ECPRI_HW_V1_0, ECPRI_HW_MAX),
	DMA_UT_ADD_TEST(
		single_pkt_mult_buffer,
		"This test will verify data path by sending one packet with multiple buffers on SRC ENDP and verifying it is received the same on DEST ENDP",
		ecpri_dma_dp_test_suite_single_pkt_mult_buffer, true,
		ECPRI_HW_V1_0, ECPRI_HW_MAX),
	DMA_UT_ADD_TEST(
		mult_pkt_single_buffer,
		"This test will verify data path by sending multiple packets with single buffer on SRC ENDP and verifying they are received the same on DEST ENDP",
		ecpri_dma_dp_test_suite_mult_pkt_single_buffer, true,
		ECPRI_HW_V1_0, ECPRI_HW_MAX),
	DMA_UT_ADD_TEST(
		mult_pkt_mult_buffer,
		"This test will verify data path by sending multiple packets with multiple buffers on SRC ENDP and verifying they are received the same on DEST ENDP",
		ecpri_dma_dp_test_suite_mult_pkt_mult_buffer, true,
		ECPRI_HW_V1_0, ECPRI_HW_MAX),
	DMA_UT_ADD_TEST(
		wrap_around_single_buffer,
		"This test will verify data path by sending multiple packets with single buffer for more than one iteration on SRC ENDP and verifying they are received the same on DEST ENDP",
		ecpri_dma_dp_test_suite_wrap_around_single_buffer, true,
		ECPRI_HW_V1_0, ECPRI_HW_MAX),
	DMA_UT_ADD_TEST(
		wrap_around_mult_buffer,
		"This test will verify data path by sending multiple packets with multiple buffers for more than one iteration on SRC ENDP and verifying they are received the same on DEST ENDP",
		ecpri_dma_dp_test_suite_wrap_around_mult_buffer, true,
		ECPRI_HW_V1_0, ECPRI_HW_MAX),
	DMA_UT_ADD_TEST(
		tx_header,
		"This test will verify packet redirection based on the contents of tx header",
		ecpri_dma_dp_test_suite_tx_header, true,
		ECPRI_HW_V2_0, ECPRI_HW_MAX),
	DMA_UT_ADD_TEST(
		tx_broadcast,
		"This test will verify packet broadcast to multiple endpoints",
		ecpri_dma_dp_test_suite_tx_broadcast, true,
		ECPRI_HW_V2_0, ECPRI_HW_MAX),

} DMA_UT_DEFINE_SUITE_END(driver_dp);
