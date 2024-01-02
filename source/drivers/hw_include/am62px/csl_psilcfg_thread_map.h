/* =============================================================================
 *   Copyright (c) 2021-2022 Texas Instruments Incorporated
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

#ifndef CSL_PSILCFG_THREAD_MAP_H_
#define CSL_PSILCFG_THREAD_MAP_H_

/*-----------------------------------------------------------------------------
 *  The following nomenclature is used in this file:
 *
 *  o #define CSL_PSILCFG_DMSS_SAUL0_PSILS_THREAD_OFFSET      (0x4000U)
 *                                             -
 *      "S" means a thread source (from the perspective of navss)
 *
 *  o #define CSL_PSILCFG_DMSS_SAUL0_PSILD_THREAD_CNT         (2U)
 *                                             -
 *      "D" means a thread destination (from the perspective of navss)
 *
 *  o #define CSL_PSILCFG_DMSS_SAUL0_PSILS_THREAD_CNT         (4U)
 *                                               ----------
 *      "THREAD_CNT" is the thread count for the specified thread
 *      source or destination
 *
 *  o #define CSL_PSILCFG_DMSS_SAUL0_PSILD_THREAD_OFFSET      (CSL_PSILCFG_DEST_THREAD_OFFSET | CSL_PSILCFG_DMSS_SAUL0_PSILS_THREAD_OFFSET)
 *                                               -------------
 *      "THREAD_OFFSET" is the starting thread # for the specified thread
 *      source or destination of the PSI-L endpoint
 *---------------------------------------------------------------------------*/

/** \brief Destination thread offset */
#define CSL_PSILCFG_DEST_THREAD_OFFSET      (0x8000U)

/**
 *  \anchor CSL_PsilcfgThreadMap
 *  \name PSIL thread map for AM64X dmss
 *
 *  Map of all PSIL threads
 *
 *  @{
 */
/*=============================================================================
 * navss_main thread map
 *===========================================================================*/
/*-----------------------------------------------------------------------------
 * PSILCFG0_CFGSTRM PSIL Map
 *---------------------------------------------------------------------------*/
#define CSL_PSILCFG_DMSS_PSILCFG0_CFGSTRM_PSILS_THREAD_OFFSET             (0x0000U)
#define CSL_PSILCFG_DMSS_PSILCFG0_CFGSTRM_PSILS_THREAD_CNT                (1U)
#define CSL_PSILCFG_DMSS_PSILCFG0_CFGSTRM_PSILD_THREAD_OFFSET             (CSL_PSILCFG_DEST_THREAD_OFFSET | CSL_PSILCFG_DMSS_PSILCFG0_CFGSTRM_PSILS_THREAD_OFFSET)
#define CSL_PSILCFG_DMSS_PSILCFG0_CFGSTRM_PSILD_THREAD_CNT                (0U)
/*-----------------------------------------------------------------------------
 * DMSS_CSI_PSILCFG0_CFGSTRM PSIL Map
 *---------------------------------------------------------------------------*/
#define CSL_PSILCFG_DMSS_CSI_PSILCFG0_CFGSTRM_PSILS_THREAD_OFFSET         (0x0003U)
#define CSL_PSILCFG_DMSS_CSI_PSILCFG0_CFGSTRM_PSILS_THREAD_CNT            (1U)
#define CSL_PSILCFG_DMSS_CSI_PSILCFG0_CFGSTRM_PSILD_THREAD_OFFSET         (CSL_PSILCFG_DEST_THREAD_OFFSET | CSL_PSILCFG_DMSS_CSI_PSILCFG0_CFGSTRM_PSILS_THREAD_OFFSET)
#define CSL_PSILCFG_DMSS_CSI_PSILCFG0_CFGSTRM_PSILD_THREAD_CNT            (0U)
/*-----------------------------------------------------------------------------
 * PKTDMA_CFGSTRM PSIL Map
 *---------------------------------------------------------------------------*/
#define CSL_PSILCFG_DMSS_PKTDMA_CFGSTRM_PSILS_THREAD_OFFSET               (0x0020U)
#define CSL_PSILCFG_DMSS_PKTDMA_CFGSTRM_PSILS_THREAD_CNT                  (1U)
#define CSL_PSILCFG_DMSS_PKTDMA_CFGSTRM_PSILD_THREAD_OFFSET               (CSL_PSILCFG_DEST_THREAD_OFFSET | CSL_PSILCFG_DMSS_PKTDMA_CFGSTRM_PSILS_THREAD_OFFSET)
#define CSL_PSILCFG_DMSS_PKTDMA_CFGSTRM_PSILD_THREAD_CNT                  (0U)
/*-----------------------------------------------------------------------------
 * BCDMA_CFGSTRM PSIL Map
 *---------------------------------------------------------------------------*/
#define CSL_PSILCFG_DMSS_BCDMA_CFGSTRM_PSILS_THREAD_OFFSET                (0x0021U)
#define CSL_PSILCFG_DMSS_BCDMA_CFGSTRM_PSILS_THREAD_CNT                   (1U)
#define CSL_PSILCFG_DMSS_BCDMA_CFGSTRM_PSILD_THREAD_OFFSET                (CSL_PSILCFG_DEST_THREAD_OFFSET | CSL_PSILCFG_DMSS_BCDMA_CFGSTRM_PSILS_THREAD_OFFSET)
#define CSL_PSILCFG_DMSS_BCDMA_CFGSTRM_PSILD_THREAD_CNT                   (0U)
/*-----------------------------------------------------------------------------
 * DMSS_CSI_BCDMA_CFGSTRM PSIL Map
 *---------------------------------------------------------------------------*/
#define CSL_PSILCFG_DMSS_CSI_BCDMA_CFGSTRM_PSILS_THREAD_OFFSET            (0x0024U)
#define CSL_PSILCFG_DMSS_CSI_BCDMA_CFGSTRM_PSILS_THREAD_CNT               (1U)
#define CSL_PSILCFG_DMSS_CSI_BCDMA_CFGSTRM_PSILD_THREAD_OFFSET            (CSL_PSILCFG_DEST_THREAD_OFFSET | CSL_PSILCFG_DMSS_CSI_BCDMA_CFGSTRM_PSILS_THREAD_OFFSET)
#define CSL_PSILCFG_DMSS_CSI_BCDMA_CFGSTRM_PSILD_THREAD_CNT               (0U)
/*-----------------------------------------------------------------------------
 * PKTDMA_STRM PSIL Map
 *---------------------------------------------------------------------------*/
#define CSL_PSILCFG_DMSS_PKTDMA_STRM_PSILS_THREAD_OFFSET                  (0x1000U)
#define CSL_PSILCFG_DMSS_PKTDMA_STRM_PSILS_THREAD_CNT                     (29U)
#define CSL_PSILCFG_DMSS_PKTDMA_STRM_PSILD_THREAD_OFFSET                  (CSL_PSILCFG_DEST_THREAD_OFFSET | CSL_PSILCFG_DMSS_PKTDMA_STRM_PSILS_THREAD_OFFSET)
#define CSL_PSILCFG_DMSS_PKTDMA_STRM_PSILD_THREAD_CNT                     (24U)
/*-----------------------------------------------------------------------------
 * BCDMA_STRM PSIL Map
 *---------------------------------------------------------------------------*/
#define CSL_PSILCFG_DMSS_BCDMA_STRM_PSILS_THREAD_OFFSET                   (0x2000U)
#define CSL_PSILCFG_DMSS_BCDMA_STRM_PSILS_THREAD_CNT                      (25U)
#define CSL_PSILCFG_DMSS_BCDMA_STRM_PSILD_THREAD_OFFSET                   (CSL_PSILCFG_DEST_THREAD_OFFSET | CSL_PSILCFG_DMSS_BCDMA_STRM_PSILS_THREAD_OFFSET)
#define CSL_PSILCFG_DMSS_BCDMA_STRM_PSILD_THREAD_CNT                      (25U)
/*-----------------------------------------------------------------------------
 * DMSS_CSI_BCDMA_STRM PSIL Map
 *---------------------------------------------------------------------------*/
#define CSL_PSILCFG_DMSS_CSI_BCDMA_STRM_PSILS_THREAD_OFFSET               (0x3100U)
#define CSL_PSILCFG_DMSS_CSI_BCDMA_STRM_PSILS_THREAD_CNT                  (8U)
#define CSL_PSILCFG_DMSS_CSI_BCDMA_STRM_PSILD_THREAD_OFFSET               (CSL_PSILCFG_DEST_THREAD_OFFSET | CSL_PSILCFG_DMSS_CSI_BCDMA_STRM_PSILS_THREAD_OFFSET)
#define CSL_PSILCFG_DMSS_CSI_BCDMA_STRM_PSILD_THREAD_CNT                  (32U)
/*-----------------------------------------------------------------------------
 * PDMA_SPI PSIL Map
 *---------------------------------------------------------------------------*/
#define CSL_PSILCFG_DMSS_PDMA_SPI_PSILS_THREAD_OFFSET                     (0x4300U)
#define CSL_PSILCFG_DMSS_PDMA_SPI_PSILS_THREAD_CNT                        (15U)
#define CSL_PSILCFG_DMSS_PDMA_SPI_PSILD_THREAD_OFFSET                     (CSL_PSILCFG_DEST_THREAD_OFFSET | CSL_PSILCFG_DMSS_PDMA_SPI_PSILS_THREAD_OFFSET)
#define CSL_PSILCFG_DMSS_PDMA_SPI_PSILD_THREAD_CNT                        (15U)
/*-----------------------------------------------------------------------------
 * PDMA_UART PSIL Map
 *---------------------------------------------------------------------------*/
#define CSL_PSILCFG_DMSS_PDMA_UART_PSILS_THREAD_OFFSET                    (0x4400U)
#define CSL_PSILCFG_DMSS_PDMA_UART_PSILS_THREAD_CNT                       (7U)
#define CSL_PSILCFG_DMSS_PDMA_UART_PSILD_THREAD_OFFSET                    (CSL_PSILCFG_DEST_THREAD_OFFSET | CSL_PSILCFG_DMSS_PDMA_UART_PSILS_THREAD_OFFSET)
#define CSL_PSILCFG_DMSS_PDMA_UART_PSILD_THREAD_CNT                       (7U)
/*-----------------------------------------------------------------------------
 * PDMA_MCASP PSIL Map
 *---------------------------------------------------------------------------*/
#define CSL_PSILCFG_DMSS_PDMA_MCASP_PSILS_THREAD_OFFSET                   (0x4500U)
#define CSL_PSILCFG_DMSS_PDMA_MCASP_PSILS_THREAD_CNT                      (3U)
#define CSL_PSILCFG_DMSS_PDMA_MCASP_PSILD_THREAD_OFFSET                   (CSL_PSILCFG_DEST_THREAD_OFFSET | CSL_PSILCFG_DMSS_PDMA_MCASP_PSILS_THREAD_OFFSET)
#define CSL_PSILCFG_DMSS_PDMA_MCASP_PSILD_THREAD_CNT                      (3U)
/*-----------------------------------------------------------------------------
 * PDMA_MCASP1 PSIL Map
 *---------------------------------------------------------------------------*/
#define CSL_PSILCFG_DMSS_PDMA_MCASP1_PSILS_THREAD_OFFSET                   (0x4580U)
#define CSL_PSILCFG_DMSS_PDMA_MCASP1_PSILS_THREAD_CNT                      (3U)
#define CSL_PSILCFG_DMSS_PDMA_MCASP1_PSILD_THREAD_OFFSET                   (CSL_PSILCFG_DEST_THREAD_OFFSET | CSL_PSILCFG_DMSS_PDMA_MCASP1_PSILS_THREAD_OFFSET)
#define CSL_PSILCFG_DMSS_PDMA_MCASP1_PSILD_THREAD_CNT                      (3U)
/*-----------------------------------------------------------------------------
 * CPSW2 PSIL Map
 *---------------------------------------------------------------------------*/
#define CSL_PSILCFG_DMSS_CPSW2_PSILS_THREAD_OFFSET                        (0x4600U)
#define CSL_PSILCFG_DMSS_CPSW2_PSILS_THREAD_CNT                           (1U)
#define CSL_PSILCFG_DMSS_CPSW2_PSILD_THREAD_OFFSET                        (CSL_PSILCFG_DEST_THREAD_OFFSET | CSL_PSILCFG_DMSS_CPSW2_PSILS_THREAD_OFFSET)
#define CSL_PSILCFG_DMSS_CPSW2_PSILD_THREAD_CNT                           (8U)
/*-----------------------------------------------------------------------------
 * CSI PSIL Map
 *---------------------------------------------------------------------------*/
#define CSL_PSILCFG_DMSS_CSI_PSILS_THREAD_OFFSET                          (0x5000U)
#define CSL_PSILCFG_DMSS_CSI_PSILS_THREAD_CNT                             (256U)
#define CSL_PSILCFG_DMSS_CSI_PSILD_THREAD_OFFSET                          (CSL_PSILCFG_DEST_THREAD_OFFSET | CSL_PSILCFG_DMSS_CSI_PSILS_THREAD_OFFSET)
#define CSL_PSILCFG_DMSS_CSI_PSILD_THREAD_CNT                             (256U)
/*-----------------------------------------------------------------------------
 * SAUL0 PSIL Map
 *---------------------------------------------------------------------------*/
#define CSL_PSILCFG_DMSS_SAUL0_PSILS_THREAD_OFFSET                        (0x7500U)
#define CSL_PSILCFG_DMSS_SAUL0_PSILS_THREAD_CNT                           (4U)
#define CSL_PSILCFG_DMSS_SAUL0_PSILD_THREAD_OFFSET                        (CSL_PSILCFG_DEST_THREAD_OFFSET | CSL_PSILCFG_DMSS_SAUL0_PSILS_THREAD_OFFSET)
#define CSL_PSILCFG_DMSS_SAUL0_PSILD_THREAD_CNT                           (2U)

/* @} */

/**
 *  \anchor CSL_PdmaCh
 *  \name PDMA Channels
 *
 *  List of all PDMA channels across dmss domain
 *
 *  @{
 */

/**
 *  \anchor CSL_PdmaChSpiTx
 *  \name SPI TX PDMA Channels
 *
 *  List of all SPI PDMA TX channels
 *
 *  @{
 */

/*
 * PDMA SPI MCSPI TX Channels
 */
#define CSL_PDMA_CH_MCSPI0_CH0_TX      (CSL_PSILCFG_DMSS_PDMA_SPI_PSILD_THREAD_OFFSET + 0U)
#define CSL_PDMA_CH_MCSPI0_CH1_TX      (CSL_PSILCFG_DMSS_PDMA_SPI_PSILD_THREAD_OFFSET + 1U)
#define CSL_PDMA_CH_MCSPI0_CH2_TX      (CSL_PSILCFG_DMSS_PDMA_SPI_PSILD_THREAD_OFFSET + 2U)
#define CSL_PDMA_CH_MCSPI0_CH3_TX      (CSL_PSILCFG_DMSS_PDMA_SPI_PSILD_THREAD_OFFSET + 3U)
#define CSL_PDMA_CH_MCSPI1_CH0_TX      (CSL_PSILCFG_DMSS_PDMA_SPI_PSILD_THREAD_OFFSET + 4U)
#define CSL_PDMA_CH_MCSPI1_CH1_TX      (CSL_PSILCFG_DMSS_PDMA_SPI_PSILD_THREAD_OFFSET + 5U)
#define CSL_PDMA_CH_MCSPI1_CH2_TX      (CSL_PSILCFG_DMSS_PDMA_SPI_PSILD_THREAD_OFFSET + 6U)
#define CSL_PDMA_CH_MCSPI1_CH3_TX      (CSL_PSILCFG_DMSS_PDMA_SPI_PSILD_THREAD_OFFSET + 7U)
#define CSL_PDMA_CH_MCSPI2_CH0_TX      (CSL_PSILCFG_DMSS_PDMA_SPI_PSILD_THREAD_OFFSET + 8U)
#define CSL_PDMA_CH_MCSPI2_CH1_TX      (CSL_PSILCFG_DMSS_PDMA_SPI_PSILD_THREAD_OFFSET + 9U)
#define CSL_PDMA_CH_MCSPI2_CH2_TX      (CSL_PSILCFG_DMSS_PDMA_SPI_PSILD_THREAD_OFFSET + 10U)
#define CSL_PDMA_CH_MCSPI2_CH3_TX      (CSL_PSILCFG_DMSS_PDMA_SPI_PSILD_THREAD_OFFSET + 11U)
/*
 * PDMA SPI MCAN TX Channels
 */
#define CSL_PDMA_CH_MCAN0_CH0_TX       (CSL_PSILCFG_DMSS_PDMA_SPI_PSILD_THREAD_OFFSET + 12U)
#define CSL_PDMA_CH_MCAN0_CH1_TX       (CSL_PSILCFG_DMSS_PDMA_SPI_PSILD_THREAD_OFFSET + 13U)
#define CSL_PDMA_CH_MCAN0_CH2_TX       (CSL_PSILCFG_DMSS_PDMA_SPI_PSILD_THREAD_OFFSET + 14U)

/* @} */

/**
 *  \anchor CSL_PdmaChSpiRx
 *  \name SPI RX PDMA Channels
 *
 *  List of all SPI PDMA RX channels
 *
 *  @{
 */

/*
 * PDMA MCSPI RX Channels
 */
#define CSL_PDMA_CH_MCSPI0_CH0_RX      (CSL_PSILCFG_DMSS_PDMA_SPI_PSILS_THREAD_OFFSET + 0U)
#define CSL_PDMA_CH_MCSPI0_CH1_RX      (CSL_PSILCFG_DMSS_PDMA_SPI_PSILS_THREAD_OFFSET + 1U)
#define CSL_PDMA_CH_MCSPI0_CH2_RX      (CSL_PSILCFG_DMSS_PDMA_SPI_PSILS_THREAD_OFFSET + 2U)
#define CSL_PDMA_CH_MCSPI0_CH3_RX      (CSL_PSILCFG_DMSS_PDMA_SPI_PSILS_THREAD_OFFSET + 3U)
#define CSL_PDMA_CH_MCSPI1_CH0_RX      (CSL_PSILCFG_DMSS_PDMA_SPI_PSILS_THREAD_OFFSET + 4U)
#define CSL_PDMA_CH_MCSPI1_CH1_RX      (CSL_PSILCFG_DMSS_PDMA_SPI_PSILS_THREAD_OFFSET + 5U)
#define CSL_PDMA_CH_MCSPI1_CH2_RX      (CSL_PSILCFG_DMSS_PDMA_SPI_PSILS_THREAD_OFFSET + 6U)
#define CSL_PDMA_CH_MCSPI1_CH3_RX      (CSL_PSILCFG_DMSS_PDMA_SPI_PSILS_THREAD_OFFSET + 7U)
#define CSL_PDMA_CH_MCSPI2_CH0_RX      (CSL_PSILCFG_DMSS_PDMA_SPI_PSILS_THREAD_OFFSET + 8U)
#define CSL_PDMA_CH_MCSPI2_CH1_RX      (CSL_PSILCFG_DMSS_PDMA_SPI_PSILS_THREAD_OFFSET + 9U)
#define CSL_PDMA_CH_MCSPI2_CH2_RX      (CSL_PSILCFG_DMSS_PDMA_SPI_PSILS_THREAD_OFFSET + 10U)
#define CSL_PDMA_CH_MCSPI2_CH3_RX      (CSL_PSILCFG_DMSS_PDMA_SPI_PSILS_THREAD_OFFSET + 11U)
/*
 * PDMA SPI MCAN RX Channels
 */
#define CSL_PDMA_CH_MCAN0_CH0_RX       (CSL_PSILCFG_DMSS_PDMA_SPI_PSILS_THREAD_OFFSET + 12U)
#define CSL_PDMA_CH_MCAN0_CH1_RX       (CSL_PSILCFG_DMSS_PDMA_SPI_PSILS_THREAD_OFFSET + 13U)
#define CSL_PDMA_CH_MCAN0_CH2_RX       (CSL_PSILCFG_DMSS_PDMA_SPI_PSILS_THREAD_OFFSET + 14U)

/* @} */

/**
 *  \anchor CSL_PdmaChUartTx
 *  \name UART TX PDMA Channels
 *
 *  List of all UART PDMA TX channels
 *
 *  @{
 */

/*
 * PDMA UART UART TX Channels
 */
#define CSL_PDMA_CH_UART0_CH0_TX       (CSL_PSILCFG_DMSS_PDMA_UART_PSILD_THREAD_OFFSET + 0U)
#define CSL_PDMA_CH_UART1_CH0_TX       (CSL_PSILCFG_DMSS_PDMA_UART_PSILD_THREAD_OFFSET + 1U)
#define CSL_PDMA_CH_UART2_CH0_TX       (CSL_PSILCFG_DMSS_PDMA_UART_PSILD_THREAD_OFFSET + 2U)
#define CSL_PDMA_CH_UART3_CH0_TX       (CSL_PSILCFG_DMSS_PDMA_UART_PSILD_THREAD_OFFSET + 3U)
#define CSL_PDMA_CH_UART4_CH0_TX       (CSL_PSILCFG_DMSS_PDMA_UART_PSILD_THREAD_OFFSET + 4U)
#define CSL_PDMA_CH_UART5_CH0_TX       (CSL_PSILCFG_DMSS_PDMA_UART_PSILD_THREAD_OFFSET + 5U)
#define CSL_PDMA_CH_UART6_CH0_TX       (CSL_PSILCFG_DMSS_PDMA_UART_PSILD_THREAD_OFFSET + 6U)

/* @} */

/**
 *  \anchor CSL_PdmaChUartRx
 *  \name UART RX PDMA Channels
 *
 *  List of all UART PDMA RX channels
 *
 *  @{
 */

/*
 * PDMA UART UART RX Channels
 */
#define CSL_PDMA_CH_UART0_CH0_RX       (CSL_PSILCFG_DMSS_PDMA_UART_PSILS_THREAD_OFFSET + 0U)
#define CSL_PDMA_CH_UART1_CH0_RX       (CSL_PSILCFG_DMSS_PDMA_UART_PSILS_THREAD_OFFSET + 1U)
#define CSL_PDMA_CH_UART2_CH0_RX       (CSL_PSILCFG_DMSS_PDMA_UART_PSILS_THREAD_OFFSET + 2U)
#define CSL_PDMA_CH_UART3_CH0_RX       (CSL_PSILCFG_DMSS_PDMA_UART_PSILS_THREAD_OFFSET + 3U)
#define CSL_PDMA_CH_UART4_CH0_RX       (CSL_PSILCFG_DMSS_PDMA_UART_PSILS_THREAD_OFFSET + 4U)
#define CSL_PDMA_CH_UART5_CH0_RX       (CSL_PSILCFG_DMSS_PDMA_UART_PSILS_THREAD_OFFSET + 5U)
#define CSL_PDMA_CH_UART6_CH0_RX       (CSL_PSILCFG_DMSS_PDMA_UART_PSILS_THREAD_OFFSET + 6U)

/* @} */

/**
 *  \anchor CSL_PdmaChMcaspTx
 *  \name MCASP TX PDMA Channels
 *
 *  List of all MCASP PDMA TX channels
 *
 *  @{
 */
/*
 * PDMA MCASP MCASP TX Channels
 */
#define CSL_PDMA_CH_MCASP0_CH0_TX      (CSL_PSILCFG_DMSS_PDMA_MCASP_PSILD_THREAD_OFFSET + 0U)
#define CSL_PDMA_CH_MCASP1_CH0_TX      (CSL_PSILCFG_DMSS_PDMA_MCASP_PSILD_THREAD_OFFSET + 1U)
#define CSL_PDMA_CH_MCASP2_CH0_TX      (CSL_PSILCFG_DMSS_PDMA_MCASP_PSILD_THREAD_OFFSET + 2U)

/* @} */

/**
 *  \anchor CSL_PdmaChMcaspRx
 *  \name MCASP RX PDMA Channels
 *
 *  List of all MCASP PDMA RX channels
 *
 *  @{
 */
/*
 * PDMA MCASP MCASP RX Channels
 */
#define CSL_PDMA_CH_MCASP0_CH0_RX      (CSL_PSILCFG_DMSS_PDMA_MCASP_PSILS_THREAD_OFFSET + 0U)
#define CSL_PDMA_CH_MCASP1_CH0_RX      (CSL_PSILCFG_DMSS_PDMA_MCASP_PSILS_THREAD_OFFSET + 1U)
#define CSL_PDMA_CH_MCASP2_CH0_RX      (CSL_PSILCFG_DMSS_PDMA_MCASP_PSILS_THREAD_OFFSET + 2U)
/* @} */

/* @} */

#endif
