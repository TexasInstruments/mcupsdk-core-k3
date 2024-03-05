/*
 *  Copyright (C) 2021-2023 Texas Instruments Incorporated
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

#include <drivers/utils/utils.h>
#include <kernel/dpl/CacheP.h>

#include <drivers/udma.h>
#include <drivers/bootloader.h>
#include <drivers/bootloader/bootloader_dma.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define UDMA_DMA_COPY_SRC_ALIGNMENT         (32U)
#define UDMA_DMA_COPY_SIZE_ALIGNMENT        (32U)

#define UDMA_DMA_MAX_L0_XFER_SIZE           (65536U)
#define UDMA_DMA_XFER_SIZE                  (64512U)

#define UDMA_DMA_COPY_LOWER_LIMIT           (1024U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */


/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static int32_t Udma_isDmaRestrictedRegion(Bootloader_AddrRegion* restrictedRegions, uint32_t addr);
static int32_t Bootloader_dmaDirectCopy(void* udmaArgs, void* dst, void* src, uint32_t length);
static int32_t BootloaderDma_submitTR(BootloaderDma_UdmaArgs* udmaDmaArgs, void* dst, void* src, uint16_t icnt[4]);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static int32_t Udma_isDmaRestrictedRegion(Bootloader_AddrRegion* restrictedRegions, uint32_t addr)
{
    int32_t isRestricted = FALSE;

    const Bootloader_AddrRegion *addrRegions = (Bootloader_AddrRegion *)restrictedRegions;
    uint32_t i = 0;
    uint32_t start;
    uint32_t size;

    while(addrRegions[i].regionStartAddr != 0xFFFFFFFF)
    {
        start = addrRegions[i].regionStartAddr;
        size = addrRegions[i].regionSize;

        if((addr >= start) && (addr < (start + size)))
        {
            isRestricted = TRUE;
            break;
        }
        i++;
    }

    return isRestricted;
}

static int32_t BootloaderDma_submitTR(BootloaderDma_UdmaArgs* udmaDmaArgs, void* dst, void* src, uint16_t icnt[4])
{
    int32_t status = UDMA_SOK;
    BootloaderDma_UdmaArgs* udmaArgs = (BootloaderDma_UdmaArgs*) udmaDmaArgs;
    Udma_ChHandle chHandle = udmaArgs->chHandle;
    uint8_t *trpdMem     = (uint8_t *) udmaArgs->trpdMem;
    uint32_t trpdMemSize = udmaArgs->trpdMemSize;
    uint64_t pDesc;
    uint32_t trRespStatus;
    uint64_t trpdMemPhy = (uint64_t) Udma_defaultVirtToPhyFxn(trpdMem, 0U, NULL);

    /* Update TRPD */
    CSL_UdmapTR15  *pTr;
    pTr = UdmaUtils_getTrpdTr15Pointer(trpdMem, 0U);

    pTr->icnt0 = icnt[0];
    pTr->icnt1 = icnt[1];
    pTr->icnt2 = icnt[2];
    pTr->icnt3 = icnt[3];

    pTr->dim1     = (int32_t)pTr->icnt0;
    pTr->dim2     = (int32_t)pTr->icnt0 * (int32_t)pTr->icnt1;
    pTr->dim3     = (int32_t)pTr->icnt0 * (int32_t)pTr->icnt1 * (int32_t)pTr->icnt2;

    pTr->dicnt0 = pTr->icnt0;
    pTr->dicnt1 = pTr->icnt1;
    pTr->dicnt2 = pTr->icnt2;
    pTr->dicnt3 = pTr->icnt3;

    pTr->ddim1    = (int32_t)pTr->dicnt0;
    pTr->ddim2    = (int32_t)pTr->dicnt0 * (int32_t)pTr->dicnt1;
    pTr->ddim3    = (int32_t)pTr->dicnt0 * (int32_t)pTr->dicnt1 * (int32_t)pTr->dicnt2;

    pTr->addr     = (uint64_t) Udma_defaultVirtToPhyFxn(src, 0U, NULL);
    pTr->daddr    = (uint64_t) Udma_defaultVirtToPhyFxn(dst, 0U, NULL);

    uint32_t length = pTr->icnt0 * pTr->icnt1 * pTr->icnt2 * pTr->icnt3;

    /* Perform cache writeback */
    CacheP_wb(trpdMem, trpdMemSize, CacheP_TYPE_ALL);
    CacheP_wbInv(dst, length, CacheP_TYPE_ALL);

    /* Submit TRPD to channel */
    status = Udma_ringQueueRaw(Udma_chGetFqRingHandle(chHandle), trpdMemPhy);

    /* Wait for return descriptor in completion ring - this marks transfer completion */
    while(1)
    {
        status = Udma_ringDequeueRaw(Udma_chGetCqRingHandle(chHandle), &pDesc);
        if(UDMA_SOK == status)
        {
            /* Check TR response status */
            CacheP_inv(trpdMem, trpdMemSize, CacheP_TYPE_ALLD);
            trRespStatus = UdmaUtils_getTrpdTr15Response(trpdMem, 1U, 0U);
            if(trRespStatus != CSL_UDMAP_TR_RESPONSE_STATUS_COMPLETE)
            {
                DebugP_log("TR Response failed for transfer : SRC = 0x%X, DST = 0x%X, SIZE = %u\r\n", (uint32_t)src, (uint32_t)dst, length);
                DebugP_assert(FALSE);
            }
            break;
        }
    }

    return status;
}


static int32_t Bootloader_dmaDirectCopy(void* udmaArgs, void* dst, void* src, uint32_t length)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t quotient = 0U;
    uint32_t rmainder = 0U;
    uint16_t icnt[4] = { 0U, 0U, 0U, 0U };

    if (length < UDMA_DMA_MAX_L0_XFER_SIZE)
    {
        icnt[0] = (uint16_t)length;
        icnt[1] = (uint16_t)1U;
    }
    else
    {
        icnt[0] = (uint16_t)UDMA_DMA_XFER_SIZE;
        quotient = length / UDMA_DMA_XFER_SIZE;
        rmainder = length % UDMA_DMA_XFER_SIZE;
        icnt[1] = (uint16_t)(quotient);
    }

    icnt[2] = (uint16_t)1U;
    icnt[3] = (uint16_t)1U;

    status = BootloaderDma_submitTR(udmaArgs, dst, src, icnt);

    if(rmainder != 0)
    {
        /* residual data */
        icnt[0] = (uint16_t)rmainder;
        icnt[1] = (uint16_t)1U;
        icnt[2] = (uint16_t)1U;
        icnt[3] = (uint16_t)1U;

        status = BootloaderDma_submitTR(udmaArgs, ((uint8_t *)dst+(length-rmainder)), ((uint8_t *)src+(length-rmainder)), icnt);
    }

    return status;
}

int32_t Bootloader_dmaOpen(void* udmaDmaArgs)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t            chType;
    Udma_ChHandle       chHandle;
    Udma_ChPrms         chPrms;
    Udma_ChTxPrms       txPrms;
    Udma_ChRxPrms       rxPrms;
    Udma_DrvHandle      drvHandle;
    uint8_t*            trpdMem;
    uint32_t            trpdMemSize;

    BootloaderDma_UdmaArgs* udmaArgs = (BootloaderDma_UdmaArgs *)udmaDmaArgs;

    drvHandle   = udmaArgs->drvHandle;
    chHandle    = udmaArgs->chHandle;
    trpdMem     = (uint8_t *) udmaArgs->trpdMem;
    trpdMemSize = udmaArgs->trpdMemSize;

    /* Init channel parameters */
    chType = UDMA_CH_TYPE_TR_BLK_COPY;
    UdmaChPrms_init(&chPrms, chType);
    chPrms.fqRingPrms.ringMem       = udmaArgs->ringMem;
    chPrms.fqRingPrms.ringMemSize   = udmaArgs->ringMemSize;
    chPrms.fqRingPrms.elemCnt       = udmaArgs->ringElemCount;

    /* Open channel for block copy */
    status = Udma_chOpen(drvHandle, chHandle, chType, &chPrms);
    DebugP_assert(UDMA_SOK == status);

    /* Config TX channel */
    UdmaChTxPrms_init(&txPrms, chType);
    status = Udma_chConfigTx(chHandle, &txPrms);
    DebugP_assert(UDMA_SOK == status);

    /* Config RX channel - which is implicitly paired to TX channel in
     * block copy mode */
    UdmaChRxPrms_init(&rxPrms, chType);
    status = Udma_chConfigRx(chHandle, &rxPrms);
    DebugP_assert(UDMA_SOK == status);

    /* Enable channel */
    status = Udma_chEnable(chHandle);
    DebugP_assert(UDMA_SOK == status);

    /* Check if TRPD memory was allocated, assert if NULL */
    DebugP_assert(trpdMem != NULL);

    /* Do TRPD Init with NULL src dst and 0 length. Fill this later in dmaCopy */
    CSL_UdmapTR15  *pTr;
    uint32_t        cqRingNum = Udma_chGetCqRingNum(chHandle);

    /* Make TRPD with TR15 TR type */
    UdmaUtils_makeTrpdTr15(trpdMem, 1U, cqRingNum);

    /* Setup TR */
    pTr = UdmaUtils_getTrpdTr15Pointer(trpdMem, 0U);
    pTr->flags    = CSL_FMK(UDMAP_TR_FLAGS_TYPE, CSL_UDMAP_TR_FLAGS_TYPE_4D_BLOCK_MOVE_REPACKING_INDIRECTION);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_STATIC, 0U);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EOL, CSL_UDMAP_TR_FLAGS_EOL_MATCH_SOL_EOL);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EVENT_SIZE, CSL_UDMAP_TR_FLAGS_EVENT_SIZE_COMPLETION);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0, CSL_UDMAP_TR_FLAGS_TRIGGER_NONE);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0_TYPE, CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ALL);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER1, CSL_UDMAP_TR_FLAGS_TRIGGER_NONE);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_TRIGGER1_TYPE, CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ALL);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_CMD_ID, 0x25U);  /* This will come back in TR response */
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_SA_INDIRECT, 0U);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_DA_INDIRECT, 0U);
    pTr->flags   |= CSL_FMK(UDMAP_TR_FLAGS_EOP, 1U);
    pTr->icnt0    = 0U;
    pTr->icnt1    = 1U;
    pTr->icnt2    = 1U;
    pTr->icnt3    = 1U;
    pTr->dim1     = pTr->icnt0;
    pTr->dim2     = (pTr->icnt0 * pTr->icnt1);
    pTr->dim3     = (pTr->icnt0 * pTr->icnt1 * pTr->icnt2);
    pTr->addr     = 0U;
    pTr->fmtflags = 0x00000000U;    /* Linear addressing, 1 byte per elem */
    pTr->dicnt0   = 0U;
    pTr->dicnt1   = 1U;
    pTr->dicnt2   = 1U;
    pTr->dicnt3   = 1U;
    pTr->ddim1    = pTr->dicnt0;
    pTr->ddim2    = (pTr->dicnt0 * pTr->dicnt1);
    pTr->ddim3    = (pTr->dicnt0 * pTr->dicnt1 * pTr->dicnt2);
    pTr->daddr    = 0U;

    /* Perform cache writeback */
    CacheP_wb(trpdMem, trpdMemSize, CacheP_TYPE_ALLD);

    return status;
}

int32_t Bootloader_dmaClose(void* udmaDmaArgs)
{
    int32_t status = SystemP_SUCCESS;

    BootloaderDma_UdmaArgs* udmaArgs = (BootloaderDma_UdmaArgs *)udmaDmaArgs;
    Udma_ChHandle chHandle = udmaArgs->chHandle;

    /* Disable Channel */
    status = Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    DebugP_assert(UDMA_SOK == status);

    /* Flush any pending request from the free queue */
    while(1)
    {
        uint64_t        pDesc;
        int32_t tempRetVal = Udma_ringFlushRaw(
                         Udma_chGetFqRingHandle(chHandle), &pDesc);
        if(UDMA_ETIMEOUT == tempRetVal)
        {
            break;
        }
    }

    /* Close channel */
    status = Udma_chClose(chHandle);
    DebugP_assert(UDMA_SOK == status);

    return status;

}

int32_t Bootloader_dmaCopy(void* udmaDmaArgs, void* dst, void* src, uint32_t length)
{
    int32_t status = SystemP_SUCCESS;
    uint8_t *pSrc;
    uint8_t *pDst;

    BootloaderDma_UdmaArgs* udmaArgs = (BootloaderDma_UdmaArgs *)udmaDmaArgs;

    pDst = (uint8_t *)dst;
    pSrc = (uint8_t *)src;

    /* DMA Copy fails when copying to to certain memory regions. So in this case we switch to normal memcpy
       for copying even if dmaEnable is true. Also do DMA copy only if size > 1KB*/
    uint32_t isDmaCopy = (Udma_isDmaRestrictedRegion(udmaArgs->restrictedRegions, \
                                                        (uint32_t)pDst) == FALSE) &&    \
                         (length > UDMA_DMA_COPY_LOWER_LIMIT);

    if(isDmaCopy == TRUE)
    {
        uint8_t *tempSrc = pSrc;
        uint8_t *tempDst = pDst;
        uint32_t remainingBytes = length;

        /* Check for 32B alignment of source address */
        if(((uint32_t)pSrc % UDMA_DMA_COPY_SRC_ALIGNMENT) != 0)
        {
            uint32_t initResidualBytes = UDMA_DMA_COPY_SRC_ALIGNMENT - (((uint32_t)pSrc) % UDMA_DMA_COPY_SRC_ALIGNMENT);

            /* Do CPU copy for the initial residual bytes */
            Utils_memcpyWord(pSrc, pDst, initResidualBytes);
            CacheP_wbInv(pDst, initResidualBytes, CacheP_TYPE_ALL);

            tempDst = (uint8_t *)((uint32_t)pDst + initResidualBytes);
            tempSrc = (uint8_t *)((uint32_t)pSrc + initResidualBytes);
            remainingBytes -= initResidualBytes;
        }

        /* Do DMA copy for 32B-aligned bytes */
        uint32_t unalignedBytes = (remainingBytes % UDMA_DMA_COPY_SIZE_ALIGNMENT);

        Bootloader_dmaDirectCopy(udmaDmaArgs, tempDst, tempSrc, remainingBytes - unalignedBytes);

        /* Do a CPU copy of unaligned bytes if any */
        if(unalignedBytes > 0)
        {
            tempDst += (remainingBytes - unalignedBytes);
            tempSrc += (remainingBytes - unalignedBytes);
            Utils_memcpyWord(tempSrc, tempDst, unalignedBytes);
            CacheP_wbInv(tempDst, unalignedBytes, CacheP_TYPE_ALL);
        }
    }
    else
    {
        Utils_memcpyWord(pSrc, pDst, length);
        CacheP_wbInv(pDst, length, CacheP_TYPE_ALL);
    }

    return status;
}