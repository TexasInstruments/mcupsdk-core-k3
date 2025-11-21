/*
 * Copyright (C) 2025 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unity.h>
#include <drivers/udma.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/AddrTranslateP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include <drivers/udma/udma_priv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define UDMA_CHHANDLE_0            (0U)
#define UDMA_CHHANDLE_1            (1U)

#define NUM_BLK_COPY_CH            (3U)
#define NUM_BLK_COPY_HC_CH         (3U)
#define NUM_BLK_COPY_UHC_CH        (3U)
#define NUM_TX_CH                  (3U)
#define NUM_RX_CH                  (3U)
#define NUM_TX_HC_CH               (3U)
#define NUM_RX_HC_CH               (3U)
#define NUM_TX_UHC_CH              (3U)
#define NUM_RX_UHC_CH              (3U)
#define NUM_FREE_RING              (3U)
#define NUM_FREE_FLOW              (3U)
#define NUM_GLOBAL_EVENT           (3U)
#define NUM_VINTR                  (3U)
#define NUM_IR_INTR                (3U)
#define NUM_RM_RANGE               (4U)
#define RM_INST_ID                 (3U)
#define RM_INTR_NUM                (1U)
#define RM_CORE_INTR_NUM           (1U)

#define VALID_DOORBELL_VALUE_1     (2U)
#define VALID_DOORBELL_VALUE_2    (130U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/** \brief UDMA test params */
typedef struct Test_UdmaMemcpyPrms
{
    uint32_t            todo;
} Test_UdmaMemcpyPrms_t;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* Testcases */
static void test_udma_dyn_coverage(void *args);
static void test_udma_csl_coverage(void *args);
void test_udma_event(void);
void test_udma_main(void *);
void test_udma_ch(void);
void test_udma(void);
void test_udma_utils(void);
void test_udma_flow(void);
void test_udma_rm(void);
void test_udma_ring_lcdma(void);
void test_udma_ring_common(void);
void udma_default_handle_params_init(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void test_udma_main(void *args)
{
    UNITY_BEGIN();

    RUN_TEST(test_udma_dyn_coverage, 7253, NULL);
    RUN_TEST(test_udma_csl_coverage, 7254, NULL);

    UNITY_END();

    return;
}

/*
 * Unity framework required functions
 */
void setUp(void)
{
}

void tearDown(void)
{
}

void udma_default_handle_params_init(void)
{
    Udma_DrvHandle drvHandle = &gUdmaDrvObj[CONFIG_UDMA0];

    Udma_ChHandle chHandle0 = gConfigUdma0BlkCopyChHandle[UDMA_CHHANDLE_0];
    Udma_ChHandle chHandle1 = gConfigUdma0BlkCopyChHandle[UDMA_CHHANDLE_1];

    Udma_ChHandleInt    chHandle0Int = (Udma_ChHandleInt) chHandle0;
    Udma_ChHandleInt    chHandle1Int = (Udma_ChHandleInt) chHandle1;

    Udma_DrvHandleInt   drvHandleInt = (Udma_DrvHandleInt) drvHandle;

    chHandle0Int->drvHandle = drvHandleInt;
    chHandle0Int->chType = 0U;
    drvHandleInt->instType = 0U;
    chHandle0Int->chInitDone = UDMA_INIT_DONE;
    chHandle0Int->chOesAllocDone = FALSE;
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    chHandle1Int->chInitDone = UDMA_INIT_DONE;
}

void myMemOps(void *pVirtAddr, uint32_t size, uint32_t opsType){};

static void test_udma_csl_coverage(void *args)
{
   CSL_BcdmaCfg pCfg;
   CSL_BcdmaTxChanCfg pTxChanCfg;
   CSL_BcdmaRxChanCfg pRxChanCfg;
   CSL_BcdmaChanStats pChanStats;
   CSL_PktdmaChanStats pChanStatsk;
   CSL_BcdmaRemotePeerOpts pPeerOpts;
   CSL_BcdmaChanBurstSize burstSize;
   CSL_BcdmaTeardownOpts pTdOpts;
   CSL_BcdmaRT pRT;
   CSL_PktdmaRT pRTk;
   CSL_IntaggrCfg pCfgI;
   CSL_LcdmaRingaccCfg pCfg2;
   CSL_LcdmaRingaccRingCfg pRing;
   CSL_PktdmaCfg pCfgk;
   int32_t retValue = 0U;
   uint32_t value2=0;

   /* passing valid parameters to initialize a transmit channel */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.bcChanCnt=1;
   pCfg.splitTxChanCnt=2;
   retValue = CSL_bcdmaTxChanCfg(&pCfg,2,&pTxChanCfg);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to initialize a receive channel */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.bcChanCnt=1;
   pCfg.splitTxChanCnt=1;
   pCfg.splitRxChanCnt=1;
   retValue = CSL_bcdmaRxChanCfg(&pCfg,2,&pRxChanCfg);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid pararmeters enabling the transmit channel */
   CSL_bcdmaInitCfg(&pCfg);
   retValue = CSL_bcdmaEnableTxChan(&pCfg,2);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   /* passing valid pararmeters enabling the transmit channel */
   retValue = CSL_bcdmaEnableRxChan(NULL,1);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   /* getting the real-time register values for the CSL_BCDMA_CHAN_OP_ENABLE */
   CSL_bcdmaInitCfg(&pCfg);
   retValue = CSL_bcdmaGetTxRT(&pCfg,1,&pRT);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   /* clear error status for the channel(CSL_BCDMA_CHAN_TYPE_BLOCK_COPY) */
   CSL_bcdmaInitCfg(&pCfg);
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_CLEAR_ERROR,CSL_BCDMA_CHAN_TYPE_BLOCK_COPY,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_EBADARGS, retValue);

   /* clear error status for the channel(CSL_BCDMA_CHAN_TYPE_SPLIT_RX) */
   CSL_bcdmaInitCfg(&pCfg);
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_CLEAR_ERROR,CSL_BCDMA_CHAN_TYPE_SPLIT_RX,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_EBADARGS, retValue);

   /* clear error status for the channel(CSL_BCDMA_CHAN_TYPE_SPLIT_TX) */
   CSL_bcdmaInitCfg(&pCfg);
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_CLEAR_ERROR,CSL_BCDMA_CHAN_TYPE_SPLIT_TX,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_EBADARGS, retValue);

    /* passing the valid parameters to  configure the control registers for channel (CSL_BCDMA_CHAN_TYPE_SPLIT_TX) */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitTxChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_CONFIG,CSL_BCDMA_CHAN_TYPE_SPLIT_TX,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_EBADARGS, retValue);

   /* passing the valid parameters to  configure the control registers for channel (CSL_BCDMA_CHAN_TYPE_BLOCK_COPY) */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.bcChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_CONFIG,CSL_BCDMA_CHAN_TYPE_BLOCK_COPY,1,(void *)&pTxChanCfg);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   CSL_bcdmaInitCfg(&pCfg);
   pCfg.bcChanCnt=2;
   pTxChanCfg.busPriority=8U;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_CONFIG,CSL_BCDMA_CHAN_TYPE_BLOCK_COPY,1,(void *)&pTxChanCfg);
   TEST_ASSERT_EQUAL_INT32(CSL_EINVALID_PARAMS, retValue);

   /* passing the valid parameters to  configure the control registers for channel (CSL_BCDMA_CHAN_TYPE_SPLIT_TX) */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitTxChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_CONFIG,CSL_BCDMA_CHAN_TYPE_SPLIT_TX,1,(void *)&pTxChanCfg);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitTxChanCnt=2;
   pTxChanCfg.busPriority=8U;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_CONFIG,CSL_BCDMA_CHAN_TYPE_SPLIT_TX,1,(void *)&pTxChanCfg);
   TEST_ASSERT_EQUAL_INT32(CSL_EINVALID_PARAMS, retValue);

   /* passing the valid parameters to  configure the control registers for channel (CSL_BCDMA_CHAN_TYPE_SPLIT_RX) */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitRxChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_CONFIG,CSL_BCDMA_CHAN_TYPE_SPLIT_RX,1,(void *)&pTxChanCfg);
   TEST_ASSERT_EQUAL_INT32(CSL_EINVALID_PARAMS, retValue);

   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitRxChanCnt=2;
   pTxChanCfg.busPriority=8U;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_CONFIG,CSL_BCDMA_CHAN_TYPE_SPLIT_RX,1,(void *)&pTxChanCfg);
    TEST_ASSERT_EQUAL_INT32(CSL_EINVALID_PARAMS, retValue);

   /* passing the valid parameters to  configure the control registers for channel (CSL_BCDMA_CHAN_TYPE_REF_PKT_RING) */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitTxChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_CONFIG,CSL_BCDMA_CHAN_TYPE_REF_PKT_RING,1,(void *)&pTxChanCfg);
   TEST_ASSERT_EQUAL_INT32(CSL_EBADARGS, retValue);

   /* passing valid parameters to enable BCDMA channel (Block Copy) */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.bcChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_ENABLE,CSL_BCDMA_CHAN_TYPE_BLOCK_COPY,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to enable BCDMA channel (Split TX) */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitTxChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_ENABLE,CSL_BCDMA_CHAN_TYPE_SPLIT_TX,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to enable DMA channel (Split RX) */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitRxChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_ENABLE,CSL_BCDMA_CHAN_TYPE_SPLIT_RX,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to disable BCDMA channel (Block Copy) */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitRxChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_DISABLE,CSL_BCDMA_CHAN_TYPE_SPLIT_RX,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to disable BCDMA channel (Split TX) */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.bcChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_DISABLE,CSL_BCDMA_CHAN_TYPE_BLOCK_COPY,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to disable BCDMA channel (Split RX) */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitTxChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_DISABLE,CSL_BCDMA_CHAN_TYPE_SPLIT_TX,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to pause BCDMA channel (Block Copy) */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.bcChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_PAUSE,CSL_BCDMA_CHAN_TYPE_BLOCK_COPY,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   CSL_bcdmaInitCfg(&pCfg);
   pCfg.bcChanCnt=2;
   pCfg.pBcChanRtRegs->CHAN[1].CTL |= CSL_BCDMA_BCRT_CHAN_CTL_EN_MASK;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_PAUSE,CSL_BCDMA_CHAN_TYPE_BLOCK_COPY,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to pause BCDMA channel (Split TX) */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitTxChanCnt=2;
   pCfg.pTxChanRtRegs->CHAN[1].CTL |= CSL_BCDMA_TXCRT_CHAN_CTL_EN_MASK;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_PAUSE,CSL_BCDMA_CHAN_TYPE_SPLIT_TX,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to disable BCDMA channel (Split RX) */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitRxChanCnt=2;
   pCfg.pRxChanRtRegs->CHAN[1].CTL |= CSL_BCDMA_RXCRT_CHAN_CTL_EN_MASK;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_PAUSE,CSL_BCDMA_CHAN_TYPE_SPLIT_RX,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to resume BCDMA channel (Block Copy) */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.bcChanCnt=2;
   pCfg.pBcChanRtRegs->CHAN[1].CTL |= CSL_BCDMA_BCRT_CHAN_CTL_EN_MASK;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_RESUME,CSL_BCDMA_CHAN_TYPE_BLOCK_COPY,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to resume BCDMA channel (Split TX) */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitTxChanCnt=2;
   pCfg.pTxChanRtRegs->CHAN[1].CTL |= CSL_BCDMA_TXCRT_CHAN_CTL_EN_MASK;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_RESUME,CSL_BCDMA_CHAN_TYPE_SPLIT_TX,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to resume BCDMA channel (Split RX) */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitRxChanCnt=2;
   pCfg.pRxChanRtRegs->CHAN[1].CTL |= CSL_BCDMA_RXCRT_CHAN_CTL_EN_MASK;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_RESUME,CSL_BCDMA_CHAN_TYPE_SPLIT_RX,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to start the BCDMA transfer for Block Copy channel */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.bcChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_TRIGGER,CSL_BCDMA_CHAN_TYPE_BLOCK_COPY,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to start the BCDMA transfer for Split TX channel */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitTxChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_TRIGGER,CSL_BCDMA_CHAN_TYPE_SPLIT_TX,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to start the BCDMA transfer for Split RX channel */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitRxChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_TRIGGER,CSL_BCDMA_CHAN_TYPE_SPLIT_RX,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to Fetche the runtime transfer data for the Split RX channel when popdata is NULL*/
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitRxChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_GET_STATS,CSL_BCDMA_CHAN_TYPE_SPLIT_RX,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_EBADARGS, retValue);

   /* passing valid parameters to Fetche the runtime transfer data for the Block Copy channel */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.bcChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_GET_STATS,CSL_BCDMA_CHAN_TYPE_BLOCK_COPY,1,(void *)&pChanStats);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to Fetche the runtime transfer data for the Split TX channel */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitTxChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_GET_STATS,CSL_BCDMA_CHAN_TYPE_SPLIT_TX,1,(void *)&pChanStats);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to Fetche the runtime transfer data for the Split RX channel */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitRxChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_GET_STATS,CSL_BCDMA_CHAN_TYPE_SPLIT_RX,1,(void *)&pChanStats);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to Initializes Block Copy channel counters when popdata is NULL */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitRxChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_DEC_STATS,CSL_BCDMA_CHAN_TYPE_SPLIT_RX,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_EBADARGS, retValue);

   /* passing valid parameters to Initializes Block Copy channel counters */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.bcChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_DEC_STATS,CSL_BCDMA_CHAN_TYPE_BLOCK_COPY,1,(void *)&pChanStats);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to Initializes Split TX channel counters */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitTxChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_DEC_STATS,CSL_BCDMA_CHAN_TYPE_SPLIT_TX,1,(void *)&pChanStats);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to Initializes Split RX channel counters */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitRxChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_DEC_STATS,CSL_BCDMA_CHAN_TYPE_SPLIT_RX,1,(void *)&pChanStats);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to read from Block Copy channel registers */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitRxChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_GET_REMOTE_PEER_REG,CSL_BCDMA_CHAN_TYPE_SPLIT_RX,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_EBADARGS, retValue);

   /* passing valid parameters to read from Split TX channel registers */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitTxChanCnt=2;
   pPeerOpts.regIdx=20u;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_GET_REMOTE_PEER_REG,CSL_BCDMA_CHAN_TYPE_SPLIT_TX,1,(void *)&pPeerOpts);
   TEST_ASSERT_EQUAL_INT32(CSL_EINVALID_PARAMS, retValue);

   /* passing valid parameters to read from Split RX channel registers */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitRxChanCnt=2;
   pPeerOpts.regIdx=10u;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_GET_REMOTE_PEER_REG,CSL_BCDMA_CHAN_TYPE_SPLIT_RX,1,(void *)&pPeerOpts);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to write from Split RX channel registers */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitRxChanCnt=2;
   pPeerOpts.regIdx=10u;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_SET_REMOTE_PEER_REG,CSL_BCDMA_CHAN_TYPE_SPLIT_RX,1,(void *)&pPeerOpts);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to write from Block Copy channel registers */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.bcChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_SET_REMOTE_PEER_REG,CSL_BCDMA_CHAN_TYPE_BLOCK_COPY,1,(void *)&pPeerOpts);
   TEST_ASSERT_EQUAL_INT32(CSL_EBADARGS, retValue);

   /* configuring  a burst size for  Split RX channel when popdata is NULL */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitRxChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_SET_BURST_SIZE,CSL_BCDMA_CHAN_TYPE_SPLIT_RX,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_EBADARGS, retValue);

   /* passing valid parameters to configure a burst size for  Block Copy channel */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.bcChanCnt=2;
   burstSize=3U;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_SET_BURST_SIZE,CSL_BCDMA_CHAN_TYPE_BLOCK_COPY,1,(void *)&burstSize);
   TEST_ASSERT_EQUAL_INT32(CSL_EINVALID_PARAMS, retValue);

   CSL_bcdmaInitCfg(&pCfg);
   pCfg.bcChanCnt=2;
   burstSize=1U;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_SET_BURST_SIZE,CSL_BCDMA_CHAN_TYPE_BLOCK_COPY,1,(void *)&burstSize);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to configure a burst size for  Split TX channel */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitTxChanCnt=2;
   burstSize=2U;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_SET_BURST_SIZE,CSL_BCDMA_CHAN_TYPE_SPLIT_TX,1,(void *)&burstSize);
   TEST_ASSERT_EQUAL_INT32(CSL_EINVALID_PARAMS, retValue);

   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitTxChanCnt=2;
   burstSize=0U;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_SET_BURST_SIZE,CSL_BCDMA_CHAN_TYPE_SPLIT_TX,1,(void *)&burstSize);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to configure a burst size for  Split RX channel */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitRxChanCnt=2;
   burstSize=2U;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_SET_BURST_SIZE,CSL_BCDMA_CHAN_TYPE_SPLIT_RX,1,(void *)&burstSize);
   TEST_ASSERT_EQUAL_INT32(CSL_EINVALID_PARAMS, retValue);

   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitRxChanCnt=2;
   burstSize=0U;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_SET_BURST_SIZE,CSL_BCDMA_CHAN_TYPE_SPLIT_RX,1,(void *)&burstSize);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* Validating function behavior when an invalid channel type is passed */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.bcChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,16U,CSL_BCDMA_CHAN_TYPE_BLOCK_COPY,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_EBADARGS, retValue);

   /* passing valid parameters to disabling Split TX channel */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitTxChanCnt=2;
   pTdOpts.wait=1U;
   pTdOpts.force=1U;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_TEARDOWN,CSL_BCDMA_CHAN_TYPE_SPLIT_TX,1,(void *)&pTdOpts);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitTxChanCnt=2;
   pCfg.pTxChanRtRegs->CHAN[1].CTL |= CSL_BCDMA_TXCRT_CHAN_CTL_EN_MASK;
   pTdOpts.wait=1U;
   pTdOpts.force=1U;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_TEARDOWN,CSL_BCDMA_CHAN_TYPE_SPLIT_TX,1,(void *)&pTdOpts);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitTxChanCnt=2;
   pCfg.pTxChanRtRegs->CHAN[1].CTL |= CSL_BCDMA_TXCRT_CHAN_CTL_EN_MASK;
   pTdOpts.wait=1U;
   pTdOpts.force=0U;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_TEARDOWN,CSL_BCDMA_CHAN_TYPE_SPLIT_TX,1,(void *)&pTdOpts);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   /* passing valid parameters to disabling Split RX channel */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitTxChanCnt=2;
   pCfg.pRxChanRtRegs->CHAN[1].CTL |= CSL_BCDMA_RXCRT_CHAN_CTL_EN_MASK;
   pTdOpts.wait=1U;
   pTdOpts.force=1U;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_TEARDOWN,CSL_BCDMA_CHAN_TYPE_SPLIT_RX,1,(void *)&pTdOpts);
   TEST_ASSERT_EQUAL_INT32(CSL_EBADARGS, retValue);

   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitTxChanCnt=2;
   pCfg.pRxChanRtRegs->CHAN[1].CTL |= CSL_BCDMA_RXCRT_CHAN_CTL_EN_MASK;
   pTdOpts.wait=1U;
   pTdOpts.force=0U;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_TEARDOWN,CSL_BCDMA_CHAN_TYPE_SPLIT_RX,1,(void *)&pTdOpts);
   TEST_ASSERT_EQUAL_INT32(CSL_EBADARGS, retValue);

   /* passing valid parameters to disabling Block copy channel */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.bcChanCnt=2;
   pCfg.pBcChanRtRegs->CHAN[1].CTL |= CSL_BCDMA_BCRT_CHAN_CTL_EN_MASK;
   pTdOpts.wait=1U;
   pTdOpts.force=1U;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_TEARDOWN,CSL_BCDMA_CHAN_TYPE_BLOCK_COPY,1,(void *)&pTdOpts);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   /* Reading the live status of Split RX channel when popdata is NULL */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitRxChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_GET_RT,CSL_BCDMA_CHAN_TYPE_SPLIT_RX,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_EBADARGS, retValue);

   /* Reading the live status of Split TX channel */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitTxChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_GET_RT,CSL_BCDMA_CHAN_TYPE_SPLIT_TX,1,(void *)&pRT);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* Reading the live status of Split RX channel */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitRxChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_GET_RT,CSL_BCDMA_CHAN_TYPE_SPLIT_RX,1,(void *)&pRT);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to set runtime operational state for Split RX channel when popdate is NULL*/
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitRxChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_SET_RT,CSL_BCDMA_CHAN_TYPE_SPLIT_RX,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_EBADARGS, retValue);

   /* passing valid parameters to set runtime operational state for Split TX channel */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitTxChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_SET_RT,CSL_BCDMA_CHAN_TYPE_SPLIT_TX,1,(void *)&pRT);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to set runtime operational state for Split RX channel */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitRxChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_SET_RT,CSL_BCDMA_CHAN_TYPE_SPLIT_RX,1,(void *)&pRT);\
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to returns the real-time register values for receive channel */
   CSL_bcdmaInitCfg(&pCfg);
   retValue = CSL_bcdmaGetRxRT(&pCfg,1,&pRT);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   /* passing valid parameters to returns the real-time register values for TX  channel */
   CSL_bcdmaInitCfg(&pCfg);
   retValue = CSL_bcdmaSetTxRT(&pCfg,1,&pRT);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   /* passing valid parameters to returns the real-time register values for RX channel */
   CSL_bcdmaInitCfg(&pCfg);
   retValue = CSL_bcdmaSetRxRT(&pCfg,1,&pRT);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   /* passing valid parameters to disables the transmit channel */
   CSL_bcdmaInitCfg(&pCfg);
   retValue = CSL_bcdmaDisableTxChan(&pCfg,1);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   /* tears down the transmit channel */
   CSL_bcdmaInitCfg(&pCfg);
   retValue = CSL_bcdmaTeardownTxChan(&pCfg,1,TRUE,TRUE);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   /* tears down the receive channel */
   CSL_bcdmaInitCfg(&pCfg);
   retValue = CSL_bcdmaTeardownRxChan(&pCfg,1,TRUE,TRUE);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   CSL_bcdmaInitCfg(&pCfg);
   retValue = CSL_bcdmaTeardownRxChan(&pCfg,1,false,false);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   /* passing valid parameters to Pause a transmit channel */
   CSL_bcdmaInitCfg(&pCfg);
   retValue = CSL_bcdmaPauseTxChan(&pCfg,1);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   /* passing valid parameters to Pause a receive channel */
   CSL_bcdmaInitCfg(&pCfg);
   retValue=CSL_bcdmaPauseRxChan(&pCfg,1);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   /* passing valid parameters to Un-pause a transmit channel */
   CSL_bcdmaInitCfg(&pCfg);
   retValue = CSL_bcdmaUnpauseTxChan(&pCfg,1);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   /* passing valid parameters to Un-pause a receive channel */
   CSL_bcdmaInitCfg(&pCfg);
   retValue = CSL_bcdmaUnpauseRxChan(&pCfg,1);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   /* passing valid parameters to Get channel statistics */
   CSL_bcdmaInitCfg(&pCfg);
   CSL_bcdmaGetChanStats(&pCfg,1,1,&pChanStats);

   /* passing valid parameters to Decrement channel statistics */
   CSL_bcdmaInitCfg(&pCfg);
   CSL_bcdmaDecChanStats(&pCfg,1,1,&pChanStats);

   /* passing valid parameters to Read a channel peer register when popdata is NULL */
   CSL_bcdmaInitCfg(&pCfg);
   CSL_bcdmaGetChanPeerReg(&pCfg,1,1,1,NULL);

   /* passing valid parameters clear block copy channel errors  */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.bcChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_CLEAR_ERROR,CSL_BCDMA_CHAN_TYPE_BLOCK_COPY,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters clear block split TX channel errors  */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitTxChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_CLEAR_ERROR,CSL_BCDMA_CHAN_TYPE_SPLIT_TX,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters clear block split RX channel errors  */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.splitRxChanCnt=2;
   retValue = CSL_bcdmaChanOp(&pCfg,CSL_BCDMA_CHAN_OP_CLEAR_ERROR,CSL_BCDMA_CHAN_TYPE_SPLIT_RX,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing NULL parameters to initialize a transmit channel */
   retValue = CSL_bcdmaTxChanCfg(NULL,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   /* passing NULL parameters to initialize a transmit channel */
   retValue=CSL_bcdmaRxChanCfg(NULL,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   /* passing valid parameters to Read a channel peer register */
   CSL_bcdmaInitCfg(&pCfg);
   pCfg.bcChanCnt=1;
   pCfg.splitTxChanCnt=1;
   pCfg.splitRxChanCnt=1;
   pCfg.pTxChanRtRegs->CHAN[1].PEER0=1;
   pPeerOpts.regIdx=10U;
   retValue = CSL_bcdmaGetChanPeerReg(&pCfg,1,1,1,(void *)&pPeerOpts);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* mapping a local event to the global event */
   pCfgI.pL2gRegs=NULL;
   pCfgI.localEventCnt=0U;
   retValue = CSL_intaggrMapEventToLocalEvent(&pCfgI,1U,0U,0U);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   pCfgI.localEventCnt=1U;
   retValue = CSL_intaggrMapEventToLocalEvent(&pCfgI,1U,2U,3U);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   pCfgI.localEventCnt=2U;
   retValue = CSL_intaggrMapEventToLocalEvent(&pCfgI,1U,1U,1U);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   /* Determining if a status interrupt is pending when parameters are NULL*/
   CSL_intaggrIsIntrPending(NULL,0,0);

   /* Clearing a pending status interrupt */
   retValue = CSL_intaggrClrIntr(NULL,0);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to return the forward occupancy for the specified ring */
   CSL_lcdma_ringaccInitCfg(&pCfg2);
   CSL_lcdma_ringaccGetForwardRingOcc(&pCfg2,1,CSL_LCDMA_RINGACC_RING_MODE_INVALID);

   /* Dequeue a value pushed to a ring in FIFO order */
   CSL_lcdma_ringaccInitCfg(&pCfg2);
   CSL_lcdma_ringaccInitRingCfg(&pRing);
   pRing.wrOcc=2U;
   pRing.wrIdx=0U;
   CSL_lcdma_ringaccDequeue(&pCfg2,&pRing,NULL);

   CSL_lcdma_ringaccInitCfg(&pCfg2);
   CSL_lcdma_ringaccInitRingCfg(&pRing);
   pRing.wrOcc=2U;
   pRing.wrIdx=3U;
   pRing.elCnt=2U;
   CSL_lcdma_ringaccDequeue(&pCfg2,&pRing,NULL);

   CSL_lcdma_ringaccInitCfg(&pCfg2);
   CSL_lcdma_ringaccInitRingCfg(&pRing);
   pRing.wrOcc=0U;
   CSL_lcdma_ringaccDequeue(&pCfg2,&pRing,NULL);

   /* Initialize a ring with defaul values */
   CSL_lcdma_ringaccInitCfg(&pCfg2);
   CSL_lcdma_ringaccInitRingCfg(&pRing);
   pRing.mode = 1U;
   pRing.elCnt = 1U;
   pRing.virtBase=(void *)&value2;
   pRing.physBase=8UL;
   CSL_lcdma_ringaccInitRing(&pCfg2,1,&pRing);

   /* passing valid parameters to teardown ring */
   CSL_lcdma_ringaccIsTeardownComplete(&pCfg2,1);

   /* passing NULL values to read the value from a peer register */
   retValue = CSL_pktdmaGetChanPeerReg(NULL,1,2U,1,NULL);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   /* read the value from a peer register for the TX channel */
   pCfgk.txChanCnt=3U;
   retValue = CSL_pktdmaGetChanPeerReg(&pCfgk,1U,CSL_PKTDMA_CHAN_DIR_TX,20U,&value2);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   /* passing valid parameters to Un-pause a receive channel */
   pCfgk.rxChanCnt=3U;
   retValue = CSL_pktdmaUnpauseRxChan(&pCfgk,1);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to pause a receive channel */

   pCfgk.rxChanCnt=3U;
   retValue = CSL_pktdmaPauseRxChan(&pCfgk,1);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to Un-pause a transmit channel */

   pCfgk.txChanCnt=3U;
   retValue = CSL_pktdmaUnpauseTxChan(&pCfgk,1);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* passing valid parameters to pause a transmit channel */

   pCfgk.txChanCnt=3U;
   retValue = CSL_pktdmaPauseTxChan(&pCfgk,1);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);


   pCfgk.txChanCnt=1U;
   retValue = CSL_pktdmaPauseTxChan(&pCfgk,3U);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   /* passing NULL to tears down the receive channel */
   retValue = CSL_pktdmaTeardownRxChan(NULL,0,true,true);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   /* passing valid parameters to tears down the receive channel */

   pCfgk.rxChanCnt=3U;
   retValue = CSL_pktdmaTeardownRxChan(&pCfgk,1,true,true);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   /* passing valid parameters to Teardown a transmit channel */

   pCfgk.txChanCnt=3U;
   retValue = CSL_pktdmaTeardownTxChan(&pCfgk,1,true,true);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   /* Disable a receive channel when PKTDMA configuration is NULL */
   retValue = CSL_pktdmaDisableRxChan(NULL,0);
   TEST_ASSERT_EQUAL_INT32(CSL_EFAIL, retValue);

   /* passing valid parameters  to Disable a receive channel */

   pCfgk.rxChanCnt=3U;
   retValue = CSL_pktdmaDisableRxChan(&pCfgk,1);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* writing a value to a peer register for the TX channel */

   pCfgk.txChanCnt=2U;
   retValue = CSL_pktdmaSetChanPeerReg(&pCfgk,1U,CSL_PKTDMA_CHAN_DIR_TX,10U,&value2);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* read the value from a peer register for the TX channel */

   pCfgk.rxChanCnt=2U;
   retValue = CSL_pktdmaGetChanPeerReg(&pCfgk,1U,CSL_PKTDMA_CHAN_DIR_RX,10U,&value2);
   TEST_ASSERT_EQUAL_INT32(CSL_PASS, retValue);

   /* getting PKTDMA configuration information */

   CSL_pktdmaGetCfg(&pCfgk);

   /* Getting an RX channel's real-time register values */
   CSL_pktdmaGetRxRT(&pCfgk,1,&pRTk);

   /* passing parameters to Set an RX channel's real-time register values */
   CSL_pktdmaSetRxRT(&pCfgk,1,&pRTk);

   /* Getting an TX channel's real-time register values */
   CSL_pktdmaGetTxRT(&pCfgk,1,&pRTk);

   /* passing parameters to Set an TX channel's real-time register values */
   CSL_pktdmaSetTxRT(&pCfgk,1,&pRTk);

   /* reading statistics for a transmit channel */
   CSL_pktdmaGetChanStats(&pCfgk,1,CSL_PKTDMA_CHAN_DIR_TX,&pChanStatsk);

   /* reading statistics for a receive channel */
   CSL_pktdmaGetChanStats(&pCfgk,1,CSL_PKTDMA_CHAN_DIR_RX,&pChanStatsk);

   /* decrement statistics for a transmit channel */
   CSL_pktdmaDecChanStats(&pCfgk,1,CSL_PKTDMA_CHAN_DIR_TX,&pChanStatsk);

   /* decrement statistics for a receive channel */
   CSL_pktdmaDecChanStats(&pCfgk,1,CSL_PKTDMA_CHAN_DIR_RX,&pChanStatsk);
}

void test_udma(void)
{
    uint32_t retValue = 0U;
    uint32_t instId = 0U;
    Udma_InitPrms initPrms;
    /* Driver and channel handle initialization */
    Udma_DrvHandle drvHandle = &gUdmaDrvObj[CONFIG_UDMA0];
    Udma_ChHandle chHandle0 = gConfigUdma0BlkCopyChHandle[0];
    Udma_DrvHandleInt   drvHandleInt = (Udma_DrvHandleInt) drvHandle;
    Udma_ChHandleInt    chHandle0Int = (Udma_ChHandleInt) chHandle0;
    chHandle0Int->drvHandle = drvHandleInt;
    DebugP_log("\r\n udma dynamic coverage test...\r\n");
    /* Passing NULL as drvHandle should return UDMA_EBADARGS */
    retValue = Udma_init(NULL_PTR, &initPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing NULL as initPrms should return UDMA_EBADARGS */
    retValue = UdmaInitPrms_init(instId,NULL_PTR);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Valid initialization of initPrms */
    retValue = UdmaInitPrms_init(instId, &initPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Enable UTC and perform valid Udma_init */
    initPrms.enableUtc = TRUE;
    retValue = Udma_init(drvHandle, &initPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing a valid parameter with De-init the drvhandle */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_init(drvHandle, &initPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing NULL to deinit should return UDMA_EBADARGS */
    retValue = Udma_deinit(NULL_PTR);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    udma_default_handle_params_init();
    /* This function call execute the error check */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    udma_default_handle_params_init();
    /* This function call execute the Udma_rmDeinit */
    retValue = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing Udma_deinit call with zeroing out RM init params */
    drvHandleInt->globalEventHandle = NULL_PTR;
    drvHandleInt->rmInitPrms.numBlkCopyCh = 0U;
    drvHandleInt->rmInitPrms.numBlkCopyHcCh = 0U;
    drvHandleInt->rmInitPrms.numBlkCopyUhcCh = 0U;
    drvHandleInt->rmInitPrms.numTxCh = 0U;
    drvHandleInt->rmInitPrms.numTxHcCh = 0U;
    drvHandleInt->rmInitPrms.numTxUhcCh = 0U;
    drvHandleInt->rmInitPrms.numRxCh = 0U;
    drvHandleInt->rmInitPrms.numRxHcCh = 0U;
    drvHandleInt->rmInitPrms.numRxUhcCh = 0U;
    drvHandleInt->rmInitPrms.numUtcCh[0] = 0U;
    drvHandleInt->rmInitPrms.numUtcCh[1] = 0U;
    drvHandleInt->rmInitPrms.numMappedTxCh[0] = 0U;
    drvHandleInt->rmInitPrms.numMappedTxCh[1] = 0U;
    drvHandleInt->rmInitPrms.numMappedTxCh[2] = 0U;
    drvHandleInt->rmInitPrms.numMappedTxCh[3] = 0U;
    drvHandleInt->rmInitPrms.numFreeRing = 0U;
    drvHandleInt->rmInitPrms.numFreeFlow = 0U;
    drvHandleInt->rmInitPrms.numGlobalEvent = 0U;
    drvHandleInt->rmInitPrms.numVintr = 0U;
    drvHandleInt->rmInitPrms.numIrIntr = 0U;
    retValue = Udma_deinit(drvHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing a valid parammeter with Re-init with skipGlobalEventReg */
    initPrms.enableUtc = TRUE;
    initPrms.skipGlobalEventReg = TRUE;
    retValue = Udma_init(drvHandle, &initPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();

    DebugP_log("\r\n udma dynamic coverage test: PASS \r\n");
}

void test_udma_ch(void)
{
    uint32_t retValue = 0U;
    uint32_t chType = 1U;
    uint32_t  peerData;
    Udma_ChHandle   chHandle1;
    chHandle1 = gConfigUdma0BlkCopyChHandle[1];
    Udma_ChHandleInt    chHandle1Int = (Udma_ChHandleInt) chHandle1;
    Udma_ChPrms chParams;
    Udma_ChTxPrms txPrms;
    Udma_ChRxPrms rxPrms;
    Udma_ChUtcPrms utcPrms;
    Udma_DrvHandle drvHandle = &gUdmaDrvObj[CONFIG_UDMA0];
    Udma_ChHandle chHandle0 = gConfigUdma0BlkCopyChHandle[0];
    const Udma_ChPrms *chPrms;
    Udma_ChHandleInt    chHandle0Int = (Udma_ChHandleInt) chHandle0;
    Udma_DrvHandleInt   drvHandleInt = (Udma_DrvHandleInt) drvHandle;
    Udma_ChPdmaPrms pdmaPrms;
    Udma_ChStats chStats;
    Udma_RingObjectInt ringNum;
    uint64_t elerg_data;
    uint8_t phyrg_data;
    uint64_t *eleInRing = &elerg_data;
    uint8_t  *phyDescMem = &phyrg_data;
    Udma_UtcInstInfo   Info;
    uint8_t *chEnableStat;
    uint8_t chValue;
    DebugP_log("\r\n udma ch dynamic coverage test...\r\n");
    /* Passing valid parameters with de_init drvHandleInt->drvInitDone returns UDMA_EFAIL */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chOpen(drvHandle,chHandle0,chType,chPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init chHandle0Int->chInitDone returns UDMA_EBADARGS */
    chHandle0Int->chInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chClose(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init drvHandleInt->drvInitDone returns UDMA_EFAIL */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chClose(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with assigning true chHandle0Int->chOesAllocDone returns UDMA_EFAIL */
    chHandle0Int->chOesAllocDone = TRUE;
    retValue = Udma_chClose(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with assigning true chHandle0Int->chOesAllocDone returns UDMA_EFAIL */
    chHandle0Int->chOesAllocDone = FALSE;
    retValue = Udma_chClose(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to execute the Udma_chUnpair */
    chHandle0Int->chOesAllocDone = FALSE;
    chHandle0Int->chType = UDMA_CH_FLAG_UTC;
    retValue = Udma_chClose(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to execute the Udma_chUnpair */
    chHandle0Int->chOesAllocDone = FALSE;
    chHandle0Int->chType = UDMA_CH_FLAG_BLK_COPY;
    chHandle0Int->drvHandle->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    retValue = Udma_chClose(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to execute the Udma_chUnpair */
    chHandle0Int->chOesAllocDone = FALSE;
    chHandle0Int->chType = UDMA_CH_FLAG_TX;
    chHandle0Int->drvHandle->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    retValue = Udma_chClose(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init chHandle0Int->chInitDone returns UDMA_EBADARGS */
    chHandle0Int->chOesAllocDone = FALSE;
    chHandle0Int->chInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chEnable(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init drvHandleInt->drvInitDone returns UDMA_EFAIL */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chEnable(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passinf valid parameters to Udma_chEnable */
    chHandle0Int->drvHandle = drvHandleInt;
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    retValue = Udma_chEnable(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init chHandle0Int->chInitDone returns UDMA_EBADARGS */
    chHandle0Int->chInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chDisable(chHandle0,100U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init drvHandleInt->drvInitDone returns UDMA_EFAIL */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chDisable(chHandle0,100U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chDisable returns UDMA_ETIMEOUT */
    retValue = Udma_chDisable(chHandle0,100U);
    TEST_ASSERT_EQUAL_INT32(UDMA_ETIMEOUT, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init chHandle0Int->chInitDone to satisfy the condition */
    chHandle0Int->chInitDone = UDMA_DEINIT_DONE;
    Udma_chGetNum(chHandle0);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init drvHandleInt->drvInitDone to satisfy the condition */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    Udma_chGetNum(chHandle0);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chGetNum */
    Udma_chGetNum(chHandle0);
    udma_default_handle_params_init();
    /* Passing valid parameters with assigning UDMA_CH_FLAG_UTC to chHandle0Int->chType to unsatisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_UTC;
    Udma_chGetNum(chHandle0);
    udma_default_handle_params_init();
    /* Passing valid parameters with assigning UDMA_CH_FLAG_TX to chHandle0Int->chType to unsatisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_TX;
    Udma_chGetNum(chHandle0);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init drvHandleInt->drvInitDone to satisfy the condition */
    chHandle0Int->chInitDone = UDMA_DEINIT_DONE;
    Udma_chGetFqRingHandle(chHandle0);
    /* Passing valid parameters with init drvHandleInt->drvInitDone to unsatisfy the condition */
    Udma_chGetCqRingHandle(chHandle0);
    /* Passing valid parameters with init drvHandleInt->drvInitDone to unsatisfy the condition */
    Udma_chGetTdCqRingHandle(chHandle0);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init drvHandleInt->drvInitDone to satisfy the condition */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    Udma_chGetFqRingHandle(chHandle0);
    /* Passing valid parameters with de_init drvHandleInt->drvInitDone to satisfy the condition */
    Udma_chGetCqRingHandle(chHandle0);
    /* Passing valid parameters to Udma_chGetTdCqRingHandle to satisfy the condition */
    Udma_chGetTdCqRingHandle(chHandle0);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chGetFqRingHandle to satisfy the condition */
    Udma_chGetFqRingHandle(chHandle0);
    /* Passing valid parameters to Udma_chGetCqRingHandle to satisfy the condition */
    Udma_chGetCqRingHandle(chHandle0);
    /* Passing valid parameters to Udma_chGetTdCqRingHandle to satisfy the condition */
    Udma_chGetTdCqRingHandle(chHandle0);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chGetFqRingNum to satisfy the condition */
    Udma_chGetFqRingNum(chHandle0);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init chHandle0Int->chInitDone to satisfy the condition */
    chHandle0Int->chInitDone = UDMA_DEINIT_DONE;
    Udma_chGetDefaultFlowHandle(chHandle0);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init drvHandleInt->drvInitDone to satisfy the condition */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    Udma_chGetDefaultFlowHandle(chHandle0);
    udma_default_handle_params_init();
    /* Passing valid parameters to satisfy the condition */
    Udma_chGetDefaultFlowHandle(chHandle0);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init chHandle0Int->chInitDone to satisfy the condition */
    chHandle0Int->chInitDone = UDMA_DEINIT_DONE;
    Udma_chGetTriggerEvent(chHandle0,CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL1);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init drvHandleInt->drvInitDone to satisfy the condition */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    Udma_chGetTriggerEvent(chHandle0,CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL1);
    udma_default_handle_params_init();
    /* Passing valid parameters with assigning UDMA_CH_FLAG_BLK_COPY to chHandle0Int->chType to satisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_BLK_COPY;
    Udma_chGetTriggerEvent(chHandle0,CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL1);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chGetTriggerEvent to satisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_RX;
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    Udma_chGetTriggerEvent(chHandle0,CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL1);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chGetTriggerEvent to satisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_RX;
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    Udma_chGetTriggerEvent(chHandle0,CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL1);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chGetTriggerEvent to satisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_RX;
    Udma_chGetTriggerEvent(chHandle0,CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL1);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chGetTriggerEvent to satisfy the condition */
    Udma_chGetTriggerEvent(chHandle0,CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL1);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init chHandle0Int->chInitDone to satisfy the condition */
    chHandle0Int->chInitDone = UDMA_DEINIT_DONE;
    Udma_chGetSwTriggerRegister(chHandle0);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init drvHandleInt->drvInitDone to satisfy the condition */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    Udma_chGetSwTriggerRegister(chHandle0);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_BLK_COPY and UDMA_INST_TYPE_LCDMA_BCDMA to satisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_BLK_COPY;
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    Udma_chGetSwTriggerRegister(chHandle0);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_TX and UDMA_INST_TYPE_LCDMA_BCDMA to satisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_TX;
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    Udma_chGetSwTriggerRegister(chHandle0);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_BLK_COPY and UDMA_INST_TYPE_LCDMA_PKTDMA to satisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_BLK_COPY;
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    Udma_chGetSwTriggerRegister(chHandle0);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_BLK_COPY to satisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_BLK_COPY;
    Udma_chGetSwTriggerRegister(chHandle0);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_RX to satisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_RX;
    Udma_chGetSwTriggerRegister(chHandle0);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chGetSwTriggerRegister to satisfy the condition */
    Udma_chGetSwTriggerRegister(chHandle0);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init chHandle0Int->chInitDone returns UDMA_EBADARGS */
    chHandle0Int->chInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chSetSwTrigger(chHandle0,CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL1);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init drvHandleInt->drvInitDone returns UDMA_EFAIL */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chSetSwTrigger(chHandle0,CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL1);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_RX to execute the Udma_chGetSwTriggerRegister */
    chHandle0Int->chType = UDMA_CH_FLAG_RX;
    retValue = Udma_chSetSwTrigger(chHandle0,CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL1);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_UTC to execute the Udma_chSetSwTrigger */
    chHandle0Int->chType = UDMA_CH_FLAG_UTC;
    retValue = Udma_chSetSwTrigger(chHandle0,CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL1);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_TX to execute the Udma_chGetSwTriggerRegister */
    chHandle0Int->chType = UDMA_CH_FLAG_TX;
    retValue = Udma_chSetSwTrigger(chHandle0,CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL1);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chSetChaining to execute the Udma_chGetTriggerEvent */
    retValue = Udma_chSetChaining(chHandle0, chHandle1, CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chSetChaining to execute the Udma_chGetTriggerEvent */
    chHandle0Int->chInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chSetChaining(chHandle0, chHandle1, CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chSetChaining to execute the Udma_chGetTriggerEvent */
    chHandle1Int->chInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chSetChaining(chHandle0, chHandle1, CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chSetChaining to execute the Udma_chGetTriggerEvent */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chSetChaining(chHandle0, chHandle1, CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chSetChaining to execute the Udma_chGetTriggerEvent */
    chHandle0Int->chOesAllocDone = TRUE;
    retValue = Udma_chSetChaining(chHandle0, chHandle1, CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chSetChaining to execute the Udma_chGetTriggerEvent */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    retValue = Udma_chSetChaining(chHandle0, chHandle1, CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chSetChaining to execute the Udma_chGetTriggerEvent */
    chHandle0Int ->chType = UDMA_CH_FLAG_BLK_COPY;
    retValue = Udma_chSetChaining(chHandle0, chHandle1, CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chSetChaining to execute the Udma_chGetTriggerEvent */
    chHandle0Int ->chType = UDMA_CH_FLAG_RX;
    retValue = Udma_chSetChaining(chHandle0, chHandle1, CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chSetChaining to execute the Udma_chGetTriggerEvent */
    chHandle0Int ->chType = UDMA_CH_FLAG_TX;
    retValue = Udma_chSetChaining(chHandle0, chHandle1, CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with assigning true to chHandle0Int->chOesAllocDone to unsatisfy the condition */
    chHandle0Int->chOesAllocDone = TRUE;
    retValue = Udma_chBreakChaining(chHandle0,chHandle1);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init chHandle0Int->chInitDone returns UDMA_EBADARGS */
    chHandle0Int->chInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chBreakChaining(chHandle0,chHandle1);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init chHandle1Int->chInitDone returns UDMA_EBADARGS */
    chHandle1Int->chInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chBreakChaining(chHandle0,chHandle1);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init drvHandleInt->drvInitDone returns UDMA_EFAIL */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chBreakChaining(chHandle0,chHandle1);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with assigning false to chHandle0Int->chOesAllocDone to satisfy the condition */
    chHandle0Int->chOesAllocDone = FALSE;
    retValue = Udma_chBreakChaining(chHandle0,chHandle1);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_PKTDMA to execute the Udma_chGetTriggerEvent */
    chHandle0Int->chOesAllocDone = TRUE;
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    retValue = Udma_chBreakChaining(chHandle0,chHandle1);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_BLK_COPY to execute the Udma_chGetTriggerEvent */
    chHandle0Int->chOesAllocDone = TRUE;
    chHandle0Int ->chType = UDMA_CH_FLAG_BLK_COPY;
    retValue = Udma_chBreakChaining(chHandle0,chHandle1);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_RX to execute the Udma_chGetTriggerEvent */
    chHandle0Int->chOesAllocDone = TRUE;
    chHandle0Int ->chType = UDMA_CH_FLAG_RX;
    retValue = Udma_chBreakChaining(chHandle0,chHandle1);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_TX to execute the Udma_chGetTriggerEvent */
    chHandle0Int->chOesAllocDone = TRUE;
    chHandle0Int ->chType = UDMA_CH_FLAG_TX;
    retValue = Udma_chBreakChaining(chHandle0,chHandle1);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to execute the UdmaChPrms_init */
    chHandle0Int->chOesAllocDone = TRUE;
    UdmaChPrms_init(&chParams, UDMA_CH_TYPE_UTC);
    /* Passing valid parameters to execute the UdmaChTxPrms_init */
    UdmaChTxPrms_init(&txPrms,UDMA_CH_FLAG_UHC);
    /* Passing valid parameters to execute the UdmaChTxPrms_init */
    UdmaChTxPrms_init(&txPrms,UDMA_CH_FLAG_HC);
    /* Passing valid parameters to execute the UdmaChRxPrms_init */
    UdmaChRxPrms_init(&rxPrms,UDMA_CH_FLAG_UHC);
    /* Passing valid parameters to execute the UdmaChRxPrms_init */
    UdmaChRxPrms_init(&rxPrms,UDMA_CH_FLAG_HC);
    /* Passing valid parameters to execute the UdmaChPdmaPrms_init */
    UdmaChPdmaPrms_init(&pdmaPrms);
    /* Passing valid parameters to satisfy the condition */
    Udma_chGetStats(chHandle0, &chStats);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to satisfy the condition */
    chHandle0Int->chInitDone = UDMA_DEINIT_DONE;
    Udma_chGetStats(chHandle0, &chStats);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to satisfy the condition */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    Udma_chGetStats(chHandle0, &chStats);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to satisfy the condition */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    Udma_chGetStats(chHandle0, &chStats);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_BCDMA and UDMA_CH_FLAG_BLK_COPY to satisfy the condition */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_BLK_COPY;
    Udma_chGetStats(chHandle0, &chStats);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_BCDMA and UDMA_CH_FLAG_UTC to satisfy the condition */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_UTC;
    Udma_chGetStats(chHandle0, &chStats);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_BCDMA and UDMA_CH_FLAG_TX to satisfy the condition */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_TX;
    Udma_chGetStats(chHandle0, &chStats);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_BCDMA to satisfy the condition */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    Udma_chGetStats(chHandle0, &chStats);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_PKTDMA and UDMA_CH_FLAG_BLK_COPY to satisfy the condition */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_BLK_COPY;
    Udma_chGetStats(chHandle0, &chStats);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_PKTDMA and UDMA_CH_FLAG_UTC to satisfy the condition */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_UTC;
    Udma_chGetStats(chHandle0, &chStats);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_PKTDMA and UDMA_CH_FLAG_TX to satisfy the condition */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_TX;
    Udma_chGetStats(chHandle0, &chStats);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_PKTDMA to satisfy the condition */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    Udma_chGetStats(chHandle0, &chStats);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_getPeerData to satisfy the condition */
    retValue = Udma_getPeerData(chHandle0, &peerData);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_getPeerData with UDMA_CH_FLAG_PDMA to unsatisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_PDMA;
    retValue = Udma_getPeerData(chHandle0, &peerData);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init drvHandleInt->drvInitDone returns UDMA_EFAIL */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    chHandle0Int->chType = UDMA_CH_FLAG_PDMA;
    retValue = Udma_getPeerData(chHandle0, &peerData);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_PKTDMA to satisfy the condition */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    chHandle0Int->chType = ((uint32_t) 0x0009U);
    retValue = Udma_getPeerData(chHandle0, &peerData);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_PKTDMA and UDMA_CH_FLAG_PDMA to satisfy the condition */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_PDMA;
    retValue = Udma_getPeerData(chHandle0, &peerData);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_getPeerData to satisfy the condition */
    retValue = Udma_clearPeerData(chHandle0, peerData);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_getPeerData with UDMA_CH_FLAG_PDMA to unsatisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_PDMA;
    retValue = Udma_clearPeerData(chHandle0, peerData);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init drvHandleInt->drvInitDone returns UDMA_EFAIL */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    chHandle0Int->chType = UDMA_CH_FLAG_PDMA;
    retValue = Udma_clearPeerData(chHandle0, peerData);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_PKTDMA to satisfy the condition */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    chHandle0Int->chType =  ((uint32_t) 0x0009U);
    retValue = Udma_clearPeerData(chHandle0, peerData);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_PKTDMA and UDMA_CH_FLAG_PDMA to satisfy the condition */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_PDMA;
    retValue = Udma_clearPeerData(chHandle0, peerData);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_RX to satisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_RX;
    retValue = Udma_chConfigTx(chHandle0,&txPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_TX to unsatisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_TX;
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chConfigTx(chHandle0,&txPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_BCDMA to satisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_TX;
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    retValue = Udma_chConfigTx(chHandle0,&txPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_RX to unsatisfy the condition returns UDMA_EBADARGS */
    chHandle0Int->chType = UDMA_CH_FLAG_RX;
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    retValue = Udma_chConfigTx(chHandle0,&txPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chConfigTx to unsatisfy the condition */
    chHandle0Int->tdCqRing->ringNum = (uint16_t) 0;
    chHandle0Int->chType = UDMA_CH_FLAG_TX;
    retValue = Udma_chConfigTx(chHandle0,&txPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_TX to satisfy the condition returns UDMA_EBADARGS */
    chHandle0Int->chType = UDMA_CH_FLAG_TX;
    retValue = Udma_chConfigRx(chHandle0,&rxPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_RX to unsatisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_RX;
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chConfigRx(chHandle0,&rxPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parametrs to Udma_chConfigRx returns UDMA_EFAIL */
    chHandle0Int->chType = UDMA_CH_FLAG_RX;
    rxPrms.configDefaultFlow = TRUE;
    retValue = Udma_chConfigRx(chHandle0,&rxPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_RX to satisfy the condition returns UDMA_EBADARGS */
    chHandle0Int->chType = UDMA_CH_FLAG_RX;
    retValue = Udma_chConfigUtc(chHandle0,&utcPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_UTC and UDMA_DEINIT_DONE to unsatisfy the condition returns UDMA_EFAIL */
    chHandle0Int->chType = UDMA_CH_FLAG_UTC;
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chConfigUtc(chHandle0,&utcPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_UTC and CSL_DRU_OWNER_UDMAC_TR to unsatisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_UTC;
    utcPrms.druOwner = CSL_DRU_OWNER_UDMAC_TR;
    retValue = Udma_chConfigUtc(chHandle0,&utcPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_UTC and CSL_DRU_OWNER_UDMAC_TR to unsatisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_UTC;
    utcPrms.druOwner = CSL_DRU_OWNER_UDMAC_TR;
    chHandle0Int->tdCqRing = &ringNum;
    retValue = Udma_chConfigUtc(chHandle0,&utcPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_RX to satisfy the condition returns UDMA_EBADARGS */
    chHandle0Int->chType = UDMA_CH_FLAG_RX;
    retValue = Udma_chConfigPdma(chHandle0, &pdmaPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_PDMA and UDMA_DEINIT_DONE to unsatisfy the condition returns UDMA_EFAIL */
    chHandle0Int->chType = UDMA_CH_FLAG_PDMA;
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chConfigPdma(chHandle0, &pdmaPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_PDMA and UDMA_INST_TYPE_LCDMA_BCDMA to satisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_PDMA;
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    retValue = Udma_chConfigPdma(chHandle0, &pdmaPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_PDMA and UDMA_INST_TYPE_LCDMA_BCDMA to satisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_PDMA;
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    pdmaPrms.isAasrcCh = 1;
    retValue = Udma_chConfigPdma(chHandle0, &pdmaPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_PDMA and UDMA_INST_TYPE_LCDMA_PKTDMA to satisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_PDMA;
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    retValue = Udma_chConfigPdma(chHandle0, &pdmaPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_PDMA to satisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_PDMA;
    retValue = Udma_chConfigPdma(chHandle0, &pdmaPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_BCDMA to satisfy the condition */
    chHandle0Int->chType = ((uint32_t) 0x0009U);
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    retValue = Udma_chConfigPdma(chHandle0, &pdmaPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_PKTDMA to satisfy the condition */
    chHandle0Int->chType = ((uint32_t) 0x0009U);
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    retValue = Udma_chConfigPdma(chHandle0, &pdmaPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_BLK_COPY to execute the Udma_chDisableBlkCpyChan */
    chHandle0Int->chType = UDMA_CH_FLAG_BLK_COPY;
    retValue = Udma_chDisable(chHandle0,100U);
    TEST_ASSERT_EQUAL_INT32(UDMA_ETIMEOUT, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_UTC to execute the Udma_chDisableExtChan */
    chHandle0Int->chType = UDMA_CH_FLAG_UTC;
    retValue = Udma_chDisable(chHandle0,100U);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_TX to execute the Udma_chDisableTxChan */
    chHandle0Int->chType = UDMA_CH_FLAG_TX;
    retValue = Udma_chDisable(chHandle0,100U);
    TEST_ASSERT_EQUAL_INT32(UDMA_ETIMEOUT, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_TX to execute the Udma_chDisableTxChan */
    chHandle0Int->chType = UDMA_CH_FLAG_TX;
    chHandle0Int->drvHandle->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    retValue = Udma_chDisable(chHandle0,100U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_TX to execute the Udma_chDisableTxChan */
    chHandle0Int->chType = UDMA_CH_FLAG_TX;
    chHandle0Int->drvHandle->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    retValue = Udma_chDisable(chHandle0,100U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to execute the Udma_chDisableRxChan */
    chHandle0Int->drvHandle->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    retValue = Udma_chDisable(chHandle0,100U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to execute the Udma_chDisableRxChan */
    chHandle0Int->drvHandle->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    retValue = Udma_chDisable(chHandle0,100U);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to execute the Udma_chDisableRxChan */
    retValue = Udma_chDisable(chHandle0,100U);
    TEST_ASSERT_EQUAL_INT32(UDMA_ETIMEOUT, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with de-init chHandle0Int->chInitDone and returns UDMA_EBADARGS */
    chHandle0Int->chInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chPause(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with de-init drvHandleInt->drvInitDone and returns UDMA_EFAIL */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chPause(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_TX to execute the Udma_chDisableTxChan */
    chHandle0Int->chType = UDMA_CH_FLAG_TX;
    retValue = Udma_chPause(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_TX to execute the Udma_chDisableRxChan */
    chHandle0Int->chType = UDMA_CH_FLAG_RX;
    retValue = Udma_chPause(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_UTC to execute the Udma_chDisableExtChan */
    chHandle0Int->chType = UDMA_CH_FLAG_UTC;
    chHandle0Int->utcPrms.druOwner = CSL_DRU_OWNER_UDMAC_TR;
    retValue = Udma_chPause(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_UTC to execute the Udma_chDisableExtChan */
    chHandle0Int->chType = UDMA_CH_FLAG_UTC;
    chHandle0Int->utcPrms.druOwner = CSL_DRU_OWNER_DIRECT_TR;
    retValue = Udma_chPause(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_UTC to execute the Udma_chDisableExtChan */
    Udma_initDrvHandle(drvHandleInt);
    chHandle0Int->chType = UDMA_CH_FLAG_UTC;
    chHandle0Int->utcPrms.druOwner = CSL_DRU_OWNER_DIRECT_TR;
    retValue = Udma_chPause(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with de-init chHandle0Int->chInitDone and returns UDMA_EBADARGS */
    chHandle0Int->chInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chResume(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with de-init drvHandleInt->drvInitDone and returns UDMA_EFAIL */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chResume(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_TX to execute the Udma_chUnpauseTxLocal */
    chHandle0Int->chType = UDMA_CH_FLAG_TX;
    retValue = Udma_chResume(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_RX to satisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_RX;
    retValue = Udma_chResume(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_UTC to satisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_UTC;
    retValue = Udma_chResume(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_TX to execute the Udma_chUnpauseTxLocal */
    chHandle0Int->utcPrms.druOwner = CSL_DRU_OWNER_UDMAC_TR;
    chHandle0Int->chType = UDMA_CH_FLAG_UTC;
    retValue = Udma_chResume(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to UdmaChTxPrms_init to satisfy the condition */
    UdmaChTxPrms_init(&txPrms,UDMA_CH_FLAG_UHC);
    /* Passing valid parameters to UdmaChTxPrms_init to satisfy the condition */
    UdmaChTxPrms_init(&txPrms,UDMA_CH_FLAG_HC);
    /* Passing valid parameters with UDMA_UTC_ID_INVALID to execute the Udma_chCheckParams */
    chParams.utcId = UDMA_UTC_ID_INVALID;
    retValue = Udma_chOpen(drvHandle,chHandle0,UDMA_CH_FLAG_UTC, &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retValue);
    /* Passing valid parameters with UDMA_DMA_CH_NA to execute the Udma_chCheckParams */
    chParams.peerChNum = UDMA_DMA_CH_NA;
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_PDMA, &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retValue);
    /* Passing valid parameters with UDMA_MAPPED_GROUP_INVALID to execute the Udma_chCheckParams */
    chParams.mappedChGrp = UDMA_MAPPED_GROUP_INVALID;
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_MAPPED, &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retValue);
    /* Passing valid parameters with UDMA_NUM_MAPPED_TX_GROUP to execute the Udma_chCheckParams */
    chParams.mappedChGrp = UDMA_NUM_MAPPED_TX_GROUP;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0101U), &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retValue);
    /* Passing valid parameters with mappedChGrp to execute the Udma_chCheckParams */
    chParams.mappedChGrp = 10;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0102U), &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retValue);
    /* Passing valid parameters with NULL to execute the Udma_chCheckParams */
    chParams.utcId = 0U;
    chParams.peerChNum = 0U;
    chParams.mappedChGrp = 0U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0044U), &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to satisfy the condition */
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0084U), &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_DMA_CH_INVALID to execute the Udma_chAllocResource */
    chHandle0Int->extChNum = UDMA_DMA_CH_INVALID;
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_UTC , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_DMA_CH_INVALID to execute the Udma_chAllocResource */
    chHandle0Int->extChNum = 0U;
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_UTC , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_chAllocResource */
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0041U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_chAllocResource */
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0101U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_chAllocResource */
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0081U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_chAllocResource */
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0001U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_chAllocResource */
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_HC , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_chAllocResource */
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_MAPPED , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_chAllocResource */
    chHandle0Int->rxChNum = UDMA_DMA_CH_INVALID;
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_UHC , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to satisfy the condition */
    chHandle0Int->rxChNum = 0U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0200U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to satisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_PDMA;
    chHandle0Int->rxChNum = 0U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0200U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to satisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_PSIL;
    chHandle0Int->rxChNum = 0U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0200U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_BCDMA and UDMA_CH_FLAG_BLK_COPY to execute the Udma_chEnableLocal */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_BLK_COPY;
    retValue = Udma_chEnable(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_BCDMA and UDMA_CH_FLAG_TX to execute the Udma_chEnableLocal */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_TX;
    retValue = Udma_chEnable(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_BCDMA and UDMA_CH_FLAG_RX to execute the Udma_chEnableLocal */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_RX;
    retValue = Udma_chEnable(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_BCDMA to execute the Udma_chEnableLocal */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    retValue = Udma_chEnable(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_PKTDMA to execute the Udma_chEnableLocal */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    retValue = Udma_chEnable(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_UTC to execute the Udma_chEnableLocal */
    chHandle0Int->chType = UDMA_CH_FLAG_UTC;
    retValue = Udma_chEnable(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_PKTDMA and UDMA_CH_FLAG_TX to execute the Udma_chEnableLocal */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_TX;
    retValue = Udma_chEnable(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_PKTDMA and UDMA_CH_FLAG_RX to execute the Udma_chEnableLocal */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_RX;
    retValue = Udma_chEnable(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_BLK_COPY and UDMA_INST_TYPE_LCDMA_BCDMA to execute the Udma_chDisableBlkCpyChan */
    chHandle0Int->chType = UDMA_CH_FLAG_BLK_COPY;
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    retValue = Udma_chDisable(chHandle0,100U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_BLK_COPY and UDMA_INST_TYPE_LCDMA_PKTDMA to execute the Udma_chDisableBlkCpyChan */
    chHandle0Int->chType = UDMA_CH_FLAG_BLK_COPY;
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    retValue = Udma_chDisable(chHandle0,100U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_BLK_COPY to execute the Udma_chDisableBlkCpyChan */
    chHandle0Int->chType = UDMA_CH_FLAG_BLK_COPY;
    retValue = Udma_chDisable(chHandle0,5U);
    TEST_ASSERT_EQUAL_INT32(UDMA_ETIMEOUT, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init chHandle0Int->chInitDone returns UDMA_EBADARGS */
    chHandle0Int->chInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chReset(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init drvHandleInt->drvInitDone returns UDMA_EFAIL */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chReset(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_BCDMA and UDMA_CH_FLAG_BLK_COPY to satisfy the condition */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_BLK_COPY;
    retValue = Udma_chReset(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_BCDMA and UDMA_CH_FLAG_TX to satisfy the condition */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_TX;
    retValue = Udma_chReset(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_ETIMEOUT, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_BCDMA and UDMA_CH_FLAG_RX to satisfy the condition */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_RX;
    retValue = Udma_chReset(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_ETIMEOUT, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_BCDMA to satisfy the condition */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    retValue = Udma_chReset(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_BCDMA to satisfy the condition */
    retValue = Udma_chReset(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_BCDMA and UDMA_CH_FLAG_RX to satisfy the condition */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_RX;
    retValue = Udma_chResume(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_PKTDMA and UDMA_CH_FLAG_RX to satisfy the condition */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_RX;
    retValue = Udma_chResume(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_BCDMA and UDMA_CH_FLAG_TX to satisfy the condition */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_TX;
    retValue = Udma_chResume(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_PKTDMA and UDMA_CH_FLAG_TX to execute the Udma_chUnpauseTxLocal */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_TX;
    retValue = Udma_chResume(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_BCDMA and UDMA_CH_FLAG_RX to satisfy the condition */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_RX;
    retValue = Udma_chPause(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_BCDMA and UDMA_CH_FLAG_RX to satisfy the condition */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_RX;
    retValue = Udma_chPause(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_BCDMA and UDMA_CH_FLAG_TX to execute the Udma_chPauseTxLocal */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_TX;
    retValue = Udma_chPause(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_PKTDMA and UDMA_CH_FLAG_TX to execute the Udma_chPauseTxLocal */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_TX;
    retValue = Udma_chPause(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_BCDMA,CSL_DRU_OWNER_UDMAC_TR and UDMA_CH_FLAG_UTC to execute the Udma_chUnpauseTxLocal */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    chHandle0Int->utcPrms.druOwner = CSL_DRU_OWNER_UDMAC_TR;
    chHandle0Int->chType = UDMA_CH_FLAG_UTC;
    retValue = Udma_chResume(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_PKTDMA,CSL_DRU_OWNER_UDMAC_TR and UDMA_CH_FLAG_UTC to execute the Udma_chUnpauseTxLocal */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    chHandle0Int->utcPrms.druOwner = CSL_DRU_OWNER_UDMAC_TR;
    chHandle0Int->chType = UDMA_CH_FLAG_UTC;
    retValue = Udma_chResume(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_BCDMA,CSL_DRU_OWNER_DIRECT_TR and UDMA_CH_FLAG_UTC to execute the CSL_druChPause */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_UTC;
    chHandle0Int->utcPrms.druOwner = CSL_DRU_OWNER_DIRECT_TR;
    retValue = Udma_chPause(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /*Passing valid parameters with UDMA_INST_TYPE_LCDMA_PKTDMA,CSL_DRU_OWNER_DIRECT_TR and UDMA_CH_FLAG_UTC to execute the CSL_druChPause */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_UTC;
    chHandle0Int->utcPrms.druOwner = CSL_DRU_OWNER_DIRECT_TR;
    retValue = Udma_chPause(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to satisfy the condition */
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_UHC , NULL_PTR);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init drvHandleInt->drvInitDone returns UDMA_EFAIL */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_UHC , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init drvHandleInt->drvInitDone returns UDMA_EFAIL */
    chHandle0Int->tdCqRing = &ringNum;
    chHandle0Int->chType = UDMA_CH_FLAG_TX;
    retValue = Udma_chConfigTx(chHandle0,&txPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with de_init drvHandleInt->drvInitDone returns UDMA_EFAIL */
    chHandle0Int->tdCqRing = &ringNum;
    chHandle0Int->chType =  ((uint32_t) 0x0006U);
    retValue = Udma_chConfigRx(chHandle0,&rxPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chConfigRx to satisfy the condition */
    chHandle0Int->chType =  ((uint32_t) 0x001FU);
    rxPrms.configDefaultFlow = TRUE;
    retValue = Udma_chConfigRx(chHandle0,&rxPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chConfigRx to satisfy the condition */
    chHandle0Int->cqRing = &ringNum;
    chHandle0Int->fqRing = &ringNum;
    chHandle0Int->chType =  ((uint32_t) 0x001FU);
    rxPrms.configDefaultFlow = TRUE;
    retValue = Udma_chConfigRx(chHandle0,&rxPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chPause to satisfy the condition */
    chHandle0Int->chType = ((uint32_t) 0x0006U);
    chHandle0Int->drvHandle->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    retValue = Udma_chPause(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chPause to satisfy the condition */
    chHandle0Int->chType = ((uint32_t) 0x0006U);
    chHandle0Int->drvHandle->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    retValue = Udma_chResume(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chPause to satisfy the condition */
    chHandle0Int->cqRing = &ringNum;
    Udma_chGetFqRingNum(chHandle0);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chPause to satisfy the condition */
    retValue = Udma_chSetChaining(chHandle0, chHandle1, ((uint32_t) 3U));
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chBreakChaining to satisfy the condition */
    chHandle0Int->chOesAllocDone = TRUE;
    chHandle0Int->trigger = ((uint32_t) 3U);
    retValue = Udma_chBreakChaining(chHandle0, chHandle1);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to satisfy the condition */
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_PDMA , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to satisfy the condition */
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_PSIL , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chClose to satisfy the condition */
    chHandle0Int -> txChNum = 0U;
    chHandle0Int -> chType  = ((uint32_t) 0x0044U);
    retValue = Udma_chClose(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to Udma_chOpen to satisfy the condition */
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_PDMA , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chClose to satisfy the condition */
    chHandle0Int -> txChNum = 0U;
    chHandle0Int -> chType  = ((uint32_t) 0x0084U);
    retValue = Udma_chClose(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to Udma_chOpen to satisfy the condition */
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_PDMA , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chClose to satisfy the condition */
    chHandle0Int -> txChNum = 0U;
    chHandle0Int -> chType  = UDMA_CH_FLAG_BLK_COPY;
    retValue = Udma_chClose(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to satisfy the condition */
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_PDMA , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocBlkCopyCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startBlkCopyCh = 1U;
    chHandle0Int->drvHandle->rmInitPrms.numBlkCopyCh = 3U;
    chHandle0Int->drvHandle->blkCopyChFlag[0] = 2U;
    chHandle0Int->txChNum = 0U;
    chHandle0Int->drvHandle->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_BLK_COPY , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocBlkCopyCh */
    chParams.chNum = UDMA_DMA_CH_ANY;
    chHandle0Int->drvHandle->rmInitPrms.numBlkCopyCh = 0U;
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_BLK_COPY, &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocBlkCopyCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startBlkCopyCh = 3U;
    chHandle0Int->drvHandle->rmInitPrms.numBlkCopyCh = 3U;
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_BLK_COPY , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocBlkCopyCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startBlkCopyCh = 0U;
    chHandle0Int->drvHandle->rmInitPrms.numBlkCopyCh = 0U;
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_BLK_COPY , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocBlkCopyCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startBlkCopyCh = 1U;
    chHandle0Int->drvHandle->rmInitPrms.numBlkCopyCh = 3U;
    chHandle0Int->drvHandle->blkCopyChFlag[0] = 5U;
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_BLK_COPY , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocBlkCopyHcCh */
    chParams.chNum = UDMA_DMA_CH_ANY;
    chHandle0Int->drvHandle->blkCopyHcChFlag[0] = 0U;
    chHandle0Int->drvHandle->rmInitPrms.numBlkCopyHcCh = 3U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0044U), &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocBlkCopyHcCh */
    chParams.chNum = UDMA_DMA_CH_ANY;
    chHandle0Int->drvHandle->blkCopyHcChFlag[0] = 1U;
    chHandle0Int->drvHandle->rmInitPrms.numBlkCopyHcCh = 3U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0044U), &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocBlkCopyHcCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startBlkCopyHcCh = 1U;
    chHandle0Int->drvHandle->rmInitPrms.numBlkCopyHcCh = 3U;
    chHandle0Int->drvHandle->blkCopyHcChFlag[0] = 2U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0044U), &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocBlkCopyHcCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startBlkCopyHcCh = 3U;
    chHandle0Int->drvHandle->rmInitPrms.numBlkCopyHcCh = 3U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0044U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocBlkCopyHcCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startBlkCopyHcCh = 0U;
    chHandle0Int->drvHandle->rmInitPrms.numBlkCopyHcCh = 0U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0044U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocBlkCopyHcCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startBlkCopyHcCh = 1U;
    chHandle0Int->drvHandle->rmInitPrms.numBlkCopyHcCh = 3U;
    chHandle0Int->drvHandle->blkCopyHcChFlag[0] = 5U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0044U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocBlkCopyUhcCh */
    chParams.chNum = UDMA_DMA_CH_ANY;
    chHandle0Int->drvHandle->blkCopyUhcChFlag[0] = 0U;
    chHandle0Int->drvHandle->rmInitPrms.numBlkCopyUhcCh = 3U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0084U), &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocBlkCopyUhcCh */
    chParams.chNum = UDMA_DMA_CH_ANY;
    chHandle0Int->drvHandle->blkCopyUhcChFlag[0] = 1U;
    chHandle0Int->drvHandle->rmInitPrms.numBlkCopyUhcCh = 3U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0084U), &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocBlkCopyUhcCh */
    chParams.chNum = 2;
    chHandle0Int->drvHandle->rmInitPrms.startBlkCopyUhcCh = 1U;
    chHandle0Int->drvHandle->rmInitPrms.numBlkCopyUhcCh = 3U;
    chHandle0Int->drvHandle->blkCopyUhcChFlag[0] = 2U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0084U), &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocBlkCopyUhcCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startBlkCopyUhcCh = 3U;
    chHandle0Int->drvHandle->rmInitPrms.numBlkCopyUhcCh = 3U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0084U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocBlkCopyUhcCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startBlkCopyUhcCh = 0U;
    chHandle0Int->drvHandle->rmInitPrms.numBlkCopyUhcCh = 0U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0084U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocBlkCopyUhcCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startBlkCopyUhcCh = 1U;
    chHandle0Int->drvHandle->rmInitPrms.numBlkCopyUhcCh = 3U;
    chHandle0Int->drvHandle->blkCopyUhcChFlag[0] = 5U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0084U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocTxCh */
    chParams.chNum = UDMA_DMA_CH_ANY;
    chHandle0Int->drvHandle->txChFlag[0] = 0U;
    chHandle0Int->drvHandle->rmInitPrms.numTxCh = 2U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0001U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocTxCh */
    chParams.chNum = UDMA_DMA_CH_ANY;
    chHandle0Int->drvHandle->txChFlag[0] = 1U;
    chHandle0Int->drvHandle->rmInitPrms.numTxCh = 2U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0001U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocTxCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startTxCh = 1U;
    chHandle0Int->drvHandle->rmInitPrms.numTxCh = 3U;
    chHandle0Int->drvHandle->txChFlag[0] = 2U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0001U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocTxCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startTxCh = 3U;
    chHandle0Int->drvHandle->rmInitPrms.numTxCh = 3U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0001U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocTxCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startTxCh = 0U;
    chHandle0Int->drvHandle->rmInitPrms.numTxCh = 0U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0001U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocTxCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startTxCh = 1U;
    chHandle0Int->drvHandle->rmInitPrms.numTxCh = 3U;
    chHandle0Int->drvHandle->txChFlag[0] = 5U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0001U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocRxCh */
    chParams.chNum = UDMA_DMA_CH_ANY;
    chHandle0Int->drvHandle->rxChFlag[0] = 0U;
    chHandle0Int->drvHandle->rmInitPrms.numRxCh = 2U;
    chHandle0Int->rxChNum = 0U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0200U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocRxCh */
    chParams.chNum = UDMA_DMA_CH_ANY;
    chHandle0Int->drvHandle->rxChFlag[0] = 1U;
    chHandle0Int->drvHandle->rmInitPrms.numRxCh = 2U;
    chHandle0Int->rxChNum = 0U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0200U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocRxCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startRxCh = 1U;
    chHandle0Int->drvHandle->rmInitPrms.numRxCh = 3U;
    chHandle0Int->drvHandle->rxChFlag[0] = 2U;
    chHandle0Int->rxChNum = 0U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0200U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocRxCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startRxCh = 3U;
    chHandle0Int->drvHandle->rmInitPrms.numRxCh = 3U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0200U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocRxCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startRxCh = 0U;
    chHandle0Int->drvHandle->rmInitPrms.numRxCh = 0U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0200U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocRxCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startRxCh = 1U;
    chHandle0Int->drvHandle->rmInitPrms.numRxCh = 3U;
    chHandle0Int->drvHandle->rxChFlag[0] = 5U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0200U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocTxHcCh */
    chParams.chNum = UDMA_DMA_CH_ANY;
    chHandle0Int->drvHandle->txHcChFlag[0] = 0U;
    chHandle0Int->drvHandle->rmInitPrms.numTxHcCh = 2U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0041U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocTxHcCh */
    chParams.chNum = UDMA_DMA_CH_ANY;
    chHandle0Int->drvHandle->txHcChFlag[0] = 1U;
    chHandle0Int->drvHandle->rmInitPrms.numTxHcCh = 2U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0041U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocTxHcCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startTxHcCh = 1U;
    chHandle0Int->drvHandle->rmInitPrms.numTxHcCh = 3U;
    chHandle0Int->drvHandle->txHcChFlag[0] = 2U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0041U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocTxHcCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startTxHcCh = 3U;
    chHandle0Int->drvHandle->rmInitPrms.numTxHcCh = 3U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0041U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocTxHcCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startTxHcCh = 0U;
    chHandle0Int->drvHandle->rmInitPrms.numTxHcCh = 0U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0041U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocTxHcCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startTxHcCh = 1U;
    chHandle0Int->drvHandle->rmInitPrms.numTxHcCh = 3U;
    chHandle0Int->drvHandle->txHcChFlag[0] = 5U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0041U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocRxHcCh */
    chParams.chNum = UDMA_DMA_CH_ANY;
    chHandle0Int->drvHandle->rxHcChFlag[0] = 0U;
    chHandle0Int->drvHandle->rmInitPrms.numRxHcCh = 2U;
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_HC , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocRxHcCh */
    chParams.chNum = UDMA_DMA_CH_ANY;
    chHandle0Int->drvHandle->rxHcChFlag[0] = 1U;
    chHandle0Int->drvHandle->rmInitPrms.numRxHcCh = 2U;
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_HC , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocRxHcCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startRxHcCh = 1U;
    chHandle0Int->drvHandle->rmInitPrms.numRxHcCh = 3U;
    chHandle0Int->drvHandle->rxHcChFlag[0] = 2U;
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_HC , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocRxHcCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startRxHcCh = 3U;
    chHandle0Int->drvHandle->rmInitPrms.numRxHcCh = 3U;
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_HC , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocRxHcCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startRxHcCh = 0U;
    chHandle0Int->drvHandle->rmInitPrms.numRxHcCh = 0U;
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_HC , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocRxHcCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startRxHcCh = 1U;
    chHandle0Int->drvHandle->rmInitPrms.numRxHcCh = 3U;
    chHandle0Int->drvHandle->rxHcChFlag[0] = 5U;
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_HC , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocTxUhcCh */
    chParams.chNum = UDMA_DMA_CH_ANY;
    chHandle0Int->drvHandle->txUhcChFlag[0] = 0U;
    chHandle0Int->drvHandle->rmInitPrms.numTxUhcCh = 2U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0081U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocTxUhcCh */
    chParams.chNum = UDMA_DMA_CH_ANY;
    chHandle0Int->drvHandle->txUhcChFlag[0] = 1U;
    chHandle0Int->drvHandle->rmInitPrms.numTxUhcCh = 2U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0081U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocTxUhcCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startTxUhcCh = 1U;
    chHandle0Int->drvHandle->rmInitPrms.numTxUhcCh = 3U;
    chHandle0Int->drvHandle->txUhcChFlag[0] = 2U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0081U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocTxUhcCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startTxUhcCh = 3U;
    chHandle0Int->drvHandle->rmInitPrms.numTxUhcCh = 3U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0081U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocTxUhcCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startTxUhcCh = 0U;
    chHandle0Int->drvHandle->rmInitPrms.numTxUhcCh = 0U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0081U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocTxUhcCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startTxUhcCh = 1U;
    chHandle0Int->drvHandle->rmInitPrms.numTxUhcCh = 3U;
    chHandle0Int->drvHandle->txUhcChFlag[0] = 5U;
    retValue = Udma_chOpen(drvHandle,chHandle0, ((uint32_t) 0x0081U) , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocRxUhcCh */
    chParams.chNum = UDMA_DMA_CH_ANY;
    chHandle0Int->drvHandle->rxUhcChFlag[0] = 0U;
    chHandle0Int->drvHandle->rmInitPrms.numRxUhcCh = 2U;
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_UHC , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocRxUhcCh */
    chParams.chNum = UDMA_DMA_CH_ANY;
    chHandle0Int->drvHandle->rxUhcChFlag[0] = 1U;
    chHandle0Int->drvHandle->rmInitPrms.numRxUhcCh = 2U;
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_UHC , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocRxUhcCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startRxUhcCh = 1U;
    chHandle0Int->drvHandle->rmInitPrms.numRxUhcCh = 3U;
    chHandle0Int->drvHandle->rxUhcChFlag[0] = 2U;
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_UHC , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocRxUhcCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startRxUhcCh = 3U;
    chHandle0Int->drvHandle->rmInitPrms.numRxUhcCh = 3U;
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_UHC , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocRxUhcCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startRxUhcCh = 0U;
    chHandle0Int->drvHandle->rmInitPrms.numRxUhcCh = 0U;
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_UHC , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chOpen to execute the Udma_rmAllocRxUhcCh */
    chParams.chNum = 2U;
    chHandle0Int->drvHandle->rmInitPrms.startRxUhcCh = 1U;
    chHandle0Int->drvHandle->rmInitPrms.numRxUhcCh = 3U;
    chHandle0Int->drvHandle->rxUhcChFlag[0] = 5U;
    retValue = Udma_chOpen(drvHandle,chHandle0, UDMA_CH_FLAG_UHC , &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chRingDeQueueRaw to satisfy the condition */
    chHandle0Int->drvHandle = (Udma_DrvHandleInt) drvHandle;
    chHandle0Int->utcInfo = &Info;
    retValue = Udma_chRingDeQueueRaw(chHandle0, 2, eleInRing);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing valid parameters to Udma_chRingDeQueueRaw to satisfy the condition */
    chHandle0Int->drvHandle = (Udma_DrvHandleInt) drvHandle;
    retValue = Udma_chRingQueueRaw(chHandle0,phyDescMem,2);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters to Udma_chReset to satisfy the condition */
    chHandle0Int->chInitDone = UDMA_INIT_DONE;
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    chHandle0Int->chType = UDMA_CH_FLAG_TX;
    retValue = Udma_chReset(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing NULL parameters to Udma_chGetChanEnStatus returns UDMA_EBADARGS */
    retValue = Udma_chGetChanEnStatus(NULL,NULL_PTR);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with de_init chHandle0Int->chInitDone to satisfy the condition */
    chEnableStat = &chValue;
    chHandle0Int->chInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chGetChanEnStatus(chHandle0,chEnableStat);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing NULL parameters to chHandle0Int->drvHandle returns UDMA_EFAIL */
    chHandle0Int->chInitDone = UDMA_INIT_DONE;
    chHandle0Int->drvHandle = NULL_PTR;
    retValue = Udma_chGetChanEnStatus(chHandle0,chEnableStat);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters with de_init drvHandleInt->drvInitDone returns UDMA_EFAIL */
    chHandle0Int->drvHandle = gConfigUdma0BlkCopyChHandle[1];
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chGetChanEnStatus(chHandle0,chEnableStat);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters with UDMA_CH_FLAG_BLK_COPY and UDMA_DMA_CH_INVALID to satisfy the condition */
    chHandle0Int->drvHandle->drvInitDone = UDMA_INIT_DONE;
    chHandle0Int->drvHandle->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_BLK_COPY;
    chHandle0Int->txChNum = UDMA_DMA_CH_INVALID;
    retValue = Udma_chGetChanEnStatus(chHandle0,chEnableStat);
    TEST_ASSERT_EQUAL_INT32(-65536, retValue);
    /* Passing valid parameters with UDMA_DMA_CH_ANY to execute the CSL_bcdmaChanOp */
    chHandle0Int->txChNum = UDMA_DMA_CH_ANY;
    retValue = Udma_chGetChanEnStatus(chHandle0,chEnableStat);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with UDMA_CH_FLAG_TX and UDMA_DMA_CH_INVALID to satisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_TX;
    chHandle0Int->txChNum = UDMA_DMA_CH_INVALID;
    retValue = Udma_chGetChanEnStatus(chHandle0,chEnableStat);
    TEST_ASSERT_EQUAL_INT32(-65536, retValue);
    /* Passing valid parameters with UDMA_DMA_CH_ANY to execute the CSL_bcdmaChanOp */
    chHandle0Int->txChNum = UDMA_DMA_CH_ANY;
    retValue = Udma_chGetChanEnStatus(chHandle0,chEnableStat);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with UDMA_CH_FLAG_RX and UDMA_DMA_CH_INVALID to satisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_RX;
    chHandle0Int->rxChNum = UDMA_DMA_CH_INVALID;
    retValue = Udma_chGetChanEnStatus(chHandle0,chEnableStat);
    TEST_ASSERT_EQUAL_INT32(-65536, retValue);
    /* Passing valid parameters with UDMA_DMA_CH_ANY to execute the CSL_bcdmaChanOp */
    chHandle0Int->rxChNum = 0;
    retValue = Udma_chGetChanEnStatus(chHandle0,chEnableStat);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing valid parameters with zero value to chHandle0Int->chType to satisfy the condition */
    chHandle0Int->chType = 0;
    retValue = Udma_chGetChanEnStatus(chHandle0,chEnableStat);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with UDMA_CH_FLAG_TX and UDMA_DMA_CH_INVALID to satisfy the condition */
    chHandle0Int->drvHandle->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    chHandle0Int->chType = UDMA_CH_FLAG_TX;
    chHandle0Int->txChNum = UDMA_DMA_CH_INVALID;
    retValue = Udma_chGetChanEnStatus(chHandle0,chEnableStat);
    TEST_ASSERT_EQUAL_INT32(-65536, retValue);
    /* Passing valid parameters with UDMA_DMA_CH_ANY to execute the CSL_pktdmaGetTxRT */
    chHandle0Int->txChNum = UDMA_DMA_CH_ANY;
    retValue = Udma_chGetChanEnStatus(chHandle0,chEnableStat);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing valid parameters with UDMA_CH_FLAG_RX and UDMA_DMA_CH_INVALID to satisfy the condition */
    chHandle0Int->chType = UDMA_CH_FLAG_RX;
    chHandle0Int->rxChNum = UDMA_DMA_CH_INVALID;
    retValue = Udma_chGetChanEnStatus(chHandle0,chEnableStat);
    TEST_ASSERT_EQUAL_INT32(-65536, retValue);
    /* Passing valid parameters with zero value to chHandle0Int->rxChNum to execute the CSL_pktdmaGetRxRT */
    chHandle0Int->rxChNum = 0;
    retValue = Udma_chGetChanEnStatus(chHandle0,chEnableStat);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing valid parameters with zero value to chHandle0Int->chType to satisfy the condition */
    chHandle0Int->chType = 0;
    retValue = Udma_chGetChanEnStatus(chHandle0,chEnableStat);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters to Udma_chGetChanEnStatus to satisfy the condition */
    chHandle0Int->drvHandle->instType = 0;
    retValue = Udma_chGetChanEnStatus(chHandle0,chEnableStat);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    udma_default_handle_params_init();
    /* Passing NULL value to Udma_chDecStats satisfy the condition and return UDMA_EBADARGS */
    retValue = Udma_chDecStats(NULL,NULL_PTR );
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with de_init chHandle0Int->chInitDone to satisfy the condition */
    chHandle1Int->chInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chDecStats(chHandle1,NULL_PTR );
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing NULL_PTR value to Udma_chDecStats satisfy the condition and return UDMA_EBADARGS */
    chHandle1Int->chInitDone = UDMA_INIT_DONE;
    retValue = Udma_chDecStats(chHandle1,NULL_PTR );
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with NULL_PTR chHandle1Int->drvHandle satisfy the condition */
    chHandle1Int->chInitDone = UDMA_INIT_DONE;
    chHandle1Int->drvHandle =  NULL_PTR;
    retValue = Udma_chDecStats(chHandle1,&chStats);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters with de_init drvHandleInt->drvInitDone returns UDMA_EFAIL */
    chHandle1Int->drvHandle = gConfigUdma0BlkCopyChHandle[0];
    chHandle1Int->drvHandle->drvInitDone =  UDMA_DEINIT_DONE;
    retValue = Udma_chDecStats(chHandle1,&chStats);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_BCDMA and UDMA_CH_FLAG_BLK_COPY to satisfy the condition */
    chHandle1Int->drvHandle = gConfigUdma0BlkCopyChHandle[0];
    chHandle1Int->drvHandle->drvInitDone =  UDMA_INIT_DONE;
    chHandle1Int->drvHandle->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    chHandle1Int->chType = UDMA_CH_FLAG_BLK_COPY;
    chHandle1Int->txChNum = 0;
    retValue = Udma_chDecStats(chHandle1,&chStats);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_BCDMA and UDMA_CH_FLAG_UTC to satisfy the condition */
    chHandle1Int->chType = UDMA_CH_FLAG_UTC;
    retValue = Udma_chDecStats(chHandle1,&chStats);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_BCDMA and UDMA_CH_FLAG_TX to satisfy the condition */
    chHandle1Int->chType = UDMA_CH_FLAG_TX;
    retValue = Udma_chDecStats(chHandle1,&chStats);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing valid parameters with 0 to chHandle1Int->chType unsatisfy the condition */
    chHandle1Int->chType = 0;
    retValue = Udma_chDecStats(chHandle1,&chStats);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_PKTDMA and UDMA_CH_FLAG_BLK_COPY to satisfy the condition */
    chHandle1Int->drvHandle->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    chHandle1Int->chType = UDMA_CH_FLAG_BLK_COPY;
    retValue = Udma_chDecStats(chHandle1,&chStats);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_PKTDMA and UDMA_CH_FLAG_UTC to satisfy the condition */
    chHandle1Int->chType = UDMA_CH_FLAG_UTC;
    retValue = Udma_chDecStats(chHandle1,&chStats);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_PKTDMA and UDMA_CH_FLAG_TX to satisfy the condition */
    chHandle1Int->chType = UDMA_CH_FLAG_TX;
    retValue = Udma_chDecStats(chHandle1,&chStats);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing valid parameters with 0 to chHandle1Int->drvHandle->instType unsatisfy the condition */
    chHandle1Int->drvHandle->instType = 0;
    retValue = Udma_chDecStats(chHandle1,&chStats);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing valid parameters with 0 to chHandle0Int->chType and chParams.utcId execute the Udma_chGetUtcInst */
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    chHandle0Int->chType = UDMA_CH_FLAG_UTC;
    chParams.utcId = 2;
    retValue = Udma_chOpen(drvHandle,chHandle0,0,&chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    /* Passing NULL value to Udma_chOpen returns UDMA_EBADARGS */
    retValue = Udma_chOpen(NULL,chHandle0,0,&chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing NULL value to Udma_chOpen returns UDMA_EBADARGS */
    retValue = Udma_chOpen(drvHandle,NULL,0,&chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing NULL value to Udma_chClose returns UDMA_EBADARGS */
    retValue = Udma_chClose(NULL_PTR);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with NULL_PTR to chHandle0Int->drvHandle to satisfy the condition */
    chHandle0Int->chInitDone = UDMA_INIT_DONE;
    chHandle0Int->drvHandle = NULL_PTR;
    retValue = Udma_chClose(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing NULL value to Udma_chClose returns UDMA_EBADARGS */
    retValue = Udma_chConfigTx(NULL_PTR,&txPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with de_init chHandle0Int->chInitDone to satisfy the condition */
    chHandle0Int->chInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chConfigTx(chHandle0,&txPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with NULL_PTR to chHandle0Int->drvHandle to satisfy the condition */
    chHandle0Int->chInitDone = UDMA_INIT_DONE;
    chHandle0Int->chType = UDMA_CH_FLAG_TX;
    chHandle0Int->drvHandle = NULL_PTR;
    retValue = Udma_chConfigTx(chHandle0,&txPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters with UDMA_CH_FLAG_TX to chHandle0Int->chType returns UDMA_EBADARGS */
    retValue = Udma_chConfigRx(chHandle0,&rxPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with de_init chHandle0Int->chInitDone to satisfy the condition */
    chHandle0Int->chInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chConfigRx(chHandle0,&rxPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with NULL_PTR to chHandle0Int->drvHandle to satisfy the condition */
    chHandle0Int->chInitDone = UDMA_INIT_DONE;
    chHandle0Int->chType = UDMA_CH_FLAG_RX;
    chHandle0Int->drvHandle = NULL_PTR;
    retValue = Udma_chConfigRx(chHandle0,&rxPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing NULL value to Udma_chConfigUtc to satisfy the condition */
    retValue = Udma_chConfigUtc(NULL,&utcPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with de_init chHandle0Int->chInitDone to satisfy the condition */
    chHandle0Int->chInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chConfigUtc(NULL,&utcPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with NULL_PTR to chHandle0Int->drvHandle to satisfy the condition */
    chHandle0Int->chInitDone = UDMA_INIT_DONE;
    chHandle0Int->chType = UDMA_CH_FLAG_UTC;
    chHandle0Int->drvHandle = NULL_PTR;
    retValue = Udma_chConfigUtc(chHandle0,&utcPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters with UDMA_UTC_TYPE_DRU to satisfy the condition */
    chHandle0Int->drvHandle = (Udma_DrvHandleInt) drvHandle;
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    utcPrms.druOwner = CSL_DRU_OWNER_DIRECT_TR;
    chHandle0Int->utcInfo = &Info;
    Info.utcType = UDMA_UTC_TYPE_DRU;
    retValue = Udma_chConfigUtc(chHandle0,&utcPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters with UDMA_UTC_TYPE_DRU_VHWA to satisfy the condition */
    chHandle0Int->drvHandle = (Udma_DrvHandleInt) drvHandle;
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    utcPrms.druOwner = CSL_DRU_OWNER_DIRECT_TR;
    chHandle0Int->utcInfo = &Info;
    Info.utcType = UDMA_UTC_TYPE_DRU_VHWA;
    retValue = Udma_chConfigUtc(chHandle0,&utcPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters with UDMA_DEFAULT_UTC_CH_BUS_PRIORITY to unsatisfy the condition */
    chHandle0Int->drvHandle = (Udma_DrvHandleInt) drvHandle;
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    utcPrms.druOwner = CSL_DRU_OWNER_DIRECT_TR;
    Info.utcType = UDMA_DEFAULT_UTC_CH_BUS_PRIORITY;
    retValue = Udma_chConfigUtc(chHandle0,&utcPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing NULL value to Udma_chConfigPdma returns UDMA_EBADARGS */
    retValue = Udma_chConfigPdma(NULL_PTR,&pdmaPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing NULL value to Udma_chConfigPdma returns UDMA_EBADARGS */
    retValue = Udma_chConfigPdma(chHandle0,NULL_PTR);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with de_init chHandle0Int->chInitDone to satisfy the condition */
    chHandle0Int->chInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_chConfigPdma(chHandle0,&pdmaPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with NULL_PTR to chHandle0Int->drvHandle to satisfy the condition */
    chHandle0Int->chInitDone = UDMA_INIT_DONE;
    chHandle0Int->drvHandle = NULL_PTR;
    chHandle0Int->chType = UDMA_CH_FLAG_PDMA;
    retValue = Udma_chConfigPdma(chHandle0,&pdmaPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing NULL value to Udma_chEnable returns UDMA_EBADARGS */
    retValue = Udma_chEnable(NULL_PTR);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with NULL_PTR to chHandle0Int->drvHandle to satisfy the condition */
    chHandle0Int->chInitDone = UDMA_INIT_DONE;
    chHandle0Int->drvHandle = NULL_PTR;
    retValue = Udma_chEnable(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing NULL value to Udma_chDisable returns UDMA_EBADARGS */
    retValue = Udma_chDisable(NULL_PTR,100U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with NULL_PTR to chHandle0Int->drvHandle to satisfy the condition */
    chHandle0Int->chInitDone = UDMA_INIT_DONE;
    chHandle0Int->drvHandle = NULL_PTR;
    retValue = Udma_chDisable(chHandle0,100U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing NULL value to Udma_chPause returns UDMA_EBADARGS */
    retValue = Udma_chPause(NULL_PTR);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with NULL_PTR to chHandle0Int->drvHandle to satisfy the condition */
    chHandle0Int->chInitDone = UDMA_INIT_DONE;
    chHandle0Int->drvHandle = NULL_PTR;
    retValue = Udma_chPause(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing NULL value to Udma_chResume returns UDMA_EBADARGS */
    retValue = Udma_chResume(NULL_PTR);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with NULL_PTR to chHandle0Int->drvHandle to satisfy the condition */
    chHandle0Int->chInitDone = UDMA_INIT_DONE;
    chHandle0Int->drvHandle = NULL_PTR;
    retValue = Udma_chResume(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing NULL value to Udma_chGetNum to satisfy the condition */
    Udma_chGetNum(NULL_PTR);
    /* Passing valid parameters with NULL_PTR to chHandle0Int->drvHandle to satisfy the condition */
    chHandle0Int->drvHandle = NULL_PTR;
    Udma_chGetNum(chHandle0);
    /* Passing NULL value to Udma_chGetFqRingHandle to satisfy the condition */
    Udma_chGetFqRingHandle(NULL_PTR);
    /* Passing valid parameters with NULL_PTR to chHandle0Int->drvHandle to satisfy the condition */
    chHandle0Int->drvHandle = NULL_PTR;
    Udma_chGetFqRingHandle(chHandle0);
    /* Passing NULL value to Udma_chGetCqRingHandle to satisfy the condition */
    Udma_chGetCqRingHandle(NULL_PTR);
    /* Passing valid parameters with NULL_PTR to chHandle0Int->drvHandle to satisfy the condition */
    chHandle0Int->drvHandle = NULL_PTR;
    Udma_chGetCqRingHandle(chHandle0);
    /* Passing NULL value to Udma_chGetTdCqRingHandle to satisfy the condition */
    Udma_chGetTdCqRingHandle(NULL_PTR);
    /* Passing valid parameters with NULL_PTR to chHandle0Int->drvHandle to satisfy the condition */
    chHandle0Int->drvHandle = NULL_PTR;
    Udma_chGetTdCqRingHandle(chHandle0);
    /* Passing NULL value to Udma_chGetDefaultFlowHandle to satisfy the condition */
    Udma_chGetDefaultFlowHandle(NULL_PTR);
    /* Passing valid parameters with NULL_PTR to chHandle0Int->drvHandle to satisfy the condition */
    chHandle0Int->drvHandle = NULL_PTR;
    Udma_chGetDefaultFlowHandle(chHandle0);
    /* Passing NULL value to Udma_chGetTriggerEvent to satisfy the condition */
    Udma_chGetTriggerEvent(NULL_PTR,CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL1);
    /* Passing valid parameters with NULL_PTR to chHandle0Int->drvHandle to satisfy the condition */
    chHandle0Int->drvHandle = NULL_PTR;
    Udma_chGetTriggerEvent(chHandle0,CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL1);
    /* Passing valid parameters with UDMA_CH_FLAG_RX to satisfy the condition */
    chHandle0Int->drvHandle = (Udma_DrvHandleInt) drvHandle;
    chHandle0Int->chType = UDMA_CH_FLAG_RX;
    Udma_chGetTriggerEvent(chHandle0,CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL0);
    /* Passing NULL value to Udma_chGetSwTriggerRegister to satisfy the condition */
    Udma_chGetSwTriggerRegister(NULL_PTR);
    /* Passing valid parameters with NULL_PTR to chHandle0Int->drvHandle to satisfy the condition */
    chHandle0Int->drvHandle = NULL_PTR;
    Udma_chGetSwTriggerRegister(chHandle0);
    /* Passing NULL value to Udma_chSetSwTrigger returns UDMA_EBADARGS */
    retValue = Udma_chSetSwTrigger(NULL_PTR,CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL1);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing 5 value to Udma_chSetSwTrigger returns UDMA_EBADARGS */
    retValue = Udma_chSetSwTrigger(chHandle0,5);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with NULL_PTR to chHandle0Int->drvHandle to satisfy the condition */
    chHandle0Int->drvHandle = NULL_PTR;
    retValue = Udma_chSetSwTrigger(chHandle0,CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL1);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing NULL value to Udma_chSetChaining returns UDMA_EBADARGS */
    retValue = Udma_chSetChaining(NULL_PTR, chHandle1, CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing NULL value to Udma_chSetChaining returns UDMA_EBADARGS */
    retValue = Udma_chSetChaining(chHandle0, NULL_PTR, CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with NULL_PTR to chHandle0Int->drvHandle to satisfy the condition */
    chHandle0Int->drvHandle = NULL_PTR;
    retValue = Udma_chSetChaining(chHandle0, chHandle1, CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing NULL value to Udma_chBreakChaining returns UDMA_EBADARGS */
    retValue = Udma_chBreakChaining(NULL_PTR,chHandle1);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing NULL value to Udma_chBreakChaining returns UDMA_EBADARGS */
    retValue = Udma_chBreakChaining(chHandle0,NULL_PTR);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with NULL_PTR to chHandle0Int->drvHandle to satisfy the condition */
    chHandle0Int->drvHandle = NULL_PTR;
    retValue = Udma_chBreakChaining(chHandle0,chHandle1);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing NULL value to UdmaChPrms_init to unsatisfy the condition */
    UdmaChPrms_init(NULL_PTR, UDMA_CH_TYPE_UTC);
    /* Passing NULL value to UdmaChPrms_init to satisfy the condition */
    UdmaChPrms_init(&chParams, UDMA_CH_TYPE_TR_BLK_COPY);
    /* Passing NULL value to UdmaChTxPrms_init to unsatisfy the condition */
    UdmaChTxPrms_init(NULL_PTR,UDMA_CH_FLAG_UHC);
    /* Passing NULL value to UdmaChRxPrms_init to unsatisfy the condition */
    UdmaChRxPrms_init(NULL_PTR,UDMA_CH_FLAG_UHC);
    /* Passing NULL value to UdmaChUtcPrms_init to unsatisfy the condition */
    UdmaChUtcPrms_init(NULL_PTR);
    /* Passing NULL value to UdmaChPdmaPrms_init to unsatisfy the condition */
    UdmaChPdmaPrms_init(NULL_PTR);
    /* Passing NULL value to Udma_chGetStats returns UDMA_EFAIL */
    Udma_chGetStats(NULL_PTR, &chStats);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters with NULL_PTR to chHandle0Int->drvHandle to satisfy the condition */
    chHandle0Int->drvHandle = NULL_PTR;
    Udma_chGetStats(chHandle0, &chStats);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing NULL value to Udma_getPeerData returns UDMA_EBADARGS */
    retValue = Udma_getPeerData(NULL_PTR, &peerData);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with de_init chHandle0Int->chInitDone to satisfy the condition */
    chHandle0Int->chInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_getPeerData(chHandle0, &peerData);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with NULL_PTR to chHandle0Int->drvHandle to satisfy the condition */
    chHandle0Int->chInitDone = UDMA_INIT_DONE;
    chHandle0Int->chType = UDMA_CH_FLAG_PDMA;
    chHandle0Int->drvHandle = NULL_PTR;
    retValue = Udma_getPeerData(chHandle0, &peerData);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing NULL value to Udma_clearPeerData returns UDMA_EBADARGS */
    retValue = Udma_clearPeerData(NULL_PTR, peerData);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with de_init chHandle0Int->chInitDone to satisfy the condition */
    chHandle0Int->chInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_clearPeerData(chHandle0, peerData);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with NULL_PTR to chHandle0Int->drvHandle to satisfy the condition */
    chHandle0Int->chInitDone = UDMA_INIT_DONE;
    chHandle0Int->chType = UDMA_CH_FLAG_PDMA;
    chHandle0Int->drvHandle = NULL_PTR;
    retValue = Udma_clearPeerData(chHandle0, peerData);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing NULL value to Udma_chRingDeQueueRaw returns UDMA_EBADARGS */
    chHandle0Int->drvHandle = (Udma_DrvHandleInt) drvHandle;
    chHandle0Int->utcInfo = &Info;
    retValue = Udma_chRingDeQueueRaw(NULL_PTR, 2, eleInRing);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with NULL_PTR to chHandle0Int->utcInfo to unsatisfy the condition */
    chHandle0Int->drvHandle = (Udma_DrvHandleInt) drvHandle;
    chHandle0Int->utcInfo = NULL_PTR;
    retValue = Udma_chRingDeQueueRaw(chHandle0, 2, eleInRing);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with &Info to chHandle0Int->utcInfo to satisfy the condition */
    chHandle0Int->drvHandle = (Udma_DrvHandleInt) drvHandle;
    chHandle0Int->utcInfo = &Info;
    retValue = Udma_chRingDeQueueRaw(chHandle0, 2, NULL_PTR);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with NULL_PTR to chHandle0Int->drvHandle to unsatisfy the condition */
    chHandle0Int->drvHandle = NULL_PTR;
    chHandle0Int->utcInfo = &Info;
    retValue = Udma_chRingDeQueueRaw(chHandle0, 2, eleInRing);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing NULL value to Udma_chRingQueueRaw returns UDMA_EBADARGS */
    chHandle0Int->drvHandle = (Udma_DrvHandleInt) drvHandle;
    chHandle0Int->utcInfo = &Info;
    retValue = Udma_chRingQueueRaw(NULL_PTR, phyDescMem, 2);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with NULL_PTR to chHandle0Int->utcInfo to unsatisfy the condition */
    chHandle0Int->drvHandle = (Udma_DrvHandleInt) drvHandle;
    chHandle0Int->utcInfo = NULL_PTR;
    retValue = Udma_chRingQueueRaw(chHandle0, phyDescMem, 2);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing NULL value to Udma_chRingQueueRaw returns UDMA_EBADARGS */
    chHandle0Int->drvHandle = (Udma_DrvHandleInt) drvHandle;
    chHandle0Int->utcInfo = &Info;
    retValue = Udma_chRingQueueRaw(chHandle0, NULL_PTR, 2);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with NULL_PTR to chHandle0Int->drvHandle to satisfy the condition */
    chHandle0Int->drvHandle = NULL_PTR;
    chHandle0Int->utcInfo = &Info;
    retValue = Udma_chRingQueueRaw(chHandle0, phyDescMem, 2);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_PKTDMA and UDMA_CH_FLAG_RX to satisfy the condition */
    udma_default_handle_params_init();
    chHandle0Int->chInitDone = UDMA_INIT_DONE;
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    chHandle0Int->chType = UDMA_CH_FLAG_RX;
    retValue = Udma_chReset(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters with UDMA_INST_TYPE_LCDMA_PKTDMA and UDMA_CH_FLAG_RX to unsatisfy the condition */
    udma_default_handle_params_init();
    chHandle0Int->chInitDone = UDMA_INIT_DONE;
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    chHandle0Int->chType = UDMA_CH_FLAG_PDMA;
    retValue = Udma_chReset(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing NULL value to Udma_chReset returns UDMA_EBADARGS */
    retValue = Udma_chReset(NULL_PTR);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with NULL_PTR to chHandle0Int->drvHandle to satisfy the condition */
    chHandle0Int->drvHandle = NULL_PTR;
    retValue = Udma_chReset(chHandle0);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to Udma_chOpen to execute the Udma_chCheckParams */
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    chParams.peerChNum = UDMA_DMA_CH_ANY;
    retValue = Udma_chOpen(drvHandle,chHandle0,UDMA_CH_FLAG_PDMA,chPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    udma_default_handle_params_init();
    /* Passing valid parameters with UDMA_CH_FLAG_UTC and CSL_DRU_OWNER_DIRECT_TR to execute the Udma_chDisableExtChan */
    chHandle0Int->chInitDone = UDMA_INIT_DONE;
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    chHandle0Int->chType = UDMA_CH_FLAG_UTC;
    chHandle0Int->utcInfo = &Info;
    Info.utcType = UDMA_UTC_TYPE_DRU;
    chHandle0Int->utcPrms.druOwner = CSL_DRU_OWNER_DIRECT_TR;
    retValue = Udma_chDisable(chHandle0,100U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters with CSL_DRU_OWNER_UDMAC_TR and UDMA_INST_TYPE_LCDMA_BCDMA to execute the Udma_chDisableExtChan */
    chHandle0Int->utcPrms.druOwner = CSL_DRU_OWNER_UDMAC_TR;
    chHandle0Int->drvHandle->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    retValue = Udma_chDisable(chHandle0,100U);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing valid parameters to Udma_chOpen to satisfy the condition */
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    chParams.mappedChGrp = 5;
    retValue = Udma_chOpen(drvHandle,chHandle0,(UDMA_CH_FLAG_MAPPED|UDMA_CH_FLAG_RX), &chParams);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);

    DebugP_log("\r\n udma ch dynamic coverage test: PASS \r\n");
}

void test_udma_ring_common(void)
{
    uint32_t retValue = 0U;
    Udma_DrvHandle drvHandle_rgcom = &gUdmaDrvObj[CONFIG_UDMA0];
    Udma_RingHandle rgHandle_rgcom = &gUdmaDrvObj[CONFIG_UDMA0];
    Udma_RingPrms crgprms_val;
    Udma_RingPrms *rgprms_rgcom = &crgprms_val;
    rgprms_rgcom->orderId = 1U;
    Udma_DrvHandleInt   drvHandleInt = (Udma_DrvHandleInt) drvHandle_rgcom;
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    uint64_t *phyDescMem;
    uint64_t rvalue;
    phyDescMem = &rvalue;
    Udma_DrvHandleInt   drvHandleint_rgcom = (Udma_DrvHandleInt)drvHandle_rgcom;
    Udma_RingHandleInt rghandleint_rgcom   = (Udma_RingHandleInt)rgHandle_rgcom;
    DebugP_log("\r\n udma ring common dynamic coverage test...\r\n");
    /* Passing NULL inputs to Udma_ringAlloc for Negative tests */
    retValue = Udma_ringAlloc(NULL,rgHandle_rgcom,0U,rgprms_rgcom);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing NULL inputs to Udma_ringAlloc for Negative tests */
    retValue = Udma_ringAlloc(drvHandle_rgcom,NULL,0U,rgprms_rgcom);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing NULL inputs to Udma_ringAlloc for Negative tests */
    retValue = Udma_ringAlloc(drvHandle_rgcom,rgHandle_rgcom,0U,NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing the valid parameter to Udma_ringAlloc and de-init the drvHandleInt->drvInitDone */
    retValue = Udma_ringAlloc(drvHandle_rgcom,rgHandle_rgcom,1U,rgprms_rgcom);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);

    drvHandleInt->drvInitDone   = UDMA_INIT_DONE;
    rgprms_rgcom->ringMem       = 0U;
    rgprms_rgcom->elemCnt       = 0U;
    drvHandleInt->instType      = 0U;
    rgprms_rgcom->mode          = 0U;
    rgprms_rgcom->ringMemSize   = 0U;
    rgprms_rgcom->orderId       = 30U;
    rgprms_rgcom->mappedRingGrp = 10U;
    rgprms_rgcom->virtId        = 0U;
    /* Passing the valid parameters for ring params to execute the Udma_ringCheckParams */
    retValue = Udma_ringAlloc(drvHandle_rgcom,rgHandle_rgcom,1U,rgprms_rgcom);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retValue);

    drvHandleInt->drvInitDone   = UDMA_INIT_DONE;
    rgprms_rgcom->ringMem       = &crgprms_val;
    rgprms_rgcom->elemCnt       = 1U;
    drvHandleInt->instType      = 1U;
    rgprms_rgcom->mode          = TISCI_MSG_VALUE_RM_RING_MODE_CREDENTIALS;
    rgprms_rgcom->ringMemSize   = 1U;
    rgprms_rgcom->orderId       = 5U;
    rgprms_rgcom->mappedRingGrp = UDMA_MAPPED_GROUP_INVALID;
    rgprms_rgcom->virtId        = 0U;
    /* Passing the different valid parameters for ring params to execute the Udma_ringCheckParams */
    retValue = Udma_ringAlloc(drvHandle_rgcom,rgHandle_rgcom,1U,rgprms_rgcom);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    /* Passing NULL inputs to Udma_ringFree for Negative tests */
    retValue = Udma_ringFree(NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameter to Udma_ringFree and de-init the rghandleint_rgcom->ringInitDone for Negative tests */
    rghandleint_rgcom->ringInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_ringFree(rgHandle_rgcom);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameter to Udma_ringFree and de-init the drvHandleint_rgcom->drvInitDone for Negative tests */
    rghandleint_rgcom->ringInitDone = UDMA_INIT_DONE;
    drvHandleint_rgcom->drvInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_ringFree(rgHandle_rgcom);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameter to Udma_ringFree and NULL the rghandleint_rgcom->drvHandle for Negative tests */
    rghandleint_rgcom->ringInitDone = UDMA_INIT_DONE;
    drvHandleint_rgcom->drvInitDone = UDMA_INIT_DONE;
    rghandleint_rgcom->drvHandle    = NULL;
    retValue = Udma_ringFree(rgHandle_rgcom);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid ringhandle parameter to Udma_ringFree */
    rghandleint_rgcom->ringInitDone = UDMA_INIT_DONE;
    drvHandleint_rgcom->drvInitDone = UDMA_INIT_DONE;
    rghandleint_rgcom->drvHandle = (Udma_DrvHandleInt)drvHandle_rgcom;
    rghandleint_rgcom->ringNum = 1U;
    rghandleint_rgcom->mappedRingGrp = UDMA_MAPPED_GROUP_INVALID;
    retValue = Udma_ringFree(rgHandle_rgcom);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing valid ringhandle parameter to Udma_ringFree */
    rghandleint_rgcom->ringInitDone = UDMA_INIT_DONE;
    drvHandleint_rgcom->drvInitDone = UDMA_INIT_DONE;
    rghandleint_rgcom->drvHandle = (Udma_DrvHandleInt)drvHandle_rgcom;
    rghandleint_rgcom->ringNum = 1U;
    rghandleint_rgcom->mappedRingGrp = UDMA_DEINIT_DONE;
    retValue = Udma_ringFree(rgHandle_rgcom);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing the NULL inputs to Udma_ringAttach for negative test */
    retValue = Udma_ringAttach(NULL,NULL,1U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing the valid parameters and de-init the drvHandleint_rgcom->drvInitDone return negative value */
    drvHandleint_rgcom->drvInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_ringAttach(drvHandle_rgcom,rgHandle_rgcom,1U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing the valid parameters and init the drvHandleint_rgcom->drvInitDone */
    drvHandleint_rgcom->drvInitDone = UDMA_INIT_DONE;
    drvHandleint_rgcom->maxRings = 1U;
    retValue = Udma_ringAttach(drvHandle_rgcom,rgHandle_rgcom,2U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retValue);
    /* Passing the diff valid parameters and init the drvHandleint_rgcom->drvInitDone */
    drvHandleint_rgcom->drvInitDone = UDMA_INIT_DONE;
    drvHandleint_rgcom->maxRings = 2U;
    retValue = Udma_ringAttach(drvHandle_rgcom,rgHandle_rgcom,1U);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing NULL value to Udma_ringDetach returns UDMA_EBADARGS */
    retValue = Udma_ringDetach(NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with de_init rghandleint_rgcom->ringInitDone to satisfy the condition */
    rghandleint_rgcom->ringInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_ringDetach(rgHandle_rgcom);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters with de_init drvHandleint_rgcom->drvInitDone returns UDMA_EFAIL */
    rghandleint_rgcom->ringInitDone = UDMA_INIT_DONE;
    drvHandleint_rgcom->drvInitDone = UDMA_DEINIT_DONE;
    rghandleint_rgcom->drvHandle = (Udma_DrvHandleInt)drvHandle_rgcom;
    retValue = Udma_ringDetach(rgHandle_rgcom);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters with NULL to rghandleint_rgcom->drvHandle  to satisfy the condition */
    rghandleint_rgcom->ringInitDone = UDMA_INIT_DONE;
    drvHandleint_rgcom->drvInitDone = UDMA_INIT_DONE;
    rghandleint_rgcom->drvHandle = NULL;
    retValue = Udma_ringDetach(rgHandle_rgcom);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters with valid address to rghandleint_rgcom->drvHandle  to satisfy the condition */
    rghandleint_rgcom->ringInitDone = UDMA_INIT_DONE;
    drvHandleint_rgcom->drvInitDone = UDMA_INIT_DONE;
    rghandleint_rgcom->drvHandle = (Udma_DrvHandleInt)drvHandle_rgcom;
    retValue = Udma_ringDetach(rgHandle_rgcom);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing NULL value to Udma_ringQueueRaw returns UDMA_EBADARGS */
    retValue = Udma_ringQueueRaw(NULL,0U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with de_init rghandleint_rgcom->ringInitDone to satisfy the condition */
    rghandleint_rgcom->ringInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_ringQueueRaw(rgHandle_rgcom,0U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with UDMA_RING_INVALID rghandleint_rgcom->ringNum to satisfy the condition */
    rghandleint_rgcom->ringNum = UDMA_RING_INVALID;
    retValue = Udma_ringQueueRaw(rgHandle_rgcom,0U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters to Udma_ringQueueRaw to satisfy the condition */
    rghandleint_rgcom->ringInitDone = UDMA_INIT_DONE;
    rghandleint_rgcom->ringNum = UDMA_DEINIT_DONE;
    drvHandleint_rgcom->drvInitDone = UDMA_DEINIT_DONE;
    rghandleint_rgcom->drvHandle = (Udma_DrvHandleInt)drvHandle_rgcom;
    retValue = Udma_ringQueueRaw(rgHandle_rgcom,0U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to Udma_ringQueueRaw to satisfy the condition */
    drvHandleint_rgcom->drvInitDone = UDMA_INIT_DONE;
    rghandleint_rgcom->drvHandle = (Udma_DrvHandleInt)drvHandle_rgcom;
    retValue = Udma_ringQueueRaw(rgHandle_rgcom,0U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to Udma_ringQueueRaw to satisfy the condition */
    drvHandleint_rgcom->drvInitDone = UDMA_INIT_DONE;
    rghandleint_rgcom->drvHandle = NULL;
    retValue = Udma_ringQueueRaw(rgHandle_rgcom,0U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing NULL value to Udma_ringDequeueRaw returns UDMA_EBADARGS */
    retValue = Udma_ringDequeueRaw(NULL,NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with de_init rghandleint_rgcom->ringInitDone to satisfy the condition */
    rghandleint_rgcom->ringInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_ringDequeueRaw(rgHandle_rgcom,NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with UDMA_RING_INVALID rghandleint_rgcom->ringNum to satisfy the condition */
    rghandleint_rgcom->ringNum = UDMA_RING_INVALID;
    retValue = Udma_ringDequeueRaw(rgHandle_rgcom,0U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters to Udma_ringQueueRaw to satisfy the condition */
    rghandleint_rgcom->ringInitDone = UDMA_INIT_DONE;
    rghandleint_rgcom->ringNum = UDMA_DEINIT_DONE;
    drvHandleint_rgcom->drvInitDone = UDMA_DEINIT_DONE;
    rghandleint_rgcom->drvHandle = (Udma_DrvHandleInt)drvHandle_rgcom;
    retValue = Udma_ringDequeueRaw(rgHandle_rgcom,0U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to Udma_ringQueueRaw to satisfy the condition */
    drvHandleint_rgcom->drvInitDone = UDMA_INIT_DONE;
    rghandleint_rgcom->drvHandle = (Udma_DrvHandleInt)drvHandle_rgcom;
    retValue = Udma_ringDequeueRaw(rgHandle_rgcom,0U);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing valid parameters with NULL_PTR to rghandleint_rgcom->drvHandle to satisfy the condition */
    drvHandleint_rgcom->drvInitDone = UDMA_INIT_DONE;
    rghandleint_rgcom->drvHandle = NULL;
    retValue = Udma_ringDequeueRaw(rgHandle_rgcom,0U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing NULL value to Udma_ringFlushRaw returns UDMA_EBADARGS */
    retValue = Udma_ringFlushRaw(NULL,NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with de_init rghandleint_rgcom->ringInitDone to satisfy the condition */
    rghandleint_rgcom->ringInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_ringFlushRaw(rgHandle_rgcom,phyDescMem);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with UDMA_RING_INVALID rghandleint_rgcom->ringNum to satisfy the condition */
    rghandleint_rgcom->ringNum = UDMA_RING_INVALID;
    retValue = Udma_ringFlushRaw(rgHandle_rgcom,phyDescMem);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters to Udma_ringQueueRaw to satisfy the condition */
    rghandleint_rgcom->ringInitDone = UDMA_INIT_DONE;
    rghandleint_rgcom->ringNum = UDMA_DEINIT_DONE;
    drvHandleint_rgcom->drvInitDone = UDMA_DEINIT_DONE;
    rghandleint_rgcom->drvHandle = (Udma_DrvHandleInt)drvHandle_rgcom;
    retValue = Udma_ringFlushRaw(rgHandle_rgcom,phyDescMem);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid to execute the Udma_ringPrimeRead */
    Udma_ringPrimeRead(rgHandle_rgcom,phyDescMem);
    /* Passing valid parameters to execute the Udma_ringSetDoorBell */
    Udma_ringSetDoorBell(rgHandle_rgcom,2U);
    /* Passing valid parameters to execute the Udma_ringPrimeRead */
    rghandleint_rgcom->ringInitDone = UDMA_INIT_DONE;
    Udma_ringGetNum(rgHandle_rgcom);
    /* Passing valid parameters to execute the Udma_ringPrimeRead */
    rghandleint_rgcom->ringInitDone = UDMA_DEINIT_DONE;
    Udma_ringGetNum(NULL);
    /* Passing valid parameters to execute the Udma_ringGetMemPtr */
    Udma_ringGetMemPtr(rgHandle_rgcom);
    /* Passing valid parameters to execute the Udma_ringGetMode */
    Udma_ringGetMode(rgHandle_rgcom);
    /* Passing valid to execute the Udma_ringGetElementCnt */
    Udma_ringGetElementCnt(rgHandle_rgcom);
    /* Passing valid parameters to execute the Udma_ringGetForwardRingOcc */
    Udma_ringGetForwardRingOcc(rgHandle_rgcom);
    /* Passing valid parameters to execute the Udma_ringGetReverseRingOcc */
    Udma_ringGetReverseRingOcc(rgHandle_rgcom);
    /* Passing valid parameters to execute the Udma_ringGetWrIdx */
    Udma_ringGetWrIdx(rgHandle_rgcom);
    /* Passing valid parameters to execute the Udma_ringGetRdIdx */
    Udma_ringGetRdIdx(rgHandle_rgcom);
    /* Passing valid parameters to execute the UdmaRingPrms_init */
    UdmaRingPrms_init(rgprms_rgcom);
    /* Passing NULL value to UdmaRingPrms_init unsatify the condition */
    UdmaRingPrms_init(NULL);

    drvHandleInt->drvInitDone   = UDMA_INIT_DONE;
    rgprms_rgcom->ringMem       = (void *)(uintptr_t)128U;
    rgprms_rgcom->elemCnt       = 1U;
    drvHandleInt->instType      = 0U;
    rgprms_rgcom->mode          = 0U;
    rgprms_rgcom->ringMemSize   = UDMA_RING_SIZE_CHECK_SKIP;
    rgprms_rgcom->orderId       = 0U;
    rgprms_rgcom->mappedRingGrp = UDMA_MAPPED_GROUP_INVALID;
    rgprms_rgcom->virtId        = 0U;
    /* Passing valid parameters to Udma_ringAlloc to satisfy the condition */
    retValue = Udma_ringAlloc(drvHandle_rgcom,rgHandle_rgcom,UDMA_RING_ANY,rgprms_rgcom);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);

    drvHandleInt->drvInitDone   = UDMA_INIT_DONE;
    rgprms_rgcom->ringMem       = (void *)(uintptr_t)128U;
    rgprms_rgcom->elemCnt       = 1U;
    drvHandleInt->instType      = 0U;
    rgprms_rgcom->mode          = 0U;
    rgprms_rgcom->ringMemSize   = UDMA_RING_SIZE_CHECK_SKIP;
    rgprms_rgcom->orderId       = 0U;
    rgprms_rgcom->mappedRingGrp = 3U;
    rgprms_rgcom->virtId        = 0U;
    rgprms_rgcom->mappedChNum   = 20U;
    /* Test ringAlloc under different mappedRingGrp cases */
    retValue = Udma_ringAlloc(drvHandle_rgcom,rgHandle_rgcom,UDMA_RING_ANY,rgprms_rgcom);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    /* Test another condition for mappedRingGrp */
    rgprms_rgcom->mappedRingGrp = 5U;
    retValue = Udma_ringAlloc(drvHandle_rgcom,rgHandle_rgcom,UDMA_RING_ANY,rgprms_rgcom);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    /* Allocation with driver having maxRings = 0 */
    drvHandleInt->maxRings = 0U;
    retValue = Udma_ringAlloc(drvHandle_rgcom,rgHandle_rgcom,1U,rgprms_rgcom);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retValue);

    DebugP_log("\r\n udma ring common dynamic coverage test: PASS \r\n");
}

void test_udma_ring_lcdma(void)
{
    uint32_t retValue = 0U;
    Udma_RingHandle cringHandle;
    cringHandle = &gUdmaDrvObj[CONFIG_UDMA0];
    Udma_RingHandleInt crghandle = (Udma_RingHandleInt) cringHandle;
    Udma_DrvHandle drvHandle_ring = &gUdmaDrvObj[CONFIG_UDMA0];
    Udma_DrvHandleInt drvHandle_rlcdma = (Udma_DrvHandleInt) drvHandle_ring;
    Udma_RingPrms cRingPrms;
    cRingPrms.orderId = 1U;
    Udma_RingHandleInt rghandle_val = NULL;
    uint64_t *phyDescMem = NULL;
    Udma_DrvHandleInt rgdrvhandle_val = NULL;
    DebugP_log("\r\n udma ring lcdma dynamic coverage test...\r\n");
    /* Passing valid parameters to Udma_ringSetCfgLcdma */
    Udma_ringSetCfgLcdma(drvHandle_rlcdma,crghandle,&cRingPrms);
    /* Passing NULL to Udma_ringSetCfgLcdma to execute the else part */
    Udma_ringSetCfgLcdma(drvHandle_rlcdma,crghandle,NULL);
    /* Clearing registers on NULL ring handle */
    Udma_ringHandleClearRegsLcdma(NULL);
    /* Passing the valid parameters to satisfy the condition */
    retValue = Udma_ringQueueRawLcdma(drvHandle_rlcdma,crghandle,1U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing the valid parameters to satisfy the condition */
    rghandle_val->lcdmaCfg.wrOcc = 0U;
    rghandle_val->pLcdmaCfgRegs->BA_LO = 1U;
    rgdrvhandle_val->devIdRing = 1U;
    retValue = Udma_ringFlushRawLcdma(drvHandle_rlcdma,rghandle_val,phyDescMem);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing the Valid doorbell values */
    Udma_ringSetDoorBellLcdma(crghandle,VALID_DOORBELL_VALUE_1);
    Udma_ringSetDoorBellLcdma(crghandle,VALID_DOORBELL_VALUE_2);
    /* Passing Invalid negative doorbell values */
    Udma_ringSetDoorBellLcdma(crghandle,-VALID_DOORBELL_VALUE_1);
    Udma_ringSetDoorBellLcdma(crghandle,-VALID_DOORBELL_VALUE_2);
    /* Passing NULL handle to doorbell API */
    Udma_ringSetDoorBellLcdma(NULL,VALID_DOORBELL_VALUE_1);
    /* Passing valid parameter to Udma_ringGetMemPtrLcdma */
    crghandle->ringInitDone = UDMA_INIT_DONE;
    Udma_ringGetMemPtrLcdma(crghandle);
    /* Passing NULL parameter to fail the condition */
    Udma_ringGetMemPtrLcdma(NULL);
    /* Passing valid parameter to Udma_ringGetModeLcdma */
    Udma_ringGetModeLcdma(crghandle);
    /* Passing NULL parameter to fail the condition */
    Udma_ringGetModeLcdma(NULL);
    /* Passing valid parameter to Udma_ringGetElementCntLcdma */
    Udma_ringGetElementCntLcdma(crghandle);
    /* Passing NULL parameter to fail the condition */
    Udma_ringGetElementCntLcdma(NULL);
    /* Passing NULL parameter to fail the condition */
    Udma_ringGetForwardRingOccLcdma(NULL);
    /* Passing NULL parameter to fail the condition */
    Udma_ringGetReverseRingOccLcdma(NULL);
    /* Passing valid parameter to Udma_ringGetWrIdxLcdma */
    Udma_ringGetWrIdxLcdma(crghandle);
    /* Passing NULL parameter to fail the condition */
    Udma_ringGetWrIdxLcdma(NULL);
    /* Passing valid parameter to Udma_ringGetRdIdxLcdma */
    Udma_ringGetRdIdxLcdma(crghandle);
    /* Passing NULL parameter to fail the condition */
    Udma_ringGetRdIdxLcdma(NULL);
    /* Passing the NULL parameters to Udma_lcdmaRingaccMemOps */
    Udma_lcdmaRingaccMemOps(NULL,1U,CSL_LCDMA_RINGACC_MEM_OPS_TYPE_WR);
    /* Passing the NULL parameters to Udma_lcdmaRingaccMemOps */
    Udma_lcdmaRingaccMemOps(NULL,1U,1U);
    /* Passing the NULL parameters to Udma_lcdmaRingaccMemOps */
    Udma_lcdmaRingaccMemOps(NULL,1U,CSL_LCDMA_RINGACC_MEM_OPS_TYPE_RD);
    /* Passing the NULL parameters to Udma_lcdmaRingaccMemOps */
    Udma_lcdmaRingaccMemOps(NULL,1U,0U);

    DebugP_log("\r\n udma ring lcdma dynamic coverage test: PASS \r\n");
}

void test_udma_rm(void)
{
    uint32_t i = 0U;
    uint32_t retValue = 0U;
    Udma_DrvHandleInt drvHandle_rm = NULL;
    Udma_RmInitPrms *rmInitPrms_rm = &drvHandle_rm->rmInitPrms;
    Udma_RmDefBoardCfgPrms cRmDefBdCfgPrms;
    Udma_RmDefBoardCfgResp cRmDefBdCfgResp;
    Udma_RmSharedResPrms crmSharedResPrms;
    DebugP_log("\r\n udma rm dynamic coverage test...\r\n");

    rmInitPrms_rm->numBlkCopyCh    = NUM_BLK_COPY_CH;
    rmInitPrms_rm->numBlkCopyHcCh  = NUM_BLK_COPY_HC_CH;
    rmInitPrms_rm->numBlkCopyUhcCh = NUM_BLK_COPY_UHC_CH;
    rmInitPrms_rm->numTxCh         = NUM_TX_CH;
    rmInitPrms_rm->numRxCh         = NUM_RX_CH;
    rmInitPrms_rm->numTxHcCh       = NUM_TX_HC_CH;
    rmInitPrms_rm->numRxHcCh       = NUM_RX_HC_CH;
    rmInitPrms_rm->numTxUhcCh      = NUM_TX_UHC_CH;
    rmInitPrms_rm->numRxUhcCh      = NUM_RX_UHC_CH;

    for(i=0; i<2; i++)
    {
        rmInitPrms_rm->numUtcCh[i] = UDMA_NUM_UTC_INSTANCE;
    }

    for(i=0; i<4; i++)

    {
        rmInitPrms_rm->numMappedTxCh[i] = UDMA_NUM_MAPPED_TX_GROUP;
        rmInitPrms_rm->numMappedRxCh[i] = UDMA_NUM_MAPPED_RX_GROUP;
    }

    for(i=0; i<8; i++)
    {
        rmInitPrms_rm->numMappedRing[i] = UDMA_NUM_MAPPED_TX_GROUP + UDMA_NUM_MAPPED_RX_GROUP;
    }

    rmInitPrms_rm->numFreeRing    = NUM_FREE_RING;
    rmInitPrms_rm->numFreeFlow    = NUM_FREE_FLOW;
    rmInitPrms_rm->numGlobalEvent = NUM_GLOBAL_EVENT;
    rmInitPrms_rm->numVintr       = NUM_VINTR;
    rmInitPrms_rm->numIrIntr      = NUM_IR_INTR;

    Udma_rmInit(drvHandle_rm);

    rmInitPrms_rm->numBlkCopyCh    = 2U;
    rmInitPrms_rm->numBlkCopyHcCh  = 2U;
    rmInitPrms_rm->numBlkCopyUhcCh = 2U;
    rmInitPrms_rm->numTxCh         = 2U;
    rmInitPrms_rm->numTxHcCh       = 2U;
    rmInitPrms_rm->numTxUhcCh      = 2U;
    rmInitPrms_rm->numRxCh         = 2U;
    rmInitPrms_rm->numRxHcCh       = 2U;
    rmInitPrms_rm->numRxUhcCh      = 2U;

    rmInitPrms_rm->numFreeRing     = 2U;
    rmInitPrms_rm->numFreeFlow     = 2U;
    rmInitPrms_rm->numGlobalEvent  = 2U;
    rmInitPrms_rm->numVintr        = 2U;
    rmInitPrms_rm->numIrIntr       = 2U;

    retValue = Udma_rmDeinit(drvHandle_rm);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);

    rmInitPrms_rm->numBlkCopyCh    = 32U;
    rmInitPrms_rm->numBlkCopyHcCh  = 32U;
    rmInitPrms_rm->numBlkCopyUhcCh = 32U;
    rmInitPrms_rm->numTxCh         = 32U;
    rmInitPrms_rm->numTxHcCh       = 32U;
    rmInitPrms_rm->numTxUhcCh      = 32U;
    rmInitPrms_rm->numRxCh         = 32U;
    rmInitPrms_rm->numRxHcCh       = 32U;
    rmInitPrms_rm->numRxUhcCh      = 32U;

    rmInitPrms_rm->numFreeRing     = 32U;
    rmInitPrms_rm->numFreeFlow     = 32U;
    rmInitPrms_rm->numGlobalEvent  = 32U;
    rmInitPrms_rm->numVintr        = 32U;
    rmInitPrms_rm->numIrIntr       = 32U;

    retValue = Udma_rmDeinit(drvHandle_rm);
    TEST_ASSERT_EQUAL_INT32( -14 , retValue);
    /* Passing valid parameters to Udma_rmAllocFreeRing */
    Udma_rmAllocFreeRing(drvHandle_rm);
    /* Passing valid parameters to Udma_rmFreeFreeRing */
    Udma_rmFreeFreeRing(1U,drvHandle_rm);
    /* Passing valid parameters and drvHandle_rm->instType = 0 to fail the condition */
    drvHandle_rm->instType = 0U;
    Udma_rmTranslateIrOutput(drvHandle_rm,RM_INTR_NUM);
    /* Passing valid parameters and drvHandle_rm->instType = 1 to satisfy the condition */
    drvHandle_rm->instType = 1U;
    Udma_rmTranslateIrOutput(drvHandle_rm,RM_INTR_NUM);
    /* Passing valid parameters and drvHandle_rm->instType = 0 to fail the condition */
    drvHandle_rm->instType = 0U;
    Udma_rmTranslateCoreIntrInput(drvHandle_rm,RM_CORE_INTR_NUM);
    /* Passing valid parameters and drvHandle_rm->instType = 1 to satisfy the condition */
    drvHandle_rm->instType = 1U;
    Udma_rmTranslateCoreIntrInput(drvHandle_rm,RM_CORE_INTR_NUM);
    /* Passing valid parameters with sciclientReqType and rangeStart to satisfy the condition */
    cRmDefBdCfgPrms.sciclientReqType = 1U;
    cRmDefBdCfgResp.rangeStart = 1U;
    retValue = Udma_rmGetSciclientDefaultBoardCfgRmRange(&cRmDefBdCfgPrms,&cRmDefBdCfgResp,NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing valid parameters with sciclientReqType and rangeStart to fail the condition */
    cRmDefBdCfgPrms.sciclientReqType = UDMA_RM_SCI_REQ_TYPE_INVALID;
    cRmDefBdCfgResp.rangeStart = UDMA_RM_SCI_REQ_TYPE_INVALID;
    retValue = Udma_rmGetSciclientDefaultBoardCfgRmRange(&cRmDefBdCfgPrms,&cRmDefBdCfgResp,NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing NULL value to Udma_rmSetSharedResRmInitPrms for to return UDMA_EBADARGS */
    crmSharedResPrms.resId = 0U;
    retValue = Udma_rmSetSharedResRmInitPrms(NULL,0U,0U,0U,NULL,NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters to Udma_rmSetSharedResRmInitPrms for to return UDMA_EBADARGS */
    crmSharedResPrms.resId         = 1U;
    crmSharedResPrms.numInst       = 1U;
    crmSharedResPrms.minReq        = 1U;
    crmSharedResPrms.startResrvCnt = 1U;
    crmSharedResPrms.endResrvCnt   = 1U;
    retValue = Udma_rmSetSharedResRmInitPrms(&crmSharedResPrms,0U,0U,0U,NULL,NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters to Udma_rmSetSharedResRmInitPrms for to return UDMA_EINVALID_PARAMS */
    retValue = Udma_rmSetSharedResRmInitPrms(&crmSharedResPrms,0U,0U,NUM_RM_RANGE,NULL,NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retValue);
    /* Passing valid parameters with instShare to satisfy the condition */
    crmSharedResPrms.instShare[0] = UDMA_RM_SHARED_RES_CNT_MIN;
    retValue = Udma_rmSetSharedResRmInitPrms(&crmSharedResPrms,RM_INST_ID,0U,NUM_RM_RANGE,NULL,NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing valid parameters with instShare to satisfy the condition */
    crmSharedResPrms.instShare[0] = 1U;
    crmSharedResPrms.instShare[0] = UDMA_RM_SHARED_RES_CNT_REST;
    retValue = Udma_rmSetSharedResRmInitPrms(&crmSharedResPrms,RM_INST_ID,0U,NUM_RM_RANGE,NULL,NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing NULL value to UdmaRmInitPrms_init for to return UDMA_EBADARGS */
    retValue=UdmaRmInitPrms_init(1,NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters to UdmaRmInitPrms_init */
    retValue=UdmaRmInitPrms_init(UDMA_INST_ID_PKTDMA_0,rmInitPrms_rm);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing valid parameters to UdmaRmInitPrms_init */
    retValue=UdmaRmInitPrms_init(4U,rmInitPrms_rm);
    TEST_ASSERT_EQUAL_INT32(UDMA_ETIMEOUT, retValue);
    /* Passing valid parameters to Udma_rmAllocMappedRing to execute the Udma_getMappedChRingAttributes */
    Udma_rmAllocMappedRing(drvHandle_rm,3,30);
    /* Passing diff valid parameters to Udma_rmAllocMappedRing to execute the Udma_getMappedChRingAttributes */
    Udma_rmAllocMappedRing(drvHandle_rm,4,30);
    /* Passing valid parameters with numInst to fail the condition */
    crmSharedResPrms.numInst       = 1U;
    crmSharedResPrms.minReq        = 1U;
    retValue = Udma_rmSetSharedResRmInitPrms(&crmSharedResPrms,RM_INST_ID,0U,NUM_RM_RANGE,NULL,NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing valid parameters with instShare[0] = UDMA_RM_SHARED_RES_CNT_MIN to fail the condition */
    crmSharedResPrms.numInst       = 1U;
    crmSharedResPrms.minReq        = 1U;
    crmSharedResPrms.instShare[0] = UDMA_RM_SHARED_RES_CNT_MIN;
    retValue = Udma_rmSetSharedResRmInitPrms(&crmSharedResPrms,RM_INST_ID,0U,NUM_RM_RANGE,NULL,NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);

    DebugP_log("\r\n udma rm dynamic coverage test: PASS \r\n");
}

void test_udma_flow(void)
{
    uint32_t retValue = 0U;
    Udma_DrvHandle  drvHandle_flow = &gUdmaDrvObj[CONFIG_UDMA0];
    Udma_FlowHandle cflhandle;
    Udma_FlowAllocMappedPrms cflallocmap;
    cflhandle = &gUdmaDrvObj[CONFIG_UDMA0];
    Udma_DrvHandleInt   drvHandleInt = (Udma_DrvHandleInt) drvHandle_flow;
    Udma_FlowHandleInt  flowHandleInt = (Udma_FlowHandleInt) cflhandle;
    Udma_FlowPrms cflprms;
    DebugP_log("\r\n udma flow dynamic coverage test...\r\n");
    /* Passing NULL value to Udma_flowAllocMapped returns UDMA_EBADARGS */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    cflallocmap.mappedChNum    = UDMA_DMA_CH_INVALID;
    cflallocmap.mappedFlowGrp  = 5U;
    retValue = Udma_flowAllocMapped(NULL,NULL,NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing NULL value to Udma_flowAllocMapped returns UDMA_EBADARGS */
    retValue = Udma_flowAllocMapped(drvHandle_flow,NULL,&cflallocmap);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing NULL value to Udma_flowAllocMapped returns UDMA_EBADARGS */
    retValue = Udma_flowAllocMapped(drvHandle_flow,cflhandle,NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with de_init the drvHandleInt->drvInitDone returns UDMA_EFAIL */
    retValue = Udma_flowAllocMapped(drvHandle_flow,cflhandle,&cflallocmap);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing the valid parameters to execute the Udma_mappedFlowCheckParams */
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    cflallocmap.mappedFlowGrp = UDMA_MAPPED_GROUP_INVALID;
    cflallocmap.mappedChNum   = UDMA_DMA_CH_INVALID;
    retValue = Udma_flowAllocMapped(drvHandle_flow,cflhandle,&cflallocmap);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retValue);
    /* Passing the valid parameters to execute the Udma_mappedFlowCheckParams */
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    cflallocmap.mappedFlowGrp  = 3U;
    cflallocmap.mappedChNum    = 0U;
    retValue = Udma_flowAllocMapped(drvHandle_flow,cflhandle,&cflallocmap);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retValue);
    /* Passing the valid parameters to execute the Udma_mappedFlowCheckParams */
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    cflallocmap.mappedFlowGrp = 10U;
    cflallocmap.mappedChNum   = UDMA_DMA_CH_INVALID;
    retValue = Udma_flowAllocMapped(drvHandle_flow,cflhandle,&cflallocmap);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retValue);
    /* Passing the valid parameters to execute the Udma_mappedFlowCheckParams */
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    cflallocmap.mappedFlowGrp  = 5U;
    cflallocmap.mappedChNum    = 0U;
    retValue = Udma_flowAllocMapped(drvHandle_flow,cflhandle,&cflallocmap);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    /* Passing NULL value to Udma_flowAttachMapped returns UDMA_EBADARGS */
    retValue = Udma_flowAttachMapped(NULL,cflhandle,0U,&cflallocmap);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing the valid parameters to execute the Udma_mappedFlowCheckParams */
    retValue = Udma_flowAttachMapped(drvHandle_flow,NULL,0U,&cflallocmap);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing the valid parameters to execute the Udma_mappedFlowCheckParams */
    retValue = Udma_flowAttachMapped(drvHandle_flow,cflhandle,0U,NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing the valid parameters to execute the Udma_mappedFlowCheckParams */
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    cflallocmap.mappedChNum   = UDMA_DMA_CH_INVALID;
    cflallocmap.mappedFlowGrp = UDMA_MAPPED_GROUP_INVALID;
    retValue = Udma_flowAttachMapped(drvHandle_flow,cflhandle,1U,&cflallocmap);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retValue);
    /* Passing the valid parameters to execute the Udma_mappedFlowCheckParams */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    cflallocmap.mappedChNum    = UDMA_DMA_CH_INVALID;
    cflallocmap.mappedFlowGrp  = UDMA_MAPPED_GROUP_INVALID;
    retValue = Udma_flowAttachMapped(drvHandle_flow,cflhandle,1U,&cflallocmap);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing the valid parameters to execute the Udma_mappedFlowCheckParams */
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    cflallocmap.mappedChNum    = 0U;
    cflallocmap.mappedFlowGrp  = 5U;
    retValue = Udma_flowAttachMapped(drvHandle_flow,cflhandle,1U,&cflallocmap);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing NULL value to Udma_flowConfig returns UDMA_EBADARGS */
    retValue = Udma_flowConfig(NULL,0U,&cflprms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing NULL value to Udma_flowConfig returns UDMA_EBADARGS */
    retValue = Udma_flowConfig(cflhandle,0U,NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with de_init flowHandleInt->flowInitDone to satisfy the condition */
    flowHandleInt->flowInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_flowConfig(cflhandle,0U,&cflprms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with de_init drvHandleInt->drvInitDone returns UDMA_EFAIL */
    cflprms.fdq0Sz3Qnum = 1U;
    flowHandleInt->flowInitDone = UDMA_INIT_DONE;
    drvHandleInt->drvInitDone   = UDMA_DEINIT_DONE;
    retValue = Udma_flowConfig(cflhandle,1U,&cflprms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters with flowHandleInt->flowCnt to fail the if condition */
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    flowHandleInt->flowCnt = 2U;
    retValue = Udma_flowConfig(cflhandle,1U,&cflprms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters with flowHandleInt->flowCnt to satisfy the if condition */
    flowHandleInt->flowCnt = 0U;
    retValue = Udma_flowConfig(cflhandle,1U,&cflprms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retValue);
    /* Passing NULL value to Udma_flowFree return UDMA_EBADARGS */
    retValue = Udma_flowFree(NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameter with de-init flowHandleInt->flowInitDone return UDMA_EFAIL */
    flowHandleInt->flowInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_flowFree(cflhandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameter with de-init drvHandleInt->drvInitDone return UDMA_EFAIL */
    flowHandleInt->flowInitDone = UDMA_INIT_DONE;
    drvHandleInt->drvInitDone   = UDMA_DEINIT_DONE;
    retValue = Udma_flowFree(cflhandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameter with flowHandleInt->mappedFlowGrp 0 fail the if condition */
    flowHandleInt->flowInitDone  = UDMA_INIT_DONE;
    drvHandleInt->drvInitDone    = UDMA_INIT_DONE;
    flowHandleInt->mappedFlowGrp = 0U;
    retValue = Udma_flowFree(cflhandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing valid parameter with flowHandleInt->mappedFlowGrp=UDMA_MAPPED_GROUP_INVALID satisfy the if condition */
    flowHandleInt->drvHandle     = (Udma_DrvHandleInt) drvHandle_flow;
    flowHandleInt->flowInitDone  = UDMA_INIT_DONE;
    drvHandleInt->drvInitDone    = UDMA_INIT_DONE;
    flowHandleInt->mappedFlowGrp = UDMA_MAPPED_GROUP_INVALID;
    retValue = Udma_flowFree(cflhandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameter with flowHandleInt->drvHandle=NULL returns UDMA_EFAIL */
    flowHandleInt->flowInitDone = UDMA_INIT_DONE;
    drvHandleInt->drvInitDone   = UDMA_INIT_DONE;
    flowHandleInt->drvHandle    = NULL;
    retValue = Udma_flowFree(cflhandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing NULL to Udma_flowDetach returns UDMA_EBADARGS */
    retValue = Udma_flowDetach(NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameter with flowHandleInt->flowInitDone=UDMA_DEINIT_DONE returns UDMA_EFAIL */
    flowHandleInt->flowInitDone = UDMA_DEINIT_DONE ;
    retValue = Udma_flowDetach(cflhandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameter to Udma_flowDetach */
    flowHandleInt->flowInitDone = UDMA_INIT_DONE;
    retValue = Udma_flowDetach(cflhandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing NULL to Udma_flowGetNum */
    Udma_flowGetNum(NULL);
    /* Passing flowHandleInt->flowInitDone=UDMA_INIT_DONE fail the if condition */
    flowHandleInt->flowInitDone = UDMA_INIT_DONE;
    Udma_flowGetNum(cflhandle);
    /* Passing NULL to Udma_flowGetNum */
    Udma_flowGetCount(NULL);
    /* Passing flowHandleInt->flowInitDone=UDMA_INIT_DONE fail the if condition */
    flowHandleInt->flowInitDone = UDMA_INIT_DONE;
    Udma_flowGetCount(cflhandle);
    /* Passing NULL to UdmaFlowPrms_init fail the if condition */
    UdmaFlowPrms_init(NULL,0U);
    /* Passing valid value to UdmaFlowPrms_init execute the if condition */
    cflprms.fdq0Sz3Qnum = 1U;
    UdmaFlowPrms_init(&cflprms,0U);
    /* Passing NULL to Udma_flowAttach returns UDMA_EBADARGS */
    retValue = Udma_flowAttach(NULL,cflhandle,0U,0U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing NULL to Udma_flowAttach returns UDMA_EBADARGS */
    retValue = Udma_flowAttach(drvHandle_flow,NULL,0U,1U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing NULL to Udma_flowAttach returns UDMA_EBADARGS */
    retValue = Udma_flowAttach(drvHandle_flow,cflhandle,0U,0U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameter with de-init the drvHandleInt->drvInitDone returns UDMA_EFAIL */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_flowAttach(drvHandle_flow,cflhandle,1U,1U);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to Udma_flowAttach */
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    retValue = Udma_flowAttach(drvHandle_flow,cflhandle,1U,1U);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing valid parameters with flowHandleInt->drvHandle=NULL return UDMA_EFAIL */
    flowHandleInt->flowInitDone = UDMA_INIT_DONE;
    drvHandleInt->drvInitDone   = UDMA_INIT_DONE;
    flowHandleInt->drvHandle    = NULL;
    retValue = Udma_flowConfig(cflhandle,1U,&cflprms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);

    DebugP_log("\r\n udma flow dynamic coverage test: PASS \r\n");
}

void test_udma_utils(void)
{
    Udma_ChHandleInt chHandle;
    Udma_DrvHandle  drvHandle = &gUdmaDrvObj[CONFIG_UDMA0];
    Udma_DrvHandleInt  drvHandle_utils = NULL;
    Udma_ChHandle cchHandle;
    uint32_t rvalue;
    uint8_t *trpdMem;
    uint8_t avalue;
    DebugP_log("\r\n udma utils dynamic coverage test...\r\n");

    UdmaUtils_getRingMemSize(0U,0U,0U);
    /* Passing valid parameters to satisfy the condition */
    UdmaUtils_getRingMemSize(TISCI_MSG_VALUE_RM_RING_MODE_CREDENTIALS,0U,0U);
    /* Passing valid parameters to satisfy the condition */
    UdmaUtils_getRingMemSize(TISCI_MSG_VALUE_RM_RING_MODE_QM,0U,0U);
    /* Passing valid parameters to satisfy the condition */
    UdmaUtils_getTrSizeEncoded(2U);
    /* Passing valid parameters to fail the condition */
    UdmaUtils_getTrSizeBytes(3U);
    /* Passing valid parameters to Udma_virtToPhyFxn */
    drvHandle_utils->initPrms.virtToPhyFxn = UDMA_DEINIT_DONE;
    Udma_virtToPhyFxn(NULL,drvHandle_utils,NULL);
    /* Passing valid parameters to Udma_virtToPhyFxn */
    struct Udma_ChObjectInt_t chObject;
    chHandle = &chObject;
    drvHandle_utils->initPrms.virtToPhyFxn = Udma_defaultVirtToPhyFxn;
    Udma_virtToPhyFxn(NULL,drvHandle_utils,chHandle);
    /* Passing valid parameters to Udma_virtToPhyFxn */
    drvHandle_utils->initPrms.virtToPhyFxn = Udma_defaultVirtToPhyFxn;
    Udma_virtToPhyFxn(NULL,drvHandle_utils,NULL);
    /* Passing valid parameters to Udma_phyToVirtFxn */
    drvHandle_utils->initPrms.virtToPhyFxn = UDMA_DEINIT_DONE;
    Udma_phyToVirtFxn(0U,drvHandle_utils,0U);
    /* Passing valid parameters to Udma_phyToVirtFxn */
    drvHandle_utils->initPrms.virtToPhyFxn = Udma_defaultVirtToPhyFxn;
    drvHandle_utils->initPrms.phyToVirtFxn = Udma_defaultPhyToVirtFxn;
    Udma_phyToVirtFxn(0U,drvHandle_utils,chHandle);
    /* Passing valid parameters to Udma_phyToVirtFxn */
    Udma_phyToVirtFxn(0U,drvHandle_utils,0U);
    /* Passing NULL value to execute the else condition */
    UdmaUtils_mapLocaltoGlobalEvent(NULL,NULL,0U,0U);
    /* Passing valid parameters to satisfy the if condition and execute the CSL_intaggrMapEventToLocalEvent */
    cchHandle = &rvalue;
    drvHandle_utils = (Udma_DrvHandleInt) drvHandle;
    UdmaUtils_mapLocaltoGlobalEvent(drvHandle_utils,cchHandle,CSL_INTAGGR_EVT_DETECT_MODE_RISING_EDGE,CSL_INTAGGR_EVT_DETECT_MODE_RISING_EDGE);
    /* Passing valid parameters to satisfy the if condition and execute the CSL_intaggrMapEventToLocalEvent */
    UdmaUtils_mapLocaltoGlobalEvent(drvHandle_utils,cchHandle,CSL_INTAGGR_EVT_DETECT_MODE_RISING_EDGE,CSL_INTAGGR_EVT_DETECT_MODE_INVALID);
    /* Passing NULL value to execute the else condition */
    UdmaUtils_setTrpdReload(NULL,0U,0U);
    /* Passing valid parameters to satisfy the if condition and execute the CSL_udmapCppi5TrSetReload */
    trpdMem = &avalue;
    UdmaUtils_setTrpdReload(trpdMem,1U,1U);

    DebugP_log("\r\n udma utils dynamic coverage test: PASS \r\n");
}

void test_udma_event(void)
{
    uint32_t retValue = 0U;
    uint32_t chType = 4U;
    Udma_ChHandle       ch0Handle = NULL;
    Udma_EventObject    Ch0TrEventObj;
    Udma_DrvHandle      drvHandle = &gUdmaDrvObj[CONFIG_UDMA0];
    Udma_EventHandle    Ch0TrEventHandle = &Ch0TrEventObj;
    Udma_EventPrms      Ch0TrEventPrms;
    Udma_EventCallback  callback = NULL;
    Udma_EventHandleInt masterEvent_handle;
    Udma_EventHandleInt eventHandleInt;
    Udma_ChHandleInt    chHandle;
    Udma_RingObjectInt  ringHandle;
    Udma_ChObjectInt    ch_Handle;
    Udma_RingObjectInt  ringNum;
    Udma_DrvHandleInt   drvHandleInt;
    DebugP_log("\r\n udma event dynamic coverage test...\r\n");
    /* Passing valid parameters to satisfy the condition */
    UdmaEventPrms_init(&Ch0TrEventPrms);
    /* Passing NULL_PTR value to unsatisfy the condition */
    UdmaEventPrms_init(NULL_PTR);

    Ch0TrEventPrms.eventType         = UDMA_EVENT_TYPE_TR;
    Ch0TrEventPrms.eventMode         = UDMA_EVENT_MODE_SHARED;
    Ch0TrEventPrms.chHandle          = ch0Handle;
    Ch0TrEventPrms.masterEventHandle = NULL;
    Ch0TrEventPrms.eventCb           = NULL;
    Ch0TrEventPrms.appData           = NULL;

    drvHandleInt = (Udma_DrvHandleInt) drvHandle;
    /* Passing NULL to Udma_eventRegister returns UDMA_EBADARGS */
    retValue = Udma_eventRegister(NULL, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing NULL to Udma_eventRegister returns UDMA_EBADARGS */
    retValue = Udma_eventRegister(drvHandle, NULL, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing NULL to Udma_eventRegister returns UDMA_EBADARGS */
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters with de-init the drvHandleInt->drvInitDone returns UDMA_EFAIL */
    ch0Handle = &gUdmaDrvObj[CONFIG_UDMA0];
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to execute the Udma_eventCheckParams */
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    Ch0TrEventPrms.eventMode = UDMA_EVENT_MODE_EXCLUSIVE;
    Ch0TrEventPrms.masterEventHandle = &gUdmaDrvObj[CONFIG_UDMA0];
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retValue);
    /* Passing valid parameters to execute the Udma_eventCheckParams */
    Ch0TrEventPrms.eventMode = UDMA_EVENT_MODE_SHARED;
    masterEvent_handle = (Udma_EventHandleInt) Ch0TrEventPrms.masterEventHandle;
    Ch0TrEventPrms.eventCb = NULL;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retValue);
    /* Passing valid parameters to execute the Udma_eventCheckParams */
    Ch0TrEventPrms.eventMode = UDMA_EVENT_MODE_SHARED;
    masterEvent_handle->eventPrms.eventCb = NULL;
    Ch0TrEventPrms.eventCb = (Udma_EventCallback) &Ch0TrEventObj;
    masterEvent_handle->eventPrms.eventType = UDMA_EVENT_TYPE_RING;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retValue);
    /* Passing valid parameters to execute the Udma_eventCheckParams */
    Ch0TrEventPrms.eventCb = callback;
    Ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_TR;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retValue);
    /* Passing valid parameters to execute the Udma_eventCheckParams */
    Ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_RING;
    Ch0TrEventPrms.ringHandle = NULL;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retValue);
    /* Passing valid parameters to execute the Udma_eventCheckParams */
    Ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_MASTER;
    Ch0TrEventPrms.eventMode = UDMA_EVENT_MODE_EXCLUSIVE;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retValue);
    /* Passing valid parameters to Udma_eventRegister */
    eventHandleInt = (Udma_EventHandleInt) Ch0TrEventHandle;
    eventHandleInt->prevEvent = (Udma_EventHandleInt) NULL_PTR;
    eventHandleInt->nextEvent = masterEvent_handle;
    Ch0TrEventPrms.eventType = 0U;
    Ch0TrEventPrms.eventMode = 0U;
    Ch0TrEventPrms.masterEventHandle = NULL_PTR;
    ((Udma_EventHandleInt)Ch0TrEventPrms.masterEventHandle)->nextEvent = NULL_PTR;
    ((Udma_EventHandleInt)Ch0TrEventPrms.masterEventHandle)->prevEvent = NULL_PTR;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);

    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to execute the Udma_eventAllocResource */
    Udma_RmInitPrms    *rmInitPrms = &drvHandleInt->rmInitPrms;
    rmInitPrms->numGlobalEvent =0U;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    /* Passing valid parameters to execute the Udma_eventAllocResource */
    rmInitPrms->numGlobalEvent =128U;
    Ch0TrEventPrms.masterEventHandle = NULL_PTR;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to execute the Udma_eventAllocResource */
    rmInitPrms->numVintr=0U;
    Ch0TrEventPrms.eventMode = UDMA_EVENT_MODE_SHARED;
    Ch0TrEventPrms.masterEventHandle = NULL;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    /* Passing valid parameters to execute the Udma_eventAllocResource */
    rmInitPrms->numVintr =45U;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to execute the Udma_eventAllocResource */
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to execute the Udma_eventAllocResource */
    Ch0TrEventPrms.eventCb = NULL;
    Ch0TrEventPrms.preferredCoreIntrNum = UDMA_CORE_INTR_ANY;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to execute the Udma_eventAllocResource */
    Ch0TrEventPrms.preferredCoreIntrNum = UDMA_INTR_INVALID;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to execute the Udma_eventAllocResource */
    Ch0TrEventPrms.preferredCoreIntrNum = 0U;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to execute the Udma_eventAllocResource */
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to execute the Udma_eventAllocResource */
    eventHandleInt->vintrBitAllocFlag = 1U;
    chHandle = (Udma_ChHandleInt) Ch0TrEventPrms.chHandle;
    chHandle->chOesAllocDone = 1U;
    Ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_TR;
    Ch0TrEventPrms.preferredCoreIntrNum = UDMA_CORE_INTR_ANY;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retValue);
    /* Passing valid parameters to execute the Udma_eventAllocResource */
    eventHandleInt->vintrBitAllocFlag = 0U;
    eventHandleInt->prevEvent = (Udma_EventHandleInt) NULL_PTR;
    eventHandleInt->nextEvent = (Udma_EventHandleInt) masterEvent_handle;
    Ch0TrEventPrms.eventType = 0U;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to execute the Udma_eventAllocResource */
    Ch0TrEventPrms.eventMode = 0U;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to execute the Udma_eventAllocResource */
    Ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_TR;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retValue);
    /* Passing valid parameters to Udma_eventRegister */
    Ch0TrEventPrms.chHandle = &chType;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to Udma_eventRegister */
    chType=2U;
    Ch0TrEventPrms.chHandle = &chType;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to Udma_eventRegister */
    chType=1U;
    Ch0TrEventPrms.chHandle = &chType;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to Udma_eventRegister */
    Ch0TrEventPrms.chHandle = &gUdmaDrvObj[CONFIG_UDMA0];
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to Udma_eventRegister */
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to Udma_eventRegister */
    ringHandle.mappedRingGrp=5U;
    Ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_RING;
    Ch0TrEventPrms.ringHandle = &ringHandle;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to Udma_eventRegister */
    ch_Handle.chType = 4U;
    ch_Handle.cqRing = &ringNum;
    Ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_DMA_COMPLETION;
    Ch0TrEventPrms.chHandle = &ch_Handle;
    drvHandleInt->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to Udma_eventRegister */
    Ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_TEARDOWN_COMPLETION;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to Udma_eventRegister */
    ch_Handle.chType = 1U;
    Ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_DMA_COMPLETION;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to Udma_eventRegister */
    Ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_TEARDOWN_COMPLETION;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to Udma_eventRegister */
    ch_Handle.chType = 0U;
    Ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_DMA_COMPLETION;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to Udma_eventRegister */
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to Udma_eventRegister */
    ch_Handle.chType = 0U;
    Ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_MASTER;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EINVALID_PARAMS, retValue);
    /* Passing valid parameters to Udma_eventRegister */
    Ch0TrEventPrms.eventMode = UDMA_EVENT_MODE_SHARED;
    Ch0TrEventPrms.masterEventHandle = NULL;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing valid parameters to Udma_eventRegister */
    Ch0TrEventPrms.eventMode = 0U;
    Ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_TEARDOWN_PACKET;
    Ch0TrEventPrms.masterEventHandle = NULL_PTR;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing valid parameters to Udma_eventRegister */
    Ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_DMA_COMPLETION;
    Ch0TrEventPrms.chHandle = &ch_Handle;
    eventHandleInt->vintrNum = 0U;
    eventHandleInt->nextEvent = 0U;
    eventHandleInt->hwiHandle = &gUdmaDrvObj[CONFIG_UDMA0];
    eventHandleInt->irIntrNum = 0U;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters with init the eventHandleInt->eventInitDone to satisfy the condition */
    eventHandleInt->eventInitDone = UDMA_INIT_DONE;
    retValue = Udma_eventDisable(Ch0TrEventHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters with NULL the eventHandleInt->drvHandle to satisfy the condition */
    eventHandleInt->eventInitDone = UDMA_INIT_DONE;
    eventHandleInt->drvHandle = NULL_PTR;
    retValue = Udma_eventDisable(Ch0TrEventHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters with de-init the eventHandleInt->eventInitDone to fail the condition */
    eventHandleInt->eventInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_eventDisable(NULL_PTR);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters with de-init the eventHandleInt->eventInitDone to fail the condition */
    retValue = Udma_eventEnable(Ch0TrEventHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters with NULL the eventHandleInt->drvHandle to fail the condition */
    eventHandleInt->eventInitDone = UDMA_INIT_DONE;
    eventHandleInt->drvHandle = NULL_PTR;
    retValue = Udma_eventEnable(Ch0TrEventHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters with assing valid address to eventHandleInt->drvHandle to satisfy the condition */
    eventHandleInt->drvHandle = (Udma_DrvHandleInt) &gUdmaDrvObj[CONFIG_UDMA0];
    retValue = Udma_eventEnable(Ch0TrEventHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing NULL to Udma_eventEnable fail the condition */
    eventHandleInt->eventInitDone = UDMA_DEINIT_DONE;
    retValue = Udma_eventEnable(NULL_PTR);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing NULL to Udma_eventGetGlobalHandle to satisfy the condition */
    Udma_eventGetGlobalHandle(NULL);
    /* Passing valid parameters with de-init drvHandleInt->drvInitDone to satisfy the condition */
    drvHandleInt->drvInitDone = UDMA_DEINIT_DONE;
    Udma_eventGetGlobalHandle(drvHandle);
    /* Passing valid parameters with init drvHandleInt->drvInitDone to fail the condition */
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    Udma_eventGetGlobalHandle(drvHandle);
    /* Passing valid parameters to execute the Udma_eventConfig */
    drvHandleInt->initPrms.enableUtc = TRUE;
    Udma_UtcInstInfo   Info;
    chHandle->utcInfo = &Info;
    Info.utcType = UDMA_UTC_TYPE_DRU;
    eventHandleInt->eventPrms.chHandle = chHandle;
    Ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_TR;
    Ch0TrEventPrms.eventMode = 0;
    Ch0TrEventPrms.masterEventHandle = NULL_PTR;
    ((Udma_EventHandleInt)Ch0TrEventPrms.masterEventHandle)->nextEvent = NULL_PTR;
    Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    /* Passing valid parameters to Udma_eventRegister */
    Ch0TrEventPrms.eventCb = Ch0TrEventHandle;
    Ch0TrEventPrms.preferredCoreIntrNum = 2;
    rmInitPrms->startIrIntr = 1;
    rmInitPrms->numIrIntr = 2;
    drvHandleInt->irIntrFlag[0] = 2;
    Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    /* Passing NULL to Udma_eventUnRegister returns UDMA_EBADARGS */
    retValue = Udma_eventUnRegister(NULL);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters to Udma_eventUnRegister to execute the Udma_eventCheckUnRegister */
    drvHandleInt->instType = UDMA_INST_TYPE_NORMAL;
    retValue = Udma_eventUnRegister(Ch0TrEventHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to Udma_eventUnRegister to execute the Udma_eventCheckUnRegister */
    eventHandleInt->eventInitDone = UDMA_INIT_DONE;
    Ch0TrEventPrms.masterEventHandle = NULL_PTR;
    eventHandleInt->nextEvent = (Udma_EventHandleInt) Ch0TrEventHandle;
    retValue = Udma_eventUnRegister(Ch0TrEventHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to Udma_eventUnRegister to execute the Udma_eventCheckUnRegister */
    eventHandleInt->nextEvent = (Udma_EventHandleInt) NULL_PTR;
    eventHandleInt->eventPrms.eventType = UDMA_INIT_DONE;
    retValue = Udma_eventUnRegister(Ch0TrEventHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters to Udma_eventUnRegister to execute the Udma_eventCheckUnRegister */
    eventHandleInt->drvHandle = (Udma_DrvHandleInt) UDMA_INIT_DONE;
    retValue = Udma_eventUnRegister(Ch0TrEventHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to Udma_eventUnRegister to execute the Udma_eventCheckUnRegister */
    eventHandleInt->drvHandle = NULL_PTR;
    eventHandleInt->drvHandle->drvInitDone = UDMA_INIT_DONE;
    retValue = Udma_eventUnRegister(Ch0TrEventHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to Udma_eventUnRegister to execute the Udma_eventReset */
    eventHandleInt->drvHandle = (Udma_DrvHandleInt) &gUdmaDrvObj[CONFIG_UDMA0];
    eventHandleInt->eventInitDone = UDMA_INIT_DONE;
    eventHandleInt->drvHandle->instType = UDMA_INST_TYPE_NORMAL;
    eventHandleInt->eventPrms.eventType = UDMA_EVENT_TYPE_TR;
    ch_Handle.chType = UDMA_CH_FLAG_RX;
    retValue = Udma_eventUnRegister(Ch0TrEventHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters to Udma_eventUnRegister to execute the Udma_eventReset */
    eventHandleInt->drvHandle = (Udma_DrvHandleInt) &gUdmaDrvObj[CONFIG_UDMA0];
    eventHandleInt->eventInitDone = UDMA_INIT_DONE;
    eventHandleInt->drvHandle->instType = UDMA_INST_TYPE_NORMAL;
    eventHandleInt->eventPrms.eventType = UDMA_EVENT_TYPE_TR;
    ch_Handle.chType = UDMA_CH_FLAG_TX;
    retValue = Udma_eventUnRegister(Ch0TrEventHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters to Udma_eventUnRegister to execute the Udma_eventReset */
    eventHandleInt->drvHandle = (Udma_DrvHandleInt) &gUdmaDrvObj[CONFIG_UDMA0];
    eventHandleInt->eventInitDone = UDMA_INIT_DONE;
    eventHandleInt->drvHandle->instType = UDMA_INST_TYPE_NORMAL;
    eventHandleInt->eventPrms.eventType = UDMA_EVENT_TYPE_TR;
    ch_Handle.chType = UDMA_CH_FLAG_PDMA;
    retValue = Udma_eventUnRegister(Ch0TrEventHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_EBADARGS, retValue);
    /* Passing valid parameters to Udma_eventUnRegister */
    eventHandleInt->drvHandle = (Udma_DrvHandleInt) &gUdmaDrvObj[CONFIG_UDMA0];
    eventHandleInt->drvHandle->drvInitDone = UDMA_INIT_DONE;
    eventHandleInt->drvHandle->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    eventHandleInt->eventPrms.eventType = UDMA_EVENT_TYPE_TEARDOWN_PACKET;
    retValue = Udma_eventUnRegister(Ch0TrEventHandle);
    TEST_ASSERT_EQUAL_INT32(UDMA_SOK, retValue);
    /* Passing valid parameters to Udma_eventRegister to execute the Udma_eventAllocResource */
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    Ch0TrEventPrms.eventMode = UDMA_EVENT_MODE_EXCLUSIVE;
    Ch0TrEventPrms.masterEventHandle = NULL_PTR;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to execute the Udma_eventRegister */
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    ch_Handle.chType = 4U;
    ch_Handle.cqRing = &ringNum;
    Ch0TrEventPrms.chHandle = &ch_Handle;
    drvHandleInt->instType = UDMA_INST_TYPE_NORMAL;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    /* Passing valid parameters to execute the Udma_eventAllocResource */
    drvHandleInt->drvInitDone = UDMA_INIT_DONE;
    eventHandleInt->eventPrms.eventType = UDMA_EVENT_TYPE_MASTER;
    Ch0TrEventPrms.eventMode = UDMA_EVENT_TYPE_RING;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    /* Passing valid parameters to execute the Udma_eventAllocResource */
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    /* Passing valid parameters to execute the Udma_eventAllocResource */
    Ch0TrEventPrms.eventCb = NULL_PTR;
    Ch0TrEventPrms.masterEventHandle = NULL_PTR;
    eventHandleInt->eventPrms.eventType = UDMA_EVENT_TYPE_TR;
    ((Udma_EventHandleInt)Ch0TrEventPrms.masterEventHandle)->nextEvent = NULL_PTR;
    ((Udma_ChHandleInt)Ch0TrEventPrms.chHandle)->chOesAllocDone = TRUE;
    retValue = Udma_eventRegister(drvHandle, Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EALLOC, retValue);
    /* Passing valid parameters to execute the Udma_eventConfig */
    Ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_TEARDOWN_PACKET;
    retValue = Udma_eventRegister(drvHandle,Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to execute the Udma_eventConfig */
    Ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_TEARDOWN_COMPLETION;
    retValue = Udma_eventRegister(drvHandle,Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to execute the Udma_eventConfig */
    Ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_RING;
    ((Udma_RingHandleInt)Ch0TrEventPrms.ringHandle)->mappedRingGrp = 3;
    retValue = Udma_eventRegister(drvHandle,Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing valid parameters to execute the Udma_eventConfig */
    Ch0TrEventPrms.eventType = UDMA_EVENT_TYPE_RING;
    ((Udma_RingHandleInt)Ch0TrEventPrms.ringHandle)->mappedRingGrp = 10;
    retValue = Udma_eventRegister(drvHandle,Ch0TrEventHandle, &Ch0TrEventPrms);
    TEST_ASSERT_EQUAL_INT32(UDMA_EFAIL, retValue);
    /* Passing NULL value to Udma_eventGetId fail the condition */
    Udma_eventGetId(NULL_PTR);
    /* Passing valid parameters with de-init eventHandleInt->eventInitDone fail the condition */
    eventHandleInt->eventInitDone = UDMA_DEINIT_DONE;
    Udma_eventGetId(Ch0TrEventHandle);
    /* Passing valid parameters and assigning NULL to eventHandleInt->drvHandle fail the condition */
    eventHandleInt->eventInitDone = UDMA_INIT_DONE;
    eventHandleInt->drvHandle = NULL_PTR;
    Udma_eventGetId(Ch0TrEventHandle);

    DebugP_log("\r\n udma event dynamic coverage test...\r\n");

    return;
}

static void test_udma_dyn_coverage(void *args)
{
    test_udma_event();

    test_udma_utils();

    test_udma_flow();

    test_udma_rm();

    test_udma_ring_lcdma();

    test_udma_ring_common();

    test_udma_ch();

    test_udma();

    return;
}
