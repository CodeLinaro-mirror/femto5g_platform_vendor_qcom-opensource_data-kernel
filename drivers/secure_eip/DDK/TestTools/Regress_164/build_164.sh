#!/bin/bash
#
# Script for building binaries for a selected regression configuration
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

#-------------------------------------------------------------------------------
# check_file_exists
#
# Arguments:
#  1. path to file to check, may include whitespaces.
#
# This function checks if the given file exists. The function returns when
# the file exists. Otherwise a message is printed and the script is aborted
# with exit code 1.
#
check_file_exists()
{
  if [ ! -f "$1" ];
  then
      echo "Missing file $1";
      exit 1;
  fi
}


#-------------------------------------------------------------------------------
# check_build_log
#
# Arguments:
#  1. Base path
#  2. Relative path to build log file
#
# This function checks the logfile for errors and reports these.
# When there are no errors, a check is made for warnings.
#
check_build_log()
{
    grep -w '\*\*\*\|error' $1/$2 > /dev/null
    if [ $? -eq 0 ];
    then
        echo "Found ERRORS. Check $2 for details";
        return;
    fi

    grep -i "warning" $1/$2 > /dev/null
    if [ $? -eq 0 ];
    then
        echo "Found warnings. Examine $2 for details";
        return;
    fi
}


#-------------------------------------------------------------------------------
# check_copy
#
# Arguments:
#   1. path to file to check and copy
#   2. destination for copy
#
# This function checks if the given file exists. If it does not exist, a
# warning message is printed. Otherwise the file is copied to the destination
# folder.
#
check_copy()
{
    if [ ! -f "$1" ];
    then
        echo "Build FAILED! Missing file $1";
    fi

    cp $1 $2
}


#-------------------------------------------------------------------------------
# make_build_temp
#
# Arguments:
#   None
#
# This function sets up a copy of the "build" sub-directory based on the
# name in $BUILD_WORK. The new directory is made the current directory.
#
make_build_temp()
{
    rm -rf $BUILD_WORK
    mkdir $BUILD_WORK
    cd $BUILD_WORK
    cp -r ../build/* .
    cp -f $BUILD_CONFIG_DIR/cs_*.h .
}


#-------------------------------------------------------------------------------
# remove_build_temp
#
# Arguments:
#   None
#
# This function removes the temporary "build" sub-directory created by
# make_build_temp().
#
remove_build_temp()
{
    if [ "$COVER_DDK" != 'y' ];
    then
        cd ..;
        rm -rf $BUILD_WORK;
    fi
}


#-------------------------------------------------------------------------------
# print_status
#
# Arguments:
#   1. Product
#   2. Configuration
#   3. Architecture
#
# This function prints the build progress.
#
print_status()
{
    echo "Building $2 for $3: $1";
}


#-------------------------------------------------------------------------------
# clang_out_set
#
# Arguments:
#   1. Name
#   2. Configuration
#
# This function makes a name for the clang output directory
# in the CLANG_OUT_ARG variable.
#
clang_out_set()
{
    if [ "$CLANG_OUT" != "" ];
    then
        if [ -z "$2" ];
        then
            mkdir -p $CLANG_OUT/$1;
            CLANG_OUT_ARG="-o $CLANG_OUT/$1";
        else
            mkdir -p $CLANG_OUT/$2/$1;
            CLANG_OUT_ARG="-o $CLANG_OUT/$2/$1";
        fi
    fi
}


#-------------------------------------------------------------------------------
# build_one
#
# Arguments:
#   None
#
build_one()
{
    BUILD_CONFIG_DIR=$BUILD_BASE/Configs/$BUILD_CONFIG
    BUILD_WORK=build_temp_$BUILD_CONFIG
    BUILD_LOG=Logs/buildlog_${BUILD_CONFIG}_$ARCH
    BUILD_OUTPUT=$BUILD_BASE/Builds/$BUILD_CONFIG

    mkdir -p $BUILD_OUTPUT

    BUILD_MACSEC=
    if [ "$BUILD_CONFIG" = "C0" -o "$BUILD_CONFIG" = "C1" -o "$BUILD_CONFIG" = "C3" -o "$BUILD_CONFIG" = "C4" ];
    then
        BUILD_MACSEC=y;
    fi

    # build Packet I/O Driver
    print_status "Driver Packet I/O" $BUILD_CONFIG $ARCH
    cd $BUILD_BASE/../../Examples/Driver_PacketIO
    make_build_temp
    make clean > /dev/null
    clang_out_set driver_pktio $BUILD_CONFIG
    $CLANG_BIN $CLANG_OUT_ARG make -j $CLANG_ARG driver_pktio_u > $BUILD_BASE/${BUILD_LOG}_driver_pktio.log 2>&1
    check_build_log $BUILD_BASE ${BUILD_LOG}_driver_pktio.log
    check_copy libdriver_pktio_u.a $BUILD_OUTPUT
    remove_build_temp

    # build EIP-164 driver
    print_status "Driver EIP-164" $BUILD_CONFIG $ARCH
    cd $BUILD_BASE/../../Examples/Driver_EIP164
    make_build_temp
    make clean > /dev/null
    clang_out_set driver $BUILD_CONFIG
    $CLANG_BIN $CLANG_OUT_ARG make -j $CLANG_ARG > $BUILD_BASE/${BUILD_LOG}_driver.log 2>&1
    if [ "$BUILD_LKM" = "y" ];
    then
        check_copy driver_164_k.ko $BUILD_OUTPUT;
        check_copy Module.symvers $BUILD_OUTPUT;
    fi
    check_build_log $BUILD_BASE ${BUILD_LOG}_driver.log
    check_copy libdriver_164_u.a $BUILD_OUTPUT
    check_copy libdf.a $BUILD_OUTPUT
    remove_build_temp

    # build DemoApp_EIP164 C++ test
    if [ "$BUILD_MACSEC" = "y" ];
    then
        print_status "DemoApp EIP-164 cpp" $BUILD_CONFIG $ARCH;
        cd $BUILD_BASE/../../Examples/DemoApp_EIP164;
        make_build_temp;
        make clean > /dev/null;
        export LIB_DRIVER_PATH=$BUILD_OUTPUT
        export LIB_DRIVER_PKTIO_PATH=$BUILD_OUTPUT
        clang_out_set da_macsec $BUILD_CONFIG
        $CLANG_BIN $CLANG_OUT_ARG make da_macsec_test_cpp $CLANG_ARG > $BUILD_BASE/${BUILD_LOG}_da_macsec_cpp_test.log 2>&1;
        export LIB_DRIVER_PATH=
        check_copy da_macsec_test_cpp $BUILD_OUTPUT;
        check_build_log $BUILD_BASE ${BUILD_LOG}_da_macsec_cpp_test.log;
        remove_build_temp
    fi

    # build DemoApp_EIP164
    if [ "$BUILD_MACSEC" = "y" ];
    then
        print_status "DemoApp EIP-164" $BUILD_CONFIG $ARCH;
        cd $BUILD_BASE/../../Examples/DemoApp_EIP164;
        make_build_temp;
        make clean > /dev/null;
        export LIB_DRIVER_PATH=$BUILD_OUTPUT
        export LIB_DRIVER_PKTIO_PATH=$BUILD_OUTPUT
        clang_out_set da_macsec $BUILD_CONFIG
        if [ "$BUILD_LKM" = "y" ];
        then
            $CLANG_BIN $CLANG_OUT_ARG make $CLANG_ARG > $BUILD_BASE/${BUILD_LOG}_da_macsec.log 2>&1;
            check_copy da_macsec_k.ko $BUILD_OUTPUT;
        else
            $CLANG_BIN $CLANG_OUT_ARG make da_macsec_u_combined $CLANG_ARG > $BUILD_BASE/${BUILD_LOG}_da_macsec.log 2>&1;
        fi
        export LIB_DRIVER_PATH=
        check_copy da_macsec_u_combined $BUILD_OUTPUT;
        check_build_log $BUILD_BASE ${BUILD_LOG}_da_macsec.log;
        remove_build_temp
    fi

    # build TestTool_EIP164
    print_status "TestTool EIP-164" $BUILD_CONFIG $ARCH
    cd $BUILD_BASE/../../TestTools/TestTool_EIP164
    make_build_temp
    make clean > /dev/null
    export LIB_DRIVER_PATH=$BUILD_OUTPUT
    export LIB_DRIVER_PKTIO_PATH=$BUILD_OUTPUT
    clang_out_set test_macsec $BUILD_CONFIG
    if [ "$BUILD_LKM" = "y" ];
    then
        $CLANG_BIN $CLANG_OUT_ARG make $CLANG_ARG > $BUILD_BASE/${BUILD_LOG}_test_macsec.log 2>&1;
        check_copy test_macsec_k.ko $BUILD_OUTPUT;
    else
        $CLANG_BIN $CLANG_OUT_ARG make test_macsec_u_combined $CLANG_ARG > $BUILD_BASE/${BUILD_LOG}_test_macsec.log 2>&1;
    fi
    export LIB_DRIVER_PATH=
    check_build_log $BUILD_BASE ${BUILD_LOG}_test_macsec.log
    check_copy test_macsec_u_combined $BUILD_OUTPUT
    remove_build_temp

    rm -f $BUILD_OUTPUT/*.symvers $BUILD_OUTPUT/*.a
}


#-------------------------------------------------------------------------------
# build_all
#
# Arguments:
#   None
#
build_all()
{
    BUILD_OUTPUT=$BUILD_BASE/Builds
    mkdir -p $BUILD_OUTPUT

    # build Kernel Support Driver
    if [ "$BUILD_LKM" = "y" ];
    then
        echo "Building for $ARCH: Kernel Support Driver";
        cd ../../Examples/Driver_KernelSupport/build;
        make clean > /dev/null;
        clang_out_set driver_ks;
        $CLANG_BIN $CLANG_OUT_ARG make $CLANG_ARG > $BUILD_BASE/Logs/buildlog_${ARCH}_driver_ks.log 2>&1;
        check_build_log $BUILD_BASE Logs/buildlog_${ARCH}_driver_ks.log;
        check_copy driver_ks_k.ko $BUILD_OUTPUT;
        cd $BUILD_BASE
    fi

    # build MemXS utility
    echo "Building for $ARCH: MemXS"
    cd ../../Examples/Driver_EIP164/build
    make clean > /dev/null
    make > $BUILD_BASE/Logs/buildlog_${ARCH}_memxs.log 2>&1
    cd ../../../TestTools/MemXS/build
    make clean > /dev/null
    export LIB_DF_PATH=$BUILD_BASE/../../Examples/Driver_EIP164/build
    clang_out_set memxs
    $CLANG_BIN $CLANG_OUT_ARG make $CLANG_ARG >> $BUILD_BASE/Logs/buildlog_${ARCH}_memxs.log 2>&1
    export LIB_DF_PATH=
    check_build_log $BUILD_BASE Logs/buildlog_${ARCH}_memxs.log
    check_copy memxs $BUILD_OUTPUT
    cd $BUILD_BASE

    # build Packet I/O Driver
    if [ "$BUILD_LKM" = "y" ];
    then
        echo "Building for $ARCH: Driver Packet I/O";
        cd ../../Examples/Driver_PacketIO/build
        make clean > /dev/null
        make driver_pktio_k > /dev/null
        check_copy driver_pktio_k.ko $BUILD_OUTPUT
        cd $BUILD_BASE
    fi

    # build all configurations
    if [ "$BUILD_CONFIGS" = "" ];
    then
        BUILD_CONFIGS="C0 C1 C3 C4"
    fi

    for ConfigLp in $BUILD_CONFIGS;
    do
        # invoke self script
        ./build_164.sh $ConfigLp
    done

    # create the tarball
    BUILD_TARNAME=regress164_${ARCH}.tar.gz
    echo "Creating tarball $BUILD_TARNAME";
    rm -f $BUILD_TARNAME
    cd ../..
    rm -f $BUILD_TARNAME
    tar -zcf $BUILD_TARNAME TestTools/Regress_164/Builds/* TestTools/Regress_164/regress*.sh Examples/DemoApp_EIP164/scripts/* TestTools/TestTool_EIP164/scripts/*
    mv $BUILD_TARNAME TestTools/Regress_164
    cd TestTools/Regress_164
    ls -l $BUILD_TARNAME
}


# main script starts here

if [ -z $ARCH ];
then
    echo "Please set ARCH, KERNEL_DIR and optionally CROSS_COMPILE";
    exit 1;
fi

if [ "$#" -ne 1 ];
then
   echo "Please provide ALL or one configuration: C0, C1, C3 C4";
   exit 1;
fi

BUILD_BASE=`pwd`
BUILD_CONFIG=`echo $1 | tr [:lower:] [:upper:]`;

CLANG_BIN=
CLANG_ARG=
CLANG_OUT=
CLANG_OUT_ARG=

if [ "$HOST_HW_PLATFORM" == "FPGA" ];
then
    BUILD_LKM=y;
    BUILD_INTERRUPTS=y
else
    BUILD_LKM=;
    BUILD_INTERRUPTS=
fi

# set clang tool parameters if configured
if [ "$CLANG_DDK" = 'y' ];
then
    CLANG_BIN=scan-build;
    CLANG_ARG="CC=ccc-analyzer COMPILER=ccc-analyzer";

    if [ -d "$CLANG_OUTPUT_DIR" ];
    then
        CLANG_OUT=$CLANG_OUTPUT_DIR/Clang;
    else
        CLANG_OUT=$BUILD_BASE/Clang;
    fi

    # remove previous data if any
    if [ $BUILD_CONFIG == "ALL" ];
    then
        rm -rf $CLANG_OUT;
    fi
fi

mkdir -p Logs

if [ $BUILD_CONFIG == "ALL" ];
then
    # build all configurations
    build_all;
else
    # build one specific configuration
    build_one;
fi

# end of file
