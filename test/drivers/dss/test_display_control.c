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
#define DISP_NUM_FRAMES_COUNT                   ((uint32_t)300U)

/* Max frame size based on resolution */
#define DISP_FRAME_SIZE_MAX                     (3840U*1080U)

/* Max pixel width */
#define DISP_FRAME_PIXEL_WIDTH_MAX              (4U)

/* Safety test defines */
/* Number of frames for safety test */
#define TEST_DSS_SAFETY_NUM_FRAMES_COUNT       ((uint32_t)100U)

/* Frame number at which to corrupt the buffer for data integrity test */
#define TEST_DSS_SAFETY_CORRUPT_FRAME_NUM      ((uint32_t)70U)

/* Freeze detect threshold value - callback fires after this many identical frames */
#define TEST_DSS_SAFETY_FREEZE_THRESHOLD       ((uint32_t)30U)

/* Number of frames to display after clearing freeze (with new buffer) */
#define TEST_DSS_SAFETY_FREEZE_CLEAR_FRAMES    ((uint32_t)10U)

/* Number of frames for the starvation test */
#define TEST_DSS_STARVE_NUM_FRAMES_COUNT       ((uint32_t)100U)

/* Frame number at which to start starving (stop re-queuing frames) */
#define TEST_DSS_STARVE_START_FRAME_NUM        ((uint32_t)30U)

/* Number of VSYNC intervals to remain starved (no frames queued) */
#define TEST_DSS_STARVE_DURATION_FRAMES        ((uint32_t)40U)

/* Number of frames each dual-display thread will dequeue/requeue */
#define TEST_DSS_DD_NUM_FRAMES                  (100U)

/* Number of dual-display threads (1 per VP: OLDI + DPI) */
#define TEST_DSS_DD_NUM_THREADS                 (2U)

#define TEST_DSS_TASK_STACK_SIZE                (8192U)

/* Task priority for dual-display threads */
#define TEST_DSS_TASK_PRIORITY                  (2U)

/* Number of dequeue/requeue iterations per thread */
#define TEST_DSS_MT_NUM_ITERATIONS              (20U)

#define TEST_DSS_HP_PHASE_FRAMES                (30U)

/* Number of IOCTL loop iterations per sub-test thread */
#define TEST_DSS_MT_IOCTL_LOOP_COUNT            (10U)

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

typedef struct
{
    Dss_InstObject *instObj;
    /**< Pointer to the pipeline instance for this thread */
    uint32_t        threadIdx;
    /**< 0 = OLDI thread, 1 = DPI thread */
    int32_t         result;
    /**< SystemP_SUCCESS or SystemP_FAILURE */
    uint32_t        frameCount;
    /**< Number of frames successfully dequeued/requeued */
    uint64_t        startTimeUs;
    /**< Start timestamp */
    uint64_t        endTimeUs;
    /**< End timestamp */
} TestDisp_DdThreadCtx;

/* Multi-thread test context passed to each worker thread */
typedef struct
{
    Dss_Object    *appObj;
    /**< Pointer to the DSS application object */
    uint32_t       pipeIdx;
    /**< Pipeline index (0 = VID1, 1 = VIDL1) */
    int32_t        result;
    /**< Thread result: SystemP_SUCCESS or SystemP_FAILURE */
    uint32_t       frameCount;
    /**< Number of frames successfully dequeued/requeued */
    uint64_t       startTimeUs;
    /**< Start timestamp in microseconds */
    uint64_t       endTimeUs;
    /**< End timestamp in microseconds */
} TestDisp_MtThreadCtx;


typedef struct
{
    Dss_Object   *appObj;
    /**< Shared DSS application object */
    Fvid2_Handle  handle;
    /**< DCTRL handle to use for the IOCTL */
    uint32_t      subTestId;
    /**< One of the sub-test IDs above */
    uint32_t      loopCount;
    /**< Number of iterations to run the IOCTL in a tight loop */
    int32_t       result;
    /**< SystemP_SUCCESS / SystemP_FAILURE written by the worker */
    uint32_t      passCount;
    /**< Number of iterations that returned FVID2_SOK */
} TestDisp_MtIoctlCtx;

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

static void TestDisp_underflowCbFxn(void *appData);
static void TestDisp_syncLostCbFxn(uint32_t vpId, void *appData);
static int32_t TestDisp_runStarveTest(Dss_Object *appObj);

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

#if defined (SOC_AM62PX)
/* Task objects for dual-display threads */
static TaskP_Object TestDss_dispDdTaskObj[TEST_DSS_DD_NUM_THREADS];

/* Task stacks */
static uint8_t TestDss_dispDdTaskStack[TEST_DSS_DD_NUM_THREADS][TEST_DSS_TASK_STACK_SIZE]
    __attribute__((aligned(32)));

/* Per-thread context */
static TestDisp_DdThreadCtx TestDss_dispDdCtx[TEST_DSS_DD_NUM_THREADS];

/* Counting semaphore for thread completion signaling */
static SemaphoreP_Object TestDss_dispDdDoneSem;

/* Start barrier — both threads wait until main releases them simultaneously */
static SemaphoreP_Object TestDss_dispDdStartSem;
#endif

TestDisp_PipeSafetyCbData TestDss_pipeSafetyCbDataVid;
TestDisp_PipeSafetyCbData TestDss_pipeSafetyCbDataVidl;

/* Safety test loop count - shared with callback */
volatile uint32_t TestDss_safetyLoopCount = 0U;

uint32_t TestDss_numVpSafetyRegions = CONFIG_DSS_NUM_SAFETY_REGIONS;
Dss_DctrlVpSafetyChkParams TestDss_vpSafetyParamsRuntime[CSL_DSS_VP_SAFETY_REGION_MAX];

/* Buffer underflow test callback data */
volatile uint32_t TestDss_underflowCbCount = 0U;
volatile uint32_t TestDss_syncLostCbCount = 0U;

volatile uint32_t TestDss_starveRepeatFrmCount  = 0U;
volatile uint32_t TestDss_starveUnderflowCount  = 0U;
volatile uint32_t TestDss_starveDispFrmCount    = 0U;
volatile uint32_t TestDss_starveSyncLostCount   = 0U;

/* Task objects, stacks, context array */
static TaskP_Object    TestDss_mtIoctlTaskObj[TEST_DSS_DD_NUM_THREADS];
static uint8_t         TestDss_mtIoctlTaskStack[TEST_DSS_DD_NUM_THREADS][TEST_DSS_TASK_STACK_SIZE] __attribute__((aligned(32)));
static TestDisp_MtIoctlCtx TestDss_mtIoctlCtx[TEST_DSS_DD_NUM_THREADS];
static SemaphoreP_Object TestDss_mtIoctlDoneSem;
static SemaphoreP_Object TestDss_mtIoctlStartSem;

/* Task objects for the pipeline threads */
static TaskP_Object TestDss_dispMtTaskObj[TEST_DSS_DD_NUM_THREADS];

/* Task stack for each thread */
static uint8_t TestDss_dispMtTaskStack[TEST_DSS_DD_NUM_THREADS][TEST_DSS_TASK_STACK_SIZE]__attribute__((aligned(32)));

/* Per-thread context */
static TestDisp_MtThreadCtx TestDss_dispMtCtx[TEST_DSS_DD_NUM_THREADS];

/* Counting semaphore for thread completion signaling */
static SemaphoreP_Object TestDss_dispMtDoneSem;

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

    /* Reset safety-region test state to prevent cross-test contamination */
    TestDss_numVpSafetyRegions = 0U;
    memset(TestDss_vpSafetyParamsRuntime, 0, sizeof(TestDss_vpSafetyParamsRuntime));

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

    /* Reset safety-region test state to prevent cross-test contamination */
    TestDss_numVpSafetyRegions = 0U;
    memset(TestDss_vpSafetyParamsRuntime, 0, sizeof(TestDss_vpSafetyParamsRuntime));

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

            if(safetyMode == CSL_DSS_SAFETY_CHK_FRAME_FREEZE_DETECT)
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
            else if(safetyMode == CSL_DSS_SAFETY_CHK_DATA_INTEGRITY)
            {
                DebugP_log("Safety Check Mode: DATA_INTEGRITY\r\n");

                if(TestDss_vpSafetyCbData[count].safetyCheckMode !=
                   CSL_DSS_SAFETY_CHK_DATA_INTEGRITY)
                {
                    DebugP_log("ERROR: Expected DATA_INTEGRITY mode, got %d\r\n",
                               TestDss_vpSafetyCbData[count].safetyCheckMode);
                    status = SystemP_FAILURE;
                }
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

static void TestDisp_underflowCbFxn(void *appData)
{
    TestDss_underflowCbCount++;
}

static void TestDisp_syncLostCbFxn(uint32_t vpId, void *appData)
{
    TestDss_syncLostCbCount++;
}

/**
 * \brief  Run test that deliberately starves the DSS pipeline to trigger buffer underflow and sync lost errors.
 *
 *  Creates display driver and registers underflow and sync-lost callbacks. Queues and dequeues
 *  frames normally for initial frames, then starves the pipeline by stopping frame re-queuing
 *  for a specified duration to trigger underflow and frame repeat conditions. Resumes normal
 *  queuing for remaining frames. After stopping, queries current display status for underflow
 *  and repeat frame counts, and VP error stats for sync lost. Validates that underflow was
 *  detected through either callback invocation or underflow counter, and sync lost stats are available.
 *
 *  \param appObj Pointer to DSS object containing driver handles and configuration.
 *
 *  \return FVID2_SOK on success, error code otherwise.
 */
static int32_t TestDisp_runStarveTest(Dss_Object *appObj)
{
    int32_t retVal = FVID2_SOK;
    uint32_t instCnt = 0U;
    volatile uint32_t loopCount = 0U;
    Dss_InstObject *instObj;
    Fvid2_FrameList frmList;
    Dss_DispCurrentStatus currStatus;
    Dss_DctrlVpErrorStats vpErrStats;
    Dss_DispUnderFlowCbParams underFlowCbParams;
    Dss_DctrlSyncLostCbParams syncLostCbParams;

    /* Create driver */
    retVal = TestDisp_create(appObj);

    if(retVal == FVID2_SOK)
    {
        /* Register underflow callback for each pipe */
        for(instCnt = 0U; instCnt < gDssConfigPipelineParams.numTestPipes;
            instCnt++)
        {
            instObj = &appObj->instObj[instCnt];

            Dss_dispUnderFlowCbParamsInit(&underFlowCbParams);
            underFlowCbParams.underFlowCbFxn = &TestDisp_underflowCbFxn;
            underFlowCbParams.appData = instObj;

            retVal = Fvid2_control(
                instObj->drvHandle,
                IOCTL_DSS_DISP_REGISTER_PIPE_UNDERFLOW_CB,
                &underFlowCbParams,
                NULL);
            if(retVal != FVID2_SOK)
            {
                DebugP_log("Register underflow CB failed for pipe %d\r\n",
                           instCnt);
                break;
            }
        }
    }

    if(retVal == FVID2_SOK)
    {
        /* Register sync-lost callback on the VP */
        syncLostCbParams.vpId = gDssVpParams.vpId;
        syncLostCbParams.syncLostCbFxn = &TestDisp_syncLostCbFxn;
        syncLostCbParams.appData = NULL;

        retVal = Fvid2_control(
            appObj->dctrlHandle,
            IOCTL_DSS_DCTRL_REGISTER_SYNCLOST_CB,
            &syncLostCbParams,
            NULL);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("Register sync-lost CB failed\r\n");
        }
    }

    if(retVal == FVID2_SOK)
    {
        /* Start driver */
        for(instCnt = 0U; instCnt < gDssConfigPipelineParams.numTestPipes;
            instCnt++)
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
        while(loopCount++ < TEST_DSS_STARVE_NUM_FRAMES_COUNT)
        {
            for(instCnt = 0U;
                instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
            {
                instObj = &appObj->instObj[instCnt];

                (void) SemaphoreP_pend(&instObj->syncSem,
                                       SystemP_WAIT_FOREVER);

                retVal = Fvid2_dequeue(instObj->drvHandle,
                                       &frmList,
                                       0U,
                                       FVID2_TIMEOUT_NONE);

                if(FVID2_SOK == retVal)
                {
                    /*
                     * Starvation window: do NOT re-queue the dequeued frame
                     * so the pipeline runs out of buffers.
                     */
                    if(loopCount >= TEST_DSS_STARVE_START_FRAME_NUM &&
                       loopCount < (TEST_DSS_STARVE_START_FRAME_NUM +
                                    TEST_DSS_STARVE_DURATION_FRAMES))
                    {
                        /* Intentionally drop the frame – do not re-queue */
                        DebugP_log("Starving DSS at frame %d\r\n",
                                   loopCount);
                    }
                    else
                    {
                        /* Normal operation – re-queue the frame */
                        retVal = Fvid2_queue(instObj->drvHandle, &frmList, 0U);
                        if(FVID2_SOK != retVal)
                        {
                            DebugP_log("Display Queue failed!!!\r\n");
                            break;
                        }
                    }
                }
                else if(FVID2_EAGAIN == retVal)
                {
                    /* No frame available to dequeue – expected during starvation */
                    retVal = FVID2_SOK;
                }
                else
                {
                    DebugP_log("Display Dequeue failed!!!\r\n");
                    break;
                }
            }
        }

        /* Stop driver */
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
        /* Reset starvation result globals before accumulating */
        TestDss_starveRepeatFrmCount = 0U;
        TestDss_starveUnderflowCount = 0U;
        TestDss_starveDispFrmCount   = 0U;
        TestDss_starveSyncLostCount  = 0U;

        /* Query underflow and repeat-frame stats per pipeline */
        for(instCnt = 0U; instCnt < gDssConfigPipelineParams.numTestPipes;
            instCnt++)
        {
            instObj = &appObj->instObj[instCnt];

            retVal = Fvid2_control(
                instObj->drvHandle,
                IOCTL_DSS_DISP_GET_CURRENT_STATUS,
                &currStatus,
                NULL);
            if(FVID2_SOK != retVal)
            {
                DebugP_log("Display get status failed for pipe %d\r\n",
                           instCnt);
            }
            else
            {
                DebugP_log("Pipeline %d: underflowCount=%d, "
                           "repeatFrmCount=%d, dispFrmCount=%d\r\n",
                           gDssConfigPipelineParams.instId[instCnt],
                           currStatus.underflowCount,
                           currStatus.repeatFrmCount,
                           currStatus.dispFrmCount);

                /* Accumulate across pipes so the caller can assert */
                TestDss_starveRepeatFrmCount += currStatus.repeatFrmCount;
                TestDss_starveUnderflowCount += currStatus.underflowCount;
                TestDss_starveDispFrmCount   += currStatus.dispFrmCount;
            }

            /* Dequeue remaining frames */
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

        /* Query VP sync-lost error stats */
        vpErrStats.vpId = gDssVpParams.vpId;
        retVal = Fvid2_control(
            appObj->dctrlHandle,
            IOCTL_DSS_DCTRL_GET_VP_ERROR_STATS,
            &vpErrStats,
            NULL);
        if(FVID2_SOK != retVal)
        {
            DebugP_log("VP get error stats failed\r\n");
        }
        else
        {
            DebugP_log("VP syncLost count: %d\r\n", vpErrStats.syncLost);
            TestDss_starveSyncLostCount = vpErrStats.syncLost;
        }

        /* Clear path and stop VP */
        retVal = Fvid2_control(
            appObj->dctrlHandle,
            IOCTL_DSS_DCTRL_CLEAR_PATH,
            appObj->dctrlPathInfo,
            NULL);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("Clear Path failed!!!\r\n");
        }

        retVal = Fvid2_control(
            appObj->dctrlHandle,
            IOCTL_DSS_DCTRL_STOP_VP,
            &appObj->vpParams,
            NULL);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("VP Stop failed!!!\r\n");
        }
    }

    return retVal;
}

/**
 * \brief  Test wrapper for buffer underflow and sync lost error detection.
 *
 *  Initializes frames and resets underflow and sync-lost callback counters.
 *  Initializes DSS configuration, runs the starvation test to trigger buffer
 *  underflow and sync lost conditions, then deinitializes the display driver.
 *  Validates that underflow and sync lost errors are correctly detected and
 *  reported through callbacks and error statistics.
 *
 *  \param appObj Pointer to DSS object containing driver handles and configuration.
 *
 *  \return SystemP_SUCCESS on successful test execution; SystemP_FAILURE otherwise.
 */
int32_t TestDisp_bufUnderflowSyncLostDisplayControl(Dss_Object *appObj)
{
    int32_t retVal = FVID2_SOK;
    int32_t status = SystemP_SUCCESS;

    /* Initialise frames */
    TestDisp_initFrames();

    /* Reset underflow/sync-lost callback counters */
    TestDss_underflowCbCount = 0U;
    TestDss_syncLostCbCount  = 0U;

    status = TestDisp_init(appObj);

    if(status == SystemP_SUCCESS)
    {
        retVal = TestDisp_runStarveTest(appObj);

        retVal += TestDisp_deInit(appObj);

        if(FVID2_SOK != retVal)
        {
            status = SystemP_FAILURE;
        }
    }

    return status;
}

/**
 * \brief  Execute display cycle with configurable flip/mirror modes.
 *
 *  Temporarily overrides the flipType in pipeline parameters and runs a full display
 *  cycle with the specified flip mode (NONE, V, H, or HV). Adjusts frame buffer base
 *  addresses for horizontal/vertical flips, executes display frames, and restores
 *  original pipeline configuration. Requires caller to set flip-compatible data format.
 *
 *  \param appObj Pointer to DSS object containing configuration and state.
 *  \param flipType Flip mode (FVID2_FLIP_TYPE_NONE / _V / _H / _HV).
 *
 *  \return SystemP_SUCCESS on success, SystemP_FAILURE otherwise.
 */
int32_t TestDisp_flipDisplayControl(Dss_Object *appObj, uint32_t flipType)
{
    int32_t retVal = FVID2_SOK;
    int32_t status = SystemP_SUCCESS;
    uint32_t instCnt;
    uint32_t savedFlipType[DSS_DISP_INST_MAX] = {0};
    uint32_t savedDataFmt[DSS_DISP_INST_MAX] = {0};
    uint32_t savedPitch[DSS_DISP_INST_MAX] = {0};

    /* Save current pipeline params that we will override */
    for(instCnt = 0U; instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
    {
        savedDataFmt[instCnt] = gDssConfigPipelineParams.inDataFmt[instCnt];
        savedPitch[instCnt]   = gDssConfigPipelineParams.pitch[instCnt][0U];
        savedFlipType[instCnt] = FVID2_FLIP_TYPE_NONE;
    }

    /* Initialise frames with current pipeline format settings */
    TestDisp_initFrames();

    if(FVID2_FLIP_TYPE_H == (FVID2_FLIP_TYPE_H & flipType))
    {
        for(instCnt = 0U; instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
        {
            uint32_t width  = gDssConfigPipelineParams.inWidth[instCnt];
            uint32_t height = gDssConfigPipelineParams.inHeight[instCnt];
            uint32_t pitch  = gDssConfigPipelineParams.pitch[instCnt][0U];
            uint32_t bpp    = pitch / width;
            uint32_t offset = (height - 1U) * pitch;

            /* For HV flip, also add horizontal offset to reach last pixel */
            if(FVID2_FLIP_TYPE_V == (FVID2_FLIP_TYPE_V & flipType))
            {
                offset += (width - 1U) * bpp;
            }

            for(uint32_t frmId = 0U; frmId < CONFIG_DSS_NUM_FRAMES_PER_PIPELINE; frmId++)
            {
                if(instCnt == 0U)
                {
                    firstPipeFrameBufferPointer[frmId] =
                        (uint8_t *)firstPipeFrameBufferPointer[frmId] + offset;
                }
                else
                {
                    secondPipeFrameBufferPointer[frmId] =
                        (uint8_t *)secondPipeFrameBufferPointer[frmId] + offset;
                }
            }
        }
    }

    status = TestDisp_init(appObj);

    if(status == SystemP_SUCCESS)
    {
        /* Init VP, Overlay and Panel params */
        TestDisp_initDssParams(appObj);

        /* Configure DSS pipeline params - this populates instObj->dispParams */
        TestDisp_initPipelineParams(appObj);

        /* Override the flip type for all pipes */
        for(instCnt = 0U; instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
        {
            appObj->instObj[instCnt].dispParams.pipeCfg.flipType = flipType;
        }

        /* Config IOCTL for VP, Overlay and Panel */
        retVal = TestDisp_configDctrl(appObj);

        if(retVal == FVID2_SOK)
        {
            /* Create DISP driver instances, set params, alloc and queue frames */
            for(instCnt = 0U; instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
            {
                Dss_InstObject *instObj = &appObj->instObj[instCnt];

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
                        DebugP_log("DSS Set Params IOCTL failed (flipType=%u)!!!\r\n",
                                   flipType);
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

        if(retVal == FVID2_SOK)
        {
            /* Start driver */
            for(instCnt = 0U; instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
            {
                Dss_InstObject *instObj = &appObj->instObj[instCnt];
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
            /* VSYNC loop - display frames */
            volatile uint32_t loopCount = 0U;
            Fvid2_FrameList frmList;

            while(loopCount++ < DISP_NUM_FRAMES_COUNT)
            {
                for(instCnt = 0U; instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
                {
                    Dss_InstObject *instObj = &appObj->instObj[instCnt];
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
                    else if(FVID2_EAGAIN == retVal)
                    {
                        /* Do nothing as this is first callback */
                    }
                    else
                    {
                        DebugP_log("Display Dequeue failed!!!\r\n");
                        break;
                    }
                }
            }

            /* Stop driver */
            for(instCnt = 0U; instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
            {
                Dss_InstObject *instObj = &appObj->instObj[instCnt];
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
            /* Delete driver - dequeue remaining frames, delete handles */
            TestDisp_delete(appObj);
        }

        retVal += TestDisp_deInit(appObj);

        if(FVID2_SOK != retVal)
        {
            status = SystemP_FAILURE;
        }
    }

    /* Restore frame buffer pointers to base (in case offset was applied) */
    TestDisp_initFrames();

    /* Restore original pipeline params */
    for(instCnt = 0U; instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
    {
        gDssConfigPipelineParams.inDataFmt[instCnt] = savedDataFmt[instCnt];
        gDssConfigPipelineParams.pitch[instCnt][0U] = savedPitch[instCnt];
    }

    return status;
}

/**
 *  \brief  Worker thread function for multi-thread pipeline test.
 *
 *  Each thread operates on a single pipeline (VID or VIDL). It performs
 *  TEST_DSS_MT_NUM_ITERATIONS dequeue/requeue cycles using the VSYNC semaphore
 *  for synchronization. On completion, it posts the done semaphore.
 */
static void TestDisp_mtPipeWorker(void *arg)
{
    TestDisp_MtThreadCtx *ctx = (TestDisp_MtThreadCtx *)arg;
    Dss_InstObject *instObj = &ctx->appObj->instObj[ctx->pipeIdx];
    Fvid2_FrameList frmList;
    int32_t retVal;
    uint32_t loopCount = 0U;

    ctx->result     = SystemP_SUCCESS;
    ctx->frameCount = 0U;
    ctx->startTimeUs = ClockP_getTimeUsec();

    while(loopCount < TEST_DSS_MT_NUM_ITERATIONS)
    {
        /* Wait for VSYNC callback */
        (void)SemaphoreP_pend(&instObj->syncSem, SystemP_WAIT_FOREVER);

        retVal = Fvid2_dequeue(instObj->drvHandle,
                               &frmList,
                               0U,
                               FVID2_TIMEOUT_NONE);

        if(FVID2_SOK == retVal)
        {
            retVal = Fvid2_queue(instObj->drvHandle, &frmList, 0U);
            if(FVID2_SOK != retVal)
            {
                DebugP_log("MT Thread %d: Queue failed at iter %d!\r\n",
                           ctx->pipeIdx, loopCount);
                ctx->result = SystemP_FAILURE;
                break;
            }
            ctx->frameCount++;
            loopCount++;
        }
        else if(FVID2_EAGAIN == retVal)
        {
            /* First callback, no frame to dequeue yet — continue */
        }
        else
        {
            DebugP_log("MT Thread %d: Dequeue failed at iter %d!\r\n",
                       ctx->pipeIdx, loopCount);
            ctx->result = SystemP_FAILURE;
            break;
        }
    }

    ctx->endTimeUs = ClockP_getTimeUsec();

    /* Signal completion */
    SemaphoreP_post(&TestDss_dispMtDoneSem);
    TaskP_exit();
}

/**
 *  \brief  Multi-thread display control: initializes DSS, starts both
 *          pipelines, spawns one worker thread per pipe, waits for
 *          completion, verifies results, then cleans up.
 *
 *  \param  appObj  [IN] Pointer to the Dss_Object.
 *
 *  \return SystemP_SUCCESS on success, SystemP_FAILURE otherwise.
 */
int32_t TestDisp_multiThreadDisplayControl(Dss_Object *appObj)
{
    int32_t  retVal = FVID2_SOK;
    int32_t  status = SystemP_SUCCESS;
    uint32_t instCnt;
    Dss_InstObject *instObj;

    /* ---- 1. Initialise frame buffers ---- */
    TestDisp_initFrames();

    /* ---- 2. Initialise FVID2 + DSS + DCTRL ---- */
    status = TestDisp_init(appObj);
    if(status != SystemP_SUCCESS)
    {
        DebugP_log("MT Test: TestDisp_init failed!\r\n");
        return status;
    }

    /* ---- 3. Initialise DSS params, pipeline params, configure DCTRL ---- */
    TestDisp_initDssParams(appObj);
    TestDisp_initPipelineParams(appObj);
    retVal = TestDisp_configDctrl(appObj);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("MT Test: DCTRL config failed!\r\n");
        TestDisp_deInit(appObj);
        return SystemP_FAILURE;
    }

    /* ---- 4. Create display driver instances + set params + queue frames ---- */
    for(instCnt = 0U; instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
    {
        instObj = &appObj->instObj[instCnt];

        status = SemaphoreP_constructBinary(&instObj->syncSem, 0);
        if(status != SystemP_SUCCESS)
        {
            retVal = FVID2_EFAIL;
            break;
        }

        Dss_dispCreateParamsInit(&instObj->createParams);
        Fvid2CbParams_init(&instObj->cbParams);
        instObj->cbParams.cbFxn   = &TestDisp_pipeCbFxn;
        instObj->cbParams.appData = instObj;

        instObj->drvHandle = Fvid2_create(
            DSS_DISP_DRV_ID,
            instObj->instId,
            &instObj->createParams,
            &instObj->createStatus,
            &instObj->cbParams);

        if((NULL == instObj->drvHandle) ||
           (instObj->createStatus.retVal != FVID2_SOK))
        {
            DebugP_log("MT Test: Display Create failed for pipe %d!\r\n",
                       instCnt);
            retVal = FVID2_EFAIL;
            break;
        }

        retVal = Fvid2_control(
            instObj->drvHandle,
            IOCTL_DSS_DISP_SET_DSS_PARAMS,
            &instObj->dispParams,
            NULL);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("MT Test: Set DSS Params failed for pipe %d!\r\n",
                       instCnt);
            break;
        }

        retVal = Fvid2_control(
            instObj->drvHandle,
            IOCTL_DSS_DISP_SET_PIPE_MFLAG_PARAMS,
            &instObj->mflagParams,
            NULL);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("MT Test: Set Mflag Params failed for pipe %d!\r\n",
                       instCnt);
            break;
        }

        retVal = TestDisp_allocAndQueueFrames(appObj, instObj);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("MT Test: Alloc/Queue failed for pipe %d!\r\n",
                       instCnt);
            break;
        }
    }

    /* ---- 5. Start both pipelines ---- */
    if(retVal == FVID2_SOK)
    {
        for(instCnt = 0U; instCnt < gDssConfigPipelineParams.numTestPipes;
            instCnt++)
        {
            instObj = &appObj->instObj[instCnt];
            retVal  = Fvid2_start(instObj->drvHandle, NULL);
            if(retVal != FVID2_SOK)
            {
                DebugP_log("MT Test: Display Start failed for pipe %d!\r\n",
                           instCnt);
                break;
            }
        }
    }

    /* ---- 6. Create counting semaphore for thread completion ---- */
    if(retVal == FVID2_SOK)
    {
        status = SemaphoreP_constructCounting(&TestDss_dispMtDoneSem, 0,
                                              TEST_DSS_DD_NUM_THREADS);
        if(status != SystemP_SUCCESS)
        {
            retVal = FVID2_EFAIL;
        }
    }

    /* ---- 7. Spawn one worker thread per pipeline ---- */
    if(retVal == FVID2_SOK)
    {
        uint32_t numThreads = gDssConfigPipelineParams.numTestPipes;
        if(numThreads > TEST_DSS_DD_NUM_THREADS)
        {
            numThreads = TEST_DSS_DD_NUM_THREADS;
        }

        for(instCnt = 0U; instCnt < numThreads; instCnt++)
        {
            TaskP_Params taskParams;

            TestDss_dispMtCtx[instCnt].appObj  = appObj;
            TestDss_dispMtCtx[instCnt].pipeIdx = instCnt;
            TestDss_dispMtCtx[instCnt].result  = SystemP_FAILURE;
            TestDss_dispMtCtx[instCnt].frameCount = 0U;

            TaskP_Params_init(&taskParams);
            taskParams.name      = (instCnt == 0U) ? "DSS_MT_VID" :
                                                      "DSS_MT_VIDL";
            taskParams.stackSize = TEST_DSS_TASK_STACK_SIZE;
            taskParams.stack     = TestDss_dispMtTaskStack[instCnt];
            taskParams.priority  = TEST_DSS_TASK_PRIORITY;
            taskParams.args      = (void *)&TestDss_dispMtCtx[instCnt];
            taskParams.taskMain  = TestDisp_mtPipeWorker;

            status = TaskP_construct(&TestDss_dispMtTaskObj[instCnt],
                                     &taskParams);
            if(status != SystemP_SUCCESS)
            {
                DebugP_log("MT Test: TaskP_construct failed for thread %d!\r\n",
                           instCnt);
                retVal = FVID2_EFAIL;
                break;
            }
        }
    }

    /* ---- 8. Wait for both threads to complete ---- */
    if(retVal == FVID2_SOK)
    {
        uint32_t numThreads = gDssConfigPipelineParams.numTestPipes;
        if(numThreads > TEST_DSS_DD_NUM_THREADS)
        {
            numThreads = TEST_DSS_DD_NUM_THREADS;
        }

        for(instCnt = 0U; instCnt < numThreads; instCnt++)
        {
            SemaphoreP_pend(&TestDss_dispMtDoneSem, SystemP_WAIT_FOREVER);
        }

        /* Destruct tasks and semaphore */
        for(instCnt = 0U; instCnt < numThreads; instCnt++)
        {
            TaskP_destruct(&TestDss_dispMtTaskObj[instCnt]);
        }
        SemaphoreP_destruct(&TestDss_dispMtDoneSem);
    }

    /* ---- 9. Stop both pipelines ---- */
    for(instCnt = 0U; instCnt < gDssConfigPipelineParams.numTestPipes;
        instCnt++)
    {
        instObj = &appObj->instObj[instCnt];
        if(instObj->drvHandle != NULL)
        {
            (void)Fvid2_stop(instObj->drvHandle, NULL);
        }
    }

    /* ---- 10. Delete display driver instances and clean up ---- */
    TestDisp_delete(appObj);
    TestDisp_deInit(appObj);

    /* ---- 11. Aggregate results ---- */
    status = SystemP_SUCCESS;
    {
        uint32_t numThreads = gDssConfigPipelineParams.numTestPipes;
        if(numThreads > TEST_DSS_DD_NUM_THREADS)
        {
            numThreads = TEST_DSS_DD_NUM_THREADS;
        }

        for(instCnt = 0U; instCnt < numThreads; instCnt++)
        {
            if(TestDss_dispMtCtx[instCnt].result != SystemP_SUCCESS)
            {
                DebugP_log("MT Test: Thread %d FAILED\r\n", instCnt);
                status = SystemP_FAILURE;
            }
            else
            {
                uint64_t elapsedUs = TestDss_dispMtCtx[instCnt].endTimeUs -
                                     TestDss_dispMtCtx[instCnt].startTimeUs;
                uint32_t fps = 0U;
                if(elapsedUs > 0U)
                {
                    fps = (uint32_t)((uint64_t)TestDss_dispMtCtx[instCnt].frameCount
                                     * 1000000ULL / elapsedUs);
                }
                DebugP_log("MT Test: Thread %d (%s) OK — %d frames in %d us "
                           "(~%d FPS)\r\n",
                           instCnt,
                           (instCnt == 0U) ? "VID1" : "VIDL1",
                           TestDss_dispMtCtx[instCnt].frameCount,
                           (uint32_t)elapsedUs,
                           fps);
            }
        }
    }

    return status;
}

/**
 * \brief Worker thread for the IOCTL protection test.
 *
 * Waits on the start-barrier, issues the designated DCTRL IOCTL in a loop,
 * records the result, then posts the done-semaphore.
 */
static void TestDisp_mtIoctlWorker(void *arg)
{
    TestDisp_MtIoctlCtx    *ctx    = (TestDisp_MtIoctlCtx *)arg;
    Dss_Object             *appObj = ctx->appObj;
    Dss_DctrlVpCscCoeff     cscCoeff;
    Dss_DctrlVpErrorStats   errStats;
    int32_t                 retVal = FVID2_SOK;
    uint32_t                iter;

    ctx->result    = SystemP_FAILURE;
    ctx->passCount = 0U;

    /* Wait until the main thread releases both threads simultaneously */
    SemaphoreP_pend(&TestDss_mtIoctlStartSem, SystemP_WAIT_FOREVER);

    for(iter = 0U; iter < ctx->loopCount; iter++)
    {
        retVal = FVID2_SOK;

        switch(ctx->subTestId)
        {
            case 0U: /* SET_VP_PARAMS — only valid when VP is IDLE */
                retVal = Fvid2_control(ctx->handle,
                                       IOCTL_DSS_DCTRL_SET_VP_PARAMS,
                                       &appObj->vpParams,
                                       NULL);
                break;

            case 1U: /* SET_OVERLAY_PARAMS */
                retVal = Fvid2_control(ctx->handle,
                                       IOCTL_DSS_DCTRL_SET_OVERLAY_PARAMS,
                                       &appObj->overlayParams,
                                       NULL);
                break;

            case 4U: /* SET_ADV_VP_PARAMS */
                retVal = Fvid2_control(ctx->handle,
                                       IOCTL_DSS_DCTRL_SET_ADV_VP_PARAMS,
                                       &appObj->advVpParams,
                                       NULL);
                break;

            case 5U: /* SET_LAYER_PARAMS */
                retVal = Fvid2_control(ctx->handle,
                                       IOCTL_DSS_DCTRL_SET_LAYER_PARAMS,
                                       &appObj->layerParams,
                                       NULL);
                break;

            case 6U: /* SET_GLOBAL_DSS_PARAMS */
                retVal = Fvid2_control(ctx->handle,
                                       IOCTL_DSS_DCTRL_SET_GLOBAL_DSS_PARAMS,
                                       &appObj->globalDssParams,
                                       NULL);
                break;

            case 7U: /* SET_VP_CSC_COEFF — write-only, no event registration */
                memset(&cscCoeff, 0, sizeof(cscCoeff));
                cscCoeff.vpId  = appObj->vpParams.vpId;
                cscCoeff.cscPos = CSL_DSS_VP_CSC_POS_BEFORE_GAMMA;
                CSL_dssCscCoeffInit(&cscCoeff.cscCoeff);
                retVal = Fvid2_control(ctx->handle,
                                       IOCTL_DSS_DCTRL_SET_VP_CSC_COEFF,
                                       &cscCoeff,
                                       NULL);
                break;

            case 8U: /* GET_VP_ERROR_STATS — read-only */
                memset(&errStats, 0, sizeof(errStats));
                errStats.vpId = appObj->vpParams.vpId;
                retVal = Fvid2_control(ctx->handle,
                                       IOCTL_DSS_DCTRL_GET_VP_ERROR_STATS,
                                       &errStats,
                                       NULL);
                break;

            default:
                retVal = FVID2_EFAIL;
                break;
        }

        if(retVal == FVID2_SOK)
        {
            ctx->passCount++;
        }

        /* Yield to increase chance of interleaving with the other thread */
        TaskP_yield();
    }

    ctx->result = (ctx->passCount == ctx->loopCount) ?
                  SystemP_SUCCESS : SystemP_FAILURE;

    SemaphoreP_post(&TestDss_mtIoctlDoneSem);
    TaskP_exit();
}

/**
 * \brief Spawn two concurrent IOCTL threads, release them together via a
 *        counting start-barrier, wait for both to complete and aggregate results.
 *
 * \param subTest0  subTestId for thread 0
 * \param subTest1  subTestId for thread 1
 * \param h0        DCTRL handle for thread 0
 * \param h1        DCTRL handle for thread 1
 * \param appObj    Shared DSS application object
 * \param loopCount Number of IOCTL iterations per thread
 *
 * \return SystemP_SUCCESS if both threads returned FVID2_SOK for all iterations.
 */
static int32_t TestDisp_runMtIoctlSubtest(uint32_t     subTest0,
                                          uint32_t     subTest1,
                                          Fvid2_Handle h0,
                                          Fvid2_Handle h1,
                                          Dss_Object  *appObj,
                                          uint32_t     loopCount)
{
    int32_t  status = SystemP_SUCCESS;
    uint32_t i;

    status = SemaphoreP_constructCounting(&TestDss_mtIoctlDoneSem, 0,
                                          TEST_DSS_DD_NUM_THREADS);
    if(status != SystemP_SUCCESS)
    {
        return status;
    }

    /* Use COUNTING semaphore with initial count 0 — main thread posts twice */
    status = SemaphoreP_constructCounting(&TestDss_mtIoctlStartSem, 0,
                                          TEST_DSS_DD_NUM_THREADS);
    if(status != SystemP_SUCCESS)
    {
        SemaphoreP_destruct(&TestDss_mtIoctlDoneSem);
        return status;
    }

    TestDss_mtIoctlCtx[0].appObj    = appObj;
    TestDss_mtIoctlCtx[0].handle    = h0;
    TestDss_mtIoctlCtx[0].subTestId = subTest0;
    TestDss_mtIoctlCtx[0].loopCount = loopCount;
    TestDss_mtIoctlCtx[0].result    = SystemP_FAILURE;
    TestDss_mtIoctlCtx[0].passCount = 0U;

    TestDss_mtIoctlCtx[1].appObj    = appObj;
    TestDss_mtIoctlCtx[1].handle    = h1;
    TestDss_mtIoctlCtx[1].subTestId = subTest1;
    TestDss_mtIoctlCtx[1].loopCount = loopCount;
    TestDss_mtIoctlCtx[1].result    = SystemP_FAILURE;
    TestDss_mtIoctlCtx[1].passCount = 0U;

    for(i = 0U; i < TEST_DSS_DD_NUM_THREADS; i++)
    {
        TaskP_Params taskParams;
        TaskP_Params_init(&taskParams);
        taskParams.name      = (i == 0U) ? "MT_IOCTL_T0" : "MT_IOCTL_T1";
        taskParams.stackSize = TEST_DSS_TASK_STACK_SIZE;
        taskParams.stack     = TestDss_mtIoctlTaskStack[i];
        taskParams.priority  = TEST_DSS_TASK_PRIORITY;
        taskParams.args      = (void *)&TestDss_mtIoctlCtx[i];
        taskParams.taskMain  = TestDisp_mtIoctlWorker;

        status = TaskP_construct(&TestDss_mtIoctlTaskObj[i], &taskParams);
        if(status != SystemP_SUCCESS)
        {
            DebugP_log("MT IOCTL: TaskP_construct failed for thread %d\r\n", i);
            SemaphoreP_destruct(&TestDss_mtIoctlDoneSem);
            SemaphoreP_destruct(&TestDss_mtIoctlStartSem);
            return status;
        }
    }

    /* Release both threads simultaneously via counting semaphore */
    SemaphoreP_post(&TestDss_mtIoctlStartSem);
    SemaphoreP_post(&TestDss_mtIoctlStartSem);

    /* Wait for both threads to complete */
    for(i = 0U; i < TEST_DSS_DD_NUM_THREADS; i++)
    {
        SemaphoreP_pend(&TestDss_mtIoctlDoneSem, SystemP_WAIT_FOREVER);
    }

    for(i = 0U; i < TEST_DSS_DD_NUM_THREADS; i++)
    {
        TaskP_destruct(&TestDss_mtIoctlTaskObj[i]);
    }

    SemaphoreP_destruct(&TestDss_mtIoctlDoneSem);
    SemaphoreP_destruct(&TestDss_mtIoctlStartSem);

    if(TestDss_mtIoctlCtx[0].result != SystemP_SUCCESS ||
       TestDss_mtIoctlCtx[1].result != SystemP_SUCCESS)
    {
        status = SystemP_FAILURE;
    }

    return status;
}

/**
 * \brief  Test concurrent DCTRL IOCTL handling from multiple threads with internal locking.
 *
 *  Validates that concurrent DCTRL IOCTLs from two threads are safely serialized by
 *  the driver's internal lockSem without corrupting DSS hardware state. Creates DCTRL
 *  handle and sets graph path with VP remaining IDLE to allow concurrent parameter
 *  configuration. Tests multiple sub-scenarios: dual handle coexistence, concurrent
 *  overlay vs advanced VP parameter updates, concurrent CSC coefficient vs error
 *  statistics queries (write vs read contention), and concurrent layer vs global DSS
 *  parameter updates. After concurrent operations, verifies driver state integrity by
 *  querying VP error statistics to confirm no internal corruption occurred.
 *
 *  \param appObj Pointer to DSS object containing driver handles and configuration.
 *
 *  \return SystemP_SUCCESS on successful concurrent IOCTL handling; SystemP_FAILURE otherwise.
 */
int32_t TestDisp_multiThreadIoctlProtection(Dss_Object *appObj)
{
    int32_t      status       = SystemP_SUCCESS;
    int32_t      retVal       = FVID2_SOK;
    Fvid2_Handle secondHandle = NULL;
    Dss_DctrlVpErrorStats errorStats;

    /* ------------------------------------------------------------------ */
    /* 1. Initialise FVID2 + DSS + DCTRL handle (VP stays IDLE)           */
    /* ------------------------------------------------------------------ */
    TestDisp_initFrames();

    status = TestDisp_init(appObj);
    if(status != SystemP_SUCCESS)
    {
        DebugP_log("MT IOCTL: TestDisp_init failed\r\n");
        return status;
    }

    /* Init VP/overlay params into appObj members (from syscfg globals) */
    TestDisp_initDssParams(appObj);

    /*
     * Only set the graph path — do NOT call SET_VP_PARAMS here because
     * that starts the VP.  We need VP IDLE for the concurrent tests.
     */
    retVal = Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_SET_PATH,
        appObj->dctrlPathInfo,
        NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("MT IOCTL: SET_PATH failed (%d)\r\n", retVal);
        TestDisp_deInit(appObj);
        return SystemP_FAILURE;
    }

    /* Set OLDI params if applicable (does not start VP) */
    if(appObj->oldiParams != NULL)
    {
        retVal = Fvid2_control(
            appObj->dctrlHandle,
            IOCTL_DSS_DCTRL_SET_OLDI_PARAMS,
            appObj->oldiParams,
            NULL);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("MT IOCTL: SET_OLDI_PARAMS failed (%d)\r\n", retVal);
            /* Non-fatal, continue */
        }
    }

    /* ------------------------------------------------------------------ */
    /* Sub-test 1: Second DCTRL handle creation                           */
    /*                                                                    */
    /* Dss_dctrlDrvCreate increments numOpenDrvHandle under lockSem.      */
    /* Both the original and the new handle point to the same instObj,    */
    /* so all subsequent IOCTLs share the same lockSem serialisation.     */
    /* ------------------------------------------------------------------ */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log("Sub-test 1: Second DCTRL handle creation\r\n");

    secondHandle = Fvid2_create(DSS_DCTRL_DRV_ID,
                                DSS_DCTRL_INST_0,
                                NULL,
                                NULL,
                                NULL);
    if(secondHandle == NULL)
    {
        DebugP_log("  FAIL: Second DCTRL handle creation returned NULL\r\n");
        status = SystemP_FAILURE;
    }
    else
    {
        DebugP_log("  PASS: Second DCTRL handle created (numOpenDrvHandle=2)\r\n");
    }

    /* ------------------------------------------------------------------ */
    /* Sub-test 2: Concurrent OVERLAY_PARAMS vs ADV_VP_PARAMS             */
    /*                                                                    */
    /* Neither IOCTL starts the VP, but both acquire/release lockSem.     */
    /* With 10 iterations per thread, there is real contention.           */
    /* ------------------------------------------------------------------ */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log("Sub-test 2: Concurrent SET_OVERLAY_PARAMS / SET_ADV_VP_PARAMS "
               "(%d iters each)\r\n", TEST_DSS_MT_IOCTL_LOOP_COUNT);

    if(status == SystemP_SUCCESS)
    {
        status = TestDisp_runMtIoctlSubtest(
                     1U, 4U,                       /* overlay, adv-vp */
                     appObj->dctrlHandle,
                     secondHandle,
                     appObj,
                     TEST_DSS_MT_IOCTL_LOOP_COUNT);
        if(status == SystemP_SUCCESS)
        {
            DebugP_log("  PASS: T0 overlay pass=%d, T1 adv-vp pass=%d\r\n",
                       TestDss_mtIoctlCtx[0].passCount,
                       TestDss_mtIoctlCtx[1].passCount);
        }
        else
        {
            DebugP_log("  FAIL: Concurrent OVERLAY/ADV_VP IOCTL\r\n");
        }
    }

    /* ------------------------------------------------------------------ */
    /* Sub-test 3: Concurrent SET_VP_CSC_COEFF vs GET_VP_ERROR_STATS      */
    /*                                                                    */
    /* Tests write-IOCTL vs read-IOCTL contention on the same lockSem.   */
    /* Neither registers event handles, so it is safe to loop.            */
    /* ------------------------------------------------------------------ */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log("Sub-test 3: Concurrent SET_VP_CSC_COEFF / GET_VP_ERROR_STATS "
               "(%d iters each)\r\n", TEST_DSS_MT_IOCTL_LOOP_COUNT);

    if(status == SystemP_SUCCESS)
    {
        status = TestDisp_runMtIoctlSubtest(
                     7U, 8U,                       /* csc-coeff, err-stats */
                     appObj->dctrlHandle,
                     secondHandle,
                     appObj,
                     TEST_DSS_MT_IOCTL_LOOP_COUNT);
        if(status == SystemP_SUCCESS)
        {
            DebugP_log("  PASS: T0 csc-coeff pass=%d, T1 err-stats pass=%d\r\n",
                       TestDss_mtIoctlCtx[0].passCount,
                       TestDss_mtIoctlCtx[1].passCount);
        }
        else
        {
            DebugP_log("  FAIL: Concurrent CSC/ERROR_STATS IOCTL\r\n");
        }
    }

    /* ------------------------------------------------------------------ */
    /* Sub-test 4: Concurrent LAYER_PARAMS vs GLOBAL_DSS_PARAMS           */
    /* ------------------------------------------------------------------ */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log("Sub-test 4: Concurrent SET_LAYER_PARAMS / SET_GLOBAL_DSS_PARAMS "
               "(%d iters each)\r\n", TEST_DSS_MT_IOCTL_LOOP_COUNT);

    if(status == SystemP_SUCCESS)
    {
        status = TestDisp_runMtIoctlSubtest(
                     5U, 6U,                       /* layer, global */
                     appObj->dctrlHandle,
                     secondHandle,
                     appObj,
                     TEST_DSS_MT_IOCTL_LOOP_COUNT);
        if(status == SystemP_SUCCESS)
        {
            DebugP_log("  PASS: T0 layer pass=%d, T1 global pass=%d\r\n",
                       TestDss_mtIoctlCtx[0].passCount,
                       TestDss_mtIoctlCtx[1].passCount);
        }
        else
        {
            DebugP_log("  FAIL: Concurrent LAYER/GLOBAL IOCTL\r\n");
        }
    }

    /* ------------------------------------------------------------------ */
    /* Verification readback: query VP error stats to prove driver state   */
    /* is still intact after all the concurrent IOCTL hammering.           */
    /* ------------------------------------------------------------------ */
    DebugP_log("------------------------------------------------------\r\n");
    DebugP_log("Readback: GET_VP_ERROR_STATS after concurrent IOCTLs\r\n");

    if(status == SystemP_SUCCESS)
    {
        memset(&errorStats, 0, sizeof(errorStats));
        errorStats.vpId = appObj->vpParams.vpId;
        retVal = Fvid2_control(
            appObj->dctrlHandle,
            IOCTL_DSS_DCTRL_GET_VP_ERROR_STATS,
            &errorStats,
            NULL);
        if(retVal == FVID2_SOK)
        {
            DebugP_log("  PASS: GET_VP_ERROR_STATS succeeded — driver state OK\r\n");
        }
        else
        {
            DebugP_log("  FAIL: GET_VP_ERROR_STATS returned %d\r\n", retVal);
            status = SystemP_FAILURE;
        }
    }

    /* ------------------------------------------------------------------ */
    /* Cleanup                                                            */
    /* ------------------------------------------------------------------ */
    if(secondHandle != NULL)
    {
        retVal = Fvid2_delete(secondHandle, NULL);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("MT IOCTL: Second DCTRL handle delete failed\r\n");
        }
    }

    /* Clear path before deinit */
    (void)Fvid2_control(
        appObj->dctrlHandle,
        IOCTL_DSS_DCTRL_CLEAR_PATH,
        appObj->dctrlPathInfo,
        NULL);

    TestDisp_deInit(appObj);

    return status;
}

#if !defined (SOC_AM62LX)
/**
 *  \brief  Pipeline callback function for the hot-plug test.
 *
 *  Posts the per-instance syncSem on every VSYNC so the main loop
 *  can dequeue/requeue frames.
 */
static int32_t TestDisp_hpPipeCbFxn(Fvid2_Handle handle, void *appData)
{
    Dss_InstObject *instObj = (Dss_InstObject *)appData;

    GT_assert(DssTrace, (NULL != instObj));
    (void)SemaphoreP_post(&instObj->syncSem);

    return FVID2_SOK;
}

/**
 *  \brief  Run one phase of the hot-plug test: dequeue/requeue for
 *          the specified number of VSYNC intervals on a single pipe.
 *
 *  \param  instObj   [IN] Pipe instance to pump frames on.
 *  \param  numFrames [IN] Number of VSYNC intervals to process.
 *
 *  \return FVID2_SOK on success, error code otherwise.
 */
static int32_t TestDisp_hpPumpFrames(Dss_InstObject *instObj,
                                     uint32_t numFrames)
{
    int32_t retVal = FVID2_SOK;
    Fvid2_FrameList frmList;
    volatile uint32_t loopCount = 0U;

    while(loopCount < numFrames)
    {
        (void)SemaphoreP_pend(&instObj->syncSem, SystemP_WAIT_FOREVER);

        retVal = Fvid2_dequeue(instObj->drvHandle, &frmList,
                               0U, FVID2_TIMEOUT_NONE);
        if(FVID2_SOK == retVal)
        {
            retVal = Fvid2_queue(instObj->drvHandle, &frmList, 0U);
            if(FVID2_SOK != retVal)
            {
                DebugP_log("HP: queue failed on pipe\r\n");
                break;
            }
            loopCount++;
        }
        else if(FVID2_EAGAIN == retVal)
        {
            /* First callback, no frame to dequeue yet */
            retVal = FVID2_SOK;
        }
        else
        {
            DebugP_log("HP: dequeue failed on pipe\r\n");
            break;
        }
    }

    return retVal;
}
#endif

/**
 * \brief  Test dynamic display share with hot-plug and unplug of pipelines.
 *
 *  Tests display share capability by dynamically creating, starting, and stopping
 *  a video pipeline on a VP that already has a video lite pipeline running. Validates
 *  that both pipelines can coexist on the same overlay and VP without disruption,
 *  and that the original pipeline continues unaffected after the second pipeline
 *  is unplugged. Sets up a 4-edge display path with VID and VIDL going through
 *  the same overlay to the same VP. Executes in three phases: single VIDL pipeline
 *  operation, both VID+VIDL running simultaneously, and VIDL-only after VID removal.
 *  Verifies no errors or stats anomalies in each phase.
 *
 *  \param appObj DSS application object containing driver handles and configuration.
 *  \param overlayId Overlay instance to use (CSL_DSS_OVERLAY_ID_1 for OLDI,
 *                   CSL_DSS_OVERLAY_ID_2 for DPI).
 *  \param vpId VP instance to use (CSL_DSS_VP_ID_1 for OLDI, CSL_DSS_VP_ID_2 for DPI).
 *  \param outputNode Output node for path configuration (DSS_DCTRL_NODE_OLDI or DSS_DCTRL_NODE_DPI).
 *
 *  \return SystemP_SUCCESS on successful test execution; SystemP_FAILURE otherwise.
 */
#if !defined (SOC_AM62LX)
int32_t TestDisp_displayShareHotPlug(Dss_Object *appObj,
                                     uint32_t overlayId,
                                     uint32_t vpId,
                                     uint32_t outputNode)
{
    int32_t  retVal  = FVID2_SOK;
    int32_t  status  = SystemP_SUCCESS;
    Dss_InstObject  *vidlObj;    /* pipe index 0 = VIDL (background) */
    Dss_InstObject  *vidObj = NULL;     /* pipe index 1 = VID  (hot-plugged) */

    Dss_DctrlVpParams        *vpParams;
    Dss_DctrlAdvVpParams     *advVpParams;
    Dss_DctrlOverlayParams   *overlayParams;
    Dss_DctrlOverlayLayerParams *layerParams;
    Dss_DctrlGlobalDssParams *globalDssParams;
    Dss_DctrlVpErrorStats     errorStats;
    Dss_DispCurrentStatus     vidlCurrStatus;
    Fvid2_FrameList           frmList;

    /* Local 4-edge path for both pipes on same VP */
    Dss_DctrlPathInfo hotPlugPath;

    uint32_t ovrNode;
    uint32_t vpNode;

    /* ------------------------------------------------------------------ */
    /* 0. Validate that 2 pipes are configured                            */
    /* ------------------------------------------------------------------ */
    if(gDssConfigPipelineParams.numTestPipes < 2U)
    {
        DebugP_log("HP: Need 2 pipes configured, have %d — SKIPPED\r\n",
                   gDssConfigPipelineParams.numTestPipes);
        return SystemP_SUCCESS;  /* Not an error, just not applicable */
    }

    /* Derive graph node IDs from the overlay ID */
    if(overlayId == CSL_DSS_OVERLAY_ID_1)
    {
        ovrNode = DSS_DCTRL_NODE_OVR1;
        vpNode  = DSS_DCTRL_NODE_VP1;
    }
    else
    {
        ovrNode = DSS_DCTRL_NODE_OVR2;
        vpNode  = DSS_DCTRL_NODE_VP2;
    }

    /* ------------------------------------------------------------------ */
    /* 1. Initialise frames + FVID2 + DSS + DCTRL handle                  */
    /* ------------------------------------------------------------------ */
    TestDisp_initFrames();

    status = TestDisp_init(appObj);
    if(status != SystemP_SUCCESS)
    {
        DebugP_log("HP: TestDisp_init failed\r\n");
        return SystemP_FAILURE;
    }

    /* ------------------------------------------------------------------ */
    /* 2. Set 4-edge path:                                                */
    /*    VID1→OVR, VIDL1→OVR, OVR→VP, VP→output                         */
    /* ------------------------------------------------------------------ */
    Dss_dctrlPathInfoInit(&hotPlugPath);
    hotPlugPath.numEdges = 4U;
    hotPlugPath.edgeInfo[0U].startNode = DSS_DCTRL_NODE_VID1;
    hotPlugPath.edgeInfo[0U].endNode   = ovrNode;
    hotPlugPath.edgeInfo[1U].startNode = DSS_DCTRL_NODE_VIDL1;
    hotPlugPath.edgeInfo[1U].endNode   = ovrNode;
    hotPlugPath.edgeInfo[2U].startNode = ovrNode;
    hotPlugPath.edgeInfo[2U].endNode   = vpNode;
    hotPlugPath.edgeInfo[3U].startNode = vpNode;
    hotPlugPath.edgeInfo[3U].endNode   = outputNode;

    retVal = Fvid2_control(appObj->dctrlHandle,
                           IOCTL_DSS_DCTRL_SET_PATH,
                           &hotPlugPath, NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("HP: SET_PATH (4-edge) failed (%d)\r\n", retVal);
        TestDisp_deInit(appObj);
        return SystemP_FAILURE;
    }

    DebugP_log("HP: 4-edge path set (VID1+VIDL1 → OVR%d → VP%d → %s)\r\n",
               (overlayId == CSL_DSS_OVERLAY_ID_1) ? 1 : 2,
               (vpId == CSL_DSS_VP_ID_1) ? 1 : 2,
               (outputNode == DSS_DCTRL_NODE_OLDI) ? "OLDI" : "DPI");

    /* ------------------------------------------------------------------ */
    /* 3. Configure VP, overlay, layer, adv VP, global DSS params         */
    /* ------------------------------------------------------------------ */
    vpParams        = &appObj->vpParams;
    advVpParams     = &appObj->advVpParams;
    overlayParams   = &appObj->overlayParams;
    layerParams     = &appObj->layerParams;
    globalDssParams = &appObj->globalDssParams;

    /* Copy from syscfg globals (TestDisp_initDssParams sets these) */
    TestDisp_initDssParams(appObj);

    /* Override VP and overlay IDs to the caller-specified values */
    vpParams->vpId          = vpId;
    advVpParams->vpId       = vpId;
    overlayParams->overlayId = overlayId;
    layerParams->overlayId   = overlayId;

    retVal = Fvid2_control(appObj->dctrlHandle,
                           IOCTL_DSS_DCTRL_SET_ADV_VP_PARAMS,
                           advVpParams, NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("HP: SET_ADV_VP_PARAMS failed\r\n");
    }

    if(retVal == FVID2_SOK)
    {
        retVal = Fvid2_control(appObj->dctrlHandle,
                               IOCTL_DSS_DCTRL_SET_VP_PARAMS,
                               vpParams, NULL);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("HP: SET_VP_PARAMS failed\r\n");
        }
    }

    /* Set OLDI params if applicable */
    if((retVal == FVID2_SOK) && (appObj->oldiParams != NULL) &&
       (outputNode == DSS_DCTRL_NODE_OLDI))
    {
        retVal = Fvid2_control(appObj->dctrlHandle,
                               IOCTL_DSS_DCTRL_SET_OLDI_PARAMS,
                               appObj->oldiParams, NULL);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("HP: SET_OLDI_PARAMS failed\r\n");
        }
    }

    if(retVal == FVID2_SOK)
    {
        retVal = Fvid2_control(appObj->dctrlHandle,
                               IOCTL_DSS_DCTRL_SET_OVERLAY_PARAMS,
                               overlayParams, NULL);
    }

    if(retVal == FVID2_SOK)
    {
        retVal = Fvid2_control(appObj->dctrlHandle,
                               IOCTL_DSS_DCTRL_SET_LAYER_PARAMS,
                               layerParams, NULL);
    }

    if(retVal == FVID2_SOK)
    {
        retVal = Fvid2_control(appObj->dctrlHandle,
                               IOCTL_DSS_DCTRL_SET_GLOBAL_DSS_PARAMS,
                               globalDssParams, NULL);
    }

    if(retVal != FVID2_SOK)
    {
        DebugP_log("HP: DCTRL configuration failed\r\n");
        (void)Fvid2_control(appObj->dctrlHandle,
                            IOCTL_DSS_DCTRL_CLEAR_PATH,
                            &hotPlugPath, NULL);
        TestDisp_deInit(appObj);
        return SystemP_FAILURE;
    }

    /* ------------------------------------------------------------------ */
    /* 4. Initialise pipeline params for both pipes, then create VIDL     */
    /*    (pipe index 0) and start it                                     */
    /* ------------------------------------------------------------------ */
    TestDisp_initPipelineParams(appObj);

    /* --- Create VIDL (instObj[0]) --- */
    vidlObj = &appObj->instObj[0];

    status = SemaphoreP_constructBinary(&vidlObj->syncSem, 0);
    if(status != SystemP_SUCCESS)
    {
        retVal = FVID2_EFAIL;
    }

    if(retVal == FVID2_SOK)
    {
        Dss_dispCreateParamsInit(&vidlObj->createParams);
        Fvid2CbParams_init(&vidlObj->cbParams);
        vidlObj->cbParams.cbFxn   = &TestDisp_hpPipeCbFxn;
        vidlObj->cbParams.appData = vidlObj;

        vidlObj->drvHandle = Fvid2_create(
            DSS_DISP_DRV_ID, vidlObj->instId,
            &vidlObj->createParams, &vidlObj->createStatus,
            &vidlObj->cbParams);

        if((NULL == vidlObj->drvHandle) ||
           (vidlObj->createStatus.retVal != FVID2_SOK))
        {
            DebugP_log("HP: VIDL create failed\r\n");
            retVal = FVID2_EFAIL;
        }
    }

    if(retVal == FVID2_SOK)
    {
        retVal = Fvid2_control(vidlObj->drvHandle,
                               IOCTL_DSS_DISP_SET_DSS_PARAMS,
                               &vidlObj->dispParams, NULL);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("HP: VIDL set params failed\r\n");
        }
    }

    if(retVal == FVID2_SOK)
    {
        Dss_dispPipeMflagParamsInit(&vidlObj->mflagParams);
        retVal = Fvid2_control(vidlObj->drvHandle,
                               IOCTL_DSS_DISP_SET_PIPE_MFLAG_PARAMS,
                               &vidlObj->mflagParams, NULL);
    }

    if(retVal == FVID2_SOK)
    {
        retVal = TestDisp_allocAndQueueFrames(appObj, vidlObj);
    }

    if(retVal == FVID2_SOK)
    {
        retVal = Fvid2_start(vidlObj->drvHandle, NULL);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("HP: VIDL start failed\r\n");
        }
    }

    if(retVal != FVID2_SOK)
    {
        DebugP_log("HP: Failed to bring up VIDL pipeline — aborting\r\n");
        status = SystemP_FAILURE;
    }

    /* ------------------------------------------------------------------ */
    /* 5. Phase 1: VIDL running alone — pump frames for N intervals       */
    /* ------------------------------------------------------------------ */
    if(status == SystemP_SUCCESS)
    {
        DebugP_log("HP Phase 1: VIDL running alone (%d frames)\r\n",
                   TEST_DSS_HP_PHASE_FRAMES);

        retVal = TestDisp_hpPumpFrames(vidlObj, TEST_DSS_HP_PHASE_FRAMES);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("HP: Phase 1 VIDL pump failed\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            DebugP_log("HP Phase 1: PASS — VIDL displayed %d frames\r\n",
                       TEST_DSS_HP_PHASE_FRAMES);
        }
    }

    /* ------------------------------------------------------------------ */
    /* 6. Phase 2a: HOT-PLUG — Create VID (instObj[1]), set params, start */
    /* ------------------------------------------------------------------ */
    if(status == SystemP_SUCCESS)
    {
        DebugP_log("HP Phase 2: Hot-plugging VID pipeline\r\n");

        vidObj  = &appObj->instObj[1];

        retVal = (int32_t)SemaphoreP_constructBinary(&vidObj->syncSem, 0);
        if(retVal != (int32_t)SystemP_SUCCESS)
        {
            status = SystemP_FAILURE;
        }
    }

    if(status == SystemP_SUCCESS)
    {
        Dss_dispCreateParamsInit(&vidObj->createParams);
        Fvid2CbParams_init(&vidObj->cbParams);
        vidObj->cbParams.cbFxn   = &TestDisp_hpPipeCbFxn;
        vidObj->cbParams.appData = vidObj;

        vidObj->drvHandle = Fvid2_create(
            DSS_DISP_DRV_ID, vidObj->instId,
            &vidObj->createParams, &vidObj->createStatus,
            &vidObj->cbParams);

        if((NULL == vidObj->drvHandle) ||
           (vidObj->createStatus.retVal != FVID2_SOK))
        {
            DebugP_log("HP: VID create failed\r\n");
            status = SystemP_FAILURE;
        }
    }

    if(status == SystemP_SUCCESS)
    {
        retVal = Fvid2_control(vidObj->drvHandle,
                               IOCTL_DSS_DISP_SET_DSS_PARAMS,
                               &vidObj->dispParams, NULL);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("HP: VID set params failed\r\n");
            status = SystemP_FAILURE;
        }
    }

    if(status == SystemP_SUCCESS)
    {
        Dss_dispPipeMflagParamsInit(&vidObj->mflagParams);
        retVal = Fvid2_control(vidObj->drvHandle,
                               IOCTL_DSS_DISP_SET_PIPE_MFLAG_PARAMS,
                               &vidObj->mflagParams, NULL);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("HP: VID mflag failed\r\n");
            status = SystemP_FAILURE;
        }
    }

    if(status == SystemP_SUCCESS)
    {
        retVal = TestDisp_allocAndQueueFrames(appObj, vidObj);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("HP: VID alloc/queue failed\r\n");
            status = SystemP_FAILURE;
        }
    }

    if(status == SystemP_SUCCESS)
    {
        retVal = Fvid2_start(vidObj->drvHandle, NULL);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("HP: VID start failed\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            DebugP_log("HP Phase 2: VID hot-plugged — both pipes running\r\n");
        }
    }

    /* ------------------------------------------------------------------ */
    /* 7. Phase 2b: Both VID + VIDL running — pump frames on both         */
    /* ------------------------------------------------------------------ */
    if(status == SystemP_SUCCESS)
    {
        uint32_t loopCount = 0U;

        while(loopCount < TEST_DSS_HP_PHASE_FRAMES)
        {
            /* VIDL */
            (void)SemaphoreP_pend(&vidlObj->syncSem, SystemP_WAIT_FOREVER);
            retVal = Fvid2_dequeue(vidlObj->drvHandle, &frmList,
                                   0U, FVID2_TIMEOUT_NONE);
            if(FVID2_SOK == retVal)
            {
                retVal = Fvid2_queue(vidlObj->drvHandle, &frmList, 0U);
            }
            else if(FVID2_EAGAIN == retVal)
            {
                retVal = FVID2_SOK;
            }

            if(retVal != FVID2_SOK)
            {
                DebugP_log("HP Phase 2: VIDL pump error\r\n");
                break;
            }

            /* VID */
            (void)SemaphoreP_pend(&vidObj->syncSem, SystemP_WAIT_FOREVER);
            retVal = Fvid2_dequeue(vidObj->drvHandle, &frmList,
                                   0U, FVID2_TIMEOUT_NONE);
            if(FVID2_SOK == retVal)
            {
                retVal = Fvid2_queue(vidObj->drvHandle, &frmList, 0U);
            }
            else if(FVID2_EAGAIN == retVal)
            {
                retVal = FVID2_SOK;
            }

            if(retVal != FVID2_SOK)
            {
                DebugP_log("HP Phase 2: VID pump error\r\n");
                break;
            }

            loopCount++;
        }

        if(retVal != FVID2_SOK)
        {
            status = SystemP_FAILURE;
        }
        else
        {
            DebugP_log("HP Phase 2: PASS — both pipes displayed %d frames\r\n",
                       TEST_DSS_HP_PHASE_FRAMES);
        }
    }

    /* ------------------------------------------------------------------ */
    /* 8. Phase 3a: UNPLUG — Stop VID, drain, delete                      */
    /* ------------------------------------------------------------------ */
    if(status == SystemP_SUCCESS)
    {
        DebugP_log("HP Phase 3: Unplugging VID pipeline\r\n");

        retVal = Fvid2_stop(vidObj->drvHandle, NULL);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("HP: VID stop failed\r\n");
            status = SystemP_FAILURE;
        }
    }

    if((vidObj != NULL) && (vidObj->drvHandle != NULL) && (status == SystemP_SUCCESS))
    {
        /* Drain remaining VID frames */
        while(FVID2_SOK == Fvid2_dequeue(vidObj->drvHandle, &frmList,
                                          0U, FVID2_TIMEOUT_NONE))
        {
            /* discard */
        }

        retVal = Fvid2_delete(vidObj->drvHandle, NULL);
        vidObj->drvHandle = NULL;
        if(retVal != FVID2_SOK)
        {
            DebugP_log("HP: VID delete failed\r\n");
            status = SystemP_FAILURE;
        }

        SemaphoreP_destruct(&vidObj->syncSem);

        DebugP_log("HP Phase 3: VID unplugged — VIDL continues\r\n");
    }

    /* ------------------------------------------------------------------ */
    /* 9. Phase 3b: VIDL continues alone — pump for N more frames         */
    /* ------------------------------------------------------------------ */
    if(status == SystemP_SUCCESS)
    {
        retVal = TestDisp_hpPumpFrames(vidlObj, TEST_DSS_HP_PHASE_FRAMES);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("HP: Phase 3 VIDL pump failed\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            DebugP_log("HP Phase 3: PASS — VIDL continued %d frames "
                       "after VID unplug\r\n", TEST_DSS_HP_PHASE_FRAMES);
        }
    }

    /* ------------------------------------------------------------------ */
    /* 10. Cleanup                                                        */
    /* ------------------------------------------------------------------ */

    /* Stop VIDL if still running */
    if(vidlObj->drvHandle != NULL)
    {
        (void)Fvid2_stop(vidlObj->drvHandle, NULL);

        /* Drain VIDL frames */
        while(FVID2_SOK == Fvid2_dequeue(vidlObj->drvHandle, &frmList,
                                          0U, FVID2_TIMEOUT_NONE))
        {
            /* discard */
        }

        /* Get VIDL status before delete */
        memset(&vidlCurrStatus, 0, sizeof(vidlCurrStatus));
        (void)Fvid2_control(vidlObj->drvHandle,
                            IOCTL_DSS_DISP_GET_CURRENT_STATUS,
                            &vidlCurrStatus, NULL);
        DebugP_log("HP: VIDL underflowCount=%d, repeatFrmCount=%d\r\n",
                   vidlCurrStatus.underflowCount,
                   vidlCurrStatus.repeatFrmCount);

        (void)Fvid2_delete(vidlObj->drvHandle, NULL);
        vidlObj->drvHandle = NULL;
    }

    SemaphoreP_destruct(&vidlObj->syncSem);

    /* Stop VID if it was not already cleaned up (error path) */
    if(vidObj != NULL && vidObj->drvHandle != NULL)
    {
        (void)Fvid2_stop(vidObj->drvHandle, NULL);
        while(FVID2_SOK == Fvid2_dequeue(vidObj->drvHandle, &frmList,
                                          0U, FVID2_TIMEOUT_NONE))
        {
            /* discard */
        }
        (void)Fvid2_delete(vidObj->drvHandle, NULL);
        vidObj->drvHandle = NULL;
        SemaphoreP_destruct(&vidObj->syncSem);
    }

    /* VP error stats */
    memset(&errorStats, 0, sizeof(errorStats));
    errorStats.vpId = vpId;
    retVal = Fvid2_control(appObj->dctrlHandle,
                           IOCTL_DSS_DCTRL_GET_VP_ERROR_STATS,
                           &errorStats, NULL);
    if(retVal == FVID2_SOK)
    {
        DebugP_log("HP: VP syncLost=%d\r\n", errorStats.syncLost);
        if(errorStats.syncLost > 0U)
        {
            DebugP_log("HP: WARNING — sync lost detected\r\n");
        }
    }

    /* Clear path */
    (void)Fvid2_control(appObj->dctrlHandle,
                         IOCTL_DSS_DCTRL_CLEAR_PATH,
                         &hotPlugPath, NULL);

    /* Stop VP */
    vpParams->vpId = vpId;
    (void)Fvid2_control(appObj->dctrlHandle,
                         IOCTL_DSS_DCTRL_STOP_VP,
                         vpParams, NULL);

    TestDisp_deInit(appObj);

    return status;
}
#endif

/* ========================================================================== */
/*       Dual Display DPI + OLDI Multi-Threaded Test (TC21)                   */
/* ========================================================================== */

#if defined (SOC_AM62PX)

/**
 *  \brief  Per-thread context for the dual-display test.
 *
 *  Each thread owns one pipeline on one VP.  Thread 0 operates the OLDI
 *  pipeline (instObj[0] from appObjOldi), Thread 1 operates the DPI
 *  pipeline (instObj[0] from appObjDpi).
 */

/**
 *  \brief  Pipeline callback for dual-display test.
 */
static int32_t TestDisp_ddPipeCbFxn(Fvid2_Handle handle, void *appData)
{
    Dss_InstObject *instObj = (Dss_InstObject *)appData;

    GT_assert(DssTrace, (NULL != instObj));
    (void)SemaphoreP_post(&instObj->syncSem);

    return FVID2_SOK;
}

/**
 * \brief  Worker thread for dual-display pipeline frame pumping.
 *
 *  Waits on start barrier semaphore for synchronization with main thread and peer thread,
 *  then continuously dequeues and requeues frames on its assigned pipeline for specified
 *  iteration count. Records frame count and timestamps to calculate throughput and FPS.
 *  Logs errors and updates result status on queue/dequeue failures. Posts done semaphore
 *  on completion to signal main thread that worker thread finished.
 *
 *  \param arg Pointer to TestDisp_DdThreadCtx structure containing pipeline instance,
 *             thread index, and context for result tracking.
 *
 *  \return None.
 */
static void TestDisp_ddPipeWorker(void *arg)
{
    TestDisp_DdThreadCtx *ctx = (TestDisp_DdThreadCtx *)arg;
    Dss_InstObject *instObj = ctx->instObj;
    Fvid2_FrameList frmList;
    int32_t retVal;
    uint32_t loopCount = 0U;

    ctx->result     = SystemP_SUCCESS;
    ctx->frameCount = 0U;

    /* Wait for main to release both threads simultaneously */
    SemaphoreP_pend(&TestDss_dispDdStartSem, SystemP_WAIT_FOREVER);

    ctx->startTimeUs = ClockP_getTimeUsec();

    while(loopCount < TEST_DSS_DD_NUM_FRAMES)
    {
        (void)SemaphoreP_pend(&instObj->syncSem, SystemP_WAIT_FOREVER);

        retVal = Fvid2_dequeue(instObj->drvHandle, &frmList,
                               0U, FVID2_TIMEOUT_NONE);
        if(FVID2_SOK == retVal)
        {
            retVal = Fvid2_queue(instObj->drvHandle, &frmList, 0U);
            if(FVID2_SOK != retVal)
            {
                DebugP_log("DD Thread %d: Queue failed at iter %d!\r\n",
                           ctx->threadIdx, loopCount);
                ctx->result = SystemP_FAILURE;
                break;
            }
            ctx->frameCount++;
            loopCount++;
        }
        else if(FVID2_EAGAIN == retVal)
        {
            /* First callback, no frame to dequeue yet */
        }
        else
        {
            DebugP_log("DD Thread %d: Dequeue failed at iter %d!\r\n",
                       ctx->threadIdx, loopCount);
            ctx->result = SystemP_FAILURE;
            break;
        }
    }

    ctx->endTimeUs = ClockP_getTimeUsec();

    SemaphoreP_post(&TestDss_dispDdDoneSem);
    TaskP_exit();
}

/**
 *  \brief  Helper: configure one VP/Overlay from a Dss_Object's syscfg globals
 *          and apply the DCTRL IOCTLs.
 *
 *  \param  dctrlHandle  [IN] Shared DCTRL handle
 *  \param  appObj       [IN] Dss_Object whose vpParams / overlayParams etc.
 *                            will be initialised and applied
 *  \param  setOldi      [IN] TRUE to also call IOCTL_DSS_DCTRL_SET_OLDI_PARAMS
 *
 *  \return FVID2_SOK on success
 */
static int32_t TestDisp_ddConfigOneVp(Fvid2_Handle dctrlHandle,
                                      Dss_Object  *appObj,
                                      uint32_t     setOldi)
{
    int32_t retVal;

    /* NOTE: vpParams / overlayParams / advVpParams / layerParams / globalDssParams
     * inside appObj MUST be pre-populated by the caller before invoking this
     * function.  TestDisp_dualDisplayDpiOldi does this explicitly for each
     * instance so that per-instance syscfg globals (VP1 vs VP2, OVR1 vs OVR2)
     * are used correctly. */

    retVal = Fvid2_control(dctrlHandle, IOCTL_DSS_DCTRL_SET_PATH,
                           appObj->dctrlPathInfo, NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DD: SET_PATH failed\r\n");
        return retVal;
    }

    retVal = Fvid2_control(dctrlHandle, IOCTL_DSS_DCTRL_SET_ADV_VP_PARAMS,
                           &appObj->advVpParams, NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DD: SET_ADV_VP_PARAMS failed\r\n");
        return retVal;
    }

    retVal = Fvid2_control(dctrlHandle, IOCTL_DSS_DCTRL_SET_VP_PARAMS,
                           &appObj->vpParams, NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DD: SET_VP_PARAMS failed\r\n");
        return retVal;
    }

    if((setOldi == TRUE) && (appObj->oldiParams != NULL))
    {
        retVal = Fvid2_control(dctrlHandle, IOCTL_DSS_DCTRL_SET_OLDI_PARAMS,
                               appObj->oldiParams, NULL);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("DD: SET_OLDI_PARAMS failed\r\n");
            return retVal;
        }
    }

    retVal = Fvid2_control(dctrlHandle, IOCTL_DSS_DCTRL_SET_OVERLAY_PARAMS,
                           &appObj->overlayParams, NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DD: SET_OVERLAY_PARAMS failed\r\n");
        return retVal;
    }

    retVal = Fvid2_control(dctrlHandle, IOCTL_DSS_DCTRL_SET_LAYER_PARAMS,
                           &appObj->layerParams, NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DD: SET_LAYER_PARAMS failed\r\n");
        return retVal;
    }

    retVal = Fvid2_control(dctrlHandle, IOCTL_DSS_DCTRL_SET_GLOBAL_DSS_PARAMS,
                           &appObj->globalDssParams, NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DD: SET_GLOBAL_DSS_PARAMS failed\r\n");
    }

    return retVal;
}

/**
 *  \brief  Helper: create a display-driver instance for one pipe, set params,
 *          queue frames and start.
 *
 *  \param  appObj   [IN]  The Dss_Object that owns the pipeline
 *  \param  instObj  [IN]  Specific instObj to create / start
 *
 *  \return FVID2_SOK on success
 */
static int32_t TestDisp_ddCreateAndStartPipe(Dss_Object     *appObj,
                                             Dss_InstObject  *instObj)
{
    int32_t retVal = FVID2_SOK;
    int32_t status;

    status = SemaphoreP_constructBinary(&instObj->syncSem, 0);
    if(status != SystemP_SUCCESS)
    {
        return FVID2_EFAIL;
    }

    Dss_dispCreateParamsInit(&instObj->createParams);
    Fvid2CbParams_init(&instObj->cbParams);
    instObj->cbParams.cbFxn   = &TestDisp_ddPipeCbFxn;
    instObj->cbParams.appData = instObj;

    instObj->drvHandle = Fvid2_create(
        DSS_DISP_DRV_ID, instObj->instId,
        &instObj->createParams, &instObj->createStatus,
        &instObj->cbParams);

    if((NULL == instObj->drvHandle) ||
       (instObj->createStatus.retVal != FVID2_SOK))
    {
        DebugP_log("DD: pipe create failed (instId=%d)\r\n", instObj->instId);
        return FVID2_EFAIL;
    }

    retVal = Fvid2_control(instObj->drvHandle,
                           IOCTL_DSS_DISP_SET_DSS_PARAMS,
                           &instObj->dispParams, NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DD: SET_DSS_PARAMS failed\r\n");
        return retVal;
    }

    Dss_dispPipeMflagParamsInit(&instObj->mflagParams);
    retVal = Fvid2_control(instObj->drvHandle,
                           IOCTL_DSS_DISP_SET_PIPE_MFLAG_PARAMS,
                           &instObj->mflagParams, NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DD: SET_PIPE_MFLAG_PARAMS failed\r\n");
        return retVal;
    }

    retVal = TestDisp_allocAndQueueFrames(appObj, instObj);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DD: alloc/queue failed\r\n");
        return retVal;
    }

    retVal = Fvid2_start(instObj->drvHandle, NULL);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DD: Fvid2_start failed\r\n");
    }

    return retVal;
}

/**
 *  \brief  Helper: stop, drain, delete a single display pipe and destruct its
 *          semaphore.  Safe to call even if the pipe was never started.
 */
static void TestDisp_ddStopAndDeletePipe(Dss_InstObject *instObj,
                                         const char     *tag)
{
    Fvid2_FrameList      frmList;
    Dss_DispCurrentStatus currStatus;

    if((instObj == NULL) || (instObj->drvHandle == NULL))
    {
        return;
    }

    (void)Fvid2_stop(instObj->drvHandle, NULL);

    /* Drain remaining frames */
    while(FVID2_SOK == Fvid2_dequeue(instObj->drvHandle, &frmList,
                                      0U, FVID2_TIMEOUT_NONE))
    {
        /* discard */
    }

    memset(&currStatus, 0, sizeof(currStatus));
    (void)Fvid2_control(instObj->drvHandle,
                        IOCTL_DSS_DISP_GET_CURRENT_STATUS,
                        &currStatus, NULL);
    DebugP_log("DD: %s underflowCount=%d, repeatFrmCount=%d\r\n",
               tag, currStatus.underflowCount, currStatus.repeatFrmCount);

    (void)Fvid2_delete(instObj->drvHandle, NULL);
    instObj->drvHandle = NULL;
    SemaphoreP_destruct(&instObj->syncSem);
}

/**
 *  \brief  Dual Display DPI + OLDI test (TC21).
 *
 *  Configures two independent display paths on a single DSS hardware:
 *    - VP1 → OVR1 → OLDI  with pipe instObj[0] from appObjOldi
 *    - VP2 → OVR2 → DPI   with pipe instObj[0] from appObjDpi
 *
 *  Both are started, and then two worker threads pump frames concurrently
 *  so that visuals appear on both the OLDI panel and the DPI/HDMI monitor
 *  simultaneously.  After TEST_DSS_DD_NUM_FRAMES iterations the threads exit,
 *  error stats are checked, and everything is cleaned up.
 *
 *  Prerequisites (syscfg):
 *    - appObjOldi (CONFIG_DSS0): VP1, OVR1, OLDI output, one pipe (e.g. VID1).
 *    - appObjDpi  (CONFIG_DSS1): VP2, OVR2, DPI output,  one pipe (e.g. VIDL1).
 *    - The two instances must use different pipe IDs.
 *
 *  \param  appObjOldi  [IN] Dss_Object for the OLDI instance
 *  \param  appObjDpi   [IN] Dss_Object for the DPI instance
 *
 *  \return SystemP_SUCCESS on success, SystemP_FAILURE otherwise.
 */
int32_t TestDisp_dualDisplayDpiOldi(Dss_Object *appObjOldi,
                                    Dss_Object *appObjDpi)
{
    int32_t  retVal  = FVID2_SOK;
    int32_t  status  = SystemP_SUCCESS;
    Fvid2_InitPrms   initPrms;
    Fvid2_Handle      dctrlHandle = NULL;

    Dss_InstObject   *oldiPipeObj = NULL;   /* instObj[0] of OLDI Dss_Object */
    Dss_InstObject   *dpiPipeObj = NULL;    /* instObj[0] of DPI  Dss_Object */

    Dss_DctrlVpParams        vpStopParams;
    Dss_DctrlVpErrorStats    errorStats;

    DebugP_log("DD: ======================================================\r\n");
    DebugP_log("DD: Dual Display DPI + OLDI Multi-Threaded Test (TC21)\r\n");
    DebugP_log("DD: ======================================================\r\n");

    /* ------------------------------------------------------------------ */
    /* 1.  Initialise frame buffers                                       */
    /* ------------------------------------------------------------------ */
    TestDisp_initFrames();

    /* ------------------------------------------------------------------ */
    /* 2.  Initialise FVID2, DSS, create single shared DCTRL handle       */
    /* ------------------------------------------------------------------ */
    Fvid2InitPrms_init(&initPrms);
    retVal = Fvid2_init(&initPrms);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DD: Fvid2_init failed\r\n");
        return SystemP_FAILURE;
    }

    Dss_initParamsInit(&appObjOldi->initParams);
    Dss_init(&appObjOldi->initParams);

    dctrlHandle = Fvid2_create(DSS_DCTRL_DRV_ID, DSS_DCTRL_INST_0,
                               NULL, NULL, NULL);
    if(NULL == dctrlHandle)
    {
        DebugP_log("DD: DCTRL create failed\r\n");
        Dss_deInit();
        Fvid2_deInit(NULL);
        return SystemP_FAILURE;
    }

    /* Store handle in both objects for helper convenience */
    appObjOldi->dctrlHandle = dctrlHandle;
    appObjDpi->dctrlHandle  = dctrlHandle;

    /* Set OLDI Tx Power Down */
    if(appObjOldi->oldiParams != NULL)
    {
        Dss_setOLDITxPowerDown(
            appObjOldi->oldiParams->oldiCfg.oldiMapType, TRUE);
    }

    /* ------------------------------------------------------------------ */
    /* 3.  Pre-populate per-instance DSS params, then configure each VP   */
    /*                                                                    */
    /* TestDisp_initDssParams uses the single-instance syscfg globals     */
    /* (gDssVpParams, gDssOverlayParams, …) which are correct for the     */
    /* OLDI instance (VP1/OVR1).  For the DPI instance (VP2/OVR2) the    */
    /* caller (TestDss_dualDisplayDpiOldiMt) must have already written    */
    /* appObjDpi->vpParams / overlayParams / layerParams / advVpParams    */
    /* / globalDssParams from the per-instance DPI syscfg globals BEFORE  */
    /* calling this function.                                             */
    /* ------------------------------------------------------------------ */
    TestDisp_initDssParams(appObjOldi);   /* VP1 / OVR1 from syscfg globals */
    /* appObjDpi params are pre-populated by the test wrapper */

    /* ------------------------------------------------------------------ */
    /* 3. Configure VP1 (OLDI)                                            */
    /* ------------------------------------------------------------------ */
    retVal = TestDisp_ddConfigOneVp(dctrlHandle, appObjOldi, TRUE);
    if(retVal != FVID2_SOK)
    {
        DebugP_log("DD: OLDI VP configuration failed\r\n");
        status = SystemP_FAILURE;
    }
    else
    {
        DebugP_log("DD: VP1 (OLDI) configured — vpId=%d, overlayId=%d\r\n",
                   appObjOldi->vpParams.vpId,
                   appObjOldi->overlayParams.overlayId);
    }

    /* ------------------------------------------------------------------ */
    /* 4. Configure VP2 (DPI)                                             */
    /* ------------------------------------------------------------------ */
    if(status == SystemP_SUCCESS)
    {
        retVal = TestDisp_ddConfigOneVp(dctrlHandle, appObjDpi, FALSE);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("DD: DPI VP configuration failed\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            DebugP_log("DD: VP2 (DPI) configured — vpId=%d, overlayId=%d\r\n",
                       appObjDpi->vpParams.vpId,
                       appObjDpi->overlayParams.overlayId);
        }
    }

    /* ------------------------------------------------------------------ */
    /* 5. Initialise pipeline params, create + start both pipes           */
    /* ------------------------------------------------------------------ */
    if(status == SystemP_SUCCESS)
    {
        TestDisp_initPipelineParams(appObjOldi);
        TestDisp_initPipelineParams(appObjDpi);

        oldiPipeObj = &appObjOldi->instObj[0];
        dpiPipeObj  = &appObjDpi->instObj[1];

        retVal = TestDisp_ddCreateAndStartPipe(appObjOldi, oldiPipeObj);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("DD: OLDI pipe create/start failed\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            DebugP_log("DD: OLDI pipe started (instId=%d)\r\n",
                       oldiPipeObj->instId);
        }
    }

    if(status == SystemP_SUCCESS)
    {
        retVal = TestDisp_ddCreateAndStartPipe(appObjDpi, dpiPipeObj);
        if(retVal != FVID2_SOK)
        {
            DebugP_log("DD: DPI pipe create/start failed\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            DebugP_log("DD: DPI pipe started (instId=%d)\r\n",
                       dpiPipeObj->instId);
            DebugP_log("DD: Both pipelines running — OLDI + DPI\r\n");
        }
    }

    /* ------------------------------------------------------------------ */
    /* 6. Create semaphores and spawn one worker thread per VP            */
    /* ------------------------------------------------------------------ */
    if(status == SystemP_SUCCESS)
    {
        status = SemaphoreP_constructCounting(&TestDss_dispDdDoneSem, 0,
                                              TEST_DSS_DD_NUM_THREADS);
    }

    if(status == SystemP_SUCCESS)
    {
        status = SemaphoreP_constructCounting(&TestDss_dispDdStartSem, 0,
                                              TEST_DSS_DD_NUM_THREADS);
        if(status != SystemP_SUCCESS)
        {
            SemaphoreP_destruct(&TestDss_dispDdDoneSem);
        }
    }

    if(status == SystemP_SUCCESS)
    {
        /* Thread 0: OLDI pipeline */
        TestDss_dispDdCtx[0].instObj    = oldiPipeObj;
        TestDss_dispDdCtx[0].threadIdx  = 0U;
        TestDss_dispDdCtx[0].result     = SystemP_FAILURE;
        TestDss_dispDdCtx[0].frameCount = 0U;

        /* Thread 1: DPI pipeline */
        TestDss_dispDdCtx[1].instObj    = dpiPipeObj;
        TestDss_dispDdCtx[1].threadIdx  = 1U;
        TestDss_dispDdCtx[1].result     = SystemP_FAILURE;
        TestDss_dispDdCtx[1].frameCount = 0U;

        {
            uint32_t tIdx;
            uint32_t threadSpawnFailed = FALSE;
            const char *tNames[TEST_DSS_DD_NUM_THREADS] = {"DSS_DD_OLDI",
                                                        "DSS_DD_DPI"};

            for(tIdx = 0U; tIdx < TEST_DSS_DD_NUM_THREADS; tIdx++)
            {
                TaskP_Params taskParams;

                TaskP_Params_init(&taskParams);
                taskParams.name      = tNames[tIdx];
                taskParams.stackSize = TEST_DSS_TASK_STACK_SIZE;
                taskParams.stack     = TestDss_dispDdTaskStack[tIdx];
                taskParams.priority  = TEST_DSS_TASK_PRIORITY;
                taskParams.args      = (void *)&TestDss_dispDdCtx[tIdx];
                taskParams.taskMain  = TestDisp_ddPipeWorker;

                status = TaskP_construct(&TestDss_dispDdTaskObj[tIdx],
                                         &taskParams);
                if(status != SystemP_SUCCESS)
                {
                    DebugP_log("DD: TaskP_construct failed for %s\r\n",
                               tNames[tIdx]);
                    /* Release any thread already waiting on start sem */
                    if(tIdx == 1U)
                    {
                        SemaphoreP_post(&TestDss_dispDdStartSem);
                        SemaphoreP_pend(&TestDss_dispDdDoneSem,
                                        SystemP_WAIT_FOREVER);
                        TaskP_destruct(&TestDss_dispDdTaskObj[0]);
                    }
                    SemaphoreP_destruct(&TestDss_dispDdDoneSem);
                    SemaphoreP_destruct(&TestDss_dispDdStartSem);
                    threadSpawnFailed = TRUE;
                    status = SystemP_FAILURE;
                    break;
                }
            }

            if(threadSpawnFailed == FALSE)
            {
                DebugP_log("DD: Worker threads spawned — releasing start "
                           "barrier\r\n");

                /* ------------------------------------------------------ */
                /* 7. Release both threads simultaneously                 */
                /* ------------------------------------------------------ */
                SemaphoreP_post(&TestDss_dispDdStartSem);
                SemaphoreP_post(&TestDss_dispDdStartSem);

                /* ------------------------------------------------------ */
                /* 8. Wait for both threads to complete                   */
                /* ------------------------------------------------------ */
                SemaphoreP_pend(&TestDss_dispDdDoneSem, SystemP_WAIT_FOREVER);
                SemaphoreP_pend(&TestDss_dispDdDoneSem, SystemP_WAIT_FOREVER);

                TaskP_destruct(&TestDss_dispDdTaskObj[0]);
                TaskP_destruct(&TestDss_dispDdTaskObj[1]);
                SemaphoreP_destruct(&TestDss_dispDdDoneSem);
                SemaphoreP_destruct(&TestDss_dispDdStartSem);

                DebugP_log("DD: Both threads completed\r\n");

                /* ------------------------------------------------------ */
                /* 9. Aggregate results and log FPS                       */
                /* ------------------------------------------------------ */
                {
                    const char *vpNames[TEST_DSS_DD_NUM_THREADS] = {"OLDI",
                                                                 "DPI"};
                    uint32_t i;

                    for(i = 0U; i < TEST_DSS_DD_NUM_THREADS; i++)
                    {
                        if(TestDss_dispDdCtx[i].result != SystemP_SUCCESS)
                        {
                            DebugP_log("DD: Thread %d (%s) FAILED\r\n",
                                       i, vpNames[i]);
                            status = SystemP_FAILURE;
                        }
                        else
                        {
                            uint64_t elapsedUs =
                                TestDss_dispDdCtx[i].endTimeUs -
                                TestDss_dispDdCtx[i].startTimeUs;
                            uint32_t fps = 0U;
                            if(elapsedUs > 0U)
                            {
                                fps = (uint32_t)(
                                    (uint64_t)TestDss_dispDdCtx[i].frameCount
                                    * 1000000ULL / elapsedUs);
                            }
                            DebugP_log("DD: Thread %d (%s) OK — %d frames "
                                       "in %d us (~%d FPS)\r\n",
                                       i, vpNames[i],
                                       TestDss_dispDdCtx[i].frameCount,
                                       (uint32_t)elapsedUs, fps);
                        }
                    }
                }
            }
        }
    }

    /* ------------------------------------------------------------------ */
    /* 10. Stop + delete both pipes, check VP errors, clear paths, deinit */
    /* ------------------------------------------------------------------ */

    /* Stop and delete OLDI pipe */
    TestDisp_ddStopAndDeletePipe(oldiPipeObj, "OLDI");

    /* Stop and delete DPI pipe */
    TestDisp_ddStopAndDeletePipe(dpiPipeObj, "DPI");

    /* VP1 error stats */
    memset(&errorStats, 0, sizeof(errorStats));
    errorStats.vpId = appObjOldi->vpParams.vpId;
    retVal = Fvid2_control(dctrlHandle, IOCTL_DSS_DCTRL_GET_VP_ERROR_STATS,
                           &errorStats, NULL);
    if(retVal == FVID2_SOK)
    {
        DebugP_log("DD: VP1 (OLDI) syncLost=%d\r\n", errorStats.syncLost);
    }

    /* VP2 error stats */
    memset(&errorStats, 0, sizeof(errorStats));
    errorStats.vpId = appObjDpi->vpParams.vpId;
    retVal = Fvid2_control(dctrlHandle, IOCTL_DSS_DCTRL_GET_VP_ERROR_STATS,
                           &errorStats, NULL);
    if(retVal == FVID2_SOK)
    {
        DebugP_log("DD: VP2 (DPI) syncLost=%d\r\n", errorStats.syncLost);
    }

    /* Clear both paths */
    (void)Fvid2_control(dctrlHandle, IOCTL_DSS_DCTRL_CLEAR_PATH,
                         appObjOldi->dctrlPathInfo, NULL);
    (void)Fvid2_control(dctrlHandle, IOCTL_DSS_DCTRL_CLEAR_PATH,
                         appObjDpi->dctrlPathInfo, NULL);

    /* Stop both VPs */
    Dss_dctrlVpParamsInit(&vpStopParams);
    vpStopParams.vpId = appObjOldi->vpParams.vpId;
    (void)Fvid2_control(dctrlHandle, IOCTL_DSS_DCTRL_STOP_VP,
                         &vpStopParams, NULL);

    vpStopParams.vpId = appObjDpi->vpParams.vpId;
    (void)Fvid2_control(dctrlHandle, IOCTL_DSS_DCTRL_STOP_VP,
                         &vpStopParams, NULL);

    /* Delete DCTRL handle and deinit */
    (void)Fvid2_delete(dctrlHandle, NULL);
    appObjOldi->dctrlHandle = NULL;
    appObjDpi->dctrlHandle  = NULL;
    Dss_deInit();
    Fvid2_deInit(NULL);

    DebugP_log("DD: ======================================================\r\n");
    if(status == SystemP_SUCCESS)
    {
        DebugP_log("DD: Dual Display DPI + OLDI Test PASSED\r\n");
    }
    else
    {
        DebugP_log("DD: Dual Display DPI + OLDI Test FAILED\r\n");
    }
    DebugP_log("DD: ======================================================\r\n");

    return status;
}
#endif

#if defined(SOC_AM62PX)
 /**
 * \brief  Interlaced video format display test.
 *
 *  Test Category: Functionality
 *
 *  Tests display pipeline with multiple interlaced video formats (NTSC, PAL, 480I, 576I,
 *  CIF, 1080I_60, 1080I_50) and verifies proper handling of field-based buffer addressing
 *  and scan format configuration. Tests the field merge calculations for interlaced buffers,
 *  TOP/BOTTOM field buffer addressing in VP configuration, and VP output mode enable flag
 *  for all interlaced format variations.
 *
 *  This test exercises:
 *  - csl_dssVideoPort.c: Interlaced scan format handling (lines 316-321)
 *  - csl_dssVideoPipe.c: Field merge logic with row increment calculations
 *  - dss_dispApi.c: TOP/BOTTOM field buffer address setup
 *  - dss_dctrlApi.c: Scan format tracking for interlaced modes
 *
 *  Tested formats: NTSC, PAL, 480I, 576I, CIF, 1080I_60, 1080I_50
 *
 *  \param appObj Pointer to DSS object containing configuration and state.
 *
 *  \return SystemP_SUCCESS on successful test execution, SystemP_FAILURE on error.
 */
int32_t TestDisp_interlacedDisplayControl(Dss_Object *appObj)
{
    int32_t retVal = FVID2_SOK;
    int32_t status = SystemP_SUCCESS;
    uint32_t instCnt = 0U, formatIdx = 0U;
    Fvid2_FrameList frmList;

    /* Interlaced format configuration table */
    typedef struct {
        uint32_t standard;
        uint32_t width;
        uint32_t height;
        uint32_t hFrontPorch;
        uint32_t hBackPorch;
        uint32_t hSyncLen;
        uint32_t vFrontPorch;
        uint32_t vBackPorch;
        uint32_t vSyncLen;
        uint32_t pixelClock;
        const char *formatName;
    } InterlacedFormatConfig;

    static const InterlacedFormatConfig interlacedFormats[] = {
        /* NTSC: 720x480i @ 29.97 Hz */
        {FVID2_STD_NTSC, 720U, 480U, 38U, 114U, 62U, 3U, 19U, 3U, 27000000U, "NTSC"},
        /* PAL: 720x576i @ 25 Hz */
        {FVID2_STD_PAL, 720U, 576U, 48U, 132U, 63U, 2U, 21U, 3U, 27000000U, "PAL"},
        /* 480I: 720x480i */
        {FVID2_STD_480I, 720U, 480U, 38U, 114U, 62U, 3U, 19U, 3U, 27000000U, "480I"},
        /* 576I: 720x576i */
        {FVID2_STD_576I, 720U, 576U, 48U, 132U, 63U, 2U, 21U, 3U, 27000000U, "576I"},
        /* CIF: 352x288i */
        {FVID2_STD_CIF, 352U, 288U, 24U, 66U, 31U, 1U, 10U, 3U, 13500000U, "CIF"},
        /* 1080I_60: 1920x1080i @ 60 Hz */
        {FVID2_STD_1080I_60, 1920U, 1080U, 88U, 148U, 44U, 4U, 36U, 5U, 74250000U, "1080I_60"},
        /* 1080I_50: 1920x1080i @ 50 Hz */
        {FVID2_STD_1080I_50, 1920U, 1080U, 528U, 148U, 44U, 2U, 22U, 5U, 72000000U, "1080I_50"},
    };

    static const uint32_t numFormats = sizeof(interlacedFormats) / sizeof(InterlacedFormatConfig);

    /* Save original video standard timing parameters */
    uint32_t savedStandard = gDssVpParams.lcdOpTimingCfg.mInfo.standard;
    uint32_t savedWidth = gDssVpParams.lcdOpTimingCfg.mInfo.width;
    uint32_t savedHeight = gDssVpParams.lcdOpTimingCfg.mInfo.height;
    uint32_t savedHFrontPorch = gDssVpParams.lcdOpTimingCfg.mInfo.hFrontPorch;
    uint32_t savedHBackPorch = gDssVpParams.lcdOpTimingCfg.mInfo.hBackPorch;
    uint32_t savedHSyncLen = gDssVpParams.lcdOpTimingCfg.mInfo.hSyncLen;
    uint32_t savedVFrontPorch = gDssVpParams.lcdOpTimingCfg.mInfo.vFrontPorch;
    uint32_t savedVBackPorch = gDssVpParams.lcdOpTimingCfg.mInfo.vBackPorch;
    uint32_t savedVSyncLen = gDssVpParams.lcdOpTimingCfg.mInfo.vSyncLen;
    uint32_t savedPixelClock = gDssVpParams.lcdOpTimingCfg.mInfo.pixelClock;

    DebugP_log("======================================================\r\n");
    DebugP_log("Interlaced Display Test: Testing %d formats\r\n", numFormats);
    DebugP_log("======================================================\r\n");

    /* Loop through all interlaced formats */
    for(formatIdx = 0U; formatIdx < numFormats && status == SystemP_SUCCESS; formatIdx++)
    {
        const InterlacedFormatConfig *fmt = &interlacedFormats[formatIdx];

        DebugP_log("------------------------------------------------------\r\n");
        DebugP_log("Testing format: %s\r\n", fmt->formatName);

        /* Configure for current interlaced format */
        gDssVpParams.lcdOpTimingCfg.mInfo.standard = fmt->standard;
        gDssVpParams.lcdOpTimingCfg.mInfo.width = fmt->width;
        gDssVpParams.lcdOpTimingCfg.mInfo.height = fmt->height;
        gDssVpParams.lcdOpTimingCfg.mInfo.hFrontPorch = fmt->hFrontPorch;
        gDssVpParams.lcdOpTimingCfg.mInfo.hBackPorch = fmt->hBackPorch;
        gDssVpParams.lcdOpTimingCfg.mInfo.hSyncLen = fmt->hSyncLen;
        gDssVpParams.lcdOpTimingCfg.mInfo.vFrontPorch = fmt->vFrontPorch;
        gDssVpParams.lcdOpTimingCfg.mInfo.vBackPorch = fmt->vBackPorch;
        gDssVpParams.lcdOpTimingCfg.mInfo.vSyncLen = fmt->vSyncLen;
        gDssVpParams.lcdOpTimingCfg.mInfo.pixelClock = fmt->pixelClock;

        retVal = FVID2_SOK;

        if(FVID2_SOK == retVal)
        {
            /* Initialize frame buffers for test */
            TestDisp_initFrames();
        }

        if(FVID2_SOK == retVal)
        {
            /* Initialize DSS module */
            retVal = TestDisp_init(appObj);
        }

        if(FVID2_SOK == retVal)
        {
            /* Initialize DSS parameters with interlaced format */
            TestDisp_initDssParams(appObj);
        }

        if(FVID2_SOK == retVal)
        {
            /* Initialize pipeline parameters */
            TestDisp_initPipelineParams(appObj);
        }

        if(FVID2_SOK == retVal)
        {
            /* Configure display controller with interlaced VP settings */
            retVal = TestDisp_configDctrl(appObj);
        }

        if(FVID2_SOK == retVal)
        {
            /* Create display driver instances */
            retVal = TestDisp_create(appObj);
        }

        if(FVID2_SOK == retVal)
        {
            /* Pump frames to exercise field merge and interlaced buffer addressing */
            volatile uint32_t loopCount = 0U;
            while(loopCount++ < DISP_NUM_FRAMES_COUNT)
            {
                for(instCnt = 0U; instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
                {
                    Dss_InstObject *instObj = &appObj->instObj[instCnt];
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
                            DebugP_log("  Frame pump failed\r\n");
                            status = SystemP_FAILURE;
                            break;
                        }
                    }
                    else if(FVID2_EAGAIN == retVal)
                    {
                        /* First callback - expected */
                        retVal = FVID2_SOK;
                    }
                    else
                    {
                        DebugP_log("  Dequeue failed\r\n");
                        status = SystemP_FAILURE;
                        break;
                    }
                }
                if(status != SystemP_SUCCESS)
                {
                    break;
                }
            }

            /* Stop driver */
            for(instCnt = 0U; instCnt < gDssConfigPipelineParams.numTestPipes; instCnt++)
            {
                Dss_InstObject *instObj = &appObj->instObj[instCnt];
                retVal = Fvid2_stop(instObj->drvHandle, NULL);
                if(retVal != FVID2_SOK)
                {
                    DebugP_log("  Stop failed\r\n");
                    status = SystemP_FAILURE;
                    break;
                }
            }
        }

        /* Delete driver instances and cleanup */
        if(FVID2_SOK == retVal)
        {
            TestDisp_delete(appObj);
        }

        retVal += TestDisp_deInit(appObj);

        if(FVID2_SOK != retVal)
        {
            status = SystemP_FAILURE;
        }

        if(status == SystemP_SUCCESS)
        {
            DebugP_log("  Format %s: PASS\r\n", fmt->formatName);
        }
        else
        {
            DebugP_log("  Format %s: FAIL\r\n", fmt->formatName);
        }
    }

    /* Restore original video parameters */
    gDssVpParams.lcdOpTimingCfg.mInfo.standard = savedStandard;
    gDssVpParams.lcdOpTimingCfg.mInfo.width = savedWidth;
    gDssVpParams.lcdOpTimingCfg.mInfo.height = savedHeight;
    gDssVpParams.lcdOpTimingCfg.mInfo.hFrontPorch = savedHFrontPorch;
    gDssVpParams.lcdOpTimingCfg.mInfo.hBackPorch = savedHBackPorch;
    gDssVpParams.lcdOpTimingCfg.mInfo.hSyncLen = savedHSyncLen;
    gDssVpParams.lcdOpTimingCfg.mInfo.vFrontPorch = savedVFrontPorch;
    gDssVpParams.lcdOpTimingCfg.mInfo.vBackPorch = savedVBackPorch;
    gDssVpParams.lcdOpTimingCfg.mInfo.vSyncLen = savedVSyncLen;
    gDssVpParams.lcdOpTimingCfg.mInfo.pixelClock = savedPixelClock;

    /* Restore frame buffer pointers */
    TestDisp_initFrames();

    DebugP_log("======================================================\r\n");
    if(status == SystemP_SUCCESS)
    {
        DebugP_log("Interlaced Display Test: ALL FORMATS PASSED\r\n");
    }
    else
    {
        DebugP_log("Interlaced Display Test: FAILED\r\n");
    }
    DebugP_log("======================================================\r\n");

    return status;
}

#endif /* SOC_AM62PX */
