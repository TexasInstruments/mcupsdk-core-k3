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

#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/AddrTranslateP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/DebugP.h>
#include <drivers/i2c.h>
#include <drivers/mcasp.h>
#include <board/ioexp/ioexp_tca6424.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <drivers/pinmux.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Audio buffer settings */
#define APP_AUDIO_RECEIVE_TRANSACTION_COUNT    (8U)
#define APP_AUDIO_TRANSMIT_TRANSACTION_COUNT   (8U)

#define APP_AUDIO_RECEIVE_SAMPLE_BUFF_SIZE     (512U)
#define APP_AUDIO_TRANSMIT_SAMPLE_BUFF_SIZE    (1024U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
typedef struct
{
    AASRC_ChHandle    aasrcChHandle ;
    AASRC_Transaction *aasrcTxn;
} App_McaspTxnArgs;

typedef struct
{
    MCASP_Handle          mcaspHandle;
    MCASP_Transaction    *mcaspTxn;
} App_AasrcTxnArgs;

/* ========================================================================== */
/*                           Global Variables                                 */
/* ========================================================================== */

/*
 * MCASP
 * MCASP transaction objects for transmit and Receive
 */
MCASP_Transaction   gMcaspAudioTxnTx[APP_AUDIO_TRANSMIT_TRANSACTION_COUNT] = {0};
MCASP_Transaction   gMcaspAudioTxnRx[APP_AUDIO_RECEIVE_TRANSACTION_COUNT] = {0};

App_McaspTxnArgs gMcaspTransmitTxnArgs[APP_AUDIO_TRANSMIT_TRANSACTION_COUNT] =   {0};
App_McaspTxnArgs gMcaspReceiveTxnArgs[APP_AUDIO_RECEIVE_TRANSACTION_COUNT] =   {0};

/*
 * AASRC
 * AASRC transaction objects for transmit and Receive
 */
AASRC_Transaction gAasrcAudioTxnTx[APP_AUDIO_TRANSMIT_TRANSACTION_COUNT] = {0};
AASRC_Transaction gAasrcAudioTxnRx[APP_AUDIO_RECEIVE_TRANSACTION_COUNT] = {0};

App_AasrcTxnArgs  gAasrcTransmitTxnArgs[APP_AUDIO_TRANSMIT_TRANSACTION_COUNT] =   {0};
App_AasrcTxnArgs  gAasrcReceiveTxnArgs[APP_AUDIO_RECEIVE_TRANSACTION_COUNT] =   {0};

/* Buffers for audio transmit and Receive */
uint32_t gAudioBufferTx[APP_AUDIO_TRANSMIT_TRANSACTION_COUNT][APP_AUDIO_TRANSMIT_SAMPLE_BUFF_SIZE] __attribute__((aligned(256)));
uint32_t gAudioBufferRx[APP_AUDIO_RECEIVE_TRANSACTION_COUNT][APP_AUDIO_RECEIVE_SAMPLE_BUFF_SIZE] __attribute__((aligned(256)));

/* ========================================================================== */
/*                              Function Declaration                          */
/* ========================================================================== */

int32_t Board_codecConfig(void);
int32_t Board_clockgenConfig(I2C_Handle handle, uint8_t devAddr);
void App_initTransaction(MCASP_Handle mcaspHandle, AASRC_Handle aasrcHandle);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void aasrc_multichannel_playback(void *args)
{
    int32_t     status = SystemP_SUCCESS;
    MCASP_Handle    mcaspHandle =NULL;
    AASRC_ChHandle  chHandle = NULL;
    char            valueChar;

    I2C_Handle      i2cHandle;
    i2cHandle = gI2cHandle[CONFIG_I2C0];

#if defined (SOC_AM275X)
    Pinmux_PerCfg_t extClkPinmuxConfig[] =
    {
        {
            PIN_GPIO1_72,
            ( PIN_MODE(1) | PIN_INPUT_ENABLE | PIN_PULL_DIRECTION  )
        },
        {PINMUX_END, 0U}
    };

    Pinmux_config(extClkPinmuxConfig, PINMUX_DOMAIN_ID_MAIN);
#endif

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

    /* Configure codec */
    status = Board_codecConfig();
    DebugP_assert(status == SystemP_SUCCESS);

    DebugP_log("[AASRC] Audio playback example started.\r\n");

    mcaspHandle = MCASP_getHandle(CONFIG_MCASP0);
    chHandle = AASRC_getChHandle(CONFIG_AASRC0, 0);

    if(status ==  SystemP_SUCCESS)
    {
        /* Init MCASP & AASRC transactions */
        App_initTransaction(mcaspHandle, chHandle);

        /* Trigger McASP receive operation */
        status = MCASP_startTransferRx(mcaspHandle);
        DebugP_assert(status == SystemP_SUCCESS);

        /* Trigger McASP transmit operation */
        status = MCASP_startTransferTx(mcaspHandle);
        DebugP_assert(status == SystemP_SUCCESS);

        /* Trigger AASRC conversion operation */
        status = AASRC_chEnable(chHandle);

        DebugP_log("Enter your response on UART terminal");

        do
        {
            DebugP_log("\r\nStop the demo? (y/n) : ");
            status = DebugP_scanf("%c", &valueChar);
            DebugP_assert(status == SystemP_SUCCESS);
        } while (valueChar != 'y');

        MCASP_stopTransferTx(mcaspHandle);
        MCASP_stopTransferRx(mcaspHandle);
        status = AASRC_chClose(chHandle);

        DebugP_log("Exiting demo\r\n");
    }
    else
    {
        DebugP_log("AASRC channel open failed\r\n");
    }
}

void App_initTransaction(MCASP_Handle mcaspHandle, AASRC_ChHandle aasrcChHandle)
{
    uint8_t i = 0U;

    /* Preapre MCASP & AASRC Transmit transactions for 96 kHZ */
    for (i = 0U; i < APP_AUDIO_TRANSMIT_TRANSACTION_COUNT; i++)
    {
        /* Submit MCASP Transmit Txn */
        gMcaspAudioTxnTx[i].buf = (void*) &gAudioBufferTx[i][0];
        gMcaspAudioTxnTx[i].count = APP_AUDIO_TRANSMIT_SAMPLE_BUFF_SIZE;
        gMcaspAudioTxnTx[i].timeout = 0xFFFFFF;
        gMcaspAudioTxnTx[i].args = (void *)&gMcaspTransmitTxnArgs[i];
        MCASP_submitTx(mcaspHandle, &gMcaspAudioTxnTx[i]);

        /* Submit AASRC Trasmit Txn */
        gAasrcAudioTxnTx[i].buf = (void*) &gAudioBufferTx[i][0];
        gAasrcAudioTxnTx[i].sampleCount = APP_AUDIO_TRANSMIT_SAMPLE_BUFF_SIZE;
        gAasrcAudioTxnTx[i].args = (void *)&gAasrcTransmitTxnArgs[i];;
        AASRC_queueTransactionTx( aasrcChHandle, &gAasrcAudioTxnTx[i]);

        gMcaspTransmitTxnArgs[i].aasrcChHandle = aasrcChHandle;
        gMcaspTransmitTxnArgs[i].aasrcTxn = &gAasrcAudioTxnTx[i];

        gAasrcTransmitTxnArgs[i].mcaspHandle = mcaspHandle;
        gAasrcTransmitTxnArgs[i].mcaspTxn = &gMcaspAudioTxnTx[i];
    }

    /* Preapre MCASP & AASRC receive transactions for 48 kHZ */
    for (i = 0U; i < APP_AUDIO_RECEIVE_TRANSACTION_COUNT; i++)
    {
        /* Submit MCASP Recieve Rxn */
        gMcaspAudioTxnRx[i].buf = (void*) &gAudioBufferRx[i][0];
        gMcaspAudioTxnRx[i].count = APP_AUDIO_RECEIVE_SAMPLE_BUFF_SIZE;
        gMcaspAudioTxnRx[i].timeout = 0xFFFFFF;
        gMcaspAudioTxnRx[i].args = (void *)&gMcaspReceiveTxnArgs[i];
        MCASP_submitRx(mcaspHandle, &gMcaspAudioTxnRx[i]);

        /* Submit AASRC Recieve Txn */
        gAasrcAudioTxnRx[i].buf = (void*) &gAudioBufferRx[i][0];
        gAasrcAudioTxnRx[i].sampleCount = APP_AUDIO_RECEIVE_SAMPLE_BUFF_SIZE;
        gAasrcAudioTxnRx[i].args = (void *)&gAasrcReceiveTxnArgs[i];;
        AASRC_queueTransactionRx( aasrcChHandle, &gAasrcAudioTxnRx[i]);

        gMcaspReceiveTxnArgs[i].aasrcChHandle = aasrcChHandle;
        gMcaspReceiveTxnArgs[i].aasrcTxn = &gAasrcAudioTxnRx[i];

        gAasrcReceiveTxnArgs[i].mcaspHandle = mcaspHandle;
        gAasrcReceiveTxnArgs[i].mcaspTxn = &gMcaspAudioTxnRx[i];
    }
}

/*
 * DATA FLOW:
 * AUDIO IN -> MCASP Rx -> AASRC Rx -> AASRC Tx -> MCASP Tx -> AUDIO OUT
 */

/* User defined Callbacks for MCASP & AASRC rx/tx */

/* MCASP received data from audio in */
void MCASP_rxCb(MCASP_Handle handle,
                        MCASP_Transaction *transaction)
{
    AASRC_ChHandle *chHandle = ((App_McaspTxnArgs *)(transaction->args))->aasrcChHandle;
    AASRC_Transaction *aasrcAudioTxn = ((App_McaspTxnArgs *)(transaction->args))->aasrcTxn;

    /* Submit received data to AASRC for starting converesion */
    AASRC_queueTransactionRx(chHandle, aasrcAudioTxn);
}

/* Input transaction to AASRC completed */
void AASRC_rxCb (AASRC_ChHandle chHandle,
        AASRC_Transaction *transaction)
{
    MCASP_Handle *drvHandle = ((App_AasrcTxnArgs *)(transaction->args))->mcaspHandle;
    MCASP_Transaction *mcaspAudioTxn = ((App_AasrcTxnArgs *)(transaction->args))->mcaspTxn;

    /* Submit same back to MCASP */
    MCASP_submitRx(drvHandle, mcaspAudioTxn);
}

/* ASRC Conversion to new sample frequency completed */
void AASRC_txCb (AASRC_ChHandle chHandle,
    AASRC_Transaction *transaction)
{
    MCASP_Handle *drvHandle = ((App_AasrcTxnArgs *)(transaction->args))->mcaspHandle;
    MCASP_Transaction *mcaspAudioTxn = ((App_AasrcTxnArgs *)(transaction->args))->mcaspTxn;

    /* Submit converted data to MCASP  Transmissin */
    MCASP_submitTx(drvHandle, mcaspAudioTxn);
}

void MCASP_txCb(MCASP_Handle handle,
    MCASP_Transaction *transaction)
{
    AASRC_ChHandle *chHandle = ((App_McaspTxnArgs *)(transaction->args))->aasrcChHandle;
    AASRC_Transaction *aasrcAudioTxn = ((App_McaspTxnArgs *)(transaction->args))->aasrcTxn;

    /* MCASP transmission to audio out completed and ready to receive again */
    AASRC_queueTransactionTx(chHandle, aasrcAudioTxn);

}

void AASRC_errorChHandler(AASRC_ChHandle chHandle,
                        AASRC_Transaction *transactionRx,
                        AASRC_Transaction *transactionTx)
{
    AASRC_chClose(chHandle);
}
