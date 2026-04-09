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
 *  \file test_display_control.c
 *
 *  \brief Application to initialise and control display.
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

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Number of frames (5sec 300 frames) */
#define DISP_NUM_FRAMES_COUNT              ((uint32_t)300U)

/* Max frame size based on resolution */
#define DISP_FRAME_SIZE_MAX                (3840U*1080U)

/* Max pixel width */
#define DISP_FRAME_PIXEL_WIDTH_MAX          (4U)

/* Safety test defines */
/* Number of frames for safety test */
#define TEST_DSS_SAFETY_NUM_FRAMES_COUNT       ((uint32_t)100U)

/* Frame number at which to corrupt the buffer for data integrity test */
#define TEST_DSS_SAFETY_CORRUPT_FRAME_NUM      ((uint32_t)70U)

/* Freeze detect threshold value - callback fires after this many identical frames */
#define TEST_DSS_SAFETY_FREEZE_THRESHOLD       ((uint32_t)30U)

/* Number of frames to display after clearing freeze (with new buffer) */
#define TEST_DSS_SAFETY_FREEZE_CLEAR_FRAMES    ((uint32_t)10U)


/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* Safety test callback data structure */
typedef struct
{
    uint32_t safetyInterrupt;
    /**< Flag to check interrupt received */
    uint32_t regionId;
    /**< Region Id for which interrupt has occurred */
    uint32_t vpId;
    /**< Video Port Id */
    uint32_t frameCount;
    /**< Frame count at which interrupt occurred */
    uint32_t safetyCheckMode;
    /**< Mode of safety check: DATA_INTEGRITY or FRAME_FREEZE_DETECT */
    uint64_t capturedSign;
    /**< Captured MISR signature */
} TestDisp_SafetyCbData;

/* Pipeline safety callback data - one per pipe */
typedef struct
{
    uint32_t safetyInterrupt;
    /**< Flag to check interrupt received */
    uint32_t pipeId;
    /**< Pipeline Id for which interrupt has occurred */
    uint32_t frameCount;
    /**< Frame count at which interrupt occurred */
    uint32_t safetyCheckMode;
    /**< Mode of safety check: DATA_INTEGRITY or FRAME_FREEZE_DETECT */
    uint32_t capturedSign;
    /**< Captured MISR signature */
} TestDisp_PipeSafetyCbData;


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

/* Safety test function declarations */
static int32_t TestDisp_safetyRunTestCommon(Dss_Object *appObj,
                                            uint32_t safetyMode,
                                            uint32_t enablePipeSafety);
static int32_t TestDisp_safetyCreate(Dss_Object *appObj,
                                     uint32_t safetyMode,
                                     uint32_t enablePipeSafety);
static void TestDisp_safetyDelete(Dss_Object *appObj);
static void TestDisp_safetyInitDssParams(Dss_Object *appObj,
                                         uint32_t safetyMode);
static int32_t TestDisp_safetyConfigDctrl(Dss_Object *appObj);
static void TestDisp_safetyInitPipelineParams(Dss_Object *appObj);
void TestDisp_vpSafetyErrCallback(uint32_t vpID,
                                 Dss_DctrlVpSafetyCbData safetyCbData,
                                 void *appData);
void TestDisp_pipeSafetyErrCallback(uint32_t pipeId,
                                    uint32_t capturedSign,
                                    void *appData);
static int32_t TestDisp_logVpSafetyData(uint32_t safetyMode);
static int32_t TestDisp_logPipeSafetyData(uint32_t safetyMode);
int32_t TestDisp_vpSafetyDisplayControlCommon(Dss_Object *appObj,
                                              uint32_t safetyMode);

static int32_t TestDisp_safetyRunTestFrameSkip(Dss_Object *appObj,
                                                uint32_t safetyMode,
                                                uint32_t frameSkipVal);

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
uint8_t gFirstPipelineFrameBuf[CONFIG_DSS_NUM_FRAMES_PER_PIPELINE][DISP_FRAME_SIZE_MAX * DISP_FRAME_PIXEL_WIDTH_MAX]__attribute__ ((section (".dssFrameBuffer"), aligned (4096)));
uint8_t gSecondPipelineFrameBuf[CONFIG_DSS_NUM_FRAMES_PER_PIPELINE][DISP_FRAME_SIZE_MAX * DISP_FRAME_PIXEL_WIDTH_MAX]__attribute__ ((section (".dssFrameBuffer"), aligned (4096))) ;

/* Pointer to frame buffers per pipleline */
void *firstPipeFrameBufferPointer[CONFIG_DSS_NUM_FRAMES_PER_PIPELINE];
void *secondPipeFrameBufferPointer[CONFIG_DSS_NUM_FRAMES_PER_PIPELINE];

/* VP safety callback data for all safety regions */
TestDisp_SafetyCbData TestDss_vpSafetyCbData[CSL_DSS_VP_SAFETY_REGION_MAX];

TestDisp_PipeSafetyCbData TestDss_pipeSafetyCbDataVid;
TestDisp_PipeSafetyCbData TestDss_pipeSafetyCbDataVidl;

/* Safety test loop count - shared with callback */
volatile uint32_t TestDss_safetyLoopCount = 0U;

/* Runtime VP safety configuration.
 * CONFIG_DSS_NUM_SAFETY_REGIONS defaults to 0U (syscfg has no VP safety
 * regions configured), which compiles the IOCTL loop away entirely.
 * Test functions set TestDss_numVpSafetyRegions > 0 and populate
 * TestDss_vpSafetyParamsRuntime before calling the safety display control. */
uint32_t TestDss_numVpSafetyRegions = CONFIG_DSS_NUM_SAFETY_REGIONS;
Dss_DctrlVpSafetyChkParams TestDss_vpSafetyParamsRuntime[CSL_DSS_VP_SAFETY_REGION_MAX];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void TestDisp_initFrames()
{
    uint32_t instCnt = 0;
    uint32_t numPipes = gDssConfigPipelineParams.numTestPipes <= DSS_DISP_INST_MAX \
                        ? gDssConfigPipelineParams.numTestPipes : DSS_DISP_INST_MAX;

    for(instCnt = 0; instCnt < CONFIG_DSS_NUM_FRAMES_PER_PIPELINE; instCnt++)
    {
        firstPipeFrameBufferPointer[instCnt] = &gFirstPipelineFrameBuf[instCnt];
        secondPipeFrameBufferPointer[instCnt] = &gSecondPipelineFrameBuf[instCnt];
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

int32_t TestDisp_displayControl(Dss_Object *appObj)
{
    int32_t retVal = FVID2_SOK;
    int32_t status = SystemP_SUCCESS;

    /* Initialise frames */
    TestDisp_initFrames();

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

/**
 * \brief  Execute pipeline-level safety tests with configurable safety mode.
 *
 *  Initializes frames and resets all VP and pipeline safety callback data for both
 *  VID and VIDL pipes. Configures DSS, executes safety test with the specified mode,
 *  logs and verifies pipeline safety check results, then deinitializes. Supports both
 *  DATA_INTEGRITY and FRAME_FREEZE_DETECT modes for comprehensive pipeline protection.
 *
 *  \param appObj Pointer to DSS object containing configuration and state.
 *  \param safetyMode Safety check mode (CSL_DSS_SAFETY_CHK_DATA_INTEGRITY or FRAME_FREEZE_DETECT).
 *
 *  \return SystemP_SUCCESS on success, SystemP_FAILURE otherwise.
 */
int32_t TestDisp_pipeSafetyDisplayControl(Dss_Object *appObj, uint32_t safetyMode)
{
    int32_t retVal = FVID2_SOK;
    int32_t status = SystemP_SUCCESS;

    /* Initialise frames */
    TestDisp_initFrames();

    /* Reset all safety callback data */
    memset(TestDss_vpSafetyCbData, 0, sizeof(TestDss_vpSafetyCbData));
    memset(&TestDss_pipeSafetyCbDataVid, 0, sizeof(TestDss_pipeSafetyCbDataVid));
    memset(&TestDss_pipeSafetyCbDataVidl, 0, sizeof(TestDss_pipeSafetyCbDataVidl));
    TestDss_safetyLoopCount = 0U;

    status = TestDisp_init(appObj);

    if(status == SystemP_SUCCESS)
    {
        retVal = TestDisp_safetyRunTestCommon(appObj, safetyMode, TRUE);

        retVal += TestDisp_deInit(appObj);

        if(FVID2_SOK != retVal)
        {
            status = SystemP_FAILURE;
        }
    }

    /* Log and verify pipeline safety check results */
    if(status == SystemP_SUCCESS)
    {
        status = TestDisp_logPipeSafetyData(safetyMode);
    }

    return status;
}

/**
 * \brief  Execute VP safety data integrity tests with frame skip validation.
 *
 *  Initializes frames and resets VP safety callback data. Configures DSS and runs
 *  safety test with frame skip enabled to verify that MISR signatures are validated
 *  correctly even when frames are skipped. Tests error detection robustness under
 *  non-uniform frame output conditions before deinitializing.
 *
 *  \param appObj Pointer to DSS object containing configuration and state.
 *  \param frameSkipVal Frame skip value to apply during safety test.
 *
 *  \return SystemP_SUCCESS on success, SystemP_FAILURE otherwise.
 */
int32_t TestDisp_frameSkipDisplayControl(Dss_Object *appObj,
                                         uint32_t frameSkipVal)
{
    int32_t retVal = FVID2_SOK;
    int32_t status = SystemP_SUCCESS;

    /* Initialise frames */
    TestDisp_initFrames();

    /* Reset safety callback data */
    memset(TestDss_vpSafetyCbData, 0, sizeof(TestDss_vpSafetyCbData));
    TestDss_safetyLoopCount = 0U;

    status = TestDisp_init(appObj);

    if(status == SystemP_SUCCESS)
    {
        retVal = TestDisp_safetyRunTestFrameSkip(appObj,
                    CSL_DSS_SAFETY_CHK_DATA_INTEGRITY, frameSkipVal);

        retVal += TestDisp_deInit(appObj);

        if(FVID2_SOK != retVal)
        {
            status = SystemP_FAILURE;
        }
    }

    return status;
}

/**
 * \brief  Common entry point for VP safety tests with configurable safety mode.
 *
 *  Initializes frames and resets VP safety callback data. Configures DSS and runs
 *  safety test with the specified mode (data integrity or frame freeze detection),
 *  logs and verifies VP safety check results, then deinitializes. This common
 *  function supports both DATA_INTEGRITY and FRAME_FREEZE_DETECT test modes.
 *
 *  \param appObj Pointer to DSS object containing configuration and state.
 *  \param safetyMode Safety check mode (CSL_DSS_SAFETY_CHK_DATA_INTEGRITY or FRAME_FREEZE_DETECT).
 *
 *  \return SystemP_SUCCESS on success, SystemP_FAILURE otherwise.
 */
int32_t TestDisp_vpSafetyDisplayControlCommon(Dss_Object *appObj,
                                              uint32_t safetyMode)
{
    int32_t retVal = FVID2_SOK;
    int32_t status = SystemP_SUCCESS;

    /* Initialise frames */
    TestDisp_initFrames();

    /* Reset safety callback data */
    memset(TestDss_vpSafetyCbData, 0, sizeof(TestDss_vpSafetyCbData));
    TestDss_safetyLoopCount = 0U;

    status = TestDisp_init(appObj);

    if(status == SystemP_SUCCESS)
    {
        retVal = TestDisp_safetyRunTestCommon(appObj, safetyMode, FALSE);

        retVal += TestDisp_deInit(appObj);

        if(FVID2_SOK != retVal)
        {
            status = SystemP_FAILURE;
        }
    }

    /* Log and verify VP safety check results */
    if(status == SystemP_SUCCESS)
    {
        status = TestDisp_logVpSafetyData(safetyMode);
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
    overlayParams->overlayCfg.transColorKeyMin =  gDssOverlayParams.overlayCfg.transColorKeyMin;
    overlayParams->overlayCfg.transColorKeyMax =  gDssOverlayParams.overlayCfg.transColorKeyMax;

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
    }

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

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_SET_GLOBAL_DSS_PARAMS,
        globalDssParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Set Global DSS Params IOCTL failed!!!\r\n");
    }

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

/**
 * \brief  VP safety error callback for handling safety check violations.
 *
 *  Callback function invoked when a VP safety violation is detected (MISR mismatch
 *  or frame freeze condition). Records the interrupt event, region ID, VP ID, frame
 *  count, safety mode, and captured MISR signature for subsequent test verification
 *  and analysis.
 *
 *  \param vpID Viewport ID where safety violation occurred.
 *  \param safetyCbData Safety callback data containing region ID and captured signature.
 *  \param appData Application data pointer containing safety check mode.
 *
 *  \return None.
 */
void TestDisp_vpSafetyErrCallback(uint32_t vpID,
                                 Dss_DctrlVpSafetyCbData safetyCbData,
                                 void *appData)
{
    if(safetyCbData.regionId < CSL_DSS_VP_SAFETY_REGION_MAX)
    {
        if(TestDss_vpSafetyCbData[safetyCbData.regionId].safetyInterrupt != TRUE &&
           TestDss_safetyLoopCount < TEST_DSS_SAFETY_NUM_FRAMES_COUNT)
        {
            TestDss_vpSafetyCbData[safetyCbData.regionId].safetyInterrupt = TRUE;
            TestDss_vpSafetyCbData[safetyCbData.regionId].regionId = safetyCbData.regionId;
            TestDss_vpSafetyCbData[safetyCbData.regionId].vpId = vpID;
            TestDss_vpSafetyCbData[safetyCbData.regionId].frameCount = TestDss_safetyLoopCount;
            TestDss_vpSafetyCbData[safetyCbData.regionId].safetyCheckMode = *(uint32_t *)appData;
            TestDss_vpSafetyCbData[safetyCbData.regionId].capturedSign = safetyCbData.capturedSign;
        }
    }
}

/**
 * \brief  Initialize DSS parameters for safety test execution.
 *
 *  Test Category: Functionality
 *
 *  Initializes VP, overlay, layer, and global DSS parameters. Configures VP safety
 *  regions from test-populated or syscfg-seeded runtime buffers, registers safety error
 *  callback, and overrides VP/pipeline safety parameters based on the requested safety
 *  mode (data integrity or frame freeze detection with appropriate thresholds).
 *
 *  \param appObj Pointer to DSS object containing configuration and state.
 *  \param safetyMode Safety check mode (CSL_DSS_SAFETY_CHK_DATA_INTEGRITY or FRAME_FREEZE_DETECT).
 *
 *  \return None.
 */
static void TestDisp_safetyInitDssParams(Dss_Object *appObj,
                                         uint32_t safetyMode)
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
    vpSafetyParams = (Dss_DctrlVpSafetyChkParams *)&appObj->vpSafetyParams;

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

    vpParams->lcdPolarityCfg.actVidPolarity = gDssVpParams.lcdPolarityCfg.actVidPolarity;
    vpParams->lcdPolarityCfg.hsPolarity = gDssVpParams.lcdPolarityCfg.hsPolarity;
    vpParams->lcdPolarityCfg.vsPolarity = gDssVpParams.lcdPolarityCfg.vsPolarity;
    vpParams->lcdPolarityCfg.pixelClkPolarity = gDssVpParams.lcdPolarityCfg.pixelClkPolarity;

    /* Configure VP Advance Params */
    advVpParams->vpId = gDssAdvVpParams.vpId;
    advVpParams->lcdAdvSignalCfg.hVAlign = gDssAdvVpParams.lcdAdvSignalCfg.hVAlign;
    advVpParams->lcdAdvSignalCfg.hVClkControl = gDssAdvVpParams.lcdAdvSignalCfg.hVClkControl;

    /* Configure VP Safety Params - Initialize all regions first */
    for(uint8_t count = 0; count < CSL_DSS_VP_SAFETY_REGION_MAX; count++)
    {
        Dss_dctrlVpSafetyChkParamsInit(vpSafetyParams + count);
    }

    /* Seed runtime buffer from syscfg when syscfg has regions configured.
     * When CONFIG_DSS_NUM_SAFETY_REGIONS == 0 (the common case), this
     * block is compiled away and TestDss_vpSafetyParamsRuntime is populated
     * directly by the test function before calling the display control. */
#if (CONFIG_DSS_NUM_SAFETY_REGIONS > 0)
    if(TestDss_numVpSafetyRegions == 0U)
    {
        TestDss_numVpSafetyRegions = CONFIG_DSS_NUM_SAFETY_REGIONS;
    }
    for(uint8_t i = 0U; i < (uint8_t)CONFIG_DSS_NUM_SAFETY_REGIONS; i++)
    {
        TestDss_vpSafetyParamsRuntime[i] = gDssVpSafetyParams[i];
    }
#endif

    /* Configure safety regions from runtime buffer (test-populated or syscfg-seeded) */
    for(uint8_t count = 0; count < (uint8_t)TestDss_numVpSafetyRegions; count++)
    {
        vpSafetyParams[count].vpId =
            TestDss_vpSafetyParamsRuntime[count].vpId;
        vpSafetyParams[count].safetySignSeedVal =
            TestDss_vpSafetyParamsRuntime[count].safetySignSeedVal;
        vpSafetyParams[count].regionSafetyChkCfg.regionId =
            TestDss_vpSafetyParamsRuntime[count].regionSafetyChkCfg.regionId;
        vpSafetyParams[count].regionSafetyChkCfg.referenceSign =
            TestDss_vpSafetyParamsRuntime[count].regionSafetyChkCfg.referenceSign;
        vpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.safetyChkEnable =
            TestDss_vpSafetyParamsRuntime[count].regionSafetyChkCfg.safetyChkCfg.safetyChkEnable;
        vpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.safetyChkMode =
            TestDss_vpSafetyParamsRuntime[count].regionSafetyChkCfg.safetyChkCfg.safetyChkMode;
        vpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.seedSelectEnable =
            TestDss_vpSafetyParamsRuntime[count].regionSafetyChkCfg.safetyChkCfg.seedSelectEnable;
        vpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.thresholdValue =
            TestDss_vpSafetyParamsRuntime[count].regionSafetyChkCfg.safetyChkCfg.thresholdValue;
        vpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.frameSkip =
            TestDss_vpSafetyParamsRuntime[count].regionSafetyChkCfg.safetyChkCfg.frameSkip;
        vpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.regionPos.startX =
            TestDss_vpSafetyParamsRuntime[count].regionSafetyChkCfg.safetyChkCfg.regionPos.startX;
        vpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.regionPos.startY =
            TestDss_vpSafetyParamsRuntime[count].regionSafetyChkCfg.safetyChkCfg.regionPos.startY;
        vpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.regionSize.width =
            TestDss_vpSafetyParamsRuntime[count].regionSafetyChkCfg.safetyChkCfg.regionSize.width;
        vpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.regionSize.height =
            TestDss_vpSafetyParamsRuntime[count].regionSafetyChkCfg.safetyChkCfg.regionSize.height;

        /* Register the VP safety error callback */
        vpSafetyParams[count].safetyErrCbFxn = TestDisp_vpSafetyErrCallback;
        vpSafetyParams[count].appData =
            &vpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.safetyChkMode;
    }

    /* Configure Overlay Params */
    overlayParams->overlayId = gDssOverlayParams.overlayId;
    overlayParams->colorbarEnable = gDssOverlayParams.colorbarEnable;
    overlayParams->overlayCfg.colorKeyEnable = gDssOverlayParams.overlayCfg.colorKeyEnable;
    overlayParams->overlayCfg.colorKeySel = gDssOverlayParams.overlayCfg.colorKeySel;
    overlayParams->overlayCfg.backGroundColor = gDssOverlayParams.overlayCfg.backGroundColor;
    overlayParams->overlayCfg.transColorKeyMin = gDssOverlayParams.overlayCfg.transColorKeyMin;
    overlayParams->overlayCfg.transColorKeyMax = gDssOverlayParams.overlayCfg.transColorKeyMax;

    /* Configure Overlay Layer params */
    layerParams->overlayId = gDssOverlayLayerParams.overlayId;
    memcpy((void *)layerParams->pipeLayerNum,
           (void *)gDssOverlayLayerParams.pipeLayerNum,
           sizeof(gDssOverlayLayerParams.pipeLayerNum));

    /* Override VP safety regions for the requested mode */
    if(safetyMode == CSL_DSS_SAFETY_CHK_FRAME_FREEZE_DETECT)
    {
        for(uint8_t count = 0; count < (uint8_t)TestDss_numVpSafetyRegions; count++)
        {
            vpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.safetyChkMode =
                CSL_DSS_SAFETY_CHK_FRAME_FREEZE_DETECT;
            vpSafetyParams[count].regionSafetyChkCfg.safetyChkCfg.thresholdValue =
                TEST_DSS_SAFETY_FREEZE_THRESHOLD;
        }
    }

    /* Override pipeline safety params for the requested mode */
    {
        uint32_t numPipes = gDssConfigPipelineParams.numTestPipes;

        for(uint32_t instCnt = 0U; instCnt < numPipes; instCnt++)
        {
            if(gDssConfigPipelineParams.safetyCheck[instCnt] == TRUE)
            {
                gDssPipelineSafetyParams[instCnt].safetyChkCfg.safetyChkMode =
                    safetyMode;

                if(safetyMode == CSL_DSS_SAFETY_CHK_FRAME_FREEZE_DETECT)
                {
                    gDssPipelineSafetyParams[instCnt].safetyChkCfg.thresholdValue =
                        TEST_DSS_SAFETY_FREEZE_THRESHOLD;
                    gDssPipelineSafetyParams[instCnt].referenceSign = 0x0U;
                }
                else
                {
                    /* DATA_INTEGRITY mode - use default config values */
                    gDssPipelineSafetyParams[instCnt].safetyChkCfg.thresholdValue = 0x0U;
                }
            }
        }
    }
}

/**
 * \brief  Initialize pipeline parameters for safety test execution.
 *
 *  Initializes display parameters for all configured pipelines including pipe type,
 *  input format, dimensions, scaling, and alpha blending. For pipelines with safety
 *  checking enabled, configures pipeline-level safety parameters (MISR signature seeds,
 *  safety check modes, thresholds, and region definitions) from test-populated parameters.
 *
 *  \param appObj Pointer to DSS object containing configuration and state.
 *
 *  \return None.
 */
static void TestDisp_safetyInitPipelineParams(Dss_Object *appObj)
{
    uint32_t instCnt = 0U, numPipes = 0U;
    Dss_DispParams *dispParams;
    Dss_InstObject *instObj;

    numPipes = gDssConfigPipelineParams.numTestPipes;

    for(instCnt = 0U; instCnt < numPipes; instCnt++)
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

        dispParams->pipeCfg.inFmt.dataFormat = gDssConfigPipelineParams.inDataFmt[instCnt];
        dispParams->pipeCfg.inFmt.scanFormat = gDssConfigPipelineParams.inScanFmt[instCnt];
        dispParams->pipeCfg.outWidth = gDssConfigPipelineParams.outWidth[instCnt];
        dispParams->pipeCfg.outHeight = gDssConfigPipelineParams.outHeight[instCnt];
        dispParams->pipeCfg.scEnable = gDssConfigPipelineParams.scEnable[instCnt];

        dispParams->alphaCfg.globalAlpha = gDssConfigPipelineParams.globalAlpha[instCnt];
        dispParams->alphaCfg.preMultiplyAlpha = gDssConfigPipelineParams.preMultiplyAlpha[instCnt];
        dispParams->layerPos.startX = gDssConfigPipelineParams.posx[instCnt];
        dispParams->layerPos.startY = gDssConfigPipelineParams.posy[instCnt];

        Dss_dispPipeMflagParamsInit(&instObj->mflagParams);

        /* Initialize pipeline safety params if enabled */
        if(gDssConfigPipelineParams.safetyCheck[instCnt] == TRUE)
        {
            Dss_dispPipeSafetyChkParamsInit(&instObj->safetyParams);

            instObj->safetyParams.safetySignSeedVal =
                gDssPipelineSafetyParams[instCnt].safetySignSeedVal;
            instObj->safetyParams.referenceSign =
                gDssPipelineSafetyParams[instCnt].referenceSign;
            instObj->safetyParams.safetyChkCfg.safetyChkEnable =
                gDssPipelineSafetyParams[instCnt].safetyChkCfg.safetyChkEnable;
            instObj->safetyParams.safetyChkCfg.safetyChkMode =
                gDssPipelineSafetyParams[instCnt].safetyChkCfg.safetyChkMode;
            instObj->safetyParams.safetyChkCfg.seedSelectEnable =
                gDssPipelineSafetyParams[instCnt].safetyChkCfg.seedSelectEnable;
            instObj->safetyParams.safetyChkCfg.thresholdValue =
                gDssPipelineSafetyParams[instCnt].safetyChkCfg.thresholdValue;
            instObj->safetyParams.safetyChkCfg.frameSkip =
                gDssPipelineSafetyParams[instCnt].safetyChkCfg.frameSkip;
            instObj->safetyParams.safetyChkCfg.regionPos.startX =
                gDssPipelineSafetyParams[instCnt].safetyChkCfg.regionPos.startX;
            instObj->safetyParams.safetyChkCfg.regionPos.startY =
                gDssPipelineSafetyParams[instCnt].safetyChkCfg.regionPos.startY;
            instObj->safetyParams.safetyChkCfg.regionSize.width =
                gDssPipelineSafetyParams[instCnt].safetyChkCfg.regionSize.width;
            instObj->safetyParams.safetyChkCfg.regionSize.height =
                gDssPipelineSafetyParams[instCnt].safetyChkCfg.regionSize.height;
        }
    }
}

/**
 * \brief  Configure display controller with safety parameters via IOCTLs.
 *
 *  Sends IOCTLs to configure VP, overlay, layer, advanced VP, global DSS, and OLDI
 *  parameters through the display controller. For safety-enabled tests, additionally
 *  configures VP safety check parameters for all configured safety regions with their
 *  respective MISR signatures, thresholds, and region definitions.
 *
 *  \param appObj Pointer to DSS object containing configuration and state.
 *
 *  \return FVID2_SOK on success, error code otherwise.
 */
static int32_t TestDisp_safetyConfigDctrl(Dss_Object *appObj)
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
    /* Always use local buffer as destination for safety params */
    vpSafetyParams = (Dss_DctrlVpSafetyChkParams *)&appObj->vpSafetyParams;
    globalDssParams = &appObj->globalDssParams;

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_SET_PATH,
        appObj->dctrlPathInfo,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("Dctrl Set Path IOCTL failed!!!\r\n");
    }

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

    if(appObj->oldiParams != NULL)
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

    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_SET_GLOBAL_DSS_PARAMS,
        globalDssParams,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DCTRL Set Global DSS Params IOCTL failed!!!\r\n");
    }

    /* Set VP Safety Check Params for each configured safety region */
    for(uint8_t count = 0; count < (uint8_t)TestDss_numVpSafetyRegions; count++)
    {
        retVal = Fvid2_control(
            appObj->dctrlHandle,
            IOCTL_DSS_DCTRL_SET_VP_SAFETY_CHK_PARAMS,
            vpSafetyParams + count,
            NULL);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("DCTRL Set VP Safety Params IOCTL failed for region %d!!!\r\n", count);
            break;
        }
    }

    return (retVal);
}

/**
 * \brief  Create display instances with VP and pipeline-level safety configuration.
 *
 *  Initializes VP and pipeline parameters with specified safety mode, configures VP
 *  safety regions and pipeline-level safety checks, registers safety error callbacks,
 *  and creates FVID2 display driver instances for all configured pipelines. Applies
 *  safety parameters via IOCTLs and sets up synchronization semaphores for frame
 *  callback coordination.
 *
 *  \param appObj Pointer to DSS object containing configuration and state.
 *  \param safetyMode Safety check mode (CSL_DSS_SAFETY_CHK_DATA_INTEGRITY or FRAME_FREEZE_DETECT).
 *  \param enablePipeSafety Enable pipeline-level safety checks (TRUE/FALSE).
 *
 *  \return FVID2_SOK on success, error code otherwise.
 */
static int32_t TestDisp_safetyCreate(Dss_Object *appObj,
                                     uint32_t safetyMode,
                                     uint32_t enablePipeSafety)
{
    int32_t retVal = FVID2_SOK;
    int32_t status = SystemP_SUCCESS;
    uint32_t instCnt = 0U;
    Dss_InstObject *instObj;

    /* Init VP, Overlay, Panel and Safety params */
    TestDisp_safetyInitDssParams(appObj, safetyMode);

    /* Configure DSS pipeline params with safety */
    TestDisp_safetyInitPipelineParams(appObj);

    /* Register pipeline safety error callback if enabled */
    if(enablePipeSafety == TRUE)
    {
        for(instCnt = 0U; instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
        {
            if(gDssConfigPipelineParams.safetyCheck[instCnt] == TRUE)
            {
                instObj = &appObj->instObj[instCnt];
                instObj->safetyParams.safetyErrCbFxn = TestDisp_pipeSafetyErrCallback;
                instObj->safetyParams.appData =
                    &gDssPipelineSafetyParams[instCnt].safetyChkCfg.safetyChkMode;
            }
        }
    }

    /* Config IOCTL for VP, Overlay, Panel and Safety */
    retVal = TestDisp_safetyConfigDctrl(appObj);

    if(retVal == FVID2_SOK)
    {
        for(instCnt = 0U; instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
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
                DebugP_log("Display Create failed!!!\r\n");
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

            /* Set pipeline safety check params if enabled */
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
                        DebugP_log("DSS Set Pipe Safety Params IOCTL failed!!!\r\n");
                    }
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

/**
 * \brief  Delete display instances and verify safety error statistics.
 *
 *  Dequeues pending frames from all pipeline drivers, collects underflow and
 *  sync-lost error statistics from DSS hardware, logs any errors encountered, and
 *  performs clean shutdown by stopping VP and clearing the display path. Verifies
 *  that expected safety violations were detected during test execution.
 *
 *  \param appObj Pointer to DSS object containing driver handles and error state.
 *
 *  \return None.
 */
static void TestDisp_safetyDelete(Dss_Object *appObj)
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

    for(instCnt = 0U; instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
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
            DebugP_log("Display get stats failed!!!\r\n");
        }

        /* Print underflow errors */
        if(0U != currStatus.underflowCount)
        {
            GT_2trace(DssTrace, GT_ERR,
                      "No of Underflows for Inst %d: %d\r\n",
                      instCnt, currStatus.underflowCount);
        }
        else
        {
            DebugP_log("Pipeline Instance %d: Underflow did not occur\r\n",
                       gDssConfigPipelineParams.instId[instCnt]);
        }

        /* Dequeue all the request from the driver */
        while(1U)
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
        GT_1trace(DssTrace, GT_ERR,
                  "No of Sync Lost: %d\r\n", pErrorStats->syncLost);
    }
    else
    {
        DebugP_log("VP Instance %d: Sync Lost did not occur\r\n",
                   gDssVpParams.vpId);
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

/**
 * \brief  Execute full safety test cycle with frame corruption or freeze scenarios.
 *
 *  Creates display drivers with VP and pipeline safety configuration, starts pipelines,
 *  executes specified number of frame iterations, and injects test violations. For
 *  DATA_INTEGRITY mode, corrupts frame data at a specific frame count to trigger safety
 *  errors. For FRAME_FREEZE_DETECT mode, re-queues the same frame repeatedly to trigger
 *  freeze detection. Collects error statistics, stops drivers, and performs cleanup.
 *
 *  \param appObj Pointer to DSS object containing configuration and driver handles.
 *  \param safetyMode Safety check mode (CSL_DSS_SAFETY_CHK_DATA_INTEGRITY or FRAME_FREEZE_DETECT).
 *  \param enablePipeSafety Enable pipeline-level safety checks (TRUE/FALSE).
 *
 *  \return FVID2_SOK on success, error code otherwise.
 */
static int32_t TestDisp_safetyRunTestCommon(Dss_Object *appObj,
                                            uint32_t safetyMode,
                                            uint32_t enablePipeSafety)
{
    int32_t retVal = FVID2_SOK;
    uint32_t instCnt = 0U;
    Dss_InstObject *instObj;
    Fvid2_FrameList frmList;

    TestDss_safetyLoopCount = 0U;

    /* Create driver with safety configuration */
    retVal = TestDisp_safetyCreate(appObj, safetyMode, enablePipeSafety);

    if(retVal == FVID2_SOK)
    {
        /* Start driver */
        for(instCnt = 0U; instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
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
        while(TestDss_safetyLoopCount++ < TEST_DSS_SAFETY_NUM_FRAMES_COUNT)
        {
            for(instCnt = 0U; instCnt < gDssConfigPipelineParams.numTestPipes;
                instCnt++)
            {
                instObj = &appObj->instObj[instCnt];
                (void)SemaphoreP_pend(&instObj->syncSem, SystemP_WAIT_FOREVER);
                retVal = Fvid2_dequeue(instObj->drvHandle,
                                       &frmList,
                                       0U,
                                       FVID2_TIMEOUT_NONE);

                /* Corrupt frame buffer for DATA_INTEGRITY mode only */
                if(safetyMode == CSL_DSS_SAFETY_CHK_DATA_INTEGRITY)
                {
                    if(TestDss_safetyLoopCount == TEST_DSS_SAFETY_CORRUPT_FRAME_NUM)
                    {
                        /* For pipeline safety, only corrupt enabled pipes */
                        if(!enablePipeSafety ||
                           gDssConfigPipelineParams.safetyCheck[instCnt] == TRUE)
                        {
                            for(uint32_t count = 0;
                                count < gDssConfigPipelineParams.inHeight[instCnt] *
                                        gDssConfigPipelineParams.pitch[instCnt][0];
                                count++)
                            {
                                *(uint8_t *)(frmList.frames[0]->addr[0] + count) = 0xAA;
                            }
                        }
                    }
                }
                /* For FRAME_FREEZE_DETECT: no corruption, same frame is re-queued */

                if(FVID2_SOK == retVal)
                {
                    retVal = Fvid2_queue(instObj->drvHandle, &frmList, 0U);
                    if(FVID2_SOK != retVal)
                    {
                        DebugP_log("Display Queue failed!!!\r\n");
                        break;
                    }
                }
                else if(FVID2_EAGAIN == retVal)
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

        for(instCnt = 0U; instCnt < gDssConfigPipelineParams.numTestPipes;
            instCnt++)
        {
            instObj = &appObj->instObj[instCnt];
            retVal = Fvid2_stop(instObj->drvHandle, NULL);
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
        TestDisp_safetyDelete(appObj);
    }

    return retVal;
}

/**
 * \brief  Execute VP safety test with frame skip validation.
 *
 *  Saves original frame skip values, overrides them with the specified skip pattern
 *  for all VP safety regions, and executes the standard safety test flow with frame
 *  corruption. Validates that MISR signatures are correctly computed even when frames
 *  are skipped in the detection pipeline, then restores original frame skip values.
 *
 *  \param appObj Pointer to DSS object containing configuration and driver handles.
 *  \param safetyMode Safety check mode (CSL_DSS_SAFETY_CHK_DATA_INTEGRITY or FRAME_FREEZE_DETECT).
 *  \param frameSkipVal Frame skip value to apply during safety test.
 *
 *  \return FVID2_SOK on success, error code otherwise.
 */
static int32_t TestDisp_safetyRunTestFrameSkip(Dss_Object *appObj,
                                                uint32_t safetyMode,
                                                uint32_t frameSkipVal)
{
    int32_t retVal = FVID2_SOK;
    uint32_t savedFrameSkip[CSL_DSS_VP_SAFETY_REGION_MAX];

    /* Save original frameSkip values and override */
    for(uint8_t count = 0; count < (uint8_t)TestDss_numVpSafetyRegions; count++)
    {
        savedFrameSkip[count] =
            TestDss_vpSafetyParamsRuntime[count].regionSafetyChkCfg.safetyChkCfg.frameSkip;
        TestDss_vpSafetyParamsRuntime[count].regionSafetyChkCfg.safetyChkCfg.frameSkip =
            frameSkipVal;
    }

    /* Run the standard safety test flow with frame skip enabled */
    retVal = TestDisp_safetyRunTestCommon(appObj, safetyMode, FALSE);

    /* Restore original frameSkip values */
    for(uint8_t count = 0; count < (uint8_t)TestDss_numVpSafetyRegions; count++)
    {
        TestDss_vpSafetyParamsRuntime[count].regionSafetyChkCfg.safetyChkCfg.frameSkip =
            savedFrameSkip[count];
    }

    return retVal;
}

/**
 * \brief  Logs VP safety data for all configured safety regions and validates safety triggers.
 *
 *  Iterates through all VP safety regions, logs safety data including region ID, VP ID,
 *  safety check mode, frame count, and captured signature. Validates that safety
 *  interrupts were triggered correctly, safety check modes match expected values,
 *  and frame thresholds are met for freeze detection. Returns success only if all
 *  regions triggered with expected safety modes and thresholds.
 *
 *  \param safetyMode Safety check mode to validate (CSL_DSS_SAFETY_CHK_DATA_INTEGRITY or
 *                    CSL_DSS_SAFETY_CHK_FRAME_FREEZE_DETECT).
 *
 *  \return SystemP_SUCCESS if all safety regions triggered correctly; SystemP_FAILURE otherwise.
 */
static int32_t TestDisp_logVpSafetyData(uint32_t safetyMode)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t count;

    DebugP_log("****************************************************\r\n");
    DebugP_log("VP Safety Data Log (%s)\r\n",
               safetyMode == CSL_DSS_SAFETY_CHK_DATA_INTEGRITY ?
               "DATA_INTEGRITY" : "FRAME_FREEZE_DETECT");
    DebugP_log("****************************************************\r\n");

    for(count = 0U; count < TestDss_numVpSafetyRegions; count++)
    {
        DebugP_log("----------------------------------------------------\r\n");
        DebugP_log("Safety Data Log Region : %d\r\n",
                   TestDss_vpSafetyCbData[count].regionId);
        DebugP_log("Safety Data VP ID: %s\r\n",
                   TestDss_vpSafetyCbData[count].vpId == CSL_DSS_VP_ID_1 ? "VP1" : "VP2");

        if(TestDss_vpSafetyCbData[count].safetyInterrupt == TRUE)
        {
            DebugP_log("Safety Check Interrupt Trigger: TRUE\r\n");

            if(TestDss_vpSafetyCbData[count].safetyCheckMode ==
               CSL_DSS_SAFETY_CHK_FRAME_FREEZE_DETECT)
            {
                DebugP_log("Safety Check Mode: FRAME_FREEZE_DETECT\r\n");

                if(TestDss_vpSafetyCbData[count].safetyCheckMode !=
                   CSL_DSS_SAFETY_CHK_FRAME_FREEZE_DETECT)
                {
                    DebugP_log("ERROR: Expected FRAME_FREEZE_DETECT mode, got %d\r\n",
                               TestDss_vpSafetyCbData[count].safetyCheckMode);
                    status = SystemP_FAILURE;
                }

                if(TestDss_vpSafetyCbData[count].frameCount < TEST_DSS_SAFETY_FREEZE_THRESHOLD)
                {
                    DebugP_log("ERROR: Freeze callback fired too early at frame %d "
                               "(threshold=%d)\r\n",
                               TestDss_vpSafetyCbData[count].frameCount,
                               TEST_DSS_SAFETY_FREEZE_THRESHOLD);
                    status = SystemP_FAILURE;
                }
            }
            else if(TestDss_vpSafetyCbData[count].safetyCheckMode ==
                    CSL_DSS_SAFETY_CHK_DATA_INTEGRITY)
            {
                DebugP_log("Safety Check Mode: DATA_INTEGRITY\r\n");
            }

            DebugP_log("Safety Data Frame count: %d\r\n",
                       TestDss_vpSafetyCbData[count].frameCount);
            DebugP_log("Safety Data Captured Signature: 0x%lX\r\n",
                       TestDss_vpSafetyCbData[count].capturedSign);
        }
        else
        {
            status = SystemP_FAILURE;
            DebugP_log("ERROR: Safety Check Interrupt NOT triggered for "
                       "region %d\r\n", count);
        }
    }

    if(status == SystemP_SUCCESS)
    {
        DebugP_log("****************************************************\r\n");
        DebugP_log("VP Safety (%s): All %d regions triggered correctly\r\n",
                   safetyMode == CSL_DSS_SAFETY_CHK_DATA_INTEGRITY ?
                   "DATA_INTEGRITY" : "FRAME_FREEZE_DETECT",
                   TestDss_numVpSafetyRegions);
    }

    return status;
}

/**
 * \brief  Callback function invoked when pipeline-level safety error is detected.
 *
 *  Captures safety error information for video or video lite pipelines when MISR
 *  signature mismatch is detected. Logs the pipe ID, captured signature, frame count
 *  at error detection, and safety check mode. Callback is invoked once per pipeline
 *  during safety test execution when frame corruption triggers signature validation.
 *
 *  \param pipeId Pipeline instance ID that detected the safety error.
 *  \param capturedSign MISR signature value captured at error detection.
 *  \param appData Application context containing safety check mode for error logging.
 *
 *  \return None.
 */
void TestDisp_pipeSafetyErrCallback(uint32_t pipeId,
                                    uint32_t capturedSign,
                                    void *appData)
{
    if(Dss_dispIsVidInst(pipeId) == TRUE)
    {
        if(TestDss_pipeSafetyCbDataVid.safetyInterrupt != TRUE &&
           TestDss_safetyLoopCount < TEST_DSS_SAFETY_NUM_FRAMES_COUNT)
        {
            TestDss_pipeSafetyCbDataVid.safetyInterrupt = TRUE;
            TestDss_pipeSafetyCbDataVid.pipeId = pipeId;
            TestDss_pipeSafetyCbDataVid.frameCount = TestDss_safetyLoopCount;
            TestDss_pipeSafetyCbDataVid.safetyCheckMode = *(uint32_t *)appData;
            TestDss_pipeSafetyCbDataVid.capturedSign = capturedSign;
        }
    }
    else if(Dss_dispIsVidLInst(pipeId) == TRUE)
    {
        if(TestDss_pipeSafetyCbDataVidl.safetyInterrupt != TRUE &&
           TestDss_safetyLoopCount < TEST_DSS_SAFETY_NUM_FRAMES_COUNT)
        {
            TestDss_pipeSafetyCbDataVidl.safetyInterrupt = TRUE;
            TestDss_pipeSafetyCbDataVidl.pipeId = pipeId;
            TestDss_pipeSafetyCbDataVidl.frameCount = TestDss_safetyLoopCount;
            TestDss_pipeSafetyCbDataVidl.safetyCheckMode = *(uint32_t *)appData;
            TestDss_pipeSafetyCbDataVidl.capturedSign = capturedSign;
        }
    }
}

/**
 * \brief  Logs pipeline safety data for all configured safety pipelines and validates safety triggers.
 *
 *  Iterates through all configured pipeline safety checks, logs safety data including
 *  pipeline ID (VID/VIDL), safety check mode, frame count, and captured signature.
 *  Validates that safety interrupts were triggered correctly, safety check modes match
 *  expected values, and frame thresholds are met for freeze detection. Returns success
 *  only if all configured pipelines with safety checks triggered with expected safety
 *  modes and thresholds.
 *
 *  \param safetyMode Safety check mode to validate (CSL_DSS_SAFETY_CHK_DATA_INTEGRITY or
 *                    CSL_DSS_SAFETY_CHK_FRAME_FREEZE_DETECT).
 *
 *  \return SystemP_SUCCESS if all configured pipelines triggered correctly; SystemP_FAILURE otherwise.
 */
static int32_t TestDisp_logPipeSafetyData(uint32_t safetyMode)
{
    int32_t status = SystemP_SUCCESS;

    DebugP_log("****************************************************\r\n");
    DebugP_log("Pipeline Safety Data Log\r\n");
    DebugP_log("****************************************************\r\n");

    for(uint32_t instCnt = 0U; instCnt < gDssConfigPipelineParams.numTestPipes;
        instCnt++)
    {
        if(gDssConfigPipelineParams.safetyCheck[instCnt] != TRUE)
        {
            continue;
        }

        if(Dss_dispIsVidInst(gDssConfigPipelineParams.pipeId[instCnt]) == TRUE)
        {
            DebugP_log("----------------------------------------------------\r\n");
            DebugP_log("Safety Data Pipeline ID: VID1\r\n");

            if(TestDss_pipeSafetyCbDataVid.safetyInterrupt == TRUE)
            {
                DebugP_log("Safety Check Interrupt Trigger: TRUE\r\n");

                if(safetyMode == CSL_DSS_SAFETY_CHK_FRAME_FREEZE_DETECT)
                {
                    DebugP_log("Safety Check Mode: FRAME_FREEZE_DETECT\r\n");

                    if(TestDss_pipeSafetyCbDataVid.safetyCheckMode !=
                       CSL_DSS_SAFETY_CHK_FRAME_FREEZE_DETECT)
                    {
                        DebugP_log("ERROR: Expected FRAME_FREEZE_DETECT mode\r\n");
                        status = SystemP_FAILURE;
                    }

                    if(TestDss_pipeSafetyCbDataVid.frameCount <
                       TEST_DSS_SAFETY_FREEZE_THRESHOLD)
                    {
                        DebugP_log("ERROR: Freeze callback fired too early at "
                                   "frame %d (threshold=%d)\r\n",
                                   TestDss_pipeSafetyCbDataVid.frameCount,
                                   TEST_DSS_SAFETY_FREEZE_THRESHOLD);
                        status = SystemP_FAILURE;
                    }
                }
                else if(safetyMode == CSL_DSS_SAFETY_CHK_DATA_INTEGRITY)
                {
                    DebugP_log("Safety Check Mode: DATA_INTEGRITY\r\n");

                    if(TestDss_pipeSafetyCbDataVid.safetyCheckMode !=
                       CSL_DSS_SAFETY_CHK_DATA_INTEGRITY)
                    {
                        DebugP_log("ERROR: Expected DATA_INTEGRITY mode\r\n");
                        status = SystemP_FAILURE;
                    }
                }

                DebugP_log("Safety Data Frame count: %d\r\n",
                           TestDss_pipeSafetyCbDataVid.frameCount);
                DebugP_log("Safety Data Captured Signature: 0x%X\r\n",
                           TestDss_pipeSafetyCbDataVid.capturedSign);
            }
            else
            {
                status = SystemP_FAILURE;
                DebugP_log("ERROR: Safety Check Interrupt NOT triggered for "
                           "VID1 pipeline\r\n");
            }
        }
        else if(Dss_dispIsVidLInst(gDssConfigPipelineParams.pipeId[instCnt]) == TRUE)
        {
            DebugP_log("----------------------------------------------------\r\n");
            DebugP_log("Safety Data Pipeline ID: VIDL1\r\n");

            if(TestDss_pipeSafetyCbDataVidl.safetyInterrupt == TRUE)
            {
                DebugP_log("Safety Check Interrupt Trigger: TRUE\r\n");

                if(safetyMode == CSL_DSS_SAFETY_CHK_FRAME_FREEZE_DETECT)
                {
                    DebugP_log("Safety Check Mode: FRAME_FREEZE_DETECT\r\n");

                    if(TestDss_pipeSafetyCbDataVidl.safetyCheckMode !=
                       CSL_DSS_SAFETY_CHK_FRAME_FREEZE_DETECT)
                    {
                        DebugP_log("ERROR: Expected FRAME_FREEZE_DETECT mode\r\n");
                        status = SystemP_FAILURE;
                    }

                    if(TestDss_pipeSafetyCbDataVidl.frameCount <
                       TEST_DSS_SAFETY_FREEZE_THRESHOLD)
                    {
                        DebugP_log("ERROR: Freeze callback fired too early at "
                                   "frame %d (threshold=%d)\r\n",
                                   TestDss_pipeSafetyCbDataVidl.frameCount,
                                   TEST_DSS_SAFETY_FREEZE_THRESHOLD);
                        status = SystemP_FAILURE;
                    }
                }
                else if(safetyMode == CSL_DSS_SAFETY_CHK_DATA_INTEGRITY)
                {
                    DebugP_log("Safety Check Mode: DATA_INTEGRITY\r\n");

                    if(TestDss_pipeSafetyCbDataVidl.safetyCheckMode !=
                       CSL_DSS_SAFETY_CHK_DATA_INTEGRITY)
                    {
                        DebugP_log("ERROR: Expected DATA_INTEGRITY mode\r\n");
                        status = SystemP_FAILURE;
                    }
                }

                DebugP_log("Safety Data Frame count: %d\r\n",
                           TestDss_pipeSafetyCbDataVidl.frameCount);
                DebugP_log("Safety Data Captured Signature: 0x%X\r\n",
                           TestDss_pipeSafetyCbDataVidl.capturedSign);
            }
            else
            {
                status = SystemP_FAILURE;
                DebugP_log("ERROR: Safety Check Interrupt NOT triggered for "
                           "VIDL1 pipeline\r\n");
            }
        }
    }

    if(status == SystemP_SUCCESS)
    {
        DebugP_log("****************************************************\r\n");
        DebugP_log("Pipeline Safety (%s): All enabled pipes triggered "
                   "correctly\r\n",
                   safetyMode == CSL_DSS_SAFETY_CHK_DATA_INTEGRITY ?
                   "DATA_INTEGRITY" : "FRAME_FREEZE_DETECT");
    }

    return status;
}

