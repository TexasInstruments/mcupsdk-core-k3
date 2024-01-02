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
 *  \file dss_dctrlApi.c
 *
 *  \brief File containing the DSS Controller driver implementation.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <kernel/dpl/SemaphoreP.h>
#include <drivers/dss.h>
#include <drivers/dss/v0/common/dss_evtMgr.h>
#include <drivers/dss/v0/dctrl/dss_dctrlDrv.h>
#include <drivers/dss/v0/dctrl/dss_dctrlPriv.h>
#include <drivers/dss/v0/dctrl/dss_dctrlIntr.h>
#include <drivers/dss/v0/soc/dss_soc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

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
 * Display Controller APIs
 */
static Fdrv_Handle Dss_dctrlDrvCreate(uint32_t drvId,
                                      uint32_t instId,
                                      void *createArgs,
                                      void *createStatusArgs,
                                      const Fvid2_DrvCbParams *fdmCbParams);
static int32_t Dss_dctrlDrvDelete(Fdrv_Handle handle, void *reserved);
static int32_t Dss_dctrlDrvControl(Fdrv_Handle handle,
                                   uint32_t cmd,
                                   void *cmdArgs,
                                   void *cmdStatusArgs);
#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

Dss_DctrlDrvCommonObj gDss_DctrlDrvCommonObj;
Dss_DctrlDrvInstObj   gDss_DctrlDrvInstObj;

Dss_DctrlDrvGraphObj gDss_DctrlDrvGraphObj;
Dss_DctrlDrvInfo gDss_DctrlDrvInfo;
Dss_EvtMgrClientInfo gDss_DctrlEvtMgrClientInfo[DSS_DCTRL_EVT_MGR_MAX_CLIENTS];

/* Semaphore to sync up back to back Fvid2_start() calls.
   A VSYNC is needed between back to back Fvid2_start() calls. */
SemaphoreP_Object gDssStartSyncSem;
/* ========================================================================== */
/*                  Internal/Private Function Declarations                    */
/* ========================================================================== */

static int32_t Dss_dctrlDrvSetPathIoctl(Dss_DctrlDrvInstObj *instObj,
                                        const Dss_DctrlPathInfo *pathInfo);
static int32_t Dss_dctrlDrvClearPathIoctl(Dss_DctrlDrvInstObj *instObj,
                                          const Dss_DctrlPathInfo *pathInfo);
static int32_t Dss_dctrlDrvSetVpParamsIoctl(
                            Dss_DctrlDrvInstObj *instObj,
                            const Dss_DctrlVpParams *vpParams);
static int32_t Dss_dctrlDrvSetOverlayParamsIoctl(
                            Dss_DctrlDrvInstObj *instObj,
                            const Dss_DctrlOverlayParams *overlayParams);
static int32_t Dss_dctrlDrvSetLayerParamsIoctl(
                            Dss_DctrlDrvInstObj *instObj,
                            const Dss_DctrlOverlayLayerParams *layerParams);
static int32_t Dss_dctrlDrvSetVpCscCoeffIoctl(
                            Dss_DctrlDrvInstObj *instObj,
                            const Dss_DctrlVpCscCoeff *vpCscCoeff);
static int32_t Dss_dctrlDrvSetAdvVpParamsIoctl(
                            Dss_DctrlDrvInstObj *instObj,
                            const Dss_DctrlAdvVpParams *advVpParams);
static int32_t Dss_dctrlDrvSetLcdBlankTimingIoctl(
                            Dss_DctrlDrvInstObj *instObj,
                            const Dss_DctrlLcdBlankTimingParams *timingParams);
static int32_t Dss_dctrlDrvSetVpSafetyChkParamsIoctl(
                            Dss_DctrlDrvInstObj *instObj,
                            const Dss_DctrlVpSafetyChkParams *safetyChkParams);
static int32_t Dss_dctrlDrvGetErrorStatsIoctl(
                            Dss_DctrlDrvInstObj *instObj,
                            Dss_DctrlVpErrorStats *vpErrStats);
static int32_t Dss_dctrlDrvSetGlobalDssParamsIoctl(
                            Dss_DctrlDrvInstObj *instObj,
                            const Dss_DctrlGlobalDssParams *globalDssParams);
static int32_t Dss_dctrlDrvStopVpIoctl(Dss_DctrlDrvInstObj *instObj,
                                       const Dss_DctrlVpParams *vpParams);
static int32_t Dss_dctrlDrvSetSyncLostCbParamsIoctl(
                            Dss_DctrlDrvInstObj *instObj,
                            const Dss_DctrlSyncLostCbParams *syncLostCbParams);
static int32_t Dss_dctrlDrvSetLineNumCbParamsIoctl(
                            Dss_DctrlDrvInstObj *instObj,
                            const Dss_DctrlLineNumCbParams *lineNumCbParams);
static void Dss_dctrlFuncCbFxn(const uint32_t *event,
                               uint32_t numEvents,
                               void *arg);
static void Dss_dctrlErrCbFxn(const uint32_t *event,
                              uint32_t numEvents,
                              void *arg);
static void Dss_dctrlSafetyErrCbFxn(const uint32_t *event,
                                    uint32_t numEvents,
                                    void *arg);
static int32_t Dss_dctrlConnectNodes(uint32_t inputNode, uint32_t outNode);
static int32_t Dss_dctrlDrvSetOldiParamsIoctl(
                            Dss_DctrlDrvInstObj *instObj,
                            const Dss_DctrlOldiParams *oldiParams);
static void Dss_dctrlVpSetGoBit(uint32_t vpId);
static void Dss_dctrlVpReset(uint32_t vpId);
static void Dss_dctrlVpEnable(uint32_t vpId, uint32_t enable);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t Dss_dctrlDrvInit(const Dss_DctrlDrvInitParams *drvInitParams)
{
    int32_t retVal = FVID2_SOK;
    int32_t status = SystemP_SUCCESS;
    uint32_t i, cnt, eventGroup, vpId, numHandle, numEvents, evtMgrId;
    uint32_t enabledEvents[DSS_EVT_MGR_MAX_CLIENT_EVENTS];
    Dss_DctrlDrvInfo *pDrvInfo;
    Dss_DctrlDrvCommonObj *pObj;
    Dss_DctrlDrvGraphObj *pGraphObj;
    Dss_DctrlDrvInstObj *pDrvInstObj;
    Dss_EvtMgrClientInfo *pClientInfo;

    pDrvInfo = &gDss_DctrlDrvInfo;
    pObj = &gDss_DctrlDrvCommonObj;
    pGraphObj = &gDss_DctrlDrvGraphObj;
    pDrvInstObj = &gDss_DctrlDrvInstObj;

    Fvid2Utils_memset(pObj, 0U, sizeof (Dss_DctrlDrvCommonObj));
    Fvid2Utils_memset(pGraphObj, 0U, sizeof (Dss_DctrlDrvGraphObj));
    Fvid2Utils_memset(pDrvInfo, 0U, sizeof (Dss_DctrlDrvInfo));
    Fvid2Utils_memset(pDrvInstObj, 0U, sizeof (Dss_DctrlDrvInstObj));

    for(i=0U; i<DSS_DCTRL_EVT_MGR_MAX_CLIENTS; i++)
    {
        pClientInfo = &gDss_DctrlEvtMgrClientInfo[i];
        Fvid2Utils_memset(pClientInfo, 0U, sizeof (Dss_EvtMgrClientInfo));
    }
    /* Initialize instance object members */
    pObj->instObj = &gDss_DctrlDrvInstObj;
    pObj->instObj->drvInstId = drvInitParams->drvInstId;

    /* Initialize graph object */
    (void) Dss_dctrlDrvGraphInit(pGraphObj);

    if(FVID2_SOK == retVal)
    {
        /* Allocate instance semaphore */
        status = SemaphoreP_constructBinary(&pObj->instObj->lockSem,  1U);
        if (status != SystemP_SUCCESS)
        {
            GT_0trace(DssTrace,
                    GT_ERR,
                    "Instance semaphore create failed!!\r\n");
            retVal = FVID2_EALLOC;
        }

        for(i=0U; i<CSL_DSS_VID_PIPE_ID_MAX; i++)
        {
            /* Allocate instance semaphore */
            status = SemaphoreP_constructBinary(&pDrvInfo->pipeInfo[i].stopSem, 0);
            if(status != SystemP_SUCCESS)
            {
                GT_0trace(DssTrace,
                        GT_ERR,
                        "Sync Stop semaphore create failed!!\r\n");
                retVal = FVID2_EALLOC;
            }
        }

        for(i=0U; i<CSL_DSS_VP_ID_MAX; i++)
        {
            pDrvInfo->vpState[i] = DSS_DCTRL_VP_IDLE;
        }

        pObj->instObj->drvState.isInit = TRUE;
        pObj->instObj->drvState.isOpened = FALSE;
        pObj->instObj->drvState.isStarted = FALSE;
    }

    if(FVID2_SOK == retVal)
    {
        /* Register for Video Port events */
        for(cnt=0U; cnt<drvInitParams->numAvailablePorts; cnt++)
        {
            vpId = drvInitParams->availablePortId[cnt];
            Dss_convModuletoEventGroup(&eventGroup,
                                       vpId,
                                       DSS_EVENT_GROUP_TYPE_VP);
            GT_assert(DssTrace, (DSS_EVENT_GROUP_INVALID != eventGroup));

            /* Register functional events */
            Dss_getEnabledVpFuncEvents(&enabledEvents[0U], &numEvents);
            numHandle = pObj->instObj->numRegEvtHandle;
            evtMgrId = Dss_getEvtMgrFuncIntrId();
            pObj->instObj->evtGroupHandle[pObj->instObj->numRegEvtHandle] =
                            Dss_evtMgrRegister(
                                evtMgrId,
                                eventGroup,
                                (const uint32_t *)&enabledEvents[0U],
                                numEvents,
                                Dss_dctrlFuncCbFxn,
                                (void *)&gDss_DctrlEvtMgrClientInfo[numHandle]);
            pObj->instObj->numRegEvtHandle++;

            /* Register error events */
            Dss_getEnabledVpErrEvents(&enabledEvents[0U], &numEvents);
            numHandle = pObj->instObj->numRegEvtHandle;
            pObj->instObj->evtGroupHandle[pObj->instObj->numRegEvtHandle] =
                            Dss_evtMgrRegister(
                                evtMgrId,
                                eventGroup,
                                (const uint32_t *)&enabledEvents[0U],
                                numEvents,
                                Dss_dctrlErrCbFxn,
                                (void *)&gDss_DctrlEvtMgrClientInfo[numHandle]);
            pObj->instObj->numRegEvtHandle++;
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Initialize Driver operations */
        Fvid2DrvOps_init(&pObj->fvidDrvOps);

        pObj->fvidDrvOps.drvId = DSS_DCTRL_DRV_ID;
        pObj->fvidDrvOps.createFxn = &Dss_dctrlDrvCreate;
        pObj->fvidDrvOps.deleteFxn = &Dss_dctrlDrvDelete;
        pObj->fvidDrvOps.controlFxn = &Dss_dctrlDrvControl;

        retVal = Fvid2_registerDriver(&pObj->fvidDrvOps);
        if(FVID2_SOK != retVal)
        {
            GT_0trace(DssTrace,
                      GT_ERR,
                      "Registering to FVID2 driver manager failed\r\n");
        }
        else
        {
            /* Init successful */
            pObj->isRegistered = TRUE;

            /* Copy Init params to local object, for future use. */
            Fvid2Utils_memcpy(&pObj->drvInitParams, drvInitParams,
                sizeof (Dss_DctrlDrvInitParams));
        }
    }
    if (FVID2_SOK == retVal)
    {
        /* create semaphore */
        SemaphoreP_constructBinary(&gDssStartSyncSem,  1U);
    }

    return (retVal);
}

int32_t Dss_dctrlDrvDeInit(void)
{
    int32_t retVal = FVID2_SOK;
    uint32_t cnt, numRegEvtHandle, i, vpFound = FALSE;;
    Dss_DctrlDrvCommonObj *pObj;
    Dss_DctrlDrvInstObj *instObj;
    Dss_DctrlDrvGraphObj *pGraphObj;
    Dss_DctrlDrvInfo *pDrvInfo;
    pObj = &gDss_DctrlDrvCommonObj;
    pGraphObj = &gDss_DctrlDrvGraphObj;
    pDrvInfo = &gDss_DctrlDrvInfo;
    if(NULL != pObj->instObj)
    {
        instObj = pObj->instObj;
        if(instObj->drvState.isOpened == TRUE)
        {
            GT_0trace(DssTrace,
                      GT_ERR,
                      "Can't de-initialize when an instance is active\r\n");
            retVal = FVID2_EFAIL;
        }

        for(i=0U; i<CSL_DSS_VP_ID_MAX; i++)
        {
            if(DSS_DCTRL_VP_IDLE != pDrvInfo->vpState[i])
            {
                vpFound = TRUE;
                break;
            }
        }
        if(TRUE == vpFound)
        {
            GT_0trace(DssTrace,
                    GT_ERR,
                    "Can't de-initialize when a VP is running\r\n");
            retVal = FVID2_EFAIL;
        }

        /* Delete the graph object */
        Dss_dctrlDrvGraphDeInit((void *) pGraphObj);

        numRegEvtHandle = instObj->numRegEvtHandle;
        /* Unregister event groups and delete object */
        for(cnt=0U; cnt<numRegEvtHandle; cnt++)
        {
            (void) Dss_evtMgrUnRegister(instObj->evtGroupHandle[cnt]);
            instObj->numRegEvtHandle--;
        }

        /* Delete the instance semaphore */
        SemaphoreP_destruct(&instObj->lockSem);

        for(i=0U; i<CSL_DSS_VID_PIPE_ID_MAX; i++)
        {
          SemaphoreP_destruct(&pDrvInfo->pipeInfo[i].stopSem);
        }

        instObj->drvState.isInit = FALSE;
        pObj->instObj = NULL;
    }

    if(TRUE == pObj->isRegistered)
    {
        /* Unregister from driver manager */
        retVal = Fvid2_unRegisterDriver(&pObj->fvidDrvOps);
        if(FVID2_SOK != retVal)
        {
            GT_0trace(DssTrace,
                      GT_ERR,
                      "Unregistering from FVID2 driver manager failed\r\n");
        }
        pObj->isRegistered = FALSE;
    }

    /* Delete start sync semaphore */
    SemaphoreP_destruct(&gDssStartSyncSem);

    return (retVal);
}

DssDctrlDrvClientHandle Dss_dctrlDrvRegisterClient(
                                    uint32_t nodeId,
                                    const Dss_DctrlDrvClientInfo *clientInfo)
{
    uint32_t i;
    DssDctrlDrvClientHandle clientHandle = NULL;
    GT_assert(DssTrace, (NULL != clientInfo));
    GT_assert(DssTrace,
              (gDss_DctrlDrvInfo.numValidPipes <= CSL_DSS_VID_PIPE_ID_MAX));

    for(i=0U; i<gDss_DctrlDrvInfo.numValidPipes; i++)
    {
        if(gDss_DctrlDrvInfo.pipeInfo[i].pipeNodeId == nodeId)
        {
            gDss_DctrlDrvInfo.pipeInfo[i].gClientInfo.cbFxn = clientInfo->cbFxn;
            gDss_DctrlDrvInfo.pipeInfo[i].gClientInfo.arg = clientInfo->arg;
            gDss_DctrlDrvInfo.pipeInfo[i].pipeState = DSS_DCTRL_PIPE_OPENED;
            clientHandle = &gDss_DctrlDrvInfo.pipeInfo[i];
            break;
        }
    }

    return clientHandle;
}

int32_t Dss_dctrlDrvUnRegisterClient(DssDctrlDrvClientHandle handle)
{
    int32_t retVal = FVID2_SOK;
    Dss_DctrlDrvPipeInfo *pipeInfo;
    GT_assert(DssTrace, (NULL != handle));

    pipeInfo = (Dss_DctrlDrvPipeInfo *) handle;
    pipeInfo->gClientInfo.cbFxn = NULL;
    pipeInfo->gClientInfo.arg = NULL;
    pipeInfo->pipeState = DSS_DCTRL_PIPE_IDLE;

    return retVal;
}

int32_t Dss_dctrlDrvStartClient(DssDctrlDrvClientHandle handle,
                                uint32_t dummyStart)
{
    int32_t retVal = FVID2_SOK;
    uint32_t cookie;
    Dss_DctrlDrvPipeInfo *pipeInfo;
    GT_assert(DssTrace, (NULL != handle));

    cookie = HwiP_disable();

    pipeInfo = (Dss_DctrlDrvPipeInfo *) handle;
    if(TRUE == dummyStart)
    {
        pipeInfo->pipeState = DSS_DCTRL_PIPE_STARTING;
    }
    else
    {
        pipeInfo->pipeState = DSS_DCTRL_PIPE_STARTED;
    }

    if(FALSE == dummyStart)
    {
        retVal = Dss_dctrlDrvSetGoBit(handle);
    }

    HwiP_restore(cookie);

    return retVal;
}

int32_t Dss_dctrlDrvStopClient(DssDctrlDrvClientHandle handle,
                               uint32_t syncStop)
{
    int32_t retVal = FVID2_SOK;
    uint32_t cookie;
    Dss_DctrlDrvPipeInfo *pipeInfo;
    GT_assert(DssTrace, (NULL != handle));

    cookie = HwiP_disable();
    pipeInfo = (Dss_DctrlDrvPipeInfo *) handle;
    if(TRUE == syncStop)
    {
        pipeInfo->pipeState = DSS_DCTRL_PIPE_STOPPING;
    }
    else
    {
        pipeInfo->pipeState = DSS_DCTRL_PIPE_STOPPED;
    }

    if(FALSE == syncStop)
    {
        retVal = Dss_dctrlDrvSetGoBit(handle);
    }

    HwiP_restore(cookie);

    /* Take the stop semaphore */
    (void) SemaphoreP_pend(&pipeInfo->stopSem, SystemP_WAIT_FOREVER);
    return retVal;
}

int32_t Dss_dctrlDrvGetVpParams(DssDctrlDrvClientHandle handle,
                                Dss_DctrlVpParams *vpParams)
{
    int32_t retVal = FVID2_SOK;
    uint32_t i;
    Dss_DctrlDrvPipeInfo *pipeInfo;
    Dss_DctrlDrvInstObj *instObj;
    Dss_DctrlDrvCommonObj *pObj = &gDss_DctrlDrvCommonObj;
    GT_assert(DssTrace, (NULL != handle));

    instObj = pObj->instObj;

    /* Take the instance semaphore */
    (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    /* Get VP Params */
    pipeInfo = (Dss_DctrlDrvPipeInfo *) handle;
    for(i=0U; i<CSL_DSS_VP_ID_MAX; i++)
    {
        if(pipeInfo->vpId == gDss_DctrlDrvInfo.vpParams[i].vpId)
        {
            vpParams->lcdOpTimingCfg.mInfo.scanFormat =
                    gDss_DctrlDrvInfo.vpParams[i].lcdOpTimingCfg.mInfo.scanFormat;
            vpParams->lcdOpTimingCfg.mInfo.standard =
                    gDss_DctrlDrvInfo.vpParams[i].lcdOpTimingCfg.mInfo.standard;
            vpParams->lcdOpTimingCfg.mInfo.width =
                    gDss_DctrlDrvInfo.vpParams[i].lcdOpTimingCfg.mInfo.width;
            vpParams->lcdOpTimingCfg.mInfo.height =
                    gDss_DctrlDrvInfo.vpParams[i].lcdOpTimingCfg.mInfo.height;
            vpParams->vpId = gDss_DctrlDrvInfo.vpParams[i].vpId;
            break;
        }
    }

    /* Post the instance semaphore */
    (void) SemaphoreP_post(&instObj->lockSem);

    return retVal;
}

int32_t Dss_dctrlDrvSetGoBit(DssDctrlDrvClientHandle handle)
{
    int32_t retVal = FVID2_SOK;
    Dss_DctrlDrvPipeInfo *pipeInfo;
    GT_assert(DssTrace, (NULL != handle));

    pipeInfo = (Dss_DctrlDrvPipeInfo *) handle;

    /* Set Go Bit */
    Dss_dctrlVpSetGoBit(pipeInfo->vpId);

    return (retVal);
}

uint32_t Dss_dctrlDrvIsSafeToPush(DssDctrlDrvClientHandle handle)
{
    uint32_t retVal = FALSE, cookie;
    Dss_DctrlDrvPipeInfo *pipeInfo;
    GT_assert(DssTrace, (NULL != handle));

    pipeInfo = (Dss_DctrlDrvPipeInfo *) handle;
    cookie = HwiP_disable();
    retVal = gDss_DctrlDrvInfo.isPushSafe[pipeInfo->vpId];
    HwiP_restore(cookie);

    return retVal;
}

Dss_DctrlDrvPipeInfo *Dss_dctrlDrvGetPipeInfo(DssDctrlDrvClientHandle handle)
{
    uint32_t i;
    Dss_DctrlDrvPipeInfo *pipeInfo;
    GT_assert(DssTrace, (NULL != handle));

    pipeInfo = (Dss_DctrlDrvPipeInfo *) handle;
    for(i=0U; i<gDss_DctrlDrvInfo.numValidPipes; i++)
    {
        if((gDss_DctrlDrvInfo.pipeInfo[i].pipeId == pipeInfo->pipeId) &&
           ((gDss_DctrlDrvInfo.pipeInfo[i].pipeState ==
                                            DSS_DCTRL_PIPE_OPENED)   ||
            (gDss_DctrlDrvInfo.pipeInfo[i].pipeState ==
                                            DSS_DCTRL_PIPE_STARTING) ||
            (gDss_DctrlDrvInfo.pipeInfo[i].pipeState ==
                                            DSS_DCTRL_PIPE_STARTED)  ||
            (gDss_DctrlDrvInfo.pipeInfo[i].pipeState ==
                                            DSS_DCTRL_PIPE_RUNNING)  ||
            (gDss_DctrlDrvInfo.pipeInfo[i].pipeState ==
                                            DSS_DCTRL_PIPE_STOPPING) ||
            (gDss_DctrlDrvInfo.pipeInfo[i].pipeState ==
                                            DSS_DCTRL_PIPE_STOPPED)))
        {
            break;
        }
    }
    return &gDss_DctrlDrvInfo.pipeInfo[i];
}

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static Fdrv_Handle Dss_dctrlDrvCreate(uint32_t drvId,
                                      uint32_t instId,
                                      void *createArgs,
                                      void *createStatusArgs,
                                      const Fvid2_DrvCbParams *fdmCbParams)
{
    int32_t retVal = FVID2_SOK;
    Fdrv_Handle drvHandle = NULL;
    Dss_DctrlDrvInstObj *instObj = NULL;
    Dss_DctrlDrvCommonObj *pObj;

    pObj = &gDss_DctrlDrvCommonObj;

    GT_assert(DssTrace, (NULL != pObj));
    GT_assert(DssTrace, (NULL != pObj->instObj));

    instObj = pObj->instObj;

    if(NULL == instObj)
    {
        GT_0trace(DssTrace, GT_ERR, "Invalid instance ID\r\n");
        retVal = FVID2_EINVALID_PARAMS;
    }

    if(NULL != instObj)
    {
        /* Take the instance semaphore */
        (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);
    }

    if(FVID2_SOK == retVal)
    {
        /* Initialize instance variables */
        if(0U == instObj->numOpenDrvHandle)
        {
            instObj->drvState.isOpened = TRUE;
        }
        instObj->numOpenDrvHandle++;
        drvHandle = instObj;
    }

    if(NULL != instObj)
    {
        /* Post the instance semaphore */
        (void) SemaphoreP_post(&instObj->lockSem);
    }

    return (drvHandle);
}

static int32_t Dss_dctrlDrvDelete(Fdrv_Handle handle, void *reserved)
{
    int32_t retVal = FVID2_SOK;

    Dss_DctrlDrvInstObj *instObj = NULL, *pInstObj = NULL;
    Dss_DctrlDrvCommonObj *pObj;

    /* Check for NULL pointers and invalid arguments */
    if(NULL == handle)
    {
        GT_0trace(DssTrace, GT_ERR, "Invalid arguments\r\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        instObj = (Dss_DctrlDrvInstObj *) handle;
        pObj = &gDss_DctrlDrvCommonObj;
        pInstObj = pObj->instObj;
    }

    if(instObj != pInstObj)
    {
        GT_0trace(DssTrace, GT_ERR, "Invalid arguments\r\n");
        retVal = FVID2_EBADARGS;
    }

    if((NULL != instObj) && (FVID2_SOK == retVal))
    {
        /* Take the instance semaphore */
        (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

        /* Check if already opened. */
        if(TRUE != instObj->drvState.isOpened)
        {
            GT_0trace(DssTrace, GT_ERR, "ERROR: Driver not opened\r\n");
            retVal = FVID2_EFAIL;
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Reset other variables */
        instObj->numOpenDrvHandle--;
        if(0U == instObj->numOpenDrvHandle)
        {
            instObj->drvState.isOpened  = FALSE;
            instObj->drvState.isStarted = FALSE;
        }
    }

    if(NULL != instObj)
    {
        /* Post the instance semaphore */
        (void) SemaphoreP_post(&instObj->lockSem);
    }

    return (retVal);
}

static int32_t Dss_dctrlDrvControl(Fdrv_Handle handle,
                                   uint32_t cmd,
                                   void *cmdArgs,
                                   void *cmdStatusArgs)
{
    int32_t retVal = FVID2_SOK;
    Dss_DctrlDrvInstObj *instObj;

    /* Check for NULL pointers */
    if((NULL == handle) || (NULL == cmdArgs))
    {
        GT_0trace(DssTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        instObj = (Dss_DctrlDrvInstObj *) handle;
        switch (cmd)
        {
            case IOCTL_DSS_DCTRL_SET_PATH:
                retVal = Dss_dctrlDrvSetPathIoctl(
                    instObj,
                    (const Dss_DctrlPathInfo*) cmdArgs);
                break;
            case IOCTL_DSS_DCTRL_CLEAR_PATH:
                retVal = Dss_dctrlDrvClearPathIoctl(
                    instObj,
                    (const Dss_DctrlPathInfo*) cmdArgs);
                break;
            case IOCTL_DSS_DCTRL_SET_VP_PARAMS:
                retVal = Dss_dctrlDrvSetVpParamsIoctl(
                    instObj,
                    (const Dss_DctrlVpParams*) cmdArgs);
                break;
            case IOCTL_DSS_DCTRL_SET_OVERLAY_PARAMS:
                retVal = Dss_dctrlDrvSetOverlayParamsIoctl(
                    instObj,
                    (const Dss_DctrlOverlayParams*) cmdArgs);
                break;
            case IOCTL_DSS_DCTRL_SET_LAYER_PARAMS:
                retVal = Dss_dctrlDrvSetLayerParamsIoctl(
                    instObj,
                    (const Dss_DctrlOverlayLayerParams*) cmdArgs);
                break;
            case IOCTL_DSS_DCTRL_SET_VP_CSC_COEFF:
                retVal = Dss_dctrlDrvSetVpCscCoeffIoctl(
                    instObj,
                    (const Dss_DctrlVpCscCoeff*) cmdArgs);
                break;
            case IOCTL_DSS_DCTRL_SET_ADV_VP_PARAMS:
                retVal = Dss_dctrlDrvSetAdvVpParamsIoctl(
                    instObj,
                    (const Dss_DctrlAdvVpParams*) cmdArgs);
                break;
            case IOCTL_DSS_DCTRL_SET_LCD_BLANK_TIMING_PARAMS:
                retVal = Dss_dctrlDrvSetLcdBlankTimingIoctl(
                    instObj,
                    (const Dss_DctrlLcdBlankTimingParams*) cmdArgs);
                break;
            case IOCTL_DSS_DCTRL_SET_VP_SAFETY_CHK_PARAMS:
                retVal = Dss_dctrlDrvSetVpSafetyChkParamsIoctl(
                    instObj,
                    (const Dss_DctrlVpSafetyChkParams*) cmdArgs);
                break;
            case IOCTL_DSS_DCTRL_GET_VP_ERROR_STATS:
                retVal = Dss_dctrlDrvGetErrorStatsIoctl(
                    instObj,
                    (Dss_DctrlVpErrorStats*) cmdArgs);
                break;
            case IOCTL_DSS_DCTRL_SET_GLOBAL_DSS_PARAMS:
                retVal = Dss_dctrlDrvSetGlobalDssParamsIoctl(
                    instObj,
                    (const Dss_DctrlGlobalDssParams*) cmdArgs);
                break;
            case IOCTL_DSS_DCTRL_STOP_VP:
                retVal = Dss_dctrlDrvStopVpIoctl(
                    instObj,
                    (const Dss_DctrlVpParams*) cmdArgs);
                break;
            case IOCTL_DSS_DCTRL_REGISTER_SYNCLOST_CB:
                retVal = Dss_dctrlDrvSetSyncLostCbParamsIoctl(
                    instObj,
                    (const Dss_DctrlSyncLostCbParams*) cmdArgs);
                break;
            case IOCTL_DSS_DCTRL_REGISTER_LINENUM_CB:
                retVal = Dss_dctrlDrvSetLineNumCbParamsIoctl(
                    instObj,
                    (const Dss_DctrlLineNumCbParams*) cmdArgs);
                break;
            case IOCTL_DSS_DCTRL_SET_OLDI_PARAMS:
                retVal = Dss_dctrlDrvSetOldiParamsIoctl(
                    instObj,
                    (const Dss_DctrlOldiParams*) cmdArgs);
                break;
            default:
                GT_0trace(DssTrace,
                          GT_ERR,
                          "UNSUPPORTED_CMD: IOCTL not supported\r\n");
                retVal = FVID2_EUNSUPPORTED_CMD;
                break;
        }
    }

    return (retVal);
}

static int32_t Dss_dctrlDrvSetPathIoctl(Dss_DctrlDrvInstObj *instObj,
                                        const Dss_DctrlPathInfo *pathInfo)
{
    int32_t retVal = FVID2_SOK;
    uint32_t i, j, k, moduleId, currPipeNum;
    Fvid2_GraphEdgeInfo *currEdge, *vpEdge, *outEdge;
    Dss_DctrlDrvPipeInfo *pPipeInfo;

    /* Check for NULL pointers */
    GT_assert(DssTrace, (NULL != instObj));
    GT_assert(DssTrace, (NULL != pathInfo));

    /* Take the instance semaphore */
    (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    gDss_DctrlDrvInfo.numValidPipes = 0;

    if(0U != pathInfo->numEdges)
    {
        retVal = Dss_dctrlDrvCreateEdgeList(&gDss_DctrlDrvGraphObj,
                                   pathInfo);
    }

    if((FVID2_SOK == retVal) && (0U != pathInfo->numEdges))
    {
        for(i=0U; i<gDss_DctrlDrvGraphObj.dctrlEdgeList.numEdges; i++)
        {
            currEdge = &gDss_DctrlDrvGraphObj.dctrlEdgeList.list[i];

            if(TRUE == Dss_dctrlIsPipeNode(currEdge->startNode))
            {
                /* Start graph construction from pipe */
                currPipeNum = gDss_DctrlDrvInfo.numValidPipes;
                pPipeInfo = &gDss_DctrlDrvInfo.pipeInfo[currPipeNum];
                GT_assert(DssTrace, (currPipeNum <= CSL_DSS_VID_PIPE_ID_MAX));
                pPipeInfo->pipeNodeId = currEdge->startNode;
                /* Get Pipe Id */
                retVal = Dss_convNodetoModule(currEdge->startNode, &moduleId);
                GT_assert(DssTrace,
                          ((CSL_DSS_MODULE_INVALID != moduleId) ||
                           (FVID2_SOK == retVal)));
                pPipeInfo->pipeId = moduleId;
                pPipeInfo->pipeState = DSS_DCTRL_PIPE_IDLE;
                /* Assign overlay node & overlay id */
                pPipeInfo->overlayNodeId = currEdge->endNode;
                retVal = Dss_convNodetoModule(currEdge->endNode, &moduleId);
                GT_assert(DssTrace,
                          ((CSL_DSS_MODULE_INVALID != moduleId) ||
                           (FVID2_SOK == retVal)));
                pPipeInfo->overlayId = moduleId;
                retVal = Dss_dctrlConnectNodes(pPipeInfo->pipeNodeId,
                                               pPipeInfo->overlayNodeId);
                GT_assert(DssTrace, (FVID2_SOK == retVal));

                /* Find video port connected to overlay */
                for(j=0U; j<gDss_DctrlDrvGraphObj.dctrlEdgeList.numEdges; j++)
                {
                    vpEdge = &gDss_DctrlDrvGraphObj.dctrlEdgeList.list[j];
                    if(vpEdge->startNode == currEdge->endNode)
                    {
                        /* Assign video port node and video port id */
                        pPipeInfo->vpNodeId = vpEdge->endNode;
                        retVal = Dss_convNodetoModule(vpEdge->endNode,
                                                      &moduleId);
                        GT_assert(DssTrace,
                                  ((CSL_DSS_MODULE_INVALID != moduleId) ||
                                   (FVID2_SOK == retVal)));
                        pPipeInfo->vpId = moduleId;
                        retVal = Dss_dctrlConnectNodes(pPipeInfo->overlayNodeId,
                                                       pPipeInfo->vpNodeId);
                        GT_assert(DssTrace, (FVID2_SOK == retVal));

                        /* Find output node connected to video port */
                        for(k=0U; k<gDss_DctrlDrvGraphObj.dctrlEdgeList.numEdges; k++)
                        {
                            /* Assign output node */
                            outEdge = &gDss_DctrlDrvGraphObj.dctrlEdgeList.list[k];
                            if(outEdge->startNode == vpEdge->endNode)
                            {
                                pPipeInfo->outNodeId = outEdge->endNode;
                                retVal = Dss_dctrlConnectNodes(
                                                        pPipeInfo->vpNodeId,
                                                        pPipeInfo->outNodeId);
                                GT_assert(DssTrace, (FVID2_SOK == retVal));
                            }
                        }
                    }
                }
                gDss_DctrlDrvInfo.numValidPipes++;
            }
        }
    }

    if(FVID2_SOK != retVal)
    {
        GT_0trace(DssTrace, GT_ERR, "Set Path IOCTL failed\r\n");
    }

    /* Post the instance semaphore */
    (void) SemaphoreP_post(&instObj->lockSem);

    return retVal;
}

static int32_t Dss_dctrlDrvClearPathIoctl(Dss_DctrlDrvInstObj *instObj,
                                          const Dss_DctrlPathInfo *pathInfo)
{
    int32_t retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(DssTrace, (NULL != instObj));
    GT_assert(DssTrace, (NULL != pathInfo));

    /* Take the instance semaphore */
    (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    Dss_dctrlDrvFreeEdgeList(&gDss_DctrlDrvGraphObj);

    if(FVID2_SOK != retVal)
    {
        GT_0trace(DssTrace, GT_ERR, "Clear Path IOCTL failed\r\n");
    }

    /* Post the instance semaphore */
    (void) SemaphoreP_post(&instObj->lockSem);

    return retVal;
}

static int32_t Dss_dctrlDrvSetVpParamsIoctl(
                            Dss_DctrlDrvInstObj *instObj,
                            const Dss_DctrlVpParams *vpParams)
{
    int32_t retVal = FVID2_SOK;
    uint32_t i, vpId, syncVpId, vpFound = FALSE;
    CSL_dss_vpRegs *vpRegs;
    const Dss_SocInfo *socInfo;
    const CSL_DssVpLcdOpTimingCfg *lcdOpTimingCfg;
    const CSL_DssVpLcdSignalPolarityCfg *lcdPolarityCfg;
    const CSL_DssVpLcdTdmCfg *lcdTdmCfg;
    const Dss_DctrlSyncOpCfg *syncOpCfg;
    Dss_DctrlVpParams *pVpParams;
    Dss_DctrlDrvInfo *pDrvInfo;

    pDrvInfo = &gDss_DctrlDrvInfo;

    /* Check for NULL pointers */
    GT_assert(DssTrace, (NULL != instObj));
    GT_assert(DssTrace, (NULL != vpParams));

    /* Check for wrong inputs */
    if(vpParams->vpId >= CSL_DSS_VP_ID_MAX)
    {
        GT_0trace(DssTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    /* Take the instance semaphore */
    (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    if(FVID2_SOK == retVal)
    {
        /* Check if VP was already running */
        vpId = vpParams->vpId;
        for(i = 0U; i < CSL_DSS_VP_ID_MAX; i++)
        {
            if((gDss_DctrlDrvInfo.vpParams[i].vpId == vpId) &&
            (DSS_DCTRL_VP_IDLE != gDss_DctrlDrvInfo.vpState[vpId]))
            {
                retVal = FVID2_EDEVICE_INUSE;
                GT_0trace(DssTrace, GT_ERR, "VP is already in use!!\r\n");
                break;
            }
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Assign input parameters */
        lcdOpTimingCfg = &vpParams->lcdOpTimingCfg;
        lcdPolarityCfg = &vpParams->lcdPolarityCfg;
        lcdTdmCfg = &vpParams->lcdTdmCfg;
        syncOpCfg = &vpParams->syncOpCfg;
        pVpParams = &gDss_DctrlDrvInfo.vpParams[vpId];

        pVpParams->syncOpCfg.enabled = syncOpCfg->enabled;
        pVpParams->syncOpCfg.isPrimary = syncOpCfg->isPrimary;
        pVpParams->syncOpCfg.numSyncVpIds = syncOpCfg->numSyncVpIds;
        for(i = 0; i < syncOpCfg->numSyncVpIds; i++)
        {
            pVpParams->syncOpCfg.syncVpIds[i] = syncOpCfg->syncVpIds[i];
        }

        pVpParams->lcdOpTimingCfg.mInfo.scanFormat =
                                            lcdOpTimingCfg->mInfo.scanFormat;
        pVpParams->lcdOpTimingCfg.mInfo.standard =
                                            lcdOpTimingCfg->mInfo.standard;
        pVpParams->lcdOpTimingCfg.mInfo.height =
                                            lcdOpTimingCfg->mInfo.height;
        pVpParams->lcdOpTimingCfg.mInfo.width =
                                            lcdOpTimingCfg->mInfo.width;
        pVpParams->vpId = vpId;
    }

    if((FVID2_SOK == retVal) &&
    (TRUE == vpParams->syncOpCfg.enabled) &&
    (TRUE == vpParams->syncOpCfg.isPrimary))
    {
        syncOpCfg = &vpParams->syncOpCfg;

        for(i = 0; i < syncOpCfg->numSyncVpIds; i++)
        {
            syncVpId = syncOpCfg->syncVpIds[i];

            if(DSS_DCTRL_VP_STARTING != pDrvInfo->vpState[syncVpId])
            {
                vpFound = TRUE;
                break;
            }
        }
        if(TRUE == vpFound)
        {
            retVal = FVID2_EBADARGS;
            GT_0trace(DssTrace, GT_ERR, "Secondary sync VPs not started!!\r\n");
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Get video port registers */
        socInfo = Dss_getSocInfo();
        vpRegs = socInfo->vpRegs[vpId];
        GT_assert(DssTrace, (NULL != vpRegs));

        /* Not safe to push */
        gDss_DctrlDrvInfo.isPushSafe[vpId] = FALSE;

        /* Call CSL APIs */
        CSL_dssVpSetLcdSignalPolarityConfig(vpRegs, lcdPolarityCfg);
        CSL_dssVpSetLcdTdmConfig(vpRegs, lcdTdmCfg);
        retVal = CSL_dssVpSetLcdOpTimingConfig(vpRegs, lcdOpTimingCfg);

        if(FVID2_SOK != retVal)
        {
            GT_assert(DssTrace, FALSE);
        }

        if(lcdOpTimingCfg->mInfo.height > 5U)
        {
            CSL_dssVpSetLcdLineNum(vpRegs, lcdOpTimingCfg->mInfo.height - 5U);
        }

        Dss_dctrlVpEnable(vpId, TRUE);
    }

    if(FVID2_SOK != retVal)
    {
        GT_0trace(DssTrace, GT_ERR, "Set VP parameters IOCTL failed\r\n");
    }

    /* Post the instance semaphore */
    (void) SemaphoreP_post(&instObj->lockSem);

    return retVal;
}

static int32_t Dss_dctrlDrvSetOverlayParamsIoctl(
                            Dss_DctrlDrvInstObj *instObj,
                            const Dss_DctrlOverlayParams *overlayParams)
{
    int32_t retVal = FVID2_SOK;
    uint32_t vpId, overlayId = overlayParams->overlayId;
    CSL_dss_overlayRegs *overlayRegs;
    const Dss_SocInfo *socInfo;
    const CSL_DssOverlayCfg *overlayCfg;

    /* Check for NULL pointers */
    GT_assert(DssTrace, (NULL != instObj));
    GT_assert(DssTrace, (NULL != overlayParams));

    /* Check for wrong inputs */
    if(overlayId >= CSL_DSS_OVERLAY_ID_MAX)
    {
        GT_0trace(DssTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    /* Take the instance semaphore */
    (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    if(FVID2_SOK == retVal)
    {
        /* Get overlay registers */
        socInfo = Dss_getSocInfo();
        overlayRegs = socInfo->overlayRegs[overlayId];
        GT_assert(DssTrace, (NULL != overlayRegs));

        /* Get video port registers */
        vpId = Dss_getVpConnId(overlayId);
        GT_assert(DssTrace, (CSL_DSS_MODULE_INVALID != vpId));

        /* Assign input parameters */
        overlayCfg = &overlayParams->overlayCfg;

        /* Call CSL APIs */
        if(FALSE == overlayParams->colorbarEnable)
        {
            CSL_dssOverlayColorBarEnable(overlayRegs, FALSE);
            CSL_dssOverlaySetConfig(overlayRegs, overlayCfg);
        }
        else
        {
            CSL_dssOverlayColorBarEnable(overlayRegs, TRUE);
            Dss_dctrlVpSetGoBit(vpId);
        }
    }

    if(FVID2_SOK != retVal)
    {
        GT_0trace(DssTrace, GT_ERR, "Set overlay parameters IOCTL failed\r\n");
    }

    /* Post the instance semaphore */
    (void) SemaphoreP_post(&instObj->lockSem);

    return retVal;
}

static int32_t Dss_dctrlDrvSetLayerParamsIoctl(
                            Dss_DctrlDrvInstObj *instObj,
                            const Dss_DctrlOverlayLayerParams *layerParams)
{
    int32_t retVal = FVID2_SOK;
    uint32_t i, overlayId = layerParams->overlayId;
    CSL_dss_overlayRegs *overlayRegs;
    const Dss_SocInfo *socInfo;
    CSL_DssOverlayLayerCfg layerCfg;

    /* Check for NULL pointers */
    GT_assert(DssTrace, (NULL != instObj));
    GT_assert(DssTrace, (NULL != layerParams));

    /* Check for wrong inputs */
    if(overlayId >= CSL_DSS_OVERLAY_ID_MAX)
    {
        GT_0trace(DssTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    /* Take the instance semaphore */
    (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    if(FVID2_SOK == retVal)
    {
        /* Initialize layer configuration */
        CSL_dssOverlayLayerCfgInit(&layerCfg);

        /* Get overlay registers */
        socInfo = Dss_getSocInfo();
        overlayRegs = socInfo->overlayRegs[overlayId];
        GT_assert(DssTrace, (NULL != overlayRegs));

        /* Call CSL APIs */
        for(i=0U; i<CSL_DSS_VID_PIPE_ID_MAX; i++)
        {
            if(CSL_DSS_OVERLAY_LAYER_INVALID != layerParams->pipeLayerNum[i])
            {
                layerCfg.layerEnable = TRUE;
                layerCfg.layerNum = i;
                layerCfg.inputPipe = layerParams->pipeLayerNum[i];
                CSL_dssOverlaySetLayerConfig(
                                    overlayRegs,
                                    (const CSL_DssOverlayLayerCfg *) &layerCfg);
            }
        }
    }

    if(FVID2_SOK != retVal)
    {
        GT_0trace(DssTrace, GT_ERR, "Set layer parameters IOCTL failed\r\n");
    }

    /* Post the instance semaphore */
    (void) SemaphoreP_post(&instObj->lockSem);

    return retVal;
}

static int32_t Dss_dctrlDrvSetVpCscCoeffIoctl(
                            Dss_DctrlDrvInstObj *instObj,
                            const Dss_DctrlVpCscCoeff *vpCscCoeff)
{
    int32_t retVal = FVID2_SOK;
    uint32_t cscPos, vpId;
    CSL_dss_vpRegs *vpRegs;
    const Dss_SocInfo *socInfo;
    const CSL_DssCscCoeff *cscCoeff;

    /* Check for NULL pointers */
    GT_assert(DssTrace, (NULL != instObj));
    GT_assert(DssTrace, (NULL != vpCscCoeff));

    /* Take the instance semaphore */
    (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    /* Get video port registers */
    vpId = vpCscCoeff->vpId;
    socInfo = Dss_getSocInfo();
    vpRegs = socInfo->vpRegs[vpId];
    GT_assert(DssTrace, (NULL != vpRegs));

    /* Assign input parameters */
    cscPos = vpCscCoeff->cscPos;
    cscCoeff = &vpCscCoeff->cscCoeff;

    /* Call CSL API */
    if(FVID2_SOK == retVal)
    {
        CSL_dssVpSetCSCCoeff(vpRegs, cscCoeff, cscPos, TRUE);
    }

    if(FVID2_SOK != retVal)
    {
        GT_0trace(DssTrace, GT_ERR, "Set VP CSC coefficients IOCTL failed\r\n");
    }

    /* Post the instance semaphore */
    (void) SemaphoreP_post(&instObj->lockSem);

    return retVal;
}

static int32_t Dss_dctrlDrvSetAdvVpParamsIoctl(
                            Dss_DctrlDrvInstObj *instObj,
                            const Dss_DctrlAdvVpParams *advVpParams)
{
    int32_t retVal = FVID2_SOK;
    CSL_dss_vpRegs *vpRegs;
    const Dss_SocInfo *socInfo;
    const CSL_DssVpLcdAdvSignalCfg *lcdAdvSignalCfg;

    /* Check for NULL pointers */
    GT_assert(DssTrace, (NULL != instObj));
    GT_assert(DssTrace, (NULL != advVpParams));

    /* Check for wrong inputs */
    if(advVpParams->vpId >= CSL_DSS_VP_ID_MAX)
    {
        GT_0trace(DssTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    /* Take the instance semaphore */
    (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    if(FVID2_SOK == retVal)
    {
        /* Get video port registers */
        socInfo = Dss_getSocInfo();
        vpRegs = socInfo->vpRegs[advVpParams->vpId];
        GT_assert(DssTrace, (NULL != vpRegs));

        /* Assign input parameters */
        lcdAdvSignalCfg = &advVpParams->lcdAdvSignalCfg;

        /* Call CSL APIs */
        CSL_dssVpSetLcdAdvSignalConfig(vpRegs, lcdAdvSignalCfg);
    }

    if(FVID2_SOK != retVal)
    {
        GT_0trace(DssTrace,
                  GT_ERR,
                  "Set advance VP parameters IOCTL failed\r\n");
    }

    /* Post the instance semaphore */
    (void) SemaphoreP_post(&instObj->lockSem);

    return retVal;
}

static int32_t Dss_dctrlDrvSetLcdBlankTimingIoctl(
                            Dss_DctrlDrvInstObj *instObj,
                            const Dss_DctrlLcdBlankTimingParams *timingParams)
{
    int32_t retVal = FVID2_SOK;
    uint32_t vpId, scanFormat;
    CSL_dss_vpRegs *vpRegs;
    const Dss_SocInfo *socInfo;
    const CSL_DssVpLcdBlankTimingCfg *lcdBlankTimingCfg;

    /* Check for NULL pointers */
    GT_assert(DssTrace, (NULL != instObj));
    GT_assert(DssTrace, (NULL != timingParams));

    /* Check for wrong inputs */
    if(timingParams->vpId >= CSL_DSS_VP_ID_MAX)
    {
        GT_0trace(DssTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    /* Take the instance semaphore */
    (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    if(FVID2_SOK == retVal)
    {
        /* Assign input parameters */
        vpId = timingParams->vpId;
        lcdBlankTimingCfg = &timingParams->lcdBlankTimingCfg;

        /* Get scan format */
        scanFormat = gDss_DctrlDrvInfo.vpParams[vpId].lcdOpTimingCfg.mInfo.scanFormat;

        /* Get video port registers */
        socInfo = Dss_getSocInfo();
        vpRegs = socInfo->vpRegs[vpId];
        GT_assert(DssTrace, (NULL != vpRegs));

        /* Call CSL APIs */
        retVal = CSL_dssVpSetLcdBlankTiming(
                        vpRegs,
                        lcdBlankTimingCfg,
                        timingParams->dvoFormat,
                        scanFormat,
                        TRUE);
    }

    if(FVID2_SOK != retVal)
    {
        GT_0trace(DssTrace, GT_ERR, "Set LCD blank timing IOCTL failed\r\n");
    }

    /* Post the instance semaphore */
    (void) SemaphoreP_post(&instObj->lockSem);

    return retVal;
}

static int32_t Dss_dctrlDrvSetVpSafetyChkParamsIoctl(
                            Dss_DctrlDrvInstObj *instObj,
                            const Dss_DctrlVpSafetyChkParams *safetyChkParams)
{
    int32_t retVal = FVID2_SOK;
    uint32_t vpId, regionId, eventGroup, numHandle, evtMgrId, safetyEvt;
    Dss_DctrlDrvCommonObj *pObj;
    CSL_dss_vpRegs *vpRegs;
    const Dss_SocInfo *socInfo;
    const CSL_DssSafetyChkCfg *safetyChkCfg;

    /* Check for NULL pointers */
    GT_assert(DssTrace, (NULL != instObj));
    GT_assert(DssTrace, (NULL != safetyChkParams));

    /* Assign inputs */
    pObj = &gDss_DctrlDrvCommonObj;
    vpId = safetyChkParams->vpId;
    regionId = safetyChkParams->regionSafetyChkCfg.regionId;
    /* Check for wrong inputs */
    if((vpId >= CSL_DSS_VP_ID_MAX)||(regionId >= CSL_DSS_VP_SAFETY_REGION_MAX))
    {
        GT_0trace(DssTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        /* Get video port registers */
        socInfo = Dss_getSocInfo();
        vpRegs = socInfo->vpRegs[vpId];
        GT_assert(DssTrace, (NULL != vpRegs));
    }

    /* Take the instance semaphore */
    (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    if(FVID2_SOK == retVal)
    {
        Fvid2Utils_memcpy(
                    &gDss_DctrlDrvInfo.safetyChkParams[regionId][vpId],
                    safetyChkParams,
                    sizeof (Dss_DctrlVpSafetyChkParams));

        /* Register for Safety Error Events */
        Dss_convModuletoEventGroup(&eventGroup,
                                   vpId,
                                   DSS_EVENT_GROUP_TYPE_VP);
        GT_assert(DssTrace, (DSS_EVENT_GROUP_INVALID != eventGroup));
        numHandle = pObj->instObj->numRegEvtHandle;
        evtMgrId = Dss_getEvtMgrSafetyIntrId();
        safetyEvt = Dss_dctrlGetVpSafetyEvtId(regionId);
        GT_assert(DssTrace, (DSS_VP_EVENT_INVALID != safetyEvt));
        pObj->instObj->evtGroupHandle[pObj->instObj->numRegEvtHandle] =
                            Dss_evtMgrRegister(
                                evtMgrId,
                                eventGroup,
                                (const uint32_t *)(&safetyEvt),
                                1U,
                                Dss_dctrlSafetyErrCbFxn,
                                (void *)&gDss_DctrlEvtMgrClientInfo[numHandle]);
        pObj->instObj->numRegEvtHandle++;

        /* Call CSL APIs */
        if(0U != safetyChkParams->safetySignSeedVal)
        {
            CSL_dssVpSetSafetySignSeedVal(vpRegs,
                                          safetyChkParams->safetySignSeedVal);
        }
        if(CSL_DSS_SAFETY_CHK_DATA_INTEGRITY ==
                safetyChkParams->regionSafetyChkCfg.safetyChkCfg.safetyChkMode)
        {
            CSL_dssVpSetSafetyReferenceSign(
                            vpRegs,
                            safetyChkParams->regionSafetyChkCfg.referenceSign,
                            regionId);
        }
        safetyChkCfg = &safetyChkParams->regionSafetyChkCfg.safetyChkCfg;
        CSL_dssVpSetSafetyChkConfig(vpRegs, safetyChkCfg, regionId);
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

static int32_t Dss_dctrlDrvGetErrorStatsIoctl(
                            Dss_DctrlDrvInstObj *instObj,
                            Dss_DctrlVpErrorStats *vpErrStats)
{
    int32_t retVal = FVID2_SOK;
    uint32_t i, vpFound = FALSE;

    /* Check for NULL pointers */
    GT_assert(DssTrace, (NULL != instObj));
    GT_assert(DssTrace, (NULL != vpErrStats));

    /* Check for wrong inputs */
    if(vpErrStats->vpId >= CSL_DSS_VP_ID_MAX)
    {
        GT_0trace(DssTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    /* Take the instance semaphore */
    (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    if(FVID2_SOK == retVal)
    {
        /* Check if Video Port is valid */
        for(i=0U; i<CSL_DSS_VP_ID_MAX; i++)
        {
            if(gDss_DctrlDrvInfo.vpParams[i].vpId == vpErrStats->vpId)
            {
                vpFound = TRUE;
                break;
            }
        }

        if(TRUE == vpFound)
        {
            retVal = FVID2_SOK;
            vpErrStats->syncLost =
                    gDss_DctrlDrvInfo.errorCnt.vpsyncLost[vpErrStats->vpId];
            for(i=0U; i<CSL_DSS_VP_SAFETY_REGION_MAX; i++)
            {
                vpErrStats->safetyViolation[i] =
                    gDss_DctrlDrvInfo.errorCnt.vpSafetyViolation[i][vpErrStats->vpId];
            }

            vpErrStats->securityViolation =
                    gDss_DctrlDrvInfo.errorCnt.vpSecurityViolation[vpErrStats->vpId];
        }
    }

    if(FVID2_SOK != retVal)
    {
        GT_0trace(DssTrace, GT_ERR, "GET VP error stat IOCTL failed\r\n");
    }

    /* Post the instance semaphore */
    (void) SemaphoreP_post(&instObj->lockSem);

    return retVal;
}

static int32_t Dss_dctrlDrvSetGlobalDssParamsIoctl(
                            Dss_DctrlDrvInstObj *instObj,
                            const Dss_DctrlGlobalDssParams *globalDssParams)
{
    int32_t retVal = FVID2_SOK;
    CSL_dss_commRegs *commRegs;
    const Dss_SocInfo *socInfo;
    const CSL_DssGlobalMFlagCfg *globalMflagCfg;
    const CSL_DssCbaCfg *cbaCfg;

    /* Check for NULL pointers */
    GT_assert(DssTrace, (NULL != instObj));
    GT_assert(DssTrace, (NULL != globalDssParams));

    /* Take the instance semaphore */
    (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    /* Get common registers */
    socInfo = Dss_getSocInfo();
    commRegs = socInfo->commRegs[CSL_DSS_COMM_REG_ID_0];
    GT_assert(DssTrace, (NULL != commRegs));

    /* Assign input parameters */
    globalMflagCfg = &globalDssParams->globalMflagCfg;
    cbaCfg = &globalDssParams->cbaCfg;

    /* Call CSL APIs */
    if(FVID2_SOK == retVal)
    {
        CSL_dssSetGlobalMflagConfig(commRegs, globalMflagCfg);
        CSL_dssSetCbaConfig(commRegs, cbaCfg);
    }

    if(FVID2_SOK != retVal)
    {
        GT_0trace(DssTrace, GT_ERR, "Set global parameters IOCTL failed\r\n");
    }

    /* Post the instance semaphore */
    (void) SemaphoreP_post(&instObj->lockSem);

    return retVal;
}


static int32_t Dss_dctrlDrvSetOldiParamsIoctl(
                            Dss_DctrlDrvInstObj *instObj,
                            const Dss_DctrlOldiParams *oldiParams)
{
    int32_t retVal = FVID2_SOK;
    uint32_t resetOldi = FALSE;
    CSL_dss_commRegs *commRegs;
    CSL_dss_vpRegs *vpRegs;
    const Dss_SocInfo *socInfo;
    const CSL_DssVpOldiCfg *oldiCfg;

    /* Check for NULL pointers */
    GT_assert(DssTrace, (NULL != instObj));
    GT_assert(DssTrace, (NULL != oldiParams));

    /* Take the instance semaphore */
    (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    /* Get video port registers */
    socInfo = Dss_getSocInfo();
    vpRegs = socInfo->vpRegs[oldiParams->vpId];
    GT_assert(DssTrace, (NULL != vpRegs));

    /* Get common registers */
    commRegs = socInfo->commRegs[CSL_DSS_COMM_REG_ID_0];
    GT_assert(DssTrace, (NULL != commRegs));

    /* Assign input parameters */
    oldiCfg = &oldiParams->oldiCfg;

    CSL_dssVpSetOldiConfig(vpRegs, oldiCfg);
    CSL_dssVpOldiEnable(vpRegs, TRUE);

    /* Call CSL APIs */
    CSL_dssVpOldiReset(vpRegs);
    do
    {
        resetOldi = CSL_dssIsOldiResetDone(commRegs);
    } while (TRUE != resetOldi);

    if(FVID2_SOK != retVal)
    {
        GT_0trace(DssTrace, GT_ERR, "Set OLDI parameters IOCTL failed\r\n");
    }

    /* Post the instance semaphore */
    (void) SemaphoreP_post(&instObj->lockSem);

    return retVal;
}


static int32_t Dss_dctrlDrvStopVpIoctl(Dss_DctrlDrvInstObj *instObj,
                                       const Dss_DctrlVpParams *vpParams)
{
    int32_t retVal = FVID2_SOK;
    uint32_t i, vpId, syncVpId;
    uint32_t vpFound = FALSE;
    uint32_t cookie;
    Dss_DctrlVpParams *sVpParams = NULL;

    /* Check for NULL pointers */
    GT_assert(DssTrace, (NULL != instObj));
    GT_assert(DssTrace, (NULL != vpParams));
    GT_assert(DssTrace, (vpParams->vpId < CSL_DSS_VP_ID_MAX));

    vpId = vpParams->vpId;
    sVpParams = &gDss_DctrlDrvInfo.vpParams[vpId];

    /* Check for wrong inputs */
    if(vpParams->vpId >= CSL_DSS_VP_ID_MAX)
    {
        GT_0trace(DssTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    /* Take the instance semaphore */
    (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    if(FVID2_SOK == retVal)
    {
        if((DSS_DCTRL_VP_RUNNING != gDss_DctrlDrvInfo.vpState[vpId]) &&
        (DSS_DCTRL_VP_STARTING != gDss_DctrlDrvInfo.vpState[vpId]))
        {
            GT_0trace(DssTrace, GT_ERR, "VP not started!!\r\n");
            retVal = FVID2_EBADARGS;
        }
    }

    if((FVID2_SOK == retVal) &&
    (TRUE == sVpParams->syncOpCfg.enabled) &&
    (TRUE == sVpParams->syncOpCfg.isPrimary))
    {
        for(i = 0; i < sVpParams->syncOpCfg.numSyncVpIds; i++)
        {
            syncVpId = sVpParams->syncOpCfg.syncVpIds[i];

            if(DSS_DCTRL_VP_STOPPING != gDss_DctrlDrvInfo.vpState[syncVpId])
            {
                vpFound = TRUE;
            }
        }

        if(TRUE == vpFound)
        {
            GT_0trace(DssTrace, GT_ERR, "Secondary sync VPs not stopped!!\r\n");
            retVal = FVID2_EBADARGS;
        }
    }

    if(FVID2_SOK == retVal)
    {
        cookie = HwiP_disable();
        Dss_dctrlVpEnable(vpId, FALSE);
        HwiP_restore(cookie);

        Dss_dctrlVpReset(vpId);

        if((TRUE == sVpParams->syncOpCfg.enabled) &&
        (TRUE == sVpParams->syncOpCfg.isPrimary))
        {
            for(i = 0; i < sVpParams->syncOpCfg.numSyncVpIds; i++)
            {
                syncVpId = sVpParams->syncOpCfg.syncVpIds[i];
                Dss_dctrlVpReset(syncVpId);
            }
        }
    }

    if(FVID2_SOK != retVal)
    {
        GT_0trace(DssTrace, GT_ERR, "Stop VP IOCTL failed\r\n");
    }

    /* Post the instance semaphore */
    (void) SemaphoreP_post(&instObj->lockSem);

    return retVal;
}

static int32_t Dss_dctrlDrvSetSyncLostCbParamsIoctl(
                            Dss_DctrlDrvInstObj *instObj,
                            const Dss_DctrlSyncLostCbParams *syncLostCbParams)
{
    int32_t retVal = FVID2_SOK;
    uint32_t vpId;

    /* Check for NULL pointers */
    GT_assert(DssTrace, (NULL != instObj));
    GT_assert(DssTrace, (NULL != syncLostCbParams));

    /* Check for wrong inputs */
    if(syncLostCbParams->vpId >= CSL_DSS_VP_ID_MAX)
    {
        GT_0trace(DssTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    /* Take the instance semaphore */
    (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    if(FVID2_SOK == retVal)
    {
        vpId = syncLostCbParams->vpId;
        Fvid2Utils_memcpy(&gDss_DctrlDrvInfo.syncLostCbParams[vpId],
                          syncLostCbParams,
                          sizeof (Dss_DctrlSyncLostCbParams));
    }

    if(FVID2_SOK != retVal)
    {
        GT_0trace(DssTrace,
                  GT_ERR,
                  "Register Sync Lost Cb Params IOCTL failed\r\n");
    }

    /* Post the instance semaphore */
    (void) SemaphoreP_post(&instObj->lockSem);

    return retVal;
}

static int32_t Dss_dctrlDrvSetLineNumCbParamsIoctl(
                            Dss_DctrlDrvInstObj *instObj,
                            const Dss_DctrlLineNumCbParams *lineNumCbParams)
{
    int32_t retVal = FVID2_SOK;
    uint32_t vpId = lineNumCbParams->vpId;

    /* Check for NULL pointers */
    GT_assert(DssTrace, (NULL != instObj));
    GT_assert(DssTrace, (NULL != lineNumCbParams));

    /* Check for wrong inputs */
    if(vpId >= CSL_DSS_VP_ID_MAX)
    {
        GT_0trace(DssTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }

    /* Take the instance semaphore */
    (void) SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    if(FVID2_SOK == retVal)
    {
        Fvid2Utils_memcpy(&gDss_DctrlDrvInfo.lineNumCbParams[vpId],
                          lineNumCbParams,
                          sizeof (Dss_DctrlLineNumCbParams));
    }

    if(FVID2_SOK != retVal)
    {
        GT_0trace(DssTrace,
                  GT_ERR,
                  "Register Line Num Cb Params IOCTL failed\r\n");
    }

    /* Post the instance semaphore */
    (void) SemaphoreP_post(&instObj->lockSem);

    return retVal;
}

static void Dss_dctrlFuncCbFxn(const uint32_t *event,
                               uint32_t numEvents,
                               void *arg)
{
    uint32_t  i, j, currEvent, vpId = 0U, activePipeNum;
    Dss_EvtMgrClientInfo *pClientObj = (Dss_EvtMgrClientInfo *)arg;

    GT_assert(DssTrace,
              (gDss_DctrlDrvInfo.numValidPipes <= CSL_DSS_VID_PIPE_ID_MAX));

    uint32_t eventGroup = pClientObj->eventGroup;
    Dss_convEventGrouptoModule(eventGroup, &vpId);
    GT_assert(DssTrace, (CSL_DSS_MODULE_INVALID != vpId));

    for(i=0U; i<numEvents; i++)
    {
        currEvent = event[i];
        if(DSS_VP_EVENT_LINE_NUM == currEvent)
        {
            gDss_DctrlDrvInfo.isPushSafe[vpId] = FALSE;
            if(NULL != gDss_DctrlDrvInfo.lineNumCbParams[vpId].lineNumCbFxn)
            {
                gDss_DctrlDrvInfo.lineNumCbParams[vpId].lineNumCbFxn(
                            vpId,
                            gDss_DctrlDrvInfo.lineNumCbParams[vpId].appData);
            }
        }
        else if(DSS_VP_EVENT_VSYNC == currEvent)
        {
            /* Post crate sync semaphore */
            /* Post the instance semaphore */
            (void) SemaphoreP_post(&gDssStartSyncSem);
            activePipeNum = 0U;
            for(j=0U; j<gDss_DctrlDrvInfo.numValidPipes; j++)
            {
                if(gDss_DctrlDrvInfo.pipeInfo[j].vpId == vpId)
                {
                    if((gDss_DctrlDrvInfo.pipeInfo[j].pipeState ==
                                                DSS_DCTRL_PIPE_STARTING)     ||
                       (gDss_DctrlDrvInfo.pipeInfo[j].pipeState ==
                                                DSS_DCTRL_PIPE_STARTED)      ||
                       (gDss_DctrlDrvInfo.pipeInfo[j].pipeState ==
                                                DSS_DCTRL_PIPE_RUNNING)      ||
                       (gDss_DctrlDrvInfo.pipeInfo[j].pipeState ==
                                                DSS_DCTRL_PIPE_STOPPING))
                    {
                        activePipeNum++;
                        if(gDss_DctrlDrvInfo.pipeInfo[j].pipeState ==
                                                    DSS_DCTRL_PIPE_STARTING)
                        {
                            /* This is the first VSync for dummy start i.e.
                             * either start is synchronous or start was called
                             * close to VSYNC */
                            gDss_DctrlDrvInfo.pipeInfo[j].pipeState =
                                                        DSS_DCTRL_PIPE_STARTED;
                        }
                        if(gDss_DctrlDrvInfo.pipeInfo[j].pipeState ==
                                                    DSS_DCTRL_PIPE_STARTED)
                        {
                            /* This is the first actual VSync where the buffer
                             * B1's display has started */
                            gDss_DctrlDrvInfo.pipeInfo[j].pipeState =
                                                        DSS_DCTRL_PIPE_RUNNING;
                        }
                        if(gDss_DctrlDrvInfo.pipeInfo[j].pipeState ==
                                                    DSS_DCTRL_PIPE_STOPPING)
                        {
                            /* This is the VSYNC before synchronous stop */
                            gDss_DctrlDrvInfo.pipeInfo[j].pipeState =
                                                        DSS_DCTRL_PIPE_STOPPED;
                        }
                        gDss_DctrlDrvInfo.isPushSafe[vpId] = TRUE;
                        GT_assert(DssTrace,
                                  (NULL !=
                                   gDss_DctrlDrvInfo.pipeInfo[j].gClientInfo.cbFxn));
                        gDss_DctrlDrvInfo.pipeInfo[j].gClientInfo.cbFxn(
                            gDss_DctrlDrvInfo.pipeInfo[j].gClientInfo.arg);
                    }
                    else if(gDss_DctrlDrvInfo.pipeInfo[j].pipeState ==
                                                    DSS_DCTRL_PIPE_STOPPED)
                    {
                        /* This is the actual stop */
                        gDss_DctrlDrvInfo.pipeInfo[j].pipeState =
                                                        DSS_DCTRL_PIPE_OPENED;
                        (void) SemaphoreP_post(&gDss_DctrlDrvInfo.pipeInfo[j].stopSem);
                    }
                    else {
                        /* To fix MISRAC issue - this is a valid else - do nothing */
                    }
                }
            }

            if(activePipeNum > 0U)
            {
                Dss_dctrlVpSetGoBit(vpId);
            }
        }
        else
        {
            GT_assert(DssTrace, FALSE);
        }
    }

    return;
}

static void Dss_dctrlErrCbFxn(const uint32_t *event,
                              uint32_t numEvents,
                              void *arg)
{
    uint32_t  i, currEvent, vpId = 0U;
    Dss_EvtMgrClientInfo *pClientObj = (Dss_EvtMgrClientInfo *)arg;
    uint32_t eventGroup = pClientObj->eventGroup;
    Dss_DctrlDrvErrorCount *pErrorCnt;

    pErrorCnt = &gDss_DctrlDrvInfo.errorCnt;
    Dss_convEventGrouptoModule(eventGroup, &vpId);
    GT_assert(DssTrace, (CSL_DSS_MODULE_INVALID != vpId));

    for(i=0U; i<numEvents; i++)
    {
        currEvent = event[i];
        if(DSS_VP_EVENT_SYNC_LOST == currEvent)
        {
           pErrorCnt->vpsyncLost[vpId]++;
           if(NULL != gDss_DctrlDrvInfo.syncLostCbParams[vpId].syncLostCbFxn)
           {
               gDss_DctrlDrvInfo.syncLostCbParams[vpId].syncLostCbFxn(
                            vpId,
                            gDss_DctrlDrvInfo.syncLostCbParams[vpId].appData);
           }
        }
        else
        {
            GT_assert(DssTrace, FALSE);
        }
    }

    return;
}

static void Dss_dctrlSafetyErrCbFxn(const uint32_t *event,
                                    uint32_t numEvents,
                                    void *arg)
{
    uint32_t  i, currEvent, vpId = 0U, regionId;
    Dss_EvtMgrClientInfo *pClientObj = (Dss_EvtMgrClientInfo *)arg;
    uint32_t eventGroup = pClientObj->eventGroup;
    Dss_DctrlDrvErrorCount *pErrorCnt;
    Dss_DctrlVpSafetyChkParams *pSafetyChkParams;
    CSL_dss_vpRegs *vpRegs;
    const Dss_SocInfo *socInfo;

    pErrorCnt = &gDss_DctrlDrvInfo.errorCnt;
    Dss_convEventGrouptoModule(eventGroup, &vpId);
    GT_assert(DssTrace, (CSL_DSS_MODULE_INVALID != vpId));

    /* Get video port registers */
    socInfo = Dss_getSocInfo();
    vpRegs = socInfo->vpRegs[vpId];
    GT_assert(DssTrace, (NULL != vpRegs));

    for(i=0U; i<numEvents; i++)
    {
        currEvent = event[i];
        if(TRUE == Dss_dctrlIsSafetyEvent(currEvent))
        {
            regionId = Dss_dctrlGetVpSafetyRegionId(currEvent);
            GT_assert(DssTrace, (CSL_DSS_VP_SAFETY_REGION_INVALID != regionId));
            pErrorCnt->vpSafetyViolation[regionId][vpId]++;
            pSafetyChkParams = &gDss_DctrlDrvInfo.safetyChkParams[regionId][vpId];
            pSafetyChkParams->safetyCbData.regionId = regionId;
            pSafetyChkParams->safetyCbData.capturedSign =
                                    CSL_dssVpGetSafetySign(vpRegs, regionId);

            if(NULL != pSafetyChkParams->safetyErrCbFxn)
            {
                pSafetyChkParams->safetyErrCbFxn(vpId,
                                                 pSafetyChkParams->safetyCbData,
                                                 pSafetyChkParams->appData);
            }
        }
        else
        {
            GT_assert(DssTrace, FALSE);
        }
    }

    return;
}

static int32_t Dss_dctrlConnectNodes(uint32_t inputNode, uint32_t outNode)
{
    int32_t retVal = FVID2_SOK;

    if((FALSE == Dss_dctrlIsValidNode(inputNode)) ||
       (FALSE == Dss_dctrlIsValidNode(outNode)))
    {
        retVal = FVID2_EBADARGS;
    }

    if(TRUE == Dss_dctrlIsVideoMuxNeeded(inputNode, outNode))
    {
        retVal = Dss_dctrlProgramVideoMux(inputNode,
                                          outNode);
        GT_assert(DssTrace, (FVID2_SOK == retVal));
    }

    return (retVal);
}

static void Dss_dctrlVpSetGoBit(uint32_t vpId)
{
    CSL_dss_vpRegs *vpRegs;
    const Dss_SocInfo *socInfo;

    socInfo = Dss_getSocInfo();

    /* Get video port registers */
    vpRegs = socInfo->vpRegs[vpId];
    GT_assert(DssTrace, (NULL != vpRegs));

    CSL_dssVpSetGoBit(vpRegs);
}

static void Dss_dctrlVpReset(uint32_t vpId)
{
    CSL_dss_vpRegs *vpRegs;
    const Dss_SocInfo *socInfo;
    CSL_DssVpLcdSignalPolarityCfg lcdPolarityCfg;
    CSL_DssVpLcdOpTimingCfg lcdOpTimingCfg;
    CSL_DssVpLcdTdmCfg lcdTdmCfg;

    socInfo = Dss_getSocInfo();

    /* Get video port registers */
    vpRegs = socInfo->vpRegs[vpId];
    GT_assert(DssTrace, (NULL != vpRegs));

    CSL_dssVpLcdTdmCfgInit(&lcdTdmCfg);
    CSL_dssVpLcdSignalPolarityCfgInit(&lcdPolarityCfg);
    CSL_dssVpLcdOpTimingCfgInit(&lcdOpTimingCfg);

    CSL_dssVpSetLcdSignalPolarityConfig(
        vpRegs,
        (const CSL_DssVpLcdSignalPolarityCfg *)(&lcdPolarityCfg));
    CSL_dssVpSetLcdTdmConfig(
        vpRegs,
        (const CSL_DssVpLcdTdmCfg *)(&lcdTdmCfg));

    /* There is no point in checking the result here. We are resetting */
    (void) CSL_dssVpSetLcdOpTimingConfig(vpRegs, &lcdOpTimingCfg);
}

static void Dss_dctrlVpEnable(uint32_t vpId, uint32_t enable)
{
    CSL_dss_vpRegs *vpRegs;
    CSL_dss_commRegs *commRegs;
    const Dss_SocInfo *socInfo;
    const Dss_DctrlVpParams *vpParams;
    uint32_t syncVpId;
    uint32_t vpMask;
    uint32_t i;

    socInfo = Dss_getSocInfo();

    /* Get video port registers */
    vpRegs = socInfo->vpRegs[vpId];
    GT_assert(DssTrace, (NULL != vpRegs));

    /* Get DSS common_m / common_0 registers */
    /* XXX if common_0/m is not enabled in rmInfo? */
    commRegs = socInfo->commRegs[0U];
    GT_assert(DssTrace, (NULL != commRegs));

    vpParams = &gDss_DctrlDrvInfo.vpParams[vpId];

    if(TRUE == vpParams->syncOpCfg.enabled)
    {
        if(TRUE == vpParams->syncOpCfg.isPrimary)
        {
            vpMask = (uint32_t)(1U << vpId);
            for(i = 0U; i < vpParams->syncOpCfg.numSyncVpIds; i++)
            {
                syncVpId = vpParams->syncOpCfg.syncVpIds[i];
                vpMask |= (uint32_t)(1U << syncVpId);
            }

            CSL_dssGlobalVpEnable(commRegs, vpMask, enable);

            if(TRUE == enable)
            {
                gDss_DctrlDrvInfo.vpState[vpId] = DSS_DCTRL_VP_RUNNING;
            }
            else
            {
                gDss_DctrlDrvInfo.vpState[vpId] = DSS_DCTRL_VP_IDLE;
            }

            for(i = 0U; i < vpParams->syncOpCfg.numSyncVpIds; i++)
            {
                syncVpId = vpParams->syncOpCfg.syncVpIds[i];
                if(TRUE == enable)
                {
                    gDss_DctrlDrvInfo.vpState[syncVpId] = DSS_DCTRL_VP_RUNNING;
                }
                else
                {
                    gDss_DctrlDrvInfo.vpState[syncVpId] = DSS_DCTRL_VP_IDLE;
                }
            }
        }
        else
        {
            if(TRUE == enable)
            {
                gDss_DctrlDrvInfo.vpState[vpId] = DSS_DCTRL_VP_STARTING;
            }
            else
            {
                gDss_DctrlDrvInfo.vpState[vpId] = DSS_DCTRL_VP_STOPPING;
            }
        }
    }
    else
    {
        CSL_dssVpEnable(vpRegs, enable);
        if(TRUE == enable)
        {
            gDss_DctrlDrvInfo.vpState[vpId] = DSS_DCTRL_VP_RUNNING;
        }
        else
        {
            gDss_DctrlDrvInfo.vpState[vpId] = DSS_DCTRL_VP_IDLE;
        }
    }
}
