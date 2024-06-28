/*
 *  Copyright (C) 2024 Texas Instruments Incorporated
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

#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/AddrTranslateP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/TaskP.h>
#include <drivers/i2c.h>
#include <drivers/gpio.h>
#include <drivers/mcasp.h>
#include <board/ioexp/ioexp_tca6424.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Audio buffer settings */
#define APP_MCASP_AUDIO_BUFF_COUNT  (4U)
#define APP_MCASP_AUDIO_BUFF_SIZE_RX   (2048U)
#define APP_MCASP_AUDIO_BUFF_SIZE_TX   (2048U/4U)

#define MCASP_TX_TASK_PRI           (8U)
#define MCASP_TX_TASK_STACK_SIZE    (32*1024U)

/* UDMA TR packet descriptor memory size - with one TR */
#define UDMA_TEST_TRPD_SIZE             (UDMA_GET_TRPD_TR15_SIZE(1U))

/* ========================================================================== */
/*                           Global Variables                                 */
/* ========================================================================== */

/* Create buffers for transmit and Receive */
uint8_t gMcaspAudioBufferTx[APP_MCASP_AUDIO_BUFF_COUNT][APP_MCASP_AUDIO_BUFF_SIZE_TX] __attribute__((aligned(256)));
uint8_t gMcaspAudioBufferRx[APP_MCASP_AUDIO_BUFF_COUNT][APP_MCASP_AUDIO_BUFF_SIZE_RX] __attribute__((aligned(256)));

/* Create transaction objects for transmit and Receive */
MCASP_Transaction   gMcaspAudioTxnTx[APP_MCASP_AUDIO_BUFF_COUNT] = {0};
MCASP_Transaction   gMcaspAudioTxnRx[APP_MCASP_AUDIO_BUFF_COUNT] = {0};

uint8_t gMcaspTaskStack[MCASP_TX_TASK_STACK_SIZE] __attribute__((aligned(32)));
TaskP_Object gMcaspTask;

SemaphoreP_Object gMcaspTxStartSem;

/* UDMA TRPD Memory */
uint8_t gUdmaTestTrpdMem[UDMA_TEST_TRPD_SIZE] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));

/* ========================================================================== */
/*                        Extern Function Declaration                         */
/* ========================================================================== */
int32_t Board_codecConfig(void);
int32_t Board_clockgenConfig(I2C_Handle handle, uint8_t devAddr);

void mcasp_udmaTrpdInit(Udma_ChHandle chHandle,
                             uint8_t *trpdMem,
                             const void *destBuf,
                             const void *srcBuf,
                             uint32_t length)
{
    CSL_UdmapTR15  *pTr;
    uint32_t        cqRingNum = Udma_chGetCqRingNum(chHandle);

    /* Make TRPD with TR15 TR type */
    UdmaUtils_makeTrpdTr15(trpdMem, 1U, cqRingNum);

    /* Setup TR */
    pTr = UdmaUtils_getTrpdTr15Pointer(trpdMem, 0U);
    pTr->flags    = CSL_FMK(UDMAP_TR_FLAGS_TYPE, CSL_UDMAP_TR_FLAGS_TYPE_4D_BLOCK_MOVE_REPACKING_INDIRECTION);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_STATIC, 0U);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EOL, CSL_UDMAP_TR_FLAGS_EOL_MATCH_SOL_EOL);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EVENT_SIZE, CSL_UDMAP_TR_FLAGS_EVENT_SIZE_COMPLETION);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0, CSL_UDMAP_TR_FLAGS_TRIGGER_NONE);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0_TYPE, CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ALL);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER1, CSL_UDMAP_TR_FLAGS_TRIGGER_NONE);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER1_TYPE, CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ALL);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_CMD_ID, 0x25U);  /* This will come back in TR response */
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_SA_INDIRECT, 0U);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_DA_INDIRECT, 0U);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EOP, 1U);
    pTr->icnt0    = sizeof(uint32_t);
    pTr->icnt1    = length/(4*sizeof(uint32_t));
    pTr->icnt2    = 1U;
    pTr->icnt3    = 1U;
    pTr->dim1     = (4*sizeof(uint32_t));
    pTr->dim2     = (pTr->icnt0 * pTr->icnt1);
    pTr->dim3     = (pTr->icnt0 * pTr->icnt1 * pTr->icnt2);
    pTr->addr     = (uint64_t) Udma_defaultVirtToPhyFxn(srcBuf, 0U, NULL);
    pTr->fmtflags = 0x00000000U;    /* Linear addressing, 1 byte per elem */
    pTr->dicnt0   = length/4;
    pTr->dicnt1   = 1U;
    pTr->dicnt2   = 1U;
    pTr->dicnt3   = 1U;
    pTr->ddim1    = pTr->dicnt0;
    pTr->ddim2    = (pTr->dicnt0 * pTr->dicnt1);
    pTr->ddim3    = (pTr->dicnt0 * pTr->dicnt1 * pTr->dicnt2);
    pTr->daddr    = (uint64_t) Udma_defaultVirtToPhyFxn(destBuf, 0U, NULL);

    /* Perform cache writeback */
    CacheP_wb(trpdMem, UDMA_TEST_TRPD_SIZE, CacheP_TYPE_ALLD);

    return;
}

void mcasp_tx_task(void *args)
{
    int32_t status;
    Udma_ChHandle chHandle;
    uint8_t *trpdMem = &gUdmaTestTrpdMem[0U];
    uint64_t trpdMemPhy = (uint64_t) Udma_defaultVirtToPhyFxn(trpdMem, 0U, NULL);
    uint32_t txIdx = APP_MCASP_AUDIO_BUFF_COUNT;
    uint32_t trRespStatus;
    uint64_t pDesc;
    MCASP_Handle mcaspHandle;

    mcaspHandle = MCASP_getHandle(CONFIG_MCASP0);

    chHandle = gConfigUdma0BlkCopyChHandle[0];

    /* Channel enable */
    status = Udma_chEnable(chHandle);
    DebugP_assert(SystemP_SUCCESS == status);

    while(1)
    {
        SemaphoreP_pend(&gMcaspTxStartSem, SystemP_WAIT_FOREVER);

        txIdx = (txIdx+1)%APP_MCASP_AUDIO_BUFF_COUNT;

        mcasp_udmaTrpdInit(chHandle, trpdMem, &gMcaspAudioBufferTx[txIdx], &gMcaspAudioBufferRx[txIdx],
                            APP_MCASP_AUDIO_BUFF_SIZE_RX);

        /* Submit TRPD to channel */
        status = Udma_ringQueueRaw(Udma_chGetFqRingHandle(chHandle), trpdMemPhy);
        DebugP_assert(status == SystemP_SUCCESS);

        while (1)
        {
            status = Udma_ringDequeueRaw(Udma_chGetCqRingHandle(chHandle), &pDesc);
            ClockP_usleep(50);
            if(SystemP_SUCCESS == status)
            {
                /* Check TR response status */
                CacheP_inv(trpdMem, UDMA_TEST_TRPD_SIZE, CacheP_TYPE_ALLD);
                trRespStatus = UdmaUtils_getTrpdTr15Response(trpdMem, 1U, 0U);
                DebugP_assert(CSL_UDMAP_TR_RESPONSE_STATUS_COMPLETE == trRespStatus);
                break;
            }
        }

        MCASP_submitTx(mcaspHandle, &gMcaspAudioTxnTx[txIdx]);
        MCASP_submitRx(mcaspHandle, &gMcaspAudioTxnRx[txIdx]);
    }
}

void mcasp_playback_main(void *args)
{
    int32_t     status = SystemP_SUCCESS;
    uint32_t    i;
    MCASP_Handle    mcaspHandle;
    char            valueChar;
    TaskP_Params taskParams;

    I2C_Handle      i2cHandle;
    i2cHandle = gI2cHandle[CONFIG_I2C0];

    /* Configure clock generator for getting the external HCLK */
    status = Board_clockgenConfig(i2cHandle, 0x68);
    DebugP_assert(status == SystemP_SUCCESS);

    ClockP_usleep(100);

    /* Open MCASP driver after enabling the HCLK */
    gMcaspHandle[0] = MCASP_open(0, &gMcaspOpenParams[0]);
    if(NULL == gMcaspHandle[0])
    {
        DebugP_logError("MCASP open failed for instance 0 !!!\r\n");
        DebugP_assert(false);
    }

    ClockP_usleep(100);

    /* Configure codec */
    status = Board_codecConfig();
    DebugP_assert(status == SystemP_SUCCESS);

    /* Construct Semaphore */
    SemaphoreP_constructBinary(&gMcaspTxStartSem, 0);

    /* Construct task to submit TX */
    TaskP_Params_init(&taskParams);
    taskParams.name = "MCASP_TX_TASK";
    taskParams.stackSize = MCASP_TX_TASK_STACK_SIZE;
    taskParams.stack = gMcaspTaskStack;
    taskParams.priority = MCASP_TX_TASK_PRI;
    taskParams.taskMain = mcasp_tx_task;

    status = TaskP_construct(&gMcaspTask, &taskParams);
    DebugP_assert(status == SystemP_SUCCESS);

    DebugP_log("[MCASP] Audio playback example started.\r\n");

    mcaspHandle = MCASP_getHandle(CONFIG_MCASP0);

    /* Prepare and submit audio transaction transmit objects */
    for (i = 0U; i < APP_MCASP_AUDIO_BUFF_COUNT; i++)
    {
        gMcaspAudioTxnTx[i].buf = (void*) &gMcaspAudioBufferTx[i][0];
        gMcaspAudioTxnTx[i].count = APP_MCASP_AUDIO_BUFF_SIZE_TX/4;
        gMcaspAudioTxnTx[i].timeout = 0xFFFFFF;
        MCASP_submitTx(mcaspHandle, &gMcaspAudioTxnTx[i]);
    }

    /* Prepare and submit audio transaction receive objects */
    for (i = 0U; i < APP_MCASP_AUDIO_BUFF_COUNT; i++)
    {
        gMcaspAudioTxnRx[i].buf = (void*) &gMcaspAudioBufferRx[i][0];
        gMcaspAudioTxnRx[i].count = APP_MCASP_AUDIO_BUFF_SIZE_RX/4;
        gMcaspAudioTxnRx[i].timeout = 0xFFFFFF;
        MCASP_submitRx(mcaspHandle, &gMcaspAudioTxnRx[i]);
    }

    /* Trigger McASP receive operation */
    status = MCASP_startTransferRx(mcaspHandle);
    DebugP_assert(status == SystemP_SUCCESS);

    /* Trigger McASP transmit operation */
    status = MCASP_startTransferTx(mcaspHandle);
    DebugP_assert(status == SystemP_SUCCESS);

    DebugP_log("Enter your response on UART terminal");

    do
    {
        DebugP_log("\r\nStop the demo? (y/n) : ");
        status = DebugP_scanf("%c", &valueChar);
        DebugP_assert(status == SystemP_SUCCESS);
    } while (valueChar != 'y');

    MCASP_stopTransferTx(mcaspHandle);
    MCASP_stopTransferRx(mcaspHandle);

    DebugP_log("Exiting demo\r\n");
}

void mcasp_txcb(MCASP_Handle handle,
                          MCASP_Transaction *transaction)
{
    /* Transaction resubmission done from mcasp_tx_task() */
}

void mcasp_rxcb(MCASP_Handle handle,
                          MCASP_Transaction *transaction)
{
    SemaphoreP_post(&gMcaspTxStartSem);
}
