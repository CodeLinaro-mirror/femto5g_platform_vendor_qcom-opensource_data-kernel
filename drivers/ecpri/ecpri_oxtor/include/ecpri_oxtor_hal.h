/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef ECPRISS_HAL_H_
#define ECPRISS_HAL_H_

#include "ecpri_oxtor_hwio.h"
#include "ecpri_global_hwio.h"
#include "ecpri_oxtor_hwio_def.h"
#include "ecpri_global_hwio_def.h"


#define ECPRI_OXTOR_BASE             0x09228000
#define ECPRI_OXTOR_BASE_SIZE        0x2000

#define ECPRI_OXTOR_GLOBAL_BASE      0x09210000
#define ECPRI_OXTOR_GLOBAL_BASE_SIZE 0x10000


/*
 * struct ipahal_context - HAL global context data
 * @hw_type: ORAN XTOR H/W type/version.
 * @base: Base address to be used for accessing IPA memory. This is
 *  I/O memory mapped address.
 *  Controlled by debugfs. default is off
 * @dent: Debugfs folder dir entry
 * @ipa_pdev: IPA Platform Device. Will be used for DMA memory
 * @empty_fltrt_tbl: Empty table to be used at tables init.
 */
typedef struct ecpriss_oxtor_hal_context {
	bool init;
	unsigned int hw_type;
	struct device *pdev;
	void *regdumpbuf;

	u32 phy_base;
	u32 phy_global_base;

	void __iomem *base;
	void __iomem *global_base;

}ecpriss_oxtor_hal_context_s;


typedef enum
{
	ECPRI_OXTOR_REG_TYPE_GLOBAL,
	ECPRI_OXTOR_REG_TYPE_BASE,
	ECPRI_OXTOR_REG_TYPE_MAX
} ecpri_oxtor_hal_reg_type_e;

/*
 * Registers names
 *
 * NOTE:: Any change to this enum, need to change to ipareg_name_to_str
 *	array as well.
 */

enum ecpriss_oxtor_hal_reg_name {

	ECPRI_GLOBAL_XTOR_CFG,
	ECPRI_ORAN_XTOR_RX_KBYTE_CNT_CTL,
	ECPRI_ORAN_XTOR_QTIMER_OFFSET_MSB,
	ECPRI_ORAN_XTOR_RX_n_MAX_LATENCY_EXPECTED,
	ECPRI_ORAN_XTOR_RX_n_CTL_REG,
	ECPRI_ORAN_XTOR_RX_n_ERROR_STATUS_DUMP_REG,
	ECPRI_ORAN_XTOR_TX_n_CTL_REG,
	ECPRI_ORAN_XTOR_TX_n_CMD_m_k,
	ECPRI_ORAN_XTOR_TX_n_DATA_IDXS_REG,
	ECPRI_ORAN_XTOR_RX_n_ERROR_REG,
	ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_1,
	ECPRI_ORAN_XTOR_RX_KBYTE_CNT_QTIMER_DELTA_0,
	ECPRI_ORAN_XTOR_RX_n_KBYTE_CNT_REG,
	ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_1,
	ECPRI_ORAN_XTOR_RX_n_ERR_COUNTERS_0,
	ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_0_REG,
	ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_1_REG,
	ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_2_REG,
	ECPRI_ORAN_XTOR_RX_n_ERROR_DUMP_3_REG,
	ECPRI_ORAN_XTOR_TX_n_BACKPRESSURE_CNT_REG,
	ECPRI_ORAN_XTOR_TX_n_PKT_CNT_REG,
	ECPRI_ORAN_XTOR_RX_n_PKT_CNT_REG,
	ECPRI_ORAN_XTOR_TX_n_RD_IDX_WRAP_CNT,

	ECPRI_OXTOR_OXTOR_MAX
};

/*
 * struct ecpriss_hal_reg_obj - Register H/W information for specific ECPRISS
 * version
 * @construct - CB to construct register value from abstracted structure
 * @parse - CB to parse register value to abstracted structure
 * @offset - register offset relative to base address
 * @n_ofst - N parameterized register sub-offset
 * @n_start - starting n for n_registers used for printing
 * @n_end - ending n for n_registers used for printing
 * @en_print - enable this register to be printed when the device crashes
 */
struct ecpriss_oxtor_hal_reg_obj {
	void (*construct)(enum ecpriss_oxtor_hal_reg_name reg,
			const void *fields,
			u32 *val);
	void (*parse)(enum ecpriss_oxtor_hal_reg_name reg, void *fields,
			u32 val);
	u32 base;
	u32 offset;
	u32 n_ofst;
	int n_start;
	int n_end;
	bool en_print;
	u32 m_ofst;
	u32 k_ofst;
};


typedef enum ecpriss_oxtor_hw_name
{
	ECPRISS_OXTOR_HW_v1_0,
	ECPRISS_OXTOR_HW_MAX
}ecpriss_xbar_hw_name_e;

#define ECPRISS_HAL_SETFIELD(val, shift, mask) (((val) << (shift)) & (mask))
#define ECPRISS_HAL_SETFIELD_IN_REG(reg, val, shift, mask) \
	(reg |= ((val) << (shift)) & (mask))
#define ECPRISS_HAL_GETFIELD_FROM_REG(reg, shift, mask) \
	(((reg) & (mask)) >> (shift))

int ecpriss_oxtor_hal_ctx_init(void);

u32 ecpriss_oxtor_hal_read_reg_n(enum ecpriss_oxtor_hal_reg_name reg, u32 n);


u32 ecpriss_oxtor_hal_read_reg_mn(enum ecpriss_oxtor_hal_reg_name reg, u32 m,
		u32 n);

void ecpriss_oxtor_hal_write_reg_mn(enum ecpriss_oxtor_hal_reg_name reg, u32 m,
		u32 n, u32 val);

u32 ecpriss_oxtor_hal_read_reg_n_fields(enum ecpriss_oxtor_hal_reg_name reg,
		u32 n, void *fields);

u32 ecpriss_oxtor_hal_read_reg_mn_fields(enum ecpriss_oxtor_hal_reg_name reg,
		u32 m, u32 n, void *fields);

void ecpriss_oxtor_hal_write_reg_n_fields(ecpri_oxtor_hal_reg_type_e reg_type,
		enum ecpriss_oxtor_hal_reg_name reg, u32 n,
		const void *fields);
/*
 * ecpriss_oxtor_hal_reg_name_str() - returns string that represent the register
 * @reg_name: [in] register name
 */
const char *ecpriss_oxtor_hal_reg_name_str(
		enum ecpriss_oxtor_hal_reg_name reg_name);

void ecpriss_oxtor_hal_write_reg_mn_fields(enum ecpriss_oxtor_hal_reg_name reg,
		u32 m, u32 n,
		void *fields);
void ecpriss_oxtor_hal_write_reg_mnk_fields(ecpri_oxtor_hal_reg_type_e reg_type,
		enum ecpriss_oxtor_hal_reg_name reg, u32 m, u32 n,
		u32 k, void *fields);

#endif
