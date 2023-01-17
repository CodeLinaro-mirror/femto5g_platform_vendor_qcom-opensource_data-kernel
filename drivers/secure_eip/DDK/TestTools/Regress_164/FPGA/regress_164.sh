#!/bin/bash
#
# This script executes a set of test vectors on a pre-defined configuration.
# The output is captured in a logfile and stored in the Logs directory.
#
# This script captures the results and stores it in a logfile.
#
# Command line argument:
# 1. Configuration to run (for example C1)
# 2. Number of iterations (optional, default = 1)
#    or "-i" for interactive runs
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
        echo "Cannot locate $1"
        echo "Please use build_164.sh first";
        exit 1;
    fi
}


#-------------------------------------------------------------------------------
# remove_timestamp
#
# Arguments:
#   None
#
# Removes "[12345something] " from the start of $line
#
remove_timestamp()
{
    # check for debug kernel timestamp
    start_char=$(expr substr "$line" 1 1);
    if [ "$start_char" ==  "[" ];
    then
        # remove the timestamp
        stamp_len=1
        end_char=x
        while [ "$end_char" != "]" ];
        do
            stamp_len=$((stamp_len+1));
            end_char=$(expr substr "$line" $stamp_len 1);
        done

        # remove stamp-end and following space
        stamp_len=$((stamp_len+1));
        line=$(expr substr "$line" $stamp_len 500);

        # remove the initial spaces, like read does
        # expr can return empty string
        start_char=$(expr substr "$line" 1 1);
        while [ "$start_char" == " " ];
        do
            line=$(expr substr "$line" 2 500);
            start_char=$(expr substr "$line" 1 1);
        done
    fi
}

# main script starts here

# map configuration number to set of test cases
case $1
in
C0)  test_cases_2_exec="macsec";;
C1)  test_cases_2_exec="macsec";;
C3)  test_cases_2_exec="macsec";;
C4)  test_cases_2_exec="macsec";;
*)
    echo "Option [$1] not one of [C0,C1,C3,C4]";
    exit;;
esac

if [ "$2" != "" ]; then
    num_iterations=$2 # Execute tests these many times
else
    num_iterations=1
fi

if [ "$2" != "-i" ]; then
    prompt_after_iteration="n"
else
    prompt_after_iteration="y"
fi

if [ -z $ARCH ];
then
    echo "Please set ARCH";
    exit 1;
fi

# move to the script base directory
MY_DIR=$(dirname $0);
cd $MY_DIR

DDK_DIR=$(pwd)/../../
DEMOAPP_DIR=../../Examples/DemoApp_EIP164/scripts
TESTTOOL_MACSEC_DIR=../TestTool_EIP164/scripts
BUILDS_DIR=$(pwd)/Builds/$1

# sanity check the build
check_file_exists $BUILDS_DIR/driver_164_k.ko

# create the empty log file
LOG_FILE=Logs/testlog_$1_${ARCH}.log
SANITY_LOG_FILE=Logs/testlog_$1_${ARCH}_issues.log
COV_LOG_FILE=Logs/covlog_$1_${ARCH}.log
mkdir -p Logs
echo $1 > $LOG_FILE

# clear the dmesg output
dmesg -c  > /dev/null


echo "[Regress $1] Start Date and Time : `date`";
echo "[Regress $1] Logging to $LOG_FILE";

echo "[Regress $1] Test cases to run: $test_cases_2_exec";
echo "[Regress $1] Test cases to run: $test_cases_2_exec" >> $LOG_FILE

if grep driver_ks_k /proc/modules >/dev/null
then
  echo Removing UMPCI driver.
  rmmod driver_ks_k.ko
  rm -f /dev/umpci_c
fi

if grep driver_pktio_k /proc/modules >/dev/null
then
  echo Removing packet I/O driver.
  rmmod driver_pktio_k.ko
fi

# load the kernel components (including Packet I/O Driver)
insmod $BUILDS_DIR/driver_pktio_k.ko

count=0
export VALGRIND=

run_test_macsec=0
while [ $count -ne ${num_iterations} ]
do
            count=$(expr $count + 1)

            echo "[Regress $1] Iteration $count";

            if [ "$test_cases_2_exec" != "" ];
            then
                for test in  $test_cases_2_exec ;
                do
                    if [ $test = "macsec" ]
                    then
                        run_test_macsec=1
                    fi
                done
            fi

            if [ "$prompt_after_iteration" != "n" ];
            then
                echo "[Regress $1] Press ENTER to proceed";
                read response
            fi
done

# unload the kernel components

# capture final output, which could include leakage details
dmesg -c >> $LOG_FILE

if [ $run_test_macsec -ne 0 ]
then
  # now run DemoApp_EIP164 tests
  echo "[Regress $1] da_macsec"
  $DEMOAPP_DIR/run_da_eip164.sh $BUILDS_DIR >> $LOG_FILE

  # now run TestTool_EIP164 tests
  echo "[Regress $1] test_macsec"
  $TESTTOOL_MACSEC_DIR/run_test_eip164.sh $BUILDS_DIR >> $LOG_FILE
fi


# unload the Packet I/O Driver
rmmod $BUILDS_DIR/driver_pktio_k.ko

if [ -f $BUILDS_DIR/../driver_ks_k.ko ]
then
# load the kernel components
export VALGRIND=$VALGRIND_BIN

count=0
run_test_macsec=0
while [ $count -ne ${num_iterations} ]
do
    count=$(expr $count + 1);

    echo "[Regress $1] Iteration $count";

    if [ "$test_cases_2_exec" != "" ];
    then
        for test in  $test_cases_2_exec ;
        do
            if [ $test = "macsec" ];
            then
                run_test_macsec=1
            fi
        done
    fi

    if [ "$prompt_after_iteration" != "n" ];
    then
        echo "[Regress $1] Press ENTER to proceed";
        read response
    fi
done

export TESTTOOL_BIN=

if [ $run_test_macsec -ne 0 ]
then
    # Run the DemoApp_EIP164 in user mode
    echo "[Regress $1] da_macsec"
    $VALGRIND $BUILDS_DIR/da_macsec_u_combined >> $LOG_FILE 2>&1

    # Run the TestTool_EIP164 in user mode
    echo "[Regress $1] test_macsec"
    $VALGRIND $BUILDS_DIR/test_macsec_u_combined >> $LOG_FILE 2>&1
fi

# unload the kernel components
fi

# capture final output, which could include leakage details
dmesg -c >> $LOG_FILE

echo "[Regress $1] Finish Date and Time : `date`";

# gather coverage data
if [ "$COVER_DDK" = 'y' ]
then
    lcov -c -d $DDK_DIR -o $1.info > $COV_LOG_FILE 2>&1;

    if [ -d "$COVER_OUTPUT_DIR" ];
    then
        COVER_OUT=$COVER_OUTPUT_DIR/Coverage;
    else
        COVER_OUT=$BUILDS_DIR/../../Coverage;
    fi

    mkdir -p $COVER_OUT/$1;
    genhtml -o $1 $1.info >> $COV_LOG_FILE 2>&1;
    mv $1 $COVER_OUT;
    rm -f $1.info
fi

# sanity-check the log file
#grep -i -E "error|warning|dump|bug|fault|oops|fail|fatal|panic|poison|overflow|corrupt|invalid" $LOG_FILE | grep -v "Pass=100, Fail=0" > $SANITY_LOG_FILE
grep -i -E "error|warning|dump|bug|fault|oops|fail|fatal|panic|poison|overflow|corrupt|invalid" $LOG_FILE | grep -v "memory error detector" | grep -v 'detected and suppressed errors,' | grep -v "ERROR SUMMARY:"|grep -v "InPktsInvalid"  > $SANITY_LOG_FILE
sanity_count=$(cat $SANITY_LOG_FILE | wc -l)
if test $sanity_count == 0;
then
    rm $SANITY_LOG_FILE;
else
    echo "[Regress $1] Found" $sanity_count "ISSUES! Please inspect $SANITY_LOG_FILE";
    echo "[Regress $1] Found" $sanity_count "ISSUES!" >> $LOG_FILE
fi

# make a benchmark logfile, if applicable
benchmark_count=$(grep " Benchmark test " $LOG_FILE | wc -l);
if test $benchmark_count != 0;
then
    BENCHMARK_LOG_FILE=Logs/testlog_$1_${ARCH}_benchmark.log
    echo "[Regress $1] Extracting benchmark data to $BENCHMARK_LOG_FILE";
    echo "Benchmark data for $1 on $ARCH" > $BENCHMARK_LOG_FILE;

    dashes="\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-"
    state=0

    cat $LOG_FILE | while read line;
    do
        if [ $state -eq 0 -o $state -eq 1 ];
        then
            has_testcase=$(echo "$line" | grep "Test Case" | wc -l);
            if [ $has_testcase -ne 0 ];
            then
                remove_timestamp;
                testcase=$(expr substr "$line" 14 500)
                testcase="Test Case : "$testcase
                state=1;
            fi
        fi
        if [ $state -ne 0 ];
        then
            # state != 0
            if [ $state -eq 1 ];
            then
                has_benchmark=$(echo "$line" | grep -i "benchmark test" | wc -l);
                if [ $has_benchmark -ne 0 ];
                then
                    echo >> $BENCHMARK_LOG_FILE;
                    echo "$testcase" >> $BENCHMARK_LOG_FILE;
                    testcase="PARSING ERROR";
                    state=2;
                fi
            else
                # state>1
                has_recordnr=$(echo "$line" | grep "Record no : " | wc -l);
                if [ $has_recordnr -ne 0 ];
                then
                    remove_timestamp;
                    echo $line >> $BENCHMARK_LOG_FILE;
                fi

                has_dashes=$(echo "$line" | grep $dashes | wc -l);
                if [ $has_dashes -ne 0 ];
                then
                    state=$((state+1));
                fi

                # print after first line of dashes
                if [ "$state" -gt "2" ];
                then
                    remove_timestamp;
                    # skip empty lines
                    if [ ${#line} -ne 0 ];
                    then
                        echo "$line"  >> $BENCHMARK_LOG_FILE;
                    fi
                fi

                if [ $state -eq 5 ];
                then
                    state=0;
                fi
            fi
        fi
    done
fi

# count and report the results
count_pass=$(grep "PASSED" $LOG_FILE | wc -l)
echo "[Regress $1] Tests PASSED:" $count_pass
echo "[Regress $1] Tests PASSED:" $count_pass >> $LOG_FILE

count_fail=$(grep "FAILED" $LOG_FILE | wc -l)
echo "[Regress $1] Tests FAILED:" $count_fail
echo "[Regress $1] Tests FAILED:" $count_fail >> $LOG_FILE

# update the summary logs
SUMMARY_LOG_FILE=Logs/testlog_summary_${ARCH}.log
echo "Summary Log File" > $SUMMARY_LOG_FILE
BUILD_CONFIGS="C0 C1 C3 C4"
for ConfigLp in $BUILD_CONFIGS;
do
    LOG_FILE=Logs/testlog_${ConfigLp}_${ARCH}.log
    if [ -f  $LOG_FILE ];
    then
        # copy the ISSUES line
        grep "Regress $ConfigLp" $LOG_FILE | grep "ISSUES" >> $SUMMARY_LOG_FILE
        # copy the PASSED and FAILED lines
        grep "Regress $ConfigLp" $LOG_FILE | grep "] Tests " >> $SUMMARY_LOG_FILE
    fi
done

count_pass=$(grep "PASSED" Logs/testlog_C*_${ARCH}.log | grep -v "] Tests PASSED" | wc -l)
count_fail=$(grep "FAILED" Logs/testlog_C*_${ARCH}.log | grep -v "] Tests FAILED" | wc -l)
echo "----" >> $SUMMARY_LOG_FILE
echo "Total tests PASSED:" $count_pass >> $SUMMARY_LOG_FILE
echo "Total tests FAILED:" $count_fail >> $SUMMARY_LOG_FILE

# end of file
