/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _EIP_REG_H_
#define _EIP_REG_H_

void eip_cache_register(unsigned int port_id, unsigned int byte_offset,
			uint32_t val);

#endif /* _EIP_REG_H_ */