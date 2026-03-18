/*
 *  Copyright (C) 2021-25 Texas Instruments Incorporated
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
 *  \file test_mcspi_multi_thread.c
 *
 *  \brief File containing MCSPI Driver test cases for multi-threaded
 *         usecases.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "string.h"
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/TaskP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <unity.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#if (CONFIG_MCSPI_NUM_INSTANCES > 2)
#include <drivers/mcspi/v0/dma/mcspi_dma.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Base address and interrupt number abstraction for various SoCs */
#if defined(SOC_AM263X)

#define MCSPI0_BASE_ADDRESS             (CSL_MCSPI0_U_BASE)
#define MCSPI1_BASE_ADDRESS             (CSL_MCSPI1_U_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCSPI2_U_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCSPI3_U_BASE)
#define MCSPI4_BASE_ADDRESS             (CSL_MCSPI4_U_BASE)

#define MCSPI0_INT_NUM                  (CSLR_R5FSS0_CORE0_INTR_MCSPI0_INTR)
#define MCSPI1_INT_NUM                  (CSLR_R5FSS0_CORE0_INTR_MCSPI1_INTR)
#define MCSPI2_INT_NUM                  (CSLR_R5FSS0_CORE0_INTR_MCSPI2_INTR)
#define MCSPI3_INT_NUM                  (CSLR_R5FSS0_CORE0_INTR_MCSPI3_INTR)
#define MCSPI4_INT_NUM                  (CSLR_R5FSS0_CORE0_INTR_MCSPI4_INTR)

#elif defined(SOC_AM62AX)

#ifdef R5F_CORE
#define MCSPI0_BASE_ADDRESS             (CSL_MCU_MCSPI0_CFG_BASE)
#define MCSPI1_BASE_ADDRESS             (CSL_MCU_MCSPI1_CFG_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCSPI0_CFG_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)
#define MCSPI4_BASE_ADDRESS             (CSL_MCSPI2_CFG_BASE)

#define MCSPI0_INT_NUM                  (207U)
#define MCSPI1_INT_NUM                  (208U)
#define MCSPI2_INT_NUM                  (204U)
#define MCSPI3_INT_NUM                  (205U)
#define MCSPI4_INT_NUM                  (206U)
#endif

#ifdef A53_CORE
#define MCSPI0_BASE_ADDRESS             (CSL_MCU_MCSPI0_CFG_BASE)
#define MCSPI1_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCU_MCSPI1_CFG_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCSPI2_CFG_BASE)
#define MCSPI4_BASE_ADDRESS             (CSL_MCSPI0_CFG_BASE)

#define MCSPI0_INT_NUM                  (208U)
#define MCSPI1_INT_NUM                  (205U)
#define MCSPI2_INT_NUM                  (209U)
#define MCSPI3_INT_NUM                  (206U)
#define MCSPI4_INT_NUM                  (209U)
#endif

#ifdef DM_R5F_CORE
#define MCSPI0_BASE_ADDRESS             (CSL_MCU_MCSPI0_CFG_BASE)
#define MCSPI1_BASE_ADDRESS             (CSL_MCU_MCSPI1_CFG_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCSPI0_CFG_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)
#define MCSPI4_BASE_ADDRESS             (CSL_MCSPI2_CFG_BASE)

#define MCSPI0_INT_NUM                  (207U)
#define MCSPI1_INT_NUM                  (208U)
#define MCSPI2_INT_NUM                  (204U)
#define MCSPI3_INT_NUM                  (205U)
#define MCSPI4_INT_NUM                  (206U)
#endif

#elif defined(SOC_AM62DX)

#ifdef R5F_CORE
#define MCSPI0_BASE_ADDRESS             (CSL_MCU_MCSPI0_CFG_BASE)
#define MCSPI1_BASE_ADDRESS             (CSL_MCU_MCSPI1_CFG_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCSPI0_CFG_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)
#define MCSPI4_BASE_ADDRESS             (CSL_MCSPI2_CFG_BASE)

#define MCSPI0_INT_NUM                  (207U)
#define MCSPI1_INT_NUM                  (208U)
#define MCSPI2_INT_NUM                  (204U)
#define MCSPI3_INT_NUM                  (205U)
#define MCSPI4_INT_NUM                  (206U)
#endif

#ifdef A53_CORE
#define MCSPI0_BASE_ADDRESS             (CSL_MCU_MCSPI0_CFG_BASE)
#define MCSPI1_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCSPI0_CFG_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCSPI2_CFG_BASE)
#define MCSPI4_BASE_ADDRESS             (CSL_MCU_MCSPI1_CFG_BASE)

#define MCSPI0_INT_NUM                  (208U)
#define MCSPI1_INT_NUM                  (205U)
#define MCSPI2_INT_NUM                  (204U)
#define MCSPI3_INT_NUM                  (206U)
#define MCSPI4_INT_NUM                  (209U)
#endif

#ifdef C75_CORE
#define MCSPI0_BASE_ADDRESS             (CSL_MCU_MCSPI1_CFG_BASE)
#define MCSPI1_BASE_ADDRESS             (CSL_MCU_MCSPI1_CFG_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCSPI0_CFG_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)
#define MCSPI4_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)

#define MCSPI0_INT_NUM                  (1U)
#define MCSPI1_INT_NUM                  (1U)
#define MCSPI2_INT_NUM                  (2U)
#define MCSPI3_INT_NUM                  (31U)
#define MCSPI4_INT_NUM                  (31U)

#define MCSPI0_EVENT_ID                 (177U)
#define MCSPI1_EVENT_ID                 (177U)
#define MCSPI2_EVENT_ID                 (172U)
#define MCSPI3_EVENT_ID                 (173U)
#define MCSPI4_EVENT_ID                 (173U)
#endif

#elif defined(SOC_AM62PX)

#if defined(R5F_CORE) || defined(DM_R5F_CORE)
#define MCSPI0_BASE_ADDRESS             (CSL_MCU_MCSPI0_CFG_BASE)
#define MCSPI1_BASE_ADDRESS             (CSL_MCU_MCSPI1_CFG_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCSPI0_CFG_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)
#define MCSPI4_BASE_ADDRESS             (CSL_MCSPI2_CFG_BASE)

#define MCSPI0_INT_NUM                  (207U)
#define MCSPI1_INT_NUM                  (208U)
#define MCSPI2_INT_NUM                  (204U)
#define MCSPI3_INT_NUM                  (205U)
#define MCSPI4_INT_NUM                  (206U)
#endif

#elif defined(SOC_AM62X)
/* NOTE: For the AM62X R5F domain the logical MCSPI3/MCSPI4 test indices do not
 * match the physical peripheral number. MCSPI3_BASE_ADDRESS maps to
 * CSL_MCSPI1_CFG_BASE (SPI1) and MCSPI4_BASE_ADDRESS maps to CSL_MCSPI0_CFG_BASE
 * (SPI0). This is intentional and matches the syscfg assignments
 * (mcspi3 -> SPI1, mcspi4 -> SPI0) for this domain; do not assume MCSPI3 maps
 * to SPI3 here. */
#ifdef R5F_CORE
#define MCSPI0_BASE_ADDRESS             (CSL_MCU_MCSPI0_CFG_BASE)
#define MCSPI1_BASE_ADDRESS             (CSL_MCU_MCSPI1_CFG_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCSPI2_CFG_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)
#define MCSPI4_BASE_ADDRESS             (CSL_MCSPI0_CFG_BASE)

#define MCSPI0_INT_NUM                  (207U)
#define MCSPI1_INT_NUM                  (208U)
#define MCSPI2_INT_NUM                  (206U)
#define MCSPI3_INT_NUM                  (205U)
#define MCSPI4_INT_NUM                  (204U)
#endif

#ifdef A53_CORE
#define MCSPI0_BASE_ADDRESS             (CSL_MCSPI0_CFG_BASE)
#define MCSPI1_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCU_MCSPI0_CFG_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCSPI2_CFG_BASE)
#define MCSPI4_BASE_ADDRESS             (CSL_MCU_MCSPI1_CFG_BASE)

#define MCSPI0_INT_NUM                  (204U)
#define MCSPI1_INT_NUM                  (205U)
#define MCSPI2_INT_NUM                  (208U)
#define MCSPI3_INT_NUM                  (206U)
#define MCSPI4_INT_NUM                  (209U)
#endif

#elif defined(SOC_AM275X)

#define MCSPI0_BASE_ADDRESS             (CSL_MCSPI0_CFG_BASE)
#define MCSPI1_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCSPI4_CFG_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCSPI2_CFG_BASE)
#define MCSPI4_BASE_ADDRESS             (CSL_MCSPI3_CFG_BASE)

#define MCSPI0_INT_NUM                  (204U)
#define MCSPI1_INT_NUM                  (205U)
#define MCSPI2_INT_NUM                  (208U)
#define MCSPI3_INT_NUM                  (206U)
#define MCSPI4_INT_NUM                  (207U)

#define MCSPI0_EVENT_ID                 (177U)
#define MCSPI1_EVENT_ID                 (178U)
#define MCSPI2_EVENT_ID                 (172U)
#define MCSPI3_EVENT_ID                 (173U)
#define MCSPI4_EVENT_ID                 (173U)

#elif defined(SOC_AM62LX)

#define MCSPI0_BASE_ADDRESS             (CSL_MCSPI0_CFG_BASE)
#define MCSPI1_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCSPI2_CFG_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCSPI3_CFG_BASE)

#define MCSPI0_INT_NUM                  (112U)
#define MCSPI1_INT_NUM                  (113U)
#define MCSPI2_INT_NUM                  (114U)
#define MCSPI3_INT_NUM                  (115U)

#elif defined(SOC_J722S)

#define MCSPI0_BASE_ADDRESS             (CSL_MCSPI0_CFG_BASE)
#define MCSPI1_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCSPI2_CFG_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCU_MCSPI0_CFG_BASE)
#define MCSPI4_BASE_ADDRESS             (CSL_MCU_MCSPI1_CFG_BASE)

#define MCSPI0_INT_NUM                  (204U)
#define MCSPI1_INT_NUM                  (205U)
#define MCSPI2_INT_NUM                  (206U)
#define MCSPI3_INT_NUM                  (63U)
#define MCSPI4_INT_NUM                  (207U)

#else

#define MCSPI0_BASE_ADDRESS             (CSL_MCSPI0_CFG_BASE)
#define MCSPI1_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCSPI2_CFG_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCSPI3_CFG_BASE)
#define MCSPI4_BASE_ADDRESS             (CSL_MCSPI4_CFG_BASE)

#define MCSPI0_INT_NUM                  (204U)
#define MCSPI1_INT_NUM                  (205U)
#define MCSPI2_INT_NUM                  (206U)
#define MCSPI3_INT_NUM                  (63U)
#define MCSPI4_INT_NUM                  (207U)
#endif

/* Task Macros */
#define MCSPI_TASK_PRIORITY   (8U)
#define MCSPI_TASK_STACK_SIZE (32U * 1024U)

/* Macro to define the number of threads in multi instance and single instance modes */
#define TEST_MCSPI_MT_THREADS                    (2U)

/* Macro to define the number of max threads to test multi instance  */
#define TEST_MCSPI_MT_MULTI_CHANNEL_THREADS      (4U)

/* Macro that defines the number of bytes involved in a single transaction */
#define TEST_MCSPI_MT_BYTES                     (32U)

/* Macro to define the timeout used by the slave function to return failure */
#define MCSPI_SLAVE_TIMEOUT_MS   (3000U)

/* ========================================================================== */
/*                               Typedefs                                     */
/* ========================================================================== */

typedef struct MCSPI_TestParams_s {
    MCSPI_ChConfig      mcspiChConfigParams;
    MCSPI_OpenParams    mcspiOpenParams;
    uint32_t            transferLength;
    uint32_t            testcaseId;
    uint32_t            dataSize;
} MCSPI_TestParams;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Semaphore for marking completion of each thread */
static SemaphoreP_Object TestMcspi_semObj;

/* Thread related objects */
static TaskP_Object         TestMcspi_MtThreadTaskObj[TEST_MCSPI_MT_MULTI_CHANNEL_THREADS];
static uint8_t              TestMcspi_MtThreadTaskStack[TEST_MCSPI_MT_MULTI_CHANNEL_THREADS][MCSPI_TASK_STACK_SIZE];

/* Variable to hold the result of each thread */
static uint32_t TestMcspi_MtThreadResults[TEST_MCSPI_MT_MULTI_CHANNEL_THREADS];

/* Buffers for TX and RX data. This buffer is specifically to be used by DMA test cases */
uint8_t  gMcspiTxBuffer[TEST_MCSPI_MT_BYTES] __attribute__((aligned(CacheP_CACHELINE_ALIGNMENT)));
uint8_t  gMcspiRxBuffer[TEST_MCSPI_MT_BYTES] __attribute__((aligned(CacheP_CACHELINE_ALIGNMENT)));

/* ========================================================================== */
/*                     Internal Function Declaration                          */
/* ========================================================================== */

static void TestMcspi_multithreadCallback(MCSPI_Handle handle, MCSPI_Transaction *trans);
static void TestMcspi_multithreadSingleInstanceBlockingWorker(void *arg);
static void TestMcspi_multithreadSingleInstanceBlocking(void *args);
static void TestMcspi_multithreadMultiInstanceBlockingWorker(void *arg);
static void TestMcspi_multithreadMultiInstanceBlocking(void *args);
static void TestMcspi_multithreadMultiInstanceCallback(void *args);
static void TestMcspi_multithreadMultiInstanceCallbackWorker(void *arg);
#if !defined A53_CORE
static void TestMcspi_multithreadMultiInstanceRandomWorker(void *arg);
static void TestMcspi_multithreadMultiInstanceRandom(void *arg);
static void TestMcspi_slaveTimeout(void *args);
static void TestMcspi_setParamsIns4(MCSPI_TestParams *testParams, uint32_t tcId);
#endif
static void Test_Mcspi_CsdisableWorker(void *arg);
void TestMcspi_csDisable(void *args);

static void TestMcspi_setParamsIns0(MCSPI_TestParams *testParams, uint32_t tcId);
static void TestMcspi_setParamsIns1(MCSPI_TestParams *testParams, uint32_t tcId);
static void TestMcspi_setParamsIns3(MCSPI_TestParams *testParams, uint32_t tcId);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void run_multi_threaded_tests(void *args)
{
    MCSPI_TestParams  testParams;
    #if !(defined(SOC_AM62X) && defined(R5F_CORE))
    TestMcspi_setParamsIns0(&testParams, 8785);
    RUN_TEST(TestMcspi_multithreadSingleInstanceBlocking, 8785, (void*) &testParams);
    TestMcspi_setParamsIns0(&testParams, 8421);
    RUN_TEST(TestMcspi_multithreadMultiInstanceBlocking, 8421, (void*)&testParams);
    #endif
    TestMcspi_setParamsIns0(&testParams, 8422);
    RUN_TEST(TestMcspi_multithreadMultiInstanceCallback, 8422, (void*)&testParams);
    /* NOTE: Master-slave external loopback tests are failing on A53 core; this issue has been raised as a bug. */
    #if !defined A53_CORE && !(defined(SOC_AM62X) && defined(R5F_CORE)) 
    TestMcspi_setParamsIns0(&testParams, 8431);
    RUN_TEST(TestMcspi_multithreadMultiInstanceRandom, 9228, (void*) &testParams);
    TestMcspi_setParamsIns0(&testParams, 8432);
    RUN_TEST(TestMcspi_multithreadMultiInstanceRandom, 9229, (void*) &testParams);
    TestMcspi_setParamsIns0(&testParams, 8433);
    RUN_TEST(TestMcspi_slaveTimeout, 9230, (void*) &testParams);
    TestMcspi_setParamsIns0(&testParams, 8434);
    RUN_TEST(TestMcspi_slaveTimeout, 9231, (void*) &testParams);
    TestMcspi_setParamsIns0(&testParams, 8435);
    RUN_TEST(TestMcspi_csDisable, 9232, (void*) &testParams);
    #endif

    return;
}

#ifdef SMP_FREERTOS
void test_main(void *args)
{
    MCSPI_TestParams  testParams;

    UNITY_BEGIN();

    TestMcspi_setParamsIns0(&testParams, 8785);
    RUN_TEST(TestMcspi_multithreadSingleInstanceBlocking, 9090, (void*) &testParams);
    #if defined(SOC_AM62AX)|| defined(SOC_AM62PX)
    /* NOTE: On AM62DX, getting data mismatch at 2nd position; all other data matches. */
    /* Only the 2nd position is overwritten, causing mismatch and hanging other test cases. */
    TestMcspi_setParamsIns0(&testParams, 8421);
    RUN_TEST(TestMcspi_multithreadMultiInstanceBlocking, 9091, (void*)&testParams);
    TestMcspi_setParamsIns0(&testParams, 8422);
    RUN_TEST(TestMcspi_multithreadMultiInstanceCallback, 9092, (void*)&testParams);
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
 * @brief MCSPI transfer completion callback.
 *
 * This function is used as the driver callback for asynchronous MCSPI transfers.
 * If the transaction provided an argument pointer that points to a DPL semaphore,
 * the semaphore is posted to signal transfer completion to the waiting task.
 *
 * @param handle MCSPI driver handle (unused)
 * @param trans  Pointer to the completed transaction; trans->args may be a
 *               SemaphoreP_Object* that will be posted.
 */
static void TestMcspi_multithreadCallback(MCSPI_Handle handle, MCSPI_Transaction *trans)
{
    if(trans && trans->args)
    {
        SemaphoreP_post((SemaphoreP_Object*)trans->args);
    }
}

/**
 * @brief Worker: single-instance blocking-mode multithread test.
 *
 * Each worker prepares a unique transmit pattern, issues a blocking transfer to
 * the shared MCSPI instance and validates that the received data matches the
 * transmitted pattern. The result is stored in a shared results array and a
 * counting semaphore is posted to indicate completion.
 *
 * @param arg  Worker index (cast from uintptr_t) used to derive the pattern.
 */
static void TestMcspi_multithreadSingleInstanceBlockingWorker(void *arg)
{
    uint32_t i;
    uint32_t idx = (uint32_t)(uintptr_t)arg;
    uint8_t           tempTxPtr8[TEST_MCSPI_MT_BYTES];
    uint8_t           tempRxPtr8[TEST_MCSPI_MT_BYTES];
    MCSPI_Transaction spiTransaction;
    int32_t status = SystemP_SUCCESS;
    int32_t dataMismatch = 0;

    for(i = 0; i < TEST_MCSPI_MT_BYTES; i++)
    {
        tempTxPtr8[i] = (uint8_t)(0xA0 ^ idx ^ i);
        tempRxPtr8[i] = 0U;
    }

    MCSPI_Transaction_init(&spiTransaction);
    spiTransaction.channel   = 0;
    spiTransaction.dataSize  = 8;
    spiTransaction.count     = TEST_MCSPI_MT_BYTES;
    spiTransaction.csDisable = TRUE;
    spiTransaction.txBuf     = tempTxPtr8;
    spiTransaction.rxBuf     = tempRxPtr8;
    spiTransaction.args      = NULL;

    if (idx == CONFIG_MCSPI0)
    {
        spiTransaction.channel = 1;
    }

    status = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction);

    /* Verify */
    if ((status == SystemP_SUCCESS) && (spiTransaction.status == MCSPI_TRANSFER_COMPLETED))
    {
        uint8_t *tempTxPtr, *tempRxPtr;
        tempTxPtr = (uint8_t *) tempTxPtr8;
        tempRxPtr = (uint8_t *) tempRxPtr8;
        for(i = 0U; i < TEST_MCSPI_MT_BYTES; i++)
        {
            if(*tempTxPtr++ != *tempRxPtr++)
            {
                dataMismatch = 1;   /* Data mismatch */
                DebugP_log("Data Mismatch at offset %d (instance %u)\r\n", i, idx);
                break;
            }
        }
    }

    /* Set the result as pass/fail depending upon the results */
    TestMcspi_MtThreadResults[idx] = (status == SystemP_SUCCESS) &&
                                     (spiTransaction.status == MCSPI_TRANSFER_COMPLETED) &&
                                     (dataMismatch == 0);

    SemaphoreP_post(&TestMcspi_semObj);
    TaskP_exit();
}

/**
 * @brief Test harness: single-instance, blocking-mode multithread case.
 *
 * Sets up the shared MCSPI instance according to provided parameters, spawns
 * multiple worker tasks that simultaneously call the blocking transfer API, and
 * waits for them to finish. Verifies expected pass/fail behavior across workers.
 *
 * @param args  Pointer to MCSPI_TestParams containing open/chconfig settings.
 */
static void TestMcspi_multithreadSingleInstanceBlocking(void *args)
{
    uint32_t i;
    int32_t status;
    MCSPI_TestParams   *testParams = (MCSPI_TestParams *)args;
    MCSPI_OpenParams   *mcspiOpenParams = &(testParams->mcspiOpenParams);
    MCSPI_ChConfig     *mcspiChConfigParams = &(testParams->mcspiChConfigParams);

    if(gMcspiHandle[CONFIG_MCSPI0])
    {
        MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);
        gMcspiHandle[CONFIG_MCSPI0] = NULL;
    }

    gMcspiHandle[CONFIG_MCSPI0] = MCSPI_open(CONFIG_MCSPI0, mcspiOpenParams );
    TEST_ASSERT_NOT_NULL(gMcspiHandle[CONFIG_MCSPI0]);

    status = MCSPI_chConfig(
                 gMcspiHandle[CONFIG_MCSPI0],
                 mcspiChConfigParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
    SemaphoreP_constructCounting(&TestMcspi_semObj, 0, TEST_MCSPI_MT_THREADS));

    for(i = 0; i < TEST_MCSPI_MT_THREADS; i++)
    {
        TaskP_Params taskParams;
        TaskP_Params_init(&taskParams);
        taskParams.name      = "MCSPI_MT_BLOCK";
        taskParams.stackSize = MCSPI_TASK_STACK_SIZE;
        taskParams.stack     = TestMcspi_MtThreadTaskStack[i];
        taskParams.priority  = MCSPI_TASK_PRIORITY+i;
        taskParams.args      = (void*)(uintptr_t)i;
        taskParams.taskMain  = TestMcspi_multithreadSingleInstanceBlockingWorker;
        taskParams.coreAffinity = 1 << i;
        status = TaskP_construct(&TestMcspi_MtThreadTaskObj[i], &taskParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* Wait for exactly one callback post per transfer */
    for(i=0U;i<TEST_MCSPI_MT_THREADS;i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&TestMcspi_semObj, SystemP_WAIT_FOREVER));
    }

    /* One test case should pass and other should fail */
    TEST_ASSERT_NOT_EQUAL_INT32(TestMcspi_MtThreadResults[0], TestMcspi_MtThreadResults[1]);

    SemaphoreP_destruct(&TestMcspi_semObj);

    for(i = 0; i < TEST_MCSPI_MT_THREADS; i++)
    {
        TaskP_destruct(&TestMcspi_MtThreadTaskObj[i]);
    }

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);
}

/**
 * @brief Worker: multi-instance blocking-mode test.
 *
 * Each worker selects its MCSPI handle based on the passed index, prepares
 * a transmit pattern, issues a blocking transfer and verifies the received
 * data. Posts a counting semaphore to signal completion.
 *
 * @param arg  Worker index (cast from uintptr_t).
 */
static void TestMcspi_multithreadMultiInstanceBlockingWorker(void *arg)
{
    uint32_t i;
    uint32_t idx = (uint32_t)(uintptr_t)arg;
    uint8_t           tempTxPtr8[TEST_MCSPI_MT_BYTES];
    uint8_t           tempRxPtr8[TEST_MCSPI_MT_BYTES];
    MCSPI_Transaction spiTransaction;
    MCSPI_Handle      mcspiHandle;
    int32_t status = SystemP_SUCCESS;

    mcspiHandle = gMcspiHandle[idx];

    /* Fill pattern */
    for(i=0;i<TEST_MCSPI_MT_BYTES;i++)
    {
        tempTxPtr8[i] = (uint8_t)(0xC0 + (idx * 0x10) + i);
        tempRxPtr8[i] = 0U;
    }

    MCSPI_Transaction_init(&spiTransaction);
    spiTransaction.channel   = 0;
    spiTransaction.dataSize  = 8;
    spiTransaction.count     = TEST_MCSPI_MT_BYTES;
    spiTransaction.csDisable = TRUE;
    spiTransaction.txBuf     = tempTxPtr8;
    spiTransaction.rxBuf     = tempRxPtr8;
    spiTransaction.args      = NULL;

    if (idx == CONFIG_MCSPI0)
    {
        spiTransaction.channel = 1;
    }

    status = MCSPI_transfer(mcspiHandle, &spiTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Verify */
    uint8_t *tempTxPtr, *tempRxPtr;
    tempTxPtr = (uint8_t *) tempTxPtr8;
    tempRxPtr = (uint8_t *) tempRxPtr8;
    for(i = 0U; i < TEST_MCSPI_MT_BYTES; i++)
    {
        if(*tempTxPtr++ != *tempRxPtr++)
        {
            status = SystemP_FAILURE;   /* Data mismatch */
            DebugP_log("Data Mismatch at offset %d (instance %u)\r\n", i, idx);
            break;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    SemaphoreP_post(&TestMcspi_semObj);
    TaskP_exit();
}

/**
 * @brief Test harness: multi-instance blocking-mode case.
 *
 * Opens multiple MCSPI instances (per configuration), spawns worker tasks that
 * each use a different instance, and waits for all to complete using a counting
 * semaphore. Ensures correct operation when multiple instances are used in
 * parallel.
 *
 * @param args Pointer to MCSPI_TestParams with instance-specific settings.
 */
static void TestMcspi_multithreadMultiInstanceBlocking(void *args)
{
    uint32_t i;
    int32_t status;
    MCSPI_TestParams   *testParams = (MCSPI_TestParams *)args;
    TaskP_Params taskParams;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
    SemaphoreP_constructCounting(&TestMcspi_semObj,0, TEST_MCSPI_MT_THREADS));

    for (i=0;i<TEST_MCSPI_MT_THREADS;i++)
    {
        switch (i)
        {
            case CONFIG_MCSPI1:
                TestMcspi_setParamsIns1(testParams, testParams->testcaseId);
                break;
            default:
                break;
        }

        MCSPI_OpenParams   *mcspiOpenParams = &(testParams->mcspiOpenParams);
        MCSPI_ChConfig     *mcspiChConfigParams = &(testParams->mcspiChConfigParams);

        if(gMcspiHandle[i])
        {
            MCSPI_close(gMcspiHandle[i]);
            gMcspiHandle[i]=NULL;
        }

        gMcspiHandle[i] = MCSPI_open(i, mcspiOpenParams);
        TEST_ASSERT_NOT_NULL(gMcspiHandle[i]);

        status = MCSPI_chConfig(gMcspiHandle[i], mcspiChConfigParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        TaskP_Params_init(&taskParams);
        taskParams.name      = "MCSPI_MT_MI_BLOCKING_REUSE";
        taskParams.stackSize = MCSPI_TASK_STACK_SIZE;
        taskParams.stack     = TestMcspi_MtThreadTaskStack[i];
        taskParams.priority  = MCSPI_TASK_PRIORITY;
        taskParams.args      = (void*)(uintptr_t)i;
        taskParams.taskMain  = TestMcspi_multithreadMultiInstanceBlockingWorker;
        taskParams.coreAffinity = 1 << i;
        status = TaskP_construct(&TestMcspi_MtThreadTaskObj[i], &taskParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* Wait for exactly one callback post per transfer */
    for(i=0U;i<TEST_MCSPI_MT_THREADS;i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&TestMcspi_semObj, SystemP_WAIT_FOREVER));
    }

    /* Cleanup */

    SemaphoreP_destruct(&TestMcspi_semObj);

    for(i=0;i<TEST_MCSPI_MT_THREADS;i++)
    {
        TaskP_destruct(&TestMcspi_MtThreadTaskObj[i]);
    }

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);
    MCSPI_close(gMcspiHandle[CONFIG_MCSPI1]);
}

/**
 * @brief Worker: multi-instance callback-mode test.
 *
 * Selects the MCSPI handle for this worker, constructs per-worker buffers and
 * a semaphore, issues an asynchronous transfer and waits for its completion
 * via the semaphore. Verifies data integrity and signals completion.
 *
 * @param arg Worker index (cast from uintptr_t).
 */
static void TestMcspi_multithreadMultiInstanceCallbackWorker(void *arg)
{
    uint32_t i;
    uint32_t idx = (uint32_t)(uintptr_t)arg;
    uint8_t           tempTxPtr8[TEST_MCSPI_MT_BYTES];
    uint8_t           tempRxPtr8[TEST_MCSPI_MT_BYTES];
    MCSPI_Transaction spiTransaction;
    MCSPI_Handle      mcspiHandle;
    SemaphoreP_Object transferDoneMutex;
    int32_t status;

    mcspiHandle = gMcspiHandle[idx];

    status = SemaphoreP_constructBinary(&transferDoneMutex, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Fill pattern */
    for(i=0;i<TEST_MCSPI_MT_BYTES;i++)
    {
        tempTxPtr8[i] = (uint8_t)(0xC0 + (idx * 0x10) + i);
        tempRxPtr8[i] = 0U;
    }

    MCSPI_Transaction_init(&spiTransaction);
    spiTransaction.channel   = 0;
    spiTransaction.dataSize  = 8;
    spiTransaction.count     = TEST_MCSPI_MT_BYTES;
    spiTransaction.csDisable = TRUE;
    spiTransaction.txBuf     = tempTxPtr8;
    spiTransaction.rxBuf     = tempRxPtr8;
    spiTransaction.args      = &transferDoneMutex;

    if (idx == CONFIG_MCSPI0)
    {
        /* This function is used for both Instance 0 and Instance 1.
        * For Instance 0, chip-select is configured as CS1 in SysConfig due to external pinout,
        * so channel = 1; for other instances, channel defaults to 0.
        */
        spiTransaction.channel = 1;
    }

    status = MCSPI_transfer(mcspiHandle, &spiTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

     /* Wait for transfer completion */
    SemaphoreP_pend(&transferDoneMutex, SystemP_WAIT_FOREVER);

    /* Verify */
    uint8_t *tempTxPtr, *tempRxPtr;
    tempTxPtr = (uint8_t *) tempTxPtr8;
    tempRxPtr = (uint8_t *) tempRxPtr8;
    for(i = 0U; i < (TEST_MCSPI_MT_BYTES); i++)
    {
        if(*tempTxPtr++ != *tempRxPtr++)
        {
            status = SystemP_FAILURE;   /* Data mismatch */
            DebugP_log("Data Mismatch at offset %d (instance %u)\r\n", i, idx);
            break;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    SemaphoreP_post(&TestMcspi_semObj);

    SemaphoreP_destruct(&transferDoneMutex);

    TaskP_exit();
}

/**
 * @brief Test harness: multi-instance, callback-mode case.
 *
 * Configures multiple MCSPI instances in callback mode, spawns a worker per
 * instance which performs an asynchronous transfer, and waits for all callbacks
 * to occur using a counting semaphore.
 *
 * @param args Pointer to MCSPI_TestParams with instance-specific settings.
 */
static void TestMcspi_multithreadMultiInstanceCallback(void *args)
{
    uint32_t i;
    int32_t status;
    MCSPI_TestParams   *testParams = (MCSPI_TestParams *)args;
    TaskP_Params taskParams;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
    SemaphoreP_constructCounting(&TestMcspi_semObj,0, TEST_MCSPI_MT_THREADS));

    for (i=0;i<TEST_MCSPI_MT_THREADS;i++)
    {
        switch (i)
        {
            case CONFIG_MCSPI1:
                TestMcspi_setParamsIns1(testParams, testParams->testcaseId);
                break;
            default:
                break;
        }

        MCSPI_OpenParams   *mcspiOpenParams = &(testParams->mcspiOpenParams);
        MCSPI_ChConfig     *mcspiChConfigParams = &(testParams->mcspiChConfigParams);

        mcspiOpenParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
        mcspiOpenParams->transferCallbackFxn    = TestMcspi_multithreadCallback;

        if(gMcspiHandle[i])
        {
            MCSPI_close(gMcspiHandle[i]);
            gMcspiHandle[i]=NULL;
        }

        gMcspiHandle[i] = MCSPI_open(i, mcspiOpenParams);
        TEST_ASSERT_NOT_NULL(gMcspiHandle[i]);

        status = MCSPI_chConfig(gMcspiHandle[i], mcspiChConfigParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        TaskP_Params_init(&taskParams);
        taskParams.name      = "MCSPI_MT_MI_CB_REUSE";
        taskParams.stackSize = MCSPI_TASK_STACK_SIZE;
        taskParams.stack     = TestMcspi_MtThreadTaskStack[i];
        taskParams.priority  = MCSPI_TASK_PRIORITY;
        taskParams.args      = (void*)(uintptr_t)i;
        taskParams.taskMain  = TestMcspi_multithreadMultiInstanceCallbackWorker;
        taskParams.coreAffinity = 1 << i;
        status = TaskP_construct(&TestMcspi_MtThreadTaskObj[i], &taskParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* Wait for exactly one callback post per transfer */
    for(i=0U;i<TEST_MCSPI_MT_THREADS;i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&TestMcspi_semObj, SystemP_WAIT_FOREVER));
    }

    /* Cleanup */
    SemaphoreP_destruct(&TestMcspi_semObj);

    for(i=0;i<TEST_MCSPI_MT_THREADS;i++)
    {
        TaskP_destruct(&TestMcspi_MtThreadTaskObj[i]);
    }


    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);
    MCSPI_close(gMcspiHandle[CONFIG_MCSPI1]);
}

/**
 * @brief Worker function to handle Chip Select (CS) disable operations in MCSPI tests.
 *
 * This function is executed as a separate thread to simulate concurrent CS disable scenarios.
 * It receives a pointer to arguments required for the CS disable operation.
 * The function is primarily used in multi-threaded test cases for MCSPI driver validation.
 * Ensures proper synchronization and error handling during CS disable process.
 */
static void Test_Mcspi_CsdisableWorker(void *arg)
{
    uint32_t  i;
    int32_t       status = SystemP_SUCCESS;
    uint32_t  idx = (uint32_t)(uintptr_t)arg;
    uint8_t   tempTxPtr8[TEST_MCSPI_MT_BYTES];
    uint8_t   tempRxPtr8[TEST_MCSPI_MT_BYTES];
    uint8_t*  txBufPtr;
    uint8_t*  rxBufPtr;
    MCSPI_Transaction spiTransaction;
    SemaphoreP_Object transferDoneMutex;

    /* Fill pattern */
    for(i=0;i<TEST_MCSPI_MT_BYTES;i++)
    {
        /* DMA uses aligned buffers */
        if (idx == CONFIG_MCSPI3)
        {
            gMcspiTxBuffer[i] = (uint8_t)(0xC0 + i);
            gMcspiRxBuffer[i] = 0U;
        }
        else
        {
            tempTxPtr8[i] = (uint8_t)(0xC0 + i);
            tempRxPtr8[i] = 0U;
        }
    }

    status = SemaphoreP_constructBinary(&transferDoneMutex, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);


    /* Initiate transfer */
    spiTransaction.channel   = 0;
    spiTransaction.dataSize  = 8;
    spiTransaction.count     = TEST_MCSPI_MT_BYTES;
    spiTransaction.csDisable = FALSE;
    spiTransaction.args      = &transferDoneMutex;

    if (idx == CONFIG_MCSPI0)
    {
        spiTransaction.channel = 1;
    }

    /* Use aligned buffers for DMA transfer */
    if (idx == CONFIG_MCSPI3)
    {
        spiTransaction.txBuf = gMcspiTxBuffer;
        spiTransaction.rxBuf = gMcspiRxBuffer;
        txBufPtr = &gMcspiTxBuffer[0];
        rxBufPtr = &gMcspiRxBuffer[0];

        CacheP_wb(&gMcspiTxBuffer[0U], sizeof(gMcspiTxBuffer), CacheP_TYPE_ALLD);
        CacheP_wb(&gMcspiRxBuffer[0U], sizeof(gMcspiRxBuffer), CacheP_TYPE_ALLD);
    }
    else
    {
        spiTransaction.txBuf = tempTxPtr8;
        spiTransaction.rxBuf = tempRxPtr8;
        txBufPtr = &tempTxPtr8[0];
        rxBufPtr = &tempRxPtr8[0];
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, MCSPI_transfer(gMcspiHandle[idx], &spiTransaction));

    SemaphoreP_pend(&transferDoneMutex, SystemP_WAIT_FOREVER);

    if (idx == CONFIG_MCSPI3)
    {
        /* Invalidate cache for DMA transfer */
        CacheP_inv(&gMcspiRxBuffer[0U], sizeof(gMcspiRxBuffer), CacheP_TYPE_ALLD);
    }

    /* Verify */
    for(i=0;i<TEST_MCSPI_MT_BYTES;i++)
    {
        if(txBufPtr[i] != rxBufPtr[i])
        {
            status = SystemP_FAILURE;   /* Data mismatch */
            DebugP_log("Data Mismatch at offset %d (instance %u)\r\n", i, idx);
            break;
        }
    }
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        for(i=0;i<TEST_MCSPI_MT_BYTES;i++)
    {
        /* DMA uses aligned buffers */
        if (idx == CONFIG_MCSPI3)
        {
            gMcspiTxBuffer[i] = (uint8_t)(0xC0 + i);
            gMcspiRxBuffer[i] = 0U;
        }
        else
        {
            tempTxPtr8[i] = (uint8_t)(0xC0 + i);
            tempRxPtr8[i] = 0U;
        }
    }

    /* Initiate transfer */
    spiTransaction.channel   = 0;
    spiTransaction.dataSize  = 8;
    spiTransaction.count     = TEST_MCSPI_MT_BYTES;
    spiTransaction.csDisable = FALSE;
    spiTransaction.args      = &transferDoneMutex;

    if (idx == CONFIG_MCSPI0)
    {
        spiTransaction.channel = 1;
    }

    /* Use aligned buffers for DMA transfer */
    if (idx == CONFIG_MCSPI3)
    {
        spiTransaction.txBuf = gMcspiTxBuffer;
        spiTransaction.rxBuf = gMcspiRxBuffer;
        txBufPtr = &gMcspiTxBuffer[0];
        rxBufPtr = &gMcspiRxBuffer[0];

        CacheP_wb(&gMcspiTxBuffer[0U], sizeof(gMcspiTxBuffer), CacheP_TYPE_ALLD);
        CacheP_wb(&gMcspiRxBuffer[0U], sizeof(gMcspiRxBuffer), CacheP_TYPE_ALLD);
    }
    else
    {
        spiTransaction.txBuf = tempTxPtr8;
        spiTransaction.rxBuf = tempRxPtr8;
        txBufPtr = &tempTxPtr8[0];
        rxBufPtr = &tempRxPtr8[0];
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, MCSPI_transfer(gMcspiHandle[idx], &spiTransaction));

    SemaphoreP_pend(&transferDoneMutex, SystemP_WAIT_FOREVER);

    if (idx == CONFIG_MCSPI3)
    {
        /* Invalidate cache for DMA transfer */
        CacheP_inv(&gMcspiRxBuffer[0U], sizeof(gMcspiRxBuffer), CacheP_TYPE_ALLD);
    }

    /* Verify */
    for(i=0;i<TEST_MCSPI_MT_BYTES;i++)
    {
        if(txBufPtr[i] != rxBufPtr[i])
        {
            status = SystemP_FAILURE;   /* Data mismatch */
            DebugP_log("Data Mismatch at offset %d (instance %u)\r\n", i, idx);
            break;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    for(i=0;i<TEST_MCSPI_MT_BYTES;i++)
    {
        /* DMA uses aligned buffers */
        if (idx == CONFIG_MCSPI3)
        {
            gMcspiTxBuffer[i] = (uint8_t)(0xC0 + i);
            gMcspiRxBuffer[i] = 0U;
        }
        else
        {
            tempTxPtr8[i] = (uint8_t)(0xC0 + i);
            tempRxPtr8[i] = 0U;
        }
    }

    /* Initiate transfer */
    spiTransaction.channel   = 0;
    spiTransaction.dataSize  = 8;
    spiTransaction.count     = TEST_MCSPI_MT_BYTES;
    spiTransaction.csDisable = TRUE;
    spiTransaction.args      = &transferDoneMutex;

    if (idx == CONFIG_MCSPI0)
    {
        spiTransaction.channel = 1;
    }

    /* Use aligned buffers for DMA transfer */
    if (idx == CONFIG_MCSPI3)
    {
        spiTransaction.txBuf = gMcspiTxBuffer;
        spiTransaction.rxBuf = gMcspiRxBuffer;
        txBufPtr = &gMcspiTxBuffer[0];
        rxBufPtr = &gMcspiRxBuffer[0];

        CacheP_wb(&gMcspiTxBuffer[0U], sizeof(gMcspiTxBuffer), CacheP_TYPE_ALLD);
        CacheP_wb(&gMcspiRxBuffer[0U], sizeof(gMcspiRxBuffer), CacheP_TYPE_ALLD);
    }
    else
    {
        spiTransaction.txBuf = tempTxPtr8;
        spiTransaction.rxBuf = tempRxPtr8;
        txBufPtr = &tempTxPtr8[0];
        rxBufPtr = &tempRxPtr8[0];
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, MCSPI_transfer(gMcspiHandle[idx], &spiTransaction));

    SemaphoreP_pend(&transferDoneMutex, SystemP_WAIT_FOREVER);

    if (idx == CONFIG_MCSPI3)
    {
        /* Invalidate cache for DMA transfer */
        CacheP_inv(&gMcspiRxBuffer[0U], sizeof(gMcspiRxBuffer), CacheP_TYPE_ALLD);
    }

    /* Verify */
    for(i=0;i<TEST_MCSPI_MT_BYTES;i++)
    {
        if(txBufPtr[i] != rxBufPtr[i])
        {
            status = SystemP_FAILURE;   /* Data mismatch */
            DebugP_log("Data Mismatch at offset %d (instance %u)\r\n", i, idx);
            break;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    SemaphoreP_post(&TestMcspi_semObj);

    SemaphoreP_destruct(&transferDoneMutex);

    TaskP_exit();
}

/**
 * @brief Test case to verify the Chip Select (CS) disable functionality in MCSPI.
 *
 * This test ensures that the MCSPI driver correctly handles the disabling of the chip select line.
 * It simulates scenarios where the CS line must be deactivated during SPI communication.
 * The test checks for proper hardware and software state transitions upon CS disable.
 * It helps validate robustness and correctness of the MCSPI driver in multi-threaded environments.
 */
void TestMcspi_csDisable(void *args)
{
    uint32_t i;
    uint32_t instance;
    int32_t status;
    MCSPI_TestParams   *testParams = (MCSPI_TestParams *)args;
    TaskP_Params tp;
    MCSPI_OpenParams   *mcspiOpenParams;
    MCSPI_ChConfig     *mcspiChConfigParams;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
    SemaphoreP_constructCounting(&TestMcspi_semObj,0, TEST_MCSPI_MT_THREADS));

    for (instance=0;instance<TEST_MCSPI_MT_THREADS;instance++)
    {
        if (instance != CONFIG_MCSPI0)
        {
            instance = CONFIG_MCSPI3 ;
        }
        if (instance == CONFIG_MCSPI3)
        {
            TestMcspi_setParamsIns3(testParams, testParams->testcaseId);
        }

        mcspiOpenParams = &(testParams->mcspiOpenParams);
        mcspiChConfigParams = &(testParams->mcspiChConfigParams);

        if(gMcspiHandle[instance])
        {
            if (instance == CONFIG_MCSPI3)
            {
                status = MCSPI_dmaClose(gMcspiHandle[CONFIG_MCSPI3], &gConfigMcspi3ChCfg[0U] );
                TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
            }

            MCSPI_close(gMcspiHandle[instance]);
            gMcspiHandle[instance]=NULL;
        }

        gMcspiHandle[instance] = MCSPI_open(instance, mcspiOpenParams);
        TEST_ASSERT_NOT_NULL(gMcspiHandle[instance]);

        status = MCSPI_chConfig(gMcspiHandle[instance], mcspiChConfigParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        if (instance != CONFIG_MCSPI0)
        {
            status = MCSPI_chConfig(
                 gMcspiHandle[CONFIG_MCSPI3],
                 &gConfigMcspi3ChCfg[0U]);
           if(status != SystemP_SUCCESS)
           {
             DebugP_logError("CONFIG_MCSPI3 channel %d config failed !!!\r\n", 0);
           }
        }


        if (instance == CONFIG_MCSPI3)
        {
            /*
            status = MCSPI_dmaChConfig(gMcspiHandle[instance], mcspiChConfigParams,
                                       &gConfigMcspi3DmaChCfg[0U]);
            TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
            */
            status = MCSPI_dmaChConfig(
                 gMcspiHandle[CONFIG_MCSPI3],
                 &gConfigMcspi3ChCfg[0U],
                 &gConfigMcspi3DmaChCfg[0U]);
            if(status != SystemP_SUCCESS)
            {
                DebugP_logError("CONFIG_MCSPI3 channel %d config failed !!!\r\n", 0);
            }
        }


        TaskP_Params_init(&tp);
        tp.name      = "MCSPI_MT_MI_CB_REUSE";
        tp.stackSize = MCSPI_TASK_STACK_SIZE;
        tp.stack     = TestMcspi_MtThreadTaskStack[instance];
        tp.priority  = MCSPI_TASK_PRIORITY;
        tp.args      = (void*)(uintptr_t)instance;
        tp.taskMain  = Test_Mcspi_CsdisableWorker;
        tp.coreAffinity = 1 << instance;
        status = TaskP_construct(&TestMcspi_MtThreadTaskObj[instance], &tp);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* Wait for exactly one callback post per transfer */
    for(i=0U;i<TEST_MCSPI_MT_THREADS;i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&TestMcspi_semObj, SystemP_WAIT_FOREVER));
    }

    /* Cleanup */
    for(i=0;i<TEST_MCSPI_MT_THREADS;i++)
    {
        TaskP_destruct(&TestMcspi_MtThreadTaskObj[i]);
    }

    SemaphoreP_destruct(&TestMcspi_semObj);

   // MCSPI_dmaClose(gMcspiHandle[CONFIG_MCSPI3], mcspiChConfigParams);
    MCSPI_dmaClose(gMcspiHandle[CONFIG_MCSPI3],&gConfigMcspi3ChCfg[0U]);
    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);
    MCSPI_close(gMcspiHandle[CONFIG_MCSPI3]);

}

#if !defined A53_CORE
/**
 * @brief Worker: multi-instance DMA/callback/random-mode test.
 *
 * Prepares aligned buffers when required by DMA instances, issues a transfer
 * (blocking or callback depending on configuration), waits for completion and
 * validates the received data. Designed to exercise mixed-mode multi-instance
 * behavior (DMA, callback, polled) depending on instance configuration.
 *
 * @param arg Worker index (cast from uintptr_t).
 */
static void TestMcspi_multithreadMultiInstanceRandomWorker(void *arg)
{
    uint32_t  i;
    int32_t status;
    uint32_t  idx = (uint32_t)(uintptr_t)arg;
    uint8_t   tempTxPtr8[TEST_MCSPI_MT_BYTES];
    uint8_t   tempRxPtr8[TEST_MCSPI_MT_BYTES];
    uint8_t*  txBufPtr;
    uint8_t*  rxBufPtr;
    MCSPI_Transaction spiTransaction;
    SemaphoreP_Object transferDoneMutex;

    /* Fill pattern */
    for(i=0;i<TEST_MCSPI_MT_BYTES;i++)
    {
        /* DMA uses aligned buffers */
        if (idx == CONFIG_MCSPI3)
        {
            gMcspiTxBuffer[i] = (uint8_t)(0xC0 + i);
            gMcspiRxBuffer[i] = 0U;
        }
        else
        {
            tempTxPtr8[i] = (uint8_t)(0xC0 + i);
            tempRxPtr8[i] = 0U;
        }
    }

    status = SemaphoreP_constructBinary(&transferDoneMutex, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MCSPI_Transaction_init(&spiTransaction);
    spiTransaction.channel   = 0;
    spiTransaction.dataSize  = 8;
    spiTransaction.count     = TEST_MCSPI_MT_BYTES;
    spiTransaction.csDisable = TRUE;
    spiTransaction.args      = &transferDoneMutex;

    if (idx == CONFIG_MCSPI0)
    {
        spiTransaction.channel = 1;
    }

    /* Use aligned buffers for DMA transfer */
    if (idx == CONFIG_MCSPI3)
    {
        spiTransaction.txBuf = gMcspiTxBuffer;
        spiTransaction.rxBuf = gMcspiRxBuffer;
        txBufPtr = &gMcspiTxBuffer[0];
        rxBufPtr = &gMcspiRxBuffer[0];

        CacheP_wb(&gMcspiTxBuffer[0U], sizeof(gMcspiTxBuffer), CacheP_TYPE_ALLD);
        CacheP_wb(&gMcspiRxBuffer[0U], sizeof(gMcspiRxBuffer), CacheP_TYPE_ALLD);
    }
    else
    {
        spiTransaction.txBuf = tempTxPtr8;
        spiTransaction.rxBuf = tempRxPtr8;
        txBufPtr = &tempTxPtr8[0];
        rxBufPtr = &tempRxPtr8[0];
    }

    if (idx != CONFIG_MCSPI4)
    {
        /* Small delay for all instances other than master
           This is to ensure slave is ready before master */
        ClockP_sleep(1);
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, MCSPI_transfer(gMcspiHandle[idx], &spiTransaction));

    /* Wait for callback for instances configured with callback option */
    if ((idx == CONFIG_MCSPI3) || (idx == CONFIG_MCSPI0) || (idx == CONFIG_MCSPI4))
    {
        SemaphoreP_pend(&transferDoneMutex, SystemP_WAIT_FOREVER);
        TEST_ASSERT_EQUAL_INT32(MCSPI_TRANSFER_COMPLETED, spiTransaction.status);
    }

    if (idx == CONFIG_MCSPI3)
    {
        /* Invalidate cache for DMA transfer */
        CacheP_inv(&gMcspiRxBuffer[0U], sizeof(gMcspiRxBuffer), CacheP_TYPE_ALLD);
    }

    /* Verify */
    for(i=0;i<TEST_MCSPI_MT_BYTES;i++)
    {
        if(txBufPtr[i] != rxBufPtr[i])
        {
            status = SystemP_FAILURE;   /* Data mismatch */
            DebugP_log("Data Mismatch at offset %d (instance %u)\r\n", i, idx);
            break;
        }
    }

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    SemaphoreP_post(&TestMcspi_semObj);

    SemaphoreP_destruct(&transferDoneMutex);

    TaskP_exit();
}

/**
 * @brief Test harness: multi-instance random/combined-mode case.
 *
 * Configures several MCSPI instances according to the provided parameters (some
 * instances may use DMA, others callbacks or polled mode), spawns a worker per
 * instance, and waits for each worker to complete. This exercises mixed-mode
 * behavior across instances and validates data integrity for each.
 *
 * @param args Pointer to MCSPI_TestParams controlling open/chconfig behavior.
 */
void TestMcspi_multithreadMultiInstanceRandom(void *args)
{
    uint32_t i;
    uint32_t instance;
    int32_t status;
    MCSPI_TestParams   *testParams = (MCSPI_TestParams *)args;
    TaskP_Params tp;
    MCSPI_OpenParams   *mcspiOpenParams;
    MCSPI_ChConfig     *mcspiChConfigParams;

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
    SemaphoreP_constructCounting(&TestMcspi_semObj,0, TEST_MCSPI_MT_MULTI_CHANNEL_THREADS));

    for (instance=0;instance<TEST_MCSPI_MT_MULTI_CHANNEL_THREADS;instance++)
    {
        switch (instance)
        {
            case CONFIG_MCSPI1:
                TestMcspi_setParamsIns1(testParams, testParams->testcaseId);
                break;
            case CONFIG_MCSPI3:
                TestMcspi_setParamsIns3(testParams, testParams->testcaseId);
                break;
            case CONFIG_MCSPI4:
                TestMcspi_setParamsIns4(testParams, testParams->testcaseId);
                break;
            default:
                break;
        }

        mcspiOpenParams = &(testParams->mcspiOpenParams);
        mcspiChConfigParams = &(testParams->mcspiChConfigParams);

        if(gMcspiHandle[instance])
        {
            if (instance == CONFIG_MCSPI3)
            {
                status = MCSPI_dmaClose(gMcspiHandle[CONFIG_MCSPI3], mcspiChConfigParams);
                TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
            }

            MCSPI_close(gMcspiHandle[instance]);
            gMcspiHandle[instance]=NULL;
        }

        gMcspiHandle[instance] = MCSPI_open(instance, mcspiOpenParams);
        TEST_ASSERT_NOT_NULL(gMcspiHandle[instance]);

        status = MCSPI_chConfig(gMcspiHandle[instance], mcspiChConfigParams);

        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        if (instance == CONFIG_MCSPI3)
        {
            status = MCSPI_dmaChConfig(gMcspiHandle[instance], mcspiChConfigParams,
                                       &gConfigMcspi3DmaChCfg[0U]);
            TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        }

        TaskP_Params_init(&tp);
        tp.name      = "MCSPI_MT_MI_CB_REUSE";
        tp.stackSize = MCSPI_TASK_STACK_SIZE;
        tp.stack     = TestMcspi_MtThreadTaskStack[instance];
        tp.priority  = MCSPI_TASK_PRIORITY;
        tp.args      = (void*)(uintptr_t)instance;
        tp.taskMain  = TestMcspi_multithreadMultiInstanceRandomWorker;
        tp.coreAffinity = 1 << instance;
        status = TaskP_construct(&TestMcspi_MtThreadTaskObj[instance], &tp);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    }

    /* Wait for exactly one callback post per transfer */
    for(i=0U;i<TEST_MCSPI_MT_MULTI_CHANNEL_THREADS;i++)
    {
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&TestMcspi_semObj, SystemP_WAIT_FOREVER));
    }

    /* Cleanup */
    for(i=0;i<TEST_MCSPI_MT_MULTI_CHANNEL_THREADS;i++)
    {
        TaskP_destruct(&TestMcspi_MtThreadTaskObj[i]);
    }

    SemaphoreP_destruct(&TestMcspi_semObj);

    MCSPI_dmaClose(gMcspiHandle[CONFIG_MCSPI3], mcspiChConfigParams);
    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]); gMcspiHandle[CONFIG_MCSPI0]=NULL;
    MCSPI_close(gMcspiHandle[CONFIG_MCSPI1]); gMcspiHandle[CONFIG_MCSPI1]=NULL;
    MCSPI_close(gMcspiHandle[CONFIG_MCSPI3]); gMcspiHandle[CONFIG_MCSPI3]=NULL;
    MCSPI_close(gMcspiHandle[CONFIG_MCSPI4]); gMcspiHandle[CONFIG_MCSPI4]=NULL;
}

/**
 * @brief Test case: slave initially times out, then succeeds after master runs.
 *
 * Phase 1: Configure an MCSPI instance in slave mode and attempt a transfer
 *          with a short timeout while no master is present. Depending on the
 *          configured transfer mode (blocking vs callback) the test asserts a
 *          timeout/failure.
 * Phase 2: Start a master instance (in a separate task), then issue a second
 *          slave transfer with a longer timeout and verify the transfer
 *          completes and the received data matches the transmitted pattern.
 *
 * @param args Pointer to MCSPI_TestParams used for master configuration.
 */
static void TestMcspi_slaveTimeout(void *args)
{
    int32_t status;
    uint32_t i;
    MCSPI_TestParams   *testParamsMaster = (MCSPI_TestParams *)args;
    MCSPI_OpenParams   *mcspiOpenParamsMaster = (&testParamsMaster->mcspiOpenParams);
    MCSPI_ChConfig     *mcspiChConfigParamsMaster = (&testParamsMaster->mcspiChConfigParams);

    MCSPI_TestParams   testParamsSlave;
    MCSPI_OpenParams   *mcspiOpenParamsSlave;
    MCSPI_ChConfig     *mcspiChConfigParamsSlave;

    uint8_t   tempTxPtr8[TEST_MCSPI_MT_BYTES];
    uint8_t   tempRxPtr8[TEST_MCSPI_MT_BYTES];
    MCSPI_Transaction spiTransaction;
    SemaphoreP_Object transferDoneMutex;

    TaskP_Params tp;

    /* Construct semaphores */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
    SemaphoreP_constructCounting(&TestMcspi_semObj,0, 1));

    status = SemaphoreP_constructBinary(&transferDoneMutex, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* ---------------- Phase 1 : Slave with short timeout expecting no master ---------------- */
    TestMcspi_setParamsIns4(&testParamsSlave, testParamsMaster->testcaseId);
    mcspiOpenParamsSlave = &(testParamsSlave.mcspiOpenParams);
    mcspiChConfigParamsSlave = &(testParamsSlave.mcspiChConfigParams);

    if(gMcspiHandle[CONFIG_MCSPI4])
    {
         MCSPI_close(gMcspiHandle[CONFIG_MCSPI4]);
         gMcspiHandle[CONFIG_MCSPI4]=NULL;
    }

    gMcspiHandle[CONFIG_MCSPI4] = MCSPI_open(CONFIG_MCSPI4, mcspiOpenParamsSlave);
    TEST_ASSERT_NOT_NULL(gMcspiHandle[CONFIG_MCSPI4]);
    status = MCSPI_chConfig(gMcspiHandle[CONFIG_MCSPI4], mcspiChConfigParamsSlave);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Fill pattern */
    for(i=0;i<TEST_MCSPI_MT_BYTES;i++)
    {
        tempTxPtr8[i] = (uint8_t)(0xC0 + i);
        tempRxPtr8[i] = 0U;
    }

    MCSPI_Transaction_init(&spiTransaction);
    spiTransaction.channel   = 0;
    spiTransaction.dataSize  = 8;
    spiTransaction.count     = TEST_MCSPI_MT_BYTES;
    spiTransaction.csDisable = TRUE;
    spiTransaction.txBuf = tempTxPtr8;
    spiTransaction.rxBuf = tempRxPtr8;
    spiTransaction.args      = &transferDoneMutex;

    status = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI4], &spiTransaction);

    /* One test case handles callback mode and other handles blocking mode */
    if (testParamsMaster->testcaseId == 8433)
    {
        /* Blocking mode */
        TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
        TEST_ASSERT_EQUAL_INT32(MCSPI_TRANSFER_TIMEOUT, spiTransaction.status);
    }
    else
    {
        /* Callback mode */
        status = SemaphoreP_pend(&transferDoneMutex, (MCSPI_SLAVE_TIMEOUT_MS + MCSPI_SLAVE_TIMEOUT_MS));
        TEST_ASSERT_EQUAL_INT32(SystemP_TIMEOUT , status);

        MCSPI_transferCancel(gMcspiHandle[CONFIG_MCSPI4]);
    }

    /* ---------------- Phase 2 : Spawn master, perform successful exchange ---------------- */

    uint32_t instance = CONFIG_MCSPI0; /* Master instance */

    if(gMcspiHandle[CONFIG_MCSPI0])
    {
        MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);
        gMcspiHandle[CONFIG_MCSPI0]=NULL;
    }

    gMcspiHandle[CONFIG_MCSPI0] = MCSPI_open(CONFIG_MCSPI0, mcspiOpenParamsMaster);
    TEST_ASSERT_NOT_NULL(gMcspiHandle[CONFIG_MCSPI0]);
    status = MCSPI_chConfig(gMcspiHandle[CONFIG_MCSPI0], mcspiChConfigParamsMaster);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MCSPI_Transaction_init(&spiTransaction);
    spiTransaction.channel   = 0;
    spiTransaction.dataSize  = 8;
    spiTransaction.count     = TEST_MCSPI_MT_BYTES;
    spiTransaction.csDisable = TRUE;
    spiTransaction.txBuf = tempTxPtr8;
    spiTransaction.rxBuf = tempRxPtr8;
    spiTransaction.args      = &transferDoneMutex;

    /* Construct master task */
    TaskP_Params_init(&tp);
    tp.name      = "MCSPI_MT_SLAVE_TIMEOUT_MASTER";
    tp.stackSize = MCSPI_TASK_STACK_SIZE;
    tp.stack     = TestMcspi_MtThreadTaskStack[0];
    tp.priority  = MCSPI_TASK_PRIORITY;
    tp.args      = (void*)(uintptr_t)(instance);
    tp.taskMain  = TestMcspi_multithreadMultiInstanceRandomWorker;
    tp.coreAffinity = 1;
    status = TaskP_construct(&TestMcspi_MtThreadTaskObj[0], &tp);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI4], &spiTransaction); /* Blocks until master drives */

    if (testParamsMaster->testcaseId == 8433)
    {
        /* Blocking mode */
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        TEST_ASSERT_EQUAL_INT32(MCSPI_TRANSFER_COMPLETED, spiTransaction.status);
    }
    else
    {
        /* Callback mode */
        status = SemaphoreP_pend(&transferDoneMutex, (MCSPI_SLAVE_TIMEOUT_MS + MCSPI_SLAVE_TIMEOUT_MS));
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS , status);
        //TEST_ASSERT_EQUAL_INT32(MCSPI_TRANSFER_COMPLETED, spiTransaction.status); //BUG: Getting transfer_started only
    }

    /* Wait for master task to finish */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&TestMcspi_semObj, SystemP_WAIT_FOREVER));

    /* Verify */
    for(i=0;i<TEST_MCSPI_MT_BYTES;i++)
    {
        if(tempTxPtr8[i] != tempRxPtr8[i])
        {
            status = SystemP_FAILURE;   /* Data mismatch */
            DebugP_log("Data Mismatch at offset %d \r\n", i);
            break;
        }
    }
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    TaskP_destruct(&TestMcspi_MtThreadTaskObj[0]);
    SemaphoreP_destruct(&TestMcspi_semObj);

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]); gMcspiHandle[CONFIG_MCSPI0]=NULL;
    MCSPI_close(gMcspiHandle[CONFIG_MCSPI4]); gMcspiHandle[CONFIG_MCSPI4]=NULL;
}
#endif

/**
 * @brief Populate default MCSPI parameters for the primary instance.
 *
 * Fills in attr/open/channel configuration fields with sane defaults and then
 * applies test-case-specific adjustments based on tcId (e.g. callback mode,
 * DMA enable, data size changes, input select). This is used to prepare the
 * MCSPI_TestParams passed to test harnesses.
 *
 * @param testParams Pointer to structure to fill
 * @param tcId       Test case identifier that selects specialized options
 */
static void TestMcspi_setParamsIns0(MCSPI_TestParams *testParams, uint32_t tcId)
{
    MCSPI_Config     *config = &gMcspiConfig[CONFIG_MCSPI0];
    MCSPI_Attrs      *attrParams = (MCSPI_Attrs *)config->attrs;
    MCSPI_OpenParams *openParams = &(testParams->mcspiOpenParams);
    MCSPI_ChConfig   *chConfigParams = &(testParams->mcspiChConfigParams);

    /* Default Attribute Parameters */
    attrParams->baseAddr           = MCSPI0_BASE_ADDRESS;
    attrParams->inputClkFreq       = 50000000U;
    attrParams->intrNum            = MCSPI0_INT_NUM;
    attrParams->operMode           = MCSPI_OPER_MODE_INTERRUPT;
    attrParams->intrPriority       = 4U;
    attrParams->chMode             = MCSPI_CH_MODE_SINGLE;
    attrParams->pinMode            = MCSPI_PINMODE_4PIN;
    attrParams->initDelay          = MCSPI_INITDLY_0;

    /* Default Open Parameters */
    openParams->transferMode           = MCSPI_TRANSFER_MODE_BLOCKING;
    openParams->transferTimeout        = SystemP_WAIT_FOREVER;
    openParams->transferCallbackFxn    = NULL;
    openParams->msMode                 = MCSPI_MS_MODE_MASTER;
    openParams->mcspiDmaIndex          = -1;

    /* Default Channel Config Parameters */
    chConfigParams->chNum              = MCSPI_CHANNEL_1;
    chConfigParams->frameFormat        = MCSPI_FF_POL0_PHA0;
    chConfigParams->bitRate            = 50000000;
    chConfigParams->csPolarity         = MCSPI_CS_POL_LOW;
    testParams->dataSize               = 32;
    chConfigParams->trMode             = MCSPI_TR_MODE_TX_RX;
    chConfigParams->inputSelect        = MCSPI_IS_D0;
    chConfigParams->dpe0               = MCSPI_DPE_ENABLE;
    chConfigParams->dpe1               = MCSPI_DPE_DISABLE;
    chConfigParams->slvCsSelect        = MCSPI_SLV_CS_SELECT_0;
    chConfigParams->startBitEnable     = FALSE;
    chConfigParams->startBitPolarity   = MCSPI_SB_POL_LOW;
    chConfigParams->csIdleTime         = MCSPI_TCS0_0_CLK;
    chConfigParams->defaultTxData      = 0x0U;
    chConfigParams->txFifoTrigLvl      = 16U;
    chConfigParams->rxFifoTrigLvl      = 16U;
    testParams->testcaseId             = tcId;
    switch (tcId)
    {
       case 8408:
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = TestMcspi_multithreadCallback;
            testParams->dataSize               = 8;
            break;

       case 8785:
            testParams->dataSize               = 8;
            break;

        case 8421:
            testParams->dataSize               = 8;
            break;

        case 8422:
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = TestMcspi_multithreadCallback;
            testParams->dataSize               = 8;
            break;

        case 8431:
        case 8433:
        case 8434:
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = TestMcspi_multithreadCallback;
            testParams->dataSize               = 8;
            chConfigParams->inputSelect        = MCSPI_IS_D1;
            chConfigParams->bitRate            = 1000000;
            break;

        case 8432:
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = TestMcspi_multithreadCallback;
            testParams->dataSize               = 8;
            break;
        case 8435:
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = TestMcspi_multithreadCallback;
            testParams->dataSize               = 8;
            break;
    }
    return;
}

/**
 * @brief Populate MCSPI parameters for instance CONFIG_MCSPI1.
 *
 * Similar to TestMcspi_setParamsIns0 but tailored to instance 1's base address
 * and defaults. Adjusts behavior for specific test ids as needed.
 */
static void TestMcspi_setParamsIns1(MCSPI_TestParams *testParams, uint32_t tcId)
{
    MCSPI_Config     *config = &gMcspiConfig[CONFIG_MCSPI1];
    MCSPI_Attrs      *attrParams = (MCSPI_Attrs *)config->attrs;
    MCSPI_OpenParams *openParams = &(testParams->mcspiOpenParams);
    MCSPI_ChConfig   *chConfigParams = &(testParams->mcspiChConfigParams);

    /* Default Attribute Parameters */
    attrParams->baseAddr           = MCSPI1_BASE_ADDRESS;
    attrParams->inputClkFreq       = 50000000U;
    attrParams->intrNum            = MCSPI1_INT_NUM;
    attrParams->operMode           = MCSPI_OPER_MODE_INTERRUPT;
    attrParams->intrPriority       = 4U;
    attrParams->chMode             = MCSPI_CH_MODE_SINGLE;
    attrParams->pinMode            = MCSPI_PINMODE_4PIN;
    attrParams->initDelay          = MCSPI_INITDLY_0;

    /* Default Open Parameters */
    openParams->transferMode           = MCSPI_TRANSFER_MODE_BLOCKING;
    openParams->transferTimeout        = SystemP_WAIT_FOREVER;
    openParams->transferCallbackFxn    = NULL;
    openParams->msMode                 = MCSPI_MS_MODE_MASTER;
    openParams->mcspiDmaIndex          = -1;

    /* Default Channel Config Parameters */
    chConfigParams->chNum              = MCSPI_CHANNEL_0;
    chConfigParams->frameFormat        = MCSPI_FF_POL0_PHA0;
    chConfigParams->bitRate            = 50000000;
    chConfigParams->csPolarity         = MCSPI_CS_POL_LOW;
    testParams->dataSize               = 32;
    chConfigParams->trMode             = MCSPI_TR_MODE_TX_RX;
    chConfigParams->inputSelect        = MCSPI_IS_D0;
    chConfigParams->dpe0               = MCSPI_DPE_ENABLE;
    chConfigParams->dpe1               = MCSPI_DPE_DISABLE;
    chConfigParams->slvCsSelect        = MCSPI_SLV_CS_SELECT_0;
    chConfigParams->startBitEnable     = FALSE;
    chConfigParams->startBitPolarity   = MCSPI_SB_POL_LOW;
    chConfigParams->csIdleTime         = MCSPI_TCS0_0_CLK;
    chConfigParams->defaultTxData      = 0x0U;
    chConfigParams->txFifoTrigLvl      = 16U;
    chConfigParams->rxFifoTrigLvl      = 16U;
    switch (tcId)
    {
       case 8421:
            testParams->dataSize               = 8;
            break;

        case 8422:
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = TestMcspi_multithreadCallback;
            testParams->dataSize               = 8;
            break;

        case 8432:
            attrParams->operMode           = MCSPI_OPER_MODE_POLLED;
            testParams->dataSize               = 8;
            break;

    }
    return;
}

/**
 * @brief Populate MCSPI parameters for instance CONFIG_MCSPI3.
 *
 * Sets defaults appropriate for instance 3 (including DMA-capable options)
 * and applies per-test overrides such as enabling DMA for certain test ids.
 */
static void TestMcspi_setParamsIns3(MCSPI_TestParams *testParams, uint32_t tcId)
{
    MCSPI_Config     *config = &gMcspiConfig[CONFIG_MCSPI3];
    MCSPI_Attrs      *attrParams = (MCSPI_Attrs *)config->attrs;
    MCSPI_OpenParams *openParams = &(testParams->mcspiOpenParams);
    MCSPI_ChConfig   *chConfigParams = &(testParams->mcspiChConfigParams);

    /* Default Attribute Parameters */
    attrParams->baseAddr           = MCSPI3_BASE_ADDRESS;
    attrParams->inputClkFreq       = 50000000U;
    attrParams->intrNum            = MCSPI3_INT_NUM;
    attrParams->operMode           = MCSPI_OPER_MODE_INTERRUPT;
    attrParams->intrPriority       = 4U;
    attrParams->chMode             = MCSPI_CH_MODE_SINGLE;
    attrParams->pinMode            = MCSPI_PINMODE_4PIN;
    attrParams->initDelay          = MCSPI_INITDLY_0;

    /* Default Open Parameters */
    openParams->transferMode           = MCSPI_TRANSFER_MODE_BLOCKING;
    openParams->transferTimeout        = SystemP_WAIT_FOREVER;
    openParams->transferCallbackFxn    = NULL;
    openParams->msMode                 = MCSPI_MS_MODE_MASTER;
    openParams->mcspiDmaIndex          = -1;

    /* Default Channel Config Parameters */
    chConfigParams->chNum              = MCSPI_CHANNEL_0;
    chConfigParams->frameFormat        = MCSPI_FF_POL0_PHA0;
    chConfigParams->bitRate            = 50000000;
    chConfigParams->csPolarity         = MCSPI_CS_POL_LOW;
    testParams->dataSize               = 32;
    chConfigParams->trMode             = MCSPI_TR_MODE_TX_RX;
    chConfigParams->inputSelect        = MCSPI_IS_D0;
    chConfigParams->dpe0               = MCSPI_DPE_ENABLE;
    chConfigParams->dpe1               = MCSPI_DPE_DISABLE;
    chConfigParams->slvCsSelect        = MCSPI_SLV_CS_SELECT_0;
    chConfigParams->startBitEnable     = FALSE;
    chConfigParams->startBitPolarity   = MCSPI_SB_POL_LOW;
    chConfigParams->csIdleTime         = MCSPI_TCS0_0_CLK;
    chConfigParams->defaultTxData      = 0x0U;
    chConfigParams->txFifoTrigLvl      = 16U;
    chConfigParams->rxFifoTrigLvl      = 16U;
    switch (tcId)
    {
       case 8421:
            testParams->dataSize               = 8;
            break;

        case 8422:
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = TestMcspi_multithreadCallback;
            testParams->dataSize               = 8;
            break;

        case 8431:
            attrParams->operMode               = MCSPI_OPER_MODE_DMA;
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = TestMcspi_multithreadCallback;
            testParams->dataSize               = 8;
            openParams->mcspiDmaIndex          = 0;
            break;

        case 8432:
            attrParams->operMode               = MCSPI_OPER_MODE_DMA;
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = TestMcspi_multithreadCallback;
            testParams->dataSize               = 8;
            openParams->mcspiDmaIndex          = 0;
            break;

        case 8435:
            attrParams->operMode               = MCSPI_OPER_MODE_DMA;
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = TestMcspi_multithreadCallback;
            testParams->dataSize               = 8;
            openParams->mcspiDmaIndex          = 0;
            break;
    }
    return;
}

#if !defined A53_CORE
/**
 * @brief Populate MCSPI parameters for instance CONFIG_MCSPI4.
 *
 * Sets defaults for instance 4 and applies mode changes required by tests
 * exercising slave behavior and timeouts.
 */
static void TestMcspi_setParamsIns4(MCSPI_TestParams *testParams, uint32_t tcId)
{
    MCSPI_Config     *config = &gMcspiConfig[CONFIG_MCSPI4];
    MCSPI_Attrs      *attrParams = (MCSPI_Attrs *)config->attrs;
    MCSPI_OpenParams *openParams = &(testParams->mcspiOpenParams);
    MCSPI_ChConfig   *chConfigParams = &(testParams->mcspiChConfigParams);

    /* Default Attribute Parameters */
    attrParams->baseAddr           = MCSPI2_BASE_ADDRESS;
    attrParams->inputClkFreq       = 50000000U;
    attrParams->intrNum            = MCSPI2_INT_NUM;
    attrParams->operMode           = MCSPI_OPER_MODE_INTERRUPT;
    attrParams->intrPriority       = 4U;
    attrParams->chMode             = MCSPI_CH_MODE_SINGLE;
    attrParams->pinMode            = MCSPI_PINMODE_4PIN;
    attrParams->initDelay          = MCSPI_INITDLY_0;

    /* Default Open Parameters */
    openParams->transferMode           = MCSPI_TRANSFER_MODE_BLOCKING;
    openParams->transferTimeout        = SystemP_WAIT_FOREVER;
    openParams->transferCallbackFxn    = NULL;
    openParams->msMode                 = MCSPI_MS_MODE_MASTER;
    openParams->mcspiDmaIndex          = -1;

    /* Default Channel Config Parameters */
    chConfigParams->chNum              = MCSPI_CHANNEL_0;
    chConfigParams->frameFormat        = MCSPI_FF_POL0_PHA0;
    chConfigParams->bitRate            = 50000000;
    chConfigParams->csPolarity         = MCSPI_CS_POL_LOW;
    testParams->dataSize               = 32;
    chConfigParams->trMode             = MCSPI_TR_MODE_TX_RX;
    chConfigParams->inputSelect        = MCSPI_IS_D0;
    chConfigParams->dpe0               = MCSPI_DPE_ENABLE;
    chConfigParams->dpe1               = MCSPI_DPE_DISABLE;
    chConfigParams->slvCsSelect        = MCSPI_SLV_CS_SELECT_0;
    chConfigParams->startBitEnable     = FALSE;
    chConfigParams->startBitPolarity   = MCSPI_SB_POL_LOW;
    chConfigParams->csIdleTime         = MCSPI_TCS0_0_CLK;
    chConfigParams->defaultTxData      = 0x0U;
    chConfigParams->txFifoTrigLvl      = 16U;
    chConfigParams->rxFifoTrigLvl      = 16U;
    switch (tcId)
    {
        case 8431:
            openParams->msMode                 = MCSPI_MS_MODE_SLAVE;
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = TestMcspi_multithreadCallback;
            testParams->dataSize               = 8;
            chConfigParams->bitRate            = 1000000;
            break;

        case 8432:
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = TestMcspi_multithreadCallback;
            testParams->dataSize               = 8;
            break;

        case 8433:
            openParams->msMode                 = MCSPI_MS_MODE_SLAVE;
            openParams->transferTimeout        = MCSPI_SLAVE_TIMEOUT_MS;
            testParams->dataSize               = 8;
            chConfigParams->inputSelect        = MCSPI_IS_D1;
            chConfigParams->bitRate            = 1000000;
            break;

        case 8434:
            openParams->msMode                 = MCSPI_MS_MODE_SLAVE;
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = TestMcspi_multithreadCallback;
            openParams->transferTimeout        = MCSPI_SLAVE_TIMEOUT_MS;
            testParams->dataSize               = 8;
            chConfigParams->inputSelect        = MCSPI_IS_D1;
            chConfigParams->bitRate            = 1000000;
            break;
    }
    return;
}
#endif

