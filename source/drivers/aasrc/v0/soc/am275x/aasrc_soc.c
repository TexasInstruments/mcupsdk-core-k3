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

#include "../../aasrc.h"
#include "aasrc_soc.h"

/* ========================================================================== */
/*                             Macro Definitions                              */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                      API Function Definitions                              */
/* ========================================================================== */

int32_t AASRC_audioPllDivConfig(void)
{
    int32_t status = AASRC_SOK;

    if (status == AASRC_SOK)
    {
        SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MAIN, 2U);
        /* set the divider value as (x+1), programmer should set only x,  (check spec)*/
        CSL_REG32_FINS(CSL_MAIN_CTRL_MMR_CFG0_REGS_BASE + CSL_MAIN_CTRL_MMR_CFG0_ASRC_SYNC_DIV_CTRL,
                        MAIN_CTRL_MMR_CFG0_ASRC_SYNC_DIV_CTRL_CLK_DIV, AASRC_DIV_PLL4_HSDIV3_DIVISOR);

        /* send the load signal to hardware divider */
        CSL_REG32_FINS(CSL_MAIN_CTRL_MMR_CFG0_REGS_BASE + CSL_MAIN_CTRL_MMR_CFG0_ASRC_SYNC_DIV_CTRL,
                    MAIN_CTRL_MMR_CFG0_ASRC_SYNC_DIV_CTRL_CLK_DIV_LD, 1U);
        SOC_controlModuleLockMMR(SOC_DOMAIN_ID_MAIN, 2U);
    }

    return status;
}

int32_t AASRC_extClkSrcRxConfig(uint32_t instNum, uint32_t rxsync, uint32_t clk_source)
{
    int32_t status =  AASRC_SOK;

    if(clk_source > AASRC_EXTERNAL_CLOCK_SRC_MAX_VAL)
    {
        status = AASRC_EINVALID_PARAMS;
    }

    if (status == AASRC_SOK)
    {
        SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MAIN, 2U);

        switch (instNum)
        {
            case AASRC0:
                switch (rxsync)
                {
                    case AASRC_RXSYNC0_IDX:
                        CSL_REG32_FINS(CSL_MAIN_CTRL_MMR_CFG0_REGS_BASE + CSL_MAIN_CTRL_MMR_CFG0_ASRC0_RXSYNC0_SEL,
                                       MAIN_CTRL_MMR_CFG0_ASRC0_RXSYNC0_SEL_SYNC_SEL, clk_source);
                        break;
                    case AASRC_RXSYNC1_IDX:
                        CSL_REG32_FINS(CSL_MAIN_CTRL_MMR_CFG0_REGS_BASE + CSL_MAIN_CTRL_MMR_CFG0_ASRC0_RXSYNC1_SEL,
                                       MAIN_CTRL_MMR_CFG0_ASRC0_RXSYNC1_SEL_SYNC_SEL, clk_source);
                        break;
                    case AASRC_RXSYNC2_IDX:
                        CSL_REG32_FINS(CSL_MAIN_CTRL_MMR_CFG0_REGS_BASE + CSL_MAIN_CTRL_MMR_CFG0_ASRC0_RXSYNC2_SEL,
                                       MAIN_CTRL_MMR_CFG0_ASRC0_RXSYNC2_SEL_SYNC_SEL, clk_source);
                        break;
                    case AASRC_RXSYNC3_IDX:
                        CSL_REG32_FINS(CSL_MAIN_CTRL_MMR_CFG0_REGS_BASE + CSL_MAIN_CTRL_MMR_CFG0_ASRC0_RXSYNC3_SEL,
                                       MAIN_CTRL_MMR_CFG0_ASRC0_RXSYNC3_SEL_SYNC_SEL, clk_source);
                        break;
                    default:
                        status = AASRC_EINVALID_PARAMS;
                        break;
                }
                break;

            case AASRC1:
                switch (rxsync)
                {
                    case AASRC_RXSYNC0_IDX:
                        CSL_REG32_FINS(CSL_MAIN_CTRL_MMR_CFG0_REGS_BASE + CSL_MAIN_CTRL_MMR_CFG0_ASRC1_RXSYNC0_SEL,
                                       MAIN_CTRL_MMR_CFG0_ASRC1_RXSYNC0_SEL_SYNC_SEL, clk_source);
                        break;
                    case AASRC_RXSYNC1_IDX:
                        CSL_REG32_FINS(CSL_MAIN_CTRL_MMR_CFG0_REGS_BASE + CSL_MAIN_CTRL_MMR_CFG0_ASRC1_RXSYNC1_SEL,
                                       MAIN_CTRL_MMR_CFG0_ASRC1_RXSYNC1_SEL_SYNC_SEL, clk_source);
                        break;
                    case AASRC_RXSYNC2_IDX:
                        CSL_REG32_FINS(CSL_MAIN_CTRL_MMR_CFG0_REGS_BASE + CSL_MAIN_CTRL_MMR_CFG0_ASRC1_RXSYNC2_SEL,
                                       MAIN_CTRL_MMR_CFG0_ASRC1_RXSYNC2_SEL_SYNC_SEL, clk_source);
                        break;
                    case AASRC_RXSYNC3_IDX:
                        CSL_REG32_FINS(CSL_MAIN_CTRL_MMR_CFG0_REGS_BASE + CSL_MAIN_CTRL_MMR_CFG0_ASRC1_RXSYNC3_SEL,
                                       MAIN_CTRL_MMR_CFG0_ASRC1_RXSYNC3_SEL_SYNC_SEL, clk_source);
                        break;
                    default:
                        status = AASRC_EINVALID_PARAMS;
                        break;
                }
                break;

            default:
                status = AASRC_EINVALID_PARAMS;
                break;
        }

        SOC_controlModuleLockMMR(SOC_DOMAIN_ID_MAIN, 2U);
    }

    return status;
}

int32_t AASRC_extClkSrcTxConfig(uint32_t instNum, uint32_t txsync, uint32_t clk_source)
{
    int32_t status = AASRC_SOK;

    if(clk_source > AASRC_EXTERNAL_CLOCK_SRC_MAX_VAL)
    {
        status = AASRC_EINVALID_PARAMS;
    }

    if (status == AASRC_SOK)
    {
        SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MAIN, 2U);

        switch (instNum)
        {
            case AASRC0:
                switch (txsync)
                {
                    case AASRC_TXSYNC0_IDX:
                        CSL_REG32_FINS(CSL_MAIN_CTRL_MMR_CFG0_REGS_BASE + CSL_MAIN_CTRL_MMR_CFG0_ASRC0_TXSYNC0_SEL,
                                       MAIN_CTRL_MMR_CFG0_ASRC0_TXSYNC0_SEL_SYNC_SEL, clk_source);
                        break;
                    case AASRC_TXSYNC1_IDX:
                        CSL_REG32_FINS(CSL_MAIN_CTRL_MMR_CFG0_REGS_BASE + CSL_MAIN_CTRL_MMR_CFG0_ASRC0_TXSYNC1_SEL,
                                       MAIN_CTRL_MMR_CFG0_ASRC0_TXSYNC1_SEL_SYNC_SEL, clk_source);
                        break;
                    case AASRC_TXSYNC2_IDX:
                        CSL_REG32_FINS(CSL_MAIN_CTRL_MMR_CFG0_REGS_BASE + CSL_MAIN_CTRL_MMR_CFG0_ASRC0_TXSYNC2_SEL,
                                       MAIN_CTRL_MMR_CFG0_ASRC0_TXSYNC2_SEL_SYNC_SEL, clk_source);
                        break;
                    case AASRC_TXSYNC3_IDX:
                        CSL_REG32_FINS(CSL_MAIN_CTRL_MMR_CFG0_REGS_BASE + CSL_MAIN_CTRL_MMR_CFG0_ASRC0_TXSYNC3_SEL,
                                       MAIN_CTRL_MMR_CFG0_ASRC0_TXSYNC3_SEL_SYNC_SEL, clk_source);
                        break;
                    default:
                        status = AASRC_EINVALID_PARAMS;
                        break;
                }
                break;

            case AASRC1:
                switch (txsync)
                {
                    case AASRC_TXSYNC0_IDX:
                        CSL_REG32_FINS(CSL_MAIN_CTRL_MMR_CFG0_REGS_BASE + CSL_MAIN_CTRL_MMR_CFG0_ASRC1_TXSYNC0_SEL,
                                       MAIN_CTRL_MMR_CFG0_ASRC1_TXSYNC0_SEL_SYNC_SEL, clk_source);
                        break;
                    case AASRC_TXSYNC1_IDX:
                        CSL_REG32_FINS(CSL_MAIN_CTRL_MMR_CFG0_REGS_BASE + CSL_MAIN_CTRL_MMR_CFG0_ASRC1_TXSYNC1_SEL,
                                       MAIN_CTRL_MMR_CFG0_ASRC1_TXSYNC1_SEL_SYNC_SEL, clk_source);
                        break;
                    case AASRC_TXSYNC2_IDX:
                        CSL_REG32_FINS(CSL_MAIN_CTRL_MMR_CFG0_REGS_BASE + CSL_MAIN_CTRL_MMR_CFG0_ASRC1_TXSYNC2_SEL,
                                        MAIN_CTRL_MMR_CFG0_ASRC1_TXSYNC2_SEL_SYNC_SEL, clk_source);
                        break;
                    case AASRC_TXSYNC3_IDX:
                        CSL_REG32_FINS(CSL_MAIN_CTRL_MMR_CFG0_REGS_BASE + CSL_MAIN_CTRL_MMR_CFG0_ASRC1_TXSYNC3_SEL,
                                       MAIN_CTRL_MMR_CFG0_ASRC1_TXSYNC3_SEL_SYNC_SEL, clk_source);
                        break;
                    default:
                        status = AASRC_EINVALID_PARAMS;
                        break;
                }
                break;

            default:
                status = AASRC_EINVALID_PARAMS;
                break;
        }

        SOC_controlModuleLockMMR(SOC_DOMAIN_ID_MAIN, 2U);
    }

    return status;
}
