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
 * \file  tsnapp_main.c
 *
 * \brief This file contains the implementation of the Enet TSN example entry
 *        point
 */

/* ========================================================================== */
/*                              Include Files                                 */
/* ========================================================================== */

#include "nrt_flow/dataflow.h"
#include "debug_log.h"
#include "tsninit.h"
#include "enetapp_cpsw.h"
#include "avb_talker.h"
#include "ShdMemCircularBufferP_nortos.h"

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */

extern EnetApp_Cfg gEnetAppCfg;

/* client ID that is used to send and receive messages */
uint32_t gClientId = 4u;

void ipc_notify_msg_handler_main_core(uint16_t remoteCoreId, uint16_t localClientId, uint32_t msgValue, void *args)
{
    SemaphoreP_post(&gEnetAppCfg.startTalkerSemObj);
}

void EnetApp_mainTask(void *args)
{
    EnetPer_AttachCoreOutArgs attachCoreOutArgs;
    EnetApp_HandleInfo handleInfo;
    int32_t status;
    uint32_t shmElemSize = 1536U;
    uint32_t shmElemCount = 32U;
    void *pShdMemBuffStartAdd = (void *)0xA3000000;

    DebugP_log("==========================\r\n");
    DebugP_log("       TSN CPSW App       \r\n");
    DebugP_log("==========================\r\n");

    status = SemaphoreP_constructBinary(&gEnetAppCfg.startTalkerSemObj, 0);
    DebugP_assert(SystemP_SUCCESS == status);
    status = IpcNotify_registerClient(gClientId, ipc_notify_msg_handler_main_core, NULL);
    DebugP_assert(status==SystemP_SUCCESS);
    EnetApp_initAppCfg(&attachCoreOutArgs, &handleInfo);
    EnetAppUtils_print("%s: Create RX task for regular traffic \r\n", ENETAPP_DEFAULT_CFG_NAME);
    EnetApp_createRxTask();

    if (EnetApp_initTsn())
    {
        DebugP_log("EnetApp_initTsn failed\r\n");
    }
    else
    {
        gEnetAppCfg.hShmListenerQ = ShdMemCircularBufferP_create( &gEnetAppCfg.shmQObjMem,
                                                                  (const void*) pShdMemBuffStartAdd,
                                                                  shmElemCount,
                                                                  shmElemSize);
        EnetAppUtils_assert(gEnetAppCfg.hShmListenerQ != NULL);
        ShdMemCircularBufferP_initQ(gEnetAppCfg.hShmListenerQ,
                                    0U,
                                    shmElemCount);
        avbTalker_createTask();
        IpcNotify_syncAll(SystemP_WAIT_FOREVER);

        while (BTRUE)
        {
            // Print CPU load
            ClockP_usleep(1000);
            EnetApp_printCpuLoad();
            TaskP_yield();
        }
        EnetApp_stopTsn();
        EnetApp_deInitTsn();
    }
}
