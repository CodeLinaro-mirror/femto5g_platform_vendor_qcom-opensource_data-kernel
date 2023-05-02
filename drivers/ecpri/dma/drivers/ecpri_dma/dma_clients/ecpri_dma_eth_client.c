/*
 * SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include <linux/dmapool.h>
#include <linux/list.h>
#include "ecpri_dma_i.h"
#include "ecpri_dma_dp.h"
#include "ecpri_dma_eth_client.h"

struct ecpri_dma_eth_client_endp_mapping
	eth_client_endp_map[ECPRI_HW_MAX][ECPRI_HW_FLAVOR_MAX]
	[ECPRI_DMA_ETH_CLIENT_MAX_CONNTECTIONS] = {
	/* V1 */
	/* RU Connections */
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_RU][0]       = { true, {0, 0},  {37, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_RU][1]       = { true, {1, 0},  {38, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_RU][2]       = { true, {2, 0},  {39, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_RU][3]       = { true, {3, 0},  {40, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_RU][4]       = { true, {4, 0},  {41, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_RU][5]       = { true, {5, 0},  {42, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_RU][6]       = { true, {6, 0},  {43, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_RU][7]       = { true, {7, 0},  {44, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_RU][8]       = { true, {8, 0},  {45, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_RU][9]       = { true, {9, 0},  {46, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_RU][10]      = { true, {10, 0}, {47, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_RU][11]      = { true, {11, 0}, {48, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_RU][12]      = { true, {14, 0}, {51, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_RU][13]      = { true, {15, 0}, {52, 0} },

	/* DU-PCIe Connections */
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_DU_PCIE][0]  = { true, {0, 0},  {37, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_DU_PCIE][1]  = { true, {1, 0},  {38, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_DU_PCIE][2]  = { true, {2, 0},  {39, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_DU_PCIE][3]  = { true, {3, 0},  {40, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_DU_PCIE][4]  = { true, {4, 0},  {41, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_DU_PCIE][5]  = { true, {5, 0},  {42, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_DU_PCIE][6]  = { true, {6, 0},  {43, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_DU_PCIE][7]  = { true, {7, 0},  {44, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_DU_PCIE][8]  = { true, {8, 0},  {45, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_DU_PCIE][9]  = { true, {9, 0},  {46, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_DU_PCIE][10] = { true, {10, 0}, {47, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_DU_PCIE][11] = { true, {11, 0}, {48, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_DU_PCIE][12] = { true, {34, 0}, {72, 0} },

	/* DU-L2 Connections */
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_DU_L2][0]    = { true, {0, 0},  {37, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_DU_L2][1]    = { true, {1, 0},  {38, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_DU_L2][2]    = { true, {2, 0},  {39, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_DU_L2][3]    = { true, {3, 0},  {40, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_DU_L2][4]    = { true, {4, 0},  {41, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_DU_L2][5]    = { true, {5, 0},  {42, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_DU_L2][6]    = { true, {6, 0},  {43, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_DU_L2][7]    = { true, {7, 0},  {44, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_DU_L2][8]    = { true, {8, 0},  {45, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_DU_L2][9]    = { true, {9, 0},  {46, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_DU_L2][10]   = { true, {10, 0}, {47, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_DU_L2][11]   = { true, {11, 0}, {48, 0} },
	[ECPRI_HW_V1_0][ECPRI_HW_FLAVOR_DU_L2][12]   = { true, {20, 0}, {57, 0} },

	/* V2 */
	/* RU Connections */
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_RU][0]       = { true, {0, 0},  {37, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_RU][1]       = { true, {1, 0},  {38, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_RU][2]       = { true, {2, 0},  {39, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_RU][3]       = { true, {3, 0},  {40, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_RU][4]       = { true, {4, 0},  {41, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_RU][5]       = { true, {5, 0},  {42, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_RU][6]       = { true, {6, 0},  {43, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_RU][7]       = { true, {7, 0},  {44, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_RU][8]       = { true, {8, 0},  {45, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_RU][9]       = { true, {9, 0},  {46, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_RU][10]      = { true, {10, 0}, {47, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_RU][11]      = { true, {11, 0}, {48, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_RU][12]      = { true, {14, 0}, {51, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_RU][13]      = { true, {15, 0}, {52, 0} },

	/* DU-L2 Connections */
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_L2][0]    = { true, {0, 0},  {37, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_L2][1]    = { true, {1, 0},  {38, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_L2][2]    = { true, {2, 0},  {39, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_L2][3]    = { true, {3, 0},  {40, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_L2][4]    = { true, {4, 0},  {41, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_L2][5]    = { true, {5, 0},  {42, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_L2][6]    = { true, {6, 0},  {43, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_L2][7]    = { true, {7, 0},  {44, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_L2][8]    = { true, {8, 0},  {45, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_L2][9]    = { true, {9, 0},  {46, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_L2][10]   = { true, {10, 0}, {47, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_L2][11]   = { true, {11, 0}, {48, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_L2][12]   = { true, {20, 0}, {57, 0} },

	/* DU-PCIe 4x9 Connections */
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_4_X_9][0] =  { true, {0, 0},  {37, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_4_X_9][1] =  { true, {24, 0}, {61, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_4_X_9][2] =  { true, {25, 0}, {62, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_4_X_9][3] =  { true, {26, 0}, {63, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_4_X_9][4] =  { true, {1, 0},  {38, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_4_X_9][5] =  { true, {27, 0}, {64, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_4_X_9][6] =  { true, {28, 0}, {65, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_4_X_9][7] =  { true, {29, 0}, {66, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_4_X_9][8] =  { true, {2, 0},  {39, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_4_X_9][9] =  { true, {30, 0}, {67, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_4_X_9][10] = { true, {31, 0}, {68, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_4_X_9][11] = { true, {32, 0}, {69, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_4_X_9][12] = { true, {23, 0}, {59, 0} },

	/* DU-PCIe 5x6 Connections */
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_5_X_6][0] =  { true, {0, 0},  {37, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_5_X_6][1] =  { true, {24, 0}, {61, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_5_X_6][2] =  { true, {25, 0}, {62, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_5_X_6][3] =  { true, {26, 0}, {63, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_5_X_6][4] =  { true, {1, 0},  {38, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_5_X_6][5] =  { true, {27, 0}, {64, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_5_X_6][6] =  { true, {28, 0}, {65, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_5_X_6][7] =  { true, {29, 0}, {66, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_5_X_6][8] =  { true, {2, 0},  {39, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_5_X_6][9] =  { true, {30, 0}, {67, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_5_X_6][10] = { true, {31, 0}, {68, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_5_X_6][11] = { true, {32, 0}, {69, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_5_X_6][12] = { true, {23, 0}, {59, 0} },

	/* DU-PCIe 3x12 Connections */
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_3_X_12][0] =  { true, {0, 0},  {37, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_3_X_12][1] =  { true, {24, 0}, {61, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_3_X_12][2] =  { true, {25, 0}, {62, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_3_X_12][3] =  { true, {26, 0}, {63, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_3_X_12][4] =  { true, {1, 0},  {38, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_3_X_12][5] =  { true, {27, 0}, {64, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_3_X_12][6] =  { true, {28, 0}, {65, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_3_X_12][7] =  { true, {29, 0}, {66, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_3_X_12][8] =  { true, {2, 0},  {39, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_3_X_12][9] =  { true, {30, 0}, {67, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_3_X_12][10] = { true, {31, 0}, {68, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_3_X_12][11] = { true, {32, 0}, {69, 0} },
	[ECPRI_HW_V2_0][ECPRI_HW_FLAVOR_DU_PCIE_3_X_12][12] = { true, {23, 0}, {59, 0} },
};

struct ecpri_dma_eth_client_context *ecpri_dma_eth_client_ctx = NULL;

static void ecpri_dma_eth_client_endps_mapping(
	struct ecpri_dma_eth_client_endp_mapping* current_map)
{
	int cnct_id = 0;

	/* Endpoints mapping */
	for (cnct_id = 0;
		cnct_id < ECPRI_DMA_ETH_CLIENT_MAX_CONNTECTIONS; cnct_id++) {
		if (current_map[cnct_id].valid) {
			ecpri_dma_eth_client_ctx->connections[cnct_id].tx_endp_ctx =
				&ecpri_dma_ctx->endp_ctx[current_map[cnct_id].tx_endp.gsi_id]
				[current_map[cnct_id].tx_endp.endp_id];

			ecpri_dma_eth_client_ctx->connections[cnct_id].rx_endp_ctx =
				&ecpri_dma_ctx->endp_ctx[current_map[cnct_id].rx_endp.gsi_id]
				[current_map[cnct_id].rx_endp.endp_id];
		}
	}
}

static struct ecpri_dma_eth_client_connection*
ecpri_dma_eth_client_get_conn_from_hdl (ecpri_dma_eth_conn_hdl_t hdl) {
	struct ecpri_dma_eth_client_connection *connection;

	spin_lock_bh(&ecpri_dma_eth_client_ctx->idr_lock);
	connection = idr_find(&ecpri_dma_eth_client_ctx->idr, hdl);
	spin_unlock_bh(&ecpri_dma_eth_client_ctx->idr_lock);

	return connection;
}

static void ecpri_dma_eth_client_register_ready(void *user_data)
{
	u32 hw_ver = ecpri_dma_get_ctx_hw_ver();
	u32 hw_flavor = ecpri_dma_get_ctx_hw_flavor();

	struct ecpri_dma_eth_client_endp_mapping *current_map;

	DMADBG_LOW("Begin\n");

	if ((ECPRI_HW_MAX == hw_ver) || (ECPRI_HW_FLAVOR_MAX == hw_flavor)) {
		DMAERR(
			"Wrong HW or Flavor versions hw_ver: %d hw_flavor = %d\n",
			 hw_ver, hw_flavor);
		return;
	}

	current_map = &eth_client_endp_map[hw_ver][hw_flavor][0];

	if (!ecpri_dma_eth_client_ctx || !ecpri_dma_eth_client_ctx->ready_cb) {
		DMAERR("ETH Ready Callback is NULL\n");
		return;
	}

	ecpri_dma_eth_client_ctx->link_to_endp_mapping = current_map;

	/* Endpoints mapping */
	ecpri_dma_eth_client_endps_mapping(current_map);

	ecpri_dma_eth_client_ctx->is_eth_ready = true;
	ecpri_dma_eth_client_ctx->ready_cb(user_data);

	mutex_lock(&ecpri_dma_eth_client_ctx->lock);
	ecpri_dma_eth_client_ctx->is_eth_notified_ready = true;
	mutex_unlock(&ecpri_dma_eth_client_ctx->lock);

	DMADBG("Succeeded\n");
}

static void dma_eth_client_tx_comp_hdlr(
	struct ecpri_dma_endp_context *endp,
	struct ecpri_dma_pkt_completion_wrapper **comp_pkt,
	u32 num_of_completed)
{
	struct ecpri_dma_eth_client_connection *connection;

	DMADBG_LOW("Begin\n");

	if (!ecpri_dma_eth_client_ctx
	    || !ecpri_dma_eth_client_ctx->is_eth_ready) {
		DMAERR("Context not initialized\n");
		return;
	}

	/* Retrieve Connection */
	connection = ecpri_dma_eth_client_get_conn_from_hdl(endp->hdl);
	if (!connection || !connection->valid) {
		DMAERR("Connection invalid handle:%x, ENDP ID:%d\n", endp->hdl,
			endp->endp_id);
		return;
	}

	ecpri_dma_eth_client_ctx->tx_comp_cb(
		ecpri_dma_eth_client_ctx->tx_comp_cb_user_data,
		connection->hdl, comp_pkt, num_of_completed);

	DMADBG_LOW("Exit\n");
}

static void dma_eth_client_tx_poll_comp_hdlr(
	struct ecpri_dma_endp_context *endp,
	struct ecpri_dma_pkt_completion_wrapper **comp_pkt,
	u32 num_of_completed)
{
	struct ecpri_dma_eth_client_connection *connection;

	DMADBG_LOW("Begin\n");

	if (!ecpri_dma_eth_client_ctx
	    || !ecpri_dma_eth_client_ctx->is_eth_ready) {
		DMAERR("Context not initialized\n");
		return;
	}

	/* Retrieve Connection */
	connection = ecpri_dma_eth_client_get_conn_from_hdl(endp->hdl);
	if (!connection || !connection->valid) {
		DMAERR("Connection invalid handle:%x, ENDP ID:%d\n", endp->hdl,
			endp->endp_id);
		return;
	}

	if (connection->tx_notify_mode == ECPRI_DMA_NOTIFY_MODE_IRQ) {
		/* Move connection to POLL mode, GSI alredy moved to poll */
		connection->tx_notify_mode = ECPRI_DMA_NOTIFY_MODE_POLL;

		/* Handle IRQ mode */
		ecpri_dma_eth_client_ctx->tx_irq_comp_cb(
			ecpri_dma_eth_client_ctx->tx_irq_comp_cb_user_data,
			connection->hdl);
	}
	else {
		/* Handle POLL mode*/
		connection->received_tx_irq_during_poll++;
	}

	DMADBG_LOW("Exit\n");
}

static void dma_eth_client_rx_comp_hdlr(
	struct ecpri_dma_endp_context *endp,
	struct ecpri_dma_pkt_completion_wrapper **comp_pkt,
	u32 num_of_completed)
{
	struct ecpri_dma_eth_client_connection *connection;

	DMADBG_LOW("Begin\n");

	if (!ecpri_dma_eth_client_ctx
	    || !ecpri_dma_eth_client_ctx->is_eth_ready) {
		DMAERR("Context not initialized\n");
		return;
	}

	/* Retrieve Connection */
	connection = ecpri_dma_eth_client_get_conn_from_hdl(endp->hdl);
	if (!connection || !connection->valid) {
		DMAERR("Connection invalid handle:%x, ENDP ID:%d\n", endp->hdl,
			endp->endp_id);
		return;
	}

	if (connection->rx_notify_mode == ECPRI_DMA_NOTIFY_MODE_IRQ) {
		/* Move connection to POLL mode, GSI alredy moved to poll */
		connection->rx_notify_mode = ECPRI_DMA_NOTIFY_MODE_POLL;

		/* Handle IRQ mode */
		ecpri_dma_eth_client_ctx->rx_comp_cb(
			ecpri_dma_eth_client_ctx->rx_comp_cb_user_data,
			connection->hdl);
	} else {
		/* Handle POLL mode*/
		connection->received_irq_during_poll++;
	}

	DMADBG_LOW("Exit\n");
}

/**
 * Parameters are being verified outside of this function and there's no need
 * to verify them again.
 */
static u32 ecpri_dma_eth_client_conn_hdl_alloc(void *ptr)
{
	ecpri_dma_eth_conn_hdl_t hdl;

	idr_preload(GFP_KERNEL);

	spin_lock_bh(&ecpri_dma_eth_client_ctx->idr_lock);
	hdl = idr_alloc(&ecpri_dma_eth_client_ctx->idr, ptr,
		ECPRI_DMA_ETH_CLIENT_MIN_CONNECTION_ID, 0, GFP_NOWAIT);
	spin_unlock_bh(&ecpri_dma_eth_client_ctx->idr_lock);

	idr_preload_end();

	return hdl;
}

/**
 * Parameters are being verified outside of this function and there's no need
 * to verify them again.
 */
static void ecpri_dma_eth_client_conn_hdl_remove(ecpri_dma_eth_conn_hdl_t hdl) {
	spin_lock_bh(&ecpri_dma_eth_client_ctx->idr_lock);
	idr_remove(&ecpri_dma_eth_client_ctx->idr, hdl);
	spin_unlock_bh(&ecpri_dma_eth_client_ctx->idr_lock);
}

int ecpri_dma_eth_client_init(void)
{
	DMADBG("eCPRI DMA ETH Client init\n");

	/* Check if the context was already initialized */
	if (ecpri_dma_eth_client_ctx)
		return 0;

	ecpri_dma_eth_client_ctx = kzalloc(sizeof(*ecpri_dma_eth_client_ctx),
		GFP_KERNEL);
	if (!ecpri_dma_eth_client_ctx) {
		DMAERR("Failed to allocate dma_eth_client ctx\n");
		return -ENOMEM;
	}

	mutex_init(&ecpri_dma_eth_client_ctx->lock);
	ecpri_dma_eth_client_ctx->is_eth_ready = false;
	ecpri_dma_eth_client_ctx->is_eth_notified_ready = false;

	idr_init(&ecpri_dma_eth_client_ctx->idr);
	spin_lock_init(&ecpri_dma_eth_client_ctx->idr_lock);

	DMADBG_LOW("Exit\n");

	return 0;
}

int ecpri_dma_eth_client_destroy(void)
{
	DMADBG("eCPRI DMA ETH Client destroy\n");

	/* Check if the context is allocated */
	if (!ecpri_dma_eth_client_ctx)
		return 0;

	mutex_destroy(&ecpri_dma_eth_client_ctx->lock);
	idr_destroy(&ecpri_dma_eth_client_ctx->idr);

	kfree(ecpri_dma_eth_client_ctx);
	ecpri_dma_eth_client_ctx = NULL;

	DMADBG_LOW("Exit\n");

	return 0;
}

int ecpri_dma_eth_register(struct ecpri_dma_eth_register_params *ready_info,
	bool *is_dma_ready)
{
	int ret = 0;
	bool ready = false;
	u32 hw_ver = 0, hw_flavor = 0;

	struct ecpri_dma_eth_client_endp_mapping *current_map = NULL;

	DMADBG_LOW("Begin\n");

	/* Params are mandatory except for ready_info->notify_tx_comp_irq */
	if (!ready_info || !ready_info->notify_ready
	    || !ready_info->notify_rx_comp || !ready_info->notify_tx_comp
	    || !is_dma_ready) {
		DMAERR("Invalid paramteres\n");
		return -EINVAL;
	}

	if (ecpri_dma_eth_client_ctx
	    && ecpri_dma_eth_client_ctx->is_eth_ready) {
		DMAERR("Context is already initialized\n");
		return -EPERM;
	}

	ret = ecpri_dma_eth_client_init();
	if (ret){
		DMAERR("Failed to init ETH client\n");
		return ret;
	}

	/* Register callbacks*/
	ecpri_dma_eth_client_ctx->ready_cb
		= ready_info->notify_ready;
	ecpri_dma_eth_client_ctx->ready_cb_user_data
		= ready_info->userdata_ready;

	ecpri_dma_eth_client_ctx->tx_comp_cb
		= ready_info->notify_tx_comp;
	ecpri_dma_eth_client_ctx->tx_comp_cb_user_data
		= ready_info->userdata_tx;

	ecpri_dma_eth_client_ctx->rx_comp_cb
		= ready_info->notify_rx_comp;
	ecpri_dma_eth_client_ctx->rx_comp_cb_user_data
		= ready_info->userdata_rx;

	ecpri_dma_eth_client_ctx->tx_irq_comp_cb
		= ready_info->notify_tx_comp_irq;
	ecpri_dma_eth_client_ctx->tx_irq_comp_cb_user_data
		= ready_info->userdata_tx_irq;

	/* Check DMA driver state */

	mutex_lock(&ecpri_dma_ctx->lock);
	ready = ecpri_dma_is_ready();
	mutex_unlock(&ecpri_dma_ctx->lock);

	if (!ready) {
		ret = ecpri_dma_register_ready_cb(
			&ecpri_dma_eth_client_register_ready,
			ready_info->userdata_ready);

		/*
		 * If the call to ecpri_dma_register_ready_cb() above
		 * returns 0, this means that we've succeeded in
		 * queuing up a future call to ecpri_dma_ut_framework_init()
		 * and that the call to it will be made once the DMA
		 * becomes ready.  If this is the case, the call to
		 * ecpri_dma_ut_framework_init() below need not be made.
		 *
		 * If the call to ecpri_dma_register_ready_cb() above
		 * returns -EEXIST, it means that during the call to
		 * ecpri_dma_register_ready_cb(), the DMA has become
		 * ready, and hence, no indirect call to
		 * ecpri_dma_ut_framework_init() will be made, so we need to
		 * call it ourselves below.
		 *
		 * If the call to ecpri_dma_register_ready_cb() above
		 * return something other than 0 or -EEXIST, that's a
		 * hard error.
		 */

		if (ret == -EEXIST) {
			ready = true;
		} else {
			if (ret != 0) {
				DMAERR("DMA ETH client Register failed - %d\n",
					ret);
				return ret;
			}
		}
	}

	if (ready) {
		hw_ver = ecpri_dma_get_ctx_hw_ver();
		hw_flavor = ecpri_dma_get_ctx_hw_flavor();

        if ((hw_ver < ECPRI_HW_MAX) && (hw_flavor < ECPRI_HW_FLAVOR_MAX)) {
            current_map = &eth_client_endp_map[hw_ver][hw_flavor][0];
        } else {
            DMAERR("HW ver/flavor out of bounds");
            return -EINVAL;
        }

		ecpri_dma_eth_client_ctx->link_to_endp_mapping = current_map;

		/* Endpoints mapping */
		ecpri_dma_eth_client_endps_mapping(current_map);

		ecpri_dma_eth_client_ctx->is_eth_ready = true;
	}

	*(is_dma_ready) = ready;

	DMADBG_LOW("Exit\n");

	return ret;
}

void ecpri_dma_eth_deregister(void)
{
	DMADBG_LOW("Begin\n");

	if (!ecpri_dma_eth_client_ctx
	    || !ecpri_dma_eth_client_ctx->is_eth_ready) {
		DMAERR("Context is not initialized\n");
		return;
	}

	ecpri_dma_eth_client_ctx->is_eth_ready		= false;
	ecpri_dma_eth_client_ctx->is_eth_notified_ready = false;

	ecpri_dma_eth_client_ctx->ready_cb              = NULL;
	ecpri_dma_eth_client_ctx->ready_cb_user_data    = NULL;

	ecpri_dma_eth_client_ctx->tx_comp_cb            = NULL;
	ecpri_dma_eth_client_ctx->tx_comp_cb_user_data  = NULL;

	ecpri_dma_eth_client_ctx->rx_comp_cb            = NULL;
	ecpri_dma_eth_client_ctx->rx_comp_cb_user_data  = NULL;

	ecpri_dma_eth_client_ctx->tx_irq_comp_cb = NULL;
	ecpri_dma_eth_client_ctx->tx_irq_comp_cb_user_data = NULL;

	DMADBG_LOW("Exit\n");
}

int ecpri_dma_eth_connect_endpoints(
	struct ecpri_dma_eth_endpoint_connect_params *params,
	ecpri_dma_eth_conn_hdl_t *hdl)
{
	int ret = 0;
	struct ecpri_dma_eth_client_connection *connection;
	struct ecpri_dma_moderation_config irq_mod_cfg = { 1, 0 };
	struct ecpri_dma_moderation_config* curr_tx_mod_cfg;
	client_notify_comp tx_notify_comp;

	DMADBG_LOW("Begin\n");

    if (NULL == ecpri_dma_eth_client_ctx) {
        DMAERR("Context pointer is NULL\n");
        return -EINVAL;
    }

	if (!hdl || !params ||
	params->link_index > ECPRI_DMA_ETH_CLIENT_MAX_CONNTECTIONS ||
		params->rx_ring_length == 0 || params->tx_ring_length == 0 ||
		params->p_type >= ECPRI_DMA_ENDP_STREAM_DEST_MAX ||
		!ecpri_dma_eth_client_ctx->
		link_to_endp_mapping[params->link_index].valid) {
		DMAERR("Invalid paramteres\n");
		return -EINVAL;
	}

	if (!ecpri_dma_eth_client_ctx
	    || !ecpri_dma_eth_client_ctx->is_eth_ready) {
		DMAERR("Context not initialized\n");
		return -EPERM;
	}

	/* Retrieve Connection */
	connection = &ecpri_dma_eth_client_ctx->connections[params->link_index];
	if (connection->valid) {
		DMAERR("Connection is already connected link_index: %d\n",
			params->link_index);
		return -EINVAL;
	}

	connection->enable_tx_poll = params->enable_tx_poll;

	if (connection->enable_tx_poll) {
		curr_tx_mod_cfg = &irq_mod_cfg;
		tx_notify_comp = &dma_eth_client_tx_poll_comp_hdlr;
	}
	else {
		curr_tx_mod_cfg = &params->tx_mod_cfg;
		tx_notify_comp = &dma_eth_client_tx_comp_hdlr;
	}

	ret = ecpri_dma_alloc_endp(
		ecpri_dma_eth_client_ctx->
		link_to_endp_mapping[params->link_index].tx_endp.gsi_id,
		ecpri_dma_eth_client_ctx->
		link_to_endp_mapping[params->link_index].tx_endp.endp_id,
		params->tx_ring_length, curr_tx_mod_cfg, false,
		tx_notify_comp, connection->enable_tx_poll);

	if (ret != 0) {
		DMAERR("Unable to allocate Tx ENDP, ENDP ID:%d, GSI ID %d\n",
			ecpri_dma_eth_client_ctx->
			link_to_endp_mapping[params->link_index].tx_endp.endp_id,
			ecpri_dma_eth_client_ctx->
			link_to_endp_mapping[params->link_index].tx_endp.gsi_id);
		return ret;
	}

	ret = ecpri_dma_alloc_endp(
		ecpri_dma_eth_client_ctx->
		link_to_endp_mapping[params->link_index].rx_endp.gsi_id,
		ecpri_dma_eth_client_ctx->
		link_to_endp_mapping[params->link_index].rx_endp.endp_id,
		params->rx_ring_length, &irq_mod_cfg, false,
		&dma_eth_client_rx_comp_hdlr, false);

	if (ret != 0) {
		DMAERR("Unable to allocate Rx ENDP, ENDP ID:%d, GSI ID %d\n",
			ecpri_dma_eth_client_ctx->
			link_to_endp_mapping[params->link_index].rx_endp.endp_id,
			ecpri_dma_eth_client_ctx->
			link_to_endp_mapping[params->link_index].rx_endp.gsi_id);
		return ret;
	}

	/* Enable/disable Tx header */
	connection->tx_endp_ctx->tx_pre_header_enabled =
		params->enable_tx_pre_header;

	ret = ecpri_dma_set_tx_pre_header(connection->tx_endp_ctx);
	if (ret != 0) {
		DMAERR("Unable to set Tx header, ENDP ID:%d\n",
			ecpri_dma_eth_client_ctx->
			link_to_endp_mapping[params->link_index].tx_endp.endp_id);
		return -EINVAL;
	}

	ret = ecpri_dma_enable_dma_endp(connection->tx_endp_ctx);
	if (ret != 0) {
		DMAERR("Unable to enable Tx endpoint, ENDP ID:%d\n",
			ecpri_dma_eth_client_ctx->
			link_to_endp_mapping[params->link_index].tx_endp.endp_id);
		return -EINVAL;
	}

	ret = ecpri_dma_enable_dma_endp(connection->rx_endp_ctx);
	if (ret != 0) {
		DMAERR("Unable to enable Rx endpoint, ENDP ID:%d\n",
			ecpri_dma_eth_client_ctx->
			link_to_endp_mapping[params->link_index].rx_endp.endp_id);
		return -EINVAL;
	}

	/* Connection allocation */
	connection->valid = true;

	*(hdl) = ecpri_dma_eth_client_conn_hdl_alloc((void *)connection);
	connection->hdl = *(hdl);
	connection->tx_endp_ctx->hdl = *(hdl);
	connection->rx_endp_ctx->hdl = *(hdl);
	connection->received_irq_during_poll = 0;

	connection->p_type = params->p_type;
	connection->link_idx = params->link_index;
	connection->rx_notify_mode = ECPRI_DMA_NOTIFY_MODE_IRQ;
	connection->tx_notify_mode = ECPRI_DMA_NOTIFY_MODE_IRQ;

	connection->tx_mod_cfg.moderation_counter_threshold =
		params->tx_mod_cfg.moderation_counter_threshold;
	connection->tx_mod_cfg.moderation_timer_threshold =
		params->tx_mod_cfg.moderation_timer_threshold;

	DMADBG_LOW("Exit\n");

	return ret;
}

int ecpri_dma_eth_disconnect_endpoints(ecpri_dma_eth_conn_hdl_t hdl)
{
	int ret = 0;
	struct ecpri_dma_eth_client_connection *connection;

	DMADBG_LOW("Begin\n");

	if (ecpri_dma_get_ctx_hw_ver() == ECPRI_HW_V1_0) {
		DMAERR("Disconnect not supported for v1\n");
		return -EPERM;
	}

	if (!ecpri_dma_eth_client_ctx
		|| !ecpri_dma_eth_client_ctx->is_eth_ready) {
		DMAERR("Context not initialized\n");
		return -EPERM;
	}

	/* Retrieve Connection */
	connection = ecpri_dma_eth_client_get_conn_from_hdl(hdl);
	if (!connection || !connection->valid) {
		DMAERR("Connection invalid handle:%x\n", hdl);
		return -EINVAL;
	}

	ecpri_dma_eth_client_conn_hdl_remove(connection->hdl);

	ret = ecpri_dma_reset_endp(connection->tx_endp_ctx);
	if (ret != 0) {
		DMAERR("Unable to reset Tx endpoint, ENDP ID:%d\n",
			connection->tx_endp_ctx->endp_id);
		return -EINVAL;
	}

	/* Deallocation of GSI channels */
	ret = ecpri_dma_dealloc_endp(connection->tx_endp_ctx);

	if (ret != 0) {
		DMAERR("Unable to de-allocate Tx endpoint, ENDP ID:%d\n",
			connection->tx_endp_ctx->endp_id);
		return -EINVAL;
	}

	ret = ecpri_dma_reset_endp(connection->rx_endp_ctx);
	if (ret != 0) {
		DMAERR("Unable to reset Rx endpoint, ENDP ID:%d\n",
			connection->rx_endp_ctx->endp_id);
		return -EINVAL;
	}

	ret = ecpri_dma_dealloc_endp(connection->rx_endp_ctx);
	if (ret != 0) {
		DMAERR("Unable to de-allocate Rx endpoint, ENDP ID:%d\n",
			connection->rx_endp_ctx->endp_id);
		return -EINVAL;
	}

	connection->tx_endp_ctx->hdl = 0;
	connection->rx_endp_ctx->hdl = 0;

	connection->valid = false;
	connection->hdl = 0;
	connection->p_type = 0;
	connection->rx_notify_mode = ECPRI_DMA_NOTIFY_MODE_IRQ;
	connection->tx_notify_mode = ECPRI_DMA_NOTIFY_MODE_IRQ;
	connection->link_idx = 0;
	connection->received_irq_during_poll = 0;
	connection->tx_mod_cfg.moderation_timer_threshold = 0;
	connection->tx_mod_cfg.moderation_counter_threshold = 0;

	DMADBG_LOW("Exit\n");

	return ret;
}

int ecpri_dma_eth_start_endpoints(ecpri_dma_eth_conn_hdl_t hdl)
{
	int ret = 0;
	struct ecpri_dma_eth_client_connection *connection;

	DMADBG_LOW("Begin\n");

	if (!ecpri_dma_eth_client_ctx
	    || !ecpri_dma_eth_client_ctx->is_eth_ready) {
		DMAERR("Context not initialized\n");
		return -EPERM;
	}

	/* Retrieve Connection */
	connection = ecpri_dma_eth_client_get_conn_from_hdl(hdl);

	if (!connection) {
		DMAERR("NULL pointer to connection\n");
		return -EINVAL;
	}

	if (!connection->valid) {
		DMAERR("Connection invalid handle:%x, ENDP ID:%d\n", hdl,
			connection->tx_endp_ctx->endp_id);
		return -EINVAL;
	}

	/* Starting GSI CH */
	ret = ecpri_dma_start_endp(connection->tx_endp_ctx);
	if (ret != 0) {
		DMAERR("Unable to start channel - Tx, ENDP ID:%d\n",
			connection->tx_endp_ctx->endp_id);
		return -EINVAL;
	}

	ret = ecpri_dma_start_endp(connection->rx_endp_ctx);
	if (ret != 0) {
		DMAERR("Unable to start channel - Rx, ENDP ID:%d\n",
			connection->rx_endp_ctx->endp_id);
		return -EINVAL;
	}

	DMADBG_LOW("Exit\n");

	return ret;
}

int ecpri_dma_eth_stop_endpoints(ecpri_dma_eth_conn_hdl_t hdl)
{
	int ret = 0;
	struct ecpri_dma_eth_client_connection *connection;

	DMADBG_LOW("Begin\n");

	if (!ecpri_dma_eth_client_ctx
	    || !ecpri_dma_eth_client_ctx->is_eth_ready) {
		DMAERR("Context not initialized\n");
		return -EPERM;
	}

	/* Retrieve Connection */
	connection = ecpri_dma_eth_client_get_conn_from_hdl(hdl);
	if (!connection) {
		DMAERR("NULL pointer to connection\n");
		return -EINVAL;
	}

	if (!connection->valid) {
		DMAERR("Connection invalid handle:%x, ENDP ID:%d\n", hdl,
			connection->tx_endp_ctx->endp_id);
		return -EINVAL;
	}


	/* Stopping GSI CH */
	ret = ecpri_dma_stop_endp(connection->tx_endp_ctx);
	if (ret != 0) {
		DMAERR("Unable to stop channel - Tx, ENDP ID:%d\n",
			connection->tx_endp_ctx->endp_id);
		return -EINVAL;
	}

	ret = ecpri_dma_stop_endp(connection->rx_endp_ctx);
	if (ret != 0) {
		DMAERR("Unable to stop channel - Rx, ENDP ID:%d\n",
			connection->rx_endp_ctx->endp_id);
		return -EINVAL;
	}

	DMADBG_LOW("Exit\n");

	return ret;
}

int ecpri_dma_eth_transmit(ecpri_dma_eth_conn_hdl_t hdl,
	struct ecpri_dma_pkt **pkts, u32 num_of_pkts, bool commit)
{
	int ret = 0;
	struct ecpri_dma_eth_client_connection *connection;
	u32 num_of_pkts_remain = num_of_pkts;
	u32 num_of_pkts_to_send = num_of_pkts;
	bool commit_transmit = false;

	DMADBG_LOW("Begin\n");

	if (!ecpri_dma_eth_client_ctx
	    || !ecpri_dma_eth_client_ctx->is_eth_ready) {
		DMAERR("Context not initialized\n");
		return -EPERM;
	}

	if(!pkts || num_of_pkts == 0){
		DMAERR("Invalid parameters\n");
		return -EINVAL;
	}

	/* Retrieve Connection */
	connection = ecpri_dma_eth_client_get_conn_from_hdl(hdl);
	if (!connection || !connection->valid) {
		DMAERR("Connection invalid handle:%x\n", hdl);
		return -EINVAL;
	}

	/* Transmit */
	while (num_of_pkts_remain) {
		if (num_of_pkts_remain > ECPRI_DMA_DP_MAX_DESC) {
			num_of_pkts_to_send = ECPRI_DMA_DP_MAX_DESC;
			commit_transmit = false;
		}
		else {
			num_of_pkts_to_send = num_of_pkts_remain;
			commit_transmit = commit;
		}

		ret = ecpri_dma_dp_transmit(connection->tx_endp_ctx, pkts,
			num_of_pkts_to_send, commit_transmit);
		if (ret != 0) {
			DMAERR("Unable to transmit, handle:%x, ENDP ID:%d\n",
				hdl, connection->tx_endp_ctx->endp_id);
			return -EINVAL;
		}
		pkts += num_of_pkts_to_send;
		num_of_pkts_remain -= num_of_pkts_to_send;
	}

	DMADBG_LOW("Exit\n");

	return ret;
}

int ecpri_dma_eth_commit(ecpri_dma_eth_conn_hdl_t hdl)
{
	int ret = 0;
	struct ecpri_dma_eth_client_connection *connection;

	DMADBG_LOW("Begin\n");

	if (!ecpri_dma_eth_client_ctx
	    || !ecpri_dma_eth_client_ctx->is_eth_ready) {
		DMAERR("Context not initialized\n");
		return -EPERM;
	}

	/* Retrieve Connection */
	connection = ecpri_dma_eth_client_get_conn_from_hdl(hdl);
	if (!connection || !connection->valid) {
		DMAERR("Connection invalid handle:%x\n", hdl);
		return -EINVAL;
	}

	ret = ecpri_dma_dp_commit(connection->tx_endp_ctx);
	if (ret != 0) {
		DMAERR("Unable to commit, handle:%x, ENDP ID:%d\n", hdl,
			connection->tx_endp_ctx->endp_id);
		return -EINVAL;
	}

	DMADBG_LOW("Exit\n");

	return ret;
}

int ecpri_dma_eth_tx_ring_state(ecpri_dma_eth_conn_hdl_t hdl,
	u32 *available)
{
	int ret = 0;
	struct ecpri_dma_eth_client_connection *connection;

	DMADBG_LOW("Begin\n");

	if (!ecpri_dma_eth_client_ctx
	    || !ecpri_dma_eth_client_ctx->is_eth_ready) {
		DMAERR("Context not initialized\n");
		return -EPERM;
	}

	if(!available){
		DMAERR("Invalid parameters\n");
		return -EINVAL;
	}

	/* Retrieve Connection */
	connection = ecpri_dma_eth_client_get_conn_from_hdl(hdl);
	if (!connection) {
		DMAERR("NULL pointer to connection\n");
		return -EINVAL;
	}

	if (!connection->valid) {
		DMAERR("Connection invalid handle:%x, ENDP ID:%d\n", hdl,
			connection->tx_endp_ctx->endp_id);
		return -EINVAL;
	}

	*(available) = connection->tx_endp_ctx->ring_length -
		connection->tx_endp_ctx->curr_outstanding_num;

	DMADBG_LOW("Exit\n");

	return ret;
}

int ecpri_dma_eth_rx_ring_state(ecpri_dma_eth_conn_hdl_t hdl,
	u32 *available)
{
	int ret = 0;
	struct ecpri_dma_eth_client_connection *connection;

	DMADBG_LOW("Begin\n");

	if (!ecpri_dma_eth_client_ctx
	    || !ecpri_dma_eth_client_ctx->is_eth_ready) {
		DMAERR("Context not initialized\n");
		return -EPERM;
	}

	if(!available){
		DMAERR("Invalid parameters\n");
		return -EINVAL;
	}

	/* Retrieve Connection */
	connection = ecpri_dma_eth_client_get_conn_from_hdl(hdl);
	if (!connection) {
		DMAERR("NULL pointer to connection\n");
		return -EINVAL;
	}

	if (!connection->valid) {
		DMAERR("Connection invalid handle:%x, ENDP ID:%d\n", hdl,
			connection->tx_endp_ctx->endp_id);
		return -EINVAL;
	}

	*(available) = connection->rx_endp_ctx->ring_length -
		connection->rx_endp_ctx->curr_outstanding_num;

	DMADBG_LOW("Exit\n");

	return ret;
}

int ecpri_dma_eth_rx_mode_set(ecpri_dma_eth_conn_hdl_t hdl,
	enum ecpri_dma_notify_mode mode)
{
	int ret = 0;
	struct ecpri_dma_eth_client_connection *connection;

	DMADBG_LOW("Begin\n");

	if(mode >= ECPRI_DMA_NOTIFY_MODE_MAX) {
		DMAERR("Invalid parameters\n");
		return -EINVAL;
	}

	/* Retrieve Connection */
	connection = ecpri_dma_eth_client_get_conn_from_hdl(hdl);
	if (!connection) {
		DMAERR("NULL pointer to connection\n");
		return -EINVAL;
	}

	if (!connection->valid) {
		DMAERR("Connection invalid handle:%x, ENDP ID:%d\n", hdl,
			connection->rx_endp_ctx->endp_id);
		return -EINVAL;
	}

	connection->rx_notify_mode = mode;

	ret = ecpri_dma_set_endp_mode(connection->rx_endp_ctx, mode);
	if (ret != 0) {
		DMAERR("Unable to set Rx mode, handle:%x, ENDP ID:%d,"
		       "Current mode: %d, New mode: %d, \n", hdl,
			connection->rx_endp_ctx->endp_id,
			connection->rx_notify_mode, mode);
		return -EINVAL;
	}

	DMADBG_LOW("Exit\n");

	return ret;
}

int ecpri_dma_eth_rx_mode_get(ecpri_dma_eth_conn_hdl_t hdl,
	enum ecpri_dma_notify_mode *mode)
{
	int ret = 0;
	struct ecpri_dma_eth_client_connection *connection;

	DMADBG_LOW("Begin\n");

	if(!mode) {
		DMAERR("Invalid parameters\n");
		return -EINVAL;
	}

	/* Retrieve Connection */
	connection = ecpri_dma_eth_client_get_conn_from_hdl(hdl);
	if (!connection) {
		DMAERR("NULL pointer to connection\n");
		return -EINVAL;
	}

	if (!connection->valid) {
		DMAERR("Connection invalid handle:%x, ENDP ID:%d\n", hdl,
			connection->rx_endp_ctx->endp_id);
		return -EINVAL;
	}

	ret = ecpri_dma_get_endp_mode(connection->rx_endp_ctx, mode);
	if (ret != 0) {
		DMAERR("Unable to get Rx mode, handle:%x, ENDP ID:%d\n", hdl,
			connection->rx_endp_ctx->endp_id);
		return -EINVAL;
	}

	DMADBG_LOW("Exit\n");

	return ret;
}

int ecpri_dma_eth_rx_poll(ecpri_dma_eth_conn_hdl_t hdl, u32 budget,
	struct ecpri_dma_pkt_completion_wrapper **pkts, u32 *actual_num)
{
	int ret = 0;
	struct ecpri_dma_eth_client_connection *connection;

	DMADBG_LOW("Begin\n");

	if (!pkts || !actual_num) {
		DMAERR("Invalid parameters\n");
		return -EINVAL;
	}

	/* Retrieve Connection */
	connection = ecpri_dma_eth_client_get_conn_from_hdl(hdl);
	if (!connection) {
		DMAERR("NULL pointer to connection\n");
		return -EINVAL;
	}

	if (!connection->valid) {
		DMAERR("Connection invalid handle:%x, ENDP ID:%d\n", hdl,
			connection->rx_endp_ctx->endp_id);
		return -EINVAL;
	}

	ret = ecpri_dma_dp_poll(connection->rx_endp_ctx, budget, pkts,
		actual_num);
	if (ret != 0) {
		DMAERR("Unable to perform Rx Poll, handle:%x, ENDP ID:%d\n", hdl,
			connection->rx_endp_ctx->endp_id);
		return -EINVAL;
	}

	DMADBG_LOW("Exit\n");

	return ret;
}

int ecpri_dma_eth_tx_mode_set(ecpri_dma_eth_conn_hdl_t hdl,
	enum ecpri_dma_notify_mode mode)
{
	int ret = 0;
	struct ecpri_dma_eth_client_connection *connection;

	DMADBG_LOW("Begin\n");

	if(mode >= ECPRI_DMA_NOTIFY_MODE_MAX) {
		DMAERR("Invalid parameters\n");
		return -EINVAL;
	}

	/* Retrieve Connection */
	connection = ecpri_dma_eth_client_get_conn_from_hdl(hdl);
	if (!connection) {
		DMAERR("NULL pointer to connection\n");
		return -EINVAL;
	}

	if (!connection->valid) {
		DMAERR("Connection invalid handle:%x, ENDP ID:%d\n", hdl,
			connection->tx_endp_ctx->endp_id);
		return -EINVAL;
	}

	connection->tx_notify_mode = mode;

	ret = ecpri_dma_set_endp_mode(connection->tx_endp_ctx, mode);
	if (ret != 0) {
		DMAERR("Unable to set Tx mode, handle:%x, ENDP ID:%d,"
		       "Current mode: %d, New mode: %d, \n", hdl,
			connection->tx_endp_ctx->endp_id,
			connection->tx_notify_mode, mode);
		return -EINVAL;
	}

	DMADBG_LOW("Exit\n");

	return ret;
}

int ecpri_dma_eth_tx_mode_get(ecpri_dma_eth_conn_hdl_t hdl,
	enum ecpri_dma_notify_mode *mode)
{
	int ret = 0;
	struct ecpri_dma_eth_client_connection *connection;

	DMADBG_LOW("Begin\n");

	if(!mode) {
		DMAERR("Invalid parameters\n");
		return -EINVAL;
	}

	/* Retrieve Connection */
	connection = ecpri_dma_eth_client_get_conn_from_hdl(hdl);
	if (!connection) {
		DMAERR("NULL pointer to connection\n");
		return -EINVAL;
	}

	if (!connection->valid) {
		DMAERR("Connection invalid handle:%x, ENDP ID:%d\n", hdl,
			connection->tx_endp_ctx->endp_id);
		return -EINVAL;
	}

	ret = ecpri_dma_get_endp_mode(connection->tx_endp_ctx, mode);
	if (ret != 0) {
		DMAERR("Unable to get Tx mode, handle:%x, ENDP ID:%d\n", hdl,
			connection->tx_endp_ctx->endp_id);
		return -EINVAL;
	}

	DMADBG_LOW("Exit\n");

	return ret;
}

int ecpri_dma_eth_tx_poll(ecpri_dma_eth_conn_hdl_t hdl, u32 budget,
	struct ecpri_dma_pkt_completion_wrapper **pkts, u32 *actual_num)
{
	int ret = 0;
	struct ecpri_dma_eth_client_connection *connection;

	DMADBG_LOW("Begin\n");

	if (!pkts || !actual_num) {
		DMAERR("Invalid parameters\n");
		return -EINVAL;
	}

	/* Retrieve Connection */
	connection = ecpri_dma_eth_client_get_conn_from_hdl(hdl);
	if (!connection) {
		DMAERR("NULL pointer to connection\n");
		return -EINVAL;
	}

	if (!connection->valid) {
		DMAERR("Connection invalid handle:%x, ENDP ID:%d\n", hdl,
			connection->tx_endp_ctx->endp_id);
		return -EINVAL;
	}

	if (!connection->enable_tx_poll) {
		DMAERR("Connection tx poll not enabled handle:%x\n", hdl);
		return -EPERM;
	}

	ret = ecpri_dma_dp_poll(connection->tx_endp_ctx, budget, pkts,
		actual_num);
	if (ret != 0) {
		DMAERR("Unable to perform Tx Poll, handle:%x, ENDP ID:%d\n", hdl,
			connection->tx_endp_ctx->endp_id);
		return -EINVAL;
	}

	DMADBG_LOW("Exit\n");

	return ret;
}

int ecpri_dma_eth_replenish_buffers(ecpri_dma_eth_conn_hdl_t hdl,
	struct ecpri_dma_pkt **pkts, u32 num_of_pkts, bool commit)
{
	int ret;
	struct ecpri_dma_eth_client_connection *connection;
	u32 num_of_pkts_remain = num_of_pkts;
	u32 num_of_pkts_to_send = num_of_pkts;

	DMADBG_LOW("Begin\n");

	if (!pkts || num_of_pkts == 0) {
		DMAERR("Invalid parameters\n");
		return -EINVAL;
	}

	/* Retrieve Connection */
	connection = ecpri_dma_eth_client_get_conn_from_hdl(hdl);
	if (!connection) {
		DMAERR("NULL pointer to connection\n");
		return -EINVAL;
	}

	if (!connection->valid) {
		DMAERR("Connection invalid handle:%x, ENDP ID:%d\n", hdl,
			connection->tx_endp_ctx->endp_id);
		return -EINVAL;
	}

	while (num_of_pkts_remain) {
		num_of_pkts_to_send =
			num_of_pkts_remain > ECPRI_DMA_DP_MAX_DESC ?
				      ECPRI_DMA_DP_MAX_DESC : num_of_pkts_remain;

		ret = ecpri_dma_dp_transmit(connection->rx_endp_ctx, pkts,
					    num_of_pkts_to_send, commit);
		if (ret != 0) {
			DMAERR("Unable to transmit, handle:%x, ENDP ID:%d\n",
			       hdl, connection->rx_endp_ctx->endp_id);
			return -EINVAL;
		}
		pkts += num_of_pkts_to_send;
		num_of_pkts_remain -= num_of_pkts_to_send;
	}

	DMADBG_LOW("Exit\n");

	return ret;
}

int ecpri_dma_eth_query_stats(ecpri_dma_eth_conn_hdl_t hdl,
	struct ecpri_dma_connection_stats *stats)
{
	int ret = 0;
	struct ecpri_dma_eth_client_connection *connection;

	DMADBG_LOW("Begin\n");

	if (!ecpri_dma_eth_client_ctx
	    || !ecpri_dma_eth_client_ctx->is_eth_ready) {
		DMAERR("Context not initialized\n");
		return -EPERM;
	}

	if (!stats) {
		DMAERR("Invalid parameters\n");
		return -EINVAL;
	}

	/* Retrieve Connection */
	connection = ecpri_dma_eth_client_get_conn_from_hdl(hdl);
	if (!connection) {
		DMAERR("NULL pointer to connection\n");
		return -EINVAL;
	}

	if (!connection->valid) {
		DMAERR("Connection invalid handle:%x, ENDP ID:%d\n", hdl,
			connection->tx_endp_ctx->endp_id);
		return -EINVAL;
	}

	// TODO
	DMADBG_LOW("Exit\n");

	return ret;
}

/* API exposed structure */
const struct ecpri_dma_eth_ops ecpri_dma_eth_driver_ops = {
.ecpri_dma_eth_register = ecpri_dma_eth_register,
.ecpri_dma_eth_deregister = ecpri_dma_eth_deregister,
.ecpri_dma_eth_connect_endpoints = ecpri_dma_eth_connect_endpoints,
.ecpri_dma_eth_disconnect_endpoints =ecpri_dma_eth_disconnect_endpoints,
.ecpri_dma_eth_start_endpoints = ecpri_dma_eth_start_endpoints,
.ecpri_dma_eth_stop_endpoints = ecpri_dma_eth_stop_endpoints,
.ecpri_dma_eth_transmit = ecpri_dma_eth_transmit,
.ecpri_dma_eth_commit = ecpri_dma_eth_commit,
.ecpri_dma_eth_tx_ring_state = ecpri_dma_eth_tx_ring_state,
.ecpri_dma_eth_rx_ring_state = ecpri_dma_eth_rx_ring_state,
.ecpri_dma_eth_rx_mode_set = ecpri_dma_eth_rx_mode_set,
.ecpri_dma_eth_rx_mode_get = ecpri_dma_eth_rx_mode_get,
.ecpri_dma_eth_rx_poll = ecpri_dma_eth_rx_poll,
.ecpri_dma_eth_replenish_buffers = ecpri_dma_eth_replenish_buffers,
.ecpri_dma_eth_query_stats = ecpri_dma_eth_query_stats,
.ecpri_dma_eth_tx_mode_set = ecpri_dma_eth_tx_mode_set,
.ecpri_dma_eth_tx_mode_get = ecpri_dma_eth_tx_mode_get,
.ecpri_dma_eth_tx_poll = ecpri_dma_eth_tx_poll,
};

EXPORT_SYMBOL(ecpri_dma_eth_driver_ops);
