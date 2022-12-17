/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/**
  @file mtip_debug_eth_gnl.c
  @brief Interface file between Debug ETH and DIAG Framework.

  This file contains interface handling between DIAG user space library and
  Debug Ethernet.
*/

#include <linux/kobject.h>
#include <linux/module.h>
#include <linux/netlink.h>
#include <linux/syscalls.h>
#include <linux/sysfs.h> /* sysfs addition*/
#include <net/genetlink.h>
#include "mtip_debug_eth_gnl_uapi.h"
#include "mtip_debug_eth_gnl.h"
#include "mtip_logging.h"
#include "mtip_sysfs.h"

struct genl_ops mtip_debug_eth_genl_ops[MTIP_DEBUG_ETH_GNL_CMD_COUNT] = {
    {
        .cmd = MTIP_DEBUG_ETH_GNL_CMD_SET_COMMON_PARAMS,
        .doit = mtip_debug_eth_gnl_set_common_params,
        .validate = 0,
    },
    {
        .cmd = MTIP_DEBUG_ETH_GNL_CMD_SET_ADDRESS_RANGE,
        .doit = mtip_debug_eth_gnl_set_addr_range,
        .validate = 0,
    },
    {
        .cmd = MTIP_DEBUG_ETH_GNL_CMD_SET_PORT,
        .doit = mtip_debug_eth_gnl_set_port,
        .validate = 0,
    },
    {
        .cmd = MTIP_DEBUG_ETH_GNL_CMD_SET_FLUSH,
        .doit = mtip_debug_eth_gnl_set_flush,
        .validate = 0,
    },
    {
        .cmd = MTIP_DEBUG_ETH_GNL_CMD_SET_THRESHOLD,
        .doit = mtip_debug_eth_gnl_set_threshold,
        .validate = 0,
    },
    {
        .cmd = MTIP_DEBUG_ETH_GNL_CMD_SET_TIMEOUT,
        .doit = mtip_debug_eth_gnl_set_timeout,
        .validate = 0,
    },
    {
        .cmd = MTIP_DEBUG_ETH_GNL_CMD_SET_VLANID,
        .doit = mtip_debug_eth_gnl_set_vlanID,
        .validate = 0,
    },
    {
        .cmd = MTIP_DEBUG_ETH_GNL_CMD_GET_RESULT,
        .doit = mtip_debug_eth_gnl_get_result,
        .validate = 0,
    },
};

static struct nla_policy
    mtip_debug_eth_genl_policy[MTIP_DEBUG_ETH_GNL_ATTR_MAX] = {
        [MTIP_DEBUG_ETH_GNL_ATTR_MIN] = {.type = NLA_UNSPEC},
        [MTIP_DEBUG_ETH_GNL_ATTR_SET_COMMON_PARAMS] = {.type = NLA_NUL_STRING},
        [MTIP_DEBUG_ETH_GNL_ATTR_SET_ADDRESS_RANGE] = {.type = NLA_NUL_STRING},
        [MTIP_DEBUG_ETH_GNL_ATTR_SET_PORT] = {.type = NLA_NUL_STRING},
        [MTIP_DEBUG_ETH_GNL_ATTR_SET_FLUSH] = {.type = NLA_U8},
        [MTIP_DEBUG_ETH_GNL_ATTR_SET_THRESHOLD] = {.type = NLA_NUL_STRING},
        [MTIP_DEBUG_ETH_GNL_ATTR_SET_TIMEOUT] = {.type = NLA_NUL_STRING},
        [MTIP_DEBUG_ETH_GNL_ATTR_SET_VLANID] = {.type = NLA_NUL_STRING},
        [MTIP_DEBUG_ETH_GNL_ATTR_GET_RESULT] = {.type = NLA_U8},
};

static struct genl_family mtip_debug_eth_gnl_family = {
    .id = 0,
    .hdrsize = 0,
    .name = MTIP_DEBUG_ETH_GNL_FAMILY_NAME,
    .version = 1,
    .ops = mtip_debug_eth_genl_ops,
    .n_ops = MTIP_DEBUG_ETH_GNL_CMD_COUNT,
    .policy = mtip_debug_eth_genl_policy,
    .maxattr = MTIP_DEBUG_ETH_GNL_ATTR_MAX,
    .module = THIS_MODULE,
};

int mtip_debug_eth_gnl_set_common_params(struct sk_buff *sender_skb,
                                        struct genl_info *info) {
  struct nlattr *na;
  mtip_debug_eth_gnl_params *mtip_debug_eth_gnl_params_tbl;
  int ret_val = 0;

  pr_err("mtip_debug_eth_gnl_set_common_params invoked");

  if (info == NULL) {
    ret_val = EINVAL;
    return ret_val;
  }

  na = info->attrs[MTIP_DEBUG_ETH_GNL_ATTR_SET_COMMON_PARAMS];
  if (!na) {
    ret_val = EINVAL;
    return ret_val;
  }

  mtip_debug_eth_gnl_params_tbl = (mtip_debug_eth_gnl_params *)nla_data(na);
  if (mtip_debug_eth_gnl_params_tbl == NULL) {
    ret_val = EINVAL;
    return ret_val;
  }

  setup_diag_l3_saddr(mtip_debug_eth_gnl_params_tbl->source_l3_addr);
  setup_diag_l3_daddr(mtip_debug_eth_gnl_params_tbl->dest_l3_addr);
  setup_diag_l2_daddr(mtip_debug_eth_gnl_params_tbl->dest_l2_addr);

  return 0;
}

int mtip_debug_eth_gnl_set_addr_range(struct sk_buff *sender_skb,
                                      struct genl_info *info) {
  struct nlattr *na;
  mtip_debug_eth_gnl_params *mtip_debug_eth_gnl_params_tbl;
  int ret_val = 0;

  pr_err("mtip_debug_eth_gnl_set_addr_range invoked");

  if (info == NULL) {
    ret_val = EINVAL;
    return ret_val;
  }

  na = info->attrs[MTIP_DEBUG_ETH_GNL_ATTR_SET_ADDRESS_RANGE];
  if (!na) {
    ret_val = EINVAL;
    return ret_val;
  }

  mtip_debug_eth_gnl_params_tbl = (mtip_debug_eth_gnl_params *)nla_data(na);
  if (mtip_debug_eth_gnl_params_tbl == NULL) {
    ret_val = EINVAL;
    return ret_val;
  }

  setup_diag_addr_range(mtip_debug_eth_gnl_params_tbl->fifo_num,
                        mtip_debug_eth_gnl_params_tbl->addr_range_start,
                        mtip_debug_eth_gnl_params_tbl->addr_range_end);

  return 0;
}

int mtip_debug_eth_gnl_set_port(struct sk_buff *sender_skb,
                                struct genl_info *info) {
  struct nlattr *na;
  mtip_debug_eth_gnl_params *mtip_debug_eth_gnl_params_tbl;
  int ret_val = 0;

  pr_err("mtip_debug_eth_gnl_set_port invoked");

  if (info == NULL) {
    ret_val = EINVAL;
    return ret_val;
  }

  na = info->attrs[MTIP_DEBUG_ETH_GNL_ATTR_SET_PORT];
  if (!na) {
    ret_val = EINVAL;
    return ret_val;
  }

  mtip_debug_eth_gnl_params_tbl = (mtip_debug_eth_gnl_params *)nla_data(na);
  if (mtip_debug_eth_gnl_params_tbl == NULL) {
    ret_val = EINVAL;
    return ret_val;
  }

  setup_diag_port(mtip_debug_eth_gnl_params_tbl->source_port,
                  mtip_debug_eth_gnl_params_tbl->dest_port);

  return 0;
}

int mtip_debug_eth_gnl_set_flush(struct sk_buff *sender_skb,
                                 struct genl_info *info) {
  struct nlattr *na;
  u_int8_t *fifo_num;
  int ret_val = 0;

  pr_err("mtip_debug_eth_gnl_set_flush invoked");

  if (info == NULL) {
    ret_val = EINVAL;
    return ret_val;
  }

  na = info->attrs[MTIP_DEBUG_ETH_GNL_ATTR_SET_FLUSH];
  if (!na) {
    ret_val = EINVAL;
    return ret_val;
  }

  fifo_num = (u_int8_t *)nla_data(na);
  if (fifo_num == NULL) {
    ret_val = EINVAL;
    return ret_val;
  }

  setup_diag_flush(*fifo_num);

  return 0;
}

int mtip_debug_eth_gnl_set_threshold(struct sk_buff *sender_skb,
                                     struct genl_info *info) {
  struct nlattr *na;
  mtip_debug_eth_gnl_params *mtip_debug_eth_gnl_params_tbl;
  int ret_val = 0;

  pr_err("mtip_debug_eth_gnl_set_threshold invoked");

  if (info == NULL) {
    ret_val = EINVAL;
    return ret_val;
  }

  na = info->attrs[MTIP_DEBUG_ETH_GNL_ATTR_SET_THRESHOLD];
  if (!na) {
    ret_val = EINVAL;
    return ret_val;
  }

  mtip_debug_eth_gnl_params_tbl = (mtip_debug_eth_gnl_params *)nla_data(na);
  if (mtip_debug_eth_gnl_params_tbl == NULL) {
    ret_val = EINVAL;
    return ret_val;
  }

  setup_diag_threshold(mtip_debug_eth_gnl_params_tbl->fifo_num,
                       mtip_debug_eth_gnl_params_tbl->threshold);

  return 0;
}

int mtip_debug_eth_gnl_set_timeout(struct sk_buff *sender_skb,
                                   struct genl_info *info) {
  struct nlattr *na;
  mtip_debug_eth_gnl_params *mtip_debug_eth_gnl_params_tbl;
  int ret_val = 0;

  pr_err("mtip_debug_eth_gnl_set_timeout invoked");

  if (info == NULL) {
    ret_val = EINVAL;
    return ret_val;
  }

  na = info->attrs[MTIP_DEBUG_ETH_GNL_ATTR_SET_TIMEOUT];
  if (!na) {
    ret_val = EINVAL;
    return ret_val;
  }

  mtip_debug_eth_gnl_params_tbl = (mtip_debug_eth_gnl_params *)nla_data(na);
  if (mtip_debug_eth_gnl_params_tbl == NULL) {
    ret_val = EINVAL;
    return ret_val;
  }

  setup_diag_timeout(mtip_debug_eth_gnl_params_tbl->fifo_num,
                     mtip_debug_eth_gnl_params_tbl->timeout);

  return 0;
}

int mtip_debug_eth_gnl_set_vlanID(struct sk_buff *sender_skb,
                                  struct genl_info *info) {
  struct nlattr *na;
  mtip_debug_eth_gnl_params *mtip_debug_eth_gnl_params_tbl;
  int ret_val = 0;

  pr_err("mtip_debug_eth_gnl_set_vlanID invoked");

  if (info == NULL) {
    ret_val = EINVAL;
    return ret_val;
  }

  na = info->attrs[MTIP_DEBUG_ETH_GNL_ATTR_SET_VLANID];
  if (!na) {
    ret_val = EINVAL;
    return ret_val;
  }

  mtip_debug_eth_gnl_params_tbl = (mtip_debug_eth_gnl_params *)nla_data(na);
  if (mtip_debug_eth_gnl_params_tbl == NULL) {
    ret_val = EINVAL;
    return ret_val;
  }

  setup_diag_vlanID(mtip_debug_eth_gnl_params_tbl->fifo_num,
                    mtip_debug_eth_gnl_params_tbl->vlanID);

  return 0;
}

int mtip_debug_eth_gnl_get_result(struct sk_buff *sender_skb,
                                  struct genl_info *info) {
  struct nlattr *na;
  struct sk_buff *reply_skb;
  void *msg_head;
  u_int8_t *fifo_num;
  mtip_debug_eth_gnl_params mtip_debug_eth_gnl_params_tbl;
  int ret_val = 0;

  pr_err("mtip_debug_eth_gnl_get_result invoked");

  if (info == NULL) {
    ret_val = EINVAL;
    return ret_val;
  }

  na = info->attrs[MTIP_DEBUG_ETH_GNL_ATTR_GET_RESULT];
  if (!na) {
    ret_val = EINVAL;
    return ret_val;
  }

  fifo_num = (u_int8_t *)nla_data(na);
  if (fifo_num == NULL) {
    ret_val = EINVAL;
    return ret_val;
  }

  pr_err("Received fifo value for result is : %d\n", *fifo_num);

  mtip_debug_eth_gnl_params_tbl = get_diag_result(*fifo_num);

  reply_skb = genlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
  if (reply_skb == NULL) {
    pr_err("Out of Memory \n");
    return -1;
  }

  msg_head = genlmsg_put(reply_skb, info->snd_portid, info->snd_seq + 1,
                         &mtip_debug_eth_gnl_family, 0,
                         MTIP_DEBUG_ETH_GNL_CMD_GET_RESULT);
  if (msg_head == NULL) {
    pr_err("genlmsg_put failed \n");
    return -1;
  }

  ret_val = nla_put(reply_skb, MTIP_DEBUG_ETH_GNL_ATTR_GET_RESULT,
                    sizeof(mtip_debug_eth_gnl_params_tbl),
                    &mtip_debug_eth_gnl_params_tbl);
  if (ret_val != 0) {
    pr_err("nla_put API failed \n");
    return -1;
  }

  genlmsg_end(reply_skb, msg_head);

  ret_val = genlmsg_reply(reply_skb, info);
  if (ret_val != 0) {
    pr_err("genlmsg_reply failed \n");
    return -1;
  }

  return 0;
}

/* Init Function */
int mtip_debug_eth_gnl_init(void) {
  int res;
  // Register family with its operations and policies
  res = genl_register_family(&mtip_debug_eth_gnl_family);
  if (res != 0) {
    pr_err("FAILED: genl_register_family(): %i", res);
    return -1;
  } else {
    pr_err("successfully registered using Generic Netlink.");
  }

  return 0;
}

/* Exit Function */
void mtip_debug_eth_gnl_exit(void) {
  // Unrerister family
  genl_unregister_family(&mtip_debug_eth_gnl_family);

  return;
}
