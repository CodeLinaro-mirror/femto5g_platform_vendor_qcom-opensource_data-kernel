/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include "ecpriss_core.h"
//#include "ecpriss_qudp_hal.h"
#include "ecpriss_log.h"

volatile int ecpriss_filtering_enabled = 0;
volatile int ecpriss_qudp_ingress_action = ECPRISS_QUDP_ACTION_DISCARD;


#define ECPRISS_ETH_QUDP_MTU_SIZE_V4   9000 
#define ECPRISS_ETH_QUDP_MTU_SIZE_V6   9000 
#define ECPRISS_QUDP_REG_FIELD_ENABLE  1
#define ENABLE_FILTER                  1
#define BYTE_SHIFT                     8
#define MSB_SHIFT                      32
#define CONFIGURE		       1
#define DE_CONFIGURE		       0

int qudp_irq_mapping[QUDP_IRQ_MAX];

void ecpriss_qudp_clear_stats_v2(uint32_t port_index, uint32_t link_index)
{
	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS ,
		ECPRI_UDP_FH_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_V2,
		port_index, link_index,0);

	ecpriss_qudp_hal_write_reg_mn(ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_V2,
		port_index, link_index,0);

	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_V2,
		port_index, link_index,0);
	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_V2,
		port_index, link_index,0);

	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_V2,
		port_index, link_index,0);
	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_V2,
		port_index, link_index,0);

	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_V2,
		port_index, link_index,0);
	ecpriss_qudp_hal_write_reg_mn(ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_V2,
		port_index, link_index,0);

	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_V2,
		port_index, link_index,0);
	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_V2,
		port_index, link_index,0);

	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_V2,
		port_index, link_index,0);
	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_V2,
		port_index, link_index,0);

	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_V2,
		port_index, link_index,0);
	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_V2,
		port_index, link_index,0);

	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_V2,
		port_index, link_index,0);
	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_V2,
		port_index, link_index,0);

	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_V2,
		port_index, link_index,0);
	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_V2,
		port_index, link_index,0);

}
void ecpriss_qudp_clear_stats(uint32_t port_index, uint32_t link_index)
{
	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS ,
		ECPRI_UDP_FH_EGRESS_NUM_UDP_PACKETS_LSB_PORT_p_LINK_n,
		port_index, link_index,0);

	ecpriss_qudp_hal_write_reg_mn(ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_EGRESS_NUM_UDP_PACKETS_MSB_PORT_p_LINK_n,
		port_index, link_index,0);

	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_EGRESS_NUM_ETH_ONLY_PACKETS_LSB_PORT_p_LINK_n,
		port_index, link_index,0);
	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_EGRESS_NUM_ETH_ONLY_PACKETS_MSB_PORT_p_LINK_n,
		port_index, link_index,0);

	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_EGRESS_NUM_BYPASSED_PACKETS_LSB_PORT_p_LINK_n,
		port_index, link_index,0);
	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_EGRESS_NUM_BYPASSED_PACKETS_MSB_PORT_p_LINK_n,
		port_index, link_index,0);

	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_EGRESS_MTU_ERR_PACKETS_LSB_PORT_p_LINK_n,
		port_index, link_index,0);
	ecpriss_qudp_hal_write_reg_mn(ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_EGRESS_MTU_ERR_PACKETS_MSB_PORT_p_LINK_n,
		port_index, link_index,0);

	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_NUM_UDP_PACKETS_LSB_PORT_p_LINK_n,
		port_index, link_index,0);
	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_NUM_UDP_PACKETS_MSB_PORT_p_LINK_n,
		port_index, link_index,0);

	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_NUM_NON_UDP_PACKETS_LSB_PORT_p_LINK_n,
		port_index, link_index,0);
	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_NUM_NON_UDP_PACKETS_MSB_PORT_p_LINK_n,
		port_index, link_index,0);

	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_FCS_ERR_PACKETS_LSB_PORT_p_LINK_n,
		port_index, link_index,0);
	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_FCS_ERR_PACKETS_MSB_PORT_p_LINK_n,
		port_index, link_index,0);

	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_IPV4_CS_ERROR_PACKETS_LSB_PORT_p_LINK_n,
		port_index, link_index,0);
	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_IPV4_CS_ERROR_PACKETS_MSB_PORT_p_LINK_n,
		port_index, link_index,0);

	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_UDP_CS_ERROR_PACKETS_LSB_PORT_p_LINK_n,
		port_index, link_index,0);
	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_UDP_CS_ERROR_PACKETS_MSB_PORT_p_LINK_n,
		port_index, link_index,0);

	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_VLAN_FILTERED_PACKETS_LSB_PORT_p_LINK_n,
		port_index, link_index,0);
	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_VLAN_FILTERED_PACKETS_MSB_PORT_p_LINK_n,
		port_index, link_index,0);

	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_SEC_ERR_PACKETS_LSB_PORT_p_LINK_n,
		port_index, link_index,0);
	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_SEC_ERR_PACKETS_MSB_PORT_p_LINK_n,
		port_index, link_index,0);

	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_IP_LEN_ERR_PACKETS_LSB_PORT_p_LINK_n,
		port_index, link_index,0);
	ecpriss_qudp_hal_write_reg_mn(ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_IP_LEN_ERR_PACKETS_MSB_PORT_p_LINK_n,
		port_index, link_index,0);

	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_IP_FILTERED_PACKETS_LSB_PORT_p_LINK_n,
		port_index, link_index,0);
	ecpriss_qudp_hal_write_reg_mn(
		ECPRISS_QUDP_FH_RAMS,
		ECPRI_UDP_FH_INGRESS_IP_FILTERED_PACKETS_MSB_PORT_p_LINK_n,
		port_index, link_index,0);

}
void debug_qudp_egress_config(void)
{
	int32_t fh_index = 0;
	int32_t egress_table_index = 0;

	for(fh_index = 0; fh_index < NUM_OF_FHP; fh_index++){

		for(egress_table_index = 0; egress_table_index < NUM_EGRESS_ENTRY; egress_table_index++){
			ECPRILOGDBG("SRC udp_ports[%d][%d]: 0x%x\n",fh_index,egress_table_index,ecpriss_pdata->cfg_stats.qudp_cfg.egress.udp_ports[fh_index][egress_table_index].src);
			ECPRILOGDBG("DST udp_ports[%d][%d]: 0x%x\n",fh_index,egress_table_index,ecpriss_pdata->cfg_stats.qudp_cfg.egress.udp_ports[fh_index][egress_table_index].dst);
			ECPRILOGDBG("VLAN vlan_ethertype[%d][%d]: 0x%x\n",fh_index,egress_table_index,ecpriss_pdata->cfg_stats.qudp_cfg.egress.vlan_ethertype[fh_index][egress_table_index].vlan_data);
			ECPRILOGDBG("EtherType vlan_ethertype[%d][%d]: 0x%x\n",fh_index,egress_table_index,ecpriss_pdata->cfg_stats.qudp_cfg.egress.vlan_ethertype[fh_index][egress_table_index].ethertype);
			ECPRILOGDBG("Eth_DST0_port eth_dst0_port[%d][%d]: 0x%x\n",fh_index,egress_table_index,ecpriss_pdata->cfg_stats.qudp_cfg.egress.eth_dst0_port[fh_index][egress_table_index].value);
			ECPRILOGDBG("DST_MSB eth_src1_dst1_port[%d][%d]: 0x%x\n",fh_index,egress_table_index,ecpriss_pdata->cfg_stats.qudp_cfg.egress.eth_src1_dst1_port[fh_index][egress_table_index].dst_msb);
			ECPRILOGDBG("SRC_MSB eth_src1_dst1_port[%d][%d]: 0x%x\n",fh_index,egress_table_index,ecpriss_pdata->cfg_stats.qudp_cfg.egress.eth_src1_dst1_port[fh_index][egress_table_index].src_msb);
			ECPRILOGDBG("ETH_src0 eth_src0_port[%d][%d]: 0x%x\n",fh_index,egress_table_index,ecpriss_pdata->cfg_stats.qudp_cfg.egress.eth_src0_port[fh_index][egress_table_index].value);
			ECPRILOGDBG("DST IP addr0 ip_addr0[%d][%d]: 0x%x\n",fh_index,egress_table_index,ecpriss_pdata->cfg_stats.qudp_cfg.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst0.value);
			ECPRILOGDBG("DST IP addr1 ip_addr1[%d][%d]: 0x%x\n",fh_index,egress_table_index,ecpriss_pdata->cfg_stats.qudp_cfg.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst1.value);
			ECPRILOGDBG("DST IP addr2 ip_addr2[%d][%d]: 0x%x\n",fh_index,egress_table_index,ecpriss_pdata->cfg_stats.qudp_cfg.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst2.value);
			ECPRILOGDBG("DST IP addr3 ip_addr3[%d][%d]: 0x%x\n",fh_index,egress_table_index,ecpriss_pdata->cfg_stats.qudp_cfg.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst3.value);
			ECPRILOGDBG("SRC IP addr0 ip_addr0[%d][%d]: 0x%x\n",fh_index,egress_table_index,ecpriss_pdata->cfg_stats.qudp_cfg.egress.src_ip_addr[fh_index][egress_table_index].ip_src0.value);
			ECPRILOGDBG("SRC IP addr1 ip_addr1[%d][%d]: 0x%x\n",fh_index,egress_table_index,ecpriss_pdata->cfg_stats.qudp_cfg.egress.src_ip_addr[fh_index][egress_table_index].ip_src1.value);
			ECPRILOGDBG("SRC IP addr2 ip_addr2[%d][%d]: 0x%x\n",fh_index,egress_table_index,ecpriss_pdata->cfg_stats.qudp_cfg.egress.src_ip_addr[fh_index][egress_table_index].ip_src2.value);
			ECPRILOGDBG("SRC IP addr3 ip_addr3[%d][%d]: 0x%x\n",fh_index,egress_table_index,ecpriss_pdata->cfg_stats.qudp_cfg.egress.src_ip_addr[fh_index][egress_table_index].ip_src3.value);
		}
	}
}
// ecpriss_pdata->cfg_stats.qudp_cfg.egress
void ecpriss_qudp_egress_config_stats_update(int32_t fh_index)
{
	int32_t egress_table_index = 0;

	for(egress_table_index = 0; egress_table_index < NUM_EGRESS_ENTRY ; egress_table_index++)
	{

		ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n,
				fh_index,
				egress_table_index,
				&ecpriss_pdata->cfg_stats.qudp_cfg.egress.udp_ports[fh_index][egress_table_index]);

		ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n,
				fh_index,
				egress_table_index,
				&ecpriss_pdata->cfg_stats.qudp_cfg.egress.vlan_ethertype[fh_index][egress_table_index]);

		ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n,
				fh_index,
				egress_table_index,
				&ecpriss_pdata->cfg_stats.qudp_cfg.egress.eth_dst0_port[fh_index][egress_table_index]);

		ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n,
				fh_index,
				egress_table_index,
				&ecpriss_pdata->cfg_stats.qudp_cfg.egress.eth_src1_dst1_port[fh_index][egress_table_index]);

		ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n,
				fh_index,
				egress_table_index,
				&ecpriss_pdata->cfg_stats.qudp_cfg.egress.eth_src0_port[fh_index][egress_table_index]);

		ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n,
				fh_index,
				egress_table_index,
				&ecpriss_pdata->cfg_stats.qudp_cfg.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst0);
		ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n,
				fh_index,
				egress_table_index,
				&ecpriss_pdata->cfg_stats.qudp_cfg.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst1);
		ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n,
				fh_index,
				egress_table_index,
				&ecpriss_pdata->cfg_stats.qudp_cfg.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst2);
		ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n,
				fh_index,
				egress_table_index,
				&ecpriss_pdata->cfg_stats.qudp_cfg.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst3);

		ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n,
				fh_index,
				egress_table_index,
				&ecpriss_pdata->cfg_stats.qudp_cfg.egress.src_ip_addr[fh_index][egress_table_index].ip_src0);
		ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n,
				fh_index,
				egress_table_index,
				&ecpriss_pdata->cfg_stats.qudp_cfg.egress.src_ip_addr[fh_index][egress_table_index].ip_src1);
		ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n,
				fh_index,
				egress_table_index,
				&ecpriss_pdata->cfg_stats.qudp_cfg.egress.src_ip_addr[fh_index][egress_table_index].ip_src2);
		ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n,
				fh_index,
				egress_table_index,
				&ecpriss_pdata->cfg_stats.qudp_cfg.egress.src_ip_addr[fh_index][egress_table_index].ip_src3);
	}
	return;
}
void ecpriss_qudp_egress_config_stats_update_v2(int32_t fh_index)
{
	int32_t egress_table_index = 0;

	for(egress_table_index = 0; egress_table_index < NUM_EGRESS_ENTRY ; egress_table_index++)
	{

		ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_V2,
				fh_index,
				egress_table_index,
				&ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.udp_ports[fh_index][egress_table_index]);

		ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_V2,
				fh_index,
				egress_table_index,
				&ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.vlan_ethertype[fh_index][egress_table_index]);

		ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n_V2,
				fh_index,
				egress_table_index,
				&ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.eth_dst0_port[fh_index][egress_table_index]);

		ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_V2,
				fh_index,
				egress_table_index,
				&ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.eth_src1_dst1_port[fh_index][egress_table_index]);

		ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_V2,
				fh_index,
				egress_table_index,
				&ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.eth_src0_port[fh_index][egress_table_index]);

		ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_V2,
				fh_index,
				egress_table_index,
				&ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst0);
		ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_V2,
				fh_index,
				egress_table_index,
				&ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst1);
		ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_V2,
				fh_index,
				egress_table_index,
				&ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst2);
		ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_V2,
				fh_index,
				egress_table_index,
				&ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.dst_ip_addr[fh_index][egress_table_index].ip_dst3);

		ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_V2,
				fh_index,
				egress_table_index,
				&ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.src_ip_addr[fh_index][egress_table_index].ip_src0);
		ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_V2,
				fh_index,
				egress_table_index,
				&ecpriss_pdata->cfg_stats.qudp_cfg.egress.src_ip_addr[fh_index][egress_table_index].ip_src1);
		ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_V2,
				fh_index,
				egress_table_index,
				&ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.src_ip_addr[fh_index][egress_table_index].ip_src2);
		ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_V2,
				fh_index,
				egress_table_index,
				&ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.egress.src_ip_addr[fh_index][egress_table_index].ip_src3);
	}
	return;
}


void debug_qudp_ingress_config(void)
{
	int i ,j;

	ECPRILOGERR("Global config\n");

	for(i=0; i < NUM_OF_FHP; i++){
		ECPRILOGDBG("0x%x\n",ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[i]);
		ECPRILOGDBG("IP_FLTR: %u\n",ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[i].enable_ip_dst_filt);
		ECPRILOGDBG("UDP_CLASS: %u\n",ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[i].enable_udp_dst_class);
		ECPRILOGDBG("VLAN_FLTR: %u\n",ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[i].enable_vlan_filt);
		ECPRILOGDBG("MAC_FLTR: %u\n",ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[i].enable_mac_dst_check);
	}
	ECPRILOGERR("VLAID BITS \n");
	for(i=0; i < NUM_OF_FHP; i++){
		ECPRILOGDBG("VALID VLAN[%d] 0x%x\n",i,ecpriss_pdata->cfg_stats.qudp_cfg.ingress.vbits.vlan[i].valid_bits);
		ECPRILOGDBG("VLAID UDP[%d] 0x%x\n",i,ecpriss_pdata->cfg_stats.qudp_cfg.ingress.vbits.udp_clss[i].valid_bits);
		ECPRILOGDBG("VLAID IP[%d] 0x%x\n",i,ecpriss_pdata->cfg_stats.qudp_cfg.ingress.vbits.ip_addr[i].valid_bits);
		ECPRILOGDBG("VLAID mac[%d] 0x%x\n",i,ecpriss_pdata->cfg_stats.qudp_cfg.ingress.vbits.mac_addr[i].valid_bits);
	}
	for(i=0; i < NUM_OF_FHP; i++){
		for(j=0; j<NUM_OF_FLTR; j++){
			ECPRILOGDBG("vlan[%d][%d]: 0x%x\t",i,j, ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.vlan[i][j].value);
			ECPRILOGDBG("udp[%d][%d]: 0x%x\t",i,j,ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.udp_clss[i][j].value);
			ECPRILOGDBG("mac_lsb[%d][%d]: 0x%x\t",i,j,ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.mac_addr[i][j].mac_lsb);
			ECPRILOGDBG("mac_msb[%d][%d]: 0x%x\t",i,j,ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.mac_addr[i][j].mac_msb);
			ECPRILOGDBG("ip0[%d][%d]: 0x%x\t",i,j,ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.ip_addr[i][j].dst_ip0.value);
			ECPRILOGDBG("ip1[%d][%d]: 0x%x\t",i,j,ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.ip_addr[i][j].dst_ip1.value);
			ECPRILOGDBG("ip2[%d][%d]: 0x%x\t",i,j,ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.ip_addr[i][j].dst_ip2.value);
			ECPRILOGDBG("ip3[%d][%d]: 0x%x\t",i,j,ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.ip_addr[i][j].dst_ip3.value);
			ECPRILOGDBG("\n");
		}
	}

}
// ecpriss_pdata->cfg_stats.qudp_cfg.ingress
void ecpriss_qudp_ingress_config_stats_update(int32_t fh_index)
{
	uint32_t flag = 1;
	int32_t fltr_index = 0;

	ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
			ECPRI_UDP_FH_INGRESS_CONFIG_P,
			fh_index,
			&ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[fh_index]);

	ecpriss_pdata->cfg_stats.qudp_cfg.ingress.vbits.vlan[fh_index].valid_bits = 0;
	if(ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[fh_index].enable_vlan_filt){
		ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS,
				fh_index,
				&ecpriss_pdata->cfg_stats.qudp_cfg.ingress.vbits.vlan[fh_index]);
	}
	ecpriss_pdata->cfg_stats.qudp_cfg.ingress.vbits.udp_clss[fh_index].valid_bits = 0;
	if(ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[fh_index].enable_udp_dst_class){
		ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS,
				fh_index,
				&ecpriss_pdata->cfg_stats.qudp_cfg.ingress.vbits.udp_clss[fh_index]);
	}
	ecpriss_pdata->cfg_stats.qudp_cfg.ingress.vbits.ip_addr[fh_index].valid_bits = 0;
	if(ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[fh_index].enable_ip_dst_filt){
		ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS,
				fh_index,
				&ecpriss_pdata->cfg_stats.qudp_cfg.ingress.vbits.ip_addr[fh_index]);
	}
	ecpriss_pdata->cfg_stats.qudp_cfg.ingress.vbits.mac_addr[fh_index].valid_bits = 0;
	if(ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[fh_index].enable_mac_dst_check){
		ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS,
				fh_index,
				&ecpriss_pdata->cfg_stats.qudp_cfg.ingress.vbits.mac_addr[fh_index]);
	}
	for(fltr_index = 0; fltr_index < NUM_OF_FLTR ; fltr_index ++){

		flag = flag << fltr_index;
		ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.vlan[fh_index][fltr_index].value = 0;
		if(ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[fh_index].enable_vlan_filt){
			if(ecpriss_pdata->cfg_stats.qudp_cfg.ingress.vbits.vlan[fh_index].valid_bits & flag){
				ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
						ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n,
						fh_index,
						fltr_index,
						&ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.vlan[fh_index][fltr_index]);
			}
		}
		ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.ip_addr[fh_index][fltr_index].dst_ip0.value = 0;
		ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.ip_addr[fh_index][fltr_index].dst_ip1.value = 0;
		ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.ip_addr[fh_index][fltr_index].dst_ip2.value = 0;
		ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.ip_addr[fh_index][fltr_index].dst_ip3.value = 0;
		if(ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[fh_index].enable_ip_dst_filt){
			if(ecpriss_pdata->cfg_stats.qudp_cfg.ingress.vbits.ip_addr[fh_index].valid_bits & flag){
				ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
						ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n,
						fh_index,
						fltr_index,
						&ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.ip_addr[fh_index][fltr_index].dst_ip0);

				ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
						ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n,
						fh_index,
						fltr_index,
						&ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.ip_addr[fh_index][fltr_index].dst_ip1);

				ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
						ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n,
						fh_index,
						fltr_index,
						&ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.ip_addr[fh_index][fltr_index].dst_ip2);

				ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
						ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n,
						fh_index,
						fltr_index,
						&ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.ip_addr[fh_index][fltr_index].dst_ip3);
			}
		}
		ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.udp_clss[fh_index][fltr_index].value = 0;
		if(ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[fh_index].enable_udp_dst_class){
			if(ecpriss_pdata->cfg_stats.qudp_cfg.ingress.vbits.udp_clss[fh_index].valid_bits & flag){
				ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
						ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n,
						fh_index,
						fltr_index,
						&ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.udp_clss[fh_index][fltr_index]);
			}
		}
		ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.mac_addr[fh_index][fltr_index].mac_lsb.value = 0;
		ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.mac_addr[fh_index][fltr_index].mac_msb.value = 0;
		if(ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.global_cfg[fh_index].enable_mac_dst_check && fltr_index <= 4){
			if(ecpriss_pdata->cfg_stats.qudp_cfg.ingress.vbits.mac_addr[fh_index].valid_bits & flag){
				ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
						ECPRI_UDP_FH_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n,
						fh_index,
						fltr_index,
						&ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.mac_addr[fh_index][fltr_index].mac_lsb);
				ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
						ECPRI_UDP_FH_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n,
						fh_index,
						fltr_index,
						&ecpriss_pdata->cfg_stats.qudp_cfg.ingress.cfg.mac_addr[fh_index][fltr_index].mac_msb);
			}
		}

		flag = 1;
	}
	return;
}

void ecpriss_qudp_ingress_config_stats_update_v2(int32_t fh_index)
{
	uint32_t flag = 1;
	int32_t fltr_index = 0;

	ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
			ECPRI_UDP_FH_INGRESS_CONFIG_P_V2,
			fh_index,
			&ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index]);

	ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.vbits.vlan[fh_index].valid_bits = 0;
	if(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].enable_vlan_filt){
		ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_V2,
				fh_index,
				&ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.vbits.vlan[fh_index]);
	}
	ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.vbits.udp_clss[fh_index].valid_bits = 0;
	if(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].enable_udp_dst_class){
		ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_V2,
				fh_index,
				&ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.vbits.udp_clss[fh_index]);
	}
	ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.vbits.ip_addr[fh_index].valid_bits = 0;
	if(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].enable_ip_dst_filt){
		ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_V2,
				fh_index,
				&ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.vbits.ip_addr[fh_index]);
	}
	ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.vbits.mac_addr[fh_index].valid_bits = 0;
	if(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].enable_mac_dst_check){
		ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS_V2,
				fh_index,
				&ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.vbits.mac_addr[fh_index]);
	}
	for(fltr_index = 0; fltr_index < NUM_OF_FLTR ; fltr_index ++){

		flag = flag << fltr_index;
		ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.vlan[fh_index][fltr_index].value = 0;
		if(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].enable_vlan_filt){
			if(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.vbits.vlan[fh_index].valid_bits & flag){
				ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
						ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n_V2,
						fh_index,
						fltr_index,
						&ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.vlan[fh_index][fltr_index]);
			}
		}
		ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.ip_addr[fh_index][fltr_index].dst_ip0.value = 0;
		ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.ip_addr[fh_index][fltr_index].dst_ip1.value = 0;
		ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.ip_addr[fh_index][fltr_index].dst_ip2.value = 0;
		ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.ip_addr[fh_index][fltr_index].dst_ip3.value = 0;
		if(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].enable_ip_dst_filt){
			if(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.vbits.ip_addr[fh_index].valid_bits & flag){
				ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
						ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_V2,
						fh_index,
						fltr_index,
						&ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.ip_addr[fh_index][fltr_index].dst_ip0);

				ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
						ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_V2,
						fh_index,
						fltr_index,
						&ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.ip_addr[fh_index][fltr_index].dst_ip1);

				ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
						ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_V2,
						fh_index,
						fltr_index,
						&ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.ip_addr[fh_index][fltr_index].dst_ip2);

				ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
						ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_V2,
						fh_index,
						fltr_index,
						&ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.ip_addr[fh_index][fltr_index].dst_ip3);
			}
		}
		ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.udp_clss[fh_index][fltr_index].value = 0;
		if(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].enable_udp_dst_class){
			if(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.vbits.udp_clss[fh_index].valid_bits & flag){
				ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
						ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_V2,
						fh_index,
						fltr_index,
						&ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.udp_clss[fh_index][fltr_index]);
			}
		}
		ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.mac_addr[fh_index][fltr_index].mac_lsb.value = 0;
		ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.mac_addr[fh_index][fltr_index].mac_msb.value = 0;
		if(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.global_cfg[fh_index].enable_mac_dst_check && fltr_index <= 4){
			if(ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.vbits.mac_addr[fh_index].valid_bits & flag){
				ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
						ECPRI_UDP_FH_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n_V2,
						fh_index,
						fltr_index,
						&ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.mac_addr[fh_index][fltr_index].mac_lsb);
				ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
						ECPRI_UDP_FH_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n_V2,
						fh_index,
						fltr_index,
						&ecpriss_pdata_v2->cfg_stats_v2.qudp_cfg_v2.ingress.cfg.mac_addr[fh_index][fltr_index].mac_msb);
			}
		}

		flag = 1;
	}
	return;
}
void ecpriss_qudp_fh_egress_stats_update(uint32_t port_index, uint32_t link_index)
{
	uint32_t lsb_val = 0;
	uint64_t msb_val = 0;
	uint64_t val = 0;
	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_EGRESS_NUM_UDP_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);

	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_EGRESS_NUM_UDP_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.egress_num_udp_packets[link_index] = val;
	ECPRILOGDBG("ECPRI_UDP_FH_EGRESS_NUM_UDP_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val =ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_EGRESS_NUM_ETH_ONLY_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_EGRESS_NUM_ETH_ONLY_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.egress_num_eth_packets[link_index] = val;
	ECPRILOGDBG("ECPRI_UDP_FH_EGRESS_NUM_ETH_ONLY_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);


	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_EGRESS_NUM_BYPASSED_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_EGRESS_NUM_BYPASSED_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.egress_num_bypassed_packets[link_index] = val;
	ECPRILOGDBG("ECPRI_UDP_FH_EGRESS_NUM_BYPASSED_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);


	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_EGRESS_MTU_ERR_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val =ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_EGRESS_MTU_ERR_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.egress_num_mtu_err_packets[link_index] = val;
	ECPRILOGDBG("ECPRI_UDP_FH_EGRESS_MTU_ERR_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);
	return;
}
void ecpriss_qudp_fh_egress_stats_update_v2(uint32_t port_index, uint32_t link_index)
{
	uint32_t val = 0;
	val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n_V2,
			port_index,
			link_index);

	ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].stats_v2.egress_num_udp_packets[link_index] += val;
	ECPRILOGDBG("ECPRI_UDP_FH_EGRESS_NUM_UDP_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	val =ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n_V2,
			port_index,
			link_index);
	ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].stats_v2.egress_num_eth_packets[link_index] += val;
	ECPRILOGDBG("ECPRI_UDP_FH_EGRESS_NUM_ETH_ONLY_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);


	val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n_V2,
			port_index,
			link_index);
	ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].stats_v2.egress_num_bypassed_packets[link_index] += val;
	ECPRILOGDBG("ECPRI_UDP_FH_EGRESS_NUM_BYPASSED_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);


	val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n_V2,
			port_index,
			link_index);
	ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].stats_v2.egress_num_mtu_err_packets[link_index] += val;
	ECPRILOGDBG("ECPRI_UDP_FH_EGRESS_MTU_ERR_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);
	return;
}



void ecpriss_qudp_fh_ingress_stats_update(uint32_t port_index, uint32_t link_index)
{
	uint32_t lsb_val = 0;
	uint64_t msb_val = 0;
	uint64_t val = 0;
	uint32_t curr_wm_index = 0;

	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_udp_watermark_port_p_s fh_egress_udp_watermark_port_p;
	ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_udp_watermark_port_p_link_n_s  fh_ingress_udp_watermark_port_p_link_n;

	curr_wm_index =
		ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.curr_wm_index % MAX_QUDP_WM_ENTRY;

	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.curr_wm_index++;


	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_NUM_UDP_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);

	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_NUM_UDP_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.ingress_num_udp_packets[link_index] = val;
	ECPRILOGDBG("ECPRI_UDP_FH_INGRESS_NUM_UDP_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);


	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_NUM_NON_UDP_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);

	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_NUM_NON_UDP_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.ingress_num_non_udp_packets[link_index] = val;
	ECPRILOGDBG("ECPRI_UDP_FH_INGRESS_NUM_NON_UDP_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_FCS_ERR_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_FCS_ERR_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.ingress_num_fcs_err_packets[link_index] = val;
	ECPRILOGDBG("ECPRI_UDP_FH_INGRESS_FCS_ERR_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_IPV4_CS_ERROR_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_IPV4_CS_ERROR_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.ingress_num_ipv4_cs_err_packets[link_index] = val;
	ECPRILOGDBG("ECPRI_UDP_FH_INGRESS_IPV4_CS_ERROR_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_UDP_CS_ERROR_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);

	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_UDP_CS_ERROR_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.ingress_num_udp_cs_err_packets[link_index] = val;
	ECPRILOGDBG("ECPRI_UDP_FH_INGRESS_UDP_CS_ERROR_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_VLAN_FILTERED_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_VLAN_FILTERED_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.ingress_num_vlan_filtered_packets[link_index] = val;
	ECPRILOGDBG("ECPRI_UDP_FH_INGRESS_VLAN_FILTERED_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_SEC_ERR_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);

	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_SEC_ERR_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);
	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.ingress_num_sec_err_packets[link_index] = val;
	ECPRILOGDBG("ECPRI_UDP_FH_INGRESS_SEC_ERR_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_IP_LEN_ERR_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_IP_LEN_ERR_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);
	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.ingress_ip_len_err_packets[link_index] = val;
	ECPRILOGDBG("ECPRI_UDP_FH_INGRESS_IP_LEN_ERR_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_IP_FILTERED_PACKETS_LSB_PORT_p_LINK_n,port_index,link_index);

	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_IP_FILTERED_PACKETS_MSB_PORT_p_LINK_n,port_index,link_index);

	val = msb_val >> MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.ingress_ip_filtered_packets[link_index]=val;
	ECPRILOGDBG("ECPRI_UDP_FH_INGRESS_IP_FILTERED_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH,
			ECPRI_UDP_FH_INGRESS_UDP_WATERMARK_PORT_p_LINK_n,
			port_index,
			link_index,
			&fh_ingress_udp_watermark_port_p_link_n);

	ECPRILOGDBG("ECPRI_UDP_FH_INGRESS_UDP_WATERMARK_PORT_p_LINK_n, : port_index :%d link_index %d value = %u\n", port_index,link_index,
			fh_ingress_udp_watermark_port_p_link_n);

	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.fh_ingress_udp_watermark_port_p_link_n_ptp_timestamp_fifo[link_index] =
		fh_ingress_udp_watermark_port_p_link_n.ptp_timestamp_fifo;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.fh_ingress_udp_watermark_port_p_link_n_pkt_handler_sync_fifos[link_index] =
		fh_ingress_udp_watermark_port_p_link_n.pkt_handler_sync_fifos;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.fh_ingress_udp_watermark_port_p_link_n_cmd_fifo[link_index] =
		fh_ingress_udp_watermark_port_p_link_n.cmd_fifo;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.fh_ingress_udp_watermark_port_p_link_n_pkt_fifo[link_index] =
		fh_ingress_udp_watermark_port_p_link_n.pkt_fifo;

	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.fh_ingress_wm_ptp_fifo[link_index][curr_wm_index] =
		fh_ingress_udp_watermark_port_p_link_n.ptp_timestamp_fifo;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.fh_ingress_wm_sync_fifo[link_index][curr_wm_index] =
		fh_ingress_udp_watermark_port_p_link_n.pkt_handler_sync_fifos;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.fh_ingress_wm_cmd_fifo[link_index][curr_wm_index] =
		fh_ingress_udp_watermark_port_p_link_n.cmd_fifo;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.fh_ingress_wm_pkt_fifo[link_index][curr_wm_index] =
		fh_ingress_udp_watermark_port_p_link_n.pkt_fifo;

	ecpriss_qudp_hal_read_reg_mn_fields(ECPRISS_QUDP_FH,
			ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_PORT_p,
			port_index,
			link_index,
			&fh_egress_udp_watermark_port_p);

	ECPRILOGDBG("ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_PORT_p, : port_index :%d link_index %d value = %u\n", port_index,link_index,
			fh_egress_udp_watermark_port_p);

	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.fh_egress_udp_watermark_port_p_aligner_output_fifo =
		fh_egress_udp_watermark_port_p.aligner_output_fifo;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.fh_egress_udp_watermark_port_p_cs_update_fifo =
		fh_egress_udp_watermark_port_p.cs_update_fifo;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.fh_egress_udp_watermark_port_p_cs_calc_fifo =
		fh_egress_udp_watermark_port_p.cs_calc_fifo;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.fh_egress_udp_watermark_port_p_hdri_output_fifo =
		fh_egress_udp_watermark_port_p.hdri_output_fifo;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.fh_egress_udp_watermark_port_p_hdri_cfg_index_fifo =
		fh_egress_udp_watermark_port_p.hdri_cfg_index_fifo;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.fh_egress_udp_watermark_port_p_pkt_fifo =
		fh_egress_udp_watermark_port_p.pkt_fifo;


	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.fh_egress_output_fifo[curr_wm_index] =
		fh_egress_udp_watermark_port_p.aligner_output_fifo;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.fh_egress_cs_update_fifo[curr_wm_index] =
		fh_egress_udp_watermark_port_p.cs_update_fifo;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.fh_egress_cs_calc_fifo[curr_wm_index] =
		fh_egress_udp_watermark_port_p.cs_calc_fifo;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.fh_egress_hdri_output_fifo[curr_wm_index] =
		fh_egress_udp_watermark_port_p.hdri_output_fifo;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.fh_egress_hdri_cfg_index_fifo[curr_wm_index] =
		fh_egress_udp_watermark_port_p.hdri_cfg_index_fifo;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.fh_egress_pkt_fifo[curr_wm_index] =
		fh_egress_udp_watermark_port_p.pkt_fifo;

	return;
}

void ecpriss_qudp_fh_ingress_stats_update_v2(uint32_t port_index, uint32_t link_index)
{
	uint32_t val = 0;
	val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n_V2,
			port_index,
			link_index);

	ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].stats_v2.ingress_num_eth_udp_packets[link_index] += val;
	ECPRILOGDBG("ECPRI_UDP_FH_INGRESS_NUM_ETH_UDP_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);


	val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_V2,
			port_index,
			link_index);

	ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].stats_v2.ingress_num_fcs_err_packets[link_index] += val;
	ECPRILOGDBG("ECPRI_UDP_FH_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n_V2: port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_V2,
			port_index,
			link_index);
	ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].stats_v2.ingress_num_ipv4_cs_err_packets[link_index] += val;
	ECPRILOGDBG("ECPRI_UDP_FH_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n_V2: port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_V2,
			port_index,
			link_index);
	ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].stats_v2.ingress_num_udp_cs_err_packets[link_index] += val;
	ECPRILOGDBG("ECPRI_UDP_FH_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n_V2: port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_V2,
			port_index,
			link_index);

	ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].stats_v2.ingress_ip_filtered_packets[link_index] += val;
	ECPRILOGDBG("ECPRI_UDP_FH_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n_V2: port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n_V2,
			port_index,
			link_index);
	ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].stats_v2.ingress_num_vlan_filtered_packets[link_index] += val;
	ECPRILOGDBG("ECPRI_UDP_FH_INGRESS_VLAN_FILTERED_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n_V2,
			port_index,
			link_index);

	ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].stats_v2.ingress_num_sec_err_packets[link_index] += val;
	ECPRILOGDBG("ECPRI_UDP_FH_INGRESS_SEC_ERR_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_V2,
			port_index,
			link_index);
	ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].stats_v2.ingress_ip_len_err_packets[link_index] += val;
	ECPRILOGDBG("ECPRI_UDP_FH_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n_V2: port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_V2,port_index,link_index);


	ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].stats_v2.ingress_num_eth_ecpri_packets[link_index] += val;
	ECPRILOGDBG("ECPRI_UDP_FH_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n_V2: port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_V2,port_index,link_index);


	ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].stats_v2.ingress_num_eth_ptp_packets[link_index] += val;
	ECPRILOGDBG("ECPRI_UDP_FH_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n_V2: port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_V2,port_index,link_index);


	ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].stats_v2.ingress_num_eth_other_packets[link_index] += val;
	ECPRILOGDBG("ECPRI_UDP_FH_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n_V2: port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_V2,port_index,link_index);


	ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].stats_v2.ingress_num_udp_ecpri_or_nfapi_packets[link_index] += val;
	ECPRILOGDBG("ECPRI_UDP_FH_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n_V2: port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_V2,port_index,link_index);


	ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].stats_v2.ingress_num_udp_ptp_packets[link_index] += val;
	ECPRILOGDBG("ECPRI_UDP_FH_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n_V2: port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_FH_RAMS,
			ECPRI_UDP_FH_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_V2,port_index,link_index);


	ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].stats_v2.ingress_num_udp_other_packets[link_index] += val;
	ECPRILOGDBG("ECPRI_UDP_FH_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n_V2: port_index :%d link_index %d value = %d\n", port_index,link_index,val);



	return;
}

void ecpriss_qudp_print_c2c_egress_stats(uint32_t port_index, uint32_t link_index)
{
	uint32_t lsb_val = 0;
	uint64_t msb_val = 0;
	uint64_t val = 0;
	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_EGRESS_NUM_UDP_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_EGRESS_NUM_UDP_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->c2c_port_cfg[port_index].stats.egress_num_udp_packets[link_index] = val;
	ECPRILOGDBG("ECPRI_UDP_C2C_EGRESS_NUM_UDP_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val =ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_EGRESS_NUM_ETH_ONLY_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_EGRESS_NUM_ETH_ONLY_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->c2c_port_cfg[port_index].stats.egress_num_eth_packets[link_index] = val;
	ECPRILOGDBG("ECPRI_UDP_C2C_EGRESS_NUM_ETH_ONLY_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);


	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_EGRESS_NUM_BYPASSED_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_EGRESS_NUM_BYPASSED_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->c2c_port_cfg[port_index].stats.egress_num_bypassed_packets[link_index] = val;
	ECPRILOGDBG("ECPRI_UDP_C2C_EGRESS_NUM_BYPASSED_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);


	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_EGRESS_MTU_ERR_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val =ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_EGRESS_MTU_ERR_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->c2c_port_cfg[port_index].stats.egress_num_mtu_err_packets[link_index] = val;
	ECPRILOGDBG("ECPRI_UDP_C2C_EGRESS_MTU_ERR_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	return;
}


void ecpriss_qudp_print_c2c_ingress_stats(uint32_t port_index, uint32_t link_index)
{
	uint32_t lsb_val = 0;
	uint64_t msb_val = 0;
	uint64_t val = 0;
	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_NUM_UDP_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_NUM_UDP_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->c2c_port_cfg[port_index].stats.ingress_num_udp_packets[link_index] = val;
	ECPRILOGDBG("ECPRI_UDP_C2C_INGRESS_NUM_UDP_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);


	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_NUM_NON_UDP_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_NUM_NON_UDP_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->c2c_port_cfg[port_index].stats.ingress_num_non_udp_packets[link_index] = val;
	ECPRILOGDBG("ECPRI_UDP_C2C_INGRESS_NUM_NON_UDP_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_FCS_ERR_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_FCS_ERR_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->c2c_port_cfg[port_index].stats.ingress_num_fcs_err_packets[link_index] = val;
	ECPRILOGDBG("ECPRI_UDP_C2C_INGRESS_FCS_ERR_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_IPV4_CS_ERROR_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_IPV4_CS_ERROR_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->c2c_port_cfg[port_index].stats.ingress_num_ipv4_cs_err_packets[link_index] = val;
	ECPRILOGDBG("ECPRI_UDP_C2C_INGRESS_IPV4_CS_ERROR_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_UDP_CS_ERROR_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_UDP_CS_ERROR_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->c2c_port_cfg[port_index].stats.ingress_num_udp_cs_err_packets[link_index] = val;
	ECPRILOGDBG("ECPRI_UDP_C2C_INGRESS_UDP_CS_ERROR_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_VLAN_FILTERED_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_VLAN_FILTERED_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->c2c_port_cfg[port_index].stats.ingress_num_vlan_filtered_packets[link_index] = val;
	ECPRILOGDBG("ECPRI_UDP_C2C_INGRESS_VLAN_FILTERED_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_SEC_ERR_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_SEC_ERR_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);
	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->c2c_port_cfg[port_index].stats.ingress_num_sec_err_packets[link_index] = val;
	ECPRILOGDBG("ECPRI_UDP_C2C_INGRESS_SEC_ERR_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_IP_LEN_ERR_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_IP_LEN_ERR_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);
	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->c2c_port_cfg[port_index].stats.ingress_ip_len_err_packets[link_index] = val;
	ECPRILOGDBG("ECPRI_UDP_C2C_INGRESS_IP_LEN_ERR_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	return;
}


void ecpriss_qudp_print_l2_egress_stats(uint32_t port_index, uint32_t link_index)
{
	uint32_t lsb_val = 0;
	uint64_t msb_val = 0;
	uint64_t val = 0;
	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_L2,
			ECPRI_UDP_L2_EGRESS_NUM_UDP_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_L2,
			ECPRI_UDP_L2_EGRESS_NUM_UDP_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.egress_num_udp_packets[link_index] = val;
	ECPRILOGINFO("ECPRI_UDP_L2_EGRESS_NUM_UDP_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val =ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_L2,
			ECPRI_UDP_L2_EGRESS_NUM_ETH_ONLY_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_L2,
			ECPRI_UDP_L2_EGRESS_NUM_ETH_ONLY_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.egress_num_eth_packets[link_index] = val;
	ECPRILOGINFO("ECPRI_UDP_L2_EGRESS_NUM_ETH_ONLY_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);


	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_L2,
			ECPRI_UDP_L2_EGRESS_NUM_BYPASSED_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_L2,
			ECPRI_UDP_L2_EGRESS_NUM_BYPASSED_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.egress_num_bypassed_packets[link_index] = val;
	ECPRILOGINFO("ECPRI_UDP_L2_EGRESS_NUM_BYPASSED_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);


	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_L2,
			ECPRI_UDP_L2_EGRESS_MTU_ERR_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val =ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_L2,
			ECPRI_UDP_L2_EGRESS_MTU_ERR_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.egress_num_mtu_err_packets[link_index] = val;
	ECPRILOGINFO("ECPRI_UDP_L2_EGRESS_MTU_ERR_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	return;
}


void ecpriss_qudp_print_l2_ingress_stats(uint32_t port_index, uint32_t link_index)
{
	uint32_t lsb_val = 0;
	uint64_t msb_val = 0;
	uint64_t val = 0;
	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_L2,
			ECPRI_UDP_L2_INGRESS_NUM_UDP_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_L2,
			ECPRI_UDP_L2_INGRESS_NUM_UDP_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.ingress_num_udp_packets[link_index] = val;
	ECPRILOGINFO("ECPRI_UDP_L2_INGRESS_NUM_UDP_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);


	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_L2,
			ECPRI_UDP_L2_INGRESS_NUM_NON_UDP_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_L2,
			ECPRI_UDP_L2_INGRESS_NUM_NON_UDP_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.ingress_num_non_udp_packets[link_index] = val;
	ECPRILOGINFO("ECPRI_UDP_L2_INGRESS_NUM_NON_UDP_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_L2,
			ECPRI_UDP_L2_INGRESS_FCS_ERR_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_L2,
			ECPRI_UDP_L2_INGRESS_FCS_ERR_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.ingress_num_fcs_err_packets[link_index] = val;
	ECPRILOGINFO("ECPRI_UDP_L2_INGRESS_FCS_ERR_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_L2,
			ECPRI_UDP_L2_INGRESS_IPV4_CS_ERROR_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_L2,
			ECPRI_UDP_L2_INGRESS_IPV4_CS_ERROR_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.ingress_num_ipv4_cs_err_packets[link_index] = val;
	ECPRILOGINFO("ECPRI_UDP_L2_INGRESS_IPV4_CS_ERROR_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_L2,
			ECPRI_UDP_L2_INGRESS_UDP_CS_ERROR_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_L2,
			ECPRI_UDP_L2_INGRESS_UDP_CS_ERROR_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.ingress_num_udp_cs_err_packets[link_index] = val;
	ECPRILOGINFO("ECPRI_UDP_L2_INGRESS_UDP_CS_ERROR_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_L2,
			ECPRI_UDP_L2_INGRESS_VLAN_FILTERED_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_L2,
			ECPRI_UDP_L2_INGRESS_VLAN_FILTERED_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.ingress_num_vlan_filtered_packets[link_index] = val;
	ECPRILOGINFO("ECPRI_UDP_L2_INGRESS_VLAN_FILTERED_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_L2,
			ECPRI_UDP_L2_INGRESS_SEC_ERR_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_L2,
			ECPRI_UDP_L2_INGRESS_SEC_ERR_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);
	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.ingress_num_sec_err_packets[link_index] = val;
	ECPRILOGINFO("ECPRI_UDP_L2_INGRESS_SEC_ERR_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_L2,
			ECPRI_UDP_L2_INGRESS_IP_LEN_ERR_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_L2,
			ECPRI_UDP_L2_INGRESS_IP_LEN_ERR_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);
	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].stats.ingress_ip_len_err_packets[link_index] = val;
	ECPRILOGINFO("ECPRI_UDP_L2_INGRESS_IP_LEN_ERR_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	return;
}

/**
 * ecpri_qudp_ingress_modify_cfg()
 *
 *
 * Returns:	0 on success, negative on failure
 */

static int ecpriss_qudp_ingress_modify_cfg(uint32_t port_index,
		uint32_t value,	ecpriss_ingress_filter_mask_e field , uint8_t filtnum,
		uint8_t cfg_action)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_config_p_s ingress_cfg;
	ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr_port_p_entries_valid_bits_s ip_dst_valid_bit;
	ecpri_qudp_hwio_def_ecpri_udp_fh_udp_classification_list_port_p_entries_valid_bits_s udp_port;
	ecpri_qudp_hwio_def_ecpri_udp_fh_filt_vlan_addr_port_p_entries_valid_bits_s vlan_id;
	ecpriss_qudp_ingress_per_port_cfg_s *qudp_ingress_port =
		&ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].ingress_port_cfg;

	memset(&ingress_cfg, 0, sizeof(ingress_cfg));

	ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
			ECPRI_UDP_FH_INGRESS_CONFIG_P,
			port_index,
			&ingress_cfg);

	if(field & ECPRISS_QUDP_RX_CFG_FLTR_MASK_IP_DADDR)
	{
		memset(&ip_dst_valid_bit ,0, sizeof(ip_dst_valid_bit));


		ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS,
				port_index, &ip_dst_valid_bit);


		if(ecpriss_filtering_enabled){
			if(qudp_ingress_port->num_ip_fltr_entries <= 0)
				ingress_cfg.enable_ip_dst_filt = 0;
			else
				ingress_cfg.enable_ip_dst_filt = 1;

			if(cfg_action == CONFIGURE)
				ip_dst_valid_bit.valid_bits |= 1UL << filtnum;
			else
				ip_dst_valid_bit.valid_bits &= ~(1UL << filtnum);
		}else{
			ingress_cfg.enable_ip_dst_filt = 0;
			ip_dst_valid_bit.valid_bits = 0;

		}


		ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS,
				port_index, &ip_dst_valid_bit);

	}

	if(field & ECPRISS_QUDP_RX_CFG_FLTR_MASK_UDP_DPORT)
	{
		memset(&udp_port ,0, sizeof(udp_port));

		ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS,
				port_index, &udp_port);
		if(qudp_ingress_port->num_udp_fltr_entries <= 0)
			ingress_cfg.enable_udp_dst_class = 0;
		else
			ingress_cfg.enable_udp_dst_class = 1;

		if(cfg_action == CONFIGURE)
			udp_port.valid_bits  |= 1UL << filtnum;
		else
			udp_port.valid_bits  &= ~( 1UL << filtnum);

		ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS,
				port_index, &udp_port);
	}

	if(field & ECPRISS_QUDP_RX_CFG_FLTR_MASK_VLAN)
	{

		memset(&vlan_id ,0, sizeof(vlan_id));

		ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS,
				port_index,
				&vlan_id);


		if(ecpriss_filtering_enabled){
			if(qudp_ingress_port->num_vlan_fltr_entries <= 0)
				ingress_cfg.enable_vlan_filt = 0;
			else
				ingress_cfg.enable_vlan_filt = 1;

			if(cfg_action == CONFIGURE)
				vlan_id.valid_bits  |= (1UL << filtnum);
			else
				vlan_id.valid_bits  &= ~(1UL << filtnum);

		}else{
			ingress_cfg.enable_vlan_filt = 0;
			vlan_id.valid_bits  = 0;
		}

		ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS,
				port_index,&vlan_id);


	}

	ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
			ECPRI_UDP_FH_INGRESS_CONFIG_P,
			port_index,
			&ingress_cfg);


	return 0;
}

static int ecpriss_qudp_ingress_modify_cfg_v2(uint32_t port_index,
		uint32_t value,	ecpriss_ingress_filter_mask_e field , uint8_t filtnum,
		uint8_t cfg_action)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_config_p_s_v2 ingress_cfg;
	ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr_port_p_entries_valid_bits_s_v2 ip_dst_valid_bit;
	ecpri_qudp_hwio_def_ecpri_udp_fh_udp_classification_list_port_p_entries_valid_bits_s_v2 udp_port;
	ecpri_qudp_hwio_def_ecpri_udp_fh_filt_vlan_addr_port_p_entries_valid_bits_s_v2 vlan_id;

	ecpriss_qudp_ingress_per_port_cfg_s_v2 *qudp_ingress_port =
		&ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].ingress_port_cfg;

	memset(&ingress_cfg, 0, sizeof(ingress_cfg));

	ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
			ECPRI_UDP_FH_INGRESS_CONFIG_P_V2,
			port_index,
			&ingress_cfg);

	if(field & ECPRISS_QUDP_RX_CFG_FLTR_MASK_IP_DADDR)
	{
		memset(&ip_dst_valid_bit ,0, sizeof(ip_dst_valid_bit));


		ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_V2,
				port_index, &ip_dst_valid_bit);


		if(ecpriss_filtering_enabled){
			if(qudp_ingress_port->num_ip_fltr_entries <= 0)
				ingress_cfg.enable_ip_dst_filt = 0;
			else
				ingress_cfg.enable_ip_dst_filt = 1;

			if(cfg_action == CONFIGURE)
				ip_dst_valid_bit.valid_bits |= 1UL << filtnum;
			else
				ip_dst_valid_bit.valid_bits &= ~(1UL << filtnum);
		}else{
			ingress_cfg.enable_ip_dst_filt = 0;
			ip_dst_valid_bit.valid_bits = 0;

		}


		ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_V2,
				port_index, &ip_dst_valid_bit);

	}

	if(field & ECPRISS_QUDP_RX_CFG_FLTR_MASK_UDP_DPORT)
	{
		memset(&udp_port ,0, sizeof(udp_port));

		ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_V2,
				port_index, &udp_port);
		if(qudp_ingress_port->num_udp_fltr_entries <= 0)
			ingress_cfg.enable_udp_dst_class = 0;
		else
			ingress_cfg.enable_udp_dst_class = 1;

		if(cfg_action == CONFIGURE)
			udp_port.valid_bits  |= 1UL << filtnum;
		else
			udp_port.valid_bits  &= ~( 1UL << filtnum);

		ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_V2,
				port_index, &udp_port);
	}

	if(field & ECPRISS_QUDP_RX_CFG_FLTR_MASK_VLAN)
	{

		memset(&vlan_id ,0, sizeof(vlan_id));

		ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_V2,
				port_index,
				&vlan_id);


		if(ecpriss_filtering_enabled){
			if(qudp_ingress_port->num_vlan_fltr_entries <= 0)
				ingress_cfg.enable_vlan_filt = 0;
			else
				ingress_cfg.enable_vlan_filt = 1;

			if(cfg_action == CONFIGURE)
				vlan_id.valid_bits  |= (1UL << filtnum);
			else
				vlan_id.valid_bits  &= ~(1UL << filtnum);

		}else{
			ingress_cfg.enable_vlan_filt = 0;
			vlan_id.valid_bits  = 0;
		}

		ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_V2,
				port_index,&vlan_id);


	}

	ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
			ECPRI_UDP_FH_INGRESS_CONFIG_P_V2,
			port_index,
			&ingress_cfg);


	return 0;
}


/**
 * ecpri_qudp_ingress_init_cfg()
 *
 *
 * Returns:	0 on success, negative on failure
 */
static int ecpriss_qudp_ingress_init_cfg(void)
{
	int ret = 0;
	int port_type = 0;
	int port_idx = 0;

	ecpri_qudp_hwio_def_ecpri_udp_fh_debug_features_cfg_s udp_fh_debug_feature_cfg;
	ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_DEBUG_FEATURES_CFG,
				0,
				&udp_fh_debug_feature_cfg);

	 udp_fh_debug_feature_cfg.watermark_en = 1;
	 udp_fh_debug_feature_cfg.en_clear_watermark_on_read = 1;

 	 ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_DEBUG_FEATURES_CFG,
				0,
				&udp_fh_debug_feature_cfg);

	for(port_type=0;port_type<ECPRISS_PORT_TYPE_MAX;port_type++)
	{
		if(port_type == ECPRISS_PORT_TYPE_FH)
		{

			for(port_idx=0;port_idx<ecpriss_pdata->qudp_ctx->num_ports;port_idx++)
			{

				ecpriss_qudp_ingress_per_port_cfg_s       *ingress_cfg =
					&ecpriss_pdata->qudp_ctx->fh_port_cfg[port_idx].ingress_port_cfg;

				ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH ,
						ECPRI_UDP_FH_INGRESS_CONFIG_P,
						port_idx,
						&ingress_cfg->fh_ingress_config);

				ingress_cfg->fh_ingress_config.ipv4_cs_err_action = 1;
				ingress_cfg->fh_ingress_config.udp_cs_err_action = 1;
				ingress_cfg->fh_ingress_config.fcs_err_action = 1;
				ingress_cfg->fh_ingress_config.pkt_err_action = 1;
				ingress_cfg->fh_ingress_config.ip_len_err_action = 1;
				ingress_cfg->fh_ingress_config.vlan_filt_miss_action = 1;
				ingress_cfg->fh_ingress_config.ip_filt_miss_action = 1;
				ingress_cfg->fh_ingress_config.non_local_dst_action = 1;

				ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
						ECPRI_UDP_FH_INGRESS_CONFIG_P,
						port_idx,
						&ingress_cfg->fh_ingress_config);
				memset(&(ingress_cfg->fh_ingress_config),
						0,
						sizeof(ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_config_p_s));

				ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH ,
						ECPRI_UDP_FH_INGRESS_CONFIG_P,
						port_idx,
						&ingress_cfg->fh_ingress_config);

			}
		}
#if 0
		else if(port_type == ECPRISS_PORT_TYPE_L2)
		{
			for(port_idx=0;port_idx<ecpriss_pdata->qudp_ctx->num_ports;port_idx++)
			{
				ecpriss_qudp_ingress_per_port_cfg_s      *ingress_cfg =
					&(ecpriss_pdata->qudp_ctx->l2_port_cfg[port_idx].ingress_port_cfg);
				memset(&(ingress_cfg->l2_ingress_config),
						0,
						sizeof(ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_config_p_s));
				ingress_cfg->l2_ingress_config.enable_ip_dst_filt = ECPRISS_QUDP_REG_FIELD_ENABLE;
				ingress_cfg->l2_ingress_config.enable_udp_dst_class = ECPRISS_QUDP_REG_FIELD_ENABLE;
				ingress_cfg->l2_ingress_config.enable_vlan_filt = ECPRISS_QUDP_REG_FIELD_ENABLE;
				ingress_cfg->l2_ingress_config.enable_udp_cs_check = ECPRISS_QUDP_REG_FIELD_ENABLE;
				ingress_cfg->l2_ingress_config.enable_ip_len_check = ECPRISS_QUDP_REG_FIELD_ENABLE;
				ingress_cfg->l2_ingress_config.ip_filt_miss_action = ECPRISS_QUDP_REG_FIELD_ENABLE;
				ingress_cfg->l2_ingress_config.vlan_filt_miss_action = ECPRISS_QUDP_REG_FIELD_ENABLE;
				ingress_cfg->l2_ingress_config.ip_len_err_action = ECPRISS_QUDP_REG_FIELD_ENABLE;
				ingress_cfg->l2_ingress_config.pkt_err_action = ECPRISS_QUDP_REG_FIELD_ENABLE;
				ingress_cfg->l2_ingress_config.disable_st_and_fw = ECPRISS_QUDP_REG_FIELD_ENABLE;
				ingress_cfg->l2_ingress_config.use_external_not_local_mac_dst = ECPRISS_QUDP_REG_FIELD_ENABLE;
				ingress_cfg->l2_ingress_config.last_in_chain = ECPRISS_QUDP_REG_FIELD_ENABLE;
				//ingress_cfg->l2_ingress_config.enable_shared_filtering_2_links = ECPRISS_QUDP_REG_FIELD_ENABLE;
				//ingress_cfg->l2_ingress_config.enable_shared_filtering_4_links = ECPRISS_QUDP_REG_FIELD_ENABLE;
				ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
						ECPRI_UDP_L2_INGRESS_CONFIG_P,
						port_idx,
						&ingress_cfg->l2_ingress_config);
			}
		}
#endif
	}
	return ret;
}

static int ecpriss_qudp_ingress_init_cfg_v2(void)
{
	int ret = 0;
	int port_type = 0;
	int port_idx = 0;



	for(port_type=0;port_type<ECPRISS_PORT_TYPE_MAX;port_type++)
	{
		if(port_type == ECPRISS_PORT_TYPE_FH)
		{

			for(port_idx=0;port_idx<ecpriss_pdata_v2->qudp_ctx_v2->num_ports;port_idx++)
			{

				ecpriss_qudp_ingress_per_port_cfg_s_v2       *ingress_cfg =
					&ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_idx].ingress_port_cfg;

				ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH ,
						ECPRI_UDP_FH_INGRESS_CONFIG_P_V2,
						port_idx,
						&ingress_cfg->fh_ingress_config);

				ingress_cfg->fh_ingress_config.ipv4_cs_err_action = ECPRISS_QUDP_ACTION_DISCARD;
				ingress_cfg->fh_ingress_config.udp_cs_err_action = ECPRISS_QUDP_ACTION_DISCARD;
				ingress_cfg->fh_ingress_config.fcs_err_action = ECPRISS_QUDP_ACTION_DISCARD;
				ingress_cfg->fh_ingress_config.pkt_err_action = ECPRISS_QUDP_ACTION_DISCARD;
				ingress_cfg->fh_ingress_config.ip_len_err_action = ECPRISS_QUDP_ACTION_DISCARD;
				ingress_cfg->fh_ingress_config.vlan_filt_miss_action = ECPRISS_QUDP_ACTION_DISCARD;
				ingress_cfg->fh_ingress_config.ip_filt_miss_action = ECPRISS_QUDP_ACTION_DISCARD;
				ingress_cfg->fh_ingress_config.non_local_dst_action = ECPRISS_QUDP_ACTION_DISCARD;

				ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
						ECPRI_UDP_FH_INGRESS_CONFIG_P_V2,
						port_idx,
						&ingress_cfg->fh_ingress_config);
				memset(&(ingress_cfg->fh_ingress_config),
						0,
						sizeof(ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_config_p_s_v2));

				ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH ,
						ECPRI_UDP_FH_INGRESS_CONFIG_P_V2,
						port_idx,
						&ingress_cfg->fh_ingress_config);

			}
		}
	}
	return ret;
}

int ecpriss_qudp_ingress_init_cfg_modify_v2(int action)
{
	int ret = 0;
	int port_type = 0;
	int port_idx = 0;



	for(port_type=0;port_type<ECPRISS_PORT_TYPE_MAX;port_type++)
	{
		if(port_type == ECPRISS_PORT_TYPE_FH)
		{

			for(port_idx=0;port_idx<ecpriss_pdata_v2->qudp_ctx_v2->num_ports;port_idx++)
			{

				ecpriss_qudp_ingress_per_port_cfg_s_v2       *ingress_cfg =
					&ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_idx].ingress_port_cfg;

				ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH ,
						ECPRI_UDP_FH_INGRESS_CONFIG_P_V2,
						port_idx,
						&ingress_cfg->fh_ingress_config);

				ingress_cfg->fh_ingress_config.ipv4_cs_err_action = action;
				ingress_cfg->fh_ingress_config.udp_cs_err_action = action;
				ingress_cfg->fh_ingress_config.fcs_err_action = action;
				ingress_cfg->fh_ingress_config.pkt_err_action = action;
				ingress_cfg->fh_ingress_config.ip_len_err_action = action;
				ingress_cfg->fh_ingress_config.vlan_filt_miss_action = action;
				ingress_cfg->fh_ingress_config.ip_filt_miss_action = action;
				ingress_cfg->fh_ingress_config.non_local_dst_action = action;

				ECPRILOGINFO("ecpriss_qudp_ingress_init_cfg_modify_v2: action %d\n",action);

				ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
						ECPRI_UDP_FH_INGRESS_CONFIG_P_V2,
						port_idx,
						&ingress_cfg->fh_ingress_config);


			}
		}
	}
	return ret;
}

static int ecpriss_qudp_egress_init_cfg_v2(void)
{
	int ret = 0;
	int port_type = 0;
	int port_idx = 0;

	for(port_type=0;port_type<ECPRISS_PORT_TYPE_MAX;port_type++)
	{
		if(port_type == ECPRISS_PORT_TYPE_FH)
		{

			for(port_idx=0;port_idx<ecpriss_pdata_v2->qudp_ctx_v2->num_ports;port_idx++)
			{

				ecpriss_qudp_egress_per_port_cfg_s_v2 *egress_cfg =
					&ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_idx].egress_cfg;

					ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH ,
						ECPRI_UDP_FH_EGRESS_CONFIG_P_V2,
						port_idx,
						&egress_cfg->fh_egress_config);

				egress_cfg->fh_egress_config.calc_ip_udp_len_from_byte_count = 0;
				egress_cfg->fh_egress_config.bypassed_packets_vport_action = 0;
				egress_cfg->fh_egress_config.bypassed_packets_vport = 0;
				egress_cfg->fh_egress_config.disable_padding_removal = 0;
				egress_cfg->fh_egress_config.l2_encap_index_override_en = 0;
				egress_cfg->fh_egress_config.l3_encap_index_override_en = 0;
				egress_cfg->fh_egress_config.disable_ptp_detection = 0;

				ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
						ECPRI_UDP_FH_EGRESS_CONFIG_P_V2,
						port_idx,
						&egress_cfg->fh_egress_config);

				ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
						ECPRI_UDP_FH_EGRESS_CONFIG_P_V2,
						port_idx,
						&egress_cfg->fh_egress_config);

			}
		}
	}
	return ret;
}


/**
 *  ecpriss_qudp_rx_filter()
 *
 *
 * Returns:	0 on success, negative on failure
 */
static void ecpriss_qudp_configure_mtu(void)
{
	int port_type=0;
	int port_idx=0;
	ecpriss_qudp_egress_per_port_cfg_s  *egress_cfg;
	eth_ecpriss_port_params_s   *fh_eth_cfg ;
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_mtu_p_s fh_egress_eth_mtu_p;
	for(port_type=0;port_type<ECPRISS_PORT_TYPE_MAX;port_type++)
	{
		if(port_type == ECPRISS_PORT_TYPE_FH)
		{
			for(port_idx=0;port_idx<ecpriss_pdata->qudp_ctx->num_ports;port_idx++)
			{


				egress_cfg = &(ecpriss_pdata->qudp_ctx->fh_port_cfg[port_idx].egress_cfg);

				fh_eth_cfg = &(ecpriss_pdata->qudp_ctx->fh_port_cfg[port_idx].eth_cfg);

				memset(&fh_egress_eth_mtu_p ,0, sizeof(fh_egress_eth_mtu_p));

				ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
						ECPRI_UDP_FH_EGRESS_ETH_MTU_P,
						port_idx,
						&fh_egress_eth_mtu_p);


				fh_egress_eth_mtu_p.value = ECPRISS_ETH_QUDP_MTU_SIZE_V4;
				ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
						ECPRI_UDP_FH_EGRESS_ETH_MTU_P,
						port_idx,
						&fh_egress_eth_mtu_p);

			}
		}
		else if(port_type == ECPRISS_PORT_TYPE_C2C)
		{

#if 0
			for(port_idx=0;port_idx<ecpriss_pdata->qudp_ctx->num_ports;port_idx++)
			{
				ecpriss_qudp_egress_per_port_cfg_s       *egress_cfg =
					&(ecpriss_pdata->qudp_ctx->c2c_port_cfg[port_idx].egress_cfg);

				eth_ecpriss_port_params_s   *c2c_eth_cfg =
					&(ecpriss_pdata->qudp_ctx->c2c_port_cfg[port_idx].eth_cfg);

				ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_eth_mtu_p_s c2c_egress_eth_mtu_p;

				/*Check if MTU is per link or per port*/
				egress_cfg->egress_eth_mtu.value = c2c_eth_cfg->port_mtu;
				c2c_egress_eth_mtu_p.value = c2c_eth_cfg->port_mtu;
				//egress_cfg->egress_eth_mtu.value = ECPRISS_ETH_MTU_SIZE;
				ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_C2C,
						ECPRI_UDP_C2C_EGRESS_ETH_MTU_P,
						port_idx,
						&c2c_egress_eth_mtu_p);
			}
#endif
		}
		else if (port_type == ECPRISS_PORT_TYPE_L2)
		{
#if 0
			for(port_idx=0;port_idx<ecpriss_pdata->qudp_ctx->num_ports;port_idx++)
			{
				ecpriss_qudp_egress_per_port_cfg_s       *egress_cfg =
					&(ecpriss_pdata->qudp_ctx->l2_port_cfg[port_idx].egress_cfg);

				eth_ecpriss_port_params_s   *l2_eth_cfg =
					&(ecpriss_pdata->qudp_ctx->l2_port_cfg[port_idx].eth_cfg);

				ecpri_qudp_hwio_def_ecpri_udp_l2_egress_eth_mtu_p_s l2_egress_eth_mtu_p;
				/*Check if MTU is per link or per port*/
				egress_cfg->egress_eth_mtu.value = l2_eth_cfg->port_mtu;
				l2_egress_eth_mtu_p.value = l2_eth_cfg->port_mtu;
				//egress_cfg->egress_eth_mtu.value = ECPRISS_ETH_MTU_SIZE;
				ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_L2,
						ECPRI_UDP_L2_EGRESS_ETH_MTU_P,
						port_idx,
						&l2_egress_eth_mtu_p);
			}
#endif

		}
	}
	return;
}
static void ecpriss_qudp_configure_mtu_v2(void)
{
	int port_type=0;
	int port_idx=0;
	ecpriss_qudp_egress_per_port_cfg_s_v2  *egress_cfg;
	eth_ecpriss_port_params_s   *fh_eth_cfg ;
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_mtu_p_s_v2 fh_egress_eth_mtu_p;

	for(port_type=0;port_type<ECPRISS_PORT_TYPE_MAX;port_type++)
	{
		if(port_type == ECPRISS_PORT_TYPE_FH)
		{
			for(port_idx=0;port_idx<ecpriss_pdata_v2->qudp_ctx_v2->num_ports;port_idx++)
			{


				egress_cfg = &(ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_idx].egress_cfg);

				fh_eth_cfg = &(ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_idx].eth_cfg);

				memset(&fh_egress_eth_mtu_p ,0, sizeof(fh_egress_eth_mtu_p));

				ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
						ECPRI_UDP_FH_EGRESS_ETH_MTU_P_V2,
						port_idx,
						&fh_egress_eth_mtu_p);


				fh_egress_eth_mtu_p.value = ECPRISS_ETH_QUDP_MTU_SIZE_V4;
				ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
						ECPRI_UDP_FH_EGRESS_ETH_MTU_P_V2,
						port_idx,
						&fh_egress_eth_mtu_p);

			}
		}
		else if(port_type == ECPRISS_PORT_TYPE_C2C)
		{

		}
		else if (port_type == ECPRISS_PORT_TYPE_L2)
		{

		}
	}
	return;
}



static irqreturn_t ecpriss_qudp_isr(int irq, void *ctxt)
{
	unsigned long flags = 0;
	int port_index;
	//Todo: check with respect to spinlock_irqsave and spinlock_irqrestore
	spin_lock_irqsave(&ecpriss_pdata->irq_lock, flags);

	for(port_index=0;port_index<ECPRISS_PORT_MAX;port_index++) {
		ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_status_0_port_p_s fh_udp_sw_irq_status_0_port_p;
		ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_status_1_port_p_s fh_udp_sw_irq_status_1_port_p;

		ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_clr_0_port_p_s fh_udp_sw_irq_clr_0_port_p;
		ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_clr_1_port_p_s fh_udp_sw_irq_clr_1_port_p;
		ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_P,
				port_index,
				&fh_udp_sw_irq_status_0_port_p);

		ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_P,
				port_index,
				&fh_udp_sw_irq_status_1_port_p);

		/* Increment stats
		link 0 */
		if(fh_udp_sw_irq_status_0_port_p.egress_mtu_err_packet_link_0) {
			fh_udp_sw_irq_clr_0_port_p.egress_mtu_err_packet_link_0 = 1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.egress_mtu_err_packet_link[0]++;
		}

		if(fh_udp_sw_irq_status_0_port_p.ingress_fcs_err_packet_link_0) {
			fh_udp_sw_irq_clr_0_port_p.ingress_fcs_err_packet_link_0 = 1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_fcs_err_packet_link[0]++;
		}

		if(fh_udp_sw_irq_status_0_port_p.ingress_pkt_fifo_empty_before_eop_link_0) {
			fh_udp_sw_irq_status_0_port_p.ingress_pkt_fifo_empty_before_eop_link_0 = 1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_pkt_fifo_empty_before_eop_link[0]++;
		}

		if(fh_udp_sw_irq_status_0_port_p.ingress_ipv4_cs_error_link_0) {
			fh_udp_sw_irq_clr_0_port_p.ingress_ipv4_cs_error_link_0 = 1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_ipv4_cs_error_link[0]++;
		}

		if(fh_udp_sw_irq_status_0_port_p.ingress_ip_filtered_packet_link_0) {
			fh_udp_sw_irq_clr_0_port_p.ingress_ip_filtered_packet_link_0 = 1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_ip_filtered_packet_link[0]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_vlan_filtered_packet_link_0) {
			fh_udp_sw_irq_clr_0_port_p.ingress_vlan_filtered_packet_link_0 = 1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_vlan_filtered_packet_link[0]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_sec_err_packet_link_0) {
			fh_udp_sw_irq_clr_0_port_p.ingress_sec_err_packet_link_0 = 1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_sec_err_packet_link[0]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_ip_len_err_packet_link_0) {
			fh_udp_sw_irq_clr_0_port_p.ingress_ip_len_err_packet_link_0 = 1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_ip_len_err_packet_link[0]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_trap_rule_0_link_0) {
			fh_udp_sw_irq_clr_0_port_p.ingress_trap_rule_0_link_0 = 1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_trap_rule_0_link[0]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_trap_rule_1_link_0) {
			fh_udp_sw_irq_clr_0_port_p.ingress_trap_rule_1_link_0 = 1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_trap_rule_1_link[0]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_trap_rule_2_link_0) {
			fh_udp_sw_irq_clr_0_port_p.ingress_trap_rule_2_link_0 = 1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_trap_rule_2_link[0]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_trap_rule_3_link_0) {
			fh_udp_sw_irq_clr_0_port_p.ingress_trap_rule_3_link_0 = 1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_trap_rule_3_link[0]++;
		}

		if(fh_udp_sw_irq_status_0_port_p.ingress_last_in_chain_non_local_dst_packet_link_0) {
			fh_udp_sw_irq_clr_0_port_p.ingress_last_in_chain_non_local_dst_packet_link_0 = 1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_last_in_chain_non_local_dst_packet_link[0]++;
		}


		/* link1 */

		if(fh_udp_sw_irq_status_0_port_p.egress_mtu_err_packet_link_1) {
			fh_udp_sw_irq_clr_0_port_p.egress_mtu_err_packet_link_1 =1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.egress_mtu_err_packet_link[1]++;
		}

		if(fh_udp_sw_irq_status_0_port_p.ingress_fcs_err_packet_link_1) {
			fh_udp_sw_irq_clr_0_port_p.ingress_fcs_err_packet_link_1 = 1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_fcs_err_packet_link[1]++;
		}

		if(fh_udp_sw_irq_status_0_port_p.ingress_pkt_fifo_empty_before_eop_link_1) {
			fh_udp_sw_irq_clr_0_port_p.ingress_pkt_fifo_empty_before_eop_link_1 = 1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_pkt_fifo_empty_before_eop_link[1]++;
		}

		if(fh_udp_sw_irq_status_0_port_p.ingress_ipv4_cs_error_link_1) {
			fh_udp_sw_irq_clr_0_port_p.ingress_ipv4_cs_error_link_1 = 1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_ipv4_cs_error_link[1]++;
		}

		if(fh_udp_sw_irq_status_0_port_p.ingress_ip_filtered_packet_link_1) {
			fh_udp_sw_irq_clr_0_port_p.ingress_ip_filtered_packet_link_1 = 1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_ip_filtered_packet_link[1]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_vlan_filtered_packet_link_1) {
			fh_udp_sw_irq_clr_0_port_p.ingress_vlan_filtered_packet_link_1 = 1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_vlan_filtered_packet_link[1]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_sec_err_packet_link_1) {
			fh_udp_sw_irq_clr_0_port_p.ingress_sec_err_packet_link_1 = 1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_sec_err_packet_link[1]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_ip_len_err_packet_link_1) {
			fh_udp_sw_irq_clr_0_port_p.ingress_ip_len_err_packet_link_1 = 1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_ip_len_err_packet_link[1]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_trap_rule_0_link_1) {
			fh_udp_sw_irq_clr_0_port_p.ingress_trap_rule_0_link_1 = 1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_trap_rule_0_link[1]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_trap_rule_1_link_1) {
			fh_udp_sw_irq_clr_0_port_p.ingress_trap_rule_1_link_1 = 1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_trap_rule_1_link[1]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_trap_rule_2_link_1) {
			fh_udp_sw_irq_clr_0_port_p.ingress_trap_rule_2_link_1 = 1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_trap_rule_2_link[1]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_trap_rule_3_link_1) {
			fh_udp_sw_irq_clr_0_port_p.ingress_trap_rule_3_link_1 = 1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_trap_rule_3_link[1]++;
		}

		if(fh_udp_sw_irq_status_0_port_p.ingress_last_in_chain_non_local_dst_packet_link_1) {
			fh_udp_sw_irq_clr_0_port_p.ingress_last_in_chain_non_local_dst_packet_link_1 = 1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_last_in_chain_non_local_dst_packet_link[1]++;
		}


		/* link 2 */

		if(fh_udp_sw_irq_status_1_port_p.egress_mtu_err_packet_link_2) {
			fh_udp_sw_irq_status_1_port_p.egress_mtu_err_packet_link_2=1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.egress_mtu_err_packet_link[2]++;
		}

		if(fh_udp_sw_irq_status_1_port_p.ingress_fcs_err_packet_link_2) {
			fh_udp_sw_irq_clr_1_port_p.ingress_fcs_err_packet_link_2=1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_fcs_err_packet_link[2]++;
		}

		if(fh_udp_sw_irq_status_1_port_p.ingress_pkt_fifo_empty_before_eop_link_2) {
			fh_udp_sw_irq_clr_1_port_p.ingress_pkt_fifo_empty_before_eop_link_2=1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_pkt_fifo_empty_before_eop_link[2]++;
		}

		if(fh_udp_sw_irq_status_1_port_p.ingress_ipv4_cs_error_link_2) {
			fh_udp_sw_irq_clr_1_port_p.ingress_ipv4_cs_error_link_2=1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_ipv4_cs_error_link[2]++;
		}

		if(fh_udp_sw_irq_status_1_port_p.ingress_ip_filtered_packet_link_2) {
			fh_udp_sw_irq_clr_1_port_p.ingress_ip_filtered_packet_link_2=1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_ip_filtered_packet_link[2]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_vlan_filtered_packet_link_2) {
			fh_udp_sw_irq_clr_1_port_p.ingress_vlan_filtered_packet_link_2=1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_vlan_filtered_packet_link[2]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_sec_err_packet_link_2) {
			fh_udp_sw_irq_clr_1_port_p.ingress_sec_err_packet_link_2=1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_sec_err_packet_link[2]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_ip_len_err_packet_link_2) {
			fh_udp_sw_irq_clr_1_port_p.ingress_ip_len_err_packet_link_2=1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_ip_len_err_packet_link[2]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_trap_rule_0_link_2) {
			fh_udp_sw_irq_clr_1_port_p.ingress_trap_rule_0_link_2=1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_trap_rule_0_link[2]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_trap_rule_1_link_2) {
			fh_udp_sw_irq_clr_1_port_p.ingress_trap_rule_1_link_2=1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_trap_rule_1_link[2]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_trap_rule_2_link_2) {
			fh_udp_sw_irq_clr_1_port_p.ingress_trap_rule_2_link_2=1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_trap_rule_2_link[2]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_trap_rule_3_link_2) {
			fh_udp_sw_irq_clr_1_port_p.ingress_trap_rule_3_link_2=1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_trap_rule_3_link[2]++;
		}

		if(fh_udp_sw_irq_status_1_port_p.ingress_last_in_chain_non_local_dst_packet_link_2) {
			fh_udp_sw_irq_clr_1_port_p.ingress_last_in_chain_non_local_dst_packet_link_2=1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_last_in_chain_non_local_dst_packet_link[2]++;
		}

		/* link 3 */
		if(fh_udp_sw_irq_status_1_port_p.egress_mtu_err_packet_link_3) {
			fh_udp_sw_irq_clr_1_port_p.egress_mtu_err_packet_link_3=1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.egress_mtu_err_packet_link[3]++;
		}

		if(fh_udp_sw_irq_status_1_port_p.ingress_fcs_err_packet_link_3) {
			fh_udp_sw_irq_clr_1_port_p.ingress_fcs_err_packet_link_3=1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_fcs_err_packet_link[3]++;
		}

		if(fh_udp_sw_irq_status_1_port_p.ingress_pkt_fifo_empty_before_eop_link_3) {
			fh_udp_sw_irq_clr_1_port_p.ingress_pkt_fifo_empty_before_eop_link_3=1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_pkt_fifo_empty_before_eop_link[3]++;
		}

		if(fh_udp_sw_irq_status_1_port_p.ingress_ipv4_cs_error_link_3) {
			fh_udp_sw_irq_clr_1_port_p.ingress_ipv4_cs_error_link_3=1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_ipv4_cs_error_link[3]++;
		}

		if(fh_udp_sw_irq_status_1_port_p.ingress_ip_filtered_packet_link_3) {
			fh_udp_sw_irq_clr_1_port_p.ingress_ip_filtered_packet_link_3=1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_ip_filtered_packet_link[3]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_vlan_filtered_packet_link_3) {
			fh_udp_sw_irq_clr_1_port_p.ingress_vlan_filtered_packet_link_3=1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_vlan_filtered_packet_link[3]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_sec_err_packet_link_3) {
			fh_udp_sw_irq_clr_1_port_p.ingress_sec_err_packet_link_3=1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_sec_err_packet_link[3]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_ip_len_err_packet_link_3) {
			fh_udp_sw_irq_clr_1_port_p.ingress_ip_len_err_packet_link_3=1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_ip_len_err_packet_link[3]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_trap_rule_0_link_3) {
			fh_udp_sw_irq_clr_1_port_p.ingress_trap_rule_0_link_3=1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_trap_rule_0_link[3]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_trap_rule_1_link_3) {
			fh_udp_sw_irq_clr_1_port_p.ingress_trap_rule_1_link_3=1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_trap_rule_1_link[3]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_trap_rule_2_link_3) {
			fh_udp_sw_irq_clr_1_port_p.ingress_trap_rule_2_link_3=1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_trap_rule_2_link[3]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_trap_rule_3_link_3) {
			fh_udp_sw_irq_clr_1_port_p.ingress_trap_rule_3_link_3=1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_trap_rule_3_link[3]++;
		}

		if(fh_udp_sw_irq_status_1_port_p.ingress_last_in_chain_non_local_dst_packet_link_3) {
			fh_udp_sw_irq_clr_1_port_p.ingress_last_in_chain_non_local_dst_packet_link_3=1;
			ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].interrupt_stats.ingress_last_in_chain_non_local_dst_packet_link[3]++;
		}

		ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_P,
				port_index,
				&fh_udp_sw_irq_clr_0_port_p);

		ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_P,
				port_index,
				&fh_udp_sw_irq_clr_1_port_p);

	}

	spin_unlock_irqrestore(&ecpriss_pdata->irq_lock, flags);
	return IRQ_HANDLED;
}
static irqreturn_t ecpriss_qudp_isr_v2(int irq, void *ctxt)
{
	unsigned long flags = 0;
	int port_index;
	//Todo: check with respect to spinlock_irqsave and spinlock_irqrestore
	spin_lock_irqsave(&ecpriss_pdata_v2->irq_lock, flags);


	for(port_index=0;port_index<ECPRISS_PORT_MAX;port_index++) {

		ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_status_0_port_p_s_v2 fh_udp_sw_irq_status_0_port_p;
		ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_status_1_port_p_s_v2 fh_udp_sw_irq_status_1_port_p;

		ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_clr_0_port_p_s_v2 fh_udp_sw_irq_clr_0_port_p;
		ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_clr_1_port_p_s_v2 fh_udp_sw_irq_clr_1_port_p;

		ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_P_V2,
				port_index,
				&fh_udp_sw_irq_status_0_port_p);

		ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_P_V2,
				port_index,
				&fh_udp_sw_irq_status_1_port_p);

		memcpy(&ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_cfg_v2.fh_udp_sw_irq_status_0_port_p,&fh_udp_sw_irq_status_0_port_p,sizeof(fh_udp_sw_irq_status_0_port_p));
		memcpy(&ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_cfg_v2.fh_udp_sw_irq_status_1_port_p,&fh_udp_sw_irq_status_1_port_p,sizeof(fh_udp_sw_irq_status_1_port_p));

		if(fh_udp_sw_irq_status_0_port_p.ingress_vlan_filtered_packet_link_0) {
			fh_udp_sw_irq_clr_0_port_p.ingress_vlan_filtered_packet_link_0 = 1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_vlan_filtered_packet_link[0]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_sec_err_packet_link_0) {
			fh_udp_sw_irq_clr_0_port_p.ingress_sec_err_packet_link_0 = 1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_sec_err_packet_link[0]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_ip_len_err_packet_link_0) {
			fh_udp_sw_irq_clr_0_port_p.ingress_ip_len_err_packet_link_0 = 1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_ip_len_err_packet_link[0]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_trap_rule_0_link_0) {
			fh_udp_sw_irq_clr_0_port_p.ingress_trap_rule_0_link_0 = 1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_trap_rule_0_link[0]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_trap_rule_1_link_0) {
			fh_udp_sw_irq_clr_0_port_p.ingress_trap_rule_1_link_0 = 1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_trap_rule_1_link[0]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_trap_rule_2_link_0) {
			fh_udp_sw_irq_clr_0_port_p.ingress_trap_rule_2_link_0 = 1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_trap_rule_2_link[0]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_trap_rule_3_link_0) {
			fh_udp_sw_irq_clr_0_port_p.ingress_trap_rule_3_link_0 = 1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_trap_rule_3_link[0]++;
		}

		if(fh_udp_sw_irq_status_0_port_p.ingress_last_in_chain_non_local_dst_packet_link_0) {
			fh_udp_sw_irq_clr_0_port_p.ingress_last_in_chain_non_local_dst_packet_link_0 = 1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_last_in_chain_non_local_dst_packet_link[0]++;
		}

		if(fh_udp_sw_irq_status_0_port_p.ingress_timestamped_packets_bw_too_high_link_0) {
			fh_udp_sw_irq_clr_0_port_p.ingress_timestamped_packets_bw_too_high_link_0 = 1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_timestamped_packets_bw_too_high_link[0]++;
		}



		/* link1 */

		if(fh_udp_sw_irq_status_0_port_p.egress_mtu_err_packet_link_1) {
			fh_udp_sw_irq_clr_0_port_p.egress_mtu_err_packet_link_1 =1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.egress_mtu_err_packet_link[1]++;
		}

		if(fh_udp_sw_irq_status_0_port_p.ingress_fcs_err_packet_link_1) {
			fh_udp_sw_irq_clr_0_port_p.ingress_fcs_err_packet_link_1 = 1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_fcs_err_packet_link[1]++;
		}

		if(fh_udp_sw_irq_status_0_port_p.ingress_pkt_fifo_empty_before_eop_link_1) {
			fh_udp_sw_irq_clr_0_port_p.ingress_pkt_fifo_empty_before_eop_link_1 = 1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_pkt_fifo_empty_before_eop_link[1]++;
		}

		if(fh_udp_sw_irq_status_0_port_p.ingress_ipv4_cs_error_link_1) {
			fh_udp_sw_irq_clr_0_port_p.ingress_ipv4_cs_error_link_1 = 1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_ipv4_cs_error_link[1]++;
		}

		if(fh_udp_sw_irq_status_0_port_p.ingress_ip_filtered_packet_link_1) {
			fh_udp_sw_irq_clr_0_port_p.ingress_ip_filtered_packet_link_1 = 1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_ip_filtered_packet_link[1]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_vlan_filtered_packet_link_1) {
			fh_udp_sw_irq_clr_0_port_p.ingress_vlan_filtered_packet_link_1 = 1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_vlan_filtered_packet_link[1]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_sec_err_packet_link_1) {
			fh_udp_sw_irq_clr_0_port_p.ingress_sec_err_packet_link_1 = 1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_sec_err_packet_link[1]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_ip_len_err_packet_link_1) {
			fh_udp_sw_irq_clr_0_port_p.ingress_ip_len_err_packet_link_1 = 1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_ip_len_err_packet_link[1]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_trap_rule_0_link_1) {
			fh_udp_sw_irq_clr_0_port_p.ingress_trap_rule_0_link_1 = 1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_trap_rule_0_link[1]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_trap_rule_1_link_1) {
			fh_udp_sw_irq_clr_0_port_p.ingress_trap_rule_1_link_1 = 1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_trap_rule_1_link[1]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_trap_rule_2_link_1) {
			fh_udp_sw_irq_clr_0_port_p.ingress_trap_rule_2_link_1 = 1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_trap_rule_2_link[1]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_trap_rule_3_link_1) {
			fh_udp_sw_irq_clr_0_port_p.ingress_trap_rule_3_link_1 = 1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_trap_rule_3_link[1]++;
		}

		if(fh_udp_sw_irq_status_0_port_p.ingress_last_in_chain_non_local_dst_packet_link_1) {
			fh_udp_sw_irq_clr_0_port_p.ingress_last_in_chain_non_local_dst_packet_link_1 = 1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_last_in_chain_non_local_dst_packet_link[1]++;
		}


		if(fh_udp_sw_irq_status_0_port_p.ingress_timestamped_packets_bw_too_high_link_1) {
			fh_udp_sw_irq_clr_0_port_p.ingress_timestamped_packets_bw_too_high_link_1 = 1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_timestamped_packets_bw_too_high_link[1]++;
		}



		/* link 2 */

		if(fh_udp_sw_irq_status_1_port_p.egress_mtu_err_packet_link_2) {
			fh_udp_sw_irq_status_1_port_p.egress_mtu_err_packet_link_2=1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.egress_mtu_err_packet_link[2]++;
		}

		if(fh_udp_sw_irq_status_1_port_p.ingress_fcs_err_packet_link_2) {
			fh_udp_sw_irq_clr_1_port_p.ingress_fcs_err_packet_link_2=1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_fcs_err_packet_link[2]++;
		}

		if(fh_udp_sw_irq_status_1_port_p.ingress_pkt_fifo_empty_before_eop_link_2) {
			fh_udp_sw_irq_clr_1_port_p.ingress_pkt_fifo_empty_before_eop_link_2=1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_pkt_fifo_empty_before_eop_link[2]++;
		}

		if(fh_udp_sw_irq_status_1_port_p.ingress_ipv4_cs_error_link_2) {
			fh_udp_sw_irq_clr_1_port_p.ingress_ipv4_cs_error_link_2=1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_ipv4_cs_error_link[2]++;
		}

		if(fh_udp_sw_irq_status_1_port_p.ingress_ip_filtered_packet_link_2) {
			fh_udp_sw_irq_clr_1_port_p.ingress_ip_filtered_packet_link_2=1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_ip_filtered_packet_link[2]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_vlan_filtered_packet_link_2) {
			fh_udp_sw_irq_clr_1_port_p.ingress_vlan_filtered_packet_link_2=1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_vlan_filtered_packet_link[2]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_sec_err_packet_link_2) {
			fh_udp_sw_irq_clr_1_port_p.ingress_sec_err_packet_link_2=1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_sec_err_packet_link[2]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_ip_len_err_packet_link_2) {
			fh_udp_sw_irq_clr_1_port_p.ingress_ip_len_err_packet_link_2=1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_ip_len_err_packet_link[2]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_trap_rule_0_link_2) {
			fh_udp_sw_irq_clr_1_port_p.ingress_trap_rule_0_link_2=1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_trap_rule_0_link[2]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_trap_rule_1_link_2) {
			fh_udp_sw_irq_clr_1_port_p.ingress_trap_rule_1_link_2=1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_trap_rule_1_link[2]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_trap_rule_2_link_2) {
			fh_udp_sw_irq_clr_1_port_p.ingress_trap_rule_2_link_2=1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_trap_rule_2_link[2]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_trap_rule_3_link_2) {
			fh_udp_sw_irq_clr_1_port_p.ingress_trap_rule_3_link_2=1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_trap_rule_3_link[2]++;
		}

		if(fh_udp_sw_irq_status_1_port_p.ingress_last_in_chain_non_local_dst_packet_link_2) {
			fh_udp_sw_irq_clr_1_port_p.ingress_last_in_chain_non_local_dst_packet_link_2=1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_last_in_chain_non_local_dst_packet_link[2]++;
		}

		if(fh_udp_sw_irq_status_1_port_p.ingress_timestamped_packets_bw_too_high_link_2) {
			fh_udp_sw_irq_clr_1_port_p.ingress_timestamped_packets_bw_too_high_link_2 = 1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_timestamped_packets_bw_too_high_link[2]++;
		}



		/* link 3 */
		if(fh_udp_sw_irq_status_1_port_p.egress_mtu_err_packet_link_3) {
			fh_udp_sw_irq_clr_1_port_p.egress_mtu_err_packet_link_3=1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.egress_mtu_err_packet_link[3]++;
		}

		if(fh_udp_sw_irq_status_1_port_p.ingress_fcs_err_packet_link_3) {
			fh_udp_sw_irq_clr_1_port_p.ingress_fcs_err_packet_link_3=1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_fcs_err_packet_link[3]++;
		}

		if(fh_udp_sw_irq_status_1_port_p.ingress_pkt_fifo_empty_before_eop_link_3) {
			fh_udp_sw_irq_clr_1_port_p.ingress_pkt_fifo_empty_before_eop_link_3=1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_pkt_fifo_empty_before_eop_link[3]++;
		}

		if(fh_udp_sw_irq_status_1_port_p.ingress_ipv4_cs_error_link_3) {
			fh_udp_sw_irq_clr_1_port_p.ingress_ipv4_cs_error_link_3=1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_ipv4_cs_error_link[3]++;
		}

		if(fh_udp_sw_irq_status_1_port_p.ingress_ip_filtered_packet_link_3) {
			fh_udp_sw_irq_clr_1_port_p.ingress_ip_filtered_packet_link_3=1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_ip_filtered_packet_link[3]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_vlan_filtered_packet_link_3) {
			fh_udp_sw_irq_clr_1_port_p.ingress_vlan_filtered_packet_link_3=1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_vlan_filtered_packet_link[3]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_sec_err_packet_link_3) {
			fh_udp_sw_irq_clr_1_port_p.ingress_sec_err_packet_link_3=1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_sec_err_packet_link[3]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_ip_len_err_packet_link_3) {
			fh_udp_sw_irq_clr_1_port_p.ingress_ip_len_err_packet_link_3=1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_ip_len_err_packet_link[3]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_trap_rule_0_link_3) {
			fh_udp_sw_irq_clr_1_port_p.ingress_trap_rule_0_link_3=1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_trap_rule_0_link[3]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_trap_rule_1_link_3) {
			fh_udp_sw_irq_clr_1_port_p.ingress_trap_rule_1_link_3=1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_trap_rule_1_link[3]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_trap_rule_2_link_3) {
			fh_udp_sw_irq_clr_1_port_p.ingress_trap_rule_2_link_3=1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_trap_rule_2_link[3]++;
		}


		if(fh_udp_sw_irq_status_1_port_p.ingress_trap_rule_3_link_3) {
			fh_udp_sw_irq_clr_1_port_p.ingress_trap_rule_3_link_3=1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_trap_rule_3_link[3]++;
		}

		if(fh_udp_sw_irq_status_1_port_p.ingress_last_in_chain_non_local_dst_packet_link_3) {
			fh_udp_sw_irq_clr_1_port_p.ingress_last_in_chain_non_local_dst_packet_link_3=1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_last_in_chain_non_local_dst_packet_link[3]++;
		}

		if(fh_udp_sw_irq_status_1_port_p.ingress_timestamped_packets_bw_too_high_link_3) {
			fh_udp_sw_irq_clr_1_port_p.ingress_timestamped_packets_bw_too_high_link_3 = 1;
			ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].interrupt_stats_v2.ingress_timestamped_packets_bw_too_high_link[3]++;
		}



		ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_P_V2,
				port_index,
				&fh_udp_sw_irq_clr_0_port_p);

		ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_P_V2,
				port_index,
				&fh_udp_sw_irq_clr_1_port_p);

	}

	spin_unlock_irqrestore(&ecpriss_pdata_v2->irq_lock, flags);
	return IRQ_HANDLED;
}
static int ecpriss_irq_init(ecpriss_qudp_interrupt_events_e qudp_irq,
		struct device *dev)
{
	int res= 0;

	struct platform_device *pdev = NULL;
	/*
	 *	 * c2c and l2 are not supported for now
	 *		 */
	if((qudp_irq == ECPRISS_UDP_FH_IRQ_PORT0) ||
			(qudp_irq == ECPRISS_UDP_FH_IRQ_PORT1) ||
			(qudp_irq == ECPRISS_UDP_FH_IRQ_PORT2)){
		ECPRILOGINFO("QUDP irq init\n");
	}else{
		return res;
	}
	do{

		pdev = to_platform_device(dev);

		if(dev ==  NULL)
		{
			ECPRILOGERR("ecpriss_irq_init pdev is NULL" );
			break;
		}
		ECPRILOGINFO("IRQ =  %d\n", qudp_irq_mapping[qudp_irq]);
		qudp_irq_mapping[qudp_irq] =  platform_get_irq(pdev, qudp_irq);

		res = request_irq(qudp_irq_mapping[qudp_irq], ecpriss_qudp_isr, IRQF_TRIGGER_HIGH, "ecpri_ss", NULL);

		if (res){
			ECPRILOGERR("IRQ request failed irq=%d res=%d\n",
					qudp_irq_mapping[qudp_irq], res);
			break;
		}
		ECPRILOGDBG("IRQ =  %d\n", qudp_irq_mapping[qudp_irq]);

		res = enable_irq_wake(qudp_irq_mapping[qudp_irq]);
		if (res){
			ECPRILOGERR("fail to enable IPA IRQ wakeup irq=%d res=%d\n",
					qudp_irq_mapping[qudp_irq], res);
			break;
		}

		ECPRILOGINFO("ecpriss_irq_init Interrupt Registration Success %d" , qudp_irq_mapping[qudp_irq]);

	}while (0);
	return res;
}
static int ecpriss_irq_init_v2(ecpriss_qudp_interrupt_events_e qudp_irq,
		struct device *dev)
{
	int res= 0;
	struct platform_device *pdev = NULL;
	/*
	 *	 * c2c and l2 are not supported for now
	 *		 */
	if((qudp_irq == ECPRISS_UDP_FH_IRQ_PORT0) ||
			(qudp_irq == ECPRISS_UDP_FH_IRQ_PORT1) ||
			(qudp_irq == ECPRISS_UDP_FH_IRQ_PORT2)){
		ECPRILOGINFO("QUDP irq init\n");
	}else{
		return res;
	}
	do{

		pdev = to_platform_device(dev);

		if(dev ==  NULL)
		{
			ECPRILOGERR("ecpriss_irq_init pdev is NULL" );
			break;
		}
		ECPRILOGINFO("IRQ =  %d\n", qudp_irq_mapping[qudp_irq]);
		qudp_irq_mapping[qudp_irq] =  platform_get_irq(pdev, qudp_irq);

		res = request_irq(qudp_irq_mapping[qudp_irq], ecpriss_qudp_isr_v2, IRQF_TRIGGER_HIGH, "ecpri_ss", NULL);

		if (res){
			ECPRILOGERR("IRQ request failed irq=%d res=%d\n",
					qudp_irq_mapping[qudp_irq], res);
			break;
		}
		ECPRILOGINFO("IRQ =  %d\n", qudp_irq_mapping[qudp_irq]);

		res = enable_irq_wake(qudp_irq_mapping[qudp_irq]);
		if (res){
			ECPRILOGERR("fail to enable IPA IRQ wakeup irq=%d res=%d\n",
					qudp_irq_mapping[qudp_irq], res);
			break;
		}

		ECPRILOGINFO("ecpriss_irq_init Interrupt Registration Success %d" , qudp_irq_mapping[qudp_irq]);

	}while (0);
	return res;
}

void ecpriss_qudp_irq_destroy_v2(void)
{
	uint32_t i = 0;

	for(i=0; i < QUDP_IRQ_MAX; i++){
		if((i == ECPRISS_UDP_FH_IRQ_PORT0) ||
				(i == ECPRISS_UDP_FH_IRQ_PORT1) ||
				(i == ECPRISS_UDP_FH_IRQ_PORT2)){

			disable_irq_wake(qudp_irq_mapping[i]);
			free_irq(qudp_irq_mapping[i],NULL);
		}
	}

}

/**
 * ecpri_qudp_reg_irq
 *
 *
 * Returns:	0 on success, negative on failure
 */
static int ecpriss_qudp_register_interrupts(uint8_t                 port_index,
		ecpriss_port_type_e     port_type,
		struct device						*dev)
{
	int res = 0;
	do{
		if(port_type == ECPRISS_PORT_TYPE_FH)
		{
			if(port_index == ECPRISS_PORT_0) {
				ecpriss_irq_init(ECPRISS_UDP_FH_IRQ_PORT0,dev);
			}
			else if(port_index == ECPRISS_PORT_1) {
				ecpriss_irq_init(ECPRISS_UDP_FH_IRQ_PORT1,dev);
			}
			else if(port_index == ECPRISS_PORT_2) {
				ecpriss_irq_init(ECPRISS_UDP_FH_IRQ_PORT2,dev);
			}
		}

		else if (port_type == ECPRISS_PORT_TYPE_C2C) {
			if(port_index == ECPRISS_PORT_0) {
				ecpriss_irq_init(ECPRISS_UDP_C2C_IRQ_PORT0,dev);
			}
			else if(port_index == ECPRISS_PORT_1) {
				ecpriss_irq_init(ECPRISS_UDP_C2C_IRQ_PORT1,dev);
			}
		}
		else if (port_type == ECPRISS_PORT_TYPE_L2) {
			ecpriss_irq_init(ECPRISS_UDP_L2_IRQ,dev);
		}

	}while (0);


	return res;
}

static int ecpriss_qudp_register_interrupts_v2(uint8_t                 port_index,
		ecpriss_port_type_e     port_type,
		struct device						*dev)
{
	do{
		if(port_type == ECPRISS_PORT_TYPE_FH)
		{
			if(port_index == ECPRISS_PORT_0) {
				ecpriss_irq_init_v2(ECPRISS_UDP_FH_IRQ_PORT0,dev);
			}
			else if(port_index == ECPRISS_PORT_1) {
				ecpriss_irq_init_v2(ECPRISS_UDP_FH_IRQ_PORT1,dev);
			}
			else if(port_index == ECPRISS_PORT_2) {
				ecpriss_irq_init_v2(ECPRISS_UDP_FH_IRQ_PORT2,dev);
			}
		}

		else if (port_type == ECPRISS_PORT_TYPE_C2C) {
			if(port_index == ECPRISS_PORT_0) {
				ecpriss_irq_init_v2(ECPRISS_UDP_C2C_IRQ_PORT0,dev);
			}
			else if(port_index == ECPRISS_PORT_1) {
				ecpriss_irq_init_v2(ECPRISS_UDP_C2C_IRQ_PORT1,dev);
			}
		}
		else if (port_type == ECPRISS_PORT_TYPE_L2) {
			ecpriss_irq_init_v2(ECPRISS_UDP_L2_IRQ,dev);
		}

	}while (0);


	return 0;
}


/*
static void ecpriss_qudp_enable_interrupts(uint8_t                 port_index,
		uint32_t                 port_type)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_mask_0_port_p_s fh_udp_sw_irq_mask_0_port_p;
	ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_mask_1_port_p_s fh_udp_sw_irq_mask_1_port_p;

	memset(&fh_udp_sw_irq_mask_0_port_p , 0, sizeof(fh_udp_sw_irq_mask_0_port_p) );
	memset(&fh_udp_sw_irq_mask_1_port_p , 0, sizeof(fh_udp_sw_irq_mask_1_port_p) );



	if(port_type == ECPRISS_PORT_TYPE_FH) {




		ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_P,
				port_index,
				&fh_udp_sw_irq_mask_0_port_p);


		ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_P,
				port_index,
				&fh_udp_sw_irq_mask_1_port_p);




		fh_udp_sw_irq_mask_0_port_p.egress_mtu_err_packet_link_0 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_fcs_err_packet_link_0 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_pkt_fifo_empty_before_eop_link_0 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_ipv4_cs_error_link_0 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_udp_cs_error_link_0 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_ip_filtered_packet_link_0 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_vlan_filtered_packet_link_0 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_sec_err_packet_link_0 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_ip_len_err_packet_link_0 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_trap_rule_0_link_0 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_trap_rule_1_link_0 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_trap_rule_2_link_0 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_trap_rule_3_link_0 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_last_in_chain_non_local_dst_packet_link_0 = 1;

		fh_udp_sw_irq_mask_0_port_p.egress_mtu_err_packet_link_1 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_fcs_err_packet_link_1 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_pkt_fifo_empty_before_eop_link_1 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_ipv4_cs_error_link_1 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_udp_cs_error_link_1 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_ip_filtered_packet_link_1 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_vlan_filtered_packet_link_1 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_sec_err_packet_link_1 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_ip_len_err_packet_link_1 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_trap_rule_0_link_1 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_trap_rule_1_link_1 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_trap_rule_2_link_1 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_trap_rule_3_link_1 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_last_in_chain_non_local_dst_packet_link_1 = 1;


		fh_udp_sw_irq_mask_1_port_p.egress_mtu_err_packet_link_2 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_fcs_err_packet_link_2 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_pkt_fifo_empty_before_eop_link_2 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_ipv4_cs_error_link_2 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_udp_cs_error_link_2 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_ip_filtered_packet_link_2 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_vlan_filtered_packet_link_2 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_sec_err_packet_link_2 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_ip_len_err_packet_link_2 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_trap_rule_0_link_2 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_trap_rule_1_link_2 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_trap_rule_2_link_2 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_trap_rule_3_link_2 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_last_in_chain_non_local_dst_packet_link_2 = 1;

		fh_udp_sw_irq_mask_1_port_p.egress_mtu_err_packet_link_3 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_fcs_err_packet_link_3 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_pkt_fifo_empty_before_eop_link_3 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_ipv4_cs_error_link_3 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_udp_cs_error_link_3 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_ip_filtered_packet_link_3 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_vlan_filtered_packet_link_3 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_sec_err_packet_link_3 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_ip_len_err_packet_link_3 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_trap_rule_0_link_3 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_trap_rule_1_link_3 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_trap_rule_2_link_3 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_trap_rule_3_link_3 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_last_in_chain_non_local_dst_packet_link_3 = 1;

		ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_P,
				port_index,
				&fh_udp_sw_irq_mask_0_port_p);

		ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_P,
				port_index,
				&fh_udp_sw_irq_mask_1_port_p);

	}

	return;
}
*/

static void ecpriss_qudp_disable_interrupts(uint8_t                 port_index,
		uint32_t                 port_type)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_mask_0_port_p_s fh_udp_sw_irq_mask_0_port_p;
	ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_mask_1_port_p_s fh_udp_sw_irq_mask_1_port_p;

	memset(&fh_udp_sw_irq_mask_0_port_p , 0, sizeof(fh_udp_sw_irq_mask_0_port_p) );
	memset(&fh_udp_sw_irq_mask_1_port_p , 0, sizeof(fh_udp_sw_irq_mask_1_port_p) );

	if(port_type == ECPRISS_PORT_TYPE_FH) {

		ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_P,
				port_index,
				&fh_udp_sw_irq_mask_0_port_p);

		ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_P,
				port_index,
				&fh_udp_sw_irq_mask_1_port_p);

	}

	return;
}

/*
static void ecpriss_qudp_enable_interrupts_v2(uint8_t                 port_index,
		uint32_t                 port_type)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_mask_0_port_p_s_v2 fh_udp_sw_irq_mask_0_port_p;
	ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_mask_1_port_p_s_v2 fh_udp_sw_irq_mask_1_port_p;

	memset(&fh_udp_sw_irq_mask_0_port_p , 0, sizeof(fh_udp_sw_irq_mask_0_port_p) );
	memset(&fh_udp_sw_irq_mask_1_port_p , 0, sizeof(fh_udp_sw_irq_mask_1_port_p) );



	if(port_type == ECPRISS_PORT_TYPE_FH) {

		ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_P_V2,
				port_index,
				&fh_udp_sw_irq_mask_0_port_p);


		ecpriss_qudp_hal_read_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_P_V2,
				port_index,
				&fh_udp_sw_irq_mask_1_port_p);

		fh_udp_sw_irq_mask_0_port_p.egress_mtu_err_packet_link_0 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_fcs_err_packet_link_0 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_pkt_fifo_empty_before_eop_link_0 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_ipv4_cs_error_link_0 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_udp_cs_error_link_0 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_ip_filtered_packet_link_0 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_vlan_filtered_packet_link_0 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_sec_err_packet_link_0 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_ip_len_err_packet_link_0 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_trap_rule_0_link_0 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_trap_rule_1_link_0 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_trap_rule_2_link_0 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_trap_rule_3_link_0 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_last_in_chain_non_local_dst_packet_link_0 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_timestamped_packets_bw_too_high_link_0= 1;

		fh_udp_sw_irq_mask_0_port_p.egress_mtu_err_packet_link_1 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_fcs_err_packet_link_1 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_pkt_fifo_empty_before_eop_link_1 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_ipv4_cs_error_link_1 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_udp_cs_error_link_1 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_ip_filtered_packet_link_1 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_vlan_filtered_packet_link_1 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_sec_err_packet_link_1 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_ip_len_err_packet_link_1 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_trap_rule_0_link_1 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_trap_rule_1_link_1 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_trap_rule_2_link_1 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_trap_rule_3_link_1 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_last_in_chain_non_local_dst_packet_link_1 = 1;
		fh_udp_sw_irq_mask_0_port_p.ingress_timestamped_packets_bw_too_high_link_1= 1;

		fh_udp_sw_irq_mask_1_port_p.egress_mtu_err_packet_link_2 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_fcs_err_packet_link_2 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_pkt_fifo_empty_before_eop_link_2 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_ipv4_cs_error_link_2 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_udp_cs_error_link_2 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_ip_filtered_packet_link_2 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_vlan_filtered_packet_link_2 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_sec_err_packet_link_2 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_ip_len_err_packet_link_2 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_trap_rule_0_link_2 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_trap_rule_1_link_2 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_trap_rule_2_link_2 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_trap_rule_3_link_2 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_last_in_chain_non_local_dst_packet_link_2 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_timestamped_packets_bw_too_high_link_2= 1;

		fh_udp_sw_irq_mask_1_port_p.egress_mtu_err_packet_link_3 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_fcs_err_packet_link_3 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_pkt_fifo_empty_before_eop_link_3 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_ipv4_cs_error_link_3 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_udp_cs_error_link_3 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_ip_filtered_packet_link_3 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_vlan_filtered_packet_link_3 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_sec_err_packet_link_3 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_ip_len_err_packet_link_3 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_trap_rule_0_link_3 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_trap_rule_1_link_3 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_trap_rule_2_link_3 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_trap_rule_3_link_3 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_last_in_chain_non_local_dst_packet_link_3 = 1;
		fh_udp_sw_irq_mask_1_port_p.ingress_timestamped_packets_bw_too_high_link_3= 1;

		ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_P_V2,
				port_index,
				&fh_udp_sw_irq_mask_0_port_p);

		ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_P_V2,
				port_index,
				&fh_udp_sw_irq_mask_1_port_p);

	}

	return;
}
*/

static void ecpriss_qudp_disable_interrupts_v2(uint8_t                 port_index,
		uint32_t                 port_type)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_mask_0_port_p_s_v2 fh_udp_sw_irq_mask_0_port_p;
	ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_mask_1_port_p_s_v2 fh_udp_sw_irq_mask_1_port_p;

	memset(&fh_udp_sw_irq_mask_0_port_p , 0, sizeof(fh_udp_sw_irq_mask_0_port_p) );
	memset(&fh_udp_sw_irq_mask_1_port_p , 0, sizeof(fh_udp_sw_irq_mask_1_port_p) );

	if(port_type == ECPRISS_PORT_TYPE_FH) {

		ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_P_V2,
				port_index,
				&fh_udp_sw_irq_mask_0_port_p);

		ecpriss_qudp_hal_write_reg_n_fields(ECPRISS_QUDP_FH,
				ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_P_V2,
				port_index,
				&fh_udp_sw_irq_mask_1_port_p);

	}

	return;
}

/**
 * ecpri_qudp_set_eth_type()
 *
 *
 * Returns:	0 on success, negative on failure
 */
int ecpriss_qudp_init(struct device *dev)
{
	int ret = 0;
	int port_type = 0;
	int port_idx = 0;

	do
	{

		ecpriss_pdata->qudp_ctx->state = ECPRI_QUDP_DEINIT ;

		/* ecpriss_global_operation_mode_cfg(); */

		ret = ecpriss_qudp_global_hal_reg_init(dev,
				ecpriss_pdata->ecpri_hw_ver);
		if(ret < 0)
		{
			break;
		}

		ret = ecpriss_qudp_fh_hal_reg_init(dev);
		if(ret < 0)
		{
			break;
		}

		ret = ecpriss_qudp_ingress_init_cfg();

		if(ret < 0)
		{
			break;
		}

		ecpriss_qudp_fh_egress_cfg_reset(0);
		ecpriss_qudp_fh_egress_cfg_reset(1);
		ecpriss_qudp_fh_egress_cfg_reset(2);

		for(port_type=0;port_type < ECPRISS_PORT_TYPE_MAX;port_type++)
		{
			for(port_idx=0;port_idx < ECPRISS_PORT_MAX;port_idx++)
			{


				ret = ecpriss_qudp_register_interrupts(port_idx,port_type,dev);
				if(ret < 0)
				{
					break;
				}

				ecpriss_qudp_disable_interrupts(port_idx,port_type);

				/* ret = ecpriss_qudp_enable_stats(port_idx,port_type); */
				if(ret < 0)
				{
					break;
				}
			}
		}


		ecpriss_qudp_configure_mtu();
		ecpriss_pdata->qudp_ctx->state = ECPRI_QUDP_READY ;

	}while (0);
	return ret;
}
int ecpriss_qudp_init_v2(struct device *dev)
{
	int ret = 0;
	int port_type = 0;
	int port_idx = 0;

	do
	{

		ecpriss_pdata_v2->qudp_ctx_v2->state = ECPRI_QUDP_DEINIT ;


		ret = ecpriss_qudp_global_hal_reg_init(dev,
				ecpriss_pdata_v2->ecpri_hw_ver);

		if(ret < 0)
		{
			break;
		}

		ret = ecpriss_qudp_fh_hal_reg_init(dev);
		if(ret < 0)
		{
			break;
		}

		ret = ecpriss_qudp_ingress_init_cfg_v2();

		if(ret < 0)
		{
			break;
		}

		ret = ecpriss_qudp_egress_init_cfg_v2();

		if(ret < 0)
		{
			break;
		}


		ecpriss_qudp_fh_egress_cfg_reset_v2(0);
		ecpriss_qudp_fh_egress_cfg_reset_v2(1);
		ecpriss_qudp_fh_egress_cfg_reset_v2(2);

		for(port_type=0;port_type < ECPRISS_PORT_TYPE_MAX;port_type++)
		{
			for(port_idx=0;port_idx < ECPRISS_PORT_MAX;port_idx++)
			{

				ret = ecpriss_qudp_register_interrupts_v2(port_idx,port_type,dev);
				if(ret < 0)
				{
					break;
				}

				ecpriss_qudp_disable_interrupts_v2(port_idx,port_type);

				/* ret = ecpriss_qudp_enable_stats_v2(port_idx,port_type); */
				if(ret < 0)
				{
					break;
				}
			}
		}

		ecpriss_qudp_configure_mtu_v2();
		ecpriss_qudp_non_ecpri_dma_ring_info();
		ecpriss_filtering_enabled = 1;

		ecpriss_pdata_v2->qudp_ctx_v2->state = ECPRI_QUDP_READY ;

	}while (0);
	return ret;
}
static bool ecpriss_qudp_fh_rx_is_ip_filter_exist_v2(
		ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr0_port_p_entry_n_s_v2 dst_ip0,
		ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr1_port_p_entry_n_s_v2 dst_ip1,
		ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr2_port_p_entry_n_s_v2 dst_ip2,
		ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr3_port_p_entry_n_s_v2 dst_ip3,
		uint8_t *filter_idx,
		uint8_t port_index,
		ecpriss_ip_type ip_type
		)
{
	uint32_t i  =0;
	ecpriss_qudp_ingress_per_port_cfg_s_v2 *qudp_ingress_port =
		&ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].ingress_port_cfg;

	for(i = 0; i< MAX_WHITELIST_ENTRIES; i++){
		if(dst_ip0.value == qudp_ingress_port->ipdst_addr[i][0]){
			if(ip_type == ECPRISS_IPV6_TYPE)
			{
				if(dst_ip1.value == qudp_ingress_port->ipdst_addr[i][1] &&
						dst_ip2.value == qudp_ingress_port->ipdst_addr[i][2] &&
						dst_ip3.value == qudp_ingress_port->ipdst_addr[i][3]){
					*filter_idx = i;
					return true;
				}
			}else{
				*filter_idx = i;
					return true;
			}

		}
	}
	return false;
}
static bool ecpriss_qudp_fh_rx_get_available_ipfilter_idx_v2(
		uint8_t *filter_idx,
		uint8_t port_index,
		ecpriss_ip_type ip_type
		)
{
	uint32_t i  =0;
	ecpriss_qudp_ingress_per_port_cfg_s_v2 *qudp_ingress_port =
		&ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].ingress_port_cfg;

	for(i = 0; i< MAX_WHITELIST_ENTRIES; i++){
		if(0 == qudp_ingress_port->ipdst_addr[i][0]){
			if(ip_type == ECPRISS_IPV6_TYPE)
			{
				if(0 == qudp_ingress_port->ipdst_addr[i][1] &&
						0 == qudp_ingress_port->ipdst_addr[i][2] &&
						0 == qudp_ingress_port->ipdst_addr[i][3]){
					*filter_idx = i;
					return true;
				}
			}else{
				*filter_idx = i;
					return true;
			}

		}
	}
	return false;
}

static bool ecpriss_qudp_fh_rx_is_ip_filter_exist(
		ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr0_port_p_entry_n_s dst_ip0,
		ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr1_port_p_entry_n_s dst_ip1,
		ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr2_port_p_entry_n_s dst_ip2,
		ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr3_port_p_entry_n_s dst_ip3,
		uint8_t *filter_idx,
		uint8_t port_index,
		ecpriss_ip_type ip_type
		)
{
	uint32_t i  =0;
	ecpriss_qudp_ingress_per_port_cfg_s *qudp_ingress_port =
		&ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].ingress_port_cfg;

	for(i = 0; i< MAX_WHITELIST_ENTRIES; i++){
		if(dst_ip0.value == qudp_ingress_port->ipdst_addr[i][0]){
			if(ip_type == ECPRISS_IPV6_TYPE)
			{
				if(dst_ip1.value == qudp_ingress_port->ipdst_addr[i][1] &&
						dst_ip2.value == qudp_ingress_port->ipdst_addr[i][2] &&
						dst_ip3.value == qudp_ingress_port->ipdst_addr[i][3]){
					*filter_idx = i;
					return true;
				}
			}else{
				*filter_idx = i;
					return true;
			}

		}
	}
	return false;
}
static bool ecpriss_qudp_fh_rx_get_available_ipfilter_idx(
		uint8_t *filter_idx,
		uint8_t port_index,
		ecpriss_ip_type ip_type
		)
{
	uint32_t i  =0;
	ecpriss_qudp_ingress_per_port_cfg_s *qudp_ingress_port =
		&ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].ingress_port_cfg;

	for(i = 0; i< MAX_WHITELIST_ENTRIES; i++){
		if(0 == qudp_ingress_port->ipdst_addr[i][0]){
			if(ip_type == ECPRISS_IPV6_TYPE)
			{
				if(0 == qudp_ingress_port->ipdst_addr[i][1] &&
						0 == qudp_ingress_port->ipdst_addr[i][2] &&
						0 == qudp_ingress_port->ipdst_addr[i][3]){
					*filter_idx = i;
					return true;
				}
			}else{
				*filter_idx = i;
					return true;
			}

		}
	}
	return false;
}
static bool ecpriss_qudp_fh_rx_ip_filter_cfg(uint32_t port_index, ecpriss_qudp_rx_cfg_s *rx_cfg)
{

	uint8_t filter_idx = 0;
	uint8_t cfg_action = DE_CONFIGURE;
	ecpriss_qudp_ingress_per_port_cfg_s *qudp_ingress_port =
		&ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].ingress_port_cfg;

	ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr0_port_p_entry_n_s dst_ip0 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr1_port_p_entry_n_s dst_ip1 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr2_port_p_entry_n_s dst_ip2 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr3_port_p_entry_n_s dst_ip3 = {0};

	if(rx_cfg == NULL) {
		return false;
	}

	if(rx_cfg->fltr_en_mask & ECPRISS_QUDP_RX_CFG_FLTR_MASK_IP_DADDR){
		cfg_action = CONFIGURE;
	}
	if(cfg_action == CONFIGURE){
		if(qudp_ingress_port->num_ip_fltr_entries >= MAX_WHITELIST_ENTRIES){
			ECPRILOGERR("Cannot apply new IP filter, Capacity is full\n");
			return false;
		}
	}
	if(cfg_action == DE_CONFIGURE){
		if(qudp_ingress_port->num_ip_fltr_entries <= 0){
			ECPRILOGERR("Cannot Remove IP filter, No filter exist\n");
			return false;
		}
	}
	dst_ip0.value = ((rx_cfg->ip_dst_addr[3]) | (rx_cfg->ip_dst_addr[2] << 8) | (rx_cfg->ip_dst_addr[1] << 16)
			| (rx_cfg->ip_dst_addr[0] << 24));

	if(rx_cfg->ip_type == ECPRISS_IPV6_TYPE)
	{
		dst_ip1.value = ((rx_cfg->ip_dst_addr[7]) | (rx_cfg->ip_dst_addr[6] << 8) | (rx_cfg->ip_dst_addr[5] << 16)
				| (rx_cfg->ip_dst_addr[4] << 24));

		dst_ip2.value = ((rx_cfg->ip_dst_addr[11]) | (rx_cfg->ip_dst_addr[10] << 8) | (rx_cfg->ip_dst_addr[9] << 16)
				| (rx_cfg->ip_dst_addr[8] << 24));

		dst_ip3.value = ((rx_cfg->ip_dst_addr[15]) | (rx_cfg->ip_dst_addr[14] << 8) | (rx_cfg->ip_dst_addr[13] << 16)
				| (rx_cfg->ip_dst_addr[12] << 24));
	}
	if(cfg_action == DE_CONFIGURE){
		if((dst_ip0.value + dst_ip1.value + dst_ip2.value + dst_ip3.value ) == 0){
			ECPRILOGERR("Invalid ip Config \n");
			return false;
		}
	}
	/*
	 * Check if the IP filter already exist
	 */
	if(ecpriss_filtering_enabled){
		if(ecpriss_qudp_fh_rx_is_ip_filter_exist(dst_ip0, dst_ip1 , dst_ip2, dst_ip3, &filter_idx, port_index, rx_cfg->ip_type)){
			ECPRILOGERR("IP Filter exist in database \n");
			if(cfg_action == CONFIGURE){
				ECPRILOGERR("Cannot apply IP filter, Already exist\n");
				return false;
			}
		}else{
			ECPRILOGERR("IP Filter Doesn't exist in database \n");
			if(cfg_action == CONFIGURE){
				if(!ecpriss_qudp_fh_rx_get_available_ipfilter_idx(&filter_idx, port_index, rx_cfg->ip_type)){
					ECPRILOGERR("Ip filter configuration is full, Can not apply new ip filtr config\n");
					return false;
				}

			}else{
				ECPRILOGERR("Cannot remove IP filter, does not exist\n");
				return false;
			}
		}
	}
	/*
	 * if ecpriss_filtering_enabled is set or it is One
	 * remove the matching filter
	 */
	if(ecpriss_filtering_enabled == 1){
		/*
		 * remove filters
		 */
		if(cfg_action == DE_CONFIGURE){
			ECPRILOGERR("forcing IP filter to zero to remove filter \n");
			dst_ip0.value = 0;
			dst_ip1.value = 0;
			dst_ip2.value = 0;
			dst_ip3.value = 0;
			if(qudp_ingress_port->num_ip_fltr_entries)
				qudp_ingress_port->num_ip_fltr_entries--;
		}
	}

	ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
			ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n,
			port_index,
			filter_idx,
			&dst_ip0);

	qudp_ingress_port->ipdst_addr[filter_idx][0] = dst_ip0.value ;


	if(rx_cfg->ip_type == ECPRISS_IPV6_TYPE)
	{

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
				ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n,
				port_index,
				filter_idx,
				&dst_ip1);

		qudp_ingress_port->ipdst_addr[filter_idx][1] = dst_ip1.value ;

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
				ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n,
				port_index,
				filter_idx,
				&dst_ip2);

		qudp_ingress_port->ipdst_addr[filter_idx][2] = dst_ip2.value ;

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
				ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n,
				port_index,
				filter_idx,
				&dst_ip3);

		qudp_ingress_port->ipdst_addr[filter_idx][3] = dst_ip3.value ;

	}

	if(ecpriss_filtering_enabled != 0 && cfg_action == CONFIGURE){
		qudp_ingress_port->num_ip_fltr_entries++;
	}
	ecpriss_qudp_ingress_modify_cfg(port_index,
			ENABLE_FILTER,
			ECPRISS_QUDP_RX_CFG_FLTR_MASK_IP_DADDR,
			filter_idx,
			cfg_action);

	return true;
}

static bool ecpriss_qudp_fh_rx_vlan_filter_cfg(uint32_t port_index, ecpriss_qudp_rx_cfg_s *rx_cfg)
{

	int i = 0;
	uint8_t filter_idx = 0;
	uint8_t cfg_action = DE_CONFIGURE;
	ecpriss_qudp_ingress_per_port_cfg_s *qudp_ingress_port =
		&ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].ingress_port_cfg;

	ecpri_qudp_hwio_def_ecpri_udp_fh_filt_vlan_addr_port_p_entry_n_s vlan_addr_port = {0};

	if(rx_cfg == NULL) {
		return false;
	}
	if(rx_cfg->vlan_addr_port > 0)
	{
		filter_idx = 0;
		cfg_action = DE_CONFIGURE;
		if(rx_cfg->fltr_en_mask & ECPRISS_QUDP_RX_CFG_FLTR_MASK_VLAN){
			cfg_action = CONFIGURE;
		}
		if(cfg_action == CONFIGURE){
			if(qudp_ingress_port->num_vlan_fltr_entries >= MAX_WHITELIST_ENTRIES){
				ECPRILOGERR("Cannot apply new VLAN filter, Capacity is full\n");
				return false;
			}
		}
		if(cfg_action == DE_CONFIGURE){
			if(qudp_ingress_port->num_vlan_fltr_entries <= 0){
				ECPRILOGERR("Cannot remove VLAN filter, No filter exist\n");
				return false;
			}
		}

		/*
		 * Check if the VLAN filter already exist
		 */
		if(ecpriss_filtering_enabled){
			for(i = 0; i< MAX_WHITELIST_ENTRIES; i++){
				if(rx_cfg->vlan_addr_port == qudp_ingress_port->vlan_addr[i]){
					if(cfg_action == CONFIGURE){
						ECPRILOGERR("Cannot apply VLAN filter :%u, Already exist\n",rx_cfg->vlan_addr_port);
						return false;
					}else{
						ECPRILOGERR("Filter exist at index %u\n", i);
						filter_idx = i;
						break;
					}
				}
			}

			if(cfg_action == DE_CONFIGURE){
				if(filter_idx != i){
					ECPRILOGERR("VLAN filter does not exist\n");
					return false;
				}
			}else{
				/*
				 * look for available space in table
				 */
				ECPRILOGERR("Looking for available slot in table\n");
				for(i = 0; i< MAX_WHITELIST_ENTRIES; i++){
					if(0 == qudp_ingress_port->vlan_addr[i]){
						filter_idx = i;
						break;
					}
				}
				if(i != filter_idx){
					ECPRILOGERR("VLAN filter full, can not cfg new filter\n");
					return false;
				}

			}
		}
		/*
		 * remove the last applied filter
		 */
		if(ecpriss_filtering_enabled == 1){
			if(cfg_action == DE_CONFIGURE){
				ECPRILOGERR("forcing vlan id to zero to remove filter \n");
				rx_cfg->vlan_addr_port = 0;
				if(qudp_ingress_port->num_vlan_fltr_entries)
					qudp_ingress_port->num_vlan_fltr_entries--;
			}
		}
		vlan_addr_port.value = rx_cfg->vlan_addr_port;

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
				ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n,
				port_index,
				filter_idx,
				&vlan_addr_port);

		qudp_ingress_port->vlan_addr[filter_idx] = rx_cfg->vlan_addr_port;


		if(ecpriss_filtering_enabled != 0 && cfg_action == CONFIGURE){
			qudp_ingress_port->num_vlan_fltr_entries++;
		}
		ecpriss_qudp_ingress_modify_cfg(port_index,
				ENABLE_FILTER,
				ECPRISS_QUDP_RX_CFG_FLTR_MASK_VLAN,
				filter_idx,
				cfg_action);

	}
	return true;
}
static bool ecpriss_qudp_fh_rx_udp_filter_cfg(uint32_t port_index, ecpriss_qudp_rx_cfg_s *rx_cfg)
{

	int i = 0;
	uint8_t filter_idx = 0;
	uint8_t cfg_action = DE_CONFIGURE;
	ecpriss_qudp_ingress_per_port_cfg_s *qudp_ingress_port =
		&ecpriss_pdata->qudp_ctx->fh_port_cfg[port_index].ingress_port_cfg;

	ecpri_qudp_hwio_def_ecpri_udp_fh_udp_classification_list_port_p_entry_n_s udp_classification_port = {0};

	if(rx_cfg == NULL) {
		return false;
	}
	if(rx_cfg->udp_dst_port > 0)
	{
		if(rx_cfg->fltr_en_mask & ECPRISS_QUDP_RX_CFG_FLTR_MASK_UDP_DPORT){
			cfg_action = CONFIGURE;
		}

		udp_classification_port.value = rx_cfg->udp_dst_port;
		if(cfg_action == CONFIGURE){
			ECPRILOGDBG("configure UDP\n");
		}else{
			ECPRILOGDBG("De configure UDP\n");
		}
		ECPRILOGDBG("udp_classification_port.value = %u\n",udp_classification_port.value);
		ECPRILOGDBG("qudp_ingress_port->num_udp_fltr_entries = %u\n",qudp_ingress_port->num_udp_fltr_entries);

		if(cfg_action == CONFIGURE){
			if(qudp_ingress_port->num_udp_fltr_entries >= MAX_WHITELIST_ENTRIES){
				ECPRILOGERR("Cannot apply new UDP_CLASSIFICATION filter, Capacity is full\n");
				return false;
			}
		}
		if(cfg_action == DE_CONFIGURE){
			if(qudp_ingress_port->num_udp_fltr_entries <= 0){
				ECPRILOGERR("Cannot remove UDP_CLASSIFICATION filter, No filter exist\n");
				return false;
			}
		}

		/*
		 * Check if the UDP_CLASSIFICATION filter already exist
		 */
		for(i = 0; i< MAX_WHITELIST_ENTRIES; i++){
			if(udp_classification_port.value == qudp_ingress_port->udp_port[i]){
				if(cfg_action == CONFIGURE){
					ECPRILOGERR("Cannot apply UDP_CLASSIFICATION filter :%u, Already exist\n",udp_classification_port.value);
					return false;
				}else{
					ECPRILOGERR("Filter exist at index %u\n", i);
					filter_idx = i;
					break;
				}
			}
		}
		if(cfg_action == DE_CONFIGURE){
			if(filter_idx != i){
				ECPRILOGERR("VLAN filter does not exist\n");
				return false;
			}
		}else{
			/*
			 * look for available space in table
			 */
			ECPRILOGERR("Looking for available slots \n");
			for(i = 0; i< MAX_WHITELIST_ENTRIES; i++){
				if(0 == qudp_ingress_port->udp_port[i]){
					filter_idx = i;
					break;
				}
			}
			if(i != filter_idx){
				ECPRILOGERR("UDP filter full, can not cfg new filter\n");
				return false;
			}
		}

		/*
		 * UDP_classification value 0 is to remove last applied filter
		 * UDP_class id '0' can not be used as filter
		 * if filter exist remove the last applied filter
		 */
		if(cfg_action == DE_CONFIGURE){
			udp_classification_port.value = 0;
			rx_cfg->udp_dst_port = 0;
			if(qudp_ingress_port->num_udp_fltr_entries)
				qudp_ingress_port->num_udp_fltr_entries--;
		}

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
				ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n,
				port_index,
				filter_idx,
				&udp_classification_port);

		qudp_ingress_port->udp_port[filter_idx] = udp_classification_port.value;

		if(cfg_action == CONFIGURE){
			qudp_ingress_port->num_udp_fltr_entries++;
		}
		ecpriss_qudp_ingress_modify_cfg(port_index,
				ENABLE_FILTER,
				ECPRISS_QUDP_RX_CFG_FLTR_MASK_UDP_DPORT,
				filter_idx,
				cfg_action);
		ECPRILOGDBG("UDP filter_idx = %u\n", filter_idx);
		ECPRILOGDBG("P_Data qudp_ingress_port->udp_port[filter_idx] = %u\n", qudp_ingress_port->udp_port[filter_idx]);
		ECPRILOGDBG("qudp_ingress_port->num_udp_fltr_entries = %u\n",qudp_ingress_port->num_udp_fltr_entries);

	}
	return true;
}

/**
 *  ecpriss_qudp_fh_rx_filter_cfg()
 *
 *  Port index provided as part of qudp_rx_cfg struct ?
 *  Description
 *
 *  Configure IP destination filter:
 *  FILT_IP_DST_ADDR0_PORT_p_ENTRY_n
 *  FILT_IP_DST_ADDR1_PORT_p_ENTRY_n
 *  FILT_IP_DST_ADDR3_PORT_p_ENTRY_n
 *  FILT_IP_DST_ADDR4_PORT_p_ENTRY_n

 *  Configure VLAN filter
 *  FILT_VLAN_ADDR_PORT_p_ENTRY_n
 *
 *  Configure UDP filter
 *  UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n
 *
 *  Maintain next qudp entry n for port p
 *
 *  Set valid bits
 *
 *  FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS
 *  FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS
 *  UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS
 *
 *
 *  Enable sharing of whitelist (Required ?)
 *
 *	INGRESS_CONFIG_n::ENABLE_SHARED_FILTERING_2_LINKS
 INGRESS_CONFIG_n::ENABLE_SHARED_FILTERING_4_LINKS
 *
 *  Enable filtering
 *
 *  INGRESS_CONFIG_n::ENABLE_IP_DST_FILT
 *  INGRESS_CONFIG_n::ENABLE_UDP_DST_CLASS
 *  INGRESS_CONFIG_n::ENABLE_VLAN_FILT
 * Returns:	0 on success, negative on failure
 */
int ecpriss_qudp_fh_rx_filter_cfg(uint32_t port_index, ecpriss_qudp_rx_cfg_s *rx_cfg)
{
	bool ret = false;
	if(ecpriss_filtering_enabled){
		ret = ecpriss_qudp_fh_rx_ip_filter_cfg(port_index, rx_cfg);
		if(ret == false){
			ECPRILOGERR("IP filter Config validation failed \n");
		}
	}else{
		ECPRILOGERR("Global filter config is disabled, Can't config IP filter \n");
	}
	if(ecpriss_filtering_enabled){
		ret = ecpriss_qudp_fh_rx_vlan_filter_cfg(port_index, rx_cfg);
		if(ret == false){
			ECPRILOGERR("Vlan filter config validation failed \n");
		}
	}else{
		ECPRILOGERR("Global filter config is disabled, Can't config VLAN filter \n");
	}
	ret = ecpriss_qudp_fh_rx_udp_filter_cfg(port_index, rx_cfg);
	if(ret == false){
		ECPRILOGERR("UDP filter config validation failed \n");
	}

	return 0;
}

static bool ecpriss_qudp_fh_rx_ip_filter_cfg_v2(uint32_t port_index, ecpriss_qudp_rx_cfg_s *rx_cfg)
{

	uint8_t filter_idx = 0;
	uint8_t cfg_action = DE_CONFIGURE;
	ecpriss_qudp_ingress_per_port_cfg_s_v2 *qudp_ingress_port =
		&ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].ingress_port_cfg;

	ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr0_port_p_entry_n_s_v2 dst_ip0 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr1_port_p_entry_n_s_v2 dst_ip1 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr2_port_p_entry_n_s_v2 dst_ip2 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr3_port_p_entry_n_s_v2 dst_ip3 = {0};

	if(rx_cfg == NULL) {
		return false;
	}

	if(rx_cfg->fltr_en_mask & ECPRISS_QUDP_RX_CFG_FLTR_MASK_IP_DADDR){
		cfg_action = CONFIGURE;
	}
	if(cfg_action == CONFIGURE){
		if(qudp_ingress_port->num_ip_fltr_entries >= MAX_WHITELIST_ENTRIES){
			ECPRILOGERR("Cannot apply new IP filter, Capacity is full\n");
			return false;
		}
	}
	if(cfg_action == DE_CONFIGURE){
		if(qudp_ingress_port->num_ip_fltr_entries <= 0){
			ECPRILOGINFO("Cannot Remove IP filter, No filter exist\n");
			return false;
		}
	}
	dst_ip0.value = ((rx_cfg->ip_dst_addr[3]) | (rx_cfg->ip_dst_addr[2] << 8) | (rx_cfg->ip_dst_addr[1] << 16)
			| (rx_cfg->ip_dst_addr[0] << 24));

	if(rx_cfg->ip_type == ECPRISS_IPV6_TYPE)
	{
		dst_ip1.value = ((rx_cfg->ip_dst_addr[7]) | (rx_cfg->ip_dst_addr[6] << 8) | (rx_cfg->ip_dst_addr[5] << 16)
				| (rx_cfg->ip_dst_addr[4] << 24));

		dst_ip2.value = ((rx_cfg->ip_dst_addr[11]) | (rx_cfg->ip_dst_addr[10] << 8) | (rx_cfg->ip_dst_addr[9] << 16)
				| (rx_cfg->ip_dst_addr[8] << 24));

		dst_ip3.value = ((rx_cfg->ip_dst_addr[15]) | (rx_cfg->ip_dst_addr[14] << 8) | (rx_cfg->ip_dst_addr[13] << 16)
				| (rx_cfg->ip_dst_addr[12] << 24));
	}
	if(cfg_action == DE_CONFIGURE){
		if((dst_ip0.value + dst_ip1.value + dst_ip2.value + dst_ip3.value ) == 0){
			ECPRILOGERR("Invalid ip Config \n");
			return false;
		}
	}
	/*
	 * Check if the IP filter already exist
	 */
	if(ecpriss_filtering_enabled){
		if(ecpriss_qudp_fh_rx_is_ip_filter_exist_v2(dst_ip0, dst_ip1 , dst_ip2, dst_ip3, &filter_idx, port_index, rx_cfg->ip_type)){
			ECPRILOGINFO("IP Filter exist in database \n");
			if(cfg_action == CONFIGURE){
				ECPRILOGINFO("Cannot apply IP filter, Already exist\n");
				return false;
			}
		}else{
			ECPRILOGINFO("IP Filter Doesn't exist in database \n");
			if(cfg_action == CONFIGURE){
				if(!ecpriss_qudp_fh_rx_get_available_ipfilter_idx_v2(&filter_idx, port_index, rx_cfg->ip_type)){
					ECPRILOGERR("Ip filter configuration is full, Can not apply new ip filtr config\n");
					return false;
				}

			}else{
				ECPRILOGINFO("Cannot remove IP filter, does not exist\n");
				return false;
			}
		}
	}
	/*
	 * if ecpriss_filtering_enabled is set or it is One
	 * remove the matching filter
	 */
	if(ecpriss_filtering_enabled == 1){
		/*
		 * remove filters
		 */
		if(cfg_action == DE_CONFIGURE){
			ECPRILOGINFO("forcing IP filter to zero to remove filter \n");
			dst_ip0.value = 0;
			dst_ip1.value = 0;
			dst_ip2.value = 0;
			dst_ip3.value = 0;
			if(qudp_ingress_port->num_ip_fltr_entries)
				qudp_ingress_port->num_ip_fltr_entries--;
		}
	}

	ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
			ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_V2,
			port_index,
			filter_idx,
			&dst_ip0);

	qudp_ingress_port->ipdst_addr[filter_idx][0] = dst_ip0.value ;


	if(rx_cfg->ip_type == ECPRISS_IPV6_TYPE)
	{

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
				ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_V2,
				port_index,
				filter_idx,
				&dst_ip1);

		qudp_ingress_port->ipdst_addr[filter_idx][1] = dst_ip1.value ;

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
				ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_V2,
				port_index,
				filter_idx,
				&dst_ip2);

		qudp_ingress_port->ipdst_addr[filter_idx][2] = dst_ip2.value ;

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
				ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_V2,
				port_index,
				filter_idx,
				&dst_ip3);

		qudp_ingress_port->ipdst_addr[filter_idx][3] = dst_ip3.value ;

	}

	if(ecpriss_filtering_enabled != 0 && cfg_action == CONFIGURE){
		qudp_ingress_port->num_ip_fltr_entries++;
	}
	ecpriss_qudp_ingress_modify_cfg_v2(port_index,
			ENABLE_FILTER,
			ECPRISS_QUDP_RX_CFG_FLTR_MASK_IP_DADDR,
			filter_idx,
			cfg_action);

	return true;
}
static bool ecpriss_qudp_fh_rx_vlan_filter_cfg_v2(uint32_t port_index, ecpriss_qudp_rx_cfg_s *rx_cfg)
{

	int i = 0;
	uint8_t filter_idx = 0;
	uint8_t cfg_action = DE_CONFIGURE;
	ecpriss_qudp_ingress_per_port_cfg_s_v2 *qudp_ingress_port =
		&ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].ingress_port_cfg;

	ecpri_qudp_hwio_def_ecpri_udp_fh_filt_vlan_addr_port_p_entry_n_s_v2 vlan_addr_port = {0};

	if(rx_cfg == NULL) {
		return false;
	}
	if(rx_cfg->vlan_addr_port > 0)
	{
		filter_idx = 0;
		cfg_action = DE_CONFIGURE;
		if(rx_cfg->fltr_en_mask & ECPRISS_QUDP_RX_CFG_FLTR_MASK_VLAN){
			cfg_action = CONFIGURE;
		}
		if(cfg_action == CONFIGURE){
			if(qudp_ingress_port->num_vlan_fltr_entries >= MAX_WHITELIST_ENTRIES){
				ECPRILOGERR("Cannot apply new VLAN filter, Capacity is full\n");
				return false;
			}
		}
		if(cfg_action == DE_CONFIGURE){
			if(qudp_ingress_port->num_vlan_fltr_entries <= 0){
				ECPRILOGINFO("Cannot remove VLAN filter, No filter exist\n");
				return false;
			}
		}

		/*
		 * Check if the VLAN filter already exist
		 */
		if(ecpriss_filtering_enabled){
			for(i = 0; i< MAX_WHITELIST_ENTRIES; i++){
				if(rx_cfg->vlan_addr_port == qudp_ingress_port->vlan_addr[i]){
					if(cfg_action == CONFIGURE){
						ECPRILOGINFO("Cannot apply VLAN filter :%u, Already exist\n",rx_cfg->vlan_addr_port);
						return false;
					}else{
						ECPRILOGINFO("Filter exist at index %u\n", i);
						filter_idx = i;
						break;
					}
				}
			}

			if(cfg_action == DE_CONFIGURE){
				if(filter_idx != i){
					ECPRILOGINFO("VLAN filter does not exist\n");
					return false;
				}
			}else{
				/*
				 * look for available space in table
				 */
				ECPRILOGINFO("Looking for available slot in table\n");
				for(i = 0; i< MAX_WHITELIST_ENTRIES; i++){
					if(0 == qudp_ingress_port->vlan_addr[i]){
						filter_idx = i;
						break;
					}
				}
				if(i != filter_idx){
					ECPRILOGERR("VLAN filter full, can not cfg new filter\n");
					return false;
				}

			}
		}
		/*
		 * remove the last applied filter
		 */
		if(ecpriss_filtering_enabled == 1){
			if(cfg_action == DE_CONFIGURE){
				ECPRILOGINFO("forcing vlan id to zero to remove filter \n");
				rx_cfg->vlan_addr_port = 0;
				if(qudp_ingress_port->num_vlan_fltr_entries)
					qudp_ingress_port->num_vlan_fltr_entries--;
			}
		}
		vlan_addr_port.value = rx_cfg->vlan_addr_port;

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
				ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n_V2,
				port_index,
				filter_idx,
				&vlan_addr_port);

		qudp_ingress_port->vlan_addr[filter_idx] = rx_cfg->vlan_addr_port;


		if(ecpriss_filtering_enabled != 0 && cfg_action == CONFIGURE){
			qudp_ingress_port->num_vlan_fltr_entries++;
		}
		ecpriss_qudp_ingress_modify_cfg_v2(port_index,
				ENABLE_FILTER,
				ECPRISS_QUDP_RX_CFG_FLTR_MASK_VLAN,
				filter_idx,
				cfg_action);

	}
	return true;
}
static bool ecpriss_qudp_fh_rx_udp_filter_cfg_v2(uint32_t port_index, ecpriss_qudp_rx_cfg_s *rx_cfg)
{

	int i = 0;
	uint8_t filter_idx = 0;
	uint8_t cfg_action = DE_CONFIGURE;
	ecpriss_qudp_ingress_per_port_cfg_s_v2 *qudp_ingress_port =
		&ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].ingress_port_cfg;

	ecpri_qudp_hwio_def_ecpri_udp_fh_udp_classification_list_port_p_entry_n_s_v2 udp_classification_port = {0};

	if(rx_cfg == NULL) {
		return false;
	}
	if(rx_cfg->udp_dst_port > 0)
	{
		if(rx_cfg->fltr_en_mask & ECPRISS_QUDP_RX_CFG_FLTR_MASK_UDP_DPORT){
			cfg_action = CONFIGURE;
		}

		udp_classification_port.value = rx_cfg->udp_dst_port;
		if(cfg_action == CONFIGURE){
			ECPRILOGDBG("configure UDP\n");
		}else{
			ECPRILOGDBG("De configure UDP\n");
		}
		ECPRILOGDBG("udp_classification_port.value = %u\n",udp_classification_port.value);
		ECPRILOGDBG("qudp_ingress_port->num_udp_fltr_entries = %u\n",qudp_ingress_port->num_udp_fltr_entries);

		if(cfg_action == CONFIGURE){
			if(qudp_ingress_port->num_udp_fltr_entries >= MAX_WHITELIST_ENTRIES){
				ECPRILOGERR("Cannot apply new UDP_CLASSIFICATION filter, Capacity is full\n");
				return false;
			}
		}
		if(cfg_action == DE_CONFIGURE){
			if(qudp_ingress_port->num_udp_fltr_entries <= 0){
				ECPRILOGINFO("Cannot remove UDP_CLASSIFICATION filter, No filter exist\n");
				return false;
			}
		}

		/*
		 * Check if the UDP_CLASSIFICATION filter already exist
		 */
		for(i = 0; i< MAX_WHITELIST_ENTRIES; i++){
			if(udp_classification_port.value == qudp_ingress_port->udp_port[i]){
				if(cfg_action == CONFIGURE){
					ECPRILOGINFO("Cannot apply UDP_CLASSIFICATION filter :%u, Already exist\n",udp_classification_port.value);
					return false;
				}else{
					ECPRILOGINFO("Filter exist at index %u\n", i);
					filter_idx = i;
					break;
				}
			}
		}
		if(cfg_action == DE_CONFIGURE){
			if(filter_idx != i){
				ECPRILOGINFO("UDP filter does not exist\n");
				return false;
			}
		}else{
			/*
			 * look for available space in table
			 */
			ECPRILOGINFO("Looking for available slots \n");
			for(i = 0; i< MAX_WHITELIST_ENTRIES; i++){
				if(0 == qudp_ingress_port->udp_port[i]){
					filter_idx = i;
					break;
				}
			}
			if(i != filter_idx){
				ECPRILOGERR("UDP filter full, can not cfg new filter\n");
				return false;
			}
		}

		/*
		 * UDP_classification value 0 is to remove last applied filter
		 * UDP_class id '0' can not be used as filter
		 * if filter exist remove the last applied filter
		 */
		if(cfg_action == DE_CONFIGURE){
			udp_classification_port.value = 0;
			rx_cfg->udp_dst_port = 0;
			if(qudp_ingress_port->num_udp_fltr_entries)
				qudp_ingress_port->num_udp_fltr_entries--;
		}

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_FILTER,
				ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_V2,
				port_index,
				filter_idx,
				&udp_classification_port);

		qudp_ingress_port->udp_port[filter_idx] = udp_classification_port.value;

		if(cfg_action == CONFIGURE){
			qudp_ingress_port->num_udp_fltr_entries++;
		}
		ecpriss_qudp_ingress_modify_cfg_v2(port_index,
				ENABLE_FILTER,
				ECPRISS_QUDP_RX_CFG_FLTR_MASK_UDP_DPORT,
				filter_idx,
				cfg_action);
		ECPRILOGDBG("UDP filter_idx = %u\n", filter_idx);
		ECPRILOGDBG("P_Data qudp_ingress_port->udp_port[filter_idx] = %u\n", qudp_ingress_port->udp_port[filter_idx]);
		ECPRILOGDBG("qudp_ingress_port->num_udp_fltr_entries = %u\n",qudp_ingress_port->num_udp_fltr_entries);

	}
	return true;
}

int ecpriss_qudp_fh_rx_filter_cfg_v2(uint32_t port_index, ecpriss_qudp_rx_cfg_s *rx_cfg)
{
	bool ret = false;
	if(ecpriss_filtering_enabled){
		ret = ecpriss_qudp_fh_rx_ip_filter_cfg_v2(port_index, rx_cfg);
		if(ret == false){
			ECPRILOGERR("IP filter Config validation failed \n");
		}
	}else{
		ECPRILOGERR("Global filter config is disabled, Can't config IP filter \n");
	}
	if(ecpriss_filtering_enabled){
		ret = ecpriss_qudp_fh_rx_vlan_filter_cfg_v2(port_index, rx_cfg);
		if(ret == false){
			ECPRILOGERR("Vlan filter config validation failed \n");
		}
	}else{
		ECPRILOGERR("Global filter config is disabled, Can't config VLAN filter \n");
	}
	ret = ecpriss_qudp_fh_rx_udp_filter_cfg_v2(port_index, rx_cfg);
	if(ret == false){
		ECPRILOGERR("UDP filter config validation failed \n");
	}

	return 0;
}



/**
 *  ecpriss_qudp_fh_tx_hdr_ins_cfg
 *
 *	Requirements - port index and maintain a table of entries
 *
 *	Description -
 *
 *
 *
 * Returns:	0 on success, negative on failure
 */
int ecpriss_qudp_fh_tx_hdr_ins_cfg(uint32_t               port_index,
		ecpriss_qudp_tx_cfg_s *tx_cfg)
{
	int ret = 0;

	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_dst0_port_p_entry_n_s       eth_dst0_port = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_src1_dst1_port_p_entry_n_s  eth_src1_dst1_port = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_src0_port_p_entry_n_s       eth_src0_port = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_vlan_ethertype_port_p_entry_n_s vlan_ethertype_port = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_vport_misc_port_p_entry_n_s     vport_misc_port = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr0_port_p_entry_n_s   ip_src0 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr1_port_p_entry_n_s   ip_src1 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr2_port_p_entry_n_s   ip_src2 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr3_port_p_entry_n_s   ip_src3 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr0_port_p_entry_n_s   ip_dst0 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr1_port_p_entry_n_s   ip_dst1 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr2_port_p_entry_n_s   ip_dst2 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr3_port_p_entry_n_s   ip_dst3 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_udp_ports_port_p_entry_n_s      udp_port = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_sa_tag_ip_tos_misc_port_p_entry_n_s  ip_opts = {0};


	do
	{
		if(tx_cfg == NULL) {
			ret = -ENOMEM;
			break;
		}

		/* 4 LSB goes to this eth_dst0_port */

		eth_dst0_port.value = ((tx_cfg->eth_hdr.dst_mac_addr[5]) | (tx_cfg->eth_hdr.dst_mac_addr[4] << 8)
				| (tx_cfg->eth_hdr.dst_mac_addr[3] << 16) | (tx_cfg->eth_hdr.dst_mac_addr[2] << 24));



		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n,
				port_index,
				tx_cfg->l2_hdr_tbl_idx,
				&eth_dst0_port);

		eth_src1_dst1_port.dst_msb = ((tx_cfg->eth_hdr.dst_mac_addr[1]) | (tx_cfg->eth_hdr.dst_mac_addr[0] << 8));
		eth_src1_dst1_port.src_msb = ((tx_cfg->eth_hdr.src_mac_addr[1]) | (tx_cfg->eth_hdr.src_mac_addr[0] << 8));


		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n,
				port_index,
				tx_cfg->l2_hdr_tbl_idx,
				&eth_src1_dst1_port);



		eth_src0_port.value = ((tx_cfg->eth_hdr.src_mac_addr[5]) | (tx_cfg->eth_hdr.src_mac_addr[4] << 8)
				| (tx_cfg->eth_hdr.src_mac_addr[3] << 16) | (tx_cfg->eth_hdr.src_mac_addr[2]) << 24);



		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n,
				port_index,
				tx_cfg->l2_hdr_tbl_idx,
				&eth_src0_port);

		vlan_ethertype_port.ethertype = tx_cfg->eth_hdr.orig_ethertype;

		vlan_ethertype_port.vlan_data = tx_cfg->eth_hdr.vlan_data;

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n,
				port_index,
				tx_cfg->l2_hdr_tbl_idx,
				&vlan_ethertype_port);

		vport_misc_port.vport = tx_cfg->eth_hdr.vport;

		vport_misc_port.has_vlan = tx_cfg->eth_hdr.is_vlan;

		vport_misc_port.vport_action = tx_cfg->eth_hdr.vport_action;

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n,
				port_index,
				tx_cfg->l2_hdr_tbl_idx,
				&vport_misc_port);

		if(tx_cfg->eth_hdr.orig_ethertype != ECPRISS_ETHERTYPE_ECPRI){

			ip_src0.value |= ((tx_cfg->ip_hdr.src_ip_addr[3]) | (tx_cfg->ip_hdr.src_ip_addr[2] << 8) | (tx_cfg->ip_hdr.src_ip_addr[1] << 16)
					| (tx_cfg->ip_hdr.src_ip_addr[0] << 24));

			ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
					ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n,
					port_index,
					tx_cfg->l3_hdr_tbl_idx,
					&ip_src0);

			ip_dst0.value |= ((tx_cfg->ip_hdr.dst_ip_addr[3]) | (tx_cfg->ip_hdr.dst_ip_addr[2] << 8) | (tx_cfg->ip_hdr.dst_ip_addr[1] << 16)
					| (tx_cfg->ip_hdr.dst_ip_addr[0] << 24));

			ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
					ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n,
					port_index,
					tx_cfg->l3_hdr_tbl_idx,
					&ip_dst0);

			if(tx_cfg->ip_hdr.ip_type == ECPRISS_IPV6_TYPE)
			{

				ip_src1.value |= ((tx_cfg->ip_hdr.src_ip_addr[7]) | (tx_cfg->ip_hdr.src_ip_addr[6] << 8) | (tx_cfg->ip_hdr.src_ip_addr[5] << 16)
						| (tx_cfg->ip_hdr.src_ip_addr[4] << 24));

				ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
						ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n,
						port_index,
						tx_cfg->l3_hdr_tbl_idx,
						&ip_src1);

				ip_src2.value |= ((tx_cfg->ip_hdr.src_ip_addr[11]) | (tx_cfg->ip_hdr.src_ip_addr[10] << 8) | (tx_cfg->ip_hdr.src_ip_addr[9] << 16)
						| (tx_cfg->ip_hdr.src_ip_addr[8] << 24));

				ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
						ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n,
						port_index,
						tx_cfg->l3_hdr_tbl_idx,
						&ip_src2);

				ip_src3.value |= ((tx_cfg->ip_hdr.src_ip_addr[15]) | (tx_cfg->ip_hdr.src_ip_addr[14] << 8) | (tx_cfg->ip_hdr.src_ip_addr[13] << 16)
						| (tx_cfg->ip_hdr.src_ip_addr[12] << 24));

				ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
						ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n,
						port_index,
						tx_cfg->l3_hdr_tbl_idx,
						&ip_src3);

				ip_dst1.value |= ((tx_cfg->ip_hdr.dst_ip_addr[7]) | (tx_cfg->ip_hdr.dst_ip_addr[6] << 8) | (tx_cfg->ip_hdr.dst_ip_addr[5] << 16)
						| (tx_cfg->ip_hdr.dst_ip_addr[4] << 24));

				ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
						ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n,
						port_index,
						tx_cfg->l3_hdr_tbl_idx,
						&ip_dst1);

				ip_dst2.value |= ((tx_cfg->ip_hdr.dst_ip_addr[11]) | (tx_cfg->ip_hdr.dst_ip_addr[10] << 8) | (tx_cfg->ip_hdr.dst_ip_addr[9] << 16)
						| (tx_cfg->ip_hdr.dst_ip_addr[8] << 24));

				ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
						ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n,
						port_index,
						tx_cfg->l3_hdr_tbl_idx,
						&ip_dst2);

				ip_dst3.value |= ((tx_cfg->ip_hdr.dst_ip_addr[15]) | (tx_cfg->ip_hdr.dst_ip_addr[14] << 8) | (tx_cfg->ip_hdr.dst_ip_addr[13] << 16)
						| (tx_cfg->ip_hdr.dst_ip_addr[12] << 24));

				ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
						ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n,
						port_index,
						tx_cfg->l3_hdr_tbl_idx,
						&ip_dst3);

			}

			udp_port.src = tx_cfg->ip_hdr.src_udp_port;
			udp_port.dst = tx_cfg->ip_hdr.dst_udp_port;

			ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
					ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n,
					port_index,
					tx_cfg->l3_hdr_tbl_idx,
					&udp_port);


			ip_opts.sa_tag_data = tx_cfg->ip_hdr.sa_tag_data ;
			ip_opts.tos = tx_cfg->ip_hdr.tos;
			ip_opts.df_bit = tx_cfg->ip_hdr.df_en;
			ip_opts.calc_udp_cs = tx_cfg->ip_hdr.udp_chksum_en;
			ip_opts.is_ipsec = tx_cfg->ip_hdr.ipsec_en;
			ip_opts.rsvd = tx_cfg->ip_hdr.rsvd;
			ip_opts.ip_type = tx_cfg->ip_hdr.ip_type;

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n,
				port_index,
				tx_cfg->l3_hdr_tbl_idx,
				&ip_opts);
		}

	}while(0);
	return 0;
}

int ecpriss_qudp_fh_egress_cfg_reset(int32_t port_index)
{
	int32_t egress_table_index = 0;

	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_dst0_port_p_entry_n_s       eth_dst0_port = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_src1_dst1_port_p_entry_n_s  eth_src1_dst1_port = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_src0_port_p_entry_n_s       eth_src0_port = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_vlan_ethertype_port_p_entry_n_s vlan_ethertype_port = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_vport_misc_port_p_entry_n_s     vport_misc_port = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr0_port_p_entry_n_s   ip_src0 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr1_port_p_entry_n_s   ip_src1 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr2_port_p_entry_n_s   ip_src2 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr3_port_p_entry_n_s   ip_src3 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr0_port_p_entry_n_s   ip_dst0 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr1_port_p_entry_n_s   ip_dst1 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr2_port_p_entry_n_s   ip_dst2 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr3_port_p_entry_n_s   ip_dst3 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_udp_ports_port_p_entry_n_s      udp_port = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_sa_tag_ip_tos_misc_port_p_entry_n_s  ip_opts = {0};

	if(port_index > 3)
		return 0;

	for(egress_table_index = 0; egress_table_index < NUM_EGRESS_ENTRY ; egress_table_index++)
	{

		/* 4 LSB goes to this eth_dst0_port */

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n,
				port_index,
				egress_table_index,
				&eth_dst0_port);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n,
				port_index,
				egress_table_index,
				&eth_src1_dst1_port);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n,
				port_index,
				egress_table_index,
				&eth_src0_port);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n,
				port_index,
				egress_table_index,
				&vlan_ethertype_port);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n,
				port_index,
				egress_table_index,
				&vport_misc_port);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n,
				port_index,
				egress_table_index,
				&ip_src0);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n,
				port_index,
				egress_table_index,
				&ip_dst0);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n,
				port_index,
				egress_table_index,
				&ip_src1);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n,
				port_index,
				egress_table_index,
				&ip_src2);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n,
				port_index,
				egress_table_index,
				&ip_src3);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n,
				port_index,
				egress_table_index,
				&ip_dst1);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n,
				port_index,
				egress_table_index,
				&ip_dst2);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n,
				port_index,
				egress_table_index,
				&ip_dst3);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n,
				port_index,
				egress_table_index,
				&udp_port);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n,
				port_index,
				egress_table_index,
				&ip_opts);

	}
	return 0;
}
int ecpriss_qudp_fh_egress_cfg_reset_v2(int32_t port_index)
{
	int32_t egress_table_index = 0;

	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_dst0_port_p_entry_n_s_v2       eth_dst0_port = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_src1_dst1_port_p_entry_n_s_v2  eth_src1_dst1_port = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_src0_port_p_entry_n_s_v2       eth_src0_port = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_vlan_ethertype_port_p_entry_n_s_v2 vlan_ethertype_port = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_vport_misc_port_p_entry_n_s_v2     vport_misc_port = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr0_port_p_entry_n_s_v2   ip_src0 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr1_port_p_entry_n_s_v2   ip_src1 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr2_port_p_entry_n_s_v2   ip_src2 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr3_port_p_entry_n_s_v2   ip_src3 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr0_port_p_entry_n_s_v2   ip_dst0 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr1_port_p_entry_n_s_v2   ip_dst1 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr2_port_p_entry_n_s_v2   ip_dst2 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr3_port_p_entry_n_s_v2   ip_dst3 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_udp_ports_port_p_entry_n_s_v2      udp_port = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_sa_tag_ip_tos_misc_port_p_entry_n_s_v2  ip_opts = {0};

	if(port_index > 3)
		return 0;

	for(egress_table_index = 0; egress_table_index < NUM_EGRESS_ENTRY ; egress_table_index++)
	{

		/* 4 LSB goes to this eth_dst0_port */

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n_V2,
				port_index,
				egress_table_index,
				&eth_dst0_port);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_V2,
				port_index,
				egress_table_index,
				&eth_src1_dst1_port);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_V2,
				port_index,
				egress_table_index,
				&eth_src0_port);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_V2,
				port_index,
				egress_table_index,
				&vlan_ethertype_port);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_V2,
				port_index,
				egress_table_index,
				&vport_misc_port);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_V2,
				port_index,
				egress_table_index,
				&ip_src0);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_V2,
				port_index,
				egress_table_index,
				&ip_dst0);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_V2,
				port_index,
				egress_table_index,
				&ip_src1);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_V2,
				port_index,
				egress_table_index,
				&ip_src2);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_V2,
				port_index,
				egress_table_index,
				&ip_src3);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_V2,
				port_index,
				egress_table_index,
				&ip_dst1);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_V2,
				port_index,
				egress_table_index,
				&ip_dst2);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_V2,
				port_index,
				egress_table_index,
				&ip_dst3);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_V2,
				port_index,
				egress_table_index,
				&udp_port);

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_V2,
				port_index,
				egress_table_index,
				&ip_opts);

	}
	return 0;
}
int ecpriss_qudp_get_ecpriss_filt_enable_info(void)
{
	return ecpriss_filtering_enabled;
}

void ecpriss_qudp_set_ecpriss_filt_enable_info(int val)
{
	ecpriss_filtering_enabled = val;
}
void ecpriss_qudp_non_ecpri_dma_ring_info(void)
{
	int32_t fh_index = 0;
	int j =0;

	ecpri_qudp_hwio_def_ecpri_udp_fh_non_ecpri_dma_ring_info_port_p_link_n_s_v2 non_ecpri_dma_ring_info;

	for(fh_index = 0; fh_index < NUM_OF_FHP; fh_index++){

		struct ecpri_dma_port_params *dma_port_cfg= &ecpriss_pdata_v2->xbar_ctx_v2->fh_port_cfg.dma_port_cfg[fh_index];

		for(j=0;j<dma_port_cfg->num_of_rings;j++)
		{
			memset(&non_ecpri_dma_ring_info , 0, sizeof(non_ecpri_dma_ring_info));

			if(dma_port_cfg->dma_rings_param[j].dma_ring_type == ECPRI_DMA_RING_TYPE_FH_DEFAULT)
			{
				switch(j)
				{
					case 0:
						non_ecpri_dma_ring_info.ring_id = dma_port_cfg->dma_rings_param[0].dest_dma_ring_id;
						non_ecpri_dma_ring_info.gsi_id= dma_port_cfg->dma_rings_param[0].dest_dma_ring_gsi_id;
							break;
					case 1:
						non_ecpri_dma_ring_info.ring_id = dma_port_cfg->dma_rings_param[1].dest_dma_ring_id;
						non_ecpri_dma_ring_info.gsi_id = dma_port_cfg->dma_rings_param[1].dest_dma_ring_gsi_id;
							break;
					case 2:
						non_ecpri_dma_ring_info.ring_id = dma_port_cfg->dma_rings_param[2].dest_dma_ring_id;
						non_ecpri_dma_ring_info.gsi_id = dma_port_cfg->dma_rings_param[2].dest_dma_ring_gsi_id;
							break;
					case 3:
						non_ecpri_dma_ring_info.ring_id = dma_port_cfg->dma_rings_param[3].dest_dma_ring_id;
						non_ecpri_dma_ring_info.gsi_id = dma_port_cfg->dma_rings_param[3].dest_dma_ring_gsi_id;
							break;
					default:
						ECPRILOGERR("Wrong default value %d\n",j);
						break;
				}
				ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH,
						ECPRI_UDP_FH_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n_V2,
						fh_index,j,
						&non_ecpri_dma_ring_info);


			}
		}

	}
}
int ecpriss_qudp_fh_tx_hdr_ins_cfg_v2(uint32_t               port_index,
		ecpriss_qudp_tx_cfg_s *tx_cfg)
{
	int ret = 0;

	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_dst0_port_p_entry_n_s_v2       eth_dst0_port = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_src1_dst1_port_p_entry_n_s_v2   eth_src1_dst1_port = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_src0_port_p_entry_n_s_v2        eth_src0_port = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_vlan_ethertype_port_p_entry_n_s_v2  vlan_ethertype_port = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_vport_misc_port_p_entry_n_s_v2      vport_misc_port = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr0_port_p_entry_n_s_v2    ip_src0 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr1_port_p_entry_n_s_v2    ip_src1 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr2_port_p_entry_n_s_v2    ip_src2 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr3_port_p_entry_n_s_v2    ip_src3 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr0_port_p_entry_n_s_v2    ip_dst0 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr1_port_p_entry_n_s_v2    ip_dst1 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr2_port_p_entry_n_s_v2    ip_dst2 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr3_port_p_entry_n_s_v2    ip_dst3 = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_udp_ports_port_p_entry_n_s_v2       udp_port = {0};
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_sa_tag_ip_tos_misc_port_p_entry_n_s_v2   ip_opts = {0};


	ecpriss_qudp_egress_per_port_cfg_s_v2 *qudp_egress_port =
		&ecpriss_pdata_v2->qudp_ctx_v2->fh_port_cfg_v2[port_index].egress_cfg;
	do
	{
		if(tx_cfg == NULL) {
			ret = -ENOMEM;
			break;
		}

		/* 4 LSB goes to this eth_dst0_port */

		eth_dst0_port.value = ((tx_cfg->eth_hdr.dst_mac_addr[5]) | (tx_cfg->eth_hdr.dst_mac_addr[4] << 8)
				| (tx_cfg->eth_hdr.dst_mac_addr[3] << 16) | (tx_cfg->eth_hdr.dst_mac_addr[2] << 24));



		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n_V2,
				port_index,
				tx_cfg->l2_hdr_tbl_idx,
				&eth_dst0_port);

		memcpy(&qudp_egress_port->eth_dst0_port[tx_cfg->l2_hdr_tbl_idx],&eth_dst0_port,sizeof(eth_dst0_port));

		eth_src1_dst1_port.dst_msb = ((tx_cfg->eth_hdr.dst_mac_addr[1]) | (tx_cfg->eth_hdr.dst_mac_addr[0] << 8));
		eth_src1_dst1_port.src_msb = ((tx_cfg->eth_hdr.src_mac_addr[1]) | (tx_cfg->eth_hdr.src_mac_addr[0] << 8));


		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_V2,
				port_index,
				tx_cfg->l2_hdr_tbl_idx,
				&eth_src1_dst1_port);


		memcpy(&qudp_egress_port->eth_src1_dst1_port[tx_cfg->l2_hdr_tbl_idx],&eth_src1_dst1_port,sizeof(eth_src1_dst1_port));

		eth_src0_port.value = ((tx_cfg->eth_hdr.src_mac_addr[5]) | (tx_cfg->eth_hdr.src_mac_addr[4] << 8)
				| (tx_cfg->eth_hdr.src_mac_addr[3] << 16) | (tx_cfg->eth_hdr.src_mac_addr[2]) << 24);



		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_V2,
				port_index,
				tx_cfg->l2_hdr_tbl_idx,
				&eth_src0_port);
		memcpy(&qudp_egress_port->eth_src0_port[tx_cfg->l2_hdr_tbl_idx],&eth_src0_port,sizeof(eth_src0_port));

		vlan_ethertype_port.ethertype = tx_cfg->eth_hdr.orig_ethertype;

		vlan_ethertype_port.vlan_data = tx_cfg->eth_hdr.vlan_data;

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_V2,
				port_index,
				tx_cfg->l2_hdr_tbl_idx,
				&vlan_ethertype_port);

		memcpy(&qudp_egress_port->vlan_ethertype[tx_cfg->l2_hdr_tbl_idx],&vlan_ethertype_port,sizeof(vlan_ethertype_port));
		vport_misc_port.vport = tx_cfg->eth_hdr.vport;

		vport_misc_port.has_vlan = tx_cfg->eth_hdr.is_vlan;

		vport_misc_port.vport_action = tx_cfg->eth_hdr.vport_action;

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_V2,
				port_index,
				tx_cfg->l2_hdr_tbl_idx,
				&vport_misc_port);

		if(tx_cfg->eth_hdr.orig_ethertype != ECPRISS_ETHERTYPE_ECPRI){

			ip_src0.value |= ((tx_cfg->ip_hdr.src_ip_addr[3]) | (tx_cfg->ip_hdr.src_ip_addr[2] << 8) | (tx_cfg->ip_hdr.src_ip_addr[1] << 16)
					| (tx_cfg->ip_hdr.src_ip_addr[0] << 24));

			ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
					ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_V2,
					port_index,
					tx_cfg->l3_hdr_tbl_idx,
					&ip_src0);


			memcpy(&qudp_egress_port->src_ip_addr[tx_cfg->l3_hdr_tbl_idx].ip_src0,&ip_src0,sizeof(ip_src0));

			ip_dst0.value |= ((tx_cfg->ip_hdr.dst_ip_addr[3]) | (tx_cfg->ip_hdr.dst_ip_addr[2] << 8) | (tx_cfg->ip_hdr.dst_ip_addr[1] << 16)
					| (tx_cfg->ip_hdr.dst_ip_addr[0] << 24));

			ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
					ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_V2,
					port_index,
					tx_cfg->l3_hdr_tbl_idx,
					&ip_dst0);
			memcpy(&qudp_egress_port->dst_ip_addr[tx_cfg->l3_hdr_tbl_idx].ip_dst0,&ip_dst0,sizeof(ip_dst0));

			if(tx_cfg->ip_hdr.ip_type == ECPRISS_IPV6_TYPE)
			{

				ip_src1.value |= ((tx_cfg->ip_hdr.src_ip_addr[7]) | (tx_cfg->ip_hdr.src_ip_addr[6] << 8) | (tx_cfg->ip_hdr.src_ip_addr[5] << 16)
						| (tx_cfg->ip_hdr.src_ip_addr[4] << 24));

				ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
						ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_V2,
						port_index,
						tx_cfg->l3_hdr_tbl_idx,
						&ip_src1);
			memcpy(&qudp_egress_port->src_ip_addr[tx_cfg->l3_hdr_tbl_idx].ip_src1,&ip_src1,sizeof(ip_src0));

				ip_src2.value |= ((tx_cfg->ip_hdr.src_ip_addr[11]) | (tx_cfg->ip_hdr.src_ip_addr[10] << 8) | (tx_cfg->ip_hdr.src_ip_addr[9] << 16)
						| (tx_cfg->ip_hdr.src_ip_addr[8] << 24));

				ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
						ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_V2,
						port_index,
						tx_cfg->l3_hdr_tbl_idx,
						&ip_src2);

			memcpy(&qudp_egress_port->src_ip_addr[tx_cfg->l3_hdr_tbl_idx].ip_src2,&ip_src0,sizeof(ip_src2));
				ip_src3.value |= ((tx_cfg->ip_hdr.src_ip_addr[15]) | (tx_cfg->ip_hdr.src_ip_addr[14] << 8) | (tx_cfg->ip_hdr.src_ip_addr[13] << 16)
						| (tx_cfg->ip_hdr.src_ip_addr[12] << 24));

				ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
						ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_V2,
						port_index,
						tx_cfg->l3_hdr_tbl_idx,
						&ip_src3);

			memcpy(&qudp_egress_port->src_ip_addr[tx_cfg->l3_hdr_tbl_idx].ip_src3,&ip_src0,sizeof(ip_src3));
				ip_dst1.value |= ((tx_cfg->ip_hdr.dst_ip_addr[7]) | (tx_cfg->ip_hdr.dst_ip_addr[6] << 8) | (tx_cfg->ip_hdr.dst_ip_addr[5] << 16)
						| (tx_cfg->ip_hdr.dst_ip_addr[4] << 24));

				ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
						ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_V2,
						port_index,
						tx_cfg->l3_hdr_tbl_idx,
						&ip_dst1);
			memcpy(&qudp_egress_port->dst_ip_addr[tx_cfg->l3_hdr_tbl_idx].ip_dst1,&ip_dst1,sizeof(ip_dst1));

				ip_dst2.value |= ((tx_cfg->ip_hdr.dst_ip_addr[11]) | (tx_cfg->ip_hdr.dst_ip_addr[10] << 8) | (tx_cfg->ip_hdr.dst_ip_addr[9] << 16)
						| (tx_cfg->ip_hdr.dst_ip_addr[8] << 24));

				ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
						ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_V2,
						port_index,
						tx_cfg->l3_hdr_tbl_idx,
						&ip_dst2);

			memcpy(&qudp_egress_port->dst_ip_addr[tx_cfg->l3_hdr_tbl_idx].ip_dst2,&ip_dst2,sizeof(ip_dst2));
				ip_dst3.value |= ((tx_cfg->ip_hdr.dst_ip_addr[15]) | (tx_cfg->ip_hdr.dst_ip_addr[14] << 8) | (tx_cfg->ip_hdr.dst_ip_addr[13] << 16)
						| (tx_cfg->ip_hdr.dst_ip_addr[12] << 24));

				ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
						ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_V2,
						port_index,
						tx_cfg->l3_hdr_tbl_idx,
						&ip_dst3);

			memcpy(&qudp_egress_port->dst_ip_addr[tx_cfg->l3_hdr_tbl_idx].ip_dst3,&ip_dst3,sizeof(ip_dst3));

			}

			udp_port.src = tx_cfg->ip_hdr.src_udp_port;
			udp_port.dst = tx_cfg->ip_hdr.dst_udp_port;

			ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
					ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_V2,
					port_index,
					tx_cfg->l3_hdr_tbl_idx,
					&udp_port);

		memcpy(&qudp_egress_port->udp_ports[tx_cfg->l3_hdr_tbl_idx],&udp_port,sizeof(udp_port));

			ip_opts.sa_tag_data = tx_cfg->ip_hdr.sa_tag_data ;
			ip_opts.tos = tx_cfg->ip_hdr.tos;
			ip_opts.df_bit = tx_cfg->ip_hdr.df_en;
			ip_opts.calc_udp_cs = tx_cfg->ip_hdr.udp_chksum_en;
			ip_opts.is_ipsec = tx_cfg->ip_hdr.ipsec_en;
			ip_opts.rsvd = tx_cfg->ip_hdr.rsvd;
			ip_opts.ip_type = tx_cfg->ip_hdr.ip_type;

		ecpriss_qudp_hal_write_reg_mn_fields(ECPRISS_QUDP_FH_RAMS,
				ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_V2,
				port_index,
				tx_cfg->l3_hdr_tbl_idx,
				&ip_opts);

		if(!qudp_egress_port->l3_tbl_valid_entry[tx_cfg->l3_hdr_tbl_idx]){
			qudp_egress_port->l3_tbl_valid_entry[tx_cfg->l3_hdr_tbl_idx] = true;
			qudp_egress_port->num_l3_tbl_entries++;
		}
		}
		if(!qudp_egress_port->l2_tbl_valid_entry[tx_cfg->l2_hdr_tbl_idx]){
			qudp_egress_port->l2_tbl_valid_entry[tx_cfg->l2_hdr_tbl_idx] = true;
			qudp_egress_port->num_l2_tbl_entries++;
		}
	}while(0);
	return 0;
}


int ecpriss_qudp_get_ingress_action(void)
{
	return ecpriss_qudp_ingress_action;
}
void ecpriss_qudp_set_ingress_action(int val)
{
	int ret = 0;
	ecpriss_qudp_ingress_action = val;

	ret = ecpriss_qudp_ingress_init_cfg_modify_v2(ecpriss_qudp_ingress_action);

	if(ret != 0)
		ECPRILOGINFO("ecpriss_qudp_ingress_init_action modify failed\n");

	return;
}


#ifdef UNUSED

/**
 * ecpri_qudp_set_eth_type()
 *
 *
 * Returns:	0 on success, negative on failure
 */
static int ecpriss_qudp_set_eth_type(void)
{
	return 0;
}



/**
 * ecpri_qudp_egress_modify_cfg()
 *
 *
 * Returns:	0 on success, negative on failure
 */
static int ecpriss_qudp_egress_modify_cfg(uint32_t value,
		uint32_t field)
{
	return 0;
}


/**
 *  ecpriss_qudp_fh_tx_hdr_ins_cfg
 *
 *	Requirements - port index and maintain a table of entries
 *
 *	Description -
 *
 *
 *
 * Returns:	0 on success, negative on failure
 */
static int ecpriss_qudp_validate_rx_idx_cfg(uint32_t               port_index,
		ecpriss_qudp_tx_cfg_s *tx_qudp_cfg,
		ecpriss_xbar_tx_cfg_s *tx_xbar_cfg)
{
	return 0;
}

/**
 *  ecpriss_qudp_fh_tx_hdr_ins_cfg
 *
 *	Requirements - port index and maintain a table of entries
 *
 *	Description -
 *
 *
 *
 * Returns:	0 on success, negative on failure
 */
static int ecpriss_qudp_validate_tx_idx_cfg(uint32_t  port_index,
		ecpriss_qudp_tx_cfg_s *tx_qudp_cfg,
		ecpriss_xbar_tx_cfg_s *tx_xbar_cfg)
{
	return 0;
}



/**
 * ecpri_qudp_fh_enable_stats()
 *
 *
 * Returns:	0 on success, negative on failure
 */
static int ecpriss_global_operation_mode_cfg(void)
{
	/*Todo: Complete this function */
	return 0;
}


/**
 * ecpri_qudp_fh_enable_stats()
 *
 *
 * Returns:	0 on success, negative on failure
 */
static int ecpriss_qudp_enable_stats(uint8_t                 port_index,
		uint32_t                port_type)
{
	/* Todo:Complete stats */
	if(port_type == ECPRISS_PORT_TYPE_FH)
	{
	}
	else if (port_type == ECPRISS_PORT_TYPE_C2C)
	{
	}
	else if (port_type == ECPRISS_PORT_TYPE_L2)
	{
	}

	return 0;
}


#endif
#if 0


void ecpriss_qudp_print_c2c_egress_stats(uint32_t port_index, uint32_t link_index)
{
	uint32_t lsb_val = 0;
	uint64_t msb_val = 0;
	uint64_t val = 0;
	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_EGRESS_NUM_UDP_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_EGRESS_NUM_UDP_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->c2c_port_cfg[port_index].stats.egress_num_udp_packets[link_index] = val;
	ECPRILOGINFO("ECPRI_UDP_C2C_EGRESS_NUM_UDP_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val =ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_EGRESS_NUM_ETH_ONLY_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_EGRESS_NUM_ETH_ONLY_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->c2c_port_cfg[port_index].stats.egress_num_eth_packets[link_index] = val;
	ECPRILOGINFO("ECPRI_UDP_C2C_EGRESS_NUM_ETH_ONLY_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);


	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_EGRESS_NUM_BYPASSED_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_EGRESS_NUM_BYPASSED_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->c2c_port_cfg[port_index].stats.egress_num_bypassed_packets[link_index] = val;
	ECPRILOGINFO("ECPRI_UDP_C2C_EGRESS_NUM_BYPASSED_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);


	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_EGRESS_MTU_ERR_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val =ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_EGRESS_MTU_ERR_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->c2c_port_cfg[port_index].stats.egress_num_mtu_err_packets[link_index] = val;
	ECPRILOGINFO("ECPRI_UDP_C2C_EGRESS_MTU_ERR_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	return;
}


void ecpriss_qudp_print_c2c_ingress_stats(uint32_t port_index, uint32_t link_index)
{
	uint32_t lsb_val = 0;
	uint64_t msb_val = 0;
	uint64_t val = 0;
	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_NUM_UDP_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_NUM_UDP_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->c2c_port_cfg[port_index].stats.ingress_num_udp_packets[link_index] = val;
	ECPRILOGINFO("ECPRI_UDP_C2C_INGRESS_NUM_UDP_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);


	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_NUM_NON_UDP_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_NUM_NON_UDP_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->c2c_port_cfg[port_index].stats.ingress_num_non_udp_packets[link_index] = val;
	ECPRILOGINFO("ECPRI_UDP_C2C_INGRESS_NUM_NON_UDP_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_FCS_ERR_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_FCS_ERR_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->c2c_port_cfg[port_index].stats.ingress_num_fcs_err_packets[link_index] = val;
	ECPRILOGINFO("ECPRI_UDP_C2C_INGRESS_FCS_ERR_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_IPV4_CS_ERROR_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_IPV4_CS_ERROR_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->c2c_port_cfg[port_index].stats.ingress_num_ipv4_cs_err_packets[link_index] = val;
	ECPRILOGINFO("ECPRI_UDP_C2C_INGRESS_IPV4_CS_ERROR_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_UDP_CS_ERROR_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_UDP_CS_ERROR_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->c2c_port_cfg[port_index].stats.ingress_num_udp_cs_err_packets[link_index] = val;
	ECPRILOGINFO("ECPRI_UDP_C2C_INGRESS_UDP_CS_ERROR_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_VLAN_FILTERED_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_VLAN_FILTERED_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);

	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->c2c_port_cfg[port_index].stats.ingress_num_vlan_filtered_packets[link_index] = val;
	ECPRILOGINFO("ECPRI_UDP_C2C_INGRESS_VLAN_FILTERED_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_SEC_ERR_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_SEC_ERR_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);
	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->c2c_port_cfg[port_index].stats.ingress_num_sec_err_packets[link_index] = val;
	ECPRILOGINFO("ECPRI_UDP_C2C_INGRESS_SEC_ERR_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	lsb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_IP_LEN_ERR_PACKETS_LSB_PORT_p_LINK_n,
			port_index,
			link_index);
	msb_val = ecpriss_qudp_hal_read_reg_mn(ECPRISS_QUDP_C2C,
			ECPRI_UDP_C2C_INGRESS_IP_LEN_ERR_PACKETS_MSB_PORT_p_LINK_n,
			port_index,
			link_index);
	val = msb_val << MSB_SHIFT | lsb_val;
	ecpriss_pdata->qudp_ctx->c2c_port_cfg[port_index].stats.ingress_ip_len_err_packets[link_index] = val;
	ECPRILOGINFO("ECPRI_UDP_C2C_INGRESS_IP_LEN_ERR_PACKETS : port_index :%d link_index %d value = %d\n", port_index,link_index,val);

	return;
}
#endif
