/*
 *  Copyright (C) 2021-2026 Texas Instruments Incorporated
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
 *  \file test_gpio_multi_thread.c
 *
 *  \brief File containing GPIO Driver test cases for multi-threaded
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
#include <drivers/gpio.h>
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

/* Number of threads for basic multithreaded GPIO tests */
#define TEST_GPIO_MT_THREADS                  (2U)

/* Number of threads for trigger type multithreaded tests */
#define TEST_GPIO_MT_TRIGTYPE                 (3U)

/* Task priority for GPIO test threads */
#define TEST_GPIO_TASK_PRIORITY               (8U)

/* Number of threads for multi-channel GPIO tests */
#define TEST_GPIO_MT_MULTI_CHANNEL_THREADS    (2U)

/* Stack size (in bytes) for each GPIO test thread */
#define TEST_GPIO_STACK_SIZE                  (16 * 1024)

/* ========================================================================== */
/*                               Typedefs                                     */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Semaphore for synchronizing multithreaded GPIO tests */
static SemaphoreP_Object        TestGpio_semObj;

/* Task objects for multithreaded GPIO test threads */
static TaskP_Object             TestGpio_MtThreadTaskObj[TEST_GPIO_MT_TRIGTYPE];

/* Stack memory for each multithreaded GPIO test thread */
static uint8_t                  TestGpio_MtTaskStack[TEST_GPIO_MT_TRIGTYPE][TEST_GPIO_STACK_SIZE];

/* ========================================================================== */
/*                     Internal Function Declaration                          */
/* ========================================================================== */

static void TestGpio_multithreadWriteReadPins(void *args);
static void TestGpio_multithreadTrigType(void *args);

/* Multithread helper function declarations */
static void TestGpio_multithreadRead(void *args);
static void TestGpio_multithreadWrite(void *args);
static void TestGpio_multithreadBothTrigType(void *arg);
static void TestGpio_multithreadFallingEdge(void *arg);
static void TestGpio_multithreadRisingEdge(void *arg);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void run_multi_threaded_tests(void *args)
{
    RUN_TEST(TestGpio_multithreadWriteReadPins,  9547, NULL);
    RUN_TEST(TestGpio_multithreadTrigType,  9548, NULL);

    return;
}

#ifdef SMP_FREERTOS
void test_main(void *args)
{

    UNITY_BEGIN();

    RUN_TEST(TestGpio_multithreadWriteReadPins,  9633, NULL);
    #if !defined (SOC_AM62DX)
    RUN_TEST(TestGpio_multithreadTrigType,  9635, NULL);
    #endif

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
 * @brief Test case for GPIO output mode in a multithreaded environment.
 *
 * This function verifies the correct behavior of GPIO pins configured in output mode
 * when accessed from multiple threads concurrently. It ensures that the GPIO driver
 * maintains data integrity and thread safety during simultaneous operations. The test
 * is essential for validating reliable GPIO output functionality in multitasking systems.
 */
static void TestGpio_multithreadWrite(void *args)
{
    uint32_t pinValue,i;
    uint32_t baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(GPIO_LED_BASE_ADDR);
    uint32_t pinNum   = GPIO_LED_PIN;
    uint32_t bankNum  = GPIO_GET_BANK_INDEX(pinNum);

    /* Set pin as output */
    GPIO_setDirMode(baseAddr, pinNum, GPIO_DIRECTION_OUTPUT);

    /* Write high and verify in a loop of 10 */
    for (i = 0; i < 10; i++)
    {
        GPIO_pinWriteHigh(baseAddr, pinNum);
        ClockP_usleep(5000);
        pinValue = GPIO_pinOutValueRead(baseAddr, pinNum);
        TEST_ASSERT_EQUAL_UINT32(GPIO_PIN_HIGH, pinValue);
        DebugP_log("Current GPIO pin value: %d\r\n", pinValue);
        GPIO_pinWriteLow(baseAddr, pinNum);
        /* Optionally, verify pin state after each write */
        pinValue = GPIO_pinOutValueRead(baseAddr, pinNum);
        TEST_ASSERT_EQUAL_UINT32(GPIO_PIN_LOW, pinValue);
        ClockP_usleep(5000);
    }

    /* Cleanup GPIO trigger and interrupt configuration */
    GPIO_setTrigType(baseAddr, pinNum, GPIO_TRIG_TYPE_NONE);
    GPIO_bankIntrDisable(baseAddr, bankNum);
    GPIO_clearIntrStatus(baseAddr, pinNum);
    GPIO_pinWriteLow(baseAddr, pinNum);

    /* Signal test completion */
    SemaphoreP_post(&TestGpio_semObj);

    TaskP_exit();
}

/**
 * @brief Test case for GPIO input mode in a multithreaded environment.
 *
 * This function verifies the correct behavior of GPIO pins configured as inputs
 * when accessed concurrently by multiple threads. It simulates parallel read
 * operations to ensure thread safety and data integrity. The test helps validate
 * the robustness of the GPIO driver under multithreaded conditions.
 */
static void TestGpio_multithreadRead(void *arg)
{
    uint32_t    pinValue,i;
    uint32_t baseAddr = (uint32_t) AddrTranslateP_getLocalAddr(GPIO_PUSH_BUTTON_BASE_ADDR);
    uint32_t pinNum   = GPIO_PUSH_BUTTON_PIN;
    uint32_t bankNum  = GPIO_GET_BANK_INDEX(pinNum);

    GPIO_setDirMode(baseAddr,pinNum, GPIO_DIRECTION_INPUT);

    for (i = 0; i < 10; i++)
    {
        pinValue = GPIO_pinRead(baseAddr , pinNum);
        DebugP_log("Current GPIO pin value: %d\r\n", pinValue);
        ClockP_usleep(1000);
    }

    /* Cleanup GPIO trigger and interrupt configuration */
    GPIO_setTrigType(baseAddr, pinNum, GPIO_TRIG_TYPE_NONE);
    GPIO_bankIntrDisable(baseAddr, bankNum);
    GPIO_clearIntrStatus(baseAddr, pinNum);
    GPIO_pinWriteLow(baseAddr, pinNum);

    /* Signal test completion */
    SemaphoreP_post(&TestGpio_semObj);

    TaskP_exit();
}

/**
 * @brief Test case for multithreaded GPIO pin write and read operations.
 *
 * This function tests the concurrent access of GPIO pins by multiple threads.
 * It writes to and reads from GPIO pins in a multithreaded environment to verify
 * data integrity and thread safety. The test ensures that simultaneous operations
 * on GPIO pins do not cause race conditions or inconsistent states.
 */
static void TestGpio_multithreadWriteReadPins(void *args)
{
    uint32_t i;
    int32_t status;;
    TaskP_Params taskParams;

    /* Create counting semaphore for threads */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_constructCounting(&TestGpio_semObj, 0, TEST_GPIO_MT_THREADS));

    for (i = 0; i < TEST_GPIO_MT_THREADS; i++)
    {
        /* Initialize and create thread */
        TaskP_Params_init(&taskParams);
        taskParams.name         = "GPIO_MT_BLOCK";
        taskParams.stackSize    = TEST_GPIO_STACK_SIZE;
        taskParams.stack        = TestGpio_MtTaskStack[i];
        taskParams.priority     = TEST_GPIO_TASK_PRIORITY;
        taskParams.args         = (void *)(uintptr_t)i;
        /* Assign task function based on thread index */
        if (i == 0)
            taskParams.taskMain = TestGpio_multithreadWrite;
        else
            taskParams.taskMain = TestGpio_multithreadRead;
        #ifdef SMP_FREERTOS
        taskParams.coreAffinity = 1 << i;
        #endif
        status = TaskP_construct(&TestGpio_MtThreadTaskObj[i], &taskParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* Wait for all threads to finish */
    for (i = 0U; i < TEST_GPIO_MT_THREADS; i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&TestGpio_semObj, SystemP_WAIT_FOREVER));
    }

    /* Destroy semaphore */
    SemaphoreP_destruct(&TestGpio_semObj);

    /* Destroy thread objects */
    for (i = 0; i < TEST_GPIO_MT_THREADS; i++)
    {
        TaskP_destruct(&TestGpio_MtThreadTaskObj[i]);
    }
}

/**
 * @brief Test case for GPIO rising edge interrupt handling in a multithreaded context.
 *
 * This function verifies the correct detection and handling of rising edge interrupts
 * on a GPIO pin when accessed from multiple threads. It ensures thread safety and
 * proper synchronization mechanisms are in place during concurrent operations.
 * The test validates that all threads receive the expected interrupt notifications
 * without race conditions or missed events.
 */
static void TestGpio_multithreadRisingEdge(void *arg)
{
    uint32_t baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(GPIO_LED_BASE_ADDR);
    uint32_t pinNum   = GPIO_LED_PIN;
    uint32_t bankNum, loopcnt = 10, count = 0;
    uint32_t intrStatus, pinMask, intrcnt = 0;

    bankNum = GPIO_GET_BANK_INDEX(pinNum);
    pinMask = GPIO_GET_BANK_BIT_MASK(pinNum);

    /* Set pin as output */
    GPIO_setDirMode(baseAddr, pinNum, GPIO_DIRECTION_OUTPUT);

    /* Start with pin low */
    GPIO_pinWriteLow(baseAddr, pinNum);
    ClockP_usleep(1000);

    /* Configure rising edge trigger and enable bank interrupt */
    GPIO_setTrigType(baseAddr, pinNum, GPIO_TRIG_TYPE_RISE_EDGE);
    GPIO_bankIntrEnable(baseAddr, bankNum);

    while (count < loopcnt)
    {
        /* Drive rising edge */
        GPIO_pinWriteHigh(baseAddr, pinNum);
        ClockP_usleep(1000);

        /* Check and clear interrupt status */
        intrStatus = GPIO_getBankIntrStatus(baseAddr, bankNum);
        GPIO_clearBankIntrStatus(baseAddr, bankNum, intrStatus);
        if (intrStatus & pinMask)
        {
            intrcnt++;
        }

        /* Drive low, should not trigger interrupt */
        GPIO_pinWriteLow(baseAddr, pinNum);
        ClockP_usleep(1000);

        /* Confirm no interrupt on falling edge */
        intrStatus = GPIO_getBankIntrStatus(baseAddr, bankNum);
        ClockP_usleep(1000);
        TEST_ASSERT_EQUAL_UINT32(0, (intrStatus & pinMask));
        count++;
    }

    /* Check that all rising edges triggered interrupts */
    TEST_ASSERT_EQUAL_INT32(loopcnt, intrcnt);

    /* Cleanup: disable trigger, disable bank interrupt, clear status, set pin low */
    GPIO_setTrigType(baseAddr, pinNum, GPIO_TRIG_TYPE_NONE);
    GPIO_bankIntrDisable(baseAddr, bankNum);
    GPIO_clearIntrStatus(baseAddr, pinNum);
    GPIO_pinWriteLow(baseAddr, pinNum);

    /* Signal test completion */
    SemaphoreP_post(&TestGpio_semObj);

    TaskP_exit();
}

/**
 * @brief Test case for GPIO falling edge interrupt handling in a multithreaded context.
 *
 * This function simulates a scenario where multiple threads interact with a GPIO pin
 * configured to detect falling edge interrupts. It verifies that the interrupt is
 * correctly triggered and handled when the pin transitions from high to low state.
 * The test ensures thread safety and proper synchronization during concurrent access.
 */
static void TestGpio_multithreadFallingEdge(void *arg)
{
    uint32_t baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(GPIO_I2C_BASE_ADDR);
    uint32_t pinNum   = GPIO_I2C_PIN;
    uint32_t bankNum, loopcnt = 10, count = 0;
    uint32_t intrStatus, pinMask, intrcnt = 0;

    bankNum = GPIO_GET_BANK_INDEX(pinNum);
    pinMask = GPIO_GET_BANK_BIT_MASK(pinNum);

    /* Set pin as output */
    GPIO_setDirMode(baseAddr, pinNum, GPIO_DIRECTION_OUTPUT);

    /* Set pin high to prepare for falling edge */
    GPIO_pinWriteHigh(baseAddr, pinNum);
    ClockP_usleep(1000);

    /* Configure falling edge trigger and enable bank interrupt */
    GPIO_setTrigType(baseAddr, pinNum, GPIO_TRIG_TYPE_FALL_EDGE);
    GPIO_bankIntrEnable(baseAddr, bankNum);

    while (count < loopcnt)
    {
        /* Drive pin low to generate falling edge */
        GPIO_pinWriteLow(baseAddr, pinNum);
        ClockP_usleep(1000);

        /* Check for interrupt status */
        intrStatus = GPIO_getBankIntrStatus(baseAddr, bankNum);
        GPIO_clearBankIntrStatus(baseAddr, bankNum, intrStatus);
        if (intrStatus & pinMask)
        {
            intrcnt++;
        }

        /* Drive pin high, should not trigger interrupt */
        GPIO_pinWriteHigh(baseAddr, pinNum);
        ClockP_usleep(1000);

        /* Check for interrupt status - should not occur */
        intrStatus = GPIO_getBankIntrStatus(baseAddr, bankNum);
        ClockP_usleep(1000);
        TEST_ASSERT_EQUAL_UINT32(0, (intrStatus & pinMask));
        count++;
    }

    /* Small delay before checking final count */
    ClockP_usleep(1000);

    /* Ensure all falling edges triggered interrupts */
    TEST_ASSERT_EQUAL_INT32(loopcnt, intrcnt);

    /* Cleanup: disable trigger, disable bank interrupt, clear status, set pin low */
    GPIO_setTrigType(baseAddr, pinNum, GPIO_TRIG_TYPE_NONE);
    GPIO_bankIntrDisable(baseAddr, bankNum);
    GPIO_clearIntrStatus(baseAddr, pinNum);
    GPIO_pinWriteLow(baseAddr, pinNum);

    /* Signal test completion */
    SemaphoreP_post(&TestGpio_semObj);

    TaskP_exit();
}

/**
 * @brief Test case for GPIO multithreaded interrupt handling with both trigger types.
 *
 * This function tests the GPIO driver's ability to handle interrupts from multiple threads,
 * where each thread may configure and respond to both rising and falling edge triggers.
 * It validates correct synchronization and event handling when both trigger types are used concurrently.
 * The test ensures robustness of the GPIO interrupt mechanism under multithreaded scenarios.
 */
static void TestGpio_multithreadBothTrigType(void *arg)
{
    uint32_t baseAddr = (uint32_t)AddrTranslateP_getLocalAddr(GPIO_MCAN_BASE_ADDR);
    uint32_t pinNum   = GPIO_MCAN_PIN;
    uint32_t bankNum, loopcnt = 10, count = 0;
    uint32_t intrStatus, pinMask, intrcnt = 0;

    bankNum = GPIO_GET_BANK_INDEX(pinNum);
    pinMask = GPIO_GET_BANK_BIT_MASK(pinNum);

    /* Set pin as output */
    GPIO_setDirMode(baseAddr, pinNum, GPIO_DIRECTION_OUTPUT);

    /* Start with pin low */
    GPIO_pinWriteLow(baseAddr, pinNum);
    ClockP_usleep(1000);

    /* Set both-edge trigger and enable bank interrupt */
    GPIO_setTrigType(baseAddr, pinNum, GPIO_TRIG_TYPE_BOTH_EDGE);
    GPIO_bankIntrEnable(baseAddr, bankNum);

    while (count < loopcnt)
    {
        /* Toggle pin to generate both edges */
        if ((count & 0x01) == 0)
        {
            GPIO_pinWriteHigh(baseAddr, pinNum);
            ClockP_usleep(1000);
        }
        else
        {
            GPIO_pinWriteLow(baseAddr, pinNum);
            ClockP_usleep(1000);
        }

        /* Check and clear interrupt status */
        intrStatus = GPIO_getBankIntrStatus(baseAddr, bankNum);
        GPIO_clearBankIntrStatus(baseAddr, bankNum, intrStatus);

        /* Count interrupt if occurred */
        if (intrStatus & pinMask)
        {
            intrcnt++;
        }
        count++;
    }

    ClockP_usleep(1000);

    /* Check all edges triggered interrupts */
    TEST_ASSERT_EQUAL_INT32(loopcnt, intrcnt);

    /* Cleanup: disable trigger, disable bank interrupt, clear status, set pin low */
    GPIO_setTrigType(baseAddr, pinNum, GPIO_TRIG_TYPE_NONE);
    GPIO_bankIntrDisable(baseAddr, bankNum);
    GPIO_clearIntrStatus(baseAddr, pinNum);
    GPIO_pinWriteLow(baseAddr, pinNum);

    /* Signal test completion */
    SemaphoreP_post(&TestGpio_semObj);

    TaskP_exit();
}

/**
 * @brief Test case for GPIO interrupt trigger type in a multithreaded environment.
 *
 * This function tests the behavior of GPIO interrupts when accessed from multiple threads.
 * It verifies correct handling of different interrupt trigger types (e.g., rising, falling edge).
 * The test ensures thread safety and proper synchronization during concurrent GPIO operations.
 * Useful for validating robustness of GPIO driver under multithreaded scenarios.
 */
static void TestGpio_multithreadTrigType(void *args)
{
    uint32_t i;
    int32_t status;
    TaskP_Params taskParams;

    /* Create counting semaphore for threads */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
        SemaphoreP_constructCounting(&TestGpio_semObj, 0, TEST_GPIO_MT_TRIGTYPE));

    for (i = 0; i < TEST_GPIO_MT_TRIGTYPE; i++)
    {
        /* Init and create thread for each trigger type */
        TaskP_Params_init(&taskParams);
        taskParams.name      = "GPIO_MT_BLOCK";
        taskParams.stackSize = TEST_GPIO_STACK_SIZE;
        taskParams.stack     = TestGpio_MtTaskStack[i];
        taskParams.priority  = TEST_GPIO_TASK_PRIORITY;
        taskParams.args      = (void *)(uintptr_t)i;

        if (i == 0)
            taskParams.taskMain = TestGpio_multithreadRisingEdge;
        else if (i == 1)
            taskParams.taskMain = TestGpio_multithreadFallingEdge;
        else
            taskParams.taskMain = TestGpio_multithreadBothTrigType;
        #ifdef SMP_FREERTOS
        taskParams.coreAffinity = 1 << i;
        #endif
        status = TaskP_construct(&TestGpio_MtThreadTaskObj[i], &taskParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* Wait for all threads to finish */
    for (i = 0U; i < TEST_GPIO_MT_TRIGTYPE; i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&TestGpio_semObj, SystemP_WAIT_FOREVER));
    }

    SemaphoreP_destruct(&TestGpio_semObj);

    /* Destroy thread objects */
    for (i = 0; i < TEST_GPIO_MT_TRIGTYPE; i++)
    {
        TaskP_destruct(&TestGpio_MtThreadTaskObj[i]);
    }
}



