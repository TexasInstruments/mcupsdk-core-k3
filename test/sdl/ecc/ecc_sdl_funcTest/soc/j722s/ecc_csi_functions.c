/*
 *   Copyright (C) Texas Instruments Incorporated 2024-25
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
 *  \file     ecc_csi_functions.c
 *
 *  \brief    This file contains helper functions for testing the CSI ECC Aggr.
 *
 *  \details  ECC Test CSI helper functions
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <sdl/include/sdl_types.h>
#include <sdl/sdl_ecc.h>
#include <dpl_interface.h>
#include <drivers/hw_include/cslr_soc.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/AddrTranslateP.h>


/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

#define CSI0_RX_ESM_FATAL_ERROR     SDLR_ESM0_ESM_LVL_EVENT_CSI_RX_IF0_CSI_FATAL_0
#define CSI1_RX_ESM_FATAL_ERROR     SDLR_ESM0_ESM_LVL_EVENT_CSI_RX_IF1_CSI_FATAL_0
#define CSI2_RX_ESM_FATAL_ERROR     SDLR_ESM0_ESM_LVL_EVENT_CSI_RX_IF2_CSI_FATAL_0
#define CSI3_RX_ESM_FATAL_ERROR     SDLR_ESM0_ESM_LVL_EVENT_CSI_RX_IF3_CSI_FATAL_0
#define CSI0_TX_ESM_FATAL_ERROR     SDLR_ESM0_ESM_LVL_EVENT_CSI_TX_IF0_CSI_FATAL_0

#define SDL_CSI_REG_TEST_OFFSET     0x8U
#define SDL_CSI_REG_EVT_OFFSET      0x4U

/* ========================================================================== */
/*                 Global Variables                                           */
/* ========================================================================== */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                 Function Definitions                                       */
/* ========================================================================== */

/* ========================================================================== */
/*                 EXternal Function Definitions                              */
/* ========================================================================== */

bool sdl_ecc_isCsiEvent(uint32_t intSrc)
{
    bool isCsiEvent = (bool)false;

    if (intSrc == CSI0_RX_ESM_FATAL_ERROR ||
        intSrc == CSI1_RX_ESM_FATAL_ERROR ||
        intSrc == CSI2_RX_ESM_FATAL_ERROR ||
        intSrc == CSI3_RX_ESM_FATAL_ERROR ||
        intSrc == CSI0_TX_ESM_FATAL_ERROR)
    {
        isCsiEvent = (bool)true;
    }

    return isCsiEvent;
}

uint32_t csi_getAggrAddrByIntSrc(uint32_t intSrc)
{
    uint32_t addr = 0x0U;

    if (intSrc == CSI0_RX_ESM_FATAL_ERROR)
    {
        addr = CSL_CSI_RX_IF0_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_BASE + 0x900U;
    }
    else if (intSrc == CSI1_RX_ESM_FATAL_ERROR)
    {
        addr = CSL_CSI_RX_IF1_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_BASE + 0x900U;
    }
    else if (intSrc == CSI2_RX_ESM_FATAL_ERROR)
    {
        addr = CSL_CSI_RX_IF2_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_BASE + 0x900U;
    }
    else if (intSrc == CSI3_RX_ESM_FATAL_ERROR)
    {
        addr = CSL_CSI_RX_IF3_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_BASE + 0x900U;
    }
    else if (intSrc == CSI0_TX_ESM_FATAL_ERROR)
    {
        addr = CSL_CSI_TX_IF0_VBUS2APB_WRAP_VBUSP_APB_CSI2TX_V2_BASE + 0xE00U;
    }

    return addr;
}

void csi_processEccEvent(uint32_t intSrc)
{
    uint32_t addr = csi_getAggrAddrByIntSrc(intSrc);
    uint32_t regVal;

    /*
     * To trigger the error on checker 0, a write to 0x30101908 was performed.
     * This caused the bit error to propogate to the same register.
     * In order to be able to clear the error event, we need to correct the
     * register contents to the expected value first.
     */
    *(uint32_t *)(AddrTranslateP_getLocalAddr(addr + SDL_CSI_REG_TEST_OFFSET)) = 0x70U;

    /* Now, clear the CSI error event at the source */
    regVal = *(uint32_t *)(AddrTranslateP_getLocalAddr(addr + SDL_CSI_REG_EVT_OFFSET));
    *(uint32_t *)(AddrTranslateP_getLocalAddr(addr + SDL_CSI_REG_EVT_OFFSET)) = regVal;

    return;
}

bool csi_isCsiAggr(uint32_t mainMem)
{
    bool isCsiAggr = (bool)false;

    if ((mainMem == SDL_CSI_RX_IF3_CSI_RX_IF_ECC_AGGR) ||
        (mainMem == SDL_CSI_RX_IF1_CSI_RX_IF_ECC_AGGR) ||
        (mainMem == SDL_CSI_RX_IF0_CSI_RX_IF_ECC_AGGR) ||
        (mainMem == SDL_CSI_TX_IF0_CSI_TX_IF_V2_ECC_AGGR) ||
        (mainMem == SDL_CSI_RX_IF2_CSI_RX_IF_ECC_AGGR))
    {
        isCsiAggr = (bool)true;
    }


    return isCsiAggr;
}

/* CSI addr lookup helper function */
uint32_t csi_getAggrAddr(uint32_t mainMem)
{
    uint32_t addr = 0U;
    uint32_t offset = 0x908;

    if (mainMem == SDL_CSI_RX_IF3_CSI_RX_IF_ECC_AGGR)
    {
        addr = CSL_CSI_RX_IF3_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_BASE + offset;
    }
    else if (mainMem == SDL_CSI_RX_IF2_CSI_RX_IF_ECC_AGGR)
    {
        addr = CSL_CSI_RX_IF2_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_BASE + offset;
    }
    else if (mainMem == SDL_CSI_RX_IF1_CSI_RX_IF_ECC_AGGR)
    {
        addr = CSL_CSI_RX_IF1_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_BASE + offset;
    }
    else if (mainMem == SDL_CSI_RX_IF0_CSI_RX_IF_ECC_AGGR)
    {
        addr = CSL_CSI_RX_IF0_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_BASE + offset;
    }
    else if (mainMem == SDL_CSI_TX_IF0_CSI_TX_IF_V2_ECC_AGGR)
    {
        addr = CSL_CSI_TX_IF0_VBUS2APB_WRAP_VBUSP_APB_CSI2TX_V2_BASE + 0xE08;
    }

    return addr;
}

int32_t csi_injectEccError(uint32_t mainMem, uint32_t i, uint32_t intsrc, uint32_t j,
                           SDL_ECC_InjectErrorConfig_t *injectErrorConfig)
{
    int32_t result = 0x0u;
    uint32_t regVal = 0x0u;
    uint32_t addr = 0x0u;
    /*
     * Although the endpoint is interconnect type, for CSI-RX, this
     * interconnect endpoint is still inject-only, and also requires
     * traffic on the endpoint in order for the error to propagate.
     * Therefore, we have special handling for this case
     * Steps:
     *     1. Inject the error
     *     2. Perform read of the CSI interface
     *     3. Wait for the ESM error event to be triggered
     */
    /* 1. Inject the error */
    result = SDL_ECC_injectError(mainMem, i, intsrc, injectErrorConfig);
    /* Wait for some time for error to inject */
    ClockP_usleep(50);
    /* 2. Perform read access by reading the CSI registers */
    addr = csi_getAggrAddr(mainMem);
    regVal = *(uint32_t *)(AddrTranslateP_getLocalAddr(addr));
    *(uint32_t *)(AddrTranslateP_getLocalAddr(addr)) = regVal;

    return result;
}

int32_t sdlInit_CsiEcc(void)
{
    SDL_ErrType_t ret = SDL_PASS;

    /* Initialize the ASF registers to report parity errors */

    /*
     * set csi_rx_if_asf_int_mask register un-mask ECC error events
     * An ECC error on endpoint 0, checker 0 will result in the CSR error event.
     * An ECC error on endpoint 0, checker 1 will result in the DAP error event.
     */
    *(uint32_t *)(AddrTranslateP_getLocalAddr(CSL_CSI_RX_IF0_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_BASE + 0x908U)) = 0x70;
    *(uint32_t *)(AddrTranslateP_getLocalAddr(CSL_CSI_RX_IF1_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_BASE + 0x908U)) = 0x70;
    *(uint32_t *)(AddrTranslateP_getLocalAddr(CSL_CSI_RX_IF2_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_BASE + 0x908U)) = 0x70;
    *(uint32_t *)(AddrTranslateP_getLocalAddr(CSL_CSI_RX_IF3_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_BASE + 0x908U)) = 0x70;
    *(uint32_t *)(AddrTranslateP_getLocalAddr(CSL_CSI_TX_IF0_VBUS2APB_WRAP_VBUSP_APB_CSI2TX_V2_BASE + 0xE08U)) = 0x70;

    /*
     * set csi_rx_if_asf_fatal_nonfatal_select to 1's to set all errors as fatal
     * This will trigger the ESM event SDLR_ESM0_ESM_LVL_EVENT_CSI_RX_IF0_COMMON_0_CSI_FATAL_0
     */
    *(uint32_t *)(AddrTranslateP_getLocalAddr(CSL_CSI_RX_IF0_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_BASE + 0x910U)) = 0x7F;
    *(uint32_t *)(AddrTranslateP_getLocalAddr(CSL_CSI_RX_IF1_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_BASE + 0x910U)) = 0x7F;
    *(uint32_t *)(AddrTranslateP_getLocalAddr(CSL_CSI_RX_IF2_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_BASE + 0x910U)) = 0x7F;
    *(uint32_t *)(AddrTranslateP_getLocalAddr(CSL_CSI_RX_IF3_VBUS2APB_WRAP_VBUSP_APB_CSI2RX_BASE + 0x910U)) = 0x7F;
    *(uint32_t *)(AddrTranslateP_getLocalAddr(CSL_CSI_TX_IF0_VBUS2APB_WRAP_VBUSP_APB_CSI2TX_V2_BASE + 0xE10U)) = 0x7F;

    return ret;
}

/* Nothing past this point */
