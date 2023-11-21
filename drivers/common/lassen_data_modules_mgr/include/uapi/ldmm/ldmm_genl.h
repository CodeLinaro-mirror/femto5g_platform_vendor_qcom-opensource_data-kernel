/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _LDMM_GENL_H
#define _LDMM_GENL_H

/*
 * This header includes definitions that are shared with kernel space and user
 * space. This header would be put in a place visible to user space.
 */

#define LDMM_GENL_NAME "ldmm_mgmt"
#define LDMM_GENL_VERSION 1
#define LDMM_MC_GRP_NAME "ldmm_mcgrp"

/* Attributes */
enum genlldmm_attrs {
	LDMM_A_UNSPEC,
	LDMM_A_MSG,
	LDMM_QXDM_LOGGER_ATTR_GET_STATS_INFO,
    	LDMM_QXDM_LOGGER_ATTR_GET_CONFIG_INFO,
    	LDMM_QXDM_LOGGER_ATTR_LINK_CHANGE_NOTIFICATION,
    	__LDMM_A_MAX,
};

#define LDMM_A_MAX (__LDMM_A_MAX - 1)

/* Commands */
enum genlldmm_cmds {
	LDMM_CMD_UNSPEC,
	LDMM_CMD_FULT_MGMT_RCV,
	LDMM_QXDM_LOGGER_CMD_GET_STATS_INFO,
	LDMM_QXDM_LOGGER_CMD_GET_CONFIG_INFO,
	LDMM_QXDM_LOGGER_CMD_LINK_CHANGE_NOTIFICATION,
	__LDMM_CMD_MAX,
};

typedef enum ldmm_fault{
	LDMM_HIGH_BER_SET = 0,
	LDMM_HIGH_BER_CLR,
	LDMM_PCS_IF_UP,
	LDMM_PCS_IF_DOWN,
	LDMM_IF_UP,
	LDMM_IF_DOWN,
	LDMM_INVALID = 128,
}ldmm_fault_en;

#define FAULT_NUM_MASK 0x0FF0
#define FAULT_NUM_SHIFT 4

#define LINK_ID_MASK 0xF
#define LINK_ID_SHIFT 0

#define LDMM_SETFIELD_IN_REG(reg, val, shift, mask) \
        (reg |= ((val) << (shift)) & (mask))
#define LDMM_GETFIELD_FROM_REG(reg, shift, mask) \
        (((reg) & (mask)) >> (shift))

#define LDMM_CMD_MAX (__LDMM_CMD_MAX - 1)

#define HELLO_NUM 1234

#define MAX_LINKS_PER_PORT 4
#define TOTAL_LINKS 16
#define MAX_PORTS 5

typedef struct {
    int link_name;
    int link_status;
    int link_speed;
    /*4 bits of a number represent 4 lanes*/
    int lanes_mapped;
    /*lanes_speed corresponds to speed for lanes which are active and mapped to links
        speed for lanes which are not mapped is zero*/
    int lanes_speed;
} __attribute__ ((packed)) link_info;

typedef struct {
    int port_type;
    int port_enabled;
    int phy_eq_mode;
    int sfp_port_type;
    int port_config;
    int active_fec;
    int link_length_range;
    int active_links;
    link_info links[MAX_LINKS_PER_PORT];
} __attribute__ ((packed)) port_info;

typedef struct {
    int link_name;
    int EtherStatsOctets;
    int OctetsReceivedOK;
    int VLANReceivedOK;
    int InErrors;
    int InUCastPkts;
    int InMCastPkts;
    int InBCastPkts;
    int EtherStatsDrops;
    int EtherStatsPkts;
    int OctetsTransmittedOK;
    int VLANTransmittedOK;
    int OutErrors;
    int OutUCastPkts;
    int OutMCastPkts;
    int OutBCastPkts;
    int FIFO_0_TX_Count;
    int FIFO_1_TX_Count;
    int FIFO_2_TX_Count;
    int FIFO_3_TX_Count;
    int FIFO_4_TX_Count;
    int FIFO_5_TX_Count;
    int FIFO_6_TX_Count;
    int FIFO_7_TX_Count;
    int Software_TX_Errors;
    int Software_RX_Errors;
    int Software_TX_Packets;
    int Software_RX_Packets;
} __attribute__ ((packed)) stats_info;

typedef struct {
    port_info ports[MAX_PORTS];
} __attribute__ ((packed)) config_packet_info;

typedef struct {
    int total_active_links;
    stats_info stats[TOTAL_LINKS];
} __attribute__ ((packed)) stats_packet_info;


#endif /* _LDMM_GENL_H */
