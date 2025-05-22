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
 *  \defgroup DRV_AASRC_SOC_MODULE AASRC Soc Specific Parameters
 *            This is AASRC Soc specific parameters and APIs
 *
 *  @{
 */

/**
 *  \file v0/soc/am275x/aasrc_soc.h
 *
 *  \brief AASRC AM275X SoC specific file.
 */

#ifndef AASRC_SOC_H_
#define AASRC_SOC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/soc.h>
#include <drivers/hw_include/am275x/cslr_main_ctrl_mmr.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* AASRC Instance numbers */
#define AASRC0                                  (0U)
#define AASRC1                                  (1U)

/* CLEC offset for AASRC Interrupts */
#define AASRC_IRQ_CLEC_OFFSET                   (224U)

/* AASRC Instance count */
#define AASRC_INSTANCE_COUNT                    (2U)
/* AASRC external clock mux max value */
#define AASRC_EXTERNAL_CLOCK_SRC_MAX_VAL        (0x1BU)
/* AASRC external audio pll divisor value
 * Use 1 to divide by 2
 * =2, to get 12.288 MHz from 24.576 MHz*/
#define AASRC_DIV_PLL4_HSDIV3_DIVISOR           (1U)
/* AASRC soft reset cycles count, needs 16 cycles of aasrc sys_clk ticks
 * AASRC runs at 200MHz, assuming C7 or R5 runs at 1 GHz
 * ratio = 5, so we need 16 x 5 = 80 processor cycles.
 * for safety, double this = 160 */
#define AASRC_SOFTRESET_CYCLES                  (160U)

/**
 *  \anchor AASRC_RxSyncClkSources
 *  \name AASRC RxSync Clock Sources
 *
 *  @{
 */
#define AASRC_RXSYNC_McASP0_AFSR             (0x0U)
#define AASRC_RXSYNC_McASP1_AFSR             (0x1U)
#define AASRC_RXSYNC_McASP2_AFSR             (0x2U)
#define AASRC_RXSYNC_McASP3_AFSR             (0x3U)
#define AASRC_RXSYNC_McASP4_AFSR             (0x4U)
#define AASRC_RXSYNC_McASP0_AFSX             (0x8U)
#define AASRC_RXSYNC_McASP1_AFSX             (0x9U)
#define AASRC_RXSYNC_McASP2_AFSX             (0xAU)
#define AASRC_RXSYNC_McASP3_AFSX             (0xBU)
#define AASRC_RXSYNC_McASP4_AFSX             (0xCU)
#define AASRC_RXSYNC_AUDIO_EXT_REFCLK0_Pin   (0x10U)
#define AASRC_RXSYNC_AUDIO_EXT_REFCLK1_Pin   (0x11U)
#define AASRC_RXSYNC_AUDIO_EXT_REFCLK2_Pin   (0x12U)
#define AASRC_RXSYNC_ADC0_CLK                (0x14U)
#define AASRC_RXSYNC_MLB_IO_CLK              (0x15U)
#define AASRC_RXSYNC_MAIN_PLL4_HSDIV3_CLKOUT (0x16U)
#define AASRC_RXSYNC_MCU_EXT_REFCLK0_Pin     (0x18U)
#define AASRC_RXSYNC_EXT_REFCLK1_Pin         (0x19U)
#define AASRC_RXSYNC_CPSW_CPTS_GENF0         (0x1AU)
#define AASRC_RXSYNC_CPSW_CPTS_GENF1         (0x1BU)
#define AASRC_RXSYNC_INVALID_CLOCK           (0xFFU)
/** @} */

/**
 *  \anchor AASRC_TxSyncClkSources
 *  \name AASRC TxSync Clock Sources
 *
 *  @{
 */
#define AASRC_TXSYNC_McASP0_AFSR             (0x0U)
#define AASRC_TXSYNC_McASP1_AFSR             (0x1U)
#define AASRC_TXSYNC_McASP2_AFSR             (0x2U)
#define AASRC_TXSYNC_McASP3_AFSR             (0x3U)
#define AASRC_TXSYNC_McASP4_AFSR             (0x4U)
#define AASRC_TXSYNC_McASP0_AFSX             (0x8U)
#define AASRC_TXSYNC_McASP1_AFSX             (0x9U)
#define AASRC_TXSYNC_McASP2_AFSX             (0xAU)
#define AASRC_TXSYNC_McASP3_AFSX             (0xBU)
#define AASRC_TXSYNC_McASP4_AFSX             (0xCU)
#define AASRC_TXSYNC_AUDIO_EXT_REFCLK0_Pin   (0x10U)
#define AASRC_TXSYNC_AUDIO_EXT_REFCLK1_Pin   (0x11U)
#define AASRC_TXSYNC_AUDIO_EXT_REFCLK2_Pin   (0x12U)
#define AASRC_TXSYNC_ADC0_CLK                (0x14U)
#define AASRC_TXSYNC_MLB_IO_CLK              (0x15U)
#define AASRC_TXSYNC_MAIN_PLL4_HSDIV3_CLKOUT (0x16U)
#define AASRC_TXSYNC_MCU_EXT_REFCLK0_Pin     (0x18U)
#define AASRC_TXSYNC_EXT_REFCLK1_Pin         (0x19U)
#define AASRC_TXSYNC_CPSW_CPTS_GENF0         (0x1AU)
#define AASRC_TXSYNC_CPSW_CPTS_GENF1         (0x1BU)
#define AASRC_TXSYNC_INVALID_CLOCK           (0xFFU)
/** @} */

/* ========================================================================== */
/*                      API Function Declarations                             */
/* ========================================================================== */

/**
 * \brief Function to configure audio pll divisor
 */
void AASRC_audioPllDivConfig(void);

/**
 * \brief Function to configure each aasrc_rxsync input's external clk source
 *
 * \param   instNum     AASRC instance number
 * \param   rxsync      AASRC rxsync input number
 * \param   clk_source  External Clock source, Refer: \ref AASRC_RxSyncClkSources
 *
 * \return  Success/Failure for configuration
 *
 */
int32_t AASRC_extClkSrcRxConfig(uint32_t instNum, uint32_t rxsync, uint32_t clk_source);

/**
 * \brief Function to configure each aasrc_txsync input's external clk source
 *
 * \param   instNum     AASRC instance number
 * \param   txsync      AASRC txsync input number
 * \param   clk_source  External Clock source, Refer: \ref AASRC_TxSyncClkSources
 *
 * \return  Success/Failure for configuration
 *
 */
int32_t AASRC_extClkSrcTxConfig(uint32_t instNum, uint32_t txsync, uint32_t clk_source);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef AASRC_SOC_H_ */

/** @} */
