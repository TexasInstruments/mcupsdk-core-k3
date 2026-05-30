/*
 * Copyright (C) 2021-26 Texas Instruments Incorporated
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

/**
 * \file test_uart_fault_injection.c
 * Faults are injected using a stub before starting a transfer.
 */

/*===================================================================*/
/* 					      Include Files 					         */
/*===================================================================*/

#include <string.h>
#include <unity.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/TaskP.h>
#include <drivers/uart.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "test_execute.h"

/*===================================================================*/
/* 					      Macro defines 					         */
/*===================================================================*/

/* Macro to define the UART buffer size */
#define TEST_UART_APP_UART_BUFSIZE                          (2048U)

/*===================================================================*/
/* 					         Typedefs 					             */
/*===================================================================*/

typedef enum {
    TEST_UART_FAULT_NONE = UART_TRANSFER_STATUS_SUCCESS,
    TEST_UART_FAULT_BD = UART_TRANSFER_STATUS_ERROR_BI,
    TEST_UART_FAULT_FE = UART_TRANSFER_STATUS_ERROR_FE,
    TEST_UART_FAULT_PE = UART_TRANSFER_STATUS_ERROR_PE,
    TEST_UART_FAULT_OE = UART_TRANSFER_STATUS_ERROR_OE,
    TEST_UART_FAULT_I2310 = 0xAU,
} TestUart_FaultType;

/*===================================================================*/
/* 					         Global Variables			             */
/*===================================================================*/

/* Current fault to be injected */
static volatile TestUart_FaultType TestUart_CurrFault = TEST_UART_FAULT_NONE;
/* Debug UART instance index */
uint16_t TestUart_debugUart = 0;
/* Backup of debug UART configuration */
UART_Config TestUart_debugUartConfigBackup;
/* Global variable to check if debug UART is open */
uint8_t TestUart_isDebugUartOpen = 0;
/* UART TX and RX buffers */
uint8_t uartTxBuffer[TEST_UART_APP_UART_BUFSIZE];
uint8_t uartRxBuffer[TEST_UART_APP_UART_BUFSIZE];

/*===================================================================*/
/* 					         Function Declarations		             */
/*===================================================================*/

/* Config debug UART */
static void TestUart_getDebugUartConfig(uint16_t debugUartInstance);
/* Close debug UART */
static void TestUart_closeDebugUart(void);
/* Open debug UART */
static void TestUart_openDebugUart(void);
/* UART write/read test in blocking mode with interrupt transfer */
static void TestUart_uartWriteReadBlockingModeInterrupt(void *args);

/*===================================================================*/
/* 					         Function Definitions		             */
/*===================================================================*/

/**
 * @brief Unity per-test setup hook.
 *
 * Called automatically by the Unity framework before each test case.
 * Closes the debug UART (if open) to ensure a clean state and avoid
 * leftover handles affecting tests. Individual tests then perform their
 * own local initialization (opening/closing handles, semaphores, loopback).
 *
 * @note Uses `TestUart_closeDebugUart()` to clear previous debug UART state.
 *
 * @return void
 */
void setUp(void)
{
    TestUart_closeDebugUart();
}

/**
 * @brief Unity per-test teardown hook.
 *
 * Called automatically by the Unity framework after each test case.
 * Reopens the debug UART (if not already open) so subsequent test logs
 * and status prints are available on the console. Individual tests are
 * responsible for their own local cleanup.
 *
 * @note Uses `TestUart_openDebugUart()` with the backed-up configuration.
 *
 * @return void
 */
void tearDown(void)
{
    TestUart_openDebugUart();
}

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 * @brief Stub handler to inject I2C fault conditions during transfer.
 *
 * This function is called during I2C transfers to simulate specific fault conditions
 * (such as access error or arbitration lost) by setting the appropriate bits in the
 * transfer status variable. The type of fault to inject is controlled by the global
 * variable TestI2c_CurrFault.
 *
 * @param xsferStatus Pointer to the transfer status variable to modify.
 */
void TestUart_faultInjectStubHandler(uint32_t *xsferStatus)
{
    static uint8_t stateMachine = 0;

    if(TestUart_CurrFault == TEST_UART_FAULT_NONE)
        return;

    switch(TestUart_CurrFault)
    {
        case TEST_UART_FAULT_BD:
            switch(stateMachine)
            {
                case 0:
                    /* Inject Break Detect on first call */
                    *xsferStatus |= UART_INTID_RX_LINE_STAT_ERROR;
                    stateMachine++;
                    break;
                case 1:
                    /* Clear Break Detect on second call */
                    *xsferStatus |= UART_FIFO_PE_FE_BI_DETECTED;
                    stateMachine++;
                    break;
                case 2:
                    /* Clear Break Detect on second call */
                    *xsferStatus |= UART_BREAK_DETECTED_ERROR;
                    stateMachine = 0;
                    TestUart_CurrFault = TEST_UART_FAULT_NONE;
                    break;
                default:
                    break;
            }
            break;
        case TEST_UART_FAULT_FE:
            switch(stateMachine)
            {
                case 0:
                    /* Inject Break Detect on first call */
                    *xsferStatus |= UART_INTID_RX_LINE_STAT_ERROR;
                    stateMachine++;
                    break;
                case 1:
                    /* Clear Break Detect on second call */
                    *xsferStatus |= UART_FIFO_PE_FE_BI_DETECTED;
                    stateMachine++;
                    break;
                case 2:
                    /* Clear Break Detect on second call */
                    *xsferStatus |= UART_FRAMING_ERROR;
                    stateMachine = 0;
                    TestUart_CurrFault = TEST_UART_FAULT_NONE;
                    break;
                default:
                    break;
            }
            break;
        case TEST_UART_FAULT_PE:
            switch(stateMachine)
            {
                case 0:
                    /* Inject Break Detect on first call */
                    *xsferStatus |= UART_INTID_RX_LINE_STAT_ERROR;
                    stateMachine++;
                    break;
                case 1:
                    /* Clear Break Detect on second call */
                    *xsferStatus |= UART_FIFO_PE_FE_BI_DETECTED;
                    stateMachine++;
                    break;
                case 2:
                    /* Clear Break Detect on second call */
                    *xsferStatus |= UART_PARITY_ERROR;
                    stateMachine = 0;
                    TestUart_CurrFault = TEST_UART_FAULT_NONE;
                    break;
                default:
                    break;
            }
            break;
        case TEST_UART_FAULT_OE:
            switch(stateMachine)
            {
                case 0:
                    /* Inject Break Detect on first call */
                    *xsferStatus |= UART_INTID_RX_LINE_STAT_ERROR;
                    stateMachine++;
                    break;
                case 1:
                    /* Clear Break Detect on second call */
                    *xsferStatus |= UART_FIFO_PE_FE_BI_DETECTED;
                    stateMachine++;
                    break;
                case 2:
                    /* Clear Break Detect on second call */
                    *xsferStatus |= UART_OVERRUN_ERROR;
                    stateMachine = 0;
                    TestUart_CurrFault = TEST_UART_FAULT_NONE;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

/**
 * @brief Unity test entry point for UART fault injection suite.
 *
 * Selects a debug UART instance per SoC/CPU, backs up its configuration for
 * later restore, and registers/runs the UART fault injection testcases that
 * exercise internal loopback and error paths (BD/FE/PE/OE, i2310).
 *
 * The function relies on SysCfg to provide valid UART instances and interrupt
 * routing. Individual testcases open/close UART handles and manage loopback.
 *
 * @param[in] args Unused.
 *
 * @return void
 */
void test_main(void *args)
{
    uint8_t instanceId;

    UNITY_BEGIN();

    /* Debug UART instance selection */
#if defined(SOC_AM62AX) || defined(SOC_AM62DX)
#if defined(CPU_MCU_R5F0)  || defined(CPU_C7X)
    instanceId = CONFIG_UART0;
#elif defined(CPU_R5F0)
    instanceId = CONFIG_UART8;
#elif defined(CPU_A53)
    instanceId = CONFIG_UART1;
#endif /* CPU_MCU_R5F0 || CPU_C7X || CPU_R5F0 || CPU_A53 */
#elif defined(SOC_AM275X)
#if defined (CPU_WKUP_R5F)
    instanceId = CONFIG_UART7;
#elif defined (CPU_C75_0) || defined (CPU_C75_1)
    instanceId = CONFIG_UART2;
#else
    instanceId = CONFIG_UART0;
#endif
#endif /* SOC_AM62AX || SOC_AM62DX || SOC_AM275X */

    /* Backup debug UART configuration */
    TestUart_getDebugUartConfig(instanceId);

    TEST_EXECUTE_TEST_CASE(TestUart_uartWriteReadBlockingModeInterrupt, 10149, (void*)TEST_UART_FAULT_BD);
    TEST_EXECUTE_TEST_CASE(TestUart_uartWriteReadBlockingModeInterrupt, 10150, (void*)TEST_UART_FAULT_FE);
    TEST_EXECUTE_TEST_CASE(TestUart_uartWriteReadBlockingModeInterrupt, 10151, (void*)TEST_UART_FAULT_PE);
    TEST_EXECUTE_TEST_CASE(TestUart_uartWriteReadBlockingModeInterrupt, 10152, (void*)TEST_UART_FAULT_OE);

    UNITY_END();
}

/**
 * @brief Backup debug UART configuration for a given instance.
 *
 * Copies gUartConfig[debugUartInstance] into TestUart_debugUartConfigBackup
 * and records the instance in TestUart_debugUart. Used by TestUart_openDebugUart()
 * to restore and reopen the debug UART without altering the original config.
 *
 * @param[in] debugUartInstance UART config index to use as the debug UART.
 *
 * @note The instance must be a valid index (< CONFIG_UART_NUM_INSTANCES).
 *
 * @return void
 */
static void TestUart_getDebugUartConfig(uint16_t debugUartInstance)
{
    UART_Config *config = NULL;

    /* Backup the current debug UART configuration */
    config = &gUartConfig[debugUartInstance];
    memcpy(&TestUart_debugUartConfigBackup, config, sizeof(UART_Config));

    TestUart_debugUart = debugUartInstance;
}

/**
 * @brief Closes the currently selected debug UART if it is open.
 *
 * Retrieves the UART handle for TestUart_debugUart, closes it if non-NULL,
 * and resets TestUart_isDebugUartOpen to 0. Ensures a clean state before
 * tests reopen the debug UART with backed-up parameters.
 *
 * @param[in] None
 *
 * @note Used by setUp() to clear previous debug UART state.
 *
 * @return void
 */
void TestUart_closeDebugUart(void)
{
    UART_Handle uartHandle;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(TestUart_debugUart);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
        TestUart_isDebugUartOpen = 0;
    }
}

/**
 * @brief Open the debug UART using the backed-up configuration.
 *
 * If the debug UART is not already open, copies UART_Params from
 * TestUart_debugUartConfigBackup and opens the instance stored in
 * TestUart_debugUart. Sets TestUart_isDebugUartOpen to 1.
 *
 * @param[in] None
 *
 * @note Requires TestUart_getDebugUartConfig() to be called beforehand.
 *       No-op if already open.
 *
 * @return void
 */
void TestUart_openDebugUart(void)
{
    UART_Params uartParams;
    uint16_t instanceId = TestUart_debugUart;

    if(!TestUart_isDebugUartOpen)
    {
        memcpy(&uartParams, &(TestUart_debugUartConfigBackup.object->prms), sizeof(UART_Params));

        /* Open UART instance */
        UART_open(instanceId, &uartParams);

        TestUart_isDebugUartOpen = 1;
    }
}

/**
 * @brief Internal loopback write/read test (blocking + interrupt) with fault injection.
 *
 * Opens the selected UART in interrupt transfer mode, enables internal loopback,
 * performs a blocking write followed by a blocking read of 8 bytes, and uses
 * TestUart_faultInjectStubHandler to inject a requested fault via TestUart_CurrFault
 * (BD/FE/PE/OE/I2310). Verifies TX/RX transaction status, compares echoed data,
 * and restores the debug UART.
 *
 * Test Steps:
 * 1. Close any existing handle for the instance and open with interrupt transfer.
 * 2. Enable internal loopback and delay to settle.
 * 3. Blocking write a test string; expect UART_TRANSFER_STATUS_SUCCESS.
 * 4. Set TestUart_CurrFault from args and start a blocking read (8 bytes).
 * 5. Validate transRead.status matches the injected fault (or success).
 * 6. Disable loopback, close handle, and reopen debug UART.
 *
 * @param[in] args Pointer cast to TestUart_FaultType indicating the fault to inject.
 *
 * @return void
 */
void TestUart_uartWriteReadBlockingModeInterrupt(void *args)
{
    UART_Params uartParams;
    uint16_t instanceId = CONFIG_UART2;
    UART_Handle uartHandle = NULL;
    UART_Transaction trans = {0}, transRead = {0};
    int32_t transferOK = SystemP_FAILURE;
    uint8_t finalStatus = 0;
    uint32_t baseAddr = 0U;
    uint8_t error;

    /* Clean state */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    UART_Params_init(&uartParams);
    uartParams.writeMode      = UART_TRANSFER_MODE_BLOCKING;
    uartParams.transferMode   = UART_CONFIG_MODE_INTERRUPT;
    uartParams.readMode       = UART_TRANSFER_MODE_BLOCKING;
    uartParams.readReturnMode = UART_READ_RETURN_MODE_FULL;
    /* Use SysCfg default IRQ routing; do not override intrNum here */
    uartParams.txTrigLvl      = UART_TXTRIGLVL_1;
    uartParams.rxTrigLvl      = UART_RXTRIGLVL_1;
    uartParams.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_UART1_USART_IRQ_0;


    uartHandle = UART_open(instanceId, &uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 0);
    }

    baseAddr = UART_getBaseAddr(uartHandle);

    /* Enable internal loopback and let it settle */
    UART_enableLoopbackMode(baseAddr);
    ClockP_usleep(1000);

    /* Prepare TX */
    UART_Transaction_init(&trans);
    trans.buf     = &uartTxBuffer[0U];
    strncpy((char *)trans.buf, "UART BLOCKING INTERRUPT WRITE TEST\r\n", TEST_UART_APP_UART_BUFSIZE);
    trans.count   = strlen((char *)trans.buf);
    trans.timeout = SystemP_WAIT_FOREVER;

    transferOK = UART_write(uartHandle, &trans);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1 << 1);
    }

    if (trans.status != UART_TRANSFER_STATUS_SUCCESS)
    {
        finalStatus |= (1 << 2);
    }

    TestUart_CurrFault = (TestUart_FaultType)(int)args;
    error = TestUart_CurrFault;

    /* Prepare RX for first 8 bytes of echo */
    UART_Transaction_init(&transRead);
    transRead.buf     = &uartRxBuffer[0U];
    transRead.count   = 8U;
    transRead.timeout = SystemP_WAIT_FOREVER;

    transferOK = UART_read(uartHandle, &transRead);

    if (error == TEST_UART_FAULT_I2310)
    {
        error = UART_TRANSFER_STATUS_SUCCESS;
    }

    if (transRead.status != error)
    {
        finalStatus |= (1 << 4);
    }

    UART_disableLoopbackMode(baseAddr);
    UART_close(uartHandle);

    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
}
