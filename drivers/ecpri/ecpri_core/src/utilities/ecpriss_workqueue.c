/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2024 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include "ecpriss_core.h"
#include "ecpriss_workqueue.h"


struct work_struct          ecpriss_eth_events_rdy;
struct work_struct          ecpriss_dma_events_rdy;
struct work_struct          ecpriss_eth_topology_events_rdy;
struct work_struct          ecpriss_interrupt_events_rdy;
struct work_struct          ecpriss_ssr_events_rdy;


struct workqueue_struct     *events_workqueue;
struct workqueue_struct     *interrupt_events_workqueue;
struct workqueue_struct     *ecpri_delay_wq;

struct ecpri_delayed_work_q_params ecpri_delay_wq_v;
struct ecpri_delayed_work_q_params *ecpri_delay_wq_p = &ecpri_delay_wq_v;

struct mutex ecpri_delay_wq_mutex_lock;

/**
 * ecpriss_queue_work()
 *
 *
 *
 * Returns:	0 on success, negative on failure
 */
int ecpriss_queue_work(struct workqueue_struct    *ecpriss_wq,
		struct work_struct         *ecpriss_work)
{
	if (ecpriss_wq) {
		queue_work(ecpriss_wq, ecpriss_work);
	}

	return 0;
}

int ecpriss_queue_delayed_work(		struct delayed_work	*ecpriss_delay_work,int delay_ms)
{
	mutex_lock(&ecpri_delay_wq_mutex_lock);
	if(ecpri_delay_wq)
	{
		queue_delayed_work(ecpri_delay_wq, ecpriss_delay_work,msecs_to_jiffies(delay_ms));
	}
	mutex_unlock(&ecpri_delay_wq_mutex_lock);

	return 0;

}

/**
 * ecpriss_initialize_workq()
 *
 * Args - Initialize a work queue
 *
 * Returns:	0 on success, negative on failure
 */
int ecpriss_initialize_workq(void)
{
	int ret = 0;
	do {
		if(ecpriss_pdata->events_workqueue->kernel_events_workqueue == NULL) {
			events_workqueue =
				create_singlethread_workqueue("ecpriss_events_workq");
			ecpriss_pdata->events_workqueue->kernel_events_workqueue =
				events_workqueue;
			if(events_workqueue == NULL) {
				ret = -1;
				break;
			}
		}

		if(ecpriss_pdata->interrupts_workqueue->ecpriss_interrupts_workq == NULL) {
			interrupt_events_workqueue =
				create_singlethread_workqueue("ecpriss_interrupts_workq");
			ecpriss_pdata->interrupts_workqueue->ecpriss_interrupts_workq =
				interrupt_events_workqueue;
			if(interrupt_events_workqueue == NULL) {
				ret = -1;
				break;
			}
		}

		INIT_WORK(&ecpriss_dma_events_rdy,
				ecpriss_dma_event_processing_wq);
		ecpriss_pdata->events_workqueue->ecpriss_dma_events_rdy_work=
			&ecpriss_dma_events_rdy;
		INIT_WORK(&ecpriss_eth_topology_events_rdy,
				ecpriss_eth_topology_init_wq);
		ecpriss_pdata->events_workqueue->ecpriss_eth_topology_events_rdy_work =
			&ecpriss_eth_topology_events_rdy;
		INIT_WORK(&ecpriss_eth_events_rdy, ecpriss_eth_event_processing_wq);
		ecpriss_pdata->events_workqueue->ecpriss_eth_events_rdy_work =
			&ecpriss_eth_events_rdy;
		INIT_WORK(&ecpriss_interrupt_events_rdy, ecpriss_interrupt_events_processing_wq);
		ecpriss_pdata->interrupts_workqueue->ecpriss_interrupt_events_rdy_work=
			&ecpriss_interrupt_events_rdy;



	} while(0);

	return ret;
}

int ecpriss_initialize_workq_v2(void)
{
	int ret = 0;
	do {
		if(ecpriss_pdata_v2->events_workqueue->kernel_events_workqueue == NULL) {
			events_workqueue =
				create_singlethread_workqueue("ecpriss_events_workq");
			ecpriss_pdata_v2->events_workqueue->kernel_events_workqueue =
				events_workqueue;
			if(events_workqueue == NULL) {
				ret = -1;
				break;
			}
		}

		if(ecpriss_pdata_v2->interrupts_workqueue->ecpriss_interrupts_workq == NULL) {
			interrupt_events_workqueue =
				create_singlethread_workqueue("ecpriss_interrupts_workq");
			ecpriss_pdata_v2->interrupts_workqueue->ecpriss_interrupts_workq =
				interrupt_events_workqueue;
			if(interrupt_events_workqueue == NULL) {
				ret = -1;
				break;
			}
		}

		INIT_WORK(&ecpriss_dma_events_rdy,
				ecpriss_dma_event_processing_wq);
		ecpriss_pdata_v2->events_workqueue->ecpriss_dma_events_rdy_work=
			&ecpriss_dma_events_rdy;
		INIT_WORK(&ecpriss_eth_topology_events_rdy,
				ecpriss_eth_topology_init_wq);
		ecpriss_pdata_v2->events_workqueue->ecpriss_eth_topology_events_rdy_work =
			&ecpriss_eth_topology_events_rdy;
		INIT_WORK(&ecpriss_eth_events_rdy, ecpriss_eth_event_processing_wq);
		ecpriss_pdata_v2->events_workqueue->ecpriss_eth_events_rdy_work =
			&ecpriss_eth_events_rdy;
		INIT_WORK(&ecpriss_interrupt_events_rdy, ecpriss_interrupt_events_processing_wq);
		ecpriss_pdata_v2->interrupts_workqueue->ecpriss_interrupt_events_rdy_work=
			&ecpriss_interrupt_events_rdy;

		INIT_WORK(&ecpriss_ssr_events_rdy, ecpriss_ssr_events_processing_wq);
		ecpriss_pdata_v2->events_workqueue->ecpriss_ssr_events_rdy_work=
			&ecpriss_ssr_events_rdy;

		mutex_init(&ecpri_delay_wq_mutex_lock);
		ecpri_delay_wq = create_singlethread_workqueue("ecpri_delayed_workq");
		INIT_DELAYED_WORK(&ecpri_delay_wq_p->wq_item, ecpriss_update_stats_and_requeue);


	} while(0);

	return ret;
}
/**
 * ecpriss_destroy_workq()
 *
 * Args - Destroy a work queue
 *
 * Returns:	0 on success, negative on failure
 */
int ecpriss_destroy_workq(void)
{
	do {
		if (events_workqueue) {

			flush_workqueue(events_workqueue);
			destroy_workqueue(events_workqueue);

			if(ecpriss_pdata_v2->events_workqueue->kernel_events_workqueue) {
				ecpriss_pdata_v2->events_workqueue->kernel_events_workqueue = NULL;
			}
		}


		if (interrupt_events_workqueue) {
			flush_workqueue(interrupt_events_workqueue);
			destroy_workqueue(interrupt_events_workqueue);

			if(ecpriss_pdata_v2->interrupts_workqueue->ecpriss_interrupts_workq) {

				ecpriss_pdata_v2->interrupts_workqueue->ecpriss_interrupts_workq = NULL;
			}
		}

		mutex_lock(&ecpri_delay_wq_mutex_lock);

		//cancel delayed work
		cancel_delayed_work_sync(&ecpri_delay_wq_p->wq_item);

		flush_workqueue(ecpri_delay_wq);
		destroy_workqueue(ecpri_delay_wq);
		ecpri_delay_wq = NULL;

		mutex_unlock(&ecpri_delay_wq_mutex_lock);
		mutex_destroy(&ecpri_delay_wq_mutex_lock);


	} while(0);
	return 0;
}


