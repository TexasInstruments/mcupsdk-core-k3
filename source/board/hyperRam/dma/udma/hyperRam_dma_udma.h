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
 *  \defgroup HYPERRAM_UDMA APIs for HYPERRAM UDMA mode
 *  \ingroup HYPERRAM_DMA_UDMA_MODULE
 *
 *  This module contains APIs to program and use UDMA driver with HYPERRAM.
 *
 *  @{
 */

/**
 *  \file hyperRam_dma_udma.h
 *
 *  \brief HYPERRAM DMA header file.
 */

#ifndef HYPERRAM_DMA_UDMA_H_
#define HYPERRAM_DMA_UDMA_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <drivers/udma.h>

#ifdef __cplusplus
extern "C"
{
#endif


/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct HyperRamDma_UdmaArgs_s
{
    void            *drvHandle;
    /**< UDMA driver handle */
    void            *chHandle;
    /**< UDMA channel handle */
    void            *trpdMem;
    /**< UDMA TR PD memory pointers */
    uint32_t        trpdMemSize;
    /**< Size of TR PD memory */
    void            *ringMem;
    /**< UDMA Ring memory pointers */
    uint32_t        ringMemSize;
    /**< Size of Ring Memory */
    uint32_t        ringElemCount;
    /**< Ring Element Count */

} HyperRamDma_UdmaArgs;

/* ========================================================================== */
/*                  Internal/Private Structure Declarations                   */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       Function Declarations                                */
/* ========================================================================== */

extern HYPERRAM_DmaFxns gHyperRamDmaUdmaFxns;

extern uint64_t Udma_virtToPhyFxn(const void *virtAddr,
    Udma_DrvHandle drvHandle,
    Udma_ChHandle chHandle);

#ifdef __cplusplus
}
#endif

#endif /* HYPERRAM_DMA_UDMA_H_ */
