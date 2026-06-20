/*
 * Copyright (C) 2021-2025 Texas Instruments Incorporated
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

 #ifndef TEST_UART_H_
 #define TEST_UART_H_

/*===================================================================*/
/* 					      Include Files 					         */
/*===================================================================*/

#include <string.h>
#include <unity.h>
#include <kernel/dpl/CacheP.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/TaskP.h>
#include <drivers/hw_include/cslr_uart.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/*===================================================================*/
/* 					      Macro defines 					         */
/*===================================================================*/

#define APP_UART_BUFSIZE              (2048U)

/*===================================================================*/
/* 					         Typedefs 					             */
/*===================================================================*/

/* UART parameter structure */
typedef struct UART_TestParams_s
{
    uint16_t instanceId;
    UART_Params  uartParams;
} UART_TestParams;

/*===================================================================*/
/* 					         Global Variables			             */
/*===================================================================*/

/*===================================================================*/
/* 					         Function Declarations		             */
/*===================================================================*/

/* UART print message */
void TestUart_printMessage(const char *message, uint32_t length);
/* UART parameters initialization */
int TestUart_paramsInit(UART_TestParams *params, uint16_t tcId, uint16_t instanceId);
/* Open debug UART */
void TestUart_openDebugUart(void);
void TestUart_mtTestcase(void);

#endif /* TEST_DRIVERS_UART_TEST_UART_MT_H_ */
