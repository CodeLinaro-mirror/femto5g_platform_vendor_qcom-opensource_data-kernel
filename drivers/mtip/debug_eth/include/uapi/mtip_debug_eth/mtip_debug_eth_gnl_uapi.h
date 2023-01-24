/* SPDX-License-Identifier: GPL-2.0-only WITH Linux-syscall-note
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/**
  @file mtip_debug_eth_gnl_uapi.h
  @brief Interface UAPI header file for generic netlink interface with the
  user space.

  This file defines header interface for netlink messages from Debug ETH 
  driver.
*/

#ifndef MTIP_DEBUG_ETH_GNL_UAPI_H
#define MTIP_DEBUG_ETH_GNL_UAPI_H

#define MTIP_DEBUG_ETH_GNL_FAMILY_NAME "DEBUG_ETH_GNL"

enum mtip_debug_eth_gnl_cmd_enum {
  MTIP_DEBUG_ETH_GNL_CMD_MIN,
  MTIP_DEBUG_ETH_GNL_CMD_SET_COMMON_PARAMS,
  MTIP_DEBUG_ETH_GNL_CMD_SET_ADDRESS_RANGE,
  MTIP_DEBUG_ETH_GNL_CMD_SET_PORT,
  MTIP_DEBUG_ETH_GNL_CMD_SET_FLUSH,
  MTIP_DEBUG_ETH_GNL_CMD_SET_THRESHOLD,
  MTIP_DEBUG_ETH_GNL_CMD_SET_TIMEOUT,
  MTIP_DEBUG_ETH_GNL_CMD_SET_VLANID,
  MTIP_DEBUG_ETH_GNL_CMD_GET_RESULT,
  MTIP_DEBUG_ETH_GNL_CMD_MAX
};

#define MTIP_DEBUG_ETH_GNL_CMD_COUNT (MTIP_DEBUG_ETH_GNL_CMD_MAX - 1)

enum mtip_debug_eth_gnl_attr_enum {
  MTIP_DEBUG_ETH_GNL_ATTR_MIN,
  MTIP_DEBUG_ETH_GNL_ATTR_SET_COMMON_PARAMS,
  MTIP_DEBUG_ETH_GNL_ATTR_SET_ADDRESS_RANGE,
  MTIP_DEBUG_ETH_GNL_ATTR_SET_PORT,
  MTIP_DEBUG_ETH_GNL_ATTR_SET_FLUSH,
  MTIP_DEBUG_ETH_GNL_ATTR_SET_THRESHOLD,
  MTIP_DEBUG_ETH_GNL_ATTR_SET_TIMEOUT,
  MTIP_DEBUG_ETH_GNL_ATTR_SET_VLANID,
  MTIP_DEBUG_ETH_GNL_ATTR_GET_RESULT,
  MTIP_DEBUG_ETH_GNL_ATTR_MAX
};

#define MTIP_DEBUG_ETH_GNL_ATTR_COUNT (MTIP_DEBUG_ETH_GNL_ATTR_MAX - 1)

typedef struct {
  u_int8_t fifo_num;
  u_int8_t source_l3_addr[4];
  u_int8_t dest_l3_addr[4];
  u_int8_t source_l2_addr[6];
  u_int8_t dest_l2_addr[6];
  u_int32_t addr_range_start;
  u_int32_t addr_range_end;
  u_int8_t source_port;
  u_int8_t dest_port;
  u_int8_t flush;
  u_int8_t threshold;
  u_int8_t timeout;
  u_int16_t vlanID;
  u_int8_t status;
  u_int8_t txcount;
} mtip_debug_eth_gnl_params;

#endif /* MTIP_DEBUG_ETH_GNL_UAPI_H */
