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
 *  \file dss_dispApi.c
 *
 *  \brief File containing the DSS display driver implementation.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/dss.h>
#include <drivers/fvid2.h>
#include <kernel/dpl/SemaphoreP.h>
#include <drivers/dss/v0/common/dss_evtMgr.h>
#include <drivers/dss/v0/disp/dss_dispDrv.h>
#include <drivers/dss/v0/disp/dss_dispPriv.h>
#include <drivers/dss/v0/soc/dss_soc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Number of lines for which time duration before VSYNC is considered to be too
 * small for DSS operations to finish */
#define DSS_DISP_NUM_LINES_NEAR_VSYNC                  ((uint32_t) 5U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if typecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Display APIs
 */
static Fdrv_Handle Dss_dispDrvCreate(uint32_t drvId,
                                     uint32_t instId,
                                     void *createArgs,
                                     void *createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbParams);
static int32_t Dss_dispDrvDelete(Fdrv_Handle handle, void *reserved);
static int32_t Dss_dispDrvQueue(Fdrv_Handle handle,
                                Fvid2_FrameList *frmList,
                                uint32_t streamId);
static int32_t Dss_dispDrvDequeue(Fdrv_Handle handle,
                                  Fvid2_FrameList *frmList,
                                  uint32_t streamId,
                                  uint32_t timeout);
static int32_t Dss_dispDrvControl(Fdrv_Handle handle,
                                  uint32_t cmd,
                                  void *cmdArgs,
                                  void *cmdStatusArgs);

#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern Dss_EvtMgrClientInfo gDss_DispEvtMgrClientInfo[DSS_DISP_EVT_MGR_MAX_CLIENTS];

extern SemaphoreP_Object gDssStartSyncSem;
/* ========================================================================== */
/*                  Internal/Private Function Declarations                    */
/* ========================================================================== */

/*
 * Display IOCTLs
 */
static void Dss_dispDrvClientCb(void *arg0);
static int32_t Dss_dispDrvStartIoctl(Dss_DispDrvInstObj *instObj);
static int32_t Dss_dispDrvStopIoctl(Dss_DispDrvInstObj *instObj);
static int32_t Dss_dispDrvSetDssParamsIoctl(Dss_DispDrvInstObj *instObj,
                                            const Dss_DispParams *dispParams);
static int32_t Dss_dispDrvSetMflagParamsIoctl(
                                    Dss_DispDrvInstObj *instObj,
                                    const Dss_DispPipeMflagParams *mflagParams);
static int32_t Dss_dispDrvGetStatusIoctl(Dss_DispDrvInstObj *instObj,
                                         Dss_DispCurrentStatus *dispStatus);
static int32_t Dss_dispDrvSetPipeSafetyParamsIoctl(
                            Dss_DispDrvInstObj *instObj,
                            const Dss_DispPipeSafetyChkParams *safetyChkParams);
static int32_t Dss_dispDrvSetPipeCscParamsIoctl(
                            Dss_DispDrvInstObj *instObj,
                            const CSL_DssCscCoeff *cscCoeff);
static int32_t Dss_dispDrvSetBufPrgmCbParamsIoctl(
                            Dss_DispDrvInstObj *instObj,
                            const Dss_DispBufPrgmCbParams *bufPrgmCbParams);
static int32_t Dss_dispDrvSetPipePrgmCbParamsIoctl(
                            Dss_DispDrvInstObj *instObj,
                            const Dss_DispPipePrgmCbParams *pipePrgmCbParams);
static int32_t Dss_dispDrvSetPipeUnderFlowCbParamsIoctl(
                            Dss_DispDrvInstObj *instObj,
                            const Dss_DispUnderFlowCbParams *underFlowCbParams);
static int32_t Dss_dispDrvValidateDssParams(const Dss_DispDrvInstObj *instObj,
                                            const Dss_DispParams *dispParams);
static int32_t Dss_dispDrvValidateRtParams(const Dss_DispDrvInstObj *instObj,
                                           const Dss_DispRtParams *rtParams);
static int32_t Dss_dispDrvApplyRtParams(Dss_DispDrvInstObj *instObj,
                                        const Dss_DispRtParams *rtParams);
static void Dss_dispSafetyErrCbFxn(const uint32_t *event,
                                   uint32_t numEvents,
                                   void *arg);
static uint32_t Dss_dispIsFarFromVsync(const Dss_DispDrvInstObj *instObj);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t Dss_dispDrvInit(uint32_t numInst,
                        const Dss_DispDrvInitParams *initParams)
{
    int32_t retVal = FVID2_SOK;
    Dss_DispDrvCommonObj *pObj;

    retVal = Dss_dispDrvPrivInit(numInst, initParams);
    if(FVID2_SOK == retVal)
    {
        pObj = &gDss_DispDrvCommonObj;
        GT_assert(DssTrace, (NULL != pObj));

        /* Initialize Driver operations */
        Fvid2DrvOps_init(&pObj->fvidDrvOps);

        pObj->fvidDrvOps.drvId = DSS_DISP_DRV_ID;
        pObj->fvidDrvOps.createFxn = &Dss_dispDrvCreate;
        pObj->fvidDrvOps.deleteFxn = &Dss_dispDrvDelete;
        pObj->fvidDrvOps.controlFxn = &Dss_dispDrvControl;
        pObj->fvidDrvOps.queueFxn = &Dss_dispDrvQueue;
        pObj->fvidDrvOps.dequeueFxn = &Dss_dispDrvDequeue;

        retVal = Fvid2_registerDriver(&pObj->fvidDrvOps);
        if(FVID2_SOK != retVal)
        {
            GT_0trace(DssTrace, GT_ERR,
                      "Registering to FVID2 driver manager failed\r\n");
            /* Un-initialize the internal objects if error occurs */
            retVal += Dss_dispDrvPrivDeInit();
        }
        else
        {
            /* Init successful */
            pObj->isRegistered = TRUE;
            pObj->numInst = numInst;
        }
    }

    return (retVal);
}

int32_t Dss_dispDrvDeInit(void)
{
    int32_t retVal = FVID2_SOK;
    Dss_DispDrvCommonObj *pObj;

    pObj = &gDss_DispDrvCommonObj;
    GT_assert(DssTrace, (NULL != pObj));

    if(TRUE == pObj->isRegistered)
    {
        /* Unregister from driver manager */
        retVal = Fvid2_unRegisterDriver(&pObj->fvidDrvOps);
        if(FVID2_SOK != retVal)
        {
            GT_0trace(DssTrace, GT_ERR,
                      "Unregistering from FVID2 driver manager failed\r\n");
        }
        pObj->isRegistered = FALSE;
    }

    retVal += Dss_dispDrvPrivDeInit();

    return (retVal);
}

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static Fdrv_Handle Dss_dispDrvCreate(uint32_t drvId,
                                     uint32_t instId,
                                     void *createArgs,
                                     void *createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbParams)
{
    int32_t retVal = FVID2_SOK, tempRetVal;
    uint32_t instCreateFlag = FALSE, nodeId;
    Fdrv_Handle drvHandle = NULL;
    Dss_DispDrvInstObj *instObj = NULL;
    Dss_DispCreateParams *createParams;
    Dss_DispCreateStatus *createStatus;
    Dss_DctrlDrvClientInfo clientInfo;
    Dss_DctrlVpParams vpParams;

    /* Check for NULL pointers and invalid arguments */
    if((NULL == createArgs) ||
       (NULL == createStatusArgs) ||
       (NULL == fdmCbParams) ||
       (DSS_DISP_DRV_ID != drvId))
    {
        GT_0trace(DssTrace, GT_ERR, "Invalid arguments\r\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        /* Get the instance object for this instance */
        instObj = Dss_dispDrvGetInstObj(instId);
        if(NULL == instObj)
        {
            GT_0trace(DssTrace, GT_ERR, "Invalid instance ID\r\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
    }

    if(NULL != instObj)
    {
        /* Take the instance semaphore */
        (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

        /* Check if the instance is already opened */
        if(TRUE == instObj->drvState.isOpened)
        {
            GT_0trace(DssTrace,
                      GT_ERR,
                      "Driver instance already created!!\r\n");
            retVal = FVID2_EDEVICE_INUSE;
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Check for valid create parameters and copy them */
        createParams = (Dss_DispCreateParams *) createArgs;
        Fvid2Utils_memcpy(&instObj->createParams,
                          createParams,
                          sizeof (Dss_DispCreateParams));
    }

    if(FVID2_SOK == retVal)
    {
        retVal = Dss_dispDrvCreateInstObj(instObj);
        if(FVID2_SOK != retVal)
        {
            GT_0trace(DssTrace, GT_ERR,
                      "Channel object create failed!!\r\n");
        }
        else
        {
            instCreateFlag = TRUE;
        }
    }

    if(FVID2_SOK == retVal)
    {
        instObj->pipeId = instId;
        retVal = Dss_convModuletoNode(&nodeId, instObj->pipeId,
			              DSS_DCTRL_NODE_TYPE_PIPE);
        GT_assert(DssTrace,
                  ((DSS_DCTRL_NODE_INVALID != nodeId) ||
                   (FVID2_SOK == retVal)));
        instObj->pipeNodeId = nodeId;
    }

    if(FVID2_SOK == retVal)
    {
        /* Initialize instance variables */
        Fvid2Utils_memcpy(
            &instObj->fdmCbParams,
            fdmCbParams,
            sizeof (Fvid2_DrvCbParams));

        instObj->drvState.isOpened = TRUE;
        instObj->isPrevBufRep = FALSE;
        instObj->isInIsrContext = FALSE;
        drvHandle = instObj;
    }

    if(FVID2_SOK == retVal)
    {
        clientInfo.cbFxn = &Dss_dispDrvClientCb;
        clientInfo.arg = instObj;
        instObj->dctrlHandle = Dss_dctrlDrvRegisterClient(instObj->pipeNodeId,
                                                          &clientInfo);
        if(NULL == instObj->dctrlHandle)
        {
            GT_0trace(DssTrace,
                      GT_ERR,
                      "Display Controller registration failed for DSS");
            retVal = FVID2_EALLOC;
        }
        else
        {
            retVal = Dss_dctrlDrvGetVpParams(instObj->dctrlHandle, &vpParams);
            if(FVID2_SOK != retVal)
            {
                GT_0trace(DssTrace,
                          GT_ERR,
                          "Getting information from Display controller failed");
            }
            else
            {
                instObj->standard = vpParams.lcdOpTimingCfg.mInfo.standard;
                instObj->dispWidth = vpParams.lcdOpTimingCfg.mInfo.width;
                instObj->dispHeight = vpParams.lcdOpTimingCfg.mInfo.height;
                instObj->dispScanFormat =
                                    vpParams.lcdOpTimingCfg.mInfo.scanFormat;
                instObj->vpId = vpParams.vpId;
            }
        }
    }

    if(FVID2_SOK != retVal)
    {
        if((NULL != instObj) && (NULL != instObj->dctrlHandle))
        {
            retVal += Dss_dctrlDrvUnRegisterClient(instObj->dctrlHandle);
        }
    }

    /* Return the status if possible */
    if(NULL != createStatusArgs)
    {
        createStatus = (Dss_DispCreateStatus *) createStatusArgs;
        createStatus->retVal = retVal;
        if(NULL != instObj)
        {
            createStatus->standard = instObj->standard;
            createStatus->dispWidth = instObj->dispWidth;
            createStatus->dispHeight = instObj->dispHeight;
            createStatus->minNumPrimeBuf = DSS_DISP_DRV_MIN_PRIME_BUFFERS;
        }
    }

    if(NULL != instObj)
    {
        /* Deallocate if error occurs */
        if(FVID2_SOK != retVal)
        {
            if(TRUE == instCreateFlag)
            {
                tempRetVal = Dss_dispDrvDeleteInstObj(instObj);
                GT_assert(DssTrace, (FVID2_SOK == tempRetVal));
            }
        }

        /* Post the instance semaphore */
        (void) SemaphoreP_post(&instObj->lockSem);
    }

    return (drvHandle);
}

static int32_t Dss_dispDrvDelete(Fdrv_Handle handle, void *reserved)
{
    int32_t retVal = FVID2_SOK;
    Dss_DispDrvInstObj *instObj = NULL;

    /* Check for NULL pointers and invalid arguments */
    if(NULL == handle)
    {
        GT_0trace(DssTrace, GT_ERR, "Invalid arguments\r\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        instObj = (Dss_DispDrvInstObj *) handle;
    }

    if(NULL != instObj)
    {
        /* Take the instance semaphore */
        (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

        /* Check if already opened. */
        if(TRUE != instObj->drvState.isOpened)
        {
            GT_0trace(DssTrace, GT_ERR, "Driver not opened\r\n");
            retVal = FVID2_EFAIL;
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* If already started, stop it. */
        if(TRUE == instObj->drvState.isStarted)
        {
            retVal = Dss_dispDrvStopIoctl(instObj);
            if(FVID2_SOK != retVal)
            {
                GT_0trace(DssTrace, GT_ERR, "Stop display failed\r\n");
            }
        }
    }

    if(FVID2_SOK == retVal)
    {
        if(NULL != instObj->dctrlHandle)
        {
            retVal = Dss_dctrlDrvUnRegisterClient(instObj->dctrlHandle);
        }
        retVal += Dss_dispDrvDeleteInstObj(instObj);
        GT_assert(DssTrace, (FVID2_SOK == retVal));

        /* Reset other variables */
        instObj->drvState.isOpened = FALSE;
        instObj->drvState.isStarted = FALSE;
        instObj->currStatus.queueCount = 0U;
        instObj->currStatus.dequeueCount = 0U;
        instObj->currStatus.dispFrmCount = 0U;
        instObj->currStatus.repeatFrmCount = 0U;

        instObj->fdmCbParams.fdmCbFxn = NULL;
        instObj->fdmCbParams.fdmErrCbFxn = NULL;
        instObj->fdmCbParams.handle = NULL;
        instObj->fdmCbParams.errList = NULL;
        instObj->fdmCbParams.fdmData = NULL;
    }

    if(NULL != instObj)
    {
        /* Post the instance semaphore */
        (void) SemaphoreP_post(&instObj->lockSem);
    }

    return (retVal);
}

static int32_t Dss_dispDrvQueue(Fdrv_Handle handle,
                                Fvid2_FrameList *frmList,
                                uint32_t streamId)
{
    int32_t  retVal = FVID2_SOK;
    uint32_t frmCnt, cookie;
    uint32_t reqQCnt, isSafe;
    uint32_t isBufAccepted = TRUE;
    Fvid2_Frame *frm, *newFrm;
    Dss_DispDrvInstObj *instObj;
    Dss_DispDrvQueObj *qObj, *qObjTemp;
    CSL_dss_pipeRegs *pipeRegs;
    const Dss_SocInfo *socInfo;
    Dss_DispRtParams *rtParams;
    int32_t rtParamsRetVal = FVID2_SOK;

    /* Check for NULL pointers */
    if((NULL == handle) || (NULL == frmList))
    {
        GT_0trace(DssTrace, GT_ERR, "NULL pointer\r\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        instObj = (Dss_DispDrvInstObj *) handle;

        /* Check frame list for error and NULL pointer check */
        retVal = Fvid2_checkFrameList(frmList, (uint32_t) FVID2_MAX_FRAME_PTR);
        if(FVID2_SOK != retVal)
        {
            GT_0trace(DssTrace, GT_ERR, "Check frame list error\r\n");
        }

        if(FALSE == instObj->drvState.isOpened)
        {
            /* If driver handle is not open then skip this frame queue */
            GT_0trace(DssTrace,
                      GT_ERR,
                      "Can't queue to an un-opened instance!!\r\n");
            retVal = FVID2_EFAIL;
        }
        /* Only one frame submit supported per instance */
        if(frmList->numFrames > 1U)
        {
            GT_0trace(DssTrace,
                      GT_ERR,
                      "Only one frame submit supported in current design\r\n");
            retVal = FVID2_EFAIL;
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* For all frames that need to be queued. The loop is dummy */
        for(frmCnt=0U; frmCnt<frmList->numFrames; frmCnt++)
        {
            /* Get FVID2 frame pointer - NULL check is already done in
             * check frame list function */
            frm = frmList->frames[frmCnt];
            GT_assert(DssTrace, (NULL != frm));

            cookie = HwiP_disable();

            /* Allocate a free queue object from the pool */
            qObj = (Dss_DispDrvQueObj *) Fvid2Utils_dequeue(
                                                        instObj->bmObj.freeQ);
            if(NULL == qObj)
            {
                HwiP_restore(cookie);
                GT_0trace(DssTrace,
                          GT_ERR,
                          "Q object allocation failed\r\n");
                retVal = FVID2_EALLOC;
                break;
            }

            /* Copy the frame to the driver's queue object */
            qObj->frm = frm;
            /* Initial credit count should be zero!! */
            GT_assert(DssTrace, (0U == qObj->creditCnt));

            /* Push mechanism */
            /* 1.  Check if the new frame should be updated immediately in case
             *     of frame repeat.
             * 2.  Check if the previous frame was repeated
             * 3.  Check if request queue is empty
             * 4.  If request queue is not empty then put it in the request
             *     queue and exit.
             * 5.  If request queue is empty then push the buffer to hardware
             * 6.  If hardware accepts then put the buffer in current queue and
             *     update the credit count
             * 7.  If hardware accepts the buffer then make the prevRepBuf as
             *     false. This is required if two back to back buffers are
             *     queued in same frame period. (The second buffer should not be
             *     pushed if first once is accepted)
             * 8.  If hardware doesn't accept the buffer then put it in the
             *     request queue.
             * 9.  In Vsync call back we set the prevBufRepeated flag
             *     appropriately.
             *     a. Set to true if no buffer is available in request queue
             *     b. Set to false if buffer is given to hardware
             * 10. Here we will overwrite the buffer present in the currQ with
             *     the new one. Basically what needs to done is to revert what
             *     is being done in Vsync callback function when the buffer
             *     is repeated. So peak the current queue and decrement
             *     the credit count. It will automatically moved to doneQ in
             *     next Vsync Call back.
             */
            reqQCnt = Fvid2Utils_getNumQElem(instObj->bmObj.reqQ);
            if((0U == reqQCnt) &&
               (FALSE == instObj->createParams.progPipeVsyncEnable) &&
               (TRUE == instObj->isPrevBufRep) &&
               /* Don't program if queue is called from ISR callback context.
                * Just push to request queue */
               (FALSE == instObj->isInIsrContext))
            {
                /* Call the user buffer program callback */
                if(NULL != instObj->bufPrgmCbParams.bufPrgmCbFxn)
                {
                    newFrm = instObj->bufPrgmCbParams.bufPrgmCbFxn(
                                                    instObj->fdmCbParams.handle,
                                                    qObj->frm,
                                                    FALSE,
                                                    qObj->creditCnt);
                    if(NULL != newFrm)
                    {
                        /* Swap the current frame */
                        qObj->frm = newFrm;
                    }
                }

                /* Query display controller to check if it is safe to push */
                isSafe = Dss_dispIsFarFromVsync(instObj);

                if((retVal == FVID2_SOK) && (isSafe == TRUE))
                {
                    instObj->progFrame = qObj->frm;

                    /* Get video pipe registers */
                    socInfo = Dss_getSocInfo();
                    pipeRegs = socInfo->pipeRegs[instObj->pipeId];
                    GT_assert(DssTrace, (NULL != pipeRegs));

                    if(NULL != instObj->progFrame->perFrameCfg)
                    {
                        rtParams =
                            (Dss_DispRtParams *)(instObj->progFrame->perFrameCfg);
                        rtParamsRetVal = Dss_dispDrvValidateRtParams(instObj,
                                                                     rtParams);
                        if(FVID2_SOK == rtParamsRetVal)
                        {
                            Dss_dispDrvApplyRtParams(instObj, rtParams);
                        }
                    }

                    CSL_dssVidPipeSetBuffAddr(pipeRegs,
                                              FVID2_FID_TOP,
                                              instObj->progFrame->addr[0U],
                                              instObj->progFrame->addr[1U]);

                    if(instObj->inScanFormat == FVID2_SF_INTERLACED)
                    {
                        CSL_dssVidPipeSetBuffAddr(pipeRegs,
                                                  FVID2_FID_BOTTOM,
                                                  instObj->progFrame->addr[3U],
                                                  instObj->progFrame->addr[4U]);
                    }
                    if(NULL != instObj->pipePrgmCbParams.pipePrgmCbFxn)
                    {
                        /* Give callback to application that buffer has been
                         * programmed
                         */
                        instObj->pipePrgmCbParams.pipePrgmCbFxn(
                                                instObj->progFrame,
                                                instObj->pipePrgmCbParams.appData);
                    }

                    retVal = Dss_dctrlDrvSetGoBit(instObj->dctrlHandle);
                }

                isBufAccepted = isSafe;

                if(TRUE == isBufAccepted)
                {
                    /* Decrement the credit count of previously repeated buffer,
                     * This is not a repeat now as we are overwriting the
                     * buffer */
                    qObjTemp = (Dss_DispDrvQueObj *) Fvid2Utils_peakTail(
                        instObj->bmObj.currQ);
                    /* This can't return NULL unless there is a bug in the
                     * buffer management */
                    GT_assert(DssTrace, (NULL != qObjTemp));
                    qObjTemp->creditCnt--;

                    Fvid2Utils_queue(instObj->bmObj.currQ, &qObj->qElem, qObj);
                    qObj->creditCnt++;
                    instObj->isPrevBufRep = FALSE;
                    /* This is like a queue only, so increment the count*/
                    instObj->currStatus.queueCount++;
                }
                else
                {
                    /* Add the queue object in driver's request queue */
                    Fvid2Utils_queue(instObj->bmObj.reqQ, &qObj->qElem, qObj);
                    instObj->currStatus.queueCount++;
                }
            }
            else
            {
                /* Add the queue object in driver's request queue */
                Fvid2Utils_queue(instObj->bmObj.reqQ, &qObj->qElem, qObj);
                instObj->currStatus.queueCount++;
            }

            HwiP_restore(cookie);

            /* Mark frame in frmList as NULL */
            frmList->frames[frmCnt] = NULL;
        }
    }

    return (retVal);
}

static int32_t Dss_dispDrvDequeue(Fdrv_Handle handle,
                                  Fvid2_FrameList *frmList,
                                  uint32_t streamId,
                                  uint32_t timeout)
{
    int32_t retVal = FVID2_SOK;
    uint32_t cookie;
    Dss_DispDrvInstObj *instObj;
    Dss_DispDrvQueObj *qObj;
    Dss_DispDrvBufManObj *bmObj;

    /* Check for NULL pointers */
    if((NULL == handle) || (NULL == frmList) || (streamId > 0U))
    {
        GT_0trace(DssTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        instObj = (Dss_DispDrvInstObj *) handle;
        bmObj   = &instObj->bmObj;

        if(FALSE == instObj->drvState.isOpened)
        {
            GT_0trace(
                DssTrace,
                GT_ERR,
                "Invalid Driver state: Can't dequeue to an un-opened instance!!\r\n");
            retVal = FVID2_EFAIL;
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Init frame list fields */
        frmList->numFrames  = 0U;
        frmList->perListCfg = NULL;

        cookie = HwiP_disable();

        /* Get a completed queue object from driver's done queue */
        qObj = (Dss_DispDrvQueObj *) Fvid2Utils_dequeue(bmObj->doneQ);
        if(NULL == qObj)
        {
            /* When display is stopped, give back all the driver owned buffer
             * including the current programmed and the buffers in request
             * queue */
            if(TRUE != instObj->drvState.isStarted)
            {
                /* Give the buffers in current state */
                qObj = (Dss_DispDrvQueObj *) Fvid2Utils_dequeue(bmObj->currQ);
                if(NULL == qObj)
                {
                    /* At last give back the buffers in request queue as well */
                    qObj = (Dss_DispDrvQueObj *) Fvid2Utils_dequeue(
                                                                bmObj->reqQ);
                }

                /* Check if all these operation has failed */
                if(NULL == qObj)
                {
                    GT_0trace(DssTrace,
                              GT_DEBUG,
                              "NO_MORE_BUFFERS: No more buffers with driver\n");
                    retVal = FVID2_ENO_MORE_BUFFERS;
                }
            }
            else
            {
                GT_0trace(DssTrace,
                          GT_DEBUG,
                          "AGAIN: Out queue Empty. Try again\r\n");
                retVal = FVID2_EAGAIN;
            }
        }

        HwiP_restore(cookie);

        /* Copy the driver's frame list to application's frame list */
        if(NULL != qObj)
        {
            cookie = HwiP_disable();

            GT_assert(DssTrace, (NULL != qObj->frm));
            frmList->frames[frmList->numFrames] = qObj->frm;
            frmList->numFrames++;

            /* Give back the queue object back to the free pool */
            qObj->frm = NULL;
            /* At time of dequeue, credit should be zero!! */
            GT_assert(DssTrace, (0U == qObj->creditCnt));
            Fvid2Utils_queue(bmObj->freeQ, &qObj->qElem, qObj);
            instObj->currStatus.dequeueCount++;

            HwiP_restore(cookie);
        }
    }

    return (retVal);
}

static int32_t Dss_dispDrvControl(Fdrv_Handle handle,
                                  uint32_t cmd,
                                  void *cmdArgs,
                                  void *cmdStatusArgs)
{
    int32_t retVal = FVID2_SOK;
    Dss_DispDrvInstObj *instObj;

    /* Check for NULL pointers */
    if(NULL == handle)
    {
        GT_0trace(DssTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        instObj = (Dss_DispDrvInstObj *) handle;
        switch (cmd)
        {
            case FVID2_START:
                retVal = Dss_dispDrvStartIoctl(instObj);
                break;
            case FVID2_STOP:
                retVal = Dss_dispDrvStopIoctl(instObj);
                break;
            case IOCTL_DSS_DISP_SET_DSS_PARAMS:
                retVal = Dss_dispDrvSetDssParamsIoctl(
                               instObj,
                               (const Dss_DispParams *) cmdArgs);
                break;
            case IOCTL_DSS_DISP_SET_PIPE_MFLAG_PARAMS:
                retVal = Dss_dispDrvSetMflagParamsIoctl(
                               instObj,
                               (const Dss_DispPipeMflagParams *) cmdArgs);
                break;
            case IOCTL_DSS_DISP_GET_CURRENT_STATUS:
                retVal = Dss_dispDrvGetStatusIoctl(
                               instObj,
                               (Dss_DispCurrentStatus *) cmdArgs);
                break;
            case IOCTL_DSS_DISP_SET_PIPE_SAFETY_CHK_PARAMS:
                retVal = Dss_dispDrvSetPipeSafetyParamsIoctl(
                               instObj,
                               (const Dss_DispPipeSafetyChkParams *) cmdArgs);
                break;
            case IOCTL_DSS_DISP_SET_PIPE_CSC_COEFF:
                retVal = Dss_dispDrvSetPipeCscParamsIoctl(
                                instObj,
                                (const CSL_DssCscCoeff *) cmdArgs);
                break;
            case IOCTL_DSS_DISP_REGISTER_BUF_PRGM_CB:
                retVal = Dss_dispDrvSetBufPrgmCbParamsIoctl(
                                instObj,
                                (const Dss_DispBufPrgmCbParams *) cmdArgs);
                break;
            case IOCTL_DSS_DISP_REGISTER_PIPE_PRGM_CB:
                retVal = Dss_dispDrvSetPipePrgmCbParamsIoctl(
                                instObj,
                                (const Dss_DispPipePrgmCbParams *) cmdArgs);
                break;
            case IOCTL_DSS_DISP_REGISTER_PIPE_UNDERFLOW_CB:
                retVal = Dss_dispDrvSetPipeUnderFlowCbParamsIoctl(
                                instObj,
                                (const Dss_DispUnderFlowCbParams *) cmdArgs);
                break;
            default:
                GT_0trace(DssTrace, GT_ERR,
                          "UNSUPPORTED_CMD: IOCTL not supported\r\n");
                retVal = FVID2_EUNSUPPORTED_CMD;
                break;
        }
    }

    return (retVal);
}

static void Dss_dispDrvClientCb(void *arg0)
{
    Dss_DispDrvInstObj *instObj;
    Dss_DispDrvQueObj *qObj, *qObjTemp;
    uint32_t currQCnt, reqQCnt, cookie;
    uint32_t frmQueuedToDoneQ = FALSE;
    CSL_dss_pipeRegs *pipeRegs;
    const Dss_SocInfo *socInfo;
    Fvid2_Frame *newFrm;
    Dss_DispRtParams *rtParams;
    int32_t rtParamsRetVal = FVID2_SOK;

    GT_assert(DssTrace, (NULL != arg0));
    instObj = (Dss_DispDrvInstObj *)arg0;

    if(TRUE == instObj->drvState.isStarted)
    {
        cookie = HwiP_disable();

        if(NULL != instObj->currFrame)
        {
            /* Update channel statistics */
            instObj->currStatus.dispFrmCount++;
            /* Get current queue head */
            qObj = (Dss_DispDrvQueObj *) Fvid2Utils_peakHead(instObj->bmObj.currQ);
            GT_assert(DssTrace, (NULL != qObj));

            /* Decrement credit count as frame display is complete - credit can't
            * be zero */
            GT_assert(DssTrace, (qObj->creditCnt > 0U));
            qObj->creditCnt--;
            if(qObj->creditCnt > 0U)
            {
                instObj->currStatus.repeatFrmCount++;
            }

            /* Get the current queue counts */
            currQCnt = Fvid2Utils_getNumQElem(instObj->bmObj.currQ);
            reqQCnt = Fvid2Utils_getNumQElem(instObj->bmObj.reqQ);

            if(0U == qObj->creditCnt)
            {
                qObjTemp = (Dss_DispDrvQueObj *) Fvid2Utils_dequeue(
                                                            instObj->bmObj.currQ);
                /* Head node and qObj should match */
                GT_assert(DssTrace, (qObj == qObjTemp));

                /* In last frame repeat mode, we could return all the frames to
                * the application if credit becomes 0 and there are some more
                * request in the current or request queue. Current queue is
                * checked for 1 element as the current frame is still present
                * in the queue. */
                if((currQCnt > 1U) || (reqQCnt > 0U))
                {
                    /* Return the frame to done queue */
                    GT_assert(DssTrace, (NULL != qObj->frm));
                    Fvid2Utils_queue(instObj->bmObj.doneQ, &qObj->qElem, qObj);
                    frmQueuedToDoneQ = TRUE;
                }
                /* In last frame repeat mode, if credit becomes 0 and there are
                * no more request in the current and request queues, take this
                * request and queue it back to request queue so that when
                * the hardware asks for next buffer, we repeat the frame
                * automatically. This is needed because the user could
                * queue a request in between and this frame will end-up
                * in the current queue!!
                * Also increment the repeat frame counter here. */
                else if((currQCnt == 1U) && (reqQCnt == 0U))
                {
                    instObj->currStatus.repeatFrmCount++;
                    Fvid2Utils_queue(instObj->bmObj.reqQ, &qObj->qElem, qObj);
                }
                else
                {
                    /* This can't happen as currQCnt can't be zero!! */
                    GT_assert(DssTrace, FALSE);
                }
            }
        }

        if(NULL != instObj->fdmCbParams.fdmCbFxn)
        {
            /* Give callback to application if periodic call back is enabled or
             * if frame is put in done queue */
            if((TRUE == instObj->createParams.periodicCbEnable) ||
               (TRUE == frmQueuedToDoneQ))
            {
                instObj->isInIsrContext = TRUE;
                instObj->fdmCbParams.fdmCbFxn(instObj->fdmCbParams.fdmData);
                instObj->isInIsrContext = FALSE;
            }
        }

        instObj->currFrame = instObj->progFrame;

        /* Get new frame from request queue or repeat frame */
        qObj = (Dss_DispDrvQueObj *) Fvid2Utils_dequeue(instObj->bmObj.reqQ);
        if(NULL != qObj)
        {
            /*
             * Buffer available in request queue
             */
            /* Increment credit */
            qObj->creditCnt++;
            Fvid2Utils_queue(instObj->bmObj.currQ, &qObj->qElem, qObj);
            instObj->isPrevBufRep = FALSE;
        }
        else
        {
            /*
             * No more buffers available in request queue.
             * Repeat the last frame queued.
             */
            qObj = (Dss_DispDrvQueObj *) Fvid2Utils_peakTail(
                                                        instObj->bmObj.currQ);
            /* This can't return NULL unless there is a bug in the buffer
             * management */
            GT_assert(DssTrace, (NULL != qObj));
            /* Increment credit */
            qObj->creditCnt++;
            /* Mark the buffer as repeated */
            instObj->isPrevBufRep = TRUE;
        }

        /* Call the user buffer program callback */
        if(NULL != instObj->bufPrgmCbParams.bufPrgmCbFxn)
        {
            newFrm = instObj->bufPrgmCbParams.bufPrgmCbFxn(
                                            instObj->fdmCbParams.handle,
                                            qObj->frm,
                                            instObj->isPrevBufRep,
                                            qObj->creditCnt);
            if(NULL != newFrm)
            {
                /* Swap the current frame */
                qObj->frm = newFrm;
            }
        }

        /* Set frame to be programmed */
        instObj->progFrame = qObj->frm;
        /* Driver should always give the buffers when requested */
        GT_assert(DssTrace, (instObj->progFrame != NULL));
        /* Get video pipe registers */
        socInfo = Dss_getSocInfo();
        pipeRegs = socInfo->pipeRegs[instObj->pipeId];
        GT_assert(DssTrace, (NULL != pipeRegs));

        if(NULL != instObj->progFrame->perFrameCfg)
        {
            rtParams = (Dss_DispRtParams *)(instObj->progFrame->perFrameCfg);
            rtParamsRetVal = Dss_dispDrvValidateRtParams(instObj, rtParams);
            if(FVID2_SOK == rtParamsRetVal)
            {
                Dss_dispDrvApplyRtParams(instObj, rtParams);
            }
        }

        CSL_dssVidPipeSetBuffAddr(pipeRegs,
                                  FVID2_FID_TOP,
                                  instObj->progFrame->addr[0U],
                                  instObj->progFrame->addr[1U]);

        if(instObj->inScanFormat == FVID2_SF_INTERLACED)
        {
            CSL_dssVidPipeSetBuffAddr(pipeRegs,
                                      FVID2_FID_BOTTOM,
                                      instObj->progFrame->addr[3U],
                                      instObj->progFrame->addr[4U]);
        }

        if(NULL != instObj->pipePrgmCbParams.pipePrgmCbFxn)
        {
            /* Give callback to application that buffer has been programmed */
            instObj->pipePrgmCbParams.pipePrgmCbFxn(
                            instObj->progFrame,
                            instObj->pipePrgmCbParams.appData);
        }

        HwiP_restore(cookie);
    }
    else if(TRUE == instObj->drvState.isStarting)
    {
        cookie = HwiP_disable();

        /* Start display */
        instObj->drvState.isStarted = TRUE;
        qObj = (Dss_DispDrvQueObj *) Fvid2Utils_dequeue(instObj->bmObj.reqQ);
        if(NULL != qObj)
        {
            /*
            * Buffer available in request queue
            */
            /* Increment credit */
            qObj->creditCnt++;
            Fvid2Utils_queue(instObj->bmObj.currQ, &qObj->qElem, qObj);
            instObj->isPrevBufRep = FALSE;
            instObj->progFrame = qObj->frm;
        }
        else
        {
            /* This can't return NULL unless application has made a mistake */
            GT_assert(DssTrace, (NULL != qObj));
        }

        /* Driver should always give the buffers when requested */
        GT_assert(DssTrace, (instObj->progFrame != NULL));

        /* Get video pipe registers */
        socInfo = Dss_getSocInfo();
        pipeRegs = socInfo->pipeRegs[instObj->pipeId];
        GT_assert(DssTrace, (NULL != pipeRegs));

        CSL_dssVidPipeSetBuffAddr(pipeRegs,
                                  FVID2_FID_TOP,
                                  instObj->progFrame->addr[0U],
                                  instObj->progFrame->addr[1U]);

        if(instObj->inScanFormat == FVID2_SF_INTERLACED)
        {
            CSL_dssVidPipeSetBuffAddr(pipeRegs,
                                      FVID2_FID_BOTTOM,
                                      instObj->progFrame->addr[3U],
                                      instObj->progFrame->addr[4U]);
        }

        CSL_dssVidPipeEnable(pipeRegs, TRUE);
        instObj->drvState.isStarting = FALSE;

        if(NULL != instObj->pipePrgmCbParams.pipePrgmCbFxn)
        {
            /* Give callback to application that buffer has been programmed */
            instObj->pipePrgmCbParams.pipePrgmCbFxn(
                            instObj->progFrame,
                            instObj->pipePrgmCbParams.appData);
        }

        HwiP_restore(cookie);
    }
    else if(TRUE == instObj->drvState.isStopping)
    {
        cookie = HwiP_disable();

        /* Get video pipe registers */
        socInfo = Dss_getSocInfo();
        pipeRegs = socInfo->pipeRegs[instObj->pipeId];
        GT_assert(DssTrace, (NULL != pipeRegs));

        /* Disable Video Pipe */
        CSL_dssVidPipeEnable(pipeRegs, FALSE);
        instObj->currFrame = NULL;
        instObj->progFrame = NULL;
        instObj->drvState.isStopping = FALSE;

        /* Take the buffers in current state and push them in to the request
         * queue so that the next start will use those buffers */
        qObj = (Dss_DispDrvQueObj *) Fvid2Utils_dequeue(instObj->bmObj.currQ);
        while (NULL != qObj)
        {
            qObj->creditCnt = 0U;
            /* Push it to the request queue */
            Fvid2Utils_queueBack(instObj->bmObj.reqQ, &qObj->qElem, qObj);
            qObj = (Dss_DispDrvQueObj *) Fvid2Utils_dequeue(
                                                        instObj->bmObj.currQ);
        };

        if(NULL != instObj->pipePrgmCbParams.pipePrgmCbFxn)
        {
            /* Give callback to application that buffer has been programmed */
            instObj->pipePrgmCbParams.pipePrgmCbFxn(
                                        instObj->progFrame,
                                        instObj->pipePrgmCbParams.appData);
        }

        HwiP_restore(cookie);
    }
    else
    {
        /* Should never execute this */
        GT_assert(DssTrace, FALSE);
    }
}

static int32_t Dss_dispDrvStartIoctl(Dss_DispDrvInstObj *instObj)
{
    int32_t retVal = FVID2_SOK;
    uint32_t numElemInReqQ, isSafe, dummyStart;
    Dss_DispDrvBufManObj *bmObj;
    Dss_DispDrvQueObj *qObj;
    uint32_t cookie;
    CSL_dss_pipeRegs *pipeRegs;
    const Dss_SocInfo *socInfo;

    /* Check for NULL pointers */
    GT_assert(DssTrace, (NULL != instObj));

    /* wait for start sync semaphore */
    (void) SemaphoreP_pend(&gDssStartSyncSem, SystemP_WAIT_FOREVER);

    /* Take the instance semaphore */
    (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    bmObj = &instObj->bmObj;

    /* Initialize instance variables that needs to be reset in stop/start
     * sequence */
    instObj->currStatus.dispFrmCount = 0U;
    instObj->currStatus.repeatFrmCount = 0U;
    bmObj->expectedFid = 0U;
    bmObj->curFid = 0U;

    /* Check if the number of elements in the queue is sufficient to prime */
    numElemInReqQ = Fvid2Utils_getNumQElem(instObj->bmObj.reqQ);
    if(numElemInReqQ < DSS_DISP_DRV_MIN_PRIME_BUFFERS)
    {
        GT_0trace(DssTrace, GT_ERR, "Insufficient buffers queued\r\n");
        retVal = FVID2_EFAIL;
    }

    if(FVID2_SOK == retVal)
    {
        if(FALSE == instObj->createParams.progPipeVsyncEnable)
        {
            /* Get video pipe registers */
            socInfo = Dss_getSocInfo();
            pipeRegs = socInfo->pipeRegs[instObj->pipeId];
            GT_assert(DssTrace, (NULL != pipeRegs));

            cookie = HwiP_disable();
            /* Check if it is safe to start or start is too near to VSYNC */
            isSafe = Dss_dispIsFarFromVsync(instObj);
            if(TRUE == isSafe)
            {
                qObj = (Dss_DispDrvQueObj *) Fvid2Utils_dequeue(
                                                        instObj->bmObj.reqQ);
                if(NULL != qObj)
                {
                    /*
                     * Buffer available in request queue
                     */
                    /* Increment credit */
                    qObj->creditCnt++;
                    Fvid2Utils_queue(instObj->bmObj.currQ, &qObj->qElem, qObj);
                    instObj->isPrevBufRep = FALSE;
                    instObj->progFrame = qObj->frm;
                }
                else
                {
                    /*
                    * No more buffers available in request queue.
                    * Repeat the last frame queued.
                    */
                    qObj = (Dss_DispDrvQueObj *) Fvid2Utils_peakTail(
                                                        instObj->bmObj.currQ);
                    /* This can't return NULL unless there is a bug in the
                     * buffer management */
                    GT_assert(DssTrace, (NULL != qObj));
                    /* Increment credit */
                    qObj->creditCnt++;
                    /* Mark the buffer as repeated */
                    instObj->isPrevBufRep = TRUE;
                    instObj->progFrame = qObj->frm;
                }

                /* Driver should always give the buffers when requested */
                GT_assert(DssTrace, (instObj->progFrame != NULL));

                CSL_dssVidPipeSetBuffAddr(pipeRegs,
                                          FVID2_FID_TOP,
                                          instObj->progFrame->addr[0U],
                                          instObj->progFrame->addr[1U]);

                if(instObj->inScanFormat == FVID2_SF_INTERLACED)
                {
                    CSL_dssVidPipeSetBuffAddr(pipeRegs,
                                              FVID2_FID_BOTTOM,
                                              instObj->progFrame->addr[3U],
                                              instObj->progFrame->addr[4U]);
                }

                /* Start display */
                instObj->drvState.isStarted = TRUE;
                dummyStart = FALSE;
                CSL_dssVidPipeEnable(pipeRegs, TRUE);
                if(NULL != instObj->pipePrgmCbParams.pipePrgmCbFxn)
                {
                    /* Give callback to application that buffer has been
                     * programmed */
                    instObj->pipePrgmCbParams.pipePrgmCbFxn(
                                            instObj->progFrame,
                                            instObj->pipePrgmCbParams.appData);
                }
            }
            else
            {
                instObj->drvState.isStarting = TRUE;
                dummyStart = TRUE;
            }

            HwiP_restore(cookie);
            retVal = Dss_dctrlDrvStartClient(instObj->dctrlHandle, dummyStart);

            if(FVID2_SOK != retVal)
            {
                instObj->drvState.isStarted = FALSE;
                instObj->drvState.isStarting = FALSE;
                CSL_dssVidPipeEnable(pipeRegs, FALSE);
                Dss_dctrlDrvStopClient(instObj->dctrlHandle, dummyStart);
                GT_0trace(DssTrace, GT_ERR, "Driver start failed!!\r\n");
            }
        }
        else
        {
            instObj->drvState.isStarting = TRUE;
            retVal = Dss_dctrlDrvStartClient(instObj->dctrlHandle, TRUE);
            if(FVID2_SOK != retVal)
            {
                instObj->drvState.isStarting = FALSE;
                Dss_dctrlDrvStopClient(instObj->dctrlHandle, TRUE);
                GT_0trace(DssTrace, GT_ERR, "Driver start failed!!\r\n");
            }
        }
    }

    if(FVID2_SOK != retVal)
    {
        GT_0trace(DssTrace, GT_ERR, "Fvid2 start failed\r\n");
    }

    /* Post the instance semaphore */
    (void) SemaphoreP_post(&instObj->lockSem);

    return (retVal);
}

static int32_t Dss_dispDrvStopIoctl(Dss_DispDrvInstObj *instObj)
{
    int32_t  retVal = FVID2_SOK;
    uint32_t cookie;
    Dss_DispDrvQueObj *qObj;
    CSL_dss_pipeRegs *pipeRegs;
    const Dss_SocInfo *socInfo;

    /* Check for NULL pointers */
    GT_assert(DssTrace, (NULL != instObj));

    /* Take the instance semaphore */
    (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    if(FALSE == instObj->createParams.progPipeVsyncEnable)
    {
        /* Get video pipe registers */
        socInfo = Dss_getSocInfo();
        pipeRegs = socInfo->pipeRegs[instObj->pipeId];
        GT_assert(DssTrace, (NULL != pipeRegs));

        /* Disable Video Pipe */
        CSL_dssVidPipeEnable(pipeRegs, FALSE);
        instObj->currFrame = NULL;
        instObj->progFrame = NULL;
        retVal = Dss_dctrlDrvStopClient(instObj->dctrlHandle, FALSE);

        if(FVID2_SOK == retVal)
        {
            cookie = HwiP_disable();

            instObj->drvState.isStarted = FALSE;

            /* Take the buffers in current state and push them in to the request
             * queue so that the next start will use those buffers */
            qObj = (Dss_DispDrvQueObj *) Fvid2Utils_dequeue(
                                                        instObj->bmObj.currQ);
            while (NULL != qObj)
            {
                qObj->creditCnt = 0U;
                /* Push it to the request queue */
                Fvid2Utils_queueBack(instObj->bmObj.reqQ, &qObj->qElem, qObj);
                qObj = (Dss_DispDrvQueObj *) Fvid2Utils_dequeue(
                                                        instObj->bmObj.currQ);
            };

            HwiP_restore(cookie);
        }
    }
    else
    {
        instObj->drvState.isStopping = TRUE;
        instObj->drvState.isStarted = FALSE;
        retVal = Dss_dctrlDrvStopClient(instObj->dctrlHandle, TRUE);
    }

    if(FVID2_SOK != retVal)
    {
        GT_0trace(DssTrace, GT_ERR, "Fvid2 stop failed\r\n");
    }

    /* Post the instance semaphore */
    (void) SemaphoreP_post(&instObj->lockSem);

    return (retVal);
}

static int32_t Dss_dispDrvSetDssParamsIoctl(Dss_DispDrvInstObj *instObj,
                                            const Dss_DispParams *dispParams)
{
    int32_t retVal = FVID2_SOK;
    uint32_t layerNum;
    CSL_DssOverlayPipePosCfg overlayPosCfg;
    CSL_dss_pipeRegs *pipeRegs;
    CSL_dss_overlayRegs *overlayRegs;
    const Dss_SocInfo *socInfo;
    Dss_DctrlDrvPipeInfo *pipeInfo;
    Dss_DispParams *pipeParams;

    GT_assert(DssTrace, (NULL != instObj));

    /* Check for wrong inputs */
    if((instObj->drvInstId >= DSS_DISP_INST_MAX) || (NULL == dispParams))
    {
        GT_0trace(DssTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    /* Take the instance semaphore */
    (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    if(FVID2_SOK == retVal)
    {
        pipeInfo = Dss_dctrlDrvGetPipeInfo(instObj->dctrlHandle);
        pipeParams = &instObj->pipeParams[instObj->pipeId];

        /* Get video pipe registers */
        socInfo = Dss_getSocInfo();
        pipeRegs = socInfo->pipeRegs[instObj->pipeId];
        GT_assert(DssTrace, (NULL != pipeRegs));

        /* Get overlay registers */
        overlayRegs = socInfo->overlayRegs[pipeInfo->overlayId];
        GT_assert(DssTrace, (NULL != overlayRegs));

        retVal = Dss_dispDrvValidateDssParams(
                                        (const Dss_DispDrvInstObj *)instObj,
                                        (const Dss_DispParams *)dispParams);
    }

    if(FVID2_SOK == retVal)
    {
        Fvid2Utils_memcpy(pipeParams, dispParams, sizeof(Dss_DispParams));
        retVal = CSL_dssVidPipeSetConfig(
                        pipeRegs,
                        (const CSL_DssVidPipeCfg *)(&dispParams->pipeCfg),
                        (const CSL_DssVidPipeVC1Cfg *)(&dispParams->vc1Cfg));
    }

    if(FVID2_SOK == retVal)
    {
        instObj->inScanFormat = dispParams->pipeCfg.inFmt.scanFormat;
        CSL_dssVidPipeSetDmaConfig(
                    pipeRegs,
                    (const CSL_DssVidPipeDmaCfg *)(&dispParams->dmaCfg));

        CSL_dssVidPipeSetAlphaConfig(
                    pipeRegs,
                    (const CSL_DssVidPipeAlphaCfg *)(&dispParams->alphaCfg));

        layerNum = CSL_dssOverlayGetEnabledPipeLayerNum(overlayRegs,
                                                        pipeInfo->pipeId);
        GT_assert(DssTrace, (layerNum < CSL_DSS_OVERLAY_LAYER_MAX));
        overlayPosCfg.layerPos.startX = dispParams->layerPos.startX;
        overlayPosCfg.layerPos.startY = dispParams->layerPos.startY;
        CSL_dssOverlaySetPipePosConfig(
                    overlayRegs,
                    (const CSL_DssOverlayPipePosCfg *)(&overlayPosCfg),
                    layerNum);
        pipeInfo->startX = dispParams->layerPos.startX;
        pipeInfo->startY = dispParams->layerPos.startY;
    }

    if(FVID2_SOK != retVal)
    {
        GT_0trace(DssTrace, GT_ERR, "Set DSS parameter IOCTL failed\r\n");
    }

    /* Post the instance semaphore */
    (void) SemaphoreP_post(&instObj->lockSem);

    return (retVal);
}

static int32_t Dss_dispDrvSetMflagParamsIoctl(
                                    Dss_DispDrvInstObj *instObj,
                                    const Dss_DispPipeMflagParams *mflagParams)
{
    int32_t retVal = FVID2_SOK;
    CSL_dss_pipeRegs *pipeRegs;
    const Dss_SocInfo *socInfo;

    GT_assert(DssTrace, (NULL != instObj));

    /* Check for wrong inputs */
    if((instObj->drvInstId >= DSS_DISP_INST_MAX) || (NULL == mflagParams))
    {
        GT_0trace(DssTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    /* Take the instance semaphore */
    (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    if(FVID2_SOK == retVal)
    {
        /* Get video pipe registers */
        socInfo = Dss_getSocInfo();
        pipeRegs = socInfo->pipeRegs[instObj->pipeId];
        GT_assert(DssTrace, (NULL != pipeRegs));

        if(TRUE == instObj->drvState.isStarted)
        {
            retVal = FVID2_EDEVICE_INUSE;
            GT_0trace(DssTrace,
                    GT_ERR,
                    "Cannot set MFLAG parameters while display is in use\r\n");
        }

        CSL_dssVidPipeSetMflagConfig(
                    pipeRegs,
                    (const CSL_DssVidPipeMFlagCfg *)(&mflagParams->mflagCfg));
    }

    if(FVID2_SOK != retVal)
    {
        GT_0trace(DssTrace, GT_ERR, "Set MFLAG parameters IOCTL failed\r\n");
    }

    /* Post the instance semaphore */
    (void) SemaphoreP_post(&instObj->lockSem);

    return (retVal);
}

static int32_t Dss_dispDrvGetStatusIoctl(Dss_DispDrvInstObj *instObj,
                                         Dss_DispCurrentStatus *dispStatus)
{
    int32_t retVal = FVID2_SOK;

    GT_assert(DssTrace, (NULL != instObj));

    /* Check for wrong inputs */
    if((instObj->drvInstId >= DSS_DISP_INST_MAX) || (NULL == dispStatus))
    {
        GT_0trace(DssTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    /* Take the instance semaphore */
    (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    if(FVID2_SOK == retVal)
    {
        Fvid2Utils_memcpy(dispStatus,
                          &instObj->currStatus,
                          sizeof(Dss_DispCurrentStatus));
    }

    if(FVID2_SOK != retVal)
    {
        GT_0trace(DssTrace, GT_ERR, "Get status IOCTL failed\r\n");
    }

    /* Post the instance semaphore */
    (void) SemaphoreP_post(&instObj->lockSem);

    return (retVal);
}

static int32_t Dss_dispDrvSetPipeSafetyParamsIoctl(
                            Dss_DispDrvInstObj *instObj,
                            const Dss_DispPipeSafetyChkParams *safetyChkParams)
{
    int32_t retVal = FVID2_SOK;
    uint32_t eventGroup, numHandle, evtMgrId, safetyEvt;
    CSL_dss_pipeRegs *pipeRegs;
    const Dss_SocInfo *socInfo;
    const CSL_DssSafetyChkCfg *safetyChkCfg;

    /* Check for NULL pointers */
    GT_assert(DssTrace, (NULL != instObj));
    /* Check for wrong inputs */
    if((instObj->drvInstId >= DSS_DISP_INST_MAX) || (NULL == safetyChkParams))
    {
        GT_0trace(DssTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    /* Take the instance semaphore */
    (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    if(FVID2_SOK == retVal)
    {
        /* Get video pipe registers */
        socInfo = Dss_getSocInfo();
        pipeRegs = socInfo->pipeRegs[instObj->pipeId];
        GT_assert(DssTrace, (NULL != pipeRegs));

        Fvid2Utils_memcpy(&instObj->safetyChkParams,
                          safetyChkParams,
                          sizeof (Dss_DispPipeSafetyChkParams));

        /* Register for Safety Error Events */
        Dss_convModuletoEventGroup(&eventGroup,
                                   instObj->drvInstId,
                                   DSS_EVENT_GROUP_TYPE_PIPE);
        GT_assert(DssTrace, (DSS_EVENT_GROUP_INVALID != eventGroup));
        safetyEvt = DSS_PIPE_EVENT_SAFETY_VIOLATION;
        numHandle = instObj->numRegEvtHandle;
        evtMgrId = Dss_getEvtMgrSafetyIntrId();
        instObj->evtGroupHandle[instObj->numRegEvtHandle] =
                            Dss_evtMgrRegister(
                                evtMgrId,
                                eventGroup,
                                (const uint32_t *)&safetyEvt,
                                1U,
                                Dss_dispSafetyErrCbFxn,
                                (void *)&gDss_DispEvtMgrClientInfo[(instObj->drvInstId*DSS_DISP_INST_EVT_MGR_MAX_CLIENTS) + numHandle]);
        instObj->numRegEvtHandle++;

        /* Call CSL APIs */
        if(0U != safetyChkParams->safetySignSeedVal)
        {
            CSL_dssVidPipeSetSafetySignSeedVal(
                                        pipeRegs,
                                        safetyChkParams->safetySignSeedVal);
        }
        if(CSL_DSS_SAFETY_CHK_DATA_INTEGRITY ==
                                    safetyChkParams->safetyChkCfg.safetyChkMode)
        {
            CSL_dssVidPipeSetSafetyReferenceSign(
                            pipeRegs,
                            safetyChkParams->referenceSign);
        }
        safetyChkCfg = &safetyChkParams->safetyChkCfg;
        CSL_dssVidPipeSetSafetyChkConfig(pipeRegs, safetyChkCfg);
    }

    if(FVID2_SOK != retVal)
    {
        GT_0trace(DssTrace,
                  GT_ERR,
                  "Register Safety Error Cb Params IOCTL failed\r\n");
    }

    /* Post the instance semaphore */
    (void) SemaphoreP_post(&instObj->lockSem);

    return retVal;
}

static int32_t Dss_dispDrvSetPipeCscParamsIoctl(
                            Dss_DispDrvInstObj *instObj,
                            const CSL_DssCscCoeff *cscCoeff)
{
    int32_t retVal = FVID2_SOK;
    CSL_dss_pipeRegs *pipeRegs;
    const Dss_SocInfo *socInfo;

    GT_assert(DssTrace, (NULL != instObj));

    /* Check for wrong inputs */
    if((instObj->drvInstId >= DSS_DISP_INST_MAX) || (NULL == cscCoeff))
    {
        GT_0trace(DssTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    /* Take the instance semaphore */
    (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    /* Set csc coefficients here only if the csc range is custom. CSL will set appropriately
     * if the cscRange is FULL or LIMITED.
     */
    if(FVID2_SOK == retVal)
    {
        if(instObj->pipeParams[instObj->pipeId].pipeCfg.cscRange == CSL_DSS_CSC_RANGE_CUSTOM)
        {
            Fvid2Utils_memcpy(&instObj->pipeParams[instObj->pipeId].pipeCfg.custCscCoeff,
                            cscCoeff,
                            sizeof (CSL_DssCscCoeff));
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Get video pipe registers */
        socInfo = Dss_getSocInfo();
        pipeRegs = socInfo->pipeRegs[instObj->pipeId];
        GT_assert(DssTrace, (NULL != pipeRegs));

        CSL_dssVidPipeSetCSCCoeff(
                        pipeRegs,
                        (const CSL_DssCscCoeff *)(cscCoeff));
    }

    if(FVID2_SOK != retVal)
    {
        GT_0trace(DssTrace, GT_ERR, "Set CSC coefficients IOCTL failed\r\n");
    }

    /* Post the instance semaphore */
    (void) SemaphoreP_post(&instObj->lockSem);

    return (retVal);
}

static int32_t Dss_dispDrvSetBufPrgmCbParamsIoctl(
                            Dss_DispDrvInstObj *instObj,
                            const Dss_DispBufPrgmCbParams *bufPrgmCbParams)
{
    int32_t retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(DssTrace, (NULL != instObj));

    /* Check for wrong inputs */
    if((instObj->drvInstId >= DSS_DISP_INST_MAX) || (NULL == bufPrgmCbParams))
    {
        GT_0trace(DssTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    /* Take the instance semaphore */
    (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    if(FVID2_SOK == retVal)
    {
        /* IOCTL supported only when display is stopped */
        if(TRUE == instObj->drvState.isStarted)
        {
            GT_0trace(DssTrace, GT_ERR, "Display in progress!!\r\n");
            retVal = FVID2_EFAIL;
        }
    }

    if(FVID2_SOK == retVal)
    {
        instObj->bufPrgmCbParams.bufPrgmCbFxn = bufPrgmCbParams->bufPrgmCbFxn;
    }

    if(FVID2_SOK != retVal)
    {
        GT_0trace(DssTrace,
                  GT_ERR,
                  "Set buffer program callback IOCTL failed\r\n");
    }

    /* Post the instance semaphore */
    (void) SemaphoreP_post(&instObj->lockSem);

    return (retVal);
}

static int32_t Dss_dispDrvSetPipePrgmCbParamsIoctl(
                            Dss_DispDrvInstObj *instObj,
                            const Dss_DispPipePrgmCbParams *pipePrgmCbParams)
{
    int32_t retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(DssTrace, (NULL != instObj));

    /* Check for wrong inputs */
    if((instObj->drvInstId >= DSS_DISP_INST_MAX) || (NULL == pipePrgmCbParams))
    {
        GT_0trace(DssTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    /* Take the instance semaphore */
    (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    if(FVID2_SOK == retVal)
    {
        /* IOCTL supported only when display is stopped */
        if(TRUE == instObj->drvState.isStarted)
        {
            GT_0trace(DssTrace, GT_ERR, "Display in progress!!\r\n");
            retVal = FVID2_EFAIL;
        }
    }

    if(FVID2_SOK == retVal)
    {
        Fvid2Utils_memcpy(&instObj->pipePrgmCbParams,
                          pipePrgmCbParams,
                          sizeof (Dss_DispPipePrgmCbParams));
    }

    if(FVID2_SOK != retVal)
    {
        GT_0trace(DssTrace,
                  GT_ERR,
                  "Set pipe program callback IOCTL failed\r\n");
    }

    /* Post the instance semaphore */
    (void) SemaphoreP_post(&instObj->lockSem);

    return (retVal);
}

static int32_t Dss_dispDrvSetPipeUnderFlowCbParamsIoctl(
                            Dss_DispDrvInstObj *instObj,
                            const Dss_DispUnderFlowCbParams *underFlowCbParams)
{
    int32_t retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(DssTrace, (NULL != instObj));

    /* Check for wrong inputs */
    if((instObj->drvInstId >= DSS_DISP_INST_MAX) || (NULL == underFlowCbParams))
    {
        GT_0trace(DssTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    /* Take the instance semaphore */
    (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    if(FVID2_SOK == retVal)
    {
        /* IOCTL supported only when display is stopped */
        if(TRUE == instObj->drvState.isStarted)
        {
            GT_0trace(DssTrace, GT_ERR, "Display in progress!!\r\n");
            retVal = FVID2_EFAIL;
        }
    }

    if(FVID2_SOK == retVal)
    {
        Fvid2Utils_memcpy(&instObj->underFlowCbParams,
                          underFlowCbParams,
                          sizeof (Dss_DispUnderFlowCbParams));
    }

    if(FVID2_SOK != retVal)
    {
        GT_0trace(DssTrace,
                  GT_ERR,
                  "Set pipe underflow callback IOCTL failed\r\n");
    }

    /* Post the instance semaphore */
    (void) SemaphoreP_post(&instObj->lockSem);

    return (retVal);
}

static int32_t Dss_dispDrvValidateDssParams(const Dss_DispDrvInstObj *instObj,
                                            const Dss_DispParams *dispParams)
{
    int32_t retVal = FVID2_SOK;

    if((FALSE == Dss_dispIsVidInst(instObj->drvInstId)) &&
       (FALSE == Dss_dispIsVidLInst(instObj->drvInstId)))
    {
        GT_0trace(DssTrace,
                  GT_ERR,
                  "Invalid Driver Id\r\n");
        retVal = FVID2_EINVALID_PARAMS;
    }
    if(((dispParams->pipeCfg.outWidth + dispParams->layerPos.startX) >
                                                        instObj->dispWidth) ||
       ((dispParams->pipeCfg.outHeight + dispParams->layerPos.startY) >
                                                        instObj->dispHeight))
    {
        GT_0trace(DssTrace,
                  GT_ERR,
                  "Input width+startX/height+startY > display width/height\r\n");
        retVal = FVID2_EINVALID_PARAMS;
    }

    /* Interlaced to progressive or vice versa*/
    if(dispParams->pipeCfg.inFmt.scanFormat != instObj->dispScanFormat)
    {
        GT_0trace(DssTrace,
                  GT_ERR,
                  "Format(interlaced/progressive) conversion not supported\r\n");
        retVal = FVID2_EINVALID_PARAMS;
    }

    /* Scaling ratio check */
    if(((dispParams->pipeCfg.inFmt.height * 16U) <
                                        (dispParams->pipeCfg.outHeight)) ||
       ((dispParams->pipeCfg.inFmt.width * 16U) <
                                        (dispParams->pipeCfg.outWidth)))
    {
        GT_0trace(DssTrace,
                  GT_ERR,
                  "Upscaling ratio is more than 16x \r\n");
        retVal = FVID2_EINVALID_PARAMS;
    }
    if(((dispParams->pipeCfg.inFmt.height) >
                                    (dispParams->pipeCfg.outHeight * 4U)) ||
       ((dispParams->pipeCfg.inFmt.width) >
                                    (dispParams->pipeCfg.outWidth * 4U)))
    {
        GT_0trace(DssTrace,
                  GT_ERR,
                  "Downscaling ratio is more than 0.25x \r\n");
        retVal = FVID2_EINVALID_PARAMS;
    }

    if((dispParams->pipeCfg.inFmt.height != dispParams->pipeCfg.outHeight) ||
       (dispParams->pipeCfg.inFmt.width != dispParams->pipeCfg.outWidth))
    {
        if(TRUE == Dss_dispIsVidLInst(instObj->drvInstId))
        {
            GT_0trace(DssTrace,
                      GT_ERR,
                      "Scaling cant be enabled for video lite pipe \r\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
        if(FALSE == dispParams->pipeCfg.scEnable)
        {
            GT_0trace(DssTrace,
                      GT_ERR,
                      "Scaling should be enabled \r\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
    }

    if((dispParams->cropParams.cropCfg.cropTop >= 32U) ||
       (dispParams->cropParams.cropCfg.cropBottom >= 32U) ||
       (dispParams->cropParams.cropCfg.cropLeft >= 32U) ||
       (dispParams->cropParams.cropCfg.cropRight >= 32U))
    {
        GT_0trace(DssTrace,
                  GT_ERR,
                  "Crop Parameter(s) should be less than 32 \r\n");
        retVal = FVID2_EINVALID_PARAMS;
    }

    if(((dispParams->pipeCfg.flipType == FVID2_FLIP_TYPE_V) ||
        (dispParams->pipeCfg.flipType == FVID2_FLIP_TYPE_H)) &&
       ((dispParams->pipeCfg.inFmt.dataFormat == FVID2_DF_RGB24_888) ||
        (dispParams->pipeCfg.inFmt.dataFormat == FVID2_DF_BGR24_888)))
    {
        GT_0trace(DssTrace,
                  GT_ERR,
                  "Flip Parameter(s) should not be used for 24-bit RGB/BGR formats \r\n");
        retVal = FVID2_EINVALID_PARAMS;
    }

    /* There is a limitation with scaling in DSS, where maximum scaling ratio
     * supported is the ratio of the DSS functional clock and Pixel Clock.
     * Driver can't check this condition as it is unaware of Pixel Clock.
     * So it should be checked by the application.
     */
    return retVal;
}

static int32_t Dss_dispDrvValidateRtParams(const Dss_DispDrvInstObj *instObj,
                                           const Dss_DispRtParams *rtParams)
{
    int32_t retVal = FVID2_SOK;
    const Dss_DispParams *pipeParams;
    const Dss_FrameRtParams *frameRtParams;

    if(NULL != rtParams->outFrmParams)
    {
        if(((rtParams->outFrmParams->width + rtParams->posCfg->startX) >
                                                        instObj->dispWidth) ||
           ((rtParams->outFrmParams->height + rtParams->posCfg->startY) >
                                                        instObj->dispHeight))
        {
            retVal = FVID2_EINVALID_PARAMS;
        }
    }

    if((NULL != rtParams->outFrmParams) && (NULL != rtParams->inFrmParams))
    {
        /* Scaling ratio check */
        if(((rtParams->inFrmParams->height * 16U) <
                                    (rtParams->outFrmParams->height)) ||
           ((rtParams->inFrmParams->width * 16U) <
                                    (rtParams->outFrmParams->width)))
        {
            retVal = FVID2_EINVALID_PARAMS;
        }
        if(((rtParams->inFrmParams->height) >
                                    (rtParams->outFrmParams->height * 4U)) ||
           ((rtParams->inFrmParams->width) >
                                    (rtParams->outFrmParams->width * 4U)))
        {
            retVal = FVID2_EINVALID_PARAMS;
        }
        if((rtParams->inFrmParams->height != rtParams->outFrmParams->height) ||
           (rtParams->inFrmParams->width != rtParams->outFrmParams->width))
        {
            if(TRUE == Dss_dispIsVidLInst(instObj->drvInstId))
            {
                retVal = FVID2_EINVALID_PARAMS;
            }
        }
    }

    if(NULL != rtParams->inFrmParams)
    {
        pipeParams = &instObj->pipeParams[instObj->pipeId];
        frameRtParams = rtParams->inFrmParams;
        if(((pipeParams->pipeCfg.flipType == FVID2_FLIP_TYPE_V) ||
           (pipeParams->pipeCfg.flipType == FVID2_FLIP_TYPE_H)) &&
          ((frameRtParams->dataFormat == FVID2_DF_RGB24_888) ||
           (frameRtParams->dataFormat == FVID2_DF_BGR24_888)))
        {
            GT_0trace(DssTrace,
                      GT_ERR,
                      "Flip Parameter(s) should not be used for 24-bit RGB/BGR formats \r\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
    }

    /* There is a limitation with scaling in DSS, where maximum scaling ratio
     * supported is the ratio of the DSS functional clock and Pixel Clock.
     * Driver can't check this condition as it is unaware of Pixel Clock.
     * So it should be checked by the application.
     */
    return retVal;
}

static int32_t Dss_dispDrvApplyRtParams(Dss_DispDrvInstObj *instObj,
                                        const Dss_DispRtParams *rtParams)
{
    int32_t rtParamsRetVal = FVID2_SOK;
    uint32_t i, layerNum;
    CSL_dss_pipeRegs *pipeRegs;
    CSL_dss_overlayRegs *overlayRegs;
    const Dss_SocInfo *socInfo;
    uint32_t pipeRtUpdate = FALSE;
    Dss_DctrlDrvPipeInfo *pipeInfo;
    CSL_DssOverlayPipePosCfg overlayPosCfg;
    Dss_DispParams *pipeParams;

    /* Get video pipe registers */
    socInfo = Dss_getSocInfo();
    pipeRegs = socInfo->pipeRegs[instObj->pipeId];
    GT_assert(DssTrace, (NULL != pipeRegs));

    pipeParams = &instObj->pipeParams[instObj->pipeId];
    if(NULL != rtParams->scParams)
    {
        pipeRtUpdate = TRUE;
        pipeParams->pipeCfg.pixelInc = rtParams->scParams->pixelInc;
    }
    if(NULL != rtParams->inFrmParams)
    {
        pipeRtUpdate = TRUE;
        pipeParams->pipeCfg.inFmt.width  = rtParams->inFrmParams->width;
        pipeParams->pipeCfg.inFmt.height = rtParams->inFrmParams->height;
        pipeParams->pipeCfg.inFmt.dataFormat =
                                            rtParams->inFrmParams->dataFormat;
        for(i=0U; i<FVID2_MAX_PLANES; i++)
        {
            pipeParams->pipeCfg.inFmt.pitch[i] =
                                            rtParams->inFrmParams->pitch[i];
        }
    }
    if((NULL != rtParams->outFrmParams) &&
       (TRUE == Dss_dispIsVidInst(instObj->drvInstId)))
    {
        pipeRtUpdate = TRUE;
        pipeParams->pipeCfg.outWidth  = rtParams->outFrmParams->width;
        pipeParams->pipeCfg.outHeight = rtParams->outFrmParams->height;
    }
    if(TRUE == pipeRtUpdate)
    {
        rtParamsRetVal =
            CSL_dssVidPipeSetConfig(
                        pipeRegs,
                        (const CSL_DssVidPipeCfg *)(&pipeParams->pipeCfg),
                        (const CSL_DssVidPipeVC1Cfg *)(&pipeParams->vc1Cfg));
        GT_assert(DssTrace, (FVID2_SOK == rtParamsRetVal));
    }
    if(NULL != rtParams->posCfg)
    {
        pipeInfo = Dss_dctrlDrvGetPipeInfo(instObj->dctrlHandle);
        /* Get overlay registers */
        overlayRegs = socInfo->overlayRegs[pipeInfo->overlayId];
        GT_assert(DssTrace, (NULL != overlayRegs));
        layerNum = CSL_dssOverlayGetEnabledPipeLayerNum(overlayRegs,
                                                        pipeInfo->pipeId);
        GT_assert(DssTrace, (layerNum < CSL_DSS_OVERLAY_LAYER_MAX));
        overlayPosCfg.layerPos.startX = rtParams->posCfg->startX;
        overlayPosCfg.layerPos.startY = rtParams->posCfg->startY;
        CSL_dssOverlaySetPipePosConfig(
                            overlayRegs,
                            (const CSL_DssOverlayPipePosCfg *)(&overlayPosCfg),
                            layerNum);
        pipeInfo->startX = rtParams->posCfg->startX;
        pipeInfo->startY = rtParams->posCfg->startY;
    }
    return rtParamsRetVal;
}

static void Dss_dispSafetyErrCbFxn(const uint32_t *event,
                                   uint32_t numEvents,
                                   void *arg)
{
    uint32_t  i, currEvent, pipeId = 0U;
    Dss_EvtMgrClientInfo *pClientObj = (Dss_EvtMgrClientInfo *)arg;
    uint32_t eventGroup = pClientObj->eventGroup;
    Dss_DispDrvInstObj *instObj;
    CSL_dss_pipeRegs *pipeRegs;
    const Dss_SocInfo *socInfo;

    /* Get pipe id */
    Dss_convEventGrouptoModule(eventGroup, &pipeId);
    GT_assert(DssTrace, (CSL_DSS_MODULE_INVALID != pipeId));
    instObj = Dss_dispDrvGetInstObj(pipeId);
    /* Instobj cannot be NULL */
    GT_assert(DssTrace, (NULL != instObj));
    /* Get video pipe registers */
    socInfo = Dss_getSocInfo();
    pipeRegs = socInfo->pipeRegs[pipeId];
    GT_assert(DssTrace, (NULL != pipeRegs));

    for(i=0U; i<numEvents; i++)
    {
        currEvent = event[i];
        if(DSS_PIPE_EVENT_SAFETY_VIOLATION == currEvent)
        {
            instObj->currStatus.safetyViolationCount++;
            instObj->safetyChkParams.capturedSign =
                                        CSL_dssVidPipeGetSafetySign(pipeRegs);

            if(NULL != instObj->safetyChkParams.safetyErrCbFxn)
            {
                instObj->safetyChkParams.safetyErrCbFxn(pipeId,
                                         instObj->safetyChkParams.capturedSign,
                                         instObj->safetyChkParams.appData);
            }
        }
        else
        {
            GT_assert(DssTrace, FALSE);
        }
    }

    return;
}

static uint32_t Dss_dispIsFarFromVsync(const Dss_DispDrvInstObj *instObj)
{
    uint32_t isFarFromVsync = FALSE;

    isFarFromVsync = Dss_dctrlDrvIsSafeToPush(instObj->dctrlHandle);

    if(instObj->dispHeight <= DSS_DISP_NUM_LINES_NEAR_VSYNC)
    {
        isFarFromVsync = FALSE;
    }

    return isFarFromVsync;
}
