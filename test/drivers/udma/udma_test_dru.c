/*
 * Copyright (C) 2025-2026 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 * @file test_dru.c
 * @brief The following test aims at DRU related api validation.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>

#include <drivers/udma.h>
#include <drivers/udma/v0/include/udma_types.h>
#include <drivers/udma/v0/include/udma_ch.h>
#include <drivers/hw_include/dru/v2/csl_dru.h>
#include <drivers/udma/v0/include/udma_utils.h>
#include <drivers/udma/v0/include/csl_udmap_tr.h>
#include <drivers/udma/v0/include/csl_udmap_cppi5.h>
#include <drivers/udma/v0/include/udma_event.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/AddrTranslateP.h>
#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/SystemP.h>

#include "ti_drivers_config.h"
#include "ti_board_open_close.h"
#include "ti_drivers_open_close.h"
#include "udma_test.h"

#include <drivers/hw_include/cslr_soc.h>
#include <kernel/nortos/dpl/c75/csl_clec.h>
#include <c7x.h>
#include "drivers/dmautils/include/dmautils_autoincrement_3d.h"
#include "drivers/dmautils/src/dmautils_autoincrement_3d_priv.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TEST_UDMA_NUM_BYTES                      (1024U)
#define TEST_UDMA_TRPD_SIZE                      (UDMA_GET_TRPD_TR15_SIZE(1U))
/** \brief Number of ring entries */
#define TEST_UDMA_APP_RING_ENTRIES               (1U)
/** \brief Size (in bytes) of each ring entry */
#define TEST_UDMA_APP_RING_ENTRY_SIZE            (sizeof(uint64_t))
/** \brief Total ring memory */
#define TEST_UDMA_APP_RING_MEM_SIZE              (TEST_UDMA_APP_RING_ENTRIES * \
                                                  TEST_UDMA_APP_RING_ENTRY_SIZE)
/** \brief This ensures every channel memory is aligned */
#define TEST_UDMA_APP_RING_MEM_SIZE_ALIGN        ((TEST_UDMA_APP_RING_MEM_SIZE + UDMA_CACHELINE_ALIGNMENT) & ~(UDMA_CACHELINE_ALIGNMENT - 1U))
/** \brief UDMA TR packet descriptor memory */
#define TEST_UDMA_APP_TRPD_SIZE                  (TEST_UDMA_TRPD_SIZE)
/** \brief This ensures every channel memory is aligned */
#define TEST_UDMA_APP_TRPD_SIZE_ALIGN            ((TEST_UDMA_APP_TRPD_SIZE + UDMA_CACHELINE_ALIGNMENT) & ~(UDMA_CACHELINE_ALIGNMENT - 1U))
/* Fill before transfer */
#define TEST_UDMA_POISON_PATTERN_BYTE            (0xA5U)
#define TEST_UDMA_BUF_ATTR __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)))
/* event */
#define TEST_DMAUTILS_TC_LEN                     (512U)
/* DRU local input event base in the CLEC */
#define TEST_DRU_CLEC_LOCAL_EVENT_START          (128U)
/* C7x output event base used in CLEC mapping */
#define TEST_DRU_C7X_EVT_BASE                    (32U)
#define TEST_DRU_NUM_OF_CHANNELS                 (16U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Application Buffers */
static uint8_t TestUdma_SrcBuf[UDMA_ALIGN_SIZE(TEST_UDMA_NUM_BYTES)] TEST_UDMA_BUF_ATTR;
static uint8_t TestUdma_DestBuf[UDMA_ALIGN_SIZE(TEST_UDMA_NUM_BYTES)] TEST_UDMA_BUF_ATTR;
/* Global buffers for dmautils DRU direct tests */
static uint8_t TestUdma_DruCtxMem[8192] __attribute__((aligned(128)));
static uint8_t TestUdma_DruTrMem[512] __attribute__((aligned(128)));
static uint8_t TestUdma_DruTrMem2[512] __attribute__((aligned(128)));
static uint8_t TestUdma_L2Scratch[64*1024] __attribute__((aligned(128)));
static uint8_t TestUdma_CmpInput[128*64] __attribute__((aligned(128)));
static uint8_t TestUdma_CmpCompressed[128*64*3 + 128] __attribute__((aligned(128)));
static uint8_t TestUdma_CmpOutput[128*64] __attribute__((aligned(128)));
static uint8_t TestUdma_CmpSectr[128*64 + 128] __attribute__((aligned(128)));
/* ISR */
static HwiP_Object TestUdma_HwiObject;
static SemaphoreP_Object TestUdma_DmaDruSem;

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

                            /* None */

/* ========================================================================== */
/*                      Internal Function Declarations                        */
/* ========================================================================== */

static void TestUdma_appUdmaInitBuf(uint8_t *srcBuf, uint8_t *destBuf, uint32_t length);
static int32_t TestUdma_appUdmaCompareBuf(uint8_t *srcBuf, uint8_t *destBuf, uint32_t length);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static void TestUdma_dmaCompletionIsr(void *arg)
{
    (void)arg;
    SemaphoreP_post(&TestUdma_DmaDruSem);
}

/* Helper: Initialize source and destination buffers for memcpy tests.
 * Source is filled with incremental pattern 0..length-1 while destination is
 * poisoned with 0xA5 to detect incomplete transfers. Performs cache writeback
 * for both buffers to ensure coherence before DMA submission. */
static void TestUdma_appUdmaInitBuf(uint8_t *srcBuf, uint8_t *destBuf, uint32_t length)
{
    uint32_t i;

    for(i = 0U; i < length; i++)
    {
        srcBuf[i] = i;
        destBuf[i] = TEST_UDMA_POISON_PATTERN_BYTE;
    }
    /* Writeback source and destination buffer */
    CacheP_wb(srcBuf, length, CacheP_TYPE_ALLD);
    CacheP_wb(destBuf, length, CacheP_TYPE_ALLD);

    return;
}

/* Helper: Compare source and destination buffers after a transfer.
 * Invalidates destination cache lines, iterates and asserts equality. On first
 * mismatch logs error and triggers debug assert for immediate test failure. */
static int32_t TestUdma_appUdmaCompareBuf(uint8_t *srcBuf, uint8_t *destBuf, uint32_t length)
{
    uint32_t i;

    /* Invalidate destination buffer */
    CacheP_inv(destBuf, length, CacheP_TYPE_ALLD);
    for(i = 0U; i < length; i++)
    {
        if(srcBuf[i] != destBuf[i])
        {
            DebugP_logError("Data mismatch !!!\r\n");
            TEST_FAIL_MESSAGE("Data mismatch detected in buffer comparison");
            return UDMA_EFAIL;
        }
    }

    return UDMA_SOK;
}

void TestUdma_appdmautilsClecInitDru(void)
{
    CSL_ClecEventConfig     cfgClec;
    CSL_CLEC_EVTRegs        *clecBaseAddr;
    uint32_t                clusterId;
    uint32_t i;
    /* Local input event base in CLEC for DRU */
    uint32_t druClecInputStart;
    uint32_t druInputNum;
    clusterId = CSL_clecGetC7xClusterId();
    if(clusterId == CSL_C75_CPU_CLUSTER_NUM_C75_1)
    {
        clecBaseAddr = (CSL_CLEC_EVTRegs * ) CSL_C7X256V0_CLEC_BASE;
    }
#if(CSL_C7X256V_MAIN_CNT == 2U)
    else if (clusterId == CSL_C75_CPU_CLUSTER_NUM_C75_2)
    {
        clecBaseAddr = (CSL_CLEC_EVTRegs * ) CSL_C7X256V1_CLEC_BASE;
    }
#endif
    else
    {
        clecBaseAddr = (CSL_CLEC_EVTRegs *) NULL;
    }

    if(clecBaseAddr != NULL)
    {
        druClecInputStart = TEST_DRU_CLEC_LOCAL_EVENT_START;
        druInputNum   = TEST_DRU_NUM_OF_CHANNELS;

        /* Only configuring the configured number of DRU channels */
        for(i = druClecInputStart; i < (druClecInputStart + druInputNum); i++)
        {
            /* Configure CLEC */
            cfgClec.secureClaimEnable = FALSE;
            cfgClec.evtSendEnable     = TRUE;
            cfgClec.rtMap             = CSL_CLEC_RTMAP_CPU_ALL;
            cfgClec.extEvtNum         = 0;
            cfgClec.c7xEvtNum         = (i - druClecInputStart) + TEST_DRU_C7X_EVT_BASE;
            CSL_clecConfigEvent(clecBaseAddr, i, &cfgClec);
        }
    }
}

/**
 * \brief DRU Direct Polling DMAUTILS test.
 *
 * Test Category: Functional
 *
 * Validates DRU direct transfer using DMAUTILS with polling for completion.
 * Initializes source/destination buffers, configures DMAUTILS context and
 * triggers transfer.
 * Verifies data integrity after transfer.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput DMA transfer completes successfully; destination buffer
 * matches source.
 */
void TestUdma_dmautilsDruDirectPolling(void *args)
{
    Udma_DrvObject udmaDrvObj;
    Udma_DrvHandle drvHandle = &udmaDrvObj;
    Udma_InitPrms initPrms;
    uint8_t *srcBuf = &TestUdma_SrcBuf[0U];
    uint8_t *dstBuf = &TestUdma_DestBuf[0U];
    uint8_t *ctxMem = &TestUdma_DruCtxMem[0U];
    uint8_t *trMem  = &TestUdma_DruTrMem[0U];
    int32_t retVal;
    uint32_t blockIdx;
    DmaUtilsAutoInc3d_InitParam initParams;
    DmaUtilsAutoInc3d_ChannelInitParam chInitParams[1];
    DmaUtilsAutoInc3d_TransferProp transferPropIn;
    DmaUtilsAutoInc3d_TrPrepareParam trPrepParam;

    TestUdma_appUdmaInitBuf(srcBuf, dstBuf, TEST_DMAUTILS_TC_LEN);
    UdmaInitPrms_init(UDMA_INST_ID_0, &initPrms);
    initPrms.instId = UDMA_INST_ID_0;
    initPrms.enableUtc = UTRUE;
    retVal = Udma_init(drvHandle, &initPrms);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "Udma_init failed (dmautils)");

    initParams.contextSize = DmaUtilsAutoInc3d_getContextSize(1);
    initParams.numChannels = 1;
    initParams.traceLogLevel = 0;
    initParams.udmaDrvHandle = drvHandle;
    initParams.DmaUtilsVprintf = vprintf;
    chInitParams[0].dmaQueNo = 0;
    chInitParams[0].druOwner = DMAUTILSAUTOINC3D_DRUOWNER_DIRECT_TR;
    retVal = DmaUtilsAutoInc3d_init(ctxMem, &initParams, chInitParams);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "dmautils init failed");

    memset(&transferPropIn, 0, sizeof(transferPropIn));
    transferPropIn.transferDim.sicnt0 = TEST_DMAUTILS_TC_LEN;
    transferPropIn.transferDim.sicnt1 = 1;
    transferPropIn.transferDim.sicnt2 = 1;
    transferPropIn.transferDim.sicnt3 = 1;
    transferPropIn.transferDim.sdim1 = TEST_DMAUTILS_TC_LEN;
    transferPropIn.transferDim.sdim2 = TEST_DMAUTILS_TC_LEN;
    transferPropIn.transferDim.sdim3 = TEST_DMAUTILS_TC_LEN;
    transferPropIn.transferDim.dicnt0 = TEST_DMAUTILS_TC_LEN;
    transferPropIn.transferDim.dicnt1 = 1;
    transferPropIn.transferDim.dicnt2 = 1;
    transferPropIn.transferDim.dicnt3 = 1;
    transferPropIn.transferDim.ddim1 = TEST_DMAUTILS_TC_LEN;
    transferPropIn.transferDim.ddim2 = TEST_DMAUTILS_TC_LEN;
    transferPropIn.transferDim.ddim3 = TEST_DMAUTILS_TC_LEN;
    transferPropIn.ioPointers.srcPtr = srcBuf;
    transferPropIn.ioPointers.dstPtr = dstBuf;
    transferPropIn.syncType = DMAUTILSAUTOINC3D_SYNC_1D;
    trPrepParam.channelId = 0;
    trPrepParam.numTRs = 1;
    trPrepParam.trMem = trMem;
    trPrepParam.trMemSize = DmaUtilsAutoInc3d_getTrMemReq(1);
    retVal = DmaUtilsAutoInc3d_prepareTr(&trPrepParam, &transferPropIn);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "prepareTr failed");
    retVal = DmaUtilsAutoInc3d_configure(ctxMem, 0, trMem, 1);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "configure failed");
    while ( 1 )
    {
        /* DMA trigger */
        blockIdx = DmaUtilsAutoInc3d_trigger(ctxMem, 0);
        /* Wait for completion */
        DmaUtilsAutoInc3d_wait(ctxMem, 0);

        if ( blockIdx == 0 )
        {
            break;
        }
    }
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, TestUdma_appUdmaCompareBuf(srcBuf, dstBuf, TEST_DMAUTILS_TC_LEN), "dmautils polling compare failed");
    retVal = DmaUtilsAutoInc3d_deconfigure(ctxMem, 0, trMem, 1);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "deconfigure failed");
    retVal = DmaUtilsAutoInc3d_deinit(ctxMem);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "deinit failed");
    retVal = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
}

/**
 * \brief DRU Direct Interrupt DMAUTILS test.
 *
 * Test Category: Functional
 *
 * Validates DRU direct transfer using DMAUTILS with interrupt-based completion.
 * Sets up event mapping and HWI, triggers transfer, and checks ISR execution.
 * Verifies data integrity after transfer.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput DMA transfer completes and ISR is called; destination
 * buffer matches source.
 */
void TestUdma_dmautilsDruDirectInterrupt(void *args)
{
    Udma_DrvObject udmaDrvObj;
    Udma_DrvHandle drvHandle = &udmaDrvObj;
    Udma_InitPrms initPrms;
    uint8_t *srcBuf = &TestUdma_SrcBuf[0U];
    uint8_t *dstBuf = &TestUdma_DestBuf[0U];
    uint8_t *ctxMem = &TestUdma_DruCtxMem[0U];
    uint8_t *trMem  = &TestUdma_DruTrMem[0U];
    int32_t retVal;
    DmaUtilsAutoInc3d_InitParam initParams;
    DmaUtilsAutoInc3d_ChannelInitParam chInitParams[1];
    DmaUtilsAutoInc3d_TransferProp transferPropIn;
    DmaUtilsAutoInc3d_TrPrepareParam trPrepParam;
    DmaUtilsAutoInc3d_Context *ctx;
    DmaUtilsAutoInc3d_ChannelContext *chCtx;
    uint32_t druCh;
    uint32_t druEvent;
    uint32_t c7xEvent;
    HwiP_Params hwiPrms;

    TestUdma_appUdmaInitBuf(srcBuf, dstBuf, TEST_DMAUTILS_TC_LEN);
    UdmaInitPrms_init(UDMA_INST_ID_0, &initPrms);
    initPrms.instId = UDMA_INST_ID_0;
    initPrms.enableUtc = UTRUE;
    retVal = Udma_init(drvHandle, &initPrms);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "Udma_init failed (dmautils)");

    initParams.contextSize = DmaUtilsAutoInc3d_getContextSize(1);
    initParams.numChannels = 1;
    initParams.traceLogLevel = 0;
    initParams.udmaDrvHandle = drvHandle;
    initParams.DmaUtilsVprintf = vprintf;
    chInitParams[0].dmaQueNo = 0;
    chInitParams[0].druOwner = DMAUTILSAUTOINC3D_DRUOWNER_DIRECT_TR;
    retVal = DmaUtilsAutoInc3d_init(ctxMem, &initParams, chInitParams);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "dmautils init failed");
    memset(&transferPropIn, 0, sizeof(transferPropIn));
    transferPropIn.transferDim.sicnt0 = TEST_DMAUTILS_TC_LEN;
    transferPropIn.transferDim.sicnt1 = 1;
    transferPropIn.transferDim.sicnt2 = 1;
    transferPropIn.transferDim.sicnt3 = 1;
    transferPropIn.transferDim.sdim1 = TEST_DMAUTILS_TC_LEN;
    transferPropIn.transferDim.sdim2 = TEST_DMAUTILS_TC_LEN;
    transferPropIn.transferDim.sdim3 = TEST_DMAUTILS_TC_LEN;
    transferPropIn.transferDim.dicnt0 = TEST_DMAUTILS_TC_LEN;
    transferPropIn.transferDim.dicnt1 = 1;
    transferPropIn.transferDim.dicnt2 = 1;
    transferPropIn.transferDim.dicnt3 = 1;
    transferPropIn.transferDim.ddim1 = TEST_DMAUTILS_TC_LEN;
    transferPropIn.transferDim.ddim2 = TEST_DMAUTILS_TC_LEN;
    transferPropIn.transferDim.ddim3 = TEST_DMAUTILS_TC_LEN;
    transferPropIn.ioPointers.srcPtr = srcBuf;
    transferPropIn.ioPointers.dstPtr = dstBuf;
    transferPropIn.syncType = DMAUTILSAUTOINC3D_SYNC_1D;
    trPrepParam.channelId = 0;
    trPrepParam.numTRs = 1;
    trPrepParam.trMem = trMem;
    trPrepParam.trMemSize = DmaUtilsAutoInc3d_getTrMemReq(1);
    ctx = (DmaUtilsAutoInc3d_Context *)ctxMem;
    chCtx = ctx->channelContext[0];
    druCh = chCtx->druChannelId;
    druEvent = TEST_DRU_CLEC_LOCAL_EVENT_START + druCh;
    c7xEvent = TEST_DRU_C7X_EVT_BASE + druCh;

    HwiP_Params_init(&hwiPrms);
    /* Construct binary semaphore for ISR notification */
    retVal = SemaphoreP_constructBinary(&TestUdma_DmaDruSem, 0);
    TEST_ASSERT_EQUAL_INT_MESSAGE(SystemP_SUCCESS, retVal, "Semaphore construct failed");
    /* Register HWI on the C7x output event */
    hwiPrms.eventId  = druEvent;
    hwiPrms.intNum   = c7xEvent;
    hwiPrms.callback = TestUdma_dmaCompletionIsr;
    hwiPrms.args     = NULL;
    hwiPrms.isPulse  = 0U;
    retVal = HwiP_construct(&TestUdma_HwiObject, &hwiPrms);
    TEST_ASSERT_EQUAL_INT(SystemP_SUCCESS, retVal);

    retVal = DmaUtilsAutoInc3d_prepareTr(&trPrepParam, &transferPropIn);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "prepareTr failed");
    retVal = DmaUtilsAutoInc3d_configure(ctxMem, 0, trMem, 1);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "configure failed");
    /* DMA trigger */
    retVal = DmaUtilsAutoInc3d_trigger(ctxMem, 0);
    /* Wait for ISR to post semaphore (timeout 5s) */
    retVal = SemaphoreP_pend(&TestUdma_DmaDruSem, 5000);
    TEST_ASSERT_EQUAL_INT_MESSAGE(SystemP_SUCCESS, retVal, "ISR call timed out");
    CacheP_inv(dstBuf, TEST_DMAUTILS_TC_LEN, CacheP_TYPE_ALLD);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, TestUdma_appUdmaCompareBuf(srcBuf, dstBuf, TEST_DMAUTILS_TC_LEN), "dmautils data mismatch");
    retVal = DmaUtilsAutoInc3d_deconfigure(ctxMem, 0, trMem, 1);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "deconfigure failed");
    retVal = DmaUtilsAutoInc3d_deinit(ctxMem);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "deinit failed");
    retVal = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    /* Destruct HwiP object to unregister interrupt handler */
    HwiP_destruct(&TestUdma_HwiObject);
    /* Destruct semaphore */
    SemaphoreP_destruct(&TestUdma_DmaDruSem);
}

/**
 * \brief DRU Direct 2D DMAUTILS test.
 *
 * Test Category: Functional
 *
 * Validates DRU direct transfer using DMAUTILS with 2D auto-increment.
 * Configures a 2D block-move with width/height and block tiling;
 * verifies data integrity.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput DMA transfer completes successfully; destination buffer
 * matches source.
 */
void TestUdma_dmautilsDruDirect2D(void *args)
{
    (void)args;
    Udma_DrvObject udmaDrvObj;
    Udma_DrvHandle drvHandle = &udmaDrvObj;
    Udma_InitPrms initPrms;
    uint8_t *srcBuf = &TestUdma_SrcBuf[0U];
    uint8_t *dstBuf = &TestUdma_DestBuf[0U];
    uint8_t *ctxMem = &TestUdma_DruCtxMem[0U];
    uint8_t *trMem  = &TestUdma_DruTrMem[0U];
    uint32_t blockIdx;
    int32_t retVal;
    /* Image and block geometry */
    const uint16_t width = 32U;
    const uint16_t height = 16U;
    const uint16_t inPitch = width;
    const uint16_t outPitch = width;
    const uint16_t blockWidth = 8U;
    const uint16_t blockHeight = 4U;
    DmaUtilsAutoInc3d_InitParam initParams;
    DmaUtilsAutoInc3d_ChannelInitParam chInitParams[1];
    DmaUtilsAutoInc3d_TransferProp transferPropIn;
    DmaUtilsAutoInc3d_TrPrepareParam trPrepParam;
    /* Initialize 2D pattern in src and zero dst */
    uint16_t i, j;
    for(j = 0; j < height; j++)
    {
        for(i = 0; i < width; i++)
        {
            srcBuf[j * inPitch + i] = (uint8_t)(i + (j * 7U));
            dstBuf[j * outPitch + i] = 0U;
        }
    }
    CacheP_wb(srcBuf, width * height, CacheP_TYPE_ALLD);
    CacheP_wb(dstBuf, width * height, CacheP_TYPE_ALLD);
    UdmaInitPrms_init(UDMA_INST_ID_0, &initPrms);
    initPrms.instId = UDMA_INST_ID_0;
    initPrms.enableUtc = UTRUE;
    retVal = Udma_init(drvHandle, &initPrms);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "Udma_init failed (dmautils 2D)");

    initParams.contextSize = DmaUtilsAutoInc3d_getContextSize(1);
    initParams.numChannels = 1;
    initParams.traceLogLevel = 0;
    initParams.udmaDrvHandle = drvHandle;
    initParams.DmaUtilsVprintf = vprintf;
    chInitParams[0].dmaQueNo = 0;
    chInitParams[0].druOwner = DMAUTILSAUTOINC3D_DRUOWNER_DIRECT_TR;
    retVal = DmaUtilsAutoInc3d_init(ctxMem, &initParams, chInitParams);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "dmautils init failed (2D)");

    memset(&transferPropIn, 0, sizeof(transferPropIn));
    /* Set 2D auto-increment transfer dimensions */
    transferPropIn.transferDim.sicnt0 = blockWidth;
    transferPropIn.transferDim.sicnt1 = blockHeight;
    transferPropIn.transferDim.sicnt2 = width / blockWidth;
    transferPropIn.transferDim.sicnt3 = height / blockHeight;
    transferPropIn.transferDim.sdim1 = inPitch;
    transferPropIn.transferDim.sdim2 = blockWidth;
    transferPropIn.transferDim.sdim3 = (int16_t)(blockHeight * inPitch);
    transferPropIn.transferDim.dicnt0 = blockWidth;
    transferPropIn.transferDim.dicnt1 = blockHeight;
    transferPropIn.transferDim.dicnt2 = width / blockWidth;
    transferPropIn.transferDim.dicnt3 = height / blockHeight;
    transferPropIn.transferDim.ddim1 = outPitch;
    transferPropIn.transferDim.ddim2 = blockWidth;
    transferPropIn.transferDim.ddim3 = (int16_t)(outPitch * blockHeight);
    transferPropIn.ioPointers.srcPtr = srcBuf;
    transferPropIn.ioPointers.dstPtr = dstBuf;
    transferPropIn.syncType = DMAUTILSAUTOINC3D_SYNC_2D;
    trPrepParam.channelId = 0;
    trPrepParam.numTRs = 1;
    trPrepParam.trMem = trMem;
    trPrepParam.trMemSize = DmaUtilsAutoInc3d_getTrMemReq(1);
    retVal = DmaUtilsAutoInc3d_prepareTr(&trPrepParam, &transferPropIn);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "prepareTr failed (2D)");
    retVal = DmaUtilsAutoInc3d_configure(ctxMem, 0, trMem, 1);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "configure failed (2D)");
    while ( 1 )
    {
        blockIdx = DmaUtilsAutoInc3d_trigger(ctxMem, 0);
        DmaUtilsAutoInc3d_wait(ctxMem, 0);
        if ( blockIdx == 0 )
        {
            break;
        }
    }

    /* Validate */
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, TestUdma_appUdmaCompareBuf(srcBuf, dstBuf, (uint32_t)(width * height)), "dmautils 2D compare failed");
    retVal = DmaUtilsAutoInc3d_deconfigure(ctxMem, 0, trMem, 1);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "deconfigure failed (2D)");
    retVal = DmaUtilsAutoInc3d_deinit(ctxMem);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "deinit failed (2D)");
    retVal = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
}

/**
 * \brief DRU Direct 3D DMAUTILS test.
 *
 * Test Category: Functional
 *
 * Validates DRU direct transfer using DMAUTILS with 3D auto-increment.
 * Configures a 3D block-move by stacking multiple 2D planes;
 * verifies data integrity.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput DMA transfer completes successfully; destination buffer
 * matches source.
 */
void TestUdma_dmautilsDruDirect3D(void *args)
{
    (void)args;
    Udma_DrvObject udmaDrvObj;
    Udma_DrvHandle drvHandle = &udmaDrvObj;
    Udma_InitPrms initPrms;
    uint8_t *srcBuf = &TestUdma_SrcBuf[0U];
    uint8_t *dstBuf = &TestUdma_DestBuf[0U];
    uint8_t *ctxMem = &TestUdma_DruCtxMem[0U];
    uint8_t *trMem  = &TestUdma_DruTrMem[0U];
    int32_t retVal;
    DmaUtilsAutoInc3d_InitParam initParams;
    DmaUtilsAutoInc3d_ChannelInitParam chInitParams[1];
    DmaUtilsAutoInc3d_TransferProp transferPropIn;
    DmaUtilsAutoInc3d_TrPrepareParam trPrepParam;
    /* 3D geometry */
    const uint16_t width = 16U;
    const uint16_t height = 8U;
    const uint16_t depth = 4U;
    const uint16_t inPitch = width;
    const uint16_t outPitch = width;
    const uint16_t blockWidth = 8U;
    const uint16_t blockHeight = 4U;
    const uint32_t planeSize = (uint32_t)width * (uint32_t)height;
    const uint32_t totalSize = planeSize * depth;
    /* Pattern across 3D */
    uint16_t i, j, k;
    uint32_t base, blockIdx;
    for( k = 0; k < depth; k++)
    {
        base = k * planeSize;
        for(j = 0; j < height; j++)
        {
            for(i = 0; i < width; i++)
            {
                srcBuf[base + j * inPitch + i] = (uint8_t)(i + (j * 3U) + (k * 17U));
                dstBuf[base + j * outPitch + i] = 0U;
            }
        }
    }
    CacheP_wb(srcBuf, totalSize, CacheP_TYPE_ALLD);
    CacheP_wb(dstBuf, totalSize, CacheP_TYPE_ALLD);
    UdmaInitPrms_init(UDMA_INST_ID_0, &initPrms);
    initPrms.instId = UDMA_INST_ID_0;
    initPrms.enableUtc = UTRUE;
    retVal = Udma_init(drvHandle, &initPrms);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "Udma_init failed (dmautils 3D)");

    initParams.contextSize = DmaUtilsAutoInc3d_getContextSize(1);
    initParams.numChannels = 1;
    initParams.traceLogLevel = 0;
    initParams.udmaDrvHandle = drvHandle;
    initParams.DmaUtilsVprintf = vprintf;
    chInitParams[0].dmaQueNo = 0;
    chInitParams[0].druOwner = DMAUTILSAUTOINC3D_DRUOWNER_DIRECT_TR;
    retVal = DmaUtilsAutoInc3d_init(ctxMem, &initParams, chInitParams);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "dmautils init failed (3D)");

    memset(&transferPropIn, 0, sizeof(transferPropIn));
    transferPropIn.transferDim.sicnt0 = blockWidth;
    transferPropIn.transferDim.sicnt1 = blockHeight;
    transferPropIn.transferDim.sicnt2 = width / blockWidth;
    transferPropIn.transferDim.sicnt3 = (height / blockHeight) * depth;
    transferPropIn.transferDim.sdim1 = inPitch;
    transferPropIn.transferDim.sdim2 = blockWidth;
    transferPropIn.transferDim.sdim3 = (int16_t)(blockHeight * inPitch);
    transferPropIn.transferDim.dicnt0 = blockWidth;
    transferPropIn.transferDim.dicnt1 = blockHeight;
    transferPropIn.transferDim.dicnt2 = width / blockWidth;
    transferPropIn.transferDim.dicnt3 = (height / blockHeight) * depth;
    transferPropIn.transferDim.ddim1 = outPitch;
    transferPropIn.transferDim.ddim2 = blockWidth;
    transferPropIn.transferDim.ddim3 = (int16_t)(outPitch * blockHeight);
    transferPropIn.ioPointers.srcPtr = srcBuf;
    transferPropIn.ioPointers.dstPtr = dstBuf;
    transferPropIn.syncType = DMAUTILSAUTOINC3D_SYNC_3D;
    trPrepParam.channelId = 0;
    trPrepParam.numTRs = 1;
    trPrepParam.trMem = trMem;
    trPrepParam.trMemSize = DmaUtilsAutoInc3d_getTrMemReq(1);
    retVal = DmaUtilsAutoInc3d_prepareTr(&trPrepParam, &transferPropIn);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "prepareTr failed (3D)");
    retVal = DmaUtilsAutoInc3d_configure(ctxMem, 0, trMem, 1);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "configure failed (3D)");
    while ( 1 )
    {
        blockIdx = DmaUtilsAutoInc3d_trigger(ctxMem, 0);
        DmaUtilsAutoInc3d_wait(ctxMem, 0);
        if ( blockIdx == 0 )
        {
            break;
        }
    }
    /* Validate entire 3D volume */
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, TestUdma_appUdmaCompareBuf(srcBuf, dstBuf, totalSize), "dmautils 3D compare failed");
    retVal = DmaUtilsAutoInc3d_deconfigure(ctxMem, 0, trMem, 1);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "deconfigure failed (3D)");
    retVal = DmaUtilsAutoInc3d_deinit(ctxMem);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "deinit failed (3D)");
    retVal = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
}

/**
 * \brief DMAUTILS Auto-Increment Compression/Decompression test.
 *
 * Test Category: Functional
 *
 * Validates analytic compression and decompression using DMAUTILS and DRU.
 * Compresses a patterned tensor, decompresses it, and checks
 * round-trip data integrity.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Compression and decompression complete; decompressed output
 * matches original input.
 */
void TestUdma_dmautilsAutoIncCompression(void *args)
{
    (void)args;
    Udma_DrvObject udmaDrvObj;
    Udma_DrvHandle drvHandle = &udmaDrvObj;
    Udma_InitPrms initPrms;
    DmaUtilsAutoInc3d_InitParam initParams;
    DmaUtilsAutoInc3d_ChannelInitParam chInitParams[1];
    DmaUtilsAutoInc3d_TrPrepareParam trPrepParam;
    DmaUtilsAutoInc3d_TransferProp tp;
    DmaUtilsAutoInc3d_TransferProp tp2;
    const uint32_t tensorWidth  = 16U;
    const uint32_t tensorHeight = 8U;
    const uint32_t sbWidth      = 16U;
    const uint32_t sbHeight     = 8U;
    const uint32_t outProcSize  = 16U;
    const uint32_t inProcSize   = 16U;
    const uint8_t  algorithm    = 1U;
    const uint8_t  bias         = 0U;
    const int32_t CIBLENGTH     = 8;
    const int32_t CIBLENGTH2    = 8;
    uint8_t *input      = &TestUdma_CmpInput[0];
    uint8_t *compressed = &TestUdma_CmpCompressed[0];
    uint8_t *sectr      = &TestUdma_CmpSectr[0];
    uint8_t *output     = &TestUdma_CmpOutput[0];
    uint8_t *ctxMem     = &TestUdma_L2Scratch[0];
    uint32_t i, j, t, u;;
    int32_t retVal;
    uint32_t triggers, triggers2;

    /* Initialize a pattern */
    for(j = 0; j < tensorHeight; j++)
    {
        for(i = 0; i < tensorWidth; i++)
        {
            input[j * tensorWidth + i] = (uint8_t)(i + j);
        }
    }
    memset(compressed, 0, tensorWidth * tensorHeight * 3);
    memset(output, 0, tensorWidth * tensorHeight);
    /* CDB table: widthBlocks=1, heightBlocks=1 -> size = 8*1 + 64 = 72 */
    const uint32_t sectrSize = 72U;
    memset(sectr, 0, sectrSize);
    CacheP_wb(input, tensorWidth * tensorHeight, CacheP_TYPE_ALLD);
    CacheP_wb(compressed, tensorWidth * tensorHeight * 3, CacheP_TYPE_ALLD);
    CacheP_wb(output, tensorWidth * tensorHeight, CacheP_TYPE_ALLD);
    CacheP_wb(sectr, sectrSize, CacheP_TYPE_ALLD);

    /* UDMA + dmautils init */
    UdmaInitPrms_init(UDMA_INST_ID_0, &initPrms);
    initPrms.instId = UDMA_INST_ID_0;
    initPrms.enableUtc = UTRUE;
    retVal = Udma_init(drvHandle, &initPrms);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "Udma_init failed (compression simple)");

    initParams.contextSize = DmaUtilsAutoInc3d_getContextSize(1);
    initParams.numChannels = 1;
    initParams.traceLogLevel = 0;
    initParams.udmaDrvHandle = drvHandle;
    initParams.DmaUtilsVprintf = vprintf;
    chInitParams[0].dmaQueNo = 0;
    chInitParams[0].druOwner = DMAUTILSAUTOINC3D_DRUOWNER_DIRECT_TR;
    retVal = DmaUtilsAutoInc3d_init(ctxMem, &initParams, chInitParams);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "dmautils init failed (simple)");
    trPrepParam.channelId = 0;
    trPrepParam.numTRs = 1;
    trPrepParam.trMem = &TestUdma_DruTrMem[0];
    trPrepParam.trMemSize = DmaUtilsAutoInc3d_getTrMemReq(1);
    /* Compression (ROW flow, single superblock) */
    memset(&tp, 0, sizeof(tp));
    tp.syncType = DMAUTILSAUTOINC3D_SYNC_2D;
    tp.dmaDfmt  = DMAUTILSAUTOINC3D_DFMT_COMP;
    /* With sbWidth=16, outProcSize=16 -> icnt0=1 */
    tp.transferDim.sicnt0 = 1;
    tp.transferDim.sicnt1 = 1;
    tp.transferDim.sicnt2 = 2;
    tp.transferDim.sicnt3 = 1;
    tp.transferDim.dicnt0 = tp.transferDim.sicnt0;
    tp.transferDim.dicnt1 = tp.transferDim.sicnt1;
    tp.transferDim.dicnt2 = 1;
    tp.transferDim.dicnt3 = 1;
    tp.transferDim.sdim1 = (int16_t)(tensorWidth * sbHeight);
    tp.transferDim.sdim2 = (int16_t)outProcSize;
    tp.transferDim.sdim3 = (int16_t)(2 * outProcSize);
    tp.transferDim.ddim1 = (int16_t)(CIBLENGTH);
    tp.transferDim.ddim2 = (int16_t)(tp.transferDim.sicnt0 * CIBLENGTH);
    tp.transferDim.ddim3 = 0;
    tp.cmpProp.cmpAlg = algorithm;
    tp.cmpProp.cmpBias = bias;
    tp.cmpProp.sbIcnt0 = (uint8_t)(sbWidth / 16);
    tp.cmpProp.sbIcnt1 = (uint8_t)sbHeight;
    tp.cmpProp.sbDim1  = (uint16_t)tensorWidth;
    tp.cmpProp.sbAM0   = 0;
    tp.cmpProp.sbAM1   = 0;
    tp.cmpProp.sDim0   = (int16_t)sbWidth;
    tp.cmpProp.dDim0   = (int16_t)CIBLENGTH;
    tp.ioPointers.srcPtr = input;
    tp.ioPointers.dstPtr = compressed;
    tp.ioPointers.strPtr = sectr;
    tp.ioPointers.cdbPtr = sectr + 32;
    retVal = DmaUtilsAutoInc3d_prepareTr(&trPrepParam, &tp);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "prepareTr (comp simple) failed");
    retVal = DmaUtilsAutoInc3d_configure(ctxMem, 0, &TestUdma_DruTrMem[0], 1);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "configure (comp simple) failed");

    triggers = (((uint32_t)tp.transferDim.sicnt2 * (uint32_t)tp.transferDim.sicnt3) <
                    ((uint32_t)tp.transferDim.dicnt2 * (uint32_t)tp.transferDim.dicnt3)) ?
                    ((uint32_t)tp.transferDim.sicnt2 * (uint32_t)tp.transferDim.sicnt3) :
                    ((uint32_t)tp.transferDim.dicnt2 * (uint32_t)tp.transferDim.dicnt3);
    for (t = 0U; t < triggers; t++)
    {
        DmaUtilsAutoInc3d_trigger(ctxMem, 0);
        DmaUtilsAutoInc3d_wait(ctxMem, 0);
    }
    retVal = DmaUtilsAutoInc3d_deconfigure(ctxMem, 0, &TestUdma_DruTrMem[0], 1);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "deconfigure (comp simple) failed");

    /* Decompression (ROW flow, single superblock) */
    memset(&tp2, 0, sizeof(tp2));
    tp2.syncType = DMAUTILSAUTOINC3D_SYNC_2D;
    tp2.dmaDfmt  = DMAUTILSAUTOINC3D_DFMT_DECOMP;

    tp2.transferDim.sicnt0 = 1;
    tp2.transferDim.sicnt1 = 1;
    tp2.transferDim.sicnt2 = 1;
    tp2.transferDim.sicnt3 = 1;
    tp2.transferDim.dicnt0 = tp2.transferDim.sicnt0;
    tp2.transferDim.dicnt1 = tp2.transferDim.sicnt1;
    tp2.transferDim.dicnt2 = 2;
    tp2.transferDim.dicnt3 = 1;
    tp2.transferDim.sdim1 = (int16_t)(CIBLENGTH2);
    tp2.transferDim.sdim2 = (int16_t)(tp2.transferDim.sicnt0 * CIBLENGTH2);
    tp2.transferDim.sdim3 = 0;
    tp2.transferDim.ddim1 = (int16_t)(tensorWidth * sbHeight);
    tp2.transferDim.ddim2 = (int16_t)inProcSize;
    tp2.transferDim.ddim3 = (int16_t)(2 * inProcSize);
    tp2.cmpProp.cmpAlg = algorithm;
    tp2.cmpProp.cmpBias = bias;
    tp2.cmpProp.sbIcnt0 = (uint8_t)(sbWidth / 16);
    tp2.cmpProp.sbIcnt1 = (uint8_t)sbHeight;
    tp2.cmpProp.sbDim1  = (uint16_t)tensorWidth;
    tp2.cmpProp.sbAM0   = 0;
    tp2.cmpProp.sbAM1   = 0;
    tp2.cmpProp.sDim0   = (int16_t)CIBLENGTH2;
    tp2.cmpProp.dDim0   = (int16_t)sbWidth;
    tp2.ioPointers.srcPtr = compressed;
    tp2.ioPointers.dstPtr = output;
    tp2.ioPointers.strPtr = sectr;
    tp2.ioPointers.cdbPtr = sectr + 32;

    retVal = DmaUtilsAutoInc3d_prepareTr(&trPrepParam, &tp2);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "prepareTr (decomp simple) failed");
    retVal = DmaUtilsAutoInc3d_configure(ctxMem, 0, &TestUdma_DruTrMem[0], 1);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "configure (decomp simple) failed");

    triggers2 = (((uint32_t)tp2.transferDim.sicnt2 * (uint32_t)tp2.transferDim.sicnt3) <
                        ((uint32_t)tp2.transferDim.dicnt2 * (uint32_t)tp2.transferDim.dicnt3)) ?
                        ((uint32_t)tp2.transferDim.sicnt2 * (uint32_t)tp2.transferDim.sicnt3) :
                        ((uint32_t)tp2.transferDim.dicnt2 * (uint32_t)tp2.transferDim.dicnt3);
    for (u = 0U; u < triggers2; u++)
    {
        DmaUtilsAutoInc3d_trigger(ctxMem, 0);
        DmaUtilsAutoInc3d_wait(ctxMem, 0);
    }

    retVal = DmaUtilsAutoInc3d_deconfigure(ctxMem, 0, &TestUdma_DruTrMem[0], 1);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "deconfigure (decomp simple) failed");
    /* Validate */
    CacheP_inv(output, tensorWidth * tensorHeight, CacheP_TYPE_ALLD);
    CacheP_inv(input, tensorWidth * tensorHeight, CacheP_TYPE_ALLD);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, TestUdma_appUdmaCompareBuf(input, output, tensorWidth * tensorHeight), "Compression roundtrip mismatch (simple)");
    /* Cleanup */
    retVal = DmaUtilsAutoInc3d_deinit(ctxMem);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
    retVal = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
}

/**
 * \brief DRU Direct Circular DMAUTILS test.
 *
 * Test Category: Functional
 *
 * Validates DRU direct transfer using DMAUTILS with circular addressing.
 * Configures destination as a circular buffer, transfers blocks, and
 * reconstructs output.
 * Verifies that output matches the expected wrapped sequence.
 * \param None.
 * \return None.
 * \expectedOutput DMA transfer completes successfully; destination buffer
 * matches source.
 */
void TestUdma_dmautilsDruDirectCircular(void)
{
    uint8_t *srcBuf  = TestUdma_SrcBuf;
    uint8_t *dstBuf  = TestUdma_DestBuf;
    uint8_t *ctxMem  = TestUdma_DruCtxMem;
    uint8_t *circMem = TestUdma_L2Scratch;
    Udma_DrvObject drvObj;
    Udma_DrvHandle drvHndl = &drvObj;
    Udma_InitPrms initPrms;
    uint32_t i, j, r;
    DmaUtilsAutoInc3d_InitParam dmaInit;
    DmaUtilsAutoInc3d_ChannelInitParam chInit[2];
    DmaUtilsAutoInc3d_TransferProp tpIn;
    DmaUtilsAutoInc3d_TransferProp tpOut;
    DmaUtilsAutoInc3d_TrPrepareParam trPrepIn;
    DmaUtilsAutoInc3d_TrPrepareParam trPrepOut;
    uint32_t pingPongFlag = 0U;
    uint32_t blockIdx = 0U;
    uint32_t firstTrigger = 0U;
    uint32_t circPitch;
    uint32_t circSizeBytes;
    uint8_t *circBuf;
    uint8_t *outBlock;
    uint32_t linearOffset, blockOffset;
    uintptr_t base, circBaseAligned, outBaseCandidate;
    uintptr_t outBaseAligned, scratchStart, scratchEnd;
    /* Test parameters */
    const uint32_t width  = 128;
    const uint32_t height = 8;
    const uint32_t blockW = 64;
    const uint32_t blockH = 8;
    const uint32_t numBlocks = width / blockW;
    /* Circular pitch must be power-of-two and >= 512 for DRU */
    circPitch = (blockW * 2U < 512U) ? 512U : (blockW * 2U);
    while ((circPitch & (circPitch - 1U)) != 0U)
    {
        circPitch += 1U;
    }
    /* Align internal circular buffers to circPitch boundary */
    circSizeBytes = circPitch * blockH;
    base = (uintptr_t)circMem;
    circBaseAligned = (base + (uintptr_t)(circPitch - 1U)) & ~(uintptr_t)(circPitch - 1U);
    circBuf = (uint8_t *)circBaseAligned;
    /* Place OUT block right after IN block, and align it too */
    outBaseCandidate = (uintptr_t)circBuf + (uintptr_t)circSizeBytes;
    outBaseAligned = (outBaseCandidate + (uintptr_t)(circPitch - 1U)) & ~(uintptr_t)(circPitch - 1U);
    outBlock = (uint8_t *)outBaseAligned;
    /* Basic bounds check within L2 scratch */
    scratchStart = (uintptr_t)TestUdma_L2Scratch;
    scratchEnd   = scratchStart + (uintptr_t)sizeof(TestUdma_L2Scratch);
    TEST_ASSERT_TRUE_MESSAGE(((outBaseAligned + (uintptr_t)circSizeBytes) <= scratchEnd), "L2 scratch overflow for circular buffers");
    memset(circBuf, 0, circSizeBytes);
    memset(outBlock, 0, circSizeBytes);
    CacheP_wb(circBuf, circSizeBytes, CacheP_TYPE_ALLD);
    CacheP_wb(outBlock, circSizeBytes, CacheP_TYPE_ALLD);
    /* Circular pointer tracking */
    linearOffset = 0U;
    blockOffset  = 0U;
    /* Fill input */
    for (j = 0; j < height; j++)
    {
        for (i = 0; i < width; i++)
        {
            srcBuf[j * width + i] = (uint8_t)(i + j);
        }
    }

    memset(dstBuf, 0, width * height);
    CacheP_wb(srcBuf, width * height, CacheP_TYPE_ALLD);
    CacheP_wb(dstBuf, width * height, CacheP_TYPE_ALLD);
    /* UDMA Init */
    UdmaInitPrms_init(UDMA_INST_ID_0, &initPrms);
    initPrms.enableUtc = UTRUE;
    TEST_ASSERT_EQUAL(UDMA_SOK, Udma_init(drvHndl, &initPrms));
    /* DMAUTILS Init */
    dmaInit.contextSize = DmaUtilsAutoInc3d_getContextSize(2);
    dmaInit.numChannels = 2;
    dmaInit.traceLogLevel = 0;
    dmaInit.udmaDrvHandle = drvHndl;
    dmaInit.DmaUtilsVprintf = vprintf;
    chInit[0].dmaQueNo = 0;
    chInit[0].druOwner = DMAUTILSAUTOINC3D_DRUOWNER_DIRECT_TR;
    chInit[1].dmaQueNo = 0;
    chInit[1].druOwner = DMAUTILSAUTOINC3D_DRUOWNER_DIRECT_TR;
    TEST_ASSERT_EQUAL(UDMA_SOK,
                      DmaUtilsAutoInc3d_init(ctxMem, &dmaInit, chInit));
    /* Transfer Properties: prepare IN and OUT transfer props */
    memset(&tpIn, 0, sizeof(tpIn));
    memset(&tpOut, 0, sizeof(tpOut));
    tpIn.syncType = DMAUTILSAUTOINC3D_SYNC_2D;
    tpIn.ioPointers.srcPtr  = srcBuf;
    tpIn.ioPointers.dstPtr  = circBuf;
    tpIn.circProp.circDir   = DMAUTILSAUTOINC3D_CIRCDIR_DST;
    tpIn.circProp.circSize1 = circPitch;
    tpIn.circProp.circSize2 = 0;
    tpIn.circProp.addrModeIcnt0 = DMAUTILSAUTOINC3D_ADDR_CIRC1;
    tpIn.circProp.addrModeIcnt1 = DMAUTILSAUTOINC3D_ADDR_LINEAR;
    tpIn.circProp.addrModeIcnt2 = DMAUTILSAUTOINC3D_ADDR_CIRC1;
    tpIn.circProp.addrModeIcnt3 = DMAUTILSAUTOINC3D_ADDR_LINEAR;
    tpIn.transferDim.sicnt0 = blockW;
    tpIn.transferDim.sicnt1 = blockH;
    tpIn.transferDim.sicnt2 = numBlocks;
    tpIn.transferDim.sicnt3 = 1;
    tpIn.transferDim.sdim1  = width;
    tpIn.transferDim.sdim2  = blockW;
    tpIn.transferDim.sdim3  = blockH * width;
    tpIn.transferDim.dicnt0 = blockW;
    tpIn.transferDim.dicnt1 = blockH;
    tpIn.transferDim.dicnt2 = numBlocks;
    tpIn.transferDim.dicnt3 = 1;
    tpIn.transferDim.ddim1  = circPitch;
    tpIn.transferDim.ddim2  = blockW;
    tpIn.transferDim.ddim3  = 0;
    /* OUT transfer: read from circular buffer and write to linear dstBuf */
    tpOut = tpIn;
    tpOut.circProp.circDir = DMAUTILSAUTOINC3D_CIRCDIR_SRC;
    tpOut.ioPointers.srcPtr = outBlock;
    tpOut.ioPointers.dstPtr = dstBuf;
    /* Adjust OUT addressing: source uses circular pitch, destination uses
     * linear width */
    tpOut.transferDim.sdim1 = (int16_t)circPitch;
    tpOut.transferDim.sdim2 = blockW;
    tpOut.transferDim.sdim3 = 0;
    tpOut.transferDim.ddim1 = width;
    tpOut.transferDim.ddim2 = blockW;
    tpOut.transferDim.ddim3 = blockH * width;
    /* Prepare TRs for IN (channel 0) and OUT (channel 1) */
    trPrepIn.channelId = 0;
    trPrepIn.numTRs = 1;
    trPrepIn.trMem = &TestUdma_DruTrMem[0];
    trPrepIn.trMemSize = DmaUtilsAutoInc3d_getTrMemReq(1);
    trPrepOut.channelId = 1;
    trPrepOut.numTRs = 1;
    trPrepOut.trMem = &TestUdma_DruTrMem2[0];
    trPrepOut.trMemSize = DmaUtilsAutoInc3d_getTrMemReq(1);

    TEST_ASSERT_EQUAL(UDMA_SOK, DmaUtilsAutoInc3d_prepareTr(&trPrepIn, &tpIn));
    TEST_ASSERT_EQUAL(UDMA_SOK, DmaUtilsAutoInc3d_prepareTr(&trPrepOut, &tpOut));
    TEST_ASSERT_EQUAL(UDMA_SOK, DmaUtilsAutoInc3d_configure(ctxMem, 0, trPrepIn.trMem, 1));
    TEST_ASSERT_EQUAL(UDMA_SOK, DmaUtilsAutoInc3d_configure(ctxMem, 1, trPrepOut.trMem, 1));
    /* Follow example: initial IN trigger to pipe-up */
    DmaUtilsAutoInc3d_trigger(ctxMem, 0);
    DmaUtilsAutoInc3d_wait(ctxMem, 0);

    while (1)
    {
        pingPongFlag ^= 1U;

        if (firstTrigger != 0U)
        {
            blockIdx = (uint32_t)DmaUtilsAutoInc3d_trigger(ctxMem, 1);
        }

        if (blockIdx != 1U)
        {
            DmaUtilsAutoInc3d_trigger(ctxMem, 0);
        }

        /* copy current block from circBuf to outBlock */
        for (r = 0U; r < blockH; r++)
        {
            /* Invalidate the DMA-written row in circBuf before CPU read */
            CacheP_inv(circBuf + blockOffset + r * circPitch, blockW, CacheP_TYPE_ALLD);
            memcpy(outBlock + blockOffset + r * circPitch,
                   circBuf + blockOffset + r * circPitch,
                   blockW);
            /* Writeback the CPU-written row in outBlock */
            CacheP_wb(outBlock + blockOffset + r * circPitch, blockW, CacheP_TYPE_ALLD);
        }
        CacheP_wbInvAll(CacheP_TYPE_ALLD);

        /* Advance circular offset */
        linearOffset += blockW;
        blockOffset   = (linearOffset & (circPitch - 1U));

        if (blockIdx != 1U)
        {
            /* Wait for IN completion of the next block after copy */
            DmaUtilsAutoInc3d_wait(ctxMem, 0);
        }

        if (firstTrigger != 0U)
        {
            /* Wait for previous OUT */
            DmaUtilsAutoInc3d_wait(ctxMem, 1);
        }
        else
        {
            firstTrigger = 1U;
        }

        if (blockIdx == 1U)
        {
            break;
        }
    }
    /* Trigger last OUT and wait */
    DmaUtilsAutoInc3d_trigger(ctxMem, 1);
    DmaUtilsAutoInc3d_wait(ctxMem, 1);
    /* Verify data */
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, TestUdma_appUdmaCompareBuf(srcBuf, dstBuf, width * height), "dmautils circular compare failed");
    /* Cleanup: deconfigure both IN and OUT channels then deinit */
    TEST_ASSERT_EQUAL(UDMA_SOK,
                      DmaUtilsAutoInc3d_deconfigure(ctxMem, 0, trPrepIn.trMem, 1));
    TEST_ASSERT_EQUAL(UDMA_SOK,
                      DmaUtilsAutoInc3d_deconfigure(ctxMem, 1, trPrepOut.trMem, 1));
    TEST_ASSERT_EQUAL(UDMA_SOK,
                      DmaUtilsAutoInc3d_deinit(ctxMem));
    TEST_ASSERT_EQUAL(UDMA_SOK,
                      Udma_deinit(drvHndl));
}

/**
 * \brief DRU direct Channel Pause/Resume test.
 *
 * Test Category: Functional
 *
 * Validates DRU direct TR channel pause and resume functionality.
 * Opens a UTC channel, enables it, tests pause/resume operations,
 * and verifies that the channel state can be controlled without errors.
 * \param args Pointer to test arguments (unused).
 * \return None.
 * \expectedOutput Pause and resume operations complete successfully
 * without errors.
 */
void TestUdma_dmautilsDruDirectPauseResume(void *args)
{
    uint8_t *srcBuf = &TestUdma_SrcBuf[0U];
    uint8_t *dstBuf = &TestUdma_DestBuf[0U];
    uint8_t *ctxMem = &TestUdma_DruCtxMem[0U];
    uint8_t *trMem  = &TestUdma_DruTrMem[0U];
    Udma_DrvObject udmaDrvObj;
    Udma_DrvHandle drvHandle = &udmaDrvObj;
    Udma_InitPrms initPrms;
    int32_t retVal;
    int changedWhilePaused = 0;
    uint32_t i;
    DmaUtilsAutoInc3d_InitParam initParams;
    DmaUtilsAutoInc3d_ChannelInitParam chInitParams[1];
    DmaUtilsAutoInc3d_TrPrepareParam trPrep;
    DmaUtilsAutoInc3d_TransferProp tp;
    DmaUtilsAutoInc3d_Context *autoCtx;
    DmaUtilsAutoInc3d_ChannelContext *chanCtx;
    Udma_ChHandle pauseCh;

    TestUdma_appUdmaInitBuf(srcBuf, dstBuf, TEST_DMAUTILS_TC_LEN);
    UdmaInitPrms_init(UDMA_INST_ID_0, &initPrms);
    initPrms.instId = UDMA_INST_ID_0;
    initPrms.enableUtc = UTRUE;
    retVal = Udma_init(drvHandle, &initPrms);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "Udma_init failed (dmautils)");

    initParams.contextSize = DmaUtilsAutoInc3d_getContextSize(1);
    initParams.numChannels = 1;
    initParams.traceLogLevel = 0;
    initParams.udmaDrvHandle = drvHandle;
    initParams.DmaUtilsVprintf = vprintf;
    chInitParams[0].dmaQueNo = 0;
    chInitParams[0].druOwner = DMAUTILSAUTOINC3D_DRUOWNER_DIRECT_TR;
    retVal = DmaUtilsAutoInc3d_init(ctxMem, &initParams, chInitParams);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "dmautils init failed");
    memset(&tp, 0, sizeof(tp));
    tp.transferDim.sicnt0 = TEST_DMAUTILS_TC_LEN;
    tp.transferDim.sicnt1 = 1;
    tp.transferDim.sicnt2 = 1;
    tp.transferDim.sicnt3 = 1;
    tp.transferDim.sdim1 = TEST_DMAUTILS_TC_LEN;
    tp.transferDim.sdim2 = TEST_DMAUTILS_TC_LEN;
    tp.transferDim.sdim3 = TEST_DMAUTILS_TC_LEN;
    tp.transferDim.dicnt0 = TEST_DMAUTILS_TC_LEN;
    tp.transferDim.dicnt1 = 1;
    tp.transferDim.dicnt2 = 1;
    tp.transferDim.dicnt3 = 1;
    tp.transferDim.ddim1 = TEST_DMAUTILS_TC_LEN;
    tp.transferDim.ddim2 = TEST_DMAUTILS_TC_LEN;
    tp.transferDim.ddim3 = TEST_DMAUTILS_TC_LEN;
    tp.ioPointers.srcPtr = srcBuf;
    tp.ioPointers.dstPtr = dstBuf;
    tp.syncType = DMAUTILSAUTOINC3D_SYNC_1D;
    trPrep.channelId = 0;
    trPrep.numTRs = 1;
    trPrep.trMem = trMem;
    trPrep.trMemSize = DmaUtilsAutoInc3d_getTrMemReq(1);
    retVal = DmaUtilsAutoInc3d_prepareTr(&trPrep, &tp);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "prepareTr failed");
    retVal = DmaUtilsAutoInc3d_configure(ctxMem, 0, trMem, 1);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "configure failed");
    /* Pause underlying UTC channel via dmautils context */
    autoCtx = (DmaUtilsAutoInc3d_Context *)ctxMem;
    chanCtx = autoCtx->channelContext[0];
    TEST_ASSERT_NOT_NULL_MESSAGE(chanCtx, "Channel context null");
    pauseCh = (Udma_ChHandle)&chanCtx->chHandle;
    retVal = Udma_chPause(pauseCh);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "UTC channel pause failed");
    /* Short sleep to allow pause to take effect */
    ClockP_usleep(2000);
    /* Try triggering while paused: ensure no data change occurs */
    DmaUtilsAutoInc3d_trigger(ctxMem, 0);
    ClockP_usleep(2000);
    CacheP_inv(dstBuf, TEST_DMAUTILS_TC_LEN, CacheP_TYPE_ALLD);

    for (i = 0; i < TEST_DMAUTILS_TC_LEN; i++)
    {
        if (dstBuf[i] != TEST_UDMA_POISON_PATTERN_BYTE)
        {
            changedWhilePaused = 1;
            break;
        }
    }
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, changedWhilePaused, "Data changed while channel paused");
    /* Resume and trigger to complete */
    retVal = Udma_chResume(pauseCh);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "UTC channel resume failed");
    /* Wait for completion */
    DmaUtilsAutoInc3d_wait(ctxMem, 0);
    /* Verify data */
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, TestUdma_appUdmaCompareBuf(srcBuf, dstBuf, TEST_DMAUTILS_TC_LEN), "dmautils pause/resume compare failed");
    /* Cleanup */
    retVal = DmaUtilsAutoInc3d_deconfigure(ctxMem, 0, trMem, 1);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "deconfigure failed");
    retVal = DmaUtilsAutoInc3d_deinit(ctxMem);
    TEST_ASSERT_EQUAL_INT_MESSAGE(UDMA_SOK, retVal, "deinit failed");
    retVal = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT(UDMA_SOK, retVal);
}




