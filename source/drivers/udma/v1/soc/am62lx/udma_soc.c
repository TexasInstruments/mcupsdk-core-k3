/*
 *  Copyright (c) Texas Instruments Incorporated 2025
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
 *  \file udma_soc.c
 *
 *  \brief File containing the UDMA driver SOC related configuration functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <drivers/udma/v1/udma_priv.h>
#include <drivers/hw_include/cslr_soc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

const Udma_ChAttributes gUdma_ChAttributes[UDMA_SOC_TOTAL_CHAN_NUM] =
{
    {UDMA_PDMA_CH_MAIN0_UART0_RX,      0u,  CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_RX_UART0_0,           CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_UART0_0, 1u, 0u  },
    {UDMA_PDMA_CH_MAIN0_UART0_TX,      1u,  CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_UART0_0,           CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_TX_UART0_0, 1u, 0u  },
    {UDMA_PDMA_CH_MAIN0_UART1_RX,      2u,  CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_RX_UART1_0,           CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_UART1_0, 1u, 0u  },
    {UDMA_PDMA_CH_MAIN0_UART1_TX,      3u,  CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_UART1_0,           CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_TX_UART1_0, 1u, 0u  },
    {UDMA_PDMA_CH_MAIN1_UART2_RX,      4u,  CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_RX_UART2_0,           CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_UART2_0, 1u, 0u  },
    {UDMA_PDMA_CH_MAIN1_UART2_TX,      5u,  CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_UART2_0,           CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_TX_UART2_0, 1u, 0u  },
    {UDMA_PDMA_CH_MAIN1_UART3_RX,      6u,  CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_RX_UART3_0,           CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_UART3_0, 1u, 0u  },
    {UDMA_PDMA_CH_MAIN1_UART3_TX,      7u,  CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_UART3_0,           CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_TX_UART3_0, 1u, 0u  },
    {UDMA_PDMA_CH_MAIN1_UART4_RX,      8u,  CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_RX_UART4_0,           CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_UART4_0, 1u, 0u  },
    {UDMA_PDMA_CH_MAIN1_UART4_TX,      9u,  CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_UART4_0,           CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_TX_UART4_0, 1u, 0u  },
    {UDMA_PDMA_CH_MAIN1_UART5_RX,      10u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_RX_UART5_0,           CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_UART5_0, 1u, 0u  },
    {UDMA_PDMA_CH_MAIN1_UART5_TX,      11u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_UART5_0,           CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_TX_UART5_0, 1u, 0u  },
    {UDMA_PDMA_CH_MAIN1_UART6_RX,      12u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_RX_UART6_0,           CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_UART6_0, 1u, 0u  },
    {UDMA_PDMA_CH_MAIN1_UART6_TX,      13u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_UART6_0,           CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_TX_UART6_0, 1u, 0u  },
    {UDMA_PDMA_CH_MAIN0_MCSPI0_CH0_RX, 16u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_RX_SHARED_SPI0_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_SHARED_SPI0_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI0_CH0_TX, 17u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_SHARED_SPI0_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_TX_SHARED_SPI0_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI0_CH1_RX, 18u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_RX_SHARED_SPI0_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_SHARED_SPI0_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI0_CH1_TX, 19u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_SHARED_SPI0_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_TX_SHARED_SPI0_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI0_CH2_RX, 20u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_RX_SHARED_SPI0_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_SHARED_SPI0_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI0_CH2_TX, 21u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_SHARED_SPI0_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_TX_SHARED_SPI0_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI0_CH3_RX, 22u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_RX_SHARED_SPI0_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_SHARED_SPI0_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI0_CH3_TX, 23u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_SHARED_SPI0_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_TX_SHARED_SPI0_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI1_CH0_RX, 24u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_RX_SHARED_SPI1_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_SHARED_SPI1_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI1_CH0_TX, 25u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_SHARED_SPI1_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_TX_SHARED_SPI1_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI1_CH1_RX, 26u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_RX_SHARED_SPI1_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_SHARED_SPI1_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI1_CH1_TX, 27u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_SHARED_SPI1_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_TX_SHARED_SPI1_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI1_CH2_RX, 28u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_RX_SHARED_SPI1_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_SHARED_SPI1_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI1_CH2_TX, 29u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_SHARED_SPI1_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_TX_SHARED_SPI1_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI1_CH3_RX, 30u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_RX_SHARED_SPI1_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_SHARED_SPI1_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI1_CH3_TX, 31u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_SHARED_SPI1_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_TX_SHARED_SPI1_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI2_CH0_RX, 32u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_RX_SHARED_SPI2_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_SHARED_SPI2_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI2_CH0_TX, 33u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_SHARED_SPI2_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_TX_SHARED_SPI2_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI2_CH1_RX, 34u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_RX_SHARED_SPI2_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_SHARED_SPI2_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI2_CH1_TX, 35u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_SHARED_SPI2_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_TX_SHARED_SPI2_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI2_CH2_RX, 36u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_RX_SHARED_SPI2_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_SHARED_SPI2_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI2_CH2_TX, 37u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_SHARED_SPI2_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_TX_SHARED_SPI2_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI2_CH3_RX, 38u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_RX_SHARED_SPI2_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_SHARED_SPI2_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI2_CH3_TX, 39u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_SHARED_SPI2_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_TX_SHARED_SPI2_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI3_CH0_RX, 40u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_RX_SHARED_SPI3_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_SHARED_SPI3_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI3_CH0_TX, 41u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_SHARED_SPI3_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_TX_SHARED_SPI3_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI3_CH1_RX, 42u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_RX_SHARED_SPI3_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_SHARED_SPI3_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI3_CH1_TX, 43u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_SHARED_SPI3_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_TX_SHARED_SPI3_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI3_CH2_RX, 44u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_RX_SHARED_SPI3_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_SHARED_SPI3_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI3_CH2_TX, 45u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_SHARED_SPI3_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_TX_SHARED_SPI3_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI3_CH3_RX, 46u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_RX_SHARED_SPI3_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_SHARED_SPI3_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCSPI3_CH3_TX, 47u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_SHARED_SPI3_0,     CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_TX_SHARED_SPI3_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCASP0_RX,     48u, UDMA_INTR_INVALID,                                       CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_MCASP0_CH0_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCASP0_TX,     49u, UDMA_INTR_INVALID,                                       CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_TX_MCASP0_CH0_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCASP1_RX,     50u, UDMA_INTR_INVALID,                                       CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_MCASP1_CH0_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCASP1_TX,     51u, UDMA_INTR_INVALID,                                       CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_TX_MCASP1_CH0_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCASP2_RX,     52u, UDMA_INTR_INVALID,                                       CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_MCASP2_CH0_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN0_MCASP2_TX,     53u, UDMA_INTR_INVALID,                                       CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_TX_MCASP2_CH0_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN1_ADC0_CH0_RX,   80u, UDMA_INTR_INVALID,                                       CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_SHARED_ADC_0, 1u, 0u },
    {UDMA_PDMA_CH_MAIN1_ADC0_CH1_RX,   81u, UDMA_INTR_INVALID,                                       CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_RX_SHARED_ADC_0, 1u, 0u },
    {UDMA_PSIL_CH_CPSW2_RX,            96u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_RX_CPSW_CH_0_FLOW0_0, UDMA_INTR_INVALID, 16u, 0u },
    {UDMA_PSIL_CH_CPSW2_TX0,           64u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_CPSW_CH_0_FLOW0_0, UDMA_INTR_INVALID, 2u, 0u },
    {UDMA_PSIL_CH_CPSW2_TX1,           66u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_CPSW_CH_1_FLOW0_0, UDMA_INTR_INVALID, 2u, 0u },
    {UDMA_PSIL_CH_CPSW2_TX2,           68u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_CPSW_CH_2_FLOW0_0, UDMA_INTR_INVALID, 2u, 0u },
    {UDMA_PSIL_CH_CPSW2_TX3,           70u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_CPSW_CH_3_FLOW0_0, UDMA_INTR_INVALID, 2u, 0u },
    {UDMA_PSIL_CH_CPSW2_TX4,           72u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_CPSW_CH_4_FLOW0_0, UDMA_INTR_INVALID, 2u, 0u },
    {UDMA_PSIL_CH_CPSW2_TX5,           74u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_CPSW_CH_5_FLOW0_0, UDMA_INTR_INVALID, 2u, 0u },
    {UDMA_PSIL_CH_CPSW2_TX6,           76u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_CPSW_CH_6_FLOW0_0, UDMA_INTR_INVALID, 2u, 0u },
    {UDMA_PSIL_CH_CPSW2_TX7,           78u, CSLR_GICSS0_SPI_DMASS0_PKTDMA_INTR_TX_CPSW_CH_7_FLOW0_0, UDMA_INTR_INVALID, 2u, 0u },
    {UDMA_DMA_CH_NA,                   128u,UDMA_INTR_INVALID,                                       CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_BC_BC0_0, 0u, 0u },
    {UDMA_DMA_CH_NA,                   129u,UDMA_INTR_INVALID,                                       CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_BC_BC1_0, 0u, 0u },
    {UDMA_DMA_CH_NA,                   130u,UDMA_INTR_INVALID,                                       CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_BC_BC2_0, 0u, 0u },
    {UDMA_DMA_CH_NA,                   131u,UDMA_INTR_INVALID,                                       CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_BC_BC3_0, 0u, 0u },
    {UDMA_DMA_CH_NA,                   132u,UDMA_INTR_INVALID,                                       CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_BC_BC4_0, 0u, 0u },
    {UDMA_DMA_CH_NA,                   133u,UDMA_INTR_INVALID,                                       CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_BC_BC5_0, 0u, 0u },
    {UDMA_DMA_CH_NA,                   134u,UDMA_INTR_INVALID,                                       CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_BC_BC6_0, 0u, 0u },
    {UDMA_DMA_CH_NA,                   135u,UDMA_INTR_INVALID,                                       CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_BC_BC7_0, 0u, 0u },
    {UDMA_DMA_CH_NA,                   136u,UDMA_INTR_INVALID,                                       CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_BC_BC8_0, 0u, 0u },
    {UDMA_DMA_CH_NA,                   137u,UDMA_INTR_INVALID,                                       CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_BC_BC9_0, 0u, 0u },
    {UDMA_DMA_CH_NA,                   138u,UDMA_INTR_INVALID,                                       CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_BC_BC10_0, 0u, 0u },
    {UDMA_DMA_CH_NA,                   139u,UDMA_INTR_INVALID,                                       CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_BC_BC11_0, 0u, 0u },
    {UDMA_DMA_CH_NA,                   140u,UDMA_INTR_INVALID,                                       CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_BC_BC12_0, 0u, 0u },
    {UDMA_DMA_CH_NA,                   141u,UDMA_INTR_INVALID,                                       CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_BC_BC13_0, 0u, 0u },
    {UDMA_DMA_CH_NA,                   142u,UDMA_INTR_INVALID,                                       CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_BC_BC14_0, 0u, 0u },
    {UDMA_DMA_CH_NA,                   143u,UDMA_INTR_INVALID,                                       CSLR_GICSS0_SPI_DMASS0_BCDMA_INTR_BC_BC15_0, 0u, 0u }
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */


void Udma_initDrvHandle(Udma_DrvHandleInt drvHandle)
{
    uint32_t                 instId;
    CSL_BcdmaCfg    		 *pBcdmaRegs;
    CSL_PktdmaCfg 	   	     *pPktdmaRegs;
    CSL_LcdmaRingaccCfg      *pLcdmaRaRegs;

    instId = drvHandle->initPrms.instId;
    /*
     * BCDMA/PKTDMA config init
     */
    /* Init the config structure - one time step */
    if(UDMA_INST_ID_BCDMA_0 == instId)
    {
    	drvHandle->instType = UDMA_INST_TYPE_LCDMA_BCDMA;
    	pBcdmaRegs = &drvHandle->bcdmaRegs;
        pBcdmaRegs->pGenCfgv2Regs     = ((CSL_bcdma_gcfg_v2Regs *) CSL_DMASS0_BCDMA_GCFG_BASE);
        pBcdmaRegs->pBcChanCfgv2Regs  = ((CSL_bcdma_chcfg_v2Regs *) CSL_DMASS0_BCDMA_CHAN_BASE);
        pBcdmaRegs->pBcChanRtv2Regs   = ((CSL_bcdma_chrt_v2Regs *) CSL_DMASS0_BCDMA_CHANRT_BASE);
        /* Fill other SOC specific parameters by reading from UDMA config
	     * registers */
	    CSL_bcdmaGetCfg(pBcdmaRegs);

        pPktdmaRegs = &drvHandle->pktdmaRegs;
        memset(pPktdmaRegs, 0, sizeof(*pPktdmaRegs));
    }
    else
    {
     	drvHandle->instType = UDMA_INST_TYPE_LCDMA_PKTDMA;
     	pPktdmaRegs = &drvHandle->pktdmaRegs;
        pPktdmaRegs->pGenCfgv2Regs     = ((CSL_pktdma_gcfg_v2Regs *) CSL_DMASS0_PKTDMA_GCFG_BASE);
        pPktdmaRegs->pPktChanCfgv2Regs  = ((CSL_pktdma_chcfg_v2Regs *) CSL_DMASS0_PKTDMA_CHAN_BASE);
        pPktdmaRegs->pPktChanCfgv2Regs  = ((CSL_pktdma_chcfg_v2Regs *) CSL_DMASS0_PKTDMA_CHAN_BASE);
        pPktdmaRegs->pPktChanRtv2Regs   = ((CSL_pktdma_chrt_v2Regs *) CSL_DMASS0_PKTDMA_CHANRT_BASE);
        pPktdmaRegs->pPktChanRtv2Regs   = ((CSL_pktdma_chrt_v2Regs *) CSL_DMASS0_PKTDMA_CHANRT_BASE);
        /* Fill other SOC specific parameters by reading from UDMA config
	     * registers */
	    CSL_pktdmaGetCfg(pPktdmaRegs);
        pBcdmaRegs = &drvHandle->bcdmaRegs;
        memset(pBcdmaRegs, 0, sizeof(*pBcdmaRegs));
    }

    /*
     * RA config init
     */
    pLcdmaRaRegs = &drvHandle->lcdmaRaRegs;
    if(UDMA_INST_ID_BCDMA_0 == instId) 
    {
	    pLcdmaRaRegs->pFlowCfgRegs   = (CSL_lcdma_ringacc_flow_cfg_v2Regs *) CSL_DMASS0_BCDMA_FLOW_BASE;
	    pLcdmaRaRegs->pFlowRtRegs    = (CSL_lcdma_ringacc_flowrt_v2Regs *) CSL_DMASS0_BCDMA_FLOWRT_BASE;
	    pLcdmaRaRegs->pCredRegs      = (CSL_lcdma_ringacc_cred_v2Regs *) CSL_DMASS0_BCDMA_CRED_BASE;
	    pLcdmaRaRegs->maxRings       = CSL_DMSS_BCDMA_MAX_NUM_RINGS; 
    }
    else
    {
     	pLcdmaRaRegs->pFlowCfgRegs   = (CSL_lcdma_ringacc_flow_cfg_v2Regs *) CSL_DMASS0_PKTDMA_FLOW_BASE;
	    pLcdmaRaRegs->pFlowRtRegs    = (CSL_lcdma_ringacc_flowrt_v2Regs *) CSL_DMASS0_PKTDMA_FLOWRT_BASE;
	    pLcdmaRaRegs->pCredRegs      = (CSL_lcdma_ringacc_cred_v2Regs *) CSL_DMASS0_PKTDMA_CRED_BASE;
        pLcdmaRaRegs->maxRings       = CSL_DMSS_PKTDMA_MAX_NUM_RINGS;
    }

    drvHandle->ringDequeueRaw           = &Udma_ringDequeueRawLcdma;
    drvHandle->ringQueueRaw             = &Udma_ringQueueRawLcdma;
    drvHandle->ringFlushRaw             = &Udma_ringFlushRawLcdma;
    drvHandle->ringGetElementCnt        = &Udma_ringGetElementCntLcdma;
    drvHandle->ringGetMemPtr            = &Udma_ringGetMemPtrLcdma;
    drvHandle->ringGetMode              = &Udma_ringGetModeLcdma;
    drvHandle->ringGetForwardRingOcc    = &Udma_ringGetForwardRingOccLcdma;
    drvHandle->ringGetReverseRingOcc    = &Udma_ringGetReverseRingOccLcdma;
    drvHandle->ringGetWrIdx             = &Udma_ringGetWrIdxLcdma;
    drvHandle->ringGetRdIdx             = &Udma_ringGetRdIdxLcdma;
    drvHandle->ringPrime                = &Udma_ringPrimeLcdma;
    drvHandle->ringPrimeRead            = &Udma_ringPrimeReadLcdma;
    drvHandle->ringSetDoorBell          = &Udma_ringSetDoorBellLcdma;
    drvHandle->ringSetCfg               = &Udma_ringSetCfgLcdma;
    drvHandle->ringHandleClearRegs      = &Udma_ringHandleClearRegsLcdma;

    /* Init other variables */
    if(UDMA_INST_ID_BCDMA_0 == instId)
    {
        drvHandle->txChOffset           = pBcdmaRegs->bcChanCnt;
	    drvHandle->rxChOffset   		= drvHandle->txChOffset + pBcdmaRegs->txChanCnt;
        drvHandle->udmapSrcThreadOffset = CSL_PSILCFG_DMSS_BCDMA_STRM_PSILS_THREAD_OFFSET;
	    drvHandle->udmapDestThreadOffset= CSL_PSILCFG_DMSS_BCDMA_STRM_PSILD_THREAD_OFFSET;
	    drvHandle->maxRings             = CSL_DMSS_BCDMA_MAX_NUM_RINGS;
    }
    else
    {
        drvHandle->txChOffset           = 0;
	    drvHandle->rxChOffset   		= 0 ;
	    drvHandle->udmapSrcThreadOffset = CSL_PSILCFG_DMSS_PKTDMA_STRM_PSILS_THREAD_OFFSET;
	    drvHandle->udmapDestThreadOffset= CSL_PSILCFG_DMSS_PKTDMA_STRM_PSILD_THREAD_OFFSET;
        drvHandle->maxRings             = CSL_DMSS_PKTDMA_MAX_NUM_RINGS;

    }

    drvHandle->extChOffset  = 0U;

    return;
}

uint32_t Udma_isCacheCoherent(void)
{
    uint32_t isCacheCoherent;

    isCacheCoherent = FALSE;

    return (isCacheCoherent);
}

uint32_t Udma_getChAttr(uint32_t peerChNum, Udma_ChAttributes *chAttribute, uint32_t ChNum)
{
    uint32_t loop, retVal = UDMA_SOK;
    
    const Udma_ChAttributes  *chAttr;

    for(loop = 0u; loop<UDMA_SOC_TOTAL_CHAN_NUM; loop++ )
    {
        if(peerChNum != UDMA_DMA_CH_NA)
        {
            if(peerChNum == gUdma_ChAttributes[loop].peerChNum)
            {
               chAttr = &gUdma_ChAttributes[loop];
               (void) memcpy(chAttribute, chAttr, sizeof (Udma_ChAttributes));
               break;
            }
            else
            {
               retVal = UDMA_EALLOC;
            }
        }
        else
        {
            if(ChNum == gUdma_ChAttributes[loop].ChNum)
            {
               chAttr = &gUdma_ChAttributes[loop];
               (void) memcpy(chAttribute, chAttr, sizeof (Udma_ChAttributes));
               break;
            }
            else
            {
               retVal = UDMA_EALLOC;
            }
        }
    }
    return retVal; 
}