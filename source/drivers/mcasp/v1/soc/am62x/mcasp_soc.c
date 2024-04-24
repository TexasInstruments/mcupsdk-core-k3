/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
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

#include <drivers/mcasp.h>
#include <drivers/soc.h>
#include "mcasp_soc.h"

/* ========================================================================== */
/*                             Macro Definitions                              */
/* ========================================================================== */
#define MCASP_HCLK_MUX_MAX_VAL      (0x3U)

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t MCASP_extHclkSrcConfig(uint32_t instNum, uint32_t source, uint32_t dir)
{
    int32_t status = SystemP_SUCCESS;

    if(source > MCASP_HCLK_MUX_MAX_VAL)
    {
        status = SystemP_FAILURE;
    }

    if (status == SystemP_SUCCESS)
    {
        SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MAIN, 2);

        switch (instNum)
        {
            case MCASP0:
                if(dir == MCASP_DIR_OUT)
                {
                    CSL_REG32_FINS(CSL_CTRL_MMR0_CFG0_BASE + CSL_MAIN_CTRL_MMR_CFG0_MCASP0_AHCLKSEL,
                                MAIN_CTRL_MMR_CFG0_MCASP0_AHCLKSEL_AHCLKX_SEL, source);
                }
                else if(dir == MCASP_DIR_IN)
                {
                    CSL_REG32_FINS(CSL_CTRL_MMR0_CFG0_BASE + CSL_MAIN_CTRL_MMR_CFG0_MCASP0_AHCLKSEL,
                                MAIN_CTRL_MMR_CFG0_MCASP0_AHCLKSEL_AHCLKR_SEL, source);
                }
                else
                {
                    status = SystemP_FAILURE;
                }
                break;

            case MCASP1:
                if(dir == MCASP_DIR_OUT)
                {
                    CSL_REG32_FINS(CSL_CTRL_MMR0_CFG0_BASE + CSL_MAIN_CTRL_MMR_CFG0_MCASP1_AHCLKSEL,
                                MAIN_CTRL_MMR_CFG0_MCASP1_AHCLKSEL_AHCLKX_SEL, source);
                }
                else if(dir == MCASP_DIR_IN)
                {
                    CSL_REG32_FINS(CSL_CTRL_MMR0_CFG0_BASE + CSL_MAIN_CTRL_MMR_CFG0_MCASP1_AHCLKSEL,
                                MAIN_CTRL_MMR_CFG0_MCASP1_AHCLKSEL_AHCLKR_SEL, source);
                }
                else
                {
                    status = SystemP_FAILURE;
                }
                break;

            case MCASP2:
                if(dir == MCASP_DIR_OUT)
                {
                    CSL_REG32_FINS(CSL_CTRL_MMR0_CFG0_BASE + CSL_MAIN_CTRL_MMR_CFG0_MCASP2_AHCLKSEL,
                                MAIN_CTRL_MMR_CFG0_MCASP2_AHCLKSEL_AHCLKX_SEL, source);
                }
                else if(dir == MCASP_DIR_IN)
                {
                    CSL_REG32_FINS(CSL_CTRL_MMR0_CFG0_BASE + CSL_MAIN_CTRL_MMR_CFG0_MCASP2_AHCLKSEL,
                                MAIN_CTRL_MMR_CFG0_MCASP2_AHCLKSEL_AHCLKR_SEL, source);
                }
                else
                {
                    status = SystemP_FAILURE;
                }
                break;

            default:
                status = SystemP_FAILURE;
                break;
        }

        SOC_controlModuleLockMMR(SOC_DOMAIN_ID_MAIN, 2);
    }

    return status;
}
