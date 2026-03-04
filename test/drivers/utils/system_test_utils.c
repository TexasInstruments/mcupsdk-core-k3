/*
 *  Copyright (C) 2021-2024 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file system_test_utils.c
 *
 *  \brief This file contains implementation of all APIs used by the
 *  system test framework for testing multi core scenarios.
 *
 */


/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdio.h>
#include <inttypes.h>
#include <drivers/soc.h>
#include <kernel/dpl/ClockP.h>
#include <drivers/ipc_notify.h>
#include <unity.h>
#include "ti_drivers_open_close.h"
#include "system_test_utils.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief  Defines wait cycle time (us) in between test case status checks */
#define TEST_WAIT_CYCLE_TIME (1000u)

/** \brief  Macro to pack the 32 bit result from test cases */
#define PACK_RESULT(core_id, tc_id, result)  (((core_id & 0x0F) << 24) | ((result & 0xFF) << 16) | tc_id)

/** \brief  Macro to get the core ID from the packed result */
#define GET_CORE_ID(x)   ((x >> 24) & 0xFF)

/** \brief  Macro to get the test case ID from the packed result */
#define GET_TC_ID(x)     (x & 0xFFFF)

/** \brief  Macro to get the test case result from the packed result */
#define GET_TC_RESULT(x) ((x >> 16) & 0xFF)

/** \brief  Macro to define remote client ID for transfer of test case ID */
#define REMOTE_CLIENT_ID (2u)

/** \brief  Macro to define remote client ID for transfer of test case result */
#define MASTER_CLIENT_ID (3u)

#if defined(SOC_AM62AX) || defined (SOC_AM62DX) || defined(SOC_AM62X) || defined(SOC_AM275X)

/** \brief  Macro to define main core ID */
#define MAIN_CORE_ID CSL_CORE_ID_R5FSS0_0

#elif defined(SOC_AM62PX)

/** \brief  Macro to define main core ID */
#define MAIN_CORE_ID CSL_CORE_ID_WKUP_R5FSS0_0

#else
#error "Unsupported SOC"
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief  Variable to hold number of test cases executed on remote cores */
volatile uint32_t TestCaseCount = 0u;

/** \brief  Variable to hold the count of test results received */
volatile uint32_t TestResultCounter = 0;

/** \brief  Array to hold the test results */
volatile uint32_t TestResult[CSL_CORE_ID_MAX] = {0};

/** \brief  Array to hold all remote core IDs with ability to run test cases */
volatile uint32_t gRemoteCoreId[CSL_CORE_ID_MAX] = {0};

/** \brief  Variable to hold the test case ID */
volatile uint32_t TestCaseId = 0u;

#if TEST_ENABLE_SYSTEM_DEBUG == 1

/** \brief  Variable to help debug the test cases
 *          This variable can be set from CCS to debug the required test case */
volatile uint32_t waitForUserTrigger = 0u;

#endif

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void TestUtils_resultMsgHandler(uint16_t remoteCoreId, uint16_t localClientId, uint32_t msgValue, void *args);
static void TestUtils_caseIdMsgHandler(uint16_t remoteCoreId, uint16_t localClientId, uint32_t msgValue, void *args);
static int32_t TestUtils_testCase(int32_t testCaseId, void* args);
static void TestUtils_executeTestCase(void* args);
static void TestUtils_ipcRemoteCoreStart();
static void TestUtils_ipcMainCoreStart();

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 * @brief Main test entry point. Registers handlers and starts test execution depending on core role.
 *
 * @param args Arguments for test main (unused)
 */
void test_main(void *args)
{
    int32_t status;
    uint8_t core;
    uint8_t coreIndex = 0;

    /* Core selection is done in SYSCONFIG. Collect list of enabled cores here */
    for(core = 0; core != CSL_CORE_ID_MAX; core++)
    {
        if(IpcNotify_isCoreEnabled(core))
        {
            gRemoteCoreId[coreIndex++] = core;
        }
    }

    gRemoteCoreId[coreIndex] = CSL_CORE_ID_MAX;

    if(IpcNotify_getSelfCoreId()==MAIN_CORE_ID)
    {
        /* register a handler to receive the test results */
        status = IpcNotify_registerClient(MASTER_CLIENT_ID, TestUtils_resultMsgHandler, NULL);
        DebugP_assert(status==SystemP_SUCCESS);

        TestUtils_ipcMainCoreStart();

        /* unregister handlers */
        IpcNotify_unregisterClient(MASTER_CLIENT_ID);
    }
    else
    {
        /* register a handler to receive the test case ID */
        status = IpcNotify_registerClient(REMOTE_CLIENT_ID, TestUtils_caseIdMsgHandler, NULL);
        DebugP_assert(status==SystemP_SUCCESS);

        TestUtils_ipcRemoteCoreStart();

        /* unregister handlers */
        IpcNotify_unregisterClient(REMOTE_CLIENT_ID);
    }

}

/**
 * @brief Unity setUp function (required, but not used).
 */
void setUp(void)
{
}

/**
 * @brief Unity tearDown function (required, but not used).
 */
void tearDown(void)
{
}

/**
 * @brief Dummy test case function for testing purposes
 *
 * This is a placeholder test function that can be used as a template
 * or stub for actual test implementations. It typically performs no
 * operations and may return a default success status.
 * @param args Additional arguments
 * @return int Returns 0 on success, non-zero on failure
 */
int32_t TestUtils_dummyTestCase(void *args)
{
    int32_t status = SystemP_SUCCESS;

    ClockP_sleep(5);

    return status;
}

/**
 * @brief Synchronizes with a remote core using IPC Notify.
 *
 * This function sends a synchronization message to the specified remote core
 * and waits for a response within the given timeout period.
 *
 * @param remoteCoreId ID of the remote core to synchronize with
 * @param timeout Timeout duration in milliseconds to wait for the response
 * @return int32_t SystemP_SUCCESS on successful synchronization, error code otherwise
 */
int32_t TestUtils_syncRemoteCore(uint32_t remoteCoreId, uint32_t timeout)
{
    /* Send message to remote core  */
    int32_t status = IpcNotify_sendSync(remoteCoreId);

    if (status != SystemP_SUCCESS)
    {
        DebugP_log(" IpcNotify_sendSync failed!!\r\n");
    }

    /* Wait message from remote core */
    status = IpcNotify_waitSync(remoteCoreId, SystemP_WAIT_FOREVER);

    if (status != SystemP_SUCCESS)
    {
        DebugP_log(" IpcNotify_sendSync failed!!\r\n");
    }

    return status;
}

/* ========================================================================== */
/*                      Internal Function Definitions                         */
/* ========================================================================== */

/* message handler to receive the test results */
/**
 * @brief Message handler to receive the test results from remote cores.
 *
 * @param remoteCoreId ID of the remote core sending the result
 * @param localClientId Local client ID
 * @param msgValue Message value containing the test result
 * @param args Additional arguments (unused)
 */
static void TestUtils_resultMsgHandler(uint16_t remoteCoreId, uint16_t localClientId, uint32_t msgValue, void *args)
{
    if ((remoteCoreId != MAIN_CORE_ID) && (localClientId == MASTER_CLIENT_ID))
    {
        TestResult[TestResultCounter++] = msgValue;
    }
}

/* message handler to receive test case IDs */
/**
 * @brief Message handler to receive test case IDs from the main core.
 *
 * @param remoteCoreId ID of the remote core
 * @param localClientId Local client ID
 * @param msgValue Message value containing the test case ID
 * @param args Additional arguments (unused)
 */
static void TestUtils_caseIdMsgHandler(uint16_t remoteCoreId, uint16_t localClientId, uint32_t msgValue, void *args)
{
    TestCaseId = msgValue;
}

/**
 * @brief Runs a test case by its ID.
 *
 * @param testCaseId ID of the test case to run
 * @param args Arguments to pass to the test function
 * @return int32_t SystemP_SUCCESS on success, SystemP_FAILURE otherwise
 */
static int32_t TestUtils_testCase(int32_t testCaseId, void* args)
{
    int32_t status = SystemP_FAILURE;
    int32_t testCaseFound = 0;
    int i = 0;

    for (i = 0; gTestCase[i].testFptr != NULL; i++)
    {
        if (gTestCase[i].testCaseId == testCaseId)
        {
            if (gTestCase[i].testFptr)
            {
                DebugP_log("Core[%d]: Starting execution of Test case ID = %d\r\n", IpcNotify_getSelfCoreId(), testCaseId);
                status = gTestCase[i].testFptr(args);
                DebugP_log("Core[%d]: Test case ID = %d completed with result = %d\r\n", IpcNotify_getSelfCoreId(), testCaseId, status);
            }

            testCaseFound = 1;
            break;
        }
    }

    if (!testCaseFound)
    {
        DebugP_log("Core[%d]: Test case ID = %d not found\r\n", IpcNotify_getSelfCoreId(), testCaseId);
    }

    return status;
}

/**
 * @brief Executes a test case on all participating cores and checks results.
 *
 * @param args Pointer to the test case ID
 */
static void TestUtils_executeTestCase(void* args)
{
    int32_t status = SystemP_FAILURE;
    int32_t testStatus = SystemP_FAILURE;
    uint32_t testCaseId = *((int32_t *)args);
    uint32_t i;
    uint64_t waitCount = 0;

    TestCaseCount = 0;
    TestResultCounter = 0;

    for(i=0; gRemoteCoreId[i]!=CSL_CORE_ID_MAX; i++)
    {
        if(gRemoteCoreId[i] != IpcNotify_getSelfCoreId())
        {
#if TEST_ENABLE_SYSTEM_DEBUG == 1
            if (testCaseId == TEST_DEBUG_TC_ID)
            {
                /* wait here till user sets the variable from CCS */
                while (waitForUserTrigger == 0)
                {
                    ClockP_usleep(TEST_WAIT_CYCLE_TIME);
                }
            }
#endif
            /* send test case ID to all participating core's, wait for message to be put in HW FIFO */
            status = IpcNotify_sendMsg(gRemoteCoreId[i], REMOTE_CLIENT_ID, testCaseId, 1);
            DebugP_assert(SystemP_SUCCESS == status);
            DebugP_log("Sent test case ID = %d to core ID = %d\r\n", testCaseId, gRemoteCoreId[i]);
            TestCaseCount++;
        }
    }

    /* For local run on main core */
    testStatus = TestUtils_testCase(testCaseId, args);

    /* Wait for completion of all test cases */
    while (TestResultCounter < TestCaseCount)
    {
        ClockP_usleep(TEST_WAIT_CYCLE_TIME);
        waitCount++;

        if (waitCount >= TEST_MAX_EXECUTION_TIME)
        {
            status = SystemP_TIMEOUT;
            break;
        }
    }

    if (status == SystemP_TIMEOUT)
    {
        DebugP_log("Timed out waiting for test case results. Received %d of %d expected results\r\n",
                    TestResultCounter, TestCaseCount);

        for (i = 0; i < TestResultCounter; i++)
        {
            uint32_t tcId = GET_TC_ID(TestResult[i]);
            uint32_t tcCore = GET_CORE_ID(TestResult[i]);
            uint32_t tcResult = GET_TC_RESULT(TestResult[i]);

            DebugP_log("Received Test case ID = %d, core ID = %d, result = %d\r\n", tcId, tcCore, tcResult);
        }
    }

    if (status == SystemP_SUCCESS)
    {
        /* Check the test results */
        for (i = 0; i < TestResultCounter; i++)
        {
            uint32_t tcId = GET_TC_ID(TestResult[i]);
            uint32_t tcCore = GET_CORE_ID(TestResult[i]);
            uint32_t tcResult = GET_TC_RESULT(TestResult[i]);

            DebugP_log("Test case ID = %d, core ID = %d, result = %d\r\n", tcId, tcCore, tcResult);

            if (tcId != testCaseId)
            {
                /* test case ID mismatch */
                status = SystemP_FAILURE;
            }

            if (tcResult != SystemP_SUCCESS)
            {
                /* test case failed on remote core */
                status = SystemP_FAILURE;
            }
        }
    }

    /* Test case run in the main core failed */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, testStatus);

    /* Overall test failure */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}

/**
 * @brief Entry point for remote cores to receive and execute test cases.
 */
static void TestUtils_ipcRemoteCoreStart()
{
    volatile int32_t status = SystemP_FAILURE;
    volatile int32_t testResult = 0;

    TestCaseId = 0;

    /* Wait for all cores to be ready/reach here */
    IpcNotify_syncAll(SystemP_WAIT_FOREVER);

    while (1)
    {
        while (TestCaseId == 0)
        {
            /* wait for test case ID from main core */
            ClockP_usleep(TEST_WAIT_CYCLE_TIME);
        }

        /* Remote run */
        status = TestUtils_testCase(TestCaseId,  (void*)&TestCaseId);

        testResult = PACK_RESULT(IpcNotify_getSelfCoreId(), TestCaseId, status);

        /* Send test result to main core */
        IpcNotify_sendMsg(MAIN_CORE_ID, MASTER_CLIENT_ID , testResult, 1);

        TestCaseId = 0;
    }
}

/**
 * @brief Entry point for the main core to run all test cases and collect results.
 */
static void TestUtils_ipcMainCoreStart()
{
    int i= 0;

    /* Wait for all cores to be ready/reach here */
    IpcNotify_syncAll(SystemP_WAIT_FOREVER);

    UNITY_BEGIN();

    for (i = 0; gTestCase[i].testFptr != NULL; i++)
    {
        RUN_TEST(TestUtils_executeTestCase, gTestCase[i].testCaseId, (void*)&gTestCase[i].testCaseId);
    }

    UNITY_END();
}


