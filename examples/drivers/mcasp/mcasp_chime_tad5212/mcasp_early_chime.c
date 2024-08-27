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
#include <drivers/i2c.h>
#include <drivers/mcasp.h>
#include <board/ioexp/ioexp_tca6424.h>
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "audio_sample.h"

/* ========================================================================== */
/*                        Extern Function Declaration                         */
/* ========================================================================== */
extern int32_t Board_codecConfig(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
MCASP_Transaction txTxn;

SemaphoreP_Object gSemAudioChime;

void mcasp_chime(void *args)
{
    int32_t status = SystemP_SUCCESS;
    MCASP_Handle mcaspHandle;

    SemaphoreP_constructBinary(&gSemAudioChime, 0);

    status = Board_codecConfig();
    DebugP_assert(status == SystemP_SUCCESS);

    mcaspHandle = MCASP_getHandle(CONFIG_MCASP0);

    txTxn.buf = (void *)audio_sample;
    txTxn.count = audio_sample_size;
    txTxn.timeout = 0xFFFFFF;
    MCASP_submitTx(mcaspHandle, &txTxn);

    DebugP_log("Starting Chime \r\n");

    status = MCASP_startTransferTx(mcaspHandle);
    DebugP_assert(status == SystemP_SUCCESS);

    SemaphoreP_pend(&gSemAudioChime, SystemP_WAIT_FOREVER);

    DebugP_log("Chime completed\r\n");

    MCASP_Transaction *transaction;
    do {
        transaction = MCASP_withdrawRx(mcaspHandle);
    }while (transaction != NULL);

    MCASP_stopTransferTx(mcaspHandle);
}

void mcasp_txcb(MCASP_Handle handle,
                          MCASP_Transaction *transaction)
{
    SemaphoreP_post(&gSemAudioChime);
}
