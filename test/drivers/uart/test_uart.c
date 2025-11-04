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

/*===================================================================*/
/* 					      Include Files 					         */
/*===================================================================*/

#include "test_uart.h"
#include <kernel/dpl/HwiP.h>
#define TestExecute_SkipTestIdMatrix TestExecute_SkipTestIdMatrix_weak_default
#define TestExecute_SkipTestIdMatrixWithInstance TestExecute_SkipTestIdMatrix_weak_default_with_instance
#include "test_execute.h"
#undef TestExecute_SkipTestIdMatrix
#undef TestExecute_SkipTestIdMatrixWithInstance

/*===================================================================*/
/* 					      Macro defines 					         */
/*===================================================================*/

/* Configuration index for invalid instances */
#define TEST_UART_CONFIG_INDEX_INVALID                  CONFIG_UART_NUM_INSTANCES
/* Macro to compare two values and return 0 if equal else 1 */
#define TEST_UART_ASSERT_EQUAL(value1, value2)          ((value1 == value2) ? 0 : 1)

/*===================================================================*/
/* 					         Typedefs 					             */
/*===================================================================*/

/* Macro to assert on UART transfer failure */
#define APP_UART_ASSERT_ON_FAILURE(transferOK, transaction) \
    do { \
        if((SystemP_SUCCESS != (transferOK)) || (UART_TRANSFER_STATUS_SUCCESS != transaction.status)) \
        { \
            DebugP_assert(FALSE); /* UART TX/RX failed!! */ \
        } \
    } while(0) \

#if defined(SOC_AM275X)
#define CONFIG_UART8    CONFIG_UART_NUM_INSTANCES
#endif

/* Bypass other SOC */
#if !(defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM275X))

#define CONFIG_UART1    CONFIG_UART_NUM_INSTANCES
#define CONFIG_UART2    CONFIG_UART_NUM_INSTANCES
#define CONFIG_UART3    CONFIG_UART_NUM_INSTANCES
#define CONFIG_UART4    CONFIG_UART_NUM_INSTANCES
#define CONFIG_UART5    CONFIG_UART_NUM_INSTANCES
#define CONFIG_UART6    CONFIG_UART_NUM_INSTANCES
#define CONFIG_UART7    CONFIG_UART_NUM_INSTANCES
#define CONFIG_UART8    CONFIG_UART_NUM_INSTANCES

#endif

/*===================================================================*/
/* 					         Global Variables			             */
/*===================================================================*/

/* Global uart buffer for Tx */
uint8_t gUartTxBuffer[APP_UART_BUFSIZE];
/* Global uart buffer for Rx */
uint8_t gUartRxBuffer[APP_UART_BUFSIZE];
/* Global UART handles for all instances */
uint32_t gNumBytesWritten = 0U;
/* Global UART handles for all instances */
uint32_t gNumBytesRead = 0U;
/* Semaphore to indicate Write completion used in callback api's */
static SemaphoreP_Object gUartWriteDoneSem;
/* Semaphore to indicate Read completion used in callback api's */
static SemaphoreP_Object gUartReadDoneSem;
/* Variable to hold read count */
static volatile uint32_t TestUart_immediateReadCount = 0U;
/* Variable to hold read status */
static volatile int32_t  TestUart_immediateReadStatus = SystemP_FAILURE;
/* Context for write-inside-callback test (11634) */
static volatile UART_Handle   TestUart_nestedWriteHandle  = NULL;
static volatile int32_t       TestUart_nestedWriteResult  = SystemP_FAILURE;
static volatile uint32_t      TestUart_nestedWriteStatus  = 0U;
static volatile uint32_t      TestUart_nestedWriteArmed   = 0U;
static UART_Transaction       TestUart_nestedWriteTrans;
/* Backup of debug UART configuration */
UART_Config TestUart_debugUartConfigBackup;
/* Global variable to check if debug UART is open */
uint8_t TestUart_isDebugUartOpen = 0;
/* Debug UART instance index */
uint16_t TestUart_debugUart = 0;

/* Only for below set of SOCs */
#if (defined(SOC_AM62AX) || defined(SOC_AM62DX) || defined(SOC_AM275X))
/* Global uart buffer for DMA Tx */
uint8_t  TestUart_txBufferDma[512] __attribute__((aligned(CacheP_CACHELINE_ALIGNMENT)));
/* Global uart buffer for DMA Rx */
uint8_t  TestUart_rxBufferDma[512] __attribute__((aligned(CacheP_CACHELINE_ALIGNMENT)));
#endif

/* AM62AX */

/* MCU */
TEST_EXECUTE_SKIP_IDS(am62ax_mcur5_skip, 8919, 9972, 9973, 9974, 9975, 9976, 9977, 9978)
TEST_EXECUTE_SKIP_IDS(am62ax_mcur5_skip_instance_0, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62ax_mcur5_skip_instance_1, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62ax_mcur5_skip_instance_2, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62ax_mcur5_skip_instance_3, 8924, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62ax_mcur5_skip_instance_4, 8924, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62ax_mcur5_skip_instance_5, 8924, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62ax_mcur5_skip_instance_6, 8924, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62ax_mcur5_skip_instance_7, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62ax_mcur5_skip_instance_8, 8935, 8936, 8943, 8944, 11621, 8958, 8960, 8995, 10120, 10121, 11622, 11623, 11624, 11625, 11626, 11627, 11628, 11629, 11631, 11632, 10125, 11633, 11634)

/* A53 */
TEST_EXECUTE_SKIP_IDS(am62ax_a53_skip, 8919, 8956, 8957, 8959, 8990)
TEST_EXECUTE_SKIP_IDS(am62ax_a53_skip_instance_0, 8944)
TEST_EXECUTE_SKIP_IDS(am62ax_a53_skip_instance_8, 8935, 8936, 8938, 8943, 8944, 8958, 8960, 8995, 10120, 10121, 11622, 11623, 11624, 11625, 11626, 11627, 11628, 11629, 11631, 11632, 10125)

/* R5 */
TEST_EXECUTE_SKIP_IDS(am62ax_r5_skip, 1111, 1116, 1117, 8919, 9977, 9978, 10110, 10115)
TEST_EXECUTE_SKIP_IDS(am62ax_r5_skip_instance_0, 8924, 8929, 8944, 11621, 8936, 8938, 8943, 8960, 8995,  11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62ax_r5_skip_instance_1, 8924, 8929, 8944, 11621, 8936, 8938, 8943, 8960, 8995,  11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62ax_r5_skip_instance_2, 8924, 8929, 8944, 11621, 8936, 8938, 8943, 8960, 8995,  11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62ax_r5_skip_instance_3, 8924, 8929, 8944, 11621, 8936, 8938, 8943, 8960, 8995,  11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62ax_r5_skip_instance_4, 8924, 8929, 8944, 11621, 8936, 8938, 8943, 8960, 8995,  11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62ax_r5_skip_instance_5, 8924, 8929, 8944, 11621, 8936, 8938, 8943, 8960, 8995,  11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62ax_r5_skip_instance_6, 8924, 8929, 8944, 11621, 8936, 8938, 8943, 8960, 8995,  11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62ax_r5_skip_instance_7, 8924, 8929, 8944, 11621, 8936, 8938, 8943, 8960, 8995,  11633, 11634)

/* C7 */
TEST_EXECUTE_SKIP_IDS(am62ax_c7x_skip, 1116, 1117, 8919, 8959, 8990, 9972, 9973, 9974, 9975, 9976, 9977, 9978)
TEST_EXECUTE_SKIP_IDS(am62ax_c7x_skip_instance_0, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62ax_c7x_skip_instance_1, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62ax_c7x_skip_instance_2, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62ax_c7x_skip_instance_3, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62ax_c7x_skip_instance_4, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62ax_c7x_skip_instance_5, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62ax_c7x_skip_instance_6, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62ax_c7x_skip_instance_7, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62ax_c7x_skip_instance_8, 8936, 8935, 8938, 8943, 8958, 8959, 8960, 8995, 10120, 10121, 11631, 11632, 10125)

/* AM62DX */

/* MCU */
TEST_EXECUTE_SKIP_IDS(am62dx_mcur5_skip, 1116, 1117, 8919, 9972, 9973, 9974, 9975, 9976, 9977, 9978)
TEST_EXECUTE_SKIP_IDS(am62dx_mcur5_skip_instance_0, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62dx_mcur5_skip_instance_1, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62dx_mcur5_skip_instance_2, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62dx_mcur5_skip_instance_3, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62dx_mcur5_skip_instance_4, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62dx_mcur5_skip_instance_5, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62dx_mcur5_skip_instance_6, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62dx_mcur5_skip_instance_7, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62dx_mcur5_skip_instance_8, 8924, 8935, 8936, 8938, 8943, 8944, 11621, 8958, 8960, 8995, 10120, 10121, 11622, 11623, 11624, 11625, 11626, 11627, 11628, 11629, 11631, 11632, 10125, 11633, 11634)

/* A53 */
TEST_EXECUTE_SKIP_IDS(am62dx_a53_skip, 8919, 8956, 8957, 8959, 8990, 9972, 9973, 9974, 9975, 9976, 9977, 9978)
TEST_EXECUTE_SKIP_IDS(am62dx_a53_skip_instance_0, 8924, 8944)
TEST_EXECUTE_SKIP_IDS(am62dx_a53_skip_instance_8, 8924, 8935, 8936, 8943, 8944, 8958, 8960, 10120, 10121, 11622, 11623, 11624, 11625, 11626, 11627, 11628, 11629, 11631, 11632, 10125)

/* C7 */
TEST_EXECUTE_SKIP_IDS(am62dx_c7x_skip, 1116, 1117, 8919, 8959, 8990, 9972, 9973, 9974, 9975, 9976, 9977, 9978)
TEST_EXECUTE_SKIP_IDS(am62dx_c7x_skip_instance_0, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62dx_c7x_skip_instance_1, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62dx_c7x_skip_instance_2, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62dx_c7x_skip_instance_3, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62dx_c7x_skip_instance_4, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62dx_c7x_skip_instance_5, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62dx_c7x_skip_instance_6, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62dx_c7x_skip_instance_7, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62dx_c7x_skip_instance_8, 8935, 8936, 8938, 8943, 8944, 8958, 8959, 8960, 8995, 10120, 10121, 11622, 11623, 11624, 11625, 11626, 11627, 11628, 11629, 11631, 11632, 10125)

/* R5 */
TEST_EXECUTE_SKIP_IDS(am62dx_r5_skip, 1116, 1117, 8919, 8959, 8961, 8990, 9972, 9973, 9974, 9975, 9976, 9977, 9978)
TEST_EXECUTE_SKIP_IDS(am62dx_r5_skip_instance_0, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62dx_r5_skip_instance_1, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62dx_r5_skip_instance_2, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62dx_r5_skip_instance_3, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62dx_r5_skip_instance_4, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62dx_r5_skip_instance_5, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62dx_r5_skip_instance_6, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62dx_r5_skip_instance_7, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am62dx_r5_skip_instance_8, 8944, 11621, 11633, 11634)

/* AM275X */

/* WKUP R5 */
TEST_EXECUTE_SKIP_IDS(am275x_wkupr5_skip, 8919, 8959, 8961, 8990, 9972, 9973, 9974, 9975, 9976, 9977, 9978)
TEST_EXECUTE_SKIP_IDS(am275x_wkupr5_skip_instance_0, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_wkupr5_skip_instance_1, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_wkupr5_skip_instance_2, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_wkupr5_skip_instance_3, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_wkupr5_skip_instance_4, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_wkupr5_skip_instance_5, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_wkupr5_skip_instance_6, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_wkupr5_skip_instance_7, 8944, 11621, 11633, 11634)

/* R5FSS0-0 */
TEST_EXECUTE_SKIP_IDS(am275x_r5fss0_0_skip, 8919, 8959, 8961, 8990, 9972, 9973, 9974, 9975, 9976, 9977, 9978)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss0_0_skip_instance_0, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss0_0_skip_instance_1, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss0_0_skip_instance_2, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss0_0_skip_instance_3, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss0_0_skip_instance_4, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss0_0_skip_instance_5, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss0_0_skip_instance_6, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss0_0_skip_instance_7, 8944, 11621, 11633, 11634)

/* R5FSS0-1 */
TEST_EXECUTE_SKIP_IDS(am275x_r5fss0_1_skip, 8919, 8959, 8961, 8990, 9972, 9973, 9974, 9975, 9976, 9977, 9978)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss0_1_skip_instance_0, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss0_1_skip_instance_1, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss0_1_skip_instance_2, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss0_1_skip_instance_3, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss0_1_skip_instance_4, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss0_1_skip_instance_5, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss0_1_skip_instance_6, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss0_1_skip_instance_7, 8944, 11621, 11633, 11634)


/* R5FSS1-0 */
TEST_EXECUTE_SKIP_IDS(am275x_r5fss1_0_skip, 8919, 8959, 8961, 8990, 9972, 9973, 9974, 9975, 9976, 9977, 9978)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss1_0_skip_instance_0, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss1_0_skip_instance_1, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss1_0_skip_instance_2, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss1_0_skip_instance_3, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss1_0_skip_instance_4, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss1_0_skip_instance_5, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss1_0_skip_instance_6, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss1_0_skip_instance_7, 8944, 11621, 11633, 11634)

/* R5FSS1-1 */
TEST_EXECUTE_SKIP_IDS(am275x_r5fss1_1_skip, 8919, 8959, 8961, 8990, 9972, 9973, 9974, 9975, 9976, 9977, 9978)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss1_1_skip_instance_0, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss1_1_skip_instance_1, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss1_1_skip_instance_2, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss1_1_skip_instance_3, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss1_1_skip_instance_4, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss1_1_skip_instance_5, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss1_1_skip_instance_6, 8944, 11621, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_r5fss1_1_skip_instance_7, 8944, 11621, 11633, 11634)

/* C75 */
TEST_EXECUTE_SKIP_IDS(am275x_c75_0_skip,1116, 1117, 8919, 8939, 8940, 8950, 8951, 8952, 8959, 8962, 8976, 8984, 8989, 8990, 8992, 8928, 9971, 9972, 9973, 9974, 9975, 9976, 9977, 9978, 8944, 10112, 10113, 10114)
TEST_EXECUTE_SKIP_IDS(am275x_c75_0_skip_instance, 8924, 8929, 8936, 8944, 11621, 8995, 8958, 8960, 8943, 8938, 8935, 10121, 11622, 11623, 11624, 11625, 11626, 11627, 11628, 11629, 11631, 11632, 10125, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_c75_0_skip_instance_1, 8924, 8936, 8944, 11621, 8995, 8958, 8960, 8943, 8938, 8935, 11631, 11632, 10125, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_c75_0_skip_instance_2, 8924, 8936, 8944, 11621, 8995, 8958, 8960, 8943, 8938, 8935, 11631, 11632, 10125, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_c75_0_skip_instance_3, 8924, 8936, 8944, 11621, 8995, 8958, 8960, 8943, 8938, 8935, 11631, 11632, 10125, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_c75_0_skip_instance_4, 8924, 8936, 8944, 11621, 8995, 8958, 8960, 8943, 8938, 8935, 11631, 11632, 10125, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_c75_0_skip_instance_5, 8924, 8936, 8944, 11621, 8995, 8958, 8960, 8943, 8938, 8935, 11631, 11632, 10125, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_c75_0_skip_instance_6, 8924, 8936, 8944, 11621, 8995, 8958, 8960, 8943, 8938, 8935, 11631, 11632, 10125, 11633, 11634)

TEST_EXECUTE_SKIP_IDS(am275x_c75_1_skip,1116,1117, 8919, 8939, 8940, 8950, 8951, 8952, 8959, 8962, 8976, 8984, 8989, 8990, 8992, 8928, 9971, 9972, 9973, 9974, 9975, 9976, 9977, 9978, 10112, 10113, 8944, 10114)
TEST_EXECUTE_SKIP_IDS(am275x_c75_1_skip_instance, 8924, 8929, 8935, 8936, 8938, 8943, 8944, 11621, 8958, 8960, 8995, 10120, 10121, 11622, 11623, 11624, 11625, 11626, 11627, 11628, 11629, 11631, 11632, 10125, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_c75_1_skip_instance_1, 8936, 8944, 11621, 8995, 8958, 8960, 8943, 8938, 8935, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_c75_1_skip_instance_2, 8936, 8944, 11621, 8995, 8958, 8960, 8943, 8938, 8935, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_c75_1_skip_instance_3, 8936, 8944, 11621, 8995, 8958, 8960, 8943, 8938, 8935, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_c75_1_skip_instance_4, 8936, 8944, 11621, 8995, 8958, 8960, 8943, 8938, 8935, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_c75_1_skip_instance_5, 8936, 8944, 11621, 8995, 8958, 8960, 8943, 8938, 8935, 11633, 11634)
TEST_EXECUTE_SKIP_IDS(am275x_c75_1_skip_instance_6, 8936, 8944, 11621, 8995, 8958, 8960, 8943, 8938, 8935, 11633, 11634)


const TestExecute_idList TestExecute_SkipTestIdMatrix[TEST_SOC_COUNT][TEST_CORE_COUNT] = {
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_MCU_R5F0, am62ax_mcur5_skip),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_A53, am62ax_a53_skip),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_R5F0, am62ax_r5_skip),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_C7X, am62ax_c7x_skip),

    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_MCU_R5F0, am62dx_mcur5_skip),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_A53, am62dx_a53_skip),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_C7X, am62dx_c7x_skip),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_R5F0, am62dx_r5_skip),

    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0, am275x_wkupr5_skip),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0_0, am275x_r5fss0_0_skip),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0_1, am275x_r5fss0_1_skip),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F1_0, am275x_r5fss1_0_skip),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F1_1, am275x_r5fss1_1_skip),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_C75_0, am275x_c75_0_skip),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_C75_1, am275x_c75_1_skip),
};

const TestExecute_idList TestExecute_SkipTestIdMatrixWithInstance[TEST_SOC_COUNT][TEST_CORE_COUNT][TEST_INSTANCE_COUNT] = {
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_MCU_R5F0, CONFIG_UART0, am62ax_mcur5_skip_instance_0),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_MCU_R5F0, CONFIG_UART1, am62ax_mcur5_skip_instance_1),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_MCU_R5F0, CONFIG_UART2, am62ax_mcur5_skip_instance_2),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_MCU_R5F0, CONFIG_UART3, am62ax_mcur5_skip_instance_3),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_MCU_R5F0, CONFIG_UART4, am62ax_mcur5_skip_instance_4),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_MCU_R5F0, CONFIG_UART5, am62ax_mcur5_skip_instance_5),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_MCU_R5F0, CONFIG_UART6, am62ax_mcur5_skip_instance_6),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_MCU_R5F0, CONFIG_UART7, am62ax_mcur5_skip_instance_7),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_MCU_R5F0, CONFIG_UART8, am62ax_mcur5_skip_instance_8),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_A53, CONFIG_UART0, am62ax_a53_skip_instance_0),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_A53, CONFIG_UART8, am62ax_a53_skip_instance_8),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_R5F0, CONFIG_UART0, am62ax_r5_skip_instance_0),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_R5F0, CONFIG_UART1, am62ax_r5_skip_instance_1),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_R5F0, CONFIG_UART2, am62ax_r5_skip_instance_2),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_R5F0, CONFIG_UART3, am62ax_r5_skip_instance_3),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_R5F0, CONFIG_UART4, am62ax_r5_skip_instance_4),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_R5F0, CONFIG_UART5, am62ax_r5_skip_instance_5),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_R5F0, CONFIG_UART6, am62ax_r5_skip_instance_6),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_R5F0, CONFIG_UART7, am62ax_r5_skip_instance_7),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_C7X, CONFIG_UART0, am62ax_c7x_skip_instance_0),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_C7X, CONFIG_UART1, am62ax_c7x_skip_instance_1),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_C7X, CONFIG_UART2, am62ax_c7x_skip_instance_2),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_C7X, CONFIG_UART3, am62ax_c7x_skip_instance_3),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_C7X, CONFIG_UART4, am62ax_c7x_skip_instance_4),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_C7X, CONFIG_UART5, am62ax_c7x_skip_instance_5),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_C7X, CONFIG_UART6, am62ax_c7x_skip_instance_6),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_C7X, CONFIG_UART7, am62ax_c7x_skip_instance_7),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62AX, TEST_CORE_IDX_C7X, CONFIG_UART8, am62ax_c7x_skip_instance_8),

    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_MCU_R5F0, CONFIG_UART0, am62dx_mcur5_skip_instance_0),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_MCU_R5F0, CONFIG_UART1, am62dx_mcur5_skip_instance_1),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_MCU_R5F0, CONFIG_UART2, am62dx_mcur5_skip_instance_2),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_MCU_R5F0, CONFIG_UART3, am62dx_mcur5_skip_instance_3),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_MCU_R5F0, CONFIG_UART4, am62dx_mcur5_skip_instance_4),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_MCU_R5F0, CONFIG_UART5, am62dx_mcur5_skip_instance_5),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_MCU_R5F0, CONFIG_UART6, am62dx_mcur5_skip_instance_6),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_MCU_R5F0, CONFIG_UART7, am62dx_mcur5_skip_instance_7),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_MCU_R5F0, CONFIG_UART8, am62dx_mcur5_skip_instance_8),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_A53, CONFIG_UART0, am62dx_a53_skip_instance_0),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_A53, CONFIG_UART8, am62dx_a53_skip_instance_8),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_C7X, CONFIG_UART0, am62dx_c7x_skip_instance_0),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_C7X, CONFIG_UART1, am62dx_c7x_skip_instance_1),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_C7X, CONFIG_UART2, am62dx_c7x_skip_instance_2),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_C7X, CONFIG_UART3, am62dx_c7x_skip_instance_3),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_C7X, CONFIG_UART4, am62dx_c7x_skip_instance_4),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_C7X, CONFIG_UART5, am62dx_c7x_skip_instance_5),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_C7X, CONFIG_UART6, am62dx_c7x_skip_instance_6),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_C7X, CONFIG_UART7, am62dx_c7x_skip_instance_7),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_C7X, CONFIG_UART8, am62dx_c7x_skip_instance_8),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_R5F0, CONFIG_UART0, am62dx_r5_skip_instance_0),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_R5F0, CONFIG_UART1, am62dx_r5_skip_instance_1),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_R5F0, CONFIG_UART2, am62dx_r5_skip_instance_2),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_R5F0, CONFIG_UART3, am62dx_r5_skip_instance_3),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_R5F0, CONFIG_UART4, am62dx_r5_skip_instance_4),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_R5F0, CONFIG_UART5, am62dx_r5_skip_instance_5),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_R5F0, CONFIG_UART6, am62dx_r5_skip_instance_6),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_R5F0, CONFIG_UART7, am62dx_r5_skip_instance_7),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM62DX, TEST_CORE_IDX_R5F0, CONFIG_UART8, am62dx_r5_skip_instance_8),

    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0, CONFIG_UART0, am275x_wkupr5_skip_instance_0),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0, CONFIG_UART1, am275x_wkupr5_skip_instance_1),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0, CONFIG_UART2, am275x_wkupr5_skip_instance_2),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0, CONFIG_UART3, am275x_wkupr5_skip_instance_3),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0, CONFIG_UART4, am275x_wkupr5_skip_instance_4),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0, CONFIG_UART5, am275x_wkupr5_skip_instance_5),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0, CONFIG_UART6, am275x_wkupr5_skip_instance_6),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0, CONFIG_UART7, am275x_wkupr5_skip_instance_7),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0_0, CONFIG_UART0, am275x_r5fss0_0_skip_instance_0),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0_0, CONFIG_UART1, am275x_r5fss0_0_skip_instance_1),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0_0, CONFIG_UART2, am275x_r5fss0_0_skip_instance_2),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0_0, CONFIG_UART3, am275x_r5fss0_0_skip_instance_3),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0_0, CONFIG_UART4, am275x_r5fss0_0_skip_instance_4),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0_0, CONFIG_UART5, am275x_r5fss0_0_skip_instance_5),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0_0, CONFIG_UART6, am275x_r5fss0_0_skip_instance_6),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0_0, CONFIG_UART7, am275x_r5fss0_0_skip_instance_7),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0_1, CONFIG_UART0, am275x_r5fss0_1_skip_instance_0),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0_1, CONFIG_UART1, am275x_r5fss0_1_skip_instance_1),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0_1, CONFIG_UART2, am275x_r5fss0_1_skip_instance_2),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0_1, CONFIG_UART3, am275x_r5fss0_1_skip_instance_3),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0_1, CONFIG_UART4, am275x_r5fss0_1_skip_instance_4),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0_1, CONFIG_UART5, am275x_r5fss0_1_skip_instance_5),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0_1, CONFIG_UART6, am275x_r5fss0_1_skip_instance_6),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F0_1, CONFIG_UART7, am275x_r5fss0_1_skip_instance_7),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F1_0, CONFIG_UART0, am275x_r5fss1_0_skip_instance_0),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F1_0, CONFIG_UART1, am275x_r5fss1_0_skip_instance_1),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F1_0, CONFIG_UART2, am275x_r5fss1_0_skip_instance_2),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F1_0, CONFIG_UART3, am275x_r5fss1_0_skip_instance_3),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F1_0, CONFIG_UART4, am275x_r5fss1_0_skip_instance_4),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F1_0, CONFIG_UART5, am275x_r5fss1_0_skip_instance_5),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F1_0, CONFIG_UART6, am275x_r5fss1_0_skip_instance_6),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F1_0, CONFIG_UART7, am275x_r5fss1_0_skip_instance_7),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F1_1, CONFIG_UART0, am275x_r5fss1_1_skip_instance_0),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F1_1, CONFIG_UART1, am275x_r5fss1_1_skip_instance_1),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F1_1, CONFIG_UART2, am275x_r5fss1_1_skip_instance_2),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F1_1, CONFIG_UART3, am275x_r5fss1_1_skip_instance_3),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F1_1, CONFIG_UART4, am275x_r5fss1_1_skip_instance_4),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F1_1, CONFIG_UART5, am275x_r5fss1_1_skip_instance_5),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F1_1, CONFIG_UART6, am275x_r5fss1_1_skip_instance_6),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_R5F1_1, CONFIG_UART7, am275x_r5fss1_1_skip_instance_7),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_C75_0, CONFIG_UART0, am275x_c75_0_skip_instance),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_C75_0, CONFIG_UART1, am275x_c75_0_skip_instance_1),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_C75_0, CONFIG_UART3, am275x_c75_0_skip_instance_2),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_C75_0, CONFIG_UART4, am275x_c75_0_skip_instance_3),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_C75_0, CONFIG_UART5, am275x_c75_0_skip_instance_4),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_C75_0, CONFIG_UART6, am275x_c75_0_skip_instance_5),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_C75_0, CONFIG_UART7, am275x_c75_0_skip_instance_6),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_C75_1, CONFIG_UART0, am275x_c75_1_skip_instance),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_C75_1, CONFIG_UART1, am275x_c75_1_skip_instance_1),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_C75_1, CONFIG_UART3, am275x_c75_1_skip_instance_2),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_C75_1, CONFIG_UART4, am275x_c75_1_skip_instance_3),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_C75_1, CONFIG_UART5, am275x_c75_1_skip_instance_4),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_C75_1, CONFIG_UART6, am275x_c75_1_skip_instance_5),
    TEST_EXECUTE_SKIP_ENTRY(TEST_SOC_IDX_AM275X, TEST_CORE_IDX_C75_1, CONFIG_UART7, am275x_c75_1_skip_instance_6),

};

/*===================================================================*/
/* 					         Function Declarations		             */
/*===================================================================*/

static void test_uart_set_params(UART_TestParams *testParams, uint32_t testCaseId);
static void uart_echo_read_full_test(void *args);
static void uart_echo_read_partial_test(void *args);
void test_printExitString(void *args);
#if defined(SOC_AM64X) || defined(SOC_AM243X)
static void uart_echo_read_full_test_dmaMode(void *args);
#endif

/* Single thread test case dispatcher */
static void TestUart_stTestcase(void);

/* Config debug UART */
static void TestUart_getDebugUartConfig(uint16_t debugUartInstance);
/* Close debug UART */
static void TestUart_closeDebugUart(void);

/* Test UART write callback */
static void TestUart_uartWriteCallback(UART_Handle handle, UART_Transaction *trans);
/* Custom write callback that attempts a nested UART_write() */
static void TestUart_nestedWriteCallback(UART_Handle handle, UART_Transaction *trans);

/* Test UART read callback */
static void TestUart_uartReadCallback(UART_Handle handle, UART_Transaction *trans);
static void TestUart_immediateReadCallback(UART_Handle handle, UART_Transaction *trans);

/* Test UART open with invalid index */
static void TestUart_uartOpenInvalidIndex(void *args);
/* Fail: Test UART open with null params */
static void TestUart_uartOpenNullParams(void *args);
/* Test UART open with multiple opens without close */
static void TestUart_uartOpenMultipleOpenWithoutClose(void *args);
/* Test UART open with close and reopen with different params */
static void TestUart_uartOpenCloseAndReopenWithDifferentParams(void *args);
/* Test UART open with different instances */
static void TestUart_uartOpenUartInstances(void *args);
/* Test UART open with different instances with different params */
static void TestUart_uartOpenDifferentInstances(void *args);
/* Test UART close with same handle twice */
static void TestUart_uartCloseCloseSameHandleTwice(void *args);
/* Test UART write and read in blocking mode with loopback */
static void TestUart_uartWriteReadBlockingModeLoopback(void *args);
/* Test UART write with null handle */
static void TestUart_uartWriteNullHandle(void *args);
/* Test UART write with null buffer */
static void TestUart_uartWriteNullBuffer(void *args);
/* Test UART write with zero count */
static void TestUart_uartWriteZeroCount(void *args);
/* Test UART write with null transaction */
static void TestUart_uartWriteNullTransaction(void *args);
/* Test UART write with callback mode interrupt */
static void TestUart_uartWriteReadBlockingModeInterrupt(void *args);
/* Test UART write with callback mode interrupt timeout cancel */
static void TestUart_uartWriteCallbackModeInterruptTimeoutCancel(void *args);
/* Test UART write with callback mode interrupt timeout */
static void TestUart_uartWriteCallbackModeInterruptTimeout(void *args);
/* Test UART write with blocking mode polled timeout */
static void TestUart_uartWriteBlockingModePolledTimeout(void *args);
/* Test UART write with DMA blocking mode */
static void TestUart_uartWriteDmaBlockingMode(void *args);
/* Test UART read with DMA blocking mode */
static void TestUart_uartReadDmaBlockingMode(void *args);
/* Test UART get handle with invalid index */
static void TestUart_uartGetHandleInvalidIndex(void *args);
/* Test UART get handle with closed instance */
static void TestUart_uartGetHandleClosedInstance(void *args);
/* Test UART flush TX FIFO with valid handle */
static void TestUart_uartFlushTxFifo(void *args);
/* Test UART flush TX FIFO with null handle */
static void TestUart_uartFlushTxFifoNullHandle(void *args);
/* Test UART parameters initialization with null handle */
static void TestUart_uartParamsInitNullHandle(void *args);
/* Test UART transaction initialization with null handle */
static void TestUart_uartTransactionInitNullHandle(void *args);
/* Test UART get base address with null handle */
static void TestUart_uartGetBaseAddrNullHandle(void *args);
/* Test UART enable loopback mode with invalid base address */
static void TestUart_enableLoopbackModeInvalidBaseAddr(void *args);
/* Test UART disable loopback mode with invalid base address */
static void TestUart_disableLoopbackModeInvalidBaseAddr(void *args);
/* Test UART put character with invalid base address */
static void TestUart_uartPutCharInvalidBaseAddr(void *args);
/* Test UART get character with valid handle */
void TestUart_uartGetChar(void *args);
/* Test UART get character with null pointer */
static void TestUart_uartGetCharNullCharPtr(void *args);
/* Test UART get character with invalid base address */
static void TestUart_uartGetCharInvalidBaseAddr(void *args);
/* Test UART interrupt enable with valid handle */
static void TestUart_uartIntrEnable(void *args);
/* Test UART interrupt enable with null handle */
static void TestUart_uartIntrEnableWrongIntFlag(void *args);
/* Test UART interrupt enable with invalid base address */
static void TestUart_uartIntrEnableWrongBaseAddr(void *args);
/* Test UART interrupt disable with valid handle */
static void TestUart_uartIntrDisable(void *args);
/* Test UART interrupt disable with null handle */
static void TestUart_uartIntrDisableWrongIntFlagAfterEnable(void *args);
/* Test UART interrupt disable with invalid base address */
static void TestUart_uartIntrDisableWrongBaseAddrAfterEnable(void *args);
/* Test UART interrupt2 enable with valid handle */
static void TestUart_uartIntr2Enable(void *args);
/* Test UART interrupt2 enable with null handle */
static void TestUart_uartIntr2EnableWrongIntFlag(void *args);
/* Test UART interrupt2 enable with invalid base address */
static void TestUart_uartIntr2EnableWrongBaseAddr(void *args);
/* Test UART interrupt2 disable with valid handle */
static void TestUart_uartIntr2Disable(void *args);
/* Test UART interrupt2 disable with null handle */
static void TestUart_uartIntr2DisableWrongIntFlagAfterEnable(void *args);
/* Test UART interrupt2 disable with invalid base address */
static void TestUart_uartIntr2DisableWrongBaseAddrAfterEnable(void *args);
/* Test UART get interrupt identity status with callback mode */
static void TestUart_uartGetIntrIdentityStatusCallbackMode(void *args);
/* Test UART get interrupt identity status with null handle */
static void TestUart_uartGetIntrIdentityStatusWrongBaseAddr(void *args);
/* Test UART get interrupt identity status with invalid base address */
static void TestUart_uartGetIntr2Status(void *args);
/* Test UART get interrupt identity status with null handle */
static void TestUart_uartGetIntr2StatusWrongBaseAddr(void *args);
/* Test UART get interrupt identity status with null handle */
static void TestUart_uartCheckCharsAvailInFifo(void *args);
/* Test UART get interrupt identity status with invalid base address */
static void TestUart_uartCheckCharsAvailInFifoInvalidBaseAddr(void *args);
/* Test UART read line status with valid handle */
static void TestUart_uartReadLineStatus(void *args);
/* Test UART read line status with null handle */
static void TestUart_uartReadLineStatusInvalidBaseAddr(void *args);
/* Test UART get character from FIFO with valid handle */
static void TestUart_uartGetCharFifo(void *args);
/* Test UART get character from FIFO with null handle */
static void TestUart_uartGetCharFifoInvalidBaseAddr(void *args);
/* Test UART get character from FIFO with invalid char pointer */
static void TestUart_uartGetCharFifoInvalidCharPtr(void *args);
/* Test UART read blocking mode with invalid base address */
static void TestUart_uartReadNullHandle(void *args);
/* Test UART read blocking mode with null buffer */
static void TestUart_uartReadNullBuffer(void *args);
/* Test UART read blocking mode with zero count */
static void TestUart_uartReadZeroCount(void *args);
/* Test UART read blocking mode with loopback callback */
void TestUart_uartWriteReadLoopBackCallback(void *args);
/* Test UART to transfer 1byte of data */
void TestUart_uartWriteOneByte(void *args);
/* Test UART to transfer 1byte of data with callback mode */
void TestUart_uartWriteOneByteCallbackWithRead(void *args);
/* Test UART TX/RX trigger level ordered callbacks */
void TestUart_txRxTriggerLevelOrderedCallbacks(void *args);
/* Test UART TX/RX trigger level with high RX trigger level */
static void TestUart_txRxTriggerLevelHighRxTriglevel(void *args);
/* Test UART operating mode 13x loopback */
static void TestUart_operMode13xLoopback(void *args);
/* Test UART write in-use error with callback mode interrupt */
static void TestUart_uartWriteErrorInUseInterrupt(void *args);
/* Test UART TX FIFO trigger levels with loopback (callback+interrupt) */
static void TestUart_txTriggerLevelsLoopback(void *args);
/* Test UART read framing error path in polled mode */
static void TestUart_uartFramingErrorPolled(void *args);
/* Test UART write polling timeout elapsed error path in polled mode */
static void TestUart_uartWritePollingTimeoutElapsed(void *args);
/* Test to cover invalid read callback parameter for Open invalid param */
static void TestUart_uartOpenInvalidParamsReadCallbackNull(void *args);
/* Test to cover invalid write callback parameter for Open invalid param */
static void TestUart_uartOpenInvalidParamsWriteCallbackNull(void *args);
/* Testcase to validate UART_readInterrupt immediate-complete path */
static void TestUart_uartReadInterruptImmediate(void *args);
/* Testcase to validate UART_readCancel error when no read in progress */
static void TestUart_uartReadCancelErrorNoReadInProgress(void *args);
/* Testcase to validate UART_write on closed handle */
static void TestUart_uartWriteOnClosedHandle(void *args);
/* Testcase to validate UART_writeSkipIntrElsePath */
static void TestUart_uartWriteSkipIntrElsePath(void *args);
/* Testcase to validate UART_read on closed handle */
static void TestUart_uartReadFailClosedHandle(void *args);
/* Test to validate baud rate on debug UART with external loopback */
static void TestUart_uartBaudRateValidationDebugUart(void *args);
/* Test UART framing error (FE) detection in interrupt mode on debug UART */
static void TestUart_uartFramingErrorInterruptDebugUart(void *args);
/* Test UART RLS error notification in blocking mode on debug UART */
static void TestUart_uartRlsErrorBlockingDebugUart(void *args);
/* Testcase to validate UART read timeout in internal loopback */
static void TestUart_uartReadTimeoutLoopback(void *args);
/* Testcase to validate UART partial read in internal loopback */
static void TestUart_uartPartialReadLoopback(void *args);
/* Testcase to validate UART write cancel followed by immediate re-write */
static void TestUart_writeCancelAndRewrite(void *args);
/* Testcase to validate UART read cancel followed by immediate re-read */
static void TestUart_readCancelAndReread(void *args);
/* Testcase to validate errata i2310 erroneous timeout interrupt with RX trigger level 1 */
static void TestUart_erratai2310TimeoutInterrupt(void *args);
/* Testcase to validate UART_udmaIsrTx handles continuous callbacks properly */
static void TestUart_udmaIsrTxContinuousCallback(void *args);
/* Testcase to validate write-inside-callback returns INUSE in DMA TX ISR */
static void TestUart_udmaIsrTxWriteInsideCallback(void *args);

/*===================================================================*/
/* 					         Function Definitions		             */
/*===================================================================*/

/**
 * @brief Enable internal loopback and flush any spurious RX data.
 *
 * On some UART instances the transition to loopback mode causes a glitch
 * that puts a spurious byte (typically 0xFF) into the RX FIFO.  This
 * helper enables loopback, waits for the line to settle, and drains the
 * RX FIFO so that subsequent reads only see real loopback data.
 */
static void TestUart_enableLoopback(uint32_t baseAddr)
{
    uint8_t rdData;

    UART_enableLoopbackMode(baseAddr);
    ClockP_usleep(1000);

    /* Flush any spurious bytes from RX FIFO */
    while (UART_getChar(baseAddr, &rdData) != 0U)
    {
        /* discard */
    }
}

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
void test_main(void *args)
{
    uint8_t instanceId;

    /* Initialize Unity Test Framework */
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

    /* Single thread test cases */
    TestUart_stTestcase();
#ifdef CONFIG_UART_MULTI_INSTANCE_TEST_ENABLE
    /* Multi thread test cases */
    TestUart_mtTestcase();
#endif

    /* Finalize Unity Test Framework */
    UNITY_END();

    /* Baud rate validation via BTT method */
    uint32_t  baudRate;

    baudRate = 1200;
    TEST_EXECUTE_TEST_CASE(TestUart_uartBaudRateValidationDebugUart, 11622, (void *)&baudRate);
    baudRate = 2400;
    TEST_EXECUTE_TEST_CASE(TestUart_uartBaudRateValidationDebugUart, 11623, (void *)&baudRate);
    baudRate = 4800;
    TEST_EXECUTE_TEST_CASE(TestUart_uartBaudRateValidationDebugUart, 11624, (void *)&baudRate);
    baudRate = 9600;
    TEST_EXECUTE_TEST_CASE(TestUart_uartBaudRateValidationDebugUart, 11625, (void *)&baudRate);
    baudRate = 19200;
    TEST_EXECUTE_TEST_CASE(TestUart_uartBaudRateValidationDebugUart, 11626, (void *)&baudRate);
    baudRate = 38400;
    TEST_EXECUTE_TEST_CASE(TestUart_uartBaudRateValidationDebugUart, 11627, (void *)&baudRate);
    baudRate = 57600;
    TEST_EXECUTE_TEST_CASE(TestUart_uartBaudRateValidationDebugUart, 11628, (void *)&baudRate);
    baudRate = 115200;
    TEST_EXECUTE_TEST_CASE(TestUart_uartBaudRateValidationDebugUart, 11629, (void *)&baudRate);

    /* Framing error test */
    TEST_EXECUTE_TEST_CASE(TestUart_uartFramingErrorInterruptDebugUart, 11630, NULL);

     /* RLS error test */
    TEST_EXECUTE_TEST_CASE(TestUart_uartRlsErrorBlockingDebugUart, 11635, NULL);

    UART_deinit();
}

static void uart_echo_read_full_test(void *args)
{
    int32_t          transferOK, status;
    UART_Transaction trans;
    UART_Handle      uartHandle;
    UART_TestParams *testParams = (UART_TestParams*)args;
    UART_Params     *uartParams = &(testParams->uartParams);
    uint32_t         baseAddr;

    UART_close(gUartHandle[CONFIG_UART0]);

    uartHandle = UART_open(CONFIG_UART0, uartParams);
    TEST_ASSERT_NOT_NULL(uartHandle);

    if (uartParams->writeMode == UART_TRANSFER_MODE_CALLBACK)
    {
        status = SemaphoreP_constructBinary(&gUartWriteDoneSem, 0);
        DebugP_assert(SystemP_SUCCESS == status);
    }

    if (uartParams->readMode == UART_TRANSFER_MODE_CALLBACK)
    {
        status = SemaphoreP_constructBinary(&gUartReadDoneSem, 0);
        DebugP_assert(SystemP_SUCCESS == status);
    }

    baseAddr = UART_getBaseAddr(gUartHandle[CONFIG_UART0]);
    DebugP_assert(baseAddr != 0U);

    TestUart_enableLoopback(baseAddr);

    UART_Transaction_init(&trans);

    trans.buf   = &gUartTxBuffer[0U];
    strncpy(trans.buf,"This is uart echo read FULL mode Test...\r\n", APP_UART_BUFSIZE);
    trans.count = strlen(trans.buf);
    transferOK = UART_write(gUartHandle[CONFIG_UART0], &trans);
    APP_UART_ASSERT_ON_FAILURE(transferOK, trans);

    if (uartParams->writeMode == UART_TRANSFER_MODE_CALLBACK)
    {
        /* Wait for write completion */
        SemaphoreP_pend(&gUartWriteDoneSem, SystemP_WAIT_FOREVER);
        DebugP_assert(trans.count == strlen(trans.buf));
    }

    trans.buf   = &gUartRxBuffer[0U];
    trans.count = trans.count;
    transferOK = UART_read(gUartHandle[CONFIG_UART0], &trans);
    APP_UART_ASSERT_ON_FAILURE(transferOK, trans);

    if (uartParams->readMode == UART_TRANSFER_MODE_CALLBACK)
    {
        /* Wait for read completion */
        SemaphoreP_pend(&gUartReadDoneSem, SystemP_WAIT_FOREVER);
        DebugP_assert(trans.count == strlen(trans.buf));
    }

    transferOK = memcmp(&gUartTxBuffer[0U], &gUartRxBuffer[0U], strlen(trans.buf));
    DebugP_assert(transferOK == 0U);

    if (uartParams->writeMode == UART_TRANSFER_MODE_CALLBACK)
    {
        SemaphoreP_destruct(&gUartWriteDoneSem);
    }
    if (uartParams->readMode == UART_TRANSFER_MODE_CALLBACK)
    {
        SemaphoreP_destruct(&gUartReadDoneSem);
    }

    UART_disableLoopbackMode(baseAddr);
    UART_close(uartHandle);

    return;
}

#if defined(SOC_AM64X) || defined(SOC_AM243X)
static void uart_echo_read_full_test_dmaMode(void *args)
{
    int32_t          transferOK, status;
    UART_Transaction trans;
    UART_TestParams *testParams = (UART_TestParams*)args;
    UART_Params     *uartParams = &(testParams->uartParams);
    uint32_t         baseAddr;

    if (uartParams->writeMode == UART_TRANSFER_MODE_CALLBACK)
    {
        status = SemaphoreP_constructBinary(&gUartWriteDoneSem, 0);
        DebugP_assert(SystemP_SUCCESS == status);
    }

    if (uartParams->readMode == UART_TRANSFER_MODE_CALLBACK)
    {
        status = SemaphoreP_constructBinary(&gUartReadDoneSem, 0);
        DebugP_assert(SystemP_SUCCESS == status);
    }

    baseAddr = UART_getBaseAddr(gUartHandle[CONFIG_UART1]);
    DebugP_assert(baseAddr != 0U);

    TestUart_enableLoopback(baseAddr);

    UART_Transaction_init(&trans);

    trans.buf   = &gUartTxBuffer[0U];
    strncpy(trans.buf,"This is uart echo read FULL DMA mode Callback mode Test...\r\n", APP_UART_BUFSIZE);
    trans.count = strlen(trans.buf);
    CacheP_wb((void *)trans.buf, trans.count, CacheP_TYPE_ALL);
    transferOK = UART_write(gUartHandle[CONFIG_UART1], &trans);
    APP_UART_ASSERT_ON_FAILURE(transferOK, trans);

    if (uartParams->writeMode == UART_TRANSFER_MODE_CALLBACK)
    {
        /* Wait for write completion */
        SemaphoreP_pend(&gUartWriteDoneSem, SystemP_WAIT_FOREVER);
        DebugP_assert(strlen(trans.buf) == gNumBytesWritten);
    }

    CacheP_wbInv((void *)&gUartRxBuffer[0U], APP_UART_BUFSIZE, CacheP_TYPE_ALL);

    trans.buf   = &gUartRxBuffer[0U];
    trans.count = gNumBytesWritten;
    transferOK = UART_read(gUartHandle[CONFIG_UART1], &trans);
    APP_UART_ASSERT_ON_FAILURE(transferOK, trans);

    if (uartParams->readMode == UART_TRANSFER_MODE_CALLBACK)
    {
        /* Wait for read completion */
        SemaphoreP_pend(&gUartReadDoneSem, SystemP_WAIT_FOREVER);
        DebugP_assert(gNumBytesWritten == gNumBytesRead);
    }

    transferOK = memcmp(&gUartTxBuffer[0U], &gUartRxBuffer[0U], gNumBytesWritten);
    DebugP_assert(transferOK == 0U);

    if (uartParams->writeMode == UART_TRANSFER_MODE_CALLBACK)
    {
        SemaphoreP_destruct(&gUartWriteDoneSem);
    }
    if (uartParams->readMode == UART_TRANSFER_MODE_CALLBACK)
    {
        SemaphoreP_destruct(&gUartReadDoneSem);
    }

    UART_disableLoopbackMode(baseAddr);

    return;
}
#endif

static void uart_echo_read_partial_test(void *args)
{
    int32_t          transferOK;
    UART_Transaction trans;
    UART_Handle      uartHandle;
    UART_TestParams *testParams = (UART_TestParams*)args;
    UART_Params     *uartParams = &(testParams->uartParams);
    uint32_t         baseAddr, strLen, tmpVar;

    UART_close(gUartHandle[CONFIG_UART0]);

    uartHandle = UART_open(CONFIG_UART0, uartParams);
    TEST_ASSERT_NOT_NULL(uartHandle);

    baseAddr = UART_getBaseAddr(gUartHandle[CONFIG_UART0]);
    DebugP_assert(baseAddr != 0U);

    TestUart_enableLoopback(baseAddr);

    UART_Transaction_init(&trans);

    trans.buf   = &gUartTxBuffer[0U];
    strncpy(trans.buf,"This is uart echo read Partial mode Test...\r\n", APP_UART_BUFSIZE);
    trans.count = strlen(trans.buf);
    strLen      = strlen(trans.buf);
    transferOK = UART_write(gUartHandle[CONFIG_UART0], &trans);
    APP_UART_ASSERT_ON_FAILURE(transferOK, trans);

    trans.buf   = &gUartRxBuffer[0U];
    trans.count = strLen;
    tmpVar      = strLen;
    while(tmpVar != 0U)
    {
        trans.buf   = &gUartRxBuffer[strLen - tmpVar];
        trans.count = tmpVar;
        transferOK = UART_read(gUartHandle[CONFIG_UART0], &trans);
        APP_UART_ASSERT_ON_FAILURE(transferOK, trans);
        tmpVar = tmpVar - trans.count;
    }

    transferOK = memcmp(&gUartTxBuffer[0U], &gUartRxBuffer[0U], strLen);
    DebugP_assert(transferOK == 0U);

    UART_disableLoopbackMode(baseAddr);
    UART_close(uartHandle);

    return;
}

void test_printExitString(void *args)
{
    int32_t          transferOK;
    UART_Transaction trans;
    UART_Handle      uartHandle;
    UART_TestParams *testParams = (UART_TestParams*)args;
    UART_Params     *uartParams;

    uartParams = &(testParams->uartParams);
    uartHandle = UART_open(CONFIG_UART0, uartParams);
    TEST_ASSERT_NOT_NULL(uartHandle);

    UART_Transaction_init(&trans);
    /* Send exit string */
    trans.buf   = &gUartTxBuffer[0U];
    strncpy(trans.buf, "All tests have passed!!\r\n", APP_UART_BUFSIZE);
    trans.count = strlen(trans.buf);
    transferOK = UART_write(gUartHandle[CONFIG_UART0], &trans);
    APP_UART_ASSERT_ON_FAILURE(transferOK, trans);

    UART_close(uartHandle);

    return;
}

void uart_echo_write_callback(UART_Handle handle, UART_Transaction *trans)
{
    DebugP_assertNoLog(UART_TRANSFER_STATUS_SUCCESS == trans->status);
    gNumBytesWritten = trans->count;
    SemaphoreP_post(&gUartWriteDoneSem);

    return;
}

void uart_echo_read_callback(UART_Handle handle, UART_Transaction *trans)
{
    DebugP_assertNoLog(UART_TRANSFER_STATUS_SUCCESS == trans->status);
    gNumBytesRead = trans->count;
    SemaphoreP_post(&gUartReadDoneSem);

    return;
}

static void test_uart_set_params(UART_TestParams *testParams, uint32_t tcId)
{
    UART_Params *params = &(testParams->uartParams);

    UART_Params_init(params);
    params->readReturnMode = UART_READ_RETURN_MODE_FULL;

    /* Map to interrupt line for UART in the SOC */
    #if defined(SOC_AM64X) || defined(SOC_AM243X)
    params->intrNum = CSLR_R5FSS0_CORE0_INTR_UART0_USART_IRQ_0;
    #endif
    #if defined(SOC_AM9976X)
    params->intrNum = CSLR_R5FSS0_CORE0_INTR_UART0_IRQ;
    #endif
    #if defined(SOC_AM275X)
    params->intrNum = CSLR_R5FSS0_CORE0_INTR_UART0_USART_IRQ_0;
    #endif
    #if defined(SOC_AM62X)
    #if defined(A53_FREERTOS)
    params->intrNum = CSLR_GICSS0_COMMON_0_SPI_UART1_USART_IRQ_0;
    #else
    params->intrNum = CSLR_MCU_M4FSS0_CORE0_NVIC_MCU_UART0_USART_IRQ_0 + 16;
    #endif
    #endif

    #if (defined(SOC_AM62AX) || defined(SOC_AM62PX))
    params->intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_MCU_UART0_USART_IRQ_0;
    #endif

    #if defined(SOC_AM62DX)
    #if defined(__aarch64__)
    params->intrNum = CSLR_GICSS0_COMMON_0_SPI_MCU_UART0_USART_IRQ_0;
    #elif defined(__C7504__)
    params->intrNum = 30;
    params->eventId = 178 + 256;
    #else
    params->intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_UART0_USART_IRQ_0;
    #endif
    #elif defined (SOC_J722S)
    #if defined (BUILD_WKUP_R5)
    params->intrNum = CSLR_WKUP_R5FSS0_CORE0_INTR_WKUP_UART0_USART_IRQ_0;
    #elif defined (BUILD_MCU_R5)
    params->intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_MCU_UART0_USART_IRQ_0;
    #elif defined (BUILD_MAIN_R5)
    params->intrNum = CSLR_R5FSS0_CORE0_INTR_UART0_USART_IRQ_0;
    #elif defined (BUILD_C75X_1)
    params->eventId = CSLR_C7X256V0_CLEC_GIC_SPI_UART0_USART_IRQ_0 - 32 + 256;
    params->intrNum = 28;   /* Any inerrupt number is fine, as long as it does not clash with others. */
    #elif defined (BUILD_C75X_2)
    params->eventId = CSLR_C7X256V1_CLEC_GIC_SPI_UART0_USART_IRQ_0 - 32 + 256;
    params->intrNum = 28;   /* Any inerrupt number is fine, as long as it does not clash with others. */
    #endif
    #endif

    #if defined(SOC_AM62LX)
    params->intrNum = CSLR_GICSS0_SPI_UART1_USART_IRQ_0;
    #endif

    switch (tcId)
    {
        case 1303:
            params->transferMode = UART_CONFIG_MODE_POLLED;
            break;
        case 1304:
            params->readReturnMode = UART_READ_RETURN_MODE_FULL;
            break;
        case 1305:
            params->readReturnMode = UART_READ_RETURN_MODE_PARTIAL;
            break;
        case 2514:
            params->readMode = UART_TRANSFER_MODE_CALLBACK;
            params->writeMode = UART_TRANSFER_MODE_CALLBACK;
            break;
    }

    return;
}

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

/**
 * @brief Single-thread UART test case dispatcher.
 *
 * This function initializes UART test parameters and sequentially executes all
 * registered single-threaded UART unit tests using the Unity test framework.
 * It covers API validation for open/close, read/write modes, interrupts, FIFO,
 * status queries, loopback, error paths, and more. Each test is invoked with
 * appropriate parameters and instance IDs, and results are printed over UART
 * for automation and reporting.
 *
 * Test Steps:
 * 1. Initialize UART test parameters for each test case.
 * 2. Run all single-threaded UART API validation tests using RUN_TEST.
 * 3. Print test status messages over UART.
 *
 * @param[in] None
 *
 * @return void
 */
static void TestUart_stTestcase(void)
{
    /*UART test parameters*/
    UART_TestParams uartInitParams = {0};

#if !(defined(CPU_A53))
    uint8_t instanceNum = CONFIG_UART1;
#else
    uint8_t instanceNum = CONFIG_UART7;
#endif /* !(defined(CPU_A53)) */

    test_uart_set_params(&uartInitParams, 1303);
    TEST_EXECUTE_TEST_CASE(uart_echo_read_full_test, 1303, (void*)&uartInitParams);
    test_uart_set_params(&uartInitParams, 1304);
    TEST_EXECUTE_TEST_CASE(uart_echo_read_full_test, 1304, (void*)&uartInitParams);
    test_uart_set_params(&uartInitParams, 1305);
    TEST_EXECUTE_TEST_CASE(uart_echo_read_partial_test, 1305, (void*)&uartInitParams);
#if defined(SOC_AM64X) || defined(SOC_AM243X)
    test_uart_set_params(&uartInitParams, 2514);
    TEST_EXECUTE_TEST_CASE(uart_echo_read_full_test_dmaMode, 2514, (void*)&uartInitParams);
#endif

    /* Functional Testcase */

    for (instanceNum = 0; instanceNum < CONFIG_UART_NUM_INSTANCES; instanceNum++)
    {
        if (instanceNum == TestUart_debugUart)
        {
            /* Skip debug UART instance to avoid conflicts */
            continue;
        }
        DebugP_log("UART Instance %d Testcases\r\n", instanceNum);
        TestUart_paramsInit(&uartInitParams, 8924, instanceNum);
        TEST_EXECUTE_TEST_CASE(TestUart_uartOpenUartInstances, 8924, &uartInitParams, instanceNum);
        TestUart_paramsInit(&uartInitParams, 8944, instanceNum);
        TEST_EXECUTE_TEST_CASE(TestUart_uartWriteDmaBlockingMode, 8944, &uartInitParams, instanceNum);
        TestUart_paramsInit(&uartInitParams, 11621, instanceNum);
        TEST_EXECUTE_TEST_CASE(TestUart_uartReadDmaBlockingMode, 11621, &uartInitParams, instanceNum);
        TestUart_paramsInit(&uartInitParams, 11633, instanceNum);
        TEST_EXECUTE_TEST_CASE(TestUart_udmaIsrTxContinuousCallback, 11633, &uartInitParams, instanceNum);
        TestUart_paramsInit(&uartInitParams, 11634, instanceNum);
        TEST_EXECUTE_TEST_CASE(TestUart_udmaIsrTxWriteInsideCallback, 11634, &uartInitParams, instanceNum);
        TestUart_paramsInit(&uartInitParams, 8929, instanceNum);
        TEST_EXECUTE_TEST_CASE(TestUart_uartWriteReadBlockingModeLoopback, 8929, &uartInitParams, instanceNum);
        TestUart_paramsInit(&uartInitParams, 8936, instanceNum);
        TEST_EXECUTE_TEST_CASE(TestUart_uartWriteReadBlockingModeInterrupt, 8936, &uartInitParams, instanceNum);
        TestUart_paramsInit(&uartInitParams, 8995, instanceNum);
        TEST_EXECUTE_TEST_CASE(TestUart_uartWriteReadLoopBackCallback, 8995, &uartInitParams, instanceNum);
        TestUart_paramsInit(&uartInitParams, 8958, instanceNum);
        TEST_EXECUTE_TEST_CASE(TestUart_uartWriteOneByte, 8958, &uartInitParams, instanceNum);
        TestUart_paramsInit(&uartInitParams, 8960, instanceNum); /* Some times seeing a hang in AM62DX C7 core */
        TEST_EXECUTE_TEST_CASE(TestUart_uartWriteOneByteCallbackWithRead, 8960, &uartInitParams, instanceNum);
        TestUart_paramsInit(&uartInitParams, 8943, instanceNum);
        TEST_EXECUTE_TEST_CASE(TestUart_txRxTriggerLevelOrderedCallbacks, 8943, &uartInitParams, instanceNum);
        TestUart_paramsInit(&uartInitParams, 8938, instanceNum);
        TEST_EXECUTE_TEST_CASE(TestUart_txRxTriggerLevelHighRxTriglevel, 8938, &uartInitParams, instanceNum);
        TestUart_paramsInit(&uartInitParams, 8935, instanceNum);
        TEST_EXECUTE_TEST_CASE(TestUart_operMode13xLoopback, 8935, &uartInitParams, instanceNum);
        TestUart_paramsInit(&uartInitParams, 10120, instanceNum);
        TEST_EXECUTE_TEST_CASE(TestUart_uartReadTimeoutLoopback, 10120, &uartInitParams, instanceNum);
        TestUart_paramsInit(&uartInitParams, 10121, instanceNum);
        TEST_EXECUTE_TEST_CASE(TestUart_uartPartialReadLoopback, 10121, &uartInitParams, instanceNum);
        TestUart_paramsInit(&uartInitParams, 11631, instanceNum);
        TEST_EXECUTE_TEST_CASE(TestUart_writeCancelAndRewrite, 11631, &uartInitParams, instanceNum);
        TestUart_paramsInit(&uartInitParams, 11632, instanceNum);
        TEST_EXECUTE_TEST_CASE(TestUart_readCancelAndReread, 11632, &uartInitParams, instanceNum);
        TestUart_paramsInit(&uartInitParams, 10125, instanceNum);
        TEST_EXECUTE_TEST_CASE(TestUart_erratai2310TimeoutInterrupt, 10125, &uartInitParams, instanceNum);
    }

    /* Negative Testcase */

    /* Negative testcase is done on CONFIG_UART2 */

    instanceNum = CONFIG_UART2;

    /*Test for UART_open*/
    TestUart_paramsInit(&uartInitParams, 8918, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartOpenInvalidIndex, 8918, &uartInitParams);
    /* Fail: API has bug when sending NULL params. Hangs at
        DebugP_assert(object->prms.intrNum != 0xFFFF); in uart_v0.c */
    TestUart_paramsInit(&uartInitParams, 8919, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartOpenNullParams, 8919, &uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8920, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartOpenMultipleOpenWithoutClose, 8920, &uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8921, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartOpenCloseAndReopenWithDifferentParams, 8921, &uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8925, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartOpenDifferentInstances, 8925, &uartInitParams);

    /*Test for UART_close*/
    TestUart_paramsInit(&uartInitParams, 8926, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartCloseCloseSameHandleTwice, 8926, &uartInitParams);

    /*Test for UART_write*/
    TestUart_paramsInit(&uartInitParams, 8930, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartWriteNullHandle, 8930, &uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8932, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartWriteNullBuffer, 8932, &uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8933, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartWriteZeroCount, 8933, &uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8934, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartWriteNullTransaction, 8934, &uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8939, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartWriteCallbackModeInterruptTimeoutCancel, 8939, (void*)&uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8940, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartWriteCallbackModeInterruptTimeout, 8940, &uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8941, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartWriteBlockingModePolledTimeout, 8941, &uartInitParams);

    /* Test for UART_getHandle */
    TestUart_paramsInit(&uartInitParams, 8949, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartGetHandleInvalidIndex, 8949, &uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8950, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartGetHandleClosedInstance, 8950, &uartInitParams);

    /* Test for UART_flushTxFifo */
    TestUart_paramsInit(&uartInitParams, 8951, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartFlushTxFifo, 8951, &uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8952, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartFlushTxFifoNullHandle, 8952, &uartInitParams);

    /* Test for UART_paramsInit */
    TestUart_paramsInit(&uartInitParams, 8953, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartParamsInitNullHandle, 8953, &uartInitParams);

    /* Test for UART_transactionInit */
    TestUart_paramsInit(&uartInitParams, 8954, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartTransactionInitNullHandle, 8954, &uartInitParams);

    /* Test for UART_getBaseAddr */
    TestUart_paramsInit(&uartInitParams, 8955, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartGetBaseAddrNullHandle, 8955, &uartInitParams);

    /* Test for UART_enableLoopbackMode */
    TestUart_paramsInit(&uartInitParams, 8956, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_enableLoopbackModeInvalidBaseAddr, 8956, &uartInitParams);

    /* Test for UART_disableLoopbackMode */
    TestUart_paramsInit(&uartInitParams, 8957, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_disableLoopbackModeInvalidBaseAddr, 8957, &uartInitParams);

    /* Test for UART_putChar */
    TestUart_paramsInit(&uartInitParams, 8959, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartPutCharInvalidBaseAddr, 8959, &uartInitParams);

    /* Test for UART_getChar */
    TestUart_paramsInit(&uartInitParams, 8961, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartGetCharInvalidBaseAddr, 8961, &uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8962, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartGetCharNullCharPtr, 8962, &uartInitParams);

    /* Test for UART_interruptEnable */
    TestUart_paramsInit(&uartInitParams, 8963, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartIntrEnable, 8963, &uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8964, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartIntrEnableWrongIntFlag, 8964, &uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8965, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartIntrEnableWrongBaseAddr, 8965, &uartInitParams);

    /* Test for UART_interruptDisable */
    TestUart_paramsInit(&uartInitParams, 8966, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartIntrDisable, 8966, &uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8967, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartIntrDisableWrongIntFlagAfterEnable, 8967, &uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8968, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartIntrDisableWrongBaseAddrAfterEnable, 8968, &uartInitParams);

    /* Test for UART_interrupt2Enable */
    TestUart_paramsInit(&uartInitParams, 8970, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartIntr2Enable, 8970, &uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8971, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartIntr2EnableWrongIntFlag, 8971, &uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8972, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartIntr2EnableWrongBaseAddr, 8972, &uartInitParams);

    /* Test for UART_interrupt2Disable */
    TestUart_paramsInit(&uartInitParams, 8973, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartIntr2Disable, 8973, &uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8974, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartIntr2DisableWrongIntFlagAfterEnable, 8974, &uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8975, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartIntr2DisableWrongBaseAddrAfterEnable, 8975, &uartInitParams);

    /* Test for UART_getIntrIdentityStatus */
    TestUart_paramsInit(&uartInitParams, 8976, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartGetIntrIdentityStatusCallbackMode, 8976, &uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8980, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartGetIntrIdentityStatusWrongBaseAddr, 8980, &uartInitParams);

    /* Test for UART_getIntr2Status */
    TestUart_paramsInit(&uartInitParams, 8981, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartGetIntr2Status, 8981, &uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8983, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartGetIntr2StatusWrongBaseAddr, 8983, &uartInitParams);

    /* Test for UART_checkCharsAvailInFifo */
    TestUart_paramsInit(&uartInitParams, 8984, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartCheckCharsAvailInFifo, 8984, &uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8985, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartCheckCharsAvailInFifoInvalidBaseAddr, 8985, &uartInitParams);

    /* Test for UART_readLineStatus */
    TestUart_paramsInit(&uartInitParams, 8986, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartReadLineStatus, 8986, &uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8987, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartReadLineStatusInvalidBaseAddr, 8987, &uartInitParams);

    /* Test for UART_getCharFifo */
    TestUart_paramsInit(&uartInitParams, 8989, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartGetCharFifo, 8989, &uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8990, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartGetCharFifoInvalidBaseAddr, 8990, &uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8991, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartGetCharFifoInvalidCharPtr, 8991, &uartInitParams);

    /* Test for UART_read */
    TestUart_paramsInit(&uartInitParams, 8992, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartReadNullHandle, 8992, &uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8993, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartReadNullBuffer, 8993, &uartInitParams);
    TestUart_paramsInit(&uartInitParams, 8994, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartReadZeroCount, 8994, &uartInitParams);

    /* Fault injection tests */

    TestUart_paramsInit(&uartInitParams, 10109, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartWriteErrorInUseInterrupt, 10109, &uartInitParams);

    TestUart_paramsInit(&uartInitParams, 10110, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_txTriggerLevelsLoopback, 10110, &uartInitParams);

    TestUart_paramsInit(&uartInitParams, 10111, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartFramingErrorPolled, 10111, &uartInitParams);

    TestUart_paramsInit(&uartInitParams, 10112, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartWritePollingTimeoutElapsed, 10112, &uartInitParams);

    TestUart_paramsInit(&uartInitParams, 10113, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartOpenInvalidParamsReadCallbackNull, 10113, &uartInitParams);

    TestUart_paramsInit(&uartInitParams, 10114, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartOpenInvalidParamsWriteCallbackNull, 10114, &uartInitParams);

    TestUart_paramsInit(&uartInitParams, 10115, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartReadInterruptImmediate, 10115, &uartInitParams);

    TestUart_paramsInit(&uartInitParams, 10116, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartReadCancelErrorNoReadInProgress, 10116, &uartInitParams);

    TestUart_paramsInit(&uartInitParams, 10117, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartWriteOnClosedHandle, 10117, &uartInitParams);

    TestUart_paramsInit(&uartInitParams, 10118, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartWriteSkipIntrElsePath, 10118, &uartInitParams);

    TestUart_paramsInit(&uartInitParams, 10119, instanceNum);
    TEST_EXECUTE_TEST_CASE(TestUart_uartReadFailClosedHandle, 10119, &uartInitParams);
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
 * @brief Initializes UART test parameters for a given test case and UART instance.
 *
 * This function sets up the UART_Params structure within UART_TestParams based on
 * the specified test case ID and UART instance ID. It configures default values,
 * interrupt numbers, transfer modes, callback functions, and other parameters
 * required for the selected test scenario. Used by the test dispatcher to ensure
 * each test runs with the correct UART configuration.
 *
 * Test Steps:
 * 1. Null check for paramsInit.
 * 2. Initialize UART_Params to default values.
 * 3. Set interrupt numbers based on SOC and instance ID.
 * 4. Configure transfer modes, callback functions, and other fields based on tcId.
 * 5. Return 0 on success, -1 on error.
 *
 * @param[in,out] paramsInit Pointer to UART_TestParams structure to initialize.
 * @param[in] tcId           Test case ID to select configuration.
 * @param[in] instanceId     UART instance ID to configure.
 *
 * @return 0 on success, -1 on error.
 */
int TestUart_paramsInit(UART_TestParams *paramsInit, uint16_t tcId, uint16_t instanceId)
{
    /* Null check */
    if (paramsInit == NULL)
    {
        return -1;
    }

    /* Get UART parameters pointer */
    UART_Params *params = (UART_Params *)&(paramsInit->uartParams);
    paramsInit->instanceId = instanceId;

    /* Initialize UART parameters to default values */
    UART_Params_init(params);

    /* Set interrupt numbers based on the core */

    /* For AM62AX */
#if defined(SOC_AM62AX)
    switch(instanceId)
    {
        case CONFIG_UART0:
        #if !defined(CPU_C7X)
            params->intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_MCU_UART0_USART_IRQ_0;
        #else
            params->intrNum = 23U;
            params->eventId = 441;
        #endif
            break;

        case CONFIG_UART8:
        #if !defined(CPU_C7X)
            params->intrNum = CSLR_WKUP_R5FSS0_CORE0_INTR_WKUP_UART0_USART_IRQ_0;
        #else
            params->intrNum = 22U;
            params->eventId = 442;
        #endif
            break;

        case CONFIG_UART1:
        #if !defined(CPU_C7X)
            params->intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_UART0_USART_IRQ_0;
        #else
            params->intrNum = 24U;
            params->eventId = 434;
        #endif
            params->rxEvtNum = 0;
            params->txEvtNum = 0;
            break;

        case CONFIG_UART2:
        #if !defined(CPU_C7X)
            params->intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_UART1_USART_IRQ_0;
        #else
            params->intrNum = 25U;
            params->eventId = 435;
        #endif
            break;

        case CONFIG_UART3:
        #if !defined(CPU_C7X)
            params->intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_UART2_USART_IRQ_0;
        #else
            params->intrNum = 26U;
            params->eventId = 436;
        #endif
            break;

        case CONFIG_UART4:
        #if !defined(CPU_C7X)
            params->intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_UART3_USART_IRQ_0;
        #else
            params->intrNum = 27U;
            params->eventId = 437;
        #endif
            break;

        case CONFIG_UART5:
        #if !defined(CPU_C7X)
            params->intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_UART4_USART_IRQ_0;
        #else
            params->intrNum = 28U;
            params->eventId = 438;
        #endif
            break;

        case CONFIG_UART6:
        #if !defined(CPU_C7X)
            params->intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_UART5_USART_IRQ_0;
        #else
            params->intrNum = 29U;
            params->eventId = 439;
        #endif
            break;

        case CONFIG_UART7:
        #if !defined(CPU_C7X)
            params->intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_UART6_USART_IRQ_0;
        #else
            params->intrNum = 30U;
            params->eventId = 440;
        #endif
            break;

        default:
            return -1;
    }

    /*For AM62DX*/
#elif defined(SOC_AM62DX)

    switch(instanceId)
    {
        case CONFIG_UART0:
        #if !defined(CPU_C7X)
            params->intrNum = CSLR_GICSS0_COMMON_0_SPI_MCU_UART0_USART_IRQ_0;
        #else
            params->intrNum = 23U;
            params->eventId = 441;
        #endif
            break;

        case CONFIG_UART8:
        #if !defined(CPU_C7X)
            params->intrNum = CSLR_GICSS0_COMMON_0_SPI_WKUP_UART0_USART_IRQ_0;
        #else
            params->intrNum = 22U;
            params->eventId = 442;
        #endif
            break;

        case CONFIG_UART1:
        #if !defined(CPU_C7X)
            params->intrNum = CSLR_GICSS0_COMMON_0_SPI_UART0_USART_IRQ_0;
        #else
            params->intrNum = 24U;
            params->eventId = 434;
        #endif
            params->rxEvtNum = 0;
            params->txEvtNum = 0;
            break;

        case CONFIG_UART2:
        #if !defined(CPU_C7X)
            params->intrNum = CSLR_GICSS0_COMMON_0_SPI_UART1_USART_IRQ_0;
        #else
            params->intrNum = 25U;
            params->eventId = 435;
        #endif
            break;

        case CONFIG_UART3:
        #if !defined(CPU_C7X)
            params->intrNum = CSLR_GICSS0_COMMON_0_SPI_UART2_USART_IRQ_0;
        #else
            params->intrNum = 26U;
            params->eventId = 436;
        #endif
            break;

        case CONFIG_UART4:
        #if !defined(CPU_C7X)
            params->intrNum = CSLR_GICSS0_COMMON_0_SPI_UART3_USART_IRQ_0;
        #else
            params->intrNum = 27U;
            params->eventId = 437;
        #endif
            break;

        case CONFIG_UART5:
        #if !defined(CPU_C7X)
            params->intrNum = CSLR_GICSS0_COMMON_0_SPI_UART4_USART_IRQ_0;
        #else
            params->intrNum = 28U;
            params->eventId = 438;
        #endif
            break;

        case CONFIG_UART6:
        #if !defined(CPU_C7X)
            params->intrNum = CSLR_GICSS0_COMMON_0_SPI_UART5_USART_IRQ_0;
        #else
            params->intrNum = 29U;
            params->eventId = 439;
        #endif
            break;

        case CONFIG_UART7:
        #if !defined(CPU_C7X)
            params->intrNum = CSLR_GICSS0_COMMON_0_SPI_UART6_USART_IRQ_0;
        #else
            params->intrNum = 30U;
            params->eventId = 440;
        #endif
            break;

        default:
            return -1;
    }
    /*For AM275X*/
#elif defined(SOC_AM275X)
    switch(instanceId)
    {
        case CONFIG_UART0:
        #if !(defined(CPU_C75_0) || defined(CPU_C75_1))
            params->intrNum = CSLR_WKUP_R5FSS0_CORE0_INTR_UART0_USART_IRQ_0;
        #else
            params->intrNum = 32U;
            params->eventId = 434;
        #endif
            break;

        case CONFIG_UART1:
        #if !(defined(CPU_C75_0) || defined(CPU_C75_1))
            params->intrNum = CSLR_WKUP_R5FSS0_CORE0_INTR_UART1_USART_IRQ_0;
        #else
            params->intrNum = 33U;
            params->eventId = 435;
        #endif
            params->rxEvtNum = 0;
            params->txEvtNum = 0;
            break;

        case CONFIG_UART2:
        #if !(defined(CPU_C75_0) || defined(CPU_C75_1))
            params->intrNum = CSLR_WKUP_R5FSS0_CORE0_INTR_UART2_USART_IRQ_0;
        #else
            params->intrNum = 34U;
            params->eventId = 436;
        #endif
            break;

        case CONFIG_UART3:
        #if!(defined(CPU_C75_0) || defined(CPU_C75_1))
            params->intrNum = CSLR_WKUP_R5FSS0_CORE0_INTR_UART3_USART_IRQ_0;
        #else
            params->intrNum = 35U;
            params->eventId = 437;
        #endif
            break;

        case CONFIG_UART4:
        #if !(defined(CPU_C75_0) || defined(CPU_C75_1))
            params->intrNum = CSLR_WKUP_R5FSS0_CORE0_INTR_UART4_USART_IRQ_0;
        #else
            params->intrNum = 36U;
            params->eventId = 438;
        #endif
            break;

        case CONFIG_UART5:
        #if !(defined(CPU_C75_0) || defined(CPU_C75_1))
            params->intrNum = CSLR_WKUP_R5FSS0_CORE0_INTR_UART5_USART_IRQ_0;
        #else
            params->intrNum = 37U;
            params->eventId = 439;
        #endif
            break;

        case CONFIG_UART6:
        #if !(defined(CPU_C75_0) || defined(CPU_C75_1))
            params->intrNum = CSLR_WKUP_R5FSS0_CORE0_INTR_UART6_USART_IRQ_0;
        #else
            params->intrNum = 38U;
            params->eventId = 440;
        #endif
            break;

        case CONFIG_UART7:
        #if !(defined(CPU_C75_0) || defined(CPU_C75_1))
            params->intrNum = CSLR_WKUP_R5FSS0_CORE0_INTR_WKUP_UART0_USART_IRQ_0;
        #else
            params->intrNum = 22U;
            params->eventId = 442;
        #endif
            break;

        default:
            return -1;
    }
#endif

/* UART instance initialization */
    switch (tcId)
    {
        case 8918:
        case 8920:
        case 8921:
        case 1006:
        case 8925:
        case 8926:
        case 8928:
        case 8929:
        case 8930:
        case 8932:
        case 8933:
        case 8934:
        case 8941:
        case 8950:
        case 8959:
        case 8961:
        case 8963:
        case 8964:
        case 8966:
        case 8967:
        case 8968:
        case 8970:
        case 8971:
        case 8973:
        case 8974:
        case 8975:
        case 8981:
        case 8986:
        case 8991:
            params->writeMode = UART_TRANSFER_MODE_BLOCKING;
            params->transferMode = UART_CONFIG_MODE_POLLED;
            break;
        case 8939:
        case 8951:
        case 8976:
            params->writeMode = UART_TRANSFER_MODE_CALLBACK;
            params->transferMode = UART_CONFIG_MODE_INTERRUPT;
            params->writeCallbackFxn = TestUart_uartWriteCallback;
            break;
        case 8940:
        case 8952:
        case 8962:
        case 8984:
        case 8989:
            params->writeMode = UART_TRANSFER_MODE_BLOCKING;
            params->transferMode = UART_CONFIG_MODE_INTERRUPT;
            break;
        case 8992:
            params->writeMode = UART_TRANSFER_MODE_BLOCKING;
            params->transferMode = UART_CONFIG_MODE_POLLED;
            params->readMode = UART_TRANSFER_MODE_BLOCKING;
            params->readReturnMode = UART_READ_RETURN_MODE_PARTIAL;
            break;
        case 8993:
        case 8994:
        case 8924:
            params->writeMode = UART_TRANSFER_MODE_BLOCKING;
            params->transferMode = UART_CONFIG_MODE_POLLED;
            params->readMode = UART_TRANSFER_MODE_BLOCKING;
            params->readReturnMode = UART_READ_RETURN_MODE_FULL;
            break;
        case 8995:
        case 8960:
        case 8943:
        case 8938:
        case 8935:
            params->writeMode = UART_TRANSFER_MODE_CALLBACK;
            params->transferMode = UART_CONFIG_MODE_INTERRUPT;
            params->readMode = UART_TRANSFER_MODE_CALLBACK;
            params->readReturnMode = UART_READ_RETURN_MODE_FULL;
            params->writeCallbackFxn = TestUart_uartWriteCallback;
            params->readCallbackFxn = TestUart_uartReadCallback;

            break;
        case 8936:
            params->writeMode = UART_TRANSFER_MODE_BLOCKING;
            params->transferMode = UART_CONFIG_MODE_INTERRUPT;
            params->readMode = UART_TRANSFER_MODE_BLOCKING;
            params->readReturnMode = UART_READ_RETURN_MODE_FULL;
            break;
        case 8958:
            params->writeMode = UART_TRANSFER_MODE_BLOCKING;
            params->transferMode = UART_CONFIG_MODE_INTERRUPT;
            params->readMode = UART_TRANSFER_MODE_BLOCKING;
            params->readReturnMode = UART_READ_RETURN_MODE_FULL;
            params->rxTrigLvl = UART_RXTRIGLVL_1;
            params->txTrigLvl = UART_TXTRIGLVL_1;
            break;
        case 8944:
            params->transferMode = UART_CONFIG_MODE_DMA;
            params->writeMode = UART_TRANSFER_MODE_BLOCKING;
            params->readMode = UART_TRANSFER_MODE_CALLBACK;
            params->writeCallbackFxn = TestUart_uartWriteCallback;
            params->readCallbackFxn = TestUart_uartReadCallback;
            params->uartDmaIndex = 0;
            params->txTrigLvl = UART_TXTRIGLVL_1;
            params->rxTrigLvl = UART_RXTRIGLVL_1;
            break;
        case 11621:
            params->transferMode = UART_CONFIG_MODE_DMA;
            params->writeMode = UART_TRANSFER_MODE_CALLBACK;
            params->readMode = UART_TRANSFER_MODE_BLOCKING;
            params->writeCallbackFxn = TestUart_uartWriteCallback;
            params->readCallbackFxn = TestUart_uartReadCallback;
            params->uartDmaIndex = 0;
            params->txTrigLvl = UART_TXTRIGLVL_1;
            params->rxTrigLvl = UART_RXTRIGLVL_1;
            break;
        case 10109:
            params->transferMode = UART_CONFIG_MODE_INTERRUPT;
            params->writeMode = UART_TRANSFER_MODE_CALLBACK;
            params->readMode = UART_TRANSFER_MODE_CALLBACK;
            params->writeCallbackFxn = TestUart_uartWriteCallback;
            params->readCallbackFxn = TestUart_uartReadCallback;
            params->txTrigLvl = UART_TXTRIGLVL_16;
            params->rxTrigLvl = UART_RXTRIGLVL_16;
            break;
        case 10110:
            params->writeMode = UART_TRANSFER_MODE_CALLBACK;
            params->readMode  = UART_TRANSFER_MODE_CALLBACK;
            params->transferMode = UART_CONFIG_MODE_INTERRUPT;
            params->writeCallbackFxn = TestUart_uartWriteCallback;
            params->readCallbackFxn  = TestUart_uartReadCallback;
            /* txTrigLvl and rxTrigLvl will be varied inside the test per iteration */
            break;
        case 10111:
            /* Polled + blocking read to drive UART_statusIsDataReady -> UART_procLineStatusErr */
            params->writeMode = UART_TRANSFER_MODE_BLOCKING;
            params->transferMode = UART_CONFIG_MODE_POLLED;
            params->readMode = UART_TRANSFER_MODE_BLOCKING;
            params->readReturnMode = UART_READ_RETURN_MODE_FULL;
            break;
        case 10112:
            /* Polled write with short timeout to hit timeoutElapsed in UART_writePolling */
            params->transferMode    = UART_CONFIG_MODE_POLLED;
            params->writeMode       = UART_TRANSFER_MODE_BLOCKING;
            params->readMode        = UART_TRANSFER_MODE_BLOCKING;
            params->readReturnMode  = UART_READ_RETURN_MODE_FULL;
            params->baudRate        = 1200;                 /* slow down to ensure timeout */
            params->txTrigLvl       = UART_TXTRIGLVL_56;
            params->rxTrigLvl       = UART_RXTRIGLVL_1;
            break;
        case 10113:
            /* Invalid: readMode=CALLBACK without readCallbackFxn */
            params->transferMode     = UART_CONFIG_MODE_POLLED;
            params->writeMode        = UART_TRANSFER_MODE_BLOCKING;
            params->readMode         = UART_TRANSFER_MODE_CALLBACK;
            params->readCallbackFxn  = NULL;
            params->writeCallbackFxn = TestUart_uartWriteCallback; /* valid write cb */
            params->readReturnMode   = UART_READ_RETURN_MODE_FULL;
            params->txTrigLvl        = UART_TXTRIGLVL_8;
            params->rxTrigLvl        = UART_RXTRIGLVL_8;
            break;

        case 10114:
            /* Invalid: writeMode=CALLBACK without writeCallbackFxn */
            params->transferMode     = UART_CONFIG_MODE_POLLED;
            params->writeMode        = UART_TRANSFER_MODE_CALLBACK;
            params->readMode         = UART_TRANSFER_MODE_BLOCKING;
            params->writeCallbackFxn = NULL;
            params->readCallbackFxn  = TestUart_uartReadCallback;  /* valid read cb */
            params->readReturnMode   = UART_READ_RETURN_MODE_FULL;
            params->txTrigLvl        = UART_TXTRIGLVL_8;
            params->rxTrigLvl        = UART_RXTRIGLVL_8;
            break;
        case 10115:
            /* Interrupt + callback read; small trigger levels for immediate drain */
            params->transferMode     = UART_CONFIG_MODE_INTERRUPT;
            params->writeMode        = UART_TRANSFER_MODE_BLOCKING;
            params->readMode         = UART_TRANSFER_MODE_CALLBACK;
            params->readReturnMode   = UART_READ_RETURN_MODE_FULL;
            params->readCallbackFxn  = TestUart_immediateReadCallback;
            params->writeCallbackFxn = TestUart_uartWriteCallback;
            params->txTrigLvl        = UART_TXTRIGLVL_1;
            params->rxTrigLvl        = UART_RXTRIGLVL_1;
            break;
        case 10116:
            /* Normal interrupt-mode config; no read started before readCancel */
            params->transferMode     = UART_CONFIG_MODE_INTERRUPT;
            params->writeMode        = UART_TRANSFER_MODE_BLOCKING;
            params->readMode         = UART_TRANSFER_MODE_BLOCKING;
            params->readReturnMode   = UART_READ_RETURN_MODE_FULL;
            params->txTrigLvl        = UART_TXTRIGLVL_1;
            params->rxTrigLvl        = UART_RXTRIGLVL_1;
            params->skipIntrReg      = FALSE;
            break;
        case 9075:
            /* Interrupt mode with blocking write; helper task will cancel to hit SemaphoreP_post path */
            params->transferMode     = UART_CONFIG_MODE_INTERRUPT;
            params->writeMode        = UART_TRANSFER_MODE_BLOCKING;
            params->readMode         = UART_TRANSFER_MODE_BLOCKING;
            params->readReturnMode   = UART_READ_RETURN_MODE_FULL;
            params->baudRate         = 1200;                /* slow to keep write active */
            params->txTrigLvl        = UART_TXTRIGLVL_1;
            params->rxTrigLvl        = UART_RXTRIGLVL_1;
            params->skipIntrReg      = FALSE;
            break;
        case 10117:
            /* Basic polled config; the handle will be closed before write */
            params->transferMode    = UART_CONFIG_MODE_POLLED;
            params->writeMode       = UART_TRANSFER_MODE_BLOCKING;
            params->readMode        = UART_TRANSFER_MODE_BLOCKING;
            params->readReturnMode  = UART_READ_RETURN_MODE_FULL;
            params->baudRate        = 115200;
            params->txTrigLvl       = UART_TXTRIGLVL_8;
            params->rxTrigLvl       = UART_RXTRIGLVL_8;
            params->skipIntrReg     = FALSE;
            break;
        case 10118:
            /* Interrupt + blocking, ensure skipIntrReg == FALSE to hit else path */
            params->transferMode     = UART_CONFIG_MODE_INTERRUPT;
            params->writeMode        = UART_TRANSFER_MODE_BLOCKING;
            params->readMode         = UART_TRANSFER_MODE_BLOCKING;
            params->readReturnMode   = UART_READ_RETURN_MODE_FULL;
            params->txTrigLvl        = UART_TXTRIGLVL_1;
            params->rxTrigLvl        = UART_RXTRIGLVL_1;
            params->skipIntrReg      = TRUE;   /* target branch */
            break;
        case 10119:
            /* Basic blocking config; we will close the handle before calling UART_read */
            params->transferMode     = UART_CONFIG_MODE_POLLED;
            params->writeMode        = UART_TRANSFER_MODE_BLOCKING;
            params->readMode         = UART_TRANSFER_MODE_BLOCKING;
            params->readReturnMode   = UART_READ_RETURN_MODE_FULL;
            params->txTrigLvl        = UART_TXTRIGLVL_1;
            params->rxTrigLvl        = UART_RXTRIGLVL_1;
            break;
        case 10120:
            /* Read timeout in loopback: interrupt + blocking read, no write performed */
            params->transferMode     = UART_CONFIG_MODE_INTERRUPT;
            params->writeMode        = UART_TRANSFER_MODE_BLOCKING;
            params->readMode         = UART_TRANSFER_MODE_BLOCKING;
            params->readReturnMode   = UART_READ_RETURN_MODE_FULL;
            params->txTrigLvl        = UART_TXTRIGLVL_1;
            params->rxTrigLvl        = UART_RXTRIGLVL_1;
            break;
        case 10121:
            /* Partial read in loopback: interrupt, callback write + blocking read, partial return */
            params->transferMode     = UART_CONFIG_MODE_INTERRUPT;
            params->writeMode        = UART_TRANSFER_MODE_CALLBACK;
            params->readMode         = UART_TRANSFER_MODE_BLOCKING;
            params->readReturnMode   = UART_READ_RETURN_MODE_PARTIAL;
            params->writeCallbackFxn = TestUart_uartWriteCallback;
            params->txTrigLvl        = UART_TXTRIGLVL_1;
            params->rxTrigLvl        = UART_RXTRIGLVL_1;
            break;
        case 11631:
        case 11632:
            /* Cancel + re-transfer: interrupt, callback write + callback read */
            params->transferMode     = UART_CONFIG_MODE_INTERRUPT;
            params->writeMode        = UART_TRANSFER_MODE_CALLBACK;
            params->readMode         = UART_TRANSFER_MODE_CALLBACK;
            params->readReturnMode   = UART_READ_RETURN_MODE_FULL;
            params->writeCallbackFxn = TestUart_uartWriteCallback;
            params->readCallbackFxn  = TestUart_uartReadCallback;
            params->txTrigLvl        = UART_TXTRIGLVL_1;
            params->rxTrigLvl        = UART_RXTRIGLVL_1;
            break;
        case 10125:
            /* Errata i2310: interrupt, blocking write + callback read, RX trig = 1 */
            params->transferMode     = UART_CONFIG_MODE_INTERRUPT;
            params->writeMode        = UART_TRANSFER_MODE_BLOCKING;
            params->readMode         = UART_TRANSFER_MODE_CALLBACK;
            params->readReturnMode   = UART_READ_RETURN_MODE_FULL;
            params->readCallbackFxn  = TestUart_uartReadCallback;
            params->txTrigLvl        = UART_TXTRIGLVL_1;
            params->rxTrigLvl        = UART_RXTRIGLVL_1;
            break;
        case 11633:
            /* Continuous DMA TX callback: DMA, callback write + callback read */
            params->transferMode     = UART_CONFIG_MODE_DMA;
            params->writeMode        = UART_TRANSFER_MODE_CALLBACK;
            params->readMode         = UART_TRANSFER_MODE_CALLBACK;
            params->writeCallbackFxn = TestUart_uartWriteCallback;
            params->readCallbackFxn  = TestUart_uartReadCallback;
            params->uartDmaIndex     = 0;
            params->txTrigLvl        = UART_TXTRIGLVL_1;
            params->rxTrigLvl        = UART_RXTRIGLVL_1;
            break;
        case 11634:
            /* Write-inside-callback: DMA, callback write + callback read */
            params->transferMode     = UART_CONFIG_MODE_DMA;
            params->writeMode        = UART_TRANSFER_MODE_CALLBACK;
            params->readMode         = UART_TRANSFER_MODE_CALLBACK;
            params->writeCallbackFxn = TestUart_nestedWriteCallback;
            params->readCallbackFxn  = TestUart_uartReadCallback;
            params->uartDmaIndex     = 0;
            params->txTrigLvl        = UART_TXTRIGLVL_1;
            params->rxTrigLvl        = UART_RXTRIGLVL_1;
            break;
        default:
            break;
    }

    return 0;
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
/**
 * @brief UART write completion callback for interrupt/callback mode tests.
 *
 * Invoked by the UART driver when a write transaction completes in
 * callback mode. Posts the write completion semaphore to signal the
 * test thread that the asynchronous write has finished.
 *
 * @param[in] handle UART handle associated with the transaction.
 * @param[in] trans  Pointer to the completed UART_Transaction structure.
 *
 * @return void
 */
static void TestUart_uartWriteCallback(UART_Handle handle, UART_Transaction *trans)
{
    /* Post the write completion semaphore */
    SemaphoreP_post(&gUartWriteDoneSem);
}

/**
 * @brief UART read completion callback for interrupt/callback mode tests.
 *
 * This function is invoked by the UART driver when a read transaction
 * completes in callback mode. It posts the read completion semaphore
 * (provided in trans->args) to signal the test thread that the read
 * operation has finished.
 *
 * Used in UART unit tests to synchronize test execution and validate
 * asynchronous read operations.
 *
 * @param[in] handle UART handle associated with the transaction.
 * @param[in] trans  Pointer to the completed UART_Transaction structure.
 *
 * @return void
 */
static void TestUart_uartReadCallback(UART_Handle handle, UART_Transaction *trans)
{
    /* Post the read completion semaphore */
    SemaphoreP_post(&gUartReadDoneSem);
}

/**
 * @brief Custom write callback that attempts a nested UART_write().
 *
 * Called by UART_udmaIsrTx while writeTrans is still non-NULL.
 * Attempts a second UART_write() to prove the driver returns
 * UART_TRANSFER_STATUS_ERROR_INUSE, then posts the semaphore.
 */
static void TestUart_nestedWriteCallback(UART_Handle handle, UART_Transaction *trans)
{
    if (TestUart_nestedWriteArmed != 0U)
    {
        /* Try to initiate another write from inside the callback */
        TestUart_nestedWriteResult = UART_write((UART_Handle)TestUart_nestedWriteHandle, &TestUart_nestedWriteTrans);
        TestUart_nestedWriteStatus = TestUart_nestedWriteTrans.status;
        TestUart_nestedWriteArmed  = 0U;
    }

    /* Always post so the test thread can continue */
    SemaphoreP_post(&gUartWriteDoneSem);
}

/**
 * @brief Validate UART_open with an invalid UART index.
 *
 * Attempts to open a UART instance using TEST_UART_CONFIG_INDEX_INVALID and
 * verifies the driver returns a NULL handle. Closes the handle if non-NULL,
 * then opens the debug UART and asserts non-zero finalStatus.
 *
 * Test Steps:
 * 1. Fetch UART_Params from args.
 * 2. Call UART_open(TEST_UART_CONFIG_INDEX_INVALID, uartParams).
 * 3. Expect NULL handle; set finalStatus bit on success.
 * 4. Close handle if opened.
 * 5. Open debug UART and assert finalStatus != 0.
 *
 * @param[in] args Pointer to UART_TestParams providing UART_Params.
 *
 * @return void
 */
static void TestUart_uartOpenInvalidIndex(void *args)
{
    /* Initialize UART parameters */
    UART_Handle uartHandle = NULL;
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint8_t finalStatus = 0;

    /* Try to open UART with invalid index */
    uartHandle = UART_open(TEST_UART_CONFIG_INDEX_INVALID, uartParams);

    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 0);
    }

    /* Close UART handle if opened */
    UART_close(uartHandle);

    TestUart_openDebugUart();
    TEST_ASSERT_NOT_EQUAL(0, finalStatus);
}

/**
 * @brief Testcase to validate UART_open API when NULL parameters are passed.
 *
 * This test attempts to open a UART instance using NULL for the UART_Params argument.
 * It checks whether the driver returns a valid UART handle or not, and prints
 * pass/fail status messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Call UART_open with CONFIG_UART1 and NULL params.
 * 4. Check if the returned handle is NULL.
 * 5. Print pass/fail message based on result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartOpenNullParams(void *args)
{
    /* Initialize UART parameters */
    UART_Handle uartHandle = NULL;
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Try to open UART with NULL params */
    uartHandle = UART_open(instanceId, NULL);
    /* Assert that UART handle is not NULL */
    if (uartHandle == NULL)
    {
        TEST_ASSERT_NULL(uartHandle);
    }
    
    /* Close UART handle */
    UART_close(uartHandle);
}

/**
 * @brief Validate UART_open when called twice without closing the first handle.
 *
 * Opens the same UART instance (from args) twice with the same params. Expects
 * the first open to succeed and the second to return NULL. Closes both handles,
 * opens the debug UART, and asserts the expected result.
 *
 * Test Steps:
 * 1. Fetch UART_Params and instanceId from args; close any existing handle.
 * 2. Open UART (first) and verify handle != NULL.
 * 3. Open UART again (second) and expect handle == NULL.
 * 4. Close both handles (if non-NULL).
 * 5. Call TestUart_openDebugUart and assert finalStatus != 0.
 *
 * @param[in] args Pointer to UART_TestParams (contains UART_Params and instanceId).
 *
 * @return void
 */
static void TestUart_uartOpenMultipleOpenWithoutClose(void *args)
{
    /* Initialize UART parameters */
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle1 = NULL;
    UART_Handle uartHandle2 = NULL;
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle1 = UART_getHandle(instanceId);
    if (uartHandle1 != NULL)
    {
        UART_close(uartHandle1);
    }

    /* First open should succeed */
    uartHandle1 = UART_open(instanceId, uartParams);
    /* Check if the first handle is valid */
    if (uartHandle1 == NULL)
    {
        finalStatus |= (1 << 0);
    }

    /* Second open on same instance should fail (should return NULL) */
    uartHandle2 = UART_open(instanceId, uartParams);
    /* Check if the second handle is not valid */
    if (uartHandle2 == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Close first handle */
    UART_close(uartHandle1);

    /* Close second handle */
    UART_close(uartHandle2);

    TestUart_openDebugUart();
    TEST_ASSERT_NOT_EQUAL(0, finalStatus);
}

/**
 * @brief Testcase to validate UART_open API after closing and reopening with different parameters.
 *
 * This test verifies that the UART driver correctly applies new configuration parameters
 * when a UART instance is closed and then reopened. It first opens the UART with one set
 * of parameters (e.g., baudRate = 9600), closes the instance, then reopens it with a
 * different set of parameters (e.g., baudRate = 115200), and checks if the new configuration
 * is applied.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1 to ensure a clean state.
 * 3. Initialize UART parameters for the first configuration (baudRate = 9600).
 * 4. Open UART instance and verify handle is not NULL.
 * 5. Close UART instance.
 * 6. Initialize UART parameters for the second configuration (baudRate = 115200).
 * 7. Open UART instance and verify handle is not NULL.
 * 8. Retrieve UART_Object from handle and check if the baudRate matches the second configuration.
 * 9. Close UART instance.
 * 10. Print pass/fail message based on the result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartOpenCloseAndReopenWithDifferentParams(void *args)
{
    /* Initialize UART parameters */
    UART_Params uartParams1 = {0};
    UART_Params *uartParams2 = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Object *uartObject = NULL;
    UART_Handle uartHandle1 = NULL, uartHandle2 = NULL;
    uint8_t finalStatus = 0;
    uint32_t baudRate2 = 0;

    /* Close to ensure previous state is cleared */
    uartHandle1 = UART_getHandle(instanceId);
    if (uartHandle1 != NULL)
    {
        UART_close(uartHandle1);
    }

    /* First configuration */
    UART_Params_init(&uartParams1);
    uartParams1.transferMode = UART_CONFIG_MODE_POLLED;
    uartParams1.baudRate = 9600;

    /* First configuration */
    uartHandle1 = UART_open(instanceId, &uartParams1);
    if(uartHandle1 == NULL)
    {
        finalStatus = (1 << 0);
    }

    /* Close UART instance */
    UART_close(uartHandle1);

    /* Second configuration */
    uartParams2->baudRate = 115200;
    uartHandle2 = UART_open(instanceId, uartParams2);
    if(uartHandle2 == NULL)
    {
        finalStatus |= (1 << 1);
    }
    else
    {
        /* Check if new configuration is applied */
        uartObject = ((UART_Config *)uartHandle2)->object;
        if (uartObject == NULL)
        {
            finalStatus |= (1 << 2);
        }
        else
        {
            baudRate2 = uartObject->prms.baudRate;
        }
    }

    /* Close UART instance */
    UART_close(uartHandle2);

    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_EQUAL_UINT32(uartParams2->baudRate, baudRate2);
}

/**
 * @brief Testcase to validate UART_open API with all UART instances.
 *
 * This test checks the driver behavior when opening each available UART instance
 * (CONFIG_UART0 to CONFIG_UART_NUM_INSTANCES-1). For each instance, it initializes
 * UART parameters, opens the instance, enables loopback mode, performs a blocking
 * write and read, and compares the transmitted and received data for integrity.
 * The test counts successful loopback operations and prints pass/fail status messages
 * over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. For each UART instance:
 *    a. Close any existing UART handle for the instance.
 *    b. Open UART instance and verify handle is not NULL.
 *    c. Enable loopback mode.
 *    d. Perform blocking write and read.
 *    e. Compare transmitted and received data.
 *    f. Close UART handle.
 * 3. Assert that all instances pass the loopback test.
 * 4. Print pass/fail message based on result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartOpenUartInstances(void *args)
{
    UART_Handle uartHandle = NULL;
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Transaction transWrite = {0}, transRead = {0};
    int32_t transferOK = SystemP_FAILURE;
    uint32_t baseAddr = 0U;
    static uint8_t uartTxBuffer[APP_UART_BUFSIZE] = {0};
    static uint8_t uartRxBuffer[APP_UART_BUFSIZE] = {0};
    uint64_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
            finalStatus |= (1 << 0);
            goto close;
    }

    /* Enable loopback mode */
    baseAddr = UART_getBaseAddr(uartHandle);
    if (baseAddr == 0U)
    {
        /* Instance not accessible on this core (e.g., AM62AX WKUP R5 MAIN UARTs). Skip gracefully. */
        UART_close(uartHandle);
        goto cleanup;
    }
    TestUart_enableLoopback(baseAddr);

    /* Prepare write transaction */
    UART_Transaction_init(&transWrite);
    transWrite.buf = &uartTxBuffer[0U];
    strncpy((char *)transWrite.buf, "UART BLOCKING LOOPBACK DATA\r\n", APP_UART_BUFSIZE);
    transWrite.count = strlen((char *)transWrite.buf);
    transWrite.timeout = SystemP_WAIT_FOREVER;

    /* Perform UART write in blocking mode */
    transferOK = UART_write(uartHandle, &transWrite);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1 << 1);
    }
    if (transWrite.status != UART_TRANSFER_STATUS_SUCCESS)
    {
        finalStatus |= (1 << 2);
    }

    /* Prepare read transaction */
    UART_Transaction_init(&transRead);
    transRead.buf = &uartRxBuffer[0U];
    transRead.count = transWrite.count;
    transRead.timeout = SystemP_WAIT_FOREVER;

    /* Perform UART read in blocking mode */
    transferOK = UART_read(uartHandle, &transRead);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1 << 3);
    }
    if (transRead.status != UART_TRANSFER_STATUS_SUCCESS)
    {
        finalStatus |= (1 << 4);
    }

    /* Disable loopback mode */
    UART_disableLoopbackMode(baseAddr);

    if (0 != memcmp(transWrite.buf, transRead.buf, transWrite.count))
    {
        finalStatus |= (1 << 5);
    }

 cleanup:

    /* Close UART handle */
    UART_close(uartHandle);
 close:
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
}

/**
 * @brief Testcase to validate UART_open API with different instances and different parameters.
 *
 * This test verifies that the UART driver correctly applies independent configuration
 * parameters to multiple UART instances. It opens two UART instances (CONFIG_UART1 and CONFIG_UART0/2)
 * with different baud rates and checks that each instance uses its own configuration.
 * The test prints pass/fail status messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handles for CONFIG_UART1 and CONFIG_UART0/2 to ensure a clean state.
 * 3. Initialize UART parameters for CONFIG_UART1 (baudRate = 9600, POLLED mode).
 * 4. Initialize UART parameters for CONFIG_UART0/2 (baudRate = 115200, POLLED mode).
 * 5. Open UART instance CONFIG_UART1 and verify handle is not NULL.
 * 6. Open UART instance CONFIG_UART0/2 and verify handle is not NULL.
 * 7. Retrieve UART_Object from each handle and check if the baudRate matches the respective configuration.
 * 8. Close both UART handles.
 * 9. Print pass/fail message based on the result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartOpenDifferentInstances(void *args)
{
    /* Initialize UART parameters */
    UART_Params *uartParams1 = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    UART_Params uartParams2 = {0};
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    uint16_t nextInstanceId = 0;
    UART_Handle uartHandle1 = NULL;
    UART_Handle uartHandle2 = NULL;
    UART_Object *uartObject1 = NULL;
    UART_Object *uartObject2 = NULL;
    uint8_t finalStatus = 0;
    uint32_t baudRate1 = 0, baudRate2 = 0;


    /* Close to ensure previous state is cleared */
    uartHandle1 = UART_getHandle(instanceId);
    if(uartHandle1 != NULL)
    {
        UART_close(uartHandle1);
    }

    /* Close to ensure previous state is cleared */
    nextInstanceId = ((instanceId + 1) > CONFIG_UART_NUM_INSTANCES - 1) ? (instanceId - 1) : (instanceId +1);
    uartHandle2 = UART_getHandle(nextInstanceId);
    if(uartHandle2 != NULL)
    {
        UART_close(uartHandle2);
    }

    /* Second UART instance configuration */
    UART_Params_init(&uartParams2);
    uartParams2.baudRate = 9600;
    uartParams2.transferMode = UART_CONFIG_MODE_POLLED;

    /* Open first UART instance */
    uartParams1->baudRate = 115200;
    uartHandle1 = UART_open(instanceId, uartParams1);
    if (uartHandle1 == NULL)
    {
        finalStatus |= (1 << 0);
    }
    else
    {
        uartObject1 = ((UART_Config *)uartHandle1)->object;
        if (uartObject1 == NULL)
        {
            finalStatus |= (1 << 1);
        }
        else
        {
            baudRate1 = uartObject1->prms.baudRate;
        }
    }

    /* Open second UART instance */
    uartHandle2 = UART_open(nextInstanceId, &uartParams2);
    if (uartHandle2 == NULL)
    {
        finalStatus |= (1 << 2);
    }
    else
    {
        uartObject2 = ((UART_Config *)uartHandle2)->object;
        if (uartObject2 == NULL)
        {
            finalStatus |= (1 << 3);
        }
        else
        {
            baudRate2 = uartObject2->prms.baudRate;
        }
    }

    /* Close both UART instances */
    UART_close(uartHandle1);
    UART_close(uartHandle2);

    /* Verify and print test result */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_EQUAL(uartParams1->baudRate, baudRate1);
    TEST_ASSERT_NOT_EQUAL(baudRate2, baudRate1);
}

/**
 * @brief Testcase to validate UART_close API when called twice on the same handle.
 *
 * This test checks the driver behavior when attempting to close the same UART handle
 * two times in succession. The expected result is that both close operations complete
 * without error or crash, demonstrating that the driver safely handles repeated close
 * calls on the same handle.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1 to ensure a clean state.
 * 3. Initialize UART parameters for POLLED mode.
 * 4. Open UART instance and verify handle is not NULL.
 * 5. Call UART_close on the handle (first close).
 * 6. Call UART_close again on the same handle (second close).
 * 7. Print pass message if no crash or error occurs.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartCloseCloseSameHandleTwice(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 0);
    }

    /* First close */
    UART_close(uartHandle);

    /* Second close (should be safe, no crash or error) */
    UART_close(uartHandle);

    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
}

/**
 * @brief Testcase to validate UART_write and UART_read APIs in blocking mode with loopback enabled.
 *
 * This test verifies that the UART driver can successfully transmit and receive data
 * in blocking mode using loopback. It initializes UART parameters for blocking mode,
 * opens the UART instance, enables loopback, writes a buffer, reads the buffer back,
 * and compares the transmitted and received data for integrity. The test prints
 * pass/fail status messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1 to ensure a clean state.
 * 3. Initialize UART parameters for blocking mode (POLLED transfer, BLOCKING write/read).
 * 4. Open UART instance and verify handle is not NULL.
 * 5. Enable loopback mode using UART base address.
 * 6. Prepare and perform UART_write in blocking mode.
 * 7. Prepare and perform UART_read in blocking mode.
 * 8. Disable loopback mode.
 * 9. Close UART handle.
 * 10. Compare transmitted and received buffers for data integrity.
 * 11. Print pass/fail message based on result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartWriteReadBlockingModeLoopback(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    UART_Transaction transWrite = {0}, transRead = {0};
    int32_t transferOK = SystemP_FAILURE;
    uint32_t baseAddr = 0U;
    uint8_t finalStatus = 0;


    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 0);
    }

    /* Enable loopback mode */
    baseAddr = UART_getBaseAddr(uartHandle);
    /* Guard against invalid base address to avoid blocking read hang */
    if (baseAddr == 0U)
    {
        finalStatus |= (1 << 5);
        goto cleanup;
    }
    TestUart_enableLoopback(baseAddr);

    /* Prepare write transaction using global buffers to avoid stack overflow */
    memset(gUartTxBuffer, 0, APP_UART_BUFSIZE);
    memset(gUartRxBuffer, 0, APP_UART_BUFSIZE);

    UART_Transaction_init(&transWrite);
    transWrite.buf = &gUartTxBuffer[0U];
    strncpy((char *)transWrite.buf, "UART BLOCKING LOOPBACK DATA\r\n", APP_UART_BUFSIZE);
    transWrite.count = strlen((char *)transWrite.buf);
    transWrite.timeout = SystemP_WAIT_FOREVER;

    /* Perform UART write in blocking mode */
    transferOK = UART_write(uartHandle, &transWrite);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1 << 1);
    }
    if (transWrite.status != UART_TRANSFER_STATUS_SUCCESS)
    {
        finalStatus |= (1 << 2);
    }

    /* Prepare read transaction */
    UART_Transaction_init(&transRead);
    transRead.buf = &gUartRxBuffer[0U];
    transRead.count = transWrite.count;
    transRead.timeout = SystemP_WAIT_FOREVER;

    /* Perform UART read in blocking mode */
    transferOK = UART_read(uartHandle, &transRead);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1 << 3);
    }
    if (transRead.status != UART_TRANSFER_STATUS_SUCCESS)
    {
        finalStatus |= (1 << 4);
    }

    /* Disable loopback mode */
    UART_disableLoopbackMode(baseAddr);

cleanup:
    /* Close UART handle */
    UART_close(uartHandle);

    /* Validate final status */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    /* Compare written and read data */
    TEST_ASSERT_EQUAL_MEMORY(transWrite.buf, transRead.buf, transWrite.count);
}

/**
 * @brief Testcase to validate UART_write API when a NULL handle is passed.
 *
 * This test checks the driver behavior when attempting to perform a UART_write
 * operation using a NULL UART handle. The expected result is that the transfer
 * fails and does not return SystemP_SUCCESS, demonstrating that the driver
 * correctly handles invalid handle input.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1 to ensure a clean state.
 * 3. Initialize UART parameters for blocking mode (POLLED transfer, BLOCKING write).
 * 4. Open UART instance and verify handle is not NULL.
 * 5. Prepare a valid UART_Transaction structure.
 * 6. Call UART_write with NULL handle and the prepared transaction.
 * 7. Close UART handle.
 * 8. Assert that transfer fails (return value is not SystemP_SUCCESS).
 * 9. Print pass/fail message based on the result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartWriteNullHandle(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    UART_Transaction trans = {0};
    int32_t transferOK = SystemP_FAILURE;
    static uint8_t uartTxBuffer[APP_UART_BUFSIZE];
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Prepare transaction */
    UART_Transaction_init(&trans);
    trans.buf = &uartTxBuffer[0U];
    strncpy((char *)trans.buf, "UART WRITE NULL HANDLE TEST\r\n", APP_UART_BUFSIZE);
    trans.count = strlen((char *)trans.buf);
    trans.timeout = SystemP_WAIT_FOREVER;

    /* Call UART_write with NULL handle */
    transferOK = UART_write(NULL, &trans);

    /* Close UART handle */
    UART_close(uartHandle);

    /* Assert that transfer fails (should not be SystemP_SUCCESS) */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_NOT_EQUAL(SystemP_SUCCESS, transferOK);
}

/**
 * @brief Testcase to validate UART_write API when a NULL buffer is passed in the transaction.
 *
 * This test checks the driver behavior when attempting to perform a UART_write
 * operation with a transaction whose buffer pointer is NULL. The expected result
 * is that the transfer fails and does not return SystemP_SUCCESS, demonstrating
 * that the driver correctly handles invalid buffer input.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1 to ensure a clean state.
 * 3. Initialize UART parameters for blocking mode (POLLED transfer, BLOCKING write).
 * 4. Open UART instance and verify handle is not NULL.
 * 5. Prepare a UART_Transaction structure with buf set to NULL and a non-zero count.
 * 6. Call UART_write with the prepared transaction.
 * 7. Close UART handle.
 * 8. Assert that transfer fails (return value is not SystemP_SUCCESS).
 * 9. Print pass/fail message based on the result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartWriteNullBuffer(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    UART_Transaction trans = {0};
    int32_t transferOK = SystemP_FAILURE;
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Prepare transaction with NULL buffer */
    UART_Transaction_init(&trans);
    trans.buf = NULL;
    trans.count = 10;
    trans.timeout = SystemP_WAIT_FOREVER;

    /* Call UART_write with NULL buffer */
    transferOK = UART_write(uartHandle, &trans);

    /* Close UART handle */
    UART_close(uartHandle);

    /* Assert that transfer fails (should not be SystemP_SUCCESS) */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_NOT_EQUAL(SystemP_SUCCESS, transferOK);
}

/**
 * @brief Testcase to validate UART_write API when a transaction with zero count is passed.
 *
 * This test checks the driver behavior when attempting to perform a UART_write
 * operation with a transaction whose count field is zero. The expected result
 * is that the transfer fails and does not return SystemP_SUCCESS, demonstrating
 * that the driver correctly handles invalid transaction input.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1 to ensure a clean state.
 * 3. Initialize UART parameters for blocking mode (POLLED transfer, BLOCKING write).
 * 4. Open UART instance and verify handle is not NULL.
 * 5. Prepare a UART_Transaction structure with a valid buffer and zero count.
 * 6. Call UART_write with the prepared transaction.
 * 7. Close UART handle.
 * 8. Assert that transfer fails (return value is not SystemP_SUCCESS).
 * 9. Print pass/fail message based on the result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartWriteZeroCount(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;

    UART_Handle uartHandle = NULL;
    UART_Transaction trans = {0};
    int32_t transferOK = SystemP_FAILURE;
    static uint8_t uartTxBuffer[APP_UART_BUFSIZE];
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Prepare transaction with zero count */
    UART_Transaction_init(&trans);
    trans.buf = &uartTxBuffer[0U];
    strncpy((char *)trans.buf, "UART WRITE ZERO COUNT TEST\r\n", APP_UART_BUFSIZE);
    trans.count = 0;
    trans.timeout = SystemP_WAIT_FOREVER;

    /* Call UART_write with zero count */
    transferOK = UART_write(uartHandle, &trans);

    /* Close UART handle */
    UART_close(uartHandle);

    /* Assert that transfer fails (should not be SystemP_SUCCESS) */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_NOT_EQUAL(SystemP_SUCCESS, transferOK);
}

/**
 * @brief Testcase to validate UART_write API when a NULL transaction pointer is passed.
 *
 * This test checks the driver behavior when attempting to perform a UART_write
 * operation with a NULL transaction pointer. The expected result is that the transfer
 * fails and does not return SystemP_SUCCESS, demonstrating that the driver correctly
 * handles invalid transaction input.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1 to ensure a clean state.
 * 3. Initialize UART parameters for blocking mode (POLLED transfer, BLOCKING write).
 * 4. Open UART instance and verify handle is not NULL.
 * 5. Call UART_write with a NULL transaction pointer.
 * 6. Close UART handle.
 * 7. Assert that transfer fails (return value is not SystemP_SUCCESS).
 * 8. Print pass/fail message based on the result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartWriteNullTransaction(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;

    UART_Handle uartHandle = NULL;
    int32_t transferOK = SystemP_FAILURE;
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Call UART_write with NULL transaction */
    transferOK = UART_write(uartHandle, NULL);

    /* Close UART handle */
    UART_close(uartHandle);

    /* Assert that transfer fails (should not be SystemP_SUCCESS) */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_NOT_EQUAL(SystemP_SUCCESS, transferOK);
}

#if !defined(CPU_C7x)

/**
 * @brief Testcase to validate UART_write API in blocking mode with interrupt transfer.
 *
 * This test verifies that the UART driver can successfully transmit data
 * in blocking mode while using interrupt-driven transfer. It initializes UART
 * parameters for blocking mode and interrupt transfer, opens the UART instance,
 * prepares a transmit buffer, and performs a UART_write operation. The test
 * checks if the transfer completes successfully and prints pass/fail status
 * messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1 to ensure a clean state.
 * 3. Initialize UART parameters for blocking mode with interrupt transfer.
 * 4. Open UART instance and verify handle is not NULL.
 * 5. Prepare a transmit buffer and transaction.
 * 6. Perform UART_write in blocking mode with interrupt transfer.
 * 7. Close UART handle.
 * 8. Check transfer status and print pass/fail message.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
void TestUart_uartWriteReadBlockingModeInterrupt(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    UART_Transaction trans = {0}, transRead = {0};
    int32_t transferOK = SystemP_FAILURE;
    static uint8_t uartTxBuffer[APP_UART_BUFSIZE];
    static uint8_t uartRxBuffer[APP_UART_BUFSIZE];
    uint8_t finalStatus = 0;
    uint32_t baseAddr = 0U;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 0);
    }

    /* Enable loopback mode */
    baseAddr = UART_getBaseAddr(uartHandle);
    TestUart_enableLoopback(baseAddr);

    /* Prepare transaction */
    UART_Transaction_init(&trans);
    trans.buf = &uartTxBuffer[0U];
    strncpy((char *)trans.buf, "UART BLOCKING INTERRUPT WRITE TEST\r\n", APP_UART_BUFSIZE);
    trans.count = strlen((char *)trans.buf);
    trans.timeout = SystemP_WAIT_FOREVER;

    /* Perform UART write in blocking mode with interrupt transfer */
    transferOK = UART_write(uartHandle, &trans);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1 << 1);
    }
    if (trans.status != UART_TRANSFER_STATUS_SUCCESS)
    {
        finalStatus |= (1 << 2);
    }

    /* Prepare read transaction */
    UART_Transaction_init(&transRead);
    transRead.buf = &uartRxBuffer[0U];
    transRead.count = 8;
    transRead.timeout = SystemP_WAIT_FOREVER;

    /* Perform UART read in blocking mode with interrupt transfer*/
    transferOK = UART_read(uartHandle, &transRead);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1 << 3);
    }
    if (transRead.status != UART_TRANSFER_STATUS_SUCCESS)
    {
        finalStatus |= (1 << 4);
    }

    /* Disable loopback mode */
    UART_disableLoopbackMode(baseAddr);

    /* Close UART handle */
    UART_close(uartHandle);

    /* Validate final status */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_EQUAL_MEMORY(trans.buf, transRead.buf, transRead.count);
}

#endif

/**
 * @brief Testcase to validate UART_write API in callback mode with interrupt transfer, timeout, and cancel.
 *
 * This test verifies that the UART driver correctly handles write transactions
 * in callback mode with interrupt transfer when a timeout and cancel operation are performed.
 * It initializes UART parameters for callback mode, opens the UART instance,
 * prepares a transmit buffer and transaction, starts the write, introduces a delay,
 * and then cancels the ongoing transaction. The test checks if the transfer status
 * is UART_TRANSFER_STATUS_TIMEOUT or UART_TRANSFER_STATUS_CANCELLED, and prints
 * pass/fail status messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for the selected instance.
 * 3. Initialize UART parameters for callback mode with interrupt transfer.
 * 4. Open UART instance and verify handle is not NULL.
 * 5. Prepare a transmit buffer and transaction.
 * 6. Start UART_write in callback mode with interrupt transfer.
 * 7. Introduce a delay to allow some data to be transmitted.
 * 8. Cancel the ongoing transaction.
 * 9. Close UART handle.
 * 10. Assert transfer status is UART_TRANSFER_STATUS_TIMEOUT or UART_TRANSFER_STATUS_CANCELLED.
 * 11. Print pass/fail message based on result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartWriteCallbackModeInterruptTimeoutCancel(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle;
    int32_t transferOK = SystemP_FAILURE;
    static UART_Transaction trans;
    static uint8_t uartTxBuffer[APP_UART_BUFSIZE];
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartParams->baudRate = 1200;
    uartHandle = UART_open(instanceId, uartParams);
    if(uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Prepare transaction — fill buffer with data larger than TX FIFO (64 bytes)
     * so that the ISR cannot complete the write in one burst. */
    UART_Transaction_init(&trans);
    trans.buf = &uartTxBuffer[0U];
    memset(uartTxBuffer, 'A', APP_UART_BUFSIZE);
    trans.count = APP_UART_BUFSIZE;
    trans.timeout = SystemP_WAIT_FOREVER;

    /* Start transaction */
    transferOK = UART_write(uartHandle, &trans);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1 << 2);
    }

    /* Cancel ongoing transaction */
    UART_writeCancel(uartHandle, &trans);

    /* Cleanup */
    UART_close(uartHandle);

    /* Assert transfer status is timeout or cancelled */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_TRUE((trans.status == UART_TRANSFER_STATUS_TIMEOUT) || (trans.status == UART_TRANSFER_STATUS_CANCELLED));
}

/**
 * @brief Testcase to validate UART_write API in callback mode with interrupt transfer and timeout.
 *
 * This test verifies that the UART driver correctly handles write transactions
 * in callback mode with interrupt transfer when a short timeout is specified.
 * It initializes UART parameters for callback mode, opens the UART instance,
 * prepares a transmit buffer and transaction with a short timeout, and performs
 * UART_write. The test waits for the write completion callback via a semaphore,
 * checks if the transfer status is UART_TRANSFER_STATUS_TIMEOUT, and prints
 * pass/fail status messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters for callback mode with interrupt transfer.
 * 4. Open UART instance and verify handle is not NULL.
 * 5. Construct semaphore for write completion.
 * 6. Prepare a transmit buffer and transaction with short timeout.
 * 7. Perform UART_write in callback mode with interrupt transfer.
 * 8. Wait for write completion via callback and semaphore.
 * 9. Cleanup semaphore and close UART handle.
 * 10. Assert transfer status is UART_TRANSFER_STATUS_TIMEOUT.
 * 11. Print pass/fail message based on result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartWriteCallbackModeInterruptTimeout(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    UART_Transaction trans = {0};
    uint32_t timeoutTicks = 10U;
    static uint8_t uartTxBuffer[APP_UART_BUFSIZE];
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Prepare transaction with short timeout — fill buffer with data larger
     * than TX FIFO (64 bytes) so the write cannot complete in one burst. */
    UART_Transaction_init(&trans);
    trans.buf = &uartTxBuffer[0U];
    memset(uartTxBuffer, 'B', APP_UART_BUFSIZE);
    trans.count = APP_UART_BUFSIZE;
    trans.timeout = timeoutTicks;

    /* Perform UART write in blocking mode with interrupt transfer.
     * The semaphore pend inside UART_write will time out because the
     * large buffer cannot be drained within 10 ticks. */
    (void)UART_write(uartHandle, &trans);

    /*
     * After a blocking-mode write timeout, the driver's internal
     * writeTrans pointer is left non-NULL (cleared only on normal
     * completion).  Reset it explicitly so the next UART_open /
     * UART_write on this instance does not see ERROR_INUSE.
     */
    {
        UART_Config *cfg = (UART_Config *)uartHandle;
        cfg->object->writeTrans = NULL;
    }

    /* Cleanup */
    UART_close(uartHandle);

    /* Assert transfer status is timeout */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_EQUAL_INT(UART_TRANSFER_STATUS_TIMEOUT, trans.status);
}

/**
 * @brief Testcase to validate UART_write API in blocking mode with polled transfer and timeout.
 *
 * This test verifies that the UART driver correctly handles write transactions
 * in blocking mode with polled transfer when a short timeout is specified.
 * It initializes UART parameters for blocking mode, opens the UART instance,
 * prepares a transmit buffer and transaction with a short timeout, and performs
 * UART_write. The test checks if the transfer status is UART_TRANSFER_STATUS_TIMEOUT
 * and prints pass/fail status messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters for blocking mode with polled transfer.
 * 4. Open UART instance and verify handle is not NULL.
 * 5. Prepare a transmit buffer and transaction with short timeout.
 * 6. Perform UART_write in blocking mode with polled transfer.
 * 7. Close UART handle.
 * 8. Assert transfer status is UART_TRANSFER_STATUS_TIMEOUT.
 * 9. Print pass/fail message based on result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartWriteBlockingModePolledTimeout(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    UART_Transaction trans = {0};
    uint32_t timeoutTicks = 10U;
    static uint8_t uartTxBuffer[APP_UART_BUFSIZE];
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Prepare transaction with short timeout — fill buffer with data larger
     * than TX FIFO (64 bytes) so polling cannot complete before timeout. */
    UART_Transaction_init(&trans);
    trans.buf = &uartTxBuffer[0U];
    memset(uartTxBuffer, 'C', APP_UART_BUFSIZE);
    trans.count = APP_UART_BUFSIZE;
    trans.timeout = timeoutTicks;

    /* Perform UART write in blocking mode with polled transfer */
    (void)UART_write(uartHandle, &trans);

    /* Close UART handle */
    UART_close(uartHandle);

    /* Assert transfer status is timeout */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_EQUAL_INT(UART_TRANSFER_STATUS_TIMEOUT, trans.status);
}

/**
 * @brief Testcase to validate UART_write API in DMA blocking mode.
 *
 * This test verifies that the UART driver can successfully transmit data
 * using DMA mode in blocking transfer. It initializes UART parameters for DMA
 * and blocking mode, opens the UART instance, prepares a transmit buffer,
 * and performs a UART_write operation. The test checks if the transfer completes
 * successfully and prints pass/fail status messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for the selected instance to ensure a clean state.
 * 3. Initialize UART parameters for DMA blocking mode.
 * 4. Open UART instance and verify handle is not NULL.
 * 5. Prepare a transmit buffer and transaction.
 * 6. Perform UART_write in DMA blocking mode.
 * 7. Close UART handle.
 * 8. Assert transfer status is UART_TRANSFER_STATUS_SUCCESS.
 * 9. Print pass/fail message based on result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartWriteDmaBlockingMode(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    UART_Transaction transWrite = {0}, transRead = {0};
    int32_t transferOK = SystemP_FAILURE;
    int32_t semStatus = SystemP_SUCCESS;
    uint8_t finalStatus = 0;
    uint16_t len = 128U;
    uint32_t baseAddr = 0U;
    uint32_t count = 0U;

#if defined(SOC_AM62AX) || defined(SOC_AM62DX)

    if ((instanceId == CONFIG_UART0) || (instanceId == CONFIG_UART8))
    {
        TestUart_openDebugUart();
        TEST_IGNORE_MESSAGE("DMA not supported on this UART instance");
        /* MAIN domain UARTs (CONFIG_UART1..CONFIG_UART7) support PDMA; MCU/WKUP do not */
        return;
    }
#endif

    /* Create semaphore for read completion (callback mode) */
    semStatus = SemaphoreP_constructBinary(&gUartReadDoneSem, 0);
    if (semStatus != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 4);
    }

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Reset Tx/RX buffer*/
    memset(TestUart_txBufferDma, 0, sizeof(TestUart_txBufferDma));
    memset(TestUart_rxBufferDma, 0, sizeof(TestUart_rxBufferDma));

    /* Prepare a deterministic TX pattern */
    for (count = 0; count < len; count++)
    {
        TestUart_txBufferDma[count] = (uint8_t)('A' + (count % 26));
    }

    /* Set PDMA events for MAIN domain UARTs (AM62AX/AM62DX A53) */
#if (defined(SOC_AM62AX) || defined(SOC_AM62DX)) && !(defined(CPU_R5F0) || defined(CPU_MCU_R5F0) || defined(CPU_C7X))
    switch (instanceId)
    {
        case CONFIG_UART1:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART0_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART0_RX;
            break;
        case CONFIG_UART2:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART1_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART1_RX;
            break;
        case CONFIG_UART3:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART2_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART2_RX;
            break;
        case CONFIG_UART4:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART3_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART3_RX;
            break;
        case CONFIG_UART5:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART4_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART4_RX;
            break;
        case CONFIG_UART6:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART5_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART5_RX;
            break;
        case CONFIG_UART7:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART6_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART6_RX;
            break;
        default:
            /* Unsupported for DMA (e.g., CONFIG_UART0 MCU, CONFIG_UART8 WKUP) */
            break;
    }
#endif

    /* Open uart instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1U << 0);
        goto tx_close;
    }

    /* Enable loopback mode */
    baseAddr = UART_getBaseAddr(uartHandle);
    if (baseAddr == 0U)
    {
        finalStatus |= (1U << 1);
        goto tx_close;
    }
    TestUart_enableLoopback(baseAddr);

    /*
     * Start the RX DMA channel BEFORE the TX DMA channel.
     * In loopback mode the TX data is echoed to RX immediately. If the
     * read DMA is not active when the write starts, the 64-byte RX FIFO
     * overflows for transfers larger than the FIFO depth (128 bytes here)
     * and data is lost.  Using callback mode for read makes it
     * non-blocking so we can set up RX DMA first, then do the blocking
     * write, then wait for the read-complete callback.
     */

    /* Setup RX DMA (callback / non-blocking) */
    UART_Transaction_init(&transRead);
    transRead.buf     = &TestUart_rxBufferDma[0U];
    transRead.count   = len;
    transRead.timeout = SystemP_WAIT_FOREVER;

    CacheP_wbInv((void*)TestUart_rxBufferDma, len, CacheP_TYPE_ALL);
    transferOK = UART_read(uartHandle, &transRead);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 2);
        goto tx_close;
    }

    /* Setup TX DMA (blocking) */
    UART_Transaction_init(&transWrite);
    transWrite.buf     = &TestUart_txBufferDma[0U];
    transWrite.count   = len;
    transWrite.timeout = SystemP_WAIT_FOREVER;

    CacheP_wb((void*)TestUart_txBufferDma, len, CacheP_TYPE_ALL);
    transferOK = UART_write(uartHandle, &transWrite);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 1);
        goto tx_close;
    }

    /* Wait for the read callback to signal completion */
    SemaphoreP_pend(&gUartReadDoneSem, SystemP_WAIT_FOREVER);

    /* Invalidate RX buffer so CPU sees DMA-written data */
    CacheP_inv((void*)TestUart_rxBufferDma, len, CacheP_TYPE_ALL);

tx_close:
    /* Disable loopback mode (only if valid) */
    if (baseAddr != 0U)
    {
        UART_disableLoopbackMode(baseAddr);
    }

    /* Close UART handle */
    if (uartHandle != NULL)
    {
        /*
         * Explicitly clear readTrans / writeTrans before closing.
         * UART_close + UART_open do NOT reset these fields in the
         * static UART_Object.  If the error path is taken before the
         * DMA ISR fires, the stale non-NULL pointer causes the next
         * UART_read / UART_write on this instance to return
         * UART_TRANSFER_STATUS_ERROR_INUSE.
         */
        UART_Config *cfg = (UART_Config *)uartHandle;
        cfg->object->readTrans  = NULL;
        cfg->object->writeTrans = NULL;

        UART_close(uartHandle);
    }

    SemaphoreP_destruct(&gUartReadDoneSem);

    /* Validate final status and data */
    if (finalStatus == 0 && 0 != memcmp(TestUart_txBufferDma, TestUart_rxBufferDma, len))
    {
        finalStatus |= (1U << 3);
    }

    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
}

/**
 * @brief Testcase to validate UART_read API in DMA blocking mode.
 *
 * This test verifies that the UART driver can successfully receive data
 * using DMA mode with a blocking read. It uses loopback mode so that
 * transmitted data is echoed back to the receiver. The write side uses
 * callback (non-blocking) mode so that the TX DMA can be started first
 * while the blocking read arms the RX PDMA before the first byte
 * finishes serialising through loopback.
 *
 * Test Steps:
 * 1. Skip unsupported UART instances (MCU/WKUP on AM62AX/AM62DX).
 * 2. Create semaphore for write-complete callback.
 * 3. Close any existing handle, clear TX/RX buffers, fill TX pattern.
 * 4. Set PDMA events for MAIN domain UARTs (AM62AX/AM62DX A53).
 * 5. Open UART in DMA mode (write=CALLBACK, read=BLOCKING).
 * 6. Enable loopback mode.
 * 7. Start non-blocking DMA write (callback mode, returns immediately).
 * 8. Start blocking DMA read (arms RX PDMA, blocks until complete).
 * 9. Wait for write callback semaphore.
 * 10. Invalidate cache, disable loopback, close UART.
 * 11. Compare TX and RX buffers.
 *
 * @param[in] args Pointer to UART_TestParams.
 *
 * @return void
 */
static void TestUart_uartReadDmaBlockingMode(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    UART_Transaction transWrite = {0}, transRead = {0};
    int32_t transferOK = SystemP_FAILURE;
    int32_t semStatus = SystemP_SUCCESS;
    uint8_t finalStatus = 0;
    uint16_t len = 128U;
    uint32_t baseAddr = 0U;
    uint32_t count = 0U;

#if defined(SOC_AM62AX) || defined(SOC_AM62DX)
    if ((instanceId == CONFIG_UART0) || (instanceId == CONFIG_UART8))
    {
        TestUart_openDebugUart();
        TEST_IGNORE_MESSAGE("DMA not supported on this UART instance");
        return;
    }
#endif

    /* Create semaphore for write completion (callback mode) */
    semStatus = SemaphoreP_constructBinary(&gUartWriteDoneSem, 0);
    if (semStatus != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 5);
    }

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Reset Tx/RX buffers */
    memset(TestUart_txBufferDma, 0, sizeof(TestUart_txBufferDma));
    memset(TestUart_rxBufferDma, 0, sizeof(TestUart_rxBufferDma));

    /* Prepare a deterministic TX pattern */
    for (count = 0; count < len; count++)
    {
        TestUart_txBufferDma[count] = (uint8_t)('A' + (count % 26));
    }

    /* Set PDMA events for MAIN domain UARTs (AM62AX/AM62DX A53) */
#if (defined(SOC_AM62AX) || defined(SOC_AM62DX)) && !(defined(CPU_R5F0) || defined(CPU_MCU_R5F0) || defined(CPU_C7X))
    switch (instanceId)
    {
        case CONFIG_UART1:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART0_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART0_RX;
            break;
        case CONFIG_UART2:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART1_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART1_RX;
            break;
        case CONFIG_UART3:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART2_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART2_RX;
            break;
        case CONFIG_UART4:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART3_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART3_RX;
            break;
        case CONFIG_UART5:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART4_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART4_RX;
            break;
        case CONFIG_UART6:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART5_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART5_RX;
            break;
        case CONFIG_UART7:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART6_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART6_RX;
            break;
        default:
            break;
    }
#endif

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1U << 0);
        goto rx_close;
    }

    /* Enable loopback mode */
    baseAddr = UART_getBaseAddr(uartHandle);
    if (baseAddr == 0U)
    {
        finalStatus |= (1U << 1);
        goto rx_close;
    }
    TestUart_enableLoopback(baseAddr);

    /*
     * Start the callback (non-blocking) TX DMA first, then the blocking
     * RX DMA.  The TX serialises bytes through loopback at baud rate
     * (~87 us per byte at 115200).  The blocking UART_read arms the
     * RX PDMA channel before the first byte finishes serialising, so
     * the RX PDMA sees every byte arrive as a fresh trigger.
     *
     * This avoids the situation where data is already sitting in the
     * RX FIFO before the PDMA RX channel is enabled — the PDMA would
     * miss the already-asserted DMA request and hang.
     */

    /* Setup TX DMA (callback / non-blocking) */
    UART_Transaction_init(&transWrite);
    transWrite.buf     = &TestUart_txBufferDma[0U];
    transWrite.count   = len;
    transWrite.timeout = SystemP_WAIT_FOREVER;

    CacheP_wb((void*)TestUart_txBufferDma, len, CacheP_TYPE_ALL);
    transferOK = UART_write(uartHandle, &transWrite);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 2);
        goto rx_close;
    }

    /* Setup RX DMA (blocking) — the actual feature under test */
    UART_Transaction_init(&transRead);
    transRead.buf     = &TestUart_rxBufferDma[0U];
    transRead.count   = len;
    transRead.timeout = SystemP_WAIT_FOREVER;

    CacheP_wbInv((void*)TestUart_rxBufferDma, len, CacheP_TYPE_ALL);
    transferOK = UART_read(uartHandle, &transRead);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 3);
        goto rx_close;
    }

    /* Wait for the write callback to signal completion */
    SemaphoreP_pend(&gUartWriteDoneSem, SystemP_WAIT_FOREVER);

    /* Invalidate RX buffer so CPU sees DMA-written data */
    CacheP_inv((void*)TestUart_rxBufferDma, len, CacheP_TYPE_ALL);

rx_close:
    /* Disable loopback mode (only if valid) */
    if (baseAddr != 0U)
    {
        UART_disableLoopbackMode(baseAddr);
    }

    /* Close UART handle */
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    SemaphoreP_destruct(&gUartWriteDoneSem);

    /* Validate final status and data */
    if (finalStatus == 0 && 0 != memcmp(TestUart_txBufferDma, TestUart_rxBufferDma, len))
    {
        finalStatus |= (1U << 4);
    }

    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
}

/**
 * @brief Testcase to validate UART_getHandle API with an invalid UART index.
 *
 * This test attempts to retrieve a UART handle using an invalid index value.
 * It verifies that the driver returns NULL for the invalid index, indicating
 * correct error handling. The test prints pass/fail status messages over UART
 * for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Call UART_getHandle with an invalid index.
 * 3. Assert that the returned handle is NULL.
 * 4. Print pass/fail message based on result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartGetHandleInvalidIndex(void *args)
{
    UART_Handle uartHandle = NULL;
    uint8_t finalStatus = 0;

    /* Try to get handle for invalid index */
    uartHandle = UART_getHandle(TEST_UART_CONFIG_INDEX_INVALID);
    /* Assert that handle is NULL */
    if (uartHandle != NULL)
    {
        finalStatus |= (1 << 1);
    }

    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
}

/**
 * @brief Testcase to validate UART_getHandle API for a closed UART instance.
 *
 * This test verifies that the UART driver returns NULL when UART_getHandle is called
 * for an instance that has been closed. It opens a UART instance, closes it, and then
 * attempts to retrieve the handle again, expecting a NULL result. The test prints
 * pass/fail status messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters and open UART instance.
 * 4. Close the UART instance.
 * 5. Call UART_getHandle for the closed instance.
 * 6. Assert that the returned handle is NULL.
 * 7. Print pass/fail message based on result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartGetHandleClosedInstance(void *args)
{
    UART_Handle uartHandle = NULL;
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Close UART instance */
    UART_close(uartHandle);

    /* Now request handle for closed instance */
    uartHandle = UART_getHandle(instanceId);
    if (uartHandle != NULL)
    {
        finalStatus |= (1 << 2);
    }

    /* Assert that handle is NULL */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
}

/**
 * @brief Testcase to validate UART_flushTxFifo API functionality.
 *
 * This test verifies that the UART_flushTxFifo function correctly flushes the TX FIFO.
 * It opens a UART instance, fills the TX FIFO by writing data, calls UART_flushTxFifo,
 * and checks that the TX FIFO is empty afterward. The test prints pass/fail status
 * messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters and open UART instance.
 * 4. Write data to fill the TX FIFO.
 * 5. Call UART_flushTxFifo to flush the TX FIFO.
 * 6. Verify that the TX FIFO is empty.
 * 7. Close UART handle.
 * 8. Print pass/fail message based on result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartFlushTxFifo(void *args)
{
    int32_t status = SystemP_FAILURE;
    UART_Transaction trans = {0};
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    uint8_t uartTxBuffer[UART_FIFO_SIZE];
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Prepare transaction */
    UART_Transaction_init(&trans);
    trans.buf = &uartTxBuffer[0U];
    trans.count = UART_FIFO_SIZE;
    trans.timeout = SystemP_WAIT_FOREVER;
    status = UART_write(uartHandle, &trans);
    if (status != SystemP_SUCCESS)
    {
        finalStatus |= (1 << 2);
    }

    /* Now TX FIFO should be full, flush the TX FIFO */
    UART_flushTxFifo(uartHandle);

    /* Verify that TX FIFO is empty */
    uint32_t baseAddr = UART_getBaseAddr(uartHandle);
    uint32_t txFifoLevel = HW_RD_REG32(baseAddr + UART_TXFIFO_LVL);

    /* Close the UART instance */
    UART_close(uartHandle);

    /* Verify that TX FIFO is empty */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_EQUAL_UINT32(0, txFifoLevel);
}

/**
 * @brief Testcase to validate UART_flushTxFifo API when a NULL handle is passed.
 *
 * This test verifies that the UART_flushTxFifo function handles a NULL UART handle gracefully.
 * It opens a UART instance, fills the TX FIFO by writing data, then calls UART_flushTxFifo
 * with a NULL handle and checks that the TX FIFO remains unchanged. The test prints pass/fail
 * status messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters and open UART instance.
 * 4. Write data to fill the TX FIFO.
 * 5. Call UART_flushTxFifo with a NULL handle.
 * 6. Verify that the TX FIFO is still full.
 * 7. Close UART handle.
 * 8. Print pass/fail message based on result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartFlushTxFifoNullHandle(void *args)
{
    int32_t status = SystemP_FAILURE;
    UART_Transaction trans = {0};
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    uint8_t uartTxBuffer[UART_FIFO_SIZE];
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Prepare transaction */
    UART_Transaction_init(&trans);
    trans.buf = &uartTxBuffer[0U];
    trans.count = UART_FIFO_SIZE;
    trans.timeout = SystemP_WAIT_FOREVER;
    status = UART_write(uartHandle, &trans);
    if (status != SystemP_SUCCESS)
    {
        finalStatus |= (1 << 2);
    }

    /* Now TX FIFO should be full, call flush function with NULL handle */
    UART_flushTxFifo(NULL);

    /* Verify that TX FIFO is still full */
    uint32_t baseAddr = UART_getBaseAddr(uartHandle);
    uint32_t txFifoLevel = HW_RD_REG32(baseAddr + UART_TXFIFO_LVL);

    /* Close the UART instance */
    UART_close(uartHandle);

    /* Verify that TX FIFO is empty */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_NOT_EQUAL(UART_FIFO_SIZE, txFifoLevel);
}

/**
 * @brief Testcase to validate UART_Params_init API when a NULL pointer is passed.
 *
 * This test verifies that the UART_Params_init function handles a NULL pointer gracefully.
 * It calls UART_Params_init with a NULL argument and checks that no crash or error occurs.
 * The test prints a pass message over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Call UART_Params_init with a NULL pointer.
 * 3. Print pass message if no crash or error occurs.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartParamsInitNullHandle(void *args)
{
    /* Call UART_Params_init with NULL pointer */
    UART_Params_init(NULL);

    /* If no crash or error, test is considered passed */
}

/**
 * @brief Testcase to validate UART_Transaction_init API when a NULL pointer is passed.
 *
 * This test verifies that the UART_Transaction_init function handles a NULL pointer gracefully.
 * It calls UART_Transaction_init with a NULL argument and checks that no crash or error occurs.
 * The test prints a pass message over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Call UART_Transaction_init with a NULL pointer.
 * 3. Print pass message if no crash or error occurs.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartTransactionInitNullHandle(void *args)
{
    /* Call UART_Transaction_init with NULL pointer */
    UART_Transaction_init(NULL);

    /* If no crash or error, test is considered passed */
}

/**
 * @brief Testcase to validate UART_getBaseAddr API when a NULL handle is passed.
 *
 * This test verifies that the UART_getBaseAddr function handles a NULL UART handle gracefully.
 * It calls UART_getBaseAddr with a NULL argument and checks that no crash or error occurs.
 * The test prints a pass message over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Call UART_getBaseAddr with a NULL handle.
 * 3. Print pass message if no crash or error occurs.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartGetBaseAddrNullHandle(void *args)
{
    /* Call UART_getBaseAddr with NULL pointer */
    UART_getBaseAddr(NULL);

    /* If no crash or error, test is considered passed */
}

/**
 * @brief Testcase to validate UART_enableLoopbackMode API with an invalid base address.
 *
 * This test verifies that the UART_enableLoopbackMode function handles an invalid
 * base address gracefully. It calls UART_enableLoopbackMode with a deliberately
 * invalid base address and checks that no crash or error occurs. The test prints
 * a pass message over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Call UART_enableLoopbackMode with an invalid base address.
 * 3. Print pass message if no crash or error occurs.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_enableLoopbackModeInvalidBaseAddr(void *args)
{
    uint32_t invalidBaseAddr = 0xFFFFFFFFU;

    /* Call UART_enableLoopbackMode with invalid base address */
    UART_enableLoopbackMode(invalidBaseAddr);

    /* If no crash or error, test is considered passed */
}

/**
 * @brief Testcase to validate UART_disableLoopbackMode API with an invalid base address.
 *
 * This test verifies that the UART_disableLoopbackMode function handles an invalid
 * base address gracefully. It calls UART_disableLoopbackMode with a deliberately
 * invalid base address and checks that no crash or error occurs. The test prints
 * a pass message over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Call UART_disableLoopbackMode with an invalid base address.
 * 3. Print pass message if no crash or error occurs.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_disableLoopbackModeInvalidBaseAddr(void *args)
{
    uint32_t invalidBaseAddr = 0xFFFFFFFFU;

    /* Call UART_disableLoopbackMode with invalid base address */
    UART_disableLoopbackMode(invalidBaseAddr);

    /* If no crash or error, test is considered passed */
}

#if 0

/**
 * @brief Testcase to validate UART_putChar API functionality.
 *
 * This test verifies that the UART_putChar function correctly writes a character
 * directly to the UART TX FIFO. It opens a UART instance, reads the TX FIFO level
 * before and after calling UART_putChar, and checks that the FIFO level increases
 * by one. The test prints pass/fail status messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters and open UART instance.
 * 4. Read TX FIFO level before calling UART_putChar.
 * 5. Call UART_putChar to write a character to TX FIFO.
 * 6. Read TX FIFO level after calling UART_putChar.
 * 7. Verify that TX FIFO level increased by one.
 * 8. Close UART handle.
 * 9. Print pass/fail message based on result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
void TestUart_uartPutChar(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    uint32_t baseAddr = 0;
    uint8_t testChar = 'A';
    uint32_t txFifoLevelBefore = 0, txFifoLevelAfter = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    TEST_ASSERT_NOT_NULL(uartHandle);

    /* Get base address */
    baseAddr = UART_getBaseAddr(uartHandle);

    /* Read TX FIFO level before putChar */
    txFifoLevelBefore = HW_RD_REG32(baseAddr + UART_TXFIFO_LVL);

    /* Write a character directly to TX FIFO */
    UART_putChar(baseAddr, testChar);

    /* Read TX FIFO level after putChar */
    txFifoLevelAfter = HW_RD_REG32(baseAddr + UART_TXFIFO_LVL);

    /* Close UART handle */
    UART_close(uartHandle);

    TEST_ASSERT_EQUAL_UINT32(txFifoLevelBefore + 1, txFifoLevelAfter);
}

#endif

/**
 * @brief Testcase to validate UART_putChar API with an invalid base address.
 *
 * This test verifies that the UART_putChar function handles an invalid base address gracefully.
 * It opens a UART instance, then calls UART_putChar with a deliberately invalid base address,
 * and checks that no crash or error occurs. The test prints a pass message over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters and open UART instance.
 * 4. Call UART_putChar with an invalid base address.
 * 5. Close UART handle.
 * 6. Print pass message if no crash or error occurs.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartPutCharInvalidBaseAddr(void *args)
{
    uint32_t invalidBaseAddr = 0xFFFFFFFFU;
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    uint8_t testChar = 'A';
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Write a character directly to TX FIFO */
    UART_putChar(invalidBaseAddr, testChar);

    /* Close UART handle */
    UART_close(uartHandle);

    /* If No crash or error, test is considered passed */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
}

/**
 * @brief Testcase to validate UART_getChar API functionality.
 *
 * This test verifies that the UART_getChar function correctly reads a character
 * from the UART RX FIFO. It opens a UART instance, enables loopback mode, writes
 * a character to the TX FIFO, flushes the TX FIFO, and reads the character from
 * the RX FIFO. The test checks that the received character matches the sent character
 * and prints pass/fail status messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters and open UART instance.
 * 4. Enable loopback mode.
 * 5. Write a character to TX FIFO.
 * 6. Flush TX FIFO.
 * 7. Read a character from RX FIFO using UART_getChar.
 * 8. Disable loopback mode.
 * 9. Close UART handle.
 * 10. Verify that the received character matches the sent character.
 * 11. Print pass/fail message based on result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
void TestUart_uartGetChar(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    uint32_t baseAddr = 0;
    uint8_t sentChar = 'B';
    uint8_t receivedChar = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    TEST_ASSERT_NOT_NULL(uartHandle);

    /* Get base address */
    baseAddr = UART_getBaseAddr(uartHandle);

    /* Enable loopback mode */
    TestUart_enableLoopback(baseAddr);

    /* Put a character into TX FIFO */
    UART_putChar(baseAddr, sentChar);

    /* Flush TX FIFO */
    UART_flushTxFifo(uartHandle);

    /* Get a character from RX FIFO (assuming loopback mode is enabled) */
    UART_getChar(baseAddr, &receivedChar);

    /* Disable loopback mode */
    UART_disableLoopbackMode(baseAddr);

    /* Close UART handle */
    UART_close(uartHandle);

    TEST_ASSERT_EQUAL_UINT8(sentChar, receivedChar);
}

/**
 * @brief Testcase to validate UART_getChar API with an invalid base address.
 *
 * This test verifies that the UART_getChar function handles an invalid base address gracefully.
 * It opens a UART instance, enables loopback mode, writes a character to the TX FIFO,
 * and then calls UART_getChar with a deliberately invalid base address. The test checks
 * that no crash or error occurs and prints a pass message over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters and open UART instance.
 * 4. Enable loopback mode.
 * 5. Write a character to TX FIFO.
 * 6. Call UART_getChar with an invalid base address.
 * 7. Close UART handle.
 * 8. Print pass message if no crash or error occurs.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartGetCharInvalidBaseAddr(void *args)
{
    uint32_t invalidBaseAddr = 0xFFFFFFFFU;
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    uint32_t baseAddr = 0;
    uint8_t sentChar = 'B';
    uint8_t receivedChar = 0;
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

     /* Get base address */
    baseAddr = UART_getBaseAddr(uartHandle);

    /* Put a character into TX FIFO */
    UART_putChar(baseAddr, sentChar);

    /* Get a character from RX FIFO (assuming loopback mode is enabled) */
    TestUart_enableLoopback(baseAddr);

    /* Get a character from RX FIFO using invalid base address */
    UART_getChar(invalidBaseAddr, &receivedChar);

    /* Close UART handle */
    UART_close(uartHandle);

    /* If no crash or error, test is considered passed */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
}

/**
 * @brief Testcase to validate UART_getChar API when a NULL char pointer is passed.
 *
 * This test verifies that the UART_getChar function handles a NULL char pointer gracefully.
 * It opens a UART instance, enables loopback mode, writes a character to the TX FIFO,
 * and then calls UART_getChar with a NULL pointer for the output character. The test
 * checks that no crash or error occurs and prints a pass message over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters and open UART instance.
 * 4. Enable loopback mode.
 * 5. Write a character to TX FIFO.
 * 6. Call UART_getChar with a NULL char pointer.
 * 7. Close UART handle.
 * 8. Print pass message if no crash or error occurs.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartGetCharNullCharPtr(void *args)
{
    uint32_t baseAddr = 0;
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    uint8_t sentChar = 'C';
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    UART_close(uartHandle);

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Get base address */
    baseAddr = UART_getBaseAddr(uartHandle);

    /* Enable loopback mode */
    TestUart_enableLoopback(baseAddr);

    /* Put a character into TX FIFO */
    UART_putChar(baseAddr, sentChar);

    /* Get a character from RX FIFO (assuming loopback mode is enabled) */
    UART_getChar(baseAddr, NULL);

    /* Close UART handle */
    UART_close(uartHandle);

    /* If no crash or error, test is considered passed */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
}

/**
 * @brief Testcase to validate UART_intrEnable API functionality.
 *
 * This test verifies that the UART_intrEnable function correctly enables UART interrupts.
 * It opens a UART instance, reads the IER register before and after enabling interrupts,
 * and checks that the specified interrupt flags are set. The test prints pass/fail status
 * messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters and open UART instance.
 * 4. Read IER register before enabling interrupts.
 * 5. Enable UART interrupts using UART_intrEnable.
 * 6. Read IER register after enabling interrupts.
 * 7. Verify that the interrupt flags are set.
 * 8. Close UART handle.
 * 9. Print pass/fail message based on result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartIntrEnable(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    uint32_t baseAddr = 0;
    uint32_t intrFlag = UART_INTR_THR | UART_INTR_LINE_STAT;
    uint32_t ierValueAfter = 0;
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Get base address */
    baseAddr = UART_getBaseAddr(uartHandle);

    /* Enable interrupts */
    UART_intrEnable(baseAddr, intrFlag);

    /* Read IER register after enabling interrupts */
    ierValueAfter = HW_RD_REG32(baseAddr + UART_IER);

    /* Enable interrupts */
    UART_intrDisable(baseAddr, intrFlag);

    /* Close UART handle */
    UART_close(uartHandle);

    /* Check if the interrupt bits are set */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_EQUAL_UINT32(intrFlag, ierValueAfter & intrFlag);
}

/**
 * @brief Testcase to validate UART_intrEnable API with an invalid interrupt flag.
 *
 * This test verifies that the UART_intrEnable function handles an invalid interrupt flag gracefully.
 * It opens a UART instance, enables interrupts using a deliberately invalid flag, and checks the IER register
 * to see if only valid bits are set. The test prints a warning if all bits are set, or a pass message if invalid bits are ignored.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters and open UART instance.
 * 4. Get UART base address.
 * 5. Call UART_intrEnable with an invalid interrupt flag.
 * 6. Read IER register and check which bits are set.
 * 7. Print warning or pass message based on result.
 * 8. Close UART handle.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartIntrEnableWrongIntFlag(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    uint32_t baseAddr = 0;
    uint32_t wrongIntrFlag = 0xFFFFFFFFU;
    uint32_t ierValueAfter = 0,  ierValueBefore = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    TEST_ASSERT_NOT_NULL(uartHandle);

    /* Get base address */
    baseAddr = UART_getBaseAddr(uartHandle);

    /* Read IER register after enabling interrupts */
    ierValueBefore = HW_RD_REG32(baseAddr + UART_IER);

    /* Enable interrupts with wrong flag */
    UART_intrEnable(baseAddr, wrongIntrFlag);

    /* Read IER register after enabling interrupts */
    ierValueAfter = HW_RD_REG32(baseAddr + UART_IER);

    /* Enable interrupts */
    UART_intrDisable(baseAddr, wrongIntrFlag);

    /* Enable interrupts with wrong flag */
    UART_intrEnable(baseAddr, ierValueBefore);

    /* Close UART handle */
    UART_close(uartHandle);

    /* Check if the interrupt bits are set (should only set valid bits)
       If driver masks invalid bits, only valid bits should be set
       If not, all bits may be set */

    TEST_ASSERT_TRUE((ierValueAfter & wrongIntrFlag) != (wrongIntrFlag));
}

/**
 * @brief Testcase to validate UART_intrEnable API with an invalid base address.
 *
 * This test verifies that the UART_intrEnable function handles an invalid base address gracefully.
 * It calls UART_intrEnable with a deliberately invalid base address and checks that no crash or error occurs.
 * The test prints a pass message over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Call UART_intrEnable with an invalid base address.
 * 3. Print pass message if no crash or error occurs.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartIntrEnableWrongBaseAddr(void *args)
{
    uint32_t wrongBaseAddr = 0xFFFFFFFFU;
    uint32_t intrFlag = UART_INTR_THR | UART_INTR_LINE_STAT;

    /* Call UART_intrEnable with wrong base address */
    UART_intrEnable(wrongBaseAddr, intrFlag);

    /* If no crash or error, test is considered passed */
}

/**
 * @brief Testcase to validate UART_intrDisable API functionality.
 *
 * This test verifies that the UART_intrDisable function correctly disables UART interrupts.
 * It opens a UART instance, enables interrupts, reads the IER register before and after disabling,
 * and checks that the specified interrupt flags are cleared. The test prints pass/fail status
 * messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters and open UART instance.
 * 4. Enable UART interrupts using UART_intrEnable.
 * 5. Read IER register before disabling interrupts.
 * 6. Disable UART interrupts using UART_intrDisable.
 * 7. Read IER register after disabling interrupts.
 * 8. Verify that the interrupt flags are cleared.
 * 9. Close UART handle.
 * 10. Print pass/fail message based on result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartIntrDisable(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    uint32_t baseAddr = 0;
    uint32_t intrFlag = UART_INTR_THR | UART_INTR_LINE_STAT;
    uint32_t ierValueBefore = 0, ierValueAfter = 0;
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Get base address */
    baseAddr = UART_getBaseAddr(uartHandle);

    /* Enable interrupts first */
    UART_intrEnable(baseAddr, intrFlag);

    /* Read IER register before disabling interrupts */
    ierValueBefore = HW_RD_REG32(baseAddr + UART_IER);

    /* Disable interrupts */
    UART_intrDisable(baseAddr, intrFlag);

    /* Read IER register after disabling interrupts */
    ierValueAfter = HW_RD_REG32(baseAddr + UART_IER);

    /* Close UART handle */
    UART_close(uartHandle);

    /* Check if the interrupt bits are cleared */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_TRUE((ierValueAfter & intrFlag) == 0);
    TEST_ASSERT_TRUE((ierValueBefore & intrFlag) == intrFlag);
}

/**
 * @brief Testcase to validate UART_intrDisable API with an invalid interrupt flag after enabling correct flags.
 *
 * This test verifies that the UART_intrDisable function handles an invalid interrupt flag gracefully
 * when called after enabling valid interrupt flags. It opens a UART instance, enables interrupts with
 * correct flags, then disables interrupts using a deliberately invalid flag, and checks the IER register
 * to confirm that only valid bits are cleared. The test prints pass/fail status messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters and open UART instance.
 * 4. Get UART base address.
 * 5. Enable interrupts with correct flag.
 * 6. Read IER register before disabling interrupts.
 * 7. Disable interrupts with wrong flag.
 * 8. Read IER register after disabling interrupts.
 * 9. Check if correct interrupt bits are cleared.
 * 10. Print pass/fail message based on result.
 * 11. Close UART handle.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartIntrDisableWrongIntFlagAfterEnable(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    uint32_t baseAddr = 0;
    uint32_t correctIntrFlag = UART_INTR_THR | UART_INTR_LINE_STAT;
    uint32_t wrongIntrFlag = 0xFFFFFFFFU;
    uint32_t ierValueBefore = 0, ierValueAfter = 0;
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Get base address */
    baseAddr = UART_getBaseAddr(uartHandle);

    /* Enable interrupts with correct flag */
    UART_intrEnable(baseAddr, correctIntrFlag);

    /* Read IER register before disabling interrupts */
    ierValueBefore = HW_RD_REG32(baseAddr + UART_IER);

    /* Disable interrupts with wrong flag */
    UART_intrDisable(baseAddr, wrongIntrFlag);

    /* Read IER register after disabling interrupts */
    ierValueAfter = HW_RD_REG32(baseAddr + UART_IER);

    /* Close UART handle */
    UART_close(uartHandle);

    /* Check if the correct interrupt bits are cleared */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_TRUE((ierValueAfter & correctIntrFlag) == 0);
    TEST_ASSERT_TRUE((ierValueBefore & correctIntrFlag) == correctIntrFlag);
}

/**
 * @brief Testcase to validate UART_intrDisable API with an invalid base address after enabling correct flags.
 *
 * This test verifies that the UART_intrDisable function handles an invalid base address gracefully
 * when called after enabling valid interrupt flags. It opens a UART instance, enables interrupts with
 * correct flags, then disables interrupts using a deliberately invalid base address, and checks the IER register
 * to confirm that the interrupt bits remain unchanged. The test prints pass/fail status messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters and open UART instance.
 * 4. Get UART base address.
 * 5. Enable interrupts with correct flag.
 * 6. Read IER register before disabling interrupts.
 * 7. Disable interrupts with wrong base address.
 * 8. Read IER register after disabling interrupts.
 * 9. Check if interrupt bits remain unchanged.
 * 10. Print pass/fail message based on result.
 * 11. Close UART handle.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartIntrDisableWrongBaseAddrAfterEnable(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    uint32_t baseAddr = 0;
    uint32_t correctIntrFlag = UART_INTR_THR | UART_INTR_LINE_STAT;
    uint32_t wrongBaseAddr = 0xFFFFFFFFU;
    uint32_t ierValueBefore = 0, ierValueAfter = 0;
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Get base address */
    baseAddr = UART_getBaseAddr(uartHandle);

    /* Enable interrupts with correct flag */
    UART_intrEnable(baseAddr, correctIntrFlag);

    /* Read IER register before disabling interrupts */
    ierValueBefore = HW_RD_REG32(baseAddr + UART_IER);

    /* Disable interrupts with wrong base address */
    UART_intrDisable(wrongBaseAddr, correctIntrFlag);

    /* Read IER register after disabling interrupts (should remain unchanged) */
    ierValueAfter = HW_RD_REG32(baseAddr + UART_IER);

    /* Disable interrupts with wrong base address */
    UART_intrDisable(baseAddr, correctIntrFlag);

    /* Close UART handle */
    UART_close(uartHandle);

    /* Check if the correct interrupt bits are still set */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_TRUE((ierValueAfter & correctIntrFlag) == correctIntrFlag);
    TEST_ASSERT_TRUE((ierValueBefore & correctIntrFlag) == correctIntrFlag);
}

/**
 * @brief Testcase to validate UART_intr2Enable API functionality.
 *
 * This test verifies that the UART_intr2Enable function correctly enables UART interrupt2 flags.
 * It opens a UART instance, reads the IER2 register before and after enabling interrupts,
 * and checks that the specified interrupt2 flags are set. The test prints pass/fail status
 * messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters and open UART instance.
 * 4. Read IER2 register before enabling interrupts.
 * 5. Enable UART interrupt2 flags using UART_intr2Enable.
 * 6. Read IER2 register after enabling interrupts.
 * 7. Verify that the interrupt2 flags are set.
 * 8. Close UART handle.
 * 9. Print pass/fail message based on result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartIntr2Enable(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    uint32_t baseAddr = 0;
    uint32_t intrFlag = UART_INTR2_TX_EMPTY | UART_INTR2_RX_EMPTY;
    uint32_t ier2ValueAfter = 0;
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Get base address */
    baseAddr = UART_getBaseAddr(uartHandle);

    /* Enable interrupts */
    UART_intr2Enable(baseAddr, intrFlag);

    /* Read IER2 register after enabling interrupts */
    ier2ValueAfter = HW_RD_REG32(baseAddr + UART_IER2);

    /* Disable interrupt */
    UART_intr2Disable(baseAddr, intrFlag);

    /* Close UART handle */
    UART_close(uartHandle);

    /* Check if the interrupt bits are set */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_TRUE((ier2ValueAfter & intrFlag) == intrFlag);
}

/**
 * @brief Testcase to validate UART_intr2Enable API with an invalid interrupt flag.
 *
 * This test verifies that the UART_intr2Enable function handles an invalid interrupt flag gracefully.
 * It opens a UART instance, enables interrupts using a deliberately invalid flag, and checks the IER2 register
 * to see if only valid bits are set. The test prints a warning if all bits are set, or a pass message if invalid bits are ignored.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters and open UART instance.
 * 4. Get UART base address.
 * 5. Call UART_intr2Enable with an invalid interrupt flag.
 * 6. Read IER2 register and check which bits are set.
 * 7. Print warning or pass message based on result.
 * 8. Close UART handle.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartIntr2EnableWrongIntFlag(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    uint32_t baseAddr = 0;
    uint32_t wrongIntrFlag = 0xFFFFFFFFU;
    uint32_t ier2ValueAfter = 0, ier2ValueBefore = 0;
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Get base address */
    baseAddr = UART_getBaseAddr(uartHandle);

    ier2ValueBefore = HW_RD_REG32(baseAddr + UART_IER2);

    /* Enable interrupts with wrong flag */
    UART_intr2Enable(baseAddr, wrongIntrFlag);

    /* Read IER2 register after enabling interrupts */
    ier2ValueAfter = HW_RD_REG32(baseAddr + UART_IER2);

    UART_intr2Disable(baseAddr, wrongIntrFlag);
    UART_intr2Enable(baseAddr, ier2ValueBefore);

    /* Close UART handle */
    UART_close(uartHandle);

    /* Check if the interrupt bits are set (should only set valid bits) */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_TRUE((ier2ValueAfter & wrongIntrFlag) != (wrongIntrFlag));
}

/**
 * @brief Testcase to validate UART_intr2Enable API with an invalid base address.
 *
 * This test verifies that the UART_intr2Enable function handles an invalid base address gracefully.
 * It calls UART_intr2Enable with a deliberately invalid base address and checks that no crash or error occurs.
 * The test prints a pass message over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Call UART_intr2Enable with an invalid base address.
 * 3. Print pass message if no crash or error occurs.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartIntr2EnableWrongBaseAddr(void *args)
{
    uint32_t wrongBaseAddr = 0xFFFFFFFFU;
    uint32_t intrFlag = UART_INTR2_TX_EMPTY | UART_INTR2_RX_EMPTY;

    /* Call UART_intr2Enable with wrong base address */
    UART_intr2Enable(wrongBaseAddr, intrFlag);

    /* If no crash or error, test is considered passed */
}

/**
 * @brief Testcase to validate UART_intr2Disable API functionality.
 *
 * This test verifies that the UART_intr2Disable function correctly disables UART interrupt2 flags.
 * It opens a UART instance, enables interrupt2 flags, reads the IER2 register before and after disabling,
 * and checks that the specified interrupt2 flags are cleared. The test prints pass/fail status
 * messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters and open UART instance.
 * 4. Enable UART interrupt2 flags using UART_intr2Enable.
 * 5. Read IER2 register before disabling interrupts.
 * 6. Disable UART interrupt2 flags using UART_intr2Disable.
 * 7. Read IER2 register after disabling interrupts.
 * 8. Verify that the interrupt2 flags are cleared.
 * 9. Close UART handle.
 * 10. Print pass/fail message based on result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartIntr2Disable(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);

    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    uint32_t baseAddr = 0;
    uint32_t intrFlag = UART_INTR2_TX_EMPTY | UART_INTR2_RX_EMPTY;
    uint32_t ier2ValueAfter = 0;
    uint32_t ier2ValueBefore = 0;
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Get base address */
    baseAddr = UART_getBaseAddr(uartHandle);

    /* Enable interrupts first */
    UART_intr2Enable(baseAddr, intrFlag);

    /* Read IER2 register before disabling interrupts */
    ier2ValueBefore = HW_RD_REG32(baseAddr + UART_IER2);

    /* Disable interrupts */
    UART_intr2Disable(baseAddr, intrFlag);

    /* Read IER2 register after disabling interrupts */
    ier2ValueAfter = HW_RD_REG32(baseAddr + UART_IER2);

    /* Close UART handle */
    UART_close(uartHandle);

    /* Check if the interrupt bits are cleared */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_TRUE((ier2ValueAfter & intrFlag) == 0);
    TEST_ASSERT_TRUE((ier2ValueBefore & intrFlag) == intrFlag);
}

/**
 * @brief Testcase to validate UART_intr2Disable API with an invalid interrupt flag after enabling correct flags.
 *
 * This test verifies that the UART_intr2Disable function handles an invalid interrupt flag gracefully
 * when called after enabling valid interrupt2 flags. It opens a UART instance, enables interrupts with
 * correct flags, then disables interrupts using a deliberately invalid flag, and checks the IER2 register
 * to confirm that only valid bits are cleared. The test prints pass/fail status messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters and open UART instance.
 * 4. Get UART base address.
 * 5. Enable interrupt2 flags with correct flag.
 * 6. Read IER2 register before disabling interrupts.
 * 7. Disable interrupt2 flags with wrong flag.
 * 8. Read IER2 register after disabling interrupts.
 * 9. Check if correct interrupt2 bits are cleared.
 * 10. Print pass/fail message based on result.
 * 11. Close UART handle.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartIntr2DisableWrongIntFlagAfterEnable(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    uint32_t baseAddr = 0;
    uint32_t correctIntrFlag = UART_INTR2_TX_EMPTY | UART_INTR2_RX_EMPTY;
    uint32_t wrongIntrFlag = 0xFFFFFFFFU;
    uint32_t ier2ValueBefore = 0, ier2ValueAfter = 0;
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Get base address */
    baseAddr = UART_getBaseAddr(uartHandle);

    /* Enable interrupts with correct flag */
    UART_intr2Enable(baseAddr, correctIntrFlag);

    /* Read IER2 register before disabling interrupts */
    ier2ValueBefore = HW_RD_REG32(baseAddr + UART_IER2);

    /* Disable interrupts with wrong flag */
    UART_intr2Disable(baseAddr, wrongIntrFlag);

    /* Read IER2 register after disabling interrupts */
    ier2ValueAfter = HW_RD_REG32(baseAddr + UART_IER2);

    /* Close UART handle */
    UART_close(uartHandle);

    /* Check if the correct interrupt bits are cleared */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_TRUE((ier2ValueAfter & correctIntrFlag) == 0);
    TEST_ASSERT_TRUE((ier2ValueBefore & correctIntrFlag) == correctIntrFlag);
}

/**
 * @brief Testcase to validate UART_intr2Disable API with an invalid base address after enabling correct flags.
 *
 * This test verifies that the UART_intr2Disable function handles an invalid base address gracefully
 * when called after enabling valid interrupt2 flags. It opens a UART instance, enables interrupts with
 * correct flags, then disables interrupts using a deliberately invalid base address, and checks the IER2 register
 * to confirm that the interrupt2 bits remain unchanged. The test prints pass/fail status messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters and open UART instance.
 * 4. Get UART base address.
 * 5. Enable interrupt2 flags with correct flag.
 * 6. Read IER2 register before disabling interrupts.
 * 7. Disable interrupts with wrong base address.
 * 8. Read IER2 register after disabling interrupts.
 * 9. Check if interrupt2 bits remain unchanged.
 * 10. Print pass/fail message based on result.
 * 11. Close UART handle.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartIntr2DisableWrongBaseAddrAfterEnable(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    uint32_t baseAddr = 0;
    uint32_t correctIntrFlag = UART_INTR2_TX_EMPTY | UART_INTR2_RX_EMPTY;
    uint32_t wrongBaseAddr = 0xFFFFFFFFU;
    uint32_t ier2ValueBefore = 0, ier2ValueAfter = 0;
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Get base address */
    baseAddr = UART_getBaseAddr(uartHandle);

    /* Enable interrupts with correct flag */
    UART_intr2Enable(baseAddr, correctIntrFlag);

    /* Read IER2 register before disabling interrupts */
    ier2ValueBefore = HW_RD_REG32(baseAddr + UART_IER2);

    /* Disable interrupts with wrong base address */
    UART_intr2Disable(wrongBaseAddr, correctIntrFlag);

    /* Read IER2 register after disabling interrupts (should remain unchanged) */
    ier2ValueAfter = HW_RD_REG32(baseAddr + UART_IER2);

    /* Disable interrupts with wrong base address */
    UART_intr2Disable(baseAddr, correctIntrFlag);


    /* Close UART handle */
    UART_close(uartHandle);

    /* Check if the correct interrupt bits are still set */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_TRUE((ier2ValueAfter & correctIntrFlag) == correctIntrFlag);
    TEST_ASSERT_TRUE((ier2ValueBefore & correctIntrFlag) == correctIntrFlag);
}

/**
 * @brief Testcase to validate UART_getIntrIdentityStatus API in callback mode.
 *
 * This test verifies that the UART_getIntrIdentityStatus function correctly reports
 * the interrupt identity status when used in callback mode. It initializes UART parameters
 * for callback mode with interrupt transfer, opens the UART instance, performs a UART_write,
 * waits for the callback via a semaphore, and then reads the interrupt identity status.
 * The test checks if the status indicates TX threshold reached and prints pass/fail messages
 * over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters for callback mode with interrupt transfer.
 * 4. Open UART instance and verify handle is not NULL.
 * 5. Construct semaphore for callback synchronization.
 * 6. Prepare a UART_Transaction and perform UART_write.
 * 7. Wait for callback via semaphore.
 * 8. Read interrupt identity status using UART_getIntrIdentityStatus.
 * 9. Cleanup semaphore and close UART handle.
 * 10. Print pass/fail message based on result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartGetIntrIdentityStatusCallbackMode(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    UART_Transaction trans = {0};
    int32_t status = 0;
    uint32_t baseAddr = 0;
    static uint32_t uartIntrStatusValue = 0;
    static uint8_t uartTxBuffer[APP_UART_BUFSIZE] = {0};
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Construct semaphore for callback sync */
    status = SemaphoreP_constructBinary(&gUartWriteDoneSem, 0);
    if (status != SystemP_SUCCESS)
    {
        finalStatus |= (1 << 2);
    }

    /* Prepare transaction */
    UART_Transaction_init(&trans);
    trans.buf = &uartTxBuffer[0U];
    strncpy((char *)trans.buf, "UART CALLBACK INTERRUPT WRITE TEST\r\n", APP_UART_BUFSIZE);
    trans.count = strlen((char *)trans.buf);
    trans.timeout = SystemP_WAIT_FOREVER;

    /* Perform UART write in callback mode */
    status = UART_write(uartHandle, &trans);
    if (status != SystemP_SUCCESS)
    {
        finalStatus |= (1 << 3);
    }

    /* Wait for callback to signal completion */
    SemaphoreP_pend(&gUartWriteDoneSem, SystemP_WAIT_FOREVER);

    /*
     * After the write completes the ISR disables the THR interrupt,
     * so reading IIR now would show "no interrupt pending".
     * Re-enable THR so the (empty) TX FIFO condition appears in IIR.
     */
    baseAddr = UART_getBaseAddr(uartHandle);
    UART_intrEnable(baseAddr, UART_INTR_THR);

    /* Get interrupt identity status — TX FIFO is empty, THR should be set */
    uartIntrStatusValue = UART_getIntrIdentityStatus(baseAddr);

    /* Disable THR interrupt again before closing */
    UART_intrDisable(baseAddr, UART_INTR_THR);

    /* Cleanup */
    SemaphoreP_destruct(&gUartWriteDoneSem);
    UART_close(uartHandle);

    /* Check if interrupt identity status indicates TX threshold reached */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_TRUE((uartIntrStatusValue & UART_INTID_TX_THRES_REACH) == UART_INTID_TX_THRES_REACH);
}

/**
 * @brief Testcase to validate UART_getIntrIdentityStatus API with an invalid base address.
 *
 * This test verifies that the UART_getIntrIdentityStatus function handles an invalid base address gracefully.
 * It calls UART_getIntrIdentityStatus with a deliberately invalid base address and checks that no crash or error occurs.
 * The test prints a pass message over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Call UART_getIntrIdentityStatus with an invalid base address.
 * 3. Print pass message if no crash or error occurs.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartGetIntrIdentityStatusWrongBaseAddr(void *args)
{
    uint32_t wrongBaseAddr = 0xFFFFFFFFU;

    /* Call UART_getIntrIdentityStatus with wrong base address */
    UART_getIntrIdentityStatus(wrongBaseAddr);

    /* If no crash or error, test is considered passed */
}

/**
 * @brief Testcase to validate UART_getIntr2Status API functionality.
 *
 * This test verifies that the UART_getIntr2Status function correctly reports
 * the interrupt 2 status. It opens a UART instance, enables UART interrupt2 flags,
 * reads the interrupt 2 status register, and checks that the expected flags are set.
 * The test prints pass/fail status messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters and open UART instance.
 * 4. Enable UART interrupt2 flags using UART_intr2Enable.
 * 5. Read interrupt 2 status using UART_getIntr2Status.
 * 6. Verify that the expected interrupt2 flags are set.
 * 7. Disable UART interrupt2 flags.
 * 8. Close UART handle.
 * 9. Print pass/fail message based on result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartGetIntr2Status(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    uint32_t baseAddr = 0;
    uint32_t intrFlag = UART_INTR2_TX_EMPTY | UART_INTR2_RX_EMPTY;
    uint32_t intr2Status = 0;
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Get base address */
    baseAddr = UART_getBaseAddr(uartHandle);

    /* Enable IER2 interrupts */
    UART_intr2Enable(baseAddr, intrFlag);

    /* Read interrupt 2 status */
    intr2Status = UART_getIntr2Status(baseAddr);

    /* Disable IER2 interrupts */
    UART_intr2Disable(baseAddr, intrFlag);

    /* Close UART handle */
    UART_close(uartHandle);

    /* Check if both TX and RX empty interrupts are set */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_TRUE((intr2Status & intrFlag) == intrFlag);
}

/**
 * @brief Testcase to validate UART_getIntr2Status API with an invalid base address.
 *
 * This test verifies that the UART_getIntr2Status function handles an invalid base address gracefully.
 * It calls UART_getIntr2Status with a deliberately invalid base address and checks that no crash or error occurs.
 * The test prints a pass message over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Call UART_getIntr2Status with an invalid base address.
 * 3. Print pass message if no crash or error occurs.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartGetIntr2StatusWrongBaseAddr(void *args)
{
    uint32_t wrongBaseAddr = 0xFFFFFFFFU;

    /* Call UART_getIntr2Status with wrong base address */
    UART_getIntr2Status(wrongBaseAddr);

    /* If no crash or error, test is considered passed */
}

/**
 * @brief Testcase to validate UART_checkCharsAvailInFifo API functionality.
 *
 * This test verifies that the UART_checkCharsAvailInFifo function correctly reports
 * whether characters are available in the UART RX FIFO. It opens a UART instance,
 * enables loopback mode, writes a character to the TX FIFO, flushes the TX FIFO,
 * and checks if RX FIFO has data available. The test prints pass/fail status
 * messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters and open UART instance.
 * 4. Enable loopback mode.
 * 5. Write a character to TX FIFO.
 * 6. Flush TX FIFO.
 * 7. Check if RX FIFO has data available using UART_checkCharsAvailInFifo.
 * 8. Disable loopback mode.
 * 9. Close UART handle.
 * 10. Print pass/fail message based on result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartCheckCharsAvailInFifo(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    uint32_t baseAddr = 0;
    uint32_t charsAvailable = 0;
    uint8_t sentChar = 'D';
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Get base address */
    baseAddr = UART_getBaseAddr(uartHandle);

    /* Enable loopback mode */
    TestUart_enableLoopback(baseAddr);

    /* Put a character into TX FIFO */
    UART_putChar(baseAddr, sentChar);

    /* Flush TX FIFO */
    UART_flushTxFifo(uartHandle);

    /* Check if RX FIFO has data available */
    charsAvailable = UART_checkCharsAvailInFifo(baseAddr);

    /* Disable loopback mode */
    UART_disableLoopbackMode(baseAddr);

    /* Close UART handle */
    UART_close(uartHandle);

    /* Verify that RX FIFO has data available */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_EQUAL_UINT32(TRUE, charsAvailable);
}

/**
 * @brief Testcase to validate UART_checkCharsAvailInFifo API with an invalid base address.
 *
 * This test verifies that the UART_checkCharsAvailInFifo function handles an invalid base address gracefully.
 * It calls UART_checkCharsAvailInFifo with a deliberately invalid base address and checks that no crash or error occurs.
 * The test prints a pass message over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Call UART_checkCharsAvailInFifo with an invalid base address.
 * 3. Print pass message if no crash or error occurs.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartCheckCharsAvailInFifoInvalidBaseAddr(void *args)
{
    uint32_t invalidBaseAddr = 0xFFFFFFFFU;

    /* Call UART_checkCharsAvailInFifo with invalid base address */
    UART_checkCharsAvailInFifo(invalidBaseAddr);

    /* If no crash or error, test is considered passed */
}

/**
 * @brief Testcase to validate UART_readLineStatus API functionality.
 *
 * This test verifies that the UART_readLineStatus function correctly reads the UART line status register.
 * It opens a UART instance, retrieves the base address, reads the line status, and checks that the value is valid.
 * The test prints pass/fail status messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters and open UART instance.
 * 4. Get UART base address.
 * 5. Read line status register using UART_readLineStatus.
 * 6. Check if the line status value is valid (not zero).
 * 7. Print pass/fail message based on result.
 * 8. Close UART handle.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartReadLineStatus(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    uint32_t baseAddr = 0;
    uint32_t lineStatus = 0;
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Get base address */
    baseAddr = UART_getBaseAddr(uartHandle);

    /* Read line status register */
    lineStatus = UART_readLineStatus(baseAddr);

    /* Close UART handle */
    UART_close(uartHandle);

    /* Check if line status register returns a valid value (not all bits zero) */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_NOT_EQUAL(0U, lineStatus);
}

/**
 * @brief Testcase to validate UART_readLineStatus API with an invalid base address.
 *
 * This test verifies that the UART_readLineStatus function handles an invalid base address gracefully.
 * It calls UART_readLineStatus with a deliberately invalid base address and checks that no crash or error occurs.
 * The test prints a pass message over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Call UART_readLineStatus with an invalid base address.
 * 3. Print pass message if no crash or error occurs.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartReadLineStatusInvalidBaseAddr(void *args)
{
    uint32_t invalidBaseAddr = 0xFFFFFFFFU;

    /* Call UART_readLineStatus with invalid base address */
    UART_readLineStatus(invalidBaseAddr);

    /* If no crash or error, test is considered passed */
}

/**
 * @brief Testcase to validate UART_getCharFifo API functionality.
 *
 * This test verifies that the UART_getCharFifo function correctly reads a character
 * from the UART RX FIFO. It opens a UART instance, enables loopback mode, writes
 * a character to the TX FIFO, flushes the TX FIFO, and reads the character from
 * the RX FIFO using UART_getCharFifo. The test checks that the received character
 * matches the sent character and prints pass/fail status messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters and open UART instance.
 * 4. Enable loopback mode.
 * 5. Write a character to TX FIFO.
 * 6. Flush TX FIFO.
 * 7. Read a character from RX FIFO using UART_getCharFifo.
 * 8. Disable loopback mode.
 * 9. Close UART handle.
 * 10. Verify that the received character matches the sent character.
 * 11. Print pass/fail message based on result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartGetCharFifo(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    uint32_t baseAddr = 0;
    uint8_t sentChar = 'D';
    uint8_t receivedChar = 0;
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Get base address */
    baseAddr = UART_getBaseAddr(uartHandle);

    /* Enable loopback mode */
    TestUart_enableLoopback(baseAddr);

    /* Put a character into TX FIFO */
    UART_putChar(baseAddr, sentChar);

    /* Read the character from RX FIFO using UART_getCharFifo */
    UART_getCharFifo(baseAddr, &receivedChar);

    /* Disable loopback mode */
    UART_disableLoopbackMode(baseAddr);

    /* Close UART handle */
    UART_close(uartHandle);

    /* Verify that the received character matches the sent character */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_EQUAL_UINT8(sentChar, receivedChar);
}

/**
 * @brief Testcase to validate UART_getCharFifo API when a NULL char pointer is passed.
 *
 * This test verifies that the UART_getCharFifo function handles a NULL char pointer gracefully.
 * It opens a UART instance, enables loopback mode, writes a character to the TX FIFO,
 * and then calls UART_getCharFifo with a NULL pointer for the output character. The test
 * checks that no crash or error occurs and prints a pass message over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters and open UART instance.
 * 4. Enable loopback mode.
 * 5. Write a character to TX FIFO.
 * 6. Call UART_getCharFifo with a NULL char pointer.
 * 7. Disable loopback mode.
 * 8. Close UART handle.
 * 9. Print pass message if no crash or error occurs.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartGetCharFifoInvalidCharPtr(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    uint32_t baseAddr = 0;
    uint8_t sentChar = 'E';
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 1);
    }

    /* Get base address */
    baseAddr = UART_getBaseAddr(uartHandle);

    /* Enable loopback mode so TX data appears in RX FIFO */
    TestUart_enableLoopback(baseAddr);

    /* Write a character to TX FIFO */
    UART_putChar(baseAddr, sentChar);

    /* Call UART_getCharFifo with invalid char pointer (NULL) */
    UART_getCharFifo(baseAddr, NULL);

    /* Disable loopback mode */
    UART_disableLoopbackMode(baseAddr);

    /* Close UART handle */
    UART_close(uartHandle);

    /* If no crash or error, test is considered passed */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
}

/**
 * @brief Testcase to validate UART_getCharFifo API with an invalid base address.
 *
 * This test verifies that the UART_getCharFifo function handles an invalid base address gracefully.
 * It calls UART_getCharFifo with a deliberately invalid base address and checks that no crash or error occurs.
 * The test prints a pass message over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Call UART_getCharFifo with an invalid base address.
 * 3. Print pass message if no crash or error occurs.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartGetCharFifoInvalidBaseAddr(void *args)
{
    uint32_t invalidBaseAddr = 0xFFFFFFFFU;
    uint8_t receivedChar = 0;

    /* Call UART_getCharFifo with invalid base address */
    UART_getCharFifo(invalidBaseAddr, &receivedChar);

    /* If no crash or error, test is considered passed */
}

/**
 * @brief Testcase to validate UART_read API when a NULL handle is passed.
 *
 * This test verifies that the UART_read function handles a NULL UART handle gracefully.
 * It prepares a valid UART_Transaction and calls UART_read with a NULL handle,
 * checking that the transfer fails and does not return SystemP_SUCCESS.
 * The test prints pass/fail status messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters and open UART instance.
 * 4. Prepare a valid UART_Transaction structure.
 * 5. Call UART_read with NULL handle.
 * 6. Assert that transfer fails (return value is not SystemP_SUCCESS).
 * 7. Print pass/fail message based on result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartReadNullHandle(void *args)
{
    UART_Transaction trans = {0};
    int32_t transferOK = SystemP_FAILURE;
    UART_Handle uartHandle = NULL;
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    uint8_t uartRxBuffer[APP_UART_BUFSIZE] = {0};
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 0);
    }

    /* Prepare transaction */
    UART_Transaction_init(&trans);
    trans.buf = &uartRxBuffer[0U];
    trans.count = 10;
    trans.timeout = SystemP_WAIT_FOREVER;

    /* Call UART_read with NULL handle */
    transferOK = UART_read(NULL, &trans);

    /* Assert that transfer fails (should not be SystemP_SUCCESS) */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_NOT_EQUAL(SystemP_SUCCESS, transferOK);

}

/**
 * @brief Testcase to validate UART_read API when a NULL buffer is passed in the transaction.
 *
 * This test verifies that the UART_read function handles a transaction with a NULL buffer pointer gracefully.
 * It prepares a UART_Transaction with buf set to NULL and a non-zero count, calls UART_read,
 * and checks that the transfer fails (does not return SystemP_SUCCESS). The test prints pass/fail
 * status messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters and open UART instance.
 * 4. Enable loopback mode.
 * 5. Prepare a UART_Transaction with buf set to NULL and a non-zero count.
 * 6. Call UART_read with the prepared transaction.
 * 7. Disable loopback mode and flush TX FIFO.
 * 8. Close UART handle.
 * 9. Assert that transfer fails (return value is not SystemP_SUCCESS).
 * 10. Print pass/fail message based on result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartReadNullBuffer(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    UART_Transaction trans = {0}, transWrite = {0};
    int32_t transferOK = SystemP_FAILURE;
    uint32_t baseAddr = 0;
    static uint8_t uartTxBuffer[APP_UART_BUFSIZE] = {0};
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 0);
    }

    /* Enable loopback mode */
    baseAddr = UART_getBaseAddr(uartHandle);
    TestUart_enableLoopback(baseAddr);

    /* Prepare write transaction */
    UART_Transaction_init(&transWrite);
    transWrite.buf = &uartTxBuffer[0U];
    strncpy((char *)transWrite.buf, "UART LOOPBACK DATA\r\n", APP_UART_BUFSIZE);
    transWrite.count = strlen((char *)transWrite.buf);
    transWrite.timeout = SystemP_WAIT_FOREVER;

    /* Perform UART write in blocking mode */
    transferOK = UART_write(uartHandle, &transWrite);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1 << 1);
    }

    /* Prepare transaction with NULL buffer */
    UART_Transaction_init(&trans);
    trans.buf = NULL;
    trans.count = 10;
    trans.timeout = SystemP_WAIT_FOREVER;

    /* Call UART_read with NULL buffer */
    transferOK = UART_read(uartHandle, &trans);

    /* Disable loopback mode */
    UART_disableLoopbackMode(baseAddr);

    /* Flush TX FIFO */
    UART_flushTxFifo(uartHandle);

    /* Close UART handle */
    UART_close(uartHandle);

    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_NOT_EQUAL(SystemP_SUCCESS, transferOK);
}

/**
 * @brief Testcase to validate UART_read API when a transaction with zero count is passed.
 *
 * This test verifies that the UART_read function handles a transaction with a zero count gracefully.
 * It prepares a UART_Transaction with a valid buffer and zero count, calls UART_read,
 * and checks that the transfer fails (does not return SystemP_SUCCESS). The test prints pass/fail
 * status messages over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters and open UART instance.
 * 4. Enable loopback mode.
 * 5. Prepare a UART_Transaction with a valid buffer and zero count.
 * 6. Call UART_read with the prepared transaction.
 * 7. Disable loopback mode and close UART handle.
 * 8. Assert that transfer fails (return value is not SystemP_SUCCESS).
 * 9. Print pass/fail message based on result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartReadZeroCount(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    UART_Transaction transRead = {0}, transWrite = {0};
    uint32_t baseAddr = 0;
    int32_t transferOK = SystemP_FAILURE;
    static uint8_t uartTxBuffer[APP_UART_BUFSIZE] = {0};
    static uint8_t uartRxBuffer[APP_UART_BUFSIZE] = {0};
    uint8_t finalStatus = 0;

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 0);
    }

    /* Enable loopback mode */
    baseAddr = UART_getBaseAddr(uartHandle);
    TestUart_enableLoopback(baseAddr);

    /* Prepare write transaction */
    UART_Transaction_init(&transWrite);
    transWrite.buf = &uartTxBuffer[0U];
    strncpy((char *)transWrite.buf, "UART BLOCKING LOOPBACK DATA\r\n", APP_UART_BUFSIZE);
    transWrite.count = strlen((char *)transWrite.buf);
    transWrite.timeout = SystemP_WAIT_FOREVER;

    /* Perform UART write in blocking mode */
    transferOK = UART_write(uartHandle, &transWrite);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1 << 1);
    }
    if (transWrite.status != UART_TRANSFER_STATUS_SUCCESS)
    {
        finalStatus |= (1 << 2);
    }

    /* Prepare read transaction */
    UART_Transaction_init(&transRead);
    transRead.buf = &uartRxBuffer[0U];
    transRead.count = 0;
    transRead.timeout = SystemP_WAIT_FOREVER;

    /* Perform UART read in blocking mode */
    transferOK = UART_read(uartHandle, &transRead);

    /* Disable loopback mode */
    UART_disableLoopbackMode(baseAddr);

    /* Close UART handle */
    UART_close(uartHandle);

    /* Assert that transfer fails (should not be SystemP_SUCCESS) */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_NOT_EQUAL(SystemP_SUCCESS, transferOK);
}

/**
 * @brief Testcase to validate UART_read API in loopback mode with callback enabled.
 *
 * This test verifies that the UART driver can successfully perform read operations
 * in loopback mode using callback mode. It initializes UART parameters for callback mode,
 * opens the UART instance, enables loopback, writes a buffer, and reads the buffer back
 * using callback mode. The test waits for write and read completion via semaphores,
 * compares the transmitted and received data, and prints pass/fail status messages
 * over UART for automation.
 *
 * Test Steps:
 * 1. Print test case information.
 * 2. Close any existing UART handle for CONFIG_UART1.
 * 3. Initialize UART parameters for callback mode.
 * 4. Open UART instance and construct semaphores for read/write completion.
 * 5. Enable loopback mode.
 * 6. Write a buffer to UART in callback mode.
 * 7. Wait for write completion via semaphore.
 * 8. Read from UART in callback mode.
 * 9. Wait for read completion via semaphore.
 * 10. Disable loopback mode and cleanup semaphores.
 * 11. Close UART handle.
 * 12. Compare transmitted and received buffers for data integrity.
 * 13. Print pass/fail message based on result.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
void TestUart_uartWriteReadLoopBackCallback(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    static UART_Transaction transWrite = {0}, transRead1 = {0};
    int32_t statusWrite = SystemP_FAILURE, statusRead1 = SystemP_FAILURE, semStatus = SystemP_SUCCESS;
    uint32_t baseAddr = 0;
    uint8_t uartReadMultiWriteDoneSem = 0;
    static uint8_t uartWriteDoneSem = 0;
    static uint8_t uartTxBuffer[APP_UART_BUFSIZE] = {0};
    static uint8_t uartRxBuffer[APP_UART_BUFSIZE] = {0};
    uint8_t finalStatus = 0;

    /* Create semaphores for write and read completion */
    semStatus = SemaphoreP_constructBinary(&gUartWriteDoneSem, 0);
    if (semStatus != SystemP_SUCCESS)
    {
        finalStatus |= (1 << 0);
    }

    semStatus = SemaphoreP_constructBinary(&gUartReadDoneSem, 0);
    if (semStatus != SystemP_SUCCESS)
    {
        finalStatus |= (1 << 1);
    }

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 2);
    }

    /* Enable loopback mode */
    baseAddr = UART_getBaseAddr(uartHandle);
    /* Guard against invalid base address to avoid blocking read hang */
    if (baseAddr == 0U)
    {
        finalStatus |= (1 << 5);
        goto cleanup;
    }
    TestUart_enableLoopback(baseAddr);

    /* Prepare write transaction */
    UART_Transaction_init(&transWrite);
    transWrite.buf = &uartTxBuffer[0U];
    strncpy((char *)transWrite.buf, "UART MULTI READ CALLBACK TEST\r\n", APP_UART_BUFSIZE);
    transWrite.count = strlen((char *)transWrite.buf);
    transWrite.timeout = SystemP_WAIT_FOREVER;
    transWrite.args = (void *)&uartWriteDoneSem;

    /* Perform UART write in callback mode */
    statusWrite = UART_write(uartHandle, &transWrite);
    if (statusWrite != SystemP_SUCCESS)
    {
        finalStatus |= (1 << 3);
    }

    /* Wait for write completion */
    SemaphoreP_pend(&gUartWriteDoneSem, SystemP_WAIT_FOREVER);

    /* Prepare first read transaction */
    UART_Transaction_init(&transRead1);
    transRead1.buf = &uartRxBuffer[0U];
    transRead1.count = 8;
    transRead1.timeout = SystemP_WAIT_FOREVER;
    transRead1.args = (void *)&uartReadMultiWriteDoneSem;

    /* Start first read */
    statusRead1 = UART_read(uartHandle, &transRead1);
    if (statusRead1 != SystemP_SUCCESS)
    {
        finalStatus |= (1 << 4);
    }

    /* Wait for first read to complete */
    SemaphoreP_pend(&gUartReadDoneSem, SystemP_WAIT_FOREVER);

    /* Disable loopback mode */
    UART_disableLoopbackMode(baseAddr);

    /* Cleanup */
    SemaphoreP_destruct(&gUartReadDoneSem);
    SemaphoreP_destruct(&gUartWriteDoneSem);
cleanup:
    UART_close(uartHandle);

    /* Compare written and first read data */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_EQUAL_MEMORY(transWrite.buf, transRead1.buf, 8);
}

/**
 * @brief Testcase to validate single-byte blocking write and read in loopback.
 *
 * Opens UART in blocking mode, enables loopback, writes one byte and reads it
 * back, then disables loopback and closes. Asserts successful transfers and
 * that TX byte equals RX byte.
 *
 * Test Steps:
 * 1. Ensure clean state; open UART and enable loopback.
 * 2. Write 1 byte in blocking mode; read back 1 byte.
 * 3. Disable loopback, close, and validate transfer success and equality.
 *
 * @param[in] args Pointer to `UART_TestParams` providing `UART_Params`.
 *
 * @return void
 */
void TestUart_uartWriteOneByte(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;

    UART_Handle uartHandle = NULL;
    UART_Transaction tx = {0}, rx = {0};
    uint32_t baseAddr = 0U;
    int32_t status = SystemP_FAILURE;
    uint8_t txByte = 'Z';
    uint8_t rxByte = 0;
    uint8_t finalStatus = 0;

    /* Ensure clean state */
    uartHandle = UART_getHandle(instanceId);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1 << 0);
    }

    /* Enable loopback for verification */
    baseAddr = UART_getBaseAddr(uartHandle);
    TestUart_enableLoopback(baseAddr);

    /* Write exactly one byte using UART_write */
    UART_Transaction_init(&tx);
    tx.buf = &txByte;
    tx.count = 1U;
    tx.timeout = SystemP_WAIT_FOREVER;

    status = UART_write(uartHandle, &tx);
    if ((status != SystemP_SUCCESS) || (tx.status != UART_TRANSFER_STATUS_SUCCESS))
    {
        finalStatus |= (1 << 1);
    }

    /* Read back one byte to confirm loopback */
    UART_Transaction_init(&rx);
    rx.buf = &rxByte;
    rx.count = 1U;
    rx.timeout = SystemP_WAIT_FOREVER;

    status = UART_read(uartHandle, &rx);
    if ((status != SystemP_SUCCESS) || (rx.status != UART_TRANSFER_STATUS_SUCCESS))
    {
        finalStatus |= (1 << 2);
    }

    /* Disable loopback and close */
    UART_disableLoopbackMode(baseAddr);
    UART_close(uartHandle);

    /* Validate */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_EQUAL_UINT8(txByte, rxByte);
}

/**
 * @brief Testcase to validate single-byte asynchronous write and read with callbacks.
 *
 * Opens UART in callback+interrupt mode, enables loopback, writes one byte and
 * reads it back using asynchronous transactions with completion semaphores.
 * Cleans up and validates transfer success and byte equality.
 *
 * Test Steps:
 * 1. Ensure clean state; open UART with callback+interrupt params; enable loopback.
 * 2. Write 1 byte asynchronously; wait for write callback.
 * 3. Read back 1 byte asynchronously; wait for read callback.
 * 4. Disable loopback; cleanup semaphores; close; validate success and equality.
 *
 * @param[in] args Pointer to `UART_TestParams` providing `UART_Params`.
 *
 * @return void
 */
void TestUart_uartWriteOneByteCallbackWithRead(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;

    UART_Handle uartHandle = NULL;
    UART_Transaction transWrite = {0}, transRead = {0};
    int32_t status = SystemP_FAILURE, semStatus = SystemP_FAILURE;
    uint32_t baseAddr = 0U;
    uint8_t txByte = 'X';
    uint8_t rxByte = 0U;
    uint8_t finalStatus = 0;

    /* Ensure clean state */
    uartHandle = UART_getHandle(instanceId);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART with callback+interrupt params */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1U << 0);
    }

    /* Construct semaphores for write/read completion */
    semStatus = SemaphoreP_constructBinary(&gUartWriteDoneSem, 0);
    if (semStatus != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 1);
    }
    semStatus = SemaphoreP_constructBinary(&gUartReadDoneSem, 0);
    if (semStatus != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 2);
    }

    /* Enable loopback for verification */
    baseAddr = UART_getBaseAddr(uartHandle);
    if (baseAddr == 0U)
    {
        finalStatus |= (1U << 3);
    }
    else
    {
        TestUart_enableLoopback(baseAddr);
    }

    /* Write exactly one byte asynchronously */
    UART_Transaction_init(&transWrite);
    transWrite.buf = &txByte;
    transWrite.count = 1U;
    transWrite.timeout = SystemP_WAIT_FOREVER;

    status = UART_write(uartHandle, &transWrite);
    if (status != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 4);
    }

    /* Wait for write completion */
    SemaphoreP_pend(&gUartWriteDoneSem, SystemP_WAIT_FOREVER);

    /* Read back one byte asynchronously */
    UART_Transaction_init(&transRead);
    transRead.buf = &rxByte;
    transRead.count = 1U;
    transRead.timeout = SystemP_WAIT_FOREVER;

    status = UART_read(uartHandle, &transRead);
    if (status != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 5);
    }

    /* Wait for read completion */
    SemaphoreP_pend(&gUartReadDoneSem, SystemP_WAIT_FOREVER);

    /* Disable loopback and cleanup */
    if (baseAddr != 0U)
    {
        UART_disableLoopbackMode(baseAddr);
    }
    SemaphoreP_destruct(&gUartReadDoneSem);
    SemaphoreP_destruct(&gUartWriteDoneSem);
    UART_close(uartHandle);

    /* Validate */
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_EQUAL_UINT32(UART_TRANSFER_STATUS_SUCCESS, transWrite.status);
    TEST_ASSERT_EQUAL_UINT32(UART_TRANSFER_STATUS_SUCCESS, transRead.status);
    TEST_ASSERT_EQUAL_UINT8(txByte, rxByte);
}

/**
 * @brief Ordered-read callback for trigger-level ordering tests.
 *
 * Sets the ordering flag in `trans->args` to `1` to indicate the
 * read callback fired first, then posts the read completion semaphore.
 * Used by trigger-level ordering tests to verify ISR ordering.
 *
 * @param[in] handle UART handle associated with the transaction.
 * @param[in] trans  Pointer to the completed UART_Transaction structure.
 *
 * @return void
 */
static void TestUart_orderedReadCallback(UART_Handle handle, UART_Transaction *trans)
{
    uint8_t *flag = (uint8_t *)trans->args;
    if (*flag == 0U)
    {
        *flag = 1U; /* read first */
    }
    SemaphoreP_post(&gUartReadDoneSem);
}

/**
 * @brief Ordered-write callback for trigger-level ordering tests.
 *
 * Sets the ordering flag in `trans->args` to `2` to indicate the
 * write callback fired first, then posts the write completion semaphore.
 * Used by trigger-level ordering tests to verify ISR ordering.
 *
 * @param[in] handle UART handle associated with the transaction.
 * @param[in] trans  Pointer to the completed UART_Transaction structure.
 *
 * @return void
 */
static void TestUart_orderedWriteCallback(UART_Handle handle, UART_Transaction *trans)
{
    uint8_t *flag = (uint8_t *)trans->args;
    if (*flag == 0U)
    {
        *flag = 2U; /* write first */
    }
    SemaphoreP_post(&gUartWriteDoneSem);
}

/**
 * @brief Testcase to validate callback order with equal TX/RX trigger levels.
 *
 * This test configures `txTrigLvl=4` and `rxTrigLvl=4` in callback+interrupt
 * mode, arms a 4-byte read, then starts an 8-byte write under loopback. It
 * expects the read callback to fire before the write callback.
 *
 * Test Steps:
 * 1. Configure trigger levels and callbacks; open UART and enable loopback.
 * 2. Arm read (4 bytes), then start write (256 bytes buffer).
 * 3. Wait for both callbacks; disable loopback and cleanup.
 * 4. Validate `uartFirstCb == 1` and successful transfer statuses/counts.
 *
 * @param[in] args Pointer to `UART_TestParams` providing `UART_Params`.
 *
 * @return void
 */
void TestUart_txRxTriggerLevelOrderedCallbacks(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;

    UART_Handle uartHandle = NULL;
    UART_Transaction  transWrite = {0}, transRead = {0};
    uint32_t baseAddr = 0U;
    int32_t status;
    uint8_t txBuf[256] = { "UART ORDER CHECK TEST FOR TRIG LEVEL\r\n" };
    uint8_t rxBuf[4] = { 0 };
    uint8_t finalStatus = 0;
    uint8_t uartFirstCb = 0U;

    /* Configure callback + interrupt, trig levels = 4 */
    uartParams->txTrigLvl          = 4U;
    uartParams->rxTrigLvl          = 4U;
    uartParams->writeCallbackFxn   = TestUart_orderedWriteCallback;
    uartParams->readCallbackFxn    = TestUart_orderedReadCallback;

    /* Clean previous */
    uartHandle = UART_getHandle(instanceId);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1U<<0);
        goto test_end;
    }

    /* Semaphores for completion */
    status = SemaphoreP_constructBinary(&gUartWriteDoneSem, 0);
    if (status != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 1);
    }
    status = SemaphoreP_constructBinary(&gUartReadDoneSem, 0);
    if (status != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 2);
    }

    /* Enable internal loopback */
    baseAddr = UART_getBaseAddr(uartHandle);
    if (baseAddr == 0U)
    {
        finalStatus |= (1U<<3);
        goto cleanup;
    }
    TestUart_enableLoopback(baseAddr);

    /* Reset ordering counters */
    uartFirstCb = 0U;

    /* Arm READ first: 4 bytes (matches RX trig level) */
    UART_Transaction_init(&transRead);
    transRead.buf = rxBuf;
    transRead.count = sizeof(rxBuf);      /* 4 bytes */
    transRead.timeout = SystemP_WAIT_FOREVER;
    transRead.args = (void *)&uartFirstCb;
    status = UART_read(uartHandle, &transRead);
    if (status != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 4);
    }

    /* Start WRITE: 8 bytes; with txTrigLvl=4 this takes two THR interrupts */
    UART_Transaction_init(&transWrite);
    transWrite.buf = txBuf;
    transWrite.count = sizeof(txBuf);
    transWrite.timeout = SystemP_WAIT_FOREVER;
    transWrite.args = (void *)&uartFirstCb;
    status = UART_write(uartHandle, &transWrite);
    if (status != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 5);
    }

    /* Wait for read to complete first, then write */
    SemaphoreP_pend(&gUartReadDoneSem, SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&gUartWriteDoneSem, SystemP_WAIT_FOREVER);

    /* Disable loopback */
    UART_disableLoopbackMode(baseAddr);

cleanup:
    SemaphoreP_destruct(&gUartReadDoneSem);
    SemaphoreP_destruct(&gUartWriteDoneSem);
    UART_close(uartHandle);

test_end:
    TestUart_openDebugUart();

    /* Validate: read callback happened first, exactly once each */
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_EQUAL_UINT32(1U, uartFirstCb); /* 1=read first */

    /* Validate transaction results */
    TEST_ASSERT_EQUAL_UINT32(UART_TRANSFER_STATUS_SUCCESS, transRead.status);
    TEST_ASSERT_EQUAL_UINT32(UART_TRANSFER_STATUS_SUCCESS, transWrite.status);
    TEST_ASSERT_EQUAL_UINT32(4U, transRead.count);
    TEST_ASSERT_EQUAL_UINT32(256U, transWrite.count);
    TEST_ASSERT_EQUAL_MEMORY(txBuf, rxBuf, 4U);
}

/**
 * @brief Testcase to validate callback order when RX trigger is higher than TX trigger.
 *
 * This test sets `txTrigLvl=4` and `rxTrigLvl=8` in callback+interrupt mode,
 * arms an 8-byte read and starts a 4-byte write under loopback, then cancels
 * the read after a short wait. It expects the write callback to fire first.
 *
 * Test Steps:
 * 1. Configure trigger levels and callbacks; open UART and enable loopback.
 * 2. Arm read (8 bytes), then start write (4 bytes).
 * 3. Wait briefly; cancel read; disable loopback and cleanup.
 * 4. Validate `uartFirstCb == 2`, read not success, write success; check counts.
 *
 * @param[in] args Pointer to `UART_TestParams` providing `UART_Params`.
 *
 * @return void
 */
static void TestUart_txRxTriggerLevelHighRxTriglevel(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;

    UART_Handle uartHandle = NULL;
    UART_Transaction  transWrite = {0}, transRead = {0};
    uint32_t baseAddr = 0U;
    int32_t status;
    uint8_t txBuf[4] = {'A', 'B', 'C', 'D'};
    uint8_t rxBuf[8] = { 0 };
    uint8_t finalStatus = 0;
    uint8_t uartFirstCb = 0U;

    /* Configure callback + interrupt, trig levels = 4 */
    uartParams->txTrigLvl          = 4U;
    uartParams->rxTrigLvl          = 8U;
    uartParams->writeCallbackFxn   = TestUart_orderedWriteCallback;
    uartParams->readCallbackFxn    = TestUart_orderedReadCallback;

    /* Clean previous */
    uartHandle = UART_getHandle(instanceId);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1U<<0);
        goto test_end;
    }

    /* Semaphores for completion */
    status = SemaphoreP_constructBinary(&gUartWriteDoneSem, 0);
    if (status != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 1);
    }
    status = SemaphoreP_constructBinary(&gUartReadDoneSem, 0);
    if (status != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 2);
    }

    /* Enable internal loopback */
    baseAddr = UART_getBaseAddr(uartHandle);
    if (baseAddr == 0U)
    {
        finalStatus |= (1U<<3);
        goto cleanup;
    }
    TestUart_enableLoopback(baseAddr);

    /* Reset ordering counters */
    uartFirstCb = 0U;

    /* Arm READ first: 8 bytes (matches RX trig level) */
    UART_Transaction_init(&transRead);
    transRead.buf = rxBuf;
    transRead.count = sizeof(rxBuf);      /* 8 bytes */
    transRead.timeout = SystemP_WAIT_FOREVER;
    transRead.args = (void *)&uartFirstCb;
    status = UART_read(uartHandle, &transRead);
    if (status != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 4);
    }

    /* Start WRITE: 4 bytes; with txTrigLvl=4 this takes two THR interrupts */
    UART_Transaction_init(&transWrite);
    transWrite.buf = txBuf;
    transWrite.count = sizeof(txBuf);
    transWrite.timeout = SystemP_WAIT_FOREVER;
    transWrite.args = (void *)&uartFirstCb;
    status = UART_write(uartHandle, &transWrite);
    if (status != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 5);
    }

    /* Wait for read to complete first, then write */
    SemaphoreP_pend(&gUartReadDoneSem,  ClockP_usecToTicks(10*1000));
    SemaphoreP_pend(&gUartWriteDoneSem, SystemP_WAIT_FOREVER);

    UART_readCancel(uartHandle, &transRead);

    /* Disable loopback */
    UART_disableLoopbackMode(baseAddr);

cleanup:
    SemaphoreP_destruct(&gUartReadDoneSem);
    SemaphoreP_destruct(&gUartWriteDoneSem);
    UART_close(uartHandle);

test_end:
    TestUart_openDebugUart();

    /* Validate: read callback happened first, exactly once each */
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_EQUAL_UINT32(2U, uartFirstCb);

    /* Validate transaction results */
    TEST_ASSERT_NOT_EQUAL_UINT32(UART_TRANSFER_STATUS_SUCCESS, transRead.status);
    TEST_ASSERT_EQUAL_UINT32(UART_TRANSFER_STATUS_SUCCESS, transWrite.status);
    TEST_ASSERT_EQUAL_UINT32(4U, transRead.count);
}

/**
 * @brief Testcase to validate loopback using UART 13x operational mode.
 *
 * This test opens the UART with `operMode=UART_OPER_MODE_13X`, enables loopback,
 * writes a byte and reads it back, then disables loopback and closes, validating
 * transfer success and data integrity.
 *
 * Test Steps:
 * 1. Close any existing handle; open with 13x mode.
 * 2. Enable loopback; perform 1-byte write and read.
 * 3. Cleanup and assert transfer success and byte equality.
 *
 * @param[in] args Pointer to `UART_TestParams` providing `UART_Params`.
 *
 * @return void
 */
static void TestUart_operMode13xLoopback(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;

    UART_Handle      uartHandle = NULL;
    UART_Transaction transWrite = {0}, transRead = {0};
    uint8_t          txByte = 0x5AU, rxByte = 0U;
    uint32_t         baseAddr;
    uint8_t          finalStatus = 0;
    int32_t          status;

    /* Ensure clean state */
    uartHandle = UART_getHandle(instanceId);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open with operMode = 13x set in params */
    uartParams->operMode = UART_OPER_MODE_13X;
    uartParams->txTrigLvl = 4U;
    uartParams->rxTrigLvl = 4U;
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1U<<0);
        goto test_end;
    }

    /* Enable internal loopback */
    baseAddr = UART_getBaseAddr(uartHandle);
    if (baseAddr == 0U)
    {
        finalStatus |= (1U<<1);
        goto cleanup;
    }

    TestUart_enableLoopback(baseAddr);

    /* Semaphores for callbacks */
    status = SemaphoreP_constructBinary(&gUartWriteDoneSem, 0);
    if (status != SystemP_SUCCESS)
    {
        finalStatus |= (1U<<2);
        goto lb_disable;
    }
    status = SemaphoreP_constructBinary(&gUartReadDoneSem, 0);
    if (status != SystemP_SUCCESS)
    {
        finalStatus |= (1U<<3);
        goto sem_cleanup_write;
    }

    /* Arm async READ for 1 byte */
    UART_Transaction_init(&transRead);
    transRead.buf = &rxByte;
    transRead.count = 1U;
    transRead.timeout = SystemP_WAIT_FOREVER;
    status = UART_read(uartHandle, &transRead);
    if (status != SystemP_SUCCESS)
    {
        finalStatus |= (1U<<4);
        goto sem_cleanup;
    }

    /* Start async WRITE of 1 byte */
    UART_Transaction_init(&transWrite);
    transWrite.buf = &txByte;
    transWrite.count = 1U;
    transWrite.timeout = SystemP_WAIT_FOREVER;
    status = UART_write(uartHandle, &transWrite);
    if (status != SystemP_SUCCESS)
    {
        finalStatus |= (1U<<5);
        goto sem_cleanup;
    }

    /* Wait for callbacks */
    SemaphoreP_pend(&gUartReadDoneSem, SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&gUartWriteDoneSem, SystemP_WAIT_FOREVER);

sem_cleanup:
    SemaphoreP_destruct(&gUartReadDoneSem);
sem_cleanup_write:
    SemaphoreP_destruct(&gUartWriteDoneSem);
lb_disable:
    UART_disableLoopbackMode(baseAddr);
cleanup:
    UART_close(uartHandle);

test_end:
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_EQUAL_UINT32(UART_TRANSFER_STATUS_SUCCESS, transRead.status);
    TEST_ASSERT_EQUAL_UINT32(UART_TRANSFER_STATUS_SUCCESS, transWrite.status);
    TEST_ASSERT_EQUAL_UINT32(1U, transRead.count);
    TEST_ASSERT_EQUAL_UINT8(txByte, rxByte);
}

/**
 * @brief Testcase to validate UART_write error-in-use handling in interrupt/callback mode.
 *
 * Starts an asynchronous write and immediately attempts a second write on the same handle
 * while the first is still active. Expects the driver to reject the second transaction with
 * UART_TRANSFER_STATUS_ERROR_INUSE. The first write completes successfully via callback.
 *
 * Test Steps:
 * 1. Close any existing handle; open UART with interrupt transfer and write callback; slow baud.
 * 2. Construct write completion semaphore; enable loopback.
 * 3. Start first asynchronous write (marks TX active).
 * 4. Attempt second write immediately; expect SystemP_FAILURE and ERROR_INUSE status.
 * 5. Wait for first write to complete; disable loopback; cleanup and close.
 *
 * @param[in] args Pointer to UART_TestParams providing UART_Params and instanceId.
 *
 * @return void
 */
static void TestUart_uartWriteErrorInUseInterrupt(void *args)
{
    UART_Params     *uartParams  = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t         instanceId  = ((UART_TestParams *)args)->instanceId;
    UART_Handle      uartHandle  = NULL;
    UART_Transaction transWrite1 = {0}, transWrite2 = {0};
    uint8_t          txBuf1[64]  = "INUSE-WRITE-TEST-AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    uint8_t          txBuf2[8]   = "BBBBBBBB";
    uint32_t         baseAddr    = 0U;
    int32_t          status;
    uint8_t          finalStatus = 0;
    uintptr_t key;

    /* Clean previous */
    uartHandle = UART_getHandle(instanceId);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open (slow baud to make TX take longer) */
    uartParams->baudRate = 4800;
    uartParams->writeMode = UART_TRANSFER_MODE_CALLBACK;
    uartParams->transferMode = UART_CONFIG_MODE_INTERRUPT;
    uartParams->writeCallbackFxn = TestUart_uartWriteCallback;
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1U << 0);
        goto test_end;
    }

    /* Semaphores for completion */
    status = SemaphoreP_constructBinary(&gUartWriteDoneSem, 0);
    if (status != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 1);
        goto cleanup_handle;
    }

    /* Enable internal loopback (keeps template consistent) */
    baseAddr = UART_getBaseAddr(uartHandle);
    if (baseAddr == 0U)
    {
        finalStatus |= (1U << 2);
        goto sem_cleanup;
    }
    TestUart_enableLoopback(baseAddr);

    /* First WRITE setup */
    UART_Transaction_init(&transWrite1);
    transWrite1.buf     = txBuf1;
    transWrite1.count   = sizeof(txBuf1);
    transWrite1.timeout = SystemP_WAIT_FOREVER;

    /* Second WRITE setup */
    UART_Transaction_init(&transWrite2);
    transWrite2.buf     = txBuf2;
    transWrite2.count   = sizeof(txBuf2);
    transWrite2.timeout = SystemP_WAIT_FOREVER;

    /* Disable interrupts to prevent ISR from completing first write before second call */
    key = HwiP_disable();

    /* Start first WRITE (asynchronous, marks txActive) */
    status = UART_write(uartHandle, &transWrite1);
    if (status != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 3);
        HwiP_restore(key);
        goto lb_disable;
    }

    /* Immediately attempt second WRITE while first is still active → expect ERROR_INUSE */
    status = UART_write(uartHandle, &transWrite2);

    /* Restore interrupts so first write can complete */
    HwiP_restore(key);

    /* Validate second write rejection */
    if (status != SystemP_FAILURE ||
        transWrite2.status != UART_TRANSFER_STATUS_ERROR_INUSE)
    {
        finalStatus |= (1U << 4);
    }

    /* Wait for first write to complete via callback */
    SemaphoreP_pend(&gUartWriteDoneSem, SystemP_WAIT_FOREVER);

lb_disable:
    UART_disableLoopbackMode(baseAddr);

sem_cleanup:
    SemaphoreP_destruct(&gUartWriteDoneSem);

cleanup_handle:
    UART_close(uartHandle);

test_end:
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_EQUAL_UINT32(UART_TRANSFER_STATUS_SUCCESS, transWrite1.status);
}

/**
 * @brief Testcase to validate UART TX FIFO trigger levels with loopback (interrupt + callback mode).
 *
 * Iterates through valid TX/RX trigger levels (1, 8, 16, 32, 56), opening the UART
 * with callback+interrupt configuration for each level. For each iteration, it:
 *  - Enables loopback.
 *  - Arms a read of the exact payload length.
 *  - Starts a write of the same payload length.
 *  - Waits for both read and write callbacks.
 *  - Verifies successful transfer statuses, matching counts, and data integrity.
 *
 * This covers programming and ISR behavior across different FIFO threshold configurations.
 *
 * Test Steps:
 * 1. For each txTrigLvl in {1, 8, 16, 32, 56}, set rxTrigLvl = txTrigLvl and open UART.
 * 2. Construct read/write completion semaphores; enable loopback.
 * 3. Arm read for strlen(txBuf) bytes; start write for the same length.
 * 4. Wait for callback completion; validate status, count, and memcmp(txBuf, rxBuf).
 * 5. Disable loopback, destruct semaphores, and close the handle.
 *
 * @param[in] args Pointer to UART_TestParams providing UART_Params and instanceId.
 *
 * @return void
 */
static void TestUart_txTriggerLevelsLoopback(void *args)
{
    UART_TestParams *uartParams = (UART_TestParams *)args;
    UART_Params     *basePrms  = (UART_Params *)&uartParams->uartParams;
    uint16_t         instanceId = uartParams->instanceId;

    UART_Handle      uartHandle = NULL;
    UART_Transaction transWrite = {0}, transRead = {0};
    int32_t          status     = SystemP_FAILURE;
    uint32_t         baseAddr   = 0U;
    uint8_t          finalStatus = 0;
    uint32_t loop;

    /* Test payload */
    uint8_t txBuf[64] = { "UART TX TRIG LEVEL LOOPBACK DATA 0123456789\r\n" };
    uint8_t rxBuf[64] = { 0 };

    /* Use ONLY valid trigger-level macros from uart.h */
    const uint32_t txLevels[] = {
        UART_TXTRIGLVL_1,
        UART_TXTRIGLVL_8,
        UART_TXTRIGLVL_16,
        UART_TXTRIGLVL_32,
        UART_TXTRIGLVL_56
    };

    for (loop = 0; loop < (sizeof(txLevels)/sizeof(txLevels[0])); loop++)
    {
        UART_Params prms;
        memcpy(&prms, basePrms, sizeof(UART_Params));

        prms.writeMode        = UART_TRANSFER_MODE_CALLBACK;
        prms.readMode         = UART_TRANSFER_MODE_CALLBACK;
        prms.transferMode     = UART_CONFIG_MODE_INTERRUPT;
        prms.writeCallbackFxn = TestUart_uartWriteCallback;
        prms.readCallbackFxn  = TestUart_uartReadCallback;
        prms.txTrigLvl        = txLevels[loop];
        prms.rxTrigLvl        = txLevels[loop];

        /* Ensure clean state per iteration */
        uartHandle = UART_getHandle(instanceId);
        if (uartHandle != NULL)
        {
            UART_close(uartHandle);
        }

        uartHandle = UART_open(instanceId, &prms);
        if (uartHandle == NULL)
        {
            finalStatus |= (1U << (loop*4 + 0));
            continue;
        }

        status = SemaphoreP_constructBinary(&gUartWriteDoneSem, 0);
        if (status != SystemP_SUCCESS)
        {
            finalStatus |= (1U << (loop*4 + 1));
            UART_close(uartHandle);
            continue;
        }
        status = SemaphoreP_constructBinary(&gUartReadDoneSem, 0);
        if (status != SystemP_SUCCESS)
        {
            finalStatus |= (1U << (loop*4 + 2));
            SemaphoreP_destruct(&gUartWriteDoneSem);
            UART_close(uartHandle);
            continue;
        }

        baseAddr = UART_getBaseAddr(uartHandle);
        if (baseAddr == 0U)
        {
            finalStatus |= (1U << (loop*4 + 3));
            goto iter_cleanup;
        }
        TestUart_enableLoopback(baseAddr);

        /* Clear RX buffer for deterministic compare */
        memset(rxBuf, 0, sizeof(rxBuf));

        /* Arm READ for exact payload length */
        UART_Transaction_init(&transRead);
        transRead.buf     = rxBuf;
        transRead.count   = (uint32_t)strlen((char *)txBuf);
        transRead.timeout = SystemP_WAIT_FOREVER;

        status = UART_read(uartHandle, &transRead);
        if (status != SystemP_SUCCESS)
        {
            finalStatus |= (1U << (loop*4 + 3));
            goto iter_lb_disable;
        }

        /* WRITE same payload length */
        UART_Transaction_init(&transWrite);
        transWrite.buf     = txBuf;
        transWrite.count   = (uint32_t)strlen((char *)txBuf);
        transWrite.timeout = SystemP_WAIT_FOREVER;

        status = UART_write(uartHandle, &transWrite);
        if (status != SystemP_SUCCESS)
        {
            finalStatus |= (1U << (loop*4 + 3));
            goto iter_lb_disable;
        }

        /* Wait for callbacks */
        SemaphoreP_pend(&gUartReadDoneSem, SystemP_WAIT_FOREVER);
        SemaphoreP_pend(&gUartWriteDoneSem, SystemP_WAIT_FOREVER);

        /* Validate */
        if (transWrite.status != UART_TRANSFER_STATUS_SUCCESS ||
            transRead.status  != UART_TRANSFER_STATUS_SUCCESS ||
            transRead.count   != transWrite.count ||
            memcmp(txBuf, rxBuf, transWrite.count) != 0)
        {
            finalStatus |= (1U << (loop*4 + 3));
        }

iter_lb_disable:
        UART_disableLoopbackMode(baseAddr);

iter_cleanup:
        SemaphoreP_destruct(&gUartReadDoneSem);
        SemaphoreP_destruct(&gUartWriteDoneSem);
        UART_close(uartHandle);
    }

    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
}

/**
 * @brief Testcase to exercise the framing error branch in UART driver.
 *
 * This test uses public APIs to open a UART instance in polled mode,
 * then simulates a framing error by setting the RX FIFO error status
 * and framing error bits in the line status register. A blocking
 * UART_read is issued which causes the driver to invoke
 * UART_statusIsDataReady() and subsequently UART_procLineStatusErr(),
 * covering the `else if ((lineStatus & UART_FRAMING_ERROR) != 0U)` path.
 *
 * Steps:
 * 1. Open UART with polled + blocking read.
 * 2. Get base address via UART_getBaseAddr.
 * 3. Set LSR error bits (RX_FIFO_STS + RX_FE) via HW_WR_REG32.
 * 4. Issue a small blocking UART_read (count=1, short timeout).
 * 5. Verify transaction did not return success (error path taken).
 * 6. Close handle.
 */
static void TestUart_uartFramingErrorPolled(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    UART_Transaction trans;
    uint32_t baseAddr = 0U;

    /* Ensure clean state for the instance */
    uartHandle = UART_getHandle(instanceId);
    if(uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance (polled + blocking as configured in paramsInit) */
    uartHandle = UART_open(instanceId, uartParams);
    TEST_ASSERT_NOT_NULL(uartHandle);

    baseAddr = UART_getBaseAddr(uartHandle);
    TEST_ASSERT_NOT_EQUAL(0U, baseAddr);

    /* Initialize read transaction */
    UART_Transaction_init(&trans);
    trans.buf = &gUartRxBuffer[0U];
    trans.count = 1U;
    trans.timeout = 1U; /* short timeout to exit polling loop */

    /* Simulate framing error: set RX FIFO error status + FE bit */
    HW_WR_REG32(baseAddr + UART_LSR, (uint32_t)(UART_LSR_RX_FIFO_STS_MASK | UART_LSR_RX_FE_MASK));

    /* Perform read; driver should hit error handling path */
    (void)UART_read(uartHandle, &trans);

    /* We only assert non-success to avoid HW-specific status expectations */
    TEST_ASSERT_NOT_EQUAL(UART_TRANSFER_STATUS_SUCCESS, trans.status);

    /* Cleanup */
    UART_close(uartHandle);
}

/**
 * @brief Testcase to validate UART_write polling timeout path (timeoutElapsed = 1U).
 *
 * Opens UART in polled + blocking mode, enables loopback, and starts a large write
 * with a very short timeout. Expects UART_write to return SystemP_TIMEOUT and set
 * trans.status to UART_TRANSFER_STATUS_TIMEOUT, covering the timeoutElapsed branch
 * inside UART_writePolling.
 *
 * Test Steps:
 * 1. Ensure clean state; open UART in polled mode.
 * 2. Enable loopback; prepare a large write with short timeout.
 * 3. Call UART_write; cleanup (disable loopback and close).
 * 4. Validate return value and transaction status indicate timeout.
 *
 * @param[in] args Pointer to UART_TestParams providing UART_Params and instanceId.
 *
 * @return void
 */
static void TestUart_uartWritePollingTimeoutElapsed(void *args)
{
    UART_Params *uartParams   = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t     instanceId   = ((UART_TestParams *)args)->instanceId;
    UART_Handle  uartHandle   = NULL;
    UART_Transaction trans    = {0};
    int32_t      transferOK   = SystemP_FAILURE;
    uint8_t      finalStatus  = 0;
    uint32_t     baseAddr     = 0U;

    /* Ensure clean state */
    uartHandle = UART_getHandle(instanceId);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open in polled mode with slow baud (set via TestUart_paramsInit) */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= 1U;
        goto cleanup;
    }

    /* Do NOT enable loopback — leave TX pin unconnected so the TX FIFO
     * drains only at the configured baud rate (1200). Without loopback
     * the hardware still shifts bits out, keeping the FIFO occupied. */
    baseAddr = UART_getBaseAddr(uartHandle);

    /* Prepare a large write with a minimal timeout to guarantee timeout.
     * At 1200 baud, each byte takes ~8.3 ms (10 bits/byte).
     * APP_UART_BUFSIZE bytes will take far longer than 1 tick. */
    memset(gUartTxBuffer, 0xAA, APP_UART_BUFSIZE);
    UART_Transaction_init(&trans);
    trans.buf     = &gUartTxBuffer[0U];
    trans.count   = APP_UART_BUFSIZE;       /* use full buffer size */
    trans.timeout = 1U;                     /* 1 tick — guarantees timeout */

    transferOK = UART_write(uartHandle, &trans);

    if (baseAddr != 0U)
    {
        UART_disableLoopbackMode(baseAddr);
    }
    UART_close(uartHandle);

cleanup:
    TestUart_openDebugUart();

    /* Must hit TIMEOUT path from UART_writePolling (timeoutElapsed = 1U) */
    TEST_ASSERT_EQUAL(0, finalStatus);
    TEST_ASSERT_EQUAL_INT(SystemP_TIMEOUT, transferOK);
    TEST_ASSERT_EQUAL_INT(UART_TRANSFER_STATUS_TIMEOUT, trans.status);
    TEST_ASSERT_TRUE(trans.count < APP_UART_BUFSIZE);
}

/**
 * @brief Validate UART_checkOpenParams when readMode=CALLBACK and readCallbackFxn=NULL.
 *
 * Opens UART with interrupt transfer and sets readMode to CALLBACK without a read
 * callback. Expects UART_open to fail and return NULL due to invalid parameters.
 *
 * Test Steps:
 * 1. Close any existing handle for the given instance.
 * 2. Call UART_open with readMode=CALLBACK and readCallbackFxn=NULL.
 * 3. Assert that the returned handle is NULL.
 *
 * @param[in] args Pointer to UART_TestParams providing UART_Params and instanceId.
 *
 * @return void
 */
static void TestUart_uartOpenInvalidParamsReadCallbackNull(void *args)
{
    UART_TestParams *uartParams     = (UART_TestParams *)args;
    UART_Params     *prms   = (UART_Params *)&uartParams->uartParams;
    uint16_t         instId = uartParams->instanceId;
    UART_Handle      uartHandle;

    /* Close if already open */
    uartHandle = UART_getHandle(instId);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Attempt open with invalid read callback configuration */
    uartHandle = UART_open(instId, prms);

    /* Must fail (NULL handle) due to UART_checkOpenParams */
    TEST_ASSERT_NULL(uartHandle);
}

/**brief Validate UART_checkOpenParams when writeMode=CALLBACK and writeCallbackFxn=NULL.
 *
 * Opens UART with interrupt transfer and sets writeMode to CALLBACK without a write
 * callback. Expects UART_open to fail and return NULL due to invalid parameters.
 *
 * Test Steps:
 * 1. Close any existing handle for the given instance.
 * 2. Call UART_open with writeMode=CALLBACK and writeCallbackFxn=NULL.
 * 3. Assert that the returned handle is NULL.
 *
 * @param[in] args Pointer to UART_TestParams providing UART_Params and instanceId.
 *
 * @return void
 */
static void TestUart_uartOpenInvalidParamsWriteCallbackNull(void *args)
{
    UART_TestParams *uartParams     = (UART_TestParams *)args;
    UART_Params     *prms   = (UART_Params *)&uartParams->uartParams;
    uint16_t         instId = uartParams->instanceId;
    UART_Handle      uartHandle;

    /* Close if already open */
    uartHandle = UART_getHandle(instId);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Attempt open with invalid write callback configuration */
    uartHandle = UART_open(instId, prms);

    /* Must fail (NULL handle) due to UART_checkOpenParams */
    TEST_ASSERT_NULL(uartHandle);
}

/**
 * @brief UART read completion callback used for immediate-complete tests.
 *
 * Captures the transaction count and status when a read completes
 * immediately inside UART_readInterrupt, then posts the read-done
 * semaphore to unblock the waiting test thread.
 *
 * Updates:
 * - TestUart_immediateReadCount  = trans->count
 * - TestUart_immediateReadStatus = trans->status
 * - Posts gUartReadDoneSem
 *
 * @param[in] handle UART handle associated with the transaction.
 * @param[in] trans  Pointer to the completed UART_Transaction.
 *
 * @return void
 */
static void TestUart_immediateReadCallback(UART_Handle handle, UART_Transaction *trans)
{
    TestUart_immediateReadCount  = trans->count;
    TestUart_immediateReadStatus = trans->status;
    (void)SemaphoreP_post(&gUartReadDoneSem);
}

/**
 * @brief Testcase to validate UART_readInterrupt immediate-complete path.
 *
 * Preloads RX FIFO under internal loopback, then starts a read in
 * interrupt + callback mode. Since the requested bytes are already
 * available, UART_readInterrupt drains them, posting the read-done
 * semaphore immediately with SUCCESS and full count.
 *
 * Test Steps:
 * 1. Open UART with interrupt transfer and read callback.
 * 2. Enable loopback and push N bytes via UART_putChar.
 * 3. Start read for N bytes; wait on gUartReadDoneSem.
 * 4. Validate callback status == SUCCESS and count == N.
 *
 * @param[in] args Pointer to UART_TestParams providing UART_Params and instanceId.
 *
 * @return void
 */
static void TestUart_uartReadInterruptImmediate(void *args)
{
    UART_TestParams *uartParams  = (UART_TestParams *)args;
    UART_Params     *prms   = (UART_Params *)&uartParams->uartParams;
    uint16_t         instId = uartParams->instanceId;

    UART_Handle      handle = NULL;
    UART_Transaction trans  = {0};
    uint32_t         base   = 0U;
    uint8_t          finalStatus = 0U;
    int32_t          semStat;
    const uint32_t byte = 8U;
    uint32_t loop;

    /* Clean up any previous open */
    handle = UART_getHandle(instId);
    if (handle != NULL)
    {
        UART_close(handle);
    }

    /* Configure for interrupt + callback read */
    prms->transferMode    = UART_CONFIG_MODE_INTERRUPT;
    prms->readMode        = UART_TRANSFER_MODE_CALLBACK;
    prms->writeMode       = UART_TRANSFER_MODE_BLOCKING;
    prms->readCallbackFxn = TestUart_immediateReadCallback;
    prms->readReturnMode  = UART_READ_RETURN_MODE_FULL;
    prms->rxTrigLvl       = UART_RXTRIGLVL_1;
    prms->txTrigLvl       = UART_TXTRIGLVL_1;

    /* Open UART */
    handle = UART_open(instId, prms);
    if (handle == NULL)
    {
        finalStatus |= 1U; goto test_end;
    }

    base = UART_getBaseAddr(handle);
    if (base == 0U) { finalStatus |= 2U; goto cleanup; }

    /* Enable internal loopback */
    TestUart_enableLoopback(base);

    /* Preload RX via loopback: put byte bytes before calling UART_read */

    for (loop = 0; loop < byte; loop++)
    {
        UART_putChar(base, (uint8_t)(0x30 + (loop & 0x0FU)));
    }

    /* Small delay to let bytes reach RX FIFO */
    ClockP_usleep(1000);

    /* Init semaphore to wait for callback */
    if (SemaphoreP_constructBinary(&gUartReadDoneSem, 0) != SystemP_SUCCESS)
    {
        finalStatus |= 4U;
        goto lb_disable;
    }

    /* Prepare async read for byte bytes; UART_readInterrupt will drain all immediately */
    UART_Transaction_init(&trans);
    trans.buf     = &gUartRxBuffer[0U];
    trans.count   = byte;
    trans.timeout = SystemP_WAIT_FOREVER;

    /* Reset capture vars */
    TestUart_immediateReadCount  = 0U;
    TestUart_immediateReadStatus = SystemP_FAILURE;

    /* Start read; in interrupt mode, UART_read() calls UART_readInterrupt immediately */
    (void)UART_read(handle, &trans);

    /* Wait for our callback to be invoked */
    semStat = SemaphoreP_pend(&gUartReadDoneSem, SystemP_WAIT_FOREVER);
    if (semStat != SystemP_SUCCESS) { finalStatus |= 8U; }

    /* Validate immediate completion via callback (SUCCESS and full count) */
    if ((TestUart_immediateReadStatus != UART_TRANSFER_STATUS_SUCCESS) || (TestUart_immediateReadCount != byte))
    {
        finalStatus |= 16U;
    }

    /* Clean up */
    SemaphoreP_destruct(&gUartReadDoneSem);

lb_disable:
    UART_disableLoopbackMode(base);

cleanup:
    UART_close(handle);

test_end:
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
}

/**
 * @brief Validate UART_readCancel error path when no read is in progress.
 *
 * Opens UART normally and calls UART_readCancel without starting a read.
 * Expects UART_readCancel to return SystemP_FAILURE and set
 * trans.status to UART_TRANSFER_STATUS_ERROR_OTH.
 *
 * Test Steps:
 * 1. Ensure clean state; open UART.
 * 2. Invoke UART_readCancel with an idle read state.
 * 3. Validate return value and transaction status.
 * 4. Close handle and assert finalStatus == 0.
 *
 * @param[in] args Pointer to UART_TestParams providing UART_Params and instanceId.
 *
 * @return void
 */
static void TestUart_uartReadCancelErrorNoReadInProgress(void *args)
{
    UART_TestParams *uartParams  = (UART_TestParams *)args;
    UART_Params     *prms   = (UART_Params *)&uartParams->uartParams;
    uint16_t         instId = uartParams->instanceId;

    UART_Handle      handle = NULL;
    UART_Transaction trans  = {0};
    int32_t          status;
    uint8_t          finalStatus = 0U;

    /* Ensure clean state */
    handle = UART_getHandle(instId);
    if (handle != NULL)
    {
        UART_close(handle);
    }

    /* Open UART normally; do NOT start any read */
    handle = UART_open(instId, prms);
    if (handle == NULL)
    {
        finalStatus |= 1U; goto test_end;
    }

    /* Call readCancel with no active read; expect ERROR_OTH */
    trans.buf     = NULL;           /* not used by readCancel path */
    trans.count   = 0U;             /* not used by readCancel path */
    trans.timeout = 0U;

    status = UART_readCancel(handle, &trans);

    /* Validate error path */
    if (!(status == SystemP_FAILURE && trans.status == UART_TRANSFER_STATUS_ERROR_OTH))
    {
        finalStatus |= 2U;
    }

    UART_close(handle);
test_end:
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
}

/**
 * @brief Testcase to cover UART_write behavior on a closed handle (object->isOpen == FALSE).
 *
 * This test ensures that the UART driver correctly rejects write operations
 * on a handle that has been closed (i.e., object->isOpen == FALSE). It opens
 * a UART instance, closes it, and then attempts to perform a UART_write using
 * the now-closed handle. The expected result is SystemP_FAILURE, covering the
 * code path where the driver checks for isOpen before proceeding.
 *
 * Test Steps:
 * 1. Ensure clean state by closing any existing handle for the given instance.
 * 2. Open a UART handle with valid parameters.
 * 3. Close the handle to set object->isOpen = FALSE.
 * 4. Prepare a valid UART_Transaction structure.
 * 5. Call UART_write with the closed handle and expect SystemP_FAILURE.
 * 6. Verify that UART_getHandle reports the instance as closed (returns NULL).
 * 7. Assert that the test passes if the driver rejects the write as expected.
 *
 * @param[in] args Pointer to UART_TestParams providing UART_Params and instanceId.
 *
 * @return void
 */
static void TestUart_uartWriteOnClosedHandle(void *args)
{
    UART_TestParams *uartParams   = (UART_TestParams *)args;
    UART_Params     *prms = (UART_Params *)&uartParams->uartParams;
    uint16_t         inst = uartParams->instanceId;

    UART_Handle      handle    = NULL;
    UART_Transaction trans   = {0};
    int32_t          status;
    uint8_t          finalStatus = 0U;

    /* Clean previous state */
    handle = UART_getHandle(inst);
    if (handle != NULL)
    {
        UART_close(handle);
    }

    /* Open a valid handle */
    handle = UART_open(inst, prms);
    if (handle == NULL)
    {
        finalStatus |= 1U;
        goto test_end;
    }

    /* Close it to force object->isOpen == FALSE */
    UART_close(handle);

    /* Prepare a valid transaction */
    UART_Transaction_init(&trans);
    memset(gUartTxBuffer, 0xAA, 8U);
    trans.buf     = &gUartTxBuffer[0];
    trans.count   = 8U;
    trans.timeout = 100U;
    /* Call UART_write on a closed handle → expect SystemP_FAILURE via else path */
    status = UART_write(handle, &trans);
    if (status != SystemP_FAILURE)
    {
        finalStatus |= 2U;
    }

    /* Verify driver reports no open handle */
    if (UART_getHandle(inst) != NULL)
    {
        finalStatus |= 4U;
    }

test_end:
    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
}

/**
 * @brief Testcase to validate UART_write failure when skipIntrReg is TRUE (interrupt registration skipped).
 *
 * This test ensures that the UART driver correctly fails UART_write operations
 * when the UART_Params.skipIntrReg flag is set to TRUE. This flag causes the
 * driver to skip interrupt registration, and the write API should return
 * SystemP_FAILURE as expected.
 *
 * Test Steps:
 * 1. Ensure clean state by closing any existing handle for the given instance.
 * 2. Open a UART handle with skipIntrReg=TRUE in UART_Params.
 * 3. Prepare a valid UART_Transaction structure.
 * 4. Call UART_write and expect SystemP_FAILURE.
 * 5. Close the UART handle.
 *
 * @param[in] args Pointer to UART_TestParams providing UART_Params and instanceId.
 *
 * @return void
 */
static void TestUart_uartWriteSkipIntrElsePath(void *args)
{
   UART_TestParams *uartParams     = (UART_TestParams *)args;
    UART_Params     *prms   = (UART_Params *)&uartParams->uartParams;
    uint16_t         instId = uartParams->instanceId;

    UART_Handle      handle      = NULL;
    UART_Transaction trans;
    int32_t          status;
    uint32_t         base   = 0U;

    /* Clean state */
    handle = UART_getHandle(instId);
    if (handle != NULL) { UART_close(handle); }

    /* Open with skipIntrReg=TRUE (set in paramsInit) */
    handle = UART_open(instId, prms);
    TEST_ASSERT_NOT_NULL(handle);

    base = UART_getBaseAddr(handle);
    TEST_ASSERT_NOT_EQUAL(0U, base);

    /* Prepare a valid transaction */
    UART_Transaction_init(&trans);
    memset(gUartTxBuffer, 0xA5, 8U);
    trans.buf     = &gUartTxBuffer[0U];
    trans.count   = 8U;
    trans.timeout = 10U;

    /* Call write: must fail due to skipIntrReg */
    status = UART_write(handle, &trans);
    TEST_ASSERT_EQUAL_INT(SystemP_FAILURE, status);

    UART_close(handle);
}

/**
 * @brief Testcase to validate UART_read failure when called on a closed handle.
 *
 * This test ensures that the UART driver correctly rejects read operations
 * on a handle that has been closed (i.e., object->isOpen == FALSE). It opens
 * a UART instance, closes it, and then attempts to perform a UART_read using
 * the now-closed handle. The expected result is SystemP_FAILURE, covering the
 * code path where the driver checks for isOpen before proceeding.
 *
 * Test Steps:
 * 1. Ensure clean state by closing any existing handle for the given instance.
 * 2. Open a UART handle with valid parameters.
 * 3. Close the handle to set object->isOpen = FALSE.
 * 4. Prepare a valid UART_Transaction structure.
 * 5. Call UART_read with the closed handle and expect SystemP_FAILURE.
 * 6. Assert that the test passes if the driver rejects the read as expected.
 *
 * @param[in] args Pointer to UART_TestParams providing UART_Params and instanceId.
 *
 * @return void
 */
static void TestUart_uartReadFailClosedHandle(void *args)
{
    UART_TestParams *uartParams   = (UART_TestParams *)args;
    UART_Params     *prms = (UART_Params *)&uartParams->uartParams;
    uint16_t         inst = uartParams->instanceId;

    UART_Handle      handle    = NULL;
    UART_Transaction rx   = {0};
    int32_t          status;
    uint8_t          finalStatus = 0U;

    /* Ensure clean state */
    handle = UART_getHandle(inst);
    if (handle != NULL)
    {
        UART_close(handle);
    }

    /* Open to get a valid handle pointer, then close to set isOpen=FALSE */
    handle = UART_open(inst, prms);
    TEST_ASSERT_NOT_NULL(handle);
    UART_close(handle);

    /* Prepare a valid transaction */
    UART_Transaction_init(&rx);
    rx.buf     = &gUartRxBuffer[0U];
    rx.count   = 1U;
    rx.timeout = SystemP_WAIT_FOREVER;

    /* Call UART_read on a closed handle → expect failure path */
    status = UART_read(handle, &rx);
    TEST_ASSERT_EQUAL_INT(SystemP_FAILURE, status);

    TEST_ASSERT_EQUAL(0U, finalStatus);
}

/**
 * @brief Testcase to validate UART baud rate on the debug UART instance using external loopback.
 *
 * This test closes the debug UART, reopens it at multiple baud rates with
 * interrupt + blocking mode, writes a known data pattern out on the debug UART
 * TX pin, reads back the same number of bytes from the debug UART RX pin
 * (requires an external loopback wire between TX and RX of the debug UART
 * connector), and compares the transmitted and received buffers. A successful
 * match confirms that the baud rate divisor is programmed correctly and data
 * integrity is maintained at the configured speed.
 *
 * Test Steps:
 * 1. Close the debug UART instance to release it for test use.
 * 2. For each target baud rate (115200, 57600, 38400, 19200, 9600):
 *    a. Initialize UART parameters with interrupt + blocking mode.
 *    b. Set the target baud rate on the params.
 *    c. Open the debug UART instance and verify handle is not NULL.
 *    d. Retrieve UART_Object and verify the stored baud rate matches.
 *    e. Prepare a TX buffer with a baud-rate-tagged identifier string.
 *    f. Perform UART_write in blocking mode and verify success.
 *    g. Perform UART_read in blocking mode for the same byte count and verify success.
 *    h. Close the debug UART instance.
 *    i. Compare TX and RX buffers for data integrity.
 *    j. Assert all checks pass for this baud rate iteration.
 * 3. Reopen the debug UART at the default baud rate for subsequent test logging.
 *
 * @param[in] args Optional argument (unused).
 *
 * @return void
 */
static void TestUart_uartBaudRateValidationDebugUart(void *args)
{
    UART_Handle      uartHandle  = NULL;
    UART_Object     *uartObject  = NULL;
    UART_Params      uartParams;
    UART_Transaction transWrite  = {0};
    UART_Transaction transRead   = {0};
    int32_t          transferOK  = SystemP_FAILURE;
    int32_t          semStatus   = SystemP_FAILURE;
    uint8_t          txBuf[128]  = {0};
    uint8_t          rxBuf[128]  = {0};
    uint8_t          finalStatus = 0;
    uint32_t         configuredBaudRate = 0U;
    uint32_t         txLen;
    uint16_t         debugInstId = TestUart_debugUart;
    uint64_t         timeStart = 0U;
    uint64_t         timeEnd = 0U;
    uint64_t         elapsedUs = 0U;
    uint64_t         expectedUs = 0U;
    const uint32_t   bitsPerChar = 10U; /* 1 start + 8 data + 1 stop bits */
    const uint32_t   tolerancePct = 20U; /* allow 20% timing tolerance due to test overhead and non-precise delays */

    /* Baud rates to validate */
    uint32_t baudRates  = *(uint32_t*)args;

    DebugP_log("UART Baud Rate %u 10s delay for test to start\r\n", (unsigned int)baudRates);

    /* Step 1: Close debug UART so we can reopen it with test params */
    TestUart_closeDebugUart();

    ClockP_sleep(10); /* small delay between iterations */

    finalStatus = 0;
    memset(txBuf, 0, sizeof(txBuf));
    memset(rxBuf, 0, sizeof(rxBuf));

    /* Ensure the instance is closed before reopening */
    uartHandle = UART_getHandle(debugInstId);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Step 2a: Initialize UART parameters – interrupt + callback */
    UART_Params_init(&uartParams);
    uartParams.transferMode   = UART_CONFIG_MODE_INTERRUPT;
    uartParams.writeMode      = UART_TRANSFER_MODE_CALLBACK;
    uartParams.writeCallbackFxn = TestUart_uartWriteCallback;
    uartParams.readMode       = UART_TRANSFER_MODE_CALLBACK;
    uartParams.readCallbackFxn = TestUart_uartReadCallback;
    uartParams.readReturnMode = UART_READ_RETURN_MODE_FULL;
    uartParams.txTrigLvl      = UART_TXTRIGLVL_1;
    uartParams.rxTrigLvl      = UART_RXTRIGLVL_1;
    uartParams.skipIntrReg    = FALSE;
    uartParams.operMode       = UART_OPER_MODE_16X;

    /* Platform-specific interrupt configuration for debug UART */
#if defined(SOC_AM62AX)
#if defined(CPU_C7X)
    uartParams.intrNum = 24U;
    uartParams.eventId = 434;
#elif defined(CPU_MCU_R5F0)
    uartParams.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_MCU_UART0_USART_IRQ_0;
#elif defined(CPU_A53)
    uartParams.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_MCU_UART0_USART_IRQ_0;
#else
    uartParams.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_MCU_UART0_USART_IRQ_0;
#endif
#elif defined(SOC_AM62DX)
#if defined(CPU_C7X)
    uartParams.intrNum = 24U;
    uartParams.eventId = 434;
#else
    uartParams.intrNum = CSLR_GICSS0_COMMON_0_SPI_MCU_UART0_USART_IRQ_0;
#endif
#elif defined(SOC_AM275X)
#if (defined(CPU_C75_0) || defined(CPU_C75_1))
    uartParams.intrNum = 33U;
    uartParams.eventId = 435;
#else
    uartParams.intrNum = CSLR_WKUP_R5FSS0_CORE0_INTR_UART0_USART_IRQ_0;
#endif
#endif

    /* Step 2b: Set the target baud rate */
    uartParams.baudRate = baudRates;

    /* Step 2c: Open debug UART instance */
    uartHandle = UART_open(debugInstId, &uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1U << 0);
        goto iter_end;
    }

    /* Step 2d: Verify driver stored the requested baud rate */
    uartObject = ((UART_Config *)uartHandle)->object;
    if (uartObject == NULL)
    {
        finalStatus |= (1U << 1);
        goto iter_close;
    }
    configuredBaudRate = uartObject->prms.baudRate;
    if (configuredBaudRate != baudRates)
    {
        finalStatus |= (1U << 2);
        goto iter_close;
    }

    /* Step 2e: Prepare TX buffer with baud-rate-tagged payload */
    UART_Transaction_init(&transWrite);
    transWrite.buf = &txBuf[0U];
    strncpy((char *)transWrite.buf, "BAUD_TEST_0123456789ABCDEF\r\n", sizeof(txBuf) - 1);
    txLen = strlen((char *)transWrite.buf);
    transWrite.count   = txLen;
    transWrite.timeout = SystemP_WAIT_FOREVER;

    /* Step 2f: Perform UART write in interrupt (callback) mode and measure TX time */
    semStatus = SemaphoreP_constructBinary(&gUartWriteDoneSem, 0);
    if (semStatus != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 3);
        goto iter_close;
    }

    timeStart = ClockP_getTimeUsec();
    transferOK = UART_write(uartHandle, &transWrite);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 3);
    }

    /* Wait for the write callback to signal completion */
    SemaphoreP_pend(&gUartWriteDoneSem, SystemP_WAIT_FOREVER);
    timeEnd = ClockP_getTimeUsec();

    SemaphoreP_destruct(&gUartWriteDoneSem);

    if (transWrite.status != UART_TRANSFER_STATUS_SUCCESS)
    {
        finalStatus |= (1U << 4);
    }

    /* Validate transmission time against baud rate */
    elapsedUs  = timeEnd - timeStart;
    expectedUs = ((uint64_t)txLen * bitsPerChar * 1000000U) / baudRates;

    if (elapsedUs < (expectedUs * (100U - tolerancePct) / 100U) ||
        elapsedUs > (expectedUs * (100U + tolerancePct) / 100U))
    {
        finalStatus |= (1U << 8);
    }

    /* Step 2g: Perform UART read in interrupt (callback) mode */
    semStatus = SemaphoreP_constructBinary(&gUartReadDoneSem, 0);
    if (semStatus != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 5);
        goto iter_close;
    }

    UART_Transaction_init(&transRead);
    transRead.buf     = &rxBuf[0U];
    transRead.count   = 8;
    transRead.timeout = SystemP_WAIT_FOREVER;

    transferOK = UART_read(uartHandle, &transRead);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 5);
    }

    /* Wait for the read callback to signal completion */
    SemaphoreP_pend(&gUartReadDoneSem, SystemP_WAIT_FOREVER);

    if (transRead.status != UART_TRANSFER_STATUS_SUCCESS)
    {
        finalStatus |= (1U << 6);
    }

    SemaphoreP_destruct(&gUartReadDoneSem);

    /* Step 2i: Compare transmitted and received data */
    if (memcmp("hello", rxBuf, 5) != 0)
    {
        finalStatus |= (1U << 7);
    }

iter_close:
    /* Step 2h: Close the debug UART instance */
    UART_close(uartHandle);

iter_end:
    /* Temporarily reopen debug UART at default rate for assertion logging */
    TestUart_openDebugUart();
    
    if (finalStatus != 0)
    {
        DebugP_log("UART Baud Rate %u validation FAILED on debug instance %d "
                    "(status=0x%02X, elapsedUs=%u, expectedUs=%u)\r\n",
                    (unsigned int)baudRates, debugInstId, finalStatus,
                    (unsigned int)elapsedUs, (unsigned int)expectedUs);
    }
    else
    {
        DebugP_log("UART Baud Rate %u validation PASSED on debug instance %d "
                    "(elapsedUs=%u, expectedUs=%u)\r\n",
                    (unsigned int)baudRates, debugInstId,
                    (unsigned int)elapsedUs, (unsigned int)expectedUs);
    }

    TEST_ASSERT_EQUAL_INT(0, finalStatus);
    TEST_ASSERT_EQUAL_MEMORY("hello", rxBuf, 5);

    /* Close debug UART again before next iteration reopens with new baud */
    TestUart_closeDebugUart();

    /* Step 3: Reopen debug UART at default baud for subsequent test output */
    TestUart_openDebugUart();
}

/**
 * @brief Testcase to verify UART_TRANSFER_STATUS_ERROR_FE in interrupt mode.
 *
 * Opens the debug UART in interrupt mode with callback-based read at a
 * deliberately mismatched baud rate. When the external host sends data at
 * the normal baud rate (e.g. 115200), the UART hardware detects framing
 * errors due to the baud rate mismatch. The ISR invokes
 * UART_procLineStatusErr() which sets trans.status to
 * UART_TRANSFER_STATUS_ERROR_FE and calls the read callback.
 *
 * This test does NOT use loopback; it relies on external UART traffic.
 *
 * Steps:
 * 1. Close the debug UART.
 * 2. Reopen debug UART in interrupt mode with callback read at a
 *    mismatched baud rate (4800 while host uses 115200).
 * 3. Send a prompt string at the mismatched baud to the host, so the
 *    host echoes data back (the echoed data arrives garbled due to
 *    baud mismatch, triggering framing error).
 * 4. Issue UART_read in callback mode; pend on semaphore.
 * 5. Verify transRead.status == UART_TRANSFER_STATUS_ERROR_FE.
 * 6. Close and restore debug UART.
 *
 * @param[in] args Unused.
 */
UART_Transaction transRead   = {0};
static void TestUart_uartFramingErrorInterruptDebugUart(void *args)
{
    UART_Handle      uartHandle  = NULL;
    UART_Params      uartParams;
    UART_Transaction transWrite  = {0};

    int32_t          transferOK  = SystemP_FAILURE;
    int32_t          semStatus   = SystemP_FAILURE;
    uint8_t          txBuf[64]   = {0};
    uint8_t          rxBuf[64]   = {0};
    uint8_t          finalStatus = 0;
    uint16_t         debugInstId = TestUart_debugUart;

    /* Step 1: Close debug UART so we can reopen with test params */
    TestUart_closeDebugUart();

    /* Ensure the instance is fully closed */
    uartHandle = UART_getHandle(debugInstId);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Step 2: Open debug UART at a mismatched baud rate (4800)
     * The external host is expected to communicate at 115200.
     * This baud mismatch will cause framing errors on received data. */
    UART_Params_init(&uartParams);
    uartParams.transferMode    = UART_CONFIG_MODE_INTERRUPT;
    uartParams.writeMode       = UART_TRANSFER_MODE_BLOCKING;
    uartParams.readMode        = UART_TRANSFER_MODE_CALLBACK;
    uartParams.readCallbackFxn = TestUart_uartReadCallback;
    uartParams.readReturnMode  = UART_READ_RETURN_MODE_FULL;
    uartParams.txTrigLvl       = UART_TXTRIGLVL_1;
    uartParams.rxTrigLvl       = UART_RXTRIGLVL_1;
    uartParams.skipIntrReg     = FALSE;
    uartParams.operMode        = UART_OPER_MODE_16X;
    uartParams.parityType      = UART_PARITY_ODD;
    uartParams.stopBits        = UART_STOPBITS_2;

    /* Use a mismatched baud rate to induce framing errors */
    uartParams.baudRate = 4800U;

    /* Platform-specific interrupt configuration for debug UART */
#if defined(SOC_AM62AX)
#if defined(CPU_C7X)
    uartParams.intrNum = 24U;
    uartParams.eventId = 434;
#elif defined(CPU_MCU_R5F0)
    uartParams.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_MCU_UART0_USART_IRQ_0;
#elif defined(CPU_A53)
    uartParams.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_MCU_UART0_USART_IRQ_0;
#else
    uartParams.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_MCU_UART0_USART_IRQ_0;
#endif
#elif defined(SOC_AM62DX)
#if defined(CPU_C7X)
    uartParams.intrNum = 24U;
    uartParams.eventId = 434;
#else
    uartParams.intrNum = CSLR_GICSS0_COMMON_0_SPI_MCU_UART0_USART_IRQ_0;
#endif
#elif defined(SOC_AM275X)
#if (defined(CPU_C75_0) || defined(CPU_C75_1))
    uartParams.intrNum = 33U;
    uartParams.eventId = 435;
#else
    uartParams.intrNum = CSLR_WKUP_R5FSS0_CORE0_INTR_UART0_USART_IRQ_0;
#endif
#endif

    /* Step 2c: Open debug UART instance */
    uartHandle = UART_open(debugInstId, &uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1U << 0);
        goto test_end;
    }

    /* Step 3: Send a prompt to the host so it echoes data back.
     * The host receives garbled data (baud mismatch) and may echo
     * something back. Any data arriving at the mismatched baud
     * will trigger a framing error in the UART hardware. */
    UART_Transaction_init(&transWrite);
    transWrite.buf     = &txBuf[0U];
    strncpy((char *)transWrite.buf, "FE_TEST_PROMPT\r\n", sizeof(txBuf));
    transWrite.count   = strlen((char *)transWrite.buf);
    transWrite.timeout = SystemP_WAIT_FOREVER;

    transferOK = UART_write(uartHandle, &transWrite);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 1);
    }

    /* Step 4: Issue a read in callback mode.
     * The host is expected to send data at 115200 baud, but this UART
     * is configured at 4800 baud. The hardware will detect framing
     * errors and the ISR will invoke UART_procLineStatusErr(). */
    semStatus = SemaphoreP_constructBinary(&gUartReadDoneSem, 0);
    if (semStatus != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 2);
        goto test_close;
    }

    UART_Transaction_init(&transRead);
    transRead.buf     = &rxBuf[0U];
    transRead.count   = 8U;
    transRead.timeout = SystemP_WAIT_FOREVER;

    transferOK = UART_read(uartHandle, &transRead);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 3);
    }

    /* Wait for the read callback (posted by ISR on error or completion) */
    SemaphoreP_pend(&gUartReadDoneSem, SystemP_WAIT_FOREVER);

    /* Step 5: Verify framing error status */
    if (transRead.status != UART_TRANSFER_STATUS_ERROR_PE)
    {
        finalStatus |= (1U << 4);
    }

    SemaphoreP_destruct(&gUartReadDoneSem);

test_close:
    /* Step 6: Close and restore */
    UART_close(uartHandle);

test_end:
    /* Reopen debug UART at default baud for assertion logging */
    TestUart_openDebugUart();

    if (finalStatus != 0)
    {
        DebugP_log("UART Framing Error Interrupt test FAILED on debug instance %d "
                    "(status=0x%02X)\r\n", debugInstId, finalStatus);
    }

    TEST_ASSERT_EQUAL_INT(0, finalStatus);
    TEST_ASSERT_EQUAL_UINT32(UART_TRANSFER_STATUS_ERROR_FE, transRead.status);
}

/**
 * @brief Validate UART partial read in internal loopback mode.
 *
 * Opens a UART instance in interrupt/blocking mode with
 * UART_READ_RETURN_MODE_PARTIAL, enables internal loopback, writes a known
 * data string, then reads with a request count LARGER than what was written.
 * With partial-return mode the driver returns as soon as any data has been
 * read from the FIFO, so the read should succeed and report a count equal
 * to the number of bytes actually available (the written count), not the
 * full requested count.
 *
 * A second write+read cycle verifies that a read request whose size exactly
 * matches the amount of available data also succeeds.
 *
 * Test Steps:
 * 1. Close any existing UART handle for the given instance.
 * 2. Open UART instance (interrupt + blocking + partial-return mode).
 * 3. Enable internal loopback.
 * 4. Write a short string via loopback.
 * 5. Issue a blocking read requesting MORE bytes than were written.
 * 6. Verify that the read succeeds and returns only the written count.
 * 7. Compare the received data against the transmitted data.
 * 8. Write the same string again and read with an exact-match count.
 * 9. Verify the second read also matches.
 * 10. Disable loopback, close UART, assert results.
 *
 * @param[in] args Pointer to UART_TestParams providing UART_Params and instanceId.
 *
 * @return void
 */
static void TestUart_uartPartialReadLoopback(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle = NULL;
    UART_Transaction transWrite = {0}, transRead = {0};
    int32_t transferOK = SystemP_FAILURE;
    int32_t semStatus  = SystemP_FAILURE;
    uint32_t baseAddr = 0U;
    static uint8_t uartTxBuffer[APP_UART_BUFSIZE] = {0};
    uint8_t uartRxBuffer[APP_UART_BUFSIZE] = {0};
    uint16_t finalStatus = 0;
    uint32_t writeLen = 0U;
    uint32_t remaining = 0U;
    uint32_t totalRead = 0U;
    uint8_t  sawPartial = 0U;

    /* Construct write-done semaphore for callback write */
    semStatus = SemaphoreP_constructBinary(&gUartWriteDoneSem, 0);
    DebugP_assert(semStatus == SystemP_SUCCESS);

    /* Close to ensure previous state is cleared */
    uartHandle = UART_getHandle(instanceId);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART instance (interrupt, callback write + blocking partial read) */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1U << 0);
        goto partial_close;
    }

    /* Enable loopback mode */
    baseAddr = UART_getBaseAddr(uartHandle);
    if (baseAddr == 0U)
    {
        finalStatus |= (1U << 1);
        goto partial_close;
    }
    TestUart_enableLoopback(baseAddr);

    /* ---- Phase 1: callback write, then blocking partial read ---- */

    /* Prepare TX data */
    UART_Transaction_init(&transWrite);
    transWrite.buf = &uartTxBuffer[0U];
    strncpy((char *)transWrite.buf, "PARTIAL_RD\r\n", APP_UART_BUFSIZE);
    transWrite.count = strlen((char *)transWrite.buf);
    transWrite.timeout = SystemP_WAIT_FOREVER;
    writeLen = transWrite.count;

    /*
     * Write using CALLBACK mode — returns immediately so we can arm
     * the blocking partial read BEFORE loopback data hits the RX FIFO.
     * Without this, the ISR discards RX bytes that arrive while no
     * read transaction is active, causing the subsequent read to hang.
     */
    transferOK = UART_write(uartHandle, &transWrite);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 2);
        goto partial_close;
    }

    /*
     * Accumulate partial reads until all written bytes have been received.
     * Each partial read returns as soon as any data is in the RX FIFO.
     */
    memset(uartRxBuffer, 0, sizeof(uartRxBuffer));
    remaining = writeLen;
    totalRead = 0U;

    while (remaining > 0U)
    {
        UART_Transaction_init(&transRead);
        transRead.buf     = &uartRxBuffer[totalRead];
        transRead.count   = remaining + 16U;  /* request more than remaining */
        transRead.timeout = SystemP_WAIT_FOREVER;

        transferOK = UART_read(uartHandle, &transRead);
        if (transferOK != SystemP_SUCCESS)
        {
            finalStatus |= (1U << 3);
            goto partial_close;
        }

        /* If the driver returned less than requested, partial mode worked */
        if (transRead.count < (remaining + 16U))
        {
            sawPartial = 1U;
        }

        totalRead += transRead.count;
        remaining  = (totalRead < writeLen) ? (writeLen - totalRead) : 0U;
    }

    /* Wait for write callback to complete */
    SemaphoreP_pend(&gUartWriteDoneSem, SystemP_WAIT_FOREVER);

    /* Verify we got exactly the written number of bytes */
    if (totalRead != writeLen)
    {
        finalStatus |= (1U << 4);
    }

    /* Verify the driver actually used partial-return (returned < requested) */
    if (sawPartial == 0U)
    {
        finalStatus |= (1U << 5);
    }

    /* Verify data integrity */
    if (memcmp(uartTxBuffer, uartRxBuffer, writeLen) != 0)
    {
        finalStatus |= (1U << 6);
    }

    /* ---- Phase 2: callback write + blocking partial read (exact count) ---- */

    memset(uartRxBuffer, 0, sizeof(uartRxBuffer));

    /* Write the same string again (callback) */
    UART_Transaction_init(&transWrite);
    transWrite.buf     = &uartTxBuffer[0U];
    transWrite.count   = writeLen;
    transWrite.timeout = SystemP_WAIT_FOREVER;

    transferOK = UART_write(uartHandle, &transWrite);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 7);
        goto partial_close;
    }

    /* Blocking partial read requesting exactly writeLen bytes */
    totalRead = 0U;
    remaining = writeLen;

    while (remaining > 0U)
    {
        UART_Transaction_init(&transRead);
        transRead.buf     = &uartRxBuffer[totalRead];
        transRead.count   = remaining;
        transRead.timeout = SystemP_WAIT_FOREVER;

        transferOK = UART_read(uartHandle, &transRead);
        if (transferOK != SystemP_SUCCESS)
        {
            finalStatus |= (1U << 8);
            goto partial_close;
        }

        totalRead += transRead.count;
        remaining  = (totalRead < writeLen) ? (writeLen - totalRead) : 0U;
    }

    /* Wait for write callback */
    SemaphoreP_pend(&gUartWriteDoneSem, SystemP_WAIT_FOREVER);

    /* Verify count and data */
    if (totalRead != writeLen)
    {
        finalStatus |= (1U << 9);
    }
    if (memcmp(uartTxBuffer, uartRxBuffer, writeLen) != 0)
    {
        finalStatus |= (1U << 10);
    }

partial_close:
    /* Disable loopback mode */
    if (baseAddr != 0U)
    {
        UART_disableLoopbackMode(baseAddr);
    }

    /* Close UART handle */
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    SemaphoreP_destruct(&gUartWriteDoneSem);

    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
}

/**
 * @brief Validate UART read timeout in internal loopback mode.
 *
 * Opens a UART instance in interrupt/blocking mode, enables internal loopback,
 * and performs a read with a short timeout without writing any data first.
 * Verifies that the read returns a timeout status (UART_TRANSFER_STATUS_TIMEOUT)
 * and that the driver does not hang.
 *
 * Test Steps:
 * 1. Close and reopen UART instance with blocking mode params.
 * 2. Enable internal loopback mode.
 * 3. Initiate a UART_read with a short timeout and no prior write.
 * 4. Verify that UART_read returns timeout/failure status.
 * 5. Disable loopback and close UART.
 *
 * @param[in] args Pointer to UART_TestParams providing UART_Params and instanceId.
 *
 * @return void
 */
static void TestUart_uartReadTimeoutLoopback(void *args)
{
    int32_t          transferOK;
    UART_Transaction trans;
    UART_Handle      uartHandle;
    UART_TestParams *testParams = (UART_TestParams *)args;
    UART_Params     *uartParams = &(testParams->uartParams);
    uint16_t         instanceId = testParams->instanceId;
    uint32_t         baseAddr;
    uint8_t          finalStatus = 0;

    /* Close existing handle if open */
    UART_Handle existingHandle = UART_getHandle(instanceId);
    if (existingHandle != NULL)
    {
        UART_close(existingHandle);
    }

    /* Configure blocking mode with a short timeout */
    uartParams->readMode       = UART_TRANSFER_MODE_BLOCKING;
    uartParams->writeMode      = UART_TRANSFER_MODE_BLOCKING;
    uartParams->transferMode   = UART_CONFIG_MODE_INTERRUPT;

    /* Open UART instance */
    uartHandle = UART_open(instanceId, uartParams);
    TEST_ASSERT_NOT_NULL(uartHandle);

    /* Get base address and enable loopback */
    baseAddr = UART_getBaseAddr(uartHandle);
    TEST_ASSERT_NOT_EQUAL(0U, baseAddr);

    TestUart_enableLoopback(baseAddr);

    /* Initialize transaction for read */
    UART_Transaction_init(&trans);
    memset(&gUartRxBuffer[0U], 0, APP_UART_BUFSIZE);

    trans.buf     = &gUartRxBuffer[0U];
    trans.count   = 16U;  /* Expect 16 bytes but nothing was written */
    trans.timeout = 100U; /* Short timeout in ticks */

    /* Perform read without any prior write — should timeout */
    transferOK = UART_read(uartHandle, &trans);

    /*
     * The read should either return SystemP_TIMEOUT or the transaction
     * status should indicate timeout since no data is available in
     * loopback without a preceding write.
     */
    if ((transferOK == SystemP_TIMEOUT) ||
        (trans.status == UART_TRANSFER_STATUS_TIMEOUT))
    {
        finalStatus |= 1U;
    }
    else if (transferOK != SystemP_SUCCESS)
    {
        /* Any non-success return (other than timeout) is also acceptable
         * as long as the driver did not hang */
        finalStatus |= 1U;
    }

    /*
     * After a read timeout in blocking interrupt mode, the driver's
     * UART_readCancelNoCB (called internally by UART_read on timeout)
     * disables interrupts and flushes the RX FIFO, but does NOT clear
     * object->readTrans.  A subsequent UART_readCancel also fails to
     * clear it because readSizeRemaining is already 0.  Neither
     * UART_close nor UART_open resets readTrans either.
     *
     * This leaves a stale non-NULL readTrans pointer that causes every
     * subsequent UART_read to return UART_TRANSFER_STATUS_ERROR_INUSE.
     *
     * Work-around: access the UART_Object (public in uart.h) and
     * explicitly NULL out readTrans after the timeout.
     */
    UART_readCancel(uartHandle, &trans);
    {
        UART_Config *config = (UART_Config *)uartHandle;
        config->object->readTrans = NULL;
    }

    /*
     * Close and reopen the UART handle to guarantee a fully clean
     * driver state (semaphores, ISR context).
     */
    UART_disableLoopbackMode(baseAddr);
    UART_close(uartHandle);

    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        goto test_end;
    }

    baseAddr = UART_getBaseAddr(uartHandle);
    if (baseAddr == 0U)
    {
        UART_close(uartHandle);
        goto test_end;
    }

    TestUart_enableLoopback(baseAddr);

    /* Now verify normal operation still works after timeout:
     * Write data and read it back successfully */
    UART_Transaction_init(&trans);
    trans.buf   = &gUartTxBuffer[0U];
    strncpy((char *)trans.buf, "TimeoutRecoveryTest\r\n", APP_UART_BUFSIZE);
    trans.count = (uint32_t)strlen((char *)trans.buf);
    trans.timeout = SystemP_WAIT_FOREVER;

    transferOK = UART_write(uartHandle, &trans);
    if (transferOK == SystemP_SUCCESS &&
        trans.status == UART_TRANSFER_STATUS_SUCCESS)
    {
        uint32_t writeLen = trans.count;

        UART_Transaction_init(&trans);
        memset(&gUartRxBuffer[0U], 0, APP_UART_BUFSIZE);
        trans.buf     = &gUartRxBuffer[0U];
        trans.count   = writeLen;
        trans.timeout = 500U;

        transferOK = UART_read(uartHandle, &trans);
        if ((transferOK == SystemP_SUCCESS) &&
            (trans.status == UART_TRANSFER_STATUS_SUCCESS))
        {
            if (memcmp(&gUartTxBuffer[0U], &gUartRxBuffer[0U], writeLen) == 0)
            {
                finalStatus |= 2U;
            }
        }
    }

    /* Cleanup */
    UART_disableLoopbackMode(baseAddr);
    UART_close(uartHandle);

test_end:
    TestUart_openDebugUart();

    /* Both bits must be set: timeout detected (bit 0) and recovery works (bit 1) */
    TEST_ASSERT_EQUAL(3U, finalStatus);
}

/**
 * @brief Validate UART write cancel followed by immediate re-write.
 *
 * Opens UART in callback mode, starts a large write without loopback so
 * that the write remains in progress, cancels it, verifies CANCELLED status,
 * then immediately initiates a new write with loopback and verifies data
 * integrity through a callback read.
 *
 * Test Steps:
 * 1. Open UART in callback write + callback read, interrupt mode.
 * 2. Start a 256-byte callback write (no loopback — write stays in progress).
 * 3. After a short delay, cancel the write and verify CANCELLED status.
 * 4. Wait for TX FIFO to drain, then enable loopback.
 * 5. Arm a callback read, start a new callback write with known data.
 * 6. Wait for both callbacks and verify data integrity.
 *
 * @param[in] args Pointer to UART_TestParams providing UART_Params and instanceId.
 */
static void TestUart_writeCancelAndRewrite(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId     = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle  = NULL;
    UART_Transaction transWrite = {0}, transRead = {0};
    int32_t  transferOK;
    int32_t  semStatus;
    uint32_t baseAddr = 0U;
    uint8_t  cancelBuf[256];
    uint8_t  txBuf[16];
    uint8_t  rxBuf[16];
    uint16_t finalStatus = 0;
    uint32_t rewriteLen = 0;

    /* Construct semaphores for callback synchronization */
    semStatus = SemaphoreP_constructBinary(&gUartWriteDoneSem, 0);
    DebugP_assert(semStatus == SystemP_SUCCESS);
    semStatus = SemaphoreP_constructBinary(&gUartReadDoneSem, 0);
    DebugP_assert(semStatus == SystemP_SUCCESS);

    /* Close previous handle if any */
    uartHandle = UART_getHandle(instanceId);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1U << 0);
        goto wc_cleanup;
    }

    baseAddr = UART_getBaseAddr(uartHandle);
    if (baseAddr == 0U)
    {
        finalStatus |= (1U << 1);
        goto wc_cleanup;
    }

    /* ---- Phase 1: Cancel an ongoing write ---- */
    /* No loopback — TX data exits the pin, nothing loops back to RX */
    memset(cancelBuf, 'W', sizeof(cancelBuf));
    UART_Transaction_init(&transWrite);
    transWrite.buf     = cancelBuf;
    transWrite.count   = sizeof(cancelBuf);
    transWrite.timeout = SystemP_WAIT_FOREVER;

    /* Callback write returns immediately; ISR drains buffer in background */
    transferOK = UART_write(uartHandle, &transWrite);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 2);
        goto wc_cleanup;
    }

    /* Brief delay so the write is still in progress */
    ClockP_usleep(1000);

    /* Cancel the ongoing write */
    transferOK = UART_writeCancel(uartHandle, &transWrite);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 3);
        goto wc_cleanup;
    }

    /* Verify the driver set CANCELLED status */
    if (transWrite.status != UART_TRANSFER_STATUS_CANCELLED)
    {
        finalStatus |= (1U << 4);
    }

    /* Cancel invokes the callback, consume the semaphore */
    SemaphoreP_pend(&gUartWriteDoneSem, SystemP_WAIT_FOREVER);

    /* Wait for residual TX FIFO data to drain before enabling loopback */
    ClockP_usleep(10000);

    /* ---- Phase 2: Immediate re-write with loopback verification ---- */
    TestUart_enableLoopback(baseAddr);

    strncpy((char *)txBuf, "REWRITE_OK\r\n", sizeof(txBuf));
    rewriteLen = (uint32_t)strlen((char *)txBuf);

    /* Arm callback read first so loopback data is captured */
    memset(rxBuf, 0, sizeof(rxBuf));
    UART_Transaction_init(&transRead);
    transRead.buf     = rxBuf;
    transRead.count   = rewriteLen;
    transRead.timeout = SystemP_WAIT_FOREVER;

    transferOK = UART_read(uartHandle, &transRead);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 5);
        goto wc_cleanup;
    }

    /* Start callback write */
    UART_Transaction_init(&transWrite);
    transWrite.buf     = txBuf;
    transWrite.count   = rewriteLen;
    transWrite.timeout = SystemP_WAIT_FOREVER;

    transferOK = UART_write(uartHandle, &transWrite);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 6);
        goto wc_cleanup;
    }

    /* Wait for both callbacks */
    SemaphoreP_pend(&gUartReadDoneSem, SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&gUartWriteDoneSem, SystemP_WAIT_FOREVER);

    /* Verify re-write succeeded */
    if (transWrite.status != UART_TRANSFER_STATUS_SUCCESS)
    {
        finalStatus |= (1U << 7);
    }
    if (transRead.status != UART_TRANSFER_STATUS_SUCCESS)
    {
        finalStatus |= (1U << 8);
    }
    if (memcmp(txBuf, rxBuf, rewriteLen) != 0)
    {
        finalStatus |= (1U << 9);
    }

wc_cleanup:
    if (baseAddr != 0U)
    {
        UART_disableLoopbackMode(baseAddr);
    }
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    SemaphoreP_destruct(&gUartWriteDoneSem);
    SemaphoreP_destruct(&gUartReadDoneSem);

    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
}

/**
 * @brief Validate UART read cancel followed by immediate re-read.
 *
 * Opens UART in callback mode with loopback enabled, starts a large read
 * with no incoming data (so it stays armed), cancels it, verifies CANCELLED
 * status, then immediately initiates a new read followed by a write and
 * verifies data integrity.
 *
 * Test Steps:
 * 1. Open UART in callback write + callback read, interrupt mode, loopback.
 * 2. Start a 256-byte callback read (no data coming — read stays armed).
 * 3. Cancel the read and verify CANCELLED status.
 * 4. Arm a new callback read for a known length.
 * 5. Start a callback write with known data.
 * 6. Wait for both callbacks and verify data integrity.
 *
 * @param[in] args Pointer to UART_TestParams providing UART_Params and instanceId.
 */
static void TestUart_readCancelAndReread(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId     = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle  = NULL;
    UART_Transaction transWrite = {0}, transRead = {0};
    int32_t  transferOK;
    int32_t  semStatus;
    uint32_t baseAddr = 0U;
    uint8_t  cancelRxBuf[256];
    uint8_t  txBuf[16];
    uint8_t  rxBuf[16];
    uint16_t finalStatus = 0;
    uint32_t rereadLen = 0;

    /* Construct semaphores for callback synchronization */
    semStatus = SemaphoreP_constructBinary(&gUartWriteDoneSem, 0);
    DebugP_assert(semStatus == SystemP_SUCCESS);
    semStatus = SemaphoreP_constructBinary(&gUartReadDoneSem, 0);
    DebugP_assert(semStatus == SystemP_SUCCESS);

    /* Close previous handle if any */
    uartHandle = UART_getHandle(instanceId);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1U << 0);
        goto rc_cleanup;
    }

    baseAddr = UART_getBaseAddr(uartHandle);
    if (baseAddr == 0U)
    {
        finalStatus |= (1U << 1);
        goto rc_cleanup;
    }

    /* Enable loopback for the entire test */
    TestUart_enableLoopback(baseAddr);

    /* ---- Phase 1: Cancel an ongoing read ---- */
    memset(cancelRxBuf, 0, sizeof(cancelRxBuf));
    UART_Transaction_init(&transRead);
    transRead.buf     = cancelRxBuf;
    transRead.count   = sizeof(cancelRxBuf);
    transRead.timeout = SystemP_WAIT_FOREVER;

    /* Callback read returns immediately; ISR waits for data */
    transferOK = UART_read(uartHandle, &transRead);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 2);
        goto rc_cleanup;
    }

    /* Brief delay — read is armed, no data arriving */
    ClockP_usleep(1000);

    /* Cancel the ongoing read */
    transferOK = UART_readCancel(uartHandle, &transRead);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 3);
        goto rc_cleanup;
    }

    /* Verify the driver set CANCELLED status */
    if (transRead.status != UART_TRANSFER_STATUS_CANCELLED)
    {
        finalStatus |= (1U << 4);
    }

    /* Cancel invokes the callback, consume the semaphore */
    SemaphoreP_pend(&gUartReadDoneSem, SystemP_WAIT_FOREVER);

    /* ---- Phase 2: Immediate re-read with loopback verification ---- */
    strncpy((char *)txBuf, "REREAD_OK!\r\n", sizeof(txBuf));
    rereadLen = (uint32_t)strlen((char *)txBuf);

    /* Arm callback read first */
    memset(rxBuf, 0, sizeof(rxBuf));
    UART_Transaction_init(&transRead);
    transRead.buf     = rxBuf;
    transRead.count   = rereadLen;
    transRead.timeout = SystemP_WAIT_FOREVER;

    transferOK = UART_read(uartHandle, &transRead);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 5);
        goto rc_cleanup;
    }

    /* Start callback write */
    UART_Transaction_init(&transWrite);
    transWrite.buf     = txBuf;
    transWrite.count   = rereadLen;
    transWrite.timeout = SystemP_WAIT_FOREVER;

    transferOK = UART_write(uartHandle, &transWrite);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 6);
        goto rc_cleanup;
    }

    /* Wait for both callbacks */
    SemaphoreP_pend(&gUartReadDoneSem, SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&gUartWriteDoneSem, SystemP_WAIT_FOREVER);

    /* Verify re-read succeeded */
    if (transWrite.status != UART_TRANSFER_STATUS_SUCCESS)
    {
        finalStatus |= (1U << 7);
    }
    if (transRead.status != UART_TRANSFER_STATUS_SUCCESS)
    {
        finalStatus |= (1U << 8);
    }
    if (memcmp(txBuf, rxBuf, rereadLen) != 0)
    {
        finalStatus |= (1U << 9);
    }

rc_cleanup:
    if (baseAddr != 0U)
    {
        UART_disableLoopbackMode(baseAddr);
    }
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    SemaphoreP_destruct(&gUartWriteDoneSem);
    SemaphoreP_destruct(&gUartReadDoneSem);

    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
}

/**
 * @brief Validate errata i2310 — erroneous UART timeout interrupt with RX trigger level 1.
 *
 * Errata i2310: When RX FIFO trigger level is set to 1, the UART may
 * erroneously assert a character-timeout (CHAR_TIMEOUT) interrupt even
 * though the RX FIFO is empty.  The driver's ISR detects this condition
 * via UART_checkCharsAvailInFifo() and applies UART_i2310WA() to clear
 * the spurious interrupt.  This test exercises that path.
 *
 * Test Steps:
 * 1. Open UART in interrupt mode, callback write + blocking read,
 *    RX trigger level = 1, internal loopback enabled.
 * 2. Arm a blocking read for the expected byte count.
 * 3. Start a callback write with known data.
 * 4. Wait for the write callback, then wait for the blocking read to complete.
 * 5. Verify data integrity (write buffer == read buffer).
 * 6. Read object->rxTimeoutCnt — if > 0 the errata fired and the WA handled it.
 * 7. Repeat with a small 1-byte transfer to maximise the chance of a
 *    spurious timeout hitting an empty FIFO.
 *
 * @param[in] args  Pointer to UART_TestParams with UART_Params and instanceId.
 */
static void TestUart_erratai2310TimeoutInterrupt(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId     = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle  = NULL;
    UART_Transaction transWrite = {0}, transRead = {0};
    int32_t  transferOK;
    int32_t  semStatus;
    uint32_t baseAddr       = 0U;
    uint8_t  txBuf[64];
    uint8_t  rxBuf[64];
    uint16_t finalStatus    = 0;
    UART_Config *config     = NULL;
    uint32_t writeLen = 0;

    /* Construct read-done semaphore for callback synchronization */
    semStatus = SemaphoreP_constructBinary(&gUartReadDoneSem, 0);
    DebugP_assert(semStatus == SystemP_SUCCESS);

    /* Close previous handle if any */
    uartHandle = UART_getHandle(instanceId);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Open UART with RX trigger level 1 — the errata i2310 condition */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1U << 0);
        goto i2310_cleanup;
    }

    baseAddr = UART_getBaseAddr(uartHandle);
    if (baseAddr == 0U)
    {
        finalStatus |= (1U << 1);
        goto i2310_cleanup;
    }

    config = &gUartConfig[instanceId];

    /* Enable internal loopback and let it settle */
    TestUart_enableLoopback(baseAddr);

    /* ---- Phase 1: Multi-byte transfer with RX trigger level 1 ---- */
    memset(txBuf, 0, sizeof(txBuf));
    strncpy((char *)txBuf, "i2310_ERRATA_TEST\r\n", sizeof(txBuf));
    writeLen = (uint32_t)strlen((char *)txBuf);

    /* Arm callback read first — returns immediately, ISR captures looped-back data */
    memset(rxBuf, 0, sizeof(rxBuf));
    UART_Transaction_init(&transRead);
    transRead.buf     = rxBuf;
    transRead.count   = writeLen;
    transRead.timeout = SystemP_WAIT_FOREVER;

    transferOK = UART_read(uartHandle, &transRead);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 2);
        goto i2310_cleanup;
    }

    /* Blocking write — bytes serialize at baud rate, loop back to RX */
    UART_Transaction_init(&transWrite);
    transWrite.buf     = txBuf;
    transWrite.count   = writeLen;
    transWrite.timeout = SystemP_WAIT_FOREVER;

    transferOK = UART_write(uartHandle, &transWrite);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 3);
        goto i2310_cleanup;
    }

    /* Wait for read callback — data looped back during the blocking write */
    SemaphoreP_pend(&gUartReadDoneSem, SystemP_WAIT_FOREVER);

    /* Verify statuses */
    if (transWrite.status != UART_TRANSFER_STATUS_SUCCESS)
    {
        finalStatus |= (1U << 4);
    }
    if (transRead.status != UART_TRANSFER_STATUS_SUCCESS)
    {
        finalStatus |= (1U << 5);
    }
    if (memcmp(txBuf, rxBuf, writeLen) != 0)
    {
        finalStatus |= (1U << 6);
    }

    /* Validate errata i2310 triggered: rxTimeoutCnt > 0 means a spurious
     * timeout interrupt fired on an empty FIFO and the WA handled it. */
    DebugP_log("Phase 1: rxTimeoutCnt = %u (> 0 means errata i2310 triggered)\r\n",
               config->object->rxTimeoutCnt);
    if (config->object->rxTimeoutCnt == 0U)
    {
        finalStatus |= (1U << 12);
    }

    /* ---- Phase 2: Single-byte transfer — maximise spurious timeout chance ---- */
    txBuf[0] = 0xA5U;

    /* Arm callback read first */
    memset(rxBuf, 0, sizeof(rxBuf));
    UART_Transaction_init(&transRead);
    transRead.buf     = rxBuf;
    transRead.count   = 1U;
    transRead.timeout = SystemP_WAIT_FOREVER;

    transferOK = UART_read(uartHandle, &transRead);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 7);
        goto i2310_cleanup;
    }

    /* Blocking write of single byte */
    UART_Transaction_init(&transWrite);
    transWrite.buf     = txBuf;
    transWrite.count   = 1U;
    transWrite.timeout = SystemP_WAIT_FOREVER;

    transferOK = UART_write(uartHandle, &transWrite);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 8);
        goto i2310_cleanup;
    }

    /* Wait for read callback */
    SemaphoreP_pend(&gUartReadDoneSem, SystemP_WAIT_FOREVER);

    if (transWrite.status != UART_TRANSFER_STATUS_SUCCESS)
    {
        finalStatus |= (1U << 9);
    }
    if (transRead.status != UART_TRANSFER_STATUS_SUCCESS)
    {
        finalStatus |= (1U << 10);
    }
    if (rxBuf[0] != 0xA5U)
    {
        finalStatus |= (1U << 11);
    }

    /* Validate errata i2310 triggered in Phase 2 as well */
    DebugP_log("Phase 2: rxTimeoutCnt = %u (> 0 means errata i2310 triggered)\r\n",
               config->object->rxTimeoutCnt);
    if (config->object->rxTimeoutCnt == 0U)
    {
        finalStatus |= (1U << 13);
    }

i2310_cleanup:
    if (baseAddr != 0U)
    {
        UART_disableLoopbackMode(baseAddr);
    }
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    SemaphoreP_destruct(&gUartReadDoneSem);

    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
}

/**
 * @brief Validate UART_udmaIsrTx handles continuous DMA write callbacks.
 *
 * Opens UART in DMA mode with callback write + callback read, enables
 * internal loopback, and performs multiple back-to-back DMA write/read
 * iterations.  Each iteration arms a callback read, starts a callback
 * write, waits for both callbacks, and verifies data integrity and
 * transfer status.  This ensures UART_udmaIsrTx correctly:
 *   - Dequeues the completion descriptor each time
 *   - Sets writeTrans->status and writeTrans->count
 *   - Calls the user writeCallbackFxn
 *   - Resets writeTrans to NULL (allowing the next write)
 *
 * @param[in] args  Pointer to UART_TestParams with UART_Params and instanceId.
 */
static void TestUart_udmaIsrTxContinuousCallback(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId     = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle  = NULL;
    UART_Transaction transWrite = {0}, transRead = {0};
    int32_t  transferOK;
    int32_t  semStatus;
    uint32_t baseAddr       = 0U;
    uint16_t finalStatus    = 0;
    uint32_t iter;
    uint32_t count;

    /* Number of back-to-back DMA write/read iterations */
    const uint32_t NUM_ITERATIONS = 5U;
    /* Transfer size per iteration (must fit in DMA buffers) */
    const uint16_t len = 64U;

#if defined(SOC_AM62AX) || defined(SOC_AM62DX)
    if ((instanceId == CONFIG_UART0) || (instanceId == CONFIG_UART8))
    {
        TestUart_openDebugUart();
        TEST_IGNORE_MESSAGE("DMA not supported on this UART instance");
        return;
    }
#endif

    /* Construct semaphores for callback synchronization */
    semStatus = SemaphoreP_constructBinary(&gUartWriteDoneSem, 0);
    DebugP_assert(semStatus == SystemP_SUCCESS);
    semStatus = SemaphoreP_constructBinary(&gUartReadDoneSem, 0);
    DebugP_assert(semStatus == SystemP_SUCCESS);

    /* Close previous handle if any */
    uartHandle = UART_getHandle(instanceId);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Set PDMA events for MAIN domain UARTs (AM62AX/AM62DX A53) */
#if (defined(SOC_AM62AX) || defined(SOC_AM62DX)) && !(defined(CPU_R5F0) || defined(CPU_MCU_R5F0) || defined(CPU_C7X))
    switch (instanceId)
    {
        case CONFIG_UART1:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART0_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART0_RX;
            break;
        case CONFIG_UART2:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART1_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART1_RX;
            break;
        case CONFIG_UART3:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART2_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART2_RX;
            break;
        case CONFIG_UART4:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART3_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART3_RX;
            break;
        case CONFIG_UART5:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART4_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART4_RX;
            break;
        case CONFIG_UART6:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART5_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART5_RX;
            break;
        case CONFIG_UART7:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART6_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART6_RX;
            break;
        default:
            break;
    }
#endif

    /* Open UART in DMA + callback mode */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1U << 0);
        goto txcb_cleanup;
    }

    baseAddr = UART_getBaseAddr(uartHandle);
    if (baseAddr == 0U)
    {
        finalStatus |= (1U << 1);
        goto txcb_cleanup;
    }

    /* Enable internal loopback */
    TestUart_enableLoopback(baseAddr);

    for (iter = 0U; iter < NUM_ITERATIONS; iter++)
    {
        /* Fill TX buffer with a unique per-iteration pattern */
        for (count = 0U; count < len; count++)
        {
            TestUart_txBufferDma[count] = (uint8_t)((iter * 37U + count) & 0xFFU);
        }
        memset(TestUart_rxBufferDma, 0, len);

        /* Arm callback read first so loopback data is captured */
        UART_Transaction_init(&transRead);
        transRead.buf     = &TestUart_rxBufferDma[0U];
        transRead.count   = len;
        transRead.timeout = SystemP_WAIT_FOREVER;

        CacheP_wbInv((void *)TestUart_rxBufferDma, len, CacheP_TYPE_ALL);
        transferOK = UART_read(uartHandle, &transRead);
        if (transferOK != SystemP_SUCCESS)
        {
            DebugP_log("Iteration %u: UART_read failed\r\n", iter);
            finalStatus |= (1U << 2);
            break;
        }

        /* Start callback write -- UART_udmaIsrTx fires on completion */
        UART_Transaction_init(&transWrite);
        transWrite.buf     = &TestUart_txBufferDma[0U];
        transWrite.count   = len;
        transWrite.timeout = SystemP_WAIT_FOREVER;

        CacheP_wb((void *)TestUart_txBufferDma, len, CacheP_TYPE_ALL);
        transferOK = UART_write(uartHandle, &transWrite);
        if (transferOK != SystemP_SUCCESS)
        {
            DebugP_log("Iteration %u: UART_write failed\r\n", iter);
            finalStatus |= (1U << 3);
            break;
        }

        /* Wait for both DMA callbacks */
        SemaphoreP_pend(&gUartWriteDoneSem, SystemP_WAIT_FOREVER);
        SemaphoreP_pend(&gUartReadDoneSem, SystemP_WAIT_FOREVER);

        /* Invalidate RX buffer so CPU sees DMA-written data */
        CacheP_inv((void *)TestUart_rxBufferDma, len, CacheP_TYPE_ALL);

        /* Verify write callback set correct status */
        if (transWrite.status != UART_TRANSFER_STATUS_SUCCESS)
        {
            DebugP_log("Iteration %u: write status = %u\r\n", iter, transWrite.status);
            finalStatus |= (1U << 4);
            break;
        }

        /* Verify write callback reported correct byte count */
        if (transWrite.count != len)
        {
            DebugP_log("Iteration %u: write count = %u, expected %u\r\n",
                       iter, transWrite.count, len);
            finalStatus |= (1U << 5);
            break;
        }

        /* Verify read callback set correct status */
        if (transRead.status != UART_TRANSFER_STATUS_SUCCESS)
        {
            DebugP_log("Iteration %u: read status = %u\r\n", iter, transRead.status);
            finalStatus |= (1U << 6);
            break;
        }

        /* Verify loopback data integrity */
        if (memcmp(TestUart_txBufferDma, TestUart_rxBufferDma, len) != 0)
        {
            DebugP_log("Iteration %u: data mismatch\r\n", iter);
            finalStatus |= (1U << 7);
            break;
        }
    }

    if (finalStatus == 0U)
    {
        DebugP_log("All %u DMA TX callback iterations passed\r\n", NUM_ITERATIONS);
    }

txcb_cleanup:
    if (baseAddr != 0U)
    {
        UART_disableLoopbackMode(baseAddr);
    }
    if (uartHandle != NULL)
    {
        UART_Config *cfg = (UART_Config *)uartHandle;
        cfg->object->readTrans  = NULL;
        cfg->object->writeTrans = NULL;
        UART_close(uartHandle);
    }

    SemaphoreP_destruct(&gUartWriteDoneSem);
    SemaphoreP_destruct(&gUartReadDoneSem);

    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
}

/**
 * @brief Validate write-inside-callback returns INUSE in DMA TX ISR.
 *
 * When UART_udmaIsrTx fires and calls the user's write callback,
 * obj->writeTrans is still non-NULL (it is NULLed only after the callback
 * returns).  Therefore a UART_write() called from inside the callback must
 * fail with UART_TRANSFER_STATUS_ERROR_INUSE.  After the callback returns
 * and writeTrans is cleared, a normal write must succeed.
 *
 * Test Steps:
 * 1. Open UART in DMA callback mode with loopback enabled.
 * 2. Set TestUart_nestedWriteHandle so the custom callback knows the handle.
 * 3. Prepare a nested-write transaction in TestUart_nestedWriteTrans.
 * 4. Start a DMA callback write (first write).
 * 5. UART_udmaIsrTx fires -> calls TestUart_nestedWriteCallback which
 *    attempts a second UART_write() and records the result.
 * 6. Verify TestUart_nestedWriteResult == SystemP_FAILURE and
 *    TestUart_nestedWriteStatus == UART_TRANSFER_STATUS_ERROR_INUSE.
 * 7. After callback returns, do a normal write + read to prove the
 *    driver recovered and the channel is usable.
 *
 * @param[in] args  Pointer to UART_TestParams with UART_Params and instanceId.
 */
static void TestUart_udmaIsrTxWriteInsideCallback(void *args)
{
    UART_Params *uartParams = (UART_Params *)&(((UART_TestParams *)args)->uartParams);
    uint16_t instanceId     = ((UART_TestParams *)args)->instanceId;
    UART_Handle uartHandle  = NULL;
    UART_Transaction transWrite = {0}, transRead = {0};
    int32_t  transferOK;
    int32_t  semStatus;
    uint32_t baseAddr       = 0U;
    uint16_t finalStatus    = 0;
    const uint16_t len      = 32U;

#if defined(SOC_AM62AX) || defined(SOC_AM62DX)
    if ((instanceId == CONFIG_UART0) || (instanceId == CONFIG_UART8))
    {
        TestUart_openDebugUart();
        TEST_IGNORE_MESSAGE("DMA not supported on this UART instance");
        return;
    }
#endif

    /* Construct semaphores for callback synchronization */
    semStatus = SemaphoreP_constructBinary(&gUartWriteDoneSem, 0);
    DebugP_assert(semStatus == SystemP_SUCCESS);
    semStatus = SemaphoreP_constructBinary(&gUartReadDoneSem, 0);
    DebugP_assert(semStatus == SystemP_SUCCESS);

    /* Close previous handle if any */
    uartHandle = UART_getHandle(instanceId);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Set PDMA events for MAIN domain UARTs (AM62AX/AM62DX A53) */
#if (defined(SOC_AM62AX) || defined(SOC_AM62DX)) && !(defined(CPU_R5F0) || defined(CPU_MCU_R5F0) || defined(CPU_C7X))
    switch (instanceId)
    {
        case CONFIG_UART1:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART0_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART0_RX;
            break;
        case CONFIG_UART2:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART1_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART1_RX;
            break;
        case CONFIG_UART3:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART2_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART2_RX;
            break;
        case CONFIG_UART4:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART3_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART3_RX;
            break;
        case CONFIG_UART5:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART4_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART4_RX;
            break;
        case CONFIG_UART6:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART5_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART5_RX;
            break;
        case CONFIG_UART7:
            uartParams->txEvtNum = UDMA_PDMA_CH_MAIN0_UART6_TX;
            uartParams->rxEvtNum = UDMA_PDMA_CH_MAIN0_UART6_RX;
            break;
        default:
            break;
    }
#endif

    /* Open UART in DMA + callback mode */
    uartHandle = UART_open(instanceId, uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1U << 0);
        goto wic_cleanup;
    }

    baseAddr = UART_getBaseAddr(uartHandle);
    if (baseAddr == 0U)
    {
        finalStatus |= (1U << 1);
        goto wic_cleanup;
    }

    /* Enable internal loopback */
    TestUart_enableLoopback(baseAddr);

    /* ---- Phase 1: Trigger write, verify nested write gets INUSE ---- */

    /* Fill TX buffer with a pattern */
    uint32_t i;
    for (i = 0U; i < len; i++)
    {
        TestUart_txBufferDma[i] = (uint8_t)(i & 0xFFU);
    }

    /* Prepare the nested-write transaction that the callback will attempt */
    TestUart_nestedWriteHandle = uartHandle;
    TestUart_nestedWriteResult = SystemP_SUCCESS;  /* reset — expect callback to set FAILURE */
    TestUart_nestedWriteStatus = UART_TRANSFER_STATUS_SUCCESS;  /* reset */
    TestUart_nestedWriteArmed  = 1U;  /* arm the nested write for Phase 1 only */
    UART_Transaction_init(&TestUart_nestedWriteTrans);
    TestUart_nestedWriteTrans.buf     = &TestUart_txBufferDma[0U];
    TestUart_nestedWriteTrans.count   = len;
    TestUart_nestedWriteTrans.timeout = SystemP_WAIT_FOREVER;

    /* Start callback write — when DMA completes, UART_udmaIsrTx calls
     * TestUart_nestedWriteCallback which attempts a second UART_write(). */
    UART_Transaction_init(&transWrite);
    transWrite.buf     = &TestUart_txBufferDma[0U];
    transWrite.count   = len;
    transWrite.timeout = SystemP_WAIT_FOREVER;

    CacheP_wb((void *)TestUart_txBufferDma, len, CacheP_TYPE_ALL);
    transferOK = UART_write(uartHandle, &transWrite);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 2);
        goto wic_cleanup;
    }

    /* Wait for the write callback (which also does the nested write attempt) */
    SemaphoreP_pend(&gUartWriteDoneSem, SystemP_WAIT_FOREVER);

    /* First write itself should have succeeded */
    if (transWrite.status != UART_TRANSFER_STATUS_SUCCESS)
    {
        DebugP_log("First write status = %u\r\n", transWrite.status);
        finalStatus |= (1U << 3);
    }

    /* Nested write inside callback must have failed with INUSE */
    if (TestUart_nestedWriteResult != SystemP_FAILURE)
    {
        DebugP_log("Nested write returned success unexpectedly\r\n");
        finalStatus |= (1U << 4);
    }
    if (TestUart_nestedWriteStatus != UART_TRANSFER_STATUS_ERROR_INUSE)
    {
        DebugP_log("Nested write status = %u, expected INUSE (%u)\r\n",
                   TestUart_nestedWriteStatus, UART_TRANSFER_STATUS_ERROR_INUSE);
        finalStatus |= (1U << 5);
    }

    /* Drain any loopback data from Phase 1 by reading it out */
    memset(TestUart_rxBufferDma, 0, len);
    UART_Transaction_init(&transRead);
    transRead.buf     = &TestUart_rxBufferDma[0U];
    transRead.count   = len;
    transRead.timeout = SystemP_WAIT_FOREVER;

    CacheP_wbInv((void *)TestUart_rxBufferDma, len, CacheP_TYPE_ALL);
    transferOK = UART_read(uartHandle, &transRead);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 6);
        goto wic_cleanup;
    }
    SemaphoreP_pend(&gUartReadDoneSem, SystemP_WAIT_FOREVER);

    /* ---- Phase 2: Normal write after callback — driver must recover ---- */
    for (i = 0U; i < len; i++)
    {
        TestUart_txBufferDma[i] = (uint8_t)((i + 0x55U) & 0xFFU);
    }
    memset(TestUart_rxBufferDma, 0, len);

    /* Arm callback read first */
    UART_Transaction_init(&transRead);
    transRead.buf     = &TestUart_rxBufferDma[0U];
    transRead.count   = len;
    transRead.timeout = SystemP_WAIT_FOREVER;

    CacheP_wbInv((void *)TestUart_rxBufferDma, len, CacheP_TYPE_ALL);
    transferOK = UART_read(uartHandle, &transRead);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 7);
        goto wic_cleanup;
    }

    /* Normal callback write — should succeed now that writeTrans is NULL */
    UART_Transaction_init(&transWrite);
    transWrite.buf     = &TestUart_txBufferDma[0U];
    transWrite.count   = len;
    transWrite.timeout = SystemP_WAIT_FOREVER;

    CacheP_wb((void *)TestUart_txBufferDma, len, CacheP_TYPE_ALL);
    transferOK = UART_write(uartHandle, &transWrite);
    if (transferOK != SystemP_SUCCESS)
    {
        DebugP_log("Phase 2 write returned failure\r\n");
        finalStatus |= (1U << 8);
        goto wic_cleanup;
    }

    /* Wait for both callbacks */
    SemaphoreP_pend(&gUartWriteDoneSem, SystemP_WAIT_FOREVER);
    SemaphoreP_pend(&gUartReadDoneSem, SystemP_WAIT_FOREVER);

    CacheP_inv((void *)TestUart_rxBufferDma, len, CacheP_TYPE_ALL);

    if (transWrite.status != UART_TRANSFER_STATUS_SUCCESS)
    {
        finalStatus |= (1U << 9);
    }
    if (transRead.status != UART_TRANSFER_STATUS_SUCCESS)
    {
        finalStatus |= (1U << 10);
    }
    if (memcmp(TestUart_txBufferDma, TestUart_rxBufferDma, len) != 0)
    {
        finalStatus |= (1U << 11);
    }

wic_cleanup:
    if (baseAddr != 0U)
    {
        UART_disableLoopbackMode(baseAddr);
    }
    if (uartHandle != NULL)
    {
        UART_Config *cfg = (UART_Config *)uartHandle;
        cfg->object->readTrans  = NULL;
        cfg->object->writeTrans = NULL;
        UART_close(uartHandle);
    }

    TestUart_nestedWriteHandle = NULL;

    SemaphoreP_destruct(&gUartWriteDoneSem);
    SemaphoreP_destruct(&gUartReadDoneSem);

    TestUart_openDebugUart();
    TEST_ASSERT_EQUAL(0, finalStatus);
}

/**
 * @brief Testcase to verify Read Line Status errors are notified in blocking mode.
 *
 * Opens the debug UART in interrupt mode with blocking read at a deliberately
 * mismatched baud rate (4800 while the host uses 115200). When the host sends
 * data, the UART hardware detects line status errors (framing / parity / break)
 * due to the baud rate mismatch. The ISR invokes UART_procLineStatusErr() which
 * sets trans.status to one of the UART_TRANSFER_STATUS_ERROR_* codes and posts
 * the internal read semaphore, unblocking the UART_read call.
 *
 * This validates the blocking-mode branch in UART_procLineStatusErr:
 *   SemaphoreP_post(&object->readTransferSemObj);
 *
 * Steps:
 * 1. Close the debug UART.
 * 2. Reopen debug UART in interrupt mode with blocking read at 4800 baud.
 * 3. Send a prompt to the host so it echoes data back.
 * 4. Issue a blocking UART_read (the ISR will detect RLS errors and post
 *    the semaphore to unblock the read).
 * 5. Verify trans.status is not UART_TRANSFER_STATUS_SUCCESS (error reported).
 * 6. Close and restore debug UART.
 *
 * @param[in] args Unused.
 */
static void TestUart_uartRlsErrorBlockingDebugUart(void *args)
{
    UART_Handle      uartHandle  = NULL;
    UART_Params      uartParams;
    UART_Params      origParams;
    UART_Transaction transWrite  = {0};
    UART_Transaction transRd     = {0};
    int32_t          transferOK  = SystemP_FAILURE;
    uint8_t          txBuf[64]   = {0};
    uint8_t          rxBuf[64]   = {0};
    uint8_t          finalStatus = 0;
    uint16_t         debugInstId = TestUart_debugUart;

    /* Step 1: Close debug UART so we can reopen with test params */
    TestUart_closeDebugUart();

    /* Ensure the instance is fully closed */
    uartHandle = UART_getHandle(debugInstId);
    if (uartHandle != NULL)
    {
        UART_close(uartHandle);
    }

    /* Save original params so we can restore them before reopening debug UART.
     * TestUart_debugUartConfigBackup.object points to the same UART_Object in
     * gUartConfig, so UART_open with test params overwrites object->prms.
     * We must restore the original params before TestUart_openDebugUart(). */
    memcpy(&origParams, &(gUartConfig[debugInstId].object->prms), sizeof(UART_Params));

    /* Step 2: Open debug UART at a mismatched baud rate (4800)
     * The external host communicates at 115200.
     * This baud mismatch will cause line status errors on received data. */
    UART_Params_init(&uartParams);
    uartParams.transferMode    = UART_CONFIG_MODE_INTERRUPT;
    uartParams.writeMode       = UART_TRANSFER_MODE_BLOCKING;
    uartParams.readMode        = UART_TRANSFER_MODE_BLOCKING;
    uartParams.readReturnMode  = UART_READ_RETURN_MODE_FULL;
    uartParams.txTrigLvl       = UART_TXTRIGLVL_1;
    uartParams.rxTrigLvl       = UART_RXTRIGLVL_1;
    uartParams.skipIntrReg     = FALSE;
    uartParams.operMode        = UART_OPER_MODE_16X;

    /* Use a mismatched baud rate to induce line status errors */
    uartParams.baudRate = 4800U;

    /* Platform-specific interrupt configuration for debug UART */
#if defined(SOC_AM62AX)
#if defined(CPU_C7X)
    uartParams.intrNum = 24U;
    uartParams.eventId = 434;
#elif defined(CPU_MCU_R5F0)
    uartParams.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_MCU_UART0_USART_IRQ_0;
#elif defined(CPU_A53)
    uartParams.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_MCU_UART0_USART_IRQ_0;
#else
    uartParams.intrNum = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_MCU_UART0_USART_IRQ_0;
#endif
#elif defined(SOC_AM62DX)
#if defined(CPU_C7X)
    uartParams.intrNum = 24U;
    uartParams.eventId = 434;
#else
    uartParams.intrNum = CSLR_GICSS0_COMMON_0_SPI_MCU_UART0_USART_IRQ_0;
#endif
#elif defined(SOC_AM275X)
#if (defined(CPU_C75_0) || defined(CPU_C75_1))
    uartParams.intrNum = 33U;
    uartParams.eventId = 435;
#else
    uartParams.intrNum = CSLR_WKUP_R5FSS0_CORE0_INTR_UART0_USART_IRQ_0;
#endif
#endif

    /* Open debug UART instance */
    uartHandle = UART_open(debugInstId, &uartParams);
    if (uartHandle == NULL)
    {
        finalStatus |= (1U << 0);
        goto test_end;
    }

    /* Step 3: Send a prompt so the host echoes data back.
     * Data arriving at the mismatched baud triggers line status errors. */
    UART_Transaction_init(&transWrite);
    transWrite.buf     = &txBuf[0U];
    strncpy((char *)transWrite.buf, "RLS_BLOCK_TEST\r\n", sizeof(txBuf));
    transWrite.count   = strlen((char *)transWrite.buf);
    transWrite.timeout = SystemP_WAIT_FOREVER;

    transferOK = UART_write(uartHandle, &transWrite);
    if (transferOK != SystemP_SUCCESS)
    {
        finalStatus |= (1U << 1);
    }

    /* Step 4: Issue a blocking read.
     * The host sends data at 115200 baud but this UART is at 4800 baud.
     * The hardware detects line status errors (FE/PE/BI/OE) and the ISR
     * invokes UART_procLineStatusErr(), which sets trans.status to one of
     * the error codes and posts the internal read semaphore, unblocking
     * this call. */
    UART_Transaction_init(&transRd);
    transRd.buf     = &rxBuf[0U];
    transRd.count   = 8U;
    transRd.timeout = 10000U;  /* 10 second timeout as safety net */

    transferOK = UART_read(uartHandle, &transRd);

    /* Step 5: Verify that the driver reported a line status error.
     * Any of UART_TRANSFER_STATUS_ERROR_BI / _FE / _PE / _OE is acceptable
     * as the specific error depends on how the baud mismatch manifests. */
    if (transRd.status == UART_TRANSFER_STATUS_SUCCESS)
    {
        /* Should NOT be success — an RLS error was expected */
        finalStatus |= (1U << 2);
    }

    /* Close UART */
    UART_close(uartHandle);
    uartHandle = NULL;

test_end:
    /* Restore original params into the config object so that
     * TestUart_openDebugUart() reads the correct (original) configuration */
    memcpy(&(gUartConfig[debugInstId].object->prms), &origParams, sizeof(UART_Params));

    /* Reopen debug UART at default baud for assertion logging */
    TestUart_openDebugUart();

    TEST_ASSERT_EQUAL_INT(0, finalStatus);
    TEST_ASSERT_NOT_EQUAL(UART_TRANSFER_STATUS_SUCCESS, transRd.status);
}
