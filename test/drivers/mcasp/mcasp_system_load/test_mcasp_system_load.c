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

/*
 * This Test validated MCASP operation does not trigger an underrun under
 * system load. The system load is emulated by DSP creating DDR traffic by
 * continuously writing to DDR.
 * MCASP is configured for TX at 96KHz 16 channels.
 *
 * If MCASP transactions are not prioritsed under system load condition,
 * MCASP will run into an underrun and the test will fail.
*/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <kernel/dpl/DebugP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "drivers/mcasp.h"
#include <string.h>

/* ========================================================================== */
/*                           Macro Defines                                    */
/* ========================================================================== */

#define APP_MCASP_MSGSIZE       (1280U)
#define APP_MCASP_MSG_COUNT     (2U)
#define APP_MCASP_TEST_COUNT    (300000U)

/* ========================================================================== */
/*                           Global Variables                                 */
/* ========================================================================== */

uint8_t gMcaspTxBuffer[APP_MCASP_MSG_COUNT][APP_MCASP_MSGSIZE] __attribute__((aligned(256)));
MCASP_Transaction   txnTx[APP_MCASP_MSG_COUNT] = {0};
volatile uint32_t    gMcaspTestCntRx = 0;
extern uint8_t gTxLoopjobBuf0[];
volatile uint32_t gMcaspTestCntTx = 0;

/* ========================================================================== */
/*                  Function Declarations                                     */
/* ========================================================================== */

void test_mcasp_system_load(void *args)
{
    int32_t             status = SystemP_SUCCESS;
    uint32_t            i=0, j=0;
    MCASP_Handle mcaspHandle;

    DebugP_log("[MCASP] System load test started.\r\n");

    /* Memfill buffers */
    for (i = 0U; i < APP_MCASP_MSG_COUNT; i++)
    {
        for(j = 0U; j < APP_MCASP_MSGSIZE; j++)
        {
            gMcaspTxBuffer[i][j] = j % 256;
        }
    }

    CacheP_wb(gMcaspTxBuffer, APP_MCASP_MSG_COUNT * APP_MCASP_MSGSIZE, CacheP_TYPE_ALL);

    mcaspHandle = MCASP_getHandle(CONFIG_MCASP0);

    for (i = 0U; i < APP_MCASP_MSG_COUNT; i++)
    {
        txnTx[i].buf = (void*) &gMcaspTxBuffer[i][0];
        txnTx[i].count = APP_MCASP_MSGSIZE/4;
        txnTx[i].timeout = 0xFFFFFF;
        MCASP_submitTx(mcaspHandle, &txnTx[i]);
    }

    /* Wait for system to be loaded */
    IpcNotify_syncAll(SystemP_WAIT_FOREVER);

    status = MCASP_startTransferTx(mcaspHandle);
    DebugP_assert(status == SystemP_SUCCESS);

    while (gMcaspTestCntTx < APP_MCASP_TEST_COUNT )
    {
        /* wait for transfer completion. */
    }

    MCASP_stopTransferTx(mcaspHandle);

    if(SystemP_SUCCESS == status)
    {
        DebugP_log("All tests have passed!!\r\n");
    }
    else
    {
        DebugP_log("Some tests have failed\r\n");
    }

    return;
}

void mcasp_loopback_txcb (MCASP_Handle handle,
                          MCASP_Transaction *transaction)
{
    if (gMcaspTestCntTx < APP_MCASP_TEST_COUNT+1)
    {
        gMcaspTestCntTx++;
        MCASP_submitTx(handle, transaction);
    }
}
