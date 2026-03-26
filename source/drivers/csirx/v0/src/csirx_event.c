/*
 *  Copyright (c) Texas Instruments Incorporated 2022-25
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
 *  \file csirx_event.c
 *
 *  \brief File containing the CSIRX driver event management functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <drivers/csirx/v0/include/csirx_drvPriv.h>
#include <kernel/dpl/ClockP.h>
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
extern CsirxDrv_CommonObj gCsirxCommonObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
static void CsirxDrv_errorEventIsrFxn(void* arg);
static void CsirxDrv_infoEventIsrFxn(void* arg);
static int32_t CsirxDrv_eventValidateParams(const Csirx_EventPrms *eventPrms,
                                            CsirxDrv_InstObj *instObj);
static int32_t CsirxDrv_eventGroupAllocResource(CsirxDrv_InstObj *instObj,
                                                Csirx_EventPrms *eventPrms);
static int32_t CsirxDrv_resetStream(const CsirxDrv_InstObj *instObj,
                                    uint32_t strmIdx);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void Csirx_eventPrmsInit(Csirx_EventPrms *eventPrms)
{
    if (eventPrms != NULL)
    {
        eventPrms->eventGroup           = CSIRX_EVENT_GROUP_ERROR;
        eventPrms->eventMasks           = CSIRX_EVENT_TYPE_ERR_ALL;
        eventPrms->eventCb              = NULL;
        eventPrms->coreIntrNum          = CSIRX_INTR_INVALID;
        eventPrms->intrPriority         = 0U;
        eventPrms->appData              = NULL;
    }
}

int32_t CsirxDrv_eventGroupRegister(Fdrv_Handle drvHandle,
                                    Csirx_EventPrms *eventPrms)
{
    int32_t retVal = FVID2_SOK;
    CsirxDrv_InstObj *instObj = NULL;
    CsirxDrv_EventObj *eventObj;
    CsirxDrv_VirtContext *virtContext;
    HwiP_Params hwiParams;

    /* Error Check: Parameters */
    GT_assert(CsirxTrace, (drvHandle != NULL_PTR));
    GT_assert(CsirxTrace, (eventPrms != NULL_PTR));

    virtContext = (CsirxDrv_VirtContext *) drvHandle;
    instObj = virtContext->instObj;
    if (instObj->inUse != CSIRX_DRV_USAGE_STATUS_IN_USE)
    {
        retVal = FVID2_EFAIL;
    }

        /* Pend on the instance semaphore */
        (void)SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);

    if (retVal == FVID2_SOK)
    {
        /* Configure more events if not already configured during previous
           open instances, not needed currently as only Error types of
           events are supported */
        /* In case of configured events, check new params with
           configured one*/
        retVal = CsirxDrv_eventValidateParams(eventPrms, instObj);
    }

    if (retVal == FVID2_SOK)
    {
        eventObj = &instObj->eventObj[eventPrms->eventGroup];
        /* Only allow event registration on first call */
        /* Configure events only if not configured in previous open calls */
        if (eventObj->eventInitDone == 0U)
        {
            /* Copy event configuration parameters to driver object */
            switch (eventPrms->eventGroup)
            {
                case CSIRX_EVENT_GROUP_ERROR:
                    Fvid2Utils_memcpy(&eventObj->eventPrms,
                                      eventPrms,
                                      sizeof(Csirx_EventPrms));
                break;
                case CSIRX_EVENT_GROUP_INFO:
                    Fvid2Utils_memcpy(&eventObj->eventPrms,
                                      eventPrms,
                                      sizeof(Csirx_EventPrms));
                break;
                default:
                break;
            }
            /* Copy driver handle to event object */
            eventObj->drvHandle = drvHandle;
            /* Allocate resource to the event group */
            retVal = CsirxDrv_eventGroupAllocResource(instObj, eventPrms);
            if (retVal == FVID2_SOK)
            {
		                    /* Populate the interrupt parameters */
                HwiP_Params_init(&hwiParams);
                hwiParams.args = (void*) eventObj;
                hwiParams.intNum = eventObj->coreIntrNum;
                if (CSIRX_EVENT_GROUP_ERROR == eventPrms->eventGroup)
                {
                    hwiParams.callback = CsirxDrv_errorEventIsrFxn;
                }
                else if (CSIRX_EVENT_GROUP_INFO == eventPrms->eventGroup)
                {
                    hwiParams.callback = CsirxDrv_infoEventIsrFxn;
                }
                /* Register interrupt */
                if ( HwiP_construct(&eventObj->hwiHandle, &hwiParams) !=
                                            SystemP_SUCCESS)
                {
                    retVal = FVID2_EFAIL;
                }

            }
            if (retVal == FVID2_SOK)
            {
                /* Enable respective events */
                retVal = CsirxDrv_eventEnable(drvHandle,
                                              eventPrms->eventGroup,
                                              eventPrms->eventMasks);
            }
            if (retVal == FVID2_SOK)
            {
                eventObj->eventInitDone = 1U;
            }
        }
    }
        /* Post the instance semaphore */
        (void)SemaphoreP_post(&instObj->lockSem);

    return retVal;
}

static int32_t CsirxDrv_eventValidateParams(const Csirx_EventPrms *eventPrms,
                                            CsirxDrv_InstObj *instObj)
{
    int32_t retVal = FVID2_SOK;
    CsirxDrv_EventObj *eventObj;

    if ((eventPrms->eventMasks == 0U) &&
        (eventPrms->eventGroup >= CSIRX_EVENT_GROUP_MAX))
    {
        retVal = FVID2_EBADARGS;
    }
    if (retVal == FVID2_SOK)
    {
        eventObj = &instObj->eventObj[eventPrms->eventGroup];
        if (eventObj->eventInitDone == 1U)
        {
            /* check against configured parameters */
            if ((eventObj->eventPrms.eventGroup == eventPrms->eventGroup) &&
                (eventObj->eventPrms.eventMasks == eventPrms->eventMasks) &&
                (eventObj->eventPrms.eventCb == eventPrms->eventCb) &&
                (eventObj->eventPrms.intrPriority == eventPrms->intrPriority))
            {
                /* Configuration matches, do nothing */
            }
            else
            {
                retVal = FVID2_WNON_RECOMMENDED_PARAMS;
            }
        }
    }
    else
    {
        /* Do nothing */
    }

    return retVal;
}

static int32_t CsirxDrv_eventGroupAllocResource(CsirxDrv_InstObj *instObj,
                                                Csirx_EventPrms *eventPrms)
{
    int32_t retVal = FVID2_SOK;

    eventPrms->coreIntrNum = CSIRX_INTR_INVALID;
    switch (instObj->drvInstId)
    {
        case CSIRX_INSTANCE_ID_0:
            switch (eventPrms->eventGroup)
            {
                case CSIRX_EVENT_GROUP_ERROR:
                #if defined (SOC_J722S)
                    eventPrms->coreIntrNum = CSIRX_CORE_INTR_NUM_MOD_0_ERR_INTR;
                #endif
                #if defined (SOC_AM62AX)
                    eventPrms->coreIntrNum = CSIRX_CORE_INTR_NUM_MOD_0_FATAL_INTR; /* CSI_RX_IF0_COMMON_0_CSI_ERR_IRQ_0 is not available for DM R5, CSI_RX_IF0_COMMON_0_CSI_FATAL_0=172 used instead */
                #endif
                break;
                case CSIRX_EVENT_GROUP_INFO:
                #if defined (SOC_J722S)
                    eventPrms->coreIntrNum = CSIRX_CORE_INTR_NUM_MOD_0_INFO_INTR;
                #endif
                break;
                default:
                    retVal = FVID2_EBADARGS;
                break;
            }
        break;
    #if defined (SOC_J722S) /* AM62A only supports 1 CSIRX Instance */
        case CSIRX_INSTANCE_ID_1:
            switch (eventPrms->eventGroup)
            {
                case CSIRX_EVENT_GROUP_ERROR:
                    eventPrms->coreIntrNum = CSIRX_CORE_INTR_NUM_MOD_1_ERR_INTR;
                break;
                case CSIRX_EVENT_GROUP_INFO:
                    eventPrms->coreIntrNum = CSIRX_CORE_INTR_NUM_MOD_1_INFO_INTR;
                break;
                default:
                    retVal = FVID2_EBADARGS;
                break;
            }
        break;
        case CSIRX_INSTANCE_ID_2:
            switch (eventPrms->eventGroup)
            {
                case CSIRX_EVENT_GROUP_ERROR:
                    eventPrms->coreIntrNum = CSIRX_CORE_INTR_NUM_MOD_2_ERR_INTR;
                break;
                case CSIRX_EVENT_GROUP_INFO:
                    eventPrms->coreIntrNum = CSIRX_CORE_INTR_NUM_MOD_2_INFO_INTR;
                break;
                default:
                    retVal = FVID2_EBADARGS;
                break;
            }
        break;
        case CSIRX_INSTANCE_ID_3:
            switch (eventPrms->eventGroup)
            {
                case CSIRX_EVENT_GROUP_ERROR:
                    eventPrms->coreIntrNum = CSIRX_CORE_INTR_NUM_MOD_3_ERR_INTR;
                break;
                default:
                    retVal = FVID2_EBADARGS;
                break;
            }
        break;
    #endif
        default:
            retVal = FVID2_EBADARGS;
        break;
    }
    instObj->eventObj[eventPrms->eventGroup].coreIntrNum =
                                                    eventPrms->coreIntrNum;

    return retVal;
}

int32_t CsirxDrv_eventEnable(Fdrv_Handle drvHandle,
                             uint32_t eventGroup,
                             uint32_t eventType)
{
    int32_t retVal = FVID2_SOK;
    CsirxDrv_InstObj *instObj;
    CSIRX_ErrorIrqsMaskCfg errMask;
    CSIRX_InfoIrqsMaskCfg infoMask;
    CsirxDrv_VirtContext *virtContext;

    switch (eventGroup)
    {
        case CSIRX_EVENT_GROUP_ERROR:
            virtContext = (CsirxDrv_VirtContext *) drvHandle;
            instObj = virtContext->instObj;
            if (CSIRX_GetErrorIrqsMaskCfg(&instObj->cslObj.cslCfgData,
                                          &errMask) != CDN_EOK)
            {
                retVal = FVID2_EFAIL;
            }
            if (retVal == FVID2_SOK)
            {
                errMask.frontFifoOverflowIrqm  |= (uint8_t)
                        ((eventType & CSIRX_EVENT_TYPE_ERR_FIFO_OVERFLOW_FRONT) >>
                         CSL_CSIRX_ERROR_IRQS_FRONT_FIFO_OVERFLOW_IRQ_SHIFT);
                errMask.payloadCrcIrqm         |= (uint8_t)
                        ((eventType & CSIRX_EVENT_TYPE_ERR_PAYLOAD_CRC) >>
                         CSL_CSIRX_ERROR_IRQS_PAYLOAD_CRC_IRQ_SHIFT);
                errMask.headerEccIrqm          |= (uint8_t)
                        ((eventType & CSIRX_EVENT_TYPE_ERR_HEADER_ECC) >>
                         CSL_CSIRX_ERROR_IRQS_HEADER_ECC_IRQ_SHIFT);
                errMask.headerCorrectedEccIrqm |= (uint8_t)
                        ((eventType & CSIRX_EVENT_TYPE_ERR_HEADER_CORRECTED_ECC) >>
                         CSL_CSIRX_ERROR_IRQS_HEADER_CORRECTED_ECC_IRQ_SHIFT);
                errMask.dataIdIrqm             |= (uint8_t)
                        ((eventType & CSIRX_EVENT_TYPE_ERR_DATA_ID) >>
                         CSL_CSIRX_ERROR_IRQS_DATA_ID_IRQ_SHIFT);
                errMask.invalidAccessIrqm      |= (uint8_t)
                        ((eventType & CSIRX_EVENT_TYPE_ERR_INVALID_ACCESS) >>
                         CSL_CSIRX_ERROR_IRQS_INVALID_ACCESS_IRQ_SHIFT);
                errMask.spInvalidRcvdIrqm      |= (uint8_t)
                        ((eventType & CSIRX_EVENT_TYPE_ERR_INVALID_SHORT_PACKET) >>
                         CSL_CSIRX_ERROR_IRQS_SP_INVALID_RCVD_IRQ_SHIFT);
                errMask.fifoOverflowIrqm[0U]   |= (uint8_t)
                        ((eventType & CSIRX_EVENT_TYPE_ERR_FIFO_OVERFLOW_STRM0) >>
                         CSL_CSIRX_ERROR_IRQS_STREAM0_FIFO_OVERFLOW_IRQ_SHIFT);
                errMask.fifoOverflowIrqm[1U]   |= (uint8_t)
                        ((eventType & CSIRX_EVENT_TYPE_ERR_FIFO_OVERFLOW_STRM1) >>
                         CSL_CSIRX_ERROR_IRQS_STREAM1_FIFO_OVERFLOW_IRQ_SHIFT);
                errMask.fifoOverflowIrqm[2U]   |= (uint8_t)
                        ((eventType & CSIRX_EVENT_TYPE_ERR_FIFO_OVERFLOW_STRM2) >>
                         CSL_CSIRX_ERROR_IRQS_STREAM2_FIFO_OVERFLOW_IRQ_SHIFT);
                errMask.fifoOverflowIrqm[3U]   |= (uint8_t)
                        ((eventType & CSIRX_EVENT_TYPE_ERR_FIFO_OVERFLOW_STRM3) >>
                         CSL_CSIRX_ERROR_IRQS_STREAM3_FIFO_OVERFLOW_IRQ_SHIFT);

                if (CSIRX_SetErrorIrqsMaskCfg(&instObj->cslObj.cslCfgData,
                                              &errMask) != CDN_EOK)
                {
                    retVal = FVID2_EFAIL;
                }
            }
        break;
        case CSIRX_EVENT_GROUP_INFO:
            virtContext = (CsirxDrv_VirtContext *) drvHandle;
            instObj = virtContext->instObj;
            if (CDN_EOK != CSIRX_GetInfoIrqsMaskCfg(&instObj->cslObj.cslCfgData,
                                          &infoMask))
            {
                retVal = FVID2_EFAIL;
            }
            if (FVID2_SOK == retVal)
            {
                infoMask.deskewEntryIrqm  |= (uint8_t)
                        ((eventType & CSIRX_EVENT_TYPE_INFO_DESKEW_ENTRY) >>
                         CSL_CSIRX_INFO_IRQS_MASK_CFG_DESKEW_ENTRY_IRQM_SHIFT);

                if (CDN_EOK != CSIRX_SetInfoIrqsMaskCfg(&instObj->cslObj.cslCfgData,
                                              &infoMask))
                {
                    retVal = FVID2_EFAIL;
                }
            }
        break;
        default:
            retVal = FVID2_EBADARGS;
        break;
    }

    return retVal;
}

int32_t CsirxDrv_eventDisable(Fdrv_Handle drvHandle,
                              uint32_t eventGroup,
                              uint32_t eventType)
{
    int32_t retVal = FVID2_SOK;
    CsirxDrv_InstObj *instObj;
    CSIRX_ErrorIrqsMaskCfg errMask;
    CSIRX_InfoIrqsMaskCfg infoMask;

    instObj = (CsirxDrv_InstObj *) drvHandle;
    switch (eventGroup)
    {
        case CSIRX_EVENT_GROUP_ERROR:
            if (CSIRX_GetErrorIrqsMaskCfg(&instObj->cslObj.cslCfgData,
                                          &errMask) != CDN_EOK)
            {
                retVal = FVID2_EFAIL;
            }
            if (retVal == FVID2_SOK)
            {
                errMask.frontFifoOverflowIrqm  &= (uint8_t)
                        (~((eventType & CSIRX_EVENT_TYPE_ERR_FIFO_OVERFLOW_FRONT) >>
                         CSL_CSIRX_ERROR_IRQS_FRONT_FIFO_OVERFLOW_IRQ_SHIFT));
                errMask.payloadCrcIrqm         &= (uint8_t)
                        (~((eventType & CSIRX_EVENT_TYPE_ERR_PAYLOAD_CRC) >>
                         CSL_CSIRX_ERROR_IRQS_PAYLOAD_CRC_IRQ_SHIFT));
                errMask.headerEccIrqm          &= (uint8_t)
                        (~((eventType & CSIRX_EVENT_TYPE_ERR_HEADER_ECC) >>
                         CSL_CSIRX_ERROR_IRQS_HEADER_ECC_IRQ_SHIFT));
                errMask.headerCorrectedEccIrqm &= (uint8_t)
                        (~((eventType & CSIRX_EVENT_TYPE_ERR_HEADER_CORRECTED_ECC) >>
                         CSL_CSIRX_ERROR_IRQS_HEADER_CORRECTED_ECC_IRQ_SHIFT));
                errMask.dataIdIrqm             &= (uint8_t)
                        (~((eventType & CSIRX_EVENT_TYPE_ERR_DATA_ID) >>
                         CSL_CSIRX_ERROR_IRQS_DATA_ID_IRQ_SHIFT));
                errMask.invalidAccessIrqm      &= (uint8_t)
                        (~((eventType & CSIRX_EVENT_TYPE_ERR_INVALID_ACCESS) >>
                         CSL_CSIRX_ERROR_IRQS_INVALID_ACCESS_IRQ_SHIFT));
                errMask.spInvalidRcvdIrqm      &= (uint8_t)
                        (~((eventType & CSIRX_EVENT_TYPE_ERR_INVALID_SHORT_PACKET) >>
                         CSL_CSIRX_ERROR_IRQS_SP_INVALID_RCVD_IRQ_SHIFT));
                errMask.fifoOverflowIrqm[0U]   &= (uint8_t)
                        (~((eventType & CSIRX_EVENT_TYPE_ERR_FIFO_OVERFLOW_STRM0) >>
                         CSL_CSIRX_ERROR_IRQS_STREAM0_FIFO_OVERFLOW_IRQ_SHIFT));
                errMask.fifoOverflowIrqm[1U]   &= (uint8_t)
                        (~((eventType & CSIRX_EVENT_TYPE_ERR_FIFO_OVERFLOW_STRM1) >>
                         CSL_CSIRX_ERROR_IRQS_STREAM1_FIFO_OVERFLOW_IRQ_SHIFT));
                errMask.fifoOverflowIrqm[2U]   &= (uint8_t)
                        (~((eventType & CSIRX_EVENT_TYPE_ERR_FIFO_OVERFLOW_STRM2) >>
                         CSL_CSIRX_ERROR_IRQS_STREAM2_FIFO_OVERFLOW_IRQ_SHIFT));
                errMask.fifoOverflowIrqm[3U]   &= (uint8_t)
                        (~((eventType & CSIRX_EVENT_TYPE_ERR_FIFO_OVERFLOW_STRM3) >>
                         CSL_CSIRX_ERROR_IRQS_STREAM3_FIFO_OVERFLOW_IRQ_SHIFT));

                if (CSIRX_SetErrorIrqsMaskCfg(&instObj->cslObj.cslCfgData,
                                              &errMask) != CDN_EOK)
                {
                    retVal = FVID2_EFAIL;
                }
            }
        break;
        case CSIRX_EVENT_GROUP_INFO:
            if (CDN_EOK != CSIRX_GetInfoIrqsMaskCfg(&instObj->cslObj.cslCfgData,
                                          &infoMask))
            {
                retVal = FVID2_EFAIL;
            }
            if (FVID2_SOK == retVal)
            {
                infoMask.deskewEntryIrqm  &= (uint8_t)
                        (~((eventType & CSIRX_EVENT_TYPE_INFO_DESKEW_ENTRY) >>
                         CSL_CSIRX_INFO_IRQS_MASK_CFG_DESKEW_ENTRY_IRQM_SHIFT));

                if (CDN_EOK != CSIRX_SetInfoIrqsMaskCfg(&instObj->cslObj.cslCfgData,
                                              &infoMask))
                {
                    retVal = FVID2_EFAIL;
                }
            }
        break;
        default:
            retVal = FVID2_EBADARGS;
        break;
    }

    return retVal;
}

static void CsirxDrv_errorEventIsrFxn(void* arg)
{
    CsirxDrv_InstObj *instObj;
    CsirxDrv_EventObj *eventObj;
    Csirx_EventStatus status;
    CSIRX_ErrorIrqs errStatus;
    CSIRX_SoftReset resetType;
    CSIRX_ErrorDebug errInfo;
    uint32_t strmIdx, cookie;
    CsirxDrv_VirtContext *virtContext;

    eventObj = (CsirxDrv_EventObj *)arg;
    virtContext = (CsirxDrv_VirtContext *) eventObj->drvHandle;
    instObj = virtContext->instObj;
    status.eventGroup = CSIRX_EVENT_GROUP_ERROR;
    status.eventMasks = 0U;
    status.drvHandle  = eventObj->drvHandle;
    /* Disable HW interrupts here */
    cookie = HwiP_disable();
    /* Check of event status */
    GT_assert(CsirxTrace,
             (CSIRX_GetErrorIrqs(&instObj->cslObj.cslCfgData,
                                        &errStatus) == CDN_EOK));
    /* Clear Event status */
    GT_assert(CsirxTrace,
            (CSIRX_SetErrorIrqs(&instObj->cslObj.cslCfgData,
                                        &errStatus) == CDN_EOK));

#if (CSIRX_DRV_ENABLE_DEBUG == 1U)
    uint32_t oldEventCnt;

    oldEventCnt = gCsirxCommonObj.eventCnt;
    gCsirxCommonObj.eventInstId[gCsirxCommonObj.eventCnt] = instObj->drvInstId;
    /* Read register status directly */
    gCsirxCommonObj.eventStatus[gCsirxCommonObj.eventCnt] =
            CSL_REG32_RD(&instObj->cslObj.configParams.regBase->error_irqs);
    if (gCsirxCommonObj.getTimeStamp != NULL)
    {
        gCsirxCommonObj.eventTS[gCsirxCommonObj.eventCnt] =
                    (uint32_t)(gCsirxCommonObj.getTimeStamp(NULL) / 1000U);
    }
    gCsirxCommonObj.eventCnt = (gCsirxCommonObj.eventCnt + 1U) %
                              CSIRX_DRV_LOG_CNT;
    if (oldEventCnt > gCsirxCommonObj.eventCnt)
    {
        gCsirxCommonObj.eventCntOverflow = 1U;
    }
#endif

    /* Service pending events */
    if (errStatus.frontFifoOverflowIrq == 1U)
    {
        /* Front FIFO Overflow */
        /* Reset front */
        resetType.protocol = 0U;
        resetType.front    = 1U;
        GT_assert(CsirxTrace,
                 (CSIRX_SetSoftReset(&instObj->cslObj.cslCfgData,
                                        &resetType) == CDN_EOK));
        status.eventMasks |= CSIRX_EVENT_TYPE_ERR_FIFO_OVERFLOW_FRONT;
        instObj->status.frontFIFOOvflCount++;
    }
    if (errStatus.payloadCrcIrq == 1U)
    {
        /* Get vc and dt info */
        GT_assert(CsirxTrace,
                (CSIRX_GetErrorDebug(&instObj->cslObj.cslCfgData,
                                        &errInfo) == CDN_EOK));
        status.eventMasks |= CSIRX_EVENT_TYPE_ERR_PAYLOAD_CRC;
        instObj->status.crcCount++;
    }
    if (errStatus.headerEccIrq == 1U)
    {
        for (strmIdx = 0U ; strmIdx < CSIRX_NUM_STREAM ; strmIdx++)
        {
            /* Reset streams */
            GT_assert(CsirxTrace,
                      (CsirxDrv_resetStream(instObj, strmIdx) == FVID2_SOK));
        }
        status.eventMasks |= CSIRX_EVENT_TYPE_ERR_HEADER_ECC;
        instObj->status.eccCount++;
    }
    if (errStatus.headerCorrectedEccIrq == 1U)
    {
        /* Nothing to be done here as it is corrected ECC Error */
        status.eventMasks |= CSIRX_EVENT_TYPE_ERR_HEADER_CORRECTED_ECC;
        instObj->status.correctedEccCount++;
    }
    if (errStatus.dataIdIrq == 1U)
    {
        /* Nothing to be done here as it is invalid data type has received.
           This will not affect current capture. */
        status.eventMasks |= CSIRX_EVENT_TYPE_ERR_DATA_ID;
        instObj->status.dataIdErrorCount++;
    }
    if (errStatus.invalidAccessIrq == 1U)
    {
        /* Nothing to be done here */
        status.eventMasks |= CSIRX_EVENT_TYPE_ERR_INVALID_ACCESS;
        instObj->status.invalidAccessCount++;
    }
    if (errStatus.spInvalidRcvdIrq == 1U)
    {
        /* Nothing to be done here */
        status.eventMasks |= CSIRX_EVENT_TYPE_ERR_INVALID_SHORT_PACKET;
        instObj->status.invalidSpCount++;
    }
    if (errStatus.fifoOverflowIrq[0U] == 1U)
    {
        GT_assert(CsirxTrace,
                      (CsirxDrv_resetStream(instObj, 0U) == FVID2_SOK));
        status.eventMasks |= CSIRX_EVENT_TYPE_ERR_FIFO_OVERFLOW_STRM0;
        instObj->status.strmFIFOOvflCount[0U]++;
    }
    if (errStatus.fifoOverflowIrq[1U] == 1U)
    {
        GT_assert(CsirxTrace,
                      (CsirxDrv_resetStream(instObj, 1U) == FVID2_SOK));
        status.eventMasks |= CSIRX_EVENT_TYPE_ERR_FIFO_OVERFLOW_STRM1;
        if (CSIRX_NUM_STREAM > 1U)
        {
            instObj->status.strmFIFOOvflCount[1U]++;
        }
    }
    if (errStatus.fifoOverflowIrq[2U] == 1U)
    {
        GT_assert(CsirxTrace,
                      (CsirxDrv_resetStream(instObj, 2U) == FVID2_SOK));
        status.eventMasks |= CSIRX_EVENT_TYPE_ERR_FIFO_OVERFLOW_STRM2;
        if (CSIRX_NUM_STREAM > 2U)
        {
            instObj->status.strmFIFOOvflCount[2U]++;
        }
    }
    if (errStatus.fifoOverflowIrq[3U] == 1U)
    {
        GT_assert(CsirxTrace,
                      (CsirxDrv_resetStream(instObj, 3U) == FVID2_SOK));
        status.eventMasks |= CSIRX_EVENT_TYPE_ERR_FIFO_OVERFLOW_STRM3;
        if (CSIRX_NUM_STREAM > 3U)
        {
            instObj->status.strmFIFOOvflCount[3U]++;
        }
    }

    /** Enable HW interrupts here */
    HwiP_restore(cookie);

    if ((eventObj->eventPrms.eventCb != NULL) && (status.eventMasks != 0U))
    {
        /* Issue a CB to application */
        eventObj->eventPrms.eventCb(status, eventObj->eventPrms.appData);
    }
}

static void CsirxDrv_infoEventIsrFxn(void* arg)
{
    CsirxDrv_InstObj *instObj;
    CsirxDrv_EventObj *eventObj;
    Csirx_EventStatus status;
    CSIRX_InfoIrqs infoStatus;
    uint32_t cookie;
    CsirxDrv_VirtContext *virtContext;

    eventObj = (CsirxDrv_EventObj *)arg;
    virtContext = (CsirxDrv_VirtContext *) eventObj->drvHandle;
    instObj = virtContext->instObj;
    status.eventGroup = CSIRX_EVENT_GROUP_INFO;
    status.eventMasks = 0U;
    status.drvHandle  = eventObj->drvHandle;
    /* Disable HW interrupts here */
    cookie = HwiP_disable();
    /* Check of event status */
    GT_assert(CsirxTrace,
             (CDN_EOK == CSIRX_GetInfoIrqs(&instObj->cslObj.cslCfgData,
                                            &infoStatus)));
    /* Clear Event status */
    GT_assert(CsirxTrace,
            (CDN_EOK == CSIRX_SetInfoIrqs(&instObj->cslObj.cslCfgData,
                                           &infoStatus)));

    /* Service pending events */
    if (1U == infoStatus.deskewEntryIrq)
    {
        status.eventMasks |= CSIRX_EVENT_TYPE_INFO_DESKEW_ENTRY;
        instObj->status.deSkewEntryCount++;
    }

    /** Enable HW interrupts here */
    HwiP_restore(cookie);

    if ((NULL != eventObj->eventPrms.eventCb) && (0U != status.eventMasks))
    {
        /* Issue a CB to application */
        eventObj->eventPrms.eventCb(status, eventObj->eventPrms.appData);
    }
}

static int32_t CsirxDrv_resetStream(const CsirxDrv_InstObj *instObj,
                                    uint32_t strmIdx)
{
    int32_t retVal = FVID2_SOK;
    CSIRX_StreamStatus strmStatus;
    CSIRX_StreamCtrl strmCtrlParams;
    uint32_t status, currTimeout = 0U;

    /* check if stream is enabled */
    if (CSIRX_GetStreamStatus(&instObj->cslObj.cslCfgData,
                              &strmStatus,
                              strmIdx) != CDN_EOK)
    {
        retVal = FVID2_EFAIL;
    }
    /* Reset stream */
    if (retVal == FVID2_SOK)
    {
        if (strmStatus.running == 1U)
        {
            /* Stream is enabled */
            strmCtrlParams.softRst = 1U;
            strmCtrlParams.abrt    = 0U;
            strmCtrlParams.stop    = 0U;
            strmCtrlParams.start   = 0U;
            status = CSIRX_SetStreamCtrl(&instObj->cslObj.cslCfgData,
                                         &strmCtrlParams,
                                         strmIdx);
            if (status != 0U)
            {
                retVal = FVID2_EBADARGS;
            }
            currTimeout = 0U;
            status = CSIRX_GetStreamStatus(&instObj->cslObj.cslCfgData,
                                           &strmStatus,
                                           strmIdx);
            if (status != 0U)
            {
                retVal = FVID2_EBADARGS;
            }
            /* Wait for stream to become IDLE */
            while ((strmStatus.readyState != 0x0U) &&
                   (strmStatus.streamFsm  != 0x0U) &&
                   (retVal == FVID2_SOK))
            {
                 status = CSIRX_GetStreamStatus(&instObj->cslObj.cslCfgData,
                                           &strmStatus,
                                           strmIdx);
                if (status != 0U)
                {
                    retVal = FVID2_EBADARGS;
                    break;
                }
                if (currTimeout > CSIRX_TIMEOUT_VAL_MS)
                {
                    retVal = FVID2_ETIMEOUT;
                }
                else
                {
                    (void)ClockP_sleep(1U);
                    currTimeout++;
                }
            }
        }
    }
    /* Re-start stream */
    if (retVal == FVID2_SOK)
    {
        strmCtrlParams.softRst = 0U;
        strmCtrlParams.abrt    = 0U;
        strmCtrlParams.stop    = 0U;
        strmCtrlParams.start   = 1U;
        status = CSIRX_SetStreamCtrl(&instObj->cslObj.cslCfgData,
                                     &strmCtrlParams,
                                     strmIdx);
        if (status != 0U)
        {
            retVal = FVID2_EBADARGS;
        }
    }

    return retVal;
}

int32_t CsirxDrv_eventGroupUnRegister(Fdrv_Handle drvHandle,
                                      uint32_t eventGroup)
{
    int32_t retVal = FVID2_SOK;
    CsirxDrv_InstObj *instObj = NULL;
    CsirxDrv_EventObj *eventObj;
    CsirxDrv_VirtContext *virtContext;

    /* Error Check: Parameters */
    GT_assert(CsirxTrace, (drvHandle != NULL_PTR));
    virtContext = (CsirxDrv_VirtContext *) drvHandle;
    instObj = virtContext->instObj;
    eventObj = &instObj->eventObj[eventGroup];
    if (instObj->inUse != CSIRX_DRV_USAGE_STATUS_IN_USE)
    {
        retVal = FVID2_EFAIL;
    }
        /* Pend on the instance semaphore */
        (void)SemaphoreP_pend(&instObj->lockSem, SystemP_WAIT_FOREVER);
    if (drvHandle == eventObj->drvHandle)
    {
        /* Only let instance which registered events to unregister them, for
           others this will be empty call */
        if (retVal == FVID2_SOK)
        {
            /* Disable All HW events for the given group first */
            retVal = CsirxDrv_eventDisable(drvHandle, eventGroup, eventObj->eventPrms.eventMasks);
        }
        if (retVal == FVID2_SOK)
        {
            /* Disable Core interrupts */
            /* Delete interrupts: TODO: 0U in following call should be core based */
            HwiP_destruct(&eventObj->hwiHandle);
            eventObj = &instObj->eventObj[eventGroup];
            eventObj->coreIntrNum   = CSIRX_INTR_INVALID;
            eventObj->eventInitDone = 0U;
        }

    }
        /* Post the instance semaphore */
        (void)SemaphoreP_post(&instObj->lockSem);

    return retVal;
}
