/*
 * SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _DMAHAL_REG_H_
#define _DMAHAL_REG_H_

#include "dmahal_reg_i.h"

/*
 * Registers names
 *
 * NOTE:: Any change to this enum, need to change to ecpri_dma_reg_name_to_str
 *	array as well.
 */
enum ecpri_dma_hal_reg_name {
    HW_PARAMS_0,
    ECPRI_NFAPI_CFG_0,
    ECPRI_NFAPI_CFG_1,
    ECPRI_NFAPI_CFG_2,
    ECPRI_DMA_STREAM_CTRL,
    ECPRI_NSO_CFG,
    ECPRI_NSO_JUMBO_PKT_CFG,
    ECPRI_IRQ_STTS_EE_n,
    ECPRI_IRQ_EN_EE_n,
    ECPRI_IRQ_CLR_EE_n,
    ECPRI_ENDP_CFG_DEST_n,
    ECPRI_ENDP_CFG_XBAR_n,
    ECPRI_DMA_EXCEPTION_CHANNEL,
    ECPRI_ENDP_CFG_AGGR_n,
    ECPRI_ENDP_NFAPI_REASSEMBLY_CFG_n,
    ECPRI_NFAPI_REASSEMBLY_VM_CFG_0_n,
    ECPRI_NFAPI_REASSEMBLY_VM_CFG_1_n,
    ECPRI_NFAPI_REASSEMBLY_VM_CFG_2_n,
    ECPRI_ENDP_GSI_CFG_n,
    DMA_REG_MAX,
};

/* Specific registers structures */

/* General registers structures */


/*
 * struct ecpri_dma_hal_reg_valmask - holding values and masking for registers
 *	HAL application may require only value and mask of it for some
 *	register fields.
 * @val - The value
 * @mask - Tha mask of the value
 */
struct ecpri_dma_hal_reg_valmask {
	u32 val;
	u32 mask;
};


/* Register HAL utility functions */

/*
 * ecpri_dma_hal_print_all_regs() - Loop and read and print all the valid registers
 *  Parameterized registers are also printed for all the valid ranges.
 *  Print to dmsg and IPC logs
 */
void ecpri_dma_hal_print_all_regs(bool print_to_dmesg);

/*
 * ecpri_dma_hal_reg_name_str() - returns string that represent the register
 * @reg_name: [in] register name
 */
const char *ecpri_dma_hal_reg_name_str(enum ecpri_dma_hal_reg_name reg_name);

/*
 * ecpri_dma_hal_read_reg_n() - Get the raw value of n parameterized reg
 */
u32 ecpri_dma_hal_read_reg_n(enum ecpri_dma_hal_reg_name reg, u32 n);

/*
 * ecpri_dma_hal_read_reg_mn() - Get mn parameterized reg value
 */
u32 ecpri_dma_hal_read_reg_mn(enum ecpri_dma_hal_reg_name reg, u32 m, u32 n);

/*
* ecpri_dma_hal_read_reg_nk() - Read from n/k parameterized reg
*/
static inline u32 ecpri_dma_hal_read_reg_nk(enum ecpri_dma_hal_reg_name reg, u32 n, u32 k)
{
	return ecpri_dma_hal_read_reg_mn(reg, k, n);
}

/*
* ecpri_dma_hal_read_ep_reg_n() - Get n parameterized reg value according to ep
*/
u32 ecpri_dma_hal_read_ep_reg_n(enum ecpri_dma_hal_reg_name reg, u32 n, u32 ep_num);

/*
 * ecpri_dma_hal_write_reg_mn() - Write to m/n parameterized reg a raw value
 */
void ecpri_dma_hal_write_reg_mn(enum ecpri_dma_hal_reg_name reg, u32 m, u32 n, u32 val);

/*
* ecpri_dma_hal_write_reg_nk() - Write to n/k parameterized reg a raw value
*/
static inline void ecpri_dma_hal_write_reg_nk(
	enum ecpri_dma_hal_reg_name reg, u32 n, u32 k, u32 val)
{
	ecpri_dma_hal_write_reg_mn(reg, k, n, val);
}

/*
 * ecpri_dma_hal_write_reg_n() - Write to n parameterized reg a raw value
 */
static inline void ecpri_dma_hal_write_reg_n(enum ecpri_dma_hal_reg_name reg,
	u32 n, u32 val)
{
	ecpri_dma_hal_write_reg_mn(reg, 0, n, val);
}

/*
 * ecpri_dma_hal_read_reg_n_fields() - Get the parsed value of n parameterized reg
 */
u32 ecpri_dma_hal_read_reg_n_fields(enum ecpri_dma_hal_reg_name reg, u32 n, void *fields);

/*
 * ecpri_dma_hal_write_reg_n_fields() - Write to n parameterized reg a prased value
 */
void ecpri_dma_hal_write_reg_n_fields(enum ecpri_dma_hal_reg_name reg, u32 n,
	const void *fields);

/*
 * ecpri_dma_hal_read_reg() - Get the raw value of a reg
 */
static inline u32 ecpri_dma_hal_read_reg(enum ecpri_dma_hal_reg_name reg)
{
	return ecpri_dma_hal_read_reg_n(reg, 0);
}

/*
 * ecpri_dma_hal_read_ep_reg() - Get the raw value of a ep reg
 */
u32 ecpri_dma_hal_read_ep_reg(enum ecpri_dma_hal_reg_name reg, u32 ep_num);

/*
 * ecpri_dma_hal_write_reg() - Write to reg a raw value
 */
static inline void ecpri_dma_hal_write_reg(enum ecpri_dma_hal_reg_name reg,
	u32 val)
{
	ecpri_dma_hal_write_reg_mn(reg, 0, 0, val);
}

/*
 * ecpri_dma_hal_read_reg_fields() - Get the parsed value of a reg
 */
static inline u32 ecpri_dma_hal_read_reg_fields(enum ecpri_dma_hal_reg_name reg, void *fields)
{
	return ecpri_dma_hal_read_reg_n_fields(reg, 0, fields);
}

/*
 * ecpri_dma_hal_write_reg_fields() - Write to reg a parsed value
 */
static inline void ecpri_dma_hal_write_reg_fields(enum ecpri_dma_hal_reg_name reg,
	const void *fields)
{
	ecpri_dma_hal_write_reg_n_fields(reg, 0, fields);
}

/*
 * ecpri_dma_hal_write_ep_reg() - Write to ep reg a raw value
 */
void ecpri_dma_hal_write_ep_reg(enum ecpri_dma_hal_reg_name reg, u32 ep_num, u32 val);

/*
 * ecpri_dma_hal_write_ep_reg_n() - Write to ep reg a raw value of n parameterized reg
 */
void ecpri_dma_hal_write_ep_reg_n(enum ecpri_dma_hal_reg_name reg, u32 n, u32 ep_num, u32 val);

/*
 * Get the offset of a m/n parameterized register
 */
u32 ecpri_dma_hal_get_reg_mn_ofst(enum ecpri_dma_hal_reg_name reg, u32 m, u32 n);

/*
* Get the offset of a n,k register
*/
u32 ecpri_dma_hal_get_reg_nk_offset(enum ecpri_dma_hal_reg_name reg, u32 n, u32 l);

/*
 * Get the offset of a n parameterized register
 */
static inline u32 ecpri_dma_hal_get_reg_n_ofst(enum ecpri_dma_hal_reg_name reg, u32 n)
{
	return ecpri_dma_hal_get_reg_mn_ofst(reg, 0, n);
}

/*
 * Get the offset of a ep register according to ep index
 */
u32 ecpri_dma_hal_get_ep_reg_offset(enum ecpri_dma_hal_reg_name reg, u32 ep_num);

/*
 * Get the offset of a register
 */
static inline u32 ecpri_dma_hal_get_reg_ofst(enum ecpri_dma_hal_reg_name reg)
{
	return ecpri_dma_hal_get_reg_mn_ofst(reg, 0, 0);
}

/*
 * Get the register base address
 */
u32 ecpri_dma_hal_get_reg_base(void);

#endif /* _DMAHAL_REG_H_ */
