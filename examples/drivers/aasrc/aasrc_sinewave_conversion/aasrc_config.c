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

/* Use this file to edit the AASRC Params */

#include <math.h>
#include <kernel/dpl/DebugP.h>
#include <drivers/soc.h>
#include <drivers/aasrc.h>
#include <drivers/sciclient.h>
#include "aasrc_config.h"
#include <drivers/udma.h>

/*
 * UDMA
 */

/* UDMA Instance Macros */
#define CONFIG_UDMA0 (0U)
#define CONFIG_UDMA_NUM_INSTANCES (1U)

/* UDMA driver instance object */
Udma_DrvObject          gUdmaDrvObj[CONFIG_UDMA_NUM_INSTANCES];

/* UDMA driver instance init params */
#if defined(__C7504__) || defined(__C7524__)
static Udma_InitPrms    gUdmaInitPrms[CONFIG_UDMA_NUM_INSTANCES] =
{
    {
        .instId             = UDMA_INST_ID_BCDMA_0,
        .skipGlobalEventReg = FALSE,
        .virtToPhyFxn       = Udma_defaultVirtToPhyFxnC7x,
        .phyToVirtFxn       = Udma_defaultPhyToVirtFxnC7x,
    },
};
#else
static Udma_InitPrms    gUdmaInitPrms[CONFIG_UDMA_NUM_INSTANCES] =
{
    {
        .instId             = UDMA_INST_ID_BCDMA_0,
        .skipGlobalEventReg = FALSE,
        .virtToPhyFxn       = Udma_defaultVirtToPhyFxn,
        .phyToVirtFxn       = Udma_defaultPhyToVirtFxn,
    },
};
#endif


Udma_EventObject gBcdmaTxCqEventObj;
Udma_EventObject gBcdmaRxCqEventObj;

/* Number of ring entries */
#define UDMA_RING_ENTRIES_TX             (AASRC_TX_DMA_RING_ELEM_CNT)
#define UDMA_RING_ENTRIES_RX             (AASRC_RX_DMA_RING_ELEM_CNT)

/* Size (in bytes) of each ring entry (Size of pointer - 64-bit) */
#define AASRC_UDMA_RING_ENTRY_SIZE       (sizeof(uint64_t))

#define AASRC_RING_MEM_SIZE_TX           (AASRC_UDMA_RING_ENTRY_SIZE*UDMA_RING_ENTRIES_TX)
#define AASRC_RING_MEM_SIZE_RX           (AASRC_UDMA_RING_ENTRY_SIZE*UDMA_RING_ENTRIES_RX)

#define AASRC_UDMA_TR3_TRPD_SIZE_TX         (UDMA_GET_TRPD_TR3_SIZE(AASRC_TX_DMA_TR_COUNT))
#define AASRC_UDMA_TR3_TRPD_SIZE_RX         (UDMA_GET_TRPD_TR3_SIZE(AASRC_RX_DMA_TR_COUNT))

Udma_ChObject       gAasrc0UdmaTxChObj[CONFIG_AASRC0_NUM_CH];
Udma_EventObject    gAasrc0_UdmaCqEventObjTx[CONFIG_AASRC0_NUM_CH];

Udma_ChObject       gAasrc0UdmaRxChObj[CONFIG_AASRC0_NUM_CH];
Udma_EventObject    gAasrc0_UdmaCqEventObjRx[CONFIG_AASRC0_NUM_CH];

uint8_t gAasrc0UdmaTxTrpdMem[CONFIG_AASRC0_NUM_CH][AASRC_UDMA_TR3_TRPD_SIZE_TX*AASRC_TX_DMA_RING_ELEM_CNT] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));
uint8_t gAasrc0UdmaRxTrpdMem[CONFIG_AASRC0_NUM_CH][AASRC_UDMA_TR3_TRPD_SIZE_RX*AASRC_RX_DMA_RING_ELEM_CNT] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));

static uint8_t gAasrc0TxFqRingMem[CONFIG_AASRC0_NUM_CH][UDMA_ALIGN_SIZE(AASRC_RING_MEM_SIZE_TX)] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));
static uint8_t gAasrc0RxFqRingMem[CONFIG_AASRC0_NUM_CH][UDMA_ALIGN_SIZE(AASRC_RING_MEM_SIZE_RX)] __attribute__((aligned(UDMA_CACHELINE_ALIGNMENT)));

static AASRC_Transaction *gAasrc0TxCbParam[CONFIG_AASRC0_NUM_CH][AASRC_TX_DMA_TR_COUNT];
static AASRC_Transaction *gAasrc0RxCbParam[CONFIG_AASRC0_NUM_CH][AASRC_RX_DMA_TR_COUNT];

AASRC_DmaChCfg gAASRC0_DmaChCfg[CONFIG_AASRC0_NUM_CH] =
{
    {
        .txChHandle         = &gAasrc0UdmaTxChObj[0],
        .rxChHandle         = &gAasrc0UdmaRxChObj[0],
        .cqTxEvtHandle      = &gAasrc0_UdmaCqEventObjTx[0],
        .cqRxEvtHandle      = &gAasrc0_UdmaCqEventObjRx[0],
        .txTrpdMem          = &gAasrc0UdmaTxTrpdMem[0],
        .rxTrpdMem          = &gAasrc0UdmaRxTrpdMem[0],
        .txRingMem          = &gAasrc0TxFqRingMem[0],
        .rxRingMem          = &gAasrc0RxFqRingMem[0],
        .txCbParams         = &gAasrc0TxCbParam[0],
        .rxCbParams         = &gAasrc0RxCbParam[0],
        .rxEvtNum           = UDMA_PDMA_CH_MAIN0_AASRC0_CH0_RX,
        .txEvtNum           = UDMA_PDMA_CH_MAIN0_AASRC0_CH0_TX,
    },
    {
        .txChHandle         = &gAasrc0UdmaTxChObj[1],
        .rxChHandle         = &gAasrc0UdmaRxChObj[1],
        .cqTxEvtHandle      = &gAasrc0_UdmaCqEventObjTx[1],
        .cqRxEvtHandle      = &gAasrc0_UdmaCqEventObjRx[1],
        .txTrpdMem          = &gAasrc0UdmaTxTrpdMem[1],
        .rxTrpdMem          = &gAasrc0UdmaRxTrpdMem[1],
        .txRingMem          = &gAasrc0TxFqRingMem[1],
        .rxRingMem          = &gAasrc0RxFqRingMem[1],
        .txCbParams         = &gAasrc0TxCbParam[1],
        .rxCbParams         = &gAasrc0RxCbParam[1],
        .rxEvtNum           = UDMA_PDMA_CH_MAIN0_AASRC0_CH1_RX,
        .txEvtNum           = UDMA_PDMA_CH_MAIN0_AASRC0_CH1_TX,
    },
    {
        .txChHandle         = &gAasrc0UdmaTxChObj[2],
        .rxChHandle         = &gAasrc0UdmaRxChObj[2],
        .cqTxEvtHandle      = &gAasrc0_UdmaCqEventObjTx[2],
        .cqRxEvtHandle      = &gAasrc0_UdmaCqEventObjRx[2],
        .txTrpdMem          = &gAasrc0UdmaTxTrpdMem[2],
        .rxTrpdMem          = &gAasrc0UdmaRxTrpdMem[2],
        .txRingMem          = &gAasrc0TxFqRingMem[2],
        .rxRingMem          = &gAasrc0RxFqRingMem[2],
        .txCbParams         = &gAasrc0TxCbParam[2],
        .rxCbParams         = &gAasrc0RxCbParam[2],
        .rxEvtNum           = UDMA_PDMA_CH_MAIN0_AASRC0_CH2_RX,
        .txEvtNum           = UDMA_PDMA_CH_MAIN0_AASRC0_CH2_TX,
    },
};



/* Edit Params */

/* AASRC Driver Open Parameters */
AASRC_OpenParams gAasrcOpenParams[CONFIG_AASRC_NUM_INSTANCES] =
{
    /* Instance 0 */
    {
        .transferMode                           = AASRC_TRANSFER_MODE_DMA,
        .dmaDrvObj                              = &gUdmaDrvObj[CONFIG_UDMA0],

        .rxClkZoneCfg                           =
        {
            {
                .clkZoneDiv                     = 128U,
                .isClkZoneDivEnable             = 1U,
                .syncPin                        = 0U,
                .extClkSrc                      = AASRC_RXSYNC_MAIN_PLL4_HSDIV3_CLKOUT,
                .overrideClkSettle              = 0U,
            },
            {
                .clkZoneDiv                     = 64U,
                .isClkZoneDivEnable             = 1U,
                .syncPin                        = 1U,
                .extClkSrc                      = AASRC_RXSYNC_MAIN_PLL4_HSDIV3_CLKOUT,
                .overrideClkSettle              = 0U,
            },
            {
                .clkZoneDiv                     = 64U,
                .isClkZoneDivEnable             = 0U,
                .syncPin                        = 2U,
                .extClkSrc                      = AASRC_RXSYNC_MAIN_PLL4_HSDIV3_CLKOUT,
                .overrideClkSettle              = 0U,
            },
            {
                .clkZoneDiv                     = 64U,
                .isClkZoneDivEnable             = 0U,
                .syncPin                        = 3U,
                .extClkSrc                      = AASRC_RXSYNC_MAIN_PLL4_HSDIV3_CLKOUT,
                .overrideClkSettle              = 0U,
            },
        },

        .txClkZoneCfg                       =
        {
            {
                .clkZoneDiv                     = 256U,
                .isClkZoneDivEnable             = 1U,
                .syncPin                        = 0U,
                .extClkSrc                      = AASRC_TXSYNC_MAIN_PLL4_HSDIV3_CLKOUT,
                .overrideClkSettle              = 0U,
            },
            {
                .clkZoneDiv                     = 120U,
                .isClkZoneDivEnable             = 1U,
                .syncPin                        = 1U,
                .extClkSrc                      = AASRC_TXSYNC_ADC0_CLK,
                .overrideClkSettle              = 0U,
            },
            {
                .clkZoneDiv                     = 100U,
                .isClkZoneDivEnable             = 0U,
                .syncPin                        = 3U,
                .extClkSrc                      = AASRC_TXSYNC_MAIN_PLL4_HSDIV3_CLKOUT,
                .overrideClkSettle              = 1U,
            },
            {
                .clkZoneDiv                     = 128U,
                .isClkZoneDivEnable             = 0U,
                .syncPin                        = 2U,
                .extClkSrc                      = AASRC_TXSYNC_MAIN_PLL4_HSDIV3_CLKOUT,
                .overrideClkSettle              = 0U,
            },
        },

    },
};

/* AASRC Channel Object Configurations */

/* AASRC transmit loopjob buffer for mono */
uint32_t gMonoTxLoopjobBuf0[1024] __attribute__((aligned(256))) = {0};
/* AASRC receive loopjob buffer */
uint32_t gMonoRxLoopjobBuf0[1024] __attribute__((aligned(256))) = {0};

/* AASRC transmit loopjob buffer for  stereo */
uint32_t gStereoTxLoopjobBuf0[1024*2*2] __attribute__((aligned(256))) = {0};
/* AASRC receive loopjob buffer */
uint32_t gStereoRxLoopjobBuf0[1024*2] __attribute__((aligned(256))) = {0};

/* AASRC transmit loopjob buffer for group */
uint32_t gGroupTxLoopjobBuf0[1024*5] __attribute__((aligned(256))) = {0};
/* AASRC receive loopjob buffer */
uint32_t gGroupRxLoopjobBuf0[1024*5] __attribute__((aligned(256))) = {0};

/* AASRC receive Callback */
void aasrc_rxcb(AASRC_ChHandle chHandle, AASRC_Transaction *transaction);
/* AASRC transmit callback */
void aasrc_txcb(AASRC_ChHandle chHandle, AASRC_Transaction *transaction);
/* AASRC error Callback */
void aasrc_ch_error_handler(AASRC_ChHandle chHandle, AASRC_Transaction *transactionTx, AASRC_Transaction *transactionRx);

/* AASRC Channel Config */
AASRC_ChObj gConfigAasrc0ChObj[CONFIG_AASRC0_NUM_CH] =
{
    {
        .chCfg                                  =
        {
            .chType                             = AASRC_MONO,
            .chCount                            = 1,
            .fifoControl.inFifoThreshold        = 16,
            .fifoControl.outFifoThreshold       = 16,
            .inClkZone                          = 0,
            .outClkZone                         = 0,
            .inWordLen                          = 24,
            .ditherEnable                       = 0,
            .mute                               = 0,
            .directDownSample                   = 0,
            .attenuation                        = 0,
            .deEmphasisMode                     = 0,
            .groupDelay                         = AASRC_GROUP_DELAY_64,
            .outWordLen                         = 24,
        },
        .errCbFxn                               = aasrc_ch_error_handler,
        .xmtObj.cbFxn                           = aasrc_txcb,
        .rcvObj.cbFxn                           = aasrc_rxcb,

        .xmtObj.loopjobEnable = true,
        .xmtObj.txnLoopjob.buf = (uint8_t *) gMonoTxLoopjobBuf0,
        .xmtObj.txnLoopjob.sampleCount = 1024,
        .rcvObj.loopjobEnable = true,
        .rcvObj.txnLoopjob.buf = (uint8_t *) gMonoRxLoopjobBuf0,
        .rcvObj.txnLoopjob.sampleCount = 1024,
        .dmaChCfg                           = &gAASRC0_DmaChCfg[0],


    },
    {
        .chCfg                                  =
        {
            .chType                             = AASRC_STEREO,
            .chCount                            = 2,
            .fifoControl.inFifoThreshold        = 16,
            .fifoControl.outFifoThreshold       = 16,
            .inClkZone                          = 0,
            .outClkZone                         = 1,
            .inWordLen                          = 24,
            .ditherEnable                       = 0,
            .mute                               = 0,
            .directDownSample                   = 0,
            .attenuation                        = 0,
            .deEmphasisMode                     = 0,
            .groupDelay                         = AASRC_GROUP_DELAY_64,
            .outWordLen                         = 24,
        },
        .errCbFxn                               = aasrc_ch_error_handler,
        .xmtObj.cbFxn                           = aasrc_txcb,
        .rcvObj.cbFxn                           = aasrc_rxcb,

        .xmtObj.loopjobEnable = true,
        .xmtObj.txnLoopjob.buf = (uint8_t *) gStereoTxLoopjobBuf0,
        .xmtObj.txnLoopjob.sampleCount = 1024*2*2,
        .rcvObj.loopjobEnable = true,
        .rcvObj.txnLoopjob.buf = (uint8_t *) gStereoRxLoopjobBuf0,
        .rcvObj.txnLoopjob.sampleCount = 1024*2,
        .dmaChCfg                           = &gAASRC0_DmaChCfg[2],
    },
    {
        .chCfg                                  =
        {
            .chType                             = AASRC_GROUP,
            .chCount                            = 5,
            .fifoControl.inFifoThreshold        = 16,
            .fifoControl.outFifoThreshold       = 16,
            .inClkZone                          = 0,
            .outClkZone                         = 0,
            .inWordLen                          = 24,
            .ditherEnable                       = 0,
            .mute                               = 0,
            .directDownSample                   = 0,
            .attenuation                        = 0,
            .deEmphasisMode                     = 0,
            .groupDelay                         = AASRC_GROUP_DELAY_64,
            .outWordLen                         = 24,
        },
        .errCbFxn                               = aasrc_ch_error_handler,
        .xmtObj.cbFxn                           = aasrc_txcb,
        .rcvObj.cbFxn                           = aasrc_rxcb,

        .xmtObj.loopjobEnable = true,
        .xmtObj.txnLoopjob.buf = (uint8_t *) gGroupTxLoopjobBuf0,
        .xmtObj.txnLoopjob.sampleCount = 1024*5,
        .rcvObj.loopjobEnable = true,
        .rcvObj.txnLoopjob.buf = (uint8_t *) gGroupRxLoopjobBuf0,
        .rcvObj.txnLoopjob.sampleCount = 1024*5,
        .dmaChCfg                           = &gAASRC0_DmaChCfg[1],
    },

};

/* AASRC Attributes - No need to edit */

static AASRC_Attrs gAasrcAttrs[CONFIG_AASRC_NUM_INSTANCES] =
{
#if defined (CONFIG_AASRC0)
    {
        .instNum            = 0U,
        .baseAddr           = CSL_AASRC0_CFG_BASE,
        .streamDataBaseAddr = CSL_AASRC0_DATA_R1_BASE,
        .groupDataBaseAddr  = CSL_AASRC0_DATA_R0_BASE,
        .intCfg             =
        {
         {
#if defined(__C7504__) || defined(__C7524__)
            .intrNum                            = 20U,
            .evntNum                            = 50U,
#else
            .intrNum                            = 50U,
            .evntNum                            = 0U,
#endif
            .intrPriority                       = 4U,
         },
         {
#if defined(__C7504__) || defined(__C7524__)
            .intrNum                            = 22U,
            .evntNum                            = 52U,
#else
            .intrNum                            = 52U,
            .evntNum                            = 0U,
#endif
            .intrPriority                       = 4U,
         },
         {
#if defined(__C7504__) || defined(__C7524__)
            .intrNum                            = 21U,
            .evntNum                            = 51U,
#else
            .intrNum                            = 51U,
            .evntNum                            = 0U,
#endif
            .intrPriority                       = 4U,
         },
         {
#if defined(__C7504__) || defined(__C7524__)
            .intrNum                            = 23U,
            .evntNum                            = 53U,
#else
            .intrNum                            = 53U,
            .evntNum                            = 0U,
#endif
            .intrPriority                       = 4U,
         },
         {
#if defined(__C7504__) || defined(__C7524__)
            .intrNum                            = 24U,
            .evntNum                            = 54U,
#else
            .intrNum                            = 54U,
            .evntNum                            = 0U,
#endif
            .intrPriority                       = 4U,
         },
        },
    },
#endif

#if defined (CONFIG_AASRC1)
    {
        .instNum            = 1U,
        .baseAddr           = CSL_AASRC1_CFG_BASE,
        .streamDataBaseAddr = CSL_AASRC1_DATA_R1_BASE,
        .groupDataBaseAddr  = CSL_AASRC1_DATA_R0_BASE,
        .intCfg             =
       {
        {
#if defined(__C7504__) || defined(__C7524__)
            .intrNum                            = 25U,
            .evntNum                            = 55U,
#else
            .intrNum                            = 55U,
            .evntNum                            = 0U,
#endif
            .intrPriority                       = 4U,
        },
        {
#if defined(__C7504__) || defined(__C7524__)
            .intrNum                            = 27U,
            .evntNum                            = 57U,
#else
            .intrNum                            = 57U,
            .evntNum                            = 0U,
#endif
            .intrPriority                       = 4U,
        },
        {
#if defined(__C7504__) || defined(__C7524__)
            .intrNum                            = 26U,
            .evntNum                            = 56U,
#else
            .intrNum                            = 56U,
            .evntNum                            = 0U,
#endif
            .intrPriority                       = 4U,
        },
        {
#if defined(__C7504__) || defined(__C7524__)
            .intrNum                            = 28U,
            .evntNum                            = 58U,
#else
            .intrNum                            = 58U,
            .evntNum                            = 0U,
#endif
            .intrPriority                       = 4U,
        },
        {
#if defined(__C7504__) || defined(__C7524__)
            .intrNum                            = 29U,
            .evntNum                            = 59U,
#else
            .intrNum                            = 59U,
            .evntNum                            = 0U,
#endif
            .intrPriority                       = 4U,
        },
       },
    },
#endif
};

/* AASRC objects - initialized by the driver */
static AASRC_Object gAasrcObjects[CONFIG_AASRC_NUM_INSTANCES];

/* AASRC driver configuration */
AASRC_Config gAasrcConfig[CONFIG_AASRC_NUM_INSTANCES] =
{
#if defined (CONFIG_AASRC0)
    {
        &gAasrcAttrs[CONFIG_AASRC0],
        &gAasrcObjects[CONFIG_AASRC0],
    },
#endif
#if defined (CONFIG_AASRC1)
    {
        &gAasrcAttrs[CONFIG_AASRC1],
        &gAasrcObjects[CONFIG_AASRC1],
    },
#endif
};

AASRC_Handle gAasrcHandle[CONFIG_AASRC_NUM_INSTANCES];

uint8_t gAasrcConfigChNum[CONFIG_AASRC_NUM_INSTANCES] =
{
#if defined (CONFIG_AASRC0)
    CONFIG_AASRC0_NUM_CH,
#endif
#if defined (CONFIG_AASRC1)
    CONFIG_AASRC1_NUM_CH,
#endif
};

uint8_t gAasrcRxClkZoneNum[CONFIG_AASRC_NUM_INSTANCES] =
{
#if defined (CONFIG_AASRC0)
    CONFIG_AASRC0_NUM_RX_CLKZONE,
#endif
#if defined (CONFIG_AASRC1)
    CONFIG_AASRC1_NUM_RX_CLKZONE,
#endif
};

uint8_t gAasrcTxClkZoneNum[CONFIG_AASRC_NUM_INSTANCES] =
{
#if defined (CONFIG_AASRC0)
    CONFIG_AASRC0_NUM_TX_CLKZONE,
#endif
#if defined (CONFIG_AASRC1)
    CONFIG_AASRC1_NUM_TX_CLKZONE,
#endif
};

uint8_t gAasrcInstNum = CONFIG_AASRC_NUM_INSTANCES;

AASRC_ChObj *gConfigAasrcChObj[] =
{
#if defined (CONFIG_AASRC0)
    gConfigAasrc0ChObj,
#endif
#if defined (CONFIG_AASRC1)
    gConfigAasrc1ChObj,
#endif
};

void Drivers_aasrcOpen(void)
{
    uint8_t instCnt;
    int32_t  status = SystemP_SUCCESS;
    uint8_t chCount = 0U;
    AASRC_ChHandle chHandle = NULL;

    for(instCnt = 0U; instCnt < CONFIG_AASRC_NUM_INSTANCES; instCnt++)
    {
        gAasrcHandle[instCnt] = NULL;   /* Init to NULL so that we can exit gracefully */
    }

    /* Open all instances */
    for(instCnt = 0U; instCnt < CONFIG_AASRC_NUM_INSTANCES; instCnt++)
    {
        gAasrcHandle[instCnt] = AASRC_open(instCnt, &gAasrcOpenParams[instCnt]);
        if(NULL == gAasrcHandle[instCnt])
        {
            DebugP_logError("AASRC open failed for instance %d !!!\r\n", instCnt);
            status = SystemP_FAILURE;
            break;
        }
    }

#if defined (CONFIG_AASRC0)
    /* Channel Configuration */
    for(chCount = 0U; chCount < CONFIG_AASRC0_NUM_CH; chCount++)
    {
        chHandle = AASRC_chOpen(chCount, gAasrcHandle[0]);
        status = AASRC_chConfig(chHandle);
        DebugP_assertNoLog(status == SystemP_SUCCESS);
    }
#endif

#if defined (CONFIG_AASRC1)
    /* Channel Configuration */
    for(chCount = 0U; chCount < CONFIG_AASRC1_NUM_CH; chCount++)
    {
        chHandle = AASRC_chOpen(chCount, gAasrcHandle[1]);
        status = AASRC_chConfig(chHandle);
        DebugP_assertNoLog(status == SystemP_SUCCESS);
    }
#endif

    if(SystemP_FAILURE == status)
    {
        Drivers_aasrcClose();   /* Exit gracefully */
    }

    return;
}

void Drivers_aasrcClose(void)
{
    uint32_t instCnt;
    /* Close all instances that are open */
    for(instCnt = 0U; instCnt < CONFIG_AASRC_NUM_INSTANCES; instCnt++)
    {
        if(gAasrcHandle[instCnt] != NULL)
        {
            AASRC_close(gAasrcHandle[instCnt]);
            gAasrcHandle[instCnt] = NULL;
        }
    }

    return;
}

/* Clock Configuration */

typedef struct {

    uint32_t moduleId;
    uint32_t clkId;
    uint32_t clkRate;

} SOC_ModuleClockFrequency;

#define SOC_MODULES_END     (0xFFFFFFFFu)

/* power_clock_config.c */
uint32_t gAsrcSocModules[] = {
#if defined (CONFIG_AASRC0)
    TISCI_DEV_AASRC0,
#endif
#if defined (CONFIG_AASRC1)
    TISCI_DEV_AASRC1,
#endif
    SOC_MODULES_END,
};

SOC_ModuleClockFrequency gAsrcSocModulesClockFrequency[] = {
    { TISCI_DEV_AASRC0, TISCI_DEV_AASRC0_SYS_CLK, 200000000 },
    { TISCI_DEV_AASRC1, TISCI_DEV_AASRC1_SYS_CLK, 200000000 },\
    { SOC_MODULES_END, SOC_MODULES_END, SOC_MODULES_END },
};

/* ti_dpl_config.c */

void Aasrc_dplInit(void)
{
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MAIN, 2);

    /* set the divider value as (x+1), programmer should set only x,  (check spec)*/
    CSL_REG32_FINS(CSL_MAIN_CTRL_MMR_CFG0_REGS_BASE + CSL_MAIN_CTRL_MMR_CFG0_ASRC_SYNC_DIV_CTRL,
                   MAIN_CTRL_MMR_CFG0_ASRC_SYNC_DIV_CTRL_CLK_DIV, 1);\
    /* send the load signal to hardware divider */
    CSL_REG32_FINS(CSL_MAIN_CTRL_MMR_CFG0_REGS_BASE + CSL_MAIN_CTRL_MMR_CFG0_ASRC_SYNC_DIV_CTRL,
                   MAIN_CTRL_MMR_CFG0_ASRC_SYNC_DIV_CTRL_CLK_DIV_LD, 1);
    SOC_controlModuleLockMMR(SOC_DOMAIN_ID_MAIN, 2);

}

void Aasrc_clockEnable(void)
{
    int32_t status;
    uint32_t i = 0;

    while(gAsrcSocModules[i]!=SOC_MODULES_END)
    {
        status = SOC_moduleClockEnable(gAsrcSocModules[i], 1);
        DebugP_assertNoLog(status == SystemP_SUCCESS);
        i++;
    }
}

void Aasrc_clockDisable(void)
{
    int32_t status;
    uint32_t i = 0;

    while(gAsrcSocModules[i]!=SOC_MODULES_END)
    {
        status = SOC_moduleClockEnable(gAsrcSocModules[i], 0);
        DebugP_assertNoLog(status == SystemP_SUCCESS);
        i++;
    }
}

void Aasrc_clockSetFrequency(void)
{
    int32_t status;
    uint32_t i = 0;
    uint64_t clkRate;

    DebugP_log("\r\n");
    while(gAsrcSocModulesClockFrequency[i].moduleId!=SOC_MODULES_END)
    {
        status = SOC_moduleSetClockFrequency(
                    gAsrcSocModulesClockFrequency[i].moduleId,
                    gAsrcSocModulesClockFrequency[i].clkId,
                    gAsrcSocModulesClockFrequency[i].clkRate
                    );
        DebugP_assertNoLog(status == SystemP_SUCCESS);
        status = SOC_moduleGetClockFrequency(gAsrcSocModulesClockFrequency[i].moduleId,
                                            gAsrcSocModulesClockFrequency[i].clkId,
                                             &clkRate);
        DebugP_assertNoLog(status == SystemP_SUCCESS);
        DebugP_log("AASRC %u sys_clk = %0.6f MHz\r\n", i, (clkRate/(float)(pow(10,6))));
        i++;
    }
#if defined (CONFIG_AASRC0)
    status = SOC_moduleGetClockFrequency(TISCI_DEV_AASRC0,
                                         TISCI_DEV_AASRC0_VBUSP_CLK,
                                         &clkRate);
    DebugP_assertNoLog(status == SystemP_SUCCESS);
    DebugP_log("AASRC 0 vbus_clk = %0.6f MHz\r\n", (clkRate/(float)(pow(10,6))));
#endif
#if defined (CONFIG_AASRC1)
    status = SOC_moduleGetClockFrequency(TISCI_DEV_AASRC1,
                                         TISCI_DEV_AASRC1_VBUSP_CLK,
                                         &clkRate);
    DebugP_assertNoLog(status == SystemP_SUCCESS);
    DebugP_log("AASRC 1 vbus_clk = %0.6f MHz\r\n", (clkRate/(float)(pow(10,6))));
#endif
}

void Aasrc_SmInit(void)
{
    AASRC_init();
    Aasrc_clockEnable();
    Aasrc_clockSetFrequency();

    /* UDMA */
    {
        uint32_t        instId;
        int32_t         retVal = UDMA_SOK;

        for(instId = 0U; instId < CONFIG_UDMA_NUM_INSTANCES; instId++)
        {
            retVal += Udma_init(&gUdmaDrvObj[instId], &gUdmaInitPrms[instId]);
            DebugP_assert(UDMA_SOK == retVal);
        }
    }
}

void Aasrc_SmDeinit(void)
{
    Aasrc_clockDisable();

    /* UDMA */
    {
        uint32_t        instId;
        int32_t         retVal = UDMA_SOK;

        for(instId = 0U; instId < CONFIG_UDMA_NUM_INSTANCES; instId++)
        {
            retVal += Udma_deinit(&gUdmaDrvObj[instId]);
            DebugP_assert(UDMA_SOK == retVal);
        }
    }
}
