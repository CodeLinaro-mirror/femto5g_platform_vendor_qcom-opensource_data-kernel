//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include "mtip_notifr.h"
#include "mtip_logging.h"

#define STATUS_SET 1
#define STATUS_CLEAR 0
#define MAX_NOTIF_INTERFACE 12

struct blocking_notifier_head lassen_mtip_fault_notifr;

EXPORT_SYMBOL_GPL(lassen_mtip_fault_notifr);

void mtip_snd_event_notification(uint32_t interface, uint32_t event)
{
	static uint32_t ber_status[MAX_NOTIF_INTERFACE];
	static uint32_t pcs_link_status[MAX_NOTIF_INTERFACE];
	static uint32_t rx_los_status[MAX_NOTIF_INTERFACE];
	static uint32_t local_plugout_status[MAX_NOTIF_INTERFACE];
	event_info_struct event_info;

	if(interface < 0 || interface > MAX_NOTIF_INTERFACE -1 ){
		CSMLOGERR("Invalid interface id %u\n",interface);
		return;
	}

	switch(event){

		case HIGH_BER_SET:
			/*
			 * check if it is already set
			 */
			if(ber_status[interface] == STATUS_SET){
				return;
			}
			ber_status[interface] = STATUS_SET;
			CSMLOGDBG("Interface[%u] Hig Ber Set\n",interface);
			break;

		case HIGH_BER_CLR:
			/*
			 * check if it is already clear
			 */
			if(ber_status[interface] == STATUS_CLEAR){
				return;
			}
			ber_status[interface] = STATUS_CLEAR;
			CSMLOGDBG("Interface[%u] Hig Ber clear\n",interface);
			break;

		case PCS_IF_UP:
			/*
			 * check if it is already set
			 */
			if(pcs_link_status[interface] == STATUS_SET){
				return;
			}
			pcs_link_status[interface] = STATUS_SET;
			CSMLOGDBG("Interface[%u] PCS_IF_UP\n",interface);
			break;

		case PCS_IF_DOWN:
			/*
			 * check if it is already set
			 */
			if(pcs_link_status[interface] == STATUS_CLEAR){
				return;
			}
			pcs_link_status[interface] = STATUS_CLEAR;
			CSMLOGDBG("Interface[%u] PCS_IF_DOWN\n",interface);
			break;

		case IF_UP:
			CSMLOGDBG("Interface[%u] IF_UP\n",interface);
			break;

		case IF_DOWN:
			CSMLOGDBG("Interface[%u] IF_DOWN\n",interface);
			break;

		case RX_LOS_SET:
			/*
			 * check if it is already set
			 */
			if(rx_los_status[interface] == STATUS_SET){
				return;
			}
			rx_los_status[interface] = STATUS_SET;
			CSMLOGDBG("Interface[%u] RX LOS Set\n",interface);
			break;

		case RX_LOS_CLR:
			/*
			 * check if it is already clear
			 */
			if(rx_los_status[interface] == STATUS_CLEAR){
				return;
			}
			rx_los_status[interface] = STATUS_CLEAR;
			CSMLOGDBG("Interface[%u] RX LOS clear\n",interface);
			break;

		case LOCAL_PLUG_OUT_SET:
			/*
			 * check if it is already set
			 */
			if(local_plugout_status[interface] == STATUS_SET){
				return;
			}
			local_plugout_status[interface] = STATUS_SET;
			CSMLOGDBG("Interface[%u] local plugout Set\n",interface);
			break;

		case LOCAL_PLUG_OUT_CLR:
			/*
			 * check if it is already clear
			 */
			if(local_plugout_status[interface] == STATUS_CLEAR){
				return;
			}
			local_plugout_status[interface] = STATUS_CLEAR;
			CSMLOGDBG("Interface[%u] local plugout clear\n",interface);
			break;

		default:
			CSMLOGDBG("Invalid event for notifier \n");
			return;

	}
	mtip_lookup_port_type_by_link_index(interface, &event_info.port_type);
	event_info.interface = interface;
	blocking_notifier_call_chain(&lassen_mtip_fault_notifr, event, (void*)(&event_info));
	return ;
}

int mtip_fault_notifr_init(void)
{
	CSMLOGINFO("FAULT: mtip_fault_notifr_init start\n");
	BLOCKING_INIT_NOTIFIER_HEAD(&lassen_mtip_fault_notifr);
	CSMLOGINFO("FAULT: mtip_fault_notifr_init end\n");
	return 0;
}
