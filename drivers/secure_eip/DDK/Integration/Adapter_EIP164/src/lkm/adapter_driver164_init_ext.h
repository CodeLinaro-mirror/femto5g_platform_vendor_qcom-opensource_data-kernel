/* adapter_driver164_init_ext.h
 *
 * Linux kernel specific Adapter extensions
 */

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Module        : ddk164                                                   */
/*   Version       : 3.2                                                      */
/*   Configuration : DDK-164-IPSEC-GPL                                        */
/*                                                                            */
/*   Date          : 2022-Jan-10                                              */
/*                                                                            */
/* Copyright (c) 2008-2021 by Rambus, Inc. and/or its subsidiaries.           */
/*                                                                            */
/* This program is free software: you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation, either version 2 of the License, or          */
/* any later version.                                                         */
/*                                                                            */
/* This program is distributed in the hope that it will be useful,            */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of             */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               */
/* GNU General Public License for more details.                               */
/*                                                                            */
/* You should have received a copy of the GNU General Public License          */
/* along with this program. If not, see <http://www.gnu.org/licenses/>.       */
/* -------------------------------------------------------------------------- */

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Top-level Adapter configuration */
#include "c_adapter_eip164.h"

/* Linux Kernel API */
#include <linux/init.h>     /* module_init, module_exit */
#include <linux/module.h>   /* EXPORT_SYMBOL */


/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

#include "api_driver164_init.h"    /* Driver Init API */
#include "api_secy.h"              /* SecY API */
#include "api_secy_ext.h"          /* Extendedn SecY API */
#include "api_cfye.h"              /* CfyE API */
#include "api_cfye_ext.h"          /* Extended CfyE API */
#include "api_memxs.h"             /* MemXS API */
#include "sa_builder_macsec.h"     /* SA Builder API */
#include "api_warmboot.h"          /* WarmBoot API */

MODULE_LICENSE(ADAPTER_EIP164_LICENSE);


/* Driver Init API */
module_init(Driver164_Init);
module_exit(Driver164_Exit);
EXPORT_SYMBOL(Driver164_Device_Add);
EXPORT_SYMBOL(Driver164_Device_Remove);
EXPORT_SYMBOL(Driver164_Device_GetCount);
EXPORT_SYMBOL(Driver164_DataPath_Add);
EXPORT_SYMBOL(Driver164_DataPath_Remove);
EXPORT_SYMBOL(Driver164_DataPath_GetCount);

/* SecY API */
EXPORT_SYMBOL(SecY_Device_Init);
EXPORT_SYMBOL(SecY_Device_Uninit);
EXPORT_SYMBOL(SecY_Device_Limits);
EXPORT_SYMBOL(SecY_Device_Update);
EXPORT_SYMBOL(SecY_Device_Config_Get);
EXPORT_SYMBOL(SecY_Device_Status_Get);
EXPORT_SYMBOL(SecY_Device_Role_Get);
EXPORT_SYMBOL(SecY_Device_InsertSOP);
EXPORT_SYMBOL(SecY_Device_InsertEOP);
EXPORT_SYMBOL(SecY_Device_CountSummary_PSecY_CheckAndClear);
EXPORT_SYMBOL(SecY_Device_CountSummary_PIfc_CheckAndClear);
EXPORT_SYMBOL(SecY_Device_CountSummary_PIfc1_CheckAndClear);
EXPORT_SYMBOL(SecY_Device_CountSummary_PSA_CheckAndClear);
#ifdef ADAPTER_EIP164_PERCOUNTER_SUMMARY
EXPORT_SYMBOL(SecY_Device_CountSummary_SecY_CheckAndClear);
EXPORT_SYMBOL(SecY_Device_CountSummary_Ifc_CheckAndClear);
EXPORT_SYMBOL(SecY_Device_CountSummary_Ifc1_CheckAndClear);
EXPORT_SYMBOL(SecY_Device_CountSummary_SA_CheckAndClear);
#endif
EXPORT_SYMBOL(SecY_SAHandle_NULL);
EXPORT_SYMBOL(SecY_SAHandle_SAIndex_IsSame);
EXPORT_SYMBOL(SecY_SAHandle_IsSame);
EXPORT_SYMBOL(SecY_SA_Add);
EXPORT_SYMBOL(SecY_SA_Read);
EXPORT_SYMBOL(SecY_SA_Params_Read);
EXPORT_SYMBOL(SecY_SA_vPortIndex_Get);
EXPORT_SYMBOL(SecY_SA_Next_Get);
EXPORT_SYMBOL(SecY_SA_Remove);
EXPORT_SYMBOL(SecY_SA_Update);
EXPORT_SYMBOL(SecY_SA_NextPN_Update);
EXPORT_SYMBOL(SecY_SA_WindowSize_Update);
EXPORT_SYMBOL(SecY_SA_NextPN_Get);
EXPORT_SYMBOL(SecY_SA_WindowSize_Get);
EXPORT_SYMBOL(SecY_SA_ExpiredSummary_CheckAndClear);
EXPORT_SYMBOL(SecY_SA_PnThrSummary_CheckAndClear);
EXPORT_SYMBOL(SecY_vPort_Params_Read);
EXPORT_SYMBOL(SecY_vPort_Statistics_Clear);
EXPORT_SYMBOL(SecY_Diag_Device_Dump);
EXPORT_SYMBOL(SecY_Diag_Channel_Dump);
EXPORT_SYMBOL(SecY_Diag_vPort_Dump);
EXPORT_SYMBOL(SecY_Diag_SA_Dump);
#ifdef ADAPTER_EIP164_MODE_EGRESS
EXPORT_SYMBOL(SecY_SA_Chain);
EXPORT_SYMBOL(SecY_SA_Chained_Get);
EXPORT_SYMBOL(SecY_SA_Switch);
EXPORT_SYMBOL(SecY_SA_Active_E_Get);
EXPORT_SYMBOL(SecY_SecY_Statistics_E_Get);
EXPORT_SYMBOL(SecY_Ifc_Statistics_E_Get);
EXPORT_SYMBOL(SecY_SA_Statistics_E_Get);
#ifdef ADAPTER_EIP164_IPSEC_ENABLE
EXPORT_SYMBOL(SecY_SecY_Statistics_IPsec_E_Get);
#endif
#endif

#ifdef ADAPTER_EIP164_MODE_INGRESS
EXPORT_SYMBOL(SecY_Device_CountSummary_PRxCAM_CheckAndClear);
EXPORT_SYMBOL(SecY_SA_Active_I_Get);
EXPORT_SYMBOL(SecY_SCI_Next_Get);
EXPORT_SYMBOL(SecY_SecY_Statistics_I_Get);
EXPORT_SYMBOL(SecY_Ifc_Statistics_I_Get);
EXPORT_SYMBOL(SecY_SA_Statistics_I_Get);
EXPORT_SYMBOL(SecY_RxCAM_Statistics_Get);

#ifdef ADAPTER_EIP164_IPSEC_ENABLE
EXPORT_SYMBOL(SecY_SecY_Statistics_IPsec_I_Get);
EXPORT_SYMBOL(SecY_SA_Statistics_IPsec_I_Get);
#endif
#endif
#ifdef ADAPTER_EIP164_CRYPT_AUTH_ENABLE
EXPORT_SYMBOL(SecY_CryptAuth_BypassLen_Update);
EXPORT_SYMBOL(SecY_CryptAuth_BypassLen_Get);
#endif
#ifdef ADAPTER_EIP164_INTERRUPTS_ENABLE
EXPORT_SYMBOL(SecY_Notify_Request);
#endif
EXPORT_SYMBOL(SecY_Rules_SecTag_Update);
EXPORT_SYMBOL(SecY_Rules_MTUCheck_Update);
EXPORT_SYMBOL(SecY_Rules_MTUCheck_Get);
EXPORT_SYMBOL(SecY_Channel_Config_Get);
EXPORT_SYMBOL(SecY_Channel_Config_Set);
EXPORT_SYMBOL(SecY_Channel_Config_Update);
EXPORT_SYMBOL(SecY_Channel_Bypass_Get);
EXPORT_SYMBOL(SecY_Channel_Bypass_Set);
EXPORT_SYMBOL(SecY_Channel_PacketsInflight_Get);
EXPORT_SYMBOL(SecY_SAIndex_Get);
EXPORT_SYMBOL(SecY_SAHandle_Get);

/* CfyE API */
EXPORT_SYMBOL(CfyE_Device_Init);
EXPORT_SYMBOL(CfyE_Device_Uninit);
EXPORT_SYMBOL(CfyE_Device_Limits);
EXPORT_SYMBOL(CfyE_Device_Limits_Get);
EXPORT_SYMBOL(CfyE_Device_Update);
EXPORT_SYMBOL(CfyE_Device_Config_Get);
EXPORT_SYMBOL(CfyE_Device_Status_Get);
EXPORT_SYMBOL(CfyE_Device_Role_Get);
EXPORT_SYMBOL(CfyE_Device_InsertSOP);
EXPORT_SYMBOL(CfyE_Device_InsertEOP);
EXPORT_SYMBOL(CfyE_Channel_Bypass_Get);
EXPORT_SYMBOL(CfyE_Channel_Bypass_Set);
EXPORT_SYMBOL(CfyE_vPortHandle_NULL);
EXPORT_SYMBOL(CfyE_vPortHandle_IsSame);
EXPORT_SYMBOL(CfyE_vPort_Add);
EXPORT_SYMBOL(CfyE_vPort_Remove);
EXPORT_SYMBOL(CfyE_vPort_Update);
EXPORT_SYMBOL(CfyE_vPort_Read);
EXPORT_SYMBOL(CfyE_vPort_Next_Get);
EXPORT_SYMBOL(CfyE_RuleHandle_NULL);
EXPORT_SYMBOL(CfyE_RuleHandle_IsSame);
EXPORT_SYMBOL(CfyE_Rule_Add);
EXPORT_SYMBOL(CfyE_Rule_Add_Index);
EXPORT_SYMBOL(CfyE_Rule_Remove);
EXPORT_SYMBOL(CfyE_Rule_Update);
EXPORT_SYMBOL(CfyE_Rule_Enable);
EXPORT_SYMBOL(CfyE_Rule_Disable);
EXPORT_SYMBOL(CfyE_Rule_EnableDisable);
EXPORT_SYMBOL(CfyE_Rule_Read);
EXPORT_SYMBOL(CfyE_Rule_Next_Get);
EXPORT_SYMBOL(CfyE_Rule_vPort_Next_Get);

#if defined(ADAPTER_EIP163_IPSEC_ENABLE)
EXPORT_SYMBOL(CfyE_MTT_Update);
EXPORT_SYMBOL(CfyE_MTT_Enable);
EXPORT_SYMBOL(CfyE_MTT_Disable);
EXPORT_SYMBOL(CfyE_MTT_EnableDisable);
EXPORT_SYMBOL(CfyE_MTT_Read);
EXPORT_SYMBOL(CfyE_Diag_MTT_Dump);
EXPORT_SYMBOL(CfyE_Statistics_MTT_Get);
EXPORT_SYMBOL(CfyE_Statistics_Summary_MTT_Read);
#endif

EXPORT_SYMBOL(CfyE_Statistics_TCAM_Get);
EXPORT_SYMBOL(CfyE_Statistics_Channel_Get);
EXPORT_SYMBOL(CfyE_Statistics_Summary_TCAM_Read);
EXPORT_SYMBOL(CfyE_Statistics_Summary_Channel_Read);
EXPORT_SYMBOL(CfyE_Diag_Device_Dump);
EXPORT_SYMBOL(CfyE_Diag_Channel_Dump);
EXPORT_SYMBOL(CfyE_Diag_vPort_Dump);
EXPORT_SYMBOL(CfyE_Diag_Rule_Dump);

#ifdef ADAPTER_EIP164_INTERRUPTS_ENABLE
EXPORT_SYMBOL(CfyE_Notify_Request);
#endif
EXPORT_SYMBOL(CfyE_RuleIndex_Get);
EXPORT_SYMBOL(CfyE_vPortIndex_Get);
EXPORT_SYMBOL(CfyE_RuleHandle_Get);
EXPORT_SYMBOL(CfyE_vPortHandle_Get);

/* MemXS API */
EXPORT_SYMBOL(MemXS_Init);
EXPORT_SYMBOL(MemXS_Handle_IsSame);
EXPORT_SYMBOL(MemXS_Device_Count_Get);
EXPORT_SYMBOL(MemXS_Device_Info_Get);
EXPORT_SYMBOL(MemXS_Read32);
EXPORT_SYMBOL(MemXS_Write32);
EXPORT_SYMBOL(MemXS_Read32Array);
EXPORT_SYMBOL(MemXS_Write32Array);
EXPORT_SYMBOL(MemXS_NULLHandle);

/* SABuiklder API */
EXPORT_SYMBOL(SABuilder_InitParams);
EXPORT_SYMBOL(SABuilder_GetSize);
EXPORT_SYMBOL(SABuilder_BuildSA);

#ifdef ADAPTER_WARMBOOT_ENABLE
EXPORT_SYMBOL(WarmBoot_MaxSize_Get);
EXPORT_SYMBOL(WarmBoot_Register);
EXPORT_SYMBOL(WarmBoot_Shutdown);
EXPORT_SYMBOL(WarmBoot_Restore);
#endif


/* end of file adapter_driver164_init_ext.h */
