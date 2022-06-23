/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef ECPRISS_HAL_H_
#define ECPRISS_HAL_H_

#define ECPRISS_HAL_SETFIELD(val, shift, mask) (((val) << (shift)) & (mask))
#define ECPRISS_HAL_SETFIELD_IN_REG(reg, val, shift, mask) \
	(reg |= ((val) << (shift)) & (mask))
#define ECPRISS_HAL_GETFIELD_FROM_REG(reg, shift, mask) \
	(((reg) & (mask)) >> (shift))
#endif
