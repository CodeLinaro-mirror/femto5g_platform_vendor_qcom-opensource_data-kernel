/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/**
  @file mtip_sysfs.c
  @brief SYS FS for Debug ETH MAC Driver.

  This file implements the SYS FS nodes interface for Debug Ethernet MAC driver
*/

#include <linux/bitrev.h>
#include <linux/delay.h>
#include <linux/dma-mapping.h>
#include <linux/errno.h>
#include <linux/etherdevice.h>
#include <linux/fcntl.h>
#include <linux/gfp.h>
#include <linux/in.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/netdevice.h>
#include <linux/platform_device.h>
#include <linux/skbuff.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/types.h>

#include <linux/errno.h>     /* error codes */
#include <linux/interrupt.h> /* mark_bh */
#include <linux/kernel.h>    /* printk() */
#include <linux/sched.h>
#include <linux/slab.h>  /* kmalloc() */
#include <linux/types.h> /* size_t */

#include <linux/etherdevice.h> /* eth_type_trans */
#include <linux/in.h>
#include <linux/ip.h>        /* struct iphdr */
#include <linux/netdevice.h> /* struct device, and other headers */
#include <linux/of.h>
#include <linux/skbuff.h>
#include <linux/tcp.h> /* struct tcphdr */

#include "mtip.h"
#include "mtip_client.h"
#include "mtip_device.h"
#include "mtip_dma.h"
#include "mtip_hashmap.h"
#include "mtip_mac.h"
#include "mtip_mdio.h"
#include "mtip_platform.h"
#include "mtip_sysfs.h"

#include <linux/kobject.h>
#include <linux/sysfs.h> /* sysfs addition*/

#define MIN(a,b) ((a < b) ? a : b)

void __iomem *debug_port_base_address;

struct kobject *kobj_root, *kobj_ref_L3L2headers, *kobj_ref_L2headers,
    *kobj_ref_L3headers, *kobj_FIFO_0, *kobj_FIFO_1, *kobj_FIFO_2, *kobj_FIFO_3,
    *kobj_FIFO_4, *kobj_FIFO_5, *kobj_FIFO_6, *kobj_FIFO_7;

struct RootDirectory root = {.enabled = 1};
struct L2Headers L2 = {.saddr = {0}, .daddr = {0}};
struct L3Headers L3 = {.saddr = {0}, .daddr = {0}, .sport = 0, .dport = 0};
struct StreamingFifo F0 = {.status = 0,
                           .flush = 0,
                           .txcount = 0,
                           .AddrRange_Start = 0,
                           .AddrRange_End = 0,
                           .OverFlowInterrupt = 0,
                           .Threshold = 1500,
                           .Timeout = 0,
                           .vlanID = 0};
struct StreamingFifo F1 = {.status = 0,
                           .flush = 0,
                           .txcount = 0,
                           .AddrRange_Start = 0,
                           .AddrRange_End = 0,
                           .OverFlowInterrupt = 0,
                           .Threshold = 1000,
                           .Timeout = 0,
                           .vlanID = 0};
struct StreamingFifo F2 = {.status = 0,
                           .flush = 0,
                           .txcount = 0,
                           .AddrRange_Start = 0,
                           .AddrRange_End = 0,
                           .OverFlowInterrupt = 0,
                           .Threshold = 1000,
                           .Timeout = 0,
                           .vlanID = 0};
struct StreamingFifo F3 = {.status = 0,
                           .flush = 0,
                           .txcount = 0,
                           .AddrRange_Start = 0,
                           .AddrRange_End = 0,
                           .OverFlowInterrupt = 0,
                           .Threshold = 1000,
                           .Timeout = 0,
                           .vlanID = 0};
struct StreamingFifo F4 = {.status = 0,
                           .flush = 0,
                           .txcount = 0,
                           .AddrRange_Start = 0,
                           .AddrRange_End = 0,
                           .OverFlowInterrupt = 0,
                           .Threshold = 1000,
                           .Timeout = 0,
                           .vlanID = 0};
struct PacketFifo F5 = {.status = 0,
                        .flush = 0,
                        .txcount = 0,
                        .AddrRange_Start = 0,
                        .AddrRange_End = 0,
                        .OverFlowInterrupt = 0,
                        .vlanID = 0};
struct PacketFifo F6 = {.status = 0,
                        .flush = 0,
                        .txcount = 0,
                        .AddrRange_Start = 0,
                        .AddrRange_End = 0,
                        .OverFlowInterrupt = 0,
                        .vlanID = 0};
struct PacketFifo F7 = {.status = 0,
                        .flush = 0,
                        .txcount = 0,
                        .AddrRange_Start = 0,
                        .AddrRange_End = 0,
                        .OverFlowInterrupt = 0,
                        .vlanID = 0};

// Sysfs Attribute Definitions
struct kobj_attribute enabled_attr =
    __ATTR(enabled, 0440, sysfs_show_enabled, NULL);
struct kobj_attribute saddr_attr =
    __ATTR(saddr, 0660, sysfs_show_saddr, sysfs_store_saddr);
struct kobj_attribute daddr_attr =
    __ATTR(daddr, 0660, sysfs_show_daddr, sysfs_store_daddr);
struct kobj_attribute sport_attr =
    __ATTR(sport, 0660, sysfs_show_sport, sysfs_store_sport);
struct kobj_attribute dport_attr =
    __ATTR(dport, 0660, sysfs_show_dport, sysfs_store_dport);
struct kobj_attribute status_attr =
    __ATTR(status, 0440, sysfs_show_status, NULL);
struct kobj_attribute flush_attr = __ATTR(flush, 0220, NULL, sysfs_store_flush);
struct kobj_attribute txcount_attr =
    __ATTR(txcount, 0440, sysfs_show_txcount, NULL);
struct kobj_attribute AddrRange_attr_start =
    __ATTR(AddrRangeStart, 0660, sysfs_show_AddrRange_Start,
           sysfs_store_AddrRange_Start);
struct kobj_attribute AddrRange_attr_end = __ATTR(
    AddrRangeEnd, 0660, sysfs_show_AddrRange_End, sysfs_store_AddrRange_End);
struct kobj_attribute OverFlowInterrupt_attr =
    __ATTR(OverFlowInterrupt, 0440, sysfs_show_OverFlowInterrupt, NULL);
struct kobj_attribute Threshold_attr =
    __ATTR(Threshold, 0660, sysfs_show_Threshold, sysfs_store_Threshold);
struct kobj_attribute Timeout_attr =
    __ATTR(Timeout, 0660, sysfs_show_Timeout, sysfs_store_Timeout);
struct kobj_attribute vlanID_attr =
    __ATTR(vlanID, 0660, sysfs_show_vlanID, sysfs_store_vlanID);

void set_debug_base_address(void __iomem *addr) {
  debug_port_base_address = addr;
  CSMLOGINFO("Debug port base address is %llx", debug_port_base_address);
}

void __iomem *get_debug_base_address(void) { return debug_port_base_address; }

void mtip_sysfs_mac_link_status(int status) {

  if (!root.enabled)
    return;

  if (status == true) {
    F0.status = 1;
    F1.status = 1;
    F2.status = 1;
    F3.status = 1;
    F4.status = 1;
    F5.status = 1;
    F6.status = 1;
    F7.status = 1;
  } else if (status == false) {
    F0.status = 0;
    F1.status = 0;
    F2.status = 0;
    F3.status = 0;
    F4.status = 0;
    F5.status = 0;
    F6.status = 0;
    F7.status = 0;
  }
}

void mtip_sysfs_isr_work_thread(struct work_struct *work) {
  int mask_val = 0;
  int set_bit = 1;
  int i;
  int *overflow_ptr;
  int fifo_interrupt_offset = 10;
  int Overflow_Interrupt_Array[] = {F0.OverFlowInterrupt, F1.OverFlowInterrupt,
                                    F2.OverFlowInterrupt, F3.OverFlowInterrupt,
                                    F4.OverFlowInterrupt, F5.OverFlowInterrupt,
                                    F6.OverFlowInterrupt, F7.OverFlowInterrupt};

  mask_val = (u32)ioread32(get_debug_base_address() + ERROR_INTR_MASK);

  for (i = FIFO_0 + fifo_interrupt_offset; i <= FIFO_7 + fifo_interrupt_offset;
       i++) {
    if (mask_val & (set_bit << i)) {
      overflow_ptr = &Overflow_Interrupt_Array[i - fifo_interrupt_offset];
      *overflow_ptr = 1;
    }
  }
}

int setup_sysfs(void __iomem *addr, struct device *dev) {
  // setup the sysfs filesystem
  int index;
  CSMLOGERR("sysfs filesystem initialization called\n");

  set_debug_base_address(addr);

  /* creating the directory structure in /sys/kernel */
  kobj_root = kobject_create_and_add("debugeth", kernel_kobj);
  sysfs_create_generic_dir_structure(kobj_root);

  // Enable Debug FS
  root.enabled = 1;

  // L2L3 header info
  kobj_ref_L3L2headers = kobject_create_and_add("L2L3HeaderInfo", kobj_root);
  kobj_ref_L2headers = kobject_create_and_add("L2_Info", kobj_ref_L3L2headers);
  kobj_ref_L3headers = kobject_create_and_add("L3_Info", kobj_ref_L3L2headers);
  sysfs_create_L2headers(kobj_ref_L2headers);
  sysfs_create_L3headers(kobj_ref_L3headers);

  // Fifo queues
  kobj_FIFO_0 = kobject_create_and_add("FIFO_0", kobj_root);
  sysfs_create_StreamingFifo(kobj_FIFO_0);
  kobj_FIFO_1 = kobject_create_and_add("FIFO_1", kobj_root);
  sysfs_create_StreamingFifo(kobj_FIFO_1);
  kobj_FIFO_2 = kobject_create_and_add("FIFO_2", kobj_root);
  sysfs_create_StreamingFifo(kobj_FIFO_2);
  kobj_FIFO_3 = kobject_create_and_add("FIFO_3", kobj_root);
  sysfs_create_StreamingFifo(kobj_FIFO_3);
  kobj_FIFO_4 = kobject_create_and_add("FIFO_4", kobj_root);
  sysfs_create_StreamingFifo(kobj_FIFO_4);
  kobj_FIFO_5 = kobject_create_and_add("FIFO_5", kobj_root);
  sysfs_create_PacketFifo(kobj_FIFO_5);
  kobj_FIFO_6 = kobject_create_and_add("FIFO_6", kobj_root);
  sysfs_create_PacketFifo(kobj_FIFO_6);
  kobj_FIFO_7 = kobject_create_and_add("FIFO_7", kobj_root);
  sysfs_create_PacketFifo(kobj_FIFO_7);

  // SysFS Directory Structure completed
  for (index = 0; index < MAX_STREAM_FIFO_COUNT; index++) {
    setup_StreamingFIFO(index);
  }

  for (index = 0; index <= MAX_STREAM_FIFO_COUNT; index++) {
    setup_AXI_Address_Range(index);
  }

  return -1;
}

/*
Function responsible for the static allocation of the AXI Address Range of the
corrseponding FIFO's at the beginning. */
void setup_AXI_Address_Range(int index) {

  unsigned int AXI_START_ARRAY[] = {F0.AddrRange_Start, F1.AddrRange_Start,
                                    F2.AddrRange_Start, F3.AddrRange_Start,
                                    F4.AddrRange_Start, F5.AddrRange_Start};
  unsigned int AXI_END_ARRAY[] = {F0.AddrRange_End, F1.AddrRange_End,
                                  F2.AddrRange_End, F3.AddrRange_End,
                                  F4.AddrRange_End, F5.AddrRange_End};
  unsigned int AXI_REG_START[] = {
      STREAM_FIFO_ADDR_MIN_0, STREAM_FIFO_ADDR_MIN_1, STREAM_FIFO_ADDR_MIN_2,
      STREAM_FIFO_ADDR_MIN_3, STREAM_FIFO_ADDR_MIN_4, PACKET_FIFO_ADDR_MIN};
  unsigned int AXI_REG_END[] = {STREAM_FIFO_ADDR_MAX_0, STREAM_FIFO_ADDR_MAX_1,
                                STREAM_FIFO_ADDR_MAX_2, STREAM_FIFO_ADDR_MAX_3,
                                STREAM_FIFO_ADDR_MAX_4, PACKET_FIFO_ADDR_MAX};

  // Setup AXI Address Range for the FIFOS
  unsigned int i = 0;
  F0.AddrRange_Start = 0x0;
  F0.AddrRange_End = 0x1000;
  F1.AddrRange_Start = 0x1000;
  F1.AddrRange_End = 0x2000;
  F2.AddrRange_Start = 0x2000;
  F2.AddrRange_End = 0x3000;
  F3.AddrRange_Start = 0x3000;
  F3.AddrRange_End = 0x4000;
  F4.AddrRange_Start = 0x4000;
  F4.AddrRange_End = 0x5000;
  F5.AddrRange_Start = 0x5000;
  F5.AddrRange_End = 0x6000;

  while (i <= index) {
    iowrite32(AXI_START_ARRAY[i], debug_port_base_address + AXI_REG_START[i]);
    iowrite32(AXI_END_ARRAY[i], debug_port_base_address + AXI_REG_END[i]);
    i++;
  }
}

/* Common Function to setup the Streaming FIFO's with a non-zero threshold value
 * initially and also set the registers dynamically later on via the
 * store_threshold endpoint. */
void setup_StreamingFIFO(int index) {
  int value = 0;
  unsigned int fifo_registers[] = {
      STREAM_FIFO_THRESHOLD_0, STREAM_FIFO_THRESHOLD_1, STREAM_FIFO_THRESHOLD_2,
      STREAM_FIFO_THRESHOLD_3, STREAM_FIFO_THRESHOLD_4};
  unsigned int STREAM_FIFO_THRESHOLD_ARRAY[] = {
      F0.Threshold, F1.Threshold, F2.Threshold, F3.Threshold, F4.Threshold};
  unsigned int STREAM_TIMEOUT_ARRAY[] = {F0.Timeout, F1.Timeout, F2.Timeout,
                                         F3.Timeout, F4.Timeout};
  unsigned int stream_fifo_registers[] = {
      STREAM_FIFO_TIMER_0, STREAM_FIFO_TIMER_1, STREAM_FIFO_TIMER_2,
      STREAM_FIFO_TIMER_3, STREAM_FIFO_TIMER_4};

  CSMLOGINFO("Setup Streaming FIFO Called \n");
  if (STREAM_FIFO_THRESHOLD_ARRAY[index] <= MAXIMUM_PACKET_SIZE) {
    value |= ((STREAM_FIFO_THRESHOLD_ARRAY[index] / BYTE_PER_WATERMARK_UNIT) &
              GENMASK(15, 0));
    iowrite32(value, debug_port_base_address + fifo_registers[index]);
  }
  iowrite32(STREAM_TIMEOUT_ARRAY[index],
            debug_port_base_address + stream_fifo_registers[index]);
  CSMLOGINFO("Setup Streaming FIFO Ends \n");
}

ssize_t sysfs_show_enabled(struct kobject *kobj, struct kobj_attribute *attr,
                           char *buf) {
  int val;
  CSMLOGINFO(KERN_INFO " Reading - sysfs show func...%s \n", kobj->name);
  val = snprintf(buf, sizeof(root.enabled), "%d", root.enabled);
  CSMLOGINFO(KERN_INFO " Sysfs show func returned %d \n", val);
  return val;
}

/*
Source Address Endpoints – (/sys/kernel/debugeth/L2L3HeaderInfo/L3_Info/saddr)
Description: This endpoint is responsible for the setting up of the Source
Address (saddr) value in the i-th FIFO’s. Access Type: Read/Write Format: String
Example Write:
For L3 Headers, if the source address is 255.255.192.100,
# echo 255.255.192.100 > /sys/kernel/debugeth/L2L3HeaderInfo/L3_Info/saddr
Example Read:
# cat /sys/kernel/debugeth/L2L3HeaderInfo/L3_Info/saddr (Expected output is
255.255.192.100.)
*/
ssize_t sysfs_show_saddr(struct kobject *kobj, struct kobj_attribute *attr,
                         char *buf) {
  int val = -1;
  char L3_show_value[100] = "";
  char L2_show_value[100] = "";
  char tmp_L3[4][20];
  char tmp_L2[6][20];
  int i;

  CSMLOGINFO(KERN_INFO " Reading - sysfs show func...%s \n", kobj->name);
  if (!strncmp(kobj->name, "L2_Info", Kobj_Name_L2_Info_Size)) {
    for (i = 0; i <= L2_size; i++) {
      snprintf(tmp_L2[i], sizeof(L2.saddr), "%x", L2.saddr[i]);
      strlcat(L2_show_value, tmp_L2[i], sizeof(L2_show_value));
      if (i != L2_size)
        strlcat(L2_show_value, ":", sizeof(L2_show_value));
    }
    val = snprintf(buf, sizeof(L2_show_value), "%s", L2_show_value);
  } else if (!strncmp(kobj->name, "L3_Info", Kobj_Name_L3_Info_Size)) {
    for (i = 0; i <= L3_size; i++) {
      snprintf(tmp_L3[i], sizeof(L3.saddr), "%d", L3.saddr[L3_size - i]);
      strlcat(L3_show_value, tmp_L3[i], sizeof(L3_show_value));
      if (i != L3_size)
        strlcat(L3_show_value, ".", sizeof(L3_show_value));
    }
    val = snprintf(buf, sizeof(L3_show_value), "%s", L3_show_value);
  }
  CSMLOGINFO(KERN_INFO " Sysfs show func returned %d \n", val);
  return val;
}

ssize_t sysfs_store_saddr(struct kobject *kobj, struct kobj_attribute *attr,
                          const char *buf, size_t count) {
  int index;
  u32 lower_SA = 0;
  u32 upper_SA = 0;
  u32 prev_val = 0;
  u64 L3_val;
  char L3_seps[2] = ".";
  char L2_seps[2] = ":";
  char *token;
  char token_string[100] = "";
  u64 var;
  int i = 0;
  unsigned int L2_SA_ADDR_HI_ARRAY[] = {
      L2_SA_ADDR_HI_0, L2_SA_ADDR_HI_1, L2_SA_ADDR_HI_2, L2_SA_ADDR_HI_3,
      L2_SA_ADDR_HI_4, L2_SA_ADDR_HI_5, L2_SA_ADDR_HI_6, L2_SA_ADDR_HI_7};
  unsigned int L2_SA_ADDR_LO_ARRAY[] = {
      L2_SA_ADDR_LO_0, L2_SA_ADDR_LO_1, L2_SA_ADDR_LO_2, L2_SA_ADDR_LO_3,
      L2_SA_ADDR_LO_4, L2_SA_ADDR_LO_5, L2_SA_ADDR_LO_6, L2_SA_ADDR_LO_7};
  unsigned int L3_IPV4_SA_ARRAY[] = {ETH_DBG_IPV4_SA_0, ETH_DBG_IPV4_SA_1,
                                     ETH_DBG_IPV4_SA_2};

  CSMLOGINFO(KERN_INFO " Reading - sysfs store func...%s \n", kobj->name);
  if (!strncmp(kobj->name, "L2_Info", Kobj_Name_L2_Info_Size)) {
    strlcpy(token_string, buf, MIN(sizeof(token_string), sizeof(buf)));
    token = mtip_sysfs_strtok(token_string, L2_seps);
    while (token != NULL) {
      sscanf(token, "%x", &var);
      CSMLOGINFO("Value passed in saddr is %x at index %d", var, i);
      L2.saddr[i++] = var;
      token = mtip_sysfs_strtok(NULL, L2_seps);
    }
    for (index = 0; index < MAX_FIFO_COUNT; index++) {
      lower_SA = (L2.saddr[0]) | (L2.saddr[1] << 8) | (L2.saddr[2] << 16) |
                 (L2.saddr[3] << 24);
      upper_SA = (L2.saddr[4]) | (L2.saddr[5] << 8);
      // write the lower bits
      CSMLOGINFO("Value in lowerSA is %x", lower_SA);
      CSMLOGINFO("Value in UpperSA is %x", upper_SA);
      iowrite32(lower_SA, debug_port_base_address + L2_SA_ADDR_LO_ARRAY[index]);
      // write the upper bits
      prev_val =
          (u32)ioread32(debug_port_base_address + L2_SA_ADDR_HI_ARRAY[index]);
      prev_val &= (~(GENMASK(15, 0)));
      prev_val |= ((upper_SA & GENMASK(15, 0)));
      iowrite32(prev_val, debug_port_base_address + L2_SA_ADDR_HI_ARRAY[index]);
    }
  } else if (!strncmp(kobj->name, "L3_Info", Kobj_Name_L3_Info_Size)) {
    strlcpy(token_string, buf, MIN(sizeof(token_string), sizeof(buf)));
    token = mtip_sysfs_strtok(token_string, L3_seps);
    while (token != NULL) {
      sscanf(token, "%d", &var);
      CSMLOGINFO("Value passed in saddr is %x at index %d", var, i);
      L3.saddr[i++] = var;
      token = mtip_sysfs_strtok(NULL, L3_seps);
    }
    L3_val = (L3.saddr[0]) | (L3.saddr[1] << 8) | (L3.saddr[2] << 16) |
             (L3.saddr[3] << 24);
    CSMLOGINFO("Value in L3_Val is %x", L3_val);
    for (index = 0; index < MAX_PACKET_FIFO_COUNT; index++) {
      iowrite32(L3_val, debug_port_base_address + L3_IPV4_SA_ARRAY[index]);
    }
  }
  return -1;
}

/*
Destination Address Endpoints –
(/sys/kernel/debugeth/L2L3HeaderInfo/L3_Info/daddr) Description: This endpoint
is responsible for the setting up of the Destination Address (daddr) value in
the i-th FIFO’s. Access Type: Read/Write Format: String Example Write: For L3
Headers, if the source address is 255.255.192.100 # echo 255.255.192.100 >
/sys/kernel/debugeth/L2L3HeaderInfo/L3_Info/daddr Example Read: # cat
/sys/kernel/debugeth/L2L3HeaderInfo/L3_Info/daddr (Expected output is
255.255.192.100.)
*/
ssize_t sysfs_show_daddr(struct kobject *kobj, struct kobj_attribute *attr,
                         char *buf) {
  int val = -1;
  char L3_show_value[100] = "";
  char L2_show_value[100] = "";
  char tmp_L3[4][20];
  char tmp_L2[6][20];
  int i;

  CSMLOGINFO(KERN_INFO " Reading - sysfs show func...%s \n", kobj->name);
  if (!strncmp(kobj->name, "L2_Info", Kobj_Name_L2_Info_Size)) {
    for (i = 0; i <= L2_size; i++) {
      snprintf(tmp_L2[i], sizeof(L2.daddr), "%x", L2.daddr[i]);
      strlcat(L2_show_value, tmp_L2[i], sizeof(L2_show_value));
      if (i != L2_size)
        strlcat(L2_show_value, ":", sizeof(L2_show_value));
    }
    val = snprintf(buf, sizeof(L2_show_value), "%s", L2_show_value);
  } else if (!strncmp(kobj->name, "L3_Info", Kobj_Name_L3_Info_Size)) {
    for (i = 0; i <= L3_size; i++) {
      snprintf(tmp_L3[i], sizeof(L3.daddr), "%d", L3.daddr[L3_size - i]);
      strlcat(L3_show_value, tmp_L3[i], sizeof(L3_show_value));
      if (i != L3_size)
        strlcat(L3_show_value, ".", sizeof(L3_show_value));
    }
    val = snprintf(buf, sizeof(L3_show_value), "%s", L3_show_value);
  }
  CSMLOGINFO(KERN_INFO " Sysfs show func returned %d \n", val);
  return val;
}

ssize_t sysfs_store_daddr(struct kobject *kobj, struct kobj_attribute *attr,
                          const char *buf, size_t count) {
  int index;
  u32 lower_DA = 0;
  u32 upper_DA = 0;
  u64 L3_val;
  char L3_seps[2] = ".";
  char L2_seps[2] = ":";
  char *token;
  char token_string[100] = "";
  int var;
  int i = 0;
  unsigned int L2_DA_ADDR_HI_ARRAY[] = {
      L2_DA_ADDR_HI_0, L2_DA_ADDR_HI_1, L2_DA_ADDR_HI_2,
      L2_DA_ADDR_HI_3, L2_DA_ADDR_HI_4, L2_DA_ADDR_HI_5,
      L2_DA_ADDR_HI_6, L2_DA_ADDR_HI_7, L2_DA_ADDR_HI_8};
  unsigned int L2_DA_ADDR_LO_ARRAY[] = {
      L2_DA_ADDR_LO_0, L2_DA_ADDR_LO_1, L2_DA_ADDR_LO_2,
      L2_DA_ADDR_LO_3, L2_DA_ADDR_LO_4, L2_DA_ADDR_LO_5,
      L2_DA_ADDR_LO_6, L2_DA_ADDR_LO_7, L2_DA_ADDR_LO_8};
  unsigned int L3_IPV4_DA_ARRAY[] = {ETH_DBG_IPV4_DA_0, ETH_DBG_IPV4_DA_1,
                                     ETH_DBG_IPV4_DA_2};

  CSMLOGINFO(KERN_INFO " Reading - sysfs store func...%s \n", kobj->name);
  if (!strncmp(kobj->name, "L2_Info", Kobj_Name_L2_Info_Size)) {
    strlcpy(token_string, buf, MIN(sizeof(token_string), sizeof(buf)));
    token = mtip_sysfs_strtok(token_string, L2_seps);
    while (token != NULL) {
      sscanf(token, "%x", &var);
      L2.daddr[i++] = var;
      token = mtip_sysfs_strtok(NULL, L2_seps);
    }
    for (index = 0; index < MAX_FIFO_COUNT; index++) {
      lower_DA = (L2.daddr[0]) | (L2.daddr[1] << 8) | (L2.daddr[2] << 16) |
                 (L2.daddr[3] << 24);
      upper_DA = (L2.daddr[4]) | (L2.daddr[5] << 8);
      // write the lower bits
      iowrite32(lower_DA, debug_port_base_address + L2_DA_ADDR_LO_ARRAY[index]);
      // write the upper bits
      iowrite32(upper_DA, debug_port_base_address + L2_DA_ADDR_HI_ARRAY[index]);
    }
  } else if (!strncmp(kobj->name, "L3_Info", Kobj_Name_L3_Info_Size)) {
    strlcpy(token_string, buf, MIN(sizeof(token_string), sizeof(buf)));
    token = mtip_sysfs_strtok(token_string, L3_seps);
    while (token != NULL) {
      sscanf(token, "%d", &var);
      L3.daddr[i++] = var;
      token = mtip_sysfs_strtok(NULL, L3_seps);
    }
    L3_val = (L3.daddr[0]) | (L3.daddr[1] << 8) | (L3.daddr[2] << 16) |
             (L3.daddr[3] << 24);
    for (index = 0; index < MAX_PACKET_FIFO_COUNT; index++) {
      iowrite32(L3_val, debug_port_base_address + L3_IPV4_DA_ARRAY[index]);
    }
  }
  return -1;
}

/*
Source Port Endpoints – (/sys/kernel/debugeth/L2L3HeaderInfo/L3_Info/sport)
Description: This endpoint is responsible for the setting up of the Source Port
(sport) value in the i-th FIFO’s. Access Type: Read/Write Format: Integer
Example Write:
For L3 Headers, if the source port is 24456, applications are expected to write
in the format as specified below. # echo 24456 >
/sys/kernel/debugeth/L2L3HeaderInfo/L3_Info/sport Example Read: # cat
/sys/kernel/debugeth/L2L3HeaderInfo/L3_Info/sport (Expected output is 24456.)
*/
ssize_t sysfs_show_sport(struct kobject *kobj, struct kobj_attribute *attr,
                         char *buf) {
  int val;
  CSMLOGINFO(KERN_INFO " Reading - sysfs show func...%s \n", kobj->name);
  val = snprintf(buf, sizeof(L3.sport), "%d", L3.sport);
  CSMLOGINFO(KERN_INFO " Sysfs show func returned %d \n", val);
  return val;
}

ssize_t sysfs_store_sport(struct kobject *kobj, struct kobj_attribute *attr,
                          const char *buf, size_t count) {
  int data;
  int index;
  int val;
  unsigned int UDP_SP_DP_ARRAY[] = {DBG_UDP_SP_DP_0, DBG_UDP_SP_DP_1,
                                    DBG_UDP_SP_DP_2};

  CSMLOGINFO(KERN_INFO " Reading - sysfs store func...%s \n", kobj->name);
  sscanf(buf, "%d", &L3.sport);
  data = L3.sport;
  for (index = 0; index < MAX_PACKET_FIFO_COUNT; index++) {
    val = (u32)ioread32(debug_port_base_address + UDP_SP_DP_ARRAY[index]);
    val &= (~(GENMASK(15, 0)));
    val |= ((data & GENMASK(15, 0)));
    iowrite32(val, debug_port_base_address + UDP_SP_DP_ARRAY[index]);
  }
  return -1;
}

/*
Destination Port Endpoints – (/sys/kernel/debugeth/L2L3HeaderInfo/L3_Info/dport)
Description: This endpoint is responsible for the setting up of the Destination
Port (dport) value in the i-th FIFO’s. Access Type: Read/Write Format: Integer
Example Write:
For L3 Headers, if the destination port is 24456, applications are expected to
write in the format as specified below. # echo 24456
/sys/kernel/debugeth/L2L3HeaderInfo/L3_Info/dport Example Read: # cat
/sys/kernel/debugeth/L2L3HeaderInfo/L3_Info/dport (Expected output is 24456.)
*/
ssize_t sysfs_show_dport(struct kobject *kobj, struct kobj_attribute *attr,
                         char *buf) {
  int val;
  CSMLOGINFO(KERN_INFO " Reading - sysfs show func...%s \n", kobj->name);
  val = snprintf(buf, sizeof(L3.dport), "%d", L3.dport);
  CSMLOGINFO(KERN_INFO " Sysfs show func returned %d \n", val);
  return val;
}

ssize_t sysfs_store_dport(struct kobject *kobj, struct kobj_attribute *attr,
                          const char *buf, size_t count) {
  int data;
  int index;
  int val;
  unsigned int UDP_SP_DP_ARRAY[] = {DBG_UDP_SP_DP_0, DBG_UDP_SP_DP_1,
                                    DBG_UDP_SP_DP_2};

  CSMLOGINFO(KERN_INFO " Reading - sysfs store func...%s \n", kobj->name);
  sscanf(buf, "%d", &L3.dport);
  data = L3.dport;
  for (index = 0; index < MAX_PACKET_FIFO_COUNT; index++) {
    val = (u32)ioread32(debug_port_base_address + UDP_SP_DP_ARRAY[index]);
    val &= (~(GENMASK(31, 16)));
    val |= ((data & GENMASK(15, 0)) << 16);
    iowrite32(val, debug_port_base_address + UDP_SP_DP_ARRAY[index]);
  }
  return -1;
}

/*
Status Endpoint – (/sys/kernel/debugeth/FIFO_#/status)
Description: This endpoint is responsible for checking the values of the Status
(Link UP/DOWN) in the i-th Streaming FIFO’s. Access Type: Read Format: Integer
Example Read:
# cat /sys/kernel/debugeth/FIFO_#/status
*/
ssize_t sysfs_show_status(struct kobject *kobj, struct kobj_attribute *attr,
                          char *buf) {
  int val = -1;
  CSMLOGINFO(KERN_INFO " Reading - sysfs show func...%s \n", kobj->name);
  if (!strncmp(kobj->name, "FIFO_0", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F0.status), "%d", F0.status);
  } else if (!strncmp(kobj->name, "FIFO_1", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F1.status), "%d", F1.status);
  } else if (!strncmp(kobj->name, "FIFO_2", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F2.status), "%d", F2.status);
  } else if (!strncmp(kobj->name, "FIFO_3", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F3.status), "%d", F3.status);
  } else if (!strncmp(kobj->name, "FIFO_4", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F4.status), "%d", F4.status);
  } else if (!strncmp(kobj->name, "FIFO_5", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F5.status), "%d", F5.status);
  } else if (!strncmp(kobj->name, "FIFO_6", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F6.status), "%d", F6.status);
  } else if (!strncmp(kobj->name, "FIFO_7", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F7.status), "%d", F7.status);
  }
  CSMLOGINFO(KERN_INFO " Sysfs show func returned %d \n", val);
  return val;
}

/*
Flush Endpoint - (/sys/kernel/debugeth/FIFO_#/flush)
Description: This endpoint is responsible for flushing the values in the i-th
FIFO’s. Access Type: Write Format: Integer Example Write: # echo 1 >
/sys/kernel/debugeth/FIFO_#/flush
*/
ssize_t sysfs_store_flush(struct kobject *kobj, struct kobj_attribute *attr,
                          const char *buf, size_t count) {
  int val = -1;
  CSMLOGINFO(KERN_INFO " Reading - sysfs store func...%s \n", kobj->name);
  if (!strncmp(kobj->name, "FIFO_0", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F0.flush);
    val = sysfs_store_flush_register_set(FIFO_0);
  } else if (!strncmp(kobj->name, "FIFO_1", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F1.flush);
    val = sysfs_store_flush_register_set(FIFO_1);
  } else if (!strncmp(kobj->name, "FIFO_2", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F2.flush);
    val = sysfs_store_flush_register_set(FIFO_2);
  } else if (!strncmp(kobj->name, "FIFO_3", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F3.flush);
    val = sysfs_store_flush_register_set(FIFO_3);
  } else if (!strncmp(kobj->name, "FIFO_4", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F4.flush);
    val = sysfs_store_flush_register_set(FIFO_4);
  } else if (!strncmp(kobj->name, "FIFO_5", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F5.flush);
    val = sysfs_store_flush_register_set(FIFO_5);
  } else if (!strncmp(kobj->name, "FIFO_6", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F6.flush);
    val = sysfs_store_flush_register_set(FIFO_6);
  } else if (!strncmp(kobj->name, "FIFO_7", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F7.flush);
    val = sysfs_store_flush_register_set(FIFO_7);
  }
  CSMLOGINFO(KERN_INFO " Sysfs store func returned %d count of bytes \n", val);
  return val;
}

int sysfs_store_flush_register_set(int index) {
  int data = 0;
  int set_bit = 1;
  int flush_bit;
  u32 v;

  // Setting the bit
  data |= set_bit << index;
  iowrite32(data, debug_port_base_address + DBG_ETH_DBG_SW_FLUSH);

  // Waiting till poll done
  if (index >= FIFO_0 && index <= FIFO_4) {
    // Changes to accomodate corresponding FIFO's instead of all FIFO's.
    flush_bit = 1;
    if (readl_poll_timeout(debug_port_base_address + DBG_ETH_DBG_FIFO_STATUS, v,
                           !(v & (flush_bit << index)), 100, 10000))
      return -EBUSY;
  } else if (index >= FIFO_5 && index <= FIFO_7) {
    // Changes to accomodate corresponding FIFO's instead of all FIFO's.
    flush_bit = 1;
    if (readl_poll_timeout(debug_port_base_address + DBG_ETH_DBG_FIFO_STATUS, v,
                           !(v & (flush_bit << index)), 100, 10000))
      return -EBUSY;
  }

  // Clearing the bit
  data &= ~(set_bit << index);
  iowrite32(data, debug_port_base_address + DBG_ETH_DBG_SW_FLUSH);

  return data;
}

/*
TXcount Endpoint – (/sys/kernel/debugeth/FIFO_#/txcount)
Description: This endpoint is responsible for returning the TX count value in
the i-th FIFO’s. Access Type: Read Format: Integer Example Read: # cat
/sys/kernel/debugeth/FIFO_#/txcount (Expected output is the Txcount in bytes.)
*/
ssize_t sysfs_show_txcount(struct kobject *kobj, struct kobj_attribute *attr,
                           char *buf) {
  int data = 0;
  ssize_t buff_size = 0;

  CSMLOGINFO(KERN_INFO " Reading - sysfs show func...%s \n", kobj->name);
  if (!strncmp(kobj->name, "FIFO_0", Kobj_Name_FIFO_Size)) {
    data = (int)ioread32(debug_port_base_address + STREAM_PKT_CNT_0);
    F0.txcount = data;
    buff_size = snprintf(buf, sizeof(F0.txcount), "%d", F0.txcount);
  } else if (!strncmp(kobj->name, "FIFO_1", Kobj_Name_FIFO_Size)) {
    data = (int)ioread32(debug_port_base_address + STREAM_PKT_CNT_1);
    F1.txcount = data;
    buff_size = snprintf(buf, sizeof(F1.txcount), "%d", F1.txcount);
  } else if (!strncmp(kobj->name, "FIFO_2", Kobj_Name_FIFO_Size)) {
    data = (int)ioread32(debug_port_base_address + STREAM_PKT_CNT_2);
    F2.txcount = data;
    buff_size = snprintf(buf, sizeof(F2.txcount), "%d", F2.txcount);
  } else if (!strncmp(kobj->name, "FIFO_3", Kobj_Name_FIFO_Size)) {
    data = (int)ioread32(debug_port_base_address + STREAM_PKT_CNT_3);
    F3.txcount = data;
    buff_size = snprintf(buf, sizeof(F3.txcount), "%d", F3.txcount);
  } else if (!strncmp(kobj->name, "FIFO_4", Kobj_Name_FIFO_Size)) {
    data = (int)ioread32(debug_port_base_address + STREAM_PKT_CNT_4);
    F4.txcount = data;
    buff_size = snprintf(buf, sizeof(F4.txcount), "%d", F4.txcount);
  } else if (!strncmp(kobj->name, "FIFO_5", Kobj_Name_FIFO_Size)) {
    data = (int)ioread32(debug_port_base_address + PACKET_FIFO1_PKT_CNT);
    F5.txcount = data;
    buff_size = snprintf(buf, sizeof(F5.txcount), "%d", F5.txcount);
  } else if (!strncmp(kobj->name, "FIFO_6", Kobj_Name_FIFO_Size)) {
    data = (int)ioread32(debug_port_base_address + PACKET_FIFO2_PKT_CNT);
    F6.txcount = data;
    buff_size = snprintf(buf, sizeof(F6.txcount), "%d", F6.txcount);
  } else if (!strncmp(kobj->name, "FIFO_7", Kobj_Name_FIFO_Size)) {
    data = (int)ioread32(debug_port_base_address + PACKET_FIFO3_PKT_CNT);
    F6.txcount = data;
    buff_size = snprintf(buf, sizeof(F7.txcount), "%d", F7.txcount);
  }
  CSMLOGINFO(KERN_INFO "The number of packets that has been sent through the "
                       "QDSS interface is as follows : \n");
  CSMLOGINFO(KERN_INFO " Sysfs show func returned %d with size %d \n", data,
             buff_size);
  return buff_size;
}

/*
Address Range Start Endpoints – (/sys/kernel/debugeth/FIFO_#/AddrRangeStart)
Description: This endpoint is responsible for updating the Address Range
Starting value in the i-th FIFO’s. Access Type: Read/Write Format: Integer
Example Write:
# echo 1000 > /sys/kernel/debugeth/FIFO_#/AddrRangeStart
Example Read:
# cat /sys/kernel/debugeth/FIFO_#/AddrRangeStart (Expected output is the Address
Range Starting value.)
*/
ssize_t sysfs_show_AddrRange_Start(struct kobject *kobj,
                                   struct kobj_attribute *attr, char *buf) {
  int val = -1;
  CSMLOGINFO(KERN_INFO " Reading - sysfs show func...%s \n", kobj->name);
  if (!strncmp(kobj->name, "FIFO_0", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F0.AddrRange_Start), "%d", F0.AddrRange_Start); //%x
  } else if (!strncmp(kobj->name, "FIFO_1", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F1.AddrRange_Start), "%d", F1.AddrRange_Start);
  } else if (!strncmp(kobj->name, "FIFO_2", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F2.AddrRange_Start), "%d", F2.AddrRange_Start);
  } else if (!strncmp(kobj->name, "FIFO_3", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F3.AddrRange_Start), "%d", F3.AddrRange_Start);
  } else if (!strncmp(kobj->name, "FIFO_4", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F4.AddrRange_Start), "%d", F4.AddrRange_Start);
  } else if (!strncmp(kobj->name, "FIFO_5", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F5.AddrRange_Start), "%d", F5.AddrRange_Start);
  } else if (!strncmp(kobj->name, "FIFO_6", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F6.AddrRange_Start), "%d", F6.AddrRange_Start);
  } else if (!strncmp(kobj->name, "FIFO_7", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F7.AddrRange_Start), "%d", F7.AddrRange_Start);
  }
  CSMLOGINFO(KERN_INFO " Sysfs show func returned %d \n", val);
  return val;
}

ssize_t sysfs_store_AddrRange_Start(struct kobject *kobj,
                                    struct kobj_attribute *attr,
                                    const char *buf, size_t count) {
  int val = -1;
  CSMLOGINFO(KERN_INFO " Reading - sysfs store func...%s \n", kobj->name);
  if (!strncmp(kobj->name, "FIFO_0", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F0.AddrRange_Start);
    val = count;
  } else if (!strncmp(kobj->name, "FIFO_1", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F1.AddrRange_Start);
    val = count;
  } else if (!strncmp(kobj->name, "FIFO_2", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F2.AddrRange_Start);
    val = count;
  } else if (!strncmp(kobj->name, "FIFO_3", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F3.AddrRange_Start);
    val = count;
  } else if (!strncmp(kobj->name, "FIFO_4", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F4.AddrRange_Start);
    val = count;
  } else if (!strncmp(kobj->name, "FIFO_5", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F5.AddrRange_Start);
    val = count;
  } else if (!strncmp(kobj->name, "FIFO_6", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F6.AddrRange_Start);
    val = count;
  } else if (!strncmp(kobj->name, "FIFO_7", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F7.AddrRange_Start);
    val = count;
  }
  CSMLOGINFO(KERN_INFO " Sysfs store func returned %d count of bytes \n", val);
  return val;
}

/*
Address Range End Endpoints– (/sys/kernel/debugeth/FIFO_#/AddrRangeEnd)
Description: This endpoint is responsible for updating the Address Range Ending
value in the i-th FIFO’s. Access Type: Read/Write Format: Integer Example Write:
# echo 1000 > /sys/kernel/debugeth/FIFO_#/AddrRangeEnd
Example Read:
# cat /sys/kernel/debugeth/FIFO_#/AddrRangeEnd (Expected output is the Address
Range Ending value.)
*/
ssize_t sysfs_show_AddrRange_End(struct kobject *kobj,
                                 struct kobj_attribute *attr, char *buf) {
  int val = -1;
  CSMLOGINFO(KERN_INFO " Reading - sysfs show func...%s \n", kobj->name);
  if (!strncmp(kobj->name, "FIFO_0", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F0.AddrRange_End), "%d", F0.AddrRange_End);
  } else if (!strncmp(kobj->name, "FIFO_1", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F1.AddrRange_End), "%d", F1.AddrRange_End);
  } else if (!strncmp(kobj->name, "FIFO_2", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F2.AddrRange_End), "%d", F2.AddrRange_End);
  } else if (!strncmp(kobj->name, "FIFO_3", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F3.AddrRange_End), "%d", F3.AddrRange_End);
  } else if (!strncmp(kobj->name, "FIFO_4", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F4.AddrRange_End), "%d", F4.AddrRange_End);
  } else if (!strncmp(kobj->name, "FIFO_5", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F5.AddrRange_End), "%d", F5.AddrRange_End);
  } else if (!strncmp(kobj->name, "FIFO_6", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F6.AddrRange_End), "%d", F6.AddrRange_End);
  } else if (!strncmp(kobj->name, "FIFO_7", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F7.AddrRange_End), "%d", F7.AddrRange_End);
  }
  CSMLOGINFO(KERN_INFO " Sysfs show func returned %d \n", val);
  return val;
}

ssize_t sysfs_store_AddrRange_End(struct kobject *kobj,
                                  struct kobj_attribute *attr, const char *buf,
                                  size_t count) {
  int val = -1;
  CSMLOGINFO(KERN_INFO " Reading - sysfs store func...%s \n", kobj->name);
  if (!strncmp(kobj->name, "FIFO_0", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F0.AddrRange_End);
    val = count;
  } else if (!strncmp(kobj->name, "FIFO_1", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F1.AddrRange_End);
    val = count;
  } else if (!strncmp(kobj->name, "FIFO_2", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F2.AddrRange_End);
    val = count;
  } else if (!strncmp(kobj->name, "FIFO_3", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F3.AddrRange_End);
    val = count;
  } else if (!strncmp(kobj->name, "FIFO_4", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F4.AddrRange_End);
    val = count;
  } else if (!strncmp(kobj->name, "FIFO_5", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F5.AddrRange_End);
    val = count;
  } else if (!strncmp(kobj->name, "FIFO_6", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F6.AddrRange_End);
    val = count;
  } else if (!strncmp(kobj->name, "FIFO_7", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F7.AddrRange_End);
    val = count;
  }
  CSMLOGINFO(KERN_INFO " Sysfs store func returned %d count of bytes \n", val);
  return val;
}
/*
OverFlowInterrupt Endpoint – (/sys/kernel/debugeth/FIFO_#/OverFlowInterrupt)
Description: This endpoint is responsible for updating the OverFlowInterrupt
value in the i-th FIFO’s. Access Type: Read Format: Integer Example Read: # cat
/sys/kernel/debugeth/FIFO_#/ OverFlowInterrupt (Expected output is the
OverFlowInterrupt value.)
*/
ssize_t sysfs_show_OverFlowInterrupt(struct kobject *kobj,
                                     struct kobj_attribute *attr, char *buf) {
  int val = -1;
  CSMLOGINFO(KERN_INFO " Reading - sysfs show func...%s \n", kobj->name);
  if (!strncmp(kobj->name, "FIFO_0", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F0.OverFlowInterrupt), "%d", F0.OverFlowInterrupt);
  } else if (!strncmp(kobj->name, "FIFO_1", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F1.OverFlowInterrupt), "%d", F1.OverFlowInterrupt);
  } else if (!strncmp(kobj->name, "FIFO_2", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F2.OverFlowInterrupt), "%d", F2.OverFlowInterrupt);
  } else if (!strncmp(kobj->name, "FIFO_3", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F3.OverFlowInterrupt), "%d", F3.OverFlowInterrupt);
  } else if (!strncmp(kobj->name, "FIFO_4", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F4.OverFlowInterrupt), "%d", F4.OverFlowInterrupt);
  } else if (!strncmp(kobj->name, "FIFO_5", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F5.OverFlowInterrupt), "%d", F5.OverFlowInterrupt);
  } else if (!strncmp(kobj->name, "FIFO_6", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F6.OverFlowInterrupt), "%d", F6.OverFlowInterrupt);
  } else if (!strncmp(kobj->name, "FIFO_7", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F7.OverFlowInterrupt), "%d", F7.OverFlowInterrupt);
  }
  CSMLOGINFO(KERN_INFO " Sysfs show func returned %d \n", val);
  return val;
}

/*
Threshold Endpoints - (/sys/kernel/debugeth/FIFO_#/Threshold)
Description: This endpoint is responsible for the setting up of the “Threshold”
value in the i-th Streaming FIFO. Access Type: Read/Write Format: Integer
Example Write: # echo 1 /sys/kernel/debugeth/FIFO_#/Threshold
Example Read: cat /sys/kernel/debugeth/FIFO_#/Threshold (Expected Output is 1)
*/
ssize_t sysfs_show_Threshold(struct kobject *kobj, struct kobj_attribute *attr,
                             char *buf) {
  int val = -1;
  CSMLOGINFO(KERN_INFO " Reading - sysfs show func...%s \n", kobj->name);
  if (!strncmp(kobj->name, "FIFO_0", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F0.Threshold), "%d", F0.Threshold);
  } else if (!strncmp(kobj->name, "FIFO_1", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F1.Threshold), "%d", F1.Threshold);
  } else if (!strncmp(kobj->name, "FIFO_2", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F2.Threshold), "%d", F2.Threshold);
  } else if (!strncmp(kobj->name, "FIFO_3", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F3.Threshold), "%d", F3.Threshold);
  } else if (!strncmp(kobj->name, "FIFO_4", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F4.Threshold), "%d", F4.Threshold);
  }
  CSMLOGINFO(KERN_INFO " Sysfs show func returned %d \n", val);
  return val;
}

ssize_t sysfs_store_Threshold(struct kobject *kobj, struct kobj_attribute *attr,
                              const char *buf, size_t count) {
  int val = -1;
  CSMLOGINFO(KERN_INFO " Reading - sysfs store func...%s \n", kobj->name);
  if (!strncmp(kobj->name, "FIFO_0", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F0.Threshold);
    setup_StreamingFIFO(FIFO_0);
    val = count;
  } else if (!strncmp(kobj->name, "FIFO_1", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F1.Threshold);
    setup_StreamingFIFO(FIFO_1);
    val = count;
  } else if (!strncmp(kobj->name, "FIFO_2", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F2.Threshold);
    setup_StreamingFIFO(FIFO_2);
    val = count;
  } else if (!strncmp(kobj->name, "FIFO_3", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F3.Threshold);
    setup_StreamingFIFO(FIFO_3);
    val = count;
  } else if (!strncmp(kobj->name, "FIFO_4", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F4.Threshold);
    setup_StreamingFIFO(FIFO_4);
    val = count;
  }
  CSMLOGINFO(KERN_INFO " Sysfs store func returned %d count of bytes \n", val);
  return val;
}

/*
Timeout Endpoints – (/sys/kernel/debugeth/FIFO_#/Timeout)
Description: This endpoint is responsible for setting the values of the Timeout
in the i-th Streaming FIFO’s. Access Type: Write Format: Integer (Value is in
number of clock cycles for that corresponding interface.) Example Write: # echo
100 > /sys/kernel/debugeth/FIFO_#/Timeout Example Read: # cat
/sys/kernel/debugeth/FIFO_#/Timeout
*/
ssize_t sysfs_show_Timeout(struct kobject *kobj, struct kobj_attribute *attr,
                           char *buf) {
  int val = -1;
  CSMLOGINFO(KERN_INFO " Reading - sysfs show func...%s \n", kobj->name);
  if (!strncmp(kobj->name, "FIFO_0", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F0.Timeout), "%d", F0.Timeout);
  } else if (!strncmp(kobj->name, "FIFO_1", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F1.Timeout), "%d", F1.Timeout);
  } else if (!strncmp(kobj->name, "FIFO_2", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F2.Timeout), "%d", F2.Timeout);
  } else if (!strncmp(kobj->name, "FIFO_3", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F3.Timeout), "%d", F3.Timeout);
  } else if (!strncmp(kobj->name, "FIFO_4", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F4.Timeout), "%d", F4.Timeout);
  }
  CSMLOGINFO(KERN_INFO " Sysfs show func returned %d \n", val);
  return val;
}

ssize_t sysfs_store_Timeout(struct kobject *kobj, struct kobj_attribute *attr,
                            const char *buf, size_t count) {
  int val = -1;
  CSMLOGINFO(KERN_INFO " Reading - sysfs store func...%s \n", kobj->name);
  if (!strncmp(kobj->name, "FIFO_0", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F0.Timeout);
    iowrite32(F0.Timeout, debug_port_base_address + STREAM_FIFO_TIMER_0);
    val = count;
  } else if (!strncmp(kobj->name, "FIFO_1", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F1.Timeout);
    iowrite32(F1.Timeout, debug_port_base_address + STREAM_FIFO_TIMER_1);
    val = count;
  } else if (!strncmp(kobj->name, "FIFO_2", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F2.Timeout);
    iowrite32(F2.Timeout, debug_port_base_address + STREAM_FIFO_TIMER_2);
    val = count;
  } else if (!strncmp(kobj->name, "FIFO_3", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F3.Timeout);
    iowrite32(F3.Timeout, debug_port_base_address + STREAM_FIFO_TIMER_3);
    val = count;
  } else if (!strncmp(kobj->name, "FIFO_4", Kobj_Name_FIFO_Size)) {
    sscanf(buf, "%d", &F4.Timeout);
    iowrite32(F4.Timeout, debug_port_base_address + STREAM_FIFO_TIMER_4);
    val = count;
  }
  CSMLOGINFO(KERN_INFO " Sysfs store func returned %d count of bytes \n", val);
  return val;
}

/*
VLAN-ID Endpoints – (/sys/kernel/debugeth/FIFO_#/VlanID)
Description: This endpoint is responsible for the setting up of the VLAN-ID’s
value in the i-th FIFO’s. Access Type: Read/Write Format: Integer (0-4095 in
decimals) Example Write: VLAN_ID = TPID( 0x8100 Default) + PCP ( 0 Default ) +
DEI ( 0 Default ) + VID ( User Input ) # echo 1024 >
/sys/kernel/debugeth/FIFO_#/VlanID Example Read: # cat
/sys/kernel/debugeth/FIFO_#/VlanID (Expected output is 1024.)
*/
ssize_t sysfs_show_vlanID(struct kobject *kobj, struct kobj_attribute *attr,
                          char *buf) {
  int val = -1;

  CSMLOGINFO(KERN_INFO " Reading - sysfs show func...%s \n", kobj->name);
  if (!strncmp(kobj->name, "FIFO_0", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F0.vlanID), "%d", F0.vlanID);
  } else if (!strncmp(kobj->name, "FIFO_1", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F1.vlanID), "%d", F1.vlanID);
  } else if (!strncmp(kobj->name, "FIFO_2", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F2.vlanID), "%d", F2.vlanID);
  } else if (!strncmp(kobj->name, "FIFO_3", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F3.vlanID),"%d", F3.vlanID);
  } else if (!strncmp(kobj->name, "FIFO_4", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F4.vlanID), "%d", F4.vlanID);
  } else if (!strncmp(kobj->name, "FIFO_5", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F5.vlanID), "%d", F5.vlanID);
  } else if (!strncmp(kobj->name, "FIFO_6", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F6.vlanID), "%d", F6.vlanID);
  } else if (!strncmp(kobj->name, "FIFO_7", Kobj_Name_FIFO_Size)) {
    val = snprintf(buf, sizeof(F7.vlanID), "%d", F7.vlanID);
  }
  CSMLOGINFO(KERN_INFO " Sysfs show func returned %d \n", val);
  return val;
}

int sysfs_store_vlanID_Register_Set(const char *buf, u64 *FIFO_vlanID, u32 reg1,
                                    u32 reg2) {
  u32 val;
  u32 vlan_id = 0;
  u32 vlan_tag = 1;
  u32 tpid = 0x8100;
  u32 vid = 0;
  u32 tci_val = 0;
  u32 tpid_val = 0;

  sscanf(buf, "%d", &vid);

  *FIFO_vlanID = vid;

  //tpid_val = tpid;
  tpid_val = (((tpid >> 8) & GENMASK(7, 0)) | (((tpid & GENMASK(7, 0)) << 8)));
  tci_val = (((vid >> 8) & GENMASK(7, 0)) | (((vid & GENMASK(7, 0)) << 8)));

  vlan_id = (tci_val << 16) | tpid_val;

  CSMLOGINFO(KERN_INFO " sysfs_store_vlanID_Register_Set - reg1 %x", vlan_id);
  iowrite32(vlan_id, debug_port_base_address + reg1);

  val = (u32)ioread32(debug_port_base_address + reg2);
  CSMLOGINFO(KERN_INFO " sysfs_store_vlanID_Register_Set - read reg2 %x", val);
  val &= (~(GENMASK(16, 16)));
  val |= ((vlan_tag) << 16);

  CSMLOGINFO(KERN_INFO " sysfs_store_vlanID_Register_Set - write reg2 %x", val);
  iowrite32(val, debug_port_base_address + reg2);

  return val;
}

ssize_t sysfs_store_vlanID(struct kobject *kobj, struct kobj_attribute *attr,
                           const char *buf, size_t count) {
  u32 val = -1;
  CSMLOGINFO(KERN_INFO " Reading - sysfs store func...%s \n", kobj->name);
  if (!strncmp(kobj->name, "FIFO_0", Kobj_Name_FIFO_Size)) {
    val = sysfs_store_vlanID_Register_Set(buf, &F0.vlanID, VLAN_TAG_0,
                                          L2_SA_ADDR_HI_0);
  } else if (!strncmp(kobj->name, "FIFO_1", Kobj_Name_FIFO_Size)) {
    val = sysfs_store_vlanID_Register_Set(buf, &F1.vlanID, VLAN_TAG_1,
                                          L2_SA_ADDR_HI_1);
  } else if (!strncmp(kobj->name, "FIFO_2", Kobj_Name_FIFO_Size)) {
    val = sysfs_store_vlanID_Register_Set(buf, &F2.vlanID, VLAN_TAG_2,
                                          L2_SA_ADDR_HI_2);
  } else if (!strncmp(kobj->name, "FIFO_3", Kobj_Name_FIFO_Size)) {
    val = sysfs_store_vlanID_Register_Set(buf, &F3.vlanID, VLAN_TAG_3,
                                          L2_SA_ADDR_HI_3);
  } else if (!strncmp(kobj->name, "FIFO_4", Kobj_Name_FIFO_Size)) {
    val = sysfs_store_vlanID_Register_Set(buf, &F4.vlanID, VLAN_TAG_4,
                                          L2_SA_ADDR_HI_4);
  } else if (!strncmp(kobj->name, "FIFO_5", Kobj_Name_FIFO_Size)) {
    val = sysfs_store_vlanID_Register_Set(buf, &F5.vlanID, VLAN_TAG_5,
                                          L2_SA_ADDR_HI_5);
  } else if (!strncmp(kobj->name, "FIFO_6", Kobj_Name_FIFO_Size)) {
    val = sysfs_store_vlanID_Register_Set(buf, &F6.vlanID, VLAN_TAG_6,
                                          L2_SA_ADDR_HI_6);
  } else if (!strncmp(kobj->name, "FIFO_7", Kobj_Name_FIFO_Size)) {
    val = sysfs_store_vlanID_Register_Set(buf, &F7.vlanID, VLAN_TAG_7,
                                          L2_SA_ADDR_HI_7);
  }
  CSMLOGINFO(KERN_INFO " Sysfs show func returned %d \n", val);
  return val;
}

int remove_sysfs(struct kobject *kobj_ref, struct kobj_attribute *attr) {
  CSMLOGINFO("Inside remove sysfs");
  kobject_put(kobj_ref);
  sysfs_remove_file(kernel_kobj, &attr->attr);
  return -1;
}

int sysfs_create_generic_dir_structure(struct kobject *kobj_ref) {
  CSMLOGINFO("Inside sysfs create directory structure function");

  if (sysfs_create_file(kobj_ref, &enabled_attr.attr)) {
    CSMLOGINFO("Unable to create the sysfs file...\n");
    remove_sysfs(kobj_ref, &enabled_attr);
  }
  return -1;
}

int sysfs_create_L2headers(struct kobject *kobj_ref) {
  if (sysfs_create_file(kobj_ref, &saddr_attr.attr)) {
    CSMLOGINFO("Unable to create the sysfs file...\n");
    remove_sysfs(kobj_ref, &saddr_attr);
  }

  else if (sysfs_create_file(kobj_ref, &daddr_attr.attr)) {
    CSMLOGINFO("Unable to create the sysfs file...\n");
    remove_sysfs(kobj_ref, &daddr_attr);
  }

  return -1;
}

int sysfs_create_L3headers(struct kobject *kobj_ref) {
  if (sysfs_create_file(kobj_ref, &saddr_attr.attr)) {
    CSMLOGINFO("Unable to create the sysfs file...\n");
    remove_sysfs(kobj_ref, &saddr_attr);
  }

  else if (sysfs_create_file(kobj_ref, &daddr_attr.attr)) {
    CSMLOGINFO("Unable to create the sysfs file...\n");
    remove_sysfs(kobj_ref, &daddr_attr);
  }

  else if (sysfs_create_file(kobj_ref, &sport_attr.attr)) {
    CSMLOGINFO("Unable to create the sysfs file...\n");
    remove_sysfs(kobj_ref, &sport_attr);
  }

  else if (sysfs_create_file(kobj_ref, &dport_attr.attr)) {
    CSMLOGINFO("Unable to create the sysfs file...\n");
    remove_sysfs(kobj_ref, &dport_attr);
  }

  return -1;
}

int sysfs_create_StreamingFifo(struct kobject *kobj_ref) {
  if (sysfs_create_file(kobj_ref, &status_attr.attr)) {
    CSMLOGINFO("Unable to create the sysfs file...\n");
    remove_sysfs(kobj_ref, &status_attr);
  }

  else if (sysfs_create_file(kobj_ref, &flush_attr.attr)) {
    CSMLOGINFO("Unable to create the sysfs file...\n");
    remove_sysfs(kobj_ref, &flush_attr);
  }

  else if (sysfs_create_file(kobj_ref, &txcount_attr.attr)) {
    CSMLOGINFO("Unable to create the sysfs file...\n");
    remove_sysfs(kobj_ref, &txcount_attr);
  }

  else if (sysfs_create_file(kobj_ref, &AddrRange_attr_start.attr)) {
    CSMLOGINFO("Unable to create the sysfs file...\n");
    remove_sysfs(kobj_ref, &AddrRange_attr_start);
  }

  else if (sysfs_create_file(kobj_ref, &AddrRange_attr_end.attr)) {
    CSMLOGINFO("Unable to create the sysfs file...\n");
    remove_sysfs(kobj_ref, &AddrRange_attr_end);
  }

  else if (sysfs_create_file(kobj_ref, &OverFlowInterrupt_attr.attr)) {
    CSMLOGINFO("Unable to create the sysfs file...\n");
    remove_sysfs(kobj_ref, &OverFlowInterrupt_attr);
  }

  else if (sysfs_create_file(kobj_ref, &Threshold_attr.attr)) {
    CSMLOGINFO("Unable to create the sysfs file...\n");
    remove_sysfs(kobj_ref, &Threshold_attr);
  }

  else if (sysfs_create_file(kobj_ref, &Timeout_attr.attr)) {
    CSMLOGINFO("Unable to create the sysfs file...\n");
    remove_sysfs(kobj_ref, &Timeout_attr);
  }

  else if (sysfs_create_file(kobj_ref, &vlanID_attr.attr)) {
    CSMLOGINFO("Unable to create the sysfs file...\n");
    remove_sysfs(kobj_ref, &vlanID_attr);
  }

  return -1;
}

int sysfs_create_PacketFifo(struct kobject *kobj_ref) {
  if (sysfs_create_file(kobj_ref, &status_attr.attr)) {
    CSMLOGINFO("Unable to create the sysfs file...\n");
    remove_sysfs(kobj_ref, &status_attr);
  }

  else if (sysfs_create_file(kobj_ref, &flush_attr.attr)) {
    CSMLOGINFO("Unable to create the sysfs file...\n");
    remove_sysfs(kobj_ref, &flush_attr);
  }

  else if (sysfs_create_file(kobj_ref, &txcount_attr.attr)) {
    CSMLOGINFO("Unable to create the sysfs file...\n");
    remove_sysfs(kobj_ref, &txcount_attr);
  }

  else if (sysfs_create_file(kobj_ref, &AddrRange_attr_start.attr)) {
    CSMLOGINFO("Unable to create the sysfs file...\n");
    remove_sysfs(kobj_ref, &AddrRange_attr_start);
  }

  else if (sysfs_create_file(kobj_ref, &AddrRange_attr_end.attr)) {
    CSMLOGINFO("Unable to create the sysfs file...\n");
    remove_sysfs(kobj_ref, &AddrRange_attr_end);
  }

  else if (sysfs_create_file(kobj_ref, &OverFlowInterrupt_attr.attr)) {
    CSMLOGINFO("Unable to create the sysfs file...\n");
    remove_sysfs(kobj_ref, &OverFlowInterrupt_attr);
  }

  else if (sysfs_create_file(kobj_ref, &vlanID_attr.attr)) {
    CSMLOGINFO("Unable to create the sysfs file...\n");
    remove_sysfs(kobj_ref, &vlanID_attr);
  }

  return -1;
}

unsigned int is_delim(char c, char *delim) {
  while (*delim != '\0') {
    if (c == *delim)
      return 1;
    delim++;
  }
  return 0;
}
char *mtip_sysfs_strtok(char *srcString, char *delim) {
  static char *backup_string; // start of the next search
  char *ret;

  if (!srcString) {
    srcString = backup_string;
  }
  if (!srcString) {
    // user is bad user
    return NULL;
  }
  // handle beginning of the string containing delims
  while (1) {
    if (is_delim(*srcString, delim)) {
      srcString++;
      continue;
    }
    if (*srcString == '\0') {
      // we've reached the end of the string
      return NULL;
    }
    break;
  }
  ret = srcString;
  while (1) {
    if (*srcString == '\0') {
      /*end of the input string and
      next exec will return NULL*/
      backup_string = srcString;
      return ret;
    }
    if (is_delim(*srcString, delim)) {
      *srcString = '\0';
      backup_string = srcString + 1;
      return ret;
    }
    srcString++;
  }
}
