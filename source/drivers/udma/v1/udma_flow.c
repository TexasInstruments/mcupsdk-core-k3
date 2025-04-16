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
 *  \file udma_flow.c
 *
 *  \brief File containing the UDMA driver flow related APIs.
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

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t Udma_flowFree(Udma_FlowHandle flowHandle)
{
    int32_t             retVal = UDMA_SOK;
    Udma_DrvHandleInt   drvHandle;
    Udma_FlowHandleInt  flowHandleInt = (Udma_FlowHandleInt) flowHandle;

    /* Error check */
    if(NULL == flowHandleInt)
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        if(flowHandleInt->flowInitDone != UDMA_INIT_DONE)
        {
            retVal = UDMA_EFAIL;
        }
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = flowHandleInt->drvHandle;
        if((NULL == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        if(UDMA_MAPPED_GROUP_INVALID == flowHandleInt->mappedFlowGrp)
        {
            retVal = UDMA_EFAIL;
        }
        else
        {
            /* Free Mapped Ring in devices like AM64x */
#if((UDMA_NUM_MAPPED_TX_GROUP + UDMA_NUM_MAPPED_RX_GROUP) > 0)
            /* Add RX Ring Number Offset */
            Udma_rmFreeFreeRing(
                flowHandleInt->flowStart,
                drvHandle);
#else
            retVal = UDMA_EFAIL;
#endif
        }

        flowHandleInt->drvHandle    = (Udma_DrvHandleInt) NULL;
        flowHandleInt->flowStart    = UDMA_FLOW_INVALID;
        flowHandleInt->flowCnt      = 0U;
        flowHandleInt->flowInitDone = UDMA_DEINIT_DONE;
        flowHandleInt->mappedFlowGrp= UDMA_MAPPED_GROUP_INVALID;
        flowHandleInt->mappedChNum  = UDMA_DMA_CH_INVALID;
    }

    return (retVal);
}

int32_t Udma_flowAttach(Udma_DrvHandle drvHandle,
                        Udma_FlowHandle flowHandle,
                        uint32_t flowStart,
                        uint32_t flowCnt)
{
    int32_t             retVal = UDMA_SOK;
    Udma_DrvHandleInt   drvHandleInt = (Udma_DrvHandleInt) drvHandle;
    Udma_FlowHandleInt  flowHandleInt = (Udma_FlowHandleInt) flowHandle;

    /* Error check */
    if((NULL == drvHandleInt) ||
       (NULL == flowHandleInt) ||
       (0U == flowCnt))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        if(drvHandleInt->drvInitDone != UDMA_INIT_DONE)
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        /* Assign values to handle object */
        flowHandleInt->drvHandle    = drvHandleInt;
        flowHandleInt->flowStart    = flowStart;
        flowHandleInt->flowCnt      = flowCnt;
        flowHandleInt->flowInitDone = UDMA_INIT_DONE;
        flowHandleInt->mappedFlowGrp= UDMA_MAPPED_GROUP_INVALID;
        flowHandleInt->mappedChNum  = UDMA_DMA_CH_INVALID;
    }

    return (retVal);
}

int32_t Udma_flowDetach(Udma_FlowHandle flowHandle)
{
    int32_t             retVal = UDMA_SOK;
    Udma_FlowHandleInt  flowHandleInt = (Udma_FlowHandleInt) flowHandle;

    /* Error check */
    if(NULL == flowHandleInt)
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        if(flowHandleInt->flowInitDone != UDMA_INIT_DONE)
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        flowHandleInt->drvHandle    = (Udma_DrvHandleInt) NULL;
        flowHandleInt->flowStart    = UDMA_FLOW_INVALID;
        flowHandleInt->flowCnt      = 0U;
        flowHandleInt->flowInitDone = UDMA_DEINIT_DONE;
        flowHandleInt->mappedFlowGrp= UDMA_MAPPED_GROUP_INVALID;
        flowHandleInt->mappedChNum  = UDMA_DMA_CH_INVALID;
    }

    return (retVal);
}

int32_t Udma_flowAttachMapped(Udma_DrvHandle drvHandle,
                              Udma_FlowHandle flowHandle,
                              uint32_t mappepdFlowNum,
                              const Udma_FlowAllocMappedPrms *flowAllocMappedPrms)
{
    int32_t             retVal = UDMA_SOK;

    Udma_DrvHandleInt   drvHandleInt = (Udma_DrvHandleInt) drvHandle;
    Udma_FlowHandleInt  flowHandleInt = (Udma_FlowHandleInt) flowHandle;
    Udma_ChHandleInt    chHandleInt;
    Udma_ChAttributes  *chAttr;

    /* Error check */
    if((NULL_PTR == drvHandleInt) ||
       (NULL_PTR == flowHandleInt) ||
       (NULL_PTR == flowAllocMappedPrms))
    {
        retVal = UDMA_EBADARGS;
    }

    if(UDMA_SOK == retVal)
    {
        chHandleInt = (Udma_ChHandleInt) flowAllocMappedPrms->ChHandle;
        chAttr = &chHandleInt->chAttr;
        if(drvHandleInt->drvInitDone != UDMA_INIT_DONE)
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        /* Assign values to handle object */
        flowHandleInt->drvHandle    = drvHandleInt;
        flowHandleInt->flowStart    = chAttr->ChNum;
        flowHandleInt->flowCnt      = chAttr->flowCnt;
        flowHandleInt->flowInitDone = UDMA_INIT_DONE;
        flowHandleInt->mappedFlowGrp= 0U;
        flowHandleInt->mappedChNum  = chAttr->ChNum;
    }

    return (retVal);
}

int32_t Udma_flowConfig(Udma_FlowHandle flowHandle,
                        uint32_t flowIdx,
                        const Udma_FlowPrms *flowPrms)
{
    int32_t             retVal = UDMA_SOK;
    Udma_DrvHandleInt   drvHandle;
    Udma_FlowHandleInt  flowHandleInt = (Udma_FlowHandleInt) flowHandle;
    Udma_ChHandleInt    chHandleInt;
    CSL_LcdmaRingaccRingCfg  flowParams;

    /* Error check */
    if((NULL == flowHandleInt) ||
       (flowHandleInt->flowInitDone != UDMA_INIT_DONE) ||
       (NULL == flowPrms))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        chHandleInt = (Udma_ChHandleInt) flowPrms->ChHandle;
        drvHandle = flowHandleInt->drvHandle;
        if((NULL == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }
    if(UDMA_SOK == retVal)
    {
        /* Flow Idx is relative to flowStart and must be less than flowCnt */
        if(flowIdx >= flowHandleInt->flowCnt)
        {
            retVal = UDMA_EINVALID_PARAMS;
            DebugP_logError("[UDMA] Invalid flow index!!!\r\n");
        }
    }
    if(UDMA_SOK == retVal)
    {
        chHandleInt->chAttr.flowIdx  = flowIdx;
        flowHandleInt->flowIdx   = flowIdx;
        flowParams.psInfoPresent = flowPrms->psInfoPresent;
        flowParams.einfoPresent  = flowPrms->einfoPresent;
        flowParams.errorHandling = flowPrms->errorHandling;
        flowParams.sopOffset     = flowPrms->sopOffset;
        retVal = CSL_lcdmaFlowCfg( &drvHandle->lcdmaRaRegs, flowHandleInt->flowStart + flowHandleInt->flowIdx, &flowParams );
    }

    return (retVal);
}

uint32_t Udma_flowGetNum(Udma_FlowHandle flowHandle)
{
    int32_t             retVal = UDMA_SOK;
    uint32_t            flowNum = UDMA_FLOW_INVALID;
    Udma_FlowHandleInt  flowHandleInt = (Udma_FlowHandleInt) flowHandle;

    /* Error check */
    if((NULL == flowHandleInt) ||
       (flowHandleInt->flowInitDone != UDMA_INIT_DONE))
    {
        retVal = UDMA_EBADARGS;
    }

    if(UDMA_SOK == retVal)
    {
        flowNum = flowHandleInt->flowStart;
    }

    return (flowNum);
}

uint32_t Udma_flowGetCount(Udma_FlowHandle flowHandle)
{
    int32_t             retVal = UDMA_SOK;
    uint32_t            flowCnt = UDMA_FLOW_INVALID;
    Udma_FlowHandleInt  flowHandleInt = (Udma_FlowHandleInt) flowHandle;

    /* Error check */
    if((NULL == flowHandleInt) ||
       (flowHandleInt->flowInitDone != UDMA_INIT_DONE))
    {
        retVal = UDMA_EBADARGS;
    }

    if(UDMA_SOK == retVal)
    {
        flowCnt = flowHandleInt->flowCnt;
    }

    return (flowCnt);
}

void UdmaFlowPrms_init(Udma_FlowPrms *flowPrms, uint32_t chType)
{
    (void) chType;  /* MISRAC fix: could be used for future. So not removed */
    if(NULL != flowPrms)
    {
        flowPrms->ChHandle    = (Udma_ChHandle) NULL;
        flowPrms->einfoPresent  = UDMAP_RX_FLOW_EINFO_NOT_PRESENT;
        flowPrms->psInfoPresent = UDMAP_RX_FLOW_PSINFO_NOT_PRESENT;
        flowPrms->errorHandling = UDMAP_RX_FLOW_ERR_RETRY;
        flowPrms->descType      = UDMAP_RX_FLOW_DESC_HOST;
        flowPrms->psLocation    = UDMAP_RX_FLOW_PS_END_PD;
        flowPrms->sopOffset     = 0U;
        flowPrms->defaultRxCQ   = UDMA_RING_INVALID;
    }

    return;
}
