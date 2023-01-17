/* test_case.h
 *
 * Test Tool for CfyE and SecY API's
 * General test case internal API
 *
 */

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Module        : ddk164                                                   */
/*   Version       : 3.2                                                      */
/*   Configuration : DDK-164-IPSEC-GPL                                        */
/*                                                                            */
/*   Date          : 2022-Jan-10                                              */
/*                                                                            */
/* Copyright (c) 2008-2021 by Rambus, Inc. and/or its subsidiaries.           */
/*                                                                            */
/* This program is free software: you can redistribute it and/or modify       */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation, either version 2 of the License, or          */
/* any later version.                                                         */
/*                                                                            */
/* This program is distributed in the hope that it will be useful,            */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of             */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               */
/* GNU General Public License for more details.                               */
/*                                                                            */
/* You should have received a copy of the GNU General Public License          */
/* along with this program. If not, see <http://www.gnu.org/licenses/>.       */
/* -------------------------------------------------------------------------- */

#ifndef TEST_CASE_H
#define TEST_CASE_H

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Default configuration */
#include "c_test_macsec.h"

/* Test Case record format */
#include "test_record.h"

/* SLAD PEC API */
#include "api_cfye.h"

/* PCL API */
#include "api_secy.h"

/* Driver Framework Basic Definitions API */
#include "basic_defs.h"


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

/* Test case internal packet administration data */
typedef struct
{
    void * SrcPkt_p;
    unsigned int SrcPkt_ByteCount;

    void * DstPkt_p;
    unsigned int DstPkt_ByteCount;
} Test_Packet_t;

/* Test case internal transform administration data */
typedef struct
{
    SecY_SAHandle_t TransformHandle;
    void * TransformRec_p;
    unsigned int SAIndex;
} Test_Transform_t;

/* Test case internal CfyE vPort administration data */
typedef struct
{
    unsigned int vPortId;
    CfyE_vPortHandle_t vPortHandle;
    unsigned int vPortIndex;
} Test_CfyEvPort_t;

/* Test case internal CfyE Rule administration data */
typedef struct
{
    unsigned int RuleId;
    CfyE_RuleHandle_t RuleHandle;
    unsigned int RuleIndex;
} Test_CfyERules_t;


/*----------------------------------------------------------------------------
 * test_macsec_sa_copy
 *
 * Copy SA parameters and build the transform record.
 *
 * TestConf_p (input)
 *      Test case configuration parameters
 *
 * SA_Input_p (input)
 *      Input SA parameters
 *
 * TransformParams_p (input)
 *      Parameters required to build transform record.
 *
 * TransformRec_p (output)
 *      Record containing pointer to transform record.
 *
 * SA_Output_p (input)
 *      Output SA parameters
 *
 * Return: none
 */
void
test_macsec_sa_copy(
        const Test_Case_ConfParams_t * const TestConf_p,
        const SecY_SA_t * const SA_Input_p,
        const Test_Case_Transform_t * const TransformParams_p,
        Test_Transform_t * const TransformRec_p,
        SecY_SA_t * const SA_Output_p);


/*----------------------------------------------------------------------------
 * test_macsec_device_init
 *
 * Attempt to initialize the device, including SecY and CfyE initialization.
 *
 * TestRec_p (input)
 *      Test case record parameters
 *
 * MaxChannelCount_p (output)
 *      Pointer to a memory location where the maximum number of Channels must
 *      be stored. Skipped if the pointer is NULL.
 *
 * MaxvPortCount_p (output)
 *      Pointer to a memory location where the maximum number of vPorts must
 *      be stored. Skipped if the pointer is NULL.
 *
 * MaxSACount_p (output)
 *      Pointer to a memory location where the maximum number of Security
 *      Associations must be stored. Skipped if the pointer is NULL.
 *
 * MaxSCCount_p (output)
 *      Pointer to a memory location where the maximum number of Secure
 *      Channels must be stored. Skipped if the pointer is NULL.
 *
 * MaxRuleCount_p (output)
 *      Pointer to a memory location where the maximum number of Rules must
 *      be stored. Skipped if the pointer is NULL.
 *
 * Return: true if the initialization is correctly done
 *         false if the installation failed
 */
bool
test_macsec_device_init(
        const Test_Case_Record_t * const TestRec_p,
        unsigned int * const MaxChannelCount_p,
        unsigned int * const MaxvPortCount_p,
        unsigned int * const MaxSACount_p,
        unsigned int * const MaxSCCount_p,
        unsigned int * const MaxRuleCount_p);


/*----------------------------------------------------------------------------
 * test_macsec_device_uninit
 *
 * Attempt to un-initialize the device,
 * including SecY and CfyE un-initialization
 *
 * TestRec_p (input)
 *      Test case record parameters
 *
 * Return: none
 */
void
test_macsec_device_uninit(
        const Test_Case_Record_t * const TestRec_p);


/*----------------------------------------------------------------------------
 * test_macsec_put_one
 *
 * Attempt to submit a single packet and check its status.
 *
 * TestConf_p (input)
 *      Test case configuration parameters
 *
 * Buffer_p (input)
 *      Pointer to the packet to submit.
 *
 * ByteCount (input)
 *      The byte count of the packet to submit.
 *
 * ChannelID (input)
 *      ChannelID of the channel onwhich the packet must be submitted.
 *
 * vPort (input)
 *      vPort on which the packet must be submitted.
 *
 * fControl (input)
 *      flag to indicate that packet must be sent with Control flag
 *
 * SecTAGOffset (input)
 *      SecTAGOffset of the packet to submit.
 *
 * Return: true if a packet was submit without error.
 *         false an error happened.
 */
bool
test_macsec_put_one(
        const Test_Case_ConfParams_t * const TestConf_p,
        const uint8_t * const Buffer_p,
        const unsigned int ByteCount,
        unsigned int ChannelID,
        unsigned int vPort,
        unsigned int SecTAGOffset,
        bool fControl);


/*----------------------------------------------------------------------------
 * test_macsec_get_one
 *
 * Attempt to receive a single packet.
 * Try this a configurable number of times. When a packet is received,
 * check its status.
 *
 * TestConf_p (input)
 *      Test case configuration parameters
 *
 * Buffer_p (output)
 *      Location to store received result packet.
 *
 * ByteCount_p (output)
 *      Location to store received result packet byte count.
 *
 * Return: true if a packet was received.
 *         false if no packet received (timeout) or the packet had an error.
 */
bool
test_macsec_get_one(
        const Test_Case_ConfParams_t * const TestConf_p,
        uint8_t * const Buffer_p,
        unsigned int * const ByteCount_p,
        unsigned int ChannelID);


/*----------------------------------------------------------------------------
 * test_macsec_cmp_pkts
 *
 * Compare the received packets with the expected one.
 *
 * Recieved_Pkt_p (input)
 *      Location to store received result packet.
 *
 * Recieved_Bytecount (input)
 *      The received result packet byte count.
 *
 * Expected_Pkt_p (input)
 *      Location to store expected result packet.
 *
 * Expected_Bytecount (input)
 *      The expected result packet byte count.
 *
 * Return: true if they have the same length and data.
 *         false if they have different length and data.
 */
bool
test_macsec_cmp_pkts(
        const void * Recieved_Pkt_p,
        const unsigned int Recieved_Bytecount,
        const void * Expected_Pkt_p,
        const unsigned int Expected_Bytecount);


/*----------------------------------------------------------------------------
 * test_macsec_single_transform_statistics_test
 *
 * perform the transform statistics test one time for the specified test record
 *
 * TestConf_p (input)
 *      Test case configuration parameters
 *
 * TC_Transform_p (input)
 *      The input transform record data to be compared with.
 *
 * TR_Admin_p (output)
 *      Transform administration data
 *
 * Return: true if the test is successful
 *         false if the test failed
 */
bool
test_macsec_single_transform_statistics_test(
        const Test_Case_ConfParams_t * TestConf_p,
        const Test_Case_Transform_t * TC_Transform_p,
        Test_Transform_t * Tr_Admin_p);


/*----------------------------------------------------------------------------
 * test_macsec_transform_install
 *
 * Install transform record(s) for the test record
 *
 * TestConf_p (input)
 *      Test case configuration parameters
 *
 * TestRec_p (input)
 *      Test record data
 *
 * TransformStartIndex (input)
 *      Index of the first transform to install
 *
 * NumberOfTransforms (input)
 *      Number of transforms to install
 *
 * TR_Admin_p (output)
 *      Transform administration data
 *
 * Return: true if the transform(s) is(are) installed
 *         false if transform installation failed
 */
bool
test_macsec_transform_install(
        const Test_Case_ConfParams_t * TestConf_p,
        const Test_Case_Record_t * TestRec_p,
        const unsigned int TransformStartIndex,
        const unsigned int NumberOfTransforms,
        Test_Transform_t ** TR_Admin_pp);


/*----------------------------------------------------------------------------
 * test_macsec_transform_uninstall
 *
 * Un-install transform record(s) for the test record
 *
 * TestConf_p (input)
 *      Test case configuration parameters
 *
 * NumberOfTransforms (input)
 *      Number of transforms to un-install
 *
 * TR_Admin_p (output)
 *      Transform administration data
 *
 * Return: true if the transform(s) is(are) un-installed
 *         false if transform un-installation failed
 */
bool
test_macsec_transform_uninstall(
        const Test_Case_ConfParams_t * TestConf_p,
        const unsigned int NumberOfTransforms,
        Test_Transform_t * TR_Admin_p);


/*----------------------------------------------------------------------------
 * test_macsec_transform_nextpn_update
 *
 * Update NextPN in transform record.
 *
 * TestConf_p (input)
 *      Test case configuration parameters
 *
 * TR_Admin_p (input)
 *      Transform administration data
 *
 * NextPN_Lo (input)
 *      Least significant 32 bits of new NextPN field.
 *
 * NextPN_Hi (input)
 *      Most significant 32 bits of new NextPN field.
 *
 * SeqMask (input)
 *      New value for WindowSize (mask) in SA.
 *
 * Return: true if the operation succeeded.
 *         false if transform NextPN update failed
 */
bool
test_macsec_transform_nextpn_update(
        const Test_Case_ConfParams_t * TestConf_p,
        Test_Transform_t * TR_Admin_p,
        uint32_t NextPN_Lo,
        uint32_t NextPN_Hi,
        uint32_t SeqMask);


/*----------------------------------------------------------------------------
 * test_macsec_single_transform_update
 *
 * Update the specified transform record with new SA data
 *
 * TestConf_p (input)
 *      Test case configuration parameters
 *
 * TestTransform_p (input)
 *      The new transform record data
 *
 * TR_Admin_p (output)
 *      Transform administration data
 *
 * Return: true if the transform is correctly updated
 *         false if transform update failed
 */
bool
test_macsec_single_transform_update(
        const Test_Case_ConfParams_t * const TestConf_p,
        const Test_Case_Transform_t * const TestTransform_p,
        Test_Transform_t * Tr_Admin_p);


/*----------------------------------------------------------------------------
 * test_macsec_pkt_sanity_check
 *
 * Perform packet test record sanity checks
 *
 * TestConf_p (input)
 *      Test case configuration parameters
 *
 * TestRec_p (input)
 *      Test record data
 *
 * Return: true if the packet buffer(s) is(are) allocated
 *         false if packet buffer allocation failed
 */
bool
test_macsec_pkt_sanity_check(
        const Test_Case_ConfParams_t * TestConf_p,
        const Test_Case_Record_t * TestRec_p);


/*----------------------------------------------------------------------------
 * test_macsec_pkt_alloc
 *
 * Allocate packet buffer(s) for one packet
 *
 * PacketCount (input)
 *      Number of buffers to allocate
 *
 * TestRec_p (input)
 *      Test record data
 *
 * Return: true if the buffer(s) is(are) allocated
 *         false if buffer allocation failed
 */
bool
test_macsec_pkt_alloc(
        const Test_Case_Record_t * TestRec_p,
        Test_Packet_t ** PKT_Admin_pp);


/*----------------------------------------------------------------------------
 * test_macsec_pkt_free
 *
 * Free packet buffer(s)
 *
 * TestRec_p (input)
 *      Test record data
 *
 * PKT_Admin_pp (output)
 *      Packet administration data
 *
 * Return: true if the buffer(s) is(are) freed
 *         false if buffer freeing failed
 */
bool
test_macsec_pkt_free(
        const Test_Case_Record_t * TestRec_p,
        Test_Packet_t * PKT_Admin_p);


/*----------------------------------------------------------------------------
 * test_macsec_transform_statistics_test
 *
 * perform transform statistics test for the test record
 *
 * TestConf_p (input)
 *      Test case configuration parameters
 *
 * TestRec_p (input)
 *      Test record data
 *
 * TR_Admin_p (output)
 *      Transform administration data
 *
 * Return: true if the test is successful
 *         false if the test failed
 */
bool
test_macsec_transform_statistics_test(
        const Test_Case_ConfParams_t * TestConf_p,
        const Test_Case_Record_t * TestRec_p,
        Test_Transform_t * TR_Admin_p);


/*----------------------------------------------------------------------------
 * test_macsec_SecY_vPort_statistics
 *
 * Display (report) the vPort related statistics and optionally verify (test)
 * it against the expected one.
 *
 * TestConf_p (input)
 *      Test case configuration parameters
 *
 * TestRec_p (input)
 *      Test record data
 *
 * vPortToUseAsDefault (input)
 *      vPort to to use as default
 *
 * vPortStatisticsToUse_p (input)
 *      Pointer to vPort statistics to use
 *
 * Return: true if the test is successful
 *         false if the test failed
 */
bool
test_macsec_SecY_vPort_statistics(
        const Test_Case_ConfParams_t * TestConf_p,
        const Test_Case_Record_t * TestRec_p,
        const unsigned int vPortToUseAsDefault,
        const Test_Case_vPortStat_t * vPortStatisticsToUse_p);


/*----------------------------------------------------------------------------
 * test_macsec_pkt_test
 *
 * Perform packet processing test for the test record
 *
 * TestConf_p (input)
 *      Test case configuration parameters
 *
 * TestRec_p (input)
 *      Test record data
 *
 * StartPacketIndex (input)
 *      Index of first packet to test
 *
 * NumberOfPackets (input)
 *      Number of packets to test
 *
 * PKT_Admin_p (output)
 *      Packet administration data
 *
 * ChannelCount (input)
 *      Number of channels supported by device, redirect any packets with
 *      higher channel numbers to Ch#0
 *
 * Return: true if the packet test is successful
 *         false if the packet test failed
 */
bool
test_macsec_pkt_test(
        const Test_Case_ConfParams_t * TestConf_p,
        const Test_Case_Record_t * TestRec_p,
        const unsigned int StartPacketIndex,
        const unsigned int NumberOfPackets,
        Test_Packet_t * PKT_Admin_p,
        unsigned int ChannelCount);


/*----------------------------------------------------------------------------
 * test_macsec_channel_rules_update
 *
 * Perform channel rules update
 *
 * TestConf_p (input)
 *      Test case configuration parameters
 *
 * TestRec_p (input)
 *      Test record data
 *
 * Return: true if the rules update is successful
 *         false if the rules update failed
 */
bool
test_macsec_channel_rules_update(
        const Test_Case_ConfParams_t * TestConf_p,
        const Test_Case_Record_t * TestRec_p);


/*----------------------------------------------------------------------------
 * test_macsec_secure_channel_rules_update
 *
 * Perform secure channel rules update
 *
 * TestConf_p (input)
 *      Test case configuration parameters
 *
 * TestRec_p (input)
 *      Test record data
 *
 * Return: true if the rules update is successful
 *         false if the rules update failed
 */
bool
test_macsec_secure_channel_rules_update(
        const Test_Case_ConfParams_t * TestConf_p,
        const Test_Case_Record_t * TestRec_p);


/*----------------------------------------------------------------------------
 * test_macsec_CfyE_install
 *
 * Install vPort(s) and rule(s) for the test record
 *
 * TestConf_p (input)
 *      Test case configuration parameters
 *
 * TestRec_p (input)
 *      Test record data
 *
 * vPortAdmin_pp (output)
 *      vPort administration data
 *
 * RuleAdmin_pp (output)
 *      Rule administration data
 *
 * fVerbose (input)
 *      Indication to print verbose information or not
 *
 * fDeviceUpdate (input)
 *      True if CfyE_Device_Update must be called
 *
 * BaseRuleIndex (input)
 *      Starting rule index when rules are allocated by index.
 *
 * Return: true if the vPort(s) and rule(s) are installed
 *         false if the installation failed
 */
bool
test_macsec_CfyE_install(
        const Test_Case_ConfParams_t * TestConf_p,
        const Test_Case_Record_t * TestRec_p,
        Test_CfyEvPort_t ** vPortAdmin_pp,
        Test_CfyERules_t ** RuleAdmin_pp,
        const bool fVerbose,
        const bool fDeviceUpdate,
        const unsigned int BaseRuleIndex);


/*----------------------------------------------------------------------------
 * test_macsec_CfyE_uninstall
 *
 * Un-install vPort(s) and rule(s) for the test record
 *
 * TestConf_p (input)
 *      Test case configuration parameters
 *
 * TestRec_p (input)
 *      Test record data
 *
 * vPortAdmin_p (input)
 *      vPort administration data
 *
 * RuleAdmin_p (input)
 *      Rule administration data
 *
 * fVerbose (input)
 *      Indication to print verbose information or not
 *
 * Return: true if the vPort(s) and rule(s) are un-installed
 *         false if un-installation failed
 */
bool
test_macsec_CfyE_uninstall(
        const Test_Case_ConfParams_t * TestConf_p,
        const Test_Case_Record_t * TestRec_p,
        Test_CfyEvPort_t * vPortAdmin_p,
        Test_CfyERules_t * RuleAdmin_p,
        const bool fVerbose);


/*----------------------------------------------------------------------------
 * test_macsec_CfyE_Rules_update
 *
 * Perform vPort and/or classification rules update
 *
 * TestConf_p (input)
 *      Test case configuration parameters
 *
 * TestRec_p (input)
 *      Test record data
 *
 * vPortAdmin_p (input)
 *      vPort administration data
 *
 * RuleAdmin_p (input)
 *      Rule administration data
 *
 * Return: true if the rules update is successful
 *         false if the rules update failed
 */
bool
test_macsec_CfyE_update(
        const Test_Case_ConfParams_t * TestConf_p,
        const Test_Case_Record_t * TestRec_p,
        Test_CfyEvPort_t * vPortAdmin_p,
        Test_CfyERules_t * RuleAdmin_p);


/*----------------------------------------------------------------------------
 * test_macsec_CfyE_statistics_test
 *
 * Read and test classification statistics
 *
 * TestConf_p (input)
 *      Test case configuration parameters
 *
 * TestRec_p (input)
 *      Test record data
 *
 * RuleAdmin_p (input)
 *      Rule administration data
 *
 * Return: true if the statistics test is successful otherwise false
 */
bool
test_macsec_CfyE_statistics_test(
        const Test_Case_ConfParams_t * TestConf_p,
        const Test_Case_Record_t * TestRec_p,
        Test_CfyERules_t * RuleAdmin_p);


/*----------------------------------------------------------------------------
 * test_macsec_CfyE_statsummary_test
 *
 * Read and test classification statistics summary
 *
 * TestConf_p (input)
 *      Test case configuration parameters
 *
 * BeginIndex (input)
 *       Begin TCAM index for the test
 *
 * NumberOfEntries (input)
 *       Number of TCAM entries to test
 *
 * SummaryMatchPattern (input)
 *      Summary match pattern
 *
 * Return: true if the statistics test is successful otherwise false
 */
bool
test_macsec_CfyE_statsummary_test(
        const Test_Case_ConfParams_t * TestConf_p,
        unsigned int BeginIndex,
        unsigned int NumberOfEntries,
        unsigned int SummaryMatchPattern);


/*----------------------------------------------------------------------------
 * test_macsec_read_entries
 *
 * Use the SecY and CfyE API functions to read SAs, vPorts and Rules from
 * the driver.
 *
 * DeviceId (input)
 *     ID of the device from which to read the entries.
 *
 * fUseCfyE (input)
 *     flag to indicate whether the CfyE related entries (vPorts and Rules)
 *     should be read.
 *
 * Return: true if functions were run successully, false otherwise.
 */
bool
test_macsec_read_entries(
        const unsigned int DeviceId,
        const bool fUseCfyE);


/*----------------------------------------------------------------------------
 * test_macsec_show_diagnostics
 *
 * Use the SecY and CfyE API functions to make daignotic dumps of the
 * device.
 *
 * DeviceId (input)
 *     ID of the device from which to show diagnostics.
 *
 * vPortCount (input)
 *     Number of vPorts to check, 0 for all vPorts of the device.
 *
 * fUseCfyE (input)
 *     flag to indicate whether the CfyE related diagnostics (vPorts and Rules)
 *     should be shown.
 *
 * Return: true if functions were run successully, false otherwise.
 */
bool
test_macsec_show_diagnostics(
        const unsigned int DeviceId,
        unsigned int vPortCount,
        const bool fUseCfyE);


#endif /* TEST_CASE_H */


/* end of file test_case.h */
