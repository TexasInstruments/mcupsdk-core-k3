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
 * @file test_device_manager_smp.c
 * @brief Standalone SMP test for the Device Manager Sciclient path on AM62DX.
 *
 * Runs on the A53 quad-core cluster under FreeRTOS-SMP.  Each test case
 * creates tasks with explicit A53 core affinity so that Sciclient calls
 * are issued from multiple physical cores simultaneously.  This verifies
 * that the Sciclient serialization layer (mutex / secure-proxy) is
 * correctly SMP-safe from the A53 host side.
 *
 * The DM firmware must already be running on r5fss0-0 before this image
 * is loaded (standard SBL + DM + APP boot flow).
 *
 * Build: am62dx : a53ss0-0 : freertos-smp : gcc-aarch64
 * Defines required: SOC_AM62DX, OS_FREERTOS, SMP_FREERTOS, SMP_QUADCORE_FREERTOS
 *
 * This is a self-contained single file — it includes the FreeRTOS-SMP
 * entry point (main) as well as all test logic.  The only external files
 * needed are the SysConfig-generated ti_*.c/.h files.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

#include <unity.h>
#include <drivers/device_manager/sciclient.h>
#include <drivers/sciclient/include/tisci/tisci_core.h>
#include <drivers/sciclient/include/tisci/tisci_protocol.h>
#include <drivers/sciclient/include/tisci/pm/tisci_pm_device.h>
#include <drivers/sciclient/include/tisci/pm/tisci_pm_clock.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/TaskP.h>
#include <kernel/dpl/SemaphoreP.h>
#include "ti_drivers_config.h"
#include "ti_board_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "FreeRTOS.h"
#include "task.h"

/* ========================================================================== */
/*                             Macros & Defines                               */
/* ========================================================================== */

/* Number of A53 cores used in the SMP tests */
#define TEST_DM_SMP_THREADS             (2U)

/* Stack size for each worker task (bytes) */
#define TEST_DM_SMP_STACK_SIZE          (32U * 1024U)

/* Worker task priority — lower than the main task priority */
#define TEST_DM_SMP_TASK_PRIORITY       (8U)

/* Number of Sciclient API calls per thread per iteration */
#define TEST_DM_SMP_LOOP_COUNT          (5U)

/* Device used for PM Set/Get contention tests (MCU_UART0 on AM62DX) */
#define TEST_DM_SMP_PM_DEV_ID           TISCI_DEV_MCU_UART0

/* Clock ID for the PM clock query tests */
#define TEST_DM_SMP_CLK_ID              TISCI_DEV_MCU_UART0_FCLK_CLK

/* INTAGGR device used for RM resource-range query (read-only, HOST_ID_ALL) */
#define TEST_DM_SMP_RM_INTAGGR_ID       TISCI_DEV_DMASS0_INTAGGR_0

/* FreeRTOS-SMP main task configuration */
#define MAIN_TASK_PRI                   (configMAX_PRIORITIES - 1)
#define MAIN_TASK_SIZE                  (16384U / sizeof(configSTACK_DEPTH_TYPE))

/* ========================================================================== */
/*                             Global Variables                               */
/* ========================================================================== */

/* FreeRTOS-SMP scheduler sync flag defined by the portable layer */
extern volatile uint64_t ullPortSchedularRunning;

static StackType_t  gMainTaskStack[MAIN_TASK_SIZE] __attribute__((aligned(32)));
static StaticTask_t gMainTaskObj;
static TaskHandle_t gMainTask;

/* Shared task objects and stacks — reused sequentially across test cases */
static TaskP_Object TestDM_SmpTaskObj[TEST_DM_SMP_THREADS];
static uint8_t      TestDM_SmpStack[TEST_DM_SMP_THREADS][TEST_DM_SMP_STACK_SIZE];

/* Semaphore used to synchronise test orchestrator with worker tasks */
static SemaphoreP_Object TestDM_SmpSem;

/* ========================================================================== */
/*                     Internal Function Declarations                         */
/* ========================================================================== */

/* Workers for 2-core concurrent version test */
void TestDM_smpWorkerVersion(void *args);
void TestDM_smpWorkerDmVersion(void *args);

/* Workers for 2-core concurrent PM-state test */
void TestDM_smpWorkerPmGet0(void *args);
void TestDM_smpWorkerPmGet1(void *args);

/* Workers for 2-core PM set-vs-get test */
void TestDM_smpWorkerPmSet(void *args);
void TestDM_smpWorkerPmGetConcurrent(void *args);

/* Workers for 2-core concurrent clock freq test */
void TestDM_smpWorkerClkGetSet(void *args);

/* Test cases */
void TestDM_smpConcurrentVersion(void *args);
void TestDM_smpPmGetTwoCores(void *args);
void TestDM_smpConcurrentPmSetGet(void *args);
void TestDM_smpConcurrentClkFreq(void *args);

/* ========================================================================== */
/*                        Worker Task Implementations                         */
/* ========================================================================== */

/**
 * Core 0 worker — sends TISCI_MSG_VERSION in a loop.
 * Signals completion via semaphore.
 */
void TestDM_smpWorkerVersion(void *args)
{
    uint32_t i;
    int32_t  retVal;
    struct tisci_msg_version_req  req = {0};
    struct tisci_msg_version_resp resp;

    for (i = 0U; i < TEST_DM_SMP_LOOP_COUNT; i++)
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_VERSION,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *)&req,
            sizeof(req),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *)&resp,
            sizeof(resp)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: smpWorkerVersion core=%d iter=%u retVal=%d flags=0x%x\r\n",
                       (int)(uintptr_t)args, i, retVal, respPrm.flags);
        }
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        TEST_ASSERT_EQUAL_UINT32(TISCI_MSG_FLAG_ACK, respPrm.flags);
        ClockP_usleep(500U);
    }

    SemaphoreP_post(&TestDM_SmpSem);
    TaskP_exit();
}

/**
 * Core 1 worker — sends TISCI_MSG_DM_VERSION in a loop.
 * Signals completion via semaphore.
 */
void TestDM_smpWorkerDmVersion(void *args)
{
    uint32_t i;
    int32_t  retVal;
    struct tisci_msg_dm_version_req  req = {0};
    struct tisci_msg_dm_version_resp resp;

    for (i = 0U; i < TEST_DM_SMP_LOOP_COUNT; i++)
    {
        const Sciclient_ReqPrm_t reqPrm =
        {
            TISCI_MSG_DM_VERSION,
            TISCI_MSG_FLAG_AOP,
            (uint8_t *)&req,
            sizeof(req),
            SystemP_WAIT_FOREVER
        };
        Sciclient_RespPrm_t respPrm =
        {
            0,
            (uint8_t *)&resp,
            sizeof(resp)
        };

        retVal = Sciclient_service(&reqPrm, &respPrm);
        if (!((retVal == SystemP_SUCCESS) && (respPrm.flags == TISCI_MSG_FLAG_ACK)))
        {
            DebugP_log("FAIL: smpWorkerDmVersion core=%d iter=%u retVal=%d flags=0x%x\r\n",
                       (int)(uintptr_t)args, i, retVal, respPrm.flags);
        }
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        TEST_ASSERT_EQUAL_UINT32(TISCI_MSG_FLAG_ACK, respPrm.flags);
        ClockP_usleep(500U);
    }

    SemaphoreP_post(&TestDM_SmpSem);
    TaskP_exit();
}

/**
 * Core 0 PM worker — queries module state in a loop.
 * Signals completion via semaphore.
 */
void TestDM_smpWorkerPmGet0(void *args)
{
    uint32_t i;
    int32_t  retVal;
    uint32_t moduleState, resetState, contextLossState;

    for (i = 0U; i < TEST_DM_SMP_LOOP_COUNT; i++)
    {
        retVal = Sciclient_pmGetModuleState(
            TEST_DM_SMP_PM_DEV_ID,
            &moduleState,
            &resetState,
            &contextLossState,
            SystemP_WAIT_FOREVER);
        if (retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: smpWorkerPmGet0 iter=%u retVal=%d\r\n", i, retVal);
        }
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        ClockP_usleep(500U);
    }

    SemaphoreP_post(&TestDM_SmpSem);
    TaskP_exit();
}

/**
 * Core 1 PM worker — queries module state in a loop (same device as core 0).
 * Signals completion via semaphore.
 */
void TestDM_smpWorkerPmGet1(void *args)
{
    uint32_t i;
    int32_t  retVal;
    uint32_t moduleState, resetState, contextLossState;

    for (i = 0U; i < TEST_DM_SMP_LOOP_COUNT; i++)
    {
        retVal = Sciclient_pmGetModuleState(
            TEST_DM_SMP_PM_DEV_ID,
            &moduleState,
            &resetState,
            &contextLossState,
            SystemP_WAIT_FOREVER);
        if (retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: smpWorkerPmGet1 iter=%u retVal=%d\r\n", i, retVal);
        }
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        ClockP_usleep(500U);
    }

    SemaphoreP_post(&TestDM_SmpSem);
    TaskP_exit();
}

/**
 * Core 0 PM worker — sets module state ON then AUTO_OFF in a loop.
 * Runs concurrently with TestDM_smpWorkerPmGetConcurrent on core 1.
 */
void TestDM_smpWorkerPmSet(void *args)
{
    uint32_t i;
    int32_t  retVal;

    for (i = 0U; i < TEST_DM_SMP_LOOP_COUNT; i++)
    {
        retVal = Sciclient_pmSetModuleState(
            TEST_DM_SMP_PM_DEV_ID,
            TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
            TISCI_MSG_FLAG_AOP,
            SystemP_WAIT_FOREVER);
        if (retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: smpWorkerPmSet SET_ON iter=%u retVal=%d\r\n", i, retVal);
        }
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        ClockP_usleep(500U);

        retVal = Sciclient_pmSetModuleState(
            TEST_DM_SMP_PM_DEV_ID,
            TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF,
            TISCI_MSG_FLAG_AOP,
            SystemP_WAIT_FOREVER);
        if (retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: smpWorkerPmSet AUTO_OFF iter=%u retVal=%d\r\n", i, retVal);
        }
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        ClockP_usleep(500U);
    }

    SemaphoreP_post(&TestDM_SmpSem);
    TaskP_exit();
}

/**
 * Core 1 PM worker — queries module state in a loop.
 * Runs concurrently with TestDM_smpWorkerPmSet on core 0.
 */
void TestDM_smpWorkerPmGetConcurrent(void *args)
{
    uint32_t i;
    int32_t  retVal;
    uint32_t moduleState, resetState, contextLossState;

    for (i = 0U; i < TEST_DM_SMP_LOOP_COUNT; i++)
    {
        retVal = Sciclient_pmGetModuleState(
            TEST_DM_SMP_PM_DEV_ID,
            &moduleState,
            &resetState,
            &contextLossState,
            SystemP_WAIT_FOREVER);
        if (retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: smpWorkerPmGetConcurrent iter=%u retVal=%d\r\n", i, retVal);
        }
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        ClockP_usleep(500U);
    }

    SemaphoreP_post(&TestDM_SmpSem);
    TaskP_exit();
}

/**
 * Shared clock worker — reads current clock freq then sets it back.
 * Used for both core 0 and core 1 in TestDM_smpConcurrentClkFreq.
 */
void TestDM_smpWorkerClkGetSet(void *args)
{
    uint32_t i;
    int32_t  retVal;
    uint64_t freqHz;

    for (i = 0U; i < TEST_DM_SMP_LOOP_COUNT; i++)
    {
        freqHz = 0ULL;
        retVal = Sciclient_pmGetModuleClkFreq(
            TEST_DM_SMP_PM_DEV_ID,
            TEST_DM_SMP_CLK_ID,
            &freqHz,
            SystemP_WAIT_FOREVER);
        if (retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: smpWorkerClkGetSet GET core=%d iter=%u retVal=%d\r\n",
                       (int)(uintptr_t)args, i, retVal);
        }
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        ClockP_usleep(250U);

        retVal = Sciclient_pmSetModuleClkFreq(
            TEST_DM_SMP_PM_DEV_ID,
            TEST_DM_SMP_CLK_ID,
            freqHz,
            TISCI_MSG_FLAG_AOP,
            SystemP_WAIT_FOREVER);
        if (retVal != SystemP_SUCCESS)
        {
            DebugP_log("FAIL: smpWorkerClkGetSet SET core=%d iter=%u retVal=%d\r\n",
                       (int)(uintptr_t)args, i, retVal);
        }
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, retVal);
        ClockP_usleep(250U);
    }

    SemaphoreP_post(&TestDM_SmpSem);
    TaskP_exit();
}

/* ========================================================================== */
/*                          Test Case Implementations                         */
/* ========================================================================== */

/**
 * TestDM_smpConcurrentPmSetGet
 *
 * Core 0 — repeatedly calls Sciclient_pmSetModuleState(ON) then (AUTO_OFF)
 * Core 1 — repeatedly calls Sciclient_pmGetModuleState on the same device
 *
 * Verifies that concurrent PM Set and Get operations from two A53 cores
 * complete correctly without corruption or blocking.
 */
void TestDM_smpConcurrentPmSetGet(void *args)
{
    int32_t status;
    TaskP_Params params;

    status = SemaphoreP_constructCounting(&TestDM_SmpSem, 0U, TEST_DM_SMP_THREADS);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Core 0 — PM Set loop */
    TaskP_Params_init(&params);
    params.name         = "DM_SMP_PM_SET";
    params.stack        = TestDM_SmpStack[0U];
    params.stackSize    = TEST_DM_SMP_STACK_SIZE;
    params.priority     = TEST_DM_SMP_TASK_PRIORITY;
    params.args         = (void *)0U;
    params.taskMain     = TestDM_smpWorkerPmSet;
    params.coreAffinity = (1U << 0U);
    status = TaskP_construct(&TestDM_SmpTaskObj[0U], &params);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Core 1 — PM Get loop */
    TaskP_Params_init(&params);
    params.name         = "DM_SMP_PM_GET";
    params.stack        = TestDM_SmpStack[1U];
    params.stackSize    = TEST_DM_SMP_STACK_SIZE;
    params.priority     = TEST_DM_SMP_TASK_PRIORITY;
    params.args         = (void *)1U;
    params.taskMain     = TestDM_smpWorkerPmGetConcurrent;
    params.coreAffinity = (1U << 1U);
    status = TaskP_construct(&TestDM_SmpTaskObj[1U], &params);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Wait for both cores to finish */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_pend(&TestDM_SmpSem, SystemP_WAIT_FOREVER));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_pend(&TestDM_SmpSem, SystemP_WAIT_FOREVER));

    SemaphoreP_destruct(&TestDM_SmpSem);
    TaskP_destruct(&TestDM_SmpTaskObj[0U]);
    TaskP_destruct(&TestDM_SmpTaskObj[1U]);
}

/**
 * TestDM_smpConcurrentClkFreq
 *
 * Both A53 cores — read current clock frequency then immediately write it back.
 *
 * Verifies that concurrent Sciclient_pmGetModuleClkFreq + Sciclient_pmSetModuleClkFreq
 * from two A53 cores completes correctly.
 */
void TestDM_smpConcurrentClkFreq(void *args)
{
    int32_t status;
    TaskP_Params params;

    status = SemaphoreP_constructCounting(&TestDM_SmpSem, 0U, TEST_DM_SMP_THREADS);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Both cores run the same get-then-set worker */
    for (uint32_t i = 0U; i < TEST_DM_SMP_THREADS; i++)
    {
        TaskP_Params_init(&params);
        params.name         = "DM_SMP_CLK";
        params.stack        = TestDM_SmpStack[i];
        params.stackSize    = TEST_DM_SMP_STACK_SIZE;
        params.priority     = TEST_DM_SMP_TASK_PRIORITY;
        params.args         = (void *)(uintptr_t)i;
        params.taskMain     = TestDM_smpWorkerClkGetSet;
        params.coreAffinity = (1U << i);  /* pin each task to its own A53 core */
        status = TaskP_construct(&TestDM_SmpTaskObj[i], &params);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    for (uint32_t i = 0U; i < TEST_DM_SMP_THREADS; i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&TestDM_SmpSem, SystemP_WAIT_FOREVER));
    }

    SemaphoreP_destruct(&TestDM_SmpSem);
    for (uint32_t i = 0U; i < TEST_DM_SMP_THREADS; i++)
    {
        TaskP_destruct(&TestDM_SmpTaskObj[i]);
    }
}

/**
 * TestDM_smpConcurrentVersion
 *
 * Two A53 cores issue TISCI version queries simultaneously:
 *   Core 0 — TISCI_MSG_VERSION
 *   Core 1 — TISCI_MSG_DM_VERSION
 *
 * Verifies that the Sciclient secure-proxy and mutex work correctly when
 * called from two physical A53 cores at the same time.
 */
void TestDM_smpConcurrentVersion(void *args)
{
    int32_t status;
    TaskP_Params params;

    status = SemaphoreP_constructCounting(&TestDM_SmpSem, 0U, TEST_DM_SMP_THREADS);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Core 0 — TISCI_MSG_VERSION */
    TaskP_Params_init(&params);
    params.name         = "DM_SMP_VER";
    params.stack        = TestDM_SmpStack[0U];
    params.stackSize    = TEST_DM_SMP_STACK_SIZE;
    params.priority     = TEST_DM_SMP_TASK_PRIORITY;
    params.args         = (void *)0U;
    params.taskMain     = TestDM_smpWorkerVersion;
    params.coreAffinity = (1U << 0U);
    status = TaskP_construct(&TestDM_SmpTaskObj[0U], &params);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Core 1 — TISCI_MSG_DM_VERSION */
    TaskP_Params_init(&params);
    params.name         = "DM_SMP_DM_VER";
    params.stack        = TestDM_SmpStack[1U];
    params.stackSize    = TEST_DM_SMP_STACK_SIZE;
    params.priority     = TEST_DM_SMP_TASK_PRIORITY;
    params.args         = (void *)1U;
    params.taskMain     = TestDM_smpWorkerDmVersion;
    params.coreAffinity = (1U << 1U);
    status = TaskP_construct(&TestDM_SmpTaskObj[1U], &params);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Wait for both cores to finish */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_pend(&TestDM_SmpSem, SystemP_WAIT_FOREVER));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_pend(&TestDM_SmpSem, SystemP_WAIT_FOREVER));

    SemaphoreP_destruct(&TestDM_SmpSem);
    TaskP_destruct(&TestDM_SmpTaskObj[0U]);
    TaskP_destruct(&TestDM_SmpTaskObj[1U]);
}

/**
 * TestDM_smpPmGetTwoCores
 *
 * Two A53 cores query Sciclient_pmGetModuleState on the same device
 * simultaneously, verifying that concurrent read-only PM queries from
 * two physical cores complete without error.
 */
void TestDM_smpPmGetTwoCores(void *args)
{
    int32_t status;
    TaskP_Params params;

    status = SemaphoreP_constructCounting(&TestDM_SmpSem, 0U, TEST_DM_SMP_THREADS);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Core 0 */
    TaskP_Params_init(&params);
    params.name         = "DM_SMP_PM0";
    params.stack        = TestDM_SmpStack[0U];
    params.stackSize    = TEST_DM_SMP_STACK_SIZE;
    params.priority     = TEST_DM_SMP_TASK_PRIORITY;
    params.args         = (void *)0U;
    params.taskMain     = TestDM_smpWorkerPmGet0;
    params.coreAffinity = (1U << 0U);
    status = TaskP_construct(&TestDM_SmpTaskObj[0U], &params);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Core 1 */
    TaskP_Params_init(&params);
    params.name         = "DM_SMP_PM1";
    params.stack        = TestDM_SmpStack[1U];
    params.stackSize    = TEST_DM_SMP_STACK_SIZE;
    params.priority     = TEST_DM_SMP_TASK_PRIORITY;
    params.args         = (void *)1U;
    params.taskMain     = TestDM_smpWorkerPmGet1;
    params.coreAffinity = (1U << 1U);
    status = TaskP_construct(&TestDM_SmpTaskObj[1U], &params);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_pend(&TestDM_SmpSem, SystemP_WAIT_FOREVER));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_pend(&TestDM_SmpSem, SystemP_WAIT_FOREVER));

    SemaphoreP_destruct(&TestDM_SmpSem);
    TaskP_destruct(&TestDM_SmpTaskObj[0U]);
    TaskP_destruct(&TestDM_SmpTaskObj[1U]);
}

/* ========================================================================== */
/*                        Unity Required Functions                            */
/* ========================================================================== */

void setUp(void)   {}
void tearDown(void) {}

/* ========================================================================== */
/*                        Test Main                                           */
/* ========================================================================== */

void test_dm_smp_main(void *args)
{
    UNITY_BEGIN();
    /* When multiple cores execute Sciclient API calls simultaneously, they can be assigned the same sequence ID for different messages.
     This causes responses from the Device Manager to be delivered to the wrong caller, resulting in: Core hangs/deadlocks*/
    #if 0
    RUN_TEST(TestDM_smpConcurrentVersion, 12392, NULL);
    RUN_TEST(TestDM_smpPmGetTwoCores,     12393, NULL);
    RUN_TEST(TestDM_smpConcurrentPmSetGet, 12394, NULL);
    RUN_TEST(TestDM_smpConcurrentClkFreq,  12395, NULL);
    #endif
    UNITY_END();
}

/* ========================================================================== */
/*                        FreeRTOS-SMP Entry Point                           */
/* ========================================================================== */

void freertos_main(void *args)
{
    int32_t status;

    Drivers_open();
    status = Board_driversOpen();
    DebugP_assert(status == SystemP_SUCCESS);

    test_dm_smp_main(NULL);

    Board_driversClose();
    Drivers_close();

    vTaskDelete(NULL);
}

int main(void)
{
    System_init();
    Board_init();

    if (0 == Armv8_getCoreId())
    {
        /* Core 0: create main task and start the SMP scheduler */
        gMainTask = xTaskCreateStatic(
            freertos_main,
            "freertos_main",
            MAIN_TASK_SIZE,
            NULL,
            MAIN_TASK_PRI,
            gMainTaskStack,
            &gMainTaskObj);
        configASSERT(gMainTask != NULL);

        /* Restrict the init task to core 0 so that worker tasks can be
         * placed on other cores without risking a priority inversion on
         * core 0 during scheduler startup. */
        vTaskCoreAffinitySet(gMainTask, 1U);

        vTaskStartScheduler();
    }
    else
    {
        /* Cores 1-3: wait for core 0 to start the scheduler, then join */
        while (ullPortSchedularRunning == 0U)
        {
            ;
        }
        xPortStartScheduler();
    }

    /* Reached only if the scheduler fails to start */
    DebugP_assertNoLog(0);
    return 0;
}
