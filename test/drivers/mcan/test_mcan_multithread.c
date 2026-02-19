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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#if defined (FREERTOS_CORE)
#include <stdint.h>
#include <stdio.h>
#include "test_mcan.h"
#include <kernel/dpl/AddrTranslateP.h>
#include <kernel/dpl/TaskP.h>


/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#define APP_MCAN_STD_ID_SHIFT             (18U)
#define APP_MCAN_STD_ID_MASK              (0x7FFU << APP_MCAN_STD_ID_SHIFT)

/* Total messages per thread = accepted + rejected */
#define TEST_MCAN_MT_ACCEPT_COUNT     (3U)   /* Accepted IDs per thread */
#define TEST_MCAN_MT_REJECT_COUNT     (2U)   /* Rejected IDs per thread */
#define TEST_MCAN_MT_MESSAGE_COUNT    (TEST_MCAN_MT_ACCEPT_COUNT + TEST_MCAN_MT_REJECT_COUNT)
#define TEST_MCAN_MT_TX_TASK_PRI      (6U)
#define TEST_MCAN_MT_TASK_STACK_SIZE  (4U * 1024U)
#define MCAN_MT_MAX_THREADS           (2U)
#define TEST_MCAN_MT_DATA_SIZE        (8U)  /* Number of data bytes per CAN message */

/* Classic bitmask filter IDs (sfid1=0x100, sfid2=0x700 -> accepts 0x100-0x1FF) */
#define FILTER_TEST_CLASSIC_ID         (0x100U)  /* Base ID */
#define FILTER_TEST_CLASSIC_MASK       (0x700U)  /* Mask: bits[10:8] must match */
#define FILTER_TEST_CLASSIC_REJECT_ID1 (0x300U)  /* Out of range: bits[10:8]==0x3 */
#define FILTER_TEST_CLASSIC_REJECT_ID2 (0x500U)  /* Out of range: bits[10:8]==0x5 */
#define FILTER_TEST_ID_NIBBLE_MASK     (0x0FU)   /* Lower nibble for accept ID variation */

/* Dual filter IDs (sfid1=0x200, sfid2=0x201 -> accepts only 0x200 or 0x201) */
#define FILTER_TEST_DUAL_ID1           (0x200U)  /* Accepted: exact match */
#define FILTER_TEST_DUAL_ID2           (0x201U)  /* Accepted: exact match */
#define FILTER_TEST_DUAL_REJECT_ID1    (0x202U)  /* Rejected: not 0x200 or 0x201 */
#define FILTER_TEST_DUAL_REJECT_ID2    (0x400U)  /* Rejected: not 0x200 or 0x201 */


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Structure to pass MCAN instance specific data to threads */
typedef struct {
    uint32_t baseAddr;
    uint32_t instanceId;
    st_mcanTestcaseParams_t *testParams;
    SemaphoreP_Object *txDoneSem;
    SemaphoreP_Object *rxDoneSem;
} McanInstanceThreadArgs_t;

/* Thread-specific data structure for filter tests */
typedef struct {
    SemaphoreP_Object txDoneSem;
    SemaphoreP_Object rxDoneSem;
    volatile uint32_t txRxCount;
    volatile uint32_t errors;
    uint32_t txBufferNum;
    uint32_t messageId;
    uint32_t alternateId;  /* For dual filter - 0 if not used */
    uint32_t rxDestination; /* FIFO0, FIFO1, or Buffer */
    uint8_t dataPattern;   /* Base data pattern for this thread */
    const char *threadName;
} McanFilterThreadArgs_t;

extern uint32_t          gMcanBaseAddr;
extern volatile uint32_t gMcanIsrIntr0Status;
extern HwiP_Object        gMcanHwiObject;
extern HwiP_Object        gMcanHwiObject3;
extern void App_mcanIntr0ISR(void *arg);
extern void App_mcanIntr1ISR(void *arg);

/* Common task stacks and objects - reused by all tests (max 3 threads) */
static uint8_t gMcanMtTaskStack[MCAN_MT_MAX_THREADS][TEST_MCAN_MT_TASK_STACK_SIZE] __attribute__((aligned(32)));
static TaskP_Object gMcanMtTaskObj[MCAN_MT_MAX_THREADS];

/* Common synchronization semaphores - constructed/destructed per test */
static SemaphoreP_Object gMcanMtStartSem;        /* Start signal for threads */
static SemaphoreP_Object gMcanMtCompleteSem;      /* Completion counting semaphore */
static SemaphoreP_Object gMcanMtReadySem[2];      /* Thread ready signals */

/* TX/RX done semaphores for shared ISR (App_mcanIntr0ISR) */
extern SemaphoreP_Object gTxDoneSem, gRxDoneSem;

/* Per-thread TX/RX done semaphores for custom ISRs */
static SemaphoreP_Object gMcanMtPerThreadTxSem[MCAN_MT_MAX_THREADS];
static SemaphoreP_Object gMcanMtPerThreadRxSem[MCAN_MT_MAX_THREADS];

/* Semaphore pointer arrays for ISR access */
static SemaphoreP_Object *gMcanMtTxSemPtrs[MCAN_MT_MAX_THREADS];
static SemaphoreP_Object *gMcanMtRxSemPtrs[MCAN_MT_MAX_THREADS];

/* Common control and counters - reset before each test */
static volatile uint32_t gMcanMtStopThreads = 0U;
static volatile uint32_t gMcanMtRxCount = 0U;
static volatile uint32_t gMcanMtPerThreadCount[MCAN_MT_MAX_THREADS];
static volatile uint32_t gMcanMtPerThreadErrors[MCAN_MT_MAX_THREADS];

/* HWI objects for custom ISRs (max 2 for multi-instance test) */
static HwiP_Object gMcanMtHwiObj[2];

/* Multi-instance base addresses */
static uint32_t gMcanMtInstBaseAddr[2];


/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 * \brief    TX Producer thread - sends 5 CAN messages for basic multi-threading test
 */
static void TestMcan_txThread(void *args)
{
    MCAN_TxBufElement txMsg;
    uint32_t msgCount = 0U;
    int32_t status;
    uint32_t bufNum = 0U;
    
    /* Initialize TX message */
    txMsg.id = (0x04U << 18U);  /* Standard ID - matches canSTDIDFilter[0] */
    txMsg.rtr = 0U;
    txMsg.xtd = 0U;  /* Standard ID */
    txMsg.esi = 0U;
    txMsg.dlc = MCAN_DATA_SIZE_8BYTES;
    txMsg.brs = 1U;  /* Bit rate switching */
    txMsg.fdf = 1U;  /* FD format */
    txMsg.efc = 1U;  /* Store Tx events */
    txMsg.mm = 0xAAU;
    
    /* Signal ready */
    SemaphoreP_post(&gMcanMtReadySem[0]);
    
    /* Wait for RX thread to be ready */
    SemaphoreP_pend(&gMcanMtReadySem[1], SystemP_WAIT_FOREVER);
    
    /* Producer loop - send 5 messages */
    while(!gMcanMtStopThreads && (msgCount < TEST_MCAN_MT_MESSAGE_COUNT))
    {
        /* Fill unique data pattern - each byte is msgCount + offset */
        for(uint32_t i = 0; i < TEST_MCAN_MT_DATA_SIZE; i++)
        {
            txMsg.data[i] = (uint8_t)(msgCount + i);
        }
        
        /* Write message to TX buffer */
        MCAN_writeMsgRam(gMcanBaseAddr, 
                        MCAN_MEM_TYPE_BUF,
                        bufNum,
                        &txMsg);
        
        /* Trigger transmission */
        status = MCAN_txBufAddReq(gMcanBaseAddr, bufNum);
        if(status != CSL_PASS)
        {
            DebugP_log("[ TX Thread] ERROR: Failed to add TX request for buffer %d\r\n", bufNum);
        }

        /* Wait for TX confirmation - only if TX request was successful */
        if(status == CSL_PASS)
        {
            status = SemaphoreP_pend(&gTxDoneSem, SystemP_WAIT_FOREVER);
            if(status == SystemP_SUCCESS)
            {
                msgCount++;
                DebugP_log("[ TX Thread] Message %d transmitted successfully\r\n", msgCount);
            }
            else
            {
                DebugP_log("[ TX Thread] ERROR: TX semaphore pend failed\r\n");
            }
        }
        
        /* Use alternate buffer (ping-pong) */
        bufNum = (bufNum + 1) % 2;
        
        /* Small delay for stability */
        ClockP_usleep(1000);
    }
    
    /* Signal completion */
    SemaphoreP_post(&gMcanMtCompleteSem);
    
    TaskP_exit();
}

/**
 * \brief    RX Consumer thread - receives and validates 5 CAN messages
 */
static void TestMcan_rXThread(void *args)
{
    MCAN_RxBufElement rxMsg;
    uint32_t msgCount = 0U;
    int32_t status;
    uint32_t expectedData;
    
    /* Suppress unused parameter warning */
    (void)args;
    
    /* Signal ready */
    SemaphoreP_post(&gMcanMtReadySem[1]);
    
    /* Wait for TX thread to be ready */
    SemaphoreP_pend(&gMcanMtReadySem[0], SystemP_WAIT_FOREVER);
    
    /* Consumer loop - receive and validate 5 messages */
    while(!gMcanMtStopThreads && (gMcanMtRxCount < TEST_MCAN_MT_MESSAGE_COUNT))
    {
        /* Wait for RX interrupt */
        status = SemaphoreP_pend(&gRxDoneSem, SystemP_WAIT_FOREVER);
        if(status != SystemP_SUCCESS)
        {
            DebugP_log("[ RX Thread] ERROR: RX semaphore pend failed\r\n");
            continue;
        }
        
        /* Read received message */
        status = App_mcanReadRxMSG(&rxMsg, gMcanIsrIntr0Status);
        if(status != CSL_PASS)
        {
            DebugP_log("[ RX Thread] ERROR: Failed to read RX message\r\n");
            continue;
        }
        
        DebugP_log("[ RX Thread] Received message %d (ID: 0x%X, Data: 0x%02X 0x%02X 0x%02X...)\r\n",
                   gMcanMtRxCount + 1, (rxMsg.id >> 18), rxMsg.data[0], rxMsg.data[1], rxMsg.data[2]);
        
        /* Validate message ID */
        if((rxMsg.id & APP_MCAN_STD_ID_MASK) != (0x04U << APP_MCAN_STD_ID_SHIFT))
        {
            DebugP_log("[ RX Thread] ERROR: ID mismatch. Expected: 0x%X, Got: 0x%X\r\n", 
                      (0x04U << APP_MCAN_STD_ID_SHIFT), rxMsg.id);
        }
        
        /* Validate data pattern - data[i] should be msgCount + i */
        for(uint32_t i = 0; i < TEST_MCAN_MT_DATA_SIZE; i++)
        {
            expectedData = (uint8_t)(msgCount + i);
            if(rxMsg.data[i] != expectedData)
            {
                DebugP_log("[ RX Thread] ERROR: Data[%d] mismatch. Expected: 0x%02X, Got: 0x%02X\r\n",
                          i, expectedData, rxMsg.data[i]);
            }
        }
        
        gMcanMtRxCount++;
        msgCount++;
    }
    
    /* Signal completion */
    SemaphoreP_post(&gMcanMtCompleteSem);
    
    TaskP_exit();
}

/**
 * \brief    Multi-threaded TX/RX test with 5 messages
 *          Validates continuous transmit/receive stability and end-to-end correctness
 *          Uses SemaphoreP_constructCounting and TaskP_construct APIs
 */
int32_t TestMcan_multiThreadedTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t configStatus = CSL_PASS;
    int32_t status;
    TaskP_Params taskParams;
    
    /* Reset counters */
    gMcanMtRxCount = 0U;
    gMcanMtStopThreads = 0U;
    
    /* Configure MCAN module */
    configStatus = App_mcanConfig(testParams);
    if(configStatus != CSL_PASS)
    {
        DebugP_log("ERROR: MCAN configuration failed!\r\n");
        return CSL_EFAIL;
    }

    /* Enable MCAN Interrupts */
    MCAN_enableIntr(gMcanBaseAddr, testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);
    
    /* Select Interrupt Line */
    MCAN_selectIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);
    
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        1U);
    
    /* Enable Transmission interrupt for TX buffers (0 and 1 for ping-pong) */
    configStatus = MCAN_txBufTransIntrEnable(gMcanBaseAddr, 0U, (uint32_t)TRUE);
    if(configStatus != CSL_PASS)
    {
        DebugP_log("ERROR: MCAN Tx Buffer 0 Interrupt Enable FAILED\r\n");
        return CSL_EFAIL;
    }
    
    configStatus = MCAN_txBufTransIntrEnable(gMcanBaseAddr, 1U, (uint32_t)TRUE);
    if(configStatus != CSL_PASS)
    {
        DebugP_log("ERROR: MCAN Tx Buffer 1 Interrupt Enable FAILED\r\n");
        return CSL_EFAIL;
    }
    
    /* Create synchronization semaphores */
    status = SemaphoreP_constructBinary(&gMcanMtReadySem[0], 0);
    DebugP_assert(status == SystemP_SUCCESS);
    
    status = SemaphoreP_constructBinary(&gMcanMtReadySem[1], 0);
    DebugP_assert(status == SystemP_SUCCESS);
    
    /* Create counting semaphore for completion (max count = 2 for TX and RX threads) */
    status = SemaphoreP_constructCounting(&gMcanMtCompleteSem, 0, 2);
    DebugP_assert(status == SystemP_SUCCESS);
    
    /* Create TX Producer Task using TaskP_construct */
    TaskP_Params_init(&taskParams);
    taskParams.name = "SIMPLE_MCAN_TX";
    taskParams.stackSize = TEST_MCAN_MT_TASK_STACK_SIZE;
    taskParams.stack = gMcanMtTaskStack[0];
    taskParams.priority = TEST_MCAN_MT_TX_TASK_PRI;
    taskParams.args = testParams;
    taskParams.taskMain = TestMcan_txThread;
    
    status = TaskP_construct(&gMcanMtTaskObj[0], &taskParams);
    if(status != SystemP_SUCCESS)
    {
        DebugP_log("ERROR: Failed to create TX thread!\r\n");
        configStatus = CSL_EFAIL;
    }

    if(configStatus == CSL_PASS)
    {
        /* Create RX Consumer Task using TaskP_construct */
        TaskP_Params_init(&taskParams);
        taskParams.name = "SIMPLE_MCAN_RX";
        taskParams.stackSize = TEST_MCAN_MT_TASK_STACK_SIZE;
        taskParams.stack = gMcanMtTaskStack[1];
        taskParams.priority = TEST_MCAN_MT_TX_TASK_PRI;
        taskParams.args = testParams;
        taskParams.taskMain = TestMcan_rXThread;

        status = TaskP_construct(&gMcanMtTaskObj[1], &taskParams);
        if(status != SystemP_SUCCESS)
        {
            DebugP_log("ERROR: Failed to create RX thread!\r\n");
            configStatus = CSL_EFAIL;
        }
    }

    if(configStatus == CSL_PASS)
    {
        /* Wait for both threads to complete using counting semaphore */
        SemaphoreP_pend(&gMcanMtCompleteSem, SystemP_WAIT_FOREVER);  /* TX complete */
        SemaphoreP_pend(&gMcanMtCompleteSem, SystemP_WAIT_FOREVER);  /* RX complete */

        /* Stop threads */
        gMcanMtStopThreads = 1U;

        if(gMcanMtRxCount != TEST_MCAN_MT_MESSAGE_COUNT)
        {
            DebugP_log("ERROR: RX count mismatch (Expected: %d, Got: %d)\r\n",
                       TEST_MCAN_MT_MESSAGE_COUNT, gMcanMtRxCount);
            configStatus = CSL_EFAIL;
        }
    }

    /* Destruct tasks */
    TaskP_destruct(&gMcanMtTaskObj[0]);
    TaskP_destruct(&gMcanMtTaskObj[1]);

    /* Destruct only the semaphores created by this test.
     * gTxDoneSem and gRxDoneSem are managed by the test framework
     * (TestMcan_initTxRxSem/TestMcan_deInitTxRxSem) and must NOT be
     * destructed here to avoid corrupting the gTxRxSemInitDone state. */
    SemaphoreP_destruct(&gMcanMtReadySem[0]);
    SemaphoreP_destruct(&gMcanMtReadySem[1]);
    SemaphoreP_destruct(&gMcanMtCompleteSem);

    return configStatus;
}

/**
 * \brief    TX Thread 1 - uses dedicated TX buffer 0
 */
static void TestMcan_concurrentTxThread1(void *args)
{
    MCAN_TxBufElement txMsg;
    MCAN_RxBufElement rxMsg;
    MCAN_RxFIFOStatus fifoStatus;
    uint32_t msgCount = 0U;
    int32_t status;
    uint32_t txStatus;
    uint32_t bitPos;
    uint8_t expected;

    /* Initialize TX message for Thread 1 - uses standard ID 0x100 */
    txMsg.id = (0x100U << 18U);  /* Standard ID */
    txMsg.rtr = 0U;
    txMsg.xtd = 0U;  /* Standard ID */
    txMsg.esi = 0U;
    txMsg.dlc = MCAN_DATA_SIZE_8BYTES;
    txMsg.brs = 1U;  /* Bit rate switching */
    txMsg.fdf = 1U;  /* FD format */
    txMsg.efc = 1U;  /* Store Tx events */
    txMsg.mm = 0x11U;  /* Marker for Thread 1 */

    /* Wait for start signal */
    SemaphoreP_pend(&gMcanMtStartSem, SystemP_WAIT_FOREVER);

    /* Transmit loop - send messages from buffer 0 */
    while(!gMcanMtStopThreads && (msgCount < TEST_MCAN_MT_MESSAGE_COUNT))
    {
        /* Fill unique data pattern - Thread 1 uses 0x10 + msgCount */
        for(uint32_t i = 0U; i < TEST_MCAN_MT_DATA_SIZE; i++)
        {
            txMsg.data[i] = (uint8_t)(0x10 + msgCount + i);
        }

        /* Write message to TX buffer 0 */
        MCAN_writeMsgRam(gMcanBaseAddr,
                        MCAN_MEM_TYPE_BUF,
                        0U,  /* Dedicated buffer 0 for Thread 1 */
                        &txMsg);

        /* Trigger transmission */
        status = MCAN_txBufAddReq(gMcanBaseAddr, 0U);
        if(status != CSL_PASS)
        {
            DebugP_log("[TX Thread 1] ERROR: Failed to add TX request for buffer 0\r\n");
        }

        /* Wait for TX completion (poll for buffer 0) - only if TX request was successful */
        if(status == CSL_PASS)
        {
            bitPos = (1U << 0U);
            do
            {
                txStatus = MCAN_getTxBufTransmissionStatus(gMcanBaseAddr);
                if(gMcanMtStopThreads)
                {
                    break;
                }
            } while((txStatus & bitPos) != bitPos);

            if(!gMcanMtStopThreads)
            {
                /* Poll RX FIFO0 for loopback message with matching ID 0x100 */
                do
                {
                    fifoStatus.num = (uint32_t)MCAN_RX_FIFO_NUM_0;
                    MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
                } while(fifoStatus.fillLvl == 0U && !gMcanMtStopThreads);

                if(!gMcanMtStopThreads)
                {
                    MCAN_readMsgRam(gMcanBaseAddr, MCAN_MEM_TYPE_FIFO, fifoStatus.getIdx,
                                    (uint32_t)MCAN_RX_FIFO_NUM_0, &rxMsg);
                    MCAN_writeRxFIFOAck(gMcanBaseAddr, (uint32_t)MCAN_RX_FIFO_NUM_0, fifoStatus.getIdx);

                    /* Validate ID */
                    if(((rxMsg.id >> APP_MCAN_STD_ID_SHIFT) & 0x7FFU) != 0x100U)
                    {
                        DebugP_log("[TX Thread 1] ID mismatch msg=%d: expected 0x100 got 0x%X\r\n",
                                   msgCount, (rxMsg.id >> APP_MCAN_STD_ID_SHIFT) & 0x7FFU);
                        gMcanMtPerThreadErrors[0]++;
                    }
                    else
                    {
                        /* Validate data */
                        for(uint32_t i = 0U; i < TEST_MCAN_MT_DATA_SIZE; i++)
                        {
                            expected = (uint8_t)(0x10 + msgCount + i);
                            if(rxMsg.data[i] != expected)
                            {
                                DebugP_log("[TX Thread 1] Data mismatch msg=%d byte=%d: expected 0x%02X got 0x%02X\r\n",
                                           msgCount, i, expected, rxMsg.data[i]);
                                gMcanMtPerThreadErrors[0]++;
                            }
                        }
                    }
                }

                msgCount++;
            }
        }

        /* Small delay for interleaving with Thread 2 */
        ClockP_usleep(500);
    }

    /* Signal completion */
    SemaphoreP_post(&gMcanMtCompleteSem);

    TaskP_exit();
}

/**
 * \brief    TX Thread 2 - uses dedicated TX buffer 1
 */
static void TestMcan_concurrentTxThread2(void *args)
{
    MCAN_TxBufElement txMsg;
    MCAN_RxBufElement rxMsg;
    MCAN_RxFIFOStatus fifoStatus;
    uint32_t msgCount = 0U;
    int32_t status;
    uint32_t txStatus;
    uint32_t bitPos;
    uint8_t expected;

    /* Initialize TX message for Thread 2 - uses standard ID 0x200 */
    txMsg.id = (0x200U << 18U);  /* Standard ID */
    txMsg.rtr = 0U;
    txMsg.xtd = 0U;  /* Standard ID */
    txMsg.esi = 0U;
    txMsg.dlc = MCAN_DATA_SIZE_8BYTES;
    txMsg.brs = 1U;  /* Bit rate switching */
    txMsg.fdf = 1U;  /* FD format */
    txMsg.efc = 1U;  /* Store Tx events */
    txMsg.mm = 0x22U;  /* Marker for Thread 2 */

    /* Wait for start signal */
    SemaphoreP_pend(&gMcanMtStartSem, SystemP_WAIT_FOREVER);

    /* Transmit loop - send messages from buffer 1 */
    while(!gMcanMtStopThreads && (msgCount < TEST_MCAN_MT_MESSAGE_COUNT))
    {
        /* Fill unique data pattern - Thread 2 uses 0x20 + msgCount */
        for(uint32_t i = 0U; i < TEST_MCAN_MT_DATA_SIZE; i++)
        {
            txMsg.data[i] = (uint8_t)(0x20 + msgCount + i);
        }

        /* Write message to TX buffer 1 */
        MCAN_writeMsgRam(gMcanBaseAddr,
                        MCAN_MEM_TYPE_BUF,
                        1U,  /* Dedicated buffer 1 for Thread 2 */
                        &txMsg);

        /* Trigger transmission */
        status = MCAN_txBufAddReq(gMcanBaseAddr, 1U);
        if(status != CSL_PASS)
        {
            DebugP_log("[TX Thread 2] ERROR: Failed to add TX request for buffer 1\r\n");
        }

        /* Wait for TX completion (poll for buffer 1) - only if TX request was successful */
        if(status == CSL_PASS)
        {
            bitPos = (1U << 1U);
            do
            {
                txStatus = MCAN_getTxBufTransmissionStatus(gMcanBaseAddr);
                if(gMcanMtStopThreads)
                {
                    break;
                }
            } while((txStatus & bitPos) != bitPos);

            if(!gMcanMtStopThreads)
            {
                /* Poll RX FIFO0 for loopback message with matching ID 0x200 */
                do
                {
                    fifoStatus.num = (uint32_t)MCAN_RX_FIFO_NUM_0;
                    MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
                } while(fifoStatus.fillLvl == 0U && !gMcanMtStopThreads);

                if(!gMcanMtStopThreads)
                {
                    MCAN_readMsgRam(gMcanBaseAddr, MCAN_MEM_TYPE_FIFO, fifoStatus.getIdx,
                                    (uint32_t)MCAN_RX_FIFO_NUM_0, &rxMsg);
                    MCAN_writeRxFIFOAck(gMcanBaseAddr, (uint32_t)MCAN_RX_FIFO_NUM_0, fifoStatus.getIdx);

                    /* Validate ID */
                    if(((rxMsg.id >> APP_MCAN_STD_ID_SHIFT) & 0x7FFU) != 0x200U)
                    {
                        DebugP_log("[TX Thread 2] ID mismatch msg=%d: expected 0x200 got 0x%X\r\n",
                                   msgCount, (rxMsg.id >> APP_MCAN_STD_ID_SHIFT) & 0x7FFU);
                        gMcanMtPerThreadErrors[1]++;
                    }
                    else
                    {
                        /* Validate data */
                        for(uint32_t i = 0U; i < TEST_MCAN_MT_DATA_SIZE; i++)
                        {
                            expected = (uint8_t)(0x20 + msgCount + i);
                            if(rxMsg.data[i] != expected)
                            {
                                DebugP_log("[TX Thread 2] Data mismatch msg=%d byte=%d: expected 0x%02X got 0x%02X\r\n",
                                           msgCount, i, expected, rxMsg.data[i]);
                                gMcanMtPerThreadErrors[1]++;
                            }
                        }
                    }
                }

                msgCount++;
            }
        }

        /* Small delay for interleaving with Thread 1 */
        ClockP_usleep(500);
    }

    /* Signal completion */
    SemaphoreP_post(&gMcanMtCompleteSem);

    TaskP_exit();
}

/**
 * \brief    Concurrent TX Test - Two threads transmitting simultaneously
 *           Thread 1 uses TX buffer 0, Thread 2 uses TX buffer 1
 *           Each thread sends TEST_MCAN_MT_MESSAGE_COUNT messages
 *           Validates thread-safe concurrent transmission with RX data comparison
 */
int32_t TestMcan_concurrentTxTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t configStatus = CSL_PASS;
    int32_t status;
    TaskP_Params taskParams;

    /* Reset counters */
    gMcanMtStopThreads = 0U;
    gMcanMtPerThreadErrors[0] = 0U;
    gMcanMtPerThreadErrors[1] = 0U;
    
    /* Configure MCAN module */
    configStatus = App_mcanConfig(testParams);
    if(configStatus != CSL_PASS)
    {
        DebugP_log("ERROR: MCAN configuration failed!\r\n");
        return CSL_EFAIL;
    }
    
    /* Enable MCAN Interrupts */
    MCAN_enableIntr(gMcanBaseAddr, testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);
    
    /* Select Interrupt Line */
    MCAN_selectIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);
    
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        1U);
    
    /* Enable Transmission interrupt for TX buffer 0 (Thread 1) */
    configStatus = MCAN_txBufTransIntrEnable(gMcanBaseAddr, 0U, (uint32_t)TRUE);
    if(configStatus != CSL_PASS)
    {
        DebugP_log("ERROR: MCAN Tx Buffer 0 Interrupt Enable FAILED\r\n");
        return CSL_EFAIL;
    }
    
    /* Enable Transmission interrupt for TX buffer 1 (Thread 2) */
    configStatus = MCAN_txBufTransIntrEnable(gMcanBaseAddr, 1U, (uint32_t)TRUE);
    if(configStatus != CSL_PASS)
    {
        DebugP_log("ERROR: MCAN Tx Buffer 1 Interrupt Enable FAILED\r\n");
        return CSL_EFAIL;
    }
    
    /* Create synchronization semaphores */
    /* Binary semaphore to signal start (both threads will pend on this) */
    status = SemaphoreP_constructCounting(&gMcanMtStartSem, 0, 2);
    DebugP_assert(status == SystemP_SUCCESS);
    
    /* Counting semaphore for completion (max count = 2 for both TX threads) */
    status = SemaphoreP_constructCounting(&gMcanMtCompleteSem, 0, 2);
    DebugP_assert(status == SystemP_SUCCESS);
    
    /* gTxDoneSem and gRxDoneSem are already constructed by the test framework
     * (TestMcan_initTxRxSem) - do NOT construct them here to avoid corruption. */
    
    /* Create TX Thread 1 using TaskP_construct (uses buffer 0) */
    TaskP_Params_init(&taskParams);
    taskParams.name = "MCAN_TX_THREAD_1";
    taskParams.stackSize = TEST_MCAN_MT_TASK_STACK_SIZE;
    taskParams.stack = gMcanMtTaskStack[0];
    taskParams.priority = TEST_MCAN_MT_TX_TASK_PRI;
    taskParams.args = testParams;
    taskParams.taskMain = TestMcan_concurrentTxThread1;
    
    status = TaskP_construct(&gMcanMtTaskObj[0], &taskParams);
    if(status != SystemP_SUCCESS)
    {
        DebugP_log("ERROR: Failed to create TX Thread 1!\r\n");
        configStatus = CSL_EFAIL;
    }

    if(configStatus == CSL_PASS)
    {
        /* Create TX Thread 2 using TaskP_construct (uses buffer 1) */
        TaskP_Params_init(&taskParams);
        taskParams.name = "MCAN_TX_THREAD_2";
        taskParams.stackSize = TEST_MCAN_MT_TASK_STACK_SIZE;
        taskParams.stack = gMcanMtTaskStack[1];
        taskParams.priority = TEST_MCAN_MT_TX_TASK_PRI;
        taskParams.args = testParams;
        taskParams.taskMain = TestMcan_concurrentTxThread2;

        status = TaskP_construct(&gMcanMtTaskObj[1], &taskParams);
        if(status != SystemP_SUCCESS)
        {
            DebugP_log("ERROR: Failed to create TX Thread 2!\r\n");
            configStatus = CSL_EFAIL;
        }
    }

    if(configStatus == CSL_PASS)
    {
        /* Give small delay to ensure both threads are created and waiting */
        ClockP_usleep(1000);

        /* Start both threads simultaneously by posting start semaphore twice */
        SemaphoreP_post(&gMcanMtStartSem);  /* Thread 1 */
        SemaphoreP_post(&gMcanMtStartSem);  /* Thread 2 */

        /* Wait for both threads to complete */
        SemaphoreP_pend(&gMcanMtCompleteSem, SystemP_WAIT_FOREVER);
        SemaphoreP_pend(&gMcanMtCompleteSem, SystemP_WAIT_FOREVER);

        /* Stop threads */
        gMcanMtStopThreads = 1U;

        /* Validate RX data comparison results */
        if(gMcanMtPerThreadErrors[0] > 0U)
        {
            DebugP_log("ERROR: Thread 1 RX data mismatch count: %d\r\n", gMcanMtPerThreadErrors[0]);
            configStatus = CSL_EFAIL;
        }

        if(gMcanMtPerThreadErrors[1] > 0U)
        {
            DebugP_log("ERROR: Thread 2 RX data mismatch count: %d\r\n", gMcanMtPerThreadErrors[1]);
            configStatus = CSL_EFAIL;
        }

        if(configStatus == CSL_PASS)
        {
            DebugP_log("PASS: All messages TX/RX data verified successfully\r\n");
        }
    }

    /* Destruct tasks */
    TaskP_destruct(&gMcanMtTaskObj[0]);
    TaskP_destruct(&gMcanMtTaskObj[1]);

    /* Destruct only the semaphores created by this test.
     * gTxDoneSem and gRxDoneSem are managed by the test framework
     * (TestMcan_initTxRxSem/TestMcan_deInitTxRxSem) and must NOT be
     * destructed here to avoid corrupting the gTxRxSemInitDone state. */
    SemaphoreP_destruct(&gMcanMtStartSem);
    SemaphoreP_destruct(&gMcanMtCompleteSem);

    /* Disable TX buffer interrupts */
    MCAN_txBufTransIntrEnable(gMcanBaseAddr, 0U, (uint32_t)FALSE);
    MCAN_txBufTransIntrEnable(gMcanBaseAddr, 1U, (uint32_t)FALSE);

    return configStatus;
}

/**
 * \brief    TX FIFO Producer Thread - Sends messages via TX FIFO
 */
static void TestMcan_txFifoThread(void *args)
{
    MCAN_TxBufElement txMsg;
    MCAN_TxFIFOStatus txFIFOStatus;
    uint32_t msgCount = 0U;
    int32_t status;
    uint32_t putIdx;
    
    /* Suppress unused parameter warning */
    (void)args;
    
    /* Initialize TX message */
    txMsg.id = (0x04U << 18U);  /* Standard ID - matches filter*/
    txMsg.rtr = 0U;
    txMsg.xtd = 0U;  /* Standard ID */
    txMsg.esi = 0U;
    txMsg.dlc = MCAN_DATA_SIZE_8BYTES;
    txMsg.brs = 1U;  /* Bit rate switching */
    txMsg.fdf = 1U;  /* FD format */
    txMsg.efc = 1U;  /* Store Tx events */
    txMsg.mm = 0xCCU;  /* Marker for TX FIFO */
    
    /* Signal ready */
    SemaphoreP_post(&gMcanMtReadySem[0]);
    
    /* Wait for RX thread to be ready */
    SemaphoreP_pend(&gMcanMtReadySem[1], SystemP_WAIT_FOREVER);
    
    /* Producer loop - send messages via TX FIFO */
    while(!gMcanMtStopThreads && (msgCount < TEST_MCAN_MT_MESSAGE_COUNT))
    {
        /* Get TX FIFO status to get the putIdx */
        MCAN_getTxFIFOQueStatus(gMcanBaseAddr, &txFIFOStatus);
        
        /* Check if TX FIFO is full */
        if(txFIFOStatus.fifoFull == 1U)
        {
            DebugP_log("[TX FIFO Thread] TX FIFO full, waiting...\r\n");
            ClockP_usleep(1000);
            continue;
        }
        
        putIdx = txFIFOStatus.putIdx;
        
        /* Fill data pattern */
        for(uint32_t i = 0; i < TEST_MCAN_MT_DATA_SIZE; i++)
        {
            txMsg.data[i] = (uint8_t)(0x10 + msgCount + i);
        }
        
        /* Write message to TX FIFO */
        MCAN_writeMsgRam(gMcanBaseAddr, 
                         MCAN_MEM_TYPE_FIFO, 
                         putIdx,
                         &txMsg);
        
        /* Request transmission */
        status = MCAN_txBufAddReq(gMcanBaseAddr, putIdx);
        if(status != CSL_PASS)
        {
            DebugP_log("[TX FIFO Thread] ERROR: TX request failed for message %d\r\n", msgCount);
            break;
        }
        
        /* Wait for TX completion */
        status = SemaphoreP_pend(&gTxDoneSem, SystemP_WAIT_FOREVER);
        DebugP_assert(status == SystemP_SUCCESS);
        msgCount++;
        
        /* Small delay between messages */
        ClockP_usleep(100);
    }
    
    /* Signal completion */
    SemaphoreP_post(&gMcanMtCompleteSem);
    
    TaskP_exit();
}

/**
 * \brief    RX FIFO0 Consumer Thread - Receives messages from RX FIFO0
 */
static void TestMcan_rxFifo0Thread(void *args)
{
    MCAN_RxBufElement rxMsg;
    MCAN_RxFIFOStatus fifoStatus;
    uint32_t msgCount = 0U;
    int32_t status;
    uint32_t expectedData;
    uint32_t getIdx;
    
    /* Suppress unused parameter warning */
    (void)args;
    
    /* Signal ready */
    SemaphoreP_post(&gMcanMtReadySem[1]);
    
    /* Wait for TX thread to be ready */
    SemaphoreP_pend(&gMcanMtReadySem[0], SystemP_WAIT_FOREVER);

    /* Consumer loop - receive and validate messages from RX FIFO0 */
    while(!gMcanMtStopThreads && (gMcanMtRxCount < TEST_MCAN_MT_MESSAGE_COUNT))
    {
        /* Wait for RX completion */
        status = SemaphoreP_pend(&gRxDoneSem, SystemP_WAIT_FOREVER);
        DebugP_assert(status == SystemP_SUCCESS);
        
        /* Get RX FIFO0 status */
        fifoStatus.num = MCAN_RX_FIFO_NUM_0;
        MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
        
        /* Check if FIFO has messages */
        if(fifoStatus.fillLvl == 0U)
        {
            DebugP_log("[RX FIFO0 Thread] WARNING: RX interrupt but FIFO empty\r\n");
            continue;
        }
        
        getIdx = fifoStatus.getIdx;
        
        /* Read message from RX FIFO0 */
        MCAN_readMsgRam(gMcanBaseAddr,
                        MCAN_MEM_TYPE_FIFO,
                        getIdx,
                        fifoStatus.num,
                        &rxMsg);
        
        /* Acknowledge the message */
        MCAN_writeRxFIFOAck(gMcanBaseAddr, fifoStatus.num, getIdx);
        
        /* Validate received data */
        for(uint32_t i = 0; i < TEST_MCAN_MT_DATA_SIZE; i++)
        {
            expectedData = (uint8_t)(0x10 + msgCount + i);
            if(rxMsg.data[i] != expectedData)
            {
                DebugP_log("[RX FIFO0 Thread] ERROR: Data mismatch at message %d, byte %d. Expected: 0x%02X, Got: 0x%02X\r\n",
                           msgCount, i, expectedData, rxMsg.data[i]);
                gMcanMtStopThreads = 1U;
                break;
            }
        }
        
        msgCount++;
        gMcanMtRxCount++;
    }
    
    
    /* Signal completion */
    SemaphoreP_post(&gMcanMtCompleteSem);
    
    TaskP_exit();
}

/**
 * \brief    TX FIFO + RX FIFO0 Concurrent Test
 *           Validates TX FIFO and RX FIFO0 operation with separate producer/consumer threads
 *           TX thread sends messages to TX FIFO
 *           RX thread receives messages from RX FIFO0
 *           Validates data integrity and FIFO management
 */
int32_t TestMcan_txFifoRxFifo0ConcurrentTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t configStatus = CSL_PASS;
    int32_t status;
    TaskP_Params taskParams;
    
    /* Reset counters */
    gMcanMtRxCount = 0U;
    gMcanMtStopThreads = 0U;
    
    /* Configure MCAN module */
    configStatus = App_mcanConfig(testParams);
    if(configStatus != CSL_PASS)
    {
        DebugP_log("[Main] ERROR: MCAN configuration failed\r\n");
        return configStatus;
    }
    
    /* gTxDoneSem and gRxDoneSem are already constructed by the test framework
     * (TestMcan_initTxRxSem) - do NOT construct them here to avoid corruption. */
    
    /* Enable MCAN Interrupts including RX FIFO0 and Transmission Complete */
    MCAN_enableIntr(gMcanBaseAddr, testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);
    
    /* Select Interrupt Line */
    MCAN_selectIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        MCAN_INTR_LINE_NUM_0);
    
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(gMcanBaseAddr,
                        MCAN_INTR_LINE_NUM_0,
                        1U);
    
    /* Enable TX FIFO interrupts - When using TX FIFO, need to enable for all potential indices */
    for(uint32_t i = 0; i < testParams->mcanConfigParams.ramConfig->txFIFOCnt; i++)
    {
        configStatus = MCAN_txBufTransIntrEnable(gMcanBaseAddr, i, (uint32_t)TRUE);
        if(configStatus != CSL_PASS)
        {
            DebugP_log("[Main] ERROR: TX FIFO interrupt enable failed for index %d\r\n", i);
            break;
        }
    }

    if(configStatus == CSL_PASS)
    {
        /* Create synchronization semaphores */
        status = SemaphoreP_constructBinary(&gMcanMtReadySem[0], 0);
        DebugP_assert(status == SystemP_SUCCESS);

        status = SemaphoreP_constructBinary(&gMcanMtReadySem[1], 0);
        DebugP_assert(status == SystemP_SUCCESS);

        /* Create counting semaphore for completion (max count = 2 for TX and RX threads) */
        status = SemaphoreP_constructCounting(&gMcanMtCompleteSem, 0, 2);
        DebugP_assert(status == SystemP_SUCCESS);

        /* Create TX FIFO Producer Task */
        TaskP_Params_init(&taskParams);
        taskParams.name = "MCAN_TX_FIFO";
        taskParams.stackSize = TEST_MCAN_MT_TASK_STACK_SIZE;
        taskParams.stack = gMcanMtTaskStack[0];
        taskParams.priority = TEST_MCAN_MT_TX_TASK_PRI;
        taskParams.args = testParams;
        taskParams.taskMain = TestMcan_txFifoThread;

        status = TaskP_construct(&gMcanMtTaskObj[0], &taskParams);
        if(status != SystemP_SUCCESS)
        {
            DebugP_log("[Main] ERROR: TX FIFO task creation failed\r\n");
            configStatus = CSL_EFAIL;
        }
    }

    if(configStatus == CSL_PASS)
    {
        /* Create RX FIFO0 Consumer Task */
        TaskP_Params_init(&taskParams);
        taskParams.name = "MCAN_RX_FIFO0";
        taskParams.stackSize = TEST_MCAN_MT_TASK_STACK_SIZE;
        taskParams.stack = gMcanMtTaskStack[1];
        taskParams.priority = TEST_MCAN_MT_TX_TASK_PRI;
        taskParams.args = testParams;
        taskParams.taskMain = TestMcan_rxFifo0Thread;

        status = TaskP_construct(&gMcanMtTaskObj[1], &taskParams);
        if(status != SystemP_SUCCESS)
        {
            DebugP_log("[Main] ERROR: RX FIFO0 task creation failed\r\n");
            configStatus = CSL_EFAIL;
        }
    }

    if(configStatus == CSL_PASS)
    {
        /* Wait for both threads to complete */
        SemaphoreP_pend(&gMcanMtCompleteSem, SystemP_WAIT_FOREVER);  /* TX complete */
        SemaphoreP_pend(&gMcanMtCompleteSem, SystemP_WAIT_FOREVER);  /* RX complete */

        /* Stop threads */
        gMcanMtStopThreads = 1U;

        /* Verify test results */
        if(gMcanMtRxCount != TEST_MCAN_MT_MESSAGE_COUNT)
        {
            DebugP_log("[Main] ERROR: RX count mismatch. Expected: %d, Got: %d\r\n",
                       TEST_MCAN_MT_MESSAGE_COUNT, gMcanMtRxCount);
            configStatus = CSL_EFAIL;
        }
        else
        {
            DebugP_log("\r\n[Main] TEST PASSED: All %d messages transmitted via TX FIFO and received via RX FIFO0\r\n",
                       TEST_MCAN_MT_MESSAGE_COUNT);
        }
    }

    /* Destruct tasks */
    TaskP_destruct(&gMcanMtTaskObj[0]);
    TaskP_destruct(&gMcanMtTaskObj[1]);

    /* Destruct only the semaphores created by this test.
     * gTxDoneSem and gRxDoneSem are managed by the test framework
     * (TestMcan_initTxRxSem/TestMcan_deInitTxRxSem) and must NOT be
     * destructed here to avoid corrupting the gTxRxSemInitDone state. */
    SemaphoreP_destruct(&gMcanMtReadySem[0]);
    SemaphoreP_destruct(&gMcanMtReadySem[1]);
    SemaphoreP_destruct(&gMcanMtCompleteSem);

    /* Disable TX FIFO interrupts */
    for(uint32_t i = 0; i < testParams->mcanConfigParams.ramConfig->txFIFOCnt; i++)
    {
        MCAN_txBufTransIntrEnable(gMcanBaseAddr, i, (uint32_t)FALSE);
    }

    return configStatus;
}

/**
 * \brief    ISR for MCAN Instance 0
 */
static void TestMcan_mcanInstance0ISR(void *arg)
{
    uint32_t intrStatus;
    
    intrStatus = MCAN_getIntrStatus(gMcanMtInstBaseAddr[0]);
    MCAN_clearIntrStatus(gMcanMtInstBaseAddr[0], intrStatus);
    
    if ((intrStatus & MCAN_INTR_SRC_TRANS_COMPLETE) == MCAN_INTR_SRC_TRANS_COMPLETE)
    {
        SemaphoreP_post(&gMcanMtPerThreadTxSem[0]);
    }
    
    uint32_t rxIntrMask = MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG |
                          MCAN_INTR_SRC_RX_FIFO0_NEW_MSG |
                          MCAN_INTR_SRC_RX_FIFO1_NEW_MSG |
                          MCAN_INTR_SRC_HIGH_PRIO_MSG;
    if ((intrStatus & rxIntrMask) != 0U)
    {
        SemaphoreP_post(&gMcanMtPerThreadRxSem[0]);
    }
}

/**
 * \brief    ISR for MCAN Instance 1
 */
static void TestMcan_mcanInstance1ISR(void *arg)
{
    uint32_t intrStatus;
    
    intrStatus = MCAN_getIntrStatus(gMcanMtInstBaseAddr[1]);
    MCAN_clearIntrStatus(gMcanMtInstBaseAddr[1], intrStatus);
    
    if ((intrStatus & MCAN_INTR_SRC_TRANS_COMPLETE) == MCAN_INTR_SRC_TRANS_COMPLETE)
    {
        SemaphoreP_post(&gMcanMtPerThreadTxSem[1]);
    }
    
    uint32_t rxIntrMask = MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG |
                          MCAN_INTR_SRC_RX_FIFO0_NEW_MSG |
                          MCAN_INTR_SRC_RX_FIFO1_NEW_MSG |
                          MCAN_INTR_SRC_HIGH_PRIO_MSG;
    if ((intrStatus & rxIntrMask) != 0U)
    {
        SemaphoreP_post(&gMcanMtPerThreadRxSem[1]);
    }
}

/**
 * \brief    Helper function to configure MCAN with specific base address
 */
static int32_t TestMcan_mcanConfigInstance(uint32_t baseAddr, st_mcanTestcaseParams_t *testParams)
{
    uint32_t fdoe, loopCnt;
    int32_t configStatus = CSL_PASS;
    MCAN_RevisionId revId;

    /* Get MCANSS Revision ID */
    MCAN_getRevisionId(baseAddr, &revId);
    
    /* Enable Auto wakeup */
    fdoe = MCAN_isFDOpEnable(baseAddr);
    (void)fdoe;
    
    /* Wait for memory initialization to happen */
    while (FALSE == MCAN_isMemInitDone(baseAddr))
    {}
    
    /* Get endianess value */
    DebugP_assert(MCAN_getEndianVal(baseAddr) == 0x87654321U);
    
    /* Put MCAN in SW initialization mode */
    MCAN_setOpMode(baseAddr, MCAN_OPERATION_MODE_SW_INIT);
    while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(baseAddr))
    {}
    
    /* Initialize MCAN module */
    configStatus += MCAN_init(baseAddr, testParams->mcanConfigParams.initParams);
    if(configStatus != CSL_PASS)
    {
        return configStatus;
    }
    
    /* Configure MCAN module */
    configStatus += MCAN_config(baseAddr, testParams->mcanConfigParams.configParams);
    if(configStatus != CSL_PASS)
    {
        return configStatus;
    }
    
    /* Configure Bit timings */
    configStatus += MCAN_setBitTime(baseAddr, testParams->mcanConfigParams.bitTimings);
    if(configStatus != CSL_PASS)
    {
        return configStatus;
    }
    
    /* Set Extended ID Mask */
    configStatus += MCAN_setExtIDAndMask(baseAddr, 0x1FFFFFFFU);
    if(configStatus != CSL_PASS)
    {
        return configStatus;
    }
    
    /* Configure Message RAM Sections */
    configStatus += MCAN_calcMsgRamParamsStartAddr(testParams->mcanConfigParams.ramConfig);
    if(configStatus != CSL_PASS)
    {
        return configStatus;
    }
    
    configStatus += MCAN_msgRAMConfig(baseAddr, testParams->mcanConfigParams.ramConfig);
    if(configStatus != CSL_PASS)
    {
        return configStatus;
    }
    
    /* Configure Standard ID filters */
    for(loopCnt = 0U; loopCnt < testParams->mcanConfigParams.stdIdFiltNum; loopCnt++)
    {
        MCAN_addStdMsgIDFilter(baseAddr, loopCnt, &testParams->mcanConfigParams.stdIDFilter[loopCnt]);
    }
    
    /* Configure Extended ID filters */
    for(loopCnt = 0U; loopCnt < testParams->mcanConfigParams.extIdFiltNum; loopCnt++)
    {
        MCAN_addExtMsgIDFilter(baseAddr, loopCnt, &testParams->mcanConfigParams.extIDFilter[loopCnt]);
    }
    
    /* Configure ECC */
    MCAN_eccConfig(baseAddr, testParams->mcanConfigParams.eccConfigParams);
    
    /* Enable loopback for internal loopback test mode */
    if (testParams->mcanConfigParams.mcanTestType == MCAN_TEST_TYPE_INTERNAL_LOOPBACK)
    {
        MCAN_lpbkModeEnable(baseAddr, MCAN_LPBK_MODE_INTERNAL, TRUE);
    }
    
    /* Take MCAN out of the SW initialization mode */
    MCAN_setOpMode(baseAddr, MCAN_OPERATION_MODE_NORMAL);
    while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(baseAddr))
    {}
    
    return configStatus;
}

/**
 * \brief    MCAN Instance 0 Thread - Sends messages on MCAN0
 */
static void TestMcan_instance0Thread(void *args)
{
    McanInstanceThreadArgs_t *threadArgs = (McanInstanceThreadArgs_t *)args;
    MCAN_TxBufElement txMsg;
    uint32_t msgCount = 0U;
    int32_t status;
    uint32_t bufNum = 0U;
    
    /* Initialize TX message for Instance 0 */
    txMsg.id = (0x100U << 18U);  /* Standard ID 0x100 */
    txMsg.rtr = 0U;
    txMsg.xtd = 0U;  /* Standard ID */
    txMsg.esi = 0U;
    txMsg.dlc = MCAN_DATA_SIZE_8BYTES;
    txMsg.brs = 1U;  /* Bit rate switching */
    txMsg.fdf = 1U;  /* FD format */
    txMsg.efc = 1U;  /* Store Tx events */
    txMsg.mm = 0xAAU;  /* Marker for Instance 0 */
    
    /* Producer loop - send TEST_MCAN_MT_MESSAGE_COUNT messages */
    while(!gMcanMtStopThreads && (msgCount < TEST_MCAN_MT_MESSAGE_COUNT))
    {
        /* Fill unique data pattern */
        for(uint32_t i = 0; i < TEST_MCAN_MT_DATA_SIZE; i++)
        {
            txMsg.data[i] = (uint8_t)(msgCount + i + 0x10);
        }
        
        /* Write message to TX buffer */
        MCAN_writeMsgRam(threadArgs->baseAddr, 
                        MCAN_MEM_TYPE_BUF, 
                        bufNum,
                        &txMsg);
        
        /* Trigger transmission */
        status = MCAN_txBufAddReq(threadArgs->baseAddr, bufNum);
        if(status != CSL_PASS)
        {
            DebugP_log("\r\n[MCAN Instance 0] TX request failed\r\n");
            break;
        }
        
        /* Wait for TX confirmation */
        status = SemaphoreP_pend(threadArgs->txDoneSem, SystemP_WAIT_FOREVER);
        if(status == SystemP_SUCCESS)
        {
            gMcanMtPerThreadCount[0]++;
            msgCount++;
        }
        else
        {
            DebugP_log("\r\n[MCAN Instance 0] TX semaphore timeout\r\n");
            break;
        }
        
        /* Use alternate buffer (ping-pong) */
        bufNum = (bufNum + 1) % 2;
        
        /* Small delay for stability */
        ClockP_usleep(2000);
    }

    /* Signal completion */
    SemaphoreP_post(&gMcanMtCompleteSem);
    
    TaskP_exit();
}

/**
 * \brief    MCAN Instance 1 Thread - Sends messages on MCAN1
 */
static void TestMcan_instance1Thread(void *args)
{
    McanInstanceThreadArgs_t *threadArgs = (McanInstanceThreadArgs_t *)args;
    MCAN_TxBufElement txMsg;
    uint32_t msgCount = 0U;
    int32_t status;
    uint32_t bufNum = 0U;
    
    /* Initialize TX message for Instance 1 */
    txMsg.id = (0x200U << 18U);  /* Standard ID 0x200 */
    txMsg.rtr = 0U;
    txMsg.xtd = 0U;  /* Standard ID */
    txMsg.esi = 0U;
    txMsg.dlc = MCAN_DATA_SIZE_8BYTES;
    txMsg.brs = 1U;  /* Bit rate switching */
    txMsg.fdf = 1U;  /* FD format */
    txMsg.efc = 1U;  /* Store Tx events */
    txMsg.mm = 0xBBU;  /* Marker for Instance 1 */
    
    /* Producer loop - send TEST_MCAN_MT_MESSAGE_COUNT messages */
    while(!gMcanMtStopThreads && (msgCount < TEST_MCAN_MT_MESSAGE_COUNT))
    {
        /* Fill unique data pattern */
        for(uint32_t i = 0; i < TEST_MCAN_MT_DATA_SIZE; i++)
        {
            txMsg.data[i] = (uint8_t)(msgCount + i + 0x20);
        }
        
        /* Write message to TX buffer */
        MCAN_writeMsgRam(threadArgs->baseAddr, 
                        MCAN_MEM_TYPE_BUF, 
                        bufNum,
                        &txMsg);
        
        /* Trigger transmission */
        status = MCAN_txBufAddReq(threadArgs->baseAddr, bufNum);
        if(status != CSL_PASS)
        {
            DebugP_log("\r\n[MCAN Instance 1] TX request failed\r\n");
            break;
        }
        
        /* Wait for TX confirmation */
        status = SemaphoreP_pend(threadArgs->txDoneSem, SystemP_WAIT_FOREVER);
        if(status == SystemP_SUCCESS)
        {
            gMcanMtPerThreadCount[1]++;
            msgCount++;
        }
        else
        {
            DebugP_log("\r\n[MCAN Instance 1] TX semaphore timeout\r\n");
            break;
        }
        
        /* Use alternate buffer (ping-pong) */
        bufNum = (bufNum + 1) % 2;
        
        /* Small delay for stability */
        ClockP_usleep(2000);
    }
    
    /* Signal completion */
    SemaphoreP_post(&gMcanMtCompleteSem);
    
    TaskP_exit();
}

/**
 * \brief    Multi-Instance Test - Two threads using MCAN0 and MCAN1 simultaneously
 *           Thread 1 transmits on MCAN Instance 0
 *           Thread 2 transmits on MCAN Instance 1
 *           Validates independent operation of multiple MCAN instances in loopback mode
 */
int32_t TestMcan_multiInstanceTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t configStatus = CSL_PASS;
    int32_t status;
    TaskP_Params taskParams;
    HwiP_Params hwiPrms;
    McanInstanceThreadArgs_t inst0Args, inst1Args;
    
    /* Reset counters */
    gMcanMtPerThreadCount[0] = 0U;
    gMcanMtPerThreadCount[1] = 0U;
    gMcanMtStopThreads = 0U;
    
    /* Get base addresses for both instances */
    gMcanMtInstBaseAddr[0] = CONFIG_MCAN0_BASE_ADDR;
    #if !defined (A53_CORE)
    gMcanMtInstBaseAddr[1] = CONFIG_MCAN1_BASE_ADDR;
    #endif
    /* Translate addresses */
    gMcanMtInstBaseAddr[0] = (uint32_t)AddrTranslateP_getLocalAddr(gMcanMtInstBaseAddr[0]);
    gMcanMtInstBaseAddr[1] = (uint32_t)AddrTranslateP_getLocalAddr(gMcanMtInstBaseAddr[1]);
    
    /* Reset both MCAN instances */
    MCAN_reset(gMcanMtInstBaseAddr[0]);
    MCAN_lpbkModeEnable(gMcanMtInstBaseAddr[0], MCAN_LPBK_MODE_INTERNAL, FALSE);
    while (MCAN_isInReset(gMcanMtInstBaseAddr[0]) == (uint32_t)TRUE)
    {}
    
    MCAN_reset(gMcanMtInstBaseAddr[1]);
    MCAN_lpbkModeEnable(gMcanMtInstBaseAddr[1], MCAN_LPBK_MODE_INTERNAL, FALSE);
    while (MCAN_isInReset(gMcanMtInstBaseAddr[1]) == (uint32_t)TRUE)
    {}
    
    /* Configure MCAN Instance 0 */
    configStatus = TestMcan_mcanConfigInstance(gMcanMtInstBaseAddr[0], testParams);
    if(configStatus != CSL_PASS)
    {
        DebugP_log("\r\nError in MCAN0 Configuration\r\n");
        return configStatus;
    }
    
    /* Configure MCAN Instance 1 */
    configStatus = TestMcan_mcanConfigInstance(gMcanMtInstBaseAddr[1], testParams);
    if(configStatus != CSL_PASS)
    {
        DebugP_log("\r\nError in MCAN1 Configuration\r\n");
        return configStatus;
    }
    
    /* Create binary semaphores for TX/RX done signaling */
    status = SemaphoreP_constructBinary(&gMcanMtPerThreadTxSem[0], 0);
    DebugP_assert(status == SystemP_SUCCESS);
    
    status = SemaphoreP_constructBinary(&gMcanMtPerThreadTxSem[1], 0);
    DebugP_assert(status == SystemP_SUCCESS);
    
    status = SemaphoreP_constructBinary(&gMcanMtPerThreadRxSem[0], 0);
    DebugP_assert(status == SystemP_SUCCESS);
    
    status = SemaphoreP_constructBinary(&gMcanMtPerThreadRxSem[1], 0);
    DebugP_assert(status == SystemP_SUCCESS);
    
    /* Register MCAN0 Interrupt */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum      = CONFIG_MCAN0_INTR;
    hwiPrms.callback    = &TestMcan_mcanInstance0ISR;
    hwiPrms.isPulse     = FALSE;
    status = HwiP_construct(&gMcanMtHwiObj[0], &hwiPrms);
    if(status != SystemP_SUCCESS)
    {
        DebugP_log("\r\nMCAN0 Interrupt Registration Failed\r\n");
        configStatus = CSL_EFAIL;
    }

    if(configStatus == CSL_PASS)
    {
        /* Register MCAN1 Interrupt */
        HwiP_Params_init(&hwiPrms);
        #if !defined (A53_CORE)
        hwiPrms.intNum      = CONFIG_MCAN1_INTR;
        #endif
        hwiPrms.callback    = &TestMcan_mcanInstance1ISR;
        hwiPrms.isPulse     = FALSE;
        status = HwiP_construct(&gMcanMtHwiObj[1], &hwiPrms);
        if(status != SystemP_SUCCESS)
        {
            DebugP_log("\r\nMCAN1 Interrupt Registration Failed\r\n");
            configStatus = CSL_EFAIL;
        }
    }

    if(configStatus == CSL_PASS)
    {
        /* Enable MCAN0 Interrupts */
        MCAN_enableIntr(gMcanMtInstBaseAddr[0], testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);
        MCAN_selectIntrLine(gMcanMtInstBaseAddr[0],
                            testParams->mcanConfigParams.intrLineSelectMask,
                            testParams->mcanConfigParams.intrLine);
        MCAN_enableIntrLine(gMcanMtInstBaseAddr[0],
                            testParams->mcanConfigParams.intrLine,
                            (uint32_t)TRUE);

        /* Enable Transmission interrupt for MCAN0 TX buffers */
        configStatus = MCAN_txBufTransIntrEnable(gMcanMtInstBaseAddr[0], 0U, (uint32_t)TRUE);
        if(configStatus != CSL_PASS)
        {
            DebugP_log("\r\nMCAN0 TX Buffer 0 interrupt enable failed\r\n");
        }
    }

    if(configStatus == CSL_PASS)
    {
        configStatus = MCAN_txBufTransIntrEnable(gMcanMtInstBaseAddr[0], 1U, (uint32_t)TRUE);
        if(configStatus != CSL_PASS)
        {
            DebugP_log("\r\nMCAN0 TX Buffer 1 interrupt enable failed\r\n");
        }
    }

    if(configStatus == CSL_PASS)
    {
        /* Enable MCAN1 Interrupts */
        MCAN_enableIntr(gMcanMtInstBaseAddr[1], testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);
        MCAN_selectIntrLine(gMcanMtInstBaseAddr[1],
                            testParams->mcanConfigParams.intrLineSelectMask,
                            testParams->mcanConfigParams.intrLine);
        MCAN_enableIntrLine(gMcanMtInstBaseAddr[1],
                            testParams->mcanConfigParams.intrLine,
                            (uint32_t)TRUE);

        /* Enable Transmission interrupt for MCAN1 TX buffers */
        configStatus = MCAN_txBufTransIntrEnable(gMcanMtInstBaseAddr[1], 0U, (uint32_t)TRUE);
        if(configStatus != CSL_PASS)
        {
            DebugP_log("\r\nMCAN1 TX Buffer 0 interrupt enable failed\r\n");
        }
    }

    if(configStatus == CSL_PASS)
    {
        configStatus = MCAN_txBufTransIntrEnable(gMcanMtInstBaseAddr[1], 1U, (uint32_t)TRUE);
        if(configStatus != CSL_PASS)
        {
            DebugP_log("\r\nMCAN1 TX Buffer 1 interrupt enable failed\r\n");
        }
    }

    if(configStatus == CSL_PASS)
    {
        /* Create counting semaphore for completion (max count = 2 for both threads) */
        status = SemaphoreP_constructCounting(&gMcanMtCompleteSem, 0, 2);
        DebugP_assert(status == SystemP_SUCCESS);

        /* Prepare thread arguments for Instance 0 */
        inst0Args.baseAddr = gMcanMtInstBaseAddr[0];
        inst0Args.instanceId = 0U;
        inst0Args.testParams = testParams;
        inst0Args.txDoneSem = &gMcanMtPerThreadTxSem[0];
        inst0Args.rxDoneSem = &gMcanMtPerThreadRxSem[0];

        /* Prepare thread arguments for Instance 1 */
        inst1Args.baseAddr = gMcanMtInstBaseAddr[1];
        inst1Args.instanceId = 1U;
        inst1Args.testParams = testParams;
        inst1Args.txDoneSem = &gMcanMtPerThreadTxSem[1];
        inst1Args.rxDoneSem = &gMcanMtPerThreadRxSem[1];

        /* Create MCAN Instance 0 Task using TaskP_construct */
        TaskP_Params_init(&taskParams);
        taskParams.name = "MCAN_INST0_TX";
        taskParams.stackSize = TEST_MCAN_MT_TASK_STACK_SIZE;
        taskParams.stack = gMcanMtTaskStack[0];
        taskParams.priority = TEST_MCAN_MT_TX_TASK_PRI;
        taskParams.args = &inst0Args;
        taskParams.taskMain = TestMcan_instance0Thread;

        status = TaskP_construct(&gMcanMtTaskObj[0], &taskParams);
        if(status != SystemP_SUCCESS)
        {
            DebugP_log("\r\nMCAN Instance 0 Task creation failed\r\n");
            configStatus = CSL_EFAIL;
        }
    }

    if(configStatus == CSL_PASS)
    {
        /* Create MCAN Instance 1 Task using TaskP_construct */
        TaskP_Params_init(&taskParams);
        taskParams.name = "MCAN_INST1_TX";
        taskParams.stackSize = TEST_MCAN_MT_TASK_STACK_SIZE;
        taskParams.stack = gMcanMtTaskStack[1];
        taskParams.priority = TEST_MCAN_MT_TX_TASK_PRI;
        taskParams.args = &inst1Args;
        taskParams.taskMain = TestMcan_instance1Thread;

        status = TaskP_construct(&gMcanMtTaskObj[1], &taskParams);
        if(status != SystemP_SUCCESS)
        {
            DebugP_log("\r\nMCAN Instance 1 Task creation failed\r\n");
            configStatus = CSL_EFAIL;
        }
    }

    if(configStatus == CSL_PASS)
    {
        /* Wait for both threads to complete */
        SemaphoreP_pend(&gMcanMtCompleteSem, SystemP_WAIT_FOREVER);  /* Instance 0 complete */
        SemaphoreP_pend(&gMcanMtCompleteSem, SystemP_WAIT_FOREVER);  /* Instance 1 complete */

        /* Stop threads */
        gMcanMtStopThreads = 1U;

        /* Verify both instances transmitted expected number of messages */
        if(gMcanMtPerThreadCount[0] != TEST_MCAN_MT_MESSAGE_COUNT)
        {
            DebugP_log("\r\n[FAIL] MCAN Instance 0: Expected %d messages, got %d\r\n",
                       TEST_MCAN_MT_MESSAGE_COUNT, gMcanMtPerThreadCount[0]);
            configStatus = CSL_EFAIL;
        }

        if(gMcanMtPerThreadCount[1] != TEST_MCAN_MT_MESSAGE_COUNT)
        {
            DebugP_log("\r\n[FAIL] MCAN Instance 1: Expected %d messages, got %d\r\n",
                       TEST_MCAN_MT_MESSAGE_COUNT, gMcanMtPerThreadCount[1]);
            configStatus = CSL_EFAIL;
        }
    }

    /* Destruct tasks */
    TaskP_destruct(&gMcanMtTaskObj[0]);
    TaskP_destruct(&gMcanMtTaskObj[1]);
    
    /* Unregister interrupts */
    HwiP_destruct(&gMcanMtHwiObj[0]);
    HwiP_destruct(&gMcanMtHwiObj[1]);
    
    /* Destruct semaphores */
    SemaphoreP_destruct(&gMcanMtPerThreadTxSem[0]);
    SemaphoreP_destruct(&gMcanMtPerThreadTxSem[1]);
    SemaphoreP_destruct(&gMcanMtPerThreadRxSem[0]);
    SemaphoreP_destruct(&gMcanMtPerThreadRxSem[1]);
    SemaphoreP_destruct(&gMcanMtCompleteSem);
    
    /* Disable TX buffer interrupts for both instances */
    MCAN_txBufTransIntrEnable(gMcanMtInstBaseAddr[0], 0U, (uint32_t)FALSE);
    MCAN_txBufTransIntrEnable(gMcanMtInstBaseAddr[0], 1U, (uint32_t)FALSE);
    MCAN_txBufTransIntrEnable(gMcanMtInstBaseAddr[1], 0U, (uint32_t)FALSE);
    MCAN_txBufTransIntrEnable(gMcanMtInstBaseAddr[1], 1U, (uint32_t)FALSE);
    
    return configStatus;
}

/**
 * \brief Helper function to validate TxEvent FIFO element against transmitted message
 */
static int32_t TestMcan_validateTxEvent(MCAN_TxBufElement *txMsg, MCAN_TxEventFIFOElement *txEventMsg, uint32_t threadId)
{
    int32_t retStatus = CSL_PASS;

    if ((txMsg->id != txEventMsg->id) ||
        (txMsg->rtr != txEventMsg->rtr) ||
        (txMsg->xtd != txEventMsg->xtd) ||
        (txMsg->esi != txEventMsg->esi) ||
        (txMsg->dlc != txEventMsg->dlc) ||
        (txMsg->brs != txEventMsg->brs) ||
        (txMsg->fdf != txEventMsg->fdf) ||
        (txMsg->mm != txEventMsg->mm))
    {
        DebugP_log("[Thread %d] ERROR: TxEvent mismatch!\r\n", threadId);
        DebugP_log("  Expected: ID=0x%X, RTR=%d, XTD=%d, ESI=%d, DLC=%d, BRS=%d, FDF=%d, MM=0x%02X\r\n",
                   txMsg->id, txMsg->rtr, txMsg->xtd, txMsg->esi, txMsg->dlc, txMsg->brs, txMsg->fdf, txMsg->mm);
        DebugP_log("  Received: ID=0x%X, RTR=%d, XTD=%d, ESI=%d, DLC=%d, BRS=%d, FDF=%d, MM=0x%02X\r\n",
                   txEventMsg->id, txEventMsg->rtr, txEventMsg->xtd, txEventMsg->esi, txEventMsg->dlc, 
                   txEventMsg->brs, txEventMsg->fdf, txEventMsg->mm);
        retStatus = CSL_EFAIL;
    }
    else
    {
        DebugP_log("[Thread %d] TxEvent validated successfully (MM=0x%02X)\r\n", threadId, txEventMsg->mm);
    }

    return retStatus;
}

/**
 * \brief Thread 1: Transmits Classic CAN frames (no FD, no BRS) with TxEvent validation
 */
static void TestMcan_classicCanTxThread(void *args)
{
    MCAN_TxBufElement txMsg;
    MCAN_TxEventFIFOElement txEventElem;
    MCAN_TxEventFIFOStatus txEventFIFOStatus;
    uint32_t msgCount = 0U;
    int32_t status;
    uint32_t bufNum = 0U;  /* Use TX buffer 0 */
    uint32_t txStatus;
    uint32_t bitPos;
    
    /* Initialize Classic CAN TX message */
    txMsg.id = (0x100U << 18U);  /* Standard ID 0x100 */
    txMsg.rtr = 0U;
    txMsg.xtd = 0U;  /* Standard ID */
    txMsg.esi = 0U;
    txMsg.dlc = MCAN_DATA_SIZE_8BYTES;
    txMsg.brs = 0U;  /* NO Bit rate switching - Classic CAN */
    txMsg.fdf = 0U;  /* NO FD format - Classic CAN */
    txMsg.efc = 1U;  /* Store Tx events */
    txMsg.mm = 0xCCU;  /* Message Marker for Classic CAN - 0xCC */
    
    /* Wait for start signal */
    SemaphoreP_pend(&gMcanMtStartSem, SystemP_WAIT_FOREVER);
    
    /* Transmit loop - send Classic CAN messages */
    while(!gMcanMtStopThreads && (msgCount < TEST_MCAN_MT_MESSAGE_COUNT))
    {
        /* Fill unique data pattern - Classic CAN uses 0xC0 + msgCount */
        for(uint32_t i = 0; i < TEST_MCAN_MT_DATA_SIZE; i++)
        {
            txMsg.data[i] = (uint8_t)(0xC0 + msgCount + i);
        }
        
        /* Write message to TX buffer 0 */
        MCAN_writeMsgRam(gMcanBaseAddr, 
                        MCAN_MEM_TYPE_BUF,
                        bufNum,
                        &txMsg);
        
        /* Trigger transmission */
        status = MCAN_txBufAddReq(gMcanBaseAddr, bufNum);
        if(status != CSL_PASS)
        {
            DebugP_log("[Classic CAN Thread] ERROR: Failed to add TX request for buffer %d\r\n", bufNum);
            gMcanMtPerThreadErrors[0]++;
        }

        /* Poll for TX completion (buffer 0) - only if TX request was successful */
        if(status == CSL_PASS)
        {
        bitPos = (1U << bufNum);
        do
        {
            txStatus = MCAN_getTxBufTransmissionStatus(gMcanBaseAddr);
            if(gMcanMtStopThreads)
            {
                break;
            }
        } while((txStatus & bitPos) != bitPos);
        }
        
        if(!gMcanMtStopThreads)
        {
            /* Read and validate TxEvent FIFO */
            MCAN_getTxEventFIFOStatus(gMcanBaseAddr, &txEventFIFOStatus);
            if(txEventFIFOStatus.fillLvl > 0)
            {
                MCAN_readTxEventFIFO(gMcanBaseAddr, &txEventElem);
                MCAN_writeTxEventFIFOAck(gMcanBaseAddr, txEventFIFOStatus.getIdx);
                
                /* Validate TxEvent */
                status = TestMcan_validateTxEvent(&txMsg, &txEventElem, 1);
                if(status != CSL_PASS)
                {
                    DebugP_log("[Classic CAN Thread] ERROR: TxEvent validation failed for message %d\r\n", msgCount + 1);
                    gMcanMtPerThreadErrors[0]++;
                }
            }
            else
            {
                DebugP_log("[Classic CAN Thread] ERROR: No TxEvent available for message %d\r\n", msgCount + 1);
                gMcanMtPerThreadErrors[0]++;
            }
            
            gMcanMtPerThreadCount[0]++;
            msgCount++;
        }
        
        /* Small delay between messages */
        ClockP_usleep(2000);
    }
    
    /* Signal completion */
    SemaphoreP_post(&gMcanMtCompleteSem);
    
    TaskP_exit();
}

/**
 * \brief Thread 2: Transmits CAN FD frames (with FD and BRS) with TxEvent validation
 */
static void TestMcan_canFdTxThread(void *args)
{
    MCAN_TxBufElement txMsg;
    MCAN_TxEventFIFOElement txEventElem;
    MCAN_TxEventFIFOStatus txEventFIFOStatus;
    uint32_t msgCount = 0U;
    int32_t status;
    uint32_t bufNum = 1U;  /* Use TX buffer 1 */
    uint32_t txStatus;
    uint32_t bitPos;
    
    /* Initialize CAN FD TX message */
    txMsg.id = (0x200U << 18U);  /* Standard ID 0x200 */
    txMsg.rtr = 0U;
    txMsg.xtd = 0U;  /* Standard ID */
    txMsg.esi = 0U;
    txMsg.dlc = MCAN_DATA_SIZE_8BYTES;
    txMsg.brs = 1U;  /* Bit rate switching - CAN FD */
    txMsg.fdf = 1U;  /* FD format - CAN FD */
    txMsg.efc = 1U;  /* Store Tx events */
    txMsg.mm = 0xFDU;  /* Message Marker for CAN FD - 0xFD */
    
    /* Wait for start signal */
    SemaphoreP_pend(&gMcanMtStartSem, SystemP_WAIT_FOREVER);
    
    /* Transmit loop - send CAN FD messages */
    while(!gMcanMtStopThreads && (msgCount < TEST_MCAN_MT_MESSAGE_COUNT))
    {
        /* Fill unique data pattern - CAN FD uses 0xF0 + msgCount */
        for(uint32_t i = 0; i < TEST_MCAN_MT_DATA_SIZE; i++)
        {
            txMsg.data[i] = (uint8_t)(0xF0 + msgCount + i);
        }
        
        /* Write message to TX buffer 1 */
        MCAN_writeMsgRam(gMcanBaseAddr, 
                        MCAN_MEM_TYPE_BUF,
                        bufNum,
                        &txMsg);
        
        /* Trigger transmission */
        status = MCAN_txBufAddReq(gMcanBaseAddr, bufNum);
        if(status != CSL_PASS)
        {
            DebugP_log("[CAN FD Thread] ERROR: Failed to add TX request for buffer %d\r\n", bufNum);
            gMcanMtPerThreadErrors[1]++;
        }

        /* Poll for TX completion (buffer 1) - only if TX request was successful */
        if(status == CSL_PASS)
        {
        bitPos = (1U << bufNum);
        do
        {
            txStatus = MCAN_getTxBufTransmissionStatus(gMcanBaseAddr);
            if(gMcanMtStopThreads)
            {
                break;
            }
        } while((txStatus & bitPos) != bitPos);
        }
        
        if(!gMcanMtStopThreads)
        {
            /* Read and validate TxEvent FIFO */
            MCAN_getTxEventFIFOStatus(gMcanBaseAddr, &txEventFIFOStatus);
            if(txEventFIFOStatus.fillLvl > 0)
            {
                MCAN_readTxEventFIFO(gMcanBaseAddr, &txEventElem);
                MCAN_writeTxEventFIFOAck(gMcanBaseAddr, txEventFIFOStatus.getIdx);
                
                /* Validate TxEvent */
                status = TestMcan_validateTxEvent(&txMsg, &txEventElem, 2);
                if(status != CSL_PASS)
                {
                    DebugP_log("[CAN FD Thread] ERROR: TxEvent validation failed for message %d\r\n", msgCount + 1);
                    gMcanMtPerThreadErrors[1]++;
                }
            }
            else
            {
                DebugP_log("[CAN FD Thread] ERROR: No TxEvent available for message %d\r\n", msgCount + 1);
                gMcanMtPerThreadErrors[1]++;
            }
            
            gMcanMtPerThreadCount[1]++;
            msgCount++;
        }
        
        /* Small delay between messages */
        ClockP_usleep(2000);
    }
    
    /* Signal completion */
    SemaphoreP_post(&gMcanMtCompleteSem);
    
    TaskP_exit();
}

/**
 * \brief Parallel transmission test of Classic CAN and CAN FD frames from two threads
 *        Validates no corruption and correct TxEvent entries for both frame types
 */
int32_t TestMcan_parallelClassicCanFdTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t configStatus = CSL_PASS;
    int32_t status;
    TaskP_Params taskParams;

    /* Reset counters */
    gMcanMtPerThreadCount[0] = 0U;
    gMcanMtPerThreadCount[1] = 0U;
    gMcanMtPerThreadErrors[0] = 0U;
    gMcanMtPerThreadErrors[1] = 0U;
    gMcanMtStopThreads = 0U;
    
    /* Configure MCAN module */
    configStatus = App_mcanConfig(testParams);
    if(configStatus != CSL_PASS)
    {
        DebugP_log("ERROR: MCAN configuration failed!\r\n");
        return CSL_EFAIL;
    }
    
    /* Create synchronization semaphores */
    status = SemaphoreP_constructCounting(&gMcanMtStartSem, 0, 2);
    DebugP_assert(status == SystemP_SUCCESS);
    
    status = SemaphoreP_constructCounting(&gMcanMtCompleteSem, 0, 2);
    DebugP_assert(status == SystemP_SUCCESS);
    
    /* Enable MCAN Interrupts */
    MCAN_enableIntr(gMcanBaseAddr, testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);
    
    /* Select Interrupt Line */
    MCAN_selectIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);
    
    /* Enable Interrupt Line */
    MCAN_enableIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        1U);
    
    /* Enable Transmission interrupt for TX buffers 0 and 1 */
    configStatus = MCAN_txBufTransIntrEnable(gMcanBaseAddr, 0U, (uint32_t)TRUE);
    if(configStatus != CSL_PASS)
    {
        DebugP_log("ERROR: MCAN Tx Buffer 0 Interrupt Enable FAILED\r\n");
        return CSL_EFAIL;
    }
    
    configStatus = MCAN_txBufTransIntrEnable(gMcanBaseAddr, 1U, (uint32_t)TRUE);
    if(configStatus != CSL_PASS)
    {
        DebugP_log("ERROR: MCAN Tx Buffer 1 Interrupt Enable FAILED\r\n");
        return CSL_EFAIL;
    }
    
    /* Create Classic CAN TX Task using TaskP_construct */
    TaskP_Params_init(&taskParams);
    taskParams.name = "MCAN_CLASSIC_TX";
    taskParams.stackSize = TEST_MCAN_MT_TASK_STACK_SIZE;
    taskParams.stack = gMcanMtTaskStack[0];
    taskParams.priority = TEST_MCAN_MT_TX_TASK_PRI;
    taskParams.args = testParams;
    taskParams.taskMain = TestMcan_classicCanTxThread;
    
    status = TaskP_construct(&gMcanMtTaskObj[0], &taskParams);
    if(status != SystemP_SUCCESS)
    {
        DebugP_log("ERROR: Failed to create Classic CAN TX thread!\r\n");
        configStatus = CSL_EFAIL;
    }

    if(configStatus == CSL_PASS)
    {
        /* Create CAN FD TX Task using TaskP_construct */
        TaskP_Params_init(&taskParams);
        taskParams.name = "MCAN_CANFD_TX";
        taskParams.stackSize = TEST_MCAN_MT_TASK_STACK_SIZE;
        taskParams.stack = gMcanMtTaskStack[1];
        taskParams.priority = TEST_MCAN_MT_TX_TASK_PRI;
        taskParams.args = testParams;
        taskParams.taskMain = TestMcan_canFdTxThread;

        status = TaskP_construct(&gMcanMtTaskObj[1], &taskParams);
        if(status != SystemP_SUCCESS)
        {
            DebugP_log("ERROR: Failed to create CAN FD TX thread!\r\n");
            configStatus = CSL_EFAIL;
        }
    }

    if(configStatus == CSL_PASS)
    {
        /* Start both threads simultaneously */
        SemaphoreP_post(&gMcanMtStartSem);  /* Signal Classic CAN thread */
        SemaphoreP_post(&gMcanMtStartSem);  /* Signal CAN FD thread */

        /* Wait for both threads to complete */
        SemaphoreP_pend(&gMcanMtCompleteSem, SystemP_WAIT_FOREVER);  /* Classic CAN complete */
        SemaphoreP_pend(&gMcanMtCompleteSem, SystemP_WAIT_FOREVER);  /* CAN FD complete */

        /* Stop threads */
        gMcanMtStopThreads = 1U;

        if(gMcanMtPerThreadCount[0] != TEST_MCAN_MT_MESSAGE_COUNT)
        {
            DebugP_log("[FAIL] Classic CAN: Expected %d messages, got %d\r\n",
                       TEST_MCAN_MT_MESSAGE_COUNT, gMcanMtPerThreadCount[0]);
            configStatus = CSL_EFAIL;
        }

        if(gMcanMtPerThreadCount[1] != TEST_MCAN_MT_MESSAGE_COUNT)
        {
            DebugP_log("[FAIL] CAN FD: Expected %d messages, got %d\r\n",
                       TEST_MCAN_MT_MESSAGE_COUNT, gMcanMtPerThreadCount[1]);
            configStatus = CSL_EFAIL;
        }

        if(gMcanMtPerThreadErrors[0] > 0)
        {
            DebugP_log("[FAIL] Classic CAN: Detected %d errors during transmission or TxEvent validation\r\n",
                       gMcanMtPerThreadErrors[0]);
            configStatus = CSL_EFAIL;
        }

        if(gMcanMtPerThreadErrors[1] > 0)
        {
            DebugP_log("[FAIL] CAN FD: Detected %d errors during transmission or TxEvent validation\r\n",
                       gMcanMtPerThreadErrors[1]);
            configStatus = CSL_EFAIL;
        }

        if(configStatus == CSL_PASS)
        {
            DebugP_log("\r\n[PASS] Parallel Classic CAN and CAN FD transmission test completed successfully!\r\n");
        }
        else
        {
            DebugP_log("\r\n[FAIL] Parallel transmission test failed!\r\n");
        }
    }

    /* Destruct tasks */
    TaskP_destruct(&gMcanMtTaskObj[0]);
    TaskP_destruct(&gMcanMtTaskObj[1]);

    /* Destruct semaphores */
    SemaphoreP_destruct(&gMcanMtStartSem);
    SemaphoreP_destruct(&gMcanMtCompleteSem);

    /* Disable TX buffer interrupts */
    MCAN_txBufTransIntrEnable(gMcanBaseAddr, 0U, (uint32_t)FALSE);
    MCAN_txBufTransIntrEnable(gMcanBaseAddr, 1U, (uint32_t)FALSE);

    return configStatus;
}
/**
 * \brief    Custom ISR for interrupt + polling multi-thread test.
 *           Posts gTxDoneSem on TX complete (MCAN_INTR_SRC_TRANS_COMPLETE)
 *           and gMcanMtPerThreadRxSem[0] on dedicated RX buffer new-data (DRX) only.
 *           FIFO0/FIFO1 events are intentionally NOT handled here since the
 *           polling thread manages FIFO0 RX via status-register polling.
 */
static void TestMcan_intrPollISR(void *arg)
{
    uint32_t intrStatus;

    intrStatus = MCAN_getIntrStatus(gMcanBaseAddr);
    MCAN_clearIntrStatus(gMcanBaseAddr, intrStatus);

    /* TX completion — post gTxDoneSem for interrupt thread */
    if ((intrStatus & MCAN_INTR_SRC_TRANS_COMPLETE) != 0U)
    {
        SemaphoreP_post(&gTxDoneSem);
    }

    /* Dedicated RX buffer new data — post gMcanMtPerThreadRxSem[0].
     * Only DRX is handled; FIFO0/FIFO1 events are left for the polling thread. */
    if ((intrStatus & MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG) != 0U)
    {
        SemaphoreP_post(&gMcanMtPerThreadRxSem[0]);
    }
}

/**
 * \brief Thread 1: Interrupt-mode TX and RX
 *        Sends messages via TX buffer 0, waits for TX done via gTxDoneSem (ISR).
 *        Receives messages via dedicated RX buffer 0, waits for RX done via
 *        gMcanMtPerThreadRxSem[0] (ISR posts on DRX interrupt).
 *        ID 0x04 is routed to dedicated RX buffer 0 by the message filter.
 */
static void TestMcan_intrModeTxRxThread(void *args)
{
    MCAN_TxBufElement txMsg;
    MCAN_RxBufElement rxMsg;
    MCAN_RxNewDataStatus newDataStatus;
    uint32_t msgCount = 0U;
    int32_t status;
    uint32_t bufNum = 0U;  /* TX buffer 0 for interrupt thread */
    uint32_t rxBufIdx = 0U; /* Dedicated RX buffer 0 */

    /* Initialize TX message - Standard ID 0x04 (routed to dedicated RX buffer 0 by filter) */
    txMsg.id = (0x04U << 18U);
    txMsg.rtr = 0U;
    txMsg.xtd = 0U;
    txMsg.esi = 0U;
    txMsg.dlc = MCAN_DATA_SIZE_8BYTES;
    txMsg.brs = 1U;
    txMsg.fdf = 1U;
    txMsg.efc = 1U;
    txMsg.mm = 0xAAU;  /* Message marker for interrupt thread */

    /* Wait for start signal */
    SemaphoreP_pend(&gMcanMtStartSem, SystemP_WAIT_FOREVER);

    /* TX/RX loop - send and receive messages using interrupts for both TX and RX */
    while(!gMcanMtStopThreads && (msgCount < TEST_MCAN_MT_MESSAGE_COUNT))
    {
        /* Fill data pattern - Interrupt thread uses 0xA0 + msgCount */
        for(uint32_t i = 0; i < TEST_MCAN_MT_DATA_SIZE; i++)
        {
            txMsg.data[i] = (uint8_t)(0xA0 + msgCount + i);
        }

        /* Write message to TX buffer 0 */
        MCAN_writeMsgRam(gMcanBaseAddr,
                        MCAN_MEM_TYPE_BUF,
                        bufNum,
                        &txMsg);

        /* Trigger transmission */
        status = MCAN_txBufAddReq(gMcanBaseAddr, bufNum);
        if(status != CSL_PASS)
        {
            DebugP_log("[Intr Thread] ERROR: TX request failed for msg %d\r\n", msgCount);
            gMcanMtPerThreadErrors[0]++;
            break;
        }

        /* Wait for TX completion via ISR -> gTxDoneSem */
        status = SemaphoreP_pend(&gTxDoneSem, SystemP_WAIT_FOREVER);
        if(status != SystemP_SUCCESS)
        {
            DebugP_log("[Intr Thread] ERROR: TX semaphore pend failed\r\n");
            gMcanMtPerThreadErrors[0]++;
            break;
        }

        /* Wait for RX completion via ISR -> gMcanMtPerThreadRxSem[0] (DRX interrupt) */
        status = SemaphoreP_pend(&gMcanMtPerThreadRxSem[0], SystemP_WAIT_FOREVER);
        if(status != SystemP_SUCCESS)
        {
            DebugP_log("[Intr Thread] ERROR: RX semaphore pend failed for msg %d\r\n", msgCount);
            gMcanMtPerThreadErrors[0]++;
            break;
        }

        /* Read from dedicated RX buffer 0 */
        MCAN_readMsgRam(gMcanBaseAddr,
                        MCAN_MEM_TYPE_BUF,
                        rxBufIdx,
                        MCAN_RX_FIFO_NUM_0,
                        &rxMsg);

        /* Clear new-data status for buffer 0 */
        newDataStatus.statusLow  = (1U << rxBufIdx);
        newDataStatus.statusHigh = 0U;
        MCAN_clearNewDataStatus(gMcanBaseAddr, &newDataStatus);

        /* Validate message ID */
        if((rxMsg.id & APP_MCAN_STD_ID_MASK) != (0x04U << APP_MCAN_STD_ID_SHIFT))
        {
            DebugP_log("[Intr Thread] ERROR: ID mismatch at msg %d. Expected: 0x%X, Got: 0x%X\r\n",
                      msgCount, (0x04U << APP_MCAN_STD_ID_SHIFT), rxMsg.id);
            gMcanMtPerThreadErrors[0]++;
        }

        /* Validate data pattern */
        for(uint32_t i = 0; i < TEST_MCAN_MT_DATA_SIZE; i++)
        {
            if(rxMsg.data[i] != (uint8_t)(0xA0 + msgCount + i))
            {
                DebugP_log("[Intr Thread] ERROR: Data[%d] mismatch at msg %d. Expected: 0x%02X, Got: 0x%02X\r\n",
                          i, msgCount, (uint8_t)(0xA0 + msgCount + i), rxMsg.data[i]);
                gMcanMtPerThreadErrors[0]++;
                break;
            }
        }

        gMcanMtPerThreadCount[0]++;
        msgCount++;
        DebugP_log("[Intr Thread] Message %d TX/RX OK\r\n", msgCount);

        /* Small delay for interleaving with polling thread */
        ClockP_usleep(1000);
    }

    /* Signal completion */
    SemaphoreP_post(&gMcanMtCompleteSem);

    TaskP_exit();
}

/**
 * \brief Thread 2: Polling-mode TX and RX
 *        Sends messages via TX buffer 1, polls MCAN_getTxBufTransmissionStatus for TX done.
 *        Polls MCAN_getRxFIFOStatus for RX FIFO 0 new message (ID 0x05 routed by filter 12).
 */
static void TestMcan_pollModeTxRxThread(void *args)
{
    MCAN_TxBufElement txMsg;
    MCAN_RxBufElement rxMsg;
    MCAN_RxFIFOStatus fifoStatus;
    uint32_t msgCount = 0U;
    int32_t status;
    uint32_t bufNum = 1U;  /* TX buffer 1 for polling thread */
    uint32_t txStatus;
    uint32_t bitPos;
    uint32_t pollTimeout;

    /* Initialize TX message - Standard ID 0x05 (routed to RX FIFO 0 by filter 12) */
    txMsg.id = (0x05U << 18U);
    txMsg.rtr = 0U;
    txMsg.xtd = 0U;
    txMsg.esi = 0U;
    txMsg.dlc = MCAN_DATA_SIZE_8BYTES;
    txMsg.brs = 1U;
    txMsg.fdf = 1U;
    txMsg.efc = 1U;
    txMsg.mm = 0xBBU;  /* Message marker for polling thread */

    /* Wait for start signal */
    SemaphoreP_pend(&gMcanMtStartSem, SystemP_WAIT_FOREVER);

    /* TX/RX loop - send and receive messages using polling */
    while(!gMcanMtStopThreads && (msgCount < TEST_MCAN_MT_MESSAGE_COUNT))
    {
        /* Fill data pattern - Polling thread uses 0xB0 + msgCount */
        for(uint32_t i = 0; i < TEST_MCAN_MT_DATA_SIZE; i++)
        {
            txMsg.data[i] = (uint8_t)(0xB0 + msgCount + i);
        }

        /* Write message to TX buffer 1 */
        MCAN_writeMsgRam(gMcanBaseAddr,
                        MCAN_MEM_TYPE_BUF,
                        bufNum,
                        &txMsg);

        /* Trigger transmission */
        status = MCAN_txBufAddReq(gMcanBaseAddr, bufNum);
        if(status != CSL_PASS)
        {
            DebugP_log("[Poll Thread] ERROR: TX request failed for msg %d\r\n", msgCount);
            gMcanMtPerThreadErrors[1]++;
            break;
        }

        /* Poll for TX completion on buffer 1 */
        bitPos = (1U << bufNum);
        pollTimeout = 100000U;
        do
        {
            txStatus = MCAN_getTxBufTransmissionStatus(gMcanBaseAddr);
            if(gMcanMtStopThreads)
            {
                break;
            }
            pollTimeout--;
        } while(((txStatus & bitPos) != bitPos) && (pollTimeout > 0U));

        if(pollTimeout == 0U)
        {
            DebugP_log("[Poll Thread] ERROR: TX poll timed out for msg %d\r\n", msgCount);
            gMcanMtPerThreadErrors[1]++;
            break;
        }

        if(gMcanMtStopThreads)
        {
            break;
        }

        /* Poll for RX message in RX FIFO0 */
        fifoStatus.num = MCAN_RX_FIFO_NUM_0;
        pollTimeout = 100000U;
        do
        {
            MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
            if(gMcanMtStopThreads)
            {
                break;
            }
            if(fifoStatus.fillLvl > 0U)
            {
                break;
            }
            pollTimeout--;
        } while(pollTimeout > 0U);

        if(pollTimeout == 0U)
        {
            DebugP_log("[Poll Thread] ERROR: RX poll timed out for msg %d\r\n", msgCount);
            gMcanMtPerThreadErrors[1]++;
            break;
        }

        if(gMcanMtStopThreads)
        {
            break;
        }

        /* Read message from RX FIFO0 */
        MCAN_readMsgRam(gMcanBaseAddr,
                        MCAN_MEM_TYPE_FIFO,
                        fifoStatus.getIdx,
                        (uint32_t)fifoStatus.num,
                        &rxMsg);

        /* Acknowledge the message */
        (void)MCAN_writeRxFIFOAck(gMcanBaseAddr,
                                  (uint32_t)fifoStatus.num,
                                  fifoStatus.getIdx);

        /* Validate message ID */
        if((rxMsg.id & APP_MCAN_STD_ID_MASK) != (0x05U << APP_MCAN_STD_ID_SHIFT))
        {
            DebugP_log("[Poll Thread] ERROR: ID mismatch at msg %d. Expected: 0x%X, Got: 0x%X\r\n",
                      msgCount, (0x05U << APP_MCAN_STD_ID_SHIFT), rxMsg.id);
            gMcanMtPerThreadErrors[1]++;
        }

        /* Validate data pattern */
        for(uint32_t i = 0; i < TEST_MCAN_MT_DATA_SIZE; i++)
        {
            if(rxMsg.data[i] != (uint8_t)(0xB0 + msgCount + i))
            {
                DebugP_log("[Poll Thread] ERROR: Data[%d] mismatch at msg %d. Expected: 0x%02X, Got: 0x%02X\r\n",
                          i, msgCount, (uint8_t)(0xB0 + msgCount + i), rxMsg.data[i]);
                gMcanMtPerThreadErrors[1]++;
                break;
            }
        }

        gMcanMtPerThreadCount[1]++;
        msgCount++;
        DebugP_log("[Poll Thread] Message %d TX/RX OK\r\n", msgCount);

        /* Small delay for interleaving with interrupt thread */
        ClockP_usleep(1000);
    }

    /* Signal completion */
    SemaphoreP_post(&gMcanMtCompleteSem);

    TaskP_exit();
}

/**
 * \brief    Multi-threaded Interrupt + Polling TX/RX test
 *           Thread 1: Interrupt-mode TX/RX (uses TX buffer 0, ID 0x04 -> dedicated RX buffer 0)
 *           Thread 2: Polling-mode TX/RX   (uses TX buffer 1, ID 0x05 -> RX FIFO 0)
 *           Both threads send TEST_MCAN_MT_MESSAGE_COUNT messages in internal loopback.
 *           RX paths are isolated to prevent cross-contamination between threads.
 *           Validates that interrupt and polling modes can coexist on the same MCAN instance.
 */
int32_t TestMcan_intrPollMultiThreadTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t configStatus = CSL_PASS;
    int32_t status;
    TaskP_Params taskParams;

    /* Reset counters */
    gMcanMtStopThreads = 0U;
    gMcanMtPerThreadCount[0] = 0U;
    gMcanMtPerThreadCount[1] = 0U;
    gMcanMtPerThreadErrors[0] = 0U;
    gMcanMtPerThreadErrors[1] = 0U;

    /* Configure MCAN module */
    configStatus = App_mcanConfig(testParams);
    if(configStatus != CSL_PASS)
    {
        DebugP_log("ERROR: MCAN configuration failed!\r\n");
        return CSL_EFAIL;
    }

    status = SemaphoreP_constructBinary(&gMcanMtPerThreadRxSem[0], 0);
    DebugP_assert(status == SystemP_SUCCESS);

    HwiP_destruct(&gMcanHwiObject3);

    /* Replace the shared ISR (App_mcanIntr0ISR) with a custom one that only
     * posts gMcanMtPerThreadRxSem[0] on DRX events, preventing FIFO0 interference
     * with the polling thread's RX path. */
    HwiP_destruct(&gMcanHwiObject);

    /* Drain any stale counts from gTxDoneSem left by previous tests (e.g., 10495
     * which uses polling but the shared ISR still posts on TX complete).
     * Without this, the interrupt thread would immediately proceed without
     * actual TX completion, then hang waiting for RX. */
    while(SemaphoreP_pend(&gTxDoneSem, 0) == SystemP_SUCCESS)
    {
        /* Drain stale semaphore posts */
    }
    {
        HwiP_Params hwiPrms;
        HwiP_Params_init(&hwiPrms);
        hwiPrms.intNum   = CONFIG_MCAN0_INTR;
        hwiPrms.callback = &TestMcan_intrPollISR;
        hwiPrms.isPulse  = FALSE;
        hwiPrms.priority = 4;
        status = HwiP_construct(&gMcanMtHwiObj[0], &hwiPrms);
        DebugP_assert(status == SystemP_SUCCESS);
    }

    /* Enable MCAN Interrupts */
    MCAN_enableIntr(gMcanBaseAddr, testParams->mcanConfigParams.intrEnable, (uint32_t)TRUE);

    /* Explicitly enable DRX (dedicated RX buffer) interrupt for interrupt thread RX */
    MCAN_enableIntr(gMcanBaseAddr, MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG, (uint32_t)TRUE);

    /* Select Interrupt Line */
    MCAN_selectIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLineSelectMask,
                        testParams->mcanConfigParams.intrLine);

    /* Enable Interrupt Line */
    MCAN_enableIntrLine(gMcanBaseAddr,
                        testParams->mcanConfigParams.intrLine,
                        1U);

    /* Enable Transmission interrupt for TX buffer 0 only (interrupt thread) */
    /* TX buffer 1 (polling thread) does NOT need TX interrupt - it polls for completion */
    configStatus = MCAN_txBufTransIntrEnable(gMcanBaseAddr, 0U, (uint32_t)TRUE);
    if(configStatus != CSL_PASS)
    {
        DebugP_log("ERROR: MCAN Tx Buffer 0 Interrupt Enable FAILED\r\n");
        return CSL_EFAIL;
    }

    /* Create synchronization semaphores */
    status = SemaphoreP_constructCounting(&gMcanMtStartSem, 0, 2);
    DebugP_assert(status == SystemP_SUCCESS);

    status = SemaphoreP_constructCounting(&gMcanMtCompleteSem, 0, 2);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Create Interrupt-mode TX/RX Task (Thread 1) */
    TaskP_Params_init(&taskParams);
    taskParams.name = "MCAN_INTR_TXRX";
    taskParams.stackSize = TEST_MCAN_MT_TASK_STACK_SIZE;
    taskParams.stack = gMcanMtTaskStack[0];
    taskParams.priority = TEST_MCAN_MT_TX_TASK_PRI;
    taskParams.args = testParams;
    taskParams.taskMain = TestMcan_intrModeTxRxThread;

    status = TaskP_construct(&gMcanMtTaskObj[0], &taskParams);
    if(status != SystemP_SUCCESS)
    {
        DebugP_log("ERROR: Failed to create Interrupt TX/RX thread!\r\n");
        configStatus = CSL_EFAIL;
    }

    if(configStatus == CSL_PASS)
    {
        /* Create Polling-mode TX/RX Task (Thread 2) */
        TaskP_Params_init(&taskParams);
        taskParams.name = "MCAN_POLL_TXRX";
        taskParams.stackSize = TEST_MCAN_MT_TASK_STACK_SIZE;
        taskParams.stack = gMcanMtTaskStack[1];
        taskParams.priority = TEST_MCAN_MT_TX_TASK_PRI;
        taskParams.args = testParams;
        taskParams.taskMain = TestMcan_pollModeTxRxThread;

        status = TaskP_construct(&gMcanMtTaskObj[1], &taskParams);
        if(status != SystemP_SUCCESS)
        {
            DebugP_log("ERROR: Failed to create Polling TX/RX thread!\r\n");
            configStatus = CSL_EFAIL;
        }
    }

    if(configStatus == CSL_PASS)
    {
        /* Give small delay to ensure both threads are created and waiting */
        ClockP_usleep(1000);

        /* Start both threads simultaneously */
        SemaphoreP_post(&gMcanMtStartSem);  /* Interrupt thread */
        SemaphoreP_post(&gMcanMtStartSem);  /* Polling thread */

        /* Wait for both threads to complete */
        SemaphoreP_pend(&gMcanMtCompleteSem, SystemP_WAIT_FOREVER);  /* Thread 1 complete */
        SemaphoreP_pend(&gMcanMtCompleteSem, SystemP_WAIT_FOREVER);  /* Thread 2 complete */

        /* Stop threads */
        gMcanMtStopThreads = 1U;

        /* Validate interrupt thread results */
        if(gMcanMtPerThreadCount[0] != TEST_MCAN_MT_MESSAGE_COUNT)
        {
            DebugP_log("[FAIL] Interrupt thread: Expected %d messages, got %d\r\n",
                       TEST_MCAN_MT_MESSAGE_COUNT, gMcanMtPerThreadCount[0]);
            configStatus = CSL_EFAIL;
        }

        if(gMcanMtPerThreadErrors[0] > 0U)
        {
            DebugP_log("[FAIL] Interrupt thread: %d errors detected\r\n", gMcanMtPerThreadErrors[0]);
            configStatus = CSL_EFAIL;
        }

        /* Validate polling thread results */
        if(gMcanMtPerThreadCount[1] != TEST_MCAN_MT_MESSAGE_COUNT)
        {
            DebugP_log("[FAIL] Polling thread: Expected %d messages, got %d\r\n",
                       TEST_MCAN_MT_MESSAGE_COUNT, gMcanMtPerThreadCount[1]);
            configStatus = CSL_EFAIL;
        }

        if(gMcanMtPerThreadErrors[1] > 0U)
        {
            DebugP_log("[FAIL] Polling thread: %d errors detected\r\n", gMcanMtPerThreadErrors[1]);
            configStatus = CSL_EFAIL;
        }

        if(configStatus == CSL_PASS)
        {
            DebugP_log("\r\n[PASS] Interrupt + Polling multi-thread TX/RX test completed successfully!\r\n");
            DebugP_log("  Interrupt thread: %d messages TX/RX OK\r\n", gMcanMtPerThreadCount[0]);
            DebugP_log("  Polling thread:   %d messages TX/RX OK\r\n", gMcanMtPerThreadCount[1]);
        }
        else
        {
            DebugP_log("\r\n[FAIL] Interrupt + Polling multi-thread TX/RX test failed!\r\n");
        }
    }

    /* Destruct tasks */
    TaskP_destruct(&gMcanMtTaskObj[0]);
    TaskP_destruct(&gMcanMtTaskObj[1]);

    /* Restore the original shared ISR (App_mcanIntr0ISR) */
    HwiP_destruct(&gMcanMtHwiObj[0]);
    {
        HwiP_Params hwiPrms;
        HwiP_Params_init(&hwiPrms);
        hwiPrms.intNum   = CONFIG_MCAN0_INTR;
        hwiPrms.callback = &App_mcanIntr0ISR;
        hwiPrms.isPulse  = FALSE;
        hwiPrms.priority = 4;
        (void)HwiP_construct(&gMcanHwiObject, &hwiPrms);
    }

    /* Restore the MCAN0 Line 1 ISR that was unregistered at the start */
    {
        HwiP_Params hwiPrms;
        HwiP_Params_init(&hwiPrms);
        hwiPrms.intNum   = CONFIG_MCAN0_INTR + 1U;
        hwiPrms.callback = &App_mcanIntr1ISR;
        hwiPrms.isPulse  = FALSE;
        hwiPrms.priority = 4;
        (void)HwiP_construct(&gMcanHwiObject3, &hwiPrms);
    }

    /* Destruct semaphores.
     * NOTE: gTxDoneSem is NOT destructed here — it was not constructed here
     * and will be cleaned up by TestMcan_deInitTxRxSem() in the caller. */
    SemaphoreP_destruct(&gMcanMtPerThreadRxSem[0]);
    SemaphoreP_destruct(&gMcanMtStartSem);
    SemaphoreP_destruct(&gMcanMtCompleteSem);

    /* Disable TX buffer interrupt (only buffer 0 was enabled) */
    MCAN_txBufTransIntrEnable(gMcanBaseAddr, 0U, (uint32_t)FALSE);

    return configStatus;
}

/* ========================================================================== */
/*    Multi-Threaded Filter Test (Classic->FIFO0, Dual->FIFO1)                */
/* ========================================================================== */
/**
 * \brief    ISR for multi-threaded filter test.
 *           Handles TX completion for buffers 0 and 1.
 *           Posts RX semaphore for FIFO0 (Thread 1) or FIFO1 (Thread 2)
 *           when a new message arrives. Rejection test frames are handled
 *           by threads via direct FIFO polling — no ISR action needed.
 */
static void TestMcan_filterTestISR(void *arg)
{
    uint32_t intrStatus;
    uint32_t i;

    (void)arg;

    intrStatus = MCAN_getIntrStatus(gMcanBaseAddr);
    MCAN_clearIntrStatus(gMcanBaseAddr, intrStatus);

    /* TX completion — check buffers 0 and 1 independently */
    if((intrStatus & MCAN_INTR_SRC_TRANS_COMPLETE) == MCAN_INTR_SRC_TRANS_COMPLETE)
    {
        uint32_t txBufStatus = MCAN_getTxBufTransmissionStatus(gMcanBaseAddr);

        for(i = 0U; i < 2U; i++)
        {
            if(((txBufStatus & (1U << i)) != 0U) && (gMcanMtTxSemPtrs[i] != NULL))
            {
                SemaphoreP_post(gMcanMtTxSemPtrs[i]);
            }
        }
    }

    /* FIFO0 new message — Thread 1 accept frames */
    if((intrStatus & MCAN_INTR_SRC_RX_FIFO0_NEW_MSG) == MCAN_INTR_SRC_RX_FIFO0_NEW_MSG)
    {
        if(gMcanMtRxSemPtrs[0] != NULL)
        {
            SemaphoreP_post(gMcanMtRxSemPtrs[0]);
        }
    }

    /* FIFO1 new message — Thread 2 accept frames */
    if((intrStatus & MCAN_INTR_SRC_RX_FIFO1_NEW_MSG) == MCAN_INTR_SRC_RX_FIFO1_NEW_MSG)
    {
        if(gMcanMtRxSemPtrs[1] != NULL)
        {
            SemaphoreP_post(gMcanMtRxSemPtrs[1]);
        }
    }
}

/**
 * \brief    Thread 1 - Classic (Bitmask) Filter -> FIFO0
 *           Filter: sfid1=0x100, sfid2=0x700 (mask). Accepts any ID where
 *           bits[10:8]==0x1 (range 0x100-0x1FF). Rejects all other IDs.
 *
 *           Sequence (TEST_MCAN_MT_ACCEPT_COUNT accepted + TEST_MCAN_MT_REJECT_COUNT rejected):
 *             Accept: 0x100, 0x101, 0x10F  -> must arrive in FIFO0
 *             Reject: 0x300, 0x500         -> must NOT arrive in FIFO0
 *
 *           For accepted IDs: waits on TX sem then RX sem (ISR-driven).
 *           For rejected IDs: waits on TX sem then polls FIFO0 with a
 *           short timeout expecting it to remain empty.
 */
static void TestMcan_filterTestThread1(void *args)
{
    /* Accept IDs (bits[10:8]==0x1, within 0x100-0x1FF) */
    static const uint32_t acceptIds[TEST_MCAN_MT_ACCEPT_COUNT] = {
        0x100U, 0x101U, 0x10FU
    };
    /* Reject IDs (bits[10:8] != 0x1, filtered out by catch-all REJECT at slot 2) */
    static const uint32_t rejectIds[TEST_MCAN_MT_REJECT_COUNT] = {
        FILTER_TEST_CLASSIC_REJECT_ID1, FILTER_TEST_CLASSIC_REJECT_ID2
    };

    MCAN_TxBufElement txMsg;
    MCAN_RxBufElement rxMsg;
    MCAN_RxFIFOStatus fifoStatus;
    uint32_t loopCnt, n;
    uint32_t pollTimeout;
    int32_t  status;

    (void)args;

    txMsg.rtr = 0U;
    txMsg.xtd = 0U;
    txMsg.esi = 0U;
    txMsg.dlc = MCAN_DATA_SIZE_8BYTES;
    txMsg.brs = 1U;
    txMsg.fdf = 1U;
    txMsg.efc = 0U;
    txMsg.mm  = 0x01U;

    SemaphoreP_pend(&gMcanMtStartSem, SystemP_WAIT_FOREVER);

    /* ---- Acceptance test: 0x100, 0x101, 0x10F must arrive in FIFO0 ---- */
    for(n = 0U; n < TEST_MCAN_MT_ACCEPT_COUNT; n++)
    {
        txMsg.id = (acceptIds[n] << APP_MCAN_STD_ID_SHIFT);
        for(loopCnt = 0U; loopCnt < TEST_MCAN_MT_DATA_SIZE; loopCnt++)
        {
            txMsg.data[loopCnt] = (uint8_t)(0x10U + loopCnt + n);
        }

        MCAN_writeMsgRam(gMcanBaseAddr, MCAN_MEM_TYPE_BUF, 0U, &txMsg);
        status = MCAN_txBufAddReq(gMcanBaseAddr, 0U);
        if(status != CSL_PASS)
        {
            DebugP_log("[Thread 1] TX request failed for accept ID 0x%03X\n", acceptIds[n]);
            gMcanMtPerThreadErrors[0]++;
            break;
        }

        SemaphoreP_pend(&gMcanMtPerThreadTxSem[0], SystemP_WAIT_FOREVER);
        SemaphoreP_pend(&gMcanMtPerThreadRxSem[0], SystemP_WAIT_FOREVER);

        fifoStatus.num = MCAN_RX_FIFO_NUM_0;
        MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
        MCAN_readMsgRam(gMcanBaseAddr, MCAN_MEM_TYPE_FIFO, fifoStatus.getIdx,
                        (uint32_t)fifoStatus.num, &rxMsg);
        MCAN_writeRxFIFOAck(gMcanBaseAddr, (uint32_t)fifoStatus.num, fifoStatus.getIdx);

        uint32_t rxId = (rxMsg.id >> APP_MCAN_STD_ID_SHIFT) & 0x7FFU;
        if(rxId != acceptIds[n])
        {
            DebugP_log("[Thread 1] ACCEPT FAIL: sent 0x%03X received 0x%03X in FIFO0\n",
                       acceptIds[n], rxId);
            gMcanMtPerThreadErrors[0]++;
        }
        else
        {
            uint32_t dataOk = 1U;
            for(loopCnt = 0U; loopCnt < TEST_MCAN_MT_DATA_SIZE; loopCnt++)
            {
                if(rxMsg.data[loopCnt] != (uint8_t)(0x10U + loopCnt + n))
                {
                    dataOk = 0U;
                    break;
                }
            }
            if(dataOk)
            {
                DebugP_log("[Thread 1] ACCEPT PASS: ID 0x%03X received in FIFO0\n", acceptIds[n]);
                gMcanMtPerThreadCount[0]++;
            }
            else
            {
                DebugP_log("[Thread 1] ACCEPT FAIL: data mismatch for ID 0x%03X\n", acceptIds[n]);
                gMcanMtPerThreadErrors[0]++;
            }
        }
        ClockP_usleep(100U);
    }

    /* ---- Rejection test: 0x300, 0x500 must NOT arrive in FIFO0 ---- */
    for(n = 0U; n < TEST_MCAN_MT_REJECT_COUNT; n++)
    {
        txMsg.id = (rejectIds[n] << APP_MCAN_STD_ID_SHIFT);
        for(loopCnt = 0U; loopCnt < TEST_MCAN_MT_DATA_SIZE; loopCnt++)
        {
            txMsg.data[loopCnt] = (uint8_t)(0xAAU + loopCnt);
        }

        MCAN_writeMsgRam(gMcanBaseAddr, MCAN_MEM_TYPE_BUF, 0U, &txMsg);
        status = MCAN_txBufAddReq(gMcanBaseAddr, 0U);
        if(status != CSL_PASS)
        {
            DebugP_log("[Thread 1] TX request failed for reject ID 0x%03X\n", rejectIds[n]);
            gMcanMtPerThreadErrors[0]++;
            break;
        }

        /* Wait for TX completion — frame was transmitted and loopback-received
         * then discarded by the catch-all REJECT filter at slot 2. */
        SemaphoreP_pend(&gMcanMtPerThreadTxSem[0], SystemP_WAIT_FOREVER);

        /* Poll FIFO0 with short timeout — expect it to stay empty */
        fifoStatus.num = MCAN_RX_FIFO_NUM_0;
        pollTimeout = 10000U;
        do
        {
            MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
            pollTimeout--;
        } while((fifoStatus.fillLvl == 0U) && (pollTimeout > 0U));

        if(fifoStatus.fillLvl == 0U)
        {
            DebugP_log("[Thread 1] REJECT PASS: ID 0x%03X correctly not in FIFO0\n", rejectIds[n]);
            gMcanMtPerThreadCount[0]++;
        }
        else
        {
            uint32_t rxId;
            MCAN_readMsgRam(gMcanBaseAddr, MCAN_MEM_TYPE_FIFO, fifoStatus.getIdx,
                            (uint32_t)MCAN_RX_FIFO_NUM_0, &rxMsg);
            MCAN_writeRxFIFOAck(gMcanBaseAddr, (uint32_t)fifoStatus.num, fifoStatus.getIdx);
            rxId = (rxMsg.id >> APP_MCAN_STD_ID_SHIFT) & 0x7FFU;
            DebugP_log("[Thread 1] REJECT FAIL: ID 0x%03X should be rejected but 0x%03X arrived in FIFO0\n",
                       rejectIds[n], rxId);
            gMcanMtPerThreadErrors[0]++;
        }
        ClockP_usleep(100U);
    }

    SemaphoreP_post(&gMcanMtCompleteSem);
    TaskP_exit();
}

/**
 * \brief    Thread 2 - Dual Filter -> FIFO1
 *           Filter: sfid1=0x200, sfid2=0x201 (dual). Accepts only 0x200 or 0x201.
 *           Rejects all other IDs.
 *
 *           Sequence (TEST_MCAN_MT_ACCEPT_COUNT accepted + TEST_MCAN_MT_REJECT_COUNT rejected):
 *             Accept: 0x200, 0x201, 0x200  -> must arrive in FIFO1
 *             Reject: 0x202, 0x400         -> must NOT arrive in FIFO1
 *
 *           For accepted IDs: waits on TX sem then RX sem (ISR-driven).
 *           For rejected IDs: waits on TX sem then polls FIFO1 with a
 *           short timeout expecting it to remain empty.
 */
static void TestMcan_filterTestThread2(void *args)
{
    /* Accept IDs (only 0x200 or 0x201 are matched by dual filter) */
    static const uint32_t acceptIds[TEST_MCAN_MT_ACCEPT_COUNT] = {
        FILTER_TEST_DUAL_ID1, FILTER_TEST_DUAL_ID2, FILTER_TEST_DUAL_ID1
    };
    /* Reject IDs (not 0x200 or 0x201, hit catch-all REJECT at slot 2) */
    static const uint32_t rejectIds[TEST_MCAN_MT_REJECT_COUNT] = {
        FILTER_TEST_DUAL_REJECT_ID1, FILTER_TEST_DUAL_REJECT_ID2
    };

    MCAN_TxBufElement txMsg;
    MCAN_RxBufElement rxMsg;
    MCAN_RxFIFOStatus fifoStatus;
    uint32_t loopCnt, n;
    uint32_t pollTimeout;
    int32_t  status;

    (void)args;

    txMsg.rtr = 0U;
    txMsg.xtd = 0U;
    txMsg.esi = 0U;
    txMsg.dlc = MCAN_DATA_SIZE_8BYTES;
    txMsg.brs = 1U;
    txMsg.fdf = 1U;
    txMsg.efc = 0U;
    txMsg.mm  = 0x02U;

    SemaphoreP_pend(&gMcanMtStartSem, SystemP_WAIT_FOREVER);

    /* ---- Acceptance test: 0x200, 0x201, 0x200 must arrive in FIFO1 ---- */
    for(n = 0U; n < TEST_MCAN_MT_ACCEPT_COUNT; n++)
    {
        txMsg.id = (acceptIds[n] << APP_MCAN_STD_ID_SHIFT);
        for(loopCnt = 0U; loopCnt < TEST_MCAN_MT_DATA_SIZE; loopCnt++)
        {
            txMsg.data[loopCnt] = (uint8_t)(0x20U + loopCnt + n);
        }

        MCAN_writeMsgRam(gMcanBaseAddr, MCAN_MEM_TYPE_BUF, 1U, &txMsg);
        status = MCAN_txBufAddReq(gMcanBaseAddr, 1U);
        if(status != CSL_PASS)
        {
            DebugP_log("[Thread 2] TX request failed for accept ID 0x%03X\n", acceptIds[n]);
            gMcanMtPerThreadErrors[1]++;
            break;
        }

        SemaphoreP_pend(&gMcanMtPerThreadTxSem[1], SystemP_WAIT_FOREVER);
        SemaphoreP_pend(&gMcanMtPerThreadRxSem[1], SystemP_WAIT_FOREVER);

        fifoStatus.num = MCAN_RX_FIFO_NUM_1;
        MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
        MCAN_readMsgRam(gMcanBaseAddr, MCAN_MEM_TYPE_FIFO, fifoStatus.getIdx,
                        (uint32_t)fifoStatus.num, &rxMsg);
        MCAN_writeRxFIFOAck(gMcanBaseAddr, (uint32_t)fifoStatus.num, fifoStatus.getIdx);

        uint32_t rxId = (rxMsg.id >> APP_MCAN_STD_ID_SHIFT) & 0x7FFU;
        if(rxId != acceptIds[n])
        {
            DebugP_log("[Thread 2] ACCEPT FAIL: sent 0x%03X received 0x%03X in FIFO1\n",
                       acceptIds[n], rxId);
            gMcanMtPerThreadErrors[1]++;
        }
        else
        {
            uint32_t dataOk = 1U;
            for(loopCnt = 0U; loopCnt < TEST_MCAN_MT_DATA_SIZE; loopCnt++)
            {
                if(rxMsg.data[loopCnt] != (uint8_t)(0x20U + loopCnt + n))
                {
                    dataOk = 0U;
                    break;
                }
            }
            if(dataOk)
            {
                DebugP_log("[Thread 2] ACCEPT PASS: ID 0x%03X received in FIFO1\n", acceptIds[n]);
                gMcanMtPerThreadCount[1]++;
            }
            else
            {
                DebugP_log("[Thread 2] ACCEPT FAIL: data mismatch for ID 0x%03X\n", acceptIds[n]);
                gMcanMtPerThreadErrors[1]++;
            }
        }
        ClockP_usleep(100U);
    }

    /* ---- Rejection test: 0x202, 0x400 must NOT arrive in FIFO1 ---- */
    for(n = 0U; n < TEST_MCAN_MT_REJECT_COUNT; n++)
    {
        txMsg.id = (rejectIds[n] << APP_MCAN_STD_ID_SHIFT);
        for(loopCnt = 0U; loopCnt < TEST_MCAN_MT_DATA_SIZE; loopCnt++)
        {
            txMsg.data[loopCnt] = (uint8_t)(0xBBU + loopCnt);
        }

        MCAN_writeMsgRam(gMcanBaseAddr, MCAN_MEM_TYPE_BUF, 1U, &txMsg);
        status = MCAN_txBufAddReq(gMcanBaseAddr, 1U);
        if(status != CSL_PASS)
        {
            DebugP_log("[Thread 2] TX request failed for reject ID 0x%03X\n", rejectIds[n]);
            gMcanMtPerThreadErrors[1]++;
            break;
        }

        SemaphoreP_pend(&gMcanMtPerThreadTxSem[1], SystemP_WAIT_FOREVER);

        /* Poll FIFO1 with short timeout — expect it to stay empty */
        fifoStatus.num = MCAN_RX_FIFO_NUM_1;
        pollTimeout = 10000U;
        do
        {
            MCAN_getRxFIFOStatus(gMcanBaseAddr, &fifoStatus);
            pollTimeout--;
        } while((fifoStatus.fillLvl == 0U) && (pollTimeout > 0U));

        if(fifoStatus.fillLvl == 0U)
        {
            DebugP_log("[Thread 2] REJECT PASS: ID 0x%03X correctly not in FIFO1\n", rejectIds[n]);
            gMcanMtPerThreadCount[1]++;
        }
        else
        {
            uint32_t rxId;
            MCAN_readMsgRam(gMcanBaseAddr, MCAN_MEM_TYPE_FIFO, fifoStatus.getIdx,
                            (uint32_t)MCAN_RX_FIFO_NUM_1, &rxMsg);
            MCAN_writeRxFIFOAck(gMcanBaseAddr, (uint32_t)fifoStatus.num, fifoStatus.getIdx);
            rxId = (rxMsg.id >> APP_MCAN_STD_ID_SHIFT) & 0x7FFU;
            DebugP_log("[Thread 2] REJECT FAIL: ID 0x%03X should be rejected but 0x%03X arrived in FIFO1\n",
                       rejectIds[n], rxId);
            gMcanMtPerThreadErrors[1]++;
        }
        ClockP_usleep(100U);
    }

    SemaphoreP_post(&gMcanMtCompleteSem);
    TaskP_exit();
}

/**
 * \brief    Multi-threaded Filter Test
 *           Two threads run concurrently, each testing their filter with both
 *           accepted and rejected IDs:
 *
 *           Thread 1: Classic bitmask filter (sfid1=0x100, sfid2=0x700) -> FIFO0
 *             Accept: 0x100, 0x101, 0x10F  (bits[10:8]==0x1 -> pass)
 *             Reject: 0x300, 0x500         (bits[10:8]!=0x1 -> caught by catch-all)
 *
 *           Thread 2: Dual filter (sfid1=0x200, sfid2=0x201) -> FIFO1
 *             Accept: 0x200, 0x201, 0x200  (exact dual match -> pass)
 *             Reject: 0x202, 0x400         (no match -> caught by catch-all)
 *
 *           Filter slots:
 *             Slot 0: Classic bitmask -> FIFO0  (Thread 1)
 *             Slot 1: Dual            -> FIFO1  (Thread 2)
 *             Slot 2: Range 0x000-0x7FF -> REJECT  (catch-all, platform-independent)
 *
 *           Rejection is enforced by the catch-all REJECT filter at slot 2,
 *           not by GFC.ANFS, making the test portable across platforms where
 *           MCAN_reset() is a no-op and GFC defaults may vary.
 */
int32_t TestMcan_multiThreadedFilterTest(st_mcanTestcaseParams_t *testParams)
{
    int32_t configStatus = CSL_PASS;
    int32_t status;
    TaskP_Params taskParams;
    MCAN_StdMsgIDFilterElement stdIdFilter;
    HwiP_Params hwiPrms;

    /* Reset counters */
    gMcanMtStopThreads = 0U;
    gMcanMtPerThreadCount[0] = 0U;
    gMcanMtPerThreadCount[1] = 0U;
    gMcanMtPerThreadErrors[0] = 0U;
    gMcanMtPerThreadErrors[1] = 0U;
    
    /* Configure MCAN module */
    configStatus = App_mcanConfig(testParams);
    if(configStatus != CSL_PASS)
    {
        DebugP_log("MCAN Configuration FAILED\n");
        return configStatus;
    }

    /* ========== Configure Filter Slot 0: Classic bitmask -> FIFO0 ==========
     * sfid1=0x100, sfid2=0x700: accepts any ID where bits[10:8]==0x1
     * (range 0x100-0x1FF). Thread 1 tests IDs 0x100, 0x101, 0x10F.         */
    stdIdFilter.sfid1 = FILTER_TEST_CLASSIC_ID;
    stdIdFilter.sfid2 = FILTER_TEST_CLASSIC_MASK;
    stdIdFilter.sfec  = MCAN_STD_FILT_ELEM_FIFO0;
    stdIdFilter.sft   = MCAN_STD_FILT_TYPE_CLASSIC;
    MCAN_addStdMsgIDFilter(gMcanBaseAddr, 0U, &stdIdFilter);

    /* ========== Configure Filter Slot 1: Dual filter -> FIFO1 ==========
     * Accepts only 0x200 or 0x201. Thread 2 tests both accepted IDs
     * and rejected IDs 0x202 and 0x400.                                     */
    stdIdFilter.sfid1 = FILTER_TEST_DUAL_ID1;
    stdIdFilter.sfid2 = FILTER_TEST_DUAL_ID2;
    stdIdFilter.sfec  = MCAN_STD_FILT_ELEM_FIFO1;
    stdIdFilter.sft   = MCAN_STD_FILT_TYPE_DUAL;
    MCAN_addStdMsgIDFilter(gMcanBaseAddr, 1U, &stdIdFilter);

    /* ========== Configure Filter Slot 2: Catch-all REJECT ==========
     * Range 0x000-0x7FF covers all standard IDs. Because MCAN evaluates
     * filters in slot order, any ID accepted by slot 0 or slot 1 is stored
     * before reaching here. IDs that matched neither slot will be rejected
     * by this filter. This avoids reliance on GFC.ANFS which cannot be
     * reliably changed after init on this platform.                         */
    stdIdFilter.sfid1 = 0x000U;
    stdIdFilter.sfid2 = 0x7FFU;
    stdIdFilter.sfec  = MCAN_STD_FILT_ELEM_REJECT;
    stdIdFilter.sft   = MCAN_STD_FILT_TYPE_RANGE;
    MCAN_addStdMsgIDFilter(gMcanBaseAddr, 2U, &stdIdFilter);

    /* Register custom ISR for this test */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CONFIG_MCAN0_INTR;
    hwiPrms.callback = &TestMcan_filterTestISR;
    hwiPrms.isPulse  = FALSE;
    hwiPrms.priority = 4;

    /* Destruct the existing global ISR and install test-specific one */
    HwiP_destruct(&gMcanHwiObject);

    status = HwiP_construct(&gMcanMtHwiObj[0], &hwiPrms);
    if(status != SystemP_SUCCESS)
    {
        DebugP_log("HwiP_construct failed\n");
        configStatus = CSL_EFAIL;
    }

    if(configStatus == CSL_PASS)
    {
        /* Enable MCAN Interrupts */
        MCAN_enableIntr(gMcanBaseAddr,
                        MCAN_INTR_MASK_ALL | MCAN_INTR_SRC_RX_FIFO0_NEW_MSG |
                        MCAN_INTR_SRC_RX_FIFO1_NEW_MSG,
                        (uint32_t)TRUE);

        /* Select Interrupt Line */
        MCAN_selectIntrLine(gMcanBaseAddr,
                            MCAN_INTR_MASK_ALL | MCAN_INTR_SRC_RX_FIFO0_NEW_MSG |
                            MCAN_INTR_SRC_RX_FIFO1_NEW_MSG,
                            MCAN_INTR_LINE_NUM_0);

        /* Enable Interrupt Line */
        MCAN_enableIntrLine(gMcanBaseAddr, MCAN_INTR_LINE_NUM_0, 1U);

        /* Enable TX buffer transmission interrupts for buffers 0 and 1 */
        configStatus = MCAN_txBufTransIntrEnable(gMcanBaseAddr, 0U, (uint32_t)TRUE);
        if(configStatus != CSL_PASS)
        {
            DebugP_log("MCAN Tx Buffer 0 Interrupt Enable FAILED\n");
        }
    }

    if(configStatus == CSL_PASS)
    {
        configStatus = MCAN_txBufTransIntrEnable(gMcanBaseAddr, 1U, (uint32_t)TRUE);
        if(configStatus != CSL_PASS)
        {
            DebugP_log("MCAN Tx Buffer 1 Interrupt Enable FAILED\n");
        }
    }

    if(configStatus == CSL_PASS)
    {
        /* Create synchronization semaphores (max count = 2 threads) */
        status = SemaphoreP_constructCounting(&gMcanMtStartSem, 0, 2);
        DebugP_assert(status == SystemP_SUCCESS);

        status = SemaphoreP_constructCounting(&gMcanMtCompleteSem, 0, 2);
        DebugP_assert(status == SystemP_SUCCESS);

        /* Create TX/RX semaphores for Thread 1 (FIFO0) */
        status = SemaphoreP_constructBinary(&gMcanMtPerThreadTxSem[0], 0);
        DebugP_assert(status == SystemP_SUCCESS);
        status = SemaphoreP_constructBinary(&gMcanMtPerThreadRxSem[0], 0);
        DebugP_assert(status == SystemP_SUCCESS);

        /* Create TX/RX semaphores for Thread 2 (FIFO1) */
        status = SemaphoreP_constructBinary(&gMcanMtPerThreadTxSem[1], 0);
        DebugP_assert(status == SystemP_SUCCESS);
        status = SemaphoreP_constructBinary(&gMcanMtPerThreadRxSem[1], 0);
        DebugP_assert(status == SystemP_SUCCESS);

        /* Expose semaphores to ISR */
        gMcanMtTxSemPtrs[0] = &gMcanMtPerThreadTxSem[0];
        gMcanMtTxSemPtrs[1] = &gMcanMtPerThreadTxSem[1];
        gMcanMtRxSemPtrs[0] = &gMcanMtPerThreadRxSem[0];
        gMcanMtRxSemPtrs[1] = &gMcanMtPerThreadRxSem[1];

        /* Create Thread 1: Classic bitmask filter, accept + reject in FIFO0 */
        TaskP_Params_init(&taskParams);
        taskParams.name      = "MCAN_FILTER_CLASSIC";
        taskParams.stackSize = TEST_MCAN_MT_TASK_STACK_SIZE;
        taskParams.stack     = gMcanMtTaskStack[0];
        taskParams.priority  = TEST_MCAN_MT_TX_TASK_PRI;
        taskParams.args      = testParams;
        taskParams.taskMain  = TestMcan_filterTestThread1;

        status = TaskP_construct(&gMcanMtTaskObj[0], &taskParams);
        if(status != SystemP_SUCCESS)
        {
            DebugP_log("TaskP_construct for Thread 1 failed\n");
            configStatus = CSL_EFAIL;
        }
    }

    if(configStatus == CSL_PASS)
    {
        /* Create Thread 2: Dual filter, accept + reject in FIFO1 */
        TaskP_Params_init(&taskParams);
        taskParams.name      = "MCAN_FILTER_DUAL";
        taskParams.stackSize = TEST_MCAN_MT_TASK_STACK_SIZE;
        taskParams.stack     = gMcanMtTaskStack[1];
        taskParams.priority  = TEST_MCAN_MT_TX_TASK_PRI;
        taskParams.args      = testParams;
        taskParams.taskMain  = TestMcan_filterTestThread2;

        status = TaskP_construct(&gMcanMtTaskObj[1], &taskParams);
        if(status != SystemP_SUCCESS)
        {
            DebugP_log("TaskP_construct for Thread 2 failed\n");
            configStatus = CSL_EFAIL;
        }
    }

    if(configStatus == CSL_PASS)
    {
        /* Give a small delay to ensure both threads are waiting on startSem */
        ClockP_usleep(1000U);

        /* Start both threads simultaneously */
        SemaphoreP_post(&gMcanMtStartSem);  /* Thread 1 */
        SemaphoreP_post(&gMcanMtStartSem);  /* Thread 2 */

        /* Wait for both threads to complete */
        SemaphoreP_pend(&gMcanMtCompleteSem, SystemP_WAIT_FOREVER);  /* Thread 1 */
        SemaphoreP_pend(&gMcanMtCompleteSem, SystemP_WAIT_FOREVER);  /* Thread 2 */

        gMcanMtStopThreads = 1U;

        /* Each thread performs TEST_MCAN_MT_MESSAGE_COUNT checks
         * (TEST_MCAN_MT_ACCEPT_COUNT accepted + TEST_MCAN_MT_REJECT_COUNT rejected). */
        if((gMcanMtPerThreadCount[0] != TEST_MCAN_MT_MESSAGE_COUNT) ||
           (gMcanMtPerThreadCount[1] != TEST_MCAN_MT_MESSAGE_COUNT) ||
           (gMcanMtPerThreadErrors[0] != 0U) ||
           (gMcanMtPerThreadErrors[1] != 0U))
        {
            DebugP_log("FAIL: Thread results: T1 pass=%d err=%d, T2 pass=%d err=%d\n",
                       gMcanMtPerThreadCount[0], gMcanMtPerThreadErrors[0],
                       gMcanMtPerThreadCount[1], gMcanMtPerThreadErrors[1]);
            configStatus = CSL_EFAIL;
        }
        else
        {
            DebugP_log("PASS: Both threads completed accept+reject validation successfully\n");
        }
    }

    /* Disable all filter slots used by this test (0-2) so they do not leak
     * into subsequent tests. MCAN_reset() is a no-op on this platform so
     * message-RAM content (including filter elements) persists.             */
    {
        MCAN_StdMsgIDFilterElement disableFilter;
        disableFilter.sfid1 = 0U;
        disableFilter.sfid2 = 0U;
        disableFilter.sfec  = MCAN_STD_FILT_ELEM_DISABLE;
        disableFilter.sft   = MCAN_STD_FILT_TYPE_RANGE;
        MCAN_addStdMsgIDFilter(gMcanBaseAddr, 0U, &disableFilter);
        MCAN_addStdMsgIDFilter(gMcanBaseAddr, 1U, &disableFilter);
        MCAN_addStdMsgIDFilter(gMcanBaseAddr, 2U, &disableFilter);
    }

    /* Destruct tasks */
    TaskP_destruct(&gMcanMtTaskObj[0]);
    TaskP_destruct(&gMcanMtTaskObj[1]);

    /* Restore the original shared ISR */
    HwiP_destruct(&gMcanMtHwiObj[0]);
    {
        HwiP_Params hwiPrms2;
        HwiP_Params_init(&hwiPrms2);
        hwiPrms2.intNum   = CONFIG_MCAN0_INTR;
        hwiPrms2.callback = &App_mcanIntr0ISR;
        hwiPrms2.isPulse  = FALSE;
        hwiPrms2.priority = 4;
        (void)HwiP_construct(&gMcanHwiObject, &hwiPrms2);
    }

    /* Destruct semaphores (2 TX + 2 RX + start + complete) */
    SemaphoreP_destruct(&gMcanMtPerThreadTxSem[0]);
    SemaphoreP_destruct(&gMcanMtPerThreadRxSem[0]);
    SemaphoreP_destruct(&gMcanMtPerThreadTxSem[1]);
    SemaphoreP_destruct(&gMcanMtPerThreadRxSem[1]);
    SemaphoreP_destruct(&gMcanMtStartSem);
    SemaphoreP_destruct(&gMcanMtCompleteSem);

    /* Disable TX buffer interrupts */
    MCAN_txBufTransIntrEnable(gMcanBaseAddr, 0U, (uint32_t)FALSE);
    MCAN_txBufTransIntrEnable(gMcanBaseAddr, 1U, (uint32_t)FALSE);

    return configStatus;
}
#endif /* #if defined (FREERTOS_CORE) */