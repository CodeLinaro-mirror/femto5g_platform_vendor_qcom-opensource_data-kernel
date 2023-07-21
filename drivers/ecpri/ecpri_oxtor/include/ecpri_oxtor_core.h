/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef ECPRISS_CORE_H_
#define ECPRISS_CORE_H_

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <net/net_namespace.h>
#include <linux/signal.h>           /* Definition of SIGEV_* constants */
#include <linux/jiffies.h>
#include <linux/uaccess.h>
#include <linux/workqueue.h>
#include <linux/of_device.h>
#include <linux/debugfs.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/atomic.h>
#include <linux/fs.h>

#include "ecpri_oxtor_tx.h"
#include "ecpri_oxtor_rx.h"
#include "ecpri_oxtor_ioctl.h"

#define ECPRI_OXTOR_XU_ID_DEFAULT 0xffffffff

#define ECPRI_OXTOR_QTIMER_FREQ_HZ  19200000
#define BW_CNT_ENABLE 1
#define BW_CNT_DISABLE 0
#define BW_CNT_CLEAR_SET 1
#define BW_CNT_CLEAR_RESET 0


#undef pr_fmt
#define pr_fmt(fmt) "::%s:%d::" fmt, __func__,__LINE__
typedef struct
{
	u32 major_num;
	u32 minor_num;
	dev_t ecpri_oxtor_dev;

	struct cdev ecpri_oxtor_cdev;
	struct class *dev_class;
	struct device *dev_number;

	u8 ref;

}ecpri_oxtor_device_info_s;

/**
  Oxtor Core context
 **/
typedef struct{

	/*init state*/
	bool init;
	/*Core id*/
	u32 xu_id;
	ecpri_oxtor_device_info_s device_info;

	ecpri_oxtor_tx_ring_cntxt_s *tx_ring_cntxt_ptr;
	ecpri_oxtor_rx_ring_cntxt_s *rx_ring_cntxt_ptr;
	void			    *ecpri_oxtor_logbuf;
	/* eCPRI HW Version*/
	int hw_ver;

} ecpri_oxtor_core_cntxt_s;


/**
 * enum dev mode
 */
typedef enum {
	ECPRI_oxtor_DEV_MODE_DU = 0,
	ECPRI_oxtor_DEV_MODE_RU,
	ECPRI_oxtor_DEV_MODE_MAX
}ecpri_oxtor_dev_mode_e;

/**
 * enum ecpriss_port_dir
 */
typedef enum {
	ECPRI_oxtor_PORT_DIR_RX = 0,
	ECPRI_oxtor_PORT_DIR_TX,
	ECPRI_oxtor_PORT_DIR_MAX
}ecpri_oxtor_port_dir_e;

/**
 * enum ecpriss_eth_port_type - port type
 */
typedef enum {
	ECPRISS_PORT_TYPE_FH = 0,
	ECPRISS_PORT_TYPE_C2C,
	ECPRISS_PORT_TYPE_L2,
	ECPRISS_PORT_TYPE_OC,
	ECPRISS_PORT_TYPE_MAX
}ecpriss_port_type_e;

typedef struct
{
	struct work_struct          *ecpriss_interrupt_events_rdy_work;
	struct workqueue_struct     *ecpriss_interrupts_workq;
}ecpri_oxtor_irq_wq_params_s;

extern ecpri_oxtor_core_cntxt_s *ecpri_oxtor_core_context;
#endif /* ECPRISS_CORE_H_ */
