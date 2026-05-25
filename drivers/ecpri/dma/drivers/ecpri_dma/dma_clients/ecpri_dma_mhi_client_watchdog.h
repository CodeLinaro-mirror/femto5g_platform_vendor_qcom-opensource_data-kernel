/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.
 */

#ifndef _ECPRI_DMA_MHI_CLIENT_WATCHDOG_H_
#define _ECPRI_DMA_MHI_CLIENT_WATCHDOG_H_

#include <linux/time.h>
#include <linux/timer.h>
#include <linux/workqueue.h>

/* Watchdog timeout threshold in microseconds */
/* NOTE: For testing/validation with 80us normal callback time:
 *       Set to 100us to trigger on any delay beyond normal
 * For production: Use 1000000us (1 second) to detect real CPU starvation */
#define ECPRI_DMA_MHI_WQ_WATCHDOG_TIMEOUT_US (1000000)

/* Watchdog check interval in microseconds */
/* NOTE: For testing/validation: Check every 50us
 * For production: Use 500000us (500ms) for periodic monitoring */
#define ECPRI_DMA_MHI_WQ_WATCHDOG_CHECK_INTERVAL_US (500000)

/**
 * struct ecpri_dma_mhi_wq_watchdog - Workqueue watchdog context
 * @timer: Timer for periodic watchdog checks
 * @last_execution_time: Timestamp of last workqueue execution
 * @work_queued_time: Timestamp when work was queued
 * @pending_work_count: Number of pending work items
 * @timeout_count: Number of timeout events detected
 * @recovery_count: Number of times recovery was triggered
 * @enabled: Whether watchdog is enabled
 * @lock: Spinlock to protect watchdog state
 * @recovery_wq: High-priority workqueue for recovery
 * @pending_work: Pointer to pending work item for recovery
 * @recovery_work: Work item to handle recovery in process context
 * @work_to_recover: Work item that needs recovery
 */
struct ecpri_dma_mhi_wq_watchdog {
	struct timer_list timer;
	ktime_t last_execution_time;
	ktime_t work_queued_time;
	atomic_t pending_work_count;
	atomic_t timeout_count;
	atomic_t recovery_count;
	bool enabled;
	spinlock_t lock;
	struct workqueue_struct *recovery_wq;
	struct work_struct *pending_work;
	struct work_struct recovery_work;
	struct work_struct *work_to_recover;
};

/**
 * ecpri_dma_mhi_wq_watchdog_init() - Initialize workqueue watchdog
 * @watchdog: Watchdog context to initialize
 *
 * Return: 0 on success, negative error code on failure
 */
int ecpri_dma_mhi_wq_watchdog_init(struct ecpri_dma_mhi_wq_watchdog *watchdog);

/**
 * ecpri_dma_mhi_wq_watchdog_destroy() - Destroy workqueue watchdog
 * @watchdog: Watchdog context to destroy
 */
void ecpri_dma_mhi_wq_watchdog_destroy(struct ecpri_dma_mhi_wq_watchdog *watchdog);

/**
 * ecpri_dma_mhi_wq_watchdog_work_queued() - Notify watchdog that work was queued
 * @watchdog: Watchdog context
 * @work: Pointer to the work item being queued
 */
void ecpri_dma_mhi_wq_watchdog_work_queued(struct ecpri_dma_mhi_wq_watchdog *watchdog,
					    struct work_struct *work);

/**
 * ecpri_dma_mhi_wq_watchdog_work_executed() - Notify watchdog that work executed
 * @watchdog: Watchdog context
 */
void ecpri_dma_mhi_wq_watchdog_work_executed(struct ecpri_dma_mhi_wq_watchdog *watchdog);

/**
 * ecpri_dma_mhi_wq_watchdog_enable() - Enable watchdog monitoring
 * @watchdog: Watchdog context
 */
void ecpri_dma_mhi_wq_watchdog_enable(struct ecpri_dma_mhi_wq_watchdog *watchdog);

/**
 * ecpri_dma_mhi_wq_watchdog_disable() - Disable watchdog monitoring
 * @watchdog: Watchdog context
 */
void ecpri_dma_mhi_wq_watchdog_disable(struct ecpri_dma_mhi_wq_watchdog *watchdog);

#endif /* _ECPRI_DMA_MHI_CLIENT_WATCHDOG_H_ */
