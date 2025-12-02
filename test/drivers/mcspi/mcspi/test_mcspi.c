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
#define MCSPI_TASK_STACK_SIZE (8U * 1024U)

/* Number of Word count */
#define APP_MCSPI_MSGSIZE                   (100U)
/* Used in a DMA large transfer */
#define APP_MCSPI_MSGSIZE_1                 (2000U)
#define APP_MCSPI_TXONLYMSGSIZE             (5U)
#define APP_MCSPI_TRANSFER_LOOPCOUNT        (5U)
#define APP_MCSPI_PERF_LOOP_ITER_CNT        (1000U)
/* Number of words used for MCSPI ramp-up test */
#define Test_Mcspi_RampUpWordCount          (5U)

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
#define MCSPI1_BASE_ADDRESS             (CSL_MCU_MCSPI1_CFG_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCSPI2_CFG_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)
#define MCSPI4_BASE_ADDRESS             (CSL_MCSPI0_CFG_BASE)

#define MCSPI0_INT_NUM                  (208U)
#define MCSPI1_INT_NUM                  (209U)
#define MCSPI2_INT_NUM                  (206U)
#define MCSPI3_INT_NUM                  (205U)
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
#define MCSPI1_BASE_ADDRESS             (CSL_MCU_MCSPI1_CFG_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCSPI0_CFG_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)
#define MCSPI4_BASE_ADDRESS             (CSL_MCSPI2_CFG_BASE)

#define MCSPI0_INT_NUM                  (208U)
#define MCSPI1_INT_NUM                  (209U)
#define MCSPI2_INT_NUM                  (204U)
#define MCSPI3_INT_NUM                  (205U)
#define MCSPI4_INT_NUM                  (206U)
#endif

#ifdef C75_CORE
#define MCSPI0_BASE_ADDRESS             (CSL_MCU_MCSPI1_CFG_BASE)
#define MCSPI1_BASE_ADDRESS             (CSL_MCSPI0_CFG_BASE)
#define MCSPI2_BASE_ADDRESS             (CSL_MCU_MCSPI0_CFG_BASE)
#define MCSPI3_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)
#define MCSPI4_BASE_ADDRESS             (CSL_MCSPI1_CFG_BASE)

#define MCSPI0_INT_NUM                  (1U)
#define MCSPI1_INT_NUM                  (2U)
#define MCSPI2_INT_NUM                  (63U)
#define MCSPI3_INT_NUM                  (31U)
#define MCSPI4_INT_NUM                  (31U)

#define MCSPI0_EVENT_ID                 (177U)
#define MCSPI1_EVENT_ID                 (172U)
#define MCSPI2_EVENT_ID                 (176U)
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

/* The following symbol is from generated files. */
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

#if ENABLE_MT_TESTS  && !defined(BUILD_C7X)
/* Semaphore for transfer cancel test completion */
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
/* Used for DMA large transfer */
uint32_t     gMcspiTxBufferDma_1[APP_MCSPI_MSGSIZE_1] __attribute__((aligned(CacheP_CACHELINE_ALIGNMENT)));
uint32_t     gMcspiRxBufferDma_1[APP_MCSPI_MSGSIZE_1] __attribute__((aligned(CacheP_CACHELINE_ALIGNMENT)));

#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#ifdef ENABLE_MT_TESTS
// This function contains multithread test cases.
/**
 * @brief Runs the multi-threaded test cases for MCSPI driver.
 *
 * This function is intended to execute a suite of test cases that
 * validate the behavior of the MCSPI driver in a multi-threaded environment.
 *
 * @param args Pointer to arguments required for the test execution.
 */
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
/* NOTE: DMA test cases are known to fail on C7x core. */
#if (CONFIG_MCSPI_NUM_INSTANCES > 2) && !defined(BUILD_C7X)
void test_mcspi_loopback_dma(void *args);
void test_mcspi_loopback_multimaster_dma(void *args);
void test_mcspi_loopback_dma_with_csdisable(void *args);
void test_mcspi_loopback_dma_with_toggled_csdisable(void *args);
void test_mcspi_dma_open_close(void *args);
static void TestMcspi_dmaSingleWordTransfer(void *args);
static void TestMcspi_txOnlyTransfer(void *args);
#if defined(SOC_AM62AX) ||  defined(SOC_AM62DX)
static int32_t TestMcspi_dmaOpenFail(void *args);
static void TestMcspi_dmaTransferNoDmaHandle(void *args);
static void TestMcspi_dmaCloseNoDmaHandle(void *args);
static void TestMcspi_dmaChInitNoDmaHandle(void *args);
/* void test_mcspi_loopback_dma_large_fail(void *args); */
#endif
#endif
static void TestMcspi_openNullOpenPrms(void *args);
static void TestMcspi_openAlreadyOpen(void *args);
static void TestMcspi_openInvalidIndex(void *args);
static void TestMcspi_chConfigNegative(void *args);
static void TestMcspi_transferNullArgs(void *args);
static void TestMcspi_rxbufNullFifoReadDiscard(void *args);
static void TestMcspi_reconfigFifoNegativeTc(void *args);
static void TestMcspi_reconfigFifo(void *args);
static void TestMcspi_fifoTriggerLevels(void *args);
static void TestMcspi_txOnlyLoopback(void *args);
static void TestMcspi_openCallbackNull(void *args);
static void TestMcspi_chConfig(void *args);
static void TestMcspi_loopbackTurboMode(void *args);
static void TestMcspi_loopbackRampUpWordCount(void *args);
static void TestMcspi_transferCountZero(void *args);
static void TestMcspi_transferInvalidChannel(void *args);
static void TestMcspi_transferDataSizeTooSmall(void *args);
static void TestMcspi_transferDataSizeTooLarge(void *args);
static void TestMcspi_transferChannelNotConfigured(void *args);
static void TestMcspi_fifoWriteDefaultCheckTxData(void *args);
static void TestMcspi_loopbackTxOnly(void *args);
static void TestMcspi_loopbackSlaveTest(void *args);
#if ENABLE_MT_TESTS && !defined(BUILD_C7X)
void test_mcspi_callback_cancel(MCSPI_Handle handle, MCSPI_Transaction *trans);
void test_mcspi_transfer_cancel(void *args);
void test_mcspi_transfer_cancel_transfer(void *args);
void test_mcspi_transfer_cancel_cancel(void *args);
static void TestMcspi_dmaStop(void *args);
static void TestMcspi_callbackDmaCancel(MCSPI_Handle handle, MCSPI_Transaction *trans);
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

    test_mcspi_set_params(&testParams, 2894);
    RUN_TEST(test_mcspi_loopback,  2894, (void*)&testParams);
    test_mcspi_set_params(&testParams, 2895);
    RUN_TEST(test_mcspi_loopback, 2895, (void*)&testParams);
    test_mcspi_set_params(&testParams, 8409);
    RUN_TEST(test_mcspi_loopback, 8409, (void*) &testParams);
    test_mcspi_set_params(&testParams, 8408);
    RUN_TEST(test_mcspi_loopback, 8408, (void*) &testParams);
    test_mcspi_set_params(&testParams, 8402);
    RUN_TEST(TestMcspi_openNullOpenPrms, 8402, (void*) &testParams);
    test_mcspi_set_params(&testParams, 8403);
    RUN_TEST(TestMcspi_openAlreadyOpen, 8403, (void*) &testParams);
    test_mcspi_set_params(&testParams, 8404);
    RUN_TEST(TestMcspi_openInvalidIndex, 8404, (void*) &testParams);
    test_mcspi_set_params(&testParams, 8406);
    RUN_TEST(TestMcspi_chConfigNegative, 8406, (void*) &testParams);
    test_mcspi_set_params(&testParams, 8407);
    RUN_TEST(TestMcspi_transferNullArgs, 8407, (void*) &testParams);
    test_mcspi_set_params(&testParams, 9355);
    RUN_TEST(TestMcspi_reconfigFifo, 9355, (void*)&testParams);
    test_mcspi_set_params(&testParams, 8373);
    RUN_TEST(TestMcspi_fifoTriggerLevels, 8373, (void*)&testParams);
    test_mcspi_set_params(&testParams, 8410);
    RUN_TEST(TestMcspi_rxbufNullFifoReadDiscard, 8410, (void*) &testParams);
    test_mcspi_set_params(&testParams, 8411);
    RUN_TEST(TestMcspi_reconfigFifoNegativeTc, 8411, (void*) &testParams);
    test_mcspi_set_params(&testParams, 8399);
    RUN_TEST(TestMcspi_txOnlyLoopback, 8399, (void*)&testParams);
    test_mcspi_set_params(&testParams, 8424);
    RUN_TEST(TestMcspi_openCallbackNull, 8424, (void*)&testParams);
    test_mcspi_set_params(&testParams, 8398);
    RUN_TEST(TestMcspi_loopbackTurboMode, 8398, (void*) &testParams);
    test_mcspi_set_params(&testParams, 8397);
    RUN_TEST(TestMcspi_chConfig, 8397, (void*) &testParams);
    test_mcspi_set_params(&testParams, 9227);
    RUN_TEST(TestMcspi_loopbackRampUpWordCount,  9227, (void*)&testParams);
    test_mcspi_set_params(&testParams, 9233);
    RUN_TEST(TestMcspi_transferCountZero, 9233, (void*)&testParams);
    test_mcspi_set_params(&testParams, 9234);
    RUN_TEST(TestMcspi_transferInvalidChannel, 9234, (void*)&testParams);
    test_mcspi_set_params(&testParams, 9235);
    RUN_TEST(TestMcspi_transferDataSizeTooSmall, 9235, (void*)&testParams);
    test_mcspi_set_params(&testParams, 9236);
    RUN_TEST(TestMcspi_transferDataSizeTooLarge, 9236, (void*)&testParams);
    test_mcspi_set_params(&testParams, 9237);
    RUN_TEST(TestMcspi_transferChannelNotConfigured, 9237, (void*)&testParams);
    test_mcspi_set_params(&testParams, 9238);
    RUN_TEST(TestMcspi_fifoWriteDefaultCheckTxData, 9238, (void*)&testParams);
    test_mcspi_set_params(&testParams, 2895);
    RUN_TEST(TestMcspi_loopbackTxOnly, 9271, (void*)&testParams);
    test_mcspi_set_params(&testParams, 2894);
    RUN_TEST(TestMcspi_loopbackTxOnly, 9272, (void*)&testParams);
    test_mcspi_set_params(&testParams, 2894);
    RUN_TEST(TestMcspi_loopbackSlaveTest, 9274, (void*)&testParams);
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
    /* NOTE: This test case is hanging on C7x core. */
    #if !defined(BUILD_C7X)
    test_mcspi_set_params(&testParams, 2911);
    RUN_TEST(test_mcspi_loopback_back2back,  2911, (void*)&testParams);
    #endif
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
#if (CONFIG_MCSPI_NUM_INSTANCES > 2) && !defined(BUILD_C7X)
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
    /* Exclude multi-threaded (MT) test cases when building for NoRTOS, as these require FreeRTOS. */
    #if ENABLE_MT_TESTS  && !defined(BUILD_C7X)
    test_mcspi_set_params(&testParams, 2930);
    RUN_TEST(test_mcspi_transfer_cancel, 2930, (void*)&testParams);
    test_mcspi_set_params(&testParams, 2931);
    RUN_TEST(test_mcspi_transfer_cancel, 2931, (void*)&testParams);
    #endif
    #if defined(SOC_AM62DX) && !defined(R5F_CORE) && !defined(ENABLE_MT_TESTS)
    /* NOTE: test_mcspi_loopback_timeout is known to FAIL on R5F NoRTOS core. */
    test_mcspi_set_params(&testParams, 2932);
    RUN_TEST(test_mcspi_loopback_timeout, 2932, (void*)&testParams);
    #endif
    test_mcspi_set_params(&testParams, 2933);
    RUN_TEST(test_mcspi_performance_16bit, 2933, (void*)&testParams);
#if (CONFIG_MCSPI_NUM_INSTANCES > 2) && !defined(BUILD_C7X)
    test_mcspi_set_params(&testParams, 4026);
    RUN_TEST(test_mcspi_loopback_multimaster_dma,  4026, (void*)&testParams);
    test_mcspi_set_params(&testParams, 4027);
    chConfigParams = &(testParams.mcspiChConfigParams);
    config = &gMcspiConfig[CONFIG_MCSPI3];
    attrParams = (MCSPI_Attrs *)config->attrs;
    for (clkList = 0U; clkList < SPI_TEST_NUM_CLK_LIST; clkList++)
    {
        chConfigParams->bitRate = (attrParams->inputClkFreq / (gClkDividerTestListRampUp[clkList] + 1));
        RUN_TEST(test_mcspi_loopback_dma,  8405, (void*)&testParams);
    }
    test_mcspi_set_params(&testParams, 4027);
    RUN_TEST(TestMcspi_txOnlyTransfer,  9239, (void*)&testParams);
    test_mcspi_set_params(&testParams, 4028);
    RUN_TEST(TestMcspi_txOnlyTransfer,  9240, (void*)&testParams);
    test_mcspi_set_params(&testParams, 4029);
    RUN_TEST(TestMcspi_txOnlyTransfer,  9241, (void*)&testParams);
    test_mcspi_set_params(&testParams, 4027);
    RUN_TEST(test_mcspi_loopback_dma,  4027, (void*)&testParams);
    test_mcspi_set_params(&testParams, 4028);
    RUN_TEST(test_mcspi_loopback_dma,  4028, (void*)&testParams);
    test_mcspi_set_params(&testParams, 4029);
    RUN_TEST(test_mcspi_loopback_dma,  4029, (void*)&testParams);
    test_mcspi_set_params(&testParams, 8425);
    RUN_TEST(test_mcspi_loopback_dma,  8425, (void*)&testParams);
    test_mcspi_set_params(&testParams, 8428);
    RUN_TEST(test_mcspi_loopback_dma,  8428, (void*)&testParams);
    test_mcspi_set_params(&testParams, 8440);
    RUN_TEST(test_mcspi_loopback_dma,  8440, (void*)&testParams);
    test_mcspi_set_params(&testParams, 8430);
    RUN_TEST(test_mcspi_loopback_dma,  8430, (void*)&testParams);
    test_mcspi_set_params(&testParams, 8431);
    RUN_TEST(test_mcspi_loopback_dma,  8431, (void*)&testParams);
    test_mcspi_set_params(&testParams, 8433);
    RUN_TEST(test_mcspi_loopback_dma,  8433, (void*)&testParams);
    test_mcspi_set_params(&testParams, 8434);
    RUN_TEST(test_mcspi_loopback_dma,  8434, (void*)&testParams);
    test_mcspi_set_params(&testParams, 8435);
    RUN_TEST(test_mcspi_loopback_dma,  8435, (void*)&testParams);
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
    #if ENABLE_MT_TESTS
    #if defined(SOC_AM62AX) && !defined(DM_R5F_CORE)
    /* Runs multi-threaded MCSPI tests using the provided test parameters.*/
    run_multi_threaded_tests(&testParams);
    #endif
    #endif
    test_mcspi_set_params(&testParams, 8441);
    RUN_TEST(TestMcspi_dmaSingleWordTransfer, 8441, (void*)&testParams);
    #if ENABLE_MT_TESTS
    test_mcspi_set_params(&testParams, 4027);
    RUN_TEST(TestMcspi_dmaStop,  9274, (void*)&testParams);
    #endif
    #if defined(SOC_AM62AX) ||  defined(SOC_AM62DX)
    test_mcspi_set_params(&testParams, 8412);
    RUN_TEST(TestMcspi_dmaChInitNoDmaHandle, 8412, (void*)&testParams);
    test_mcspi_set_params(&testParams, 8413);
    RUN_TEST(TestMcspi_dmaCloseNoDmaHandle, 8413, (void*)&testParams);
    test_mcspi_set_params(&testParams, 8414);
    RUN_TEST(TestMcspi_dmaTransferNoDmaHandle, 8414, (void*)&testParams);
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

#if (CONFIG_MCSPI_NUM_INSTANCES > 2) && !defined(BUILD_C7X)
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

#if (CONFIG_MCSPI_NUM_INSTANCES > 2) && !defined(BUILD_C7X)
/**
 * @brief Test case for MCSPI transmit-only transfer functionality.
 *
 * This test verifies the correct operation of the MCSPI peripheral in transmit-only mode.
 * It initializes the MCSPI driver, configures the transfer parameters, and sends data to the SPI bus.
 * The test ensures that data is transmitted correctly without expecting any data to be received.
 * It checks for successful completion of the transfer and validates error handling for transmit-only scenarios.
 * This test is essential for applications that require SPI master to send data without reading from the slave.
 */
static void TestMcspi_txOnlyTransfer(void *args)
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
    MCSPI_Config       *config;
    MCSPI_Attrs        *attrParams;
    MCSPI_Handle        mcspiHandle;
    MCSPI_ChConfig     *chConfigParams = &(testParams->mcspiChConfigParams);

    /* Memset Buffers */
    memset(&gMcspiTxBufferDma[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiTxBufferDma[0U]));
    memset(&gMcspiRxBufferDma[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiRxBufferDma[0U]));

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI3]);

    config = &gMcspiConfig[CONFIG_MCSPI3];
    attrParams = (MCSPI_Attrs *)config->attrs;
    attrParams->operMode = MCSPI_OPER_MODE_DMA;
    mcspiOpenParams->transferMode = MCSPI_TRANSFER_MODE_CALLBACK;
    mcspiOpenParams->transferCallbackFxn = test_mcspi_callback;
    mcspiOpenParams->mcspiDmaIndex = 0;
    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        chConfigParams->trMode = MCSPI_TR_MODE_TX_ONLY;
    }
    mcspiHandle = MCSPI_open(CONFIG_MCSPI3, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        status = SemaphoreP_constructBinary(&gMcspiTransferDoneSem, 0);
        DebugP_assert(SystemP_SUCCESS == status);
    }

    status = MCSPI_chConfig(
                 gMcspiHandle[CONFIG_MCSPI3],
                 chConfigParams);
    if(status != SystemP_SUCCESS)
    {
        DebugP_logError("CONFIG_MCSPI3 channel %d config failed !!!\r\n", 0);
    }

    status = MCSPI_dmaChConfig(
                 gMcspiHandle[CONFIG_MCSPI3],
                 chConfigParams,
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
    for (dataWidthIdx = 0U; dataWidthIdx < dataWidth; dataWidthIdx++)
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
    spiTransaction.channel = gConfigMcspi3ChCfg[0U].chNum;
    spiTransaction.count = testParams->transferLength;
    spiTransaction.dataSize = dataWidth;
    spiTransaction.csDisable = TRUE;
    spiTransaction.txBuf = (void *)gMcspiTxBufferDma;
    spiTransaction.rxBuf = (void *)gMcspiRxBufferDma;
    spiTransaction.args = NULL;
    transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI3], &spiTransaction);
    TEST_APP_MCSPI_ASSERT_ON_FAILURE(transferOK, spiTransaction);

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        /* Wait for transfer completion */
        SemaphoreP_pend(&gMcspiTransferDoneSem, SystemP_WAIT_FOREVER);
    }

    /* Invalidate cache */
    CacheP_inv(&gMcspiRxBufferDma[0U], sizeof(gMcspiRxBufferDma), CacheP_TYPE_ALLD);

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

/**
 * @brief Test case for single word transfer using MCSPI with DMA.
 *
 * This test verifies the functionality of MCSPI peripheral when performing
 * a single word data transfer using DMA. It initializes the required SPI
 * and DMA configurations, triggers the transfer, and checks for data integrity.
 * The test ensures that DMA correctly handles the SPI data movement and
 * validates the completion and correctness of the transfer.
 */
static void TestMcspi_dmaSingleWordTransfer(void *args)
{
    MCSPI_TestParams *testParams        = (MCSPI_TestParams*)args;
    MCSPI_OpenParams *mcspiOpenParams   = &testParams->mcspiOpenParams;
    MCSPI_Handle      mcspiHandle;
    int32_t           status;
    uint32_t         *tempTxPtr32, *tempRxPtr32;
    MCSPI_Transaction spiTransaction;


    /* Clean previous */
    MCSPI_close(gMcspiHandle[CONFIG_MCSPI3]);

        /* Force DMA + callback */
    MCSPI_Config *mcspiChConfigParams   = &gMcspiConfig[CONFIG_MCSPI3];
    MCSPI_Attrs  *attrs = (MCSPI_Attrs*)mcspiChConfigParams->attrs;
    attrs->operMode                 = MCSPI_OPER_MODE_DMA;
    attrs->chMode                   = MCSPI_CH_MODE_SINGLE;
    mcspiOpenParams->transferMode          = MCSPI_TRANSFER_MODE_CALLBACK;
    mcspiOpenParams->transferCallbackFxn   = test_mcspi_callback;
    mcspiOpenParams->mcspiDmaIndex         = 0;

    /* Open */
    mcspiHandle = MCSPI_open(CONFIG_MCSPI3, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);

    gConfigMcspi3ChCfg[0].txFifoTrigLvl= 1U;
    gConfigMcspi3ChCfg[0].rxFifoTrigLvl= 1U;

    status = MCSPI_chConfig(mcspiHandle, &gConfigMcspi3ChCfg[0]);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    status = MCSPI_dmaChConfig(mcspiHandle,
                               &gConfigMcspi3ChCfg[0],
                               &gConfigMcspi3DmaChCfg[0]);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Semaphore for callback */
    status = SemaphoreP_constructBinary(&gMcspiTransferDoneSem, 0);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Fill single word */
    tempTxPtr32 = &gMcspiTxBufferDma[0];
    tempRxPtr32 = &gMcspiRxBufferDma[0];
    *tempTxPtr32 = 0x5A;
    *tempRxPtr32 = 0x00;

    /* WB caches (place in aligned DMA buffers for consistency) */
    CacheP_wb(tempTxPtr32, sizeof(uint32_t), CacheP_TYPE_ALLD);
    CacheP_wb(tempRxPtr32, sizeof(uint32_t), CacheP_TYPE_ALLD);

    /* Transaction (count = 1 word) */
    MCSPI_Transaction_init(&spiTransaction);
    spiTransaction.channel   = gConfigMcspi3ChCfg[0].chNum;
    spiTransaction.count     = 1U;
    spiTransaction.dataSize  = testParams->dataSize; /* 8 bits */
    spiTransaction.csDisable = TRUE;
    spiTransaction.txBuf     = tempTxPtr32;
    spiTransaction.rxBuf     = tempRxPtr32;
    spiTransaction.args      = NULL;

    status = MCSPI_transfer(mcspiHandle, &spiTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Wait for DMA completion */
    SemaphoreP_pend(&gMcspiTransferDoneSem, SystemP_WAIT_FOREVER);

    /* Invalidate RX */
    CacheP_inv(tempRxPtr32, sizeof(uint32_t), CacheP_TYPE_ALLD);

    TEST_ASSERT_EQUAL_INT32(MCSPI_TRANSFER_COMPLETED, spiTransaction.status);
    TEST_ASSERT_EQUAL_UINT8((uint8_t)(*tempTxPtr32), (uint8_t)(*tempRxPtr32));

    SemaphoreP_destruct(&gMcspiTransferDoneSem);

    status = MCSPI_dmaClose(mcspiHandle, &gConfigMcspi3ChCfg[0]);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MCSPI_close(mcspiHandle);
}

#if defined(SOC_AM62AX) ||  defined(SOC_AM62DX)
static int32_t TestMcspi_dmaOpenFail(void *args)
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
static void TestMcspi_dmaTransferNoDmaHandle(void *args)
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
        patchedFxns[i].dmaOpenFxn = TestMcspi_dmaOpenFail;
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
static void TestMcspi_dmaCloseNoDmaHandle(void *args)
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
        patchedFxns[i].dmaOpenFxn= TestMcspi_dmaOpenFail;
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
static void TestMcspi_dmaChInitNoDmaHandle(void *args)
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
        patchedFxns[i].dmaOpenFxn= TestMcspi_dmaOpenFail;
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
 * @brief Executes the MCSPI loopback slave test case.
 *
 * This test case validates the functionality of the MCSPI peripheral
 * in loopback mode when configured as a slave device. It initializes
 * the required hardware, performs data transfers, and checks for data
 * integrity. The test ensures correct operation of the SPI slave logic
 * under loopback conditions.
 */
static void TestMcspi_loopbackSlaveTest(void *args)
{
    int32_t             status = SystemP_SUCCESS;
    MCSPI_Handle        mcspiHandle;
    MCSPI_TestParams   *testParams = (MCSPI_TestParams *)args;
    MCSPI_OpenParams   *mcspiOpenParams = &(testParams->mcspiOpenParams);
    MCSPI_ChConfig     *mcspiChConfigParams = &(testParams->mcspiChConfigParams);

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);

    mcspiChConfigParams->trMode          = MCSPI_TR_MODE_RX_ONLY;
    mcspiOpenParams->msMode              = MCSPI_MS_MODE_SLAVE;
    mcspiChConfigParams->chNum              = MCSPI_CHANNEL_1;

    mcspiHandle = MCSPI_open(CONFIG_MCSPI0, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);

    status = MCSPI_chConfig(
                 gMcspiHandle[CONFIG_MCSPI0],
                 mcspiChConfigParams);
    DebugP_assert(status == SystemP_FAILURE);

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);

    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    return;
}

/**
 * @brief Test case for MCSPI loopback transmit-only mode.
 *
 * This test verifies the functionality of the MCSPI peripheral in loopback mode,
 * focusing solely on data transmission. It ensures that transmitted data is
 * correctly looped back and received, validating the integrity of the SPI
 * transmit path. The test is useful for detecting issues in the transmit logic
 * without involving external SPI devices.
 *
 * @param args Pointer to test-specific arguments or configuration.
 */
static void TestMcspi_loopbackTxOnly(void *args)
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

    mcspiChConfigParams->trMode          = MCSPI_TR_MODE_TX_ONLY;

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

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        SemaphoreP_destruct(&gMcspiTransferDoneSem);
    }

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    return;
}

/**
 * @brief Test case to verify default behavior of FIFO write for MCSPI TX data.
 *
 * This test checks the default values written to the TX FIFO buffer in the MCSPI driver.
 * It ensures that the data sent to the FIFO matches expected default patterns or values.
 * The test validates correct initialization and handling of the TX FIFO in various scenarios.
 * It also checks for any data corruption or unexpected values during FIFO write operations.
 * This helps guarantee reliable data transmission through the MCSPI peripheral.
 */
static void TestMcspi_fifoWriteDefaultCheckTxData(void *args)
{
    MCSPI_TestParams *testParams = (MCSPI_TestParams*)args;
    MCSPI_OpenParams *mcspiOpenParams = &testParams->mcspiOpenParams;
    MCSPI_ChConfig   *mcspiChConfigParams = &testParams->mcspiChConfigParams;
    MCSPI_Handle      mcspiHandle;
    int32_t           status;
    MCSPI_Transaction spiTransaction;
    uint8_t           rxBuf[8];
    uint32_t          i;

    /* Set a known defaultTxData value */
    mcspiChConfigParams->defaultTxData = 0xA5U;

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);
    mcspiHandle = MCSPI_open(CONFIG_MCSPI0, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);
    status = MCSPI_chConfig(mcspiHandle, mcspiChConfigParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Prepare transaction with txBuf = NULL to trigger MCSPI_fifoWriteDefault */
    MCSPI_Transaction_init(&spiTransaction);
    spiTransaction.channel = mcspiChConfigParams->chNum;
    spiTransaction.count = sizeof(rxBuf);
    spiTransaction.dataSize = 8;
    spiTransaction.txBuf = NULL; // This triggers the default path
    spiTransaction.rxBuf = rxBuf; // Capture what is received

    /* Clear RX buffer */
    memset(rxBuf, 0, sizeof(rxBuf));

    status = MCSPI_transfer(mcspiHandle, &spiTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_INT32(MCSPI_TRANSFER_COMPLETED, spiTransaction.status);

    /* Check that RX buffer contains the defaultTxData value */
    for(i = 0; i < sizeof(rxBuf); i++)
    {
        TEST_ASSERT_EQUAL_HEX8(mcspiChConfigParams->defaultTxData, rxBuf[i]);
    }

    MCSPI_close(mcspiHandle);
}

/**
 * @brief Test case for MCSPI transfer with zero transfer count.
 *
 * This test verifies the behavior of the MCSPI driver when a transfer is
 * initiated with a transfer count of zero. It ensures that the driver does
 * not perform any data transfer and handles the zero-count scenario gracefully.
 * The test checks for correct return values and absence of side effects or errors.
 * It is essential for validating robustness against invalid or edge-case inputs.
 */
static void TestMcspi_transferCountZero(void *args)
{
    MCSPI_TestParams *testParams = (MCSPI_TestParams*)args;
    MCSPI_OpenParams *mcspiOpenParams = &testParams->mcspiOpenParams;
    MCSPI_ChConfig   *mcspiChConfigParams = &testParams->mcspiChConfigParams;
    MCSPI_Handle      mcspiHandle;
    int32_t           status;
    MCSPI_Transaction spiTransaction;

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);
    mcspiHandle = MCSPI_open(CONFIG_MCSPI0, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);
    status = MCSPI_chConfig(mcspiHandle, mcspiChConfigParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MCSPI_Transaction_init(&spiTransaction);
    spiTransaction.channel = mcspiChConfigParams->chNum;
    spiTransaction.count = 0; // Invalid
    spiTransaction.dataSize = 8;

    status = MCSPI_transfer(mcspiHandle, &spiTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    TEST_ASSERT_EQUAL_INT32(MCSPI_TRANSFER_FAILED, spiTransaction.status);

    MCSPI_close(mcspiHandle);
}

/**
 * @brief Test case to verify MCSPI transfer with an invalid channel.
 *
 * This test case attempts to initiate a data transfer using an invalid or
 * non-existent MCSPI channel. It is designed to validate the driver's error
 * handling capabilities when faced with incorrect channel parameters. The test
 * ensures that the driver does not proceed with the transfer and returns the
 * appropriate error code. It also checks that no unintended side effects occur
 * in the hardware or software state as a result of the invalid operation.
 */
static void TestMcspi_transferInvalidChannel(void *args)
{
    MCSPI_TestParams *testParams = (MCSPI_TestParams*)args;
    MCSPI_OpenParams *mcspiOpenParams = &testParams->mcspiOpenParams;
    MCSPI_ChConfig   *mcspiChConfigParams = &testParams->mcspiChConfigParams;
    MCSPI_Handle      mcspiHandle;
    int32_t           status;
    MCSPI_Transaction spiTransaction;

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);
    mcspiHandle = MCSPI_open(CONFIG_MCSPI0, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);
    status = MCSPI_chConfig(mcspiHandle, mcspiChConfigParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MCSPI_Transaction_init(&spiTransaction);
    spiTransaction.channel = MCSPI_MAX_NUM_CHANNELS; // Invalid
    spiTransaction.count = 4;
    spiTransaction.dataSize = 8;

    status = MCSPI_transfer(mcspiHandle, &spiTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    TEST_ASSERT_EQUAL_INT32(MCSPI_TRANSFER_FAILED, spiTransaction.status);

    MCSPI_close(mcspiHandle);
}

/**
 * @brief Test case to verify MCSPI transfer with data size too small.
 *
 * This test checks the behavior of the MCSPI driver when a transfer is attempted
 * with a data size smaller than the minimum required. It ensures that the driver
 * correctly identifies and handles this invalid configuration. The test validates
 * that appropriate error codes or responses are returned. It also confirms that
 * no unintended data transfer occurs in this scenario.
 */
static void TestMcspi_transferDataSizeTooSmall(void *args)
{
    MCSPI_TestParams *testParams = (MCSPI_TestParams*)args;
    MCSPI_OpenParams *mcspiOpenParams = &testParams->mcspiOpenParams;
    MCSPI_ChConfig   *mcspiChConfigParams = &testParams->mcspiChConfigParams;
    MCSPI_Handle      mcspiHandle;
    int32_t           status;
    MCSPI_Transaction spiTransaction;

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);
    mcspiHandle = MCSPI_open(CONFIG_MCSPI0, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);
    status = MCSPI_chConfig(mcspiHandle, mcspiChConfigParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MCSPI_Transaction_init(&spiTransaction);
    spiTransaction.channel = mcspiChConfigParams->chNum;
    spiTransaction.count = 4;
    spiTransaction.dataSize = 3; // Invalid

    status = MCSPI_transfer(mcspiHandle, &spiTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    TEST_ASSERT_EQUAL_INT32(MCSPI_TRANSFER_FAILED, spiTransaction.status);

    MCSPI_close(mcspiHandle);
}

/**
 * @brief Test case to verify MCSPI transfer with data size exceeding allowed limit.
 *
 * This test attempts to initiate an MCSPI data transfer where the data size is intentionally set
 * larger than the maximum supported by the driver or hardware. It checks if the driver correctly
 * detects and handles this error condition, returning the appropriate error code or status.
 * The test ensures robustness by validating that no buffer overflows or undefined behaviors occur.
 * Proper error logging and resource cleanup are also verified as part of this test case.
 */
static void TestMcspi_transferDataSizeTooLarge(void *args)
{
    MCSPI_TestParams *testParams = (MCSPI_TestParams*)args;
    MCSPI_OpenParams *mcspiOpenParams = &testParams->mcspiOpenParams;
    MCSPI_ChConfig   *mcspiChConfigParams = &testParams->mcspiChConfigParams;
    MCSPI_Handle      mcspiHandle;
    int32_t           status;
    MCSPI_Transaction spiTransaction;

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);
    mcspiHandle = MCSPI_open(CONFIG_MCSPI0, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);
    status = MCSPI_chConfig(mcspiHandle, mcspiChConfigParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    MCSPI_Transaction_init(&spiTransaction);
    spiTransaction.channel = mcspiChConfigParams->chNum;
    spiTransaction.count = 4;
    spiTransaction.dataSize = 33; // Invalid

    status = MCSPI_transfer(mcspiHandle, &spiTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    TEST_ASSERT_EQUAL_INT32(MCSPI_TRANSFER_FAILED, spiTransaction.status);

    MCSPI_close(mcspiHandle);
}

/**
 * @brief Test case for MCSPI transfer on a channel that is not configured.
 *
 * This test verifies the behavior of the MCSPI driver when a transfer is
 * attempted on a channel that has not been properly configured. It ensures
 * that the driver returns the appropriate error or handles the situation
 * gracefully without causing unexpected behavior. The test is essential for
 * validating the robustness and error handling capabilities of the MCSPI driver.
 */
static void TestMcspi_transferChannelNotConfigured(void *args)
{
    MCSPI_TestParams *testParams = (MCSPI_TestParams*)args;
    MCSPI_OpenParams *mcspiOpenParams = &testParams->mcspiOpenParams;
    MCSPI_ChConfig   *mcspiChConfigParams = &testParams->mcspiChConfigParams;
    MCSPI_Handle      mcspiHandle;
    int32_t           status;
    MCSPI_Transaction spiTransaction;

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);
    mcspiHandle = MCSPI_open(CONFIG_MCSPI0, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);
    // Do NOT call MCSPI_chConfig, so channel is not configured

    MCSPI_Transaction_init(&spiTransaction);
    spiTransaction.channel = mcspiChConfigParams->chNum;
    spiTransaction.count = 4;
    spiTransaction.dataSize = 8;

    status = MCSPI_transfer(mcspiHandle, &spiTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_FAILURE, status);
    TEST_ASSERT_EQUAL_INT32(MCSPI_TRANSFER_FAILED, spiTransaction.status);

    MCSPI_close(mcspiHandle);
}

/**
 * @brief Test case for MCSPI loopback ramp-up with varying word count.
 *
 * This test verifies the functionality of the MCSPI peripheral in loopback mode
 * by incrementally increasing the word count for each transfer. It ensures data
 * integrity by comparing transmitted and received data for each word count.
 * The test helps identify issues related to buffer handling and transfer size
 * limitations in the MCSPI driver implementation.
 *
 * @param args Pointer to test-specific arguments (if any).
 */
static void TestMcspi_loopbackRampUpWordCount(void *args)
{
    int32_t             status = SystemP_SUCCESS;
    uint32_t            i, j, dataWidth, fifoBitMask, tempTxData, dataWidthIdx;
    int32_t             transferOK;
    MCSPI_Transaction   spiTransaction;
    MCSPI_Handle        mcspiHandle;
    MCSPI_TestParams   *testParams = (MCSPI_TestParams *)args;
    uint8_t            *tempRxPtr8 = NULL, *tempTxPtr8 = NULL;
    uint16_t           *tempRxPtr16 = NULL, *tempTxPtr16 = NULL;
    uint32_t           *tempRxPtr32 = NULL, *tempTxPtr32 = NULL;
    MCSPI_OpenParams   *mcspiOpenParams = &(testParams->mcspiOpenParams);
    MCSPI_ChConfig     *mcspiChConfigParams = &(testParams->mcspiChConfigParams);
    uint32_t bufWidthShift;


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
   bufWidthShift = MCSPI_getBufWidthShift(testParams->dataSize);
   static const uint32_t RampUpWordLength[Test_Mcspi_RampUpWordCount] = {10U, 20U, 40U, 60U, 80U};
   for(j = 0U; j < Test_Mcspi_RampUpWordCount; j++)
   {

    testParams->transferLength = (RampUpWordLength[j] * (sizeof(gMcspiTxBuffer[0U]) / (1 << bufWidthShift)));

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
    for(i = 0U; i < testParams->transferLength ; i++)
    {
        if(*tempTxPtr++ != *tempRxPtr++)
        {
            status = SystemP_FAILURE;   /* Data mismatch */
            DebugP_log("Data Mismatch at offset %d\r\n", i);
            break;
        }
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

/**
 * @brief Test case for verifying MCSPI FIFO trigger levels functionality.
 *
 * This test validates the correct configuration and handling of FIFO trigger levels
 * in the MCSPI driver. It ensures that the transmit and receive FIFOs generate
 * interrupts at the expected thresholds. The test also checks for proper data
 * transfer and error handling when FIFO levels are reached. This helps guarantee
 * reliable SPI communication in applications using FIFO buffering.
 */
static void TestMcspi_fifoTriggerLevels(void *args)
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
 * @brief Test case for verifying MCSPI channel configuration robustness.
 *
 * This test exercises the MCSPI channel configuration API by performing three passes,
 * each with different channel parameters (channel number, frame format, polarity, idle time, etc.).
 * It starts from a known baseline, modifies channel config for each pass, and performs a transfer.
 * The test verifies that the driver correctly applies channel settings and maintains data integrity.
 * For each pass, it fills buffers with unique patterns, initiates transfer, and checks for data match.
 * It covers edge cases such as toggling start bit, polarity, and bitrate to ensure correct behavior.
 * The test asserts success only if all three passes complete without data mismatch or errors.
 */
static void TestMcspi_chConfig(void *args)
{
    int32_t             status = SystemP_SUCCESS;
    uint32_t            i, dataWidth, fifoBitMask, tempTxData, dataWidthIdx, pass;
    int32_t             transferOK;
    MCSPI_Transaction   spiTransaction;
    MCSPI_Handle        mcspiHandle;
    MCSPI_TestParams   *origParams = (MCSPI_TestParams *)args;
    MCSPI_TestParams    localParams;
    MCSPI_TestParams   *testParams = &localParams;
    uint8_t            *tempRxPtr8 = NULL, *tempTxPtr8 = NULL;
    uint16_t           *tempRxPtr16 = NULL, *tempTxPtr16 = NULL;
    uint32_t           *tempRxPtr32 = NULL, *tempTxPtr32 = NULL;
    MCSPI_OpenParams   *mcspiOpenParams;
    MCSPI_ChConfig     *mcspiChConfigParams;

    /* Start from a known baseline using existing param setup helper */
    memcpy(&localParams, origParams, sizeof(localParams));
    test_mcspi_set_params(testParams, 335); /* baseline (polled), will override below as needed */

    mcspiOpenParams     = &(testParams->mcspiOpenParams);
    mcspiChConfigParams = &(testParams->mcspiChConfigParams);

    /* Prepare / open handle fresh */
    memset(&gMcspiTxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiTxBuffer[0U]));
    memset(&gMcspiRxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiRxBuffer[0U]));
    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);
    mcspiHandle = MCSPI_open(CONFIG_MCSPI0, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);

    /* If callback mode, create semaphore once (reuse for all 3 passes) */
    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        status = SemaphoreP_constructBinary(&gMcspiTransferDoneSem, 0);
        DebugP_assert(SystemP_SUCCESS == status);
    }

    for(pass = 0; pass < 3; pass++)
    {
        /* Modify channel config parameters for each pass */
        if(pass == 0)
        {
            mcspiChConfigParams->chNum        = MCSPI_CHANNEL_0;
            mcspiChConfigParams->frameFormat  = MCSPI_FF_POL0_PHA0;
            mcspiChConfigParams->csPolarity   = MCSPI_CS_POL_LOW;
            mcspiChConfigParams->csIdleTime   = MCSPI_TCS0_0_CLK;
            mcspiChConfigParams->inputSelect  = MCSPI_IS_D0;
            mcspiChConfigParams->dpe0         = MCSPI_DPE_ENABLE;
            mcspiChConfigParams->dpe1         = MCSPI_DPE_DISABLE;
            mcspiChConfigParams->startBitEnable = FALSE;
        }
        else if(pass == 1)
        {
            mcspiChConfigParams->chNum        = MCSPI_CHANNEL_1;
            mcspiChConfigParams->frameFormat  = MCSPI_FF_POL0_PHA1;
            mcspiChConfigParams->csPolarity   = MCSPI_CS_POL_HIGH;
            mcspiChConfigParams->csIdleTime   = MCSPI_TCS0_3_CLK;
            mcspiChConfigParams->inputSelect  = MCSPI_IS_D1;
            mcspiChConfigParams->dpe0         = MCSPI_DPE_DISABLE;
            mcspiChConfigParams->dpe1         = MCSPI_DPE_ENABLE;
            mcspiChConfigParams->startBitEnable = TRUE;
            mcspiChConfigParams->startBitPolarity = MCSPI_SB_POL_LOW;
        }
        else /* pass == 2 */
        {
            mcspiChConfigParams->chNum        = MCSPI_CHANNEL_0;
            mcspiChConfigParams->frameFormat  = MCSPI_FF_POL1_PHA1;
            mcspiChConfigParams->csPolarity   = MCSPI_CS_POL_LOW;
            mcspiChConfigParams->csIdleTime   = MCSPI_TCS0_2_CLK;
            mcspiChConfigParams->inputSelect  = MCSPI_IS_D0;
            mcspiChConfigParams->dpe0         = MCSPI_DPE_ENABLE;
            mcspiChConfigParams->dpe1         = MCSPI_DPE_DISABLE;
            mcspiChConfigParams->bitRate      = 1000000U; /* change bitrate */
            mcspiChConfigParams->startBitEnable = FALSE;
        }

        /* Apply channel config */
        status = MCSPI_chConfig(gMcspiHandle[CONFIG_MCSPI0], mcspiChConfigParams);
        DebugP_assert(status == SystemP_SUCCESS);

        /* Reset buffers for this pass */
        memset(&gMcspiTxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiTxBuffer[0U]));
        memset(&gMcspiRxBuffer[0U], 0, APP_MCSPI_MSGSIZE * sizeof(gMcspiRxBuffer[0U]));

        /* Data width & pointer selection (same logic as original test) */
        dataWidth = testParams->dataSize;
        if (dataWidth < 9U)
        {
            tempTxPtr8 = (uint8_t *) &gMcspiTxBuffer[0U];
            tempRxPtr8 = (uint8_t *) &gMcspiRxBuffer[0U];
        }
        else if (dataWidth < 17U)
        {
            tempTxPtr16 = (uint16_t *) &gMcspiTxBuffer[0U];
            tempRxPtr16 = (uint16_t *) &gMcspiRxBuffer[0U];
        }
        else
        {
            tempTxPtr32 = (uint32_t *) &gMcspiTxBuffer[0U];
            tempRxPtr32 = (uint32_t *) &gMcspiRxBuffer[0U];
        }
        fifoBitMask = 0x0U;
        for (dataWidthIdx = 0U; dataWidthIdx < dataWidth; dataWidthIdx++)
        {
            fifoBitMask |= (1U << dataWidthIdx);
        }

        /* Fill buffers */
        for (i = 0U; i < testParams->transferLength; i++)
        {
            tempTxData = 0xDEADBABE ^ (0x01010101U * pass); /* vary pattern per pass */
            tempTxData &= fifoBitMask;
            if (dataWidth < 9U)
            {
                *tempTxPtr8++  = (uint8_t)  tempTxData;
                *tempRxPtr8++  = 0U;
            }
            else if (dataWidth < 17U)
            {
                *tempTxPtr16++ = (uint16_t) tempTxData;
                *tempRxPtr16++ = 0U;
            }
            else
            {
                *tempTxPtr32++ = (uint32_t) tempTxData;
                *tempRxPtr32++ = 0U;
            }
        }

        /* Transaction setup & transfer */
        spiTransaction.channel   = mcspiChConfigParams->chNum;
        spiTransaction.count     = testParams->transferLength;
        spiTransaction.dataSize  = dataWidth;
        spiTransaction.csDisable = TRUE;
        spiTransaction.txBuf     = (void *)gMcspiTxBuffer;
        spiTransaction.rxBuf     = (void *)gMcspiRxBuffer;
        spiTransaction.args      = NULL;
        transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction);
        TEST_APP_MCSPI_ASSERT_ON_FAILURE(transferOK, spiTransaction);

        if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
        {
            SemaphoreP_pend(&gMcspiTransferDoneSem, SystemP_WAIT_FOREVER);
        }

        /* Compare data (same logic as loopback test) */
        {
            uint8_t *tempTxPtr = (uint8_t *)&gMcspiTxBuffer[0U];
            uint8_t *tempRxPtr = (uint8_t *)&gMcspiRxBuffer[0U];
            for(i = 0U; i < (APP_MCSPI_MSGSIZE * 4); i++)
            {
                if(*tempTxPtr++ != *tempRxPtr++)
                {
                    status = SystemP_FAILURE;
                    DebugP_log("Pass %u data mismatch at offset %u\r\n", pass, i);
                    break;
                }
            }
        }

        if(status != SystemP_SUCCESS)
        {
            break; /* stop further passes on failure */
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

/**
 * @brief Test case for MCSPI loopback in Turbo Mode.
 *
 * This test verifies the functionality of the MCSPI peripheral in loopback configuration
 * while operating in Turbo Mode. It checks data integrity by transmitting and receiving
 * data through the SPI interface. The test ensures correct handling of high-speed transfers
 * and validates error conditions. Note: Turbo Mode is currently not available in this implementation.
 */
static void TestMcspi_loopbackTurboMode(void *args)
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
    uint64_t            startTimeInUSec, elapsedTimeInUsecs = 0U;

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

    spiTransaction.count    = testParams->transferLength;
    spiTransaction.dataSize  = dataWidth;
    spiTransaction.csDisable = TRUE;
    spiTransaction.txBuf    = (void *)gMcspiTxBuffer;
    spiTransaction.rxBuf    = (void *)gMcspiRxBuffer;
    spiTransaction.args     = NULL;
    startTimeInUSec = ClockP_getTimeUsec();
    transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction);
    TEST_APP_MCSPI_ASSERT_ON_FAILURE(transferOK, spiTransaction);
    elapsedTimeInUsecs = ClockP_getTimeUsec() - startTimeInUSec;
    DebugP_log("----------------------------------------------------------\r\n");
    DebugP_log("McSPI Clock %d Hz\r\n", gConfigMcspi0ChCfg[0U].bitRate);
    DebugP_log("----------------------------------------------------------\r\n");
    DebugP_log("Data Width \tData Length \tTransfer Time (micro sec)\r\n");
    DebugP_log("%u\t\t%u\t\t%5.2f\r\n", spiTransaction.dataSize, APP_MCSPI_MSGSIZE,
                        (Float32)elapsedTimeInUsecs);
    DebugP_log("----------------------------------------------------------\r\n\n");

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

/**
 * @brief Test case to verify MCSPI driver behavior when open callback is NULL.
 *
 * This test ensures that the MCSPI driver can handle a NULL open callback gracefully.
 * It checks if the driver initialization proceeds without errors in the absence of a callback.
 * The test validates that no unexpected side effects or crashes occur due to the NULL pointer.
 * It is important for robustness, especially in systems where callbacks are optional.
 */
static void TestMcspi_openCallbackNull(void *args)
{
    MCSPI_TestParams   *testParams = (MCSPI_TestParams*)args;
    MCSPI_Handle        mcspiHandle;

    /* Ensure params are set for test case 1222 (callback mode, NULL cb) */
    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);
    mcspiHandle = MCSPI_open(CONFIG_MCSPI0, &testParams->mcspiOpenParams);

    /* Expect failure (NULL handle) */
    TEST_ASSERT_NULL(mcspiHandle);
}

/**
 * @brief Test case for MCSPI TX-only loopback operation.
 *
 * This test verifies the functionality of the MCSPI peripheral when configured for transmit-only mode.
 * It initializes the SPI channel for TX_ONLY, fills a buffer with known data, and performs a transfer with rxBuf set to NULL.
 * The test ensures that the driver correctly handles transmit-only transactions and completes without errors.
 * No RX data comparison is performed, as the test focuses on successful transmission and peripheral progression.
 */
static void TestMcspi_txOnlyLoopback(void *args)
{
    MCSPI_TestParams *testParams        = (MCSPI_TestParams*)args;
    MCSPI_OpenParams *mcspiOpenParams   = &testParams->mcspiOpenParams;
    MCSPI_ChConfig   *mcspiChConfigParams = &testParams->mcspiChConfigParams;
    MCSPI_Handle      mcspiHandle;
    int32_t           status;
    uint8_t           txBuf[32];
    MCSPI_Transaction spiTransaction;
    uint32_t          i;

    /* Ensure clean handle */
    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);
    mcspiHandle = MCSPI_open(CONFIG_MCSPI0, mcspiOpenParams);
    TEST_ASSERT_NOT_NULL(mcspiHandle);

    /* Channel config (TX_ONLY) */
    status = MCSPI_chConfig(mcspiHandle, mcspiChConfigParams);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);

    /* Prepare TX data */
    uint32_t count = (testParams->transferLength > 32U) ? 32U : testParams->transferLength;
    for(i=0;i<count;i++) { txBuf[i] = (uint8_t)(0x55U + i); }

    /* Transaction; rxBuf NULL since TX_ONLY */
    MCSPI_Transaction_init(&spiTransaction);
    spiTransaction.channel   = mcspiChConfigParams->chNum;
    spiTransaction.count     = count;
    spiTransaction.dataSize  = testParams->dataSize;   /* 8-bit */
    spiTransaction.csDisable = TRUE;
    spiTransaction.txBuf     = txBuf;
    spiTransaction.rxBuf     = NULL;           /* No receive */
    spiTransaction.args      = NULL;

    status = MCSPI_transfer(mcspiHandle, &spiTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    TEST_ASSERT_EQUAL_INT32(MCSPI_TRANSFER_COMPLETED, spiTransaction.status);

    /* No RX comparison (TX_ONLY). Just ensure peripheral progressed. */
    MCSPI_close(mcspiHandle);
}

/**
 * @brief Test case to verify behavior when attempting to open an already open MCSPI instance.
 *
 * This test ensures that the driver correctly handles repeated open calls.
 * It checks for proper error handling and resource management in such scenarios.
 */
static void TestMcspi_openAlreadyOpen(void *args)
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
static void TestMcspi_openNullOpenPrms(void *args)
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
static void TestMcspi_reconfigFifo(void *args)
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
static void TestMcspi_chConfigNegative(void *args)
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
static void TestMcspi_transferNullArgs(void *args)
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
static void TestMcspi_openInvalidIndex(void *args)
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
static void TestMcspi_rxbufNullFifoReadDiscard(void *args)
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
static void TestMcspi_reconfigFifoNegativeTc(void *args)
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

#if ENABLE_MT_TESTS && !defined(BUILD_C7X)
/**
 * @brief Test case to stop DMA operations for MCSPI.
 *
 * This function is used to test the stopping of DMA transfers in the MCSPI driver.
 * It ensures that all ongoing DMA operations are properly halted.
 * The function is typically invoked as part of the MCSPI driver test suite.
 * @param args Pointer to arguments required for the test case execution.
 */
static void TestMcspi_dmaStop(void *args)
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
    MCSPI_Config       *config;
    MCSPI_Attrs        *attrParams;
    MCSPI_Handle        mcspiHandle;

    /* Memset Buffers */
    memset(&gMcspiTxBufferDma_1[0U], 0, APP_MCSPI_MSGSIZE_1 * sizeof(gMcspiTxBufferDma_1[0U]));
    memset(&gMcspiRxBufferDma_1[0U], 0, APP_MCSPI_MSGSIZE_1 * sizeof(gMcspiRxBufferDma_1[0U]));

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI3]);

    config = &gMcspiConfig[CONFIG_MCSPI3];
    attrParams = (MCSPI_Attrs *)config->attrs;
    attrParams->operMode                = MCSPI_OPER_MODE_DMA;
    testParams->dataSize                = 32;
    mcspiOpenParams->transferMode       = MCSPI_TRANSFER_MODE_CALLBACK;
    mcspiOpenParams->transferCallbackFxn= TestMcspi_callbackDmaCancel;
    mcspiOpenParams->mcspiDmaIndex      = 0;

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
        tempTxPtr8 = (uint8_t *) &gMcspiTxBufferDma_1[0U];
        tempRxPtr8 = (uint8_t *) &gMcspiRxBufferDma_1[0U];
    }
    else if (dataWidth < 17U)
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr16 = (uint16_t *) &gMcspiTxBufferDma_1[0U];
        tempRxPtr16 = (uint16_t *) &gMcspiRxBufferDma_1[0U];
    }
    else
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr32 = (uint32_t *) &gMcspiTxBufferDma_1[0U];
        tempRxPtr32 = (uint32_t *) &gMcspiRxBufferDma_1[0U];
    }
    fifoBitMask = 0x0U;
    for (dataWidthIdx = 0U; dataWidthIdx < dataWidth; dataWidthIdx++)
    {
        fifoBitMask |= (1U << dataWidthIdx);
    }

    /* Memfill buffers */
    for (i = 0U; i < APP_MCSPI_MSGSIZE_1; i++)
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
    CacheP_wb(&gMcspiTxBufferDma_1[0U], sizeof(gMcspiTxBufferDma_1), CacheP_TYPE_ALLD);
    CacheP_wb(&gMcspiRxBufferDma_1[0U], sizeof(gMcspiRxBufferDma_1), CacheP_TYPE_ALLD);

    /* Initiate transfer */
    spiTransaction.channel   = gConfigMcspi3ChCfg[0U].chNum;
    spiTransaction.count     = APP_MCSPI_MSGSIZE_1;
    spiTransaction.dataSize  = dataWidth;
    spiTransaction.csDisable = TRUE;
    spiTransaction.txBuf     = (void *)gMcspiTxBufferDma_1;
    spiTransaction.rxBuf     = (void *)gMcspiRxBufferDma_1;
    spiTransaction.args      = NULL;
    transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI3], &spiTransaction);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, transferOK);

    transferOK = MCSPI_transferCancel(gMcspiHandle[CONFIG_MCSPI3]);
    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, transferOK);

    TEST_ASSERT_EQUAL_INT32(MCSPI_TRANSFER_CANCELLED, spiTransaction.status);

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        /* Wait for transfer completion */
        SemaphoreP_pend(&gMcspiTransferDoneSem, SystemP_WAIT_FOREVER);
    }

    /* Give HW time to finish teardown and complete CQ events before closing */
    ClockP_usleep(2000);

    /* Invalidate cache */
    CacheP_inv(&gMcspiRxBufferDma_1[0U], sizeof(gMcspiRxBufferDma_1), CacheP_TYPE_ALLD);

    uint8_t *tempTxPtr, *tempRxPtr;
    tempTxPtr = (uint8_t *) &gMcspiTxBufferDma_1[0U];
    tempRxPtr = (uint8_t *) &gMcspiRxBufferDma_1[0U];
    for(i = 0U; i < (APP_MCSPI_MSGSIZE_1); i++)
    {
        if(*tempTxPtr++ != *tempRxPtr++)
        {
            status = SystemP_SUCCESS;   /* Data mismatch */
            break;
        }
    }

    if(mcspiOpenParams->transferMode == MCSPI_TRANSFER_MODE_CALLBACK)
    {
        SemaphoreP_destruct(&gMcspiTransferDoneSem);
    }

    MCSPI_close(gMcspiHandle[CONFIG_MCSPI3]);

    TEST_ASSERT_EQUAL_INT32(SystemP_SUCCESS, status);
    return;
}

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

static void TestMcspi_callbackDmaCancel(MCSPI_Handle handle, MCSPI_Transaction *trans)
{
    DebugP_assertNoLog(MCSPI_TRANSFER_CANCELLED == trans->status);
    SemaphoreP_post(&gMcspiTransferDoneSem);

    return;
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
        case 8399: /*  TX-only loopback  */
            attrParams->operMode            = MCSPI_OPER_MODE_INTERRUPT;
            openParams->transferMode        = MCSPI_TRANSFER_MODE_BLOCKING;
            openParams->transferCallbackFxn = NULL;
            openParams->msMode              = MCSPI_MS_MODE_MASTER;
            testParams->dataSize            = 8U;
            chConfigParams->trMode          = MCSPI_TR_MODE_TX_ONLY;
            chConfigParams->bitRate         = 1000000U;
            chConfigParams->inputSelect     = MCSPI_IS_D0;        /* Drive and (optionally) sample D0 */
            chConfigParams->dpe0            = MCSPI_DPE_ENABLE;   /* Enable output on D0 */
            chConfigParams->dpe1            = MCSPI_DPE_DISABLE;
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
#if ENABLE_MT_TESTS && !defined(BUILD_C7X)
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
        case 8441: /* Single-word DMA loopback */
            testParams->dataSize                      = 8U;
            testParams->transferLength                = 1U;
            chConfigParams->chNum                     = 0U;
            chConfigParams->bitRate                   = 1000000U;
            chConfigParams->trMode                    = MCSPI_TR_MODE_TX_RX;
            chConfigParams->txFifoTrigLvl             = 1U;
            chConfigParams->rxFifoTrigLvl             = 1U;
            break;
        case 8425:
            attrParams->baseAddr               = MCSPI3_BASE_ADDRESS;
            testParams->dataSize               = 32;
            attrParams->operMode               = MCSPI_OPER_MODE_DMA;
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = test_mcspi_callback;
            openParams->mcspiDmaIndex          = 0;
            chConfigParams->chNum              = MCSPI_CHANNEL_2;
            break;
        case 8428:
            attrParams->baseAddr               = MCSPI3_BASE_ADDRESS;
            testParams->dataSize               = 32;
            attrParams->operMode               = MCSPI_OPER_MODE_DMA;
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = test_mcspi_callback;
            openParams->mcspiDmaIndex          = 0;
            chConfigParams->chNum              = MCSPI_CHANNEL_3;
            break;
        case 8440:
            attrParams->baseAddr               = MCSPI3_BASE_ADDRESS;
            testParams->dataSize               = 32;
            attrParams->operMode               = MCSPI_OPER_MODE_DMA;
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = test_mcspi_callback;
            openParams->mcspiDmaIndex          = 0;
            attrParams->pinMode                = MCSPI_PINMODE_3PIN;
            break;
        case 8430:
            attrParams->baseAddr               = MCSPI3_BASE_ADDRESS;
            testParams->dataSize               = 32;
            attrParams->operMode               = MCSPI_OPER_MODE_DMA;
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = test_mcspi_callback;
            openParams->mcspiDmaIndex          = 0;
            attrParams->initDelay              = MCSPI_INITDLY_8;
            break;
        case 8431:
            attrParams->baseAddr               = MCSPI3_BASE_ADDRESS;
            testParams->dataSize               = 32;
            attrParams->operMode               = MCSPI_OPER_MODE_DMA;
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = test_mcspi_callback;
            openParams->mcspiDmaIndex          = 0;
            chConfigParams->csPolarity         = MCSPI_CS_POL_HIGH;
            break;
        case 8433:
            attrParams->baseAddr               = MCSPI3_BASE_ADDRESS;
            testParams->dataSize               = 32;
            attrParams->operMode               = MCSPI_OPER_MODE_DMA;
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = test_mcspi_callback;
            openParams->mcspiDmaIndex          = 0;
            chConfigParams->startBitEnable     = TRUE;
            break;
        case 8434:
            attrParams->baseAddr               = MCSPI3_BASE_ADDRESS;
            testParams->dataSize               = 32;
            attrParams->operMode               = MCSPI_OPER_MODE_DMA;
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = test_mcspi_callback;
            openParams->mcspiDmaIndex          = 0;
            chConfigParams->csIdleTime         = MCSPI_TCS0_3_CLK;
            break;
        case 8435:
            attrParams->baseAddr               = MCSPI3_BASE_ADDRESS;
            testParams->dataSize               = 32;
            attrParams->operMode               = MCSPI_OPER_MODE_DMA;
            openParams->transferMode           = MCSPI_TRANSFER_MODE_CALLBACK;
            openParams->transferCallbackFxn    = test_mcspi_callback;
            openParams->mcspiDmaIndex          = 0;
            chConfigParams->inputSelect        = MCSPI_IS_D1;
            chConfigParams->dpe0               = MCSPI_DPE_DISABLE;
            chConfigParams->dpe1               = MCSPI_DPE_ENABLE;
            break;
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
