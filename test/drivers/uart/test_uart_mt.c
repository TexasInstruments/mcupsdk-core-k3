/*
 * Copyright (C) 2021-2026 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* This example demonstrates the UART RX and TX operation in blocking mode
 * and in particular UART Read Return Partial Mode.
 * UART_READ_RETURN_MODE_PARTIAL unblocks or performs a callback whenever a
 * read timeout error occurs on the UART peripheral.
 * The read timeout occurs if the read FIFO is non-empty and no new
 * data has been received for a specific device/baudrate dependent number of
 * clock cycles.  This mode can be used when the exact number of bytes to
 * be read is not known.
 * Example is configured to receive APP_UART_RECEIVE_BUFSIZE characters but
 * the input to this test is a file which contains half of the APP_UART_RECEIVE_BUFSIZE
 * characters.
 * Example ends when it receives half of the APP_UART_RECEIVE_BUFSIZE characters.
 */

/*===================================================================*/
/* 					      Include Files 					         */
/*===================================================================*/

#include "test_uart.h"
#include <board/ioexp/ioexp_tca6424.h>
#define TestExecute_SkipTestIdMatrix TestExecute_SkipTestIdMatrix_weak_default
#include "test_execute.h"
#undef TestExecute_SkipTestIdMatrix

/*===================================================================*/
/* 					      Macro defines 					         */
/*===================================================================*/
/* Macro to define the UART buffer size */
#define TEST_UART_APP_UART_BUFSIZE                          (2048U)
/* IO Expander pin for UART1 enable */
#define TEST_UART_IO_EXP_CODEC_RESET_PIN                    (0x15U)

extern const TestExecute_idList TestExecute_SkipTestIdMatrix[TEST_SOC_COUNT][TEST_CORE_COUNT];

/*===================================================================*/
/* 					         Typedefs 					             */
/*===================================================================*/

/* Shared context for cancel test */
typedef struct
{
    UART_Handle handle;
    UART_Transaction *wTrans;
    SemaphoreP_Object canCancelSem;
    SemaphoreP_Object bothDone;
    uint32_t len;
    uint32_t baud;
} TestUart_CancelCtx;

/*===================================================================*/
/* 					         Global Variables			             */
/*===================================================================*/

#if !defined(CPU_C7X)
/* Stack for UART test thread 1 */
static uint8_t TestUart_threadStack1[8192] __attribute__ ((aligned(32)));
/* Stack for UART test thread 2 */
static uint8_t TestUart_threadStack2[8192] __attribute__ ((aligned(32)));
#else
#if defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM62PX)
/* Stack for UART test thread 1 */
static uint8_t TestUart_threadStack1[65536] __attribute__ ((aligned(32)));
/* Stack for UART test thread 2 */
static uint8_t TestUart_threadStack2[65536] __attribute__ ((aligned(32)));
#endif /* defined(SOC_AM62AX) */
#endif /* !defined(CPU_C7X) */

/* Status variable */
volatile uint32_t TestUart_finalStatus = 0;
/* Object for shared shared context for cancel test */
static TestUart_CancelCtx TestUart_cancelCtx;
/* Buffers for uart */
extern uint8_t gUartTxBuffer[TEST_UART_APP_UART_BUFSIZE];
extern uint8_t gUartRxBuffer[TEST_UART_APP_UART_BUFSIZE];
extern uint8_t  TestUart_txBufferDma[512] __attribute__((aligned(CacheP_CACHELINE_ALIGNMENT)));
static volatile uint32_t TestUart_mtRxCount = 0;
static volatile uint32_t TestUart_mtTxCount = 0;

/*===================================================================*/
/* 					         Function Declarations		             */
/*===================================================================*/

/* Test UART write with multithreaded callback mode interrupt */
/* static void TestUart_uartWriteMultithreadedCallbackInterrupt(void *args); */
/* UART write cancel for multithreaded test */
static void TestUart_uartWriteCancelFromOtherThread(void *args);
/* UART read cancel for multithreaded test */
static void TestUart_uartReadCancelWriteReadLoopbackMT(void *args);
#if !(defined(CPU_C7X) || defined(SOC_AM62DX) || defined(SOC_AM275X))
/* Function to enable/disable the Main UART1 to connector */
static void TestUart_enableDisableUart1ToConnector(uint32_t state);
#endif
/* Test to verify external UART loopback test */
static void TestUart_externalLoopbackUartTxRx(void *args);
/* Test to verify the functionality of write cancel using external loopback test */
static void TestUart_uartTxRxTwoInstancesWriteCancelCompare(void *args);
/* Test to verify different baud rate using externl loopback test */
static void TestUart_uartTxRxTwoInstDiffBaudListCallback(void *args);
/* Test to verify UART DMA Tx uisng externl loopback test */
static void TestUart_uartTxDmaCallback(void *args);
/* Test to verify UART DMA Rx using externl loopback test */
static void TestUart_uartRxDmaCallback(void *args);
/* Test to verify Control signal using externl loopback test */
static void TestUart_externalLoopbackUartTxRxCtrlSignalEnabled(void *args);
/* Test to verify Control signal failure using externl loopback test */
static void TestUart_externalLoopbackUartTxRxCtsHigh(void *args);
/* Test to verify UART read cancel posts semaphore */
static void TestUart_uartReadCancelPostsSem(void *args);

/*===================================================================*/
/* 					         Function Definitions		             */
/*===================================================================*/

/**
 * @brief Main UART driver unit test entry point.
 *
 * Initializes Unity, configures UART test parameters for a set of
 * predefined test case IDs, and executes all registered UART API
 * validation tests (open/close, read/write modes, interrupts, FIFO,
 * status queries, loopback, error paths). Ends by finalizing the
 * Unity framework.
 *
 * Test cases are invoked using RUN_TEST with associated IDs to
 * exercise different parameter combinations (blocking, callback,
 * partial/full return modes, interrupt vs polled).
 *
 * @param[in] args Optional user argument (unused in current implementation).
 *
 * @return void
 */
void TestUart_mtTestcase(void)
{
    TEST_EXECUTE_TEST_CASE(TestUart_uartReadCancelPostsSem, 11636, NULL);
    TEST_EXECUTE_TEST_CASE(TestUart_uartWriteCancelFromOtherThread, 8928, NULL);
    TEST_EXECUTE_TEST_CASE(TestUart_uartReadCancelWriteReadLoopbackMT, 9971, NULL);
#if !(defined(CPU_C7X) || defined(SOC_AM62DX) || defined(SOC_AM275X))
    TestUart_enableDisableUart1ToConnector(TCA6424_OUT_STATE_LOW);
#endif
    TEST_EXECUTE_TEST_CASE(TestUart_externalLoopbackUartTxRx, 9972, NULL);
    TEST_EXECUTE_TEST_CASE(TestUart_uartTxRxTwoInstancesWriteCancelCompare, 9973, NULL);
    TEST_EXECUTE_TEST_CASE(TestUart_uartTxRxTwoInstDiffBaudListCallback, 9974, NULL);
    TEST_EXECUTE_TEST_CASE(TestUart_externalLoopbackUartTxRxCtrlSignalEnabled, 9975, NULL);
    TEST_EXECUTE_TEST_CASE(TestUart_externalLoopbackUartTxRxCtsHigh, 9976, NULL);
    TEST_EXECUTE_TEST_CASE(TestUart_uartTxDmaCallback, 9977, NULL);
    TEST_EXECUTE_TEST_CASE(TestUart_uartRxDmaCallback, 9978, NULL);
#if !(defined(CPU_C7X) || defined(SOC_AM62DX) || defined(SOC_AM275X))
    TestUart_enableDisableUart1ToConnector(TCA6424_OUT_STATE_HIGH);
#endif
}

/**
 * @brief UART write completion callback for interrupt/callback mode tests.
 *
 * This function is invoked by the UART driver when a write transaction
 * completes in callback mode. It updates the global variable gNumBytesWritten
 * with the number of bytes written and posts the write completion semaphore
 * (gUartWriteDoneSem) to signal the test thread.
 *
 * Used in UART unit tests to synchronize test execution and validate
 * asynchronous write operations.
 *
 * @param[in] handle UART handle associated with the transaction.
 * @param[in] trans  Pointer to the completed UART_Transaction structure.
 *
 * @return void
 */
void TestUart_uartWriteCallbackMt(UART_Handle handle, UART_Transaction *trans)
{
    if (trans->args != NULL)
    {
        /* Post the write completion semaphore */
        SemaphoreP_post((SemaphoreP_Object *)trans->args);
    }
}

/**
 * @brief UART write completion callback for interrupt/callback mode tests.
 *
 * This function is invoked by the UART driver when a write transaction
 * completes in callback mode. It updates the global variable gNumBytesWritten
 * with the number of bytes written and posts the write completion semaphore
 * (gUartWriteDoneSem) to signal the test thread.
 *
 * Used in UART unit tests to synchronize test execution and validate
 * asynchronous write operations.
 *test/drivers/uart/test_uart.c
 * @param[in] handle UART handle associated with the transaction.
 * @param[in] trans  Pointer to the completed UART_Transaction structure.
 *
 * @return void
 */
void TestUart_uartReadCallbackMt(UART_Handle handle, UART_Transaction *trans)
{
    if (trans->args != NULL)
    {
        /* Post the read completion semaphore */
        SemaphoreP_post((SemaphoreP_Object *)trans->args);
    }
}

/**
 * @brief UART write thread for callback interrupt test (CONFIG_UART1).
 *
 * This thread performs a UART_write operation in callback mode with interrupt
 * transfer on CONFIG_UART1. It initializes UART parameters, prepares a transmit
 * buffer and transaction, waits for completion via a semaphore, updates
 * TestUart_finalStatus on error, closes the handle, and signals the main test.
 *
 * Test Steps:
 * 1. Initialize UART parameters for interrupt transfer and callback write.
 * 2. Open UART instance CONFIG_UART1.
 * 3. Construct a semaphore for write completion.
 * 4. Prepare the transmit buffer and transaction.
 * 5. Start UART_write.
 * 6. Wait for write completion via the semaphore.
 * 7. Cleanup semaphore and close the UART handle.
 * 8. Update TestUart_finalStatus on errors.
 * 9. Signal the main thread via the provided semaphore.
 *
 * @param[in] args Pointer to semaphore object for thread synchronization.
 *
 * @return void
 */
static void TestUart_writeThread1(void *args)
{
    int32_t transferOK = SystemP_FAILURE;
    UART_Handle uartHandle = NULL;
    UART_Transaction testUartTrans = {0};
    static UART_Params uartParams = {0};
    int32_t status = SystemP_FAILURE;
    uint8_t uartTxBuffer[256] = {0};
    SemaphoreP_Object uartWriteDoneSem;

    /* Initialize UART parameters */
    UART_Params_init(&uartParams);
    uartParams.transferMode = UART_CONFIG_MODE_INTERRUPT;
    uartParams.writeMode = UART_TRANSFER_MODE_CALLBACK;
    uartParams.writeCallbackFxn = TestUart_uartWriteCallbackMt;
#if defined(SOC_AM62AX) || defined(SOC_AM62PX)
#if defined(CPU_C7X)
    uartParams.intrNum = 24U;
    uartParams.eventId = 434;
#else
    uartParams.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_UART0_USART_IRQ_0;
#endif
#elif defined(SOC_AM62DX)
#if defined(CPU_C7X)
    uartParams.intrNum = 24U;
    uartParams.eventId = 434;
#else
    uartParams.intrNum = CSLR_GICSS0_COMMON_0_SPI_UART0_USART_IRQ_0;
#endif
#endif

    /* Open UART instance */
    uartHandle = UART_open(CONFIG_UART1, &uartParams);
    if (uartHandle == NULL)
    {
        TestUart_finalStatus |= (1 << 10);
    }

    /* Construct semaphore for write completion */
    status = SemaphoreP_constructBinary(&uartWriteDoneSem, 0);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1 << 11);
    }

    /* Initialize transaction */
    UART_Transaction_init(&testUartTrans);
    testUartTrans.buf = &uartTxBuffer[0U];
    strncpy((char *)testUartTrans.buf, "UART MULTITHREAD CALLBACK INTERRUPT WRITE TEST1\r\n", 256);
    testUartTrans.count = strlen((char *)testUartTrans.buf);
    testUartTrans.timeout = SystemP_WAIT_FOREVER;
    testUartTrans.args = (void *)&uartWriteDoneSem;

    /* Start the write operation */
    transferOK = UART_write(uartHandle, &testUartTrans);
    if (transferOK != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1 << 12);
    }

    /* Wait for write completion */
    SemaphoreP_pend(&uartWriteDoneSem, SystemP_WAIT_FOREVER);

    /* Cleanup */
    SemaphoreP_destruct(&uartWriteDoneSem);
    UART_close(uartHandle);

    /* Check if UART write was successful */
    if (testUartTrans.status != UART_TRANSFER_STATUS_SUCCESS)
    {
          TestUart_finalStatus |= (1 << 13);
    }

    /* Signal main thread that this write is done */
    SemaphoreP_post((SemaphoreP_Object *)args);

    TaskP_exit();
}

/**
 * @brief UART write/read thread for callback interrupt test with internal loopback (CONFIG_UART2).
 *
 * This thread performs a UART_write followed by a UART_read in callback mode
 * with interrupt transfer on CONFIG_UART2 using internal loopback. It waits
 * for both operations via semaphores, validates statuses, compares the first
 * 8 bytes, updates TestUart_finalStatus on error, and signals the main test.
 *
 * Test Steps:
 * 1. Initialize UART parameters (interrupt transfer, callback write/read, FULL return).
 * 2. Open UART instance CONFIG_UART2.
 * 3. Construct semaphores for write and read completion.
 * 4. Enable internal loopback.
 * 5. Prepare TX buffer and write transaction; start UART_write.
 * 6. Wait for write completion and verify status.
 * 7. Prepare 8-byte read transaction; start UART_read.
 * 8. Wait for read completion and verify status.
 * 9. Disable internal loopback.
 * 10. Cleanup semaphores and close the UART handle.
 * 11. Compare first 8 bytes of TX and RX; update TestUart_finalStatus on mismatch.
 * 12. Signal the main thread via the provided semaphore.
 *
 * @param[in] args Pointer to semaphore object for thread synchronization.
 *
 * @return void
 */
static void TestUart_writeThread2(void *args)
{
    int32_t transferOK;
    UART_Handle uartHandle = NULL;
    UART_Transaction testUartTrans = {0};
    UART_Transaction transUartRead = {0};
    static UART_Params uartParams = {0};
    int32_t status = SystemP_FAILURE;
    uint8_t uartTxBuffer[256] = {0};
    uint8_t uartRxBuffer[8] = {0};
    uint32_t baseAddr;
    SemaphoreP_Object uartWriteDoneSem;
    SemaphoreP_Object uartReadDoneSem;

    /* Initialize UART parameters */
    UART_Params_init(&uartParams);
    uartParams.transferMode = UART_CONFIG_MODE_INTERRUPT;
    uartParams.writeMode = UART_TRANSFER_MODE_CALLBACK;
    uartParams.writeCallbackFxn = TestUart_uartWriteCallbackMt;
    uartParams.readMode = UART_TRANSFER_MODE_CALLBACK;
    uartParams.readReturnMode = UART_READ_RETURN_MODE_FULL;
    uartParams.readCallbackFxn = TestUart_uartReadCallbackMt;
#if defined(SOC_AM62AX) || defined(SOC_AM62PX)
#if defined(CPU_C7X)
    uartParams.intrNum = 25U;
    uartParams.eventId = 435;
#else
    uartParams.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_UART1_USART_IRQ_0;
#endif
#elif defined(SOC_AM62DX)
#if defined(CPU_C7X)
    uartParams.intrNum = 25U;
    uartParams.eventId = 435;
#else
    uartParams.intrNum = CSLR_GICSS0_COMMON_0_SPI_UART1_USART_IRQ_0;
#endif
#endif

    /* Open UART instance */
    uartHandle = UART_open(CONFIG_UART2, &uartParams);
    if (uartHandle == NULL)
    {
        TestUart_finalStatus |= (1 << 3);
    }

    /* Construct semaphore for write completion */
    status = SemaphoreP_constructBinary(&uartWriteDoneSem, 0);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1 << 4);
    }

    /* Construct semaphore for read completion */
    status = SemaphoreP_constructBinary(&uartReadDoneSem, 0);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1 << 5);
    }

    /* Enable loopback mode */
    baseAddr = UART_getBaseAddr(uartHandle);
    UART_enableLoopbackMode(baseAddr);

    /* Initialize transaction */
    UART_Transaction_init(&testUartTrans);
    testUartTrans.buf = &uartTxBuffer[0U];
    strncpy((char *)testUartTrans.buf, "UART MULTITHREAD CALLBACK INTERRUPT WRITE TEST2\r\n", 256);
    testUartTrans.count = strlen((char *)testUartTrans.buf);
    testUartTrans.timeout = SystemP_WAIT_FOREVER;
    testUartTrans.args = (void *)&uartWriteDoneSem;

    /* Start the write operation */
    transferOK = UART_write(uartHandle, &testUartTrans);
    if (transferOK != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1 << 6);
    }

    /* Wait for write completion */
    SemaphoreP_pend(&uartWriteDoneSem, SystemP_WAIT_FOREVER);

    /* Check if UART write was successful */
    if (testUartTrans.status != UART_TRANSFER_STATUS_SUCCESS)
    {
          TestUart_finalStatus |=  (1 << 7);
    }

    /* Prepare first read transaction */
    UART_Transaction_init(&transUartRead);
    transUartRead.buf = &uartRxBuffer[0U];
    transUartRead.count = 8;
    transUartRead.timeout = SystemP_WAIT_FOREVER;
    transUartRead.args = (void *)&uartReadDoneSem;

    /* Start first read */
    transferOK = UART_read(uartHandle, &transUartRead);
    if (transferOK != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1 << 8);
    }

    /* Wait for first read to complete */
    SemaphoreP_pend(&uartReadDoneSem, SystemP_WAIT_FOREVER);

    /* Disable loopback mode */
    UART_disableLoopbackMode(baseAddr);

    /* Cleanup */
    SemaphoreP_destruct(&uartWriteDoneSem);
    SemaphoreP_destruct(&uartReadDoneSem);
    UART_close(uartHandle);

    /* Compare transmitted and received data */
    if (memcmp(uartTxBuffer, uartRxBuffer, 8) != 0)
    {
        TestUart_finalStatus |= (1 << 9);
    }

    /* Signal main thread that this write is done */
    SemaphoreP_post((SemaphoreP_Object *)args);

    TaskP_exit();
}

/**
 * @brief Testcase to validate UART_write API in multithreaded callback mode with interrupt transfer.
 *
 * This test spawns two threads on different UART instances.
 * Thread 1 performs a write in callback mode on CONFIG_UART1.
 * Thread 2 performs a write followed by an 8-byte read using internal loopback
 * on CONFIG_UART2, both in callback mode. A counting semaphore synchronizes
 * completion; TestUart_finalStatus aggregates errors.
 *
 * Test Steps:
 * 1. Close any existing UART handles for CONFIG_UART1 and CONFIG_UART2.
 * 2. Construct a counting semaphore (max count = 2) for thread synchronization.
 * 3. Create writeThread1 (CONFIG_UART1, callback write).
 * 4. Create writeThread2 (CONFIG_UART2, callback write + loopback read).
 * 5. Wait for both threads to signal completion via the semaphore.
 * 6. Cleanup semaphore and task objects; assert TestUart_finalStatus == 0.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
void TestUart_uartWriteMultithreadedCallbackInterrupt(void *args)
{
    int32_t status = SystemP_FAILURE;
    int instanceLoop = 0;
    TaskP_Object uartTaskObj1;
    TaskP_Object uartTaskObj2;
    TaskP_Params taskParams1 = {0};
    TaskP_Params taskParams2 = {0};
    UART_Handle uartHandle1 = NULL;
    UART_Handle uartHandle2 = NULL;
    TestUart_finalStatus = 0;
    SemaphoreP_Object TestUart_threadSemaphore;

    /* Close to ensure previous state is cleared */
    uartHandle1 = UART_getHandle(CONFIG_UART1);
    if(uartHandle1 != NULL)
    {
        UART_close(uartHandle1);
    }

    uartHandle2 = UART_getHandle(CONFIG_UART2);
    if(uartHandle2 != NULL)
    {
        UART_close(uartHandle2);
    }

    /* Construct semaphores for each thread */
    status =  SemaphoreP_constructCounting(&TestUart_threadSemaphore, 0, 2);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1 << 0);
    }

    /* Create threads for each UART instance */

    /* Create write thread1 */
    TaskP_Params_init(&taskParams1);
    taskParams1.priority       = 3U;
    taskParams1.stack          = TestUart_threadStack1;
    taskParams1.stackSize      = sizeof(TestUart_threadStack1);
    taskParams1.args           = (void*)&TestUart_threadSemaphore;
    taskParams1.name           = "UART_Thread_Write1";
    taskParams1.taskMain       = TestUart_writeThread1;
    status = TaskP_construct(&uartTaskObj1, &taskParams1);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1 << 1);
    }

    /* Create write thread2 */
    TaskP_Params_init(&taskParams2);
    taskParams2.priority       = 3U;
    taskParams2.stack          = TestUart_threadStack2;
    taskParams2.stackSize      = sizeof(TestUart_threadStack2);
    taskParams2.args           = (void*)&TestUart_threadSemaphore;
    taskParams2.name           = "UART_Thread_Write2";
    taskParams2.taskMain       = TestUart_writeThread2;
    status = TaskP_construct(&uartTaskObj2, &taskParams2);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1 << 2);
    }

    /* Wait for all threads to complete */
    for(instanceLoop = 0; instanceLoop < 2; instanceLoop++)
    {
        status = SemaphoreP_pend(&TestUart_threadSemaphore, SystemP_WAIT_FOREVER);
    }

    /* Cleanup */
    SemaphoreP_destruct(&TestUart_threadSemaphore);
    TaskP_destruct(&uartTaskObj1);
    TaskP_destruct(&uartTaskObj2);

    /* Check final status */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, TestUart_finalStatus);
}

/**
 * @brief Writer thread that starts a cancelable UART write (callback + interrupt).
 *
 * Starts an asynchronous UART_write on CONFIG_UART2 with a long buffer to
 * allow another thread to cancel the transaction. Publishes the UART handle
 * and transaction to the shared cancel context, signals the canceller, waits
 * for the write callback, verifies the transfer was cancelled, then cleans up
 * and signals the test body via the provided semaphore.
 *
 * Test Steps:
 * 1. Initialize UART parameters (interrupt transfer, callback write).
 * 2. Open UART instance CONFIG_UART2.
 * 3. Fill a large TX buffer with a deterministic pattern.
 * 4. Construct a binary semaphore for write completion.
 * 5. Initialize UART_Transaction (args = writeDoneSem) and start UART_write.
 * 6. Publish TestUart_cancelCtx.handle and .wTrans; post canCancelSem; yield.
 * 7. Wait for write completion via writeDoneSem.
 * 8. Verify trans.status == UART_TRANSFER_STATUS_CANCELLED; update TestUart_finalStatus on error.
 * 9. Cleanup semaphore and close the UART handle.
 * 10. Post the test-level semaphore passed in args and exit the task.
 *
 * @param[in] args Pointer to SemaphoreP_Object to be posted when this thread finishes.
 *
 * @return void
 */
static void TestUart_writerWithCancelableTx(void *args)
{
    SemaphoreP_Object *allDone = (SemaphoreP_Object *)args;
    UART_Handle uartHandle = NULL;
    static UART_Params uartParams;
    UART_Transaction trans = {0};
    static uint8_t txBuf[2048];
    SemaphoreP_Object writeDoneSem;
    int32_t status;
    uint32_t count;

    /* Init params: interrupt + callback write */
    UART_Params_init(&uartParams);
    uartParams.transferMode       = UART_CONFIG_MODE_INTERRUPT;
    uartParams.writeMode          = UART_TRANSFER_MODE_CALLBACK;
    uartParams.writeCallbackFxn   = TestUart_uartWriteCallbackMt;
#if defined(SOC_AM62AX) || defined(SOC_AM62PX)
#if defined(CPU_C7X)
    uartParams.intrNum = 25U;
    uartParams.eventId = 435;
#else
    uartParams.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_UART1_USART_IRQ_0;
#endif
#elif defined(SOC_AM62DX)
#if defined(CPU_C7X)
    uartParams.intrNum = 25U;
    uartParams.eventId = 435;
#else
    uartParams.intrNum = CSLR_GICSS0_COMMON_0_SPI_UART1_USART_IRQ_0;
#endif
#elif defined(SOC_AM275X)
#if (defined(CPU_C75_0) || defined(CPU_C75_1))
    uartParams.intrNum = 34U;
    uartParams.eventId = 436;
#else
    uartParams.intrNum = CSLR_WKUP_R5FSS0_CORE0_INTR_UART2_USART_IRQ_0;
#endif
#endif

    /* Open UART */
    uartHandle = UART_open(CONFIG_UART2, &uartParams);
    if (uartHandle == NULL)
    {
        TestUart_finalStatus |= (1U << 4);
    }
    else
    {
        uint8_t semOK = 0U;

        /* Prepare buffer */
        for ( count = 0; count < sizeof(txBuf); count++)
        {
             txBuf[count] = (uint8_t)(count & 0xFF);
        }

        /* Write-done semaphore (posted by callback) */
        status = SemaphoreP_constructBinary(&writeDoneSem, 0);
        if (status != SystemP_SUCCESS)
        {
            TestUart_finalStatus |= (1U << 5);
        }
        else
        {
            semOK = 1U;

            /* Prepare transaction */
            UART_Transaction_init(&trans);
            trans.buf     = txBuf;
            trans.count   = sizeof(txBuf);
            trans.timeout = SystemP_WAIT_FOREVER;
            trans.args    = (void *)&writeDoneSem;

            /* Start async write */
            status = UART_write(uartHandle, &trans);
            if (status != SystemP_SUCCESS)
            {
                TestUart_finalStatus |= (1U << 6);
            }
            else
            {
                /* Publish handle and trans for canceller, then allow cancel thread to run */
                TestUart_cancelCtx.handle = uartHandle;
                TestUart_cancelCtx.wTrans = &trans;
                SemaphoreP_post(&TestUart_cancelCtx.canCancelSem);
                TaskP_yield();

                /* Wait for callback (expected: CANCELLED) */
                (void)SemaphoreP_pend(&writeDoneSem, SystemP_WAIT_FOREVER);

                if (trans.status != UART_TRANSFER_STATUS_CANCELLED)
                {
                    TestUart_finalStatus |= (1U << 7);
                }
                ClockP_usleep(1000);
            }
        }

        if (semOK) { SemaphoreP_destruct(&writeDoneSem); }
        UART_close(uartHandle);
    }

    SemaphoreP_post(allDone);
    TaskP_exit();
}

/**
 * @brief Canceller thread that aborts an in-flight UART write (callback + interrupt).
 *
 * Waits until the writer thread publishes its UART handle and transaction in
 * TestUart_cancelCtx, then issues UART_writeCancel(). Signals the test-level
 * semaphore passed in args and exits. Updates TestUart_finalStatus on errors.
 *
 * Test Steps:
 * 1. Pend on TestUart_cancelCtx.canCancelSem until the writer is ready.
 * 2. Validate TestUart_cancelCtx.handle and .wTrans; set error bit and exit if null.
 * 3. Call UART_writeCancel(handle, wTrans); set error bit on failure.
 * 4. Post the completion semaphore provided in args.
 * 5. Exit the task.
 *
 * @param[in] args Pointer to SemaphoreP_Object to be posted when this thread finishes.
 *
 * @return void
 */
static void TestUart_cancellerThread(void *args)
{
    SemaphoreP_Object *allDone = (SemaphoreP_Object *)args;
    int32_t status;

    /* Wait until writer has started and published objects */
    (void)SemaphoreP_pend(&TestUart_cancelCtx.canCancelSem, SystemP_WAIT_FOREVER);

    /* Check transaction handle is not NULL*/
    if ((TestUart_cancelCtx.handle == NULL) || (TestUart_cancelCtx.wTrans == NULL))
    {
        TestUart_finalStatus |= (1U << 8);
    }
    else
    {
        /* Issue cancel; driver will invoke write callback */
        status = UART_writeCancel(TestUart_cancelCtx.handle, TestUart_cancelCtx.wTrans);
        if (status != SystemP_SUCCESS)
        {
            TestUart_finalStatus |= (1U << 9);
        }
    }

    SemaphoreP_post(allDone);
    TaskP_exit();
}

/**
 * @brief Test: one thread starts a UART write, another cancels it (same instance, callback + interrupt).
 *
 * Spawns a writer thread that starts an asynchronous UART_write on CONFIG_UART2
 * and a canceller thread that issues UART_writeCancel on the same handle.
 * Uses semaphores for synchronization and aggregates errors in TestUart_finalStatus.
 *
 * Test Steps:
 * 1. Clear shared cancel context; close any existing CONFIG_UART2 handle.
 * 2. Construct synchronization semaphores: threadSync (counting=2) and canCancelSem (binary).
 * 3. Create writer thread (TestUart_writerWithCancelableTx) and canceller thread (TestUart_cancellerThread).
 * 4. Wait for both threads to signal completion via threadSync.
 * 5. Cleanup semaphores and task objects.
 * 6. Assert TestUart_finalStatus == 0.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartWriteCancelFromOtherThread(void *args)
{
    int32_t status = SystemP_FAILURE;
    TaskP_Object writerTask;
    TaskP_Object cancelTask;
    TaskP_Params writerParams = {0};
    TaskP_Params cancelParams = {0};
    SemaphoreP_Object threadSync;
    TestUart_finalStatus = 0;
    UART_Handle uartHandle = NULL;

    /* Clean shared ctx */
    memset(&TestUart_cancelCtx, 0, sizeof(TestUart_cancelCtx));

    /* Ensure instance is closed */
    uartHandle = UART_getHandle(CONFIG_UART2);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Construct "both threads done" semaphore (counting = 2) */
    status = SemaphoreP_constructCounting(&threadSync, 0, 2);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 0);
    }

    /* Construct "can cancel now" semaphore */
    status = SemaphoreP_constructBinary(&TestUart_cancelCtx.canCancelSem, 0);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 1);
    }

    /* Create writer thread */
    TaskP_Params_init(&writerParams);
    writerParams.priority  = 3U;
    writerParams.stack     = TestUart_threadStack1;
    writerParams.stackSize = sizeof(TestUart_threadStack1);
    writerParams.args      = (void *)&threadSync;
    writerParams.name      = "UART_Writer_Cancelable";
    writerParams.taskMain  = TestUart_writerWithCancelableTx;
    status = TaskP_construct(&writerTask, &writerParams);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 2);
    }

    /* Create canceller thread */
    TaskP_Params_init(&cancelParams);
    cancelParams.priority  = 3U;
    cancelParams.stack     = TestUart_threadStack2;
    cancelParams.stackSize = sizeof(TestUart_threadStack2);
    cancelParams.args      = (void *)&threadSync;
    cancelParams.name      = "UART_Canceller";
    cancelParams.taskMain  = TestUart_cancellerThread;
    status = TaskP_construct(&cancelTask, &cancelParams);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 3);
    }

    /* Wait both threads complete */
    (void)SemaphoreP_pend(&threadSync, SystemP_WAIT_FOREVER);
    (void)SemaphoreP_pend(&threadSync, SystemP_WAIT_FOREVER);

    /* Cleanup */
    SemaphoreP_destruct(&threadSync);
    SemaphoreP_destruct(&TestUart_cancelCtx.canCancelSem);
    TaskP_destruct(&writerTask);
    TaskP_destruct(&cancelTask);

    /* Validate */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, TestUart_finalStatus);
}

/**
 * @brief Canceller thread that aborts an in-flight UART read (callback + interrupt).
 *
 * Waits until the reader thread publishes its UART handle and read transaction
 * in TestUart_cancelCtx, then issues UART_readCancel(). Posts the completion
 * semaphore provided in args and exits. Sets TestUart_finalStatus on errors.
 *
 * Test Steps:
 * 1. Pend on TestUart_cancelCtx.canCancelSem until the reader is ready.
 * 2. Small delay to ensure RX IRQ is armed.
 * 3. Validate TestUart_cancelCtx.handle and .wTrans; set error bit and exit if null.
 * 4. Call UART_readCancel(handle, wTrans); set error bit on failure.
 * 5. Post the completion semaphore provided in args and exit the task.
 *
 * @param[in] args Pointer to SemaphoreP_Object to be posted when this thread finishes.
 *
 * @return void
 */
static void TestUart_readCancellerLoopbackMT(void *args)
{
    SemaphoreP_Object *done = (SemaphoreP_Object *)args;

    /* Wait until reader has started and published objects */
    (void)SemaphoreP_pend(&TestUart_cancelCtx.canCancelSem, SystemP_WAIT_FOREVER);

    /* Small delay to ensure RX IRQ armed before cancel */
    ClockP_usleep(1000);

    /* Issue read cancel */
    if ((TestUart_cancelCtx.handle != NULL) && (TestUart_cancelCtx.wTrans != NULL))
    {
        if (UART_readCancel(TestUart_cancelCtx.handle, TestUart_cancelCtx.wTrans) != SystemP_SUCCESS)
        {
            TestUart_finalStatus |= (1U << 20);
        }
    }
    else
    {
        TestUart_finalStatus |= (1U << 21);
    }

    /* Post done semaphore */
    SemaphoreP_post(done);
    TaskP_exit();
}

/**
 * @brief Test: internal loopback write+read in callback mode, cancel the read from another thread (CONFIG_UART2).
 *
 * Starts UART in interrupt/callback mode on CONFIG_UART2 with internal loopback enabled.
 * Arms a large read (512 bytes), starts a small write (64 bytes), then a separate canceller
 * task issues UART_readCancel on the pending read. Synchronizes via semaphores and validates
 * that write succeeds and read is cancelled.
 *
 * Test Steps:
 * 1. Ensure CONFIG_UART2 is closed; clear TestUart_cancelCtx.
 * 2. Initialize UART params: interrupt, callback write/read, FULL return, small trig levels.
 * 3. Open CONFIG_UART2 and enable internal loopback.
 * 4. Construct semaphores: writeDone, readDone, cancelDone, canCancelSem.
 * 5. Create canceller task (TestUart_readCancellerLoopbackMT).
 * 6. Arm a 512-byte UART_read (pending until cancel).
 * 7. Prepare 64-byte TX buffer and start UART_write.
 * 8. Publish handle and read transaction to cancelCtx; post canCancelSem.
 * 9. Wait for cancelDone, readDone, and writeDone semaphores.
 * 10. Verify transUartRead.status == CANCELLED and testUartTrans.status == SUCCESS.
 * 11. Cleanup: destroy semaphores, stop loopback, close UART, destroy task.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartReadCancelWriteReadLoopbackMT(void *args)
{
    UART_Handle uartHandle = NULL;
    UART_Transaction testUartTrans = {0};
    UART_Transaction transUartRead = {0};
    UART_Params uartParams;
    uint32_t baseAddr = 0U;
    int32_t status = 0;
    SemaphoreP_Object writeDoneSem;
    SemaphoreP_Object readDoneSem;
    SemaphoreP_Object cancelDoneSem;
    TaskP_Object cancelTask;
    TaskP_Params cancelParams = {0};
    uint8_t txBuf[64] = {0};
    static uint8_t rxBuf[512];
    uint32_t count;

    TestUart_finalStatus = 0;
    /* Reset cancel context */
    memset(&TestUart_cancelCtx, 0, sizeof(TestUart_cancelCtx));

    /* Close any existing handle */
    uartHandle = UART_getHandle(CONFIG_UART2);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Params: interrupt transfer, callback read+write, small trig levels */
    UART_Params_init(&uartParams);
    uartParams.transferMode       = UART_CONFIG_MODE_INTERRUPT;
    uartParams.writeMode          = UART_TRANSFER_MODE_CALLBACK;
    uartParams.readMode           = UART_TRANSFER_MODE_CALLBACK;
    uartParams.readReturnMode     = UART_READ_RETURN_MODE_FULL;
    uartParams.writeCallbackFxn   = TestUart_uartWriteCallbackMt;
    uartParams.readCallbackFxn    = TestUart_uartReadCallbackMt;
    uartParams.txTrigLvl          = 4U;
    uartParams.rxTrigLvl          = 4U;

#if defined(SOC_AM62AX) || defined(SOC_AM62PX)
#if defined(CPU_C7X)
    uartParams.intrNum = 25U;
    uartParams.eventId = 435;
#else
    uartParams.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_UART1_USART_IRQ_0;
#endif
#elif defined(SOC_AM62DX)
#if defined(CPU_C7X)
    uartParams.intrNum = 25U;
    uartParams.eventId = 435;
#else
    uartParams.intrNum = CSLR_GICSS0_COMMON_0_SPI_UART1_USART_IRQ_0;
#endif
#elif defined(SOC_AM275X)
#if (defined(CPU_C75_0) || defined(CPU_C75_1))
    uartParams.intrNum = 34U;
    uartParams.eventId = 436;
#else
    uartParams.intrNum = CSLR_WKUP_R5FSS0_CORE0_INTR_UART2_USART_IRQ_0;
#endif
#endif

    /* Open UART */
    uartHandle = UART_open(CONFIG_UART2, &uartParams);
    if (uartHandle == NULL)
    {
        TestUart_finalStatus |= (1U << 22);
    }
    else
    {
        uint8_t writeSemOK = 0U, readSemOK = 0U, cancelSemOK = 0U, ctxSemOK = 0U;
        uint8_t cancelTaskOK = 0U;

        /* Enable loopback */
        baseAddr = UART_getBaseAddr(uartHandle);
        UART_enableLoopbackMode(baseAddr);

        /* Semaphores */
        status = SemaphoreP_constructBinary(&writeDoneSem, 0);
        if (status != SystemP_SUCCESS)
        {
            TestUart_finalStatus |= (1U << 23);
        }
        else
        {
            writeSemOK = 1U;
        }

        if (writeSemOK)
        {
            status = SemaphoreP_constructBinary(&readDoneSem, 0);
            if (status != SystemP_SUCCESS)
            {
                TestUart_finalStatus |= (1U << 24);
            }
            else
            {
                readSemOK = 1U;
            }
        }

        if (readSemOK)
        {
            status = SemaphoreP_constructBinary(&cancelDoneSem, 0);
            if (status != SystemP_SUCCESS)
            {
                TestUart_finalStatus |= (1U << 25);
            }
            else
            {
                cancelSemOK = 1U;
            }
        }

        if (cancelSemOK)
        {
            status = SemaphoreP_constructBinary(&TestUart_cancelCtx.canCancelSem, 0);
            if (status != SystemP_SUCCESS)
            {
                TestUart_finalStatus |= (1U << 26);
            }
            else
            {
                ctxSemOK = 1U;
            }
        }

        if (ctxSemOK)
        {
            /* Construct cancel task */
            TaskP_Params_init(&cancelParams);
            cancelParams.priority  = 3U;
            cancelParams.stack     = TestUart_threadStack2;
            cancelParams.stackSize = sizeof(TestUart_threadStack2);
            cancelParams.args      = (void *)&cancelDoneSem;
            cancelParams.name      = "UART_ReadCanceller_MT";
            cancelParams.taskMain  = TestUart_readCancellerLoopbackMT;
            status = TaskP_construct(&cancelTask, &cancelParams);
            if (status != SystemP_SUCCESS)
            {
                TestUart_finalStatus |= (1U << 29);
            }
            else
            {
                cancelTaskOK = 1U;

                /* Prepare RX (large count so it stays pending until cancel) */
                UART_Transaction_init(&transUartRead);
                transUartRead.buf     = rxBuf;
                transUartRead.count   = sizeof(rxBuf);
                transUartRead.timeout = SystemP_WAIT_FOREVER;
                transUartRead.args    = (void *)&readDoneSem;
                status = UART_read(uartHandle, &transUartRead);
                if (status != SystemP_SUCCESS)
                {
                    TestUart_finalStatus |= (1U << 27);
                }
                else
                {
                    /* Prepare TX buffer and transaction */
                    for (count = 0U; count < sizeof(txBuf); count++)
                    {
                        txBuf[count] = (uint8_t)(count & 0xFF);
                    }

                    UART_Transaction_init(&testUartTrans);
                    testUartTrans.buf     = txBuf;
                    testUartTrans.count   = sizeof(txBuf);
                    testUartTrans.timeout = SystemP_WAIT_FOREVER;
                    testUartTrans.args    = (void *)&writeDoneSem;
                    status = UART_write(uartHandle, &testUartTrans);
                    if (status != SystemP_SUCCESS)
                    {
                        TestUart_finalStatus |= (1U << 28);
                    }
                    else
                    {
                        /* Publish reader ctx and spawn canceller */
                        TestUart_cancelCtx.handle = uartHandle;
                        TestUart_cancelCtx.wTrans = &transUartRead;
                        SemaphoreP_post(&TestUart_cancelCtx.canCancelSem);

                        /* Wait for cancel and write completion */
                        (void)SemaphoreP_pend(&cancelDoneSem, SystemP_WAIT_FOREVER);
                        (void)SemaphoreP_pend(&readDoneSem, SystemP_WAIT_FOREVER);
                        (void)SemaphoreP_pend(&writeDoneSem, SystemP_WAIT_FOREVER);

                        /* Validate statuses */
                        if (transUartRead.status != UART_TRANSFER_STATUS_CANCELLED)
                        {
                            TestUart_finalStatus |= (1U << 30);
                        }
                        if (testUartTrans.status != UART_TRANSFER_STATUS_SUCCESS)
                        {
                            TestUart_finalStatus |= (1U << 31);
                        }
                    }
                }

                if (cancelTaskOK) { TaskP_destruct(&cancelTask); }
            }
        }

        if (ctxSemOK)    { SemaphoreP_destruct(&TestUart_cancelCtx.canCancelSem); }
        if (cancelSemOK) { SemaphoreP_destruct(&cancelDoneSem); }
        if (readSemOK)   { SemaphoreP_destruct(&readDoneSem); }
        if (writeSemOK)  { SemaphoreP_destruct(&writeDoneSem); }

        UART_disableLoopbackMode(baseAddr);
        UART_close(uartHandle);
    }
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, TestUart_finalStatus);
}

#if !(defined(CPU_C7X) || defined(SOC_AM62DX) || defined(SOC_AM275X))

/**
 * @brief Enable or disable the Main UART1 routing to the external connector.
 *
 * Drives the TCA6424 IO expander pin TEST_UART_IO_EXP_CODEC_RESET_PIN to the
 * requested level to control UART1 connectivity to the board connector. Updates
 * TestUart_finalStatus on any IO expander open/config/set errors.
 *
 * @param[in] state TCA6424 output level:
 *                  - TCA6424_OUT_STATE_LOW  disables routing
 *                  - TCA6424_OUT_STATE_HIGH enables routing
 *
 * @note Compiled only on SOC_AM62AX for CPU_R5F0 or CPU_A53.
 *
 * @return void
 */
static void TestUart_enableDisableUart1ToConnector(uint32_t state)
{
    TCA6424_Params ioExpParams;
    TCA6424_Config ioExpConfig;
    int32_t status;

    /* Init io expander */
    TCA6424_Params_init(&ioExpParams);
    /* Open io expander */
    status = TCA6424_open(&ioExpConfig, &ioExpParams);

    /* Configure UART1 enable */
    if (status == SystemP_SUCCESS)
    {
        status = TCA6424_config(&ioExpConfig, TEST_UART_IO_EXP_CODEC_RESET_PIN, TCA6424_MODE_OUTPUT);
    }
    else
    {
        TestUart_finalStatus |= (1U << 0U);
    }

    /* Set UART1 enable level to LOW to enable and HIGH to disable */
    if (status == SystemP_SUCCESS)
    {
        status = TCA6424_setOutput(&ioExpConfig, TEST_UART_IO_EXP_CODEC_RESET_PIN, state);
    }
    else
    {
        TestUart_finalStatus |= (1U << 1U);
    }

    /* Close io expander */
    TCA6424_close(&ioExpConfig);
}

#endif

/**
 * @brief TX thread: start async write on CONFIG_UART0 (callback + interrupt) for external loopback.
 *
 * Opens CONFIG_UART0 in interrupt/callback mode with a small TX trigger level,
 * fills gUartTxBuffer with a pattern, starts UART_write, waits for the write
 * callback via a local semaphore, updates TestUart_finalStatus on errors, closes
 * the handle, posts the test-level sync semaphore passed in args, and exits.
 *
 * Test Steps:
 * 1. Ensure CONFIG_UART0 is closed; initialize UART params (interrupt, callback write, txTrigLvl=4).
 * 2. Open CONFIG_UART0.
 * 3. Fill gUartTxBuffer with a deterministic pattern.
 * 4. Construct writeDone semaphore; setup UART_Transaction with args=writeDone.
 * 5. Start UART_write and wait for writeDone to be posted by callback.
 * 6. Verify transWrite.status == SUCCESS; set error bits on failure.
 * 7. Cleanup: destroy semaphore and close UART; post syncSem (args) and exit task.
 *
 * @param[in] args Pointer to SemaphoreP_Object used to signal thread completion.
 *
 * @return void
 */
static void TestUart_txUart2Thread(void *args)
{
    SemaphoreP_Object *syncSem = (SemaphoreP_Object *)args;
    UART_Handle uartHandle = NULL;
    UART_Transaction transWrite = {0};
    UART_Params uartParams;
    SemaphoreP_Object writeDoneSem;
    int32_t status;
    uint32_t count = 0U;

    UART_Params_init(&uartParams);
    uartParams.transferMode       = UART_CONFIG_MODE_INTERRUPT;
    uartParams.writeMode          = UART_TRANSFER_MODE_CALLBACK;
    uartParams.writeCallbackFxn   = TestUart_uartWriteCallbackMt;
    uartParams.txTrigLvl          = 4U;
    #if defined(SOC_AM62AX) || defined(SOC_AM62PX)
    uartParams.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_MCU_UART0_USART_IRQ_0;
    #elif defined(SOC_AM62DX)
    uartParams.intrNum = CSLR_GICSS0_COMMON_0_SPI_MCU_UART0_USART_IRQ_0;
    #endif

    /* Ensure clean state */
    uartHandle = UART_getHandle(CONFIG_UART0);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART0 */
    uartHandle = UART_open(CONFIG_UART0, &uartParams);
    if (uartHandle == NULL)
    {
        TestUart_finalStatus |= (1U << 12);
        SemaphoreP_post(syncSem);
        TaskP_exit();
    }

    /* Prepare TX buffer */
    for (count = 0; count < sizeof(gUartTxBuffer); count++)
    {
        gUartTxBuffer[count] = (uint8_t)(0xA0U + count);
    }

    /* Construct binary semaphore for write completion */
    status = SemaphoreP_constructBinary(&writeDoneSem, 0);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 13);
        UART_close(uartHandle);
        SemaphoreP_post(syncSem);
        TaskP_exit();
    }

    /* Initialize UART transaction */
    UART_Transaction_init(&transWrite);
    transWrite.buf     = gUartTxBuffer;
    transWrite.count   = sizeof(gUartTxBuffer);
    transWrite.timeout = SystemP_WAIT_FOREVER;
    transWrite.args    = (void *)&writeDoneSem;

    /* Start UART write transaction */
    status = UART_write(uartHandle, &transWrite);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 14);
    }
    else
    {
        /* Wait for UART write completion */
        SemaphoreP_pend(&writeDoneSem, SystemP_WAIT_FOREVER);
        if (transWrite.status != UART_TRANSFER_STATUS_SUCCESS)
        {
            TestUart_finalStatus |= (1U << 15);
        }
    }

    /* Destruct binary semaphore for write completion */
    SemaphoreP_destruct(&writeDoneSem);
    UART_close(uartHandle);

    /* Post semaphore to signal completion */
    SemaphoreP_post(syncSem);
    TaskP_exit();
}

/**
 * @brief RX thread: start async read on CONFIG_UART2 (callback + interrupt) for external loopback.
 *
 * Opens CONFIG_UART2 in interrupt/callback mode with FULL return and a small
 * RX trigger level, arms a 16-byte UART_read, waits for the read callback via
 * a local semaphore, updates TestUart_finalStatus on errors, closes the handle,
 * posts the test-level sync semaphore passed in args, and exits.
 *
 * Test Steps:
 * 1. Ensure CONFIG_UART2 is closed; initialize UART params (interrupt, callback read, rxTrigLvl=4, FULL).
 * 2. Open CONFIG_UART2.
 * 3. Construct readDone semaphore; setup UART_Transaction with args=readDone.
 * 4. Start UART_read and wait for readDone to be posted by callback.
 * 5. Record TestUart_mtRxCount; verify transRead.status == SUCCESS; set error bits on failure.
 * 6. Cleanup: destroy semaphore and close UART; post syncSem (args) and exit task.
 *
 * @param[in] args Pointer to SemaphoreP_Object used to signal thread completion.
 *
 * @return void
 */
static void TestUart_rxUart1Thread(void *args)
{
    SemaphoreP_Object *syncSem = (SemaphoreP_Object *)args;
    UART_Handle uartHandle = NULL;
    UART_Transaction transRead = {0};
    UART_Params uartParams;
    SemaphoreP_Object readDoneSem;
    int32_t status;

    /* Initialize UART parameters */
    UART_Params_init(&uartParams);
    uartParams.transferMode       = UART_CONFIG_MODE_INTERRUPT;
    uartParams.readMode           = UART_TRANSFER_MODE_CALLBACK;
    uartParams.readReturnMode     = UART_READ_RETURN_MODE_FULL;
    uartParams.readCallbackFxn    = TestUart_uartReadCallbackMt;
    uartParams.rxTrigLvl          = 4U;
    #if defined(SOC_AM62AX) || defined(SOC_AM62PX)
    uartParams.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_UART1_USART_IRQ_0;
    #elif defined(SOC_AM62DX)
    uartParams.intrNum = CSLR_GICSS0_COMMON_0_SPI_UART1_USART_IRQ_0;
    #endif

    /* Ensure clean state */
    uartHandle = UART_getHandle(CONFIG_UART2);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART2 */
    uartHandle = UART_open(CONFIG_UART2, &uartParams);
    if (uartHandle == NULL)
    {
        TestUart_finalStatus |= (1U << 16);
        SemaphoreP_post(syncSem);
        TaskP_exit();
    }

    /* Construct binary semaphore for read completion */
    status = SemaphoreP_constructBinary(&readDoneSem, 0);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 17);
        UART_close(uartHandle);
        SemaphoreP_post(syncSem);
        TaskP_exit();
    }

    /* Initialize UART transaction for read */
    UART_Transaction_init(&transRead);
    transRead.buf     = gUartRxBuffer;
    transRead.count   = 16;
    transRead.timeout = SystemP_WAIT_FOREVER;
    transRead.args    = (void *)&readDoneSem;

    /* Start UART read transaction */
    status = UART_read(uartHandle, &transRead);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 18);
    }
    else
    {
        /* Wait for UART read completion */
        SemaphoreP_pend(&readDoneSem, SystemP_WAIT_FOREVER);
        TestUart_mtRxCount = transRead.count;
        if (transRead.status != UART_TRANSFER_STATUS_SUCCESS)
        {
            TestUart_finalStatus |= (1U << 19);
        }
    }

    /* Cleanup */
    SemaphoreP_destruct(&readDoneSem);
    UART_close(uartHandle);

    /* Post semaphore to signal completion */
    SemaphoreP_post(syncSem);
    TaskP_exit();
}

/**
 * @brief External loopback TX/RX test in callback + interrupt mode.
 *
 * Spawns two tasks: TX on CONFIG_UART0 and RX on CONFIG_UART2. Each runs in
 * interrupt/callback mode. Waits via a counting semaphore, then verifies 16
 * received bytes match the transmitted prefix. Aggregates errors in
 * TestUart_finalStatus and asserts success.
 *
 * Test Steps:
 * 1. Construct counting semaphore bothDone (count=2).
 * 2. Create TX task (TestUart_txUart2Thread, CONFIG_UART0).
 * 3. Create RX task (TestUart_rxUart1Thread, CONFIG_UART2).
 * 4. Wait for both tasks to post bothDone.
 * 5. Validate TestUart_mtRxCount == 16 and buffers match for 16 bytes.
 * 6. Cleanup: destruct semaphore and tasks; log and assert final status.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_externalLoopbackUartTxRx(void *args)
{
    TaskP_Object txTask;
    TaskP_Object rxTask;
    TaskP_Params txParams = {0};
    TaskP_Params rxParams = {0};
    SemaphoreP_Object bothDone;
    int32_t status;
    TestUart_finalStatus = 0;

    /* Counting semaphore to wait both threads */
    status = SemaphoreP_constructCounting(&bothDone, 0, 2);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 20);
        TestUart_openDebugUart();
        TEST_ASSERT_EQUAL(0, TestUart_finalStatus);
        return;
    }

    /* Initialize TX task parameters */
    TaskP_Params_init(&txParams);
    txParams.priority  = 3U;
    txParams.stack     = TestUart_threadStack1;
    txParams.stackSize = sizeof(TestUart_threadStack1);
    txParams.args      = (void *)&bothDone;
    txParams.name      = "UART2_TX_CB";
    txParams.taskMain  = TestUart_txUart2Thread;
    status = TaskP_construct(&txTask, &txParams);
    if (status != SystemP_SUCCESS) TestUart_finalStatus |= (1U << 21);

    /* Initialize RX task parameters */
    TaskP_Params_init(&rxParams);
    rxParams.priority  = 3U;
    rxParams.stack     = TestUart_threadStack2;
    rxParams.stackSize = sizeof(TestUart_threadStack2);
    rxParams.args      = (void *)&bothDone;
    rxParams.name      = "UART1_RX_CB";
    rxParams.taskMain  = TestUart_rxUart1Thread;
    status = TaskP_construct(&rxTask, &rxParams);
    if (status != SystemP_SUCCESS) TestUart_finalStatus |= (1U << 22);

    /* Wait both complete */
    SemaphoreP_pend(&bothDone, SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&bothDone, SystemP_WAIT_FOREVER);

    /* Compare */
    if (TestUart_mtRxCount != 16)
    {
        TestUart_finalStatus |= (1U << 23);
    }
    /* Compare TX and RX buffers */
    else if (memcmp(gUartTxBuffer, gUartRxBuffer, 16) != 0)
    {
        TestUart_finalStatus |= (1U << 24);
    }
    /* Cleanup */
    SemaphoreP_destruct(&bothDone);
    TaskP_destruct(&txTask);
    TaskP_destruct(&rxTask);

    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, TestUart_finalStatus);
}

/**
 * @brief TX thread: start async write on CONFIG_UART0 (callback + interrupt) and cancel mid-way.
 *
 * Waits for the RX thread to arm its read, opens CONFIG_UART0 in interrupt/callback mode,
 * sends a 128-byte pattern, issues UART_writeCancel on the in-flight write, waits for the
 * write callback, records TestUart_mtTxCount, verifies CANCELLED status, cleans up, and
 * signals completion via ctx->bothDone. Updates TestUart_finalStatus on errors.
 *
 * Test Steps:
 * 1. Wait on ctx->canCancelSem (reader armed).
 * 2. Initialize UART params (interrupt, callback write, txTrigLvl=4).
 * 3. Open CONFIG_UART0.
 * 4. Fill gUartTxBuffer with 128-byte pattern.
 * 5. Construct writeDone semaphore; set UART_Transaction args=writeDone.
 * 6. Start UART_write.
 * 7. Call UART_writeCancel(uartHandle, &transWrite).
 * 8. Wait for writeDone; set TestUart_mtTxCount and verify status == CANCELLED.
 * 9. Cleanup semaphore and close UART.
 * 10. Post ctx->bothDone and exit task.
 *
 * @param[in] args Pointer to TestUart_CancelCtx used for synchronization.
 *
 * @return void
 */
static void TestUart_txThread_Uart2_Cancel(void *args)
{
    TestUart_CancelCtx *ctx = (TestUart_CancelCtx *)args;
    UART_Handle uartHandle = NULL;
    UART_Transaction transWrite = {0};
    UART_Params prms;
    SemaphoreP_Object writeDoneSem;
    int32_t status;
    uint32_t count = 0U;

    /* Wait until RX has armed a read */
    SemaphoreP_pend(&ctx->canCancelSem, SystemP_WAIT_FOREVER);

    /* Initialize UART parameters */
    UART_Params_init(&prms);
    prms.transferMode       = UART_CONFIG_MODE_INTERRUPT;
    prms.writeMode          = UART_TRANSFER_MODE_CALLBACK;
    prms.writeCallbackFxn   = TestUart_uartWriteCallbackMt;
    prms.txTrigLvl          = 4U; /* exercise ISR threshold */
    #if defined(SOC_AM62AX) || defined(SOC_AM62PX)
    prms.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_MCU_UART0_USART_IRQ_0;
    #elif defined(SOC_AM62DX)
    prms.intrNum = CSLR_GICSS0_COMMON_0_SPI_MCU_UART0_USART_IRQ_0;
    #endif

    /* Clean and open CONFIG_UART2 */
    uartHandle = UART_open(CONFIG_UART0, &prms);
    if (uartHandle == NULL)
    {
        TestUart_finalStatus |= (1U << 12);
        SemaphoreP_post(&ctx->bothDone);
        TaskP_exit();
    }

    /* Fill TX pattern */
    for (count = 0; count < 128; count++)
    {
        gUartTxBuffer[count] = (uint8_t)(0xC0U + count);
    }

    /* Construct binary semaphore for write completion */
    status = SemaphoreP_constructBinary(&writeDoneSem, 0);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 13);
        UART_close(uartHandle);
        SemaphoreP_post(&ctx->bothDone);
        TaskP_exit();
    }

    /* Initialize write transaction */
    UART_Transaction_init(&transWrite);
    transWrite.buf     = gUartTxBuffer;
    transWrite.count   = 128;
    transWrite.timeout = SystemP_WAIT_FOREVER;
    transWrite.args    = (void *)&writeDoneSem;

    /* Start async write */
    status = UART_write(uartHandle, &transWrite);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 14);
        SemaphoreP_destruct(&writeDoneSem);
        UART_close(uartHandle);
        SemaphoreP_post(&ctx->bothDone);
        TaskP_exit();
    }

    /* Allow ISR to push some data to FIFO, then cancel */
    status = UART_writeCancel(uartHandle, &transWrite);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 15);
    }

    /* Wait for write callback (expected: CANCELLED) */
    SemaphoreP_pend(&writeDoneSem, SystemP_WAIT_FOREVER);

    /* Record how many bytes were actually written before cancel */
    TestUart_mtTxCount = transWrite.count;
    if (transWrite.status != UART_TRANSFER_STATUS_CANCELLED)
    {
        TestUart_finalStatus |= (1U << 16);
    }

    /* Cleanup */
    SemaphoreP_destruct(&writeDoneSem);
    UART_close(uartHandle);

    SemaphoreP_post(&ctx->bothDone);
    TaskP_exit();
}

/**
 * @brief RX thread: arm partial-read on CONFIG_UART1 (callback + interrupt) to capture bytes sent before cancel.
 *
 * Opens CONFIG_UART1 in interrupt/callback mode with UART_READ_RETURN_MODE_PARTIAL and a small RX
 * trigger level. Arms a 128-byte UART_read, signals the TX thread via ctx->canCancelSem to start,
 * waits for the read callback, records TestUart_mtRxCount, verifies SUCCESS status, cleans up, and
 * posts ctx->bothDone. Updates TestUart_finalStatus on errors.
 *
 * Test Steps:
 * 1. Initialize UART params (interrupt, callback read, PARTIAL return, rxTrigLvl=4).
 * 2. Open CONFIG_UART1.
 * 3. Construct readDone semaphore.
 * 4. Setup UART_Transaction (buf=gUartRxBuffer, count=128, args=readDone).
 * 5. Start UART_read.
 * 6. Post ctx->canCancelSem to allow TX to proceed; wait for readDone.
 * 7. Set TestUart_mtRxCount; verify transRead.status == SUCCESS.
 * 8. Cleanup: destroy semaphore and close UART.
 * 9. Post ctx->bothDone and exit task.
 *
 * @param[in] args Pointer to TestUart_CancelCtx used for synchronization.
 *
 * @return void
 */
static void TestUart_rxThread_Uart1_Partial(void *args)
{
    TestUart_CancelCtx *ctx = (TestUart_CancelCtx *)args;
    UART_Handle uartHandle = NULL;
    UART_Transaction transRead = {0};
    UART_Params prms;
    SemaphoreP_Object readDoneSem;
    int32_t status;

    UART_Params_init(&prms);
    prms.transferMode       = UART_CONFIG_MODE_INTERRUPT;
    prms.readMode           = UART_TRANSFER_MODE_CALLBACK;
    prms.readReturnMode     = UART_READ_RETURN_MODE_PARTIAL;
    prms.readCallbackFxn    = TestUart_uartReadCallbackMt;
    prms.rxTrigLvl          = 4U;
    #if defined(SOC_AM62AX) || defined(SOC_AM62PX)
    prms.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_UART1_USART_IRQ_0;
    #elif defined(SOC_AM62DX)
    prms.intrNum = CSLR_GICSS0_COMMON_0_SPI_UART1_USART_IRQ_0;
    #endif

    /* Clean and open CONFIG_UART1 */
    uartHandle = UART_open(CONFIG_UART2, &prms);
    if (uartHandle == NULL)
    {
        TestUart_finalStatus |= (1U << 8);
        SemaphoreP_post(&ctx->bothDone);
        TaskP_exit();
    }

    /* Construct binary semaphore for read completion */
    status = SemaphoreP_constructBinary(&readDoneSem, 0);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 9);
        UART_close(uartHandle);
        SemaphoreP_post(&ctx->bothDone);
        TaskP_exit();
    }

    /* Arm a read larger than expected write to ensure partial completion */
    UART_Transaction_init(&transRead);
    memset(gUartRxBuffer, 0, sizeof(gUartRxBuffer));
    transRead.buf     = gUartRxBuffer;
    transRead.count   = 128;
    transRead.timeout = SystemP_WAIT_FOREVER;
    transRead.args    = (void *)&readDoneSem;

    /* Start async read */
    status = UART_read(uartHandle, &transRead);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 10);
        SemaphoreP_destruct(&readDoneSem);
        UART_close(uartHandle);
        SemaphoreP_post(&ctx->bothDone);
        TaskP_exit();
    }

    /* Signal TX to start after RX is armed */
    SemaphoreP_post(&ctx->canCancelSem);

    /* Wait for partial read to complete (callback posts) */
    SemaphoreP_pend(&readDoneSem, SystemP_WAIT_FOREVER);

    TestUart_mtRxCount = transRead.count;
    if (transRead.status != UART_TRANSFER_STATUS_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 11);
    }

    /* Cleanup */
    SemaphoreP_destruct(&readDoneSem);
    UART_close(uartHandle);

    SemaphoreP_post(&ctx->bothDone);
    TaskP_exit();
}

/**
 * @brief Two-instance external loopback: TX on CONFIG_UART0 cancelled mid-way, RX on CONFIG_UART2 captures prefix.
 *
 * Spawns two tasks: a TX thread on CONFIG_UART0 that starts an async write and cancels it,
 * and an RX thread on CONFIG_UART2 using PARTIAL return mode to capture bytes written before
 * cancel. Synchronizes via semaphores in a shared context, then validates RX count vs TX count
 * and prefix equality. Aggregates errors in TestUart_finalStatus and asserts success.
 *
 * Test Steps:
 * 1. Close any existing UART handles for CONFIG_UART0 and CONFIG_UART2.
 * 2. Construct ctx.bothDone (counting=2) and ctx.canCancelSem (binary) semaphores.
 * 3. Create RX task first (TestUart_rxThread_Uart1_Partial) to arm the read.
 * 4. Create TX task (TestUart_txThread_Uart2_Cancel) to start write and issue cancel.
 * 5. Wait for both tasks to post ctx.bothDone.
 * 6. Validate: TestUart_mtRxCount > 0, TestUart_mtTxCount > 0, RX <= TX, and buffers match for RX count.
 * 7. Cleanup semaphores and tasks; log via TestUart_openDebugUart and assert TestUart_finalStatus == 0.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartTxRxTwoInstancesWriteCancelCompare(void *args)
{
    TaskP_Object txTask;
    TaskP_Object rxTask;
    TaskP_Params txParams = {0};
    TaskP_Params rxParams = {0};
    TestUart_CancelCtx ctx;
    int32_t status;
    UART_Handle uartHandle;

    TestUart_finalStatus = 0;
    TestUart_mtTxCount = 0;
    TestUart_mtRxCount = 0;

    /* Ensure clean instances */
    uartHandle = UART_getHandle(CONFIG_UART0);
    {
    if (uartHandle) UART_close(uartHandle);
    }
    uartHandle = UART_getHandle(CONFIG_UART2);
    {
        if (uartHandle) UART_close(uartHandle);
    }

    /* Sync semaphores */
    status = SemaphoreP_constructCounting(&ctx.bothDone, 0, 2);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 0);
    }
    status = SemaphoreP_constructBinary(&ctx.canCancelSem, 0);
    if (status != SystemP_SUCCESS)
    {
         TestUart_finalStatus |= (1U << 2);
    }

    /* RX thread first (arms read), then TX thread (starts and cancels) */
    TaskP_Params_init(&rxParams);
    rxParams.priority  = 3U;
    rxParams.stack     = TestUart_threadStack1;
    rxParams.stackSize = sizeof(TestUart_threadStack1);
    rxParams.args      = (void *)&ctx;
    rxParams.name      = "UART1_RX_Partial_CB_MT";
    rxParams.taskMain  = TestUart_rxThread_Uart1_Partial;
    if (TaskP_construct(&rxTask, &rxParams) != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 3);
    }

    TaskP_Params_init(&txParams);
    txParams.priority  = 3U;
    txParams.stack     = TestUart_threadStack2;
    txParams.stackSize = sizeof(TestUart_threadStack2);
    txParams.args      = (void *)&ctx;
    txParams.name      = "UART2_TX_Cancel_CB_MT";
    txParams.taskMain  = TestUart_txThread_Uart2_Cancel;
    if (TaskP_construct(&txTask, &txParams) != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 4);
    }

    /* Wait both complete */
    SemaphoreP_pend(&ctx.bothDone, SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&ctx.bothDone, SystemP_WAIT_FOREVER);

    /* Validate: RX received <= TX written, and data prefix matches */
    if (TestUart_mtRxCount == 0U || TestUart_mtTxCount == 0U)
    {
        TestUart_finalStatus |= (1U << 5);
    }
    else
    {
        if (TestUart_mtRxCount > TestUart_mtTxCount)
        {
            TestUart_finalStatus |= (1U << 6);
        }
        /* Validate data prefix matches */
        else if (memcmp(gUartTxBuffer, gUartRxBuffer, TestUart_mtRxCount) != 0)
        {
            TestUart_finalStatus |= (1U << 7);
        }
    }

    /* Cleanup */
    SemaphoreP_destruct(&ctx.canCancelSem);
    SemaphoreP_destruct(&ctx.bothDone);
    TaskP_destruct(&txTask);
    TaskP_destruct(&rxTask);

    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, TestUart_finalStatus);
}

/**
 * @brief TX thread: async write on CONFIG_UART0 (callback + interrupt) at ctx->baud.
 *
 * Waits for the RX thread to arm, opens CONFIG_UART0 with txTrigLvl=4 and
 * baudRate=ctx->baud, fills gUartTxBuffer with ctx->len bytes, starts
 * UART_write, waits for the write callback, verifies SUCCESS, cleans up,
 * posts ctx->bothDone, and updates TestUart_finalStatus on errors.
 *
 * Test Steps:
 * 1. Wait on ctx->canCancelSem (RX armed).
 * 2. Init UART params (interrupt, callback write, txTrigLvl=4, baud=ctx->baud).
 * 3. Open CONFIG_UART0.
 * 4. Fill gUartTxBuffer with ctx->len bytes (pattern 0x5A + i).
 * 5. Construct writeDone semaphore.
 * 6. Setup UART_Transaction (buf=gUartTxBuffer, count=ctx->len, args=writeDone).
 * 7. Start UART_write and wait for writeDone.
 * 8. Verify transWrite.status == SUCCESS; set error bits on failure.
 * 9. Cleanup: destroy semaphore and close UART.
 * 10. Post ctx->bothDone and exit.
 *
 * @param[in] args Pointer to TestUart_CancelCtx used for synchronization and configuration.
 *
 * @return void
 */
static void TestUart_txBaudThreadUart0Cb(void *args)
{
    TestUart_CancelCtx *ctx = (TestUart_CancelCtx *)args;
    UART_Handle uartHandle = NULL;
    UART_Transaction transWrite = {0};
    UART_Params prms;
    SemaphoreP_Object writeDoneSem;
    uint32_t count = 0U;

    /* Wait until RX is armed */
    SemaphoreP_pend(&ctx->canCancelSem, SystemP_WAIT_FOREVER);

    /* Init transaction */
    UART_Params_init(&prms);
    prms.transferMode       = UART_CONFIG_MODE_INTERRUPT;
    prms.writeMode          = UART_TRANSFER_MODE_CALLBACK;
    prms.writeCallbackFxn   = TestUart_uartWriteCallbackMt;
    prms.txTrigLvl          = 4U;
    prms.baudRate           = ctx->baud;
    #if defined(SOC_AM62AX) || defined(SOC_AM62PX)
    prms.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_MCU_UART0_USART_IRQ_0;
    #elif defined(SOC_AM62DX)
    prms.intrNum = CSLR_GICSS0_COMMON_0_SPI_MCU_UART0_USART_IRQ_0;
    #endif

    /* Ensure clean state and open CONFIG_UART0 */
    uartHandle = UART_open(CONFIG_UART0, &prms);
    if (uartHandle == NULL)
    {
        TestUart_finalStatus |= (1U << 12);
        SemaphoreP_post(&ctx->bothDone);
        TaskP_exit();
    }

    /* Prepare TX buffer pattern */
    for (count = 0; count < ctx->len; count++)
    {
        gUartTxBuffer[count] = (uint8_t)(0x5AU + (count & 0xFF));
    }

    /* Init writeDoneSem semaphore */
    if (SemaphoreP_constructBinary(&writeDoneSem, 0) != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 13);
        UART_close(uartHandle);
        SemaphoreP_post(&ctx->bothDone);
        TaskP_exit();
    }

    /* Init transaction */
    UART_Transaction_init(&transWrite);
    transWrite.buf     = gUartTxBuffer;
    transWrite.count   = ctx->len;
    transWrite.timeout = SystemP_WAIT_FOREVER;
    transWrite.args    = (void *)&writeDoneSem;

    /* Start TX, then allow RX to start */
    if (UART_write(uartHandle, &transWrite) != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 14);
    }
    else
    {
        /* Wait for TX to complete */
        SemaphoreP_pend(&writeDoneSem, SystemP_WAIT_FOREVER);
        if (transWrite.status != UART_TRANSFER_STATUS_SUCCESS)
        {
            TestUart_finalStatus |= (1U << 15);
        }
    }

    /* Cleanup */
    SemaphoreP_destruct(&writeDoneSem);
    UART_close(uartHandle);

    SemaphoreP_post(&ctx->bothDone);
    TaskP_exit();
}

/**
 * @brief RX thread: async read on CONFIG_UART2 (callback + interrupt) at ctx->baud.
 *
 * Opens CONFIG_UART2 in interrupt/callback mode with FULL return and rxTrigLvl=4,
 * arms a UART_read of ctx->len bytes, signals TX via ctx->canCancelSem, waits for
 * the read callback, records TestUart_mtRxCount, verifies SUCCESS, cleans up, and
 * posts ctx->bothDone. Updates TestUart_finalStatus on errors.
 *
 * Test Steps:
 * 1. Initialize UART params (interrupt, callback read, FULL return, rxTrigLvl=4, baud=ctx->baud).
 * 2. Open CONFIG_UART2.
 * 3. Construct readDone semaphore.
 * 4. Setup UART_Transaction (buf=gUartRxBuffer, count=ctx->len, args=readDone).
 * 5. Start UART_read; post ctx->canCancelSem to allow TX to proceed.
 * 6. Wait for readDone; set TestUart_mtRxCount; verify transRead.status == SUCCESS.
 * 7. Cleanup: destroy semaphore and close UART; post ctx->bothDone and exit task.
 *
 * @param[in] args Pointer to TestUart_CancelCtx used for synchronization and configuration.
 *
 * @return void
 */
static void TestUart_rxBaudThreadUart2Cb(void *args)
{
    TestUart_CancelCtx *ctx = (TestUart_CancelCtx *)args;
    UART_Handle uartHandle = NULL;
    UART_Transaction transRead = {0};
    UART_Params prms;
    SemaphoreP_Object readDoneSem;

    /* Init UART params */
    UART_Params_init(&prms);
    prms.transferMode       = UART_CONFIG_MODE_INTERRUPT;
    prms.readMode           = UART_TRANSFER_MODE_CALLBACK;
    prms.readReturnMode     = UART_READ_RETURN_MODE_FULL;
    prms.readCallbackFxn    = TestUart_uartReadCallbackMt;
    prms.rxTrigLvl          = 4U;
    prms.baudRate           = ctx->baud;
    #if defined(SOC_AM62AX) || defined(SOC_AM62PX)
    prms.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_UART1_USART_IRQ_0;
    #elif defined(SOC_AM62DX)
    prms.intrNum = CSLR_GICSS0_COMMON_0_SPI_UART1_USART_IRQ_0;
    #endif

    /* Ensure clean state and open CONFIG_UART2 */
    uartHandle = UART_open(CONFIG_UART2, &prms);
    if (uartHandle == NULL)
    {
        TestUart_finalStatus |= (1U << 16);
        SemaphoreP_post(&ctx->bothDone);
        TaskP_exit();
    }

    /* Init readDone semaphore */
    if (SemaphoreP_constructBinary(&readDoneSem, 0) != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 17);
        UART_close(uartHandle);
        SemaphoreP_post(&ctx->bothDone);
        TaskP_exit();
    }

    /* Init transaction */
    UART_Transaction_init(&transRead);
    memset(gUartRxBuffer, 0, ctx->len);
    transRead.buf     = gUartRxBuffer;
    transRead.count   = ctx->len;
    transRead.timeout = SystemP_WAIT_FOREVER;
    transRead.args    = (void *)&readDoneSem;

    /* Arm RX, then allow TX to start */
    if (UART_read(uartHandle, &transRead) != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 18);
    }
    else
    {
        /* Signal TX to start */
        SemaphoreP_post(&ctx->canCancelSem);
        /* Wait for RX to complete */
        SemaphoreP_pend(&readDoneSem, SystemP_WAIT_FOREVER);
        TestUart_mtRxCount = transRead.count;
        if (transRead.status != UART_TRANSFER_STATUS_SUCCESS)
        {
            TestUart_finalStatus |= (1U << 19);
        }
    }

    /* Cleanup */
    SemaphoreP_destruct(&readDoneSem);
    UART_close(uartHandle);

    SemaphoreP_post(&ctx->bothDone);
    TaskP_exit();
}

/**
 * @brief Iterate TX/RX over multiple baud rates using two UART instances in callback + interrupt mode.
 *
 * For each baud in {115200, 57600, 38400, 19200, 9600, 4800, 2400}, spawns TX on CONFIG_UART0
 * and RX on CONFIG_UART2 (both callback mode). Synchronizes via semaphores, validates the
 * 64-byte payload equality, logs the last baud and RX data, and asserts final status.
 *
 * Test Steps:
 * 1. For each baud: reset ctx and buffers; set ctx.baud and ctx.len = 64.
 * 2. Ensure CONFIG_UART0 and CONFIG_UART2 are closed.
 * 3. Construct ctx.bothDone (counting=2) and ctx.canCancelSem (binary).
 * 4. Create RX task (TestUart_rxBaudThreadUart2Cb, CONFIG_UART2).
 * 5. Create TX task (TestUart_txBaudThreadUart0Cb, CONFIG_UART0).
 * 6. Wait for both tasks to post ctx.bothDone.
 * 7. Validate TestUart_mtRxCount == 64 and memcmp(gUartTxBuffer, gUartRxBuffer, 64) == 0.
 * 8. Cleanup semaphores and tasks for the iteration.
 * 9. After loop, log last baud and RX bytes; assert TestUart_finalStatus == 0.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartTxRxTwoInstDiffBaudListCallback(void *args)
{
    const uint32_t baudList[] = {115200U, 57600U, 38400U, 19200U, 9600U, 4800U, 2400U};
    const uint32_t len = 64U;
    uint8_t baud_count;
    TaskP_Object txTask;
    TaskP_Object rxTask;
    TaskP_Params txParams = {0};
    TaskP_Params rxParams = {0};
    TestUart_CancelCtx ctx;
    UART_Handle uartHandle;
    int32_t status;

    /* Iterate over baud rates */
    for (baud_count = 0; baud_count < (sizeof(baudList)/sizeof(baudList[0])); baud_count++)
    {
        /* Reset context and buffers */
        memset(&ctx, 0, sizeof(ctx));
        TestUart_mtRxCount = 0;
        memset(gUartTxBuffer, 0, sizeof(gUartTxBuffer));
        memset(gUartRxBuffer, 0, sizeof(gUartRxBuffer));

        ctx.baud = baudList[baud_count];
        ctx.len  = len;

        /* Ensure clean state */
        uartHandle = UART_getHandle(CONFIG_UART0);
        if (uartHandle != NULL)
        {
            UART_close(uartHandle);
        }
        uartHandle = UART_getHandle(CONFIG_UART2);
        if (uartHandle != NULL)
        {
            UART_close(uartHandle);
        }

        /* Initialize semaphores */
        status = SemaphoreP_constructCounting(&ctx.bothDone, 0, 2);
        if (status != SystemP_SUCCESS)
        {
            TestUart_finalStatus |= (1U << 20);
            break;
        }
        status = SemaphoreP_constructBinary(&ctx.canCancelSem, 0);
        if (status != SystemP_SUCCESS)
        {
            TestUart_finalStatus |= (1U << 21);
            SemaphoreP_destruct(&ctx.bothDone);
            break;
        }

        /* Initialize RX task parameters */
        TaskP_Params_init(&rxParams);
        rxParams.priority  = 3U;
        rxParams.stack     = TestUart_threadStack2;
        rxParams.stackSize = sizeof(TestUart_threadStack2);
        rxParams.args      = (void *)&ctx;
        rxParams.name      = "UART2_RX_Baud_CB";
        rxParams.taskMain  = TestUart_rxBaudThreadUart2Cb;
        if (TaskP_construct(&rxTask, &rxParams) != SystemP_SUCCESS)
        {
            TestUart_finalStatus |= (1U << 22);
        }

        /* Initialize TX task parameters */
        TaskP_Params_init(&txParams);
        txParams.priority  = 3U;
        txParams.stack     = TestUart_threadStack1;
        txParams.stackSize = sizeof(TestUart_threadStack1);
        txParams.args      = (void *)&ctx;
        txParams.name      = "UART0_TX_Baud_CB";
        txParams.taskMain  = TestUart_txBaudThreadUart0Cb;
        if (TaskP_construct(&txTask, &txParams) != SystemP_SUCCESS)
        {
            TestUart_finalStatus |= (1U << 23);
        }

        /* Wait both complete */
        SemaphoreP_pend(&ctx.bothDone, SystemP_WAIT_FOREVER);
        SemaphoreP_pend(&ctx.bothDone, SystemP_WAIT_FOREVER);

        /* Compare full payload for this baud */
        if (TestUart_mtRxCount != len)
        {
            TestUart_finalStatus |= (1U << 24);
        }
        /* Compare TX and RX buffers */
        else if (memcmp(gUartTxBuffer, gUartRxBuffer, len) != 0)
        {
            TestUart_finalStatus |= (1U << 25);
        }

        /* Cleanup per-iteration */
        SemaphoreP_destruct(&ctx.canCancelSem);
        SemaphoreP_destruct(&ctx.bothDone);
        TaskP_destruct(&txTask);
        TaskP_destruct(&rxTask);
    }

    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, TestUart_finalStatus);
}

/**
 * @brief TX thread: DMA + callback write on CONFIG_UART2 for external loopback (A53 only).
 *
 * Prepares a 512-byte deterministic pattern (TestUart_txBufferDma), configures UART in
 * DMA transfer mode with callback, opens CONFIG_UART2, starts an asynchronous UART_write,
 * waits for the write-completion callback via a local semaphore, records TestUart_mtTxCount,
 * cleans up, posts the test-level semaphore provided in args, and exits. Updates
 * TestUart_finalStatus on errors.
 *
 * Test Steps:
 * 1. Fill TestUart_txBufferDma[512] with 'A'..'Z' pattern.
 * 2. Initialize UART_Params for DMA + callback (uartDmaIndex=0, tx/rx trig=1,
 *    intrNum for UART1, txEvtNum=UDMA_PDMA_CH_MAIN0_UART1_TX, rxEvtNum=UDMA_PDMA_CH_MAIN0_UART1_RX).
 * 3. Open CONFIG_UART2.
 * 4. Construct writeDone semaphore.
 * 5. Setup UART_Transaction (buf=TestUart_txBufferDma, count=512, args=writeDone).
 * 6. CacheP_wb the TX buffer; start UART_write.
 * 7. Wait for writeDone; set TestUart_mtTxCount = trans.count.
 * 8. Cleanup: destroy semaphore and close UART.
 * 9. Post the completion semaphore (args) and exit task.
 *
 * @param[in] args Pointer to SemaphoreP_Object to be posted when this thread finishes.
 *
 * @return void
 */
static void TestUart_txUart2DmaCbThread(void *args)
{
    int32_t transferOK = SystemP_FAILURE;
    UART_Handle uartHandle = NULL;
    UART_Transaction trans = {0};
    static UART_Params uartParams = {0};
    SemaphoreP_Object writeDoneSem;
    uint32_t len = 512U;
    uint32_t count = 0U;

    /* Prepare a deterministic TX pattern */
    for (count = 0; count < len; count++)
    {
        TestUart_txBufferDma[count] = (uint8_t)('A' + (count % 26));
    }

    /* Initialize UART parameters for DMA + callback */
    UART_Params_init(&uartParams);
    uartParams.transferMode = UART_CONFIG_MODE_DMA;
    uartParams.writeMode = UART_TRANSFER_MODE_CALLBACK;
    uartParams.writeCallbackFxn = TestUart_uartWriteCallbackMt;
    uartParams.uartDmaIndex = 0;
    uartParams.txTrigLvl = UART_TXTRIGLVL_1;
    uartParams.rxTrigLvl = UART_RXTRIGLVL_1;
    #if defined(SOC_AM62AX) || defined(SOC_AM62PX)
    uartParams.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_UART1_USART_IRQ_0;
    #elif defined(SOC_AM62DX)
    uartParams.intrNum = CSLR_GICSS0_COMMON_0_SPI_UART1_USART_IRQ_0;
    #endif

    #if ((defined(SOC_AM62AX) || defined(SOC_AM62PX)) && !((defined(CPU_MCU_R5F0) || defined(CPU_C7X) || defined(CPU_R5F0)) || defined(SOC_AM62DX)))
    uartParams.txEvtNum = UDMA_PDMA_CH_MAIN0_UART1_TX;
    uartParams.rxEvtNum = UDMA_PDMA_CH_MAIN0_UART1_RX;
    #endif

    /* Open TX instance (CONFIG_UART2) */
    uartHandle = UART_open(CONFIG_UART2, &uartParams);
    if (uartHandle == NULL)
    {
        TestUart_finalStatus |= (1U << 9);
    }
    else
    {
        uint8_t semOK = 0U;

        /* Construct local semaphore to be posted from callback */
        if (SemaphoreP_constructBinary(&writeDoneSem, 0) != SystemP_SUCCESS)
        {
            TestUart_finalStatus |= (1U << 10);
        }
        else
        {
            semOK = 1U;

            /* Setup transaction */
            UART_Transaction_init(&trans);
            trans.buf     = &TestUart_txBufferDma[0U];
            trans.count   = len;
            trans.timeout = SystemP_WAIT_FOREVER;
            trans.args    = (void *)&writeDoneSem;

            /* Start async write */
            CacheP_wb((void*)TestUart_txBufferDma, len, CacheP_TYPE_ALL);
            transferOK = UART_write(uartHandle, &trans);
            if (transferOK != SystemP_SUCCESS)
            {
                TestUart_finalStatus |= (1U << 11);
            }
            else
            {
                /* Wait for callback to post */
                SemaphoreP_pend(&writeDoneSem, SystemP_WAIT_FOREVER);

                /* Record TX count from completed transaction */
                TestUart_mtTxCount = trans.count;
            }
        }

        if (semOK) { SemaphoreP_destruct(&writeDoneSem); }
        UART_close(uartHandle);
    }

    /* Signal test body that TX thread finished */
    SemaphoreP_post((SemaphoreP_Object *)args);
    TaskP_exit();
}

/**
 * @brief RX thread: interrupt + callback read on CONFIG_UART0 for external loopback (A53 only).
 *
 * Clears the RX buffer, configures UART in interrupt/callback mode, opens CONFIG_UART0,
 * arms a 512-byte UART_read, waits for the read-completion callback via a local semaphore,
 * records TestUart_mtRxCount, cleans up, posts the test-level semaphore provided in args,
 * and exits. Updates TestUart_finalStatus on errors.
 *
 * Test Steps:
 * 1. Clear gUartRxBuffer.
 * 2. Initialize UART_Params for interrupt + callback (intrNum for MCU UART0).
 * 3. Open CONFIG_UART0.
 * 4. Construct readDone semaphore.
 * 5. Setup UART_Transaction (buf=gUartRxBuffer, count=512, args=readDone).
 * 6. Start UART_read.
 * 7. Wait for readDone; set TestUart_mtRxCount = trans.count.
 * 8. Cleanup: destroy semaphore and close UART.
 * 9. Post the completion semaphore (args) and exit task.
 *
 * @param[in] args Pointer to SemaphoreP_Object to be posted when this thread finishes.
 *
 * @return void
 */
static void TestUart_rxUart1DmaCbThread(void *args)
{
    int32_t transferOK = SystemP_FAILURE;
    UART_Handle uartHandle = NULL;
    UART_Transaction trans = {0};
    static UART_Params uartParams = {0};
    SemaphoreP_Object readDoneSem;
    uint32_t len = 512U;

    /* Clear RX buffer */
    memset(gUartRxBuffer, 0, len);

    /* Initialize UART parameters for Interrupt + callback */
    UART_Params_init(&uartParams);
    uartParams.transferMode      = UART_CONFIG_MODE_INTERRUPT;
    uartParams.readMode          = UART_TRANSFER_MODE_CALLBACK;
    uartParams.readCallbackFxn   = TestUart_uartReadCallbackMt;
    #if defined(SOC_AM62AX) || defined(SOC_AM62PX)
    uartParams.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_MCU_UART0_USART_IRQ_0;
    #elif defined(SOC_AM62DX)
    uartParams.intrNum = CSLR_GICSS0_COMMON_0_SPI_MCU_UART0_USART_IRQ_0;
    #endif

    /* Open RX instance (CONFIG_UART0) */
    uartHandle = UART_open(CONFIG_UART0, &uartParams);
    if (uartHandle == NULL)
    {
        TestUart_finalStatus |= (1U << 6);
    }
    else
    {
        uint8_t semOK = 0U;

        /* Construct local semaphore to be posted from callback */
        if (SemaphoreP_constructBinary(&readDoneSem, 0) != SystemP_SUCCESS)
        {
            TestUart_finalStatus |= (1U << 7);
        }
        else
        {
            semOK = 1U;

            /* Setup transaction */
            UART_Transaction_init(&trans);
            trans.buf     = &gUartRxBuffer[0U];
            trans.count   = len;
            trans.timeout = SystemP_WAIT_FOREVER;
            trans.args    = (void *)&readDoneSem;

            /* Start async read */
            transferOK = UART_read(uartHandle, &trans);
            if (transferOK != SystemP_SUCCESS)
            {
                TestUart_finalStatus |= (1U << 8);
            }
            else
            {
                /* Wait for callback to post */
                SemaphoreP_pend(&readDoneSem, SystemP_WAIT_FOREVER);

                /* Record RX count from completed transaction */
                TestUart_mtRxCount = trans.count;
            }
        }

        if (semOK) { SemaphoreP_destruct(&readDoneSem); }
        UART_close(uartHandle);
    }

    /* Signal test body that RX thread finished */
    SemaphoreP_post((SemaphoreP_Object *)args);
    TaskP_exit();
}

/**
 * @brief External loopback test: TX on CONFIG_UART2 (DMA + callback) vs RX on CONFIG_UART0 (interrupt + callback). A53 only.
 *
 * Spawns two tasks for external loopback: a TX thread using DMA + callback on CONFIG_UART2
 * and an RX thread using interrupt + callback on CONFIG_UART0. Synchronizes via binary
 * semaphores, waits for both to complete, validates the 512-byte payload equality and
 * that both TX/RX counts match, then cleans up and asserts final status.
 *
 * Test Steps:
 * 1. Ensure CONFIG_UART0 and CONFIG_UART2 handles are closed.
 * 2. Construct txDoneSem and rxDoneSem (binary) for thread completion.
 * 3. Spawn RX first: TestUart_rxUart1DmaCbThread (CONFIG_UART0, interrupt + callback, 512 bytes).
 * 4. Spawn TX next: TestUart_txUart2DmaCbThread (CONFIG_UART2, DMA + callback, 512 bytes).
 * 5. Wait for rxDoneSem and txDoneSem.
 * 6. Validate:
 *    - memcmp(TestUart_txBufferDma, gUartRxBuffer, 512) == 0
 *    - TestUart_mtTxCount == 512 and TestUart_mtRxCount == 512
 * 7. Delay briefly to drain any pending UART activity.
 * 8. Cleanup: destruct tasks and semaphores; log via TestUart_openDebugUart; assert TestUart_finalStatus == 0.
 *
 * @param[in] args Optional argument (unused).
 *
 * @note Compiled only when CPU_A53 is defined.
 *
 * @return void
 */
void TestUart_uartTxDmaCallback(void *args)
{
    int32_t status = SystemP_FAILURE;
    SemaphoreP_Object txDoneSem;
    SemaphoreP_Object rxDoneSem;
    TaskP_Object txTask;
    TaskP_Object rxTask;
    TaskP_Params taskParams;
    UART_Handle uartHandle;
    uint32_t len = 512U;

    TestUart_finalStatus = 0;

    /* Ensure clean state */
    uartHandle = UART_getHandle(CONFIG_UART0);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    uartHandle = UART_getHandle(CONFIG_UART2);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Done semaphores for test-level sync */
    if (SemaphoreP_constructBinary(&txDoneSem, 0) != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 0);
    }
    else
    {
        uint8_t rxDoneSemOK = 0U, rxTaskOK = 0U, txTaskOK = 0U;

        if (SemaphoreP_constructBinary(&rxDoneSem, 0) != SystemP_SUCCESS)
        {
            TestUart_finalStatus |= (1U << 1);
        }
        else
        {
            rxDoneSemOK = 1U;

            /* Spawn RX first to arm read */
            TaskP_Params_init(&taskParams);
            taskParams.name      = (char *)"uart_rx_dma_cb_uart1";
            taskParams.stack     = TestUart_threadStack1;
            taskParams.stackSize = sizeof(TestUart_threadStack1);
            taskParams.priority  = 4;
            taskParams.taskMain  = TestUart_rxUart1DmaCbThread;
            taskParams.args       = (void *)&rxDoneSem;
            status = TaskP_construct(&rxTask, &taskParams);
            if (status != SystemP_SUCCESS)
            {
                TestUart_finalStatus |= (1U << 2);
            }
            else
            {
                rxTaskOK = 1U;

                /* Spawn TX */
                TaskP_Params_init(&taskParams);
                taskParams.name      = (char *)"uart_tx_dma_cb_uart2";
                taskParams.stack     = TestUart_threadStack2;
                taskParams.stackSize = sizeof(TestUart_threadStack2);
                taskParams.priority  = 4;
                taskParams.taskMain  = TestUart_txUart2DmaCbThread;
                taskParams.args       = (void *)&txDoneSem;
                status = TaskP_construct(&txTask, &taskParams);
                if (status != SystemP_SUCCESS)
                {
                    TestUart_finalStatus |= (1U << 3);
                }
                else
                {
                    txTaskOK = 1U;

                    /* Wait for both threads to finish */
                    SemaphoreP_pend(&rxDoneSem, SystemP_WAIT_FOREVER);
                    SemaphoreP_pend(&txDoneSem, SystemP_WAIT_FOREVER);

                    /* Validate counts and data equality */
                    if (0 != memcmp(TestUart_txBufferDma, gUartRxBuffer, len))
                    {
                            TestUart_finalStatus |= (1U << 4);
                    }

                    if ((TestUart_mtTxCount != len) || (TestUart_mtRxCount != len))
                    {
                        TestUart_finalStatus |= (1U << 5);
                    }

                    /*Wait for any pending UART operations to complete */
                    ClockP_usleep(10000);
                }
            }
        }

        if (txTaskOK)    { TaskP_destruct(&txTask); }
        if (rxTaskOK)    { TaskP_destruct(&rxTask); }
        if (rxDoneSemOK) { SemaphoreP_destruct(&rxDoneSem); }
        SemaphoreP_destruct(&txDoneSem);
    }
    /* test_cleanup: */

    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, TestUart_finalStatus);
}

/**
 * @brief RX thread: DMA + callback read on CONFIG_UART2 for external loopback (A53 only).
 *
 * Clears the DMA buffer (TestUart_txBufferDma), configures UART in DMA transfer
 * mode with callback, opens CONFIG_UART2, starts an asynchronous UART_read,
 * waits for the read-completion callback via a local semaphore, records
 * TestUart_mtRxCount, cleans up, posts the test-level semaphore provided in
 * args, and exits. Updates TestUart_finalStatus on errors.
 *
 * Test Steps:
 * 1. Clear TestUart_txBufferDma[512].
 * 2. Initialize UART_Params for DMA + callback (uartDmaIndex=0, tx/rx trig=1,
 *    intrNum for UART1, txEvtNum=UDMA_PDMA_CH_MAIN0_UART1_TX, rxEvtNum=UDMA_PDMA_CH_MAIN0_UART1_RX).
 * 3. Open CONFIG_UART2.
 * 4. Construct readDone semaphore.
 * 5. Setup UART_Transaction (buf=TestUart_txBufferDma, count=512, args=readDone).
 * 6. CacheP_wbInv the RX buffer; start UART_read.
 * 7. Wait for readDone; set TestUart_mtRxCount = trans.count.
 * 8. Cleanup: destroy semaphore and close UART.
 * 9. Post the completion semaphore (args) and exit task.
 *
 * @param[in] args Pointer to SemaphoreP_Object to be posted when this thread finishes.
 *
 * @note Compiled only when CPU_A53 is defined.
 *
 * @return void
 */
static void TestUart_rxUart1DmaThread(void *args)
{
    int32_t transferOK = SystemP_FAILURE;
    UART_Handle uartHandle = NULL;
    UART_Transaction trans = {0};
    static UART_Params uartParams = {0};
    SemaphoreP_Object readDoneSem;
    uint32_t len = 512U;

    /* Reset rx buffer */
    memset(TestUart_txBufferDma, 0, len);

    /* Initialize UART parameters for DMA + callback */
    UART_Params_init(&uartParams);
    uartParams.transferMode = UART_CONFIG_MODE_DMA;
    uartParams.readMode = UART_TRANSFER_MODE_CALLBACK;
    uartParams.readCallbackFxn = TestUart_uartReadCallbackMt;
    uartParams.uartDmaIndex = 0;
    uartParams.txTrigLvl = UART_TXTRIGLVL_1;
    uartParams.rxTrigLvl = UART_RXTRIGLVL_1;
    #if defined(SOC_AM62AX) || defined(SOC_AM62PX)
    uartParams.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_UART1_USART_IRQ_0;
    #elif defined(SOC_AM62DX)
    uartParams.intrNum = CSLR_GICSS0_COMMON_0_SPI_UART1_USART_IRQ_0;
    #endif

    #if ((defined(SOC_AM62AX) || defined(SOC_AM62PX)) && !((defined(CPU_MCU_R5F0) || defined(CPU_C7X) || defined(CPU_R5F0)) || defined(SOC_AM62DX)))
    uartParams.txEvtNum = UDMA_PDMA_CH_MAIN0_UART1_TX;
    uartParams.rxEvtNum = UDMA_PDMA_CH_MAIN0_UART1_RX;
    #endif

    /* Open TX instance (CONFIG_UART2) */
    uartHandle = UART_open(CONFIG_UART2, &uartParams);
    if (uartHandle == NULL)
    {
        TestUart_finalStatus |= (1U << 9);
    }
    else
    {
        uint8_t semOK = 0U;

        /* Construct local semaphore to be posted from callback */
        if (SemaphoreP_constructBinary(&readDoneSem, 0) != SystemP_SUCCESS)
        {
            TestUart_finalStatus |= (1U << 10);
        }
        else
        {
            semOK = 1U;

            /* Setup transaction */
            UART_Transaction_init(&trans);
            trans.buf     = &TestUart_txBufferDma[0U];
            trans.count   = len;
            trans.timeout = SystemP_WAIT_FOREVER;
            trans.args    = (void *)&readDoneSem;

            /* Start async write */
            CacheP_wbInv((void*)TestUart_txBufferDma, len, CacheP_TYPE_ALL);
            transferOK = UART_read(uartHandle, &trans);
            if (transferOK != SystemP_SUCCESS)
            {
                TestUart_finalStatus |= (1U << 11);
            }
            else
            {
                /* Wait for callback to post */
                SemaphoreP_pend(&readDoneSem, SystemP_WAIT_FOREVER);

                /* Record RX count from completed transaction */
                TestUart_mtRxCount = trans.count;
            }
        }

        if (semOK) { SemaphoreP_destruct(&readDoneSem); }
        UART_close(uartHandle);
    }

    /* Signal test body that TX thread finished */
    SemaphoreP_post((SemaphoreP_Object *)args);
    TaskP_exit();
}

/**
 * @brief TX thread: interrupt + callback write on CONFIG_UART0 for external loopback (A53 only).
 *
 * Prepares a 512-byte deterministic pattern in gUartTxBuffer, configures UART in
 * interrupt transfer mode with callback, opens CONFIG_UART0, starts an asynchronous
 * UART_write, waits for the write-completion callback via a local semaphore, records
 * TestUart_mtTxCount, cleans up, posts the semaphore passed in args, and exits.
 * Updates TestUart_finalStatus on errors.
 *
 * Test Steps:
 * 1. Fill gUartTxBuffer[512] with 'A'..'Z' repeating pattern.
 * 2. Initialize UART_Params for interrupt + callback (intrNum for MCU UART0).
 * 3. Open CONFIG_UART0.
 * 4. Construct writeDone semaphore.
 * 5. Setup UART_Transaction (buf=gUartTxBuffer, count=512, args=writeDone).
 * 6. Start UART_write.
 * 7. Wait for writeDone; set TestUart_mtTxCount = trans.count.
 * 8. Cleanup: destroy semaphore and close UART.
 * 9. Post the completion semaphore (args) and exit task.
 *
 * @param[in] args Pointer to SemaphoreP_Object to be posted when this thread finishes.
 *
 * @note Compiled only when CPU_A53 is defined.
 *
 * @return void
 */
static void TestUart_txUart2DmaThread(void *args)
{
    int32_t transferOK = SystemP_FAILURE;
    UART_Handle uartHandle = NULL;
    UART_Transaction trans = {0};
    static UART_Params uartParams = {0};
    SemaphoreP_Object writeDoneSem;
    uint32_t len = 512U;
    uint32_t count = 0U;

    /* Prepare a deterministic TX pattern */
    for (count = 0; count < len; count++)
    {
        gUartTxBuffer[count] = (uint8_t)('A' + (count % 26));
    }

    /* Initialize UART parameters for Interrupt + callback */
    UART_Params_init(&uartParams);
    uartParams.transferMode      = UART_CONFIG_MODE_INTERRUPT;
    uartParams.writeMode          = UART_TRANSFER_MODE_CALLBACK;
    uartParams.writeCallbackFxn   = TestUart_uartWriteCallbackMt;
    #if defined(SOC_AM62AX) || defined(SOC_AM62PX)
    uartParams.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_MCU_UART0_USART_IRQ_0;
    #elif defined(SOC_AM62DX)
    uartParams.intrNum = CSLR_GICSS0_COMMON_0_SPI_MCU_UART0_USART_IRQ_0;
    #endif

    /* Open TX instance (CONFIG_UART0) */
    uartHandle = UART_open(CONFIG_UART0, &uartParams);
    if (uartHandle == NULL)
    {
        TestUart_finalStatus |= (1U << 6);
    }
    else
    {
        uint8_t semOK = 0U;

        /* Construct local semaphore to be posted from callback */
        if (SemaphoreP_constructBinary(&writeDoneSem, 0) != SystemP_SUCCESS)
        {
            TestUart_finalStatus |= (1U << 7);
        }
        else
        {
            semOK = 1U;

            /* Setup transaction */
            UART_Transaction_init(&trans);
            trans.buf     = &gUartTxBuffer[0U];
            trans.count   = len;
            trans.timeout = SystemP_WAIT_FOREVER;
            trans.args    = (void *)&writeDoneSem;

            /* Start async write */
            transferOK = UART_write(uartHandle, &trans);
            if (transferOK != SystemP_SUCCESS)
            {
                TestUart_finalStatus |= (1U << 8);
            }
            else
            {
                /* Wait for callback to post */
                SemaphoreP_pend(&writeDoneSem, SystemP_WAIT_FOREVER);

                /* Record TX count from completed transaction */
                TestUart_mtTxCount = trans.count;
            }
        }

        if (semOK) { SemaphoreP_destruct(&writeDoneSem); }
        UART_close(uartHandle);
    }

    /* Signal test body that RX thread finished */
    SemaphoreP_post((SemaphoreP_Object *)args);
    TaskP_exit();
}

/**
 * @brief External loopback test: RX on CONFIG_UART2 (DMA + callback) vs TX on CONFIG_UART0 (interrupt + callback). A53 only.
 *
 * Spawns two tasks for external loopback: an RX thread using DMA + callback on CONFIG_UART2
 * and a TX thread using interrupt + callback on CONFIG_UART0. Synchronizes via binary
 * semaphores, waits for both to complete, validates 512-byte payload equality between
 * TestUart_txBufferDma (RX) and gUartTxBuffer (TX), verifies both TX/RX counts, then
 * cleans up and asserts final status.
 *
 * Test Steps:
 * 1. Ensure CONFIG_UART0 and CONFIG_UART2 handles are closed.
 * 2. Construct txDoneSem and rxDoneSem (binary) for thread completion.
 * 3. Spawn RX first: TestUart_rxUart1DmaThread (CONFIG_UART2, DMA + callback, 512 bytes).
 * 4. Spawn TX next: TestUart_txUart2DmaThread (CONFIG_UART0, interrupt + callback, 512 bytes).
 * 5. Wait for rxDoneSem and txDoneSem.
 * 6. Validate:
 *    - memcmp(TestUart_txBufferDma, gUartTxBuffer, 512) == 0
 *    - TestUart_mtRxCount == 512 and TestUart_mtTxCount == 512
 * 7. Delay briefly to drain any pending UART activity.
 * 8. Cleanup: destruct tasks and semaphores; log via TestUart_openDebugUart; assert TestUart_finalStatus == 0.
 *
 * @param[in] args Optional argument (unused).
 *
 * @note Compiled only when CPU_A53 is defined.
 *
 * @return void
 */
void TestUart_uartRxDmaCallback(void *args)
{
    int32_t status = SystemP_FAILURE;
    SemaphoreP_Object txDoneSem;
    SemaphoreP_Object rxDoneSem;
    TaskP_Object txTask;
    TaskP_Object rxTask;
    TaskP_Params taskParams;
    UART_Handle uartHandle;
    uint32_t len = 512U;

    TestUart_finalStatus = 0;

    /* Ensure clean state */
    uartHandle = UART_getHandle(CONFIG_UART0);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    uartHandle = UART_getHandle(CONFIG_UART2);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Done semaphores for test-level sync */
    if (SemaphoreP_constructBinary(&txDoneSem, 0) != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 0);
    }
    else
    {
        uint8_t rxDoneSemOK = 0U, rxTaskOK = 0U, txTaskOK = 0U;

        if (SemaphoreP_constructBinary(&rxDoneSem, 0) != SystemP_SUCCESS)
        {
            TestUart_finalStatus |= (1U << 1);
        }
        else
        {
            rxDoneSemOK = 1U;

            /* Spawn RX first to arm read */
            TaskP_Params_init(&taskParams);
            taskParams.name      = (char *)"uart_rx_dma_cb_uart1";
            taskParams.stack     = TestUart_threadStack1;
            taskParams.stackSize = sizeof(TestUart_threadStack1);
            taskParams.priority  = 4;
            taskParams.taskMain  = TestUart_rxUart1DmaThread;
            taskParams.args       = (void *)&rxDoneSem;
            status = TaskP_construct(&rxTask, &taskParams);
            if (status != SystemP_SUCCESS)
            {
                TestUart_finalStatus |= (1U << 2);
            }
            else
            {
                rxTaskOK = 1U;

                /* Spawn TX */
                TaskP_Params_init(&taskParams);
                taskParams.name      = (char *)"uart_tx_dma_cb_uart2";
                taskParams.stack     = TestUart_threadStack2;
                taskParams.stackSize = sizeof(TestUart_threadStack2);
                taskParams.priority  = 4;
                taskParams.taskMain  = TestUart_txUart2DmaThread;
                taskParams.args       = (void *)&txDoneSem;
                status = TaskP_construct(&txTask, &taskParams);
                if (status != SystemP_SUCCESS)
                {
                    TestUart_finalStatus |= (1U << 3);
                }
                else
                {
                    txTaskOK = 1U;

                    /* Wait for both threads to finish */
                    SemaphoreP_pend(&rxDoneSem, SystemP_WAIT_FOREVER);
                    SemaphoreP_pend(&txDoneSem, SystemP_WAIT_FOREVER);

                    /* Validate counts and data equality */
                    if (0 != memcmp(TestUart_txBufferDma, gUartTxBuffer, len))
                    {
                            TestUart_finalStatus |= (1U << 4);
                    }

                    if ((TestUart_mtTxCount != len) || (TestUart_mtRxCount != len))
                    {
                        TestUart_finalStatus |= (1U << 5);
                    }

                    ClockP_usleep(10000);
                }
            }
        }

        if (txTaskOK)    { TaskP_destruct(&txTask); }
        if (rxTaskOK)    { TaskP_destruct(&rxTask); }
        if (rxDoneSemOK) { SemaphoreP_destruct(&rxDoneSem); }
        SemaphoreP_destruct(&txDoneSem);
    }
    /* test_cleanup: */

    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, TestUart_finalStatus);
}

/**
 * @brief TX thread: async write on CONFIG_UART0 (callback + interrupt) with hardware flow control enabled.
 *
 * Opens CONFIG_UART0 in interrupt/callback mode with CTS/RTS hardware flow control,
 * prepares a full TX buffer, starts UART_write, waits for the write callback, verifies
 * SUCCESS, cleans up, posts the sync semaphore passed in args, and exits. Updates
 * TestUart_finalStatus on errors.
 *
 * Test Steps:
 * 1. Ensure CONFIG_UART0 is closed; initialize UART params (interrupt, callback write, txTrigLvl=4,
 *    hwFlowControl=TRUE, rxTrigLvl=4, hwFlowControlThr=4).
 * 2. Open CONFIG_UART0.
 * 3. Fill gUartTxBuffer with a deterministic pattern.
 * 4. Construct writeDone semaphore; setup UART_Transaction with args=writeDone.
 * 5. Start UART_write and wait for writeDone.
 * 6. Verify transWrite.status == SUCCESS; set error bits on failure.
 * 7. Cleanup: destroy semaphore and close UART; post syncSem (args) and exit task.
 *
 * @param[in] args Pointer to SemaphoreP_Object used to signal thread completion.
 *
 * @return void
 */
static void TestUart_txUart2ThreadCtrlSignal(void *args)
{
    SemaphoreP_Object *syncSem = (SemaphoreP_Object *)args;
    UART_Handle uartHandle = NULL;
    UART_Transaction transWrite = {0};
    UART_Params uartParams;
    SemaphoreP_Object writeDoneSem;
    int32_t status;
    uint32_t count = 0U;

    /* Initialize UART parameters */
    UART_Params_init(&uartParams);
    uartParams.transferMode       = UART_CONFIG_MODE_INTERRUPT;
    uartParams.writeMode          = UART_TRANSFER_MODE_CALLBACK;
    uartParams.writeCallbackFxn   = TestUart_uartWriteCallbackMt;
    uartParams.txTrigLvl          = 4U;
    #if defined(SOC_AM62AX) || defined(SOC_AM62PX)
    uartParams.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_MCU_UART0_USART_IRQ_0;
    #elif defined(SOC_AM62DX)
    uartParams.intrNum = CSLR_GICSS0_COMMON_0_SPI_MCU_UART0_USART_IRQ_0;
    #endif
    uartParams.hwFlowControl      = (uint32_t)TRUE;
    uartParams.rxTrigLvl          = 4U;
    uartParams.hwFlowControlThr   = 4U;

    /* Ensure clean state */
    uartHandle = UART_getHandle(CONFIG_UART0);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART with configured parameters */
    uartHandle = UART_open(CONFIG_UART0, &uartParams);
    if (uartHandle == NULL)
    {
        TestUart_finalStatus |= (1U << 12);
        SemaphoreP_post(syncSem);
        TaskP_exit();
    }

    /* Prepare TX buffer */
    for (count = 0; count < sizeof(gUartTxBuffer); count++)
    {
        gUartTxBuffer[count] = (uint8_t)(0xA0U + count);
    }

    /* Construct binary semaphore for write completion */
    status = SemaphoreP_constructBinary(&writeDoneSem, 0);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 13);
        UART_close(uartHandle);
        SemaphoreP_post(syncSem);
        TaskP_exit();
    }

    /* Initialize UART transaction */
    UART_Transaction_init(&transWrite);
    transWrite.buf     = gUartTxBuffer;
    transWrite.count   = sizeof(gUartTxBuffer);
    transWrite.timeout = SystemP_WAIT_FOREVER;
    transWrite.args    = (void *)&writeDoneSem;

    /* Start UART write operation */
    status = UART_write(uartHandle, &transWrite);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 14);
    }
    else
    {
        /* Wait for write completion semaphore */
        SemaphoreP_pend(&writeDoneSem, SystemP_WAIT_FOREVER);
        if (transWrite.status != UART_TRANSFER_STATUS_SUCCESS)
        {
            TestUart_finalStatus |= (1U << 15);
        }
    }

    /* Cleanup resources */
    SemaphoreP_destruct(&writeDoneSem);
    UART_close(uartHandle);

    SemaphoreP_post(syncSem);
    TaskP_exit();
}

/**
 * @brief RX thread: start async read on CONFIG_UART2 (callback + interrupt) with hardware flow control.
 *
 * Opens CONFIG_UART2 in interrupt/callback mode with CTS/RTS hardware flow control, FULL return,
 * and rxTrigLvl=4. Arms a 16-byte UART_read, waits for the read callback via a local semaphore,
 * records TestUart_mtRxCount, verifies SUCCESS, cleans up, posts the sync semaphore passed in args,
 * and exits. Updates TestUart_finalStatus on errors.
 *
 * Test Steps:
 * 1. Ensure CONFIG_UART2 is closed; initialize UART params (interrupt, callback read, FULL,
 *    rxTrigLvl=4, hwFlowControl=TRUE, hwFlowControlThr=4).
 * 2. Open CONFIG_UART2.
 * 3. Construct readDone semaphore.
 * 4. Setup UART_Transaction (buf=gUartRxBuffer, count=16, args=readDone).
 * 5. Start UART_read and wait for readDone.
 * 6. Record TestUart_mtRxCount; verify transRead.status == SUCCESS.
 * 7. Cleanup: destroy semaphore and close UART; post syncSem (args) and exit task.
 *
 * @param[in] args Pointer to SemaphoreP_Object used to signal thread completion.
 *
 * @return void
 */
static void TestUart_rxUart1ThreadCtrlSignal(void *args)
{
    SemaphoreP_Object *syncSem = (SemaphoreP_Object *)args;
    UART_Handle uartHandle = NULL;
    UART_Transaction transRead = {0};
    UART_Params uartParams;
    SemaphoreP_Object readDoneSem;
    int32_t status;

    /* Initialize UART parameters */
    UART_Params_init(&uartParams);
    uartParams.transferMode       = UART_CONFIG_MODE_INTERRUPT;
    uartParams.readMode           = UART_TRANSFER_MODE_CALLBACK;
    uartParams.readReturnMode     = UART_READ_RETURN_MODE_FULL;
    uartParams.readCallbackFxn    = TestUart_uartReadCallbackMt;
    uartParams.rxTrigLvl          = 4U;
    #if defined(SOC_AM62AX) || defined(SOC_AM62PX)
    uartParams.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_UART1_USART_IRQ_0;
    #elif defined(SOC_AM62DX)
    uartParams.intrNum = CSLR_GICSS0_COMMON_0_SPI_UART1_USART_IRQ_0;
    #endif
    uartParams.hwFlowControl      = (uint32_t)TRUE;
    uartParams.hwFlowControlThr   = 4U;

    /* Ensure clean state */
    uartHandle = UART_getHandle(CONFIG_UART2);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART with configured parameters */
    uartHandle = UART_open(CONFIG_UART2, &uartParams);
    if (uartHandle == NULL)
    {
        TestUart_finalStatus |= (1U << 16);
        SemaphoreP_post(syncSem);
        TaskP_exit();
    }

    /* Construct binary semaphore for read completion */
    status = SemaphoreP_constructBinary(&readDoneSem, 0);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 17);
        UART_close(uartHandle);
        SemaphoreP_post(syncSem);
        TaskP_exit();
    }

    /* Initialize UART transaction */
    UART_Transaction_init(&transRead);
    transRead.buf     = gUartRxBuffer;
    transRead.count   = 16;
    transRead.timeout = SystemP_WAIT_FOREVER;
    transRead.args    = (void *)&readDoneSem;

    status = UART_read(uartHandle, &transRead);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 18);
    }
    else
    {
        /* Wait for read completion semaphore */
        SemaphoreP_pend(&readDoneSem, SystemP_WAIT_FOREVER);
        TestUart_mtRxCount = transRead.count;
        if (transRead.status != UART_TRANSFER_STATUS_SUCCESS)
        {
            TestUart_finalStatus |= (1U << 19);
        }
    }

    /* Cleanup resources */
    SemaphoreP_destruct(&readDoneSem);
    UART_close(uartHandle);

    SemaphoreP_post(syncSem);
    TaskP_exit();
}

/**
 * @brief External loopback TX/RX in callback + interrupt mode with hardware flow control enabled.
 *
 * Spawns two tasks: TX on CONFIG_UART0 with CTS/RTS flow control and RX on CONFIG_UART2
 * with CTS/RTS flow control and FULL return mode. Uses a counting semaphore to wait
 * for both threads, then verifies 16 bytes were received and match the transmitted
 * prefix. Aggregates errors in TestUart_finalStatus and asserts success.
 *
 * Test Steps:
 * 1. Construct counting semaphore bothDone (count=2).
 * 2. Create TX task (TestUart_txUart2ThreadCtrlSignal, CONFIG_UART0, hardware flow control).
 * 3. Create RX task (TestUart_rxUart1ThreadCtrlSignal, CONFIG_UART2, hardware flow control, FULL).
 * 4. Wait for both tasks to post bothDone.
 * 5. Validate TestUart_mtRxCount == 16 and buffers match for 16 bytes.
 * 6. Cleanup: destruct semaphore and tasks; log and assert final status.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_externalLoopbackUartTxRxCtrlSignalEnabled(void *args)
{
    TaskP_Object txTask;
    TaskP_Object rxTask;
    TaskP_Params txParams = {0};
    TaskP_Params rxParams = {0};
    SemaphoreP_Object bothDone;
    int32_t status;
    TestUart_finalStatus = 0;

    /* Counting semaphore to wait both threads */
    status = SemaphoreP_constructCounting(&bothDone, 0, 2);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 20);
        TestUart_openDebugUart();
        TEST_ASSERT_EQUAL(0, TestUart_finalStatus);
        return;
    }

    /* Initialize TX task parameters */
    TaskP_Params_init(&txParams);
    txParams.priority  = 3U;
    txParams.stack     = TestUart_threadStack1;
    txParams.stackSize = sizeof(TestUart_threadStack1);
    txParams.args      = (void *)&bothDone;
    txParams.name      = "UART2_TX_CB";
    txParams.taskMain  = TestUart_txUart2ThreadCtrlSignal;
    status = TaskP_construct(&txTask, &txParams);
    if (status != SystemP_SUCCESS) TestUart_finalStatus |= (1U << 21);

    TaskP_Params_init(&rxParams);
    rxParams.priority  = 3U;
    rxParams.stack     = TestUart_threadStack2;
    rxParams.stackSize = sizeof(TestUart_threadStack2);
    rxParams.args      = (void *)&bothDone;
    rxParams.name      = "UART1_RX_CB";
    rxParams.taskMain  = TestUart_rxUart1ThreadCtrlSignal;
    status = TaskP_construct(&rxTask, &rxParams);
    if (status != SystemP_SUCCESS) TestUart_finalStatus |= (1U << 22);

    /* Wait both complete */
    SemaphoreP_pend(&bothDone, SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&bothDone, SystemP_WAIT_FOREVER);

    /* Compare */
    if (TestUart_mtRxCount != 16)
    {
        TestUart_finalStatus |= (1U << 23);
    }
    else if (memcmp(gUartTxBuffer, gUartRxBuffer, 16) != 0)
    {
        TestUart_finalStatus |= (1U << 24);
    }
    /* Cleanup */
    SemaphoreP_destruct(&bothDone);
    TaskP_destruct(&txTask);
    TaskP_destruct(&rxTask);

    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, TestUart_finalStatus);
}

/**
 * @brief TX thread: attempt async write on CONFIG_UART0 with CTS held high (hardware flow control).
 *
 * Opens CONFIG_UART0 in interrupt/callback mode with CTS/RTS enabled and expects
 * the write to not complete while CTS is asserted. Starts UART_write, polls a
 * local completion semaphore without blocking, checks that the transaction did
 * not report SUCCESS, cleans up, posts the sync semaphore passed in args, and exits.
 *
 * Test Steps:
 * 1. Ensure CONFIG_UART0 is closed; initialize UART params (interrupt, callback write,
 *    txTrigLvl=4, hwFlowControl=TRUE, rxTrigLvl=4, hwFlowControlThr=4).
 * 2. Open CONFIG_UART0.
 * 3. Fill gUartTxBuffer with a deterministic pattern.
 * 4. Construct writeDone semaphore and setup UART_Transaction (args=writeDone).
 * 5. Start UART_write.
 * 6. Poll writeDone non-blocking for ~20 ms; expect no SUCCESS completion while CTS is high.
 * 7. Cleanup: destroy semaphore and close UART; post syncSem (args) and exit task.
 *
 * @param[in] args Pointer to SemaphoreP_Object used to signal thread completion.
 *
 * @return void
 */
static void TestUart_txUart2ThreadCtsHigh(void *args)
{
    SemaphoreP_Object *syncSem = (SemaphoreP_Object *)args;
    UART_Handle uartHandle = NULL;
    UART_Transaction transWrite = {0};
    UART_Params uartParams;
    SemaphoreP_Object writeDoneSem;
    int32_t status;
    uint16_t timeout = 20U;
    uint32_t count = 0U;

    /* Initialize UART parameters */
    UART_Params_init(&uartParams);
    uartParams.transferMode       = UART_CONFIG_MODE_INTERRUPT;
    uartParams.writeMode          = UART_TRANSFER_MODE_CALLBACK;
    uartParams.writeCallbackFxn   = TestUart_uartWriteCallbackMt;
    uartParams.txTrigLvl          = 4U;
    #if defined(SOC_AM62AX) || defined(SOC_AM62PX)
    uartParams.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_MCU_UART0_USART_IRQ_0;
    #elif defined(SOC_AM62DX)
    uartParams.intrNum = CSLR_GICSS0_COMMON_0_SPI_MCU_UART0_USART_IRQ_0;
    #endif
    uartParams.hwFlowControl      = (uint32_t)TRUE;
    uartParams.rxTrigLvl          = 4U;
    uartParams.hwFlowControlThr   = 4U;

    /* Ensure clean state */
    uartHandle = UART_getHandle(CONFIG_UART0);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART with configured parameters */
    uartHandle = UART_open(CONFIG_UART0, &uartParams);
    if (uartHandle == NULL)
    {
        TestUart_finalStatus |= (1U << 12);
        SemaphoreP_post(syncSem);
        TaskP_exit();
    }

    /* Prepare TX buffer */
    for (count = 0; count < sizeof(gUartTxBuffer); count++)
    {
        gUartTxBuffer[count] = (uint8_t)(0xA0U + count);
    }

    /* Construct binary semaphore for write completion */
    status = SemaphoreP_constructBinary(&writeDoneSem, 0);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 13);
        UART_close(uartHandle);
        SemaphoreP_post(syncSem);
        TaskP_exit();
    }

    /* Initialize UART transaction */
    UART_Transaction_init(&transWrite);
    transWrite.buf     = gUartTxBuffer;
    transWrite.count   = sizeof(gUartTxBuffer);
    transWrite.timeout = SystemP_WAIT_FOREVER;
    transWrite.args    = (void *)&writeDoneSem;

    /* Write data to UART */
    status = UART_write(uartHandle, &transWrite);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 14);
    }
    else
    {
        while(timeout--)
        {
            /* Wait for write completion or timeout */
            SemaphoreP_pend(&writeDoneSem, SystemP_NO_WAIT);
            ClockP_usleep(1000U);
        }
        if (transWrite.status == UART_TRANSFER_STATUS_SUCCESS)
        {
            TestUart_finalStatus |= (1U << 15);
        }
    }

    /* Cleanup resources */
    SemaphoreP_destruct(&writeDoneSem);
    UART_close(uartHandle);

    SemaphoreP_post(syncSem);
    TaskP_exit();
}

/**
 * @brief External loopback negative test: TX on CONFIG_UART0 with CTS held high (callback + interrupt).
 *
 * Spawns a single TX task that attempts an asynchronous UART_write on CONFIG_UART0
 * with CTS/RTS hardware flow control enabled while CTS is asserted high. The test
 * polls for a short duration to confirm the write does not complete, waits for the
 * task to signal completion, verifies no bytes were reported written (TestUart_mtTxCount == 0),
 * cleans up, and asserts final status.
 *
 * Test Steps:
 * 1. Construct counting semaphore bothDone (count=1).
 * 2. Create TX task (TestUart_txUart2ThreadCtsHigh, CONFIG_UART0, HW flow control, CTS high).
 * 3. Wait for the TX task to post bothDone.
 * 4. Validate TestUart_mtTxCount == 0 (no successful completion while CTS is high).
 * 5. Cleanup: destruct semaphore and task; log and assert final status.
 *
 * @param[in] args Optional argument (unused).
 *
 * @note Compiled only on SOC_AM62AX for CPU_R5F0 or CPU_A53.
 *
 * @return void
 */
static void TestUart_externalLoopbackUartTxRxCtsHigh(void *args)
{
    TaskP_Object txTask;
    TaskP_Params txParams = {0};
    SemaphoreP_Object bothDone;
    int32_t status;
    TestUart_finalStatus = 0;

    /* Counting semaphore to wait both threads */
    status = SemaphoreP_constructCounting(&bothDone, 0, 1);
    if (status != SystemP_SUCCESS)
    {
        TestUart_finalStatus |= (1U << 20);
        TestUart_openDebugUart();
        TEST_ASSERT_EQUAL(0, TestUart_finalStatus);
        return;
    }

    /* Initialize TX task parameters */
    TaskP_Params_init(&txParams);
    txParams.priority  = 3U;
    txParams.stack     = TestUart_threadStack1;
    txParams.stackSize = sizeof(TestUart_threadStack1);
    txParams.args      = (void *)&bothDone;
    txParams.name      = "UART2_TX_CB";
    txParams.taskMain  = TestUart_txUart2ThreadCtsHigh;
    status = TaskP_construct(&txTask, &txParams);
    if (status != SystemP_SUCCESS) TestUart_finalStatus |= (1U << 21);

    SemaphoreP_pend(&bothDone, SystemP_WAIT_FOREVER);

    /* Compare */
    if (TestUart_mtTxCount != 0)
    {
        TestUart_finalStatus |= (1U << 23);
    }

    /* Cleanup */
    SemaphoreP_destruct(&bothDone);
    TaskP_destruct(&txTask);

    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, TestUart_finalStatus);
}


/**
 * @brief Helper task to cancel a blocking UART read operation.
 *
 * This task waits for a short delay to ensure the main thread's UART_read
 * has started and is blocking, then calls UART_readCancel to cancel the
 * pending read operation. The task exits immediately after cancellation.
 *
 * @param[in] arg Pointer to TestUart_CancelCtx containing the UART handle
 *                and transaction pointer.
 *
 * @return void
 */
static void TestUart_cancelReadTask(void *arg)
{
    TestUart_CancelCtx *ptr = (TestUart_CancelCtx *)arg;

    /* Small delay to ensure UART_read has started and is blocking */
    ClockP_usleep(2000);

    (void)UART_readCancel(ptr->handle, ptr->wTrans);

    /* Signal the main task that UART_readCancel (and readTrans = NULL) is complete,
     * then exit.  Without this, the main task's TaskP_destruct would kill this task
     * before it clears readTrans, leaving stale state in the UART driver object. */
    SemaphoreP_post(&ptr->canCancelSem);
    TaskP_exit();
}

/**
 * @brief Test UART_readCancel posts the read transfer semaphore in blocking mode.
 *
 * Opens CONFIG_UART2 in interrupt mode with blocking reads, enables internal loopback,
 * and spawns a helper task that cancels a pending blocking UART_read. The test validates
 * that UART_readCancel properly posts the internal readTransferSemObj semaphore, allowing
 * the blocking read to return with UART_TRANSFER_STATUS_CANCELLED. Verifies proper cleanup
 * and asserts final status.
 *
 * Test Steps:
 * 1. Open CONFIG_UART2 in interrupt mode with blocking read mode.
 * 2. Enable internal loopback mode.
 * 3. Prepare a read transaction requesting 8 bytes with infinite timeout (blocking).
 * 4. Spawn helper task (TestUart_cancelReadTask) to cancel the read after a short delay.
 * 5. Start blocking UART_read (will be cancelled by helper task).
 * 6. Wait for read to return due to cancellation.
 * 7. Destroy helper task.
 * 8. Validate read status is SystemP_FAILURE and transaction status is UART_TRANSFER_STATUS_CANCELLED.
 * 9. Cleanup: disable loopback, close UART; log and assert final status.
 *
 * @param[in] args Optional argument (unused).
 *
 * @note This test covers the SemaphoreP_post(&object->readTransferSemObj) code path
 *       in UART_readCancel for blocking mode.
 *
 * @return void
 */
static void TestUart_uartReadCancelPostsSem(void *args)
{
    UART_Params uartParams;
    uint16_t instId = CONFIG_UART2;

    UART_Handle      handle  = NULL;
    UART_Transaction trans   = {0};
    int32_t          readStatus;
    uint32_t         base    = 0U;
    uint8_t          finalStatus = 0;
    static TaskP_Object cancelTaskObj;
    TaskP_Params tparms;
    TestUart_CancelCtx argsCancel;

    /* Open UART in interrupt mode, blocking read */
    handle = UART_getHandle(instId);
    if (handle != NULL)
    {
        UART_close(handle);
    }

    UART_Params_init(&uartParams);
    uartParams.transferMode    = UART_CONFIG_MODE_INTERRUPT;
    uartParams.readMode        = UART_TRANSFER_MODE_BLOCKING;   /* ensure semaphore post path */
    uartParams.writeMode       = UART_TRANSFER_MODE_BLOCKING;
    uartParams.readReturnMode  = UART_READ_RETURN_MODE_FULL;
    uartParams.rxTrigLvl       = UART_RXTRIGLVL_1;
    uartParams.txTrigLvl       = UART_TXTRIGLVL_1;
    uartParams.skipIntrReg     = FALSE;

#if defined(SOC_AM62AX) || defined(SOC_AM62PX)
#if defined(CPU_C7X)
    uartParams.intrNum = 25U;
    uartParams.eventId = 435;
#else
    uartParams.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_UART1_USART_IRQ_0;
#endif
#elif defined(SOC_AM62DX)
#if defined(CPU_C7X)
    uartParams.intrNum = 25U;
    uartParams.eventId = 435;
#else
    uartParams.intrNum = CSLR_GICSS0_COMMON_0_SPI_UART1_USART_IRQ_0;
#endif
#elif defined(SOC_AM275X)
#if (defined(CPU_C75_0) || defined(CPU_C75_1))
    uartParams.intrNum = 34U;
    uartParams.eventId = 436;
#else
    uartParams.intrNum = CSLR_WKUP_R5FSS0_CORE0_INTR_UART2_USART_IRQ_0;
#endif
#endif

    handle = UART_open(instId, &uartParams);
    if (handle == NULL)
    {
        finalStatus |= 1U;
    }
    else
    {
        base = UART_getBaseAddr(handle);
        UART_enableLoopbackMode(base);

        /* Prepare a pending read that will block (no data provided) */
        UART_Transaction_init(&trans);
        trans.buf     = &gUartRxBuffer[0];
        trans.count   = 8U;                      /* request some bytes */
        trans.timeout = SystemP_WAIT_FOREVER;    /* block until completion */

        /* Spawn a helper task that will cancel the read and post the semaphore */
        argsCancel.handle = handle;
        argsCancel.wTrans = &trans;

        /* canCancelSem: "task done" semaphore — cancel task posts it after readTrans=NULL */
        uint8_t semOK = 0U;
        if (SemaphoreP_constructBinary(&argsCancel.canCancelSem, 0U) == SystemP_SUCCESS)
        {
            semOK = 1U;
        }
        else
        {
            finalStatus |= 8U;
        }

        if (semOK)
        {
            TaskP_Params_init(&tparms);
            tparms.name      = "uart_read_cancel_task";
            tparms.stack     = TestUart_threadStack2;
            tparms.stackSize = sizeof(TestUart_threadStack2);
            tparms.priority  = 3;
            tparms.taskMain  = TestUart_cancelReadTask;
            tparms.args      = &argsCancel;

            if (TaskP_construct(&cancelTaskObj, &tparms) != SystemP_SUCCESS)
            {
                finalStatus |= 2U;
            }
            else
            {
                /* Start blocking read; helper task will call UART_readCancel and post the sem */
                readStatus = UART_read(handle, &trans);

                /* Wait for the cancel task to fully finish (including object->readTrans=NULL).
                 * Without this, the higher-priority main task preempts the cancel task the
                 * instant it posts readTransferSemObj, and TaskP_destruct kills it before it
                 * clears readTrans — leaving a stale pointer that breaks the next test. */
                (void)SemaphoreP_pend(&argsCancel.canCancelSem, SystemP_WAIT_FOREVER);

                /* Destroy helper task after it has signalled completion */
                TaskP_destruct(&cancelTaskObj);

                /* Validate: read should complete due to cancel */
                if (!(readStatus == SystemP_FAILURE && trans.status == UART_TRANSFER_STATUS_CANCELLED))
                {
                    finalStatus |= 4U;
                }
            }

            SemaphoreP_destruct(&argsCancel.canCancelSem);
        }

        UART_disableLoopbackMode(base);
        UART_close(handle);
    }

    /* test_end: */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
}
