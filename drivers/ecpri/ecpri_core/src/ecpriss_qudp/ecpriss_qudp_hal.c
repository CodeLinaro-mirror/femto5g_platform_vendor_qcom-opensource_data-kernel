/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/io.h>
//#include <linux/delay.h>
#include <net/netlink.h>
#include <net/net_namespace.h>
#include <linux/signal.h>           /* Definition of SIGEV_* constants */
#include <linux/jiffies.h>
#include <linux/uaccess.h>
#include <linux/workqueue.h>
#include <linux/netdevice.h>
#include <linux/of_device.h>
#include <linux/debugfs.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/atomic.h>
#include <linux/fs.h>



#include "ecpriss_qudp_hal.h"

ecpriss_qudp_hal_context_s  ecpriss_qudp_hal_ctx;
static const char *ecpriss_qudp_hal_reg_name_to_str[ECPRISS_QUDP_REG_MAX] = {
	"ECPRI_UDP_FH_HW_PARAMS_0",
	"ECPRI_UDP_FH_HW_PARAMS_1",
	"ECPRI_UDP_FH_INGRESS_CONFIG_P",
	"ECPRI_UDP_FH_EGRESS_IPV4_FIELDS_P",
	"ECPRI_UDP_FH_EGRESS_IPV6_FIELDS_P",
	"ECPRI_UDP_FH_EGRESS_ETH_MTU_P",
	"ECPRI_UDP_FH_EGRESS_SA_TAG_ETHERTYPE_P",
	"ECPRI_UDP_FH_EGRESS_CONFIG_P",
	"ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_P",
	"ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_P",
	"ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_P",
	"ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_P",
	"ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_P",
	"ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_P",
	"ECPRI_UDP_FH_ECPRI_ETHERTYPE_P",
	"ECPRI_UDP_FH_PTP_ETHERTYPE_P",
	"ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n",
	"ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n",
	"ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n",
	"ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n",
	"ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n",
	"ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n",
	"ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS",
	"ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS",
	"ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS",
	"ECPRI_UDP_C2C_HW_PARAMS_0",
	"ECPRI_UDP_C2C_HW_PARAMS_1",
	"ECPRI_UDP_C2C_INGRESS_CONFIG_P",
	"ECPRI_UDP_C2C_EGRESS_IPV4_FIELDS_P",
	"ECPRI_UDP_C2C_EGRESS_IPV6_FIELDS_P",
	"ECPRI_UDP_C2C_EGRESS_ETH_MTU_P",
	"ECPRI_UDP_C2C_EGRESS_SA_TAG_ETHERTYPE_P",
	"ECPRI_UDP_C2C_EGRESS_CONFIG_P",
	"ECPRI_UDP_C2C_UDP_SW_IRQ_STATUS_0_PORT_P",
	"ECPRI_UDP_C2C_UDP_SW_IRQ_STATUS_1_PORT_P",
	"ECPRI_UDP_C2C_ECPRI_ETHERTYPE_P",
	"ECPRI_UDP_C2C_PTP_ETHERTYPE_P",
	"ECPRI_UDP_L2_HW_PARAMS_0",
	"ECPRI_UDP_L2_HW_PARAMS_1",
	"ECPRI_UDP_L2_INGRESS_CONFIG_P",
	"ECPRI_UDP_L2_EGRESS_IPV4_FIELDS_P",
	"ECPRI_UDP_L2_EGRESS_IPV6_FIELDS_P",
	"ECPRI_UDP_L2_EGRESS_ETH_MTU_P",
	"ECPRI_UDP_L2_EGRESS_SA_TAG_ETHERTYPE_P",
	"ECPRI_UDP_L2_EGRESS_CONFIG_P",
	"ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_PORT_P",
	"ECPRI_UDP_L2_ECPRI_ETHERTYPE_P",
	"ECPRI_UDP_L2_PTP_ETHERTYPE_P",
	"ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n",
	"ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n",
	"ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n",
	"ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n",
	"ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n",
	"ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n",
	"ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n",
	"ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n",
	"ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n",
	"ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n",
	"ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n",
	"ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n",
	"ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n",
	"ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n",
	"ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n",
	"ECPRI_UDP_FH_INGRESS_NUM_UDP_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_FH_INGRESS_NUM_UDP_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_FH_INGRESS_NUM_NON_UDP_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_FH_INGRESS_NUM_NON_UDP_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_FH_INGRESS_FCS_ERR_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_FH_INGRESS_FCS_ERR_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_FH_INGRESS_IPV4_CS_ERROR_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_FH_INGRESS_IPV4_CS_ERROR_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_FH_INGRESS_UDP_CS_ERROR_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_FH_INGRESS_UDP_CS_ERROR_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_FH_INGRESS_IP_FILTERED_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_FH_INGRESS_IP_FILTERED_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_FH_INGRESS_VLAN_FILTERED_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_FH_INGRESS_VLAN_FILTERED_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_FH_INGRESS_SEC_ERR_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_FH_INGRESS_SEC_ERR_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_FH_INGRESS_IP_LEN_ERR_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_FH_INGRESS_IP_LEN_ERR_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_FH_EGRESS_NUM_UDP_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_FH_EGRESS_NUM_UDP_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_FH_EGRESS_NUM_ETH_ONLY_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_FH_EGRESS_NUM_ETH_ONLY_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_FH_EGRESS_NUM_BYPASSED_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_FH_EGRESS_NUM_BYPASSED_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_FH_EGRESS_MTU_ERR_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_FH_EGRESS_MTU_ERR_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_L2_INGRESS_NUM_UDP_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_L2_INGRESS_NUM_UDP_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_L2_INGRESS_NUM_NON_UDP_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_L2_INGRESS_NUM_NON_UDP_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_L2_INGRESS_FCS_ERR_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_L2_INGRESS_FCS_ERR_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_L2_INGRESS_IPV4_CS_ERROR_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_L2_INGRESS_IPV4_CS_ERROR_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_L2_INGRESS_UDP_CS_ERROR_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_L2_INGRESS_UDP_CS_ERROR_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_L2_INGRESS_IP_FILTERED_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_L2_INGRESS_IP_FILTERED_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_L2_INGRESS_VLAN_FILTERED_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_L2_INGRESS_VLAN_FILTERED_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_L2_INGRESS_SEC_ERR_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_L2_INGRESS_SEC_ERR_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_L2_INGRESS_IP_LEN_ERR_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_L2_INGRESS_IP_LEN_ERR_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_L2_EGRESS_NUM_UDP_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_L2_EGRESS_NUM_UDP_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_L2_EGRESS_NUM_ETH_ONLY_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_L2_EGRESS_NUM_ETH_ONLY_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_L2_EGRESS_NUM_BYPASSED_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_L2_EGRESS_NUM_BYPASSED_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_L2_EGRESS_MTU_ERR_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_L2_EGRESS_MTU_ERR_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_C2C_INGRESS_NUM_UDP_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_C2C_INGRESS_NUM_UDP_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_C2C_INGRESS_NUM_NON_UDP_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_C2C_INGRESS_NUM_NON_UDP_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_C2C_INGRESS_FCS_ERR_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_C2C_INGRESS_FCS_ERR_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_C2C_INGRESS_IPV4_CS_ERROR_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_C2C_INGRESS_IPV4_CS_ERROR_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_C2C_INGRESS_UDP_CS_ERROR_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_C2C_INGRESS_UDP_CS_ERROR_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_C2C_INGRESS_IP_FILTERED_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_C2C_INGRESS_IP_FILTERED_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_C2C_INGRESS_VLAN_FILTERED_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_C2C_INGRESS_VLAN_FILTERED_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_C2C_INGRESS_SEC_ERR_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_C2C_INGRESS_SEC_ERR_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_C2C_INGRESS_IP_LEN_ERR_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_C2C_INGRESS_IP_LEN_ERR_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_C2C_EGRESS_NUM_UDP_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_C2C_EGRESS_NUM_UDP_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_C2C_EGRESS_NUM_ETH_ONLY_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_C2C_EGRESS_NUM_ETH_ONLY_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_C2C_EGRESS_NUM_BYPASSED_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_C2C_EGRESS_NUM_BYPASSED_PACKETS_MSB_PORT_p_LINK_n",
	"ECPRI_UDP_C2C_EGRESS_MTU_ERR_PACKETS_LSB_PORT_p_LINK_n",
	"ECPRI_UDP_C2C_EGRESS_MTU_ERR_PACKETS_MSB_PORT_p_LINK_n"
};



	static void ecpriss_qudp_hal_reg_parse_udp_fh_params_0
(ecpriss_qudp_hal_reg_name_e reg, void *fields, uint32_t val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_hw_params_0_s *fh_hw_params
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_hw_params_0_s *)fields;

	fh_hw_params->instance_type = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_HW_PARAMS_0_INSTANCE_TYPE_SHFT,
			HWIO_ECPRI_UDP_FH_HW_PARAMS_0_INSTANCE_TYPE_BMSK);

	fh_hw_params->ports_n = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_HW_PARAMS_0_PORTS_N_SHFT,
			HWIO_ECPRI_UDP_FH_HW_PARAMS_0_PORTS_N_BMSK);

	fh_hw_params->links_n = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_HW_PARAMS_0_LINKS_N_SHFT,
			HWIO_ECPRI_UDP_FH_HW_PARAMS_0_LINKS_N_BMSK);

	fh_hw_params->eth_table_entries_n = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_HW_PARAMS_0_ETH_TABLE_ENTRIES_N_SHFT,
			HWIO_ECPRI_UDP_FH_HW_PARAMS_0_ETH_TABLE_ENTRIES_N_BMSK);

	fh_hw_params->ip_table_entries_n =	ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_HW_PARAMS_0_IP_TABLE_ENTRIES_N_SHFT,
			HWIO_ECPRI_UDP_FH_HW_PARAMS_0_IP_TABLE_ENTRIES_N_BMSK);

	fh_hw_params->udp_classification_entries_n = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_HW_PARAMS_0_UDP_CLASSIFICATION_ENTRIES_N_SHFT,
			HWIO_ECPRI_UDP_FH_HW_PARAMS_0_UDP_CLASSIFICATION_ENTRIES_N_BMSK);

	fh_hw_params->l3_support = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_HW_PARAMS_0_L3_SUPPORT_SHFT,
			HWIO_ECPRI_UDP_FH_HW_PARAMS_0_L3_SUPPORT_BMSK);

	return;
}



	static void ecpriss_qudp_hal_reg_construct_udp_fh_ingress_config_p
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_config_p_s *ingress_config_p
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_config_p_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ingress_config_p->enable_ip_dst_filt,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_IP_DST_FILT_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_IP_DST_FILT_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ingress_config_p->enable_udp_dst_class,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_UDP_DST_CLASS_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_UDP_DST_CLASS_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ingress_config_p->enable_vlan_filt,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_VLAN_FILT_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_VLAN_FILT_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ingress_config_p->enable_udp_cs_check,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_UDP_CS_CHECK_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_UDP_CS_CHECK_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ingress_config_p->ipv4_cs_err_action,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_IPV4_CS_ERR_ACTION_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_IPV4_CS_ERR_ACTION_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ingress_config_p->udp_cs_err_action,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_UDP_CS_ERR_ACTION_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_UDP_CS_ERR_ACTION_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ingress_config_p->fcs_err_action,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_FCS_ERR_ACTION_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_FCS_ERR_ACTION_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ingress_config_p->pkt_err_action,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_PKT_ERR_ACTION_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_PKT_ERR_ACTION_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ingress_config_p->ip_len_err_action,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_IP_LEN_ERR_ACTION_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_IP_LEN_ERR_ACTION_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ingress_config_p->disable_st_and_fw,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_DISABLE_ST_AND_FW_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_DISABLE_ST_AND_FW_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ingress_config_p->vlan_filt_miss_action,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_VLAN_FILT_MISS_ACTION_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_VLAN_FILT_MISS_ACTION_BMSK);


	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ingress_config_p->use_external_not_local_mac_dst,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_USE_EXTERNAL_NOT_LOCAL_MAC_DST_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_USE_EXTERNAL_NOT_LOCAL_MAC_DST_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ingress_config_p->enable_broadcast_check,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_BROADCAST_CHECK_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_BROADCAST_CHECK_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ingress_config_p->last_in_chain,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_LAST_IN_CHAIN_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_LAST_IN_CHAIN_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ingress_config_p->non_local_dst_action,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_NON_LOCAL_DST_ACTION_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_NON_LOCAL_DST_ACTION_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ingress_config_p->enable_shared_filtering_2_links,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_SHARED_FILTERING_2_LINKS_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_SHARED_FILTERING_2_LINKS_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ingress_config_p->enable_shared_filtering_4_links,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_SHARED_FILTERING_4_LINKS_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_SHARED_FILTERING_4_LINKS_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ingress_config_p->enable_eth_padding_removal,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_ETH_PADDING_REMOVAL_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_ETH_PADDING_REMOVAL_BMSK);

	return;
}



	static void ecpriss_qudp_hal_reg_parse_udp_fh_ingress_config_p
(ecpriss_qudp_hal_reg_name_e reg, void *fields, uint32_t val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_config_p_s *ingress_config_p
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_config_p_s *)fields;

	ingress_config_p->enable_ip_dst_filt = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_IP_DST_FILT_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_IP_DST_FILT_BMSK);

	ingress_config_p->enable_udp_dst_class = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_UDP_DST_CLASS_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_UDP_DST_CLASS_BMSK);

	ingress_config_p->enable_vlan_filt = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_VLAN_FILT_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_VLAN_FILT_BMSK);

	ingress_config_p->enable_udp_cs_check = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_UDP_CS_CHECK_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_UDP_CS_CHECK_BMSK);

	ingress_config_p->ipv4_cs_err_action = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_IPV4_CS_ERR_ACTION_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_IPV4_CS_ERR_ACTION_BMSK);

	ingress_config_p->udp_cs_err_action = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_UDP_CS_ERR_ACTION_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_UDP_CS_ERR_ACTION_BMSK);

	ingress_config_p->fcs_err_action = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_FCS_ERR_ACTION_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_FCS_ERR_ACTION_BMSK);

	ingress_config_p->pkt_err_action = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_PKT_ERR_ACTION_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_PKT_ERR_ACTION_BMSK);

	ingress_config_p->ip_len_err_action = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_IP_LEN_ERR_ACTION_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_IP_LEN_ERR_ACTION_BMSK);

	ingress_config_p->disable_st_and_fw = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_DISABLE_ST_AND_FW_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_DISABLE_ST_AND_FW_BMSK);

	ingress_config_p->vlan_filt_miss_action = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_VLAN_FILT_MISS_ACTION_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_VLAN_FILT_MISS_ACTION_BMSK);


	ingress_config_p->use_external_not_local_mac_dst = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_USE_EXTERNAL_NOT_LOCAL_MAC_DST_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_USE_EXTERNAL_NOT_LOCAL_MAC_DST_BMSK);

	ingress_config_p->enable_broadcast_check = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_BROADCAST_CHECK_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_BROADCAST_CHECK_BMSK);

	ingress_config_p->last_in_chain = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_LAST_IN_CHAIN_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_LAST_IN_CHAIN_BMSK);

	ingress_config_p->non_local_dst_action = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_NON_LOCAL_DST_ACTION_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_NON_LOCAL_DST_ACTION_BMSK);


	ingress_config_p->enable_shared_filtering_2_links = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_SHARED_FILTERING_2_LINKS_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_SHARED_FILTERING_2_LINKS_BMSK);

	ingress_config_p->enable_shared_filtering_4_links = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_SHARED_FILTERING_4_LINKS_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_SHARED_FILTERING_4_LINKS_BMSK);

	ingress_config_p->enable_eth_padding_removal = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_ETH_PADDING_REMOVAL_SHFT,
			HWIO_ECPRI_UDP_FH_INGRESS_CONFIG_p_ENABLE_ETH_PADDING_REMOVAL_BMSK);

	return;
}

	static void ecpriss_qudp_hal_reg_parse_udp_fh_params_1
(ecpriss_qudp_hal_reg_name_e reg, void *fields, uint32_t val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_hw_params_1_s *fh_hw_params
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_hw_params_1_s *)fields;

	fh_hw_params->vlan_filt_entries_n = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_HW_PARAMS_1_VLAN_FILT_ENTRIES_N_SHFT,
			HWIO_ECPRI_UDP_FH_HW_PARAMS_1_VLAN_FILT_ENTRIES_N_BMSK);

	fh_hw_params->ip_filt_entries_n = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_HW_PARAMS_1_IP_FILT_ENTRIES_N_SHFT,
			HWIO_ECPRI_UDP_FH_HW_PARAMS_1_IP_FILT_ENTRIES_N_BMSK);

	fh_hw_params->eth_dst_filt_entries_n = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_HW_PARAMS_1_ETH_DST_FILT_ENTRIES_N_SHFT,
			HWIO_ECPRI_UDP_FH_HW_PARAMS_1_ETH_DST_FILT_ENTRIES_N_BMSK);

	return;
}


	static void ecpriss_qudp_hal_reg_construct_udp_fh_egress_ipv4_fields_p
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ipv4_fields_p_s *ipv4_fields
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ipv4_fields_p_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ipv4_fields->id,
			HWIO_ECPRI_UDP_FH_EGRESS_IPV4_FIELDS_p_ID_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_IPV4_FIELDS_p_ID_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ipv4_fields->ttl,
			HWIO_ECPRI_UDP_FH_EGRESS_IPV4_FIELDS_p_TTL_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_IPV4_FIELDS_p_TTL_BMSK);
	return;
}


	static void ecpriss_qudp_hal_reg_construct_udp_fh_egress_ipv6_fields_p
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ipv6_fields_p_s *ipv6_fields
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ipv6_fields_p_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ipv6_fields->hop_limit,
			HWIO_ECPRI_UDP_FH_EGRESS_IPV6_FIELDS_p_HOP_LIMIT_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_IPV6_FIELDS_p_HOP_LIMIT_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ipv6_fields->flow_label,
			HWIO_ECPRI_UDP_FH_EGRESS_IPV6_FIELDS_p_FLOW_LABEL_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_IPV6_FIELDS_p_FLOW_LABEL_BMSK);
	return;
}



	static void ecpriss_qudp_hal_reg_construct_udp_fh_egress_eth_mtu_p
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_mtu_p_s *eth_mtu
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_mtu_p_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			eth_mtu->value,
			HWIO_ECPRI_UDP_FH_EGRESS_ETH_MTU_p_VALUE_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_ETH_MTU_p_VALUE_BMSK);

	return;
}

	static void ecpriss_qudp_hal_reg_parse_udp_fh_egress_eth_mtu_p
(ecpriss_qudp_hal_reg_name_e reg,  void *fields, uint32_t val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_mtu_p_s *eth_mtu
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_mtu_p_s *)fields;

	eth_mtu->value = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_EGRESS_ETH_MTU_p_VALUE_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_ETH_MTU_p_VALUE_BMSK);

	return;
}



	static void ecpriss_qudp_hal_reg_construct_udp_fh_egress_sa_tag_ethertype_p
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_sa_tag_ethertype_p_s *sa_tag_ethertype
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_egress_sa_tag_ethertype_p_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			sa_tag_ethertype->value,
			HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_ETHERTYPE_p_VALUE_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_ETHERTYPE_p_VALUE_BMSK);

	return;
}



	static void ecpriss_qudp_hal_reg_construct_udp_fh_egress_config_p
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_config_p_s *egress_config
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_egress_config_p_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			egress_config->calc_ip_udp_len_from_byte_count,
			HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_CALC_IP_UDP_LEN_FROM_BYTE_COUNT_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_CALC_IP_UDP_LEN_FROM_BYTE_COUNT_BMSK);
	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			egress_config->bypassed_packets_vport_action,
			HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_BYPASSED_PACKETS_VPORT_ACTION_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_BYPASSED_PACKETS_VPORT_ACTION_BMSK);
	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			egress_config->bypassed_packets_vport,
			HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_BYPASSED_PACKETS_VPORT_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_CONFIG_p_BYPASSED_PACKETS_VPORT_BMSK);

	return;
}


	static void ecpriss_qudp_hal_reg_construct_udp_fh_ecpri_ethertype_p
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{


	ecpri_qudp_hwio_def_ecpri_udp_fh_ecpri_ethertype_p_s *ecpri_ethertype_p
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_ecpri_ethertype_p_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ecpri_ethertype_p->value,
			HWIO_ECPRI_UDP_FH_ECPRI_ETHERTYPE_p_VALUE_SHFT,
			HWIO_ECPRI_UDP_FH_ECPRI_ETHERTYPE_p_VALUE_BMSK);

	return;

}

#if 0
	static void ecpriss_qudp_hal_reg_construct_udp_fh_sw_irq_status_0_port_p
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_ecpri_ethertype_p_s *ecpri_ethertype_p
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_ecpri_ethertype_p_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ecpri_ethertype_p->value,
			HWIO_ECPRI_UDP_FH_ECPRI_ETHERTYPE_p_VALUE_SHFT,
			HWIO_ECPRI_UDP_FH_ECPRI_ETHERTYPE_p_VALUE_BMSK);
	return;
}



	static void ecpriss_qudp_hal_reg_construct_udp_fh_ptp_ethertype_p
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{


	ecpri_qudp_hwio_def_ecpri_udp_fh_ptp_ethertype_p_s *ptp_ethertype_p
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_ptp_ethertype_p_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ptp_ethertype_p->value,
			HWIO_ECPRI_UDP_FH_PTP_ETHERTYPE_p_VALUE_SHFT,
			HWIO_ECPRI_UDP_FH_PTP_ETHERTYPE_p_VALUE_BMSK);

	return;
}
#endif
	static void ecpriss_qudp_hal_reg_construct_filt_ip_dst_addr0_port_p_entry_n
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{


	ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr0_port_p_entry_n_s *ip_dst_addr0_port_p_entry_n
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr0_port_p_entry_n_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ip_dst_addr0_port_p_entry_n->value,
			HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_VALUE_SHFT,
			HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n_VALUE_BMSK);
	return;
}

	static void ecpriss_qudp_hal_reg_construct_filt_ip_dst_addr1_port_p_entry_n
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr1_port_p_entry_n_s *ip_dst_addr1_port_p_entry_n
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr1_port_p_entry_n_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ip_dst_addr1_port_p_entry_n->value,
			HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_VALUE_SHFT,
			HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n_VALUE_BMSK);
	return;
}

	static void ecpriss_qudp_hal_reg_construct_filt_ip_dst_addr2_port_p_entry_n
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr2_port_p_entry_n_s *ip_dst_addr2_port_p_entry_n
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr2_port_p_entry_n_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ip_dst_addr2_port_p_entry_n->value,
			HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_VALUE_SHFT,
			HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n_VALUE_BMSK);
	return;
}


	static void ecpriss_qudp_hal_reg_construct_filt_ip_dst_addr3_port_p_entry_n
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr3_port_p_entry_n_s *ip_dst_addr3_port_p_entry_n
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr3_port_p_entry_n_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ip_dst_addr3_port_p_entry_n->value,
			HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_VALUE_SHFT,
			HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n_VALUE_BMSK);
	return;
}


	static void ecpriss_qudp_hal_reg_construct_filt_vlan_addr_port_port_p_entry_n
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_filt_vlan_addr_port_p_entry_n_s *vlan_addr_port_p_entry_n
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_filt_vlan_addr_port_p_entry_n_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			vlan_addr_port_p_entry_n->value,
			HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n_VALUE_SHFT,
			HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n_VALUE_BMSK);
	return;
}


	static void ecpriss_qudp_hal_reg_construct_udp_fh_udp_classification_list_port_p_entry_n
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_udp_classification_list_port_p_entry_n_s *fh_udp_classification_list_port_p_entry_n
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_udp_classification_list_port_p_entry_n_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_classification_list_port_p_entry_n->value,
			HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_VALUE_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_VALUE_BMSK);
	return;
}

#if 0
	static void ecpriss_qudp_hal_reg_parse_udp_fh_udp_classification_list_port_p_entry_n
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_udp_classification_list_port_p_entry_n_s *fh_udp_classification_list_port_p_entry_n
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_udp_classification_list_port_p_entry_n_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_classification_list_port_p_entry_n->value,
			HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_VALUE_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n_VALUE_BMSK);
	return;
}
#endif

	static void  ecpriss_qudp_hal_reg_construct_filt_udp_fh_filt_ip_dst_addr_port_p_entries_valid_bits
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr_port_p_entries_valid_bits_s *ip_dst_addr_port_p_entries_valid
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr_port_p_entries_valid_bits_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ip_dst_addr_port_p_entries_valid->valid_bits,
			HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_SHFT,
			HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_BMSK);
	return;
}


	static void  ecpriss_qudp_hal_reg_parse_filt_udp_fh_filt_ip_dst_addr_port_p_entries_valid_bits
(ecpriss_qudp_hal_reg_name_e reg,  void *fields, uint32_t val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr_port_p_entries_valid_bits_s *ip_dst_addr_port_p_entries_valid
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr_port_p_entries_valid_bits_s *)fields;

	ip_dst_addr_port_p_entries_valid->valid_bits = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_SHFT,
			HWIO_ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_BMSK);

	return;
}

	static void ecpriss_qudp_hal_reg_construct_udp_fh_filt_vlan_addr_port_p_entries_valid_bits
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_filt_vlan_addr_port_p_entries_valid_bits_s *vlan_addr_port_p_entries_valid
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_filt_vlan_addr_port_p_entries_valid_bits_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			vlan_addr_port_p_entries_valid->valid_bits,
			HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_SHFT,
			HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_BMSK);
	return;
}

	static void ecpriss_qudp_hal_reg_parse_udp_fh_filt_vlan_addr_port_p_entries_valid_bits
(ecpriss_qudp_hal_reg_name_e reg, void *fields, uint32_t val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_filt_vlan_addr_port_p_entries_valid_bits_s *vlan_addr_port_p_entries_valid
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_filt_vlan_addr_port_p_entries_valid_bits_s *)fields;

	vlan_addr_port_p_entries_valid->valid_bits = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_SHFT,
			HWIO_ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_BMSK);

	return;
}



	static void ecpriss_qudp_hal_reg_construct_udp_classification_list_port_p_entries_valid_bits
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_udp_classification_list_port_p_entries_valid_bits_s *udp_classification_list_port_p_entries_valid_bits
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_udp_classification_list_port_p_entries_valid_bits_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			udp_classification_list_port_p_entries_valid_bits->valid_bits,
			HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_BMSK);
	return;
}

	static void ecpriss_qudp_hal_reg_parse_udp_classification_list_port_p_entries_valid_bits
(ecpriss_qudp_hal_reg_name_e reg,  void *fields, uint32_t val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_udp_classification_list_port_p_entries_valid_bits_s *udp_classification_list_port_p_entries_valid_bits
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_udp_classification_list_port_p_entries_valid_bits_s *)fields;

	udp_classification_list_port_p_entries_valid_bits->valid_bits = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS_VALID_BITS_BMSK);

	return;
}

	static void ecpriss_qudp_hal_reg_construct_fh_egress_eth_dst0_port_p_entry_n
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_dst0_port_p_entry_n_s *eth_dst0_port_p_entry_n
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_dst0_port_p_entry_n_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			eth_dst0_port_p_entry_n->value,
			HWIO_ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n_VALUE_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n_VALUE_BMSK);
	return;
}

	static void ecpriss_qudp_hal_reg_construct_fh_egress_eth_src1_dst1_port_p_entry_n
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_src1_dst1_port_p_entry_n_s *eth_src1_dst1_port_p_entry_n
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_src1_dst1_port_p_entry_n_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			eth_src1_dst1_port_p_entry_n->src_msb,
			HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_SRC_MSB_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_SRC_MSB_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			eth_src1_dst1_port_p_entry_n->dst_msb,
			HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_DST_MSB_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n_DST_MSB_BMSK);

	return;
}


	static void ecpriss_qudp_hal_reg_construct_fh_egress_eth_src0_port_p_entry_n
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_src0_port_p_entry_n_s *eth_src0_port_p_entry_n
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_src0_port_p_entry_n_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			eth_src0_port_p_entry_n->value,
			HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_VALUE_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n_VALUE_BMSK);
	return;
}

	static void ecpriss_qudp_hal_reg_construct_fh_egress_vlan_ethertype_port_p_entry_n
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_vlan_ethertype_port_p_entry_n_s *vlan_ethertype_port_p_entry_n
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_egress_vlan_ethertype_port_p_entry_n_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			vlan_ethertype_port_p_entry_n->ethertype,
			HWIO_ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_ETHERTYPE_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_ETHERTYPE_BMSK);
	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			vlan_ethertype_port_p_entry_n->vlan_data,
			HWIO_ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_VLAN_DATA_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n_VLAN_DATA_BMSK);

	return;
}

	static void ecpriss_qudp_hal_reg_construct_fh_egress_vport_misc_port_p_entry_n
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_vport_misc_port_p_entry_n_s *vport_misc_port_p_entry_n
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_egress_vport_misc_port_p_entry_n_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			vport_misc_port_p_entry_n->vport,
			HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_VPORT_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_VPORT_BMSK);
	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			vport_misc_port_p_entry_n->has_vlan,
			HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_HAS_VLAN_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_HAS_VLAN_BMSK);
	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			vport_misc_port_p_entry_n->vport_action,
			HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_VPORT_ACTION_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n_VPORT_ACTION_BMSK);
	return;
}


	static void ecpriss_qudp_hal_reg_construct_fh_egress_ip_src_addr0_port_p_entry_n
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr0_port_p_entry_n_s *ip_src0_port_p_entry_n
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr0_port_p_entry_n_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ip_src0_port_p_entry_n->value,
			HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_VALUE_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n_VALUE_BMSK);
	return;
}



	static void ecpriss_qudp_hal_reg_construct_fh_egress_ip_src_addr1_port_p_entry_n
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr1_port_p_entry_n_s *ip_src1_port_p_entry_n
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr1_port_p_entry_n_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ip_src1_port_p_entry_n->value,
			HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_VALUE_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n_VALUE_BMSK);
	return;
}


	static void ecpriss_qudp_hal_reg_construct_fh_egress_ip_src_addr2_port_p_entry_n
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr2_port_p_entry_n_s *ip_src2_port_p_entry_n
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr2_port_p_entry_n_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ip_src2_port_p_entry_n->value,
			HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_VALUE_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n_VALUE_BMSK);
	return;
}


	static void ecpriss_qudp_hal_reg_construct_fh_egress_ip_src_addr3_port_p_entry_n
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr3_port_p_entry_n_s *ip_src3_port_p_entry_n
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr3_port_p_entry_n_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ip_src3_port_p_entry_n->value,
			HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_VALUE_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n_VALUE_BMSK);
	return;
}


	static void ecpriss_qudp_hal_reg_construct_fh_egress_ip_dst_addr0_port_p_entry_n
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr0_port_p_entry_n_s *ip_dst_addr0_port_p_entry_n
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr0_port_p_entry_n_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ip_dst_addr0_port_p_entry_n->value,
			HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_VALUE_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n_VALUE_BMSK);
	return;
}



	static void ecpriss_qudp_hal_reg_construct_fh_egress_ip_dst_addr1_port_p_entry_n
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr1_port_p_entry_n_s *ip_dst_addr1_port_p_entry_n
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr1_port_p_entry_n_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ip_dst_addr1_port_p_entry_n->value,
			HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_VALUE_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n_VALUE_BMSK);
	return;
}



	static void ecpriss_qudp_hal_reg_construct_fh_egress_ip_dst_addr2_port_p_entry_n
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr2_port_p_entry_n_s *ip_dst_addr2_port_p_entry_n
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr2_port_p_entry_n_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ip_dst_addr2_port_p_entry_n->value,
			HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_VALUE_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n_VALUE_BMSK);
	return;
}


	static void ecpriss_qudp_hal_reg_construct_fh_egress_ip_dst_addr3_port_p_entry_n
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr3_port_p_entry_n_s *ip_dst_addr3_port_p_entry_n
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr3_port_p_entry_n_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			ip_dst_addr3_port_p_entry_n->value,
			HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_VALUE_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n_VALUE_BMSK);
	return;
}


	static void ecpriss_qudp_hal_reg_construct_fh_egress_udp_ports_port_p_entry_n
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_udp_ports_port_p_entry_n_s *udp_ports_port_p_entry_n
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_egress_udp_ports_port_p_entry_n_s *)fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			udp_ports_port_p_entry_n->src,
			HWIO_ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_SRC_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_SRC_BMSK);
	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			udp_ports_port_p_entry_n->dst,
			HWIO_ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_DST_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n_DST_BMSK);
	return;
}

	static void ecpriss_qudp_hal_reg_construct_fh_egress_sa_tag_ip_tos_misc_port_p_entry_n
(ecpriss_qudp_hal_reg_name_e reg, const void *fields, uint32_t* val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_egress_sa_tag_ip_tos_misc_port_p_entry_n_s *sa_tag_ip_tos_misc_port_p_entry_n
		= (ecpri_qudp_hwio_def_ecpri_udp_fh_egress_sa_tag_ip_tos_misc_port_p_entry_n_s *)fields;
	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			sa_tag_ip_tos_misc_port_p_entry_n->sa_tag_data,
			HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_SA_TAG_DATA_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_SA_TAG_DATA_BMSK);
	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			sa_tag_ip_tos_misc_port_p_entry_n->tos,
			HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_TOS_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_TOS_BMSK);
	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			sa_tag_ip_tos_misc_port_p_entry_n->ip_type,
			HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_IP_TYPE_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_IP_TYPE_BMSK);
	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			sa_tag_ip_tos_misc_port_p_entry_n->is_ipsec,
			HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_IS_IPSEC_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_IS_IPSEC_BMSK);
	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			sa_tag_ip_tos_misc_port_p_entry_n->df_bit,
			HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_DF_BIT_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_DF_BIT_BMSK);
	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			sa_tag_ip_tos_misc_port_p_entry_n->calc_udp_cs,
			HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_CALC_UDP_CS_SHFT,
			HWIO_ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n_CALC_UDP_CS_BMSK);
	return;
}

static void ecpriss_qudp_hal_reg_construct_dummy(ecpriss_qudp_hal_reg_name_e reg,
		const void *fields,
		uint32_t *val)
{
	return;
}

static void ecpriss_qudp_hal_reg_parse_udp_fh_sw_irq_status_0_port_p(ecpriss_qudp_hal_reg_name_e reg,
		void *fields,
		uint32_t val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_status_0_port_p_s *fh_udp_sw_irq_status_0_port_p =
		(ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_status_0_port_p_s *) fields;

	fh_udp_sw_irq_status_0_port_p->egress_mtu_err_packet_link_0 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_0_BMSK);

	fh_udp_sw_irq_status_0_port_p->ingress_fcs_err_packet_link_0 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_0_BMSK);

	fh_udp_sw_irq_status_0_port_p->ingress_pkt_fifo_empty_before_eop_link_0 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_0_BMSK);

	fh_udp_sw_irq_status_0_port_p->ingress_ipv4_cs_error_link_0  = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_0_BMSK);

	fh_udp_sw_irq_status_0_port_p->ingress_udp_cs_error_link_0 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_0_BMSK);

	fh_udp_sw_irq_status_0_port_p->ingress_sec_err_packet_link_0 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_0_BMSK);

	fh_udp_sw_irq_status_0_port_p->ingress_ip_len_err_packet_link_0 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_0_BMSK);

	fh_udp_sw_irq_status_0_port_p->ingress_trap_rule_0_link_0 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_0_BMSK);

	fh_udp_sw_irq_status_0_port_p->ingress_trap_rule_1_link_0= ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_0_BMSK);

	fh_udp_sw_irq_status_0_port_p->ingress_trap_rule_2_link_0 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_0_BMSK);

	fh_udp_sw_irq_status_0_port_p->ingress_trap_rule_3_link_0 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_0_BMSK);

	fh_udp_sw_irq_status_0_port_p->ingress_last_in_chain_non_local_dst_packet_link_0 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_0_BMSK);


	//link1
	fh_udp_sw_irq_status_0_port_p->egress_mtu_err_packet_link_1 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_1_BMSK);

	fh_udp_sw_irq_status_0_port_p->ingress_fcs_err_packet_link_1 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_1_BMSK);

	fh_udp_sw_irq_status_0_port_p->ingress_pkt_fifo_empty_before_eop_link_1 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_1_BMSK);

	fh_udp_sw_irq_status_0_port_p->ingress_ipv4_cs_error_link_1  = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_1_BMSK);

	fh_udp_sw_irq_status_0_port_p->ingress_udp_cs_error_link_1 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_1_BMSK);

	fh_udp_sw_irq_status_0_port_p->ingress_sec_err_packet_link_1 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_1_BMSK);

	fh_udp_sw_irq_status_0_port_p->ingress_ip_len_err_packet_link_1 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_1_BMSK);

	fh_udp_sw_irq_status_0_port_p->ingress_trap_rule_0_link_1 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_1_BMSK);

	fh_udp_sw_irq_status_0_port_p->ingress_trap_rule_1_link_1= ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_1_BMSK);

	fh_udp_sw_irq_status_0_port_p->ingress_trap_rule_2_link_1 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_1_BMSK);

	fh_udp_sw_irq_status_0_port_p->ingress_trap_rule_3_link_1 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_1_BMSK);

	fh_udp_sw_irq_status_0_port_p->ingress_last_in_chain_non_local_dst_packet_link_1 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_1_BMSK);

	return;
}


static void ecpriss_qudp_hal_reg_parse_udp_fh_sw_irq_status_1_port_p(ecpriss_qudp_hal_reg_name_e reg,
		void *fields,
		uint32_t val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_status_1_port_p_s *fh_udp_sw_irq_status_1_port_p =
		(ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_status_1_port_p_s *) fields;

	fh_udp_sw_irq_status_1_port_p->egress_mtu_err_packet_link_2 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_2_BMSK);

	fh_udp_sw_irq_status_1_port_p->ingress_fcs_err_packet_link_2 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_2_BMSK);

	fh_udp_sw_irq_status_1_port_p->ingress_pkt_fifo_empty_before_eop_link_2 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_2_BMSK);

	fh_udp_sw_irq_status_1_port_p->ingress_ipv4_cs_error_link_2  = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_2_BMSK);

	fh_udp_sw_irq_status_1_port_p->ingress_udp_cs_error_link_2 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_UDP_CS_ERROR_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_UDP_CS_ERROR_LINK_2_BMSK);

	fh_udp_sw_irq_status_1_port_p->ingress_sec_err_packet_link_2 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_2_BMSK);

	fh_udp_sw_irq_status_1_port_p->ingress_ip_len_err_packet_link_2 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_2_BMSK);

	fh_udp_sw_irq_status_1_port_p->ingress_trap_rule_0_link_2 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_0_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_0_LINK_2_BMSK);

	fh_udp_sw_irq_status_1_port_p->ingress_trap_rule_1_link_2= ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_1_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_1_LINK_2_BMSK);

	fh_udp_sw_irq_status_1_port_p->ingress_trap_rule_2_link_2 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_2_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_2_LINK_2_BMSK);

	fh_udp_sw_irq_status_1_port_p->ingress_trap_rule_3_link_2 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_3_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_3_LINK_2_BMSK);

	fh_udp_sw_irq_status_1_port_p->ingress_last_in_chain_non_local_dst_packet_link_2 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_2_BMSK);


	//link1
	fh_udp_sw_irq_status_1_port_p->egress_mtu_err_packet_link_3 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_3_BMSK);

	fh_udp_sw_irq_status_1_port_p->ingress_fcs_err_packet_link_3 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_3_BMSK);

	fh_udp_sw_irq_status_1_port_p->ingress_pkt_fifo_empty_before_eop_link_3 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_3_BMSK);

	fh_udp_sw_irq_status_1_port_p->ingress_ipv4_cs_error_link_3  = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_3_BMSK);

	fh_udp_sw_irq_status_1_port_p->ingress_udp_cs_error_link_3 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_UDP_CS_ERROR_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_UDP_CS_ERROR_LINK_3_BMSK);

	fh_udp_sw_irq_status_1_port_p->ingress_sec_err_packet_link_3 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_3_BMSK);

	fh_udp_sw_irq_status_1_port_p->ingress_ip_len_err_packet_link_3 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_3_BMSK);

	fh_udp_sw_irq_status_1_port_p->ingress_trap_rule_0_link_3 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_0_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_0_LINK_3_BMSK);

	fh_udp_sw_irq_status_1_port_p->ingress_trap_rule_1_link_3= ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_1_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_1_LINK_3_BMSK);

	fh_udp_sw_irq_status_1_port_p->ingress_trap_rule_2_link_3 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_2_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_2_LINK_3_BMSK);

	fh_udp_sw_irq_status_1_port_p->ingress_trap_rule_3_link_3 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_3_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_TRAP_RULE_3_LINK_3_BMSK);

	fh_udp_sw_irq_status_1_port_p->ingress_last_in_chain_non_local_dst_packet_link_3 = ECPRISS_HAL_GETFIELD_FROM_REG(val,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_3_BMSK);

	return;
}

static void ecpriss_qudp_hal_reg_parse_udp_fh_sw_irq_mask_0_port_p(ecpriss_qudp_hal_reg_name_e reg,
		void *fields,
		uint32_t val)
{
	return;
}

static void ecpriss_qudp_hal_reg_parse_udp_fh_sw_irq_mask_1_port_p(ecpriss_qudp_hal_reg_name_e reg,
		void *fields,
		uint32_t val)
{
	return;
}


static void ecpriss_qudp_hal_reg_parse_udp_fh_sw_irq_clr_0_port_p(ecpriss_qudp_hal_reg_name_e reg,
		void *fields,
		uint32_t val)
{
	return;
}

static void ecpriss_qudp_hal_reg_parse_udp_fh_sw_irq_clr_1_port_p(ecpriss_qudp_hal_reg_name_e reg,
		void *fields,
		uint32_t val)
{
	return;
}



static void ecpriss_qudp_hal_reg_construct_udp_fh_sw_irq_mask_0_port_p(ecpriss_qudp_hal_reg_name_e reg,
		const void *fields,
		uint32_t *val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_mask_0_port_p_s *fh_udp_sw_irq_mask_0_port_p =
		(ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_mask_0_port_p_s *) fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_0_port_p->egress_mtu_err_packet_link_0,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_0_port_p->ingress_fcs_err_packet_link_0,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_0_port_p->ingress_pkt_fifo_empty_before_eop_link_0,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_0_port_p->ingress_ipv4_cs_error_link_0,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_0_port_p->ingress_udp_cs_error_link_0,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_0_port_p->ingress_sec_err_packet_link_0,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_0_port_p->ingress_ip_len_err_packet_link_0,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_0_port_p->ingress_trap_rule_0_link_0,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_0_port_p->ingress_trap_rule_1_link_0,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_0_port_p->ingress_trap_rule_2_link_0,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_0_port_p->ingress_trap_rule_3_link_0,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_0_port_p->ingress_last_in_chain_non_local_dst_packet_link_0,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_0_BMSK);


	//link1
	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_0_port_p->egress_mtu_err_packet_link_1,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_0_port_p->ingress_fcs_err_packet_link_1,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_0_port_p->ingress_pkt_fifo_empty_before_eop_link_1,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_0_port_p->ingress_ipv4_cs_error_link_1,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_0_port_p->ingress_udp_cs_error_link_1,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_0_port_p->ingress_sec_err_packet_link_1,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_0_port_p->ingress_ip_len_err_packet_link_1,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_0_port_p->ingress_trap_rule_0_link_1,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_0_port_p->ingress_trap_rule_1_link_1,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_0_port_p->ingress_trap_rule_2_link_1,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_0_port_p->ingress_trap_rule_3_link_1,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_0_port_p->ingress_last_in_chain_non_local_dst_packet_link_1,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_1_BMSK);

	return;
}

static void ecpriss_qudp_hal_reg_construct_udp_fh_sw_irq_mask_1_port_p(ecpriss_qudp_hal_reg_name_e reg,
		const void *fields,
		uint32_t *val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_mask_1_port_p_s *fh_udp_sw_irq_mask_1_port_p =
		(ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_mask_1_port_p_s *) fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_1_port_p->egress_mtu_err_packet_link_2,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_1_port_p->ingress_fcs_err_packet_link_2,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_1_port_p->ingress_pkt_fifo_empty_before_eop_link_2,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_1_port_p->ingress_ipv4_cs_error_link_2,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_1_port_p->ingress_udp_cs_error_link_2,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_UDP_CS_ERROR_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_UDP_CS_ERROR_LINK_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_1_port_p->ingress_sec_err_packet_link_2,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_1_port_p->ingress_ip_len_err_packet_link_2,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_1_port_p->ingress_trap_rule_0_link_2,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_0_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_0_LINK_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_1_port_p->ingress_trap_rule_1_link_2,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_1_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_1_LINK_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_1_port_p->ingress_trap_rule_2_link_2,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_2_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_2_LINK_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_1_port_p->ingress_trap_rule_3_link_2,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_3_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_3_LINK_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_1_port_p->ingress_last_in_chain_non_local_dst_packet_link_2,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_2_BMSK);


	//link3
	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_1_port_p->egress_mtu_err_packet_link_3,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_3_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_1_port_p->ingress_fcs_err_packet_link_3,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_3_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_1_port_p->ingress_pkt_fifo_empty_before_eop_link_3,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_3_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_1_port_p->ingress_ipv4_cs_error_link_3,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_3_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_1_port_p->ingress_udp_cs_error_link_3,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_UDP_CS_ERROR_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_UDP_CS_ERROR_LINK_3_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_1_port_p->ingress_sec_err_packet_link_3,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_3_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_1_port_p->ingress_ip_len_err_packet_link_3,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_3_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_1_port_p->ingress_trap_rule_0_link_3,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_0_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_0_LINK_3_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_1_port_p->ingress_trap_rule_1_link_3,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_1_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_1_LINK_3_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_1_port_p->ingress_trap_rule_2_link_3,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_2_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_2_LINK_3_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_1_port_p->ingress_trap_rule_3_link_3,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_3_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_TRAP_RULE_3_LINK_3_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_mask_1_port_p->ingress_last_in_chain_non_local_dst_packet_link_3,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_3_BMSK);

	return;
}


static void ecpriss_qudp_hal_reg_construct_udp_fh_sw_irq_clr_0_port_p(ecpriss_qudp_hal_reg_name_e reg,
		const void *fields,
		uint32_t *val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_clr_0_port_p_s *fh_udp_sw_irq_clr_0_port_p =
		(ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_clr_0_port_p_s *) fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_0_port_p->egress_mtu_err_packet_link_0,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_0_port_p->ingress_fcs_err_packet_link_0,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_0_port_p->ingress_pkt_fifo_empty_before_eop_link_0,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_0_port_p->ingress_ipv4_cs_error_link_0,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_0_port_p->ingress_udp_cs_error_link_0,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_0_port_p->ingress_sec_err_packet_link_0,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_0_port_p->ingress_ip_len_err_packet_link_0,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_0_port_p->ingress_trap_rule_0_link_0,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_0_port_p->ingress_trap_rule_1_link_0,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_0_port_p->ingress_trap_rule_2_link_0,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_0_port_p->ingress_trap_rule_3_link_0,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_0_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_0_port_p->ingress_last_in_chain_non_local_dst_packet_link_0,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_0_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_0_BMSK);


	//link1
	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_0_port_p->egress_mtu_err_packet_link_1,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_0_port_p->ingress_fcs_err_packet_link_1,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_0_port_p->ingress_pkt_fifo_empty_before_eop_link_1,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_0_port_p->ingress_ipv4_cs_error_link_1,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_0_port_p->ingress_udp_cs_error_link_1,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_UDP_CS_ERROR_LINK_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_0_port_p->ingress_sec_err_packet_link_1,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_0_port_p->ingress_ip_len_err_packet_link_1,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_0_port_p->ingress_trap_rule_0_link_1,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_0_LINK_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_0_port_p->ingress_trap_rule_1_link_1,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_1_LINK_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_0_port_p->ingress_trap_rule_2_link_1,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_2_LINK_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_0_port_p->ingress_trap_rule_3_link_1,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_TRAP_RULE_3_LINK_1_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_0_port_p->ingress_last_in_chain_non_local_dst_packet_link_1,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_1_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_1_BMSK);

	return;
}

static void ecpriss_qudp_hal_reg_construct_udp_fh_sw_irq_clr_1_port_p(ecpriss_qudp_hal_reg_name_e reg,
		const void *fields,
		uint32_t *val)
{
	ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_clr_1_port_p_s *fh_udp_sw_irq_clr_1_port_p =
		(ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_clr_1_port_p_s *) fields;

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_1_port_p->egress_mtu_err_packet_link_2,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_1_port_p->ingress_fcs_err_packet_link_2,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_1_port_p->ingress_pkt_fifo_empty_before_eop_link_2,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_1_port_p->ingress_ipv4_cs_error_link_2,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_1_port_p->ingress_udp_cs_error_link_2,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_UDP_CS_ERROR_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_UDP_CS_ERROR_LINK_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_1_port_p->ingress_sec_err_packet_link_2,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_1_port_p->ingress_ip_len_err_packet_link_2,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_1_port_p->ingress_trap_rule_0_link_2,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_0_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_0_LINK_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_1_port_p->ingress_trap_rule_1_link_2,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_1_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_1_LINK_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_1_port_p->ingress_trap_rule_2_link_2,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_2_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_2_LINK_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_1_port_p->ingress_trap_rule_3_link_2,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_3_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_3_LINK_2_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_1_port_p->ingress_last_in_chain_non_local_dst_packet_link_2,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_2_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_2_BMSK);


	//link3
	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_1_port_p->egress_mtu_err_packet_link_3,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_EGRESS_MTU_ERR_PACKET_LINK_3_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_1_port_p->ingress_fcs_err_packet_link_3,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_FCS_ERR_PACKET_LINK_3_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_1_port_p->ingress_pkt_fifo_empty_before_eop_link_3,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_PKT_FIFO_EMPTY_BEFORE_EOP_LINK_3_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_1_port_p->ingress_ipv4_cs_error_link_3,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_IPV4_CS_ERROR_LINK_3_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_1_port_p->ingress_udp_cs_error_link_3,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_UDP_CS_ERROR_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_UDP_CS_ERROR_LINK_3_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_1_port_p->ingress_sec_err_packet_link_3,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_SEC_ERR_PACKET_LINK_3_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_1_port_p->ingress_ip_len_err_packet_link_3,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_IP_LEN_ERR_PACKET_LINK_3_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_1_port_p->ingress_trap_rule_0_link_3,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_0_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_0_LINK_3_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_1_port_p->ingress_trap_rule_1_link_3,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_1_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_1_LINK_3_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_1_port_p->ingress_trap_rule_2_link_3,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_2_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_2_LINK_3_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_1_port_p->ingress_trap_rule_3_link_3,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_3_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_TRAP_RULE_3_LINK_3_BMSK);

	ECPRISS_HAL_SETFIELD_IN_REG(*val,
			fh_udp_sw_irq_clr_1_port_p->ingress_last_in_chain_non_local_dst_packet_link_3,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_3_SHFT,
			HWIO_ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p_INGRESS_LAST_IN_CHAIN_NON_LOCAL_DST_PACKET_LINK_3_BMSK);

	return;
}


static void ecpriss_qudp_hal_reg_parse_dummy(ecpriss_qudp_hal_reg_name_e reg,
		void *fields,
		uint32_t val)
{
	return;
}

/*
 * struct ecpriss_qudp_hal_reg_obj - Register H/W information for specific ECPRISS version
 * @construct - CB to construct register value from abstracted structure
 * @parse - CB to parse register value to abstracted structure
 * @offset - register offset relative to base address
 * @n_ofst - N parameterized register sub-offset
 * @n_start - starting n for n_registers used for printing
 * @n_end - ending n for n_registers used for printing
 * @en_print - enable this register to be printed when the device crashes
 */
struct ecpriss_qudp_hal_reg_obj {
	void (*construct)(ecpriss_qudp_hal_reg_name_e reg, const void *fields,
			uint32_t *val);
	void (*parse)(ecpriss_qudp_hal_reg_name_e reg, void *fields,
			uint32_t val);
	uint32_t base;
	uint32_t offset;
	uint32_t n_ofst;
	int n_start;
	int n_end;
	bool en_print;
	uint32_t m_ofst;
};



static struct ecpriss_qudp_hal_reg_obj ecpriss_qudp_hal_reg_objs[ECPRISS_HW_MAX][ECPRISS_QUDP_REG_MAX] = {
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_HW_PARAMS_0] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_udp_fh_params_0,
		0x09180000, 0x514, 0, 0, 0, 0, 0},

	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_HW_PARAMS_1] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_udp_fh_params_1,
		0x09180000, 0x518, 0, 0, 0, 0, 0},

	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_INGRESS_CONFIG_P] = {
		ecpriss_qudp_hal_reg_construct_udp_fh_ingress_config_p,
		ecpriss_qudp_hal_reg_parse_udp_fh_ingress_config_p,
		0x09180000, 0x0, 0, 0, 0, 0, 0},

	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_EGRESS_IPV4_FIELDS_P] = {
		ecpriss_qudp_hal_reg_construct_udp_fh_egress_ipv4_fields_p,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09180000, 0x800, 0, 0, 0, 0, 0},

	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_EGRESS_IPV6_FIELDS_P] = {
		ecpriss_qudp_hal_reg_construct_udp_fh_egress_ipv6_fields_p,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09180000, 0x80C, 0, 0, 0, 0, 0},

	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_EGRESS_ETH_MTU_P] = {
		ecpriss_qudp_hal_reg_construct_udp_fh_egress_eth_mtu_p,
		ecpriss_qudp_hal_reg_parse_udp_fh_egress_eth_mtu_p,
		0x09180000, 0x83C, 0, 0, 0, 0, 0},

	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_EGRESS_SA_TAG_ETHERTYPE_P] = {
		ecpriss_qudp_hal_reg_construct_udp_fh_egress_sa_tag_ethertype_p,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09180000, 0x818, 0, 0, 0, 0, 0},

	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_EGRESS_CONFIG_P] = {
		ecpriss_qudp_hal_reg_construct_udp_fh_egress_config_p,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09180000, 0x860, 0, 0, 0, 0, 0},

	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_P] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_udp_fh_sw_irq_status_0_port_p,
		0x09180000, 0x900, 0x4, 0, 0, 0, 0},

	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_P] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_udp_fh_sw_irq_status_1_port_p,
		0x09180000, 0x90C, 0x4, 0, 0, 0, 0},

	//Clear
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_P] = {
		ecpriss_qudp_hal_reg_construct_udp_fh_sw_irq_mask_0_port_p,
		ecpriss_qudp_hal_reg_parse_udp_fh_sw_irq_mask_0_port_p,
		0x09180000, 0x920, 0x4, 0, 0, 0, 0},

	[ECPRISS_HW_v1_0][ ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_P] = {
		ecpriss_qudp_hal_reg_construct_udp_fh_sw_irq_mask_1_port_p,
		ecpriss_qudp_hal_reg_parse_udp_fh_sw_irq_mask_1_port_p,
		0x09180000, 0x92C, 0x4, 0, 0, 0, 0},

	//Enable
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_P] = {
		ecpriss_qudp_hal_reg_construct_udp_fh_sw_irq_clr_0_port_p,
		ecpriss_qudp_hal_reg_parse_udp_fh_sw_irq_clr_0_port_p,
		0x09180000, 0x940, 0x4, 0, 0, 0, 0},

	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_P] = {
		ecpriss_qudp_hal_reg_construct_udp_fh_sw_irq_clr_1_port_p,
		ecpriss_qudp_hal_reg_parse_udp_fh_sw_irq_clr_1_port_p,
		0x09180000, 0x94C, 0x4, 0, 0, 0, 0},


	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_ECPRI_ETHERTYPE_P] = {
		ecpriss_qudp_hal_reg_construct_udp_fh_ecpri_ethertype_p,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09180000, 0x2C, 0, 0, 0, 0, 0},

	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_PTP_ETHERTYPE_P] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09180000, 0x38, 0, 0, 0, 0, 0},

	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n] = {
		ecpriss_qudp_hal_reg_construct_filt_ip_dst_addr0_port_p_entry_n,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09181000, 0x700, 0x4, 0, 0, 0, 0x40},

	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n] = {
		ecpriss_qudp_hal_reg_construct_filt_ip_dst_addr1_port_p_entry_n,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09181000, 0xA00, 0x4, 0, 0, 0, 0x40},

	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n] = {
		ecpriss_qudp_hal_reg_construct_filt_ip_dst_addr2_port_p_entry_n,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09181000,0xD00, 0x4, 0, 0, 0, 0x40},

	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n] = {
		ecpriss_qudp_hal_reg_construct_filt_ip_dst_addr3_port_p_entry_n,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09181000,0x1000, 0x4, 0, 0, 0, 0x40},

	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n] = {
		ecpriss_qudp_hal_reg_construct_filt_vlan_addr_port_port_p_entry_n,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09181000,0x0, 0x4, 0, 0, 0, 0x40},

	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n] = {
		ecpriss_qudp_hal_reg_construct_udp_fh_udp_classification_list_port_p_entry_n,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09181000, 0x300, 0x4, 0, 0, 0, 0x40},

	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS] = {
		ecpriss_qudp_hal_reg_construct_filt_udp_fh_filt_ip_dst_addr_port_p_entries_valid_bits,
		ecpriss_qudp_hal_reg_parse_filt_udp_fh_filt_ip_dst_addr_port_p_entries_valid_bits,
		0x09180000, 0x3E4, 0x4, 0, 0, 0, 0},

	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS] = {
		ecpriss_qudp_hal_reg_construct_udp_fh_filt_vlan_addr_port_p_entries_valid_bits,
		ecpriss_qudp_hal_reg_parse_udp_fh_filt_vlan_addr_port_p_entries_valid_bits,
		0x09180000, 0x3C0, 0x4, 0, 0, 0, 0},

	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS] = {
		ecpriss_qudp_hal_reg_construct_udp_classification_list_port_p_entries_valid_bits,
		ecpriss_qudp_hal_reg_parse_udp_classification_list_port_p_entries_valid_bits,
		0x09180000, 0x3CC, 0x40, 0, 0, 0, 0},
	//EGRESS port
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n] = {
		ecpriss_qudp_hal_reg_construct_fh_egress_eth_dst0_port_p_entry_n,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x1000, 0x20, 0, 0, 0, 0x2000},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n] = {
		ecpriss_qudp_hal_reg_construct_fh_egress_eth_src1_dst1_port_p_entry_n,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x1004, 0x20, 0, 0, 0, 0x2000},
	[ECPRISS_HW_v1_0][ ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n] = {
		ecpriss_qudp_hal_reg_construct_fh_egress_eth_src0_port_p_entry_n,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x1008, 0x20, 0, 0, 0, 0x2000},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n] = {
		ecpriss_qudp_hal_reg_construct_fh_egress_vlan_ethertype_port_p_entry_n,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x100C, 0x20, 0, 0, 0, 0x2000},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n] = {
		ecpriss_qudp_hal_reg_construct_fh_egress_vport_misc_port_p_entry_n,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x1010, 0x20, 0, 0, 0, 0x2000},
	[ECPRISS_HW_v1_0][ ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n] = {
		ecpriss_qudp_hal_reg_construct_fh_egress_ip_src_addr0_port_p_entry_n,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 	0x10000, 0x40, 0, 0, 0, 0x4000},
	[ECPRISS_HW_v1_0][ ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n] = {
		ecpriss_qudp_hal_reg_construct_fh_egress_ip_src_addr1_port_p_entry_n,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 	0x10004, 0x40, 0, 0, 0, 0x4000},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n] = {
		ecpriss_qudp_hal_reg_construct_fh_egress_ip_src_addr2_port_p_entry_n,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x10008, 0x40, 0, 0, 0, 0x4000},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n] = {
		ecpriss_qudp_hal_reg_construct_fh_egress_ip_src_addr3_port_p_entry_n,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x1000C, 0x40, 0, 0, 0, 0x4000},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n] = {
		ecpriss_qudp_hal_reg_construct_fh_egress_ip_dst_addr0_port_p_entry_n,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x10010, 0x40, 0, 0, 0, 0x4000},
	[ECPRISS_HW_v1_0][ ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n] = {
		ecpriss_qudp_hal_reg_construct_fh_egress_ip_dst_addr1_port_p_entry_n,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x10014, 0x40, 0, 0, 0, 0x4000},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n] = {
		ecpriss_qudp_hal_reg_construct_fh_egress_ip_dst_addr2_port_p_entry_n,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x10018, 0x40, 0, 0, 0, 0x4000},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n] = {
		ecpriss_qudp_hal_reg_construct_fh_egress_ip_dst_addr3_port_p_entry_n,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x1001C, 0x40, 0, 0, 0, 0x4000},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n] = {
		ecpriss_qudp_hal_reg_construct_fh_egress_udp_ports_port_p_entry_n,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x10020, 0x40, 0, 0, 0, 0x4000},
	[ECPRISS_HW_v1_0][ ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n] = {
		ecpriss_qudp_hal_reg_construct_fh_egress_sa_tag_ip_tos_misc_port_p_entry_n,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x10024, 0x40, 0, 0, 0, 0x4000},
	//FH Stats
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_INGRESS_NUM_UDP_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x0, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_INGRESS_NUM_UDP_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x4, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_INGRESS_NUM_NON_UDP_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x8, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_INGRESS_NUM_NON_UDP_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0xC, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_INGRESS_FCS_ERR_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x10, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_INGRESS_FCS_ERR_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x14, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_INGRESS_IPV4_CS_ERROR_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x18, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_INGRESS_IPV4_CS_ERROR_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x1C, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_INGRESS_UDP_CS_ERROR_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x20, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_INGRESS_UDP_CS_ERROR_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x24, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_INGRESS_IP_FILTERED_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x28, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_INGRESS_IP_FILTERED_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x2C, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_INGRESS_VLAN_FILTERED_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x30, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_INGRESS_VLAN_FILTERED_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x34, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_INGRESS_SEC_ERR_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x38, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_INGRESS_SEC_ERR_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x3C, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_INGRESS_IP_LEN_ERR_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x40, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_INGRESS_IP_LEN_ERR_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x44, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_EGRESS_NUM_UDP_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x48, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_EGRESS_NUM_UDP_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x4C, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_EGRESS_NUM_ETH_ONLY_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x50, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_EGRESS_NUM_ETH_ONLY_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x54, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_EGRESS_NUM_BYPASSED_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x58, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_EGRESS_NUM_BYPASSED_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x5C, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_EGRESS_MTU_ERR_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x60, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_FH_EGRESS_MTU_ERR_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x09184000, 0x64, 0x80, 0, 0, 0, 0x200},

	//l2 stat
	[ECPRISS_HW_v1_0][ECPRI_UDP_L2_INGRESS_NUM_UDP_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x91E4000 , 0x0, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_L2_INGRESS_NUM_UDP_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x91E4000 , 0x4, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_L2_INGRESS_NUM_NON_UDP_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x91E4000 , 0x8, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_L2_INGRESS_NUM_NON_UDP_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x91E4000 , 0xC, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_L2_INGRESS_FCS_ERR_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x91E4000 , 0x10, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_L2_INGRESS_FCS_ERR_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x91E4000 , 0x14, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_L2_INGRESS_IPV4_CS_ERROR_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x91E4000 , 0x18, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_L2_INGRESS_IPV4_CS_ERROR_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x91E4000 , 0x1C, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_L2_INGRESS_UDP_CS_ERROR_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x91E4000 , 0x20, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_L2_INGRESS_UDP_CS_ERROR_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x91E4000 , 0x24, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_L2_INGRESS_IP_FILTERED_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x91E4000 , 0x28, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_L2_INGRESS_IP_FILTERED_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x91E4000 , 0x2C, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_L2_INGRESS_VLAN_FILTERED_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x91E4000 , 0x30, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_L2_INGRESS_VLAN_FILTERED_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x91E4000 , 0x34, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_L2_INGRESS_SEC_ERR_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x91E4000 , 0x38, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_L2_INGRESS_SEC_ERR_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x91E4000 , 0x3C, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_L2_INGRESS_IP_LEN_ERR_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x91E4000 , 0x40, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_L2_INGRESS_IP_LEN_ERR_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x91E4000 , 0x44, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_L2_EGRESS_NUM_UDP_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x91E4000 , 0x48, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_L2_EGRESS_NUM_UDP_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x91E4000 , 0x4C, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_L2_EGRESS_NUM_ETH_ONLY_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x91E4000 , 0x50, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_L2_EGRESS_NUM_ETH_ONLY_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x91E4000 , 0x54, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_L2_EGRESS_NUM_BYPASSED_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x91E4000 , 0x58, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_L2_EGRESS_NUM_BYPASSED_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x91E4000 , 0x5C, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_L2_EGRESS_MTU_ERR_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x91E4000 , 0x60, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_L2_EGRESS_MTU_ERR_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x91E4000 , 0x64, 0x80, 0, 0, 0, 0x200},

	//C2C stats

	[ECPRISS_HW_v1_0][ECPRI_UDP_C2C_INGRESS_NUM_UDP_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x091B4000, 0x0, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_C2C_INGRESS_NUM_UDP_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x091B4000, 0x4, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_C2C_INGRESS_NUM_NON_UDP_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x091B4000, 0x8, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_C2C_INGRESS_NUM_NON_UDP_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x091B4000, 0xC, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_C2C_INGRESS_FCS_ERR_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x091B4000, 0x10, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_C2C_INGRESS_FCS_ERR_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x091B4000, 0x14, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_C2C_INGRESS_IPV4_CS_ERROR_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x091B4000, 0x18, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_C2C_INGRESS_IPV4_CS_ERROR_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x091B4000, 0x1C, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_C2C_INGRESS_UDP_CS_ERROR_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x091B4000, 0x20, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_C2C_INGRESS_UDP_CS_ERROR_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x091B4000, 0x24, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_C2C_INGRESS_IP_FILTERED_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x091B4000, 0x28, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_C2C_INGRESS_IP_FILTERED_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x091B4000, 0x2C, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_C2C_INGRESS_VLAN_FILTERED_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x091B4000, 0x30, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_C2C_INGRESS_VLAN_FILTERED_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x091B4000, 0x34, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_C2C_INGRESS_SEC_ERR_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x091B4000, 0x38, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_C2C_INGRESS_SEC_ERR_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x091B4000, 0x3C, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_C2C_INGRESS_IP_LEN_ERR_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x091B4000, 0x40, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_C2C_INGRESS_IP_LEN_ERR_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x091B4000, 0x44, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_C2C_EGRESS_NUM_UDP_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x091B4000, 0x48, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_C2C_EGRESS_NUM_UDP_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x091B4000, 0x4C, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_C2C_EGRESS_NUM_ETH_ONLY_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x091B4000, 0x50, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_C2C_EGRESS_NUM_ETH_ONLY_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x091B4000, 0x54, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_C2C_EGRESS_NUM_BYPASSED_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x091B4000, 0x58, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_C2C_EGRESS_NUM_BYPASSED_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x091B4000, 0x5C, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_C2C_EGRESS_MTU_ERR_PACKETS_LSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x091B4000, 0x60, 0x80, 0, 0, 0, 0x200},
	[ECPRISS_HW_v1_0][ECPRI_UDP_C2C_EGRESS_MTU_ERR_PACKETS_MSB_PORT_p_LINK_n] = {
		ecpriss_qudp_hal_reg_construct_dummy,
		ecpriss_qudp_hal_reg_parse_dummy,
		0x091B4000, 0x64, 0x80, 0, 0, 0, 0x200}
};


/*
 * ecpriss_qudp_hal_reg_name_e_str() - returns string that represent the register
 * @reg_name: [in] register name
 */
const char *ecpriss_qudp_hal_reg_name_str(ecpriss_qudp_hal_reg_name_e reg_name)
{
	if (reg_name < 0 || reg_name >= ECPRISS_QUDP_REG_MAX) {
		pr_err("requested name of invalid reg=%d\n", reg_name);
		return "Invalid Register";
	}
	return ecpriss_qudp_hal_reg_name_to_str[reg_name];
}




int ecpriss_qudp_global_hal_reg_init(struct device *dev)
{
	int result = 0;
	/* setup ECPRISS register access */

	do
	{
		ecpriss_qudp_hal_ctx.hw_type = ECPRISS_HW_v1_0;
		ecpriss_qudp_hal_ctx.ecpriss_dev = dev;
		ecpriss_qudp_hal_ctx.qudp_global_phy_base = ECPRISS_QUDP_GLOBAL_REG_BASE;

		pr_err("Mapping  QUDP global HAL reg space : 0x%x\n", ecpriss_qudp_hal_ctx.qudp_global_phy_base);
		ecpriss_qudp_hal_ctx.global_base = ioremap(ecpriss_qudp_hal_ctx.qudp_global_phy_base,
				ECPRISS_QUDP_GLOBAL_REG_SIZE);
		if (!ecpriss_qudp_hal_ctx.global_base) {
			pr_err(":ecpriss_global_base ioremap err\n");
			result = -EFAULT;
			break;
		}
	}while(0);

	return result;
}


int ecpriss_qudp_fh_hal_reg_init(struct device *dev)
{
	int result = 0;
	/* setup ECPRISS register access */
	do
	{
		ecpriss_qudp_hal_ctx.qudp_fh_phy_base = ECPRISS_FH_QUDP_REG_BASE;

		ecpriss_qudp_hal_ctx.fh_base = ioremap(ecpriss_qudp_hal_ctx.qudp_fh_phy_base,
				ECPRISS_QUDP_FH_REG_SIZE);
		if (!ecpriss_qudp_hal_ctx.fh_base) {
			pr_err(":ecpriss_qudp_fh_base ioremap err\n");
			result = -EFAULT;
			break;
		}


		ecpriss_qudp_hal_ctx.qudp_fh_phy_filter_base = ECPRISS_FH_QUDP_FILTER_REG_BASE;


		ecpriss_qudp_hal_ctx.fh_filter_base = ioremap(ecpriss_qudp_hal_ctx.qudp_fh_phy_filter_base,
				ECPRISS_QUDP_FH_FILTER_REG_SIZE);
		if (!ecpriss_qudp_hal_ctx.fh_filter_base) {
			pr_err(":ecpriss_qudp_fh_base filter ioremap err\n");
			result = -EFAULT;
			break;
		}


		ecpriss_qudp_hal_ctx.qudp_fh_phy_rams_base = ECPRISS_FH_QUDP_RAMS_REG_BASE;

		ecpriss_qudp_hal_ctx.fh_rams_base = ioremap(ecpriss_qudp_hal_ctx.qudp_fh_phy_rams_base,
				ECPRISS_QUDP_FH_RAMS_REG_SIZE);
		if (!ecpriss_qudp_hal_ctx.qudp_fh_phy_rams_base) {
			pr_err(":ecpriss_qudp_fh_base filter ioremap err\n");
			result = -EFAULT;
			break;
		}


	}while(0);

	return result;
}



int ecpriss_qudp_c2c_hal_reg_init(struct device *dev)
{
	int result = 0;
	/* setup ECPRISS register access */
	do
	{
		ecpriss_qudp_hal_ctx.qudp_c2c_phy_base = ECPRISS_C2C_QUDP_REG_BASE;

		ecpriss_qudp_hal_ctx.c2c_base = ioremap(ecpriss_qudp_hal_ctx.qudp_c2c_phy_base,
				ECPRISS_QUDP_C2C_REG_SIZE);
		if (!ecpriss_qudp_hal_ctx.c2c_base) {
			pr_err(":ecpriss_xbar_base ioremap err\n");
			result = -EFAULT;
			break;
		}
	}while(0);

	return result;
}



int ecpriss_qudp_l2_hal_reg_init(struct device *dev)
{
	int result = 0;
	/* setup ECPRISS register access */
	do
	{
		ecpriss_qudp_hal_ctx.qudp_l2_phy_base = ECPRISS_QUDP_L2_REG_BASE;

		pr_debug("Mapping  XBAR HAL reg space : 0x%x\n", ecpriss_qudp_hal_ctx.qudp_l2_phy_base);
		ecpriss_qudp_hal_ctx.l2_base = ioremap(ecpriss_qudp_hal_ctx.qudp_l2_phy_base,
				ECPRISS_QUDP_L2_REG_SIZE);
		if (!ecpriss_qudp_hal_ctx.l2_base) {
			pr_err(":ecpriss_xbar_base ioremap err\n");
			result = -EFAULT;
			break;
		}
	}while(0);

	return result;
}

void ecpriss_qudp_reg_write(ecpriss_qudp_hal_reg_type_e  reg_type,
		uint32_t offset,
		uint32_t val)
{
	if(reg_type == ECPRISS_QUDP_GLOBAL) {

		iowrite32(val, ecpriss_qudp_hal_ctx.global_base + offset);
	}
	else if(reg_type == ECPRISS_QUDP_FH) {

		iowrite32(val, ecpriss_qudp_hal_ctx.fh_base + offset);
	}
	else if(reg_type == ECPRISS_QUDP_FH_FILTER) {

		iowrite32(val, ecpriss_qudp_hal_ctx.fh_filter_base + offset);
	}
	else if(reg_type == ECPRISS_QUDP_FH_RAMS) {

		iowrite32(val, ecpriss_qudp_hal_ctx.fh_rams_base + offset);
	}
	else if(reg_type == ECPRISS_QUDP_C2C) {
		iowrite32(val, ecpriss_qudp_hal_ctx.c2c_base + offset);
	}
	else if(reg_type == ECPRISS_QUDP_L2) {
		iowrite32(val, ecpriss_qudp_hal_ctx.l2_base + offset);
	}
	return;
}


uint32_t ecpriss_qudp_reg_read(ecpriss_qudp_hal_reg_type_e  reg_type,
		uint32_t offset)
{
	uint32_t val = 0;
	if(reg_type == ECPRISS_QUDP_GLOBAL) {
		val = ioread32(ecpriss_qudp_hal_ctx.global_base + offset);
	}
	else if(reg_type == ECPRISS_QUDP_FH) {
		val = ioread32(ecpriss_qudp_hal_ctx.fh_base + offset);
	}
	else if(reg_type == ECPRISS_QUDP_C2C) {
		val = ioread32(ecpriss_qudp_hal_ctx.c2c_base + offset);
	}
	else if(reg_type == ECPRISS_QUDP_L2) {
		val = ioread32(ecpriss_qudp_hal_ctx.l2_base + offset);
	}
	return val;
}


/*
 * ecpriss_qudp_hal_read_reg_n() - Get n parameterized reg value
 */
uint32_t ecpriss_qudp_hal_read_reg_n(ecpriss_qudp_hal_reg_type_e  reg_type,
		ecpriss_qudp_hal_reg_name_e reg,
		uint32_t n)
{
	uint32_t offset;

	if (reg >= ECPRISS_QUDP_REG_MAX) {
		pr_err("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return -EINVAL;
	}

	pr_info("read from %s n=%u\n",
			ecpriss_qudp_hal_reg_name_str(reg), n);

	offset = ecpriss_qudp_hal_reg_objs[ecpriss_qudp_hal_ctx.hw_type][reg].offset;
	if (offset == -1) {
		pr_err("Read access to obsolete reg=%s\n",
				ecpriss_qudp_hal_reg_name_str(reg));
		WARN_ON(1);
		return -EPERM;
	}
	offset += ecpriss_qudp_hal_reg_objs[ecpriss_qudp_hal_ctx.hw_type][reg].n_ofst * n;
	return ecpriss_qudp_reg_read(reg_type,offset);
}



/*
 * ecpriss_qudp_hal_read_reg_mn() - Get mn parameterized reg value
 */
uint32_t ecpriss_qudp_hal_read_reg_mn(ecpriss_qudp_hal_reg_type_e  reg_type,
		ecpriss_qudp_hal_reg_name_e reg,
		uint32_t m,
		uint32_t n)
{
	uint32_t offset;

	if (reg >= ECPRISS_QUDP_REG_MAX) {
		pr_err("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return -EINVAL;
	}

	pr_info("read %s m=%u n=%u\n",
			ecpriss_qudp_hal_reg_name_str(reg), m, n);
	offset = ecpriss_qudp_hal_reg_objs[ecpriss_qudp_hal_ctx.hw_type][reg].offset;
	if (offset == -1) {
		pr_err("Read access to obsolete reg=%s\n",
				ecpriss_qudp_hal_reg_name_str(reg));
		WARN_ON_ONCE(1);
		return -EPERM;
	}

	offset += ecpriss_qudp_hal_reg_objs[ecpriss_qudp_hal_ctx.hw_type][reg].m_ofst * m;
	offset += ecpriss_qudp_hal_reg_objs[ecpriss_qudp_hal_ctx.hw_type][reg].n_ofst * n;
	return ecpriss_qudp_reg_read(reg_type,offset);
}



/*
 * ecpriss_qudp_hal_write_reg_mn() - Write to m/n parameterized reg a raw value
 */
void ecpriss_qudp_hal_write_reg_mn(ecpriss_qudp_hal_reg_type_e  reg_type,
		ecpriss_qudp_hal_reg_name_e reg,
		uint32_t m,
		uint32_t n,
		uint32_t val)
{
	uint32_t offset;

	if (reg >= ECPRISS_QUDP_REG_MAX) {
		pr_err("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return;
	}

	pr_info("write to %s m=%u n=%u val=%u\n",
			ecpriss_qudp_hal_reg_name_str(reg), m, n, val);
	offset = ecpriss_qudp_hal_reg_objs[ecpriss_qudp_hal_ctx.hw_type][reg].offset;




	if (offset == -1) {
		pr_err("Write access to obsolete reg=%s\n",
				ecpriss_qudp_hal_reg_name_str(reg));
		WARN_ON(1);
		return;
	}

	offset += ecpriss_qudp_hal_reg_objs[ecpriss_qudp_hal_ctx.hw_type][reg].m_ofst * m;
	offset += ecpriss_qudp_hal_reg_objs[ecpriss_qudp_hal_ctx.hw_type][reg].n_ofst * n;
	ecpriss_qudp_reg_write(reg_type,offset,val);
	return;
}


/*
 * ecpriss_qudp_hal_write_reg_mn() - Write to m/n parameterized reg a raw value
 */
void ecpriss_qudp_hal_write_reg_mn_fields(ecpriss_qudp_hal_reg_type_e  reg_type,
		ecpriss_qudp_hal_reg_name_e reg,
		uint32_t m,
		uint32_t n,
		void *fields)
{
	uint32_t val = 0;
	uint32_t offset;

	if (reg >= ECPRISS_QUDP_REG_MAX) {
		pr_err("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return;
	}

	pr_info("write to %s m=%u n=%u val=%u\n",
			ecpriss_qudp_hal_reg_name_str(reg), m, n, val);
	offset = ecpriss_qudp_hal_reg_objs[ecpriss_qudp_hal_ctx.hw_type][reg].offset;

	if (offset == -1) {
		pr_err("Write access to obsolete reg=%s\n",
				ecpriss_qudp_hal_reg_name_str(reg));
		WARN_ON(1);
		return;
	}

	offset += ecpriss_qudp_hal_reg_objs[ecpriss_qudp_hal_ctx.hw_type][reg].m_ofst * m;

	offset += ecpriss_qudp_hal_reg_objs[ecpriss_qudp_hal_ctx.hw_type][reg].n_ofst * n;

	ecpriss_qudp_hal_reg_objs[ecpriss_qudp_hal_ctx.hw_type][reg].construct(reg, fields, &val);
	ecpriss_qudp_reg_write(reg_type,offset,val);
	return;
}

uint32_t ecpriss_qudp_hal_read_reg_mn_fields(ecpriss_qudp_hal_reg_type_e  reg_type,
		ecpriss_qudp_hal_reg_name_e reg,
		uint32_t m,
		uint32_t n,
		void *fields)
{
	uint32_t val = 0;
	uint32_t offset;

	if (!fields) {
		pr_err("Input error fields\n");
		WARN_ON(1);
		return -EINVAL;
	}

	if (reg >= ECPRISS_QUDP_REG_MAX) {
		pr_err("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return -EINVAL;
	}

	pr_info("read from %s n=%u and parse it\n",
			ecpriss_qudp_hal_reg_name_str(reg), n);
	offset = ecpriss_qudp_hal_reg_objs[ecpriss_qudp_hal_ctx.hw_type][reg].offset;
	if (offset == -1) {
		pr_err("Read access to obsolete reg=%s\n",
				ecpriss_qudp_hal_reg_name_str(reg));
		WARN_ON(1);
		return -EPERM;
	}
	offset += ecpriss_qudp_hal_reg_objs[ecpriss_qudp_hal_ctx.hw_type][reg].m_ofst * m;
	offset += ecpriss_qudp_hal_reg_objs[ecpriss_qudp_hal_ctx.hw_type][reg].n_ofst * n;
	val = ecpriss_qudp_reg_read(reg_type,offset);
	ecpriss_qudp_hal_reg_objs[ecpriss_qudp_hal_ctx.hw_type][reg].parse(reg, fields, val);
	return val;
}


/*
 * ecpriss_qudp_hal_read_reg_n_fields() - Get the parsed value of n parameterized reg
 */
uint32_t ecpriss_qudp_hal_read_reg_n_fields(ecpriss_qudp_hal_reg_type_e  reg_type,
		ecpriss_qudp_hal_reg_name_e reg,
		uint32_t n,
		void *fields)
{
	uint32_t val = 0;
	uint32_t offset;

	if (!fields) {
		pr_err("Input error fields\n");
		WARN_ON(1);
		return -EINVAL;
	}

	if (reg >= ECPRISS_QUDP_REG_MAX) {
		pr_err("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return -EINVAL;
	}

	pr_info("read from %s \n", ecpriss_qudp_hal_reg_name_str(reg), n);
	offset = ecpriss_qudp_hal_reg_objs[ecpriss_qudp_hal_ctx.hw_type][reg].offset;
	if (offset == -1) {
		pr_err("Read access to obsolete reg=%s\n",
				ecpriss_qudp_hal_reg_name_str(reg));
		WARN_ON(1);
		return -EPERM;
	}
	offset += ecpriss_qudp_hal_reg_objs[ecpriss_qudp_hal_ctx.hw_type][reg].n_ofst * n;
	val = ecpriss_qudp_reg_read(reg_type,offset);
	ecpriss_qudp_hal_reg_objs[ecpriss_qudp_hal_ctx.hw_type][reg].parse(reg, fields, val);

	return val;
}




/*
 * ecpriss_qudp_hal_write_reg_n_fields() - Write to n parameterized reg a prased value
 */
void ecpriss_qudp_hal_write_reg_n_fields(ecpriss_qudp_hal_reg_type_e  reg_type,
		ecpriss_qudp_hal_reg_name_e reg,
		uint32_t n,
		const void *fields)
{
	uint32_t val = 0;
	uint32_t offset;

	if (!fields) {
		pr_err("Input error fields=%pK\n", fields);
		WARN_ON(1);
		return;
	}

	if (reg >= ECPRISS_QUDP_REG_MAX) {
		pr_err("Invalid register reg=%u\n", reg);
		WARN_ON(1);
		return;
	}

	//pr_info("write to %s \n",ecpriss_qudp_hal_reg_name_str(reg), n);
	offset = ecpriss_qudp_hal_reg_objs[ecpriss_qudp_hal_ctx.hw_type][reg].offset;
	if (offset == -1) {
		pr_err("Write access to obsolete reg=%s\n",
				ecpriss_qudp_hal_reg_name_str(reg));
		WARN_ON(1);
		return;
	}


	offset += ecpriss_qudp_hal_reg_objs[ecpriss_qudp_hal_ctx.hw_type][reg].n_ofst * n;
	ecpriss_qudp_hal_reg_objs[ecpriss_qudp_hal_ctx.hw_type][reg].construct(reg, fields, &val);


	ecpriss_qudp_reg_write(reg_type,offset,val);
	return;
}
