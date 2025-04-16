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
 *  \file udma_ring.c
 *
 *  \brief File containing the UDMA driver ring related APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/udma/v1/udma_priv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Max number of door bell ring that can be performed at one go */
#define UDMA_RING_MAX_DB_RING_CNT       (127U)

#define UDMA_RING_MODE_RING             (0x0u)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static int32_t Udma_ringCheckParams(Udma_DrvHandleInt drvHandle,
                                    const Udma_RingPrms *ringPrms);
static inline void Udma_ringAssertFnPointers(Udma_DrvHandleInt drvHandle);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t Udma_ringAlloc(Udma_DrvHandle drvHandle,
                       Udma_RingHandle ringHandle,
                       uint16_t ringNum,
                       const Udma_RingPrms *ringPrms)
{
    int32_t             retVal = UDMA_SOK;
    uint32_t            allocDone = (uint32_t) FALSE;
    uint64_t            physBase;
    Udma_DrvHandleInt   drvHandleInt = (Udma_DrvHandleInt) drvHandle;
    Udma_RingHandleInt  ringHandleInt = (Udma_RingHandleInt) ringHandle;
    CSL_LcdmaRingaccRingCfg ringCfg;
    CSL_LcdmaRingaccCfg *pCfg = &drvHandleInt->lcdmaRaRegs;

    /* Error check */
    if((NULL == drvHandleInt) ||
       (NULL == ringHandleInt) ||
       (NULL == ringPrms))
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
        retVal = Udma_ringCheckParams(drvHandleInt, ringPrms);
    }

    if(UDMA_SOK == retVal)
    {
        if(ringNum >= drvHandleInt->maxRings)
        {
            DebugP_logError("[UDMA] Out of range ring index!!!\r\n");
            retVal = UDMA_EINVALID_PARAMS;
        }
        else
        {
            ringHandleInt->ringNum = ringNum;
            allocDone = (uint32_t) TRUE;
        }
    }

    if(UDMA_SOK == retVal)
    {
        Udma_ringAssertFnPointers(drvHandleInt);
        ringHandleInt->drvHandle = drvHandleInt;
        drvHandleInt->ringSetCfg(drvHandleInt, ringHandleInt, ringPrms);
    }

    if(UDMA_SOK == retVal)
    {
        physBase = Udma_virtToPhyFxn(ringPrms->ringMem, drvHandleInt, (Udma_ChHandleInt) NULL);
        ringCfg.physBase = physBase;
        ringCfg.asel = ringPrms->asel;
        ringCfg.elCnt = ringPrms->elemCnt;
        CSL_lcdmaCfgRingRt(pCfg, ringNum, &ringCfg);
        /* Enable the interrupt */
        CSL_lcdmaSetInterrupt(pCfg, ringNum, UDMA_SET_COMP_INT,true);
    }

    if(UDMA_SOK == retVal)
    {
        ringHandleInt->ringInitDone = UDMA_INIT_DONE;
    }
    else
    {
        /* Error. Free-up resource if allocated */
        if(((uint32_t) TRUE) == allocDone)
        {
            if(UDMA_MAPPED_GROUP_INVALID == ringPrms->mappedRingGrp)
            {
                Udma_rmFreeFreeRing(ringHandleInt->ringNum, drvHandleInt);
            }
#if((UDMA_NUM_MAPPED_TX_GROUP + UDMA_NUM_MAPPED_RX_GROUP) > 0)
            else
            {
                Udma_rmFreeFreeRing(ringHandleInt->ringNum, drvHandleInt);
            }
#endif
        }
    }

    return (retVal);
}

int32_t Udma_ringFree(Udma_RingHandle ringHandle)
{
    int32_t             retVal = UDMA_SOK;
    Udma_DrvHandleInt   drvHandle;
    Udma_RingHandleInt  ringHandleInt = (Udma_RingHandleInt) ringHandle;

    /* Error check */
    if(NULL == ringHandleInt)
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        if(ringHandleInt->ringInitDone != UDMA_INIT_DONE)
        {
            retVal = UDMA_EFAIL;
        }
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = ringHandleInt->drvHandle;
        if((NULL == drvHandle) || (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        /* Free-up event resources */
        if(ringHandleInt->ringNum != UDMA_RING_INVALID)
        {
            Udma_rmFreeFreeRing(ringHandleInt->ringNum, drvHandle);
        }
        
        ringHandleInt->ringNum         = UDMA_RING_INVALID;
        ringHandleInt->ringInitDone    = UDMA_DEINIT_DONE;
        drvHandle->ringHandleClearRegs(ringHandleInt);
        ringHandleInt->drvHandle       = (Udma_DrvHandleInt) NULL;
    }

    return (retVal);
}

int32_t Udma_ringAttach(Udma_DrvHandle drvHandle,
                        Udma_RingHandle ringHandle,
                        uint16_t ringNum)
{
    int32_t             retVal = UDMA_SOK;
    Udma_DrvHandleInt   drvHandleInt = (Udma_DrvHandleInt) drvHandle;
    Udma_RingHandleInt  ringHandleInt = (Udma_RingHandleInt) ringHandle;

    /* Error check */
    if((NULL == drvHandleInt) || (NULL == ringHandleInt))
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
        if(ringNum >= drvHandleInt->maxRings)
        {
            DebugP_logError("[UDMA] Out of range ring index!!!\r\n");
            retVal = UDMA_EINVALID_PARAMS;
        }
    }

    if(UDMA_SOK == retVal)
    {
        ringHandleInt->ringNum = ringNum;
        ringHandleInt->drvHandle = drvHandleInt;
        drvHandleInt->ringSetCfg(drvHandleInt, ringHandleInt, (Udma_RingPrms *) NULL);
        ringHandleInt->ringInitDone = UDMA_INIT_DONE;
    }

    return (retVal);
}

int32_t Udma_ringDetach(Udma_RingHandle ringHandle)
{
    int32_t             retVal = UDMA_SOK;
    Udma_DrvHandleInt   drvHandle;
    Udma_RingHandleInt  ringHandleInt = (Udma_RingHandleInt) ringHandle;

    /* Error check */
    if(NULL == ringHandleInt)
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        if(ringHandleInt->ringInitDone != UDMA_INIT_DONE)
        {
            retVal = UDMA_EFAIL;
        }
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = ringHandleInt->drvHandle;
        if((NULL == drvHandle) ||
           (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        /* Clear handle object */
        ringHandleInt->ringInitDone    = UDMA_DEINIT_DONE;
        drvHandle->ringHandleClearRegs(ringHandleInt);
        ringHandleInt->drvHandle       = (Udma_DrvHandleInt) NULL;

    }

    return (retVal);
}

int32_t Udma_ringQueueRaw(Udma_RingHandle ringHandle, uint64_t phyDescMem)
{
    int32_t             retVal = UDMA_SOK;
    uintptr_t           cookie;
    Udma_DrvHandleInt   drvHandle;
    Udma_RingHandleInt  ringHandleInt = (Udma_RingHandleInt) ringHandle;

    /* Error check */
    if((NULL == ringHandleInt) ||
       (ringHandleInt->ringInitDone != UDMA_INIT_DONE) ||
       (ringHandleInt->ringNum == UDMA_RING_INVALID))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = ringHandleInt->drvHandle;
        if((NULL == drvHandle) ||
           (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        cookie = HwiP_disable();

        retVal = drvHandle->ringQueueRaw(drvHandle, ringHandleInt, phyDescMem);

        HwiP_restore(cookie);
    }

    return (retVal);
}

int32_t Udma_ringDequeueRaw(Udma_RingHandle ringHandle, uint64_t *phyDescMem)
{
    int32_t             retVal = UDMA_SOK;
    uintptr_t           cookie;
    Udma_DrvHandleInt   drvHandle;
    Udma_RingHandleInt  ringHandleInt = (Udma_RingHandleInt) ringHandle;

    /* Error check */
    if((NULL == ringHandleInt) ||
       (ringHandleInt->ringInitDone != UDMA_INIT_DONE) ||
       (ringHandleInt->ringNum == UDMA_RING_INVALID))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = ringHandleInt->drvHandle;
        if((NULL == drvHandle) ||
           (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        cookie = HwiP_disable();

        retVal = drvHandle->ringDequeueRaw(drvHandle, ringHandleInt, phyDescMem);

        HwiP_restore(cookie);
    }

    return (retVal);
}

int32_t Udma_ringFlushRaw(Udma_RingHandle ringHandle, uint64_t *phyDescMem)
{
    int32_t             retVal = UDMA_SOK;
    Udma_DrvHandleInt   drvHandle;
    Udma_RingHandleInt  ringHandleInt = (Udma_RingHandleInt) ringHandle;

    /* Error check */
    if((NULL == ringHandleInt) ||
       (ringHandleInt->ringInitDone != UDMA_INIT_DONE) ||
       (ringHandleInt->ringNum == UDMA_RING_INVALID))
    {
        retVal = UDMA_EBADARGS;
    }
    if(UDMA_SOK == retVal)
    {
        drvHandle = ringHandleInt->drvHandle;
        if((NULL == drvHandle) ||
           (drvHandle->drvInitDone != UDMA_INIT_DONE))
        {
            retVal = UDMA_EFAIL;
        }
    }

    if(UDMA_SOK == retVal)
    {
        retVal = drvHandle->ringFlushRaw(drvHandle, ringHandleInt, phyDescMem);
    }

    return (retVal);
}

void Udma_ringPrime(Udma_RingHandle ringHandle, uint64_t phyDescMem)
{
    Udma_RingHandleInt  ringHandleInt = (Udma_RingHandleInt) ringHandle;
    Udma_DrvHandleInt   drvHandle = ringHandleInt->drvHandle;

    drvHandle->ringPrime(ringHandleInt, phyDescMem);

    return;
}

void Udma_ringPrimeRead(Udma_RingHandle ringHandle, uint64_t *phyDescMem)
{
    Udma_RingHandleInt  ringHandleInt = (Udma_RingHandleInt) ringHandle;
    Udma_DrvHandleInt   drvHandle = ringHandleInt->drvHandle;

    drvHandle->ringPrimeRead(ringHandleInt, phyDescMem);

    return;
}

void Udma_ringSetDoorBell(Udma_RingHandle ringHandle, int32_t count)
{
    Udma_RingHandleInt  ringHandleInt = (Udma_RingHandleInt) ringHandle;
    Udma_DrvHandleInt   drvHandle = ringHandleInt->drvHandle;

    drvHandle->ringSetDoorBell(ringHandleInt, count);

    return;
}

uint16_t Udma_ringGetNum(Udma_RingHandle ringHandle)
{
    uint16_t            ringNum = UDMA_RING_INVALID;
    Udma_RingHandleInt  ringHandleInt = (Udma_RingHandleInt) ringHandle;

    if((NULL != ringHandleInt) &&
       (UDMA_INIT_DONE == ringHandleInt->ringInitDone))
    {
        ringNum = ringHandleInt->ringNum;
    }

    return (ringNum);
}

void *Udma_ringGetMemPtr(Udma_RingHandle ringHandle)
{
    void               *ringMem = NULL;
    Udma_RingHandleInt  ringHandleInt = (Udma_RingHandleInt) ringHandle;
    Udma_DrvHandleInt   drvHandle = ringHandleInt->drvHandle;

    ringMem = drvHandle->ringGetMemPtr(ringHandleInt);

    return (ringMem);
}

uint32_t Udma_ringGetMode(Udma_RingHandle ringHandle)
{
    uint32_t            ringMode;
    Udma_RingHandleInt  ringHandleInt = (Udma_RingHandleInt) ringHandle;
    Udma_DrvHandleInt   drvHandle = ringHandleInt->drvHandle;

    ringMode = drvHandle->ringGetMode(ringHandleInt);

    return (ringMode);
}

uint32_t Udma_ringGetElementCnt(Udma_RingHandle ringHandle)
{
    uint32_t            size = 0U;
    Udma_RingHandleInt  ringHandleInt = (Udma_RingHandleInt) ringHandle;
    Udma_DrvHandleInt   drvHandle = ringHandleInt->drvHandle;

    size = drvHandle->ringGetElementCnt(ringHandleInt);

    return (size);
}

uint32_t Udma_ringGetForwardRingOcc(Udma_RingHandle ringHandle)
{
    uint32_t            occ = 0U;
    Udma_RingHandleInt  ringHandleInt = (Udma_RingHandleInt) ringHandle;
    Udma_DrvHandleInt   drvHandle = ringHandleInt->drvHandle;

    occ = drvHandle->ringGetForwardRingOcc(ringHandleInt);

    return (occ);
}

uint32_t Udma_ringGetReverseRingOcc(Udma_RingHandle ringHandle)
{
    uint32_t            occ = 0U;
    Udma_RingHandleInt  ringHandleInt = (Udma_RingHandleInt) ringHandle;
    Udma_DrvHandleInt   drvHandle = ringHandleInt->drvHandle;

    occ = drvHandle->ringGetReverseRingOcc(ringHandleInt);

    return (occ);
}

uint32_t Udma_ringGetWrIdx(Udma_RingHandle ringHandle)
{
    uint32_t            idx = 0U;
    Udma_RingHandleInt  ringHandleInt = (Udma_RingHandleInt) ringHandle;
    Udma_DrvHandleInt   drvHandle = ringHandleInt->drvHandle;

    idx = drvHandle->ringGetWrIdx(ringHandleInt);

    return (idx);
}

uint32_t Udma_ringGetRdIdx(Udma_RingHandle ringHandle)
{
    uint32_t            idx = 0U;
    Udma_RingHandleInt  ringHandleInt = (Udma_RingHandleInt) ringHandle;
    Udma_DrvHandleInt   drvHandle = ringHandleInt->drvHandle;

    idx = drvHandle->ringGetRdIdx(ringHandleInt);

    return (idx);
}

void UdmaRingPrms_init(Udma_RingPrms *ringPrms)
{
    if(NULL != ringPrms)
    {
        ringPrms->ringMem       = NULL;
        ringPrms->ringMemSize   = UDMA_RING_SIZE_CHECK_SKIP;
        ringPrms->mode          = UDMA_RING_MODE_RING;
        ringPrms->virtId        = UDMA_RING_VIRTID_INVALID;
        ringPrms->elemCnt       = 0U;
        ringPrms->elemSize      = UDMA_RING_ES_8BYTES;
        ringPrms->orderId       = UDMA_DEFAULT_RING_ORDER_ID;
        ringPrms->asel          = UDMA_RINGACC_ASEL_ENDPOINT_PHYSADDR;
        ringPrms->mappedRingGrp = UDMA_MAPPED_GROUP_INVALID;
        ringPrms->mappedChNum   = UDMA_DMA_CH_INVALID;
    }

    return;
}

static int32_t Udma_ringCheckParams(Udma_DrvHandleInt drvHandle,
                                    const Udma_RingPrms *ringPrms)
{
    int32_t     retVal = UDMA_SOK;
    uint32_t    ringMemSize;

    if(ringPrms != NULL)
    {
       if(NULL == ringPrms->ringMem)
       {
           retVal = UDMA_EINVALID_PARAMS;
           DebugP_logError("[UDMA] Ring memory should not be NULL!!!\r\n");
       }
       else
       {
           /* Check 128 byte alignment */
           if(((uintptr_t)ringPrms->ringMem & (UDMA_CACHELINE_ALIGNMENT - 1U)) != 0U)
           {
               retVal = UDMA_EINVALID_PARAMS;
               DebugP_logError("[UDMA] Ring memory not aligned!!!\r\n");
           }
       }

       if(0U == ringPrms->elemCnt)
       {
           retVal = UDMA_EINVALID_PARAMS;
           DebugP_logError("[UDMA] Ring element count should not be zero!!!\r\n");
       }

       if(UDMA_INST_TYPE_NORMAL != drvHandle->instType)
       {
           if(UDMA_RING_MODE_RING != ringPrms->mode)
           {
               retVal = UDMA_EINVALID_PARAMS;
               DebugP_logError("[UDMA] Invalid Ring Mode for LCDMA!!!\r\n");
           }
       }

       if(UDMA_RING_SIZE_CHECK_SKIP != ringPrms->ringMemSize)
       {
           /* Get ring memory size */
           ringMemSize = UdmaUtils_getRingMemSize(
                          ringPrms->mode,
                          ringPrms->elemCnt,
                          ringPrms->elemSize);
           if(ringPrms->ringMemSize < ringMemSize)
           {
               retVal = UDMA_EALLOC;
               DebugP_logError("[UDMA] Ring memory not sufficient!!!\r\n");
           }
       }

       if (UDMA_RING_ORDERID_MAX < ringPrms->orderId)
       {
           retVal = UDMA_EINVALID_PARAMS;
           DebugP_logError("[UDMA] Ring orderId out of range (%u)!!!\r\n", ringPrms->orderId);
       }
    }

    return (retVal);
}

static inline void Udma_ringAssertFnPointers(Udma_DrvHandleInt drvHandle)
{
    DebugP_assert(drvHandle->ringDequeueRaw        != (Udma_ringDequeueRawFxn) NULL);
    DebugP_assert(drvHandle->ringQueueRaw          != (Udma_ringQueueRawFxn) NULL);
    DebugP_assert(drvHandle->ringFlushRaw          != (Udma_ringFlushRawFxn) NULL);
    DebugP_assert(drvHandle->ringGetElementCnt     != (Udma_ringGetElementCntFxn) NULL);
    DebugP_assert(drvHandle->ringGetMemPtr         != (Udma_ringGetMemPtrFxn) NULL);
    DebugP_assert(drvHandle->ringGetMode           != (Udma_ringGetModeFxn) NULL);
    DebugP_assert(drvHandle->ringGetForwardRingOcc != (Udma_ringGetForwardRingOccFxn) NULL);
    DebugP_assert(drvHandle->ringGetReverseRingOcc != (Udma_ringGetReverseRingOccFxn) NULL);
    DebugP_assert(drvHandle->ringGetWrIdx          != (Udma_ringGetWrIdxFxn) NULL);
    DebugP_assert(drvHandle->ringGetRdIdx          != (Udma_ringGetRdIdxFxn) NULL);
    DebugP_assert(drvHandle->ringPrime             != (Udma_ringPrimeFxn) NULL);
    DebugP_assert(drvHandle->ringPrimeRead         != (Udma_ringPrimeReadFxn) NULL);
    DebugP_assert(drvHandle->ringSetDoorBell       != (Udma_ringSetDoorBellFxn) NULL);
    DebugP_assert(drvHandle->ringSetCfg            != (Udma_ringSetCfgFxn) NULL);
    DebugP_assert(drvHandle->ringHandleClearRegs   != (Udma_ringHandleClearRegsFxn) NULL);

    return;
}
