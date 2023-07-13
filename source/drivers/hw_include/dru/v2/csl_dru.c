/*
 *  Copyright (C) 2023 Texas Instruments Incorporated.
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
 *
 */
/**
 *  \file  csl_dru.c
 *
 *  \brief Implementation file for the DRU CSL-FL module.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <drivers/hw_include/dru/v2/cslr_dru.h>
#include <drivers/hw_include/dru/v2/csl_dru.h>
#include <drivers/hw_include/cslr.h>
#include <drivers/hw_include/cslr64.h>
#include <kernel/dpl/SystemP.h>


/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t CSL_druGetCapabilities(const CSL_DRU_t     *pRegs,
                               CSL_DruCapabilities *druCap)
{
    int32_t     retVal = SystemP_SUCCESS;
    uint64_t    regVal;
    uint64_t    trTypeMasks = CSL_DRU_CAPABILITIES_TYPE0_MASK |
                              CSL_DRU_CAPABILITIES_TYPE1_MASK |
                              CSL_DRU_CAPABILITIES_TYPE2_MASK |
                              CSL_DRU_CAPABILITIES_TYPE3_MASK |
                              CSL_DRU_CAPABILITIES_TYPE4_MASK |
                              CSL_DRU_CAPABILITIES_TYPE5_MASK |
                              CSL_DRU_CAPABILITIES_TYPE6_MASK |
                              CSL_DRU_CAPABILITIES_TYPE7_MASK |
                              CSL_DRU_CAPABILITIES_TYPE8_MASK |
                              CSL_DRU_CAPABILITIES_TYPE9_MASK |
                              CSL_DRU_CAPABILITIES_TYPE10_MASK |
                              CSL_DRU_CAPABILITIES_TYPE11_MASK |
                              CSL_DRU_CAPABILITIES_TYPE12_MASK |
                              CSL_DRU_CAPABILITIES_TYPE13_MASK |
                              CSL_DRU_CAPABILITIES_TYPE14_MASK |
                              CSL_DRU_CAPABILITIES_TYPE15_MASK;
    uint32_t    trTypeShift = CSL_DRU_CAPABILITIES_TYPE0_SHIFT;

    if(NULL == druCap)
    {
        retVal = SystemP_FAILURE;
    }
    else
    {
        regVal = CSL_REG64_RD(&pRegs->DRURegs.DRU_CAPABILITIES);
        druCap->trTypeSupported =
            CSL_REG64_FEXT_RAW(&regVal, trTypeMasks, trTypeShift);
        druCap->staticSupported =
            CSL_REG64_FEXT(&regVal, DRU_CAPABILITIES_TRSTATIC);
        druCap->eolSupported =
            CSL_REG64_FEXT(&regVal, DRU_CAPABILITIES_EOL);
        druCap->localTriggerSupported =
            CSL_REG64_FEXT(&regVal, DRU_CAPABILITIES_LOCAL_TRIG);
        druCap->globalTriggerSupported =
            CSL_REG64_FEXT(&regVal, DRU_CAPABILITIES_GLOBAL_TRIG);
        druCap->amode =
            CSL_REG64_FEXT(&regVal, DRU_CAPABILITIES_AMODE);
        druCap->elType =
            CSL_REG64_FEXT(&regVal, DRU_CAPABILITIES_ELTYPE);
        druCap->dfmt =
            CSL_REG64_FEXT(&regVal, DRU_CAPABILITIES_DFMT);
        druCap->sectr =
            CSL_REG64_FEXT(&regVal, DRU_CAPABILITIES_SECTR);
    }

    return (retVal);
}

int32_t CSL_druQueueConfig(const CSL_DRU_t             *pRegs,
                           uint32_t                     queueId,
                           const CSL_DruQueueConfig    *queueCfg)
{
    int32_t     retVal = SystemP_SUCCESS;
    uint64_t    regVal;

    if((queueId >= CSL_DRU_NUM_QUEUE) || (NULL == queueCfg))
    {
        retVal = SystemP_FAILURE;
    }
    else
    {
        regVal =  CSL_FMK(DRU_QUEUE_CFG_PRI, queueCfg->priority);
        regVal |= CSL_FMK(DRU_QUEUE_CFG_QOS, queueCfg->qos);
        regVal |= CSL_FMK(DRU_QUEUE_CFG_ORDERID, queueCfg->orderId);
        regVal |= CSL_FMK(DRU_QUEUE_CFG_CONSECUTIVE_TRANS,
                          queueCfg->consecuitveTrans);
        regVal |= CSL_FMK(DRU_QUEUE_CFG_REARB_WAIT, queueCfg->rearbWait);
        CSL_REG64_WR(&pRegs->DRUQueues.CFG[queueId], regVal);
    }

    return (retVal);
}

int32_t CSL_druChConfig(const CSL_DRU_t        *pRegs,
                        uint32_t                chId,
                        const CSL_DruChConfig  *chCfg)
{
    int32_t     retVal = SystemP_SUCCESS;
    uint64_t    regVal;

    if((chId >= CSL_DRU_NUM_CH) ||
       (NULL == chCfg) ||
       (chCfg->queueId >= CSL_DRU_NUM_QUEUE))
    {
        retVal = SystemP_FAILURE;
    }
    else
    {
        regVal =  CSL_FMK(DRU_CHNRT_CFG_CHAN_TYPE, chCfg->type);
        regVal |= CSL_FMK(DRU_CHNRT_CFG_CHAN_TYPE_OWNER, chCfg->owner);
        regVal |= CSL_FMK(DRU_CHNRT_CFG_PAUSE_ON_ERR, chCfg->pauseOnErr);
        CSL_REG64_WR(&pRegs->CHNRT[chId].CFG, regVal);

        regVal =  CSL_FMK(DRU_CHNRT_CHOES0_EVT_NUM, chCfg->evtNum);
        CSL_REG64_WR(&pRegs->CHNRT[chId].CHOES0, regVal);

        regVal =  CSL_FMK(DRU_CHNRT_CHST_SCHED_QUEUE, chCfg->queueId);
        CSL_REG64_WR(&pRegs->CHNRT[chId].CHST_SCHED, regVal);
    }

    return (retVal);
}

int32_t CSL_druChSetEvent(const CSL_DRU_t *pRegs,
                          uint32_t         chId,
                          uint64_t         evtNum)
{
    int32_t     retVal = SystemP_SUCCESS;
    uint64_t    regVal;

    if(chId >= CSL_DRU_NUM_CH)
    {
        retVal = SystemP_FAILURE;
    }
    else
    {
        regVal =  CSL_FMK(DRU_CHNRT_CHOES0_EVT_NUM, evtNum);
        CSL_REG64_WR(&pRegs->CHNRT[chId].CHOES0, regVal);
    }

    return (retVal);
}

int32_t CSL_druChEnable(const CSL_DRU_t *pRegs, uint32_t chId)
{
    int32_t     retVal = SystemP_SUCCESS;

    if(chId >= CSL_DRU_NUM_CH)
    {
        retVal = SystemP_FAILURE;
    }
    else
    {
        /* RT register is 32-bit wide only. Perform 32-bit access so that
         * all arch will do same operation. Doing a 64-bit access from
         * 32-bit arch will result in two 32-bit write to the 64-bit register
         * resulting in unintended operation */
        CSL_REG32_FINS((volatile uint32_t *) &pRegs->CHRT[chId].CHRT_CTL, DRU_CHRT_CTL_ENABLE, 1U);
    }

    return (retVal);
}

int32_t CSL_druChDisable(const CSL_DRU_t *pRegs, uint32_t chId)
{
    int32_t     retVal = SystemP_SUCCESS;

    if(chId >= CSL_DRU_NUM_CH)
    {
        retVal = SystemP_FAILURE;
    }
    else
    {
        /* RT register is 32-bit wide only. Perform 32-bit access so that
         * all arch will do same operation. Doing a 64-bit access from
         * 32-bit arch will result in two 32-bit write to the 64-bit register
         * resulting in unintended operation */
        CSL_REG32_FINS((volatile uint32_t *) &pRegs->CHRT[chId].CHRT_CTL, DRU_CHRT_CTL_ENABLE, 0U);
    }

    return (retVal);
}

int32_t CSL_druChTeardown(const CSL_DRU_t *pRegs, uint32_t chId)
{
    int32_t     retVal = SystemP_SUCCESS;

    if(chId >= CSL_DRU_NUM_CH)
    {
        retVal = SystemP_FAILURE;
    }
    else
    {
        /* RT register is 32-bit wide only. Perform 32-bit access so that
         * all arch will do same operation. Doing a 64-bit access from
         * 32-bit arch will result in two 32-bit write to the 64-bit register
         * resulting in unintended operation */
        CSL_REG32_FINS((volatile uint32_t *) &pRegs->CHRT[chId].CHRT_CTL, DRU_CHRT_CTL_TEARDOWN, 1U);
    }

    return (retVal);
}

uint32_t CSL_druChIsTeardownComplete(const CSL_DRU_t *pRegs, uint32_t chId)
{
    uint32_t    status = FALSE;
    uint64_t    regVal;

    if(chId < CSL_DRU_NUM_CH)
    {
        /* Channel enable clears when teardown completes */
        regVal = CSL_REG64_FEXT(&pRegs->CHRT[chId].CHRT_CTL, DRU_CHRT_CTL_ENABLE);
        if(0U == regVal)
        {
            status = TRUE;
        }
    }

    return (status);
}

int32_t CSL_druChPause(const CSL_DRU_t *pRegs, uint32_t chId)
{
    int32_t     retVal = SystemP_SUCCESS;

    if(chId >= CSL_DRU_NUM_CH)
    {
        retVal = SystemP_FAILURE;
    }
    else
    {
        /* RT register is 32-bit wide only. Perform 32-bit access so that
         * all arch will do same operation. Doing a 64-bit access from
         * 32-bit arch will result in two 32-bit write to the 64-bit register
         * resulting in unintended operation */
        CSL_REG32_FINS((volatile uint32_t *) &pRegs->CHRT[chId].CHRT_CTL, DRU_CHRT_CTL_PAUSE, 1U);
    }

    return (retVal);
}

int32_t CSL_druChResume(const CSL_DRU_t *pRegs, uint32_t chId)
{
    int32_t     retVal = SystemP_SUCCESS;

    if(chId >= CSL_DRU_NUM_CH)
    {
        retVal = SystemP_FAILURE;
    }
    else
    {
        /* RT register is 32-bit wide only. Perform 32-bit access so that
         * all arch will do same operation. Doing a 64-bit access from
         * 32-bit arch will result in two 32-bit write to the 64-bit register
         * resulting in unintended operation */
        CSL_REG32_FINS((volatile uint32_t *) &pRegs->CHRT[chId].CHRT_CTL, DRU_CHRT_CTL_PAUSE, 0U);
    }

    return (retVal);
}

volatile uint64_t *CSL_druChGetTriggerRegAddr(CSL_DRU_t *pRegs, uint32_t chId)
{
    volatile uint64_t *regAddr = NULL;

    if((chId < CSL_DRU_NUM_CH) && (pRegs != NULL))
    {
        regAddr = &pRegs->CHRT[chId].CHRT_SWTRIG;
    }

    return (regAddr);
}

int32_t CSL_druChSetLocalTrigger0(CSL_DRU_t *pRegs, uint32_t chId)
{
    int32_t             retVal = SystemP_SUCCESS;
    volatile uint64_t  *pSwTrigReg;

    pSwTrigReg = CSL_druChGetTriggerRegAddr(pRegs, chId);
    if(NULL == pSwTrigReg)
    {
        retVal = SystemP_FAILURE;
    }
    else
    {
        CSL_druChSetLocalTrigger0Raw(pSwTrigReg);
    }

    return (retVal);
}

int32_t CSL_druChSetGlobalTrigger0(CSL_DRU_t *pRegs, uint32_t chId)
{
    int32_t             retVal = SystemP_SUCCESS;
    volatile uint64_t  *pSwTrigReg;

    pSwTrigReg = CSL_druChGetTriggerRegAddr(pRegs, chId);
    if(NULL == pSwTrigReg)
    {
        retVal = SystemP_FAILURE;
    }
    else
    {
        CSL_druChSetGlobalTrigger0Raw(pSwTrigReg);
    }

    return (retVal);
}

int32_t CSL_druChSetGlobalTrigger1(CSL_DRU_t *pRegs, uint32_t chId)
{
    int32_t             retVal = SystemP_SUCCESS;
    volatile uint64_t  *pSwTrigReg;

    pSwTrigReg = CSL_druChGetTriggerRegAddr(pRegs, chId);
    if(NULL == pSwTrigReg)
    {
        retVal = SystemP_FAILURE;
    }
    else
    {
        CSL_druChSetGlobalTrigger1Raw(pSwTrigReg);
    }

    return (retVal);
}

int32_t CSL_druGetQueueStatus(const CSL_DRU_t *pRegs,
                              uint32_t queueId,
                              CSL_DruQueueStatus *status)
{
    int32_t     retVal = SystemP_SUCCESS;
    uint64_t    regVal;

    if((queueId >= CSL_DRU_NUM_QUEUE) || (NULL == status))
    {
        retVal = SystemP_FAILURE;
    }
    else
    {
        regVal = CSL_REG64_RD(&pRegs->DRUQueues.STATUS[queueId]);
        status->rdTop   = CSL_REG64_FEXT(&regVal, DRU_QUEUE_STATUS_RD_TOP);
        status->rdTotal = CSL_REG64_FEXT(&regVal, DRU_QUEUE_STATUS_RD_TOTAL);
        status->wrTop   = CSL_REG64_FEXT(&regVal, DRU_QUEUE_STATUS_WR_TOP);
        status->wrTotal = CSL_REG64_FEXT(&regVal, DRU_QUEUE_STATUS_WR_TOTAL);
    }

    return (retVal);
}
