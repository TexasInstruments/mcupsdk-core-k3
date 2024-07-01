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
 *  \file dss_display_share.c
 *
 *  \brief DSS sample application that performs splash and share display with
 *         HLOS.
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
#include <kernel/dpl/TaskP.h>
#include "ti_drivers_open_close.h"
#include "ti_drivers_config.h"
#include "ti_board_open_close.h"
#include "dss_display_sample.h"
#include "FreeRTOS.h"
#include <drivers/device_manager/sciclient.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Frame buffer region start and length are defined in the linker. Macros
 * maintained here refer to the same, to configure firewall for this region.
 * Incase of linker is updated, please update the base address and length.
 */
#define DISP_FRAME_BUFFER_REGION_ADDRESS            (0x93500000U)
#define DISP_FRAME_BUFFER_REGION_LENGTH             (0x08000000U)


/* Max frame size based on resolution */
#define DISP_FRAME_SIZE_MAX                         (3840U*1080U)

/* Max pixel width */
#define DISP_FRAME_PIXEL_WIDTH_MAX                  (4U)

/* X and Y position for splash image */
#define DISP_SPLASH_IMAGE_XPOSTION                  760U
#define DISP_SPLASH_IMAGE_YPOSTION                  550U

/* Width and height of splash image */
#define DISP_SPLASH_IMAGE_WIDTH                     400U
#define DISP_SPLASH_IMAGE_HEIGHT                    100U

/* X and Y position for cluster image */
#define DISP_SHARE_IMAGE_XPOSTION                   610U
#define DISP_SHARE_IMAGE_YPOSTION                   120U

/* Width and height of cluster image */
#define DISP_SHARE_IMAGE_WIDTH                      700U
#define DISP_SHARE_IMAGE_HEIGHT                     105U

/* Number of bytes per pixel */
#define DISP_BYTES_PER_PIXEL                        4U

/* Splash timeout in ticks */
#define DISP_SPLASH_TIMEOUT_TICKS                   5000U

/* Splash thread priority */
#define TASK_PRI_SPLASH_THREAD                      (configMAX_PRIORITIES - 1U)
/* Display share thread priority */
#define TASK_PRI_SHARE_THREAD                       (configMAX_PRIORITIES - 1U)

/* Display task size */
#define DISPLAY_TASK_SIZE                           (4*1024U)

/* Number of same frame before frame change for cluster image */
#define DISPLAY_SHARE_THREAD_FRAME_SWAP_COUNT       (12U)

/* Number frames elapsed to measure fps */
#define DISPLAY_SHARE_THREAD_FPS_FRAME_COUNT        (300U)

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
static void DispApp_updateSplashFrameBuffer(void *frameBuf, uint32_t xpostion,
                                      uint32_t yposition, uint32_t width,
                                      uint32_t height, uint32_t bpp);
static void DispApp_updateTelltaleFrameBuffer(void *frameBuf, uint32_t xpostion,
                                              uint32_t yposition, uint32_t width,
                                              uint32_t height, uint32_t bpp);
static void DispApp_splashTimeoutCbFxn(ClockP_Object *obj, void *args);
static void DispApp_initFrames(uint32_t frameLength);
static void DispApp_fwlConfigureDssRegion(Dss_Object *appObj);
static void DispApp_fwlFrameBufferRegion(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Globals to hold fps time */
static uint32_t gStopProfileTime, gStartProfileTime, frameCount;

/*
 * Global frame buffer. Maximum frames per handle is considered 2 and first frame
 * is used for first pipeline instance. DSS sharing use case only uses one pipeline.
 */
uint8_t gFirstPipelineFrameBuf[CONFIG_DSS_NUM_FRAMES_PER_PIPELINE][DISP_FRAME_SIZE_MAX * DISP_FRAME_PIXEL_WIDTH_MAX]__attribute__ ((section (".dssFrameBuffer"), aligned (4096)));

/* Splash thread and display share thread stack */
static uint8_t gDisplaySplashTaskStack[DISPLAY_TASK_SIZE] __attribute__((aligned(32)));
static uint8_t gDisplayShareTaskStack[DISPLAY_TASK_SIZE] __attribute__((aligned(32)));

/* Splash thread and display share thread handles */
static TaskP_Object gDisplaySplashTask;
static TaskP_Object gDisplayShareTask;

/* Splash timeout semaphore */
static SemaphoreP_Object gSplashTimeoutSem;

/* Splash timeout clock object */
static ClockP_Object gSplashClockObj;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void dss_display_share_main(void *args)
{
    int32_t retVal = FVID2_SOK;

    DispApp_fwlConfigureDssRegion(&gDssObjects[CONFIG_DSS0]);

    DispApp_init(&gDssObjects[CONFIG_DSS0]);

    DebugP_log("DSS display share application started...\r\n");

    retVal = DispApp_runTest(&gDssObjects[CONFIG_DSS0]);

    if(FVID2_SOK == retVal)
    {
        DebugP_log("DSS display share Passed!!\r\n");
    }
    else
    {
        DebugP_log("DSS display share Failed!!\r\n");
    }

    return;
}

void DispApp_splashThread(void *args)
{
    int32_t status = SystemP_SUCCESS;
    int32_t retVal = FVID2_SOK;
    Dss_InstObject *instObj;
    Dss_Object *appObj = (Dss_Object*)args;
    instObj = &appObj->instObj[0];
    Fvid2_FrameList  frmList;
    ClockP_Params clockParams;
    Dss_DispParams *dispParams;

    /* Create timer for splash thread timeout */
    ClockP_Params_init(&clockParams);
    clockParams.timeout = DISP_SPLASH_TIMEOUT_TICKS;
    clockParams.period = 0;
    clockParams.callback = DispApp_splashTimeoutCbFxn;
    clockParams.args = &gSplashTimeoutSem;
    status = ClockP_construct(&gSplashClockObj, &clockParams);

    if(status == SystemP_SUCCESS)
    {
        /* Initialise frames */
        DispApp_initFrames(DISP_SPLASH_IMAGE_WIDTH * DISP_SPLASH_IMAGE_HEIGHT * DISP_BYTES_PER_PIXEL);

        /* Update frame buffers for the pipeline before starting display */
        DispApp_updateSplashFrameBuffer((void*)&gFirstPipelineFrameBuf[0], 0, \
                                0, DISP_SPLASH_IMAGE_WIDTH, \
                                DISP_SPLASH_IMAGE_HEIGHT, DISP_BYTES_PER_PIXEL);

        DispApp_updateSplashFrameBuffer((void*)&gFirstPipelineFrameBuf[1], 0, \
                    0, DISP_SPLASH_IMAGE_WIDTH, \
                    DISP_SPLASH_IMAGE_HEIGHT, DISP_BYTES_PER_PIXEL);

        dispParams = &instObj->dispParams;

        /* Update input splash image frame length and width for DSS */
        dispParams->pipeCfg.inFmt.width = DISP_SPLASH_IMAGE_WIDTH;
        dispParams->pipeCfg.inFmt.height = DISP_SPLASH_IMAGE_HEIGHT;
        dispParams->pipeCfg.inFmt.pitch[0] =DISP_SPLASH_IMAGE_WIDTH * DISP_BYTES_PER_PIXEL;
        dispParams->pipeCfg.outWidth = DISP_SPLASH_IMAGE_WIDTH;
        dispParams->pipeCfg.outHeight = DISP_SPLASH_IMAGE_HEIGHT;
        dispParams->layerPos.startX = DISP_SPLASH_IMAGE_XPOSTION;
        dispParams->layerPos.startY = DISP_SPLASH_IMAGE_YPOSTION;

        /* Send IOCTL to set DSS pipeline parameters */
        retVal = Fvid2_control(
                instObj->drvHandle,
                IOCTL_DSS_DISP_SET_DSS_PARAMS,
                &instObj->dispParams,
                NULL);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("DSS Set Params IOCTL Failed!!!\r\n");
        }

        if(retVal == FVID2_SOK)
        {
            /* Start display driver */
            retVal = Fvid2_start(instObj->drvHandle, NULL);
        }

        if(retVal != FVID2_SOK)
        {
            DebugP_log("Display Start Failed!!!\r\n");
        }
        else
        {
            /* Start splash thread timeout */
            ClockP_start(&gSplashClockObj);
        }

        if(retVal == FVID2_SOK)
        {
            while(true)
            {
                int32_t retVal = FVID2_SOK;

                /* Pend for display frame queue sync sempahore */
                SemaphoreP_pend(&instObj->syncSem, SystemP_WAIT_FOREVER);

                /* Dequeue diplayed frame */
                retVal = Fvid2_dequeue(instObj->drvHandle,
                                        &frmList,
                                        0U,
                                        FVID2_TIMEOUT_NONE);

                if(FVID2_SOK == retVal)
                {
                    /* Update frame buffer for dequeued frame */
                    DispApp_updateSplashFrameBuffer((void*)frmList.frames[0]->addr[0], 0, \
                                            0, DISP_SPLASH_IMAGE_WIDTH, \
                                            DISP_SPLASH_IMAGE_HEIGHT, DISP_BYTES_PER_PIXEL);

                    /* Queue the new frame buffer */
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
    }

    TaskP_destruct(&gDisplaySplashTask);
}

void DispApp_displayShareThread(void *args)
{
    int32_t retVal = FVID2_SOK;
    Dss_InstObject *instObj;
    Dss_Object *appObj = (Dss_Object*)args;
    instObj = &appObj->instObj[0];
    Fvid2_FrameList  frmList;

    SemaphoreP_pend(&instObj->syncSem, SystemP_WAIT_FOREVER);
    DispApp_initFrames(gDssConfigPipelineParams.inHeight[0] * gDssConfigPipelineParams.pitch[0][0]);

    /* Reinitialise pipeline params for tell tales */
    DispApp_initPipelineParams(&gDssObjects[CONFIG_DSS0]);

    /* Send IOCTL to set DSS pipeline parameters */
    retVal = Fvid2_control(
        instObj->drvHandle,
        IOCTL_DSS_DISP_SET_DSS_PARAMS,
        &instObj->dispParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DSS Set Params IOCTL Failed!!!\r\n");
    }

    gStartProfileTime = (ClockP_getTimeUsec() / 1000U);

    while(true)
    {
        int32_t retVal = FVID2_SOK;

        /* Pend for display frame queue sync sempahore */
        SemaphoreP_pend(&instObj->syncSem, SystemP_WAIT_FOREVER);

        retVal = Fvid2_dequeue(instObj->drvHandle,
                                &frmList,
                                0U,
                                FVID2_TIMEOUT_NONE);

        if(FVID2_SOK == retVal)
        {
            /* Update frame buffer for dequeued frame */
            DispApp_updateTelltaleFrameBuffer((void*)frmList.frames[0]->addr[0], DISP_SHARE_IMAGE_XPOSTION, \
                                    DISP_SHARE_IMAGE_YPOSTION, DISP_SHARE_IMAGE_WIDTH, \
                                    DISP_SHARE_IMAGE_HEIGHT, DISP_BYTES_PER_PIXEL);

            /* Queue the new frame buffer */
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

        if(frameCount == DISPLAY_SHARE_THREAD_FPS_FRAME_COUNT)
        {
            gStopProfileTime = (ClockP_getTimeUsec() / 1000U);

            DebugP_log("Number of elapsed frames = %d, elapsed msec = %d, fps = %0.2f\r\n",
                        DISPLAY_SHARE_THREAD_FPS_FRAME_COUNT,
                        gStopProfileTime - gStartProfileTime,
                        (float)((float)DISPLAY_SHARE_THREAD_FPS_FRAME_COUNT / ((gStopProfileTime - gStartProfileTime)/1000.0)));

            /* Reset frame count and measurement time */
            frameCount = 0;
            gStartProfileTime = (ClockP_getTimeUsec() / 1000U);
        }
        else
        {
            frameCount++;
        }
    }

    /* Incase of display failure, stop display driver */
    retVal  = Fvid2_stop(instObj->drvHandle, NULL);

    if(retVal != FVID2_SOK)
    {
        DebugP_log("Display Stop Failed!!!\r\n");
    }

    if(FVID2_SOK == retVal)
    {
        /* Delete driver */
        DispApp_delete(appObj);
        DispApp_deInit(&gDssObjects[CONFIG_DSS0]);
    }

    TaskP_destruct(&gDisplayShareTask);
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
    int32_t status = SystemP_SUCCESS;
    Dss_InstObject *instObj;
    instObj = &appObj->instObj[0];
    TaskP_Params taskParams;

    /* Create driver */
    DispApp_create(appObj);

    DebugP_log("Starting display ... !!!\r\n");
    DebugP_log("Display in progress ... DO NOT HALT !!!\r\n");

    /* Create splash thread */
    TaskP_Params_init(&taskParams);
    taskParams.name = "DispApp_splashThread";
    taskParams.stackSize = DISPLAY_TASK_SIZE;
    taskParams.stack = &gDisplaySplashTaskStack[0];
    taskParams.priority = TASK_PRI_SPLASH_THREAD;
    taskParams.args = (void*)&gDssObjects[CONFIG_DSS0];
    taskParams.taskMain = DispApp_splashThread;

    status = TaskP_construct(&gDisplaySplashTask, &taskParams);

    status += SemaphoreP_constructBinary(&gSplashTimeoutSem, 0);

    if(status == SystemP_SUCCESS)
    {
        /* Pend for splash thread timeout */
        SemaphoreP_pend(&gSplashTimeoutSem, SystemP_WAIT_FOREVER);
        SemaphoreP_destruct(&gSplashTimeoutSem);

        /* Kill splash thread only when there is some frame queued in display driver */
        SemaphoreP_pend(&instObj->syncSem, SystemP_WAIT_FOREVER);
        TaskP_destruct(&gDisplaySplashTask);

        if(status == SystemP_SUCCESS)
        {
            /* Create display share thread */
            TaskP_Params_init(&taskParams);
            taskParams.name = "DispApp_displayShareThread";
            taskParams.stackSize = DISPLAY_TASK_SIZE;
            taskParams.stack = &gDisplayShareTaskStack[0];
            taskParams.priority = TASK_PRI_SHARE_THREAD;
            taskParams.args = (void*)&gDssObjects[CONFIG_DSS0];
            taskParams.taskMain = DispApp_displayShareThread;

            status = TaskP_construct(&gDisplayShareTask, &taskParams);

            if(status == SystemP_FAILURE)
            {
                DebugP_log("Display share task failed!!!\r\n");
            }
        }

    }

    if(status != SystemP_SUCCESS)
    {
        ClockP_destruct(&gSplashClockObj);
        SemaphoreP_destruct(&gSplashTimeoutSem);
        TaskP_destruct(&gDisplaySplashTask);
        TaskP_destruct(&gDisplayShareTask);
        DebugP_log("Display start failed!!!\r\n");
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

            /* Create Display driver */
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

            /* Call display set params IOTCL */
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

            /* Call set mflag params IOTCL */
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

            /* Allocate frame buffers to display driver */
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
            frm[frmId].addr[0U] = (uint64_t)&gFirstPipelineFrameBuf[frmId];
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

    /* Call display set path IOCTL */
    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_SET_PATH,
        appObj->dctrlPathInfo,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("Dctrl Set Path IOCTL Failed!!!\r\n");
    }

    /* Call set advance VP params IOCTL */
    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_SET_ADV_VP_PARAMS,
        advVpParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Set Advance VP Params IOCTL Failed!!!\r\n");
    }

    /* Call set VP params IOCTL */
    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_SET_VP_PARAMS,
        vpParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("Dctrl Set VP Params IOCTL Failed!!!\r\n");
    }

    /* Call set OLDI params IOCTL */
    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_SET_OLDI_PARAMS,
        oldiParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Set OLDI Params IOCTL Failed!!!\r\n");
    }

    /* Call set OVERLAY params IOCTL */
    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_SET_OVERLAY_PARAMS,
        overlayParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Set Overlay Params IOCTL Failed!!!\r\n");
    }

    /* Call set layer params IOCTL to set ZORDER */
    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_SET_LAYER_PARAMS,
        layerParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Set Layer Params IOCTL Failed!!!\r\n");
    }

    /* Set the global dss params like CBA config */
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

static void DispApp_splashTimeoutCbFxn(ClockP_Object *obj, void *args)
{
    SemaphoreP_Object *pSemObj = (SemaphoreP_Object *)args;

    SemaphoreP_post(pSemObj);
}

static void DispApp_updateSplashFrameBuffer(void *frameBuf, uint32_t xpostion, \
                                uint32_t yposition, uint32_t width, \
                                uint32_t height, uint32_t bpp)
{
    uint32_t yDestPos = yposition;
    uint32_t ySrcPos = 0;
    uint32_t iCnt = 0;
    uint32_t jCnt = 0;
    volatile uint32_t *srcPtr = NULL;
    volatile uint32_t *destPtr = NULL;
    static uint8_t alphaBlendVal = 0x0U;

    if (xpostion + width >= gDssVpParams.lcdOpTimingCfg.mInfo.width)
    {
        width = gDssVpParams.lcdOpTimingCfg.mInfo.width - xpostion;
    }

    if (yposition + height >= gDssVpParams.lcdOpTimingCfg.mInfo.height)
    {
        height = gDssVpParams.lcdOpTimingCfg.mInfo.height - yposition;
    }

    /* Update alpha blending value */
    alphaBlendVal = (alphaBlendVal != 0xFFU) ? alphaBlendVal + 1U : alphaBlendVal;

    /* Copy source image to frame buffer at desired location */
    while (ySrcPos <= height)
    {
        iCnt = yDestPos * bpp * width + xpostion * bpp;
        jCnt = ySrcPos * width * bpp;
        destPtr = (volatile uint32_t *)(frameBuf + iCnt);
        srcPtr = (volatile uint32_t *)&gFrameLogoData[jCnt];

        for (uint32_t count = 0; count < width; count++)
        {
            /* Current alpha update is for ARGB888 frame type.
             * Changing frame type requires update to the below written logic to update
             * alpha value in frame.
             */
            *destPtr = (*srcPtr & 0xFFFFFF00) | ((uint32_t)alphaBlendVal  & 0x000000FF);
            destPtr++;
            srcPtr++;
        }
        CacheP_wb(frameBuf + iCnt, width * bpp, CacheP_TYPE_ALLD);
        yDestPos++;
        ySrcPos++;
    }
}

static void DispApp_updateTelltaleFrameBuffer(void *frameBuf, uint32_t xpostion, \
                                uint32_t yposition, uint32_t width, \
                                uint32_t height, uint32_t bpp)
{
    uint32_t yDestPos = yposition;
    uint32_t ySrcPos = 0;
    uint32_t iCnt = 0;
    uint32_t jCnt = 0;
    volatile uint8_t *destPtr = NULL;
    volatile uint8_t* sourceframe = NULL;
    static uint8_t toggleFrameCnt = 0x0U;
    static uint8_t toggleFrame = true;

    if (xpostion + width >= gDssVpParams.lcdOpTimingCfg.mInfo.width)
    {
        width = gDssVpParams.lcdOpTimingCfg.mInfo.width - xpostion;
    }

    if (yposition + height >= gDssVpParams.lcdOpTimingCfg.mInfo.height)
    {
        height = gDssVpParams.lcdOpTimingCfg.mInfo.height - yposition;
    }

    /* Toggle between two frames while updating the frame buffer */
    if (toggleFrame == true)
    {
        toggleFrameCnt = (toggleFrameCnt != DISPLAY_SHARE_THREAD_FRAME_SWAP_COUNT) ? toggleFrameCnt + 1U : toggleFrameCnt;
        toggleFrame = (toggleFrameCnt != DISPLAY_SHARE_THREAD_FRAME_SWAP_COUNT) ? true : false;
        sourceframe = (volatile uint8_t *)&gFrameTellTaleData1[0];
    }
    else
    {
        toggleFrameCnt = (toggleFrameCnt != 0x0U) ? toggleFrameCnt - 1U : toggleFrameCnt;
        toggleFrame = (toggleFrameCnt != 0x0U) ? false : true;
        sourceframe = (volatile uint8_t *)&gFrameTellTaleData2[0];
    }

    /* Copy source image to frame buffer at desired location */
    while (ySrcPos <= height)
    {
        iCnt = yDestPos * bpp * gDssVpParams.lcdOpTimingCfg.mInfo.width + xpostion * bpp;
        jCnt = ySrcPos * width * bpp;
        destPtr = (volatile uint8_t *)(frameBuf + iCnt);

        memcpy((void*)destPtr, (void*)(sourceframe + jCnt), width * bpp);
        CacheP_wb((void*)destPtr, width * bpp, CacheP_TYPE_ALLD);

        yDestPos++;
        ySrcPos++;
    }
}

static void DispApp_initFrames(uint32_t frameLength)
{
    /* Reset frame buffer */
    for(uint8_t numframes = 0 ; numframes < CONFIG_DSS_NUM_FRAMES_PER_PIPELINE; numframes++)
    {
        memset(&gFirstPipelineFrameBuf[numframes], 0x00, frameLength);
    }
}

static void DispApp_fwlConfigureDssRegion(Dss_Object *appObj)
{
    int32_t status = SystemP_FAILURE;
    Dss_FirewallRegionConfig *fwlData = appObj->fwlConfig;
    /* Before configuring the DSS register region specific firewall region to
     * allow access to only DM and A core, configure the whole region covered by
     * the firewall to allow access to all cores as a background region. So that
     * the other regions (except the DSS specific regions) guarded by this
     * firewall will be accessible to all cores.
     */
    const struct tisci_msg_fwl_set_firewall_region_req fwl_set_req =
    {
        .fwl_id = fwlData->fwlRegionData[0U].fwlId,
        .region = 0,
        .n_permission_regs = 3,
        /*
         * The firewall control register layout is
         *  ---------------------------------------------------------------------------
         * |  31:10   |      9     |     8      |     7:5    |      4      |   3:0     |
         *  ---------------------------------------------------------------------------
         * | Reserved | Cache Mode | Background |  Reserved  | Lock Config |  Enable   |
         *  ---------------------------------------------------------------------------
         *
         * Enable = 0xA implies firewall is enabled. Any other value means not enabled
         *
         */
        .control = 0x30A, /* 0x3 - Firewall background region, Unlocked. 0xA - Enable Firewall */
        /*
         * The firewall permission register layout is
         *  ---------------------------------------------------------------------------
         * |  31:24   |    23:16   |  15:12     |   11:8     |   7:4      |   3:0      |
         *  ---------------------------------------------------------------------------
         * | Reserved |   Priv ID  | NSUSR-DCRW | NSPRI-DCRW | SUSER-DCRW | SPRIV-DCRW |
         *  ---------------------------------------------------------------------------
         *
         * PRIV_ID = 0xC3 implies all.
         * In each of the 4 nibbles from 15:0 the 4 bits means Debug, Cache,
         * Read, Write Access for Non-secure user, Non-secure Priv,
         * Secure user, Secure Priv respectively. To enable all access bits for
         * all users, we set each of these nibbles to 0b1111 = 0xF.
         * So 15:0 becomes 0xFFFF
         */
        .permissions[0] = 0xC3FFFF,
        .permissions[1] = 0xC3FFFF,
        .permissions[2] = 0xC3FFFF,
        .start_address  = 0X0,
        .end_address    = 0xFFFFFFFFU,
    };
    struct tisci_msg_fwl_set_firewall_region_resp fwl_set_resp = { 0 };

    status = Sciclient_firewallSetRegion(&fwl_set_req, &fwl_set_resp, \
                                         SystemP_TIMEOUT);

    if(SystemP_SUCCESS == status)
    {
        for(uint32_t region = 0U; region < appObj->fwlConfig->numFwlRegion && \
            status == SystemP_SUCCESS; region++)
        {
            /* Lock the region 1 firewall ownership to DM core, so that other cores
             * cannot modify the below region 1 firewall configuration.
             */
            const struct tisci_msg_fwl_change_owner_info_req fwl_owner_req =
            {
                .fwl_id = fwlData->fwlRegionData[region].fwlId,
                .region = region + 1U,
                .owner_index = TISCI_HOST_ID_WKUP_0_R5_1,
            };
            struct tisci_msg_fwl_change_owner_info_resp fwl_owner_resp = { 0 };
            status = Sciclient_firewallChangeOwnerInfo(&fwl_owner_req, \
                                                       &fwl_owner_resp, \
                                                       SystemP_TIMEOUT);
            if(SystemP_SUCCESS == status)
            {
                /*
                 * Lock DSS Config region by region based firewall only to DM
                 * core. Configure this as a foreground region. This will
                 * override the above config only for DSS region. So all other
                 * regions covered by the firewall can be accessed by other
                 * cores.
                 */
                const struct tisci_msg_fwl_set_firewall_region_req fwl_set_req =
                {
                    .fwl_id = fwlData->fwlRegionData[region].fwlId,
                    .region = region + 1U,
                    .n_permission_regs = 2U,
                    /* 0xA - Enable Firewall */
                    .control = 0xA,
                    /* PRIV_ID = 0xD4 implies DM R5 core, giving full access to
                     * to DM core.
                     */
                    .permissions[0] = 0xD4FFFF,
                    /* PRIV_ID = 0x04 implies A53 core, giving read access to
                     * a53 context.
                     */
                    .permissions[1] = 0x042222,

                    .start_address  = fwlData->fwlRegionData[region].startAddr,
                    .end_address    = fwlData->fwlRegionData[region].endAddr,
                };
                struct tisci_msg_fwl_set_firewall_region_resp fwl_set_resp = \
                                                                          { 0 };

                status = Sciclient_firewallSetRegion(&fwl_set_req, \
                                                     &fwl_set_resp, \
                                                     SystemP_TIMEOUT);
            }
        }

    }

    if(status == SystemP_SUCCESS)
    {
        DebugP_log("Configure DSS region firewall... DONE !!!\r\n");
    }
    else
    {
        DebugP_logError("Configure DSS region firewall ... Failed !!!\r\n");
    }
}

static void DispApp_fwlFrameBufferRegion(void)
{
    int32_t status = SystemP_FAILURE;

    /* Before configuring the DSS register region specific firewall region to
     * allow access to only DM and A core, configure the whole region covered by
     * the firewall to allow access to all cores as a background region. So that
     * the other regions (except the DSS specific regions) guarded by this
     * firewall will be accessible to all cores.
     */
    const struct tisci_msg_fwl_set_firewall_region_req fwl_set_req =
    {
        .fwl_id = CSL_STD_FW_DDR32SS0_SDRAM_FW1_ID,
        .region = 0,
        .n_permission_regs = 3,
        /*
         * The firewall control register layout is
         *  ---------------------------------------------------------------------------
         * |  31:10   |      9     |     8      |     7:5    |      4      |   3:0     |
         *  ---------------------------------------------------------------------------
         * | Reserved | Cache Mode | Background |  Reserved  | Lock Config |  Enable   |
         *  ---------------------------------------------------------------------------
         *
         * Enable = 0xA implies firewall is enabled. Any other value means not enabled
         *
         */
        .control = 0x30A, /* 0x3 - Firewall background region, Unlocked. 0xA - Enable Firewall */
        /*
         * The firewall permission register layout is
         *  ---------------------------------------------------------------------------
         * |  31:24   |    23:16   |  15:12     |   11:8     |   7:4      |   3:0      |
         *  ---------------------------------------------------------------------------
         * | Reserved |   Priv ID  | NSUSR-DCRW | NSPRI-DCRW | SUSER-DCRW | SPRIV-DCRW |
         *  ---------------------------------------------------------------------------
         *
         * PRIV_ID = 0xC3 implies all.
         * In each of the 4 nibbles from 15:0 the 4 bits means Debug, Cache,
         * Read, Write Access for Non-secure user, Non-secure Priv,
         * Secure user, Secure Priv respectively. To enable all access bits for
         * all users, we set each of these nibbles to 0b1111 = 0xF.
         * So 15:0 becomes 0xFFFF
         */
        .permissions[0] = 0xC3FFFF,
        .permissions[1] = 0xC3FFFF,
        .permissions[2] = 0xC3FFFF,
        .start_address  = 0X0,
        .end_address    = 0xFFFFFFFFU,
    };
    struct tisci_msg_fwl_set_firewall_region_resp fwl_set_resp = { 0 };

    status = Sciclient_firewallSetRegion(&fwl_set_req, &fwl_set_resp, \
                                         SystemP_TIMEOUT);

    if(SystemP_SUCCESS == status)
    {

        /* Lock the region 1 firewall ownership to DM core, so that other cores
         * cannot modify the below region 1 firewall configuration.
         */
        const struct tisci_msg_fwl_change_owner_info_req fwl_owner_req =
        {
            .fwl_id = CSL_STD_FW_DDR32SS0_SDRAM_FW1_ID,
            .region = 1U,
            .owner_index = TISCI_HOST_ID_WKUP_0_R5_1,
        };
        struct tisci_msg_fwl_change_owner_info_resp fwl_owner_resp = { 0 };
        status = Sciclient_firewallChangeOwnerInfo(&fwl_owner_req, \
                                                    &fwl_owner_resp, \
                                                    SystemP_TIMEOUT);
        if(SystemP_SUCCESS == status)
        {
            /*
                * Lock DSS Config region by region based firewall only to DM
                * core. Configure this as a foreground region. This will
                * override the above config only for DSS region. So all other
                * regions covered by the firewall can be accessed by other
                * cores.
                */
            const struct tisci_msg_fwl_set_firewall_region_req fwl_set_req =
            {
                .fwl_id = CSL_STD_FW_DDR32SS0_SDRAM_FW1_ID,
                .region = 1U,
                .n_permission_regs = 1U,
                /* 0xA - Enable Firewall */
                .control = 0xA,
                /* PRIV_ID = 0xD4 implies DM R5 core, giving full access to
                 * to DM core.
                 */
                .permissions[0] = 0xD4FFFF,
                .start_address  = (uint64_t)DISP_FRAME_BUFFER_REGION_ADDRESS,
                .end_address    = (uint64_t)(DISP_FRAME_BUFFER_REGION_ADDRESS +\
                                  DISP_FRAME_BUFFER_REGION_LENGTH),
            };
            struct tisci_msg_fwl_set_firewall_region_resp fwl_set_resp = \
                                                                        { 0 };

            status = Sciclient_firewallSetRegion(&fwl_set_req, \
                                                    &fwl_set_resp, \
                                                    SystemP_TIMEOUT);
        }

    }

    if(status == SystemP_SUCCESS)
    {
        DebugP_log("Configure DSS framebuffer region firewall... DONE !!!\r\n");
    }
    else
    {
        DebugP_logError("Configure DSS framebuffer region firewall ... Failed !!!\r\n");
    }
}