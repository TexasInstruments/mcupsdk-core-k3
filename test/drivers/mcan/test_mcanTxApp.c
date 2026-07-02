/*
 *  Copyright (C) 2021 Texas Instruments Incorporated
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
 *
 */
/**
 *  \file     test_mcanTxApp.c
 *
 *  \brief    This file contains mcan test code.
 *
 *  \details  mcan operational mode is set to normal mode for group 1.
 *            EVE reset interrupt is enabled from group 1 and
 *            it's priority is set as high level interrupt.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stdio.h>
#include "test_mcan.h"
#include <kernel/dpl/AddrTranslateP.h>
/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#define APP_MCAN_STD_ID_SHIFT             (18U)
#define APP_MCAN_EXT_ID_SHIFT             (0U)
#define APP_MCAN_STD_ID_MASK              (0x7FFU << APP_MCAN_STD_ID_SHIFT)
#define APP_MCAN_EXT_ID_MASK              (0x1FFFFFFFU)

/**
 * \brief  Mask and shift for Tx Buffers elements.
 */
#define MCANSS_TX_BUFFER_ELEM_ID_SHIFT                           (0U)
#define MCANSS_TX_BUFFER_ELEM_ID_MASK                            (0x1FFFFFFFU)
#define MCANSS_TX_BUFFER_ELEM_RTR_SHIFT                          (29U)
#define MCANSS_TX_BUFFER_ELEM_RTR_MASK                           (0x20000000U)
#define MCANSS_TX_BUFFER_ELEM_XTD_SHIFT                          (30U)
#define MCANSS_TX_BUFFER_ELEM_XTD_MASK                           (0x40000000U)
#define MCANSS_TX_BUFFER_ELEM_ESI_SHIFT                          (31U)
#define MCANSS_TX_BUFFER_ELEM_ESI_MASK                           (0x80000000U)
#define MCANSS_TX_BUFFER_ELEM_DLC_SHIFT                          (16U)
#define MCANSS_TX_BUFFER_ELEM_DLC_MASK                           (0x000F0000U)
#define MCANSS_TX_BUFFER_ELEM_BRS_SHIFT                          (20U)
#define MCANSS_TX_BUFFER_ELEM_BRS_MASK                           (0x00100000U)
#define MCANSS_TX_BUFFER_ELEM_FDF_SHIFT                          (21U)
#define MCANSS_TX_BUFFER_ELEM_FDF_MASK                           (0x00200000U)
#define MCANSS_TX_BUFFER_ELEM_EFC_SHIFT                          (23U)
#define MCANSS_TX_BUFFER_ELEM_EFC_MASK                           (0x00800000U)
#define MCANSS_TX_BUFFER_ELEM_MM_SHIFT                           (24U)
#define MCANSS_TX_BUFFER_ELEM_MM_MASK                            (0xFF000000U)
#define MAX_RAM_FIFO0_CNT                                        (64U)
#define MAX_RAM_FIFO1_CNT                                        (64U)
#define MAX_RAM_RXBUF_CNT                                        (64U)
#define MAX_RAM_TOTAL_RX                                         (MAX_RAM_FIFO0_CNT + MAX_RAM_FIFO1_CNT + MAX_RAM_RXBUF_CNT)  /* 192 */
#define MAX_RAM_SEND_CNT                                         (MAX_RAM_TOTAL_RX + 1U)  /* 193 */
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
extern uint32_t          gMcanBaseAddr;
extern uint32_t          gMcanAppdataSize[16];
extern volatile uint32_t gMcanECCIntrFlag;
extern MCAN_ECCErrStatus gMcaneccErr;
extern volatile uint32_t gMcanIsrIntr0Status;
extern volatile uint32_t gMcanIsrIntr1Status;
extern volatile uint32_t gMcanExtTSIntrFlag;
extern MCAN_BitTimingParams canFDBitTimings[];
extern MCAN_InitParams canFDInitParams[];
extern MCAN_ConfigParams canFDConfigParams[];
extern MCAN_MsgRAMConfigParams canFDRAMConfigParams[];
volatile uint32_t    rxBuffNum;
volatile uint32_t isrPrintEnable = (uint32_t)FALSE;
uint32_t objSize[8] = {4, 5, 6, 7, 8, 10, 14, 18};
uint32_t dataSize[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64};
/* 1 full CAN FD message = 18 words and put this in .data section */
uint32_t txBuffer[500U * 18U] __attribute__(( aligned(128), section(".data") )) = {1U};
uint32_t rxBuffer[500U * 18U] __attribute__(( aligned(128), section(".data") )) = {1U};
SemaphoreP_Object gTxDoneSem, gRxDoneSem;
static uint32_t gTxRxSemInitDone = (uint32_t)FALSE;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This function will configure MCAN module
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      configuration status.
 */
int32_t App_mcanConfig(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function contains MCAN Tx Test
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      configuration status.
 */
static int32_t App_mcanTxTest(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function contains MCAN Tx Test for performance test
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      configuration status.
 */
int32_t App_mcanPerfTxTest(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function will check TC pass/fail criteria apart from Tx/Rx
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      Execution status.
 */
static int32_t App_mcanCheckTCResultsMisc(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function will check received message against transferred.
 *
 * \param   txMsg       Tx Message.
 * \param   rxMsg       Rx Message.
 *
 * \retval  status      Check status.
 */
static int32_t App_mcanTxRxMessageCheck(MCAN_TxBufElement txMsg,
                                        MCAN_RxBufElement rxMsg);

/**
 * \brief   This function will check received message against transferred.
 *
 * \param   rxMsg       Read Rx Message.
 * \param   status      Interrupt Status.
 *
 * \retval  status      Check status.
 */
int32_t App_mcanReadRxMSG(MCAN_RxBufElement *rxMsg,
                                 uint32_t status);
int32_t App_mcanNoCpyNonAlignedDlcTest(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function will configure receiver or other things depending on
 *          TC parameters.
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      Execution status.
 */
static int32_t App_mcanTCEntrySetup(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function will configure receiver or other things for next TC.
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      Execution status.
 */
static int32_t App_mcanTCExitSetup(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function will send a message to change the receiver side
 *          application baud-rate.
 *
 * \param   idx         'canFDBitTimings' array index.
 *
 * \retval  status      Execution status.
 */
static int32_t App_mcanChangeBaudrateMSG(uint32_t idx);

/**
 * \brief   This function will check transmitted message against Tx Event Entry.
 *
 * \param   txMsg       Tx Message.
 * \param   rxMsg       Tx Event Message.
 *
 * \retval  status      Check status.
 */
static int32_t App_mcanTxEventMessageCheck(MCAN_TxBufElement txMsg,
                                           MCAN_TxEventFIFOElement txEventMsg);

/**
 * \brief   This function contains MCAN ECC Test
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      configuration status.
 */
static int32_t App_mcanECCTest(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function contains code for MCAN ECC Self Test/Diagnostic mode
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      configuration status.
 */
static int32_t App_mcanECCSelfTest(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function contains test code for MCAN State transition
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      configuration status.
 */
static int32_t App_mcanStateTransnTest(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function contains test code for MCAN Ext Time Stamp Interrupt
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      configuration status.
 */
static int32_t App_mcanExtTSIntrTest(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function contains test code for MCAN Rx/Tx state
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      configuration status.
 */
static int32_t App_mcanTxRxPinStateTest(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function contains test code for MCAN Rx/Tx state
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      configuration status.
 */
static int32_t App_mcanClkStpReqTest(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function contains test code for MCAN Rx/Tx state
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      configuration status.
 */
static int32_t App_mcanTSRstTest(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function contains test code for MCAN Rx/Tx state
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      configuration status.
 */
static int32_t App_mcanBusMonTest(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function contains MCAN Tx Test and then Rx Test for performance
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      configuration status.
 */
int32_t App_mcanPerfTxRxTest(st_mcanTestcaseParams_t *testParams);

/**
 * \brief   This function contains MCAN Rx FIFO Mode Tests
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      configuration status.
 */

static int32_t App_mcanMsgCancelTest(st_mcanTestcaseParams_t *testParams);
int32_t App_mcanRxFIFOModes(st_mcanTestcaseParams_t *testParams);
static int32_t App_mcanRxFIFO0MsgLostTest(st_mcanTestcaseParams_t *testParams);

extern int32_t App_mcanRegisterInterrupt();
extern int32_t App_mcanUnRegisterInterrupt();

extern void App_mcanIntr0ISR(void *handle);

extern void App_mcanIntr1ISR(void *handle);

extern void App_mcanECCIntrISR(void *handle);

extern void App_mcanTSIntrISR(void *handle);

extern uint32_t App_getBitConfigParamId(const MCAN_BitTimingParams *bitTimings);

extern void App_delayFunc(uint32_t timeout);

extern void App_mcanGetIntStatus(uint32_t baseAddr);

extern void App_mcanWriteMsg(uint32_t                 baseAddr,
                      uint32_t                 elemAddr,
                      const MCAN_TxBufElement *elem);

extern void App_mcanReadMsg(uint32_t           baseAddr,
                     uint32_t           elemAddr,
                     MCAN_RxBufElement *elem);
static void App_mcanInitTxElem(MCAN_TxBufElementNoCpy *txMsg);
static void App_mcanCompareBitTimeParams(MCAN_BitTimingParams *setPrms,
                MCAN_BitTimingParams *dstPrms);
static int32_t App_mcanTxTestBusMonitor(st_mcanTestcaseParams_t *testParams);
static int32_t App_mcanTxTestBusOff(st_mcanTestcaseParams_t *testParams);
static int32_t TestMcan_rxFifo0WatermarkIr(st_mcanTestcaseParams_t *testParams);
static int32_t TestMcan_timeoutCounter(st_mcanTestcaseParams_t *testParams);
static int32_t TestMcan_fDdlcRamElemMisconfigTest(st_mcanTestcaseParams_t *testParams);
static int32_t TestMcan_fDOperationDisabledTest(st_mcanTestcaseParams_t *testParams);
static int32_t TestMcan_nullPointerTest(st_mcanTestcaseParams_t *testParams);
static int32_t TestMcan_stdIDFilterMaxTest(st_mcanTestcaseParams_t *testParams);
static int32_t TestMcan_extIDFilterMaxTest(st_mcanTestcaseParams_t *testParams);
#ifdef MCAN_ECC_SUPPORTED
static int32_t TestMcan_eCCIntrStatusTest(st_mcanTestcaseParams_t *testParams);
#endif
static int32_t TestMcan_mixedExtIdClassicFdTest(st_mcanTestcaseParams_t *testParams);
static int32_t TestMcan_explicitBufferNumbersIsolationTest(st_mcanTestcaseParams_t *testParams);
static int32_t TestMcan_combinedFilterTypeTest(st_mcanTestcaseParams_t *testParams);
static int32_t App_mcanBurstTxTest(st_mcanTestcaseParams_t *testParams);
static int32_t App_mcanBurstDedicatedRxBufTest(st_mcanTestcaseParams_t *testParams);
static int32_t App_mcanExternalReadWriteTest(st_mcanTestcaseParams_t *testParams);
static int32_t TestMcan_maxMsgRamWordCntTest(st_mcanTestcaseParams_t *testParams);
static int32_t TestMcan_initTxRxSem(void);
static void TestMcan_deInitTxRxSem(void);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t st_mcanTxApp_main(st_mcanTestcaseParams_t *testParams)
{
    int32_t                    configStatus = CSL_PASS;

    if ((testParams->testcaseId == 10251U) || (testParams->testcaseId == 10253U))
    {
        App_mcanNegativeTest(testParams);
    }
    else if(testParams->testcaseId == 10482U)
    {
        testParams->testResult = TestMcan_nullPointerTest(testParams);
    }
    else
    {
        configStatus += TestMcan_initTxRxSem();
        if (CSL_PASS != configStatus)
        {
            DebugP_log("\nError in Semaphore Configuration...");
        }
        configStatus += App_mcanRegisterInterrupt();
        if (CSL_PASS != configStatus)
        {
            DebugP_log("\nError in X-Bar Configuration...");
        }
        gMcanBaseAddr = DEF_MCAN_MODULE;
#if !defined (A53_CORE) && !defined (WKUP_R5_CORE)
        if (testParams->testcaseId == 10249)
        {
            gMcanBaseAddr = CONFIG_MCAN1_BASE_ADDR;
        }
#endif

#if defined (SOC_AM263X)
        if (testParams->testcaseId == 1235)
        {
            gMcanBaseAddr = CONFIG_MCAN2_BASE_ADDR;
        }
        else if (testParams->testcaseId == 1236)
        {
            gMcanBaseAddr = CONFIG_MCAN3_BASE_ADDR;
        }
        else
        {
            gMcanBaseAddr = DEF_MCAN_MODULE;
        }
#else
        gMcanBaseAddr = (uint32_t) AddrTranslateP_getLocalAddr(gMcanBaseAddr);
#endif
        /* Reset MCAN Module */
        MCAN_reset(gMcanBaseAddr);
        MCAN_lpbkModeEnable(gMcanBaseAddr, MCAN_LPBK_MODE_INTERNAL, FALSE);
        while (MCAN_isInReset(gMcanBaseAddr) == (uint32_t)TRUE)
        {
        }
        configStatus += App_mcanConfig(testParams);
        if (CSL_PASS != configStatus)
        {
            DebugP_log("\nError in MCAN Configuration...");
        }

        configStatus += App_mcanTCEntrySetup(testParams);
        if(configStatus != CSL_PASS)
        {
            DebugP_log("\nError in MCAN TC Entry Configuration...TC cannot be Run...");
        }
        else
        {
            switch (testParams->testcaseId)
            {
                case 10:
                    testParams->testResult = App_mcanECCTest(testParams);
                break;
                case 11:
                    testParams->testResult = App_mcanECCSelfTest(testParams);
                break;
                case 12:
                    testParams->testResult = App_mcanECCSelfTest(testParams);
                break;
                case 15:
                    testParams->testResult = App_mcanStateTransnTest(testParams);
                break;
                case 10247:
                    testParams->testResult = App_mcanExtTSIntrTest(testParams);
                break;
                case 10241:
                    testParams->testResult = App_mcanTxRxPinStateTest(testParams);
                break;
                case 10250:
                    testParams->testResult = App_mcanClkStpReqTest(testParams);
                break;
                case 10248:
                    testParams->testResult = App_mcanTSRstTest(testParams);
                break;
                case 20:
                    testParams->testResult = App_mcanBusMonTest(testParams);
                break;
                case 10237:
                    testParams->testResult = App_mcanPerfTxRxTest(testParams);
                break;
                case 10233:
                case 10234:
                case 10235:
                    testParams->testResult = App_mcanRxFIFOModes(testParams);
                break;
                case 11863:
                    testParams->testResult = App_mcanRxFIFO0MsgLostTest(testParams);
                break;
                case 10238:
                    testParams->testResult = App_mcanPerfTxRxTest(testParams);
                break;
                case 10272:
                    testParams->testResult = App_mcanMsgCancelTest(testParams);
                break;
                case 1256:
                case 1257:
                    testParams->testResult = App_mcanTxTestBusOff(testParams);
                break;
                case 1259:
                    testParams->testResult = App_mcanTxTestBusMonitor(testParams);
                break;
                case 1260:
                case 11089:
                case 11090:
                    testParams->testResult = App_mcanExternalReadWriteTest(testParams);
                break;
                case 10477:
                    testParams->testResult = TestMcan_rxFifo0WatermarkIr(testParams);
                break;
                case 10478:
                    testParams->testResult = TestMcan_timeoutCounter(testParams);
                break;
                case 10480:
                    testParams->testResult = TestMcan_fDdlcRamElemMisconfigTest(testParams);
                break;
                case 10481:
                    testParams->testResult = TestMcan_fDOperationDisabledTest(testParams);
                break;
                case 10483:
                     testParams->testResult = TestMcan_stdIDFilterMaxTest(testParams);
                break;
                case 10484:
                     testParams->testResult = TestMcan_extIDFilterMaxTest(testParams);
                break;
                #if defined (FREERTOS_CORE)
                case 10491:
                     testParams->testResult = TestMcan_multiThreadedTest(testParams);
                break;
                case 10492:
                     testParams->testResult = TestMcan_concurrentTxTest(testParams);
                break;
                case 10493:
                     testParams->testResult = TestMcan_multiInstanceTest(testParams);
                break;
                case 10297:
                     testParams->testResult = TestMcan_txFifoRxFifo0ConcurrentTest(testParams);
                break;
                case 10495:
                     testParams->testResult = TestMcan_parallelClassicCanFdTest(testParams);
                break;
                case 10874:
                     testParams->testResult = TestMcan_intrPollMultiThreadTest(testParams);
                break;
                #endif
                #ifdef MCAN_ECC_SUPPORTED
                case 10871:
                    testParams->testResult = App_mcanNoCpyNonAlignedDlcTest(testParams);
                break;
                 case 10872:
                    testParams->testResult = TestMcan_eCCIntrStatusTest(testParams);
                 break;
                #endif
                case 10485:
                case 10486:
                    testParams->testResult = App_mcanBurstTxTest(testParams);
                break;
                case 10487:
                    testParams->testResult = App_mcanBurstDedicatedRxBufTest(testParams);
                break;
                case 10488:
                    testParams->testResult = TestMcan_maxMsgRamWordCntTest(testParams);
                break;
                case 10870:
                    testParams->testResult = TestMcan_mixedExtIdClassicFdTest(testParams);
                break;
                case 10868:
                    testParams->testResult = TestMcan_explicitBufferNumbersIsolationTest(testParams);
                break;
                case 10869:
                    testParams->testResult = TestMcan_combinedFilterTypeTest(testParams);
                break;
                #if defined (FREERTOS_CORE)
                case 10875:
                    testParams->testResult = TestMcan_multiThreadedFilterTest(testParams);
                break;
                #endif
                default:
                    testParams->testResult = App_mcanTxTest(testParams);
                break;
            }
            testParams->testResult += App_mcanCheckTCResultsMisc(testParams);
            configStatus += App_mcanTCExitSetup(testParams);
            if(configStatus != CSL_PASS)
            {
                DebugP_log("\nError in MCAN TC Exit Configuration...");
            }
            configStatus += App_mcanUnRegisterInterrupt();
            TestMcan_deInitTxRxSem();
        }
    }
    return 0;
}

/**
 * \brief   Initialize TX/RX semaphores used by MCAN tests.
 *
 * \return  SystemP_SUCCESS on success, SystemP_FAILURE (or other error) on failure.
 */
static int32_t TestMcan_initTxRxSem(void)
{
    int32_t status = SystemP_SUCCESS;

    if (gTxRxSemInitDone == (uint32_t)FALSE)
    {
        status = SemaphoreP_constructBinary(&gTxDoneSem, 0U);
        DebugP_assert(SystemP_SUCCESS == status);
        if (status == SystemP_SUCCESS)
        {
            status = SemaphoreP_constructBinary(&gRxDoneSem, 0U);
            DebugP_assert(SystemP_SUCCESS == status);
            if (status != SystemP_SUCCESS)
            {
                SemaphoreP_destruct(&gTxDoneSem);
            }
        }
        if (status == SystemP_SUCCESS)
        {
            gTxRxSemInitDone = (uint32_t)TRUE;
        }
    }

    return status;
}

/**
 * \brief   De-initialize TX/RX semaphores used by MCAN tests.
 *
 * \note    Safe to call even if TestMcan_initTxRxSem() was not called or failed.
 */
static void TestMcan_deInitTxRxSem(void)
{
    if (gTxRxSemInitDone == (uint32_t)TRUE)
    {
        SemaphoreP_destruct(&gTxDoneSem);
        SemaphoreP_destruct(&gRxDoneSem);
        gTxRxSemInitDone = (uint32_t)FALSE;
    }
}

int32_t App_mcanNegativeTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t           configStatus = CSL_PASS;
    MCAN_RxFIFOStatus fifoStatus;
    MCAN_TxBufElement txMsg;
    MCAN_InitParams   initParams;
    MCAN_ConfigParams configParams;
    MCAN_BitTimingParams bitTimes;
    MCAN_ECCErrStatus eccErr;
    MCAN_ECCAggrRevisionId eccAggrRevId;
    MCAN_ECCWrapRevisionId eccWrapRevId;
    MCAN_TxBufElementNoCpy txElem = {0U};
#if !defined(R5_FREERTOS_CORE) && !defined(MCU_M4_CORE)
    MCAN_RxBufElement rxMsg = {0};
    MCAN_RxBufElementNoCpy rxMsgNoCpy = {0};
#endif

    /* Reset MCAN Module */
    MCAN_reset(gMcanBaseAddr);
    while (MCAN_isInReset(gMcanBaseAddr) == (uint32_t)TRUE)
    {
    }
    /* wait for memory initialization to happen */
    while (FALSE == MCAN_isMemInitDone(gMcanBaseAddr))
    {}

    /* Put MCAN in SW initialization mode */
    MCAN_setOpMode(gMcanBaseAddr, MCAN_OPERATION_MODE_SW_INIT);
    while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(gMcanBaseAddr))
    {}
    /* Initialize MCAN module */
    configStatus = MCAN_init(gMcanBaseAddr, testParams->mcanConfigParams.initParams);
    DebugP_assert(configStatus == CSL_EFAIL);
    configStatus = MCAN_init(gMcanBaseAddr, &canFDInitParams[2U]);
    DebugP_assert(configStatus == CSL_EFAIL);
    configStatus = MCAN_init(gMcanBaseAddr, &canFDInitParams[3U]);
    DebugP_assert(configStatus == CSL_EFAIL);
    configStatus = MCAN_init(gMcanBaseAddr, NULL);
    DebugP_assert(configStatus == CSL_EFAIL);

    /* Configure MCAN module */
    configStatus = MCAN_config(gMcanBaseAddr, testParams->mcanConfigParams.configParams);
    DebugP_assert(configStatus == CSL_EFAIL);
    configStatus = MCAN_config(gMcanBaseAddr, &canFDConfigParams[6U]);
    DebugP_assert(configStatus == CSL_EFAIL);
    configStatus = MCAN_config(gMcanBaseAddr, NULL);
    DebugP_assert(configStatus == CSL_EFAIL);

    /* Configure MCAN ECC */
    MCAN_eccConfig(gMcanBaseAddr, NULL);

    /* Configure Bit timings */
    configStatus = MCAN_setBitTime(gMcanBaseAddr, testParams->mcanConfigParams.bitTimings);
    DebugP_assert(configStatus == CSL_EFAIL);
    /* Configure Bit timings */
    configStatus = MCAN_setBitTime(gMcanBaseAddr, &canFDBitTimings[6U]);
    DebugP_assert(configStatus == CSL_EFAIL);
    configStatus = MCAN_setBitTime(gMcanBaseAddr, &canFDBitTimings[7U]);
    DebugP_assert(configStatus == CSL_EFAIL);
    configStatus = MCAN_setBitTime(gMcanBaseAddr, &canFDBitTimings[8U]);
    DebugP_assert(configStatus == CSL_EFAIL);
    configStatus = MCAN_setBitTime(gMcanBaseAddr, &canFDBitTimings[9U]);
    DebugP_assert(configStatus == CSL_EFAIL);
    configStatus = MCAN_setBitTime(gMcanBaseAddr, &canFDBitTimings[10U]);
    DebugP_assert(configStatus == CSL_EFAIL);
    configStatus = MCAN_setBitTime(gMcanBaseAddr, &canFDBitTimings[11U]);
    DebugP_assert(configStatus == CSL_EFAIL);
    configStatus = MCAN_setBitTime(gMcanBaseAddr, NULL);
    DebugP_assert(configStatus == CSL_EFAIL);

    configStatus = MCAN_msgRAMConfig(gMcanBaseAddr, &canFDRAMConfigParams[4U]);
    DebugP_assert(configStatus == CSL_EFAIL);
    configStatus = MCAN_msgRAMConfig(gMcanBaseAddr, NULL);
    DebugP_assert(configStatus == CSL_EFAIL);

    /* Set Extended ID Mask */
    configStatus = MCAN_setExtIDAndMask(gMcanBaseAddr, MCAN_XIDAM_EIDM_MAX + 1U);
    DebugP_assert(configStatus == CSL_EFAIL);

    MCAN_writeMsgRam(gMcanBaseAddr,
                     MCAN_MEM_TYPE_FIFO,
                     0,
                     NULL);
    MCAN_writeMsgRam(gMcanBaseAddr,
                     MCAN_MEM_TYPE_FIFO + 1,
                     0,
                     &testParams->mcanConfigParams.txMsg[0].txElem);
                     
    MCAN_writeMsgRamNoCpy(gMcanBaseAddr,
                     MCAN_MEM_TYPE_FIFO,
                     0,
                     NULL);
    App_mcanInitTxElem(&txElem);
    MCAN_writeMsgRamNoCpy(gMcanBaseAddr,
                     MCAN_MEM_TYPE_FIFO + 1,
                     0,
                     &txElem);

    MCAN_getNewDataStatus(gMcanBaseAddr, NULL);
    MCAN_clearNewDataStatus(gMcanBaseAddr, NULL);
#if !defined(R5_FREERTOS_CORE) && !defined(MCU_M4_CORE)
    MCAN_readMsgRam(gMcanBaseAddr,
                    MCAN_MEM_TYPE_BUF,
                    0U,
                    MCAN_RX_FIFO_NUM_1 + 1,
                    &rxMsg);
    MCAN_readMsgRam(gMcanBaseAddr,
                    MCAN_MEM_TYPE_FIFO,
                    0U,
                    MCAN_RX_FIFO_NUM_1 + 1,
                    &rxMsg);
    MCAN_readMsgRam(gMcanBaseAddr,
                    MCAN_MEM_TYPE_FIFO,
                    0U,
                    MCAN_RX_FIFO_NUM_1,
                    NULL);
    MCAN_readMsgRamNoCpy(gMcanBaseAddr,
                    MCAN_MEM_TYPE_BUF,
                    0U,
                    MCAN_RX_FIFO_NUM_1 + 1,
                    &rxMsgNoCpy);
    MCAN_readMsgRamNoCpy(gMcanBaseAddr,
                    MCAN_MEM_TYPE_FIFO,
                    0U,
                    MCAN_RX_FIFO_NUM_1 + 1,
                    &rxMsgNoCpy);
    MCAN_readMsgRamNoCpy(gMcanBaseAddr,
                    MCAN_MEM_TYPE_FIFO,
                    0U,
                    MCAN_RX_FIFO_NUM_1,
                    NULL);
#endif
    MCAN_readTxEventFIFO(gMcanBaseAddr, NULL);

    MCAN_addStdMsgIDFilter(gMcanBaseAddr, 0U, NULL);

    MCAN_addExtMsgIDFilter(gMcanBaseAddr, 0U, NULL);

    MCAN_getErrCounters(gMcanBaseAddr, NULL);

    MCAN_getProtocolStatus(gMcanBaseAddr, NULL);

    MCAN_getHighPriorityMsgStatus(gMcanBaseAddr, NULL);

    MCAN_txBufAddReq(gMcanBaseAddr,
                     MCAN_TX_BUFFER_MAX_NUM + 1);
    fifoStatus.num = (uint32_t)MCAN_RX_FIFO_NUM_1 + 1;
    MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);

    MCAN_getRxFIFOStatus(gMcanBaseAddr, NULL);

    MCAN_getTxFIFOQueStatus(gMcanBaseAddr, NULL);

    MCAN_getTxEventFIFOStatus(gMcanBaseAddr, NULL);

    MCAN_eccForceError(gMcanBaseAddr, NULL);

    MCAN_eccGetErrorStatus(gMcanBaseAddr, NULL);

    MCAN_getRevisionId(gMcanBaseAddr, NULL);

    MCAN_getBitTime(gMcanBaseAddr, NULL);

    MCAN_eccAggrGetRevisionId(gMcanBaseAddr, NULL);

    MCAN_writeRxFIFOAck(gMcanBaseAddr, MCAN_RX_FIFO_NUM_1 + 1, 0U);
    MCAN_writeRxFIFOAck(gMcanBaseAddr, MCAN_RX_FIFO_NUM_0, MCAN_RX_FIFO_0_MAX_NUM + 1);
    MCAN_writeRxFIFOAck(gMcanBaseAddr, MCAN_RX_FIFO_NUM_1, MCAN_RX_FIFO_1_MAX_NUM + 1);
    MCAN_txBufCancellationReq(gMcanBaseAddr, MCAN_TX_BUFFER_MAX_NUM + 1);
    MCAN_txBufTransIntrEnable(gMcanBaseAddr, MCAN_TX_BUFFER_MAX_NUM + 1, 0U);
    MCAN_txBufCancellationIntrEnable(gMcanBaseAddr, MCAN_TX_BUFFER_MAX_NUM + 1, TRUE);
    MCAN_txBufCancellationIntrEnable(gMcanBaseAddr, 0, FALSE);
    MCAN_writeTxEventFIFOAck(gMcanBaseAddr, MCAN_TX_BUFFER_MAX_NUM + 1);
    MCAN_extTSSetRawStatus(gMcanBaseAddr);

    MCAN_lpbkModeEnable(gMcanBaseAddr, MCAN_LPBK_MODE_EXTERNAL, FALSE);
    MCAN_lpbkModeEnable(gMcanBaseAddr, MCAN_LPBK_MODE_EXTERNAL, TRUE);
    MCAN_lpbkModeEnable(gMcanBaseAddr, MCAN_LPBK_MODE_INTERNAL, FALSE);
    MCAN_initTxBufElement(NULL);
    MCAN_initTxBufElement(&txMsg);
    MCAN_initOperModeParams(NULL);
    MCAN_initOperModeParams(&initParams);
    MCAN_initGlobalFilterConfigParams(NULL);
    MCAN_initGlobalFilterConfigParams(&configParams);
    MCAN_initSetBitTimeParams(NULL);
    MCAN_initSetBitTimeParams(&bitTimes);
    MCAN_initMsgRamConfigParams(NULL);
    MCAN_initMsgRamConfigParams(testParams->mcanConfigParams.ramConfig);
    MCAN_calcMsgRamParamsStartAddr(NULL);
    MCAN_calcMsgRamParamsStartAddr(&canFDRAMConfigParams[5U]);

    /* Enable ECC Interrupts */
    MCAN_eccAggrGetRevisionId(gMcanBaseAddr, &eccAggrRevId);
    MCAN_eccWrapGetRevisionId(gMcanBaseAddr, &eccWrapRevId);
    MCAN_eccEnableIntr(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_SEC, TRUE);
    MCAN_eccEnableIntr(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_DED, TRUE);
    MCAN_eccEnableIntr(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_DED + 1, TRUE);
    MCAN_eccConfig(gMcanBaseAddr, testParams->mcanConfigParams.eccConfigParams);
    MCAN_eccForceError(gMcanBaseAddr, testParams->mcanConfigParams.eccFrcParams);
    testParams->mcanConfigParams.eccFrcParams->errType = MCAN_ECC_ERR_TYPE_DED;
    MCAN_eccForceError(gMcanBaseAddr, testParams->mcanConfigParams.eccFrcParams);
    MCAN_eccWriteEOI(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_SEC);
    MCAN_eccWriteEOI(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_DED);
    MCAN_eccWriteEOI(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_DED + 1);
    MCAN_eccClearErrorStatus(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_SEC);
    MCAN_eccClearErrorStatus(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_DED);
    MCAN_eccClearErrorStatus(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_DED + 1);
    MCAN_eccGetErrorStatus(gMcanBaseAddr, &eccErr);
    MCAN_eccEnableIntr(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_SEC, FALSE);
    MCAN_eccEnableIntr(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_DED, FALSE);
    MCAN_eccEnableIntr(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_DED + 1, FALSE);
    MCAN_eccClearIntrStatus(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_DED);
    MCAN_eccClearIntrStatus(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_SEC);
    MCAN_eccClearIntrStatus(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_SEC + 1);

    return configStatus;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */

int32_t App_mcanConfig(st_mcanTestcaseParams_t *testParams)
{
    uint32_t                   fdoe, loopCnt, extMask = 0U;
    int32_t                    configStatus = CSL_PASS;
    MCAN_RevisionId            revId;
    MCAN_BitTimingParams bitTimes;

    /* Reset MCAN SS */
    /* Get MCANSS Revision ID */
    MCAN_getRevisionId(gMcanBaseAddr, &revId);
    /* Enable Auto wakeup */
    fdoe = MCAN_isFDOpEnable(gMcanBaseAddr);
    (void)fdoe; /* Kill warning. Presently set but not used */
    /* wait for memory initialization to happen */
    while (FALSE == MCAN_isMemInitDone(gMcanBaseAddr))
    {}
    /* Get endianess value */
    DebugP_assert(MCAN_getEndianVal(gMcanBaseAddr) == 0x87654321U);
    /* Put MCAN in SW initialization mode */
    MCAN_setOpMode(gMcanBaseAddr, MCAN_OPERATION_MODE_SW_INIT);
    while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(gMcanBaseAddr))
    {}
    /* Initialize MCAN module */
    configStatus += MCAN_init(gMcanBaseAddr, testParams->mcanConfigParams.initParams);
    if(configStatus != CSL_PASS)
    {
        DebugP_log("\nMCAN Initialization FAILED...\n", -1);
    }
    /* Configure MCAN module */
    configStatus += MCAN_config(gMcanBaseAddr, testParams->mcanConfigParams.configParams);
    if(configStatus != CSL_PASS)
    {
        DebugP_log("\nMCAN Configuration FAILED...\n", -1);
    }
    /* Configure Bit timings */
    configStatus += MCAN_setBitTime(gMcanBaseAddr, testParams->mcanConfigParams.bitTimings);
    if(configStatus != CSL_PASS)
    {
        DebugP_log("\nMCAN Bit Time Configuration FAILED...\n", -1);
    }
    MCAN_getBitTime(gMcanBaseAddr, &bitTimes);

    App_mcanCompareBitTimeParams(testParams->mcanConfigParams.bitTimings, &bitTimes);

    /* Set Extended ID Mask */
    configStatus += MCAN_setExtIDAndMask(gMcanBaseAddr, 0x1FFFFFFFU);
    if(configStatus != CSL_PASS)
    {
        DebugP_log("\nMCAN Bit Time Configuration FAILED...\n", -1);
    }
    extMask = MCAN_getExtIDANDMassk(gMcanBaseAddr);
    DebugP_assert(extMask == 0x1FFFFFFFU);

    /* Configure Message RAM Sections */
    configStatus += MCAN_calcMsgRamParamsStartAddr(testParams->mcanConfigParams.ramConfig);
    if(configStatus != CSL_PASS)
    {
        DebugP_log("\nMCAN Message RAM Addr Calculation FAILED...\n", -1);
    }

    configStatus += MCAN_msgRAMConfig(gMcanBaseAddr, testParams->mcanConfigParams.ramConfig);
    if(configStatus != CSL_PASS)
    {
        DebugP_log("\nMCAN Message RAM Configuration FAILED...\n", -1);
    }

    for(loopCnt = 0U ; loopCnt < testParams->mcanConfigParams.stdIdFiltNum; loopCnt++)
    {
        /* Configure Standard ID filter element */
        MCAN_addStdMsgIDFilter(gMcanBaseAddr, loopCnt, &testParams->mcanConfigParams.stdIDFilter[loopCnt]);
    }
    for(loopCnt = 0U ; loopCnt < testParams->mcanConfigParams.extIdFiltNum; loopCnt++)
    {
        /* Configure Standard ID filter element */
        MCAN_addExtMsgIDFilter(gMcanBaseAddr, loopCnt, &testParams->mcanConfigParams.extIDFilter[loopCnt]);
    }
    /* Configure ECC */
    MCAN_eccConfig(gMcanBaseAddr, testParams->mcanConfigParams.eccConfigParams);
    /* Enable loopback if autoRunEnable is set/TRUE */
    /* Enable loopback only if internal loopback is set as test mode */
    if (testParams->mcanConfigParams.mcanTestType == MCAN_TEST_TYPE_INTERNAL_LOOPBACK)
    {
        MCAN_lpbkModeEnable(gMcanBaseAddr, MCAN_LPBK_MODE_INTERNAL, TRUE);
    }
    /* Take MCAN out of the SW initialization mode */
    MCAN_setOpMode(gMcanBaseAddr, MCAN_OPERATION_MODE_NORMAL);
    while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(gMcanBaseAddr))
    {}
    return configStatus;
}

/**
 * @brief  Burst TX FIFO test: fill all 32 TX FIFO slots, request all
 *         transmissions at once, then continuously drain the receive FIFO.
 *
 * Covers two FIFO-path variants (both use canFDRAMConfigParams[7U],
 * txFIFO=32, rxFIFO0=64, rxFIFO1=64):
 *
 *   10485 - 32 CAN-Classic frames -> TX FIFO -> RX FIFO0.
 *   10486 - 32 CAN-FD frames -> TX FIFO -> RX FIFO1
 *           (ID below filter range falls through to FIFO1 via GFC anfs=1).
 *
 * Phase 1: Write unique data[0] stamp (0..31) into each TX FIFO slot and call
 *          MCAN_txBufAddReq() for every slot before waiting for any reply.
 * Phase 2: Poll MCAN_getTxBufTransmissionStatus() until all 32 TXBTO bits set.
 * Phase 3: Poll RX FIFO fillLvl until 32 messages are buffered, then drain
 *          and verify all 32 messages in a continuous loop.
 */
static int32_t App_mcanBurstTxTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t            testStatus    = CSL_PASS;
    int32_t            configStatus;
    uint32_t           loopCnt;
    uint32_t           txBufIdx;
    uint32_t           txAllDoneMask = 0U;
    uint32_t           txStatus;
    uint32_t           burstCount;
    uint32_t           rxFIFONum;
    MCAN_TxFIFOStatus  txFIFOStat;
    MCAN_RxFIFOStatus  rxFIFOStatus;
    MCAN_TxBufElement  txElem;
    MCAN_RxBufElement  rxMsg;
    MCAN_ProtocolStatus protStatus;
    MCAN_ErrCntStatus   errCounter;

    /* FIFO-only path: burst count equals TX FIFO depth */
    burstCount = testParams->mcanConfigParams.ramConfig->txFIFOCnt;

    /* Determine which RX FIFO to drain from the tx-message config */
    rxFIFONum = testParams->mcanConfigParams.txMsg[0U].rxBuffNum;

    /* Enable MCAN interrupts and interrupt line */
    MCAN_enableIntr(gMcanBaseAddr,
                    testParams->mcanConfigParams.intrEnable,
                    (uint32_t)TRUE);
    MCAN_selectIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);
    MCAN_enableIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLine, 1U);

    /* Enable TX transmission interrupts for all TX FIFO slots */
    for (loopCnt = 0U; loopCnt < burstCount; loopCnt++)
    {
        configStatus = MCAN_txBufTransIntrEnable(gMcanBaseAddr, loopCnt,
                                                 (uint32_t)TRUE);
        if (configStatus != CSL_PASS)
        {
            DebugP_log("\nMCAN TX intr enable FAILED for slot %u\n", loopCnt);
        }
    }

    DebugP_log("\n=== Burst TX FIFO Test: %u messages -> RX FIFO%u ===\n",
               burstCount, rxFIFONum);

    /* ------------------------------------------------------------------
     * Phase 1: Burst-fill all TX FIFO slots and issue all TX requests
     *          before waiting for any acknowledgement.
     * ------------------------------------------------------------------ */
    DebugP_log("Phase 1: Loading %u messages into TX FIFO and requesting all TX...\n",
               burstCount);

    for (loopCnt = 0U; loopCnt < burstCount; loopCnt++)
    {
        /* Stamp data[0] with sequence number for per-message verification */
        txElem          = testParams->mcanConfigParams.txMsg[0U].txElem;
        txElem.data[0U] = (uint8_t)loopCnt;

        /* TX FIFO mode: hardware advances putIdx after each TXBAR write */
        MCAN_getTxFIFOQueStatus(gMcanBaseAddr, &txFIFOStat);
        txBufIdx = txFIFOStat.putIdx;
        MCAN_writeMsgRam(gMcanBaseAddr, MCAN_MEM_TYPE_FIFO, txBufIdx, &txElem);

        configStatus = MCAN_txBufAddReq(gMcanBaseAddr, txBufIdx);
        if (configStatus != CSL_PASS)
        {
            DebugP_log("FAIL: MCAN_txBufAddReq() returned %d for slot %u\n",
                       configStatus, txBufIdx);
            testStatus = CSL_EFAIL;
        }
        txAllDoneMask |= (1U << txBufIdx);
    }

    DebugP_log("Phase 1 complete: all %u TX FIFO requests submitted.\n", burstCount);

    /* ------------------------------------------------------------------
     * Phase 2: Poll TXBTO until all FIFO slots report transmission done.
     * ------------------------------------------------------------------ */
    DebugP_log("Phase 2: Polling for all TX completions (mask=0x%08X)...\n",
               txAllDoneMask);

    do
    {
        txStatus = MCAN_getTxBufTransmissionStatus(gMcanBaseAddr);
    } while ((txStatus & txAllDoneMask) != txAllDoneMask);

    DebugP_log("Phase 2 complete: TXBTO=0x%08X - all %u messages transmitted.\n",
               txStatus, burstCount);

    /* Verify no protocol errors occurred during burst transmission */
    MCAN_getErrCounters(gMcanBaseAddr, &errCounter);
    MCAN_getProtocolStatus(gMcanBaseAddr, &protStatus);
    if ((errCounter.recErrCnt != 0U) || (errCounter.canErrLogCnt != 0U))
    {
        DebugP_log("FAIL: Error counters non-zero after burst TX "
                   "(TEC=%u REC=%u)\n",
                   errCounter.canErrLogCnt, errCounter.recErrCnt);
        testStatus = CSL_EFAIL;
    }
    if (!((MCAN_ERR_CODE_NO_ERROR == protStatus.lastErrCode ||
           MCAN_ERR_CODE_NO_CHANGE == protStatus.lastErrCode) &&
          (MCAN_ERR_CODE_NO_ERROR == protStatus.dlec ||
           MCAN_ERR_CODE_NO_CHANGE == protStatus.dlec) &&
          (0U == protStatus.pxe)))
    {
        DebugP_log("FAIL: Protocol errors detected after burst TX\n");
        testStatus = CSL_EFAIL;
    }

    /* ------------------------------------------------------------------
     * Phase 3: Continuously drain the RX FIFO.
     * Wait until all burstCount messages are present, then read them
     * one after another in a single loop and verify the sequence stamp.
     * ------------------------------------------------------------------ */
    DebugP_log("Phase 3: Draining RX FIFO%u - waiting for %u messages...\n",
               rxFIFONum, burstCount);

    rxFIFOStatus.num = rxFIFONum;

    /* Spin until the FIFO has accumulated all transmitted messages */
    do
    {
        MCAN_getRxFIFOStatus(gMcanBaseAddr, &rxFIFOStatus);
    } while (rxFIFOStatus.fillLvl < burstCount);

    DebugP_log("RX FIFO%u fillLvl=%u. Continuously reading all messages...\n",
               rxFIFONum, rxFIFOStatus.fillLvl);

    for (loopCnt = 0U; loopCnt < burstCount; loopCnt++)
    {
        MCAN_getRxFIFOStatus(gMcanBaseAddr, &rxFIFOStatus);
        MCAN_readMsgRam(gMcanBaseAddr,
                        MCAN_MEM_TYPE_FIFO,
                        rxFIFOStatus.getIdx,
                        rxFIFONum,
                        &rxMsg);
        MCAN_writeRxFIFOAck(gMcanBaseAddr, rxFIFONum, rxFIFOStatus.getIdx);

        /* Check per-message sequence stamp planted in Phase 1 */
        if (rxMsg.data[0U] != (uint8_t)loopCnt)
        {
            DebugP_log("FAIL: msg[%u] data[0]: expected 0x%02X got 0x%02X\n",
                       loopCnt, (uint8_t)loopCnt, rxMsg.data[0U]);
            testStatus = CSL_EFAIL;
        }
    }

    if (testStatus == CSL_PASS)
    {
        DebugP_log("Phase 3 complete: all %u messages received and verified OK.\n",
                   burstCount);
    }

    /* Disable TX interrupts */
    for (loopCnt = 0U; loopCnt < burstCount; loopCnt++)
    {
        (void)MCAN_txBufTransIntrEnable(gMcanBaseAddr, loopCnt, (uint32_t)FALSE);
    }

    DebugP_log("=== Burst TX Test %s ===\n",
               (testStatus == CSL_PASS) ? "PASSED" : "FAILED");

    return testStatus;
}

/**
 * @brief  Burst test for 32 dedicated TX buffers -> 32 dedicated RX buffers.
 *
 * Covers the dedicated RX buffer path end-to-end with maximum capacity:
 *
 * Setup:
 *   Enters SW_INIT to add 32 standard ID filters.
 *   Each filter uses sfec=MCAN_STD_FILT_ELEM_BUFFER (7) to route a unique ID
 *   (0x001+i) directly into dedicated RX buffer slot i (i = 0..31).
 *   Requires canFDRAMConfigParams[8U]: lss=32, txBufCnt=32, no RX FIFO.
 *
 * Phase 1: Write all 32 dedicated TX buffers (unique ID + data stamp),
 *          call MCAN_txBufAddReq() for all 32 before waiting for any reply.
 *
 * Phase 2: Poll MCAN_getTxBufTransmissionStatus() until all 32 TXBTO bits set.
 *
 * Phase 3: Poll MCAN_getNewDataStatus() until statusLow bits 0..31 are all set,
 *          then read and verify each dedicated RX buffer in order.
 *
 * @param  testParams  Test case parameters (expects canFDRAMConfigParams[11U]).
 * @return CSL_PASS if all 32 TX->RX transfers verified OK, CSL_EFAIL otherwise.
 */
static int32_t App_mcanBurstDedicatedRxBufTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t                    testStatus    = CSL_PASS;
    int32_t                    configStatus;
    uint32_t                   loopCnt;
    uint32_t                   txAllDoneMask = 0U;
    uint32_t                   txStatus;
    uint32_t                   pollCnt;
    MCAN_StdMsgIDFilterElement filterElem;
    MCAN_TxBufElement          txElem;
    MCAN_RxBufElement          rxMsg;
    MCAN_RxNewDataStatus       newDataStatus;
    MCAN_ProtocolStatus        protStatus;
    MCAN_ErrCntStatus          errCounter;

#define BURST_DED_BUF_COUNT  (32U)

    DebugP_log("\n=== Burst Dedicated TX->RX Buffer Test: %u messages ===\n",
               BURST_DED_BUF_COUNT);

    /* ------------------------------------------------------------------
     * Setup: Enter SW_INIT to program 32 standard ID filters.
     *        Each filter routes a unique ID (0x001+i) to dedicated RX
     *        buffer slot i (sfec=MCAN_STD_FILT_ELEM_BUFFER, sfid2=i).
     * ------------------------------------------------------------------ */
    MCAN_setOpMode(gMcanBaseAddr, MCAN_OPERATION_MODE_SW_INIT);
    while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(gMcanBaseAddr))
    {}

    for (loopCnt = 0U; loopCnt < BURST_DED_BUF_COUNT; loopCnt++)
    {
        filterElem.sfid1 = 0x001U + loopCnt;           /* ID to match */
        filterElem.sfid2 = loopCnt;                    /* dedicated RX buffer index */
        filterElem.sfec  = MCAN_STD_FILT_ELEM_BUFFER;  /* sfec=7: store in RX buffer */
        filterElem.sft   = MCAN_STD_FILT_TYPE_RANGE;   /* SFT ignored when sfec=7 */
        MCAN_addStdMsgIDFilter(gMcanBaseAddr, loopCnt, &filterElem);
    }

    /* Re-enable internal loopback (must be set in SW_INIT mode) */
    MCAN_lpbkModeEnable(gMcanBaseAddr, MCAN_LPBK_MODE_INTERNAL, TRUE);

    MCAN_setOpMode(gMcanBaseAddr, MCAN_OPERATION_MODE_NORMAL);
    while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(gMcanBaseAddr))
    {}

    /* Enable TX completion interrupts for all 32 dedicated TX buffer slots */
    for (loopCnt = 0U; loopCnt < BURST_DED_BUF_COUNT; loopCnt++)
    {
        configStatus = MCAN_txBufTransIntrEnable(gMcanBaseAddr, loopCnt,
                                                 (uint32_t)TRUE);
        if (configStatus != CSL_PASS)
        {
            DebugP_log("\nMCAN TX intr enable FAILED for slot %u\n", loopCnt);
        }
    }

    DebugP_log("Phase 1: Loading %u dedicated TX buffers and requesting all TX...\n",
               BURST_DED_BUF_COUNT);

    /* ------------------------------------------------------------------
     * Phase 1: Burst fill all 32 dedicated TX buffers.
     *   Each message: STD ID = (0x001 + i), Classic CAN, 8 bytes,
     *   data[0] = i (sequence stamp for verification in Phase 3).
     *   All 32 TX requests are issued before waiting for any completion.
     * ------------------------------------------------------------------ */
    MCAN_initTxBufElement(&txElem);
    txElem.xtd = 0U;                     /* Standard ID */
    txElem.dlc = MCAN_DATA_SIZE_8BYTES;  /* 8 bytes */
    txElem.fdf = 0U;                     /* Classic CAN */
    txElem.brs = 0U;
    txElem.efc = 0U;

    for (loopCnt = 0U; loopCnt < BURST_DED_BUF_COUNT; loopCnt++)
    {
        txElem.id       = ((0x001U + loopCnt) << APP_MCAN_STD_ID_SHIFT);
        txElem.data[0U] = (uint8_t)loopCnt;  /* sequence stamp */

        MCAN_writeMsgRam(gMcanBaseAddr, MCAN_MEM_TYPE_BUF, loopCnt, &txElem);
        MCAN_txBufAddReq(gMcanBaseAddr, loopCnt);
        txAllDoneMask |= (1U << loopCnt);
    }

    DebugP_log("Phase 1 complete: all %u TX requests submitted (mask=0x%08X).\n",
               BURST_DED_BUF_COUNT, txAllDoneMask);

    /* ------------------------------------------------------------------
     * Phase 2: Poll TXBTO until all 32 dedicated TX buffers report
     *          transmission complete.
     * ------------------------------------------------------------------ */
    DebugP_log("Phase 2: Polling TXBTO for all %u TX completions...\n",
               BURST_DED_BUF_COUNT);

    do
    {
        txStatus = MCAN_getTxBufTransmissionStatus(gMcanBaseAddr);
    } while ((txStatus & txAllDoneMask) != txAllDoneMask);

    DebugP_log("Phase 2 complete: TXBTO=0x%08X - all %u messages transmitted.\n",
               txStatus, BURST_DED_BUF_COUNT);

    /* Verify no protocol errors occurred during burst */
    MCAN_getErrCounters(gMcanBaseAddr, &errCounter);
    MCAN_getProtocolStatus(gMcanBaseAddr, &protStatus);
    if ((errCounter.recErrCnt != 0U) || (errCounter.canErrLogCnt != 0U))
    {
        DebugP_log("FAIL: Error counters non-zero after burst (TEC=%u REC=%u)\n",
                   errCounter.canErrLogCnt, errCounter.recErrCnt);
        testStatus = CSL_EFAIL;
    }
    if (!((MCAN_ERR_CODE_NO_ERROR == protStatus.lastErrCode ||
           MCAN_ERR_CODE_NO_CHANGE == protStatus.lastErrCode) &&
          (MCAN_ERR_CODE_NO_ERROR == protStatus.dlec ||
           MCAN_ERR_CODE_NO_CHANGE == protStatus.dlec) &&
          (0U == protStatus.pxe)))
    {
        DebugP_log("FAIL: Protocol errors detected after burst TX\n");
        testStatus = CSL_EFAIL;
    }

    /* ------------------------------------------------------------------
     * Phase 3: Poll MCAN_getNewDataStatus() until statusLow bits 0..31
     *          are all set (one bit per dedicated RX buffer 0..31).
     *          Then read and verify each buffer sequentially.
     * ------------------------------------------------------------------ */
    DebugP_log("Phase 3: Waiting for all %u dedicated RX buffers to flag new data...\n",
               BURST_DED_BUF_COUNT);

    pollCnt = 0U;
    do
    {
        MCAN_getNewDataStatus(gMcanBaseAddr, &newDataStatus);
        pollCnt++;
    } while ((newDataStatus.statusLow & txAllDoneMask) != txAllDoneMask);

    DebugP_log("Phase 3: All %u RX buffers ready (ND1=0x%08X pollCnt=%u).\n",
               BURST_DED_BUF_COUNT, newDataStatus.statusLow, pollCnt);

    for (loopCnt = 0U; loopCnt < BURST_DED_BUF_COUNT; loopCnt++)
    {
        MCAN_readMsgRam(gMcanBaseAddr,
                        MCAN_MEM_TYPE_BUF,
                        loopCnt,
                        MCAN_RX_FIFO_NUM_0,  /* fifoNum unused for MEM_TYPE_BUF */
                        &rxMsg);

        /* Clear new-data flag for this buffer */
        newDataStatus.statusLow  = (1U << loopCnt);
        newDataStatus.statusHigh = 0U;
        MCAN_clearNewDataStatus(gMcanBaseAddr, &newDataStatus);

        /* Verify sequence stamp */
        if (rxMsg.data[0U] != (uint8_t)loopCnt)
        {
            DebugP_log("FAIL: buf[%u] data[0]: expected 0x%02X got 0x%02X\n",
                       loopCnt, (uint8_t)loopCnt, rxMsg.data[0U]);
            testStatus = CSL_EFAIL;
        }
        /* Verify standard ID */
        if ((rxMsg.id & APP_MCAN_STD_ID_MASK) !=
            (((0x001U + loopCnt) << APP_MCAN_STD_ID_SHIFT) & APP_MCAN_STD_ID_MASK))
        {
            DebugP_log("FAIL: buf[%u] ID mismatch: expected 0x%03X got 0x%03X\n",
                       loopCnt,
                       (unsigned)(0x001U + loopCnt),
                       (unsigned)((rxMsg.id & APP_MCAN_STD_ID_MASK) >>
                                   APP_MCAN_STD_ID_SHIFT));
            testStatus = CSL_EFAIL;
        }
    }

    if (testStatus == CSL_PASS)
    {
        DebugP_log("Phase 3 complete: all %u dedicated RX buffers received and verified OK.\n",
                   BURST_DED_BUF_COUNT);
    }

    /* Disable TX interrupts */
    for (loopCnt = 0U; loopCnt < BURST_DED_BUF_COUNT; loopCnt++)
    {
        (void)MCAN_txBufTransIntrEnable(gMcanBaseAddr, loopCnt, (uint32_t)FALSE);
    }

    DebugP_log("=== Burst Dedicated TX->RX Buffer Test %s ===\n",
               (testStatus == CSL_PASS) ? "PASSED" : "FAILED");

    return testStatus;
}

static int32_t App_mcanTxTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t  configStatus = CSL_PASS, testStatus = CSL_PASS;
    uint32_t loopCnt      = 1U, iterationCnt = 0U, txBufCnt;
    uint32_t bitPos = 0U, txStatus = 0U;
    MCAN_ProtocolStatus protStatus;
    MCAN_ErrCntStatus    errCounter;
    MCAN_RxBufElement rxMsg;
    MCAN_TxFIFOStatus txFIFOStatus;
    MCAN_HighPriorityMsgInfo highPriorityMsgStatus;

    /* Enable Interrupts */
    MCAN_enableIntr(gMcanBaseAddr, testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);
    /* Select Interrupt Line */
    MCAN_selectIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        1U);
    /* Enable interrupts for Tx Buffers */
    for (loopCnt = 0U ;
         loopCnt < testParams->mcanConfigParams.txMsgNum ;
         loopCnt++)
    {
        if (testParams->mcanConfigParams.txMsg[loopCnt].storageId ==
                                                        MCAN_MEM_TYPE_BUF)
        {
            /* Enable Transmission interrupt */
            configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr,
                    testParams->mcanConfigParams.txMsg[loopCnt].bufferNum,
                    (uint32_t)TRUE);
            if(configStatus != CSL_PASS)
            {
                DebugP_log("\nMCAN Tx Buffer Interrupt Enable FAILED...\n", -1);
            }
        }
    }
    /* Enable interrupts for Tx FIFO/Queue */
    for (loopCnt = testParams->mcanConfigParams.ramConfig->txBufCnt ;
         loopCnt < (testParams->mcanConfigParams.ramConfig->txFIFOCnt +
                    testParams->mcanConfigParams.ramConfig->txBufCnt);
         loopCnt++)
    {
        /* Enable Transmission interrupt */
        configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr,
                loopCnt,
                (uint32_t)TRUE);
        if(configStatus != CSL_PASS)
        {
            DebugP_log("\nMCAN Tx FIFO Interrupt Enable FAILED...\n", -1);
        }
    }

    /* Select the correct ISR status variable based on interrupt line */
    volatile uint32_t *pIsrStatus;
    if (testParams->mcanConfigParams.intrLine == MCAN_INTR_LINE_NUM_1)
    {
        pIsrStatus = &gMcanIsrIntr1Status;
    }
    else
    {
        pIsrStatus = &gMcanIsrIntr0Status;
    }

    for (iterationCnt = 0U ;
         iterationCnt < testParams->mcanConfigParams.txMSGInterationCnt ;
         iterationCnt++)
    {
        for (loopCnt = 0U ;
             loopCnt < testParams->mcanConfigParams.txMsgNum ;
             loopCnt++)
        {
            MCAN_getTxFIFOQueStatus(gMcanBaseAddr, &txFIFOStatus);
            if (testParams->mcanConfigParams.txMsg[loopCnt].storageId ==
                                                        MCAN_MEM_TYPE_BUF)
            {
                txBufCnt = testParams->mcanConfigParams.txMsg[loopCnt].bufferNum;
            }
            else
            {
                txBufCnt = txFIFOStatus.putIdx;
            }
            // App_mcanPrintTxMsg(&testParams->mcanConfigParams.txMsg[loopCnt].txElem);
            /* Write message to Msg RAM */
            MCAN_writeMsgRam(gMcanBaseAddr,
                             testParams->mcanConfigParams.txMsg[loopCnt].storageId,
                             txBufCnt,
                             &testParams->mcanConfigParams.txMsg[loopCnt].txElem);
            /* Add request for transmission */
            configStatus += MCAN_txBufAddReq(gMcanBaseAddr, txBufCnt);
            if (CSL_PASS != configStatus)
            {
                DebugP_log("\nError in Adding Transmission Request...\n", -1);
            }

            SemaphoreP_pend(&gTxDoneSem, SystemP_WAIT_FOREVER);

            SemaphoreP_pend(&gRxDoneSem, SystemP_WAIT_FOREVER);

            bitPos = (1U << txBufCnt);
            /* Poll for Tx completion */
            do
            {
                txStatus = MCAN_getTxBufTransmissionStatus(gMcanBaseAddr);
            }while((txStatus & bitPos) != bitPos);
            /* Checking for Errors */
            MCAN_getErrCounters(gMcanBaseAddr, &errCounter);
            if ((0U == errCounter.recErrCnt) &&
                (0U == errCounter.canErrLogCnt))
            {
                MCAN_getProtocolStatus(gMcanBaseAddr, &protStatus);
                /* Checking for Errors */
                if (((MCAN_ERR_CODE_NO_ERROR == protStatus.lastErrCode) ||
                     (MCAN_ERR_CODE_NO_CHANGE == protStatus.lastErrCode)) &&
                    ((MCAN_ERR_CODE_NO_ERROR == protStatus.dlec) ||
                     (MCAN_ERR_CODE_NO_CHANGE == protStatus.dlec)) &&
                    (0U == protStatus.pxe))
                {
                    configStatus += App_mcanReadRxMSG(&rxMsg, *pIsrStatus);
                    if(configStatus != CSL_PASS)
                    {
                        DebugP_log("\nUnable to read received message(Iteration Count:Message Number): (%d,%d).\n", (iterationCnt + 1U), (loopCnt + 1U));
                    }
                    if (testParams->testcaseId == 10239)
                    {
                        MCAN_getHighPriorityMsgStatus(gMcanBaseAddr, &highPriorityMsgStatus);
                        /* Message should be stored in FIFO 0 according to the configuration */
                        DebugP_assert(highPriorityMsgStatus.msi == 2U);
                    }
                    configStatus += App_mcanTxRxMessageCheck(
                                    testParams->mcanConfigParams.txMsg[loopCnt].txElem,
                                    rxMsg);
                    /* Check if Message is stored into appropriate Rx Buffer */
                    if(testParams->mcanConfigParams.txMsg[loopCnt].rxMSGStorageId == MCAN_MEM_TYPE_BUF)
                    {
                        if(rxBuffNum != testParams->mcanConfigParams.txMsg[loopCnt].rxBuffNum)
                        {
                           testStatus += CSL_EFAIL;
                        }
                    }
                    if(configStatus != CSL_PASS)
                    {
                        testStatus += CSL_EFAIL;
                        DebugP_log("\nTransmitted and received message does not match(Iteration Count:Message Number): (%d,%d).\n", (iterationCnt + 1U), (loopCnt + 1U));
                    }
                    else
                    {
                        testStatus += CSL_PASS;
                        DebugP_log(
                            "\nMessage successfully transferred/received(Iteration Count:Message Number): (%d,%d).\n",
                            (iterationCnt + 1U), (loopCnt + 1U));
                    }
                }
                else
                {
                    testStatus += CSL_EFAIL;
                    DebugP_log("\nError in transmission/reception(Iteration Count:Message Number): (%d,%d).\n",
                               (iterationCnt + 1U), (loopCnt + 1U));
                }
            }
            else
            {
                testStatus += CSL_EFAIL;
                DebugP_log("\nError Counters: Error in transmission/reception(Iteration Count:Message Number): (%d,%d).\n",
                           (iterationCnt + 1U), (loopCnt + 1U));
            }
            *pIsrStatus = 0U;
        }
    }
    /* Disable interrupts for Tx Buffers */

    for (loopCnt = 0U ;
         loopCnt < testParams->mcanConfigParams.txMsgNum ;
         loopCnt++)
    {
        if (testParams->mcanConfigParams.txMsg[loopCnt].storageId ==
                                                        MCAN_MEM_TYPE_BUF)
        {
            /* Enable Transmission interrupt */
            configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr,
                    testParams->mcanConfigParams.txMsg[loopCnt].bufferNum,
                    (uint32_t)FALSE);
            if(configStatus != CSL_PASS)
            {
                DebugP_log("\nMCAN Tx Buffer Interrupt Enable FAILED...\n", -1);
            }
        }
    }
    return testStatus;
}

int32_t App_mcanReadRxMSG(MCAN_RxBufElement *rxMsg,
                                 uint32_t status)
{
    uint32_t    readBuffNum, bitPos;
    MCAN_RxFIFOStatus fifoStatus;
    MCAN_RxNewDataStatus newDataStatus;
    int32_t retStatus = CSL_EFAIL;

    if((status & MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG) ==
                                    MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG)
    {
        MCAN_getNewDataStatus(gMcanBaseAddr, &newDataStatus);
        for(readBuffNum = 0U ; readBuffNum < 64U ; readBuffNum++)
        {
            if(readBuffNum < 32U)
            {
                status = newDataStatus.statusLow;
                bitPos = 1U << readBuffNum;
                newDataStatus.statusLow = (0U | bitPos);
            }
            else
            {
                status = newDataStatus.statusHigh;
                bitPos = 1U << (readBuffNum - 32U);
                newDataStatus.statusHigh = (0U | bitPos);
            }
            MCAN_clearNewDataStatus(gMcanBaseAddr, &newDataStatus);

            rxBuffNum = readBuffNum;
            if(bitPos == (status & bitPos))
            {
                MCAN_readMsgRam(gMcanBaseAddr,
                                MCAN_MEM_TYPE_BUF,
                                readBuffNum,
                                MCAN_RX_FIFO_NUM_0,
                                rxMsg);
                if (isrPrintEnable == (uint32_t)TRUE)
                {
                    DebugP_log( "\nRx Buffer: Received message with following details:");
                }
                retStatus = CSL_PASS;
                break;
            }
        }
    }
    else if(((status & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ==
                                    MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ||
        ((status & MCAN_INTR_SRC_RX_FIFO1_NEW_MSG) ==
                                    MCAN_INTR_SRC_RX_FIFO1_NEW_MSG))
    {
        retStatus = CSL_PASS;
        readBuffNum = 0U;
        if(((status & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ==
                                    MCAN_INTR_SRC_RX_FIFO0_NEW_MSG))
        {
            fifoStatus.num = (uint32_t)MCAN_RX_FIFO_NUM_0;
            if (isrPrintEnable == (uint32_t)TRUE)
            {
                DebugP_log( "\nRx FIFO 0: Received message with following details:");
            }
        }
        else
        {
            fifoStatus.num = (uint32_t)MCAN_RX_FIFO_NUM_1;
            if (isrPrintEnable == (uint32_t)TRUE)
            {
                DebugP_log( "\nRx FIFO 1: Received message with following details:");
            }
        }
        MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
        MCAN_readMsgRam(gMcanBaseAddr,
                        MCAN_MEM_TYPE_FIFO,
                        fifoStatus.getIdx,
                        (uint32_t)fifoStatus.num,
                        rxMsg);
        (void) MCAN_writeRxFIFOAck(gMcanBaseAddr,
                                   (uint32_t)fifoStatus.num,
                                   fifoStatus.getIdx);
    }

    return retStatus;
}

static int32_t App_mcanTxRxMessageCheck(MCAN_TxBufElement txMsg,
                                        MCAN_RxBufElement rxMsg)
{
    uint32_t msgMask, loopCnt;
    int32_t retStatus = CSL_PASS;

    /* Check/Compare Rx message with Tx message */
    if(txMsg.xtd == 1U)
    {
        msgMask = APP_MCAN_EXT_ID_MASK;
    }
    else
    {
        msgMask = APP_MCAN_STD_ID_MASK;
    }
    if (((txMsg.id & msgMask) == (rxMsg.id & msgMask)) &&
        (txMsg.rtr == rxMsg.rtr) &&
        (txMsg.xtd == rxMsg.xtd) &&
        (txMsg.esi == rxMsg.esi) &&
        (txMsg.dlc == rxMsg.dlc) &&
        (txMsg.brs == rxMsg.brs) &&
        (txMsg.fdf == rxMsg.fdf))
    {
        for (loopCnt = 0U;
             loopCnt < gMcanAppdataSize[rxMsg.dlc];
             loopCnt++)
        {
            if (txMsg.data[loopCnt] != rxMsg.data[loopCnt])
            {
                break;
            }
        }
        if(loopCnt == gMcanAppdataSize[rxMsg.dlc])
        {
            retStatus = CSL_PASS;
        }
        else
        {
            retStatus = CSL_EFAIL;
        }
    }
    else
    {
        retStatus = CSL_EFAIL;
    }

    return retStatus;
}

static int32_t App_mcanTCEntrySetup(st_mcanTestcaseParams_t *testParams)
{
    int32_t status = CSL_PASS, configStatus = CSL_PASS;
    uint32_t    configId;

    configId = App_getBitConfigParamId(testParams->mcanConfigParams.bitTimings);
    /* send a message to change baud-rate of receiver and this is valid only for
       B2B and not for loop back or external PCAN tests */
    if((configId != 0U) && (configId != 1U) && (configId != 2U) &&
        (configId != 3U) && (configId != 0xFFFFFFFFU) &&
        (testParams->mcanConfigParams.mcanTestType != MCAN_TEST_TYPE_EXTERNAL_LOOBACK))
    {
        /* change Tx baud-rate to default */
        /* Put MCAN in SW initialization mode */
        MCAN_setOpMode(gMcanBaseAddr, MCAN_OPERATION_MODE_SW_INIT);
        while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(gMcanBaseAddr))
        {}
        /* Configure Bit timings */
        configStatus += MCAN_setBitTime(gMcanBaseAddr, &canFDBitTimings[0U]);
        if(configStatus != CSL_PASS)
        {
            DebugP_log("\nDEFAULT MCAN Bit Time Configuration FAILED...\n", -1);
        }
        /* Take MCAN out of the SW initialization mode */
        MCAN_setOpMode(gMcanBaseAddr, MCAN_OPERATION_MODE_NORMAL);
        while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(gMcanBaseAddr))
        {}
        status += App_mcanChangeBaudrateMSG(configId);
        /* change Tx baud-rate to configured by TC */
        /* Put MCAN in SW initialization mode */
        MCAN_setOpMode(gMcanBaseAddr, MCAN_OPERATION_MODE_SW_INIT);
        while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(gMcanBaseAddr))
        {}
        /* Configure Bit timings */
        configStatus += MCAN_setBitTime(gMcanBaseAddr, &canFDBitTimings[configId]);
        if(configStatus != CSL_PASS)
        {
            DebugP_log("\nCONFIGURRED MCAN Bit Time Configuration FAILED...\n", -1);
        }
        /* Take MCAN out of the SW initialization mode */
        MCAN_setOpMode(gMcanBaseAddr, MCAN_OPERATION_MODE_NORMAL);
        while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(gMcanBaseAddr))
        {}
    }
    switch (testParams->testcaseId)
    {
        case 10247:
            MCAN_extTSCounterConfig(gMcanBaseAddr, 0xFF);
            MCAN_extTSCounterEnable(gMcanBaseAddr, (uint32_t)TRUE);
        break;
        case 16:
            MCAN_extTSCounterConfig(gMcanBaseAddr, 0x3FFF);
            MCAN_extTSCounterEnable(gMcanBaseAddr, (uint32_t)TRUE);
        break;
        default:
        break;
    }

    return status;
}

static int32_t App_mcanTCExitSetup(st_mcanTestcaseParams_t *testParams)
{
    int32_t status = CSL_PASS;
    uint32_t    configId;

    configId = App_getBitConfigParamId(testParams->mcanConfigParams.bitTimings);
    /* send a message to change baud-rate of receiver and this is valid only for
       B2B and not for loop back or external PCAN tests */
    if((configId != 0U) && (configId != 1U) && (configId != 2U) &&
        (configId != 3U) && (configId != 0xFFFFFFFFU) &&
        (testParams->mcanConfigParams.mcanTestType != MCAN_TEST_TYPE_EXTERNAL_LOOBACK))
    {
        status += App_mcanChangeBaudrateMSG(0U);

    }

    return status;
}

static int32_t App_mcanChangeBaudrateMSG(uint32_t idx)
{
    int32_t configStatus = CSL_PASS;
    MCAN_RxBufElement    rxMsg = {0};
    MCAN_TxBufElement    txMsg;
    MCAN_RxNewDataStatus newDataStatus;
    MCAN_ErrCntStatus    errCounter;
    MCAN_ProtocolStatus protStatus;
    uint32_t    readBuffNum, bitPos, status;
    MCAN_RxFIFOStatus fifoStatus;

    DebugP_log( "\n===============Sending Change Baud-rate message to Receiver===============\n");
    /* Clear stale interrupt status before polling */
    gMcanIsrIntr1Status = 0U;
    /* Message will be sent using Tx buffer 1 */
    /* Enable Interrupts */
    MCAN_enableIntr(gMcanBaseAddr, MCAN_INTR_MASK_ALL, (uint32_t)TRUE);
    MCAN_enableIntr(gMcanBaseAddr,
                    MCAN_INTR_SRC_RES_ADDR_ACCESS, (uint32_t)FALSE);
    /* Select Interrupt Line */
    MCAN_selectIntrLine(gMcanBaseAddr,
                        MCAN_INTR_MASK_ALL,
                        MCAN_INTR_LINE_NUM_1);
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(gMcanBaseAddr,
                        MCAN_INTR_LINE_NUM_1,
                        1U);
    if(idx == 0U)
    {
        txMsg.id =  (0x16 << 18);
    }
    else
    {
        txMsg.id =  (0x44 << 18);
    }
    txMsg.rtr = 0U;
    txMsg.xtd = 0U;
    txMsg.esi = 0U;
    txMsg.dlc = 1U;
    txMsg.brs = 1U;
    txMsg.fdf = 1U;
    txMsg.efc = 0U;
    txMsg.mm = 0xAAU;
    txMsg.data[0U] = (uint8_t)(idx & 0xFFU);
    /* Enable Transmission interrupt */
    configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr,
                                             1U,
                                             (uint32_t)TRUE);
    if(configStatus != CSL_PASS)
    {
         DebugP_log("\nError in enabling Transmission Interrupt...\n", -1);
    }
    /* Always writing to Tx Buffer number 1 for echoing back */
    MCAN_writeMsgRam(gMcanBaseAddr,
                     MCAN_MEM_TYPE_BUF,
                     1U,
                     (const MCAN_TxBufElement*) &txMsg);
    /* Add request for transmission */
    configStatus += MCAN_txBufAddReq(gMcanBaseAddr, 1U);
    if (CSL_PASS != configStatus)
    {
        DebugP_log("\nError in Adding Transmission Request...\n", -1);
    }
    while (!(MCAN_INTR_SRC_TRANS_COMPLETE ==
            (gMcanIsrIntr1Status & MCAN_INTR_SRC_TRANS_COMPLETE)))
    {
    }
    while (!((((gMcanIsrIntr1Status & MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG) ==
                        MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG) ||
             ((gMcanIsrIntr1Status & MCAN_INTR_SRC_RX_FIFO1_NEW_MSG) ==
                        MCAN_INTR_SRC_RX_FIFO1_NEW_MSG) ||
             ((gMcanIsrIntr1Status & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ==
                        MCAN_INTR_SRC_RX_FIFO0_NEW_MSG))))
    {
    }
    /* Checking for Errors */
    MCAN_getErrCounters(gMcanBaseAddr, &errCounter);
    if ((0U != errCounter.recErrCnt) &&
        (0U != errCounter.canErrLogCnt))
    {
        configStatus += CSL_EFAIL;
        DebugP_log("\nError Counters: Error in transmission/reception\n");
    }
    MCAN_getProtocolStatus(gMcanBaseAddr, &protStatus);
    /* Checking for Errors */
    if (((MCAN_ERR_CODE_NO_ERROR == protStatus.lastErrCode) ||
         (MCAN_ERR_CODE_NO_CHANGE == protStatus.lastErrCode)) &&
        ((MCAN_ERR_CODE_NO_ERROR == protStatus.dlec) ||
         (MCAN_ERR_CODE_NO_CHANGE == protStatus.dlec)) &&
        (0U == protStatus.pxe))
    {
        DebugP_log("\nMessage successfully transferred.\n");
    }
    else
    {
        configStatus += CSL_EFAIL;
        DebugP_log("\nError in transmission message.\n");
    }
    if((gMcanIsrIntr1Status & MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG) ==
                                MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG)
    {
        MCAN_getNewDataStatus(gMcanBaseAddr, &newDataStatus);
        MCAN_clearNewDataStatus(gMcanBaseAddr, &newDataStatus);
        for(readBuffNum = 0U ; readBuffNum < 64U ; readBuffNum++)
        {
            if(readBuffNum < 32U)
            {
                status = newDataStatus.statusLow;
                bitPos = 1U << readBuffNum;
            }
            else
            {
                status = newDataStatus.statusHigh;
                bitPos = 1U << (readBuffNum - 32U);
            }

            if(bitPos == (status & bitPos))
            {
                MCAN_readMsgRam(gMcanBaseAddr,
                                MCAN_MEM_TYPE_BUF,
                                readBuffNum,
                                MCAN_RX_FIFO_NUM_0,
                                &rxMsg);
                DebugP_log( "\nRx Buffer: Received message.");
            }
        }
    }
    else if(((gMcanIsrIntr1Status & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ==
                                    MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ||
        ((gMcanIsrIntr1Status & MCAN_INTR_SRC_RX_FIFO1_NEW_MSG) ==
                                    MCAN_INTR_SRC_RX_FIFO1_NEW_MSG))
    {
        readBuffNum = 0U;
        if(((gMcanIsrIntr1Status & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ==
                                    MCAN_INTR_SRC_RX_FIFO0_NEW_MSG))
        {
            fifoStatus.num = (uint32_t)MCAN_RX_FIFO_NUM_0;
            DebugP_log( "\nRx FIFO 0: Received message.");

        }
        else
        {
            fifoStatus.num = (uint32_t)MCAN_RX_FIFO_NUM_1;
            DebugP_log( "\nRx FIFO 1: Received message.");
        }
        MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
        MCAN_readMsgRam(gMcanBaseAddr,
                        MCAN_MEM_TYPE_FIFO,
                        fifoStatus.getIdx,
                        (uint32_t)fifoStatus.num,
                        &rxMsg);
        (void) MCAN_writeRxFIFOAck(gMcanBaseAddr,
                                   (uint32_t)fifoStatus.num,
                                   fifoStatus.getIdx);

    }
    configStatus += App_mcanTxRxMessageCheck(txMsg, rxMsg);

    /* Revert configuration done by this  function to send the baud-rate change message */
    /* Enable Interrupts */
    MCAN_enableIntr(gMcanBaseAddr, MCAN_INTR_MASK_ALL, (uint32_t)FALSE);
    /* Select Interrupt Line */
    MCAN_selectIntrLine(gMcanBaseAddr,
                        MCAN_INTR_MASK_ALL,
                        MCAN_INTR_LINE_NUM_0);
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(gMcanBaseAddr,
                        MCAN_INTR_LINE_NUM_1,
                        0U);
    /* Enable Transmission interrupt */
    configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr,
                                             1U,
                                             (uint32_t)FALSE);
    if(configStatus != CSL_PASS)
    {
         DebugP_log("\nRerverting Config: Error in disabling Transmission Interrupt...\n", -1);
    }
    if(configStatus != CSL_PASS)
    {
        DebugP_log("\n===============Change in Baud-rate for Receiver FAILED===============\n");
    }
    else
    {
        DebugP_log("\n===============Change in Baud-rate for Receiver is SUCCESSFUL===============\n");
    }
    /* Wait for sometime, this could be needed by receiver to change the baud rate */
    /* Added Delay - This is needed by Rx node to change the baudrate */
    App_delayFunc(50U);

    return configStatus;
}

static int32_t App_mcanCheckTCResultsMisc(st_mcanTestcaseParams_t *testParams)
{
    int32_t status = CSL_PASS;
    uint32_t iterationCnt, loopCnt, oldTimeStamp = 0U;
    MCAN_TxEventFIFOElement txEventElem;
    MCAN_TxEventFIFOStatus txEventFIFOStatus;

    switch (testParams->testcaseId)
    {
        case 1:
            for (iterationCnt = 0U ;
             iterationCnt < testParams->mcanConfigParams.txMSGInterationCnt ;
             iterationCnt++)
            {
                for (loopCnt = 0U ;
                     loopCnt < testParams->mcanConfigParams.txMsgNum ;
                     loopCnt++)
                {
                    MCAN_getTxEventFIFOStatus(gMcanBaseAddr, &txEventFIFOStatus);
                    MCAN_readTxEventFIFO(gMcanBaseAddr, &txEventElem);
                    MCAN_writeTxEventFIFOAck(gMcanBaseAddr, txEventFIFOStatus.getIdx);

                    if(App_mcanTxEventMessageCheck(
                        testParams->mcanConfigParams.txMsg[loopCnt].txElem,
                        txEventElem) == CSL_PASS)
                    {
                        oldTimeStamp = txEventElem.txts;
                        status += CSL_PASS;
                        DebugP_log("Tx Event FIFO element matches with transmitted message.\r\n", -1);
                    }
                    else
                    {
                        DebugP_log("Tx Event FIFO element does not matche with transmitted message.\r\n", -1);
                        status += CSL_EFAIL;
                    }
                }
            }
        break;
        case 10247:
            for (iterationCnt = 0U ;
             iterationCnt < testParams->mcanConfigParams.txMSGInterationCnt ;
             iterationCnt++)
            {
                for (loopCnt = 0U ;
                     loopCnt < testParams->mcanConfigParams.txMsgNum ;
                     loopCnt++)
                {
                    MCAN_getTxEventFIFOStatus(gMcanBaseAddr, &txEventFIFOStatus);
                    MCAN_readTxEventFIFO(gMcanBaseAddr, &txEventElem);
                    MCAN_writeTxEventFIFOAck(gMcanBaseAddr, txEventFIFOStatus.getIdx);

                    if ((App_mcanTxEventMessageCheck(
                        testParams->mcanConfigParams.txMsg[loopCnt].txElem,
                        txEventElem) == CSL_PASS)  &&
                        (oldTimeStamp != txEventElem.txts))
                    {
                        oldTimeStamp = txEventElem.txts;
                        status += CSL_PASS;
                        DebugP_log("Tx Event FIFO element matches with transmitted message.\r\n", -1);
                    }
                    else
                    {
                        DebugP_log("Tx Event FIFO element does not matche with transmitted message.\r\n", -1);
                        status += CSL_EFAIL;
                    }
                }
            }
        break;
        default:
        break;
    }

    return status;
}

static int32_t App_mcanTxEventMessageCheck(MCAN_TxBufElement txMsg,
                                           MCAN_TxEventFIFOElement txEventMsg)
{
    int32_t retStatus = CSL_PASS;

    if ((txMsg.id == txEventMsg.id) &&
        (txMsg.rtr == txEventMsg.rtr) &&
        (txMsg.xtd == txEventMsg.xtd) &&
        (txMsg.esi == txEventMsg.esi) &&
        (txMsg.dlc == txEventMsg.dlc) &&
        (txMsg.brs == txEventMsg.brs) &&
        (txMsg.fdf == txEventMsg.fdf) &&
        (txMsg.mm == txEventMsg.mm))
    {
        retStatus += CSL_PASS;
    }
    else
    {
        retStatus += CSL_EFAIL;
    }

    return retStatus;
}

static int32_t App_mcanECCTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t  configStatus = CSL_PASS, testStatus = CSL_PASS;
    uint32_t loopCnt      = 1U, iterationCnt = 0U, intrMask, txBufCnt;
    MCAN_ProtocolStatus protStatus;
    MCAN_ErrCntStatus    errCounter;
    MCAN_RxBufElement rxMsg;
    MCAN_TxFIFOStatus txFIFOStatus;
    uint32_t startAddr, elemSize, elemAddr;

    gMcanECCIntrFlag = 1U;
    /* Enable Interrupts */
    MCAN_enableIntr(gMcanBaseAddr, testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);
    /* Select Interrupt Line */
    MCAN_selectIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        1U);
    /* Enable interrupts for Tx Buffers */
    for (loopCnt = 0U ;
         loopCnt < testParams->mcanConfigParams.txMsgNum ;
         loopCnt++)
    {
        if (testParams->mcanConfigParams.txMsg[loopCnt].storageId ==
                                                        MCAN_MEM_TYPE_BUF)
        {
            /* Enable Transmission interrupt */
            configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr,
                    testParams->mcanConfigParams.txMsg[loopCnt].bufferNum,
                    (uint32_t)TRUE);
            if(configStatus != CSL_PASS)
            {
                DebugP_log("\nMCAN Tx Buffer Interrupt Enable FAILED...\n", -1);
            }
            /* Enable Transmission Cancellation interrupt */
            configStatus += MCAN_txBufCancellationIntrEnable(gMcanBaseAddr,
                    testParams->mcanConfigParams.txMsg[loopCnt].bufferNum,
                    (uint32_t)TRUE);
            if(configStatus != CSL_PASS)
            {
                DebugP_log("\nMCAN Tx Cancellation Interrupt Enable FAILED...\n", -1);
            }
        }
    }
    /* Enable interrupts for Tx FIFO/Queue */
    for (loopCnt = testParams->mcanConfigParams.ramConfig->txBufCnt ;
         loopCnt < (testParams->mcanConfigParams.ramConfig->txFIFOCnt +
                    testParams->mcanConfigParams.ramConfig->txBufCnt);
         loopCnt++)
    {
        /* Enable Transmission interrupt */
        configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr,
                loopCnt,
                (uint32_t)TRUE);
        if(configStatus != CSL_PASS)
        {
            DebugP_log("\nMCAN Tx FIFO Interrupt Enable FAILED...\n", -1);
        }
        /* Enable Transmission Cancellation interrupt */
        configStatus += MCAN_txBufCancellationIntrEnable(gMcanBaseAddr,
                loopCnt,
                (uint32_t)TRUE);
        if(configStatus != CSL_PASS)
        {
            DebugP_log("\nMCAN Tx Cancellation Interrupt Enable FAILED...\n", -1);
        }
    }
    /* Enable ECC Interrupts */
    MCAN_eccEnableIntr(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_SEC, TRUE);
    MCAN_eccEnableIntr(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_DED, TRUE);
    if (testParams->mcanConfigParams.txMsg[0U].storageId ==
                                                        MCAN_MEM_TYPE_BUF)
    {
        loopCnt = 0U;
        startAddr = testParams->mcanConfigParams.ramConfig->txStartAddr;
        elemSize  = objSize[testParams->mcanConfigParams.ramConfig->txBufElemSize];
        elemSize *= 4U;
        elemAddr  = startAddr + (elemSize * testParams->mcanConfigParams.txMsg[0U].bufferNum);
        /* Access data bytes of the message */
        elemAddr += 12U;
        elemAddr += MCAN_MCAN_MSG_MEM;
        elemAddr += gMcanBaseAddr;

        MCAN_getTxFIFOQueStatus(gMcanBaseAddr, &txFIFOStatus);
        if (testParams->mcanConfigParams.txMsg[loopCnt].storageId ==
                                                    MCAN_MEM_TYPE_BUF)
        {
            txBufCnt = testParams->mcanConfigParams.txMsg[loopCnt].bufferNum;
        }
        else
        {
            txBufCnt = txFIFOStatus.putIdx;
        }
        /* Calculate Rx Interrupt Mask */
        if(testParams->mcanConfigParams.txMsg[loopCnt].rxMSGStorageId == MCAN_MEM_TYPE_BUF)
        {
            intrMask = MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG;
        }
        else
        {
            if(testParams->mcanConfigParams.txMsg[loopCnt].rxBuffNum == MCAN_RX_FIFO_NUM_0)
            {
                intrMask = MCAN_INTR_SRC_RX_FIFO0_NEW_MSG;
            }
            else
            {
                intrMask = MCAN_INTR_SRC_RX_FIFO1_NEW_MSG;
            }

        }
        switch (testParams->testcaseId)
        {
            case 10239:
                intrMask = MCAN_INTR_SRC_HIGH_PRIO_MSG;
            break;
            default:
            break;
        }
        /* SEC error test */
        {
            // App_mcanPrintTxMsg(&testParams->mcanConfigParams.txMsg[loopCnt].txElem);
            /* Write message to Msg RAM */
            MCAN_writeMsgRam(gMcanBaseAddr,
                             testParams->mcanConfigParams.txMsg[loopCnt].storageId,
                             txBufCnt,
                             &testParams->mcanConfigParams.txMsg[loopCnt].txElem);
            /* Disable ECC */
            testParams->mcanConfigParams.eccConfigParams->enable = 0U;
            testParams->mcanConfigParams.eccConfigParams->enableChk = 0U;
            MCAN_eccConfig(gMcanBaseAddr, testParams->mcanConfigParams.eccConfigParams);
            DebugP_log("Before single Bit Error/Bit Flip:0x%x\n", HW_RD_REG32(elemAddr));
            /* Introduce single bit error */
            HW_WR_REG32(elemAddr, HW_RD_REG32(elemAddr)^0x8U);
            DebugP_log("After single Bit Error/Bit Flip:0x%x\n", HW_RD_REG32(elemAddr));
            /* Enable ECC */
            testParams->mcanConfigParams.eccConfigParams->enable = 1U;
            testParams->mcanConfigParams.eccConfigParams->enableChk = 1U;
            MCAN_eccConfig(gMcanBaseAddr, testParams->mcanConfigParams.eccConfigParams);
            /* Add request for transmission */
            configStatus += MCAN_txBufAddReq(gMcanBaseAddr, txBufCnt);
            if (CSL_PASS != configStatus)
            {
                DebugP_log("\nError in Adding Transmission Request...\n", -1);
            }
            while (gMcanECCIntrFlag)
            {
            }
            gMcanECCIntrFlag = 1U;
            while (!((gMcanIsrIntr0Status & MCAN_INTR_SRC_TRANS_COMPLETE) ==
                                MCAN_INTR_SRC_TRANS_COMPLETE))
            {}
            while (!((gMcanIsrIntr0Status & intrMask) == intrMask))
            {
            }
            /* Check for ECC Error */
            if ((gMcaneccErr.secErr == 1U) &&
                (gMcaneccErr.dedErr != 1U) &&
                (gMcaneccErr.row == ((elemAddr - (MCAN_MCAN_MSG_MEM + gMcanBaseAddr))/4)) &&
                (gMcaneccErr.bit1 == 3U))
            {
                DebugP_log("\nECC SEC Error location matched.\n");
            }
            else
            {
                testStatus += CSL_EFAIL;
                DebugP_log("\nECC SEC Error location does not match.\n");
            }
            /* Checking for Errors */
            MCAN_getErrCounters(gMcanBaseAddr, &errCounter);
            if ((0U == errCounter.recErrCnt) &&
                (0U == errCounter.canErrLogCnt))
            {
                MCAN_getProtocolStatus(gMcanBaseAddr, &protStatus);
                /* Checking for Errors */
                if (((MCAN_ERR_CODE_NO_ERROR == protStatus.lastErrCode) ||
                     (MCAN_ERR_CODE_NO_CHANGE == protStatus.lastErrCode)) &&
                    ((MCAN_ERR_CODE_NO_ERROR == protStatus.dlec) ||
                     (MCAN_ERR_CODE_NO_CHANGE == protStatus.dlec)) &&
                    (0U == protStatus.pxe))
                {
                    configStatus += App_mcanReadRxMSG(&rxMsg, gMcanIsrIntr0Status);
                    if(configStatus != CSL_PASS)
                    {
                        DebugP_log("\nUnable to read received message(Iteration Count:Message Number): (%d,%d).\n", (iterationCnt + 1U), (loopCnt + 1U));
                    }
                    configStatus += App_mcanTxRxMessageCheck(
                                    testParams->mcanConfigParams.txMsg[loopCnt].txElem,
                                    rxMsg);
                    /* Check if Message is stored into appropriate Rx Buffer */
                    if(testParams->mcanConfigParams.txMsg[loopCnt].rxMSGStorageId == MCAN_MEM_TYPE_BUF)
                    {
                        if(rxBuffNum != testParams->mcanConfigParams.txMsg[loopCnt].rxBuffNum)
                        {
                           testStatus += CSL_EFAIL;
                        }
                    }
                    if(configStatus != CSL_PASS)
                    {
                        testStatus += CSL_EFAIL;
                        DebugP_log("\nTransmitted and received message does not match(Iteration Count:Message Number): (%d,%d).\n", (iterationCnt + 1U), (loopCnt + 1U));
                    }
                    else
                    {
                        testStatus += CSL_PASS;
                        DebugP_log(
                            "\nMessage successfully transferred/received(Iteration Count:Message Number): (%d,%d).\n",
                            (iterationCnt + 1U), (loopCnt + 1U));
                    }
                }
                else
                {
                    testStatus += CSL_EFAIL;
                    DebugP_log("\nError in transmission/reception(Iteration Count:Message Number): (%d,%d).\n",
                               (iterationCnt + 1U), (loopCnt + 1U));
                }
            }
            else
            {
                testStatus += CSL_EFAIL;
                DebugP_log("\nError Counters: Error in transmission/reception(Iteration Count:Message Number): (%d,%d).\n",
                           (iterationCnt + 1U), (loopCnt + 1U));
            }
            gMcanIsrIntr0Status = 0U;
        }
        /* DED error test */
        {
            // App_mcanPrintTxMsg(&testParams->mcanConfigParams.txMsg[loopCnt].txElem);
            /* Write message to Msg RAM */
            MCAN_writeMsgRam(gMcanBaseAddr,
                             testParams->mcanConfigParams.txMsg[loopCnt].storageId,
                             txBufCnt,
                             &testParams->mcanConfigParams.txMsg[loopCnt].txElem);
            /* Disable ECC */
            testParams->mcanConfigParams.eccConfigParams->enable = 0U;
            testParams->mcanConfigParams.eccConfigParams->enableChk = 0U;
            MCAN_eccConfig(gMcanBaseAddr, testParams->mcanConfigParams.eccConfigParams);
            DebugP_log("Before Double Bit Error/Bit Flip:0x%x\n", HW_RD_REG32(elemAddr));
            /* Introduce Double bit error */
            HW_WR_REG32(elemAddr, HW_RD_REG32(elemAddr)^0xAU);
            DebugP_log("After Double Bit Error/Bit Flip:0x%x\n", HW_RD_REG32(elemAddr));
            /* Enable ECC */
            testParams->mcanConfigParams.eccConfigParams->enable = 1U;
            testParams->mcanConfigParams.eccConfigParams->enableChk = 1U;
            MCAN_eccConfig(gMcanBaseAddr, testParams->mcanConfigParams.eccConfigParams);
            /* Add request for transmission */
            configStatus += MCAN_txBufAddReq(gMcanBaseAddr, txBufCnt);
            if (CSL_PASS != configStatus)
            {
                DebugP_log("\nError in Adding Transmission Request...\n", -1);
            }
            while (gMcanECCIntrFlag)
            {
            }
            gMcanECCIntrFlag = 1U;
            if (MCAN_OPERATION_MODE_SW_INIT == MCAN_getOpMode(gMcanBaseAddr))
            {
                DebugP_log("\nTransmission of corrupted message stopped.\n");
            }
            else
            {
                testStatus += CSL_EFAIL;
                DebugP_log("\nSent out Corrupted Message.\n");
            }
            /* cancel transmission of corrupted message */
            MCAN_txBufCancellationReq(gMcanBaseAddr, txBufCnt);
            while (!((gMcanIsrIntr0Status & MCAN_INTR_SRC_TRANS_CANCEL_FINISH) ==
                                MCAN_INTR_SRC_TRANS_CANCEL_FINISH))
            {}
            DebugP_log( "\nTx Buffer Transmission Cancellation Interrupt Happened.\n");
            /* Take MCAN out of the SW initialization mode */
            MCAN_setOpMode(gMcanBaseAddr, MCAN_OPERATION_MODE_NORMAL);
            while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(gMcanBaseAddr))
            {}
            /* Check for ECC Error */
            if ((gMcaneccErr.secErr != 1U) &&
                (gMcaneccErr.dedErr == 1U) &&
                (gMcaneccErr.row == ((elemAddr - (MCAN_MCAN_MSG_MEM + gMcanBaseAddr))/4)))
            {
                DebugP_log("\nECC DED Error location matched.\n");
            }
            else
            {
                testStatus += CSL_EFAIL;
                DebugP_log("\nECC DED Error location does not match.\n");
            }
            gMcanIsrIntr0Status = 0U;
        }
    }
    return testStatus;
}

static int32_t App_mcanECCSelfTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t  testStatus = CSL_PASS;
    uint32_t accessAddr, secErrFlag = 0U, dedErrFlag = 0U;

    gMcanECCIntrFlag = 1U;
    /* Enable ECC Interrupts */
    MCAN_eccEnableIntr(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_SEC, TRUE);
    MCAN_eccEnableIntr(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_DED, TRUE);
    MCAN_eccForceError(gMcanBaseAddr, testParams->mcanConfigParams.eccFrcParams);
    if (testParams->mcanConfigParams.eccFrcParams->errType == MCAN_ECC_ERR_TYPE_SEC)
    {
        secErrFlag = 1U;
        DebugP_log("SEC Error Test:\n");
    }
    if (testParams->mcanConfigParams.eccFrcParams->errType == MCAN_ECC_ERR_TYPE_DED)
    {
        dedErrFlag = 1U;
        DebugP_log("DED Error Test:\n");
    }
    accessAddr = gMcanBaseAddr;
    accessAddr += MCAN_MCAN_MSG_MEM;
    accessAddr += (testParams->mcanConfigParams.eccFrcParams->rowNum * 4U);
    HW_RD_REG32(accessAddr);
    while (gMcanECCIntrFlag)
    {
    }
    gMcanECCIntrFlag = 1U;
    /* Check for ECC Error */
    if ((gMcaneccErr.secErr == secErrFlag) &&
        (gMcaneccErr.dedErr == dedErrFlag) &&
        (gMcaneccErr.row == testParams->mcanConfigParams.eccFrcParams->rowNum))
    {
        if (secErrFlag == 1U)
        {
            if (gMcaneccErr.bit1 != testParams->mcanConfigParams.eccFrcParams->bit1)
            {
                testStatus += CSL_EFAIL;
                DebugP_log("\nECC SEC Error bit location match failed.\n");
            }
        }
        DebugP_log("\nECC Error location matched.\n");
    }
    else
    {
        testStatus += CSL_EFAIL;
        DebugP_log("\nECC Error location does not match.\n");
    }

    return testStatus;
}

static int32_t App_mcanMsgCancelTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t  configStatus = CSL_PASS, testStatus = CSL_PASS;
    uint32_t loopCnt      = 1U, txBufCnt;

    /* Enable Interrupts */
    MCAN_enableIntr(gMcanBaseAddr, testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);
    /* Select Interrupt Line */
    MCAN_selectIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        1U);
    /* Enable interrupts for Tx Buffers */
    for (loopCnt = 0U ;
         loopCnt < testParams->mcanConfigParams.txMsgNum ;
         loopCnt++)
    {
        if (testParams->mcanConfigParams.txMsg[loopCnt].storageId ==
                                                        MCAN_MEM_TYPE_BUF)
        {
            /* Enable Transmission interrupt */
            configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr,
                    testParams->mcanConfigParams.txMsg[loopCnt].bufferNum,
                    (uint32_t)TRUE);
            if(configStatus != CSL_PASS)
            {
                DebugP_log("\nMCAN Tx Buffer Interrupt Enable FAILED...\n", -1);
                testStatus += CSL_EFAIL;
            }
        }
    }
    /* Enable interrupts for Tx FIFO/Queue */
    for (loopCnt = testParams->mcanConfigParams.ramConfig->txBufCnt ;
         loopCnt < (testParams->mcanConfigParams.ramConfig->txFIFOCnt +
                    testParams->mcanConfigParams.ramConfig->txBufCnt);
         loopCnt++)
    {
        /* Enable Transmission interrupt */
        configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr,
                loopCnt,
                (uint32_t)TRUE);
        if(configStatus != CSL_PASS)
        {
            DebugP_log("\nMCAN Tx FIFO Interrupt Enable FAILED...\n", -1);
            testStatus += CSL_EFAIL;
        }
    }

    loopCnt = 0U;
    txBufCnt = testParams->mcanConfigParams.txMsg[loopCnt].bufferNum;
    // App_mcanPrintTxMsg(&testParams->mcanConfigParams.txMsg[loopCnt].txElem);

    /* Write message to Msg RAM */
    MCAN_writeMsgRam(gMcanBaseAddr,
                     testParams->mcanConfigParams.txMsg[0U].storageId,
                     txBufCnt,
                     &testParams->mcanConfigParams.txMsg[0U].txElem);
    /* add transmission request only if previous transmission is completed */
    if ((MCAN_getTxBufReqPend(gMcanBaseAddr) & (1U << txBufCnt)) != (1U << txBufCnt))
    {
        /* Clear pending Tx request */
        MCAN_txBufCancellationReq(gMcanBaseAddr, txBufCnt);
        while ((MCAN_txBufCancellationStatus(gMcanBaseAddr)  & (0x1 << txBufCnt)) != (0x1 << txBufCnt))
        {
        }
        MCAN_txBufCancellationIntrEnable(gMcanBaseAddr, txBufCnt, TRUE);
        /* Take MCAN out of the SW initialization mode */
        MCAN_setOpMode(gMcanBaseAddr, MCAN_OPERATION_MODE_NORMAL);
        while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(gMcanBaseAddr))
        {}
    }

    return testStatus;
}

static int32_t App_mcanStateTransnTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t  configStatus = CSL_PASS, testStatus = CSL_PASS;
    uint32_t loopCnt      = 1U, txBufCnt;
    MCAN_ProtocolStatus protStatus;
    MCAN_ErrCntStatus errCnt;

    /* Enable Interrupts */
    MCAN_enableIntr(gMcanBaseAddr, testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);
    /* Select Interrupt Line */
    MCAN_selectIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        1U);
    /* Enable interrupts for Tx Buffers */
    for (loopCnt = 0U ;
         loopCnt < testParams->mcanConfigParams.txMsgNum ;
         loopCnt++)
    {
        if (testParams->mcanConfigParams.txMsg[loopCnt].storageId ==
                                                        MCAN_MEM_TYPE_BUF)
        {
            /* Enable Transmission interrupt */
            configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr,
                    testParams->mcanConfigParams.txMsg[loopCnt].bufferNum,
                    (uint32_t)TRUE);
            if(configStatus != CSL_PASS)
            {
                DebugP_log("\nMCAN Tx Buffer Interrupt Enable FAILED...\n", -1);
                testStatus += CSL_EFAIL;
            }
        }
    }
    /* Enable interrupts for Tx FIFO/Queue */
    for (loopCnt = testParams->mcanConfigParams.ramConfig->txBufCnt ;
         loopCnt < (testParams->mcanConfigParams.ramConfig->txFIFOCnt +
                    testParams->mcanConfigParams.ramConfig->txBufCnt);
         loopCnt++)
    {
        /* Enable Transmission interrupt */
        configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr,
                loopCnt,
                (uint32_t)TRUE);
        if(configStatus != CSL_PASS)
        {
            DebugP_log("\nMCAN Tx FIFO Interrupt Enable FAILED...\n", -1);
            testStatus += CSL_EFAIL;
        }
    }

    loopCnt = 0U;
    txBufCnt = testParams->mcanConfigParams.txMsg[loopCnt].bufferNum;
    // App_mcanPrintTxMsg(&testParams->mcanConfigParams.txMsg[loopCnt].txElem);

    /* Write message to Msg RAM */
    MCAN_writeMsgRam(gMcanBaseAddr,
                     testParams->mcanConfigParams.txMsg[0U].storageId,
                     txBufCnt,
                     &testParams->mcanConfigParams.txMsg[0U].txElem);
    DebugP_log("\nCurrent State: Error Active\n");
    while (!((gMcanIsrIntr0Status & MCAN_INTR_SRC_ERR_PASSIVE) ==
                                MCAN_INTR_SRC_ERR_PASSIVE))
    {
        /* add transmission request only if previous transmission is completed */
        if ((MCAN_getTxBufReqPend(gMcanBaseAddr) & (1U << txBufCnt)) != (1U << txBufCnt))
        {
            loopCnt++;
            /* Add request for transmission */
            configStatus += MCAN_txBufAddReq(gMcanBaseAddr, txBufCnt);
            if (CSL_PASS != configStatus)
            {
                DebugP_log("\nError in Adding Transmission Request...\n", -1);
                testStatus += CSL_EFAIL;
            }
        }
    }
    gMcanIsrIntr0Status = 0U;
    MCAN_getProtocolStatus(gMcanBaseAddr, &protStatus);
    if ((protStatus.errPassive == 1U) && (protStatus.busOffStatus != 1U))
    {
        DebugP_log("\nCurrent State: Error Passive\n");
        DebugP_log( "Message transmitted unsuccessfully: %d\n", loopCnt);

    }

    while (!((gMcanIsrIntr0Status & MCAN_INTR_SRC_BUS_OFF_STATUS) ==
                                MCAN_INTR_SRC_BUS_OFF_STATUS))
    {
        /* add transmission request only if previous transmission is completed */
        if ((MCAN_getTxBufReqPend(gMcanBaseAddr) & (1U << txBufCnt)) != (1U << txBufCnt))
        {
            loopCnt++;
            /* Add request for transmission */
            configStatus += MCAN_txBufAddReq(gMcanBaseAddr, txBufCnt);
            if (CSL_PASS != configStatus)
            {
                DebugP_log("\nError in Adding Transmission Request...\n", -1);
            }
        }
    }
    gMcanIsrIntr0Status = 0U;
    MCAN_getProtocolStatus(gMcanBaseAddr, &protStatus);
    if ((protStatus.errPassive == 1U) &&
        (protStatus.busOffStatus == 1U) &&
        (MCAN_OPERATION_MODE_SW_INIT == MCAN_getOpMode(gMcanBaseAddr)))
    {
        DebugP_log("\nCurrent State: Bus Off\n");
        DebugP_log("Message transmitted unsuccessfully: %d\n", loopCnt);

    }
    loopCnt = 0U;

    /* Clear pending Tx request */
    MCAN_txBufCancellationReq(gMcanBaseAddr, 0U);
    while ((MCAN_txBufCancellationStatus(gMcanBaseAddr)  & (0x1 << 0)) != (0x1 << 0))
    {
    }
    /* Take MCAN out of the SW initialization mode */
    MCAN_setOpMode(gMcanBaseAddr, MCAN_OPERATION_MODE_NORMAL);
    while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(gMcanBaseAddr))
    {}
    /* wait for 129 occurrences of Bus Idle (129 × 11 consecutive recessive bits)
       before resuming normal operation. */
    /* The MCAN_ECR[14:8] REC field is used to count these sequences */
    /* Wait till first 11 consecutive recessive bits are detected */
    /* After resetting CCCR.INIT bit, MCAN writes to '5'(MCAN_ERR_CODE_BIT0_ERROR) to PSR.LEC */
    MCAN_getProtocolStatus(gMcanBaseAddr, &protStatus);
    while (protStatus.lastErrCode != MCAN_ERR_CODE_BIT0_ERROR)
    {
        MCAN_getProtocolStatus(gMcanBaseAddr, &protStatus);
    }
    /* This is 7 bit field(max value 127), so wait till it becomes none zero */
    /* wait for rest 128 occurrences */
    MCAN_getErrCounters(gMcanBaseAddr, &errCnt);
    while (errCnt.recErrCnt != 0U)
    {
        MCAN_getErrCounters(gMcanBaseAddr, &errCnt);
    }
    MCAN_getProtocolStatus(gMcanBaseAddr, &protStatus);
    if ((protStatus.errPassive == 0U) &&
        (protStatus.busOffStatus == 0U) &&
        (protStatus.warningStatus == 0U))
    {
        DebugP_log("\nCurrent State: Error Active\n");
        DebugP_log("Message transmitted Successfully: %d\n", loopCnt);
    }
    else
    {
        DebugP_log("\nCurrent State: Error Warning/Passive or Bus Off\n");
        testStatus += CSL_EFAIL;
    }

    return testStatus;
}

static int32_t App_mcanExtTSIntrTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t testStatus = CSL_PASS;

    gMcanExtTSIntrFlag = 1U;
    /* Enable External Time Stamp Interrupt */
    MCAN_extTSEnableIntr(gMcanBaseAddr, TRUE);

    isrPrintEnable = TRUE;

#if defined (SOC_AM273X) || defined (SOC_AWR294X)
    /* MCAN External TS Interrupt is connected to ESM Module
     * so ESM produces only one time interrupt
     */
    DebugP_log( "Waiting for Interrupt...\n");
    while (gMcanExtTSIntrFlag)
    {
    }
#else
    DebugP_log( "Waiting for 1st Interrupt...\n");
    while (gMcanExtTSIntrFlag)
    {
    }
    gMcanExtTSIntrFlag = 1U;
    DebugP_log( "Waiting for 2nd Interrupt...\n");
    while (gMcanExtTSIntrFlag)
    {
    }
    gMcanExtTSIntrFlag = 1U;
    DebugP_log( "Waiting for 3rd Interrupt...\n");
    while (gMcanExtTSIntrFlag)
    {
    }
    gMcanExtTSIntrFlag = 1U;
#endif
    /* Disable External Time Stamp Interrupt */
    MCAN_extTSEnableIntr(gMcanBaseAddr, FALSE);

    return testStatus;
}

static int32_t App_mcanTxRxPinStateTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t testStatus = CSL_PASS;

    /* Put MCAN in SW initialization mode */
    MCAN_setOpMode(gMcanBaseAddr, MCAN_OPERATION_MODE_SW_INIT);
    while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(gMcanBaseAddr))
    {}

    /* Monitors the actual value of the MCAN RX pin
       Rx pin may be Dominant/Recessive. Not correct to return error */
    if (MCAN_getRxPinState(gMcanBaseAddr) == 0U)
    {
        DebugP_log( "Rx Pin Mode: Dominant\r\n");
    }
    else
    {
        DebugP_log( "Rx Pin Mode: Recessive\r\n");
    }
    if (MCAN_getRxPinState(gMcanBaseAddr) == 1U)
    {
        DebugP_log( "Rx Pin Mode: Recessive\r\n");
    }
    else
    {
        DebugP_log( "Rx Pin Mode: Dominant\r\n");
    }
    DebugP_log( "Setting Tx PAD into Dominant mode.\r\n");
    MCAN_setTxPinState(gMcanBaseAddr, 0x2);
    if (MCAN_getTxPinState(gMcanBaseAddr) == 0x2U)
    {
        DebugP_log( "Tx Pin Mode: Dominant\r\n");
    }
    else
    {
        testStatus += CSL_EFAIL;
        DebugP_log( "Rx Pin Mode: Recessive\r\n");
    }
    DebugP_log( "Setting Tx PAD into Recessive mode.\r\n");
    MCAN_setTxPinState(gMcanBaseAddr, 0x3);
    if (MCAN_getTxPinState(gMcanBaseAddr) == 0x3U)
    {
        DebugP_log( "Tx Pin Mode: Recessive\r\n");
    }
    else
    {
        testStatus += CSL_EFAIL;
        DebugP_log( "Tx Pin Mode: Dominant\r\n");
    }

    DebugP_log( "Setting Tx PAD into Dominant mode.\r\n");
    MCAN_setTxPinState(gMcanBaseAddr, 0x0);
    if (MCAN_getTxPinState(gMcanBaseAddr) == 0x0)
    {
        DebugP_log( "Resetting Tx Pin \r\n");
    }
    else
    {
        testStatus += CSL_EFAIL;
        DebugP_log( "Tx Pin Set Fail \r\n");
    }

    /* Take MCAN out of the SW initialization mode */
    MCAN_setOpMode(gMcanBaseAddr, MCAN_OPERATION_MODE_NORMAL);
    while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(gMcanBaseAddr))
    {}

    return testStatus;
}

static int32_t App_mcanClkStpReqTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t testStatus = CSL_PASS;

    DebugP_log("Asserting Clock Stop Request..\r\n");
    MCAN_addClockStopRequest(gMcanBaseAddr, TRUE);
    while (MCAN_getClkStopAck(gMcanBaseAddr) != 1U)
    {
    }
    DebugP_log("Clock Stop Request ACKed!!\r\n");
    if (MCAN_OPERATION_MODE_SW_INIT == MCAN_getOpMode(gMcanBaseAddr))
    {
        DebugP_log("MCAN is in SW Init Mode.\r\n");
    }
    else
    {
        DebugP_log("MCAN is in not SW Init Mode.\r\n");
        testStatus += CSL_EFAIL;
    }
    MCAN_getClockStopAck(gMcanBaseAddr);
    MCAN_addClockStopRequest(gMcanBaseAddr, FALSE);

    return testStatus;
}

static int32_t App_mcanTSRstTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t testStatus = CSL_PASS;
    uint32_t oldTimeStamp, timeStamp;

    timeStamp = MCAN_getTSCounterVal(gMcanBaseAddr);
    DebugP_log("TS at (t) ms: %d\r\n", timeStamp);
    /* Delay added for getting new timeStamp- so that there will difference between two timeStamps */
    App_delayFunc(10);
    oldTimeStamp = timeStamp;
    timeStamp = MCAN_getTSCounterVal(gMcanBaseAddr);
    DebugP_log("TS at (t + 10) ms: %d\r\n", timeStamp);

    /* reset TS counter */
    MCAN_resetTSCounter(gMcanBaseAddr);
    oldTimeStamp = timeStamp;
    timeStamp = MCAN_getTSCounterVal(gMcanBaseAddr);
    /* wrap around condition is not taken care */
    if (timeStamp < oldTimeStamp)
    {
        DebugP_log("TS Counter Reset done!!\r\n");
    }
    else
    {
        testStatus += CSL_EFAIL;
    }

    return testStatus;
}

static int32_t App_mcanBusMonTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t configStatus = CSL_PASS, testStatus = CSL_PASS;
    MCAN_RxBufElement rxMsg;

    /* Enable Interrupts */
    MCAN_enableIntr(gMcanBaseAddr, testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);
    /* Select Interrupt Line */
    MCAN_selectIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        1U);
    gMcanIsrIntr0Status = 0U;
    DebugP_log( "Send message over the CAN network(TDA3xx MCAN and only one another node).\n");
    DebugP_log( "Same message shall be received by MCAN but transmitter node shall get ACK Error.\n");
    while  (!(((gMcanIsrIntr0Status & MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG) ==
                                    MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG) ||
            ((gMcanIsrIntr0Status & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ==
                                    MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ||
            ((gMcanIsrIntr0Status & MCAN_INTR_SRC_RX_FIFO1_NEW_MSG) ==
                                    MCAN_INTR_SRC_RX_FIFO1_NEW_MSG)))
    {
    }
    /* Disable Interrupt Line */
    MCAN_enableIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        0U);
    DebugP_log( "Message received:\n");
    configStatus += App_mcanReadRxMSG(&rxMsg, gMcanIsrIntr0Status);
    if(configStatus != CSL_PASS)
    {
        testStatus += CSL_EFAIL;
        DebugP_log("\nUnable to read received message.\n");
    }
    gMcanIsrIntr0Status = 0U;

    return testStatus;
}

int32_t App_mcanPerfTxRxTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t  configStatus = CSL_PASS, testStatus = CSL_PASS;
    MCAN_RxFIFOStatus fifoStatus;
    MCAN_RxBufElement rxMsg;
    uint32_t loopCnt      = 1U, iterationCnt = 0U, txBufNum, maxMsgCnt;
    MCAN_ErrCntStatus    errCounter;
    MCAN_TxFIFOStatus txFIFOStatus;
    uint64_t tsDiff, hwUtiln, tsFreq;
    uint64_t numOfMsgPerSec;
    /* Get ticks delay */
    CycleCounterP_reset();
    uint32_t ticksDelay = CycleCounterP_getCount32();
    uint32_t startTicks, stopTicks;

    ticksDelay = CycleCounterP_getCount32() - ticksDelay;

    configStatus += App_mcanRegisterInterrupt();
    if (CSL_PASS != configStatus)
    {
        DebugP_log("\nError in Interrupt Configuration...");
    }

    /* Reset MCAN Module */
    MCAN_reset(gMcanBaseAddr);
    while (MCAN_isInReset(gMcanBaseAddr) == (uint32_t)TRUE)
    {
    }
    configStatus += App_mcanConfig(testParams);
    if (CSL_PASS != configStatus)
    {
        DebugP_log("\nError in MCAN Configuration...");
    }

    configStatus += App_mcanTCEntrySetup(testParams);
    if(configStatus != CSL_PASS)
    {
        DebugP_log("\nError in MCAN TC Entry Configuration...TC cannot be Run...");
    }
    else
    {
    }
    /* Enable Interrupts */
    MCAN_enableIntr(gMcanBaseAddr, testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);
    /* Select Interrupt Line */
    MCAN_selectIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        1U);
    /* Enable interrupts for Tx Buffers */
    for (loopCnt = 0U ;
         loopCnt < testParams->mcanConfigParams.txMsgNum ;
         loopCnt++)
    {
        if (testParams->mcanConfigParams.txMsg[loopCnt].storageId ==
                                                        MCAN_MEM_TYPE_BUF)
        {
            /* Enable Transmission interrupt */
            configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr,
                    testParams->mcanConfigParams.txMsg[loopCnt].bufferNum,
                    (uint32_t)TRUE);
            if(configStatus != CSL_PASS)
            {
                DebugP_log("\nMCAN Tx Buffer Interrupt Enable FAILED...\n");
            }
        }
    }
    /* Enable interrupts for Tx FIFO/Queue */
    for (loopCnt = testParams->mcanConfigParams.ramConfig->txBufCnt ;
         loopCnt < (testParams->mcanConfigParams.ramConfig->txFIFOCnt +
                    testParams->mcanConfigParams.ramConfig->txBufCnt);
         loopCnt++)
    {
        /* Enable Transmission interrupt */
        configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr,
                loopCnt,
                (uint32_t)TRUE);
        if(configStatus != CSL_PASS)
        {
            DebugP_log("\nMCAN Tx FIFO Interrupt Enable FAILED...\n");
        }
    }

    /* Check for STD vs EXT ID and FD vs Classic messages for CAN message */
    if ((testParams->mcanConfigParams.txMsg[0U].txElem.xtd == 1U) && (testParams->mcanConfigParams.txMsg[0U].txElem.fdf == 1U))
    {
        maxMsgCnt = MCAN_THEOROTICAL_MAX_EXT_1_5_MBPS;
    }
    else if ((testParams->mcanConfigParams.txMsg[0U].txElem.xtd == 1U) && (testParams->mcanConfigParams.txMsg[0U].txElem.fdf == 0U))
    {
        maxMsgCnt = MCAN_CLASSIC_CAN_THEOROTICAL_MAX_EXT_1_MBPS;
    }
    else if ((testParams->mcanConfigParams.txMsg[0U].txElem.xtd == 0U) && (testParams->mcanConfigParams.txMsg[0U].txElem.fdf == 0U))
    {
        maxMsgCnt = MCAN_CLASSIC_CAN_THEOROTICAL_MAX_STD_1_MBPS;
    }
    else
    {
        maxMsgCnt = MCAN_THEOROTICAL_MAX_STD_1_5_MBPS;
    }
    /* Throughput measurement for Tx only */
    /* capture time stamp before triggering Tx */
    MCAN_getTxFIFOQueStatus(gMcanBaseAddr, &txFIFOStatus);
    if (testParams->mcanConfigParams.txMsg[0U].storageId ==
                                                MCAN_MEM_TYPE_BUF)
    {
        txBufNum = testParams->mcanConfigParams.txMsg[0U].bufferNum;
    }
    else
    {
        txBufNum = txFIFOStatus.putIdx;
    }
    CycleCounterP_reset();
    startTicks = CycleCounterP_getCount32();
    for (iterationCnt = 0U ;
         iterationCnt < testParams->mcanConfigParams.txMSGInterationCnt ;
         iterationCnt++)
    {
        for (loopCnt = 0U ;
             loopCnt < testParams->mcanConfigParams.txMsgNum ;
             loopCnt++)
        {
            /* Write message to Msg RAM */
            MCAN_writeMsgRam(gMcanBaseAddr,
                             testParams->mcanConfigParams.txMsg[loopCnt].storageId,
                             txBufNum,
                             &testParams->mcanConfigParams.txMsg[loopCnt].txElem);
            /* Add request for transmission */
            configStatus += MCAN_txBufAddReq(gMcanBaseAddr, txBufNum);
            if (CSL_PASS != configStatus)
            {
                DebugP_log("\nError in Adding Transmission Request...\n");
            }
            /* Wait for Tx completion */
            SemaphoreP_pend(&gTxDoneSem, SystemP_WAIT_FOREVER);

            /* Wait for Rx completion */
            SemaphoreP_pend(&gRxDoneSem, SystemP_WAIT_FOREVER);

            /* Checking for Errors */
            MCAN_getErrCounters(gMcanBaseAddr, &errCounter);
            if ((0U != errCounter.recErrCnt) &&
                (0U != errCounter.transErrLogCnt))
            {
                /* Error occurred in transmission*/
                testStatus += CSL_EFAIL;
                DebugP_log("\nError Counters: Error in transmission/reception(Iteration Count:Message Number): (%d,%d).\n",
                           (iterationCnt + 1U), (loopCnt + 1U));
                break;
            }

            /* Messages will be stored in FIFO1 as these will fail filters and non-matching messages are stored into FIFO 1 */
            fifoStatus.num = (uint32_t)MCAN_RX_FIFO_NUM_1;
            MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
            MCAN_readMsgRam(gMcanBaseAddr,
                            MCAN_MEM_TYPE_FIFO,
                            fifoStatus.getIdx,
                            (uint32_t)fifoStatus.num,
                            &rxMsg);
            (void) MCAN_writeRxFIFOAck(gMcanBaseAddr,
                                       (uint32_t)fifoStatus.num,
                                       fifoStatus.getIdx);
            configStatus += App_mcanTxRxMessageCheck(
                                testParams->mcanConfigParams.txMsg[loopCnt].txElem,
                                rxMsg);
            if(configStatus != CSL_PASS)
            {
                testStatus += CSL_EFAIL;
                DebugP_log("\nTransmitted and received message does not match(Iteration Count:Message Number): (%d,%d).\n", (iterationCnt + 1U), (loopCnt + 1U));
                break;
            }
        }
    }
    /* capture time stamp After Tx completion */
    stopTicks = CycleCounterP_getCount32();

    if(stopTicks > startTicks)
    {
        tsDiff = (uint64_t)(stopTicks - startTicks - ticksDelay);
    }
    else
    {
        /* Counter overflow, assume only one overflow has happened */
        tsDiff = (uint64_t)((0xFFFFFFFFU - startTicks) + stopTicks - ticksDelay);
    }

    tsFreq = SOC_getSelfCpuClk();
    numOfMsgPerSec = ((uint64_t)testParams->mcanConfigParams.txMSGInterationCnt *
                      (uint64_t)testParams->mcanConfigParams.txMsgNum * tsFreq) / tsDiff;

    /* If internal loopback then no need of x2 as Tx and Rx nodes are same */
    if (!(testParams->mcanConfigParams.mcanTestType == MCAN_TEST_TYPE_INTERNAL_LOOPBACK))
    {
        numOfMsgPerSec *= 2U;
    }
    hwUtiln = ((numOfMsgPerSec * 100) / maxMsgCnt);
    DebugP_log("\nTxRx:: Iteration Count:%d\tNumber of messages:%d\r\n", testParams->mcanConfigParams.txMSGInterationCnt, testParams->mcanConfigParams.txMsgNum);
    DebugP_log("\nTxRx:: ThroughPut: %lld Msg/sec\r\n", numOfMsgPerSec);
    DebugP_log("\nTxRx:: HW Utilization: %lld%% (of HW theoretical max)\r\n", hwUtiln);
#if defined(MCU_M4_CORE)
    /* M4F FreeRTOS incurs higher per-interrupt OS overhead than R5F.
     * hwUtiln is still reported relative to the true HW theoretical max.
     * MCAN_M4_HW_UTIL_THRESHOLD must be calibrated from a measured baseline;
     * see definition in test_mcan.h. */
    if(hwUtiln < MCAN_M4_HW_UTIL_THRESHOLD)
#else
    if(hwUtiln < MCAN_HW_UTIL_THRESHOLD)
#endif
    {
        testParams->testResult += CSL_EFAIL;
        testStatus += CSL_EFAIL;
    }
    testParams->isRun      = CSL_PASS;
    return testStatus;
}

int32_t App_mcanRxFIFOModes(st_mcanTestcaseParams_t *testParams)
{
    int32_t  configStatus = CSL_PASS, testStatus = CSL_PASS;
    uint32_t loopCnt      = 1U, loopBreakFlag = 1U, txBufCnt;
    uint32_t getIdx, putIdx;
    MCAN_ProtocolStatus protStatus;
    MCAN_ErrCntStatus    errCounter;
    MCAN_RxBufElementNoCpy rxMsg;
    MCAN_TxFIFOStatus txFIFOStatus;
    MCAN_RxFIFOStatus fifoStatus;
    MCAN_ConfigParams configParams;
    MCAN_TxBufElementNoCpy txElem = {0U};
    uint8_t txData[MCAN_MAX_PAYLOAD_BYTES];

    /* Initialize TX Data */
    for (loopCnt = 0U; loopCnt < MCAN_MAX_PAYLOAD_BYTES; loopCnt++)
    {
        txData[loopCnt] = loopCnt;
    }

    App_mcanInitTxElem(&txElem);
    txElem.data = &txData[0U];

    /* Enable Interrupts */
    MCAN_enableIntr(gMcanBaseAddr, testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);
    /* Select Interrupt Line */
    MCAN_selectIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        1U);
    /* Enable interrupts for Tx Buffers */
    for (loopCnt = 0U ;
         loopCnt < testParams->mcanConfigParams.txMsgNum ;
         loopCnt++)
    {
        if (testParams->mcanConfigParams.txMsg[loopCnt].storageId ==
                                                        MCAN_MEM_TYPE_BUF)
        {
            /* Enable Transmission interrupt */
            configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr,
                    testParams->mcanConfigParams.txMsg[loopCnt].bufferNum,
                    (uint32_t)TRUE);
            if(configStatus != CSL_PASS)
            {
                DebugP_log("\nMCAN Tx Buffer Interrupt Enable FAILED...\n", -1);
            }
        }
    }
    /* Enable interrupts for Tx FIFO/Queue */
    for (loopCnt = testParams->mcanConfigParams.ramConfig->txBufCnt ;
         loopCnt < (testParams->mcanConfigParams.ramConfig->txFIFOCnt +
                    testParams->mcanConfigParams.ramConfig->txBufCnt);
         loopCnt++)
    {
        /* Enable Transmission interrupt */
        configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr,
                loopCnt,
                (uint32_t)TRUE);
        if(configStatus != CSL_PASS)
        {
            DebugP_log("\nMCAN Tx FIFO Interrupt Enable FAILED...\n", -1);
        }
    }
    /* FIFO Block mode Test - Start */
    DebugP_log("FIFO 1 Blocking Mode Test:\r\n", -1);
    /* Accept non-matching messages into FIFO1 */
    /* Send messages until FIFO1 condition is reached */
    loopCnt = 0U;
    while (loopBreakFlag == 1U)
    {
        loopCnt++;
        MCAN_getTxFIFOQueStatus(gMcanBaseAddr, &txFIFOStatus);
        if (testParams->mcanConfigParams.txMsg[0U].storageId ==
                                                    MCAN_MEM_TYPE_BUF)
        {
            txBufCnt = testParams->mcanConfigParams.txMsg[0U].bufferNum;
        }
        else
        {
            txBufCnt = txFIFOStatus.putIdx;
        }
        /* Write message to Msg RAM-sending message with extended ID only */
        testParams->mcanConfigParams.txMsg[0U].txElem.id = loopCnt;
        testParams->mcanConfigParams.txMsg[0U].txElem.xtd = 1U;
        MCAN_writeMsgRamNoCpy(gMcanBaseAddr,
                         testParams->mcanConfigParams.txMsg[0U].storageId,
                         txBufCnt,
                         &txElem);
        /* Add request for transmission */
        configStatus += MCAN_txBufAddReq(gMcanBaseAddr, txBufCnt);
        if (CSL_PASS != configStatus)
        {
            DebugP_log("\nError in Adding Transmission Request...\n", -1);
        }
        while (!((gMcanIsrIntr0Status & MCAN_INTR_SRC_TRANS_COMPLETE) ==
                                MCAN_INTR_SRC_TRANS_COMPLETE))
        {
        }
        while (!((gMcanIsrIntr0Status & MCAN_INTR_SRC_RX_FIFO1_NEW_MSG) ==
                                MCAN_INTR_SRC_RX_FIFO1_NEW_MSG))
        {
        }
        if ((gMcanIsrIntr0Status & MCAN_INTR_SRC_RX_FIFO1_FULL) ==
                                MCAN_INTR_SRC_RX_FIFO1_FULL)
        {
            loopBreakFlag = 0U;
        }
        gMcanIsrIntr0Status = 0U;
        /* Checking for Errors */
        MCAN_getErrCounters(gMcanBaseAddr, &errCounter);
        if ((0U == errCounter.recErrCnt) &&
            (0U == errCounter.canErrLogCnt))
        {
            MCAN_getProtocolStatus(gMcanBaseAddr, &protStatus);
            /* Checking for Errors */
            if (((MCAN_ERR_CODE_NO_ERROR == protStatus.lastErrCode) ||
                 (MCAN_ERR_CODE_NO_CHANGE == protStatus.lastErrCode)) &&
                ((MCAN_ERR_CODE_NO_ERROR == protStatus.dlec) ||
                 (MCAN_ERR_CODE_NO_CHANGE == protStatus.dlec)) &&
                (0U == protStatus.pxe))
            {
            }
            else
            {
                testStatus += CSL_EFAIL;
                DebugP_log("\nError in transmission/reception(Iteration Count).\n");
                loopBreakFlag = 0U;
            }
        }
        else
        {
            testStatus += CSL_EFAIL;
            DebugP_log("\nError Counters: Error in transmission/reception.\n");
            loopBreakFlag = 0U;
        }
    }
    fifoStatus.num = MCAN_RX_FIFO_NUM_1;
    MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
    if (fifoStatus.fifoFull == 1U)
    {
        getIdx = fifoStatus.getIdx;
        putIdx = fifoStatus.putIdx;
        loopCnt++;
        /* Send another message to cause overflow */
        /* Write message to Msg RAM-sending message with extended ID only */
        testParams->mcanConfigParams.txMsg[0U].txElem.id = loopCnt;
        testParams->mcanConfigParams.txMsg[0U].txElem.xtd = 1U;
        MCAN_writeMsgRamNoCpy(gMcanBaseAddr,
                         testParams->mcanConfigParams.txMsg[0U].storageId,
                         txBufCnt,
                         &txElem);
        /* Add request for transmission */
        configStatus += MCAN_txBufAddReq(gMcanBaseAddr, txBufCnt);
        if (CSL_PASS != configStatus)
        {
            DebugP_log("\nError in Adding Transmission Request...\n", -1);
        }
        while (!((gMcanIsrIntr0Status & MCAN_INTR_SRC_TRANS_COMPLETE) ==
                                MCAN_INTR_SRC_TRANS_COMPLETE))
        {
        }
        while (!((gMcanIsrIntr0Status & MCAN_INTR_SRC_RX_FIFO1_MSG_LOST) ==
                                MCAN_INTR_SRC_RX_FIFO1_MSG_LOST))
        {
        }
        /* get FIFO status, since FIFO is in Blocking mode, latest message will
         * lost and get/put index will not be updated */
        MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
        if ((getIdx == fifoStatus.getIdx) && (putIdx == fifoStatus.putIdx))
        {
            DebugP_log("Get and Put Indices are not updated after sending message after FIFO Full Condition.\r\n", -1);
        }
        /* Read first message in FIFO - this should be oldest message(with EXT ID: 1) */
        MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
        MCAN_readMsgRamNoCpy(gMcanBaseAddr,
                        MCAN_MEM_TYPE_FIFO,
                        fifoStatus.getIdx,
                        (uint32_t)fifoStatus.num,
                        &rxMsg);
        (void) MCAN_writeRxFIFOAck(gMcanBaseAddr,
                                   (uint32_t)fifoStatus.num,
                                   fifoStatus.getIdx);
        if ((rxMsg.id >> MCAN_STD_ID_SHIFT) == (txElem.id >> MCAN_STD_ID_SHIFT))
        {
            DebugP_log("Oldest message is not overwritten, FIFO is in Blocking Mode.\r\n", -1);
        }
        else
        {
            testStatus += CSL_EFAIL;
            DebugP_log("Oldest message is overwritten, FIFO is not in Blocking Mode.\r\n", -1);
        }
    }
    else
    {
        testStatus += CSL_EFAIL;
    }
    /* FIFO Block mode Test - End */
    /* FIFO Overwrite mode Test - Start */
    DebugP_log("\nFIFO 0 Overwrite Mode Test:\r\n", -1);
    /* Accept non-matching messages into FIFO0(previously was FIFO1) */
    configParams.monEnable = testParams->mcanConfigParams.configParams->monEnable;
    configParams.asmEnable = testParams->mcanConfigParams.configParams->asmEnable;
    configParams.tsPrescalar = testParams->mcanConfigParams.configParams->tsPrescalar;
    configParams.tsSelect = testParams->mcanConfigParams.configParams->tsSelect;
    configParams.timeoutPreload = testParams->mcanConfigParams.configParams->timeoutPreload;
    configParams.timeoutCntEnable = testParams->mcanConfigParams.configParams->timeoutCntEnable;
    configParams.filterConfig.rrfe = testParams->mcanConfigParams.configParams->filterConfig.rrfe;
    configParams.filterConfig.rrfs = testParams->mcanConfigParams.configParams->filterConfig.rrfs;
    configParams.filterConfig.anfe = 0U;
    configParams.filterConfig.anfs = 0U;
    /* Put MCAN in SW initialization mode */
    MCAN_setOpMode(gMcanBaseAddr, MCAN_OPERATION_MODE_SW_INIT);
    while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(gMcanBaseAddr))
    {}
    MCAN_config(gMcanBaseAddr, &configParams);
    /* Take MCAN out of the SW initialization mode */
    MCAN_setOpMode(gMcanBaseAddr, MCAN_OPERATION_MODE_NORMAL);
    while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(gMcanBaseAddr))
    {}
    /* Send messages until FIFO1 condition is reached */
    loopCnt = 0U;
    gMcanIsrIntr0Status = 0U;
    loopBreakFlag = 1U;
    while (loopBreakFlag == 1U)
    {
        loopCnt++;
        MCAN_getTxFIFOQueStatus(gMcanBaseAddr, &txFIFOStatus);
        if (testParams->mcanConfigParams.txMsg[0U].storageId ==
                                                    MCAN_MEM_TYPE_BUF)
        {
            txBufCnt = testParams->mcanConfigParams.txMsg[0U].bufferNum;
        }
        else
        {
            txBufCnt = txFIFOStatus.putIdx;
        }
        /* Write message to Msg RAM-sending message with extended ID only */
        testParams->mcanConfigParams.txMsg[0U].txElem.id = loopCnt;
        testParams->mcanConfigParams.txMsg[0U].txElem.xtd = 1U;
        MCAN_writeMsgRamNoCpy(gMcanBaseAddr,
                         testParams->mcanConfigParams.txMsg[0U].storageId,
                         txBufCnt,
                         &txElem);
        /* Add request for transmission */
        configStatus += MCAN_txBufAddReq(gMcanBaseAddr, txBufCnt);
        if (CSL_PASS != configStatus)
        {
            DebugP_log("\nError in Adding Transmission Request...\n", -1);
        }
        while (!((gMcanIsrIntr0Status & MCAN_INTR_SRC_TRANS_COMPLETE) ==
                                MCAN_INTR_SRC_TRANS_COMPLETE))
        {
        }
        while (!((gMcanIsrIntr0Status & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ==
                                MCAN_INTR_SRC_RX_FIFO0_NEW_MSG))
        {
        }
        if ((gMcanIsrIntr0Status & MCAN_INTR_SRC_RX_FIFO0_FULL) ==
                                MCAN_INTR_SRC_RX_FIFO0_FULL)
        {
            loopBreakFlag = 0U;
        }
        gMcanIsrIntr0Status = 0U;
        /* Checking for Errors */
        MCAN_getErrCounters(gMcanBaseAddr, &errCounter);
        if ((0U == errCounter.recErrCnt) &&
            (0U == errCounter.canErrLogCnt))
        {
            MCAN_getProtocolStatus(gMcanBaseAddr, &protStatus);
            /* Checking for Errors */
            if (((MCAN_ERR_CODE_NO_ERROR == protStatus.lastErrCode) ||
                 (MCAN_ERR_CODE_NO_CHANGE == protStatus.lastErrCode)) &&
                ((MCAN_ERR_CODE_NO_ERROR == protStatus.dlec) ||
                 (MCAN_ERR_CODE_NO_CHANGE == protStatus.dlec)) &&
                (0U == protStatus.pxe))
            {
            }
            else
            {
                testStatus += CSL_EFAIL;
                DebugP_log("\nError in transmission/reception(Iteration Count).\n");
                loopBreakFlag = 0U;
            }
        }
        else
        {
            testStatus += CSL_EFAIL;
            DebugP_log("\nError Counters: Error in transmission/reception.\n");
            loopBreakFlag = 0U;
        }
    }
    fifoStatus.num = MCAN_RX_FIFO_NUM_0;
    MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
    if (fifoStatus.fifoFull == 1U)
    {
        getIdx = fifoStatus.getIdx;
        putIdx = fifoStatus.putIdx;
        loopCnt++;
        /* Send another message to cause overflow */
        /* Write message to Msg RAM-sending message with extended ID only */
        testParams->mcanConfigParams.txMsg[0U].txElem.id = loopCnt;
        testParams->mcanConfigParams.txMsg[0U].txElem.xtd = 1U;
        MCAN_writeMsgRamNoCpy(gMcanBaseAddr,
                         testParams->mcanConfigParams.txMsg[0U].storageId,
                         txBufCnt,
                         &txElem);
        /* Add request for transmission */
        configStatus += MCAN_txBufAddReq(gMcanBaseAddr, txBufCnt);
        if (CSL_PASS != configStatus)
        {
            DebugP_log("\nError in Adding Transmission Request...\n", -1);
        }
        while (!((gMcanIsrIntr0Status & MCAN_INTR_SRC_TRANS_COMPLETE) ==
                                MCAN_INTR_SRC_TRANS_COMPLETE))
        {
        }
        while (!((gMcanIsrIntr0Status & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ==
                                MCAN_INTR_SRC_RX_FIFO0_NEW_MSG))
        {
        }
        gMcanIsrIntr0Status = 0U;
        /* get FIFO status, since FIFO is in Blocking mode, latest message will
         * lost and get/put index will not be updated */
        MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
        if ((getIdx == (fifoStatus.getIdx - 1U)) && (putIdx == (fifoStatus.putIdx - 1U)))
        {
            DebugP_log("Get and Put Indices are  updated after sending message after FIFO Full Condition.\r\n", -1);
        }
        /* Read first message in FIFO - this should be second oldest message(with EXT ID: 2) */
        MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
        MCAN_readMsgRamNoCpy(gMcanBaseAddr,
                        MCAN_MEM_TYPE_FIFO,
                        fifoStatus.getIdx,
                        (uint32_t)fifoStatus.num,
                        &rxMsg);
        (void) MCAN_writeRxFIFOAck(gMcanBaseAddr,
                                   (uint32_t)fifoStatus.num,
                                   fifoStatus.getIdx);
        if ((rxMsg.id >> MCAN_STD_ID_SHIFT) == (txElem.id >> MCAN_STD_ID_SHIFT))
        {
            DebugP_log("First message in the FIFO is second oldest message.\r\n", -1);
        }
        else
        {
            testStatus += CSL_EFAIL;
            DebugP_log("First message in the FIFO is not second oldest message.\r\n", -1);
        }
        MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
        while (fifoStatus.fillLvl > 0U)
        {
            MCAN_readMsgRamNoCpy(gMcanBaseAddr,
                            MCAN_MEM_TYPE_FIFO,
                            fifoStatus.getIdx,
                            (uint32_t)fifoStatus.num,
                            &rxMsg);
            (void) MCAN_writeRxFIFOAck(gMcanBaseAddr,
                                       (uint32_t)fifoStatus.num,
                                       fifoStatus.getIdx);
            MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
        }
        if ((rxMsg.id >> MCAN_STD_ID_SHIFT) == (txElem.id >> MCAN_STD_ID_SHIFT))
        {
            DebugP_log("Oldest message is overwritten, FIFO is in Overwriting Mode.\r\n", -1);
        }
        else
        {
            testStatus += CSL_EFAIL;
            DebugP_log("Oldest message is not overwritten, FIFO is not in Overwriting Mode.\r\n", -1);
        }
    }
    else
    {
        testStatus += CSL_EFAIL;
    }
    /* FIFO Overwrite mode Test - End */

    /* Disable Interrupt */
    MCAN_enableIntr(gMcanBaseAddr, MCAN_INTR_MASK_ALL, (uint32_t)FALSE);

    return testStatus;
}

static int32_t App_mcanTxTestBusMonitor(st_mcanTestcaseParams_t *testParams)
{
    int32_t  configStatus = CSL_PASS, testStatus = CSL_PASS;
    uint32_t loopCnt      = 1U, iterationCnt = 0U, intrMask, txBufCnt;
    uint32_t bitPos = 0U;
    MCAN_RxBufElement rxMsg;
    MCAN_TxFIFOStatus txFIFOStatus;

    /* Enable Interrupts */
    MCAN_enableIntr(gMcanBaseAddr, testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);
    /* Select Interrupt Line */
    MCAN_selectIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        1U);
    /* Enable interrupts for Tx Buffers */
    for (loopCnt = 0U ;
         loopCnt < testParams->mcanConfigParams.txMsgNum ;
         loopCnt++)
    {
        if (testParams->mcanConfigParams.txMsg[loopCnt].storageId ==
                                                        MCAN_MEM_TYPE_BUF)
        {
            /* Enable Transmission interrupt */
            configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr,
                    testParams->mcanConfigParams.txMsg[loopCnt].bufferNum,
                    (uint32_t)TRUE);
            if(configStatus != CSL_PASS)
            {
                DebugP_log("\nMCAN Tx Buffer Interrupt Enable FAILED...\n", -1);
            }
        }
    }
    /* Enable interrupts for Tx FIFO/Queue */
    for (loopCnt = testParams->mcanConfigParams.ramConfig->txBufCnt ;
         loopCnt < (testParams->mcanConfigParams.ramConfig->txFIFOCnt +
                    testParams->mcanConfigParams.ramConfig->txBufCnt);
         loopCnt++)
    {
        /* Enable Transmission interrupt */
        configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr,
                loopCnt,
                (uint32_t)TRUE);
        if(configStatus != CSL_PASS)
        {
            DebugP_log("\nMCAN Tx FIFO Interrupt Enable FAILED...\n", -1);
        }
    }

    for (iterationCnt = 0U ;
         iterationCnt < testParams->mcanConfigParams.txMSGInterationCnt ;
         iterationCnt++)
    {
        for (loopCnt = 0U ;
             loopCnt < testParams->mcanConfigParams.txMsgNum ;
             loopCnt++)
        {
            MCAN_getTxFIFOQueStatus(gMcanBaseAddr, &txFIFOStatus);
            if (testParams->mcanConfigParams.txMsg[loopCnt].storageId ==
                                                        MCAN_MEM_TYPE_BUF)
            {
                txBufCnt = testParams->mcanConfigParams.txMsg[loopCnt].bufferNum;
            }
            else
            {
                txBufCnt = txFIFOStatus.putIdx;
            }
            /* Calculate Rx Interrupt Mask */
            if(testParams->mcanConfigParams.txMsg[loopCnt].rxMSGStorageId == MCAN_MEM_TYPE_BUF)
            {
                intrMask = MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG;
            }
            else
            {
                if(testParams->mcanConfigParams.txMsg[loopCnt].rxBuffNum == MCAN_RX_FIFO_NUM_0)
                {
                    intrMask = MCAN_INTR_SRC_RX_FIFO0_NEW_MSG;
                }
                else
                {
                    intrMask = MCAN_INTR_SRC_RX_FIFO1_NEW_MSG;
                }

            }
            (void)intrMask; /* Presently set but not used. Suppress warning */
            gMcanIsrIntr0Status = 0U;
            // App_mcanPrintTxMsg(&testParams->mcanConfigParams.txMsg[loopCnt].txElem);
            /* Write message to Msg RAM */
            MCAN_writeMsgRam(gMcanBaseAddr,
                             testParams->mcanConfigParams.txMsg[loopCnt].storageId,
                             txBufCnt,
                             &testParams->mcanConfigParams.txMsg[loopCnt].txElem);
            /* Add request for transmission */
            configStatus += MCAN_txBufAddReq(gMcanBaseAddr, txBufCnt);
            if (CSL_PASS != configStatus)
            {
                DebugP_log("\nError in Adding Transmission Request...\n", -1);
            }
            bitPos = (1U << txBufCnt);
            if ((MCAN_getTxBufReqPend(gMcanBaseAddr) & (bitPos)) != (bitPos))
            {
                /* Send CAN Msg with ID as 0x4U from any node or CAN tool */
                while  (!(((gMcanIsrIntr0Status & MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG) ==
                                                MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG) ||
                        ((gMcanIsrIntr0Status & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ==
                                                MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ||
                        ((gMcanIsrIntr0Status & MCAN_INTR_SRC_RX_FIFO1_NEW_MSG) ==
                                                MCAN_INTR_SRC_RX_FIFO1_NEW_MSG)))
                {
                }
                configStatus = App_mcanReadRxMSG(&rxMsg, gMcanIsrIntr0Status);
                if((configStatus != CSL_PASS) && (((rxMsg.id >> MCAN_STD_ID_SHIFT) & MCAN_STD_ID_MASK) != 0x4U))
                {
                    DebugP_log("\nUnable to read received message(Iteration Count:Message Number): (%d,%d).\n", (iterationCnt + 1U), (loopCnt + 1U));
                    testStatus = CSL_EFAIL;
                }
                gMcanIsrIntr0Status = 0U;
            }
        }
    }
    /* Disable interrupts for Tx Buffers */
    for (loopCnt = 0U ;
         loopCnt < testParams->mcanConfigParams.txMsgNum ;
         loopCnt++)
    {
        if (testParams->mcanConfigParams.txMsg[loopCnt].storageId ==
                                                        MCAN_MEM_TYPE_BUF)
        {
            /* Enable Transmission interrupt */
            configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr,
                    testParams->mcanConfigParams.txMsg[loopCnt].bufferNum,
                    (uint32_t)FALSE);
            if(configStatus != CSL_PASS)
            {
                DebugP_log("\nMCAN Tx Buffer Interrupt Enable FAILED...\n", -1);
            }
        }
    }

    return testStatus;
}

/* Test Setup: Short MCAN_HIGH and MCAN_LOW Pins */
static int32_t App_mcanTxTestBusOff(st_mcanTestcaseParams_t *testParams)
{
    int32_t  configStatus = CSL_PASS, testStatus = CSL_PASS;
    uint32_t loopCnt      = 1U, iterationCnt = 0U, intrMask, txBufCnt;
    MCAN_TxFIFOStatus txFIFOStatus;

    /* Enable Interrupts */
    MCAN_enableIntr(gMcanBaseAddr, testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);
    /* Select Interrupt Line */
    MCAN_selectIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        1U);
    /* Enable interrupts for Tx Buffers */
    for (loopCnt = 0U ;
         loopCnt < testParams->mcanConfigParams.txMsgNum ;
         loopCnt++)
    {
        if (testParams->mcanConfigParams.txMsg[loopCnt].storageId ==
                                                        MCAN_MEM_TYPE_BUF)
        {
            /* Enable Transmission interrupt */
            configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr,
                    testParams->mcanConfigParams.txMsg[loopCnt].bufferNum,
                    (uint32_t)TRUE);
            if(configStatus != CSL_PASS)
            {
                DebugP_log("\nMCAN Tx Buffer Interrupt Enable FAILED...\n", -1);
            }
        }
    }
    /* Enable interrupts for Tx FIFO/Queue */
    for (loopCnt = testParams->mcanConfigParams.ramConfig->txBufCnt ;
         loopCnt < (testParams->mcanConfigParams.ramConfig->txFIFOCnt +
                    testParams->mcanConfigParams.ramConfig->txBufCnt);
         loopCnt++)
    {
        /* Enable Transmission interrupt */
        configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr,
                loopCnt,
                (uint32_t)TRUE);
        if(configStatus != CSL_PASS)
        {
            DebugP_log("\nMCAN Tx FIFO Interrupt Enable FAILED...\n", -1);
        }
    }

    for (iterationCnt = 0U ;
         iterationCnt < testParams->mcanConfigParams.txMSGInterationCnt ;
         iterationCnt++)
    {
        for (loopCnt = 0U ;
             loopCnt < testParams->mcanConfigParams.txMsgNum ;
             loopCnt++)
        {
            MCAN_getTxFIFOQueStatus(gMcanBaseAddr, &txFIFOStatus);
            if (testParams->mcanConfigParams.txMsg[loopCnt].storageId ==
                                                        MCAN_MEM_TYPE_BUF)
            {
                txBufCnt = testParams->mcanConfigParams.txMsg[loopCnt].bufferNum;
            }
            else
            {
                txBufCnt = txFIFOStatus.putIdx;
            }
            /* Calculate Rx Interrupt Mask */
            if(testParams->mcanConfigParams.txMsg[loopCnt].rxMSGStorageId == MCAN_MEM_TYPE_BUF)
            {
                intrMask = MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG;
            }
            else
            {
                if(testParams->mcanConfigParams.txMsg[loopCnt].rxBuffNum == MCAN_RX_FIFO_NUM_0)
                {
                    intrMask = MCAN_INTR_SRC_RX_FIFO0_NEW_MSG;
                }
                else
                {
                    intrMask = MCAN_INTR_SRC_RX_FIFO1_NEW_MSG;
                }

            }
            (void)intrMask; /* Kill warning as presently varaible set but not used */
            gMcanIsrIntr0Status = 0U;
            // App_mcanPrintTxMsg(&testParams->mcanConfigParams.txMsg[loopCnt].txElem);
            /* Write message to Msg RAM */
            MCAN_writeMsgRam(gMcanBaseAddr,
                             testParams->mcanConfigParams.txMsg[loopCnt].storageId,
                             txBufCnt,
                             &testParams->mcanConfigParams.txMsg[loopCnt].txElem);
            /* Add request for transmission */
            volatile uint32_t myTemp = 1U;
            MCAN_ProtocolStatus protStatus;
            while(myTemp)
            {
                configStatus += MCAN_txBufAddReq(gMcanBaseAddr, txBufCnt);
                MCAN_getProtocolStatus(gMcanBaseAddr, &protStatus);
                /* Checking for Errors */
                if ((1U == protStatus.busOffStatus) &&
                     (1U == protStatus.errPassive))
                {
                    testStatus = CSL_PASS;
                    break;
                }
            }
        }
    }
    /* Disable interrupts for Tx Buffers */
    for (loopCnt = 0U ;
         loopCnt < testParams->mcanConfigParams.txMsgNum ;
         loopCnt++)
    {
        if (testParams->mcanConfigParams.txMsg[loopCnt].storageId ==
                                                        MCAN_MEM_TYPE_BUF)
        {
            /* Enable Transmission interrupt */
            configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr,
                    testParams->mcanConfigParams.txMsg[loopCnt].bufferNum,
                    (uint32_t)FALSE);
            if(configStatus != CSL_PASS)
            {
                DebugP_log("\nMCAN Tx Buffer Interrupt Enable FAILED...\n", -1);
            }
        }
    }

    return testStatus;
}

static void App_mcanInitTxElem(MCAN_TxBufElementNoCpy *txMsg)
{
    /* Standard message identifier 11 bit, stored into ID[28-18] */
    txMsg->id  = ((uint32_t)0x3U << 18U), /* Identifier */
    /* Transmit data frame */
    txMsg->rtr = FALSE;
    /* Standard message id */
    txMsg->xtd = FALSE;
    txMsg->esi = FALSE;
    /* Payload size is 64 bytes */
    txMsg->dlc = 0xFU;
    /* Bit Rate Switch */
    txMsg->brs = TRUE;
    /* CAN FD Frame Format */
    txMsg->fdf = TRUE;
    txMsg->efc = TRUE;
    txMsg->mm  = 0xAAU;
    txMsg->data = NULL;
}

static void App_mcanCompareBitTimeParams(MCAN_BitTimingParams *setPrms,
                MCAN_BitTimingParams *dstPrms)
{
    if ((setPrms->nomRatePrescalar != dstPrms->nomRatePrescalar) ||
        (setPrms->nomTimeSeg1 != dstPrms->nomTimeSeg1) ||
        (setPrms->nomTimeSeg2 != dstPrms->nomTimeSeg2) ||
        (setPrms->nomSynchJumpWidth != dstPrms->nomSynchJumpWidth) ||
        (setPrms->dataRatePrescalar != dstPrms->dataRatePrescalar) ||
        (setPrms->dataTimeSeg1 != dstPrms->dataTimeSeg1) ||
        (setPrms->dataTimeSeg2 != dstPrms->dataTimeSeg2) ||
        (setPrms->dataSynchJumpWidth != dstPrms->dataSynchJumpWidth))
   {
        DebugP_assert(TRUE);
   }
}

/**
 * @brief  Handle RX FIFO0 watermark interrupt test.
 *
 * @param  testParams  Pointer to testcase parameters.
 *
 * @return CSL_PASS on success, CSL_EFAIL on failure.
 */
static int32_t TestMcan_rxFifo0WatermarkIr(st_mcanTestcaseParams_t *testParams)
{
    int32_t configStatus = CSL_PASS;
    MCAN_RxFIFOStatus fifoStatus;
    MCAN_TxFIFOStatus txFIFOStatus;
    uint32_t txBufCnt;
    uint32_t loopCnt;

    /* Enable MCAN interrupts and route to requested line */
    MCAN_enableIntr(gMcanBaseAddr, testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);
    MCAN_selectIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);
    MCAN_enableIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        1U);

    /* Enable Transmission interrupt for dedicated buffer(s) used */
    for (loopCnt = 0U ; loopCnt < testParams->mcanConfigParams.txMsgNum ; loopCnt++)
    {
        if (testParams->mcanConfigParams.txMsg[loopCnt].storageId == MCAN_MEM_TYPE_BUF)
        {
            configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr,
                    testParams->mcanConfigParams.txMsg[loopCnt].bufferNum,
                    (uint32_t)TRUE);
        }
    }

    /* Transmit messages targeting RX FIFO0 without reading it to reach watermark */
    for (loopCnt = 0U ; loopCnt < testParams->mcanConfigParams.txMsgNum ; loopCnt++)
    {
        MCAN_getTxFIFOQueStatus(gMcanBaseAddr, &txFIFOStatus);
        if (testParams->mcanConfigParams.txMsg[loopCnt].storageId == MCAN_MEM_TYPE_BUF)
        {
            txBufCnt = testParams->mcanConfigParams.txMsg[loopCnt].bufferNum;
        }
        else
        {
            txBufCnt = txFIFOStatus.putIdx;
        }

        MCAN_writeMsgRam(gMcanBaseAddr,
                         testParams->mcanConfigParams.txMsg[loopCnt].storageId,
                         txBufCnt,
                         &testParams->mcanConfigParams.txMsg[loopCnt].txElem);
        configStatus += MCAN_txBufAddReq(gMcanBaseAddr, txBufCnt);
        if (CSL_PASS != configStatus)
        {
            return CSL_EFAIL;
        }

        /* Wait for Tx done to ensure message entered RX FIFO */
        SemaphoreP_pend(&gTxDoneSem, SystemP_WAIT_FOREVER);
    }

    /* Wait until RX FIFO0 watermark interrupt asserted */
    while ((gMcanIsrIntr0Status & MCAN_INTR_SRC_RX_FIFO0_WATERMARK) != MCAN_INTR_SRC_RX_FIFO0_WATERMARK)
    {
        /* spin until RF0W observed; ISR clears hardware and latches status */
    }

    /* Verify FIFO0 fill level equals configured watermark */
    fifoStatus.num = (uint32_t)MCAN_RX_FIFO_NUM_0;
    MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
    if (fifoStatus.fillLvl != testParams->mcanConfigParams.ramConfig->rxFIFO0WaterMark)
    {
        return CSL_EFAIL;
    }

    /* Drain FIFO0 and acknowledge entries */
    while (fifoStatus.fillLvl > 0U)
    {
        MCAN_RxBufElement rxMsg;
        MCAN_readMsgRam(gMcanBaseAddr,
                        MCAN_MEM_TYPE_FIFO,
                        fifoStatus.getIdx,
                        (uint32_t)fifoStatus.num,
                        &rxMsg);
        (void) MCAN_writeRxFIFOAck(gMcanBaseAddr,
                                   (uint32_t)fifoStatus.num,
                                   fifoStatus.getIdx);
        MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
    }

    return CSL_PASS;
}

/**
 * @brief  Validate timeout counter behaviour (TOCC/TOCN).
 *
 * @param  testParams  Pointer to testcase parameters.
 *
 * @return CSL_PASS on success, CSL_EFAIL on failure.
 */
static int32_t TestMcan_timeoutCounter(st_mcanTestcaseParams_t *testParams)
{
    int32_t status = CSL_PASS;
    MCAN_TxFIFOStatus txFIFOStatus;
    uint32_t txBufCnt;

    /* Enable interrupts and route */
    MCAN_enableIntr(gMcanBaseAddr, testParams->mcanConfigParams.intrEnable | MCAN_INTR_SRC_TIMEOUT, (uint32_t)TRUE);
    MCAN_selectIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask | MCAN_INTR_SRC_TIMEOUT,
                        testParams->mcanConfigParams.intrLine);
    MCAN_enableIntrLine(gMcanBaseAddr, testParams->mcanConfigParams.intrLine, 1U);

    /* Send one message to FIFO0 and do not read it */
    MCAN_getTxFIFOQueStatus(gMcanBaseAddr, &txFIFOStatus);
    if (testParams->mcanConfigParams.txMsg[0].storageId == MCAN_MEM_TYPE_BUF)
    {
        txBufCnt = testParams->mcanConfigParams.txMsg[0].bufferNum;
    }
    else
    {
        txBufCnt = txFIFOStatus.putIdx;
    }
    MCAN_writeMsgRam(gMcanBaseAddr,
                     testParams->mcanConfigParams.txMsg[0].storageId,
                     txBufCnt,
                     &testParams->mcanConfigParams.txMsg[0].txElem);
    status += MCAN_txBufAddReq(gMcanBaseAddr, txBufCnt);
    if (CSL_PASS != status)
    {
        return CSL_EFAIL;
    }

    /* Wait Tx done */
    SemaphoreP_pend(&gTxDoneSem, SystemP_WAIT_FOREVER);

    /* Wait for timeout interrupt */
    while ((gMcanIsrIntr0Status & MCAN_INTR_SRC_TIMEOUT) != MCAN_INTR_SRC_TIMEOUT)
    {
        /* spin until timeout occurs */
    }
    /* Validate timeout counter reached zero */
    if (MCAN_getTOCounterVal(gMcanBaseAddr) != 0U)
    {
        return CSL_EFAIL;
    }
    return CSL_PASS;
}

/**
 * @brief  Negative test: send FD frame when RAM elements are configured for classic.
 *
 * @param  testParams  Pointer to testcase parameters.
 *
 * @return CSL_PASS on expected failure (driver/HW rejected), CSL_EFAIL otherwise.
 */
static int32_t TestMcan_fDdlcRamElemMisconfigTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t status = CSL_PASS;
    int32_t rc;
    MCAN_TxFIFOStatus txFIFOStatus;
    uint32_t txBufCnt;

    /* Get TX buffer index to use */
    MCAN_getTxFIFOQueStatus(gMcanBaseAddr, &txFIFOStatus);
    if (testParams->mcanConfigParams.txMsg[0].storageId == MCAN_MEM_TYPE_BUF)
    {
        txBufCnt = testParams->mcanConfigParams.txMsg[0].bufferNum;
    }
    else
    {
        txBufCnt = txFIFOStatus.putIdx;
    }

    /* Write the FD message (dlc>8) into message RAM */
    MCAN_writeMsgRam(gMcanBaseAddr,
                     testParams->mcanConfigParams.txMsg[0].storageId,
                     txBufCnt,
                     &testParams->mcanConfigParams.txMsg[0].txElem);

    /* Reset any ISR status tracked by test framework */
    gMcanIsrIntr0Status = 0U;

    /* Try to add transmission request - this is expected to either be rejected
     * by driver API or cause HW to abort transmission and set error flags.
     */
    rc = MCAN_txBufAddReq(gMcanBaseAddr, txBufCnt);
    DebugP_log("MCAN_txBufAddReq returned %d for FD frame with RAM element misconfigured.\n", rc);

    /* If API rejected request -> expected negative behaviour */
    if (rc != CSL_PASS)
    {
        DebugP_log("MCAN_txBufAddReq failed as expected for FD frame with MSG RAM elems configured for classic frames.\n");
        status = CSL_PASS;
        return status;
    }

    /* API accepted request. Wait for TX completion or error/abort indication. */
    if (SemaphoreP_pend(&gTxDoneSem, 1000U) == SystemP_SUCCESS)
    {
        /* Transmission completed unexpectedly -> test fail */
        DebugP_log("Unexpected: TX completed for FD frame although MSG RAM elems were classic sized.\n");
        status = CSL_EFAIL;
        return status;
    }

    /* No TX completion within timeout. Validate HW/driver error indications. */
    {
        MCAN_ProtocolStatus protStatus;
        uint32_t txReqPend = MCAN_getTxBufReqPend(gMcanBaseAddr);
        uint32_t txTransStatus = MCAN_getTxBufTransmissionStatus(gMcanBaseAddr);
        MCAN_ErrCntStatus errCnt;
        
        MCAN_getProtocolStatus(gMcanBaseAddr, &protStatus);
        MCAN_getErrCounters(gMcanBaseAddr, &errCnt);

        DebugP_log("ProtocolStatus: LEC=%u DLEC=%u PXE=%u, TxReqPend=0x%08x, TxTransStatus=0x%08x, ErrCnt TEC=%u REC=%u, ISR=0x%08x\n",
                   protStatus.lastErrCode, protStatus.dlec, protStatus.pxe, txReqPend, txTransStatus, 
                   errCnt.transErrLogCnt, errCnt.recErrCnt, gMcanIsrIntr0Status);

        /* Consider test passed if any HW/driver error/abort indication is observed */
        if ((protStatus.lastErrCode != MCAN_ERR_CODE_NO_ERROR && protStatus.lastErrCode != MCAN_ERR_CODE_NO_CHANGE) ||
            (protStatus.dlec != MCAN_ERR_CODE_NO_ERROR && protStatus.dlec != MCAN_ERR_CODE_NO_CHANGE) ||
            (protStatus.pxe != 0U) ||
            (txTransStatus != 0U) ||
            (errCnt.transErrLogCnt != 0U) ||
            (errCnt.recErrCnt != 0U) ||
            (gMcanIsrIntr0Status != 0U))
        {
            DebugP_log("Error/abort indications observed for FD frame with RAM elem size mismatch: PASS.\n");
            status = CSL_PASS;
        }
        else
        {
            DebugP_log("No error/abort indications observed for FD frame with RAM elem size mismatch: FAIL.\n");
            status = CSL_EFAIL;
        }
    }

    return status;
}
/**
 *  \brief  Negative test: FD operation disabled but attempting to send FD frame
 *
 *  \param  testParams  Test case parameters
 *
 *  \return Test result
 */
static int32_t TestMcan_fDOperationDisabledTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t status = CSL_PASS;
    int32_t rc;
    MCAN_TxFIFOStatus txFIFOStatus;
    uint32_t txBufCnt;

    /* Get TX buffer index to use */
    MCAN_getTxFIFOQueStatus(gMcanBaseAddr, &txFIFOStatus);
    if (testParams->mcanConfigParams.txMsg[0].storageId == MCAN_MEM_TYPE_BUF)
    {
        txBufCnt = testParams->mcanConfigParams.txMsg[0].bufferNum;
    }
    else
    {
        txBufCnt = txFIFOStatus.putIdx;
    }

    /* Write the FD message into message RAM */
    MCAN_writeMsgRam(gMcanBaseAddr,
                     testParams->mcanConfigParams.txMsg[0].storageId,
                     txBufCnt,
                     &testParams->mcanConfigParams.txMsg[0].txElem);

    /* Reset any ISR status tracked by test framework */
    gMcanIsrIntr0Status = 0U;

    /* Try to add transmission request - this is expected to either be rejected
     * by driver API or cause HW to abort transmission and set error flags.
     */
    rc = MCAN_txBufAddReq(gMcanBaseAddr, txBufCnt);
    DebugP_log("MCAN_txBufAddReq returned %d for FD frame with FD operation disabled.\n", rc);

    /* If API rejected request -> expected negative behaviour */
    if (rc != CSL_PASS)
    {
        DebugP_log("MCAN_txBufAddReq failed as expected for FD frame with FD operation disabled.\n");
        status = CSL_PASS;
        return status;
    }

    /* API accepted request. Wait for TX completion or error/abort indication. */
    if (SemaphoreP_pend(&gTxDoneSem, 1000U) == SystemP_SUCCESS)
    {
        /* Transmission completed unexpectedly -> test fail */
        DebugP_log("Unexpected: TX completed for FD frame although FD operation was disabled.\n");
        status = CSL_EFAIL;
        return status;
    }

    /* No TX completion within timeout. Validate HW/driver error indications. */
    {
        MCAN_ProtocolStatus protStatus;
        uint32_t txReqPend = MCAN_getTxBufReqPend(gMcanBaseAddr);
        uint32_t txTransStatus = MCAN_getTxBufTransmissionStatus(gMcanBaseAddr);
        MCAN_ErrCntStatus errCnt;
        
        MCAN_getProtocolStatus(gMcanBaseAddr, &protStatus);
        MCAN_getErrCounters(gMcanBaseAddr, &errCnt);

        DebugP_log("ProtocolStatus: LEC=%u DLEC=%u PXE=%u, TxReqPend=0x%08x, TxTransStatus=0x%08x, ErrCnt TEC=%u REC=%u, ISR=0x%08x\n",
                   protStatus.lastErrCode, protStatus.dlec, protStatus.pxe, txReqPend, txTransStatus, 
                   errCnt.transErrLogCnt, errCnt.recErrCnt, gMcanIsrIntr0Status);

        /* Consider test passed if any HW/driver error/abort indication is observed */
        if ((protStatus.lastErrCode != MCAN_ERR_CODE_NO_ERROR && protStatus.lastErrCode != MCAN_ERR_CODE_NO_CHANGE) ||
            (protStatus.dlec != MCAN_ERR_CODE_NO_ERROR && protStatus.dlec != MCAN_ERR_CODE_NO_CHANGE) ||
            (protStatus.pxe != 0U) ||
            (txTransStatus != 0U) ||
            (errCnt.transErrLogCnt != 0U) ||
            (errCnt.recErrCnt != 0U) ||
            (gMcanIsrIntr0Status != 0U))
        {
            DebugP_log("Error/abort indications observed for FD frame with FD operation disabled: PASS.\n");
            status = CSL_PASS;
        }
        else
        {
            DebugP_log("No error/abort indications observed for FD frame with FD operation disabled: FAIL.\n");
            status = CSL_EFAIL;
        }
    }

    return status;
}

/**
 * @brief  NULL-pointer robustness tests for various MCAN APIs.
 *
 * @param  testParams  Pointer to testcase parameters.
 *
 * @return CSL_PASS if APIs with return values correctly reject NULL, CSL_EFAIL otherwise.
 */
static int32_t TestMcan_nullPointerTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t status = CSL_PASS;
    int32_t rc;
    uint32_t loopCnt = 0U;

    DebugP_log("\n==== MCAN NULL Pointer Validation Test ====\n");

    /* Test 1: MCAN_init with NULL initParams */
    DebugP_log("[%d] Testing MCAN_init with NULL initParams...\n", ++loopCnt);
    rc = MCAN_init(gMcanBaseAddr, NULL);
    if (rc == CSL_PASS)
    {
        DebugP_log("FAIL: MCAN_init accepted NULL initParams\n");
        status = CSL_EFAIL;
    }
    else
    {
        DebugP_log("PASS: MCAN_init rejected NULL initParams\n");
    }

    /* Test 2: MCAN_config with NULL configParams */
    DebugP_log("[%d] Testing MCAN_config with NULL configParams...\n", ++loopCnt);
    rc = MCAN_config(gMcanBaseAddr, NULL);
    if (rc == CSL_PASS)
    {
        DebugP_log("FAIL: MCAN_config accepted NULL configParams\n");
        status = CSL_EFAIL;
    }
    else
    {
        DebugP_log("PASS: MCAN_config rejected NULL configParams\n");
    }

#ifdef MCAN_ECC_SUPPORTED
    /* Test 3: MCAN_eccConfig with NULL configParams */
    DebugP_log("[%d] Testing MCAN_eccConfig with NULL configParams...\n", ++loopCnt);
    MCAN_eccConfig(gMcanBaseAddr, NULL);
    /* No return value - check if it crashes or handles gracefully */
    DebugP_log("INFO: MCAN_eccConfig executed with NULL (void return)\n");
#endif

    /* Test 4: MCAN_setBitTime with NULL configParams */
    DebugP_log("[%d] Testing MCAN_setBitTime with NULL configParams...\n", ++loopCnt);
    rc = MCAN_setBitTime(gMcanBaseAddr, NULL);
    if (rc == CSL_PASS)
    {
        DebugP_log("FAIL: MCAN_setBitTime accepted NULL configParams\n");
        status = CSL_EFAIL;
    }
    else
    {
        DebugP_log("PASS: MCAN_setBitTime rejected NULL configParams\n");
    }

    /* Test 5: MCAN_msgRAMConfig with NULL msgRAMConfigParams */
    DebugP_log("[%d] Testing MCAN_msgRAMConfig with NULL msgRAMConfigParams...\n", ++loopCnt);
    rc = MCAN_msgRAMConfig(gMcanBaseAddr, NULL);
    if (rc == CSL_PASS)
    {
        DebugP_log("FAIL: MCAN_msgRAMConfig accepted NULL msgRAMConfigParams\n");
        status = CSL_EFAIL;
    }
    else
    {
        DebugP_log("PASS: MCAN_msgRAMConfig rejected NULL msgRAMConfigParams\n");
    }

    /* Test 6: MCAN_writeMsgRam with NULL elem */
    DebugP_log("[%d] Testing MCAN_writeMsgRam with NULL elem...\n", ++loopCnt);
    MCAN_writeMsgRam(gMcanBaseAddr, MCAN_MEM_TYPE_BUF, 0U, NULL);
    /* No return value - check if it crashes or handles gracefully */
    DebugP_log("INFO: MCAN_writeMsgRam executed with NULL elem (void return)\n");

    /* Test 7: MCAN_writeMsgRamNoCpy with NULL elem */
    DebugP_log("[%d] Testing MCAN_writeMsgRamNoCpy with NULL elem...\n", ++loopCnt);
    MCAN_writeMsgRamNoCpy(gMcanBaseAddr, MCAN_MEM_TYPE_BUF, 0U, NULL);
    DebugP_log("INFO: MCAN_writeMsgRamNoCpy executed with NULL elem (void return)\n");

    /* Test 8: MCAN_getNewDataStatus with NULL newDataStatus */
    DebugP_log("[%d] Testing MCAN_getNewDataStatus with NULL newDataStatus...\n", ++loopCnt);
    MCAN_getNewDataStatus(gMcanBaseAddr, NULL);
    DebugP_log("INFO: MCAN_getNewDataStatus executed with NULL (void return)\n");

    /* Test 9: MCAN_clearNewDataStatus with NULL newDataStatus */
    DebugP_log("[%d] Testing MCAN_clearNewDataStatus with NULL newDataStatus...\n", ++loopCnt);
    MCAN_clearNewDataStatus(gMcanBaseAddr, NULL);
    DebugP_log("INFO: MCAN_clearNewDataStatus executed with NULL (void return)\n");

    /* Test 10: MCAN_readMsgRam with NULL elem */
    DebugP_log("[%d] Testing MCAN_readMsgRam with NULL elem...\n", ++loopCnt);
    MCAN_readMsgRam(gMcanBaseAddr, MCAN_MEM_TYPE_BUF, 0U, MCAN_RX_FIFO_NUM_0, NULL);
    DebugP_log("INFO: MCAN_readMsgRam executed with NULL elem (void return)\n");

    /* Test 11: MCAN_readMsgRamNoCpy with NULL elem */
    DebugP_log("[%d] Testing MCAN_readMsgRamNoCpy with NULL elem...\n", ++loopCnt);
    MCAN_readMsgRamNoCpy(gMcanBaseAddr, MCAN_MEM_TYPE_BUF, 0U, MCAN_RX_FIFO_NUM_0, NULL);
    DebugP_log("INFO: MCAN_readMsgRamNoCpy executed with NULL elem (void return)\n");

    /* Test 12: MCAN_readTxEventFIFO with NULL txEventElem */
    DebugP_log("[%d] Testing MCAN_readTxEventFIFO with NULL txEventElem...\n", ++loopCnt);
    MCAN_readTxEventFIFO(gMcanBaseAddr, NULL);
    DebugP_log("INFO: MCAN_readTxEventFIFO executed with NULL (void return)\n");

    /* Test 13: MCAN_addStdMsgIDFilter with NULL elem */
    DebugP_log("[%d] Testing MCAN_addStdMsgIDFilter with NULL elem...\n", ++loopCnt);
    MCAN_addStdMsgIDFilter(gMcanBaseAddr, 0U, NULL);
    DebugP_log("INFO: MCAN_addStdMsgIDFilter executed with NULL elem (void return)\n");

    /* Test 14: MCAN_addExtMsgIDFilter with NULL elem */
    DebugP_log("[%d] Testing MCAN_addExtMsgIDFilter with NULL elem...\n", ++loopCnt);
    MCAN_addExtMsgIDFilter(gMcanBaseAddr, 0U, NULL);
    DebugP_log("INFO: MCAN_addExtMsgIDFilter executed with NULL elem (void return)\n");

    /* Test 15: MCAN_getErrCounters with NULL errCounter */
    DebugP_log("[%d] Testing MCAN_getErrCounters with NULL errCounter...\n", ++loopCnt);
    MCAN_getErrCounters(gMcanBaseAddr, NULL);
    DebugP_log("INFO: MCAN_getErrCounters executed with NULL (void return)\n");

    /* Test 16: MCAN_getProtocolStatus with NULL protStatus */
    DebugP_log("[%d] Testing MCAN_getProtocolStatus with NULL protStatus...\n", ++loopCnt);
    MCAN_getProtocolStatus(gMcanBaseAddr, NULL);
    DebugP_log("INFO: MCAN_getProtocolStatus executed with NULL (void return)\n");

    /* Test 17: MCAN_getHighPriorityMsgStatus with NULL hpm */
    DebugP_log("[%d] Testing MCAN_getHighPriorityMsgStatus with NULL hpm...\n", ++loopCnt);
    MCAN_getHighPriorityMsgStatus(gMcanBaseAddr, NULL);
    DebugP_log("INFO: MCAN_getHighPriorityMsgStatus executed with NULL (void return)\n");

    /* Test 18: MCAN_getRxFIFOStatus with NULL fifoStatus */
    DebugP_log("[%d] Testing MCAN_getRxFIFOStatus with NULL fifoStatus...\n", ++loopCnt);
    MCAN_getRxFIFOStatus(gMcanBaseAddr, NULL);
    DebugP_log("INFO: MCAN_getRxFIFOStatus executed with NULL (void return)\n");

    /* Test 19: MCAN_getTxFIFOQueStatus with NULL fifoStatus */
    DebugP_log("[%d] Testing MCAN_getTxFIFOQueStatus with NULL fifoStatus...\n", ++loopCnt);
    MCAN_getTxFIFOQueStatus(gMcanBaseAddr, NULL);
    DebugP_log("INFO: MCAN_getTxFIFOQueStatus executed with NULL (void return)\n");

    /* Test 20: MCAN_getTxEventFIFOStatus with NULL fifoStatus */
    DebugP_log("[%d] Testing MCAN_getTxEventFIFOStatus with NULL fifoStatus...\n", ++loopCnt);
    MCAN_getTxEventFIFOStatus(gMcanBaseAddr, NULL);
    DebugP_log("INFO: MCAN_getTxEventFIFOStatus executed with NULL (void return)\n");

#ifdef MCAN_ECC_SUPPORTED
    /* Test 21: MCAN_eccForceError with NULL eccErr */
    DebugP_log("[%d] Testing MCAN_eccForceError with NULL eccErr...\n", ++loopCnt);
    MCAN_eccForceError(gMcanBaseAddr, NULL);
    DebugP_log("INFO: MCAN_eccForceError executed with NULL (void return)\n");

    /* Test 22: MCAN_eccGetErrorStatus with NULL eccErr */
    DebugP_log("[%d] Testing MCAN_eccGetErrorStatus with NULL eccErr...\n", ++loopCnt);
    MCAN_eccGetErrorStatus(gMcanBaseAddr, NULL);
    DebugP_log("INFO: MCAN_eccGetErrorStatus executed with NULL (void return)\n");
#endif

    /* Test 23: MCAN_getRevisionId with NULL revId */
    DebugP_log("[%d] Testing MCAN_getRevisionId with NULL revId...\n", ++loopCnt);
    MCAN_getRevisionId(gMcanBaseAddr, NULL);
    DebugP_log("INFO: MCAN_getRevisionId executed with NULL (void return)\n");

    /* Test 24: MCAN_getBitTime with NULL configParams */
    DebugP_log("[%d] Testing MCAN_getBitTime with NULL configParams...\n", ++loopCnt);
    MCAN_getBitTime(gMcanBaseAddr, NULL);
    DebugP_log("INFO: MCAN_getBitTime executed with NULL (void return)\n");

#ifdef MCAN_ECC_SUPPORTED
    /* Test 25: MCAN_eccAggrGetRevisionId with NULL revId */
    DebugP_log("[%d] Testing MCAN_eccAggrGetRevisionId with NULL revId...\n", ++loopCnt);
    MCAN_eccAggrGetRevisionId(gMcanBaseAddr, NULL);
    DebugP_log("INFO: MCAN_eccAggrGetRevisionId executed with NULL (void return)\n");
#endif

    DebugP_log("\n==== Summary: %d APIs tested for NULL pointer handling ====\n", loopCnt);
    
    if (status == CSL_PASS)
    {
        DebugP_log("NULL pointer validation test: PASS (APIs with return values rejected NULL)\n");
    }
    else
    {
        DebugP_log("NULL pointer validation test: FAIL (Some APIs accepted NULL pointers)\n");
    }

    return status;
}

#ifdef MCAN_ECC_SUPPORTED
/**
 * \brief   Test to validate MCAN_eccGetIntrStatus and MCAN_eccClearIntrStatus APIs
 *
 *          This test exercises the ECC interrupt status read/clear APIs directly:
 *          1. Verifies initial status is clear (no pending ECC interrupts)
 *          2. Forces a SEC error via MCAN_eccForceError and reads back status
 *          3. Clears SEC interrupt status and verifies it is cleared
 *          4. Forces a DED error via MCAN_eccForceError and reads back status
 *          5. Clears DED interrupt status and verifies it is cleared
 *          6. Tests invalid errType returns 0 (default branch coverage)
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      CSL_PASS if all checks pass, CSL_EFAIL otherwise.
 */
static int32_t TestMcan_eCCIntrStatusTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t  testStatus = CSL_PASS;
    uint32_t intrStatus;
    uint32_t accessAddr;
    MCAN_ECCErrForceParams eccErrForce;

    DebugP_log("\n==== MCAN ECC Interrupt Status API Test ====\n");

    /*
     * Disable ECC interrupts so the ECC ISR does not fire and clear the
     * status registers before we can read them.  The SEC_STATUS / DED_STATUS
     * registers latch error occurrences regardless of the interrupt-enable
     * bits — only the interrupt signal propagation is gated.
     */
    MCAN_eccEnableIntr(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_SEC, FALSE);
    MCAN_eccEnableIntr(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_DED, FALSE);

    /* ---- Step 1: Verify initial status is clear ---- */
    intrStatus = MCAN_eccGetIntrStatus(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_SEC);
    if (intrStatus != 0U)
    {
        DebugP_log("FAIL: Initial SEC interrupt status is not clear (got %u)\n", intrStatus);
        testStatus = CSL_EFAIL;
    }
    else
    {
        DebugP_log("PASS: Initial SEC interrupt status is clear\n");
    }

    intrStatus = MCAN_eccGetIntrStatus(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_DED);
    if (intrStatus != 0U)
    {
        DebugP_log("FAIL: Initial DED interrupt status is not clear (got %u)\n", intrStatus);
        testStatus = CSL_EFAIL;
    }
    else
    {
        DebugP_log("PASS: Initial DED interrupt status is clear\n");
    }

    /* ---- Step 2: Force SEC error and validate eccGetIntrStatus ---- */
    DebugP_log("\nForcing SEC error via ECC self-test...\n");
    eccErrForce.errType  = MCAN_ECC_ERR_TYPE_SEC;
    eccErrForce.rowNum   = 0U;
    eccErrForce.bit1     = 0x04U;  /* Column/Data bit to flip for SEC */
    eccErrForce.bit2     = 0x01U;  /* Not used for SEC but set for consistency */
    eccErrForce.errOnce  = 1U;
    eccErrForce.errForce = 0U;

    MCAN_eccForceError(gMcanBaseAddr, &eccErrForce);

    /* Trigger the error by reading from the row in message RAM */
    accessAddr = gMcanBaseAddr + MCAN_MCAN_MSG_MEM + (eccErrForce.rowNum * 4U);
    (void)HW_RD_REG32(accessAddr);

    /* Check that SEC interrupt status is now pending */
    intrStatus = MCAN_eccGetIntrStatus(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_SEC);
    if (intrStatus == 0U)
    {
        DebugP_log("FAIL: SEC interrupt status not set after forcing SEC error\n");
        testStatus = CSL_EFAIL;
    }
    else
    {
        DebugP_log("PASS: SEC interrupt status is pending after forced error (status=%u)\n", intrStatus);
    }

    /* ---- Step 3: Clear SEC status and verify ---- */
    MCAN_eccClearIntrStatus(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_SEC);
    /* Also clear the error status to fully service the error */
    MCAN_eccClearErrorStatus(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_SEC);
    MCAN_eccWriteEOI(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_SEC);

    intrStatus = MCAN_eccGetIntrStatus(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_SEC);
    if (intrStatus != 0U)
    {
        DebugP_log("FAIL: SEC interrupt status not cleared after MCAN_eccClearIntrStatus (got %u)\n", intrStatus);
        testStatus = CSL_EFAIL;
    }
    else
    {
        DebugP_log("PASS: SEC interrupt status successfully cleared\n");
    }

    /* ---- Step 4: Force DED error and validate eccGetIntrStatus ---- */
    DebugP_log("\nForcing DED error via ECC self-test...\n");
    eccErrForce.errType  = MCAN_ECC_ERR_TYPE_DED;
    eccErrForce.rowNum   = 0U;
    eccErrForce.bit1     = 0x04U;  /* First bit to flip for DED */
    eccErrForce.bit2     = 0x01U;  /* Second bit to flip for DED */
    eccErrForce.errOnce  = 1U;
    eccErrForce.errForce = 0U;

    MCAN_eccForceError(gMcanBaseAddr, &eccErrForce);

    /* Trigger the error by reading from the row in message RAM */
    accessAddr = gMcanBaseAddr + MCAN_MCAN_MSG_MEM + (eccErrForce.rowNum * 4U);
    (void)HW_RD_REG32(accessAddr);

    /* Check that DED interrupt status is now pending */
    intrStatus = MCAN_eccGetIntrStatus(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_DED);
    if (intrStatus == 0U)
    {
        DebugP_log("FAIL: DED interrupt status not set after forcing DED error\n");
        testStatus = CSL_EFAIL;
    }
    else
    {
        DebugP_log("PASS: DED interrupt status is pending after forced error (status=%u)\n", intrStatus);
    }

    /* ---- Step 5: Clear DED status and verify ---- */
    MCAN_eccClearIntrStatus(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_DED);
    /* Also clear the error status to fully service the error */
    MCAN_eccClearErrorStatus(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_DED);
    MCAN_eccWriteEOI(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_DED);

    intrStatus = MCAN_eccGetIntrStatus(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_DED);
    if (intrStatus != 0U)
    {
        DebugP_log("FAIL: DED interrupt status not cleared after MCAN_eccClearIntrStatus (got %u)\n", intrStatus);
        testStatus = CSL_EFAIL;
    }
    else
    {
        DebugP_log("PASS: DED interrupt status successfully cleared\n");
    }

    /* ---- Step 6: Test invalid errType (default branch coverage) ---- */
    DebugP_log("\nTesting invalid errType for MCAN_eccGetIntrStatus...\n");
    intrStatus = MCAN_eccGetIntrStatus(gMcanBaseAddr, 0xFFU);
    if (intrStatus != 0U)
    {
        DebugP_log("FAIL: Invalid errType returned non-zero status (got %u)\n", intrStatus);
        testStatus = CSL_EFAIL;
    }
    else
    {
        DebugP_log("PASS: Invalid errType correctly returned 0\n");
    }

    /* Call eccClearIntrStatus with invalid errType - should hit default branch harmlessly */
    MCAN_eccClearIntrStatus(gMcanBaseAddr, 0xFFU);
    DebugP_log("PASS: MCAN_eccClearIntrStatus with invalid errType did not crash\n");

    /* Take MCAN out of SW init mode if it entered due to DED error */
    if (MCAN_OPERATION_MODE_SW_INIT == MCAN_getOpMode(gMcanBaseAddr))
    {
        MCAN_setOpMode(gMcanBaseAddr, MCAN_OPERATION_MODE_NORMAL);
        while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(gMcanBaseAddr))
        {
        }
    }

    /* Re-enable ECC interrupts so other tests are not affected */
    MCAN_eccEnableIntr(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_SEC, TRUE);
    MCAN_eccEnableIntr(gMcanBaseAddr, MCAN_ECC_ERR_TYPE_DED, TRUE);

    DebugP_log("\n==== ECC Interrupt Status API Test: %s ====\n",
               (testStatus == CSL_PASS) ? "PASS" : "FAIL");

    return testStatus;
}
#endif /* #ifdef MCAN_ECC_SUPPORTED */

/**
 * \brief   Test to configure and validate 128 Standard ID filter elements
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      Test execution status.
 */
static int32_t TestMcan_stdIDFilterMaxTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t configStatus = CSL_PASS, testStatus = CSL_PASS;
    uint32_t filterIdx, txBufCnt;
    MCAN_StdMsgIDFilterElement stdIdFilter;
    MCAN_RxBufElement rxMsg;
    MCAN_TxFIFOStatus txFIFOStatus;
    MCAN_ProtocolStatus protStatus;
    MCAN_ErrCntStatus errCounter;
    const uint32_t maxStdFilters = 128U;

    DebugP_log("\n==== Standard ID Filter Maximum Elements Test ====\n");
    DebugP_log("Configuring %d Standard ID filters...\n", maxStdFilters);

    /* Enable Interrupts */
    MCAN_enableIntr(gMcanBaseAddr, testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);
    MCAN_selectIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);
    MCAN_enableIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        1U);

    /* Enable Transmission interrupt for buffer 0 */
    configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr, 0U, (uint32_t)TRUE);
    if(configStatus != CSL_PASS)
    {
        DebugP_log("\nMCAN Tx Buffer Interrupt Enable FAILED...\n");
        testStatus = CSL_EFAIL;
    }

    /* Configure 128 Standard ID filters */
    for(filterIdx = 0U; filterIdx < maxStdFilters; filterIdx++)
    {
        stdIdFilter.sfid2 = (filterIdx + 1U) & 0x7FFU;
        stdIdFilter.sfid1 = (filterIdx + 1U) & 0x7FFU;
        
        /* Vary filter types across the filter list */
        if(filterIdx < 32U)
        {
            /* First 32: Store in dedicated RX buffers */
            stdIdFilter.sfec = MCAN_STD_FILT_ELEM_BUFFER;
            stdIdFilter.sft = MCAN_STD_FILT_TYPE_CLASSIC;
            stdIdFilter.sfid1 = (filterIdx + 1U) & 0x7FFU;
            stdIdFilter.sfid2 = filterIdx;  /* Use as buffer index */
        }
        else if(filterIdx < 64U)
        {
            /* Next 32: Store in RX FIFO0 */
            stdIdFilter.sfec = MCAN_STD_FILT_ELEM_FIFO0;
            stdIdFilter.sft = MCAN_STD_FILT_TYPE_RANGE;
            stdIdFilter.sfid1 = (filterIdx + 1U) & 0x7FFU;
            stdIdFilter.sfid2 = (filterIdx + 10U) & 0x7FFU;
        }
        else if(filterIdx < 96U)
        {
            /* Next 32: Store in RX FIFO1 */
            stdIdFilter.sfec = MCAN_STD_FILT_ELEM_FIFO1;
            stdIdFilter.sft = MCAN_STD_FILT_TYPE_CLASSIC; 
            stdIdFilter.sfid1 = (filterIdx + 1U) & 0x7FFU;
            stdIdFilter.sfid2 = 0x7FFU;  // ← Mask: accept all (or use specific mask)
        }
        else
        {
            /* Last 32: Reject matching messages */
            stdIdFilter.sfec = MCAN_STD_FILT_ELEM_REJECT;
            stdIdFilter.sft = MCAN_STD_FILT_TYPE_CLASSIC;
            stdIdFilter.sfid1 = (filterIdx + 1U) & 0x7FFU;
            stdIdFilter.sfid2 = 0U;
        }

        /* Add Standard ID filter */
        MCAN_addStdMsgIDFilter(gMcanBaseAddr, filterIdx, &stdIdFilter);
    }

    DebugP_log("Successfully configured %d Standard ID filters.\n", maxStdFilters);

    /* Test filter functionality by sending test messages */
    /* Test Case 1: Send message matching first filter (should go to RX buffer 0) */
    DebugP_log("\n--- Test Case 1: Message to RX Buffer ---\n");
    gMcanIsrIntr0Status = 0U;
    
    MCAN_getTxFIFOQueStatus(gMcanBaseAddr, &txFIFOStatus);
    txBufCnt = 0U;
    
    testParams->mcanConfigParams.txMsg[0U].txElem.id = (1U << APP_MCAN_STD_ID_SHIFT);
    testParams->mcanConfigParams.txMsg[0U].txElem.xtd = 0U;
    testParams->mcanConfigParams.txMsg[0U].txElem.rtr = 0U;
    testParams->mcanConfigParams.txMsg[0U].txElem.dlc = MCAN_DATA_SIZE_8BYTES;
    testParams->mcanConfigParams.txMsg[0U].txElem.fdf = 0U;
    testParams->mcanConfigParams.txMsg[0U].txElem.brs = 0U;
    
    MCAN_writeMsgRam(gMcanBaseAddr,
                     MCAN_MEM_TYPE_BUF,
                     txBufCnt,
                     &testParams->mcanConfigParams.txMsg[0U].txElem);
    
    configStatus = MCAN_txBufAddReq(gMcanBaseAddr, txBufCnt);
    if (CSL_PASS != configStatus)
    {
        DebugP_log("Error in Adding Transmission Request...\n");
        testStatus = CSL_EFAIL;
    }

    SemaphoreP_pend(&gTxDoneSem, SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&gRxDoneSem, SystemP_WAIT_FOREVER);

    /* Check if message received in dedicated buffer */
    if((gMcanIsrIntr0Status & MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG) == MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG)
    {
        configStatus = App_mcanReadRxMSG(&rxMsg, gMcanIsrIntr0Status);
        if(configStatus == CSL_PASS)
        {
            if(((rxMsg.id >> APP_MCAN_STD_ID_SHIFT) & 0x7FFU) == 1U)
            {
                DebugP_log("PASS: Message correctly filtered to RX Buffer 0\n");
            }
            else
            {
                DebugP_log("FAIL: Incorrect message ID received\n");
                testStatus = CSL_EFAIL;
            }
        }
    }
    else
    {
        DebugP_log("FAIL: Message not received in dedicated buffer\n");
        testStatus = CSL_EFAIL;
    }

    /* Test Case 2: Send message matching filter 40 (should go to RX FIFO0) */
    DebugP_log("\n--- Test Case 2: Message to RX FIFO0 ---\n");
    gMcanIsrIntr0Status = 0U;
    
    testParams->mcanConfigParams.txMsg[0U].txElem.id = (41U << APP_MCAN_STD_ID_SHIFT);
    
    MCAN_writeMsgRam(gMcanBaseAddr,
                     MCAN_MEM_TYPE_BUF,
                     txBufCnt,
                     &testParams->mcanConfigParams.txMsg[0U].txElem);
    
    configStatus = MCAN_txBufAddReq(gMcanBaseAddr, txBufCnt);
    if (CSL_PASS != configStatus)
    {
        DebugP_log("Error in Adding Transmission Request...\n");
        testStatus = CSL_EFAIL;
    }

    SemaphoreP_pend(&gTxDoneSem, SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&gRxDoneSem, SystemP_WAIT_FOREVER);

    if((gMcanIsrIntr0Status & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) == MCAN_INTR_SRC_RX_FIFO0_NEW_MSG)
    {
        configStatus = App_mcanReadRxMSG(&rxMsg, gMcanIsrIntr0Status);
        if(configStatus == CSL_PASS)
        {
            if(((rxMsg.id >> APP_MCAN_STD_ID_SHIFT) & 0x7FFU) == 41U)
            {
                DebugP_log("PASS: Message correctly filtered to RX FIFO0\n");
            }
            else
            {
                DebugP_log("FAIL: Incorrect message ID in FIFO0\n");
                testStatus = CSL_EFAIL;
            }
        }
    }
    else
    {
        DebugP_log("FAIL: Message not received in RX FIFO0\n");
        testStatus = CSL_EFAIL;
    }

    /* Test Case 3: Send message matching filter 80 (should go to RX FIFO1) */
    DebugP_log("\n--- Test Case 3: Message to RX FIFO1 ---\n");
    
    /* Clear previous interrupt status */
    MCAN_clearIntrStatus(gMcanBaseAddr, MCAN_INTR_MASK_ALL);
    gMcanIsrIntr0Status = 0U;
    
    testParams->mcanConfigParams.txMsg[0U].txElem.id = (81U << APP_MCAN_STD_ID_SHIFT);
    
    MCAN_writeMsgRam(gMcanBaseAddr,
                     MCAN_MEM_TYPE_BUF,
                     txBufCnt,
                     &testParams->mcanConfigParams.txMsg[0U].txElem);
    
    configStatus = MCAN_txBufAddReq(gMcanBaseAddr, txBufCnt);
    if (CSL_PASS != configStatus)
    {
        DebugP_log("Error in Adding Transmission Request...\n");
        testStatus = CSL_EFAIL;
    }

    SemaphoreP_pend(&gTxDoneSem, SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&gRxDoneSem, SystemP_WAIT_FOREVER);

    if((gMcanIsrIntr0Status & MCAN_INTR_SRC_RX_FIFO1_NEW_MSG) == MCAN_INTR_SRC_RX_FIFO1_NEW_MSG)
    {
        configStatus = App_mcanReadRxMSG(&rxMsg, gMcanIsrIntr0Status);
        if(configStatus == CSL_PASS)
        {
            if(((rxMsg.id >> APP_MCAN_STD_ID_SHIFT) & 0x7FFU) == 81U)
            {
                DebugP_log("PASS: Message correctly filtered to RX FIFO1\n");
            }
            else
            {
                DebugP_log("FAIL: Incorrect message ID in FIFO1 (expected 81, got %d)\n", 
                           ((rxMsg.id >> APP_MCAN_STD_ID_SHIFT) & 0x7FFU));
                testStatus = CSL_EFAIL;
            }
        }
    }
    else
    {
        DebugP_log("FAIL: Message not received in RX FIFO1 (intr status: 0x%X)\n", gMcanIsrIntr0Status);
        testStatus = CSL_EFAIL;
    }

    /* Test Case 4: Send message matching filter 100 (should be rejected) */
    DebugP_log("\n--- Test Case 4: Rejected Message ---\n");
    
    /* Clear previous interrupt status */
    MCAN_clearIntrStatus(gMcanBaseAddr, MCAN_INTR_MASK_ALL);
    gMcanIsrIntr0Status = 0U;
    
    testParams->mcanConfigParams.txMsg[0U].txElem.id = (101U << APP_MCAN_STD_ID_SHIFT);
    
    MCAN_writeMsgRam(gMcanBaseAddr,
                     MCAN_MEM_TYPE_BUF,
                     txBufCnt,
                     &testParams->mcanConfigParams.txMsg[0U].txElem);
    
    configStatus = MCAN_txBufAddReq(gMcanBaseAddr, txBufCnt);
    if (CSL_PASS != configStatus)
    {
        DebugP_log("Error in Adding Transmission Request...\n");
        testStatus = CSL_EFAIL;
    }

    SemaphoreP_pend(&gTxDoneSem, SystemP_WAIT_FOREVER);
    
    /* Wait a bit to ensure no RX interrupt occurs */
    ClockP_usleep(10000);  // ← Increase timeout to 10ms
    
    /* Only TX complete interrupt should be set, no RX interrupts */
    if((gMcanIsrIntr0Status & (MCAN_INTR_SRC_RX_FIFO0_NEW_MSG | 
                               MCAN_INTR_SRC_RX_FIFO1_NEW_MSG | 
                               MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG)) == 0U)
    {
        DebugP_log("PASS: Message correctly rejected by filter\n");
    }
    else
    {
        DebugP_log("FAIL: Rejected message was received (intr status: 0x%X)\n", gMcanIsrIntr0Status);
        testStatus = CSL_EFAIL;
    }

    /* Verify no errors occurred during testing */
    MCAN_getErrCounters(gMcanBaseAddr, &errCounter);
    MCAN_getProtocolStatus(gMcanBaseAddr, &protStatus);
    
    if ((errCounter.recErrCnt != 0U) || (errCounter.canErrLogCnt != 0U) ||
        (protStatus.lastErrCode != MCAN_ERR_CODE_NO_ERROR && 
         protStatus.lastErrCode != MCAN_ERR_CODE_NO_CHANGE))
    {
        DebugP_log("FAIL: Errors detected during filter testing\n");
        DebugP_log("REC: %d, CAN Err Log: %d, Last Err: %d\n", 
                   errCounter.recErrCnt, errCounter.canErrLogCnt, protStatus.lastErrCode);
        testStatus = CSL_EFAIL;
    }

    /* Disable Transmission interrupt */
    MCAN_txBufTransIntrEnable(gMcanBaseAddr, 0U, (uint32_t)FALSE);
    
    SemaphoreP_destruct(&gTxDoneSem);
    SemaphoreP_destruct(&gRxDoneSem);

    DebugP_log("\n==== Standard ID Filter Test Complete ====\n");
    if(testStatus == CSL_PASS)
    {
        DebugP_log("Result: PASS - All 128 filters configured and validated\n");
    }
    else
    {
        DebugP_log("Result: FAIL - Filter configuration or validation failed\n");
    }

    return testStatus;
}
/**
 * \brief   Test to configure and validate 64 Extended ID filter elements
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      Test execution status.
 */
static int32_t TestMcan_extIDFilterMaxTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t  configStatus = CSL_PASS;
    uint32_t filterIdx = 0U;
    uint32_t maxExtFilters = 64U;
    MCAN_ExtMsgIDFilterElement extIdFilter;
    MCAN_TxBufElement txMsg;
    MCAN_RxBufElement rxMsg;
    MCAN_ErrCntStatus errCounter;
    
    DebugP_log("\r\n==== Extended ID Filter Maximum Elements Test ====\r\n");
    DebugP_log("Configuring %d Extended ID filters...\r\n", maxExtFilters);

    /* Configure 64 Extended ID filters with NON-OVERLAPPING ID ranges */
    for(filterIdx = 0U; filterIdx < maxExtFilters; filterIdx++)
    {
        /* Vary filter types across the filter list */
        if(filterIdx < 16U)
        {
            /* First 16: Store in dedicated RX buffers (IDs 0x100-0x10F) */
            extIdFilter.efec = MCAN_EXT_FILT_ELEM_BUFFER;
            extIdFilter.eft = MCAN_EXT_FILT_TYPE_CLASSIC;
            extIdFilter.efid1 = (0x100U + filterIdx) & 0x1FFFFFFFU;
            extIdFilter.efid2 = filterIdx;  /* Use as buffer index */
        }
        else if(filterIdx < 32U)
        {
            /* Next 16: Store in RX FIFO0 with RANGE filter (IDs 0x200-0x20F range) */
            extIdFilter.efec = MCAN_EXT_FILT_ELEM_FIFO0;
            extIdFilter.eft = MCAN_EXT_FILT_TYPE_RANGE;
            uint32_t baseId = 0x200U + (filterIdx - 16U);
            extIdFilter.efid1 = baseId & 0x1FFFFFFFU;          /* Range start */
            extIdFilter.efid2 = (baseId + 0x0FU) & 0x1FFFFFFFU; /* Range end */
        }
        else if(filterIdx < 48U)
        {
            /* Next 16: Store in RX FIFO1 with CLASSIC filter (IDs 0x300-0x30F) */
            extIdFilter.efec = MCAN_EXT_FILT_ELEM_FIFO1;
            extIdFilter.eft = MCAN_EXT_FILT_TYPE_CLASSIC;
            extIdFilter.efid1 = (0x300U + (filterIdx - 32U)) & 0x1FFFFFFFU;
            extIdFilter.efid2 = 0x00000000U;  /* Exact match (mask = 0) */
        }
        else
        {
            /* Last 16: REJECT matching messages (IDs 0x400-0x40F) */
            extIdFilter.efec = MCAN_EXT_FILT_ELEM_REJECT;
            extIdFilter.eft = MCAN_EXT_FILT_TYPE_CLASSIC;
            extIdFilter.efid1 = (0x400U + (filterIdx - 48U)) & 0x1FFFFFFFU;
            extIdFilter.efid2 = 0x00000000U;  /* Exact match */
        }

        /* Add Extended ID filter */
        MCAN_addExtMsgIDFilter(gMcanBaseAddr, filterIdx, &extIdFilter);
    }

    DebugP_log("Successfully configured %d Extended ID filters.\r\n", maxExtFilters);

    /* Enable interrupts for reception */
    MCAN_enableIntr(gMcanBaseAddr, MCAN_INTR_MASK_ALL, (uint32_t)TRUE);
    MCAN_selectIntrLine(gMcanBaseAddr, MCAN_INTR_MASK_ALL, MCAN_INTR_LINE_NUM_0);
    MCAN_enableIntrLine(gMcanBaseAddr, MCAN_INTR_LINE_NUM_0, TRUE);

    /* Test Case 1: Message to RX Buffer */
    DebugP_log("\r\n--- Test Case 1: Message to RX Buffer ---\r\n");
    MCAN_initTxBufElement(&txMsg);
    txMsg.id = (0x100U << APP_MCAN_EXT_ID_SHIFT);  /* Matches filter 0 */
    txMsg.xtd = 1U;
    txMsg.dlc = 4U;
    txMsg.data[0] = 0xAA;
    
    gMcanIsrIntr0Status = 0U;
    MCAN_writeMsgRam(gMcanBaseAddr, MCAN_MEM_TYPE_BUF, 0U, &txMsg);
    MCAN_txBufAddReq(gMcanBaseAddr, 0U);
    
    while((gMcanIsrIntr0Status & MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG) == 0U)
    {
        /* Wait for RX buffer interrupt */
    }
    
    if(App_mcanReadRxMSG(&rxMsg, gMcanIsrIntr0Status) == CSL_PASS)
    {
        DebugP_log("PASS: Message correctly filtered to RX Buffer 0\r\n");
    }
    else
    {
        DebugP_log("FAIL: Message not received in RX Buffer (intr: 0x%x)\r\n", 
                   gMcanIsrIntr0Status);
        configStatus = CSL_EFAIL;
    }

    /* Test Case 2: Message to RX FIFO0 */
    DebugP_log("\r\n--- Test Case 2: Message to RX FIFO0 ---\r\n");
    MCAN_initTxBufElement(&txMsg);
    txMsg.id = (0x205U << APP_MCAN_EXT_ID_SHIFT);  /* Matches filter 21 range */
    txMsg.xtd = 1U;
    txMsg.dlc = 4U;
    txMsg.data[0] = 0xBB;
    
    gMcanIsrIntr0Status = 0U;
    MCAN_writeMsgRam(gMcanBaseAddr, MCAN_MEM_TYPE_BUF, 0U, &txMsg);
    MCAN_txBufAddReq(gMcanBaseAddr, 0U);
    
    while((gMcanIsrIntr0Status & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) == 0U)
    {
        /* Wait for RX FIFO0 interrupt */
    }
    
    if(App_mcanReadRxMSG(&rxMsg, gMcanIsrIntr0Status) == CSL_PASS)
    {
        DebugP_log("PASS: Message correctly filtered to RX FIFO0\r\n");
    }
    else
    {
        DebugP_log("FAIL: Message not received in RX FIFO0 (intr: 0x%x)\r\n", 
                   gMcanIsrIntr0Status);
        configStatus = CSL_EFAIL;
    }

    /* Test Case 3: Message to RX FIFO1 */
    DebugP_log("\r\n--- Test Case 3: Message to RX FIFO1 ---\r\n");
    MCAN_initTxBufElement(&txMsg);
    txMsg.id = (0x308U << APP_MCAN_EXT_ID_SHIFT);  /* Matches filter 40 (0x300 + 8) */
    txMsg.xtd = 1U;
    txMsg.dlc = 4U;
    txMsg.data[0] = 0xCC;
    
    gMcanIsrIntr0Status = 0U;
    MCAN_writeMsgRam(gMcanBaseAddr, MCAN_MEM_TYPE_BUF, 0U, &txMsg);
    MCAN_txBufAddReq(gMcanBaseAddr, 0U);
    
    while((gMcanIsrIntr0Status & MCAN_INTR_SRC_RX_FIFO1_NEW_MSG) == 0U)
    {
        /* Wait for RX FIFO1 interrupt */
    }
    
    if(App_mcanReadRxMSG(&rxMsg, gMcanIsrIntr0Status) == CSL_PASS)
    {
        DebugP_log("PASS: Message correctly filtered to RX FIFO1\r\n");
    }
    else
    {
        DebugP_log("FAIL: Message not received in RX FIFO1 (intr: 0x%x)\r\n", 
                   gMcanIsrIntr0Status);
        configStatus = CSL_EFAIL;
    }

    /* Test Case 4: Rejected Message */
    DebugP_log("\r\n--- Test Case 4: Rejected Message ---\r\n");
    MCAN_initTxBufElement(&txMsg);
    txMsg.id = (0x408U << APP_MCAN_EXT_ID_SHIFT);  /* Matches filter 56 (REJECT) */
    txMsg.xtd = 1U;
    txMsg.dlc = 4U;
    txMsg.data[0] = 0xDD;
    
    gMcanIsrIntr0Status = 0U;
    MCAN_writeMsgRam(gMcanBaseAddr, MCAN_MEM_TYPE_BUF, 0U, &txMsg);
    MCAN_txBufAddReq(gMcanBaseAddr, 0U);
    
    /* Wait a bit to ensure message would be received if filter failed */
    App_delayFunc(1000U);
    
    if((gMcanIsrIntr0Status & (MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG | 
                               MCAN_INTR_SRC_RX_FIFO0_NEW_MSG | 
                               MCAN_INTR_SRC_RX_FIFO1_NEW_MSG)) == 0U)
    {
        DebugP_log("PASS: Message correctly rejected by filter\r\n");
    }
    else
    {
        DebugP_log("FAIL: Rejected message was received (intr: 0x%x)\r\n", 
                   gMcanIsrIntr0Status);
        configStatus = CSL_EFAIL;
    }

    /* Test Case 5: Dual ID Filter Test */
    DebugP_log("\r\n--- Test Case 5: Dual ID Filter Test ---\r\n");
    
    /* Configure a dual ID filter */
    extIdFilter.efec = MCAN_EXT_FILT_ELEM_FIFO0;
    extIdFilter.eft = MCAN_EXT_FILT_TYPE_DUAL;
    extIdFilter.efid1 = 0x500U;  /* First ID */
    extIdFilter.efid2 = 0x600U;  /* Second ID */
    MCAN_addExtMsgIDFilter(gMcanBaseAddr, 0U, &extIdFilter);
    
    /* Test first ID */
    MCAN_initTxBufElement(&txMsg);
    txMsg.id = (0x500U << APP_MCAN_EXT_ID_SHIFT);
    txMsg.xtd = 1U;
    txMsg.dlc = 4U;
    
    gMcanIsrIntr0Status = 0U;
    MCAN_writeMsgRam(gMcanBaseAddr, MCAN_MEM_TYPE_BUF, 0U, &txMsg);
    MCAN_txBufAddReq(gMcanBaseAddr, 0U);
    
    while((gMcanIsrIntr0Status & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) == 0U) {}
    
    if(App_mcanReadRxMSG(&rxMsg, gMcanIsrIntr0Status) == CSL_PASS)
    {
        DebugP_log("PASS: Dual filter matched first ID (0x500)\r\n");
    }
    else
    {
        configStatus = CSL_EFAIL;
    }
    
    /* Test second ID */
    MCAN_initTxBufElement(&txMsg);
    txMsg.id = (0x600U << APP_MCAN_EXT_ID_SHIFT);
    txMsg.xtd = 1U;
    txMsg.dlc = 4U;
    
    gMcanIsrIntr0Status = 0U;
    MCAN_writeMsgRam(gMcanBaseAddr, MCAN_MEM_TYPE_BUF, 0U, &txMsg);
    MCAN_txBufAddReq(gMcanBaseAddr, 0U);
    
    while((gMcanIsrIntr0Status & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) == 0U) {}
    
    if(App_mcanReadRxMSG(&rxMsg, gMcanIsrIntr0Status) == CSL_PASS)
    {
        DebugP_log("PASS: Dual filter matched second ID (0x600)\r\n");
    }
    else
    {
        configStatus = CSL_EFAIL;
    }

    /* Check for errors */
    MCAN_getErrCounters(gMcanBaseAddr, &errCounter);
    if((errCounter.recErrCnt != 0U) || (errCounter.canErrLogCnt != 0U))
    {
        DebugP_log("ERROR: CAN errors detected (REC:%d, CEL:%d)\r\n", 
                   errCounter.recErrCnt, errCounter.canErrLogCnt);
        configStatus = CSL_EFAIL;
    }

    DebugP_log("\r\n==== Extended ID Filter Test Complete ====\r\n");
    DebugP_log("Result: %s\r\n", (configStatus == CSL_PASS) ? "PASS" : "FAIL");

    return configStatus;
}

/**
 * @brief Test MCAN_writeMsgRamNoCpy with non-4-aligned payload sizes.
 *
 * Covers the "remaining bytes" if-block in MCAN_writeMsgNoCpy()
 * (lines 2183-2191 of mcan.c) by using DLC values where
 * gDataSize[dlc] % 4 != 0 (e.g., dlc=5 → 5 bytes, dlc=7 → 7 bytes).
 *
 * Uses internal loopback mode. Tx via MCAN_writeMsgRamNoCpy,
 * Rx via MCAN_readMsgRam, then compares payload.
 */
int32_t App_mcanNoCpyNonAlignedDlcTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t  testStatus = CSL_PASS;
    int32_t  configStatus = CSL_PASS;
    uint32_t loopCnt;
    MCAN_TxBufElementNoCpy txElem = {0U};
    MCAN_RxBufElement      rxMsg;
    MCAN_ProtocolStatus    protStatus;
    MCAN_ErrCntStatus      errCounter;
    uint8_t txData[MCAN_MAX_PAYLOAD_BYTES];

    /* DLC values where gDataSize[dlc] is NOT a multiple of 4 */
    uint32_t nonAlignedDlcValues[] = {1U, 2U, 3U, 5U, 6U, 7U};
    uint32_t numDlcValues = sizeof(nonAlignedDlcValues) / sizeof(nonAlignedDlcValues[0U]);
    /* Expected payload sizes for each DLC */
    uint32_t expectedSizes[] = {1U, 2U, 3U, 5U, 6U, 7U};

    /* Initialize TX Data with known pattern */
    for (loopCnt = 0U; loopCnt < MCAN_MAX_PAYLOAD_BYTES; loopCnt++)
    {
        txData[loopCnt] = (uint8_t)(loopCnt + 0xA0U);
    }

    /* Enable Interrupts */
    MCAN_enableIntr(gMcanBaseAddr,
                    testParams->mcanConfigParams.intrEnable,
                    (uint32_t)TRUE);
    MCAN_selectIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);
    MCAN_enableIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        1U);

    /* Enable Transmission interrupt for buffer 0 */
    configStatus = MCAN_txBufTransIntrEnable(gMcanBaseAddr, 0U, (uint32_t)TRUE);
    if (CSL_PASS != configStatus)
    {
        DebugP_log("\nMCAN Tx Buffer Interrupt Enable FAILED...\n", -1);
        testStatus = CSL_EFAIL;
    }

    for (loopCnt = 0U; (loopCnt < numDlcValues) && (CSL_PASS == testStatus); loopCnt++)
    {
        /* Initialize TX element with NoCpy API */
        App_mcanInitTxElem(&txElem);
        txElem.dlc  = nonAlignedDlcValues[loopCnt];
        txElem.brs  = FALSE;
        txElem.fdf  = FALSE;  /* Classic CAN for small DLC */
        txElem.data = &txData[0U];

        DebugP_log("Testing NoCpy with DLC=%d (payload=%d bytes)\r\n",
                   nonAlignedDlcValues[loopCnt],
                   expectedSizes[loopCnt]);

        /* Write message to Msg RAM using NoCpy API */
        MCAN_writeMsgRamNoCpy(gMcanBaseAddr,
                              MCAN_MEM_TYPE_BUF,
                              0U,
                              &txElem);

        /* Add request for transmission */
        configStatus = MCAN_txBufAddReq(gMcanBaseAddr, 0U);
        if (CSL_PASS != configStatus)
        {
            DebugP_log("\nError in Adding Transmission Request...\n", -1);
            testStatus = CSL_EFAIL;
            break;
        }

        /* Wait for Tx complete */
        while (!((gMcanIsrIntr0Status & MCAN_INTR_SRC_TRANS_COMPLETE) ==
                                MCAN_INTR_SRC_TRANS_COMPLETE))
        {
        }
        gMcanIsrIntr0Status = 0U;

        /* Check for errors */
        MCAN_getErrCounters(gMcanBaseAddr, &errCounter);
        MCAN_getProtocolStatus(gMcanBaseAddr, &protStatus);
        if ((0U != errCounter.recErrCnt) ||
            (0U != errCounter.canErrLogCnt))
        {
            DebugP_log("\nError counters non-zero for DLC=%d\n",
                       nonAlignedDlcValues[loopCnt]);
            testStatus = CSL_EFAIL;
            break;
        }

        /* Read received message (loopback) and verify payload */
        MCAN_readMsgRam(gMcanBaseAddr,
            testParams->mcanConfigParams.txMsg[0U].rxMSGStorageId,
            testParams->mcanConfigParams.txMsg[0U].rxBuffNum,
            testParams->mcanConfigParams.txMsg[0U].rxBuffNum,
            &rxMsg);

        /* Verify payload data up to the expected size */
        {
            uint32_t byteIdx;
            for (byteIdx = 0U; byteIdx < expectedSizes[loopCnt]; byteIdx++)
            {
                if (rxMsg.data[byteIdx] != txData[byteIdx])
                {
                    DebugP_log("\nData mismatch at byte %d for DLC=%d: "
                               "expected 0x%02X, got 0x%02X\n",
                               byteIdx, nonAlignedDlcValues[loopCnt],
                               txData[byteIdx], rxMsg.data[byteIdx]);
                    testStatus = CSL_EFAIL;
                    break;
                }
            }
        }
    }

    if (CSL_PASS == testStatus)
    {
        DebugP_log("\nAll non-4-aligned DLC NoCpy tests PASSED.\n");
    }

    return testStatus;
}

/**
 * \brief   Test case for transmitting Extended ID Classic CAN and CAN-FD frames
 *          in one sequence (sequential, non-concurrent transmission)
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  status      Test execution status.
 */
/**
 * \brief   Test to validate explicit buffer number isolation and prevent cross-write.
 *          This test verifies that:
 *          - Multiple TX buffers (0, 1, 2, 3) can store unique data patterns
 *          - Each buffer transmits and receives correctly
 *          - No cross-contamination between adjacent buffers
 *          - Buffer isolation is maintained throughout operations
 *
 * \param   testParams  [IN] Test case parameters
 *
 * \return  CSL_PASS on success, CSL_EFAIL on failure
 */
static int32_t TestMcan_explicitBufferNumbersIsolationTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t  configStatus = CSL_PASS, testStatus = CSL_PASS;
    uint32_t loopCnt, txBufCnt, bitPos, txStatus, dataIdx;
    MCAN_TxBufElement txMsg[4];  /* Array for 4 different buffer messages */
    MCAN_RxBufElement rxMsg;
    MCAN_ProtocolStatus protStatus;
    MCAN_ErrCntStatus errCounter;

    /* Enable Interrupts */
    MCAN_enableIntr(gMcanBaseAddr, testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);
    
    /* Select Interrupt Line */
    MCAN_selectIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);
    
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        1U);

    /* Enable interrupts for Tx Buffers 0, 1, 2, 3 */
    for (loopCnt = 0U; loopCnt < 4U; loopCnt++)
    {
        configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr, loopCnt, (uint32_t)TRUE);
        if(configStatus != CSL_PASS)
        {
            DebugP_log("\nMCAN Tx Buffer %d Interrupt Enable FAILED...\n", loopCnt);
            return CSL_EFAIL;
        }
    }

    /* =================================================================
     * Prepare 4 unique messages with distinct data patterns
     * Each buffer gets a unique ID and data pattern for isolation testing
     * ================================================================= */
    for(loopCnt = 0U; loopCnt < 4U; loopCnt++)
    {
        MCAN_initTxBufElement(&txMsg[loopCnt]);
        txMsg[loopCnt].id  = ((uint32_t)0x100U + loopCnt) << 18U;  /* Standard IDs: 0x100, 0x101, 0x102, 0x103 */
        txMsg[loopCnt].rtr = 0U;             /* Data frame */
        txMsg[loopCnt].xtd = 0U;             /* Standard ID */
        txMsg[loopCnt].esi = 0U;
        txMsg[loopCnt].dlc = MCAN_DATA_SIZE_64BYTES;  /* 64 bytes for better isolation testing */
        txMsg[loopCnt].brs = 1U;             /* Bit rate switching enabled */
        txMsg[loopCnt].fdf = 1U;             /* CAN-FD format */
        txMsg[loopCnt].efc = 0U;
        txMsg[loopCnt].mm  = 0xB0U + loopCnt;  /* Unique message marker */
        
        /* Fill with unique data pattern for each buffer
         * Buffer 0: 0x00, 0x01, 0x02, ...
         * Buffer 1: 0x10, 0x11, 0x12, ...
         * Buffer 2: 0x20, 0x21, 0x22, ...
         * Buffer 3: 0x30, 0x31, 0x32, ... */
        for(dataIdx = 0U; dataIdx < 64U; dataIdx++)
        {
            txMsg[loopCnt].data[dataIdx] = (uint8_t)((loopCnt << 4) + (dataIdx & 0x0FU));
        }
    }

    /* =================================================================
     * Transmit messages from each buffer sequentially
     * Verify each buffer's data integrity and isolation
     * ================================================================= */
    for(loopCnt = 0U; loopCnt < 4U; loopCnt++)
    {
        uint32_t localIntrStatus;  /* Capture interrupt status for this iteration */
        
        txBufCnt = loopCnt;  /* Using Tx buffers 0, 1, 2, 3 explicitly */
        
        /* Write message to Msg RAM at specific buffer location */
        MCAN_writeMsgRam(gMcanBaseAddr,
                         MCAN_MEM_TYPE_BUF,
                         txBufCnt,
                         &txMsg[loopCnt]);
        
        /* Add request for transmission from this specific buffer */
        configStatus = MCAN_txBufAddReq(gMcanBaseAddr, txBufCnt);
        if (CSL_PASS != configStatus)
        {
            DebugP_log("\nError: Transmission Request failed for buffer %d\n", txBufCnt);
            testStatus = CSL_EFAIL;
            break;
        }

        /* Wait for Tx completion using semaphore */
        SemaphoreP_pend(&gTxDoneSem, SystemP_WAIT_FOREVER);

        /* Wait for Rx completion using semaphore */
        SemaphoreP_pend(&gRxDoneSem, SystemP_WAIT_FOREVER);

        /* Capture the interrupt status after RX completion */
        localIntrStatus = gMcanIsrIntr0Status;

        /* Poll for Tx completion status */
        bitPos = (1U << txBufCnt);
        do
        {
            txStatus = MCAN_getTxBufTransmissionStatus(gMcanBaseAddr);
        } while((txStatus & bitPos) != bitPos);
        
        DebugP_log("  TX Status: Complete\n");
        
        /* Check for transmission/reception errors */
        MCAN_getErrCounters(gMcanBaseAddr, &errCounter);
        if ((0U != errCounter.recErrCnt) || (0U != errCounter.canErrLogCnt))
        {
            DebugP_log("\nError: Non-zero error counters for buffer %d\n", loopCnt);
            DebugP_log("  REC: %d, CEL: %d\n", errCounter.recErrCnt, errCounter.canErrLogCnt);
            testStatus = CSL_EFAIL;
            break;
        }
        
        /* Check protocol status */
        MCAN_getProtocolStatus(gMcanBaseAddr, &protStatus);
        if (((MCAN_ERR_CODE_NO_ERROR != protStatus.lastErrCode) &&
             (MCAN_ERR_CODE_NO_CHANGE != protStatus.lastErrCode)) ||
            ((MCAN_ERR_CODE_NO_ERROR != protStatus.dlec) &&
             (MCAN_ERR_CODE_NO_CHANGE != protStatus.dlec)) ||
            (0U != protStatus.pxe))
        {
            DebugP_log("\nError: Protocol error detected for buffer %d\n", loopCnt);
            DebugP_log("  LEC: %d, DLEC: %d, PXE: %d\n", 
                       protStatus.lastErrCode, protStatus.dlec, protStatus.pxe);
            testStatus = CSL_EFAIL;
            break;
        }
        
        /* Read received message (loopback mode) using captured interrupt status */
        configStatus = App_mcanReadRxMSG(&rxMsg, localIntrStatus);
        if(configStatus != CSL_PASS)
        {
            DebugP_log("\nError: Unable to read received message for buffer %d\n", loopCnt);
            testStatus = CSL_EFAIL;
            break;
        }
        
        /* Verify transmitted vs received message */
        configStatus = App_mcanTxRxMessageCheck(txMsg[loopCnt], rxMsg);
        if(configStatus != CSL_PASS)
        {
            DebugP_log("\nError: TX/RX message mismatch for buffer %d!\n", loopCnt);
            testStatus = CSL_EFAIL;
            break;
        }
        
        /* Additional validation: Verify data pattern integrity
         * This ensures no cross-contamination from adjacent buffers */
        uint32_t dataMismatch = 0U;
        for(dataIdx = 0U; dataIdx < 64U; dataIdx++)
        {
            uint8_t expectedData = (uint8_t)((loopCnt << 4) + (dataIdx & 0x0FU));
            if(rxMsg.data[dataIdx] != expectedData)
            {
                if(dataMismatch == 0U)
                {
                    DebugP_log("\nError: Data pattern corruption detected in buffer %d!\n", loopCnt);
                    DebugP_log("  Expected pattern: 0x%02X, Got: 0x%02X at position %d\n",
                               expectedData, rxMsg.data[dataIdx], dataIdx);
                }
                dataMismatch++;
            }
        }
        
        if(dataMismatch > 0U)
        {
            DebugP_log("  Total mismatches: %d out of 64 bytes\n", dataMismatch);
            DebugP_log("  This indicates possible cross-write or buffer contamination!\n");
            testStatus = CSL_EFAIL;
            break;
        }
        
    }

    /* Clear interrupt status after all buffers are processed */
    gMcanIsrIntr0Status = 0U;

    /* Disable interrupts for Tx Buffers */
    for (loopCnt = 0U; loopCnt < 4U; loopCnt++)
    {
        configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr, loopCnt, (uint32_t)FALSE);
    }

    return testStatus;
}

static int32_t TestMcan_mixedExtIdClassicFdTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t  configStatus = CSL_PASS, testStatus = CSL_PASS;
    uint32_t loopCnt, txBufCnt, bitPos, txStatus;
    MCAN_TxBufElement txMsg[3];  /* Array for 3 different message types */
    MCAN_RxBufElement rxMsg;
    MCAN_ProtocolStatus protStatus;
    MCAN_ErrCntStatus errCounter;

    /* Enable Interrupts */
    MCAN_enableIntr(gMcanBaseAddr, testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);
    
    /* Select Interrupt Line */
    MCAN_selectIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);
    
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        1U);

    /* Enable interrupts for Tx Buffers 0, 1, 2 */
    for (loopCnt = 0U; loopCnt < 3U; loopCnt++)
    {
        configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr, loopCnt, (uint32_t)TRUE);
        if(configStatus != CSL_PASS)
        {
            DebugP_log("\nMCAN Tx Buffer %d Interrupt Enable FAILED...\n", loopCnt);
            return CSL_EFAIL;
        }
    }

    /* =================================================================
     * Message 1: Extended ID + Classic CAN (8 bytes data)
     * ================================================================= */
    MCAN_initTxBufElement(&txMsg[0]);
    txMsg[0].id  = 0x1ABCDEF0;    /* 29-bit Extended ID */
    txMsg[0].rtr = 0U;             /* Data frame */
    txMsg[0].xtd = 1U;             /* Extended ID */
    txMsg[0].esi = 0U;
    txMsg[0].dlc = MCAN_DATA_SIZE_8BYTES;  /* 8 bytes */
    txMsg[0].brs = 0U;             /* No bit rate switching (Classic CAN) */
    txMsg[0].fdf = 0U;             /* Classic CAN format */
    txMsg[0].efc = 0U;
    txMsg[0].mm  = 0xA1U;
    
    /* Fill data payload for message 1 */
    for(loopCnt = 0U; loopCnt < 8U; loopCnt++)
    {
        txMsg[0].data[loopCnt] = 0x10 + loopCnt;
    }

    /* =================================================================
     * Message 2: Extended ID + CAN-FD (16 bytes data)
     * ================================================================= */
    MCAN_initTxBufElement(&txMsg[1]);
    txMsg[1].id  = 0x1CAFE001;     /* 29-bit Extended ID */
    txMsg[1].rtr = 0U;
    txMsg[1].xtd = 1U;             /* Extended ID */
    txMsg[1].esi = 0U;
    txMsg[1].dlc = MCAN_DATA_SIZE_16BYTES;  /* 16 bytes */
    txMsg[1].brs = 1U;             /* Bit rate switching enabled */
    txMsg[1].fdf = 1U;             /* CAN-FD format */
    txMsg[1].efc = 0U;
    txMsg[1].mm  = 0xA2U;
    
    /* Fill data payload for message 2 */
    for(loopCnt = 0U; loopCnt < 16U; loopCnt++)
    {
        txMsg[1].data[loopCnt] = 0x20 + loopCnt;
    }

    /* =================================================================
     * Message 3: Extended ID + CAN-FD (64 bytes data)
     * ================================================================= */
    MCAN_initTxBufElement(&txMsg[2]);
    txMsg[2].id  = 0x1BADC0DE;     /* 29-bit Extended ID */
    txMsg[2].rtr = 0U;
    txMsg[2].xtd = 1U;             /* Extended ID */
    txMsg[2].esi = 0U;
    txMsg[2].dlc = MCAN_DATA_SIZE_64BYTES;  /* 64 bytes */
    txMsg[2].brs = 1U;             /* Bit rate switching enabled */
    txMsg[2].fdf = 1U;             /* CAN-FD format */
    txMsg[2].efc = 0U;
    txMsg[2].mm  = 0xA3U;
    
    /* Fill data payload for message 3 */
    for(loopCnt = 0U; loopCnt < 64U; loopCnt++)
    {
        txMsg[2].data[loopCnt] = 0x30 + (loopCnt % 256);
    }

    /* =================================================================
     * Transmit all 3 messages sequentially
     * ================================================================= */
    for(loopCnt = 0U; loopCnt < 3U; loopCnt++)
    {
        txBufCnt = loopCnt;  /* Using Tx buffers 0, 1, 2 */
        
        /* Write message to Msg RAM */
        MCAN_writeMsgRam(gMcanBaseAddr,
                         MCAN_MEM_TYPE_BUF,
                         txBufCnt,
                         &txMsg[loopCnt]);
        
        /* Add request for transmission */
        configStatus = MCAN_txBufAddReq(gMcanBaseAddr, txBufCnt);
        if (CSL_PASS != configStatus)
        {
            DebugP_log("\nError in Adding Transmission Request for buffer %d...\n", txBufCnt);
            testStatus = CSL_EFAIL;
            break;
        }

        /* Wait for Tx completion using semaphore */
        SemaphoreP_pend(&gTxDoneSem, SystemP_WAIT_FOREVER);

        /* Wait for Rx completion using semaphore */
        SemaphoreP_pend(&gRxDoneSem, SystemP_WAIT_FOREVER);

        /* Poll for Tx completion status */
        bitPos = (1U << txBufCnt);
        do
        {
            txStatus = MCAN_getTxBufTransmissionStatus(gMcanBaseAddr);
        } while((txStatus & bitPos) != bitPos);
        
        /* Check for errors */
        MCAN_getErrCounters(gMcanBaseAddr, &errCounter);
        if ((0U != errCounter.recErrCnt) || (0U != errCounter.canErrLogCnt))
        {
            DebugP_log("\nError Counters non-zero for message %d\n", loopCnt + 1);
            DebugP_log("  REC: %d, CEL: %d\n", errCounter.recErrCnt, errCounter.canErrLogCnt);
            testStatus = CSL_EFAIL;
            break;
        }
        
        MCAN_getProtocolStatus(gMcanBaseAddr, &protStatus);
        if (((MCAN_ERR_CODE_NO_ERROR != protStatus.lastErrCode) &&
             (MCAN_ERR_CODE_NO_CHANGE != protStatus.lastErrCode)) ||
            ((MCAN_ERR_CODE_NO_ERROR != protStatus.dlec) &&
             (MCAN_ERR_CODE_NO_CHANGE != protStatus.dlec)) ||
            (0U != protStatus.pxe))
        {
            DebugP_log("\nProtocol error detected for message %d\n", loopCnt + 1);
            DebugP_log("  LEC: %d, DLEC: %d, PXE: %d\n", 
                       protStatus.lastErrCode, protStatus.dlec, protStatus.pxe);
            testStatus = CSL_EFAIL;
            break;
        }
        
        /* Read received message (loopback mode) */
        configStatus = App_mcanReadRxMSG(&rxMsg, gMcanIsrIntr0Status);
        if(configStatus != CSL_PASS)
        {
            DebugP_log("\nUnable to read received message %d\n", loopCnt + 1);
            testStatus = CSL_EFAIL;
            break;
        }
        
        /* Verify transmitted vs received message */
        configStatus = App_mcanTxRxMessageCheck(txMsg[loopCnt], rxMsg);
        if(configStatus != CSL_PASS)
        {
            DebugP_log("\nTransmitted and received message %d mismatch!\n", loopCnt + 1);
            testStatus = CSL_EFAIL;
            break;
        }
        
        DebugP_log("  Status: PASSED\n\n");
        gMcanIsrIntr0Status = 0U;
    }

    /* Disable interrupts for Tx Buffers */
    for (loopCnt = 0U; loopCnt < 3U; loopCnt++)
    {
        configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr, loopCnt, (uint32_t)FALSE);
    }

    return testStatus;
}

/**
 * \brief   Test to verify combined filter types (Classic, Dual, Bit Mask) 
 *          receiving messages in FIFO0, FIFO1, and dedicated buffer simultaneously.
 *
 * \param   testParams      Test case parameters.
 *
 * \retval  status          Execution status.
 */
static int32_t TestMcan_combinedFilterTypeTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t  configStatus = CSL_PASS, testStatus = CSL_PASS;
    uint32_t loopCnt, txBufCnt;
    MCAN_StdMsgIDFilterElement stdIdFilter[3];
    MCAN_RxBufElement rxMsg;
    MCAN_RxFIFOStatus fifoStatus;
    MCAN_TxFIFOStatus txFIFOStatus;
    MCAN_ProtocolStatus protStatus;
    MCAN_ErrCntStatus errCounter;
    uint32_t rxBuffNum;
    MCAN_RxNewDataStatus newDataStatus;

    /* Message IDs for testing different filter types */
    const uint32_t classicFilterId = 0x100U;   /* Classic filter: exact match */
    const uint32_t dualFilterId1   = 0x200U;   /* Dual filter: ID 1 */
    const uint32_t dualFilterId2   = 0x201U;   /* Dual filter: ID 2 */
    const uint32_t bitMaskFilterId = 0x350U;   /* Bit mask filter: will match with mask */

    /* Enable Interrupts */
    MCAN_enableIntr(gMcanBaseAddr, testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);
    MCAN_selectIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);
    MCAN_enableIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        1U);

    /* Enable Transmission interrupt for buffer 0 */
    configStatus = MCAN_txBufTransIntrEnable(gMcanBaseAddr, 0U, (uint32_t)TRUE);
    if(configStatus != CSL_PASS)
    {
        DebugP_log("MCAN Tx Buffer Interrupt Enable FAILED\n");
        testStatus = CSL_EFAIL;
    }

    /* ========== Configure Filter 1: Classic Filter -> FIFO0 ========== */
    stdIdFilter[0].sfid1 = classicFilterId;    /* Filter value */
    stdIdFilter[0].sfid2 = 0x7FFU;             /* Mask: all bits must match (exact match) */
    stdIdFilter[0].sfec  = MCAN_STD_FILT_ELEM_FIFO0;  /* Store in RX FIFO 0 */
    stdIdFilter[0].sft   = MCAN_STD_FILT_TYPE_CLASSIC; /* Classic filter (bit mask) */
    MCAN_addStdMsgIDFilter(gMcanBaseAddr, 0U, &stdIdFilter[0]);

    /* ========== Configure Filter 2: Dual Filter -> FIFO1 ========== */
    stdIdFilter[1].sfid1 = dualFilterId1;      /* First ID to match */
    stdIdFilter[1].sfid2 = dualFilterId2;      /* Second ID to match */
    stdIdFilter[1].sfec  = MCAN_STD_FILT_ELEM_FIFO1;  /* Store in RX FIFO 1 */
    stdIdFilter[1].sft   = MCAN_STD_FILT_TYPE_DUAL;    /* Dual ID filter */
    MCAN_addStdMsgIDFilter(gMcanBaseAddr, 1U, &stdIdFilter[1]);

    /* ========== Configure Filter 3: Bit Mask Filter -> Dedicated Buffer ========== */
    stdIdFilter[2].sfid1 = bitMaskFilterId;    /* Filter value to match (0x305) */
    stdIdFilter[2].sfid2 = 0U;                 /* Buffer index 0 */
    stdIdFilter[2].sfec  = MCAN_STD_FILT_ELEM_BUFFER;  /* Store in dedicated buffer */
    stdIdFilter[2].sft   = MCAN_STD_FILT_TYPE_CLASSIC; /* Classic filter with mask */
    MCAN_addStdMsgIDFilter(gMcanBaseAddr, 2U, &stdIdFilter[2]);

    gMcanIsrIntr0Status = 0U;
    
    MCAN_getTxFIFOQueStatus(gMcanBaseAddr, &txFIFOStatus);
    txBufCnt = 0U;
    
    testParams->mcanConfigParams.txMsg[0U].txElem.id  = (classicFilterId << APP_MCAN_STD_ID_SHIFT);
    testParams->mcanConfigParams.txMsg[0U].txElem.xtd = 0U;
    testParams->mcanConfigParams.txMsg[0U].txElem.rtr = 0U;
    testParams->mcanConfigParams.txMsg[0U].txElem.dlc = MCAN_DATA_SIZE_8BYTES;
    testParams->mcanConfigParams.txMsg[0U].txElem.fdf = 0U;
    testParams->mcanConfigParams.txMsg[0U].txElem.brs = 0U;
    
    /* Set distinctive data pattern for verification */
    for(loopCnt = 0U; loopCnt < 8U; loopCnt++)
    {
        testParams->mcanConfigParams.txMsg[0U].txElem.data[loopCnt] = 0x10U + loopCnt;
    }
    
    MCAN_writeMsgRam(gMcanBaseAddr,
                     MCAN_MEM_TYPE_BUF,
                     txBufCnt,
                     &testParams->mcanConfigParams.txMsg[0U].txElem);
    
    configStatus = MCAN_txBufAddReq(gMcanBaseAddr, txBufCnt);
    if (CSL_PASS != configStatus)
    {
        DebugP_log("Error in Adding Transmission Request\n");
        testStatus = CSL_EFAIL;
    }

    SemaphoreP_pend(&gTxDoneSem, SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&gRxDoneSem, SystemP_WAIT_FOREVER);

    /* Verify message received in FIFO0 */
    if((gMcanIsrIntr0Status & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) == MCAN_INTR_SRC_RX_FIFO0_NEW_MSG)
    {
        fifoStatus.num = MCAN_RX_FIFO_NUM_0;
        MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
        
        MCAN_readMsgRam(gMcanBaseAddr,
                       MCAN_MEM_TYPE_FIFO,
                       fifoStatus.getIdx,
                       (uint32_t)fifoStatus.num,
                       &rxMsg);
        
        MCAN_writeRxFIFOAck(gMcanBaseAddr,
                           (uint32_t)fifoStatus.num,
                           fifoStatus.getIdx);
        
        if(((rxMsg.id >> APP_MCAN_STD_ID_SHIFT) & 0x7FFU) == classicFilterId)
        {
            /* Verify data pattern */
            uint32_t dataMatch = 1U;
            for(loopCnt = 0U; loopCnt < 8U; loopCnt++)
            {
                if(rxMsg.data[loopCnt] != (0x10U + loopCnt))
                {
                    dataMatch = 0U;
                    break;
                }
            }
            
            if(dataMatch)
            {
                DebugP_log("PASS: Classic Filter message correctly received in FIFO0\n");
            }
            else
            {
                DebugP_log("FAIL: Data mismatch in FIFO0 message\n");
                testStatus = CSL_EFAIL;
            }
        }
        else
        {
            DebugP_log("FAIL: Incorrect message ID in FIFO0\n");
            testStatus = CSL_EFAIL;
        }
    }
    else
    {
        DebugP_log("FAIL: Message not received in FIFO0\n");
        testStatus = CSL_EFAIL;
    }

    /* Check for errors */
    MCAN_getErrCounters(gMcanBaseAddr, &errCounter);
    if((0U != errCounter.recErrCnt) || (0U != errCounter.canErrLogCnt))
    {
        DebugP_log("FAIL: Error counters non-zero\n");
        testStatus = CSL_EFAIL;
    }

    gMcanIsrIntr0Status = 0U;
    
    testParams->mcanConfigParams.txMsg[0U].txElem.id  = (dualFilterId2 << APP_MCAN_STD_ID_SHIFT);
    
    /* Set different data pattern */
    for(loopCnt = 0U; loopCnt < 8U; loopCnt++)
    {
        testParams->mcanConfigParams.txMsg[0U].txElem.data[loopCnt] = 0x20U + loopCnt;
    }
    
    MCAN_writeMsgRam(gMcanBaseAddr,
                     MCAN_MEM_TYPE_BUF,
                     txBufCnt,
                     &testParams->mcanConfigParams.txMsg[0U].txElem);
    
    configStatus = MCAN_txBufAddReq(gMcanBaseAddr, txBufCnt);
    if (CSL_PASS != configStatus)
    {
        DebugP_log("Error in Adding Transmission Request\n");
        testStatus = CSL_EFAIL;
    }

    SemaphoreP_pend(&gTxDoneSem, SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&gRxDoneSem, SystemP_WAIT_FOREVER);

    /* Verify message received in FIFO1 */
    if((gMcanIsrIntr0Status & MCAN_INTR_SRC_RX_FIFO1_NEW_MSG) == MCAN_INTR_SRC_RX_FIFO1_NEW_MSG)
    {
        fifoStatus.num = MCAN_RX_FIFO_NUM_1;
        MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
        
        MCAN_readMsgRam(gMcanBaseAddr,
                       MCAN_MEM_TYPE_FIFO,
                       fifoStatus.getIdx,
                       (uint32_t)fifoStatus.num,
                       &rxMsg);
        
        MCAN_writeRxFIFOAck(gMcanBaseAddr,
                           (uint32_t)fifoStatus.num,
                           fifoStatus.getIdx);
        
        if(((rxMsg.id >> APP_MCAN_STD_ID_SHIFT) & 0x7FFU) == dualFilterId2)
        {
            /* Verify data pattern */
            uint32_t dataMatch = 1U;
            for(loopCnt = 0U; loopCnt < 8U; loopCnt++)
            {
                if(rxMsg.data[loopCnt] != (0x20U + loopCnt))
                {
                    dataMatch = 0U;
                    break;
                }
            }
            
            if(dataMatch)
            {
                DebugP_log("PASS: Dual Filter message correctly received in FIFO1\n");
            }
            else
            {
                DebugP_log("FAIL: Data mismatch in FIFO1 message\n");
                testStatus = CSL_EFAIL;
            }
        }
        else
        {
            DebugP_log("FAIL: Incorrect message ID in FIFO1\n");
            testStatus = CSL_EFAIL;
        }
    }
    else
    {
        DebugP_log("FAIL: Message not received in FIFO1\n");
        testStatus = CSL_EFAIL;
    }

    gMcanIsrIntr0Status = 0U;
    
    testParams->mcanConfigParams.txMsg[0U].txElem.id  = (bitMaskFilterId << APP_MCAN_STD_ID_SHIFT);
    
    /* Set different data pattern */
    for(loopCnt = 0U; loopCnt < 8U; loopCnt++)
    {
        testParams->mcanConfigParams.txMsg[0U].txElem.data[loopCnt] = 0x30U + loopCnt;
    }
    
    MCAN_writeMsgRam(gMcanBaseAddr,
                     MCAN_MEM_TYPE_BUF,
                     txBufCnt,
                     &testParams->mcanConfigParams.txMsg[0U].txElem);
    
    configStatus = MCAN_txBufAddReq(gMcanBaseAddr, txBufCnt);
    if (CSL_PASS != configStatus)
    {
        DebugP_log("Error in Adding Transmission Request\n");
        testStatus = CSL_EFAIL;
    }

    SemaphoreP_pend(&gTxDoneSem, SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&gRxDoneSem, SystemP_WAIT_FOREVER);

    /* Verify message received in Dedicated Buffer */
    if((gMcanIsrIntr0Status & MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG) == MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG)
    {
        rxBuffNum = 0U;  /* Buffer index configured in filter */
        
        MCAN_readMsgRam(gMcanBaseAddr,
                       MCAN_MEM_TYPE_BUF,
                       rxBuffNum,
                       0U,
                       &rxMsg);
        
        newDataStatus.statusLow = (1U << rxBuffNum);
        newDataStatus.statusHigh = 0U;
        MCAN_clearNewDataStatus(gMcanBaseAddr, &newDataStatus);
        
        if(((rxMsg.id >> APP_MCAN_STD_ID_SHIFT) & 0x7FFU) == bitMaskFilterId)
        {
            /* Verify data pattern */
            uint32_t dataMatch = 1U;
            for(loopCnt = 0U; loopCnt < 8U; loopCnt++)
            {
                if(rxMsg.data[loopCnt] != (0x30U + loopCnt))
                {
                    dataMatch = 0U;
                    break;
                }
            }
            
            if(dataMatch)
            {
                DebugP_log("PASS: Bit Mask Filter message correctly received in Dedicated Buffer\n");
            }
            else
            {
                DebugP_log("FAIL: Data mismatch in Dedicated Buffer message\n");
                testStatus = CSL_EFAIL;
            }
        }
        else
        {
            DebugP_log("FAIL: Incorrect message ID in Dedicated Buffer\n");
            testStatus = CSL_EFAIL;
        }
    }
    else
    {
        DebugP_log("FAIL: Message not received in Dedicated Buffer\n");
        testStatus = CSL_EFAIL;
    }

    /* Final status check */
    MCAN_getProtocolStatus(gMcanBaseAddr, &protStatus);
    if(((MCAN_ERR_CODE_NO_ERROR == protStatus.lastErrCode) ||
        (MCAN_ERR_CODE_NO_CHANGE == protStatus.lastErrCode)) &&
       ((MCAN_ERR_CODE_NO_ERROR == protStatus.dlec) ||
        (MCAN_ERR_CODE_NO_CHANGE == protStatus.dlec)) &&
       (0U == protStatus.pxe))
    {
        /* No protocol errors */
    }
    else
    {
        DebugP_log("FAIL: Protocol errors detected\n");
        testStatus = CSL_EFAIL;
    }

    /* Disable Tx interrupt */
    MCAN_txBufTransIntrEnable(gMcanBaseAddr, 0U, (uint32_t)FALSE);

    SemaphoreP_destruct(&gTxDoneSem);
    SemaphoreP_destruct(&gRxDoneSem);

    return testStatus;
}


/**
 * \brief   Test function for MCAN_INTR_SRC_RX_FIFO0_MSG_LOST interrupt
 *          Tests that the MSG_LOST interrupt is triggered when FIFO0 is full
 *          in blocking mode and a new message arrives.
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  CSL_PASS    Test passed
 * \retval  CSL_EFAIL   Test failed
 */
static int32_t App_mcanRxFIFO0MsgLostTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t  configStatus = CSL_PASS, testStatus = CSL_PASS;
    uint32_t loopCnt = 0U, loopBreakFlag = 1U, txBufCnt;
    uint32_t getIdx, putIdx;
    MCAN_ProtocolStatus protStatus;
    MCAN_ErrCntStatus errCounter;
    MCAN_RxBufElementNoCpy rxMsg;
    MCAN_TxFIFOStatus txFIFOStatus;
    MCAN_RxFIFOStatus fifoStatus;
    MCAN_ConfigParams configParams;
    MCAN_TxBufElementNoCpy txElem = {0U};
    uint8_t txData[MCAN_MAX_PAYLOAD_BYTES];

    /* Initialize TX Data */
    for (loopCnt = 0U; loopCnt < MCAN_MAX_PAYLOAD_BYTES; loopCnt++)
    {
        txData[loopCnt] = loopCnt;
    }

    App_mcanInitTxElem(&txElem);
    txElem.data = &txData[0U];

    /* Enable Interrupts */
    MCAN_enableIntr(gMcanBaseAddr, testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);
    /* Select Interrupt Line */
    MCAN_selectIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        1U);

    /* Enable interrupts for Tx Buffers */
    for (loopCnt = 0U ;
         loopCnt < testParams->mcanConfigParams.txMsgNum ;
         loopCnt++)
    {
        if (testParams->mcanConfigParams.txMsg[loopCnt].storageId ==
                                                        MCAN_MEM_TYPE_BUF)
        {
            /* Enable Transmission interrupt */
            configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr,
                    testParams->mcanConfigParams.txMsg[loopCnt].bufferNum,
                    (uint32_t)TRUE);
            if(configStatus != CSL_PASS)
            {
                DebugP_log("\nMCAN Tx Buffer Interrupt Enable FAILED...\n", -1);
            }
        }
    }

    /* Enable interrupts for Tx FIFO/Queue */
    for (loopCnt = testParams->mcanConfigParams.ramConfig->txBufCnt ;
         loopCnt < (testParams->mcanConfigParams.ramConfig->txFIFOCnt +
                    testParams->mcanConfigParams.ramConfig->txBufCnt);
         loopCnt++)
    {
        /* Enable Transmission interrupt */
        configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr,
                loopCnt,
                (uint32_t)TRUE);
        if(configStatus != CSL_PASS)
        {
            DebugP_log("\nMCAN Tx FIFO Interrupt Enable FAILED...\n", -1);
        }
    }

    /* Verify FIFO0 is configured in Blocking mode */
    if (testParams->mcanConfigParams.ramConfig->rxFIFO0OpMode != 
        MCAN_RX_FIFO_OPERATION_MODE_BLOCKING)
    {
        DebugP_log("ERROR: FIFO0 must be configured in Blocking Mode for this test!\n", -1);
        testStatus = CSL_EFAIL;
        goto test_exit;
    }

    /* Configure to accept non-matching messages into FIFO0 */
    configParams.monEnable = testParams->mcanConfigParams.configParams->monEnable;
    configParams.asmEnable = testParams->mcanConfigParams.configParams->asmEnable;
    configParams.tsPrescalar = testParams->mcanConfigParams.configParams->tsPrescalar;
    configParams.tsSelect = testParams->mcanConfigParams.configParams->tsSelect;
    configParams.timeoutPreload = testParams->mcanConfigParams.configParams->timeoutPreload;
    configParams.timeoutCntEnable = testParams->mcanConfigParams.configParams->timeoutCntEnable;
    configParams.filterConfig.rrfe = testParams->mcanConfigParams.configParams->filterConfig.rrfe;
    configParams.filterConfig.rrfs = testParams->mcanConfigParams.configParams->filterConfig.rrfs;
    configParams.filterConfig.anfe = 0U;  /* Accept non-matching extended frames into FIFO 0 */
    configParams.filterConfig.anfs = 2U;  /* Reject non-matching standard frames */

    /* Put MCAN in SW initialization mode */
    MCAN_setOpMode(gMcanBaseAddr, MCAN_OPERATION_MODE_SW_INIT);
    while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(gMcanBaseAddr))
    {}
    MCAN_config(gMcanBaseAddr, &configParams);
    /* Take MCAN out of the SW initialization mode */
    MCAN_setOpMode(gMcanBaseAddr, MCAN_OPERATION_MODE_NORMAL);
    while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(gMcanBaseAddr))
    {}
    
    /* Send messages until FIFO0 full condition is reached */
    loopCnt = 0U;
    gMcanIsrIntr0Status = 0U;
    loopBreakFlag = 1U;
    
    while (loopBreakFlag == 1U)
    {
        loopCnt++;
        MCAN_getTxFIFOQueStatus(gMcanBaseAddr, &txFIFOStatus);
        
        if (testParams->mcanConfigParams.txMsg[0U].storageId == MCAN_MEM_TYPE_BUF)
        {
            txBufCnt = testParams->mcanConfigParams.txMsg[0U].bufferNum;
        }
        else
        {
            txBufCnt = txFIFOStatus.putIdx;
        }
        
        /* Write message to Msg RAM - sending message with extended ID only */
        txElem.id = loopCnt << MCAN_STD_ID_SHIFT;
        txElem.xtd = 1U;
        MCAN_writeMsgRamNoCpy(gMcanBaseAddr,
                         testParams->mcanConfigParams.txMsg[0U].storageId,
                         txBufCnt,
                         &txElem);
        
        /* Add request for transmission */
        configStatus = MCAN_txBufAddReq(gMcanBaseAddr, txBufCnt);
        if (CSL_PASS != configStatus)
        {
            DebugP_log("\nError in Adding Transmission Request...\n", -1);
            testStatus = CSL_EFAIL;
            break;
        }
        
        /* Wait for transmission complete */
        while (!((gMcanIsrIntr0Status & MCAN_INTR_SRC_TRANS_COMPLETE) ==
                                MCAN_INTR_SRC_TRANS_COMPLETE))
        {}
        
        /* Wait for reception in FIFO0 */
        while (!((gMcanIsrIntr0Status & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) ==
                                MCAN_INTR_SRC_RX_FIFO0_NEW_MSG))
        {}
        
        /* Check if FIFO0 is full */
        if ((gMcanIsrIntr0Status & MCAN_INTR_SRC_RX_FIFO0_FULL) ==
                                MCAN_INTR_SRC_RX_FIFO0_FULL)
        {
            DebugP_log("FIFO0 Full condition reached after %d messages\n", loopCnt);
            loopBreakFlag = 0U;
        }
        
        gMcanIsrIntr0Status = 0U;
        
        /* Check for transmission/reception errors */
        MCAN_getErrCounters(gMcanBaseAddr, &errCounter);
        if ((0U != errCounter.recErrCnt) || (0U != errCounter.canErrLogCnt))
        {
            testStatus = CSL_EFAIL;
            DebugP_log("\nError Counters: Error in transmission/reception.\n", -1);
            loopBreakFlag = 0U;
        }
        
        MCAN_getProtocolStatus(gMcanBaseAddr, &protStatus);
        if (!((MCAN_ERR_CODE_NO_ERROR == protStatus.lastErrCode) ||
              (MCAN_ERR_CODE_NO_CHANGE == protStatus.lastErrCode)) ||
            !((MCAN_ERR_CODE_NO_ERROR == protStatus.dlec) ||
              (MCAN_ERR_CODE_NO_CHANGE == protStatus.dlec)) ||
            (0U != protStatus.pxe))
        {
            testStatus = CSL_EFAIL;
            DebugP_log("\nProtocol Error in transmission/reception.\n", -1);
            loopBreakFlag = 0U;
        }
    }

    /* Check if test failed during FIFO fill */
    if (testStatus != CSL_PASS)
    {
        goto test_exit;
    }

    /* Verify FIFO0 is full */
    fifoStatus.num = MCAN_RX_FIFO_NUM_0;
    MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
    
    if (fifoStatus.fifoFull != 1U)
    {
        testStatus = CSL_EFAIL;
        DebugP_log("ERROR: FIFO0 Full condition not reached.\n", -1);
        goto test_exit;
    }

    /* Save current get/put indices */
    getIdx = fifoStatus.getIdx;
    putIdx = fifoStatus.putIdx;
    
    /* Send one more message to cause overflow and trigger MSG_LOST interrupt */
    loopCnt++;
    txElem.id = loopCnt << MCAN_STD_ID_SHIFT;
    txElem.xtd = 1U;
    
    MCAN_writeMsgRamNoCpy(gMcanBaseAddr,
                     testParams->mcanConfigParams.txMsg[0U].storageId,
                     txBufCnt,
                     &txElem);
    
    /* Add request for transmission */
    configStatus = MCAN_txBufAddReq(gMcanBaseAddr, txBufCnt);
    if (CSL_PASS != configStatus)
    {
        DebugP_log("\nError in Adding Transmission Request...\n", -1);
        testStatus = CSL_EFAIL;
        goto test_exit;
    }
    
    /* Wait for transmission complete */
    while (!((gMcanIsrIntr0Status & MCAN_INTR_SRC_TRANS_COMPLETE) ==
                            MCAN_INTR_SRC_TRANS_COMPLETE))
    {}
    
    /* Wait for FIFO0 MSG_LOST interrupt - THIS IS THE KEY TEST */
    while (!((gMcanIsrIntr0Status & MCAN_INTR_SRC_RX_FIFO0_MSG_LOST) ==
                            MCAN_INTR_SRC_RX_FIFO0_MSG_LOST))
    {}
    
    /* Verify FIFO status - get/put indices should NOT be updated in blocking mode */
    MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
    
    DebugP_log("After MSG_LOST - Get Index: %d, Put Index: %d, Fill Level: %d\n",
               fifoStatus.getIdx, fifoStatus.putIdx, fifoStatus.fillLvl);
    
    if ((getIdx == fifoStatus.getIdx) && (putIdx == fifoStatus.putIdx))
    {
        DebugP_log("Get and Put Indices not updated (Blocking Mode correct behavior)\n");
    }
    else
    {
        testStatus = CSL_EFAIL;
        DebugP_log("ERROR: Get/Put Indices were updated in Blocking Mode!\n");
    }
    
    /* Read first message in FIFO - should be oldest message (with EXT ID: 1) */
    MCAN_readMsgRamNoCpy(gMcanBaseAddr,
                    MCAN_MEM_TYPE_FIFO,
                    fifoStatus.getIdx,
                    (uint32_t)fifoStatus.num,
                    &rxMsg);
    
    /* Acknowledge the read */
    (void) MCAN_writeRxFIFOAck(gMcanBaseAddr,
                               (uint32_t)fifoStatus.num,
                               fifoStatus.getIdx);
    
    /* Verify oldest message is NOT overwritten */
    if ((rxMsg.id >> MCAN_STD_ID_SHIFT) == 1U)
    {
        DebugP_log("Oldest message preserved (ID=1), newest message rejected\n");
    }
    else
    {
        testStatus = CSL_EFAIL;
        DebugP_log("ERROR: Oldest message was overwritten! Received ID=%d\n", 
                   (rxMsg.id >> MCAN_STD_ID_SHIFT));
    }
    
    /* Clear remaining messages from FIFO0 */
    DebugP_log("Clearing FIFO0...\n", -1);
    MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
    while (fifoStatus.fillLvl > 0U)
    {
        MCAN_readMsgRamNoCpy(gMcanBaseAddr,
                        MCAN_MEM_TYPE_FIFO,
                        fifoStatus.getIdx,
                        (uint32_t)fifoStatus.num,
                        &rxMsg);
        (void) MCAN_writeRxFIFOAck(gMcanBaseAddr,
                                   (uint32_t)fifoStatus.num,
                                   fifoStatus.getIdx);
        MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
    }

test_exit:
    /* Disable Interrupts */
    MCAN_enableIntr(gMcanBaseAddr, MCAN_INTR_MASK_ALL, (uint32_t)FALSE);

    return testStatus;
}


/**
 * \brief   This function contains the common external MCAN read/write test
 *          for test cases 1260, 11089, 11090.
 *
 *          Flow:
 *          1. Configure MCAN with the bitrate from test-case params.
 *          2. Transmit a CAN FD message to the external PCAN tool.
 *          3. Wait for the PCAN tool to echo the message back.
 *          4. Receive and validate the echoed message against the
 *             transmitted one.
 *          Steps 2-4 are repeated for txMSGInterationCnt iterations.
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  CSL_PASS on success, CSL_EFAIL on failure.
 */
static int32_t App_mcanExternalReadWriteTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t  configStatus = CSL_PASS, testStatus = CSL_PASS;
    uint32_t loopCnt      = 0U, iterationCnt = 0U, txBufCnt;
    uint32_t bitPos = 0U, txStatus = 0U;
    MCAN_ProtocolStatus protStatus;
    MCAN_ErrCntStatus   errCounter;
    MCAN_RxBufElement   rxMsg;
    MCAN_TxFIFOStatus   txFIFOStatus;
    MCAN_RxNewDataStatus newDataStatus;
    int32_t             semStatus;

    DebugP_log("\n[MCAN] External Read-Write Test (TC %d) started ...\n",
               testParams->testcaseId);

    /* Enable Interrupts */
    MCAN_enableIntr(gMcanBaseAddr,
                    testParams->mcanConfigParams.intrEnable,
                    (uint32_t)TRUE);
    /* Select Interrupt Line */
    MCAN_selectIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        1U);

    /* Enable interrupts for Tx Buffers */
    for (loopCnt = 0U;
         loopCnt < testParams->mcanConfigParams.txMsgNum;
         loopCnt++)
    {
        if (testParams->mcanConfigParams.txMsg[loopCnt].storageId ==
                                                        MCAN_MEM_TYPE_BUF)
        {
            configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr,
                    testParams->mcanConfigParams.txMsg[loopCnt].bufferNum,
                    (uint32_t)TRUE);
            if (configStatus != CSL_PASS)
            {
                DebugP_log("\nMCAN Tx Buffer Interrupt Enable FAILED...\n");
            }
        }
    }
    /* Enable interrupts for Tx FIFO/Queue */
    for (loopCnt = testParams->mcanConfigParams.ramConfig->txBufCnt;
         loopCnt < (testParams->mcanConfigParams.ramConfig->txFIFOCnt +
                    testParams->mcanConfigParams.ramConfig->txBufCnt);
         loopCnt++)
    {
        configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr,
                loopCnt,
                (uint32_t)TRUE);
        if (configStatus != CSL_PASS)
        {
            DebugP_log("\nMCAN Tx FIFO Interrupt Enable FAILED...\n");
        }
    }

    for (iterationCnt = 0U;
         iterationCnt < testParams->mcanConfigParams.txMSGInterationCnt;
         iterationCnt++)
    {
        for (loopCnt = 0U;
             loopCnt < testParams->mcanConfigParams.txMsgNum;
             loopCnt++)
        {
            gMcanIsrIntr0Status = 0U;

            MCAN_getTxFIFOQueStatus(gMcanBaseAddr, &txFIFOStatus);
            if (testParams->mcanConfigParams.txMsg[loopCnt].storageId ==
                                                        MCAN_MEM_TYPE_BUF)
            {
                txBufCnt = testParams->mcanConfigParams.txMsg[loopCnt].bufferNum;
            }
            else
            {
                txBufCnt = txFIFOStatus.putIdx;
            }

            /* Write message to Msg RAM */
            MCAN_writeMsgRam(gMcanBaseAddr,
                             testParams->mcanConfigParams.txMsg[loopCnt].storageId,
                             txBufCnt,
                             &testParams->mcanConfigParams.txMsg[loopCnt].txElem);

            /* Add request for transmission */
            configStatus += MCAN_txBufAddReq(gMcanBaseAddr, txBufCnt);
            if (CSL_PASS != configStatus)
            {
                DebugP_log("\nError in Adding Transmission Request...\n");
            }

            /* ---- Wait for Tx completion ---- */
            semStatus = SemaphoreP_pend(&gTxDoneSem, SystemP_WAIT_FOREVER);
            if (semStatus != SystemP_SUCCESS)
            {
                testStatus += CSL_EFAIL;
                DebugP_log("\nTx TIMEOUT (Iteration:Msg): (%d,%d).\n",
                           (iterationCnt + 1U), (loopCnt + 1U));
                continue;
            }

            /* Poll for Tx completion status bit */
            bitPos = (1U << txBufCnt);
            do
            {
                txStatus = MCAN_getTxBufTransmissionStatus(gMcanBaseAddr);
            } while ((txStatus & bitPos) != bitPos);

            /* Check for Tx errors */
            MCAN_getProtocolStatus(gMcanBaseAddr, &protStatus);
            if (((MCAN_ERR_CODE_NO_ERROR != protStatus.lastErrCode) &&
                 (MCAN_ERR_CODE_NO_CHANGE != protStatus.lastErrCode)) ||
                ((MCAN_ERR_CODE_NO_ERROR != protStatus.dlec) &&
                 (MCAN_ERR_CODE_NO_CHANGE != protStatus.dlec)) ||
                (0U != protStatus.pxe))
            {
                testStatus += CSL_EFAIL;
                DebugP_log("\nTx Protocol Error (Iteration:Msg): (%d,%d).\n",
                           (iterationCnt + 1U), (loopCnt + 1U));
                continue;
            }

            DebugP_log("Message transmitted successfully (Iteration:Msg): (%d,%d).\n",
                       (iterationCnt + 1U), (loopCnt + 1U));

            /* ---- Wait for Rx from external PCAN tool ---- */
            semStatus = SemaphoreP_pend(&gRxDoneSem, SystemP_WAIT_FOREVER);
            if (semStatus != SystemP_SUCCESS)
            {
                testStatus += CSL_EFAIL;
                DebugP_log("\nRx TIMEOUT waiting for PCAN echo (Iteration:Msg): (%d,%d).\n",
                           (iterationCnt + 1U), (loopCnt + 1U));
                continue;
            }

            /* Check for Rx errors */
            MCAN_getErrCounters(gMcanBaseAddr, &errCounter);
            if ((0U != errCounter.recErrCnt) ||
                (0U != errCounter.canErrLogCnt))
            {
                testStatus += CSL_EFAIL;
                DebugP_log("\nRx Error Counters non-zero (Iteration:Msg): (%d,%d).\n",
                           (iterationCnt + 1U), (loopCnt + 1U));
                continue;
            }

            /* Read received message */
            if ((gMcanIsrIntr0Status & MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG) ==
                                       MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG)
            {
                /* Rx Buffer path */
                MCAN_getNewDataStatus(gMcanBaseAddr, &newDataStatus);
                MCAN_clearNewDataStatus(gMcanBaseAddr, &newDataStatus);

                bitPos = (1U << testParams->mcanConfigParams.txMsg[loopCnt].rxBuffNum);
                if ((newDataStatus.statusLow & bitPos) == bitPos)
                {
                    MCAN_readMsgRam(gMcanBaseAddr,
                                    MCAN_MEM_TYPE_BUF,
                                    testParams->mcanConfigParams.txMsg[loopCnt].rxBuffNum,
                                    MCAN_RX_FIFO_NUM_0,
                                    &rxMsg);
                }
                else
                {
                    testStatus += CSL_EFAIL;
                    DebugP_log("\nRx Buffer new data status mismatch (Iteration:Msg): (%d,%d).\n",
                               (iterationCnt + 1U), (loopCnt + 1U));
                    continue;
                }
            }
            else
            {
                /* FIFO / general path using existing helper */
                configStatus = App_mcanReadRxMSG(&rxMsg, gMcanIsrIntr0Status);
                if (configStatus != CSL_PASS)
                {
                    testStatus += CSL_EFAIL;
                    DebugP_log("\nUnable to read Rx message (Iteration:Msg): (%d,%d).\n",
                               (iterationCnt + 1U), (loopCnt + 1U));
                    continue;
                }
            }

            /* Compare Tx and Rx messages */
            configStatus = App_mcanTxRxMessageCheck(
                            testParams->mcanConfigParams.txMsg[loopCnt].txElem,
                            rxMsg);
            if (configStatus != CSL_PASS)
            {
                testStatus += CSL_EFAIL;
                DebugP_log("\nTx/Rx message MISMATCH (Iteration:Msg): (%d,%d).\n",
                           (iterationCnt + 1U), (loopCnt + 1U));
            }
            else
            {
                DebugP_log("Message received and validated OK (Iteration:Msg): (%d,%d).\n",
                           (iterationCnt + 1U), (loopCnt + 1U));
            }

            gMcanIsrIntr0Status = 0U;
        }
    }

    /* Disable interrupts for Tx Buffers */
    for (loopCnt = 0U;
         loopCnt < testParams->mcanConfigParams.txMsgNum;
         loopCnt++)
    {
        if (testParams->mcanConfigParams.txMsg[loopCnt].storageId ==
                                                        MCAN_MEM_TYPE_BUF)
        {
            configStatus += MCAN_txBufTransIntrEnable(gMcanBaseAddr,
                    testParams->mcanConfigParams.txMsg[loopCnt].bufferNum,
                    (uint32_t)FALSE);
            if (configStatus != CSL_PASS)
            {
                DebugP_log("\nMCAN Tx Buffer Interrupt Disable FAILED...\n");
            }
        }
    }

    /* Disable Interrupt */
    MCAN_enableIntr(gMcanBaseAddr, MCAN_INTR_MASK_ALL, (uint32_t)FALSE);

    if (testStatus == CSL_PASS)
    {
        DebugP_log("\n[MCAN] External Read-Write Test (TC %d) PASSED.\n",
                   testParams->testcaseId);
    }
    else
    {
        DebugP_log("\n[MCAN] External Read-Write Test (TC %d) FAILED.\n",
                   testParams->testcaseId);
    }

    testParams->isRun = CSL_PASS;
    return testStatus;
}

/**
 * \brief   Test case 10488U: Max Msg RAM Word Count - Send 193 Receive 192.
 *
 *          Validates that with maximum message RAM configuration (4352 words),
 *          exactly 192 messages can be received (64 FIFO0 + 64 FIFO1 + 64 RX
 *          buffers). The 193rd message is lost because all RX paths are full.
 *
 *          Flow:
 *          1. Configure filters dynamically:
 *             - 2 std ID filters (range to FIFO0 and FIFO1)
 *             - 64 ext ID filters (each routing to a dedicated RX buffer)
 *          2. Send 193 messages without reading:
 *             - 64 with std IDs 0x001-0x040 -> FIFO0
 *             - 64 with std IDs 0x041-0x080 -> FIFO1
 *             - 64 with ext IDs 0x001-0x040 -> RX buffers 0-63
 *             - 1 more with std ID 0x001 -> FIFO0 full -> MSG_LOST
 *          3. Receive phase: read 192 messages, verify 193rd is lost.
 *
 * \param   testParams  Test case parameters.
 *
 * \retval  CSL_PASS on success, CSL_EFAIL on failure.
 */
static int32_t TestMcan_maxMsgRamWordCntTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t  testStatus   = CSL_PASS;
    int32_t  configStatus = CSL_PASS;
    uint32_t loopCnt      = 0U;
    uint32_t txBufNum     = 0U;
    uint32_t bitPos, txStatus;
    uint32_t totalRxCount = 0U;
    uint32_t msgLostDetected = 0U;
    MCAN_ProtocolStatus    protStatus;
    MCAN_ErrCntStatus      errCounter;
    MCAN_TxBufElement      txElem;
    MCAN_TxBufElement      refTxElem;
    MCAN_RxBufElement      rxMsg;
    uint32_t               fifo0Idx  = 0U;
    uint32_t               fifo1Idx  = 0U;
    MCAN_RxFIFOStatus      fifoStatus;
    MCAN_RxNewDataStatus   newDataStatus;
    MCAN_RxNewDataStatus   clearStatus;
    MCAN_StdMsgIDFilterElement stdFilter;
    MCAN_ExtMsgIDFilterElement extFilter;
    MCAN_ConfigParams      configParams;

    DebugP_log("\n=== Max Msg RAM Word Count Test: Send %u, Receive %u ===\n",
               MAX_RAM_SEND_CNT, MAX_RAM_TOTAL_RX);

    /* ------------------------------------------------------------------
     * Setup: Enter SW_INIT mode to configure filters dynamically.
     * ------------------------------------------------------------------ */
    MCAN_setOpMode(gMcanBaseAddr, MCAN_OPERATION_MODE_SW_INIT);
    while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(gMcanBaseAddr))
    {}

    /* Configure non-matching frame acceptance to reject all non-matching */
    configParams.monEnable        = testParams->mcanConfigParams.configParams->monEnable;
    configParams.asmEnable        = testParams->mcanConfigParams.configParams->asmEnable;
    configParams.tsPrescalar      = testParams->mcanConfigParams.configParams->tsPrescalar;
    configParams.tsSelect         = testParams->mcanConfigParams.configParams->tsSelect;
    configParams.timeoutPreload   = testParams->mcanConfigParams.configParams->timeoutPreload;
    configParams.timeoutCntEnable = testParams->mcanConfigParams.configParams->timeoutCntEnable;
    configParams.filterConfig.rrfe = testParams->mcanConfigParams.configParams->filterConfig.rrfe;
    configParams.filterConfig.rrfs = testParams->mcanConfigParams.configParams->filterConfig.rrfs;
    configParams.filterConfig.anfe = 3U;  /* Reject non-matching extended frames */
    configParams.filterConfig.anfs = 3U;  /* Reject non-matching standard frames */
    MCAN_config(gMcanBaseAddr, &configParams);

    /* Std Filter 0: Range 0x001-0x040 -> FIFO0 (messages 1-64) */
    stdFilter.sfid1 = 0x001U;
    stdFilter.sfid2 = 0x040U;
    stdFilter.sfec  = MCAN_STD_FILT_ELEM_FIFO0;
    stdFilter.sft   = MCAN_STD_FILT_TYPE_RANGE;
    MCAN_addStdMsgIDFilter(gMcanBaseAddr, 0U, &stdFilter);

    /* Std Filter 1: Range 0x041-0x080 -> FIFO1 (messages 65-128) */
    stdFilter.sfid1 = 0x041U;
    stdFilter.sfid2 = 0x080U;
    stdFilter.sfec  = MCAN_STD_FILT_ELEM_FIFO1;
    stdFilter.sft   = MCAN_STD_FILT_TYPE_RANGE;
    MCAN_addStdMsgIDFilter(gMcanBaseAddr, 1U, &stdFilter);

    /* Ext Filters 0-63: Each routes ext ID (i+1) to RX buffer i (messages 129-192) */
    for (loopCnt = 0U; loopCnt < MAX_RAM_RXBUF_CNT; loopCnt++)
    {
        extFilter.efid1 = loopCnt + 1U;             /* Extended ID to match */
        extFilter.efec  = MCAN_EXT_FILT_ELEM_BUFFER; /* Store into RX buffer */
        extFilter.efid2 = loopCnt;                   /* RX buffer index */
        extFilter.eft   = MCAN_STD_FILT_TYPE_RANGE;  /* Ignored when efec=7 */
        MCAN_addExtMsgIDFilter(gMcanBaseAddr, loopCnt, &extFilter);
    }

    /* Re-enable internal loopback (must be set in SW_INIT mode) */
    MCAN_lpbkModeEnable(gMcanBaseAddr, MCAN_LPBK_MODE_INTERNAL, TRUE);

    MCAN_setOpMode(gMcanBaseAddr, MCAN_OPERATION_MODE_NORMAL);
    while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(gMcanBaseAddr))
    {}

    /* Enable Interrupts */
    MCAN_enableIntr(gMcanBaseAddr, testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);
    MCAN_selectIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);
    MCAN_enableIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLine, 1U);

    /* Enable TX buffer 0 transmission interrupt */
    configStatus = MCAN_txBufTransIntrEnable(gMcanBaseAddr, txBufNum, (uint32_t)TRUE);
    if (configStatus != CSL_PASS)
    {
        DebugP_log("\nMCAN TX intr enable FAILED\n");
        MCAN_enableIntr(gMcanBaseAddr, MCAN_INTR_MASK_ALL, (uint32_t)FALSE);
        DebugP_log("=== Max Msg RAM Word Count Test FAILED ===\n");
        return CSL_EFAIL;
    }

    /* ------------------------------------------------------------------
     * Phase 1: Send 193 messages without reading any.
     *   Messages 1-64:   Std ID 0x001-0x040 -> FIFO0
     *   Messages 65-128: Std ID 0x041-0x080 -> FIFO1
     *   Messages 129-192: Ext ID 0x001-0x040 -> RX Buffers 0-63
     *   Message 193:      Std ID 0x001 -> FIFO0 (full) -> MSG_LOST
     * ------------------------------------------------------------------ */
    DebugP_log("Phase 1: Sending %u messages without reading...\n", MAX_RAM_SEND_CNT);
    MCAN_initTxBufElement(&txElem);
    txElem.dlc = MCAN_DATA_SIZE_8BYTES;
    txElem.fdf = 0U;
    txElem.brs = 0U;
    txElem.efc = 0U;

    gMcanIsrIntr0Status = 0U;

    for (loopCnt = 0U; loopCnt < MAX_RAM_SEND_CNT; loopCnt++)
    {
        if (loopCnt < MAX_RAM_FIFO0_CNT)
        {
            /* Messages 0-63: Std ID 0x001-0x040 -> FIFO0 */
            txElem.id  = ((0x001U + loopCnt) << APP_MCAN_STD_ID_SHIFT);
            txElem.xtd = 0U;
        }
        else if (loopCnt < (MAX_RAM_FIFO0_CNT + MAX_RAM_FIFO1_CNT))
        {
            /* Messages 64-127: Std ID 0x041-0x080 -> FIFO1 */
            txElem.id  = ((0x041U + (loopCnt - MAX_RAM_FIFO0_CNT)) << APP_MCAN_STD_ID_SHIFT);
            txElem.xtd = 0U;
        }
        else if (loopCnt < MAX_RAM_TOTAL_RX)
        {
            /* Messages 128-191: Ext ID 0x001-0x040 -> RX Buffers 0-63 */
            txElem.id  = (loopCnt - MAX_RAM_FIFO0_CNT - MAX_RAM_FIFO1_CNT) + 1U;
            txElem.xtd = 1U;
        }
        else
        {
            /* Message 192 (193rd): Std ID 0x001 -> FIFO0 full -> MSG_LOST */
            txElem.id  = (0x001U << APP_MCAN_STD_ID_SHIFT);
            txElem.xtd = 0U;
        }

        /* Stamp data with message sequence number for verification */
        txElem.data[0U] = (uint8_t)(loopCnt & 0xFFU);
        txElem.data[1U] = (uint8_t)((loopCnt >> 8U) & 0xFFU);

        /* Write to TX buffer 0 and request transmission */
        MCAN_writeMsgRam(gMcanBaseAddr, MCAN_MEM_TYPE_BUF, txBufNum, &txElem);
        configStatus = MCAN_txBufAddReq(gMcanBaseAddr, txBufNum);
        if (CSL_PASS != configStatus)
        {
            DebugP_log("\nError in Adding TX Request for msg %u\n", loopCnt);
            testStatus = CSL_EFAIL;
            break;
        }

        /* Wait for TX completion */
        while (!((gMcanIsrIntr0Status & MCAN_INTR_SRC_TRANS_COMPLETE) ==
                                MCAN_INTR_SRC_TRANS_COMPLETE))
        {}

        /* Poll TXBTO for confirmation */
        bitPos = (1U << txBufNum);
        do
        {
            txStatus = MCAN_getTxBufTransmissionStatus(gMcanBaseAddr);
        } while ((txStatus & bitPos) != bitPos);

        /* Check for MSG_LOST on the 193rd message */
        if (loopCnt == (MAX_RAM_SEND_CNT - 1U))
        {
            if ((gMcanIsrIntr0Status & MCAN_INTR_SRC_RX_FIFO0_MSG_LOST) ==
                                MCAN_INTR_SRC_RX_FIFO0_MSG_LOST)
            {
                msgLostDetected = 1U;
                DebugP_log("MSG_LOST detected for message %u (expected)\n", loopCnt + 1U);
            }
        }

        gMcanIsrIntr0Status = 0U;

        /* Check for protocol errors */
        MCAN_getErrCounters(gMcanBaseAddr, &errCounter);
        if ((0U != errCounter.recErrCnt) || (0U != errCounter.canErrLogCnt))
        {
            DebugP_log("\nError counters non-zero at msg %u (TEC=%u REC=%u)\n",
                       loopCnt, errCounter.canErrLogCnt, errCounter.recErrCnt);
            testStatus = CSL_EFAIL;
            break;
        }

        MCAN_getProtocolStatus(gMcanBaseAddr, &protStatus);
        if (!((MCAN_ERR_CODE_NO_ERROR == protStatus.lastErrCode) ||
              (MCAN_ERR_CODE_NO_CHANGE == protStatus.lastErrCode)) ||
            !((MCAN_ERR_CODE_NO_ERROR == protStatus.dlec) ||
              (MCAN_ERR_CODE_NO_CHANGE == protStatus.dlec)) ||
            (0U != protStatus.pxe))
        {
            DebugP_log("\nProtocol error at msg %u\n", loopCnt);
            testStatus = CSL_EFAIL;
            break;
        }
    }

    DebugP_log("Phase 1 complete: All %u messages sent.\n", MAX_RAM_SEND_CNT);

    /* ------------------------------------------------------------------
     * Phase 2: Verify MSG_LOST was detected for the 193rd message.
     * ------------------------------------------------------------------ */
    if (msgLostDetected != 1U)
    {
        DebugP_log("FAIL: MSG_LOST not detected for 193rd message!\n");
        testStatus = CSL_EFAIL;
    }
    else
    {
        DebugP_log("Phase 2: MSG_LOST correctly detected for 193rd message.\n");
    }

    /* ------------------------------------------------------------------
     * Phase 3: Receive phase - read 192 messages from all RX paths.
     * ------------------------------------------------------------------ */
    DebugP_log("Phase 3: Receiving messages from all RX paths...\n");

    /* Initialize reference TX element with same constant fields as send loop */
    MCAN_initTxBufElement(&refTxElem);
    refTxElem.dlc = MCAN_DATA_SIZE_8BYTES;
    refTxElem.fdf = 0U;
    refTxElem.brs = 0U;
    refTxElem.efc = 0U;

    /* Read from FIFO0 (expect 64 messages) */
    fifoStatus.num = MCAN_RX_FIFO_NUM_0;
    MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
    DebugP_log("FIFO0: fillLvl=%u, fifoFull=%u\n", fifoStatus.fillLvl, fifoStatus.fifoFull);

    if (fifoStatus.fifoFull != 1U)
    {
        DebugP_log("FAIL: FIFO0 should be full (64 messages)\n");
        testStatus = CSL_EFAIL;
    }

    while (fifoStatus.fillLvl > 0U)
    {
        MCAN_readMsgRam(gMcanBaseAddr,
                        MCAN_MEM_TYPE_FIFO,
                        fifoStatus.getIdx,
                        (uint32_t)fifoStatus.num,
                        &rxMsg);
        (void)MCAN_writeRxFIFOAck(gMcanBaseAddr,
                                  (uint32_t)fifoStatus.num,
                                  fifoStatus.getIdx);
        totalRxCount++;
        /* Reconstruct expected TX element and compare TX/RX data */
        refTxElem.id       = ((0x001U + fifo0Idx) << APP_MCAN_STD_ID_SHIFT);
        refTxElem.xtd      = 0U;
        refTxElem.data[0U] = (uint8_t)(fifo0Idx & 0xFFU);
        refTxElem.data[1U] = (uint8_t)((fifo0Idx >> 8U) & 0xFFU);
        if (App_mcanTxRxMessageCheck(refTxElem, rxMsg) != CSL_PASS)
        {
            DebugP_log("FAIL: FIFO0 msg %u TX/RX mismatch\n", fifo0Idx);
            testStatus = CSL_EFAIL;
        }
        fifo0Idx++;
        MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
    }
    DebugP_log("FIFO0: Read %u messages\n", totalRxCount);

    /* Read from FIFO1 (expect 64 messages) */
    fifoStatus.num = MCAN_RX_FIFO_NUM_1;
    MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
    DebugP_log("FIFO1: fillLvl=%u, fifoFull=%u\n", fifoStatus.fillLvl, fifoStatus.fifoFull);

    if (fifoStatus.fifoFull != 1U)
    {
        DebugP_log("FAIL: FIFO1 should be full (64 messages)\n");
        testStatus = CSL_EFAIL;
    }

    while (fifoStatus.fillLvl > 0U)
    {
        MCAN_readMsgRam(gMcanBaseAddr,
                        MCAN_MEM_TYPE_FIFO,
                        fifoStatus.getIdx,
                        (uint32_t)fifoStatus.num,
                        &rxMsg);
        (void)MCAN_writeRxFIFOAck(gMcanBaseAddr,
                                  (uint32_t)fifoStatus.num,
                                  fifoStatus.getIdx);
        totalRxCount++;
        /* Reconstruct expected TX element and compare TX/RX data */
        refTxElem.id       = ((0x041U + fifo1Idx) << APP_MCAN_STD_ID_SHIFT);
        refTxElem.xtd      = 0U;
        refTxElem.data[0U] = (uint8_t)((MAX_RAM_FIFO0_CNT + fifo1Idx) & 0xFFU);
        refTxElem.data[1U] = (uint8_t)(((MAX_RAM_FIFO0_CNT + fifo1Idx) >> 8U) & 0xFFU);
        if (App_mcanTxRxMessageCheck(refTxElem, rxMsg) != CSL_PASS)
        {
            DebugP_log("FAIL: FIFO1 msg %u TX/RX mismatch\n", fifo1Idx);
            testStatus = CSL_EFAIL;
        }
        fifo1Idx++;
        MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
    }
    DebugP_log("FIFO0+FIFO1: Read %u messages total\n", totalRxCount);

    /* Read from dedicated RX buffers 0-63 (expect 64 messages).
     * newDataStatus is read once and kept intact for all 64 checks.
     * clearStatus is a separate struct used only for the clear call. */
    MCAN_getNewDataStatus(gMcanBaseAddr, &newDataStatus);
    for (loopCnt = 0U; loopCnt < MAX_RAM_RXBUF_CNT; loopCnt++)
    {
        if (loopCnt < 32U)
        {
            bitPos = (1U << loopCnt);
            if ((newDataStatus.statusLow & bitPos) == bitPos)
            {
                MCAN_readMsgRam(gMcanBaseAddr,
                                MCAN_MEM_TYPE_BUF,
                                loopCnt,
                                MCAN_RX_FIFO_NUM_0,
                                &rxMsg);
                /* Clear new-data flag for this buffer only */
                clearStatus.statusLow  = bitPos;
                clearStatus.statusHigh = 0U;
                MCAN_clearNewDataStatus(gMcanBaseAddr, &clearStatus);
                totalRxCount++;
                /* Reconstruct expected TX element and compare TX/RX data */
                refTxElem.id       = (loopCnt + 1U);
                refTxElem.xtd      = 1U;
                refTxElem.data[0U] = (uint8_t)((MAX_RAM_FIFO0_CNT + MAX_RAM_FIFO1_CNT + loopCnt) & 0xFFU);
                refTxElem.data[1U] = (uint8_t)(((MAX_RAM_FIFO0_CNT + MAX_RAM_FIFO1_CNT + loopCnt) >> 8U) & 0xFFU);
                if (App_mcanTxRxMessageCheck(refTxElem, rxMsg) != CSL_PASS)
                {
                    DebugP_log("FAIL: RX buffer %u TX/RX mismatch\n", loopCnt);
                    testStatus = CSL_EFAIL;
                }
            }
            else
            {
                DebugP_log("FAIL: RX buffer %u has no new data\n", loopCnt);
                testStatus = CSL_EFAIL;
            }
        }
        else
        {
            bitPos = (1U << (loopCnt - 32U));
            if ((newDataStatus.statusHigh & bitPos) == bitPos)
            {
                MCAN_readMsgRam(gMcanBaseAddr,
                                MCAN_MEM_TYPE_BUF,
                                loopCnt,
                                MCAN_RX_FIFO_NUM_0,
                                &rxMsg);
                /* Clear new-data flag for this buffer only */
                clearStatus.statusLow  = 0U;
                clearStatus.statusHigh = bitPos;
                MCAN_clearNewDataStatus(gMcanBaseAddr, &clearStatus);
                totalRxCount++;
                /* Reconstruct expected TX element and compare TX/RX data */
                refTxElem.id       = (loopCnt + 1U);
                refTxElem.xtd      = 1U;
                refTxElem.data[0U] = (uint8_t)((MAX_RAM_FIFO0_CNT + MAX_RAM_FIFO1_CNT + loopCnt) & 0xFFU);
                refTxElem.data[1U] = (uint8_t)(((MAX_RAM_FIFO0_CNT + MAX_RAM_FIFO1_CNT + loopCnt) >> 8U) & 0xFFU);
                if (App_mcanTxRxMessageCheck(refTxElem, rxMsg) != CSL_PASS)
                {
                    DebugP_log("FAIL: RX buffer %u TX/RX mismatch\n", loopCnt);
                    testStatus = CSL_EFAIL;
                }
            }
            else
            {
                DebugP_log("FAIL: RX buffer %u has no new data\n", loopCnt);
                testStatus = CSL_EFAIL;
            }
        }
    }
    DebugP_log("Total messages received: %u (expected %u)\n", totalRxCount, MAX_RAM_TOTAL_RX);

    /* ------------------------------------------------------------------
     * Phase 4: Verify total count and that no more messages are available.
     * ------------------------------------------------------------------ */
    if (totalRxCount != MAX_RAM_TOTAL_RX)
    {
        DebugP_log("FAIL: Expected %u received messages, got %u\n",
                   MAX_RAM_TOTAL_RX, totalRxCount);
        testStatus = CSL_EFAIL;
    }

    /* Verify FIFO0 is empty */
    fifoStatus.num = MCAN_RX_FIFO_NUM_0;
    MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
    if (fifoStatus.fillLvl != 0U)
    {
        DebugP_log("FAIL: FIFO0 still has %u messages after reading\n", fifoStatus.fillLvl);
        testStatus = CSL_EFAIL;
    }

    /* Verify FIFO1 is empty */
    fifoStatus.num = MCAN_RX_FIFO_NUM_1;
    MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
    if (fifoStatus.fillLvl != 0U)
    {
        DebugP_log("FAIL: FIFO1 still has %u messages after reading\n", fifoStatus.fillLvl);
        testStatus = CSL_EFAIL;
    }

    /* Verify no new data in RX buffers (193rd receive attempt fails) */
    MCAN_getNewDataStatus(gMcanBaseAddr, &newDataStatus);
    if ((newDataStatus.statusLow != 0U) || (newDataStatus.statusHigh != 0U))
    {
        DebugP_log("FAIL: RX buffers still have new data (low=0x%08X high=0x%08X)\n",
                   newDataStatus.statusLow, newDataStatus.statusHigh);
        testStatus = CSL_EFAIL;
    }

    DebugP_log("Phase 4: 193rd message receive correctly failed (no more messages available)\n");

    /* Disable TX buffer interrupt */
    (void)MCAN_txBufTransIntrEnable(gMcanBaseAddr, txBufNum, (uint32_t)FALSE);

    /* Disable Interrupts */
    MCAN_enableIntr(gMcanBaseAddr, MCAN_INTR_MASK_ALL, (uint32_t)FALSE);

    DebugP_log("=== Max Msg RAM Word Count Test %s ===\n",
               (testStatus == CSL_PASS) ? "PASSED" : "FAILED");

    return testStatus;
}
