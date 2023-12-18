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
 *  \file dss_dispPriv.c
 *
 *  \brief File containing the DSS display driver private APIs.
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

static void Dss_dispErrCbFxn(const uint32_t *event,
                             uint32_t numEvents,
                             void *arg);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

Dss_DispDrvCommonObj gDss_DispDrvCommonObj;
Dss_DispDrvInstObj gDss_DispDrvInstObj[CSL_DSS_VID_PIPE_ID_MAX];
Dss_EvtMgrClientInfo gDss_DispEvtMgrClientInfo[DSS_DISP_EVT_MGR_MAX_CLIENTS];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t Dss_dispDrvPrivInit(uint32_t numInst,
                            const Dss_DispDrvInitParams *initParams)
{
    int32_t  retVal = FVID2_SOK;
    int32_t status = SystemP_SUCCESS;
    uint32_t instCnt;
    uint32_t i, eventGroup, numHandle, numEvents, evtMgrId;
    uint32_t enabledEvents[DSS_EVT_MGR_MAX_CLIENT_EVENTS];
    Dss_DispDrvInstObj *instObj;
    Dss_DispDrvCommonObj *pObj;
    Dss_EvtMgrClientInfo *pClientInfo;
    const Dss_DispDrvInitParams *params = initParams;

    /* Check for errors */
    GT_assert(DssTrace, (numInst <= DSS_DISP_INST_MAX));
    GT_assert(DssTrace, (NULL != params));

    /* Initialize common object */
    pObj = &gDss_DispDrvCommonObj;
    Fvid2Utils_memset(pObj, 0U, sizeof (Dss_DispDrvCommonObj));

    /* Initialize instance object members */
    if(numInst > CSL_DSS_VID_PIPE_ID_MAX)
    {
        /* Number of instances exceeds the global variable used to store the
         * instance object */
        GT_0trace(DssTrace,
                  GT_ERR,
                  "Number of instances exceeds the global array size!!\r\n");
        retVal = FVID2_EALLOC;
    }
    else
    {
        pObj->instObj = &gDss_DispDrvInstObj[0];
        Fvid2Utils_memset(pObj->instObj, 0U, sizeof (gDss_DispDrvInstObj));
        for(i=0U; i<DSS_DISP_EVT_MGR_MAX_CLIENTS; i++)
        {
            pClientInfo = &gDss_DispEvtMgrClientInfo[i];
            Fvid2Utils_memset(pClientInfo, 0U, sizeof (Dss_EvtMgrClientInfo));
        }
    }

    if(FVID2_SOK == retVal)
    {
        pObj->numInst = numInst;
        instObj = pObj->instObj;
        for(instCnt=0U; instCnt<numInst; instCnt++)
        {
            /* Copy the information */
            instObj->drvInstId = params->drvInstId;

            /* Allocate instance semaphore */
            status = SemaphoreP_constructBinary(&instObj->lockSem, 1);
            if(status != SystemP_SUCCESS)
            {
                GT_0trace(DssTrace,
                          GT_ERR,
                          "Instance semaphore create failed!!\r\n");
                retVal = FVID2_EALLOC;
                break;
            }

            if(FVID2_SOK == retVal)
            {
                Dss_convModuletoEventGroup(&eventGroup,
                                           instObj->drvInstId,
                                           DSS_EVENT_GROUP_TYPE_PIPE);
                GT_assert(DssTrace, (DSS_EVENT_GROUP_INVALID != eventGroup));

                /* Register functional events */
                Dss_getEnabledPipeErrEvents(&enabledEvents[0U], &numEvents);
                evtMgrId = Dss_getEvtMgrFuncIntrId();
                numHandle = instObj->numRegEvtHandle;
                instObj->evtGroupHandle[instObj->numRegEvtHandle] =
                            Dss_evtMgrRegister(
                                evtMgrId,
                                eventGroup,
                                (const uint32_t *)&enabledEvents[0U],
                                numEvents,
                                Dss_dispErrCbFxn,
                                (void *)&gDss_DispEvtMgrClientInfo[(instObj->drvInstId*DSS_DISP_INST_EVT_MGR_MAX_CLIENTS) + numHandle]);//todo: Check for this, one more place like this exists.
                instObj->numRegEvtHandle++;
            }

            instObj->drvState.isInit     = TRUE;
            instObj->drvState.isOpened   = FALSE;
            instObj->drvState.isStarted  = FALSE;
            instObj->drvState.isStarting = FALSE;
            instObj->drvState.isStopping = FALSE;

            params++;
            instObj++;
        }
    }

    if(FVID2_SOK != retVal)
    {
        /* Un initialize the internal objects if error occurs */
        retVal += Dss_dispDrvPrivDeInit();
    }

    return (retVal);
}

int32_t Dss_dispDrvPrivDeInit(void)
{
    int32_t retVal = FVID2_SOK;
    uint32_t instCnt, cnt, numRegEvtHandle;
    Dss_DispDrvInstObj *instObj;
    Dss_DispDrvCommonObj *pObj;

    pObj = &gDss_DispDrvCommonObj;
    if(NULL != pObj->instObj)
    {
        instObj = pObj->instObj;
        for(instCnt=0U; instCnt<pObj->numInst; instCnt++)
        {
            if(TRUE == instObj->drvState.isOpened)
            {
                GT_0trace(DssTrace, GT_ERR,
                          "Can't de-initialize when an instance is active\r\n");
                retVal = FVID2_EFAIL;
                break;
            }

            /* Delete the instance semaphore */
            SemaphoreP_destruct(&instObj->lockSem);

            instObj->drvState.isInit = FALSE;
            numRegEvtHandle = instObj->numRegEvtHandle;
            /* Unregister event groups and delete object */
            for(cnt=0U; cnt<numRegEvtHandle; cnt++)
            {
                retVal += Dss_evtMgrUnRegister(instObj->evtGroupHandle[cnt]);
                instObj->numRegEvtHandle--;
            }
            Fvid2Utils_memset(pObj->instObj, 0U, sizeof (Dss_DispDrvInstObj));

            instObj++;
        }
        if(retVal == FVID2_SOK)
        {
            pObj->instObj = NULL;
            pObj->numInst = 0U;
        }
    }
    return (retVal);
}

Dss_DispDrvInstObj *Dss_dispDrvGetInstObj(uint32_t instId)
{
    uint32_t instCnt;
    Dss_DispDrvInstObj *instObj = NULL;
    Dss_DispDrvCommonObj *pObj;

    /* Find out the instance */
    pObj = &gDss_DispDrvCommonObj;
    GT_assert(DssTrace, (NULL != pObj));
    GT_assert(DssTrace, (NULL != pObj->instObj));
    for(instCnt=0U; instCnt<pObj->numInst; instCnt++)
    {
        if((TRUE == pObj->instObj[instCnt].drvState.isInit) &&
           (pObj->instObj[instCnt].drvInstId == instId))
        {
            instObj = &pObj->instObj[instCnt];
            break;
        }
    }

    return (instObj);
}

int32_t Dss_dispDrvCreateInstObj(Dss_DispDrvInstObj *instObj)
{
    int32_t  retVal = FVID2_SOK, tempRetVal;
    uint32_t qCnt;
    Dss_DispDrvBufManObj *bmObj;
    Dss_DispDrvQueObj *qObj;

    GT_assert(DssTrace, (NULL != instObj));
    bmObj = &instObj->bmObj;

    instObj->bufPrgmCbParams.bufPrgmCbFxn = NULL;
    instObj->currStatus.queueCount = 0U;
    instObj->currStatus.dequeueCount = 0U;
    instObj->currStatus.dispFrmCount = 0U;
    instObj->currStatus.repeatFrmCount = 0U;
    instObj->currStatus.underflowCount = 0U;
    instObj->currStatus.safetyViolationCount = 0U;

    bmObj->isProgressive = TRUE;
    bmObj->curFid = 0U;
    bmObj->expectedFid = 0U;
    bmObj->fieldMerged = TRUE;
    bmObj->freeQ = NULL;
    bmObj->reqQ = NULL;
    bmObj->currQ = NULL;
    bmObj->doneQ = NULL;

    /* Create Queues */
    retVal = Fvid2Utils_constructQ(&bmObj->freeLlObj);
    GT_assert(DssTrace, (retVal == FVID2_SOK));
    bmObj->freeQ = &bmObj->freeLlObj;

    retVal = Fvid2Utils_constructQ(&bmObj->reqLlObj);
    GT_assert(DssTrace, (retVal == FVID2_SOK));
    bmObj->reqQ = &bmObj->reqLlObj;

    retVal = Fvid2Utils_constructQ(&bmObj->curLlObj);
    GT_assert(DssTrace, (retVal == FVID2_SOK));
    bmObj->currQ = &bmObj->curLlObj;

    retVal = Fvid2Utils_constructQ(&bmObj->doneLlObj);
    GT_assert(DssTrace, (retVal == FVID2_SOK));
    bmObj->doneQ = &bmObj->doneLlObj;

    if(FVID2_SOK == retVal)
    {
        /* Initialize and queue the allocate queue object to free Q */
        for(qCnt=0U; qCnt<DSS_DEF_QUEUE_LEN_PER_INST; qCnt++)
        {
            qObj = &bmObj->dispQObj[qCnt];
            qObj->instObj = instObj;
            qObj->frm = NULL;
            qObj->creditCnt = 0U;
            Fvid2Utils_queue(bmObj->freeQ, &qObj->qElem, qObj);
        }
    }

    if(FVID2_SOK == retVal)
    {
        CSL_dssCscCoeffInit(&instObj->pipeParams[instObj->pipeId].pipeCfg.custCscCoeff);
    }

    /* Deallocate if error occurs */
    if(FVID2_SOK != retVal)
    {
        tempRetVal = Dss_dispDrvDeleteInstObj(instObj);
        GT_assert(DssTrace, (FVID2_SOK == tempRetVal));
    }

    return (retVal);
}

int32_t Dss_dispDrvDeleteInstObj(Dss_DispDrvInstObj *instObj)
{
    int32_t retVal = FVID2_SOK;
    Dss_DispDrvQueObj *qObj;
    Dss_DispDrvBufManObj *bmObj;

    /* NULL pointer check */
    GT_assert(DssTrace, (NULL != instObj));
    bmObj = &instObj->bmObj;

    bmObj->isProgressive = TRUE;
    bmObj->curFid        = 0U;
    bmObj->expectedFid   = 0U;
    bmObj->fieldMerged   = TRUE;

    if(NULL != bmObj->freeQ)
    {
        /* Free-up all the queued free queue objects */
        do
        {
            qObj = (Dss_DispDrvQueObj *) Fvid2Utils_dequeue(bmObj->freeQ);
        } while (NULL != qObj);

        /* Delete the free Q */
        Fvid2Utils_destructQ(bmObj->freeQ);
        bmObj->freeQ = NULL;
    }

    if(NULL != bmObj->reqQ)
    {
        /* Free-up all object from request queue */
        do
        {
            qObj = (Dss_DispDrvQueObj *) Fvid2Utils_dequeue(bmObj->reqQ);
        } while (NULL != qObj);

        /* Delete the request Q */
        Fvid2Utils_destructQ(bmObj->reqQ);
        bmObj->reqQ = NULL;
    }

    if(NULL != bmObj->currQ)
    {
        /* Free-up all object from current queue */
        do
        {
            qObj = (Dss_DispDrvQueObj *) Fvid2Utils_dequeue(bmObj->currQ);
        } while (NULL != qObj);

        /* Delete the free Q */
        Fvid2Utils_destructQ(bmObj->currQ);
        bmObj->currQ = NULL;
    }

    if(NULL != bmObj->doneQ)
    {
        /* Free-up all object from done queue */
        do
        {
            qObj = (Dss_DispDrvQueObj *) Fvid2Utils_dequeue(bmObj->doneQ);
        } while (NULL != qObj);

        /* Delete the done Q */
        Fvid2Utils_destructQ(bmObj->doneQ);
        bmObj->doneQ = NULL;
    }

    return (retVal);
}

static void Dss_dispErrCbFxn(const uint32_t *event,
                             uint32_t numEvents,
                             void *arg)
{
    uint32_t  i, currEvent, pipeId = 0U;
    Dss_EvtMgrClientInfo *pClientObj = (Dss_EvtMgrClientInfo *)arg;
    uint32_t eventGroup = pClientObj->eventGroup;
    Dss_DispDrvInstObj *instObj;

    Dss_convEventGrouptoModule(eventGroup, &pipeId);
    GT_assert(DssTrace, (CSL_DSS_MODULE_INVALID != pipeId));
    instObj = &gDss_DispDrvInstObj[pipeId];
    for(i=0U; i<numEvents; i++)
    {
        currEvent = event[i];
        if(DSS_PIPE_EVENT_BUFF_UNDERFLOW == currEvent)
        {
           instObj->currStatus.underflowCount++;
           if(NULL != instObj->underFlowCbParams.underFlowCbFxn)
           {
               instObj->underFlowCbParams.underFlowCbFxn(
                                        instObj->underFlowCbParams.appData);
           }
        }
        else
        {
            GT_assert(DssTrace, FALSE);
        }
    }

    return;
}
