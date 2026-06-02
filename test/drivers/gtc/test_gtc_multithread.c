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

 /*===================================================================*/
/* 					      Include Files 					         */
/*===================================================================*/

#include "test_gtc.h"
#include <kernel/dpl/TaskP.h>
#include <kernel/dpl/SemaphoreP.h>

/*===================================================================*/
/* 					      Macro defines 					         */
/*===================================================================*/

/* Macro defining the maximum loop count for the test */
#define MAX_LOOP_COUNT  10

/*===================================================================*/
/* 					         Global Variables			             */
/*===================================================================*/

#if (defined(SOC_AM62X) || defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM275X)) && !(defined(SOC_AM62X) && defined(__aarch64__))

#if defined(SOC_AM275X) && (defined(CPU_C75_0) || defined(CPU_C75_1))
/* Stack for GTC test thread 1 */
static uint8_t TestGtc_threadStack1[32768] __attribute__ ((aligned(32)));
/* Stack for GTC test thread 2 */
static uint8_t TestGtc_threadStack2[32768] __attribute__ ((aligned(32)));
#else
/* Stack for GTC test thread 1 */
static uint8_t TestGtc_threadStack1[1024] __attribute__ ((aligned(32)));
/* Stack for GTC test thread 2 */
static uint8_t TestGtc_threadStack2[1024] __attribute__ ((aligned(32)));
#endif

/* Task status variable for GTC thread1 */
int TestGtc_status1 = 0;
/* Task status variable for GTC thread2 */
int TestGtc_status2 = 0;
#endif

/*===================================================================*/
/* 					         Function Declarations		             */
/*===================================================================*/

#if (defined(SOC_AM62X) || defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM275X)) && !(defined(SOC_AM62X) && defined(__aarch64__))
/* Test case to validate counter values in multiple threads */
static void TestGtc_counterValueInThreads(void *args);
#endif

/*===================================================================*/
/* 					         Function Definitions		             */
/*===================================================================*/

#if defined(SOC_AM62X) || defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM275X)
/**
 * @brief Main GTC multithreaded unit test entry point.
 *
 * Executes the multithreaded Global Timer Counter (GTC) test using the Unity framework.
 * This function dispatches the test case that creates and runs two threads, each reading
 * the GTC counter value and verifying its increment behavior over multiple iterations.
 * The test validates correct counter operation in a concurrent environment.
 *
 * Test cases are invoked using RUN_TEST with associated IDs to exercise GTC functionality
 * in multithreaded scenarios.
 *
 * @return void
 */
void TestGtc_mtTestcase(void)
{
#if (defined(SOC_AM62X) || defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM275X)) && !(defined(SOC_AM62X) && defined(__aarch64__))
    RUN_TEST(TestGtc_counterValueInThreads,  9401, NULL);
#endif
}

#if (defined(SOC_AM62X) || defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM275X)) && !(defined(SOC_AM62X) && defined(__aarch64__))

/**
 * @brief Thread function to validate GTC counter increments in a multithreaded test.
 *
 * This thread reads the Global Timer Counter (GTC) value over multiple iterations,
 * sleeping and yielding between reads, and checks that the difference between
 * consecutive counter values matches the expected clock rate. If any unexpected
 * difference is detected, it sets the thread status variable to indicate failure.
 * Signals the main thread via semaphore upon completion.
 *
 * Test Steps:
 * 1. Get the GTC clock rate.
 * 2. Read the GTC counter value in a loop, sleeping and yielding between reads.
 * 3. Check that the difference between consecutive reads matches the expected clock rate.
 * 4. Set status variable if an error is detected.
 * 5. Signal completion using a semaphore and exit the thread.
 *
 * @param[in] args Pointer to semaphore object for thread synchronization.
 *
 * @return void
 */
static void TestGtc_counterThread1(void *args)
{
    uint64_t clkRate = 0;
    uint64_t difference = 0;
    uint64_t counter_difference = 0;
    static int loopCount = 0;
    int32_t retVal = SystemP_SUCCESS;
    static uint64_t gtcCount_1[MAX_LOOP_COUNT] = {0};
    retVal = SOC_moduleGetClockFrequency(TISCI_DEV_WKUP_GTC0, TISCI_DEV_WKUP_GTC0_GTC_CLK, &clkRate);
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, retVal);

    /* Read GTC counter values in a loop */
    while (loopCount < MAX_LOOP_COUNT)
    {
        gtcCount_1[loopCount] = GTC_getCount64();
        ClockP_sleep(1);
        TaskP_yield();
        loopCount++;
    }

    /* Check differences between consecutive counter values */
    for(loopCount = 1; loopCount <  (MAX_LOOP_COUNT - 1); loopCount++)
    {
        counter_difference = gtcCount_1[loopCount + 1] - gtcCount_1[loopCount];
        difference = (counter_difference < clkRate) ? (clkRate - counter_difference) : (counter_difference - clkRate);

        if(difference > 1000000)
        {
            TestGtc_status1 = 1;
        }
    }

    /* Signal main thread that this thread is done */
    SemaphoreP_post((SemaphoreP_Object *)args);
    TaskP_exit();
}

/**
 * @brief Thread function to validate GTC counter increments in a multithreaded test.
 *
 * This thread reads the Global Timer Counter (GTC) value over multiple iterations,
 * sleeping and yielding between reads, and checks that the difference between
 * consecutive counter values matches the expected clock rate. If any unexpected
 * difference is detected, it sets the thread status variable to indicate failure.
 * Signals the main thread via semaphore upon completion.
 *
 * Test Steps:
 * 1. Get the GTC clock rate.
 * 2. Read the GTC counter value in a loop, sleeping and yielding between reads.
 * 3. Check that the difference between consecutive reads matches the expected clock rate.
 * 4. Set status variable if an error is detected.
 * 5. Signal completion using a semaphore and exit the thread.
 *
 * @param[in] args Pointer to semaphore object for thread synchronization.
 *
 * @return void
 */
static void TestGtc_counterThread2(void *args)
{
    uint64_t clkRate = 0;
    uint64_t difference = 0 ;
    uint64_t counter_difference = 0;
    static int loopCount = 0;
    int32_t retVal = SystemP_SUCCESS;
    static uint64_t gtcCount_1[MAX_LOOP_COUNT] = {0};

    /* Get GTC clock frequency */
    retVal = SOC_moduleGetClockFrequency(TISCI_DEV_WKUP_GTC0, TISCI_DEV_WKUP_GTC0_GTC_CLK, &clkRate);
    TEST_ASSERT_EQUAL(SystemP_SUCCESS, retVal);

    /* Read GTC counter values in a loop */
    while (loopCount < MAX_LOOP_COUNT)
    {
        gtcCount_1[loopCount] = GTC_getCount64();
        ClockP_sleep(1);
        TaskP_yield();
        loopCount++;
    }

    /* Check differences between consecutive counter values. Considering from 1st sample as there may be scheduler delay */
    for(loopCount = 1; loopCount <  (MAX_LOOP_COUNT - 1); loopCount++)
    {
        counter_difference = gtcCount_1[loopCount + 1] - gtcCount_1[loopCount];
        difference = (counter_difference < clkRate) ? (clkRate - counter_difference) : (counter_difference - clkRate);

        if(difference > 1000000)
        {
            TestGtc_status2 = 1;
        }
    }

    /* Signal main thread that this thread is done */
    SemaphoreP_post((SemaphoreP_Object *)args);
    TaskP_exit();
}

/**
 * @brief Multithreaded GTC counter value validation test.
 *
 * This test case creates two threads, each reading the Global Timer Counter (GTC)
 * value over multiple iterations and verifying that the counter increments as expected.
 * Each thread compares consecutive counter values against the clock rate to ensure
 * correct operation. The test passes if both threads observe valid increments and
 * no unexpected differences.
 *
 * Test Steps:
 * 1. Construct a counting semaphore for thread synchronization.
 * 2. Create and start two threads, each reading the GTC counter in a loop.
 * 3. Each thread checks that the difference between consecutive counter reads matches the expected clock rate.
 * 4. Main thread waits for both threads to complete.
 * 5. Cleanup semaphore and thread objects.
 * 6. Assert that both threads observed correct counter increments.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestGtc_counterValueInThreads(void *args)
{
    int32_t status = SystemP_FAILURE;
    int instanceLoop = 0;
    TaskP_Params taskParams1 = {0};
    TaskP_Params taskParams2 = {0};
    SemaphoreP_Object gtcTaskSem;
    TaskP_Object gtcTaskObj1;
    TaskP_Object gtcTaskObj2;
    TestGtc_status1 = 0;
    TestGtc_status2 = 0;

    /* Construct semaphores for each thread */
    status =  SemaphoreP_constructCounting(&gtcTaskSem, 0, 2);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, status);

    /* Create threads for each GTC instance */

    /* Create thread1 */
    TaskP_Params_init(&taskParams1);
    taskParams1.priority       = 3U;
    taskParams1.stack          = TestGtc_threadStack1;
    taskParams1.stackSize      = sizeof(TestGtc_threadStack1);
    taskParams1.args           = (void*)&gtcTaskSem;
    taskParams1.name           = "GTC_Thread1";
    taskParams1.taskMain       = TestGtc_counterThread1;
    status = TaskP_construct(&gtcTaskObj1, &taskParams1);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, status);

    /* Create thread2 */
    TaskP_Params_init(&taskParams2);
    taskParams2.priority       = 3U;
    taskParams2.stack          = TestGtc_threadStack2;
    taskParams2.stackSize      = sizeof(TestGtc_threadStack2);
    taskParams2.args           = (void*)&gtcTaskSem;
    taskParams2.name           = "GTC_Thread2";
    taskParams2.taskMain       = TestGtc_counterThread2;
    status = TaskP_construct(&gtcTaskObj2, &taskParams2);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, status);

    /* Wait for all threads to complete */
    for(instanceLoop = 0; instanceLoop < 2; instanceLoop++)
    {
        status = SemaphoreP_pend(&gtcTaskSem, SystemP_WAIT_FOREVER);
    }

    /* Cleanup */
    SemaphoreP_destruct(&gtcTaskSem);
    TaskP_destruct(&gtcTaskObj1);
    TaskP_destruct(&gtcTaskObj2);

    /* Verify that both threads observed correct no jitter */
    TEST_ASSERT_EQUAL(TestGtc_status1, 0);
    TEST_ASSERT_EQUAL(TestGtc_status2, 0);
}
#endif /* (SOC_AM62X || SOC_AM62AX || SOC_AM62DX || SOC_AM275X) && !((SOC_AM62X) && (__aarch64__)) */
#endif /* SOC_AM62X || SOC_AM62AX || SOC_AM62DX || SOC_AM275X */
