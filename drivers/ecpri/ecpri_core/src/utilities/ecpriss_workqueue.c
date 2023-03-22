/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include "ecpriss_core.h"
#include "ecpriss_workqueue.h"


struct work_struct          ecpriss_eth_events_rdy;
struct work_struct          ecpriss_dma_events_rdy;
struct work_struct          ecpriss_eth_topology_events_rdy;
struct work_struct          ecpriss_interrupt_events_rdy;

struct workqueue_struct     *events_workqueue;
struct workqueue_struct     *interrupt_events_workqueue;

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
			destroy_workqueue(events_workqueue);
			//events_workqueue  = NULL;
		}

		if (interrupt_events_workqueue) {
			destroy_workqueue(interrupt_events_workqueue);
			//interrupt_events_workqueue = NULL;
		}
	} while(0);
	return 0;
}




