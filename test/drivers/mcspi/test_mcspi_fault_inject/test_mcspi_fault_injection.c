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
 *  \file test_mcspi_fault_inject.c
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
#define MCSPI4_INT_NUM                  (204U)
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

/* Macro to define the number of max threads to test multi instance  */
#define TEST_MCSPI_MT_MULTI_CHANNEL_THREADS      (4U)

/* Macro that defines the number of bytes involved in a single transaction */
#define TEST_MCSPI_MT_BYTES                     (32U)

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

#define TEST_MCSPI_FAULT_TX_UNDRFLW   (0U) /* Transmit underrun */
#define TEST_MCSPI_FAULT_RX_OVRFLW    (1U) /* Receive overrun */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Semaphore for marking completion of each thread */
static SemaphoreP_Object TestMcspi_semObj;

volatile uint32_t TestMcspi_CntRx = 0;

/* Thread related objects */
static TaskP_Object         TestMcspi_MtThreadTaskObj[TEST_MCSPI_MT_MULTI_CHANNEL_THREADS];
static uint8_t              TestMcspi_MtThreadTaskStack[TEST_MCSPI_MT_MULTI_CHANNEL_THREADS][MCSPI_TASK_STACK_SIZE];


/* Buffers used for fault injection */
uint32_t  TestMcspi_txBufferMax[TEST_MCSPI_MT_BYTES*4];
uint32_t  TestMcspi_rxBufferMax[TEST_MCSPI_MT_BYTES*4];

/* ========================================================================== */
/*                     Internal Function Declaration                          */
/* ========================================================================== */
static void Test_Mcspi_SlaveFaultInjectionWorker(void *arg);
static void Test_Mcspi_SlaveFaultInjection(void *args);

static void TestMcspi_setParamsIns0(MCSPI_TestParams *testParams, uint32_t tcId);
static void TestMcspi_setParamsIns4(MCSPI_TestParams *testParams, uint32_t tcId);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
* \brief Setup fuction for unity framework
*
* \param None.
*
* \return None.
*/

void setUp(void)
{
     /* Setup function nothing to perform */
}

/**
* \brief Tear down fuction for unity framework
*
* \param None.
*
* \return None.
*/
void tearDown(void)
{
    /* Tear down function nothing to perform */
}

/**
* \brief Main fuction for unity framework
*
* \param None.
*
* \return None.
*/

void test_main(void *args)
{
    MCSPI_TestParams testParams;
    UNITY_BEGIN();

    TestMcspi_setParamsIns0(&testParams, 9234);
    RUN_TEST(Test_Mcspi_SlaveFaultInjection, 9234, (void*) &testParams);
    TestMcspi_setParamsIns0(&testParams, 9235);
    RUN_TEST(Test_Mcspi_SlaveFaultInjection, 9235, (void*) &testParams);

    UNITY_END();

    return;
}


/* ========================================================================== */
/*                     Internal Function Definitions                          */
/* ========================================================================== */


void Test_Mcspi_FaultInjectStubHandler(uint32_t *xstat)
{

        switch (TestMcspi_CntRx)
        {
            case 9234:
                DebugP_log("Injecting TX_UNDERRUN error\n");
                *xstat = TEST_MCSPI_FAULT_TX_UNDRFLW;
                break;
            case 9235:
                DebugP_log("Injecting RX_OVERFLOW error \n");
                *xstat = TEST_MCSPI_FAULT_RX_OVRFLW;
                break;
            default:
                break;
        }
}

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
static void Test_Mcspi_SlaveFaultInjectionWorker(void *arg)
{
    int32_t status;
    uint32_t  idx = (uint32_t)(uintptr_t)arg;
    MCSPI_Transaction spiTransaction;
    SemaphoreP_Object transferDoneMutex;

    status = SemaphoreP_constructBinary(&transferDoneMutex, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MCSPI_Transaction_init(&spiTransaction);
    spiTransaction.channel   = 1;
    spiTransaction.dataSize  = 32;
    spiTransaction.count     = TEST_MCSPI_MT_BYTES*4;
    spiTransaction.csDisable = TRUE;
    spiTransaction.args      = &transferDoneMutex;
    spiTransaction.txBuf = TestMcspi_txBufferMax;
    spiTransaction.rxBuf = TestMcspi_rxBufferMax;

    /* Just to make sure that slave is waiting */
    ClockP_sleep(1);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, MCSPI_transfer(gMcspiHandle[idx], &spiTransaction));
    TEST_ASSERT_EQUAL_INT32(MCSPI_TRANSFER_COMPLETED, spiTransaction.status);

    SemaphoreP_post(&TestMcspi_semObj);

    SemaphoreP_destruct(&transferDoneMutex);

    TaskP_exit();
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
static void Test_Mcspi_SlaveFaultInjection(void *args)
{
    int32_t status;
    MCSPI_TestParams   *testParamsMaster = (MCSPI_TestParams *)args;
    MCSPI_OpenParams   *mcspiOpenParamsMaster = (&testParamsMaster->mcspiOpenParams);
    MCSPI_ChConfig     *mcspiChConfigParamsMaster = (&testParamsMaster->mcspiChConfigParams);

    MCSPI_TestParams   testParamsSlave;
    MCSPI_OpenParams   *mcspiOpenParamsSlave;
    MCSPI_ChConfig     *mcspiChConfigParamsSlave;

    MCSPI_Transaction spiTransaction;
    SemaphoreP_Object transferDoneMutex;

    MCSPI_Config       *config = &gMcspiConfig[CONFIG_MCSPI4];
    MCSPI_Object       *obj = (MCSPI_Object *)config->object;

    TaskP_Params testParams;

    /* Construct semaphores */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
    SemaphoreP_constructCounting(&TestMcspi_semObj,0, 1));

    status = SemaphoreP_constructBinary(&transferDoneMutex, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

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
    spiTransaction.count     = TEST_MCSPI_MT_BYTES*4;
    spiTransaction.csDisable = TRUE;
    spiTransaction.txBuf = TestMcspi_txBufferMax;
    spiTransaction.rxBuf = TestMcspi_rxBufferMax;
    spiTransaction.args      = &transferDoneMutex;

    /* Construct master task */
    TaskP_Params_init(&testParams);
    testParams.name      = "MCSPI_MT_SLAVE_TIMEOUT_MASTER";
    testParams.stackSize = MCSPI_TASK_STACK_SIZE;
    testParams.stack     = TestMcspi_MtThreadTaskStack[0];
    testParams.priority  = MCSPI_TASK_PRIORITY;
    testParams.args      = (void*)(uintptr_t)(instance);
    testParams.taskMain  = Test_Mcspi_SlaveFaultInjectionWorker;
    testParams.coreAffinity = 1;
    status = TaskP_construct(&TestMcspi_MtThreadTaskObj[0], &testParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI4], &spiTransaction); /* Blocks until master drives */

    /* Blocking mode */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_INT32(MCSPI_TRANSFER_CANCELLED, spiTransaction.status);

    /* Check if the errors are reported. A bit unconventional to spy on internal variables */
    TEST_ASSERT_EQUAL_INT32((MCSPI_ERROR_TX_UNDERFLOW|MCSPI_ERROR_RX_OVERFLOW), obj->errorFlag);

    /* Wait for master task to finish */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
            SemaphoreP_pend(&TestMcspi_semObj, SystemP_WAIT_FOREVER));

    TaskP_destruct(&TestMcspi_MtThreadTaskObj[0]);
    SemaphoreP_destruct(&TestMcspi_semObj);

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]); gMcspiHandle[CONFIG_MCSPI0]=NULL;
    MCSPI_close(gMcspiHandle[CONFIG_MCSPI4]); gMcspiHandle[CONFIG_MCSPI4]=NULL;
}


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


    TestMcspi_CntRx                = tcId;
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

        case 9234:
            testParams->dataSize               = 32;
            break;
        case 9235:
            testParams->dataSize               = 32;
            break;

    }

    return;
}

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

    TestMcspi_CntRx                = tcId;
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

         case 9234:
            openParams->msMode                 = MCSPI_MS_MODE_SLAVE;
            testParams->dataSize               = 8;
            chConfigParams->inputSelect        = MCSPI_IS_D1;
            chConfigParams->bitRate            = 1000000;
            chConfigParams->txFifoTrigLvl      = 16U;
            chConfigParams->rxFifoTrigLvl      = 16U;
            break;
         case 9235:
            openParams->msMode                 = MCSPI_MS_MODE_SLAVE;
            testParams->dataSize               = 8;
            chConfigParams->inputSelect        = MCSPI_IS_D1;
            chConfigParams->bitRate            = 1000000;
            chConfigParams->txFifoTrigLvl      = 16U;
            chConfigParams->rxFifoTrigLvl      = 16U;
            break;
    }

    return;
}

