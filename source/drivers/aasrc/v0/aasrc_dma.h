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

/**
 *  \ingroup DRV_AASRC_MODULE
 *  \defgroup DRV_AASRC_DMA_MODULE AASRC DMA
 *            This is AASRC dma related APIs, parameters and
 *            local functions
 *
 *  @{
 */

/**
 *  \file v0/aasrc_dma.h
 *
 *  \brief AASRC dma related parameters and APIs
 */

 #ifndef AASRC_DMA_H_
 #define AASRC_DMA_H_

 /* ========================================================================== */
 /*                             Include Files                                  */
 /* ========================================================================== */

 /* None */

 #ifdef __cplusplus
 extern "C" {
 #endif

 /* ========================================================================== */
 /*                           Macros & Typedefs                                */
 /* ========================================================================== */

 /* Element count in Tx Ring */
#define  AASRC_TX_DMA_RING_ELEM_CNT         (1U)

/* TR count in TX TRPD */
#define  AASRC_TX_DMA_TR_COUNT              (64U)

/* Element count in Rx Ring */
#define  AASRC_RX_DMA_RING_ELEM_CNT         (1U)

/* TR count in RX TRPD */
#define  AASRC_RX_DMA_TR_COUNT              (64U)

#define AASRC_DMA_L0_MAX_XFER_SIZE          (65535U)
#define AASRC_DMA_UDMA_XFER_SIZE            (64512U)
#define AASRC_DMA_TX_CH_FIFO_DEPTH          (128U)
#define AASRC_DMA_RX_CH_FIFO_DEPTH          (128U)

#define AASRC_UDMA_TRPD_MEM_SIZE_TX         (UDMA_GET_TRPD_TR3_SIZE(AASRC_TX_DMA_TR_COUNT))
#define AASRC_UDMA_TRPD_MEM_SIZE_RX         (UDMA_GET_TRPD_TR3_SIZE(AASRC_RX_DMA_TR_COUNT))

#define AASRC_UDMA_RING_ENTRY_SIZE          (sizeof(uint64_t))
#define AASRC_UDMA_RING_MEM_SIZE_TX         (AASRC_TX_DMA_RING_ELEM_CNT * AASRC_UDMA_RING_ENTRY_SIZE)
#define AASRC_UDMA_RING_MEM_SIZE_RX         (AASRC_RX_DMA_RING_ELEM_CNT * AASRC_UDMA_RING_ENTRY_SIZE)

/* DMA perpertual reload count */
#define AASRC_DMA_PERPETUAL_RELOAD_CNT      (0x1FFU)

#define WORD_BYTE_COUNT                     (4U)

#define AASRC_INVALID_TXN_IDX               (0xDEADBEEFU)

#define AASRC_ICNT2_MAX                     (65535U)

 /* ========================================================================== */
 /*                         Structure Declarations                             */
 /* ========================================================================== */

 /**
  *  \brief Data structure used to store DMA channel configuration
  *
  */

typedef struct AASRC_DMAChConfig_s
{
    void            *txChHandle;
    /**< UDMA channel tx handle */
    void            *rxChHandle;
    /**< UDMA channel rx handle */
    void            *cqTxEvtHandle;
    /**< UDMA cq tx event handle */
    void            *cqRxEvtHandle;
    /**< UDMA cq rx event handle */
    void            *txTrpdMem;
    /**< UDMA TX TRPD memory pointers */
    void            *rxTrpdMem;
    /**< UDMA RX TRPD memory pointers */
    uint32_t        trpdMemSize;
    /**< Size of TR PD memory */
    void            *txRingMem;
    /**< UDMA TX Ring memory pointers */
    void            *rxRingMem;
    /**< UDMA RX Ring memory pointers */
    void            *txCbParams;
    /**< UDMA TX callback params */
    void            *rxCbParams;
    /**< UDMA RX callback params */
    uint32_t        rxEvtNum;
    /**< UDMA Event number used for Rx */
    uint32_t        txEvtNum;
    /**< UDMA Event number used for Tx */
    uint32_t        isOpen;
    /**< Flag to indicate whether the DMA instance is opened already */
}AASRC_DmaChCfg;

 typedef struct
{
    uint8_t initDone;
    /**< Flag to indicate if the ICNT is initialized */
    uint32_t txnByteCnt;
    /**< Byte count for the TR */
    uint16_t icnt0;
    /**< ICNT0 value for the TR */
    uint16_t icnt1;
    /**< ICNT1 value for the TR */
    uint16_t icnt2;
    /**< ICNT2 value for the TR */
    uint16_t icnt3;
    /**< ICNT3 value for the TR */
} AASRC_DmaIcnt;


/* ========================================================================== */
/*                         API Function Declarations                          */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       Local Function Definitions                           */
/* ========================================================================== */

/**
 *  \brief Function opens an UDMA channel for AASRC channel RX/TX
 *
 *  Connects AASRC RX with UDMA TX and AASRC TX with UDMA RX
 *
 *  \param chHandle                 [IN] channel handle to identify AASRC channel
 *                                       (returned from AASRC_chOpen())
 *
 *  \return \ref AASRC_ErrorCodes
 */
int32_t AASRC_dmaChOpen(AASRC_ChHandle chHandle);

/**
 *  \brief Function enables the UDMA channel for AASRC channel RX/TX
 *
 *  Enables the dma and create TRPDs
 *
 *  \param chHandle                 [IN] channel handle to identify AASRC channel
 *                                       (returned from AASRC_chOpen())
 *
 *  \return \ref AASRC_ErrorCodes
 */
int32_t AASRC_dmaChEnable(AASRC_ChHandle chHandle);

/**
 *  \brief Function disables the UDMA channel for AASRC channel RX/TX
 *
 *  Disables the dma. This will in turn clear out all the BCDMA/PDMA FIFOs,
 *  clearout all the TRPDs from the ring (teardown the channel)
 *
 *  \param chHandle                 [IN] channel handle to identify AASRC channel
 *                                       (returned from AASRC_chOpen())
 *
 *  \return \ref AASRC_ErrorCodes
 */
int32_t AASRC_dmaChDisable(AASRC_ChHandle chHandle);

/**
 *  \brief Function closes the UDMA channel for AASRC channel RX/TX
 *
 *  Flushes pending TRPDs from the queue and closes the DMA channel
 *
 *  \param chHandle                 [IN] channel handle to identify AASRC channel
 *                                       (returned from AASRC_chOpen())
 *
 *  \return \ref AASRC_ErrorCodes
 */
int32_t AASRC_dmaChClose(AASRC_ChHandle chHandle);

/**
 *  \brief Function disables the UDMA channel for AASRC channel Tx
 *
 *  \param chHandle                 [IN] channel handle to identify AASRC channel
 *                                       (returned from AASRC_chOpen())
 *
 *  \return \ref AASRC_ErrorCodes
 */
int32_t AASRC_disableDmaRx(AASRC_ChHandle chHandle);

/**
 *  \brief Function disables the UDMA channel for AASRC channel Rx
 *
 *  \param chHandle                 [IN] channel handle to identify AASRC channel
 *                                       (returned from AASRC_chOpen())
 *
 *  \return \ref AASRC_ErrorCodes
 */
int32_t AASRC_disableDmaTx(AASRC_ChHandle chHandle);


#ifdef __cplusplus
}
#endif

#endif /* #ifndef AASRC_DMA_H_ */

/** @} */
