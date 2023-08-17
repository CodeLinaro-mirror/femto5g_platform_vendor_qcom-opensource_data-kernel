/*
 * SPDX-License-Identifier: GPL-2.0-only
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include <linux/module.h>
#include <net/genetlink.h>
#include "ldmm_shrd_genntlk.h"
#include "ldmm_ipc_log.h"

#define MSG_MAX_LEN 1024
#define INIT_MSG 1234

//#define IS_MULTICAST_EN

static struct genl_family genl_fam;
static uint32_t dst_portid;

/* Handler for LDMM_CMD_FULT_MGMT_RCV messages received */
static int fult_mgmt_rcv_doit(struct sk_buff *skb, struct genl_info *info)
{
	int ret = 0;
	uint32_t *str = NULL;

	if (info->attrs[LDMM_A_MSG]) {
		str = nla_data(info->attrs[LDMM_A_MSG]);

		LDMM_LOG_INFO("message received: %u\n", str);
	} else {
		LDMM_LOG_INFO("empty message received\n");
	}
	dst_portid = info->snd_portid;

	/*
	 * Dummy MSG to check connectivity
	 */
	fult_mgmt_snd(INIT_MSG, UNICAST_MSG);

	return ret;
}


/* Attribute validation policy for our fult_mgmt_rcv command */
static struct nla_policy fult_mgmt_rcv_pol[LDMM_A_MAX + 1] = {
	[LDMM_A_MSG] = { .type = NLA_U32 },
};

/* Operations for our Generic Netlink family */
static struct genl_ops genl_ops[] = {
	{
		.cmd	= LDMM_CMD_FULT_MGMT_RCV,
		.policy = fult_mgmt_rcv_pol,
		.doit	= fult_mgmt_rcv_doit,
	 },
};

/* Multicast groups for our family */
static const struct genl_multicast_group genl_mcgrps[] = {
	{ .name = LDMM_MC_GRP_NAME },
};

/* Generic Netlink family */
static struct genl_family genl_fam = {
	.name	  = LDMM_GENL_NAME,
	.version  = LDMM_GENL_VERSION,
	.maxattr  = LDMM_A_MAX,
	.ops	  = genl_ops,
	.n_ops	  = ARRAY_SIZE(genl_ops),
	.mcgrps	  = genl_mcgrps,
	.n_mcgrps = ARRAY_SIZE(genl_mcgrps),
};

/*
 * mode =0 unicast
 * mode =1 multicast
 */
int fult_mgmt_snd(uint32_t buf, int mode)
{
	int ret = 0;
	void *hdr = NULL;

	/* Allocate message buffer */
	struct sk_buff *skb = genlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);

	if ((!skb)) {
		LDMM_LOG_ERR("failed to allocate memory for genl message\n");
		return -ENOMEM;
	}

	/* Put the Generic Netlink header */
	hdr = genlmsg_put(skb, 0, 0, &genl_fam, 0, LDMM_CMD_FULT_MGMT_RCV);
	if ((!hdr)) {
		LDMM_LOG_ERR("failed to allocate memory for genl header\n");
		nlmsg_free(skb);
		return -ENOMEM;
	}

	if ((ret = nla_put_u32(skb, LDMM_A_MSG, buf))) {
		LDMM_LOG_ERR("unable to create netlink msg Err: %d\n",ret);
		genlmsg_cancel(skb, hdr);
		nlmsg_free(skb);
		return ret;
	}

	/* Finalize the message */
	genlmsg_end(skb, hdr);

	LDMM_LOG_INFO("%s: Buf = 0x%x\n",__func__,buf);

#ifdef IS_MULTICAST_EN
	if(mode == MULTICAST_MSG){
		ret = genlmsg_multicast(&genl_fam, skb, 0, 0, GFP_KERNEL);
		if (ret == -ESRCH) {
			LDMM_LOG_ERR("multicast message sent, but nobody was listening...\n");
		} else if (ret) {
			LDMM_LOG_ERR("failed to send multicast genl message\n");
		} else {
			LDMM_LOG_INFO("multicast message sent\n");
		}
	}else if(mode == UNICAST_MSG){
		ret = genlmsg_unicast(&init_net, skb, dst_portid);
		if(ret != 0){
			LDMM_LOG_ERR("Unicast message sent failed: %d\n", ret );
		}
	}
#else
	ret = genlmsg_unicast(&init_net, skb, dst_portid);
	if(ret != 0){
		LDMM_LOG_ERR("Unicast message sent failed Err: %d\n", ret );
	}
#endif

	return ret;
}

int  init_genlldmm(void)
{
	int ret = 0;

	LDMM_LOG_INFO("init start\n");

	ret = genl_register_family(&genl_fam);
	if((ret)){
		LDMM_LOG_ERR("failed to register generic netlink family Err: %d\n",ret);
	}

	LDMM_LOG_INFO("init end\n");

	return ret;
}

void exit_genlldmm(void)
{
	int ret = 0;

	if ((ret = genl_unregister_family(&genl_fam))) {
		LDMM_LOG_ERR("failed to unregister generic netlink family Err: %d\n",ret);
	}

	LDMM_LOG_INFO("exit\n");
}
