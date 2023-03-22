 /* SPDX-License-Identifier: GPL-2.0-only
  *  Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
  */

#ifndef __ECPRI_QUDP_HWIO_DEF_V2_H__
#define __ECPRI_QUDP_HWIO_DEF_V2_H__
/*
===========================================================================
*/
/**
  @file ecpri_qudp_hwio.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
    ECPRI_UDP.*

  /Include' filters applied: <none>
  'Exclude' filters applied: RESERVED DUMMY
*/
/*
  ===========================================================================

  $Header: $
  $DateTime: $
  $Author: $

  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_UDP_FH_UDP_FH_REGS
 *--------------------------------------------------------------------------*/

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_INGRESS_CONFIG_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t enable_ip_dst_filt : 1;
  uint32_t enable_udp_dst_class : 1;
  uint32_t enable_vlan_filt : 1;
  uint32_t enable_udp_cs_check : 1;
  uint32_t enable_ip_len_check : 1;
  uint32_t ipv4_cs_err_action : 2;
  uint32_t udp_cs_err_action : 2;
  uint32_t fcs_err_action : 2;
  uint32_t pkt_err_action : 2;
  uint32_t ip_len_err_action : 2;
  uint32_t disable_st_and_fw : 1;
  uint32_t vlan_filt_miss_action : 2;
  uint32_t ip_filt_miss_action : 2;
  uint32_t enable_mac_dst_check : 1;
  uint32_t use_external_not_local_mac_dst : 1;
  uint32_t enable_broadcast_check : 1;
  uint32_t last_in_chain : 1;
  uint32_t non_local_dst_action : 3;
  uint32_t enable_shared_filtering_2_links : 1;
  uint32_t enable_shared_filtering_4_links : 1;
  uint32_t enable_eth_padding_removal : 1;
  uint32_t reserved0 : 2;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_config_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_config_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_config_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_WORDS_BEFORE_TRANSMITTING_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 8;
  uint32_t reserved0 : 24;
} ecpri_qudp_hwio_def_ecpri_udp_fh_words_before_transmitting_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_words_before_transmitting_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_words_before_transmitting_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_UDP_PTP_PORT_NUM_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 16;
  uint32_t reserved0 : 16;
} ecpri_qudp_hwio_def_ecpri_udp_fh_udp_ptp_port_num_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_udp_ptp_port_num_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_udp_ptp_port_num_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_ECPRI_ETHERTYPE_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 16;
  uint32_t reserved0 : 16;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ecpri_ethertype_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_ecpri_ethertype_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ecpri_ethertype_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_PTP_ETHERTYPE_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 16;
  uint32_t reserved0 : 16;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ptp_ethertype_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_ptp_ethertype_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ptp_ethertype_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_FILT_ERROR_CHANNEL_CFG_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t send_vlan_filt_miss_to_error_channel : 1;
  uint32_t send_ip_filt_miss_to_error_channel : 1;
  uint32_t reserved0 : 30;
} ecpri_qudp_hwio_def_ecpri_udp_fh_filt_error_channel_cfg_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_filt_error_channel_cfg_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_filt_error_channel_cfg_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_TRAP_MISC_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t rule64_offset : 8;
  uint32_t rule32_offset : 8;
  uint32_t action : 3;
  uint32_t enable : 1;
  uint32_t reserved0 : 12;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_misc_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_trap_misc_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_misc_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_rule64_val_lsb_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_trap_rule64_val_lsb_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_rule64_val_lsb_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_rule64_val_msb_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_trap_rule64_val_msb_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_rule64_val_msb_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_rule64_mask_lsb_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_trap_rule64_mask_lsb_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_rule64_mask_lsb_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_rule64_mask_msb_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_trap_rule64_mask_msb_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_rule64_mask_msb_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_TRAP_RULE32_VAL_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_rule32_val_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_trap_rule32_val_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_rule32_val_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_TRAP_RULE32_MASK_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_rule32_mask_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_trap_rule32_mask_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_rule32_mask_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t large_set_rule128_offset : 8;
  uint32_t large_set_rule32_offset : 8;
  uint32_t reserved0 : 16;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_offsets_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_offsets_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_offsets_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule32_val_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule32_val_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule32_val_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule32_mask_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule32_mask_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule32_mask_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule128_0_val_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule128_0_val_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule128_0_val_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule128_0_mask_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule128_0_mask_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule128_0_mask_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule128_1_val_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule128_1_val_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule128_1_val_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule128_1_mask_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule128_1_mask_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule128_1_mask_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule128_2_val_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule128_2_val_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule128_2_val_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule128_2_mask_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule128_2_mask_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule128_2_mask_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule128_3_val_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule128_3_val_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule128_3_val_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule128_3_mask_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule128_3_mask_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_large_set_rule128_3_mask_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_TRAP_PTP_CFG_PORT_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t trap_ptp_over_eth_without_vlan_en : 1;
  uint32_t trap_ptp_over_eth_with_vlan_en : 1;
  uint32_t trap_ptp_over_ipv4_without_vlan_en : 1;
  uint32_t trap_ptp_over_ipv4_with_vlan_en : 1;
  uint32_t trap_ptp_over_ipv6_without_vlan_en : 1;
  uint32_t trap_ptp_over_ipv6_with_vlan_en : 1;
  uint32_t reserved0 : 26;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_ptp_cfg_port_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_trap_ptp_cfg_port_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_trap_ptp_cfg_port_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t valid_bits : 16;
  uint32_t reserved0 : 16;
} ecpri_qudp_hwio_def_ecpri_udp_fh_filt_vlan_addr_port_p_entries_valid_bits_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_filt_vlan_addr_port_p_entries_valid_bits_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_filt_vlan_addr_port_p_entries_valid_bits_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t valid_bits : 16;
  uint32_t reserved0 : 16;
} ecpri_qudp_hwio_def_ecpri_udp_fh_udp_classification_list_port_p_entries_valid_bits_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_udp_classification_list_port_p_entries_valid_bits_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_udp_classification_list_port_p_entries_valid_bits_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t valid_bits : 16;
  uint32_t reserved0 : 16;
} ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr_port_p_entries_valid_bits_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr_port_p_entries_valid_bits_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr_port_p_entries_valid_bits_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t valid_bits : 20;
  uint32_t reserved0 : 12;
} ecpri_qudp_hwio_def_ecpri_udp_fh_filt_mac_address_port_p_entries_valid_bits_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_filt_mac_address_port_p_entries_valid_bits_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_filt_mac_address_port_p_entries_valid_bits_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t gsi_id : 2;
  uint32_t ring_id : 8;
  uint32_t reserved0 : 22;
} ecpri_qudp_hwio_def_ecpri_udp_fh_non_ecpri_dma_ring_info_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_non_ecpri_dma_ring_info_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_non_ecpri_dma_ring_info_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_IDLE_STATUS_PORT_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t port_is_idle : 1;
  uint32_t ingress_idle : 1;
  uint32_t ingress_aligner_idle : 1;
  uint32_t ingress_pkt_fifo_empty_link_0 : 1;
  uint32_t ingress_cmd_fifo_empty_link_0 : 1;
  uint32_t egress_idle : 1;
  uint32_t egress_hdri_idle : 1;
  uint32_t egress_pkt_fifo_empty : 1;
  uint32_t egress_aligner_idle : 1;
  uint32_t egress_output_fifo_empty : 1;
  uint32_t egress_cs_fifo_empty : 1;
  uint32_t ingress_arbiter_idle : 1;
  uint32_t ingress_pkt_fifo_empty_link_1 : 1;
  uint32_t ingress_pkt_fifo_empty_link_2 : 1;
  uint32_t ingress_pkt_fifo_empty_link_3 : 1;
  uint32_t ingress_cmd_fifo_empty_link_1 : 1;
  uint32_t ingress_cmd_fifo_empty_link_2 : 1;
  uint32_t ingress_cmd_fifo_empty_link_3 : 1;
  uint32_t reserved0 : 14;
} ecpri_qudp_hwio_def_ecpri_udp_fh_idle_status_port_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_idle_status_port_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_idle_status_port_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_CGC_CFG
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t ingress_cgc_open : 1;
  uint32_t egress_cgc_open : 1;
  uint32_t reserved0 : 30;
} ecpri_qudp_hwio_def_ecpri_udp_fh_cgc_cfg_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_cgc_cfg_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_cgc_cfg_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_HW_PARAMS_0
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t instance_type : 2;
  uint32_t ports_n : 2;
  uint32_t links_n : 3;
  uint32_t eth_table_entries_n : 9;
  uint32_t ip_table_entries_n : 9;
  uint32_t udp_classification_entries_n : 6;
  uint32_t l3_support : 1;
} ecpri_qudp_hwio_def_ecpri_udp_fh_hw_params_0_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_hw_params_0_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_hw_params_0_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_HW_PARAMS_1
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t vlan_filt_entries_n : 5;
  uint32_t ip_filt_entries_n : 5;
  uint32_t eth_dst_filt_entries_n : 5;
  uint32_t reserved0 : 17;
} ecpri_qudp_hwio_def_ecpri_udp_fh_hw_params_1_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_hw_params_1_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_hw_params_1_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_QUDP_STAT_COUNTERS_CTL
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t cnt_en : 1;
  uint32_t cnt_clr_en : 1;
  uint32_t reserved0 : 30;
} ecpri_qudp_hwio_def_ecpri_udp_fh_qudp_stat_counters_ctl_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_qudp_stat_counters_ctl_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_qudp_stat_counters_ctl_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_QUDP_CTL_PORT_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t sres : 1;
  uint32_t sleep_mode : 1;
  uint32_t disable_irq_delay : 1;
  uint32_t reserved0 : 29;
} ecpri_qudp_hwio_def_ecpri_udp_fh_qudp_ctl_port_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_qudp_ctl_port_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_qudp_ctl_port_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_INGRESS_UDP_WATERMARK_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t pkt_fifo : 10;
  uint32_t pkt_handler_sync_fifos : 3;
  uint32_t ptp_timestamp_fifo : 3;
  uint32_t cmd_fifo : 10;
  uint32_t reserved0 : 6;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_udp_watermark_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_udp_watermark_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_udp_watermark_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_0_PORT_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t pkt_fifo : 10;
  uint32_t hdri_cfg_index_fifo : 9;
  uint32_t hdri_output_fifo : 3;
  uint32_t aligner_output_fifo : 3;
  uint32_t reserved0 : 7;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_udp_watermark_0_port_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_udp_watermark_0_port_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_udp_watermark_0_port_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_DEBUG_FEATURES_CFG
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t tpdm_en : 1;
  uint32_t tpdm_operation_mode : 1;
  uint32_t watermark_en : 1;
  uint32_t en_clear_watermark_on_read : 1;
  uint32_t testbus_en : 1;
  uint32_t hw_events_en : 1;
  uint32_t reserved0 : 26;
} ecpri_qudp_hwio_def_ecpri_udp_fh_debug_features_cfg_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_debug_features_cfg_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_debug_features_cfg_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_TPDM_DATA_CFG
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t port_index_sel : 2;
  uint32_t link_index_sel : 2;
  uint32_t bus_sel : 3;
  uint32_t sideband_insertion_en : 1;
  uint32_t sideband_insertion_mode : 2;
  uint32_t sideband_insertion_offset : 3;
  uint32_t sampling_mode : 2;
  uint32_t reserved0 : 2;
  uint32_t max_words_to_send_per_packet : 9;
  uint32_t sample_only_trapped_packets : 1;
  uint32_t reserved1 : 5;
} ecpri_qudp_hwio_def_ecpri_udp_fh_tpdm_data_cfg_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_tpdm_data_cfg_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_tpdm_data_cfg_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_TPDM_CONTROL_CFG_0
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t port_index_sel : 2;
  uint32_t link_index_sel : 2;
  uint32_t bus_sel : 3;
  uint32_t arbitrary_testbus_0_sel : 7;
  uint32_t arbitrary_testbus_1_sel : 7;
  uint32_t arbitrary_testbus_2_sel : 7;
  uint32_t reserved0 : 4;
} ecpri_qudp_hwio_def_ecpri_udp_fh_tpdm_control_cfg_0_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_tpdm_control_cfg_0_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_tpdm_control_cfg_0_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_TPDM_CONTROL_CFG_1
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t arbitrary_testbus_3_sel : 7;
  uint32_t arbitrary_testbus_4_sel : 7;
  uint32_t arbitrary_testbus_5_sel : 7;
  uint32_t arbitrary_testbus_6_sel : 7;
  uint32_t reserved0 : 4;
} ecpri_qudp_hwio_def_ecpri_udp_fh_tpdm_control_cfg_1_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_tpdm_control_cfg_1_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_tpdm_control_cfg_1_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_TPDM_CONTROL_MASK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t mask_bits : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_tpdm_control_mask_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_tpdm_control_mask_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_tpdm_control_mask_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_TESTBUS_SEL_CFG
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t port_index_sel : 2;
  uint32_t link_index_sel : 2;
  uint32_t testbus_sel : 7;
  uint32_t reserved0 : 21;
} ecpri_qudp_hwio_def_ecpri_udp_fh_testbus_sel_cfg_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_testbus_sel_cfg_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_testbus_sel_cfg_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_TESTBUS
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t data : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_testbus_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_testbus_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_testbus_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_ERROR_SYNDROME_MISC_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t clr : 1;
  uint32_t en : 1;
  uint32_t num_valid_bytes : 7;
  uint32_t link_id : 2;
  uint32_t erro_info : 8;
  uint32_t reserved0 : 13;
} ecpri_qudp_hwio_def_ecpri_udp_fh_error_syndrome_misc_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_error_syndrome_misc_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_error_syndrome_misc_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_ERROR_SYNDROME_REG_PORT_p_ENRTY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_error_syndrome_reg_port_p_enrty_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_error_syndrome_reg_port_p_enrty_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_error_syndrome_reg_port_p_enrty_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_UDP_WATERMARK_1_PORT_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t cs_calc_fifo : 9;
  uint32_t cs_update_fifo : 2;
  uint32_t reserved0 : 21;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_udp_watermark_1_port_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_udp_watermark_1_port_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_udp_watermark_1_port_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_IPV4_FIELDS_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t id : 16;
  uint32_t ttl : 8;
  uint32_t reserved0 : 8;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ipv4_fields_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ipv4_fields_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ipv4_fields_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_IPV6_FIELDS_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t hop_limit : 8;
  uint32_t flow_label : 20;
  uint32_t reserved0 : 4;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ipv6_fields_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ipv6_fields_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ipv6_fields_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_SA_TAG_ETHERTYPE_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 16;
  uint32_t reserved0 : 16;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_sa_tag_ethertype_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_sa_tag_ethertype_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_sa_tag_ethertype_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t redirect_from : 8;
  uint32_t redirect_to : 8;
  uint32_t reserved0 : 16;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_l2_encap_index_override_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_l2_encap_index_override_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_l2_encap_index_override_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t redirect_from : 8;
  uint32_t redirect_to : 8;
  uint32_t reserved0 : 16;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_l3_encap_index_override_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_l3_encap_index_override_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_l3_encap_index_override_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_ETH_MTU_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 14;
  uint32_t reserved0 : 18;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_mtu_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_mtu_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_mtu_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_CONFIG_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t calc_ip_udp_len_from_byte_count : 1;
  uint32_t bypassed_packets_vport_action : 2;
  uint32_t bypassed_packets_vport : 8;
  uint32_t disable_padding_removal : 1;
  uint32_t l2_encap_index_override_en : 1;
  uint32_t l3_encap_index_override_en : 1;
  uint32_t disable_ptp_detection : 1;
  uint32_t reserved0 : 17;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_config_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_config_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_config_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_0_PORT_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t egress_mtu_err_packet_link_0 : 1;
  uint32_t ingress_fcs_err_packet_link_0 : 1;
  uint32_t ingress_pkt_fifo_empty_before_eop_link_0 : 1;
  uint32_t ingress_ipv4_cs_error_link_0 : 1;
  uint32_t ingress_udp_cs_error_link_0 : 1;
  uint32_t ingress_ip_filtered_packet_link_0 : 1;
  uint32_t ingress_vlan_filtered_packet_link_0 : 1;
  uint32_t ingress_sec_err_packet_link_0 : 1;
  uint32_t ingress_ip_len_err_packet_link_0 : 1;
  uint32_t ingress_trap_rule_0_link_0 : 1;
  uint32_t ingress_trap_rule_1_link_0 : 1;
  uint32_t ingress_trap_rule_2_link_0 : 1;
  uint32_t ingress_trap_rule_3_link_0 : 1;
  uint32_t ingress_last_in_chain_non_local_dst_packet_link_0 : 1;
  uint32_t ingress_timestamped_packets_bw_too_high_link_0 : 1;
  uint32_t reserved0 : 1;
  uint32_t egress_mtu_err_packet_link_1 : 1;
  uint32_t ingress_fcs_err_packet_link_1 : 1;
  uint32_t ingress_pkt_fifo_empty_before_eop_link_1 : 1;
  uint32_t ingress_ipv4_cs_error_link_1 : 1;
  uint32_t ingress_udp_cs_error_link_1 : 1;
  uint32_t ingress_ip_filtered_packet_link_1 : 1;
  uint32_t ingress_vlan_filtered_packet_link_1 : 1;
  uint32_t ingress_sec_err_packet_link_1 : 1;
  uint32_t ingress_ip_len_err_packet_link_1 : 1;
  uint32_t ingress_trap_rule_0_link_1 : 1;
  uint32_t ingress_trap_rule_1_link_1 : 1;
  uint32_t ingress_trap_rule_2_link_1 : 1;
  uint32_t ingress_trap_rule_3_link_1 : 1;
  uint32_t ingress_last_in_chain_non_local_dst_packet_link_1 : 1;
  uint32_t ingress_timestamped_packets_bw_too_high_link_1 : 1;
  uint32_t reserved1 : 1;
} ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_status_0_port_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_status_0_port_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_status_0_port_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_UDP_SW_IRQ_STATUS_1_PORT_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t egress_mtu_err_packet_link_2 : 1;
  uint32_t ingress_fcs_err_packet_link_2 : 1;
  uint32_t ingress_pkt_fifo_empty_before_eop_link_2 : 1;
  uint32_t ingress_ipv4_cs_error_link_2 : 1;
  uint32_t ingress_udp_cs_error_link_2 : 1;
  uint32_t ingress_ip_filtered_packet_link_2 : 1;
  uint32_t ingress_vlan_filtered_packet_link_2 : 1;
  uint32_t ingress_sec_err_packet_link_2 : 1;
  uint32_t ingress_ip_len_err_packet_link_2 : 1;
  uint32_t ingress_trap_rule_0_link_2 : 1;
  uint32_t ingress_trap_rule_1_link_2 : 1;
  uint32_t ingress_trap_rule_2_link_2 : 1;
  uint32_t ingress_trap_rule_3_link_2 : 1;
  uint32_t ingress_last_in_chain_non_local_dst_packet_link_2 : 1;
  uint32_t ingress_timestamped_packets_bw_too_high_link_2 : 1;
  uint32_t reserved0 : 1;
  uint32_t egress_mtu_err_packet_link_3 : 1;
  uint32_t ingress_fcs_err_packet_link_3 : 1;
  uint32_t ingress_pkt_fifo_empty_before_eop_link_3 : 1;
  uint32_t ingress_ipv4_cs_error_link_3 : 1;
  uint32_t ingress_udp_cs_error_link_3 : 1;
  uint32_t ingress_ip_filtered_packet_link_3 : 1;
  uint32_t ingress_vlan_filtered_packet_link_3 : 1;
  uint32_t ingress_sec_err_packet_link_3 : 1;
  uint32_t ingress_ip_len_err_packet_link_3 : 1;
  uint32_t ingress_trap_rule_0_link_3 : 1;
  uint32_t ingress_trap_rule_1_link_3 : 1;
  uint32_t ingress_trap_rule_2_link_3 : 1;
  uint32_t ingress_trap_rule_3_link_3 : 1;
  uint32_t ingress_last_in_chain_non_local_dst_packet_link_3 : 1;
  uint32_t ingress_timestamped_packets_bw_too_high_link_3 : 1;
  uint32_t reserved1 : 1;
} ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_status_1_port_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_status_1_port_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_status_1_port_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_UDP_SW_IRQ_MASK_0_PORT_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t egress_mtu_err_packet_link_0 : 1;
  uint32_t ingress_fcs_err_packet_link_0 : 1;
  uint32_t ingress_pkt_fifo_empty_before_eop_link_0 : 1;
  uint32_t ingress_ipv4_cs_error_link_0 : 1;
  uint32_t ingress_udp_cs_error_link_0 : 1;
  uint32_t ingress_ip_filtered_packet_link_0 : 1;
  uint32_t ingress_vlan_filtered_packet_link_0 : 1;
  uint32_t ingress_sec_err_packet_link_0 : 1;
  uint32_t ingress_ip_len_err_packet_link_0 : 1;
  uint32_t ingress_trap_rule_0_link_0 : 1;
  uint32_t ingress_trap_rule_1_link_0 : 1;
  uint32_t ingress_trap_rule_2_link_0 : 1;
  uint32_t ingress_trap_rule_3_link_0 : 1;
  uint32_t ingress_last_in_chain_non_local_dst_packet_link_0 : 1;
  uint32_t ingress_timestamped_packets_bw_too_high_link_0 : 1;
  uint32_t reserved0 : 1;
  uint32_t egress_mtu_err_packet_link_1 : 1;
  uint32_t ingress_fcs_err_packet_link_1 : 1;
  uint32_t ingress_pkt_fifo_empty_before_eop_link_1 : 1;
  uint32_t ingress_ipv4_cs_error_link_1 : 1;
  uint32_t ingress_udp_cs_error_link_1 : 1;
  uint32_t ingress_ip_filtered_packet_link_1 : 1;
  uint32_t ingress_vlan_filtered_packet_link_1 : 1;
  uint32_t ingress_sec_err_packet_link_1 : 1;
  uint32_t ingress_ip_len_err_packet_link_1 : 1;
  uint32_t ingress_trap_rule_0_link_1 : 1;
  uint32_t ingress_trap_rule_1_link_1 : 1;
  uint32_t ingress_trap_rule_2_link_1 : 1;
  uint32_t ingress_trap_rule_3_link_1 : 1;
  uint32_t ingress_last_in_chain_non_local_dst_packet_link_1 : 1;
  uint32_t ingress_timestamped_packets_bw_too_high_link_1 : 1;
  uint32_t reserved1 : 1;
} ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_mask_0_port_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_mask_0_port_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_mask_0_port_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_UDP_SW_IRQ_MASK_1_PORT_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t egress_mtu_err_packet_link_2 : 1;
  uint32_t ingress_fcs_err_packet_link_2 : 1;
  uint32_t ingress_pkt_fifo_empty_before_eop_link_2 : 1;
  uint32_t ingress_ipv4_cs_error_link_2 : 1;
  uint32_t ingress_udp_cs_error_link_2 : 1;
  uint32_t ingress_ip_filtered_packet_link_2 : 1;
  uint32_t ingress_vlan_filtered_packet_link_2 : 1;
  uint32_t ingress_sec_err_packet_link_2 : 1;
  uint32_t ingress_ip_len_err_packet_link_2 : 1;
  uint32_t ingress_trap_rule_0_link_2 : 1;
  uint32_t ingress_trap_rule_1_link_2 : 1;
  uint32_t ingress_trap_rule_2_link_2 : 1;
  uint32_t ingress_trap_rule_3_link_2 : 1;
  uint32_t ingress_last_in_chain_non_local_dst_packet_link_2 : 1;
  uint32_t ingress_timestamped_packets_bw_too_high_link_2 : 1;
  uint32_t reserved0 : 1;
  uint32_t egress_mtu_err_packet_link_3 : 1;
  uint32_t ingress_fcs_err_packet_link_3 : 1;
  uint32_t ingress_pkt_fifo_empty_before_eop_link_3 : 1;
  uint32_t ingress_ipv4_cs_error_link_3 : 1;
  uint32_t ingress_udp_cs_error_link_3 : 1;
  uint32_t ingress_ip_filtered_packet_link_3 : 1;
  uint32_t ingress_vlan_filtered_packet_link_3 : 1;
  uint32_t ingress_sec_err_packet_link_3 : 1;
  uint32_t ingress_ip_len_err_packet_link_3 : 1;
  uint32_t ingress_trap_rule_0_link_3 : 1;
  uint32_t ingress_trap_rule_1_link_3 : 1;
  uint32_t ingress_trap_rule_2_link_3 : 1;
  uint32_t ingress_trap_rule_3_link_3 : 1;
  uint32_t ingress_last_in_chain_non_local_dst_packet_link_3 : 1;
  uint32_t ingress_timestamped_packets_bw_too_high_link_3 : 1;
  uint32_t reserved1 : 1;
} ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_mask_1_port_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_mask_1_port_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_mask_1_port_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_UDP_SW_IRQ_CLR_0_PORT_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t egress_mtu_err_packet_link_0 : 1;
  uint32_t ingress_fcs_err_packet_link_0 : 1;
  uint32_t ingress_pkt_fifo_empty_before_eop_link_0 : 1;
  uint32_t ingress_ipv4_cs_error_link_0 : 1;
  uint32_t ingress_udp_cs_error_link_0 : 1;
  uint32_t ingress_ip_filtered_packet_link_0 : 1;
  uint32_t ingress_vlan_filtered_packet_link_0 : 1;
  uint32_t ingress_sec_err_packet_link_0 : 1;
  uint32_t ingress_ip_len_err_packet_link_0 : 1;
  uint32_t ingress_trap_rule_0_link_0 : 1;
  uint32_t ingress_trap_rule_1_link_0 : 1;
  uint32_t ingress_trap_rule_2_link_0 : 1;
  uint32_t ingress_trap_rule_3_link_0 : 1;
  uint32_t ingress_last_in_chain_non_local_dst_packet_link_0 : 1;
  uint32_t ingress_timestamped_packets_bw_too_high_link_0 : 1;
  uint32_t reserved0 : 1;
  uint32_t egress_mtu_err_packet_link_1 : 1;
  uint32_t ingress_fcs_err_packet_link_1 : 1;
  uint32_t ingress_pkt_fifo_empty_before_eop_link_1 : 1;
  uint32_t ingress_ipv4_cs_error_link_1 : 1;
  uint32_t ingress_udp_cs_error_link_1 : 1;
  uint32_t ingress_ip_filtered_packet_link_1 : 1;
  uint32_t ingress_vlan_filtered_packet_link_1 : 1;
  uint32_t ingress_sec_err_packet_link_1 : 1;
  uint32_t ingress_ip_len_err_packet_link_1 : 1;
  uint32_t ingress_trap_rule_0_link_1 : 1;
  uint32_t ingress_trap_rule_1_link_1 : 1;
  uint32_t ingress_trap_rule_2_link_1 : 1;
  uint32_t ingress_trap_rule_3_link_1 : 1;
  uint32_t ingress_last_in_chain_non_local_dst_packet_link_1 : 1;
  uint32_t ingress_timestamped_packets_bw_too_high_link_1 : 1;
  uint32_t reserved1 : 1;
} ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_clr_0_port_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_clr_0_port_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_clr_0_port_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_UDP_SW_IRQ_CLR_1_PORT_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t egress_mtu_err_packet_link_2 : 1;
  uint32_t ingress_fcs_err_packet_link_2 : 1;
  uint32_t ingress_pkt_fifo_empty_before_eop_link_2 : 1;
  uint32_t ingress_ipv4_cs_error_link_2 : 1;
  uint32_t ingress_udp_cs_error_link_2 : 1;
  uint32_t ingress_ip_filtered_packet_link_2 : 1;
  uint32_t ingress_vlan_filtered_packet_link_2 : 1;
  uint32_t ingress_sec_err_packet_link_2 : 1;
  uint32_t ingress_ip_len_err_packet_link_2 : 1;
  uint32_t ingress_trap_rule_0_link_2 : 1;
  uint32_t ingress_trap_rule_1_link_2 : 1;
  uint32_t ingress_trap_rule_2_link_2 : 1;
  uint32_t ingress_trap_rule_3_link_2 : 1;
  uint32_t ingress_last_in_chain_non_local_dst_packet_link_2 : 1;
  uint32_t ingress_timestamped_packets_bw_too_high_link_2 : 1;
  uint32_t reserved0 : 1;
  uint32_t egress_mtu_err_packet_link_3 : 1;
  uint32_t ingress_fcs_err_packet_link_3 : 1;
  uint32_t ingress_pkt_fifo_empty_before_eop_link_3 : 1;
  uint32_t ingress_ipv4_cs_error_link_3 : 1;
  uint32_t ingress_udp_cs_error_link_3 : 1;
  uint32_t ingress_ip_filtered_packet_link_3 : 1;
  uint32_t ingress_vlan_filtered_packet_link_3 : 1;
  uint32_t ingress_sec_err_packet_link_3 : 1;
  uint32_t ingress_ip_len_err_packet_link_3 : 1;
  uint32_t ingress_trap_rule_0_link_3 : 1;
  uint32_t ingress_trap_rule_1_link_3 : 1;
  uint32_t ingress_trap_rule_2_link_3 : 1;
  uint32_t ingress_trap_rule_3_link_3 : 1;
  uint32_t ingress_last_in_chain_non_local_dst_packet_link_3 : 1;
  uint32_t ingress_timestamped_packets_bw_too_high_link_3 : 1;
  uint32_t reserved1 : 1;
} ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_clr_1_port_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_clr_1_port_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_udp_sw_irq_clr_1_port_p_u_v2;

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_UDP_FH_UDP_FH_FILTER
 *--------------------------------------------------------------------------*/

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_FILT_VLAN_ADDR_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 16;
  uint32_t reserved0 : 16;
} ecpri_qudp_hwio_def_ecpri_udp_fh_filt_vlan_addr_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_filt_vlan_addr_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_filt_vlan_addr_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 16;
  uint32_t reserved0 : 16;
} ecpri_qudp_hwio_def_ecpri_udp_fh_udp_classification_list_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_udp_classification_list_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_udp_classification_list_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr0_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr0_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr0_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr1_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr1_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr1_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr2_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr2_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr2_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr3_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr3_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_filt_ip_dst_addr3_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_filt_mac_address_lsb_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_filt_mac_address_lsb_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_filt_mac_address_lsb_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 16;
  uint32_t reserved0 : 16;
} ecpri_qudp_hwio_def_ecpri_udp_fh_filt_mac_address_msb_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_filt_mac_address_msb_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_filt_mac_address_msb_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t action : 3;
  uint32_t gsi_id : 2;
  uint32_t ring_id : 8;
  uint32_t reserved0 : 19;
} ecpri_qudp_hwio_def_ecpri_udp_fh_filt_mac_address_info_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_filt_mac_address_info_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_filt_mac_address_info_port_p_entry_n_u_v2;

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_UDP_FH_UDP_FH_RAMS
 *--------------------------------------------------------------------------*/

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_num_eth_udp_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_num_eth_udp_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_num_eth_udp_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_fcs_err_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_fcs_err_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_fcs_err_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_ipv4_cs_error_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_ipv4_cs_error_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_ipv4_cs_error_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_udp_cs_error_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_udp_cs_error_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_udp_cs_error_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_ip_filtered_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_ip_filtered_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_ip_filtered_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_vlan_filtered_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_vlan_filtered_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_vlan_filtered_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_sec_err_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_sec_err_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_sec_err_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_ip_len_err_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_ip_len_err_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_ip_len_err_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_num_eth_ecpri_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_num_eth_ecpri_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_num_eth_ecpri_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_num_eth_ptp_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_num_eth_ptp_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_num_eth_ptp_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_num_eth_other_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_num_eth_other_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_num_eth_other_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_num_udp_ecpri_or_nfapi_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_num_udp_ecpri_or_nfapi_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_num_udp_ecpri_or_nfapi_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_num_udp_ptp_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_num_udp_ptp_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_num_udp_ptp_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_num_udp_other_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_num_udp_other_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_ingress_num_udp_other_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_num_udp_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_num_udp_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_num_udp_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_num_eth_only_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_num_eth_only_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_num_eth_only_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_num_bypassed_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_num_bypassed_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_num_bypassed_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_mtu_err_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_mtu_err_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_mtu_err_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_ETH_DST0_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_dst0_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_dst0_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_dst0_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t dst_msb : 16;
  uint32_t src_msb : 16;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_src1_dst1_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_src1_dst1_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_src1_dst1_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_ETH_SRC0_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_src0_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_src0_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_eth_src0_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t ethertype : 16;
  uint32_t vlan_data : 16;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_vlan_ethertype_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_vlan_ethertype_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_vlan_ethertype_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_VPORT_MISC_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t vport : 8;
  uint32_t has_vlan : 1;
  uint32_t vport_action : 2;
  uint32_t rsvd : 4;
  uint32_t reserved0 : 17;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_vport_misc_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_vport_misc_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_vport_misc_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr0_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr0_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr0_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr1_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr1_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr1_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr2_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr2_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr2_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr3_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr3_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_src_addr3_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr0_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr0_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr0_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr1_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr1_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr1_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr2_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr2_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr2_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr3_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr3_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_ip_dst_addr3_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_UDP_PORTS_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t src : 16;
  uint32_t dst : 16;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_udp_ports_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_udp_ports_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_udp_ports_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_FH_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t sa_tag_data : 16;
  uint32_t tos : 8;
  uint32_t ip_type : 1;
  uint32_t is_ipsec : 1;
  uint32_t df_bit : 1;
  uint32_t calc_udp_cs : 1;
  uint32_t rsvd : 4;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_sa_tag_ip_tos_misc_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_fh_egress_sa_tag_ip_tos_misc_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_fh_egress_sa_tag_ip_tos_misc_port_p_entry_n_u_v2;

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_UDP_C2C_UDP_C2C_REGS
 *--------------------------------------------------------------------------*/

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_WORDS_BEFORE_TRANSMITTING_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 8;
  uint32_t reserved0 : 24;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_words_before_transmitting_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_words_before_transmitting_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_words_before_transmitting_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_ECPRI_ETHERTYPE_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 16;
  uint32_t reserved0 : 16;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ecpri_ethertype_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_ecpri_ethertype_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ecpri_ethertype_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_IDLE_STATUS_PORT_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t port_is_idle : 1;
  uint32_t ingress_idle : 1;
  uint32_t ingress_aligner_idle : 1;
  uint32_t ingress_pkt_fifo_empty_link_0 : 1;
  uint32_t ingress_cmd_fifo_empty_link_0 : 1;
  uint32_t egress_idle : 1;
  uint32_t egress_hdri_idle : 1;
  uint32_t egress_pkt_fifo_empty : 1;
  uint32_t egress_aligner_idle : 1;
  uint32_t egress_output_fifo_empty : 1;
  uint32_t reserved0 : 22;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_idle_status_port_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_idle_status_port_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_idle_status_port_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_CGC_CFG
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t ingress_cgc_open : 1;
  uint32_t egress_cgc_open : 1;
  uint32_t reserved0 : 30;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_cgc_cfg_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_cgc_cfg_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_cgc_cfg_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_HW_PARAMS_0
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t instance_type : 2;
  uint32_t ports_n : 2;
  uint32_t links_n : 3;
  uint32_t eth_table_entries_n : 9;
  uint32_t ip_table_entries_n : 9;
  uint32_t udp_classification_entries_n : 6;
  uint32_t l3_support : 1;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_hw_params_0_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_hw_params_0_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_hw_params_0_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_HW_PARAMS_1
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t vlan_filt_entries_n : 5;
  uint32_t ip_filt_entries_n : 5;
  uint32_t eth_dst_filt_entries_n : 5;
  uint32_t reserved0 : 17;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_hw_params_1_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_hw_params_1_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_hw_params_1_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_QUDP_STAT_COUNTERS_CTL
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t cnt_en : 1;
  uint32_t cnt_clr_en : 1;
  uint32_t reserved0 : 30;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_qudp_stat_counters_ctl_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_qudp_stat_counters_ctl_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_qudp_stat_counters_ctl_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_QUDP_CTL_PORT_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t sres : 1;
  uint32_t reserved0 : 1;
  uint32_t disable_irq_delay : 1;
  uint32_t reserved1 : 29;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_qudp_ctl_port_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_qudp_ctl_port_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_qudp_ctl_port_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_INGRESS_UDP_WATERMARK_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t pkt_fifo : 10;
  uint32_t pkt_handler_sync_fifos : 3;
  uint32_t reserved0 : 3;
  uint32_t cmd_fifo : 10;
  uint32_t reserved1 : 6;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_udp_watermark_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_udp_watermark_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_udp_watermark_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_EGRESS_UDP_WATERMARK_0_PORT_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t pkt_fifo : 10;
  uint32_t hdri_cfg_index_fifo : 9;
  uint32_t hdri_output_fifo : 3;
  uint32_t aligner_output_fifo : 3;
  uint32_t reserved0 : 7;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_udp_watermark_0_port_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_udp_watermark_0_port_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_udp_watermark_0_port_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_DEBUG_FEATURES_CFG
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t tpdm_en : 1;
  uint32_t tpdm_operation_mode : 1;
  uint32_t watermark_en : 1;
  uint32_t en_clear_watermark_on_read : 1;
  uint32_t testbus_en : 1;
  uint32_t hw_events_en : 1;
  uint32_t reserved0 : 26;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_debug_features_cfg_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_debug_features_cfg_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_debug_features_cfg_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_TPDM_DATA_CFG
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t port_index_sel : 2;
  uint32_t reserved0 : 2;
  uint32_t bus_sel : 3;
  uint32_t sideband_insertion_en : 1;
  uint32_t sideband_insertion_mode : 2;
  uint32_t sideband_insertion_offset : 3;
  uint32_t sampling_mode : 2;
  uint32_t reserved1 : 2;
  uint32_t max_words_to_send_per_packet : 9;
  uint32_t reserved2 : 6;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_tpdm_data_cfg_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_tpdm_data_cfg_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_tpdm_data_cfg_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_TPDM_CONTROL_CFG_0
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t port_index_sel : 2;
  uint32_t reserved0 : 2;
  uint32_t bus_sel : 3;
  uint32_t arbitrary_testbus_0_sel : 7;
  uint32_t arbitrary_testbus_1_sel : 7;
  uint32_t arbitrary_testbus_2_sel : 7;
  uint32_t reserved1 : 4;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_tpdm_control_cfg_0_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_tpdm_control_cfg_0_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_tpdm_control_cfg_0_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_TPDM_CONTROL_CFG_1
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t arbitrary_testbus_3_sel : 7;
  uint32_t arbitrary_testbus_4_sel : 7;
  uint32_t arbitrary_testbus_5_sel : 7;
  uint32_t arbitrary_testbus_6_sel : 7;
  uint32_t reserved0 : 4;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_tpdm_control_cfg_1_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_tpdm_control_cfg_1_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_tpdm_control_cfg_1_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_TPDM_CONTROL_MASK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t mask_bits : 32;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_tpdm_control_mask_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_tpdm_control_mask_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_tpdm_control_mask_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_TESTBUS_SEL_CFG
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t port_index_sel : 2;
  uint32_t reserved0 : 2;
  uint32_t testbus_sel : 7;
  uint32_t reserved1 : 21;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_testbus_sel_cfg_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_testbus_sel_cfg_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_testbus_sel_cfg_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_TESTBUS
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t data : 32;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_testbus_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_testbus_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_testbus_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_EGRESS_ETH_MTU_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 14;
  uint32_t reserved0 : 18;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_eth_mtu_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_eth_mtu_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_eth_mtu_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_EGRESS_CONFIG_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t reserved0 : 1;
  uint32_t bypassed_packets_vport_action : 2;
  uint32_t bypassed_packets_vport : 8;
  uint32_t disable_padding_removal : 1;
  uint32_t reserved1 : 20;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_config_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_config_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_config_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_UDP_SW_IRQ_STATUS_0_PORT_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t egress_mtu_err_packet_link_0 : 1;
  uint32_t ingress_fcs_err_packet_link_0 : 1;
  uint32_t ingress_pkt_fifo_empty_before_eop_link_0 : 1;
  uint32_t reserved0 : 29;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_udp_sw_irq_status_0_port_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_udp_sw_irq_status_0_port_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_udp_sw_irq_status_0_port_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_UDP_SW_IRQ_MASK_0_PORT_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t egress_mtu_err_packet_link_0 : 1;
  uint32_t ingress_fcs_err_packet_link_0 : 1;
  uint32_t ingress_pkt_fifo_empty_before_eop_link_0 : 1;
  uint32_t reserved0 : 29;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_udp_sw_irq_mask_0_port_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_udp_sw_irq_mask_0_port_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_udp_sw_irq_mask_0_port_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_UDP_SW_IRQ_CLR_0_PORT_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t egress_mtu_err_packet_link_0 : 1;
  uint32_t ingress_fcs_err_packet_link_0 : 1;
  uint32_t ingress_pkt_fifo_empty_before_eop_link_0 : 1;
  uint32_t reserved0 : 29;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_udp_sw_irq_clr_0_port_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_udp_sw_irq_clr_0_port_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_udp_sw_irq_clr_0_port_p_u_v2;

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_UDP_C2C_UDP_C2C_RAMS
 *--------------------------------------------------------------------------*/

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_num_eth_udp_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_num_eth_udp_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_num_eth_udp_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_fcs_err_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_fcs_err_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_fcs_err_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_ipv4_cs_error_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_ipv4_cs_error_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_ipv4_cs_error_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_udp_cs_error_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_udp_cs_error_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_udp_cs_error_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_ip_filtered_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_ip_filtered_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_ip_filtered_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_vlan_filtered_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_vlan_filtered_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_vlan_filtered_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_sec_err_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_sec_err_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_sec_err_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_ip_len_err_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_ip_len_err_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_ip_len_err_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_num_eth_ecpri_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_num_eth_ecpri_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_num_eth_ecpri_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_num_eth_ptp_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_num_eth_ptp_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_num_eth_ptp_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_num_eth_other_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_num_eth_other_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_num_eth_other_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_num_udp_ecpri_or_nfapi_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_num_udp_ecpri_or_nfapi_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_num_udp_ecpri_or_nfapi_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_num_udp_ptp_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_num_udp_ptp_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_num_udp_ptp_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_num_udp_other_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_num_udp_other_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_ingress_num_udp_other_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_num_udp_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_num_udp_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_num_udp_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_num_eth_only_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_num_eth_only_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_num_eth_only_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_num_bypassed_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_num_bypassed_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_num_bypassed_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_mtu_err_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_mtu_err_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_mtu_err_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_EGRESS_ETH_DST0_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_eth_dst0_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_eth_dst0_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_eth_dst0_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t dst_msb : 16;
  uint32_t src_msb : 16;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_eth_src1_dst1_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_eth_src1_dst1_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_eth_src1_dst1_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_EGRESS_ETH_SRC0_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_eth_src0_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_eth_src0_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_eth_src0_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t ethertype : 16;
  uint32_t vlan_data : 16;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_vlan_ethertype_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_vlan_ethertype_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_vlan_ethertype_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_C2C_EGRESS_VPORT_MISC_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t vport : 8;
  uint32_t has_vlan : 1;
  uint32_t vport_action : 2;
  uint32_t rsvd : 4;
  uint32_t reserved0 : 17;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_vport_misc_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_vport_misc_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_c2c_egress_vport_misc_port_p_entry_n_u_v2;

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_UDP_L2_UDP_L2_REGS
 *--------------------------------------------------------------------------*/

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_INGRESS_CONFIG_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t enable_ip_dst_filt : 1;
  uint32_t enable_udp_dst_class : 1;
  uint32_t enable_vlan_filt : 1;
  uint32_t enable_udp_cs_check : 1;
  uint32_t enable_ip_len_check : 1;
  uint32_t ipv4_cs_err_action : 2;
  uint32_t udp_cs_err_action : 2;
  uint32_t fcs_err_action : 2;
  uint32_t pkt_err_action : 2;
  uint32_t ip_len_err_action : 2;
  uint32_t disable_st_and_fw : 1;
  uint32_t vlan_filt_miss_action : 2;
  uint32_t ip_filt_miss_action : 2;
  uint32_t enable_mac_dst_check : 1;
  uint32_t use_external_not_local_mac_dst : 1;
  uint32_t enable_broadcast_check : 1;
  uint32_t last_in_chain : 1;
  uint32_t non_local_dst_action : 3;
  uint32_t reserved0 : 2;
  uint32_t enable_eth_padding_removal : 1;
  uint32_t reserved1 : 2;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_config_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_config_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_config_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_WORDS_BEFORE_TRANSMITTING_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 8;
  uint32_t reserved0 : 24;
} ecpri_qudp_hwio_def_ecpri_udp_l2_words_before_transmitting_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_words_before_transmitting_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_words_before_transmitting_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_UDP_PTP_PORT_NUM_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 16;
  uint32_t reserved0 : 16;
} ecpri_qudp_hwio_def_ecpri_udp_l2_udp_ptp_port_num_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_udp_ptp_port_num_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_udp_ptp_port_num_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_ECPRI_ETHERTYPE_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 16;
  uint32_t reserved0 : 16;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ecpri_ethertype_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_ecpri_ethertype_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ecpri_ethertype_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_PTP_ETHERTYPE_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 16;
  uint32_t reserved0 : 16;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ptp_ethertype_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_ptp_ethertype_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ptp_ethertype_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_FILT_ERROR_CHANNEL_CFG_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t send_vlan_filt_miss_to_error_channel : 1;
  uint32_t send_ip_filt_miss_to_error_channel : 1;
  uint32_t reserved0 : 30;
} ecpri_qudp_hwio_def_ecpri_udp_l2_filt_error_channel_cfg_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_filt_error_channel_cfg_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_filt_error_channel_cfg_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_TRAP_MISC_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t rule64_offset : 8;
  uint32_t rule32_offset : 8;
  uint32_t action : 3;
  uint32_t enable : 1;
  uint32_t reserved0 : 12;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_misc_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_trap_misc_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_misc_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_TRAP_RULE64_VAL_LSB_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_rule64_val_lsb_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_trap_rule64_val_lsb_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_rule64_val_lsb_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_TRAP_RULE64_VAL_MSB_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_rule64_val_msb_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_trap_rule64_val_msb_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_rule64_val_msb_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_TRAP_RULE64_MASK_LSB_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_rule64_mask_lsb_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_trap_rule64_mask_lsb_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_rule64_mask_lsb_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_TRAP_RULE64_MASK_MSB_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_rule64_mask_msb_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_trap_rule64_mask_msb_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_rule64_mask_msb_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_TRAP_RULE32_VAL_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_rule32_val_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_trap_rule32_val_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_rule32_val_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_TRAP_RULE32_MASK_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_rule32_mask_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_trap_rule32_mask_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_rule32_mask_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_TRAP_LARGE_SET_OFFSETS_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t large_set_rule128_offset : 8;
  uint32_t large_set_rule32_offset : 8;
  uint32_t reserved0 : 16;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_offsets_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_offsets_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_offsets_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_VAL_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule32_val_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule32_val_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule32_val_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_TRAP_LARGE_SET_RULE32_MASK_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule32_mask_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule32_mask_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule32_mask_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_VAL_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule128_0_val_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule128_0_val_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule128_0_val_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_0_MASK_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule128_0_mask_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule128_0_mask_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule128_0_mask_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_VAL_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule128_1_val_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule128_1_val_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule128_1_val_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_1_MASK_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule128_1_mask_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule128_1_mask_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule128_1_mask_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_VAL_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule128_2_val_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule128_2_val_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule128_2_val_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_2_MASK_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule128_2_mask_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule128_2_mask_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule128_2_mask_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_VAL_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule128_3_val_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule128_3_val_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule128_3_val_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_TRAP_LARGE_SET_RULE128_3_MASK_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule128_3_mask_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule128_3_mask_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_large_set_rule128_3_mask_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_TRAP_PTP_CFG_PORT_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t trap_ptp_over_eth_without_vlan_en : 1;
  uint32_t trap_ptp_over_eth_with_vlan_en : 1;
  uint32_t trap_ptp_over_ipv4_without_vlan_en : 1;
  uint32_t trap_ptp_over_ipv4_with_vlan_en : 1;
  uint32_t trap_ptp_over_ipv6_without_vlan_en : 1;
  uint32_t trap_ptp_over_ipv6_with_vlan_en : 1;
  uint32_t reserved0 : 26;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_ptp_cfg_port_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_trap_ptp_cfg_port_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_trap_ptp_cfg_port_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRIES_VALID_BITS
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t valid_bits : 16;
  uint32_t reserved0 : 16;
} ecpri_qudp_hwio_def_ecpri_udp_l2_filt_vlan_addr_port_p_entries_valid_bits_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_filt_vlan_addr_port_p_entries_valid_bits_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_filt_vlan_addr_port_p_entries_valid_bits_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRIES_VALID_BITS
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t valid_bits : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_udp_classification_list_port_p_entries_valid_bits_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_udp_classification_list_port_p_entries_valid_bits_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_udp_classification_list_port_p_entries_valid_bits_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_FILT_IP_DST_ADDR_PORT_p_ENTRIES_VALID_BITS
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t valid_bits : 16;
  uint32_t reserved0 : 16;
} ecpri_qudp_hwio_def_ecpri_udp_l2_filt_ip_dst_addr_port_p_entries_valid_bits_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_filt_ip_dst_addr_port_p_entries_valid_bits_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_filt_ip_dst_addr_port_p_entries_valid_bits_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_FILT_MAC_ADDRESS_PORT_p_ENTRIES_VALID_BITS
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t valid_bits : 4;
  uint32_t reserved0 : 28;
} ecpri_qudp_hwio_def_ecpri_udp_l2_filt_mac_address_port_p_entries_valid_bits_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_filt_mac_address_port_p_entries_valid_bits_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_filt_mac_address_port_p_entries_valid_bits_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_NON_ECPRI_DMA_RING_INFO_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t gsi_id : 2;
  uint32_t ring_id : 8;
  uint32_t reserved0 : 22;
} ecpri_qudp_hwio_def_ecpri_udp_l2_non_ecpri_dma_ring_info_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_non_ecpri_dma_ring_info_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_non_ecpri_dma_ring_info_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_IDLE_STATUS_PORT_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t port_is_idle : 1;
  uint32_t ingress_idle : 1;
  uint32_t ingress_aligner_idle : 1;
  uint32_t ingress_pkt_fifo_empty_link_0 : 1;
  uint32_t ingress_cmd_fifo_empty_link_0 : 1;
  uint32_t egress_idle : 1;
  uint32_t egress_hdri_idle : 1;
  uint32_t egress_pkt_fifo_empty : 1;
  uint32_t egress_aligner_idle : 1;
  uint32_t egress_output_fifo_empty : 1;
  uint32_t egress_cs_fifo_empty : 1;
  uint32_t reserved0 : 21;
} ecpri_qudp_hwio_def_ecpri_udp_l2_idle_status_port_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_idle_status_port_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_idle_status_port_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_CGC_CFG
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t ingress_cgc_open : 1;
  uint32_t egress_cgc_open : 1;
  uint32_t reserved0 : 30;
} ecpri_qudp_hwio_def_ecpri_udp_l2_cgc_cfg_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_cgc_cfg_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_cgc_cfg_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_HW_PARAMS_0
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t instance_type : 2;
  uint32_t ports_n : 2;
  uint32_t links_n : 3;
  uint32_t eth_table_entries_n : 9;
  uint32_t ip_table_entries_n : 9;
  uint32_t udp_classification_entries_n : 6;
  uint32_t l3_support : 1;
} ecpri_qudp_hwio_def_ecpri_udp_l2_hw_params_0_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_hw_params_0_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_hw_params_0_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_HW_PARAMS_1
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t vlan_filt_entries_n : 5;
  uint32_t ip_filt_entries_n : 5;
  uint32_t eth_dst_filt_entries_n : 5;
  uint32_t reserved0 : 17;
} ecpri_qudp_hwio_def_ecpri_udp_l2_hw_params_1_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_hw_params_1_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_hw_params_1_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_QUDP_STAT_COUNTERS_CTL
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t cnt_en : 1;
  uint32_t cnt_clr_en : 1;
  uint32_t reserved0 : 30;
} ecpri_qudp_hwio_def_ecpri_udp_l2_qudp_stat_counters_ctl_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_qudp_stat_counters_ctl_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_qudp_stat_counters_ctl_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_QUDP_CTL_PORT_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t sres : 1;
  uint32_t sleep_mode : 1;
  uint32_t disable_irq_delay : 1;
  uint32_t reserved0 : 29;
} ecpri_qudp_hwio_def_ecpri_udp_l2_qudp_ctl_port_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_qudp_ctl_port_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_qudp_ctl_port_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_INGRESS_UDP_WATERMARK_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t pkt_fifo : 10;
  uint32_t pkt_handler_sync_fifos : 3;
  uint32_t ptp_timestamp_fifo : 3;
  uint32_t cmd_fifo : 8;
  uint32_t l2_sb_fifo : 8;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_udp_watermark_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_udp_watermark_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_udp_watermark_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_0_PORT_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t pkt_fifo : 10;
  uint32_t hdri_cfg_index_fifo : 9;
  uint32_t hdri_output_fifo : 3;
  uint32_t aligner_output_fifo : 3;
  uint32_t reserved0 : 7;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_udp_watermark_0_port_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_udp_watermark_0_port_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_udp_watermark_0_port_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_DEBUG_FEATURES_CFG
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t tpdm_en : 1;
  uint32_t tpdm_operation_mode : 1;
  uint32_t watermark_en : 1;
  uint32_t en_clear_watermark_on_read : 1;
  uint32_t testbus_en : 1;
  uint32_t hw_events_en : 1;
  uint32_t reserved0 : 26;
} ecpri_qudp_hwio_def_ecpri_udp_l2_debug_features_cfg_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_debug_features_cfg_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_debug_features_cfg_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_TPDM_DATA_CFG
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t reserved0 : 4;
  uint32_t bus_sel : 3;
  uint32_t sideband_insertion_en : 1;
  uint32_t sideband_insertion_mode : 2;
  uint32_t sideband_insertion_offset : 3;
  uint32_t sampling_mode : 2;
  uint32_t reserved1 : 2;
  uint32_t max_words_to_send_per_packet : 9;
  uint32_t sample_only_trapped_packets : 1;
  uint32_t reserved2 : 5;
} ecpri_qudp_hwio_def_ecpri_udp_l2_tpdm_data_cfg_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_tpdm_data_cfg_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_tpdm_data_cfg_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_TPDM_CONTROL_CFG_0
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t reserved0 : 4;
  uint32_t bus_sel : 3;
  uint32_t arbitrary_testbus_0_sel : 7;
  uint32_t arbitrary_testbus_1_sel : 7;
  uint32_t arbitrary_testbus_2_sel : 7;
  uint32_t reserved1 : 4;
} ecpri_qudp_hwio_def_ecpri_udp_l2_tpdm_control_cfg_0_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_tpdm_control_cfg_0_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_tpdm_control_cfg_0_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_TPDM_CONTROL_CFG_1
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t arbitrary_testbus_3_sel : 7;
  uint32_t arbitrary_testbus_4_sel : 7;
  uint32_t arbitrary_testbus_5_sel : 7;
  uint32_t arbitrary_testbus_6_sel : 7;
  uint32_t reserved0 : 4;
} ecpri_qudp_hwio_def_ecpri_udp_l2_tpdm_control_cfg_1_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_tpdm_control_cfg_1_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_tpdm_control_cfg_1_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_TPDM_CONTROL_MASK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t mask_bits : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_tpdm_control_mask_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_tpdm_control_mask_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_tpdm_control_mask_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_TESTBUS_SEL_CFG
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t reserved0 : 4;
  uint32_t testbus_sel : 7;
  uint32_t reserved1 : 21;
} ecpri_qudp_hwio_def_ecpri_udp_l2_testbus_sel_cfg_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_testbus_sel_cfg_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_testbus_sel_cfg_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_TESTBUS
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t data : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_testbus_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_testbus_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_testbus_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_ERROR_SYNDROME_MISC_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t clr : 1;
  uint32_t en : 1;
  uint32_t num_valid_bytes : 7;
  uint32_t link_id : 2;
  uint32_t erro_info : 8;
  uint32_t reserved0 : 13;
} ecpri_qudp_hwio_def_ecpri_udp_l2_error_syndrome_misc_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_error_syndrome_misc_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_error_syndrome_misc_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_ERROR_SYNDROME_REG_PORT_p_ENRTY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_error_syndrome_reg_port_p_enrty_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_error_syndrome_reg_port_p_enrty_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_error_syndrome_reg_port_p_enrty_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_UDP_WATERMARK_1_PORT_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t cs_calc_fifo : 9;
  uint32_t cs_update_fifo : 2;
  uint32_t reserved0 : 21;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_udp_watermark_1_port_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_udp_watermark_1_port_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_udp_watermark_1_port_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_IPV4_FIELDS_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t id : 16;
  uint32_t ttl : 8;
  uint32_t reserved0 : 8;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ipv4_fields_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ipv4_fields_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ipv4_fields_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_IPV6_FIELDS_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t hop_limit : 8;
  uint32_t flow_label : 20;
  uint32_t reserved0 : 4;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ipv6_fields_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ipv6_fields_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ipv6_fields_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_SA_TAG_ETHERTYPE_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 16;
  uint32_t reserved0 : 16;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_sa_tag_ethertype_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_sa_tag_ethertype_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_sa_tag_ethertype_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_L2_ENCAP_INDEX_OVERRIDE_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t redirect_from : 8;
  uint32_t redirect_to : 8;
  uint32_t reserved0 : 16;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_l2_encap_index_override_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_l2_encap_index_override_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_l2_encap_index_override_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_L3_ENCAP_INDEX_OVERRIDE_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t redirect_from : 8;
  uint32_t redirect_to : 8;
  uint32_t reserved0 : 16;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_l3_encap_index_override_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_l3_encap_index_override_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_l3_encap_index_override_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_ETH_MTU_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 14;
  uint32_t reserved0 : 18;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_eth_mtu_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_eth_mtu_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_eth_mtu_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_CONFIG_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t calc_ip_udp_len_from_byte_count : 1;
  uint32_t bypassed_packets_vport_action : 2;
  uint32_t bypassed_packets_vport : 8;
  uint32_t disable_padding_removal : 1;
  uint32_t l2_encap_index_override_en : 1;
  uint32_t l3_encap_index_override_en : 1;
  uint32_t disable_ptp_detection : 1;
  uint32_t reserved0 : 17;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_config_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_config_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_config_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_UDP_SW_IRQ_STATUS_0_PORT_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t egress_mtu_err_packet_link_0 : 1;
  uint32_t ingress_fcs_err_packet_link_0 : 1;
  uint32_t ingress_pkt_fifo_empty_before_eop_link_0 : 1;
  uint32_t ingress_ipv4_cs_error_link_0 : 1;
  uint32_t ingress_udp_cs_error_link_0 : 1;
  uint32_t ingress_ip_filtered_packet_link_0 : 1;
  uint32_t ingress_vlan_filtered_packet_link_0 : 1;
  uint32_t ingress_sec_err_packet_link_0 : 1;
  uint32_t ingress_ip_len_err_packet_link_0 : 1;
  uint32_t ingress_trap_rule_0_link_0 : 1;
  uint32_t ingress_trap_rule_1_link_0 : 1;
  uint32_t ingress_trap_rule_2_link_0 : 1;
  uint32_t ingress_trap_rule_3_link_0 : 1;
  uint32_t ingress_last_in_chain_non_local_dst_packet_link_0 : 1;
  uint32_t ingress_timestamped_packets_bw_too_high_link_0 : 1;
  uint32_t reserved0 : 17;
} ecpri_qudp_hwio_def_ecpri_udp_l2_udp_sw_irq_status_0_port_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_udp_sw_irq_status_0_port_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_udp_sw_irq_status_0_port_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_UDP_SW_IRQ_MASK_0_PORT_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t egress_mtu_err_packet_link_0 : 1;
  uint32_t ingress_fcs_err_packet_link_0 : 1;
  uint32_t ingress_pkt_fifo_empty_before_eop_link_0 : 1;
  uint32_t ingress_ipv4_cs_error_link_0 : 1;
  uint32_t ingress_udp_cs_error_link_0 : 1;
  uint32_t ingress_ip_filtered_packet_link_0 : 1;
  uint32_t ingress_vlan_filtered_packet_link_0 : 1;
  uint32_t ingress_sec_err_packet_link_0 : 1;
  uint32_t ingress_ip_len_err_packet_link_0 : 1;
  uint32_t ingress_trap_rule_0_link_0 : 1;
  uint32_t ingress_trap_rule_1_link_0 : 1;
  uint32_t ingress_trap_rule_2_link_0 : 1;
  uint32_t ingress_trap_rule_3_link_0 : 1;
  uint32_t ingress_last_in_chain_non_local_dst_packet_link_0 : 1;
  uint32_t ingress_timestamped_packets_bw_too_high_link_0 : 1;
  uint32_t reserved0 : 17;
} ecpri_qudp_hwio_def_ecpri_udp_l2_udp_sw_irq_mask_0_port_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_udp_sw_irq_mask_0_port_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_udp_sw_irq_mask_0_port_p_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_UDP_SW_IRQ_CLR_0_PORT_p
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t egress_mtu_err_packet_link_0 : 1;
  uint32_t ingress_fcs_err_packet_link_0 : 1;
  uint32_t ingress_pkt_fifo_empty_before_eop_link_0 : 1;
  uint32_t ingress_ipv4_cs_error_link_0 : 1;
  uint32_t ingress_udp_cs_error_link_0 : 1;
  uint32_t ingress_ip_filtered_packet_link_0 : 1;
  uint32_t ingress_vlan_filtered_packet_link_0 : 1;
  uint32_t ingress_sec_err_packet_link_0 : 1;
  uint32_t ingress_ip_len_err_packet_link_0 : 1;
  uint32_t ingress_trap_rule_0_link_0 : 1;
  uint32_t ingress_trap_rule_1_link_0 : 1;
  uint32_t ingress_trap_rule_2_link_0 : 1;
  uint32_t ingress_trap_rule_3_link_0 : 1;
  uint32_t ingress_last_in_chain_non_local_dst_packet_link_0 : 1;
  uint32_t ingress_timestamped_packets_bw_too_high_link_0 : 1;
  uint32_t reserved0 : 17;
} ecpri_qudp_hwio_def_ecpri_udp_l2_udp_sw_irq_clr_0_port_p_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_udp_sw_irq_clr_0_port_p_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_udp_sw_irq_clr_0_port_p_u_v2;

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_UDP_L2_UDP_L2_FILTER
 *--------------------------------------------------------------------------*/

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_FILT_VLAN_ADDR_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 16;
  uint32_t reserved0 : 16;
} ecpri_qudp_hwio_def_ecpri_udp_l2_filt_vlan_addr_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_filt_vlan_addr_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_filt_vlan_addr_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_UDP_CLASSIFICATION_LIST_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 16;
  uint32_t reserved0 : 16;
} ecpri_qudp_hwio_def_ecpri_udp_l2_udp_classification_list_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_udp_classification_list_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_udp_classification_list_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_FILT_IP_DST_ADDR0_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_filt_ip_dst_addr0_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_filt_ip_dst_addr0_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_filt_ip_dst_addr0_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_FILT_IP_DST_ADDR1_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_filt_ip_dst_addr1_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_filt_ip_dst_addr1_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_filt_ip_dst_addr1_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_FILT_IP_DST_ADDR2_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_filt_ip_dst_addr2_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_filt_ip_dst_addr2_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_filt_ip_dst_addr2_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_FILT_IP_DST_ADDR3_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_filt_ip_dst_addr3_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_filt_ip_dst_addr3_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_filt_ip_dst_addr3_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_FILT_MAC_ADDRESS_LSB_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_filt_mac_address_lsb_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_filt_mac_address_lsb_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_filt_mac_address_lsb_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_FILT_MAC_ADDRESS_MSB_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 16;
  uint32_t reserved0 : 16;
} ecpri_qudp_hwio_def_ecpri_udp_l2_filt_mac_address_msb_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_filt_mac_address_msb_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_filt_mac_address_msb_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_FILT_MAC_ADDRESS_INFO_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t action : 3;
  uint32_t gsi_id : 2;
  uint32_t ring_id : 8;
  uint32_t reserved0 : 19;
} ecpri_qudp_hwio_def_ecpri_udp_l2_filt_mac_address_info_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_filt_mac_address_info_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_filt_mac_address_info_port_p_entry_n_u_v2;

/*----------------------------------------------------------------------------
 * MODULE: ECPRI_UDP_L2_UDP_L2_RAMS
 *--------------------------------------------------------------------------*/

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_INGRESS_NUM_ETH_UDP_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_num_eth_udp_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_num_eth_udp_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_num_eth_udp_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_INGRESS_FCS_ERR_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_fcs_err_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_fcs_err_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_fcs_err_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_INGRESS_IPV4_CS_ERROR_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_ipv4_cs_error_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_ipv4_cs_error_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_ipv4_cs_error_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_INGRESS_UDP_CS_ERROR_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_udp_cs_error_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_udp_cs_error_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_udp_cs_error_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_INGRESS_IP_FILTERED_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_ip_filtered_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_ip_filtered_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_ip_filtered_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_INGRESS_VLAN_FILTERED_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_vlan_filtered_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_vlan_filtered_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_vlan_filtered_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_INGRESS_SEC_ERR_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_sec_err_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_sec_err_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_sec_err_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_INGRESS_IP_LEN_ERR_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_ip_len_err_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_ip_len_err_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_ip_len_err_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_INGRESS_NUM_ETH_ECPRI_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_num_eth_ecpri_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_num_eth_ecpri_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_num_eth_ecpri_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_INGRESS_NUM_ETH_PTP_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_num_eth_ptp_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_num_eth_ptp_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_num_eth_ptp_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_INGRESS_NUM_ETH_OTHER_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_num_eth_other_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_num_eth_other_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_num_eth_other_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_INGRESS_NUM_UDP_ECPRI_OR_NFAPI_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_num_udp_ecpri_or_nfapi_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_num_udp_ecpri_or_nfapi_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_num_udp_ecpri_or_nfapi_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_INGRESS_NUM_UDP_PTP_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_num_udp_ptp_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_num_udp_ptp_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_num_udp_ptp_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_INGRESS_NUM_UDP_OTHER_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_num_udp_other_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_num_udp_other_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_ingress_num_udp_other_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_NUM_UDP_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_num_udp_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_num_udp_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_num_udp_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_NUM_ETH_ONLY_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_num_eth_only_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_num_eth_only_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_num_eth_only_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_NUM_BYPASSED_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_num_bypassed_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_num_bypassed_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_num_bypassed_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_MTU_ERR_PACKETS_PORT_p_LINK_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_mtu_err_packets_port_p_link_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_mtu_err_packets_port_p_link_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_mtu_err_packets_port_p_link_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_ETH_DST0_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_eth_dst0_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_eth_dst0_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_eth_dst0_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_ETH_SRC1_DST1_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t dst_msb : 16;
  uint32_t src_msb : 16;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_eth_src1_dst1_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_eth_src1_dst1_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_eth_src1_dst1_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_ETH_SRC0_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_eth_src0_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_eth_src0_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_eth_src0_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_VLAN_ETHERTYPE_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t ethertype : 16;
  uint32_t vlan_data : 16;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_vlan_ethertype_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_vlan_ethertype_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_vlan_ethertype_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_VPORT_MISC_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t vport : 8;
  uint32_t has_vlan : 1;
  uint32_t vport_action : 2;
  uint32_t rsvd : 4;
  uint32_t reserved0 : 17;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_vport_misc_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_vport_misc_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_vport_misc_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR0_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ip_src_addr0_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ip_src_addr0_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ip_src_addr0_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR1_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ip_src_addr1_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ip_src_addr1_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ip_src_addr1_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR2_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ip_src_addr2_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ip_src_addr2_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ip_src_addr2_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_IP_SRC_ADDR3_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ip_src_addr3_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ip_src_addr3_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ip_src_addr3_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_IP_DST_ADDR0_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ip_dst_addr0_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ip_dst_addr0_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ip_dst_addr0_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_IP_DST_ADDR1_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ip_dst_addr1_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ip_dst_addr1_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ip_dst_addr1_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_IP_DST_ADDR2_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ip_dst_addr2_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ip_dst_addr2_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ip_dst_addr2_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_IP_DST_ADDR3_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t value : 32;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ip_dst_addr3_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ip_dst_addr3_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_ip_dst_addr3_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_UDP_PORTS_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t src : 16;
  uint32_t dst : 16;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_udp_ports_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_udp_ports_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_udp_ports_port_p_entry_n_u_v2;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_UDP_L2_EGRESS_SA_TAG_IP_TOS_MISC_PORT_p_ENTRY_n
*/
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
  uint32_t sa_tag_data : 16;
  uint32_t tos : 8;
  uint32_t ip_type : 1;
  uint32_t is_ipsec : 1;
  uint32_t df_bit : 1;
  uint32_t calc_udp_cs : 1;
  uint32_t rsvd : 4;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_sa_tag_ip_tos_misc_port_p_entry_n_s_v2;

/* Union definition of register */
typedef union
{
  ecpri_qudp_hwio_def_ecpri_udp_l2_egress_sa_tag_ip_tos_misc_port_p_entry_n_s_v2 def;
  uint32_t value;
} ecpri_qudp_hwio_def_ecpri_udp_l2_egress_sa_tag_ip_tos_misc_port_p_entry_n_u_v2;


#endif /* __ECPRI_QUDP_HWIO_DEF_V2_H__ */
