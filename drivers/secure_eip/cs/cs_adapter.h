//SPDX-License-Identifier: GPL-2.0-only

/*
* Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
*/

#ifndef LASSEN_ADAPTER_H
#define LASSEN_ADAPTER_H


#include "cs_adapter_ddk.h"



#undef LOG_SEVERITY_MAX
#undef ADAPTER_EIP163_WRITE_TO_DECREMENT
#undef ADAPTER_EIP164_WRITE_TO_DECREMENT



#define LOG_SEVERITY_MAX  LOG_SEVERITY_CRITICAL

/** EIP-163 Write-to-decrement  for statistics */
#define ADAPTER_EIP163_WRITE_TO_DECREMENT       0  /* changed from 1 to 0 to accumulate stats */
/** EIP-164 Write-to-decrement for statistics */
#define ADAPTER_EIP164_WRITE_TO_DECREMENT       0   /* changed from 1 to 0 to accumulate stats */

#endif /* LASSEN_ADAPTER_H */
