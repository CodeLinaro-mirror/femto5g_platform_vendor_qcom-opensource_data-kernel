#!/vendor/bin/sh
#Copyright (c) 2019, 2021 The Linux Foundation. All rights reserved.
#
#This program is free software; you can redistribute it and/or modify
#it under the terms of the GNU General Public License version 2 and
#only version 2 as published by the Free Software Foundation.
#
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#
irq_num=`cat /proc/interrupts | grep -i DWC_ETH_QOS| grep -i gic | awk {'print $1'} | awk -F :  {'print $1'}`;
echo irqnum=$irq_num;
# Here 08 is forcing ISR to CPU 3
echo 08 > /proc/irq/$irq_num/smp_affinity;
# Here 34 forcing RX CPU as 2,4,5
echo 34 > /sys/class/net/eth0/queues/rx-0/rps_cpus;
