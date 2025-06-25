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

/**
 *  \file test_display_dynamic_control.c
 *
 *  \brief Application to initialise and control display for the dynamic coverage.
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
#include "test_ids.h"
#include <drivers/dss/v0/dctrl/dss_dctrlDrv.h>
#include <drivers/dss/v0/common/dss_evtMgr.h>
#include <drivers/dss/v0/disp/dss_dispDrv.h>
#include <drivers/dss/v0/disp/dss_dispPriv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Number of frames (5sec 300 frames) */
#define DISP_NUM_FRAMES_COUNT              ((uint32_t)300U)

/* Max frame size based on resolution */
#define DISP_FRAME_SIZE_MAX                (3840U*1080U)

/* Max pixel width */
#define DISP_FRAME_PIXEL_WIDTH_MAX          (4U)

#define TEST_DSS_INVALID_IOCTL_CMD                   (0xFFFFFFU)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static int32_t TestDisp_init(Dss_Object *appObj);
static int32_t TestDisp_deInit(Dss_Object *appObj);
static int32_t TestDisp_create(Dss_Object *appObj);
static void TestDisp_delete(Dss_Object *appObj);
static int32_t TestDisp_configDctrl(Dss_Object *appObj);
static int32_t TestDisp_runTest(Dss_Object *appObj);
static void TestDisp_initPipelineParams(Dss_Object *appObj);
static int32_t TestDisp_allocAndQueueFrames(const Dss_Object *appObj,
                                           Dss_InstObject *instObj);
static int32_t TestDisp_pipeCbFxn(Fvid2_Handle handle, void *appData);
static void TestDisp_initDssParams(Dss_Object *appObj);

static int32_t TestDisp_createError(Dss_Object *appObj, uint32_t testId);
static int32_t TestDisp_runIoctlTest(Dss_Object *appObj, uint32_t testId);
static int32_t TestDisp_Error(Dss_Object *appObj, uint32_t testId);
static int32_t testStopVpIoctl(Dss_Object *appObj);
static int32_t testVPErrStatsIoctls(Dss_Object *appObj);
static int32_t testInvalidIoctSetup(Dss_Object *appObj);
static int32_t testSyncLostCBIoctl(Dss_Object *appObj);
static int32_t testLineCBIoctl(Dss_Object *appObj);
static void lineNumCallback();
static void syncLostCallback();
int32_t TestDisp_reregisterDriver(Dss_Object *appObj);
int32_t TestDisp_createDriver(Dss_Object *appObj);
int32_t TestDisp_unusedIoctl(Dss_Object *appObj);
int32_t TestDisp_dctrlIoctls(Dss_Object *appObj, uint32_t testId);
int32_t TestDisp_initParams(Dss_Object *appObj);
int32_t TestDisp_ioctlErrors(Dss_Object *appObj, uint32_t testId);

extern void Disp_prepareFrameBuffer(uint32_t instCount,
                            uint32_t inDataFmt, \
                            uint32_t inWidth, \
                            uint32_t inHeight,\
                            uint32_t pitch, \
                            void* \
                            frameBuffer[CONFIG_DSS_NUM_FRAMES_PER_PIPELINE]);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/*
 * Global frame buffers. Maximum frames per handle is considered 2 and first frame
 * is used for first pipeline instance and other is used for second pipeline instance.
 */
uint8_t gDssFirstPipelineFrameBuf[CONFIG_DSS_NUM_FRAMES_PER_PIPELINE][DISP_FRAME_SIZE_MAX * DISP_FRAME_PIXEL_WIDTH_MAX]__attribute__ ((section (".dssFrameBuffer"), aligned (4096)));
uint8_t gDssSecondPipelineFrameBuf[CONFIG_DSS_NUM_FRAMES_PER_PIPELINE][DISP_FRAME_SIZE_MAX * DISP_FRAME_PIXEL_WIDTH_MAX]__attribute__ ((section (".dssFrameBuffer"), aligned (4096))) ;

/* Pointer to frame buffers per pipleline */
void *firstPipeFrameBufferPointer[CONFIG_DSS_NUM_FRAMES_PER_PIPELINE];
void *secondPipeFrameBufferPointer[CONFIG_DSS_NUM_FRAMES_PER_PIPELINE];

uint32_t gLineNumCallbackHit = 0U;
uint32_t gSyncLostCallbackHit = 0U;
uint32_t gStopVpTest = 0U;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static Dss_DctrlPathInfo gfaultyDssPathInfo =
{
    .numEdges = 4,
    .edgeInfo = {
        {
            .startNode = DSS_DCTRL_NODE_VID1,
            .endNode = DSS_DCTRL_NODE_VP2,
        },
        {
            .startNode = DSS_DCTRL_NODE_OVR2,
            .endNode = DSS_DCTRL_NODE_VP2,
        },
        {
            .startNode = DSS_DCTRL_NODE_VP2,
            .endNode = DSS_DCTRL_NODE_DPI,
        },
        {
            .startNode = DSS_DCTRL_NODE_VIDL1,
            .endNode = DSS_DCTRL_NODE_OVR1,
        },

    }

};

void TestDisp_dssInitFrames()
{
    uint32_t instCnt = 0;
    uint32_t numPipes = gDssConfigPipelineParams.numTestPipes <= DSS_DISP_INST_MAX \
                        ? gDssConfigPipelineParams.numTestPipes : DSS_DISP_INST_MAX;

    for(instCnt = 0; instCnt < CONFIG_DSS_NUM_FRAMES_PER_PIPELINE; instCnt++)
    {
        firstPipeFrameBufferPointer[instCnt] = &gDssFirstPipelineFrameBuf[instCnt];
        secondPipeFrameBufferPointer[instCnt] = &gDssSecondPipelineFrameBuf[instCnt];
    }

    for(instCnt = 0U; instCnt< numPipes ; instCnt++)
    {
        if(instCnt == 0)
        {
            Disp_prepareFrameBuffer(instCnt,
                                    gDssConfigPipelineParams.inDataFmt[instCnt],
                                    gDssConfigPipelineParams.inWidth[instCnt],
                                    gDssConfigPipelineParams.inHeight[instCnt],
                                    gDssConfigPipelineParams.pitch[instCnt][0],
                                    firstPipeFrameBufferPointer);
        }
        else
        {
            Disp_prepareFrameBuffer(instCnt,
                                    gDssConfigPipelineParams.inDataFmt[instCnt],
                                    gDssConfigPipelineParams.inWidth[instCnt],
                                    gDssConfigPipelineParams.inHeight[instCnt],
                                    gDssConfigPipelineParams.pitch[instCnt][0],
                                    secondPipeFrameBufferPointer);
        }
    }

}

int32_t TestDisp_dynamicDisplayControl(Dss_Object *appObj)
{
    int32_t retVal = FVID2_SOK;
    int32_t status = SystemP_SUCCESS;

    /* Initialise frames */
    TestDisp_dssInitFrames();

    status = TestDisp_init(appObj);

    if(status == SystemP_SUCCESS)
    {
        retVal = TestDisp_runTest(appObj);

        retVal += TestDisp_deInit(appObj);

        if(FVID2_SOK != retVal)
        {
            status = SystemP_FAILURE;
        }
    }

    return status;
}

static int32_t TestDisp_init(Dss_Object *appObj)
{
    int32_t         retVal = FVID2_SOK;
    int32_t         status = SystemP_SUCCESS;
    Fvid2_InitPrms  initPrms;

    Fvid2InitPrms_init(&initPrms);
    retVal = Fvid2_init(&initPrms);
    if(retVal != FVID2_SOK)
    {
        status = SystemP_FAILURE;
        DebugP_log("Fvid2 Init failed!!!\r\n");
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
            status  = SystemP_FAILURE;
            DebugP_log("DCTRL Create failed!!!\r\n");
        }
    }

    if(appObj->oldiParams != NULL)
    {
        /* Negative test case to set OLDI Power Domain Control to power off OLDI TX */
        Dss_setOLDITxPowerDown(appObj->oldiParams->oldiCfg.oldiMapType, FALSE);

        Dss_setOLDITxPowerDown(appObj->oldiParams->oldiCfg.oldiMapType, TRUE);
    }

    return status;
}

static int32_t TestDisp_deInit(Dss_Object *appObj)
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

    return retVal;
}

static int32_t TestDisp_runTest(Dss_Object *appObj)
{
    int32_t retVal = FVID2_SOK;
    uint32_t instCnt = 0U;
    volatile uint32_t loopCount = 0U;
    Dss_InstObject *instObj;
    Fvid2_FrameList  frmList;

    /* Create driver */
    retVal = TestDisp_create(appObj);

    if(retVal == FVID2_SOK)
    {
        /* Start driver */
        for(instCnt=0U; instCnt<gDssConfigPipelineParams.numTestPipes; instCnt++)
        {
            instObj = &appObj->instObj[instCnt];

            retVal = Fvid2_start(instObj->drvHandle, NULL);
            if(retVal != FVID2_SOK)
            {
                DebugP_log("Display Start failed!!!\r\n");
                break;
            }
        }
    }

    if(retVal == FVID2_SOK)
    {
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

        	    /* Disable the FVID2 asserts */
        	    Fvid2Utils_controlAssert(false);
                retVal = Fvid2_dequeue(instObj->drvHandle,
                                    NULL,
                                    0U,
                                    FVID2_TIMEOUT_NONE);
                DebugP_assert(retVal!= FVID2_SOK);

        	    /* Enable back the FVID2 asserts */
        	    Fvid2Utils_controlAssert(true);
 
                if(FVID2_SOK == retVal)
                {
                    retVal = Fvid2_queue(instObj->drvHandle, &frmList, 0U);
                    if(FVID2_SOK != retVal)
                    {
                        DebugP_log("Display Queue failed!!!\r\n");
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
                    DebugP_log("Display Dequeue failed!!!\r\n");
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
                DebugP_log("Display Stop failed!!!\r\n");
                break;
            }
        }

    }

    if(FVID2_SOK == retVal)
    {
        /* Delete driver */
        TestDisp_delete(appObj);
    }

    return retVal;
}

static void TestDisp_initDssParams(Dss_Object *appObj)
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

static int32_t TestDisp_create(Dss_Object *appObj)
{
    int32_t retVal = FVID2_SOK;
    int32_t status = SystemP_SUCCESS;
    uint32_t instCnt = 0U;
    Dss_InstObject *instObj;

    /* Init VP, Overlay and Panel params */
    TestDisp_initDssParams(appObj);

    /* Configure DSS pipeline params */
    TestDisp_initPipelineParams(appObj);

    /* Config IOCTL for VP, Overlay and Panel */
    retVal = TestDisp_configDctrl(appObj);

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
                NULL,
                &instObj->cbParams);

            DebugP_assert(instObj->drvHandle == NULL);

            instObj->drvHandle = Fvid2_create(
                DSS_DISP_DRV_ID,
                instObj->instId+100,
                &instObj->createParams,
                &instObj->createStatus,
                &instObj->cbParams);

            DebugP_assert(instObj->drvHandle == NULL);

            instObj->drvHandle = Fvid2_create(
                DSS_DISP_DRV_ID,
                instObj->instId,
                &instObj->createParams,
                &instObj->createStatus,
                &instObj->cbParams);

            if((NULL == instObj->drvHandle) ||
            (instObj->createStatus.retVal != FVID2_SOK))
            {
                DebugP_log("Display Create failed!!!\r\n");
                retVal = instObj->createStatus.retVal;
            }

            if(FVID2_SOK == retVal)
            {
                Dss_DispDrvInstObj *instDrvObj = (Dss_DispDrvInstObj *) instObj->drvHandle;
                uint32_t outWidth = instObj->dispParams.pipeCfg.outWidth;
                uint32_t scanFormat = instObj->dispParams.pipeCfg.inFmt.scanFormat;

                instObj->dispParams.pipeCfg.outWidth = instDrvObj->dispWidth + 1;
                instObj->dispParams.pipeCfg.inFmt.scanFormat = instDrvObj->dispScanFormat + 1;

                retVal = Fvid2_control(
                    instObj->drvHandle,
                    IOCTL_DSS_DISP_SET_DSS_PARAMS,
                    NULL,
                    NULL);
                    DebugP_assert(retVal != FVID2_SOK);

                retVal = Fvid2_control(
                    instObj->drvHandle,
                    IOCTL_DSS_DISP_SET_DSS_PARAMS,
                    &instObj->dispParams,
                    NULL);
                DebugP_assert(retVal != FVID2_SOK);

                instObj->dispParams.pipeCfg.outWidth = outWidth;
                instObj->dispParams.pipeCfg.inFmt.scanFormat = instDrvObj->dispScanFormat;
                instObj->dispParams.pipeCfg.inFmt.scanFormat = scanFormat;
                instDrvObj->dispScanFormat = scanFormat;

                retVal = Fvid2_control(
                    instObj->drvHandle,
                    IOCTL_DSS_DISP_SET_DSS_PARAMS,
                    &instObj->dispParams,
                    NULL);
                if(retVal != FVID2_SOK)
                {
                    DebugP_log("DSS Set Params IOCTL failed!!!\r\n");
                }
            }
            if(FVID2_SOK == retVal)
            {
                retVal = Fvid2_control(
                            instObj->drvHandle,
                            IOCTL_DSS_DISP_SET_PIPE_MFLAG_PARAMS,
                            NULL,
                            NULL);

                retVal = Fvid2_control(
                    instObj->drvHandle,
                    IOCTL_DSS_DISP_SET_PIPE_MFLAG_PARAMS,
                    &instObj->mflagParams,
                    NULL);
                if(retVal != FVID2_SOK)
                {
                    DebugP_log("DSS Set Mflag Params IOCTL failed!!!\r\n");
                }
            }

            if(FVID2_SOK == retVal)
            {
                retVal = TestDisp_allocAndQueueFrames(appObj, instObj);
                if(retVal != FVID2_SOK)
                {
                    DebugP_log("Display Alloc and Queue failed!!!\r\n");
                }
            }

            if(FVID2_SOK != retVal)
            {
                break;
            }
        }
    }

    return retVal;
}

static void TestDisp_delete(Dss_Object *appObj)
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

        /* Disable the FVID2 asserts */
        Fvid2Utils_controlAssert(false);

        retVal = Fvid2_control(
            instObj->drvHandle,
            IOCTL_DSS_DISP_GET_CURRENT_STATUS,
            NULL,
            NULL);

        /* Enable back the FVID2 asserts */
        Fvid2Utils_controlAssert(true);

        /* Check for DSS underflow errors */
        retVal = Fvid2_control(
            instObj->drvHandle,
            IOCTL_DSS_DISP_GET_CURRENT_STATUS,
            &currStatus,
            NULL);
        if(FVID2_SOK != retVal)
        {
            DebugP_log("Display get stats failed!!!\r\n");
        }

        /* Print Synclost errors */
        if(0U != currStatus.underflowCount)
        {
            GT_2trace(DssTrace, GT_ERR, "No of Underflows for Inst %d: %d\r\n", instCnt, currStatus.underflowCount);
        }
        else
        {
            DebugP_log("Pipeline Instance %d: Underflow did not occur\r\n", gDssConfigPipelineParams.instId[instCnt]);
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
            DebugP_log("Display Delete failed!!!\r\n");
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
        DebugP_log("VP get stats failed!!!\r\n");
    }

    /* Print Synclost errors */
    if(0U != pErrorStats->syncLost)
    {
        GT_1trace(DssTrace, GT_ERR, "No of Sync Lost: %d\r\n", pErrorStats->syncLost);
    }
    else
    {
        DebugP_log("VP Instance %d: Sync Lost did not occur\r\n", gDssVpParams.vpId);
    }

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_CLEAR_PATH,
        appObj->dctrlPathInfo,
        NULL);
    if(FVID2_SOK != retVal)
    {
        DebugP_log("Clear Path failed!!!\r\n");
    }

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_STOP_VP,
        vpParams,
        NULL);

    if(FVID2_SOK != retVal)
    {
        DebugP_log("VP Stop failed!!!\r\n");
    }

    return;
}

static int32_t TestDisp_allocAndQueueFrames(const Dss_Object *appObj,
                                           Dss_InstObject *instObj)
{
    int32_t  retVal = FVID2_SOK;
    uint32_t frmId, numFrames;
    Fvid2_Frame *frm;
    Fvid2_FrameList frmList;
    Dss_DispDrvInstObj *drvObj;
    uint32_t restoreState;

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
            if(instObj->dispParams.pipeCfg.inFmt.dataFormat == FVID2_DF_YUV420SP_UV)
            {
                frm[frmId].addr[1U] = (uint64_t)firstPipeFrameBufferPointer[frmId] +
                                        instObj->dispParams.pipeCfg.inFmt.width * \
                                        instObj->dispParams.pipeCfg.inFmt.height;
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
            if(instObj->dispParams.pipeCfg.inFmt.dataFormat == FVID2_DF_YUV420SP_UV)
            {
                frm[frmId].addr[1U] = (uint64_t)secondPipeFrameBufferPointer[frmId] +
                                        instObj->dispParams.pipeCfg.inFmt.width * \
                                        instObj->dispParams.pipeCfg.inFmt.height;
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
        /* Disable the FVID2 asserts */
        Fvid2Utils_controlAssert(false);

        retVal = Fvid2_queue(instObj->drvHandle, NULL, 0U);
        frmList.numFrames = (FVID2_MAX_FRAME_PTR + 1U);
        retVal = Fvid2_queue(instObj->drvHandle, &frmList, 0U);
        frmList.numFrames = 1U;
        drvObj = (Dss_DispDrvInstObj *) ((uint8_t *)instObj->drvHandle - 0x3d2c);
        restoreState = drvObj->drvState.isOpened;
        drvObj->drvState.isOpened = FALSE;
        retVal = Fvid2_queue(instObj->drvHandle, &frmList, 0U);

        /* Enable back the FVID2 asserts */
        Fvid2Utils_controlAssert(true);

        drvObj->drvState.isOpened = restoreState;
        frmList.frames[0U] = &frm[frmId];
        retVal = Fvid2_queue(instObj->drvHandle, &frmList, 0U);
        if(FVID2_SOK != retVal)
        {
            DebugP_log("Display Queue failed!!!\r\n");
            break;
        }
    }

    return (retVal);
}

static void TestDisp_initPipelineParams(Dss_Object *appObj)
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

        instObj->cbParams.cbFxn = &TestDisp_pipeCbFxn;
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

static int32_t TestDisp_configDctrl(Dss_Object *appObj)
{
    int32_t retVal = FVID2_SOK;
    Dss_DispDrvCommonObj *pObj;
    pObj = &gDss_DispDrvCommonObj;
    Fvid2_FrameList  frmList;

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
        DebugP_log("Dctrl Set Path IOCTL failed!!!\r\n");
        return (retVal);
    }

    if(gStopVpTest == 0U)
    {
        retVal = Fvid2_control(
            appObj->dctrlHandle,
            IOCTL_DSS_DCTRL_SET_ADV_VP_PARAMS,
            advVpParams,
            NULL);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("DCTRL Set Advance VP Params IOCTL failed!!!\r\n");
        }

        retVal = Fvid2_control(
            appObj->dctrlHandle,
            IOCTL_DSS_DCTRL_SET_VP_PARAMS,
            vpParams,
            NULL);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("Dctrl Set VP Params IOCTL failed!!!\r\n");
        }
    }

    if (appObj->oldiParams != NULL)
    {
        retVal = Fvid2_control(
            appObj->dctrlHandle,
            IOCTL_DSS_DCTRL_SET_OLDI_PARAMS,
            oldiParams,
            NULL);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("DCTRL Set OLDI Params IOCTL failed!!!\r\n");
        }
    }

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_SET_OVERLAY_PARAMS,
        overlayParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Set Overlay Params IOCTL failed!!!\r\n");
    }

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_SET_LAYER_PARAMS,
        layerParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Set Layer Params IOCTL failed!!!\r\n");
    }

    /* Disable the FVID2 asserts */
    Fvid2Utils_controlAssert(false);

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_SET_VP_CSC_COEFF,
        advVpParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Set VP CSC Params IOCTL failed!!!\r\n");
    }

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_SET_LCD_BLANK_TIMING_PARAMS,
        advVpParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Set LCD Timing Params IOCTL failed!!!\r\n");
    }

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_REGISTER_SYNCLOST_CB,
        overlayParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Register Synclost IOCTL failed!!!\r\n");
    }

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_REGISTER_LINENUM_CB,
        overlayParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Register LineNum IOCTL failed!!!\r\n");
    }

    /* Enable back the FVID2 asserts */
    Fvid2Utils_controlAssert(true);

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_SET_GLOBAL_DSS_PARAMS,
        globalDssParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Set Global DSS Params IOCTL failed!!!\r\n");
    }

    /* Disable the FVID2 asserts */
    Fvid2Utils_controlAssert(false);

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_SET_VP_SAFETY_CHK_PARAMS,
        globalDssParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Set VP safety chk Params IOCTL failed!!!\r\n");
    }

    advVpParams->vpId = CSL_DSS_VP_ID_MAX;
    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_SET_LCD_BLANK_TIMING_PARAMS,
        advVpParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Set LCD Timing Params IOCTL failed!!!\r\n");
    }

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        (DSS_DCTRL_IOCTL_BASE + 0x00U),
        advVpParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL INVALID Params failed!!!\r\n");
    }

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_STOP_VP,
        advVpParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Stop VP failed!!!\r\n");
    }
    advVpParams->vpId = gDssAdvVpParams.vpId;

    overlayParams->overlayId = CSL_DSS_VP_ID_MAX;
    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_REGISTER_SYNCLOST_CB,
        overlayParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Register Synclost IOCTL failed!!!\r\n");
    }

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_REGISTER_LINENUM_CB,
        overlayParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Register LineNum IOCTL failed!!!\r\n");
    }
    overlayParams->overlayId =  gDssOverlayParams.overlayId;

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_SET_VP_CSC_COEFF,
        advVpParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Set VP CSC Params IOCTL failed!!!\r\n");
    }

    retVal = Fvid2_queue(
        appObj->dctrlHandle,
        &frmList,
        0U);

    if(FVID2_SOK != retVal)
    {
        DebugP_log("Display Queue Failed!!!\r\n");
    }

    retVal = Fvid2_dequeue(
        appObj->dctrlHandle,
        &frmList, 0,
        0U);
    if(FVID2_SOK != retVal)
    {
        DebugP_log("Display Dequeue Failed!!!\r\n");
    }

    retVal = Fvid2_queue(
        appObj->dctrlHandle,
        &frmList,
        0U);
    if(FVID2_SOK != retVal)
    {
        DebugP_log("Display Queue Failed!!!\r\n");
    }

    retVal = Dss_evtMgrEnable(pObj->instObj->evtGroupHandle[0]);

    retVal = Dss_evtMgrDisable(pObj->instObj->evtGroupHandle[0]);

    /* Enable back the FVID2 asserts */
    Fvid2Utils_controlAssert(true);
    return (retVal);
}

static int32_t TestDisp_pipeCbFxn(Fvid2_Handle handle, void *appData)
{
    int32_t retVal  = FVID2_SOK;
    Dss_InstObject *instObj = (Dss_InstObject *) appData;

    GT_assert (DssTrace, (NULL != instObj));
    (void) SemaphoreP_post(&instObj->syncSem);

    return (retVal);
}

#if defined (SOC_AM62PX)
static int32_t TestDisp_createError(Dss_Object *appObj, uint32_t testId)
{
    int32_t retVal = FVID2_SOK;
    int32_t status = SystemP_SUCCESS;
    uint32_t instCnt = 0U;
    Dss_InstObject *instObj;
	Dss_DctrlVpSafetyChkParams safetyCheckParams;
    /* Init VP, Overlay and Panel params */
    TestDisp_initDssParams(appObj);

    /* Configure DSS pipeline params */
    TestDisp_initPipelineParams(appObj);
    /* Config IOCTL for VP, Overlay and Panel */

    if(testId == TEST_DSS_IOCTL_DCTRL_SET_INVALID_VP_ID)
    {
        appObj->vpParams.vpId = CSL_DSS_VP_ID_MAX;
    }
    else if(testId == TEST_DSS_IOCTL_DCTRL_SET_INVALID_OLY_ID)
    {
        appObj->overlayParams.overlayId = CSL_DSS_OVERLAY_ID_MAX;
    }
    else if(testId == TEST_DSS_IOCTL_DCTRL_SET_INVALID_LAYER_PARAMS)
    {
        appObj->layerParams.overlayId = CSL_DSS_OVERLAY_ID_MAX;
    }
    else if(testId == TEST_DSS_IOCTL_DCTRL_SET_INVALID_OLY_LAYER_NUM)
    {
        appObj->layerParams.pipeLayerNum[0] = CSL_DSS_OVERLAY_LAYER_INVALID;
    }
    else if(testId == TEST_DSS_IOCTL_DCTRL_SET_INVALID_ADV_VP_ID)
    {
        appObj->advVpParams.vpId = CSL_DSS_VP_ID_MAX;
    }
    retVal = TestDisp_configDctrl(appObj);

    if(testId == TEST_DSS_IOCTL_DCTRL_INVALID_SAFETY_CHK_PRMS)
    {
        memset(&safetyCheckParams, 0, sizeof(safetyCheckParams));
        safetyCheckParams.vpId = CSL_DSS_VP_ID_MAX;
        retVal = Fvid2_control(
            appObj->dctrlHandle,
            IOCTL_DSS_DCTRL_SET_VP_SAFETY_CHK_PARAMS,
            &safetyCheckParams,
            NULL);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("DCTRL Set Safety check params IOCTL failed!!!\r\n");
        }
    }

    if(testId == TEST_DSS_IOCTL_DCTRL_SET_INVALID_OLY_LAYER_NUM)
    {
        return SystemP_FAILURE;
    }

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
            if(testId == TEST_DSS_DISP_VSYNC_ENABLE)
            {
                instObj->createParams.progPipeVsyncEnable = TRUE;
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
                retVal = instObj->createStatus.retVal;
            }

            if(FVID2_SOK == retVal)
            {
            Fvid2Utils_controlAssert(false);
                retVal = Fvid2_control(
                    instObj->drvHandle,
                    IOCTL_DSS_DISP_SET_DSS_PARAMS,
                    &instObj->dispParams,
                    NULL);
                if(retVal != FVID2_SOK)
                {
                    DebugP_log("DSS Set Params IOCTL failed!!!\r\n");
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
                    DebugP_log("DSS Set Mflag Params IOCTL failed!!!\r\n");
                }
            }

            if(FVID2_SOK == retVal)
            {
                retVal = TestDisp_allocAndQueueFrames(appObj, instObj);
                if(retVal != FVID2_SOK)
                {
                    DebugP_log("Display Alloc and Queue failed!!!\r\n");
                }
            }

            if(FVID2_SOK != retVal)
            {
                break;
            }
        }
    }

    return retVal;
}

static int32_t TestDisp_runIoctlTest(Dss_Object *appObj, uint32_t testId)
{
    int32_t retVal = FVID2_SOK;
    uint32_t instCnt = 0U;
    volatile uint32_t loopCount = 0U;
    Dss_InstObject *instObj;
    Fvid2_FrameList  frmList;

    /* Create driver */
    retVal = TestDisp_create(appObj);
    if((retVal == FVID2_SOK) && (testId == TEST_DSS_IOCTL_DCTRL_LINENUM_CB) )
    {
        retVal = testLineCBIoctl(appObj);
    }

    if((retVal == FVID2_SOK) && (testId == TEST_DSS_IOCTL_DCTRL_SYNCLOST_CB) )
    {
        retVal = testSyncLostCBIoctl(appObj);
    }

    if((retVal == FVID2_SOK) && (testId == TEST_DSS_IOCTL_DCTRL_INVALID_IOCTL))
    {
        retVal = testInvalidIoctSetup(appObj);
    }

    if(testId == TEST_DSS_IOCTL_DCTRL_STOP_VP)
    {
        retVal = testStopVpIoctl(appObj);
    }

    if(retVal == FVID2_SOK)
    {
        /* Start driver */
        for(instCnt=0U; instCnt<gDssConfigPipelineParams.numTestPipes; instCnt++)
        {
            instObj = &appObj->instObj[instCnt];

            retVal = Fvid2_start(instObj->drvHandle, NULL);
            if(retVal != FVID2_SOK)
            {
                DebugP_log("Display Start failed!!!\r\n");
                break;
            }
        }
    }

    if(retVal == FVID2_SOK)
    {
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
                        DebugP_log("Display Queue failed!!!\r\n");
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
                    DebugP_log("Display Dequeue failed!!!\r\n");
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
                DebugP_log("Display Stop failed!!!\r\n");
                break;
            }
        }

    }

    if(testId == TEST_DSS_IOCTL_DCTRL_INVALID_VP_ERR_STATS)
    {
        retVal = testVPErrStatsIoctls(appObj);
        return retVal;
    }
    if(FVID2_SOK == retVal)
    {
        /* Delete driver */
        TestDisp_delete(appObj);
    }

    return retVal;
}

static int32_t TestDisp_Error(Dss_Object *appObj, uint32_t testId)
{
    int32_t retVal = FVID2_SOK;
    uint32_t instCnt = 0U;
    volatile uint32_t loopCount = 0U;
    Dss_InstObject *instObj;
    Fvid2_FrameList  frmList;

    Dss_DctrlVpParams *vpParams;
    vpParams = &appObj->vpParams;

    /* Create driver */
    if(testId == TEST_DSS_IOCTL_DCTRL_SET_INVALID_VP_ID          || testId == TEST_DSS_IOCTL_DCTRL_SET_INVALID_OLY_ID
    || testId == TEST_DSS_IOCTL_DCTRL_SET_INVALID_LAYER_PARAMS   || testId == TEST_DSS_IOCTL_DCTRL_SET_INVALID_OLY_LAYER_NUM
    || testId == TEST_DSS_IOCTL_DCTRL_SET_INVALID_ADV_VP_ID      || testId == TEST_DSS_IOCTL_DCTRL_INVALID_SAFETY_CHK_PRMS
    || testId == TEST_DSS_DISP_VSYNC_ENABLE)
    {
        /* Disable the FVID2 asserts */
        Fvid2Utils_controlAssert(false);

        retVal = TestDisp_createError(appObj, testId);
    }
    else
    {
        retVal = TestDisp_create(appObj);
    }

    if(retVal == FVID2_SOK)
    {
        /* Start driver */
        instObj = &appObj->instObj[instCnt];
        retVal = Fvid2_start(instObj->drvHandle, NULL);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("Display Start failed!!!\r\n\n");
        }
    }

    if(retVal == FVID2_SOK)
    {
        while(loopCount++ < DISP_NUM_FRAMES_COUNT)
        {
            for(instCnt=0U; instCnt<gDssConfigPipelineParams.numTestPipes; instCnt++)
            {
                instObj = &appObj->instObj[instCnt];
                DebugP_log("Dequeue pipe%d/%d!!!\r\n\n",instCnt+1,gDssConfigPipelineParams.numTestPipes);
                retVal = Fvid2_dequeue(instObj->drvHandle,
                                    &frmList,
                                    0U,
                                    FVID2_TIMEOUT_NONE);

                if(FVID2_SOK == retVal)
                {
                    retVal = Fvid2_queue(instObj->drvHandle, &frmList, 0U);
                    if(FVID2_SOK != retVal)
                    {
                        DebugP_log("Display Queue failed!!!\r\n");
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
                    DebugP_log("Display Dequeue failed!!!\r\n");
                    break;
                }
            }
        }
        if(testId == TEST_DSS_IOCTL_DCTRL_CONFIG_IN_USE_VP)
        {
            retVal = Fvid2_control(
                        appObj->dctrlHandle,
                        IOCTL_DSS_DCTRL_SET_VP_PARAMS,
                        vpParams,
                        NULL);
        }
        if(retVal != FVID2_SOK)
        {
            DebugP_log("Dctrl Set VP Params IOCTL failed!!!\r\n");
        }

        if (testId != TEST_DSS_IOCTL_DCTRL_SET_INVALID_ADV_VP_ID)
        {
            for(instCnt=0U; instCnt<gDssConfigPipelineParams.numTestPipes; instCnt++)
            {
                instObj = &appObj->instObj[instCnt];
                retVal  = Fvid2_stop(instObj->drvHandle, NULL);
                if(retVal != FVID2_SOK)
                {
                    DebugP_log("Display Stop failed!!!\r\n");
                    break;
                }
            }
        }
    }

    if(FVID2_SOK == retVal && (testId != TEST_DSS_IOCTL_DCTRL_SET_INVALID_ADV_VP_ID))
    {
        /* Delete driver */
        TestDisp_delete(appObj);
    }

    return retVal;
}

int32_t TestDisp_reregisterDriver(Dss_Object *appObj)
{
    int32_t status = SystemP_SUCCESS;

    /* Initialise frames */
    TestDisp_dssInitFrames();

    status = TestDisp_init(appObj);
    DebugP_log("Return value:%d\n\r",status);

    status = TestDisp_init(appObj);
    DebugP_log("Return value:%d\n\r",status);

    return status;
}

int32_t TestDisp_createDriver(Dss_Object *appObj)
{
    int32_t status = SystemP_SUCCESS;
    Fvid2_InitPrms  initPrms;
    int32_t retVal;

    /* Initialise frames */
    TestDisp_dssInitFrames();

    Fvid2InitPrms_init(&initPrms);
    retVal = Fvid2_init(&initPrms);
    if(retVal != FVID2_SOK)
    {
         status = SystemP_FAILURE;
    }

    Dss_initParamsInit(&appObj->initParams);
    Dss_init(&appObj->initParams);

    if (retVal == FVID2_SOK)
    {
        Fvid2_CbParams dummyParams;

        /* Create DCTRL handle, used for common driver configuration */
        appObj->dctrlHandle = Fvid2_create(
              DSS_DCTRL_DRV_ID,
              DSS_DCTRL_INST_0,
              NULL,
              NULL,
              NULL);
          if(NULL == appObj->dctrlHandle)
          {
              status  = SystemP_FAILURE;
          }
          /*Create DCTRL handle with all bad arguments */
         appObj->dctrlHandle = Fvid2_create(
             DSS_DCTRL_DRV_ID+1,
             DSS_DCTRL_INST_0,
             &retVal,
             &retVal,
             &dummyParams);
    }

    return status;
}

int32_t TestDisp_unusedIoctl(Dss_Object *appObj)
{
    int32_t retVal = FVID2_SOK;
    int32_t status = SystemP_SUCCESS;

    Dss_InstObject *instObj;
    Dss_DispDrvInstObj *drvObj;
    uint32_t restoreParams;
    CSL_DssCscCoeff  DssCscCoeff;

    /* Initialise frames */
    TestDisp_dssInitFrames();

    status = TestDisp_init(appObj);

    if(status == SystemP_SUCCESS)
    {
        /* Init VP, Overlay and Panel params */
        TestDisp_initDssParams(appObj);

        /* Configure DSS pipeline params */
        TestDisp_initPipelineParams(appObj);

        /* Config IOCTL for VP, Overlay and Panel */
        retVal = TestDisp_configDctrl(appObj);

        if(retVal == FVID2_SOK)
        {
            uint32_t instCnt = 0U;
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
                    retVal = instObj->createStatus.retVal;
                }

                if(FVID2_SOK == retVal)
                {
                    drvObj = (Dss_DispDrvInstObj *)((uint8_t *)instObj->drvHandle - 0x3d2c);
                    retVal = Fvid2_control(
                                instObj->drvHandle,
                                IOCTL_DSS_DISP_SET_PIPE_CSC_COEFF,
                                NULL,
                                NULL);

                    restoreParams = drvObj->pipeParams[0].pipeCfg.cscRange;
                    drvObj->pipeParams[0].pipeCfg.cscRange = CSL_DSS_CSC_RANGE_CUSTOM;

                    retVal = Fvid2_control(
                                instObj->drvHandle,
                                IOCTL_DSS_DISP_SET_PIPE_CSC_COEFF,
                                &instObj->dispParams,
                                &DssCscCoeff);
                    drvObj->pipeParams[0].pipeCfg.cscRange = restoreParams;

                    retVal = Fvid2_control(
                                instObj->drvHandle,
                                IOCTL_DSS_DISP_SET_PIPE_CSC_COEFF,
                                &instObj->dispParams,
                                NULL);
                    if(retVal != FVID2_SOK)
                    {
                        DebugP_log("DSS Set Pipe CSC coeff IOCTL failed!!!\r\n");
                    }
                }

                if(FVID2_SOK == retVal)
                {
                    retVal = Fvid2_control(
                        instObj->drvHandle,
                        IOCTL_DSS_DISP_REGISTER_BUF_PRGM_CB,
                        NULL,
                        NULL);
                    drvObj->drvState.isStarted = TRUE;
                    retVal = Fvid2_control(
                        instObj->drvHandle,
                        IOCTL_DSS_DISP_REGISTER_BUF_PRGM_CB,
                        &instObj->dispParams,
                        NULL);
                    drvObj->drvState.isStarted = FALSE;
                    retVal = Fvid2_control(
                        instObj->drvHandle,
                        IOCTL_DSS_DISP_REGISTER_BUF_PRGM_CB,
                        &instObj->dispParams,
                        NULL);

                    if(retVal != FVID2_SOK)
                    {
                        DebugP_log("DSS disp register buf prgm failed!!!\r\n");
                    }
                }

                if(FVID2_SOK == retVal)
                {
                    retVal = Fvid2_control(
                        instObj->drvHandle,
                        IOCTL_DSS_DISP_REGISTER_PIPE_PRGM_CB,
                        NULL,
                        NULL);

                    drvObj->drvState.isStarted = TRUE;
                    retVal = Fvid2_control(
                        instObj->drvHandle,
                        IOCTL_DSS_DISP_REGISTER_PIPE_PRGM_CB,
                        &instObj->dispParams,
                        NULL);
                    drvObj->drvState.isStarted = FALSE;

                    retVal = Fvid2_control(
                        instObj->drvHandle,
                        IOCTL_DSS_DISP_REGISTER_PIPE_PRGM_CB,
                        &instObj->dispParams,
                        NULL);

                    if(retVal != FVID2_SOK)
                    {
                        DebugP_log("DSS disp register pipe prgm failed!!!\r\n");
                    }
                }

                if(FVID2_SOK == retVal)
                {
                    drvObj = (Dss_DispDrvInstObj *) ((uint8_t *)instObj->drvHandle - 0x3d2c);
                    retVal = Fvid2_control(
                        instObj->drvHandle,
                        IOCTL_DSS_DISP_REGISTER_PIPE_UNDERFLOW_CB,
                        NULL,
                        NULL);

                drvObj->drvState.isStarted = TRUE;
                    retVal = Fvid2_control(
                        instObj->drvHandle,
                        IOCTL_DSS_DISP_REGISTER_PIPE_UNDERFLOW_CB,
                        &instObj->dispParams,
                        NULL);

                drvObj->drvState.isStarted = FALSE;

                    retVal = Fvid2_control(
                        instObj->drvHandle,
                        IOCTL_DSS_DISP_REGISTER_PIPE_UNDERFLOW_CB,
                        &instObj->dispParams,
                        NULL);

                    if(retVal != FVID2_SOK)
                    {
                        DebugP_log("DSS disp register pipe undeflow cb failed!!!\r\n");
                    }
                }

                if(FVID2_SOK == retVal)
                {
                    retVal = Fvid2_control(
                        instObj->drvHandle,
                        -1,
                        &instObj->dispParams,
                        NULL);
                    if(retVal != FVID2_SOK)
                    {
                        DebugP_log("DSS disp default case!!!\r\n");
                    }
                    else
                    {
                        DebugP_log("Dss disp dafult case failed!!!\r\n");
                    }
                }

                if(FVID2_SOK == retVal)
                {
                    retVal = TestDisp_allocAndQueueFrames(appObj, instObj);
                    if(retVal != FVID2_SOK)
                    {
                        DebugP_log("Display Alloc and Queue failed!!!\r\n");
                    }
                    else
                    {
                    DebugP_log("Display Alloc and Queue passed\r\n");
                    }
                }

                if(FVID2_SOK != retVal)
                {
                    break;
                }
            }
        }

        if(FVID2_SOK != retVal)
        {
            status = SystemP_FAILURE;
        }
    }
    if(FVID2_SOK == retVal)
    {
        /* Delete driver */
        TestDisp_delete(appObj);
    }

    retVal += TestDisp_deInit(appObj);
    if (retVal != FVID2_SOK)
    {
        status = SystemP_FAILURE;
    }

    return status;
}

int32_t TestDisp_dctrlIoctls(Dss_Object *appObj, uint32_t testId)
{
    int32_t retVal = FVID2_SOK;
    int32_t status = SystemP_SUCCESS;

    if(testId == TEST_DSS_IOCTL_DCTRL_STOP_VP)
    {
        gStopVpTest = 1U;
    }
    else
    {
        gStopVpTest = 0U;
    }

    /* Initialise frames */
    TestDisp_dssInitFrames();

    status = TestDisp_init(appObj);

    if(status == SystemP_SUCCESS)
    {
        retVal = TestDisp_runIoctlTest(appObj, testId);

        if(testId == TEST_DSS_IOCTL_DCTRL_DEINIT_ERR)
        {
            retVal = Dss_deInit();
        }
        retVal += TestDisp_deInit(appObj);

        if(FVID2_SOK != retVal)
        {
            status = SystemP_FAILURE;
        }
    }

    return status;
}

int32_t TestDisp_initParams(Dss_Object *appObj)
{
    int32_t retVal = FVID2_SOK;
    int32_t status = SystemP_SUCCESS;
    Dss_DctrlDrvInitParams dctrlInitParams;
    Fvid2_InitPrms  initPrms;

    DebugP_assert(appObj != NULL);

    /* Initialise frames */
    TestDisp_dssInitFrames();
    status = TestDisp_init(appObj);
    DebugP_assert(status == SystemP_SUCCESS);
    Fvid2InitPrms_init(&initPrms);

    retVal = Fvid2_init(&initPrms);
    if(retVal != FVID2_SOK)
    {
        status = SystemP_FAILURE;
    }

    dctrlInitParams.drvInstId = DSS_DCTRL_INST_0;
    dctrlInitParams.availablePortId[0] = CSL_DSS_VP_ID_MAX + 1;
    dctrlInitParams.numAvailablePorts = 1;
    status = Dss_dctrlDrvInit(&dctrlInitParams);
    return status;
}

int32_t TestDisp_ioctlErrors(Dss_Object *appObj, uint32_t testId)
{
    int32_t retVal = FVID2_SOK;
    int32_t status = SystemP_SUCCESS;
    uint32_t testNumEdges;
    Dss_DctrlPathInfo *testPathInfo;

    if(testId == TEST_DSS_IOCTL_DCTRL_SET_INVALID_PATH_INFO || testId == TEST_DSS_IOCTL_DCTRL_SET_ZERO_PATH_EDGES)
    {
        if(testId == TEST_DSS_IOCTL_DCTRL_SET_INVALID_PATH_INFO)
        {
            testPathInfo = appObj->dctrlPathInfo;
        }
        else
        {
            testNumEdges = appObj->dctrlPathInfo->numEdges;
        }

        /* Initialise frames */
        TestDisp_dssInitFrames();

        status = TestDisp_init(appObj);
        if(testId == TEST_DSS_IOCTL_DCTRL_SET_INVALID_PATH_INFO)
        {
            appObj->dctrlPathInfo = &gfaultyDssPathInfo;
        }
        else
        {
            appObj->dctrlPathInfo->numEdges = 0;
        }

        if(status == SystemP_SUCCESS)
        {
            retVal = TestDisp_runTest(appObj);

            retVal += TestDisp_deInit(appObj);

            if(FVID2_SOK != retVal)
            {
                status = SystemP_FAILURE;
            }
        }

        if(testId == TEST_DSS_IOCTL_DCTRL_SET_INVALID_PATH_INFO)
        {
            appObj->dctrlPathInfo = testPathInfo;
        }
        else
        {
            appObj->dctrlPathInfo->numEdges = testNumEdges;
        }

        /* It should return failure */
        if(status == SystemP_SUCCESS)
        {
            return status;
        }
    }
    else if(testId == TEST_DSS_IOCTL_DCTRL_SET_INVALID_VP_ID         || testId == TEST_DSS_IOCTL_DCTRL_CONFIG_IN_USE_VP
        ||  testId == TEST_DSS_IOCTL_DCTRL_SET_INVALID_OLY_ID        || testId == TEST_DSS_IOCTL_DCTRL_SET_INVALID_LAYER_PARAMS
        ||  testId == TEST_DSS_IOCTL_DCTRL_SET_INVALID_OLY_LAYER_NUM || testId == TEST_DSS_IOCTL_DCTRL_SET_INVALID_ADV_VP_ID
        ||  testId == TEST_DSS_IOCTL_DCTRL_INVALID_SAFETY_CHK_PRMS   || testId == TEST_DSS_DISP_VSYNC_ENABLE)
    {
        /* Initialise frames */
        TestDisp_dssInitFrames();

        status = TestDisp_init(appObj);

        if(status == SystemP_SUCCESS)
        {
            retVal = TestDisp_Error(appObj, testId);
            retVal += TestDisp_deInit(appObj);

            if(FVID2_SOK != retVal)
            {
                status = SystemP_FAILURE;
            }
        }

        if(testId == TEST_DSS_IOCTL_DCTRL_SET_INVALID_VP_ID)
        {
            /* It should return failure*/
            if(status == SystemP_SUCCESS)
            {
                return status;
            }
        }
        if(testId == TEST_DSS_IOCTL_DCTRL_CONFIG_IN_USE_VP || testId == TEST_DSS_IOCTL_DCTRL_SET_INVALID_OLY_ID
            || testId == TEST_DSS_IOCTL_DCTRL_SET_INVALID_LAYER_PARAMS)
        {
            status = SystemP_FAILURE;
        }
    }

    if(status == SystemP_SUCCESS)
    {
        status = SystemP_FAILURE;
    }
    else
    {
        status = SystemP_SUCCESS;
    }

    return status;
}

static int32_t testStopVpIoctl(Dss_Object *appObj)
{
    Dss_DctrlVpParams stopVpParams;
    int32_t retVal = FVID2_SOK;

    /* Calling with Invalid VP ID */
    stopVpParams.vpId = CSL_DSS_VP_ID_MAX;

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_STOP_VP,
        &stopVpParams,
        NULL);

    stopVpParams.vpId = CSL_DSS_VP_ID_1;
    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_STOP_VP,
        &stopVpParams,
        NULL);

    return retVal;
}

static int32_t testVPErrStatsIoctls(Dss_Object *appObj)
{
    Dss_DctrlVpErrorStats vpErrStats;
    int32_t retVal = FVID2_SOK;

    /* Calling with Invalid VP ID */
    vpErrStats.vpId = CSL_DSS_VP_ID_MAX;

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_GET_VP_ERROR_STATS,
        &vpErrStats,
        NULL);

    vpErrStats.vpId = CSL_DSS_VP_ID_2;
    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_GET_VP_ERROR_STATS,
        &vpErrStats,
        NULL);

    return retVal;
}

static int32_t testInvalidIoctSetup(Dss_Object *appObj)
{
    Dss_DctrlSyncLostCbParams syncLostCbParams;
    int32_t retVal = FVID2_SOK;

    /*Calling with NULL command args*/
    retVal = Fvid2_control(
            appObj->dctrlHandle,
            IOCTL_DSS_DCTRL_REGISTER_SYNCLOST_CB,
            NULL,
            NULL);
    if(retVal != FVID2_EBADARGS)
    {
        DebugP_log("TEST_DSS_IOCTL_DCTRL_INVALID_IOCTL failed!\r\n");
        return retVal;
    }

    /* calling with invalid command */
    retVal = Fvid2_control(
            appObj->dctrlHandle,
            TEST_DSS_INVALID_IOCTL_CMD,
            &syncLostCbParams,
            NULL);
    if(retVal != FVID2_EUNSUPPORTED_CMD)
    {
        DebugP_log("TEST_DSS_IOCTL_DCTRL_INVALID_IOCTL failed!\r\n");
        return retVal;
    }

    DebugP_log("IOCTL_DCTRL_INVALID_IOCTL Passed\r\n");
    return FVID2_SOK;
}

static int32_t testSyncLostCBIoctl(Dss_Object *appObj)
{
    Dss_DctrlSyncLostCbParams syncLostCbParams;
    int32_t retVal = FVID2_SOK;

    syncLostCbParams.vpId = CSL_DSS_VP_ID_MAX;
    syncLostCbParams.syncLostCbFxn = syncLostCallback;
    syncLostCbParams.appData = NULL;

    retVal = Fvid2_control(
            appObj->dctrlHandle,
            IOCTL_DSS_DCTRL_REGISTER_SYNCLOST_CB,
            &syncLostCbParams,
            NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Register callback sync lost IOCTL failed for VP ID: %d\r\n", syncLostCbParams.vpId);
    }

    syncLostCbParams.vpId = CSL_DSS_VP_ID_1;
    syncLostCbParams.syncLostCbFxn = syncLostCallback;
    syncLostCbParams.appData = NULL;

    retVal = Fvid2_control(
            appObj->dctrlHandle,
            IOCTL_DSS_DCTRL_REGISTER_SYNCLOST_CB,
            &syncLostCbParams,
            NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Register callback sync lost IOCTL failed for VP ID: %d\r\n", syncLostCbParams.vpId);
    }

    return retVal;
}

static int32_t testLineCBIoctl(Dss_Object *appObj)
{
    Dss_DctrlLineNumCbParams lineCbParams;
    int32_t retVal = FVID2_SOK;

    /* Invalid VP ID */
    lineCbParams.vpId = CSL_DSS_VP_ID_MAX;
    lineCbParams.lineNumCbFxn = lineNumCallback;
    lineCbParams.appData = NULL;

    retVal = Fvid2_control(
            appObj->dctrlHandle,
            IOCTL_DSS_DCTRL_REGISTER_LINENUM_CB,
            &lineCbParams,
            NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Register Linenumber callback IOCTL failed!!!\r\n");
    }

    /* call the ioctl properly now */
    lineCbParams.vpId = CSL_DSS_VP_ID_1;
    lineCbParams.lineNumCbFxn = lineNumCallback;
    lineCbParams.appData = NULL;

    retVal = Fvid2_control(
            appObj->dctrlHandle,
            IOCTL_DSS_DCTRL_REGISTER_LINENUM_CB,
            &lineCbParams,
            NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Register Linenumber callback IOCTL failed!!!\r\n");
    }

    return retVal;
}

static void lineNumCallback()
{
    gLineNumCallbackHit = 1;
}

static void syncLostCallback()
{
    gSyncLostCallbackHit = 1;
}
#endif
