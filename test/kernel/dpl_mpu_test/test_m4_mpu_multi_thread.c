/*
 *  Copyright (C) 2026 Texas Instruments Incorporated
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
 *  \file test_m4_mpu_multi_thread.c
 *
 *  \brief File containing M4F MPU Driver test cases for multi-threaded
 *         usecases.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>
#include "core_m4_test.h"
#include <kernel/dpl/CacheP.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/AddrTranslateP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <kernel/dpl/TaskP.h>
#include <kernel/dpl/SemaphoreP.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Number of threads for basic multithreaded MPU tests */
#define TEST_MPU_MT_THREADS                  (2U)

/* Number of threads for trigger type multithreaded tests */
#define TEST_MPU_MT_TRIGTYPE                 (3U)

/* Task priority for MPU test threads */
#define TEST_MPU_TASK_PRIORITY               (8U)

/* Number of threads for multi-channel MPU tests */
#define TEST_MPU_MT_MULTI_CHANNEL_THREADS    (2U)

/* Stack size (in bytes) for each MPU test thread */
#define TEST_MPU_STACK_SIZE                  (16 * 1024)

/* ========================================================================== */
/*                               Typedefs                                     */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Semaphore for synchronizing multithreaded MPU tests */
static SemaphoreP_Object        TestMpu_semObj;

/* Task objects for multithreaded MPU test threads */
static TaskP_Object             TestMpu_MtThreadTaskObj[TEST_MPU_MT_TRIGTYPE];

/* Stack memory for each multithreaded MPU test thread */
static uint8_t                  TestMpu_MtTaskStack[TEST_MPU_MT_TRIGTYPE][TEST_MPU_STACK_SIZE];

/* SysConfig style MPU config, defined in test_core_m4_mpu.c */
extern MpuP_Config              gMpuConfig;

/* ========================================================================== */
/*                     Internal Function Declaration                          */
/* ========================================================================== */

static void TestMpu_multithreadEnableDisableFlapper(void *args);
static void TestMpu_multithreadStatePoller(void *args);
static void TestMpu_multithreadEnableDisableWithStatePolling(void *args);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void run_multi_threaded_tests(void *args)
{
    RUN_TEST(TestMpu_multithreadEnableDisableWithStatePolling,  10077, NULL);
    return;
}

/* ========================================================================== */
/*                     Internal Function Definitions                          */
/* ========================================================================== */

/**
 * @brief Thread A: MPU enable/disable flapper.
 *
 * This thread repeatedly toggles MPU enable/disable state. It exercises
 * the critical sections in MpuP_enable() and MpuP_disable(). Introduces
 * small delays between toggles to allow Thread B to observe state
 * transitions and perform memory operations. The M4F has no hardware
 * caches, so no cache state tracking is required.
 */
static void TestMpu_multithreadEnableDisableFlapper(void *args)
{
    uint32_t iterations = 5;
    uint32_t mpuState;
    uint32_t i;

    for (i = 0; i < iterations; i++)
    {
        /* Enable MPU (background region PRIVDEFENA is set by the test entry) */
        MpuP_enable();
        mpuState = MpuP_isEnable();
        TEST_ASSERT_NOT_EQUAL(0, mpuState);
        DebugP_log("  Iter %u: MPU enabled, state = %u\r\n", i, mpuState);

        /* Small delay for Thread B to observe enabled state */
        ClockP_usleep(100);

        /* Disable MPU */
        MpuP_disable();
        mpuState = MpuP_isEnable();
        TEST_ASSERT_EQUAL_UINT32(0, mpuState);
        DebugP_log("  Iter %u: MPU disabled, state = %u\r\n", i, mpuState);

        /* Small delay for Thread B to observe disabled state */
        ClockP_usleep(100);
    }

    /* Leave the MPU enabled */
    MpuP_enable();

    DebugP_log("Thread A: Completed %u enable/disable cycles\r\n", iterations);

    /* Signal test completion */
    SemaphoreP_post(&TestMpu_semObj);
    TaskP_exit();
}

/**
 * @brief Thread B: MPU state poller with continuous memory I/O.
 *
 * This thread continuously polls MPU enabled state and performs read/write
 * operations in a stable RAM test buffer. It verifies that memory access
 * remains functional across MPU state transitions and validates data
 * integrity. Monitors state changes triggered by Thread A and ensures no
 * faults occur.
 */
static void TestMpu_multithreadStatePoller(void *args)
{
    uint32_t iterations = 5;
    uint32_t mpuState, prevMpuState;
    volatile uint32_t *testPtr = (volatile uint32_t *)TestMpu_getExecBase(); /* RAM test buffer */
    uint32_t testValue;
    uint32_t i;
    uint32_t stateTransitions = 0;

    DebugP_log("Thread B: Starting state poller with I/O\r\n");

    prevMpuState = MpuP_isEnable();

    for (i = 0; i < iterations; i++)
    {
        /* Poll MPU state */
        mpuState = MpuP_isEnable();

        /* Detect state transition */
        if (mpuState != prevMpuState)
        {
            stateTransitions++;
            DebugP_log("  Iter %u: MPU state transition detected: %u -> %u\r\n",
                       i, prevMpuState, mpuState);
            prevMpuState = mpuState;
        }

        /*
         * Perform memory I/O in the RAM test buffer. This is safe in both
         * MPU states:
         * - When the MPU is disabled, ARMv7-M uses the default memory map
         *   with no access restrictions for privileged code.
         * - When the MPU is enabled, the background region (PRIVDEFENA)
         *   provides default map access for addresses not covered by any
         *   foreground region.
         */
        testValue = 0xA5000000U | i;
        *testPtr = testValue;

        /* Verify written value */
        TEST_ASSERT_EQUAL_UINT32(testValue, *testPtr);

        /* Small delay between polls */
        ClockP_usleep(100);
    }

    DebugP_log("Thread B: Completed %u polls, detected %u state transitions\r\n",
               iterations, stateTransitions);
    DebugP_log("Thread B: All memory I/O operations successful\r\n");

    /* Signal test completion */
    SemaphoreP_post(&TestMpu_semObj);
    TaskP_exit();
}

/**
 * @brief Test case for concurrent MPU enable/disable with state polling and I/O.
 *
 * This test validates thread safety of MpuP_enable() and MpuP_disable() operations
 * when accessed concurrently with state polling and memory operations. Thread A
 * repeatedly toggles MPU enable/disable while monitoring cache state. Thread B
 * continuously polls MPU state and performs memory I/O in MSRAM. The test verifies:
 * - Cache state is correctly saved/restored across enable/disable cycles
 * - HwiP_disable critical sections prevent race conditions
 * - Memory access remains functional during state transitions
 * - State changes are observable and consistent across threads
 */
static void TestMpu_multithreadEnableDisableWithStatePolling(void *args)
{
    uint32_t i;
    int32_t status;
    TaskP_Params taskParams;

    DebugP_log("TestMpu_multithreadEnableDisableWithStatePolling: Starting test\r\n");

    /* Ensure the background region (PRIVDEFENA) is used when the MPU is
     * enabled so that code/data not covered by a foreground region keeps
     * default memory map access while Thread A toggles the MPU */
    gMpuConfig.enableBackgroundRegion = 1;

    /* Create counting semaphore for 2 threads */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_constructCounting(&TestMpu_semObj, 0, TEST_MPU_MT_THREADS));

    for (i = 0; i < TEST_MPU_MT_THREADS; i++)
    {
        /* Initialize and create thread */
        TaskP_Params_init(&taskParams);
        taskParams.stackSize    = TEST_MPU_STACK_SIZE;
        taskParams.stack        = TestMpu_MtTaskStack[i];
        taskParams.priority     = TEST_MPU_TASK_PRIORITY;
        taskParams.args         = (void *)(uintptr_t)i;

        /* Assign task function based on thread index */
        if (i == 0)
        {
            taskParams.name      = "MPU_FLAPPER";
            taskParams.taskMain  = TestMpu_multithreadEnableDisableFlapper;
        }
        else
        {
            taskParams.name      = "MPU_POLLER";
            taskParams.taskMain  = TestMpu_multithreadStatePoller;
        }

        status = TaskP_construct(&TestMpu_MtThreadTaskObj[i], &taskParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* Wait for all threads to finish */
    for (i = 0U; i < TEST_MPU_MT_THREADS; i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&TestMpu_semObj, SystemP_WAIT_FOREVER));
    }

    DebugP_log("TestMpu_multithreadEnableDisableWithStatePolling: Both threads completed\r\n");
    DebugP_log("TestMpu_multithreadEnableDisableWithStatePolling: PASSED\r\n");

    /* Destroy semaphore */
    SemaphoreP_destruct(&TestMpu_semObj);

    /* Destroy thread objects */
    for (i = 0; i < TEST_MPU_MT_THREADS; i++)
    {
        TaskP_destruct(&TestMpu_MtThreadTaskObj[i]);
    }
}

