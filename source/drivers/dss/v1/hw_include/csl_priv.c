/*
 *  Copyright (C) 2025-2026 Texas Instruments Incorporated
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
 *  \file csl_priv.c
 *
 *  \brief File containing implementation of DSI specific reg read/write.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/dss.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define DSI_TOP                    (CSL_DSS_DSI0_DSI_TOP_VBUSP_CFG_DSI_0_DSI_BASE)
#define DSI_TOP_SIZE               (DSI_TOP + CSL_DSS_DSI0_DSI_TOP_VBUSP_CFG_DSI_0_DSI_SIZE)
#define DSI_WRAPPER                (CSL_DSS_DSI0_DSI_WRAP_MMR_VBUSP_CFG_DSI_WRAP_BASE)
#define DSI_WRAPPER_SIZE           (DSI_WRAPPER + CSL_DSS_DSI0_DSI_WRAP_MMR_VBUSP_CFG_DSI_WRAP_SIZE)
#define DSI_DPHY                   (CSL_DPHY_TX0_BASE)
#define DSI_DPHY_SIZE              (DSI_DPHY + CSL_DPHY_TX0_SIZE)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

uint32_t CPS_ReadReg32(volatile uint32_t* address)
{
    uint32_t data;
    uintptr_t address_int = (uintptr_t)address;

    if (((address_int >= DSI_TOP) && (address_int < DSI_TOP_SIZE)) ||
             ((address_int >= DSI_DPHY) && (address_int < DSI_DPHY_SIZE)) ||
             ((address_int >= DSI_WRAPPER) && (address_int < DSI_WRAPPER_SIZE)))
    {
        data = CSL_REG32_RD(address_int);
    }
    else
    {
        GT_1trace(DssTrace,
                  GT_ERR,
                  "Address %d (read) doesn't map to any DP bus",
                  address);
        data = 0u;
    }

    return data;
}

void CPS_WriteReg32(volatile uint32_t* address, uint32_t value)
{
    uintptr_t address_int = (uintptr_t)address;

    if (((address_int >= DSI_TOP) && (address_int < DSI_TOP_SIZE)) ||
             ((address_int >= DSI_DPHY) && (address_int < DSI_DPHY_SIZE)) ||
             ((address_int >= DSI_WRAPPER) && (address_int < DSI_WRAPPER_SIZE)))
    {
        CSL_REG32_WR(address_int, value);
    }
    else
    {
        GT_1trace(DssTrace,
                  GT_ERR,
                  "Address %d (write) doesn't map to any DP bus",
                  address);
    }
}
