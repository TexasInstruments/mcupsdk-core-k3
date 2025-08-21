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
 *  \defgroup HYPERRAM_DMA APIs for HYPERRAM DMA mode
 *  \ingroup HYPERRAM_DMA_MODULE
 *
 *  This module contains APIs to program and use the DMA drivers available in the SoC with HYPERRAM.
 *  @{
 */

/**
 *  \file hyperRam_dma.h
 *
 *  \brief HYPERRAM DMA header file.
 */

#ifndef HYPERRAM_DMA_H_
#define HYPERRAM_DMA_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <kernel/dpl/SystemP.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * \brief Handle to the HYPERRAM DMA Config Object returned by \ref HYPERRAM_dmaOpen
 */
typedef void* HYPERRAM_DmaHandle;

/**
 * \brief Driver implementation to open a specific DMA driver channel - UDMA, EDMA etc
 *
 * Typically this callback is hidden from the end application and is implemented
 * when a new DMA driver needs to be supported.
 *
 * \param hyperRamDmaArgs   [in] DMA specific arguments, obtained from the config
 *
 * \return SystemP_SUCCESS on success, else failure
 */
typedef int32_t (*HYPERRAM_dmaOpenFxn)(void *hyperRamDmaArgs);

/**
 * \brief Driver implementation to close a specific DMA driver channel - UDMA, EDMA etc
 *
 * Typically this callback is hidden from the end application and is implemented
 * when a new DMA driver needs to be supported.
 *
 * \param HYPERRAM_DmaHandle   [in] HYPERRAM DMA Object handle returned from \ref HYPERRAM_dmaOpen
 * \param hyperRamDmaArgs      [in] DMA specific arguments, obtained from the config
 *
 * \return SystemP_SUCCESS on success, else failure
 */
typedef int32_t (*HYPERRAM_dmaCloseFxn)(HYPERRAM_DmaHandle, void *hyperRamDmaArgs);

/**
 * \brief Driver implementation to do a DMA copy using a specific DMA driver - UDMA, EDMA etc
 *
 * Typically this callback is hidden from the end application and is implemented
 * when a new DMA driver needs to be supported.
 *
 * \param hyperRamDmaArgs   [in] DMA specific arguments, obtained from the config
 * \param dst           [in] Destination address to which the data is to be copied
 * \param src           [in] Source address from which the data is to be copied
 * \param length        [in] Data length
 *
 * \return SystemP_SUCCESS on success, else failure
 */
typedef int32_t (*HYPERRAM_dmaCopyFxn)(void *hyperRamDmaArgs, void *dst, void *src, uint32_t length);

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 * \brief Driver implementation callbacks
 */
typedef struct HYPERRAM_DmaFxns_s
{
	HYPERRAM_dmaOpenFxn    dmaOpenFxn;
	HYPERRAM_dmaCloseFxn   dmaCloseFxn;
	HYPERRAM_dmaCopyFxn    dmaCopyFxn;

} HYPERRAM_DmaFxns;

/**
 * \brief HYPERRAM DMA Configuration, these are filled by SysCfg based on the DMA driver that is selected
 */
typedef struct HYPERRAM_DmaConfig_s
{
	HYPERRAM_DmaFxns *fxns;
	/* Registered callbacks for a particular DMA driver. This will be set by Sysconfig depending on the DMA driver selected*/
	void *hyperRamDmaArgs;
	/* Arguments specific to a DMA driver. This will be typecasted to the specific DMA driver args struct
	 * when used by the appropriate callback. This struct will be defined in the specific DMA driver header file.
	 * Allocation of this struct will be done statically using Sysconfig code generation in the example code
	 */

} HYPERRAM_DmaConfig;

/* ========================================================================== */
/*                  Internal/Private Structure Declarations                   */
/* ========================================================================== */

/* ========================================================================== */
/*                       Function Declarations                                */
/* ========================================================================== */

/**
 * \brief API to open an HYPERRAM DMA channel
 *
 * This API will open a DMA Channel using the appropriate DMA driver callbacks and the registered via Sysconfig
 *
 * \param index [in] Index of the DMA Config selected for this particular HYPERRAM driver instance
 *
 * \return Handle to the HYPERRAM DMA Config Object
 */
HYPERRAM_DmaHandle HYPERRAM_dmaOpen(int32_t index);

/**
 * \brief API to close an HYPERRAM DMA channel
 *
 * This API will open a DMA Channel using the appropriate DMA driver callbacks registered via Sysconfig
 *
 * \param index [in] Handle to the HYPERRAM DMA Config Object returned from \ref HYPERRAM_dmaOpen
 *
 * \return SystemP_SUCCESS on success, else failure
 */
int32_t HYPERRAM_dmaClose(HYPERRAM_DmaHandle handle);

/**
 * \brief API to do a DMA Copy using appropriate DMA Channel opened
 *
 * This API will open a DMA Channel using the appropriate DMA driver callbacks registered via Sysconfig
 *
 * \param handle        [in] Handle to the HYPERRAM DMA Config Object returned from \ref HYPERRAM_dmaOpen
 * \param dst           [in] Destination address to which the data is to be copied
 * \param src           [in] Source address from which the data is to be copied
 * \param length        [in] Data length
 *
 * \return SystemP_SUCCESS on success, else failure
 */
int32_t HYPERRAM_dmaCopy(HYPERRAM_DmaHandle handle, void* dst, void* src, uint32_t length);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* HYPERRAM_DMA_H_ */
