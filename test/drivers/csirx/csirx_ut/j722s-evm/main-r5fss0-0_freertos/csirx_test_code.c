/*
 *  Copyright (c) 2019-25 Texas Instruments Incorporated
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
 *  \file csirx_test_code.c
 *
 *  \brief Contains test for various test-cases for CSIRX FVID3 DRV.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "csirx_test.h"
#include "csirx_testconfig_priv.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**< Frame Attribute: Width in pixels */
#define CSIRX_TEST_CAPT_MAX_FRAME_WIDTH                      ((uint32_t)1936U)
/**< Frame Attribute: Height in pixels */
#define CSIRX_TEST_CAPT_MAX_FRAME_HEIGHT                     ((uint32_t)1100U)
/**< Frame Attribute: Bytes per pixel */
#define CSIRX_TEST_CAPT_MAX_FRAME_BPP                        ((uint32_t)2U)
/**< Frame Attribute: size in bytes */
#define CSIRX_TEST_CAPT_MAX_FRAME_SIZE                       ((uint32_t)\
            (CSIRX_TEST_CAPT_MAX_FRAME_HEIGHT * CSIRX_TEST_CAPT_MAX_FRAME_WIDTH * CSIRX_TEST_CAPT_MAX_FRAME_BPP))

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
static int32_t App_init(CsirxTestTaskObj *taskObj);
static int32_t App_create(CsirxTestTaskObj *taskObj);
static int32_t App_csiTest(CsirxTestTaskObj *taskObj);
static int32_t App_delete(CsirxTestTaskObj *taskObj);
static int32_t App_frameCompletionCb(Fvid2_Handle handle,
                                     Ptr appData,
                                     Ptr reserved);
static int32_t App_allocAndQFrames(CsirxTestTaskObj *taskObj);
static int32_t App_captFreeFrames(CsirxTestTaskObj *taskObj);
#if defined (SIMULATOR)
static void App_sendFrame(CsirxTestTaskObj *taskObj);
#endif
static Bool App_continueCapture(CsirxTestTaskObj *taskObj);
extern int32_t App_sensorConfig(CsirxSensorCfg *senCfg);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

uint32_t gSimTbArgs[10U];

/* Memory buffer to hold frame data */
static uint8_t gFrms[(CSIRX_TEST_CAPT_FRAMES_PER_CH * CSIRX_TEST_MAX_CH)][CSIRX_TEST_CAPT_MAX_FRAME_SIZE]__attribute__(( aligned(128), section(".data_buffer")));
/** \brief Log enable for CSIRX Unit Test  application */
extern uint32_t gAppTrace;
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t Csirx_captureTest(CsirxTestTaskObj *taskObj)
{
    int retVal = FVID2_SOK;
    uint32_t chIdx;
    CsirxInstObj *instObj;

    /* App Init */
    retVal += App_init(taskObj);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(gAppTrace,
                  GT_ERR,
                  APP_NAME ": [ERROR]App_init() FAILED!!!\r\n");
    }
    /* App create */
    if (FVID2_SOK == retVal)
    {
        retVal += App_create(taskObj);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(gAppTrace,
                      GT_ERR,
                      APP_NAME ": [ERROR]App_create() FAILED!!!\r\n");
        }
    }
    /* App CSI test function */
    if (FVID2_SOK == retVal)
    {
        retVal += App_csiTest(taskObj);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(gAppTrace,
                      GT_ERR,
                      APP_NAME ": [ERROR]App_csiTest() FAILED!!!\r\n");
        }
    }

    /* App CSI delete function */
    if (FVID2_SOK == retVal)
    {
        retVal += App_delete(taskObj);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(gAppTrace,
                      GT_ERR,
                      APP_NAME ": [ERROR]App_delete() FAILED!!!\r\n");
        }
    }
    /* print channel stats here */
    GT_0trace(gAppTrace, GT_INFO,
                  "=============================================================\r\n");
    GT_0trace(gAppTrace, GT_INFO,
                  " ::Frames per seconds information for channels::\r\n");
    GT_0trace(gAppTrace, GT_INFO,
                  " |Inst ID   |Channel ID|Frames received|Error Frames|  FPS  |\r\n");
    instObj = &taskObj->instObj;
    for (chIdx = 0U ; chIdx < instObj->instCfgInfo->numCh ; chIdx++)
    {
        float fps = instObj->chObj[chIdx].fps;
        GT_6trace(gAppTrace, GT_INFO,
                  " |%d         |%d         |%d            |%d           | %u.%u |\r\n",
          instObj->instCfgInfo->csiDrvInst,
          chIdx,
          instObj->chObj[chIdx].captFrames,
          instObj->chObj[chIdx].captErrFrames,
          (uint32_t)fps,
          (fps - (uint32_t)fps)*100U);
    }
    GT_0trace(gAppTrace, GT_INFO,
                  "=============================================================\r\n");

    taskObj->testResult = retVal;

    return retVal;
}

static int32_t App_init(CsirxTestTaskObj *taskObj)
{
    int32_t retVal = FVID2_SOK;

    return retVal;
}

static int32_t App_create(CsirxTestTaskObj *taskObj)
{
    int32_t retVal = FVID2_SOK;
    Csirx_CreateParams createParams;
    uint32_t loopCnt;
    Csirx_DPhyCfg dphyCfg;
    Csirx_EventPrms eventPrms;

    memset(&createParams, 0x0, sizeof (Csirx_CreateParams));
    /* set instance configuration parameters */
    Csirx_createParamsInit(&createParams);
    /* prepare create paramters */
    createParams.numCh           = taskObj->instObj.instCfgInfo->numCh;
    createParams.frameDropBuf    = taskObj->instObj.instCfgInfo->frameDropBuf;
    createParams.frameDropBufLen = taskObj->instObj.instCfgInfo->frameDropBufLen;
    for (loopCnt = 0U ; loopCnt < createParams.numCh ; loopCnt++)
    {
        createParams.chCfg[loopCnt].chId = taskObj->instObj.chObj[loopCnt].chCfgInfo->chCfg->chId;
        createParams.chCfg[loopCnt].chType =taskObj->instObj.chObj[loopCnt].chCfgInfo->chCfg->chType;
        createParams.chCfg[loopCnt].vcNum = taskObj->instObj.chObj[loopCnt].chCfgInfo->chCfg->vcNum ;
        createParams.chCfg[loopCnt].inCsiDataType = taskObj->instObj.chObj[loopCnt].chCfgInfo->chCfg->inCsiDataType;
        createParams.chCfg[loopCnt].outFmt.width = taskObj->instObj.chObj[loopCnt].chCfgInfo->chCfg->outFmt.width;
        createParams.chCfg[loopCnt].outFmt.height = taskObj->instObj.chObj[loopCnt].chCfgInfo->chCfg->outFmt.height;
        createParams.chCfg[loopCnt].outFmt.pitch[0U] =
                                    taskObj->instObj.chObj[loopCnt].chCfgInfo->chCfg->outFmt.pitch[0];
        createParams.chCfg[loopCnt].outFmt.dataFormat =
                                    taskObj->instObj.chObj[loopCnt].chCfgInfo->chCfg->outFmt.dataFormat;
        createParams.chCfg[loopCnt].outFmt.ccsFormat =
                                                taskObj->instObj.chObj[loopCnt].chCfgInfo->chCfg->outFmt.ccsFormat;
    }
    /* set module configuration parameters */
    createParams.instCfg.enableCsiv2p0Support =taskObj->instObj.instCfgInfo->instCfg->enableCsiv2p0Support ;
    createParams.instCfg.numDataLanes = taskObj->instObj.instCfgInfo->instCfg->numDataLanes;
    createParams.instCfg.numPixelsStrm0 = taskObj->instObj.instCfgInfo->instCfg->numPixelsStrm0;
    createParams.instCfg.enableErrbypass = taskObj->instObj.instCfgInfo->instCfg->enableErrbypass;
    createParams.instCfg.enableStrm[CSIRX_CAPT_STREAM_ID] = 1U;
    for (loopCnt = 0U ;
         loopCnt < taskObj->instObj.instCfgInfo->instCfg->numDataLanes ;
         loopCnt++)
    {
        createParams.instCfg.dataLanesMap[loopCnt] = taskObj->instObj.instCfgInfo->instCfg->dataLanesMap[loopCnt];
    }

    /* Register call-back */
    Fvid2CbParams_init(&taskObj->instObj.cbPrms);
    taskObj->instObj.cbPrms.cbFxn   = (Fvid2_CbFxn) &App_frameCompletionCb;
    taskObj->instObj.cbPrms.appData = taskObj;

    /* Fvid2_create() */
    taskObj->drvHandle = Fvid2_create(
                                    CSIRX_CAPT_DRV_ID,
                                    taskObj->instObj.instCfgInfo->csiDrvInst,
                                    &createParams,
                                    &taskObj->instObj.createStatus,
                                    &taskObj->instObj.cbPrms);

    if ((NULL      == taskObj->drvHandle) ||
        (FVID2_SOK != taskObj->instObj.createStatus.retVal))
    {
        GT_0trace(gAppTrace, GT_ERR,
                  APP_NAME ": Capture Create Failed!!!\r\n");
        retVal = taskObj->instObj.createStatus.retVal;
    }
    if (FVID2_SOK == retVal)
    {
        /* Allocate instance semaphore */
        SemaphoreP_constructBinary(&taskObj->instObj.lockSem ,0U);
    }
    if (FVID2_SOK == retVal)
    {
        /* Set CSIRX D-PHY configuration parameters */
        Csirx_initDPhyCfg(&dphyCfg);
        dphyCfg.inst = CSIRX_INSTANCE_ID_0;
        retVal = Fvid2_control(taskObj->drvHandle,
                               IOCTL_CSIRX_SET_DPHY_CONFIG,
                               &dphyCfg,
                               NULL);
        if(FVID2_SOK != retVal)
        {
            GT_0trace(gAppTrace,
                      GT_ERR,
                      APP_NAME
                      ":Set D-PHY Configuration FAILED!!!\r\n");
        }
        else
        {
            GT_0trace(gAppTrace,
                      GT_ERR,
                      APP_NAME
                      ":Set D-PHY Configuration SUCCESSFUL!!!\r\n");
        }

    }
    if (FVID2_SOK == retVal)
    {
        /* Register Error Events */
        Csirx_eventPrmsInit(&eventPrms);
        retVal = Fvid2_control(taskObj->drvHandle,
                               IOCTL_CSIRX_REGISTER_EVENT,
                               &eventPrms,
                               NULL);

    }

    return retVal;
}

/* Timeout per semaphore pend: 5 seconds. At ~30 FPS, one frame arrives
 * every ~33 ms. A 5-second timeout is generous enough for normal operation
 * and prevents an infinite hang when sensors are not streaming. */
#define APP_FRAME_WAIT_TIMEOUT_USEC     (5000000U)

static int32_t App_csiTest(CsirxTestTaskObj *taskObj)
{
    int32_t retVal = FVID2_SOK;
    uint32_t startTime, elapsedTime, chIdx, vcNumCnt;
    CsirxSensorCfg senCfg;
    CsirxInstObj *instObj;
    CsirxChObj *chObj;



    senCfg.numCh = taskObj->instObj.instCfgInfo->numCh;
    if(1U == senCfg.numCh)
    {
        senCfg.usePatternGen = 1;
        senCfg.dt = taskObj->instObj.chObj[0].chCfgInfo->chCfg->inCsiDataType;
        senCfg.frameWidth = taskObj->instObj.chObj[0].chCfgInfo->chCfg->outFmt.width;
        senCfg.frameHeight = taskObj->instObj.chObj[0].chCfgInfo->chCfg->outFmt.height;
    }
    else
    {
        senCfg.usePatternGen = 0;
    }

    senCfg.numDataLanes = taskObj->instObj.instCfgInfo->instCfg->numDataLanes;
    for (vcNumCnt = 0U; vcNumCnt < senCfg.numCh ; vcNumCnt++)
    {
        if(taskObj->instObj.instCfgInfo->instCfgInfoId ==
           INST_CFG_ID_DRV_ID0_2CH_RAW12_STRM_FIFO_OVERFLOW)
        {
            senCfg.vcNum[vcNumCnt] = 0x0;
        }
        else
        {
            senCfg.vcNum[vcNumCnt] =
            taskObj->instObj.chObj[vcNumCnt].chCfgInfo->chCfg->vcNum;
        }
    }
    /* Allocate and queue all available frames */
    retVal = App_allocAndQFrames(taskObj);

    /* Sensor Config here */
    if (FVID2_SOK != App_sensorConfig(&senCfg))
    {
        retVal = FVID2_EFAIL;
    }

    if (FVID2_SOK == retVal)
    {
        GT_0trace(gAppTrace, GT_INFO,
                  APP_NAME ": Sensor Configuration SUCCESSFUL!!!\r\n");
    }

    if (FVID2_SOK == retVal)
    {
        retVal    = Fvid2_start(taskObj->drvHandle, NULL);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(gAppTrace, GT_ERR,
                      APP_NAME ": Capture Start Failed!!!\r\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        startTime = App_getCurTimeInMsec();

        /* Wait for reception completion */
        while (App_continueCapture(taskObj))
        {
            /* Pend with timeout to avoid infinite hang when sensor
             * is not streaming (misconfigured, not connected, etc.) */
            if (SystemP_TIMEOUT == SemaphoreP_pend(&taskObj->instObj.lockSem,
                            (uint32_t)ClockP_usecToTicks(APP_FRAME_WAIT_TIMEOUT_USEC)))
            {
                GT_0trace(gAppTrace, GT_ERR,
                          APP_NAME ": Timed out waiting for frame - sensor not streaming!!!\r\n");
                retVal = FVID2_ETIMEOUT;
                break;
            }
        }

        elapsedTime = App_getElapsedTimeInMsec(startTime);
    }
    else
    {
        elapsedTime = 0U;
    }

    retVal = Fvid2_stop(taskObj->drvHandle, NULL);
    instObj = &taskObj->instObj;
    for (chIdx = 0U; chIdx < instObj->instCfgInfo->numCh ; chIdx++)
    {
        chObj = &instObj->chObj[chIdx];
        chObj->fps = (elapsedTime > 0U) ?
                     ((float)(chObj->captFrames) * 1000U / elapsedTime) : 0.0f;
    }
    if (FVID2_SOK != retVal)
    {
        GT_0trace(gAppTrace, GT_ERR,
                  APP_NAME ": Capture Stop Failed!!!\r\n");
        return retVal;
    }
    retVal = App_captFreeFrames(taskObj);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(gAppTrace, GT_ERR,
                  APP_NAME ": Capture Stop Failed!!!\r\n");
    }
    if (FVID2_ENO_MORE_BUFFERS == retVal)
    {
        /* All buffer might be de-queued during stop,
           in this case no error shall be returned */
        retVal = FVID2_SOK;
    }

    return retVal;
}

static int32_t App_allocAndQFrames(CsirxTestTaskObj *taskObj)
{
    int32_t retVal = FVID2_SOK;
    uint32_t chIdx = 0U, frmIdx = 0U;
    static Fvid2_FrameList frmList;
    Fvid2_Frame  *pFrm;
    CsirxInstObj *instObj;
    CsirxChObj   *chObj;

    /* for every channel in a capture handle,
       allocate memory for and queue frames */
    Fvid2FrameList_init(&frmList);
    frmList.numFrames = 0U;
    instObj = &taskObj->instObj;
    for (chIdx = 0U; chIdx < instObj->instCfgInfo->numCh ; chIdx++)
    {
        chObj = &instObj->chObj[chIdx];
        for (frmIdx = 0U; frmIdx < chObj->chCfgInfo->numFrames ; frmIdx++)
        {

            /* assign frames memory */
            /* Only following fields are used in CSIRX DRV */
            pFrm = (Fvid2_Frame *)
                    &chObj->frames[(chIdx *CSIRX_TEST_CAPT_FRAMES_PER_CH) + frmIdx];
            pFrm->addr[0U] = (uint64_t)(uint64_t)&gFrms[(chIdx * CSIRX_TEST_CAPT_FRAMES_PER_CH) + frmIdx][0U];

            pFrm->chNum = chObj->chCfgInfo->chCfg->chId;

            pFrm->appData = taskObj;
            frmList.frames[frmList.numFrames] = pFrm;
            frmList.numFrames++;
        }
    }
    /* queue the frames in frmList
     * All allocated frames are queued here as an example.
     * In general at least 2 frames per stream/channel need to queued
     * before capture can be started.
     * Failing which, frame could be dropped.
     */
    /* last parameter, i.e. streamId is unused in CSIRX DRV */
    retVal = Fvid2_queue(taskObj->drvHandle, &frmList, 0U);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(gAppTrace,
                  GT_ERR,
                  APP_NAME ": Capture Queue Failed!!!\r\n");
    }

    return retVal;
}

static int32_t App_frameCompletionCb(Fvid2_Handle handle,
                                     Ptr appData,
                                     Ptr reserved)
{
    int32_t  retVal = FVID2_SOK;
    uint32_t frmIdx = 0U;
    static Fvid2_FrameList frmList;
    Fvid2_Frame *pFrm;
    CsirxTestTaskObj *taskObj = (CsirxTestTaskObj *) appData;
    CsirxChObj *chObj;

    GT_assert(gAppTrace, (NULL != appData));

    Fvid2FrameList_init(&frmList);
    retVal = Fvid2_dequeue(
        taskObj->drvHandle,
        &frmList,
        0U,
        FVID2_TIMEOUT_NONE);
    if (FVID2_SOK == retVal)
    {
        for (frmIdx = 0U; frmIdx < frmList.numFrames; frmIdx++)
        {
            pFrm = frmList.frames[frmIdx];
            chObj = &taskObj->instObj.chObj[pFrm->chNum];
            if (FVID2_FRAME_STATUS_COMPLETED != pFrm->status)
            {
                chObj->captErrFrames++;
            }
            else
            {
                chObj->captFrames++;
            }
        }

        /* Queue back de-queued frames,
           last param i.e. streamId is unused in DRV */
        retVal = Fvid2_queue(taskObj->drvHandle, &frmList, 0U);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(gAppTrace, GT_ERR,
                      APP_NAME ": Capture Queue Failed!!!\r\n");
        }
    }

    /* always return 'FVID2_SOK' */
    /* Post semaphore here for sending next Image */
    SemaphoreP_post(&taskObj->instObj.lockSem);

    return FVID2_SOK;
}

static int32_t App_captFreeFrames(CsirxTestTaskObj *taskObj)
{
    int32_t retVal = FVID2_SOK;
    static Fvid2_FrameList frmList;
    uint32_t chIdx = 0U, frmIdx = 0U;
    CsirxInstObj *instObj;
    CsirxChObj *chObj;

    /* for every stream and channel in a capture handle */
    Fvid2FrameList_init(&frmList);

    /* Deq-queue any frames queued more than needed */
    retVal = Fvid2_dequeue(
                    taskObj->drvHandle,
                    &frmList,
                    0U,
                    FVID2_TIMEOUT_NONE);
    if (FVID2_ENO_MORE_BUFFERS == retVal)
    {
        retVal = FVID2_SOK;
    }
    if (FVID2_SOK != retVal)
    {
        GT_0trace(gAppTrace,
                  GT_ERR,
                  APP_NAME ": De-queue in shut down failed!!!\r\n");
    }
    /* Free up frame allocated memories here */
    /* for every channel in a capture handle, de-allocate frame memory */
    instObj = &taskObj->instObj;
    for (chIdx = 0U; chIdx < instObj->instCfgInfo->numCh ; chIdx++)
    {
        chObj = &instObj->chObj[chIdx];
        for (frmIdx = 0U; frmIdx < chObj->chCfgInfo->numFrames ; frmIdx++)
        {
            /* free frames memory */
            retVal += Utils_memFree(
               chObj->chCfgInfo->heapId,
               (chObj->frmAddr[frmIdx]),
               (chObj->chCfgInfo->chCfg->outFmt.pitch[0U] * \
                chObj->chCfgInfo->chCfg->outFmt.height));
        }
    }
    if (FVID2_SOK != retVal)
    {
        GT_0trace(gAppTrace,
                  GT_ERR,
                  APP_NAME ": Frame memory freeing up failed!!!\r\n");
    }

    return retVal;
}

static int32_t App_delete(CsirxTestTaskObj *taskObj)
{
    int32_t retVal = FVID2_SOK;
    static Fvid2_FrameList frmList;

    Fvid2FrameList_init(&frmList);
    /* Dequeue all the request from the driver */
    retVal = Fvid2_dequeue(
                    taskObj->drvHandle,
                    &frmList,
                    0U,
                    FVID2_TIMEOUT_NONE);

    if ((FVID2_SOK != retVal) && (FVID2_ENO_MORE_BUFFERS != retVal))
    {
        GT_0trace(gAppTrace, GT_ERR,
                  APP_NAME ": Capture De-queue Failed!!!\r\n");
    }
    retVal = Fvid2_delete(taskObj->drvHandle, NULL);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(gAppTrace, GT_ERR,
                  APP_NAME ": FVID2 Delete Failed!!!\r\n");
    }
    else
    {
        taskObj->drvHandle = NULL;
    }

    if (FVID2_SOK == retVal)
    {
        /* Delete semaphore */
        SemaphoreP_destruct(&taskObj->instObj.lockSem);
        GT_0trace(gAppTrace, GT_INFO, APP_NAME ": Capture Driver deleted\r\n");
    }

    return retVal;
}

static Bool App_continueCapture(CsirxTestTaskObj *taskObj)
{
    Bool retVal = UTRUE;
    uint32_t chIdx;
    CsirxInstObj *instObj;

    instObj = &taskObj->instObj;
    for (chIdx = 0U ;chIdx <  instObj->instCfgInfo->numCh ; chIdx++)
    {
        if ((instObj->chObj[chIdx].captFrames <
             instObj->chObj[chIdx].chCfgInfo->numCaptFrames) &&
            (instObj->chObj[chIdx].captErrFrames < instObj->chObj[chIdx].chCfgInfo->numCaptFrames))
        {
            break;
        }
        else
        {
            retVal = UFALSE;
        }
    }

    return retVal;
}
