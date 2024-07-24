/*
 *  Copyright (c) Texas Instruments Incorporated 2022-23
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

/*!
 * \file  remote_main.c
 *
 * \brief This file contains the implementation of the client example entry
 *        point
 */

/* ========================================================================== */
/*                              Include Files                                 */
/* ========================================================================== */

#include <stdio.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/ClockP.h>
#include "kernel/dpl/TimerP.h"
#include "ti_dpl_config.h"
#include "../../ShdMemCircularBufferP_nortos.h"
#include "avb_ipc.h"

SemaphoreP_Object gRemoteTimerSem;

uint8_t g_data[1000U];
uint32_t gRemoteClientId = 4u;
uint32_t g_WriteCount = 0U;

void ipc_notify_msg_handler_remote_core(uint16_t remoteCoreId, uint16_t localClientId, uint32_t msgValue, void *args)
{

}
void RemoteApp_mainTask(void *args)
{
    ShdMemCircularBufferP_Rsv shmQObjMem;
    ShdMemCircularBufferP_Handle hShmListenerQ;
    int32_t status;
    ShdMemCircularBufferStatus shmStatus = SHDMEM_CIRCULAR_BUFFER_STATUS_OK;
    /*uint32_t count = 0U;*/
    uint32_t shmElemSize = 1536U;
    uint32_t shmElemCount = 32U;
    void *pShdMemBuffStartAdd = (void *)0xA3000000;
    uint32_t dataLenArr[1U];
    void *pDataArr[1U];
    uint32_t i;

    /* Debug code: dummy data */
    for (i = 0U; i < 1000U; i++)
    {
        g_data[i] = (uint8_t) (i % 255);
    }
    status = IpcNotify_registerClient(gRemoteClientId, ipc_notify_msg_handler_remote_core, NULL);
    DebugP_assert(status==SystemP_SUCCESS);
    hShmListenerQ = ShdMemCircularBufferP_create(&shmQObjMem,
            (const void*) pShdMemBuffStartAdd, shmElemCount, shmElemSize);
    IpcNotify_syncAll(SystemP_WAIT_FOREVER);
    IpcNotify_sendMsg(CSL_CORE_ID_MCU_R5FSS0_0, 4U, TI_AVB_START_STREAM_CMD,
            1U);

    // pend on isBufferValid or isBufferInit
    status = SemaphoreP_constructBinary(&gRemoteTimerSem, 0);
    DebugP_assert(SystemP_SUCCESS == status);
    TimerP_start(gTimerBaseAddr[CONFIG_TIMER1]);

    while(true)
    {
        // pend on timerSem
        SemaphoreP_pend(&gRemoteTimerSem, SystemP_WAIT_FOREVER);
        dataLenArr[0] = 1000U;
        pDataArr[0] = (void *)g_data;
        shmStatus = ShdMemCircularBufferP_writeElem(hShmListenerQ, 1U, pDataArr, dataLenArr);
        // read the whole buffer to local buffer
        if(shmStatus == SHDMEM_CIRCULAR_BUFFER_STATUS_OK)
        {
            g_WriteCount++;
        }
    }
}

void remoteTimerIsr(void)
{
    SemaphoreP_post(&gRemoteTimerSem);
}
