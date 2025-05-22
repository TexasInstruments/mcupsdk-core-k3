
#include <stdio.h>
//! [include]
#include <drivers/aasrc.h>
//! [include]
#include <drivers/hw_include/csl_types.h>
#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/SemaphoreP.h>

#define MONO_INPUT_TRANSACTION_SAMPLE_COUNT            (1024U)

#define APP_AUDIO_TRANSACTION_COUNT (64U)

#define CONFIG_AASRC0           (0U)
#define CONFIG_AASRC0_CH0       (0U)

AASRC_Handle        gAasrcHandle;
AASRC_ChHandle      gAasrcChHandle;

SemaphoreP_Object gCountSemAsrcConv;

void aasrc_rxcb (AASRC_ChHandle chHandle,
                AASRC_Transaction *transaction);

void aasrc_txcb (AASRC_ChHandle chHandle,
                AASRC_Transaction *transaction);

void aasrc_ch_error_handler(AASRC_ChHandle chHandle,
                            AASRC_Transaction *transactionRx,
                            AASRC_Transaction *transactionTx);

void open(void)
{
//! [open]
    int32_t     status;
    AASRC_OpenParams     aasrcParams
    AASRC_OpenParams_init(&aasrcParams); /* Initialize aasrc parameters */

    gAasrcHandle = AASRC_open(CONFIG_AASRC0, &aasrcParams);
    DebugP_assert(gAasrcHandle != NULL);
    gAasrcChHandle = AASRC_chOpen(CONFIG_AASRC0_CH0, gAasrcHandle);
    DebugP_assert(gAasrcChHandle != NULL);
    status = AASRC_chConfig(gAasrcChHandle);
    DebugP_assert(status == SystemP_SUCCESS);
//! [open]
}

void close(void)
{
//! [close]
    AASRC_close(gAasrcHandle);
//! [close]
}

void aasrc_conversion (void)
{
//! [start_aasrc_conversion]
    int32_t     status;
    uint32_t i;

    /* AASRC transaction objects for transmit and Receive */
    AASRC_Transaction aasrcAudioTxnTx[APP_AUDIO_TRANSACTION_COUNT] = {0};
    AASRC_Transaction aasrcAudioTxnRx[APP_AUDIO_TRANSACTION_COUNT] = {0};

    /* Buffers for audio transmit and Receive */
    uint32_t audioBufferTx[APP_AUDIO_TRANSACTION_COUNT][MONO_INPUT_TRANSACTION_SAMPLE_COUNT] __attribute__((aligned(256)));
    uint32_t audioBufferRx[APP_AUDIO_TRANSACTION_COUNT][MONO_INPUT_TRANSACTION_SAMPLE_COUNT] __attribute__((aligned(256)));

    for (i = 0U; i < APP_AUDIO_TRANSACTION_COUNT; i++)
    {
        /* Submit AASRC Trasmit Txn */
        aasrcAudioTxnTx[i].buf = (void*) &audioBufferTx[i][0];
        aasrcAudioTxnTx[i].sampleCount = MONO_INPUT_TRANSACTION_SAMPLE_COUNT;
        AASRC_queueTransactionTx( aasrcChHandle, &aasrcAudioTxnTx[i]);

        /* Submit AASRC Recieve Txn */
        aasrcAudioTxnRx[i].buf = (void*) &audioBufferRx[i][0];
        aasrcAudioTxnRx[i].sampleCount = MONO_INPUT_TRANSACTION_SAMPLE_COUNT;
        AASRC_queueTransactionRx( aasrcChHandle, &gAasrcAudioTxnRx[i]);
    }
    status = AASRC_chEnable(chHandle);
    DebugP_assert(status == SystemP_SUCCESS);
//! [start_aasrc_conversion]

//! [stop_aasrc_conversion]
    AASRC_chDisable(chHandle);
//! [stop_aasrc_conversion]
}

//! [aasrc_callback_functions]
void aasrc_loopback_txcb (AASRC_ChHandle handle,
                         AASRC_Transaction *transaction)
{
    /* Post semaphore to track transaction count */
    SemaphoreP_post(&gCountSemAsrcConv);
}

void aasrc_loopback_rxcb (AASRC_ChHandle handle,
                        AASRC_Transaction *transaction)
{

}

//! [aasrc_callback_functions]