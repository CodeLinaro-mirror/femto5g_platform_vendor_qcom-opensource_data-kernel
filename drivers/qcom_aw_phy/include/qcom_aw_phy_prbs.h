/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/**
  @brief Interface header file between PRBS and DIAG Framework.

  This file defines interface between DIAG user space library and
  PRBS and PRBS functionalities.
*/

#ifndef QCOM_AW_PHY_PRBS_H
#define QCOM_AW_PHY_PRBS_H

#include <net/genetlink.h>
#include "qcom_aw_phy_prbs_gnl_uapi.h"

// Netlink APIs
int qcom_aw_phy_prbs_gnl_set_prbs_params(struct sk_buff *sender_skb,
                                         struct genl_info *info);

int qcom_aw_phy_prbs_gnl_enable_disable_prbs(struct sk_buff *sender_skb,
                                             struct genl_info *info);

int qcom_aw_phy_prbs_gnl_get_prbs_result(struct sk_buff *sender_skb,
                                         struct genl_info *info);

int qcom_aw_phy_prbs_gnl_init(void);
void qcom_aw_phy_prbs_gnl_exit(void);

// PRBS APIs
void qcom_aw_phy_prbs_set_params(
    data_csm_diag_prbs_params *prbs_params_info);

int qcom_aw_phy_prbs_enable_disable(uint8_t enable_flag);

data_csm_diag_prbs_result qcom_aw_phy_prbs_get_result(void);

#endif /* QCOM_AW_PHY_PRBS_H */
