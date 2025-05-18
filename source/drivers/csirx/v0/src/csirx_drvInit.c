/*
 *  Copyright (c) Texas Instruments Incorporated 2018-2025
 *  All rights reserved.
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
 *  \file csirx_drvInit.c
 *
 *  \brief File containing the CSIRX driver initialization code.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <drivers/csirx/v0/include/csirx_drvPriv.h>
#include <drivers/csirx/v0/include/csirx_drvUdma.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */


/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   Call-back for Info and status interrupts
 *
 * \param   pD              CSI RX CSL FL Driver Object
 * \param   val             Interrupt status.
 */
static void CsirxDrv_infoHandler(CSIRX_PrivateData* pD,
                                 CSIRX_InfoIrqs* val);

/**
 * \brief   Call-back for Monitor interrupts
 *
 * \param   pD              CSI RX CSL FL Driver Object
 * \param   val             Interrupt status.
 */
static void CsirxDrv_monitorHandler(CSIRX_PrivateData* pD,
                                    CSIRX_MonitorIrqs* val);

/**
 * \brief   Call-back for Error interrupts
 *
 * \param   pD              CSI RX CSL FL Driver Object
 * \param   val             Interrupt status.
 */
static void CsirxDrv_errorHandler(CSIRX_PrivateData* pD, CSIRX_ErrorIrqs* val);

/**
 * \brief   Call-back for D-PHY interrupts
 *
 * \param   pD              CSI RX CSL FL Driver Object
 * \param   val             Interrupt status.
 */
static void CsirxDrv_dphyHandler(CSIRX_PrivateData* pD,
                                 CSIRX_DphyErrStatusIrq* val);

/**
 * \brief   Init function for module instance object
 *
 * \param   instObj         CSI module Driver Object
 * \param   instId          Instance Id.
 *
 * \retval  retVal          status.
 */
int32_t CsirxDrv_modInstObjInit(CsirxDrv_InstObj *instObj, uint32_t instId);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
extern CsirxDrv_CommonObj gCsirxCommonObj;

/* ========================================================================== */
/*                  Internal/Private Function Declarations                   */
/* ========================================================================== */
static int32_t CsirxDrv_initParamsCheck(const Csirx_InitParams *initParams);
static int32_t CsirxDrv_coreInit(CsirxDrv_InstObj *instObj);
static int32_t CsirxDrv_chInit(CsirxDrv_InstObj *instObj);
int32_t CsirxDrv_init(CsirxDrv_CommonObj *captObj);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t Csirx_init(const Csirx_InitParams *initParams)
{
    int32_t retVal = FVID2_SOK;
    uint32_t instCnt, CsirxInstCnt = 0, contextId;
    CsirxDrv_CommonObj *captObj;
    CsirxDrv_InstObj *instObj;
#if (CSIRX_DRV_ENABLE_DEBUG == 1U)
    uint32_t trIdx;
#endif

    /* return error if 'initParams' is NULL */
    if (initParams == NULL)
    {
        retVal = FVID2_EBADARGS;
    }
    else
    {
        GT_assert(CsirxTrace, (initParams != NULL));
        GT_assert(CsirxTrace, (retVal == FVID2_SOK));

        captObj = &gCsirxCommonObj;
        instObj = &gCsirxCommonObj.instObj[0U];
        /* Initialize Driver object */
        captObj->isRegistered = (uint32_t)FALSE;
        captObj->numInst = 0U;
        Fvid2Utils_memcpy(&captObj->initParams,
                          initParams,
                          sizeof (captObj->initParams));
        CsirxDrv_initPlatData(&captObj->platData);

        gCsirxCommonObj.getTimeStamp = NULL;

        for (instCnt = 0U; instCnt < CSIRX_INSTANCE_ID_MAX; instCnt++)
        {
            for (contextId = 0U ;
                 contextId < CSIRX_NUM_VIRTUAL_CONTEXT ;
                 contextId++)
            {
                captObj->virtContext[instCnt][contextId].contextId = contextId;
                captObj->virtContext[instCnt][contextId].numCh     = 0U;
                captObj->virtContext[instCnt][contextId].state     =
                                                        CSIRX_DRV_STATE_IDLE;
                Fvid2Utils_memset(
                        &captObj->virtContext[instCnt][contextId].chId[0U],
                        0U,
                        sizeof (captObj->virtContext[instCnt][contextId].chId));
                captObj->virtContext[instCnt][contextId].instObj   =
                                            &instObj[instCnt];
                captObj->virtContext[instCnt][contextId].inUse     =
                                            CSIRX_DRV_USAGE_STATUS_NOT_USED;
                captObj->numVirtContUsed[instCnt]                  = 0U;
            }

            retVal = CsirxDrv_modInstObjInit(&instObj[instCnt], instCnt);
            if (retVal != FVID2_SOK)
            {
                break;
            }
            CsirxInstCnt++;
        }

        /* Csirxl Csirx init only if required */
        if ((CsirxInstCnt > 0U) && (retVal == FVID2_SOK))
        {
            gCsirxCommonObj.numInst = CsirxInstCnt;
            retVal +=  CsirxDrv_chInit(instObj);
            retVal +=  CsirxDrv_coreInit(instObj);
            retVal += CsirxDrv_init(captObj);
            /* de-initialize all the structures */
            if (retVal != FVID2_SOK)
            {
                /* Ignoring return value as it does not matter in case of
                   failure(in this case which already  failure case) */
                (void)Csirx_deInit();
            }
        }
    }
    return retVal;
}

int32_t Csirx_deInit(void)
{
    int32_t retVal = FVID2_SOK, tempRetVal = FVID2_SOK;
    CsirxDrv_CommonObj *captObj;
    CsirxDrv_InstObj *instObj;
    uint32_t instIdx, contextId;

    captObj = &gCsirxCommonObj;

    /* un-initialize instance object variables */
    for (instIdx = 0U ; instIdx < CSIRX_INSTANCE_ID_MAX ; instIdx++)
    {
        instObj = &captObj->instObj[instIdx];
        /* mark instance as un-used */
        instObj->inUse = CSIRX_DRV_USAGE_STATUS_NOT_USED;
        /* putting to init state, this will prevent condition where
           user calls create() before calling init() after doing unint()*/
        for (contextId = 0U ;
             contextId < CSIRX_NUM_VIRTUAL_CONTEXT ;
             contextId++)
        {
            captObj->virtContext[instIdx][contextId].state =
                                                    CSIRX_DRV_STATE_UNINIT;
            captObj->virtContext[instIdx][contextId].numCh     = 0U;
            captObj->virtContext[instIdx][contextId].inUse     =
                                        CSIRX_DRV_USAGE_STATUS_NOT_USED;
        }
        /* Delete semaphore */
        (void)SemaphoreP_destruct(&instObj->lockSem);
    }

    /* un-initialize DRV object variables */
    /* unregister driver */
    retVal = Fvid2_unRegisterDriver(&captObj->fvidDrvOps);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(
            CsirxTrace, GT_ERR,
            "Unregistering from FVID2 driver manager failed\r\n");
    }
    if (retVal == FVID2_SOK)
    {
        //if(captObj->masterEvent.drvHandle != NULL)
        {
             /* Unregister the UDMA Master event handle */
             tempRetVal = Udma_eventUnRegister(&captObj->masterEvent);
             retVal = CsirxDrv_udmaToFvid2ErrorMap(tempRetVal);
        }
    }

    captObj->isRegistered = (uint32_t)FALSE;

    return retVal;
}

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */
static int32_t CsirxDrv_initParamsCheck(const Csirx_InitParams *initParams)
{
    int32_t retVal = FVID2_SOK;

    if (initParams->drvHandle == NULL)
    {
        retVal = FVID2_EBADARGS;
        GT_0trace(CsirxTrace,
                  GT_ERR,
                  "Invalid UDMA DRV Handle!!\r\n");
    }

    return retVal;
}
static int32_t CsirxDrv_chInit(CsirxDrv_InstObj *instObj)
{
    int32_t retVal = FVID2_SOK;
    uint32_t instCnt, chNum;

    for (instCnt = 0U ; instCnt < CSIRX_INSTANCE_ID_MAX ; instCnt++)
    {
        chNum = 0U;
        /* Keeping loops separate for Capture, OTF and Loopback channels as
           this can be helpful in future */
        for (; chNum < CSIRX_NUM_CH_CAPT ; chNum++)
        {
            /* For capture channels only */
            instObj[instCnt].chObj[chNum].instObj = &instObj[instCnt];
            instObj[instCnt].chObj[chNum].status = CSIRX_DRV_CH_STATE_IDLE;
            /* Only capture channel will have 'psilThreadId' other than
               'CSIRX_DRV_DEF_PSIL_THREAD_ID' */
            instObj[instCnt].chObj[chNum].psilThreadId = chNum;
        }
        for (; chNum < (CSIRX_NUM_CH_CAPT + CSIRX_NUM_CH_OTF_MAX) ; chNum++)
        {
            /* For OTF channels only */
            instObj[instCnt].chObj[chNum].instObj = &instObj[instCnt];
            instObj[instCnt].chObj[chNum].status = CSIRX_DRV_CH_STATE_IDLE;
            /* Only capture channel will have 'psilThreadId' other than
               'CSIRX_DRV_DEF_PSIL_THREAD_ID' */
            instObj[instCnt].chObj[chNum].psilThreadId =
                                                CSIRX_DRV_DEF_PSIL_THREAD_ID;
        }
        for (; chNum < CSIRX_NUM_CH_MAX ; chNum++)
        {
            /* For Loopback channels only */
            instObj[instCnt].chObj[chNum].instObj = &instObj[instCnt];
            instObj[instCnt].chObj[chNum].status = CSIRX_DRV_CH_STATE_IDLE;
            /* Only capture channel will have 'psilThreadId' other than
               'CSIRX_DRV_DEF_PSIL_THREAD_ID' */
            instObj[instCnt].chObj[chNum].psilThreadId =
                                                CSIRX_DRV_DEF_PSIL_THREAD_ID;
        }
    }

    return retVal;
}

static int32_t CsirxDrv_coreInit(CsirxDrv_InstObj *instObj)
{
    int32_t retVal = FVID2_SOK;
    uint32_t instCnt;

    for (instCnt = 0U ; instCnt < CSIRX_INSTANCE_ID_MAX ; instCnt++)
    {
        /* Initialize call-backs */
        instObj[instCnt].cslObj.intrHandlers.infoHandler =
                                                CsirxDrv_infoHandler;
        instObj[instCnt].cslObj.intrHandlers.monitorHandler =
                                                CsirxDrv_monitorHandler;
        instObj[instCnt].cslObj.intrHandlers.errorHandler =
                                                CsirxDrv_errorHandler;
        instObj[instCnt].cslObj.intrHandlers.dphyHandler =
                                                CsirxDrv_dphyHandler;
        /* Always outputs in 1 pixel per clock cycle */
        Fvid2Utils_memset(&instObj[instCnt].cslObj.strmCfgParams,
                          0U,
                          sizeof (CSIRX_StreamCfg));
        instObj[instCnt].cslObj.strmCfgParams.fifoMode = 1U;
        /* 'vcSelect' is not used when 'enableVcSelect' is set to 0U */
        /* 'datatypeSelectx is not use when 'enableDtx' is set to 0U */
        Fvid2Utils_memset(&instObj[instCnt].cslObj.strmDataCfgParams,
                          0U,
                          sizeof (CSIRX_StreamDataCfg));

        /* Disable info/status interrupts */
        /* Disable all stream interrupt and then enable them as per need */
        Fvid2Utils_memset(&instObj[instCnt].cslObj.infoIntrMask,
                          0U,
                          sizeof (CSIRX_InfoIrqsMaskCfg));

        /* Disable error interrupts */
        /* Disable all stream interrupt and then enable them as per need */
        Fvid2Utils_memset(&instObj[instCnt].cslObj.errIntrMask,
                          0U,
                          sizeof (CSIRX_ErrorIrqsMaskCfg));
    }

    return retVal;
}

int32_t CsirxDrv_init(CsirxDrv_CommonObj *captObj)
{
    int32_t retVal = FVID2_SOK;

    /* Initialize Driver operations */
    Fvid2DrvOps_init(&captObj->fvidDrvOps);

    captObj->fvidDrvOps.drvId      = CSIRX_CAPT_DRV_ID;
    captObj->fvidDrvOps.createFxn  = &CsirxDrv_create;
    captObj->fvidDrvOps.deleteFxn  = &CsirxDrv_delete;
    captObj->fvidDrvOps.controlFxn = &CsirxDrv_control;
    captObj->fvidDrvOps.queueFxn   = &CsirxDrv_queue;
    captObj->fvidDrvOps.dequeueFxn = &CsirxDrv_dequeue;

    retVal = Fvid2_registerDriver(&captObj->fvidDrvOps);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(
            CsirxTrace, GT_ERR,
            "Registering to FVID2 driver manager failed\r\n");
        /* Un-initialize the internal objects if error occurs: deInit() */
    }
    else
    {
        /* Init successful */
        captObj->isRegistered = (uint32_t) TRUE;
    }

    return (retVal);
}

static void CsirxDrv_infoHandler(CSIRX_PrivateData* pD, CSIRX_InfoIrqs* val)
{
    GT_0trace(CsirxTrace, GT_ERR, "In Info Handler!!\r\n");
}

static void CsirxDrv_monitorHandler(CSIRX_PrivateData* pD,
                                    CSIRX_MonitorIrqs* val)
{
    GT_0trace(CsirxTrace, GT_ERR, "In Monitor Handler!!\r\n");
}

static void CsirxDrv_errorHandler(CSIRX_PrivateData* pD, CSIRX_ErrorIrqs* val)
{
    GT_0trace(CsirxTrace, GT_ERR, "In Error interrupt Handler!!\r\n");
}

static void CsirxDrv_dphyHandler(CSIRX_PrivateData* pD,
                                 CSIRX_DphyErrStatusIrq* val)
{
    GT_0trace(CsirxTrace, GT_ERR, "In D-PHY interrupt Handler!!\r\n");
}

int32_t CsirxDrv_modInstObjInit(CsirxDrv_InstObj *instObj, uint32_t instId)
{
    int32_t retVal = FVID2_SOK;
    CsirxDrv_CommonObj *captObj;
    captObj = &gCsirxCommonObj;
    uint32_t loopCnt, eventId;
    int32_t status = SystemP_SUCCESS;

    instObj->dpyCfgDone                 = 0U;
    /* Initialize D-PHY configuration parameters */
    instObj->dphyCfg.inst               = instId;
    instObj->dphyCfg.psmClkFreqDiv      = 0U;
    instObj->dphyCfg.leftLaneBandSpeed  =
                                        CSIRX_LANE_BAND_SPEED_RESERVED;
    instObj->dphyCfg.rightLaneBandSpeed =
                                        CSIRX_LANE_BAND_SPEED_RESERVED;
    instObj->dphyCfg.bandGapTimerVal     = 0U;
    instObj->drvInstId            = instId;
    instObj->commonObjRef         = captObj;
    instObj->inUse                = CSIRX_DRV_USAGE_STATUS_NOT_USED;
    instObj->vp0Enable            = (uint32_t)FALSE;
    instObj->vp1Enable            = (uint32_t)FALSE;
    instObj->numCaptCh            = 0U;
    instObj->numOtfCh             = 0U;
    instObj->numLpbkCh            = 0U;
    instObj->numDrvInstCreated    = 0U;
    instObj->numDrvInstStarted    = 0U;
    /* initialize register base addresses */
    instObj->cslObj.configParams.regBase =
        (CSIRX_Regs*)
        captObj->platData.modAddr[instId];
    instObj->shimBaseAddr =
        captObj->platData.shimAddr[instId];
    instObj->dPhyWrapAddr =
        captObj->platData.dPhyWrapAddr[instId];
    instObj->dPhyCoreAddr =
        captObj->platData.dPhyCoreAddr[instId];
    instObj->psilThreadIdStart =
        captObj->platData.psilThreadIdStart[instId];

    Csirx_instStatusInit(&instObj->status);
    for (loopCnt = 0U ; loopCnt < CSIRX_NUM_CH ; loopCnt++)
    {
        instObj->chObj[loopCnt].chId             = loopCnt;
        instObj->chObj[loopCnt].virtContext      = NULL;
        instObj->chObj[loopCnt].psilThreadstatus =
                                                    (uint32_t)FALSE;
#if (CSIRX_DRV_ENABLE_DEBUG == 1U)
        /* Initialize TRPD addresses to '0' */
        for (trIdx = 0U ;
             trIdx < CSIRX_CAPT_QUEUE_DEPTH_PER_CH ;
             trIdx++)
        {

            instObj->chObj[loopCnt].listOfTRPDs[trIdx] =
                                                    (uint64_t)0U;
        }
#endif
    }

    /* Allocate instance semaphore */
    status = SemaphoreP_constructBinary(&instObj->lockSem,1U);
    if (status != SystemP_SUCCESS)
    {
        GT_0trace(
            CsirxTrace, GT_ERR,
            "Instance semaphore create failed!!\r\n");
        retVal = FVID2_EALLOC;
    }

    /* Initialize event object */
    for (eventId = 0U ; eventId < CSIRX_EVENT_GROUP_MAX ; eventId++)
    {
        instObj->eventObj[eventId].coreIntrNum   =
                                            CSIRX_INTR_INVALID;
        instObj->eventObj[eventId].eventInitDone = 0U;
        //instObj->eventObj[eventId].hwiHandle     = NULL;
    }

    return retVal;
}
