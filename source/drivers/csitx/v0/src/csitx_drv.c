/*
 *  Copyright (c) Texas Instruments Incorporated 2020-2025
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
 *  \file csitx_drv.c
 *
 *  \brief File containing the CSITX driver functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/csitx/v0/include/csitx_drvPriv.h>
#include <drivers/csitx/v0/include/csitx_drvUdma.h>
#include <kernel/dpl/ClockP.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief CSITX capture driver ID used at the time of FVID2 create. */
#define CSITX_STREAM_ID_INVALID              ((uint32_t)0xFFFFU)

#define CSITX_DEF_BPP                        ((uint32_t)12U)

/** \brief CSI protocol data type info */
dataTypeInfo gdtInfo[] =
{
    {FVID2_CSI2_DF_YUV420_8B, 8U, CSITX_BITS_PER_PIXEL_16_BITS},
    {FVID2_CSI2_DF_YUV420_10B, 10U, CSITX_BITS_PER_PIXEL_32_BITS},
    {FVID2_CSI2_DF_YUV420_8B_LEGACY, 12U, CSITX_BITS_PER_PIXEL_12_BITS},
    {FVID2_CSI2_DF_YUV420_8B_CHROMA_SHIFT, 8U, CSITX_BITS_PER_PIXEL_12_BITS},
    {FVID2_CSI2_DF_YUV420_10B_CHROMA_SHIFT, 10U, CSITX_BITS_PER_PIXEL_12_BITS},
    {FVID2_CSI2_DF_YUV422_8B, 16U, CSITX_BITS_PER_PIXEL_16_BITS},
    {FVID2_CSI2_DF_YUV422_10B, 20U, CSITX_BITS_PER_PIXEL_64_BITS},
    {FVID2_CSI2_DF_RGB444, 12U, CSITX_BITS_PER_PIXEL_16_BITS},
    {FVID2_CSI2_DF_RGB555, 15U, CSITX_BITS_PER_PIXEL_16_BITS},
    {FVID2_CSI2_DF_RGB565, 16U, CSITX_BITS_PER_PIXEL_16_BITS},
    {FVID2_CSI2_DF_RGB666, 18U, CSITX_BITS_PER_PIXEL_32_BITS},
    {FVID2_CSI2_DF_RGB888, 24U, CSITX_BITS_PER_PIXEL_32_BITS},
    {FVID2_CSI2_DF_RAW6, 6U, CSITX_BITS_PER_PIXEL_8_BITS},
    {FVID2_CSI2_DF_RAW7, 7U, CSITX_BITS_PER_PIXEL_8_BITS},
    {FVID2_CSI2_DF_RAW8, 8U, CSITX_BITS_PER_PIXEL_8_BITS},
    {FVID2_CSI2_DF_RAW10, 10U, CSITX_BITS_PER_PIXEL_16_BITS},
    {FVID2_CSI2_DF_RAW12, 12U, CSITX_BITS_PER_PIXEL_16_BITS},
    {FVID2_CSI2_DF_RAW14, 14U, CSITX_BITS_PER_PIXEL_16_BITS},
    {FVID2_CSI2_DF_RAW16, 16U, CSITX_BITS_PER_PIXEL_16_BITS},
    {FVID2_CSI2_DF_RAW20, 20U, CSITX_BITS_PER_PIXEL_32_BITS},
    /* TODO: Replace following with CSL macros in the file 'csl_fvid2_dataTypes.h'
             Hard-coding as corresponding patch might not be merged */
    {0x10, 8U, CSITX_BITS_PER_PIXEL_8_BITS},
    {0x11, 8U, CSITX_BITS_PER_PIXEL_8_BITS},
    {0x12, 8U, CSITX_BITS_PER_PIXEL_8_BITS},
    {0x13, 8U, CSITX_BITS_PER_PIXEL_8_BITS},
    {0x14, 8U, CSITX_BITS_PER_PIXEL_8_BITS},
    {0x15, 8U, CSITX_BITS_PER_PIXEL_8_BITS},
    {0x15, 8U, CSITX_BITS_PER_PIXEL_8_BITS},
    {0x16, 8U, CSITX_BITS_PER_PIXEL_8_BITS},
    {0x17, 8U, CSITX_BITS_PER_PIXEL_8_BITS},
    {0x30, 8U, CSITX_BITS_PER_PIXEL_8_BITS},
    {0x31, 8U, CSITX_BITS_PER_PIXEL_8_BITS},
    {0x32, 8U, CSITX_BITS_PER_PIXEL_8_BITS},
    {0x33, 8U, CSITX_BITS_PER_PIXEL_8_BITS},
    {0x34, 8U, CSITX_BITS_PER_PIXEL_8_BITS},
    {0x35, 8U, CSITX_BITS_PER_PIXEL_8_BITS},
    {0x35, 8U, CSITX_BITS_PER_PIXEL_8_BITS},
    {0x36, 8U, CSITX_BITS_PER_PIXEL_8_BITS},
    {0x37, 8U, CSITX_BITS_PER_PIXEL_8_BITS},
};

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

CsitxDrv_CommonObj gCsitxCommonObj;

#if (CSITX_DRV_ENABLE_DEBUG == 1U)
uint32_t gTxTrSubmit[CSITX_DRV_TR_LOG_CNT][3] = {0U};
uint32_t gTxTrSubmitCnt = 0U;
uint32_t gTxTrOut[CSITX_DRV_TR_LOG_CNT][3] = {0U};
uint32_t gTxTrOutCnt = 0U;
#endif
/* ========================================================================== */
/*                  Internal/Private Function Declarations                   */
/* ========================================================================== */

static int32_t CsitxDrv_setInstCfgParams(CsitxDrv_InstObj *instObj,
                                         Csitx_CreateParams *createParams);

static int32_t CsitxDrv_createChQueues(CsitxDrv_InstObj *instObj);

static int32_t CsitxDrv_setCslCfgParams(CsitxDrv_CommonObj *txObj,
                                        CsitxDrv_InstObj *instObj,
                                        Csitx_CreateParams *createParams);

static int32_t CsitxDrv_configShim(CsitxDrv_CommonObj *txObj,
                                   CsitxDrv_InstObj *instObj);

int32_t Csitx_setDphyCfg(Csitx_DPhyCfg *dphyCfg);

static void CsitxDrv_deleteChObj(CsitxDrv_InstObj *instObj);

static void CsitxDrv_deleteChQueues(CsitxDrv_ChObj *chObj);

static int32_t CsitxDrv_startIoctl(CsitxDrv_InstObj *instObj);

static int32_t CsitxDrv_stopIoctl(CsitxDrv_InstObj *instObj);

void Csitx_printLogs(void);

static int32_t CsitxDrv_getStatusIoctl(CsitxDrv_InstObj *instObj,
                                       Csitx_InstStatus *txStat);

/* This function returns the size aligned to wordSize boundary
   e.g. sizeInBits = 60 bits , wordSize = 32 bits, output is 2 words */
static uint32_t CsitxDrv_getSizeInWords(uint32_t sizeInBits,
                                        uint32_t wordSizeInBits);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Fdrv_Handle CsitxDrv_create(uint32_t drvId,
                            uint32_t instId,
                            void *createArgs,
                            void *createStatusArgs,
                            const Fvid2_DrvCbParams *fdmCbParams)
{
    Fdrv_Handle drvHandle = NULL;
    int32_t retVal = FVID2_SOK;
    CsitxDrv_CommonObj *txObj;
    CsitxDrv_InstObj *instObj = NULL;
    Csitx_CreateParams *createParams;
    Csitx_CreateStatus *status;
    uint32_t eventIdx;

    /* Check for NULL pointers and invalid arguments */
    if ((createArgs == NULL) ||
        (createStatusArgs == NULL) ||
        (fdmCbParams == NULL) ||
        (drvId != CSITX_TX_DRV_ID))
    {
        GT_0trace(CsitxTrace, GT_ERR, "Invalid arguments\r\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        txObj = &gCsitxCommonObj;
        status = (Csitx_CreateStatus *)createStatusArgs;
        createParams = (Csitx_CreateParams *)createArgs;
        /* check if provided instance is free */
        if (txObj->instObj[instId].inUse !=
                                (uint32_t)CSITX_DRV_USAGE_STATUS_NOT_USED)
        {
            GT_0trace(CsitxTrace,
                      GT_ERR,
                      "Provided instance is already in use\r\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
        else
        {
            /* Get the instance object for this instance */
            instObj = &txObj->instObj[instId];
            GT_assert(CsitxTrace, (instObj != NULL));
        }
    }
    /* If the selected instance is IDLE or not */
    if ((retVal == FVID2_SOK) && (instObj->state != CSITX_DRV_STATE_IDLE))
    {
        retVal = FVID2_EFAIL;
        GT_0trace(CsitxTrace,
                  GT_ERR,
                  "Selected instance is not in IDLE state\r\n");
    }

    if (instObj != NULL)
    {
        /* Pend on the instance semaphore */
        (void)SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);
        /* Assert reset to pixel interface */
        CSL_csitxAssertPixelIfReset((CSL_csi_tx_ifRegs *)instObj->shimBaseAddr,
                                    TRUE);
    }

    if (retVal == FVID2_SOK)
    {
        /* Copy createParams to instance object */
        Fvid2Utils_memcpy(&instObj->createParams,
                          createParams,
                          sizeof (instObj->createParams));
        /* Initialize instance configuration parameters */
        instObj->drvInstId = instId;
        instObj->inUse = (uint32_t)CSITX_DRV_USAGE_STATUS_IN_USE;
        Fvid2Utils_memcpy(&instObj->fdmCbParams,
                          fdmCbParams,
                          sizeof (instObj->fdmCbParams));
        /* Create done Queue */
        retVal = Fvid2Utils_constructQ(&instObj->bufManObj.doneLlObj);
        GT_assert(CsitxTrace, (retVal == FVID2_SOK));
        instObj->bufManObj.doneQ = &instObj->bufManObj.doneLlObj;
        if (gCsitxCommonObj.platData.serialMultiChanEnable ==
                    CSITX_ENABLE_SERIAL_TRANS_ENABLE)
        {
            /* Create wait Queue */
            retVal += Fvid2Utils_constructQ(&instObj->bufManObj.waitLlObj);
            GT_assert(CsitxTrace, (retVal == FVID2_SOK));
            instObj->bufManObj.waitQ = &instObj->bufManObj.waitLlObj;
        }
    }
    /* Call this API before configuration of SHIM/UDMA as some of variables are
       set in this function which will be used in 'CsitxDrv_setUdmaParams()' */
    if (retVal == FVID2_SOK)
    {
        /* Set CSITX Module configuration parameters */
        retVal = CsitxDrv_setCslCfgParams(txObj,
                                          instObj,
                                          &instObj->createParams);
    }
    if (retVal == FVID2_SOK)
    {
        /* Set SHIL/PSIL, UDMA configuration parameters */
        retVal = CsitxDrv_setInstCfgParams(instObj, &instObj->createParams);
    }
    if (retVal == FVID2_SOK)
    {
        /* Configure UDMA */
        retVal = CsitxDrv_setUdmaParams(txObj, instObj);
    }
    if (retVal == FVID2_SOK)
    {
        /* Set CSITX Module configuration parameters */
        retVal = CsitxDrv_createChQueues(instObj);
    }
    if (retVal == FVID2_SOK)
    {
        /* Copy Csitx_DPhyCfg to instance object */
        Fvid2Utils_memcpy(&instObj->dphyCfg,
                          &createParams->instCfg.dphyCfg,
                          sizeof (instObj->dphyCfg));
        /* Configure DPHY */
        retVal = Csitx_setDphyCfg(&instObj->dphyCfg);
    }
    if (retVal == FVID2_SOK)
    {
        /* Set SHIM- CSITX Module configuration parameters */
        retVal = CsitxDrv_configShim(txObj, instObj);
    }

    if (retVal == FVID2_SOK)
    {
        for (eventIdx = 0U ;
             eventIdx < CSITX_EVENT_GROUP_MAX;
             eventIdx++)

        {
            /* Initialize event configuration parameters */
            retVal = CsitxDrv_eventGroupRegister(instObj,
                    &instObj->createParams.instCfg.eventParams[eventIdx]);
        }
    }

    if (retVal != FVID2_SOK)
    {
        if (instObj != NULL)
        {
            /* De-assert reset to pixel interface in case of failure.
               In normal scenario, this will de-asserted in Fvid_start() call */
            CSL_csitxAssertPixelIfReset((CSL_csi_tx_ifRegs *)instObj->shimBaseAddr,
                                        FALSE);
            GT_0trace(CsitxTrace,
                      GT_ERR,
                      "Instance create failed!!!\r\n");
        }
    }

    if (retVal == FVID2_SOK)
    {
        instObj->state = CSITX_DRV_STATE_CREATED;
        drvHandle = instObj;
        status->retVal = retVal;
    }
    else
    {
        if (createStatusArgs != NULL)
        {
            status = (Csitx_CreateStatus *)createStatusArgs;
            status->retVal = retVal;
        }
        if (instObj != NULL)
        {
            /* Deallocate if error occurs */
            CsitxDrv_deleteChObj(instObj);
        }
        GT_0trace(CsitxTrace,
                  GT_ERR,
                  "Create failed for given configuration\r\n");
    }
    if (instObj != NULL)
    {
        /* Post the instance semaphore */
        SemaphoreP_post(&instObj->lockSem);
    }

#if (CSITX_DRV_ENABLE_DEBUG == 1U)
    /* Initialize Log Data */
    uint32_t loopCnt;

    if (retVal == FVID2_SOK)
    {
        gCsitxCommonObj.frmCnt = 0U;
        gCsitxCommonObj.frmCntOverflow = 0U;
        for (loopCnt = 0U ; loopCnt < CSITX_DRV_LOG_CNT ; loopCnt++)
        {
            gCsitxCommonObj.frmStatus[loopCnt] = 0U;
            gCsitxCommonObj.frmType[loopCnt]   = 0U;
            gCsitxCommonObj.trResp[loopCnt]    = 0U;
            gCsitxCommonObj.frmTS[loopCnt]     = 0U;
            gCsitxCommonObj.frmChId[loopCnt]   = 0U;
            gCsitxCommonObj.frmInstId[loopCnt] = 0U;
        }
    }
#endif

    return drvHandle;
}

int32_t CsitxDrv_control(Fdrv_Handle handle,
                         uint32_t cmd,
                         void *cmdArgs,
                         void *cmdStatusArgs)
{
    int32_t retVal = FVID2_SOK;
    CsitxDrv_InstObj *instObj;
    Fvid2_TimeStampParams *tsParams;

    /* Check for NULL pointers */
    if (handle == NULL)
    {
        GT_0trace(CsitxTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        instObj = (CsitxDrv_InstObj *) handle;
        switch (cmd)
        {
            case FVID2_START:
                retVal = CsitxDrv_startIoctl(instObj);
            break;
            case FVID2_STOP:
                retVal = CsitxDrv_stopIoctl(instObj);
            break;
            case IOCTL_CSITX_GET_INST_STATUS:
                retVal = CsitxDrv_getStatusIoctl(
                                    instObj,
                                    (Csitx_InstStatus *)cmdArgs);
            break;
            case IOCTL_CSITX_PRINT_DEBUG_LOGS:
                retVal = FVID2_SOK;
                Csitx_printLogs();
            break;
            case FVID2_REGISTER_TIMESTAMP_FXN:
                tsParams = (Fvid2_TimeStampParams *)cmdArgs;
                gCsitxCommonObj.getTimeStamp = tsParams->timeStampFxn;
            break;
            default:
            {
                GT_0trace(CsitxTrace, GT_ERR,
                            "UNSUPPORTED_CMD: IOCTL not supported\r\n");
                retVal = FVID2_EUNSUPPORTED_CMD;
            }
        }
    }

    return retVal;
}

int32_t CsitxDrv_delete(Fdrv_Handle handle, void *reserved)
{
    int32_t retVal = FVID2_SOK;
    CsitxDrv_InstObj *instObj = NULL;
    uint32_t eventIdx;

    /* Check for NULL pointers and invalid arguments */
    if (handle == NULL)
    {
        GT_0trace(CsitxTrace, GT_ERR, "Invalid arguments\r\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        instObj = (CsitxDrv_InstObj *) handle;
    }

    if (instObj != NULL)
    {
        /* Pend on the instance semaphore */
        (void)SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

        /* Check if the instance is already opened and in a stopped state */
        if ((instObj->state == CSITX_DRV_STATE_STOPPED) ||
            (instObj->state == CSITX_DRV_STATE_CREATED))
        {
            /* Un-register events if any */
            if (retVal == FVID2_SOK)
            {
                for (eventIdx = 0U ;
                     eventIdx < CSITX_EVENT_GROUP_MAX;
                     eventIdx++)
                {
                    /* Initialize event configuration parameters */
                    retVal = CsitxDrv_eventGroupUnRegister(instObj,
                            instObj->createParams.instCfg.eventParams[eventIdx].eventGroup);
                }
            }
            CsitxDrv_deleteChObj(instObj);

            if (instObj->bufManObj.doneQ !=  NULL)
            {
                /* Delete the done Q */
                Fvid2Utils_destructQ(instObj->bufManObj.doneQ);
                instObj->bufManObj.doneQ = NULL;
            }
            if (gCsitxCommonObj.platData.serialMultiChanEnable ==
                    CSITX_ENABLE_SERIAL_TRANS_ENABLE)
            {
                if (instObj->bufManObj.waitQ !=  NULL)
                {
                    /* Delete the free Q */
                    Fvid2Utils_destructQ(instObj->bufManObj.waitQ);
                    instObj->bufManObj.waitQ = NULL;
                }
            }

            /* Mark state as idle */
            instObj->state = CSITX_DRV_STATE_IDLE;

            /* Mark as not in use */
            instObj->inUse = (uint32_t)CSITX_DRV_USAGE_STATUS_NOT_USED;

            /* Reset all channel numbers */
            instObj->numTxCh        = 0U;
            instObj->numColorbarCh  = 0U;
            instObj->numLpbkCh      = 0U;
        }
        else
        {
            GT_0trace(
                CsitxTrace, GT_ERR,
                "Driver not in a state to delete. Try stopping it!!\r\n");
            retVal = FVID2_EFAIL;
        }
        /* Post the instance semaphore */
        SemaphoreP_post(&instObj->lockSem);
    }

    return retVal;
}

int32_t CsitxDrv_queue(Fdrv_Handle handle,
                       Fvid2_FrameList *frmList,
                       uint32_t streamId)
{
    int32_t retVal = FVID2_SOK, tempVal = UDMA_SOK;
    CsitxDrv_InstObj *instObj;
    CsitxDrv_ChObj *chObj;
    uint32_t frmCnt = 0U, chIdx, cookie;
    Fvid2_Frame *frm;
    CSL_UdmapTR1 *pTr;
    CsitxDrv_QueObj *qObj;
    /* Check for NULL pointers */
    if((NULL == handle) || (NULL == frmList))
    {
        GT_0trace(CsitxTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }
    if(retVal == FVID2_SOK)
    {
        instObj = (CsitxDrv_InstObj *)handle;
        retVal = Fvid2_checkFrameList(frmList, (uint32_t) FVID2_MAX_FRAME_PTR);
        if (retVal != FVID2_SOK)
        {
            GT_0trace(CsitxTrace, GT_ERR, "Check frame list error\n");
        }
        if (instObj->state == CSITX_DRV_STATE_IDLE)
        {
            /* If driver handle is not open then skip this frame queue */
            GT_0trace(
                CsitxTrace, GT_ERR,
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
            chIdx = frm->chNum;
            if (chIdx >= instObj->createParams.numCh)
            {
                /* invalid stream ID skip this frame queue */
                GT_0trace(CsitxTrace, GT_ERR, "Invalid Channel ID\r\n");
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
                 (CsitxDrv_QueObj *) Fvid2Utils_dequeue(chObj->bufManObj.freeQ);
                if (qObj == NULL)
                {
                    GT_0trace(
                        CsitxTrace, GT_ERR,
                        "ALLOC: Q object allocation failed\r\n");
                    retVal = FVID2_EALLOC;
                }
            }
            if(retVal == FVID2_SOK)
            {
                if (gCsitxCommonObj.platData.serialMultiChanEnable ==
                    CSITX_ENABLE_SERIAL_TRANS_ENABLE)
                {
                    qObj->chObj = chObj;
                }
                /* Copy the frame to the driver's queue object */
                qObj->frm = frm;
                /* Update TR packet descriptor for given Frame */
                pTr = UdmaUtils_getTrpdTr1Pointer((uint8_t *)qObj->trpd, 0U);
                pTr->addr = qObj->frm->addr[0U];
                /* Submit TR to FQ ring for UDMA channel */
                /* Writeback cache */
                CsitxDrv_cacheWb(qObj->trpd,
                                 CSITX_DRV_TRPD_SIZE_ALIGN);
                /* Submit TRPD to channel */
#if (CSITX_DRV_ENABLE_DEBUG == 1U)
                {
                    gTxTrSubmit[gTxTrSubmitCnt][0U] = (uint32_t)qObj->trpd;
                    gTxTrSubmit[gTxTrSubmitCnt][1U] = chIdx;
                    if (gCsitxCommonObj.getTimeStamp != NULL)
                    {
                        gTxTrSubmit[gTxTrSubmitCnt][2U] =
                                        (uint32_t)gCsitxCommonObj.getTimeStamp(NULL);;
                    }
                    else
                    {
                        gTxTrSubmit[gTxTrSubmitCnt][2U] = 0U;
                    }
                    gTxTrSubmitCnt = (gTxTrSubmitCnt + 1U) % CSITX_DRV_TR_LOG_CNT;
                    CsitxDrv_cacheWb(&gTxTrSubmit[0U],
                                     sizeof(gTxTrSubmit));
                }
#endif
                if (gCsitxCommonObj.platData.serialMultiChanEnable ==
                    CSITX_ENABLE_SERIAL_TRANS_DISABLE)
                {
                    /* put lanes into LP state if clock mode is non continuous */
                    if ((retVal == FVID2_SOK) &&
                        (instObj->dphyCfg.clkMode == CSITX_CLK_MODE_NON_CONTINUOUS))
                    {
                        retVal = CsitxDrv_dphytxSetLaneState(instObj, CSITX_DPHY_MODE_HIGH_SPEED);
                    }
                    tempVal = Udma_ringQueueRaw(
                        Udma_chGetFqRingHandle(&chObj->txChObj),
                        (uint64_t)qObj->trpd);
                    if(tempVal != UDMA_SOK)
                    {
                        GT_0trace(
                            CsitxTrace, GT_ERR,
                            "Queue: Submitting of TR failed\r\n");
                        /* Queue back the Object which was
                           de-queued earlier from freeQ */
                        Fvid2Utils_queue(chObj->bufManObj.freeQ, &qObj->qElem, qObj);
                        retVal = FVID2_EFAIL;
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
                if (gCsitxCommonObj.platData.serialMultiChanEnable ==
                    CSITX_ENABLE_SERIAL_TRANS_ENABLE)
                {
                    /* Add the queue object in driver's waiting queue */
                    Fvid2Utils_queue(instObj->bufManObj.waitQ, &qObj->qElem, qObj);
                    instObj->status.queueCount[chIdx]++;
                }
            }
        }
        if (gCsitxCommonObj.platData.serialMultiChanEnable ==
                                CSITX_ENABLE_SERIAL_TRANS_ENABLE)
        {
            if(retVal == FVID2_SOK)
            {
                /* Check if no frames are current being queue to UDMA channels.
                   If not, submit a frame to UDMA channel */
                if (instObj->bufManObj.curFrmNum == 0U)
                {
                    /* Take a object from waiting Q and put in respective channel's
                       curQ (submit the same to UDMA) */
                    qObj =
                     (CsitxDrv_QueObj *) Fvid2Utils_dequeue(instObj->bufManObj.waitQ);
                    if (qObj == NULL)
                    {
                        GT_0trace(
                            CsitxTrace, GT_ERR,
                            "ALLOC: Q object allocation failed\r\n");
                        retVal = FVID2_EALLOC;
                    }
                    else
                    {
                        /* Submit it to respective channel's curQ */
                        chObj = qObj->chObj;
                        /* put lanes into LP state if clock mode is non continuous */
                        if ((retVal == FVID2_SOK) &&
                            (instObj->dphyCfg.clkMode ==
                                            CSITX_CLK_MODE_NON_CONTINUOUS))
                        {
                            retVal =
                                CsitxDrv_dphytxSetLaneState(instObj,
                                                CSITX_DPHY_MODE_HIGH_SPEED);
                        }
                        tempVal = Udma_ringQueueRaw(
                            Udma_chGetFqRingHandle(&chObj->txChObj),
                            (uint64_t)qObj->trpd);
                        if(tempVal != UDMA_SOK)
                        {
                            GT_0trace(
                                CsitxTrace, GT_ERR,
                                "Queue: Submitting of TR failed\r\n");
                            /* Queue back the Object which was
                               de-queued earlier from waitQ */
                            Fvid2Utils_queue(instObj->bufManObj.waitQ, &qObj->qElem, qObj);
                            retVal = FVID2_EFAIL;
                        }
                        else
                        {
                            /* Add the queue object in driver's current queue */
                            Fvid2Utils_queue(chObj->bufManObj.curQ, &qObj->qElem, qObj);
                            /* Mark frame in frmList as NULL */
                            frmList->frames[frmCnt] = NULL;
                            instObj->bufManObj.curFrmNum++;
                        }
                    }
                }
            }
        }
        /* Enable HW interrupts here */
        HwiP_restore(cookie);
    }

    return retVal;
}

int32_t CsitxDrv_dequeue(Fdrv_Handle handle,
                         Fvid2_FrameList *frmList,
                         uint32_t streamId,
                         uint32_t timeout)
{
    int32_t retVal = FVID2_SOK,tempRetVal = UDMA_SOK;
    CsitxDrv_InstObj *instObj;
    CsitxDrv_ChObj *chObj;
    uint32_t chIdx, cookie;
    volatile uint32_t loopBreakFlag = 1U;
    CsitxDrv_QueObj *qObj;
    uint64_t pDesc;

    /* Check for NULL pointers */
    if((handle == NULL) ||
        (frmList == NULL))
    {
        GT_0trace(CsitxTrace, GT_ERR, "Invalid argument!!\r\n");
        retVal = FVID2_EBADARGS;
    }
    if(retVal == FVID2_SOK)
    {
        instObj = (CsitxDrv_InstObj *) handle;
        if (instObj->state == CSITX_DRV_STATE_IDLE)
        {
            GT_0trace(
                CsitxTrace, GT_ERR,
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

        loopBreakFlag = 1U;
        /* Extract done frames from queue till the queue
         * is empty or framelist runs out of space!! */
        do
        {
            qObj = (CsitxDrv_QueObj *) Fvid2Utils_dequeue(instObj->bufManObj.doneQ);
            if (qObj != NULL)
            {
                GT_assert(CsitxTrace, (qObj->chObj != NULL));
                chObj = qObj->chObj;
                GT_assert(CsitxTrace, (qObj->frm != NULL));
                frmList->frames[frmList->numFrames] = qObj->frm;
                frmList->numFrames++;
                instObj->status.dequeueCount[chObj->chCfg->chId]++;

                /* Give back the queue object back to the free pool */
                qObj->frm = NULL;

                Fvid2Utils_queue(chObj->bufManObj.freeQ, &qObj->qElem, qObj);
            }
             /* Max frames limit exceeded exit */
            if ((frmList->numFrames >= FVID2_MAX_FRAME_PTR) ||
                (qObj == NULL))
            {
                loopBreakFlag = 0U;
            }

        } while(loopBreakFlag == 1U);
    }
    /* If no frame is dequeued, then check if we could return frames from input
     * and current queue for stopped instances */
    if (retVal == FVID2_SOK)
    {
        /* When an instance is stopped, return all the request in
         * channel's current queue as well. */
        GT_assert(CsitxTrace, (instObj != NULL));
        if (instObj->state == CSITX_DRV_STATE_STOPPED)
        {
            for (chIdx = 0U ; chIdx < instObj->createParams.numCh ; chIdx++)
            {
                chObj = &instObj->chObj[chIdx];
                if (chObj->chCfg->chType == CSITX_CH_TYPE_TX)
                {
                    /* Extract frames from queue till the queue
                     * is empty or frame list runs out of space!! */
                    while (1)
                    {
                        /* At this point only TRPDs should only be available in
                           FQ Ring of UDMA since all UDMA channels are
                           stopped */
                        /* Flush any pending request from the free queue */
                        tempRetVal = Udma_ringFlushRaw(
                                        Udma_chGetFqRingHandle(&chObj->txChObj),
                                        &pDesc);
                        if(UDMA_ETIMEOUT == tempRetVal)
                        {
                            break;
                        }
                        /* Give the buffers in current state */
                        qObj = (CsitxDrv_QueObj *)
                               Fvid2Utils_dequeue(chObj->bufManObj.curQ);
                        GT_assert(CsitxTrace, (qObj != NULL));
                        GT_assert(CsitxTrace,
                            (chObj->chCfg->chId == qObj->chObj->chCfg->chId));
                        /* Check returned descriptor pointer */
                        GT_assert(CsitxTrace,
                                  (pDesc == ((uint64_t) qObj->trpd)));
                        GT_assert(CsitxTrace, (qObj->frm != NULL));
                        instObj->bufManObj.curFrmNum--;
                        qObj->frm->status = FVID2_FRAME_STATUS_ABORTED;
                        frmList->frames[frmList->numFrames] = qObj->frm;
                        frmList->numFrames++;
                        instObj->status.dequeueCount[chObj->chCfg->chId]++;
                        /* Give back the queue object back to the free pool */
                        qObj->frm = NULL;
                        GT_assert(CsitxTrace, (chObj == qObj->chObj));
                        Fvid2Utils_queue(chObj->bufManObj.freeQ,
                                         &qObj->qElem,
                                         qObj);
                        /* Max frames limit exceeded exit or no more frames for this
                         * channel, continue with next channel */
                        if ((frmList->numFrames >= FVID2_MAX_FRAME_PTR) ||
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
                    chObj->status = CSITX_DRV_CH_STATE_STOPPED;
                }
            }
            if (gCsitxCommonObj.platData.serialMultiChanEnable ==
                    CSITX_ENABLE_SERIAL_TRANS_ENABLE)
            {
                /* Empty up waiting queue */
                loopBreakFlag = 1U;
                do
                {
                    qObj = (CsitxDrv_QueObj *) Fvid2Utils_dequeue(instObj->bufManObj.waitQ);
                    if (qObj != NULL)
                    {
                        GT_assert(CsitxTrace, (qObj->chObj != NULL));
                        chObj = qObj->chObj;
                        GT_assert(CsitxTrace, (qObj->frm != NULL));
                        frmList->frames[frmList->numFrames] = qObj->frm;
                        frmList->numFrames++;
                        instObj->status.dequeueCount[chObj->chCfg->chId]++;

                        qObj->frm = NULL;

                        /* Give back the queue object back to the free pool */
                        Fvid2Utils_queue(chObj->bufManObj.freeQ, &qObj->qElem, qObj);
                        /* Max frames limit exceeded exit */
                        if (frmList->numFrames >= FVID2_MAX_FRAME_PTR)
                        {
                            loopBreakFlag = 0U;
                        }
                    }
                    else
                    {
                        loopBreakFlag = 0U;
                    }
                } while(loopBreakFlag == 1U);
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
            if ((instObj->state == CSITX_DRV_STATE_CREATED) ||
                (instObj->state == CSITX_DRV_STATE_STOPPED))
            {
                GT_0trace(
                    CsitxTrace, GT_DEBUG,
                    "NO_MORE_BUFFERS: No more buffers with driver\n");
                retVal = FVID2_ENO_MORE_BUFFERS;
            }
            else
            {
                GT_0trace(
                    CsitxTrace, GT_DEBUG,
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
/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static int32_t CsitxDrv_setInstCfgParams(CsitxDrv_InstObj *instObj,
                                         Csitx_CreateParams *createParams)
{
    int32_t retVal = FVID2_SOK;
    uint32_t chNum, psilThreadId = 0U;
    for (chNum = 0U ; chNum < createParams->numCh ; chNum++)
    {
        if (psilThreadId >= CSITX_NUM_CH_TX)
        {
            GT_0trace(
                CsitxTrace,
                GT_ERR,
                "More Capture channels are provided than HW can process\r\n");
            retVal = FVID2_EINVALID_PARAMS;
            break;
        }
        else
        {
            instObj->chObj[chNum].chCfg = &createParams->chCfg[chNum];
            if (createParams->chCfg[chNum].chType == CSITX_CH_TYPE_TX)
            {
                if (instObj->numTxCh < CSITX_NUM_CH_TX)
                {
                    instObj->chObj[chNum].psilThreadId = psilThreadId;
                    psilThreadId++;
                    instObj->numTxCh++;
                    retVal = CsitxDrv_setDMACfgParams(&instObj->chObj[chNum]);
                }
                else
                {
                    GT_0trace(
                        CsitxTrace,
                        GT_ERR,
                        "More Capture channels are provided than HW "
                        "can process\r\n");
                    retVal = FVID2_EINVALID_PARAMS;
                    break;
                }
            }
            if (createParams->chCfg[chNum].chType == CSITX_CH_TYPE_COLORBAR)
            {
                if (instObj->numColorbarCh < CSITX_NUM_CH_COLORBAR_MAX)
                {
                    instObj->colorbarChId[instObj->numColorbarCh] = chNum;
                    instObj->numColorbarCh++;
                }
                else
                {
                    GT_0trace(
                        CsitxTrace,
                        GT_ERR,
                        "More OTF channels are provided than HW can "
                        "process\r\n");
                    retVal = FVID2_EINVALID_PARAMS;
                    break;
                }
            }
            if (createParams->chCfg[chNum].chType == CSITX_CH_TYPE_LPBK)
            {
                if (instObj->numLpbkCh < CSITX_NUM_CH_LPBK_MAX)
                {
                    instObj->lpbkChId[instObj->numLpbkCh] = chNum;
                    instObj->numLpbkCh++;
                    CSL_csitxRetransCfg((CSL_csi_tx_ifRegs *)instObj->shimBaseAddr,
                                        &createParams->instCfg.retransCfg);
                    retVal = CsirtxDrv_lpbkSel(instObj->drvInstId, createParams->instCfg.lpbkCsiRxInst);
                }
                else
                {
                    GT_0trace(
                        CsitxTrace,
                        GT_ERR,
                        "More Loop-back channels are provided than "
                        "HW can process\r\n");
                    retVal = FVID2_EINVALID_PARAMS;
                    break;
                }
            }
        }
    }

    return retVal;
}

static int32_t CsitxDrv_createChQueues(CsitxDrv_InstObj *instObj)
{
    int32_t  retVal = FVID2_SOK, tempRetVal;
    uint32_t chIdx = 0U;
    uint32_t qCnt = 0U;
    CsitxDrv_QueObj *qObj;
    CsitxDrv_ChObj *chObj;
    CsitxDrv_ChBufManObj *bmObj;
    CsitxDrv_InstBufManObj *instBmObj;

    /* NULL pointer check */
    GT_assert(CsitxTrace, (NULL != instObj));
    for (chIdx = 0U ; chIdx < instObj->createParams.numCh ; chIdx++)
    {
        chObj = &instObj->chObj[chIdx];
        /* Do configuration for CSITX_CH_TYPE_TX type of channel */
        if (chObj->chCfg->chType == CSITX_CH_TYPE_TX)
        {
            bmObj = &chObj->bufManObj;

            bmObj->freeQ         = NULL;
            /* Create Queues */
            retVal = Fvid2Utils_constructQ(&bmObj->freeLlObj);
            GT_assert(CsitxTrace, (retVal == FVID2_SOK));
            bmObj->freeQ = &bmObj->freeLlObj;

            bmObj->curQ          = NULL;
            retVal = Fvid2Utils_constructQ(&bmObj->curLlObj);
            GT_assert(CsitxTrace, (retVal == FVID2_SOK));
            bmObj->curQ = &bmObj->curLlObj;
            instBmObj = &instObj->bufManObj;
            /* Initialize and queue the allocate queue object to free Q */
            for (qCnt = 0U; qCnt < CSITX_TX_QUEUE_DEPTH_PER_CH ; qCnt++)
            {
                if (gCsitxCommonObj.platData.serialMultiChanEnable ==
                                CSITX_ENABLE_SERIAL_TRANS_DISABLE)
                {
                    qObj = &bmObj->txQObj[qCnt];
                }
                else
                {
                    qObj = &instBmObj->txQObj[((chIdx * CSITX_TX_QUEUE_DEPTH_PER_CH) + qCnt)];
                }
                qObj->inUse = CSITX_DRV_USAGE_STATUS_NOT_USED;
                qObj->chObj = &instObj->chObj[chIdx];
                qObj->frm   = NULL;
                qObj->trpd =
                        (CSL_UdmapCppi5TRPD *)CsitxDrv_getTrpdMemAddr(chIdx,
                                                                      qCnt);
                tempRetVal = CsitxDrv_udmaTxTrpdInit(
                                    &instObj->chObj[chIdx].txChObj,
                                    (uint8_t *)qObj->trpd,
                                    NULL,
                                    instObj->chObj[chIdx].chCfg,
                                    chIdx);
                if (tempRetVal != FVID2_SOK)
                {
                    retVal = FVID2_EINVALID_PARAMS;
                    break;
                }
                Fvid2Utils_queue(bmObj->freeQ, &qObj->qElem, qObj);
            }
            if (retVal != FVID2_SOK)
            {
                break;
            }
        }
    }

    /* Deallocate if error occurs */
    if (retVal != FVID2_SOK)
    {
        for (chIdx = 0U ; chIdx < CSITX_NUM_CH; chIdx++)
        {
            CsitxDrv_deleteChQueues(&instObj->chObj[chIdx]);
        }
    }

    return retVal;
}

static int32_t CsitxDrv_setCslCfgParams(CsitxDrv_CommonObj *txObj,
                                        CsitxDrv_InstObj *instObj,
                                        Csitx_CreateParams *createParams)
{
    int32_t retVal = FVID2_SOK;
    uint32_t status, loopCnt, loopBreakFlag, enable, chIdx, dtIdx;
    uint32_t currTimeout = 0U;
    uint32_t lineSize = 0U;
    CSITX_RxCompatibilityConfig cfg;

    /* TODO: Check for drivers memory requirements, not needed */
    /* Initialize CSI CSL FL object */
    status = CSITX_Init(&instObj->cslObj.cslCfgData,
                        &instObj->cslObj.configParams,
                        &instObj->cslObj.intrCbs);
    if (status != 0U)
    {
        GT_0trace(CsitxTrace,
                  GT_ERR,
                  "CSL FL: Invalid Config Arguments\r\n");
        retVal = FVID2_EBADARGS;
    }
    if (retVal == FVID2_SOK)
    {
        /* Enable Configuration mode */
        if (CSITX_SetConfigurationMode(&instObj->cslObj.cslCfgData,
                                        (uint32_t)TRUE) != 0U)
        {
            retVal = FVID2_EBADARGS;
        }
        else
        {
            currTimeout = 0U;
            /* Wait for controller to enter into configuration mode */
            loopBreakFlag = 0U;
            enable = FALSE;
            while ((loopBreakFlag == 0U) && (enable != TRUE))
            {
                if (CSITX_GetConfigurationMode(&instObj->cslObj.cslCfgData,
                                               &enable) != 0U)
                {
                    loopBreakFlag = 1U;
                    retVal = FVID2_EFAIL;
                }
                /* Time-out logic */
                if(currTimeout > CSITX_TIMEOUT_VAL_MS)
                {
                    loopBreakFlag = 1U;
                    retVal = FVID2_ETIMEOUT;
                    GT_0trace(CsitxTrace,
                        GT_ERR,
                        "CSL FL: Stream set configuration mode timed-out\r\n");
                }
                else
                {
                    ClockP_sleep(1U);
                    currTimeout++;
                }
            }
        }
    }
    if (retVal == FVID2_SOK)
    {
        /* Collect DT cfg from info provided channels */
        for (chIdx = 0U ; chIdx < createParams->numCh ; chIdx++)
        {
            for (dtIdx = 0U ;
                 dtIdx < instObj->cslObj.dtInUse ;
                 dtIdx++)
            {
                if (instObj->cslObj.dtCfg[dtIdx].dataType ==
                                    createParams->chCfg[chIdx].outCsiDataType)
                {
                    break;
                }
            }
            /* let the loop iteration overwrite the lineSize as in case of
               multi-channel, only channels with same frame dimensions are supported.
               Error for the same is reported in the following else statement */
            lineSize = createParams->chCfg[chIdx].inFmt.width *
                       CsitxDrv_getBpp(createParams->chCfg[chIdx].outCsiDataType);
            GT_assert(CsitxTrace, (lineSize != 0U));
            if (dtIdx == instObj->cslObj.dtInUse)
            {
                instObj->cslObj.dtCfg[instObj->cslObj.dtInUse].dataType      =
                                    createParams->chCfg[chIdx].outCsiDataType;
                instObj->cslObj.dtCfg[instObj->cslObj.dtInUse].bytesPerLine =
                    CsitxDrv_getSizeInWords(lineSize, 8U);
                instObj->cslObj.dtCfg[instObj->cslObj.dtInUse].maxLineNumber =
                        createParams->chCfg[chIdx].inFmt.height;
                instObj->cslObj.dtInUse++;
            }
            else
            {
                /* Check if two channels with same DT have different resolutions */
                if ((instObj->cslObj.dtCfg[dtIdx].maxLineNumber ==
                                    createParams->chCfg[chIdx].inFmt.height) &&
                    (instObj->cslObj.dtCfg[dtIdx].bytesPerLine ==
                    (CsitxDrv_getSizeInWords(lineSize, 8U))))
                {
                    /* No need to report error as it matches */
                }
                else
                {
                    retVal = FVID2_EINVALID_PARAMS;
                }
            }
        }
    }
    if (retVal == FVID2_SOK)
    {
        /* Program DT cfgs */
        for (dtIdx = 0U ;
             dtIdx < instObj->cslObj.dtInUse ;
             dtIdx++)
        {
            if (CSITX_SetDataTypeConfig(&instObj->cslObj.cslCfgData,
                                        &instObj->cslObj.dtCfg[dtIdx],
                                        (CSITX_DtNumber)(dtIdx & CSITX_DT7))
                                                    != 0U)
            {
                retVal = FVID2_EFAIL;
                break;
            }
        }
    }
    if (retVal == FVID2_SOK)
    {
        for (loopCnt = 0U ; loopCnt < CSITX_NUM_STREAM ; loopCnt++)
        {
            /* Number of words in a line */
            instObj->cslObj.strmcfg[loopCnt].fillLevel =
                CsitxDrv_getSizeInWords(lineSize, 32U);
            status = CSITX_SetStreamConfig(&instObj->cslObj.cslCfgData,
                                           &instObj->cslObj.strmcfg[loopCnt],
                                           (CSITX_IfNumber) loopCnt);
            if (status != 0U)
            {
                GT_0trace(CsitxTrace,
                        GT_ERR,
                        "CSL FL: Stream configuration failed\r\n");
                retVal = FVID2_EBADARGS;
            }
        }
    }
    if (retVal == FVID2_SOK)
    {
        /* Program Rx compatibility and 1v3 support enable */
        /* Need to set Rx compatibility mode to '1' as per specs */
        cfg.rxCompEnable = 1U;
        cfg.rxMapping    = instObj->createParams.instCfg.rxv1p3MapEnable;
        status = CSITX_SetRxCompatibility(&instObj->cslObj.cslCfgData,
                                          &cfg);

        if (status != 0U)
        {
            GT_0trace(CsitxTrace,
                      GT_ERR,
                      "CSL FL: Rx Compatibilty failed\r\n");
            retVal = FVID2_EBADARGS;
        }
    }
    if (retVal == FVID2_SOK)
    {
        /* Disable Configuration mode */
        if (CSITX_SetConfigurationMode(&instObj->cslObj.cslCfgData,
                                       (uint32_t)FALSE) != 0U)
        {
            retVal = FVID2_EBADARGS;
        }
        else
        {
            /* Wait for controller to exit from configuration mode */
            loopBreakFlag = 0U;
            enable = TRUE;
            currTimeout = 0U;
            while ((loopBreakFlag == 0U) && (enable != FALSE))
            {
                if (CSITX_GetConfigurationMode(&instObj->cslObj.cslCfgData,
                                               &enable) != 0U)
                {
                    loopBreakFlag = 1U;
                    retVal = FVID2_EFAIL;
                }
                /* Time-out logic */
                if(currTimeout > CSITX_TIMEOUT_VAL_MS)
                {
                    loopBreakFlag = 1U;
                    retVal = FVID2_ETIMEOUT;
                    GT_0trace(CsitxTrace,
                        GT_ERR,
                        "CSL FL: Stream set configuration mode timed-out\r\n");
                }
                else
                {
                    ClockP_sleep(1U);
                    currTimeout++;
                }
            }
        }
    }

    return retVal;
}

static int32_t CsitxDrv_configShim(CsitxDrv_CommonObj *txObj,
                                   CsitxDrv_InstObj *instObj)
{
    int32_t retVal = FVID2_SOK, status = CSL_PASS;
    uint32_t chNum;

    for (chNum = 0U ; chNum < instObj->createParams.numCh ; chNum++)
    {
        if (instObj->chObj[chNum].psilThreadId !=
                                        CSITX_DRV_DEF_PSIL_THREAD_ID)
        {
            /* Do following for Capture channels only */
            status+= CSL_csitxConfigDMA(
                            (CSL_csi_tx_ifRegs *)instObj->shimBaseAddr,
                            &instObj->chObj[chNum].dmaCfgParams);
            if (status != CSL_PASS)
            {
                GT_0trace(CsitxTrace,
                          GT_ERR,
                          "Invalid SHIM Capture config arguments\r\n");
                retVal = FVID2_EBADARGS;
                break;
            }
        }
    }

    return retVal;
}

int32_t Csitx_setDphyCfg(Csitx_DPhyCfg *dphyCfg)
{
    int32_t retVal = FVID2_SOK;
    CsitxDrv_InstObj *instObj;

    if (dphyCfg == NULL)
    {
        retVal = FVID2_EBADARGS;
    }
    if (retVal == FVID2_SOK)
    {
        instObj = &gCsitxCommonObj.instObj[dphyCfg->inst];
        retVal = Csitx_dphyConfig(instObj);
    }
    /* put lanes into LP state if clock mode is non continuous */
    if ((retVal == FVID2_SOK) &&
        (dphyCfg->clkMode == CSITX_CLK_MODE_NON_CONTINUOUS))
    {
        retVal = CsitxDrv_dphytxSetLaneState(instObj, CSITX_DPHY_MODE_LOW_POWER);
    }
    if (retVal != FVID2_SOK)
    {
        GT_0trace(CsitxTrace,
                  GT_ERR,
                  "DPHY configuration failed!!!\r\n");
    }

    return retVal;
}

static void CsitxDrv_deleteChObj(CsitxDrv_InstObj *instObj)
{
    int32_t retVal = FVID2_SOK;
    uint32_t chIdx;
    CsitxDrv_ChObj *chObj;

    GT_assert(CsitxTrace, (instObj != NULL));
    GT_assert(CsitxTrace,
              (instObj->createParams.numCh <= CSITX_NUM_CH));
    /* Close sequence for UDMA DRV */
    retVal = CsitxDrv_clearUdmaParams(instObj);
    if (retVal != UDMA_SOK)
    {
        GT_0trace(CsitxTrace,
                  GT_ERR,
                  "[ERROR]UDMA channel close FAILED!!!\r\n");
    }
    for (chIdx = 0U; chIdx < instObj->createParams.numCh; chIdx++)
    {
        /* Get channel object */
        chObj = &instObj->chObj[chIdx];
        /* Delete channel queues */
        CsitxDrv_deleteChQueues(chObj);
    }
}

static void CsitxDrv_deleteChQueues(CsitxDrv_ChObj *chObj)
{
    CsitxDrv_QueObj    *qObj;
    CsitxDrv_ChBufManObj *bmObj;

    /* NULL pointer check */
    GT_assert(CsitxTrace, (chObj != NULL));
    bmObj = &chObj->bufManObj;

    if (bmObj->freeQ != NULL)
    {
        /* Free-up all the queued free queue objects */
        while (1U)
        {
            qObj = (CsitxDrv_QueObj *) Fvid2Utils_dequeue(bmObj->freeQ);
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
}

static int32_t CsitxDrv_startIoctl(CsitxDrv_InstObj *instObj)
{
    int32_t retVal = FVID2_SOK, tempRetVal = UDMA_SOK;
    uint32_t chIdx = 0U;
    CsitxDrv_ChObj *chObj;

    /* Check for NULL pointers */
    GT_assert(CsitxTrace, (instObj != NULL));
    GT_assert(CsitxTrace,
              (instObj->createParams.numCh <= CSITX_NUM_CH));
    /* Pend the instance semaphore */
    (void)SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    for (chIdx = 0U ; chIdx < instObj->createParams.numCh ; chIdx++)
    {
        /* Get channel object */
        chObj = &instObj->chObj[chIdx];
        /* Enable channel only if it is created */
        if (chObj->status == CSITX_DRV_CH_STATE_CREATED)
        {
            /* Enable DMA context for PSIL threads and UDMA channels only
               for capture channels */
            if (chObj->chCfg->chType == CSITX_CH_TYPE_TX)
            {
                if (retVal == FVID2_SOK)
                {
                    /* Enable UDMA channel */
                    tempRetVal = Udma_chEnable(&chObj->txChObj);
                    if(tempRetVal != UDMA_SOK)
                    {
                        retVal = FVID2_EFAIL;
                        GT_0trace(
                                CsitxTrace,
                                GT_ERR,
                                "[ERROR]UDMA TX channel enable FAILED!!!\r\n");
                    }
                }
            }
            if (retVal == FVID2_SOK)
            {
                /* set channel state to running */
                chObj->status = CSITX_DRV_CH_STATE_RUNNING;
            }
        }
    }
    if (retVal == FVID2_SOK)
    {
        /* change driver instance to started/running state */
        instObj->state = CSITX_DRV_STATE_RUNNING;
        /* release pixel reset */
        CSL_csitxAssertPixelIfReset((CSL_csi_tx_ifRegs *)instObj->shimBaseAddr,
                                    FALSE);
    }
    /* Post the instance semaphore */
    SemaphoreP_post(&instObj->lockSem);

    return retVal;
}

static int32_t CsitxDrv_stopIoctl(CsitxDrv_InstObj *instObj)
{
    int32_t retVal = FVID2_SOK, tempRetVal = UDMA_SOK;
    uint32_t chIdx = 0U, cookie;
    CsitxDrv_ChObj *chObj;

    /* Check for NULL pointers */
    GT_assert(CsitxTrace, (instObj != NULL));
    GT_assert(CsitxTrace,
              (instObj->createParams.numCh <= CSITX_NUM_CH));
    /* Pend the instance semaphore */
    (void)SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);
    /* Disable HW interrupts here */
    cookie = HwiP_disable();
    for (chIdx = 0U ; chIdx < instObj->createParams.numCh ; chIdx++)
    {
        /* Get channel object */
        chObj = &instObj->chObj[chIdx];
        /* set channel state to stopping */
        chObj->status = CSITX_DRV_CH_STATE_STOPPING;
        /* Get channel object */
        chObj = &instObj->chObj[chIdx];
        /* Disable DMA context for PSIL threads and UDMA channels only
           for capture channels */
        if (chObj->chCfg->chType == CSITX_CH_TYPE_TX)
        {
            if (retVal == FVID2_SOK)
            {
                /* Disable UDMA channel */
                tempRetVal = Udma_chDisable(&chObj->txChObj,
                                            UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
                if(tempRetVal != UDMA_SOK)
                {
                    retVal = FVID2_EFAIL;
                    GT_0trace(
                            CsitxTrace,
                            GT_ERR,
                            "[ERROR]UDMA TX channel disable FAILED!!!\r\n");
                }
            }
        }
        if (retVal == FVID2_SOK)
        {
            /* set channel state to stopped */
            chObj->status = CSITX_DRV_CH_STATE_STOPPED;
        }
    }
    /* Enable HW interrupts here */
    HwiP_restore(cookie);

    if (retVal == FVID2_SOK)
    {
        /* change driver isntance to stopped state */
        instObj->state = CSITX_DRV_STATE_STOPPED;
    }

    /* Post the instance semaphore */
    SemaphoreP_post(&instObj->lockSem);

    return retVal;
}

static int32_t CsitxDrv_getStatusIoctl(CsitxDrv_InstObj *instObj,
                                       Csitx_InstStatus *txStat)
{
    int32_t retVal = FVID2_SOK;

    /* Pend on the instance semaphore */
    (void)SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);
    /* Copy capture status from DRV object to application provided parameter */
    Fvid2Utils_memcpy(txStat,
                      &instObj->status,
                      sizeof (instObj->status));
    /* Post the instance semaphore */
    SemaphoreP_post(&instObj->lockSem);

    return retVal;
}

void Csitx_printLogs(void)
{
#if (CSITX_DRV_ENABLE_DEBUG == 1U)
    uint32_t frmIdx, loopCnt;

    GT_0trace(CsitxTrace,
              GT_INFO,
              "\n\r=====================================================\r\n");
    GT_0trace(CsitxTrace,
              GT_INFO,
              "::Debug Logs::");
    GT_0trace(CsitxTrace,
              GT_INFO,
              "\n\r=====================================================\r\n");
    if (gCsitxCommonObj.frmCntOverflow == 1U)
    {
        loopCnt = CSITX_DRV_LOG_CNT;
    }
    else
    {
        loopCnt = gCsitxCommonObj.frmCnt;
    }

    for (frmIdx = 0U ;frmIdx < loopCnt ;frmIdx++)
    {
        GT_7trace(CsitxTrace,
                  GT_INFO,
                  "[LOG]Frame: %d | Inst: %d | Ch ID: 0x%x | FRM TYPE: %d | "
                  "FRM Status: 0x%x | TR Resp: 0x%x | TS: %d |\r\n",
                  frmIdx,
                  gCsitxCommonObj.frmInstId[frmIdx],
                  gCsitxCommonObj.frmChId[frmIdx],
                  gCsitxCommonObj.frmType[frmIdx],
                  gCsitxCommonObj.frmStatus[frmIdx],
                  gCsitxCommonObj.trResp[frmIdx],
                  gCsitxCommonObj.frmTS[frmIdx]);
    }
#else
    GT_0trace(CsitxTrace,
              GT_INFO,
              "\n\rDebug Logging is not enabled."
              " Please enable it through 'CSITX_DRV_ENABLE_DEBUG'.\r\n");
#endif
}

uint32_t CsitxDrv_getBpp(uint32_t dt)
{
    uint32_t bpp = 0U, loopCnt;

    for (loopCnt = 0U ;
         loopCnt < (sizeof(gdtInfo) / sizeof(dataTypeInfo)) ;
         loopCnt++)
    {
        if (gdtInfo[loopCnt].dt == dt)
        {
            break;
        }
    }
    if (loopCnt < (sizeof(gdtInfo) / sizeof(dataTypeInfo)))
    {
        bpp = gdtInfo[loopCnt].bpp;
    }

    return bpp;
}

static uint32_t CsitxDrv_getSizeInWords(uint32_t sizeInBits,
                                        uint32_t wordSizeInBits)
{
    uint32_t sizeInWords;

    sizeInWords = (sizeInBits + (wordSizeInBits - 1U));
    sizeInWords /= wordSizeInBits;

    return sizeInWords;
}

uint32_t CsitxDrv_getStorageBpp(uint32_t dt)
{
    uint32_t bpp = 0U, loopCnt;

    for (loopCnt = 0U ;
         loopCnt < (sizeof(gdtInfo) / sizeof(dataTypeInfo)) ;
         loopCnt++)
    {
        if (gdtInfo[loopCnt].dt == dt)
        {
            break;
        }
    }
    if (loopCnt < (sizeof(gdtInfo) / sizeof(dataTypeInfo)))
    {
        bpp = gdtInfo[loopCnt].storageBpp;
    }

    return bpp;
}

int32_t CsitxDrv_dphytxSetLaneState(CsitxDrv_InstObj *instObj,
                                    uint32_t newState)
{
    int32_t retVal = FVID2_SOK;
     CSITX_DphyConfig  cslDphyCfg;

    /* Transition table:
       Transition       Valid/Invalid
       ------------------------------
       LP->ULP          Valid
       ULP->LP          Valid
       LP->HS           Valid
       HS->LP           Valid
       ULP->HS          Invalid
       HS->ULP          Invalid
    */
    switch (newState)
    {
        case CSITX_DPHY_MODE_ULP:
            /* Enter into LP state first, as ULP cannot be
               entered directly from HS */
            /* change lane state to LP first */
            retVal = CsitxDrv_dphytxSetLaneState(instObj,
                                            CSITX_DPHY_MODE_LOW_POWER);
            /* Enter into ULP state */
            CSITX_GetDphyConfig(&instObj->cslObj.cslCfgData,
                                &cslDphyCfg);
            cslDphyCfg.dphyMode = CSITX_DPHY_MODE_ULP;
            CSITX_SetDphyConfig(&instObj->cslObj.cslCfgData,
                                &cslDphyCfg);
        break;
        case CSITX_DPHY_MODE_HIGH_SPEED:
            /* Enter into LP state first, as HS cannot be
               entered directly from ULP */
            /* change lane state to LP first */
            retVal = CsitxDrv_dphytxSetLaneState(instObj,
                                            CSITX_DPHY_MODE_LOW_POWER);
            /* Enter into ULP state */
            CSITX_GetDphyConfig(&instObj->cslObj.cslCfgData,
                                &cslDphyCfg);
            cslDphyCfg.dphyMode = CSITX_DPHY_MODE_HIGH_SPEED;
            CSITX_SetDphyConfig(&instObj->cslObj.cslCfgData,
                                &cslDphyCfg);
        break;
        case CSITX_DPHY_MODE_LOW_POWER:
            /* Enter into LP state directly as there is not prerequisite for this */
            CSITX_GetDphyConfig(&instObj->cslObj.cslCfgData,
                                &cslDphyCfg);
            cslDphyCfg.dphyMode = CSITX_DPHY_MODE_LOW_POWER;
            CSITX_SetDphyConfig(&instObj->cslObj.cslCfgData,
                                &cslDphyCfg);
        break;
        default:
            retVal = FVID2_EFAIL;
        break;
    }

    return retVal;
}
