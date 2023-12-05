/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include <linux/slab.h>
#include <linux/notifier.h>
#include "ldmm_shrd_notifr.h"
#include "ldmm_shrd_genntlk.h"
#include "ldmm_ipc_log.h"

//#define IS_MULTICAST_EN

extern struct blocking_notifier_head lassen_mtip_fault_notifr;
extern struct blocking_notifier_head lassen_qxdm_timer_update_notifr;

//default logging timer value 
int qxdm_logging_timer_value = 10;

bool QXDM_NOTIFICATION_ENABLED = false;

void ldmm_enable_notification()
{
	QXDM_NOTIFICATION_ENABLED = true;
}

void ldmm_disable_notification()
{
	QXDM_NOTIFICATION_ENABLED = false;
}

int ldmm_mtip_fault_hndlr(struct notifier_block *nb, unsigned long event, void *arg)
{
	int ret = NOTIFY_DONE;
	uint32_t interface = 0;
	uint32_t val = 0;

	if(!arg){
		LDMM_LOG_ERR("%s:Invalid Param NULL\n", __func__);
		return NOTIFY_BAD;
	}
	interface = (uint32_t)*((uint32_t*) arg);

	LDMM_SETFIELD_IN_REG(val, interface, LINK_ID_SHIFT, LINK_ID_MASK);

	LDMM_LOG_INFO("ldmm_mtip_fault_hndlr interface = %u\n",interface);

	switch(event){
		case HIGH_BER_SET:
			LDMM_LOG_ERR("HIGH_BER_SET\n");
			LDMM_SETFIELD_IN_REG(val, LDMM_HIGH_BER_SET, FAULT_NUM_SHIFT, FAULT_NUM_MASK);
			break;

		case HIGH_BER_CLR:
			LDMM_LOG_ERR("HIGH_BER_CLR\n");
			LDMM_SETFIELD_IN_REG(val, LDMM_HIGH_BER_CLR, FAULT_NUM_SHIFT, FAULT_NUM_MASK);
			break;

		case IF_DOWN:
			LDMM_LOG_ERR("IF_DOWN\n");
#if 0
			LDMM_SETFIELD_IN_REG(val, LDMM_IF_DOWN, FAULT_NUM_SHIFT, FAULT_NUM_MASK);
#else
			return ret;
#endif
			break;

		case IF_UP:
			LDMM_LOG_ERR("IF_UP\n");
#if 0
			LDMM_SETFIELD_IN_REG(val, LDMM_IF_UP, FAULT_NUM_SHIFT, FAULT_NUM_MASK);
#else
			return ret;
#endif
			break;

		case PCS_IF_UP:
			LDMM_LOG_ERR("PCS_IF_UP\n");
			LDMM_SETFIELD_IN_REG(val, LDMM_PCS_IF_UP, FAULT_NUM_SHIFT, FAULT_NUM_MASK);
			if(QXDM_NOTIFICATION_ENABLED)
				ldmm_qxdm_logger_link_change_notification();
			break;

		case PCS_IF_DOWN:
			LDMM_LOG_ERR("PCS_IF_DOWN\n");
			LDMM_SETFIELD_IN_REG(val, LDMM_PCS_IF_DOWN, FAULT_NUM_SHIFT, FAULT_NUM_MASK);
			if(QXDM_NOTIFICATION_ENABLED)
				ldmm_qxdm_logger_link_change_notification();
			break;

		default:
			LDMM_LOG_ERR("Unknown Fault detected \n");
			return NOTIFY_BAD;
	}

	fult_mgmt_snd(val ,UNICAST_MSG);

#ifdef IS_MULTICAST_EN
	fult_mgmt_snd(val ,MULTICAST_MSG);
#endif
	return ret;
}

int ldmm_qxdm_timer_update_hndlr(struct notifier_block *nb, unsigned long timer_value, void *arg)
{
	ldmm_qxdm_logger_update_timer_value((int)timer_value);
	return 0;
}

static struct notifier_block ldmm_mtip_fault_event = {
	.notifier_call = ldmm_mtip_fault_hndlr,
};

static struct notifier_block ldmm_qxdm_timer_update_event = {
	.notifier_call = ldmm_qxdm_timer_update_hndlr,
};

int ldmm_fault_notifr_init(void)
{
	return blocking_notifier_chain_register(&lassen_mtip_fault_notifr ,&ldmm_mtip_fault_event);

}
int ldmm_fault_notifr_exit(void)
{
	return blocking_notifier_chain_unregister(&lassen_mtip_fault_notifr ,&ldmm_mtip_fault_event);

}

int ldmm_qxdm_timer_update_notifr_init(void)
{
	int ret = blocking_notifier_chain_register(&lassen_qxdm_timer_update_notifr ,&ldmm_qxdm_timer_update_event);
	if(!ret)
	{
		//calling notifier to set initial timer value
   		blocking_notifier_call_chain(&lassen_qxdm_timer_update_notifr, qxdm_logging_timer_value, NULL);
	}
	return ret;  
}
int ldmm_qxdm_timer_update_notifr_exit(void)
{
	return blocking_notifier_chain_unregister(&lassen_qxdm_timer_update_notifr ,&ldmm_qxdm_timer_update_event);
}



