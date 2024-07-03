/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef __ECPRI_GLOBAL_HWIO_DEF_H__
#define __ECPRI_GLOBAL_HWIO_DEF_H__
/**
  @file ecpri_global_hwio.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
  GLOBAL.*

  'Include' filters applied: <none>
  'Exclude' filters applied: RESERVED DUMMY
  */

/*----------------------------------------------------------------------------
 * MODULE: GLOBAL
 *--------------------------------------------------------------------------*/

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_GLOBAL_CFG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 operation_mode : 3;
	u32 ahb_resp_err_en : 1;
	u32 xbar_sres : 1;
	u32 reserved0 : 27;
} ecpri_global_hwio_def_ecpri_global_cfg_s;

/* Union definition of register */
typedef union
{
	ecpri_global_hwio_def_ecpri_global_cfg_s def;
	u32 value;
} ecpri_global_hwio_def_ecpri_global_cfg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_DEFAULT_HRESP
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 data : 32;
} ecpri_global_hwio_def_ecpri_default_hresp_s;

/* Union definition of register */
typedef union
{
	ecpri_global_hwio_def_ecpri_default_hresp_s def;
	u32 value;
} ecpri_global_hwio_def_ecpri_default_hresp_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_GLOBAL_XTOR_CFG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 oran_xtor_en : 1;
	u32 oran_xtor_tx_reset_0 : 1;
	u32 oran_xtor_tx_reset_1 : 1;
	u32 oran_xtor_tx_reset_2 : 1;
	u32 oran_xtor_tx_reset_3 : 1;
	u32 oran_xtor_rx_reset_0 : 1;
	u32 oran_xtor_rx_reset_1 : 1;
	u32 oran_xtor_rx_reset_2 : 1;
	u32 oran_xtor_rx_reset_3 : 1;
	u32 reserved0 : 23;
} ecpri_global_hwio_def_ecpri_global_xtor_cfg_s;

/* Union definition of register */
typedef union
{
	ecpri_global_hwio_def_ecpri_global_xtor_cfg_s def;
	u32 value;
} ecpri_global_hwio_def_ecpri_global_xtor_cfg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_IPCAT_VERSION
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 step : 16;
	u32 minor : 12;
	u32 major : 4;
} ecpri_global_hwio_def_ecpri_ipcat_version_s;

/* Union definition of register */
typedef union
{
	ecpri_global_hwio_def_ecpri_ipcat_version_s def;
	u32 value;
} ecpri_global_hwio_def_ecpri_ipcat_version_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_HW_VERSION
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 r_rev : 8;
	u32 reserved0 : 24;
} ecpri_global_hwio_def_ecpri_hw_version_s;

/* Union definition of register */
typedef union
{
	ecpri_global_hwio_def_ecpri_hw_version_s def;
	u32 value;
} ecpri_global_hwio_def_ecpri_hw_version_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_GLOBAL_QUDP_CFG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 fh_cfg_ahb_cgc_open : 1;
	u32 l2_cfg_ahb_cgc_open : 1;
	u32 reserved0 : 30;
} ecpri_global_hwio_def_ecpri_global_qudp_cfg_s;

/* Union definition of register */
typedef union
{
	ecpri_global_hwio_def_ecpri_global_qudp_cfg_s def;
	u32 value;
} ecpri_global_hwio_def_ecpri_global_qudp_cfg_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_GLOBAL_TPDM_SELECT
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 select : 32;
} ecpri_global_hwio_def_ecpri_global_tpdm_select_s;

/* Union definition of register */
typedef union
{
	ecpri_global_hwio_def_ecpri_global_tpdm_select_s def;
	u32 value;
} ecpri_global_hwio_def_ecpri_global_tpdm_select_u;

/*===========================================================================*/
/*!
  @brief Bit Field definition of register: ECPRI_GLOBAL_TPDM_CFG
  */
/*===========================================================================*/
/* Structure definition of register */
typedef struct
{
	u32 tpdm_cmb_i : 3;
	u32 reserved0 : 29;
} ecpri_global_hwio_def_ecpri_global_tpdm_cfg_s;

/* Union definition of register */
typedef union
{
	ecpri_global_hwio_def_ecpri_global_tpdm_cfg_s def;
	u32 value;
} ecpri_global_hwio_def_ecpri_global_tpdm_cfg_u;


#endif /* __ECPRI_GLOBAL_HWIO_DEF_H__ */
