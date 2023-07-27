/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef ECPRI_DMA_V01_H
#define ECPRI_DMA_V01_H

#define ECPRI_DMA_SERVICE_ID_V01 0x434
#define ECPRI_DMA_SERVICE_VERS_V01 0x01

#define QMI_ECPRI_MODEM_CH_CMD_COMPLETE_IND_V01 0x0021
#define QMI_ECPRI_INIT_MODEM_DRIVER_REQ_V01 0x0020
#define QMI_ECPRI_MODEM_CH_CMD_REQ_V01 0x0021
#define QMI_ECPRI_INIT_MODEM_DRIVER_COMPLETE_IND_V01 0x0020
#define QMI_ECPRI_MODEM_CH_CMD_RESP_V01 0x0021
#define QMI_ECPRI_INIT_MODEM_DRIVER_RESP_V01 0x0020

#define ECPRI_NUM_MODEM_EP_V01 16

enum ecpri_platform_enum_type_v01 {
	ECPRI_PLATFORM_ENUM_TYPE_MIN_VAL_V01 = INT_MIN,
	QMI_ECPRI_PLATFORM_TYPE_INVALID_V01 = 0,
	QMI_ECPRI_PLATFORM_TYPE_RU_ETH_V01 = 1,
	QMI_ECPRI_PLATFORM_TYPE_DU_PCIE_V01 = 2,
	QMI_ECPRI_PLATFORM_TYPE_DU_ETH_V01 = 3,
	QMI_ECPRI_PLATFORM_TYPE_DU_PCIE_4X9_V01 = 4,
	QMI_ECPRI_PLATFORM_TYPE_DU_PCIE_5X6_V01 = 5,
	ECPRI_PLATFORM_ENUM_TYPE_MAX_VAL_V01 = INT_MAX,
};

enum ecpri_ep_dir_enum_type_v01 {
	ECPRI_EP_DIR_ENUM_TYPE_MIN_VAL_V01 = INT_MIN,
	ECPRI_EP_DIR_SRC_V01 = 0,
	ECPRI_EP_DIR_DST_V01 = 1,
	ECPRI_EP_DIR_ENUM_TYPE_MAX_VAL_V01 = INT_MAX,
};

enum ecpri_ep_type_enum_type_v01 {
	ECPRI_EP_TYPE_ENUM_TYPE_MIN_VAL_V01 = INT_MIN,
	ECPRI_EP_TYPE_M2M_V01 = 0,
	ECPRI_EP_TYPE_S2M_V01 = 1,
	ECPRI_EP_TYPE_M2S_V01 = 2,
	ECPRI_EP_TYPE_ENUM_TYPE_MAX_VAL_V01 = INT_MAX,
};

enum ecpri_ep_protocol_enum_type_v01 {
	ECPRI_EP_PROTOCOL_ENUM_TYPE_MIN_VAL_V01 = INT_MIN,
	ECPRI_EP_PROT_FAPI_V01 = 0,
	ECPRI_EP_PROT_NFAPI_V01 = 1,
	ECPRI_EP_PROT_IPC_V01 = 2,
	ECPRI_EP_PROTOCOL_ENUM_TYPE_MAX_VAL_V01 = INT_MAX,
};

struct ecpri_ep_desc_type_v01 {
	u32 endp_id;
	enum ecpri_ep_dir_enum_type_v01 dir;
	enum ecpri_ep_type_enum_type_v01 type;
	enum ecpri_ep_protocol_enum_type_v01 prot;
};

enum ecpri_modem_mode_enum_type_v01 {
	ECPRI_MODEM_MODE_ENUM_TYPE_MIN_VAL_V01 = INT_MIN,
	ECPRI_MODEM_MODE_OPERATIONAL_V01 = 1,
	ECPRI_MODEM_MODE_E2E_LB_V01 = 2,
	ECPRI_MODEM_MODE_INT_FAPI_LB_V01 = 3,
	ECPRI_MODEM_MODE_ENUM_TYPE_MAX_VAL_V01 = INT_MAX,
};

struct ecpri_init_modem_driver_req_msg_v01 {
	enum ecpri_platform_enum_type_v01 platform_type;
	u32 ep_desc_list_len;
	struct ecpri_ep_desc_type_v01 ep_desc_list[ECPRI_NUM_MODEM_EP_V01];
	u8 hw_version_valid;
	u32 hw_version;
	u8 sw_version_valid;
	u32 sw_version;
};
#define ECPRI_INIT_MODEM_DRIVER_REQ_MSG_V01_MAX_MSG_LEN 281
extern struct qmi_elem_info ecpri_init_modem_driver_req_msg_v01_ei[];

struct ecpri_init_modem_driver_resp_msg_v01 {
	struct qmi_response_type_v01 resp;
	u8 sw_version_valid;
	u32 sw_version;
};
#define ECPRI_INIT_MODEM_DRIVER_RESP_MSG_V01_MAX_MSG_LEN 14
extern struct qmi_elem_info ecpri_init_modem_driver_resp_msg_v01_ei[];

struct ecpri_init_modem_driver_cmplt_ind_msg_v01 {
	u8 modem_driver_mode_valid;
	enum ecpri_modem_mode_enum_type_v01 modem_driver_mode;
};
#define ECPRI_INIT_MODEM_DRIVER_CMPLT_IND_MSG_V01_MAX_MSG_LEN 7
extern struct qmi_elem_info ecpri_init_modem_driver_cmplt_ind_msg_v01_ei[];

enum ecpri_ch_cmd_type_enum_v01 {
	ECPRI_CH_CMD_TYPE_ENUM_MIN_VAL_V01 = INT_MIN,
	QMI_ECPRI_CH_CMD_TYPE_START_V01 = 0,
	QMI_ECPRI_CH_CMD_TYPE_STOP_V01 = 1,
	QMI_ECPRI_CH_CMD_TYPE_RESET_V01 = 2,
	ECPRI_CH_CMD_TYPE_ENUM_MAX_VAL_V01 = INT_MAX,
};

struct ecpri_ch_cmd_txn_id_type_v01 {
	u32 q6_endp_id;
	u32 a55_endp_id;
	u32 gsi_id;
};

struct ecpri_modem_ch_cmd_req_msg_v01 {
	struct ecpri_ch_cmd_txn_id_type_v01 txn_id;
	u32 vf_id;
	enum ecpri_ch_cmd_type_enum_v01 ch_cmd;
};
#define ECPRI_MODEM_CH_CMD_REQ_MSG_V01_MAX_MSG_LEN 29
extern struct qmi_elem_info ecpri_modem_ch_cmd_req_msg_v01_ei[];

struct ecpri_modem_ch_cmd_resp_msg_v01 {
	struct qmi_response_type_v01 resp;
	u8 txn_id_valid;
	struct ecpri_ch_cmd_txn_id_type_v01 txn_id;
	u8 ch_cmd_valid;
	enum ecpri_ch_cmd_type_enum_v01 ch_cmd;
};
#define ECPRI_MODEM_CH_CMD_RESP_MSG_V01_MAX_MSG_LEN 29
extern struct qmi_elem_info ecpri_modem_ch_cmd_resp_msg_v01_ei[];

struct ecpri_modem_ch_cmd_cmplt_ind_msg_v01 {
	struct ecpri_ch_cmd_txn_id_type_v01 txn_id;
	enum ecpri_ch_cmd_type_enum_v01 ch_cmd;
};
#define ECPRI_MODEM_CH_CMD_CMPLT_IND_MSG_V01_MAX_MSG_LEN 22
extern struct qmi_elem_info ecpri_modem_ch_cmd_cmplt_ind_msg_v01_ei[];

#endif
