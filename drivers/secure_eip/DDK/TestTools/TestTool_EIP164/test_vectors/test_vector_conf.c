/* test_vector_conf.c
 *
 * Test Tool for CfyE and SecY API's
 * Implementation of the test vectors test case configuration and general data
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

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

#include "test_vector_conf.h"


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

/* Default configuration */
#include "c_test_macsec.h"

/* Driver Framework Basic Defs API */
#include "basic_defs.h"

/* Test Case record format */
#include "test_record.h"

Test_Case_ConfParams_t ConfParamsEgressDefaultBypass =
{
    /* Device ID */
    1,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_1,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    false,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_BYPASS,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    0,

    /* Rule count */
    0,

    /* vPort count */
    0,

    /* SC count */
    0,

    /* SA count */
    0,
};

Test_Case_ConfParams_t ConfParamsEgressInterruptsBypass =
{
    /* Device ID */
    1,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_1,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    false,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_BYPASS,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    0,

    /* Rule count */
    0,

    /* vPort count */
    0,

    /* SC count */
    0,

    /* SA count */
    0,
};

Test_Case_ConfParams_t ConfParamsIngressDefaultBypass =
{
    /* Device ID */
    0,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_1,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    true,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_BYPASS,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    0,

    /* Rule count */
    0,

    /* vPort count */
    0,

    /* SC count */
    0,

    /* SA count */
    0,
};

Test_Case_ConfParams_t ConfParamsEgressDefaultDropCRC =
{
    /* Device ID */
    1,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_1,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    false,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_DROP_CRC_ERROR,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    0,

    /* Rule count */
    0,

    /* vPort count */
    0,

    /* SC count */
    0,

    /* SA count */
    0,
};

Test_Case_ConfParams_t ConfParamsEgressDefaultDropInternal =
{
    /* Device ID */
    1,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_1,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    false,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_DROP_INTERNAL,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    0,

    /* Rule count */
    0,

    /* vPort count */
    0,

    /* SC count */
    0,

    /* SA count */
    0,
};

Test_Case_ConfParams_t ConfParamsEgressDefaultDropInternalKAT5 =
{
    /* Device ID */
    1,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_5,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    false,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_DROP_INTERNAL,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    0,

    /* Rule count */
    0,

    /* vPort count */
    0,

    /* SC count */
    0,

    /* SA count */
    0,
};

Test_Case_ConfParams_t ConfParamsIngressDefaultDropCRC =
{
    /* Device ID */
    0,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_1,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    true,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_DROP_CRC_ERROR,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    0,

    /* Rule count */
    0,

    /* vPort count */
    0,

    /* SC count */
    0,

    /* SA count */
    0,
};

Test_Case_ConfParams_t ConfParamsIngressDefaultDropInternal =
{
    /* Device ID */
    0,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_1,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    true,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_DROP_INTERNAL,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    0,

    /* Rule count */
    0,

    /* vPort count */
    0,

    /* SC count */
    0,

    /* SA count */
    0,
};

Test_Case_ConfParams_t ConfParamsIngressDefaultDropInternalKAT5 =
{
    /* Device ID */
    0,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_5,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    true,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_DROP_INTERNAL,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    0,

    /* Rule count */
    0,

    /* vPort count */
    0,

    /* SC count */
    0,

    /* SA count */
    0,
};

Test_Case_ConfParams_t ConfParamsEgressReducedDropCRC =
{
    /* Device ID */
    1,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_1,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    false,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_DROP_CRC_ERROR,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    1,

    /* Rule count */
    16,

    /* vPort count */
    8,

    /* SC count */
    8,

    /* SA count */
    16,
};

Test_Case_ConfParams_t ConfParamsEgressReducedDropInternal =
{
    /* Device ID */
    1,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_1,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    false,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_DROP_INTERNAL,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    1,

    /* Rule count */
    16,

    /* vPort count */
    8,

    /* SC count */
    8,

    /* SA count */
    16,
};

Test_Case_ConfParams_t ConfParamsEgressReducedDropInternalIndex =
{
    /* Device ID */
    1,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_1,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    false,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_DROP_INTERNAL,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    true,

    /* Channel count */
    1,

    /* Rule count */
    16,

    /* vPort count */
    8,

    /* SC count */
    8,

    /* SA count */
    16,
};

Test_Case_ConfParams_t ConfParamsIngressReducedDropCRC =
{
    /* Device ID */
    0,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_1,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    true,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_DROP_CRC_ERROR,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    4,

    /* Rule count */
    16,

    /* vPort count */
    8,

    /* SC count */
    8,

    /* SA count */
    16,
};

Test_Case_ConfParams_t ConfParamsIngressReducedDropInternal =
{
    /* Device ID */
    0,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_1,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    true,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_DROP_INTERNAL,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    4,

    /* Rule count */
    16,

    /* vPort count */
    8,

    /* SC count */
    8,

    /* SA count */
    16,
};


Test_Case_ConfParams_t ConfParamsIngressReducedDropInternalIndex =
{
    /* Device ID */
    0,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_1,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    true,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_DROP_INTERNAL,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    true,

    /* Channel count */
    4,

    /* Rule count */
    16,

    /* vPort count */
    8,

    /* SC count */
    8,

    /* SA count */
    16,
};


Test_Case_ConfParams_t ConfParamsEgressLowLatencyBypass =
{
    /* Device ID */
    1,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_1,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    false,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_BYPASS,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    true,

    /* Allocate by index. */
    false,

    /* Channel count */
    0,

    /* Rule count */
    0,

    /* vPort count */
    0,

    /* SC count */
    0,

    /* SA count */
    0,
};

Test_Case_ConfParams_t ConfParamsIngressLowLatencyBypass =
{
    /* Device ID */
    0,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_1,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    true,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_BYPASS,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    true,

    /* Allocate by index. */
    false,

    /* Channel count */
    0,

    /* Rule count */
    0,

    /* vPort count */
    0,

    /* SC count */
    0,

    /* SA count */
    0,
};

Test_Case_ConfParams_t ConfParamsEgressBasicTransform =
{
    /* Device ID */
    1,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_1,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    false,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_BYPASS,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    0,

    /* Rule count */
    0,

    /* vPort count */
    0,

    /* SC count */
    0,

    /* SA count */
    0,
};

#if defined(TEST_IPSEC_ENABLE)
Test_Case_ConfParams_t ConfParamsIPsecEgressBasicTransform =
{
    /* Device ID */
    1,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_1,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    false,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_DROP_INTERNAL,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    0,

    /* Rule count */
    0,

    /* vPort count */
    0,

    /* SC count */
    0,

    /* SA count */
    0,
};

Test_Case_ConfParams_t ConfParamsIPsecEgressMultiTransform =
{
    /* Device ID */
    1,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_4,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    false,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_DROP_INTERNAL,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    0,

    /* Rule count */
    0,

    /* vPort count */
    0,

    /* SC count */
    0,

    /* SA count */
    0,
};

Test_Case_ConfParams_t ConfParamsIPsecIngressMultiTransform =
{
    /* Device ID */
    0,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_4,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    true,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0x9999,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_DROP_INTERNAL,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    0,

    /* Rule count */
    0,

    /* vPort count */
    0,

    /* SC count */
    0,

    /* SA count */
    0,
};


Test_Case_ConfParams_t ConfParamsIPsecIngressBasicTransform =
{
    /* Device ID */
    1,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_1,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    true,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0x9999,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_DROP_INTERNAL,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    0,

    /* Rule count */
    0,

    /* vPort count */
    0,

    /* SC count */
    0,

    /* SA count */
    0,
};

Test_Case_ConfParams_t ConfParamsIPsecIngressVLANTransform =
{
    /* Device ID */
    1,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_1,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    true,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0x0081,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_DROP_INTERNAL,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    0,

    /* Rule count */
    0,

    /* vPort count */
    0,

    /* SC count */
    0,

    /* SA count */
    0,
};

Test_Case_ConfParams_t ConfParamsIPsecEgressMPLS =
{
    /* Device ID */
    1,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_1,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    false,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_DROP_INTERNAL,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    0,

    /* Rule count */
    0,

    /* vPort count */
    0,

    /* SC count */
    0,

    /* SA count */
    0,
};

Test_Case_ConfParams_t ConfParamsIPsecEgressVLAN =
{
    /* Device ID */
    1,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_1,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    false,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_DROP_INTERNAL,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    0,

    /* Rule count */
    0,

    /* vPort count */
    0,

    /* SC count */
    0,

    /* SA count */
    0,
};
#endif

Test_Case_ConfParams_t ConfParamsEgressBasicTransformKAT5 =
{
    /* Device ID */
    1,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_5,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    false,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_BYPASS,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    0,

    /* Rule count */
    0,

    /* vPort count */
    0,

    /* SC count */
    0,

    /* SA count */
    0,
};

Test_Case_ConfParams_t ConfParamsIngressBasicTransform =
{
    /* Device ID */
    0,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_1,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    true,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_BYPASS,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    0,

    /* Rule count */
    0,

    /* vPort count */
    0,

    /* SC count */
    0,

    /* SA count */
    0,
};

Test_Case_ConfParams_t ConfParamsIngressBasicTransformKAT5 =
{
    /* Device ID */
    0,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_5,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    true,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_BYPASS,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    0,

    /* Rule count */
    0,

    /* vPort count */
    0,

    /* SC count */
    0,

    /* SA count */
    0,
};

Test_Case_ConfParams_t ConfParamsCryptAuthenticateEncode =
{
    /* Device ID */
    1,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_1,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    false,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_BYPASS,

    /* The length of the bypass data during crypt-authenticate operation */
    30,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    0,

    /* Rule count */
    0,

    /* vPort count */
    0,

    /* SC count */
    0,

    /* SA count */
    0,
};

Test_Case_ConfParams_t ConfParamsCryptAuthenticateDecode =
{
    /* Device ID */
    0,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_1,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    true,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_BYPASS,

    /* The length of the bypass data during crypt-authenticate operation */
    32,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    0,

    /* Rule count */
    0,

    /* vPort count */
    0,

    /* SC count */
    0,

    /* SA count */
    0,
};

Test_Case_ConfParams_t ConfParamsEgressMultiTransform =
{
    /* Device ID */
    1,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_1,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    false,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_BYPASS,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    0,

    /* Rule count */
    0,

    /* vPort count */
    0,

    /* SC count */
    0,

    /* SA count */
    0,
};

Test_Case_ConfParams_t ConfParamsIngressMultiTransform =
{
    /* Device ID */
    0,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_1,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    true,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */

    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_BYPASS,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    0,

    /* Rule count */
    0,

    /* vPort count */
    0,

    /* SC count */
    0,

    /* SA count */
    0,
};

Test_Case_ConfParams_t ConfParamsEgressExtPN =
{
    /* Device ID */
    1,

    /* Unique test case identifier */
    TEST_MACSEC_TC_ID_KAT_1,

    /* Wait timeout for one iteration, in ms */
    TEST_MACSEC_RETRY_DELAY_MS,

    /* Maximum number of iterations (retries) */
    TEST_MACSEC_NOF_TRIES,

    /* Test duration time, in seconds */
    0,

    /* Use verbose trace info */
    true,

    /* Ingress when true otherwise egress */
    false,

    /** IPsec Ingress Header EType */
#if defined(TEST_IPSEC_ENABLE)
    0,
#endif

    /* --- SecY specifics --- */
    /* Default packet processing rule */
    TEST_PKT_PROCESS_RULE_BYPASS,

    /* The length of the bypass data during crypt-authenticate operation */
    0,

    /* --- CfyE specifics --- */
    /* Use low-latency bypass when true */
    false,

    /* Allocate by index. */
    false,

    /* Channel count */
    0,

    /* Rule count */
    0,

    /* vPort count */
    0,

    /* SC count */
    0,

    /* SA count */
    0,
};


/* end of file test_vector_conf.c */
