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
 #include "aasrc_config.h"

 /* ========================================================================== */
 /*                           Macros & Typedefs                                */
 /* ========================================================================== */


 /* Audio buffer settings */
 #define APP_AUDIO_RECEIVE_TRANSACTION_COUNT    (64U)
 #define APP_AUDIO_TRANSMIT_TRANSACTION_COUNT   (64U)

 #define APP_AUDIO_RECEIVE_SAMPLE_BUFF_SIZE     (512U)
 #define APP_AUDIO_TRANSMIT_SAMPLE_BUFF_SIZE    (1024U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
typedef struct
{
    AASRC_ChHandle    aasrcChHandle ;
    AASRC_Transaction *aasrcTxn;
}mcaspTxnArgs;

typedef struct
{
    MCASP_Handle          mcaspHandle;
    MCASP_Transaction    *mcaspTxn;
}asrcTxnArgs;

 /* ========================================================================== */
 /*                           Global Variables                                 */
 /* ========================================================================== */

 /*
  * MCASP
  * MCASP transaction objects for transmit and Receive
  */
 MCASP_Transaction   gMcaspAudioTxnTx[APP_AUDIO_TRANSMIT_TRANSACTION_COUNT] = {0};
 MCASP_Transaction   gMcaspAudioTxnRx[APP_AUDIO_RECEIVE_TRANSACTION_COUNT] = {0};

 mcaspTxnArgs gMcaspTransmitTxnArgs[APP_AUDIO_TRANSMIT_TRANSACTION_COUNT] =   {0};
 mcaspTxnArgs gMcaspReceiveTxnArgs[APP_AUDIO_RECEIVE_TRANSACTION_COUNT] =   {0};

 /*
  * AASRC
  * AASRC transaction objects for transmit and Receive
  */
 AASRC_Transaction gAasrcAudioTxnTx[APP_AUDIO_TRANSMIT_TRANSACTION_COUNT] = {0};
 AASRC_Transaction gAasrcAudioTxnRx[APP_AUDIO_RECEIVE_TRANSACTION_COUNT] = {0};

 asrcTxnArgs  gAasrcTransmitTxnArgs[APP_AUDIO_TRANSMIT_TRANSACTION_COUNT] =   {0};
 asrcTxnArgs  gAasrcReceiveTxnArgs[APP_AUDIO_RECEIVE_TRANSACTION_COUNT] =   {0};

 /* Buffers for audio transmit and Receive */
 uint32_t gAudioBufferTx[APP_AUDIO_TRANSMIT_TRANSACTION_COUNT][APP_AUDIO_TRANSMIT_SAMPLE_BUFF_SIZE] __attribute__((aligned(256)));
 uint32_t gAudioBufferRx[APP_AUDIO_RECEIVE_TRANSACTION_COUNT][APP_AUDIO_RECEIVE_SAMPLE_BUFF_SIZE] __attribute__((aligned(256)));

 /* ========================================================================== */
 /*                              Function Declaration                          */
 /* ========================================================================== */

 int32_t Board_codecConfig(void);
 void transactionInit(MCASP_Handle mcaspHandle, AASRC_Handle aasrcHandle);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

 void aasrc_stereo_playback_main(void *args)
 {
     int32_t     status = SystemP_SUCCESS;
     MCASP_Handle    mcaspHandle =NULL;
     AASRC_ChHandle  chHandle = NULL;
     char            valueChar;

     /* Configure codec */
     status = Board_codecConfig();
     DebugP_assert(status == SystemP_SUCCESS);

     DebugP_log("[AASRC] Audio playback example started.\r\n");

     mcaspHandle = MCASP_getHandle(CONFIG_MCASP0);
     chHandle = AASRC_getChHandle(CONFIG_AASRC0, 0);

     if( status ==  SystemP_SUCCESS)
     {
        /* Init MCASP & AASRC transactions */
        transactionInit(mcaspHandle, chHandle);

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

 void transactionInit(MCASP_Handle mcaspHandle, AASRC_ChHandle aasrcChHandle)
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
    * FLOW
    *
    * AUDIO IN -> MCASP Rx -> AASRC Rx -> AASRC Tx -> MCASP Tx -> AUDIO OUT
    */

 /* User defined Callbacks for MCASP & AASRC rx/tx */

 /* MCASP received data from audio in */
 void mcasp_rxcb(MCASP_Handle handle,
                           MCASP_Transaction *transaction)
 {
     AASRC_ChHandle *chHandle = ((mcaspTxnArgs *)(transaction->args))->aasrcChHandle;
     AASRC_Transaction *aasrcAudioTxn = ((mcaspTxnArgs *)(transaction->args))->aasrcTxn;

     /* Submit received data to AASRC for starting converesion */
     AASRC_queueTransactionRx(chHandle, aasrcAudioTxn);

 }

 /* Input transaction to AASRC completed */
 void aasrc_rxcb (AASRC_ChHandle chHandle,
         AASRC_Transaction *transaction)
 {
     MCASP_Handle *drvHandle = ((asrcTxnArgs *)(transaction->args))->mcaspHandle;
     MCASP_Transaction *mcaspAudioTxn = ((asrcTxnArgs *)(transaction->args))->mcaspTxn;

     /* Submit same back to MCASP */
     MCASP_submitRx(drvHandle, mcaspAudioTxn);

 }

 /* ASRC Conversion to new sample frequency completed */
 void aasrc_txcb (AASRC_ChHandle chHandle,
     AASRC_Transaction *transaction)
 {
     MCASP_Handle *drvHandle = ((asrcTxnArgs *)(transaction->args))->mcaspHandle;
     MCASP_Transaction *mcaspAudioTxn = ((asrcTxnArgs *)(transaction->args))->mcaspTxn;

     /* Submit converted data to MCASP  Transmissin */
     MCASP_submitTx(drvHandle, mcaspAudioTxn);
 }

 void mcasp_txcb(MCASP_Handle handle,
     MCASP_Transaction *transaction)
 {
     AASRC_ChHandle *chHandle = ((mcaspTxnArgs *)(transaction->args))->aasrcChHandle;
     AASRC_Transaction *aasrcAudioTxn = ((mcaspTxnArgs *)(transaction->args))->aasrcTxn;

     /* MCASP transmission to audio out completed and ready to receive again */
     AASRC_queueTransactionTx(chHandle, aasrcAudioTxn);

 }

 void aasrc_ch_error_handler(AASRC_ChHandle chHandle,
                             AASRC_Transaction *transactionRx,
                             AASRC_Transaction *transactionTx)
 {

 }

