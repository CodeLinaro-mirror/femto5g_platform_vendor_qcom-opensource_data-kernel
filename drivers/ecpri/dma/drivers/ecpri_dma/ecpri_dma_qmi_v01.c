/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include <linux/soc/qcom/qmi.h>

#include "ecpri_dma_qmi_v01.h"

static struct qmi_elem_info ecpri_ep_desc_type_v01_ei[] = {
	{
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = sizeof(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = offsetof(struct ecpri_ep_desc_type_v01,
					   endp_id),
	},
	{
		.data_type      = QMI_SIGNED_4_BYTE_ENUM,
		.elem_len       = 1,
		.elem_size      = sizeof(enum ecpri_ep_dir_enum_type_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = offsetof(struct ecpri_ep_desc_type_v01,
					   dir),
	},
	{
		.data_type      = QMI_SIGNED_4_BYTE_ENUM,
		.elem_len       = 1,
		.elem_size      = sizeof(enum ecpri_ep_type_enum_type_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = offsetof(struct ecpri_ep_desc_type_v01,
					   type),
	},
	{
		.data_type      = QMI_SIGNED_4_BYTE_ENUM,
		.elem_len       = 1,
		.elem_size      = sizeof(enum ecpri_ep_protocol_enum_type_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0,
		.offset         = offsetof(struct ecpri_ep_desc_type_v01,
					   prot),
	},
	{
		.data_type      = QMI_EOTI,
		.array_type     = NO_ARRAY,
		.tlv_type       = QMI_COMMON_TLV_TYPE,
	},
};

struct qmi_elem_info ecpri_init_modem_driver_req_msg_v01_ei[] = {
	{
		.data_type      = QMI_SIGNED_4_BYTE_ENUM,
		.elem_len       = 1,
		.elem_size      = sizeof(enum ecpri_platform_enum_type_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x01,
		.offset         = offsetof(struct ecpri_init_modem_driver_req_msg_v01,
					   platform_type),
	},
	{
		.data_type      = QMI_DATA_LEN,
		.elem_len       = 1,
		.elem_size      = sizeof(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = offsetof(struct ecpri_init_modem_driver_req_msg_v01,
					   ep_desc_list_len),
	},
	{
		.data_type      = QMI_STRUCT,
		.elem_len       = ECPRI_NUM_MODEM_EP_V01,
		.elem_size      = sizeof(struct ecpri_ep_desc_type_v01),
		.array_type       = VAR_LEN_ARRAY,
		.tlv_type       = 0x02,
		.offset         = offsetof(struct ecpri_init_modem_driver_req_msg_v01,
					   ep_desc_list),
		.ei_array      = ecpri_ep_desc_type_v01_ei,
	},
	{
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = sizeof(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = offsetof(struct ecpri_init_modem_driver_req_msg_v01,
					   hw_version_valid),
	},
	{
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = sizeof(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = offsetof(struct ecpri_init_modem_driver_req_msg_v01,
					   hw_version),
	},
	{
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = sizeof(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x11,
		.offset         = offsetof(struct ecpri_init_modem_driver_req_msg_v01,
					   sw_version_valid),
	},
	{
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = sizeof(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x11,
		.offset         = offsetof(struct ecpri_init_modem_driver_req_msg_v01,
					   sw_version),
	},
	{
		.data_type      = QMI_EOTI,
		.array_type     = NO_ARRAY,
		.tlv_type       = QMI_COMMON_TLV_TYPE,
	},
};

struct qmi_elem_info ecpri_init_modem_driver_resp_msg_v01_ei[] = {
	{
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = sizeof(struct qmi_response_type_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = offsetof(struct ecpri_init_modem_driver_resp_msg_v01,
					   resp),
		.ei_array      = qmi_response_type_v01_ei,
	},
	{
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = sizeof(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = offsetof(struct ecpri_init_modem_driver_resp_msg_v01,
					   sw_version_valid),
	},
	{
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = sizeof(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = offsetof(struct ecpri_init_modem_driver_resp_msg_v01,
					   sw_version),
	},
	{
		.data_type      = QMI_EOTI,
		.array_type     = NO_ARRAY,
		.tlv_type       = QMI_COMMON_TLV_TYPE,
	},
};

struct qmi_elem_info ecpri_init_modem_driver_cmplt_ind_msg_v01_ei[] = {
	{
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = sizeof(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = offsetof(struct ecpri_init_modem_driver_cmplt_ind_msg_v01,
					   modem_driver_mode_valid),
	},
	{
		.data_type      = QMI_SIGNED_4_BYTE_ENUM,
		.elem_len       = 1,
		.elem_size      = sizeof(enum ecpri_modem_mode_enum_type_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = offsetof(struct ecpri_init_modem_driver_cmplt_ind_msg_v01,
					   modem_driver_mode),
	},
	{
		.data_type      = QMI_EOTI,
		.array_type     = NO_ARRAY,
		.tlv_type       = QMI_COMMON_TLV_TYPE,
	},
};

