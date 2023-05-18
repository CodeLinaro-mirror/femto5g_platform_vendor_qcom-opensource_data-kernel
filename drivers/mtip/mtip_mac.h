//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#ifndef _MTIP_MAC_H
#define _MTIP_MAC_H

#include <linux/slab.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/phylink.h>

#include "mtip.h"
#include "mtip_device.h"

/*
 * MTIP hardware register offsets
 */

#define MTIP_MAC_REVISION                         0x00000000
#define MTIP_MAC_SCRATCH                          0x00000004
#define MTIP_MAC_COMMAND_CONFIG                   0x00000008
#define MTIP_MAC_MAC_ADDR_0                       0x0000000C
#define MTIP_MAC_MAC_ADDR_1                       0x00000010
#define MTIP_MAC_FRM_LENGTH                       0x00000014
#define MTIP_MAC_RX_FIFO_SECTIONS                 0x0000001C
#define MTIP_MAC_TX_FIFO_SECTIONS                 0x00000020
#define MTIP_MAC_HASHTABLE_LOAD                   0x0000002C
#define MTIP_MAC_TX_IPG_LENGTH                    0x00000044
#define MTIP_MAC_CRC_MODE                         0x00000048
#define MTIP_MAC_CRC_INV_MASK                     0x0000004C
#define MTIP_MAC_XIF_MODE                         0x00000080

/*
 * MTIP register values to be written
 */
#define MTIP_MAC_RESET                            0x00001800

#define MTIP_MAC_INIT_COMMAND_CONFIG              0x00000800      // was 0x00002810

#define MTIP_MAC_COMMAND_CONFIG_ENABLE_TX         0x00000001
#define MTIP_MAC_COMMAND_CONFIG_ENABLE_RX         0x00000002
#define MTIP_MAC_COMMAND_CONFIG_SET_PROMISC       0x00000010

#define MTIP_MAC_INIT_FRAME_LENGTH                9216
#define MTIP_MAC_INIT_RX_FIFO_SECTIONS            0x00000002
#define MTIP_MAC_INIT_TX_FIFO_SECTIONS            0x00000004
#define MTIP_MAC_INIT_HASHTABLE_LOAD              0x0
#define MTIP_MAC_INIT_TX_IPG_LENGTH               0x0000000C
#define MTIP_MAC_INIT_CRC_MODE                    0x0
#define MTIP_MAC_INIT_CRC_INV_MASK                0xFFFFFFFF
#define MTIP_MAC_INIT_XIF_MODE_FOR_XGMII          0x00010101
#define MTIP_MAC_INIT_XIF_MODE_FOR_XLGMII         0x00010100


#define MTIP_MAC_HASHTABLE_SIZE                   64


// MAC Wrapper Register Offset
#define MTIP_MAC_WRAPPER_CALENDAR_CFG_REG_OFFSET         0x00000018

#define MTIP_MAC_WRAPPER_TX_TS1_REG_BASE_OFFSET          0x0000001C
#define MTIP_MAC_WRAPPER_TX_TS0_REG_BASE_OFFSET          0x00000020

#define MTIP_MAC_WRAPPER_TX_TS_REG_OFFSET                0x00000008

#define MTIP_MAC_WRAPPER_TX_TS_SEQ_NUM_REG_BASE_OFFSET   0x00000388
#define MTIP_MAC_WRAPPER_TX_TS_SEQ_NUM_LINK_REG_OFFSET   0x00000004

#define MTIP_MAC_WRAPPER_INTERRUPT_STAT_REG_OFFSET       0x00000250
#define MTIP_MAC_WRAPPER_INTERRUPT_MASK_REG_OFFSET       0x00000254
#define MTIP_MAC_WRAPPER_INTERRUPT_CLR_REG_OFFSET        0x00000258
#define MTIP_MAC_WRAPPER_INTERRUPT_OFFSET                0x0000000C

#define MTIP_MAC_WRAPPER_INTERRUPT_SUMMARY_REG_OFFSET    0x00000280

#define MTIP_MAC_WRAPPER_TX_AMF_CFG_REG_OFFSET           0x00000290
#define MTIP_MAC_WRAPPER_GLOBAL_TIMER_EN_REG_OFFSET      0x00000050
#define MTIP_MAC_WRAPPER_TSC_OFFSET_REG_OFFSET           0x00000284

#define MTIP_MAC_WRAPPER_CSR_CONFIG_OFFSET               0x00000000
#define MTIP_MAC_WRAPPER_PCS_MODE_SET_OFFSET             0x00000010
#define MTIP_MAC_WRAPPER_SERDES_MUX_CFG_OFFSET           0x0000004C

#define MTIP_MAC_WRAPPER_CORE_STATUS_REG_OFFSET          0x00000004

// MAC Wrapper Register values
#define MTIP_MAC_WRAPPER_CALENDAR_CFG_REG_VAL_4_LINKS    0x00001111
#define MTIP_MAC_WRAPPER_CALENDAR_CFG_REG_VAL_2_LINKS    0x00000011
#define MTIP_MAC_WRAPPER_CALENDAR_CFG_REG_VAL_1_LINKS    0x00000001

#define MTIP_MAC_WRAPPER_TX_AMF_CFG_REG_VAL_4_LINKS      0x26262626
#define MTIP_MAC_WRAPPER_TX_AMF_CFG_REG_VAL_2_LINKS      0x02022626
#define MTIP_MAC_WRAPPER_TX_AMF_CFG_REG_VAL_1_LINKS      0x02020226

#define MTIP_MAC_WRAPPER_PCS_MODE_4X25G_RSFEC_ENABLE_VAL   0x0000003F
#define MTIP_MAC_WRAPPER_PCS_MODE_4X25G_RSFEC_DISABLE_VAL  0x00000000

#define MTIP_MAC_WRAPPER_CSR_CFG_REG_BASE_VAL              0x00003C00

#define MTIP_MAC_WRAPPER_PCS_MODE_FEC91_ENA_BASE         0
#define MTIP_MAC_WRAPPER_PCS_MODE_FEC91_1LANE_BASE       4
#define MTIP_MAC_WRAPPER_PCS_MODE_KP_MODE_IN_BASE        6
#define MTIP_MAC_WRAPPER_PCS_MODE_FEC91_LL_IN_BASE       12
#define MTIP_MAC_WRAPPER_PCS_MODE_RXLAUI_ENA_IN_BASE     16
#define MTIP_MAC_WRAPPER_PCS_MODE_PCS100_ENA_IN_BASE     18
#define MTIP_MAC_WRAPPER_PCS_MODE_PCS10_ENA_BASE         25

// This is the TSC Offset register value
// To be set after BU is complete
#define MTIP_MAC_WRAPPER_TSC_OFFSET_REG_VAL       MTIP_TSC_OFFSET_VAL

#define MTIP_MAC_WRAPPER_GLOBAL_TIMER_EN_REG_VAL  0x00000001

/* Set of MAC Interrupt Status Register bits */
#define MTIP_MAC_INTERRUPT_PTP_TX_INTR            0x00000040
#define MTIP_MAC_INTERRUPT_LINK_DOWN_INTR         0x00100000
#define MTIP_MAC_INTERRUPT_LINK_UP_INTR           0x00200000
#define MTIP_MAC_INTERRUPT_HI_BER_INTR            0x01000000
#define MTIP_MAC_INTERRUPT_LINE_FAULT_INTR        0x00000001
#define MTIP_MAC_INTERRUPT_REMOTE_FAULT_INTR      0x00000002
#define MTIP_MAC_INTERRUPT_LOCAL_FAULT_INTR       0x00000004


/*
 * Other configuration items
 */
#define MTIP_MAC_RESET_DELAY_MSECS                10

#define MTIP_MAC_MAX_JUMBO_PKT_SIZE	     (9 * 1024)
#define MTIP_MAC_MAX_ETH_FRAME_SIZE	      MTIP_MAC_MAX_JUMBO_PKT_SIZE
#define MTIP_MAC_MIN_ETH_FRAME_SIZE	     68

/*
 * structures for bottom half handling of interrupts
 */
struct mtip_process_timestamp_task
{
    u32 link_index;
    u32 timestamp_secs;
    u32 timestamp_nsecs;
    u8  ts_seq_num;
};

void mtip_mac_initialize(struct mtip_netdev_priv* priv);

void mtip_mac_finalize(void __iomem *mac_base_addr, unsigned int irq,
                            const char* name, void* dev_id);

void mtip_mac_wrapper_init(struct mtip_port_device_info* port_device);

void mtip_mac_wrapper_pcs_mode_control(struct mtip_port_device_info* port_device);

void mtip_mac_enable_tx_rx(u32 link_index);
void mtip_mac_disable_tx_rx(u32 link_index);

void mtip_mac_set_frame_length(struct mtip_netdev_priv* priv, 
                                         u32 frame_length);
u32 mtip_mac_get_frame_length(u32 port_number, u32 link_number);

void mtip_mac_set_mac_address(struct mtip_netdev_priv* priv, 
                                         struct sockaddr *saddr);
//void mtip_mac_get_mac_address_by_device(u32 port_device_index, u32 link_device_index, uint8_t saddr[]);
//void mtip_mac_set_mac_address_by_device(u32 port_device_index, u32 link_device_index, uint8_t saddr[]);

void mtip_mac_get_mac_address_by_link_index(u32 link_index, uint8_t saddr[]);
void mtip_mac_set_mac_address_by_link_index(u32 link_index, uint8_t saddr[]);

int mtip_mac_set_promisc_mode(struct mtip_netdev_priv *priv, bool mode);
void mtip_mac_set_hashtable_entry(struct mtip_netdev_priv *priv, u8 entry_address, u8 val);

void mtip_mac_wrapper_register_irq(struct device *dev, unsigned int irq,
                              const char* dev_name, void* devptr);

void mtip_mac_read_timestamp(u32 link_index, u32* timestamp_secs, u32* timestamp_nsecs);
void mtip_mac_read_ts_seq_num(u32 link_index, u8* ts_seq);

void mtip_mac_set_interrupt_mask(u32 link_index);
void mtip_mac_clear_interrupt_mask(u32 link_index);
void mtip_mac_set_link_status_interrupt_mask(u32 link_index);
void mtip_mac_clear_link_status_interrupt_mask(u32 link_index);
u32 mtip_mac_get_interrupt_mask(u32 link_index);

bool mtip_mac_wrapper_get_link_status(u32 link_index);

// functions to enable/disable rsfec for 25g mode
void mtip_mac_wrapper_enable_rsfec_for_25g_mode(struct mtip_port_device_info* port_device);
void mtip_mac_wrapper_disable_rsfec_for_25g_mode(struct mtip_port_device_info* port_device);

#endif // _MTIP_MAC_H
