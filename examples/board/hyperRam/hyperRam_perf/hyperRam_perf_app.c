/*
 *  Copyright (C) 2025 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include <inttypes.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/CacheP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <drivers/pinmux.h>
#include <drivers/hyperbus.h>
#include "ti_board_open_close.h"
#include "ti_drivers_open_close.h"
#include "ti_drivers_config.h"
#include <drivers/soc.h>
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define APP_HYPERRAM_TEST_SIZE               (100U*1024U)
#define APP_HYPERRAM_OFFSET                  (200U*1024U)
#define APP_HYPERRAM_OFFSET_FOR_ECC_TEST     (100U*1024U)
/* offsset + size shoud be less than 64MB */

/* UDMA TR packet descriptor memory size - with one TR */
#define UDMA_TEST_HYPERRAM_TRPD_SIZE             (UDMA_GET_TRPD_TR15_SIZE(1U))

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void hyperRam_fill_buffers(void);
void hyperRam_write(uint32_t baseAddress, uint32_t offset, uint8_t *Buffer, int32_t size);
void hyperRam_read(uint32_t baseAddress, uint32_t offset, uint8_t *Buffer, int32_t size);
int32_t hyperRam_cpu_mecmcpy(uint32_t baseAddress, uint32_t offset, uint32_t size);
int32_t hyperRam_bcdma_mecmcpy(uint32_t baseAddress, uint32_t offset, uint32_t size);
uint64_t hyperRam_udma_memcpy_interrupt_transfer(uint8_t *srcBuf, uint8_t *destBuf, uint32_t length);
void hyperRam_app_udmaEventCb(Udma_EventHandle eventHandle, uint32_t eventType, void *appData);
void hyperRam_app_udmaTrpdInit(Udma_ChHandle chHandle,
                             uint8_t *trpdMem,
                             const void *destBuf,
                             const void *srcBuf,
                             uint32_t length);
void hyperRam_app_udmaInitBuf(uint8_t *srcBuf, uint8_t *destBuf, uint32_t length);
void hyperRam_app_udmaCompareBuf(uint8_t *srcBuf, uint8_t *destBuf, uint32_t length);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Allocate as uint32_t so that write pattern can be more than 256 so that we
 * can avoid any wrap around mistakes */
uint8_t gReadBuffer[APP_HYPERRAM_TEST_SIZE]__attribute__ ((section (".globalScratchBuffer"), aligned (128U)));
uint8_t gWriteBuffer[APP_HYPERRAM_TEST_SIZE]__attribute__ ((section (".globalScratchBuffer"), aligned (128U)));

/* UDMA TRPD Memory */
uint8_t gUdmaTestTrpdMem[UDMA_TEST_HYPERRAM_TRPD_SIZE] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));

/* Application Buffers */
uint8_t gUdmaTestSrcBuf[UDMA_ALIGN_SIZE(APP_HYPERRAM_TEST_SIZE)] __attribute__((section (".globalScratchBuffer"), aligned(UDMA_CACHELINE_ALIGNMENT)));
uint8_t gUdmaTestDestBuf[UDMA_ALIGN_SIZE(APP_HYPERRAM_TEST_SIZE)] __attribute__((section (".globalScratchBuffer"), aligned(UDMA_CACHELINE_ALIGNMENT)));

/* Semaphore to indicate transfer completion */
static SemaphoreP_Object gUdmaTestDoneSem;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*
 * The example writes known data to a particular offset in the HyperRam and
 * then reads it back. The read back data is then compared with the written known data.
 * This is done using both cpu and bcdma transfer modes.
 *
 */

/*
 * For BCDMA mode, the example performs UDMA block copy transfer using Type 15 Transfer Record (TR15)
 * using Transfer Record Packet Descriptor (TRPD) in interrupt mode.
 *
 * The application opens and configures a BCDMA channel using SysConfig.
 * It also configures the interrupt mode of operation through the SysConfig
 * which ensures that all required interrupt configuration are done.
 * The callback function hyperRam_app_udmaEventCb is registered via SysConfig.
 *
 * Then the application prepares a TRPD for a 1D/2D transfer from source to
 * destination buffer, submits the request to DMA, waits for the DMA to complete
 * by waiting on a semaphore which is posted in the callback function.
 *
 * Once the transfer it completes, it does cache operation for data coherency
 * and compares the source and destination buffers for any data mismatch.
 *
 */

void hyperRam_perf_app_main(void)
{
    HYPERRAM_Handle   hyperRamHandle = gHyperRamHandle[CONFIG_HYPERRAM0];
    HYPERBUS_Handle hyperbusHandle = NULL;
    HyperRam_Config *config = (HyperRam_Config *)hyperRamHandle;
    HyperRam_Attrs *attrs = config->attrs;
    uint32_t baseAddress = 0U;
    int32_t status = SystemP_SUCCESS;

    hyperbusHandle = HYPERBUS_getHandle(attrs->driverInstance);
    baseAddress = HYPERBUS_getHyperBusDataBaseAddr(hyperbusHandle);

    DebugP_log("================================================================\r\n");
    DebugP_log("HyperRam read write test started with ECC!!\r\n");

    status |= hyperRam_cpu_mecmcpy(baseAddress, APP_HYPERRAM_OFFSET_FOR_ECC_TEST, APP_HYPERRAM_TEST_SIZE);

    status |= hyperRam_bcdma_mecmcpy(baseAddress, APP_HYPERRAM_OFFSET_FOR_ECC_TEST, APP_HYPERRAM_TEST_SIZE);

    DebugP_log("================================================================\r\n");
    DebugP_log("                                                                \r\n");
    DebugP_log("HyperRam read write test started without ECC!!\r\n");

    HYPERBUS_enableECC(hyperbusHandle, 0U);
    status |= hyperRam_cpu_mecmcpy(baseAddress, APP_HYPERRAM_OFFSET, APP_HYPERRAM_TEST_SIZE);

    status |= hyperRam_bcdma_mecmcpy(baseAddress, APP_HYPERRAM_OFFSET, APP_HYPERRAM_TEST_SIZE);

    DebugP_log("================================================================\r\n");

    if( status != SystemP_SUCCESS )
    {
        DebugP_log("Some tests have failed!!\r\n");
    }
    else
    {
        DebugP_log("All tests have passed!!\r\n");
    }

    return;
}

void hyperRam_app_udmaEventCb(Udma_EventHandle eventHandle, uint32_t eventType, void *appData)
{
    if(UDMA_EVENT_TYPE_DMA_COMPLETION == eventType)
    {
        SemaphoreP_post(&gUdmaTestDoneSem);
    }
}

void hyperRam_app_udmaTrpdInit(Udma_ChHandle chHandle,
                             uint8_t *trpdMem,
                             const void *destBuf,
                             const void *srcBuf,
                             uint32_t length)
{
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
    pTr->icnt0    = length/2;
    pTr->icnt1    = 2U;
    pTr->icnt2    = 1U;
    pTr->icnt3    = 1U;
    pTr->dim1     = pTr->icnt0;
    pTr->dim2     = (pTr->icnt0 * pTr->icnt1);
    pTr->dim3     = (pTr->icnt0 * pTr->icnt1 * pTr->icnt2);
    pTr->addr     = (uint64_t) Udma_defaultVirtToPhyFxn(srcBuf, 0U, NULL);
    pTr->fmtflags = 0x00000000U;    /* Linear addressing, 1 byte per elem */
    pTr->dicnt0   = length/2;
    pTr->dicnt1   = 2U;
    pTr->dicnt2   = 1U;
    pTr->dicnt3   = 1U;
    pTr->ddim1    = pTr->dicnt0;
    pTr->ddim2    = (pTr->dicnt0 * pTr->dicnt1);
    pTr->ddim3    = (pTr->dicnt0 * pTr->dicnt1 * pTr->dicnt2);
    pTr->daddr    = (uint64_t) Udma_defaultVirtToPhyFxn(destBuf, 0U, NULL);

    /* Perform cache writeback */
    CacheP_wb(trpdMem, UDMA_TEST_HYPERRAM_TRPD_SIZE, CacheP_TYPE_ALLD);

    return;
}

void hyperRam_app_udmaInitBuf(uint8_t *srcBuf, uint8_t *destBuf, uint32_t length)
{
    uint32_t        i;

    for(i = 0U; i < length; i++)
    {
        srcBuf[i] = i;
        destBuf[i] = 0xA5U;
    }
    /* Writeback source and destination buffer */
    CacheP_wb(srcBuf, length, CacheP_TYPE_ALLD);
    CacheP_wb(destBuf, length, CacheP_TYPE_ALLD);

    return;
}

void hyperRam_app_udmaCompareBuf(uint8_t *srcBuf, uint8_t *destBuf, uint32_t length)
{
    uint32_t        i;

    /* Invalidate destination buffer */
    CacheP_inv(destBuf, length, CacheP_TYPE_ALLD);
    for(i = 0U; i < length; i++)
    {
        if(srcBuf[i] != destBuf[i])
        {
            DebugP_logError("Data mismatch !!!\r\n");
            DebugP_assert(FALSE);
        }
    }

    return;
}

uint64_t hyperRam_udma_memcpy_interrupt_transfer(uint8_t *srcBuf, uint8_t *destBuf, uint32_t length)
{
    int32_t         retVal = UDMA_SOK, status;
    Udma_ChHandle   chHandle;
    uint64_t        pDesc;
    uint32_t        trRespStatus;
    uint8_t        *trpdMem = &gUdmaTestTrpdMem[0U];
    uint64_t        trpdMemPhy = (uint64_t) Udma_defaultVirtToPhyFxn(trpdMem, 0U, NULL);
    uint64_t        curTime = 0U;

    chHandle = gConfigUdma0BlkCopyChHandle[0];  /* Has to be done after driver open */

    status = SemaphoreP_constructBinary(&gUdmaTestDoneSem, 0);
    DebugP_assert(SystemP_SUCCESS == status);

    /* Channel enable */
    retVal = Udma_chEnable(chHandle);
    DebugP_assert(UDMA_SOK == retVal);

    /* Init buffers and TR packet descriptor */
    hyperRam_app_udmaInitBuf(srcBuf, destBuf, length);
    hyperRam_app_udmaTrpdInit(chHandle, trpdMem, destBuf, srcBuf, length);

    curTime = ClockP_getTimeUsec();

    /* Submit TRPD to channel */
    retVal = Udma_ringQueueRaw(Udma_chGetFqRingHandle(chHandle), trpdMemPhy);
    DebugP_assert(UDMA_SOK == retVal);

    /* Wait for return descriptor in completion ring - this marks transfer completion */
    SemaphoreP_pend(&gUdmaTestDoneSem, SystemP_WAIT_FOREVER);
    curTime = ClockP_getTimeUsec() - curTime;

    retVal = Udma_ringDequeueRaw(Udma_chGetCqRingHandle(chHandle), &pDesc);
    DebugP_assert(UDMA_SOK == retVal);

    /* Check TR response status */
    CacheP_inv(trpdMem, UDMA_TEST_HYPERRAM_TRPD_SIZE, CacheP_TYPE_ALLD);
    trRespStatus = UdmaUtils_getTrpdTr15Response(trpdMem, 1U, 0U);
    DebugP_assert(CSL_UDMAP_TR_RESPONSE_STATUS_COMPLETE == trRespStatus);

    /* Compare data */
    hyperRam_app_udmaCompareBuf(srcBuf, destBuf, length);

    /* Channel disable */
    retVal = Udma_chDisable(chHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
    DebugP_assert(UDMA_SOK == retVal);

    SemaphoreP_destruct(&gUdmaTestDoneSem);

    return curTime;
}

int32_t hyperRam_bcdma_mecmcpy(uint32_t baseAddress, uint32_t offset, uint32_t size)
{
    uint8_t        *srcBuf = &gUdmaTestSrcBuf[0U];
    uint8_t        *destBuf = (uint8_t *)(baseAddress + offset);
    uint64_t        curTime = 0U;
    int32_t         status = SystemP_SUCCESS;

    DebugP_log("================================================================\r\n");
    DebugP_log("Writing to the hyperRam Started with BCDMA...\r\n");

    Drivers_udmaClose();
    Drivers_udmaOpen();

    curTime = hyperRam_udma_memcpy_interrupt_transfer(srcBuf, destBuf, size);

    DebugP_log("DMA : Achieved Write throughput is %.2f MB/s\r\n",\
        (float)(((float)(size)/(float)(curTime))*((float)(1000U * 1000U)/(float)(1024U * 1024U))));

    Drivers_udmaClose();
    Drivers_udmaOpen();

    srcBuf = (uint8_t *)(baseAddress + offset);
    destBuf = &gUdmaTestDestBuf[0U];
    DebugP_log("Reading from the hyperRam Started with BCDMA...\r\n");

    curTime = hyperRam_udma_memcpy_interrupt_transfer(srcBuf, destBuf, size);

    if(SystemP_SUCCESS == status)
    {
        DebugP_log("DMA : Achieved Read throughput is %.2f MB/s\r\n",\
            (float)(((float)(size)/(float)(curTime))*((float)(1000U * 1000U)/(float)(1024U * 1024U))));
    }
    else
    {
        DebugP_log("Reading  the hyperRam is FAILED ... data mismatch\r\n");
    }

    return status;
}

int32_t hyperRam_cpu_mecmcpy(uint32_t baseAddress, uint32_t offset, uint32_t size)
{
    int32_t status = SystemP_SUCCESS;
    uint64_t curTime = 0U;

    /* Fill the buffer with data */
    hyperRam_fill_buffers();

    DebugP_log("================================================================\r\n");
    DebugP_log("Writing to the hyperRam Started with CPU...\r\n");

    curTime = ClockP_getTimeUsec();
    hyperRam_write(baseAddress, offset, gWriteBuffer, size);
    curTime = ClockP_getTimeUsec() - curTime;

    if(SystemP_SUCCESS == status)
    {
        DebugP_log("CPU : Achieved Write throughput is %.2f MB/s\r\n",\
            (float)(((float)(APP_HYPERRAM_TEST_SIZE)/(float)(curTime))*((float)(1000U * 1000U)/(float)(1024U * 1024U))));
    }
    else
    {
        DebugP_log("Writing to the hyperRam is FAILED...\r\n");
    }

    DebugP_log("Reading from the hyperRam Started with CPU...\r\n");

    curTime = ClockP_getTimeUsec();
    hyperRam_read(baseAddress, offset, gReadBuffer, size);
    curTime = ClockP_getTimeUsec() - curTime;

    status = memcmp(gReadBuffer, gWriteBuffer, size);

    if(SystemP_SUCCESS == status)
    {
        DebugP_log("CPU : Achieved Read throughput is %.2f MB/s\r\n",\
            (float)(((float)(APP_HYPERRAM_TEST_SIZE)/(float)(curTime))*((float)(1000U * 1000U)/(float)(1024U * 1024U))));
    }
    else
    {
        DebugP_log("Reading  the hyperRam is FAILED ... data mismatch\r\n");
    }

    return status;
}

void hyperRam_read(uint32_t baseAddress, uint32_t offset, uint8_t *Buffer, int32_t size)
{
    memcpy(Buffer, (uint32_t *)(baseAddress + offset), size);
}

void hyperRam_write(uint32_t baseAddress, uint32_t offset, uint8_t *Buffer, int32_t size)
{
    memcpy((uint32_t *)(baseAddress + offset), Buffer, size);
}

void hyperRam_fill_buffers(void)
{
    uint32_t i;
    for(i = 0U; i < APP_HYPERRAM_TEST_SIZE; i++)
    {
        gWriteBuffer[i] = i % 13U;
        gReadBuffer[i] = 0U;
    }
}
