#!/bin/bash
# load.sh
#
# This script loads the Kernel Support Driver and creates the communication
# point for the application (using the proxy).
#

#############################################################################
# Copyright (c) 2015-2021 by Rambus, Inc. and/or its subsidiaries.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
##############################################################################


dmesg -c > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo "Not enough rights. Try sudo."
    exit;
fi

# check if already loaded (0) or not yet loaded (1)
is_loaded=$(lsmod | grep driver_ks_k > /dev/null; echo $?)
if [ $is_loaded -eq 0 ]; then
    echo "Already loaded; use unload.sh first";
    exit;
fi

# move to the script base directory
MY_DIR=$(dirname $0);
cd $MY_DIR

# check that the driver was built successfully
build=../build/driver_ks_k.ko

if [ ! -f "$build" ]; then
    echo "Fatal: cannot find driver";
    exit;
fi

# load the driver
insmod $build

# grab the major number for the character device
major_nr=`awk "\\$2==\"driver_ks_c\" {print \\$1}" /proc/devices`
#echo "Major nr: $major_nr";

# make the communication pointer
mknod /dev/driver_ks_c c ${major_nr} 0

# make accessible to application
chmod 666 /dev/driver_ks_c

# print and clear start-up messages
dmesg -c

# end of file load.sh
