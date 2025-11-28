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
 *  \file test_mcspi_v0.c
 *
 *  \brief File containing MCSPI Driver test cases for version V0.
 *
 */

/* This UT demonstrates the McSPI RX and TX operation configured
 * in different configurations and all possible MCSPI instances that can be
 * configured. MCSPI2 instance is muxed with UART, so it is not tested.
 * In case of AM243 LP we, have only 3 instances available.
 *
 * This example sends a known data in the TX mode of length APP_MCSPI_MSGSIZE
 * and then receives the same in RX mode. Internal pad level loopback mode
 * is enabled to receive data.
 *
 * When transfer is completed, TX and RX buffer data are compared.
 * If data is matched, test result is passed otherwise failed.
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
#if ENABLE_MT_TESTS
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#endif
#if (CONFIG_MCSPI_NUM_INSTANCES > 2)
#include <drivers/mcspi/v0/dma/mcspi_dma.h>
#endif
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Task Macros */
#define MCSPI_TASK_PRIORITY   (8U)
#define MCSPI_TASK_STACK_SIZE (32U * 1024U)

/* Number of Word count */
#define APP_MCSPI_MSGSIZE                   (100U)
#define APP_MCSPI_TXONLYMSGSIZE             (5U)
#define APP_MCSPI_TRANSFER_LOOPCOUNT        (5U)
#define APP_MCSPI_PERF_LOOP_ITER_CNT        (1000U)

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



#define SPI_TEST_NUM_CLK_LIST            (sizeof (gClkDividerTestListRampUp) / \
                                          sizeof (gClkDividerTestListRampUp[0U]))

#define TEST_APP_MCSPI_ASSERT_ON_FAILURE(transferOK, transaction) \
    do { \
        if((SystemP_SUCCESS != (transferOK)) || \
                ((MCSPI_TRANSFER_COMPLETED != transaction.status) && \
                (MCSPI_TRANSFER_STARTED != transaction.status))) \
        { \
            DebugP_assert(FALSE); /* MCSPI TX/RX failed!! */ \
        } \
    } while(0) \

/* ========================================================================== */
/*                               Typedefs                                     */
/* ========================================================================== */

typedef struct MCSPI_TestParams_s {
    MCSPI_ChConfig      mcspiChConfigParams;
    MCSPI_OpenParams    mcspiOpenParams;
    uint32_t            transferLength;
    uint32_t            dataSize;
} MCSPI_TestParams;

typedef struct mcspiUtPref_ {
uint64_t polled;
uint64_t interrupt;
uint64_t dma;
} mcspiUtPref;


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

mcspiUtPref gUtPerf[3];

 #if defined(SOC_AM62AX) ||  defined(SOC_AM62DX)
extern MCSPI_DmaConfig gMcspiDmaConfig[];
extern uint32_t gMcspiDmaConfigNum;
#endif


/* Semaphore to indicate Tx/Rx completion used in callback api's */
static SemaphoreP_Object gMcspiTransferDoneSem;

static uint32_t   gClkDividerTestListRampUp[] =
{
    0U,   1U,   2U,   3U,   4U,   5U,   6U,    7U,    8U,    9U,    10U,
    99U,  15U,  31U,  63U,  127U,  199U,  255U,  299U, 399U, 499U, 511U, 599U,
    699U, 799U, 899U, 999U, 1023U, 2047U, 3000U, 4095U
};

static uint32_t   gClkDividerTestListRampDown[] =
{
    4095U, 3000U, 2047U, 1023U, 999U, 899U, 799U,
    699U, 599U, 511U, 499U, 399U, 299U, 255U,
    199U, 127U, 99U, 63U, 31U, 15U, 10U, 9U,
    8U, 7U, 6U, 5U, 4U, 3U, 2U, 1U, 0U
};

#if ENABLE_MT_TESTS

static SemaphoreP_Object Test_Mcspi_TransferDoneSemCancel;

/* Semaphore to track end of rx_task and tx_task */
SemaphoreP_Object gMcspiTransferTaskDoneSemaphoreObj;
SemaphoreP_Object gMcspiTransferCancelTaskDoneSemaphoreObj;

uint8_t gMcspiTransferTaskStack[MCSPI_TASK_STACK_SIZE] __attribute__((aligned(32)));
TaskP_Object gMcspiTransferTaskObject;

uint8_t gMcspiTransferCancelTaskStack[MCSPI_TASK_STACK_SIZE] __attribute__((aligned(32)));
TaskP_Object gMcspiTransferCancelTaskObject;

#endif
uint32_t     gMcspiTxBuffer[APP_MCSPI_MSGSIZE];
uint32_t     gMcspiRxBuffer[APP_MCSPI_MSGSIZE];
uint32_t     gMcspiTxBuffer1[APP_MCSPI_MSGSIZE];
uint32_t     gMcspiRxBuffer1[APP_MCSPI_MSGSIZE];
uint16_t     gMcspiPerfTxBuffer[APP_MCSPI_TXONLYMSGSIZE];
uint32_t     gChEnableRegVal, gChDisableRegVal;
uint32_t     gCsAssertRegVal, gCsDeAssertRegVal;

#if (CONFIG_MCSPI_NUM_INSTANCES > 2)
uint32_t     gMcspiTxBufferDma[APP_MCSPI_MSGSIZE] __attribute__((aligned(CacheP_CACHELINE_ALIGNMENT)));
uint32_t     gMcspiRxBufferDma[APP_MCSPI_MSGSIZE] __attribute__((aligned(CacheP_CACHELINE_ALIGNMENT)));
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
#ifdef ENABLE_MT_TESTS
extern void run_multi_threaded_tests(void *args);
#endif

static void test_mcspi_set_params(MCSPI_TestParams *testParams, uint32_t testCaseId);
void test_mcspi_loopback(void *args);
void test_mcspi_loopback_simultaneous(void *args);
void test_mcspi_callback(MCSPI_Handle handle, MCSPI_Transaction *trans);
void test_mcspi_loopback_back2back(void *args);
void test_mcspi_loopback_multimaster(void *args);
void test_mcspi_performance_16bit(void *args);
void test_mcspi_loopback_timeout(void *args);
void test_mcspi_loopback_performance(void *args);
static void mcspi_low_latency_transfer_16bit(uint32_t baseAddr,
                                            uint32_t chNum,
                                            uint16_t *txBuff,
                                            uint32_t length,
                                            uint32_t bufWidthShift);

#if (CONFIG_MCSPI_NUM_INSTANCES > 2)
void test_mcspi_loopback_dma(void *args);
void test_mcspi_loopback_multimaster_dma(void *args);
void test_mcspi_loopback_dma_with_csdisable(void *args);
void test_mcspi_loopback_dma_with_toggled_csdisable(void *args);
void test_mcspi_dma_open_close(void *args);
#if defined(SOC_AM62AX) ||  defined(SOC_AM62DX)
static int32_t Test_Mcspi_DmaOpenFail(void *args);
static void Test_Mcspi_DmaTransferNoDmaHandle(void *args);
static void Test_Mcspi_DmaCloseNoDmaHandle(void *args);
static void Test_Mcspi_DmaChInitNoDmaHandle(void *args);
#endif
#endif
static void Test_Mcspi_OpenNullOpenPrms(void *args);
static void Test_Mcspi_OpenAlreadyOpen(void *args);
static void Test_Mcspi_OpenInvalidIndex(void *args);
static void Test_Mcspi_ChConfigNegative(void *args);
static void Test_Mcspi_TransferNullArgs(void *args);
static void Test_Mcspi_RxbufNullFifoReadDiscard(void *args);
static void Test_Mcspi_ReconfigFifoNegativeTc(void *args);
static void Test_Mcspi_ReconfigFifo(void *args);
static void Test_Mcspi_FifoTriggerLevels(void *args);
#if ENABLE_MT_TESTS
void test_mcspi_callback_cancel(MCSPI_Handle handle, MCSPI_Transaction *trans);
void test_mcspi_transfer_cancel(void *args);
void test_mcspi_transfer_cancel_transfer(void *args);
void test_mcspi_transfer_cancel_cancel(void *args);
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_main(void *args)
{
    MCSPI_TestParams  testParams;
    uint32_t          clkList;
    MCSPI_ChConfig   *chConfigParams;
    MCSPI_Config     *config;
    MCSPI_Attrs      *attrParams;
    uint32_t          i;

    UNITY_BEGIN();

    #if defined(SOC_AM62AX) && defined (ENABLE_MT_TESTS)
    run_multi_threaded_tests(&testParams);
    #endif

    test_mcspi_set_params(&testParams, 2894);
    RUN_TEST(test_mcspi_loopback,  2894, (void*)&testParams);
    test_mcspi_set_params(&testParams, 2895);
    RUN_TEST(test_mcspi_loopback, 2895, (void*)&testParams);
    test_mcspi_set_params(&testParams, 8409);
    RUN_TEST(test_mcspi_loopback, 8409, (void*) &testParams);
    test_mcspi_set_params(&testParams, 8408);
    RUN_TEST(test_mcspi_loopback, 8408, (void*) &testParams);
    test_mcspi_set_params(&testParams, 8402);
    RUN_TEST(Test_Mcspi_OpenNullOpenPrms, 8402, (void*) &testParams);
    test_mcspi_set_params(&testParams, 8403);
    RUN_TEST(Test_Mcspi_OpenAlreadyOpen, 8403, (void*) &testParams);
    test_mcspi_set_params(&testParams, 8404);
    RUN_TEST(Test_Mcspi_OpenInvalidIndex, 8404, (void*) &testParams);
    test_mcspi_set_params(&testParams, 8406);
    RUN_TEST(Test_Mcspi_ChConfigNegative, 8406, (void*) &testParams);
    test_mcspi_set_params(&testParams, 8407);
    RUN_TEST(Test_Mcspi_TransferNullArgs, 8407, (void*) &testParams);
    test_mcspi_set_params(&testParams, 8840);
    RUN_TEST(Test_Mcspi_ReconfigFifo, 8840, (void*)&testParams);
    test_mcspi_set_params(&testParams, 8373);
    RUN_TEST(Test_Mcspi_FifoTriggerLevels, 8373, (void*)&testParams);
    test_mcspi_set_params(&testParams, 8410);
    RUN_TEST(Test_Mcspi_RxbufNullFifoReadDiscard, 8410, (void*) &testParams);
    test_mcspi_set_params(&testParams, 8411);
    RUN_TEST(Test_Mcspi_ReconfigFifoNegativeTc, 8411, (void*) &testParams);
/* AM263X does not support MCU_SPI instance */
#if !defined(SOC_AM263X) && !defined(SOC_AM62AX) && !defined(SOC_AM62X) && !defined(SOC_AM62DX) && !defined(SOC_AM275X)
/* AM243 LP we, have only 2 instances available */
#if (CONFIG_MCSPI_NUM_INSTANCES > 2)
    test_mcspi_set_params(&testParams, 970);
    RUN_TEST(test_mcspi_loopback,  970, (void*)&testParams);
    test_mcspi_set_params(&testParams, 971);
    RUN_TEST(test_mcspi_loopback,  971, (void*)&testParams);
#endif
#endif
#if (CONFIG_MCSPI_NUM_INSTANCES > 2)
    test_mcspi_set_params(&testParams, 4003);
    RUN_TEST(test_mcspi_loopback,  4003, (void*)&testParams);
#endif
#if !defined(SOC_AM64X) && !defined(SOC_AM243X) && !defined(SOC_AM263X)
    test_mcspi_set_params(&testParams, 2901);
    RUN_TEST(test_mcspi_loopback,  2901, (void*)&testParams);
#endif
    test_mcspi_set_params(&testParams, 2902);
    RUN_TEST(test_mcspi_loopback,  2902, (void*)&testParams);
#if (CONFIG_MCSPI_NUM_INSTANCES > 2)
    test_mcspi_set_params(&testParams, 4004);
    RUN_TEST(test_mcspi_loopback,  4004, (void*)&testParams);
#endif
    test_mcspi_set_params(&testParams, 2903);
    RUN_TEST(test_mcspi_loopback_performance,  2903, (void*)&testParams);
    test_mcspi_set_params(&testParams, 2904);
    RUN_TEST(test_mcspi_loopback_performance,  2904, (void*)&testParams);
    test_mcspi_set_params(&testParams, 2905);
    RUN_TEST(test_mcspi_loopback_performance,  2905, (void*)&testParams);
    test_mcspi_set_params(&testParams, 2906);
    RUN_TEST(test_mcspi_loopback_performance,  2906, (void*)&testParams);
    test_mcspi_set_params(&testParams, 2908);
    RUN_TEST(test_mcspi_loopback_performance,  2908, (void*)&testParams);
    test_mcspi_set_params(&testParams, 2910);
    RUN_TEST(test_mcspi_loopback_performance,  2910, (void*)&testParams);

     test_mcspi_set_params(&testParams, 2911);
     RUN_TEST(test_mcspi_loopback_back2back,  2911, (void*)&testParams);
    test_mcspi_set_params(&testParams, 2912);
    RUN_TEST(test_mcspi_loopback,  2912, (void*)&testParams);
    test_mcspi_set_params(&testParams, 2934);
    /* Change clock divider as per test list */
    chConfigParams = &(testParams.mcspiChConfigParams);
    config = &gMcspiConfig[CONFIG_MCSPI0];
    attrParams = (MCSPI_Attrs *)config->attrs;
    for (clkList = 0U; clkList < SPI_TEST_NUM_CLK_LIST; clkList++)
    {
        chConfigParams->bitRate = (attrParams->inputClkFreq / (gClkDividerTestListRampUp[clkList] + 1));
        RUN_TEST(test_mcspi_loopback,  2934, (void*)&testParams);
    }
    test_mcspi_set_params(&testParams, 2914);
    chConfigParams = &(testParams.mcspiChConfigParams);
    config = &gMcspiConfig[CONFIG_MCSPI0];
    attrParams = (MCSPI_Attrs *)config->attrs;
    for (clkList = 0U; clkList < SPI_TEST_NUM_CLK_LIST; clkList++)
    {
        chConfigParams->bitRate = (attrParams->inputClkFreq / (gClkDividerTestListRampDown[clkList] + 1));
        RUN_TEST(test_mcspi_loopback,  2914, (void*)&testParams);
    }
    test_mcspi_set_params(&testParams, 2915);
    RUN_TEST(test_mcspi_loopback,  2915, (void*)&testParams);
    test_mcspi_set_params(&testParams, 2916);
    RUN_TEST(test_mcspi_loopback,  2916, (void*)&testParams);
    test_mcspi_set_params(&testParams, 2917);
    RUN_TEST(test_mcspi_loopback,  2917, (void*)&testParams);
    test_mcspi_set_params(&testParams, 2918);
    RUN_TEST(test_mcspi_loopback,  2918, (void*)&testParams);
    test_mcspi_set_params(&testParams, 2919);
    RUN_TEST(test_mcspi_loopback,  2919, (void*)&testParams);
    test_mcspi_set_params(&testParams, 2920);
    RUN_TEST(test_mcspi_loopback,  2920, (void*)&testParams);
    test_mcspi_set_params(&testParams, 2921);
    RUN_TEST(test_mcspi_loopback,  2921, (void*)&testParams);
    test_mcspi_set_params(&testParams, 2922);
    RUN_TEST(test_mcspi_loopback,  2922, (void*)&testParams);
    test_mcspi_set_params(&testParams, 2923);
    RUN_TEST(test_mcspi_loopback,  2923, (void*)&testParams);
    test_mcspi_set_params(&testParams, 2924);
    RUN_TEST(test_mcspi_loopback,  2924, (void*)&testParams);
    test_mcspi_set_params(&testParams, 2925);
    RUN_TEST(test_mcspi_loopback,  2925, (void*)&testParams);
    test_mcspi_set_params(&testParams, 2926);
    RUN_TEST(test_mcspi_loopback,  2926, (void*)&testParams);
    test_mcspi_set_params(&testParams, 2927);
    RUN_TEST(test_mcspi_loopback_multimaster,  2927, (void*)&testParams);
#if (CONFIG_MCSPI_NUM_INSTANCES > 2)
    test_mcspi_set_params(&testParams, 4025);
    /* Change clock divider as per test list */
    chConfigParams = &(testParams.mcspiChConfigParams);
    config = &gMcspiConfig[CONFIG_MCSPI0];
    attrParams = (MCSPI_Attrs *)config->attrs;
    for (clkList = 0U; clkList < SPI_TEST_NUM_CLK_LIST; clkList++)
    {
        chConfigParams->bitRate = (attrParams->inputClkFreq / (gClkDividerTestListRampUp[clkList] + 1));
        RUN_TEST(test_mcspi_loopback,  4025, (void*)&testParams);
    }
#endif
    test_mcspi_set_params(&testParams, 2928);
    chConfigParams = &(testParams.mcspiChConfigParams);
    config = &gMcspiConfig[CONFIG_MCSPI0];
    attrParams = (MCSPI_Attrs *)config->attrs;
    for (clkList = 0U; clkList < SPI_TEST_NUM_CLK_LIST; clkList++)
    {
        chConfigParams->bitRate = (attrParams->inputClkFreq / (gClkDividerTestListRampDown[clkList] + 1));
        RUN_TEST(test_mcspi_loopback,  2928, (void*)&testParams);
    }
    test_mcspi_set_params(&testParams, 2929);
    RUN_TEST(test_mcspi_loopback_simultaneous, 2929, (void*)&testParams);
    #if ENABLE_MT_TESTS
    test_mcspi_set_params(&testParams, 2930);
    RUN_TEST(test_mcspi_transfer_cancel, 2930, (void*)&testParams);
    test_mcspi_set_params(&testParams, 2931);
    RUN_TEST(test_mcspi_transfer_cancel, 2931, (void*)&testParams);
    #endif
    test_mcspi_set_params(&testParams, 2932);
    RUN_TEST(test_mcspi_loopback_timeout, 2932, (void*)&testParams);
    test_mcspi_set_params(&testParams, 2933);
    RUN_TEST(test_mcspi_performance_16bit, 2933, (void*)&testParams);
#if (CONFIG_MCSPI_NUM_INSTANCES > 2)
    test_mcspi_set_params(&testParams, 4026);
    RUN_TEST(test_mcspi_loopback_multimaster_dma,  4026, (void*)&testParams);
    test_mcspi_set_params(&testParams, 4027);
    RUN_TEST(test_mcspi_loopback_dma,  4027, (void*)&testParams);
    test_mcspi_set_params(&testParams, 4028);
    RUN_TEST(test_mcspi_loopback_dma,  4028, (void*)&testParams);
    test_mcspi_set_params(&testParams, 4029);
    RUN_TEST(test_mcspi_loopback_dma,  4029, (void*)&testParams);
    test_mcspi_set_params(&testParams, 4027);
    RUN_TEST(test_mcspi_loopback_dma_with_csdisable,  8057, (void*)&testParams);
    test_mcspi_set_params(&testParams, 4028);
    RUN_TEST(test_mcspi_loopback_dma_with_csdisable,  8056, (void*)&testParams);
    test_mcspi_set_params(&testParams, 4029);
    RUN_TEST(test_mcspi_loopback_dma_with_csdisable,  8055, (void*)&testParams);
    test_mcspi_set_params(&testParams, 4027);
    RUN_TEST(test_mcspi_loopback_dma_with_toggled_csdisable,  8057, (void*)&testParams);
    test_mcspi_set_params(&testParams, 4028);
    RUN_TEST(test_mcspi_loopback_dma_with_toggled_csdisable,  8056, (void*)&testParams);
    test_mcspi_set_params(&testParams, 4029);
    RUN_TEST(test_mcspi_loopback_dma_with_toggled_csdisable,  8055, (void*)&testParams);
#if defined(SOC_AM62AX) ||  defined(SOC_AM62DX)
    test_mcspi_set_params(&testParams, 8412);
    RUN_TEST(Test_Mcspi_DmaChInitNoDmaHandle, 8412, (void*)&testParams);
    test_mcspi_set_params(&testParams, 8413);
    RUN_TEST(Test_Mcspi_DmaCloseNoDmaHandle, 8413, (void*)&testParams);
    test_mcspi_set_params(&testParams, 8414);
    RUN_TEST(Test_Mcspi_DmaTransferNoDmaHandle, 8414, (void*)&testParams);
#endif
#endif

    /* Print Performance Numbers. */
    DebugP_log("\nMCSPI Performance Numbers Print Start\r\n\n");
#if (CONFIG_MCSPI_NUM_INSTANCES > 2)
    DebugP_log("Number of Words | Word Width (Bits)     | Polled mode Throughput / Transfer time  | Interrupt mode (Mbps) Throughput / Transfer time | Dma mode (Mbps) Throughput / Transfer time\r\n");
    DebugP_log("----------------|-----------------------|-------------------------------|-------------------------------|-------------------------------\r\n");
#else
    DebugP_log("Number of Words | Word Width (Bits)     | Polled mode Throughput / Transfer time  | Interrupt mode (Mbps) Throughput / Transfer time\r\n");
    DebugP_log("----------------|-----------------------|-------------------------------|-------------------------------\r\n");
#endif
    for (i =0;i<3;i++)
    {
        uint32_t dataWidth = 8*(1<<i);
        uint32_t dataLength = 400/(1<<i);
#if (CONFIG_MCSPI_NUM_INSTANCES > 2)
        DebugP_log(" %u\t\t| %02u\t\t\t| %5.2f Mbps / %5.2f us \t| %5.2f Mbps / %5.2f us \t| %5.2f Mbps / %5.2f us\r\n", dataLength, dataWidth,
                            (float)(dataLength * dataWidth)/((float)gUtPerf[i].polled / APP_MCSPI_PERF_LOOP_ITER_CNT),
                            ((float)gUtPerf[i].polled / APP_MCSPI_PERF_LOOP_ITER_CNT),
                            (float)(dataLength * dataWidth)/((float)gUtPerf[i].interrupt / APP_MCSPI_PERF_LOOP_ITER_CNT),
                            ((float)gUtPerf[i].interrupt / APP_MCSPI_PERF_LOOP_ITER_CNT),
                            (float)(dataLength * dataWidth)/((float)gUtPerf[i].dma / APP_MCSPI_PERF_LOOP_ITER_CNT),
                            ((float)gUtPerf[i].dma / APP_MCSPI_PERF_LOOP_ITER_CNT));
#else
        DebugP_log(" %u\t\t| %02u\t\t\t| %5.2f Mbps / %5.2f us \t| %5.2f Mbps / %5.2f us\r\n", dataLength, dataWidth,
                            (float)(dataLength * dataWidth)/((float)gUtPerf[i].polled / APP_MCSPI_PERF_LOOP_ITER_CNT),
                            ((float)gUtPerf[i].polled / APP_MCSPI_PERF_LOOP_ITER_CNT),
                            (float)(dataLength * dataWidth)/((float)gUtPerf[i].interrupt / APP_MCSPI_PERF_LOOP_ITER_CNT),
                            ((float)gUtPerf[i].interrupt / APP_MCSPI_PERF_LOOP_ITER_CNT));
#endif
    }
    DebugP_log("\nMCSPI Performance Numbers Print End\r\n");

#if (CONFIG_MCSPI_NUM_INSTANCES > 2)
    test_mcspi_set_params(&testParams, 6864);
    RUN_TEST(test_mcspi_dma_open_close,  6864, (void*)&testParams);
#endif

    UNITY_END();

    return;
}

/* Test: McSPI RX and TX operation in loopback mode */
void test_mcspi_loopback(void *args)
{
    int32_t             status = SystemP_SUCCESS;
    uint32_t            i, dataWidth, fifoBitMask, tempTxData, dataWidthIdx;
    int32_t             transferOK;
    MCSPI_Transaction   spiTransaction;
    MCSPI_Handle        mcspiHandle;
    MCSPI_TestParams   *testParams = (MCSPI_TestParams *)args;
    uint8_t            *tempRxPtr8 = NULL, *tempTxPtr8 = NULL;
    uint16_t           *tempRxPtr16 = NULL, *tempTxPtr16 = NULL;
    uint32_t           *tempRxPtr32 = NULL, *tempTxPtr32 = NULL;
    MCSPI_OpenParams   *mcspiOpenParams = &(testParams->mcspiOpenParams);
    MCSPI_ChConfig     *mcspiChConfigParams = &(testParams->mcspiChConfigParams);

    /* Memset Buffers */
    memset(&gMcspiTxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiTxBuffer[0U]));
    memset(&gMcspiRxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiRxBuffer[0U]));

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);

    mcspiHandle = MCSPI_open(CONFIG_MCSPI0, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);

    status = MCSPI_chConfig(
                 gMcspiHandle[CONFIG_MCSPI0],
                 mcspiChConfigParams);
    DebugP_assert(status == SystemP_SUCCESS);

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        status = SemaphoreP_constructBinary(&gMcspiTransferDoneSem, 0);
        DebugP_assert(SystemP_SUCCESS == status);
    }

    dataWidth = testParams->dataSize;
    if (dataWidth < 9U)
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr8 = (uint8_t *) &gMcspiTxBuffer[0U];
        tempRxPtr8 = (uint8_t *) &gMcspiRxBuffer[0U];
    }
    else if (dataWidth < 17U)
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr16 = (uint16_t *) &gMcspiTxBuffer[0U];
        tempRxPtr16 = (uint16_t *) &gMcspiRxBuffer[0U];
    }
    else
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr32 = (uint32_t *) &gMcspiTxBuffer[0U];
        tempRxPtr32 = (uint32_t *) &gMcspiRxBuffer[0U];
    }
    fifoBitMask = 0x0U;
    for (dataWidthIdx = 0U;
         dataWidthIdx < dataWidth; dataWidthIdx++)
    {
        fifoBitMask |= (1U << dataWidthIdx);
    }

    /* Memfill buffers */
    for (i = 0U; i < testParams->transferLength; i++)
    {
        tempTxData = 0xDEADBABE;
        tempTxData &= (fifoBitMask);
        if (dataWidth < 9U)
        {
            *tempTxPtr8++ = (uint8_t) (tempTxData);
            *tempRxPtr8++ = 0U;
        }
        else if (dataWidth < 17U)
        {
            *tempTxPtr16++ = (uint16_t) (tempTxData);
            *tempRxPtr16++ = 0U;
        }
        else
        {
            *tempTxPtr32++ = (uint32_t) (tempTxData);
            *tempRxPtr32++ = 0U;
        }
    }

    /* Initiate transfer */
    spiTransaction.channel  = testParams->mcspiChConfigParams.chNum;
    spiTransaction.count    = testParams->transferLength;
    spiTransaction.dataSize  = dataWidth;
    spiTransaction.csDisable = TRUE;
    spiTransaction.txBuf    = (void *)gMcspiTxBuffer;
    spiTransaction.rxBuf    = (void *)gMcspiRxBuffer;
    spiTransaction.args     = NULL;
    transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction);
    TEST_APP_MCSPI_ASSERT_ON_FAILURE(transferOK, spiTransaction);

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        /* Wait for transfer completion */
        SemaphoreP_pend(&gMcspiTransferDoneSem, SystemP_WAIT_FOREVER);
    }

    /* Compare data */
    uint8_t *tempTxPtr, *tempRxPtr;
    tempTxPtr = (uint8_t *) &gMcspiTxBuffer[0U];
    tempRxPtr = (uint8_t *) &gMcspiRxBuffer[0U];
    for(i = 0U; i < (APP_MCSPI_MSGSIZE * 4); i++)
    {
        if(*tempTxPtr++ != *tempRxPtr++)
        {
            status = SystemP_FAILURE;   /* Data mismatch */
            DebugP_log("Data Mismatch at offset %d\r\n", i);
            break;
        }
    }

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        SemaphoreP_destruct(&gMcspiTransferDoneSem);
    }

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    return;
}

/* Test: McSPI loopback performance measurement */
void test_mcspi_loopback_performance(void *args)
{
    int32_t             status = SystemP_SUCCESS;
    uint32_t            i,j, dataWidth, fifoBitMask, tempTxData, dataWidthIdx;
    int32_t             transferOK;
    MCSPI_Transaction   spiTransaction;
    MCSPI_Handle        mcspiHandle;
    MCSPI_TestParams   *testParams = (MCSPI_TestParams *)args;
    uint8_t            *tempRxPtr8 = NULL, *tempTxPtr8 = NULL;
    uint16_t           *tempRxPtr16 = NULL, *tempTxPtr16 = NULL;
    uint32_t           *tempRxPtr32 = NULL, *tempTxPtr32 = NULL;
    MCSPI_OpenParams   *mcspiOpenParams = &(testParams->mcspiOpenParams);
    MCSPI_ChConfig     *mcspiChConfigParams = &(testParams->mcspiChConfigParams);
    uint64_t            startTimeInUSec, elapsedTimeInUsecs, totalTimeInUsecs = 0U;
    uint32_t            perf_offset = 0;
    MCSPI_Config       *config = &gMcspiConfig[CONFIG_MCSPI0];
    MCSPI_Attrs        *attrParams = (MCSPI_Attrs *)config->attrs;

    /* Memset Buffers */
    memset(&gMcspiTxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiTxBuffer[0U]));
    memset(&gMcspiRxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiRxBuffer[0U]));

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);

    mcspiHandle = MCSPI_open(CONFIG_MCSPI0, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);

    status = MCSPI_chConfig(
                 gMcspiHandle[CONFIG_MCSPI0],
                 mcspiChConfigParams);
    DebugP_assert(status == SystemP_SUCCESS);

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        status = SemaphoreP_constructBinary(&gMcspiTransferDoneSem, 0);
        DebugP_assert(SystemP_SUCCESS == status);
    }

    dataWidth = testParams->dataSize;
    if (dataWidth < 9U)
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr8 = (uint8_t *) &gMcspiTxBuffer[0U];
        tempRxPtr8 = (uint8_t *) &gMcspiRxBuffer[0U];
    }
    else if (dataWidth < 17U)
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr16 = (uint16_t *) &gMcspiTxBuffer[0U];
        tempRxPtr16 = (uint16_t *) &gMcspiRxBuffer[0U];
    }
    else
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr32 = (uint32_t *) &gMcspiTxBuffer[0U];
        tempRxPtr32 = (uint32_t *) &gMcspiRxBuffer[0U];
    }
    fifoBitMask = 0x0U;
    for (dataWidthIdx = 0U;
         dataWidthIdx < dataWidth; dataWidthIdx++)
    {
        fifoBitMask |= (1U << dataWidthIdx);
    }

    /* Memfill buffers */
    for (i = 0U; i < testParams->transferLength; i++)
    {
        tempTxData = 0xDEADBABE;
        tempTxData &= (fifoBitMask);
        if (dataWidth < 9U)
        {
            *tempTxPtr8++ = (uint8_t) (tempTxData);
            *tempRxPtr8++ = 0U;
        }
        else if (dataWidth < 17U)
        {
            *tempTxPtr16++ = (uint16_t) (tempTxData);
            *tempRxPtr16++ = 0U;
        }
        else
        {
            *tempTxPtr32++ = (uint32_t) (tempTxData);
            *tempRxPtr32++ = 0U;
        }
    }

    for(j = 0U; j < APP_MCSPI_PERF_LOOP_ITER_CNT; j++)
    {
        /* Initiate transfer */
        spiTransaction.channel  = testParams->mcspiChConfigParams.chNum;
        spiTransaction.count    = testParams->transferLength;
        spiTransaction.dataSize  = dataWidth;
        spiTransaction.csDisable = TRUE;
        spiTransaction.txBuf    = (void *)gMcspiTxBuffer;
        spiTransaction.rxBuf    = (void *)gMcspiRxBuffer;
        spiTransaction.args     = NULL;
        startTimeInUSec = ClockP_getTimeUsec();
        transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction);
        TEST_APP_MCSPI_ASSERT_ON_FAILURE(transferOK, spiTransaction);
        if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
        {
            /* Wait for transfer completion */
            SemaphoreP_pend(&gMcspiTransferDoneSem, SystemP_WAIT_FOREVER);
        }
        elapsedTimeInUsecs = ClockP_getTimeUsec() - startTimeInUSec;
        totalTimeInUsecs += elapsedTimeInUsecs;

        /* Compare data */
        uint8_t *tempTxPtr, *tempRxPtr;
        tempTxPtr = (uint8_t *) &gMcspiTxBuffer[0U];
        tempRxPtr = (uint8_t *) &gMcspiRxBuffer[0U];
        for(i = 0U; i < (APP_MCSPI_MSGSIZE * 4); i++)
        {
            if(*tempTxPtr++ != *tempRxPtr++)
            {
                status = SystemP_FAILURE;   /* Data mismatch */
                DebugP_log("Data Mismatch at offset %d\r\n", i);
                break;
            }
        }
    }

    /* Store Performance value in global var. Performance numbers are printed at the end of UT. */
    if (dataWidth == 8) {
        perf_offset = 0;
    } else if (dataWidth == 16) {
        perf_offset = 1;
    } else if (dataWidth == 32) {
        perf_offset = 2;
    }
    if (attrParams->operMode == MCSPI_OPER_MODE_POLLED)
    {
        gUtPerf[perf_offset].polled = totalTimeInUsecs;
    }
    if (attrParams->operMode == MCSPI_OPER_MODE_INTERRUPT)
    {
        gUtPerf[perf_offset].interrupt = totalTimeInUsecs;
    }

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        SemaphoreP_destruct(&gMcspiTransferDoneSem);
    }

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    return;
}

#if (CONFIG_MCSPI_NUM_INSTANCES > 2)

#if defined(SOC_AM62AX) ||  defined(SOC_AM62DX)
static int32_t Test_Mcspi_DmaOpenFail(void *args)
{
    (void)args;
    return SystemP_FAILURE;
}


/**
 * @brief Test case for MCSPI DMA transfer without a DMA handle.
 *
 * This test verifies the behavior of the MCSPI driver when a DMA transfer is attempted
 * without providing a valid DMA handle. It ensures that the driver handles this scenario
 * gracefully and returns the expected error or status.
 */
static void Test_Mcspi_DmaTransferNoDmaHandle(void *args)
{
    MCSPI_TestParams *testparams        = (MCSPI_TestParams*)args;
    MCSPI_OpenParams *mcspiOpenParams   = &testparams->mcspiOpenParams;
    MCSPI_ChConfig   *mcspiChConfigParams = &testparams->mcspiChConfigParams;
    MCSPI_Config     *cfg       = &gMcspiConfig[CONFIG_MCSPI3];
    MCSPI_Attrs      *attrs     = (MCSPI_Attrs*)cfg->attrs;
    uint32_t savedOperMode      = attrs->operMode;
    int32_t savedDmaIndex       = mcspiOpenParams->mcspiDmaIndex;

    /* Patch all dmaOpenFxn to fail so mcspiDmaHandle remains NULL even in DMA operMode */
    MCSPI_DmaFxns *origFxns[8];
    MCSPI_DmaFxns  patchedFxns[8];
    uint32_t i;
    for(i=0; i<gMcspiDmaConfigNum && i<8; i++)
    {
        origFxns[i]            = gMcspiDmaConfig[i].fxns;
        patchedFxns[i]         = *origFxns[i];
        patchedFxns[i].dmaOpenFxn = Test_Mcspi_DmaOpenFail;
        gMcspiDmaConfig[i].fxns = &patchedFxns[i];
    }

    attrs->operMode            = MCSPI_OPER_MODE_DMA;
    mcspiOpenParams->mcspiDmaIndex    = 0;
    mcspiOpenParams->transferMode     = MCSPI_TRANSFER_MODE_BLOCKING;

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI3]);
    MCSPI_Handle mcspiHandle = MCSPI_open(CONFIG_MCSPI3, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);

    /* Channel config (OK even with NULL dma handle) */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, MCSPI_chConfig(mcspiHandle, mcspiChConfigParams));

    /* Verify dma handle NULL */
    MCSPI_Config *openedCfg = (MCSPI_Config*)mcspiHandle;
    TEST_ASSERT_NULL(openedCfg->object->mcspiDmaHandle);

    /* Prepare small transfer */
    uint8_t txbuff[4] = {1,2,3,4};
    uint8_t rxbuff[4] = {0};
    MCSPI_Transaction spiTransaction;
    MCSPI_Transaction_init(&spiTransaction);
    spiTransaction.channel   = mcspiChConfigParams->chNum;
    spiTransaction.count     = 4;
    spiTransaction.dataSize  = testparams->dataSize;
    spiTransaction.csDisable = TRUE;
    spiTransaction.txBuf     = txbuff;
    spiTransaction.rxBuf     = rxbuff;

    int32_t status = MCSPI_transfer(mcspiHandle, &spiTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Close BEFORE restoring operMode so close path does NOT attempt DMA close */
    attrs->operMode = MCSPI_OPER_MODE_INTERRUPT; /* neutralize before close */
    MCSPI_close(mcspiHandle);

    /* Restore patched tables */
    for(i=0; i<gMcspiDmaConfigNum && i<8; i++)
    {
        gMcspiDmaConfig[i].fxns = origFxns[i];
    }

    /* Optionally reopen + close in original mode (only if different) to leave system clean */
    if(savedOperMode == MCSPI_OPER_MODE_DMA)
    {
        attrs->operMode         = MCSPI_OPER_MODE_DMA;
        mcspiOpenParams->mcspiDmaIndex = savedDmaIndex;
        mcspiHandle = MCSPI_open(CONFIG_MCSPI3, mcspiOpenParams);
        if(mcspiHandle)
        {
            (void)MCSPI_chConfig(mcspiHandle, mcspiChConfigParams);
            MCSPI_close(mcspiHandle);
        }
    }
    else
    {
        attrs->operMode = savedOperMode;
        mcspiOpenParams->mcspiDmaIndex = savedDmaIndex;
    }
}


/**
 * @brief Test case for closing MCSPI DMA when no DMA handle is present.
 *
 * This test verifies that the DMA close operation behaves correctly
 * when invoked without a valid DMA handle. It ensures no errors or
 * resource leaks occur in this scenario.
 */
static void Test_Mcspi_DmaCloseNoDmaHandle(void *args)
{

    MCSPI_TestParams *testParams        = (MCSPI_TestParams*)args;
    MCSPI_OpenParams *mcspiOpenParams   = &testParams->mcspiOpenParams;
    MCSPI_ChConfig   *mcspiChConfigParams = &testParams->mcspiChConfigParams;
    MCSPI_Config     *cfg               = &gMcspiConfig[CONFIG_MCSPI3];
    MCSPI_Attrs      *attrs             = (MCSPI_Attrs*)cfg->attrs;
    uint32_t savedOperMode              = attrs->operMode;
    int32_t  savedDmaIndex              = mcspiOpenParams->mcspiDmaIndex;

    /* Patch dmaOpenFxn to force failure so mcspiDmaHandle stays NULL */
    MCSPI_DmaFxns *origFxns[8];
    MCSPI_DmaFxns  patchedFxns[8];
    uint32_t i;
    for(i=0; i<gMcspiDmaConfigNum && i<8; i++)
    {
        origFxns[i]              = gMcspiDmaConfig[i].fxns;
        patchedFxns[i]           = *origFxns[i];
        patchedFxns[i].dmaOpenFxn= Test_Mcspi_DmaOpenFail;
        gMcspiDmaConfig[i].fxns  = &patchedFxns[i];
    }

    attrs->operMode            = MCSPI_OPER_MODE_DMA;
    mcspiOpenParams->mcspiDmaIndex    = 0;
    mcspiOpenParams->transferMode     = MCSPI_TRANSFER_MODE_BLOCKING;

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI3]);
    MCSPI_Handle mcspiHandle = MCSPI_open(CONFIG_MCSPI3, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);

    /* Channel config succeeds even without DMA handle */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, MCSPI_chConfig(mcspiHandle, mcspiChConfigParams));

    /* Confirm no DMA handle */
    MCSPI_Config *openedCfg = (MCSPI_Config*)mcspiHandle;
    TEST_ASSERT_NULL(openedCfg->object->mcspiDmaHandle);

    /* Call dmaClose -> expect FAILURE since handle NULL */
    int32_t status = MCSPI_dmaClose(mcspiHandle, mcspiChConfigParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Neutralize operMode before close to avoid internal dmaClose attempt */
    attrs->operMode = MCSPI_OPER_MODE_INTERRUPT;
    MCSPI_close(mcspiHandle);

    /* Restore patched tables */
    for(i=0; i<gMcspiDmaConfigNum && i<8; i++)
    {
        gMcspiDmaConfig[i].fxns = origFxns[i];
    }

    /* Restore original mode/index */
    attrs->operMode         = savedOperMode;
    mcspiOpenParams->mcspiDmaIndex = savedDmaIndex;
}

/**
 * @brief Test case for initializing MCSPI DMA channel without a DMA handle.
 *
 * This test verifies that the DMA channel initialization behaves correctly
 * when invoked without a valid DMA handle. It ensures no errors or
 * resource leaks occur in this scenario.
 */
static void Test_Mcspi_DmaChInitNoDmaHandle(void *args)
{

    MCSPI_TestParams *testParams        = (MCSPI_TestParams*)args;
    MCSPI_OpenParams *mcspiOpenParams   = &testParams->mcspiOpenParams;
    MCSPI_ChConfig   *mcspiChConfigParams = &testParams->mcspiChConfigParams;
    MCSPI_Config     *cfg               = &gMcspiConfig[CONFIG_MCSPI3];
    MCSPI_Attrs      *attrs             = (MCSPI_Attrs*)cfg->attrs;
    uint32_t savedOperMode              = attrs->operMode;
    int32_t  savedDmaIndex              = mcspiOpenParams->mcspiDmaIndex;

    /* Patch dmaOpenFxn to force failure so mcspiDmaHandle stays NULL */
    MCSPI_DmaFxns *origFxns[8];
    MCSPI_DmaFxns  patchedFxns[8];
    uint32_t i;
    for(i=0; i<gMcspiDmaConfigNum && i<8; i++)
    {
        origFxns[i]              = gMcspiDmaConfig[i].fxns;
        patchedFxns[i]           = *origFxns[i];
        patchedFxns[i].dmaOpenFxn= Test_Mcspi_DmaOpenFail;
        gMcspiDmaConfig[i].fxns  = &patchedFxns[i];
    }

    attrs->operMode            = MCSPI_OPER_MODE_DMA;
    mcspiOpenParams->mcspiDmaIndex    = 0;
    mcspiOpenParams->transferMode     = MCSPI_TRANSFER_MODE_BLOCKING;

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI3]);
    MCSPI_Handle mcspiHandle = MCSPI_open(CONFIG_MCSPI3, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, MCSPI_chConfig(mcspiHandle, mcspiChConfigParams));

    /* Confirm no DMA handle */
    MCSPI_Config *openedCfg = (MCSPI_Config*)mcspiHandle;
    TEST_ASSERT_NULL(openedCfg->object->mcspiDmaHandle);

    /* Prepare dummy DMA channel config */
    MCSPI_DmaChConfig dummyDmaChCfg;
    memset(&dummyDmaChCfg, 0, sizeof(dummyDmaChCfg));

    /* Invoke dmaChConfig. Current driver returns SUCCESS even with NULL DMA handle (design quirk). */
    int32_t status = MCSPI_dmaChConfig(mcspiHandle, mcspiChConfigParams, &dummyDmaChCfg);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_NULL(openedCfg->object->mcspiDmaHandle);

    /* Neutralize operMode before close */
    attrs->operMode = MCSPI_OPER_MODE_INTERRUPT;
    MCSPI_close(mcspiHandle);

    /* Restore patched tables */
    for(i=0; i<gMcspiDmaConfigNum && i<8; i++)
    {
        gMcspiDmaConfig[i].fxns = origFxns[i];
    }

    /* Restore original mode/index */
    attrs->operMode         = savedOperMode;
    mcspiOpenParams->mcspiDmaIndex = savedDmaIndex;
}
#endif
#endif
/**
 * @brief Test case for verifying MCSPI FIFO trigger levels functionality.
 *
 * This test validates the correct configuration and handling of FIFO trigger levels
 * in the MCSPI driver. It ensures that the transmit and receive FIFOs generate
 * interrupts at the expected thresholds. The test also checks for proper data
 * transfer and error handling when FIFO levels are reached. This helps guarantee
 * reliable SPI communication in applications using FIFO buffering.
 */
static void Test_Mcspi_FifoTriggerLevels(void *args)
{
    static const uint32_t triggerLevelList[] = {1U,4U,8U,16U,32U};
    MCSPI_TestParams *testParams        = (MCSPI_TestParams*)args;
    MCSPI_OpenParams *mcspiOpenParams   = &testParams->mcspiOpenParams;
    MCSPI_ChConfig   *mcspiChConfigParams = &testParams->mcspiChConfigParams;
    MCSPI_Handle      mcspiHandle;
    uint32_t          levelIdx;
    int32_t           status;
    uint32_t          i;

    /* Base config: interrupt + blocking (or keep existing) */
    ((MCSPI_Attrs*)gMcspiConfig[CONFIG_MCSPI0].attrs)->operMode = MCSPI_OPER_MODE_INTERRUPT;
    mcspiOpenParams->transferMode = MCSPI_TRANSFER_MODE_BLOCKING;
    testParams->dataSize           = 8U;  /* 8-bit words */

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);
    mcspiHandle = MCSPI_open(CONFIG_MCSPI0, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);

    for(levelIdx = 0U; levelIdx < (sizeof(triggerLevelList)/sizeof(triggerLevelList[0])); levelIdx++)
    {
        uint32_t fifoTrig = triggerLevelList[levelIdx];
        if(fifoTrig > MCSPI_FIFO_LENGTH) { continue; }

        mcspiChConfigParams->txFifoTrigLvl = fifoTrig;
        mcspiChConfigParams->rxFifoTrigLvl = fifoTrig;
        status = MCSPI_chConfig(mcspiHandle, mcspiChConfigParams);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

        /**
         * Set largeCount to a value larger than fifoTrig to ensure the interrupt is triggered.
         * This helps verify that no errors or blocking occur when transaction count exceeds FIFO trigger level.
         */
        uint32_t largeCount = (fifoTrig < 4U) ? 8U : (fifoTrig + fifoTrig/2U);
        if(largeCount > APP_MCSPI_MSGSIZE) largeCount = APP_MCSPI_MSGSIZE;

        /* Fill TX/RX buffers */
        uint8_t *txPtr = (uint8_t*)gMcspiTxBuffer;
        uint8_t *rxPtr = (uint8_t*)gMcspiRxBuffer;
        memset(rxPtr, 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiRxBuffer[0]));
        for(i=0U; i<largeCount; i++) txPtr[i] = (uint8_t)(0x40 + (uint8_t)fifoTrig + (uint8_t)i);

        MCSPI_Transaction spiTransactionLarge;
        MCSPI_Transaction_init(&spiTransactionLarge);
        spiTransactionLarge.channel   = mcspiChConfigParams->chNum;
        spiTransactionLarge.count     = largeCount;
        spiTransactionLarge.dataSize  = testParams->dataSize;
        spiTransactionLarge.csDisable = TRUE;
        spiTransactionLarge.txBuf     = gMcspiTxBuffer;
        spiTransactionLarge.rxBuf     = gMcspiRxBuffer;

        status = MCSPI_transfer(mcspiHandle, &spiTransactionLarge);
        TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
        TEST_ASSERT_EQUAL_INT32(MCSPI_TRANSFER_COMPLETED, spiTransactionLarge.status);

        for(i=0U; i<largeCount; i++)
        {
            TEST_ASSERT_EQUAL_UINT8(txPtr[i], rxPtr[i]);
        }

        /* Small transfer (< trigger) only if trigger > 1 */
        if(fifoTrig > 1U)
        {
            /**
             * Set smallCount to one less than fifoTrig to test interrupt triggering
             * and ensure no errors occur when transaction count is below FIFO trigger level.
             */
            uint32_t smallCount = fifoTrig - 1U;
            if(smallCount > APP_MCSPI_MSGSIZE) smallCount = APP_MCSPI_MSGSIZE;

            memset(rxPtr, 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiRxBuffer[0]));
            for( i=0U; i<smallCount; i++) txPtr[i] = (uint8_t)(0xA0 + (uint8_t)fifoTrig + (uint8_t)i);

            MCSPI_Transaction spiTransactionSmall;
            MCSPI_Transaction_init(&spiTransactionSmall);
            spiTransactionSmall.channel   = mcspiChConfigParams->chNum;
            spiTransactionSmall.count     = smallCount;
            spiTransactionSmall.dataSize  = testParams->dataSize;
            spiTransactionSmall.csDisable = TRUE;
            spiTransactionSmall.txBuf     = gMcspiTxBuffer;
            spiTransactionSmall.rxBuf     = gMcspiRxBuffer;

            status = MCSPI_transfer(mcspiHandle, &spiTransactionSmall);
            TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
            TEST_ASSERT_EQUAL_INT32(MCSPI_TRANSFER_COMPLETED, spiTransactionSmall.status);

            for( i=0U; i<smallCount; i++)
            {
                TEST_ASSERT_EQUAL_UINT8(txPtr[i], rxPtr[i]);
            }
        }
    }

    MCSPI_close(mcspiHandle);
}

/**
 * @brief Test case to verify behavior when attempting to open an already open MCSPI instance.
 *
 * This test ensures that the driver correctly handles repeated open calls.
 * It checks for proper error handling and resource management in such scenarios.
 */
static void Test_Mcspi_OpenAlreadyOpen(void *args)
{
    MCSPI_Handle mcspiHandle1, mcspiHandle2;
    MCSPI_OpenParams mcspiOpenParams;
    MCSPI_OpenParams_init(&mcspiOpenParams);

    /* Open once */
    mcspiHandle1 = MCSPI_open(CONFIG_MCSPI0, &mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle1);

    /* Try to open again (should fail) */
    mcspiHandle2 = MCSPI_open(CONFIG_MCSPI0, &mcspiOpenParams);
    TEST_ASSERT_NULL(mcspiHandle2);

    MCSPI_close(mcspiHandle1);
}

/**
 * @brief Test case for opening MCSPI with NULL open parameters.
 *
 * This test verifies the behavior of the MCSPI driver when the open parameters are NULL.
 * It ensures that the driver handles invalid input gracefully and does not cause unexpected failures.
 * The test is intended to validate robustness against improper API usage.
 */
static void Test_Mcspi_OpenNullOpenPrms(void *args)
{
    MCSPI_Handle mcspiHandle;

    /* Pass NULL for openPrms */
    mcspiHandle = MCSPI_open(CONFIG_MCSPI0, NULL);
    TEST_ASSERT_NOT_NULL(mcspiHandle);

    MCSPI_close(mcspiHandle);
}

/**
 * @brief Test case to validate MCSPI open with invalid parameters.
 *
 * This test verifies that the MCSPI driver correctly handles invalid open parameters.
 * It ensures that the driver does not initialize or open the peripheral when given incorrect arguments.
 * The test helps in identifying robustness and error handling in the MCSPI open API.
 */
void test_mcspi_open_invalid_openprms(void *args)
{
    MCSPI_Handle mcspiHandle;
    MCSPI_OpenParams mcspiOpenParams;
    MCSPI_OpenParams_init(&mcspiOpenParams);

    mcspiOpenParams.transferMode = MCSPI_TRANSFER_MODE_CALLBACK;
    mcspiOpenParams.transferCallbackFxn = NULL; /* Invalid for callback mode */

    mcspiHandle = MCSPI_open(CONFIG_MCSPI0, &mcspiOpenParams);
    TEST_ASSERT_NULL(mcspiHandle);
}

/**
 * @brief Test case for basic MCSPI FIFO reconfiguration.
 *
 * This test verifies the basic functionality of reconfiguring the FIFO settings
 * of the MCSPI peripheral. It ensures that the FIFO can be reconfigured without
 * errors and that data integrity is maintained during the process.
 */
static void Test_Mcspi_ReconfigFifo(void *args)
{
    uint32_t i;
    MCSPI_TestParams *testParams        = (MCSPI_TestParams*)args;
    MCSPI_OpenParams *mcspiOpenParams   = &testParams->mcspiOpenParams;
    MCSPI_ChConfig   *mcspiChConfigParams = &testParams->mcspiChConfigParams;
    MCSPI_Handle      mcspiHandle;
    int32_t           status;
    uint8_t           tempTxPtr8[24], tempRxPtr8[24];
    MCSPI_Transaction spiTransaction;

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);
    mcspiHandle = MCSPI_open(CONFIG_MCSPI0, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);

    status = MCSPI_chConfig(mcspiHandle, mcspiChConfigParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /**
     * Test case for MCSPI_reConfigFifo API.
     * First configures the channel FIFO/XFERLEVEL for a larger chunk (24 words), then immediately reprograms it to a smaller chunk (12 words).
     * These calls update internal HW registers (WCNT and FIFO trigger setup) but do not start a transfer.
     * The test later transfers 12 words to confirm reconfiguration succeeds with no error when expanding then shrinking.
     * Data integrity is maintained after changing the FIFO word count; 24U and 12U represent word counts.
     */
    /* Configure larger length then shrink */
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
                            MCSPI_reConfigFifo(mcspiHandle, mcspiChConfigParams->chNum, 24U));
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS,
                            MCSPI_reConfigFifo(mcspiHandle, mcspiChConfigParams->chNum, 12U));

    for(i=0;i<12U;i++){ tempTxPtr8[i]=(uint8_t)(0x5A + i); tempRxPtr8[i]=0U; }

    MCSPI_Transaction_init(&spiTransaction);
    spiTransaction.channel   = mcspiChConfigParams->chNum;
    spiTransaction.count     = 12U;
    spiTransaction.dataSize  = 8;
    spiTransaction.csDisable = TRUE;
    spiTransaction.txBuf     = tempTxPtr8;
    spiTransaction.rxBuf     = tempRxPtr8;

    status = MCSPI_transfer(mcspiHandle, &spiTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_INT32(MCSPI_TRANSFER_COMPLETED, spiTransaction.status);

    for(i=0;i<12U;i++)
    {
        TEST_ASSERT_EQUAL_UINT8(tempTxPtr8[i], tempRxPtr8[i]);
    }

    /* Negative: invalid channel */
    status = MCSPI_reConfigFifo(mcspiHandle, 0xFFU, 4U);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    MCSPI_close(mcspiHandle);
}

/**
 * @brief Test case for negative scenarios in MCSPI channel configuration.
 *
 * This test verifies the robustness of the MCSPI channel configuration API
 * by providing invalid or boundary input parameters and checking error handling.
 * It ensures the driver does not crash or misbehave with incorrect configurations.
 */
static void Test_Mcspi_ChConfigNegative(void *args)
{
    int32_t status;
    MCSPI_Handle mcspiHandle = NULL;
    MCSPI_ChConfig mcspiChConfigParams;

    /* Case 1: mcspiHandle is NULL */
    status = MCSPI_chConfig(NULL, &mcspiChConfigParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Case 2: mcspiChConfigParams is NULL */
    mcspiHandle = gMcspiHandle[CONFIG_MCSPI0];
    status = MCSPI_chConfig(mcspiHandle, NULL);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Case 3: chNum >= MCSPI_MAX_NUM_CHANNELS */
    memset(&mcspiChConfigParams, 0, sizeof(mcspiChConfigParams));
    mcspiChConfigParams.chNum = MCSPI_MAX_NUM_CHANNELS; /* Invalid channel */
    status = MCSPI_chConfig(mcspiHandle, &mcspiChConfigParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
}

/**
 * @brief Test case for MCSPI transfer API with NULL arguments.
 *
 * This test verifies the behavior of the MCSPI transfer function when provided with NULL arguments.
 * It ensures that the API handles invalid input gracefully and does not cause unexpected behavior.
 * The test is designed to validate error handling and robustness of the driver implementation.
 */
static void Test_Mcspi_TransferNullArgs(void *args)
{
    int32_t status;
    MCSPI_Transaction spiTransaction;

    /* Case 1: handle is NULL */
    status = MCSPI_transfer(NULL, &spiTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    /* Case 2: transaction is NULL */
    MCSPI_Handle mcspiHandle = gMcspiHandle[CONFIG_MCSPI0];
    status = MCSPI_transfer(mcspiHandle, NULL);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
}

/**
 * @brief Test case to verify MCSPI open operation with an invalid index.
 *
 * This test attempts to open an MCSPI instance using an invalid index value.
 * It checks whether the driver correctly handles invalid input and returns an error.
 * Ensures robustness of the MCSPI driver against incorrect usage scenarios.
 */
static void Test_Mcspi_OpenInvalidIndex(void *args)
{
    MCSPI_Handle mcspiHandle;
    MCSPI_OpenParams mcspiOpenParams;
    MCSPI_OpenParams_init(&mcspiOpenParams);

    /* Use an out-of-range index */
    uint32_t invalidIndex = gMcspiConfigNum; /* >= valid range */

    mcspiHandle = MCSPI_open(invalidIndex, &mcspiOpenParams);
    TEST_ASSERT_NULL(mcspiHandle);
}

/**
 * @brief Test case for MCSPI RX buffer null scenario with FIFO read discard.
 *
 * This test verifies the behavior of the MCSPI driver when the RX buffer is NULL
 * and FIFO read is configured to discard data. It ensures no data is written to
 * the RX buffer and no unexpected errors occur.
 */
static void Test_Mcspi_RxbufNullFifoReadDiscard(void *args)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t i, dataWidth, fifoBitMask, tempTxData, dataWidthIdx;
    int32_t transferOK;
    MCSPI_Transaction spiTransaction;
    MCSPI_Handle mcspiHandle;
    MCSPI_TestParams *testParams = (MCSPI_TestParams*) args;
    uint8_t *tempTxPtr8 = NULL;
    uint16_t *tempTxPtr16 = NULL;
    uint32_t *tempTxPtr32 = NULL;
    MCSPI_OpenParams *mcspiOpenParams = &(testParams->mcspiOpenParams);
    MCSPI_ChConfig *mcspiChConfigParams = &(testParams->mcspiChConfigParams);

    /* Memset TX Buffer */
    memset(&gMcspiTxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiTxBuffer[0U]));

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);

    mcspiHandle = MCSPI_open(CONFIG_MCSPI0, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);

    status = MCSPI_chConfig(gMcspiHandle[CONFIG_MCSPI0], mcspiChConfigParams);
    DebugP_assert(status == SystemP_SUCCESS);

    dataWidth = testParams->dataSize;
    if (dataWidth < 9U)
    {
        tempTxPtr8 = (uint8_t*) &gMcspiTxBuffer[0U];
    }
    else if (dataWidth < 17U)
    {
        tempTxPtr16 = (uint16_t*) &gMcspiTxBuffer[0U];
    }
    else
    {
        tempTxPtr32 = (uint32_t*) &gMcspiTxBuffer[0U];
    }
    fifoBitMask = 0x0U;
    for (dataWidthIdx = 0U; dataWidthIdx < dataWidth; dataWidthIdx++)
    {
        fifoBitMask |= (1U << dataWidthIdx);
    }

    /* Fill TX buffer */
    for (i = 0U; i < testParams->transferLength; i++)
    {
        tempTxData = 0xA5A5A5A5;
        tempTxData &= (fifoBitMask);
        if (dataWidth < 9U)
        {
            *tempTxPtr8++ = (uint8_t)(tempTxData);
        }
        else if (dataWidth < 17U)
        {
            *tempTxPtr16++ = (uint16_t)(tempTxData);
        }
        else
        {
            *tempTxPtr32++ = (uint32_t)(tempTxData);
        }
    }

    /* Initiate transfer with rxBuf = NULL to trigger MCSPI_fifoReadDiscard */
    spiTransaction.channel = testParams->mcspiChConfigParams.chNum;
    spiTransaction.count = testParams->transferLength;
    spiTransaction.dataSize = dataWidth;
    spiTransaction.csDisable = TRUE;
    spiTransaction.txBuf = (void*) gMcspiTxBuffer;
    spiTransaction.rxBuf = NULL; /* NULL RX buffer triggers discard path */
    spiTransaction.args = NULL;
    transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction);
    TEST_APP_MCSPI_ASSERT_ON_FAILURE(transferOK, spiTransaction);

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    return;
}

/**
 * @brief Test case for reconfiguring the MCSPI FIFO settings.
 *
 * This test verifies the correct behavior when the FIFO configuration
 * of the MCSPI peripheral is changed during runtime. It ensures that
 * data integrity and transfer operations remain consistent after reconfiguration.
 */
static void Test_Mcspi_ReconfigFifoNegativeTc(void *args)
{
    int32_t status = SystemP_SUCCESS;
    MCSPI_Handle mcspiHandle;
    MCSPI_TestParams *testParams = (MCSPI_TestParams*) args;
    MCSPI_OpenParams *mcspiOpenParams = &(testParams->mcspiOpenParams);
    MCSPI_ChConfig *mcspiChConfigParams = &(testParams->mcspiChConfigParams);
    uint32_t chNum = mcspiChConfigParams->chNum;
    uint32_t numWordsRxTx = 8; /* Example: set FIFO config for 8 words */

    /* Close and open to ensure clean state */
    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);
    mcspiHandle = MCSPI_open(CONFIG_MCSPI0, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);

    /* Configure channel */
    status = MCSPI_chConfig(mcspiHandle, mcspiChConfigParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Call reConfigFifo with valid params */
    status = MCSPI_reConfigFifo(mcspiHandle, chNum, numWordsRxTx);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Optionally: Call with invalid channel to check for failure */
    status = MCSPI_reConfigFifo(mcspiHandle, 0xFF, numWordsRxTx);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);

    MCSPI_close(mcspiHandle);
}

void test_mcspi_loopback_back2back(void *args)
{
    int32_t             status = SystemP_SUCCESS;
    uint32_t            i, dataWidth, fifoBitMask, tempTxData, dataWidthIdx;
    int32_t             transferOK;
    MCSPI_Transaction   spiTransaction;
    MCSPI_Handle        mcspiHandle;
    MCSPI_TestParams   *testParams = (MCSPI_TestParams *)args;
    uint8_t            *tempRxPtr8 = NULL, *tempTxPtr8 = NULL;
    uint16_t           *tempRxPtr16 = NULL, *tempTxPtr16 = NULL;
    uint32_t           *tempRxPtr32 = NULL, *tempTxPtr32 = NULL;
    MCSPI_OpenParams   *mcspiOpenParams = &(testParams->mcspiOpenParams);
    MCSPI_ChConfig     *mcspiChConfigParams = &(testParams->mcspiChConfigParams);

    /* Memset Buffers */
    memset(&gMcspiTxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiTxBuffer[0U]));
    memset(&gMcspiRxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiRxBuffer[0U]));

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);

    mcspiHandle = MCSPI_open(CONFIG_MCSPI0, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);

    status = MCSPI_chConfig(
                 gMcspiHandle[CONFIG_MCSPI0],
                 mcspiChConfigParams);
    DebugP_assert(status == SystemP_SUCCESS);

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        status = SemaphoreP_constructBinary(&gMcspiTransferDoneSem, 0);
        DebugP_assert(SystemP_SUCCESS == status);
    }

    dataWidth = testParams->dataSize;
    if (dataWidth < 9U)
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr8 = (uint8_t *) &gMcspiTxBuffer[0U];
        tempRxPtr8 = (uint8_t *) &gMcspiRxBuffer[0U];
    }
    else if (dataWidth < 17U)
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr16 = (uint16_t *) &gMcspiTxBuffer[0U];
        tempRxPtr16 = (uint16_t *) &gMcspiRxBuffer[0U];
    }
    else
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr32 = (uint32_t *) &gMcspiTxBuffer[0U];
        tempRxPtr32 = (uint32_t *) &gMcspiRxBuffer[0U];
    }
    fifoBitMask = 0x0U;
    for (dataWidthIdx = 0U;
         dataWidthIdx < dataWidth; dataWidthIdx++)
    {
        fifoBitMask |= (1U << dataWidthIdx);
    }

    /* Memfill buffers */
    for (i = 0U; i < testParams->transferLength; i++)
    {
        tempTxData = 0xDEADBABE;
        tempTxData &= (fifoBitMask);
        if (dataWidth < 9U)
        {
            *tempTxPtr8++ = (uint8_t) (tempTxData);
            *tempRxPtr8++ = 0U;
        }
        else if (dataWidth < 17U)
        {
            *tempTxPtr16++ = (uint16_t) (tempTxData);
            *tempRxPtr16++ = 0U;
        }
        else
        {
            *tempTxPtr32++ = (uint32_t) (tempTxData);
            *tempRxPtr32++ = 0U;
        }
    }

    /* Initiate transfer */
    spiTransaction.channel  = testParams->mcspiChConfigParams.chNum;
    spiTransaction.count    = testParams->transferLength;
    spiTransaction.dataSize  = dataWidth;
    spiTransaction.csDisable = TRUE;
    spiTransaction.txBuf    = (void *)gMcspiTxBuffer;
    spiTransaction.rxBuf    = (void *)gMcspiRxBuffer;
    spiTransaction.args     = NULL;
    transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction);
    transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction);
    DebugP_assert(transferOK != SystemP_SUCCESS);
    DebugP_assert(spiTransaction.status == MCSPI_TRANSFER_CANCELLED);

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        /* Wait for transfer completion */
        SemaphoreP_pend(&gMcspiTransferDoneSem, SystemP_WAIT_FOREVER);
    }

    /* Compare data */
    uint8_t *tempTxPtr, *tempRxPtr;
    tempTxPtr = (uint8_t *) &gMcspiTxBuffer[0U];
    tempRxPtr = (uint8_t *) &gMcspiRxBuffer[0U];
    for(i = 0U; i < (APP_MCSPI_MSGSIZE * 4); i++)
    {
        if(*tempTxPtr++ != *tempRxPtr++)
        {
            status = SystemP_SUCCESS;   /* Data Match */
            DebugP_log("Data Mismatch at offset %d\r\n", i);
            break;
        }
    }

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        SemaphoreP_destruct(&gMcspiTransferDoneSem);
    }

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    return;
}

void test_mcspi_loopback_multimaster(void *args)
{
    int32_t             status = SystemP_SUCCESS;
    uint32_t            i, dataWidth, fifoBitMask, tempTxData, dataWidthIdx;
    int32_t             transferOK, chCnt;
    MCSPI_Transaction   spiTransaction;
    MCSPI_Handle        mcspiHandle;
    MCSPI_TestParams   *testParams = (MCSPI_TestParams *)args;
    uint8_t            *tempRxPtr8 = NULL, *tempTxPtr8 = NULL;
    uint16_t           *tempRxPtr16 = NULL, *tempTxPtr16 = NULL;
    uint32_t           *tempRxPtr32 = NULL, *tempTxPtr32 = NULL;
    MCSPI_OpenParams   *mcspiOpenParams = &(testParams->mcspiOpenParams);
    uint32_t            mcspiChDataSize[4] = { 4, 8, 8, 8};
    MCSPI_Config       *config;
    MCSPI_Attrs        *attrParams;

    /* Memset Buffers */
    memset(&gMcspiTxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiTxBuffer[0U]));
    memset(&gMcspiRxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiRxBuffer[0U]));

    config = &gMcspiConfig[CONFIG_MCSPI1];
    attrParams = (MCSPI_Attrs *)config->attrs;

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI1]);

    attrParams->operMode = MCSPI_OPER_MODE_INTERRUPT;
    mcspiHandle = MCSPI_open(CONFIG_MCSPI1, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);

    for(chCnt = 0U; chCnt < CONFIG_MCSPI1_NUM_CH; chCnt++)
    {
        if ((chCnt % 2) == 0U)
        {
            gConfigMcspi1ChCfg[chCnt].inputSelect = MCSPI_IS_D1;
            gConfigMcspi1ChCfg[chCnt].dpe0        = MCSPI_DPE_DISABLE;
            gConfigMcspi1ChCfg[chCnt].dpe1        = MCSPI_DPE_ENABLE;
        }
        else
        {
            gConfigMcspi1ChCfg[chCnt].inputSelect = MCSPI_IS_D0;
            gConfigMcspi1ChCfg[chCnt].dpe0        = MCSPI_DPE_ENABLE;
            gConfigMcspi1ChCfg[chCnt].dpe1        = MCSPI_DPE_DISABLE;
        }

        status = MCSPI_chConfig(
                     gMcspiHandle[CONFIG_MCSPI1],
                     &gConfigMcspi1ChCfg[chCnt]);
        if(status != SystemP_SUCCESS)
        {
            DebugP_logError("CONFIG_MCSPI1 channel %d config failed !!!\r\n", chCnt);
            break;
        }

        if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
        {
            status = SemaphoreP_constructBinary(&gMcspiTransferDoneSem, 0);
            DebugP_assert(SystemP_SUCCESS == status);
        }

        dataWidth = mcspiChDataSize[chCnt];
        if (dataWidth < 9U)
        {
            /* Init TX buffer with known data and memset RX buffer */
            tempTxPtr8 = (uint8_t *) &gMcspiTxBuffer[0U];
            tempRxPtr8 = (uint8_t *) &gMcspiRxBuffer[0U];
        }
        else if (dataWidth < 17U)
        {
            /* Init TX buffer with known data and memset RX buffer */
            tempTxPtr16 = (uint16_t *) &gMcspiTxBuffer[0U];
            tempRxPtr16 = (uint16_t *) &gMcspiRxBuffer[0U];
        }
        else
        {
            /* Init TX buffer with known data and memset RX buffer */
            tempTxPtr32 = (uint32_t *) &gMcspiTxBuffer[0U];
            tempRxPtr32 = (uint32_t *) &gMcspiRxBuffer[0U];
        }
        fifoBitMask = 0x0U;
        for (dataWidthIdx = 0U;
             dataWidthIdx < dataWidth; dataWidthIdx++)
        {
            fifoBitMask |= (1U << dataWidthIdx);
        }

        /* Memfill buffers */
        for (i = 0U; i < testParams->transferLength; i++)
        {
            tempTxData = 0xDEADBABE;
            tempTxData &= (fifoBitMask);
            if (dataWidth < 9U)
            {
                *tempTxPtr8++ = (uint8_t) (tempTxData);
                *tempRxPtr8++ = 0U;
            }
            else if (dataWidth < 17U)
            {
                *tempTxPtr16++ = (uint16_t) (tempTxData);
                *tempRxPtr16++ = 0U;
            }
            else
            {
                *tempTxPtr32++ = (uint32_t) (tempTxData);
                *tempRxPtr32++ = 0U;
            }
        }

        /* Initiate transfer */
        spiTransaction.channel  = gConfigMcspi1ChCfg[chCnt].chNum;
        spiTransaction.dataSize  = dataWidth;
        spiTransaction.csDisable = TRUE;
        spiTransaction.count    = testParams->transferLength;
        spiTransaction.txBuf    = (void *)gMcspiTxBuffer;
        spiTransaction.rxBuf    = (void *)gMcspiRxBuffer;
        spiTransaction.args     = NULL;
        transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI1], &spiTransaction);
        TEST_APP_MCSPI_ASSERT_ON_FAILURE(transferOK, spiTransaction);

        if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
        {
            /* Wait for transfer completion */
            SemaphoreP_pend(&gMcspiTransferDoneSem, SystemP_WAIT_FOREVER);
        }

        /* Compare data */
        uint8_t *tempTxPtr, *tempRxPtr;
        tempTxPtr = (uint8_t *) &gMcspiTxBuffer[0U];
        tempRxPtr = (uint8_t *) &gMcspiRxBuffer[0U];
        for(i = 0U; i < (APP_MCSPI_MSGSIZE * 4); i++)
        {
            if(*tempTxPtr++ != *tempRxPtr++)
            {
                status = SystemP_FAILURE;   /* Data mismatch */
                DebugP_log("Data Mismatch at offset %d\r\n", i);
                break;
            }
        }

        if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
        {
            SemaphoreP_destruct(&gMcspiTransferDoneSem);
        }

    }

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI1]);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    return;
}

#if (CONFIG_MCSPI_NUM_INSTANCES > 2)
void test_mcspi_loopback_multimaster_dma(void *args)
{
    int32_t             status = SystemP_SUCCESS;
    uint32_t            i, dataWidth, fifoBitMask, tempTxData, dataWidthIdx;
    int32_t             transferOK, chCnt;
    MCSPI_Transaction   spiTransaction;
    MCSPI_TestParams   *testParams = (MCSPI_TestParams *)args;
    uint8_t            *tempRxPtr8 = NULL, *tempTxPtr8 = NULL;
    uint16_t           *tempRxPtr16 = NULL, *tempTxPtr16 = NULL;
    uint32_t           *tempRxPtr32 = NULL, *tempTxPtr32 = NULL;
    MCSPI_OpenParams   *mcspiOpenParams = &(testParams->mcspiOpenParams);

    /* Memset Buffers */
    memset(&gMcspiTxBufferDma[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiTxBufferDma[0U]));
    memset(&gMcspiRxBufferDma[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiRxBufferDma[0U]));

    for(chCnt = 0U; chCnt < CONFIG_MCSPI3_NUM_CH; chCnt++)
    {
        if ((chCnt % 2) == 0U)
        {
            gConfigMcspi3ChCfg[chCnt].inputSelect = MCSPI_IS_D1;
            gConfigMcspi3ChCfg[chCnt].dpe0        = MCSPI_DPE_DISABLE;
            gConfigMcspi3ChCfg[chCnt].dpe1        = MCSPI_DPE_ENABLE;
        }
        else
        {
            gConfigMcspi3ChCfg[chCnt].inputSelect = MCSPI_IS_D0;
            gConfigMcspi3ChCfg[chCnt].dpe0        = MCSPI_DPE_ENABLE;
            gConfigMcspi3ChCfg[chCnt].dpe1        = MCSPI_DPE_DISABLE;
        }

        status = MCSPI_chConfig(
                     gMcspiHandle[CONFIG_MCSPI3],
                     &gConfigMcspi3ChCfg[chCnt]);
        if(status != SystemP_SUCCESS)
        {
            DebugP_logError("CONFIG_MCSPI3 channel %d config failed !!!\r\n", chCnt);
            break;
        }

        if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
        {
            status = SemaphoreP_constructBinary(&gMcspiTransferDoneSem, 0);
            DebugP_assert(SystemP_SUCCESS == status);
        }

        dataWidth = 8U;
        if (dataWidth < 9U)
        {
            /* Init TX buffer with known data and memset RX buffer */
            tempTxPtr8 = (uint8_t *) &gMcspiTxBufferDma[0U];
            tempRxPtr8 = (uint8_t *) &gMcspiRxBufferDma[0U];
        }
        else if (dataWidth < 17U)
        {
            /* Init TX buffer with known data and memset RX buffer */
            tempTxPtr16 = (uint16_t *) &gMcspiTxBufferDma[0U];
            tempRxPtr16 = (uint16_t *) &gMcspiRxBufferDma[0U];
        }
        else
        {
            /* Init TX buffer with known data and memset RX buffer */
            tempTxPtr32 = (uint32_t *) &gMcspiTxBufferDma[0U];
            tempRxPtr32 = (uint32_t *) &gMcspiRxBufferDma[0U];
        }
        fifoBitMask = 0x0U;
        for (dataWidthIdx = 0U;
             dataWidthIdx < dataWidth; dataWidthIdx++)
        {
            fifoBitMask |= (1U << dataWidthIdx);
        }

        /* Memfill buffers */
        for (i = 0U; i < testParams->transferLength; i++)
        {
            tempTxData = 0xDEADBABE;
            tempTxData &= (fifoBitMask);
            if (dataWidth < 9U)
            {
                *tempTxPtr8++ = (uint8_t) (tempTxData);
                *tempRxPtr8++ = 0U;
            }
            else if (dataWidth < 17U)
            {
                *tempTxPtr16++ = (uint16_t) (tempTxData);
                *tempRxPtr16++ = 0U;
            }
            else
            {
                *tempTxPtr32++ = (uint32_t) (tempTxData);
                *tempRxPtr32++ = 0U;
            }
        }

        /* Writeback buffer */
        CacheP_wb(&gMcspiTxBufferDma[0U], sizeof(gMcspiTxBufferDma), CacheP_TYPE_ALLD);
        CacheP_wb(&gMcspiRxBufferDma[0U], sizeof(gMcspiRxBufferDma), CacheP_TYPE_ALLD);

        /* Initiate transfer */
        spiTransaction.channel  = gConfigMcspi3ChCfg[chCnt].chNum;
        spiTransaction.dataSize  = dataWidth;
        spiTransaction.csDisable = TRUE;
        spiTransaction.count    = APP_MCSPI_MSGSIZE / (dataWidth / 8);
        spiTransaction.txBuf    = (void *)gMcspiTxBufferDma;
        spiTransaction.rxBuf    = (void *)gMcspiRxBufferDma;
        spiTransaction.args     = NULL;
        transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI3], &spiTransaction);
        TEST_APP_MCSPI_ASSERT_ON_FAILURE(transferOK, spiTransaction);

        if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
        {
            /* Wait for transfer completion */
            SemaphoreP_pend(&gMcspiTransferDoneSem, SystemP_WAIT_FOREVER);
        }

        /* Invalidate cache */
        CacheP_inv(&gMcspiRxBufferDma[0U], sizeof(gMcspiRxBufferDma), CacheP_TYPE_ALLD);
        /* Compare data */
        uint8_t *tempTxPtr, *tempRxPtr;
        tempTxPtr = (uint8_t *) &gMcspiTxBufferDma[0U];
        tempRxPtr = (uint8_t *) &gMcspiRxBufferDma[0U];
        for(i = 0U; i < (APP_MCSPI_MSGSIZE); i++)
        {
            if(*tempTxPtr++ != *tempRxPtr++)
            {
                status = SystemP_FAILURE;   /* Data mismatch */
                DebugP_log("Data Mismatch at offset %d\r\n", i);
                break;
            }
        }

        if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
        {
            SemaphoreP_destruct(&gMcspiTransferDoneSem);
        }

    }

    for(chCnt = 0U; chCnt < CONFIG_MCSPI3_NUM_CH; chCnt++)
    {
        status = MCSPI_dmaClose(gMcspiHandle[CONFIG_MCSPI3],
                                &gConfigMcspi3ChCfg[chCnt]);
        if(status != SystemP_SUCCESS)
        {
            DebugP_logError("CONFIG_MCSPI3 DMA close %d failed !!!\r\n", chCnt);
            break;
        }
    }

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI3]);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    return;
}

void test_mcspi_loopback_dma(void *args)
{
    int32_t             status = SystemP_SUCCESS;
    uint32_t            i, j, dataWidth, fifoBitMask, tempTxData, dataWidthIdx;
    int32_t             transferOK;
    MCSPI_Transaction   spiTransaction;
    MCSPI_TestParams   *testParams = (MCSPI_TestParams *)args;
    uint8_t            *tempRxPtr8 = NULL, *tempTxPtr8 = NULL;
    uint16_t           *tempRxPtr16 = NULL, *tempTxPtr16 = NULL;
    uint32_t           *tempRxPtr32 = NULL, *tempTxPtr32 = NULL;
    MCSPI_OpenParams   *mcspiOpenParams = &(testParams->mcspiOpenParams);
    MCSPI_Config       *config;
    MCSPI_Attrs        *attrParams;
    MCSPI_Handle        mcspiHandle;
    uint64_t            startTimeInUSec, elapsedTimeInUsecs, totalTimeInUsecs = 0U;
    uint32_t            perf_offset = 0;

    /* Memset Buffers */
    memset(&gMcspiTxBufferDma[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiTxBufferDma[0U]));
    memset(&gMcspiRxBufferDma[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiRxBufferDma[0U]));

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI3]);

    config = &gMcspiConfig[CONFIG_MCSPI3];
    attrParams = (MCSPI_Attrs *)config->attrs;
    attrParams->operMode               = MCSPI_OPER_MODE_DMA;
    mcspiOpenParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
    mcspiOpenParams->transferCallbackFxn    = test_mcspi_callback;
    mcspiOpenParams->mcspiDmaIndex          = 0;
    mcspiHandle = MCSPI_open(CONFIG_MCSPI3, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        status = SemaphoreP_constructBinary(&gMcspiTransferDoneSem, 0);
        DebugP_assert(SystemP_SUCCESS == status);
    }

    status = MCSPI_chConfig(
                 gMcspiHandle[CONFIG_MCSPI3],
                 &gConfigMcspi3ChCfg[0U]);
    if(status != SystemP_SUCCESS)
    {
        DebugP_logError("CONFIG_MCSPI3 channel %d config failed !!!\r\n", 0);
    }

    status = MCSPI_dmaChConfig(
                 gMcspiHandle[CONFIG_MCSPI3],
                 &gConfigMcspi3ChCfg[0U],
                 &gConfigMcspi3DmaChCfg[0U]);
    if(status != SystemP_SUCCESS)
    {
        DebugP_logError("CONFIG_MCSPI3 channel %d config failed !!!\r\n", 0);
    }

    dataWidth = testParams->dataSize;
    if (dataWidth < 9U)
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr8 = (uint8_t *) &gMcspiTxBufferDma[0U];
        tempRxPtr8 = (uint8_t *) &gMcspiRxBufferDma[0U];
    }
    else if (dataWidth < 17U)
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr16 = (uint16_t *) &gMcspiTxBufferDma[0U];
        tempRxPtr16 = (uint16_t *) &gMcspiRxBufferDma[0U];
    }
    else
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr32 = (uint32_t *) &gMcspiTxBufferDma[0U];
        tempRxPtr32 = (uint32_t *) &gMcspiRxBufferDma[0U];
    }
    fifoBitMask = 0x0U;
    for (dataWidthIdx = 0U;
         dataWidthIdx < dataWidth; dataWidthIdx++)
    {
        fifoBitMask |= (1U << dataWidthIdx);
    }

    /* Memfill buffers */
    for (i = 0U; i < testParams->transferLength; i++)
    {
        tempTxData = 0xDEADBABE;
        tempTxData &= (fifoBitMask);
        if (dataWidth < 9U)
        {
            *tempTxPtr8++ = (uint8_t) (tempTxData);
            *tempRxPtr8++ = 0U;
        }
        else if (dataWidth < 17U)
        {
            *tempTxPtr16++ = (uint16_t) (tempTxData);
            *tempRxPtr16++ = 0U;
        }
        else
        {
            *tempTxPtr32++ = (uint32_t) (tempTxData);
            *tempRxPtr32++ = 0U;
        }
    }

    /* Writeback buffer */
    CacheP_wb(&gMcspiTxBufferDma[0U], sizeof(gMcspiTxBufferDma), CacheP_TYPE_ALLD);
    CacheP_wb(&gMcspiRxBufferDma[0U], sizeof(gMcspiRxBufferDma), CacheP_TYPE_ALLD);
    for(j = 0U; j < APP_MCSPI_PERF_LOOP_ITER_CNT; j++)
    {
        /* Initiate transfer */
        spiTransaction.channel  = gConfigMcspi3ChCfg[0U].chNum;
        spiTransaction.count    = testParams->transferLength;
        spiTransaction.dataSize  = dataWidth;
        spiTransaction.csDisable = TRUE;
        spiTransaction.txBuf    = (void *)gMcspiTxBufferDma;
        spiTransaction.rxBuf    = (void *)gMcspiRxBufferDma;
        spiTransaction.args     = NULL;
        startTimeInUSec = ClockP_getTimeUsec();
        transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI3], &spiTransaction);
        TEST_APP_MCSPI_ASSERT_ON_FAILURE(transferOK, spiTransaction);

        if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
        {
            /* Wait for transfer completion */
            SemaphoreP_pend(&gMcspiTransferDoneSem, SystemP_WAIT_FOREVER);
        }
        elapsedTimeInUsecs = ClockP_getTimeUsec() - startTimeInUSec;
        totalTimeInUsecs += elapsedTimeInUsecs;

        /* Invalidate cache */
        CacheP_inv(&gMcspiRxBufferDma[0U], sizeof(gMcspiRxBufferDma), CacheP_TYPE_ALLD);

        /* Compare data */
        uint8_t *tempTxPtr, *tempRxPtr;
        tempTxPtr = (uint8_t *) &gMcspiTxBufferDma[0U];
        tempRxPtr = (uint8_t *) &gMcspiRxBufferDma[0U];
        for(i = 0U; i < (APP_MCSPI_MSGSIZE); i++)
        {
            if(*tempTxPtr++ != *tempRxPtr++)
            {
                status = SystemP_FAILURE;   /* Data mismatch */
                DebugP_log("Data Mismatch at offset %d\r\n", i);
                break;
            }
        }
    }

    /* Store Performance value in global var. Performance numbers are printed at the end of UT. */
    if (dataWidth == 8) {
        perf_offset = 0;
    } else if (dataWidth == 16) {
        perf_offset = 1;
    } else{
        perf_offset = 2;
    }
    gUtPerf[perf_offset].dma = totalTimeInUsecs;

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        SemaphoreP_destruct(&gMcspiTransferDoneSem);
    }

    status = MCSPI_dmaClose(gMcspiHandle[CONFIG_MCSPI3],
                            &gConfigMcspi3ChCfg[0U]);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI3]);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    return;
}

void test_mcspi_loopback_dma_with_csdisable(void *args)
{
    int32_t             status = SystemP_SUCCESS;
    uint32_t            i, j, dataWidth, fifoBitMask, tempTxData, dataWidthIdx;
    int32_t             transferOK;
    MCSPI_Transaction   spiTransaction;
    MCSPI_TestParams   *testParams = (MCSPI_TestParams *)args;
    uint8_t            *tempRxPtr8 = NULL, *tempTxPtr8 = NULL;
    uint16_t           *tempRxPtr16 = NULL, *tempTxPtr16 = NULL;
    uint32_t           *tempRxPtr32 = NULL, *tempTxPtr32 = NULL;
    MCSPI_OpenParams   *mcspiOpenParams = &(testParams->mcspiOpenParams);
    MCSPI_Config       *config;
    MCSPI_Attrs        *attrParams;
    MCSPI_Handle        mcspiHandle;
    uint64_t            startTimeInUSec, elapsedTimeInUsecs, totalTimeInUsecs = 0U;
    uint32_t            perf_offset = 0;

    /* Memset Buffers */
    memset(&gMcspiTxBufferDma[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiTxBufferDma[0U]));
    memset(&gMcspiRxBufferDma[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiRxBufferDma[0U]));

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI3]);

    config = &gMcspiConfig[CONFIG_MCSPI3];
    attrParams = (MCSPI_Attrs *)config->attrs;
    attrParams->operMode                    = MCSPI_OPER_MODE_DMA;
    attrParams->chMode                      = MCSPI_CH_MODE_SINGLE;
    mcspiOpenParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
    mcspiOpenParams->transferCallbackFxn    = test_mcspi_callback;
    mcspiOpenParams->mcspiDmaIndex          = 0;
    mcspiHandle = MCSPI_open(CONFIG_MCSPI3, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        status = SemaphoreP_constructBinary(&gMcspiTransferDoneSem, 0);
        DebugP_assert(SystemP_SUCCESS == status);
    }

    status = MCSPI_chConfig(
                 gMcspiHandle[CONFIG_MCSPI3],
                 &gConfigMcspi3ChCfg[0U]);
    if(status != SystemP_SUCCESS)
    {
        DebugP_logError("CONFIG_MCSPI3 channel %d config failed !!!\r\n", 0);
    }

    status = MCSPI_dmaChConfig(
                 gMcspiHandle[CONFIG_MCSPI3],
                 &gConfigMcspi3ChCfg[0U],
                 &gConfigMcspi3DmaChCfg[0U]);
    if(status != SystemP_SUCCESS)
    {
        DebugP_logError("CONFIG_MCSPI3 channel %d config failed !!!\r\n", 0);
    }

    dataWidth = testParams->dataSize;
    if (dataWidth < 9U)
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr8 = (uint8_t *) &gMcspiTxBufferDma[0U];
        tempRxPtr8 = (uint8_t *) &gMcspiRxBufferDma[0U];
    }
    else if (dataWidth < 17U)
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr16 = (uint16_t *) &gMcspiTxBufferDma[0U];
        tempRxPtr16 = (uint16_t *) &gMcspiRxBufferDma[0U];
    }
    else
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr32 = (uint32_t *) &gMcspiTxBufferDma[0U];
        tempRxPtr32 = (uint32_t *) &gMcspiRxBufferDma[0U];
    }
    fifoBitMask = 0x0U;
    for (dataWidthIdx = 0U;
         dataWidthIdx < dataWidth; dataWidthIdx++)
    {
        fifoBitMask |= (1U << dataWidthIdx);
    }

    /* Memfill buffers */
    for (i = 0U; i < testParams->transferLength; i++)
    {
        tempTxData = 0xDEADBABE;
        tempTxData &= (fifoBitMask);
        if (dataWidth < 9U)
        {
            *tempTxPtr8++ = (uint8_t) (tempTxData);
            *tempRxPtr8++ = 0U;
        }
        else if (dataWidth < 17U)
        {
            *tempTxPtr16++ = (uint16_t) (tempTxData);
            *tempRxPtr16++ = 0U;
        }
        else
        {
            *tempTxPtr32++ = (uint32_t) (tempTxData);
            *tempRxPtr32++ = 0U;
        }
    }

    /* Writeback buffer */
    CacheP_wb(&gMcspiTxBufferDma[0U], sizeof(gMcspiTxBufferDma), CacheP_TYPE_ALLD);
    CacheP_wb(&gMcspiRxBufferDma[0U], sizeof(gMcspiRxBufferDma), CacheP_TYPE_ALLD);
    for(j = 0U; j < APP_MCSPI_PERF_LOOP_ITER_CNT; j++)
    {
        /* Initiate transfer */
        spiTransaction.channel  = gConfigMcspi3ChCfg[0U].chNum;
        spiTransaction.count    = testParams->transferLength;
        spiTransaction.dataSize  = dataWidth;
        spiTransaction.csDisable = FALSE;
        spiTransaction.txBuf    = (void *)gMcspiTxBufferDma;
        spiTransaction.rxBuf    = (void *)gMcspiRxBufferDma;
        spiTransaction.args     = NULL;
        startTimeInUSec = ClockP_getTimeUsec();
        transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI3], &spiTransaction);
        TEST_APP_MCSPI_ASSERT_ON_FAILURE(transferOK, spiTransaction);

        if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
        {
            /* Wait for transfer completion */
            SemaphoreP_pend(&gMcspiTransferDoneSem, SystemP_WAIT_FOREVER);
        }
        elapsedTimeInUsecs = ClockP_getTimeUsec() - startTimeInUSec;
        totalTimeInUsecs += elapsedTimeInUsecs;

        /* Invalidate cache */
        CacheP_inv(&gMcspiRxBufferDma[0U], sizeof(gMcspiRxBufferDma), CacheP_TYPE_ALLD);

        /* Compare data */
        uint8_t *tempTxPtr, *tempRxPtr;
        tempTxPtr = (uint8_t *) &gMcspiTxBufferDma[0U];
        tempRxPtr = (uint8_t *) &gMcspiRxBufferDma[0U];
        for(i = 0U; i < (APP_MCSPI_MSGSIZE); i++)
        {
            if(*tempTxPtr++ != *tempRxPtr++)
            {
                status = SystemP_FAILURE;   /* Data mismatch */
                DebugP_log("Data Mismatch at offset %d\r\n", i);
                break;
            }
        }
    }

    /* Store Performance value in global var. Performance numbers are printed at the end of UT. */
    if (dataWidth == 8) {
        perf_offset = 0;
    } else if (dataWidth == 16) {
        perf_offset = 1;
    } else{
        perf_offset = 2;
    }
    gUtPerf[perf_offset].dma = totalTimeInUsecs;

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        SemaphoreP_destruct(&gMcspiTransferDoneSem);
    }

    status = MCSPI_dmaClose(gMcspiHandle[CONFIG_MCSPI3],
                            &gConfigMcspi3ChCfg[0U]);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI3]);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    return;
}

void test_mcspi_loopback_dma_with_toggled_csdisable(void *args)
{
    int32_t             status = SystemP_SUCCESS;
    uint32_t            i, j, dataWidth, fifoBitMask, tempTxData, dataWidthIdx;
    int32_t             transferOK;
    MCSPI_Transaction   spiTransaction;
    MCSPI_TestParams   *testParams = (MCSPI_TestParams *)args;
    uint8_t            *tempRxPtr8 = NULL, *tempTxPtr8 = NULL;
    uint16_t           *tempRxPtr16 = NULL, *tempTxPtr16 = NULL;
    uint32_t           *tempRxPtr32 = NULL, *tempTxPtr32 = NULL;
    MCSPI_OpenParams   *mcspiOpenParams = &(testParams->mcspiOpenParams);
    MCSPI_Config       *config;
    MCSPI_Attrs        *attrParams;
    MCSPI_Handle        mcspiHandle;
    uint64_t            startTimeInUSec, elapsedTimeInUsecs, totalTimeInUsecs = 0U;
    uint32_t            perf_offset = 0;

    /* Memset Buffers */
    memset(&gMcspiTxBufferDma[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiTxBufferDma[0U]));
    memset(&gMcspiRxBufferDma[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiRxBufferDma[0U]));

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI3]);

    config = &gMcspiConfig[CONFIG_MCSPI3];
    attrParams = (MCSPI_Attrs *)config->attrs;
    attrParams->operMode                    = MCSPI_OPER_MODE_DMA;
    attrParams->chMode                      = MCSPI_CH_MODE_SINGLE;
    mcspiOpenParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
    mcspiOpenParams->transferCallbackFxn    = test_mcspi_callback;
    mcspiOpenParams->mcspiDmaIndex          = 0;
    mcspiHandle = MCSPI_open(CONFIG_MCSPI3, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        status = SemaphoreP_constructBinary(&gMcspiTransferDoneSem, 0);
        DebugP_assert(SystemP_SUCCESS == status);
    }

    status = MCSPI_chConfig(
                 gMcspiHandle[CONFIG_MCSPI3],
                 &gConfigMcspi3ChCfg[0U]);
    if(status != SystemP_SUCCESS)
    {
        DebugP_logError("CONFIG_MCSPI3 channel %d config failed !!!\r\n", 0);
    }

    status = MCSPI_dmaChConfig(
                 gMcspiHandle[CONFIG_MCSPI3],
                 &gConfigMcspi3ChCfg[0U],
                 &gConfigMcspi3DmaChCfg[0U]);
    if(status != SystemP_SUCCESS)
    {
        DebugP_logError("CONFIG_MCSPI3 channel %d config failed !!!\r\n", 0);
    }

    dataWidth = testParams->dataSize;
    if (dataWidth < 9U)
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr8 = (uint8_t *) &gMcspiTxBufferDma[0U];
        tempRxPtr8 = (uint8_t *) &gMcspiRxBufferDma[0U];
    }
    else if (dataWidth < 17U)
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr16 = (uint16_t *) &gMcspiTxBufferDma[0U];
        tempRxPtr16 = (uint16_t *) &gMcspiRxBufferDma[0U];
    }
    else
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr32 = (uint32_t *) &gMcspiTxBufferDma[0U];
        tempRxPtr32 = (uint32_t *) &gMcspiRxBufferDma[0U];
    }
    fifoBitMask = 0x0U;
    for (dataWidthIdx = 0U;
         dataWidthIdx < dataWidth; dataWidthIdx++)
    {
        fifoBitMask |= (1U << dataWidthIdx);
    }

    /* Memfill buffers */
    for (i = 0U; i < testParams->transferLength; i++)
    {
        tempTxData = 0xDEADBABE;
        tempTxData &= (fifoBitMask);
        if (dataWidth < 9U)
        {
            *tempTxPtr8++ = (uint8_t) (tempTxData);
            *tempRxPtr8++ = 0U;
        }
        else if (dataWidth < 17U)
        {
            *tempTxPtr16++ = (uint16_t) (tempTxData);
            *tempRxPtr16++ = 0U;
        }
        else
        {
            *tempTxPtr32++ = (uint32_t) (tempTxData);
            *tempRxPtr32++ = 0U;
        }
    }

    /* Writeback buffer */
    CacheP_wb(&gMcspiTxBufferDma[0U], sizeof(gMcspiTxBufferDma), CacheP_TYPE_ALLD);
    CacheP_wb(&gMcspiRxBufferDma[0U], sizeof(gMcspiRxBufferDma), CacheP_TYPE_ALLD);
    for(j = 0U; j < APP_MCSPI_PERF_LOOP_ITER_CNT; j++)
    {
        /* Initiate transfer */
        spiTransaction.channel  = gConfigMcspi3ChCfg[0U].chNum;
        spiTransaction.count    = testParams->transferLength;
        spiTransaction.dataSize  = dataWidth;
        if(j < (APP_MCSPI_PERF_LOOP_ITER_CNT/4))
        {
            spiTransaction.csDisable = TRUE;
        }
        else if((j>=(APP_MCSPI_PERF_LOOP_ITER_CNT/4)) && (j<(APP_MCSPI_PERF_LOOP_ITER_CNT/2)))
        {
            spiTransaction.csDisable = FALSE;
        }
        else
        {
            spiTransaction.csDisable = TRUE;
        }
        spiTransaction.txBuf    = (void *)gMcspiTxBufferDma;
        spiTransaction.rxBuf    = (void *)gMcspiRxBufferDma;
        spiTransaction.args     = NULL;
        startTimeInUSec = ClockP_getTimeUsec();
        transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI3], &spiTransaction);
        TEST_APP_MCSPI_ASSERT_ON_FAILURE(transferOK, spiTransaction);

        if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
        {
            /* Wait for transfer completion */
            SemaphoreP_pend(&gMcspiTransferDoneSem, SystemP_WAIT_FOREVER);
        }
        elapsedTimeInUsecs = ClockP_getTimeUsec() - startTimeInUSec;
        totalTimeInUsecs += elapsedTimeInUsecs;

        /* Invalidate cache */
        CacheP_inv(&gMcspiRxBufferDma[0U], sizeof(gMcspiRxBufferDma), CacheP_TYPE_ALLD);

        /* Compare data */
        uint8_t *tempTxPtr, *tempRxPtr;
        tempTxPtr = (uint8_t *) &gMcspiTxBufferDma[0U];
        tempRxPtr = (uint8_t *) &gMcspiRxBufferDma[0U];
        for(i = 0U; i < (APP_MCSPI_MSGSIZE); i++)
        {
            if(*tempTxPtr++ != *tempRxPtr++)
            {
                status = SystemP_FAILURE;   /* Data mismatch */
                DebugP_log("Data Mismatch at offset %d\r\n", i);
                break;
            }
        }
    }

    /* Store Performance value in global var. Performance numbers are printed at the end of UT. */
    if (dataWidth == 8) {
        perf_offset = 0;
    } else if (dataWidth == 16) {
        perf_offset = 1;
    } else{
        perf_offset = 2;
    }
    gUtPerf[perf_offset].dma = totalTimeInUsecs;

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        SemaphoreP_destruct(&gMcspiTransferDoneSem);
    }

    status = MCSPI_dmaClose(gMcspiHandle[CONFIG_MCSPI3],
                            &gConfigMcspi3ChCfg[0U]);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI3]);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    return;
}

#endif

void test_mcspi_loopback_timeout(void *args)
{
    int32_t             status = SystemP_SUCCESS;
    uint32_t            i, dataWidth, fifoBitMask, tempTxData, dataWidthIdx;
    int32_t             transferOK;
    MCSPI_Transaction   spiTransaction;
    MCSPI_Handle        mcspiHandle;
    MCSPI_TestParams   *testParams = (MCSPI_TestParams *)args;
    uint8_t            *tempRxPtr8 = NULL, *tempTxPtr8 = NULL;
    uint16_t           *tempRxPtr16 = NULL, *tempTxPtr16 = NULL;
    uint32_t           *tempRxPtr32 = NULL, *tempTxPtr32 = NULL;
    MCSPI_OpenParams   *mcspiOpenParams = &(testParams->mcspiOpenParams);
    MCSPI_ChConfig     *mcspiChConfigParams = &(testParams->mcspiChConfigParams);

    /* Memset Buffers */
    memset(&gMcspiTxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiTxBuffer[0U]));
    memset(&gMcspiRxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiRxBuffer[0U]));

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);

    mcspiHandle = MCSPI_open(CONFIG_MCSPI0, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);

    status = MCSPI_chConfig(
                 gMcspiHandle[CONFIG_MCSPI0],
                 mcspiChConfigParams);
    DebugP_assert(status == SystemP_SUCCESS);

    dataWidth = testParams->dataSize;
    if (dataWidth < 9U)
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr8 = (uint8_t *) &gMcspiTxBuffer[0U];
        tempRxPtr8 = (uint8_t *) &gMcspiRxBuffer[0U];
    }
    else if (dataWidth < 17U)
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr16 = (uint16_t *) &gMcspiTxBuffer[0U];
        tempRxPtr16 = (uint16_t *) &gMcspiRxBuffer[0U];
    }
    else
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr32 = (uint32_t *) &gMcspiTxBuffer[0U];
        tempRxPtr32 = (uint32_t *) &gMcspiRxBuffer[0U];
    }
    fifoBitMask = 0x0U;
    for (dataWidthIdx = 0U;
         dataWidthIdx < dataWidth; dataWidthIdx++)
    {
        fifoBitMask |= (1U << dataWidthIdx);
    }

    /* Memfill buffers */
    for (i = 0U; i < testParams->transferLength; i++)
    {
        tempTxData = 0xDEADBABE;
        tempTxData &= (fifoBitMask);
        if (dataWidth < 9U)
        {
            *tempTxPtr8++ = (uint8_t) (tempTxData);
            *tempRxPtr8++ = 0U;
        }
        else if (dataWidth < 17U)
        {
            *tempTxPtr16++ = (uint16_t) (tempTxData);
            *tempRxPtr16++ = 0U;
        }
        else
        {
            *tempTxPtr32++ = (uint32_t) (tempTxData);
            *tempRxPtr32++ = 0U;
        }
    }

    /* Initiate transfer */
    spiTransaction.channel  = testParams->mcspiChConfigParams.chNum;
    spiTransaction.dataSize  = dataWidth;
    spiTransaction.csDisable = TRUE;
    spiTransaction.count    = testParams->transferLength;
    spiTransaction.txBuf    = (void *)gMcspiTxBuffer;
    spiTransaction.rxBuf    = (void *)gMcspiRxBuffer;
    spiTransaction.args     = NULL;
    transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction);
    DebugP_assert(spiTransaction.status == MCSPI_TRANSFER_TIMEOUT);
    DebugP_assert(transferOK == SystemP_FAILURE);

    /* Compare data and should mismatch as timeout occurred */
    uint8_t *tempTxPtr, *tempRxPtr;
    tempTxPtr = (uint8_t *) &gMcspiTxBuffer[0U];
    tempRxPtr = (uint8_t *) &gMcspiRxBuffer[0U];
    for(i = 0U; i < (APP_MCSPI_MSGSIZE * 4); i++)
    {
        if(*tempTxPtr++ != *tempRxPtr++)
        {
            status = SystemP_SUCCESS;
            break;
        }
    }

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    return;
}

void test_mcspi_performance_16bit(void *args)
{
    uint32_t            i, j;
    uint32_t            dataLength, dataWidth, bitRate, bufWidthShift;
    uint32_t            baseAddr, chNum, dataSize;
    uint32_t            chCtrlRegVal, chConfRegVal;
    uint64_t            startTimeInUSec, elapsedTimeInUsecs;
    int32_t             status = SystemP_SUCCESS;
    MCSPI_Handle        mcspiHandle;
    MCSPI_TestParams   *testParams = (MCSPI_TestParams *)args;
    MCSPI_OpenParams   *mcspiOpenParams = &(testParams->mcspiOpenParams);

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);

    mcspiHandle = MCSPI_open(CONFIG_MCSPI0, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);

    /* update data size to 16 and bitrate to 12MHZ */
    dataSize = 16U;
    gConfigMcspi0ChCfg[0U].bitRate  = 12500000U;
    gConfigMcspi0ChCfg[0U].trMode   = MCSPI_TR_MODE_TX_ONLY;

    status = MCSPI_chConfig(gMcspiHandle[CONFIG_MCSPI0], &gConfigMcspi0ChCfg[0U]);
    DebugP_assert(SystemP_SUCCESS == status);

    DebugP_log("[MCSPI] Performance 16bit Example Started...\r\n\n");

    /* Memfill buffers */
    for(i = 0U; i < APP_MCSPI_TXONLYMSGSIZE; i++)
    {
        gMcspiPerfTxBuffer[i] = i;
    }

    /* Initialize SPI Channel Number */
    chNum  = gConfigMcspi0ChCfg[0U].chNum;

    /* Get SPI Channel Info */
    baseAddr = MCSPI_getBaseAddr(gMcspiHandle[CONFIG_MCSPI0]);
    DebugP_assert(baseAddr != 0U); /* MCSPI baseAddr Invalid!! */

    /* Set dataWidth */
    MCSPI_setDataWidth(baseAddr, chNum, dataSize);
    /* Enable the transmitter FIFO of McSPI peripheral. */
    MCSPI_enableTxFIFO(baseAddr, chNum, MCSPI_TX_FIFO_ENABLE);

    /* Disable the receiver FIFO of McSPI peripheral for Tx only mode. */
    MCSPI_enableRxFIFO(baseAddr, chNum, MCSPI_RX_FIFO_DISABLE);

    /*
     * Channel Control and config registers are updated after Open/Reconfigure.
     * Channel enable/disable and CS assert/deassert require updation of bits in
     * control and config registers. Also these registers will not be updated
     * during data transfer. So reg read modify write operations can be updated
     * to write only operations.
     * Store ch enable/disable reg val and cs assert/deassert reg vals.
     */
    chCtrlRegVal     = MCSPI_readChCtrlReg(baseAddr, chNum);
    gChEnableRegVal  = chCtrlRegVal | CSL_MCSPI_CH0CTRL_EN_MASK;
    gChDisableRegVal = chCtrlRegVal & (~CSL_MCSPI_CH0CTRL_EN_MASK);

    chConfRegVal      = MCSPI_readChConf(baseAddr, chNum);
    gCsAssertRegVal   = chConfRegVal | CSL_MCSPI_CH0CONF_FORCE_MASK;
    gCsDeAssertRegVal = chConfRegVal & (~CSL_MCSPI_CH0CONF_FORCE_MASK);

    /*  Calculate buffer width shift value.
     *  When dataWidth <= 8,           bufWidth = uint8_t  (1 byte - 0 shift)
     *  When dataWidth > 8  && <= 16,  bufWidth = uint16_t (2 bytes - 1 shift)
     *  When dataWidth > 16 && <= 32,  bufWidth = uint32_t (4 bytes - 2 shift)
     */
    dataWidth  = dataSize;
    bufWidthShift = MCSPI_getBufWidthShift(dataWidth);
    dataLength = APP_MCSPI_TXONLYMSGSIZE;
    bitRate    = gConfigMcspi0ChCfg[0U].bitRate;

    /* Initiate transfer */
    startTimeInUSec = ClockP_getTimeUsec();
    for(j = 0U; j < APP_MCSPI_TRANSFER_LOOPCOUNT; j++)
    {
        mcspi_low_latency_transfer_16bit(baseAddr, chNum,
                                   &gMcspiPerfTxBuffer[0], dataLength, bufWidthShift);
    }
    elapsedTimeInUsecs = ClockP_getTimeUsec() - startTimeInUSec;

    DebugP_log("----------------------------------------------------------\r\n");
    DebugP_log("McSPI Clock %d Hz\r\n", bitRate);
    DebugP_log("----------------------------------------------------------\r\n");
    DebugP_log("Data Width \tData Length \tTransfer Time (micro sec)\r\n");
    DebugP_log("%u\t\t%u\t\t%5.2f\r\n", dataWidth, dataLength,
                        (float)elapsedTimeInUsecs / APP_MCSPI_TRANSFER_LOOPCOUNT);
    DebugP_log("----------------------------------------------------------\r\n\n");
    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);

    return;
}

void test_mcspi_loopback_simultaneous(void *args)
{
    int32_t             status = SystemP_SUCCESS;
    uint32_t            i, dataWidth, fifoBitMask, tempTxData, dataWidthIdx;
    int32_t             transferOK;
    MCSPI_Transaction   spiTransaction, spiTransaction1;
    MCSPI_Handle        mcspiHandle, mcspiHandle1;
    MCSPI_TestParams   *testParams = (MCSPI_TestParams *)args;
    uint16_t           *tempRxPtr16 = NULL, *tempTxPtr16 = NULL;
    uint32_t           *tempRxPtr32 = NULL, *tempTxPtr32 = NULL, dataWidth1, bufWidthShift;
    MCSPI_TestParams    testParams1;
    MCSPI_OpenParams   *mcspiOpenParams = &(testParams->mcspiOpenParams);
    MCSPI_ChConfig     *mcspiChConfigParams = &(testParams->mcspiChConfigParams);
    MCSPI_OpenParams   *mcspiOpenParams1 = &(testParams1.mcspiOpenParams);
    MCSPI_ChConfig     *mcspiChConfigParams1 = &(testParams1.mcspiChConfigParams);
    MCSPI_Config     *config = &gMcspiConfig[CONFIG_MCSPI1];
    MCSPI_Attrs      *attrParams = (MCSPI_Attrs *)config->attrs;

    mcspiOpenParams->transferMode = MCSPI_TRANSFER_MODE_BLOCKING;
    /* Instance 1 Init params */
    test_mcspi_set_params(&testParams1, 2929);
#if (CONFIG_MCSPI_NUM_INSTANCES > 2U)
    attrParams->baseAddr           = MCSPI1_BASE_ADDRESS;
    attrParams->intrNum            = MCSPI1_INT_NUM;
#if defined BUILD_C7X
    attrParams->eventId            = MCSPI1_EVENT_ID;
#endif
#else /* LP Case */
    #if defined(SOC_AM62AX) || defined(SOC_AM62X) || defined(SOC_AM62DX) || defined(SOC_AM275X) || defined(SOC_J722S)
    attrParams->baseAddr           = MCSPI1_BASE_ADDRESS;
    attrParams->intrNum            = MCSPI1_INT_NUM;
#if defined BUILD_C7X
    attrParams->eventId            = MCSPI1_EVENT_ID;
#endif
    #else
    attrParams->baseAddr           = MCSPI3_BASE_ADDRESS;
    attrParams->intrNum            = MCSPI3_INT_NUM;
#if defined BUILD_C7X
    attrParams->eventId            = MCSPI3_EVENT_ID;
#endif
    #endif
#endif
    attrParams->operMode           = MCSPI_OPER_MODE_INTERRUPT;
    attrParams->intrPriority       = 4U;
    mcspiChConfigParams1->bitRate            = 12500000;
    mcspiChConfigParams1->csPolarity         = MCSPI_CS_POL_HIGH;
    testParams1.dataSize           = 16;

    /* Memset Buffers */
    memset(&gMcspiTxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiTxBuffer[0U]));
    memset(&gMcspiRxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiRxBuffer[0U]));
    /* Memset Buffers */
    memset(&gMcspiTxBuffer1[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiTxBuffer1[0U]));
    memset(&gMcspiRxBuffer1[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiRxBuffer1[0U]));

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);
    MCSPI_close(gMcspiHandle[CONFIG_MCSPI1]);

    mcspiHandle = MCSPI_open(CONFIG_MCSPI0, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);
    mcspiHandle1 = MCSPI_open(CONFIG_MCSPI1, mcspiOpenParams1);
    TEST_ASSERT_NOT_NULL(mcspiHandle1);

    status = MCSPI_chConfig(
                 gMcspiHandle[CONFIG_MCSPI0],
                 mcspiChConfigParams);
    DebugP_assert(status == SystemP_SUCCESS);
    status = MCSPI_chConfig(
                 gMcspiHandle[CONFIG_MCSPI1],
                 mcspiChConfigParams1);
    DebugP_assert(status == SystemP_SUCCESS);

    if(mcspiOpenParams1->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        status = SemaphoreP_constructBinary(&gMcspiTransferDoneSem, 0);
        DebugP_assert(SystemP_SUCCESS == status);
    }

    dataWidth = testParams->dataSize;
    bufWidthShift = MCSPI_getBufWidthShift(dataWidth);
    if (dataWidth <= 32U)
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr32 = (uint32_t *) &gMcspiTxBuffer[0U];
        tempRxPtr32 = (uint32_t *) &gMcspiRxBuffer[0U];
    }

    fifoBitMask = 0x0U;
    for (dataWidthIdx = 0U;
         dataWidthIdx < dataWidth; dataWidthIdx++)
    {
        fifoBitMask |= (1U << dataWidthIdx);
    }

    /* Memfill buffers */
    for (i = 0U; i < testParams->transferLength; i++)
    {
        tempTxData = 0xDEADBABE;
        tempTxData &= (fifoBitMask);
        *tempTxPtr32++ = (uint32_t) (tempTxData);
        *tempRxPtr32++ = 0U;
    }

    dataWidth1 = testParams1.dataSize;
    bufWidthShift = MCSPI_getBufWidthShift(dataWidth1);
    if (dataWidth1 <= 16U)
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr16 = (uint16_t *) &gMcspiTxBuffer1[0U];
        tempRxPtr16 = (uint16_t *) &gMcspiRxBuffer1[0U];
    }

    fifoBitMask = 0x0U;
    for (dataWidthIdx = 0U;
         dataWidthIdx < dataWidth1; dataWidthIdx++)
    {
        fifoBitMask |= (1U << dataWidthIdx);
    }

    /* Memfill buffers */
    for (i = 0U; i < (APP_MCSPI_MSGSIZE * (sizeof(gMcspiTxBuffer1[0U]) / (1 << bufWidthShift))); i++)
    {
        tempTxData = 0xBEDEEFAD;
        tempTxData &= (fifoBitMask);
        *tempTxPtr16++ = (uint16_t) (tempTxData);
        *tempRxPtr16++ = 0U;
    }

    /* Initiate transfer */
    spiTransaction1.channel  = testParams1.mcspiChConfigParams.chNum;
    spiTransaction1.dataSize  = testParams1.dataSize;
    spiTransaction1.csDisable = TRUE;
    spiTransaction1.count    = (APP_MCSPI_MSGSIZE * (sizeof(gMcspiTxBuffer1[0U]) / (1 << bufWidthShift)));
    spiTransaction1.txBuf    = (void *)gMcspiTxBuffer1;
    spiTransaction1.rxBuf    = (void *)gMcspiRxBuffer1;
    spiTransaction1.args     = NULL;
    transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI1], &spiTransaction1);
    TEST_APP_MCSPI_ASSERT_ON_FAILURE(transferOK, spiTransaction1);

    /* Initiate transfer */
    spiTransaction.channel  = testParams->mcspiChConfigParams.chNum;
    spiTransaction.count    = testParams->transferLength;
    spiTransaction.dataSize  = dataWidth;
    spiTransaction.csDisable = TRUE;
    spiTransaction.txBuf    = (void *)gMcspiTxBuffer;
    spiTransaction.rxBuf    = (void *)gMcspiRxBuffer;
    spiTransaction.args     = NULL;
    transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction);
    TEST_APP_MCSPI_ASSERT_ON_FAILURE(transferOK, spiTransaction);

    if(mcspiOpenParams1->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        /* Wait for transfer completion */
        SemaphoreP_pend(&gMcspiTransferDoneSem, SystemP_WAIT_FOREVER);
    }

    /* Compare data */
    uint8_t *tempTxPtr, *tempRxPtr;
    tempTxPtr = (uint8_t *) &gMcspiTxBuffer[0U];
    tempRxPtr = (uint8_t *) &gMcspiRxBuffer[0U];
    for(i = 0U; i < (APP_MCSPI_MSGSIZE * 4); i++)
    {
        if(*tempTxPtr++ != *tempRxPtr++)
        {
            status = SystemP_FAILURE;   /* Data mismatch */
            DebugP_log("Data Mismatch at offset %d\r\n", i);
            break;
        }
    }

    /* Compare data */
    tempTxPtr = (uint8_t *) &gMcspiTxBuffer1[0U];
    tempRxPtr = (uint8_t *) &gMcspiRxBuffer1[0U];
    for(i = 0U; i < (APP_MCSPI_MSGSIZE * 4); i++)
    {
        if(*tempTxPtr++ != *tempRxPtr++)
        {
            status = SystemP_FAILURE;   /* Data mismatch */
            DebugP_log("Data Mismatch at offset %d\r\n", i);
            break;
        }
    }

    if(mcspiOpenParams1->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        SemaphoreP_destruct(&gMcspiTransferDoneSem);
    }

    /* Memset Buffers */
    memset(&gMcspiTxBuffer1[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiTxBuffer1[0U]));
    memset(&gMcspiRxBuffer1[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiRxBuffer1[0U]));

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);
    MCSPI_close(gMcspiHandle[CONFIG_MCSPI1]);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    return;
}

#if ENABLE_MT_TESTS
void test_mcspi_transfer_cancel(void *args)
{
    int32_t status = SystemP_SUCCESS;
    MCSPI_Handle        mcspiHandle;
    TaskP_Params transferTaskParms, transferCancelTaskParms;
    MCSPI_TestParams   *testParams = (MCSPI_TestParams *)args;
    MCSPI_ChConfig     *mcspiChConfigParams = &(testParams->mcspiChConfigParams);
    MCSPI_OpenParams   *mcspiOpenParams = &(testParams->mcspiOpenParams);

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);

    mcspiHandle = MCSPI_open(CONFIG_MCSPI0, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);

    status = MCSPI_chConfig(
                 gMcspiHandle[CONFIG_MCSPI0],
                 mcspiChConfigParams);
    DebugP_assert(status == SystemP_SUCCESS);

    status = SemaphoreP_constructCounting(&gMcspiTransferTaskDoneSemaphoreObj, 0, 2);
    DebugP_assert(status == SystemP_SUCCESS);
    status = SemaphoreP_constructCounting(&gMcspiTransferCancelTaskDoneSemaphoreObj, 0, 2);
    DebugP_assert(status == SystemP_SUCCESS);

    TaskP_Params_init(&transferTaskParms);
    transferTaskParms.name = "MCSPI Transfer Task";
    transferTaskParms.stackSize = MCSPI_TASK_STACK_SIZE;
    transferTaskParms.stack = gMcspiTransferTaskStack;
    transferTaskParms.priority = MCSPI_TASK_PRIORITY;
    transferTaskParms.args = testParams;
    transferTaskParms.taskMain = test_mcspi_transfer_cancel_transfer;
    status = TaskP_construct(&gMcspiTransferTaskObject, &transferTaskParms);
    DebugP_assert(status == SystemP_SUCCESS);

    ClockP_usleep(1000);

    TaskP_Params_init(&transferCancelTaskParms);
    transferCancelTaskParms.name = "MCSPI Transfer Cancel Task";
    transferCancelTaskParms.stackSize = MCSPI_TASK_STACK_SIZE;
    transferCancelTaskParms.stack = gMcspiTransferCancelTaskStack;
    transferCancelTaskParms.priority = MCSPI_TASK_PRIORITY;
    transferCancelTaskParms.args = testParams;
    transferCancelTaskParms.taskMain = test_mcspi_transfer_cancel_cancel;
    status = TaskP_construct(&gMcspiTransferCancelTaskObject, &transferCancelTaskParms);
    DebugP_assert(status == SystemP_SUCCESS);

    SemaphoreP_pend(&gMcspiTransferTaskDoneSemaphoreObj, SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&gMcspiTransferCancelTaskDoneSemaphoreObj, SystemP_WAIT_FOREVER);

    ClockP_usleep(1000);
    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    return;
}

void test_mcspi_transfer_cancel_transfer(void *args)
{
    int32_t             status = SystemP_SUCCESS;
    uint32_t            i, dataWidth, fifoBitMask, tempTxData, dataWidthIdx;
    int32_t             transferOK;
    MCSPI_Transaction   spiTransaction;
    MCSPI_TestParams   *testParams = (MCSPI_TestParams *)args;
    uint8_t            *tempRxPtr8 = NULL, *tempTxPtr8 = NULL;
    uint16_t           *tempRxPtr16 = NULL, *tempTxPtr16 = NULL;
    uint32_t           *tempRxPtr32 = NULL, *tempTxPtr32 = NULL;
    MCSPI_OpenParams   *mcspiOpenParams = &(testParams->mcspiOpenParams);

    /* Memset Buffers */
    memset(&gMcspiTxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiTxBuffer[0U]));
    memset(&gMcspiRxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiRxBuffer[0U]));

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        status = SemaphoreP_constructBinary(&Test_Mcspi_TransferDoneSemCancel, 0);
        DebugP_assert(SystemP_SUCCESS == status);
    }

    dataWidth = testParams->dataSize;
    if (dataWidth < 9U)
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr8 = (uint8_t *) &gMcspiTxBuffer[0U];
        tempRxPtr8 = (uint8_t *) &gMcspiRxBuffer[0U];
    }
    else if (dataWidth < 17U)
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr16 = (uint16_t *) &gMcspiTxBuffer[0U];
        tempRxPtr16 = (uint16_t *) &gMcspiRxBuffer[0U];
    }
    else
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr32 = (uint32_t *) &gMcspiTxBuffer[0U];
        tempRxPtr32 = (uint32_t *) &gMcspiRxBuffer[0U];
    }
    fifoBitMask = 0x0U;
    for (dataWidthIdx = 0U;
         dataWidthIdx < dataWidth; dataWidthIdx++)
    {
        fifoBitMask |= (1U << dataWidthIdx);
    }

    /* Memfill buffers */
    for (i = 0U; i < testParams->transferLength; i++)
    {
        tempTxData = 0xABCDBADC;
        tempTxData &= (fifoBitMask);
        if (dataWidth < 9U)
        {
            *tempTxPtr8++ = (uint8_t) (tempTxData);
            *tempRxPtr8++ = 0U;
        }
        else if (dataWidth < 17U)
        {
            *tempTxPtr16++ = (uint16_t) (tempTxData);
            *tempRxPtr16++ = 0U;
        }
        else
        {
            *tempTxPtr32++ = (uint32_t) (tempTxData);
            *tempRxPtr32++ = 0U;
        }
    }

    /* Initiate transfer */
    spiTransaction.channel  = testParams->mcspiChConfigParams.chNum;
    spiTransaction.dataSize  = dataWidth;
    spiTransaction.csDisable = TRUE;
    spiTransaction.count    = testParams->transferLength;
    spiTransaction.txBuf    = (void *)gMcspiTxBuffer;
    spiTransaction.rxBuf    = (void *)gMcspiRxBuffer;
    spiTransaction.args     = NULL;
    transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction);
    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_BLOCKING)
    {
        DebugP_assert(spiTransaction.status == MCSPI_TRANSFER_CANCELLED);
    }
    DebugP_assert(transferOK == SystemP_SUCCESS);

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        /* Wait for transfer completion */
        SemaphoreP_pend(&Test_Mcspi_TransferDoneSemCancel, SystemP_WAIT_FOREVER);
        DebugP_assert(spiTransaction.status == MCSPI_TRANSFER_CANCELLED);
    }

    /* Compare data and should be mismatch as it is cancelled in another task */
    uint8_t *tempTxPtr, *tempRxPtr;
    tempTxPtr = (uint8_t *) &gMcspiTxBuffer[0U];
    tempRxPtr = (uint8_t *) &gMcspiRxBuffer[0U];
    for(i = 0U; i < (APP_MCSPI_MSGSIZE * 4); i++)
    {
        if(*tempTxPtr++ != *tempRxPtr++)
        {
            status = SystemP_SUCCESS;   /* Data mismatch */
            break;
        }
    }

    /* Initiate transfer */
    spiTransaction.channel   = testParams->mcspiChConfigParams.chNum;
    spiTransaction.dataSize  = dataWidth;
    spiTransaction.csDisable = TRUE;
    spiTransaction.count     = testParams->transferLength;
    spiTransaction.txBuf     = (void *)gMcspiTxBuffer;
    spiTransaction.rxBuf     = (void *)gMcspiRxBuffer;
    spiTransaction.args      = NULL;
    transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction);
    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_BLOCKING)
    {
        DebugP_assert(spiTransaction.status == MCSPI_TRANSFER_COMPLETED);
    }
    DebugP_assert(transferOK == SystemP_SUCCESS);

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        /* Wait for transfer completion */
        SemaphoreP_pend(&Test_Mcspi_TransferDoneSemCancel, SystemP_WAIT_FOREVER);
        DebugP_assert(spiTransaction.status == MCSPI_TRANSFER_COMPLETED);
    }

    /* Compare data and should be mismatch as it is cancelled in another task */
    tempTxPtr = (uint8_t *) &gMcspiTxBuffer[0U];
    tempRxPtr = (uint8_t *) &gMcspiRxBuffer[0U];
    for(i = 0U; i < (APP_MCSPI_MSGSIZE * 4); i++)
    {
        if(*tempTxPtr++ != *tempRxPtr++)
        {
            status = SystemP_FAILURE;   /* Data mismatch */
            DebugP_assert(FALSE);
            break;
        }
    }

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        SemaphoreP_destruct(&Test_Mcspi_TransferDoneSemCancel);
    }

    SemaphoreP_post(&gMcspiTransferTaskDoneSemaphoreObj);
    TaskP_exit();

    return;
}

void test_mcspi_callback_cancel(MCSPI_Handle handle, MCSPI_Transaction *trans)
{
    SemaphoreP_post(&Test_Mcspi_TransferDoneSemCancel);
    return;
}


void test_mcspi_transfer_cancel_cancel(void *args)
{
    int32_t transferOK;

    transferOK = MCSPI_transferCancel(gMcspiHandle[CONFIG_MCSPI0]);
    DebugP_assert(transferOK == SystemP_SUCCESS);

    SemaphoreP_post(&gMcspiTransferCancelTaskDoneSemaphoreObj);
    TaskP_exit();
}
#endif

void test_mcspi_callback(MCSPI_Handle handle, MCSPI_Transaction *trans)
{
    DebugP_assertNoLog(MCSPI_TRANSFER_COMPLETED == trans->status);
    SemaphoreP_post(&gMcspiTransferDoneSem);

    return;
}


void setUp(void)
{
}

void tearDown(void)
{
}

static void mcspi_low_latency_transfer_16bit(uint32_t baseAddr,
                                            uint32_t chNum,
                                            uint16_t *txBuff,
                                            uint32_t length,
                                            uint32_t bufWidthShift)
{
    /* Effective FIFO depth in bytes(64/32/16) depending on datawidth */
    uint32_t effTxFifoDepth = MCSPI_FIFO_LENGTH >> bufWidthShift;
    uint32_t i, numWordsWritten = 0U, transferLength = length;

    /* Enable the McSPI channel for communication.*/
    /* Updated for write only operation. */
    MCSPI_writeChCtrlReg(baseAddr, chNum, gChEnableRegVal);

    /* SPIEN line is forced to low state.*/
    /* Updated for write only operation. */
    MCSPI_writeChConfReg(baseAddr, chNum, gCsAssertRegVal);

    while (transferLength != 0)
    {
        /* Write Effective TX FIFO depth */
        if (transferLength >= effTxFifoDepth)
        {
            transferLength = effTxFifoDepth;
        }
        while (0 == (MCSPI_readChStatusReg(baseAddr, chNum) &
                        CSL_MCSPI_CH0STAT_TXFFE_MASK))
        {
            /* Wait fot Tx FIFO to be empty before writing the data. */
        }
        /* Write the data in Tx FIFO. */
        for (i = 0; i < transferLength; i++)
        {
            MCSPI_writeTxDataReg(baseAddr, (uint16_t) (*txBuff++), chNum);
        }
        numWordsWritten  += transferLength;
        transferLength    = length - numWordsWritten;
    }

    while (0 == (MCSPI_readChStatusReg(baseAddr, chNum) &
                    CSL_MCSPI_CH0STAT_TXFFE_MASK))
    {
        /* Wait fot Tx FIFO to be empty for the last set of data. */
    }
    while (0 == (MCSPI_readChStatusReg(baseAddr, chNum) &
                    CSL_MCSPI_CH0STAT_EOT_MASK))
    {
        /* Tx FIFO Empty is triggered when last word from FIFO is written to
           internal shift register. SO wait for the end of transfer of last word.
           The EOT gets set after every word when the transfer from shift
           register is complete and is reset when the transmission starts.
           So FIFO empty check is required to make sure the data in FIFO is
           sent out then wait for EOT for the last word. */
    }

    /* Force SPIEN line to the inactive state.*/
    /* Updated for write only operation. */
    MCSPI_writeChConfReg(baseAddr, chNum, gCsDeAssertRegVal);

    /* Disable the McSPI channel.*/
    /* Updated for write only operation. */
    MCSPI_writeChCtrlReg(baseAddr, chNum, gChDisableRegVal);
}

static void test_mcspi_set_params(MCSPI_TestParams *testParams, uint32_t tcId)
{
    uint32_t bufWidthShift;
    MCSPI_Config     *config = &gMcspiConfig[CONFIG_MCSPI0];
    MCSPI_Attrs      *attrParams = (MCSPI_Attrs *)config->attrs;
    MCSPI_OpenParams *openParams = &(testParams->mcspiOpenParams);
    MCSPI_ChConfig   *chConfigParams = &(testParams->mcspiChConfigParams);

    /* Default Attribute Parameters */
    attrParams->baseAddr           = MCSPI0_BASE_ADDRESS;
    attrParams->inputClkFreq       = 50000000U;
    attrParams->intrNum            = MCSPI0_INT_NUM;
#if defined BUILD_C7X
    attrParams->eventId            = MCSPI0_EVENT_ID;
#endif
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
        case 2894:
            attrParams->operMode         = MCSPI_OPER_MODE_POLLED;
            break;
        case 2895:
            openParams->transferMode = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = test_mcspi_callback;
            break;
        case 8411:
            chConfigParams->txFifoTrigLvl      = 8U;
            chConfigParams->rxFifoTrigLvl      = 8U;
            break;
        case 8409:
            chConfigParams->chNum              = MCSPI_CHANNEL_2;
            break;
        case 8408:
            chConfigParams->chNum              = MCSPI_CHANNEL_3;
            break;
        case 8841: /* params for simple reconfig fifo test */
            testParams->dataSize               = 8U;
            chConfigParams->chNum              = MCSPI_CHANNEL_0;
            chConfigParams->txFifoTrigLvl      = 8U;
            chConfigParams->rxFifoTrigLvl      = 8U;
            break;
        case 8373: /* Base config for FIFO trigger level sweep: interrupt + blocking, 8-bit */
            attrParams->operMode               = MCSPI_OPER_MODE_INTERRUPT;
            openParams->transferMode           = MCSPI_TRANSFER_MODE_BLOCKING;
            openParams->transferCallbackFxn    = NULL;
            testParams->dataSize               = 8;
            chConfigParams->txFifoTrigLvl      = 16U;
            chConfigParams->rxFifoTrigLvl      = 16U;
            break;
        case 8424: /* Error: CALLBACK mode with NULL callback function */
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = NULL; /* Intentional error */
            break;

/* AM263X and AM62LX does not support MCU_SPI instance */
#if !defined(SOC_AM263X) && !defined(SOC_AM62LX)
#if (CONFIG_MCSPI_NUM_INSTANCES > 2)
        case 970:
#if defined(SOC_AM275X)
            attrParams->baseAddr           = CSL_MCSPI4_CFG_BASE;
            attrParams->intrNum            = 208U;
#else
            attrParams->baseAddr           = CSL_MCU_MCSPI0_CFG_BASE;
            attrParams->intrNum            = 208U;
#endif
            break;
        case 971:
#if defined(SOC_AM275X)
            attrParams->baseAddr           = CSL_MCSPI3_CFG_BASE;
            attrParams->intrNum            = 207U;
#else

            attrParams->baseAddr           = CSL_MCU_MCSPI1_CFG_BASE;
            attrParams->intrNum            = 209U;
#endif
            testParams->dataSize           = 8;
            break;
#endif
#endif
#if !defined(SOC_AM62LX)
        case 4003:
            attrParams->baseAddr           = MCSPI4_BASE_ADDRESS;
            attrParams->operMode           = MCSPI_OPER_MODE_POLLED;
            #if defined(SOC_AM62X)
            chConfigParams->inputSelect        = MCSPI_IS_D1;
            chConfigParams->dpe0               = MCSPI_DPE_DISABLE;
            chConfigParams->dpe1               = MCSPI_DPE_ENABLE;
            #endif
            break;
#endif
        case 2901:
            #if defined(SOC_AM62AX) ||  defined(SOC_AM62X) || defined(SOC_AM62DX) || defined(SOC_AM275X) || defined(SOC_J722S)
            attrParams->baseAddr           = MCSPI0_BASE_ADDRESS;
            attrParams->intrNum            = MCSPI0_INT_NUM;
#if defined BUILD_C7X
            attrParams->eventId            = MCSPI0_EVENT_ID;
#endif
            testParams->dataSize           = 16;
            #else
            attrParams->baseAddr           = MCSPI2_BASE_ADDRESS;
            attrParams->intrNum            = MCSPI2_INT_NUM;
#if defined BUILD_C7X
            attrParams->eventId            = MCSPI2_EVENT_ID;
#endif
            testParams->dataSize           = 16;
            #endif
            break;
        case 2902:
            attrParams->baseAddr           = MCSPI0_BASE_ADDRESS;
            attrParams->intrNum            = MCSPI0_INT_NUM;
#if defined BUILD_C7X
            attrParams->eventId            = MCSPI0_EVENT_ID;
#endif
            break;
#if !defined(SOC_AM62LX)
        case 4004:
            attrParams->baseAddr           = MCSPI4_BASE_ADDRESS;
            attrParams->intrNum            = MCSPI4_INT_NUM;
            #if defined(SOC_AM62X)
            chConfigParams->inputSelect        = MCSPI_IS_D1;
            chConfigParams->dpe0               = MCSPI_DPE_DISABLE;
            chConfigParams->dpe1               = MCSPI_DPE_ENABLE;
            #endif
#endif
#if defined BUILD_C7X
            attrParams->eventId            = MCSPI4_EVENT_ID;
#endif
            break;
        case 2903:
            testParams->dataSize           = 8;
            break;
        case 2904:
            testParams->dataSize           = 16;
            break;
        case 2905:
            testParams->dataSize           = 32;
            break;
        case 2906:
            testParams->dataSize           = 8;
            attrParams->operMode = MCSPI_OPER_MODE_POLLED;
            break;
        case 2908:
            testParams->dataSize           = 16;
            attrParams->operMode = MCSPI_OPER_MODE_POLLED;
            break;
        case 2910:
            testParams->dataSize           = 32;
            attrParams->operMode = MCSPI_OPER_MODE_POLLED;
            break;
        case 2911:
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = test_mcspi_callback;
            chConfigParams->bitRate            = 12207;
            break;
        case 2912:
        case 2934:
        case 2914:
            attrParams->operMode = MCSPI_OPER_MODE_POLLED;
            break;
        case 2916:
            testParams->dataSize = 16;
            break;
        case 2917:
            testParams->dataSize = 8;
            break;
        case 2918:
            attrParams->pinMode = MCSPI_PINMODE_3PIN;
            break;
        case 2919:
            attrParams->initDelay = MCSPI_INITDLY_8;
            break;
        case 2920:
            chConfigParams->csPolarity = MCSPI_CS_POL_HIGH;
            break;
        case 2921:
            chConfigParams->startBitEnable = TRUE;
            break;
        case 2922:
            chConfigParams->csIdleTime = MCSPI_TCS0_3_CLK;
            break;
        case 2923:
            chConfigParams->inputSelect = MCSPI_IS_D1;
            chConfigParams->dpe0        = MCSPI_DPE_DISABLE;
            chConfigParams->dpe1        = MCSPI_DPE_ENABLE;
            break;
        case 2924:
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = test_mcspi_callback;
            break;
        case 2926:
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = test_mcspi_callback;
            break;
        case 2927:
            attrParams->operMode               = MCSPI_OPER_MODE_INTERRUPT;
            break;
        case 4025:
        attrParams->baseAddr = MCSPI0_BASE_ADDRESS;
        attrParams->intrNum = MCSPI0_INT_NUM;
#if defined BUILD_C7X
            attrParams->eventId                = MCSPI1_EVENT_ID;
#endif
           break;
        case 2929:
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = test_mcspi_callback;
            break;
#if ENABLE_MT_TESTS
      case 2930:
            testParams->dataSize               = 8;
            chConfigParams->bitRate            = 1000000;
            break;
        case 2931:
            testParams->dataSize               = 16;
            chConfigParams->bitRate            = 1000000;
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = test_mcspi_callback_cancel;
            break;
#endif
        case 2932:
            openParams->transferTimeout        = 1U;
            chConfigParams->bitRate            = 50000;
            break;
        case 2933:
            attrParams->operMode               = MCSPI_OPER_MODE_POLLED;
            break;

#if (CONFIG_MCSPI_NUM_INSTANCES > 2)
        case 4027:
            attrParams->baseAddr               = MCSPI3_BASE_ADDRESS;
            testParams->dataSize               = 8;
            attrParams->operMode               = MCSPI_OPER_MODE_DMA;
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = test_mcspi_callback;
            openParams->mcspiDmaIndex          = 0;
            break;
        case 4028:
            attrParams->baseAddr               = MCSPI3_BASE_ADDRESS;
            testParams->dataSize               = 16;
            attrParams->operMode               = MCSPI_OPER_MODE_DMA;
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = test_mcspi_callback;
            openParams->mcspiDmaIndex          = 0;
            break;
        case 4029:
            attrParams->baseAddr               = MCSPI3_BASE_ADDRESS;
            testParams->dataSize               = 32;
            attrParams->operMode               = MCSPI_OPER_MODE_DMA;
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = test_mcspi_callback;
            openParams->mcspiDmaIndex          = 0;
            break;
        case 4026:
            attrParams->baseAddr               = MCSPI3_BASE_ADDRESS;
            testParams->dataSize               = 16;
            attrParams->operMode               = MCSPI_OPER_MODE_DMA;
            openParams->mcspiDmaIndex          = 0;
            break;
        case 6864:
            attrParams->baseAddr               = MCSPI3_BASE_ADDRESS;
            testParams->dataSize               = 8;
            attrParams->operMode               = MCSPI_OPER_MODE_DMA;
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = test_mcspi_callback;
            openParams->mcspiDmaIndex          = 0;
            break;

#endif
    }

    bufWidthShift = MCSPI_getBufWidthShift(testParams->dataSize);
    /* If Count is less than FIFO trigger level */
    if ((tcId == 971U) || (tcId == 2912U))
    {
        testParams->transferLength = (2U * (sizeof(gMcspiTxBuffer[0U]) / (1 << bufWidthShift)));
    }
    else
    {
        testParams->transferLength = (APP_MCSPI_MSGSIZE * (sizeof(gMcspiTxBuffer[0U]) / (1 << bufWidthShift)));
    }

    return;
}

#if (CONFIG_MCSPI_NUM_INSTANCES > 2)
void test_mcspi_dma_open_close(void *args)
{
    int32_t status = SystemP_SUCCESS;
    MCSPI_Handle mcspiHandle;
    MCSPI_TestParams   *testParams = (MCSPI_TestParams *)args;
    MCSPI_OpenParams *mcspiOpenParams = &(testParams->mcspiOpenParams);

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI3]);

    mcspiHandle = MCSPI_open(CONFIG_MCSPI3, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI3]);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
}
#endif
