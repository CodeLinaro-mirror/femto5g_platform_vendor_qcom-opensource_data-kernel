/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2024 Qualcomm Innovation Center, Inc. All rights reserved.
 */

/**
  @file qcom_aw_phy_main.h
  @brief Main header file for the AW PHY driver.

  This file contains definitions to be used across AW PHY driver code.
*/

#ifndef QCOM_AW_PHY_MAIN_H
#define QCOM_AW_PHY_MAIN_H

#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/phy.h>
#include <linux/of.h>
#include <linux/regulator/consumer.h>
#include <linux/pinctrl/consumer.h>
#include <linux/sysfs.h> /* sysfs addition*/
#include <linux/kobject.h>

#include "eth_phy_iface.h"

/* Module level feature definitions */
//#define FEATURE_QCOM_AW_RUMI_SW
#ifndef NO_DEBUGFS_PERF
#define FEATURE_QCOM_AW_DEBUG_FS
#endif
/* Macro to validate the lane number */
#define QCOM_AW_PHY_LANE_VALID(lane) ((lane >= PHY_LANE_0) && \
                                      (lane < PHY_LANE_MAX))

/* Macro to validate the PHY instance */
#define QCOM_AW_PHY_INST_VALID(inst) ((inst >= QCOM_AW_PHY_INST_FH0) && \
                                      (inst < QCOM_AW_PHY_INST_MAX))

/* PHY wrapper register offsets */
#define QCOM_AW_PHY_WRAPPER_PHY_ICTL_CMN_CFG_OFFSET           0x00000010
#define ICTL_CMN_CFG_REF_LS_ENA_A_OFFSET   0x1
#define ICTL_CMN_CFG_REF_LS_ENA_A_MASK     0x2

#define QCOM_AW_PHY_WRAPPER_INT_STATUS_REG_OFFSET             0x00000030
#define QCOM_AW_PHY_WRAPPER_INT_STATUS_EN_REG_OFFSET          0x00000034
#define QCOM_AW_PHY_WRAPPER_INT_STATUS_CLR_REG_OFFSET         0x00000038

#define QCOM_AW_PHY_WRAPPER_INT_ERROR_REG_OFFSET              0x0000003C
#define QCOM_AW_PHY_WRAPPER_INT_ERROR_EN_REG_OFFSET           0x00000040
#define QCOM_AW_PHY_WRAPPER_INT_ERROR_CLR_REG_OFFSET          0x00000044

#define QCOM_AW_PHY_WRAPPER_PHY_ICTL_AN_MASTER_CFG_OFFSET     0x00000014

/* TCSR register offsets */
#define TCSR_ETH_CLAMP_EN_REG_OFFSET                          0x00021000

#define TCSR_FH0_ICTL_REF_CML_LS_REG_OFFSET                   0x00024018
#define TCSR_FH1_ICTL_REF_CML_LS_REG_OFFSET                   0x00024028
#define TCSR_FH2_ICTL_REF_CML_LS_REG_OFFSET                   0x00024038
#define TCSR_C2C_L2_ICTL_REF_CML_LS_REG_OFFSET                0x00024048
#define TCSR_C2C_DBG_ICTL_REF_CML_LS_REG_OFFSET               0x00024058
#define B2T_0_MUX_SEL_NT_OFFSET   0x0
#define B2T_0_MUX_SEL_NT_MASK     0x3

#define TCSR_FH0_ICTL_REF_LS_MUX_SEL_REG_OFFSET               0x0002401C
#define TCSR_FH1_ICTL_REF_LS_MUX_SEL_REG_OFFSET               0x0002402C
#define TCSR_FH2_ICTL_REF_LS_MUX_SEL_REG_OFFSET               0x0002403C
#define TCSR_C2C_L2_ICTL_REF_LS_MUX_SEL_REG_OFFSET            0x0002404C
#define TCSR_C2C_DBG_ICTL_REF_LS_MUX_SEL_REG_OFFSET           0x0002405C
#define LS_MUX_SEL_NT_OFFSET      0x0
#define LS_MUX_SEL_NT_MASK        0x7

/* PHY status interrupt bit positions */
enum qcom_aw_phy_int_status_bit_enum{
	QCOM_AW_PHY_INT_STATUS_BIT_MIN       = 0,
	QCOM_AW_PHY_RX_SIGNAL_DETECT_LANE_0  = QCOM_AW_PHY_INT_STATUS_BIT_MIN,
	QCOM_AW_PHY_RX_SIGNAL_DETECT_LANE_1  = 1,
	QCOM_AW_PHY_RX_SIGNAL_DETECT_LANE_2  = 2,
	QCOM_AW_PHY_RX_SIGNAL_DETECT_LANE_3  = 3,
	QCOM_AW_PHY_AN_DONE_LANE_0           = 4,
	QCOM_AW_PHY_AN_DONE_LANE_1           = 5,
	QCOM_AW_PHY_AN_DONE_LANE_2           = 6,
	QCOM_AW_PHY_AN_DONE_LANE_3           = 7,
	QCOM_AW_PHY_AN_LINK_GOOD_LANE_0      = 8,
	QCOM_AW_PHY_AN_LINK_GOOD_LANE_1      = 9,
	QCOM_AW_PHY_AN_LINK_GOOD_LANE_2      = 10,
	QCOM_AW_PHY_AN_LINK_GOOD_LANE_3      = 11,
	QCOM_AW_PHY_AN_NEW_PAGE_LANE_0       = 12,
	QCOM_AW_PHY_AN_NEW_PAGE_LANE_1       = 13,
	QCOM_AW_PHY_AN_NEW_PAGE_LANE_2       = 14,
	QCOM_AW_PHY_AN_NEW_PAGE_LANE_3       = 15,
	QCOM_AW_PHY_SNR_VALID_LANE_0         = 20,
	QCOM_AW_PHY_SNR_VALID_LANE_1         = 21,
	QCOM_AW_PHY_SNR_VALID_LANE_2         = 22,
	QCOM_AW_PHY_SNR_VALID_LANE_3         = 23,
	QCOM_AW_PHY_INT_STATUS_BIT_MAX
};

/* PHY error interrupt bit positions */
enum qcom_aw_phy_int_error_bit_enum{
	QCOM_AW_PHY_INT_ERROR_BIT_MIN            = 0,
	QCOM_AW_PHY_RX_SIGNAL_DETECT_ERR_LANE_0  = QCOM_AW_PHY_INT_ERROR_BIT_MIN,
	QCOM_AW_PHY_RX_SIGNAL_DETECT_ERR_LANE_1  = 1,
	QCOM_AW_PHY_RX_SIGNAL_DETECT_ERR_LANE_2  = 2,
	QCOM_AW_PHY_RX_SIGNAL_DETECT_ERR_LANE_3  = 3,
	QCOM_AW_PHY_SNR_VALID_ERR_LANE_0         = 4,
	QCOM_AW_PHY_SNR_VALID_ERR_LANE_1         = 5,
	QCOM_AW_PHY_SNR_VALID_ERR_LANE_2         = 6,
	QCOM_AW_PHY_SNR_VALID_ERR_LANE_3         = 7,
	QCOM_AW_PHY_INT_ERROR_BIT_MAX
};


enum qcom_aw_phy_loopback_mode_enum{
	QCOM_AW_PHY_NO_LB                    = 0,
	QCOM_AW_PHY_NEAR_END_SERIAL_LB,
	QCOM_AW_PHY_NEAR_END_PARALLEL_LB
};

/* Enum to map error within a function */
enum local_error_enum{
	LOCAL_ERROR_INVALID = -1,
	LOCAL_ERROR_0,
	LOCAL_ERROR_1,
	LOCAL_ERROR_2,
	LOCAL_ERROR_3,
	LOCAL_ERROR_4,
	LOCAL_ERROR_5,
	LOCAL_ERROR_6,
	LOCAL_ERROR_7,
	LOCAL_ERROR_8,
	LOCAL_ERROR_9,
	LOCAL_ERROR_MAX
};

/* Enum to identify the PHY instance at port level */
enum qcom_aw_phy_instance_enum{
	QCOM_AW_PHY_INST_FH0 = 0,
	QCOM_AW_PHY_INST_FH1,
	QCOM_AW_PHY_INST_FH2,
	QCOM_AW_PHY_INST_L2_C2C,
	QCOM_AW_PHY_INST_DEBUG_C2C,
	QCOM_AW_PHY_INST_MAX
};

enum qcom_aw_phy_mod_tech_enum {
	QCOM_AW_PHY_MOD_TECH_MIN = 0,
	QCOM_AW_PHY_MOD_TECH_NRZ,
	QCOM_AW_PHY_MOD_TECH_PAM4,
	QCOM_AW_PHY_MOD_TECH_MAX
};

enum qcom_aw_phy_synce_lane_id{
	LANE_NONE  = -1,
	FH0_LANE_0 =  0,
	FH0_LANE_1,
	FH0_LANE_2,
	FH0_LANE_3,
	FH1_LANE_0,
	FH1_LANE_1,
	FH1_LANE_2,
	FH1_LANE_3,
	FH2_LANE_0,
	FH2_LANE_1,
	FH2_LANE_2,
	FH2_LANE_3,
	L2_C2C_LANE_0,  // L2 lane 0 or C2C2 lane 0
	L2_C2C_LANE_1,  // L2 lane 1 or C2C2 lane 1
	L2_C2C_LANE_2,  // L2 lane 2 or C2C1 lane 0
	L2_C2C_LANE_3,  // L2 lane 3 or C2C1 lane 1
	DBG_C2C_LANE0,  // C2C0 lane 0
	DBG_C2C_LANE1,  // C2C0 lane 1
	DBG_C2C_LANE2,  // DBG lane 0
	DBG_C2C_LANE3,  // DBG lane 1
	MAX_PHY_SYNCE_LANES
};

enum qcom_aw_phy_synce_eth_inst{
	ETH_NONE = -1,
	ETH00 = 0,
	ETH01 = 1,
	ETH02 = 2,
	ETH03 = 3,
	ETH10 = 4,
	ETH11 = 5,
	ETH12 = 6,
	ETH13 = 7,
	ETH20 = 8,
	ETH21 = 9,
	ETH22 = 10,
	ETH23 = 11,
	ETH30 = 12,  // L2_C2C2
	ETH31 = 13,  // C2C1
	ETH40 = 14,  // C2C0
	ETH41 = 15,  // DBG
	MAX_ETH_NUM
};

enum qcom_aw_phy_cdr_lock_lane_status{
	CDR_LOCK_NONE = -1,
	CDR_LOCK_FAILURE = 0,
	CDR_LOCK_SUCCESS = 1
};

enum qcom_aw_phy_speed_spec_enum {
	PHY_SPEED_SPEC_10G_BASE_KR = 2,
	PHY_SPEED_SPEC_40G_BASE_KR4 = 3,
	PHY_SPEED_SPEC_40G_BASE_CR4 = 4,
	PHY_SPEED_SPEC_100G_BASE_KR4 = 7,
	PHY_SPEED_SPEC_100G_BASE_CR4 = 8,
	PHY_SPEED_SPEC_25G_BASE_K_CR_S = 9,
	PHY_SPEED_SPEC_25G_BASE_K_CR = 10,
	PHY_SPEED_SPEC_50G_BASE_K_CR = 13,
	PHY_SPEED_SPEC_100G_BASE_K_CR2 = 14,
	PHY_SPEED_SPEC_100G_BASE_K_CR = 16,
	PHY_SPEED_SPEC_MAX = 20
};

enum qcom_aw_phy_fec_spec_enum {
	PHY_100G_BASE_P_RSFEC = 0,
	PHY_25G_RS_FEC = 1,
	PHY_25G_BASE_R_FEC = 2,
	PHY_10G_BASE_R_FEC = 4,
	PHY_FEC_SPEC_MAX
};

enum qcom_aw_phy_an_state_enum {
	PHY_AN_STATE_NONE = 0,
	PHY_AN_STATE_START = 1,
	PHY_AN_STATE_PCS_CONFIG = 2,
	PHY_AN_STATE_LINK_GOOD = 3,
	PHY_AN_STATE_DONE = 4,
	PHY_AN_STATE_FAILURE = 5
};

/* Work structure to be passed to work queue for deferred processing */
struct qcom_aw_phy_work_q_params{
	struct work_struct                     wq_item;
	enum qcom_aw_phy_instance_enum         phy_inst;
	enum eth_phy_iface_phy_lane_num_enum   lane_num;
	void                                  *user_data;
};

/* Delayed work structure to be passed to work queue for deferred processing */
struct qcom_aw_phy_delayed_work_q_params{
	struct delayed_work                    wq_item;
	enum qcom_aw_phy_instance_enum         phy_inst;
	enum eth_phy_iface_phy_lane_num_enum   lane_num;
	void                                  *user_data;
};

/* Lane Params - Lane specific information */
struct qcom_aw_lane_params{
	struct eth_phy_iface_phy_lane_config      lane_config;
	bool                                      link_status;
	bool                                      lane_bring_up_status;
	uint32_t                                  snr_valid_intr;
	uint32_t                                  an_link_good_intr;
	uint32_t                                  an_done_intr;
	bool                                      rx_sig_detect_status;
	struct qcom_aw_phy_delayed_work_q_params  an_restart_wq_item;
	struct qcom_aw_phy_work_q_params          snr_valid_err_wq_item;
	struct qcom_aw_phy_work_q_params          snr_valid_wq_item;
	struct qcom_aw_phy_work_q_params          an_done_wq_item;
	struct qcom_aw_phy_work_q_params          an_link_good_wq_item;
};

/* AN Params - AN specific information */
struct qcom_aw_phy_an_params{
	uint32_t                              adv_ability[PHY_SPEED_SPEC_MAX];
	uint32_t                              fec_ability[PHY_FEC_SPEC_MAX];
	enum qcom_aw_phy_an_state_enum        an_state[PHY_LANE_MAX];
	int                                   an_result[PHY_LANE_MAX];
	int                                   an_fec_result[PHY_LANE_MAX];
	uint32_t                              lp_adv_ability[PHY_LANE_MAX][PHY_SPEED_SPEC_MAX];
	uint32_t                              lp_fec_ability[PHY_LANE_MAX][PHY_FEC_SPEC_MAX];
	int                                   num_lanes;
	enum eth_phy_iface_phy_lane_num_enum  current_lane;
	uint32_t                              mac_port_config_mask;
	u8                                    seq_num;
};

/* PHY Instance Config - Config info for a particular PHY instance */
struct qcom_aw_phy_inst_config{
	bool                              valid;
	enum qcom_aw_phy_instance_enum    phy_inst;
	enum qcom_aw_phy_eq_mode_enum     phy_eq_mode;
	void __iomem                     *base_addr;
	void __iomem                     *wrapper_base_addr;
	struct platform_device           *pdev;
	int                               phy_status_irq;
	uint8_t                           num_lanes;
	struct qcom_aw_lane_params        lane_params[PHY_LANE_MAX];
	struct mutex                      lane_lock[PHY_LANE_MAX];
	enum qcom_aw_phy_cdr_lock_lane_status
	                                  cdr_lock_status_flag[PHY_LANE_MAX];
	bool                              bring_up_status;
	struct mutex                      phy_inst_lock;
	int                               sfp_port_type;
	struct qcom_aw_phy_an_params      an_params;
	struct workqueue_struct          *wq;
};

/* PHY Config - Config for all PHY instances at device level(DU/RU) */
struct qcom_aw_phy_config{
	uint8_t                                  num_phy_instances;
	void __iomem                            *tcsr_base_addr;
	struct qcom_aw_phy_inst_config   phy_inst_config_info[QCOM_AW_PHY_INST_MAX];
	struct regulator                        *ldo16_supply;
	struct reset_control                    *acgc_reset_ctrl;
	struct clk                              *synce_cmux_clk_src;
	struct clk                              *synce_cmux_clk;
	struct clk                              *synce_div_clk;
	struct clk                         *synce_phy_lane_clk[MAX_PHY_SYNCE_LANES];
	void                                    *phy_ipc_log_buf;
	void                                    *phy_ipc_log_buf_low;
	uint32_t                                 fw_major_ver;
	uint32_t                                 fw_minor_ver;
	uint32_t                                 fw_patch_ver;
	struct workqueue_struct                 *rx_sig_detect_wq;
	struct qcom_aw_phy_delayed_work_q_params rx_sig_detect_wq_item;
};

/* PHY lane speed config - Rate, width, LTCS clause, Modulation technique*/
struct qcom_aw_phy_lane_speed_config{
	uint32_t                         rate;
	uint32_t                         width;
	uint32_t                         clause;
	enum qcom_aw_phy_mod_tech_enum   mod_tech;
	unsigned long                    synce_cmux_clk_rate;
	unsigned long                    synce_div_clk_src_rate;
};

struct qcom_aw_phy_config* qcom_aw_phy_get_config_info(void);
struct qcom_aw_phy_inst_config *qcom_aw_phy_get_inst_config(enum qcom_aw_phy_instance_enum port);
struct qcom_aw_lane_params *qcom_aw_phy_get_lane_params(enum qcom_aw_phy_instance_enum port, enum eth_phy_iface_phy_lane_num_enum lane);
enum qcom_aw_phy_loopback_mode_enum qcom_aw_phy_get_loopback_mode(void);
void qcom_aw_phy_set_loopback_mode(enum qcom_aw_phy_loopback_mode_enum mode);
int qcom_aw_phy_get_polarity_flag(void);
int qcom_aw_phy_get_ref_clk_mode(void);
void qcom_aw_phy_enable_snr_interrupt(
                                  struct qcom_aw_phy_inst_config *phy_inst_info,
                                  enum eth_phy_iface_phy_lane_num_enum lane);
void qcom_aw_phy_disable_snr_interrupt(
                                  struct qcom_aw_phy_inst_config *phy_inst_info,
                                  enum eth_phy_iface_phy_lane_num_enum lane);

#ifdef FEATURE_QCOM_AW_DEBUG_FS
void qcom_aw_phy_setup_debugfs(void);
void qcom_aw_phy_del_debugfs(void);
ssize_t qcom_aw_phy_set_attr(struct file *file, const char __user *buf,
                                      size_t count, loff_t *ppos) ;
ssize_t qcom_aw_phy_get_attr(struct file *file, char __user *buf,
                             size_t count, loff_t *ppos) ;
ssize_t qcom_aw_phy_get_prbs_result(struct file *file, char __user *buf,
                                    size_t count, loff_t *ppos);
ssize_t qcom_aw_phy_set_tx_eq_val(struct file *file, const char __user *buf,
                             size_t count, loff_t *ppos);
ssize_t qcom_aw_phy_get_tx_eq_val(struct file *file, char __user *buf,
                                    size_t count, loff_t *ppos);
bool qcom_aw_phy_debugfs_get_tx_fir_val(enum qcom_aw_phy_instance_enum tx_bist_phy_inst,
                    enum eth_phy_iface_phy_lane_num_enum lane, void* txfir_cfg);
int32_t setup_phy_status_debugfs_directory(void);
#endif /* FEATURE_QCOM_AW_DEBUG_FS */

void qcom_aw_phy_setup_sysfs(void);
void qcom_aw_phy_del_sysfs(void);
ssize_t qcom_aw_phy_sysfs_show_an_restart_delay_timer(
                  struct kobject *kobj, struct kobj_attribute *attr, char *buf);
ssize_t qcom_aw_phy_sysfs_store_an_restart_delay_timer(
                              struct kobject *kobj, struct kobj_attribute *attr,
                              const char *buf, size_t count);
bool qcom_aw_phy_sysfs_get_tx_fir_val(enum qcom_aw_phy_instance_enum tx_bist_phy_inst,
                    enum eth_phy_iface_phy_lane_num_enum lane, void* txfir_cfg);


#endif /* QCOM_AW_PHY_MAIN_H */
