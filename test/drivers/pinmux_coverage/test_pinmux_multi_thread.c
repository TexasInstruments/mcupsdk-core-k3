/*
 *  Copyright (C) 2025-2026 Texas Instruments Incorporated
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
 *  \file test_pinmux_multi_thread.c
 *
 *  \brief File containing Pinmux Driver test cases for multi-threaded
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
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/AddrTranslateP.h>
#include <kernel/dpl/TaskP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <drivers/pinmux.h>
#include <drivers/hw_include/cslr.h>
#include <drivers/hw_include/cslr_soc.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* SOC-specific pin and base address definitions */
#if defined(SOC_AM62AX) || defined(SOC_AM62PX) || defined(SOC_AM62X) || defined(SOC_AM62DX)
#define TEST_PINMUX_MT_SPI_CS0          PIN_MCU_SPI0_CS0
#define TEST_PINMUX_MT_OSPI0_CLK        PIN_OSPI0_CLK
#define TEST_PINMUX_MT_OSPI0_D0         PIN_OSPI0_D0
#define TEST_PINMUX_MT_GPIO_PIN         PIN_GPIO0_45
#define TEST_PINMUX_MT_MAIN_BASE        CSL_PADCFG_CTRL0_CFG0_BASE
#define TEST_PINMUX_MT_MCU_BASE         CSL_WKUP_PADCFG_CTRL0_CFG0_BASE
#elif defined(SOC_AM275X)
#define TEST_PINMUX_MT_SPI_CS0          PIN_SPI0_CS0
#define TEST_PINMUX_MT_OSPI0_CLK        PIN_OSPI0_CLK
#define TEST_PINMUX_MT_OSPI0_D0         PIN_OSPI0_D0
#define TEST_PINMUX_MT_GPIO_PIN         PIN_GPIO1_47
#define TEST_PINMUX_MT_MAIN_BASE        CSL_PADCFG_CTRL0_CFG0_BASE
#define TEST_PINMUX_MT_MCU_BASE         CSL_MCU_PADCFG_CTRL0_CFG0_BASE
#endif

/**
 * @brief Offset value for the PADCFG register used in multi-threaded pinmux tests.
 */
#define TEST_PINMUX_MT_PADCFG_OFFSET    (0x4000U)

/* Number of threads for multi-threaded pinmux tests */
#define TEST_PINMUX_MT_THREADS          (2U)

/* Task priority for pinmux test threads */
#define TEST_PINMUX_TASK_PRIORITY       (8U)

/* Stack size (in bytes) for each pinmux test thread */
#define TEST_PINMUX_STACK_SIZE          (16 * 1024)

/* Number of loop iterations per thread */
#define TEST_PINMUX_MT_LOOP_COUNT       (100U)

/* Number of unlock/lock iterations per thread */
#define TEST_PINMUX_MT_LOCK_COUNT       (200U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Semaphore for synchronizing multithreaded pinmux tests */
static SemaphoreP_Object        TestPinmux_semObj;

/* Task objects for multithreaded pinmux test threads */
static TaskP_Object             TestPinmux_MtThreadTaskObj[TEST_PINMUX_MT_THREADS];

/* Stack memory for each multithreaded pinmux test thread */
static uint8_t                  TestPinmux_MtTaskStack[TEST_PINMUX_MT_THREADS][TEST_PINMUX_STACK_SIZE];

/* Error counter for readback validation (used by TC_16) */
static volatile uint32_t        TestPinmux_readerErrorCount = 0U;

/* ========================================================================== */
/*                     Internal Function Declaration                          */
/* ========================================================================== */

static void TestPinmux_multithreadMainMcuConcurrent(void *args);
static void TestPinmux_multithreadUnlockLockConcurrent(void *args);
static void TestPinmux_multithreadSameDomainConfig(void *args);
static void TestPinmux_multithreadConfigAndReadback(void *args);

/* Thread worker functions */
static void TestPinmux_threadConfigMain(void *args);
static void TestPinmux_threadConfigMcu(void *args);
static void TestPinmux_threadUnlockLockMain(void *args);
static void TestPinmux_threadUnlockLockMcu(void *args);
static void TestPinmux_threadConfigPin1(void *args);
static void TestPinmux_threadConfigPin2(void *args);
static void TestPinmux_threadWriter(void *args);
static void TestPinmux_threadReader(void *args);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void run_pinmux_multi_threaded_tests(void *args)
{

    RUN_TEST(TestPinmux_multithreadMainMcuConcurrent, 11244, NULL);
    RUN_TEST(TestPinmux_multithreadUnlockLockConcurrent, 11246, NULL);
    RUN_TEST(TestPinmux_multithreadSameDomainConfig, 11248, NULL);
    RUN_TEST(TestPinmux_multithreadConfigAndReadback, 11250, NULL);

    return;
}

#ifdef SMP_FREERTOS
void test_main(void *args)
{

    UNITY_BEGIN();

    RUN_TEST(TestPinmux_multithreadMainMcuConcurrent, 11245, NULL);
    RUN_TEST(TestPinmux_multithreadSameDomainConfig, 11247, NULL);
    RUN_TEST(TestPinmux_multithreadConfigAndReadback, 11249, NULL);

    UNITY_END();

}

/**
 * @brief Unity test setup hook.
 *
 * Called before each Unity test. Left empty because tests perform their own
 * per-test setup and teardown.
 */
void setUp(void)
{
}

/**
 * @brief Unity test teardown hook.
 *
 * Called after each Unity test. Left empty because tests perform their own
 * per-test cleanup.
 */
void tearDown(void)
{
}
#endif


/* ========================================================================== */
/*                     Internal Function Definitions                          */
/* ========================================================================== */

/**
 * @brief Thread A for TC_13: Configures MAIN domain pin in a loop.
 *
 * This thread repeatedly configures the OSPI0_CLK pin in the MAIN domain
 * using Pinmux_config(). The purpose is to verify that concurrent pinmux
 * operations on different domains (MAIN and MCU) do not interfere with
 * each other. The thread signals completion via a semaphore after all
 * iterations are done.
 */
static void TestPinmux_threadConfigMain(void *args)
{
    uint32_t i;
    Pinmux_PerCfg_t pinCfg[] = {
        { TEST_PINMUX_MT_OSPI0_CLK, PIN_MODE(0) | PIN_INPUT_ENABLE },
        { PINMUX_END, 0 }
    };

    for (i = 0U; i < TEST_PINMUX_MT_LOOP_COUNT; i++)
    {
        Pinmux_config(pinCfg, PINMUX_DOMAIN_ID_MAIN);
    }

    /* Signal test completion */
    SemaphoreP_post(&TestPinmux_semObj);

    TaskP_exit();
}

/**
 * @brief Thread B for TC_13: Configures MCU domain pin in a loop.
 *
 * This thread repeatedly configures the SPI0_CS0 pin in the MCU domain
 * using Pinmux_config(). The goal is to verify that concurrent pinmux
 * operations on different domains (MAIN and MCU) do not interfere with
 * each other. The thread signals completion via a semaphore after all
 * iterations are done.
 */
static void TestPinmux_threadConfigMcu(void *args)
{
    uint32_t i;
    Pinmux_PerCfg_t pinCfg[] = {
        { TEST_PINMUX_MT_SPI_CS0, PIN_MODE(0) | PIN_INPUT_ENABLE },
        { PINMUX_END, 0 }
    };

    for (i = 0U; i < TEST_PINMUX_MT_LOOP_COUNT; i++)
    {
        Pinmux_config(pinCfg, PINMUX_DOMAIN_ID_MCU);
    }

    /* Signal test completion */
    SemaphoreP_post(&TestPinmux_semObj);
    TaskP_exit();
}

/**
 * @brief TC_13: Multi-thread test - Concurrent pinmux config on MAIN and MCU domains.
 *
 * This test launches two threads: one configures a pin in the MAIN domain,
 * and the other configures a pin in the MCU domain, both in a loop.
 * The test ensures that concurrent pinmux operations on different domains
 * do not interfere with each other. After both threads complete, the test
 * verifies that the final register values are as expected for both domains.
 */
static void TestPinmux_multithreadMainMcuConcurrent(void *args)
{
    uint32_t    i;
    int32_t     status;
    uint32_t    baseAddr, readValue;
    TaskP_Params taskParams;

    DebugP_log("\r\n TestPinmux_multithreadMainMcuConcurrent started...\r\n");

    /* Create counting semaphore for threads */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_constructCounting(&TestPinmux_semObj, 0, TEST_PINMUX_MT_THREADS));

    for (i = 0U; i < TEST_PINMUX_MT_THREADS; i++)
    {
        TaskP_Params_init(&taskParams);
        taskParams.name      = "PINMUX_MT_BLOCK";
        taskParams.stackSize = TEST_PINMUX_STACK_SIZE;
        taskParams.stack     = TestPinmux_MtTaskStack[i];
        taskParams.priority  = TEST_PINMUX_TASK_PRIORITY;
        taskParams.args      = (void *)(uintptr_t)i;

        if (i == 0U)
            taskParams.taskMain = TestPinmux_threadConfigMain;
        else
            taskParams.taskMain = TestPinmux_threadConfigMcu;
        #ifdef SMP_FREERTOS
            taskParams.coreAffinity = 1 << i;
        #endif

        status = TaskP_construct(&TestPinmux_MtThreadTaskObj[i], &taskParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* Wait for all threads to finish */
    for (i = 0U; i < TEST_PINMUX_MT_THREADS; i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&TestPinmux_semObj, SystemP_WAIT_FOREVER));
    }

    /* Verify MAIN domain register */
    baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(TEST_PINMUX_MT_MAIN_BASE + TEST_PINMUX_MT_PADCFG_OFFSET);
    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_MT_OSPI0_CLK);
    TEST_ASSERT_EQUAL_UINT32(PIN_MODE(0) | PIN_INPUT_ENABLE, readValue);

    /* Verify MCU domain register */
    baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(TEST_PINMUX_MT_MCU_BASE + TEST_PINMUX_MT_PADCFG_OFFSET);
    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_MT_SPI_CS0);
    TEST_ASSERT_EQUAL_UINT32(PIN_MODE(0) | PIN_INPUT_ENABLE, readValue);

    /* Cleanup */
    SemaphoreP_destruct(&TestPinmux_semObj);
    for (i = 0U; i < TEST_PINMUX_MT_THREADS; i++)
    {
        TaskP_destruct(&TestPinmux_MtThreadTaskObj[i]);
    }

    DebugP_log("TestPinmux_multithreadMainMcuConcurrent: PASS\r\n");
}

/**
 * @brief Thread A for TC_14: Rapid unlock/lock on MAIN domain.
 *
 * This thread repeatedly unlocks and locks the MAIN domain's MMR (Memory Mapped Register)
 * in a tight loop. The purpose is to stress-test the unlock/lock sequence in a multi-threaded
 * environment, ensuring that concurrent unlock/lock operations on different domains do not
 * interfere with each other. After completing all iterations, the thread signals completion
 * using a semaphore.
 */
static void TestPinmux_threadUnlockLockMain(void *args)
{
    uint32_t i;

    for (i = 0U; i < TEST_PINMUX_MT_LOCK_COUNT; i++)
    {
        /* Unlock and lock MAIN domain MMR in each iteration */
        Pinmux_unlockMMR(PINMUX_DOMAIN_ID_MAIN);
        Pinmux_lockMMR(PINMUX_DOMAIN_ID_MAIN);
    }

    /* Signal test completion */
    SemaphoreP_post(&TestPinmux_semObj);
    TaskP_exit();
}

/**
 * @brief Thread B for TC_14: Rapid unlock/lock on MCU domain.
 *
 * This thread repeatedly unlocks and locks the MCU domain's MMR (Memory Mapped Register)
 * in a tight loop. The purpose is to stress-test the unlock/lock sequence in a multi-threaded
 * environment, ensuring that concurrent unlock/lock operations on different domains do not
 * interfere with each other. After completing all iterations, the thread signals completion
 * using a semaphore.
 */
static void TestPinmux_threadUnlockLockMcu(void *args)
{
    uint32_t i;

    for (i = 0U; i < TEST_PINMUX_MT_LOCK_COUNT; i++)
    {
        /* Unlock and lock MCU domain MMR in each iteration */
        Pinmux_unlockMMR(PINMUX_DOMAIN_ID_MCU);
        Pinmux_lockMMR(PINMUX_DOMAIN_ID_MCU);
    }

    /* Signal test completion */
    SemaphoreP_post(&TestPinmux_semObj);
    TaskP_exit();
}

/**
 * @brief TC_14: Multi-thread test - Concurrent unlock/lock on MAIN and MCU domains.
 *
 * This test launches two threads: one repeatedly unlocks/locks the MAIN domain MMR,
 * and the other does the same for the MCU domain. The goal is to stress-test the
 * unlock/lock sequence in a multi-threaded environment and ensure that concurrent
 * unlock/lock operations on different domains do not interfere with each other.
 * After both threads complete, the test verifies that pinmux configuration still
 * works correctly for both domains.
 */
static void TestPinmux_multithreadUnlockLockConcurrent(void *args)
{
    uint32_t    i;
    int32_t     status;
    uint32_t    baseAddr, readValue;
    TaskP_Params taskParams;

    DebugP_log("\r\nTestPinmux_multithreadUnlockLockConcurrent started...\r\n");

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_constructCounting(&TestPinmux_semObj, 0, TEST_PINMUX_MT_THREADS));

    for (i = 0U; i < TEST_PINMUX_MT_THREADS; i++)
    {
        TaskP_Params_init(&taskParams);
        taskParams.name      = "PINMUX_MT_LOCK";
        taskParams.stackSize = TEST_PINMUX_STACK_SIZE;
        taskParams.stack     = TestPinmux_MtTaskStack[i];
        taskParams.priority  = TEST_PINMUX_TASK_PRIORITY;
        taskParams.args      = (void *)(uintptr_t)i;

        if (i == 0U)
            taskParams.taskMain = TestPinmux_threadUnlockLockMain;
        else
            taskParams.taskMain = TestPinmux_threadUnlockLockMcu;

        status = TaskP_construct(&TestPinmux_MtThreadTaskObj[i], &taskParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* Wait for all threads to finish */
    for (i = 0U; i < TEST_PINMUX_MT_THREADS; i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&TestPinmux_semObj, SystemP_WAIT_FOREVER));
    }

    /* Verify MAIN domain config still works */
    Pinmux_PerCfg_t pinCfgMain[] = {
        { TEST_PINMUX_MT_OSPI0_CLK, PIN_MODE(0) | PIN_INPUT_ENABLE },
        { PINMUX_END, 0 }
    };
    Pinmux_config(pinCfgMain, PINMUX_DOMAIN_ID_MAIN);

    baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(TEST_PINMUX_MT_MAIN_BASE + TEST_PINMUX_MT_PADCFG_OFFSET);
    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_MT_OSPI0_CLK);
    TEST_ASSERT_EQUAL_UINT32(PIN_MODE(0) | PIN_INPUT_ENABLE, readValue);

    /* Verify MCU domain config still works */
    Pinmux_PerCfg_t pinCfgMCU[] = {
        { TEST_PINMUX_MT_SPI_CS0, PIN_MODE(0) | PIN_INPUT_ENABLE },
        { PINMUX_END, 0 }
    };
    Pinmux_config(pinCfgMCU, PINMUX_DOMAIN_ID_MCU);

    baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(TEST_PINMUX_MT_MCU_BASE + TEST_PINMUX_MT_PADCFG_OFFSET);
    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_MT_SPI_CS0);
    TEST_ASSERT_EQUAL_UINT32(PIN_MODE(0) | PIN_INPUT_ENABLE, readValue);

    /* Cleanup */
    SemaphoreP_destruct(&TestPinmux_semObj);
    for (i = 0U; i < TEST_PINMUX_MT_THREADS; i++)
    {
        TaskP_destruct(&TestPinmux_MtThreadTaskObj[i]);
    }

    DebugP_log("TestPinmux_multithreadUnlockLockConcurrent: PASS\r\n");
}

/**
 * @brief Thread A for TC_15: Configures OSPI0_CLK in MAIN domain (same domain as Thread B).
 *
 * This thread repeatedly configures the OSPI0_CLK pin in the MAIN domain using Pinmux_config().
 * The purpose is to verify that concurrent pinmux operations on different pins within the same
 * domain do not interfere with each other. This helps ensure that the unlock/config/lock sequence
 * is robust even when multiple threads operate on the same domain's KICK registers. The thread
 * signals completion via a semaphore after all iterations are done.
 */
static void TestPinmux_threadConfigPin1(void *args)
{
    uint32_t i;
    Pinmux_PerCfg_t pinCfg[] = {
        { TEST_PINMUX_MT_OSPI0_CLK, PIN_MODE(0) | PIN_INPUT_ENABLE },
        { PINMUX_END, 0 }
    };

    for (i = 0U; i < TEST_PINMUX_MT_LOOP_COUNT; i++)
    {
        Pinmux_config(pinCfg, PINMUX_DOMAIN_ID_MAIN);
    }

    SemaphoreP_post(&TestPinmux_semObj);
    TaskP_exit();
}

/**
 * @brief Thread B for TC_15: Configures GPIO pin in MAIN domain (different pin from Thread A).
 *
 * This thread repeatedly configures the GPIO pin in the MAIN domain using Pinmux_config().
 * The purpose is to verify that concurrent pinmux operations on different pins within the same
 * domain do not interfere with each other. This helps ensure that the unlock/config/lock sequence
 * is robust even when multiple threads operate on the same domain's KICK registers. The thread
 * signals completion via a semaphore after all iterations are done.
 */
static void TestPinmux_threadConfigPin2(void *args)
{
    uint32_t i;
    Pinmux_PerCfg_t pinCfg[] = {
        { TEST_PINMUX_MT_GPIO_PIN, PIN_MODE(7) | PIN_PULL_DISABLE },
        { PINMUX_END, 0 }
    };

    for (i = 0U; i < TEST_PINMUX_MT_LOOP_COUNT; i++)
    {
        Pinmux_config(pinCfg, PINMUX_DOMAIN_ID_MAIN);
    }

    SemaphoreP_post(&TestPinmux_semObj);
    TaskP_exit();
}

/**
 * @brief TC_15: Multi-thread test - Concurrent pinmux config on different pins in the same domain.
 *
 * This test launches two threads, both configuring different pins (OSPI0_CLK and GPIO) in the MAIN domain
 * in a loop. The goal is to verify that concurrent pinmux operations on different pins within the same domain
 * do not interfere with each other, ensuring the unlock/config/lock sequence is robust even when multiple
 * threads operate on the same domain's KICK registers. After both threads complete, the test verifies that
 * the final register values are as expected for both pins.
 */
static void TestPinmux_multithreadSameDomainConfig(void *args)
{
    uint32_t i;
    int32_t status;
    uint32_t baseAddr, readValue;
    TaskP_Params taskParams;

    DebugP_log("\r\nTestPinmux_multithreadSameDomainConfig started...\r\n");

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_constructCounting(&TestPinmux_semObj, 0, TEST_PINMUX_MT_THREADS));

    for (i = 0U; i < TEST_PINMUX_MT_THREADS; i++)
    {
        TaskP_Params_init(&taskParams);
        taskParams.name      = "PINMUX_MT_SAME";
        taskParams.stackSize = TEST_PINMUX_STACK_SIZE;
        taskParams.stack     = TestPinmux_MtTaskStack[i];
        taskParams.priority  = TEST_PINMUX_TASK_PRIORITY;
        taskParams.args      = (void *)(uintptr_t)i;

        if (i == 0U)
            taskParams.taskMain = TestPinmux_threadConfigPin1;
        else
            taskParams.taskMain = TestPinmux_threadConfigPin2;
        #ifdef SMP_FREERTOS
            taskParams.coreAffinity = 1 << i;
        #endif
        status = TaskP_construct(&TestPinmux_MtThreadTaskObj[i], &taskParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* Wait for all threads to finish */
    for (i = 0U; i < TEST_PINMUX_MT_THREADS; i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&TestPinmux_semObj, SystemP_WAIT_FOREVER));
    }

    /* Verify both pins in MAIN domain */
    baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(TEST_PINMUX_MT_MAIN_BASE + TEST_PINMUX_MT_PADCFG_OFFSET);

    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_MT_OSPI0_CLK);
    TEST_ASSERT_EQUAL_UINT32(PIN_MODE(0) | PIN_INPUT_ENABLE, readValue);

    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_MT_GPIO_PIN);
    TEST_ASSERT_EQUAL_UINT32(PIN_MODE(7) | PIN_PULL_DISABLE, readValue);

    /* Cleanup */
    SemaphoreP_destruct(&TestPinmux_semObj);
    for (i = 0U; i < TEST_PINMUX_MT_THREADS; i++)
    {
        TaskP_destruct(&TestPinmux_MtThreadTaskObj[i]);
    }

    DebugP_log("TestPinmux_multithreadSameDomainConfig: PASS\r\n");
}

/**
 * @brief Writer thread for TC_16: Continuously writes to OSPI0_D0 register.
 *
 * This thread repeatedly configures the OSPI0_D0 pin in the MAIN domain using Pinmux_config().
 * The purpose is to verify that concurrent writes to the same PADCONFIG register do not result
 * in torn or partial writes, and that the register always contains a valid value. This test,
 * when run in parallel with a reader thread, helps ensure atomicity of PADCONFIG register writes.
 * After completing all iterations, the thread signals completion using a semaphore.
 */
static void TestPinmux_threadWriter(void *args)
{
    uint32_t i;
    Pinmux_PerCfg_t pinCfg[] = {
        { TEST_PINMUX_MT_OSPI0_D0, PIN_MODE(0) | PIN_INPUT_ENABLE },
        { PINMUX_END, 0 }
    };

    for (i = 0U; i < TEST_PINMUX_MT_LOCK_COUNT; i++)
    {
        Pinmux_config(pinCfg, PINMUX_DOMAIN_ID_MAIN);
    }

    SemaphoreP_post(&TestPinmux_semObj);
    TaskP_exit();
}

/**
 * @brief Reader thread for TC_16: Continuously reads OSPI0_D0 register.
 *
 * This thread repeatedly reads the OSPI0_D0 pin's PADCONFIG register in the MAIN domain,
 * while another thread is writing to it. The goal is to detect any torn or partial writes
 * by comparing the read value to the expected value. If a mismatch is detected, an error
 * counter is incremented. This test helps ensure that PADCONFIG register writes are atomic
 * and that the reader never observes an invalid or partial value.
 */
static void TestPinmux_threadReader(void *args)
{
    uint32_t i, readValue;
    uint32_t baseAddr;
    uint32_t expectedValue = PIN_MODE(0) | PIN_INPUT_ENABLE;

    baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(TEST_PINMUX_MT_MAIN_BASE + TEST_PINMUX_MT_PADCFG_OFFSET);

    /* First set the pin to the expected value so initial reads are valid */
    Pinmux_PerCfg_t pinCfg[] = {
        { TEST_PINMUX_MT_OSPI0_D0, expectedValue },
        { PINMUX_END, 0 }
    };
    Pinmux_config(pinCfg, PINMUX_DOMAIN_ID_MAIN);

    TestPinmux_readerErrorCount = 0U;

    for (i = 0U; i < TEST_PINMUX_MT_LOCK_COUNT; i++)
    {
        readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_MT_OSPI0_D0);
        /* Increment error count if a torn/invalid value is observed */
        if (readValue != expectedValue)
        {
            TestPinmux_readerErrorCount++;
        }
        ClockP_usleep(10);
    }

    SemaphoreP_post(&TestPinmux_semObj);
    TaskP_exit();
}

/**
 * @brief TC_16: Multi-thread test - Concurrent config and readback of the same PADCONFIG register.
 *
 * This test launches two threads: one continuously writes a known value to the OSPI0_D0 PADCONFIG
 * register in the MAIN domain, while the other thread continuously reads back the same register.
 * The goal is to verify that register writes are atomic and that no torn or partial values are
 * observed by the reader. After both threads complete, the test checks that no read errors were
 * detected and that the final register value matches the expected configuration.
 */
static void TestPinmux_multithreadConfigAndReadback(void *args)
{
    uint32_t    i;
    int32_t     status;
    uint32_t    baseAddr, readValue;
    TaskP_Params taskParams;

    DebugP_log("\r\nTestPinmux_multithreadConfigAndReadback started...\r\n");

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_constructCounting(&TestPinmux_semObj, 0, TEST_PINMUX_MT_THREADS));

    for (i = 0U; i < TEST_PINMUX_MT_THREADS; i++)
    {
        TaskP_Params_init(&taskParams);
        taskParams.name      = "PINMUX_MT_RW";
        taskParams.stackSize = TEST_PINMUX_STACK_SIZE;
        taskParams.stack     = TestPinmux_MtTaskStack[i];
        taskParams.priority  = TEST_PINMUX_TASK_PRIORITY;
        taskParams.args      = (void *)(uintptr_t)i;

        if (i == 0U)
            taskParams.taskMain = TestPinmux_threadWriter;
        else
            taskParams.taskMain = TestPinmux_threadReader;
        #ifdef SMP_FREERTOS
            taskParams.coreAffinity = 1 << i;
        #endif
        status = TaskP_construct(&TestPinmux_MtThreadTaskObj[i], &taskParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* Wait for all threads to finish */
    for (i = 0U; i < TEST_PINMUX_MT_THREADS; i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&TestPinmux_semObj, SystemP_WAIT_FOREVER));
    }

    /* Verify no torn reads were observed */
    TEST_ASSERT_EQUAL_UINT32(0U, TestPinmux_readerErrorCount);

    /* Verify final register value */
    baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(TEST_PINMUX_MT_MAIN_BASE + TEST_PINMUX_MT_PADCFG_OFFSET);
    readValue = CSL_REG32_RD(baseAddr + TEST_PINMUX_MT_OSPI0_D0);
    TEST_ASSERT_EQUAL_UINT32(PIN_MODE(0) | PIN_INPUT_ENABLE, readValue);

    /* Cleanup */
    SemaphoreP_destruct(&TestPinmux_semObj);
    for (i = 0U; i < TEST_PINMUX_MT_THREADS; i++)
    {
        TaskP_destruct(&TestPinmux_MtThreadTaskObj[i]);
    }

    DebugP_log("TestPinmux_multithreadConfigAndReadback: PASS\r\n");
}

