/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.
 */

#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/spinlock.h>
#include <linux/atomic.h>
#include <linux/time.h>
#include <linux/jiffies.h>
#include "ecpri_dma_mhi_client_watchdog.h"
#include "../ecpri_dma_i.h"

/**
 * ecpri_dma_mhi_wq_watchdog_recovery_work() - Handle recovery in process context
 * @work: Work structure
 *
 * This function runs in process context and can safely call cancel_work_sync
 */
static void ecpri_dma_mhi_wq_watchdog_recovery_work(struct work_struct *work)
{
	struct ecpri_dma_mhi_wq_watchdog *watchdog =
		container_of(work, struct ecpri_dma_mhi_wq_watchdog, recovery_work);
	struct work_struct *work_to_recover;
	unsigned long flags;

	spin_lock_irqsave(&watchdog->lock, flags);
	work_to_recover = watchdog->work_to_recover;
	watchdog->work_to_recover = NULL;
	spin_unlock_irqrestore(&watchdog->lock, flags);

	if (work_to_recover) {
		/* Cancel from original workqueue and requeue on high-priority one */
		if (cancel_work_sync(work_to_recover)) {
			DMADBG_LOW("Watchdog: Successfully cancelled stuck work\n");
			queue_work(watchdog->recovery_wq, work_to_recover);
			DMADBG_LOW("Watchdog: Work requeued on high-priority workqueue\n");
		} else {
			DMADBG_LOW("Watchdog: Work already executing or completed\n");
		}
	}
}

/**
 * ecpri_dma_mhi_wq_watchdog_timer_cb() - Watchdog timer callback
 * @t: Timer list structure
 *
 * This function is called periodically to check if workqueue is stuck
 */
static void ecpri_dma_mhi_wq_watchdog_timer_cb(struct timer_list *t)
{
	struct ecpri_dma_mhi_wq_watchdog *watchdog =
		from_timer(watchdog, t, timer);
	unsigned long flags;
	ktime_t current_time;
	s64 delay_us;
	int pending_count;
	bool timeout_detected = false;

	if (!watchdog->enabled)
		return;

	spin_lock_irqsave(&watchdog->lock, flags);

	pending_count = atomic_read(&watchdog->pending_work_count);
	
	/* Only check if there's pending work */
	if (pending_count > 0) {
		current_time = ktime_get();
		delay_us = ktime_us_delta(current_time, watchdog->work_queued_time);

		/* Check if delay exceeds threshold */
		if (delay_us > ECPRI_DMA_MHI_WQ_WATCHDOG_TIMEOUT_US) {
			timeout_detected = true;
			atomic_inc(&watchdog->timeout_count);

			DMADBG_LOW("=== DMA MHI Workqueue Watchdog: TIMEOUT DETECTED ===\n");
			DMADBG_LOW("Work queued at: %lld us\n",
				ktime_to_us(watchdog->work_queued_time));
			DMADBG_LOW("Current time: %lld us\n",
				ktime_to_us(current_time));
			DMADBG_LOW("Delay: %lld us (threshold: %d us)\n",
				delay_us, ECPRI_DMA_MHI_WQ_WATCHDOG_TIMEOUT_US);
			DMADBG_LOW("Pending work count: %d\n", pending_count);
			DMADBG_LOW("Total timeout events: %d\n",
				atomic_read(&watchdog->timeout_count));
			DMADBG_LOW("Last successful execution: %lld us\n",
				ktime_to_us(watchdog->last_execution_time));

			/* RECOVERY CODE COMMENTED OUT - See note below
			 *
			 * NOTE: Recovery mechanism has fundamental limitations:
			 * 1. Cannot cancel work that's already executing (only queued work)
			 * 2. Risk of double callbacks if work completes after recovery
			 * 3. Only tracks single work item, but multiple can be queued
			 *
			 * SOLUTION: The async_wq is already created with WQ_HIGHPRI flag,
			 * which prevents CPU starvation at the source. The watchdog now
			 * serves as a monitoring/debugging tool only.
			 */

			/* COMMENTED OUT - Recovery code kept for reference
			if (watchdog->pending_work && watchdog->recovery_wq) {
				watchdog->work_to_recover = watchdog->pending_work;
				atomic_inc(&watchdog->recovery_count);
				DMADBG_LOW("Scheduling recovery work\n");
				DMADBG_LOW("Recovery count: %d\n",
					atomic_read(&watchdog->recovery_count));
				queue_work(watchdog->recovery_wq, &watchdog->recovery_work);
			}
			*/
			DMADBG_LOW("===================================================\n");
		}
	}

	spin_unlock_irqrestore(&watchdog->lock, flags);

	/* Reschedule timer if still enabled */
	if (watchdog->enabled) {
		mod_timer(&watchdog->timer,
			jiffies + usecs_to_jiffies(
				ECPRI_DMA_MHI_WQ_WATCHDOG_CHECK_INTERVAL_US));
	}
}

/**
 * ecpri_dma_mhi_wq_watchdog_init() - Initialize workqueue watchdog
 * @watchdog: Watchdog context to initialize
 *
 * Return: 0 on success, negative error code on failure
 */
int ecpri_dma_mhi_wq_watchdog_init(struct ecpri_dma_mhi_wq_watchdog *watchdog)
{
	if (!watchdog) {
		DMAERR("Null watchdog pointer\n");
		return -EINVAL;
	}

	/* Initialize timer */
	timer_setup(&watchdog->timer, ecpri_dma_mhi_wq_watchdog_timer_cb, 0);

	/* Initialize timestamps */
	watchdog->last_execution_time = ktime_get();
	watchdog->work_queued_time = ktime_get();

	/* Initialize atomic counters */
	atomic_set(&watchdog->pending_work_count, 0);
	atomic_set(&watchdog->timeout_count, 0);
	atomic_set(&watchdog->recovery_count, 0);

	/* Initialize spinlock */
	spin_lock_init(&watchdog->lock);

	/* Create high-priority recovery workqueue */
	watchdog->recovery_wq = alloc_workqueue("ecpri_dma_mhi_recovery_wq",
		WQ_HIGHPRI | WQ_MEM_RECLAIM | WQ_UNBOUND, 1);
	if (!watchdog->recovery_wq) {
		DMAERR("Failed to create recovery workqueue\n");
		return -ENOMEM;
	}

	/* Initialize pending work pointer */
	watchdog->pending_work = NULL;
	watchdog->work_to_recover = NULL;

	/* Initialize recovery work */
	INIT_WORK(&watchdog->recovery_work, ecpri_dma_mhi_wq_watchdog_recovery_work);

	/* Watchdog starts disabled */
	watchdog->enabled = false;

	DMADBG("Workqueue watchdog initialized (timeout: %d us, check interval: %d us)\n",
		ECPRI_DMA_MHI_WQ_WATCHDOG_TIMEOUT_US,
		ECPRI_DMA_MHI_WQ_WATCHDOG_CHECK_INTERVAL_US);

	return 0;
}

/**
 * ecpri_dma_mhi_wq_watchdog_destroy() - Destroy workqueue watchdog
 * @watchdog: Watchdog context to destroy
 */
void ecpri_dma_mhi_wq_watchdog_destroy(struct ecpri_dma_mhi_wq_watchdog *watchdog)
{
	if (!watchdog)
		return;

	/* Disable watchdog first */
	ecpri_dma_mhi_wq_watchdog_disable(watchdog);

	/* Delete timer */
	del_timer_sync(&watchdog->timer);

	/* Cancel any pending recovery work */
	cancel_work_sync(&watchdog->recovery_work);

	/* Destroy recovery workqueue */
	if (watchdog->recovery_wq) {
		destroy_workqueue(watchdog->recovery_wq);
		watchdog->recovery_wq = NULL;
	}

	DMADBG("Workqueue watchdog destroyed (total timeouts: %d, recoveries: %d)\n",
		atomic_read(&watchdog->timeout_count),
		atomic_read(&watchdog->recovery_count));
}

/**
 * ecpri_dma_mhi_wq_watchdog_work_queued() - Notify watchdog that work was queued
 * @watchdog: Watchdog context
 */
void ecpri_dma_mhi_wq_watchdog_work_queued(struct ecpri_dma_mhi_wq_watchdog *watchdog,
					    struct work_struct *work)
{
	unsigned long flags;

	if (!watchdog || !watchdog->enabled)
		return;

	spin_lock_irqsave(&watchdog->lock, flags);

	/* Record timestamp when work was queued */
	watchdog->work_queued_time = ktime_get();

	/* Store pointer to pending work for potential recovery */
	watchdog->pending_work = work;

	/* Increment pending work counter */
	atomic_inc(&watchdog->pending_work_count);

	DMADBG_LOW("Work queued, pending count: %d\n",
		atomic_read(&watchdog->pending_work_count));

	spin_unlock_irqrestore(&watchdog->lock, flags);
}

/**
 * ecpri_dma_mhi_wq_watchdog_work_executed() - Notify watchdog that work executed
 * @watchdog: Watchdog context
 */
void ecpri_dma_mhi_wq_watchdog_work_executed(struct ecpri_dma_mhi_wq_watchdog *watchdog)
{
	unsigned long flags;
	ktime_t current_time;
	s64 delay_us;
	int pending_count;

	if (!watchdog || !watchdog->enabled)
		return;

	spin_lock_irqsave(&watchdog->lock, flags);

	current_time = ktime_get();

	/* Calculate delay from queue to execution */
	delay_us = ktime_us_delta(current_time, watchdog->work_queued_time);

	/* Update last execution time */
	watchdog->last_execution_time = current_time;

	/* DON'T clear pending_work pointer yet - keep it for potential recovery
	 * It will be cleared by the timer if no timeout occurs */
	/* watchdog->pending_work = NULL; */

	/* Decrement pending work counter */
	pending_count = atomic_dec_return(&watchdog->pending_work_count);

	/* Log warning if delay is significant */
	if (delay_us > 90) {
		DMADBG_LOW("DMA MHI Workqueue: High delay detected: %lld us (pending: %d)\n",
			delay_us, pending_count);
	}

	DMADBG_LOW("Work executed after %lld us, pending count: %d\n",
		delay_us, pending_count);

	spin_unlock_irqrestore(&watchdog->lock, flags);
}

/**
 * ecpri_dma_mhi_wq_watchdog_enable() - Enable watchdog monitoring
 * @watchdog: Watchdog context
 */
void ecpri_dma_mhi_wq_watchdog_enable(struct ecpri_dma_mhi_wq_watchdog *watchdog)
{
	unsigned long flags;

	if (!watchdog)
		return;

	spin_lock_irqsave(&watchdog->lock, flags);

	if (!watchdog->enabled) {
		watchdog->enabled = true;

		/* Start the timer */
		mod_timer(&watchdog->timer,
			jiffies + usecs_to_jiffies(
				ECPRI_DMA_MHI_WQ_WATCHDOG_CHECK_INTERVAL_US));

		DMADBG("Workqueue watchdog enabled\n");
	}

	spin_unlock_irqrestore(&watchdog->lock, flags);
}

/**
 * ecpri_dma_mhi_wq_watchdog_disable() - Disable watchdog monitoring
 * @watchdog: Watchdog context
 */
void ecpri_dma_mhi_wq_watchdog_disable(struct ecpri_dma_mhi_wq_watchdog *watchdog)
{
	unsigned long flags;

	if (!watchdog)
		return;

	spin_lock_irqsave(&watchdog->lock, flags);

	if (watchdog->enabled) {
		watchdog->enabled = false;

		DMADBG("Workqueue watchdog disabled\n");
	}

	spin_unlock_irqrestore(&watchdog->lock, flags);

	/* Stop the timer (outside spinlock to avoid deadlock) */
	del_timer_sync(&watchdog->timer);
}
