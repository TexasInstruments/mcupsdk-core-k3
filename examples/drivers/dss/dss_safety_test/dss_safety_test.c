/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
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
 *  \file dss_safety_test.c
 *
 *  \brief DSS sample application that configures and tests DSS safety features
 *         (Freeze Frame Detect and Data Integrity Check).
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

/* Number of frames */
#define DISP_NUM_FRAMES_COUNT               ((uint32_t)100U)

/* Max frame size based on resolution */
#define DISP_FRAME_SIZE_MAX                 (3840U*1080U)

/* Max pixel width */
#define DISP_FRAME_PIXEL_WIDTH_MAX          (4U)

/* Corrupt frame number */
#define DISP_FRAME_CORRUPT_NUM              (70U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    uint32_t safetyInterupt;
    /**< Flag to check interupt received */
    uint32_t vpId;
    /**< Video Port Id */
    uint32_t pipeId;
    /**< Pipe Id */
    uint32_t frameCount;
    /**< Frame Count */
    uint32_t safetyCheckMode;
    /**< Mode of operation of the safety check module */
    Dss_DctrlVpSafetyCbData cbData;
    /**< Safety Error callback data to be returned to application */
} Dss_safetyTestCbData;

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
static void DispApp_vpSafetyErrCallback(uint32_t vpID,
                                        Dss_DctrlVpSafetyCbData safetyCbData,
                                        void *appData);
static void DispApp_pipelineSafetyErrCallback(uint32_t pipeId,
                                              uint32_t capturedSign,
                                              void *appData);
static int32_t DispApp_logSafetyCheckData();

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
void *gfirstPipeFrameBufferPointer[CONFIG_DSS_NUM_FRAMES_PER_PIPELINE];
void *gsecondPipeFrameBufferPointer[CONFIG_DSS_NUM_FRAMES_PER_PIPELINE];

static Dss_safetyTestCbData gSafetyCallbackDataVP[CONFIG_DSS_NUM_SAFETY_REGIONS];
static Dss_safetyTestCbData gSafetyCallbackDataVID;
static Dss_safetyTestCbData gSafetyCallbackDataVIDL;

static volatile uint32_t gLoopCount;
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void DispApp_initFrames()
{
    uint32_t instCnt = 0;

    for(instCnt = 0; instCnt < CONFIG_DSS_NUM_FRAMES_PER_PIPELINE; instCnt++)
    {
        gfirstPipeFrameBufferPointer[instCnt] = &gFirstPipelineFrameBuf[instCnt];
        gsecondPipeFrameBufferPointer[instCnt] = &gSecondPipelineFrameBuf[instCnt];
    }

    for(instCnt = 0U; instCnt<gDssConfigPipelineParams.numTestPipes; instCnt++)
    {
        if(instCnt != 0)
        {
            Disp_prepareFrameBuffer(instCnt,&gDssConfigPipelineParams,
                                       gsecondPipeFrameBufferPointer);
        }
        else
        {
            Disp_prepareFrameBuffer(instCnt,&gDssConfigPipelineParams,
                                       gfirstPipeFrameBufferPointer);
        }
    }

}

/*
 * DSS display test
 */
void dss_safety_test_main(void *args)
{
    int32_t retVal = SystemP_SUCCESS;

    /* Initialise frames */
    DispApp_initFrames();

    DispApp_init(&gDssObjects[CONFIG_DSS0]);

    DebugP_log("DSS display application started...\r\n");

    retVal = DispApp_runTest(&gDssObjects[CONFIG_DSS0]);

    DispApp_deInit(&gDssObjects[CONFIG_DSS0]);

    retVal = DispApp_logSafetyCheckData();

    if(SystemP_SUCCESS == retVal)
    {
        DebugP_log("DSS Safety Test Passed!!\r\n");
    }
    else
    {
        DebugP_log("DSS Safety Test Failed!!\r\n");
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

    while(gLoopCount++ < DISP_NUM_FRAMES_COUNT)
    {
        for(instCnt=0U; instCnt<gDssConfigPipelineParams.numTestPipes; instCnt++)
        {
            instObj = &appObj->instObj[instCnt];
            (void) SemaphoreP_pend(&instObj->syncSem, SystemP_WAIT_FOREVER);
            retVal = Fvid2_dequeue(instObj->drvHandle,
                                   &frmList,
                                   0U,
                                   FVID2_TIMEOUT_NONE);

            /* Corrupt frame to introduce data integrity error */
            if(gLoopCount == DISP_FRAME_CORRUPT_NUM)
            {
                for(uint32_t count = 0; count < gDssConfigPipelineParams.inHeight[instCnt] * \
                gDssConfigPipelineParams.pitch[instCnt][0]; count++)
                {
                    *(uint8_t *)(frmList.frames[0]->addr[0] + count) = 0xAA;
                }
            }

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

    return (retVal != FVID2_SOK? SystemP_FAILURE:SystemP_SUCCESS);
}

static void DispApp_initDssParams(Dss_Object *appObj)
{
    Dss_DctrlVpParams *vpParams;
    Dss_DctrlAdvVpParams *advVpParams;
    Dss_DctrlOverlayParams *overlayParams;
    Dss_DctrlOverlayLayerParams *layerParams;
    Dss_DctrlGlobalDssParams *globalDssParams;
    Dss_DctrlVpSafetyChkParams *vpSafetyParams;

    vpParams = &appObj->vpParams;
    overlayParams = &appObj->overlayParams;
    layerParams = &appObj->layerParams;
    advVpParams = &appObj->advVpParams;
    globalDssParams = &appObj->globalDssParams;
    vpSafetyParams = (Dss_DctrlVpSafetyChkParams*)&appObj->vpSafetyParams;

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

    /* Configure VP Safety Params */
    for(uint8_t count = 0; count < CSL_DSS_VP_SAFETY_REGION_MAX; count++)
    {
        Dss_dctrlVpSafetyChkParamsInit(vpSafetyParams + count);
    }

    for(uint8_t count = 0; count < CONFIG_DSS_NUM_SAFETY_REGIONS; count++)
    {
        vpSafetyParams[count].vpId = gDssVpSafetyParams[count].vpId;
        vpSafetyParams[count].safetySignSeedVal = gDssVpSafetyParams[count].safetySignSeedVal;
        vpSafetyParams[count].regionSafetyChkCfg.regionId = gDssVpSafetyParams[count].regionSafetyChkCfg.regionId;
        vpSafetyParams[count].regionSafetyChkCfg.referenceSign = gDssVpSafetyParams[count].regionSafetyChkCfg.referenceSign;
        vpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.safetyChkEnable = gDssVpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.safetyChkEnable;
        vpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.safetyChkMode = gDssVpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.safetyChkMode;
        vpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.seedSelectEnable = gDssVpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.seedSelectEnable;
        vpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.thresholdValue = gDssVpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.thresholdValue;
        vpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.frameSkip = gDssVpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.frameSkip;
        vpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.regionPos.startX = gDssVpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.regionPos.startX;
        vpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.regionPos.startY = gDssVpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.regionPos.startY;
        vpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.regionSize.width = gDssVpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.regionSize.width;
        vpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.regionSize.height = gDssVpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.regionSize.height;

        vpSafetyParams[count].safetyErrCbFxn = DispApp_vpSafetyErrCallback;
        vpSafetyParams[count].appData = &vpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.safetyChkMode;
    }

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
                if(gDssConfigPipelineParams.safetyCheck[instCnt] == TRUE)
                {
                    retVal = Fvid2_control(
                        instObj->drvHandle,
                        IOCTL_DSS_DISP_SET_PIPE_SAFETY_CHK_PARAMS,
                        &instObj->safetyParams,
                        NULL);
                    if(retVal != FVID2_SOK)
                    {
                        DebugP_log("DSS Set Safety Params IOCTL Failed!!!\r\n");
                    }
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
            frm[frmId].addr[0U] = (uint64_t)gfirstPipeFrameBufferPointer[frmId];
        }
        else
        {
            frm[frmId].addr[0U] = (uint64_t)gsecondPipeFrameBufferPointer[frmId];
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

        dispParams->alphaCfg.globalAlpha =
                                gDssConfigPipelineParams.globalAlpha[instCnt];
        dispParams->alphaCfg.preMultiplyAlpha =
                                gDssConfigPipelineParams.preMultiplyAlpha[instCnt];
        dispParams->layerPos.startX = gDssConfigPipelineParams.posx[instCnt];
        dispParams->layerPos.startY = gDssConfigPipelineParams.posy[instCnt];

        Dss_dispPipeMflagParamsInit(&instObj->mflagParams);

        if(gDssConfigPipelineParams.safetyCheck[instCnt] == TRUE)
        {
            Dss_dispPipeSafetyChkParamsInit(&instObj->safetyParams);

            instObj->safetyParams.safetySignSeedVal = gDssPipelineSafetyParams[instCnt].safetySignSeedVal;
            instObj->safetyParams.referenceSign = gDssPipelineSafetyParams[instCnt].referenceSign;
            instObj->safetyParams.safetyChkCfg.safetyChkEnable = gDssPipelineSafetyParams[instCnt].safetyChkCfg.safetyChkEnable;
            instObj->safetyParams.safetyChkCfg.safetyChkMode = gDssPipelineSafetyParams[instCnt].safetyChkCfg.safetyChkMode;
            instObj->safetyParams.safetyChkCfg.seedSelectEnable = gDssPipelineSafetyParams[instCnt].safetyChkCfg.seedSelectEnable;
            instObj->safetyParams.safetyChkCfg.thresholdValue = gDssPipelineSafetyParams[instCnt].safetyChkCfg.thresholdValue;
            instObj->safetyParams.safetyChkCfg.frameSkip = gDssPipelineSafetyParams[instCnt].safetyChkCfg.frameSkip;
            instObj->safetyParams.safetyChkCfg.regionPos.startX = gDssPipelineSafetyParams[instCnt].safetyChkCfg.regionPos.startX;
            instObj->safetyParams.safetyChkCfg.regionPos.startY = gDssPipelineSafetyParams[instCnt].safetyChkCfg.regionPos.startY;
            instObj->safetyParams.safetyChkCfg.regionSize.width = gDssPipelineSafetyParams[instCnt].safetyChkCfg.regionSize.width;
            instObj->safetyParams.safetyChkCfg.regionSize.height = gDssPipelineSafetyParams[instCnt].safetyChkCfg.regionSize.height;

            instObj->safetyParams.safetyErrCbFxn = DispApp_pipelineSafetyErrCallback;
            instObj->safetyParams.appData = &gDssConfigPipelineParams.pipeType[instCnt];
        }
    }
}

static int32_t DispApp_configDctrl(Dss_Object *appObj)
{
    int32_t retVal = FVID2_SOK;

    Dss_DctrlVpParams *vpParams;
    Dss_DctrlOverlayParams *overlayParams;
    Dss_DctrlOverlayLayerParams *layerParams;
    Dss_DctrlAdvVpParams *advVpParams;
    Dss_DctrlVpSafetyChkParams *vpSafetyParams;
    Dss_DctrlGlobalDssParams *globalDssParams;
    Dss_DctrlOldiParams *oldiParams;

    oldiParams = appObj->oldiParams;
    vpParams = &appObj->vpParams;
    overlayParams = &appObj->overlayParams;
    layerParams = &appObj->layerParams;
    advVpParams = &appObj->advVpParams;
    vpSafetyParams = (Dss_DctrlVpSafetyChkParams*)&appObj->vpSafetyParams;
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

    for(uint8_t count = 0; count < CONFIG_DSS_NUM_SAFETY_REGIONS; count++)
    {
        retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_SET_VP_SAFETY_CHK_PARAMS,
        vpSafetyParams + count,
        NULL);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("DCTRL Set Safety Params IOCTL Failed!!!\r\n");
            break;
        }
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

static void DispApp_vpSafetyErrCallback(uint32_t vpID,
                                        Dss_DctrlVpSafetyCbData safetyCbData,
                                        void *appData)
{
    if(gSafetyCallbackDataVP[safetyCbData.regionId].safetyInterupt != true && gLoopCount < DISP_NUM_FRAMES_COUNT)
    {
        gSafetyCallbackDataVP[safetyCbData.regionId].safetyInterupt = true;
        gSafetyCallbackDataVP[safetyCbData.regionId].vpId = vpID;
        gSafetyCallbackDataVP[safetyCbData.regionId].frameCount = gLoopCount;
        gSafetyCallbackDataVP[safetyCbData.regionId].safetyCheckMode = *(uint32_t *)appData;
        gSafetyCallbackDataVP[safetyCbData.regionId].cbData.capturedSign = safetyCbData.capturedSign;
        gSafetyCallbackDataVP[safetyCbData.regionId].cbData.regionId = safetyCbData.regionId;
    }

}

static void DispApp_pipelineSafetyErrCallback(uint32_t pipeId,
                                              uint32_t capturedSign,
                                              void *appData)
{
    if(pipeId == CSL_DSS_VID_PIPE_ID_VID1)
    {
        if(gSafetyCallbackDataVID.safetyInterupt != true && gLoopCount < DISP_NUM_FRAMES_COUNT)
        {
            gSafetyCallbackDataVID.safetyInterupt = true;
            gSafetyCallbackDataVID.pipeId = pipeId;
            gSafetyCallbackDataVID.frameCount = gLoopCount;
            gSafetyCallbackDataVID.safetyCheckMode = *(uint32_t *)appData;
            gSafetyCallbackDataVID.cbData.capturedSign = capturedSign;
        }
    }
    else if(pipeId == CSL_DSS_VID_PIPE_ID_VIDL1)
    {
        if(gSafetyCallbackDataVIDL.safetyInterupt != true && gLoopCount < DISP_NUM_FRAMES_COUNT)
        {
            gSafetyCallbackDataVIDL.safetyInterupt = true;
            gSafetyCallbackDataVIDL.pipeId = pipeId;
            gSafetyCallbackDataVIDL.frameCount = gLoopCount;
            gSafetyCallbackDataVIDL.safetyCheckMode = *(uint32_t *)appData;
            gSafetyCallbackDataVIDL.cbData.capturedSign = capturedSign;
        }
    }

}

static int32_t DispApp_logSafetyCheckData()
{
    int32_t status = SystemP_SUCCESS;
    uint32_t count;

    for(count = 0U; count < CONFIG_DSS_NUM_SAFETY_REGIONS; count++)
    {
        DebugP_log("****************************************************\r\n");

        DebugP_log("Safety Data Log Region : %d\r\n", gSafetyCallbackDataVP[count].cbData.regionId);
        DebugP_log("Safety Data VP ID: %s\r\n",gSafetyCallbackDataVP[count].vpId == CSL_DSS_VP_ID_1 ? "VP1" : "Invalid VP");

        if(gSafetyCallbackDataVP[count].safetyInterupt == true)
        {
            DebugP_log("Safety Check Interupt Trigger: TRUE\r\n");

            if(gSafetyCallbackDataVP[count].safetyCheckMode == CSL_DSS_SAFETY_CHK_FRAME_FREEZE_DETECT)
            {
                DebugP_log("Safety Check Mode: FRAME_FREEZE_DETECT\r\n");

                if(gSafetyCallbackDataVP[count].frameCount < gDssVpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.thresholdValue)
                {
                    status = SystemP_FAILURE;
                }
            }
            else if(gSafetyCallbackDataVP[count].safetyCheckMode == CSL_DSS_SAFETY_CHK_DATA_INTEGRITY)
            {
                DebugP_log("Safety Check Mode: DATA_INTEGRITY\r\n");
            }

            DebugP_log("Safety Data Frame count: %d\r\n", gSafetyCallbackDataVP[count].frameCount);
            DebugP_log("Safety Data Captured Signature: 0x%lX\r\n", gSafetyCallbackDataVP[count].cbData.capturedSign);
        }
        else
        {
            status = SystemP_FAILURE;
            DebugP_log("Safety Check Interupt Trigger: FALSE\r\n");
        }

    }

    for(uint32_t instCnt=0U; instCnt<gDssConfigPipelineParams.numTestPipes; instCnt++)
    {
        if(gDssConfigPipelineParams.safetyCheck[instCnt] == TRUE)
        {
            if(gDssConfigPipelineParams.pipeId[instCnt] == CSL_DSS_VID_PIPE_ID_VID1)
            {
                DebugP_log("****************************************************\r\n");

                DebugP_log("Safety Data Pipeline ID: VID1\r\n");

                if(gSafetyCallbackDataVID.safetyInterupt == true)
                {
                    DebugP_log("Safety Check Interupt Trigger: TRUE\r\n");

                    if(gSafetyCallbackDataVID.safetyCheckMode == CSL_DSS_SAFETY_CHK_FRAME_FREEZE_DETECT)
                    {
                        DebugP_log("Safety Check Mode: FRAME_FREEZE_DETECT\r\n");

                        if(gSafetyCallbackDataVID.frameCount < gDssPipelineSafetyParams[instCnt].safetyChkCfg.thresholdValue)
                        {
                            status = SystemP_FAILURE;
                        }
                    }
                    else if(gSafetyCallbackDataVID.safetyCheckMode == CSL_DSS_SAFETY_CHK_DATA_INTEGRITY)
                    {
                        DebugP_log("Safety Check Mode: DATA_INTEGRITY\r\n");
                    }

                    DebugP_log("Safety Data Frame count: %d\r\n", gSafetyCallbackDataVID.frameCount);
                    DebugP_log("Safety Data Captured Signature: 0x%lX\r\n", gSafetyCallbackDataVID.cbData.capturedSign);
                }
                else
                {
                    status = SystemP_FAILURE;
                    DebugP_log("Safety Check Interupt Trigger: FALSE\r\n");
                }

            }
            else if(gDssConfigPipelineParams.pipeId[instCnt] == CSL_DSS_VID_PIPE_ID_VIDL1)
            {
                DebugP_log("****************************************************\r\n");

                DebugP_log("Safety Data Pipeline ID: VIDL1\r\n");

                if(gSafetyCallbackDataVIDL.safetyInterupt == true)
                {
                    DebugP_log("Safety Check Interupt Trigger: TRUE\r\n");

                    if(gSafetyCallbackDataVIDL.safetyCheckMode == CSL_DSS_SAFETY_CHK_FRAME_FREEZE_DETECT)
                    {
                        DebugP_log("Safety Check Mode: FRAME_FREEZE_DETECT\r\n");

                        if(gSafetyCallbackDataVIDL.frameCount < gDssPipelineSafetyParams[instCnt].safetyChkCfg.thresholdValue)
                        {
                            status = SystemP_FAILURE;
                        }
                    }
                    else if(gSafetyCallbackDataVIDL.safetyCheckMode == CSL_DSS_SAFETY_CHK_DATA_INTEGRITY)
                    {
                        DebugP_log("Safety Check Mode: DATA_INTEGRITY\r\n");
                    }

                    DebugP_log("Safety Data Frame count: %d\r\n", gSafetyCallbackDataVIDL.frameCount);
                    DebugP_log("Safety Data Captured Signature: 0x%lX\r\n", gSafetyCallbackDataVIDL.cbData.capturedSign);
                }
                else
                {
                    status = SystemP_FAILURE;
                    DebugP_log("Safety Check Interupt Trigger: FALSE\r\n");
                }

            }
        }
    }

    return status;
}