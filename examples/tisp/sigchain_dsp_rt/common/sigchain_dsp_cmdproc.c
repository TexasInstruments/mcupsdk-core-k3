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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "sigchain_cmd_proc.h"
#include "sigchain_dsp_mcasp.h"
#include "sigchain_platform.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* semaphore used for packet processing */
SemaphoreP_Object semCmdPkt;

/* idle task */
StackType_t gIdleTaskStack[DSP_IPC_TASK_SIZE];
StaticTask_t gIdleTaskObj;
TaskHandle_t gIdleTask;

ipcMsgBuf_t msg;

extern int32_t chPlotData[BUFSIZE_PER_CHANNEL];
extern uint32_t gNewChnlData;
extern uint32_t gPlotChnl;
extern uint32_t gPlotCaptureMode;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

uint32_t SigchainDSP_Cmdproc_getSysInfo(uint8_t *buf)
{
    SignalChainCmd_SysInfo *si = (SignalChainCmd_SysInfo *) buf;
    strcpy(si->socName, SOC_NAME);
    strcpy(si->coreName, CORE_NAME);
    si->samplingRate = SAMPL_RATE;
    si->nodeCount = get_graph_length(gSpGraph);
    return sizeof(SignalChainCmd_SysInfo);
}

uint32_t SigchainDSP_Cmdproc_getNodeInfo(uint8_t *buf, uint32_t nodeIndex)
{
    int32_t error = -1;
    uint32_t retVal = 0;
    NodeInfo *ni = (NodeInfo *) buf;
    error =
        getNodeInfo(gSpGraph, nodeIndex, &(ni->nodeId), ni->name, ni->param);
    if (error == 0)
    {
        retVal = sizeof(NodeInfo);
    }

    return retVal;
}

uint32_t SigchainDSP_Cmdproc_getRTInfo(uint8_t *buf)
{
    gRtInfo.dspLoad = TaskP_loadGetTotalCpuLoad();
    memcpy(buf, &gRtInfo, sizeof(gRtInfo));
    TaskP_loadResetAll();
    return sizeof(RtInfo);
}

void SigchainDSP_Cmdproc_decodeCmd()
{
    uint16_t *cmd;
    uint32_t retVal = 0;
    uint8_t *dataBuf;
    uint32_t bExitApp = 0;
    uint32_t nodeIndex = 0;

    gCmdSize = 0;

    cmd = (uint16_t *) gCmdAddr;
    dataBuf = (uint8_t *) (cmd + 1);
    DebugP_log("DSP: Cmd = 0x%04X\r\n", *cmd);

    switch (*cmd)
    {
    case SIGCHAIN_CMD_INFO:
        *cmd = (2 << 12) + (*cmd & 0xFFF);
        gCmdSize = 2;
        retVal = SigchainDSP_Cmdproc_getSysInfo(dataBuf);
        gCmdSize += retVal;
        break;

    case SIGCHAIN_CMD_NODE_INFO:
        *cmd = (2 << 12) + (*cmd & 0xFFF);
        gCmdSize = 2;
        nodeIndex = *(uint16_t *) dataBuf;
        retVal = SigchainDSP_Cmdproc_getNodeInfo(dataBuf, nodeIndex);
        gCmdSize += retVal;
        break;

    case SIGCHAIN_CMD_MUTE:
        *cmd = (2 << 12) + (*cmd & 0xFFF);
        gCmdSize = 2;
        break;

    case SIGCHAIN_CMD_RT_INFO:
        *cmd = (2 << 12) + (*cmd & 0xFFF);
        gCmdSize = 2;
        retVal = SigchainDSP_Cmdproc_getRTInfo(dataBuf);
        gCmdSize += retVal;
        break;

    case SIGCHAIN_CMD_CHNL_MAP:
        *cmd = (2 << 12) + (*cmd & 0xFFF);
        gCmdSize = 2;
        memcpy(chmap, dataBuf, sizeof(chmap));
        {
            int sz = sizeof(chmap);
            int i = 0;
            for (i = 0; i < sz; i++)
            {
                DebugP_log("%d ", chmap[i]);
            }
            DebugP_log("\r\n");
        }
        break;

    case SIGCHAIN_CMD_PLOT_CAPTURE:
        gPlotCaptureMode = 1;
        *cmd = (2 << 12) + (*cmd & 0xFFF);
        gCmdSize = 2;
        gPlotCaptureMode = dataBuf[0];
        gPlotChnl = dataBuf[1];
        if (gPlotCaptureMode == 1)
        {
            DebugP_log("Starting channel capture, ch: %d\r\n", gPlotChnl);
        }
        else
        {
            DebugP_log("Stopping channel capture\r\n");
        }
        break;

    case SIGCHAIN_CMD_CHNL_DATA:
        *cmd = (2 << 12) + (*cmd & 0xFFF);
        gCmdSize = 2;
        if (gNewChnlData > 0)
        {
            memcpy(dataBuf, chPlotData, gNewChnlData);
            gCmdSize += gNewChnlData;
            gNewChnlData = 0;
        }
        break;

    case SIGCHAIN_CMD_EXIT_APP:
        *cmd = (2 << 12) + (*cmd & 0xFFF);
        gCmdSize = 2;
        bExitApp = 1;
        break;

    default:
        break;
    }

    if (gCmdSize > 0)
    {
        msg.dataBuffer = gCmdAddr;
        msg.dataSize = gCmdSize;
        CacheP_wb((void *) gCmdAddr, gCmdSize, CacheP_TYPE_ALLD);
        SigchainDSP_IPC_send((uint8_t *) &msg, sizeof(ipcMsgBuf_t));
    }

    if (bExitApp == 1)
    {
        SemaphoreP_post(&gSemExit);
    }
}

void SigchainDSP_Cmdproc_idleTask(void *arg)
{
    int32_t done = 0;

    /* create semaphore for command packet */
    SemaphoreP_constructBinary(&semCmdPkt, 0);

    while (!done)
    {
        /* Wait for command packet from host */
        SemaphoreP_pend(&semCmdPkt, SystemP_WAIT_FOREVER);

        SigchainDSP_Cmdproc_decodeCmd();

    } /* While done loop*/

    vTaskDelete(NULL);
}

void SigchainDSP_Cmdproc_createIdleTask()
{
    gIdleTask = xTaskCreateStatic(
        SigchainDSP_Cmdproc_idleTask, "SigchainDSP_Cmdproc_idleTask",
        SIGCHAIN_IDLE_TASK_STACKSIZE, NULL, SIGCHAIN_IDLE_TASK_PRI,
        gIdleTaskStack, &gIdleTaskObj);
    configASSERT(gIdleTask != NULL);
}
