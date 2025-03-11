/*
 *  Copyright (c) Texas Instruments Incorporated 2020-25
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
 *  \file csitx_drvInit.c
 *
 *  \brief File containing the CSITX driver initialization code.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/csitx/v0/include/csitx_drvPriv.h>

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
 * \brief   Call-back for Info and status interrupts
 *
 * \param   pD              CSI TX CSL FL Driver Object
 * \param   val             Interrupt status.
 *
 * \retval  none.
 */
static void CsitxDrv_eventHandler(CSITX_PrivateData* pD,
                                  uint32_t irq_event,
                                  uint32_t dphy_event);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern CsitxDrv_CommonObj gCsitxCommonObj;

/* ========================================================================== */
/*                  Internal/Private Function Declarations                   */
/* ========================================================================== */

static int32_t CsitxDrv_coreInit(CsitxDrv_InstObj *instObj);
static int32_t CsitxDrv_chInit(CsitxDrv_InstObj *instObj);
int32_t CsitxDrv_init(CsitxDrv_CommonObj *txObj);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t Csitx_init(const Csitx_InitParams *initParams)
{
    int32_t retVal = FVID2_SOK;
    uint32_t instCnt, CsitxInstCnt = 0, loopCnt;
    CsitxDrv_CommonObj *txObj;
    CsitxDrv_InstObj *instObj;
    int32_t status = SystemP_SUCCESS;

    /* return error if 'initParams' is NULL */
    if (initParams == NULL)
    {
        retVal = FVID2_EBADARGS;
    }
    else
    {
        GT_assert(CsitxTrace, (retVal == FVID2_SOK));
        txObj = &gCsitxCommonObj;
        instObj = &gCsitxCommonObj.instObj[0U];
        /* Initialize Driver object */
        txObj->isRegistered = (uint32_t)FALSE;
        txObj->numInst = 0U;
        Fvid2Utils_memcpy(&txObj->initParams,
                          initParams,
                          sizeof (txObj->initParams));
        CsitxDrv_initPlatData(&txObj->platData);

        gCsitxCommonObj.getTimeStamp = NULL;
        for (instCnt = 0U; instCnt < CSITX_INSTANCE_ID_MAX; instCnt++)
        {
            /* Initialize D-PHY configuration parameters */
            instObj[instCnt].dphyCfg.inst                = instCnt;
            instObj[instCnt].drvInstId                   = instCnt;
            instObj[instCnt].inUse                       =
                                                CSITX_DRV_USAGE_STATUS_NOT_USED;
            instObj[instCnt].state                       = CSITX_DRV_STATE_IDLE;
            instObj[instCnt].numTxCh                     = 0U;
            instObj[instCnt].numColorbarCh               = 0U;
            instObj[instCnt].numLpbkCh                   = 0U;
            instObj[instCnt].bufManObj.curFrmNum         = 0U;
            /* initialize register base addresses */
            instObj[instCnt].shimBaseAddr                =
                                txObj->platData.instInfo[instCnt].shimAddr;
            instObj[instCnt].dPhyCoreAddr                =
                                txObj->platData.instInfo[instCnt].dPhyCoreAddr;

            Csitx_instStatusInit(&instObj[instCnt].status);
            for (loopCnt = 0U ; loopCnt < CSITX_NUM_CH; loopCnt++)
            {
                instObj[instCnt].chObj[loopCnt].psilThreadstatus =
                                                            (uint32_t)FALSE;
            }
            if (retVal == FVID2_SOK)
            {
                /* Allocate instance semaphore */
                status = SemaphoreP_constructBinary(&instObj[instCnt].lockSem ,1U);
                if (SystemP_SUCCESS != status)
                {
                    GT_0trace(
                        CsitxTrace, GT_ERR,
                        "Instance semaphore create failed!!\r\n");
                    retVal = FVID2_EALLOC;
                    break;
                }
            }
            CsitxInstCnt++;
        }

        /* Call Csitx init only if required */
        if ((CsitxInstCnt > 0U) && (retVal == FVID2_SOK))
        {
            gCsitxCommonObj.numInst = CsitxInstCnt;
            retVal +=  CsitxDrv_chInit(instObj);
            retVal +=  CsitxDrv_coreInit(instObj);
            retVal += CsitxDrv_init(txObj);
            /* de-initialize all the structures */
            if (retVal != FVID2_SOK)
            {
                /* Ignoring return value as it does not matter in case of
                   failure(in this case which already  failure case) */
                Csitx_deInit();
            }
        }
    }
    return retVal;
}

int32_t Csitx_deInit(void)
{
    int32_t retVal = FVID2_SOK;
    CsitxDrv_CommonObj *txObj;
    CsitxDrv_InstObj *instObj;
    uint32_t instIdx;

    txObj = &gCsitxCommonObj;
    /* un-initialize instance object variables */
    for (instIdx = 0U ; instIdx < CSITX_INSTANCE_ID_MAX ; instIdx++)
    {
        instObj = &txObj->instObj[instIdx];
        /* mark instance as un-used */
        instObj->inUse = CSITX_DRV_USAGE_STATUS_NOT_USED;
        /* putting to init state, this will prevent condition where
           user calls create() before calling init() after doing unint()*/
        instObj->state = CSITX_DRV_STATE_UNINIT;
        /* Delete semaphore */
        SemaphoreP_destruct(&instObj->lockSem);
    }
    /* un-initialize DRV object variables */
    /* unregister driver */
    retVal = Fvid2_unRegisterDriver(&txObj->fvidDrvOps);
    if (retVal != FVID2_SOK)
    {
        GT_0trace(
            CsitxTrace, GT_ERR,
            "Unregistering from FVID2 driver manager failed\r\n");
    }
    if (retVal == FVID2_SOK)
    {
       //if(txObj->masterEvent.drvHandle != NULL)
       {
           /* Register the UDMA Master event handle */
           if(Udma_eventUnRegister(&txObj->masterEvent) != UDMA_SOK)
           {
               retVal = FVID2_EFAIL;
           }
       }

    }

    txObj->isRegistered = (uint32_t)FALSE;

    return retVal;
}

void Csitx_initParamsInit(Csitx_InitParams *initPrms)
{
    initPrms->drvHandle = NULL;
}

void Csitx_createParamsInit(Csitx_CreateParams *createPrms)
{
    uint32_t loopCnt;

    if (NULL != createPrms)
    {
        createPrms->numCh = 0U;
        for (loopCnt = 0U ; loopCnt < CSITX_NUM_CH ; loopCnt++)
        {
            Csitx_chCfgInit(&createPrms->chCfg[loopCnt]);
        }
        Csitx_instCfgInit(&createPrms->instCfg);
    }
}

void Csitx_chCfgInit(Csitx_ChCfg *chCfgPrms)
{
    chCfgPrms->chId             = CSITX_CH_ID_DEFAULT;
    chCfgPrms->chType           = CSITX_CH_TYPE_TX;
    chCfgPrms->vcNum            = CSITX_VC_NUM_DEFAULT;
    chCfgPrms->hBlank           = CSITX_IN_FRAME_HB_DEFAULT;
    chCfgPrms->vBlank           = CSITX_IN_FRAME_VB_DEFAULT;
    chCfgPrms->startDelayPeriod = 0U;
    chCfgPrms->outCsiDataType   = CSITX_OUT_DT_DEFAULT;
    Fvid2Format_init(&chCfgPrms->inFmt);
    chCfgPrms->inFmt.width      = CSITX_IN_FRAME_WIDTH_DEFAULT;
    chCfgPrms->inFmt.height     = CSITX_IN_FRAME_HEIGHT_DEFAULT;
    Fvid2Utils_memset(&chCfgPrms->inFmt.pitch[0U],
                      0x0,
                      sizeof (chCfgPrms->inFmt.pitch));
    /* Initialization of UDMA channel params */
    UdmaChTxPrms_init(&chCfgPrms->txChParams, UDMA_CH_TYPE_TX_TR);
    /* Make CSI2RX DMA channels as highest priority,
       it is assumed that order 8-15 is mapped as RT at system level */
    chCfgPrms->txChParams.busPriority = 0U;
    chCfgPrms->txChParams.busQos      = 0U;
    chCfgPrms->txChParams.busOrderId  = 8U;
    chCfgPrms->txChParams.dmaPriority =
                                TISCI_MSG_VALUE_RM_UDMAP_CH_SCHED_PRIOR_HIGH;
}

void Csitx_instCfgInit(Csitx_InstCfg *modCfgPrms)
{
    uint32_t loopCnt;

    modCfgPrms->rxCompEnable         = 1U;
    modCfgPrms->rxv1p3MapEnable      = 1U;
    modCfgPrms->numDataLanes         = CSITX_TX_DATA_LANES_MAX;
    for(loopCnt = 0U ;
        loopCnt < (CSITX_TX_DATA_LANES_MAX + CSITX_TX_CLK_LANES_MAX) ;
        loopCnt++)
    {
        modCfgPrms->lanePolarityCtrl[loopCnt] = 0U;
    }
    /* Initialize DPHY configuration parameters */
    /* Default lane speed is configured to 800Mbps */
    Csitx_initDPhyCfgParams(&modCfgPrms->dphyCfg);
    /* Initialize event configuration parameters */
    modCfgPrms->eventGrpNum = 0U;
    for (loopCnt = 0U ; loopCnt < CSITX_EVENT_GROUP_MAX ; loopCnt++)
    {
        Csitx_eventPrmsInit(&modCfgPrms->eventParams[loopCnt]);
    }

}

void Csitx_instStatusInit(Csitx_InstStatus *captStatus)
{
    uint32_t loopCnt;

    captStatus->overflowCount = 0U;
    for(loopCnt = 0U ; loopCnt < CSITX_NUM_CH ; loopCnt++)
    {
        captStatus->queueCount[loopCnt]     = 0U;
        captStatus->dequeueCount[loopCnt]   = 0U;
        captStatus->frmRepeatCount[loopCnt] = 0U;
    }
}
/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static int32_t CsitxDrv_chInit(CsitxDrv_InstObj *instObj)
{
    int32_t retVal = FVID2_SOK;
    uint32_t instCnt, chNum;

    for (instCnt = 0U ; instCnt < CSITX_INSTANCE_ID_MAX ; instCnt++)
    {
        for (chNum = 0U ; chNum < CSITX_NUM_CH ; chNum++)
        {
            instObj[instCnt].chObj[chNum].instObj = &instObj[instCnt];
            instObj[instCnt].chObj[chNum].status =
                                        CSITX_DRV_CH_STATE_IDLE;
            /* Only capture channel will have 'psilThreadId' other than
               'CSITX_DRV_DEF_PSIL_THREAD_ID' */
            instObj[instCnt].chObj[chNum].psilThreadId =
                                        CSITX_DRV_DEF_PSIL_THREAD_ID;
        }
    }

    return retVal;
}

static int32_t CsitxDrv_coreInit(CsitxDrv_InstObj *instObj)
{
    int32_t retVal = FVID2_SOK;
    uint32_t instIdx, dtIdx;

    for (instIdx = 0U ; instIdx < CSITX_INSTANCE_ID_MAX ; instIdx++)
    {
        /* Initialize structure elements */
        Fvid2Utils_memset(&instObj[instIdx].cslObj.cslCfgData,
                          0U,
                          sizeof (CSITX_PrivateData));
        Fvid2Utils_memset(&instObj[instIdx].cslObj.deviceCfg,
                          0U,
                          sizeof (CSITX_DeviceConfig));
        Fvid2Utils_memset(&instObj[instIdx].cslObj.intrCbs,
                          0U,
                          sizeof (CSITX_Callbacks));
        Fvid2Utils_memset(&instObj[instIdx].cslObj.configParams,
                          0U,
                          sizeof (CSITX_Config));
        Fvid2Utils_memset(&instObj[instIdx].cslObj.sysreq,
                          0U,
                          sizeof (CSITX_SysReq));
        Fvid2Utils_memset(&instObj[instIdx].cslObj.dtCfg[0U],
                          0U,
                          sizeof (instObj[instIdx].cslObj.dtCfg));
        Fvid2Utils_memset(&instObj[instIdx].cslObj.strmcfg[0U],
                          0U,
                          sizeof (instObj[instIdx].cslObj.strmcfg));
        /* Initialize call-backs */
        instObj[instIdx].cslObj.configParams.regBase =
                (CSITX_Regs*)gCsitxCommonObj.platData.instInfo[instIdx].modAddr;
        instObj[instIdx].cslObj.intrCbs.event = CsitxDrv_eventHandler;
        instObj[instIdx].cslObj.dtInUse = 0U;
        /* Initialize some of the parameters of DT CFG */
        for (dtIdx = 0U ; dtIdx < CSITX_TX_DT_CFG_MAX ; dtIdx++)
        {
            instObj[instIdx].cslObj.dtCfg[dtIdx].extendedDataType   =
                                                CSITX_DRV_ENABLE_EXTENDED_DT;
            instObj[instIdx].cslObj.dtCfg[dtIdx].lineStartEndEnable =
                                                CSITX_DRV_ENABLE_LS_LE;
            instObj[instIdx].cslObj.dtCfg[dtIdx].lineCountEnable    = 0U;
        }
    }

    return retVal;
}

int32_t CsitxDrv_init(CsitxDrv_CommonObj *txObj)
{
    int32_t retVal = FVID2_SOK;

    /* Initialize Driver operations */
    Fvid2DrvOps_init(&txObj->fvidDrvOps);

    txObj->fvidDrvOps.drvId      = CSITX_TX_DRV_ID;
    txObj->fvidDrvOps.createFxn  = &CsitxDrv_create;
    txObj->fvidDrvOps.deleteFxn  = &CsitxDrv_delete;
    txObj->fvidDrvOps.controlFxn = &CsitxDrv_control;
    txObj->fvidDrvOps.queueFxn   = &CsitxDrv_queue;
    txObj->fvidDrvOps.dequeueFxn = &CsitxDrv_dequeue;

    retVal = Fvid2_registerDriver(&txObj->fvidDrvOps);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(
            CsitxTrace, GT_ERR,
            "Registering to FVID2 driver manager failed\r\n");
        /* Un-initialize the internal objects if error occurs: deInit() */
    }
    else
    {
        /* Init successful */
        txObj->isRegistered = (uint32_t) TRUE;
    }

    return (retVal);
}

static void CsitxDrv_eventHandler(CSITX_PrivateData* pD,
                                  uint32_t irq_event,
                                  uint32_t dphy_event)
{
    GT_0trace(CsitxTrace, GT_ERR, "Event CB!!\r\n");
}
