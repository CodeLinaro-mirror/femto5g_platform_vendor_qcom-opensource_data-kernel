/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2024 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include "ecpriss_core.h"
#include "ecpriss_netlink.h"
#include "ecpriss_log.h"
#include "ecpriss_qudp.h"

uint32_t global_pid = 0;

void ecpriss_netlink_send_netlink_message(int client_id,
		int message_id,
		char* buffer)
{
#if 0
	struct nlmsghdr *nlh;
	memset(&nlh,0,sizeof(nlh));
	ecpriss_packet_s packet;

	size_t message_size = strlen(buffer) + 1;
	packet.header.message_id = message_id;
	packet.header.client_id = client_id;
	packet.header.len = sizeof(packet.payload.buffer) + 8;
	packet.header.num_flows = 0;
	packet.header.reserved = 0;
	packet.header.seq_id = count++;
	packet.header.version = 0;
	strlcpy(packet.payload.buffer, buffer,message_size);
	struct sk_buff *skb_out = nlmsg_new(sizeof(packet.payload.buffer), GFP_KERNEL);
	if (!skb_out)
	{
		ECPRILOGERR(KERN_ERR "Failed to allocate a new skb\n");
		return;
	}

	memcpy(skb_out->data,packet.payload.flow_cfg,sizeof(packet.payload.flow_cfg));
	nlh = nlmsg_put(skb_out, 0, 0, NLMSG_DONE, sizeof(packet.payload.flow_cfg), 0);
	nlh->nlmsg_len = 1024; //Needs to be modified
	memcpy(nlmsg_data(nlh),&packet,sizeof(ecpriss_packet_s));
	NETLINK_CB(skb_out).dst_group = 0;
	int result = 0;
	printPacket(&packet);
	result = nlmsg_unicast(socket, skb_out, global_pid);
	ECPRILOGDBG(KERN_INFO "DEBUG:Unicast result = %d\n",result);
#endif
	return;
}

//Wrapper for  ecpriss_process_packet() in ecpriss_core.c
void ecpriss_netlink_process_packet(ecpriss_packet_s *packet)
{
	if(packet) {
	
	ecpriss_debug_flow_info(&packet->payload, packet->header.message_id);
		
		switch(packet->header.message_id){
			case ECPRISS_MESSAGE_FLOW_CFG:
				ecpriss_process_packet(&packet->payload);
				break;
			case ECPRISS_MESSAGE_TRANSPORT_CFG:
				ecpriss_process_packet(&packet->payload);
				break;
			case ECPRISS_MESSAGE_FLOW_RECFG:
				ecpriss_process_packet(&packet->payload);
				break;
			case ECPRISS_MESSAGE_TRANSPORT_RECFG:
				ecpriss_process_packet(&packet->payload);
				break;
			case ECPRISS_MESSAGE_FLOW_DECFG:
				ecpriss_process_packet_decfg(&packet->payload,ECPRISS_MESSAGE_FLOW_DECFG);
				break;
			case ECPRISS_MESSAGE_TRANSPORT_DECFG:
				ecpriss_process_packet_decfg(&packet->payload,ECPRISS_MESSAGE_TRANSPORT_DECFG);
				break;
			case ECPRISS_MESSAGE_RESPONSE:
				ecpriss_process_packet(&packet->payload);
				break;
			case ECPRISS_MESSAGE_EVENT:
				ecpriss_process_packet(&packet->payload);
				break;
			case ECPRISS_MESSAGE_TEST:
				ecpriss_process_packet(&packet->payload);
				break;
			case ECPRISS_MESSAGE_FLOW_TRANSP_DECFG:
				ecpriss_process_packet_decfg(&packet->payload,ECPRISS_MESSAGE_FLOW_TRANSP_DECFG);
				break;
			case ECPRISS_MESSAGE_TRANSPORT_EGRESS_L2_TABLE_RECFG:
				ecpriss_qudp_egress_l2_table_reconfig(&packet->payload);
				break;
			case ECPRISS_MESSAGE_TRANSPORT_EGRESS_L3_TABLE_RECFG:
				ecpriss_qudp_egress_l3_table_reconfig(&packet->payload);
				break;
			case ECPRISS_MESSAGE_TRANSPORT_EGRESS_L2_L3_TABLE_RECFG:
				ecpriss_qudp_egress_l2_l3_table_reconfig(&packet->payload);
				break;
			case ECPRISS_MESSAGE_TRANSPORT_INGESS_TABLE_CFG:
				ecpriss_qudp_ingress_table_config(&packet->payload);
				break;
			case ECPRISS_MESSAGE_TRANSPORT_INGESS_TABLE_DECFG:
				ecpriss_qudp_ingress_table_deconfig(&packet->payload);
				break;
			case ECPRISS_MESSAGE_LTE_MAC_CFG:
				ecpriss_qudp_set_lte_mac_filter(&packet->payload);
				break;
			default:
				ECPRILOGERR("Invalid message type: %s \n",packet->header.message_id);
				break;
		}
	}
}


void ecpriss_netlink_debug_print_packet(ecpriss_packet_s *packet)
{

#if 0
	ECPRILOGDBG(KERN_INFO "DEBUG:packet->header.version  = %d\n",
			packet->header.version);
	ECPRILOGDBG(KERN_INFO "DEBUG:packet->header.client_id  = %d\n",
			packet->header.client_id);
	ECPRILOGDBG(KERN_INFO "DEBUG:packet->header.message_id  = %d\n",
			packet->header.message_id);
	ECPRILOGDBG(KERN_INFO "DEBUG:packet->header.num_flows  = %d\n",
			packet->header.num_flows);
	ECPRILOGDBG(KERN_INFO "DEBUG:packet->header.reserved  = %d\n",
			packet->header.reserved);
	ECPRILOGDBG(KERN_INFO "DEBUG:packet->header.seq_id  = %d\n",
			packet->header.seq_id);
	ECPRILOGDBG(KERN_INFO "DEBUG:packet->header.len = %d\n",
			packet->header.len);
	//ECPRILOGDBG(KERN_INFO "DEBUG:packet->payload.len = %d\n",packet->payload.len);
	//ECPRILOGDBG(KERN_INFO "DEBUG:packet->payload.buffer = %s",packet->payload.buffer);
#endif
	ECPRILOGDBG("DEBUG:packet->header.version  = %d\n",
			packet->header.version);
	ECPRILOGDBG("DEBUG:packet->header.client_id  = %d\n",
			packet->header.client_id);
	ECPRILOGDBG("DEBUG:packet->header.message_id  = %d\n",
			packet->header.message_id);
	ECPRILOGDBG("DEBUG:packet->header.num_flows  = %d\n",
			packet->header.num_flows);
	ECPRILOGDBG("DEBUG:packet->header.reserved  = %d\n",
			packet->header.reserved);
	ECPRILOGDBG("DEBUG:packet->header.seq_id  = %d\n",
			packet->header.seq_id);
	ECPRILOGDBG("DEBUG:packet->header.len = %d\n",
			packet->header.len);
	return;
}

void ecpriss_netlink_receive_netlink_message(struct sk_buff *skb)
{
	ecpriss_packet_s packet;
	struct nlmsghdr *nlh;
	nlh = (struct nlmsghdr *) skb->data;
	ECPRILOGDBG("DEBUG:Received message: %p\n",
			(ecpriss_packet_s *) nlmsg_data(nlh));

	memset(&packet , 0, sizeof(ecpriss_packet_s));
	memcpy(&packet,nlmsg_data(nlh),sizeof(ecpriss_packet_s));
	ecpriss_netlink_debug_print_packet(&packet);
	ecpriss_netlink_process_packet(&packet);
	global_pid = nlh->nlmsg_pid;
	//schedule_flag = 1;
	ECPRILOGDBG(KERN_INFO "DEBUG:Global PID: %d\n", global_pid);
	//send_response( ECPRISS_KERNEL, ECPRISS_MESSAGE_RESPONSE,
	//"KERNEL:Response message from kernel\n");=
	return;
}

int ecpriss_netlink_socket_create(void)
{
	struct netlink_kernel_cfg config = {
		.input = ecpriss_netlink_receive_netlink_message,
	};
	ecpriss_pdata->netlink_socket =
		netlink_kernel_create(&init_net, NETLINK_ECPRI, &config);
	if (ecpriss_pdata->netlink_socket == NULL) {
		return -1;
	}
	return 0;
}
int ecpriss_netlink_socket_create_v2(void)
{
	struct netlink_kernel_cfg config = {
		.input = ecpriss_netlink_receive_netlink_message,
	};
	ecpriss_pdata_v2->netlink_socket =
		netlink_kernel_create(&init_net, NETLINK_ECPRI, &config);
	if (ecpriss_pdata_v2->netlink_socket == NULL) {
		return -1;
	}
	return 0;
}

