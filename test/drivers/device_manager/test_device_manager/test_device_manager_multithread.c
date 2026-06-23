/*
 * Copyright (C) 2026 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file test_device_manager_multithread.c
 *
 *  \brief File containing Device Manager test cases for multi-threaded
 *         usecases.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>
#include <drivers/device_manager/sciclient.h>
#include <drivers/sciclient/include/tisci/tisci_core.h>
#include <drivers/sciclient/include/tisci/tisci_protocol.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/TaskP.h>
#include <kernel/dpl/SemaphoreP.h>
#include "FreeRTOS.h"
#include "task.h"
#include "test_device_manager_multithread.h"

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Semaphore for synchronizing multi-threaded DM tests */
static SemaphoreP_Object        TestDM_semObj;

/* Shared task objects and stack pool — all tests run sequentially so memory is reused.
 * Sized for TEST_DM_MT4_THREADS (4) which is the maximum used by any single test. */
static TaskP_Object             TestDM_SharedTaskObj[TEST_DM_MT4_THREADS];
static uint8_t                  TestDM_SharedStack[TEST_DM_MT4_THREADS][TEST_DM_STACK_SIZE];

/* ========================================================================== */
/*                     Internal Function Declarations                         */
/* ========================================================================== */

/* Thread helpers for concurrent version test */
static void TestDM_threadVersionQuery(void *args);
static void TestDM_threadDmVersionQuery(void *args);

/* Thread helpers for concurrent multi-API test */
static void TestDM_threadVersion(void *args);
static void TestDM_threadFwCaps(void *args);
static void TestDM_threadDmVersion(void *args);

/* Thread helpers for PM priority-contention test */
static void TestDM_threadPmSetState(void *args);
static void TestDM_threadPmGetState(void *args);

/* Thread helpers for four-service simultaneous test */
static void TestDM_threadServiceVersion(void *args);
static void TestDM_threadServicePm(void *args);
static void TestDM_threadServiceRm(void *args);
static void TestDM_threadServiceClock(void *args);

/* Thread helpers for concurrent SET API test */
static void TestDM_threadConcurrentSetClk(void *args);

/* Thread helpers for PM+Clock priority-contention test */
static void TestDM_threadPmSetHighPri(void *args);
static void TestDM_threadPmGetLowPri(void *args);

/* Thread helpers for concurrent SET device test */
static void TestDM_threadConcurrentSetDevice(void *args);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* ========================================================================== */
/*                     Internal Function Definitions                          */
/* ========================================================================== */

/**
 * Thread: sends TISCI_MSG_VERSION in a loop and verifies each call succeeds.
 * Signals completion via semaphore.
 */
static void TestDM_threadVersionQuery(void *args)
{
    uint32_t i;
    int32_t retVal;
    struct tisci_msg_version_req  request = {0};
    struct tisci_msg_version_resp response;

   for (i = 0U; i < TEST_DM_LOOP_COUNT; i++)
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_VERSION,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *)&request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *)&response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: TestDM_threadVersionQuery iter=%u retVal=%d flags=0x%x\r\n",
                       i, retVal, respPrm.flags);
        }
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        TEST_ASSERT_EQUAL_UINT32(TISCI_MSG_FLAG_ACK, respPrm.flags);

    }

    SemaphoreP_post(&TestDM_semObj);
    TaskP_exit();
}

/**
 * Thread: sends TISCI_MSG_DM_VERSION in a loop and verifies each call succeeds.
 * Signals completion via semaphore.
 */
static void TestDM_threadDmVersionQuery(void *args)
{
    uint32_t i;
    int32_t retVal;
    struct tisci_msg_dm_version_req  request = {0};
    struct tisci_msg_dm_version_resp response;

   for (i = 0U; i < TEST_DM_LOOP_COUNT; i++)
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_DM_VERSION,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *)&request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *)&response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: TestDM_threadDmVersionQuery iter=%u retVal=%d flags=0x%x\r\n",
                       i, retVal, respPrm.flags);
        }
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        TEST_ASSERT_EQUAL_UINT32(TISCI_MSG_FLAG_ACK, respPrm.flags);
        
    }

    SemaphoreP_post(&TestDM_semObj);
    TaskP_exit();
}

/**
 * Test: two threads concurrently issue TISCI_MSG_VERSION and TISCI_MSG_DM_VERSION
 * to verify thread-safe serialization of the Sciclient message path.
 */
void testDM_multithreadConcurrentVersion(void *args)
{
    uint32_t i;
    int32_t status;
    TaskP_Params taskParams;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_constructCounting(&TestDM_semObj, 0, TEST_DM_MT_THREADS));

   for (i = 0U; i < TEST_DM_MT_THREADS; i++)
    {
        TaskP_Params_init(&taskParams);
        taskParams.name      = "DM_MT_VERSION";
        taskParams.stackSize = TEST_DM_STACK_SIZE;
        taskParams.stack     = TestDM_SharedStack[i];
        taskParams.priority  = TEST_DM_TASK_PRIORITY;
        taskParams.args      = (void *)(uintptr_t)i;

        if (i == 0)
        {
            taskParams.taskMain = TestDM_threadVersionQuery;
        }
        else
        {
            taskParams.taskMain = TestDM_threadDmVersionQuery;
        }

        status = TaskP_construct(&TestDM_SharedTaskObj[i], &taskParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

   for (i = 0U; i < TEST_DM_MT_THREADS; i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_pend(&TestDM_semObj, SystemP_WAIT_FOREVER));
    }

    ClockP_usleep(1000);
    SemaphoreP_destruct(&TestDM_semObj);

   for (i = 0U; i < TEST_DM_MT_THREADS; i++)
    {
        TaskP_destruct(&TestDM_SharedTaskObj[i]);
    }
}

/**
 * Thread: sends TISCI_MSG_VERSION in a loop (used in multi-API concurrent test).
 */
static void TestDM_threadVersion(void *args)
{
    uint32_t i;
    int32_t retVal;
    struct tisci_msg_version_req  request = {0};
    struct tisci_msg_version_resp response;

   for (i = 0U; i < TEST_DM_LOOP_COUNT; i++)
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_VERSION,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *)&request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *)&response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        TEST_ASSERT_EQUAL_UINT32(TISCI_MSG_FLAG_ACK, respPrm.flags);    
    }

    SemaphoreP_post(&TestDM_semObj);
    TaskP_exit();
}

/**
 * Thread: sends TISCI_MSG_QUERY_FW_CAPS in a loop (used in multi-API concurrent test).
 */
static void TestDM_threadFwCaps(void *args)
{
    uint32_t i;
    int32_t retVal;
    struct tisci_query_fw_caps_req  request = {0};
    struct tisci_query_fw_caps_resp response;

   for (i = 0U; i < TEST_DM_LOOP_COUNT; i++)
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_QUERY_FW_CAPS,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *)&request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *)&response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        TEST_ASSERT_EQUAL_UINT32(TISCI_MSG_FLAG_ACK, respPrm.flags);
    }

    SemaphoreP_post(&TestDM_semObj);
    TaskP_exit();
}

/**
 * Thread: sends TISCI_MSG_DM_VERSION in a loop (used in multi-API concurrent test).
 */
static void TestDM_threadDmVersion(void *args)
{
    uint32_t i;
    int32_t retVal;
    struct tisci_msg_dm_version_req  request = {0};
    struct tisci_msg_dm_version_resp response;

   for (i = 0U; i < TEST_DM_LOOP_COUNT; i++)
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_DM_VERSION,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *)&request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *)&response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        TEST_ASSERT_EQUAL_UINT32(TISCI_MSG_FLAG_ACK, respPrm.flags);  
    }

    SemaphoreP_post(&TestDM_semObj);
    TaskP_exit();
}

/**
 * Test: three threads concurrently issue TISCI_MSG_VERSION, TISCI_MSG_QUERY_FW_CAPS,
 * and TISCI_MSG_DM_VERSION to stress the Sciclient serialization under mixed message types.
 */
void testDM_multithreadConcurrentMultiApi(void *args)
{
    uint32_t i;
    int32_t status;
    TaskP_Params taskParams;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_constructCounting(&TestDM_semObj, 0, TEST_DM_MT_MULTIAPI_THREADS));

   for (i = 0U; i < TEST_DM_MT_MULTIAPI_THREADS; i++)
    {
        TaskP_Params_init(&taskParams);
        taskParams.name      = "DM_MT_MULTIAPI";
        taskParams.stackSize = TEST_DM_STACK_SIZE;
        taskParams.stack     = TestDM_SharedStack[i];
        taskParams.priority  = TEST_DM_TASK_PRIORITY;
        taskParams.args      = (void *)(uintptr_t)i;

        if (i == 0)
        {
            taskParams.taskMain = TestDM_threadVersion;
        }
        else if (i == 1)
        {
            taskParams.taskMain = TestDM_threadFwCaps;
        }
        else
        {
            taskParams.taskMain = TestDM_threadDmVersion;
        }

        status = TaskP_construct(&TestDM_SharedTaskObj[i], &taskParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

   for (i = 0U; i < TEST_DM_MT_MULTIAPI_THREADS; i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&TestDM_semObj, SystemP_WAIT_FOREVER));
    }

    ClockP_usleep(1000);
    SemaphoreP_destruct(&TestDM_semObj);

   for (i = 0U; i < TEST_DM_MT_MULTIAPI_THREADS; i++)
    {
        TaskP_destruct(&TestDM_SharedTaskObj[i]);
    }
}

/**
 * High-priority thread: repeatedly sets the module ON then AUTO_OFF.
 * Asserts that every Set call returns SUCCESS — the key invariant under test.
 */
static void TestDM_threadPmSetState(void *args)
{
    uint32_t i;
    int32_t  retVal;

   for (i = 0U; i < TEST_DM_LOOP_COUNT; i++)
    {
        retVal = Sciclient_pmSetModuleState(
            TEST_DM_PM_DEVICE_ID,
            TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
            TISCI_MSG_FLAG_AOP,
            SystemP_WAIT_FOREVER);
        if (retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: TestDM_threadPmSetState SET_ON iter=%u retVal=%d\r\n",
                       i, retVal);
        }
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

        retVal = Sciclient_pmSetModuleState(
            TEST_DM_PM_DEVICE_ID,
            TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF,
            TISCI_MSG_FLAG_AOP,
            SystemP_WAIT_FOREVER);
        if (retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: TestDM_threadPmSetState AUTO_OFF iter=%u retVal=%d\r\n",
                       i, retVal);
        }
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    }

    SemaphoreP_post(&TestDM_semObj);
    TaskP_exit();
}

/**
 * Low-priority thread: repeatedly queries module state.
 * Runs concurrently with the high-priority Set thread.
 */
static void TestDM_threadPmGetState(void *args)
{
    uint32_t i;
    int32_t  retVal;
    uint32_t moduleState, resetState, contextLossState;

   for (i = 0U; i < TEST_DM_LOOP_COUNT; i++)
    {
        retVal = Sciclient_pmGetModuleState(
            TEST_DM_PM_DEVICE_ID,
            &moduleState,
            &resetState,
            &contextLossState,
            SystemP_WAIT_FOREVER);
        if (retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: TestDM_threadPmGetState iter=%u retVal=%d\r\n",
                       i, retVal);
        }
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);  
    }

    SemaphoreP_post(&TestDM_semObj);
    TaskP_exit();
}

/**
 * Test: high-priority thread calls Sciclient_pmSetModuleState while a
 * low-priority thread concurrently calls Sciclient_pmGetModuleState.
 * Verifies that the high-priority Set operation completes without error
 * even under concurrent Get traffic on the same device.
 */
void testDM_pmSetStateHighPriVsGetStateLowPri(void *args)
{
    int32_t      status;
    TaskP_Params taskParams;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_constructCounting(&TestDM_semObj, 0, TEST_DM_MT_PM_THREADS));

    /* Thread 0: high-priority SetModuleState */
    TaskP_Params_init(&taskParams);
    taskParams.name      = "DM_PM_SET";
    taskParams.stackSize = TEST_DM_STACK_SIZE;
    taskParams.stack     = TestDM_SharedStack[0];
    taskParams.priority  = TEST_DM_PM_HI_PRIORITY;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestDM_threadPmSetState;
    status = TaskP_construct(&TestDM_SharedTaskObj[0], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Thread 1: low-priority GetModuleState */
    TaskP_Params_init(&taskParams);
    taskParams.name      = "DM_PM_GET";
    taskParams.stackSize = TEST_DM_STACK_SIZE;
    taskParams.stack     = TestDM_SharedStack[1];
    taskParams.priority  = TEST_DM_PM_LO_PRIORITY;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestDM_threadPmGetState;
    status = TaskP_construct(&TestDM_SharedTaskObj[1], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Wait for both threads to complete */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_pend(&TestDM_semObj, SystemP_WAIT_FOREVER));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_pend(&TestDM_semObj, SystemP_WAIT_FOREVER));
    ClockP_usleep(1000);
    SemaphoreP_destruct(&TestDM_semObj);
    TaskP_destruct(&TestDM_SharedTaskObj[0]);
    TaskP_destruct(&TestDM_SharedTaskObj[1]);
}

/* ========================================================================== */
/* Four-service simultaneous test                                             */
/* ========================================================================== */

/* Thread 0 — Version service: TISCI_MSG_VERSION query. */
static void TestDM_threadServiceVersion(void *args)
{
    uint32_t i;
    int32_t  retVal;
    struct tisci_msg_version_req  request = {0};
    struct tisci_msg_version_resp response;

   for (i = 0U; i < TEST_DM_LOOP_COUNT; i++)
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_VERSION,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *)&request,
            sizeof(request),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *)&response,
            sizeof(response)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: TestDM_threadServiceVersion iter=%u retVal=%d flags=0x%x\r\n",
                       i, retVal, respPrm.flags);
        }
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        TEST_ASSERT_EQUAL_UINT32(TISCI_MSG_FLAG_ACK, respPrm.flags);
    }

    SemaphoreP_post(&TestDM_semObj);
    TaskP_exit();
}

/* Thread 1 — PM service: Sciclient_pmGetModuleState query. */
static void TestDM_threadServicePm(void *args)
{
    uint32_t i;
    int32_t  retVal;
    uint32_t moduleState, resetState, contextLossState;

   for (i = 0U; i < TEST_DM_LOOP_COUNT; i++)
    {
        retVal = Sciclient_pmGetModuleState(
            TEST_DM_PM_DEVICE_ID,
            &moduleState,
            &resetState,
            &contextLossState,
            SystemP_WAIT_FOREVER);
        if (retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: TestDM_threadServicePm iter=%u retVal=%d\r\n",
                       i, retVal);
        }
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        
    }

    SemaphoreP_post(&TestDM_semObj);
    TaskP_exit();
}

/* Thread 2 — RM service: Sciclient_rmGetResourceRange query (read-only). */
static void TestDM_threadServiceRm(void *args)
{
    uint32_t i;
    int32_t  retVal;
    struct tisci_msg_rm_get_resource_range_req  req;
    struct tisci_msg_rm_get_resource_range_resp resp;

   for (i = 0U; i < TEST_DM_LOOP_COUNT; i++)
    {
        memset(&req,  0, sizeof(req));
        memset(&resp, 0, sizeof(resp));
        req.type           = (uint16_t)TEST_DM_MT4_RM_INTAGGR_ID;
        req.subtype        = TISCI_RESASG_SUBTYPE_IA_VINT;
        req.secondary_host = TISCI_HOST_ID_ALL;

        retVal = Sciclient_rmGetResourceRange(&req, &resp, SystemP_WAIT_FOREVER);
        if (retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: TestDM_threadServiceRm iter=%u retVal=%d\r\n",
                       i, retVal);
        }
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    }

    SemaphoreP_post(&TestDM_semObj);
    TaskP_exit();
}

/* Thread 3 — Clock service: Sciclient_pmGetModuleClkFreq query. */
static void TestDM_threadServiceClock(void *args)
{
    uint32_t i;
    int32_t  retVal;
    uint64_t freqHz;

   for (i = 0U; i < TEST_DM_LOOP_COUNT; i++)
    {
        freqHz = 0ULL;
        retVal = Sciclient_pmGetModuleClkFreq(
            TEST_DM_PM_DEVICE_ID,
            TEST_DM_MT4_CLK_ID,
            &freqHz,
            SystemP_WAIT_FOREVER);
        if (retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: TestDM_threadServiceClock iter=%u retVal=%d\r\n",
                       i, retVal);
        }
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        
    }

    SemaphoreP_post(&TestDM_semObj);
    TaskP_exit();
}

/**
 * Test: Version, PM, RM, and Clock service threads run simultaneously.
 * Each thread drives its own service independently for TEST_DM_LOOP_COUNT
 * iterations and asserts that every call succeeds.
 */
void testDM_allServicesSimultaneous(void *args)
{
    uint32_t     i;
    int32_t      status;
    TaskP_Params taskParams;

    static void (*const threadFn[TEST_DM_MT4_THREADS])(void *) =
    {
        TestDM_threadServiceVersion,
        TestDM_threadServicePm,
        TestDM_threadServiceRm,
        TestDM_threadServiceClock,
    };
    static const char *const threadName[TEST_DM_MT4_THREADS] =
    {
        "DM_SVC_VER",
        "DM_SVC_PM",
        "DM_SVC_RM",
        "DM_SVC_CLK",
    };

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_constructCounting(&TestDM_semObj, 0, TEST_DM_MT4_THREADS));

   for (i = 0U; i < TEST_DM_MT4_THREADS; i++)
    {
        TaskP_Params_init(&taskParams);
        taskParams.name      = threadName[i];
        taskParams.stackSize = TEST_DM_STACK_SIZE;
        taskParams.stack     = TestDM_SharedStack[i];
        taskParams.priority  = TEST_DM_TASK_PRIORITY;
        taskParams.args      = (void *)(uintptr_t)i;
        taskParams.taskMain  = threadFn[i];
        status = TaskP_construct(&TestDM_SharedTaskObj[i], &taskParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

   for (i = 0U; i < TEST_DM_MT4_THREADS; i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&TestDM_semObj, SystemP_WAIT_FOREVER));
    }
    ClockP_usleep(1000);
    SemaphoreP_destruct(&TestDM_semObj);

   for (i = 0U; i < TEST_DM_MT4_THREADS; i++)
    {
        TaskP_destruct(&TestDM_SharedTaskObj[i]);
    }
}

/* ========================================================================== */
/* Concurrent SET API test                                                   */
/* ========================================================================== */

/**
 * Thread: reads current clock frequency and sets it back (no-op).
 * Tests Sciclient_pmSetModuleClkFreq thread-safety under concurrent Get+Set pairs.
 * Thread index passed via args (0 or 1, increases with TEST_DM_MT_PMCLK_THREADS).
 */
static void TestDM_threadConcurrentSetClk(void *args)
{
    int32_t  retVal;
    uint64_t clkFreq;
    uintptr_t threadId = (uintptr_t)args;

    clkFreq = 0ULL;
    retVal = Sciclient_pmGetModuleClkFreq(
        TEST_DM_PM_DEVICE_ID,
        TEST_DM_MT4_CLK_ID,
        &clkFreq,
        SystemP_WAIT_FOREVER);
    if (retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: TestDM_threadConcurrentSetClk[%u] GET retVal=%d\r\n",
                   threadId, retVal);
    }
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    retVal = Sciclient_pmSetModuleClkFreq(
        TEST_DM_PM_DEVICE_ID,
        TEST_DM_MT4_CLK_ID,
        clkFreq,
        TISCI_MSG_FLAG_AOP,
        SystemP_WAIT_FOREVER);
    if (retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: TestDM_threadConcurrentSetClk[%u] SET retVal=%d\r\n",
                   threadId, retVal);
    }
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    SemaphoreP_post(&TestDM_semObj);
    TaskP_exit();
}

/**
 * High-priority thread: sets module state.
 * Tests that Set operations complete successfully even under concurrent Get traffic.
 */
static void TestDM_threadPmSetHighPri(void *args)
{
    int32_t  retVal;

    retVal = Sciclient_pmSetModuleState(
        TEST_DM_PM_DEVICE_ID,
        TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
        TISCI_MSG_FLAG_AOP,
        SystemP_WAIT_FOREVER);
    if (retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: TestDM_threadPmSetHighPri PM_SET_ON retVal=%d\r\n", retVal);
    }
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    retVal = Sciclient_pmSetModuleState(
        TEST_DM_PM_DEVICE_ID,
        TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF,
        TISCI_MSG_FLAG_AOP,
        SystemP_WAIT_FOREVER);
    if (retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: TestDM_threadPmSetHighPri PM_SET_AUTO_OFF retVal=%d\r\n", retVal);
    }
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

    SemaphoreP_post(&TestDM_semObj);
    TaskP_exit();
}

/**
 * Low-priority thread: queries module state.
 * Runs concurrently with the high-priority Set thread.
 */
static void TestDM_threadPmGetLowPri(void *args)
{
    int32_t  retVal;
    uint32_t moduleState, resetState, contextLossState;

    retVal = Sciclient_pmGetModuleState(
        TEST_DM_PM_DEVICE_ID,
        &moduleState,
        &resetState,
        &contextLossState,
        SystemP_WAIT_FOREVER);
    if (retVal != SystemP_SUCCESS)
    {
        DebugP_log("FAIL: TestDM_threadPmGetLowPri PM_GET retVal=%d\r\n", retVal);
    }
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    SemaphoreP_post(&TestDM_semObj);
    TaskP_exit();
}

/**
 * Test: two threads concurrently call Sciclient_pmSetModuleClkFreq on the same device.
 * Verifies that concurrent SetClk operations are properly serialized and thread-safe
 * even when issued simultaneously from multiple threads.
 */
void testDM_concurrentSetClock(void *args)
{
    uint32_t i;
    int32_t  status;
    TaskP_Params taskParams;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_constructCounting(&TestDM_semObj, 0, TEST_DM_MT_PMCLK_THREADS));

    /* Create two threads that concurrently set clock frequency */
   for (i = 0U; i < TEST_DM_MT_PMCLK_THREADS; i++)
    {
        TaskP_Params_init(&taskParams);
        taskParams.name      = "DM_SET_CLK";
        taskParams.stackSize = TEST_DM_STACK_SIZE;
        taskParams.stack     = TestDM_SharedStack[i];
        taskParams.priority  = TEST_DM_TASK_PRIORITY;
        taskParams.args      = (void *)(uintptr_t)i;
        taskParams.taskMain  = TestDM_threadConcurrentSetClk;
        status = TaskP_construct(&TestDM_SharedTaskObj[i], &taskParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* Wait for both threads to complete */
   for (i = 0U; i < TEST_DM_MT_PMCLK_THREADS; i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&TestDM_semObj, SystemP_WAIT_FOREVER));
    }
    ClockP_usleep(1000);
    SemaphoreP_destruct(&TestDM_semObj);
   for (i = 0U; i < TEST_DM_MT_PMCLK_THREADS; i++)
    {
        TaskP_destruct(&TestDM_SharedTaskObj[i]);
    }
}

/**
 * Test: high-priority thread calls PM Set while a low-priority thread
 * concurrently calls PM Get on the same device.
 * Verifies that the high-priority Set operations complete without error
 * and that the low-priority Get operations are not corrupted or blocked.
 */
void testDM_pmClkSetHighPriVsGetLowPri(void *args)
{
    int32_t      status;
    TaskP_Params taskParams;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_constructCounting(&TestDM_semObj, 0, TEST_DM_MT_PMCLK_THREADS));

    /* Thread 0: high-priority PM Set */
    TaskP_Params_init(&taskParams);
    taskParams.name      = "DM_PM_SET";
    taskParams.stackSize = TEST_DM_STACK_SIZE;
    taskParams.stack     = TestDM_SharedStack[0];
    taskParams.priority  = TEST_DM_PM_HI_PRIORITY;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestDM_threadPmSetHighPri;
    status = TaskP_construct(&TestDM_SharedTaskObj[0], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Thread 1: low-priority PM Get */
    TaskP_Params_init(&taskParams);
    taskParams.name      = "DM_PM_GET";
    taskParams.stackSize = TEST_DM_STACK_SIZE;
    taskParams.stack     = TestDM_SharedStack[1];
    taskParams.priority  = TEST_DM_PM_LO_PRIORITY;
    taskParams.args      = NULL;
    taskParams.taskMain  = TestDM_threadPmGetLowPri;
    status = TaskP_construct(&TestDM_SharedTaskObj[1], &taskParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Wait for both threads to complete */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_pend(&TestDM_semObj, SystemP_WAIT_FOREVER));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_pend(&TestDM_semObj, SystemP_WAIT_FOREVER));

    ClockP_usleep(1000);
    SemaphoreP_destruct(&TestDM_semObj);
    TaskP_destruct(&TestDM_SharedTaskObj[0]);
    TaskP_destruct(&TestDM_SharedTaskObj[1]);
}


/**
 * Thread: sets device to ON, then AUTO_OFF, repeatedly.
 * Tests Sciclient_pmSetModuleState (SetDevice) thread-safety under concurrent calls.
 * Thread index passed via args (0 or 1, increases with TEST_DM_MT_PMCLK_THREADS).
 */
static void TestDM_threadConcurrentSetDevice(void *args)
{
    uint32_t i;
    int32_t  retVal;
    uintptr_t threadId = (uintptr_t)args;

   for (i = 0U; i < TEST_DM_LOOP_COUNT; i++)
    {
        retVal = Sciclient_pmSetModuleState(
            TEST_DM_PM_DEVICE_ID,
            TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
            TISCI_MSG_FLAG_AOP,
            SystemP_WAIT_FOREVER);
        if (retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: TestDM_threadConcurrentSetDevice[%u] SET_ON iter=%u retVal=%d\r\n",
                       threadId, i, retVal);
        }
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);

        retVal = Sciclient_pmSetModuleState(
            TEST_DM_PM_DEVICE_ID,
            TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF,
            TISCI_MSG_FLAG_AOP,
            SystemP_WAIT_FOREVER);
        if (retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: TestDM_threadConcurrentSetDevice[%u] SET_AUTO_OFF iter=%u retVal=%d\r\n",
                       threadId, i, retVal);
        }
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
    }

    SemaphoreP_post(&TestDM_semObj);
    TaskP_exit();
}

/**
 * Test: two threads concurrently call Sciclient_pmSetModuleState on the same device.
 * Each thread alternates between setting the device to ON and AUTO_OFF state.
 * Verifies that concurrent SetDevice operations are properly serialized and thread-safe
 * even when issued simultaneously from multiple threads on the same device.
 */
void testDM_concurrentSetDevice(void *args)
{
    uint32_t i;
    int32_t  status;
    TaskP_Params taskParams;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_constructCounting(&TestDM_semObj, 0, TEST_DM_MT_PMCLK_THREADS));

    /* Create two threads that concurrently set device state */
   for (i = 0U; i < TEST_DM_MT_PMCLK_THREADS; i++)
    {
        TaskP_Params_init(&taskParams);
        taskParams.name      = "DM_SET_DEVICE";
        taskParams.stackSize = TEST_DM_STACK_SIZE;
        taskParams.stack     = TestDM_SharedStack[i];
        taskParams.priority  = TEST_DM_TASK_PRIORITY;
        taskParams.args      = (void *)(uintptr_t)i;
        taskParams.taskMain  = TestDM_threadConcurrentSetDevice;
        status = TaskP_construct(&TestDM_SharedTaskObj[i], &taskParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* Wait for both threads to complete */
   for (i = 0U; i < TEST_DM_MT_PMCLK_THREADS; i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&TestDM_semObj, SystemP_WAIT_FOREVER));
    }
    ClockP_usleep(1000);
    SemaphoreP_destruct(&TestDM_semObj);
   for (i = 0U; i < TEST_DM_MT_PMCLK_THREADS; i++)
    {
        TaskP_destruct(&TestDM_SharedTaskObj[i]);
    }
}
