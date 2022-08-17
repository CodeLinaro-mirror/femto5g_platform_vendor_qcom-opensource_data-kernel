/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/**
  @file qcom_aw_phy_gnl.c
  @brief Source file for generic netlink interface with the
  user space.

  This file defines  interface for generic netlink messages from PHY driver.
*/

#include <linux/kobject.h>
#include <linux/module.h>
#include <linux/netlink.h>
#include <linux/syscalls.h>
#include <linux/sysfs.h> /* sysfs addition*/
#include <net/genetlink.h>

#include "qcom_aw_phy_gnl.h"
#include "qcom_aw_phy_gnl_uapi.h"
#include "qcom_aw_phy_main.h"
#include "qcom_aw_phy_synce.h"
#include "qcom_aw_phy_utils.h"

static uint32_t dst_portid;

struct genl_ops qcom_aw_phy_genl_ops[QCOM_AW_PHY_GNL_CMD_COUNT] = {
    {
        .cmd = QCOM_AW_PHY_GNL_ATTR_INIT_LIB,
        .doit = qcom_aw_phy_gnl_init_lib,
        .validate = 0,
    },
    {
        .cmd = QCOM_AW_PHY_GNL_CMD_PHY_LANE_STATUS_CHANGE,
        .doit = qcom_aw_phy_gnl_no_action,
        .validate = 0,
    },
    {
        .cmd = QCOM_AW_PHY_GNL_CMD_SNR_VALID_CHANGE,
        .doit = qcom_aw_phy_gnl_no_action,
        .validate = 0,
    },
    {
        .cmd = QCOM_AW_PHY_GNL_CMD_SET_SNR_THRESHOLD,
        .doit = qcom_aw_phy_gnl_set_snr_threshold,
        .validate = 0,
    },
    {
        .cmd = QCOM_AW_PHY_GNL_CMD_GET_SNR_VALUE_REQ,
        .doit = qcom_aw_phy_gnl_get_snr_value,
        .validate = 0,
    },
    {
        .cmd = QCOM_AW_PHY_GNL_CMD_GET_SNR_VALUE_RESP,
        .doit = qcom_aw_phy_gnl_no_action,
        .validate = 0,
    },
    {
        .cmd = QCOM_AW_PHY_GNL_CMD_SET_SYNCE_MUX,
        .doit = qcom_aw_phy_gnl_set_synce_mux,
        .validate = 0,
    },
};

static struct nla_policy qcom_aw_phy_gnl_policy[QCOM_AW_PHY_GNL_ATTR_MAX] = {
    [QCOM_AW_PHY_GNL_ATTR_UNSPEC] = {.type = NLA_UNSPEC},
    [QCOM_AW_PHY_GNL_ATTR_INIT_LIB] = {.type = NLA_NUL_STRING},
    [QCOM_AW_PHY_GNL_ATTR_PHY_LANE_STATUS_CHANGE] = {.type = NLA_NUL_STRING},
    [QCOM_AW_PHY_GNL_ATTR_SNR_VALID_CHANGE] = {.type = NLA_NUL_STRING},
    [QCOM_AW_PHY_GNL_ATTR_SET_SNR_THRESHOLD] = {.type = NLA_NUL_STRING},
    [QCOM_AW_PHY_GNL_ATTR_GET_SNR_VALUE_REQ] = {.type = NLA_S32},
    [QCOM_AW_PHY_GNL_ATTR_GET_SNR_VALUE_RESP] = {.type = NLA_NUL_STRING},
    [QCOM_AW_PHY_GNL_ATTR_SET_SYNCE_MUX] = {.type = NLA_S32},
};

static struct genl_family qcom_aw_phy_gnl_family = {
    .id = 0,
    .hdrsize = 0,
    .name = FAMILY_NAME,
    .version = 1,
    .ops = qcom_aw_phy_genl_ops,
    .n_ops = QCOM_AW_PHY_GNL_CMD_COUNT,
    .policy = qcom_aw_phy_gnl_policy,
    .maxattr = QCOM_AW_PHY_GNL_ATTR_MAX,
    .module = THIS_MODULE,
};

int qcom_aw_phy_gnl_init_lib(struct sk_buff *sender_skb,
                             struct genl_info *info) {

  // cache the port id from info
  dst_portid = info->snd_portid;

  // Trigger callbacks
  qcom_aw_phy_synce_notify_phy_lane_state_change();

  return 0;
}

int qcom_aw_phy_gnl_lane_status_change(
    struct qcom_aw_phy_synce_lane_status *lane_status) {
  struct sk_buff *skb_buf;
  void *msg_head;
  char *send_char_msg = NULL;
  int ret_val = 0;
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;

  QCOM_AW_PHY_LOG_INFO("qcom_aw_phy_gnl_lane_status_change invoked");

  skb_buf = genlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
  if (skb_buf == NULL) {
    ret_val = ENOMEM;
    local_err_val = LOCAL_ERROR_0;
    goto func_exit;
  }

  msg_head = genlmsg_put(skb_buf, 0, 0, &qcom_aw_phy_gnl_family, 0,
                         QCOM_AW_PHY_GNL_CMD_PHY_LANE_STATUS_CHANGE);
  if (msg_head == NULL) {
    ret_val = ENOMEM;
    local_err_val = LOCAL_ERROR_1;
    goto func_exit;
  }

  send_char_msg = (char *)kzalloc(sizeof(struct qcom_aw_phy_synce_lane_status) *
                                      MAX_PHY_SYNCE_LANES,
                                  GFP_KERNEL);
  memset(send_char_msg, 0,
         sizeof(struct qcom_aw_phy_synce_lane_status) * MAX_PHY_SYNCE_LANES);
  memcpy(send_char_msg, lane_status,
         sizeof(struct qcom_aw_phy_synce_lane_status) * MAX_PHY_SYNCE_LANES);

  ret_val = nla_put(skb_buf, QCOM_AW_PHY_GNL_ATTR_PHY_LANE_STATUS_CHANGE,
                    sizeof(struct qcom_aw_phy_synce_lane_status) *
                        MAX_PHY_SYNCE_LANES,
                    send_char_msg);
  if (ret_val != 0) {
    local_err_val = LOCAL_ERROR_2;
    goto func_exit;
  }

  genlmsg_end(skb_buf, msg_head);

  ret_val = genlmsg_unicast(&init_net, skb_buf, dst_portid);
  if (ret_val != 0) {
    local_err_val = LOCAL_ERROR_3;
    goto func_exit;
  }

func_exit:
  if (!send_char_msg)
    kfree(send_char_msg);

  QCOM_AW_PHY_LOG_ERR("qcom_aw_phy_gnl_lane_status_change returned %d "
                      "with local error %d",
                      ret_val, local_err_val);
  return ret_val;
}

int qcom_aw_phy_gnl_snr_valid_change(
    struct qcom_aw_phy_synce_snr_valid_change snr_valid_info) {
  struct sk_buff *skb_buf;
  void *msg_head;
  char *send_char_msg = NULL;
  int ret_val = 0;
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;

  QCOM_AW_PHY_LOG_ERR("qcom_aw_phy_gnl_snr_valid_change invoked");

  skb_buf = genlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
  if (skb_buf == NULL) {
    ret_val = ENOMEM;
    local_err_val = LOCAL_ERROR_0;
    goto func_exit;
  }

  msg_head = genlmsg_put(skb_buf, 0, 0, &qcom_aw_phy_gnl_family, 0,
                         QCOM_AW_PHY_GNL_CMD_SNR_VALID_CHANGE);
  if (msg_head == NULL) {
    ret_val = ENOMEM;
    local_err_val = LOCAL_ERROR_1;
    goto func_exit;
  }

  send_char_msg = (char *)kzalloc(
      sizeof(struct qcom_aw_phy_synce_snr_valid_change), GFP_KERNEL);
  memset(send_char_msg, 0, sizeof(struct qcom_aw_phy_synce_snr_valid_change));
  memcpy(send_char_msg, &snr_valid_info,
         sizeof(struct qcom_aw_phy_synce_snr_valid_change));

  ret_val =
      nla_put(skb_buf, QCOM_AW_PHY_GNL_ATTR_SNR_VALID_CHANGE,
              sizeof(struct qcom_aw_phy_synce_snr_valid_change), send_char_msg);
  if (ret_val != 0) {
    local_err_val = LOCAL_ERROR_2;
    goto func_exit;
  }

  genlmsg_end(skb_buf, msg_head);

  ret_val = genlmsg_unicast(&init_net, skb_buf, dst_portid);
  if (ret_val != 0) {
    local_err_val = LOCAL_ERROR_3;
    goto func_exit;
  }

func_exit:
  if (!send_char_msg)
    kfree(send_char_msg);

  QCOM_AW_PHY_LOG_ERR(
      "qcom_aw_phy_gnl_snr_valid_change returned %d, local error %d", ret_val,
      local_err_val);

  return ret_val;
}

int qcom_aw_phy_gnl_no_action(struct sk_buff *sender_skb,
                              struct genl_info *info) {
  return 0;
}

int qcom_aw_phy_gnl_set_snr_threshold(struct sk_buff *sender_skb,
                                      struct genl_info *info) {
  struct nlattr *na;
  struct qcom_aw_phy_snr_threshold_info *recv_msg;
  int ret_val = 0;
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;

  QCOM_AW_PHY_LOG_INFO("qcom_aw_phy_gnl_set_snr_threshold invoked");

  if (info == NULL) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_0;
    goto func_exit;
  }

  na = info->attrs[QCOM_AW_PHY_GNL_ATTR_SET_SNR_THRESHOLD];
  if (!na) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_1;
    goto func_exit;
  }

  recv_msg = (struct qcom_aw_phy_snr_threshold_info *)nla_data(na);
  if (recv_msg == NULL) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_2;
    goto func_exit;
  } else {
    QCOM_AW_PHY_LOG_INFO("Received SNR thresholds for lane %d, "
                         "low_val = %d, high_val = %d",
                         recv_msg->lane_id, recv_msg->low_val,
                         recv_msg->high_val);
  }

  if (recv_msg->lane_id <= LANE_NONE ||
      recv_msg->lane_id >= MAX_PHY_SYNCE_LANES) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_3;
    goto func_exit;
  }

  qcom_aw_phy_synce_set_snr_threshold((recv_msg->lane_id / PHY_LANE_MAX),
                                      (recv_msg->lane_id % PHY_LANE_MAX),
                                      recv_msg->low_val, recv_msg->high_val);

func_exit:
  QCOM_AW_PHY_LOG_ERR(
      "qcom_aw_phy_gnl_set_snr_threshold returned %d, local error %d", ret_val,
      local_err_val);

  return ret_val;
}

int qcom_aw_phy_gnl_get_snr_value(struct sk_buff *sender_skb,
                                  struct genl_info *info) {
  struct nlattr *na;
  enum qcom_aw_phy_synce_lane_id *recv_msg;
  int snr_val[3];
  struct sk_buff *reply_skb;
  void *msg_head;
  int ret_val = 0;
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;

  QCOM_AW_PHY_LOG_INFO("qcom_aw_phy_gnl_get_snr_value invoked");

  if (info == NULL) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_0;
    goto func_exit;
  }

  na = info->attrs[QCOM_AW_PHY_GNL_ATTR_GET_SNR_VALUE_REQ];
  if (!na) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_1;
    goto func_exit;
  }

  recv_msg = (enum qcom_aw_phy_synce_lane_id *)nla_data(na);
  if (recv_msg == NULL) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_2;
    goto func_exit;
  } else {
    QCOM_AW_PHY_LOG_INFO("Received lane id as %d", *recv_msg);
  }

  if (*recv_msg <= LANE_NONE || *recv_msg >= MAX_PHY_SYNCE_LANES) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_3;
    goto func_exit;
  }

  qcom_aw_phy_synce_get_current_snr_val((*recv_msg / PHY_LANE_MAX),
                                        (*recv_msg % PHY_LANE_MAX), snr_val);

  reply_skb = genlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
  if (reply_skb == NULL) {
    ret_val = ENOMEM;
    local_err_val = LOCAL_ERROR_4;
    goto func_exit;
  }

  msg_head = genlmsg_put(reply_skb, info->snd_portid, info->snd_seq + 1,
                         &qcom_aw_phy_gnl_family, 0,
                         QCOM_AW_PHY_GNL_CMD_GET_SNR_VALUE_RESP);
  if (msg_head == NULL) {
    ret_val = ENOMEM;
    local_err_val = LOCAL_ERROR_5;
    goto func_exit;
  }

  ret_val = nla_put(reply_skb, QCOM_AW_PHY_GNL_ATTR_GET_SNR_VALUE_RESP,
                    3 * sizeof(int), snr_val);
  if (ret_val != 0) {
    local_err_val = LOCAL_ERROR_6;
    goto func_exit;
  }

  genlmsg_end(reply_skb, msg_head);

  ret_val = genlmsg_reply(reply_skb, info);
  if (ret_val != 0) {
    local_err_val = LOCAL_ERROR_6;
    goto func_exit;
  }

func_exit:
  QCOM_AW_PHY_LOG_ERR(
      "qcom_aw_phy_gnl_get_snr_value returned %d, local error %d", ret_val,
      local_err_val);

  return ret_val;
}

int qcom_aw_phy_gnl_set_synce_mux(struct sk_buff *sender_skb,
                                  struct genl_info *info) {
  struct nlattr *na;
  enum qcom_aw_phy_synce_lane_id *recv_msg;
  int ret_val = 0;
  enum local_error_enum local_err_val = LOCAL_ERROR_INVALID;

  QCOM_AW_PHY_LOG_INFO("qcom_aw_phy_gnl_set_synce_mux invoked");

  if (info == NULL) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_0;
    goto func_exit;
  }

  na = info->attrs[QCOM_AW_PHY_GNL_ATTR_SET_SYNCE_MUX];
  if (!na) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_1;
    goto func_exit;
  }

  recv_msg = (enum qcom_aw_phy_synce_lane_id *)nla_data(na);
  if (recv_msg == NULL) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_2;
    goto func_exit;
  } else {
    QCOM_AW_PHY_LOG_INFO("Received SyncE MUX lane %d", *recv_msg);
  }

  if (*recv_msg < LANE_NONE || *recv_msg >= MAX_PHY_SYNCE_LANES) {
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_3;
    goto func_exit;
  }

  // Set SyncE MUX processing
  if(qcom_aw_phy_synce_set_synce_mux(*recv_msg)){
    ret_val = EINVAL;
    local_err_val = LOCAL_ERROR_4;
    goto func_exit;
  }

func_exit:
  QCOM_AW_PHY_LOG_ERR(
      "qcom_aw_phy_gnl_set_synce_mux returned %d, local error %d", ret_val,
      local_err_val);

  return ret_val;
}

/* Init Function */
int qcom_aw_phy_gnl_init(void) {
  int res;
  // Register family with its operations and policies
  res = genl_register_family(&qcom_aw_phy_gnl_family);
  if (res != 0) {
    QCOM_AW_PHY_LOG_ERR("FAILED: genl_register_family(): %i\n", res);
    return -1;
  } else {
    QCOM_AW_PHY_LOG_ERR("successfully registered using Generic Netlink.\n");
  }

  return 0;
}

/* Exit Function */
void qcom_aw_phy_gnl_exit(void) {
  // Unrerister family
  genl_unregister_family(&qcom_aw_phy_gnl_family);

  return;
}
