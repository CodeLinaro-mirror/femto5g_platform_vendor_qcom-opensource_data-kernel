/* Copyright (c) 2020, The Linux Foundation. All rights reserved.

* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 and
* only version 2 as published by the Free Software Foundation.

* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*/

/*
 * Ethernet adaptation module to interface with IPCRTR.
 * Owner - Abhishek B Chauhan - 8/18/2020
*/

#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/socket.h>
#include<linux/in.h>
#include<linux/in6.h>
#include<linux/net.h>
#include<linux/tcp.h>
#include<linux/slab.h>
#include<linux/inet.h>
#include<linux/syscalls.h>
#include<linux/netdev_features.h>
#include<linux/netdevice.h>
#include<linux/types.h>
#include<linux/platform_device.h>
#include<linux/phy.h>
#include<linux/debugfs.h>
#include <linux/pm_wakeup.h>


#include<net/protocol.h>
#include<net/addrconf.h>
#include<net/sock.h>

#include<net/inet_common.h>
#include<net/tcp_states.h>
#include<net/tcp.h>

#include<asm/uaccess.h>

#ifdef CONFIG_MSM_BOOT_TIME_MARKER
#include <soc/qcom/boot_stats.h>
#endif

#include <linux/cdev.h>

#define DRV_NAME "eth-adaption-layer"
#define MAX_SIZE 8192

#define QRTR_DEINIT           0x0
#define QRTR_INIT             0x1
#define QRTR_INPROGRESS       0x2
#define QRTR_CONNFAILED       0x3

#define ETHADPTDBG(fmt, args...) \
do {\
	pr_debug(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ## args);\
} while (0)
#define ETHADPTERR(fmt, args...) \
do {\
	pr_err(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ## args);\
} while (0)
#define ETHADPTINFO(fmt, args...) \
do {\
	pr_info(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ## args);\
} while (0)

enum eam_power_management_state
{
	EAM_POWER_STATE_SUSPENDED,
	EAM_POWER_STATE_RUNNING,
	EAM_POWER_STATE_SUSPENDING,
	EAM_POWER_STATE_RESUMING,
};
/* power management state*/
extern enum eam_power_management_state power_state;
/* Power state lock */
extern struct mutex power_state_lock;

/* Variable to indicate if peer has toggle wake up GPIO*/
extern bool peer_gpio_toggled;
/* Power state lock */
extern struct mutex gpio_toggle_lock;

extern atomic_t acquire_wakelock;
extern struct wakeup_source *eth_ws;

/**
* eth_adaption_send() - Function to send QMI packet from IPCRTR over TCP socket.
*
* @skb: buffer holding QMI message.
*
* Use this API from IPCRTR ethernet transport layer.
*
* Return: 0 on success, non-zero otherwise
*/
int eth_adaption_send(struct sk_buff *skb);

/**
* eth_adaption_notifier_soft_reset() - resets Ethernet adaptation module.
* Return: void
*/
void eth_adaption_notifier_soft_reset(struct kthread_work *work);

/**
* eth_adaption_notifier_soft_set() - sets Ethernet adaptation module.
* Return: void
*/
void eth_adaption_notifier_soft_set(struct kthread_work *work);

/**
* eth_adaption_handle_suspend() - handler for suspend case
* scenario Return:int
*/
int eth_adaption_handle_suspend(void);

/**
* eth_adaption_handle_resume() - handler for resume case
* scenario Return:int
*/
int eth_adaption_handle_resume(void);

/**
* eth_adaption_wake_up() - Function to wake up waiting thread.
* Return: 0 on success, non-zero otherwise
*/
int eth_adaption_wake_up(void);
