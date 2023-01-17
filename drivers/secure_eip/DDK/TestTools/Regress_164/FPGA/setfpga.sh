#!/bin/bash

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

echo "Setting FPGA as a host platform"

rm -f ../../../Examples/Driver_EIP164/build/Makefile
cp ../../../Examples/Driver_EIP164/build/FPGA/Makefile.FPGA ../../../Examples/Driver_EIP164/build/Makefile
rm -f ../../../Examples/Driver_PacketIO/build/Makefile
cp ../../../Examples/Driver_PacketIO/build/FPGA/Makefile.FPGA ../../../Examples/Driver_PacketIO/build/Makefile
rm -f ../regress_164.sh
cp regress_164.sh ../
export HOST_HW_PLATFORM=FPGA
export USER_LFLAGS=
export BUILD_CONFIGS=
export VPROCHOST=
export VPROCPORT=
