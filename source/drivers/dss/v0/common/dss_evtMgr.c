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
 *  \file dss_evtMgr.c
 *
 *  \brief File containing the DSS event manager implementation.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/dss.h>
#include <drivers/fvid2.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/HwiP.h>
#include <drivers/dss/v0/common/dss_evtMgr.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Flags used by event info structure memory pool manager to
 *  indicate availability of pool memory
 */
#define DSS_EVT_MGR_MEM_FLAG_FREE               ((uint32_t) 0xFFFFFFFFU)
#define DSS_EVT_MGR_MEM_FLAG_ALLOC              ((uint32_t) 0x00000000U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Structure containing common variables of event manager
 */
typedef struct
{
    uint32_t isInitDone;
    /**< Flag to indicate that the object is initialized */
    Dss_EvtMgrInfo evtMgrMemPool[DSS_EVT_MGR_MAX_CLIENTS];
    /**< Pool of memory for the event manager info structure */
    uint32_t evtMgrMemFlag[DSS_EVT_MGR_MAX_CLIENTS];
    /**< Flags for each instance to indicate whether it is free or allocated */
    Fvid2Utils_Node nodePool[DSS_EVT_MGR_MAX_CLIENTS];
    /**< Pool of memory for the node */
    SemaphoreP_Object lockSem;
    /**< Semaphore handle */
} Dss_EvtMgrCommonObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void Dss_evtMgrMasterIsr(void *arg);

static int32_t Dss_evtMgrFillInfo(Dss_EvtMgrInfo *evtMgrInfo,
                                  uint32_t eventGroup,
                                  const uint32_t *event,
                                  uint32_t numEvents,
                                  Dss_evtMgrCbFxn callback,
                                  void *arg);

static void Dss_evtMgrDeleteInfo(const Dss_EvtMgrInfo *evtMgrInfo);

static Dss_EvtMgrInfo *Dss_evtMgrCreateInfo(Fvid2Utils_Node **node);

static void Dss_evtMgrAddNode(Fvid2Utils_Node *newNode);

static void Dss_evtMgrDeleteNode(const Fvid2Utils_Node *emNode);

static Dss_EvtMgrInstObj *Dss_evtMgrGetInstObj(uint32_t instId);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static Dss_EvtMgrInstObj gDss_EvtMgrInstObj[DSS_EVT_MGR_INST_ID_MAX];
static Dss_EvtMgrCommonObj gDss_EvtMgrCommonObj = {FALSE};

/* ========================================================================== */
/*                  Internal/Private Function Declarations                   */
/* ========================================================================== */


/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t Dss_evtMgrInit(const Dss_EvtMgrInitParams *initParams)
{
    int32_t retVal = FVID2_SOK;
    int32_t status = SystemP_SUCCESS;
    uint32_t cnt;
    Dss_EvtMgrInstObj *instObj;
    HwiP_Params hwiParams;

    /* Check for errors */
    GT_assert(DssTrace, (NULL != initParams));
    GT_assert(DssTrace, (initParams->numIrq <= DSS_EVT_MGR_INST_ID_MAX));
    GT_assert(DssTrace,
              (initParams->dssCommonRegionId < CSL_DSS_COMM_REG_ID_MAX));

    if(FALSE == gDss_EvtMgrCommonObj.isInitDone)
    {
        /* Initialize objects and mark flags as free */
        for(cnt=0U; cnt<DSS_EVT_MGR_INST_ID_MAX; cnt++)
        {
            Fvid2Utils_memset(&gDss_EvtMgrInstObj[cnt],
                              0U,
                              sizeof (gDss_EvtMgrInstObj[cnt]));
            gDss_EvtMgrInstObj[cnt].instId = DSS_EVT_MGR_INST_ID_INVALID;
            Fvid2Utils_initTsPrfLog(&gDss_EvtMgrInstObj[cnt].isrPrfLog);
        }
        Fvid2Utils_memset(&gDss_EvtMgrCommonObj,
                          0U,
                          sizeof (gDss_EvtMgrCommonObj));

        for(cnt=0U; cnt<DSS_EVT_MGR_MAX_CLIENTS; cnt++)
        {
            gDss_EvtMgrCommonObj.evtMgrMemFlag[cnt] =
                                                DSS_EVT_MGR_MEM_FLAG_FREE;
        }

        /* Initialize the semaphore parameters and create semaphore pool */
        status = SemaphoreP_constructBinary(&gDss_EvtMgrCommonObj.lockSem, 1U);

        if(status != SystemP_SUCCESS)
        {
            retVal = FVID2_EALLOC;
        }

        if(FVID2_SOK == retVal)
        {
            /* Initialize instance object members */
            for(cnt=0U; cnt<initParams->numIrq; cnt++)
            {
                instObj = &gDss_EvtMgrInstObj[cnt];
                instObj->dssCommonRegionId = initParams->dssCommonRegionId;
                instObj->irqNum = initParams->irqNum[cnt];
                instObj->instId = initParams->instId[cnt];
                instObj->isInitDone = TRUE;
                instObj->headNode = NULL;
                instObj->numIntr  = 0U;

                /* Clear out any pending interrupts */
                HwiP_clearInt(instObj->irqNum);

                /* Populate the interrupt parameters */
                HwiP_Params_init(&hwiParams);
                hwiParams.args = (void *) instObj;
                hwiParams.intNum = instObj->irqNum;
                hwiParams.callback = Dss_evtMgrMasterIsr;
                status = HwiP_construct(&instObj->intrHandle, &hwiParams);

                /* Initialize head node and number of interrupts */
                instObj->headNode = NULL;
                instObj->numIntr  = 0U;

                if(status != SystemP_SUCCESS)
                {
                    retVal = FVID2_EALLOC;
                    GT_1trace(DssTrace,
                              GT_ERR,
                              "%s: Cannot Register IRQ", __FUNCTION__);
                }

            }
        }

        if(retVal != FVID2_SOK)
        {
            retVal+= Dss_evtMgrDeInit();
        }
    }
    return (retVal);
}

int32_t Dss_evtMgrDeInit(void)
{
    uint32_t cnt;
    Dss_EvtMgrInstObj *instObj;
    Fvid2Utils_Node *tempNode;
    Fvid2Utils_Node *emNode;

    for(cnt=0U; cnt<DSS_EVT_MGR_INST_ID_MAX; cnt++)
    {
        instObj = &gDss_EvtMgrInstObj[cnt];
        instObj->isInitDone = FALSE;

        /* Un-register interrupt */
        HwiP_destruct(&instObj->intrHandle);

        /* Free Entire Linked List */
        tempNode = instObj->headNode;
        while (NULL != tempNode)
        {
            emNode   = tempNode;
            tempNode = tempNode->next;
            Dss_evtMgrDeleteInfo((Dss_EvtMgrInfo *) emNode->data);
            Dss_evtMgrDeleteNode(emNode);
        }
    }

    SemaphoreP_destruct(&gDss_EvtMgrCommonObj.lockSem);

    return (FVID2_SOK);
}

void *Dss_evtMgrRegister(uint32_t instId,
                         uint32_t eventGroup,
                         const uint32_t *event,
                         uint32_t numEvents,
                         Dss_evtMgrCbFxn callback,
                         void *arg)
{
    int32_t retVal = FVID2_SOK;
    Dss_EvtMgrInstObj *instObj;
    Fvid2Utils_Node *newNode = NULL;
    Dss_EvtMgrInfo *evtMgrInfo = NULL;

    /* Check for the error conditions */
    GT_assert(DssTrace, (NULL != event));
    GT_assert(DssTrace, (0U != numEvents));
    GT_assert(DssTrace, (NULL != callback));

    instObj = Dss_evtMgrGetInstObj(instId);
    GT_assert(DssTrace, (NULL != instObj));

    if(TRUE != instObj->isInitDone)
    {
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        (void) SemaphoreP_pend(&gDss_EvtMgrCommonObj.lockSem,
                               SystemP_WAIT_FOREVER);

        /* Allocate memory for the event manager info structure */
        evtMgrInfo = Dss_evtMgrCreateInfo(&newNode);

        if((NULL != evtMgrInfo) && (NULL != newNode))
        {
            newNode->data = (void *) evtMgrInfo;

            evtMgrInfo->instObj = instObj;
            evtMgrInfo->numIntr = 0U;

            /* Fill up the details about events in the client info structure */
            retVal = Dss_evtMgrFillInfo(evtMgrInfo,
                                        eventGroup,
                                        event,
                                        numEvents,
                                        callback,
                                        arg);

            /* Add the node in the linked list as per the priority */
            Dss_evtMgrAddNode(newNode);
        }

        (void) SemaphoreP_post(&gDss_EvtMgrCommonObj.lockSem);
    }

    return ((void *) newNode);
}

int32_t Dss_evtMgrUnRegister(void *handle)
{
    uint32_t found = FALSE;
    uint32_t cnt, event, regVal;
    uint32_t eventGroup;
    Dss_EvtMgrInstObj *instObj = NULL;
    Fvid2Utils_Node *tempNode = NULL;
    Fvid2Utils_Node *emNode = NULL;
    Dss_EvtMgrInfo *evtMgrInfo = NULL;

    /* Error condition Checking */
    GT_assert(DssTrace, (NULL != handle));
    tempNode = (Fvid2Utils_Node *) handle;
    GT_assert(DssTrace, (NULL != tempNode->data));
    instObj = ((Dss_EvtMgrInfo *) (tempNode->data))->instObj;
    GT_assert(DssTrace, (NULL != instObj));

    /* Check to see if the node given is in the linked list */
    emNode = instObj->headNode;
    GT_assert(DssTrace, (NULL != emNode));

    while (NULL != emNode)
    {
        if(tempNode == emNode)
        {
            found = TRUE;
            break;
        }
        emNode = emNode->next;
    }
    GT_assert(DssTrace, (FALSE != found));

    evtMgrInfo = (Dss_EvtMgrInfo *) tempNode->data;
    GT_assert(DssTrace, (NULL != evtMgrInfo));

    (void) SemaphoreP_pend(&gDss_EvtMgrCommonObj.lockSem,
                           SystemP_WAIT_FOREVER);

    /* Delete the Node */
    Dss_evtMgrDeleteNode(tempNode);

    /* Disable events in the DSS registers */
    eventGroup = evtMgrInfo->eventGroup;

    for(cnt=0U; cnt<evtMgrInfo->numEvents; cnt++)
    {
        event = evtMgrInfo->allEvents[cnt];

        /* Disable the interrupts at the level 1 */
        regVal = CSL_REG32_RD(evtMgrInfo->l1EnableReg[cnt]);
        regVal &= (~event);
        CSL_REG32_WR(evtMgrInfo->l1EnableReg[cnt], regVal);

        /* Clear the status of the interrupt */
        CSL_REG32_WR(evtMgrInfo->l1StatusReg[cnt],
                     evtMgrInfo->l1Mask[cnt]);

        evtMgrInfo->l1EnableReg[cnt] = 0x0U;
        evtMgrInfo->l1StatusReg[cnt] = 0x0U;
        evtMgrInfo->l1Mask[cnt]      = 0x0U;
    }

    /* Disable the interrupt */
    regVal = eventGroup;
    CSL_REG32_WR(evtMgrInfo->l0DisableReg, regVal);

    /* Clear the status of interrupt */
    regVal = eventGroup;
    CSL_REG32_WR(evtMgrInfo->l0StatusReg, regVal);

    evtMgrInfo->l0EnableReg  = 0x0U;
    evtMgrInfo->l0StatusReg  = 0x0U;
    evtMgrInfo->l0DisableReg = 0x0U;
    evtMgrInfo->l0Mask       = 0x0U;
    evtMgrInfo->clientCb     = NULL;
    evtMgrInfo->arg          = NULL;
    evtMgrInfo->instObj      = NULL;
    evtMgrInfo->numEvents    = 0U;

    /* Free up memory allocated to event arrays and evtMgrInfo structure */
    Dss_evtMgrDeleteInfo(evtMgrInfo);

    (void) SemaphoreP_post(&gDss_EvtMgrCommonObj.lockSem);

    return (FVID2_SOK);
}

int32_t Dss_evtMgrEnable(void *handle)
{
    uint32_t found = FALSE;
    uint32_t cnt, regVal;
    uint32_t eventGroup, event;
    Dss_EvtMgrInstObj *instObj = NULL;
    Fvid2Utils_Node *tempNode = NULL;
    Fvid2Utils_Node *emNode = NULL;
    Dss_EvtMgrInfo *evtMgrInfo = NULL;

    /* Error condition Checking */
    GT_assert(DssTrace, (NULL != handle));
    tempNode = (Fvid2Utils_Node *) handle;
    GT_assert(DssTrace, (NULL != tempNode->data));
    instObj = ((Dss_EvtMgrInfo *) (tempNode->data))->instObj;
    GT_assert(DssTrace, (NULL != instObj));

    /* Check to see if the node given is in the linked list */
    emNode = instObj->headNode;
    GT_assert(DssTrace, (NULL != emNode));

    while (NULL != emNode)
    {
        if(tempNode == emNode)
        {
            found = TRUE;
            break;
        }
        emNode = emNode->next;
    }
    GT_assert(DssTrace, (FALSE != found));

    evtMgrInfo = (Dss_EvtMgrInfo *) tempNode->data;
    GT_assert(DssTrace, (NULL != evtMgrInfo));

    (void) SemaphoreP_pend(&gDss_EvtMgrCommonObj.lockSem,
                           SystemP_WAIT_FOREVER);

    eventGroup = evtMgrInfo->eventGroup;

    for(cnt=0U; cnt<evtMgrInfo->numEvents; cnt++)
    {
        event = evtMgrInfo->allEvents[cnt];

        /* Clear the status of the interrupt */
        CSL_REG32_WR(evtMgrInfo->l1StatusReg[cnt],
                     evtMgrInfo->l1Mask[cnt]);

        /* Enable the interrupts at the level 1 */
        regVal = CSL_REG32_RD(evtMgrInfo->l1EnableReg[cnt]);
        regVal |= event;
        CSL_REG32_WR(evtMgrInfo->l1EnableReg[cnt], regVal);
    }

    /* Clear the status of interrupt */
    regVal = CSL_REG32_RD(evtMgrInfo->l0StatusReg);
    regVal |= eventGroup;
    CSL_REG32_WR(evtMgrInfo->l0StatusReg, regVal);

    /* Enable the interrupt */
    regVal = CSL_REG32_RD(evtMgrInfo->l0EnableReg);
    regVal |= eventGroup;
    CSL_REG32_WR(evtMgrInfo->l0EnableReg, regVal);

    (void) SemaphoreP_post(&gDss_EvtMgrCommonObj.lockSem);

    return (FVID2_SOK);
}

int32_t Dss_evtMgrDisable(void *handle)
{
    uint32_t found = FALSE;
    uint32_t cnt, regVal;
    uint32_t eventGroup, event;
    Dss_EvtMgrInstObj *instObj = NULL;
    Fvid2Utils_Node *tempNode = NULL;
    Fvid2Utils_Node *emNode = NULL;
    Dss_EvtMgrInfo *evtMgrInfo = NULL;

    /* Error condition Checking */
    GT_assert(DssTrace, (NULL != handle));
    tempNode = (Fvid2Utils_Node *) handle;
    GT_assert(DssTrace, (NULL != tempNode->data));
    instObj = ((Dss_EvtMgrInfo *) (tempNode->data))->instObj;
    GT_assert(DssTrace, (NULL != instObj));

    /* Check to see if the node given is in the linked list */
    emNode = instObj->headNode;
    GT_assert(DssTrace, (NULL != emNode));

    while (NULL != emNode)
    {
        if(tempNode == emNode)
        {
            found = TRUE;
            break;
        }
        emNode = emNode->next;
    }
    GT_assert(DssTrace, (FALSE != found));

    evtMgrInfo = (Dss_EvtMgrInfo *) tempNode->data;
    GT_assert(DssTrace, (NULL != evtMgrInfo));

    (void) SemaphoreP_pend(&gDss_EvtMgrCommonObj.lockSem,
                           SystemP_WAIT_FOREVER);

    eventGroup = evtMgrInfo->eventGroup;

    for(cnt=0U; cnt<evtMgrInfo->numEvents; cnt++)
    {
        event = evtMgrInfo->allEvents[cnt];

        /* Disable the interrupts at the level 1 */
        regVal = CSL_REG32_RD(evtMgrInfo->l1EnableReg[cnt]);
        regVal &= (~event);
        CSL_REG32_WR(evtMgrInfo->l1EnableReg[cnt], regVal);

        /* Clear the status of the interrupt */
        CSL_REG32_WR(evtMgrInfo->l1StatusReg[cnt],
                     evtMgrInfo->l1Mask[cnt]);
    }

    /* Disable the interrupt */
    regVal = CSL_REG32_RD(evtMgrInfo->l0DisableReg);
    regVal |= eventGroup;
    CSL_REG32_WR(evtMgrInfo->l0DisableReg, regVal);

    /* Clear the status of interrupt */
    regVal = CSL_REG32_RD(evtMgrInfo->l0StatusReg);
    regVal |= eventGroup;
    CSL_REG32_WR(evtMgrInfo->l0StatusReg, regVal);

    (void) SemaphoreP_post(&gDss_EvtMgrCommonObj.lockSem);

    return (FVID2_SOK);
}

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static void Dss_evtMgrMasterIsr(void *arg)
{
    uint32_t cnt;
    uint32_t regVal, numEvents;
    Fvid2Utils_Node *tempNode;
    Dss_EvtMgrInfo *evtMgrInfo = NULL;
    Dss_EvtMgrInstObj *instObj;
    instObj  = (Dss_EvtMgrInstObj *) arg;

    Fvid2Utils_startTsPrfLog(&instObj->isrPrfLog);

    /* Traverse through the entire list of registered clients */
    tempNode = instObj->headNode;
    while (NULL != tempNode)
    {
        evtMgrInfo = (Dss_EvtMgrInfo *) tempNode->data;
        GT_assert(DssTrace, (NULL != evtMgrInfo));

        regVal = CSL_REG32_RD(evtMgrInfo->l0StatusReg);
        if(evtMgrInfo->l0Mask == (evtMgrInfo->l0Mask & regVal))
        {
            CSL_REG32_WR(evtMgrInfo->l0StatusReg,
                         evtMgrInfo->l0Mask);
        }

        /* Move to the next client */
        tempNode = tempNode->next;
    }

    /* Traverse through the entire list of registered clients */
    tempNode = instObj->headNode;
    while (NULL != tempNode)
    {
        evtMgrInfo = (Dss_EvtMgrInfo *) tempNode->data;
        GT_assert(DssTrace, (NULL != evtMgrInfo));
        numEvents = 0U;

        for(cnt=0U; cnt<evtMgrInfo->numEvents; cnt++)
        {
            regVal = CSL_REG32_RD(evtMgrInfo->l1StatusReg[cnt]);

            if(0U != (regVal & (evtMgrInfo->l1Mask[cnt])))
            {
                evtMgrInfo->setEvents[numEvents] =
                                        evtMgrInfo->allEvents[cnt];
                numEvents++;
                /* Clear the status */
                CSL_REG32_WR(evtMgrInfo->l1StatusReg[cnt],
                             evtMgrInfo->l1Mask[cnt]);
            }
        }

        /* Call callback if any event occurs for the client */
        if(0U != numEvents)
        {
            if(NULL != evtMgrInfo->clientCb)
            {
                evtMgrInfo->clientCb(evtMgrInfo->setEvents,
                                     numEvents,
                                     evtMgrInfo->arg);
            }

            /* Increment total number of interrupts */
            evtMgrInfo->numIntr++;
        }

        /* Move to the next client */
        tempNode = tempNode->next;
    }

    /* Increment total number of interrupts */
    instObj->numIntr++;

    Fvid2Utils_endTsPrfLog(&instObj->isrPrfLog);

    return;
}

static int32_t Dss_evtMgrFillInfo(Dss_EvtMgrInfo *evtMgrInfo,
                                  uint32_t eventGroup,
                                  const uint32_t *event,
                                  uint32_t numEvents,
                                  Dss_evtMgrCbFxn callback,
                                  void *arg)
{
    int32_t retVal = FVID2_SOK;
    uint32_t cnt, regVal;
    uint32_t dssCommonRegionId;
    CSL_dss_commRegs *commRegs;
    const Dss_SocInfo *socInfo;
    Dss_EvtMgrClientInfo *evtMgrClientInfo =
                        (Dss_EvtMgrClientInfo *)(arg);

    GT_assert(DssTrace, (NULL != evtMgrInfo));
    GT_assert(DssTrace, (NULL != event));
    GT_assert(DssTrace, (NULL != callback));

    evtMgrInfo->eventGroup = eventGroup;
    evtMgrInfo->numEvents  = numEvents;
    evtMgrInfo->arg = arg;
    dssCommonRegionId = evtMgrInfo->instObj->dssCommonRegionId;
    /* Get common register space */
    socInfo = Dss_getSocInfo();
    commRegs = socInfo->commRegs[dssCommonRegionId];
    GT_assert(DssTrace, (NULL != commRegs));

    for(cnt=0U; cnt<numEvents; cnt++)
    {
        retVal = Dss_enableL1Event(evtMgrInfo,
                                   dssCommonRegionId,
                                   eventGroup,
                                   event[cnt],
                                   cnt);

        GT_assert(DssTrace, (FVID2_SOK == retVal));
    }

    /* Clear the status of interrupt */
    regVal = CSL_REG32_RD(&commRegs->DISPC_IRQSTATUS);
    regVal |= eventGroup;
    CSL_REG32_WR(&commRegs->DISPC_IRQSTATUS, regVal);

    /* Enable Interrupt at the top level */
    regVal = CSL_REG32_RD(&commRegs->DISPC_IRQENABLE_SET);
    regVal |= eventGroup;
    CSL_REG32_WR(&commRegs->DISPC_IRQENABLE_SET, regVal);

    /* Store the register address in evtMgrInfo instance */
    evtMgrInfo->l0DisableReg = &commRegs->DISPC_IRQENABLE_CLR;
    evtMgrInfo->l0EnableReg = &commRegs->DISPC_IRQENABLE_SET;
    evtMgrInfo->l0StatusReg = &commRegs->DISPC_IRQSTATUS;
    evtMgrInfo->l0Mask = eventGroup;

    evtMgrClientInfo->eventGroup = eventGroup;
    evtMgrInfo->clientCb = callback;

    return (retVal);
}

static Dss_EvtMgrInfo *Dss_evtMgrCreateInfo(Fvid2Utils_Node **node)
{
    uint32_t cnt;
    Dss_EvtMgrInfo *evtMgrInfo = NULL;

    for(cnt=0U; cnt<DSS_EVT_MGR_MAX_CLIENTS; cnt++)
    {
        if(DSS_EVT_MGR_MEM_FLAG_FREE ==
                                    gDss_EvtMgrCommonObj.evtMgrMemFlag[cnt])
        {
            evtMgrInfo = &(gDss_EvtMgrCommonObj.evtMgrMemPool[cnt]);
            *node = &gDss_EvtMgrCommonObj.nodePool[cnt];
            gDss_EvtMgrCommonObj.evtMgrMemFlag[cnt] =
                                                DSS_EVT_MGR_MEM_FLAG_ALLOC;
            break;
        }
    }

    return (evtMgrInfo);
}

static void Dss_evtMgrDeleteInfo(const Dss_EvtMgrInfo *evtMgrInfo)
{
    uint32_t cnt;

    GT_assert(DssTrace, (NULL != evtMgrInfo));

    for(cnt=0U; cnt<DSS_EVT_MGR_MAX_CLIENTS; cnt++)
    {
        if(evtMgrInfo == &(gDss_EvtMgrCommonObj.evtMgrMemPool[cnt]))
        {
            gDss_EvtMgrCommonObj.evtMgrMemFlag[cnt] = DSS_EVT_MGR_MEM_FLAG_FREE;
            break;
        }
    }

    return;
}

static void Dss_evtMgrAddNode(Fvid2Utils_Node *newNode)
{
    uint32_t cookie;
    Dss_EvtMgrInstObj *instObj = NULL;
    Fvid2Utils_Node *curr = NULL;
    Fvid2Utils_Node *prev = NULL;

    GT_assert(DssTrace, (NULL != newNode));

    /* Disable interrupts before updating node list */
    cookie = HwiP_disable();

    instObj = ((Dss_EvtMgrInfo *) (newNode->data))->instObj;
    GT_assert(DssTrace, (NULL != instObj));

    newNode->prev = NULL;
    newNode->next = NULL;

    curr = instObj->headNode;
    prev = NULL;

    /* Search for place to insert new node */
    while (NULL != curr)
    {
        prev = curr;
        curr = curr->next;
    }

    /* Update pointers */
    newNode->next = curr;
    newNode->prev = prev;

    if(NULL == prev)
    {
        instObj->headNode = newNode;
    }
    else
    {
        prev->next = newNode;
    }

    /* Restore interrupts after updating node list */
    HwiP_restore(cookie);

    return;
}

static void Dss_evtMgrDeleteNode(const Fvid2Utils_Node *emNode)
{
    uint32_t cookie;
    Dss_EvtMgrInstObj *instObj = NULL;
    Fvid2Utils_Node *curr = NULL;
    Fvid2Utils_Node *prev = NULL;

    GT_assert(DssTrace, (NULL != emNode));

    /* Disable interrupts before updating node list */
    cookie = HwiP_disable();

    instObj = ((Dss_EvtMgrInfo *) (emNode->data))->instObj;
    prev = emNode->prev;
    curr = emNode->next;

    if(NULL != prev)
    {
        if(NULL != curr)
        {
            prev->next = curr;
        }
        else
        {
            prev->next = NULL;
        }
    }
    else
    {
        instObj->headNode = curr;
        if(NULL != instObj->headNode)
        {
            instObj->headNode->prev = NULL;
        }
    }
    if(NULL != curr)
    {
        curr->prev = prev;
    }

    /* Restore interrupts after updating node list */
    HwiP_restore(cookie);

    return;
}

static Dss_EvtMgrInstObj *Dss_evtMgrGetInstObj(uint32_t instId)
{
    uint32_t cnt;
    Dss_EvtMgrInstObj *instObj = NULL;

    if(instId < DSS_EVT_MGR_INST_ID_MAX)
    {
        for(cnt=0U; cnt<DSS_EVT_MGR_INST_ID_MAX; cnt++)
        {
            if(gDss_EvtMgrInstObj[instId].instId == instId)
            {
                instObj = &gDss_EvtMgrInstObj[instId];
                break;
            }
        }
    }

    return (instObj);
}
