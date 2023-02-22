/* SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include "ecpriss_core.h"
#include "ecpriss_netlink.h"

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
		printk(KERN_ERR "Failed to allocate a new skb\n");
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
	printk(KERN_INFO "DEBUG:Unicast result = %d\n",result);
#endif
	return;
}

//Wrapper for  ecpriss_process_packet() in ecpriss_core.c
void ecpriss_netlink_process_packet(ecpriss_packet_s *packet)
{
	if(packet) {
		ecpriss_process_packet(&packet->payload);
	}
	return;
}


void ecpriss_netlink_debug_print_packet(ecpriss_packet_s *packet)
{

#if 0
	printk(KERN_INFO "DEBUG:packet->header.version  = %d\n",
			packet->header.version);
	printk(KERN_INFO "DEBUG:packet->header.client_id  = %d\n",
			packet->header.client_id);
	printk(KERN_INFO "DEBUG:packet->header.message_id  = %d\n",
			packet->header.message_id);
	printk(KERN_INFO "DEBUG:packet->header.num_flows  = %d\n",
			packet->header.num_flows);
	printk(KERN_INFO "DEBUG:packet->header.reserved  = %d\n",
			packet->header.reserved);
	printk(KERN_INFO "DEBUG:packet->header.seq_id  = %d\n",
			packet->header.seq_id);
	printk(KERN_INFO "DEBUG:packet->header.len = %d\n",
			packet->header.len);
	//printk(KERN_INFO "DEBUG:packet->payload.len = %d\n",packet->payload.len);
	//printk(KERN_INFO "DEBUG:packet->payload.buffer = %s",packet->payload.buffer);
#endif
	pr_err("DEBUG:packet->header.version  = %d\n",
			packet->header.version);
	pr_err("DEBUG:packet->header.client_id  = %d\n",
			packet->header.client_id);
	pr_err("DEBUG:packet->header.message_id  = %d\n",
			packet->header.message_id);
	pr_err("DEBUG:packet->header.num_flows  = %d\n",
			packet->header.num_flows);
	pr_err("DEBUG:packet->header.reserved  = %d\n",
			packet->header.reserved);
	pr_err("DEBUG:packet->header.seq_id  = %d\n",
			packet->header.seq_id);
	pr_err("DEBUG:packet->header.len = %d\n",
			packet->header.len);
	return;
}

void ecpriss_netlink_receive_netlink_message(struct sk_buff *skb)
{
	ecpriss_packet_s packet;
	struct nlmsghdr *nlh;
	nlh = (struct nlmsghdr *) skb->data;
	pr_err("DEBUG:Received message: %p\n",
			(ecpriss_packet_s *) nlmsg_data(nlh));

	memset(&packet , 0, sizeof(ecpriss_packet_s));
	memcpy(&packet,nlmsg_data(nlh),sizeof(ecpriss_packet_s));
	ecpriss_netlink_debug_print_packet(&packet);
	ecpriss_netlink_process_packet(&packet);
	global_pid = nlh->nlmsg_pid;
	//schedule_flag = 1;
	printk(KERN_INFO "DEBUG:Global PID: %d\n", global_pid);
	//send_response( ECPRISS_KERNEL, ECPRISS_MESSAGE_RESPONSE,
	//"KERNEL:Response message from kernel\n");=
	return;
}

int ecpriss_netlink_socket_create()
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
