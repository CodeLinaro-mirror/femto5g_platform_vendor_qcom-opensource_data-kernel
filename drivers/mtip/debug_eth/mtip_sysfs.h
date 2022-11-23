/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/**
  @file mtip_sysfs.h
  @brief SYS FS header for Debug ETH MAC Driver.

  This file defines the SYS FS nodes interface header for Debug Ethernet 
  MAC driver.
*/

#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/netdevice.h>
#include <linux/slab.h>
#include <linux/types.h>

#define STREAM_FIFO_THRESHOLD_0 0x00000000
#define STREAM_FIFO_THRESHOLD_1 0x00000004
#define STREAM_FIFO_THRESHOLD_2 0x00000008
#define STREAM_FIFO_THRESHOLD_3 0x0000000C
#define STREAM_FIFO_THRESHOLD_4 0x00000010
#define L2_SA_ADDR_HI_0 0x000000E0
#define L2_SA_ADDR_HI_1 0x000000E4
#define L2_SA_ADDR_HI_2 0x000000E8
#define L2_SA_ADDR_HI_3 0x000000EC
#define L2_SA_ADDR_HI_4 0x000000F0
#define L2_SA_ADDR_HI_5 0x000000F4
#define L2_SA_ADDR_HI_6 0x000000F8
#define L2_SA_ADDR_HI_7 0x000000FC
#define L2_SA_ADDR_HI_8 0x00000100
#define L2_SA_ADDR_LO_0 0x000000BC
#define L2_SA_ADDR_LO_1 0x000000C0
#define L2_SA_ADDR_LO_2 0x000000C4
#define L2_SA_ADDR_LO_3 0x000000C8
#define L2_SA_ADDR_LO_4 0x000000CC
#define L2_SA_ADDR_LO_5 0x000000D0
#define L2_SA_ADDR_LO_6 0x000000D4
#define L2_SA_ADDR_LO_7 0x000000D8
#define L2_SA_ADDR_LO_8 0x000000DC
#define L2_DA_ADDR_HI_0 0x00000098
#define L2_DA_ADDR_HI_1 0x0000009C
#define L2_DA_ADDR_HI_2 0x000000A0
#define L2_DA_ADDR_HI_3 0x000000A4
#define L2_DA_ADDR_HI_4 0x000000A8
#define L2_DA_ADDR_HI_5 0x000000AC
#define L2_DA_ADDR_HI_6 0x000000B0
#define L2_DA_ADDR_HI_7 0x000000B4
#define L2_DA_ADDR_HI_8 0x000000B8
#define L2_DA_ADDR_LO_0 0x00000074
#define L2_DA_ADDR_LO_1 0x00000078
#define L2_DA_ADDR_LO_2 0x0000007C
#define L2_DA_ADDR_LO_3 0x00000080
#define L2_DA_ADDR_LO_4 0x00000084
#define L2_DA_ADDR_LO_5 0x00000088
#define L2_DA_ADDR_LO_6 0x0000008C
#define L2_DA_ADDR_LO_7 0x00000090
#define L2_DA_ADDR_LO_8 0x00000094
#define STREAM_PKT_CNT_0 0x0000015C
#define STREAM_PKT_CNT_1 0x00000160
#define STREAM_PKT_CNT_2 0x00000164
#define STREAM_PKT_CNT_3 0x00000168
#define STREAM_PKT_CNT_4 0x0000016C
#define PACKET_FIFO1_PKT_CNT 0x00000170
#define PACKET_FIFO2_PKT_CNT 0x00000174
#define PACKET_FIFO3_PKT_CNT 0x00000178
#define VLAN_TAG_0 0x00000104
#define VLAN_TAG_1 0x00000108
#define VLAN_TAG_2 0x0000010C
#define VLAN_TAG_3 0x00000110
#define VLAN_TAG_4 0x00000114
#define VLAN_TAG_5 0x00000118
#define VLAN_TAG_6 0x0000011C
#define VLAN_TAG_7 0x00000120
#define VLAN_TAG_8 0x00000124
#define ETH_DBG_IPV4_SA_0 0x00000134
#define ETH_DBG_IPV4_SA_1 0x00000138
#define ETH_DBG_IPV4_SA_2 0x0000013C
#define ETH_DBG_IPV4_DA_0 0x00000128
#define ETH_DBG_IPV4_DA_1 0x0000012C
#define ETH_DBG_IPV4_DA_2 0x00000130
#define DBG_UDP_SP_DP_0 0x00000140
#define DBG_UDP_SP_DP_1 0x00000144
#define DBG_UDP_SP_DP_2 0x00000148
#define STREAM_FIFO_ADDR_MIN_0 0x0000002C
#define STREAM_FIFO_ADDR_MIN_1 0x00000030
#define STREAM_FIFO_ADDR_MIN_2 0x00000034
#define STREAM_FIFO_ADDR_MIN_3 0x00000038
#define STREAM_FIFO_ADDR_MIN_4 0x0000003C
#define STREAM_FIFO_ADDR_MAX_0 0x00000040
#define STREAM_FIFO_ADDR_MAX_1 0x00000044
#define STREAM_FIFO_ADDR_MAX_2 0x00000048
#define STREAM_FIFO_ADDR_MAX_3 0x0000004C
#define STREAM_FIFO_ADDR_MAX_4 0x00000050
#define PACKET_FIFO_ADDR_MIN 0x00000064
#define PACKET_FIFO_ADDR_MAX 0x00000068
#define STREAM_FIFO_TIMER_0 0x00000018
#define STREAM_FIFO_TIMER_1 0x0000001C
#define STREAM_FIFO_TIMER_2 0x00000020
#define STREAM_FIFO_TIMER_3 0x00000024
#define STREAM_FIFO_TIMER_4 0x00000028
#define ERROR_INTR_STAT 0x0000019C
#define ERROR_INTR_MASK 0x000001A4

#define DBG_ETH_DBG_SW_FLUSH 0x00000014
#define DBG_ETH_DBG_FIFO_STATUS 0x00000158
#define FLUSH_DONE_PACKET 0x101C00
#define FLUSH_DONE_STREAM 0x10001F
#define MAXIMUM_PACKET_SIZE 1500
#define BYTE_PER_WATERMARK_UNIT 32
#define VLAN_TAG_ENABLED_BIT 16
#define MAX_FIFO_COUNT 8
#define MAX_PACKET_FIFO_COUNT 3
#define MAX_STREAM_FIFO_COUNT 5
#define EBUSY 16 /* Device or resource busy */
#define Kobj_Name_L2_Info_Size 8
#define Kobj_Name_L3_Info_Size 8
#define Kobj_Name_FIFO_Size 7
#define L2_size 5
#define L3_size 3

struct RootDirectory {
  unsigned int enabled;
};

struct L2Headers {
  u64 saddr[6];
  u64 daddr[6];
};

struct L3Headers {
  u64 saddr[4];
  u64 daddr[4];
  u64 sport;
  u64 dport;
};

struct StreamingFifo {
  unsigned int status;
  unsigned int flush;
  unsigned int txcount;
  unsigned int AddrRange_Start;
  unsigned int AddrRange_End;
  unsigned int OverFlowInterrupt;
  unsigned int Threshold;
  unsigned int Timeout;
  u64 vlanID;
};

struct PacketFifo {
  unsigned int status;
  unsigned int flush;
  unsigned int txcount;
  unsigned int AddrRange_Start;
  unsigned int AddrRange_End;
  unsigned int OverFlowInterrupt;
  u64 vlanID;
};

enum FIFOS {
  FIFO_0 = 0,
  FIFO_1 = 1,
  FIFO_2 = 2,
  FIFO_3 = 3,
  FIFO_4 = 4,
  FIFO_5 = 5,
  FIFO_6 = 6,
  FIFO_7 = 7
};

void set_debug_base_address(void __iomem *addr);
void __iomem *get_debug_base_address(void);
void mtip_sysfs_mac_link_status(int status);
void mtip_sysfs_isr_work_thread(struct work_struct *work);
int setup_sysfs(void __iomem *addr, struct device *dev);
void setup_AXI_Address_Range(int index);
void setup_StreamingFIFO(int index);
ssize_t sysfs_show_enabled(struct kobject *kobj, struct kobj_attribute *attr,
                           char *buf);
ssize_t sysfs_show_saddr(struct kobject *kobj, struct kobj_attribute *attr,
                         char *buf);
ssize_t sysfs_store_saddr(struct kobject *kobj, struct kobj_attribute *attr,
                          const char *buf, size_t count);
ssize_t sysfs_show_daddr(struct kobject *kobj, struct kobj_attribute *attr,
                         char *buf);
ssize_t sysfs_store_daddr(struct kobject *kobj, struct kobj_attribute *attr,
                          const char *buf, size_t count);
ssize_t sysfs_show_sport(struct kobject *kobj, struct kobj_attribute *attr,
                         char *buf);
ssize_t sysfs_store_sport(struct kobject *kobj, struct kobj_attribute *attr,
                          const char *buf, size_t count);
ssize_t sysfs_show_dport(struct kobject *kobj, struct kobj_attribute *attr,
                         char *buf);
ssize_t sysfs_store_dport(struct kobject *kobj, struct kobj_attribute *attr,
                          const char *buf, size_t count);
ssize_t sysfs_show_status(struct kobject *kobj, struct kobj_attribute *attr,
                          char *buf);
int sysfs_store_flush_register_set(int index);
ssize_t sysfs_store_flush(struct kobject *kobj, struct kobj_attribute *attr,
                          const char *buf, size_t count);
ssize_t sysfs_show_txcount(struct kobject *kobj, struct kobj_attribute *attr,
                           char *buf);
ssize_t sysfs_show_AddrRange_Start(struct kobject *kobj,
                                   struct kobj_attribute *attr, char *buf);
ssize_t sysfs_store_AddrRange_Start(struct kobject *kobj,
                                    struct kobj_attribute *attr,
                                    const char *buf, size_t count);
ssize_t sysfs_show_AddrRange_End(struct kobject *kobj,
                                 struct kobj_attribute *attr, char *buf);
ssize_t sysfs_store_AddrRange_End(struct kobject *kobj,
                                  struct kobj_attribute *attr, const char *buf,
                                  size_t count);
ssize_t sysfs_show_OverFlowInterrupt(struct kobject *kobj,
                                     struct kobj_attribute *attr, char *buf);
ssize_t sysfs_show_Threshold(struct kobject *kobj, struct kobj_attribute *attr,
                             char *buf);
ssize_t sysfs_store_Threshold(struct kobject *kobj, struct kobj_attribute *attr,
                              const char *buf, size_t count);
ssize_t sysfs_show_Timeout(struct kobject *kobj, struct kobj_attribute *attr,
                           char *buf);
ssize_t sysfs_store_Timeout(struct kobject *kobj, struct kobj_attribute *attr,
                            const char *buf, size_t count);
ssize_t sysfs_show_vlanID(struct kobject *kobj, struct kobj_attribute *attr,
                          char *buf);
int sysfs_store_vlanID_Register_Set(const char *buf, u64 *FIFO_vlanID, u32 reg1,
                                    u32 reg2);
ssize_t sysfs_store_vlanID(struct kobject *kobj, struct kobj_attribute *attr,
                           const char *buf, size_t count);
int remove_sysfs(struct kobject *kobj_ref, struct kobj_attribute *attr);
int sysfs_create_generic_dir_structure(struct kobject *kobj_ref);
int sysfs_create_L2headers(struct kobject *kobj_ref);
int sysfs_create_L3headers(struct kobject *kobj_ref);
int sysfs_create_StreamingFifo(struct kobject *kobj_ref);
int sysfs_create_PacketFifo(struct kobject *kobj_ref);
unsigned int is_delim(char c, char *delim);
char *mtip_sysfs_strtok(char *srcString, char *delim);
