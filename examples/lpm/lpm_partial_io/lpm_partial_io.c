/*
 *  Copyright (C) 2025 Texas Instruments Incorporated
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
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/TaskP.h>
#include <drivers/pinmux.h>
#include "ti_drivers_open_close.h"
#include "ti_drivers_config.h"
#include "ti_board_open_close.h"
#include "FreeRTOS.h"
#include "task.h"

/*
 * Example: Partial IO / IO Retention Low Power Mode Entry from MCU R5 Core
 * This example demonstrates how to trigger entry to partial IO or IO retention low power mode on the MCU
 * R5 core
 * Key Features:
 * - Enables MCU MCAN / MCU UART IO activity as wakeup source.
 * - Waits to receive a character on UART.
 * - If the character received is "P", then it requests device manager core to initiate low power mode entry.
 */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define LPM_APP_BACKUP_REG_0_OFFSET         0x0U
#define LPM_APP_WKUP_PAD_NUM_START          0x5U
#define LPM_APP_WKUP_PAD_NUM_END            0x16U
#define LPM_APP_WKUP_PAD_INVALID_VAL        0xFFU
#define LPM_APP_EARLY_WKUP_DETECTED         0x1U
#define LPM_APP_NORMAL_BOOT                 0x0U

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* UART transaction object and received character buffer */
UART_Transaction gLpmTrans;
SemaphoreP_Object gLpmPartialIO;
uint8_t gLpmRxByte;

#ifdef SOC_AM275X
static Pinmux_PerCfg_t gPinMuxWakeupEnableCfg[] = {

                             /* MCAN0_RX -> MCU_GPIO0_6 (B4) */
    {
        PIN_MCU_GPIO0_6,
        ( PIN_MODE(2) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE | PIN_WAKEUP_ENABLE )
    },
                             /* MCAN0_TX -> MCU_GPIO0_5 (C4) */
    {
        PIN_MCU_GPIO0_5,
        ( PIN_MODE(2) | PIN_PULL_DISABLE )
    },

    {PINMUX_END, 0U}
};
#elif defined(SOC_AM62DX)
static Pinmux_PerCfg_t gPinMuxWakeupEnableCfg[] = {

    /* MCU_USART0 pin config */
            /* MCU_UART0_RXD -> MCU_UART0_RXD (D8) */
    {
        PIN_MCU_UART0_RXD,
        ( PIN_MODE(0) | PIN_INPUT_ENABLE | PIN_PULL_DISABLE | PIN_WAKEUP_ENABLE )
    },
            /* MCU_UART0_TXD -> MCU_UART0_TXD (F8) */
    {
        PIN_MCU_UART0_TXD,
        ( PIN_MODE(0) | PIN_PULL_DISABLE )
    },

    {PINMUX_END, 0U}
};
#endif

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void LpmApp_readUARTCallback(UART_Handle handle, UART_Transaction *gLpmTrans);
static bool LpmApp_getWakeReason(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void LPMApp_partialIOMain(void *args)
{
    int32_t status;

    if (LpmApp_getWakeReason() == true)
    {
        DebugP_log("[LPM Partial IO APP] Woken up from Partial IO...\r\n");
    }
    else
    {
        DebugP_log("[LPM Partial IO APP] Example Application Started...\r\n");
    }

    /* This API must enable the wakeup sources to ensure that system is recoverable */
    Pinmux_config(gPinMuxWakeupEnableCfg, PINMUX_DOMAIN_ID_MCU);

    status = SemaphoreP_constructBinary(&gLpmPartialIO, 0);
    DebugP_assert(SystemP_SUCCESS == status);

    UART_Transaction_init(&gLpmTrans);
    /* Configure UART read parameters */
    gLpmTrans.buf   = &gLpmRxByte;
    gLpmTrans.count = 1U;

    DebugP_log("[LPM PARTIAL IO APP] Press 'P' to enter partial I/O\r\n");

    while (1U)
    {
        /* Initialize UART Read */
        UART_read(gUartHandle[CONFIG_UART0], &gLpmTrans);

        /* Wait for UART interrupt */
        SemaphoreP_pend(&gLpmPartialIO, SystemP_WAIT_FOREVER);

        if(gLpmRxByte == 'P')
        {

            DebugP_log("[LPM PARTIAL IO APP] Entering partial I/O\r\n");

            /* Send request to DM to enter partial IO low power mode */
            status = Sciclient_lpmSendPrepareSleepMessage(TISCI_MSG_VALUE_SLEEP_MODE_PARTIAL_IO, SystemP_WAIT_FOREVER);

            /* If system is unable to enter this mode, assert failure */
            DebugP_assert(SystemP_SUCCESS == status);

            break;
        }
    }

    SemaphoreP_destruct(&gLpmPartialIO);

    /* Close the drivers */
    Drivers_close();

    /* Deinit system */
    System_deinit();

    vTaskDelete(NULL);
}

void LpmApp_readUARTCallback(UART_Handle handle, UART_Transaction *trans)
{
    gLpmRxByte = *((uint8_t*)(gLpmTrans.buf));
    if (UART_TRANSFER_STATUS_SUCCESS == trans->status)
    {
        SemaphoreP_post(&gLpmPartialIO);
    }
}

static bool LpmApp_getWakeReason(void)
{
    uint32_t wakeupReason;
    bool isLPMExit = true;

    /* Get wake reason */
    wakeupReason = CSL_REG32_RD(CSL_WKUP_CTRL_MMR0_CFG0_BASE + CSL_WKUP_CTRL_MMR_CFG0_BACKUP_REG(LPM_APP_BACKUP_REG_0_OFFSET));

    /* If this is partial I/O resume */
    if (wakeupReason != LPM_APP_NORMAL_BOOT)
    {
    #ifdef SOC_AM275X
        if (wakeupReason == LPM_APP_EARLY_WKUP_DETECTED)
        {
            DebugP_log("[LPM PARTIAL IO APP] Resume detected from early wake event...\r\n");
        }
        else if (wakeupReason >= LPM_APP_WKUP_PAD_NUM_START && wakeupReason <= LPM_APP_WKUP_PAD_NUM_END)
    #else
        if (wakeupReason >= LPM_APP_WKUP_PAD_NUM_START && wakeupReason <= LPM_APP_WKUP_PAD_NUM_END)
    #endif
        {
            DebugP_log("[LPM PARTIAL IO APP] Resume detected from pad%d...\r\n", wakeupReason);
        }
        else if (wakeupReason == LPM_APP_WKUP_PAD_INVALID_VAL)
        {
            DebugP_log("[LPM PARTIAL IO APP] Resume detected: No valid pad detected...\r\n");
        }
    }
    else
    {
        isLPMExit = false;
    }

    return isLPMExit;
}
