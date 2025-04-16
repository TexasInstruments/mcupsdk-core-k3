/*
 *  Copyright (C) 2018-2025 Texas Instruments Incorporated
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
 *  \file udma_event.c
 *
 *  \brief File containing the UDMA driver event management functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/udma/v1/udma_priv.h>

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

static void Udma_eventIsrFxn(void *args);
static int32_t Udma_eventCheckParams(Udma_DrvHandleInt drvHandle,
                                     const Udma_EventPrms *eventPrms);
static int32_t Udma_eventCheckUnRegister(Udma_DrvHandleInt drvHandle,
                                         Udma_EventHandleInt eventHandle);
static void Udma_eventFreeResource(Udma_DrvHandleInt drvHandle,
                                   Udma_EventHandleInt eventHandle);
static int32_t Udma_eventConfig(Udma_DrvHandleInt drvHandle,
                                Udma_EventHandleInt eventHandle);



/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t Udma_eventRegister(Udma_DrvHandle drvHandle,
                           Udma_EventHandle eventHandle,
                           Udma_EventPrms *eventPrms)
{
    int32_t             retVal = UDMA_SOK;
    uint32_t            allocDone = (uint32_t) FALSE;
    Udma_DrvHandleInt   drvHandleInt;
    Udma_EventHandleInt eventHandleInt;
    Udma_ChHandleInt    chHandle;
    CSL_LcdmaRingaccCfg *pRaCfg;

    /* Error check */
    if((NULL == drvHandle) || (NULL == eventHandle) || (NULL == eventPrms))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandleInt = (Udma_DrvHandleInt) drvHandle;
        chHandle = (Udma_ChHandleInt) eventPrms->chHandle;
        if(drvHandleInt->drvInitDone != UDMA_INIT_DONE)
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        retVal = Udma_eventCheckParams(drvHandleInt, eventPrms);
    }

    if(UDMA_SOK == retVal)
    {
        /* Copy and init parameters */
        eventHandleInt = (Udma_EventHandleInt) eventHandle;
        (void) memcpy(
            &eventHandleInt->eventPrms, eventPrms, sizeof(eventHandleInt->eventPrms));
        eventHandleInt->drvHandle       = drvHandleInt;
        eventHandleInt->coreIntrNum     = UDMA_INTR_INVALID;
        eventHandleInt->hwiHandle       = NULL;
    }

    if(UDMA_SOK == retVal)
    {
        if ((UDMA_INST_TYPE_NORMAL           != drvHandleInt->instType) &&
            (UDMA_EVENT_TYPE_TEARDOWN_PACKET == eventPrms->eventType))
        {
            /* eventHandle is already populated with drvHandle and eventPrms,
            becase during Unregistering this event,
            the instType in DrvHandle and evenType in eventPrms
            are required to bypass the eventReset
            (Since only evenHandle is passed to eventUnRegister) */
        }
        else
        {
            /* Set init flag as events are allocated and event config expects
            * this flag to be set */
            eventHandleInt->eventInitDone = UDMA_INIT_DONE;

            /* Configure Event */
            retVal = Udma_eventConfig(drvHandleInt, eventHandleInt);
            if(UDMA_SOK == retVal)
            {
                allocDone = (uint32_t) TRUE;
            }
            else
            {
                DebugP_logError("[UDMA] Event config failed!!\r\n");
            }

            if(UDMA_SOK != retVal)
            {
                /* Error. Free-up resource if allocated */
                if(((uint32_t) TRUE) == allocDone)
                {
                    Udma_eventFreeResource(drvHandleInt, eventHandleInt);
                    eventHandleInt->eventInitDone = UDMA_DEINIT_DONE;
                }
            }
            else
            {
                if((chHandle->chType & UDMA_CH_FLAG_BLK_COPY) == UDMA_CH_FLAG_BLK_COPY)
                {
                    pRaCfg = &drvHandleInt->lcdmaRaRegs;
                    eventPrms->intrStatusReg    = &pRaCfg->pFlowRtRegs->FLOW[chHandle->txChNum].INT_STATUS;
                    eventPrms->intrClearReg     = &pRaCfg->pFlowRtRegs->FLOW[chHandle->txChNum].INT_STATUS;
                }

                eventPrms->intrMask = 0xFFFFFFFFu;
                eventPrms->coreIntrNum  = eventHandleInt->coreIntrNum;
                /* Copy the same info to eventHandleInt->eventPrms*/
                eventHandleInt->eventPrms.coreIntrNum     = eventPrms->coreIntrNum;
                eventHandleInt->eventPrms.intrStatusReg   = eventPrms->intrStatusReg;
                eventHandleInt->eventPrms.intrClearReg    = eventPrms->intrClearReg;
                eventHandleInt->eventPrms.intrMask        = eventPrms->intrMask;
            }
        }
    }
    return (retVal);
}

int32_t Udma_eventUnRegister(Udma_EventHandle eventHandle)
{
    int32_t             retVal = UDMA_SOK;
    Udma_DrvHandleInt   drvHandle;
    Udma_EventHandleInt eventHandleInt;

    /* Error check */
    if(NULL == eventHandle)
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        eventHandleInt = (Udma_EventHandleInt) eventHandle;
        drvHandle = eventHandleInt->drvHandle;
        if((NULL == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        if ((UDMA_INST_TYPE_NORMAL           != drvHandle->instType) &&
            (UDMA_EVENT_TYPE_TEARDOWN_PACKET == eventHandleInt->eventPrms.eventType))
        {
            /* In case of some devices where Teardown is not supported.
            There is no need to unregister teardown event. */
        }
        else
        {
            retVal = Udma_eventCheckUnRegister(drvHandle, eventHandleInt);

            if(UDMA_SOK == retVal)
            {
                if(NULL != eventHandleInt->hwiHandle)
                {
                    /* Disable able core interrupt to avoid having insane
                    * state/variables when an interrupt occurs while processing
                    * event free */
                    if(eventHandleInt->coreIntrNum != UDMA_INTR_INVALID)
                    {
                       HwiP_disableInt(eventHandleInt->coreIntrNum);
                    }
                }
                Udma_eventFreeResource(drvHandle, eventHandleInt);

                eventHandleInt->eventInitDone  = UDMA_DEINIT_DONE;
                eventHandleInt->drvHandle      = (Udma_DrvHandleInt) NULL;
            }
        }
    }
    return (retVal);
}

void UdmaEventPrms_init(Udma_EventPrms *eventPrms)
{
    if(NULL != eventPrms)
    {
        eventPrms->eventType            = UDMA_EVENT_TYPE_DMA_COMPLETION;
        eventPrms->eventMode            = UDMA_EVENT_MODE_SHARED;
        eventPrms->chHandle             = (Udma_ChHandle) NULL;
        eventPrms->ringHandle           = (Udma_RingHandle) NULL;
        eventPrms->eventCb              = (Udma_EventCallback) NULL;
        eventPrms->intrPriority         = 1U;
        eventPrms->appData              = NULL;
        eventPrms->preferredCoreIntrNum = UDMA_CORE_INTR_ANY;
        eventPrms->coreIntrNum          = UDMA_INTR_INVALID;
        eventPrms->intrStatusReg        = (volatile uint32_t *) NULL;
        eventPrms->intrClearReg         = (volatile uint32_t *) NULL;
        eventPrms->intrMask             = 0U;
    }

    return;
}

static void Udma_eventIsrFxn(void *args)
{

    uint32_t            teardownStatus;
    Udma_EventHandleInt eventHandle = (Udma_EventHandleInt) args;
    Udma_DrvHandleInt   drvHandle;
    Udma_EventPrms     *eventPrms;
    Udma_ChHandleInt   chHandle;

    teardownStatus = UDMA_EVENT_CH_TEARDOWN_STATUS_NA;
    chHandle = NULL;
    drvHandle = eventHandle->drvHandle;

    CSL_LcdmaRingaccCfg *pCfg = &drvHandle->lcdmaRaRegs;
    bool     retVal = (bool)false;
    uint32_t regVal;
    uint32_t ringNum;

    /* Loop through all the shared events. In case of exclusive events,
     * the next event is NULL and the logic remains same and the while breaks */
    while(eventHandle != NULL)
    {
        /* There is no valid VINT bit for global master event */
        if(UDMA_EVENT_TYPE_MASTER != eventHandle->eventPrms.eventType)
        {
            /* Notify through callback if registered */
            eventPrms = &eventHandle->eventPrms;
            if(eventPrms->chHandle != NULL)
            {
                chHandle = ((Udma_ChHandleInt) (eventPrms->chHandle));
                ringNum = chHandle->chAttr.ChNum + chHandle->chAttr.flowIdx;
                regVal = CSL_lcdmaGetInterrupt(pCfg, ringNum);
                if(regVal != 0u)
                {
                    retVal = (bool)true;
                }
                if((bool)true == retVal)
                {
                    /* Clear the interrupt */
                    CSL_lcdmaSetInterrupt(pCfg, ringNum, UDMA_SET_COMP_INT, false);

                    if((UDMA_EVENT_TYPE_DMA_COMPLETION == eventPrms->eventType) ||
                       (UDMA_EVENT_TYPE_TEARDOWN_COMPLETION == eventPrms->eventType))
                    {
                         /* Read the teardown status bit in the Reverse Ring Occupancy register */
                        if( CSL_lcdma_ringaccIsTeardownComplete(pCfg, ringNum) == (bool)true )
                        {
                           teardownStatus = UDMA_EVENT_CH_TEARDOWN_STATUS_COMPLETE;
                        }
                        else
                        {
                           teardownStatus = UDMA_EVENT_CH_TEARDOWN_STATUS_INCOMPLETE;
                        }
                    }

                   /* Since DMA completion and teardown completion are registered on the same event, teardown status bit in the
                   Reverse Ring Occupancy register must be used to differentiate both events. If it is a DMA Completion event,
                   the teardown status bit should not be set and if it is a teardown completion event, the teardown status bit
                   must be set */
                    if(!(((eventHandle->eventPrms.eventType == UDMA_EVENT_TYPE_DMA_COMPLETION) && (teardownStatus == UDMA_EVENT_CH_TEARDOWN_STATUS_COMPLETE)) ||
                      ((eventHandle->eventPrms.eventType == UDMA_EVENT_TYPE_TEARDOWN_COMPLETION) && (teardownStatus == UDMA_EVENT_CH_TEARDOWN_STATUS_INCOMPLETE))))
                    {
                       if((Udma_EventCallback) NULL != eventPrms->eventCb)
                       {
                           eventPrms->eventCb(
                               eventHandle, eventPrms->eventType, eventPrms->appData);
                       }
                    }
                }
            }
        }

        /* Move to next shared event */
        eventHandle = eventHandle->nextEvent;
    }

    return;
}

static int32_t Udma_eventCheckParams(Udma_DrvHandleInt drvHandle,
                                     const Udma_EventPrms *eventPrms)
{
    int32_t             retVal = UDMA_SOK;

    if(eventPrms != NULL)
    {
        /* Channel handle should be provided to reconfigure channel related event */
        if((UDMA_EVENT_TYPE_DMA_COMPLETION == eventPrms->eventType) ||
          (UDMA_EVENT_TYPE_TEARDOWN_COMPLETION == eventPrms->eventType) ||
          (UDMA_EVENT_TYPE_TEARDOWN_PACKET == eventPrms->eventType) ||
          (UDMA_EVENT_TYPE_TR == eventPrms->eventType))
        {
           if(NULL == eventPrms->chHandle)
           {
               retVal = UDMA_EINVALID_PARAMS;
               DebugP_logError("[UDMA] Channel handle should be provided for ring/ch OES programming!!!\r\n");
           }
        }

        /* Ring handle should be provided to configure ring event */
       if(UDMA_EVENT_TYPE_RING == eventPrms->eventType)
       {
           if(NULL == eventPrms->ringHandle)
           {
               retVal = UDMA_EINVALID_PARAMS;
               DebugP_logError("[UDMA] Ring handle should be provided for ring OES programming!!!\r\n");
           }
       }
    }

    return (retVal);
}

static int32_t Udma_eventCheckUnRegister(Udma_DrvHandleInt drvHandle,
                                         Udma_EventHandleInt eventHandle)
{
    int32_t             retVal = UDMA_SOK;
    Udma_EventPrms     *eventPrms;
    Udma_RingHandle     ringHandle = NULL;
    uint32_t            fOcc = 0U;
    uint32_t            rOcc = 0U;

    if(eventHandle != NULL)
    {
        if(eventHandle->eventInitDone != UDMA_INIT_DONE)
        {
          retVal = UDMA_EFAIL;
        }
    }
    else
    {
        retVal = UDMA_EBADARGS;
    }

    if(UDMA_SOK == retVal)
    {
        eventPrms = &eventHandle->eventPrms;
        /* Ring occupancies must be zero before unregistering Ring / DMA completion events.
         * This is to make sure that there is no resource leak, because unregistering
         * these events will reset the ring. */
        if((UDMA_EVENT_TYPE_DMA_COMPLETION == eventPrms->eventType) ||
           (UDMA_EVENT_TYPE_TEARDOWN_COMPLETION == eventPrms->eventType) ||
           (UDMA_EVENT_TYPE_RING == eventPrms->eventType))
        {
            if((UDMA_EVENT_TYPE_DMA_COMPLETION == eventPrms->eventType) || (UDMA_EVENT_TYPE_TEARDOWN_COMPLETION == eventPrms->eventType))
            {
                if(eventPrms->chHandle != NULL)
                {
                    ringHandle = ((Udma_ChHandleInt) (eventPrms->chHandle))->cqRing;
                }

            }
            else
            {
                ringHandle = eventPrms->ringHandle;
            }

            if(ringHandle != NULL)
            {
               fOcc = Udma_ringGetForwardRingOcc(ringHandle);
               rOcc = Udma_ringGetReverseRingOcc(ringHandle);
            }

            if((0U != fOcc) || (0U != rOcc))
            {
                retVal = UDMA_EFAIL;
                DebugP_logError("[UDMA] Can't unregister the event when descriptors are present in the ring!!!\r\n");
            }
        }
    }

    return (retVal);
}

static void Udma_eventFreeResource(Udma_DrvHandleInt drvHandle,
                                   Udma_EventHandleInt eventHandle)
{
    uintptr_t   cookie;

    /* Do atomic link list update as the same is used in ISR */
    cookie = HwiP_disable();

    HwiP_restore(cookie);

    if(NULL != eventHandle->hwiHandle)
    {
        HwiP_destruct(&eventHandle->hwiObject);
        eventHandle->hwiHandle = NULL;
    }
    if(UDMA_INTR_INVALID != eventHandle->coreIntrNum)
    {
        Udma_rmFreeIrIntr(eventHandle->coreIntrNum, drvHandle);
        eventHandle->coreIntrNum = UDMA_INTR_INVALID;
    }
    return;
}

static int32_t Udma_eventConfig(Udma_DrvHandleInt drvHandle,
                                Udma_EventHandleInt eventHandle)
{
    int32_t             retVal = UDMA_SOK;
    uint32_t            coreIntrNum;
    HwiP_Params         hwiPrms;
    Udma_EventPrms     *eventPrms;
    Udma_ChHandleInt    chHandle;
    if(eventHandle == NULL)
    {
        retVal = UDMA_EBADARGS;
    }

    if(UDMA_SOK == retVal)
    {
        eventPrms = &eventHandle->eventPrms;
        chHandle = (Udma_ChHandleInt) eventPrms->chHandle;
        /*Allocate interrupt for block copy channel*/
        if(UDMA_INST_TYPE_LCDMA_BCDMA == drvHandle->instType)
        {
            eventHandle->coreIntrNum = chHandle->chAttr.bcdmaIntNum;
            Udma_rmAllocIrIntr(eventHandle->coreIntrNum, drvHandle);
        }
        /*Allocate interrupt for packetdma channel*/
        if(UDMA_INST_TYPE_LCDMA_PKTDMA == drvHandle->instType)
        {
            if(((chHandle->chType & UDMA_CH_FLAG_MAPPED) == UDMA_CH_FLAG_MAPPED))
            {
                eventHandle->coreIntrNum = chHandle->chAttr.pktdmaIntNum + chHandle->chAttr.flowIdx;
            }
            else
            {
                eventHandle->coreIntrNum = chHandle->chAttr.pktdmaIntNum;
            }
            Udma_rmAllocIrIntr(eventHandle->coreIntrNum, drvHandle);
        }

        if(((Udma_EventCallback) NULL != eventPrms->eventCb) && (UDMA_INTR_INVALID != eventHandle->coreIntrNum))
        {
            eventHandle->flowNum = chHandle->chAttr.flowIdx;
            coreIntrNum = eventHandle->coreIntrNum;

            /* Register interrupt only when asked for */
            HwiP_Params_init(&hwiPrms);
            hwiPrms.intNum = coreIntrNum;
            hwiPrms.callback = &Udma_eventIsrFxn;
            hwiPrms.args = (void *)eventHandle;
            hwiPrms.priority = (uint8_t)eventHandle->eventPrms.intrPriority;
            retVal = HwiP_construct(&eventHandle->hwiObject, &hwiPrms);
            if(SystemP_SUCCESS != retVal)
            {
                DebugP_logError("[UDMA] Intr registration failed!!!\r\n");
            }
            else
            {
                eventHandle->hwiHandle = &eventHandle->hwiObject;
            }
        }
    }

    return (retVal);
}

int32_t Udma_eventDisable(Udma_EventHandle eventHandle)
{
    int32_t             retVal = UDMA_EFAIL;
    Udma_DrvHandleInt   drvHandle;
    Udma_ChHandleInt    chHandle;
    Udma_EventPrms     *eventPrms;
    Udma_EventHandleInt eventHandleInt = (Udma_EventHandleInt) eventHandle;
    CSL_LcdmaRingaccCfg *pCfg;
    uint32_t regVal, flowNum;

    if((NULL != eventHandleInt) &&
       (UDMA_INIT_DONE == eventHandleInt->eventInitDone))
    {
        drvHandle = eventHandleInt->drvHandle;
        eventPrms = &eventHandleInt->eventPrms;

        if((NULL != drvHandle) && (eventPrms->chHandle != NULL))
        {          
            chHandle = (Udma_ChHandleInt) eventPrms->chHandle;  
            pCfg = &drvHandle->lcdmaRaRegs;
            if(((chHandle->chType & UDMA_CH_FLAG_MAPPED) == UDMA_CH_FLAG_MAPPED) &&
                ((chHandle->chType & UDMA_CH_FLAG_RX) == UDMA_CH_FLAG_RX))
            {
                flowNum = chHandle->rxChNum + eventHandleInt->flowNum;
            }
            else
            {
                flowNum = chHandle->txChNum + eventHandleInt->flowNum;
            }
            /* Clear the interrupt */
            regVal = CSL_lcdmaGetInterrupt(pCfg, flowNum);
            CSL_lcdmaClrInterrupt(pCfg, flowNum, regVal);
            retVal = UDMA_SOK;
        }
    }

    return (retVal);
}

int32_t Udma_eventEnable(Udma_EventHandle eventHandle)
{
    int32_t             retVal = UDMA_EFAIL, flowNum;
    Udma_DrvHandleInt   drvHandle;
    Udma_ChHandleInt    chHandle;
    Udma_EventPrms     *eventPrms;
    Udma_EventHandleInt eventHandleInt = (Udma_EventHandleInt) eventHandle;
    CSL_LcdmaRingaccCfg *pCfg;

    if((NULL != eventHandleInt) &&
       (UDMA_INIT_DONE == eventHandleInt->eventInitDone))
    {
        drvHandle = eventHandleInt->drvHandle;
        eventPrms = &eventHandleInt->eventPrms;

        if((NULL != drvHandle) && (eventPrms->chHandle != NULL))
        {
            chHandle = (Udma_ChHandleInt) eventPrms->chHandle;
            pCfg = &drvHandle->lcdmaRaRegs;
            if(((chHandle->chType & UDMA_CH_FLAG_MAPPED) == UDMA_CH_FLAG_MAPPED) &&
                ((chHandle->chType & UDMA_CH_FLAG_RX) == UDMA_CH_FLAG_RX))
            {
                flowNum = chHandle->rxChNum + eventHandleInt->flowNum;
            }
            else
            {
                flowNum = chHandle->txChNum + eventHandleInt->flowNum;
            }

            /* Enable the interrupt */
            CSL_lcdmaSetInterrupt(pCfg, flowNum, UDMA_SET_COMP_INT, true);

            retVal = UDMA_SOK;
        }
    }
    return (retVal);
}

Udma_EventHandle Udma_eventGetGlobalHandle(Udma_DrvHandle drvHandle)
{
    int32_t             retVal = UDMA_SOK;
    Udma_DrvHandleInt   drvHandleInt;
    Udma_EventHandle    eventHandle = (Udma_EventHandle) NULL;

    /* Error check */
    if(NULL == drvHandle)
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandleInt = (Udma_DrvHandleInt) drvHandle;
        if(drvHandleInt->drvInitDone != UDMA_INIT_DONE)
        {
            retVal = UDMA_EFAIL;
        }
    }
    if(UDMA_SOK == retVal)
    {
        eventHandle = (Udma_EventHandle) drvHandleInt->globalEventHandle;
    }

    return (eventHandle);
}