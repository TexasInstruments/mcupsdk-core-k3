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
 *  \file csirx_drv.c
 *
 *  \brief File containing the CSIRX driver functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <drivers/csirx.h>
#include <drivers/csirx/v0/include/csirx_drvPriv.h>
#include <drivers/csirx/v0/include/csirx_drvUdma.h>
#include <kernel/dpl/ClockP.h>
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/** \brief CSIRX capture driver ID used at the time of FVID2 create. */
#define CSIRX_STREAM_ID_INVALID              ((uint32_t)0xFFFFU)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
CsirxDrv_CommonObj gCsirxCommonObj;

/** \brief CSI protocol data type info */
dataTypeInfo gRxDtInfo[] =
{
    {FVID2_CSI2_DF_YUV420_8B, 8U, CSIRX_BITS_PER_PIXEL_16_BITS},
    {FVID2_CSI2_DF_YUV420_10B, 10U, CSIRX_BITS_PER_PIXEL_32_BITS},
    {FVID2_CSI2_DF_YUV420_8B_LEGACY, 12U, CSIRX_BITS_PER_PIXEL_12_BITS},
    {FVID2_CSI2_DF_YUV420_8B_CHROMA_SHIFT, 8U, CSIRX_BITS_PER_PIXEL_12_BITS},
    {FVID2_CSI2_DF_YUV420_10B_CHROMA_SHIFT, 10U, CSIRX_BITS_PER_PIXEL_12_BITS},
    {FVID2_CSI2_DF_YUV422_8B, 16U, CSIRX_BITS_PER_PIXEL_16_BITS},
    {FVID2_CSI2_DF_YUV422_10B, 20U, CSIRX_BITS_PER_PIXEL_64_BITS},
    {FVID2_CSI2_DF_RGB444, 12U, CSIRX_BITS_PER_PIXEL_16_BITS},
    {FVID2_CSI2_DF_RGB555, 15U, CSIRX_BITS_PER_PIXEL_16_BITS},
    {FVID2_CSI2_DF_RGB565, 16U, CSIRX_BITS_PER_PIXEL_16_BITS},
    {FVID2_CSI2_DF_RGB666, 18U, CSIRX_BITS_PER_PIXEL_32_BITS},
    {FVID2_CSI2_DF_RGB888, 24U, CSIRX_BITS_PER_PIXEL_32_BITS},
    {FVID2_CSI2_DF_RAW6, 6U, CSIRX_BITS_PER_PIXEL_8_BITS},
    {FVID2_CSI2_DF_RAW7, 7U, CSIRX_BITS_PER_PIXEL_8_BITS},
    {FVID2_CSI2_DF_RAW8, 8U, CSIRX_BITS_PER_PIXEL_8_BITS},
    {FVID2_CSI2_DF_RAW10, 10U, CSIRX_BITS_PER_PIXEL_16_BITS},
    {FVID2_CSI2_DF_RAW12, 12U, CSIRX_BITS_PER_PIXEL_16_BITS},
    {FVID2_CSI2_DF_RAW14, 14U, CSIRX_BITS_PER_PIXEL_16_BITS},
    {FVID2_CSI2_DF_RAW16, 16U, CSIRX_BITS_PER_PIXEL_16_BITS},
    {FVID2_CSI2_DF_RAW20, 20U, CSIRX_BITS_PER_PIXEL_32_BITS},
    /* TODO: Replace following with CSL macros in the file 'csl_fvid2_dataTypes.h'
             Hard-coding as corresponding patch might not be merged */
    {0x10, 8U, CSIRX_BITS_PER_PIXEL_8_BITS},
    {0x11, 8U, CSIRX_BITS_PER_PIXEL_8_BITS},
    {0x12, 8U, CSIRX_BITS_PER_PIXEL_8_BITS},
    {0x13, 8U, CSIRX_BITS_PER_PIXEL_8_BITS},
    {0x14, 8U, CSIRX_BITS_PER_PIXEL_8_BITS},
    {0x15, 8U, CSIRX_BITS_PER_PIXEL_8_BITS},
    {0x15, 8U, CSIRX_BITS_PER_PIXEL_8_BITS},
    {0x16, 8U, CSIRX_BITS_PER_PIXEL_8_BITS},
    {0x17, 8U, CSIRX_BITS_PER_PIXEL_8_BITS},
    {0x30, 8U, CSIRX_BITS_PER_PIXEL_8_BITS},
    {0x31, 8U, CSIRX_BITS_PER_PIXEL_8_BITS},
    {0x32, 8U, CSIRX_BITS_PER_PIXEL_8_BITS},
    {0x33, 8U, CSIRX_BITS_PER_PIXEL_8_BITS},
    {0x34, 8U, CSIRX_BITS_PER_PIXEL_8_BITS},
    {0x35, 8U, CSIRX_BITS_PER_PIXEL_8_BITS},
    {0x35, 8U, CSIRX_BITS_PER_PIXEL_8_BITS},
    {0x36, 8U, CSIRX_BITS_PER_PIXEL_8_BITS},
    {0x37, 8U, CSIRX_BITS_PER_PIXEL_8_BITS},
};

#if (CSIRX_DRV_ENABLE_DEBUG == 1U)
/* This array is filled like below
   gTrSubmit[x][0] = TRPD address
   gTrSubmit[x][1] = Inst ID
   gTrSubmit[x][2] = CH ID
   gTrSubmit[x][3] = Time stamp
 */
uint32_t gTrSubmit[CSIRX_DRV_TR_LOG_CNT][4] = {0U};
uint32_t gTrSubmitCnt = 0U;
/* This array is filled like below
   gTrOut[x][0] = TRPD address
   gTrOut[x][1] = Inst ID
   gTrOut[x][2] = CH ID
   gTrOut[x][3] = Time stamp
 */
uint32_t gTrOut[CSIRX_DRV_TR_LOG_CNT][4] = {0U};
uint32_t gTrOutCnt = 0U;
#endif
/* ========================================================================== */
/*                  Internal/Private Function Declarations                   */
/* ========================================================================== */
static int32_t CsirxDrv_setCslCfgParams(CsirxDrv_CommonObj *captObj,
                                        CsirxDrv_InstObj *instObj,
                                        Csirx_CreateParams *createParams);

static int32_t CsirxDrv_chConfigShim(CsirxDrv_ChObj *chObj);

static int32_t CsirxDrv_createChQueues(CsirxDrv_ChObj *chObj);

static void CsirxDrv_deleteChQueues(CsirxDrv_ChObj *chObj);

static int32_t CsirxDrv_startIoctl(CsirxDrv_VirtContext *virtContext);

static int32_t CsirxDrv_stopIoctl(CsirxDrv_VirtContext *virtContext);

static int32_t CsirxDrv_getStatusIoctl(const CsirxDrv_VirtContext *virtContext,
                                       Csirx_InstStatus *captStat);

static void CsirxDrv_deleteChObj(CsirxDrv_ChObj *chObj);

static uint32_t CsirxDrv_getStrmId(const Csirx_PlatformData *platformData,
                                   uint32_t instId,
                                   uint32_t strmType);

static void Csirx_printLogs(void);

static int32_t Csirx_setDphyCfg(CsirxDrv_VirtContext *virtContext,
                                const Csirx_DPhyCfg *dphyCfg);

static int32_t Csirx_dphyCfg(const Csirx_DPhyCfg *dphyCfg);

static int32_t CsirxDrv_setChCfgParams(CsirxDrv_ChObj *chObj, Csirx_ChCfg *chCfg);

static int32_t Csirx_startCh(CsirxDrv_ChObj *chObj);

static int32_t Csirx_stopCh(CsirxDrv_ChObj *chObj);

static int32_t CsirxDrv_getActiveChNumIoctl(CsirxDrv_InstObj *instObj,
                                            uint32_t *chNum);

static int32_t CsirxDrv_getFreeChNumIoctl(CsirxDrv_InstObj *instObj,
                                          uint32_t *chNum);

static int32_t CsirxDrv_startChannelIoctl(CsirxDrv_InstObj *instObj,
                                          uint32_t chNum);

static int32_t CsirxDrv_stopChannelIoctl(CsirxDrv_InstObj *instObj,
                                         uint32_t chNum);

static int32_t CsirxDrv_checkCreateParams(Csirx_CreateParams *programmed,
                                          Csirx_CreateParams *new);

/* This is create parameters validate function, add specific checks in this
   functions as this gets called before anything else.  */
static int32_t CsirxDrv_validateCreateParams(Csirx_CreateParams *params);

extern int32_t CsirxDrv_modInstObjInit(CsirxDrv_InstObj *instObj, uint32_t instId);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */
Fdrv_Handle CsirxDrv_create(uint32_t drvId,
                            uint32_t instId,
                            void *createArgs,
                            void *createStatusArgs,
                            const Fvid2_DrvCbParams *fdmCbParams)
{
    Fdrv_Handle drvHandle = NULL;
    int32_t retVal = FVID2_SOK;
    CsirxDrv_CommonObj *captObj;
    CsirxDrv_InstObj *instObj = NULL;
    Csirx_CreateParams *createParams;
    Csirx_CreateStatus *status;
    uint32_t chIdx, virtContextId, chId;
    CsirxDrv_VirtContext *virtContext;

    /* Check for NULL pointers and invalid arguments */
    if ((createArgs == NULL) ||
        (createStatusArgs == NULL) ||
        (fdmCbParams == NULL) ||
        (drvId != CSIRX_CAPT_DRV_ID))
    {
        GT_0trace(CsirxTrace, GT_ERR, "Invalid arguments\r\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        captObj = &gCsirxCommonObj;
        createParams = (Csirx_CreateParams *)createArgs;
        /* Get free virtual context */
        for (virtContextId = 0U ;
             virtContextId < CSIRX_NUM_VIRTUAL_CONTEXT ;
             virtContextId++)
        {
            if (captObj->virtContext[instId][virtContextId].inUse ==
                                        CSIRX_DRV_USAGE_STATUS_NOT_USED)
            {
                virtContext = &captObj->virtContext[instId][virtContextId];
                /* Get the instance object for this instance */
                instObj = virtContext->instObj;
                /* Copy createParams to instance object */
                Fvid2Utils_memcpy(&virtContext->createParams,
                          createParams,
                          sizeof (virtContext->createParams));
                Fvid2Utils_memcpy(&virtContext->fdmCbParams,
                          fdmCbParams,
                          sizeof (virtContext->fdmCbParams));
                break;
            }

        }
        if (virtContextId >= CSIRX_NUM_VIRTUAL_CONTEXT)
        {
            /* All the contexts are already in use */
            GT_0trace(CsirxTrace,
                      GT_ERR,
                      "Provided instance is already in use\r\n");
            retVal = FVID2_EDEVICE_INUSE;
        }
    }

    if (instObj != NULL)
    {
        /* Pend on the instance semaphore */
        (void)SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);
    }
    else
    {
        retVal = FVID2_EFAIL;
    }

    /* Validate Create time configuration parameters */
    if (retVal == FVID2_SOK)
    {
        retVal = CsirxDrv_validateCreateParams(createParams);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(CsirxTrace,
                      GT_ERR,
                      "Invalid createArgs provided\r\n");
        }
    }

    /* Configure modules common across multiple contexts, only do this first time
       for subsequent calls, ignore the configurations and check only for
       configurations integrity across contexts */
    if ((retVal == FVID2_SOK) && (instObj->inUse == CSIRX_DRV_USAGE_STATUS_NOT_USED))
    {
        /* Copy createParams to instance object */
        Fvid2Utils_memcpy(&instObj->createParams,
                          createParams,
                          sizeof (instObj->createParams));
        /* Initialize instance configuration parameters */
        instObj->drvInstId = instId;
        instObj->inUse     = CSIRX_DRV_USAGE_STATUS_IN_USE;
    }
    if ((retVal == FVID2_SOK) &&
        (instObj->inUse == CSIRX_DRV_USAGE_STATUS_IN_USE))
    {
        /* Integrity check: for createParams with actually programmed
           createParams on first call of Fvid2_create() for each
           CSI port/driver instance. This check is only done for common
           configuration across contexts like stream cfg. */
        retVal = CsirxDrv_checkCreateParams(&instObj->createParams,
                                            createParams);
    }

    /* Do channels configurations here, these has to be done per context */
    if ((retVal == FVID2_SOK) &&
        (instObj->inUse == CSIRX_DRV_USAGE_STATUS_IN_USE))
    {
         for (chIdx = 0U ; chIdx < createParams->numCh ; chIdx++)
         {
             if ((instObj->chObj[chIdx].chCfg->chType == CSIRX_CH_TYPE_CAPT) &&
                 (instObj->commonObjRef->initParams.drvHandle == NULL))
             {
                 retVal = FVID2_EBADARGS;
                 GT_0trace(CsirxTrace,
                           GT_ERR,
                           "Invalid UDMA DRV Handle!!\r\n");
                 break;

             }
         }
         for (chIdx = 0U ; chIdx < createParams->numCh ; chIdx++)
         {

             if (FVID2_SOK == CsirxDrv_getFreeChNumIoctl(instObj, &chId))
             {
                 /* Set SHIL/PSIL, UDMA configuration parameters */
                 retVal = CsirxDrv_setChCfgParams(&instObj->chObj[chId],
                                                  &createParams->chCfg[chIdx]);
                 if (retVal == FVID2_SOK)
                 {

                     /* Configure UDMA */
                     retVal = CsirxDrv_setChUdmaParams(
                                             &instObj->chObj[chId]);
                 }
                 if (retVal == FVID2_SOK)
                 {
                     /* Set CSIRX Module configuration parameters */
                     retVal = CsirxDrv_createChQueues(
                                             &instObj->chObj[chId]);
                 }
                 if (retVal == FVID2_SOK)
                 {
                     /* Set SHIM- CSIRX Module configuration parameters */
                     retVal = CsirxDrv_chConfigShim(&instObj->chObj[chId]);
                 }
                 if (retVal != FVID2_SOK)
                 {
                     break;
                 }
                 else
                 {
                     instObj->chObj[chId].virtContext = virtContext;
                     virtContext->chId[virtContext->numCh] = chId;
                     virtContext->numCh++;
                 }
             }
        }
    }
    if ((retVal == FVID2_SOK) &&
        (instObj->inUse == CSIRX_DRV_USAGE_STATUS_IN_USE))
    {

        /* Set CSIRX Module configuration parameters */
        retVal = CsirxDrv_setCslCfgParams(captObj,
                                          instObj,
                                          &instObj->createParams);
        if (retVal == FVID2_SOK)
        {
            /* de-assert pixel interface reset */
            CSL_csirxAssertPixelIfReset((CSL_csi_rx_ifRegs *)instObj->shimBaseAddr,
                                        (uint32_t)FALSE);
        }
    }
    if (createStatusArgs != NULL)
    {
        status = (Csirx_CreateStatus *)createStatusArgs;
        status->retVal = retVal;
    }
    if (retVal == FVID2_SOK)
    {
        drvHandle = virtContext;
        virtContext->state = CSIRX_DRV_STATE_CREATED;
        virtContext->inUse = CSIRX_DRV_USAGE_STATUS_IN_USE;
        captObj->numVirtContUsed[instId]++;
        instObj->numDrvInstCreated++;
    }
    else
    {
        if (instObj != NULL)
        {
            /* Deallocate if error occurs */
            for (chIdx = 0U ; chIdx < createParams->numCh ; chIdx++)
            {
                chId = virtContext->chId[chIdx];
                CsirxDrv_deleteChObj(&instObj->chObj[chId]);
            }
        }
        GT_0trace(CsirxTrace,
                  GT_ERR,
                  "Create failed for given configuration\r\n");
    }
    if (instObj != NULL)
    {
        /* Post the instance semaphore */
        (void)SemaphoreP_post(&instObj->lockSem);
    }

#if (CSIRX_DRV_ENABLE_DEBUG == 1U)
    /* Initialize Log Data */
    uint32_t loopCnt;

    if (retVal == FVID2_SOK)
    {
        gCsirxCommonObj.frmCnt         = 0U;
        gCsirxCommonObj.frmCntOverflow = 0U;
        gCsirxCommonObj.eventCnt       = 0U;
        for (loopCnt = 0U ; loopCnt < CSIRX_DRV_LOG_CNT ; loopCnt++)
        {
            gCsirxCommonObj.frmStatus[loopCnt]   = 0U;
            gCsirxCommonObj.frmType[loopCnt]     = 0U;
            gCsirxCommonObj.trResp[loopCnt]      = 0U;
            gCsirxCommonObj.frmTS[loopCnt]       = 0U;
            gCsirxCommonObj.frmChId[loopCnt]     = 0U;
            gCsirxCommonObj.frmInstId[loopCnt]   = 0U;
            gCsirxCommonObj.eventStatus[loopCnt] = 0U;
            gCsirxCommonObj.eventTS[loopCnt]     = 0U;
            gCsirxCommonObj.eventInstId[loopCnt] = 0U;
        }
    }
#endif
    return drvHandle;
}

int32_t CsirxDrv_delete(Fdrv_Handle handle, void *reserved)
{
    int32_t retVal = FVID2_SOK;
    uint32_t chIdx;
    CsirxDrv_InstObj *instObj = NULL;
    CsirxDrv_VirtContext *virtContext;
    CsirxDrv_CommonObj *captObj;

    captObj = &gCsirxCommonObj;
    /* Check for NULL pointers and invalid arguments */
    if (handle == NULL)
    {
        GT_0trace(CsirxTrace, GT_ERR, "Invalid arguments\r\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        virtContext = (CsirxDrv_VirtContext *) handle;
        instObj = virtContext->instObj;
    }

    if (instObj != NULL)
    {
        /* Pend on the instance semaphore */
        (void)SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

        /* Check if the instance is already opened and in a stopped state */
        if ((virtContext->state == CSIRX_DRV_STATE_STOPPED) ||
            (virtContext->state == CSIRX_DRV_STATE_CREATED))
        {
            /* TODO: Currently only done for Capture channels */
            for (chIdx = 0U ; chIdx < virtContext->numCh ; chIdx++)
            {
                if (instObj->chObj[virtContext->chId[chIdx]].status ==
                                            CSIRX_DRV_CH_STATE_STOPPED)
                {
                    CsirxDrv_deleteChObj(
                                &instObj->chObj[virtContext->chId[chIdx]]);
                    instObj->chObj[virtContext->chId[chIdx]].status =
                                                    CSIRX_DRV_CH_STATE_IDLE;
                }
            }

            /* Set configuration parameter to '0' */
            Fvid2Utils_memset(&virtContext->createParams,
                          0U,
                          sizeof (Csirx_CreateParams));
            Fvid2Utils_memset(&virtContext->fdmCbParams,
                          0U,
                          sizeof (Fvid2_DrvCbParams));

            /* Mark state as idle */
            virtContext->state = CSIRX_DRV_STATE_IDLE;
            /* Reset all channel numbers */
            instObj->numCaptCh = (instObj->numCaptCh - virtContext->numCh);
            virtContext->numCh = 0U;
            /* TODO: Should not be reset to '0' directly,
               it should be like above 'numCaptCh' */
            instObj->numOtfCh  = 0U;
            instObj->numLpbkCh = 0U;
            instObj->numDrvInstCreated--;

            virtContext->inUse = (uint32_t)CSIRX_DRV_USAGE_STATUS_NOT_USED;
            /* Mark as not in use for last open driver instance */
            if (captObj->numVirtContUsed[instObj->drvInstId] == 1U)
            {
                instObj->inUse = (uint32_t)CSIRX_DRV_USAGE_STATUS_NOT_USED;
            }
            captObj->numVirtContUsed[instObj->drvInstId]--;
        }
        else
        {
            GT_0trace(
                CsirxTrace, GT_ERR,
                "Driver not in a state to delete. Try stopping it!!\r\n");
            retVal = FVID2_EFAIL;
        }
        /* Post the instance semaphore */
        (void)SemaphoreP_post(&instObj->lockSem);
    }

    return retVal;
}

int32_t CsirxDrv_queue(Fdrv_Handle handle,
                       Fvid2_FrameList *frmList,
                       uint32_t streamId)
{
    int32_t retVal = FVID2_SOK, tempVal = UDMA_SOK;
    CsirxDrv_InstObj *instObj;
    CsirxDrv_ChObj *chObj;
    uint32_t frmCnt = 0U, chIdx, cookie;
    Fvid2_Frame *frm;
    CSL_UdmapTR1 *pTr;
    CsirxDrv_QueObj *qObj;
    CsirxDrv_VirtContext *virtContext;

    /* Check for NULL pointers */
    if((NULL == handle) || (NULL == frmList))
    {
        GT_0trace(CsirxTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }
    if(retVal == FVID2_SOK)
    {
        virtContext = (CsirxDrv_VirtContext *) handle;
        instObj = virtContext->instObj;
        retVal = Fvid2_checkFrameList(frmList, (uint32_t) FVID2_MAX_FRAME_PTR);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(CsirxTrace, GT_ERR, "Check frame list error\n");
        }
        if (virtContext->state == CSIRX_DRV_STATE_IDLE)
        {
            /* If driver handle is not open then skip this frame queue */
            GT_0trace(
                CsirxTrace, GT_ERR,
                "Invalid state: Can't queue to an un-opened instance!!\r\n");
            retVal = FVID2_EFAIL;
        }
    }
    if(retVal == FVID2_SOK)
    {
        /* Disable HW interrupts here */
        cookie = HwiP_disable();
        /* for all frames that need to be queued */
        for (frmCnt = 0U ; frmCnt < frmList->numFrames ; frmCnt++)
        {
            /* Get FVID2 frame pointer - NULL check is already done in
             * check frame list function */
            frm = frmList->frames[frmCnt];
            chIdx = virtContext->chId[frm->chNum];
            if (frm->chNum >= virtContext->numCh)
            {
                /* invalid stream ID skip this frame queue */
                GT_0trace(CsirxTrace, GT_ERR, "Invalid Channel ID\r\n");
                retVal = FVID2_EFAIL;
            }
            if(retVal == FVID2_SOK)
            {
                /*
                 * valid instance, stream and channel
                 */
                /* Get channel specific object in the required instance */
                chObj = &instObj->chObj[chIdx];
                /* Allocate a free queue object from the pool */
                qObj =
                 (CsirxDrv_QueObj *) Fvid2Utils_dequeue(chObj->bufManObj.freeQ);
                if (qObj == NULL)
                {
                    GT_0trace(
                        CsirxTrace, GT_ERR,
                        "ALLOC: Q object allocation failed\r\n");
                    retVal = FVID2_EALLOC;
                }
            }
            if(retVal == FVID2_SOK)
            {
                /* Copy the frame to the driver's queue object */
                qObj->frm = frm;
                /* Update TR packet descriptor for given Frame */
                pTr = UdmaUtils_getTrpdTr1Pointer((uint8_t *)qObj->trpd, 0U);

                pTr->addr = qObj->frm->addr[0U];
                /* Update dim1 as it may have been over-written by frame drop buffer */
                /* Submit TR to FQ ring for UDMA channel */
                pTr->dim1 = (int32_t)(chObj->chCfg->outFmt.pitch[0U]);
                /* Writeback cache */
                CsirxDrv_cacheWb(qObj->trpd,
                                 CSIRX_DRV_TRPD_SIZE_ALIGN);
                /* Submit TRPD to channel */
#if (CSIRX_DRV_ENABLE_DEBUG == 1U)
                {
                    gTrSubmit[gTrSubmitCnt][0U] = (uint32_t)qObj->trpd;
                    gTrSubmit[gTrSubmitCnt][1U] = instObj->drvInstId;
                    gTrSubmit[gTrSubmitCnt][2U] = chIdx;
                    if (gCsirxCommonObj.getTimeStamp != NULL)
                    {
                        gTrSubmit[gTrSubmitCnt][3U] =
                                        (uint32_t)gCsirxCommonObj.getTimeStamp(NULL);
                    }
                    else
                    {
                        gTrSubmit[gTrSubmitCnt][3U] = 0U;
                    }
                    gTrSubmitCnt = (gTrSubmitCnt + 1U) % CSIRX_DRV_TR_LOG_CNT;
                    CsirxDrv_cacheWb(&gTrSubmit[0U],
                                     sizeof(gTrSubmit));
                }
#endif
                tempVal = Udma_ringQueueRaw(
                                    Udma_chGetFqRingHandle(&chObj->rxChObj),
                                    (uint64_t)qObj->trpd);
                if(tempVal != UDMA_SOK)
                {
                    GT_0trace(
                        CsirxTrace, GT_ERR,
                        "Queue: Submitting of TR failed\r\n");
                    /* Queue back the Object which was
                       de-queued earlier from freeQ */
                    Fvid2Utils_queue(chObj->bufManObj.freeQ, &qObj->qElem, qObj);
                    retVal = CsirxDrv_udmaToFvid2ErrorMap(tempVal);
                }
                else
                {
                    /* Add the queue object in driver's current queue */
                    Fvid2Utils_queue(chObj->bufManObj.curQ, &qObj->qElem, qObj);
                    instObj->status.queueCount[chIdx]++;
                    /* Mark frame in frmList as NULL */
                    frmList->frames[frmCnt] = NULL;
                }
            }
        }
        /* Enable HW interrupts here */
        HwiP_restore(cookie);
    }

    return retVal;
}

int32_t CsirxDrv_dequeue(Fdrv_Handle handle,
                         Fvid2_FrameList *frmList,
                         uint32_t streamId,
                         uint32_t timeout)
{
    int32_t retVal = FVID2_SOK,tempRetVal = UDMA_SOK;
    CsirxDrv_InstObj *instObj;
    CsirxDrv_ChObj *chObj=NULL;
    uint32_t chIdx, cookie;
    volatile uint32_t loopBreakFlag = 1U;
    CsirxDrv_QueObj *qObj;
    uint64_t pDesc;
    CsirxDrv_VirtContext *virtContext;

    /* Check for NULL pointers */
    if((handle == NULL) ||
        (frmList == NULL))
    {
        GT_0trace(CsirxTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }
    if(retVal == FVID2_SOK)
    {
        virtContext = (CsirxDrv_VirtContext *) handle;
        instObj = virtContext->instObj;
        if (virtContext->state == CSIRX_DRV_STATE_IDLE)
        {
            GT_0trace(
                CsirxTrace, GT_ERR,
                "Invalid state: Can't dequeue to an un-opened instance!!\r\n");
            retVal = FVID2_EFAIL;
        }
    }
    /* Disable HW interrupts here */
    cookie = HwiP_disable();
    if(retVal == FVID2_SOK)
    {
        /* init frame list fields */
        frmList->numFrames  = 0U;
        frmList->perListCfg = NULL;
        for (chIdx = 0U ; chIdx < virtContext->numCh ; chIdx++)
        {
            chObj = &instObj->chObj[(virtContext->chId[chIdx])];
            loopBreakFlag = 1U;
            /* Extract done frames from queue till the queue
             * is empty or framelist runs out of space!! */
            do
            {
                qObj = (CsirxDrv_QueObj *) Fvid2Utils_dequeue(chObj->bufManObj.doneQ);
                if (qObj != NULL)
                {
                    if (qObj->type != CSIRX_DRV_Q_OBJ_TYPE_FD)
                    {
                        GT_assert(CsirxTrace, (qObj->chObj != NULL));
                        GT_assert(CsirxTrace, (qObj->frm != NULL));
                        frmList->frames[frmList->numFrames] = qObj->frm;
                        frmList->numFrames++;
                        instObj->status.dequeueCount[chObj->chId]++;

                    }
                    /* Give back the queue object back to the free pool */
                    qObj->frm = NULL;
                    if(chObj!=NULL)
                    {
                        Fvid2Utils_queue(chObj->bufManObj.freeQ, &qObj->qElem, qObj);
                    }
                }
                 /* Max frames limit exceeded exit */
                if ((frmList->numFrames >= FVID2_MAX_FRAME_PTR) ||
                    (qObj == NULL))
                {
                    loopBreakFlag = 0U;
                }
                /* TODO: Per Frame call back if needed */
            } while(loopBreakFlag == 1U);
        }
    }
    /* If no frame is dequeued, then check if we could return frames from input
     * and current queue for stopped instances */
    if (retVal == FVID2_SOK)
    {
        /* When an instance is stopped, return all the request in
         * channel's current queue as well. */
        GT_assert(CsirxTrace, (instObj != NULL));
        if (virtContext->state == CSIRX_DRV_STATE_STOPPED)
        {
            for (chIdx = 0U ; chIdx < virtContext->numCh ; chIdx++)
            {
                chObj = &instObj->chObj[(virtContext->chId[chIdx])];
                if (chObj->chCfg->chType == CSIRX_CH_TYPE_CAPT)
                {
                    /* Extract frames from queue till the queue
                     * is empty or frame list runs out of space!! */
                    for(;;)
                    {
                        /* At this point only TRPDs should only be available in
                           FQ Ring of UDMA since all UDMA channels are
                           stopped */
                        /* Flush any pending request from the free queue */
                        tempRetVal = Udma_ringFlushRaw(
                                        Udma_chGetFqRingHandle(&chObj->rxChObj),
                                        &pDesc);
                        if(UDMA_ETIMEOUT != tempRetVal)
                        {
                            /* Give the buffers in current state */
                            qObj = (CsirxDrv_QueObj *)
                                Fvid2Utils_dequeue(chObj->bufManObj.curQ);
                            GT_assert(CsirxTrace, (qObj != NULL));
                            if (qObj != NULL)
                            {
                                GT_assert(CsirxTrace,
                                  (chObj->chId == qObj->chObj->chId));
								                /* Check returned descriptor pointer */

								                GT_assert(CsirxTrace,
                                  (pDesc == (uint64_t)(qObj->trpd)));
                                if (qObj->type != CSIRX_DRV_Q_OBJ_TYPE_FD)
                                {
                                    GT_assert(CsirxTrace, (qObj->frm != NULL));
                                    qObj->frm->status = (uint32_t)FVID2_FRAME_STATUS_ABORTED;
                                    frmList->frames[frmList->numFrames] = qObj->frm;
                                    frmList->numFrames++;
                                    instObj->status.dequeueCount[chObj->chId]++;
                                }
                                /* Give back the queue object back to the free pool */
                                qObj->frm = NULL;
                                GT_assert(CsirxTrace, (chObj == qObj->chObj));
                                Fvid2Utils_queue(chObj->bufManObj.freeQ,
                                                &qObj->qElem,
                                                qObj);
                            }
                        }
                        /* Max frames limit exceeded exit or no more frames for this
                         * channel, continue with next channel */
                        if ((tempRetVal == UDMA_ETIMEOUT) || (frmList->numFrames >= FVID2_MAX_FRAME_PTR) ||
                            (qObj == NULL))
                        {
                            break;
                        }

                    }

                    /* Max frames limit exceeded exit */
                    if (frmList->numFrames >= FVID2_MAX_FRAME_PTR)
                    {
                        break;      /* for (chCnt) */
                    }
                    chObj->status = CSIRX_DRV_CH_STATE_STOPPED;
                }
            }
        }
    }
    /* Re-enable HW interrupts here */
    HwiP_restore(cookie);

    if (retVal == FVID2_SOK)
    {
        /* If no frame is dequeued, then return appropriate error */
        if (frmList->numFrames == 0U)
        {
            if ((virtContext->state == CSIRX_DRV_STATE_CREATED) ||
                (virtContext->state == CSIRX_DRV_STATE_STOPPED))
            {
                GT_0trace(
                    CsirxTrace, GT_DEBUG,
                    "NO_MORE_BUFFERS: No more buffers with driver\n");
                retVal = FVID2_ENO_MORE_BUFFERS;
            }
            else
            {
                GT_0trace(
                    CsirxTrace, GT_DEBUG,
                    "AGAIN: Out queue Empty. Try again\r\n");
                retVal = FVID2_EAGAIN;
            }
        }
        else
        {
            /* Increment dequeueCount for instance if any */
        }
    }

    return retVal;
}

int32_t CsirxDrv_control(Fdrv_Handle handle,
                         uint32_t cmd,
                         void *cmdArgs,
                         void *cmdStatusArgs)
{
    int32_t retVal = FVID2_SOK;
    CsirxDrv_InstObj *instObj;
    Fvid2_TimeStampParams *tsParams;
    CsirxDrv_VirtContext *virtContext;
    uint32_t chIdx;

    /* Check for NULL pointers */
    if (handle == NULL)
    {
        GT_0trace(CsirxTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        virtContext = (CsirxDrv_VirtContext *) handle;
        instObj = virtContext->instObj;
        switch (cmd)
        {
            case FVID2_START:
                retVal = CsirxDrv_startIoctl(virtContext);
            break;
            case FVID2_STOP:
                retVal = CsirxDrv_stopIoctl(virtContext);
            break;
            case IOCTL_CSIRX_GET_INST_STATUS:
                retVal = CsirxDrv_getStatusIoctl(
                                    virtContext,
                                    (Csirx_InstStatus *)cmdArgs);
            break;
            case IOCTL_CSIRX_PRINT_DEBUG_LOGS:
                retVal = FVID2_SOK;
                Csirx_printLogs();
            break;
            case FVID2_REGISTER_TIMESTAMP_FXN:
                tsParams = (Fvid2_TimeStampParams *)cmdArgs;
                gCsirxCommonObj.getTimeStamp = tsParams->timeStampFxn;
            break;
            case IOCTL_CSIRX_SET_DPHY_CONFIG:
                retVal = Csirx_setDphyCfg(virtContext,
                                          (Csirx_DPhyCfg *)cmdArgs);
            break;
            case IOCTL_CSIRX_REGISTER_EVENT:
                retVal = CsirxDrv_eventGroupRegister(handle,
                                                (Csirx_EventPrms *)cmdArgs);
            break;
            case IOCTL_CSIRX_UNREGISTER_EVENT:
                retVal = CsirxDrv_eventGroupUnRegister(handle,
                                                       (uint32_t)cmdArgs);
            break;
            case IOCTL_CSIRX_GET_INST_CH_NUM:
                retVal = CsirxDrv_getActiveChNumIoctl(instObj,
                                                      (uint32_t *)cmdArgs);
            break;
            case IOCTL_CSIRX_CH_START:
                if ((*((uint32_t *)cmdArgs)) >= virtContext->numCh)
                {
                    retVal = FVID2_EBADARGS;
                }
                else
                {
                    chIdx = virtContext->chId[*((uint32_t *)cmdArgs)];
                    retVal = CsirxDrv_startChannelIoctl(instObj, chIdx);
                }
            break;
            case IOCTL_CSIRX_CH_STOP:
                if ((*((uint32_t *)cmdArgs)) >= virtContext->numCh)
                {
                    retVal = FVID2_EBADARGS;
                }
                else
                {
                    chIdx = virtContext->chId[*((uint32_t *)cmdArgs)];
                    retVal = CsirxDrv_stopChannelIoctl(instObj, chIdx);
                }
            break;
            default:
            {
                GT_0trace(CsirxTrace, GT_ERR,
                            "UNSUPPORTED_CMD: IOCTL not supported\r\n");
                retVal = FVID2_EUNSUPPORTED_CMD;
            }
			break;
        }
    }

    return retVal;
}

static int32_t CsirxDrv_setCslCfgParams(CsirxDrv_CommonObj *captObj,
                                         CsirxDrv_InstObj *instObj,
                                        Csirx_CreateParams *createParams)
{
    int32_t retVal = FVID2_SOK;
    uint32_t status, loopCnt, strmId;
    CSIRX_ErrorBypassCfg errCfg;
    CSIRX_StreamCfg strmCfgParams;
    CSIRX_StreamDataCfg strmDataCfgParams;
    CSIRX_StreamCtrl strmCtrlParams;
    CSIRX_StreamStatus strmStatus;
    uint32_t currTimeout = 0U;

    /* Initialize CSI CSL FL object */
    status = CSIRX_Init(&instObj->cslObj.cslCfgData,
                        &instObj->cslObj.configParams,
                        &instObj->cslObj.intrHandlers);
    if (status != 0U)
    {
        GT_0trace(CsirxTrace,
                  GT_ERR,
                  "CSL FL: Invalid Config Arguments\r\n");
        retVal = FVID2_EBADARGS;
    }

    if (retVal == FVID2_SOK)
    {
        /* reset streams before configuration */
        for (loopCnt = 0U ; loopCnt < CSIRX_NUM_STREAM ; loopCnt++)
        {
            strmCtrlParams.softRst = 1U;
            strmCtrlParams.abrt = 0U;
            strmCtrlParams.stop = 0U;
            strmCtrlParams.start = 0U;
            status = CSIRX_SetStreamCtrl(&instObj->cslObj.cslCfgData,
                                         &strmCtrlParams,
                                         loopCnt);
            if (status != 0U)
            {
                GT_0trace(CsirxTrace,
                        GT_ERR,
                        "CSL FL: Stream reset failed\r\n");
                retVal = FVID2_EBADARGS;
            }
            currTimeout = 0U;
            status = CSIRX_GetStreamStatus(&instObj->cslObj.cslCfgData,
                                           &strmStatus,
                                           loopCnt);
            if (status != 0U)
            {
                GT_0trace(CsirxTrace,
                    GT_ERR,
                    "CSL FL: Stream Get Stream Status failed\r\n");
                retVal = FVID2_EBADARGS;
                break;
            }
            /* Wait for stream to become IDLE */
            while ((strmStatus.readyState != 0x0U) &&
                   (strmStatus.streamFsm  != 0x0U) &&
                   (retVal == FVID2_SOK))
            {
                 status = CSIRX_GetStreamStatus(&instObj->cslObj.cslCfgData,
                                           &strmStatus,
                                           loopCnt);
                if (status != 0U)
                {
                    GT_0trace(CsirxTrace,
                        GT_ERR,
                        "CSL FL: Stream Get Stream Status failed\r\n");
                    retVal = FVID2_EBADARGS;
                    break;
                }
                if(currTimeout > CSIRX_TIMEOUT_VAL_MS)
                {
                    retVal = FVID2_ETIMEOUT;
                    GT_0trace(CsirxTrace,
                        GT_ERR,
                        "CSL FL: Stream reset timed-out\r\n");
                }
                else
                {
                    (void)ClockP_sleep(1U);
                    currTimeout++;
                }
            }
        }
    }
    if (retVal == FVID2_SOK)
    {
      /* Get device status */
      (void)CSIRX_GetDeviceConfig(&instObj->cslObj.cslCfgData,
                        &instObj->cslObj.deviceCfg);
      instObj->cslObj.staticCfg.laneNb =
                          (uint8_t)createParams->instCfg.numDataLanes;
      /* Enable CSI v2p0 support */
      if (createParams->instCfg.enableCsiv2p0Support == (uint32_t)TRUE)
      {
          instObj->cslObj.staticCfg.enable2p0Support = (uint8_t)1U;
      }
      else
      {
          instObj->cslObj.staticCfg.enable2p0Support = (uint8_t)0U;
      }

      for (loopCnt = 0U ;
           loopCnt < CSIRX_CAPT_DATA_LANES_MAX ;
           loopCnt++)
      {
          /* D-PHY lane mapping to logical lanes */
          instObj->cslObj.staticCfg.dlMap[loopCnt] =
                          (uint8_t)createParams->instCfg.dataLanesMap[loopCnt];
      }
      /* Use internal D-Phy */
      instObj->cslObj.staticCfg.sel = 0U;
      /* Configure D-PHY lanes used */
      status = CSIRX_SetStaticCfg(
                      &instObj->cslObj.cslCfgData,
                      &instObj->cslObj.staticCfg);
      if (status != 0U)
      {
          GT_0trace(CsirxTrace,
                    GT_ERR,
                    "CSL FL: Invalid Static Config Arguments\r\n");
          retVal = FVID2_EBADARGS;
      }
    }
    if (retVal == FVID2_SOK)
    {
        /* Configure CSI RX Module interrupts */
        status = CSIRX_SetErrorIrqsMaskCfg(&instObj->cslObj.cslCfgData,
                                           &instObj->cslObj.errIntrMask);
        status += CSIRX_SetInfoIrqsMaskCfg(&instObj->cslObj.cslCfgData,
                                          &instObj->cslObj.infoIntrMask);
        if (status != 0U)
        {
            GT_0trace(CsirxTrace,
                        GT_ERR,
                        "CSL FL: Invalid Interrupt Config Arguments\r\n");
            retVal = FVID2_EBADARGS;
        }
    }
    if (retVal == FVID2_SOK)
    {
        if (instObj->createParams.instCfg.enableErrbypass == (uint32_t)TRUE)
        {
            errCfg.dataId = 1U;
            errCfg.ecc = 1U;
            errCfg.crc = 1U;
        }
        else
        {
            errCfg.dataId = 0U;
            errCfg.ecc = 0U;
            errCfg.crc = 0U;
        }
        status = CSIRX_SetErrorBypassCfg(&instObj->cslObj.cslCfgData, &errCfg);
        if (status != 0U)
        {
            GT_0trace(CsirxTrace,
                        GT_ERR,
                        "CSL FL: Invalid Error Bypass Config Arguments\r\n");
            retVal = FVID2_EBADARGS;
        }
    }
    if (retVal == FVID2_SOK)
    {
        if ((instObj->numCaptCh > 0U) ||
            (instObj->inUse == CSIRX_DRV_USAGE_STATUS_NOT_USED))
        {
            strmId = CsirxDrv_getStrmId(&captObj->platData,
                                        instObj->drvInstId,
                                        CSIRX_CH_TYPE_CAPT);
            /* assert if given stream is not supported on the module instance */
            GT_assert(CsirxTrace, (strmId != CSIRX_STREAM_ID_INVALID));
            /* Configure Capture Stream of CSI RX Module */
            /* Set configuration passed down by application */
            instObj->cslObj.strmCfgParams.numPixels =
                                        (uint8_t)createParams->instCfg.numPixelsStrm0;
            Fvid2Utils_memcpy(&strmCfgParams,
                          &instObj->cslObj.strmCfgParams,
                          sizeof (CSIRX_StreamCfg));
            Fvid2Utils_memcpy(&strmDataCfgParams,
                          &instObj->cslObj.strmDataCfgParams,
                          sizeof (CSIRX_StreamDataCfg));
            status = CSIRX_SetStreamCfg(&instObj->cslObj.cslCfgData,
                                        &instObj->cslObj.strmCfgParams,
                                        strmId);
            status += CSIRX_SetStreamDataCfg(&instObj->cslObj.cslCfgData,
                                            &strmDataCfgParams,
                                            strmId);
            if (status != 0U)
            {
                GT_0trace(CsirxTrace,
                        GT_ERR,
                        "CSL FL: Invalid Capture Stream Config Arguments\r\n");
                retVal = FVID2_EBADARGS;
            }
        }
        if (instObj->numOtfCh > 0U)
        {
            strmId = CsirxDrv_getStrmId(&captObj->platData,
                                        instObj->drvInstId,
                                        CSIRX_CH_TYPE_OTF);
            /* assert if given stream is not supported on the module instance */
            GT_assert(CsirxTrace, (strmId != CSIRX_STREAM_ID_INVALID));
            /* Configure OTF Stream of CSI RX Module */
            Fvid2Utils_memcpy(&strmCfgParams,
                          &instObj->cslObj.strmCfgParams,
                          sizeof (CSIRX_StreamCfg));
            Fvid2Utils_memcpy(&strmDataCfgParams,
                          &instObj->cslObj.strmDataCfgParams,
                          sizeof (CSIRX_StreamDataCfg));
            strmDataCfgParams.enableVcSelect = 1U;
            strmDataCfgParams.enableDt0 = 1U;
            for (loopCnt = 0U ; loopCnt < instObj->numOtfCh ; loopCnt++)
            {
                strmDataCfgParams.vcSelect =
                    (uint8_t)instObj->chObj[instObj->otfChId[loopCnt]].chCfg->vcNum;
                strmDataCfgParams.datatypeSelect0 =
                    (uint8_t)instObj->chObj[instObj->otfChId[loopCnt]].chCfg->inCsiDataType;
                status = CSIRX_SetStreamCfg(&instObj->cslObj.cslCfgData,
                                            &instObj->cslObj.strmCfgParams,
                                            strmId);
                status += CSIRX_SetStreamDataCfg(&instObj->cslObj.cslCfgData,
                                                &strmDataCfgParams,
                                                strmId);
                if (status != 0U)
                {
                    GT_0trace(CsirxTrace,
                            GT_ERR,
                            "CSL FL: Invalid OTF Stream Config Arguments\r\n");
                    retVal = FVID2_EBADARGS;
                    break;
                }
            }
        }
        if (instObj->numLpbkCh > 0U)
        {
            strmId = CsirxDrv_getStrmId(&captObj->platData,
                                        instObj->drvInstId,
                                        CSIRX_CH_TYPE_LPBK);
            /* assert if given stream is not supported on the module instance */
            GT_assert(CsirxTrace, (strmId != CSIRX_STREAM_ID_INVALID));
            /* Configure Loop-back Stream of CSI RX Module */
            Fvid2Utils_memcpy(&strmCfgParams,
                          &instObj->cslObj.strmCfgParams,
                          sizeof (CSIRX_StreamCfg));
            Fvid2Utils_memcpy(&strmDataCfgParams,
                          &instObj->cslObj.strmDataCfgParams,
                          sizeof (CSIRX_StreamDataCfg));
            strmDataCfgParams.enableVcSelect = 1U;
            strmDataCfgParams.enableDt0 = 1U;
            for (loopCnt = 0U ; loopCnt < instObj->numLpbkCh ; loopCnt++)
            {
                strmDataCfgParams.vcSelect |=
                    (uint16_t)((uint16_t)(0x1U) << instObj->chObj[instObj->lpbkChId[loopCnt]].chCfg->vcNum);
                strmDataCfgParams.datatypeSelect0 =
                    (uint8_t)instObj->chObj[instObj->lpbkChId[loopCnt]].chCfg->inCsiDataType;

                status = CSIRX_SetStreamCfg(&instObj->cslObj.cslCfgData,
                                            &instObj->cslObj.strmCfgParams,
                                            strmId);
                status += CSIRX_SetStreamDataCfg(&instObj->cslObj.cslCfgData,
                                                &strmDataCfgParams,
                                                strmId);
                if (status != 0U)
                {
                    GT_0trace(CsirxTrace,
                       GT_ERR,
                       "CSL FL: Invalid Loop-back Stream Config Arguments\r\n");
                    retVal = FVID2_EBADARGS;
                    break;
                }
            }
        }
    }

    return retVal;
}

static int32_t CsirxDrv_chConfigShim(CsirxDrv_ChObj *chObj)
{
    int32_t retVal = FVID2_SOK, status = CSL_PASS;

    /* Program and disable SHIM for OTF and Loop-back channels if needed,
       re-enable it in Fvid2_Start() */
    /* Disable DMA context first then program it,
       re-enable it in Fvid2_Start() */
    if (chObj->psilThreadId != CSIRX_DRV_DEF_PSIL_THREAD_ID)
    {
        /* Do following for Capture channels only */
        status =
            CSL_csirxEnableDMA(
                        (CSL_csi_rx_ifRegs *)chObj->instObj->shimBaseAddr,
                        chObj->psilThreadId,
                        (uint32_t)FALSE);
        status+= CSL_csirxConfigDMA(
                        (CSL_csi_rx_ifRegs *)chObj->instObj->shimBaseAddr,
                        &chObj->dmaCfgParams);
        if (status != CSL_PASS)
        {
            GT_0trace(CsirxTrace,
                      GT_ERR,
                      "Invalid SHIM Capture config arguments\r\n");
            retVal = FVID2_EBADARGS;
        }
    }

    return retVal;
}

static int32_t CsirxDrv_createChQueues(CsirxDrv_ChObj *chObj)
{
    int32_t  retVal = FVID2_SOK, tempRetVal;
    uint32_t qCnt = 0U;
    CsirxDrv_QueObj *qObj;
    CsirxDrv_BufManObj *bmObj;

    /* Do configuration for CSIRX_CH_TYPE_CAPT type of channel */
    if (chObj->chCfg->chType == CSIRX_CH_TYPE_CAPT)
    {
        bmObj = &chObj->bufManObj;

        bmObj->freeQ         = NULL;
        bmObj->curQ          = NULL;

        /* Create Queues */
        retVal += Fvid2Utils_constructQ(&bmObj->freeLlObj);
        GT_assert(CsirxTrace, (retVal == FVID2_SOK));
        bmObj->freeQ = &bmObj->freeLlObj;

        retVal += Fvid2Utils_constructQ(&bmObj->curLlObj);
        GT_assert(CsirxTrace, (retVal == FVID2_SOK));
        bmObj->curQ = &bmObj->curLlObj;

        retVal += Fvid2Utils_constructQ(&bmObj->doneLlObj);
        GT_assert(CsirxTrace, (retVal == FVID2_SOK));
        bmObj->doneQ = &bmObj->doneLlObj;

        /* Initialize and queue the allocate queue object to free Q */
        for (qCnt = 0U; qCnt < CSIRX_CAPT_QUEUE_DEPTH_PER_CH ; qCnt++)
        {
            qObj        = &bmObj->captQObj[qCnt];
            qObj->inUse = CSIRX_DRV_USAGE_STATUS_NOT_USED;
            qObj->type  = CSIRX_DRV_Q_OBJ_TYPE_NORMAL;
            qObj->chObj = chObj;
            qObj->frm   = NULL;
            qObj->trpd  =
                    (CSL_UdmapCppi5TRPD *)CsirxDrv_getTrpdMemAddr(chObj,
                                                                  qCnt);
#if (CSIRX_DRV_ENABLE_DEBUG == 1U)
            chObj->listOfTRPDs[qCnt] = (uint64_t)qObj->trpd;
#endif
            tempRetVal = CsirxDrv_udmaRxTrpdInit(
                                &chObj->rxChObj,
                                (uint8_t *)qObj->trpd,
                                NULL,
                                chObj->chCfg,
                                chObj->chId);
            if (tempRetVal != FVID2_SOK)
            {
                retVal = FVID2_EINVALID_PARAMS;
                break;
            }
            Fvid2Utils_queue(bmObj->freeQ, &qObj->qElem, qObj);
        }
    }

    /* Deallocate if error occurs */
    if (retVal != FVID2_SOK)
    {
        CsirxDrv_deleteChQueues(chObj);
    }

    return retVal;
}

static void CsirxDrv_deleteChQueues(CsirxDrv_ChObj *chObj)
{
    CsirxDrv_QueObj    *qObj;
    CsirxDrv_BufManObj *bmObj;

    /* NULL pointer check */
    GT_assert(CsirxTrace, (chObj != NULL));
    bmObj = &chObj->bufManObj;

    if (bmObj->freeQ != NULL)
    {
        /* Free-up all the queued free queue objects */
        for(;;)
        {
            qObj = (CsirxDrv_QueObj *) Fvid2Utils_dequeue(bmObj->freeQ);
            if (qObj == NULL)
            {
                /* No more in queue */
                break;
            }
        }

        /* Delete the free Q */
        Fvid2Utils_destructQ(bmObj->freeQ);
        bmObj->freeQ = NULL;
    }


    if (bmObj->curQ != NULL)
    {
        /* Delete the free Q */
        Fvid2Utils_destructQ(bmObj->curQ);
        bmObj->curQ = NULL;
    }

    if (bmObj->doneQ != NULL)
    {
        /* Delete the free Q */
        Fvid2Utils_destructQ(bmObj->doneQ);
        bmObj->doneQ = NULL;
    }
}

static int32_t CsirxDrv_startIoctl(CsirxDrv_VirtContext *virtContext)
{
    int32_t retVal = FVID2_SOK;
    uint32_t chIdx = 0U, loopCnt = 0U, status;
    CsirxDrv_ChObj *chObj;
    CSIRX_StreamCtrl strmCtrlParams;
    CsirxDrv_InstObj *instObj;

    /* Check for NULL pointers */
    GT_assert(CsirxTrace, (virtContext != NULL));
    GT_assert(CsirxTrace, (virtContext->numCh <= CSIRX_NUM_CH));
    instObj = virtContext->instObj;
    /* Pend the instance semaphore */
    (void)SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    for (chIdx = 0U ; chIdx < virtContext->numCh ; chIdx++)
    {
        /* Get channel object */
        chObj = &instObj->chObj[(virtContext->chId[chIdx])];
        retVal = Csirx_startCh(chObj);
        if (retVal != FVID2_SOK)
        {
            break;
        }

    }
    if (retVal == FVID2_SOK)
    {
        if (gCsirxCommonObj.numVirtContUsed[instObj->drvInstId] >= 1U)
        {
            /* start streams */
            /* Start streams only if this is first active Virtual context */
            /* Re-enabling streams multiple time should not affect the operation */
            for (loopCnt = 0U ; loopCnt < CSIRX_NUM_STREAM ; loopCnt++)
            {
                if(1U == instObj->createParams.instCfg.enableStrm[loopCnt])
                {
                    /* start stream */
                    strmCtrlParams.softRst = 0U;
                    strmCtrlParams.abrt    = 0U;
                    strmCtrlParams.stop    = 0U;
                    strmCtrlParams.start   = 1U;
                    status = CSIRX_SetStreamCtrl(&instObj->cslObj.cslCfgData,
                                                 &strmCtrlParams,
                                                 loopCnt);
                    if (status != 0U)
                    {
                        GT_0trace(CsirxTrace,
                                 GT_ERR,
                                 "CSL FL: Stream start failed\r\n");
                        retVal = FVID2_EBADARGS;
                        break;
                    }

                }
            }
        }
    }
    if (retVal == FVID2_SOK)
    {
        /* change driver instance to started/running state */
        virtContext->state = CSIRX_DRV_STATE_RUNNING;
        instObj->numDrvInstStarted++;
    }
    /* Post the instance semaphore */
    (void)SemaphoreP_post(&instObj->lockSem);

    return retVal;
}

static int32_t CsirxDrv_stopIoctl(CsirxDrv_VirtContext *virtContext)
{
    int32_t retVal = FVID2_SOK;
    uint32_t chIdx = 0U, cookie, status, loopCnt;
    CsirxDrv_ChObj *chObj;
    CSIRX_StreamCtrl strmCtrlParams;
    CsirxDrv_InstObj *instObj;

    /* Check for NULL pointers */
    GT_assert(CsirxTrace, (virtContext != NULL));
    GT_assert(CsirxTrace, (virtContext->numCh <= CSIRX_NUM_CH));
    instObj = virtContext->instObj;
    /* Pend the instance semaphore */
    (void)SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);
    /* Disable HW interrupts here */
    cookie = HwiP_disable();
    if (instObj->numDrvInstStarted == 1U)
    {
        /* Stop streams only if this is last active Virtual context */
        /* TODO: All streams are stopped, it should based on channel type,
           if OTF is not used then no need to stop the stream */
        for (loopCnt = 0U ; loopCnt < CSIRX_NUM_STREAM ; loopCnt++)
        {
            /* stop stream */
            strmCtrlParams.softRst = 0U;
            strmCtrlParams.abrt    = 0U;
            strmCtrlParams.stop    = 1U;
            strmCtrlParams.start   = 0U;
            status = CSIRX_SetStreamCtrl(&instObj->cslObj.cslCfgData,
                                         &strmCtrlParams,
                                         loopCnt);
            if (status != 0U)
            {
                GT_0trace(CsirxTrace,
                        GT_ERR,
                        "CSL FL: Stream stop failed\r\n");
                retVal = FVID2_EBADARGS;
                break;
            }
        }
    }

    for (chIdx = 0U ; chIdx < virtContext->numCh ; chIdx++)
    {
        /* Get channel object */
        chObj = &instObj->chObj[(virtContext->chId[chIdx])];
        retVal = Csirx_stopCh(chObj);
        if (retVal != FVID2_SOK)
        {
            break;
        }
    }
    /* Enable HW interrupts here */
    HwiP_restore(cookie);

    if (retVal == FVID2_SOK)
    {
        /* change driver instance to stopped state */
        virtContext->state = CSIRX_DRV_STATE_STOPPED;
        instObj->numDrvInstStarted--;
    }

    /* Post the instance semaphore */
    (void)SemaphoreP_post(&instObj->lockSem);

    return retVal;
}

static int32_t CsirxDrv_getStatusIoctl(const CsirxDrv_VirtContext *virtContext,
                                       Csirx_InstStatus *captStat)
{
    int32_t retVal = FVID2_SOK;
    uint32_t chIdx, streamIdx;
    CsirxDrv_InstObj *instObj;

    instObj = virtContext->instObj;
    /* Pend on the instance semaphore */
    (void)SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);
    /* Copy capture status from DRV object to application provided parameter */
    for (chIdx = 0U ; chIdx < virtContext->numCh ; chIdx++)
    {
        captStat->queueCount[chIdx] =
            instObj->status.queueCount[virtContext->chId[chIdx]];
        captStat->dequeueCount[chIdx] =
            instObj->status.dequeueCount[virtContext->chId[chIdx]];
        captStat->dropCount[chIdx] =
            instObj->status.dropCount[virtContext->chId[chIdx]];
    }
    for (streamIdx = 0U ; streamIdx < CSIRX_NUM_STREAM ; streamIdx++)
    {
        captStat->strmFIFOOvflCount[streamIdx] =
            instObj->status.strmFIFOOvflCount[streamIdx];
    }
    captStat->overflowCount         = instObj->status.overflowCount;
    captStat->spuriousUdmaIntrCount = instObj->status.spuriousUdmaIntrCount;
    captStat->frontFIFOOvflCount    = instObj->status.frontFIFOOvflCount;
    captStat->crcCount              = instObj->status.crcCount;
    captStat->eccCount              = instObj->status.eccCount;
    captStat->correctedEccCount     = instObj->status.correctedEccCount;
    captStat->dataIdErrorCount      = instObj->status.dataIdErrorCount;
    captStat->invalidAccessCount    = instObj->status.invalidAccessCount;
    captStat->invalidSpCount        = instObj->status.invalidSpCount;

    /* Post the instance semaphore */
    (void)SemaphoreP_post(&instObj->lockSem);

    return retVal;
}

static void CsirxDrv_deleteChObj(CsirxDrv_ChObj *chObj)
{
    int32_t retVal = FVID2_SOK;

    /* Close sequence for UDMA DRV */
    retVal = CsirxDrv_clearUdmaParams(chObj);
    if (retVal != UDMA_SOK)
    {
        GT_0trace(CsirxTrace,
                  GT_ERR,
                  "[ERROR]UDMA channel close FAILED!!!\r\n");
    }
    /* Delete channel queues */
    CsirxDrv_deleteChQueues(chObj);
}

static uint32_t CsirxDrv_getStrmId(const Csirx_PlatformData *platformData,
                                   uint32_t instId,
                                   uint32_t strmType)
{
    uint32_t strmId = CSIRX_STREAM_ID_INVALID, loopCnt = 0U;

    /* look if given type of stream is supported or not and if supported then
       on which physical stream it supported */
    for (loopCnt = 0U ; loopCnt < CSIRX_INSTANCE_ID_MAX ; loopCnt++)
    {
        if (( platformData->strmStatus[instId][loopCnt] ==
                                    CSIRX_STRM_SUPPORT_SUPPORTED) &&
            ( platformData->strmType[instId][loopCnt] == strmType))
        {
            strmId = loopCnt;
        }
    }

    return strmId;
}

static void Csirx_printLogs(void)
{
#if (CSIRX_DRV_ENABLE_DEBUG == 1U)
    uint32_t loopIdx, loopCnt;

    GT_0trace(CsirxTrace,
              GT_INFO,
              "\n\r=====================================================\r\n");
    GT_0trace(CsirxTrace,
              GT_INFO,
              "::Debug Logs::");
    GT_0trace(CsirxTrace,
              GT_INFO,
              "\n\r=====================================================\r\n");
    if (gCsirxCommonObj.frmCntOverflow == 1U)
    {
        loopCnt = CSIRX_DRV_LOG_CNT;
    }
    else
    {
        loopCnt = gCsirxCommonObj.frmCnt;
    }

    for (loopIdx = 0U ;loopIdx < loopCnt ;loopIdx++)
    {
        GT_7trace(CsirxTrace,
                  GT_INFO,
                  "[LOG]Frame: %d | Inst: %d | Ch ID: 0x%x | FRM TYPE: %d | "
                  "FRM Status: 0x%x | TR Resp: 0x%x | TS: %d |\r\n",
                  loopIdx,
                  gCsirxCommonObj.frmInstId[loopIdx],
                  gCsirxCommonObj.frmChId[loopIdx],
                  gCsirxCommonObj.frmType[loopIdx],
                  gCsirxCommonObj.frmStatus[loopIdx],
                  gCsirxCommonObj.trResp[loopIdx],
                  gCsirxCommonObj.frmTS[loopIdx]);
    }

    GT_0trace(CsirxTrace,
              GT_INFO,
              "\n\r=====================================================\r\n");
    GT_0trace(CsirxTrace,
              GT_INFO,
              "::TR Submit Debug Logs::");
    GT_0trace(CsirxTrace,
              GT_INFO,
              "\n\r=====================================================\r\n");
    for (loopIdx = 0U ;loopIdx < CSIRX_DRV_TR_LOG_CNT ;loopIdx++)
    {
        GT_4trace(CsirxTrace,
                  GT_INFO,
                  "[LOG]TR Submit No.: %d | CH ID: %d | TRPD: 0x%x | TS: %d |\r\n",
                  loopIdx,
                  gTrSubmit[loopIdx][0U],
                  gTrSubmit[loopIdx][1U],
                  gTrSubmit[loopIdx][2U]);
    }

    GT_0trace(CsirxTrace,
              GT_INFO,
              "\n\r=====================================================\r\n");
    GT_0trace(CsirxTrace,
              GT_INFO,
              "::TR Out/Complete Debug Logs::");
    GT_0trace(CsirxTrace,
              GT_INFO,
              "\n\r=====================================================\r\n");
    for (loopIdx = 0U ;loopIdx < CSIRX_DRV_TR_LOG_CNT ;loopIdx++)
    {
        GT_4trace(CsirxTrace,
                  GT_INFO,
                  "[LOG]TR Out No.: %d | CH ID: %d | pDesc: 0x%x | TS: %d |\r\n",
                  loopIdx,
                  gTrOut[loopIdx][0U],
                  gTrOut[loopIdx][1U],
                  gTrOut[loopIdx][2U]);
    }

    GT_0trace(CsirxTrace,
              GT_INFO,
              "\n\r=====================================================\r\n");
    GT_0trace(CsirxTrace,
              GT_INFO,
              "::Event Debug Logs::");
    GT_0trace(CsirxTrace,
              GT_INFO,
              "\n\r=====================================================\r\n");
    if (gCsirxCommonObj.eventCntOverflow == 1U)
    {
        loopCnt = CSIRX_DRV_LOG_CNT;
    }
    else
    {
        loopCnt = gCsirxCommonObj.eventCnt;
    }
    for (loopIdx = 0U ;loopIdx < loopCnt ;loopIdx++)
    {
        GT_4trace(CsirxTrace,
                  GT_INFO,
                  "[LOG]Event No.: %d | Inst: %d | Status: 0x%x | TS: %d |\r\n",
                  loopIdx,
                  gCsirxCommonObj.eventInstId[loopIdx],
                  gCsirxCommonObj.eventStatus[loopIdx],
                  gCsirxCommonObj.eventTS[loopIdx]);
    }
#else
    GT_0trace(CsirxTrace,
              GT_INFO,
              "\n\rDebug Logging is not enabled."
              " Please enable it through 'CSIRX_DRV_ENABLE_DEBUG'.\r\n");
#endif
}

static int32_t Csirx_setDphyCfg(CsirxDrv_VirtContext *virtContext,
                         const Csirx_DPhyCfg *dphyCfg)
{
    int32_t retVal = FVID2_SOK;
    CsirxDrv_InstObj *instObj;

    /* Check parameters values */
    if ((dphyCfg->inst < CSIRX_INSTANCE_ID_MAX) &&
        ((dphyCfg->psmClkFreqDiv < 256U) && (dphyCfg->psmClkFreqDiv > 0U)) &&
        (dphyCfg->leftLaneBandSpeed < CSIRX_LANE_BAND_SPEED_RESERVED) &&
        (dphyCfg->rightLaneBandSpeed < CSIRX_LANE_BAND_SPEED_RESERVED) &&
        (dphyCfg->bandGapTimerVal < 256U))
    {
        instObj = &gCsirxCommonObj.instObj[dphyCfg->inst];
        /* Copy Csirx_DPhyCfg to instance object */
        if (instObj->dpyCfgDone == 0U)
        {
            Fvid2Utils_memcpy(&instObj->dphyCfg,
                              dphyCfg,
                              sizeof (instObj->dphyCfg));
        }
    }
    else
    {
        retVal = FVID2_EBADARGS;
    }
    if (retVal == FVID2_SOK)
    {
        if (instObj->dpyCfgDone == 0U)
        {
            retVal = Csirx_dphyCfg(dphyCfg);
            instObj->dpyCfgDone = 1U;
        }
        else
        {
            /* check DPHY params with programmed one */
            retVal = CsirxDrv_checkDphyrxConfig(dphyCfg, &instObj->dphyCfg);
        }
    }

    return retVal;
}

static int32_t Csirx_dphyCfg(const Csirx_DPhyCfg *dphyCfg)
{
    CsirxDrv_InstObj *instObj;
    int32_t retVal = FVID2_SOK;

    /* Get the instance object for this instance */
    instObj = &gCsirxCommonObj.instObj[dphyCfg->inst];
    {
        /* Step-1: Enable power & ground (Done in hardware)*/
        /* Step-2: Assert lane reset (lane_rstb, apb_presetn, tap_rstb_n) = 0 (Done in hardware)*/
        /* Step-3: Disable PSO */
        CsirxDrv_dphyrxPsoDisable(instObj->dPhyCoreAddr, 1u);

        /* Step-4: De-Assert LaneReset to common */
        CsirxDrv_dphyCommonReset(instObj->dPhyCoreAddr, 1u);

        /* Step-5: Apply Band control setting for clock and data lanes by
                   writing into PCS test register TX_DIG_TBIT0 according
                   to data rate. */
        CsirxDrv_dphyrxSetLaneBandSpeed(instObj->dPhyCoreAddr,
                                        &instObj->dphyCfg);

        /* Step-6: Write proper clock divider value into PCS test register
                   TX_DIG_TBIT1 */
        CsirxDrv_dphyrxWrapPsmClockConfig(instObj->dPhyWrapAddr,
                                      dphyCfg->psmClkFreqDiv);

        /* Step-7 */
        CsirxDrv_dphyrxCorePpiClockConfig(instObj->dPhyCoreAddr,
                                          &instObj->dphyCfg);

        /* Step-8: Wait for DPHY cmn_ready before enabling lanes */
        CsirxDrv_dphyrxCoreCommonReady(instObj->dPhyCoreAddr);

        /* Step-9 & 10: */
        /* Enable All Lanes and De-Assert CLK and Data lane reset */
        {
            uint32_t loopCnt = 0U, status;
            CSIRX_DphyLaneControl cfgCsiRxDphy;

            /* DPHYRX clock and data lanes enable */
            cfgCsiRxDphy.clEnable = 1U;
            cfgCsiRxDphy.clReset  = 1U;
            /* Put Clock lane and data lanes in reset till configuration
               is completed. Release these reset after configuration are
               done during DPHY CFG. */
            for (loopCnt = 0U ;
                 loopCnt < instObj->createParams.instCfg.numDataLanes ;
                 loopCnt++)
            {
                cfgCsiRxDphy.dlEnable[loopCnt] = 1U;
                cfgCsiRxDphy.dlReset[loopCnt]  = 1U;
            }
            while (loopCnt < CSIRX_CAPT_DATA_LANES_MAX)
            {
                cfgCsiRxDphy.dlEnable[loopCnt] = 0U;
                cfgCsiRxDphy.dlReset[loopCnt]  = 1U;
                loopCnt++;
            }

            status = CSIRX_SetDphyLaneControl(&instObj->cslObj.cslCfgData,
                                              &cfgCsiRxDphy);
            if (status != 0U)
            {
                GT_0trace(CsirxTrace,
                          GT_ERR,
                          "CSL FL: D-PHY configuration failed...\r\n");
                retVal = FVID2_EBADARGS;
            }
        }

        /* Step-11: Wait for 1ms */
        (void)ClockP_sleep(1U);

        /* Step-12: Wait for DPHY lanes to be ready */
        CsirxDrv_dphyrxCoreLaneReady(instObj->dPhyCoreAddr,
                                 instObj->createParams.instCfg.numDataLanes);

    }

    return retVal;
}

uint32_t CsirxDrv_getBpp(uint32_t dt)
{
    uint32_t bpp = 0U, loopCnt;

    for (loopCnt = 0U ;
         loopCnt < (sizeof(gRxDtInfo) / sizeof(dataTypeInfo)) ;
         loopCnt++)
    {
        if (gRxDtInfo[loopCnt].dt == dt)
        {
            break;
        }
    }
    if (loopCnt < (sizeof(gRxDtInfo) / sizeof(dataTypeInfo)))
    {
        bpp = gRxDtInfo[loopCnt].bpp;
    }

    return bpp;
}

uint32_t CsirxDrv_getStorageBpp(uint32_t dt)
{
    uint32_t bpp = 0U, loopCnt;

    for (loopCnt = 0U ;
         loopCnt < (sizeof(gRxDtInfo) / sizeof(dataTypeInfo)) ;
         loopCnt++)
    {
        if (gRxDtInfo[loopCnt].dt == dt)
        {
            break;
        }
    }
    if (loopCnt < (sizeof(gRxDtInfo) / sizeof(dataTypeInfo)))
    {
        bpp = gRxDtInfo[loopCnt].storageBpp;
    }

    return bpp;
}

static int32_t CsirxDrv_setChCfgParams(CsirxDrv_ChObj *chObj, Csirx_ChCfg *chCfg)
{
    int32_t retVal = FVID2_SOK;
    CsirxDrv_InstObj *instObj;

    instObj = chObj->instObj;
    chObj->chCfg = chCfg;
    if (chCfg->chType == CSIRX_CH_TYPE_CAPT)
    {
        instObj->numCaptCh++;
        if (instObj->numCaptCh > CSIRX_NUM_CH_CAPT)
        {
            GT_0trace(
                CsirxTrace,
                GT_ERR,
                "More Capture channels are provided than HW "
                "can process\r\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
        if(retVal == FVID2_SOK)
        {
            retVal = CsirxDrv_getDMACfgParams(chObj);
        }
    }
    if (chCfg->chType == CSIRX_CH_TYPE_OTF)
    {
        instObj->otfChId[instObj->numOtfCh] = chObj->chId;
        instObj->numOtfCh++;
        if (instObj->numOtfCh > CSIRX_NUM_CH_OTF_MAX)
        {
            GT_0trace(
                CsirxTrace,
                GT_ERR,
                "More OTF channels are provided than HW can "
                "process\r\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
    }
    if (chCfg->chType == CSIRX_CH_TYPE_LPBK)
    {
        instObj->lpbkChId[instObj->numLpbkCh] = chObj->chId;
        instObj->numLpbkCh++;
        if (instObj->numLpbkCh > CSIRX_NUM_CH_LPBK_MAX)
        {
            GT_0trace(
                CsirxTrace,
                GT_ERR,
                "More Loop-back channels are provided than "
                "HW can process\r\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
    }

    return retVal;
}

static int32_t Csirx_startCh(CsirxDrv_ChObj *chObj)
{
    int32_t retVal = FVID2_SOK, tempRetVal = UDMA_SOK;
    uint32_t curQCnt = 0U, chIdx;
    CsirxDrv_BufManObj *bmObj;
    CsirxDrv_InstObj *instObj;
    CsirxDrv_QueObj *qObj;
    CSL_UdmapTR1 *pTr;

    /* Enable channel only if it is created or stopped */
    if ((chObj->status == CSIRX_DRV_CH_STATE_CREATED) ||
        (chObj->status == CSIRX_DRV_CH_STATE_STOPPED))
    {
        instObj = chObj->instObj;
        chIdx = chObj->chId;
        /* Enable DMA context for PSIL threads and UDMA channels only
           for capture channels */
        if (chObj->chCfg->chType == CSIRX_CH_TYPE_CAPT)
        {
            bmObj = &chObj->bufManObj;
            /* check if any frames are queued before start,
               if none are queued, program Frame drop buffer  */
            curQCnt = Fvid2Utils_getNumQElem(bmObj->curQ);
            if (curQCnt <= 1U)
            {
                while (curQCnt < CSIRX_DRV_FRAME_DROP_TRPD_NUM)
                {
                    /* Allocate a free queue object from the pool */
                    qObj =
                     (CsirxDrv_QueObj *) Fvid2Utils_dequeue(chObj->bufManObj.freeQ);
                    if (qObj == NULL)
                    {
                        GT_0trace(
                            CsirxTrace, GT_ERR,
                            "ALLOC: Q object allocation failed\r\n");
                        retVal = FVID2_EALLOC;
                    }
                    if(retVal == FVID2_SOK)
                    {
                        /* Copy the frame to the driver's queue object */
                        qObj->frm = NULL;
                        /* Re-program dim0 and destination buffer */
                        pTr = UdmaUtils_getTrpdTr1Pointer((uint8_t *)qObj->trpd, 0U);

                        /* Keep over-writing frameDrop buffer with each incoming line */
                        pTr->dim1 = 0;
                        pTr->addr = (uint64_t)(instObj->createParams.frameDropBuf);
                        /* Mark qBoj as Frame Drop */
                        qObj->type = CSIRX_DRV_Q_OBJ_TYPE_FD;
                        /* Submit TR to FQ ring for UDMA channel */
                        /* Writeback cache */
                        CsirxDrv_cacheWb(qObj->trpd,
                                         CSIRX_DRV_TRPD_SIZE_ALIGN);
                        /* Submit TRPD to channel */
#if (CSIRX_DRV_ENABLE_DEBUG == 1U)
                        {
                            gTrSubmit[gTrSubmitCnt][0U] = (uint32_t)qObj->trpd;
                            gTrSubmit[gTrSubmitCnt][1U] = instObj->drvInstId;
                            gTrSubmit[gTrSubmitCnt][2U] = chIdx;
                            if (gCsirxCommonObj.getTimeStamp != NULL)
                            {
                                gTrSubmit[gTrSubmitCnt][3U] =
                                                (uint32_t)gCsirxCommonObj.getTimeStamp(NULL);;
                            }
                            else
                            {
                                gTrSubmit[gTrSubmitCnt][3U] = 0U;
                            }
                            gTrSubmitCnt = (gTrSubmitCnt + 1U) % CSIRX_DRV_TR_LOG_CNT;
                            CsirxDrv_cacheWb(&gTrSubmit[0U],
                                             sizeof(gTrSubmit));
                        }
#endif
                        tempRetVal = Udma_ringQueueRaw(
                                            Udma_chGetFqRingHandle(&chObj->rxChObj),
                                            (uint64_t)qObj->trpd);
                        if(tempRetVal != UDMA_SOK)
                        {
                            GT_0trace(
                                CsirxTrace, GT_ERR,
                                "Queue: Submitting of TR failed\r\n");
                            /* Queue back the Object which was
                               de-queued earlier from freeQ */
                            Fvid2Utils_queue(bmObj->freeQ, &qObj->qElem, qObj);
                            retVal = CsirxDrv_udmaToFvid2ErrorMap(tempRetVal);
                        }
                        else
                        {
                            /* Add the queue object in driver's current queue */
                            Fvid2Utils_queue(bmObj->curQ, &qObj->qElem, qObj);
                        }
                    }
                    curQCnt = Fvid2Utils_getNumQElem(bmObj->curQ);
                }
            }
            if (retVal == FVID2_SOK)
            {
                /* Enable DMA context for PSIL thread */
                tempRetVal = CSL_csirxEnableDMA(
                                    (CSL_csi_rx_ifRegs *)instObj->shimBaseAddr,
                                    instObj->chObj[chIdx].psilThreadId,
                                    (uint32_t)TRUE);
                if (tempRetVal != CSL_PASS)
                {
                    retVal = FVID2_EFAIL;
                    GT_0trace(
                            CsirxTrace, GT_ERR,
                            "PSIL DMA context enable failed!!!\r\n");
                }
            }
            if (retVal == FVID2_SOK)
            {
                /* Enable UDMA channel */
                tempRetVal = Udma_chEnable(&chObj->rxChObj);
                if(tempRetVal != UDMA_SOK)
                {
                    retVal = CsirxDrv_udmaToFvid2ErrorMap(tempRetVal);
                    GT_0trace(
                            CsirxTrace,
                            GT_ERR,
                            "[ERROR]UDMA RX channel enable FAILED!!!\r\n");
                }
            }
        }
        if (retVal == FVID2_SOK)
        {
            /* set channel state to running */
            chObj->status = CSIRX_DRV_CH_STATE_RUNNING;
        }
    }

    return retVal;
}

static int32_t Csirx_stopCh(CsirxDrv_ChObj *chObj)
{
    int32_t retVal = FVID2_SOK, tempRetVal = UDMA_SOK;
    CsirxDrv_InstObj *instObj;

    /* set channel state to stopping */
    chObj->status = CSIRX_DRV_CH_STATE_STOPPING;
    instObj = chObj->instObj;
    /* Disable DMA context for PSIL threads and UDMA channels only
       for capture channels */
    if (chObj->chCfg->chType == CSIRX_CH_TYPE_CAPT)
    {
      /* Disable DMA context for PSIL thread */
      tempRetVal = CSL_csirxEnableDMA(
                          (CSL_csi_rx_ifRegs *)instObj->shimBaseAddr,
                          chObj->psilThreadId,
                          (uint32_t)FALSE);
      if (tempRetVal != CSL_PASS)
      {
          retVal = FVID2_EFAIL;
          GT_0trace(
                  CsirxTrace, GT_ERR,
                  "PSIL DMA context disable failed!!!\r\n");
      }
      if (retVal == FVID2_SOK)
      {
        /* Disable UDMA channel */
        tempRetVal = Udma_chDisable(&chObj->rxChObj,
                                    UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
        if(tempRetVal != UDMA_SOK)
        {
            retVal = CsirxDrv_udmaToFvid2ErrorMap(tempRetVal);
            GT_0trace(
                    CsirxTrace,
                    GT_ERR,
                    "[ERROR]UDMA RX channel disable FAILED!!!\r\n");
        }
      }
    }
    if (retVal == FVID2_SOK)
    {
        /* set channel state to stopped */
        chObj->status = CSIRX_DRV_CH_STATE_STOPPED;
    }

    return retVal;
}

static int32_t CsirxDrv_getActiveChNumIoctl(CsirxDrv_InstObj *instObj,
                                            uint32_t *chNum)
{
    int32_t retVal = FVID2_SOK;

    GT_assert(CsirxTrace, (instObj != NULL));
    *chNum = instObj->numCaptCh;

    return retVal;
}

static int32_t CsirxDrv_getFreeChNumIoctl(CsirxDrv_InstObj *instObj,
                                          uint32_t *chNum)
{
    int32_t retVal = FVID2_SOK;
    uint32_t chIdx;

    GT_assert(CsirxTrace, (instObj != NULL));

    for (chIdx = 0U ; chIdx < CSIRX_NUM_CH ; chIdx++)
    {
        if (instObj->chObj[chIdx].status == CSIRX_DRV_CH_STATE_IDLE)
        {
            break;
        }
    }

    if (chIdx < CSIRX_NUM_CH)
    {
        *chNum = chIdx;
    }
    else
    {
        retVal = FVID2_EAGAIN;
    }

    return retVal;
}

static int32_t CsirxDrv_startChannelIoctl(CsirxDrv_InstObj *instObj,
                                          uint32_t chNum)
{
    int32_t retVal = FVID2_SOK;
    CsirxDrv_ChObj *chObj;

    GT_assert(CsirxTrace, (instObj != NULL));
    GT_assert(CsirxTrace, (chNum < CSIRX_NUM_CH));

    /* Get channel object */
    chObj = &instObj->chObj[chNum];
    retVal = Csirx_startCh(chObj);

    return retVal;
}

static int32_t CsirxDrv_stopChannelIoctl(CsirxDrv_InstObj *instObj,
                                         uint32_t chNum)
{
    int32_t retVal = FVID2_SOK;
    CsirxDrv_ChObj *chObj;

    GT_assert(CsirxTrace, (instObj != NULL));
    GT_assert(CsirxTrace, (chNum < CSIRX_NUM_CH));

    /* Get channel object */
    chObj = &instObj->chObj[chNum];
    retVal = Csirx_stopCh(chObj);

    return retVal;
}

static int32_t CsirxDrv_checkCreateParams(Csirx_CreateParams *programmed,
                                          Csirx_CreateParams *new)
{
    int32_t retVal = FVID2_SOK;
    uint32_t laneIdx;

    if ((programmed->instCfg.enableCsiv2p0Support ==
                                        new->instCfg.enableCsiv2p0Support) &&
        (programmed->instCfg.numDataLanes ==
                                        new->instCfg.numDataLanes)&&
        (programmed->instCfg.enableErrbypass ==
                                        new->instCfg.enableErrbypass) &&
        (programmed->instCfg.numPixelsStrm0 == new->instCfg.numPixelsStrm0))
    {
        for (laneIdx = 0U ; laneIdx < CSIRX_CAPT_DATA_LANES_MAX ; laneIdx++)
        {
            if (programmed->instCfg.dataLanesMap[laneIdx] !=
                                        new->instCfg.dataLanesMap[laneIdx])
            {
                break;
            }
        }
        if (laneIdx < CSIRX_CAPT_DATA_LANES_MAX)
        {
            /* check failed as createParams don't match */
            retVal = FVID2_WNON_RECOMMENDED_PARAMS;
        }
    }
    else
    {
        /* check failed as createParams don't match */
        retVal = FVID2_WNON_RECOMMENDED_PARAMS;
    }

    return retVal;
}

static int32_t CsirxDrv_validateCreateParams(Csirx_CreateParams *params)
{
    int32_t retVal = FVID2_SOK;
    uint32_t numPixel;
    uint32_t idx, bpp;
    bool breakFlag = false;

    for (idx = 0U ; idx < params->numCh ; idx++)
    {
        bpp = CsirxDrv_getBpp(params->chCfg[idx].inCsiDataType);
        if (bpp == 0U)
        {
            /* Given data type is not supported */
            retVal = FVID2_EINVALID_PARAMS;
            GT_0trace(CsirxTrace, GT_ERR, "Invalid/Unsupported data type\r\n");

            breakFlag = true;
        }
        else
        {
            numPixel = (CSIRX_CORE_PIXEL_OUTPUT_BUS_WIDTH / bpp);
            if ((0x1U << params->instCfg.numPixelsStrm0) <= numPixel)
            {
                /* Continue as given DT can be outputted at provided rate */
            }
            else
            {
                retVal = FVID2_EINVALID_PARAMS;
                GT_1trace(CsirxTrace,
                          GT_ERR,
                          "Wrong pixels per clock configuration for 0x%x\r\n",
                          params->chCfg[idx].inCsiDataType);
                breakFlag = true;

            }
        }
        if(breakFlag == true)
        {
          break;
        }
    }

    return retVal;
}
