/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022-2025 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include "ecpriss_core.h"
#include "ecpriss_netlink.h"
#include "ecpriss_log.h"
#include "ecpriss_qudp.h"

uint32_t global_pid = 0;
ecpriss_packet_s g_packet;

const char *ecpriss_msg_type_enum_to_str[] = {
	[ECPRISS_MESSAGE_REGISTER_CLIENT] = "Register Client ",
	[ECPRISS_MESSAGE_FLOW_CFG] = "Configure Flow ",
	[ECPRISS_MESSAGE_TRANSPORT_CFG] = "Configure Transport",
	[ECPRISS_MESSAGE_FLOW_RECFG] = "ReConfigure Flow",
	[ECPRISS_MESSAGE_TRANSPORT_RECFG] = "ReConfigure Transport",
	[ECPRISS_MESSAGE_FLOW_DECFG] = "DeConfigure Flow",
	[ECPRISS_MESSAGE_TRANSPORT_DECFG] = "Deconfigure Transport",
	[ECPRISS_MESSAGE_RESPONSE] = "Responce Message",
	[ECPRISS_MESSAGE_EVENT] = "Event Message",
	[ECPRISS_MESSAGE_TEST] = "Test Message",
	[ECPRISS_MESSAGE_STAT] = "Stat Message",
	[ECPRISS_MESSAGE_DEREGISTER_CLIENT] = "Deregister Client",
	[ECPRISS_MESSAGE_FLOW_TRANSP_DECFG] = "DeConfigure Flow and Transport",
	[ECPRISS_MESSAGE_TRANSPORT_EGRESS_L2_TABLE_RECFG] = "ReConfigure L2 Tables",
	[ECPRISS_MESSAGE_TRANSPORT_EGRESS_L3_TABLE_RECFG] = "ReConfigure L3 Tables",
	[ECPRISS_MESSAGE_TRANSPORT_EGRESS_L2_L3_TABLE_RECFG] = "ReConfigure L2 and L3 Tables",
	[ECPRISS_MESSAGE_TRANSPORT_INGESS_TABLE_CFG] = "ReConfigure Ingress Filter table",
	[ECPRISS_MESSAGE_TRANSPORT_INGESS_TABLE_DECFG] = "DeConfigure Ingress Filter Table",
	[ECPRISS_MESSAGE_LTE_MAC_CFG] = "Configure LTE MAC",
	[ECPRISS_MESSAGE_LOGGING_CFG] = "Configure Logging",

};

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
int32_t ecpriss_netlink_process_packet(ecpriss_packet_s *packet)
{
	uint32_t num_of_flows = 0;
	int32_t ret = 0;
	ecpriss_packet_payload_s *curr_payload = NULL;

	if(!packet)
		return -1;
	ECPRILOGINFO("Got netlink request to performe %s\n",ecpriss_msg_type_enum_to_str[packet->header.message_id]);

	for(num_of_flows = 0; num_of_flows < packet->header.num_flows; num_of_flows++){
		if(num_of_flows >= ECPRISS_MAX_KERNEL_NETLINK_FLOW){
			ECPRILOGERR("Invalid num of flows inside Kenrel netlink msg %u\n",num_of_flows);
			return -1;
		}
		curr_payload  = &(packet->payload[num_of_flows]);
		ecpriss_debug_flow_info(curr_payload, packet->header.message_id);
		if(packet) {
			switch(packet->header.message_id){
				case ECPRISS_MESSAGE_FLOW_CFG:
					ret = ecpriss_process_packet(curr_payload);
					break;
				case ECPRISS_MESSAGE_TRANSPORT_CFG:
					ret = ecpriss_process_packet(curr_payload);
					break;
				case ECPRISS_MESSAGE_FLOW_RECFG:
					ret = ecpriss_process_packet(curr_payload);
					break;
				case ECPRISS_MESSAGE_TRANSPORT_RECFG:
					ret = ecpriss_process_packet(curr_payload);
					break;
				case ECPRISS_MESSAGE_FLOW_DECFG:
					ret = ecpriss_process_packet_decfg(curr_payload,ECPRISS_MESSAGE_FLOW_DECFG);
					break;
				case ECPRISS_MESSAGE_TRANSPORT_DECFG:
					ret  = ecpriss_process_packet_decfg(curr_payload,ECPRISS_MESSAGE_TRANSPORT_DECFG);
					break;
				case ECPRISS_MESSAGE_RESPONSE:
					ret  = ecpriss_process_packet(curr_payload);
					break;
				case ECPRISS_MESSAGE_EVENT:
					ret = ecpriss_process_packet(curr_payload);
					break;
				case ECPRISS_MESSAGE_TEST:
					ret = ecpriss_process_packet(curr_payload);
					break;
				case ECPRISS_MESSAGE_FLOW_TRANSP_DECFG:
					ret = ecpriss_process_packet_decfg(curr_payload,ECPRISS_MESSAGE_FLOW_TRANSP_DECFG);
					break;
				case ECPRISS_MESSAGE_TRANSPORT_EGRESS_L2_TABLE_RECFG:
					ret = ecpriss_qudp_egress_l2_table_reconfig(curr_payload);
					break;
				case ECPRISS_MESSAGE_TRANSPORT_EGRESS_L3_TABLE_RECFG:
					ret = ecpriss_qudp_egress_l3_table_reconfig(curr_payload);
					break;
				case ECPRISS_MESSAGE_TRANSPORT_EGRESS_L2_L3_TABLE_RECFG:
					ret = ecpriss_qudp_egress_l2_l3_table_reconfig(curr_payload);
					break;
				case ECPRISS_MESSAGE_TRANSPORT_INGESS_TABLE_CFG:
					ret = ecpriss_qudp_ingress_table_config(curr_payload);
					break;
				case ECPRISS_MESSAGE_TRANSPORT_INGESS_TABLE_DECFG:
					ret = ecpriss_qudp_ingress_table_deconfig(curr_payload);
					break;
				case ECPRISS_MESSAGE_LTE_MAC_CFG:
					ret = ecpriss_qudp_set_lte_mac_filter(curr_payload);
					break;
				case ECPRISS_MESSAGE_LOGGING_CFG:
					ret = ecpriss_configure_logging(curr_payload);
					break;
				default:
					ECPRILOGERR("Invalid message type: %s \n",packet->header.message_id);
					break;
			}
		}
	}
	ECPRILOGINFO("completed netlink request to performe %s\n",ecpriss_msg_type_enum_to_str[packet->header.message_id]);
	return ret;
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
void ecpriss_stats_rcv_netlink_message(struct sk_buff *skb)
{
	int32_t res = 0;
	datacsm_ecpriss_stats_info_s *fh_stats = NULL;
	struct nlmsghdr *nlh = NULL;
	struct sk_buff *skb_out = NULL;
	nlh = (struct nlmsghdr *) skb->data;

	ECPRILOGDBG("DEBUG:Received message: %s\n",(char *) nlmsg_data(nlh));
	fh_stats = &ecpriss_pdata_v2->fh_stats_usr;

	global_pid = nlh->nlmsg_pid;
	ECPRILOGDBG(KERN_INFO "DEBUG:Global PID: %d\n", global_pid);

	skb_out = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if(!skb_out){
		ECPRILOGERR("Failed to allocate memory\n");
		return;
	}

	nlh = nlmsg_put(skb_out, nlh->nlmsg_pid, nlh->nlmsg_seq, NLMSG_DONE, sizeof(datacsm_ecpriss_stats_info_s), 0);
	if(NULL == nlh)
		return;

	NETLINK_CB(skb_out).dst_group = 0;
	nlh->nlmsg_len = sizeof(datacsm_ecpriss_stats_info_s);
	memcpy(nlmsg_data(nlh), fh_stats, sizeof(datacsm_ecpriss_stats_info_s));

	res = nlmsg_unicast(ecpriss_pdata_v2->stats_netlink_socket,
			skb_out,
			global_pid);
	if(res<0)
		ECPRILOGERR("Failed to send stats over netlink\n");
	return;
}
void ecpriss_netlink_receive_netlink_message(struct sk_buff *skb)
{
	int32_t res = 0;
	ecpriss_packet_s *packet = &g_packet;
	struct nlmsghdr *nlh;
	nlh = (struct nlmsghdr *) skb->data;
	ECPRILOGDBG("DEBUG:Received message: %p\n",
			(ecpriss_packet_s *) nlmsg_data(nlh));

	memset(packet , 0, sizeof(ecpriss_packet_s));
	memcpy(packet,nlmsg_data(nlh),sizeof(ecpriss_packet_s));
	ecpriss_netlink_debug_print_packet(packet);
	res = ecpriss_netlink_process_packet(packet);
	global_pid = nlh->nlmsg_pid;
	ECPRILOGDBG(KERN_INFO "DEBUG:Global PID: %d\n", global_pid);
	netlink_ack(skb, nlmsg_hdr(skb), res, NULL);
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
int ecpriss_netlink_stats_socket_create(void)
{
	struct netlink_kernel_cfg config = {
		.input = ecpriss_stats_rcv_netlink_message,
	};
	ecpriss_pdata_v2->stats_netlink_socket =
		netlink_kernel_create(&init_net, ECPRISS_STATS_UPDATE, &config);
	if(ecpriss_pdata_v2->stats_netlink_socket == NULL){
		return -1;
	}
	return 0;

}

