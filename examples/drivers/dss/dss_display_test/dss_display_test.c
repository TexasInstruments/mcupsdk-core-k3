/*
 *  Copyright (C) 2023-24 Texas Instruments Incorporated
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

/**
 *  \file dss_display_test.c
 *
 *  \brief DSS sample application that displays two frame buffers.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <drivers/dss.h>
#include <drivers/fvid2.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SemaphoreP.h>
#include "ti_drivers_open_close.h"
#include "ti_drivers_config.h"
#include "ti_board_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Number of frames (5sec 300 frames) */
#define DISP_NUM_FRAMES_COUNT              ((uint32_t)300U)

/* Max frame size based on resolution */
#define DISP_FRAME_SIZE_MAX                (3840U*1080U)

/* Max pixel width */
#define DISP_FRAME_PIXEL_WIDTH_MAX          (4U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void DispApp_init(Dss_Object *appObj);
static void DispApp_deInit(Dss_Object *appObj);
static void DispApp_create(Dss_Object *appObj);
static void DispApp_delete(Dss_Object *appObj);
static int32_t DispApp_configDctrl(Dss_Object *appObj);
static int32_t DispApp_runTest(Dss_Object *appObj);
static void DispApp_initPipelineParams(Dss_Object *appObj);
static int32_t DispApp_allocAndQueueFrames(const Dss_Object *appObj,
                                           Dss_InstObject *instObj);
static int32_t DispApp_pipeCbFxn(Fvid2_Handle handle, void *appData);
static void DispApp_initDssParams(Dss_Object *appObj);

extern void Disp_prepareFrameBuffer(uint32_t instCount,
                                       Dss_ConfigPipelineParams *pipelineParams,
                                       void *frameBuffer[CONFIG_DSS_NUM_FRAMES_PER_PIPELINE]);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

uint32_t gStopProfileTime, gStartProfileTime;

/*
 * Global frame buffers. Maximum frames per handle is considered 2 and first frame
 * is used for first pipeline instance and other is used for second pipeline instance.
 */
uint8_t gFirstPipelineFrameBuf[CONFIG_DSS_NUM_FRAMES_PER_PIPELINE][DISP_FRAME_SIZE_MAX * DISP_FRAME_PIXEL_WIDTH_MAX]__attribute__ ((section (".dssFrameBuffer"), aligned (4096)));
uint8_t gSecondPipelineFrameBuf[CONFIG_DSS_NUM_FRAMES_PER_PIPELINE][DISP_FRAME_SIZE_MAX * DISP_FRAME_PIXEL_WIDTH_MAX]__attribute__ ((section (".dssFrameBuffer"), aligned (4096))) ;

/* Pointer to frame buffers per pipleline */
void *firstPipeFrameBufferPointer[CONFIG_DSS_NUM_FRAMES_PER_PIPELINE];
void *secondPipeFrameBufferPointer[CONFIG_DSS_NUM_FRAMES_PER_PIPELINE];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void DispApp_initFrames()
{
    uint32_t instCnt = 0;

    for(instCnt = 0; instCnt < CONFIG_DSS_NUM_FRAMES_PER_PIPELINE; instCnt++)
    {
        firstPipeFrameBufferPointer[instCnt] = &gFirstPipelineFrameBuf[instCnt];
        secondPipeFrameBufferPointer[instCnt] = &gSecondPipelineFrameBuf[instCnt];
    }

    for(instCnt = 0U; instCnt<gDssConfigPipelineParams.numTestPipes; instCnt++)
    {
        if(instCnt != 0)
        {
            Disp_prepareFrameBuffer(instCnt,&gDssConfigPipelineParams,
                                       secondPipeFrameBufferPointer);
        }
        else
        {
            Disp_prepareFrameBuffer(instCnt,&gDssConfigPipelineParams,
                                       firstPipeFrameBufferPointer);
        }
    }

}

/*
 * DSS display test
 */
void dss_display_test_main(void *args)
{
    int32_t retVal = FVID2_SOK;

    /* Initialise frames */
    DispApp_initFrames();

    DispApp_init(&gDssObjects[CONFIG_DSS0]);

    DebugP_log("DSS display application started...\r\n");

    retVal = DispApp_runTest(&gDssObjects[CONFIG_DSS0]);

    DebugP_log("Number of frames = %d, elapsed msec = %d, fps = %0.2f\r\n",
            DISP_NUM_FRAMES_COUNT,
            gStopProfileTime - gStartProfileTime,
            (float)((float)DISP_NUM_FRAMES_COUNT / ((gStopProfileTime - gStartProfileTime)/1000.0)));

    DispApp_deInit(&gDssObjects[CONFIG_DSS0]);

    if(FVID2_SOK == retVal)
    {
        DebugP_log("DSS display test Passed!!\r\n");
    }
    else
    {
        DebugP_log("DSS display test Failed!!\r\n");
    }

    return;
}

static void DispApp_init(Dss_Object *appObj)
{
    int32_t         retVal = FVID2_SOK;
    Fvid2_InitPrms  initPrms;

    Fvid2InitPrms_init(&initPrms);
    retVal = Fvid2_init(&initPrms);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("Fvid2 Init Failed!!!\r\n");
    }

    Dss_initParamsInit(&appObj->initParams);

    Dss_init(&appObj->initParams);

    if(FVID2_SOK == retVal)
    {
        /* Create DCTRL handle, used for common driver configuration */
        appObj->dctrlHandle = Fvid2_create(
            DSS_DCTRL_DRV_ID,
            DSS_DCTRL_INST_0,
            NULL,
            NULL,
            NULL);
        if(NULL == appObj->dctrlHandle)
        {
            DebugP_log("DCTRL Create Failed!!!\r\n");
        }
    }

    if(appObj->oldiParams != NULL)
    {
        Dss_setOLDITxPowerDown(appObj->oldiParams->oldiCfg.oldiMapType, TRUE);
    }

    if(FVID2_SOK == retVal)
    {
        DebugP_log("DispApp_init() - DONE !!!\r\n");
    }

    return;
}

static void DispApp_deInit(Dss_Object *appObj)
{
    int32_t  retVal = FVID2_SOK;

    /* Delete DCTRL handle */
    retVal = Fvid2_delete(appObj->dctrlHandle, NULL);
    retVal += Dss_deInit();
    retVal += Fvid2_deInit(NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL handle delete failed!!!\r\n");
    }
    else
    {
        DebugP_log("DispApp_deInit() - DONE !!!\r\n");
    }

    return;
}

static int32_t DispApp_runTest(Dss_Object *appObj)
{
    int32_t retVal = FVID2_SOK;
    uint32_t instCnt = 0U;
    volatile uint32_t loopCount = 0U;
    Dss_InstObject *instObj;
    Fvid2_FrameList  frmList;

    /* Create driver */
    DispApp_create(appObj);

    DebugP_log("Starting display ... !!!\r\n");
    DebugP_log("Display in progress ... DO NOT HALT !!!\r\n");

    /* Start driver */
    for(instCnt=0U; instCnt<gDssConfigPipelineParams.numTestPipes; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];

        retVal = Fvid2_start(instObj->drvHandle, NULL);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("Display Start Failed!!!\r\n");
            break;
        }
    }

    gStartProfileTime = (ClockP_getTimeUsec() / 1000U);

    while(loopCount++ < DISP_NUM_FRAMES_COUNT)
    {
        for(instCnt=0U; instCnt<gDssConfigPipelineParams.numTestPipes; instCnt++)
        {
            instObj = &appObj->instObj[instCnt];
            (void) SemaphoreP_pend(&instObj->syncSem, SystemP_WAIT_FOREVER);
            retVal = Fvid2_dequeue(instObj->drvHandle,
                                   &frmList,
                                   0U,
                                   FVID2_TIMEOUT_NONE);

            if(FVID2_SOK == retVal)
            {
                retVal = Fvid2_queue(instObj->drvHandle, &frmList, 0U);
                if(FVID2_SOK != retVal)
                {
                    DebugP_log("Display Queue Failed!!!\r\n");
                    break;
                }
            }
            else if (FVID2_EAGAIN == retVal)
            {
                /* Do nothing as this is first callback */
            }
            else
            {
                /* Error */
                DebugP_log("Display Dequeue Failed!!!\r\n");
                break;
            }
        }
    }

    for(instCnt=0U; instCnt<gDssConfigPipelineParams.numTestPipes; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];
        retVal  = Fvid2_stop(instObj->drvHandle, NULL);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("Display Stop Failed!!!\r\n");
            break;
        }
    }

    gStopProfileTime = (ClockP_getTimeUsec() / 1000U);

    if(FVID2_SOK == retVal)
    {
        /* Delete driver */
        DispApp_delete(appObj);
    }

    return retVal;
}

static void DispApp_initDssParams(Dss_Object *appObj)
{
    Dss_DctrlVpParams *vpParams;
    Dss_DctrlAdvVpParams *advVpParams;
    Dss_DctrlOverlayParams *overlayParams;
    Dss_DctrlOverlayLayerParams *layerParams;
    Dss_DctrlGlobalDssParams *globalDssParams;

    vpParams = &appObj->vpParams;
    overlayParams = &appObj->overlayParams;
    layerParams = &appObj->layerParams;
    advVpParams = &appObj->advVpParams;
    globalDssParams= &appObj->globalDssParams;

    Dss_dctrlVpParamsInit(vpParams);
    Dss_dctrlAdvVpParamsInit(advVpParams);
    Dss_dctrlOverlayParamsInit(overlayParams);
    Dss_dctrlOverlayLayerParamsInit(layerParams);
    Dss_dctrlGlobalDssParamsInit(globalDssParams);


    /* Configure VP params */
    vpParams->vpId = gDssVpParams.vpId;
    vpParams->lcdOpTimingCfg.mInfo.standard = gDssVpParams.lcdOpTimingCfg.mInfo.standard;
    vpParams->lcdOpTimingCfg.mInfo.width = gDssVpParams.lcdOpTimingCfg.mInfo.width;
    vpParams->lcdOpTimingCfg.mInfo.height = gDssVpParams.lcdOpTimingCfg.mInfo.height;
    vpParams->lcdOpTimingCfg.mInfo.hFrontPorch = gDssVpParams.lcdOpTimingCfg.mInfo.hFrontPorch;
    vpParams->lcdOpTimingCfg.mInfo.hBackPorch = gDssVpParams.lcdOpTimingCfg.mInfo.hBackPorch;
    vpParams->lcdOpTimingCfg.mInfo.hSyncLen = gDssVpParams.lcdOpTimingCfg.mInfo.hSyncLen;
    vpParams->lcdOpTimingCfg.mInfo.vFrontPorch = gDssVpParams.lcdOpTimingCfg.mInfo.vFrontPorch;
    vpParams->lcdOpTimingCfg.mInfo.vBackPorch = gDssVpParams.lcdOpTimingCfg.mInfo.vBackPorch;
    vpParams->lcdOpTimingCfg.mInfo.vSyncLen = gDssVpParams.lcdOpTimingCfg.mInfo.vSyncLen;

    vpParams->lcdOpTimingCfg.dvoFormat = gDssVpParams.lcdOpTimingCfg.dvoFormat;
    vpParams->lcdOpTimingCfg.videoIfWidth = gDssVpParams.lcdOpTimingCfg.videoIfWidth;

    vpParams->lcdPolarityCfg.actVidPolarity =  gDssVpParams.lcdPolarityCfg.actVidPolarity;
    vpParams->lcdPolarityCfg.hsPolarity = gDssVpParams.lcdPolarityCfg.hsPolarity;
    vpParams->lcdPolarityCfg.vsPolarity = gDssVpParams.lcdPolarityCfg.vsPolarity;
    vpParams->lcdPolarityCfg.pixelClkPolarity = gDssVpParams.lcdPolarityCfg.pixelClkPolarity ;

    /* Configure VP Advance Params*/
    advVpParams->vpId = gDssAdvVpParams.vpId;
    advVpParams->lcdAdvSignalCfg.hVAlign = gDssAdvVpParams.lcdAdvSignalCfg.hVAlign;
    advVpParams->lcdAdvSignalCfg.hVClkControl = gDssAdvVpParams.lcdAdvSignalCfg.hVClkControl;

    /* Configure Overlay Params */
    overlayParams->overlayId =  gDssOverlayParams.overlayId;
    overlayParams->colorbarEnable =  gDssOverlayParams.colorbarEnable;
    overlayParams->overlayCfg.colorKeyEnable =  gDssOverlayParams.overlayCfg.colorKeyEnable;
    overlayParams->overlayCfg.colorKeySel =  gDssOverlayParams.overlayCfg.colorKeySel;
    overlayParams->overlayCfg.backGroundColor =  gDssOverlayParams.overlayCfg.backGroundColor;

    /* Configure Overlay Layer params */
    layerParams->overlayId = gDssOverlayLayerParams.overlayId;
    memcpy((void*)layerParams->pipeLayerNum, (void* )gDssOverlayLayerParams.pipeLayerNum, \
    sizeof(gDssOverlayLayerParams.pipeLayerNum));

}

static void DispApp_create(Dss_Object *appObj)
{
    int32_t retVal = FVID2_SOK;
    int32_t status = SystemP_SUCCESS;
    uint32_t instCnt = 0U;
    Dss_InstObject *instObj;

    /* Init VP, Overlay and Panel params */
    DispApp_initDssParams(appObj);

    /* Configure DSS pipeline params */
    DispApp_initPipelineParams(appObj);

    /* Config IOCTL for VP, Overlay and Panel */
    retVal = DispApp_configDctrl(appObj);

    if(retVal == FVID2_SOK)
    {
        for(instCnt=0U; instCnt<gDssConfigPipelineParams.numTestPipes; instCnt++)
        {
            instObj = &appObj->instObj[instCnt];

            status = SemaphoreP_constructBinary(&instObj->syncSem, 0);
            if(status != SystemP_SUCCESS)
            {
                retVal = FVID2_EFAIL;
            }

            instObj->drvHandle = Fvid2_create(
                DSS_DISP_DRV_ID,
                instObj->instId,
                &instObj->createParams,
                &instObj->createStatus,
                &instObj->cbParams);

            if((NULL == instObj->drvHandle) ||
            (instObj->createStatus.retVal != FVID2_SOK))
            {
                DebugP_log("Display Create Failed!!!\r\n");
                retVal = instObj->createStatus.retVal;
            }

            if(FVID2_SOK == retVal)
            {
                retVal = Fvid2_control(
                    instObj->drvHandle,
                    IOCTL_DSS_DISP_SET_DSS_PARAMS,
                    &instObj->dispParams,
                    NULL);
                if(retVal != FVID2_SOK)
                {
                    DebugP_log("DSS Set Params IOCTL Failed!!!\r\n");
                }
            }
            if(FVID2_SOK == retVal)
            {
                retVal = Fvid2_control(
                    instObj->drvHandle,
                    IOCTL_DSS_DISP_SET_PIPE_MFLAG_PARAMS,
                    &instObj->mflagParams,
                    NULL);
                if(retVal != FVID2_SOK)
                {
                    DebugP_log("DSS Set Mflag Params IOCTL Failed!!!\r\n");
                }
            }

            if(FVID2_SOK == retVal)
            {
                retVal = DispApp_allocAndQueueFrames(appObj, instObj);
                if(retVal != FVID2_SOK)
                {
                    DebugP_log("Display Alloc and Queue Failed!!!\r\n");
                }
            }

            if(FVID2_SOK != retVal)
            {
                break;
            }
        }
    }

    if(FVID2_SOK == retVal)
    {
        DebugP_log("Display create complete!!\r\n");
    }

    return;
}

static void DispApp_delete(Dss_Object *appObj)
{
    int32_t retVal;
    uint32_t instCnt;
    Dss_DctrlVpParams *vpParams;
    Dss_DctrlVpErrorStats *pErrorStats;
    Dss_InstObject *instObj;
    Dss_DispCurrentStatus currStatus;
    Fvid2_FrameList frmList;

    vpParams = &appObj->vpParams;
    pErrorStats = &appObj->errorStats;

    for(instCnt=0U; instCnt<gDssConfigPipelineParams.numTestPipes; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];

        /* Check for DSS underflow errors */
        retVal = Fvid2_control(
            instObj->drvHandle,
            IOCTL_DSS_DISP_GET_CURRENT_STATUS,
            &currStatus,
            NULL);
        if(FVID2_SOK != retVal)
        {
            DebugP_log("Failed to get Display Stats!!!\r\n");
        }

        /* Print Synclost errors */
        if(0U != currStatus.underflowCount)
        {
            GT_2trace(DssTrace, GT_ERR, "No of Underflows for Inst %d: %d\r\n", instCnt, currStatus.underflowCount);
        }
        else
        {
            DebugP_log("Underflow did not occur\r\n");
        }

        /* Dequeue all the request from the driver */
        while (1U)
        {
            retVal = Fvid2_dequeue(
                instObj->drvHandle,
                &frmList,
                0U,
                FVID2_TIMEOUT_NONE);
            if(FVID2_SOK != retVal)
            {
                break;
            }
        }

        retVal = Fvid2_delete(instObj->drvHandle, NULL);
        if(FVID2_SOK != retVal)
        {
            DebugP_log("Display Delete Failed!!!\r\n");
            break;
        }
    }

    /* Check for DSS synclost errors */
    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_GET_VP_ERROR_STATS,
        pErrorStats,
        NULL);
    if(FVID2_SOK != retVal)
    {
        DebugP_log("Failed to get VP Stats!!!\r\n");
    }

    /* Print Synclost errors */
    if(0U != pErrorStats->syncLost)
    {
        GT_1trace(DssTrace, GT_ERR, "No of Sync Lost: %d\r\n", pErrorStats->syncLost);
    }
    else
    {
        DebugP_log("Sync Lost did not occur\r\n");
    }

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_CLEAR_PATH,
        appObj->dctrlPathInfo,
        NULL);
    if(FVID2_SOK != retVal)
    {
        DebugP_log("Clear Path Failed!!!\r\n");
    }

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_STOP_VP,
        vpParams,
        NULL);

    if(FVID2_SOK != retVal)
    {
        DebugP_log("VP Stop Failed!!!\r\n");
    }

    if(FVID2_SOK == retVal)
    {
         DebugP_log("Display delete complete!!\r\n");
    }

    return;
}

static int32_t DispApp_allocAndQueueFrames(const Dss_Object *appObj,
                                           Dss_InstObject *instObj)
{
    int32_t  retVal = FVID2_SOK;
    uint32_t frmId, numFrames;
    Fvid2_Frame *frm;
    Fvid2_FrameList frmList;

    Fvid2FrameList_init(&frmList);
    frm = instObj->frames;
    numFrames = instObj->numFrames;
    /* init memory pointer for 'numFrames'  */
    for(frmId=0U; frmId<numFrames; frmId++)
    {
        /* init Fvid2_Frame to 0's  */
        Fvid2Frame_init((Fvid2_Frame *)(frm + frmId));
        if(instObj->instId == gDssConfigPipelineParams.instId[0U])
        {
            frm[frmId].addr[0U] = (uint64_t)firstPipeFrameBufferPointer[frmId];

            /* YUV 420 NV12 format is dual plane format. Here in a single buffer
             * we are calculating location of second plane by taking frame
             * input width and height. Fixing static indexes for pipeline
             * params so that we can link a frame buffer to first pipeline used.
             */
            if(gDssConfigPipelineParams.inDataFmt[0U] == FVID2_DF_YUV420SP_UV)
            {
                frm[frmId].addr[1U] = (uint64_t)firstPipeFrameBufferPointer[frmId] +
                                        gDssConfigPipelineParams.inWidth[0] * \
                                        gDssConfigPipelineParams.inHeight[0];
            }
        }
        else
        {
            frm[frmId].addr[0U] = (uint64_t)secondPipeFrameBufferPointer[frmId];

            /* YUV 420 NV12 format is dual plane format. Here in a single buffer
             * we are calculating location of second plane by taking frame
             * input width and height. Fixing static indexes for pipeline
             * params so that we can link a frame buffer to first pipeline used.
             */
            if(gDssConfigPipelineParams.inDataFmt[1U] == FVID2_DF_YUV420SP_UV)
            {
                frm[frmId].addr[1U] = (uint64_t)secondPipeFrameBufferPointer[frmId] +
                                        gDssConfigPipelineParams.inWidth[1] * \
                                        gDssConfigPipelineParams.inHeight[1];
            }

        }

        frm[frmId].fid = FVID2_FID_FRAME;
        frm[frmId].appData = instObj;

        /* Set number of frame in frame list - one at a time */
        frmList.numFrames  = 1U;
        frmList.frames[0U] = &frm[frmId];

        /*
         * queue the frames in frmList
         * All allocate frames are queued here as an example.
         * In general atleast 2 frames per channel need to queued
         * before starting display,
         * else frame will get dropped until frames are queued
         */
        retVal = Fvid2_queue(instObj->drvHandle, &frmList, 0U);
        if(FVID2_SOK != retVal)
        {
            DebugP_log("Display Queue Failed!!!\r\n");
            break;
        }
    }

    return (retVal);
}

static void DispApp_initPipelineParams(Dss_Object *appObj)
{
    uint32_t instCnt = 0U, numPipes = 0U;
    Dss_DispParams *dispParams;
    Dss_InstObject *instObj;

    numPipes = gDssConfigPipelineParams.numTestPipes;

    for(instCnt=0U; instCnt<numPipes; instCnt++)
    {
        /* Initialize video pipes */
        instObj = &appObj->instObj[instCnt];
        instObj->instId = gDssConfigPipelineParams.instId[instCnt];

        Dss_dispCreateParamsInit(&instObj->createParams);
        Fvid2CbParams_init(&instObj->cbParams);

        instObj->cbParams.cbFxn = &DispApp_pipeCbFxn;
        instObj->cbParams.appData = instObj;

        dispParams = &instObj->dispParams;
        Dss_dispParamsInit(dispParams);

        dispParams->pipeCfg.pipeType = gDssConfigPipelineParams.pipeType[instCnt];
        dispParams->pipeCfg.inFmt.width = gDssConfigPipelineParams.inWidth[instCnt];
        dispParams->pipeCfg.inFmt.height = gDssConfigPipelineParams.inHeight[instCnt];

        for(uint32_t count = 0U; count < FVID2_MAX_PLANES; count++)
        {
            dispParams->pipeCfg.inFmt.pitch[count] =
                                        gDssConfigPipelineParams.pitch[instCnt][count];
        }

        dispParams->pipeCfg.inFmt.dataFormat =
                                        gDssConfigPipelineParams.inDataFmt[instCnt];
        dispParams->pipeCfg.inFmt.scanFormat =
                                        gDssConfigPipelineParams.inScanFmt[instCnt];
        dispParams->pipeCfg.outWidth = gDssConfigPipelineParams.outWidth[instCnt];
        dispParams->pipeCfg.outHeight = gDssConfigPipelineParams.outHeight[instCnt];
        dispParams->pipeCfg.scEnable = gDssConfigPipelineParams.scEnable[instCnt];

#if(1U==DISP_APP_ENABLE_FLIP)
        dispParams->pipeCfg.flipType = FVID2_FLIP_TYPE_V;
#endif
        dispParams->alphaCfg.globalAlpha =
                                gDssConfigPipelineParams.globalAlpha[instCnt];
        dispParams->alphaCfg.preMultiplyAlpha =
                                gDssConfigPipelineParams.preMultiplyAlpha[instCnt];
        dispParams->layerPos.startX = gDssConfigPipelineParams.posx[instCnt];
        dispParams->layerPos.startY = gDssConfigPipelineParams.posy[instCnt];

#if(1U == DISP_APP_ENBALE_PIPE_CROP)
        dispParams->cropParams.cropEnable = TRUE;
        dispParams->cropParams.cropCfg.cropTop = 31;
        dispParams->cropParams.cropCfg.cropBottom = 31;
        dispParams->cropParams.cropCfg.cropLeft = 31;
        dispParams->cropParams.cropCfg.cropRight = 31;
#endif
        Dss_dispPipeMflagParamsInit(&instObj->mflagParams);
    }
}

static int32_t DispApp_configDctrl(Dss_Object *appObj)
{
    int32_t retVal = FVID2_SOK;

    Dss_DctrlVpParams *vpParams;
    Dss_DctrlOverlayParams *overlayParams;
    Dss_DctrlOverlayLayerParams *layerParams;
    Dss_DctrlAdvVpParams *advVpParams;
    Dss_DctrlGlobalDssParams *globalDssParams;
    Dss_DctrlOldiParams *oldiParams;

    oldiParams = appObj->oldiParams;
    vpParams = &appObj->vpParams;
    overlayParams = &appObj->overlayParams;
    layerParams = &appObj->layerParams;
    advVpParams = &appObj->advVpParams;
    globalDssParams= &appObj->globalDssParams;

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_SET_PATH,
        appObj->dctrlPathInfo,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("Dctrl Set Path IOCTL Failed!!!\r\n");
    }

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_SET_ADV_VP_PARAMS,
        advVpParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Set Advance VP Params IOCTL Failed!!!\r\n");
    }

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_SET_VP_PARAMS,
        vpParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("Dctrl Set VP Params IOCTL Failed!!!\r\n");
    }

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_SET_OLDI_PARAMS,
        oldiParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Set OLDI Params IOCTL Failed!!!\r\n");
    }

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_SET_OVERLAY_PARAMS,
        overlayParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Set Overlay Params IOCTL Failed!!!\r\n");
    }

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_SET_LAYER_PARAMS,
        layerParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Set Layer Params IOCTL Failed!!!\r\n");
    }

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_SET_GLOBAL_DSS_PARAMS,
        globalDssParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Set Global DSS Params IOCTL Failed!!!\r\n");
    }

    return (retVal);
}

static int32_t DispApp_pipeCbFxn(Fvid2_Handle handle, void *appData)
{
    int32_t retVal  = FVID2_SOK;
    Dss_InstObject *instObj = (Dss_InstObject *) appData;

    GT_assert (DssTrace, (NULL != instObj));
    (void) SemaphoreP_post(&instObj->syncSem);

    return (retVal);
}

